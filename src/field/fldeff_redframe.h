//==============================================================================
/**
 * @file	fldeff_redframe.h
 * @brief	�t�B�[���hOBJ�Ԙg
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
///	FE_REDFRAME_PTR�^
//--------------------------------------------------------------
typedef struct _TAG_FE_REDFRAME * FE_REDFRAME_PTR;

//==============================================================================
//	�O���Q��
//==============================================================================
extern void * FE_RedFrame_Init( FE_SYS *fes );
extern void FE_RedFrame_Delete( void *work );

extern EOA_PTR FE_FldOBJRedFrame_Add( FIELD_OBJ_PTR fldobj );

#endif //FLDEFF_REDFRAME_H_FILE
