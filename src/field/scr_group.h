//============================================================================================
/**
 * @file		scr_group.h
 * @brief
 * @author		tamada GAME FREAK inc.
 * @date		2006.05.15
 */
//============================================================================================

#ifndef	__SCR_GROUP_H__
#define	__SCR_GROUP_H__

//============================================================================================
//
//		�X�N���v�g�E�v���O�������ʂŎQ�Ƃ����`
//
//============================================================================================

//�O���[�v�R�}���h�p��`
#define	GROUP_COMMAND_EXIST_CHECK		0
#define	GROUP_COMMAND_ENTRY_CHECK		1
#define	GROUP_COMMAND_GET_GROUP_NAME	2
#define GROUP_COMMAND_GET_LEADER_NAME	3
#define	GROUP_COMMAND_NAMEIN			4
#define	GROUP_COMMAND_ENTRY				5
#define	GROUP_COMMAND_MAKEGROUP			6

//�O���[�vID�w���`
#define	GROUP_ID_MINE			0
#define	GROUP_ID_MYUSE			1
#define	GROUP_ID_DATA0			2
#define	GROUP_ID_DATA1			3
#define	GROUP_ID_DATA2			4
#define	GROUP_ID_DATA3			5

#define	GROUP_ID_MAX			6


//============================================================================================
//
//		�v���O�����ł̂ݎQ�Ƃ����`
//
//============================================================================================
//__ASM_NO_DEF_����`����Ă���ꍇ�A�A�Z���u���\�[�X�Ȃ̂ňȉ��͖����ɂ���
#ifndef	__ASM_NO_DEF_

#include "vm.h"

extern BOOL EvCmdRandomGroup(VM_MACHINE * core);

#endif	//__ASM_NO_DEF_

#endif	/* __SCR_GROUP_H__ */
