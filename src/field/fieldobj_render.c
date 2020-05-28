//******************************************************************************
/**
 * 
 * @file	fieldobj_render.c
 * @brief	�t�B�[���hOBJ�̃����_OBJ�Ǘ�
 * @author	kagaya
 * @data	05.07.13
 *
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "fieldobj.h"

//==============================================================================
//	define
//==============================================================================

//==============================================================================
//	typedef struct
//==============================================================================
//--------------------------------------------------------------
///	RDOBJDATA�\����
//--------------------------------------------------------------
typedef struct
{
	int code;
	NNSG3dRenderObj render;
	NNSG3dResMdl *model;
	NNSG3dResFileHeader *res_file;
}RDOBJDATA;

#define RDOBJDATA_SIZE (sizeof(RDOBJDATA))

//--------------------------------------------------------------
///	FLDOBJ_rdcont�\����
//--------------------------------------------------------------
typedef struct _TAG_FIELD_OBJ_RENDER_CONT
{
	int heap_id;
	int obj_max;
	CONST_FIELD_OBJ_SYS_PTR fos;
	RDOBJDATA *rdobjdata;
}FIELD_OBJ_RENDER_CONT;

#define FIELD_OBJ_RENDER_CONT_SIZE (sizeof(FIELD_OBJ_RENDER_CONT)) 

//==============================================================================
//	�v���g�^�C�v
//==============================================================================
static FIELD_OBJ_RENDER_CONT_PTR FldOBJRdC_AllocMemory( int heap_id );
static void FldOBJRdC_FreeMemory( FIELD_OBJ_RENDER_CONT_PTR rdcont );

static void FldOBJRdC_GraphicInit( FIELD_OBJ_RENDER_CONT_PTR rdcont );
static void FldOBJRdC_GraphicDelete( FIELD_OBJ_RENDER_CONT_PTR rdcont );

static RDOBJDATA * RdC_SpaceSearch( RDOBJDATA *data, int max );
static RDOBJDATA * RdC_CodeSearch( RDOBJDATA *data, int code, int max );
static void RdC_Delete( RDOBJDATA *data );

//==============================================================================
//	�����_OBJ�Ǘ��@�V�X�e��
//==============================================================================
//--------------------------------------------------------------
/**
 * �t�B�[���hOBJ�����_OBJ�Ǘ�������
 * @param	fes		SYS_PTR
 * @param	heap_id	�q�[�vID
 * @retval	FIELD_OBJ_RENDER_CONT_PTR ���������ꂽFIELD_OBJ_RENDER_CONT_PTR
 */
//--------------------------------------------------------------
FIELD_OBJ_RENDER_CONT_PTR FieldOBJ_RenderCont_Init( CONST_FIELD_OBJ_SYS_PTR fos, u32 heap_id )
{
	FIELD_OBJ_RENDER_CONT_PTR rdcont;
	
	rdcont = FldOBJRdC_AllocMemory( heap_id );
	rdcont->heap_id = heap_id;
	rdcont->fos = fos;
	
	FldOBJRdC_GraphicInit( rdcont );
	
	return( rdcont );
}

//--------------------------------------------------------------
/**
 * �����_OBJ�Ǘ��폜
 * @param	rdcont		FIELD_OBJ_RENDER_CONT_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_RenderCont_Delete( FIELD_OBJ_RENDER_CONT_PTR rdcont )
{
	FldOBJRdC_GraphicDelete( rdcont );
	FldOBJRdC_FreeMemory( rdcont );
}

//==============================================================================
//	�����_OBJ�Ǘ�	�p�[�c
//==============================================================================
//--------------------------------------------------------------
/**
 * �����_OBJ�Ǘ��������m��
 * @param	heap_id		�q�[�vID
 * @retval	FIELD_OBJ_RENDER_CONT_PTR	�m�ۂ���FIELD_OBJ_RENDER_CONT_PTR
 */
//--------------------------------------------------------------
static FIELD_OBJ_RENDER_CONT_PTR FldOBJRdC_AllocMemory( int heap_id )
{
	FIELD_OBJ_RENDER_CONT_PTR rdcont = sys_AllocMemory( heap_id, FIELD_OBJ_RENDER_CONT_SIZE );
	GF_ASSERT( rdcont != NULL && "FldOBJrdcont_AllocMemory()�������m�ێ��s" );
	memset( rdcont, 0, FIELD_OBJ_RENDER_CONT_SIZE );
	return( rdcont );
}

//--------------------------------------------------------------
/**
 * �����_OBJ�Ǘ��������폜
 * @param	rdcont		FIELD_OBJ_RENDER_CONT_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJRdC_FreeMemory( FIELD_OBJ_RENDER_CONT_PTR rdcont )
{
	sys_FreeMemory( rdcont->heap_id, rdcont );
}

//==============================================================================
//	�����_OBJ�Ǘ��@�O���t�B�b�N
//==============================================================================
//--------------------------------------------------------------
/**
 * �����_OBJ�Ǘ� �O���t�B�b�N������
 * @param	rdcont		FIELD_OBJ_RENDER_CONT_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJRdC_GraphicInit( FIELD_OBJ_RENDER_CONT_PTR rdcont )
{
}

//--------------------------------------------------------------
/**
 * �����_OBJ�Ǘ��@�O���t�B�b�N�폜
 * @param	rdcont		FIELD_OBJ_RENDER_CONT_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJRdC_GraphicDelete( FIELD_OBJ_RENDER_CONT_PTR rdcont )
{
	if( rdcont->obj_max && rdcont->rdobjdata != NULL ){
		RDOBJDATA *data = rdcont->rdobjdata;
		
		do{
			if( data->res_file != NULL ){
				RdC_Delete( data );
			}
			
			data++;
			rdcont->obj_max--;
		}while( rdcont->obj_max );
		
		sys_FreeMemory( rdcont->heap_id, rdcont->rdobjdata );
	}
}

//==============================================================================
//	�����_OBJ�Ǘ��@�Ǘ�����
//==============================================================================
//--------------------------------------------------------------
/**
 * �����_OBJ�Ǘ��@�Ǘ�����������
 * @param	fes		SYS_PTR
 * @param	max		OBJ�Ǘ��ő吔
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_RenderCont_RegistInit( FIELD_OBJ_RENDER_CONT_PTR rdcont, int max )
{
	rdcont->obj_max = max;
	max *= RDOBJDATA_SIZE;
	rdcont->rdobjdata = sys_AllocMemory( rdcont->heap_id, max );
	GF_ASSERT( rdcont->rdobjdata != NULL && "FieldOBJ_RenderContRegistInit()�������m�ێ��s" );
	memset( rdcont->rdobjdata, NULL, max );
}

//--------------------------------------------------------------
/**
 * �����_OBJ�Ǘ��@simple_3DModelSetResFileAlready()�ɂ��OBJ�o�^
 * @param	fes		SYS_PTR
 * @param	max		OBJ�Ǘ��ő吔
 * @retval	int		TRUE=�o�^���� FALSE=�o�^�ł��Ȃ�
 */
//--------------------------------------------------------------
int FieldOBJ_RenderCont_OBJRegSimple( FIELD_OBJ_RENDER_CONT_PTR rdcont, 
		int code, ARCHANDLE *handle, u32 data_id, u32 heap_id )
{
	RDOBJDATA *data = RdC_SpaceSearch( rdcont->rdobjdata, rdcont->obj_max );
	data->res_file = ArchiveDataLoadAllocByHandle( handle, data_id, heap_id );
	simple_3DModelSetResFileAlready( &data->render, &data->model, &data->res_file );
	
	data->code = code;
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * �����_OBJ�Ǘ��@�w�肳�ꂽcode���폜
 * @param	fes		SYS_PTR
 * @param	max		OBJ�Ǘ��ő吔
 * @retval	int		TRUE=�o�^���� FALSE=�o�^�ł��Ȃ�
 */
//--------------------------------------------------------------
void FieldOBJ_RenderCont_OBJRegFree( FIELD_OBJ_RENDER_CONT_PTR rdcont, int code )
{
	RDOBJDATA *data = RdC_CodeSearch( rdcont->rdobjdata, code, rdcont->obj_max );
	RdC_Delete( data );
}

//--------------------------------------------------------------
/**
 * �����_OBJ�Ǘ��@�w�肳�ꂽcode�̃����_�擾
 * @param	fes		SYS_PTR
 * @param	max		OBJ�Ǘ��ő吔
 * @retval	int		TRUE=�o�^���� FALSE=�o�^�ł��Ȃ�
 */
//--------------------------------------------------------------
NNSG3dRenderObj * FieldOBJ_RenderCont_OBJRenderGet( FIELD_OBJ_RENDER_CONT_PTR rdcont, int code )
{
	RDOBJDATA *data = RdC_CodeSearch( rdcont->rdobjdata, code, rdcont->obj_max );
	return( &data->render );
}

//--------------------------------------------------------------
/**
 * �����_OBJ�Ǘ��@�w�肳�ꂽcode�̃��f���擾
 * @param	fes		SYS_PTR
 * @param	max		OBJ�Ǘ��ő吔
 * @retval	int		TRUE=�o�^���� FALSE=�o�^�ł��Ȃ�
 */
//--------------------------------------------------------------
NNSG3dResMdl * FldOBJrdcont_OBJModelGet( FIELD_OBJ_RENDER_CONT_PTR rdcont, int code )
{
	RDOBJDATA *data = RdC_CodeSearch( rdcont->rdobjdata, code, rdcont->obj_max );
	return( data->model );
}

//==============================================================================
//	�����_OBJ�@�p�[�c
//==============================================================================
//--------------------------------------------------------------
/**
 * �����_OBJ�Ǘ��@�X�y�[�X�T��
 * @param	data	RDOBJDATA
 * @param	max		data�v�f��
 * @retval	RDOBJDATA*	��RDOBJDATA *
 */
//--------------------------------------------------------------
static RDOBJDATA * RdC_SpaceSearch( RDOBJDATA *data, int max )
{
	int i = 0;
	while( i < max ){ if(data->res_file == NULL){return(data);} i++; data++; }
	GF_ASSERT( 0 && "rdcont_SpaceSeach()�󂫂Ȃ�" );
	return( NULL );
}

//--------------------------------------------------------------
/**
 * �����_OBJ�Ǘ��@�R�[�h�T��
 * @param	data	RDOBJDATA
 * @param	code	�����R�[�h
 * @param	max		data�v�f��
 * @retval	RDOBJDATA*	code�Ɉ�v����RDOBJDATA *
 */
//--------------------------------------------------------------
static RDOBJDATA * RdC_CodeSearch( RDOBJDATA *data, int code, int max )
{
	int i = 0;
	while( i < max ){ if(data->code == code){return(data);} i++; data++; }
	GF_ASSERT( 0 && "rdcont_CodeSearch()�o�^����Ă��Ȃ��R�[�h�ł�" );
	return( NULL );
}

//--------------------------------------------------------------
/**
 * �����_OBJ�Ǘ��@�폜
 * @param	data	�폜����RDOBJDATA
 * @retval	nothing
 */
//--------------------------------------------------------------
static void RdC_Delete( RDOBJDATA *data )
{
	sys_FreeMemoryEz( data->res_file );
	memset( data, NULL, RDOBJDATA_SIZE );
}

//==============================================================================
//	�t�B�[���hOBJ �����_OBJ
//==============================================================================

