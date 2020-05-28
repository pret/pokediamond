//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_encount_draw.c
 *	@brief		エンカウントデータ描画システム
 *	@author		tomoya takahashi
 *	@data		2006.02.09
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include "bg_system.h"

#define __ZKN_ENCOUNT_DRAW_H_GLOBAL
#include "include/application/zukanlist/zkn_encount_draw.h"

//-----------------------------------------------------------------------------
/**
 *					コーディング規約
 *		●関数名
 *				１文字目は大文字それ以降は小文字にする
 *		●変数名
 *				・変数共通
 *						constには c_ を付ける
 *						staticには s_ を付ける
 *						ポインタには p_ を付ける
 *						全て合わさると csp_ となる
 *				・グローバル変数
 *						１文字目は大文字
 *				・関数内変数
 *						小文字と”＿”と数字を使用する 関数の引数もこれと同じ
*/
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------
#define GRID_MUDDY_MUSK_NONE	( 0 )
#define GRID_MUDDY_MUSK_U		( 1<<0 )	// 1
#define GRID_MUDDY_MUSK_D		( 1<<1 )	// 2
#define GRID_MUDDY_MUSK_L		( 1<<2 )	// 4
#define GRID_MUDDY_MUSK_R		( 1<<3 )	// 8
#define GRID_MUDDY_MUSK_UL		( 1<<4 )	// 10
#define GRID_MUDDY_MUSK_UR		( 1<<5 )	// 20
#define GRID_MUDDY_MUSK_DL		( 1<<6 )	// 40
#define GRID_MUDDY_MUSK_DR		( 1<<7 )	// 80

#define 	GRIDCHK_MUDDY_MUSK_U			( GRID_MUDDY_MUSK_U )
#define 	GRIDCHK_MUDDY_MUSK_D			( GRID_MUDDY_MUSK_D )
#define 	GRIDCHK_MUDDY_MUSK_L			( GRID_MUDDY_MUSK_L )
#define 	GRIDCHK_MUDDY_MUSK_R			( GRID_MUDDY_MUSK_R )
#define 	GRIDCHK_MUDDY_MUSK_UD			( GRID_MUDDY_MUSK_U|GRID_MUDDY_MUSK_D )
#define 	GRIDCHK_MUDDY_MUSK_UL			( GRID_MUDDY_MUSK_U|GRID_MUDDY_MUSK_L )
#define 	GRIDCHK_MUDDY_MUSK_UR			( GRID_MUDDY_MUSK_U|GRID_MUDDY_MUSK_R )
#define 	GRIDCHK_MUDDY_MUSK_DL			( GRID_MUDDY_MUSK_D|GRID_MUDDY_MUSK_L )
#define 	GRIDCHK_MUDDY_MUSK_DR			( GRID_MUDDY_MUSK_D|GRID_MUDDY_MUSK_R )
#define 	GRIDCHK_MUDDY_MUSK_LR			( GRID_MUDDY_MUSK_L|GRID_MUDDY_MUSK_R )
#define 	GRIDCHK_MUDDY_MUSK_UDL			( GRID_MUDDY_MUSK_U|GRID_MUDDY_MUSK_D|GRID_MUDDY_MUSK_L )
#define 	GRIDCHK_MUDDY_MUSK_UDR			( GRID_MUDDY_MUSK_U|GRID_MUDDY_MUSK_D|GRID_MUDDY_MUSK_R )
#define 	GRIDCHK_MUDDY_MUSK_ULR			( GRID_MUDDY_MUSK_U|GRID_MUDDY_MUSK_L|GRID_MUDDY_MUSK_R )
#define 	GRIDCHK_MUDDY_MUSK_DLR			( GRID_MUDDY_MUSK_D|GRID_MUDDY_MUSK_L|GRID_MUDDY_MUSK_R )
#define 	GRIDCHK_MUDDY_MUSK_UDLR			( GRID_MUDDY_MUSK_U|GRID_MUDDY_MUSK_D|GRID_MUDDY_MUSK_L|GRID_MUDDY_MUSK_R )
#define 	GRIDCHK_MUDDY_MUSK_TUL			( GRID_MUDDY_MUSK_UL )
#define 	GRIDCHK_MUDDY_MUSK_TUR			( GRID_MUDDY_MUSK_UR )
#define 	GRIDCHK_MUDDY_MUSK_TDL			( GRID_MUDDY_MUSK_DL )
#define 	GRIDCHK_MUDDY_MUSK_TDR			( GRID_MUDDY_MUSK_DR )
#define 	GRIDCHK_MUDDY_MUSK_TULTUR		( GRID_MUDDY_MUSK_UL|GRID_MUDDY_MUSK_UR )
#define 	GRIDCHK_MUDDY_MUSK_TULTDL		( GRID_MUDDY_MUSK_UL|GRID_MUDDY_MUSK_DL )
#define 	GRIDCHK_MUDDY_MUSK_TULTDR		( GRID_MUDDY_MUSK_UL|GRID_MUDDY_MUSK_DR )
#define 	GRIDCHK_MUDDY_MUSK_TURTDL		( GRID_MUDDY_MUSK_UR|GRID_MUDDY_MUSK_DL )
#define 	GRIDCHK_MUDDY_MUSK_TURTDR		( GRID_MUDDY_MUSK_UR|GRID_MUDDY_MUSK_DR )
#define 	GRIDCHK_MUDDY_MUSK_TDLTDR		( GRID_MUDDY_MUSK_DL|GRID_MUDDY_MUSK_DR )
#define 	GRIDCHK_MUDDY_MUSK_TULTURTDL	( GRID_MUDDY_MUSK_UL|GRID_MUDDY_MUSK_UR|GRID_MUDDY_MUSK_DL )
#define 	GRIDCHK_MUDDY_MUSK_TULTURTDR	( GRID_MUDDY_MUSK_UL|GRID_MUDDY_MUSK_UR|GRID_MUDDY_MUSK_DR )
#define 	GRIDCHK_MUDDY_MUSK_TULTDLTDR	( GRID_MUDDY_MUSK_UL|GRID_MUDDY_MUSK_DL|GRID_MUDDY_MUSK_DR )
#define 	GRIDCHK_MUDDY_MUSK_TURTDLTDR	( GRID_MUDDY_MUSK_UR|GRID_MUDDY_MUSK_DL|GRID_MUDDY_MUSK_DR )
#define 	GRIDCHK_MUDDY_MUSK_TULTURTDLTDR	( GRID_MUDDY_MUSK_UL|GRID_MUDDY_MUSK_UR|GRID_MUDDY_MUSK_DL|GRID_MUDDY_MUSK_DR )
#define 	GRIDCHK_MUDDY_MUSK_UTDLTDR		( GRID_MUDDY_MUSK_U|GRID_MUDDY_MUSK_DL|GRID_MUDDY_MUSK_DR )
#define 	GRIDCHK_MUDDY_MUSK_DTULTUR		( GRID_MUDDY_MUSK_D|GRID_MUDDY_MUSK_UL|GRID_MUDDY_MUSK_UR )
#define 	GRIDCHK_MUDDY_MUSK_LTURTDR		( GRID_MUDDY_MUSK_L|GRID_MUDDY_MUSK_UR|GRID_MUDDY_MUSK_DR )
#define 	GRIDCHK_MUDDY_MUSK_RTULTDL		( GRID_MUDDY_MUSK_R|GRID_MUDDY_MUSK_UL|GRID_MUDDY_MUSK_DL )
#define 	GRIDCHK_MUDDY_MUSK_ULTDR		( GRID_MUDDY_MUSK_U|GRID_MUDDY_MUSK_L|GRID_MUDDY_MUSK_DR )
#define 	GRIDCHK_MUDDY_MUSK_URTDL		( GRID_MUDDY_MUSK_U|GRID_MUDDY_MUSK_R|GRID_MUDDY_MUSK_DL )
#define 	GRIDCHK_MUDDY_MUSK_DLTUR		( GRID_MUDDY_MUSK_D|GRID_MUDDY_MUSK_L|GRID_MUDDY_MUSK_UR )
#define 	GRIDCHK_MUDDY_MUSK_DRTUL		( GRID_MUDDY_MUSK_D|GRID_MUDDY_MUSK_R|GRID_MUDDY_MUSK_UL )
#define		GRIDCHK_MUDDY_MUSK_UTDL			( GRID_MUDDY_MUSK_U|GRID_MUDDY_MUSK_DL )
#define		GRIDCHK_MUDDY_MUSK_UTDR			( GRID_MUDDY_MUSK_U|GRID_MUDDY_MUSK_DR )
#define		GRIDCHK_MUDDY_MUSK_DTUL			( GRID_MUDDY_MUSK_D|GRID_MUDDY_MUSK_UL )
#define		GRIDCHK_MUDDY_MUSK_DTUR			( GRID_MUDDY_MUSK_D|GRID_MUDDY_MUSK_UR )
#define		GRIDCHK_MUDDY_MUSK_LTUR			( GRID_MUDDY_MUSK_L|GRID_MUDDY_MUSK_UR )
#define		GRIDCHK_MUDDY_MUSK_LTDR			( GRID_MUDDY_MUSK_L|GRID_MUDDY_MUSK_DR )
#define		GRIDCHK_MUDDY_MUSK_RTUL			( GRID_MUDDY_MUSK_R|GRID_MUDDY_MUSK_UL )
#define		GRIDCHK_MUDDY_MUSK_RTDL			( GRID_MUDDY_MUSK_R|GRID_MUDDY_MUSK_DL )







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
static void PrintMain( GF_BGL_BMPWIN* win, u8* char_buff, u16 char_sizex, u16 char_sizey, int grid_size, int chip_no, u8 win_x, u8 win_y );

static void MuddyMain( u8* p_buff, int x, int y, int size_x, int size_y );

static int GetGridChipData( u8* p_buff, int x, int y, int size_x, int size_y );

static void GetGrid8Data( u8* p_buff, int* p_mask8, int x, int y, int size_x, int size_y );
static int GetMuddyChip( int mask8 );

//----------------------------------------------------------------------------
/**
 *	@brief	ビットマップデータ作成
 *
 *	@param	win				ビットマップウィンドウ
 *	@param	char_buff		キャラクタバッファ
 *	@param	char_size_x		キャラクタサイズｘ
 *	@param	char_size_y		キャラクタサイズｙ
 *	@param	grid_size		1グリッドピクセルサイズ
 *	@param	p_buff			グラフィックバッファ
 *	@param	size_x			バッファ横サイズ
 *	@param	size_y			バッファ縦サイズ
 *	@param	win_x			bitmapウィンドウに書き込む座標ｘ
 *	@param	win_y			bitmapウィンドウに書き込む座標ｙ
 *	@param	win_size_x		bitmapウィンドウのサイズｘ
 *	@param	win_size_y		bitmapウィンドウのサイズｙ
 *
 *	@return	none
 *
 *	サイズは全部ピクセル
 */
//-----------------------------------------------------------------------------
void ZKN_ENCOUNTDRAW_PrintChar( GF_BGL_BMPWIN * win, u8* char_buff, u16 char_sizex, u16 char_sizey, u8 grid_size, u8* p_buff, u8 size_x, u8 size_y, u16 win_x, u16 win_y )
{
	int i, j;


	// チップデータ書き込み
	for( i=0; i<size_y; i++ ){

		for( j=0; j<size_x; j++ ){

			// 書き込み
			PrintMain( win, char_buff,	
					char_sizex, char_sizey,
					grid_size, p_buff[ (i*size_y)+j ],	// chipdata
					win_x + (j * grid_size),
					win_y + (i * grid_size) );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	グリッドデータの滑らかグラフィック作成
 *
 *	@param	p_buff	バッファ
 *	@param	size_x	バッファサイズｘ
 *	@param	size_y	バッファサイズｙ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_ENCOUNTDRAW_MakeMuddyData( u8* p_buff, u8 size_x, u8 size_y )
{
	int i,j;
	
	for( i=0; i<size_y; i++ ){

		for( j=0; j<size_x; j++ ){
			MuddyMain( p_buff, j, i, size_x, size_y );
		}
	}
}



//----------------------------------------------------------------------------
/**
 *	@brief	ウィンドウへの書き込みメイン
 *
 *	@param	win			bmpウィンドウ
 *	@param	char_buff	キャラクタバッファ
 *	@param	char_sizex	キャラクタサイズｘ
 *	@param	char_sizey	キャラクタサイズｙ
 *	@param	grid_size	グリッドサイズ
 *	@param	chip_no		チップナンバー
 *	@param	win_x		ウィンドウ書き込み座標ｘ
 *	@param	win_y		ウィンドウ書き込み座標ｙ
 *	@param	win_size_x	ウィンドウサイズｘ
 *	@param	win_size_y	ウィンドウサイズｙ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void PrintMain( GF_BGL_BMPWIN* win, u8* char_buff, u16 char_sizex, u16 char_sizey, int grid_size, int chip_no, u8 win_x, u8 win_y )
{
	int chip_x;
	int chip_y;

	if( chip_no != ZKN_ENCOUNT_DRAW_MUDDY_NONE ){
		
		chip_x = chip_no * grid_size;
		chip_y = chip_x / char_sizex;
		chip_x = chip_x % char_sizex;

		GF_BGL_BmpWinPrint( win, char_buff,
				chip_x, chip_y, char_sizex, char_sizey,
				win_x, win_y, grid_size, grid_size );
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	グリッドデータに丸め込みグラフィックナンバーを設定
 *
 *	@param	p_buff		グリッドバッファ
 *	@param	x			チェックｘ座標
 *	@param	y			チェックｙ座標
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void MuddyMain( u8* p_buff, int x, int y, int size_x, int size_y )
{
	int mask8;
	int chip_no;
	
	// 中身がカラならチェック
	if( p_buff[ (y * size_x) + x ] == ZKN_ENCOUNT_DRAW_MUDDY_NONE ){
		
		// ８方向チップデータ取得
		GetGrid8Data( p_buff, &mask8, x, y, size_x, size_y );

		// 丸め込みチップナンバー取得
		chip_no = GetMuddyChip( mask8 );

		// 格納
		p_buff[ (y * size_x) + x ] = chip_no;
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	グリッドのチップデータを取得
 *
 *	@param	p_buff	バッファ
 *	@param	x		ｘ座標
 *	@param	y		ｙ座標
 *
 *	@return	チップデータ	ないとき -1
 */
//-----------------------------------------------------------------------------
static int GetGridChipData( u8* p_buff, int x, int y, int size_x, int size_y )
{
	if( (x < 0) || (x >= size_x) ){
		return -1;
	}
	if( (y < 0) || (y >= size_y) ){
		return -1;
	}

	return  p_buff[ (y*size_x) + x ];
	
}


//----------------------------------------------------------------------------
/**
 *	@brief	xyを中心にした回りの８点データ取得
 *
 *	@param	p_buff		バッファ
 *	@param	p_8buff		８点データ取得バッファ
 *	@param	x			バッファｘ座標
 *	@param	y			バッファｙ座標
 *	@param	size_x		バッファサイズｘ
 *	@param	size_y		バッファサイズｙ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void GetGrid8Data( u8* p_buff, int* p_mask8, int x, int y, int size_x, int size_y )
{
	int chip_data;


	*p_mask8 = 0;
	
	// ８方向の点を検索
	// 上
	if( GetGridChipData( p_buff, x, y - 1, size_x, size_y ) == ZKN_ENCOUNT_DRAW_MUDDY_NORMAL ){
		*p_mask8 |= GRID_MUDDY_MUSK_U;
	}
	// 下
	if( GetGridChipData( p_buff, x, y + 1, size_x, size_y ) == ZKN_ENCOUNT_DRAW_MUDDY_NORMAL ){
		*p_mask8 |= GRID_MUDDY_MUSK_D;
	}
	// 左
	if( GetGridChipData( p_buff, x - 1, y, size_x, size_y ) == ZKN_ENCOUNT_DRAW_MUDDY_NORMAL ){
		*p_mask8 |= GRID_MUDDY_MUSK_L;
	}
	// 右
	if( GetGridChipData( p_buff, x + 1, y, size_x,  size_y ) == ZKN_ENCOUNT_DRAW_MUDDY_NORMAL ){
		*p_mask8 |= GRID_MUDDY_MUSK_R;
	}

	// 斜めは両脇が無いときだけチェックする
	// 左上
	if( (((*p_mask8) & GRID_MUDDY_MUSK_U) == 0) && (((*p_mask8) & GRID_MUDDY_MUSK_L) == 0) ){
		if( GetGridChipData( p_buff, x - 1, y - 1, size_x, size_y ) == ZKN_ENCOUNT_DRAW_MUDDY_NORMAL ){
			*p_mask8 |= GRID_MUDDY_MUSK_UL;
		}
	}

	// 右上
	if( (((*p_mask8) & GRID_MUDDY_MUSK_U) == 0) && (((*p_mask8) & GRID_MUDDY_MUSK_R) == 0) ){
		if( GetGridChipData( p_buff, x + 1, y - 1, size_x, size_y ) == ZKN_ENCOUNT_DRAW_MUDDY_NORMAL ){
			*p_mask8 |= GRID_MUDDY_MUSK_UR;
		}
	}
	// 左下
	if( (((*p_mask8) & GRID_MUDDY_MUSK_D) == 0) && (((*p_mask8) & GRID_MUDDY_MUSK_L) == 0) ){
		if( GetGridChipData( p_buff, x - 1, y + 1, size_x, size_y ) == ZKN_ENCOUNT_DRAW_MUDDY_NORMAL ){
			*p_mask8 |= GRID_MUDDY_MUSK_DL;
		}
	}
	// 右下
	if( (((*p_mask8) & GRID_MUDDY_MUSK_D) == 0) && (((*p_mask8) & GRID_MUDDY_MUSK_R) == 0) ){
		if( GetGridChipData( p_buff, x + 1, y + 1, size_x, size_y ) == ZKN_ENCOUNT_DRAW_MUDDY_NORMAL ){
			*p_mask8 |= GRID_MUDDY_MUSK_DR;
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	丸め込みチップデータ作成
 *
 *	@param	p_8buff		８方向チップデータ
 *
 *	@return	丸め込みデータ
 */
//-----------------------------------------------------------------------------
static int GetMuddyChip( int mask8 )
{
	int ret;
	
	switch( mask8 ){
	case 0:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_NONE;
		break;
	case GRIDCHK_MUDDY_MUSK_U:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_U;
		break;
	case GRIDCHK_MUDDY_MUSK_D:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_D;
		break;
	case GRIDCHK_MUDDY_MUSK_L:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_L;
		break;
	case GRIDCHK_MUDDY_MUSK_R:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_R;
		break;
	case GRIDCHK_MUDDY_MUSK_UD:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_UD;
		break;
	case GRIDCHK_MUDDY_MUSK_UL:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_UL;
		break;
	case GRIDCHK_MUDDY_MUSK_UR:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_UR;
		break;
	case GRIDCHK_MUDDY_MUSK_DL:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_DL;
		break;
	case GRIDCHK_MUDDY_MUSK_DR:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_DR;
		break;
	case GRIDCHK_MUDDY_MUSK_LR:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_LR;
		break;
	case GRIDCHK_MUDDY_MUSK_UDL:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_UDL;
		break;
	case GRIDCHK_MUDDY_MUSK_UDR:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_UDR;
		break;
	case GRIDCHK_MUDDY_MUSK_ULR:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_ULR;
		break;
	case GRIDCHK_MUDDY_MUSK_DLR:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_DLR;
		break;
	case GRIDCHK_MUDDY_MUSK_UDLR:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_UDLR;
		break;
	case GRIDCHK_MUDDY_MUSK_TUL:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_TUL;
		break;
	case GRIDCHK_MUDDY_MUSK_TUR:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_TUR;
		break;
	case GRIDCHK_MUDDY_MUSK_TDL:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_TDL;
		break;
	case GRIDCHK_MUDDY_MUSK_TDR:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_TDR;
		break;
	case GRIDCHK_MUDDY_MUSK_TULTUR:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_TULTUR;
		break;
	case GRIDCHK_MUDDY_MUSK_TULTDL:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_TULTDL;
		break;
	case GRIDCHK_MUDDY_MUSK_TULTDR:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_TULTDR;
		break;
	case GRIDCHK_MUDDY_MUSK_TURTDL:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_TURTDL;
		break;
	case GRIDCHK_MUDDY_MUSK_TURTDR:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_TURTDR;
		break;
	case GRIDCHK_MUDDY_MUSK_TDLTDR:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_TDLTDR;
		break;
	case GRIDCHK_MUDDY_MUSK_TULTURTDL:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_TULTURTDL;
		break;
	case GRIDCHK_MUDDY_MUSK_TULTURTDR:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_TULTURTDR;
		break;
	case GRIDCHK_MUDDY_MUSK_TULTDLTDR:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_TULTDLTDR;
		break;
	case GRIDCHK_MUDDY_MUSK_TURTDLTDR:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_TURTDLTDR;
		break;
	case GRIDCHK_MUDDY_MUSK_TULTURTDLTDR:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_TULTURTDLTDR;
		break;
	case GRIDCHK_MUDDY_MUSK_UTDLTDR:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_UTDLTDR;
		break;
	case GRIDCHK_MUDDY_MUSK_DTULTUR:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_DTULTUR;
		break;
	case GRIDCHK_MUDDY_MUSK_LTURTDR:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_LTURTDR;
		break;
	case GRIDCHK_MUDDY_MUSK_RTULTDL:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_RTULTDL;
		break;
	case GRIDCHK_MUDDY_MUSK_ULTDR:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_ULTDR;
		break;
	case GRIDCHK_MUDDY_MUSK_URTDL:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_URTDL;
		break;
	case GRIDCHK_MUDDY_MUSK_DLTUR:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_DLTUR;
		break;
	case GRIDCHK_MUDDY_MUSK_DRTUL:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_DRTUL;
		break;
	case GRIDCHK_MUDDY_MUSK_UTDL:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_UTDL;
		break;
	case GRIDCHK_MUDDY_MUSK_UTDR:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_UTDR;
		break;
	case GRIDCHK_MUDDY_MUSK_DTUL:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_DTUL;
		break;
	case GRIDCHK_MUDDY_MUSK_DTUR:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_DTUR;
		break;
	case GRIDCHK_MUDDY_MUSK_LTUR:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_LTUR;
		break;
	case GRIDCHK_MUDDY_MUSK_LTDR:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_LTDR;
		break;
	case GRIDCHK_MUDDY_MUSK_RTUL:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_RTUL;
		break;
	case GRIDCHK_MUDDY_MUSK_RTDL:
		ret = ZKN_ENCOUNT_DRAW_MUDDY_RTDL;
		break;

	default:
		// おかしい
		GF_ASSERT_MSG( 0, "%x", mask8 );
		break;
	}

	return ret;
}

