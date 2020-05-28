//============================================================================================
/**
 * @file	field_clact.c
 * @brief	フィールド用セルアクター設定処理
 * @author	Hiroyuki Nakamura
 * @date	2005.01.13
 */
//============================================================================================
#include "common.h"
#include "system/clact_tool.h"

#define	FIELD_CLACT_H_GLOBAL
#include "field_clact.h"


static BOOL CATS_LoadResourceTable_Private( CLACT_U_RES_OBJ_TBL * tbl, CLACT_U_RES_OBJ_PTR obj );
static void CATS_LoadResourceCellArc_Private(
				FIELD_CLACT * fcat, int arc_id, int data_id, int comp, int type, int id );


//--------------------------------------------------------------------------------------------
/**
 * セルアクター設定
 *
 * @param	fcat	設定データ保存場所
 * @param	list	読み込みファイルリスト
 * @param	max		セルアクター最大数
 * @param	heap	ヒープID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void FieldCellActSet(
		FIELD_CLACT * fcat, const TCATS_RESOURCE_FILE_LIST * list, u32 max, u32 heap )
{
	CLACT_U_RES_HEADER_PTR rhb;
	CLACT_U_RES_HEADER_PTR rht;
	void * buf;
	u32	siz;
	u32 i;

	fcat->cas  = CLACT_U_SetEasyInit( max, &fcat->renddata, heap );
	fcat->heap = heap;

	// マルチセルが無い場合
	if( list->resource.mcell_path == NULL ){
		fcat->res_max = CLACT_U_RES_MAX - 2;
	}else{
		fcat->res_max = CLACT_U_RES_MAX;
	}
	
	// リソースマネージャー用ヘッダー領域の作成
	rht = sys_AllocMemory( heap, CLACT_U_ResManagerGetHeaderSize() * fcat->res_max );

	// リソースマネージャー用ヘッダー読み込み
	for( i=0; i<fcat->res_max; i++ ){
		rhb = CLACT_U_ResManagerGetHeaderNoData( rht, i );
		buf = sys_LoadFile( heap, list->res_file[i] );
		CLACT_U_ResManagerHeaderLoadBinary( buf, rhb, heap );
		sys_FreeMemoryEz( buf );
	}

	// リソースマネージャー作成
	for( i=0; i<fcat->res_max; i++ ){
		rhb = CLACT_U_ResManagerGetHeaderNoData( rht, i );
		siz = CLACT_U_ResManagerHeaderSetDataNum( rhb );
		fcat->resMan[i] = CLACT_U_ResManagerInit( siz, i, heap );
	}

	// リソースマネージャーに登録するデータ読み込み
	for( i=0; i<fcat->res_max; i++ ){
		rhb = CLACT_U_ResManagerGetHeaderNoData( rht, i );
		siz = CLACT_U_ResManagerHeaderSetDataNum( rhb );
		fcat->resObjTbl[i] = CLACT_U_ResManagerResObjTblMake( siz, heap );
		CLACT_U_ResManagerResAddsHd( fcat->resMan[i], rhb, fcat->resObjTbl[i], heap );
	}

	for( i=0; i<fcat->res_max; i++ ){
		rhb = CLACT_U_ResManagerGetHeaderNoData( rht, i );
		CLACT_U_ResManagerHeaderFree( rhb );
	}
	sys_FreeMemoryEz( rht );

	// マネージャに登録
	CLACT_U_CharManagerSetsAreaCont( fcat->resObjTbl[0] );
	CLACT_U_PlttManagerSetsCleanArea( fcat->resObjTbl[1] );
	
	// セルアクターヘッダー読み込み
	buf = sys_LoadFile( heap, list->resource.clact_header_path );
	fcat->clh = CLACT_U_MakeHeaderBinary(
					buf, heap,
					fcat->resMan[0], fcat->resMan[1],
					fcat->resMan[2], fcat->resMan[3],
					fcat->resMan[4], fcat->resMan[5] );
	sys_FreeMemoryEz( buf );
}

//--------------------------------------------------------------------------------------------
/**
 * セルアクター設定破棄
 *
 * @param	fcat	設定データ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void FieldCellActDelete( FIELD_CLACT * fcat )
{
	u32	i;

	CLACT_DestSet( fcat->cas );							// セットの破棄
	CLACT_U_CLACT_HeaderTblDelete( fcat->clh );			// セルアクターヘッダー破棄
	CLACT_U_CharManagerDeletes( fcat->resObjTbl[0] );	// キャラクタデータ破棄
	CLACT_U_PlttManagerDeletes( fcat->resObjTbl[1] );	// パレットデータ破棄

	for( i=0; i<fcat->res_max; i++ ){
		// リソースオブジェテーブルを破棄
		CLACT_U_ResManagerResObjTblDelete( fcat->resObjTbl[i] );
		// リソースマネージャ破棄
		CLACT_U_ResManagerDelete( fcat->resMan[i] );
	}
}

//--------------------------------------------------------------------------------------------
/**
 * セルアクター登録
 *
 * @param	fcat	設定データ
 * @param	prm		追加データ
 *
 * @return	登録したセルアクターのポインタ
 */
//--------------------------------------------------------------------------------------------
CLACT_WORK_PTR FieldCellActAdd( FIELD_CLACT * fcat, const TCATS_OBJECT_ADD_PARAM * prm )
{
	CLACT_ADD ca;
	CLACT_WORK_PTR cwp;
	VecFx32 sca = { FX32_ONE, FX32_ONE, FX32_ONE };
	VecFx32 pos;

	pos.x = prm->x * FX32_ONE;
	pos.y = prm->y * FX32_ONE;
	pos.z = prm->z * FX32_ONE;

	ca.ClActSet		= fcat->cas;
	ca.ClActHeader	= &fcat->clh->tbl[prm->no];
	ca.mat			= pos;
	ca.sca			= sca;
	ca.rot			= 0;
	ca.pri			= prm->pri;
	ca.DrawArea		= prm->d_area;
	ca.heap			= fcat->heap;

	cwp = CLACT_Add( &ca );
	GF_ASSERT( cwp && ("セルアクター登録失敗\n") );

	CLACT_AnmChg( cwp, prm->anm );
	CLACT_PaletteNoChgAddTransPlttNo( cwp, prm->pal );

	return cwp;
}


//--------------------------------------------------------------------------------------------
/**
 * セルアクター設定（単発用）
 *
 * @param	fcat	設定データ保存場所
 * @param	crnl	
 * @param	max		セルアクター最大数
 * @param	heap	ヒープID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void FieldCellActSet_S(
		FIELD_CLACT * fcat, TCATS_RESOURCE_NUM_LIST * crnl, u32 max, u32 heap )
{
	CLACT_U_RES_HEADER_PTR rhb;
	CLACT_U_RES_HEADER_PTR rht;
	void * buf;
	u32	siz;
	u32 i, j;

	fcat->cas  = CLACT_U_SetEasyInit( max, &fcat->renddata, heap );
	fcat->heap = heap;

	// マルチセルが無い場合
	if( crnl->resource_num.mcell_num == 0 || crnl->resource_num.mcell_anm_num == 0 ){
		fcat->res_max = CLACT_U_RES_MAX - 2;
		fcat->resMan[4] = NULL;
		fcat->resMan[5] = NULL;
	}else{
		fcat->res_max = CLACT_U_RES_MAX;
	}

	///< リソースマネージャー作成
	for( i=0; i<fcat->res_max; i++ ){
		fcat->resMan[i] = CLACT_U_ResManagerInit( crnl->res_num[i], i, heap );
	}

	///< リソースマネージャーに登録するデータ読み込み
	for( i=0; i<fcat->res_max; i++ ){
		if( crnl->res_num[i] == 0 ){ continue; }
		fcat->resObjTbl[i] = CLACT_U_ResManagerResObjTblMake( crnl->res_num[i], heap );
//		crp->resObjNum[i] = 0;
		for( j=0; j<fcat->resObjTbl[i]->tbl_num; j++ ){
			fcat->resObjTbl[i]->tbl[j] = NULL;
		}
	}
}

//--------------------------------------------------------------------------------------------
/**
 * パレットリソース設定
 *
 * @param	fcat		設定データ
 * @param	arc_id		アーカイブID
 * @param	data_id		データID
 * @param	comp		圧縮フラグ
 * @param	num			転送サイズ
 * @param	trans_mode	転送モード
 * @param	id			リソースID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void FldClact_LoadResPlttArc(
		FIELD_CLACT * fcat, int arc_id, int data_id, int comp, int num, int trans_mode, int id )
{
	CLACT_U_RES_OBJ_PTR obj;
	int ret;
	
	if( CLACT_U_ResManagerCheckID( fcat->resMan[1], id ) == FALSE){
		GF_ASSERT(0);
		return;
	}

	obj = CLACT_U_ResManagerResAddArcPltt(
				fcat->resMan[1], arc_id, data_id, comp, id, trans_mode, num, fcat->heap );

	if( obj != NULL ){
		ret = CLACT_U_PlttManagerSetCleanArea( obj );
		GF_ASSERT(ret == TRUE && "パレット登録失敗");
	
		CATS_LoadResourceTable_Private( fcat->resObjTbl[1], obj );	
		CLACT_U_PlttManagerGetPlttNo( obj, trans_mode );
		return;
	}
	GF_ASSERT(0);
}

//--------------------------------------------------------------------------------------------
/**
 * セルリソース設定
 *
 * @param	fcat		設定データ
 * @param	arc_id		アーカイブID
 * @param	data_id		データID
 * @param	comp		圧縮フラグ
 * @param	id			リソースID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void FldClact_LoadResCellArc( FIELD_CLACT * fcat, int arc_id, int data_id, int comp, int id )
{
	CATS_LoadResourceCellArc_Private( fcat, arc_id, data_id, comp, 2, id );
}

//--------------------------------------------------------------------------------------------
/**
 * セルアニメリソース設定
 *
 * @param	fcat		設定データ
 * @param	arc_id		アーカイブID
 * @param	data_id		データID
 * @param	comp		圧縮フラグ
 * @param	id			リソースID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void FldClact_LoadResCellAnmArc( FIELD_CLACT * fcat, int arc_id, int data_id, int comp, int id )
{
	CATS_LoadResourceCellArc_Private( fcat, arc_id, data_id, comp, 3, id );
}

//--------------------------------------------------------------------------------------------
/**
 * キャラリソース設定
 *
 * @param	fcat		設定データ
 * @param	arc_id		アーカイブID
 * @param	data_id		データID
 * @param	comp		圧縮フラグ
 * @param	trans_mode	転送モード
 * @param	id			リソースID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void FldClact_LoadResourceCharArc(
		FIELD_CLACT * fcat, int arc_id, int data_id, BOOL comp, int trans_mode, int id )
{
	CLACT_U_RES_OBJ_PTR obj;

	if( CLACT_U_ResManagerCheckID( fcat->resMan[0], id ) == FALSE ){
		GF_ASSERT(0);
		return;
	}
	
	obj = CLACT_U_ResManagerResAddArcChar(
			fcat->resMan[0], arc_id, data_id, comp, id, trans_mode, fcat->heap );

	if( obj != NULL ){
		CLACT_U_CharManagerSetAreaCont(obj);
		
		CATS_LoadResourceTable_Private( fcat->resObjTbl[0], obj );	
		
		return;
	}
	
	GF_ASSERT(0);
}

//--------------------------------------------------------------------------------------------
/**
 * キャラのリーソースを変更する
 *
 * @param	fcat		設定データ
 * @param	arc_id		アーカイブID
 * @param	data_id		データID
 * @param	comp		圧縮フラグ
 * @param	id			リソースID
 *
 * @retval	BOOL	
 */
//--------------------------------------------------------------------------------------------
void FldClact_ChangeResourceCharArc(
					FIELD_CLACT * fcat, int arc_id, int data_id, BOOL comp, int id )
{
	CLACT_U_RES_OBJ_PTR	obj = CLACT_U_ResManagerGetIDResObjPtr( fcat->resMan[0], id );
	CLACT_U_ResManagerResChgArcChar( fcat->resMan[0], obj, arc_id, data_id, comp, fcat->heap );
	CLACT_U_CharManagerReTrans( obj );
}

//--------------------------------------------------------------------------------------------
/**
 * パレットのリーソースを変更する
 *
 * @param	fcat		設定データ
 * @param	arc_id		アーカイブID
 * @param	data_id		データID
 * @param	comp		圧縮フラグ
 * @param	id			リソースID
 *
 * @retval	BOOL	
 */
//--------------------------------------------------------------------------------------------
void FldClact_ChangeResourcePlttArc(
					FIELD_CLACT * fcat, int arc_id, int data_id, BOOL comp, int id )
{
	CLACT_U_RES_OBJ_PTR	obj = CLACT_U_ResManagerGetIDResObjPtr( fcat->resMan[1], id );
	CLACT_U_ResManagerResChgArcPltt( fcat->resMan[1], obj, arc_id, data_id, comp, fcat->heap );
	CLACT_U_PlttManagerReTrans( obj );
}

static BOOL CATS_LoadResourceTable_Private( CLACT_U_RES_OBJ_TBL * tbl, CLACT_U_RES_OBJ_PTR obj )
{
	int i;
	
	for( i=0; i<tbl->tbl_num; i++ ){
		if( tbl->tbl[i] != NULL ){ continue; }
		tbl->tbl[i] = obj;
		tbl->tbl_now++;
		return TRUE;
	}
	return FALSE;
}

static void CATS_LoadResourceCellArc_Private(
				FIELD_CLACT * fcat, int arc_id, int data_id, int comp, int type, int id )
{
	CLACT_U_RES_OBJ_PTR obj;
	int ret;

	if( CLACT_U_ResManagerCheckID( fcat->resMan[type], id ) == FALSE ){
		GF_ASSERT(0);
		return;
	}
	
	obj = CLACT_U_ResManagerResAddArcKindCell(
				fcat->resMan[type], arc_id, data_id, comp, id, type, fcat->heap );

	if (obj != NULL){
		ret = CATS_LoadResourceTable_Private( fcat->resObjTbl[type], obj );
		
		GF_ASSERT(ret == TRUE && "セル登録失敗");
		
		return;
	}
	
	GF_ASSERT(0);
}



//--------------------------------------------------------------------------------------------
/**
 * セルアクター追加（単発用）
 *
 * @param	fcat		設定データ
 * @param	coap_s		表示データ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
CATS_ACT_PTR FieldCellActAdd_S(
				FIELD_CLACT * fcat, const TCATS_OBJECT_ADD_PARAM_S * coap_s )
{
	int i;
	int def_palno;
	CATS_ACT_PTR cap = NULL;
	CLACT_ADD	 add;
	int id_list[CLACT_U_RES_MAX];

	cap = sys_AllocMemory( fcat->heap, sizeof(TCATS_ACT) );

	///< ヘッダーのメモリ確保
	cap->act_htp = sys_AllocMemory( fcat->heap, sizeof(CLACT_HEADER_TBL) );

	cap->act_htp->tbl = sys_AllocMemory( fcat->heap, sizeof(CLACT_HEADER) );
	cap->act_hd = cap->act_htp->tbl;

	///< リソースIDを書き換える
	for( i=0; i<CLACT_U_RES_MAX; i++ ){
		id_list[i] = coap_s->id[i];
	}
	
	if( fcat->resMan[4] == NULL || fcat->resMan[5] == NULL ){
		///< マネージャーが無い場合は、データ指定無し
		id_list[4] = CLACT_U_HEADER_DATA_NONE;
		id_list[5] = CLACT_U_HEADER_DATA_NONE;
	}else{	
		///< データ指定されていても、指定IDのリソースが無い場合もデータ無し
		if( id_list[4] != CLACT_U_HEADER_DATA_NONE &&
			CLACT_U_ResManagerCheckID( fcat->resMan[4], id_list[4] ) == FALSE ){
			id_list[4] = CLACT_U_HEADER_DATA_NONE;
		}

		if( id_list[5] != CLACT_U_HEADER_DATA_NONE &&
			CLACT_U_ResManagerCheckID( fcat->resMan[5], id_list[5] ) == FALSE ){
			id_list[5] = CLACT_U_HEADER_DATA_NONE;
		}	
	}
	
	///< 実際にヘッダーを作成
	CLACT_U_MakeHeader(
		cap->act_hd,
		id_list[0], id_list[1], id_list[2],
		id_list[3], id_list[4], id_list[5],
		coap_s->vram_trans, coap_s->bg_pri,
		fcat->resMan[0], fcat->resMan[1], fcat->resMan[2],
		fcat->resMan[3], fcat->resMan[4], fcat->resMan[5] );
	
	///< OBJ の登録
	add.ClActSet	= fcat->cas;
	add.ClActHeader = cap->act_hd;

	add.mat.x		= FX32_CONST(coap_s->x);		///< 座標
	add.mat.y		= FX32_CONST(coap_s->y);
	add.mat.z		= FX32_CONST(coap_s->z);
	if(coap_s->d_area == NNS_G2D_VRAM_TYPE_2DSUB){
		add.mat.y += SUB_SURFACE_Y;
	}
	
	add.sca.x		= FX32_ONE;						///< 拡縮率
	add.sca.y		= FX32_ONE;
	add.sca.z		= FX32_ONE;
	
	add.rot			= 0;							///< 回転角
	add.pri			= coap_s->pri;					///< 優先度
	add.DrawArea	= coap_s->d_area;				///< 描画面
	add.heap		= fcat->heap;				///< ヒープ領域
	
	cap->act = CLACT_Add(&add);						///< 登録
	
	if (cap->act != NULL){
		def_palno = CLACT_PaletteNoGet(cap->act);				///< 基本パレット番号取得
		CLACT_AnmChg(cap->act, coap_s->anm);					///< アニメーション指定
		CLACT_PaletteNoChg(cap->act, def_palno + coap_s->pal);	///< パレット指定
	}
	else{
		GF_ASSERT(0 && "アクター登録失敗");
	}
	return cap;		
}

//--------------------------------------------------------------------------------------------
/**
 * セルアクター削除（単発用）
 *
 * @param	fcat		設定データ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void FieldCellActDelete_S( FIELD_CLACT * fcat )
{
	u32	i;

	CLACT_DestSet( fcat->cas );							// セットの破棄
	CLACT_U_CharManagerDeletes( fcat->resObjTbl[0] );	// キャラクタデータ破棄
	CLACT_U_PlttManagerDeletes( fcat->resObjTbl[1] );	// パレットデータ破棄

	for( i=0; i<fcat->res_max; i++ ){
		// リソースオブジェテーブルを破棄
		CLACT_U_ResManagerResObjTblDelete( fcat->resObjTbl[i] );
		// リソースマネージャ破棄
		CLACT_U_ResManagerDelete( fcat->resMan[i] );
	}
}
