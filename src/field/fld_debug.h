//===========================================================================
/**
 *	@file	fld_debug.h
 *	@brief	フィールドデバッグメニューリスト設定
 *
 */
//===========================================================================

#ifndef _FLD_DEBUG_H_
#define _FLD_DEBUG_H_


#include "field/field.h"

#ifdef	PM_DEBUG
#define DEBUG_BG1_PRINT		// フィールド画面でBG1面にデバッグ文字列を描画
#endif


//===========================================================================
/**
 *	@brief	フィールドデバッグメニューリスト設定
 *
 *	@param	none
 *	@retval	none
 */
//===========================================================================
extern void FieldDebugListSet(FIELDSYS_WORK * fsys);

//------------------------------------------------------------------
///	デバッグメニューからRTC操作呼び出し
//------------------------------------------------------------------
extern void EventSet_DebugRtcCotrol(FIELDSYS_WORK * fsys);

//------------------------------------------------------------------
///	デバッグメニューからテレビ内容表示呼び出し
//------------------------------------------------------------------
extern void EventSet_TVDebugInfo(FIELDSYS_WORK * fsys);

//===========================================================================
//===========================================================================

#ifndef DEBUG_BG1_PRINT

#define	DEBUG_INIT_TICK()		/* 何もしない */
#define	DEBUG_STORE_TICK(n)		/* 何もしない */
#define DEBUG_CLEAR_TICK()		/* 何もしない */

#define	DEBUG_VIEW_HOOK(n)		/* 何もしない */

#define	DEBUG_ENTRY_STRESSPRINT_TASK(fsys)		/* 何もしない */

#else

#define	DEBUG_INIT_TICK()		DEBUG_InitTick()
#define	DEBUG_STORE_TICK(n)		DEBUG_StoreTick(n)
#define DEBUG_CLEAR_TICK()		DEBUG_ClearMaxTick()

#define	DEBUG_VIEW_HOOK(n)		DebugStressDispHookSet(n)

#define	DEBUG_ENTRY_STRESSPRINT_TASK(fsys)	Debug_Entry_StressPrintTask(fsys)

extern void DebugBgPrint(GF_BGL_INI *ini,FIELDSYS_WORK *fsys);

extern void DEBUG_InitTick(void);
extern void DEBUG_StoreTick(int id);
extern void DEBUG_ClearMaxTick(void);
extern void DEBUG_PrintTickResult(GF_BGL_INI *ini,char * str, int x, int y);
extern void DebugStressDispHookSet(BOOL flag);

extern void DebugStressDispSet(const BOOL inFlg);

extern void Debug_EventSet_Tamada(FIELDSYS_WORK * fsys, int id);

extern void Debug_Entry_StressPrintTask(FIELDSYS_WORK * fsys);

extern void DEBUG_StoreTick2(int id);
extern void DEBUG_OS_PrintTick(void);

extern void DebugIchiCheckOn(FIELDSYS_WORK* fsys);

#endif	//DEBUG_BG1_PRINT


#endif	//_FLD_DEBUG_H_

