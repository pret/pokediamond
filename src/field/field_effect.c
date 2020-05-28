//******************************************************************************
/**
 * 
 * @file	field_effect.c
 * @brief	フィールドエフェクト
 * @author	kagaya
 * @data	05.07.13
 *
 */
//******************************************************************************
#include "common.h"
#include "fieldsys.h"
#include "field_effect.h"

//==============================================================================
//	define
//==============================================================================
//debug
#ifdef PM_DEBUG
#define DEBUG_FE_EOA_USE_CHECK			//有効でEOA追加監視
#endif

///ビルボードテクスチャ転送TCBプライオリティ
#define TCBPRI_VINTR_BLACT_TEX_LOAD (0xff)
#define TCBPRI_VWAIT_BLACT_TEX_LOAD (0xff)

//システム全体の初期化破棄タスク
#define FLD_3DOBJ_TEXTRANS_TCB_PRI	( 1024 )

//==============================================================================
//	typedef struct
//==============================================================================
//--------------------------------------------------------------
///	構造体名定義
//--------------------------------------------------------------
///FE_SUBPROC_REGDATA
typedef struct _TAG_SUBPROC_REGDATA SUBPROC_REGDATA;
///FE_BLACT
typedef struct _TAG_FE_BLACT FE_BLACT;
///FE_BLACT_H_ID
typedef struct _TAG_FE_BLACT_H_ID FE_BLACT_H_ID;

//--------------------------------------------------------------
///	FE_SYS構造体
//--------------------------------------------------------------
typedef struct _TAG_FE_SYS
{
	u32 heap_id;								///<ヒープID
	u32 fe_heap_id;								///<フィールドエフェクト専用ヒープID
	u32 reg_max;								///<エフェクト登録最大数
	u32 eoa_max;								///<EOA最大数
	u32 blact_max;								///<ビルボードアクター最大数
	
	LRES *lres;									///<LRES *
	FIELDSYS_WORK *fsys;						///<FIELDSYS_WORK *
	SUBPROC_REGDATA *subproc_regdata;			///<FE_SUBPROC_REGDATA
	
	ARCHANDLE *arc_handle;						///<フィールドエフェクトアーカイブデータハンドル
	EOA_SYS_PTR eoa_sys;						///<EOA_SYS_PTR
	FE_BLACT *fe_blact;							///<FE_BLACT *
}FE_SYS;

#define FE_SYS_SIZE (sizeof(FE_SYS))			///<FE_SYSサイズ

//--------------------------------------------------------------
///	SUBPROC_REGDATA構造体
//--------------------------------------------------------------
typedef struct _TAG_SUBPROC_REGDATA
{
	u32 id;						///<サブプロセス登録ID FE_PROC_MAX=無し
	void *subproc_work;			///<サブプロセスで使用するワーク* NULL=無し
};

#define SUBPROC_REGDATA_SIZE (sizeof(SUBPROC_REGDATA))	///<SUBPROC_REGDATA SIZE

//--------------------------------------------------------------
///	FE_BLACT構造体
//--------------------------------------------------------------
typedef struct _TAG_FE_BLACT
{
	u32 gp_heap_id;								///<グラフィック用ヒープ領域を作成するヒープID
	u16 blact_max;										///<ビルボードアクター最大数
	u16 mdl_max;										///<モデリングデータ最大数
	u16 anm_max;										///<アニメデータ最大数
	u16 tex_max;										///<テクスチャデータ最大数
	BLACT_SET_PTR set_ptr;								///<BLACT_SET_PTR
	LRES *lres_mdl;										///<モデル用LRES *
	LRES *lres_anm;										///<アニメ用LRES *
	TEXRES_MANAGER_PTR resm_tex;						///<TEXRES_MANAGER_PTR
	FE_BLACT_H_ID *head_manage;							///<FE_BLACT_H_ID
	BLACT_HEADER *head_tbl;								///<BLACT_HEADER
};

#define FE_BLACT_SIZE (sizeof(FE_BLACT))				///<FE_BLACT SIZE

//--------------------------------------------------------------
///	FE_BLACT_HEADER_ID構造体
//--------------------------------------------------------------
typedef struct _TAG_FE_BLACT_H_ID
{
	u32 id;														///<登録ID
	BLACT_HEADER *head;											///<ヘッダー*
};

#define FE_BLACT_H_ID_SIZE (sizeof(FE_BLACT_H_ID))				///<FE_BLACT_H_ID SIZE

//--------------------------------------------------------------
///	FE_VINTR_TEX_WORK構造体
//--------------------------------------------------------------
typedef struct
{
	u32 trans_end;												///<VRAM転送終了フラグ
	u32 id;														///<登録するID
	TEXRES_MANAGER_PTR resm_tex;								///<転送するTEXRES_MANAGER_PTR
}FE_VINTR_TEX_WORK;

#define FE_VINTR_TEX_WORK_SIZE (sizeof(FE_VINTR_TEX_WORK))

//==============================================================================
//	プロトタイプ
//==============================================================================
static u32 fe_HeapIDGet( const FE_SYS *fes );

static void fe_ArcHandleOpen( FE_SYS *fes );
static void fe_ArcHandleClose( FE_SYS *fes );

static void fe_SubProcRegDataInitAll( FE_SYS *fes );
static void fe_SubProcRegDataIDSet( FE_SYS *fes, u32 id );
static void fe_SubProcRegDataDelete( FE_SYS *fes, SUBPROC_REGDATA *subproc );
static void fe_SubProcRegDataIDDelete( FE_SYS *fes, u32 id );
static void fe_SubProcRegDataDeleteAll( FE_SYS *fes );
static SUBPROC_REGDATA * fe_SubProcRegDataSpaceSearch( FE_SYS *fes );
static SUBPROC_REGDATA * fe_SubProcRegDataIDSearch( FE_SYS *fes, u32 id );
static void SubProcRegDataInit( SUBPROC_REGDATA *subproc );
static void SubProcRegDataSet( SUBPROC_REGDATA *subproc, u32 id, void *work );
static int SubProcRegDataSpaceCheck( const SUBPROC_REGDATA *subproc );
static const FE_SUBPROC_DATA * SubProcIDDataGet( u32 id );

static void fe_EoaInit( FE_SYS *fes );
static void fe_EoaDelete( FE_SYS *fes );
static void fe_EoaDraw( FE_SYS *fes );

static void fe_BlActInit(
		FE_SYS *fes, u32 gp_heap_id,  u32 act_max,
		u32 mdl_max, u32 anm_max, u32 tex_max,
		u32 mdl_size, u32 anm_size, u32 tex_size );
static void fe_BlActDelete( FE_SYS *fes );

static void fe_BlActHeaderManageInit( FE_SYS *fes, FE_BLACT *fba, u32 max );
static void fe_BlActHeaderManageDelete( FE_BLACT *fba );
static BLACT_HEADER * fe_BlActHeaderManageGet( FE_BLACT *fba, u32 id );
static void fe_BlActHeaderManageFree( FE_BLACT *fba, u32 id );
static BLACT_HEADER * fe_BlActHeaderManageAdd( FE_BLACT *fba, u32 id,
	void *mdl, TEXANM_DATATBL *anm, void *tex, TEXRES_OBJ_PTR tex_key,
	const BLACT_ANIME_TBL *anm_tbl );

static void fe_VIntrWaitTexLoadSet( FE_SYS *fes, u32 id, TEXRES_MANAGER_PTR resm_tex );
static void fe_VIntrTCB_TexLoad( TCB_PTR tcb, void *wk );
static void fe_VWaitTCB_TexLoad( TCB_PTR tcb, void *wk );

//debug
#ifdef DEBUG_FE_EOA_USE_CHECK
static void DEBUG_FeEoaUseCheck_Init( FE_SYS *fes );
static void DEBUG_FeEoaUseCheck_Add( EOA_PTR eoa, const EOA_H_NPP *head );
static void DEBUG_FeEoaUseCheck_Del( EOA_PTR eoa );
#endif

//==============================================================================
//	フィールドエフェクト　システム
//==============================================================================
//--------------------------------------------------------------
/**
 * フィールドエフェクト　システム初期化
 * @param	fsys		FIELDSYS_WORK *
 * @param	reg_max		登録するエフェクト最大数
 * @param	heap_id		ワークに使用するヒープID
 * @param	worksize	フィールドエフェクトで確保するワーク領域最大サイズ
 * @retval	FE_SYS_PTR	FE_SYS_PTR
 * 
 * worksizeは登録されるエフェクト、EOA、ビルボード等、
 * フィールドエフェクト全体で使用される量を考慮してください
 */
//--------------------------------------------------------------
FE_SYS * FE_Init( FIELDSYS_WORK *fsys, u32 reg_max, u32 heap_id, u32 worksize )
{
	LRES *lres;
	FE_SYS *fes;
	
	lres = LRes_Init( heap_id, HEAPID_FIELD_FE, worksize, 0 );
	
	fes = LRes_Alloc( lres, FE_SYS_SIZE, ALLOC_FR );
	memset( fes, 0, FE_SYS_SIZE );
	
	fes->heap_id = heap_id;
	fes->fe_heap_id = HEAPID_FIELD_FE;
	fes->reg_max = reg_max;
	fes->lres = lres;
	fes->fsys = fsys;
	
	fes->subproc_regdata = LRes_Alloc( lres, SUBPROC_REGDATA_SIZE * reg_max, ALLOC_FR );
	fe_SubProcRegDataInitAll( fes );
	fe_ArcHandleOpen( fes );
	
#ifdef DEBUG_FE_EOA_USE_CHECK
	DEBUG_FeEoaUseCheck_Init( fes );
#endif
	
	return( fes );
}

//--------------------------------------------------------------
/**
 * フィールドエフェクト パラメタ初期化 EOA
 * @param	fes			FE_SYS_PTR
 * @param	eoa_max		EOA最大数
 * @param	blact_max	ビルボードアクター最大数
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_ParamInit_EOA( FE_SYS *fes, u32 eoa_max )
{
	fes->eoa_max = eoa_max;
	fe_EoaInit( fes );
}

//--------------------------------------------------------------
/**
 * フィールドエフェクト パラメタ初期化 ビルボードアクター
 * @param	fes			FE_SYS_PTR
 * @param	gp_heap_id		グラフィック用領域を確保するヒープ領域を作成するヒープID
 * @param	act_max			ビルボードアクター最大数
 * @param	mdl_max			モデリングデータ最大数
 * @param	anm_max			アニメーションデータ最大数
 * @param	tex_max			テクスチャデータ最大数
 * @param	mdl_size		モデリングデータ用に確保する領域サイズ
 * @param	anm_size		アニメデータ用に確保する領域サイズ
 * @param	tex_size		テクスチャデータ用に確保する領域サイズ
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_ParamInit_BlAct(
		FE_SYS *fes, u32 gp_heap_id,  u32 act_max,
		u32 mdl_max, u32 anm_max, u32 tex_max,
		u32 mdl_size, u32 anm_size, u32 tex_size )
{
	fe_BlActInit( fes, gp_heap_id, act_max,
		mdl_max, anm_max, tex_max,
		mdl_size, anm_size, tex_size );
}

//--------------------------------------------------------------
/**
 * フィールドエフェクト　エフェクト登録
 * @param	fes		FE_SYS *
 * @param	id		登録するエフェクトID FE_FLD_SHADOW等
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_EffectRegist( FE_SYS *fes, u32 id )
{
	if( fe_SubProcRegDataIDSearch(fes,id) != NULL ){
		GF_ASSERT( 0 && "FE_EffectRegist()既にそのIDは登録済みです" );
		return;
	}
	
	fe_SubProcRegDataIDSet( fes, id );
}

//--------------------------------------------------------------
/**
 * フィールドエフェクト　エフェクト複数登録
 * @param	fes		FE_SYS *
 * @param	id_tbl	登録するエフェクトIDをまとめたu32型の配列。終端にFE_PROC_MAX
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_EffectRegistMore( FE_SYS *fes, const u32 *id_tbl )
{
	while( (*id_tbl) != FE_PROC_MAX ){
		FE_EffectRegist( fes, (*id_tbl) );
		id_tbl++;
	}
}

//--------------------------------------------------------------
/**
 * フィールドエフェクト　エフェクト登録チェック
 * @param	fes		FE_SYS *
 * @param	id		登録チェックするエフェクトID FE_FLD_SHADOW等
 * @retval	int		TRUE=登録済み FALSE=登録されていない
 */
//--------------------------------------------------------------
int FE_EffectRegistCheck( FE_SYS *fes, u32 id )
{
	if( fe_SubProcRegDataIDSearch(fes,id) == NULL ){
		return( FALSE );
	}
	
	return( TRUE );
}

//--------------------------------------------------------------
/**
 * フィールドエフェクト　エフェクト削除
 * @param	fes		FE_SYS *
 * @param	id		削除するエフェクトID FE_FLD_SHADOW等
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_EffectDelete( FE_SYS *fes, u32 id )
{
	fe_SubProcRegDataIDDelete( fes, id );
}

//--------------------------------------------------------------
/**
 * フィールドエフェクト　描画
 * @param	fes	FE_SYS *
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_Draw( FE_SYS *fes )
{
	fe_EoaDraw( fes );
}

//--------------------------------------------------------------
/**
 * フィールドエフェクトシステム削除
 * @param	fes			FE_SYS_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_Delete( FE_SYS *fes )
{
	LRES *lres = fes->lres;
	
	fe_EoaDelete( fes );
	fe_SubProcRegDataDeleteAll( fes );
	fe_BlActDelete( fes );
	fe_ArcHandleClose( fes );
	
	LRes_Free( lres, fes->subproc_regdata );
	LRes_Free( lres, fes );
	LRes_Delete( lres );
}

//==============================================================================
//	フィールドエフェクト　パーツ
//==============================================================================
//--------------------------------------------------------------
/**
 * フィールドエフェクト専用領域からメモリ確保
 * @param	fes		FE_SYS_PTR
 * @param	size	確保するサイズ
 * @param	type	ALLOCTYPE
 * @retval	void*	確保したサイズ　NULL=確保出来ない(ASSERT。
 */
//--------------------------------------------------------------
void * FE_AllocMemory( const FE_SYS *fes, u32 size, ALLOCTYPE type )
{
	void *alloc = LRes_Alloc( fes->lres, size, type );
	return( alloc );
}

//--------------------------------------------------------------
/**
 * フィールドエフェクト専用領域からメモリ確保。確保した領域は指定値でクリアされる。
 * @param	fes		FE_SYS_PTR
 * @param	size	確保するサイズ。
 * @param	type	ALLOCTYPE
 * @param	clear	埋め尽くす値
 * @retval	void*	確保したサイズ　NULL=確保出来ない(ASSERT。
 */
//--------------------------------------------------------------
void * FE_AllocClearMemory( const FE_SYS *fes, u32 size, ALLOCTYPE type, u32 clear )
{
	void *alloc = FE_AllocMemory( fes, size, type );
	memset( alloc, clear, size );
	return( alloc );
}

//--------------------------------------------------------------
/**
 * フィールドエフェクト専用領域から取得したメモリを開放
 * @param	alloc	FE_AllocMemory()で確保したメモリ
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_FreeMemory( void *alloc )
{
	sys_FreeMemoryEz( alloc );
}

//--------------------------------------------------------------
/**
 * フィールドエフェクト　エフェクトで使用しているワークを取得
 * @param	fes		FE_SYS *
 * @param	id		取得するエフェクトID FE_FLD_SHADOW等
 * @retval	void*	idで使用しているワーク　NULL=登録されていない NULL時、ASSERT()
 */
//--------------------------------------------------------------
void * FE_EffectWorkGet( FE_SYS *fes, u32 id )
{
	SUBPROC_REGDATA *subproc = fe_SubProcRegDataIDSearch( fes, id );
	
	if( subproc == NULL ){
		GF_ASSERT( 0 && "FE_EffectWorkGet()そのIDは登録されていません" );
		return( NULL );
	}
	
	return( subproc->subproc_work );
}

//--------------------------------------------------------------
/**
 * FIELDSYS_WORK取得
 * @param	fes				FE_SYS_PTR
 * @retval	FIELDSYS_WORK	FIELDSYS_WORK *
 */
//--------------------------------------------------------------
FIELDSYS_WORK * FE_FieldSysWorkGet( const FE_SYS *fes )
{
	return( fes->fsys );
}

//--------------------------------------------------------------
/**
 * FIELD_OBJ_PTRからFE_SYS *取得
 * @param	fldobj		FIELD_OBJ_PTR
 * @retval	FE_SYS*		FE_SYS *
 */
//--------------------------------------------------------------
FE_SYS * FE_FieldOBJ_FE_SYS_Get( CONST_FIELD_OBJ_PTR fldobj )
{
	FIELDSYS_WORK *fsys = FieldOBJ_FieldSysWorkGet( fldobj );
	return( (FE_SYS *)fsys->fes );
}

//==============================================================================
//	フィールドエフェクト　パーツ　ローカル
//==============================================================================
//--------------------------------------------------------------
/**
 * フィールドエフェクト専用ヒープID取得
 * @param	fes		FE_SYS_PTR
 * @retval	u32		ヒープID
 */
//--------------------------------------------------------------
static u32 fe_HeapIDGet( const FE_SYS *fes )
{
	return( fes->fe_heap_id );
}

//==============================================================================
//	フィールドエフェクト　アーカイブデータ
//==============================================================================
//--------------------------------------------------------------
/**
 * フィールドエフェクト用アーカイブデータオープン
 * @param	fes		FE_SYS *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void fe_ArcHandleOpen( FE_SYS *fes )
{
	fes->arc_handle = ArchiveDataHandleOpen( ARC_FLDEFF, fe_HeapIDGet(fes) );
}

//--------------------------------------------------------------
/**
 * フィールドエフェクト用アーカイブデータクローズ
 * @param	fes		FE_SYS *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void fe_ArcHandleClose( FE_SYS *fes )
{
	ArchiveDataHandleClose( fes->arc_handle );
}

//--------------------------------------------------------------
/**
 * フィールドエフェクト用アーカイブデータのサイズを取得
 * @param	fes		FE_SYS *
 * @param	datid	データインデックスID
 * @retval	u32		datidデータサイズ
 */
//--------------------------------------------------------------
u32 FE_ArcDataSizeGet( FE_SYS *fes, u32 datid )
{
	u32 size = ArchiveDataSizeGetByHandle( fes->arc_handle, datid );
	return( size );
}

//--------------------------------------------------------------
/**
 * フィールドエフェクト用アーカイブデータを取得
 * @param	fes		FE_SYS *
 * @param	datid	データインデックスID
 * @param	buf		datidロード先
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_ArcDataLoad( FE_SYS *fes, u32 datid, void *buf )
{
	ArchiveDataLoadByHandle( fes->arc_handle, datid, buf );
}

//--------------------------------------------------------------
/**
 * フィールドエフェクト用アーカイブデータを展開先の領域を確保し、取得。
 * 領域はフィールドエフェクト用ヒープ領域。開放はFE_FreeMemory()
 * @param	fes		FE_SYS *
 * @param	datid	データインデックスID
 * @retval	void*	アーカイブデータを読み込んだ領域 *
 */
//--------------------------------------------------------------
void * FE_ArcDataLoadAlloc( FE_SYS *fes, u32 datid, ALLOCTYPE type )
{
	void *alloc = LResUtil_AllocArcLoad( fes->lres, fes->arc_handle, datid, type );
	return( alloc );
}

//==============================================================================
//	SUBPROC_REGDATA関連
//==============================================================================
//--------------------------------------------------------------
/**
 * SUBPROC_REGDATA 全初期化
 * @param	fes		FE_SYS
 * @retval	nothing
 */
//--------------------------------------------------------------
static void fe_SubProcRegDataInitAll( FE_SYS *fes )
{
	u32 max = fes->reg_max;
	SUBPROC_REGDATA *subproc = fes->subproc_regdata;
	
	while( max ){
		SubProcRegDataInit( subproc );
		subproc++; max--;
	}
}

//--------------------------------------------------------------
/**
 * SUBPROC_REGDATA 指定IDの初期化関数呼び出し、登録
 * @param	fes		FE_SYS
 * @param	id		FE_FLD_SHADOW等
 * @retval	nothing
 */
//--------------------------------------------------------------
static void fe_SubProcRegDataIDSet( FE_SYS *fes, u32 id )
{
	const FE_SUBPROC_DATA *procdata = SubProcIDDataGet( id );
	void *work;
	SUBPROC_REGDATA *subproc;

	OS_Printf("FE_SYS *fes = %08x, procdata = %08x, proc_init = %08x\n", fes, procdata, procdata->proc_init);

	work = procdata->proc_init( fes );
	subproc = fe_SubProcRegDataSpaceSearch( fes );
	SubProcRegDataSet( subproc, id, work );
}

//--------------------------------------------------------------
/**
 * SUBPROC_REGDATA 指定SUBPROC_REGDATAの削除関数呼び出し、削除
 * @param	fes		FE_SYS
 * @param	subproc	SUBPROC_REGDATA *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void fe_SubProcRegDataDelete( FE_SYS *fes, SUBPROC_REGDATA *subproc )
{
	const FE_SUBPROC_DATA *procdata = SubProcIDDataGet( subproc->id );
	procdata->proc_del( subproc->subproc_work );
	SubProcRegDataInit( subproc );
}

//--------------------------------------------------------------
/**
 * SUBPROC_REGDATA 指定IDの削除関数呼び出し、削除
 * @param	fes		FE_SYS
 * @param	id		FE_FLD_SHADOW等
 * @retval	nothing
 */
//--------------------------------------------------------------
static void fe_SubProcRegDataIDDelete( FE_SYS *fes, u32 id )
{
	SUBPROC_REGDATA *subproc = fe_SubProcRegDataIDSearch( fes, id );
	GF_ASSERT( subproc != NULL && "fe_SubProcRegDataIDDelete()ID一致無し\n" );
	fe_SubProcRegDataDelete( fes, subproc );
}

//--------------------------------------------------------------
/**
 * SUBPROC_REGDATA 登録されているIDを全て削除
 * @param	fes		FE_SYS
 * @retval	nothing
 */
//--------------------------------------------------------------
static void fe_SubProcRegDataDeleteAll( FE_SYS *fes )
{
	u32 max = fes->reg_max;
	SUBPROC_REGDATA *subproc = fes->subproc_regdata;
	
	while( max ){
		if( SubProcRegDataSpaceCheck(subproc) == FALSE ){
			fe_SubProcRegDataDelete( fes, subproc );
		}
		
		subproc++; max--;
	}
}

//--------------------------------------------------------------
/**
 * SUBPROC_REGDATA 空き探し
 * @param	fes		FE_SYS
 * @retval	SUBPROC_REGDATA* 空いているSUBPROC_REGDATA*　NULL=空き無し
 */
//--------------------------------------------------------------
static SUBPROC_REGDATA * fe_SubProcRegDataSpaceSearch( FE_SYS *fes )
{
	u32 max = fes->reg_max;
	SUBPROC_REGDATA *subproc = fes->subproc_regdata;
	
	while( max ){
		if( SubProcRegDataSpaceCheck(subproc) == TRUE ){
			return( subproc );
		}
		
		subproc++; max--;
	}
	
	GF_ASSERT( 0 && "fe_SubProcRegDataSpaceSearch()空き無し" );
	return( NULL );
}

//--------------------------------------------------------------
/**
 * SUBPROC_REGDATA 一致ID探し
 * @param	fes		FE_SYS
 * @param	id		検索ID FE_FLD_SHADOW等
 * @retval	SUBPROC_REGDATA* 空いているSUBPROC_REGDATA*　NULL=空き無し
 */
//--------------------------------------------------------------
static SUBPROC_REGDATA * fe_SubProcRegDataIDSearch( FE_SYS *fes, u32 id )
{
	u32 max = fes->reg_max;
	SUBPROC_REGDATA *subproc = fes->subproc_regdata;
	
	while( max ){
		if( subproc->id  == id ){
			return( subproc );
		}
		
		subproc++; max--;
	}
	
	return( NULL );
}

//--------------------------------------------------------------
/**
 * SUBPROC_REGDATA 初期化
 * @param	subproc	SUBPROC_REGDATA
 * @retval	nothing
 */
//--------------------------------------------------------------
static void SubProcRegDataInit( SUBPROC_REGDATA *subproc )
{
	subproc->id = FE_PROC_MAX;
	subproc->subproc_work = NULL;
}

//--------------------------------------------------------------
/**
 * SUBPROC_REGDATA セット
 * @param	subproc	SUBPROC_REGDATA
 * @param	id		FE_FLD_SHADOW等
 * @param	work	指定id関数で使用するワーク
 * @retval	nothing
 */
//--------------------------------------------------------------
static void SubProcRegDataSet( SUBPROC_REGDATA *subproc, u32 id, void *work )
{
	subproc->id = id;
	subproc->subproc_work = work;
}

//--------------------------------------------------------------
/**
 * SUBPROC_REGDATA　空きチェック
 * @param	subproc	SUBPROC_REGDATA
 * @retval	int	TRUE=空き　FALSE=空いていない
 */
//--------------------------------------------------------------
static int SubProcRegDataSpaceCheck( const SUBPROC_REGDATA *subproc )
{
	if( subproc->id == FE_PROC_MAX ){
		return( TRUE );
	}
	
	return( FALSE );
}

//--------------------------------------------------------------
/**
 * エフェクトID -> FE_SUBPROC_DATA取得
 * @param	id		FE_FLD_SHADOW等
 * @retval	FE_SUBPROC_DATA FE_SUBPROC_DATA *
 */
//--------------------------------------------------------------
static const FE_SUBPROC_DATA * SubProcIDDataGet( u32 id )
{
	const FE_SUBPROC_DATA *tbl = DATA_FE_SubProcDataTbl;
	
	while( tbl->id != FE_PROC_MAX ){
		if( tbl->id == id ){
			return( tbl );
		}
		
		tbl++;
	}
	
	GF_ASSERT( 0 && "SubProcDataGet()登録されていないIDです" );
	return( NULL );
}

//==============================================================================
//	フィールドエフェクト　EOA
//==============================================================================
//--------------------------------------------------------------
/**
 * EOA初期化
 * @param	fes		FE_SYS
 * @retval	nothing
 */
//--------------------------------------------------------------
static void fe_EoaInit( FE_SYS *fes )
{
	fes->eoa_sys = EOA_SysInit( fes->fe_heap_id, fes->eoa_max );
}

//--------------------------------------------------------------
/**
 * EOA削除
 * @param	fes		FE_SYS
 * @retval	nothing
 */
//--------------------------------------------------------------
static void fe_EoaDelete( FE_SYS *fes )
{
	if( fes->eoa_sys != NULL ){
		EOA_SysDeleteAll( fes->eoa_sys );
		fes->eoa_sys = NULL;
	}
}

//--------------------------------------------------------------
/**
 * EOA描画
 * @param	fes	FE_SYS *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void fe_EoaDraw( FE_SYS *fes )
{
	if( fes->eoa_sys != NULL ){
		EOA_SysDraw( fes->eoa_sys );
	}
}

//==============================================================================
//	フィールドエフェクト　EOA　パーツ
//==============================================================================
//--------------------------------------------------------------
/**
 * EOA追加　実体はEOA_Add_NPP()
 * @param	fes		FE_SYS_PTR
 * @param	EOA_H_NPP	追加される情報が纏められたEOA_H_NPP
 * @param	mtx			初期位置
 * @param	prm			追加するEOAへ指定するパラメタ
 * @param	ptr			追加するEOAへ指定するポインタ
 * @param	pri			追加するEOAの動作プライオリティ
 * @retval	EOA_PTR		追加されたEOA_PTR 追加失敗時　強制終了
 */
//--------------------------------------------------------------
EOA_PTR FE_EoaAddNpp( const FE_SYS *fes, const EOA_H_NPP *head,
		const VecFx32 *mtx, int prm, const void *ptr, int pri )
{
	EOA_PTR eoa;
	EOA_SYS_PTR es;
	
	es = fes->eoa_sys;
	eoa = EOA_Add_NPP( es, head, mtx, prm, ptr, pri );
	
	GF_ASSERT( eoa != NULL && "FE_EoaAddNpp() EOAの追加に失敗…" );
	
#ifdef DEBUG_FE_EOA_USE_CHECK
	DEBUG_FeEoaUseCheck_Add( eoa, head );
#endif
	
	return( eoa );
}

//--------------------------------------------------------------
/**
 * EOA削除　実体はEOA_Delete()
 * ※フィールドエフェクトで使用しているEOA把握の為、削除の際、こちらを使う
 * @param	eoa		EOA_PTR
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_EoaDelete( EOA_PTR eoa )
{
#ifdef DEBUG_FE_EOA_USE_CHECK
	DEBUG_FeEoaUseCheck_Del( eoa );
#endif
	
	EOA_Delete( eoa );
}

//==============================================================================
//	フィールドエフェクト　ビルボードアクター
//==============================================================================
//--------------------------------------------------------------
/**
 * ビルボードアクター初期化　メイン
 * @param	fes				FE_SYS *
 * @param	gp_heap_id		グラフィック用領域を確保するヒープ領域を作成するヒープID
 * @param	act_max			ビルボードアクター最大数
 * @param	mdl_max			モデリングデータ最大数
 * @param	anm_max			アニメーションデータ最大数
 * @param	tex_max			テクスチャデータ最大数
 * @param	mdl_size		モデリングデータ用に確保する領域サイズ
 * @param	anm_size		アニメデータ用に確保する領域サイズ
 * @param	tex_size		テクスチャデータ用に確保する領域サイズ
 * @retval	nothing
 */
//--------------------------------------------------------------
static void fe_BlActInit(
		FE_SYS *fes, u32 gp_heap_id,  u32 act_max,
		u32 mdl_max, u32 anm_max, u32 tex_max,
		u32 mdl_size, u32 anm_size, u32 tex_size )
{
	FE_BLACT *fba;
	BLACT_SETDATA set;
	
	fba = FE_AllocClearMemory( fes, FE_BLACT_SIZE, ALLOC_FR, 0 );
	fes->fe_blact = fba;
	
	fba->gp_heap_id = gp_heap_id;
	fba->blact_max = act_max;
	fba->mdl_max = mdl_max;
	fba->anm_max = anm_max;
	fba->tex_max = tex_max;
	
	fba->lres_mdl = LRes_Init(
		gp_heap_id, HEAPID_FIELD_FE_BLACT_MDL, mdl_size, mdl_max );
	fba->lres_anm = LRes_Init(
		gp_heap_id, HEAPID_FIELD_FE_BLACT_ANM, anm_size, anm_max );
	
	fba->resm_tex = TEXRESM_Init( tex_max, gp_heap_id );		//どうしようか
	
	fe_BlActHeaderManageInit( fes, fba, act_max );
	
	set.WorkNum = act_max;
	set.heap = fe_HeapIDGet( fes );
	fba->set_ptr = BLACT_InitSet( &set );
}

//--------------------------------------------------------------
/**
 * ビルボードアクター削除
 * @param	fes				FE_SYS *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void fe_BlActDelete( FE_SYS *fes )
{
	FE_BLACT *fba = fes->fe_blact;
	
	if( fba != NULL ){
		BLACT_DestSet( fba->set_ptr );
		fe_BlActHeaderManageDelete( fba );
		
		LRes_Delete( fba->lres_mdl );
		LRes_Delete( fba->lres_anm );
		TEXRESM_Delete( fba->resm_tex );
	
		FE_FreeMemory( fba );
		fes->fe_blact = NULL;
	}
}

//==============================================================================
//	フィールドエフェクト用ビルボードアクター　パーツ
//==============================================================================
//--------------------------------------------------------------
/**
 * ビルボードアクター追加　実体はBLACT_Add()
 * @param	fes			FE_SYS
 * @param	head		BLACT_HEADER *
 * @param	vec			座標
 * @retval	BLACT_WORK	BLACT_WORK_PTR 失敗=強制終了
 */
//--------------------------------------------------------------
BLACT_WORK_PTR FE_BlActAdd( FE_SYS *fes, 
		const BLACT_HEADER *head, const VecFx32 *vec )
{
	BLACT_ADD add;
	BLACT_WORK_PTR act;
	BLACT_SET_PTR set;
	VecFx32 scale = { FX32_ONE,FX32_ONE,FX32_ONE };
	
	set = fes->fe_blact->set_ptr;
	
	add.blact_s = set;
	add.pHeader = head;
	add.matrix	= *vec;
	add.scale	= scale;
	
	act = BLACT_Add( &add );
	GF_ASSERT( act != NULL && "FE_BlActAdd()アクター追加失敗 アクター弾数不足か?" );
	
	if( act != NULL ){
		NNS_G3dMdlSetMdlFogEnableFlagAll( BLACT_MdlResGet(act), TRUE );
		SetGlbLightMdl( BLACT_MdlResGet(act) );
	}
	
	return( act );
}

//--------------------------------------------------------------
/**
 * ビルボードアクター追加　実体はBLACT_Add()。
 * ヘッダー指定はFE_BlActHeaderManageAdd()で指定したID。
 * @param	fes			FE_SYS
 * @param	id			ヘッダー登録ID
 * @param	vec			座標
 * @retval	BLACT_WORK	BLACT_WORK_PTR 失敗=強制終了
 */
//--------------------------------------------------------------
BLACT_WORK_PTR FE_BlActAddID( FE_SYS *fes, u32 id, const VecFx32 *vec )
{
	BLACT_HEADER *head;
	head = fe_BlActHeaderManageGet( fes->fe_blact, id );
	return( FE_BlActAdd(fes,head,vec) );
}

//--------------------------------------------------------------
/**
 * ビルボードアクターヘッダー登録
 * @param	fes			FE_SYS *
 * @param	id			登録ID
 * @param	mdl				モデルリソースへの*
 * @param	anm				アニメリソースへの*
 * @param	tex				テクスチャリソースへの*
 * @param	tex_key			常駐型の場合はキー取得用TEXRES_OBJ_PTRを指定。NULL=転送型でセット
 * @param	anm_tbl			ビルボードアニメ const BLACT_ANIME_TBL *
 * @retval	BLACT_HEADER 登録されたBLACT_HEADER * 追加済みの場合はその領域を返す 追加失敗=ASSERT
 */
//--------------------------------------------------------------
BLACT_HEADER * FE_BlActHeaderManageAdd( FE_SYS *fes, u32 id,
	void *mdl, TEXANM_DATATBL *anm, void *tex, TEXRES_OBJ_PTR tex_key,
	const BLACT_ANIME_TBL *anm_tbl )
{
	BLACT_HEADER *head;
	head = fe_BlActHeaderManageAdd( fes->fe_blact, id, mdl, anm, tex, tex_key, anm_tbl );
	return( head );
}

//--------------------------------------------------------------
/**
 * ビルボードアクターヘッダー登録 リソースマネージャー利用
 * @param	fes			FE_SYS *
 * @param	id			登録ID
 * @param	mdl_id		FE_BlActResAdd_Mdl()で登録したID
 * @param	anm_id		FE_BlActResAdd_Anm()で登録したID
 * @param	tex_id		FE_BlActResAdd_Tex()で登録したID
 * @param	tex_flag	FE_BLACT_TEX_VRAM等
 * @param	anm_tbl		ビルボードアニメ const BLACT_ANIME_TBL *
 * @retval	BLACT_HEADER 登録されたBLACT_HEADER * 追加済みの場合はその領域を返す 追加失敗=ASSERT
 */
//--------------------------------------------------------------
BLACT_HEADER * FE_BlActHeaderManageAddResmID(
		FE_SYS *fes, u32 id, u32 mdl_id, u32 anm_id, u32 tex_id, int tex_flag,
		const BLACT_ANIME_TBL *anm_tbl )
{
	void *mdl,*tex,*anm;
	TEXANM_DATATBL anmdata;
	TEXRES_OBJ_PTR tex_obj;
	BLACT_HEADER *head;
	FE_BLACT *fba;
	
	fba = fes->fe_blact;
	
	mdl = LRes_IDResGet( fba->lres_mdl, mdl_id );
	anm = LRes_IDResGet( fba->lres_anm, anm_id );
	TEXANM_UnPackLoadFile( anm, &anmdata );
	
	tex_obj = TEXRESM_GetResObj( fba->resm_tex, tex_id );
	GF_ASSERT( tex_obj != NULL && "FE_BlActHeaderManageAddResmID()テクスチャ未登録ID指定" );
	tex = TEXRESM_GetResPTR( tex_obj );
	
	if( tex_flag == FE_BLACT_TEX_TRANS ){
		tex_obj = NULL;
	}
	
	head = fe_BlActHeaderManageAdd( fba, id, mdl, &anmdata, tex, tex_obj, anm_tbl );
	GF_ASSERT( head != NULL && "FE_BlActHeaderManageAdd()登録数オーバーによる追加失敗" );
	
	return( head );
}

//==============================================================================
//	フィールドエフェクト用ビルボードアクター　ヘッダーマネージャ
//==============================================================================
//--------------------------------------------------------------
/**
 * ヘッダー領域確保　領域はFE_AllocMemory()で確保
 * @param	fes		FE_SYS
 * @param	fba		FE_BLACT
 * @param	max		ヘッダー最大数
 * @retval	nothing
 */
//--------------------------------------------------------------
static void fe_BlActHeaderManageInit( FE_SYS *fes, FE_BLACT *fba, u32 max )
{
	BLACT_HEADER *head;
	FE_BLACT_H_ID *hm;
	
	head = FE_AllocMemory( fes, sizeof(BLACT_HEADER)*max, ALLOC_FR );
	fba->head_tbl = head;
	
	hm = FE_AllocMemory( fes, FE_BLACT_H_ID_SIZE*max, ALLOC_FR );
	fba->head_manage = hm;
	
	do{
		hm->id = FE_BLACT_H_ID_NOT;
		hm->head = head;
		hm++;
		head++;
		max--;
	}while( max );
}

//--------------------------------------------------------------
/**
 * ヘッダー領域削除
 * @param	fba		FE_BLACT
 * @retval	nothing
 */
//--------------------------------------------------------------
static void fe_BlActHeaderManageDelete( FE_BLACT *fba )
{
	FE_FreeMemory( fba->head_manage );
	FE_FreeMemory( fba->head_tbl );
}

//--------------------------------------------------------------
/**
 * ビルボードアクターヘッダー管理領域開放
 * @param	fba			FE_BLACT *
 * @param	id			開放するID
 * @retval	nothing
 */
//--------------------------------------------------------------
static void fe_BlActHeaderManageFree( FE_BLACT *fba, u32 id )
{
	u32 max = fba->blact_max;
	FE_BLACT_H_ID *ma = fba->head_manage;
	
	do{
		if( ma->id == id ){ ma->id = FE_BLACT_H_ID_NOT; return; }
		ma++; max--;
	}while( max );	
	
	GF_ASSERT( 0 && "fe_BlActHeaderManageFree()登録されていないヘッダーIDです" );
}

//--------------------------------------------------------------
/**
 * ビルボードアクターヘッダー管理領域へヘッダー追加
 * @param	fba				FE_BLACT *
 * @param	id				登録するID
 * @param	mdl				モデルリソースへの*
 * @param	anm				アニメリソースへの*
 * @param	tex				テクスチャリソースへの*
 * @param	tex_key			常駐型の場合はキー取得用TEXRES_OBJ_PTRを指定。NULL=転送型でセット
 * @param	anm_tbl			ビルボードアニメ BLACT_ANIME_TBL *
 * @retval	BLACT_HEADER	ヘッダー領域への*。NULL=失敗
 */
//--------------------------------------------------------------
static BLACT_HEADER * fe_BlActHeaderManageAdd( FE_BLACT *fba, u32 id,
	void *mdl, TEXANM_DATATBL *anm, void *tex, TEXRES_OBJ_PTR tex_key,
	const BLACT_ANIME_TBL *anm_tbl )
{
	BLACT_HEADER *head;
	
	head = NULL;
	
	{
		u32 max = fba->blact_max;
		FE_BLACT_H_ID *ma = fba->head_manage;
		
		do{ if(ma->id==id){ return(ma->head); }					//登録済み
			ma++; max--;
		}while( max );
		
		ma = fba->head_manage;
		max = fba->blact_max;
		
		do{ if(ma->id==FE_BLACT_H_ID_NOT){ ma->id=id; head=ma->head; break; }
			ma++; max--;
		}while( max );
	}
	
	GF_ASSERT( head != NULL && "fe_BlActHeaderManageAdd() ビルボードヘッダー満杯"  );
	
	memset( head, 0, sizeof(BLACT_HEADER) );
	
	head->ImdRes = mdl;
	head->texanm = *anm;
	head->ItxRes = tex;
	
	if( tex_key != NULL ){
		head->texKey = TEXRESM_GetTexKeyPTR( tex_key );
		head->tex4x4Key = TEXRESM_GetTex4x4KeyPTR( tex_key );
		head->plttKey = TEXRESM_GetPlttKeyPTR( tex_key );
	}
	
	head->anm = anm_tbl;
	return( head );
}

//--------------------------------------------------------------
/**
 * ビルボードアクターヘッダー管理領域　ヘッダー取得
 * @param	fba				FE_BLACT *
 * @param	id				取得するするID
 * @retval	BLACT_HEADER	ヘッダー領域への*。NULL=失敗
 */
//--------------------------------------------------------------
static BLACT_HEADER * fe_BlActHeaderManageGet( FE_BLACT *fba, u32 id )
{
	u32 max = fba->blact_max;
	FE_BLACT_H_ID *ma = fba->head_manage;
		
	do{ if(ma->id==id){ return(ma->head); }
		ma++; max--;
	}while( max );
	
	GF_ASSERT( 0 && "fe_BlActHeaderManageGet()ID登録無し"  );
	return( NULL );
}

//--------------------------------------------------------------
/**
 * ビルボードアクターヘッダー管理領域ヘッダー取得
 * @param	fes				FE_SYS *
 * @param	id				取得するID
 * @retal	BLACT_HEADER	ヘッダー領域への*。NULL=登録されていない
 */
//--------------------------------------------------------------
BLACT_HEADER * FE_BlActHeaderManageGet( FE_SYS *fes, u32 id )
{
	FE_BLACT *fba = fes->fe_blact;
	return( fe_BlActHeaderManageGet(fba,id) );
}

//--------------------------------------------------------------
/**
 * ビルボードアクターヘッダー管理領域開放
 * @param	fes			FE_SYS *
 * @param	id			開放するID
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_BlActHeaderManageFree( FE_SYS *fes, u32 id )
{
	FE_BLACT *fba = fes->fe_blact;
	fe_BlActHeaderManageFree( fba, id );
}

//==============================================================================
//	フィールドエフェクト　ビルボードリソース　パーツ
//==============================================================================
//--------------------------------------------------------------
/**
 * リソース配置　モデリングデータ
 * @param	fes		FE_SYS *
 * @param	id		登録するID
 * @param	data	配置するデータ
 * @param	size	dataサイズ
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_BlActResAdd_Mdl( FE_SYS *fes, u32 id, const void *data, u32 size )
{
	FE_BLACT *fba = fes->fe_blact;
	void *alloc = LRes_AllocID( fba->lres_mdl, id, size, ALLOC_FR );
	MI_CpuCopy8( data, alloc, size );
}

//--------------------------------------------------------------
/**
 * リソース配置　モデリングデータ　アーカイブ
 * @param	fes		FE_SYS *
 * @param	id		登録するID
 * @param	datid	登録するアーカイブデータインデックスID
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_BlActResAdd_MdlArc( FE_SYS *fes, u32 id, u32 datid ) 
{
	FE_BLACT *fba = fes->fe_blact;
	LResUtil_AllocIDArcLoad( fba->lres_mdl, id, fes->arc_handle, datid, ALLOC_FR );
}

//--------------------------------------------------------------
/**
 * リソース取得　モデルデータ
 * @param	fes		FE_SYS *
 * @param	id		取得するID
 * @retval	void*	idリソース
 */
//--------------------------------------------------------------
void * FE_BlActResGet_Mdl( FE_SYS *fes, u32 id )
{
	FE_BLACT *fba = fes->fe_blact;
	void *mdl = LRes_IDResGet( fba->lres_mdl, id );
	return( mdl );
}

//--------------------------------------------------------------
/**
 * リソース削除　モデリングデータ
 * @param	fes		FE_SYS *
 * @param	id		削除するID
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_BlActResDelete_Mdl( FE_SYS *fes, u32 id )
{
	FE_BLACT *fba = fes->fe_blact;
	LRes_FreeID( fba->lres_mdl, id );
}

//--------------------------------------------------------------
/**
 * リソース配置　アニメデータ
 * @param	fes		FE_SYS *
 * @param	id		登録するID
 * @param	data	配置するデータ
 * @param	size	dataサイズ
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_BlActResAdd_Anm( FE_SYS *fes, u32 id, const void *data, u32 size )
{
	FE_BLACT *fba = fes->fe_blact;
	void *alloc = LRes_AllocID( fba->lres_anm, id, size, ALLOC_FR );
	MI_CpuCopy8( data, alloc, size );
}

//--------------------------------------------------------------
/**
 * リソース配置　アニメーションデータ　アーカイブ
 * @param	fes		FE_SYS *
 * @param	id		登録するID
 * @param	datid	登録するアーカイブデータインデックスID
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_BlActResAdd_AnmArc( FE_SYS *fes, u32 id, u32 datid ) 
{
	FE_BLACT *fba = fes->fe_blact;
	LResUtil_AllocIDArcLoad( fba->lres_anm, id, fes->arc_handle, datid, ALLOC_FR );
}

//--------------------------------------------------------------
/**
 * リソース取得　アニメデータ
 * @param	fes		FE_SYS *
 * @param	id		取得するID
 * @retval	void*	idリソース
 */
//--------------------------------------------------------------
void * FE_BlActResGet_Anm( FE_SYS *fes, u32 id )
{
	FE_BLACT *fba = fes->fe_blact;
	void *anm = LRes_IDResGet( fba->lres_anm, id );
	return( anm );
}

//--------------------------------------------------------------
/**
 * リソース削除　アニメデータ
 * @param	fes		FE_SYS *
 * @param	id		削除するID
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_BlActResDelete_Anm( FE_SYS *fes, u32 id )
{
	FE_BLACT *fba = fes->fe_blact;
	LRes_FreeID( fba->lres_anm, id );
}

//--------------------------------------------------------------
/**
 * リソース配置　テクスチャデータ
 * @param	fes		FE_SYS *
 * @param	id		登録するID
 * @param	data	配置するデータ
 * @param	size	dataサイズ
 * @param	texcut	TEXRESM_TEX_CUT_FALSE等
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_BlActResAdd_Tex( FE_SYS *fes, u32 id, void *data, u32 texcut )
{
	FE_BLACT *fba = fes->fe_blact;
	TEXRES_OBJ_PTR obj = TEXRESM_AddAndAllocVramKeyResNormal( fba->resm_tex, data, id, texcut, fe_HeapIDGet(fes) );
	GF_ASSERT( obj != NULL && "FE_BlActResAdd_Tex()追加失敗" );
	fe_VIntrWaitTexLoadSet( fes, id, fba->resm_tex );
}

//--------------------------------------------------------------
/**
 * リソース配置　テクスチャデータ、アーカイブ。
 * @param	fes		FE_SYS *
 * @aram	id		登録するID
 * @param	dataid	アーカイブデータインデックスID
 * @param	texcut	TEXRESM_TEX_CUT_FALSE等
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_BlActResAdd_TexArc( FE_SYS *fes, u32 id, u32 datid, u32 texcut )
{
	FE_BLACT *fba = fes->fe_blact;
	void *buf = FE_ArcDataLoadAlloc( fes, datid, ALLOC_LO );
	TEXRES_OBJ_PTR obj = TEXRESM_AddAndAllocVramKeyResNormal( fba->resm_tex, buf, id, texcut, fe_HeapIDGet(fes) );
	GF_ASSERT( obj != NULL && "FE_BlActResAdd_Tex()追加失敗" );
	fe_VIntrWaitTexLoadSet( fes, id, fba->resm_tex );
}

//--------------------------------------------------------------
/**
 * リソース取得　テクスチャデータ
 * @param	fes		FE_SYS *
 * @param	id		取得するID
 * @retval	void*	idリソース
 */
//--------------------------------------------------------------
void * FE_BlActResGet_Tex( FE_SYS *fes, u32 id )
{
	FE_BLACT *fba = fes->fe_blact;
	TEXRES_OBJ_PTR tex_obj = TEXRESM_GetResObj( fba->resm_tex, id );
	void *tex = TEXRESM_GetResPTR( tex_obj );
	return( tex );
}

//--------------------------------------------------------------
/**
 * リソース削除　テクスチャデータ
 * @param	fes		FE_SYS *
 * @param	id		登録するID
 * @param	data	配置するデータ
 * @param	size	dataサイズ
 * @retval	nothing
 */
//--------------------------------------------------------------
void FE_BlActResDelete_Tex( FE_SYS *fes, u32 id )
{
	FE_BLACT *fba = fes->fe_blact;
	TEXRESM_DeleteResID( fba->resm_tex, id );
}

//--------------------------------------------------------------
/**
 * テクスチャデータVブランク転送作成
 * @param	tcb		TCB_PTR
 * @param	wk		tcb work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void fe_VIntrWaitTexLoadSet( FE_SYS *fes, u32 id, TEXRES_MANAGER_PTR resm_tex )
{
	FE_VINTR_TEX_WORK *work = FE_AllocMemory( fes, FE_VINTR_TEX_WORK_SIZE, ALLOC_LO );
	work->trans_end = TRUE;
	work->id = id;
	work->resm_tex = resm_tex;
	VIntrTCB_Add( fe_VIntrTCB_TexLoad, work, TCBPRI_VINTR_BLACT_TEX_LOAD );
	VWaitTCB_Add( fe_VWaitTCB_TexLoad, work, TCBPRI_VWAIT_BLACT_TEX_LOAD );
}

//--------------------------------------------------------------
/**
 * テクスチャデータVブランク転送 tcb
 * @param	tcb		TCB_PTR
 * @param	wk		tcb work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void fe_VIntrTCB_TexLoad( TCB_PTR tcb, void *wk )
{
	FE_VINTR_TEX_WORK *work = wk;
	TEXRESM_TexLoadID( work->resm_tex, work->id );
	work->trans_end = TRUE;
	TCB_Delete( tcb );
}

//--------------------------------------------------------------
/**
 * テクスチャデータVブランク後の開放 tcb
 * @param	tcb		TCB_PTR
 * @param	wk		tcb work *
 * @retval	nothing
 */
//--------------------------------------------------------------
static void fe_VWaitTCB_TexLoad( TCB_PTR tcb, void *wk )
{
	FE_VINTR_TEX_WORK *work = wk;
	
	if( work->trans_end == TRUE ){
		TEXRESM_CutTexID( work->resm_tex, work->id );
		FE_FreeMemory( work );
		TCB_Delete( tcb );
	}
}

//==============================================================================
//	3dmdl
//==============================================================================
//--------------------------------------------------------------
/**
 * simple_3DModelSet　フィールドエフェクト版
 * @param	
 * @retval
 */
//--------------------------------------------------------------
void FE_simple3DModelInitOnly( FE_SYS *fes,
	NNSG3dRenderObj *object_p, NNSG3dResMdl **model, NNSG3dResFileHeader **resFile )
{
    NNSG3dResTex *texture = NULL;
    BOOL status;
	
	texture = NNS_G3dGetTex( *resFile );						//テクスチャリソース取得
	
	if( texture != NULL ){
		if( TexKeyLive(texture) == FALSE ){		// テクスチャがVramに展開されていないかチェック
			DC_FlushRange( *resFile, (*resFile)->fileSize );
			
			// デフォルトの初期化関数をコールしてセットアップする
			status = NNS_G3dResDefaultSetup( *resFile );
			GF_ASSERT( status && "NNS_G3dResDefaultSetup failed" );
		}
	}
 	 
    // G3D: モデルの取得
    // nsbmdはモデルを複数含むことができるので、インデックス(モデルが１つの場合は0)
    // を指定して１つのモデルへのポインタを取得する。
    *model = NNS_G3dGetMdlByIdx( NNS_G3dGetMdlSet(*resFile), 0 );
	GF_ASSERT( model && "NNS_G3dGetMdlByIdx() failed" );
	NNS_G3dRenderObjInit( object_p, *model );
}

//--------------------------------------------------------------
/**
 * simple_3DModelSet　フィールドエフェクト版
 * @param	
 * @retval
 */
//--------------------------------------------------------------
void FE_simple3DModelInit( FE_SYS *fes, u32 dataid, ALLOCTYPE type,
	NNSG3dRenderObj *object_p, NNSG3dResMdl **model, NNSG3dResFileHeader **resFile )
{
    *resFile = FE_ArcDataLoadAlloc( fes, dataid, type );
	FE_simple3DModelInitOnly( fes, object_p, model, resFile );
}

//----------------------------------------------------------------------------
/**
 *	@brief	モデル転送タスク
 */
//-----------------------------------------------------------------------------
static void FLD_3DObjMdlTransTcb( TCB_PTR tcb, void* p_work )
{
	FLD_3DOBJ_MDL* p_mdl = p_work;
	LoadVRAMTexture( p_mdl->pMdlTex );
	BindTexture( p_mdl->pResMdl, p_mdl->pMdlTex );
	TCB_Delete( tcb );
}

//----------------------------------------------------------------------------
/**
 *	@brief	３Dモデル読み込み
 */
//-----------------------------------------------------------------------------
void FE_3DObjMdlLoad( FE_SYS *fes, FLD_3DOBJ_MDL *p_mdl, u32 dataid, ALLOCTYPE type )
{
	p_mdl->pResMdl = FE_ArcDataLoadAlloc( fes, dataid, type );
	p_mdl->pModelSet	= NNS_G3dGetMdlSet( p_mdl->pResMdl );
	p_mdl->pModel		= NNS_G3dGetMdlByIdx( p_mdl->pModelSet, 0 );
	p_mdl->pMdlTex		= NNS_G3dGetTex( p_mdl->pResMdl );
	
	if( p_mdl->pMdlTex ){
		// テクスチャデータ転送
		VIntrTCB_Add( FLD_3DObjMdlTransTcb, p_mdl, FLD_3DOBJ_TEXTRANS_TCB_PRI );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	３Dアニメデータ読み込み
 */
//-----------------------------------------------------------------------------
void FE_3DObjAnmLoad(
		FE_SYS *fes,
		FLD_3DOBJ_ANM *p_anm,
		const FLD_3DOBJ_MDL *cp_mdl,
		NNSFndAllocator* pallocator,
		u32 dataid, ALLOCTYPE type )
{
	p_anm->pResAnm = FE_ArcDataLoadAlloc( fes, dataid, type );
	p_anm->pOneResAnm = NNS_G3dGetAnmByIdx(p_anm->pResAnm,0);
	p_anm->pAnmObj = NNS_G3dAllocAnmObj( pallocator, p_anm->pOneResAnm, cp_mdl->pModel );
	
	NNS_G3dAnmObjInit(
		p_anm->pAnmObj,
		p_anm->pOneResAnm,
		cp_mdl->pModel,
		cp_mdl->pMdlTex );
}

//------------------------------------------------------------------
/**
 * NitroSystem ライブラリ系関数が要求するアロケータを作成する
 */
//------------------------------------------------------------------
void FE_InitAllocator( FE_SYS *fes, NNSFndAllocator *pAllocator )
{
	sys_InitAllocator( pAllocator, fe_HeapIDGet(fes), 32 );
}

//==============================================================================
//	debug
//==============================================================================
#ifdef DEBUG_FE_EOA_USE_CHECK

#define DB_FE_EOA_USE_CHECK_MAX (80)

FIELDSYS_WORK *DebugFeEoaUseCheck_FieldSysWork;
u32 DebugFeEoaUseCheck_ZoneIDTbl[DB_FE_EOA_USE_CHECK_MAX];
u32 DebugFeEoaUseCheck_HeadTbl[DB_FE_EOA_USE_CHECK_MAX];
u32 DebugFeEoaUseCheck_EoaTbl[DB_FE_EOA_USE_CHECK_MAX];

//--------------------------------------------------------------
//	eoa 追加チェック　初期化
//--------------------------------------------------------------
static void DEBUG_FeEoaUseCheck_Init( FE_SYS *fes )
{
	int i;
	DebugFeEoaUseCheck_FieldSysWork = fes->fsys;
	
	for( i = 0; i < DB_FE_EOA_USE_CHECK_MAX; i++ ){
		DebugFeEoaUseCheck_ZoneIDTbl[i] = 0xffffffff;
		DebugFeEoaUseCheck_HeadTbl[i] = 0;
		DebugFeEoaUseCheck_EoaTbl[i] = 0;
	}
}

//--------------------------------------------------------------
//	eoa 追加チェック　追加
//--------------------------------------------------------------
static void DEBUG_FeEoaUseCheck_Add( EOA_PTR eoa, const EOA_H_NPP *head )
{
	int i;
	FIELDSYS_WORK *fsys = DebugFeEoaUseCheck_FieldSysWork;
	u32 zone_id = fsys->location->zone_id;
	
	for( i = 0; i < DB_FE_EOA_USE_CHECK_MAX; i++ ){
		if( DebugFeEoaUseCheck_EoaTbl[i] == (u32)NULL ){
			DebugFeEoaUseCheck_ZoneIDTbl[i] = zone_id;
			DebugFeEoaUseCheck_HeadTbl[i] = (u32)head;
			DebugFeEoaUseCheck_EoaTbl[i] = (u32)eoa;
			return;
		}
	}
}

//--------------------------------------------------------------
//	eoa 追加チェック　削除
//--------------------------------------------------------------
static void DEBUG_FeEoaUseCheck_Del( EOA_PTR eoa )
{
	int i;
	
	for( i = 0; i < DB_FE_EOA_USE_CHECK_MAX; i++ ){
		if( DebugFeEoaUseCheck_EoaTbl[i] == (u32)eoa ){
			DebugFeEoaUseCheck_ZoneIDTbl[i] = 0xffffffff;
			DebugFeEoaUseCheck_HeadTbl[i] = 0;
			DebugFeEoaUseCheck_EoaTbl[i] = 0;
			return;
		}
	}
}
#endif
