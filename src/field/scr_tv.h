//============================================================================================
/**
 * @file	scr_tv.h
 * @date	2006.05.18
 * @author	tamada GAME FREAK inc.
 */
//============================================================================================
#ifndef	__SCR_TV_H__
#define	__SCR_TV_H__

//============================================================================================
//
//		�X�N���v�g�E�v���O�������ʂŎQ�Ƃ����`
//
//============================================================================================

//-----------------------------------------------------------------------------
//�ԑg�p�R�}���h��`
//-----------------------------------------------------------------------------
#define	TV_CMD_GET_STATUS			0
#define	TV_CMD_GET_PROG_MSG			1
#define	TV_CMD_SET_END_FLAG			2
#define	TV_CMD_GET_MSG				3
#define	TV_CMD_GET_CM_MSG			4
#define	TV_CMD_GET_DATA				5
#define TV_CMD_GET_DATA_TOTAL		6


//�ԑg��Ԓ�`
#define	TV_STATUS_PROGRAM_END		0			///<�ԑg�I�����
#define	TV_STATUS_TOPIC_END			1			///<�S�g�s�b�N���������
#define	TV_STATUS_START				2			///<�ԑg�J�n����
#define	TV_STATUS_ONAIR				3			///<�ԑg�������i2�ڈȍ~�j
#define	TV_STATUS_NO_TOPIC			4			///<�g�s�b�N�i�؂�

//�ԑg���ʃ��b�Z�[�WID
#define	TV_PROG_MSG_OPENING			0			///<�J�n���b�Z�[�W�i�����Ӂj
#define TV_PROG_MSG_INTRO			1			///<�����i��ԍŏ��A����ȍ~�j
#define	TV_PROG_MSG_ENDING			2			///<�I�����b�Z�[�W
#define	TV_PROG_MSG_PLEASE			3			///<�ԑg����Ă˃��b�Z�[�W

#define	TV_MINE_TOPIC				1			///<�����̃g�s�b�N
#define	TV_OTHER_TOPIC				0			///<���̑��̃g�s�b�N

#define	TV_NEW_TOPIC				0			///<�V�����g�s�b�N
#define	TV_OLD_TOPIC				1			///<�������Ƃ̂���g�s�b�N

//-----------------------------------------------------------------------------
//�C���^�r���[�p�R�}���h��`
//-----------------------------------------------------------------------------
#define	TV_INTERVIEW_CMD_GET_MSG	0
#define	TV_INTERVIEW_CMD_SET_TOPIC	1
#define	TV_INTERVIEW_CMD_CHK_TOPIC	2

//-----------------------------------------------------------------------------
//�A����������f�[�^�o�^�p�R�}���h��`
//-----------------------------------------------------------------------------
#define	TV_ENTRYPARK_CMD_INIT		0
#define	TV_ENTRYPARK_CMD_ITEM		1
#define	TV_ENTRYPARK_CMD_ACCE		2

//============================================================================================
//
//		�v���O�����ł̂ݎQ�Ƃ����`
//
//============================================================================================
//__ASM_NO_DEF_����`����Ă���ꍇ�A�A�Z���u���\�[�X�Ȃ̂ňȉ��͖����ɂ���
#ifndef	__ASM_NO_DEF_

#include "vm.h"

extern BOOL EvCmdBroadcastTV(VM_MACHINE * core);
extern BOOL EvCmdTVEntryWatchHideItem(VM_MACHINE * core);
extern BOOL EvCmdTVEntryWatchChangeName(VM_MACHINE * core);
extern BOOL EvCmdTVInterview(VM_MACHINE * core);
extern BOOL EvCmdTVInterviewerCheck(VM_MACHINE * core);
extern BOOL EvCmdTVEntryParkInfo(VM_MACHINE * core);

#endif	//__ASM_NO_DEF_

#endif	//__SCR_TV_H__
