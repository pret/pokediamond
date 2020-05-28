//============================================================================================
/**
 * @file	board.c
 * @brief	看板処理
 * @author	Hiroyuki Nakamura
 * @date	2005.10.25
 */
//============================================================================================
#include "common.h"
#include "fieldsys.h"
#include "fieldmap.h"
#include "talk_msg.h"

#include "system/window.h"

#define	BOARD_H_GLOBAL
#include "board.h"


//============================================================================================
//	定数定義
//============================================================================================
/// 看板ワーク
struct _BOARD_WORK {
	GF_BGL_BMPWIN	win;	// BMPウィンドウ
	u16	map;				// マップID（グラフィックID）
	u8	type;				// 看板タイプ
	u8	req:7;				// リクエスト
	u8	flg:1;				// 作成フラグ
};

#define	BOARD_INIT_SCROLL_Y	( -48 )		///< 作成直後の初期Yスクロール値
#define	BOARD_SCROLL_VAL	( 16 )		///< 1sync のスクロール値
#define	BOARD_WIN_PX		( 0 )		///< ウィンドウ描画X座標
#define	BOARD_WIN_PY		( 18 )		///< ウィンドウ描画Y座標
#define	BOARD_WIN_SX		( 32 )		///< ウィンドウXサイズ
#define	BOARD_WIN_SY		( 6 )		///< ウィンドウYサイズ


//============================================================================================
//	プロトタイプ宣言
//============================================================================================
static void BoardMake( FIELDSYS_WORK * repw );
static void BoardDelete( FIELDSYS_WORK * repw );
static BOOL BoarsScroll_Up( FIELDSYS_WORK * repw );
static BOOL BoarsScroll_Down( FIELDSYS_WORK * repw );


//--------------------------------------------------------------------------------------------
/**
 * 看板ワーク確保
 *
 * @param	heap	ヒープID
 *
 * @return	確保したワーク
 */
//--------------------------------------------------------------------------------------------
void * BoardWorkAlloc( u32 heap )
{
	void * buf = sys_AllocMemory( heap, sizeof(BOARD_WORK) );
	memset( buf, 0, sizeof(BOARD_WORK) );
	return buf;
}

//--------------------------------------------------------------------------------------------
/**
 * 看板ワーク解放
 *
 * @param	wk		ワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BoardWorkDelete( BOARD_WORK * wk )
{
	if( wk->flg != 0 ){
		GF_BGL_BmpWinDel( &wk->win );
	}
	sys_FreeMemoryEz( wk );
}

//--------------------------------------------------------------------------------------------
/**
 * 看板データセット
 *
 * @param	wk		ワーク
 * @param	type	看板タイプ
 * @param	map		マップID（グラフィックID）
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BoardDataSet( BOARD_WORK * wk, u16 type, u16 map )
{
	wk->type = type;
	wk->map  = map;
}

//--------------------------------------------------------------------------------------------
/**
 * 看板リクエスト発行
 *
 * @param	wk		ワーク
 * @param	req		リクエスト
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BoardSetRequest( BOARD_WORK * wk, u8 req )
{
	wk->req = req;
}

//--------------------------------------------------------------------------------------------
/**
 * データ取得：BMPウィンドウデータ
 *
 * @param	wk		ワーク
 *
 * @return	BMPウィンドウデータ
 */
//--------------------------------------------------------------------------------------------
GF_BGL_BMPWIN * BoardWinGet( BOARD_WORK * wk )
{
	return &wk->win;
}

//--------------------------------------------------------------------------------------------
/**
 * データ取得：看板タイプ
 *
 * @param	wk		ワーク
 *
 * @return	看板タイプ
 */
//--------------------------------------------------------------------------------------------
u8 BoardTypeGet( BOARD_WORK * wk )
{
	return wk->type;
}

//--------------------------------------------------------------------------------------------
/**
 * 看板処理終了チェック
 *
 * @param	wk		ワーク
 *
 * @retval	"TRUE = 終了"
 * @retval	"FALSE = 動作中"
 */
//--------------------------------------------------------------------------------------------
BOOL BoardReqEndCheck( BOARD_WORK * wk )
{
	if( wk->req == BOARD_REQ_WAIT ){
		return TRUE;
	}
	return FALSE;
}

//--------------------------------------------------------------------------------------------
/**
 * 看板メイン処理
 *
 * @param	repw	フィールドワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BoardMain( FIELDSYS_WORK * repw )
{
	BOARD_WORK * wk = repw->board;

	switch( wk->req ){
	case BOARD_REQ_WAIT:	// 待機
		break;

	case BOARD_REQ_ADD:		// 看板ウィンドウ作成
		BoardMake( repw );
		wk->req = BOARD_REQ_WAIT;
		break;

	case BOARD_REQ_DOWN:	// 看板ウィンドウを下げる
		if( BoarsScroll_Down( repw ) == 1 ){
			wk->req = BOARD_REQ_WAIT;
		}
		break;

	case BOARD_REQ_UP:		// 看板ウィンドウを上げる
		if( BoarsScroll_Up( repw ) == 1 ){
			wk->req = BOARD_REQ_WAIT;
		}
		break;

	case BOARD_REQ_DEL:		// 看板ウィンドウ破棄
		BoardDelete( repw );
		wk->req = BOARD_REQ_WAIT;
		break;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * リクエストを即実行
 *
 * @param	repw	フィールドワーク
 * @param	req		リクエスト
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BoardSetDirect( FIELDSYS_WORK * repw, u8 req )
{
	BoardSetRequest( repw->board, req );
	BoardMain( repw );
}


//--------------------------------------------------------------------------------------------
/**
 * 看板作成
 *
 * @param	repw	フィールドワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BoardMake( FIELDSYS_WORK * repw )
{
	GF_BGL_ScrollSet( repw->bgl, FLD_MBGFRM_FONT, GF_BGL_SCROLL_Y_SET, BOARD_INIT_SCROLL_Y );

	// 看板未作成
	if( repw->board->flg == 0 ){
		FldBoardBmpAdd( repw->bgl, &repw->board->win, repw->board->type, FLD_MBGFRM_FONT );
		repw->board->flg = 1;
	}
	FldBoardWinPut( &repw->board->win, repw->board->type, repw->board->map );
}

//--------------------------------------------------------------------------------------------
/**
 * 看板削除
 *
 * @param	repw	フィールドワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void BoardDelete( FIELDSYS_WORK * repw )
{
	if( repw->board->flg == 0 ){ return; }	// 看板未作成

	GF_BGL_BmpWinDel( &repw->board->win );
	GF_BGL_ScrFill(
		repw->bgl, FLD_MBGFRM_FONT, 0,
		BOARD_WIN_PX, BOARD_WIN_PY, BOARD_WIN_SX, BOARD_WIN_SY, GF_BGL_SCRWRT_PALNL );
	GF_BGL_LoadScreenReq( repw->bgl, FLD_MBGFRM_FONT );
	GF_BGL_ScrollSet( repw->bgl, FLD_MBGFRM_FONT, GF_BGL_SCROLL_Y_SET, 0 );

	repw->board->flg = 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 看板スクロールイン
 *
 * @param	repw	フィールドワーク
 *
 * @retval	"1 = 終了"
 * @retval	"0 = スクロール中"
 */
//--------------------------------------------------------------------------------------------
static BOOL BoarsScroll_Up( FIELDSYS_WORK * repw )
{
	int	scroll = GF_BGL_ScrollGetY( repw->bgl, FLD_MBGFRM_FONT );

	if( scroll == 0 ){ return 1; }

	if( !( scroll > BOARD_INIT_SCROLL_Y && scroll < 0 ) ){
		GF_BGL_ScrollSet(
			repw->bgl, FLD_MBGFRM_FONT, GF_BGL_SCROLL_Y_SET, BOARD_INIT_SCROLL_Y );
	}

	GF_BGL_ScrollSet( repw->bgl, FLD_MBGFRM_FONT, GF_BGL_SCROLL_Y_INC, BOARD_SCROLL_VAL );

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 看板スクロールアウト
 *
 * @param	repw	フィールドワーク
 *
 * @retval	"1 = 終了"
 * @retval	"0 = スクロール中"
 */
//--------------------------------------------------------------------------------------------
static BOOL BoarsScroll_Down( FIELDSYS_WORK * repw )
{
	int	scroll = GF_BGL_ScrollGetY( repw->bgl, FLD_MBGFRM_FONT );

	if( scroll == BOARD_INIT_SCROLL_Y ){
		GF_BGL_ScrFill(
			repw->bgl, FLD_MBGFRM_FONT, 0,
			BOARD_WIN_PX, BOARD_WIN_PY, BOARD_WIN_SX, BOARD_WIN_SY, GF_BGL_SCRWRT_PALNL );
		GF_BGL_LoadScreenReq( repw->bgl, FLD_MBGFRM_FONT );
		GF_BGL_ScrollSet( repw->bgl, FLD_MBGFRM_FONT, GF_BGL_SCROLL_Y_SET, 0 );
		return 1;
	}

	if( !( scroll > BOARD_INIT_SCROLL_Y && scroll < 0 ) ){
		GF_BGL_ScrollSet( repw->bgl, FLD_MBGFRM_FONT, GF_BGL_SCROLL_Y_SET, 0 );
	}

	GF_BGL_ScrollSet( repw->bgl, FLD_MBGFRM_FONT, GF_BGL_SCROLL_Y_DEC, BOARD_SCROLL_VAL );

	return 0;
}
