/**
 *	@file	scr_btower.h
 *	@brief	バトルタワー専用スクリプトコマンドソースヘッダ
 *	@author	Miyuki Iwasawa
 *	@date	06.05.23
 */

#ifndef __H_SCR_BTOWER_H__
#define __H_SCR_BTOWER_H__

//============================================================================================
//
//	スクリプトからも参照する定義
//
//======================================================================================
#define BP_GIFT_NUM01	(26)
#define BP_GIFT_NUM02	(15)
//============================================================================================
//
//	プログラムでのみ参照する定義
//
//======================================================================================
//__ASM_NO_DEF_が定義されている場合、アセンブラソースなので以下は無効にする
#ifndef	__ASM_NO_DEF_

#undef GLOBAL

#ifdef __SCR_BTOWER_H_GLOBAL
#define GLOBAL /***/
#else
#define GLOBAL	extern
#endif

//バトルタワー
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
