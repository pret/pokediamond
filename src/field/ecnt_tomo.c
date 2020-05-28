//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		ecnt_tomo.c
 *@brief	自作エンカウント
 *@author	tomoya takahashi
 *@data		2005.07.28
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#include "common.h"
#include "system/lib_pack.h"
#include "system/brightness.h"
#include "fieldsys.h"
#include "fieldmap_work.h"
#include "field_event.h"
#include "fld_motion_bl.h"
#include "encount_effect_def.h"
#include "system/wipe.h"

#define	__ECNT_TOMO_H_GLOBAL
#include "ecnt_tomo.h"
//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------

//-------------------------------------
//	モーションブラー用
//=====================================
#define MSBL00_ROTA_START	(64)		// 回転初期速度
#define	MSBL00_ROTA_ADD		(48)		// 回転加速度
#define MSBL00_ROTA_COUNT	(40)		// 回転している時間
#define MSBL00_MSBLFADE_COUNT	(16)	// モーションブラー係数により白くしていく
#define MSBL00_DIST_START	(FX32_ONE)				// 近づく初期速度
#define MSBL00_DIST_ADD		(FX32_CONST(0.90f))		// 加速値
#define	MSBL00_CAMERA_IN_TIMING		(20)			// カメラを近づけはじめるタイミング
#define MSBL00_FADEOUT_DIV			( 8 )
#define MSBL00_FADEOUT_SYNC			( 1 )
enum{
	MSBL00_START_EFFECT,	// エフェクトスタート
	MSBL00_FLASH_INIT,		// 最初のピカピカ開始
	MSBL00_FLASH_WAIT,		// 最初のピカピカ終了待ち
	MSBL00_MOTION_INIT,		// モーションブラー準備
	MSBL00_CAMERA_ROTA,		// カメラ回転
	MSBL00_FADE_OUT,		// フェードアウト
	MSBL00_END_WAIT,		// 終了まで待つ
	MSBL00_END_EFFECT		// 終了
};

//-------------------------------------
//	モーションブラー01用
//=====================================
enum{
	MSBL01_START_EFFECT,	// エフェクトスタート
	MSBL01_FLASH_INIT,		// 最初のピカピカ開始
	MSBL01_FLASH_WAIT,		// 最初のピカピカ終了待ち
	MSBL01_MOTION_INIT,		// モーションブラー準備
	MSBL01_MOTION,			// カメラを動かす
	MSBL01_FADE_OUT,		// ブラックフェードアウト
	MSBL01_END_WAIT,		// 終了まで待つ
	MSBL01_END_EFFECT		// 終了
};

#define MSBL01_CAMERA_SHIFT_INIT	(FX32_CONST(1.0f))	// カメラシフトの最初の距離
#define MSBL01_CAMERA_SHIFT_ADD		(FX32_CONST(24.0f))	//カメラシフトの加速値
#define MSBL01_CAMERA_COUNT_ADD		(8192)
#define MSBL01_END_COUNT			(40)
#define MSBL01_FADEOUT_DIV			( 8 )
#define MSBL01_FADEOUT_SYNC			( 1 )

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------


//-------------------------------------
//	モーションブラー構造体
//=====================================
typedef struct{
	FLD_MOTION_BL_DATA_PTR	motion;
	GF_CAMERA_PTR	camera;				// カメラデータ
	u16				camera_rota;		// カメラ回転角
	u16				camera_rota_add;	// 今の回転速度
	fx32			camera_dist;		// カメラ距離
	fx32			camera_dist_add;	// カメラ距離のちかづき速度
	int				count;				// 書く処理内でのカウンタ

	/* OBJ */
} MSBL00_WORK;

//-------------------------------------
//
//	モーションブラー01構造体
//
//=====================================
typedef struct{
	FLD_MOTION_BL_DATA_PTR	motion;

	GF_CAMERA_PTR	camera;				// カメラデータ
	VecFx32			camera_shift;		// カメラシフト距離
	fx32			camera_mv;			// カメラ移動速度
	int				camera_count;		// カメラエフェクト用カウンタ
	int				count;				// 各処理内でのカウンタ
	
	/* OBJ */
} MSBL01_WORK;

//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------



//----------------------------------------------------------------------------
/**
 *
 *@brief	モーションブラー回転エンカウント
 *
 *@param	tcb		タスクポインタ
 *@param	*work	ワークポインタ
 *
 *@return	none
 *
 * エフェクトの流れ
 *
 * 1:サブ画面ブラックアウト
 * 2:メイン画面にモーションブラーがかかる
 * 3:カメラの上方向を回転させる
 * 4:どんどん早くなる
 * 5:大きなモンスターボールBGを出す。（１５フレーム）
 * 
 *
 */
//-----------------------------------------------------------------------------
void EncountEffectMotionBl00(TCB_PTR tcb, void *work)
{
	ENCOUNT_EFFECT_WORK *eew = work;
	MSBL00_WORK* task_w = eew->work;
	int add_num;

	switch(eew->seq){
	case MSBL00_START_EFFECT:	// 初期化処理
		eew->work = sys_AllocMemory(HEAPID_FIELD, sizeof(MSBL00_WORK));
		memset( eew->work, 0, sizeof(MSBL00_WORK) );
		
		GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG1, VISIBLE_OFF);
		GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG2, VISIBLE_OFF);
		GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG3, VISIBLE_OFF);
		
		eew->seq++;
		break;
		
	case MSBL00_FLASH_INIT:		// 最初のピカピカ表示
		EncountFlashTask(MASK_MAIN_DISPLAY, 16, -16,  &eew->wait, 2);

		eew->seq++;
		break;

	case MSBL00_FLASH_WAIT:
		if(eew->wait){
			eew->wait = 0;

			eew->seq++;
		}
		break;

	case MSBL00_MOTION_INIT:	// モーションブラーを使用する準備
		task_w->motion = FLDMotionBl_Init(4, 15);
		

		// カメラ回転の準備
		task_w->camera				= GFC_AllocCamera(HEAPID_FIELD);		// カメラ作成
		GFC_CopyCamera(eew->fsw->camera_ptr, task_w->camera);	// カメラコピー
		GFC_AttachCamera(task_w->camera);
		task_w->camera_rota_add		= MSBL00_ROTA_START;
		task_w->count				= MSBL00_ROTA_COUNT;
		task_w->camera_dist			= GFC_GetCameraDistance(task_w->camera);
		task_w->camera_dist_add		= MSBL00_DIST_START;
		eew->seq++;
		break;
		
	case MSBL00_CAMERA_ROTA:	// カメラ回転

		// 回転角に足す値を補正する（今のカメラの角度でしかうまくいかないので注意！！）
		// 無理やりな補正なので、カメラの角度で、作り直す必要あり！！
		add_num = FX_Mul(FX_SinIdx(task_w->camera_rota), (task_w->camera_rota_add*4)<<FX32_SHIFT) >> FX32_SHIFT;
		if(add_num < 0){		// マイナスをプラスにする
			add_num *= -1;
		}

		// 補正値＋足しこむ値を足す
		task_w->camera_rota += add_num + task_w->camera_rota_add;

		// 加速させる
		task_w->camera_rota_add += MSBL00_ROTA_ADD;
		
		{
			VecFx32	vect;
			vect.x = FX_SinIdx(task_w->camera_rota);
			vect.y = FX_CosIdx(task_w->camera_rota);
			vect.z = 0;
			GFC_SetCamUp(&vect, task_w->camera);
		}

		// カメラを徐々にちかずける
		if(task_w->count <= MSBL00_CAMERA_IN_TIMING){
			task_w->camera_dist -= task_w->camera_dist_add;
			task_w->camera_dist_add += MSBL00_DIST_ADD;
			GFC_SetCameraDistance(task_w->camera_dist, task_w->camera);
		}

		if(task_w->count < MSBL00_MSBLFADE_COUNT){
			FLDMotionBl_ParamChg(task_w->motion, 2, 16);
		}
		
		task_w->count--;
		if(task_w->count < 0){
			FLDMotionBl_ParamChg(task_w->motion, 0, 16);
			eew->seq++;
		}
		break;

	
	
	case MSBL00_FADE_OUT:		// BG描画
		WIPE_SYS_Start( WIPE_PATTERN_M, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, MSBL00_FADEOUT_DIV, MSBL00_FADEOUT_SYNC, HEAPID_FIELD );

		eew->seq++;
		break;
		
	
	
	case MSBL00_END_WAIT:
		if( WIPE_SYS_EndCheck() ){
			eew->wait = 0;

			// 元に戻す
			FLDMotionBl_Delete(&task_w->motion);
			GFC_PurgeCamera();				// カメラ割り当てフリー
			GFC_AttachCamera(eew->fsw->camera_ptr);
			GFC_FreeCamera(task_w->camera);	// カメラ破棄

			// ブライトネス解除
			G2_BlendNone();
			
			eew->seq++;
		}
		break;

	
	case MSBL00_END_EFFECT:		// 後始末
		
		if(eew->end != NULL){
			*(eew->end) = TRUE;		// タスク終了を報告
		}
		sys_FreeMemory(HEAPID_FIELD, eew->work);
		PMDS_taskDel(tcb);	//タスク終了
		WIPE_SetBrightness( WIPE_DISP_SUB, WIPE_FADE_BLACK );
		break;
	}	
}



//----------------------------------------------------------------------------
/**
 *
 *@brief	モーションブラーブレエンカウント
 *
 *@param	tcb		タスクポインタ
 *@param	*work	ワークポインタ
 *
 *@return	none
 *
 * エフェクトの流れ
 *
 * 1:モーションブラーがかかる
 * 2:カメラをぶれさせる
 * 3:ブラックアウト
 *
 */
//-----------------------------------------------------------------------------
void EncountEffectMotionBl01(TCB_PTR tcb, void *work)
{
	ENCOUNT_EFFECT_WORK *eew = work;
	MSBL01_WORK* task_w = eew->work;
	VecFx32 shift_num;
	VecFx32 set_num;

	switch(eew->seq){
	case MSBL01_START_EFFECT:	// 初期化処理
		eew->work = sys_AllocMemory(HEAPID_FIELD, sizeof(MSBL01_WORK));
		memset( eew->work, 0, sizeof(MSBL01_WORK) );
		
		GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG1, VISIBLE_OFF);
		GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG2, VISIBLE_OFF);
		GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG3, VISIBLE_OFF);
		
		eew->seq++;
		break;

	case MSBL01_FLASH_INIT:		// 最初のピカピカ表示
		EncountFlashTask(MASK_MAIN_DISPLAY, 16, -16,  &eew->wait, 2);

		eew->seq++;
		break;

	case MSBL01_FLASH_WAIT:
		if(eew->wait){
			eew->wait = 0;

			eew->seq++;
		}
		break;


	case MSBL01_MOTION_INIT:	// モーションブラーを使用する準備
	
		task_w->motion = FLDMotionBl_Init(2, 14);
		
		// カメラ移動の準備
		task_w->camera				= GFC_AllocCamera(HEAPID_FIELD);		// カメラ作成
		GFC_CopyCamera(eew->fsw->camera_ptr, task_w->camera);	// カメラコピー
		GFC_AttachCamera(task_w->camera);
		task_w->camera_mv	= MSBL01_CAMERA_SHIFT_INIT;
		task_w->camera_count= 0;
		task_w->count		= MSBL01_END_COUNT;
		eew->seq++;
		break;
		
		
	case MSBL01_MOTION:	// カメラ移動
		
		// 移動させる
		shift_num.x = FX_SinIdx(task_w->camera_count);
		shift_num.x = FX_Mul(shift_num.x, task_w->camera_mv);
		shift_num.y = 0;
		shift_num.z = 0;

		set_num.x =	shift_num.x - task_w->camera_shift.x;
		set_num.y =	shift_num.y - task_w->camera_shift.y;
		set_num.z =	shift_num.z - task_w->camera_shift.z;
		
		// 設定
		GFC_ShiftCamera(&set_num, task_w->camera);

		// カウント
		task_w->camera_count += MSBL01_CAMERA_COUNT_ADD;
		if(task_w->camera_count >= 0x10000){
			task_w->camera_count = 0;
			task_w->camera_mv += MSBL01_CAMERA_SHIFT_ADD;
		}
		
		// 移動させた距離を保存（最後に元に戻すため）
		task_w->camera_shift.x = shift_num.x;
		task_w->camera_shift.y = shift_num.y;
		task_w->camera_shift.z = shift_num.z;
		
		
		task_w->count--;
		if(task_w->count < 0){
			eew->seq++;
		}
		break;

	
	
	case MSBL01_FADE_OUT:		// フェードアウト
		//BG面を横にカット
		ENC_BG_Cut_Start( eew );
		
		//ブラックアウト
		WIPE_SYS_Start( WIPE_PATTERN_M, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, MSBL01_FADEOUT_DIV, MSBL01_FADEOUT_SYNC, HEAPID_FIELD );
		eew->seq++;
		break;
		
	
	
	case MSBL01_END_WAIT:
		if((ENC_HBlankEndCheck(eew) == TRUE) && ( WIPE_SYS_EndCheck() == TRUE )){
			// 元に戻す
			FLDMotionBl_Delete(&task_w->motion);
			GFC_PurgeCamera();				// カメラ割り当てフリー
			GFC_AttachCamera(eew->fsw->camera_ptr);
			GFC_FreeCamera(task_w->camera);	// カメラ破棄

			// ブライトネス解除
			G2_BlendNone();
			
			eew->seq++;
		}
		break;

	
	case MSBL01_END_EFFECT:		// 後始末
		
		G2_SetBG0Offset(0, 0);
		G2_SetBG1Offset(0, 0);
		G2_SetBG2Offset(0, 0);
		G2_SetBG3Offset(0, 0);
		
		if(eew->end != NULL){
			*(eew->end) = TRUE;		// タスク終了を報告
		}
		sys_FreeMemory(HEAPID_FIELD, eew->work);
		PMDS_taskDel(tcb);	//タスク終了
		WIPE_SetBrightness( WIPE_DISP_SUB, WIPE_FADE_BLACK );
		break;
	}	
}
