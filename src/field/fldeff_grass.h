//==============================================================================
/**
 * @file	fldeff_grass.h
 * @brief	�t�B�[���hOBJ��
 * @author	kagaya
 * @data	05.07.13
 */
//==============================================================================
#ifndef FLDEFF_GRASS_H_FILE
#define FLDEFF_GRASS_H_FILE

#include "eoa.h"
#include "fieldobj.h"
#include "field_effect.h"

//==============================================================================
//	define
//==============================================================================
//--------------------------------------------------------------
///	�G���J�E���g�����
//--------------------------------------------------------------
typedef enum
{
	FE_GRASS_TYPE_ENCOUNT_SMALL = 0,
	FE_GRASS_TYPE_ENCOUNT_BIG,
	FE_GRASS_TYPE_ENCOUNT_KIRAKIRA,
}FE_GRASS_TYPE;
		
//==============================================================================
//	typedef
//==============================================================================
//--------------------------------------------------------------
///	FE_GRASS_PTR�^
//--------------------------------------------------------------
typedef struct _TAG_FE_GRASS * FE_GRASS_PTR;

//==============================================================================
//	�O���Q��
//==============================================================================
extern void * FE_Grass_Init( FE_SYS *fes );
extern void FE_Grass_Delete( void *work );
extern void FE_FldOBJGrass_Add( FIELD_OBJ_PTR fldobj, int shake );

//�n����
extern EOA_PTR FE_CommTrapGrass_Add( FIELDSYS_WORK *fsys, int x, int z );
extern int FE_CommTrapGrass_AnimeCheck( EOA_PTR eoa );

//��ꑐ
extern EOA_PTR FE_EncGrass_Add( FIELDSYS_WORK *fsys, int x, int z, FE_GRASS_TYPE type );
extern int FE_EncGrass_AnimeCheck( EOA_PTR eoa );

#endif //FLDEFF_GRASS_H_FILE
