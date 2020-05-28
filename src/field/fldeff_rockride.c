//******************************************************************************
/**
 * 
 * @file	fldeff_rockride.c
 * @brief	�t�B�[���hOBJ�@���@�Ǐ��|�P����
 * @author	kagaya
 * @data	05.07.13
 *
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "field_effect.h"
#include "fieldobj.h"
#include "fldeff_rockride.h"

//==============================================================================
//	define
//==============================================================================
//#define DEBUG_ROCKRIDE_WRITE_OFF	//��`�ŕǏ��|�P�����`��OFF

//#define ROCKRIDE_DRAW_Z_OFFSET (FX32_ONE*(3))
//#define ROCKRIDE_DRAW_Z_OFFSET (FX32_ONE*(5))			///<�Ǐ��|�P�����`��I�t�Z�b�gZ��
//#define ROCKRIDE_DRAW_Z_OFFSET (FX32_ONE*(3))				

#define ROCKRIDE_RIDE_Y_OFFSET (FX32_ONE*8)				///<�g�|�P���ւ̕\���I�t�Z�b�gY
#define ROCKRIDE_RIDE_Z_OFFSET (FX32_ONE*4)				///<�g�|�P���ւ̕\���I�t�Z�b�gZ

#define ROCKRIDE_SHAKE_VALUE (0x0400)					///<�����h�ꕝ
#define ROCKRIDE_SHAKE_MAX (FX32_ONE*4)

#define ROCKRIDE_ON_FRAME (30)
#define ROCKRIDE_OFF_FRAME (ROCKRIDE_ON_FRAME+30)

//==============================================================================
//	typedef struct
//==============================================================================
//--------------------------------------------------------------
///	FE_ROCKRIDE�^
//--------------------------------------------------------------
typedef struct _TAG_FE_ROCKRIDE * FE_ROCKRIDE_PTR;

//--------------------------------------------------------------
///	FE_ROCKRIDE�\����
//--------------------------------------------------------------
typedef struct _TAG_FE_ROCKRIDE
{
	int add_count;
	int draw_init;
	int trans_set;
	TCB_PTR tcb_vintr_trans;
	FE_SYS *fes;
	NNSG3dRenderObj render;
	NNSG3dResMdl *model;
	NNSG3dResFileHeader *res_file;
}FE_ROCKRIDE;

#define FE_ROCKRIDE_SIZE (sizeof(FE_ROCKRIDE)) ///<FE_ROCKRIDE�T�C�Y

//--------------------------------------------------------------
///	ROCKRIDE_ADD_H�\����
//--------------------------------------------------------------
typedef struct
{
	int init_dir;					///<�\������
	FE_SYS *fes;					///<FE_SYS_PTR
	FIELDSYS_WORK *fsys;			///<FIELDSYS_WORK
	FE_ROCKRIDE_PTR rockride;		///<FE_ROCKRIDE_PTR
	FIELD_OBJ_PTR fldobj;			///<FIELD_OBJ_PTR
}ROCKRIDE_ADD_H;

#define ROCKRIDE_ADD_H_SIZE (sizeof(ROCKRIDE_ADD_H)) ///<ROCKRIDE_ADD_H�T�C�Y

//--------------------------------------------------------------
///	ROCKRIDE_WORK�\����
//--------------------------------------------------------------
typedef struct
{
	int vanish_sw;								///<��\��SW
	int dir;									///<����
	int frame;									///<�\���t���[��
	int joint;									///<�ڑ��t���O
	ROCKRIDE_ADD_H head;						///<�ǉ�����ROCKRIDE_ADD_H
}ROCKRIDE_WORK;

#define ROCKRIDE_WORK_SIZE (sizeof(ROCKRIDE_WORK))	///<ROCKRIDE_WORK�T�C�Y

//==============================================================================
//	�v���g�^�C�v
//==============================================================================
static void RockRide_AddCountUp( FE_ROCKRIDE_PTR rockride );
static void RockRide_AddCountDown( FE_ROCKRIDE_PTR rockride );

static void RockRide_GraphicInit( FE_ROCKRIDE_PTR rockride );
static void RockRide_GraphicDelete( FE_ROCKRIDE_PTR rockride );
static void RockRide_GraphicCheckInit( FE_ROCKRIDE_PTR rockride );
static void RockRide_GraphicCheckDelete( FE_ROCKRIDE_PTR rockride );
static void RockRide_VIntrTCBTrans( TCB_PTR tcb, void *wk );

static const EOA_H_NPP DATA_EoaH_RockRide;

//==============================================================================
//	�Ǐ��|�P�����@�V�X�e��
//==============================================================================
//--------------------------------------------------------------
/**
 * �Ǐ��|�P����������
 * @param	fes		FE_SYS_PTR
 * @retval	FE_ROCKRIDE_PTR	FE_ROCKRIDE_PTR
 */
//--------------------------------------------------------------
void * FE_RockRide_Init( FE_SYS *fes )
{
	FE_ROCKRIDE_PTR rockride;
	
	rockride = FE_AllocClearMemory( fes, FE_ROCKRIDE_SIZE, ALLOC_FR, 0 );
	rockride->fes = fes;
	
	return( rockride );
}

//--------------------------------------------------------------
/**
 * �Ǐ��|�P�����폜
 * @param	rockride		FE_ROCKRIDE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_RockRide_Delete( void *work )
{
	FE_ROCKRIDE_PTR rockride = work;
	RockRide_GraphicDelete( rockride );
	FE_FreeMemory( rockride );
}

//==============================================================================
//	�Ǐ��|�P����	�p�[�c
//==============================================================================
//--------------------------------------------------------------
/**
 * �Ǐ�萔�J�E���g
 * @param	rockride	FE_ROCKRIDE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void RockRide_AddCountUp( FE_ROCKRIDE_PTR rockride )
{
	rockride->add_count++;
}

//--------------------------------------------------------------
/**
 * �Ǐ�萔�f�N�������g
 * @param	rockride	FE_ROCKRIDE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void RockRide_AddCountDown( FE_ROCKRIDE_PTR rockride )
{
	rockride->add_count--;
	
	GF_ASSERT( rockride->add_count >= 0 &&
		"RockRide_AddCountDown()�@�Ǐ��̒ǉ��ƍ폜�̉񐔂�����Ȃ�" );
}

//==============================================================================
//	�Ǐ��|�P�����@�O���t�B�b�N
//==============================================================================
//--------------------------------------------------------------
/**
 * �Ǐ��|�P���� �O���t�B�b�N������
 * @param	rockride	FE_ROCKRIDE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void RockRide_GraphicInit( FE_ROCKRIDE_PTR rockride )
{
	if( rockride->draw_init == FALSE ){
		rockride->res_file = FE_ArcDataLoadAlloc(
			rockride->fes, NARC_fldeff_rock_ride_nsbmd, ALLOC_LO );
		rockride->tcb_vintr_trans = VIntrTCB_Add( RockRide_VIntrTCBTrans, rockride, 0x80 );
		rockride->draw_init = TRUE;
	}
}

//--------------------------------------------------------------
/**
 * �Ǐ��|�P���� �O���t�B�b�N�폜
 * @param	rockride	FE_ROCKRIDE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void RockRide_GraphicDelete( FE_ROCKRIDE_PTR rockride )
{
	if( rockride->tcb_vintr_trans != NULL ){
		TCB_Delete( rockride->tcb_vintr_trans );
		rockride->tcb_vintr_trans = NULL;
		rockride->trans_set = FALSE;
	}
	
	if( rockride->draw_init == TRUE ){
		rockride->draw_init = FALSE;
		FE_FreeMemory( rockride->res_file );
	}
}

//--------------------------------------------------------------
/**
 * ������O���t�B�b�N������
 * @param	rockride	FE_ROCKRIDE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void RockRide_GraphicCheckInit( FE_ROCKRIDE_PTR rockride )
{
	if( rockride->add_count == 0 ){
		RockRide_GraphicInit( rockride );
	}
}

//--------------------------------------------------------------
/**
 * ������O���t�B�b�N�폜
 * @param	rockride	FE_ROCKRIDE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void RockRide_GraphicCheckDelete( FE_ROCKRIDE_PTR rockride )
{
	if( rockride->add_count == 0 ){
		RockRide_GraphicDelete( rockride );
	}
}

//--------------------------------------------------------------
/**
 * VIntrTcb �O���t�B�b�N������
 * @param	tcb		TCB_PTR
 * @param	wk		tcb work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void RockRide_VIntrTCBTrans( TCB_PTR tcb, void *wk )
{
	FE_ROCKRIDE_PTR rockride = wk;
	
	FE_simple3DModelInitOnly( rockride->fes,
		&rockride->render, &rockride->model, &rockride->res_file );
	
	rockride->tcb_vintr_trans = NULL;
	rockride->trans_set = TRUE;
	TCB_Delete( tcb );
}

//==============================================================================
//	�Ǐ��|�P�����@EOA
//==============================================================================
//--------------------------------------------------------------
/**
 * EOA �Ǐ��|�P�����ǉ�
 * @param	fldobj	FIELD_OBJ_PTR
 * @param	gx		�\���O���b�hX
 * @param	gz		�\���O���b�hZ
 * @param	dir		�\������
 * @param	joint	TRUE=fldobj�̍��W�ɐڑ� FALSE=���Ȃ�
 * @retval	EOA_PTR	�ǉ����ꂽ�|�P����EOA_PTR
 */
//--------------------------------------------------------------
EOA_PTR FE_FldOBJRockRidePoke_Add( FIELD_OBJ_PTR fldobj, int gx, int gz, int dir, int joint )
{
	int pri;
	EOA_PTR eoa;
	ROCKRIDE_ADD_H head;
	VecFx32 mtx = {0,0,0};
	FE_SYS *fes = FE_FieldOBJ_FE_SYS_Get( fldobj );
	
	head.init_dir = dir;
	head.fes = fes;
	head.fsys = FieldOBJ_FieldSysWorkGet( fldobj );
	head.rockride = FE_EffectWorkGet( fes, FE_FLD_ROCKRIDE );
	head.fldobj = fldobj;
		
	if( joint == FALSE ){
		mtx.x = GRID_SIZE_FX32( gx ) + FLDOBJ_VEC_X_GRID_OFFS_FX32;
		mtx.z = GRID_SIZE_FX32( gz ) + FLDOBJ_VEC_Z_GRID_OFFS_FX32;
		FieldOBJTool_GetHeight( head.fsys, &mtx );
	}else{
		FieldOBJ_VecPosGet( fldobj, &mtx );
	}
	
	pri = FieldOBJ_TCBPriGet( fldobj, FLDOBJ_TCBPRI_OFFS_AFTER );
	eoa = FE_EoaAddNpp( fes, &DATA_EoaH_RockRide, &mtx, joint, &head, pri );
	
	return( eoa );
}

//--------------------------------------------------------------
/**
 * �Ǐ��|�P�����̐ڑ��t���O�Z�b�g
 * @param	eoa		EOA_PTR
 * @param	joint	TRUE=�ڑ� FALSE=��ڑ�
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_FldOBJRockRidePokeJointFlagSet( EOA_PTR eoa, int joint )
{
	ROCKRIDE_WORK *work = EOA_LocalWorkGet( eoa );
	work->joint = joint;
}

//--------------------------------------------------------------
/**
 * EOA �Ǐ��|�P�����@������
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	int		TRUE=����I���BFALSE=�ُ�I��
 */
//--------------------------------------------------------------
static int EoaRockRide_Init( EOA_PTR eoa, void *wk )
{
	ROCKRIDE_WORK *work = wk;
	const ROCKRIDE_ADD_H *head = EOA_AddPtrGet( eoa );
	
	work->head = *head;
	work->dir = head->init_dir;
	work->joint = EOA_AddParamGet( eoa );
	
	RockRide_GraphicCheckInit( work->head.rockride );
	RockRide_AddCountUp( work->head.rockride );
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA �Ǐ��|�P�����@�폜
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaRockRide_Delete( EOA_PTR eoa, void *wk )
{
	ROCKRIDE_WORK *work = wk;
	
	RockRide_AddCountDown( work->head.rockride );
	RockRide_GraphicCheckDelete( work->head.rockride );
}

//--------------------------------------------------------------
/**
 * EOA �Ǐ��|�P�����@����
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaRockRide_Move( EOA_PTR eoa, void *wk )
{
	ROCKRIDE_WORK *work = wk;
	FIELD_OBJ_PTR fldobj = work->head.fldobj;
	
	if( work->joint == FALSE ){
		return;
	}
	
	{
		VecFx32 offs = { 0, 0, 0 };
		FieldOBJ_VecDrawOffsOutSideSet( fldobj, &offs );
	}
	
	{
		VecFx32 vec;
		FieldOBJ_VecPosGet( fldobj, &vec );
		vec.y += 0;
		EOA_MatrixSet( eoa, &vec );
	}
}

//--------------------------------------------------------------
/**
 * EOA �Ǐ��|�P�����@�`��
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaRockRide_Draw( EOA_PTR eoa, void *wk )
{
	ROCKRIDE_WORK *work;
	
	work = wk;
	
	if( work->vanish_sw == TRUE || work->head.rockride->trans_set == FALSE ){
		return;
	}
	
	{
		work->frame++;
	}
	
	{
		VecFx32 vec;
		VecFx32 scale = { FX32_ONE, FX32_ONE, FX32_ONE };
		MtxFx33 rot	  = { FX32_ONE, 0,0,0, FX32_ONE, 0,0,0,FX32_ONE};
		
		switch( work->dir ){
		case DIR_UP:	Rot360_to_MtxFx33( &rot, 0, 180, 0 ); break;
		case DIR_DOWN:	Rot360_to_MtxFx33( &rot, 0, 0, 0 ); break;
		case DIR_LEFT:	Rot360_to_MtxFx33( &rot, 0, 270, 0 ); break;
		case DIR_RIGHT:	Rot360_to_MtxFx33( &rot, 0, 90, 0 ); break;
		}
		
		EOA_MatrixGet( eoa, &vec );
		simple_3DModelDraw( &work->head.rockride->render, &vec, &rot, &scale );
	}
}

//==============================================================================
//	data
//==============================================================================
//--------------------------------------------------------------
///	�Ǐ��|�P����EOA_H
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_RockRide =
{
	ROCKRIDE_WORK_SIZE,
	EoaRockRide_Init,
	EoaRockRide_Delete,
	EoaRockRide_Move,
	EoaRockRide_Draw,
};


//==============================================================================
//	debug
//==============================================================================
#ifdef DEBUG_ROCKRIDE_ROT
void DEBUG_RockRide_Rot( EOA_PTR eoa, int x, int y, int z )
{
	ROCKRIDE_WORK *work = EOA_LocalWorkGet( eoa );
	work->rot_x += x;
	if( work->rot_x >= 360 ){ work->rot_x = 0; }
	if( work->rot_x < 0 ){ work->rot_x = 360 - work->rot_x; }
	work->rot_y += y;
	if( work->rot_y >= 360 ){ work->rot_y = 0; }
	if( work->rot_y < 0 ){ work->rot_y = 360 - work->rot_y; }
	work->rot_z += z;
	if( work->rot_z >= 360 ){ work->rot_z = 0; }
	if( work->rot_z < 0 ){ work->rot_z = 360 - work->rot_z; }
}
#endif
