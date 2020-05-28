//==============================================================================
/**
 * @file	fldeff_kemuri.h
 * @brief	フィールドOBJ土煙
 * @author	kagaya
 * @data	05.07.13
 */
//==============================================================================
#ifndef FLDEFF_KEMURI_H_FILE
#define FLDEFF_KEMURI_H_FILE

#include "eoa.h"
#include "fieldobj.h"
#include "field_effect.h"

//==============================================================================
//	typedef
//==============================================================================

//==============================================================================
//	外部参照
//==============================================================================
extern void * FE_Kemuri_Init( FE_SYS *fes );
extern void FE_Kemuri_Delete( void *work );

extern void FE_FldOBJKemuri_Add( FIELD_OBJ_PTR fldobj );

#endif //FLDEFF_KEMURI_H_FILE
