//==============================================================================
/**
 * @file	fldeff_redframe.h
 * @brief	フィールドOBJ赤枠
 * @author	kagaya
 * @data	05.07.13
 */
//==============================================================================
#ifndef FLDEFF_REDFRAME_H_FILE
#define FLDEFF_REDFRAME_H_FILE

#include "eoa.h"
#include "fieldobj.h"
#include "field_effect.h"

//==============================================================================
//	typedef
//==============================================================================
//--------------------------------------------------------------
///	FE_REDFRAME_PTR型
//--------------------------------------------------------------
typedef struct _TAG_FE_REDFRAME * FE_REDFRAME_PTR;

//==============================================================================
//	外部参照
//==============================================================================
extern void * FE_RedFrame_Init( FE_SYS *fes );
extern void FE_RedFrame_Delete( void *work );

extern EOA_PTR FE_FldOBJRedFrame_Add( FIELD_OBJ_PTR fldobj );

#endif //FLDEFF_REDFRAME_H_FILE
