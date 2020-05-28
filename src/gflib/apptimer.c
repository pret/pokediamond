//============================================================================================
/**
 * @file	app_timer.c
 * @bfief	�A�v������g����^�C�}�[
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
 * �������F���C������P�x�����Ă΂��
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
 * �^�C�}�[���荞�݃n���h��
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
 * �A�v���^�C�}�[�P�ʒl��Ԃ�
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
 * �O�����J�F�b�P�ʎ擾
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
 * �O�����J�F�~���b�P�ʎ擾
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
 * �O�����J�F���̃f�[�^��n��
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
 * �O�����J�F���̃f�[�^�l���~���b�P�ʂɕϊ�
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
 * �O�����J�F���̃f�[�^�l��b�P�ʂɕϊ�
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

