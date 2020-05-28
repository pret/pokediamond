//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		amaikaori_eff.h
 *	@brief		甘い香りエフェクト
 *	@author		tomoya takahashi
 *	@data		2006.05.01
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __AMAIKAORI_EFF_H__
#define __AMAIKAORI_EFF_H__

#include "fieldsys.h"
#include "fieldmap_func.h"

#undef GLOBAL
#ifdef	__AMAIKAORI_EFF_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------

#ifdef PM_DEBUG
//#define FIELD_AMAIKAORI_DEBUG	// デバック機能ON
#endif


//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	甘い香りイベント
//=====================================
typedef struct _EVENT_AMAIKAORI_EFF_WORK EVENT_AMAIKAORI_EFF_WORK;
GLOBAL u32 FLDMAP_Amaikaori_WorkSize( void );


//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	甘い香りイベント　制御部分	ワークのはきもします　確保は外
 *
 *	@param	event	イベントワーク
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL FLDMAP_AmaikaoriEvent( GMEVENT_CONTROL * event );






//-----------------------------------------------------------------------------
/**
 *	エフェクト関数
 */
//-----------------------------------------------------------------------------
GLOBAL FLDMAPFUNC_WORK* FLDMAP_Amaikaori_Start( FIELDSYS_WORK* fsys );
GLOBAL FLDMAPFUNC_WORK* FLDMAP_AmaikaoriEndEff_Start( FIELDSYS_WORK* fsys );
GLOBAL void FLDMAP_Amaikaori_End( FLDMAPFUNC_WORK* p_eff );
GLOBAL BOOL FLDMAP_Amaikaori_EndCheck( FLDMAPFUNC_WORK* p_eff );

#ifdef FIELD_AMAIKAORI_DEBUG
GLOBAL void AmaikaoriDebugMain( TCB_PTR tcb, void* p_work );
#endif


#undef	GLOBAL
#endif		// __AMAIKAORI_EFF_H__

