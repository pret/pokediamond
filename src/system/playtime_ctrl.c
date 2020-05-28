//============================================================================================
/**
 * @brief	playtime_ctrl.c
 * @brief	プレイ時間情報の操作
 * @date	2006.06.21
 * @author	taya
 */
//============================================================================================
#include "common.h"
#include "gflib\apptimer.h"
#include "savedata/playtime.h"

#include "system\playtime_ctrl.h"


static BOOL StartFlag = FALSE;
static u64  PassedTick = 0;
static u64  PassedSec = 0;
static u64  StartTick = 0;
static PLAYTIME*  PlayTimePointer = NULL;

//------------------------------------------------------------------
/**
 * 初期化（ゲームメインループの前に１回だけ呼ぶ）
 */
//------------------------------------------------------------------
void PlayTimeCtrl_Init( void )
{
	StartFlag = FALSE;
}

//------------------------------------------------------------------
/**
 * プレイ時間のカウント開始（ゲーム開始直後に１回だけ呼ぶ）
 *
 */
//------------------------------------------------------------------
void PlayTimeCtrl_Start( PLAYTIME* pt )
{
	StartFlag = TRUE;
	PassedTick = 0;
	PassedSec = 0;
	PlayTimePointer = pt;
	StartTick = APTM_GetData();
}

//------------------------------------------------------------------
/**
 * プレイ時間のカウント（メインループ内で毎回呼ぶ）
 *
 * @param   time		プレイ時間セーブデータポインタ
 *
 */
//------------------------------------------------------------------
void PlayTimeCtrl_Countup( void )
{
	if( StartFlag )
	{
		u64  sec = APTM_CalcSec( APTM_GetData() - StartTick );
		if( sec > PassedSec )
		{
			PLAYTIME_CountUp( PlayTimePointer, (sec - PassedSec) );
			PassedSec = sec;
		}
	}
}










