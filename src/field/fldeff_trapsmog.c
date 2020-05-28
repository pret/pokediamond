//******************************************************************************
/**
 * 
 * @file	fldeff_trapsmog.c
 * @brief	�t�B�[���hOBJ�@��
 * @author	k.ohno
 * @data	06.05.05
 *
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "field_effect.h"
#include "fieldobj.h"
#include "fldeff_trapsmog.h"

#include "system/snd_tool.h"
#include "underground/ug_snd_def.h"

#include "field_3dobj.h"

//==============================================================================
//	define
//==============================================================================

#define TRAPSMOG_DRAW_Y_OFFSET (0)
#define TRAPSMOG_DRAW_Z_OFFSET (FX32_ONE*2)

#define TRAPSMOG_ON_FRAME (30)
#define TRAPSMOG_OFF_FRAME (TRAPSMOG_ON_FRAME+30)

//==============================================================================
//	typedef struct
//==============================================================================
//--------------------------------------------------------------
///	FE_TRAPSMOG_PTR��`
//--------------------------------------------------------------
typedef struct _TAG_FE_TRAPSMOG * FE_TRAPSMOG_PTR;

//--------------------------------------------------------------
///	FE_TRAPSMOG�\����
//--------------------------------------------------------------
typedef struct _TAG_FE_TRAPSMOG
{
	FE_SYS *fes;
	
	FLD_3DOBJ_MDL obj_mdl;
	FLD_3DOBJ_ANM obj_anm;
	NNSFndAllocator allocator;
}FE_TRAPSMOG;

#define FE_TRAPSMOG_SIZE (sizeof(FE_TRAPSMOG)) ///<FE_TRAPSMOG�T�C�Y

//--------------------------------------------------------------
///	TRAPSMOG_ADD_H�\����
//--------------------------------------------------------------
typedef struct
{
	FE_SYS *fes;					///<FE_SYS_PTR
	FE_TRAPSMOG_PTR trapsmog;		///<FE_TRAPSMOG_PTR
}TRAPSMOG_ADD_H;

#define TRAPSMOG_ADD_H_SIZE (sizeof(TRAPSMOG_ADD_H)) ///<TRAPSMOG_ADD_H�T�C�Y

//--------------------------------------------------------------
///	TRAPSMOG_3DOBJ�\����
//--------------------------------------------------------------
typedef struct
{
	NNSG3dAnmObj*			pAnmObj;			// �A�j���[�V�����I�u�W�F
	NNSFndAllocator allocator;
	fx32 frame;
	FLD_3DOBJ obj;
}TRAPSMOG_3DOBJ;

#define TRAPSMOG_3DOBJ_SIZE (sizeof(TRAPSMOG_3DOBJ))

//--------------------------------------------------------------
///	TRAPSMOG_WORK�\����
//--------------------------------------------------------------
typedef struct
{
	TRAPSMOG_3DOBJ *ripobj;
	TRAPSMOG_ADD_H head;						///<�ǉ�����TRAPSMOG_ADD_H
}TRAPSMOG_WORK;

#define TRAPSMOG_WORK_SIZE (sizeof(TRAPSMOG_WORK))	///<TRAPSMOG_WORK�T�C�Y

//==============================================================================
//	�v���g�^�C�v
//==============================================================================
static void Trapsmog_GraphicInit( FE_TRAPSMOG_PTR trapsmog );
static void Trapsmog_GraphicDelete( FE_TRAPSMOG_PTR trapsmog );

static const EOA_H_NPP DATA_EoaH_Trapsmog;

//==============================================================================
//	���@�V�X�e��
//==============================================================================
//--------------------------------------------------------------
/**
 * ��������
 * @param	fes		FE_SYS_PTR
 * @retval	FE_TRAPSMOG_PTR	FE_TRAPSMOG_PTR
 */
//--------------------------------------------------------------
void * FE_Trapsmog_Init( FE_SYS *fes )
{
	FE_TRAPSMOG_PTR trapsmog;
	
	trapsmog = FE_AllocClearMemory( fes, FE_TRAPSMOG_SIZE, ALLOC_FR, 0 );
	trapsmog->fes = fes;
	
	Trapsmog_GraphicInit( trapsmog );
	return( trapsmog );
}

//--------------------------------------------------------------
/**
 * ���폜
 * @param	trapsmog		FE_TRAPSMOG_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_Trapsmog_Delete( void *work )
{
	FE_TRAPSMOG_PTR trapsmog = work;
	Trapsmog_GraphicDelete( trapsmog );
	FE_FreeMemory(trapsmog );
}

//==============================================================================
//	��	�p�[�c
//==============================================================================

//==============================================================================
//	���@�O���t�B�b�N
//==============================================================================
//--------------------------------------------------------------
/**
 * �� �O���t�B�b�N������
 * @param	trapsmog	FE_TRAPSMOG_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Trapsmog_GraphicInit( FE_TRAPSMOG_PTR trapsmog )
{
	FE_InitAllocator( trapsmog->fes, &trapsmog->allocator );
/*
	FLD_3DObjMdlLoad( &trapsmog->obj_mdl,
		ARC_FLDEFF, NARC_fldeff_ripple_nsbmd, trapsmog->heap_id );
	FLD_3DObjAnmLoad( &trapsmog->obj_anm, &trapsmog->obj_mdl,
		ARC_FLDEFF, NARC_fldeff_ripple_nsbtp, trapsmog->heap_id, &trapsmog->allocator );
*/
    
    FE_3DObjMdlLoad( trapsmog->fes, &trapsmog->obj_mdl,
			NARC_fldeff_ug_ef_smoke_nsbmd, ALLOC_FR );
	FE_3DObjAnmLoad( trapsmog->fes,
		&trapsmog->obj_anm, &trapsmog->obj_mdl, &trapsmog->allocator,
		NARC_fldeff_ug_ef_smoke_nsbtp, ALLOC_FR );
}

//--------------------------------------------------------------
/**
 * �� �O���t�B�b�N�폜
 * @param	trapsmog	FE_TRAPSMOG_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Trapsmog_GraphicDelete( FE_TRAPSMOG_PTR trapsmog )
{
	FLD_3DObjMdlDelete( &trapsmog->obj_mdl );	
	FLD_3DObjAnmDelete( &trapsmog->obj_anm, &trapsmog->allocator );	
}

//==============================================================================
//	��EOA
//==============================================================================
//--------------------------------------------------------------
/**
 * ���ǉ�
 * @param	fsys	�t�B�[���h�ɓ\��t�� �����I��EFFECT
 * @param	gx		�\������O���b�hX���W
 * @param	gz		�\������O���b�hZ���W
 * @retval	none
 */
//--------------------------------------------------------------
void FE_FldOBJTrapsmogSet(  FIELDSYS_WORK *fsys, int gx, int gy, int gz )
{
	int pri,param;
	TRAPSMOG_ADD_H head;
	VecFx32 mtx;
	
	head.fes =  fsys->fes;
	head.trapsmog = FE_EffectWorkGet( head.fes, FE_UG_TRAP_SMOG );

    mtx.x = GRID_SIZE_FX32( gx ) + (FX32_ONE*8);
    mtx.y = (FX32_ONE * 10);
    mtx.z = GRID_SIZE_FX32( gz );

	param = 0;
	FE_EoaAddNpp( head.fes, &DATA_EoaH_Trapsmog, &mtx, param, &head, 0xff );
    Snd_SePlay(UGT_SE_TRAPEND);
}

//--------------------------------------------------------------
/**
 * EOA ���@������
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	int		TRUE=����I���BFALSE=�ُ�I��
 */
//--------------------------------------------------------------
static int EoaTrapsmog_Init( EOA_PTR eoa, void *wk )
{
	VecFx32 mtx;
	TRAPSMOG_WORK *work = wk;
	TRAPSMOG_3DOBJ *ripobj = work->ripobj;
	const TRAPSMOG_ADD_H *head = EOA_AddPtrGet( eoa );
	
	work->head = *head;
	ripobj = FE_AllocClearMemory( work->head.fes, TRAPSMOG_3DOBJ_SIZE, ALLOC_LO, 0 );
	work->ripobj = ripobj;
	
	FE_InitAllocator( work->head.fes, &ripobj->allocator );
	
	ripobj->pAnmObj = NNS_G3dAllocAnmObj( 
			&ripobj->allocator,
			work->head.trapsmog->obj_anm.pOneResAnm,
			work->head.trapsmog->obj_mdl.pModel );
	
	NNS_G3dAnmObjInit(
		ripobj->pAnmObj,
		work->head.trapsmog->obj_anm.pOneResAnm,
		work->head.trapsmog->obj_mdl.pModel,
		work->head.trapsmog->obj_mdl.pMdlTex );
	
	FLD_3DObjInit( &ripobj->obj, &work->head.trapsmog->obj_mdl );
	NNS_G3dRenderObjAddAnmObj( &ripobj->obj.render, ripobj->pAnmObj );
	
	EOA_MatrixGet( eoa, &mtx );
	FLD_3DObjSetMatrix( &ripobj->obj, mtx.x, mtx.y, mtx.z );
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA ���@�폜
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaTrapsmog_Delete( EOA_PTR eoa, void *wk )
{
	TRAPSMOG_WORK *work = wk;
	TRAPSMOG_3DOBJ *ripobj = work->ripobj;
	NNS_G3dFreeAnmObj( &ripobj->allocator, ripobj->pAnmObj );
	FE_FreeMemory( ripobj );
}

//--------------------------------------------------------------
/**
 * EOA ���@����
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaTrapsmog_Move( EOA_PTR eoa, void *wk )
{
	TRAPSMOG_WORK *work = wk;
	TRAPSMOG_3DOBJ *ripobj = work->ripobj;
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
 * EOA ���@�`��
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaTrapsmog_Draw( EOA_PTR eoa, void *wk )
{
    TRAPSMOG_WORK *work = wk;
	TRAPSMOG_3DOBJ *ripobj = work->ripobj;
#if 0
    FLD_3DObjSetRota(&ripobj->obj, 0x3000,FLD_3DROTA_WAY_X);
    FLD_3DObjDraw( &ripobj->obj );
#else
    
    {
		VecFx32 scale = { FX32_ONE, FX32_ONE, FX32_ONE };
		MtxFx33 rot	  = { FX32_ONE, 0,0,0, FX32_ONE, 0,0,0,FX32_ONE};
        // �J�����t�s�������
        const MtxFx43* pCamInv = NNS_G3dGlbGetInvCameraMtx();
        MtxFx33 Mat33;


        
        Rot360_to_MtxFx33(&rot, 90, 0, 0);
        MTX_Copy43To33(pCamInv, &Mat33);
        MTX_Concat33(&rot, &Mat33, &rot);
        simple_3DModelDraw( &ripobj->obj.render, &ripobj->obj.matrix, &rot, &ripobj->obj.scale );
	}
#endif
}

//==============================================================================
//	data
//==============================================================================
//--------------------------------------------------------------
///	��EOA_H
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_Trapsmog =
{
	TRAPSMOG_WORK_SIZE,
	EoaTrapsmog_Init,
	EoaTrapsmog_Delete,
	EoaTrapsmog_Move,
	EoaTrapsmog_Draw,
};

