//============================================================================================
/**
 * @file	wifi_note.h
 * @bfief	WIFI友達手帳
 * @author	k.ohno
 * @date	06.04.05
 */
//============================================================================================
#ifndef __WIFI_NOTE_H__
#define __WIFI_NOTE_H__

//============================================================================================
//	定義
//============================================================================================

//------------------------------------------------------
/**
 * WIFIともだちリストPROCパラメータ
 */
//------------------------------------------------------
typedef struct {
	SAVEDATA*  savedata;
}WIFINOTE_PROC_PARAM;


// プロセス定義データ
extern PROC_RESULT WifiNoteProc_Init( PROC * proc, int * seq );
extern PROC_RESULT WifiNoteProc_Main( PROC * proc, int * seq );
extern PROC_RESULT WifiNoteProc_End( PROC * proc, int * seq );

// 登録用プロセス定義データ
extern PROC_RESULT WifiNoteEntryProc_Init( PROC * proc, int * seq );

// ポインタ参照だけできるレコードコーナーワーク構造体
typedef struct _WIFINOTE_WORK WIFINOTE_WORK;	



#endif //__WIFI_NOTE_H__
