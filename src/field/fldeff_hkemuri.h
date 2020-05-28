//==============================================================================
/**
 * @file	fldeff_hkemuri.h
 * @brief	フィールドOBJ隠れ蓑土煙
 * @author	kagaya
 * @data	05.07.13
 */
//==============================================================================
#ifndef FLDEFF_HKEMURI_H_FILE
#define FLDEFF_HKEMURI_H_FILE

#include "eoa.h"
#include "fieldobj.h"
#include "field_effect.h"

//==============================================================================
//	typedef
//==============================================================================

//==============================================================================
//	外部参照
//==============================================================================
extern void * FE_HKemuri_Init( FE_SYS *fes );
extern void FE_HKemuri_Delete( void *work );

extern void FE_FldOBJHKemuri_Add( FIELD_OBJ_PTR fldobj );

#endif //FLDEFF_HKEMURI_H_FILE
