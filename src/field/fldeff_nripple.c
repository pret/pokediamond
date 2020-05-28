//******************************************************************************
/**
 * 
 * @file	fldeff_nripple.c
 * @brief	�t�B�[���hOBJ�@���n���g��
 * @author	kagaya
 * @data	05.07.13
 *
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "field_effect.h"
#include "fieldobj.h"
#include "fldeff_nripple.h"

#include "field_3dobj.h"

//==============================================================================
//	define
//==============================================================================
//#define DEBUG_NRIPPLE_WRITE_OFF	//��`�ŏ��g��`��OFF

#define NRIPPLE_DRAW_Y_OFFSET (-FX32_ONE*(8))		///<���g��`��I�t�Z�b�gY��
#define NRIPPLE_DRAW_Z_OFFSET (FX32_ONE*(0))

#define NRIPPLE_ON_FRAME (30)
#define NRIPPLE_OFF_FRAME (RIPPLE_ON_FRAME+30)

//==============================================================================
//	typedef struct
//==============================================================================
//--------------------------------------------------------------
///	FE_NRIPPLE�^
//--------------------------------------------------------------
typedef struct _TAG_FE_NRIPPLE * FE_NRIPPLE_PTR;

//--------------------------------------------------------------
///	FE_NRIPPLE�\����
//--------------------------------------------------------------
typedef struct _TAG_FE_NRIPPLE
{
	FE_SYS *fes;
	
	FLD_3DOBJ_MDL obj_mdl;
	FLD_3DOBJ_ANM obj_anm;
	NNSFndAllocator allocator;
}FE_NRIPPLE;

#define FE_NRIPPLE_SIZE (sizeof(FE_NRIPPLE)) ///<FE_NRIPPLE�T�C�Y

//--------------------------------------------------------------
///	NRIPPLE_ADD_H�\����
//--------------------------------------------------------------
typedef struct
{
	FE_SYS *fes;					///<FE_SYS_PTR
	FE_NRIPPLE_PTR ripple;		///<FE_RIPPLE_PTR
}NRIPPLE_ADD_H;

#define NRIPPLE_ADD_H_SIZE (sizeof(RIPPLE_ADD_H)) ///<RIPPLE_ADD_H�T�C�Y

//--------------------------------------------------------------
///	NRIPPLE_3DOBJ�\����
//--------------------------------------------------------------
typedef struct
{
	NNSG3dAnmObj*			pAnmObj;			// �A�j���[�V�����I�u�W�F
	NNSFndAllocator allocator;
	fx32 frame;
	FLD_3DOBJ obj;
}NRIPPLE_3DOBJ;

#define NRIPPLE_3DOBJ_SIZE (sizeof(NRIPPLE_3DOBJ))

//--------------------------------------------------------------
///	NRIPPLE_WORK�\����
//--------------------------------------------------------------
typedef struct
{
	NRIPPLE_3DOBJ *ripobj;
	NRIPPLE_ADD_H head;						///<�ǉ�����RIPPLE_ADD_H
}NRIPPLE_WORK;

#define NRIPPLE_WORK_SIZE (sizeof(NRIPPLE_WORK))	///<NRIPPLE_WORK�T�C�Y

//==============================================================================
//	�v���g�^�C�v
//==============================================================================
static void NRipple_GraphicInit( FE_NRIPPLE_PTR ripple );
static void NRipple_GraphicDelete( FE_NRIPPLE_PTR ripple );

static const EOA_H_NPP DATA_EoaH_NRipple;

//==============================================================================
//	���g��@�V�X�e��
//==============================================================================
//--------------------------------------------------------------
/**
 * ���g�䏉����
 * @param	fes		FE_SYS_PTR
 * @retval	FE_NRIPPLE_PTR	FE_RIPPLE_PTR
 */
//--------------------------------------------------------------
void * FE_NRipple_Init( FE_SYS *fes )
{
	FE_NRIPPLE_PTR ripple;
	
	ripple = FE_AllocClearMemory( fes, FE_NRIPPLE_SIZE, ALLOC_FR, 0 );
	ripple->fes = fes;
	
	NRipple_GraphicInit( ripple );
	return( ripple );
}

//--------------------------------------------------------------
/**
 * ���g��폜
 * @param	ripple		FE_NRIPPLE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_NRipple_Delete( void *work )
{
	FE_NRIPPLE_PTR ripple = work;
	NRipple_GraphicDelete( ripple );
	FE_FreeMemory( ripple );
}

//==============================================================================
//	���g��	�p�[�c
//==============================================================================

//==============================================================================
//	���g��@�O���t�B�b�N
//==============================================================================
//--------------------------------------------------------------
/**
 * ���g�� �O���t�B�b�N������
 * @param	ripple	FE_NRIPPLE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void NRipple_GraphicInit( FE_NRIPPLE_PTR ripple )
{
	FE_InitAllocator( ripple->fes, &ripple->allocator );
	FE_3DObjMdlLoad( ripple->fes, &ripple->obj_mdl, NARC_fldeff_numa_ripple_nsbmd, ALLOC_FR );
	FE_3DObjAnmLoad( ripple->fes, &ripple->obj_anm, &ripple->obj_mdl, &ripple->allocator,
		NARC_fldeff_numa_ripple_nsbtp, ALLOC_FR );
}

//--------------------------------------------------------------
/**
 * ���g�� �O���t�B�b�N�폜
 * @param	ripple	FE_NRIPPLE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void NRipple_GraphicDelete( FE_NRIPPLE_PTR ripple )
{
	FLD_3DObjMdlDelete( &ripple->obj_mdl );	
	FLD_3DObjAnmDelete( &ripple->obj_anm, &ripple->allocator );	
}

//==============================================================================
//	���g��@EOA
//==============================================================================
//--------------------------------------------------------------
/**
 * ���g��ǉ�
 * @param	fldobj	�ΏۂƂȂ�FIELD_OBJ_PTR
 * @param	gx		�\������O���b�hX���W
 * @param	gz		�\������O���b�hZ���W
 * @retval	EOA_PTR	���g��EOA_PTR
 */
//--------------------------------------------------------------
void FE_FldOBJNRippleSet( FIELD_OBJ_PTR fldobj, int gx, int gy, int gz )
{
	int pri,param;
	NRIPPLE_ADD_H head;
	VecFx32 mtx;
	
	head.fes = FE_FieldOBJ_FE_SYS_Get( fldobj );
	head.ripple = FE_EffectWorkGet( head.fes, FE_FLD_NRIPPLE );
	
	FieldOBJTool_GridCenterPosGet( gx, gz, &mtx );
	mtx.z += H_GRID_SIZE( gy ) + NRIPPLE_DRAW_Z_OFFSET;
	
	mtx.y = H_GRID_SIZE_FX32( FieldOBJ_OldPosGY_Get(fldobj) ) + NRIPPLE_DRAW_Y_OFFSET;
	
	param = 0;
	pri = FieldOBJ_TCBPriGet( fldobj, FLDOBJ_TCBPRI_OFFS_AFTER );
	FE_EoaAddNpp( head.fes, &DATA_EoaH_NRipple, &mtx, param, &head,pri );
}

//--------------------------------------------------------------
/**
 * EOA ���g��@������
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	int		TRUE=����I���BFALSE=�ُ�I��
 */
//--------------------------------------------------------------
static int EoaNRipple_Init( EOA_PTR eoa, void *wk )
{
	VecFx32 mtx;
	NRIPPLE_WORK *work = wk;
	NRIPPLE_3DOBJ *ripobj = work->ripobj;
	const NRIPPLE_ADD_H *head = EOA_AddPtrGet( eoa );
	
	work->head = *head;
	ripobj = FE_AllocClearMemory( work->head.ripple->fes, NRIPPLE_3DOBJ_SIZE, ALLOC_LO, 0 );
	work->ripobj = ripobj;
	
	FE_InitAllocator( work->head.fes, &ripobj->allocator );
	
	ripobj->pAnmObj = NNS_G3dAllocAnmObj( 
			&ripobj->allocator,
			work->head.ripple->obj_anm.pOneResAnm,
			work->head.ripple->obj_mdl.pModel );
	
	NNS_G3dAnmObjInit(
		ripobj->pAnmObj,
		work->head.ripple->obj_anm.pOneResAnm,
		work->head.ripple->obj_mdl.pModel,
		work->head.ripple->obj_mdl.pMdlTex );
	
	FLD_3DObjInit( &ripobj->obj, &work->head.ripple->obj_mdl );
	NNS_G3dRenderObjAddAnmObj( &ripobj->obj.render, ripobj->pAnmObj );
	
	EOA_MatrixGet( eoa, &mtx );
	FLD_3DObjSetMatrix( &ripobj->obj, mtx.x, mtx.y, mtx.z );
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA ���g��@�폜
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaNRipple_Delete( EOA_PTR eoa, void *wk )
{
	NRIPPLE_WORK *work = wk;
	NRIPPLE_3DOBJ *ripobj = work->ripobj;
	NNS_G3dFreeAnmObj( &ripobj->allocator, ripobj->pAnmObj );
	FE_FreeMemory( ripobj );
}

//--------------------------------------------------------------
/**
 * EOA ���g��@����
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaNRipple_Move( EOA_PTR eoa, void *wk )
{
	NRIPPLE_WORK *work = wk;
	NRIPPLE_3DOBJ *ripobj = work->ripobj;
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
 * EOA ���g��@�`��
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaNRipple_Draw( EOA_PTR eoa, void *wk )
{
	NRIPPLE_WORK *work = wk;
	NRIPPLE_3DOBJ *ripobj = work->ripobj;
	FLD_3DObjDraw( &ripobj->obj );
}

//==============================================================================
//	data
//==============================================================================
//--------------------------------------------------------------
///	���g��EOA_H
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_NRipple =
{
	NRIPPLE_WORK_SIZE,
	EoaNRipple_Init,
	EoaNRipple_Delete,
	EoaNRipple_Move,
	EoaNRipple_Draw,
};

