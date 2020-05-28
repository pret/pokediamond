//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		fontoam.h
 *	@brief		OAMを使用した文字列描画システム
 *	@author		tomoya takahashi
 *	@data		2005.10.20
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __FONTOAM_H__
#define __FONTOAM_H__

#include <nnsys.h>
#include "clact.h"

#undef GLOBAL
#ifdef	__FONTOAM_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif
//-----------------------------------------------------------------------------
/**
 *
 * OAMフォントシステム説明
 *
 * 基本的な使用方法
 *
 * １：システムワーク（大本）作成
 *		FONTOAM_SYS_PTR FONTOAM_SysInit( int workNum, int heap );
 *
 * ２：貼り付けるビットマップデータ作成
 *
 * ３：OAMフォント作成
 *		FOTNOAM_OBJ_PTR	FONTOAM_Init( const FONTOAM_INIT* fontoam_init );
 *
 * ４：OAMフォントを動かす
 *		FONTOAM_SetMat();などセルアクターにある操作関数の回転、拡大縮小以外は用意されています。
 *
 * ５：OAMフォントの破棄
 *		FONTOAM_Delete( FONTOAM_OBJ_PTR fontoam );
 *
 * ６：OAMフォントシステムワークの破棄
 *		FONTOAM_SysDelete( FONTOAM_SYS_PTR fntoam_sys );
 *
 *
 */
//-----------------------------------------------------------------------------

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
//-------------------------------------
//	
//	1OAMフォントデータ
//	
//=====================================
typedef struct _FONTOAM_OBJ*		FONTOAM_OBJ_PTR;
typedef const struct _FONTOAM_OBJ*	CONST_FONTOAM_OBJ_PTR;

//-------------------------------------
//	
//	システムデータ
//	
//=====================================
typedef struct _FONTOAM_SYSTEM*			FONTOAM_SYS_PTR;
typedef const struct _FONTOAM_SYSTEM*	CONST_FONTOAM_SYS_PTR;


//-------------------------------------
//	
//	フォントデータ登録構造体
//	
//=====================================
typedef struct {
	CONST_FONTOAM_SYS_PTR	fontoam_sys;// フォントシステムデータ
	const GF_BGL_BMPWIN* bmp;			// 貼り付けるビットマップデータ
	CLACT_SET_PTR		clact_set;		// セルアクターセット
	const NNSG2dImagePaletteProxy* pltt;// セル参照先パレットプロクシ
	CONST_CLACT_WORK_PTR	parent;		// 親のアクター		いらないときNULL	（ボタンなど）
	int					char_ofs;		// キャラクタデータ転送オフセット
	int					x;				// 登録ｘ座標		親アクターがあるときは親からのオフセットｙ座標	(dot単位)
	int					y;				// 登録ｙ座標		親アクターがあるときは親からのオフセットｙ座標	(dot単位)
	int					bg_pri;			// bg優先順位
	int					soft_pri;		// ソフト優先順位
	int					draw_area;		// 表示先
	/*
		NNS_G2D_VRAM_TYPE_2DMAIN    ２ＤグラフィックスエンジンＡ用
		NNS_G2D_VRAM_TYPE_2DSUB     ２ＤグラフィックスエンジンＢ用*/
	int					heap;			// 使用するヒープ	
} FONTOAM_INIT;


//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	OAMフォントシステムの作成
 *
 *	@param	workNum		管理する文字列数
 *	@param	heap		使用するヒープ
 *
 *	@return	FONTOAM_SYS_PTR		作成したOAMフォントシステムデータ
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL FONTOAM_SYS_PTR FONTOAM_SysInit( int workNum, int heap );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	OAMフォントシステムの破棄
 *
 *	@param	fntoam_sys	OAMフォントシステムデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void FONTOAM_SysDelete( FONTOAM_SYS_PTR fntoam_sys );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	OAMフォント作成
 *
 *	@param	fontoam_init	OAMフォント作成データ
 *
 *	@return	FONTOAM_OBJ_PTR	OAMフォントデータ
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL FONTOAM_OBJ_PTR FONTOAM_Init( const FONTOAM_INIT* fontoam_init );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	OAMフォント破棄
 *
 *	@param	fontoam 
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void FONTOAM_Delete( FONTOAM_OBJ_PTR fontoam );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ビットマップウィンドウをOAMフォントシステムで表示するために必要なキャラクタデータサイズを取得
 *
 *	@param	bmp		ビットマップデータ
 *	@param	draw_area	描画エリア
 *	@param	heap	使用するヒープ
 *
 *	@return	表示するために必要なキャラクタサイズ
	
	draw_area
		NNS_G2D_VRAM_TYPE_2DMAIN    ２ＤグラフィックスエンジンＡ用
		NNS_G2D_VRAM_TYPE_2DSUB     ２ＤグラフィックスエンジンＢ用
 *	
 *	char_managerを使用しているときは、このサイズ分
 *	先にVram領域を確保しておく必要があるため作成
 *
 */
//-----------------------------------------------------------------------------
GLOBAL int FONTOAM_NeedCharSize( const GF_BGL_BMPWIN* bmp, int draw_area,  int heap );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	OAMフォント座標を設定
 *
 *	@param	fontoam		OAMフォント
 *	@param	x			ｘ座標		親アクターがいるときはオフセット座標
 *	@param	y			ｙ座標		親アクターがいるときはオフセット座標
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void FONTOAM_SetMat( FONTOAM_OBJ_PTR fontoam, int x, int y );

//----------------------------------------------------------------------------
/**
 * ●親セルアクターを設定していない場合は使用しても意味がありません。
 *	
 *	@brief	親アクターの座標位置に位置を合わせる
 *
 *	@param	fontoam 
 *
 *	@return
 *
 * ■親セルアクターの位置を変更したときに呼んでください。
 *	　親に合わせて文字も動きます
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void FONTOAM_ReflectParentMat( FONTOAM_OBJ_PTR fontoam );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	OAMフォント座標を取得
 *
 *	@param	fontoam		OAMフォント
 *	@param	x			ｘ座標		親アクターがいるときはオフセット座標
 *	@param	y			ｙ座標		親アクターがいるときはオフセット座標
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void FONTOAM_GetMat( CONST_FONTOAM_OBJ_PTR fontoam, int* x, int* y );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	表示/非表示設定
 *
 *	@param	fontoam		OAMフォントオブジェ
 *	@param	flag		表示/非表示フラグ
 *
 *	@return	none
 *
 * flag
 *	TRUE	表示
 *	FALSE	非表示
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void FONTOAM_SetDrawFlag( FONTOAM_OBJ_PTR fontoam, BOOL flag );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	表示/非表示を取得
 *
 *	@param	fontoam		OAMフォントオブジェ
 *
 *	@retval	TRUE	表示中
 *	@retval	FALSE	非表示中
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL FONTOAM_GetDrawFlag( CONST_FONTOAM_OBJ_PTR fontoam );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BG面との優先順位を設定
 *
 *	@param	fontoam	OAMフォントデータ
 *	@param	pri		BGとの優先順位
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void FONTOAM_SetBGPriority( FONTOAM_OBJ_PTR fontoam, u8 pri );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BG面との描画優先順位を取得
 *
 *	@param	fontoam		OAMフォントオブジェ
 *
 *	@return	BG面との優先順位
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL int FONTOAM_GetBGPriority( CONST_FONTOAM_OBJ_PTR fontoam );

//-----------------------------------------------------------------------------
/**
 *	@brief	描画優先順位を設定
 *
 *	@param	fontoam		OAMフォントデータ
 *	@param	pri			表示優先順位
 *				
 * 
 *	@return	none
 */
 //----------------------------------------------------------------------------
GLOBAL void FONTOAM_SetDrawPriority( FONTOAM_OBJ_PTR fontoam, u32 pri );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	描画優先順位を取得
 *
 *	@param	fontoam		OAMフォントオブジェ
 *
 *	@return	u32			描画優先順位
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL u32 FONTOAM_GetDrawPriority( CONST_FONTOAM_OBJ_PTR fontoam );

//-----------------------------------------------------------------------------
/**
 * ●OAMがこのパレットナンバーを見るようになります。
 *
 *	@brief				パレットナンバーを変更
 *
 *	@param	fontoam		OAMフォントオブジェ
 *	@param	pltt_no		設定パレットナンバー
 * 
 *	@return	none
 *
 * ■パレットナンバー設定とパレットオフセット設定は同居しません。
 *　　●パレットナンバーを設定するとオフセットの値は反映されなくなります。
 *	　●オフセット値を設定したときはパレットナンバーが反映されなくなります。
 * 
 */
 //----------------------------------------------------------------------------
GLOBAL void FONTOAM_SetPaletteNo( FONTOAM_OBJ_PTR fontoam, u32 pltt_no );
GLOBAL void FONTOAM_SetPaletteNoAddTransPlttNo( FONTOAM_OBJ_PTR fontoam, u32 pltt_no );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	パレットナンバー取得
 *
 *	@param	fontoam		OAMフォントオブジェ
 *
 *	@return	u32			今のパレットナンバー
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL u32 FONTOAM_GetPaletteNo( CONST_FONTOAM_OBJ_PTR fontoam );

//-----------------------------------------------------------------------------
/**
 * ●OAMアトリビュートに設定されているパレットナンバーに加算されます。
 *	 もし、OAMアトリビュートのカラーパレットNoが２でオフセットに２を
 *	 設定すると、４のカラーパレットを参照するようになります
 * 
 *	@brief	パレットオフセットを設定
 *
 *	@param	fontoam		OAMフォントオブジェ
 *	@param	pltt_ofs	パレットオフセット
 * 
 *	@return	none
 *
 * ■パレットナンバー設定とパレットオフセット設定は同居しません。
 *　　●パレットナンバーを設定するとオフセットの値は反映されなくなります。
 *	　●オフセット値を設定したときはパレットナンバーが反映されなくなります。
 * 
 */
 //----------------------------------------------------------------------------
GLOBAL void FONTOAM_SetPaletteOffset( FONTOAM_OBJ_PTR fontoam, u32 pltt_ofs );
GLOBAL void FONTOAM_SetPaletteOffsetAddTransPlttNo( FONTOAM_OBJ_PTR fontoam, u32 pltt_ofs );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	パレットオフセット値取得
 *
 *	@param	fontoam	OAMフォントオブジェ
 *
 *	@return	u32		今のパレットオフセット値
 *
 */
//-----------------------------------------------------------------------------
GLOBAL u32 FONTOAM_GetPaletteOffset( CONST_FONTOAM_OBJ_PTR fontoam );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	モザイク設定
 *
 *	@param	fontoam	OAMフォントオブジェ
 *	@param	flag	フラグ	TRUE＝モザイクON	FALSE＝モザイクOFF
 *
 *	@return	none
 *
 * モザイクOFFの時でも、ニトロキャラクタでモザイクONにしたOAMは
 * モザイクがかかって描画されます。
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void FONTOAM_SetMosaic( FONTOAM_OBJ_PTR fontoam, BOOL flag );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	モザイク設定状態を取得
 *
 *	@param	fontoam	OAMフォントオブジェ
 *
 *	@retval	TRUE	モザイク＝ON
 *	@retval	FALSE	モザイク＝OFF	（ニトロキャラクタで設定してるときは反映される）
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL FONTOAM_GetMosaic( CONST_FONTOAM_OBJ_PTR fontoam );

//----------------------------------------------------------------------------
/**
 *	@brief	オブジェクトモードの設定
 *
 *	@param	fontoam		フォントOAM
 *	@param	objmode		オブジェモード
 *
 *	@return	none
 *
	GX_OAM_MODE_NORMAL		ノーマルOBJ 
	GX_OAM_MODE_XLU			半透明OBJ 
	GX_OAM_MODE_OBJWND		OBJウィンドウ 
	GX_OAM_MODE_BITMAPOBJ	ビットマップOBJ 
 */
//-----------------------------------------------------------------------------
GLOBAL void FONTOAM_ObjModeSet( FONTOAM_OBJ_PTR fontoam, GXOamMode objmode );

//----------------------------------------------------------------------------
/**
 *	@brief	オブジェモードの取得
 *
 *	@param	fontoam		FONTOAM
 *	@param	objmode		オブジェモード
 *
 *	@retval	GX_OAM_MODE_NORMAL		ノーマルOBJ 
 *	@retval	GX_OAM_MODE_XLU			半透明OBJ 
 *	@retval	GX_OAM_MODE_OBJWND		OBJウィンドウ 
 *	@retval	GX_OAM_MODE_BITMAPOBJ	ビットマップOBJ 
 */
//-----------------------------------------------------------------------------
GXOamMode FONTOAM_ObjModeGet( CONST_FONTOAM_OBJ_PTR fontoam, GXOamMode objmode );




//-----------------------------------------------------------------------------
/**
 *		FONTOAM	細か処理分岐バージョン
 */
//-----------------------------------------------------------------------------
typedef struct _FONTOAM_OAM_DATA_SET* FONTOAM_OAM_DATA_PTR;
typedef const struct _FONTOAM_OAM_DATA_SET* CONST_FONTOAM_OAM_DATA_PTR;

//----------------------------------------------------------------------------
/**
 *	@brief	フォントOAM分割データ作成
 *
 *	@param	bmp		データ作成元ビットマップ
 *	@param	heap	ヒープ
 *
 *	@return	分割データ
 */
//-----------------------------------------------------------------------------
GLOBAL FONTOAM_OAM_DATA_PTR FONTOAM_OAMDATA_Make( const GF_BGL_BMPWIN* bmp, int heap );
//----------------------------------------------------------------------------
/**
 *	@brief	フォントOAM分割データの破棄
 *
 *	@param	oamdata	フォントOAM分割データ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
GLOBAL void FONTOAM_OAMDATA_Free( FONTOAM_OAM_DATA_PTR oamdata );
//----------------------------------------------------------------------------
/**
 *	@brief	フォントOAM分割データから転送に必要がキャラクタサイズを取得
 *
 *	@param	oamdata		フォントOAM分割データ
 *	@param	draw_area	描画エリア
 *
 *	@return	必要がキャラクタサイズ
 */
//-----------------------------------------------------------------------------
GLOBAL int FONTOAM_OAMDATA_NeedCharSize( CONST_FONTOAM_OAM_DATA_PTR oamdata, int draw_area );

//----------------------------------------------------------------------------
/**
 *	@brief	フォントOAM分割データを使用してフォントOAMの作成
 *
 *	@param	fontoam_init		ふぉんとOAM 作成データ
 *	@param	oamdata				OAM分割データ
 *
 *	@return	作成されたフォントOAM
 */
//-----------------------------------------------------------------------------
GLOBAL FONTOAM_OBJ_PTR FONTOAM_OAMDATA_Init( const FONTOAM_INIT* fontoam_init, CONST_FONTOAM_OAM_DATA_PTR oamdata );
//----------------------------------------------------------------------------
/**
 *	@brief	OAMフォント破棄
 *
 *	@param	fontoam 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
GLOBAL void FONTOAM_OAMDATA_Delete( FONTOAM_OBJ_PTR fontoam );

//----------------------------------------------------------------------------
/**
 *	@brief	フォントOAMのビットマップデータを変更する
 *
 *	@param	fontoam		変更するFONTOAM
 *	@param	oamdata		OAM分割データ
 *	@param	bmp			ビットマップ 
 *	@param	heap		ヒープ
 *
 *	@return	none
 *
 *	＊注意点
 *		ビットマップの大きさが等しい必要があります。
 */
//-----------------------------------------------------------------------------
GLOBAL void FONTOAM_OAMDATA_ResetBmp( FONTOAM_OBJ_PTR fontoam, CONST_FONTOAM_OAM_DATA_PTR oamdata, const GF_BGL_BMPWIN* bmp, int heap );


//-----------------------------------------------------------------------------
/**
 *		FONTOAMとは無関係ですが、汎用的に使用できる関数
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	BMPのキャラクタデータをOAMのサイズで切り取る
 *
 *	@param	bmp				ビットマップデータ
 *	@param	oam_csx			OAMの横サイズ	（キャラクタ単位）
 *	@param	oam_csy			OAMの縦サイズ	（キャラクタ単位）
 *	@param	bmp_cmx			ビットマップ切り取り左上ｘ座標	（キャラクタ単位）
 *	@param	bmp_cmy			ビットマップ切り取り左上ｙ座標	（キャラクタ単位）
 *	@param	char_buff		出力先キャラクタバッファ (oam_csx * oam_csy)*32byte　サイズ以上の領域
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void FONTOAM_BmpCutOamSize( const GF_BGL_BMPWIN* cp_bmp, int oam_csx, int oam_csy, int bmp_cmx, int bmp_cmy, char* char_buff );



#undef	GLOBAL
#endif		// __FONTOAM_H__

