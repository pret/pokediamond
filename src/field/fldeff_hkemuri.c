//******************************************************************************
/**
 * 
 * @file	fldeff_hkemuri.c
 * @brief	�t�B�[���hOBJ�B�ꖪ�y��
 * @author	kagaya
 * @data	05.07.13
 *
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "field_effect.h"
#include "fieldobj.h"

#include "fldeff_hkemuri.h"

//==============================================================================
//	define
//==============================================================================
#define HKEMURI_ANIME_FRAME (7)				///<�B�ꖪ�y���A�j���t���[��

#define HKEMURI_DRAW_Z_OFFS (NUM_FX32(8))	///<�\�����WZ�I�t�Z�b�g

//==============================================================================
//	typedef struct
//==============================================================================
//--------------------------------------------------------------
///	FE_HKEMURI_PTR�^
//--------------------------------------------------------------
typedef struct _TAG_FE_HKEMURI * FE_HKEMURI_PTR;

//--------------------------------------------------------------
///	FE_HKEMURI�\����
//--------------------------------------------------------------
typedef struct _TAG_FE_HKEMURI
{
	FE_SYS *fes;
}FE_HKEMURI;

#define FE_HKEMURI_SIZE (sizeof(FE_HKEMURI))	///<FE_HKEMURI�T�C�Y

//--------------------------------------------------------------
///	HKEMURI_ADD_H�\����
//--------------------------------------------------------------
typedef struct
{
	FIELDSYS_WORK *fsys;
	FE_SYS *fes;
	FE_HKEMURI_PTR hkemu;
	FIELD_OBJ_PTR fldobj;
}HKEMURI_ADD_H;

//--------------------------------------------------------------
///	HKEMURI_WORK�\����
//--------------------------------------------------------------
typedef struct
{
	int seq_no;
	int obj_id;
	int zone_id;
	int frame;
	HKEMURI_ADD_H head;
	BLACT_WORK_PTR act;
}HKEMURI_WORK;

#define HKEMURI_WORK_SIZE (sizeof(HKEMURI_WORK))

//==============================================================================
//	�v���g�^�C�v
//==============================================================================
static void HKemuri_GraphicInit( FE_HKEMURI_PTR hkemu );
static void HKemuri_GraphicDelete( FE_HKEMURI_PTR hkemu );

static const EOA_H_NPP DATA_EoaH_HKemuri;
const BLACT_ANIME_TBL DATA_BlActAnmTbl_HKemuri[];

//==============================================================================
//	�B�ꖪ�y��	�V�X�e��
//==============================================================================
//--------------------------------------------------------------
/**
 * �B�ꖪ�y��������
 * @param	fes		FE_SYS_PTR
 * @retval	FE_HKEMURI_PTR FE_HKEMURI_PTR
 */
//--------------------------------------------------------------
void * FE_HKemuri_Init( FE_SYS *fes )
{
	FE_HKEMURI_PTR hkemu;
	
	hkemu = FE_AllocClearMemory( fes, FE_HKEMURI_SIZE, ALLOC_FR, 0 );
	hkemu->fes = fes;
	
	HKemuri_GraphicInit( hkemu );
	return( hkemu );
}

//--------------------------------------------------------------
/**
 * �B�ꖪ�y���폜
 * @param	kusa		FE_HKEMURI_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_HKemuri_Delete( void *work )
{
	FE_HKEMURI_PTR hkemu = work;
	
	HKemuri_GraphicDelete( hkemu );
	FE_FreeMemory( hkemu );
}

//==============================================================================
//	�B�ꖪ�y���@�O���t�B�b�N
//==============================================================================
//--------------------------------------------------------------
/**
 * �B�ꖪ�y���@�O���t�B�b�N������
 * @param	hkemu	FE_GRASS_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void HKemuri_GraphicInit( FE_HKEMURI_PTR hkemu )
{
	FE_BlActResAdd_MdlArc( hkemu->fes, FE_RESID_MDL_HKEMURI, NARC_fldeff_nin_kemu_nsbmd );
	FE_BlActResAdd_AnmArc( hkemu->fes, FE_RESID_ANM_HKEMURI, NARC_fldeff_nin_kemu_itpcv_dat );
	FE_BlActResAdd_TexArc( hkemu->fes,
			FE_RESID_TEX_HKEMURI, NARC_fldeff_nin_kemu_nsbtx, TEXRESM_TEX_CUT_TRUE );
	
	FE_BlActHeaderManageAddResmID( hkemu->fes, FE_BLACT_H_ID_HKEMURI,
			FE_RESID_MDL_HKEMURI, FE_RESID_ANM_HKEMURI,
			FE_RESID_TEX_HKEMURI, FE_BLACT_TEX_VRAM,
			DATA_BlActAnmTbl_HKemuri );
}

//--------------------------------------------------------------
/**
 * �B�ꖪ�y���@�O���t�B�b�N�폜
 * @param	hkemu	FE_HKEMURI_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void HKemuri_GraphicDelete( FE_HKEMURI_PTR hkemu )
{
	FE_BlActResDelete_Mdl( hkemu->fes, FE_RESID_MDL_HKEMURI );
	FE_BlActResDelete_Anm( hkemu->fes, FE_RESID_ANM_HKEMURI );
	FE_BlActResDelete_Tex( hkemu->fes, FE_RESID_TEX_HKEMURI );
	
	FE_BlActHeaderManageFree( hkemu->fes, FE_BLACT_H_ID_HKEMURI );
}

//==============================================================================
//	EOA �B�ꖪ�y��
//==============================================================================
//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ�p�B�ꖪ�y���ǉ�
 * @param	fldobj		FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_FldOBJHKemuri_Add( FIELD_OBJ_PTR fldobj )
{
	HKEMURI_ADD_H head;
	FE_SYS *fes;
	EOA_PTR eoa;
	VecFx32 vec;
	int pri;
	
	fes = FE_FieldOBJ_FE_SYS_Get( fldobj );
	
	head.fsys = FieldOBJ_FieldSysWorkGet( fldobj );
	head.fes = fes;
	head.hkemu = FE_EffectWorkGet( fes, FE_FLD_HKEMURI );
	head.fldobj = fldobj;
	
	FieldOBJ_VecPosGet( fldobj, &vec );
	FieldOBJTool_GridCenterPosGet(
		FieldOBJ_NowPosGX_Get(fldobj), FieldOBJ_NowPosGZ_Get(fldobj), &vec );
	
	pri = FieldOBJ_TCBPriGet( fldobj, FLDOBJ_TCBPRI_OFFS_AFTER );
	eoa = FE_EoaAddNpp( fes, &DATA_EoaH_HKemuri, &vec, 0, &head, pri );
}

//--------------------------------------------------------------
/**
 * EOA �B�ꖪ�y���@������
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	int		TRUE=����I���BFALSE=�ُ�I��
 */
//--------------------------------------------------------------
static int EoaHKemuri_Init( EOA_PTR eoa, void *wk )
{
	VecFx32 vec;
	HKEMURI_WORK *work;
	const HKEMURI_ADD_H *head;
	
	work = wk;
	head = EOA_AddPtrGet( eoa );
	
	work->head = *head;
	work->obj_id = FieldOBJ_OBJIDGet( work->head.fldobj );
	work->zone_id = FieldOBJ_ZoneIDGet( work->head.fldobj );
	
	EOA_MatrixGet( eoa, &vec );
	work->act = FE_BlActAddID( work->head.fes, FE_BLACT_H_ID_HKEMURI, &vec );
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA �B�ꖪ�y���@�폜
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaHKemuri_Delete( EOA_PTR eoa, void *wk )
{
	HKEMURI_WORK *work;
	
	work = wk;
	BLACT_Delete( work->act );
}

//--------------------------------------------------------------
/**
 * EOA �B�ꖪ�y���@����
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaHKemuri_Move( EOA_PTR eoa, void *wk )
{
	int frame;
	HKEMURI_WORK *work;
	FIELD_OBJ_PTR fldobj;
	
	work = wk;
	fldobj = work->head.fldobj;
	
	switch( work->seq_no ){
	case 0:													//�h��
		BLACT_AnmFrameChg( work->act, FX32_ONE );
		frame = BLACT_AnmFrameGetOffs( work->act ) / FX32_ONE;
		
		if( frame >= HKEMURI_ANIME_FRAME ){
			FE_EoaDelete( eoa );
			return;
		}
		
		break;
	}
}

//--------------------------------------------------------------
/**
 * EOA �B�ꖪ�y���@�`��
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaHKemuri_Draw( EOA_PTR eoa, void *wk )
{
	VecFx32 vec,d_vec;
	HKEMURI_WORK *work;
	FIELD_OBJ_PTR fldobj;
	
	work = wk;
	fldobj = work->head.fldobj;
	
	EOA_MatrixGet( eoa, &vec );
	vec.z += HKEMURI_DRAW_Z_OFFS;
	BLACT_MatrixSet( work->act, &vec );
}

//==============================================================================
//	data
//==============================================================================
//--------------------------------------------------------------
///	�B�ꖪ�y��EOA_H
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_HKemuri =
{
	HKEMURI_WORK_SIZE,
	EoaHKemuri_Init,
	EoaHKemuri_Delete,
	EoaHKemuri_Move,
	EoaHKemuri_Draw,
};

//--------------------------------------------------------------
///	�B�ꖪ�y���A�j��
//--------------------------------------------------------------
static const BLACT_ANIME_TBL DATA_BlActAnmTbl_HKemuri[] =
{
	{ 0, HKEMURI_ANIME_FRAME, BLACT_ANIM_END },
	{ 0, 0, BLACT_ANIM_CMD_MAX },
};
