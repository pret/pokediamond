
//============================================================================================
/**
 * @file		scr_kinomi.h
 * @brief
 * @author		tamada GAME FREAK inc.
 * @date		2006.05.23
 */
//============================================================================================

#ifndef	__SCR_KINOMI_H__
#define	__SCR_KINOMI_H__

//============================================================================================
//
//		�X�N���v�g�E�v���O�������ʂŎQ�Ƃ����`
//
//============================================================================================

#define	SEEDWATER_CMD_START		0
#define	SEEDWATER_CMD_END		1

//============================================================================================
//
//		�v���O�����ł̂ݎQ�Ƃ����`
//
//============================================================================================
//__ASM_NO_DEF_����`����Ă���ꍇ�A�A�Z���u���\�[�X�Ȃ̂ňȉ��͖����ɂ���
#ifndef	__ASM_NO_DEF_

#include "vm.h"

extern BOOL EvCmdSeedGetStatus(VM_MACHINE * core);
extern BOOL EvCmdSeedGetType(VM_MACHINE * core);
extern BOOL EvCmdSeedGetCompost(VM_MACHINE * core);
extern BOOL EvCmdSeedGetNutsCount(VM_MACHINE * core);
extern BOOL EvCmdSeedGetGroundStatus(VM_MACHINE * core);

extern BOOL EvCmdSeedSetCompost(VM_MACHINE * core);
extern BOOL EvCmdSeedSetNuts(VM_MACHINE * core);
extern BOOL EvCmdSeedSetWater(VM_MACHINE * core);
extern BOOL EvCmdSeedTakeNuts(VM_MACHINE * core);

#endif	//__ASM_NO_DEF_

#endif	//	__SCR_KINOMI_H__
