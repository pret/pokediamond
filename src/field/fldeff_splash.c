//******************************************************************************
/**
 * 
 * @file	fldeff_splash.c
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

#include "fldeff_splash.h"
#include "map_tool.h"

//==============================================================================
//	define
//==============================================================================
#define SPLASH_ANIME_FRAME (12)				///<���򖗃A�j���t���[��

//==============================================================================
//	typedef struct
//==============================================================================
//--------------------------------------------------------------
///	FE_SPLASH_PTR�^
//--------------------------------------------------------------
typedef struct _TAG_FE_SPLASH * FE_SPLASH_PTR;

//--------------------------------------------------------------
///	FE_SPLASH�\����
//--------------------------------------------------------------
typedef struct _TAG_FE_SPLASH
{
	FE_SYS *fes;
}FE_SPLASH;

#define FE_SPLASH_SIZE (sizeof(FE_SPLASH))	///<FE_SPLASH�T�C�Y

//--------------------------------------------------------------
///	SPLASH_ADD_H�\����
//--------------------------------------------------------------
typedef struct
{
	FIELDSYS_WORK *fsys;
	FE_SYS *fes;
	FE_SPLASH_PTR spl;
	FIELD_OBJ_PTR fldobj;
}SPLASH_ADD_H;

//--------------------------------------------------------------
///	SPLASH_WORK�\����
//--------------------------------------------------------------
typedef struct
{
	int seq_no;
	int obj_code;
	int obj_id;
	int zone_id;
	int frame;
	SPLASH_ADD_H head;
	BLACT_WORK_PTR act;
}SPLASH_WORK;

#define SPLASH_WORK_SIZE (sizeof(SPLASH_WORK))

//==============================================================================
//	�v���g�^�C�v
//==============================================================================
static void Splash_GraphicInit( FE_SPLASH_PTR spl );
static void Splash_GraphicDelete( FE_SPLASH_PTR spl );

static const EOA_H_NPP DATA_EoaH_Splash;
const BLACT_ANIME_TBL DATA_BlActAnmTbl_Splash[];

//==============================================================================
//	����	�V�X�e��
//==============================================================================
//--------------------------------------------------------------
/**
 * ���򖗏�����
 * @param	fes		FE_SYS_PTR
 * @retval	FE_SPLASH_PTR FE_SPLASH_PTR
 */
//--------------------------------------------------------------
void * FE_Splash_Init( FE_SYS *fes )
{
	FE_SPLASH_PTR spl;
	
	spl = FE_AllocClearMemory( fes, FE_SPLASH_SIZE, ALLOC_FR, 0 );
	spl->fes = fes;
	
	Splash_GraphicInit( spl );
	return( spl );
}

//--------------------------------------------------------------
/**
 * ���򖗍폜
 * @param	kusa		FE_SPLASH_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_Splash_Delete( void *work )
{
	FE_SPLASH_PTR spl = work;
	Splash_GraphicDelete( spl );
	FE_FreeMemory( spl );
}

//==============================================================================
//	���򖗁@�O���t�B�b�N
//==============================================================================
//--------------------------------------------------------------
/**
 * ���@�O���t�B�b�N������
 * @param	spl	FE_GRASS_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Splash_GraphicInit( FE_SPLASH_PTR spl )
{
	FE_BlActResAdd_MdlArc( spl->fes, FE_RESID_MDL_SPLASH, NARC_fldeff_shibuki_nsbmd );
	FE_BlActResAdd_AnmArc( spl->fes, FE_RESID_ANM_SPLASH, NARC_fldeff_shibuki_itpcv_dat );
	FE_BlActResAdd_TexArc( spl->fes,
			FE_RESID_TEX_SPLASH, NARC_fldeff_shibuki_nsbtx, TEXRESM_TEX_CUT_TRUE );
	
	FE_BlActHeaderManageAddResmID( spl->fes, FE_BLACT_H_ID_SPLASH,
			FE_RESID_MDL_SPLASH, FE_RESID_ANM_SPLASH,
			FE_RESID_TEX_SPLASH, FE_BLACT_TEX_VRAM,
			DATA_BlActAnmTbl_Splash );
}

//--------------------------------------------------------------
/**
 * ���򖗁@�O���t�B�b�N�폜
 * @param	spl	FE_SPLASH_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Splash_GraphicDelete( FE_SPLASH_PTR spl )
{
	FE_BlActResDelete_Mdl( spl->fes, FE_RESID_MDL_SPLASH );
	FE_BlActResDelete_Anm( spl->fes, FE_RESID_ANM_SPLASH );
	FE_BlActResDelete_Tex( spl->fes, FE_RESID_TEX_SPLASH );
	
	FE_BlActHeaderManageFree( spl->fes, FE_BLACT_H_ID_SPLASH );
}

//==============================================================================
//	EOA ����
//==============================================================================
//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ�p���򖗒ǉ�
 * @param	fldobj		FIELD_OBJ_PTR
 * @param	joint		�ڑ��t���O
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_FldOBJSplash_Add( FIELD_OBJ_PTR fldobj, int joint )
{
	SPLASH_ADD_H head;
	FE_SYS *fes;
	EOA_PTR eoa;
	
	fes = FE_FieldOBJ_FE_SYS_Get( fldobj );
	
	head.fsys = FieldOBJ_FieldSysWorkGet( fldobj );
	head.fes = fes;
	head.spl = FE_EffectWorkGet( fes, FE_FLD_SPLASH );
	head.fldobj = fldobj;
	
	{
		VecFx32 vec = {0,0,0};
		int pri = FieldOBJ_TCBPriGet( fldobj, FLDOBJ_TCBPRI_OFFS_AFTER );
		eoa = FE_EoaAddNpp( fes, &DATA_EoaH_Splash, &vec, joint, &head, pri );
	}
}

//--------------------------------------------------------------
/**
 * EOA ���򖗁@������
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	int		TRUE=����I���BFALSE=�ُ�I��
 */
//--------------------------------------------------------------
static int EoaSplash_Init( EOA_PTR eoa, void *wk )
{
	VecFx32 vec = { 0,0,0 };
	SPLASH_WORK *work;
	const SPLASH_ADD_H *head;
	
	work = wk;
	head = EOA_AddPtrGet( eoa );
	
	work->head = *head;
	work->obj_code = FieldOBJ_OBJCodeGetSeedIn( work->head.fldobj );
	work->obj_id = FieldOBJ_OBJIDGet( work->head.fldobj );
	work->zone_id = FieldOBJ_ZoneIDGet( work->head.fldobj );
	
	EOA_MatrixSet( eoa, &vec );
	work->act = FE_BlActAddID( work->head.fes, FE_BLACT_H_ID_SPLASH, &vec );
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA ���򖗁@�폜
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaSplash_Delete( EOA_PTR eoa, void *wk )
{
	SPLASH_WORK *work;
	
	work = wk;
	BLACT_Delete( work->act );
}

//--------------------------------------------------------------
/**
 * EOA ���򖗁@����
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaSplash_Move( EOA_PTR eoa, void *wk )
{
	int frame,param;
	SPLASH_WORK *work;
	FIELD_OBJ_PTR fldobj;
	
	work = wk;
	fldobj = work->head.fldobj;
	
	if( FieldOBJ_CheckSameIDOBJCodeIn(
		fldobj,work->obj_code,work->obj_id,work->zone_id) == FALSE ){
		FE_EoaDelete( eoa );
		return;
	}
	
	param = EOA_AddParamGet( eoa );
	
	if( param == TRUE ){
		if( FieldOBJ_StatusBitCheck_ShoalEffectSet(fldobj) == FALSE ){
			FE_EoaDelete( eoa );
			return;
		}
	}
	
	switch( work->seq_no ){
	case 0:													//�h��
		BLACT_AnmFrameChg( work->act, FX32_ONE );
		frame = BLACT_AnmFrameGetOffs( work->act ) / FX32_ONE;
		
		if( frame >= SPLASH_ANIME_FRAME ){
			if( param == FALSE ){
				FE_EoaDelete( eoa );
				return;
			}else{
				BLACT_AnmFrameSet( work->act, 0 );
			}
		}

		
		break;
	}
}

//--------------------------------------------------------------
/**
 * EOA ���򖗁@�`��
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaSplash_Draw( EOA_PTR eoa, void *wk )
{
	VecFx32 vec;
	SPLASH_WORK *work;
	FIELD_OBJ_PTR fldobj;
	
	work = wk;
	fldobj = work->head.fldobj;
	
	if( FieldOBJ_CheckSameIDOBJCodeIn(
		fldobj,work->obj_code,work->obj_id,work->zone_id) == FALSE ){
		FE_EoaDelete( eoa );
		return;
	}
	
	FieldOBJ_VecPosGet( fldobj, &vec );
#if 0
	{
		VecFx32 d_vec;
		FieldOBJ_VecDrawOffsGet( fldobj, &d_vec );
		vec.x = d_vec.x;
		vec.y = d_vec.y;
		vec.z = d_vec.z;
	}
#endif
	vec.z += FX32_ONE * 8;
	BLACT_MatrixSet( work->act, &vec );
}

//==============================================================================
//	data
//==============================================================================
//--------------------------------------------------------------
///	����EOA_H
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_Splash =
{
	SPLASH_WORK_SIZE,
	EoaSplash_Init,
	EoaSplash_Delete,
	EoaSplash_Move,
	EoaSplash_Draw,
};

//--------------------------------------------------------------
///	���򖗃A�j��
//--------------------------------------------------------------
static const BLACT_ANIME_TBL DATA_BlActAnmTbl_Splash[] =
{
	{ 0, SPLASH_ANIME_FRAME, BLACT_ANIM_END },
	{ 0, 0, BLACT_ANIM_CMD_MAX },
};
