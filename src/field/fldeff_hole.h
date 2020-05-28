//==============================================================================
/**
 * @file	fldeff_hole.h
 * @brief	フィールドOBJ あな
 * @author	k.ohno
 * @data	05.11.29
 */
//==============================================================================
#ifndef FLDEFF_HOLE_H_FILE
#define FLDEFF_HOLE_H_FILE

#include "fieldobj.h"
#include "field_effect.h"

//==============================================================================
//	typedef
//==============================================================================

//==============================================================================
//	外部参照
//==============================================================================
extern void * FE_Hole_Init( FE_SYS *fes );
extern void FE_Hole_Delete( void *work );

extern EOA_PTR FE_Hole_Add( FIELDSYS_WORK *fsys, int x, int z , int scale,int modelNo);
extern EOA_PTR FE_ScaleHole_Add(  FIELDSYS_WORK *fsys, int x, int z, int scale,int modelNo);

extern int FE_Hole_AnimeCheck( EOA_PTR eoa );

#endif //FLDEFF_HOLE_H_FILE
