//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		clact_util_vram.h
 *@brief	セルアクターユーティリティリソースマネージャーを使用しキャラクタデータパレットデータをVramに転送するシステム
 *@author	tomoya takahashi
 *@data		2005.09.02
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __CLACT_UTIL_VRAM_H__
#define __CLACT_UTIL_VRAM_H__

#include "include/system/clact_util_res.h"

#undef GLOBAL
#ifdef	__CLACT_UTIL_VRAM_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------
#define CLACT_U_PLTT_NO_NONE	(NNS_G2D_VRAM_ADDR_NOT_INITIALIZED)

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
// エリアコントロールタイプ
// vramエリアを１キャラごとに管理する配列を作成して、
// 空き領域から使用できるvramエリアを検索します。
//
// 推奨します。
//////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
/**
 *
 *@brief	キャラクタマネジャーにリソースオブジェないのキャラクタデータを設定
 *
 *@param	resObj	リソースオブジェ
 *
 *@return	none
 *
 * CLACT_U_RES_OBJ_PTR	リソースオブジェ
 * CLACT_U_ResManagerResAddChar関数などの戻り値
 * 読み込んだリソースのデータ　管理IDなどが格納されています。
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL CLACT_U_CharManagerSetAreaCont( CONST_CLACT_U_RES_OBJ_PTR resObj );

//----------------------------------------------------------------------------
/**
 *
 *@brief	キャラクタマネジャーにリソースオブジェないのキャラクタデータを設定（複数）
 *
 *@param	resTbl		リソースオブジェ配列のポインタ
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
GLOBAL void CLACT_U_CharManagerSetsAreaCont( const CLACT_U_RES_OBJ_TBL* resTbl );

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
 * NitroSystemの転送関数内で、キャラクタＯＢＪマッピングモードレジスタを変更していて、
 * ２Dマッピングモードでコンバートしたファイルを１Dマッピングモードで読み込みたいなどの
 * 処理がしたくても出来ないようになっているため作成しました。
 *
 * この関数を使用すると、今のマッピングモードを取得し、そのマッピングモードで転送するように
 * キャラクタデータの中身を書き換えるという処理を行って、転送処理をしています。
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL CLACT_U_CharManagerSetCharModeAdjustAreaCont( CONST_CLACT_U_RES_OBJ_PTR resObj );

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
 * NitroSystemの転送関数内で、キャラクタＯＢＪマッピングモードレジスタを変更していて、
 * ２Dマッピングモードでコンバートしたファイルを１Dマッピングモードで読み込みたいなどの
 * 処理がしたくても出来ないようになっているため作成しました。
 *
 * この関数を使用すると、今のマッピングモードを取得し、そのマッピングモードで転送するように
 * キャラクタデータの中身を書き換えるという処理を行って、転送処理をしています。
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_CharManagerSetsCharModeAdjustAreaCont( const CLACT_U_RES_OBJ_TBL* resTbl );


//////////////////////////////////////////////////////////////////////////////
// キャラクタデータ転送関数
// オフセットタイプ
// 上から順に詰めてVramに転送していきます。
// しかし解放などしても解放した領域を認識して、
// その領域に再度違うキャラクタを転送するなどができません。
//
// 基本的には、上のCLACT_U_CharManagerSetAreaCont系関数を使用してください
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
 * CLACT_U_RES_OBJ_PTR	リソースオブジェ
 * CLACT_U_ResManagerResAddChar関数などの戻り値
 * 読み込んだリソースのデータ　管理IDなどが格納されています。
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL CLACT_U_CharManagerSet( CONST_CLACT_U_RES_OBJ_PTR resObj );

//----------------------------------------------------------------------------
/**
 *
 *@brief	キャラクタマネジャーにリソースオブジェないのキャラクタデータを設定（複数）
 *
 *@param	resTbl		リソースオブジェ配列のポインタ
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
GLOBAL void CLACT_U_CharManagerSets( const CLACT_U_RES_OBJ_TBL* resTbl );

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
 * NitroSystemの転送関数内で、キャラクタＯＢＪマッピングモードレジスタを変更していて、
 * ２Dマッピングモードでコンバートしたファイルを１Dマッピングモードで読み込みたいなどの
 * 処理がしたくても出来ないようになっているため作成しました。
 *
 * この関数を使用すると、今のマッピングモードを取得し、そのマッピングモードで転送するように
 * キャラクタデータの中身を書き換えるという処理を行って、転送処理をしています。
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL CLACT_U_CharManagerSetCharModeAdjust(  CONST_CLACT_U_RES_OBJ_PTR resObj );

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
 * NitroSystemの転送関数内で、キャラクタＯＢＪマッピングモードレジスタを変更していて、
 * ２Dマッピングモードでコンバートしたファイルを１Dマッピングモードで読み込みたいなどの
 * 処理がしたくても出来ないようになっているため作成しました。
 *
 * この関数を使用すると、今のマッピングモードを取得し、そのマッピングモードで転送するように
 * キャラクタデータの中身を書き換えるという処理を行って、転送処理をしています。
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_CharManagerSetsCharModeAdjust( const CLACT_U_RES_OBJ_TBL* resTbl );




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
 * nowTblのあるVramにnewTblのキャラクタデータを転送します。
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_CharManagerChg( CONST_CLACT_U_RES_OBJ_PTR nowTbl, CONST_CLACT_U_RES_OBJ_PTR newTbl );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	キャラクタデータの再転送を行う
 *
 *	@param	resObj	リソースオブジェ
 *
 *	@return	none
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_CharManagerReTrans( CONST_CLACT_U_RES_OBJ_PTR resObj );

//----------------------------------------------------------------------------
/**
 *
 *@brief	キャラクタマネジャーからリソースオブジェのIDのキャラクタデータを破棄
 *
 *@param	resObj		リソースオブジェポインタ
 *
 *@return none
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_CharManagerDelete( CLACT_U_RES_OBJ_PTR resObj );

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
GLOBAL void CLACT_U_CharManagerDeletes( CLACT_U_RES_OBJ_TBL* resTbl );
	
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
GLOBAL NNSG2dImageProxy* CLACT_U_CharManagerGetProxy( CONST_CLACT_U_RES_OBJ_PTR resObj );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	２Dマッピングモードのキャラクタを読み込む
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
GLOBAL void CLACT_U_2DmapCharLoad( CONST_CLACT_U_RES_OBJ_PTR resObj, NNSG2dImageProxy* proxy, int base_addr );

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
 *	中でVram領域を確保しています。
 *
 */
//-----------------------------------------------------------------------------
GLOBAL NNSG2dImageProxy* CLACT_U_CharManagerGetVramTransferProxy( CONST_CLACT_U_RES_OBJ_PTR charObj, CONST_CLACT_U_RES_OBJ_PTR cellObj );

//----------------------------------------------------------------------------
/**
 *
 *@brief	セルVram転送アニメのVram領域を開放
 *
 *@param	pImage		Vram転送用に作成されたイメージプロクシ
 *
 *@return	none
 *
 * 中でVram領域を開放しています。
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_CharManagerDeleteVramTransferProxy( const NNSG2dImageProxy* pImage );

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
 * 空いている空間をビット操作で管理しています。
 * 基本こっちを使用してください。
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL CLACT_U_PlttManagerSetCleanArea( CONST_CLACT_U_RES_OBJ_PTR resObj );

//----------------------------------------------------------------------------
/**
 *
 *@brief	パレットマネジャーにリソースオブジェないのパレットデータを設定（複数）
 *
 *@param	resTbl		リソースオブジェテーブルポインタ
 *
 *@return	none
 *
 * 空いている空間をビット操作で管理しています。
 * 基本こっちを使用してください。
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
GLOBAL void CLACT_U_PlttManagerSetsCleanArea( const CLACT_U_RES_OBJ_TBL* resTbl );



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
 * オフセットずらしで先頭からパレットを追加していきます。
 * しかし、パレット使用禁止領域などの管理も行わないため、推奨しません
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL CLACT_U_PlttManagerSet( CONST_CLACT_U_RES_OBJ_PTR resObj );

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
 * オフセットずらしで先頭からパレットを追加していきます。
 * しかし、パレット使用禁止領域などの管理も行わないため、推奨しません
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_PlttManagerSets( const CLACT_U_RES_OBJ_TBL* resTbl );


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
 * nowTblのあるVramにnewTblのパレットデータを転送します。
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_PlttManagerChg( CONST_CLACT_U_RES_OBJ_PTR nowObj, CONST_CLACT_U_RES_OBJ_PTR newObj );

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
GLOBAL void CLACT_U_PlttManagerReTrans( CONST_CLACT_U_RES_OBJ_PTR resObj );

//----------------------------------------------------------------------------
/**
 *
 *@brief	パレットマネジャーからリソースオブジェのIDのパレットデータを破棄
 *
 *@param	resObj		リソースオブジェポインタ
 *
 *@return none
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_PlttManagerDelete( CLACT_U_RES_OBJ_PTR resObj );

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
GLOBAL void CLACT_U_PlttManagerDeletes( CLACT_U_RES_OBJ_TBL* resTbl );
	
//----------------------------------------------------------------------------
/**
 *
 *@brief	パレットプロクシを取得
 *
 *@param	resObj	リソースオブジェパラメータ
 *@param	pImage	関連ずけるイメージプロクシ	拡張パレット以外のときはNULL
 *
 *@return	パレットプロクシ
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL const NNSG2dImagePaletteProxy* CLACT_U_PlttManagerGetProxy( CONST_CLACT_U_RES_OBJ_PTR resObj, NNSG2dImageProxy* pImage );

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
GLOBAL u32 CLACT_U_PlttManagerGetPlttNo( CONST_CLACT_U_RES_OBJ_PTR resObj, NNS_G2D_VRAM_TYPE type );


#undef	GLOBAL
#endif		// CLACT_UTIL_VRAM_H__

