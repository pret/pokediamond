//==============================================================================
/**
 * @file	fldeff_elight.h
 * @brief	フィールドOBJ電灯
 * @author	kagaya
 * @data	05.07.13
 */
//==============================================================================
#ifndef FLDEFF_ELIGHT_H_FILE
#define FLDEFF_ELIGHT_H_FILE

#include "eoa.h"
#include "fieldobj.h"
#include "field_effect.h"

//==============================================================================
//	typedef
//==============================================================================
//--------------------------------------------------------------
///	FE_ELIGHT_PTR
//--------------------------------------------------------------
typedef struct _TAG_FE_ELIGHT * FE_ELIGHT_PTR;

//==============================================================================
//	外部参照
//==============================================================================
extern FE_ELIGHT_PTR FE_ELight_Init( FE_SYS_PTR fes, int heap_id );
extern void FE_ELight_Delete( FE_ELIGHT_PTR el );

extern EOA_PTR FE_FldOBJELight_Add( FIELD_OBJ_PTR fldobj );

#endif //FLDEFF_ELIGHT_H
