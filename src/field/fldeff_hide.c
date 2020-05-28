//******************************************************************************
/**
 * 
 * @file	fldeff_hide.c
 * @brief	�t�B�[���hOBJ�B�ꖪ
 * @author	kagaya
 * @data	05.07.13
 *
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "field_effect.h"
#include "fieldobj.h"
#include "fldeff_hide.h"

//==============================================================================
//	define
//==============================================================================

//==============================================================================
//	typedef struct
//==============================================================================
//--------------------------------------------------------------
///	FE_HIDE�^
//--------------------------------------------------------------
typedef struct _TAG_FE_HIDE * FE_HIDE_PTR;

//--------------------------------------------------------------
///	FE_HIDE�\����
//--------------------------------------------------------------
typedef struct _TAG_FE_HIDE
{
	FE_SYS *fes;
	NNSG3dRenderObj render[HIDE_MAX];
	NNSG3dResMdl *model[HIDE_MAX];
	NNSG3dResFileHeader *res_file[HIDE_MAX];
}FE_HIDE;

#define FE_HIDE_SIZE (sizeof(FE_HIDE)) ///<FE_HIDE�T�C�Y

//--------------------------------------------------------------
///	HIDE_ADD_H�\����
//--------------------------------------------------------------
typedef struct
{
	HIDETYPE type;
	FE_SYS *fes;
	FE_HIDE *hide;
	FIELD_OBJ_PTR fldobj;
	NNSG3dRenderObj *render;
}HIDE_ADD_H;

//--------------------------------------------------------------
///	HIDE_WORK�\����
//--------------------------------------------------------------
typedef struct
{
	int seq_no;
	int vanish_sw;
	int obj_id;
	int zone_id;
	HIDE_ADD_H head;
}HIDE_WORK;

#define HIDE_WORK_SIZE (sizeof(HIDE_WORK))

//==============================================================================
//	�v���g�^�C�v
//==============================================================================
static void Hide_GraphicInit( FE_HIDE_PTR hide );
static void Hide_GraphicDelete( FE_HIDE_PTR hide );
static NNSG3dRenderObj * Hide_TypeRenderGet( FE_HIDE_PTR hide, HIDETYPE type );

static const EOA_H_NPP DATA_EoaH_Hide;

static const u32 DATA_3DModelArcID_Hide[HIDE_MAX];

//==============================================================================
//	�B�ꖪ�@�V�X�e��
//==============================================================================
//--------------------------------------------------------------
/**
 * �B�ꖪ������
 * @param	fes		FE_SYS_PTR
 * @retval	FE_HIDE_PTR		FE_HIDE_PTR
 */
//--------------------------------------------------------------
void * FE_Hide_Init( FE_SYS *fes )
{
	FE_HIDE_PTR hide;
	
	hide = FE_AllocClearMemory( fes, FE_HIDE_SIZE, ALLOC_FR, 0 );
	hide->fes = fes;
	
	Hide_GraphicInit( hide );
	return( hide );
}

//--------------------------------------------------------------
/**
 * �B�ꖪ�폜
 * @param	hide		FE_HIDE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_Hide_Delete( void *work )
{
	FE_HIDE_PTR hide = work;
	Hide_GraphicDelete( hide );
	FE_FreeMemory( hide );
}

//==============================================================================
//	�B�ꖪ	�p�[�c
//==============================================================================

//==============================================================================
//	�B�ꖪ�@�O���t�B�b�N
//==============================================================================
//--------------------------------------------------------------
/**
 * �B�ꖪ �O���t�B�b�N������
 * @param	hide		FE_HIDE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Hide_GraphicInit( FE_HIDE_PTR hide )
{
	int i;
	u32 id;
	
	for( i = 0; i < HIDE_MAX; i++ ){
		id = DATA_3DModelArcID_Hide[i];
		FE_simple3DModelInit( hide->fes, id, ALLOC_FR,
				&hide->render[i], &hide->model[i], &hide->res_file[i] );
	}
}

//--------------------------------------------------------------
/**
 * �B�ꖪ�@�O���t�B�b�N�폜
 * @param	hide		FE_HIDE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Hide_GraphicDelete( FE_HIDE_PTR hide )
{
	int i;
	
	for( i = 0; i < HIDE_MAX; i++ ){
		FE_FreeMemory( hide->res_file[i] );
	}
}

//--------------------------------------------------------------
/**
 * �w��^�C�v�̃����_�擾
 * @param	hide	FE_HIDE_PTR
 * @param	type	HIDETYPE
 * @param	attr	HIDE_ATTR
 * @retval	NNSG3dRenderObj �w��̃����_
 */
//--------------------------------------------------------------
static NNSG3dRenderObj * Hide_TypeRenderGet( FE_HIDE_PTR hide, HIDETYPE type )
{
	return( &hide->render[type] );
}

//==============================================================================
//	�B�ꖪ�@EOA
//==============================================================================
//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ�B�ꖪ�ǉ�
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	type	HIDETYPE
 * @retval	eoa		EOA_PTR
 */
//--------------------------------------------------------------
EOA_PTR FE_FldOBJHide_Add( FIELD_OBJ_PTR fldobj, HIDETYPE type )
{
	VecFx32 mtx;
	EOA_PTR eoa;
	HIDE_ADD_H head;
	FE_SYS *fes;
	
	fes = FE_FieldOBJ_FE_SYS_Get( fldobj );
	
	{
		FIELDSYS_WORK *fsys = FE_FieldSysWorkGet( fes );
		int gx = FieldOBJ_NowPosGX_Get( fldobj );
		int gz = FieldOBJ_NowPosGZ_Get( fldobj );
		FieldOBJTool_GridCenterPosGet( gx, gz, &mtx );
		FieldOBJTool_GetHeight( fsys, &mtx );
	}
	
	{
		head.type = type;
		head.fes = fes;
		head.hide = FE_EffectWorkGet( fes, FE_FLD_HIDE );
		head.fldobj = fldobj;
		head.render = Hide_TypeRenderGet( head.hide, type );
	}
	
	{
		int pri = FieldOBJ_TCBPriGet( fldobj, FLDOBJ_TCBPRI_OFFS_AFTER );
		eoa = FE_EoaAddNpp( fes, &DATA_EoaH_Hide, &mtx, 0, &head, pri );
	}
	
	return( eoa );
}

//--------------------------------------------------------------
/**
 * EOA �B�ꖪ�@������
 * @param	eoa	EOA_PTR
 * @param	wk	eoa work *
 * @retval	int TRUE=����I���BFALSE=�ُ�I��
 */
//--------------------------------------------------------------
static int EoaHide_Init( EOA_PTR eoa, void *wk )
{
	HIDE_WORK *work = wk;
	const HIDE_ADD_H *head = EOA_AddPtrGet( eoa );
	FIELD_OBJ_PTR fldobj = head->fldobj;
	
	work->head = *head;
	work->obj_id = FieldOBJ_OBJIDGet( fldobj );
	work->zone_id = FieldOBJ_ZoneIDGet( fldobj );
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA �B�ꖪ�@�폜
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaHide_Delete( EOA_PTR eoa, void *wk )
{
	HIDE_WORK *work = wk;
	FIELD_OBJ_PTR fldobj = work->head.fldobj;
	
	if( FieldOBJ_CheckSameID(fldobj,work->obj_id,work->zone_id) == TRUE ){
		FieldOBJ_MoveHideEoaPtrSet( fldobj, NULL );
	}
}

//--------------------------------------------------------------
/**
 * EOA �B�ꖪ�@����
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaHide_Move( EOA_PTR eoa, void *wk )
{
	HIDE_WORK *work = wk;
}

//--------------------------------------------------------------
/**
 * EOA �B�ꖪ�@�`��
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaHide_Draw( EOA_PTR eoa, void *wk )
{
	HIDE_WORK *work = wk;
	
	if( work->vanish_sw == TRUE ){
		return;
	}
	
	{
		VecFx32 vec;
		VecFx32 scale = { FX32_ONE, FX32_ONE, FX32_ONE };
		MtxFx33 rot	  = { FX32_ONE, 0,0,0, FX32_ONE, 0,0,0,FX32_ONE};
		
		EOA_MatrixGet( eoa, &vec );
		simple_3DModelDraw( work->head.render, &vec, &rot, &scale );
	}
}

//--------------------------------------------------------------
///	�B�ꖪEOA_H
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_Hide =
{
	HIDE_WORK_SIZE,
	EoaHide_Init,
	EoaHide_Delete,
	EoaHide_Move,
	EoaHide_Draw,
};

//==============================================================================
//	data
//==============================================================================
//--------------------------------------------------------------
///	�B�ꖪimd�e�[�u���@���т�HIDETYPE�̒l�Ɉ�v
//--------------------------------------------------------------
static const u32 DATA_3DModelArcID_Hide[HIDE_MAX] =
{
	NARC_fldeff_nin_hide_s_nsbmd,
	NARC_fldeff_nin_hide_b_nsbmd,
	NARC_fldeff_nin_hide_g_nsbmd,
	NARC_fldeff_nin_hide_k_nsbmd,
};

