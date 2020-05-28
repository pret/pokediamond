//******************************************************************************
/**
 * 
 * @file	fldeff_flag.c
 * @brief	�ꖇ�|���S�� �n���p ��
 * @author	k.ohno
 * @data	05.11.29
 *
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "field_effect.h"
#include "fieldobj.h"
#include "fldeff_flag.h"

//==============================================================================
//	define
//==============================================================================

#define FLAG_FLDOBJ_Y_MOVE_START ((FX32_ONE*6))				///<������
#define FLAG_FLDOBJ_Y_OFFSET ((FX32_ONE*25))				///<�t�B�[���hOBJ�����Y�I�t�Z�b�g
#define FLAG_FLDOBJ_Z_OFFSET ((FX32_ONE*-10))					///<�t�B�[���hOBJ�����Z�I�t�Z�b�g
#define FLAG_END_FRAME (30)									///<���I���t���[��	

//==============================================================================
//	typedef struct
//==============================================================================
//--------------------------------------------------------------
///	FE_FLAG�^
//--------------------------------------------------------------
typedef struct _TAG_FE_FLAG * FE_FLAG_PTR;

//--------------------------------------------------------------
///	FE_FLAG�\����
//--------------------------------------------------------------
typedef struct _TAG_FE_FLAG
{
	int add_count;
	int draw_init;
	FE_SYS *fes;
	NNSG3dRenderObj render;
	NNSG3dResMdl *model;
	NNSG3dResFileHeader *res_file;
	FIELD_OBJ_PTR fldobj;						///<���̑Ώ�FIELD_OBJ_PTR
}FE_FLAG;

#define FE_FLAG_SIZE (sizeof(FE_FLAG)) ///<FE_FLAG�T�C�Y

//--------------------------------------------------------------
///	FLAG_ADD_H�\����
//--------------------------------------------------------------
typedef struct
{
	FE_SYS *fes;
	FE_FLAG_PTR flag;						///<FE_FLAG_PTR
	FIELD_OBJ_PTR fldobj;						///<���̑Ώ�FIELD_OBJ_PTR
}FLAG_ADD_H;

#define FLAG_ADD_H_SIZE (sizeof(FLAG_ADD_H)) ///<FLAG_ADD_H�T�C�Y

//--------------------------------------------------------------
///	FLAG_WORK�\����
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
/*    int counter;
    int dir;
	int obj_id;									///<���Ώ�OBJID
	int zone_id;								///<���Ώۃ]�[��ID
	int vanish_sw;								///<��\��SW*/
	FLAG_ADD_H head;							///<�ǉ�����FLAG_ADD_H
}FLAG_WORK;

#define FLAG_WORK_SIZE (sizeof(FLAG_WORK))	///<FLAG_WORK�T�C�Y

//==============================================================================
//	�v���g�^�C�v
//==============================================================================
static void Flag_GraphicInit( FE_FLAG_PTR sd );
static void Flag_GraphicDelete( FE_FLAG_PTR sd );

static const EOA_H_NPP DATA_EoaH_Flag;

//==============================================================================
//	���@�V�X�e��
//==============================================================================
//--------------------------------------------------------------
/**
 * ��������
 * @param	fes		FE_SYS_PTR
 * @retval	FE_FLAG_PTR	FE_FLAG_PTR
 */
//--------------------------------------------------------------
void * FE_Flag_Init( FE_SYS *fes )
{
	FE_FLAG_PTR sd;

	sd = FE_AllocClearMemory( fes, FE_FLAG_SIZE, ALLOC_FR, 0 );
	sd->fes = fes;
	
	Flag_GraphicInit( sd );
	return( sd );
}

//--------------------------------------------------------------
/**
 * ���폜
 * @param	sd		FE_FLAG_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_Flag_Delete( void *work )
{
	FE_FLAG_PTR sd = work;
	Flag_GraphicDelete( sd );
	FE_FreeMemory( sd );
}

//==============================================================================
//	��	�p�[�c
//==============================================================================

//==============================================================================
//	���@�O���t�B�b�N
//==============================================================================
//--------------------------------------------------------------
/**
 * �� �O���t�B�b�N������
 * @param	sd	FE_FLAG_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Flag_GraphicInit( FE_FLAG_PTR sd )
{
	FE_simple3DModelInit( sd->fes, NARC_fldeff_h_flag_nsbmd, ALLOC_FR,
			&sd->render, &sd->model, &sd->res_file );
}

//--------------------------------------------------------------
/**
 * �� �O���t�B�b�N�폜
 * @param	sd	FE_FLAG_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Flag_GraphicDelete( FE_FLAG_PTR sd )
{
    FE_FreeMemory( sd->res_file );
}

//==============================================================================
//	���@EOA
//==============================================================================
//--------------------------------------------------------------
/**
 * �g���b�v�ǉ�
 * @param	fldobj		FIELD_OBJ_PTR
 * @retval	EOA_PTR
 */
//--------------------------------------------------------------
EOA_PTR FE_Flag_Add(  FIELD_OBJ_PTR fldobj )
{
	int param,pri;
	FLAG_ADD_H head;
	FE_SYS *fes;
	VecFx32 mtx;
    EOA_PTR eoa;
	FLAG_WORK *work;
	
	fes = FE_FieldOBJ_FE_SYS_Get( fldobj );
	head.fes = fes;
	head.flag = FE_EffectWorkGet( fes, FE_UG_TRAP_FLAG );
	head.fldobj = fldobj;
	
    FieldOBJ_VecPosGet( fldobj, &mtx );
	param = 0;
	
	eoa = FE_EoaAddNpp( fes, &DATA_EoaH_Flag, &mtx, param, &head, 0xff );
    return eoa;
}

//--------------------------------------------------------------
/**
 * EOA ���@������
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	int		TRUE=����I���BFALSE=�ُ�I��
 */
//--------------------------------------------------------------
static int EoaFlag_Init( EOA_PTR eoa, void *wk )
{
	FLAG_WORK *work;
	const FLAG_ADD_H *head;
    VecFx32 vec;
	
	work = wk;
	head = EOA_AddPtrGet( eoa );
	work->head = *head;

	work->obj_id = FieldOBJ_OBJIDGet( work->head.fldobj );
	work->zone_id = FieldOBJ_ZoneIDGet( work->head.fldobj );
	work->move.y = FLAG_FLDOBJ_Y_MOVE_START;

    FieldOBJ_VecPosGet( work->head.fldobj, &vec );

    EOA_MatrixSet( eoa, &vec );

    
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
static void EoaFlag_Delete( EOA_PTR eoa, void *wk )
{
}

//--------------------------------------------------------------
/**
 * EOA ���@����
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaFlag_Move( EOA_PTR eoa, void *wk )
{
	FLAG_WORK *work;
	FIELD_OBJ_PTR fldobj;
	VecFx32 vec;
	
	work = wk;
    fldobj = work->head.fldobj;
	
	GF_ASSERT( FieldOBJ_CheckSameID(fldobj,work->obj_id,work->zone_id) != FALSE &&
		"�����쒆�ɑΏۂ̃t�B�[���hOBJ���폜����܂���" );
	
	switch( work->seq_no ){
	case 0:
		FieldOBJ_VecPosGet( fldobj, &vec );
		vec.z += FLAG_FLDOBJ_Z_OFFSET;
		EOA_MatrixSet( eoa, &vec );

  //      work->move.y += 1;
  //      OS_TPrintf("move y %d\n",work->move.y);

        /*
        work->offset.y += work->move.y / FX32_ONE;
		
		if( work->offset.y ){
			work->move.y -= FX32_ONE * 2 / FX32_ONE;
		}else{
			work->move.y = 0;
//            work->seq_no++;
		}
*/		
		break;
	case 1:		
		work->frame++;
		
		if( work->frame >= FLAG_END_FRAME ){
			work->seq_no++;
//			work->end_sw = TRUE;
		}
		
		break;
	case 2:
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
static void EoaFlag_Draw( EOA_PTR eoa, void *wk )
{
	FLAG_WORK *work;
	
	work = wk;
	
    {
		VecFx32 vec;
		VecFx32 scale = { FX32_ONE, FX32_ONE, FX32_ONE };
		MtxFx33 rot	  = { FX32_ONE, 0,0,0, FX32_ONE, 0,0,0,FX32_ONE};
		
		EOA_MatrixGet( eoa, &vec );
		
//        vec.x += work->offset.x;
//        vec.y +=  work->move.y;
		vec.y += FLAG_FLDOBJ_Y_OFFSET;
        vec.z += - (FX32_ONE*5);

        {    // �J�����t�s�������
            const MtxFx43* pCamInv = NNS_G3dGlbGetInvCameraMtx();
            MtxFx33 Mat33;
            
            Rot360_to_MtxFx33(&rot, 90, 0, 0);
            MTX_Copy43To33(pCamInv, &Mat33);
            MTX_Concat33(&rot, &Mat33, &rot);
        }
        simple_3DModelDraw_1mat1shape( &work->head.flag->render, &vec, &rot, &scale );
	}
}

//--------------------------------------------------------------
///	��EOA_H
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_Flag =
{
	FLAG_WORK_SIZE,
	EoaFlag_Init,
	EoaFlag_Delete,
	EoaFlag_Move,
	EoaFlag_Draw,
};

