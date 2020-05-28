//==============================================================================
/**
 * @file	fldeff_footmark.h
 * @brief	フィールドOBJ足跡
 * @author	kagaya
 * @data	05.07.13
 */
//==============================================================================
#ifndef FLDEFF_FOOTMARK_H_FILE
#define FLDEFF_FOOTMARK_H_FILE

#include "fieldobj.h"
#include "field_effect.h"

//==============================================================================
//	define
//==============================================================================

//==============================================================================
//	typedef
//==============================================================================

//==============================================================================
//	外部参照
//==============================================================================
extern void * FE_FootMark_Init( FE_SYS *fes );
extern void FE_FootMark_Delete( void *work );

extern EOA_PTR FE_FldOBJFootMarkNormal_Add( CONST_FIELD_OBJ_PTR fldobj );
extern EOA_PTR FE_FldOBJFootMarkCycle_Add( CONST_FIELD_OBJ_PTR fldobj );
extern EOA_PTR FE_FldOBJFootMarkSnow_Add( CONST_FIELD_OBJ_PTR fldobj );
extern EOA_PTR FE_FldOBJFootMarkSnowDeep_Add( CONST_FIELD_OBJ_PTR fldobj );

#endif //FLDEFF_FOOTMARK_H_FILE
