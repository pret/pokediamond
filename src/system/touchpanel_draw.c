//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		touchpanel_draw.c
 *@brief	タッチパネル情報の描画
 *@author	tomoya takahashi
 *@data		2005.03.29
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "common.h"
#define __TOUCHPANEL_DRAW_H_GLOBAL
#include "touchpanel_draw.h"

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

//----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
 */
//-----------------------------------------------------------------------------
//-------------------------------------
// タッチパネル情報描画用
static void drawPoint(GF_BGL_INI* bgl, u16 x, u16 y, TP_BRUSH_DATA brush_data );					// 点の描画
static void drawLine(GF_BGL_INI* bgl, u16 x1, u16 y1, u16 x2, u16 y2, TP_BRUSH_DATA brush_data );	// ラインを引く
static void drawLineInOut(GF_BGL_INI* bgl, u16 x1, u16 y1, u16 x2, u16 y2,
		TP_BRUSH_DATA in_brush_data, TP_BRUSH_DATA out_brush_data,
		TP_PICTURE_DATA* pData );	// ライン上の内外判定を行いラインを引く
static u32 getOffset( u16 x, u16 y, u16* p_shift, u32 char_width );				// キャラクタデータオフセットを求める	

// デバック用ベクトルデータ描画
static void drawVect(GF_BGL_INI* bgl, Vec2DS32* p_point1, Vec2DS32* p_point2 );

//----------------------------------------------------------------------------
/**
 *					グローバル変数宣言
 */
//-----------------------------------------------------------------------------
static GF_BGL_BMPWIN*	TouchPanelDrawDataIdx;	// バンプデータのインデックス
static TPData	TouchPanelOld;			// 一つ前の描画情報
static u8		TouchPanelDrawInit=0;	// 描画システム初期化したかのフラグ


//
/// タッチペン情報の描画用関数
//
//----------------------------------------------------------------------------
/**
 *
 * @brief	タッチペンの描画情報とビットマップの作成
 *
 * @param	gf_bgl_frame：bg_systemの描画BGのナンバー
 * @param	width ：描画幅
 * @param	height：描画高さ
 * @param	x	  ：描画開始点横
 * @param	y	  ：描画開始点たて
 * @param	p_pltt：使用するパレットデータ
 * @param	heap	使用するヒープ
 *
 * @return	none
 */
 //----------------------------------------------------------------------------
void DrawTPInit(GF_BGL_INI* bgl, int gf_bgl_frame, u32 width, u32 height, u32 x, u32 y, const u16* p_pltt, int heap)
{
	//
	// タッチペン描画用のビットマップを作成してパレットをロードする
	//
	// Controlを作成
	GF_BGL_BGCNT_HEADER		bg =		// BGの設定
	{
		0,0,
//		GF_BGL_SCRSIZ_256_256,			// 描画範囲分(32*32分)
		0x800,			// 描画範囲分(32*32分)
		0,
		GX_BG_SCRSIZE_TEXT_256x256,
		GX_BG_COLORMODE_16,
		GX_BG_SCRBASE_0x0000,
		GX_BG_CHARBASE_0x04000,
		GX_BG_EXTPLTT_01,
		0,
		0,
		0,
		FALSE
	};

	
	// 初期化
	TouchPanelDrawInit = 1;
	
	//
	// コンロールセットをセット＆キャラクタを作成
	//
	GF_BGL_BGControlSet(bgl, gf_bgl_frame, &bg, GF_BGL_MODE_TEXT );
	
	TouchPanelDrawDataIdx = GF_BGL_BmpWinAllocGet(heap, 1);
	GF_BGL_BmpWinAdd(bgl, TouchPanelDrawDataIdx,
			gf_bgl_frame, x, y,
			width, height, 0, TP_WIN_CGX - (width * height) );
	
	// パレットロード
	DrawTPChgPltt( gf_bgl_frame, p_pltt );

	// 各種データセット
	TouchPanelOld.touch = 0;


	
	// 画面をクリア
	DrawTPClean(bgl, 0 );
	GF_BGL_BmpWinOn(TouchPanelDrawDataIdx );					// 描画
}

//----------------------------------------------------------------------------
/**
 *
 * @brief	パレットを変える
 * 
 * @param	gf_bgl_frame：bg_systemの描画BGのナンバー
 * @param	p_pltt：使用するパレットデータ
 *
 * @return	none
 */
 //----------------------------------------------------------------------------
void DrawTPChgPltt( int gf_bgl_frame, const u16* p_pltt )
{
	// パレットロード
	if( gf_bgl_frame < GF_BGL_FRAME0_S ){
		GX_LoadBGPltt( (const void *)p_pltt, 0, sizeof(u16)*16 );
	}
	else{
		GXS_LoadBGPltt( (const void *)p_pltt, 0, sizeof(u16)*16 );
	}
}

//----------------------------------------------------------------------------
/**
 *
 * @brief	タッチパネル描画システムの破棄
 * 
 * @param	pltt：パレットナンバー
 *
 * @return	none
 */
 //----------------------------------------------------------------------------
void DrawTPDelete(GF_BGL_INI* bgl, u16 pltt )
{
	// 初期化されているかチェック
	SDK_ASSERTMSG( TouchPanelDrawInit != 0,
			"warning:TouchPanelDrawSystem初期化されていません\n" );

	DrawTPClean(bgl, pltt );
	DrawTPPaste(bgl);
	GF_BGL_BmpWinDel( TouchPanelDrawDataIdx );
	sys_FreeMemoryEz(TouchPanelDrawDataIdx);
	
	// 初期化
	TouchPanelDrawInit = 0;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	実際に画面に描画
 *
 *@param	none
 * 
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
void DrawTPPaste( GF_BGL_INI* bgl )
{
	// 初期化されているかチェック
	SDK_ASSERTMSG( TouchPanelDrawInit != 0,
			"warning:TouchPanelDrawSystem初期化されていません\n" );
	
	//
	// 実際に画面に描画する
	//
	GF_BGL_BmpWinCgxOn(TouchPanelDrawDataIdx );
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	タッチパネル情報を描画
 *
 *@param	pBuff：タッチパネル情報バッファ
 *@param	size：バッファサイズ
 *@param	brush_data：使用するブラシデータ
 *@param	check_num：タッチパネル情報がこれ以上離れていたら新しく線を描く値
 * 
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
void DrawTP(GF_BGL_INI* bgl, TPData* pBuff, u32 size, TP_BRUSH_DATA brush_data, u16 check_num )
{
	int i;			// ループ用
	
	for( i = 0; i < size; i++ )
	{
		DrawTPLine(bgl, pBuff[ i ], brush_data, check_num );		// 線を書く
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	内外判定をしてタッチパネル情報を描画
 *
 *@param	pBuff：タッチパネル情報バッファ
 *@param	size：バッファサイズ
 *@param	in_brush_data：領域内のとき使用するブラシデータ
 *@param	out_brush_data：領域外のとき使用するブラシデータ
 *@param	check_num：タッチパネル情報がこれ以上離れていたら新しく線を描く値
 *@param	pData：絵のデータ
 * 
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
void DrawTPInOut(GF_BGL_INI* bgl, TPData* pBuff, u32 size, TP_BRUSH_DATA in_brush_data, TP_BRUSH_DATA out_brush_data,
						 u16 check_num, TP_PICTURE_DATA* pData )
{
	int i;			// ループ用

	
	for( i = 0; i < size; i++ )
	{
		DrawTPLineInOut(bgl, pBuff[ i ], in_brush_data, out_brush_data, check_num, pData );		// 線を書く
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	タッチパネル情報を描画
 *@brief	syncの値分描画して行きます
 *
 *@param	pBuff：タッチパネル情報バッファ
 *@param	size：バッファサイズ
 *@param	brush_data：使用するブラシデータ
 *@param	check_num：タッチパネル情報がこれ以上離れていたら新しく線を描く値
 *@param	sync：オートサンプリングの１フレームにサンプリングする値
 *@param	p_count：使用するカウンタ(グローバル)
 * 
 *@retval	０：続行　
 *@retval	１：終了
 *
 */
//-----------------------------------------------------------------------------
u32 DrawTPSync(GF_BGL_INI* bgl, TPData* pBuff, u32 size, TP_BRUSH_DATA brush_data, u16 check_num, u16 sync, u32* p_count )
{
	int i;			// ループ用
	int num;		// 終わりの数
	u32 ret = 0;	// 戻り値

	// ループの終わりの数をセット
	num = *p_count + sync;
	if( num > size ){
		num = size;
		ret = 1;
	}
	
	for( i = *p_count; i < num; i++ ){
		DrawTPLine(bgl, pBuff[ i ], brush_data, check_num );		// 線を書く
	}

	*p_count = i;

	return ret;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	タッチパネル情報を描画（点を描画）
 *
 *@param	Buff：タッチパネル情報バッファ
 *@param	brush_data：使用するブラシデータ
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
void DrawTPPoint(GF_BGL_INI* bgl, TPData Buff, TP_BRUSH_DATA brush_data )
{	
	// 初期化されているかチェック
	SDK_ASSERTMSG( TouchPanelDrawInit != 0,
			"warning:TouchPanelDrawSystem初期化されていません\n" );
	
	//
	// initで取得したバンプデータのキャラクタデータに点を書く
	//
	if( (Buff.touch == TP_TOUCH_ON) &&
		(Buff.validity == TP_VALIDITY_VALID) ){
		drawPoint(bgl, Buff.x, Buff.y, brush_data );		// 点を書く
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	タッチパネル情報を描画（線にする）
 *
 *@param	Buff：タッチパネル情報バッファ
 *@param	brush_data：使用するブラシデータ
 *@param	check_num：新しく書き始めるときの１つ前との最大差
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
void DrawTPLine(GF_BGL_INI* bgl, TPData Buff, TP_BRUSH_DATA brush_data, u16 check_num )
{	
	// 初期化されているかチェック
	SDK_ASSERTMSG( TouchPanelDrawInit != 0,
			"warning:TouchPanelDrawSystem初期化されていません\n" );
	
	// 一つ前がタッチしたいなければ新しく書き始める
	if( TouchPanelOld.touch == TP_TOUCH_OFF ){
		TouchPanelOld = Buff;
	}else{
		// あまりにも１つ前の値との差があるときは新しく書き始める
		if( (((TouchPanelOld.x - Buff.x) > check_num) ||
			((TouchPanelOld.y - Buff.y) > check_num)) ||
			(((TouchPanelOld.x - Buff.x) < -check_num) ||
			((TouchPanelOld.y - Buff.y) < -check_num)))
		{
			TouchPanelOld = Buff;
		}
	}
	
	// タッチしていたら描画
	if( (Buff.touch == TP_TOUCH_ON) &&
		(Buff.validity == TP_VALIDITY_VALID) ){
		//
		// initで取得したバンプデータのキャラクタデータに点を書く
		//
		drawLine(bgl, TouchPanelOld.x, TouchPanelOld.y, Buff.x, Buff.y, brush_data );		// 点を書く

		// データをセット
		TouchPanelOld = Buff;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	タッチパネル情報を描画（線にする）内外判定を行って描画
 *
 *@param	Buff：タッチパネル情報バッファ
 *@param	in_brush_data：領域内のとき使用するブラシデータ
 *@param	out_brush_data：領域外のとき使用するブラシデータ
 *@param	check_num：タッチパネル情報がこれ以上離れていたら新しく線を描く値
 *@param	pData：絵のデータ
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
void DrawTPLineInOut(GF_BGL_INI* bgl, TPData Buff, TP_BRUSH_DATA in_brush_data, TP_BRUSH_DATA out_brush_data,
					  u16 check_num, TP_PICTURE_DATA* pData )
{	
	// 初期化されているかチェック
	SDK_ASSERTMSG( TouchPanelDrawInit != 0,
			"warning:TouchPanelDrawSystem初期化されていません\n" );
	
	// 一つ前がタッチしたいなければ新しく書き始める
	if( TouchPanelOld.touch == TP_TOUCH_OFF ){
		TouchPanelOld = Buff;
	}else{
		// あまりにも１つ前の値との差があるときは新しく書き始める
		if( (((TouchPanelOld.x - Buff.x) > check_num) ||
			((TouchPanelOld.y - Buff.y) > check_num)) ||
			(((TouchPanelOld.x - Buff.x) < -check_num) ||
			((TouchPanelOld.y - Buff.y) < -check_num)))
		{
			TouchPanelOld = Buff;
		}
	}
	
	// タッチしていたら描画
	if( (Buff.touch == TP_TOUCH_ON) &&
		(Buff.validity == TP_VALIDITY_VALID) ){
		//
		// initで取得したバンプデータのキャラクタデータに点を書く
		//
		drawLineInOut(bgl, TouchPanelOld.x, TouchPanelOld.y, Buff.x, Buff.y, in_brush_data, out_brush_data, pData );		// 点を書く

		// データをセット
		TouchPanelOld = Buff;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	バンプをクリーンする
 *
 *@param	pltt_num：塗りつぶすパレットナンバー
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
void DrawTPClean(GF_BGL_INI* bgl, u16 pltt_num )
{
	// 初期化されているかチェック
	SDK_ASSERTMSG( TouchPanelDrawInit != 0,
			"warning:TouchPanelDrawSystem初期化されていません\n" );

	//
	// パレットナンバーの色でクリーンする
	//
	GF_BGL_BmpWinDataFill(TouchPanelDrawDataIdx, pltt_num );			// 塗りつぶし
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	保存している１つ前の座標を初期化する
 *
 *@param	none
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
void DrawTPOldMatDest( void )
{
	// 初期化
	TouchPanelOld.touch = TP_TOUCH_OFF;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ブラシデータを作成する
 *
 *@param	p_brush：ブラシデータ
 *@param	pltt：パレットナンバー
 *@param	size_x：横サイズ
 *@param	size_y：たてサイズ
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
void MakeTPBrush( TP_BRUSH_DATA* p_brush, u16 pltt, u16 size_x, u16 size_y, int heap )
{
	int i, j;
	int make_size;		// キャラクタデータのサイズ
	u16 shift;			// シフトする値
	u32 offset;			// オフセット値

	
	//
	// ブラシデータを作成する
	// キャラクタは絶対に８の倍数にする
	// 何もうあがきしたくないときは０を入れる
	//
	// キャラクタデータサイズを求める
	p_brush->SizeX = size_x;
	p_brush->SizeY = size_y;
	if( (p_brush->SizeX % 8) != 0 ){
		p_brush->SizeX += (8 - (size_x % 8));
	}
	if( (p_brush->SizeY % 8) != 0 ){
		p_brush->SizeY += (8 - (size_y % 8));
	}

	
	p_brush->pCharData = (u16*)sys_AllocMemory( heap, sizeof(u16) * ((p_brush->SizeX / 4) * p_brush->SizeY) );

	// 0で初期化
	for( i = 0; i < (p_brush->SizeX / 4) * p_brush->SizeY; i++ ){
		p_brush->pCharData[ i ] = 0;
	}


	// キャラクタ内をパレットの色で塗りつぶす
	for( i = 0; i < size_y; i++ ){
		for( j = 0; j < size_x; j++ ){
			// 座標位置のオフセットを求める
			offset = getOffset( j, i, &shift, p_brush->SizeX / 8 );

			// オフセットの位置に格納
			*(p_brush->pCharData + offset) |= pltt << shift;
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	絵のブラシデータを作成する
 *@brief	サイズは必ずキャラクタ単位（８）でお願いします
 *
 *@param	p_brush：ブラシデータ
 *@param	p_char：絵のキャラクタデータ
 *@param	size_x：横サイズ
 *@param	size_y：たてサイズ
 *@param	heap	使用するヒープ
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
void MakeTPGraphicBrush( TP_BRUSH_DATA* p_brush, const u16* p_char, u16 size_x, u16 size_y, int heap )
{
	int i, j;
	int make_size;		// キャラクタデータのサイズ
	u16 shift;			// シフトする値
	u32 offset;			// オフセット値

	
	//
	// ブラシデータを作成する
	// キャラクタは絶対に８の倍数にする
	// 何もうあがきしたくないときは０を入れる
	//
	// キャラクタデータサイズを求める
	p_brush->SizeX = size_x;
	p_brush->SizeY = size_y;

	
	p_brush->pCharData = (u16*)sys_AllocMemory( heap, sizeof(u16) * ((p_brush->SizeX / 4) * p_brush->SizeY) );

	// コピー
	MI_CpuCopy16( p_char, p_brush->pCharData, sizeof(u16) * ((p_brush->SizeX / 4) * p_brush->SizeY) );

}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ブラシデータを破棄する
 *
 *@param	p_brush：ブラシデータ
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
void DestTPBrush( TP_BRUSH_DATA* p_brush )
{
	//
	// ブラシデータ破棄
	//
	sys_FreeMemoryEz( p_brush->pCharData );
	p_brush->pCharData = NULL;
}
	
//----------------------------------------------------------------------------
/**
 *
 *@brief	線を描画する
 *
 *@param	x1：描画開始ｘ座標
 *@param	y1：描画開始ｙ座標
 *@param	x2：描画終了ｘ座標
 *@param	y2：描画終了ｙ座標
 *@param	brush_data：ブラシデータ
 *
 *@return	none
 *
 */
//-----------------------------------------------------------------------------
static void drawLine(GF_BGL_INI* bgl, u16 x1, u16 y1, u16 x2, u16 y2, TP_BRUSH_DATA brush_data )
{
	u16 width, height;			// ラインの幅と高さ
	int i;						// ループ用
	u16 min;					// 座標の最低の値（１づつ増えるほう）
	u16 max;					// 座標の最大の値（１づつ増えるほう）
	u16 base;					// ベースの値（minの座標の時の値）
	u16 px, py;					// ピクセル位置
	s32 vec_heigt;				// 線分の傾き
	
	
	// 高さと幅を取得
	width = (u16) ((x1 >= x2) ? (x1 - x2) : (x2 - x1));  // 幅を取得
    height = (u16) ((y1 >= y2) ? (y1 - y2) : (y2 - y1)); // 高さを取得

	
	// 大きいほうを１ドットづつ増える座標にする
	if( width > height ){
		if( x1 >= x2 ){
			min = x2;
			max = x1;
			base = y2;
	
			// 傾きを求める
			vec_heigt = ((y2 - y1) * 10000) / (x2 - x1);
		}else{
			min = x1;
			max = x2;
			base = y1;

			// 傾きを求める
			vec_heigt = ((y1 - y2) * 10000) / (x1 - x2);
		} 

		// 線に沿って点を描画
		for( i = min; i < max; i++ ){
			px = i;
			py = (u16) (base + ((vec_heigt * (i - min)) / 10000));
			drawPoint(bgl, px, py, brush_data );
		}
	}else{
		if( y1 >= y2 ){
			min = y2;
			max = y1;
			base = x2;
	
			// 傾きを求める
			vec_heigt = ((x2 - x1) * 10000) / (y2 - y1);
		}else{
			min = y1;
			max = y2;
			base = x1;

			// 傾きを求める
			vec_heigt = ((x1 - x2) * 10000) / (y1 - y2);
		} 

		// 線に沿って点を描画
		for( i = min; i < max; i++ ){
			px = (u16) (base + ((vec_heigt * (i - min)) / 10000));
			py = i;
			drawPoint( bgl, px, py, brush_data );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	内外判定しながら線を描画する
 *
 *@param	u16 x1：描画開始ｘ座標
 *@param	u16 y1：描画開始ｙ座標
 *@param	u16 x2：描画終了ｘ座標
 *@param	u16 y2：描画終了ｙ座標
 *@param	TP_BRUSH_DATA in_brush_data：領域内ブラシデータ
 *@param	TP_BRUSH_DATA out_brush_data：領域外ブラシデータ
 *@param	TP_PICTURE_DATA* pData：絵のデータ
 *
 *@return	なし
 *
 */
//-----------------------------------------------------------------------------
static void drawLineInOut(GF_BGL_INI* bgl, u16 x1, u16 y1, u16 x2, u16 y2,
		TP_BRUSH_DATA in_brush_data, TP_BRUSH_DATA out_brush_data,
		TP_PICTURE_DATA* pData )
{
	u16 width, height;			// ラインの幅と高さ
	int i;						// ループ用
	u16 min;					// 座標の最低の値（１づつ増えるほう）
	u16 max;					// 座標の最大の値（１づつ増えるほう）
	u16 base;					// ベースの値（minの座標の時の値）
	u16 px, py;					// ピクセル位置
	s32 vec_heigt;				// 線分の傾き
	
	
	// 高さと幅を取得
	width = (u16) ((x1 >= x2) ? (x1 - x2) : (x2 - x1));  // 幅を取得
    height = (u16) ((y1 >= y2) ? (y1 - y2) : (y2 - y1)); // 高さを取得

	
	// 大きいほうを１ドットづつ増える座標にする
	if( width > height ){
		if( x1 >= x2 ){
			min = x2;
			max = x1;
			base = y2;
	
			// 傾きを求める
			vec_heigt = ((y2 - y1) * 10000) / (x2 - x1);
		}else{
			min = x1;
			max = x2;
			base = y1;

			// 傾きを求める
			vec_heigt = ((y1 - y2) * 10000) / (x1 - x2);
		} 

		// 線に沿って点を描画
		for( i = min; i < max; i++ ){
			px = i;
			py = (u16) (base + ((vec_heigt * (i - min)) / 10000));

			// 内外判定
			if( CheckTPPictureInOut( pData, px, py ) == 1 ){
				drawPoint(bgl, px, py, in_brush_data );
			}else{	
				drawPoint(bgl, px, py, out_brush_data );
			}
		}
	}else{
		if( y1 >= y2 ){
			min = y2;
			max = y1;
			base = x2;
	
			// 傾きを求める
			vec_heigt = ((x2 - x1) * 10000) / (y2 - y1);
		}else{
			min = y1;
			max = y2;
			base = x1;

			// 傾きを求める
			vec_heigt = ((x1 - x2) * 10000) / (y1 - y2);
		} 

		// 線に沿って点を描画
		for( i = min; i < max; i++ ){
			px = (u16) (base + ((vec_heigt * (i - min)) / 10000));
			py = i;
			
			// 内外判定
			if( CheckTPPictureInOut( pData, px, py ) == 1 ){
				drawPoint(bgl, px, py, in_brush_data );
			}else{	
				drawPoint(bgl, px, py, out_brush_data );
			}
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	点を描画する
 *
 *@param	u16 x：描画ｘ座標
 *@param	u16 y：描画ｙ座標
 *@param	TP_BRUSH_DATA brush_data：ブラシデータ
 *
 *@return
 *
 */
//-----------------------------------------------------------------------------
static void drawPoint(GF_BGL_INI* bgl, u16 x, u16 y, TP_BRUSH_DATA brush_data )
{
	s32		draw_start_x = 0;		// 画面外に絵が飛び出すときにどこから描画をするか
	s32		draw_start_y = 0;		// 画面外に絵が飛び出すときにどこから描画をするか
	int		i;						// ループ用
	u32		offset;					// オフセット
	u16		shift;					// シフト

	
	// オーバーする値を計算
	// 0以下チェック
	if( x - (brush_data.SizeX / 2) < 0 ){
		draw_start_x = -(x - (brush_data.SizeX / 2));

	}
	if( y - (brush_data.SizeY / 2) < 0 ){
		draw_start_y = -(y - (brush_data.SizeY / 2));
	}

	

	// 描画
	// 横にずれているときは１段ずつ書き込む
	if( draw_start_x == 0 ){
		GF_BGL_BmpWinPrint( 
				TouchPanelDrawDataIdx,
				brush_data.pCharData,
				draw_start_x,
				draw_start_y,
				brush_data.SizeX - draw_start_x,
				brush_data.SizeY - draw_start_y,
				x - (brush_data.SizeX / 2) + draw_start_x,
				y - (brush_data.SizeY / 2) + draw_start_y,
				brush_data.SizeX - draw_start_x,
				brush_data.SizeY - draw_start_y );
	}else{
		// １段ずつ描画
		for( i = draw_start_y; i < brush_data.SizeY; i++ ){
			// 高さのオフセットを求める
			offset = getOffset( 0, i, &shift, brush_data.SizeX / 8 );
			
			GF_BGL_BmpWinPrint( 
					TouchPanelDrawDataIdx,
					(brush_data.pCharData + offset),
					draw_start_x,
					0,
					brush_data.SizeX - draw_start_x,
					1,
					x - (brush_data.SizeX / 2) + draw_start_x,
					y - (brush_data.SizeY / 2) + i,
					brush_data.SizeX - draw_start_x,
					1 );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	キャラクタデータオフセットを求める
 *
 *@param	u16 x,y：座標値
 *@param	u16* p_shift：シフトする値格納用
 *@param	u32 char_width：８＊８の数
 *
 *@return	u32	型：オフセット値(u16*型用)
 *
 */
//-----------------------------------------------------------------------------
static u32 getOffset( u16 x, u16 y, u16* p_shift, u32 char_width )
{
	u32	offset;			// オフセット値
	u16 char_off_y;		// １キャラクタデータ内のオフセット
	u16 char_off_x;		// １キャラクタデータ内のオフセット

	
	//
	// 座標値からu16型(２バイト)用のオフセットを求める
	//
	// キャラクタ単位の配列の大きさを求める	
	// その位置のキャラクタオフセットを求める
	offset = ((y / 8) * char_width) + (x / 8);

	// ８を表現するのに必要なU16の数をかける
	offset *= 16;

	// キャラクタ内のオフセットを求める
	char_off_y = y % 8;
	char_off_x = x % 8;
	char_off_y *= 2;				// 2＝キャラクタデータの横は８　８を格納するにはu16が2つ必要
	char_off_y += char_off_x / 4;	// 4＝u16には４ピクセル分の色が入るから４以上のときは１つずらした位置をオフセットにする
	char_off_x %= 4;				// 今char_off_yで４以上のときのオフセットをずらしたので４のあまりの値にする(シフトする値)
	char_off_x *= 4;				// これでシフトする値

	// シフトする値格納
	*p_shift = char_off_x;	

	return offset + char_off_y;
}

#if 0
//----------------------------------------------------------------------------
/**
 *
 *@brief	ベクトルデータを描画する
 *				(デバック用　　内外判定用データを描画するために作成しました)
 *
 *@param	Vec2DS32* p_point1：頂点とベクトルデータ
 *@param	Vec2DS32* p_point2：頂点とベクトルデータ
 *
 *@return	なし
 *
 */
//-----------------------------------------------------------------------------
static void drawVect(GF_BGL_INI* bgl, Vec2DS32* p_point1, Vec2DS32* p_point2 )
{	
	TP_BRUSH_DATA brush;
	
	MakeTPBrush( &brush, 3, 4, 4 );
	
	//
	// ベクトルデータを描画する
	//
	drawLine( bgl, p_point1->x, p_point1->y, p_point2->x, p_point2->y, brush );

	DestTPBrush( &brush );
}
#endif
