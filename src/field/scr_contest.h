//============================================================================================
/**
 * @file	scr_contest.h
 * @bfief	スクリプトコマンド：コンテスト関連
 * @author	Satoshi Nohara
 * @date	06.06.23
 */
//============================================================================================
#ifndef SCR_CONTEST_H
#define SCR_CONTEST_H


//============================================================================================
//
//	プログラムでのみ参照する定義
//
//============================================================================================
//__ASM_NO_DEF_が定義されている場合、アセンブラソースなので以下は無効にする
#ifndef	__ASM_NO_DEF_
extern BOOL EvCmdConSioTimingSend( VM_MACHINE * core );
extern BOOL EvCmdConSioTimingCheck( VM_MACHINE * core );
extern BOOL EvCmdConSystemCreate( VM_MACHINE * core );
extern BOOL EvCmdConSystemExit( VM_MACHINE * core );
extern BOOL EvCmdConJudgeNameGet( VM_MACHINE * core );
extern BOOL EvCmdConBreederNameGet( VM_MACHINE * core );
extern BOOL EvCmdConNickNameGet( VM_MACHINE * core );
extern BOOL EvCmdConSioParamInitSet( VM_MACHINE * core );
extern BOOL EvCmdContestProc( VM_MACHINE * core );
extern BOOL EvCmdConRankNameGet( VM_MACHINE * core );
extern BOOL EvCmdConTypeNameGet( VM_MACHINE * core );
extern BOOL EvCmdConVictoryBreederNameGet( VM_MACHINE * core );
extern BOOL EvCmdConVictoryItemNoGet( VM_MACHINE * core );

extern BOOL EvCmdConVictoryNickNameGet( VM_MACHINE * core );
extern BOOL EvCmdConRankingCheck( VM_MACHINE * core );
extern BOOL EvCmdConVictoryEntryNoGet( VM_MACHINE * core );
extern BOOL EvCmdConMyEntryNoGet( VM_MACHINE * core );
extern BOOL EvCmdConObjCodeGet( VM_MACHINE * core );
extern BOOL EvCmdConPopularityGet( VM_MACHINE * core );
extern BOOL EvCmdConDeskModeGet( VM_MACHINE * core );
extern BOOL EvCmdConCameraFlashSet( VM_MACHINE * core );
extern BOOL EvCmdConCameraFlashCheck( VM_MACHINE * core );
extern BOOL EvCmdConHBlankStop( VM_MACHINE * core );
extern BOOL EvCmdConHBlankStart( VM_MACHINE * core );
extern BOOL EvCmdConNumTagSet( VM_MACHINE * core );
extern BOOL EvCmdConEndingSkipCheck( VM_MACHINE * core );
extern BOOL EvCmdConRecordDisp( VM_MACHINE * core );
extern BOOL EvCmdConEntryParamGet( VM_MACHINE * core );
extern BOOL EvCmdConMsgPrintFlagSet( VM_MACHINE * core );
extern BOOL EvCmdConMsgPrintFlagReset( VM_MACHINE * core );
extern BOOL EvCmdConHaveRibbonCheck( VM_MACHINE * core );
extern BOOL EvCmdConRibbonNameGet( VM_MACHINE * core );
extern BOOL EvCmdConAcceNoGet( VM_MACHINE * core );
#endif	/* __ASM_NO_DEF_ */


#endif	/* SCR_CONTEST_H */


