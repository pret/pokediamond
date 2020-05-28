//==============================================================================================
/**
 * @file	guinness_win.h
 * @brief	�M�l�X�E�B���h�E
 * @author	Satoshi Nohara
 * @date	2006.03.01
 */
//==============================================================================================
#ifndef GUINNESS_WIN_H
#define GUINNESS_WIN_H


//==============================================================================================
//
//	��`
//
//==============================================================================================
#define GUINNESS_WIN_B_CANCEL			(0xfffe)		//B�L�����Z��
//#define GUINNESS_WIN_LIST_END		(0xfffd)		//���ڂ̏I���R�[�h
#define GUINNESS_WIN_NOTHING			(0xeeee)		//�������̒l
#define	GUINNESS_WIN_LIST_LABEL		(0xfa)			//���X�g�g�p���Ƀ��x�����w�肷���`(�X�N���v�g�p)


//�A�Z���u����include����Ă���ꍇ�́A���̐錾�𖳎��ł���悤��ifndef�ň͂�ł���
#ifndef	__ASM_NO_DEF_


#include "common.h"
#include "gflib/msg_print.h"					//STRCODE
#include "system/msgdata.h"						//MSGDATA_MANAGER


//#define	SE_GUINNESS_WIN_START		(SEQ_SE_DP_CALL01)	//�J�n��	//�Ⴄ
//#define	SE_GUINNESS_WIN_START		(SEQ_SE_DP_PIKO2)	//�J�n��	//bank�Ⴄ�H
#define	SE_GUINNESS_WIN_START		(SEQ_SE_DP_UP)	//�J�n��


//==============================================================================================
//
//	�C�x���g�E�B���h�E���[�N�ւ̕s���S�^�|�C���^
//
//==============================================================================================
typedef	struct _GUINNESS_WIN_WORK GUINNESS_WIN_WORK;


//==============================================================================================
//
//	extern�錾
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	�C�x���g�[���R�}���h�F�M�l�X�E�B���h�E�Ăяo��
 *
 * @param	x			�E�B���h�E�\��X���W
 * @param	y			�E�B���h�E�\��X���W
 * @param	cursor		�J�[�\���ʒu
 * @param	cancel		B�L�����Z���t���O(TRUE=�L���AFALSE=����)
 * @param	wordset		WORDSET�^�̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
extern void EventCmd_GuinnessWin( GMEVENT_CONTROL* event, u8 x, u8 y, u8 cursor, u8 cancel, WORDSET* wordset );


#endif	__ASM_NO_DEF_


#endif	/* GUINNESS_WIN_H */



