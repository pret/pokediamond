//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		clact_util.h
 *@brief	セルアクターの登録を簡単に行うシステム
 *@author	tomoya takahashi
 *@data		2005.09.02
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __CLACT_UTIL_H__
#define __CLACT_UTIL_H__

#include "nnsys.h"
#include "clact.h"
#include "include/system/clact_util_res.h"
#include "include/system/clact_util_vram.h"

#undef GLOBAL
#ifdef	__CLACT_UTIL_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------
#define	CLACT_U_HEADER_DATA_NONE	(0xffffffff)	// 主にマルチセルの有無にしよう

//-------------------------------------
//	バイナリデータ特殊コード
//=====================================
// "n"マルチセル、マルチセルアニメが必要ないときに設定
#define CLACT_U_HEADER_MAKE_NONE_CODE	(CLACT_U_HEADER_DATA_NONE)	
// "e"バイナリデータの終了コード
#define CLACT_U_HEADER_MAKE_END_CODE	(0xfffffffe)


// 簡単アクターセット登録用
// サブ画面にセルを出すときは、"SUB_SURFACE_Y"からの座標で
// セルを登録してください。
#define	MAIN_SURFACE_X	(0)					// メインサーフェース左上座標
#define MAIN_SURFACE_Y	(0)					// メインサーフェース左上座標
#define SUB_SURFACE_X	(0)					// サブサーフェース左上座標
#define SUB_SURFACE_Y	(192 << FX32_SHIFT)	// サブサーフェース左上座標
#define SURFACE_WIDTH	(255 << FX32_SHIFT)	// サーフェースサイズ
#define	SURFACE_HEIGHT	(192 << FX32_SHIFT)	// サーフェースサイズ
#define MAIN_SURFACE_Y_INTEGER	(0)
#define SUB_SURFACE_Y_INTEGER	(192)


//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	セルアクターヘッダーテーブル
//	
//=====================================
typedef struct _CLACT_HEADER_TBL{
	CLACT_HEADER_PTR tbl;		// ヘッダー
	int	tbl_num;			// ヘッダーテーブル
} CLACT_HEADER_TBL;

//-------------------------------------
//	
//	セルアクターヘッダーテーブル	
//	
//=====================================
typedef struct _CLACT_HEADER_TBL* CLACT_HEADER_TBL_PTR;


//-------------------------------------
//	
//	セルアクターユーティリティ
//	セルアクターヘッダー作成バイナリデータ
//	格納構造体
//	
//=====================================
typedef struct {
	u32	char_id;				// キャラクタID
	u32 pltt_id;				// パレットID
	u32 cell_id;				// セルID
	u32 cellanime_id;			// セルアニメID
	u32 multicell_id;			// マルチセルID
	u32 multicellanime_id;		// マルチセルアニメID
	u32 vram_trans;				// Vram転送フラグ
	u32 bg_priority;			// BG面との優先順位
} CLACT_U_HEADER_MAKE_BINDATA;


///////////////////////////////////////////////////////////////////////////////
//
//
//	簡単セルアクターセット初期化用構造体
//
//
///////////////////////////////////////////////////////////////////////////////
//-------------------------------------
//	
//	簡単セルアクターセット用レンダラデータ
//	
//=====================================
typedef struct{
	NNSG2dRendererInstance	 Rend;		// レンダラ
	NNSG2dRenderSurface		surface[2];	// サーフェース
} CLACT_U_EASYRENDER_DATA;

//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *@brief	セルアクターヘッダーを作成	（単体）
 *
 *@param	tbl					ヘッダーデータ格納先
 *@param	charID				キャラクタデータID
 *@param	plttID				パレットデータID
 *@param	cellID				セルデータID
 *@param	cellAnmID			セルアニメーションID	"無いときはCLACT_U_HEADER_DATA_NONE"
 *@param	MultiID				マルチセルID		"無いときはCLACT_U_HEADER_DATA_NONE"
 *@param	MultiAnmID			マルチセルアニメID	"無いときはCLACT_U_HEADER_DATA_NONE"
 *@param	vram_trans			Vram転送かフラグ
 *@param	priority			BGとの優先順位
 *@param	charResMan			キャラクタデータが格納されてるリソースマネージャ
 *@param	plttResMan			パレットデータが格納されているリソースマネージャ
 *@param	cellResMan			セルデータが格納されているリソースマネージャ
 *@param	cellAnmResMan		セルアニメデータが格納されているリソースマネージャ	"無いときはNULL"
 *@param	multiCellResMan		マルチセルデータが格納されているリソースマネージャ	"無いときはNULL"
 *@param	multiCellAnmResMan	マルチセルアニメデータが格納されているリソースマネージャ	"無いときはNULL"

 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_MakeHeader(CLACT_HEADER_PTR tbl, int charID, int plttID, int cellID,
		int cellAnmID, int MultiID, int MultiAnmID, int vram_trans, int priority,
		CLACT_U_RES_MANAGER_PTR charResMan,
		CLACT_U_RES_MANAGER_PTR plttResMan,
		CLACT_U_RES_MANAGER_PTR cellResMan,
		CLACT_U_RES_MANAGER_PTR cellAnmResMan,
		CLACT_U_RES_MANAGER_PTR multiCellResMan,
		CLACT_U_RES_MANAGER_PTR multiCellAnmResMan);

//----------------------------------------------------------------------------
/**
 *
 *@brief	ヘッダーのメモリを解放する前に、ヘッダー内のデータで確保したメモリを破棄する
 *
 *@param	tbl		中身のデータを破棄するヘッダー
 *
 *@return	none
 *
 * Vram転送用に確保したVram領域を破棄する
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_DeleteInHeaderVramTransferArea(CLACT_HEADER_PTR tbl);

//----------------------------------------------------------------------------
/**
 *
 *@brief	セルアクターヘッダーテーブルをロムから読み込む	（複数）
 *
 *@param	path				パス
 *@param	heap				ヒープ
 *@param	charResMan			キャラクタデータが格納されてるリソースマネージャ
 *@param	plttResMan			パレットデータが格納されているリソースマネージャ
 *@param	cellResMan			セルデータが格納されているリソースマネージャ
 *@param	cellAnmResMan		セルアニメデータが格納されているリソースマネージャ
 *@param	multiCellResMan		マルチセルデータが格納されているリソースマネージャ
 *@param	multiCellAnmResMan	マルチセルアニメデータが格納されているリソースマネージャ
 *
 *@return	CLACT_HEADER_TBL_PTR	ヘッダーのテーブルを格納した構造体のポインタ
 *									アクセス関数で個々のヘッダーを取得することが出来ます。
 *
 * ヘッダー書式			"（実際は横につなげてください）"
 *	キャラクタID,		（リソースマネージャーと関連付けされたID）
 *	パレットID,
 *	セルID,
 *	セルアニメID,
 *	マルチセルID,		（マルチセル、マルチセルアニメが無いときは'n'）
 *	マルチセルアニメID,
 *	Vram転送アニメ確認フラグ,
 *	BG面との優先度（改行）
 *	次のテーブルを書く↓
 *	0,1,0,2,n,n,0,0			例）こうして並べる
 *	1,2,3,2,0,0,1,2
 *	終了コード
 *	e,e,e,e,e,e,e,e			このデータが出てきたら終了
 *
 */
//-----------------------------------------------------------------------------
GLOBAL CLACT_HEADER_TBL_PTR CLACT_U_LoadHeaderTbl(const char* path, int heap,
		CLACT_U_RES_MANAGER_PTR charResMan,
		CLACT_U_RES_MANAGER_PTR plttResMan,
		CLACT_U_RES_MANAGER_PTR cellResMan,
		CLACT_U_RES_MANAGER_PTR cellAnmResMan,
		CLACT_U_RES_MANAGER_PTR multiCellResMan,
		CLACT_U_RES_MANAGER_PTR multiCellAnmResMan);

//----------------------------------------------------------------------------
/**
 *
 *@brief	セルアクターヘッダーテーブルをバイナリデータから作成	（複数）
 *
 *@param	bindata				バイナリデータ
 *@param	p_header_tbl		ヘッダーテーブル
 *@param	heap				ヒープ
 *@param	charResMan			キャラクタデータが格納されてるリソースマネージャ
 *@param	plttResMan			パレットデータが格納されているリソースマネージャ
 *@param	cellResMan			セルデータが格納されているリソースマネージャ
 *@param	cellAnmResMan		セルアニメデータが格納されているリソースマネージャ
 *@param	multiCellResMan		マルチセルデータが格納されているリソースマネージャ
 *@param	multiCellAnmResMan	マルチセルアニメデータが格納されているリソースマネージャ
 *
 *@return	CLACT_HEADER_TBL_PTR	ヘッダーのテーブルを格納した構造体のポインタ
 *									アクセス関数で個々のヘッダーを取得することが出来ます。
 *
 * バイナリデータ書式		各データ2byteずつの配置となっています。
 *	キャラクタID,		（リソースマネージャーと関連付けされたID）
 *	パレットID,
 *	セルID,
 *	セルアニメID,
 *	マルチセルID,		（マルチセル、マルチセルアニメが無いときは'CLACT_U_HEADER_MAKE_NONE_CODE'）
 *	マルチセルアニメID,
 *	Vram転送アニメ確認フラグ,
 *	BG面との優先度
 *	次のテーブルを書く↓
 *	0x0000,0x0001,0x0000,0x0002,CLACT_U_HEADER_MAKE_NONE_CODE, CLACT_U_HEADER_MAKE_NONE_CODE, 0,0			<-１つのデータ
 *	0x0001,0x0002,0x0003,0x0002,0x0000,0x0000,0x0001,0x0002
 *	終了コード
 *	CLACT_U_HEADER_MAKE_END_CODE, CLACT_U_HEADER_MAKE_END_CODE, CLACT_U_HEADER_MAKE_END_CODE, CLACT_U_HEADER_MAKE_END_CODE, CLACT_U_HEADER_MAKE_END_CODE, CLACT_U_HEADER_MAKE_END_CODE, CLACT_U_HEADER_MAKE_END_CODE, CLACT_U_HEADER_MAKE_END_CODE			このデータが出てきたら終了	
 *
 */
//-----------------------------------------------------------------------------
GLOBAL CLACT_HEADER_TBL_PTR CLACT_U_MakeHeaderBinary(
		const CLACT_U_HEADER_MAKE_BINDATA* bindata,
		int heap,
		CLACT_U_RES_MANAGER_PTR charResMan,
		CLACT_U_RES_MANAGER_PTR plttResMan,
		CLACT_U_RES_MANAGER_PTR cellResMan,
		CLACT_U_RES_MANAGER_PTR cellAnmResMan,
		CLACT_U_RES_MANAGER_PTR multiCellResMan,
		CLACT_U_RES_MANAGER_PTR multiCellAnmResMan);

//----------------------------------------------------------------------------
/**
 *
 *@brief	ヘッダーテーブルを破棄する
 *
 *@param	data	ヘッダーテーブル
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_CLACT_HeaderTblDelete(CLACT_HEADER_TBL_PTR data);


///////////////////////////////////////////////////////////////////////////////
//
//	簡単セルアクターセット初期化関数
//
//
///////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------------------
/**
 *
 *@brief	セルアクターセットの簡単初期化
 *
 *@param	work_num	セルアクターに設定する最大アクター数
 *@param	data		セルアクター簡単設定に使用するレンダーデータ
 *						(実態のポインタ)
 *@param	heap		メモリ確保に使用するヒープ数
 *
 *@return	CLACT_SET_PTR	作成されたセルアクターセット
 *
 * 内容
 * ●レンダラの初期化、サーフェースの設定などを行う
 *		メインサーフェース座標	(0,0)
 *		サブサーフェース座標	(0,192*FX32_ONE)
 *		サーフェースサイズ		(256*FX32_ONE,192*FX32_ONE)
 * ●セルアクターセット作成
 * ●セルアクターセットに初期化したレンダラを設定
 *
 * 破棄は普通のセルアクターの破棄関数で大丈夫です。
 *
 */
//-----------------------------------------------------------------------------
GLOBAL CLACT_SET_PTR CLACT_U_SetEasyInit( int work_num, CLACT_U_EASYRENDER_DATA* data, int heap );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	レンダラー内	メイン画面のサーフェース位置を設定
 *
 *	@param	data	簡単セルアクターセット用レンダラデータ
 *	@param	x		メイン画面サーフェースｘ座標
 *	@param	y		メイン画面サーフェースｙ座標
 *
 *	@return	none
 *
 *		サーフェースのサイズは無条件で(256*FX32_ONE,192*FX32_ONE)
 *		になります。
 *
 *	＊もしサーフェースサイズを変える関数が必要になったときは
 *	takahashi tomoya までよろしくお願いいたします。
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_SetMainSurfaceMatrix( CLACT_U_EASYRENDER_DATA* data, fx32 x, fx32 y );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	レンダラー内	サブ画面のサーフェース位置を設定
 *
 *	@param	data	簡単セルアクターセット用レンダラデータ
 *	@param	x		サブ画面サーフェースｘ座標
 *	@param	y		サブ画面サーフェースｙ座標
 *
 *	@return	none
 *
 *		サーフェースのサイズは無条件で(256*FX32_ONE,192*FX32_ONE)
 *		になります。
 *
 *	＊もしサーフェースサイズを変える関数が必要になったときは
 *	takahashi tomoya までよろしくお願いいたします。
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_SetSubSurfaceMatrix( CLACT_U_EASYRENDER_DATA* data, fx32 x, fx32 y );



//-----------------------------------------------------------------------------
/**
 *
 *		通信アイコンを使用するアプリケーション用
 *		キャラクタマネージャ　パレットマネージャ
 *		使用禁止領域設定関数
 *
 *	@param	disp	設定画面	
 *	@param	mode	オブジェマッピングﾓｰﾄﾞ
 *	disp
 *		main画面：NNS_G2D_VRAM_TYPE_2DMAIN = 1
 *		sub画面 ：NNS_G2D_VRAM_TYPE_2DSUB = 2
 *
 *	mode
 *		GX_OBJVRAMMODE_CHAR_1D_32K 
 *		GX_OBJVRAMMODE_CHAR_1D_64K 
 *		GX_OBJVRAMMODE_CHAR_1D_128K 
 *
 *	■キャラクタマネージャはCharSetAreaCont系関数
 *	  パレットマネージャはPlttSetCleanArea系関数を使用してください。
 *	  
 *	　オフセット移動管理の方には、反映されないようになっています。
 */
//-----------------------------------------------------------------------------
GLOBAL void CLACT_U_WmIcon_SetReserveAreaCharManager( u32 disp, GXOBJVRamModeChar mode );
GLOBAL void CLACT_U_WmIcon_SetReserveAreaPlttManager( u32 disp );



#undef	GLOBAL
#endif		// __CLACT_UTIL_H__
