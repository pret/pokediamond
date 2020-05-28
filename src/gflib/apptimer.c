//============================================================================================
/**
 * @file	app_timer.c
 * @bfief	アプリから使えるタイマー
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include "common.h"

#define __APPTIMER_H_GLOBAL__
#include "gflib\apptimer.h"

#define	APP_TIMER_NUMBER	(OS_TIMER_3)
#define	APP_TIMER_IE		(OS_IE_TIMER3)
#define	APP_TIMER_CONTROL	((u16)( REG_OS_TM3CNT_H_E_MASK | REG_OS_TM3CNT_H_I_MASK | OS_TIMER_PRESCALER_64 ))

#define  APP_TIMER_TO_MILLI_SECONDS( t )	( ((t) * 64) / (OS_SYSTEM_CLOCK/1000) )
#define  APP_TIMER_TO_SECONDS( t )			( ((t) * 64) / OS_SYSTEM_CLOCK )


//==============================================================
// Prototype
//==============================================================
static void AppTimerHandler( void );
static u64 AppTimerGet( void );

//==============================================================
// Globals
//==============================================================
static vu64  AppTimerCount = 0;
static BOOL  ResetReq = 0;


//------------------------------------------------------------------
/**
 * 初期化：メインから１度だけ呼ばれる
 */
//------------------------------------------------------------------
void APTM_Init( void )
{
	AppTimerCount = 0;
	ResetReq = FALSE;

	OS_SetTimerControl(APP_TIMER_NUMBER, 0);
	OS_SetTimerCount(APP_TIMER_NUMBER, 0);
	OS_SetTimerControl(APP_TIMER_NUMBER, (u16)APP_TIMER_CONTROL);

	OS_SetIrqFunction( APP_TIMER_IE, AppTimerHandler );
	OS_EnableIrqMask( APP_TIMER_IE );
}

//------------------------------------------------------------------
/**
 * タイマー割り込みハンドラ
 */
//------------------------------------------------------------------
static void AppTimerHandler( void )
{
	AppTimerCount++;

	if( ResetReq )
	{
		OS_SetTimerControl(APP_TIMER_NUMBER, 0);
		OS_SetTimerCount(APP_TIMER_NUMBER, 0);
		OS_SetTimerControl(APP_TIMER_NUMBER, (u16)APP_TIMER_CONTROL);

		ResetReq = FALSE;
	}

	OS_SetIrqCheckFlag( APP_TIMER_IE );
//	OS_EnableIrqMask( APP_TIMER_IE );
	OS_SetIrqFunction( APP_TIMER_IE, AppTimerHandler );
}

//------------------------------------------------------------------
/**
 * アプリタイマー単位値を返す
 *
 * @retval  u64		
 */
//------------------------------------------------------------------
static u64 AppTimerGet( void )
{
    vu16 countL;
    vu64 countH;

    OSIntrMode prev = OS_DisableInterrupts();

    countL = *(REGType16 *)((u32)REG_TM0CNT_L_ADDR + APP_TIMER_NUMBER * 4);
    countH = AppTimerCount & 0xffffffffffffULL;

    //---- check if timer interrupt bit is on
    if (reg_OS_IF & APP_TIMER_IE && !(countL & 0x8000))
    {
        countH++;
    }

    (void)OS_RestoreInterrupts(prev);

    return (countH << 16) | countL;
}

//------------------------------------------------------------------
/**
 * 外部公開：秒単位取得
 *
 * @retval  u64		
 */
//------------------------------------------------------------------
u64 APTM_GetSec( void )
{
	u64 t = AppTimerGet();
	return APP_TIMER_TO_SECONDS( t );
}

//------------------------------------------------------------------
/**
 * 外部公開：ミリ秒単位取得
 *
 * @retval  u64		
 */
//------------------------------------------------------------------
u64 APTM_GetMsec( void )
{
	u64 t = AppTimerGet();
	return APP_TIMER_TO_MILLI_SECONDS( t );
}

//------------------------------------------------------------------
/**
 * 外部公開：生のデータを渡す
 *
 * @retval  u64		
 */
//------------------------------------------------------------------
u64 APTM_GetData( void )
{
	return AppTimerGet( );
}


//------------------------------------------------------------------
/**
 * 外部公開：生のデータ値をミリ秒単位に変換
 *
 * @param   tick		
 *
 * @retval  u64		
 */
//------------------------------------------------------------------
u64 APTM_CalcMsec( u64 tick )
{
	return APP_TIMER_TO_MILLI_SECONDS( tick );
}

//------------------------------------------------------------------
/**
 * 外部公開：生のデータ値を秒単位に変換
 *
 * @param   tick		
 *
 * @retval  u64		
 */
//------------------------------------------------------------------
u64 APTM_CalcSec( u64 tick )
{
	return APP_TIMER_TO_SECONDS( tick );
}

