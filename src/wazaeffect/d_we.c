//==============================================================================
/**
 * @file	d_we.c
 * @brief	デバッグ用技エフェクト
 * @author	goto
 * @date	2005.08.08(月)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================

#include "common.h"
#include "system/lib_pack.h"
#include "system/fontproc.h"
#include "system/pm_str.h"

#include "str_tool.h"
#include "wazaeffect/we_mana.h"
#include "system/snd_tool.h"
#include "system/msgdata.h"

#include "d_we.h"

#include "d_tool.h"
#include "we_tool.h"

#include "system/fontproc.h"
#include "system/msgdata.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_debug_goto.h"
#include "battle/wazano_def.h"

#include "system/particle.h"
#include "spl.h"
#include "system/arc_tool.h"

//          #define DWE_LOOP_ON

// -----------------------------------------
//
//	デバッグ用構造体
//
// -----------------------------------------
typedef struct _TDWE_SYS {
	int		seq;
	
	int		menu_sel;
	int		target_no;
	int		eff_no;
	int		turn_num;
	
	int 	camera;
	
	int		max;
	
//	void*	d_wk;
	WES_CALL_BTL_EX_PARAM wcbep;
	GF_BGL_BMPWIN	win;
	
	WE_SYS_PTR			wsys;
	WAZA_EFFECT_PARAM	wep;
	
	BATTLE_WORK* d_wk;
	TCB_PTR		btcb;
	TCB_FUNC	bfunc;
	
	CATS_SYS_PTR csp;	
} TDWE_SYS;

#define DWE_BUF_MAX	(4)


// =============================================================================
//
//
//	■プロトタイプ
//
//
// =============================================================================
static void DWE_MainTCB(TCB_PTR tcb, void* work);
static void DWE_ParamSet(int* num, int max, int flg);

static void DWE_WepSet(TDWE_SYS* wk);

// =============================================================================
//
//
//	■内部参照
//
//
// =============================================================================
//--------------------------------------------------------------
/**
 * @brief	
 *
 * @param	wk	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void DWE_WepSet(TDWE_SYS* wk)
{
	wk->wep.command_code = 0;
	wk->wep.mode		  = 0;
	wk->wep.waza_no	  = 0;
	
	wk->wep.waza_eff_damage = 0;
	wk->wep.waza_eff_power  = 0;
	wk->wep.waza_eff_cnt	 = wk->turn_num;
	
//	OS_Printf("デバッグターン = %2d\n",wk->wep.waza_eff_cnt);
	
	wk->wep.waza_eff_natuki = 0;
	wk->wep.waza_eff_weather= 0;
	
	switch(wk->target_no){
	case 0:
		///< AA-BB
		wk->wep.at_client_no = 0;
		wk->wep.df_client_no = 1;
		break;
	case 1:
		///< BB-AA
		wk->wep.at_client_no = 1;
		wk->wep.df_client_no = 0;
		break;
	case 2:
		///< A-B
		wk->wep.at_client_no = 2 - 2;
		wk->wep.df_client_no = 3 - 2;
		break;
	case 3:
		///< A-D
		wk->wep.at_client_no = 2 - 2;
		wk->wep.df_client_no = 5 - 2;
		break;
	case 4:
		///< C-B
		wk->wep.at_client_no = 4 - 2;
		wk->wep.df_client_no = 3 - 2;
		break;
	case 5:
		///< C-D
		wk->wep.at_client_no = 4 - 2;
		wk->wep.df_client_no = 5 - 2;
		break;
	case 6:
		///< B-A
		wk->wep.at_client_no = 3 - 2;
		wk->wep.df_client_no = 2 - 2;
		break;
	case 7:
		///< B-C
		wk->wep.at_client_no = 3 - 2;
		wk->wep.df_client_no = 4 - 2;
		break;
	case 8:
		///< D-A
		wk->wep.at_client_no = 5 - 2;
		wk->wep.df_client_no = 2 - 2;
		break;
	case 9:
		///< D-C
		wk->wep.at_client_no = 5 - 2;
		wk->wep.df_client_no = 4 - 2;
		break;
	case 10:
		///< A-C
		wk->wep.at_client_no = 2-2;
		wk->wep.df_client_no = 4-2;
		break;
	case 11:
		///< C-A
		wk->wep.at_client_no = 4-2;
		wk->wep.df_client_no = 2-2;
		break;
	case 12:
		///< B-D
		wk->wep.at_client_no = 3-2;
		wk->wep.df_client_no = 5-2;
		break;
	case 13:
		///< D-B
		wk->wep.at_client_no = 5-2;
		wk->wep.df_client_no = 3-2;
		break;
	default:
		break;
	}

	wk->csp = CATS_AllocMemory(HEAPID_BATTLE);
	wk->wcbep.csp = wk->csp;

#if 0
typedef struct{
	u8	command_code;		//命令コードインデックス
	u8	mode;				///< 戦闘・コンテスト・コンクール？
	u16	waza_no;			///<エフェクトを出す技ナンバー

	s32 waza_eff_damage;	///< 技で受けるダメージ(回復の時は[ - ])

	u16	waza_eff_power;		///< 出ている技の威力
	u16 waza_eff_cnt;		///< 技エフェクトのカウンタ(空を飛ぶとか)

	u16	waza_eff_natuki;	///< なつき度
	u16	waza_eff_weather;	///< 天候
	
	u16	at_client_no;		///< 攻撃側のクライアント番号
	u16	df_client_no;		///< 防御側のクライアント番号
}WAZA_EFFECT_PARAM;
#endif
}


//--------------------------------------------------------------
/**
 * @brief	TCB-main
 *
 * @param	tcb	
 * @param	work	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void DWE_Draw(DWE_SYS_PTR wk)
{
	int i;
	int no = 0;
	STRBUF* str_buff[DWE_BUF_MAX];
	STRBUF* str_dest[DWE_BUF_MAX];
	STRBUF* str_camera;
	STRBUF* str_target;
	STRBUF* str_steff;
	WORDSET* wset;
	DT_MsgClear(wk->wcbep.bgl, &wk->win);
	GF_BGL_BmpWinOn(&wk->win);
	
	{
		MSGDATA_MANAGER *man;
		
		man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, 
			 			    NARC_msg_debug_goto_dat, HEAPID_BATTLE);
		
		for (i = 0; i < DWE_BUF_MAX; i++){
			str_dest[i] = STRBUF_Create(255, HEAPID_BATTLE);
			str_buff[i] = MSGMAN_AllocString(man, i);
		}
		
		switch(wk->camera){
		case 0:
		case 1:
			str_camera = MSGMAN_AllocString(man, DWE_BUF_MAX + wk->camera);
			break;
		default:
			str_camera = MSGMAN_AllocString(man, DWE_BUF_MAX + 2);
			break;
		}
		
		str_target = MSGMAN_AllocString(man, dwe_07 + wk->target_no);
		
		str_steff = NULL;
		
		if (wk->max < 200){
			str_steff = MSGMAN_AllocString(man, ST_EFF_000 + wk->eff_no);
		}
		
		MSGMAN_Delete(man);
	}
	
	no = 0;
	
	
	wset = WORDSET_Create(HEAPID_BATTLE);
	
	///< 対象
//	WORDSET_RegisterNumber(wset, 3, wk->target_no, 1, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT);
//	WORDSET_ExpandStr(wset, str_dest[no], str_buff[no]);
	DT_MsgPrint(wk->wcbep.bgl, &wk->win, str_target,	0*8, no*2*8, 1);
	no++;

	///< エフェクト番号
	WORDSET_RegisterNumber(wset, 0, wk->eff_no, 3, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT);
	WORDSET_ExpandStr(wset, str_dest[no], str_buff[no]);
	DT_MsgPrint(wk->wcbep.bgl, &wk->win, str_dest[no],	0*8, no*2*8, 2);
	no++;

	///< エフェクト名
	if (wk->max >= 200){
		WORDSET_RegisterWazaName( wset, 1, wk->eff_no );
		WORDSET_ExpandStr(wset, str_dest[no], str_buff[no]);
		DT_MsgPrint(wk->wcbep.bgl, &wk->win, str_dest[no],	0*8, no*2*8, 2);
		no++;
	}
	else {
		DT_MsgPrint(wk->wcbep.bgl, &wk->win, str_steff,	0*8, no*2*8, 2);
		no++;
	}

	///< ターン数
	WORDSET_RegisterNumber(wset, 2, wk->turn_num, 2, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT);
	WORDSET_ExpandStr(wset, str_dest[no], str_buff[no]);
	DT_MsgPrint(wk->wcbep.bgl, &wk->win, str_dest[no],	0*8, no*2*8, 1);
	no++;

	///< カメラ
	DT_MsgPrint(wk->wcbep.bgl, &wk->win, str_camera,	0*8, no*2*8, 1);
	no++;

	G2_SetBG2Priority(0);
	GF_BGL_VisibleSet(BATTLE_FRAME_EFFECT, VISIBLE_ON);
	
	for (i = 0; i < DWE_BUF_MAX; i++){
		STRBUF_Delete(str_buff[i]);
		STRBUF_Delete(str_dest[i]);
	}
	STRBUF_Delete(str_camera);
	STRBUF_Delete(str_target);
	
	if (str_steff != NULL){
		STRBUF_Delete(str_steff);
	}
	WORDSET_Delete(wset);
}

static int d_cnt = 2;

static void DWE_MainTCB(TCB_PTR tcb, void* work)
{
	int* param;
	int sel_max;
	int sw = 0;
	int no = 0;
	DWE_SYS_PTR wk = (DWE_SYS_PTR)work;
	
	switch(wk->seq){
	case 0:
		///< 画面初期化
		DT_MsgClear(wk->wcbep.bgl, &wk->win);
		BattleGaugePriSet(wk->d_wk,1);
		G2_SetBG2Priority(0);
		wk->seq++;
		
	case 1:
		///< メニュー表示
		DWE_Draw(wk);
		wk->seq++;
	
	case 2:
		///< パラメーター設定
		sw = 1;
		/*
		if (sys.trg & PAD_KEY_UP){
		//	DWE_ParamSet(&wk->menu_sel, 3, -1);
		}
		else if (sys.trg & PAD_KEY_DOWN){
		//	DWE_ParamSet(&wk->menu_sel, 3, +1);
		}
		else {
			sw = 0;
		}
		if (sw){
			DWE_Draw(wk);
			break;
		}
		*/
		
		///< ターゲット
		sw = 1;
		switch(wk->menu_sel){
		case 0:
			param	= &wk->target_no;
			if (wk->wcbep.fight_type){
				sel_max = 14;
			}
			else {
				sel_max = 2;
			}
			break;
		case 1:
			param = &wk->eff_no;
			sel_max = wk->max;//WAZANO_MAX + 1;//500;
			break;
		case 2:
			param = &wk->turn_num;
			sel_max = 10;
			break;
		}
		if (sys.repeat & PAD_KEY_LEFT){
			DWE_ParamSet(param, sel_max, -1);
		}
		else if (sys.repeat & PAD_KEY_RIGHT){
			DWE_ParamSet(param, sel_max, +1);
		}
		else if (sys.repeat & PAD_BUTTON_L){
			DWE_ParamSet(param, sel_max, -10);
		}
		else if (sys.repeat & PAD_BUTTON_R){
			DWE_ParamSet(param, sel_max, +10);
		}
		else if (sys.trg & PAD_KEY_UP){
			DWE_ParamSet(param, sel_max, -100);
		}
		else if (sys.trg & PAD_KEY_DOWN){
			DWE_ParamSet(param, sel_max, +100);
		}
		else if (sys.trg & PAD_BUTTON_START){
			DWE_ParamSet(param, 0, 0);
		}
		else if (sys.trg & PAD_BUTTON_SELECT){
			///< カメラ
			wk->camera++;
			wk->camera %= 3;
			WE_SYS_CameraModeSet(wk->wsys, wk->camera);
		}
		else if (sys.trg & PAD_BUTTON_X){
			///< 対象
			param	= &wk->target_no;
			if (wk->wcbep.fight_type){
				sel_max = 14;
			}
			else {
				sel_max = 2;
			}
			DWE_ParamSet(param, sel_max, +1);
			if (wk->wcbep.fight_type){
				if (*param < 2){
					*param = 2;
				}
			}
			else {
				if (*param >= 2){
					*param = 0;
				}
			}
		}
		else if (sys.trg & PAD_BUTTON_Y){
			wk->turn_num++;
			wk->turn_num %= 5;
		}
		else {
			sw = 0;
		}
		if (sw){
			DWE_Draw(wk);
			break;
		}
		
		///< コマンド
		if (sys.trg & PAD_BUTTON_A){
			///< 発動
			GF_BGL_BmpWinOff(&wk->win);
			wk->seq++;
		}
		else if (sys.trg & PAD_BUTTON_B){
			wk->seq = 0xff;
		}
		break;
		
	case 3:
		///< エフェクト処理-初期化
		BattleGaugePriSet(wk->d_wk,0);
		DWE_WepSet(wk);
		WES_Call_Ex(wk->wsys, &wk->wep, wk->eff_no, &(wk->wcbep));
		wk->seq++;
		break;
		
	case 4:
		///< エフェクト処理-メイン
		WES_Executed(wk->wsys);
		if (IsWES_Executed(wk->wsys) == FALSE){
			BattleGaugePriSet(wk->d_wk,1);
			WES_Reset(wk->wsys);
			WET_SAFE_RELEASE(wk->csp);
		
		#ifdef DWE_LOOP_ON
		
			if (++wk->target_no > 13){
				wk->target_no = 2;
				wk->eff_no++;
				wk->seq++;
				break;
			}
			else {
				wk->seq = 3;
			}
			
		#else
		//	wk->eff_no++;
		
			wk->seq++;
			
		#endif
		
		}
		break;

	case 5:
		///< エフェクト選択処理
		BattleDefaultBlendSet();
		wk->seq = 0;
		break;

	default:
		///< 終了処理
		BattleGaugePriSet(wk->d_wk,0);
		G2_SetBG2Priority(1);
		GF_BGL_BmpWinOff(&wk->win);
		GF_BGL_BmpWinDel(&wk->win);					///< bmp-win破棄
		WES_Delete(wk->wsys);
		TCB_ChangeFunc(wk->btcb, wk->bfunc);		///< battle-tcbの復帰
		if (wk->csp != NULL){
			sys_FreeMemoryEz(wk->csp);			///< CSP
		}
		sys_FreeMemoryEz(wk);						///< メモリ解放
		TCB_Delete(tcb);							///< tcb破棄
//		GF_BGL_VisibleSet(BATTLE_FRAME_EFFECT, VISIBLE_OFF);
		break;
	}
	
}


//--------------------------------------------------------------
/**
 * @brief	パラメーターセット
 *
 * @param	num		数値
 * @param	max		最大値
 * @param	flg		符号
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void DWE_ParamSet(int* num, int max, int flg)
{
	if (flg == 0){
		*num = 0;
	}
	else if (flg < 0){
		if (*num + flg < 0){
			*num = max - 1;
		}
		else {
			*num = *num + flg;
		}
	}
	else {
		*num = *num + flg;
		*num = *num % max;
	}		
}

// =============================================================================
//
//
//	■外部参照
//
//
// =============================================================================
//--------------------------------------------------------------
/**
 * @brief	デバッグ呼び出し
 *
 * @param	work	ワーク	
 *
 * @retval	BOOL	FALSE=失敗
 *
 */
//--------------------------------------------------------------
BOOL DebugWazaEffectInit(int heap, BATTLE_WORK* bw, TCB_PTR tcb, TCB_FUNC func)
{
	DWE_SYS_PTR wk = NULL;
	int i;

	GF_BGL_VisibleSet(BATTLE_FRAME_EFFECT, VISIBLE_ON);
	
	wk = sys_AllocMemory(heap, sizeof(TDWE_SYS));
	
	if (wk == NULL){
		return FALSE;
	}

	memset(wk, 0, sizeof(TDWE_SYS));
	
	wk->wsys = WES_Create(heap);
	
//	wk->csp  = CATS_AllocMemory(HEAPID_BATTLE);//BattleWorkCATS_SYS_PTRGet(bw);	
//	GF_ASSERT(wk->csp != NULL);
	
	if (wk->wsys == NULL){
		return NULL;
	}

	TCB_ChangeFunc(tcb, NULL);

	wk->seq			= 0;
	wk->menu_sel	= 1;
	wk->target_no	= 0;
	wk->eff_no		= 0;
	wk->turn_num	= 0;
	wk->camera		= 2;
	WE_SYS_CameraModeSet(wk->wsys, wk->camera);

	wk->d_wk		= bw;
	wk->btcb		= tcb;
	wk->bfunc		= func;
	
	///< 拡張引数
	wk->wcbep.bgl	= BattleWorkGF_BGL_INIGet(bw);
	wk->wcbep.fight_type = BattleWorkFightTypeGet(bw);
	wk->wcbep.mons_no[0] = 1;
	wk->wcbep.mons_no[1] = 1;
	wk->wcbep.mons_no[2] = 1;
	wk->wcbep.mons_no[3] = 1;

	if (wk->wcbep.fight_type){
		wk->target_no = 2;
	}
	wk->wcbep.perap_voice = BattleWorkPerapVoiceGet(bw, 0);	///< ペラップ
	wk->wcbep.bg_area = BattleWorkBGAreaGet(bw);			///< BGエリア
	wk->wcbep.pal_area = BattleWorkPalAreaGet(bw);			///< PALエリア

//	wk->wcbep.excp	= BattleWorkExChrParamGet(bw);
	for(i = 0; i < CLIENT_MAX; i++){
		wk->wcbep.excp[i] = BattleWorkExChrClientParamGet(bw, i);

		///< のちのちパラメータ作る
	}
	wk->wcbep.pfd	= BattleWorkPfdGet(bw);
	BattleClientTypeBufMake(bw, &(wk->wcbep.client_type[0]));
	BattleSoftSpriteBufMake(bw, &(wk->wcbep.ss[0]));

	if (sys.cont & PAD_BUTTON_R){
		wk->max = 41;
		wk->wcbep.eff_arc_id = ARC_WAZA_EFF_SUB;
//		OS_Printf("■□■□■□■□■□■□■□■□■□■\n");
//		OS_Printf("■□ ステータスエフェクトデバッグ □■\n");
//		OS_Printf("■□■□■□■□■□■□■□■□■□■\n");
	}
	else {
		wk->max = WAZANO_MAX + 1;
		wk->wcbep.eff_arc_id = ARC_WAZA_EFF;
//		OS_Printf("■□■□■□■□■□■□■□■□■□■\n");
//		OS_Printf("■□　通常技エフェクトデバッグ　　□■\n");
//		OS_Printf("■□■□■□■□■□■□■□■□■□■\n");
	}
	
	///< 背景データ
	wk->wcbep.haikei_data.arc_index = ARC_BATT_BG;
	wk->wcbep.haikei_data.chr_id	= BATTLE_BG00_NCGR_BIN + BattleWorkBGIDGet(bw);
	wk->wcbep.haikei_data.pal_id	= BATT_BG00_D_NCLR + BattleWorkBGIDGet(bw)*3;
	wk->wcbep.haikei_data.scr_id	= BATTLE_BG00_NSCR_BIN;
	wk->wcbep.haikei_data.pal_start	= 0;
	wk->wcbep.haikei_data.pal_num	= 8;
	/*
	wk->wcbep.eff_arc_id = ARC_WAZA_EFF;
	wk->wcbep.haikei_data.arc_index = ARC_BATT_BG;
	wk->wcbep.haikei_data.chr_id	= BATTLE_BG00_NCGR_BIN;
	wk->wcbep.haikei_data.pal_id	= BATT_BG00_D_NCLR;
	wk->wcbep.haikei_data.scr_id	= BATTLE_BG00_NSCR_BIN;
	wk->wcbep.haikei_data.pal_start	= 0;
	wk->wcbep.haikei_data.pal_num	= 8;
	*/
	DT_WinAdd(wk->wcbep.bgl, &wk->win, BATTLE_FRAME_EFFECT, 0, 0, 28, 10, 0x0a,0x0d);
	
	G2_SetBG2Priority(0);

//	DT_MsgClear(wk->wcbep.bgl, &wk->win);
//	DWE_Draw(wk);
	TCB_Add(DWE_MainTCB, wk, 4);
	
	return TRUE;
}


//--------------------------------------------------------------
/**
 * @brief	デバッグ終了
 *
 * @param	none	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void DebugWazaEffectDelete(void)
{
	///< イラネ
}



