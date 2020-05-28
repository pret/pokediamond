//******************************************************************************
/**
 * 
 * @file	fldeff_footmark.c
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
#include "fldeff_footmark.h"

//==============================================================================
//	define
//==============================================================================
#define FOOTMARK_VANISH_START_FRAME (16)						///<�_�ŊJ�n�t���[��(�ԗ�40)
//#define FOOTMARK_VANISH_START_FRAME (20)						///<�_�ŊJ�n�t���[��(�ԗ�40)
#define FOOTMARK_VANISH_END_FRAME (28)							///<�_�ŏI���t���[��(�ԗ�56)

//--------------------------------------------------------------
///	���Վ���
//--------------------------------------------------------------
enum
{
	FOOTMARK_WALK_UP = 0,										///<���Ձ@��
	FOOTMARK_WALK_DOWN,											///<���Ձ@��
	FOOTMARK_WALK_LEFT,											///<���Ձ@��
	FOOTMARK_WALK_RIGHT,										///<���Ձ@�E
	FOOTMARK_CYCLE_UD,											///<���]�ԑ��� �㉺
	FOOTMARK_CYCLE_LR,											///<���]�ԑ��� ���E
	FOOTMARK_CYCLE_UL,											///<���]�ԑ��� �㍶
	FOOTMARK_CYCLE_UR,											///<���]�ԑ��� ��E
	FOOTMARK_CYCLE_DL,											///<���]�ԑ��� ����
	FOOTMARK_CYCLE_DR,											///<���]�ԑ��� ���E
	FOOTMARK_MAX,												///<���Սő吔
};

//--------------------------------------------------------------
///	���Ճ^�C�v
//--------------------------------------------------------------
typedef enum
{
	FOOTMARKTYPE_NORMAL = 0,		///<���Ճ^�C�v�@�Q��
	FOOTMARKTYPE_CYCLE,				///<���Ճ^�C�v�@���]��
	FOOTMARKTYPE_SNOW,				///<���Ճ^�C�v�@��
	FOOTMARKTYPE_SNOWDEEP,			///<���Ճ^�C�v�@�[����
}FOOTMARKTYPE;

//==============================================================================
//	typedef struct
//==============================================================================
//--------------------------------------------------------------
///	FE_FOOTMARK�^
//--------------------------------------------------------------
typedef struct _TAG_FE_FOOTMARK * FE_FOOTMARK_PTR;

//--------------------------------------------------------------
///	FE_FOOTMARK�\����
//--------------------------------------------------------------
typedef struct _TAG_FE_FOOTMARK
{
	FE_SYS *fes;
	NNSG3dRenderObj render[FOOTMARK_MAX];
	NNSG3dRenderObj render_snow[FOOTMARK_MAX];
	NNSG3dResMdl *model[FOOTMARK_MAX];
	NNSG3dResMdl *model_snow[FOOTMARK_MAX];
	NNSG3dResFileHeader *res_file[FOOTMARK_MAX];
	NNSG3dResFileHeader *res_file_snow[FOOTMARK_MAX];
}FE_FOOTMARK;

#define FE_FOOTMARK_SIZE (sizeof(FE_FOOTMARK)) ///<FE_FOOTMARK�T�C�Y

//--------------------------------------------------------------
///	FOOTMARK_ADD_H�\����
//--------------------------------------------------------------
typedef struct
{
	FOOTMARKTYPE type;
	NNSG3dRenderObj *render;
	NNSG3dResMdl *model;
}FOOTMARK_ADD_H;

//--------------------------------------------------------------
///	FOOTMARK_WORK�\����
//--------------------------------------------------------------
typedef struct
{
	int seq_no;
	int frame;
	int vanish_sw;
	int alpha;
	FOOTMARKTYPE type;
	NNSG3dRenderObj *render;
	NNSG3dResMdl *model;
}FOOTMARK_WORK;

#define FOOTMARK_WORK_SIZE (sizeof(FOOTMARK_WORK))

//==============================================================================
//	�v���g�^�C�v
//==============================================================================
static void FootMark_GraphicInit( FE_FOOTMARK_PTR fm );
static void FootMark_GraphicDelete( FE_FOOTMARK_PTR fm );

static NNSG3dRenderObj * FootMark_TypeRenderGet(
		FE_FOOTMARK_PTR fm, FOOTMARKTYPE type, int now_dir, int old_dir );
static NNSG3dResMdl * FootMark_TypeMdlGet(
		FE_FOOTMARK_PTR fm, FOOTMARKTYPE type, int now_dir, int old_dir );

static EOA_PTR FldOBJFootMark_AddMain( CONST_FIELD_OBJ_PTR fldobj, FOOTMARKTYPE type );

static const u32 DATA_3DModelArcID_FootMark[FOOTMARK_MAX];
static const u32 DATA_3DModelArcID_FootMarkSnow[FOOTMARK_MAX];
static const int DATA_FootMarkCycleDirTbl[DIR_4_MAX][DIR_4_MAX];
static const EOA_H_NPP DATA_EoaH_FootMark;

//==============================================================================
//	���Ձ@�V�X�e��
//==============================================================================
//--------------------------------------------------------------
/**
 * ���Տ�����
 * @param	fes		FE_SYS_PTR
 * @retval	FE_FOOTMARK_PTR		FE_FOOTMARK_PTR
 */
//--------------------------------------------------------------
void * FE_FootMark_Init( FE_SYS *fes )
{
	FE_FOOTMARK_PTR fm;
	
	fm = FE_AllocClearMemory( fes, FE_FOOTMARK_SIZE, ALLOC_FR, 0 );
	fm->fes = fes;
	
	FootMark_GraphicInit( fm );
	return( fm );
}

//--------------------------------------------------------------
/**
 * ���Ս폜
 * @param	fm		FE_FOOTMARK_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_FootMark_Delete( void *work )
{
	FE_FOOTMARK_PTR fm = work;
	FootMark_GraphicDelete( fm );
	FE_FreeMemory( fm );
}

//==============================================================================
//	����	�p�[�c
//==============================================================================

//==============================================================================
//	���Ձ@�O���t�B�b�N
//==============================================================================
//--------------------------------------------------------------
/**
 * ���� �O���t�B�b�N������
 * @param	fm		FE_FOOTMARK_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FootMark_GraphicInit( FE_FOOTMARK_PTR fm )
{
	int i;
	u32 id;
	
	for( i = 0; i < FOOTMARK_MAX; i++ ){
		id = DATA_3DModelArcID_FootMark[i];
		FE_simple3DModelInit( fm->fes, id, ALLOC_FR,
			&fm->render[i], &fm->model[i], &fm->res_file[i] );
		
		id = DATA_3DModelArcID_FootMarkSnow[i];
		FE_simple3DModelInit( fm->fes, id, ALLOC_FR,
			&fm->render_snow[i], &fm->model_snow[i], &fm->res_file_snow[i] );
	}
}

//--------------------------------------------------------------
/**
 * ���Ձ@�O���t�B�b�N�폜
 * @param	fm		FE_FOOTMARK_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FootMark_GraphicDelete( FE_FOOTMARK_PTR fm )
{
	int i;
	
	for( i = 0; i < FOOTMARK_MAX; i++ ){
		FE_FreeMemory( fm->res_file[i] );
		FE_FreeMemory( fm->res_file_snow[i] );
	}
}

//--------------------------------------------------------------
/**
 * �w��^�C�v�̃����_�擾
 * @param	fm		FE_FOOTMARK_PTR
 * @param	type	FOOTMARK_TYPE_NORMAL��
 * @param	now_dir	���݂̌��� DIR_UP��
 * @param	old_dir	�ߋ��̌��� DIR_UP��
 * @param	attr	FOOTMARK_ATTR
 * @retval	NNSG3dRenderObj �w��̃����_
 */
//--------------------------------------------------------------
static NNSG3dRenderObj * FootMark_TypeRenderGet(
		FE_FOOTMARK_PTR fm, FOOTMARKTYPE type, int now_dir, int old_dir )
{
	int no;
	NNSG3dRenderObj * render = NULL;
	
	switch( type ){
	case FOOTMARKTYPE_NORMAL:
		no = FOOTMARK_WALK_UP + now_dir;
		render = &fm->render[no];
		break;
	case FOOTMARKTYPE_CYCLE:
		no = DATA_FootMarkCycleDirTbl[old_dir][now_dir];
		render = &fm->render[no];
		break;
	case FOOTMARKTYPE_SNOW:
		no = FOOTMARK_WALK_UP + now_dir;
		render = &fm->render_snow[no];
		break;
	case FOOTMARKTYPE_SNOWDEEP:
		no = DATA_FootMarkCycleDirTbl[old_dir][now_dir];
		render = &fm->render_snow[no];
		break;
	}
	
	GF_ASSERT( render != NULL && "FootMark_TypeRenderGet()�s��\n" );
	return( render );
}

//--------------------------------------------------------------
/**
 * �w��^�C�v�̃��f���擾
 * @param	fm		FE_FOOTMARK_PTR
 * @param	type	FOOTMARK_TYPE_NORMAL��
 * @param	now_dir	���݂̌��� DIR_UP��
 * @param	old_dir	�ߋ��̌��� DIR_UP��
 * @param	attr	FOOTMARK_ATTR
 * @retval	NNSG3dMdl �w��̃����_
 */
//--------------------------------------------------------------
static NNSG3dResMdl * FootMark_TypeMdlGet(
		FE_FOOTMARK_PTR fm, FOOTMARKTYPE type, int now_dir, int old_dir )
{
	int no = 0;
	NNSG3dResMdl *model = NULL;
	
	switch( type ){
	case FOOTMARKTYPE_NORMAL:
		no = FOOTMARK_WALK_UP + now_dir;
		model = fm->model[no];
		break;
	case FOOTMARKTYPE_CYCLE:
		no = DATA_FootMarkCycleDirTbl[old_dir][now_dir];
		model = fm->model[no];
		break;
	case FOOTMARKTYPE_SNOW:
		no = FOOTMARK_WALK_UP + now_dir;
		model = fm->model_snow[no];
		break;
	case FOOTMARKTYPE_SNOWDEEP:
		no = DATA_FootMarkCycleDirTbl[old_dir][now_dir];
		model = fm->model_snow[no];
		break;
	}
	
	GF_ASSERT( model != NULL && "FootMark_TypeMdlGet()�s��\n" );
	return( model );
}

//==============================================================================
//	���Ձ@EOA
//==============================================================================
//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ �Q�����Ւǉ�
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	eoa		EOA_PTR
 */
//--------------------------------------------------------------
EOA_PTR FE_FldOBJFootMarkNormal_Add( CONST_FIELD_OBJ_PTR fldobj )
{
	return( FldOBJFootMark_AddMain(fldobj,FOOTMARKTYPE_NORMAL) );
}

//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ ���]�ԑ��Ւǉ�
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	eoa		EOA_PTR
 */
//--------------------------------------------------------------
EOA_PTR FE_FldOBJFootMarkCycle_Add( CONST_FIELD_OBJ_PTR fldobj )
{
	return( FldOBJFootMark_AddMain(fldobj,FOOTMARKTYPE_CYCLE) );
}

//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ �ᑫ�Ւǉ�
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	eoa		EOA_PTR
 */
//--------------------------------------------------------------
EOA_PTR FE_FldOBJFootMarkSnow_Add( CONST_FIELD_OBJ_PTR fldobj )
{
	return( FldOBJFootMark_AddMain(fldobj,FOOTMARKTYPE_SNOW) );
}

//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ �[���ᑫ�Ւǉ�
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	eoa		EOA_PTR
 */
//--------------------------------------------------------------
EOA_PTR FE_FldOBJFootMarkSnowDeep_Add( CONST_FIELD_OBJ_PTR fldobj )
{
	return( FldOBJFootMark_AddMain(fldobj,FOOTMARKTYPE_SNOWDEEP) );
}

//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ���Ւǉ��@���C��
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	attr	FOOTMARK_ATTR
 * @retval	eoa		EOA_PTR
 */
//--------------------------------------------------------------
static EOA_PTR FldOBJFootMark_AddMain( CONST_FIELD_OBJ_PTR fldobj, FOOTMARKTYPE type )
{
	VecFx32 mtx;
	EOA_PTR eoa;
	FOOTMARK_ADD_H head;
	int gx = FieldOBJ_OldPosGX_Get( fldobj );
	int gz = FieldOBJ_OldPosGZ_Get( fldobj );
	fx32 y = FieldOBJ_VecPosYGet( fldobj );
	int now_dir = FieldOBJ_DirDispGet( fldobj );
	int old_dir = FieldOBJ_DirDispOldGet( fldobj );
	int pri = FieldOBJ_TCBPriGet( fldobj, FLDOBJ_TCBPRI_OFFS_AFTER );
	FE_SYS *fes = FE_FieldOBJ_FE_SYS_Get( fldobj );
	FE_FOOTMARK_PTR fm = FE_EffectWorkGet( fes, FE_FLD_FOOTMARK );
	
	head.render = FootMark_TypeRenderGet( fm, type, now_dir, old_dir );
	head.model = FootMark_TypeMdlGet( fm, type, now_dir, old_dir );
	head.type = type;
	
	FieldOBJTool_GridCenterPosGet( gx, gz, &mtx );
	mtx.y = y;
	
	switch( type ){
	case FOOTMARKTYPE_NORMAL:
	case FOOTMARKTYPE_CYCLE:
		mtx.y += NUM_FX32( -8 );
			
		if( type == FOOTMARK_WALK_LEFT || type == FOOTMARK_WALK_RIGHT ){
			mtx.z += NUM_FX32( -2 );
		}else{
			mtx.z += NUM_FX32( 1 );
		}
		
		break;
	case FOOTMARKTYPE_SNOW:
	case FOOTMARKTYPE_SNOWDEEP:
		mtx.y += NUM_FX32( -10 );
			
		if( type == FOOTMARK_WALK_LEFT || type == FOOTMARK_WALK_RIGHT ){
			mtx.z += NUM_FX32( -2 );
		}else{
			mtx.z += NUM_FX32( 2 );
		}
	}
	
	eoa = FE_EoaAddNpp( fes, &DATA_EoaH_FootMark, &mtx, 0, &head, pri );
	return( eoa );
}

//--------------------------------------------------------------
/**
 * EOA ���Ձ@������
 * @param	eoa	EOA_PTR
 * @param	wk	eoa work *
 * @retval	int TRUE=����I���BFALSE=�ُ�I��
 */
//--------------------------------------------------------------
static int EoaFootMark_Init( EOA_PTR eoa, void *wk )
{
	VecFx32 mtx;
	FOOTMARK_WORK *work;
	const FOOTMARK_ADD_H *head;
	
	work = wk;
	work->type = EOA_AddParamGet( eoa );
	
	head = EOA_AddPtrGet( eoa );
	work->render = head->render;
	work->model = head->model;
	work->alpha = 31;
	work->type = head->type;
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA ���Ձ@�폜
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaFootMark_Delete( EOA_PTR eoa, void *wk )
{
}

//--------------------------------------------------------------
/**
 * EOA ���Ձ@����
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaFootMark_Move( EOA_PTR eoa, void *wk )
{
	FOOTMARK_WORK *work;
	
	work = wk;
	
	switch( work->seq_no ){
	case 0:
		work->frame++;
		
		if( work->frame >= FOOTMARK_VANISH_START_FRAME ){
			work->seq_no++;
		}
		
		break;
	case 1:
		work->alpha -= 2;
		
		if( work->alpha < 0 ){
			FE_EoaDelete( eoa );
			return;
		}
	}
}

//--------------------------------------------------------------
/**
 * EOA ���Ձ@�`��
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaFootMark_Draw( EOA_PTR eoa, void *wk )
{
	FOOTMARK_WORK *work;
	
	work = wk;
	
	if( work->vanish_sw == TRUE ){
		return;
	}
	
	{
		VecFx32 vec;
		VecFx32 scale = { FX32_ONE, FX32_ONE, FX32_ONE };
		MtxFx33 rot	  = { FX32_ONE, 0,0,0, FX32_ONE, 0,0,0,FX32_ONE};
		
		EOA_MatrixGet( eoa, &vec );
		
		NNS_G3dMdlUseMdlAlpha( work->model );
		NNS_G3dMdlSetMdlAlphaAll( work->model, work->alpha );
		simple_3DModelDraw( work->render, &vec, &rot, &scale );
	}
}

//==============================================================================
//	data
//==============================================================================
//--------------------------------------------------------------
///	����imd�e�[�u���@���т�FOOTMARK_WALK_UP���̒l�Ɉ�v
//--------------------------------------------------------------
static const u32 DATA_3DModelArcID_FootMark[FOOTMARK_MAX] =
{
	NARC_fldeff_f_mark_u_nsbmd,
	NARC_fldeff_f_mark_d_nsbmd,
	NARC_fldeff_f_mark_l_nsbmd,
	NARC_fldeff_f_mark_r_nsbmd,
	NARC_fldeff_c_mark_u_nsbmd,
	NARC_fldeff_c_mark_l_nsbmd,
	NARC_fldeff_c_mark_ul_nsbmd,
	NARC_fldeff_c_mark_ur_nsbmd,
	NARC_fldeff_c_mark_dl_nsbmd,
	NARC_fldeff_c_mark_dr_nsbmd,
};

//--------------------------------------------------------------
///	����imd�e�[�u���@���т�FOOTMARK_WALK_UP���̒l�Ɉ�v�@��
//--------------------------------------------------------------
static const u32 DATA_3DModelArcID_FootMarkSnow[FOOTMARK_MAX] =
{
	NARC_fldeff_nf_mark_u_nsbmd,
	NARC_fldeff_nf_mark_d_nsbmd,
	NARC_fldeff_nf_mark_l_nsbmd,
	NARC_fldeff_nf_mark_r_nsbmd,
	NARC_fldeff_nc_mark_u_nsbmd,
	NARC_fldeff_nc_mark_l_nsbmd,
	NARC_fldeff_nc_mark_ul_nsbmd,
	NARC_fldeff_nc_mark_ur_nsbmd,
	NARC_fldeff_nc_mark_dl_nsbmd,
	NARC_fldeff_nc_mark_dr_nsbmd,
};

//--------------------------------------------------------------
///	���]�ԑ��Ճe�[�u�� [�ߋ�����][���ݕ���]
//--------------------------------------------------------------
static const int DATA_FootMarkCycleDirTbl[DIR_4_MAX][DIR_4_MAX] =
{
	{FOOTMARK_CYCLE_UD,FOOTMARK_CYCLE_UD,FOOTMARK_CYCLE_UR,FOOTMARK_CYCLE_UL},
	{FOOTMARK_CYCLE_UD,FOOTMARK_CYCLE_UD,FOOTMARK_CYCLE_DR,FOOTMARK_CYCLE_DL},
	{FOOTMARK_CYCLE_DL,FOOTMARK_CYCLE_UL,FOOTMARK_CYCLE_LR,FOOTMARK_CYCLE_LR},
	{FOOTMARK_CYCLE_DR,FOOTMARK_CYCLE_UR,FOOTMARK_CYCLE_LR,FOOTMARK_CYCLE_LR},
};

//--------------------------------------------------------------
///	����EOA_H
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_FootMark =
{
	FOOTMARK_WORK_SIZE,
	EoaFootMark_Init,
	EoaFootMark_Delete,
	EoaFootMark_Move,
	EoaFootMark_Draw,
};

