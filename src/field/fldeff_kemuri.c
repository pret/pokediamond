//******************************************************************************
/**
 * 
 * @file	fldeff_kemuri.c
 * @brief	�t�B�[���hOBJ�y��
 * @author	kagaya
 * @data	05.07.13
 *
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "field_effect.h"
#include "fieldobj.h"

#include "fldeff_kemuri.h"
#include "map_tool.h"

//==============================================================================
//	define
//==============================================================================
#define KEMURI_ANIME_FRAME (9)				///<�y���A�j���t���[��

#define KEMURI_DRAW_Z_OFFS (NUM_FX32(8))	///<�\�����WZ�I�t�Z�b�g

//==============================================================================
//	typedef struct
//==============================================================================
//--------------------------------------------------------------
///	FE_KEMURI_PTR�^
//--------------------------------------------------------------
typedef struct _TAG_FE_KEMURI * FE_KEMURI_PTR;

//--------------------------------------------------------------
///	FE_KEMURI�\����
//--------------------------------------------------------------
typedef struct _TAG_FE_KEMURI
{
	FE_SYS *fes;
}FE_KEMURI;

#define FE_KEMURI_SIZE (sizeof(FE_KEMURI))	///<FE_KEMURI�T�C�Y

//--------------------------------------------------------------
///	KEMURI_ADD_H�\����
//--------------------------------------------------------------
typedef struct
{
	FIELDSYS_WORK *fsys;
	FE_SYS *fes;
	FE_KEMURI_PTR kemu;
	FIELD_OBJ_PTR fldobj;
}KEMURI_ADD_H;

//--------------------------------------------------------------
///	KEMURI_WORK�\����
//--------------------------------------------------------------
typedef struct
{
	int seq_no;
	int obj_id;
	int zone_id;
	int frame;
	KEMURI_ADD_H head;
	BLACT_WORK_PTR act;
}KEMURI_WORK;

#define KEMURI_WORK_SIZE (sizeof(KEMURI_WORK))

//==============================================================================
//	�v���g�^�C�v
//==============================================================================
static void Kemuri_GraphicInit( FE_KEMURI_PTR kemu );
static void Kemuri_GraphicDelete( FE_KEMURI_PTR kemu );

static const EOA_H_NPP DATA_EoaH_Kemuri;
const BLACT_ANIME_TBL DATA_BlActAnmTbl_Kemuri[];

//==============================================================================
//	�y��	�V�X�e��
//==============================================================================
//--------------------------------------------------------------
/**
 * �y��������
 * @param	fes		FE_SYS_PTR
 * @retval	FE_KEMURI_PTR FE_KEMURI_PTR
 */
//--------------------------------------------------------------
void * FE_Kemuri_Init( FE_SYS *fes )
{
	FE_KEMURI_PTR kemu;
	
	kemu = FE_AllocClearMemory( fes, FE_KEMURI_SIZE, ALLOC_FR, 0 );
	kemu->fes = fes;
	
	Kemuri_GraphicInit( kemu );
	return( kemu );
}

//--------------------------------------------------------------
/**
 * �y���폜
 * @param	kusa		FE_KEMURI_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_Kemuri_Delete( void *work )
{
	FE_KEMURI_PTR kemu = work;
	
	Kemuri_GraphicDelete( kemu );
	FE_FreeMemory( kemu );
}

//==============================================================================
//	�y���@�O���t�B�b�N
//==============================================================================
//--------------------------------------------------------------
/**
 * ���@�O���t�B�b�N������
 * @param	kemu	FE_GRASS_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Kemuri_GraphicInit( FE_KEMURI_PTR kemu )
{
	FE_BlActResAdd_MdlArc( kemu->fes, FE_RESID_MDL_KEMURI, NARC_fldeff_hero_kemu_nsbmd );
	FE_BlActResAdd_AnmArc( kemu->fes, FE_RESID_ANM_KEMURI, NARC_fldeff_hero_kemu_itpcv_dat );
	FE_BlActResAdd_TexArc( kemu->fes,
			FE_RESID_TEX_KEMURI, NARC_fldeff_hero_kemu_nsbtx, TEXRESM_TEX_CUT_TRUE );
	
	FE_BlActHeaderManageAddResmID( kemu->fes, FE_BLACT_H_ID_KEMURI,
			FE_RESID_MDL_KEMURI, FE_RESID_ANM_KEMURI,
			FE_RESID_TEX_KEMURI, FE_BLACT_TEX_VRAM,
			DATA_BlActAnmTbl_Kemuri );
}

//--------------------------------------------------------------
/**
 * �y���@�O���t�B�b�N�폜
 * @param	kemu	FE_KEMURI_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Kemuri_GraphicDelete( FE_KEMURI_PTR kemu )
{
	FE_BlActResDelete_Mdl( kemu->fes, FE_RESID_MDL_KEMURI );
	FE_BlActResDelete_Anm( kemu->fes, FE_RESID_ANM_KEMURI );
	FE_BlActResDelete_Tex( kemu->fes, FE_RESID_TEX_KEMURI );
	
	FE_BlActHeaderManageFree( kemu->fes, FE_BLACT_H_ID_KEMURI );
}

//==============================================================================
//	EOA �y��
//==============================================================================
//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ�p�y���ǉ�
 * @param	fldobj		FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_FldOBJKemuri_Add( FIELD_OBJ_PTR fldobj )
{
	KEMURI_ADD_H head;
	FE_SYS *fes;
	EOA_PTR eoa;
	VecFx32 vec;
	int pri;
	
	fes = FE_FieldOBJ_FE_SYS_Get( fldobj );
	
	head.fsys = FieldOBJ_FieldSysWorkGet( fldobj );
	head.fes = fes;
	head.kemu = FE_EffectWorkGet( fes, FE_FLD_KEMURI );
	head.fldobj = fldobj;
	
	FieldOBJ_VecPosGet( fldobj, &vec );
	FieldOBJTool_GridCenterPosGet(
		FieldOBJ_NowPosGX_Get(fldobj), FieldOBJ_NowPosGZ_Get(fldobj), &vec );
	
	pri = FieldOBJ_TCBPriGet( fldobj, FLDOBJ_TCBPRI_OFFS_AFTER );
	eoa = FE_EoaAddNpp( fes, &DATA_EoaH_Kemuri, &vec, 0, &head, pri );
}

//--------------------------------------------------------------
/**
 * EOA �y���@������
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	int		TRUE=����I���BFALSE=�ُ�I��
 */
//--------------------------------------------------------------
static int EoaKemuri_Init( EOA_PTR eoa, void *wk )
{
	VecFx32 vec;
	KEMURI_WORK *work;
	const KEMURI_ADD_H *head;
	
	work = wk;
	head = EOA_AddPtrGet( eoa );
	
	work->head = *head;
	work->obj_id = FieldOBJ_OBJIDGet( work->head.fldobj );
	work->zone_id = FieldOBJ_ZoneIDGet( work->head.fldobj );
	
	EOA_MatrixGet( eoa, &vec );
	work->act = FE_BlActAddID( work->head.fes, FE_BLACT_H_ID_KEMURI, &vec );
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA �y���@�폜
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaKemuri_Delete( EOA_PTR eoa, void *wk )
{
	KEMURI_WORK *work;
	
	work = wk;
	BLACT_Delete( work->act );
}

//--------------------------------------------------------------
/**
 * EOA �y���@����
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaKemuri_Move( EOA_PTR eoa, void *wk )
{
	int frame;
	KEMURI_WORK *work;
	FIELD_OBJ_PTR fldobj;
	
	work = wk;
	fldobj = work->head.fldobj;
	
	switch( work->seq_no ){
	case 0:													//�h��
		BLACT_AnmFrameChg( work->act, FX32_ONE );
		frame = BLACT_AnmFrameGetOffs( work->act ) / FX32_ONE;
		
		if( frame >= KEMURI_ANIME_FRAME ){
			FE_EoaDelete( eoa );
			return;
		}
		
		break;
	}
}

//--------------------------------------------------------------
/**
 * EOA �y���@�`��
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaKemuri_Draw( EOA_PTR eoa, void *wk )
{
	VecFx32 vec,d_vec;
	KEMURI_WORK *work;
	FIELD_OBJ_PTR fldobj;
	
	work = wk;
	fldobj = work->head.fldobj;
	
	EOA_MatrixGet( eoa, &vec );
	vec.z += KEMURI_DRAW_Z_OFFS;
	BLACT_MatrixSet( work->act, &vec );
}

//==============================================================================
//	data
//==============================================================================
//--------------------------------------------------------------
///	�y��EOA_H
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_Kemuri =
{
	KEMURI_WORK_SIZE,
	EoaKemuri_Init,
	EoaKemuri_Delete,
	EoaKemuri_Move,
	EoaKemuri_Draw,
};

//--------------------------------------------------------------
///	�y���A�j��
//--------------------------------------------------------------
static const BLACT_ANIME_TBL DATA_BlActAnmTbl_Kemuri[] =
{
	{ 0, KEMURI_ANIME_FRAME, BLACT_ANIM_END },
	{ 0, 0, BLACT_ANIM_CMD_MAX },
};
