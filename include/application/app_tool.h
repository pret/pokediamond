//============================================================================================
/**
 * @file	app_tool.h
 * @brief	ツール関連
 * @author	Hiroyuki Nakamura
 * @date	05.09.28
 *
 *	適当に追加して下さい
 */
//============================================================================================
#ifndef APP_TOOL_H
#define APP_TOOL_H
#undef GLOBAL
#ifdef APP_TOOL_H_GLOBAL
#define GLOBAL	/*	*/
#else
#define GLOBAL	extern
#endif


//============================================================================================
//	定数定義
//============================================================================================
// HPカラー
enum {
	HP_DOTTO_NULL = 0,		// HP=0
	HP_DOTTO_RED,			// 赤
	HP_DOTTO_YELLOW,		// 黄
	HP_DOTTO_GREEN,			// 緑
	HP_DOTTO_MAX			// HP=MHP
};

// 輝度変更リクエストID
enum {
	APP_BRIGHT_IN = 0,	// 暗→明
	APP_BRIGHT_OUT		// 明→暗
};

enum {
	APP_WIPE_IN = 0,
	APP_WIPE_OUT,
};

//BMPウィンドウクリアカラー生成マクロ
#define APP_WINCLR_COL(col)	(((col)<<4)|(col))

// 個数選択戻り値
enum {
	APP_NUMSEL_NONE = 0,	// ±０
	APP_NUMSEL_UP,			// ＋
	APP_NUMSEL_DOWN,		// －
};


//==============================================================================
//	外部関数宣言
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   OAMタイプからOAMのデータサイズを取得する
 * @param   oam_type		OAMタイプ
 * @retval  データサイズ(Byte単位)
 */
//--------------------------------------------------------------
GLOBAL int APP_OamTypeToSize(int oam_type);


//--------------------------------------------------------------
/**
 * @brief   直線距離を求めます
 *
 * @param   x		Xの距離
 * @param   y		Yの距離
 *
 * @retval  int		直線距離
 *
 * 座標(0,0)を始点として、(x,y)までの直線距離を計算します
 */
//--------------------------------------------------------------
GLOBAL u32 APP_StraightDistance(u32 x, u32 y);


//--------------------------------------------------------------------------------------------
/**
 * 現在値のゲージドット数を取得
 *
 * @param	prm_now		現在値
 * @param	prm_max		最大値
 * @param	dot_max		最大ドット数
 *
 * @return	ドット数
 */
//--------------------------------------------------------------------------------------------
GLOBAL u8 GetNumDotto( u32 prm_now, u32 prm_max, u8 dot_max );

//--------------------------------------------------------------
/**
 * @brief   表示ドットと最大ドットからHPゲージの色を取得する
 *
 * @param   put_dot		表示ドット数
 * @param   max_dot		最大ドット数
 *
 * @retval  ゲージカラー
 */
//--------------------------------------------------------------
GLOBAL u8 GetGaugeDottoColor(u32 put_dot, u32 max_dot);

//--------------------------------------------------------------------------------------------
/**
 * HPゲージのカラーを取得
 *
 * @param	hp			現在のHP
 * @param	mhp			最大HP
 * @param	max_dot		最大ドット数
 *
 * @return	ドット数
 */
//--------------------------------------------------------------------------------------------
GLOBAL u8 GetHPGaugeDottoColor( u16 hp, u16 mhp, u32 max_dot );


//--------------------------------------------------------------------------------------------
/**
 * 輝度変更リクエスト
 *
 * @param	req		リクエストID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void APP_BrightnessReq( u8 req );

//--------------------------------------------------------------------------------------------
/**
 * ワイプシステムによるフェードリクエスト
 *
 * @param	req			リクエストID
 * @param	heap		ヒープID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void APP_WipeStart( u8 req, u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * 個数変更
 *
 * @param	num		個数
 * @param	max		最大値
 *
 * @retval	"TRUE = 変更した"
 * @retval	"FALSE = 変更してない"
 */
//--------------------------------------------------------------------------------------------
GLOBAL u8 NumSelectCheck( s16 * num, u16 max );

/**
 *	@brief	アーカイブハンドル・ファイルidx等を引数に、
 *			指定フレームのデータをVRAMへ転送する
 *
 *	@param	bgl		初期済みのBGLデータ
 *	@param	heapID	テンポラリ作成に使うヒープハンドル
 *	@param	handel	オープン済みのアーカイブファイルハンドル
 *	@param	arcID	アーカイブファイルID
 *	@param	dataID	アーカイブ内データID
 *	@param	frame	データ転送GF_BGL_FRAME_***指定
 *	@param	mode	0:キャラ,1:スクリーン,2:パレット
 *	@param	size	転送サイズ指定(0を指定した場合、ファイルサイズ分)
 *	@param	ofs		転送オフセット指定
 */
extern void APP_ArcFileVramLoad(GF_BGL_INI* bgl,int heapID,
		ARCHANDLE* handle,int arcID,int fileID,int frame,int mode,u16 trans_siz,u16 ofs);

/**
 *	@brief	オープン済みのアーカイブファイルハンドルを渡して
 *			アーカイブ内のスクリーンデータをUnpackして取得する
 *
 *	@param	handel	オープン済みのアーカイブファイルハンドル
 *	@param	arcID	アーカイブファイルID
 *	@param	dataID	アーカイブ内データID
 *	@param	heapID	メモリ確保するヒープハンドル
 *
 *	@return void*	確保したデータ領域の先頭ポインタ
 *	
 *	＊Unpackするだけなので、解放は自分でやること！
 */
extern void* APP_ArcScrFileUnpack(ARCHANDLE* handle,
	int arcID,int fileID,NNSG2dScreenData** pDat,int heapID);


#undef GLOBAL
#endif	/* APP_TOOL_H */
