//******************************************************************************
/**
 *
 * @file	localres.c
 * @brief	確保したリソース領域を更に配分して再利用しまくる。
 * @author	kagaya
 * @data	05.07.25
 *
 */
//******************************************************************************
#include "common.h"
#include "localres.h"

//==============================================================================
//	define
//==============================================================================
#define LRES_SEEK_SIZE (sizeof(u32))

//==============================================================================
//	typedef
//==============================================================================
//--------------------------------------------------------------
///	LRESID定義
//--------------------------------------------------------------
typedef struct _RESID		RESID;

//--------------------------------------------------------------
///	LRES構造体
//--------------------------------------------------------------
typedef struct _LRES
{
	u32 main_heap_id;								//確保するHEAP ID
	u32 reg_heap_id;								//登録するHEAP ID
	u32 resid_max;									//ID登録最大数
	u32 total_size;									//確保したサイズ
	u32 resid_total_size;							//ローカルリソース管理用ワーク最大サイズ
	RESID *resid_ptr;								//ローカルリソース管理ワーク *
};

#define LRES_SIZE (sizeof(LRES))	//LRESサイズ

//--------------------------------------------------------------
///	RESID構造体
//--------------------------------------------------------------
typedef struct _RESID
{
	void *alloc_ptr;								//確保しているリソース *　未確保=NULL
	u32 alloc_id;									//登録ID
};

#define RESID_SIZE (sizeof(RESID))	//RESIDサイズ

//==============================================================================
//	プロトタイプ
//==============================================================================
static void * lRes_AllocHeap( LRES *lres, u32 size, ALLOCTYPE type );
static void lRes_FreeHeap( void *alloc );
static RESID * lRes_IDSearch( LRES *lres, u32 id );
static RESID * lRes_IDSpaceSearch( LRES *lres );
static RESID * lRes_IDAllocSearch( LRES *lres, void *alloc );
static void lRes_ResIDInit( RESID *resid, u32 id, void *alloc );
static void lRes_ResIDDelete( RESID *resid );

#ifdef PM_DEBUG
#endif

//==============================================================================
//	local resource
//==============================================================================
//--------------------------------------------------------------
/**
 * LRES初期化
 * @param	main_heap_id	確保するHEAP ID
 * @param	reg_heap_id		確保した領域を識別するHEAP ID
 * @param	size			確保するサイズ
 * @param	regid_max		登録するID最大数。ID管理要らない場合は0指定
 * @retval	LRES*			確保したLRES *
 */
//--------------------------------------------------------------
LRES * LRes_Init( u32 main_heap_id, u32 reg_heap_id, u32 size, u32 resid_max )
{
	u32 resid_size,total_size;
	LRES *lres;
	
	resid_size = RESID_SIZE * resid_max;
	total_size = size + resid_size + LRES_SIZE;
	
	{
		BOOL ret = sys_CreateHeap( main_heap_id, reg_heap_id, total_size );
		GF_ASSERT( ret == TRUE && "LRes_Init()領域確保失敗" );
	}
	
	size = total_size - size;
	lres = sys_AllocMemory( reg_heap_id, size );
	GF_ASSERT( lres != NULL && "LRes_Init()領域確保失敗" );
	memset( lres, 0, size );
	
	lres->main_heap_id = main_heap_id;
	lres->reg_heap_id = reg_heap_id;
	lres->resid_max = resid_max;
	lres->total_size = total_size;
	lres->resid_total_size = resid_size;
	lres->resid_ptr = (void*)((u32)lres + LRES_SIZE);
	
	return( lres );
}

//--------------------------------------------------------------
/**
 * LRES削除
 * @param	lres	LRES *
 * @retval	nothing
 */
//--------------------------------------------------------------
void LRes_Delete( LRES *lres )
{
	{
		u32 max = lres->resid_max;
		RESID *resid = lres->resid_ptr;
	
		while( max ){
			if( resid->alloc_ptr != NULL ){
				LRes_FreeID( lres, resid->alloc_id );
			}
			
			max--; resid++;
		}
	}
	
	{
		u32 reg_heap_id = lres->reg_heap_id;
		sys_FreeMemoryEz( lres );
		sys_DeleteHeap( reg_heap_id );
	}
}

//--------------------------------------------------------------
/**
 * LRES 領域確保
 * @param	lres	LRES *
 * @param	size	確保するサイズ
 * @param	type	ALLOCTYPE
 * @retval	void*	確保した領域 NULL=確保出来ない。 確保出来ない場合、ASSERT
 */
//--------------------------------------------------------------
void * LRes_Alloc( LRES *lres, u32 size, ALLOCTYPE type )
{
	void *alloc = lRes_AllocHeap( lres, size, type );
	return( alloc );
}

//--------------------------------------------------------------
/**
 * LRES 領域確保　ID登録アリ
 * @param	lres	LRES *
 * @param	id		登録するID
 * @param	size	確保するサイズ
 * @param	type	ALLOCTYPE
 * @retval	void*	確保した領域 NULL=確保出来ない。 確保出来ない場合、ASSERT
 */
//--------------------------------------------------------------
void * LRes_AllocID( LRES *lres, u32 id, u32 size, ALLOCTYPE type )
{
	RESID *resid = lRes_IDSpaceSearch( lres );
	GF_ASSERT( resid != NULL && "LRes_AllocID()登録数最大\n" );
	
	{
		void *alloc = lRes_AllocHeap( lres, size, type );
		lRes_ResIDInit( resid, id, alloc );
		return( alloc );
	}
}

//--------------------------------------------------------------
/**
 * LRES 領域開放。allocがID登録されていた場合、そのIDも削除する
 * @param	lres		LRES
 * @param	alloc		LRes_Allocで確保した領域
 * @retval	nothing
 */
//--------------------------------------------------------------
void LRes_Free( LRES *lres, void *alloc )
{
	RESID *resid = lRes_IDAllocSearch( lres, alloc );
	if( resid != NULL ){ lRes_ResIDDelete( resid ); }
	lRes_FreeHeap( alloc );
}

//--------------------------------------------------------------
/**
 * LRES 領域開放 ID版
 * @param	lres		LRES
 * @param	id			LRes_AllocIDで指定したID
 * @retval	nothing
 */
//--------------------------------------------------------------
void LRes_FreeID( LRES *lres, u32 id )
{
	RESID *resid = lRes_IDSearch( lres, id );
	GF_ASSERT( resid != NULL && "LRes_FreeID()id登録無し\n" );
	lRes_FreeHeap( resid->alloc_ptr );
	lRes_ResIDDelete( resid );
}

//--------------------------------------------------------------
/**
 * LRES ID指定領域取得。
 * @param	lres		LRES *
 * @param	id			LRes_AllocIDで指定したID
 * @retval	void*		LRes_AllocID(id)で取得した領域
 */
//--------------------------------------------------------------
void * LRes_IDResGet( LRES *lres, u32 id )
{
	RESID *resid = lRes_IDSearch( lres, id );
	GF_ASSERT( resid != NULL && "LRes_IDResGet()id登録無し\n" );
	return( resid->alloc_ptr );
}

//--------------------------------------------------------------
/**
 * LRES ID登録済みチェック
 * @param	lres		LRES
 * @param	id			LRes_AllocIDで指定したID
 * @retval	int			TRUE=登録済み　FALSE=登録していない
 */
//--------------------------------------------------------------
int LRes_IDResCheck( LRES *lres, u32 id )
{
	RESID *resid = lRes_IDSearch( lres, id );
	if( resid != NULL ){ return( TRUE ); }
	return( FALSE );
}

//==============================================================================
//	LRES ツール
//==============================================================================
//--------------------------------------------------------------
/**
 * LRES_Alloc()+ArchiveDataLoadByHandle()。
 * LRES_Alloc()で確保した領域へアーカイブデータ転送。
 * datIdのサイズ分、確保する。
 * @param	lres		LRES *
 * @param	handle		ARCHANDLE*
 * @param	datId		データインデックスID
 * @param	type		ALLOCTYPE
 * @retval	void*		確保、データ転送済みの領域
 */
//--------------------------------------------------------------
void * LResUtil_AllocArcLoad( LRES *lres, ARCHANDLE *handle, u32 datId, ALLOCTYPE type )
{
	u32 size = ArchiveDataSizeGetByHandle( handle, datId );
	void *alloc = LRes_Alloc( lres, size, type );
	ArchiveDataLoadByHandle( handle, datId, alloc );
	return( alloc );
}

//--------------------------------------------------------------
/**
 * LRES_AllocID()+ArchiveDataLoadByHandle()。
 * LRES_AllocID()で確保した領域へアーカイブデータ転送。
 * datIdのサイズ分、確保する。
 * @param	lres		LRES *
 * @param	id			登録ID
 * @param	handle		ARCHANDLE*
 * @param	datId		データインデックスID
 * @param	type		ALLOCTYPE
 * @retval	void*		確保、データ転送済みの領域
 */
//--------------------------------------------------------------
void * LResUtil_AllocIDArcLoad(
		LRES *lres, u32 id, ARCHANDLE *handle, u32 datId, ALLOCTYPE type )
{
	u32 size = ArchiveDataSizeGetByHandle( handle, datId );
	void *alloc = LRes_AllocID( lres, id, size, type );
	ArchiveDataLoadByHandle( handle, datId, alloc );
	return( alloc );
}

//==============================================================================
//	パーツ
//==============================================================================
//--------------------------------------------------------------
/**
 * 領域確保
 * @param	lress		LRES *
 * @param	size		確保するサイズ
 * @param	type		ALLOCTYPE
 * @retval	void*		確保した領域
 */
//--------------------------------------------------------------
static void * lRes_AllocHeap( LRES *lres, u32 size, ALLOCTYPE type )
{
	void *alloc;
	
	if( type == ALLOC_FR ){ alloc = sys_AllocMemory( lres->reg_heap_id, size ); }
	else{ alloc = sys_AllocMemoryLo( lres->reg_heap_id, size ); }
	
	GF_ASSERT( alloc != NULL && "lRes_AllocHeap()確保失敗\n" );
	return( alloc );
}

//--------------------------------------------------------------
/**
 * 領域開放
 * @param	lress		LRES *
 * @param	alloc		lRes_AllocHeap()で確保した領域
 * @retval	nothing
 */
//--------------------------------------------------------------
static void lRes_FreeHeap( void *alloc )
{
	sys_FreeMemoryEz( alloc );
}

//--------------------------------------------------------------
/**
 * ID検索
 * @param	lres		LRES *
 * @param	id			検索ID
 * @retval	RESID*		一致するRESID *　一致しない=NULL
 */
//--------------------------------------------------------------
static RESID * lRes_IDSearch( LRES *lres, u32 id )
{
	u32 max = lres->resid_max;
	RESID *resid = lres->resid_ptr;
	
	while( max ){
		if( resid->alloc_ptr != NULL && resid->alloc_id == id ){
			return( resid );
		}
		
		resid++; max--;
	};
	
	return( NULL );
}

//--------------------------------------------------------------
/**
 * RESID空き探し
 * @param	lres		LRES *
 * @retval	RESID*		空RESID　空き無し=NULL
 */
//--------------------------------------------------------------
static RESID * lRes_IDSpaceSearch( LRES *lres )
{
	u32 max = lres->resid_max;
	RESID *resid = lres->resid_ptr;
	
	while( max ){
		if( resid->alloc_ptr == NULL ){
			return( resid );
		}
		
		resid++; max--;
	}
	
	return( NULL );
}

//--------------------------------------------------------------
/**
 * RESID　指定された領域が登録されているか
 * @param	lres		LRES *
 * @param	alloc		確保した領域
 * @retval	RESID*		該当するRESID　該当無し=NULL
 */
//--------------------------------------------------------------
static RESID * lRes_IDAllocSearch( LRES *lres, void *alloc )
{
	u32 max = lres->resid_max;
	RESID *resid = lres->resid_ptr;
	
	while( max ){
		if( resid->alloc_ptr == alloc ){
			return( resid );
		}
		
		resid++; max--;
	}
	
	return( NULL );
}

//--------------------------------------------------------------
/**
 * RESID初期化
 * @param	resid		初期化するRESID *
 * @param	id			登録するID
 * @param	alloc		確保している領域
 * @retval	nothing
 */
//--------------------------------------------------------------
static void lRes_ResIDInit( RESID *resid, u32 id, void *alloc )
{
	resid->alloc_ptr = alloc;
	resid->alloc_id = id;
}

//--------------------------------------------------------------
/**
 * RESID削除
 * @param	resid		削除するRESID *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void lRes_ResIDDelete( RESID *resid )
{
	resid->alloc_ptr = NULL;
	resid->alloc_id = 0;
}

//==============================================================================
//	デバッグ
//==============================================================================
//----
#ifdef PM_DEBUG
//----
//----
#endif //PM_DEBUG
//----
