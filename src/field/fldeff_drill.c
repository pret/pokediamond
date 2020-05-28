//******************************************************************************
/**
 * 
 * @file	fldeff_drill.c
 * @brief	�t�B�[���hOBJ�@�h����
 * @author	k.ohno
 * @data	06.05.05
 *
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "field_effect.h"
#include "fieldobj.h"
#include "fldeff_drill.h"

#include "field_3dobj.h"

//==============================================================================
//	define
//==============================================================================

#define DRILL_DRAW_OFFSET (16*FX32_ONE)

#define DRILL_ON_FRAME (30)
#define DRILL_OFF_FRAME (DRILL_ON_FRAME+30)

//==============================================================================
//	typedef struct
//==============================================================================
//--------------------------------------------------------------
///	FE_DRILL_PTR��`
//--------------------------------------------------------------
typedef struct _TAG_FE_DRILL * FE_DRILL_PTR;

//--------------------------------------------------------------
///	FE_DRILL�\����
//--------------------------------------------------------------
typedef struct _TAG_FE_DRILL
{
	FE_SYS *fes;
	
	FLD_3DOBJ_MDL obj_mdl;
	FLD_3DOBJ_ANM obj_anm;
	NNSFndAllocator allocator;
}FE_DRILL;

#define FE_DRILL_SIZE (sizeof(FE_DRILL)) ///<FE_DRILL�T�C�Y

//--------------------------------------------------------------
///	DRILL_ADD_H�\����
//--------------------------------------------------------------
typedef struct
{
	FE_SYS *fes;					///<FE_SYS_PTR
	FE_DRILL_PTR drill;		///<FE_DRILL_PTR
}DRILL_ADD_H;

#define DRILL_ADD_H_SIZE (sizeof(DRILL_ADD_H)) ///<DRILL_ADD_H�T�C�Y

//--------------------------------------------------------------
///	DRILL_3DOBJ�\����
//--------------------------------------------------------------
typedef struct
{
	NNSG3dAnmObj*			pAnmObj;			// �A�j���[�V�����I�u�W�F
	NNSFndAllocator allocator;
	fx32 frame;
	FLD_3DOBJ obj;
}DRILL_3DOBJ;

#define DRILL_3DOBJ_SIZE (sizeof(DRILL_3DOBJ))

//--------------------------------------------------------------
///	DRILL_WORK�\����
//--------------------------------------------------------------
typedef struct
{
	DRILL_3DOBJ *ripobj;
	DRILL_ADD_H head;						///<�ǉ�����DRILL_ADD_H
}DRILL_WORK;

#define DRILL_WORK_SIZE (sizeof(DRILL_WORK))	///<DRILL_WORK�T�C�Y

//==============================================================================
//	�v���g�^�C�v
//==============================================================================
static void Drill_GraphicInit( FE_DRILL_PTR drill );
static void Drill_GraphicDelete( FE_DRILL_PTR drill );

static const EOA_H_NPP DATA_EoaH_Drill;

//==============================================================================
//	�h�����@�V�X�e��
//==============================================================================
//--------------------------------------------------------------
/**
 * �h����������
 * @param	fes		FE_SYS_PTR
 * @retval	FE_DRILL_PTR	FE_DRILL_PTR
 */
//--------------------------------------------------------------
void * FE_Drill_Init( FE_SYS *fes )
{
	FE_DRILL_PTR drill;
	
	drill = FE_AllocClearMemory( fes, FE_DRILL_SIZE, ALLOC_FR, 0 );
	drill->fes = fes;
	
	Drill_GraphicInit( drill );
	return( drill );
}

//--------------------------------------------------------------
/**
 * �h�����폜
 * @param	drill		FE_DRILL_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_Drill_Delete( void *work )
{
	FE_DRILL_PTR drill = work;
	Drill_GraphicDelete( drill );
	FE_FreeMemory( drill );
}

//==============================================================================
//	�h����	�p�[�c
//==============================================================================

//==============================================================================
//	�h�����@�O���t�B�b�N
//==============================================================================
//--------------------------------------------------------------
/**
 * �h���� �O���t�B�b�N������
 * @param	drill	FE_DRILL_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Drill_GraphicInit( FE_DRILL_PTR drill )
{
	FE_InitAllocator( drill->fes, &drill->allocator );
    FE_3DObjMdlLoad( drill->fes, &drill->obj_mdl, NARC_fldeff_ug_ef_drill_nsbmd, ALLOC_FR );
	FE_3DObjAnmLoad( drill->fes, &drill->obj_anm, &drill->obj_mdl, &drill->allocator,
		NARC_fldeff_ug_ef_drill_nsbtp, ALLOC_FR );
}

//--------------------------------------------------------------
/**
 * �h���� �O���t�B�b�N�폜
 * @param	drill	FE_DRILL_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Drill_GraphicDelete( FE_DRILL_PTR drill )
{
	FLD_3DObjMdlDelete( &drill->obj_mdl );	
	FLD_3DObjAnmDelete( &drill->obj_anm, &drill->allocator );	
}

//==============================================================================
//	�h����EOA
//==============================================================================
//--------------------------------------------------------------
/**
 * �h�����ǉ�
 * @param	fldobj	�ΏۂƂȂ�FIELD_OBJ_PTR
 * @param	gx		�\������O���b�hX���W
 * @param	gz		�\������O���b�hZ���W
 * @retval	EOA_PTR	���g��EOA_PTR
 */
//--------------------------------------------------------------
void FE_FldOBJDrillSet( FIELD_OBJ_PTR fldobj, int gx, int gy, int gz )
{
	int pri,param,dir;
	DRILL_ADD_H head;
	VecFx32 mtx;
	
	head.fes = FE_FieldOBJ_FE_SYS_Get( fldobj );
	head.drill = FE_EffectWorkGet( head.fes, FE_UG_DRILL );


    FieldOBJ_VecPosGet( fldobj, &mtx );
    dir = FieldOBJ_DirDispGet(fldobj);
    switch(dir){
      case DIR_UP:
        mtx.z -= DRILL_DRAW_OFFSET;
        break;
      case DIR_DOWN:
        mtx.z += DRILL_DRAW_OFFSET;
        break;
      case DIR_RIGHT:
        mtx.x += DRILL_DRAW_OFFSET;
        break;
      case DIR_LEFT:
        mtx.x -= DRILL_DRAW_OFFSET;
        break;
    }

    param = 0;
	pri = FieldOBJ_TCBPriGet( fldobj, FLDOBJ_TCBPRI_OFFS_AFTER );
	FE_EoaAddNpp( head.fes, &DATA_EoaH_Drill, &mtx, param, &head,pri );
}

//--------------------------------------------------------------
/**
 * EOA �h�����@������
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	int		TRUE=����I���BFALSE=�ُ�I��
 */
//--------------------------------------------------------------
static int EoaDrill_Init( EOA_PTR eoa, void *wk )
{
	VecFx32 mtx;
	DRILL_WORK *work = wk;
	DRILL_3DOBJ *ripobj;
	const DRILL_ADD_H *head = EOA_AddPtrGet( eoa );
	
	work->head = *head;
	ripobj = FE_AllocClearMemory( work->head.fes, DRILL_3DOBJ_SIZE, ALLOC_LO, 0 );
	work->ripobj = ripobj;
	
	FE_InitAllocator( work->head.fes, &ripobj->allocator );
	
	ripobj->pAnmObj = NNS_G3dAllocAnmObj( 
			&ripobj->allocator,
			work->head.drill->obj_anm.pOneResAnm,
			work->head.drill->obj_mdl.pModel );
	
	NNS_G3dAnmObjInit(
		ripobj->pAnmObj,
		work->head.drill->obj_anm.pOneResAnm,
		work->head.drill->obj_mdl.pModel,
		work->head.drill->obj_mdl.pMdlTex );
	
	FLD_3DObjInit( &ripobj->obj, &work->head.drill->obj_mdl );
	NNS_G3dRenderObjAddAnmObj( &ripobj->obj.render, ripobj->pAnmObj );
	
	EOA_MatrixGet( eoa, &mtx );
	FLD_3DObjSetMatrix( &ripobj->obj, mtx.x, mtx.y, mtx.z );
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA �h�����@�폜
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaDrill_Delete( EOA_PTR eoa, void *wk )
{
	DRILL_WORK *work = wk;
	DRILL_3DOBJ *ripobj = work->ripobj;
	NNS_G3dFreeAnmObj( &ripobj->allocator, ripobj->pAnmObj );
	FE_FreeMemory( ripobj );
}

//--------------------------------------------------------------
/**
 * EOA �h�����@����
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaDrill_Move( EOA_PTR eoa, void *wk )
{
	DRILL_WORK *work = wk;
	DRILL_3DOBJ *ripobj = work->ripobj;
	fx32 end_frame = NNS_G3dAnmObjGetNumFrame( ripobj->pAnmObj );
	
	ripobj->frame += FX32_ONE;
	
	if( ripobj->frame > end_frame ){
		FE_EoaDelete( eoa );
		return;
	}
	
	NNS_G3dAnmObjSetFrame( ripobj->pAnmObj, ripobj->frame );
}

//--------------------------------------------------------------
/**
 * EOA �h�����@�`��
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaDrill_Draw( EOA_PTR eoa, void *wk )
{
	DRILL_WORK *work = wk;
	DRILL_3DOBJ *ripobj = work->ripobj;
	FLD_3DObjDraw( &ripobj->obj );
}

//==============================================================================
//	data
//==============================================================================
//--------------------------------------------------------------
///	�h����EOA_H
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_Drill =
{
	DRILL_WORK_SIZE,
	EoaDrill_Init,
	EoaDrill_Delete,
	EoaDrill_Move,
	EoaDrill_Draw,
};

