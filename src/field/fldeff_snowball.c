//******************************************************************************
/**
 * 
 * @file	fldeff_snowball.c
 * @brief	�t�B�[���hOBJ���
 * @author	kagaya
 * @data	05.07.13
 *
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "field_effect.h"
#include "fieldobj.h"

#include "fldeff_snowball.h"

//==============================================================================
//	define
//==============================================================================

//==============================================================================
//	typedef struct
//==============================================================================
//--------------------------------------------------------------
///	FE_SNOWBALL�^
//--------------------------------------------------------------
typedef struct _TAG_FE_SNOWBALL * FE_SNOWBALL_PTR;
typedef struct _TAG_FE_BOOK * FE_BOOK_PTR;
typedef struct _TAG_FE_DOOR2 * FE_DOOR2_PTR;

//--------------------------------------------------------------
///	FE_SNOWBALL�\����
//--------------------------------------------------------------
typedef struct _TAG_FE_SNOWBALL
{
	FE_SYS *fes;
	FLD_3DOBJ_MDL obj_mdl;
	FLD_3DOBJ_ANM obj_anm;
	NNSFndAllocator allocator;
}FE_SNOWBALL;

#define FE_SNOWBALL_SIZE (sizeof(FE_SNOWBALL)) 					///<FE_SNOWBALL�T�C�Y

//--------------------------------------------------------------
///	SNOWBALL_ADD_H�\����
//--------------------------------------------------------------
typedef struct
{
	FE_SYS *fes;
	FE_SNOWBALL_PTR sball;
	FIELD_OBJ_PTR fldobj;
}SNOWBALL_ADD_H;

//--------------------------------------------------------------
///	SNOWBALL_3DOBJ�\����
//--------------------------------------------------------------
typedef struct
{
	NNSG3dAnmObj *pAnmObj;
	NNSFndAllocator allocator;
	fx32 frame;
	FLD_3DOBJ obj;
}SNOWBALL_3DOBJ;

#define SNOWBALL_3DOBJ_SIZE (sizeof(SNOWBALL_3DOBJ))

//--------------------------------------------------------------
///	EOA_SNOWBALL_WORK�\����
//--------------------------------------------------------------
typedef struct
{
	int seq_no;
	int obj_id;
	int zone_id;
	int break_flag;
	SNOWBALL_ADD_H head;
	SNOWBALL_3DOBJ *obj;
}EOA_SNOWBALL_WORK;

#define EOA_SNOWBALL_WORK_SIZE (sizeof(EOA_SNOWBALL_WORK))

//==============================================================================
//	�v���g�^�C�v
//==============================================================================
static void SnowBall_GraphicInit( FE_SNOWBALL_PTR sball );
static void SnowBall_GraphicDelete( FE_SNOWBALL_PTR sball );

static const EOA_H_NPP DATA_EoaH_SnowBall;

//==============================================================================
//	��ʁ@�V�X�e��
//==============================================================================
//--------------------------------------------------------------
/**
 * ��ʏ�����
 * @param	fes		FE_SYS_PTR
 * @retval	FE_SNOWBALL_PTR		FE_FOOTMARK_PTR
 */
//--------------------------------------------------------------
void * FE_SnowBall_Init( FE_SYS *fes )
{
	FE_SNOWBALL_PTR sball;
	
	sball = FE_AllocClearMemory( fes, FE_SNOWBALL_SIZE, ALLOC_FR, 0 );
	sball->fes = fes;
	
	SnowBall_GraphicInit( sball );
	return( sball );
}

//--------------------------------------------------------------
/**
 * ��ʍ폜
 * @param	sball		FE_SNOWBALL_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_SnowBall_Delete( void *work )
{
	FE_SNOWBALL_PTR sball = work;
	SnowBall_GraphicDelete( sball );
	FE_FreeMemory( sball );
}

//==============================================================================
//	���	�p�[�c
//==============================================================================

//==============================================================================
//	��ʁ@�O���t�B�b�N
//==============================================================================
//--------------------------------------------------------------
/**
 * ��� �O���t�B�b�N������
 * @param	sball		FE_SNOWBALL_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void SnowBall_GraphicInit( FE_SNOWBALL_PTR sball )
{
	FE_InitAllocator( sball->fes, &sball->allocator );
	FE_3DObjMdlLoad( sball->fes, &sball->obj_mdl, NARC_fldeff_gym06_o1_nsbmd, ALLOC_FR );
	FE_3DObjAnmLoad( sball->fes, &sball->obj_anm, &sball->obj_mdl, &sball->allocator, 
		NARC_fldeff_gym06_o1_nsbtp, ALLOC_FR );
}

//--------------------------------------------------------------
/**
 * ��ʁ@�O���t�B�b�N�폜
 * @param	sball		FE_SNOWBALL_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void SnowBall_GraphicDelete( FE_SNOWBALL_PTR sball )
{
	FLD_3DObjMdlDelete( &sball->obj_mdl );	
	FLD_3DObjAnmDelete( &sball->obj_anm, &sball->allocator );	
}

//==============================================================================
//	��ʁ@EOA
//==============================================================================
//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ��ʒǉ�
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	eoa		EOA_PTR
 */
//--------------------------------------------------------------
EOA_PTR FE_FldOBJSnowBall_Add( FIELD_OBJ_PTR fldobj )
{
	EOA_PTR eoa;
	FE_SYS *fes;
	FE_SNOWBALL_PTR sball;
	SNOWBALL_ADD_H head;
	
	fes = FE_FieldOBJ_FE_SYS_Get( fldobj );
	sball = FE_EffectWorkGet( fes, FE_FLD_SNOWBALL );
	
	head.fes = fes;
	head.sball = sball;
	head.fldobj = fldobj;
	
	{
		VecFx32 mtx = {0,0,0};
		int pri = FieldOBJ_TCBPriGet( fldobj, FLDOBJ_TCBPRI_OFFS_AFTER );
		eoa = FE_EoaAddNpp( fes, &DATA_EoaH_SnowBall, &mtx, 0, &head, pri );
	}
	
	return( eoa );
}

//--------------------------------------------------------------
/**
 * �ዅ�@����A�j������
 * @param	eoa		EOA_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_FldOBJSnowBall_BreakAnimeSet( EOA_PTR eoa )
{
	EOA_SNOWBALL_WORK *work = EOA_LocalWorkGet( eoa );
	work->break_flag = TRUE;
	work->obj->frame = 0;
}

//--------------------------------------------------------------
/**
 * EOA ��ʁ@������
 * @param	eoa	EOA_PTR
 * @param	wk	eoa work *
 * @retval	int TRUE=����I���BFALSE=�ُ�I��
 */
//--------------------------------------------------------------
static int EoaSnowBall_Init( EOA_PTR eoa, void *wk )
{
	SNOWBALL_3DOBJ *obj;
	EOA_SNOWBALL_WORK *work;
	const SNOWBALL_ADD_H *head;
	
	work = wk;
	head = EOA_AddPtrGet( eoa );
	work->head = *head;
	
	obj = FE_AllocClearMemory( work->head.fes, SNOWBALL_3DOBJ_SIZE, ALLOC_LO, 0 );
	work->obj = obj;
	
	FE_InitAllocator( work->head.fes, &obj->allocator );
	
	obj->pAnmObj = NNS_G3dAllocAnmObj( 
			&obj->allocator,
			work->head.sball->obj_anm.pOneResAnm,
			work->head.sball->obj_mdl.pModel );
	
	NNS_G3dAnmObjInit(
		obj->pAnmObj,
		work->head.sball->obj_anm.pOneResAnm,
		work->head.sball->obj_mdl.pModel,
		work->head.sball->obj_mdl.pMdlTex );
	
	FLD_3DObjInit( &obj->obj, &work->head.sball->obj_mdl );
	NNS_G3dRenderObjAddAnmObj( &obj->obj.render, obj->pAnmObj );
	
	work->obj_id = FieldOBJ_OBJIDGet( work->head.fldobj );
	work->zone_id = FieldOBJ_ZoneIDGet( work->head.fldobj );
	
	{
		VecFx32 mtx,d_mtx;
		FIELD_OBJ_PTR fldobj = work->head.fldobj;
		
		FieldOBJ_VecPosGet( fldobj, &mtx );
		FieldOBJ_VecDrawOffsGet( fldobj, &d_mtx );
		
		mtx.x += d_mtx.x + FLDOBJ_BLACT_X_GROUND_OFFS_FX32;
		mtx.y += d_mtx.y + FLDOBJ_BLACT_Y_GROUND_OFFS_FX32;
		mtx.z += d_mtx.z + FLDOBJ_BLACT_Z_GROUND_OFFS_FX32 - (FX32_ONE * 6);
		
		EOA_MatrixSet( eoa, &mtx );
		FLD_3DObjSetMatrix( &obj->obj, mtx.x, mtx.y, mtx.z );
	}
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA ��ʁ@�폜
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaSnowBall_Delete( EOA_PTR eoa, void *wk )
{
	EOA_SNOWBALL_WORK *work = wk;
	SNOWBALL_3DOBJ *obj = work->obj;
	NNS_G3dFreeAnmObj( &obj->allocator, obj->pAnmObj );
	FE_FreeMemory( obj );
}

//--------------------------------------------------------------
/**
 * EOA ��ʁ@����
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaSnowBall_Move( EOA_PTR eoa, void *wk )
{
	EOA_SNOWBALL_WORK *work = wk;
	SNOWBALL_3DOBJ *obj = work->obj;
	FIELD_OBJ_PTR fldobj = work->head.fldobj;
	
	if( work->break_flag == FALSE ){
		if( FieldOBJ_CheckSameID(fldobj,work->obj_id,work->zone_id) == FALSE ){
			OS_Printf( "��ʁ@ID�Ⴂ�ɂ��폜\n" );
			FE_EoaDelete( eoa );
			return;
		}
	}else{
		fx32 end_frame = NNS_G3dAnmObjGetNumFrame( obj->pAnmObj );
		obj->frame += FX32_ONE;
		
		if( obj->frame > end_frame ){
			OS_Printf( "��ʁ@�A�j���I���ɂ��폜\n" );
			FE_EoaDelete( eoa );
			return;
		}
		
		NNS_G3dAnmObjSetFrame( obj->pAnmObj, obj->frame );
	}
	
	if( work->break_flag == FALSE ){
		VecFx32 mtx,d_mtx;
			
		FieldOBJ_VecPosGet( fldobj, &mtx );
		FieldOBJ_VecDrawOffsGet( fldobj, &d_mtx );
		
		mtx.x += d_mtx.x + FLDOBJ_BLACT_X_GROUND_OFFS_FX32;
		mtx.y += d_mtx.y + FLDOBJ_BLACT_Y_GROUND_OFFS_FX32;
		mtx.z += d_mtx.z + FLDOBJ_BLACT_Z_GROUND_OFFS_FX32 - (FX32_ONE * 6);
		
		EOA_MatrixSet( eoa, &mtx );
		FLD_3DObjSetMatrix( &obj->obj, mtx.x, mtx.y, mtx.z );
	}
}

//--------------------------------------------------------------
/**
 * EOA ��ʁ@�`��
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaSnowBall_Draw( EOA_PTR eoa, void *wk )
{
	EOA_SNOWBALL_WORK *work = wk;
	SNOWBALL_3DOBJ *obj = work->obj;
	FLD_3DObjDraw( &obj->obj );
}

//==============================================================================
//	data
//==============================================================================
//--------------------------------------------------------------
///	���EOA_H
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_SnowBall =
{
	EOA_SNOWBALL_WORK_SIZE,
	EoaSnowBall_Init,
	EoaSnowBall_Delete,
	EoaSnowBall_Move,
	EoaSnowBall_Draw,
};

//******************************************************************************
/**
 * �t�B�[���hOBJ�{
 */
//******************************************************************************
//==============================================================================
//	define
//==============================================================================

//==============================================================================
//	typedef struct
//==============================================================================
//--------------------------------------------------------------
///	FE_BOOK�\����
//--------------------------------------------------------------
typedef struct _TAG_FE_BOOK
{
	FE_SYS *fes;
	NNSG3dRenderObj render;
	NNSG3dResMdl *model;
	NNSG3dResFileHeader *res_file;
}FE_BOOK;

#define FE_BOOK_SIZE (sizeof(FE_BOOK)) 					///<FE_BOOK�T�C�Y

//--------------------------------------------------------------
///	BOOK_ADD_H�\����
//--------------------------------------------------------------
typedef struct
{
	FE_SYS *fes;
	FE_BOOK_PTR book;
	FIELD_OBJ_PTR fldobj;
}BOOK_ADD_H;

//--------------------------------------------------------------
///	EOA_BOOK_WORK�\����
//--------------------------------------------------------------
typedef struct
{
	int seq_no;
	int obj_id;
	int zone_id;
	BOOK_ADD_H head;
}EOA_BOOK_WORK;

#define EOA_BOOK_WORK_SIZE (sizeof(EOA_BOOK_WORK))

//==============================================================================
//	�v���g�^�C�v
//==============================================================================
static void Book_GraphicInit( FE_BOOK_PTR book );
static void Book_GraphicDelete( FE_BOOK_PTR book );

static const EOA_H_NPP DATA_EoaH_Book;

//==============================================================================
//	�{�@�V�X�e��
//==============================================================================
//--------------------------------------------------------------
/**
 * �{������
 * @param	fes		FE_SYS_PTR
 * @retval	FE_BOOK_PTR		FE_FOOTMARK_PTR
 */
//--------------------------------------------------------------
void * FE_Book_Init( FE_SYS *fes )
{
	FE_BOOK_PTR book;
	
	book = FE_AllocClearMemory( fes, FE_BOOK_SIZE, ALLOC_FR, 0 );
	book->fes = fes;
	
	Book_GraphicInit( book );
	return( book );
}

//--------------------------------------------------------------
/**
 * �{�폜
 * @param	book		FE_BOOK_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_Book_Delete( void *work )
{
	FE_BOOK_PTR book = work;
	Book_GraphicDelete( book );
	FE_FreeMemory( book );
}

//==============================================================================
//	�{	�p�[�c
//==============================================================================

//==============================================================================
//	�{�@�O���t�B�b�N
//==============================================================================
//--------------------------------------------------------------
/**
 * �{ �O���t�B�b�N������
 * @param	book		FE_BOOK_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Book_GraphicInit( FE_BOOK_PTR book )
{
	FE_simple3DModelInit( book->fes, NARC_fldeff_book_nsbmd, ALLOC_FR,
			&book->render, &book->model, &book->res_file );
}

//--------------------------------------------------------------
/**
 * �{�@�O���t�B�b�N�폜
 * @param	book		FE_BOOK_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Book_GraphicDelete( FE_BOOK_PTR book )
{
	FE_FreeMemory( book->res_file );
}

//==============================================================================
//	�{�@EOA
//==============================================================================
//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ�{�ǉ�
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	eoa		EOA_PTR
 */
//--------------------------------------------------------------
EOA_PTR FE_FldOBJBook_Add( FIELD_OBJ_PTR fldobj )
{
	EOA_PTR eoa;
	FE_SYS *fes;
	FE_BOOK_PTR book;
	BOOK_ADD_H head;
	
	fes = FE_FieldOBJ_FE_SYS_Get( fldobj );
	book = FE_EffectWorkGet( fes, FE_FLD_BOOK );
	
	head.fes = fes;
	head.book = book;
	head.fldobj = fldobj;
	
	{
		VecFx32 mtx = {0,0,0};
		int pri = FieldOBJ_TCBPriGet( fldobj, FLDOBJ_TCBPRI_OFFS_AFTER );
		eoa = FE_EoaAddNpp( fes, &DATA_EoaH_Book, &mtx, 0, &head, pri );
	}
	
	return( eoa );
}

//--------------------------------------------------------------
/**
 * EOA �{�@������
 * @param	eoa	EOA_PTR
 * @param	wk	eoa work *
 * @retval	int TRUE=����I���BFALSE=�ُ�I��
 */
//--------------------------------------------------------------
static int EoaBook_Init( EOA_PTR eoa, void *wk )
{
	EOA_BOOK_WORK *work;
	const BOOK_ADD_H *head;
	
	work = wk;
	head = EOA_AddPtrGet( eoa );
	work->head = *head;
	
	work->obj_id = FieldOBJ_OBJIDGet( work->head.fldobj );
	work->zone_id = FieldOBJ_ZoneIDGet( work->head.fldobj );
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA �{�@�폜
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaBook_Delete( EOA_PTR eoa, void *wk )
{
}

//--------------------------------------------------------------
/**
 * EOA �{�@����
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaBook_Move( EOA_PTR eoa, void *wk )
{
	EOA_BOOK_WORK *work;
	FIELD_OBJ_PTR fldobj;
	
	work = wk;
	fldobj = work->head.fldobj;
	
	if( FieldOBJ_CheckSameID(fldobj,work->obj_id,work->zone_id) == FALSE ){
		FE_EoaDelete( eoa );
		return;
	}
	
	{
		VecFx32 mtx,d_mtx;
		
		FieldOBJ_VecPosGet( fldobj, &mtx );
		FieldOBJ_VecDrawOffsGet( fldobj, &d_mtx );
		
		mtx.x += d_mtx.x + FLDOBJ_BLACT_X_GROUND_OFFS_FX32;
		mtx.y += d_mtx.y + FLDOBJ_BLACT_Y_GROUND_OFFS_FX32;
		mtx.z += d_mtx.z + FLDOBJ_BLACT_Z_GROUND_OFFS_FX32 - (FX32_ONE * 6);
		
		EOA_MatrixSet( eoa, &mtx );
	}
}

//--------------------------------------------------------------
/**
 * EOA �{�@�`��
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaBook_Draw( EOA_PTR eoa, void *wk )
{
	EOA_BOOK_WORK *work;
	
	work = wk;
	
	{
		VecFx32 vec;
		VecFx32 scale = { FX32_ONE, FX32_ONE, FX32_ONE };
		MtxFx33 rot	  = { FX32_ONE, 0,0,0, FX32_ONE, 0,0,0,FX32_ONE};
		
		EOA_MatrixGet( eoa, &vec );
		simple_3DModelDraw( &work->head.book->render, &vec, &rot, &scale );
	}
}

//******************************************************************************
/**
 * �t�B�[���hOBJ�h�A�Q
 */
//******************************************************************************
//==============================================================================
//	define
//==============================================================================

//==============================================================================
//	typedef struct
//==============================================================================
//--------------------------------------------------------------
///	FE_DOOR2�\����
//--------------------------------------------------------------
typedef struct _TAG_FE_DOOR2
{
	FE_SYS *fes;
	NNSG3dRenderObj render;
	NNSG3dResMdl *model;
	NNSG3dResFileHeader *res_file;
}FE_DOOR2;

#define FE_DOOR2_SIZE (sizeof(FE_DOOR2)) 					///<FE_DOOR2�T�C�Y

//--------------------------------------------------------------
///	DOOR2_ADD_H�\����
//--------------------------------------------------------------
typedef struct
{
	FE_SYS *fes;
	FE_DOOR2_PTR door2;
	FIELD_OBJ_PTR fldobj;
}DOOR2_ADD_H;

//--------------------------------------------------------------
///	EOA_DOOR2_WORK�\����
//--------------------------------------------------------------
typedef struct
{
	int seq_no;
	int obj_id;
	int zone_id;
	DOOR2_ADD_H head;
}EOA_DOOR2_WORK;

#define EOA_DOOR2_WORK_SIZE (sizeof(EOA_DOOR2_WORK))

//==============================================================================
//	�v���g�^�C�v
//==============================================================================
static void Door2_GraphicInit( FE_DOOR2_PTR door2 );
static void Door2_GraphicDelete( FE_DOOR2_PTR door2 );

static const EOA_H_NPP DATA_EoaH_Door2;

//==============================================================================
//	�h�A�Q�@�V�X�e��
//==============================================================================
//--------------------------------------------------------------
/**
 * �h�A�Q������
 * @param	fes		FE_SYS_PTR
 * @retval	FE_DOOR2_PTR		FE_FOOTMARK_PTR
 */
//--------------------------------------------------------------
void * FE_Door2_Init( FE_SYS *fes )
{
	FE_DOOR2_PTR door2;
	
	door2 = FE_AllocClearMemory( fes, FE_DOOR2_SIZE, ALLOC_FR, 0 );
	door2->fes = fes;
	
	Door2_GraphicInit( door2 );
	return( door2 );
}

//--------------------------------------------------------------
/**
 * �h�A�Q�폜
 * @param	door2		FE_DOOR2_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_Door2_Delete( void *work )
{
	FE_DOOR2_PTR door2 = work;
	Door2_GraphicDelete( door2 );
	FE_FreeMemory( door2 );
}

//==============================================================================
//	�h�A�Q�@�O���t�B�b�N
//==============================================================================
//--------------------------------------------------------------
/**
 * �h�A�Q �O���t�B�b�N������
 * @param	door2		FE_DOOR2_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Door2_GraphicInit( FE_DOOR2_PTR door2 )
{
	FE_simple3DModelInit( door2->fes, NARC_fldeff_door2_nsbmd, ALLOC_FR,
			&door2->render, &door2->model, &door2->res_file );
}

//--------------------------------------------------------------
/**
 * �h�A�Q�@�O���t�B�b�N�폜
 * @param	door2		FE_DOOR2_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void Door2_GraphicDelete( FE_DOOR2_PTR door2 )
{
	FE_FreeMemory( door2->res_file );
}

//==============================================================================
//	�h�A�Q�@EOA
//==============================================================================
//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ�h�A�Q�ǉ�
 * @param	fldobj	FIELD_OBJ_PTR
 * @retval	eoa		EOA_PTR
 */
//--------------------------------------------------------------
EOA_PTR FE_FldOBJDoor2_Add( FIELD_OBJ_PTR fldobj )
{
	EOA_PTR eoa;
	FE_SYS *fes;
	FE_DOOR2_PTR door2;
	DOOR2_ADD_H head;
	
	fes = FE_FieldOBJ_FE_SYS_Get( fldobj );
	door2 = FE_EffectWorkGet( fes, FE_FLD_DOOR2 );
	
	head.fes = fes;
	head.door2 = door2;
	head.fldobj = fldobj;
	
	{
		VecFx32 mtx = {0,0,0};
		int pri = FieldOBJ_TCBPriGet( fldobj, FLDOBJ_TCBPRI_OFFS_AFTER );
		eoa = FE_EoaAddNpp( fes, &DATA_EoaH_Door2, &mtx, 0, &head, pri );
	}
	
	return( eoa );
}

//--------------------------------------------------------------
/**
 * EOA �h�A�Q�@������
 * @param	eoa	EOA_PTR
 * @param	wk	eoa work *
 * @retval	int TRUE=����I���BFALSE=�ُ�I��
 */
//--------------------------------------------------------------
static int EoaDoor2_Init( EOA_PTR eoa, void *wk )
{
	EOA_DOOR2_WORK *work;
	const DOOR2_ADD_H *head;
	
	work = wk;
	head = EOA_AddPtrGet( eoa );
	work->head = *head;
	
	work->obj_id = FieldOBJ_OBJIDGet( work->head.fldobj );
	work->zone_id = FieldOBJ_ZoneIDGet( work->head.fldobj );
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * EOA �h�A�Q�@�폜
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaDoor2_Delete( EOA_PTR eoa, void *wk )
{
}

//--------------------------------------------------------------
/**
 * EOA �h�A�Q�@����
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaDoor2_Move( EOA_PTR eoa, void *wk )
{
	EOA_DOOR2_WORK *work;
	FIELD_OBJ_PTR fldobj;
	
	work = wk;
	fldobj = work->head.fldobj;
	
	if( FieldOBJ_CheckSameID(fldobj,work->obj_id,work->zone_id) == FALSE ){
		FE_EoaDelete( eoa );
		return;
	}
	
	{
		VecFx32 mtx,d_mtx;
		
		FieldOBJ_VecPosGet( fldobj, &mtx );
		FieldOBJ_VecDrawOffsGet( fldobj, &d_mtx );
		
		mtx.x += d_mtx.x + FLDOBJ_BLACT_X_GROUND_OFFS_FX32;
		mtx.y += d_mtx.y + FLDOBJ_BLACT_Y_GROUND_OFFS_FX32;
		mtx.z += d_mtx.z + FLDOBJ_BLACT_Z_GROUND_OFFS_FX32 - (FX32_ONE * 6);
		
		EOA_MatrixSet( eoa, &mtx );
	}
}

//--------------------------------------------------------------
/**
 * EOA �h�A�Q�@�`��
 * @param	eoa		EOA_PTR
 * @param	wk		eoa work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void EoaDoor2_Draw( EOA_PTR eoa, void *wk )
{
	EOA_DOOR2_WORK *work;
	
	work = wk;
	
	{
		VecFx32 vec;
		VecFx32 scale = { FX32_ONE, FX32_ONE, FX32_ONE };
		MtxFx33 rot	  = { FX32_ONE, 0,0,0, FX32_ONE, 0,0,0,FX32_ONE};
		
		EOA_MatrixGet( eoa, &vec );
		simple_3DModelDraw( &work->head.door2->render, &vec, &rot, &scale );
	}
}

//==============================================================================
//	data
//==============================================================================
//--------------------------------------------------------------
///	�{EOA_H
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_Book =
{
	EOA_BOOK_WORK_SIZE,
	EoaBook_Init,
	EoaBook_Delete,
	EoaBook_Move,
	EoaBook_Draw,
};

//--------------------------------------------------------------
///	�h�A�QEOA_H
//--------------------------------------------------------------
static const EOA_H_NPP DATA_EoaH_Door2 =
{
	EOA_DOOR2_WORK_SIZE,
	EoaDoor2_Init,
	EoaDoor2_Delete,
	EoaDoor2_Move,
	EoaDoor2_Draw,
};
