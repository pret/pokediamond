//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		field_hideneff.h
 *	@brief		フィールド秘伝技エフェクト
 *	@author		tomoya takahashi
 *	@data		2006.06.26
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __FIELD_HIDENEFF_H__
#define __FIELD_HIDENEFF_H__

#include "fieldmap_func.h"

#undef GLOBAL
#ifdef	__FIELD_HIDENEFF_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					いあいぎり
*/
//-----------------------------------------------------------------------------
GLOBAL FLDMAPFUNC_WORK* FLD_HIDENEFF_Iaigiri_Start( FIELDSYS_WORK* fsys );
GLOBAL void FLD_HIDENEFF_Iaigiri_End( FLDMAPFUNC_WORK* p_demo );
GLOBAL BOOL FLD_HIDENEFF_Iaigiri_EndCheck( FLDMAPFUNC_WORK* p_demo );

//-----------------------------------------------------------------------------
/**
 *					いわくだき
*/
//-----------------------------------------------------------------------------
GLOBAL FLDMAPFUNC_WORK* FLD_HIDENEFF_Iwakudaki_Start( FIELDSYS_WORK* fsys );
GLOBAL FLDMAPFUNC_WORK* FLD_HIDENEFF_Iwakudaki_KuroganeL_Start( FIELDSYS_WORK* fsys );
GLOBAL void FLD_HIDENEFF_Iwakudaki_End( FLDMAPFUNC_WORK* p_demo );
GLOBAL BOOL FLD_HIDENEFF_Iwakudaki_EndCheck( FLDMAPFUNC_WORK* p_demo );


//-----------------------------------------------------------------------------
/**
 *					たきのぼり		
*/
//-----------------------------------------------------------------------------
GLOBAL FLDMAPFUNC_WORK* FLD_HIDENEFF_Takinobori_Start( FIELDSYS_WORK* fsys );
GLOBAL void FLD_HIDENEFF_Takinobori_End( FLDMAPFUNC_WORK* p_demo );



//-----------------------------------------------------------------------------
/**
 *					ロッククライム		
*/
//-----------------------------------------------------------------------------
GLOBAL FLDMAPFUNC_WORK* FLD_HIDENEFF_RockClime_Start( FIELDSYS_WORK* fsys );
GLOBAL void FLD_HIDENEFF_RockClime_End( FLDMAPFUNC_WORK* p_demo );


#undef	GLOBAL
#endif		// __FIELD_HIDENEFF_H__

