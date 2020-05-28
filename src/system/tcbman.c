//=============================================================================================
/**
 * @file	tcbman.c
 * @brief	�eTCB�V�X�e������ă^�X�N�������Ăяo��
 * @author	taya
 * @date	2005.10.07
 */
//=============================================================================================
#include "common.h"
#include "tcb.h"


//------------------------------------------------------------------
/**
 * TCB�o�^�i���C�����[�v���ɌĂ΂��^�X�N�j
 *
 * @param   func		�^�X�N���s�֐�
 * @param   work		�^�X�N�Ɋ֘A�t���郏�[�N�G���A�̃A�h���X
 * @param   pri			�^�X�N�v���C�I���e�B
 *
 * @retval  TCB_PTR		�o�^���ꂽTCB�|�C���^
 */
//------------------------------------------------------------------
TCB_PTR TCB_Add(TCB_FUNC func, void* work, u32 pri)
{
	return TCBSYS_AddTask( sys.mainTCBSys, func, work, pri );
}
//------------------------------------------------------------------
/**
 * TCB�o�^�iVBlank���荞�ݒ��ɌĂ΂��^�X�N�j
 *
 * @param   func		�^�X�N���s�֐�
 * @param   work		�^�X�N�Ɋ֘A�t���郏�[�N�G���A�̃A�h���X
 * @param   pri			�^�X�N�v���C�I���e�B
 *
 * @retval  TCB_PTR		�o�^���ꂽTCB�|�C���^
 */
//------------------------------------------------------------------
TCB_PTR VIntrTCB_Add( TCB_FUNC func, void* work, u32 pri )
{
	return TCBSYS_AddTask( sys.vintrTCBSys, func, work, pri );
}

//------------------------------------------------------------------
/**
 * TCB�o�^�i�����o�̓^�X�N=VBlank���荞�ݑO�ɌĂ΂��j
 *
 * @param   func		�^�X�N���s�֐�
 * @param   work		�^�X�N�Ɋ֘A�t���郏�[�N�G���A�̃A�h���X
 * @param   pri			�^�X�N�v���C�I���e�B
 *
 * @retval  TCB_PTR		�o�^���ꂽTCB�|�C���^
 */
//------------------------------------------------------------------
TCB_PTR PrintTCB_Add( TCB_FUNC func, void* work, u32 pri )
{
	return TCBSYS_AddTask( sys.printTCBSys, func, work, pri );
}

//------------------------------------------------------------------
/**
 * TCB�o�^�i���C�����[�v�I���҂���̓����p�^�X�N�j
 *
 * @param   func		�^�X�N���s�֐�
 * @param   work		�^�X�N�Ɋ֘A�t���郏�[�N�G���A�̃A�h���X
 * @param   pri			�^�X�N�v���C�I���e�B
 *
 * @retval  TCB_PTR		�o�^���ꂽTCB�|�C���^
 */
//------------------------------------------------------------------
TCB_PTR VWaitTCB_Add( TCB_FUNC func, void* work, u32 pri )
{
	return TCBSYS_AddTask( sys.vwaitTCBSys, func, work, pri );
}


//------------------------------------------------------------------
/**
 * TCB�폜
 *
 * @param   TCB_PTR		�폜����TCB�|�C���^
 */
//------------------------------------------------------------------
void TCB_Delete(TCB_PTR tcb)
{
	TCBSYS_DeleteTask( tcb );
}

