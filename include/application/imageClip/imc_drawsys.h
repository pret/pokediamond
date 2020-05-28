//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_drawsys.h
 *	@brief		イメージクリップ描画システムデータ管理システム
 *				このシステムを使用すれば、すべて描画出来るようにします。
 *	@author		tomoya takahashi
 *	@data		2005.09.21
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __IMC_DRAWSYS_H__
#define __IMC_DRAWSYS_H__

#include <nnsys.h>
#include "include/system/swsprite.h"
#include "include/application/imageClip/imc_drawdata_define.h"
#include "system/softsprite.h"
#include "res_manager.h"
#include "bg_system.h"
#include "clact.h"
#include "include/system/clact_util.h"
#include "include/system/clact_util_res.h"
#include "include/system/clact_util_vram.h"

#undef GLOBAL
#ifdef	__IMC_DRAWSYS_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------
#define	IMC_DRAW_USE_RES_NUM	(4)		// キャラクタ　パレット　セル　セルアニメ

//-------------------------------------
//	
//	キャラクタデータの指定位置に色が
//	paramで無いかチェック
//	戻り値用
//	
//=====================================
enum{
	IMC_DRAW_CHAR_CHECK_FALSE,
	IMC_DRAW_CHAR_CHECK_TRUE,
	IMC_DRAW_CHAR_CHECK_ERR,
};


//-------------------------------------
//	キャラクタデータのスクリーン表示座標
//=====================================


//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	描画データをまとめた構造体
//	
//=====================================
typedef struct {
	// スプライトデータ
	SWSP_SYS_PTR	SWSP_drawSys;		// スプライト描画システム
	SWSP_CHAR_PTR*	SWSP_charData;		// キャラクタデータ配列
	int					SWSP_charNum;		// 登録可能最大数
	int					SWSP_charNow;		// 今の登録数
	SWSP_PLTT_PTR*	SWSP_plttData;		// パレットデータ配列
	int					SWSP_plttNum;		// 登録可能最大数
	int					SWSP_plttNow;		// 今の登録数
	BOOL			SWSP_DrawFlag;			// 描画フラグ

	SOFT_SPRITE_MANAGER* SSM_drawSys;		// ポケモン描画用スプライト
	BOOL SSM_DrawFlag;						// ポケモン描画フラグ

	// アクセサリ用パレットオフセットテーブル
	u8* accePlttOfsTbl;

	// アクセサリ＆ポケモン用アンパック後のキャラクタデータ
	RES_MANAGER_PTR		SWSP_charRes;		// キャラクタデータのリソース	
	NNSG2dCharacterData** SWSP_UPchar;		// アンパック後のデータ
	int					SWSP_UPcharNum;		// アンパック後のデータ数

	// BGデータ
	GF_BGL_INI*		BG_Ini;
	
	// OBJデータ
	CLACT_SET_PTR		clactSet;			// セルアクターセット
	CLACT_U_RES_MANAGER_PTR	resMan[IMC_DRAW_USE_RES_NUM];	// リソースマネージャ
	CLACT_U_EASYRENDER_DATA		renddata;	// 簡易レンダーデータ

} IMC_DRAW_DATA;

//-------------------------------------
//	
//	リソース登録データ
//	
//=====================================
typedef struct {
	// スプライト
	SWSP_CHARDATA* SWSP_charTbl;
	int	SWSP_charNum;
	SWSP_PLTTDATA* SWSP_plttTbl;
	int	SWSP_plttNum;

	// その場で破棄するリソースの格納先
	RES_MANAGER_PTR		SWSP_charRes;		// キャラクタデータのリソース	
	RES_MANAGER_PTR		SWSP_plttRes;		// パレットデータのリソース	
} IMC_DRAW_LOADRES_DATA;


//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	描画システムを描画出来るように環境を設定します
 *
 *	@param	none
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_DRAW_SetUp( void );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	設定した環境データを破棄します
 *
 *	@param	none
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_DRAW_PutBack( void );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	描画用システムの設定を行います。
 *
 *	@param	drawData	描画データ
 *
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_DRAW_InitSys( IMC_DRAW_DATA* drawData );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	描画システムデータを破棄する
 *
 *	@param	drawData	描画データ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_DRAW_DeleteSys( IMC_DRAW_DATA* drawData );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	描画関数のある描画システムの描画
 *
 *	@param	drawData	描画データ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_DRAW_DrawSys( IMC_DRAW_DATA* drawData );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	リソースの読み込みを行います	個々でVram上に展開します
 *
 *	@param	drawData	描画データ格納領域
 *	@param	loadData	読み込むリソースデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_DRAW_LoadResource( IMC_DRAW_DATA* drawData, IMC_DRAW_LOADRES_DATA* loadData );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	リソースの破棄を行います
 *
 *	@param	drawData	描画データ格納領域
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_DRAW_DeleteResource( IMC_DRAW_DATA* drawData );


//----------------------------------------------------------------------------
/**
 *	@brief	アクター登録
 *
 *	@param	drawData	ワーク
 *	@param	contid		管理ID
 *	@param	x			ｘ座標
 *	@param	y			ｙ座標
 *	@param	pri			優先順位
 *	@param	draw_area	描画エリア
 *
 *	@return	アクターワーク
 */
//-----------------------------------------------------------------------------
GLOBAL CLACT_WORK_PTR IMC_DRAW_AddClact( IMC_DRAW_DATA* drawData, int contid, int x, int y, int pri, int draw_area );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	キャラクタデータ読み込み
 *
 *	@param	drawData		描画システムデータ
 *	@param	fileIdx			ファイルインデックス
 *	@param	dataIdx			データインデックス
 *	@param	comp			圧縮フラグ
 *	@param	vramType		Vramタイプ
 *	@param	id				管理ID
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_DRAW_CLACT_LoadCharData( IMC_DRAW_DATA* drawData, int fileIdx, int dataIdx, BOOL comp, int vramType, int id );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	パレットデータ読み込み
 *
 *	@param	drawData		描画システムデータ
 *	@param	fileIdx			ファイルインデックス
 *	@param	dataIdx			データインデックス
 *	@param	comp			圧縮フラグ
 *	@param	vramType		Vramタイプ
 *	@param	load_num		パレット読み込み数
 *	@param	id				管理ID
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_DRAW_CLACT_LoadPlttData( IMC_DRAW_DATA* drawData, int fileIdx, int dataIdx, BOOL comp, int vramType, int load_num, int id );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	セルデータ読み込み
 *
 *	@param	drawData		描画システムデータ
 *	@param	fileIdx			ファイルインデックス
 *	@param	dataIdx			データインデックス
 *	@param	comp			圧縮フラグ
 *	@param	id				管理ID
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_DRAW_CLACT_LoadCellData( IMC_DRAW_DATA* drawData, int fileIdx, int dataIdx, BOOL comp, int id );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	セルアニメデータ読み込み
 *
 *	@param	drawData		描画システムデータ
 *	@param	fileIdx			ファイルインデックス
 *	@param	dataIdx			データインデックス
 *	@param	comp			圧縮フラグ
 *	@param	id				管理ID
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_DRAW_CLACT_LoadCellAnmData( IMC_DRAW_DATA* drawData, int fileIdx, int dataIdx, BOOL comp, int id );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	キャラクタリソースデータのみの破棄
 *
 *	@param	drawData	描画システムデータ
 *	@param	id			管理ID
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_DRAW_CLACT_DeleteCharRes( IMC_DRAW_DATA* drawData, int id );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	パレットリソースデータのみの破棄
 *
 *	@param	drawData	描画システムデータ
 *	@param	id			管理ID
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_DRAW_CLACT_DeletePlttRes( IMC_DRAW_DATA* drawData, int id );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	セルリソースデータのみの破棄
 *
 *	@param	drawData	描画システムデータ
 *	@param	id			管理ID
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_DRAW_CLACT_DeleteCellRes( IMC_DRAW_DATA* drawData, int id );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	セルアニメリソースデータのみの破棄
 *
 *	@param	drawData	描画システムデータ
 *	@param	id			管理ID
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_DRAW_CLACT_DeleteCellAnmRes( IMC_DRAW_DATA* drawData, int id );


//----------------------------------------------------------------------------
/**
 *
 *	@brief	スプライト用の読み込むファイルを作成
 *
 *	@param	drawData	描画システムデータ
 *	@param	loadData	作成先
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_DRAW_MakeLoadSWSP_samp( IMC_DRAW_DATA* drawData, IMC_DRAW_LOADRES_DATA* loadData );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	スプライト用の読み込みファイルを破棄する
 *
 *	@param	loadData	読み込みデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_DRAW_DestLoadSWSP( IMC_DRAW_LOADRES_DATA* loadData );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	キャラクタデータの登録
 *
 *	@param	drawData	描画データ構造体
 *	@param	buff		キャラクタデータバッファ
 *	@param	char_no		登録キャラクタナンバー（アクセサリナンバーとLink）
 *
 *	@return	アンパック後のキャラクタデータ
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL NNSG2dCharacterData* IMC_DRAW_SetCharData( IMC_DRAW_DATA* drawData, void* buff, int char_no );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	通常時のウィンドウマスク設定
 *
 *	@param	none	
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_DRAW_WndMaskNormalSet( void );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	オブジェクトを動かしているときのウィンドウマスクを設定
 *
 *	@param	none	
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_DRAW_WndMaskObjMoveSet( void );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	終了チェック時の表示優先順位設定
 *
 *	@param	none	
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_DRAW_EndCheckBGPri( void );

//-----------------------------------------------------------------------------
/**
*		キャラクタデータを見て、ほんとにその位置に抜き色以外の色になって
*		いるかをチェックする
*/
//----------------------------------------------------------------------------
/**
 *
 *	@brief	キャラクタデータの指定位置に色がparamで無いかチェック
 *
 *	@param	char_data		チェックに使うキャラクタデータ
 *	@param	offs_x			xオフセット
 *	@param	offs_y			yオフセット
 *	@param	param			チェック色ナンバー
 *
 *	@retval	IMC_DRAW_CHAR_CHECK_TRUE	paramの色
 *	@retval	IMC_DRAW_CHAR_CHECK_FALSE	paramの色じゃない
 *	@retval	IMC_DRAW_CHAR_CHECK_ERR		エラー
 *
 * １６色限定
 *
 */
//-----------------------------------------------------------------------------
GLOBAL int IMC_DRAW_CharCheck( NNSG2dCharacterData* char_data, int offs_x, int offs_y, int param );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	描画システム用Vブランク関数
 *
 *	@param	drawData	描画システムデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_DRAW_VBlank( IMC_DRAW_DATA* drawData );

//----------------------------------------------------------------------------
/**
 *	@brief	アクセサリ用ソフトウェアスプライトデータメモリ確保
 *
 *	@param	drawData	読み込みデータワーク	
 *	@param	heap 
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_DRAW_SWSPResDataAllocMemory( IMC_DRAW_LOADRES_DATA* loadData, int heap );

//-----------------------------------------------------------------------------
/**
 *		プレイヤー用関数	
 *			イメージクリップ以外のシステムから使用してもらうときは、こっちの関数で初期化などを行う。
 *			また右パレットの表示に必要な物のみ作成するようになっています。
 */
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *	@brief	イメージクリッププレイヤー用	初期化関数
 *	@param	drawData	描画データ
 *	@param	cp_swsp		イメージクリップ用ソフトウェアスプライトシステム初期化データ
 *	@param	heap		ヒープID
 *
 *	@retval	none
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_DRAW_InitSysPlayer( IMC_DRAW_DATA* drawData, const SWSP_SYSDATA* cp_swsp, int heap );
GLOBAL void IMC_DRAW_InitSysPlayerBG( IMC_DRAW_DATA* drawData, GF_BGL_INI* BG_Ini, int heap );



//----------------------------------------------------------------------------
/**
 *
 *	@brief	描画システムデータを破棄する
 *
 *	@param	drawData	描画データ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_DRAW_DeleteSysPlayer( IMC_DRAW_DATA* drawData );
GLOBAL void IMC_DRAW_DeleteSysPlayerBG( IMC_DRAW_DATA* drawData );


//----------------------------------------------------------------------------
/**
 *
 *	@brief	描画システム用Vブランク関数
 *
 *	@param	drawData	描画システムデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_DRAW_VBlankPlayer( IMC_DRAW_DATA* drawData );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	描画関数のある描画システムの描画
 *
 *	@param	drawData	描画データ
 *	@param	center_x	中心ｘ
 *	@param	center_y	中心ｙ
 *	@param	rota_num	回転角
 *	@param	p_scale		スケールベクトル
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_DRAW_DrawSysPlayer( IMC_DRAW_DATA* drawData, int center_x, int center_y, u16 rota_num, const VecFx32* p_scale );


//-----------------------------------------------------------------------------
/**
 *		previewシステム専用
 */
//-----------------------------------------------------------------------------
// previewシステム
GLOBAL void IMC_DRAW_InitSysPrev( IMC_DRAW_DATA* drawData, int heap );
GLOBAL void IMC_DRAW_DeleteSysPrev( IMC_DRAW_DATA* drawData );
GLOBAL void IMC_DRAW_VBlankPrev( IMC_DRAW_DATA* drawData );
GLOBAL void IMC_DRAW_DrawSysPrev( IMC_DRAW_DATA* drawData );



#undef	GLOBAL
#endif		// __IMC_DRAWSYS_H__

