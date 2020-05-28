//******************************************************************************
/**
 * 
 * @file	fldeff_seed.c
 * @brief	�t�B�[���hOBJ�؂̎��֘A�G�t�F�N�g
 * @author	kagaya
 * @data	05.07.13
 *
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "field_effect.h"
#include "fieldobj.h"
#include "fldeff_seed.h"
#include "seedsys.h"

//==============================================================================
//	define
//==============================================================================
//--------------------------------------------------------------
///	�f�o�b�O
//--------------------------------------------------------------

//--------------------------------------------------------------
///	����C��ލő�
//--------------------------------------------------------------
#define SEEDGROUND_KIND (SEEDGROUND_FULL+1)

//--------------------------------------------------------------
///	�\���I�t�Z�b�g
//--------------------------------------------------------------
//#define SG_DRAW_Z_OFFSET (FX32_ONE*(3))
#define SG_DRAW_X_OFFSET (FX32_ONE*2)
#define SG_DRAW_Y_OFFSET (FX32_ONE*(0))
#define SG_DRAW_Z_OFFSET (FX32_ONE*(0))

//==============================================================================
//	typedef struct
//==============================================================================
//--------------------------------------------------------------
///	FE_SEEDGROUND�^
//--------------------------------------------------------------
typedef struct _TAG_FE_SEEDGROUND * FE_SEEDGROUND_PTR;

//--------------------------------------------------------------
///	FE_SEEDGROUND�\����
//--------------------------------------------------------------
typedef struct _TAG_FE_SEEDGROUND
{
	FE_SYS *fes;
	NNSG3dRenderObj render[SEEDGROUND_KIND];
	NNSG3dResMdl *model[SEEDGROUND_KIND];
	NNSG3dResFileHeader *res_file[SEEDGROUND_KIND];
}FE_SEEDGROUND;

#define FE_SEEDGROUND_SIZE (sizeof(FE_SEEDGROUND)) ///<FE_SEEDGROUND�T�C�Y

//--------------------------------------------------------------
///	SEEDGROUND_ADD_H�\����
//--------------------------------------------------------------
typedef struct
{
	FE_SYS *fes;								///<FE_SYS_PTR
	FE_SEEDGROUND_PTR sg;						///<FE_SEEDGROUND_PTR
	FIELD_OBJ_PTR fldobj;						///<�؂̎��y�̑Ώ�FIELD_OBJ_PTR
}SEEDGROUND_ADD_H;

#define SEEDGROUND_ADD_H_SIZE (sizeof(SEEDGROUND_ADD_H)) ///<SEEDGROUND_ADD_H�T�C�Y

//--------------------------------------------------------------
///	SG_WORK�\����
//--------------------------------------------------------------
typedef struct
{
	int obj_id;									///<�؂̎��y�Ώ�OBJID
	int zone_id;								///<�؂̎��y�Ώۃ]�[��ID
	int vanish_sw;								///<��\��SW
	int dry;									///<�����
	SEEDGROUND_ADD_H head;						///<�ǉ�����SEEDGROUND_ADD_H
}SG_WORK;

#define SG_WORK_SIZE (sizeof(SG_WORK))			///<SG_WORK�T�C�Y

//--------------------------------------------------------------
///	FE_SEED_EFF�\����
//--------------------------------------------------------------
typedef struct
{
	int add_count;
	int draw_init;
	FE_SYS *fes;
}FE_SEED_EFF;

#define FE_SEED_EFF_SIZE (sizeof(FE_SEED_EFF))

//--------------------------------------------------------------
///	SEED_EFF_ADD_H�\����
//--------------------------------------------------------------
typedef struct
{
	FE_SYS *fes;								///<FE_SYS_PTR
	FE_SEED_EFF *seedeff;						///<FE_SEED_EFF
	FIELD_OBJ_PTR fldobj;						///<�Ώ�FIELD_OBJ_PTR
}SEED_EFF_ADD_H;

//--------------------------------------------------------------
///	SEED_EFF_WORK�\����
//--------------------------------------------------------------
typedef struct
{
	int seq_no;									///<����ԍ�
	int count;									///<�J�E���g
	int frame_init;								///<�t���[��
	SEED_EFF_ADD_H head;						///<�ǉ�����SEED_EFF_ADD_H
	BLACT_WORK_PTR act;							///<�r���{�[�h�A�N�^�[
}SEED_EFF_WORK;

//==============================================================================
//	�v���g�^�C�v
//==============================================================================
static void SG_GraphicInit( FE_SEEDGROUND_PTR sd );
static void SG_GraphicDelete( FE_SEEDGROUND_PTR sd );

static const EOA_H_NPP DATA_EoaH_SeedGround;

static void SeedEff_AddCountUp( FE_SEED_EFF *seedeff );
static void SeedEff_AddCountDown( FE_SEED_EFF *seedeff );
static void SeedEff_GraphicInit( FE_SEED_EFF *seedeff );
static void SeedEff_GraphicDelete( FE_SEED_EFF *seedeff );
static void SeedEff_GraphicCheckInit( FE_SEED_EFF *seedeff );
static void SeedEff_GraphicCheckDelete( FE_SEED_EFF *seedeff );

static const EOA_H_NPP DATA_EoaH_SeedEff;
static const u32 DATA_SeedGroundMdlArcIDTbl[SEEDGROUND_KIND];
const BLACT_ANIME_TBL DATA_BlActAnmTbl_SeedEff[];

//==============================================================================
//	�؂̎��y�@�V�X�e��
//==============================================================================
//--------------------------------------------------------------
/**
 * �؂̎��y������
 * @param	fes		FE_SYS_PTR
 * @retval	FE_SEEDGROUND_PTR	FE_SEEDGROUND_PTR
 */
//--------------------------------------------------------------
void * FE_SeedGround_Init( FE_SYS *fes )
{
	FE_SEEDGROUND_PTR sg;
	
	sg = FE_AllocClearMemory( fes, FE_SEEDGROUND_SIZE, ALLOC_FR, 0 );
	sg->fes = fes;
	
	SG_GraphicInit( sg );
	return( sg );
}

//--------------------------------------------------------------
/**
 * �؂̎��y�폜
 * @param	sd		FE_SEEDGROUND_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_SeedGround_Delete( void *work )
{
	FE_SEEDGROUND_PTR sg = work;
	SG_GraphicDelete( sg );
	FE_FreeMemory( sg );
}

//==============================================================================
//	�؂̎��y	�p�[�c
//==============================================================================

//==============================================================================
//	�؂̎��y�@�O���t�B�b�N
//==============================================================================
//--------------------------------------------------------------
/**
 * �؂̎��y �O���t�B�b�N������
 * @param	sg	FE_SEEDGROUND_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void SG_GraphicInit( FE_SEEDGROUND_PTR sg )
{
	int i = 0;
	
	do{
		FE_simple3DModelInit( sg->fes, DATA_SeedGroundMdlArcIDTbl[i], ALLOC_FR,
			&sg->render[i], &sg->model[i], &sg->res_file[i] );
		i++;
	}while( i < SEEDGROUND_KIND );
}

//--------------------------------------------------------------
/**
 * �؂̎��y �O���t�B�b�N�폜
 * @param	sg	FE_SEEDGROUND_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void SG_GraphicDelete( FE_SEEDGROUND_PTR sg )
{
	int i = 0;
	
	do{
		FE_FreeMemory( sg->res_file[i] );
		i++;
	}while( i < SEEDGROUND_KIND );
}

//==============================================================================
//	�؂̎��y�@EOA
//==============================================================================
//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ�p�؂̎��y�ǉ�
 * @param	fldobj		FIELD_OBJ_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_FldOBJSeedGround_Add( FIELD_OBJ_PTR fldobj )
{
	int param,pri;
	SEEDGROUND_ADD_H head;
	FE_SYS *fes;
	VecFx32 mtx;
	
	fes = FE_FieldOBJ_FE_SYS_Get( fldobj );
	
	head.fes = fes;
	head.sg = FE_EffectWorkGet( fes, FE_FLD_SEEDGROUND );
	head.fldobj = fldobj;
	
	FieldOBJ_VecPosGet( fldobj, &mtx );
	
	param = 0;	//�����I�ɂ͂Ȃ񂩂̃p�����^
	
	pri = FieldOBJ_TCBStandardPriorityGet( fldobj ) + 1;	//�t�B�[���hOBJ�������������
	FE_EoaAddNpp( fes, &DATA_EoaH_SeedGround, &mtx, param, &head, pri );
}

//--------------------------------------------------------------
/**
 * EOA �؂̎��y�@������
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	int		TRUE=����I���BFALSE=�ُ�I��
 */
//--------------------------------------------------------------
static int EoaSeedGround_Init( EOA_PTR eoa, void *wk )
{
	SG_WORK *work;
	const SEEDGROUND_ADD_H *head;
	
	work = wk;
	head = EOA_AddPtrGet( eoa );
	work->head = *head;
	
	work->obj_id = FieldOBJ_OBJIDGet( work->head.fldobj );
	work->zone_id = FieldOBJ_ZoneIDGet( work->head.fldobj );
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA �؂̎��y�@�폜
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaSeedGround_Delete( EOA_PTR eoa, void *wk )
{
}

//--------------------------------------------------------------
/**
 * EOA �؂̎��y�@����
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaSeedGround_Move( EOA_PTR eoa, void *wk )
{
	SG_WORK *work;
	FIELD_OBJ_PTR fldobj;
	
	work = wk;
	fldobj = work->head.fldobj;
	
	if( FieldOBJ_CheckSameID(fldobj,work->obj_id,work->zone_id) == FALSE ){
		FE_EoaDelete( eoa );										//����ł͂Ȃ�
		return;
	}
	
	work->vanish_sw = FALSE;
	
	if( FieldOBJ_StatusBit_CheckEasy(fldobj,FLDOBJ_STA_BIT_VANISH) == TRUE || 
		SeedSys_GetSeedStatus(FieldOBJ_FieldSysWorkGet(fldobj),fldobj) == SEEDSTAT_NOTHING ){
		work->vanish_sw = TRUE;									//��\��
		return;
	}
	
	{
		work->dry = SeedSys_GetGroundStatus( FieldOBJ_FieldSysWorkGet(fldobj), fldobj );
	}
	
	{
		VecFx32 vec;
		
		FieldOBJ_VecPosGet( fldobj, &vec );
		EOA_MatrixSet( eoa, &vec );
	}
}

//--------------------------------------------------------------
/**
 * EOA �؂̎��y�@�`��
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaSeedGround_Draw( EOA_PTR eoa, void *wk )
{
	SG_WORK *work;
	
	work = wk;
	
	if( work->vanish_sw == TRUE ){
		return;
	}
	
	{
		VecFx32 vec;
		VecFx32 scale = { FX32_ONE, FX32_ONE, FX32_ONE };
		MtxFx33 rot	  = { FX32_ONE, 0,0,0, FX32_ONE, 0,0,0,FX32_ONE};
		
		EOA_MatrixGet( eoa, &vec );
		
		vec.z += SG_DRAW_Z_OFFSET;
		simple_3DModelDraw( &work->head.sg->render[work->dry], &vec, &rot, &scale );
	}
}

//--------------------------------------------------------------
///	�؂̎��yEOA_H
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_SeedGround =
{
	SG_WORK_SIZE,
	EoaSeedGround_Init,
	EoaSeedGround_Delete,
	EoaSeedGround_Move,
	EoaSeedGround_Draw,
};

//==============================================================================
//	�؂̎��L���L���G�t�F�N�g
//==============================================================================
//--------------------------------------------------------------
/**
 * �؂̎��G�t�F�N�g�@������
 * @param	fes	FE_SYS_PTR
 * @retval	void* FE_SEED_EFF *
 */
//--------------------------------------------------------------
void * FE_SeedEff_Init( FE_SYS *fes )
{
	FE_SEED_EFF *seedeff;
	
	seedeff = FE_AllocClearMemory( fes, FE_SEED_EFF_SIZE, ALLOC_FR, 0 );
	seedeff->fes = fes;
	
	return( seedeff );
}

//--------------------------------------------------------------
/**
 * �؂̎��G�t�F�N�g�@�폜
 * @param	work	FE_SEED_EFF
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_SeedEff_Delete( void *work )
{
	FE_SEED_EFF *seedeff = work;
	SeedEff_GraphicDelete( seedeff );
	FE_FreeMemory( seedeff );
}

//--------------------------------------------------------------
/**
 * �G�t�F�N�g���J�E���g
 * @param	seedeff	FE_SEED_EFF
 * @retval	nothing
 */
//--------------------------------------------------------------
static void SeedEff_AddCountUp( FE_SEED_EFF *seedeff )
{
	seedeff->add_count++;
}

//--------------------------------------------------------------
/**
 * �G�t�F�N�g���f�N�������g
 * @param	seedeff	FE_SEED_EFF
 * @retval	nothing
 */
//--------------------------------------------------------------
static void SeedEff_AddCountDown( FE_SEED_EFF *seedeff )
{
	seedeff->add_count--;
	
	GF_ASSERT( seedeff->add_count >= 0 &&
		"SeedEff_AddCountDown()�@�ǉ��ƍ폜�̉񐔂�����Ȃ�" );
}

//--------------------------------------------------------------
/**
 * �G�t�F�N�g �O���t�B�b�N������
 * @param	seedeff	FE_SEED_EFF
 * @retval	nothing
 */
//--------------------------------------------------------------
static void SeedEff_GraphicInit( FE_SEED_EFF *seedeff )
{
	if( seedeff->draw_init == FALSE ){
		seedeff->draw_init = TRUE;
		FE_BlActResAdd_MdlArc( seedeff->fes, FE_RESID_MDL_SEED_EFF, NARC_fldeff_seed_kira_nsbmd );
		FE_BlActResAdd_AnmArc( seedeff->fes, FE_RESID_ANM_SEED_EFF, NARC_fldeff_seed_kira_itpcv_dat );
		FE_BlActResAdd_TexArc( seedeff->fes,
			FE_RESID_TEX_SEED_EFF, NARC_fldeff_seed_kira_nsbtx, TEXRESM_TEX_CUT_TRUE );
		
		FE_BlActHeaderManageAddResmID( seedeff->fes, FE_BLACT_H_ID_SEED_EFF,
			FE_RESID_MDL_SEED_EFF, FE_RESID_ANM_SEED_EFF,
			FE_RESID_TEX_SEED_EFF, FE_BLACT_TEX_VRAM,
			DATA_BlActAnmTbl_SeedEff );
	}
}

//--------------------------------------------------------------
/**
 * ���傦�[ �O���t�B�b�N�폜
 * @param	seedeff	FE_SEED_EFF
 * @retval	nothing
 */
//--------------------------------------------------------------
static void SeedEff_GraphicDelete( FE_SEED_EFF *seedeff )
{
	if( seedeff->draw_init == TRUE ){
		seedeff->draw_init = FALSE;
		
		FE_BlActResDelete_Mdl( seedeff->fes, FE_RESID_MDL_SEED_EFF );
		FE_BlActResDelete_Anm( seedeff->fes, FE_RESID_ANM_SEED_EFF );
		FE_BlActResDelete_Tex( seedeff->fes, FE_RESID_TEX_SEED_EFF );
		FE_BlActHeaderManageFree( seedeff->fes, FE_BLACT_H_ID_SEED_EFF );
	}
}

//--------------------------------------------------------------
/**
 * ������O���t�B�b�N������
 * @param	seedeff FE_SEED_EFF
 * @retval	nothing
 */
//--------------------------------------------------------------
static void SeedEff_GraphicCheckInit( FE_SEED_EFF *seedeff )
{
	if( seedeff->add_count == 0 ){
		SeedEff_GraphicInit( seedeff );
	}
}

//--------------------------------------------------------------
/**
 * ������O���t�B�b�N�폜
 * @param	seedeff FE_SEED_EFF
 * @retval	nothing
 */
//--------------------------------------------------------------
static void SeedEff_GraphicCheckDelete( FE_SEED_EFF *seedeff )
{
	if( seedeff->add_count == 0 ){
		SeedEff_GraphicDelete( seedeff );
	}
}

//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ �؂̎��G�t�F�N�g�ǉ�
 * @param	fldobj		FIELD_OBJ_PTR
 * @retval	EOA_PTR		�ǉ�EOA_PTR
 */
//--------------------------------------------------------------
EOA_PTR FE_FldOBJSeedEff_Add( FIELD_OBJ_PTR fldobj )
{
	VecFx32 mtx;
	FE_SYS *fes;
	SEED_EFF_ADD_H head;
	EOA_PTR eoa;
	
	fes = FE_FieldOBJ_FE_SYS_Get( fldobj );
	FieldOBJ_DrawVecPosTotalGet( fldobj, &mtx );
	mtx.z += (FX32_ONE*8);
	
	head.fes = fes;
	head.seedeff = FE_EffectWorkGet( fes, FE_FLD_SEED_EFF );
	eoa = FE_EoaAddNpp( fes, &DATA_EoaH_SeedEff, &mtx, 0, &head, 0xff );
	
	return( eoa );
}

//--------------------------------------------------------------
/**
 * EOA �؂̎��G�t�F�N�g�@������
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	int		TRUE=����I���BFALSE=�ُ�I��
 */
//--------------------------------------------------------------
static int EoaSeedEff_Init( EOA_PTR eoa, void *wk )
{
	VecFx32 vec;
	SEED_EFF_WORK *work;
	const SEED_EFF_ADD_H *head;
	
	work = wk;
	head = EOA_AddPtrGet( eoa );
	work->head = *head;
	
	SeedEff_GraphicCheckInit( work->head.seedeff );				//�O���t�B�b�N������
	
	EOA_MatrixGet( eoa, &vec );
	work->act = FE_BlActAddID( work->head.fes, FE_BLACT_H_ID_SEED_EFF, &vec );
	SeedEff_AddCountUp( work->head.seedeff );
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA �؂̎��G�t�F�N�g�@�폜
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaSeedEff_Delete( EOA_PTR eoa, void *wk )
{
	SEED_EFF_WORK *work;
	
	work = wk;
	
	BLACT_Delete( work->act );									//�A�N�^�[�폜
	SeedEff_AddCountDown( work->head.seedeff );					//�J�E���g�_�E��
	SeedEff_GraphicCheckDelete( work->head.seedeff );			//�O���t�B�b�N�폜
}

//--------------------------------------------------------------
/**
 * EOA �؂̎��G�t�F�N�g�@����
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaSeedEff_Move( EOA_PTR eoa, void *wk )
{
	fx32 frame[5] = { 0x1000, 0x1000, 0x2000, 0x2000, 0x1000 };
	SEED_EFF_WORK *work = wk;
	
	if( work->frame_init == TRUE ){
		work->frame_init = FALSE;
		work->count++;
		
		if( work->count >= 5 ){
			FE_EoaDelete( eoa );
			return;
		}
		
		BLACT_AnmFrameSet( work->act, 0 );
	}
		
	if( BLACT_AnmFrameChg(work->act,frame[work->count]) != BLACT_ANISTA_END ){
		return;
	}
	
	work->frame_init = TRUE;
}

//--------------------------------------------------------------
/**
 * EOA �؂̎��G�t�F�N�g�@�`��
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaSeedEff_Draw( EOA_PTR eoa, void *wk )
{
	VecFx32 vec;
	SEED_EFF_WORK *work;
	
	work = wk;
	
	EOA_MatrixGet( eoa, &vec );
	BLACT_MatrixSet( work->act, &vec );
}

//--------------------------------------------------------------
/// �؂̎��G�t�F�N�gEOA_H
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_SeedEff =
{
	sizeof(SEED_EFF_WORK),
	EoaSeedEff_Init,
	EoaSeedEff_Delete,
	EoaSeedEff_Move,
	EoaSeedEff_Draw,
};

//==============================================================================
//	data
//==============================================================================
//--------------------------------------------------------------
///	�탂�f�����O�f�[�^�t�@�C���p�X�e�[�u���BSEEDGROUND_DRY�̕��тɈ�v
//--------------------------------------------------------------
static const u32 DATA_SeedGroundMdlArcIDTbl[SEEDGROUND_KIND] =
{
	NARC_fldeff_seed_ground03_nsbmd,
	NARC_fldeff_seed_ground02_nsbmd,
	NARC_fldeff_seed_ground01_nsbmd,
};

//--------------------------------------------------------------
///	�؂̎��G�t�F�N�g
//--------------------------------------------------------------
static const BLACT_ANIME_TBL DATA_BlActAnmTbl_SeedEff[] =
{
	{ 0, 9, BLACT_ANIM_END },
	{ 0, 0, BLACT_ANIM_CMD_MAX },
};
