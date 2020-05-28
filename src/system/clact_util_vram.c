//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		clact_util_vram.c
 *@brief	セルアクターユーティリティリソースマネージャーを使用しキャラクタデータ、パレットデータをVramに転送するシステム
 *@author	tomoya takahashi
 *@data		2005.09.02
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "assert.h"

#include "char_manager.h"
#include "pltt_manager.h"

#define __CLACT_UTIL_VRAM_H_GLOBAL
#include "include/system/clact_util_vram.h"

//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------


//////////////////////////////////////////////////////////////////////////////
// キャラクタデータ転送関数
// オフセットタイプ
// 上から順に詰めてVramに転送していきます。
// しかし解放などしても解放した領域を認識して、
// その領域に再度違うキャラクタを転送するなどができません。
//////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
/**
 *
 *@brief	キャラクタマネジャーにリソースオブジェないのキャラクタデータを設定
 *
 *@param	resObj	リソースオブジェ
 *
 *@retval	TRUE	成功
 *@retval	FALSE	失敗
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL CLACT_U_CharManagerSet( CONST_CLACT_U_RES_OBJ_PTR resObj )
{
	CHAR_MANAGER_HEADER char_data;

	GF_ASSERT(resObj);
	GF_ASSERT(CLACT_U_ResManagerGetResObjResType(resObj) == CLACT_U_CHAR_RES);
	
	// キャラクタデータ取得
	char_data.res_file = CLACT_U_ResManagerGetResObjResChar(resObj);

	char_data.type = CLACT_U_ResManagerGetResObjVramType(resObj);
	char_data.id	= CLACT_U_ResManagerGetResObjID(resObj);
	char_data.cont_type = CHARM_CONT_OFFSET;

	// 登録
	return CharSet(&char_data);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	キャラクタマネジャーにリソースオブジェないのキャラクタデータを設定（複数）
 *
 *@param	resTbl		リソースオブジェテーブルのポインタ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_CharManagerSets( const CLACT_U_RES_OBJ_TBL* resTbl )
{
	int i;		// ループ用
	BOOL check;
	GF_ASSERT(resTbl);

	for(i=0;i<resTbl->tbl_num;i++){

		if( resTbl->tbl[i] ){
			check = CLACT_U_CharManagerSet(resTbl->tbl[i]);
			GF_ASSERT_MSG( check, "キャラクタデータ登録失敗\n" );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	キャラクタマネジャーにリソースオブジェないのキャラクタデータを設定
 *				マッピングモードを今の状態に変更するモード
 *
 *@param	resObj	リソースオブジェ
 *
 *@retval	TRUE	成功
 *@retval	FALSE	失敗
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL CLACT_U_CharManagerSetCharModeAdjust( CONST_CLACT_U_RES_OBJ_PTR resObj )
{
	CHAR_MANAGER_HEADER char_data;

	GF_ASSERT(resObj);
	GF_ASSERT(CLACT_U_ResManagerGetResObjResType(resObj) == CLACT_U_CHAR_RES);
	
	// キャラクタデータ取得
	char_data.res_file = CLACT_U_ResManagerGetResObjResChar(resObj);

	char_data.type = CLACT_U_ResManagerGetResObjVramType(resObj);
	char_data.id	= CLACT_U_ResManagerGetResObjID(resObj);
	char_data.cont_type = CHARM_CONT_OFFSET;

	// 登録
	return CharSetCharModeAdjust(&char_data);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	キャラクタマネジャーにリソースオブジェないのキャラクタデータを設定（複数）
 *				マッピングモードを今の状態に変更するモード
 *
 *@param	resTbl		リソースオブジェ配列のポインタ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_CharManagerSetsCharModeAdjust( const CLACT_U_RES_OBJ_TBL* resTbl )
{
	int i;		// ループ用
	BOOL check;	// ﾁｪｯｸ用
	GF_ASSERT(resTbl);

	for(i=0;i<resTbl->tbl_num;i++){
		if( resTbl->tbl[ i ] ){
			check = CLACT_U_CharManagerSetCharModeAdjust(resTbl->tbl[i]);
			GF_ASSERT_MSG( check, "キャラクタデータ登録失敗\n" );
		}
	}
}



//////////////////////////////////////////////////////////////////////////////
// キャラクタデータ転送関数
// エリアコントロールタイプ
// vramエリアを１キャラごとに管理する配列を作成して、
// 空き領域から使用できるvramエリアを検索します。
//////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
/**
 *
 *@brief	キャラクタマネジャーにリソースオブジェないのキャラクタデータを設定
 *
 *@param	resObj	リソースオブジェ
 *
 *@retval	TRUE	成功
 *@retval	FALSE	失敗
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL CLACT_U_CharManagerSetAreaCont( CONST_CLACT_U_RES_OBJ_PTR resObj )
{
	CHAR_MANAGER_HEADER char_data;

	GF_ASSERT(resObj);
	GF_ASSERT(CLACT_U_ResManagerGetResObjResType(resObj) == CLACT_U_CHAR_RES);
	
	// キャラクタデータ取得
	char_data.res_file = CLACT_U_ResManagerGetResObjResChar(resObj);

	char_data.type = CLACT_U_ResManagerGetResObjVramType(resObj);
	char_data.id	= CLACT_U_ResManagerGetResObjID(resObj);
	char_data.cont_type = CHARM_CONT_AREACONT;

	// 登録
	return CharSet(&char_data);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	キャラクタマネジャーにリソースオブジェないのキャラクタデータを設定（複数）
 *
 *@param	resTbl		リソースオブジェテーブルのポインタ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_CharManagerSetsAreaCont( const CLACT_U_RES_OBJ_TBL* resTbl )
{
	int i;		// ループ用
	BOOL check;	// ﾁｪｯｸ用
	GF_ASSERT(resTbl);

	for(i=0;i<resTbl->tbl_num;i++){

		if( resTbl->tbl[i] ){
			check = CLACT_U_CharManagerSetAreaCont(resTbl->tbl[i]);
			GF_ASSERT_MSG( check, "キャラクタデータ登録失敗" );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	キャラクタマネジャーにリソースオブジェないのキャラクタデータを設定
 *				マッピングモードを今の状態に変更するモード
 *
 *@param	resObj	リソースオブジェ
 *
 *@retval	TRUE	成功
 *@retval	FALSE	失敗
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL CLACT_U_CharManagerSetCharModeAdjustAreaCont( CONST_CLACT_U_RES_OBJ_PTR resObj )
{
	CHAR_MANAGER_HEADER char_data;

	GF_ASSERT(resObj);
	GF_ASSERT(CLACT_U_ResManagerGetResObjResType(resObj) == CLACT_U_CHAR_RES);
	
	// キャラクタデータ取得
	char_data.res_file = CLACT_U_ResManagerGetResObjResChar(resObj);

	char_data.type = CLACT_U_ResManagerGetResObjVramType(resObj);
	char_data.id	= CLACT_U_ResManagerGetResObjID(resObj);
	char_data.cont_type = CHARM_CONT_AREACONT;

	// 登録
	return CharSetCharModeAdjust(&char_data);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	キャラクタマネジャーにリソースオブジェないのキャラクタデータを設定（複数）
 *				マッピングモードを今の状態に変更するモード
 *
 *@param	resTbl		リソースオブジェ配列のポインタ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_CharManagerSetsCharModeAdjustAreaCont( const CLACT_U_RES_OBJ_TBL* resTbl )
{
	int i;		// ループ用
	BOOL check;	// ﾁｪｯｸ用
	GF_ASSERT(resTbl);

	for(i=0;i<resTbl->tbl_num;i++){
		if( resTbl->tbl[ i ] ){
			check = CLACT_U_CharManagerSetCharModeAdjustAreaCont(resTbl->tbl[i]);
			GF_ASSERT_MSG( check, "キャラクタデータ登録失敗\n" );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	キャラクタデータを変更する
 *
 *	@param	nowTbl		今のキャラクタデータ
 *	@param	newTbl		変更するキャラクタデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_CharManagerChg( CONST_CLACT_U_RES_OBJ_PTR nowTbl, CONST_CLACT_U_RES_OBJ_PTR newTbl )
{
	int id;
	NNSG2dCharacterData* data;
	
	GF_ASSERT(nowTbl);
	GF_ASSERT(newTbl);

	// プロクシとキャラクタデータ取得
	id = CLACT_U_ResManagerGetResObjID( nowTbl );
	data = CLACT_U_ResManagerGetResObjResChar( newTbl );

	// 入れ替える
	CharDataChg(id, data);
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	キャラクタデータの再転送を行う
 *
 *	@param	resObj	リソースオブジェ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_CharManagerReTrans( CONST_CLACT_U_RES_OBJ_PTR resObj )
{
	int id;
	NNSG2dCharacterData* data;

	GF_ASSERT(resObj);

	// プロクシとキャラクタデータ取得
	id = CLACT_U_ResManagerGetResObjID( resObj );
	data = CLACT_U_ResManagerGetResObjResChar( resObj );
	
	CharDataChg(id, data);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	キャラクタマネジャーからリソースオブジェのIDのキャラクタデータを破棄
 *
 *@param	resObj		リソースオブジェのポインタ
 *
 *@return none
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_CharManagerDelete( CLACT_U_RES_OBJ_PTR resObj )
{
	int id;
	GF_ASSERT(resObj);
	GF_ASSERT(CLACT_U_ResManagerGetResObjResType(resObj) == CLACT_U_CHAR_RES);
	
	id = CLACT_U_ResManagerGetResObjID(resObj);
	DelChar(id);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	キャラクタマネジャーからリソースオブジェテーブルに対応するデータを破棄
 *
 *@param	resTbl		リソースオブジェテーブル
 *
 *@return none
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_CharManagerDeletes( CLACT_U_RES_OBJ_TBL* resTbl )
{
	int i;		// ループ用
	GF_ASSERT(resTbl);

	for(i=0;i<resTbl->tbl_num;i++){
		if( resTbl->tbl[ i ] ){
			CLACT_U_CharManagerDelete(resTbl->tbl[i]);
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	イメージプロクシを取得
 *
 *@param	resObj	リソースオブジェ
 *
 *@return	NNSG2dImageProxy*	イメージプロクシ
 *
 *
 */
//-----------------------------------------------------------------------------
NNSG2dImageProxy* CLACT_U_CharManagerGetProxy( CONST_CLACT_U_RES_OBJ_PTR resObj )
{
	int id;
	GF_ASSERT(resObj);
	GF_ASSERT(CLACT_U_ResManagerGetResObjResType(resObj) == CLACT_U_CHAR_RES);

	id = CLACT_U_ResManagerGetResObjID(resObj);
	return GetCharIDProxy( id );	
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	２Dマップキャラクタを読み込む
 *
 *	@param	resObj		リソースオブジェ
 *	@param	proxy		転送データを格納するプロクシ
 *	@param	base_addr	Vramベースアドレス
 * 
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_2DmapCharLoad( CONST_CLACT_U_RES_OBJ_PTR resObj, NNSG2dImageProxy* proxy, int base_addr )
{
	NNSG2dCharacterData* char_data;
	int	vram_type;

	GF_ASSERT(resObj);
	GF_ASSERT(CLACT_U_ResManagerGetResObjResType(resObj) == CLACT_U_CHAR_RES);
	
	// キャラクタデータ取得
	char_data = CLACT_U_ResManagerGetResObjResChar(resObj);
	vram_type = CLACT_U_ResManagerGetResObjVramType(resObj);

	
	// 読み込み
	NNS_G2dLoadImage2DMapping( 
			char_data,
			base_addr,
			vram_type,
			proxy );
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	Vram転送用のイメージプロクシを取得
 *
 *@param	charObj	キャラクタリソースオブジェ
 *@param	cellObj	セルリソースオブジェ
 *
 *@return	NNSG2dImageProxy*	イメージプロクシ
 *
 *
 */
//-----------------------------------------------------------------------------
NNSG2dImageProxy* CLACT_U_CharManagerGetVramTransferProxy( CONST_CLACT_U_RES_OBJ_PTR charObj, CONST_CLACT_U_RES_OBJ_PTR cellObj )
{
	int id;
	NNSG2dCellDataBank* cellData;
	NNSG2dImageProxy* proxy;
	
	GF_ASSERT(charObj);
	GF_ASSERT(CLACT_U_ResManagerGetResObjResType(charObj) == CLACT_U_CHAR_RES);
	GF_ASSERT(cellObj);
	GF_ASSERT(CLACT_U_ResManagerGetResObjResType(cellObj) == CLACT_U_CELL_RES);
	
	
	// キャラクタデータID取得
	id = CLACT_U_ResManagerGetResObjID(charObj);

	// セルデータ取得
	cellData = CLACT_U_ResManagerGetResObjResCell(cellObj);
	
	proxy = GetCharVramTransData( id, cellData->pVramTransferData->szByteMax );	
	if(proxy == NULL){
		NNSG2dImageProxy* org;
		org = GetCharIDProxy( id );
		// コピー作成
		proxy = GetCharVramTransProxyCopy( org );
	}

	return proxy;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	セルVram転送アニメのVram領域を開放
 *
 *@param	pImage		Vram転送用に作成されたイメージプロクシ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_CharManagerDeleteVramTransferProxy( const NNSG2dImageProxy* pImage )
{
	GF_ASSERT(pImage);
	
	DelVramTransData( pImage );	
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	パレットマネージャーにリソースオブジェ内のパレットデータを設定
 *
 *@param	resObj	リソースオブジェ
 *
 *@retval	TRUE	成功
 *@retval	FALSE	失敗
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL CLACT_U_PlttManagerSet( CONST_CLACT_U_RES_OBJ_PTR resObj )
{
	PLTT_MANAGER_HEADER pltt_data;

	GF_ASSERT(resObj);
	GF_ASSERT(CLACT_U_ResManagerGetResObjResType(resObj) == CLACT_U_PLTT_RES);
	
	// リソース取得
	pltt_data.res_file = CLACT_U_ResManagerGetResObjResPltt(resObj);

	pltt_data.type		= CLACT_U_ResManagerGetResObjVramType(resObj);
	pltt_data.id		= CLACT_U_ResManagerGetResObjID(resObj);
	pltt_data.pltt_num	= CLACT_U_ResManagerGetResObjPlttNum(resObj);

	// 登録
	return PlttSet(&pltt_data);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	パレットマネジャーにリソースオブジェないのパレットデータを設定（複数）
	 *
 *@param	resTbl		リソースオブジェテーブルポインタ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_PlttManagerSets( const CLACT_U_RES_OBJ_TBL* resTbl )
{
	int i;
	BOOL check;
	GF_ASSERT(resTbl);

	for(i=0;i<resTbl->tbl_num;i++){
		if( resTbl->tbl[ i ] ){
			check = CLACT_U_PlttManagerSet(resTbl->tbl[i]);
			GF_ASSERT_MSG( check ,"パレット転送失敗\n" );
		}
	}
}

// 空き領域を検索して転送します
// ただし、上の転送関数を使用してその後に転送すると
// 上書きされます。
//----------------------------------------------------------------------------
/**
 *
 *@brief	パレットマネージャーにリソースオブジェ内のパレットデータを設定
 *
 *@param	resObj	リソースオブジェ
 *
 *@retval	TRUE	成功
 *@retval	FALSE	失敗
 *
 * CLACT_U_RES_OBJ_PTR	リソースオブジェ
 * CLACT_U_ResManagerResAddPltt関数などの戻り値
 * 読み込んだリソースのデータ　管理IDなどが格納されています。
 *
 */
//-----------------------------------------------------------------------------
BOOL CLACT_U_PlttManagerSetCleanArea( CONST_CLACT_U_RES_OBJ_PTR resObj )
{
	PLTT_MANAGER_HEADER pltt_data;

	GF_ASSERT(resObj);
	GF_ASSERT(CLACT_U_ResManagerGetResObjResType(resObj) == CLACT_U_PLTT_RES);
	
	// リソース取得
	pltt_data.res_file = CLACT_U_ResManagerGetResObjResPltt(resObj);

	pltt_data.type		= CLACT_U_ResManagerGetResObjVramType(resObj);
	pltt_data.id		= CLACT_U_ResManagerGetResObjID(resObj);
	pltt_data.pltt_num	= CLACT_U_ResManagerGetResObjPlttNum(resObj);

	// 登録
	return PlttSetCleanArea(&pltt_data);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	パレットマネジャーにリソースオブジェないのパレットデータを設定（複数）
 *
 *@param	resTbl		リソースオブジェテーブルポインタ
 *
 *@return	none
 *
 * CLACT_U_RES_OBJ_TBL　リソースオブジェテーブル
	typedef struct {
		CLACT_U_RES_OBJ_PTR*	tbl;// ポインタを格納するテーブルのポインタ
		int		tbl_num;			// テーブル要素数
		int		tbl_now;			// 現在格納数
	} CLACT_U_RES_OBJ_TBL;
	上の構造体を下の関数で作成できます。
	GLOBAL CLACT_U_RES_OBJ_TBL* CLACT_U_ResManagerResObjTblMake(int inResObjNum, int heap);
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_PlttManagerSetsCleanArea( const CLACT_U_RES_OBJ_TBL* resTbl )
{
	int i;
	BOOL check;
	GF_ASSERT(resTbl);

	for(i=0;i<resTbl->tbl_num;i++){
		if( resTbl->tbl[ i ] ){
			check = CLACT_U_PlttManagerSetCleanArea(resTbl->tbl[i]);
			GF_ASSERT_MSG( check, "パレット転送失敗\n" );
		}
	}
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	パレットデータ変更
 *
 *	@param	nowObj		今のパレットデータのリソースオブジェ
 *	@param	newObj		変更するパレットのリソースオブジェ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_PlttManagerChg( CONST_CLACT_U_RES_OBJ_PTR nowObj, CONST_CLACT_U_RES_OBJ_PTR newObj )
{
	NNSG2dPaletteData* data;
	int id;
	int trans_num;
	
	GF_ASSERT(nowObj);
	GF_ASSERT(newObj);

	// プロクシとパレットデータ取得
	id = CLACT_U_ResManagerGetResObjID( nowObj );
	
	data = CLACT_U_ResManagerGetResObjResPltt( newObj );
	
	// 入れ替える
	PlttDataChg(id, data );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	パレットデータの再転送を行う
 *
 *	@param	resObj	リソースオブジェ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_PlttManagerReTrans( CONST_CLACT_U_RES_OBJ_PTR resObj )
{
	NNSG2dPaletteData* data;
	int id;
	int trans_num;
	
	GF_ASSERT(resObj);

	// プロクシとパレットデータ取得
	id = CLACT_U_ResManagerGetResObjID( resObj );
	
	data = CLACT_U_ResManagerGetResObjResPltt( resObj );

	// 入れ替える
	PlttDataChg(id, data );

}

//----------------------------------------------------------------------------
/**
 *
 *@brief	パレットマネジャーからリソースオブジェのIDのパレットデータを破棄
 *
 *@param	resObj		リソースオブジェのポインタ
 *
 *@return none
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_PlttManagerDelete( CLACT_U_RES_OBJ_PTR resObj )
{
	int id;
	GF_ASSERT(resObj);
	GF_ASSERT(CLACT_U_ResManagerGetResObjResType(resObj) == CLACT_U_PLTT_RES);
	
	id = CLACT_U_ResManagerGetResObjID(resObj);
	DelPltt(id);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	パレットマネジャーからリソースオブジェのIDのパレットデータを破棄
 *
 *@param	resTbl		リソースオブジェテーブルのポインタ
 *
 *@return none
 *
 */
//-----------------------------------------------------------------------------
void CLACT_U_PlttManagerDeletes( CLACT_U_RES_OBJ_TBL* resTbl )
{
	int i;		// ループ用
	
	GF_ASSERT(resTbl);

	for(i=0;i<resTbl->tbl_num;i++){

		if( resTbl->tbl[ i ] ){
			CLACT_U_PlttManagerDelete(resTbl->tbl[i]);
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	パレットプロクシを取得
 *
 *@param	resObj	リソースオブジェパラメータ
 *@param	pImage	関連ずけるイメージプロクシ
 *
 *@return	パレットプロクシ
 *
 *
 */
//-----------------------------------------------------------------------------
const NNSG2dImagePaletteProxy* CLACT_U_PlttManagerGetProxy( CONST_CLACT_U_RES_OBJ_PTR resObj, NNSG2dImageProxy* pImage )
{
	int id;
	GF_ASSERT(resObj);
	GF_ASSERT(CLACT_U_ResManagerGetResObjResType(resObj) == CLACT_U_PLTT_RES);

	id = CLACT_U_ResManagerGetResObjID(resObj);

	if( pImage ){
		return GetPlttIDProxyJoin(id, pImage);
	}

	return GetPlttIDProxy( id );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	登録されているパレットが何番のパレットに転送されているかを返す
 *
 *	@param	resObj		リソースオブジェ
 *	@param	vram		vramタイプ
 *
 *	@retval	CLACT_U_PLTT_NO_NONE以外	転送されたパレット番号
 *	@retval	CLACT_U_PLTT_NO_NONE		パレット転送されていない
 *
 * vramタイプ
 *	NNS_G2D_VRAM_TYPE_2DMAIN    ２ＤグラフィックスエンジンＡ用
 *  NNS_G2D_VRAM_TYPE_2DSUB     ２ＤグラフィックスエンジンＢ用
 *
 * resObj
 *	GLOBAL CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerGetIDResObjPtr(CONST_CLACT_U_RES_MANAGER_PTR resm, int id);
 *	関数で取得してください。
 *
 *
 */
//-----------------------------------------------------------------------------
u32 CLACT_U_PlttManagerGetPlttNo( CONST_CLACT_U_RES_OBJ_PTR resObj, NNS_G2D_VRAM_TYPE type )
{
	int no;
	const NNSG2dImagePaletteProxy* imgpltt;

	imgpltt = CLACT_U_PlttManagerGetProxy( resObj, NULL );
	no =  NNS_G2dGetImagePaletteLocation( imgpltt, type );

	// addr->noにする
	if( no != CLACT_U_PLTT_NO_NONE ){
		no /= 32;
	}

	return no;
}
