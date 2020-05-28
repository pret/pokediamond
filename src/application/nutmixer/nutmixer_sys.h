/**
 *	@file	nutmixer_sys.h
 *	@brief	�i�b�c�~�L�T�[�@���[�J���w�b�_
 *	@author	Miyuki Iwasawa
 *	@date	06.04.06
 */

#ifndef __H_NUTMIXER_SYS_H__
#define __H_NUTMIXER_SYS_H__

#include "nutmixer_def.h"

typedef struct _NUTMIXER_WORK{
	int	heapID;		///<�q�[�vID
	u16	mem_num;	///<�����o�[��
	u16	comm_f:8;	///<���[�J�����ʐM��(�ʐM�Ȃ�TRUE)
	u16	endseq_f:4;	///<���C���I���t���O
	u16	view_f:4;	///<�`��֐��Ăяo���t���O

	int	itemno;	///<�I�񂾖؂̎��i���o�[
	BAG_CURSOR* bag_cursor;	// �o�b�O�J�[�\���ʒu�L���̈�
	
	NUTMIXER_PARAM* param;	///<���p���p�����[�^
	int		m_seq;		///<���C���R�}���h�V�[�P���X
	void*	app_wk;		///<�T�u�A�v�����[�N
	PROC	*proc;		///<�v���Z�X

	// �Q�[�����瑱���邩�擾�p
	BOOL game_next;		///< TRUE�Q�[���𑱂��� FALSE�I���

}NUTMIXER_WORK;

//���C���R�}���h�֐��^
typedef int (*NMIXER_MFUNC)(struct _NUTMIXER_WORK* mp,void* wk,int* seq);

///���C���V�[�P���X��`
typedef enum{
 NMSEQ_BAG_MAIN,
 NMSEQ_GAME_CALL,
 NMSEQ_GAME_WAIT,
 NMSEQ_GAME_END,
 NMSEQ_MAIN_END,	///<�I��
 NMSEQ_MAX,
};

//------------------------------------------------------------------
/**
 * @brief	�T�u�v���Z�X�Ăяo������
 * @param	proc	�T�u�v���Z�X�|�C���^��ێ����郏�[�N�ւ̃|�C���^
 */
//------------------------------------------------------------------
extern BOOL NutMixerProcCall(PROC ** proc);

#endif	//__H_NUTMIXER_SYS_H__

