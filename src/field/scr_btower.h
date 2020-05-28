/**
 *	@file	scr_btower.h
 *	@brief	�o�g���^���[��p�X�N���v�g�R�}���h�\�[�X�w�b�_
 *	@author	Miyuki Iwasawa
 *	@date	06.05.23
 */

#ifndef __H_SCR_BTOWER_H__
#define __H_SCR_BTOWER_H__

//============================================================================================
//
//	�X�N���v�g������Q�Ƃ����`
//
//======================================================================================
#define BP_GIFT_NUM01	(26)
#define BP_GIFT_NUM02	(15)
//============================================================================================
//
//	�v���O�����ł̂ݎQ�Ƃ����`
//
//======================================================================================
//__ASM_NO_DEF_����`����Ă���ꍇ�A�A�Z���u���\�[�X�Ȃ̂ňȉ��͖����ɂ���
#ifndef	__ASM_NO_DEF_

#undef GLOBAL

#ifdef __SCR_BTOWER_H_GLOBAL
#define GLOBAL /***/
#else
#define GLOBAL	extern
#endif

//�o�g���^���[
GLOBAL BOOL EvCmdBattleTowerWorkClear(VM_MACHINE* core);
GLOBAL BOOL EvCmdBattleTowerWorkInit(VM_MACHINE* core);
GLOBAL BOOL EvCmdBattleTowerWorkRelease(VM_MACHINE* core);
GLOBAL BOOL EvCmdBattleTowerTools(VM_MACHINE* core);
GLOBAL BOOL EvCmdBattleTowerIsPrizeGet(VM_MACHINE* core);
GLOBAL BOOL EvCmdBattleTowerIsPrizemanSet(VM_MACHINE* core);
GLOBAL BOOL EvCmdBattleTowerSendBuf(VM_MACHINE* core);
GLOBAL BOOL EvCmdBattleTowerRecvBuf(VM_MACHINE* core);
GLOBAL BOOL EvCmdBattleTowerGetSevenPokeData(VM_MACHINE* core);
GLOBAL BOOL EvCmdBattleTowerGetLeaderRoomID(VM_MACHINE* core);
GLOBAL BOOL EvCmdBattleTowerIsLeaderDataExist(VM_MACHINE* core);
GLOBAL BOOL EvCmdBtlPointWinWrite(VM_MACHINE * core);
GLOBAL BOOL EvCmdBtlPointWinDel(VM_MACHINE * core);
GLOBAL BOOL EvCmdBtlPointWrite(VM_MACHINE * core);
GLOBAL BOOL EvCmdCheckBtlPoint( VM_MACHINE * core );
GLOBAL BOOL EvCmdAddBtlPoint( VM_MACHINE * core );
GLOBAL BOOL EvCmdSubBtlPoint( VM_MACHINE * core );
GLOBAL BOOL EvCmdCompBtlPoint( VM_MACHINE * core );
GLOBAL BOOL EvCmdGetBtlPointGift( VM_MACHINE * core );






#endif	/* __ASM_NO_DEF_ */

#endif	//__H_SCR_BTOWER_H__
