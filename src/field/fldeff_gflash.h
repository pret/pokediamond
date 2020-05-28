//==============================================================================
/**
 * @file	fldeff_gflash.h
 * @brief	�n��  ���܂����点��
 * @author	k.ohno
 * @data	06.05.05
 */
//==============================================================================
#ifndef FLDEFF_GFLASH_H_FILE
#define FLDEFF_GFLASH_H_FILE

#include "fieldobj.h"
#include "field_effect.h"

//==============================================================================
//	define
//==============================================================================

//==============================================================================
//	typedef
//==============================================================================
//==============================================================================
//	�O���Q��
//==============================================================================
extern void * FE_GFlash_Init( FE_SYS *fes );
extern void FE_GFlash_Delete( void *work );

extern void FE_FldOBJGFlashSet( FIELDSYS_WORK *fsys, int gx, int gz );

//extern void FE_FldOBJGFlashSet( FIELD_OBJ_PTR fldobj, int gx, int gy, int gz );

#endif //FLDEFF_GFLASH_H_FILE
