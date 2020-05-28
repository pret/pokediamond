//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		clact_util_res.h
 *@brief	セルアクターユーティリティシステム
 *@author	tomoya takahashi
 *@data		2005.09.01
 *
 * このシステムは、CLACTを簡単に使用できるようリソースを管理する
 * システムをまとめた物です。
 * 
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#ifndef __CLACT_UTIL_RES_H__
#define __CLACT_UTIL_RES_H__

#include "nnsys.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"

#undef GLOBAL
#ifdef	__CLACT_UTIL_RES_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	リソースタイプ列挙
//	
//=====================================
enum{
	CLACT_U_CHAR_RES,		// キャラクタリソースを管理
	CLACT_U_PLTT_RES,		// パレットリソースを管理
	CLACT_U_CELL_RES,		// セルリソースを管理
	CLACT_U_CELLANM_RES,	// セルアニメリソースを管理
	CLACT_U_MULTI_RES,		// マルチセルリソースを管理
	CLACT_U_MULTIANM_RES,	// マルチセルアニメリソースを管理
	CLACT_U_RES_MAX			// 最大
};

//-------------------------------------
//	バイナリデータ特殊コード
//=====================================
// "e"バイナリデータの終了コード
#define CLACT_U_RES_HEADER_MAKE_END_CODE	(0xfffffffe)

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	リソースマネージャー管理構造体
//	
//=====================================
typedef struct _CLACT_U_RES_MANAGER* CLACT_U_RES_MANAGER_PTR;
typedef const struct _CLACT_U_RES_MANAGER* CONST_CLACT_U_RES_MANAGER_PTR;

//-------------------------------------
//	
//	リソースマネージャーオブジェクト構造体
//	
//=====================================
typedef struct _CLACT_U_RES_OBJ* CLACT_U_RES_OBJ_PTR;
typedef const struct _CLACT_U_RES_OBJ* CONST_CLACT_U_RES_OBJ_PTR;

//-------------------------------------
//	
//	リソースマネージャオブジェテーブル
//	構造体
//
//	ヘッダーから一気に複数の
//	リソースを読み込む時の引数に使用
//
//	読み込んだリソースのオブジェを保存する
//	
//=====================================
typedef struct {
	CLACT_U_RES_OBJ_PTR*	tbl;// ポインタを格納するテーブルのポインタ
	int		tbl_num;			// テーブル要素数
	int		tbl_now;			// 現在格納数
} CLACT_U_RES_OBJ_TBL;


//-------------------------------------
//	
//	リソースマネージャーヘッダー構造体
//	
//=====================================
typedef struct _CLACT_U_RES_HEADER* CLACT_U_RES_HEADER_PTR;
typedef const struct _CLACT_U_RES_HEADER* CONST_CLACT_U_RES_HEADER_PTR;

//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *@brief	リソース管理マネージャー初期化
 *
 *@param	tbl_num			データ登録数
 *@param	res_type		リソースタイプ
 *@param	heap			使用するヒープ
 *
 *@return	CLACT_RES_MANAGER_PTR	セルアクターユーティリティリソースマネージャーポインタ
 *
 * リソースタイプ
	enum{
		CLACT_U_CHAR_RES,		// キャラクタリソースを管理
		CLACT_U_PLTT_RES,		// パレットリソースを管理
		CLACT_U_CELL_RES,		// セルリソースを管理
		CLACT_U_CELLANM_RES,	// セルアニメリソースを管理
		CLACT_U_MULTI_RES,		// マルチセルリソースを管理
		CLACT_U_MULTIANM_RES,	// マルチセルアニメリソースを管理
		CLACT_U_RES_MAX			// 最大
	};
 *
 */
//-----------------------------------------------------------------------------
GLOBAL CLACT_U_RES_MANAGER_PTR CLACT_U_ResManagerInit(int tbl_num, int res_type, int heap);

//----------------------------------------------------------------------------
/**
 *
 *@brief	リソースマネージャーの破棄
 *
 *@param	resm	リソースマネージャー
 *	
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_ResManagerDelete(CLACT_U_RES_MANAGER_PTR resm);



//----------------------------------------------------------------------------
/**
 *
 *@brief	キャラクタデータの登録
 *
 *@param	resm			キャラクタ用に作成したリソースマネージャー
 *@param	path			ファイルパス
 *@param	id				管理ＩＤ		（重複しないようにユーザーが設定）
 *@param	vram			Ｖｒａｍタイプ
 *@param	heap			使用ヒープ
 *
 *@return	CLACT_U_RES_OBJ_PTR	リソースオブジェポインタ
 *
 * Vramタイプ
	mainに登録：NNS_G2D_VRAM_TYPE_2DMAIN
	subに登録 ：NNS_G2D_VRAM_TYPE_2DSUB
	両方に登録：NNS_G2D_VRAM_TYPE_2DMAX
 */
//-----------------------------------------------------------------------------
GLOBAL CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerResAddChar(CLACT_U_RES_MANAGER_PTR resm, const char* path, int id, int vram, int heap);

//----------------------------------------------------------------------------
/**
 *
 *@brief	パレットデータの登録
 *
 *@param	resm			パレット用に作成したリソースマネージャー
 *@param	path			ファイルパス
 *@param	id				管理ＩＤ		（重複しないようにユーザーが設定）
 *@param	vram			Ｖｒａｍタイプ
 *@param	pltt_num		パレット読み込み本数
 *@param	heap			使用ヒープ
 *
 *@return	CLACT_U_RES_OBJ_PTR	リソースオブジェポインタ
 *
 *
 * Vramタイプ
	mainに登録：NNS_G2D_VRAM_TYPE_2DMAIN
	subに登録 ：NNS_G2D_VRAM_TYPE_2DSUB
	両方に登録：NNS_G2D_VRAM_TYPE_2DMAX
 */
//-----------------------------------------------------------------------------
GLOBAL CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerResAddPltt(CLACT_U_RES_MANAGER_PTR resm, const char* path, int id, int vram, int pltt_num, int heap);

//----------------------------------------------------------------------------
/**
 *
 *@brief	セル、セルアニメ、マルチセル、マルチセルアニメデータの登録
 *
 *@param	resm			パレット用に作成したリソースマネージャー
 *@param	path			ファイルパス
 *@param	id				管理ＩＤ		（重複しないようにユーザーが設定）
 *@param	type			リソースタイプ
 *@param	heap			使用ヒープ
 * 
 *@return	CLACT_U_RES_OBJ_PTR	リソースオブジェポインタ
 *
 * リソースタイプ
	enum{
		CLACT_U_CHAR_RES,		// キャラクタリソースを管理
		CLACT_U_PLTT_RES,		// パレットリソースを管理
		CLACT_U_CELL_RES,		// セルリソースを管理
		CLACT_U_CELLANM_RES,	// セルアニメリソースを管理
		CLACT_U_MULTI_RES,		// マルチセルリソースを管理
		CLACT_U_MULTIANM_RES,	// マルチセルアニメリソースを管理
		CLACT_U_RES_MAX			// 最大
	};
 *
 */
//-----------------------------------------------------------------------------
GLOBAL CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerResAddKindCell(CLACT_U_RES_MANAGER_PTR resm, const char* path, int id, int type,  int heap);

//----------------------------------------------------------------------------
/**
 *
 *@brief	アーカイブされたキャラクタデータの登録
 *
 *@param	resm			キャラクタ用に作成したリソースマネージャー
 *@param	arcFile			アーカイブファイルID
 *@param	detaIdx			データインデックス
 *@param	compFlag		圧縮されているか	(TRUE 圧縮  　　FALSE 非圧縮)
 *@param	id				管理ＩＤ		（重複しないようにユーザーが設定）
 *@param	vram			Ｖｒａｍタイプ
 *@param	heap			使用ヒープ
 *
 *@return	CLACT_U_RES_OBJ_PTR	リソースオブジェポインタ
 *
 * Vramタイプ
	mainに登録：NNS_G2D_VRAM_TYPE_2DMAIN
	subに登録 ：NNS_G2D_VRAM_TYPE_2DSUB
	両方に登録：NNS_G2D_VRAM_TYPE_2DMAX
 *
 */
//-----------------------------------------------------------------------------
GLOBAL CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerResAddArcChar(CLACT_U_RES_MANAGER_PTR resm, int arcFile, int dataIdx, BOOL compFlag, int id, int vram, int heap);
GLOBAL CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerResAddArcChar_AllocType(CLACT_U_RES_MANAGER_PTR resm, int arcFile, int dataIdx, BOOL compFlag, int id, int vram, int heap, ALLOC_TYPE alloc_type );

//----------------------------------------------------------------------------
/**
 *
 *@brief	パレットデータの登録
 *
 *@param	resm			パレット用に作成したリソースマネージャー
 *@param	arcFile			アーカイブファイルID
 *@param	detaIdx			データインデックス
 *@param	compFlag		圧縮されているか	(TRUE 圧縮  　　FALSE 非圧縮)
 *@param	id				管理ＩＤ		（重複しないようにユーザーが設定）
 *@param	vram			Ｖｒａｍタイプ
 *@param	pltt_num		パレット読み込み本数
 *@param	heap			使用ヒープ
 *
 *@return	CLACT_U_RES_OBJ_PTR	リソースオブジェポインタ
 *
 * Vramタイプ
	mainに登録：NNS_G2D_VRAM_TYPE_2DMAIN
	subに登録 ：NNS_G2D_VRAM_TYPE_2DSUB
	両方に登録：NNS_G2D_VRAM_TYPE_2DMAX
 *
 */
//-----------------------------------------------------------------------------
GLOBAL CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerResAddArcPltt(CLACT_U_RES_MANAGER_PTR resm, int arcFile, int dataIdx, BOOL compFlag, int id, int vram, int pltt_num, int heap);
GLOBAL CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerResAddArcPltt_AllocType(CLACT_U_RES_MANAGER_PTR resm, int arcFile, int dataIdx, BOOL compFlag, int id, int vram, int pltt_num, int heap, ALLOC_TYPE alloc_type );

//----------------------------------------------------------------------------
/**
 *
 *@brief	セル、セルアニメ、マルチセル、マルチセルアニメデータの登録
 *
 *@param	resm			パレット用に作成したリソースマネージャー
 *@param	arcFile			アーカイブファイルID
 *@param	detaIdx			データインデックス
 *@param	compFlag		圧縮されているか	(TRUE 圧縮  　　FALSE 非圧縮)
 *@param	id				管理ＩＤ		（重複しないようにユーザーが設定）
 *@param	type			リソースタイプ
 *@param	heap			使用ヒープ
 *
 *@return	CLACT_U_RES_OBJ_PTR	リソースオブジェポインタ
 *
 * リソースタイプ
	enum{
		CLACT_U_CHAR_RES,		// キャラクタリソースを管理
		CLACT_U_PLTT_RES,		// パレットリソースを管理
		CLACT_U_CELL_RES,		// セルリソースを管理
		CLACT_U_CELLANM_RES,	// セルアニメリソースを管理
		CLACT_U_MULTI_RES,		// マルチセルリソースを管理
		CLACT_U_MULTIANM_RES,	// マルチセルアニメリソースを管理
		CLACT_U_RES_MAX			// 最大
	};
 *
 */
//-----------------------------------------------------------------------------
GLOBAL CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerResAddArcKindCell(CLACT_U_RES_MANAGER_PTR resm, int arcFile, int dataIdx, BOOL compFlag, int id, int type, int heap);

//----------------------------------------------------------------------------
/**
 *
 *@brief	アーカイブされたキャラクタデータのリソース変更
 *
 *@param	resm			キャラクタ用リソースマネージャポインタ
 *@param	resObj			変更するリソースオブジェ
 *@param	arcFile			アーカイブファイルID
 *@param	detaIdx			データインデックス
 *@param	compFlag		圧縮されているか	(TRUE 圧縮  　　FALSE 非圧縮)
 *@param	heap			使用ヒープ
 *
 * @return none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_ResManagerResChgArcChar(CLACT_U_RES_MANAGER_PTR resm, CLACT_U_RES_OBJ_PTR resObj, int arcFile, int dataIdx, BOOL compFlag, int heap);


//----------------------------------------------------------------------------
/**
 *
 *@brief	パレットデータのリソースを変更
 *
 *@param	resm			パレット用リソースマネージャポインタ
 *@param	resObj			変更するリソースオブジェ
 *@param	arcFile			アーカイブファイルID
 *@param	detaIdx			データインデックス
 *@param	compFlag		圧縮されているか	(TRUE 圧縮  　　FALSE 非圧縮)
 *@param	heap			使用するヒープ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_ResManagerResChgArcPltt(CLACT_U_RES_MANAGER_PTR resm, CLACT_U_RES_OBJ_PTR resObj, int arcFile, int dataIdx, BOOL compFlag, int heap);

//----------------------------------------------------------------------------
/**
 *
 *@brief	セル、セルアニメ、マルチセル、マルチセルアニメデータのリソースを変更
 *
 *@param	resm			変更するリソース用リソースマネージャポインタ
 *@param	resObj			変更するリソースオブジェ
 *@param	arcFile			アーカイブファイルID
 *@param	detaIdx			データインデックス
 *@param	compFlag		圧縮されているか	(TRUE 圧縮  　　FALSE 非圧縮)
 *@param	type			リソースタイプ
 *@param	heap			使用するヒープ
 *
 *@return	none
 *
 * リソースタイプ
	enum{
		CLACT_U_CHAR_RES,		// キャラクタリソースを管理
		CLACT_U_PLTT_RES,		// パレットリソースを管理
		CLACT_U_CELL_RES,		// セルリソースを管理
		CLACT_U_CELLANM_RES,	// セルアニメリソースを管理
		CLACT_U_MULTI_RES,		// マルチセルリソースを管理
		CLACT_U_MULTIANM_RES,	// マルチセルアニメリソースを管理
		CLACT_U_RES_MAX			// 最大
	};
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_ResManagerResChgArcKindCell(CLACT_U_RES_MANAGER_PTR resm, CLACT_U_RES_OBJ_PTR resObj, int arcFile, int dataIdx, BOOL compFlag, int type, int heap);

//----------------------------------------------------------------------------
/**
 * ■アーカイブハンドル方式
 *
 *@brief	アーカイブされたキャラクタデータの登録
 *
 *@param	resm			キャラクタ用に作成したリソースマネージャー
 *@param	arcHandle		アーカイブファイルハンドル
 *@param	detaIdx			データインデックス
 *@param	compFlag		圧縮されているか	(TRUE 圧縮  　　FALSE 非圧縮)
 *@param	id				管理ＩＤ		（重複しないようにユーザーが設定）
 *@param	vram			Ｖｒａｍタイプ
 *@param	heap			使用ヒープ
 *
 *@return	CLACT_U_RES_OBJ_PTR	リソースオブジェポインタ
 *
 * Vramタイプ
	mainに登録：NNS_G2D_VRAM_TYPE_2DMAIN
	subに登録 ：NNS_G2D_VRAM_TYPE_2DSUB
	両方に登録：NNS_G2D_VRAM_TYPE_2DMAX
 *
 */
//-----------------------------------------------------------------------------
GLOBAL CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerResAddArcChar_ArcHandle(CLACT_U_RES_MANAGER_PTR resm, ARCHANDLE* arcHandle, int dataIdx, BOOL compFlag, int id, int vram, int heap);
GLOBAL CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerResAddArcChar_ArcHandle_AllocType(CLACT_U_RES_MANAGER_PTR resm, ARCHANDLE* arcHandle, int dataIdx, BOOL compFlag, int id, int vram, int heap, ALLOC_TYPE alloc_type);

//----------------------------------------------------------------------------
/**
 * ■アーカイブハンドル方式
 *
 *@brief	パレットデータの登録
 *
 *@param	resm			パレット用に作成したリソースマネージャー
 *@param	arcHandle		アーカイブファイルハンドル
 *@param	detaIdx			データインデックス
 *@param	compFlag		圧縮されているか	(TRUE 圧縮  　　FALSE 非圧縮)
 *@param	id				管理ＩＤ		（重複しないようにユーザーが設定）
 *@param	vram			Ｖｒａｍタイプ
 *@param	pltt_num		パレット読み込み本数
 *@param	heap			使用ヒープ
 *
 *@return	CLACT_U_RES_OBJ_PTR	リソースオブジェポインタ
 *
 * Vramタイプ
	mainに登録：NNS_G2D_VRAM_TYPE_2DMAIN
	subに登録 ：NNS_G2D_VRAM_TYPE_2DSUB
	両方に登録：NNS_G2D_VRAM_TYPE_2DMAX
 *
 */
//-----------------------------------------------------------------------------
GLOBAL CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerResAddArcPltt_ArcHandle(CLACT_U_RES_MANAGER_PTR resm, ARCHANDLE* arcHandle, int dataIdx, BOOL compFlag, int id, int vram, int pltt_num, int heap);
GLOBAL CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerResAddArcPltt_ArcHandle_AllocType(CLACT_U_RES_MANAGER_PTR resm, ARCHANDLE* arcHandle, int dataIdx, BOOL compFlag, int id, int vram, int pltt_num, int heap, ALLOC_TYPE alloc_type);

//----------------------------------------------------------------------------
/**
 * ■アーカイブハンドル方式
 *
 *@brief	セル、セルアニメ、マルチセル、マルチセルアニメデータの登録
 *
 *@param	resm			パレット用に作成したリソースマネージャー
 *@param	arcHandle		アーカイブファイルハンドル
 *@param	detaIdx			データインデックス
 *@param	compFlag		圧縮されているか	(TRUE 圧縮  　　FALSE 非圧縮)
 *@param	id				管理ＩＤ		（重複しないようにユーザーが設定）
 *@param	type			リソースタイプ
 *@param	heap			使用ヒープ
 *
 *@return	CLACT_U_RES_OBJ_PTR	リソースオブジェポインタ
 *
 * リソースタイプ
	enum{
		CLACT_U_CHAR_RES,		// キャラクタリソースを管理
		CLACT_U_PLTT_RES,		// パレットリソースを管理
		CLACT_U_CELL_RES,		// セルリソースを管理
		CLACT_U_CELLANM_RES,	// セルアニメリソースを管理
		CLACT_U_MULTI_RES,		// マルチセルリソースを管理
		CLACT_U_MULTIANM_RES,	// マルチセルアニメリソースを管理
		CLACT_U_RES_MAX			// 最大
	};
 *
 */
//-----------------------------------------------------------------------------
GLOBAL CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerResAddArcKindCell_ArcHandle(CLACT_U_RES_MANAGER_PTR resm, ARCHANDLE* arcHandle, int dataIdx, BOOL compFlag, int id, int type, int heap);

//----------------------------------------------------------------------------
/**
 * ■アーカイブハンドル方式
 *
 *@brief	アーカイブされたキャラクタデータのリソース変更
 *
 *@param	resm			キャラクタ用リソースマネージャポインタ
 *@param	resObj			変更するリソースオブジェ
 *@param	arcHandle		アーカイブファイルハンドル
 *@param	detaIdx			データインデックス
 *@param	compFlag		圧縮されているか	(TRUE 圧縮  　　FALSE 非圧縮)
 *@param	heap			使用ヒープ
 *
 * @return none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_ResManagerResChgArcChar_ArcHandle(CLACT_U_RES_MANAGER_PTR resm, CLACT_U_RES_OBJ_PTR resObj, ARCHANDLE* arcHandle, int dataIdx, BOOL compFlag, int heap);


//----------------------------------------------------------------------------
/**
 * ■アーカイブハンドル方式
 *
 *@brief	パレットデータのリソースを変更
 *
 *@param	resm			パレット用リソースマネージャポインタ
 *@param	resObj			変更するリソースオブジェ
 *@param	arcHandle		アーカイブファイルハンドル
 *@param	detaIdx			データインデックス
 *@param	compFlag		圧縮されているか	(TRUE 圧縮  　　FALSE 非圧縮)
 *@param	heap			使用するヒープ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_ResManagerResChgArcPltt_ArcHandle(CLACT_U_RES_MANAGER_PTR resm, CLACT_U_RES_OBJ_PTR resObj, ARCHANDLE* arcHandle, int dataIdx, BOOL compFlag, int heap);

//----------------------------------------------------------------------------
/**
 * ■アーカイブハンドル方式
 *
 *@brief	セル、セルアニメ、マルチセル、マルチセルアニメデータのリソースを変更
 *
 *@param	resm			変更するリソース用リソースマネージャポインタ
 *@param	resObj			変更するリソースオブジェ
 *@param	arcHandle		アーカイブファイルハンドル
 *@param	detaIdx			データインデックス
 *@param	compFlag		圧縮されているか	(TRUE 圧縮  　　FALSE 非圧縮)
 *@param	type			リソースタイプ
 *@param	heap			使用するヒープ
 *
 *@return	none
 *
 * リソースタイプ
	enum{
		CLACT_U_CHAR_RES,		// キャラクタリソースを管理
		CLACT_U_PLTT_RES,		// パレットリソースを管理
		CLACT_U_CELL_RES,		// セルリソースを管理
		CLACT_U_CELLANM_RES,	// セルアニメリソースを管理
		CLACT_U_MULTI_RES,		// マルチセルリソースを管理
		CLACT_U_MULTIANM_RES,	// マルチセルアニメリソースを管理
		CLACT_U_RES_MAX			// 最大
	};
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_ResManagerResChgArcKindCell_ArcHandle(CLACT_U_RES_MANAGER_PTR resm, CLACT_U_RES_OBJ_PTR resObj, ARCHANDLE* arcHandle, int dataIdx, BOOL compFlag, int type, int heap);


//----------------------------------------------------------------------------
/**
 *
 *@brief	リソースデータをヘッダーから読み込む（単発）
 *
 *@param	resm	リソースマネージャー
 *@param	head	読み込んだヘッダー
 *@param	no		ヘッダーの何番目を読み込むか
 *@param	heap	使用するヒープ
 *
 *@return	読み込んだデータ
 *
 * ヘッダ書式
 *	ヘッダファイルは、"ファイルタイプ部"と"データ部"に分かれます。
 *	"ファイルタイプ部の次の行からデータ部としてデータを記入します。"
 *	また終了字には,'e'を引数数分つなげた物が"終了コード"となります。
 *	"e,e,e,e"	<-引数数分
 *	
 *	
 *	"●"ファイルタイプ部
 *	"リソースタイプ , アーカイブデータフラグ(0:非アーカイブ	1:アーカイブ)"
 *	
 *	"●"データ部
 *	データ部はリソースタイプより変化します。
 *	・リソースタイプが0=	"キャラクタ"
 *	・アーカイブフラグが0=	"非アーカイブ"
 *	"ファイルパス,管理ID,Vramタイプ(1=MAIN 2=SUB 3=両方)"
 *	"ファイルパス,管理ID,Vramタイプ"
 *	"e,e,e"
 *	・アーカイブフラグが1=	"アーカイブ"
 *	"アーカイブファイルidx,アーカイブデータidx,圧縮フラグ(0=非圧縮 1=圧縮),管理ID,Vramタイプ"
 *	"アーカイブファイルidx,アーカイブデータidx,圧縮フラグ,管理ID,Vramタイプ"
 *	"e,e,e,e,e"
 *
 *	・リソースタイプが1=	"パレット"
 *	・アーカイブフラグが0=	"非アーカイブ"
 *	"ファイルパス,管理ID,Vramタイプ,パレット読み込み数"
 *	"ファイルパス,管理ID,Vramタイプ,パレット読み込み数"
 *	"e,e,e,e"
 *	・アーカイブフラグが1=	"アーカイブ"
 *	"アーカイブファイルidx,アーカイブデータidx,圧縮フラグ,管理ID,Vramタイプ,パレット読み込み数"
 *	"アーカイブファイルidx,アーカイブデータidx,圧縮フラグ,管理ID,Vramタイプ,パレット読み込み数"
 *	"e,e,e,e,e,e"
 *	
 *	・リソースタイプが2=	"セル"
 *	・アーカイブフラグが0=	"非アーカイブ"
 *	"ファイルパス,管理ID"
 *	"ファイルパス,管理ID"
 *	"e,e,e,e"
 *	・アーカイブフラグが1=	"アーカイブ"
 *	"アーカイブファイルidx,アーカイブデータidx,圧縮フラグ,管理ID"
 *	"アーカイブファイルidx,アーカイブデータidx,圧縮フラグ,管理ID"
 *	"e,e,e,e"
 *
 *	・リソースタイプが3=	"セルアニメ"
 *	・アーカイブフラグが0=	"非アーカイブ"
 *	"ファイルパス,管理ID"
 *	"ファイルパス,管理ID"
 *	"e,e,e,e"
 *	・アーカイブフラグが1=	"アーカイブ"
 *	"アーカイブファイルidx,アーカイブデータidx,圧縮フラグ,管理ID"
 *	"アーカイブファイルidx,アーカイブデータidx,圧縮フラグ,管理ID"
 *	"e,e,e,e"
 *
 *	・リソースタイプが4=	"マルチセル"
 *	・アーカイブフラグが0=	"非アーカイブ"
 *	"ファイルパス,管理ID"
 *	"ファイルパス,管理ID"
 *	"e,e,e,e"
 *	・アーカイブフラグが1=	"アーカイブ"
 *	"アーカイブファイルidx,アーカイブデータidx,圧縮フラグ,管理ID"
 *	"アーカイブファイルidx,アーカイブデータidx,圧縮フラグ,管理ID"
 *	"e,e,e,e"
 *
 *	・リソースタイプが5=	"マルチセルアニメ"
 *	・アーカイブフラグが0=	"非アーカイブ"
 *	"ファイルパス,管理ID"
 *	"ファイルパス,管理ID"
 *	"e,e,e,e"
 *	・アーカイブフラグが1=	"アーカイブ"
 *	"アーカイブファイルidx,アーカイブデータidx,圧縮フラグ,管理ID"
 *	"アーカイブファイルidx,アーカイブデータidx,圧縮フラグ,管理ID"
 *	"e,e,e,e"
 *
 */
//-----------------------------------------------------------------------------
GLOBAL CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerResAddHd(CLACT_U_RES_MANAGER_PTR resm, const CLACT_U_RES_HEADER_PTR head, int no, int heap);

//----------------------------------------------------------------------------
/**
 *
 *@brief	リソースデータをヘッダーから読み込む(複数)
 *
 *@param	resm		リソースマネージャーポインタ
 *@param	head		ヘッダー
 *@param	p_ro_tbl	メモリ確保済みリソースオブジェテーブル
 *@param	heap		使用するヒープ
 *
 *@return	int			登録数
 *
 * CLACT_U_RES_OBJ_TBL*の説明
	typedef struct {
		CLACT_U_RES_OBJ_PTR*	tbl;// ポインタを格納するテーブルのポインタ
		int		tbl_num;			// テーブル要素数
		int		tbl_now;			// 現在格納数
	} CLACT_U_RES_OBJ_TBL;
	上の構造体を下の関数で作成できます。
	GLOBAL CLACT_U_RES_OBJ_TBL* CLACT_U_ResManagerResObjTblMake(int inResObjNum, int heap);
	作成してから渡してください。
	読み込んだりソースのオブジェクトポインタ	CLACT_U_RES_OBJ_PTR	を保存します。
 *
 */
//-----------------------------------------------------------------------------
GLOBAL int CLACT_U_ResManagerResAddsHd(CLACT_U_RES_MANAGER_PTR resm, const CLACT_U_RES_HEADER_PTR head, CLACT_U_RES_OBJ_TBL* p_ro_tbl, int heap );

//----------------------------------------------------------------------------
/**
 *
 *@brief	リソースデータをヘッダーから読み込む(読み込む数を指定)
 *
 *@param	resm		リソースマネージャーポインタ
 *@param	head		ヘッダー
 *@param	start		読み込み開始テーブルナンバー
 *@param	num			読み込み数
 *@param	p_ro_tbl	メモリ確保済みリソースオブジェテーブル
 *@param	heap		使用するヒープ
 *
 *@return	none
 *
 * ヘッダ内のstartからnum分を読み込みます
 * 
 * 
 * CLACT_U_RES_OBJ_TBL*の説明
	typedef struct {
		CLACT_U_RES_OBJ_PTR*	tbl;// ポインタを格納するテーブルのポインタ
		int		tbl_num;			// テーブル要素数
		int		tbl_now;			// 現在格納数
	} CLACT_U_RES_OBJ_TBL;
	上の構造体を下の関数で作成できます。
	GLOBAL CLACT_U_RES_OBJ_TBL* CLACT_U_ResManagerResObjTblMake(int inResObjNum, int heap);
	作成してから渡してください。
	読み込んだりソースのオブジェクトポインタ	CLACT_U_RES_OBJ_PTR	を保存します。
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_ResManagerResAddsHdEx(CLACT_U_RES_MANAGER_PTR resm, const CLACT_U_RES_HEADER_PTR head, int start, int num, CLACT_U_RES_OBJ_TBL* p_ro_tbl,int heap);

//----------------------------------------------------------------------------
/**
 *
 *@brief	リソースオブジェ格納用テーブルを作成
 *			このテーブルを使用し、リソースデータの複数読み込みにも対応する
 *
 *@param	inResObjNum		中に登録するデータ数
 *@param	heap			メモリ確保ヒープ
 *
 *@return	CLACT_U_RES_OBJ_TBL*	作成データ
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL CLACT_U_RES_OBJ_TBL* CLACT_U_ResManagerResObjTblMake(int inResObjNum, int heap);

//----------------------------------------------------------------------------
/**
 *
 *@brief	リソースオブジェ格納用テーブル破棄
 *
 *
 *@param	data		破棄するリソースオブジェテーブル
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_ResManagerResObjTblDelete(CLACT_U_RES_OBJ_TBL* data);

//----------------------------------------------------------------------------
/**
 *
 *@brief	残り登録可能数取得
 *
 *@param	resm		リソースマネージャーポインタ
 *
 *@return	int		残り登録可能数
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL int CLACT_U_ResManagerRest(CLACT_U_RES_MANAGER_PTR resm);

//----------------------------------------------------------------------------
/**
 *
 *@brief	IDのデータがあるかチェック
 *
 *@param	resm	リソースマネージャ
 *@param	id		チェックするID
 *
 *@retval	TRUE	IDのデータが無い
 *@retval	FALSE	IDのデータがある
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL CLACT_U_ResManagerCheckID(CONST_CLACT_U_RES_MANAGER_PTR resm, int id);

//----------------------------------------------------------------------------
/**
 *
 *	@brief	リソースオブジェ内の読み込んできたデータのみ破棄
 *			IDやリソースタイプなどの情報は保持したまま
 *
 *	@param	res_obj		リソースオブジェ
 *
 *	@return	none
 *
 * この関数を呼ぶとVramへのリソースの転送などが行えなくなります。
 * 
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_ResManagerResOnlyDelete( CLACT_U_RES_OBJ_PTR res_obj );

//----------------------------------------------------------------------------
/**
 *
 *@brief	リソース全データ破棄
 *
 *@param	resm		セルアクターユーティリティリソースマネージャーポインタ
 *@param	res_obj		リソースオブジェ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_ResManagerResDelete(CLACT_U_RES_MANAGER_PTR resm, CLACT_U_RES_OBJ_PTR res_obj);

//----------------------------------------------------------------------------
/**
 *
 *@brief	リソース全破棄
 *
 *@param	resm		セルアクターユーティリティリソースマネージャーポインタ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_ResManagerResDeleteAll(CLACT_U_RES_MANAGER_PTR resm);

//----------------------------------------------------------------------------
/**
 *
 *@brief	IDのリソースを取得
 *
 *@param	id		取得するリソースオブジェポインタに設定されている管理ＩＤ
 *	
 *@return	CLACT_U_RES_OBJ_PTR		リソースオブジェポインタ
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL CLACT_U_RES_OBJ_PTR CLACT_U_ResManagerGetIDResObjPtr(CONST_CLACT_U_RES_MANAGER_PTR resm, int id);

//----------------------------------------------------------------------------
/**
 *
 *@brief	リソースオブジェからＩＤを取得
 *
 *@param	resObj	リソースオブジェ
 *	
 *@return	int		管理ＩＤ
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL int CLACT_U_ResManagerGetResObjID(CONST_CLACT_U_RES_OBJ_PTR resObj);

//----------------------------------------------------------------------------
/**
 *
 *@brief	リソースオブジェにＩＤを設定
 *
 *@param	resm	変更するオブジェの登録されているリソースマネージャ
 *@param	resObj	リソースオブジェ
 *@param	id		設定するID
 *	
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_ResManagerSetResObjID(CLACT_U_RES_MANAGER_PTR resm, CLACT_U_RES_OBJ_PTR resObj, int id);

//----------------------------------------------------------------------------
/**
 *
 *@brief	リソースオブジェのリソースを取得
 *
 *@param	resObj	リソースオブジェ
 *	
 *@return	void*	リソースポインタ
 *
 * このポインタの中身をもうアンパックしているため、アンパック禁止です。
 * アンパック済みファイルを取得する関数を用意しているため、
 * そちらを使用してください。
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void* CLACT_U_ResManagerGetResObjRes(CONST_CLACT_U_RES_OBJ_PTR resObj);

//----------------------------------------------------------------------------
/**
 *
 *@brief	キャラクタデータを取得	リソースデータをアンパックしてから取得
 *
 *@param	resObj	キャラクタリソースオブジェ
 *
 *@return	キャラクタリソースデータ
 *
 */
//-----------------------------------------------------------------------------
GLOBAL NNSG2dCharacterData* CLACT_U_ResManagerGetResObjResChar(CONST_CLACT_U_RES_OBJ_PTR resObj);
//----------------------------------------------------------------------------
/**
 *
 *@brief	パレットデータを取得	リソースデータをアンパックしてから取得
 *
 *@param	resObj	パレットリソースオブジェ
 *
 *@return	パレットリソースデータ
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL NNSG2dPaletteData* CLACT_U_ResManagerGetResObjResPltt(CONST_CLACT_U_RES_OBJ_PTR resObj);
//----------------------------------------------------------------------------
/**
 *
 *@brief	セルデータを取得	リソースデータをアンパックしてから取得
 *
 *@param	resObj	セルリソースオブジェ
 *
 *@return	セルリソースデータ
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL NNSG2dCellDataBank* CLACT_U_ResManagerGetResObjResCell(CONST_CLACT_U_RES_OBJ_PTR resObj);
//----------------------------------------------------------------------------
/**
 *
 *@brief	セルアニメデータを取得	リソースデータをアンパックしてから取得
 *
 *@param	resObj	セルアニメリソースオブジェ
 *
 *@return	セルアニメリソースデータ
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL NNSG2dCellAnimBankData* CLACT_U_ResManagerGetResObjResCellAnm(CONST_CLACT_U_RES_OBJ_PTR resObj);
//----------------------------------------------------------------------------
/**
 *
 *@brief	マルチセルデータを取得	リソースデータをアンパックしてから取得
 *
 *@param	resObj	マルチセルリソースオブジェ
 *
 *@return	マルチセルリソースデータ
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL NNSG2dMultiCellDataBank* CLACT_U_ResManagerGetResObjResMultiCell(CONST_CLACT_U_RES_OBJ_PTR resObj);
//----------------------------------------------------------------------------
/**
 *
 *@brief	マルチセルアニメデータを取得	リソースデータをアンパックしてから取得
 *
 *@param	resObj	マルチセルアニメリソースオブジェ
 *
 *@return	マルチセルアニメリソースデータ
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL NNSG2dMultiCellAnimBankData* CLACT_U_ResManagerGetResObjResMultiCellAnim(CONST_CLACT_U_RES_OBJ_PTR resObj);

//----------------------------------------------------------------------------
/**
 *
 *@brief	リソースオブジェに設定されているリソースのタイプを取得
 *
 *@param	resObj	リソースオブジェ
 *	
 *@return	int		リソースタイプ
 *
 *
 * リソースタイプ
	enum{
		CLACT_U_CHAR_RES,		// キャラクタリソースを管理
		CLACT_U_PLTT_RES,		// パレットリソースを管理
		CLACT_U_CELL_RES,		// セルリソースを管理
		CLACT_U_CELLANM_RES,	// セルアニメリソースを管理
		CLACT_U_MULTI_RES,		// マルチセルリソースを管理
		CLACT_U_MULTIANM_RES,	// マルチセルアニメリソースを管理
		CLACT_U_RES_MAX			// 最大
	};
 *
 */
//-----------------------------------------------------------------------------
GLOBAL int CLACT_U_ResManagerGetResObjResType(CONST_CLACT_U_RES_OBJ_PTR resObj);

//----------------------------------------------------------------------------
/**
 *
 *@brief	リソースオブジェに設定されているVramタイプを取得
 *
 *@param	resObj	リソースオブジェ
 *	
 *@return	int		Vramタイプ（キャラクタ。パレット時のみ）
 *
 * Vramタイプ
	mainに登録：NNS_G2D_VRAM_TYPE_2DMAIN
	subに登録 ：NNS_G2D_VRAM_TYPE_2DSUB
	両方に登録：NNS_G2D_VRAM_TYPE_2DMAX
 *
 */
//-----------------------------------------------------------------------------
GLOBAL int CLACT_U_ResManagerGetResObjVramType(CONST_CLACT_U_RES_OBJ_PTR resObj);

//----------------------------------------------------------------------------
/**
 *
 *@brief	リソースオブジェに設定されているパレット読み込み数を取得
 *
 *@param	resObj	リソースオブジェ
 *	
 *@return	int		パレット読み込み本数（パレット時のみ）
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL int CLACT_U_ResManagerGetResObjPlttNum(CONST_CLACT_U_RES_OBJ_PTR resObj);

//----------------------------------------------------------------------------
/**
 *
 *@brief	リソースオブジェにVramタイプを設定
 *
 *@param	resobj	リソースオブジェ
 *@param	vram	vramタイプ	メイン:1	サブ:2	両方:3
 *	
 *@return	none
 *
 * Vramタイプ
	mainに登録：NNS_G2D_VRAM_TYPE_2DMAIN
	subに登録 ：NNS_G2D_VRAM_TYPE_2DSUB
	両方に登録：NNS_G2D_VRAM_TYPE_2DMAX
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_ResManagerSetResObjVramType(CLACT_U_RES_OBJ_PTR resObj, int vram);

//----------------------------------------------------------------------------
/**
 *
 *@brief	リソースオブジェに設定されているパレット読み込み数を設定
 *
 *@param	resObj	リソースオブジェ
 *@param	pltt	パレット読み込み本数
 *	
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_ResManagerSetResObjPlttNum(CLACT_U_RES_OBJ_PTR resObj, int pltt);


//-----------------------------------------------------------------------------
//
//
//			ヘッダーシステム
//
//
//=============================================================================
//----------------------------------------------------------------------------
/**
 *
 *@brief	ヘッダーサイズを取得
 *
 *@param	none
 *
 *@return	int		サイズ
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL int CLACT_U_ResManagerGetHeaderSize(void);

//----------------------------------------------------------------------------
/**
 *
 *@brief	リソースヘッダーを配列で確保したときの各要素数のデータを
 *			取得する関数
 *
 *@param	head	ヘッダーデータ（配列）
 *@param	no		要素数
 *
 *@return	CLACT_U_RES_HEADER_PTR
 *
 * noが配列の要素数より大きい時、不当なポインタを返してしまいます。
 *
 */
//-----------------------------------------------------------------------------
GLOBAL CLACT_U_RES_HEADER_PTR CLACT_U_ResManagerGetHeaderNoData(CLACT_U_RES_HEADER_PTR head, int no);

//----------------------------------------------------------------------------
/**
 *
 *@brief	セルアクターユーティリティリソースマネージャヘッダー読み込み
 *
 *@param	path		ヘッダーファイルパス
 *@param	head		ヘッダー格納先
 *@param	type		リソースタイプ
 *@param	heap		使用するヒープ
 *
 *@return	none
 *
 * ヘッダ書式
 *	ヘッダファイルは、"ファイルタイプ部"と"データ部"に分かれます。
 *	"ファイルタイプ部の次の行からデータ部としてデータを記入します。"
 *	また終了字には,'e'を4個つなげた物が"終了コード"となります。
 *	"e,e,e,e"
 *	
 *	"●"ファイルタイプ部
 *	"リソースタイプ , アーカイブデータフラグ(0:非アーカイブ	1:アーカイブ)"
 *	
 *	"●"データ部
 *	データ部はリソースタイプより変化します。
 *	・リソースタイプが0=	"キャラクタ"
 *	"ファイルパス,管理ID,Vramタイプ(1=MAIN 2=SUB 3=両方)"
 *	"ファイルパス,管理ID,Vramタイプ"
 *	"e,e,e,e"
 *
 *	・リソースタイプが1=	"パレット"
 *	"ファイルパス,管理ID,Vramタイプ,パレット読み込み数"
 *	"ファイルパス,管理ID,Vramタイプ,パレット読み込み数"
 *	"e,e,e,e"
 *	
 *	・リソースタイプが2=	"セル"
 *	"ファイルパス,管理ID"
 *	"ファイルパス,管理ID"
 *	"e,e,e,e"
 *
 *	・リソースタイプが3=	"セルアニメ"
 *	"ファイルパス,管理ID"
 *	"ファイルパス,管理ID"
 *	"e,e,e,e"
 *
 *	・リソースタイプが4=	"マルチセル"
 *	"ファイルパス,管理ID"
 *	"ファイルパス,管理ID"
 *	"e,e,e,e"
 *
 *	・リソースタイプが5=	"マルチセルアニメ"
 *	"ファイルパス,管理ID"
 *	"ファイルパス,管理ID"
 *	"e,e,e,e"
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_ResManagerHeaderLoad(const char* path, CLACT_U_RES_HEADER_PTR head,int heap);


//----------------------------------------------------------------------------
/**
 *
 *@brief	セルアクターユーティリティリソースマネージャバイナリヘッダー読み込み
 *
 *@param	cp_bindata		バイナリデータ
 *@param	head			ヘッダー格納先
 *@param	heap			使用するヒープ
 *
 *@return	none
 *
 * Binaryデータ書式		全データ4byte区切り
 *	リソースタイプ				(0～5)
 *	アーカイブファイルidx		(arc_tool.datに定義されている物)
 *	データidx					(naixに定義されている物)
 *	圧縮フラグ					(圧縮1	非圧縮0)
 *	管理ID						
 *	＊▲Vramタイプ				(1=MAIN 2=SUB 3=両方)
 *	  ▲パレット読み込み本数	(1～16)
 *
 * ＊キャラクタリソースの時		(その他の時はダミーデータ = 何でもOK)
 * ▲パレットリソースの時		(その他の時はダミーデータ = 何でもOK)
 *
 * 例）
 *		リソースタイプ	
 *		0x00000001		
 *		アーカイブidx	データidx		圧縮フラグ
 *		0x00000000		0x00000000		0x00000000
 *		管理ID			vramタイプ		パレット読み込み本数
 *		0x00000000		0x00000002		0x00000001
 *		アーカイブidx	データidx		圧縮フラグ
 *		0x00000000		0x00000001		0x00000000
 *		管理ID			vramタイプ		パレット読み込み本数
 *		0x00000001		0x00000002		0x00000001
 *		<終了コード>
 *		アーカイブidx	データidx		圧縮フラグ
 *		0xfffffffe		0xfffffffe		0xfffffffe		
 *		管理ID			vramタイプ		パレット読み込み本数
 *		0xfffffffe		0xfffffffe		0xfffffffe		
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_ResManagerHeaderLoadBinary(const void* cp_bindata, CLACT_U_RES_HEADER_PTR head,int heap);

//----------------------------------------------------------------------------
/**
 *
 *@brief	リソースマネージャヘッダー破棄
 *
 *@param	head		ヘッダーポインタ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_ResManagerHeaderFree(CLACT_U_RES_HEADER_PTR head);

//----------------------------------------------------------------------------
/**
 *
 *@brief	リソースマネージャーヘッダーに読み込まれているデータ数取得
 *
 *@param	head		リソースヘッダ
 *
 *@return	int		読み込まれているデータ数
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL int CLACT_U_ResManagerHeaderSetDataNum(CONST_CLACT_U_RES_HEADER_PTR head);

//----------------------------------------------------------------------------
/**
 *
 *@brief	リソースマネージャーヘッダーに読み込まれているデータのリソースタイプを取得
 *
 *@param	head		リソースヘッダ
 *
 *@return	int		リソースタイプ
 *
 * リソースタイプ
	enum{
		CLACT_U_CHAR_RES,		// キャラクタリソースを管理
		CLACT_U_PLTT_RES,		// パレットリソースを管理
		CLACT_U_CELL_RES,		// セルリソースを管理
		CLACT_U_CELLANM_RES,	// セルアニメリソースを管理
		CLACT_U_MULTI_RES,		// マルチセルリソースを管理
		CLACT_U_MULTIANM_RES,	// マルチセルアニメリソースを管理
		CLACT_U_RES_MAX			// 最大
	};
 *
 */
//-----------------------------------------------------------------------------
GLOBAL int CLACT_U_ResManagerHeaderSetDataResType(CONST_CLACT_U_RES_HEADER_PTR head);

//----------------------------------------------------------------------------
/**
 *
 *@brief	リソースマネージャーヘッダーに読み込まれているデータはアーカイブされているか
 *
 *@param	head		リソースヘッダ
 *
 *@return	int			0：されてない	1：されてる
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL int CLACT_U_ResManagerHeaderSetDataArc(CONST_CLACT_U_RES_HEADER_PTR head);

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ヘッダに登録されているデータを変更する 関数郡
 *
 *	@param	head		リソースヘッダー
 *	@param	no			リソースヘッダー内に登録されているデータナンバー
 *	@param	param		設定する値
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_ResManagerHeaderDataIDSet( CLACT_U_RES_HEADER_PTR head, int no, int param );
GLOBAL void CLACT_U_ResManagerHeaderArcFileSet( CLACT_U_RES_HEADER_PTR head, int no, int param );
GLOBAL void CLACT_U_ResManagerHeaderDataIdxSet( CLACT_U_RES_HEADER_PTR head, int no, int param );
GLOBAL void CLACT_U_ResManagerHeaderCompFlagSet( CLACT_U_RES_HEADER_PTR head, int no, int param );
GLOBAL void CLACT_U_ResManagerHeaderVramTypeSet( CLACT_U_RES_HEADER_PTR head, int no, int param );
GLOBAL void CLACT_U_ResManagerHeaderPlttNumSet( CLACT_U_RES_HEADER_PTR head, int no, int param );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ヘッダに登録されているデータを取得する	関数郡
 *
 *	@param	head		リソースヘッダー
 *	@param	no			リソースヘッダー内に登録されているデータナンバー
 *
 *	@return	データ
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL int CLACT_U_ResManagerHeaderDataIDGet( CONST_CLACT_U_RES_HEADER_PTR head, int no );
GLOBAL int CLACT_U_ResManagerHeaderArcFileGet( CONST_CLACT_U_RES_HEADER_PTR head, int no );
GLOBAL int CLACT_U_ResManagerHeaderDataIdxGet( CONST_CLACT_U_RES_HEADER_PTR head, int no );
GLOBAL int CLACT_U_ResManagerHeaderCompFlagGet( CONST_CLACT_U_RES_HEADER_PTR head, int no );
GLOBAL int CLACT_U_ResManagerHeaderVramTypeGet( CONST_CLACT_U_RES_HEADER_PTR head, int no );
GLOBAL int CLACT_U_ResManagerHeaderPlttNumGet( CONST_CLACT_U_RES_HEADER_PTR head, int no );

#undef	GLOBAL
#endif		// __CLACT_UTIL_RES_H__

