//============================================================================================
/**
 * @file	poketch_prv.h
 * @bfief	ポケッチ　内部共有ヘッダ
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#ifndef _POKETCH_PRV_H_
#define _POKETCH_PRV_H_

#include "gflib\bg_system.h"
#include "field\poketch_data.h"
#include "field\field_common.h"

#include "poketch_button.h"

//====================================================
// タスクプライオリティ
//====================================================
enum {
	POKETCH_MAIN_TASKPRI = 0,
	POKETCH_APP_TASKPRI,
	POKETCH_GRAPHIC_TASKPRI,
	POKETCH_APP_GRAPHIC_TASKPRI,

	POKETCH_TAIL_TASKPRI,
};

//====================================================
// アプリケーションとメインの連絡用構造体
//====================================================
typedef struct _POKETCH_WORK   CONTACT_WORK;

//====================================================
// アプリケーション制御関数の型
//====================================================
typedef BOOL (*pAppInitProc)(void**, CONTACT_WORK*, GF_BGL_INI* bgl, u32 param);
typedef void (*pAppQuitProc)(void*);
typedef void (*pAppSaveProc)(void*);

//====================================================
// モニター領域の位置・サイズ
//====================================================
enum {
	POKETCH_MONITOR_SCRN_XORG = 2,
	POKETCH_MONITOR_SCRN_YORG = 2,
	POKETCH_MONITOR_SCRN_WIDTH = 24,
	POKETCH_MONITOR_SCRN_HEIGHT = 20,

	POKETCH_MONITOR_DOT_XORG = POKETCH_MONITOR_SCRN_XORG*8,
	POKETCH_MONITOR_DOT_YORG = POKETCH_MONITOR_SCRN_YORG*8,
	POKETCH_MONITOR_DOT_WIDTH = POKETCH_MONITOR_SCRN_WIDTH*8,
	POKETCH_MONITOR_DOT_HEIGHT = POKETCH_MONITOR_SCRN_HEIGHT*8,
	POKETCH_MONITOR_DOT_XEND = POKETCH_MONITOR_DOT_XORG+POKETCH_MONITOR_DOT_WIDTH-1,
	POKETCH_MONITOR_DOT_YEND = POKETCH_MONITOR_DOT_YORG+POKETCH_MONITOR_DOT_HEIGHT-1,

	POKETCH_MONITOR_CENTER_X = POKETCH_MONITOR_DOT_XORG + (POKETCH_MONITOR_DOT_WIDTH / 2),
	POKETCH_MONITOR_CENTER_Y = POKETCH_MONITOR_DOT_YORG + (POKETCH_MONITOR_DOT_HEIGHT / 2),
};

//====================================================
// 無効コマンドナンバー
//====================================================
#define CMD_NULL	(0xffffffff)


//====================================================
// 使用ヒープＩＤ
//====================================================
enum {
	POKETCH_MAIN_CTRL_HEAPID = HEAPID_POKETCH_MAIN,
	POKETCH_MAIN_VIEW_HEAPID = HEAPID_POKETCH_MAIN,
	POKETCH_APP_CTRL_HEAPID = HEAPID_POKETCH_APP,
	POKETCH_APP_VIEW_HEAPID = HEAPID_POKETCH_APP,
};



//====================================================
// 関数プロトタイプ
//====================================================
extern void PoketchSetAppProc( pAppInitProc initproc, pAppQuitProc quitproc);
extern void PoketchNoticeAppStart( CONTACT_WORK* wk );
extern void PoketchNoticeAppEnd( CONTACT_WORK* wk );
extern void PoketchSetAppSaveProc( pAppSaveProc saveproc, void* arg );
extern BOOL PoketchIsSleepMode( const CONTACT_WORK* wk );
extern BOOL PoketchGetPlayerMoveTrg( const CONTACT_WORK* wk );
extern BOOL PoketchGetPedometerUpdateFlag( const CONTACT_WORK* wk );
extern FIELDSYS_WORK* PoketchGetFieldSysWork( const CONTACT_WORK* wk );
extern POKETCH_DATA* PoketchGetSaveData( const CONTACT_WORK* wk );
extern SAVEDATA* PoketchGetSystemSaveData( const CONTACT_WORK* wk );
extern int PoketchGetBoardType( const CONTACT_WORK* wk );

extern void PoketchSePlay( u32 se );
extern void PoketchVoicePlay( u32 pokeno );
extern BOOL PoketchGetTPCont( u32* x, u32 *y );
extern BOOL PoketchGetTPTrg( u32* x, u32* y );
extern void PoketchButtonMainCall( const CONTACT_WORK* wk, POKETCH_BUTTON_MAN* man );


/*
extern BOOL  PoketchViewWorkCreate(POKETCH_VIEW_WORK** wk_ptr);
extern void PoketchViewSetCommand(u32 cmd, void *view_wk);
extern BOOL PoketchViewWaitCommand(u32 cmd);
extern BOOL PoketchViewWaitCommandAll(void);
*/


// アプリデータ保存用ワーク操作
extern void PoketchWork_Reset( void );
extern void PoketchWork_Save( u32 appNumber, const void* dat, u32 size );
extern BOOL PoketchWork_Load( u32 appNumber, void* buf, u32 size );
extern void PoketchWork_SaveFast( u32 appNumber, const void* dat, u32 size );
extern BOOL PoketchWork_LoadFast( u32 appNumber, void* buf, u32 size );


#endif

