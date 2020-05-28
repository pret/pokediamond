//============================================================================================
/**
 * @file	sleep.c
 * @brief	�X���[�v���[�h�ݒ�
 * @author	Hiroyuki Nakamura
 * @date	2005.02.28
 */
//============================================================================================
#define	SLEEP_H_GLOBAL

#include "system.h"
#include "standard.h"
#include "tcb.h"
#include "gflib_os_print.h"

#include "sleep.h"


//============================================================================================
//	�V���{����`
//============================================================================================


//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================
static void CoverCloseCheckTask( TCB_PTR _tcb, void * work );


//============================================================================================
//	�ݒ�
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �X���[�v�f�[�^�̈�m�ہA������
 *
 * @param	heap	�q�[�vID
 *
 * @return	�X���[�v�f�[�^�̈�
 */
//--------------------------------------------------------------------------------------------
GF_SLEEP_SYS * GF_SleepSystemInit( u32 heap )
{
	GF_SLEEP_SYS * dat = (GF_SLEEP_SYS *)sys_AllocMemory( heap, sizeof(GF_SLEEP_SYS) );

#ifdef	OSP_ERR_SLEEPBUF_GET	// �X���[�v�p�̃o�b�t�@�m�ێ��s
	if( dat == NULL ){
		OS_Printf( "ERROR : GF_SleepSystemInit\n" );
		return;
	}
#endif	// OSP_ERR_SLEEPBUF_GET	// �X���[�v�p�̃o�b�t�@�m�ێ��s

	memset( dat, 0, sizeof(GF_SLEEP_SYS) );
	dat->heap = (u16)heap;

	return dat;
}

//--------------------------------------------------------------------------------------------
/**
 * �V�X�e������
 *
 * @param	dat		�X���[�v�f�[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void GF_SleepSystemDelete( GF_SLEEP_SYS * dat )
{
#ifdef	OSP_ERR_SLEEP_DEL		// �X���[�v�p�̃o�b�t�@���m�ۂ��Ă��Ȃ�
	if( dat == NULL ){
		OS_Printf( "ERROR : GF_SleepSystemDelete\n" );
		return;
	}
#endif	// OSP_ERR_SLEEP_DEL

	GF_SleepCallBackDel( dat, GF_SLEEP_CB_BEFORE );
	GF_SleepCallBackDel( dat, GF_SLEEP_CB_AFTER );
	sys_FreeMemory( dat->heap, dat );
}

//--------------------------------------------------------------------------------------------
/**
 * �X���[�v�̃g���K�[�ݒ�
 *
 * @param	dat		�X���[�v�f�[�^
 * @param	trg		�X���[�v��Ԃ���̕��A�v��
 * @param	logic	�L�[�����݂ŕ��A����ꍇ�̃L�[�̑g�ݍ��킹�_��
 * @param	pat		�L�[�����݂ŕ��A����ꍇ�̃L�[
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void GF_SleepTriggerSet( GF_SLEEP_SYS * dat, PMWakeUpTrigger trg, PMLogic logic, u16 pat )
{
	dat->trigger = trg;
	dat->logic = logic;
	dat->keyPattern = pat;
}

//--------------------------------------------------------------------------------------------
/**
 * �X���[�v�f�[�^�ݒ�
 *
 * @param	dat		�X���[�v�f�[�^
 *
 * @return	none
 *
 * @li	dat->hold : GF_SLEEP_MODE = ���X���[�v
 * @li	�X���[�v��s���ɂ���ɂ�GF_SleepModeSet(GF_SLEEP_HOLD)���ĂԂ���
 */
//--------------------------------------------------------------------------------------------
void GF_SleepSystemSetAll( GF_SLEEP_SYS * dat )
{
	u16	init;

#ifdef	OSP_ERR_SLEEP_SET		// �X���[�v�ݒ莸�s
	if( dat == NULL ){
		OS_Printf( "ERROR : GF_SleepSystemSetAll\n" );
		return;
	}
#endif	// SP_ERR_SLEEP_SET

	init = dat->hold;
	dat->hold = GF_SLEEP_MODE;

	if( dat->b_info.callback != NULL ){
		GF_SleepCallBackAdd( dat, &dat->b_info, GF_SLEEP_CB_BEFORE, GF_SLEEP_CB_BEFORE );
	}
	if( dat->a_info.callback != NULL ){
		GF_SleepCallBackAdd( dat, &dat->a_info, GF_SLEEP_CB_AFTER, GF_SLEEP_CB_BEFORE );
	}

	if( init == GF_SLEEP_MODE ){
		GF_GoSleepMode( dat );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * ����؂�ւ�
 *
 * @param	dat		�X���[�v�f�[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void GF_GoSleepMode( GF_SLEEP_SYS * dat )
{
	if( dat->hold == GF_SLEEP_HOLD ){ return; }
	PM_GoSleepMode( dat->trigger, dat->logic, dat->keyPattern );
}

//--------------------------------------------------------------------------------------------
/**
 * ����؂�ւ�
 *
 * @param	dat		�X���[�v�f�[�^
 * @param	flg		GF_SLEEP_MODE = ����, GF_SLEEP_HOLD = �s����
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void GF_SleepModeSet( GF_SLEEP_SYS * dat, u8 flg )
{
	dat->hold = flg;
}


//============================================================================================
//	�R�[���o�b�N
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �R�[���o�b�N���Z�b�g
 *
 * @param	dat		�X���[�v�f�[�^
 * @param	info	�R�[���o�b�N���
 * @param	type	�ǉ��^�C�v ( GF_SLEEP_CB_BEFORE = �ڍs��, GF_SLEEP_CB_AFTER = ���A�� )
 * @param	mode	�ǉ����[�h ( GF_SLEEP_CB_BEFORE = �擪��, GF_SLEEP_CB_AFTER = ������ )
 *
 * @return	none
 *
 * @li	�����o�^�͖��Ή�
 */
//--------------------------------------------------------------------------------------------
void GF_SleepCallBackAdd( GF_SLEEP_SYS * dat, PMSleepCallbackInfo * info, u8 type, u8 mode )
{
	u8	i;

	if( type == GF_SLEEP_CB_BEFORE ){
#ifdef	OSP_ERR_SLEEP_CALLBACK_SET		// �R�[���o�b�N�ݒ莸�s
		if( dat->b_info.callback != NULL ){
			OS_Printf( "ERROR : GF_SleepCallBackAdd( GF_SLEEP_CB_BEFORE )\n" );
			return;
		}
#endif	// OSP_ERR_SLEEP_CALLBACK_SET
		dat->b_info = *info;

		if( mode == GF_SLEEP_CB_BEFORE ){
			PM_PrependPreSleepCallback( &dat->b_info );
		}else{
			PM_AppendPreSleepCallback( &dat->b_info );
		}
	}else{
#ifdef	OSP_ERR_SLEEP_CALLBACK_SET		// �R�[���o�b�N�ݒ莸�s
		if( dat->a_info.callback != NULL ){
			OS_Printf( "ERROR : GF_SleepCallBackAdd( GF_SLEEP_CB_AFTER )\n" );
			return;
		}
#endif	// OSP_ERR_SLEEP_CALLBACK_SET
		dat->a_info = *info;

		if( mode == GF_SLEEP_CB_BEFORE ){
			PM_PrependPostSleepCallback( &dat->a_info );
		}else{
			PM_AppendPostSleepCallback( &dat->a_info );
		}
	}
}

//--------------------------------------------------------------------------------------------
/**
 * �R�[���o�b�N���폜
 *
 * @param	dat		�X���[�v�f�[�^
 * @param	id		�폜�^�C�v ( GF_SLEEP_CB_BEFORE = �ڍs��, GF_SLEEP_CB_AFTER = ���A�� )
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void GF_SleepCallBackDel( GF_SLEEP_SYS * dat, u8 id )
{
	if( id == GF_SLEEP_CB_BEFORE ){
		if( dat->b_info.callback == NULL ){ return; }
		PM_DeletePreSleepCallback( &dat->b_info );
	}else{
		if( dat->a_info.callback == NULL ){ return; }
		PM_DeletePostSleepCallback( &dat->a_info );
	}
}


//============================================================================================
//	�{�̂̊J�ŃX���[�v
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * �{�̂̊J�ŃX���[�v����^�X�N���Z�b�g
 *
 * @param	dat		�X���[�v�f�[�^
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void GF_SleepCoverCloseAdd( GF_SLEEP_SYS * dat )
{
/*
	GF_SLEEP_SYS	dat = {
		{NULL,NULL,NULL}, {NULL,NULL,NULL}, PM_TRIGGER_COVER_OPEN, 0, 0, 1
	};

	GF_SleepSystemSetAll( &dat );
*/
	GF_SleepTriggerSet( dat, PM_TRIGGER_COVER_OPEN, 0, 0 );
	TCB_Add( CoverCloseCheckTask, dat, 0 );
}

//--------------------------------------------------------------------------------------------
/**
 * �{�̂̊J�ŃX���[�v����^�X�N
 *
 * @param	none
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void CoverCloseCheckTask( TCB_PTR _tcb, void * work )
{
	if( PAD_DetectFold() == FALSE ){ return; }

	{
		GF_SLEEP_SYS * dat = (GF_SLEEP_SYS *)work;
		GF_GoSleepMode( dat );
	}
}
