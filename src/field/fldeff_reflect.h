//==============================================================================
/**
 * @file	fldeff_reflect.h
 * @brief	�t�B�[���hOBJ�f�肱��
 * @author	kagaya
 * @data	05.07.13
 */
//==============================================================================
#ifndef FLDEFF_REFLECT_H_FILE
#define FLDEFF_REFLECT_H_FILE

#include "eoa.h"
#include "fieldobj.h"
#include "field_effect.h"

//==============================================================================
//	typedef
//==============================================================================
//--------------------------------------------------------------
///	REFTYPE �f�荞�݃^�C�v
//--------------------------------------------------------------
typedef enum
{
	REFTYPE_POOL = 0,
	REFTYPE_POND,
	REFTYPE_MAX,
}REFTYPE;

//==============================================================================
//	�O���Q��
//==============================================================================
extern void * FE_Reflect_Init( FE_SYS *fes );
extern void FE_Reflect_Delete( void *work );

extern void FE_FldOBJReflect_Add( FIELD_OBJ_PTR fldobj, REFTYPE type );

extern EOA_PTR FE_EoaReflectSole_Add( FE_SYS *fes,
	const BLACT_HEADER *act_head, CONST_BLACT_WORK_PTR act, const VecFx32 *mtx,
	REFTYPE type, int pri );

#endif //FLDEFF_REFLECT_H_FILE
