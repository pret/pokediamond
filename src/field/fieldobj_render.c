//******************************************************************************
/**
 * 
 * @file	fieldobj_render.c
 * @brief	フィールドOBJのレンダOBJ管理
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
///	RDOBJDATA構造体
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
///	FLDOBJ_rdcont構造体
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
//	プロトタイプ
//==============================================================================
static FIELD_OBJ_RENDER_CONT_PTR FldOBJRdC_AllocMemory( int heap_id );
static void FldOBJRdC_FreeMemory( FIELD_OBJ_RENDER_CONT_PTR rdcont );

static void FldOBJRdC_GraphicInit( FIELD_OBJ_RENDER_CONT_PTR rdcont );
static void FldOBJRdC_GraphicDelete( FIELD_OBJ_RENDER_CONT_PTR rdcont );

static RDOBJDATA * RdC_SpaceSearch( RDOBJDATA *data, int max );
static RDOBJDATA * RdC_CodeSearch( RDOBJDATA *data, int code, int max );
static void RdC_Delete( RDOBJDATA *data );

//==============================================================================
//	レンダOBJ管理　システム
//==============================================================================
//--------------------------------------------------------------
/**
 * フィールドOBJレンダOBJ管理初期化
 * @param	fes		SYS_PTR
 * @param	heap_id	ヒープID
 * @retval	FIELD_OBJ_RENDER_CONT_PTR 初期化されたFIELD_OBJ_RENDER_CONT_PTR
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
 * レンダOBJ管理削除
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
//	レンダOBJ管理	パーツ
//==============================================================================
//--------------------------------------------------------------
/**
 * レンダOBJ管理メモリ確保
 * @param	heap_id		ヒープID
 * @retval	FIELD_OBJ_RENDER_CONT_PTR	確保したFIELD_OBJ_RENDER_CONT_PTR
 */
//--------------------------------------------------------------
static FIELD_OBJ_RENDER_CONT_PTR FldOBJRdC_AllocMemory( int heap_id )
{
	FIELD_OBJ_RENDER_CONT_PTR rdcont = sys_AllocMemory( heap_id, FIELD_OBJ_RENDER_CONT_SIZE );
	GF_ASSERT( rdcont != NULL && "FldOBJrdcont_AllocMemory()メモリ確保失敗" );
	memset( rdcont, 0, FIELD_OBJ_RENDER_CONT_SIZE );
	return( rdcont );
}

//--------------------------------------------------------------
/**
 * レンダOBJ管理メモリ削除
 * @param	rdcont		FIELD_OBJ_RENDER_CONT_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJRdC_FreeMemory( FIELD_OBJ_RENDER_CONT_PTR rdcont )
{
	sys_FreeMemory( rdcont->heap_id, rdcont );
}

//==============================================================================
//	レンダOBJ管理　グラフィック
//==============================================================================
//--------------------------------------------------------------
/**
 * レンダOBJ管理 グラフィック初期化
 * @param	rdcont		FIELD_OBJ_RENDER_CONT_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
static void FldOBJRdC_GraphicInit( FIELD_OBJ_RENDER_CONT_PTR rdcont )
{
}

//--------------------------------------------------------------
/**
 * レンダOBJ管理　グラフィック削除
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
//	レンダOBJ管理　管理処理
//==============================================================================
//--------------------------------------------------------------
/**
 * レンダOBJ管理　管理処理初期化
 * @param	fes		SYS_PTR
 * @param	max		OBJ管理最大数
 * @retval	nothing
 */
//--------------------------------------------------------------
void FieldOBJ_RenderCont_RegistInit( FIELD_OBJ_RENDER_CONT_PTR rdcont, int max )
{
	rdcont->obj_max = max;
	max *= RDOBJDATA_SIZE;
	rdcont->rdobjdata = sys_AllocMemory( rdcont->heap_id, max );
	GF_ASSERT( rdcont->rdobjdata != NULL && "FieldOBJ_RenderContRegistInit()メモリ確保失敗" );
	memset( rdcont->rdobjdata, NULL, max );
}

//--------------------------------------------------------------
/**
 * レンダOBJ管理　simple_3DModelSetResFileAlready()によるOBJ登録
 * @param	fes		SYS_PTR
 * @param	max		OBJ管理最大数
 * @retval	int		TRUE=登録完了 FALSE=登録できない
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
 * レンダOBJ管理　指定されたcodeを削除
 * @param	fes		SYS_PTR
 * @param	max		OBJ管理最大数
 * @retval	int		TRUE=登録完了 FALSE=登録できない
 */
//--------------------------------------------------------------
void FieldOBJ_RenderCont_OBJRegFree( FIELD_OBJ_RENDER_CONT_PTR rdcont, int code )
{
	RDOBJDATA *data = RdC_CodeSearch( rdcont->rdobjdata, code, rdcont->obj_max );
	RdC_Delete( data );
}

//--------------------------------------------------------------
/**
 * レンダOBJ管理　指定されたcodeのレンダ取得
 * @param	fes		SYS_PTR
 * @param	max		OBJ管理最大数
 * @retval	int		TRUE=登録完了 FALSE=登録できない
 */
//--------------------------------------------------------------
NNSG3dRenderObj * FieldOBJ_RenderCont_OBJRenderGet( FIELD_OBJ_RENDER_CONT_PTR rdcont, int code )
{
	RDOBJDATA *data = RdC_CodeSearch( rdcont->rdobjdata, code, rdcont->obj_max );
	return( &data->render );
}

//--------------------------------------------------------------
/**
 * レンダOBJ管理　指定されたcodeのモデル取得
 * @param	fes		SYS_PTR
 * @param	max		OBJ管理最大数
 * @retval	int		TRUE=登録完了 FALSE=登録できない
 */
//--------------------------------------------------------------
NNSG3dResMdl * FldOBJrdcont_OBJModelGet( FIELD_OBJ_RENDER_CONT_PTR rdcont, int code )
{
	RDOBJDATA *data = RdC_CodeSearch( rdcont->rdobjdata, code, rdcont->obj_max );
	return( data->model );
}

//==============================================================================
//	レンダOBJ　パーツ
//==============================================================================
//--------------------------------------------------------------
/**
 * レンダOBJ管理　スペース探し
 * @param	data	RDOBJDATA
 * @param	max		data要素数
 * @retval	RDOBJDATA*	空きRDOBJDATA *
 */
//--------------------------------------------------------------
static RDOBJDATA * RdC_SpaceSearch( RDOBJDATA *data, int max )
{
	int i = 0;
	while( i < max ){ if(data->res_file == NULL){return(data);} i++; data++; }
	GF_ASSERT( 0 && "rdcont_SpaceSeach()空きなし" );
	return( NULL );
}

//--------------------------------------------------------------
/**
 * レンダOBJ管理　コード探し
 * @param	data	RDOBJDATA
 * @param	code	検索コード
 * @param	max		data要素数
 * @retval	RDOBJDATA*	codeに一致するRDOBJDATA *
 */
//--------------------------------------------------------------
static RDOBJDATA * RdC_CodeSearch( RDOBJDATA *data, int code, int max )
{
	int i = 0;
	while( i < max ){ if(data->code == code){return(data);} i++; data++; }
	GF_ASSERT( 0 && "rdcont_CodeSearch()登録されていないコードです" );
	return( NULL );
}

//--------------------------------------------------------------
/**
 * レンダOBJ管理　削除
 * @param	data	削除するRDOBJDATA
 * @retval	nothing
 */
//--------------------------------------------------------------
static void RdC_Delete( RDOBJDATA *data )
{
	sys_FreeMemoryEz( data->res_file );
	memset( data, NULL, RDOBJDATA_SIZE );
}

//==============================================================================
//	フィールドOBJ レンダOBJ
//==============================================================================

