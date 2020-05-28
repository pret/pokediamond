//輝度変更
#include "common.h"
#include "system/brightness.h"

enum{
	BRIGHT_CHG_NO = 0,
	BRIGHT_CHG_YES
};

typedef struct BRIGHTNESS_CHG_tag{
	BRIGHT_PARAM BrightParam;
	s8	Dir;

	s16 Dif;
	s16 dps;
	u16 d_rest;
	u16	rest;
	
	s16 Now;

	BOOL Request;

//BRIGHT_PLANEMASK PlaneMask;
//BRIGHT_DISPMASK DisplayMask;	
//u16 Sync;
//s16 Dst;
//s16 Src;
}BRIGHTNESS_CHG;


static BRIGHTNESS_CHG MainBrightCont;
static BRIGHTNESS_CHG SubBrightCont;

static void SetUpBrightness(BRIGHTNESS_CHG	*bright_data,
							const u8 inSync,
							const s16 inDstBright,
							const s16 inSrcBright,
							const BRIGHT_PLANEMASK inPlaneMask,
							const BRIGHT_DISPMASK inDisplayMask);

//==============================================================================
/**
 * 輝度変更
 *
 * @param	bright_data	輝度変更構造体へのポインタ
 *
 * @retval  なし
 */
//==============================================================================
static void ChangeBrightness(BRIGHTNESS_CHG *bright_data)
{
	BRIGHT_PARAM *param;
	BOOL finished;
	
	finished = BRIGHT_CHG_NO;
	param = &bright_data->BrightParam;
	
	if ((bright_data->Now + bright_data->Dir*bright_data->dps != param->Dst) &&
			(bright_data->Now != param->Dst)){
		bright_data->Now += bright_data->Dir*bright_data->dps;
		bright_data->rest += bright_data->d_rest;
		if (bright_data->rest>=param->Sync){
			bright_data->Now += bright_data->Dir;

			if (bright_data->Now != param->Dst){
				bright_data->rest -= param->Sync;
			}else{
				finished = BRIGHT_CHG_YES;
			}
		}
	}else{
		bright_data->Now = param->Dst;
		finished = BRIGHT_CHG_YES;
	}

	if (param->DisplayMask & MASK_MAIN_DISPLAY){
		G2_SetBlendBrightness(param->PlaneMask,bright_data->Now);
	}
	else if (param->DisplayMask & MASK_SUB_DISPLAY){
		G2S_SetBlendBrightness(param->PlaneMask,bright_data->Now);
	}

	if (finished == BRIGHT_CHG_YES){
		bright_data->Request = FALSE;
	}

}

//==============================================================================
/**
 * 輝度セットアップ
 *
 * @param	*bright_data	輝度変更構造体へのポインタ
 * @param   inSync			フェードするのにかかるSync数
 * @param   inDstBright		フェード終了時の輝度（上にdefineあり)	←  こっちが終了時
 * @param   inSrcBright		フェード開始時の輝度（上にdefineあり)
 * @param   inPlaneMask		フェードが反映されるBG面（上にenumあり)
 * @param   inDisplayMask	フェードが反映されるLCD（上にenumあり)
 *
 * @retval  なし
 */
//==============================================================================
static void SetUpBrightness(BRIGHTNESS_CHG	*bright_data,
							const u8 inSync,
							const s16 inDstBright,
							const s16 inSrcBright,
							const BRIGHT_PLANEMASK inPlaneMask,
							const BRIGHT_DISPMASK inDisplayMask)
{
	BRIGHT_PARAM *param;
	GF_ASSERT((bright_data->Request == FALSE)&&"輝度変更リクエストがかかっています");
	bright_data->Request = TRUE;
	
	param = &bright_data->BrightParam;

	//輝度変更面マスク
	param->PlaneMask = (u8)inPlaneMask;
	//輝度反映表示画面マスク
	param->DisplayMask = (u8)inDisplayMask;
	//Sync何シンクで色を変えるか
	param->Sync = inSync;
	//目的輝度
	param->Dst = inDstBright;
	//現在輝度
	bright_data->Now = inSrcBright;
	//現在輝度と指定輝度の差をとる
	bright_data->Dif = inSrcBright - inDstBright;
	//とった差分をシンク数で割る
	//商が１シンクの変化量（余りは保存して足しこみ、割った数(指定シンク)を超えたら変化量に追加）
	
	if (bright_data->Dif>0){
		bright_data->Dir = -1;
	}else{
		bright_data->Dir = 1;
		bright_data->Dif *= (-1);
	}
	bright_data->dps = bright_data->Dif/inSync;
	bright_data->d_rest = bright_data->Dif%inSync;
	bright_data->rest = 0;
}

//==============================================================================
/**
 * 輝度変更フェードリクエスト
 *
 * @param   inSync			フェードするのにかかるSync数
 * @param   inDstBright		フェード終了時の輝度（上にdefineあり)	←  こっちが終了時
 * @param   inSrcBright		フェード開始時の輝度（上にdefineあり)
 * @param   inPlaneMask		フェードが反映されるBG面（上にenumあり)
 * @param   inDisplayMask	フェードが反映されるLCD（上にenumあり)
 *
 * @retval  なし
 */
//==============================================================================
void ChangeBrightnessRequest(const u8 inSync, const s16 inDstBright, const s16 inSrcBright,
		const BRIGHT_PLANEMASK inPlaneMask, const BRIGHT_DISPMASK inDisplayMask)
{
	BRIGHTNESS_CHG	*bright_data;
	
	//0シンクでの輝度変更は不可能なので、リクエストを拒否
	if (inSync == 0){
		return;
	}

	//初期輝度をセット
	if (inDisplayMask & MASK_MAIN_DISPLAY){
		G2_SetBlendBrightness(inPlaneMask,inSrcBright);
		bright_data = &MainBrightCont;
		SetUpBrightness(bright_data,inSync,inDstBright,inSrcBright,
				inPlaneMask, MASK_MAIN_DISPLAY);
	}
	if (inDisplayMask & MASK_SUB_DISPLAY){
		G2S_SetBlendBrightness(inPlaneMask,inSrcBright);
		bright_data = &SubBrightCont;
		SetUpBrightness(bright_data,inSync,inDstBright,inSrcBright,
				inPlaneMask, MASK_SUB_DISPLAY);
	}
	
}

//==============================================================================
/**
 * 輝度変更
 *
 * @param   inDstBright		輝度（上にdefineあり)
 * @param   inPlaneMask		フェードが反映されるBG面（上にenumあり)
 * @param   inDisplayMask	フェードが反映されるLCD（上にenumあり)
 *
 * @retval  なし
 */
//==============================================================================
void SetBrightness(	const s16 inDstBright,
					const BRIGHT_PLANEMASK inPlaneMask,
					const BRIGHT_DISPMASK inDisplayMask)
{
	if (inDisplayMask & MASK_MAIN_DISPLAY){
		G2_SetBlendBrightness(inPlaneMask,inDstBright);
	}
	if (inDisplayMask & MASK_SUB_DISPLAY){
		G2S_SetBlendBrightness(inPlaneMask,inDstBright);
	}
	BrightnessChgReset(inDisplayMask);
}

//==============================================================================
/**
 * 輝度変更構造体初期化
 *
 * @param	なし
 *
 * @retval  なし
 */
//==============================================================================
void BrightnessChgInit(void)
{
	MI_CpuClear8(&MainBrightCont, sizeof(BRIGHTNESS_CHG));
	MI_CpuClear8(&SubBrightCont, sizeof(BRIGHTNESS_CHG));
	MainBrightCont.Request = FALSE;
	SubBrightCont.Request = FALSE;
}

//==============================================================================
/**
 * 輝度変更構造体のリセット
 *
 * @param   inDisplayMask	フェードが反映されるLCD（上にenumあり)
 *
 * @retval  なし
 */
//==============================================================================
void BrightnessChgReset(const BRIGHT_DISPMASK inDisplayMask)
{
	if (inDisplayMask & MASK_MAIN_DISPLAY){
		MI_CpuClear8(&MainBrightCont, sizeof(BRIGHTNESS_CHG));
		MainBrightCont.Request = FALSE;
	}
	if (inDisplayMask & MASK_SUB_DISPLAY){
		MI_CpuClear8(&SubBrightCont, sizeof(BRIGHTNESS_CHG));
		SubBrightCont.Request = FALSE;
	}
}

//==============================================================================
/**
 * 輝度変更メイン
 *
 * @param	なし
 *
 * @retval  なし
 */
//==============================================================================
void BrightnessChgMain(void)
{
	//リクエストチェック
	if (MainBrightCont.Request){
		ChangeBrightness(&MainBrightCont);
	}
	if (SubBrightCont.Request){
		ChangeBrightness(&SubBrightCont);
	}
}

//==============================================================================
/**
 * 終了チェック
 *
 * @param	flg 調べるＬＣＤＣ
 *
 * @retval  終了有無
 */
//==============================================================================
BOOL IsFinishedBrightnessChg(BRIGHT_DISPMASK flg)
{
	if (flg == MASK_DOUBLE_DISPLAY){
		if (MainBrightCont.Request == FALSE && SubBrightCont.Request == FALSE){
			return TRUE;
		}
	}else if(flg == MASK_MAIN_DISPLAY){
		if (MainBrightCont.Request == FALSE){
			return TRUE;
		}
	}else if (flg == MASK_SUB_DISPLAY){
		if (SubBrightCont.Request == FALSE){
			return TRUE;
		}
	}

	return FALSE;
}

