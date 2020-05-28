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
//		スクリプト・プログラム共通で参照する定義
//
//============================================================================================

//グループコマンド用定義
#define	GROUP_COMMAND_EXIST_CHECK		0
#define	GROUP_COMMAND_ENTRY_CHECK		1
#define	GROUP_COMMAND_GET_GROUP_NAME	2
#define GROUP_COMMAND_GET_LEADER_NAME	3
#define	GROUP_COMMAND_NAMEIN			4
#define	GROUP_COMMAND_ENTRY				5
#define	GROUP_COMMAND_MAKEGROUP			6

//グループID指定定義
#define	GROUP_ID_MINE			0
#define	GROUP_ID_MYUSE			1
#define	GROUP_ID_DATA0			2
#define	GROUP_ID_DATA1			3
#define	GROUP_ID_DATA2			4
#define	GROUP_ID_DATA3			5

#define	GROUP_ID_MAX			6


//============================================================================================
//
//		プログラムでのみ参照する定義
//
//============================================================================================
//__ASM_NO_DEF_が定義されている場合、アセンブラソースなので以下は無効にする
#ifndef	__ASM_NO_DEF_

#include "vm.h"

extern BOOL EvCmdRandomGroup(VM_MACHINE * core);

#endif	//__ASM_NO_DEF_

#endif	/* __SCR_GROUP_H__ */
