//============================================================================================
/**
 * @brief	playtime_ctrl.c
 * @brief	�v���C���ԏ��̑���
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
 * �������i�Q�[�����C�����[�v�̑O�ɂP�񂾂��Ăԁj
 */
//------------------------------------------------------------------
void PlayTimeCtrl_Init( void )
{
	StartFlag = FALSE;
}

//------------------------------------------------------------------
/**
 * �v���C���Ԃ̃J�E���g�J�n�i�Q�[���J�n����ɂP�񂾂��Ăԁj
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
 * �v���C���Ԃ̃J�E���g�i���C�����[�v���Ŗ���Ăԁj
 *
 * @param   time		�v���C���ԃZ�[�u�f�[�^�|�C���^
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










