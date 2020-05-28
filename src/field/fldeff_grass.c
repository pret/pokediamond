//******************************************************************************
/**
 * 
 * @file	fldeff_grass.c
 * @brief	�t�B�[���hOBJ��
 * @author	kagaya
 * @data	05.07.13
 *
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "field_effect.h"
#include "fieldobj.h"

#include "fldeff_grass.h"
#include "map_tool.h"

//==============================================================================
//	define
//==============================================================================
#define YURE_KUSA_SET

///���\���ʒu�@�O���b�h����̃I�t�Z�b�gX
#define GRASS_GIRD_VEC_OFFS_X (FLDOBJ_VEC_X_GRID_OFFS_FX32)
///���\���ʒu�@�O���b�h����̃I�t�Z�b�gZ
//#define GRASS_GIRD_VEC_OFFS_Z (FLDOBJ_VEC_Z_GRID_OFFS_FX32+FLDOBJ_BLACT_Z_GROUND_OFFS_FX32);
#define GRASS_GIRD_VEC_OFFS_Z \
	(FLDOBJ_VEC_Z_GRID_OFFS_FX32+FLDOBJ_BLACT_Z_GROUND_OFFS_FX32+(FX32_ONE*4))
///���\���ʒu�@�n�ʂ���̃I�t�Z�b�gY
#define GRASS_GROUND_OFFS_Y (FX32_ONE)

///���h��A�j���t���[����
#define GRASS_SHAKE_FRAME (12)

//==============================================================================
//	typedef struct
//==============================================================================
//--------------------------------------------------------------
///	FE_GRASS�\����
//--------------------------------------------------------------
typedef struct _TAG_FE_GRASS
{
	FE_SYS *fes;
}FE_GRASS;

#define FE_GRASS_SIZE (sizeof(FE_GRASS))	///<FE_GRASS�T�C�Y

//--------------------------------------------------------------
///	GRASS_ADD_H�\����
//--------------------------------------------------------------
typedef struct
{
	int init_gx;								///<����X �O���b�h
	int init_gy;								///<����Y
	int init_gz;								///<����Z
	FIELDSYS_WORK *fsys;						///<FIELDSYS_WORK *
	FE_SYS *fes;								///<FE_SYS_PTR
	FE_GRASS_PTR kusa;							///<FE_GRASS_PTR
	FIELD_OBJ_PTR fldobj;						///<�Ώۂ�FIELD_OBJ_PTR
}GRASS_ADD_H;

#define GRASS_ADD_H_SIZE (sizeof(GRASS_ADD_H))	///<GRASS_ADD_H�T�C�Y

//--------------------------------------------------------------
///	GRASS_WORK�\����
//--------------------------------------------------------------
typedef struct
{
	int seq_no;									///<����ԍ�
	int obj_code;								///<�Ώۃt�B�[���hOBJ OBJ CODE
	int obj_id;									///<�Ώۃt�B�[���hOBJ OBJ ID
	int zone_id;								///<�Ώۃt�B�[���hOBJ ZONE ID
	int frame;									///<�t���[��
	int height_get;								///<�����擾
	GRASS_ADD_H head;							///<�ǉ�����GRASS_ADD_H
	BLACT_WORK_PTR act;							///<�r���{�[�h�A�N�^�[
}GRASS_WORK;

#define GRASS_WORK_SIZE (sizeof(GRASS_WORK))	///<GRASS_WORK�T�C�Y

//==============================================================================
//	�v���g�^�C�v
//==============================================================================
static void Grass_GraphicInit( FE_GRASS_PTR grass );
static void Grass_GraphicDelete( FE_GRASS_PTR grass );

static const EOA_H_NPP DATA_EoaH_Grass;
const BLACT_ANIME_TBL DATA_BlActAnmTbl_Grass[];

const BLACT_ANIME_TBL DATA_BlActAnmTbl_GrassSmall[];
const BLACT_ANIME_TBL DATA_BlActAnmTbl_GrassBig[];
const BLACT_ANIME_TBL DATA_BlActAnmTbl_GrassKiraKira[];

//==============================================================================
//	��	�V�X�e��
//==============================================================================
//--------------------------------------------------------------
/**
 * ��������
 * @param	fes		FE_SYS_PTR
 * @retval	FE_GRASS_PTR	FE_GRASS_PTR
 */
//--------------------------------------------------------------
void * FE_Grass_Init( FE_SYS *fes )
{
	FE_GRASS_PTR kusa;
	
	kusa = FE_AllocClearMemory( fes, FE_GRASS_SIZE, ALLOC_FR, 0 );
	kusa->fes = fes;
	
	Grass_GraphicInit( kusa );
	return( kusa );
}

//--------------------------------------------------------------
/**
 * ���폜
 * @param	kusa		FE_GRASS_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_Grass_Delete( void *work )
{
	FE_GRASS_PTR kusa = work;
	Grass_GraphicDelete( kusa );
	FE_FreeMemory( kusa );
}

//==============================================================================
//	���@�O���t�B�b�N
//==============================================================================
//--------------------------------------------------------------
/**
 * ���@�O���t�B�b�N������
 * @param	kusa	FE_GRASS_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Grass_GraphicInit( FE_GRASS_PTR kusa )
{
	FE_BlActResAdd_MdlArc( kusa->fes,
			FE_RESID_MDL_GRASS, NARC_fldeff_kusaeff_nsbmd );
	FE_BlActResAdd_MdlArc( kusa->fes,
			FE_RESID_MDL_GRASS_ENCOUNT, NARC_fldeff_e_kusaeff1_nsbmd );
	
	FE_BlActResAdd_AnmArc( kusa->fes,
			FE_RESID_ANM_GRASS, NARC_fldeff_kusaeff_itpcv_dat );
	FE_BlActResAdd_AnmArc( kusa->fes,
			FE_RESID_ANM_GRASS_ENCOUNT_SMALL, NARC_fldeff_e_kusaeff1_itpcv_dat );
	FE_BlActResAdd_AnmArc( kusa->fes, 
			FE_RESID_ANM_GRASS_ENCOUNT_BIG,NARC_fldeff_e_kusaeff2_itpcv_dat );
	FE_BlActResAdd_AnmArc( kusa->fes,
			FE_RESID_ANM_GRASS_ENCOUNT_KIRAKIRA, NARC_fldeff_e_kusaeff3_itpcv_dat );
	
	FE_BlActResAdd_TexArc( kusa->fes, FE_RESID_TEX_GRASS,
			NARC_fldeff_kusaeff_nsbtx, TEXRESM_TEX_CUT_TRUE );
	FE_BlActResAdd_TexArc( kusa->fes, FE_RESID_TEX_GRASS_ENCOUNT_SMALL,
			NARC_fldeff_e_kusaeff1_nsbtx, TEXRESM_TEX_CUT_TRUE );
	FE_BlActResAdd_TexArc( kusa->fes, FE_RESID_TEX_GRASS_ENCOUNT_BIG,
			NARC_fldeff_e_kusaeff2_nsbtx, TEXRESM_TEX_CUT_TRUE );
	FE_BlActResAdd_TexArc( kusa->fes, FE_RESID_TEX_GRASS_ENCOUNT_KIRAKIRA,
			NARC_fldeff_e_kusaeff3_nsbtx, TEXRESM_TEX_CUT_TRUE );
	
	FE_BlActHeaderManageAddResmID( kusa->fes, FE_BLACT_H_ID_GRASS,
			FE_RESID_MDL_GRASS, FE_RESID_ANM_GRASS,
			FE_RESID_TEX_GRASS, FE_BLACT_TEX_VRAM,
			DATA_BlActAnmTbl_Grass );
	FE_BlActHeaderManageAddResmID( kusa->fes, FE_BLACT_H_ID_GRASS_ENCOUNT_SMALL,
			FE_RESID_MDL_GRASS_ENCOUNT, FE_RESID_ANM_GRASS_ENCOUNT_SMALL,
			FE_RESID_TEX_GRASS_ENCOUNT_SMALL, FE_BLACT_TEX_VRAM,
			DATA_BlActAnmTbl_GrassSmall );
	FE_BlActHeaderManageAddResmID( kusa->fes, FE_BLACT_H_ID_GRASS_ENCOUNT_BIG,
			FE_RESID_MDL_GRASS_ENCOUNT, FE_RESID_ANM_GRASS_ENCOUNT_BIG,
			FE_RESID_TEX_GRASS_ENCOUNT_BIG, FE_BLACT_TEX_VRAM,
			DATA_BlActAnmTbl_GrassBig );
	
	FE_BlActHeaderManageAddResmID( kusa->fes, FE_BLACT_H_ID_GRASS_ENCOUNT_KIRAKIRA,
			FE_RESID_MDL_GRASS_ENCOUNT, FE_RESID_ANM_GRASS_ENCOUNT_KIRAKIRA,
			FE_RESID_TEX_GRASS_ENCOUNT_KIRAKIRA, FE_BLACT_TEX_VRAM,
			DATA_BlActAnmTbl_GrassKiraKira );
}

//--------------------------------------------------------------
/**
 * ���@�O���t�B�b�N�폜
 * @param	kusa	FE_GRASS_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Grass_GraphicDelete( FE_GRASS_PTR kusa )
{
	FE_BlActResDelete_Mdl( kusa->fes, FE_RESID_MDL_GRASS );
	FE_BlActResDelete_Mdl( kusa->fes, FE_RESID_MDL_GRASS_ENCOUNT );

	FE_BlActResDelete_Anm( kusa->fes, FE_RESID_ANM_GRASS );
	FE_BlActResDelete_Anm( kusa->fes, FE_RESID_ANM_GRASS_ENCOUNT_SMALL );
	
	FE_BlActResDelete_Anm( kusa->fes, FE_RESID_ANM_GRASS_ENCOUNT_BIG );
	FE_BlActResDelete_Anm( kusa->fes, FE_RESID_ANM_GRASS_ENCOUNT_KIRAKIRA );
	
	FE_BlActResDelete_Tex( kusa->fes, FE_RESID_TEX_GRASS );
	FE_BlActResDelete_Tex( kusa->fes, FE_RESID_TEX_GRASS_ENCOUNT_SMALL );
	FE_BlActResDelete_Tex( kusa->fes, FE_RESID_TEX_GRASS_ENCOUNT_BIG );
	FE_BlActResDelete_Tex( kusa->fes, FE_RESID_TEX_GRASS_ENCOUNT_KIRAKIRA );
	
	FE_BlActHeaderManageFree( kusa->fes, FE_BLACT_H_ID_GRASS );
	FE_BlActHeaderManageFree( kusa->fes, FE_BLACT_H_ID_GRASS_ENCOUNT_SMALL );
	FE_BlActHeaderManageFree( kusa->fes, FE_BLACT_H_ID_GRASS_ENCOUNT_BIG );
	FE_BlActHeaderManageFree( kusa->fes, FE_BLACT_H_ID_GRASS_ENCOUNT_KIRAKIRA );
}

//==============================================================================
//	���p�[�c
//==============================================================================

//==============================================================================
//	���@EOA
//==============================================================================
//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ�p���ǉ�
 * @param	fldobj		FIELD_OBJ_PTR
 * @param	shake		TRUE=����ꂩ��J�n�BFALSE=�h��Ȃ�����J�n
 * @retval	nothing		
 */
//--------------------------------------------------------------
void FE_FldOBJGrass_Add( FIELD_OBJ_PTR fldobj, int shake )
{
	int pri;
	VecFx32 mtx;
	GRASS_ADD_H head;
	FE_SYS *fes;
	EOA_PTR eoa;
	
	fes = FE_FieldOBJ_FE_SYS_Get( fldobj );
	
	head.init_gx = FieldOBJ_NowPosGX_Get( fldobj );
	head.init_gy = FieldOBJ_NowPosGY_Get( fldobj );
	head.init_gz = FieldOBJ_NowPosGZ_Get( fldobj );
	head.fes = fes;
	head.fsys = FE_FieldSysWorkGet( fes );
	head.kusa = FE_EffectWorkGet( fes, FE_FLD_GRASS );
	head.fldobj = fldobj;
	
	FieldOBJ_VecPosGet( fldobj, &mtx );
	pri = FieldOBJ_TCBPriGet( fldobj, FLDOBJ_TCBPRI_OFFS_AFTER );
	eoa = FE_EoaAddNpp( fes, &DATA_EoaH_Grass, &mtx, shake, &head, pri );
}

//--------------------------------------------------------------
/**
 * EOA ���@������
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	int		TRUE=����I���BFALSE=�ُ�I��
 */
//--------------------------------------------------------------
static int EoaGrass_Init( EOA_PTR eoa, void *wk )
{
	int gx,gz;
	VecFx32 vec;
	GRASS_WORK *work;
	const GRASS_ADD_H *head;
	
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
	
	vec.x += GRASS_GIRD_VEC_OFFS_X;
	vec.z += GRASS_GIRD_VEC_OFFS_Z;
	EOA_MatrixSet( eoa, &vec );
	
	work->act = FE_BlActAddID( work->head.fes, FE_BLACT_H_ID_GRASS, &vec );
	
	if( EOA_AddParamGet(eoa) == FALSE ){						//���h��Ȃ�
		work->seq_no = 1;
	}
	
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
static void EoaGrass_Delete( EOA_PTR eoa, void *wk )
{
	GRASS_WORK *work;
	
	work = wk;
	BLACT_Delete( work->act );
}

//--------------------------------------------------------------
/**
 * EOA ���@����
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaGrass_Move( EOA_PTR eoa, void *wk )
{
	int frame;
	GRASS_WORK *work;
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
		frame = BLACT_AnmFrameGetOffs( work->act ) / FX32_ONE;
		
		if( frame >= GRASS_SHAKE_FRAME ){
			work->seq_no = 1;
		}
		
		break;
	case 1:
		BLACT_AnmFrameSet( work->act, (GRASS_SHAKE_FRAME*FX32_ONE) );
		work->seq_no = 2;
	case 2:
		if( FieldOBJ_CheckSameIDOBJCodeIn(
			fldobj,work->obj_code,work->obj_id,work->zone_id) == FALSE ){
			FE_EoaDelete( eoa );
			return;
		}
		
		{
			int gx,gz;
			
			gx = FieldOBJ_NowPosGX_Get( fldobj );
			gz = FieldOBJ_NowPosGZ_Get( fldobj );
			
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
 * EOA ���@�`��
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaGrass_Draw( EOA_PTR eoa, void *wk )
{
	VecFx32 vec;
	GRASS_WORK *work;
	FIELD_OBJ_PTR fldobj;
	
	work = wk;
	fldobj = work->head.fldobj;
	
	if( FieldOBJ_CheckSameIDOBJCodeIn(
		fldobj,work->obj_code,work->obj_id,work->zone_id) == FALSE ){
		FE_EoaDelete( eoa );
		return;
	}
	
	EOA_MatrixGet( eoa, &vec );
	BLACT_MatrixSet( work->act, &vec );
}

//--------------------------------------------------------------
///	��EOA_H
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_Grass =
{
	GRASS_WORK_SIZE,
	EoaGrass_Init,
	EoaGrass_Delete,
	EoaGrass_Move,
	EoaGrass_Draw,
};

//--------------------------------------------------------------
///	���A�j��
//--------------------------------------------------------------
static const BLACT_ANIME_TBL DATA_BlActAnmTbl_Grass[] =
{
	{ 0, GRASS_SHAKE_FRAME, BLACT_ANIM_LOOP },
	{ 0, 0, BLACT_ANIM_CMD_MAX },
};

//==============================================================================
//	�n���
//==============================================================================
static const EOA_H_NPP DATA_EoaH_CommTrapGrass;

//--------------------------------------------------------------
//	TIKA_GRASS_ADD_H�\����
//--------------------------------------------------------------
typedef struct
{
	int init_gx;
	int init_gz;
	FIELDSYS_WORK *fsys;
	FE_SYS *fes;
	FE_GRASS_PTR kusa;
}TIKA_GRASS_ADD_H;

//--------------------------------------------------------------
//	�n�����p���[�N
//--------------------------------------------------------------
typedef struct
{
	int seq_no;
	int end_flag;
	TIKA_GRASS_ADD_H head;
	BLACT_WORK_PTR act;
}TIKA_GRASS_WORK;

#define TIKA_GRASS_WORK_SIZE (sizeof(TIKA_GRASS_WORK))

//--------------------------------------------------------------
/**
 * �n��㩗p���ǉ�
 * @param	fsys		FIELDSYS_WORK *
 * @param	x			�O���b�hX���W
 * @param	z			�O���b�hZ���W
 * @retval	EOA_PTR		������EOA_PTR
 */
//--------------------------------------------------------------
EOA_PTR FE_CommTrapGrass_Add( FIELDSYS_WORK *fsys, int x, int z )
{
	VecFx32 mtx;
	TIKA_GRASS_ADD_H head;
	FE_SYS *fes;
	EOA_PTR eoa;
	
	fes = fsys->fes;
	
	head.init_gx = x;
	head.init_gz = z;
	head.fes = fes;
	head.fsys = fsys;
	head.kusa = FE_EffectWorkGet( fes, FE_FLD_GRASS );
	
	mtx.x = GRID_SIZE_FX32( x ) + (FX32_ONE * 9 );
	mtx.y = 0;
	mtx.z = GRID_SIZE_FX32( z ) + (FX32_ONE * 15 );
	
	eoa = FE_EoaAddNpp( fes, &DATA_EoaH_CommTrapGrass, &mtx, 0, &head, 0xff );
	return( eoa );
}

//--------------------------------------------------------------
/**
 * �n��㩗p���A�j���I���`�F�b�N
 * @param	EOA_PTR		FE_CommTrapGrass_Add()�߂�l
 * @retval	int		TRUE=�I���BFALSE=�܂�
 */
//--------------------------------------------------------------
int FE_CommTrapGrass_AnimeCheck( EOA_PTR eoa )
{
	TIKA_GRASS_WORK *work;
	
	work = EOA_LocalWorkGet( eoa );
	return( work->end_flag );
}

//--------------------------------------------------------------
/**
 * EOA �n�����@������
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	int		TRUE=����I���BFALSE=�ُ�I��
 */
//--------------------------------------------------------------
static int EoaCommTrapGrass_Init( EOA_PTR eoa, void *wk )
{
	VecFx32 mtx;
	TIKA_GRASS_WORK *work;
	const TIKA_GRASS_ADD_H *head;
	
	work = wk;
	head = EOA_AddPtrGet( eoa );
	work->head = *head;
	
	EOA_MatrixGet( eoa, &mtx );
	work->act = FE_BlActAddID( work->head.fes, FE_BLACT_H_ID_GRASS, &mtx );
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA �n�����@�폜
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaCommTrapGrass_Delete( EOA_PTR eoa, void *wk )
{
	TIKA_GRASS_WORK *work;
	
	work = wk;
	BLACT_Delete( work->act );
}

//--------------------------------------------------------------
/**
 * EOA �n�����@����
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaCommTrapGrass_Move( EOA_PTR eoa, void *wk )
{
	int frame;
	TIKA_GRASS_WORK *work;
	
	work = wk;
	
	switch( work->seq_no ){
	case 0:													//�h��
		BLACT_AnmFrameChg( work->act, FX32_ONE );
		frame = BLACT_AnmFrameGetOffs( work->act ) / FX32_ONE;
		
		if( frame >= GRASS_SHAKE_FRAME ){
			work->end_flag = TRUE;
			work->seq_no = 1;
		}
		
		break;
	case 1:
		break;
	}
}

//--------------------------------------------------------------
/**
 * EOA �n�����@�`��
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaCommTrapGrass_Draw( EOA_PTR eoa, void *wk )
{
	VecFx32 mtx;
	TIKA_GRASS_WORK *work;
	
	work = wk;
	EOA_MatrixGet( eoa, &mtx );
	BLACT_MatrixSet( work->act, &mtx );
}

//--------------------------------------------------------------
///	��EOA_H
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_CommTrapGrass =
{
	TIKA_GRASS_WORK_SIZE,
	EoaCommTrapGrass_Init,
	EoaCommTrapGrass_Delete,
	EoaCommTrapGrass_Move,
	EoaCommTrapGrass_Draw,
};

//==============================================================================
//	��ꑐ�G���J�E���g
//==============================================================================
static const EOA_H_NPP DATA_EoaH_EncGrass;

//--------------------------------------------------------------
//	�\����
//--------------------------------------------------------------
typedef struct
{
	int init_gx;
	int init_gz;
	FIELDSYS_WORK *fsys;
	FE_SYS *fes;
	FE_GRASS_PTR kusa;
}ENC_GRASS_ADD_H;

//--------------------------------------------------------------
//	��ꑐ�p���[�N
//--------------------------------------------------------------
typedef struct
{
	int seq_no;
	int end_flag;
	int frame;
	FE_GRASS_TYPE type;
	ENC_GRASS_ADD_H head;
	BLACT_WORK_PTR act;
}ENC_GRASS_WORK;

#define ENC_GRASS_WORK_SIZE (sizeof(ENC_GRASS_WORK))

//--------------------------------------------------------------
///	���A�j��
//--------------------------------------------------------------
static const BLACT_ANIME_TBL DATA_BlActAnmTbl_GrassSmall[] =
{
	{ 0, 40, BLACT_ANIM_END },
	{ 0, 0, BLACT_ANIM_CMD_MAX },
};

//--------------------------------------------------------------
///	���A�j��
//--------------------------------------------------------------
static const BLACT_ANIME_TBL DATA_BlActAnmTbl_GrassBig[] =
{
	{ 0, 24, BLACT_ANIM_END },
	{ 0, 0, BLACT_ANIM_CMD_MAX },
};

//--------------------------------------------------------------
///	���A�j��
//--------------------------------------------------------------
static const BLACT_ANIME_TBL DATA_BlActAnmTbl_GrassKiraKira[] =
{
	{ 0, 40, BLACT_ANIM_END },
	{ 0, 0, BLACT_ANIM_CMD_MAX },
};

//--------------------------------------------------------------
/**
 * ��ꑐ�ǉ�
 * @param	fsys		FIELDSYS_WORK *
 * @param	x			�O���b�hX���W
 * @param	z			�O���b�hZ���W
 * @param	type		FE_GRASS_TYPE
 * @retval	EOA_PTR		������EOA_PTR
 */
//--------------------------------------------------------------
EOA_PTR FE_EncGrass_Add( FIELDSYS_WORK *fsys, int x, int z, FE_GRASS_TYPE type )
{
	VecFx32 mtx;
	ENC_GRASS_ADD_H head;
	FE_SYS *fes;
	EOA_PTR eoa;
	
	fes = fsys->fes;
	
	head.init_gx = x;
	head.init_gz = z;
	head.fes = fes;
	head.fsys = fsys;
	head.kusa = FE_EffectWorkGet( fes, FE_FLD_GRASS );
	
	mtx.x = GRID_SIZE_FX32( x ) + GRASS_GIRD_VEC_OFFS_X;
	mtx.y = 0;
	mtx.z = GRID_SIZE_FX32( z ) + (GRASS_GIRD_VEC_OFFS_Z/2);
	
	eoa = FE_EoaAddNpp( fes, &DATA_EoaH_EncGrass, &mtx, type, &head, 0xff );
	return( eoa );
}

//--------------------------------------------------------------
/**
 * �n��㩗p���A�j���I���`�F�b�N
 * @param	EOA_PTR		FE_CommTrapGrass_Add()�߂�l
 * @retval	int		TRUE=�I���BFALSE=�܂�
 */
//--------------------------------------------------------------
int FE_EncGrass_AnimeCheck( EOA_PTR eoa )
{
	ENC_GRASS_WORK *work;
	
	work = EOA_LocalWorkGet( eoa );
	return( work->end_flag );
}

//--------------------------------------------------------------
/**
 * EOA ��ꑐ�@������
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	int		TRUE=����I���BFALSE=�ُ�I��
 */
//--------------------------------------------------------------
static int EoaEncGrass_Init( EOA_PTR eoa, void *wk )
{
	int head_id;
	VecFx32 vec;
	ENC_GRASS_WORK *work;
	const ENC_GRASS_ADD_H *head;
	
	work = wk;
	head = EOA_AddPtrGet( eoa );
	work->head = *head;
	work->type = EOA_AddParamGet( eoa );
	
	vec.x = GRID_SIZE_FX32( work->head.init_gx ) + GRASS_GIRD_VEC_OFFS_X;
	vec.z = GRID_SIZE_FX32( work->head.init_gz ) + (GRASS_GIRD_VEC_OFFS_Z/2);
	
	vec.y = 0;
	FieldOBJTool_GetHeight( work->head.fsys, &vec );
	vec.y += GRASS_GROUND_OFFS_Y;
	
	EOA_MatrixSet( eoa, &vec );
	
	switch( work->type ){
	case FE_GRASS_TYPE_ENCOUNT_SMALL:
		head_id = FE_BLACT_H_ID_GRASS_ENCOUNT_SMALL;
		OS_Printf( "�h�ꑐ�@��\n" );
		break;
	case FE_GRASS_TYPE_ENCOUNT_BIG:
		head_id = FE_BLACT_H_ID_GRASS_ENCOUNT_BIG;
		OS_Printf( "�h�ꑐ�@��\n" );
		break;
	case FE_GRASS_TYPE_ENCOUNT_KIRAKIRA:
	default:
		head_id = FE_BLACT_H_ID_GRASS_ENCOUNT_KIRAKIRA;
		OS_Printf( "�h�ꑐ�@���炫��\n" );
	}
	
#ifndef YURE_KUSA_SET
	head_id = FE_BLACT_H_ID_GRASS;
#endif
	
	work->act = FE_BlActAddID( work->head.fes, head_id, &vec );
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA ��ꑐ�@�폜
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaEncGrass_Delete( EOA_PTR eoa, void *wk )
{
	ENC_GRASS_WORK *work;
	
	work = wk;
	BLACT_Delete( work->act );
}

//--------------------------------------------------------------
/**
 * EOA ��ꑐ�@����
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaEncGrass_Move( EOA_PTR eoa, void *wk )
{
	int frame;
	ENC_GRASS_WORK *work;
	
	work = wk;
#ifdef YURE_KUSA_SET
	switch( work->seq_no ){
	case 0:													//�h��
		if( BLACT_AnmFrameChg(work->act,FX32_ONE) == BLACT_ANISTA_END ){
			work->end_flag = TRUE;
			work->seq_no++;
		}
		
		break;
	case 1:
		break;
	}
#else
	switch( work->seq_no ){
	case 0:													//�h��
		BLACT_AnmFrameChg( work->act, FX32_ONE );
		work->frame++;
		
		if( work->frame >= GRASS_SHAKE_FRAME ){
			work->end_flag = TRUE;
			work->seq_no++;
		}
		
		break;
	case 1:
		break;
	}
#endif
}

//--------------------------------------------------------------
/**
 * EOA ��ꑐ�@�`��
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaEncGrass_Draw( EOA_PTR eoa, void *wk )
{
	VecFx32 mtx;
	ENC_GRASS_WORK *work;
	
	work = wk;
	EOA_MatrixGet( eoa, &mtx );
	BLACT_MatrixSet( work->act, &mtx );
}

//--------------------------------------------------------------
///	��EOA_H
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_EncGrass =
{
	ENC_GRASS_WORK_SIZE,
	EoaEncGrass_Init,
	EoaEncGrass_Delete,
	EoaEncGrass_Move,
	EoaEncGrass_Draw,
};

