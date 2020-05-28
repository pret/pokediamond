//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		field_hideneff.h
 *	@brief		�t�B�[���h��`�Z�G�t�F�N�g
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
 *					����������
*/
//-----------------------------------------------------------------------------
GLOBAL FLDMAPFUNC_WORK* FLD_HIDENEFF_Iaigiri_Start( FIELDSYS_WORK* fsys );
GLOBAL void FLD_HIDENEFF_Iaigiri_End( FLDMAPFUNC_WORK* p_demo );
GLOBAL BOOL FLD_HIDENEFF_Iaigiri_EndCheck( FLDMAPFUNC_WORK* p_demo );

//-----------------------------------------------------------------------------
/**
 *					���킭����
*/
//-----------------------------------------------------------------------------
GLOBAL FLDMAPFUNC_WORK* FLD_HIDENEFF_Iwakudaki_Start( FIELDSYS_WORK* fsys );
GLOBAL FLDMAPFUNC_WORK* FLD_HIDENEFF_Iwakudaki_KuroganeL_Start( FIELDSYS_WORK* fsys );
GLOBAL void FLD_HIDENEFF_Iwakudaki_End( FLDMAPFUNC_WORK* p_demo );
GLOBAL BOOL FLD_HIDENEFF_Iwakudaki_EndCheck( FLDMAPFUNC_WORK* p_demo );


//-----------------------------------------------------------------------------
/**
 *					�����̂ڂ�		
*/
//-----------------------------------------------------------------------------
GLOBAL FLDMAPFUNC_WORK* FLD_HIDENEFF_Takinobori_Start( FIELDSYS_WORK* fsys );
GLOBAL void FLD_HIDENEFF_Takinobori_End( FLDMAPFUNC_WORK* p_demo );



//-----------------------------------------------------------------------------
/**
 *					���b�N�N���C��		
*/
//-----------------------------------------------------------------------------
GLOBAL FLDMAPFUNC_WORK* FLD_HIDENEFF_RockClime_Start( FIELDSYS_WORK* fsys );
GLOBAL void FLD_HIDENEFF_RockClime_End( FLDMAPFUNC_WORK* p_demo );


#undef	GLOBAL
#endif		// __FIELD_HIDENEFF_H__

