//==============================================================================
/**
 * @file	fldeff_trap.h
 * @brief	フィールドOBJ 罠
 * @author	k.ohno
 * @data	05.11.29
 */
//==============================================================================
#ifndef FLDEFF_TRAP_H_FILE
#define FLDEFF_TRAP_H_FILE

#include "fieldobj.h"
#include "field_effect.h"

//==============================================================================
//	typedef
//==============================================================================

//==============================================================================
//	外部参照
//==============================================================================
extern void * FE_Trap_Init( FE_SYS *fes );
extern void FE_Trap_Delete( void *work );

extern EOA_PTR FE_Trap_Add( FIELDSYS_WORK *fsys, int x, int z , int liveTime );

extern int FE_Trap_AnimeCheck( EOA_PTR eoa );

#endif //FLDEFF_TRAP_H_FILE
