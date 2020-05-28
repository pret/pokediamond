//============================================================================================
/**
 * @file	b_app_tool.h
 * @brief	戦闘用アプリ共通処理
 * @author	Hiroyuki Nakamura
 * @date	06.03.30
 */
//============================================================================================
#ifndef B_APP_TOOL_H
#define B_APP_TOOL_H
#undef GLOBAL
#ifdef B_APP_TOOL_H_GLOBAL
#define GLOBAL	/*	*/
#else
#define GLOBAL	extern
#endif


#include "battle_cursor.h"


//============================================================================================
//	定数定義
//============================================================================================
typedef struct _BAPP_CURSOR_MVWK	BAPP_CURSOR_MVWK;

#define	BAPP_CMV_CANCEL		( 0xfffffffe )
#define	BAPP_CMV_NONE		( 0xffffffff )

#define	BAPP_CMV_RETBIT		( 0x80 )		// カーソル移動で前回の位置へ戻る


//============================================================================================
//	プロトタイプ宣言
//============================================================================================

GLOBAL BAPP_CURSOR_MVWK * BAPP_CursorMoveWorkAlloc( u32 heap );
GLOBAL void BAPP_CursorMoveWorkFree( BAPP_CURSOR_MVWK * wk );

GLOBAL BCURSOR_PTR BAPP_CursorMvWkGetBCURSOR_PTR( BAPP_CURSOR_MVWK * wk );
GLOBAL u8 BAPP_CursorMvWkGetPos( BAPP_CURSOR_MVWK * wk );
GLOBAL u8 BAPP_CursorMvWkGetFlag( BAPP_CURSOR_MVWK * wk );

GLOBAL void BAPP_CursorMvWkSetFlag( BAPP_CURSOR_MVWK * wk, u8 flg );
GLOBAL void BAPP_CursorMvWkSetBCURSOR_PTR( BAPP_CURSOR_MVWK * wk, BCURSOR_PTR cur );
GLOBAL void BAPP_CursorMvWkSetPos( BAPP_CURSOR_MVWK * wk, u8 pos );
GLOBAL void BAPP_CursorMvWkPosInit( BAPP_CURSOR_MVWK * wk );
GLOBAL void BAPP_CursorMvWkSetPoint( BAPP_CURSOR_MVWK * wk, const POINTER_WORK * pwk );
GLOBAL void BAPP_CursorMvWkSetMvTbl( BAPP_CURSOR_MVWK * wk, u32 mv_tbl );

GLOBAL u32 BAPP_CursorMove( BAPP_CURSOR_MVWK * wk );


#undef GLOBAL
#endif	/* B_APP_TOOL_H */
