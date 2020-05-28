//******************************************************************************
/**
 * 
 * @file	fldeff_trap.c
 * @brief	�t�B�[���hOBJ �
 * @author	k.ohno
 * @data	05.11.29
 *
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "field_effect.h"
#include "fieldobj.h"
#include "fldeff_trap.h"

//==============================================================================
//	define
//==============================================================================
//#define DEBUG_TRAP_WRITE_OFF	//��`��㩕`��OFF

//#define TRAP_DRAW_Z_OFFSET (FX32_ONE*(3))
#define TRAP_DRAW_Z_OFFSET (FX32_ONE*(5))			///<㩕`��I�t�Z�b�gZ��

//==============================================================================
//	typedef struct
//==============================================================================
//--------------------------------------------------------------
///	FE_TRAP�^
//--------------------------------------------------------------
typedef struct _TAG_FE_TRAP * FE_TRAP_PTR;

//--------------------------------------------------------------
///	FE_TRAP�\����
//--------------------------------------------------------------
typedef struct _TAG_FE_TRAP
{
	FE_SYS *fes;
	NNSG3dRenderObj render;
	NNSG3dResMdl *model;
	NNSG3dResFileHeader *res_file;
}FE_TRAP;

#define FE_TRAP_SIZE (sizeof(FE_TRAP)) ///<FE_TRAP�T�C�Y

//--------------------------------------------------------------
///	TRAP_ADD_H�\����
//--------------------------------------------------------------
typedef struct
{
	int init_gx;
	int init_gz;
	FIELDSYS_WORK *fsys;
	FE_SYS *fes;
	FE_TRAP_PTR trap;						///<FE_TRAP_PTR
}TRAP_ADD_H;

#define TRAP_ADD_H_SIZE (sizeof(TRAP_ADD_H)) ///<TRAP_ADD_H�T�C�Y

//--------------------------------------------------------------
///	TRAP_WORK�\����
//--------------------------------------------------------------
typedef struct
{
    int counter;    // ��������
	int obj_id;									///<㩑Ώ�OBJID
	int zone_id;								///<㩑Ώۃ]�[��ID
	int vanish_sw;								///<��\��SW
	TRAP_ADD_H head;							///<�ǉ�����TRAP_ADD_H
}TRAP_WORK;

#define TRAP_WORK_SIZE (sizeof(TRAP_WORK))	///<TRAP_WORK�T�C�Y

//==============================================================================
//	�v���g�^�C�v
//==============================================================================
static void Trap_GraphicInit( FE_TRAP_PTR sd );
static void Trap_GraphicDelete( FE_TRAP_PTR sd );

static const EOA_H_NPP DATA_EoaH_Trap;

//==============================================================================
//	㩁@�V�X�e��
//==============================================================================
//--------------------------------------------------------------
/**
 * 㩏�����
 * @param	fes		FE_SYS_PTR
 * @retval	void*	FE_TRAP_PTR
 */
//--------------------------------------------------------------
void * FE_Trap_Init( FE_SYS *fes )
{
	FE_TRAP_PTR sd;

	sd = FE_AllocClearMemory( fes, FE_TRAP_SIZE, ALLOC_FR, 0 );
	sd->fes = fes;
	
	Trap_GraphicInit( sd );
	
	return( sd );
}

//--------------------------------------------------------------
/**
 * 㩍폜
 * @param	sd		FE_TRAP_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_Trap_Delete( void *work )
{
	FE_TRAP_PTR sd = work;
	Trap_GraphicDelete( sd );
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
 * @param	sd	FE_TRAP_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Trap_GraphicInit( FE_TRAP_PTR sd )
{
	FE_simple3DModelInit( sd->fes, NARC_fldeff_kage_nsbmd, ALLOC_FR,
           &sd->render, &sd->model, &sd->res_file );
}

//--------------------------------------------------------------
/**
 * � �O���t�B�b�N�폜
 * @param	sd	FE_TRAP_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Trap_GraphicDelete( FE_TRAP_PTR sd )
{
    FE_FreeMemory( sd->res_file );
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
EOA_PTR FE_Trap_Add(  FIELDSYS_WORK *fsys, int x, int z, int liveTime )
{
	int param,pri;
	TRAP_ADD_H head;
	FE_SYS *fes;
	VecFx32 mtx;
    EOA_PTR eoa;
	TRAP_WORK *work;
	
    fes = fsys->fes;
	head.fes = fes;
	head.trap = FE_EffectWorkGet( fes, FE_UG_TRAP );
	head.init_gx = x;
	head.init_gz = z;
	head.fsys = fsys;
	mtx.x = GRID_SIZE_FX32( x ) + (FX32_ONE * 9 );
	mtx.y = 0;
	mtx.z = GRID_SIZE_FX32( z );
	param = 0;
	eoa = FE_EoaAddNpp( fes, &DATA_EoaH_Trap, &mtx, param, &head, 0xff );
	work = EOA_LocalWorkGet( eoa );
    work->counter = liveTime;
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
static int EoaTrap_Init( EOA_PTR eoa, void *wk )
{
	TRAP_WORK *work;
	const TRAP_ADD_H *head;
    VecFx32 vec;
	
	work = wk;
	head = EOA_AddPtrGet( eoa );
	work->head = *head;

	vec.x = GRID_SIZE_FX32( work->head.init_gx ) + (FX32_ONE * 9 );
	vec.z = GRID_SIZE_FX32( work->head.init_gz );
    vec.y = 0;
    
	EOA_MatrixSet( eoa, &vec );

    work->counter = 20;// @@OO test time
    
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
static void EoaTrap_Delete( EOA_PTR eoa, void *wk )
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
static void EoaTrap_Move( EOA_PTR eoa, void *wk )
{
    TRAP_WORK *work;
	work = wk;

    if(work->counter > 0){
        work->counter--;
        if(work->counter == 0){
            FE_EoaDelete( eoa );
        }
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
static void EoaTrap_Draw( EOA_PTR eoa, void *wk )
{
	TRAP_WORK *work;
	
	work = wk;
	
    {
		VecFx32 vec;
		VecFx32 scale = { FX32_ONE, FX32_ONE, FX32_ONE };
		MtxFx33 rot	  = { FX32_ONE, 0,0,0, FX32_ONE, 0,0,0,FX32_ONE};
		
		EOA_MatrixGet( eoa, &vec );
		
		vec.x += -(FX32_ONE * 1) / 2;
		vec.y += -(FX32_ONE * 1);
		vec.z += TRAP_DRAW_Z_OFFSET;
		simple_3DModelDraw_1mat1shape( &work->head.trap->render, &vec, &rot, &scale );
	}
}

//--------------------------------------------------------------
///	�EOA_H
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_Trap =
{
	TRAP_WORK_SIZE,
	EoaTrap_Init,
	EoaTrap_Delete,
	EoaTrap_Move,
	EoaTrap_Draw,
};

