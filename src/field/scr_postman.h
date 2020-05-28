
//============================================================================================
/**
 * @file		scr_postman.h
 * @brief
 * @author		tamada GAME FREAK inc.  --> k.ohno
 * @date		2006.05.26
 */
//============================================================================================

#ifndef	__SCR_POSTMAN_H__
#define	__SCR_POSTMAN_H__

//============================================================================================
//
//		�X�N���v�g�E�v���O�������ʂŎQ�Ƃ����`
//
//============================================================================================

#define	POSTMAN_CMD_INIT		        0
#define	POSTMAN_CMD_PRESENT_CHECK		1
#define	POSTMAN_CMD_GET_PRESENT_ID		2
#define	POSTMAN_CMD_RECEIVE_CHECK		3
#define POSTMAN_CMD_RECEIVE_PRESENT		4
#define	POSTMAN_CMD_ENABLE_MSG			5
#define	POSTMAN_CMD_DISABLE_MSG			6
#define	POSTMAN_CMD_END		            7
#define	POSTMAN_CMD_SAVE_END		    8

#define	MP_ID_NOTHING			0
#define	MP_ID_POKEMON			1
#define	MP_ID_TAMAGO			2
#define	MP_ID_ITEM				3
#define	MP_ID_REGULATION		4
#define	MP_ID_GOODS				5
#define	MP_ID_ACCESSORIES		6
#define	MP_ID_RANGER			7
#define	MP_ID_MEMBERSCARD		8
#define	MP_ID_OOKIDOMAIL		9
#define	MP_ID_TENKAINOHUE		10

#define POKEMON_RND_FULL_RANDOM		0x00000000	// ���S�����_���Ōő̗���������
#define POKEMON_RND_EXCEPT_RARE		0x00000001	// ���A�ȊO�̌ő̗���


//============================================================================================
//
//		�v���O�����ł̂ݎQ�Ƃ����`
//
//============================================================================================
//__ASM_NO_DEF_����`����Ă���ꍇ�A�A�Z���u���\�[�X�Ȃ̂ňȉ��͖����ɂ���
#ifndef	__ASM_NO_DEF_

#include "vm.h"

extern BOOL EvCmdMysteryPostMan(VM_MACHINE * core);

#endif	//__ASM_NO_DEF_

#endif	/* __SCR_POSTMAN_H__ */
