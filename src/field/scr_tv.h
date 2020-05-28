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
//		スクリプト・プログラム共通で参照する定義
//
//============================================================================================

//-----------------------------------------------------------------------------
//番組用コマンド定義
//-----------------------------------------------------------------------------
#define	TV_CMD_GET_STATUS			0
#define	TV_CMD_GET_PROG_MSG			1
#define	TV_CMD_SET_END_FLAG			2
#define	TV_CMD_GET_MSG				3
#define	TV_CMD_GET_CM_MSG			4
#define	TV_CMD_GET_DATA				5
#define TV_CMD_GET_DATA_TOTAL		6


//番組状態定義
#define	TV_STATUS_PROGRAM_END		0			///<番組終了状態
#define	TV_STATUS_TOPIC_END			1			///<４つトピックを放送した
#define	TV_STATUS_START				2			///<番組開始直後
#define	TV_STATUS_ONAIR				3			///<番組放送中（2つ目以降）
#define	TV_STATUS_NO_TOPIC			4			///<トピック品切れ

//番組共通メッセージID
#define	TV_PROG_MSG_OPENING			0			///<開始メッセージ（朝昼晩）
#define TV_PROG_MSG_INTRO			1			///<導入（一番最初、それ以降）
#define	TV_PROG_MSG_ENDING			2			///<終了メッセージ
#define	TV_PROG_MSG_PLEASE			3			///<番組作ってねメッセージ

#define	TV_MINE_TOPIC				1			///<自分のトピック
#define	TV_OTHER_TOPIC				0			///<その他のトピック

#define	TV_NEW_TOPIC				0			///<新しいトピック
#define	TV_OLD_TOPIC				1			///<見たことのあるトピック

//-----------------------------------------------------------------------------
//インタビュー用コマンド定義
//-----------------------------------------------------------------------------
#define	TV_INTERVIEW_CMD_GET_MSG	0
#define	TV_INTERVIEW_CMD_SET_TOPIC	1
#define	TV_INTERVIEW_CMD_CHK_TOPIC	2

//-----------------------------------------------------------------------------
//連れ歩き公園データ登録用コマンド定義
//-----------------------------------------------------------------------------
#define	TV_ENTRYPARK_CMD_INIT		0
#define	TV_ENTRYPARK_CMD_ITEM		1
#define	TV_ENTRYPARK_CMD_ACCE		2

//============================================================================================
//
//		プログラムでのみ参照する定義
//
//============================================================================================
//__ASM_NO_DEF_が定義されている場合、アセンブラソースなので以下は無効にする
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
