//******************************************************************************
/**
 * 
 * @file	fldeff_ngrass.c
 * @brief	�t�B�[���hOBJ����
 * @author	kagaya
 * @data	05.07.13
 *
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "field_effect.h"
#include "fieldobj.h"

#include "fldeff_ngrass.h"
#include "map_tool.h"

//==============================================================================
//	define
//==============================================================================
#define YURE_KUSA_SET

///�����\���ʒu�@�O���b�h����̃I�t�Z�b�gX
#define NGRASS_GIRD_VEC_OFFS_X (FLDOBJ_VEC_X_GRID_OFFS_FX32-(FX32_ONE/2))
///�����\���ʒu�@�O���b�h����̃I�t�Z�b�gZ
#define NGRASS_GIRD_VEC_OFFS_Z \
	(FLDOBJ_VEC_Z_GRID_OFFS_FX32+FLDOBJ_BLACT_Z_GROUND_OFFS_FX32-NUM_FX32(1))
/*
#define NGRASS_GIRD_VEC_OFFS_Z \
	(FLDOBJ_VEC_Z_GRID_OFFS_FX32+FLDOBJ_BLACT_Z_GROUND_OFFS_FX32+(FX32_ONE*4))
*/
///�����\���ʒu�@�n�ʂ���̃I�t�Z�b�gY
#define NGRASS_GROUND_OFFS_Y (-NUM_FX32(8))

///�����h��A�j���t���[����
#define NGRASS_SHAKE_FRAME (2)

//==============================================================================
//	typedef struct
//==============================================================================
//--------------------------------------------------------------
///	FE_NGRASS_PTR�^
//--------------------------------------------------------------
typedef struct _TAG_FE_NGRASS * FE_NGRASS_PTR;

//--------------------------------------------------------------
///	FE_NGRASS�\����
//--------------------------------------------------------------
typedef struct _TAG_FE_NGRASS
{
	FE_SYS *fes;
}FE_NGRASS;

#define FE_NGRASS_SIZE (sizeof(FE_NGRASS))	///<FE_GRASS�T�C�Y

//--------------------------------------------------------------
///	NGRASS_ADD_H�\����
//--------------------------------------------------------------
typedef struct
{
	int init_gx;								///<����X �O���b�h
	int init_gy;								///<����Y
	int init_gz;								///<����Z
	FIELDSYS_WORK *fsys;						///<FIELDSYS_WORK *
	FE_SYS *fes;								///<FE_SYS_PTR
	FE_NGRASS_PTR kusa;							///<FE_GRASS_PTR
	FIELD_OBJ_PTR fldobj;						///<�Ώۂ�FIELD_OBJ_PTR
}NGRASS_ADD_H;

#define NGRASS_ADD_H_SIZE (sizeof(NGRASS_ADD_H))	///<NGRASS_ADD_H�T�C�Y

//--------------------------------------------------------------
///	NGRASS_WORK�\����
//--------------------------------------------------------------
typedef struct
{
	int seq_no;									///<����ԍ�
	int obj_code;								///<�Ώۃt�B�[���hOBJ OBJ CODE
	int obj_id;									///<�Ώۃt�B�[���hOBJ OBJ ID
	int zone_id;								///<�Ώۃt�B�[���hOBJ ZONE ID
	int frame;									///<�t���[��
	int height_get;								///<�����擾
	NGRASS_ADD_H head;							///<�ǉ�����NGRASS_ADD_H
	BLACT_WORK_PTR act;							///<�r���{�[�h�A�N�^�[
}NGRASS_WORK;

#define NGRASS_WORK_SIZE (sizeof(NGRASS_WORK))	///<NGRASS_WORK�T�C�Y

//==============================================================================
//	�v���g�^�C�v
//==============================================================================
static void NGrass_GraphicInit( FE_NGRASS_PTR ngrass );
static void NGrass_GraphicDelete( FE_NGRASS_PTR ngrass );

static const EOA_H_NPP DATA_EoaH_NGrass;
const BLACT_ANIME_TBL DATA_BlActAnmTbl_NGrass[];


const BLACT_ANIME_TBL DATA_BlActAnmTbl_NGrassSmall[];
const BLACT_ANIME_TBL DATA_BlActAnmTbl_NGrassBig[];
const BLACT_ANIME_TBL DATA_BlActAnmTbl_NGrassKiraKira[];

//==============================================================================
//	����	�V�X�e��
//==============================================================================
//--------------------------------------------------------------
/**
 * ����������
 * @param	fes		FE_SYS_PTR
 * @retval	FE_NGRASS_PTR	FE_GRASS_PTR
 */
//--------------------------------------------------------------
void * FE_NGrass_Init( FE_SYS *fes )
{
	FE_NGRASS_PTR kusa;
	
	kusa = FE_AllocClearMemory( fes, FE_NGRASS_SIZE, ALLOC_FR, 0 );
	kusa->fes = fes;
	
	NGrass_GraphicInit( kusa );
	return( kusa );
}

//--------------------------------------------------------------
/**
 * �����폜
 * @param	kusa		FE_NGRASS_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_NGrass_Delete( void *work )
{
	FE_NGRASS_PTR kusa = work;
	NGrass_GraphicDelete( kusa );
	FE_FreeMemory( kusa );
}

//==============================================================================
//	�����@�O���t�B�b�N
//==============================================================================
//--------------------------------------------------------------
/**
 * �����@�O���t�B�b�N������
 * @param	kusa	FE_NGRASS_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void NGrass_GraphicInit( FE_NGRASS_PTR kusa )
{
	FE_BlActResAdd_MdlArc( kusa->fes, FE_RESID_MDL_NGRASS, NARC_fldeff_ngrass_ani1_nsbmd );
	FE_BlActResAdd_AnmArc( kusa->fes, FE_RESID_ANM_NGRASS, NARC_fldeff_ngrass_ani1_itpcv_dat );
	FE_BlActResAdd_TexArc( kusa->fes,
			FE_RESID_TEX_NGRASS, NARC_fldeff_ngrass_ani1_nsbtx, TEXRESM_TEX_CUT_TRUE );
	
	FE_BlActHeaderManageAddResmID( kusa->fes, FE_BLACT_H_ID_NGRASS,
			FE_RESID_MDL_NGRASS, FE_RESID_ANM_NGRASS,
			FE_RESID_TEX_NGRASS, FE_BLACT_TEX_VRAM,
			DATA_BlActAnmTbl_NGrass );
}

//--------------------------------------------------------------
/**
 * �����@�O���t�B�b�N�폜
 * @param	kusa	FE_NGRASS_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void NGrass_GraphicDelete( FE_NGRASS_PTR kusa )
{
	FE_BlActResDelete_Mdl( kusa->fes, FE_RESID_MDL_NGRASS );
	FE_BlActResDelete_Anm( kusa->fes, FE_RESID_ANM_NGRASS );
	FE_BlActResDelete_Tex( kusa->fes, FE_RESID_TEX_NGRASS );
	FE_BlActHeaderManageFree( kusa->fes, FE_BLACT_H_ID_NGRASS );
}

//==============================================================================
//	�����p�[�c
//==============================================================================

//==============================================================================
//	�����@EOA
//==============================================================================
//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ�p�����ǉ�
 * @param	fldobj		FIELD_OBJ_PTR
 * @param	shake		TRUE=������ꂩ��J�n�BFALSE=�h��Ȃ�����J�n
 * @retval	nothing		
 */
//--------------------------------------------------------------
void FE_FldOBJNGrass_Add( FIELD_OBJ_PTR fldobj, int shake )
{
	int pri;
	VecFx32 mtx;
	NGRASS_ADD_H head;
	FE_SYS *fes;
	EOA_PTR eoa;
	
	fes = FE_FieldOBJ_FE_SYS_Get( fldobj );
	
	head.init_gx = FieldOBJ_NowPosGX_Get( fldobj );
	head.init_gy = FieldOBJ_NowPosGY_Get( fldobj );
	head.init_gz = FieldOBJ_NowPosGZ_Get( fldobj );
	head.fes = fes;
	head.fsys = FE_FieldSysWorkGet( fes );
	head.kusa = FE_EffectWorkGet( fes, FE_FLD_NGRASS );
	head.fldobj = fldobj;
	
	FieldOBJ_VecPosGet( fldobj, &mtx );
	pri = FieldOBJ_TCBPriGet( fldobj, FLDOBJ_TCBPRI_OFFS_AFTER );
	eoa = FE_EoaAddNpp( fes, &DATA_EoaH_NGrass, &mtx, shake, &head, pri );
}

//--------------------------------------------------------------
/**
 * EOA �����@������
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	int		TRUE=����I���BFALSE=�ُ�I��
 */
//--------------------------------------------------------------
static int EoaNGrass_Init( EOA_PTR eoa, void *wk )
{
	int gx,gz;
	VecFx32 vec;
	NGRASS_WORK *work;
	const NGRASS_ADD_H *head;
	
	work = wk;
	head = EOA_AddPtrGet( eoa );
	
	work->head = *head;
	work->obj_code = FieldOBJ_OBJCodeGetSeedIn( work->head.fldobj );
	work->obj_id = FieldOBJ_OBJIDGet( work->head.fldobj );
	work->zone_id = FieldOBJ_ZoneIDGet( work->head.fldobj );
	
	vec.x = GRID_SIZE_FX32( work->head.init_gx );
	vec.z = GRID_SIZE_FX32( work->head.init_gz );
	vec.y = FieldOBJ_VecPosYGet( work->head.fldobj );
	work->height_get = FieldOBJTool_GetHeight( work->head.fsys, &vec );
	
	vec.x += NGRASS_GIRD_VEC_OFFS_X;
	vec.y += NGRASS_GROUND_OFFS_Y;
	vec.z += NGRASS_GIRD_VEC_OFFS_Z;
	EOA_MatrixSet( eoa, &vec );
	
	work->act = FE_BlActAddID( work->head.fes, FE_BLACT_H_ID_NGRASS, &vec );
	
	if( EOA_AddParamGet(eoa) == FALSE ){						//�����h��Ȃ�
		work->seq_no = 1;
	}
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA �����@�폜
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaNGrass_Delete( EOA_PTR eoa, void *wk )
{
	NGRASS_WORK *work;
	
	work = wk;
	BLACT_Delete( work->act );
}

//--------------------------------------------------------------
/**
 * EOA �����@����
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaNGrass_Move( EOA_PTR eoa, void *wk )
{
	int frame;
	NGRASS_WORK *work;
	FIELD_OBJ_PTR fldobj;
	
	work = wk;
	fldobj = work->head.fldobj;
	
	if( FieldOBJ_CheckSameIDOBJCodeIn(
		fldobj,work->obj_code,work->obj_id,work->zone_id) == FALSE ){
		FE_EoaDelete( eoa );
		return;
	}
	
	if( work->height_get == FALSE ){
		VecFx32 mtx,vec;
		
		EOA_MatrixGet( eoa, &mtx );
		
		vec.x = GRID_SIZE_FX32( work->head.init_gx );
		vec.z = GRID_SIZE_FX32( work->head.init_gz );
		vec.y = mtx.y;
		
		work->height_get = FieldOBJTool_GetHeight( work->head.fsys, &vec );
		
		if( work->height_get == TRUE ){
			mtx.y = vec.y;
			EOA_MatrixSet( eoa, &mtx );
		}
	}
	
	switch( work->seq_no ){
	case 0:													//�h��
		BLACT_AnmFrameChg( work->act, FX32_ONE );
		frame = FX32_NUM( BLACT_AnmFrameGetOffs(work->act) );
		
		if( frame >= NGRASS_SHAKE_FRAME ){
			work->seq_no = 1;
		}
		
		break;
	case 1:
		BLACT_AnmFrameSet( work->act, NUM_FX32(NGRASS_SHAKE_FRAME) );
		BLACT_AnmFrameChg( work->act, 0 );
		work->seq_no = 2;
	case 2:
		{
			int gx = FieldOBJ_NowPosGX_Get( fldobj );
			int gz = FieldOBJ_NowPosGZ_Get( fldobj );
			
			if( work->head.init_gx != gx || work->head.init_gz != gz ){
				FE_EoaDelete( eoa );
				return;
			}
		}
		
		break;
	}
}

//--------------------------------------------------------------
/**
 * EOA �����@�`��
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaNGrass_Draw( EOA_PTR eoa, void *wk )
{
	VecFx32 vec;
	NGRASS_WORK *work;
	FIELD_OBJ_PTR fldobj;
	
	work = wk;
	fldobj = work->head.fldobj;
	
	if( FieldOBJ_CheckSameID(fldobj,work->obj_id,work->zone_id) == FALSE ){
		FE_EoaDelete( eoa );
		return;
	}
	
	EOA_MatrixGet( eoa, &vec );
	BLACT_MatrixSet( work->act, &vec );
}

//--------------------------------------------------------------
///	����EOA_H
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_NGrass =
{
	NGRASS_WORK_SIZE,
	EoaNGrass_Init,
	EoaNGrass_Delete,
	EoaNGrass_Move,
	EoaNGrass_Draw,
};

//--------------------------------------------------------------
///	�����A�j��
//--------------------------------------------------------------
static const BLACT_ANIME_TBL DATA_BlActAnmTbl_NGrass[] =
{
	{ 0, NGRASS_SHAKE_FRAME, BLACT_ANIM_LOOP },
	{ 0, 0, BLACT_ANIM_CMD_MAX },
};
