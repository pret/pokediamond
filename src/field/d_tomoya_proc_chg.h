//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		d_tomoya_proc_chg.h
 *	@brief		�v���b�N�ύX����f�o�b�N�f�[�^
 *	@author		tomoya takahashi
 *	@data		2006.03.27
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __D_TOMOYA_PROC_CHG_H__
#define __D_TOMOYA_PROC_CHG_H__


#include "field_trade_cmd.h"

#undef GLOBAL
#ifdef	__D_TOMOYA_PROC_CHG_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	�X�v���C�g��\�������邽�߂ɕK�v�ȕ�
//
//	���̌�v���b�N�`�F���W�ɕK�v�Ȃ��̂ɂȂ�܂���
//	
//	
//=====================================
typedef struct {
	int seq;
	int sub;
	int tmp_seq;
	void* p_pearent;

	FIELDSYS_WORK* p_fsys;

	void* p_work;
} DT_SPRITE_CHECK;




//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
//�@�C���[�W�N���b�v�J�n
GLOBAL void MainSprite_Check( TCB_PTR tcb, void* work );
GLOBAL void MainSprite_Check_Contest( TCB_PTR tcb, void* work );
GLOBAL void MainSprite_CheckView( TCB_PTR tcb, void* work );

// �}�ӊJ�n
GLOBAL void MainZukan_Check( TCB_PTR tcb, void* work );

// �J�n�|�P�����I��
GLOBAL void MainEvPokeSelect_Check( TCB_PTR tcb, void* work );

// �����ł�
typedef struct{
	FLD_TRADE_WORK* p_work;
	u32 seq;
} D_TOMOYA_EVENT_WORK;
GLOBAL BOOL EventScr_D_FldTrade(GMEVENT_CONTROL * event);

#undef	GLOBAL
#endif		// __D_TOMOYA_PROC_CHG_H__

