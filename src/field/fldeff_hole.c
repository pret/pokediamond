//******************************************************************************
/**
 * 
 * @file	fldeff_hole.c
 * @brief	�t�B�[���hOBJ HOLE   �n���n�ʂɒu�����̂͂܂Ƃ߂ĊǗ��ɕύX
 * @author	k.ohno
 * @data	05.11.29
 *
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "field_effect.h"
#include "fieldobj.h"
#include "fldeff_hole.h"

//==============================================================================
//	define
//==============================================================================
#define HOLE_DRAW_Z_OFFSET (FX32_ONE*(5))			///<㩕`��I�t�Z�b�gZ��

//==============================================================================
//	typedef struct
//==============================================================================
//--------------------------------------------------------------
///	FE_HOLE_PTR��`
//--------------------------------------------------------------
typedef struct _TAG_FE_HOLE * FE_HOLE_PTR;

//--------------------------------------------------------------
///	FE_HOLE�\����
//--------------------------------------------------------------
typedef struct _TAG_FE_HOLE
{
	FE_SYS *fes;
	NNSG3dRenderObj render[33];
	NNSG3dResMdl *model[33];
	NNSG3dResFileHeader *res_file[33];
}FE_HOLE;

#define FE_HOLE_SIZE (sizeof(FE_HOLE)) ///<FE_HOLE�T�C�Y

//--------------------------------------------------------------
///	HOLE_ADD_H�\����
//--------------------------------------------------------------
typedef struct
{
	int init_gx;
	int init_gz;
	FIELDSYS_WORK *fsys;
	FE_SYS *fes;
	FE_HOLE_PTR hole;						///<FE_HOLE_PTR
}HOLE_ADD_H;

#define HOLE_ADD_H_SIZE (sizeof(HOLE_ADD_H)) ///<HOLE_ADD_H�T�C�Y

//--------------------------------------------------------------
///	HOLE_WORK�\����
//--------------------------------------------------------------
typedef struct
{
	NNSG3dRenderObj render;  //�G
    int modelNo;
    float scale;
    float maxScale;
	int obj_id;									///<㩑Ώ�OBJID
	int zone_id;								///<㩑Ώۃ]�[��ID
	int vanish_sw;								///<��\��SW
	HOLE_ADD_H head;							///<�ǉ�����HOLE_ADD_H
}HOLE_WORK;

#define HOLE_WORK_SIZE (sizeof(HOLE_WORK))	///<HOLE_WORK�T�C�Y

//==============================================================================
//	�v���g�^�C�v
//==============================================================================
static void Hole_GraphicInit( FE_HOLE_PTR sd );
static void Hole_GraphicDelete( FE_HOLE_PTR sd );

static const EOA_H_NPP DATA_EoaH_Hole;

//==============================================================================
//	㩁@�V�X�e��
//==============================================================================
//--------------------------------------------------------------
/**
 * 㩏�����
 * @param	fes		FE_SYS_PTR
 * @retval	FE_HOLE_PTR	FE_HOLE_PTR
 */
//--------------------------------------------------------------
void * FE_Hole_Init( FE_SYS *fes )
{
	FE_HOLE_PTR sd;

	sd = FE_AllocClearMemory( fes, FE_HOLE_SIZE, ALLOC_FR, 0 );
	sd->fes = fes;
	
	Hole_GraphicInit( sd );
	
	return( sd );
}

//--------------------------------------------------------------
/**
 * 㩍폜
 * @param	sd		FE_HOLE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_Hole_Delete( void *work )
{
	FE_HOLE_PTR sd = work;
	Hole_GraphicDelete( sd );
	FE_FreeMemory( sd );
}

//==============================================================================
//	�	�p�[�c
//==============================================================================

//==============================================================================
//	㩁@�O���t�B�b�N
//==============================================================================
//--------------------------------------------------------------
/**
 * � �O���t�B�b�N������
 * @param	sd	FE_HOLE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Hole_GraphicInit( FE_HOLE_PTR sd )
{
    int i;
    for(i = 0;i < 32;i++){
        FE_simple3DModelInit( sd->fes, NARC_fldeff_ug_strap_01_nsbmd+i, ALLOC_FR,
                              &sd->render[i], &sd->model[i], &sd->res_file[i] );
    }
    FE_simple3DModelInit( sd->fes, NARC_fldeff_hole_nsbmd, ALLOC_FR,
                          &sd->render[i], &sd->model[i], &sd->res_file[i] );

}

//--------------------------------------------------------------
/**
 * � �O���t�B�b�N�폜
 * @param	sd	FE_HOLE_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Hole_GraphicDelete( FE_HOLE_PTR sd )
{
    int i;
    for(i = 0;i < 33;i++){
        FE_FreeMemory( sd->res_file[i] );
    }
}

//==============================================================================
//	㩁@EOA
//==============================================================================
//--------------------------------------------------------------
/**
 * �g���b�v�ǉ�
 * @param	fldobj		FIELD_OBJ_PTR
 * @retval	EOA_PTR
 */
//--------------------------------------------------------------
EOA_PTR FE_Hole_Add(  FIELDSYS_WORK *fsys, int x, int z, int scale, int modelNo)//NNSG3dResMdl *model )
{
	int param,pri;
	HOLE_ADD_H head;
	FE_SYS *fes;
	VecFx32 mtx;
    EOA_PTR eoa;
	HOLE_WORK *work;
	
    fes = fsys->fes;
	head.fes = fes;
	head.hole = FE_EffectWorkGet( fes, FE_UG_TRAP_HOLE );
	head.init_gx = x;
	head.init_gz = z;
	head.fsys = fsys;
	mtx.x = GRID_SIZE_FX32( x ) + (FX32_ONE * 9 );
	mtx.y = 0;
	mtx.z = GRID_SIZE_FX32( z );
	param = 0;
	eoa = FE_EoaAddNpp( fes, &DATA_EoaH_Hole, &mtx, param, &head, 0xff );
    if(eoa){
        work = EOA_LocalWorkGet( eoa );
        work->modelNo = modelNo;
        work->scale = scale;
        work->maxScale = scale;
//        NNS_G3dRenderObjInit( &work->render, model );
    }
    return eoa;
}

//--------------------------------------------------------------
/**
 * �傫�����ω�����g���b�v�ǉ�
 * @param	fldobj		FIELD_OBJ_PTR
 * @retval	EOA_PTR
 */
//--------------------------------------------------------------
EOA_PTR FE_ScaleHole_Add(  FIELDSYS_WORK *fsys, int x, int z, int scale,int modelNo) //, NNSG3dResMdl *model )
{
	HOLE_WORK *work;
    EOA_PTR eoa = FE_Hole_Add(fsys, x, z, scale, modelNo);
    if(eoa){
        work = EOA_LocalWorkGet( eoa );
        work->scale = 0;
        work->maxScale = scale;
    }
    return eoa;
}

//--------------------------------------------------------------
/**
 * EOA 㩁@������
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	int		TRUE=����I���BFALSE=�ُ�I��
 */
//--------------------------------------------------------------
static int EoaHole_Init( EOA_PTR eoa, void *wk )
{
	HOLE_WORK *work;
	const HOLE_ADD_H *head;
    VecFx32 vec;
	
	work = wk;
	head = EOA_AddPtrGet( eoa );
	work->head = *head;

	vec.x = GRID_SIZE_FX32( work->head.init_gx ) + (FX32_ONE * 9 );
	vec.z = GRID_SIZE_FX32( work->head.init_gz );
    vec.y = 0;
    
	EOA_MatrixSet( eoa, &vec );

	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA 㩁@�폜
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaHole_Delete( EOA_PTR eoa, void *wk )
{
}

//--------------------------------------------------------------
/**
 * EOA 㩁@����
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaHole_Move( EOA_PTR eoa, void *wk )
{
    HOLE_WORK *work;
	work = wk;

    if(work->scale < work->maxScale){
        work->scale += 0.2;
    }
}

//--------------------------------------------------------------
/**
 * EOA 㩁@�`��
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaHole_Draw( EOA_PTR eoa, void *wk )
{
	HOLE_WORK *work;
	
	work = wk;
	
    {
		VecFx32 vec;
		VecFx32 scale = { FX32_ONE, FX32_ONE, FX32_ONE };
		MtxFx33 rot	  = { FX32_ONE, 0,0,0, FX32_ONE, 0,0,0,FX32_ONE};
		
		EOA_MatrixGet( eoa, &vec );

        scale.x *= work->scale;
        scale.y *= work->scale;
        scale.z *= work->scale;
		vec.x += -(FX32_ONE * 1) / 2;
		vec.y += -(FX32_ONE * 1);
		vec.z += HOLE_DRAW_Z_OFFSET;
		simple_3DModelDraw( &work->head.hole->render[work->modelNo], &vec, &rot, &scale );
	}
}

//--------------------------------------------------------------
///	�EOA_H
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_Hole =
{
	HOLE_WORK_SIZE,
	EoaHole_Init,
	EoaHole_Delete,
	EoaHole_Move,
	EoaHole_Draw,
};

