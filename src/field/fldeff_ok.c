//******************************************************************************
/**
 * 
 * @file	fldeff_ok.c
 * @brief	�ꖇ�|���S�� �n���p OK�}�[�N
 * @author	k.ohno
 * @data	05.02.13
 *
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "field_effect.h"
#include "fieldobj.h"
#include "fldeff_ok.h"

//==============================================================================
//	define
//==============================================================================

#define OK_FLDOBJ_Y_MOVE_START ((FX32_ONE*6))				///<������
#define OK_FLDOBJ_Y_OFFSET ((FX32_ONE*25))				///<�t�B�[���hOBJ�����Y�I�t�Z�b�g
#define OK_FLDOBJ_Z_OFFSET ((FX32_ONE*-10))					///<�t�B�[���hOBJ�����Z�I�t�Z�b�g
#define OK_END_FRAME (60)									///<���I���t���[��	

//==============================================================================
//	typedef struct
//==============================================================================
//--------------------------------------------------------------
///	FE_OK�^
//--------------------------------------------------------------
typedef struct _TAG_FE_OK * FE_OK_PTR;

//--------------------------------------------------------------
///	FE_OK�\����
//--------------------------------------------------------------
typedef struct _TAG_FE_OK
{
	int add_count;
	int draw_init;
	FE_SYS *fes;
	NNSG3dRenderObj render;
	NNSG3dResMdl *model;
	NNSG3dResFileHeader *res_file;
	FIELD_OBJ_PTR fldobj;						///<���̑Ώ�FIELD_OBJ_PTR
}FE_OK;

#define FE_OK_SIZE (sizeof(FE_OK)) ///<FE_OK�T�C�Y

//--------------------------------------------------------------
///	OK_ADD_H�\����
//--------------------------------------------------------------
typedef struct
{
	FE_SYS *fes;
	FE_OK_PTR ok;						///<FE_OK_PTR
	FIELD_OBJ_PTR fldobj;						///<���̑Ώ�FIELD_OBJ_PTR
}OK_ADD_H;

#define OK_ADD_H_SIZE (sizeof(OK_ADD_H)) ///<OK_ADD_H�T�C�Y

//--------------------------------------------------------------
///	OK_WORK�\����
//--------------------------------------------------------------
typedef struct
{
	int seq_no;									///<����ԍ�
	int frame;									///<�t���[��
	int obj_id;									///<���Ώ�OBJID
	int zone_id;								///<���Ώۃ]�[��ID
	int vanish_sw;								///<��\��SW
	int end_sw;									///<�I��SW
	VecFx32 offset;								///<�I�t�Z�b�g
	VecFx32 move;								///<�ړ���
    int counter;
	OK_ADD_H head;							///<�ǉ�����OK_ADD_H
}OK_WORK;

#define OK_WORK_SIZE (sizeof(OK_WORK))	///<OK_WORK�T�C�Y

//==============================================================================
//	�v���g�^�C�v
//==============================================================================
static void Ok_GraphicInit( FE_OK_PTR sd );
static void Ok_GraphicDelete( FE_OK_PTR sd );

static const EOA_H_NPP DATA_EoaH_Ok;

//==============================================================================
//	�V�X�e��
//==============================================================================
//--------------------------------------------------------------
/**
 * OK�}�[�N������
 * @param	fes		FE_SYS_PTR
 * @retval	FE_OK_PTR	FE_OK_PTR
 */
//--------------------------------------------------------------
void * FE_Ok_Init( FE_SYS *fes )
{
	FE_OK_PTR sd;
	
	sd = FE_AllocClearMemory( fes, FE_OK_SIZE, ALLOC_FR, 0 );
	sd->fes = fes;
	
	Ok_GraphicInit( sd );
	return( sd );
}

//--------------------------------------------------------------
/**
 * OK�}�[�N�폜
 * @param	sd		FE_OK_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_Ok_Delete( void *work )
{
	FE_OK_PTR sd = work;
	Ok_GraphicDelete( sd );
	FE_FreeMemory( sd );
}

//==============================================================================
//	OK�}�[�N	�p�[�c
//==============================================================================

//==============================================================================
//	OK�}�[�N�@�O���t�B�b�N
//==============================================================================
//--------------------------------------------------------------
/**
 * OK�}�[�N �O���t�B�b�N������
 * @param	sd	FE_OK_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Ok_GraphicInit( FE_OK_PTR sd )
{
	FE_simple3DModelInit( sd->fes, NARC_fldeff_ug_ok_nsbmd, ALLOC_FR,
                       &sd->render, &sd->model, &sd->res_file );
}

//--------------------------------------------------------------
/**
 * OK�}�[�N �O���t�B�b�N�폜
 * @param	sd	FE_OK_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Ok_GraphicDelete( FE_OK_PTR sd )
{
   FE_FreeMemory( sd->res_file );
}

//==============================================================================
//	OK�}�[�N�@EOA
//==============================================================================
//--------------------------------------------------------------
/**
 * �g���b�v�ǉ�
 * @param	fldobj		FIELD_OBJ_PTR
 * @retval	EOA_PTR
 */
//--------------------------------------------------------------
EOA_PTR FE_Ok_Add(  FIELD_OBJ_PTR fldobj )
{
	int param,pri;
	OK_ADD_H head;
	FE_SYS *fes;
	VecFx32 mtx;
    EOA_PTR eoa;
	OK_WORK *work;
	
	fes = FE_FieldOBJ_FE_SYS_Get( fldobj );
	head.fes = fes;
	head.ok = FE_EffectWorkGet( fes, FE_UG_TRAP_OK );
	head.fldobj = fldobj;

    FieldOBJ_VecPosGet( fldobj, &mtx );
	param = 0;

	eoa = FE_EoaAddNpp( fes, &DATA_EoaH_Ok, &mtx, param, &head, 0xff );
    return eoa;
}

//--------------------------------------------------------------
/**
 * EOA OK�}�[�N�@������
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	int		TRUE=����I���BFALSE=�ُ�I��
 */
//--------------------------------------------------------------
static int EoaOk_Init( EOA_PTR eoa, void *wk )
{
	OK_WORK *work;
	const OK_ADD_H *head;
    VecFx32 vec;
	
	work = wk;
	head = EOA_AddPtrGet( eoa );
	work->head = *head;

	work->obj_id = FieldOBJ_OBJIDGet( work->head.fldobj );
	work->zone_id = FieldOBJ_ZoneIDGet( work->head.fldobj );
	work->move.y = OK_FLDOBJ_Y_MOVE_START;

    FieldOBJ_VecPosGet( work->head.fldobj, &vec );

    EOA_MatrixSet( eoa, &vec );

    work->counter = OK_END_FRAME;
    
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA OK�}�[�N�@�폜
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaOk_Delete( EOA_PTR eoa, void *wk )
{
}

//--------------------------------------------------------------
/**
 * EOA OK�}�[�N�@����
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaOk_Move( EOA_PTR eoa, void *wk )
{
	OK_WORK *work;
	FIELD_OBJ_PTR fldobj;
	VecFx32 vec;
	
	work = wk;
    if(work->counter != 0){
        work->counter--;
    }
    else{
        FE_EoaDelete(eoa);
        return;
    }
    
    fldobj = work->head.fldobj;
    FieldOBJ_VecPosGet( fldobj, &vec );
    vec.z += OK_FLDOBJ_Z_OFFSET;
    EOA_MatrixSet( eoa, &vec );
}

//--------------------------------------------------------------
/**
 * EOA OK�}�[�N�@�`��
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaOk_Draw( EOA_PTR eoa, void *wk )
{
	OK_WORK *work;
	
	work = wk;
	
    {
		VecFx32 vec;
		VecFx32 scale = { FX32_ONE, FX32_ONE, FX32_ONE };
		MtxFx33 rot	  = { FX32_ONE, 0,0,0, FX32_ONE, 0,0,0,FX32_ONE};
		
		EOA_MatrixGet( eoa, &vec );
		
		vec.y += OK_FLDOBJ_Y_OFFSET;
        vec.z += - (FX32_ONE*5);

        {    // �J�����t�s�������
            const MtxFx43* pCamInv = NNS_G3dGlbGetInvCameraMtx();
            MtxFx33 Mat33;
            
            Rot360_to_MtxFx33(&rot, 90, 0, 0);
            MTX_Copy43To33(pCamInv, &Mat33);
            MTX_Concat33(&rot, &Mat33, &rot);
        }
        simple_3DModelDraw_1mat1shape( &work->head.ok->render, &vec, &rot, &scale );
	}
}

//--------------------------------------------------------------
///	OK�}�[�NEOA_H
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_Ok =
{
	OK_WORK_SIZE,
	EoaOk_Init,
	EoaOk_Delete,
	EoaOk_Move,
	EoaOk_Draw,
};

