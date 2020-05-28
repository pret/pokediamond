//******************************************************************************
/**
 * 
 * @file	fldeff_redframe.c
 * @brief	�t�B�[���hOBJ �Ԙg
 * @author	kagaya
 * @data	05.07.13
 *
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "field_effect.h"
#include "fieldobj.h"

#include "fldeff_redframe.h"
#include "map_tool.h"

//==============================================================================
//	define
//==============================================================================
#define REDFRAME_ANIME_FRAME (1)				///<�}�[�N�A�j���t���[��

//==============================================================================
//	typedef struct
//==============================================================================
//--------------------------------------------------------------
///	FE_REDFRAME�\����
//--------------------------------------------------------------
typedef struct _TAG_FE_REDFRAME
{
	FE_SYS *fes;
}FE_REDFRAME;

#define FE_REDFRAME_SIZE (sizeof(FE_REDFRAME))	///<FE_REDFRAME�T�C�Y

//--------------------------------------------------------------
///	REDFRAME_ADD_H�\����
//--------------------------------------------------------------
typedef struct
{
	FIELDSYS_WORK *fsys;
	FE_SYS *fes;
	FE_REDFRAME_PTR red;
	FIELD_OBJ_PTR fldobj;
}REDFRAME_ADD_H;

//--------------------------------------------------------------
///	REDFRAME_WORK�\����
//--------------------------------------------------------------
typedef struct
{
	int seq_no;
	int obj_id;
	int zone_id;
	int frame;
	REDFRAME_ADD_H head;
	BLACT_WORK_PTR act;
}REDFRAME_WORK;

#define REDFRAME_WORK_SIZE (sizeof(REDFRAME_WORK))

//==============================================================================
//	�v���g�^�C�v
//==============================================================================
static void RedFrame_GraphicInit( FE_REDFRAME_PTR red );
static void RedFrame_GraphicDelete( FE_REDFRAME_PTR red );

static const EOA_H_NPP DATA_EoaH_RedFrame;
const BLACT_ANIME_TBL DATA_BlActAnmTbl_RedFrame[];

//==============================================================================
//	�}�[�N	�V�X�e��
//==============================================================================
//--------------------------------------------------------------
/**
 * �}�[�N������
 * @param	fes		FE_SYS_PTR
 * @retval	FE_REDFRAME_PTR FE_REDFRAME_PTR
 */
//--------------------------------------------------------------
void * FE_RedFrame_Init( FE_SYS *fes )
{
	FE_REDFRAME_PTR red;
	
	red = FE_AllocClearMemory( fes, FE_REDFRAME_SIZE, ALLOC_FR, 0 );
	red->fes = fes;
	
	RedFrame_GraphicInit( red );
	return( red );
}

//--------------------------------------------------------------
/**
 * �}�[�N�폜
 * @param	kusa		FE_REDFRAME_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_RedFrame_Delete( void *work )
{
	FE_REDFRAME_PTR red = work;
	RedFrame_GraphicDelete( red );
	FE_FreeMemory( red );
}

//==============================================================================
//	�}�[�N�@�O���t�B�b�N
//==============================================================================
//--------------------------------------------------------------
/**
 * �}�[�N�@�O���t�B�b�N������
 * @param	red	FE_GRASS_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void RedFrame_GraphicInit( FE_REDFRAME_PTR red )
{
	FE_BlActResAdd_MdlArc( red->fes, FE_RESID_MDL_REDFRAME, NARC_fldeff_red_waku_nsbmd );
	FE_BlActResAdd_TexArc( red->fes,
			FE_RESID_TEX_REDFRAME, NARC_fldeff_red_waku_nsbtx, TEXRESM_TEX_CUT_TRUE );
	
	FE_BlActHeaderManageAddResmID( red->fes, FE_BLACT_H_ID_REDFRAME,
			FE_RESID_MDL_REDFRAME, FE_RESID_ANM_GRASS,
			FE_RESID_TEX_REDFRAME, FE_BLACT_TEX_VRAM,
			DATA_BlActAnmTbl_RedFrame );
}

//--------------------------------------------------------------
/**
 * �}�[�N�@�O���t�B�b�N�폜
 * @param	red	FE_REDFRAME_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void RedFrame_GraphicDelete( FE_REDFRAME_PTR red )
{
	FE_BlActResDelete_Mdl( red->fes, FE_RESID_MDL_REDFRAME );
	FE_BlActResDelete_Tex( red->fes, FE_RESID_TEX_REDFRAME );
	
	FE_BlActHeaderManageFree( red->fes, FE_BLACT_H_ID_REDFRAME );
}

//==============================================================================
//	EOA �}�[�N
//==============================================================================
//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ�p�Ԙg�ǉ�
 * @param	fldobj		FIELD_OBJ_PTR
 * @retval	eoa			EOA_PTR
 */
//--------------------------------------------------------------
EOA_PTR FE_FldOBJRedFrame_Add( FIELD_OBJ_PTR fldobj )
{
	REDFRAME_ADD_H head;
	FE_SYS *fes;
	EOA_PTR eoa;
	
	fes = FE_FieldOBJ_FE_SYS_Get( fldobj );
	
	head.fsys = FieldOBJ_FieldSysWorkGet( fldobj );
	head.fes = fes;
	head.red = FE_EffectWorkGet( fes, FE_UG_REDFRAME );
	head.fldobj = fldobj;
	
	{
		VecFx32 vec = {0,0,0};
		int pri = FieldOBJ_TCBPriGet( fldobj, FLDOBJ_TCBPRI_OFFS_AFTER );
		eoa = FE_EoaAddNpp( fes, &DATA_EoaH_RedFrame, &vec, 0, &head, pri );
	}
	
	return( eoa );
}

//--------------------------------------------------------------
/**
 * EOA �}�[�N�@������
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	int		TRUE=����I���BFALSE=�ُ�I��
 */
//--------------------------------------------------------------
static int EoaRedFrame_Init( EOA_PTR eoa, void *wk )
{
	VecFx32 vec = { 0,0,0 };
	REDFRAME_WORK *work;
	const REDFRAME_ADD_H *head;
	
	work = wk;
	head = EOA_AddPtrGet( eoa );
	
	work->head = *head;
	work->obj_id = FieldOBJ_OBJIDGet( work->head.fldobj );
	work->zone_id = FieldOBJ_ZoneIDGet( work->head.fldobj );
	
	EOA_MatrixSet( eoa, &vec );
	work->act = FE_BlActAddID( work->head.fes, FE_BLACT_H_ID_REDFRAME, &vec );
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA �}�[�N�@�폜
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaRedFrame_Delete( EOA_PTR eoa, void *wk )
{
	REDFRAME_WORK *work;
	
	work = wk;
	BLACT_Delete( work->act );
}

//--------------------------------------------------------------
/**
 * EOA �}�[�N�@����
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaRedFrame_Move( EOA_PTR eoa, void *wk )
{
	REDFRAME_WORK *work;
	FIELD_OBJ_PTR fldobj;
	
	work = wk;
	fldobj = work->head.fldobj;
	
	if( FieldOBJ_CheckSameID(fldobj,work->obj_id,work->zone_id) == FALSE ){
		FE_EoaDelete( eoa );
		return;
	}
}

//--------------------------------------------------------------
/**
 * EOA �}�[�N�@�`��
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaRedFrame_Draw( EOA_PTR eoa, void *wk )
{
	VecFx32 vec,d_vec;
	REDFRAME_WORK *work;
	FIELD_OBJ_PTR fldobj;
	
	work = wk;
	fldobj = work->head.fldobj;
	
	if( FieldOBJ_CheckSameID(fldobj,work->obj_id,work->zone_id) == FALSE ){
		FE_EoaDelete( eoa );
		return;
	}
	
	FieldOBJ_VecPosGet( fldobj, &vec );
	FieldOBJ_VecDrawOffsGet( fldobj, &d_vec );
	
	vec.x += d_vec.x;
	vec.y += d_vec.y;
	vec.z += d_vec.z;
	vec.z += FX32_ONE * 12;
	BLACT_MatrixSet( work->act, &vec );
}

//==============================================================================
//	data
//==============================================================================
//--------------------------------------------------------------
///	�}�[�NEOA_H
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_RedFrame =
{
	REDFRAME_WORK_SIZE,
	EoaRedFrame_Init,
	EoaRedFrame_Delete,
	EoaRedFrame_Move,
	EoaRedFrame_Draw,
};

//--------------------------------------------------------------
///	�}�[�N�A�j��
//--------------------------------------------------------------
static const BLACT_ANIME_TBL DATA_BlActAnmTbl_RedFrame[] =
{
	{ 0, REDFRAME_ANIME_FRAME, BLACT_ANIM_END },
	{ 0, 0, BLACT_ANIM_CMD_MAX },
};
