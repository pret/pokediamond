//=============================================================================
/**
 * @file	bmp_list.c	
 * @brief	ビットマップＢＧ上でのリスト表示システム
 * @author	GAME FREAK inc.
 * @date	tetsu
 */
//=============================================================================
#include <nitro.h>
#include <nnsys.h>
#include "common.h"
#include "fntsys.h"
#include "system/fontproc.h"
#include "system/bmp_cursor.h"

#define __BMP_LIST_H_GLOBAL__
#include "system/bmp_list.h"


/********************************************************************/
/*                                                                  */
/*				使用定義											*/
/*                                                                  */
/********************************************************************/
enum {
	LIST_UP = 0,
	LIST_DOWN
};


typedef struct {
	u8	f_col:4;		// 表示文字色
	u8	b_col:4;		// 表示背景色
	u8	s_col:4;		// 表示文字影色
	u8	msg_spc:6;		// 文字間隔Ｘ
	u8	dummy:6;		// 未使用
	u8	font:7;			// 文字指定
	u8	sw:1;			// 一時変更スイッチ
}BMPLIST_TMP;

///リストワーク構造体
struct _BMPLIST_WORK {

	BMPLIST_HEADER	hed;	//表示文字データヘッダ

	BMPLIST_TMP		tmp;	// 一時変更データ

	BMPCURSOR * cursor;		// BMPカーソルデータ

	u16	lp;			//リスト位置
	u16	cp;			//カーソル位置
	u8	seq;		//処理シーケンス
	u8	scrwork;	//スクロールワーク
	u8	cur_actID;	//
	u8	work;		//移動方向（使ってないようなので）

	u8	mode;		// メモリ取得モード
};


/********************************************************************/
/*                                                                  */
/*				ローカル関数宣言									*/
/*                                                                  */
/********************************************************************/
static void LocalMsgPrint( BMPLIST_WORK * lw, void * msg, u8 x, u8 y );
static void ListScreenPut( BMPLIST_WORK * lw, u16 print_p, u16 line, u16 len );
static void ListCursorPut( BMPLIST_WORK * lw );
static void ListCursorCls( BMPLIST_WORK * lw, u16 p );
static u8 ListCursorMoveUpDown( BMPLIST_WORK * lw, u8 mode );
static void ListScrollMoveUpDown( BMPLIST_WORK * lw, u8 len, u8 mode );
static u8 ListMoveUpDownCheck( BMPLIST_WORK * lw, u8 print_f, u8 req_line, u8 mode );
static void CallBackSet( BMPLIST_WORK * lw, u8 mode );



//--------------------------------------------------------------------------------------------
/**
 * 設定関数
 *
 * @param	bmplist		表示リストヘッダポインタ
 * @param	list_p		リスト初期位置
 * @param	cursor_p	カーソル初期位置
 * @param	mode		メモリ取得モード
 *
 * @return	BMPリストワーク
 *
 * @li	BMPリストワークはsys_AllocMemoryで確保
 */
//--------------------------------------------------------------------------------------------
BMPLIST_WORK * BmpListSet(
					const BMPLIST_HEADER * bmplist, u16 list_p, u16 cursor_p, u8 mode )
{
	BMPLIST_WORK * lw = (BMPLIST_WORK *)sys_AllocMemory( mode, sizeof(BMPLIST_WORK) );

	// 基本設定
	lw->hed       = *bmplist;
	lw->cursor    = BMPCURSOR_Create( mode );
	lw->lp        = list_p;
	lw->cp        = cursor_p;
	lw->seq       = 0;
	lw->scrwork   = 0;
	lw->cur_actID = 0xff;
	lw->work      = 0;
	lw->mode      = mode;

	// テンポラリ初期化
	lw->tmp.f_col   = lw->hed.f_col;	// 表示文字色
	lw->tmp.b_col   = lw->hed.b_col;	// 表示背景色
	lw->tmp.s_col   = lw->hed.s_col;	// 表示文字影色
	lw->tmp.msg_spc = lw->hed.msg_spc;	// 文字間隔Ｘ
	lw->tmp.font    = lw->hed.font;		// 文字指定
	lw->tmp.sw      = 0;				// 一時変更スイッチ

	// 項目数が表示指定ライン数より少ない場合は、表示指定ライン数を項目数にあわせる
	if( lw->hed.count < lw->hed.line ){
		lw->hed.line = lw->hed.count;
	}

	// BMPカーソル色変更
	BMPCURSOR_ChangeColor(
		lw->cursor, GF_PRINTCOLOR_MAKE(lw->hed.f_col,lw->hed.s_col,lw->hed.b_col) );

	// リストキャラデータ初期化
	GF_BGL_BmpWinDataFill( lw->hed.win, lw->hed.b_col );
	ListScreenPut( lw, lw->lp, 0, lw->hed.line );		// 全体リスト描画
	ListCursorPut( lw );								// カーソル描画

	CallBackSet( lw, 1 );

	GF_BGL_BmpWinOn( bmplist->win );

	return lw;
}

//--------------------------------------------------------------------------------------------
/**
 * メイン関数
 *
 * @param	lw		BMPリストワーク
 *
 * @retval	"param = 選択パラメータ"
 * @retval	"BMPLIST_NULL = 選択中"
 * @retval	"BMPLIST_CANCEL	= キャンセル(Ｂボタン)"
 */
//--------------------------------------------------------------------------------------------
u32 BmpListMain( BMPLIST_WORK * lw )
{
	u16	skip_u, skip_d;

	lw->work = BMPLIST_MOVE_NONE;

	if( sys.trg & PAD_BUTTON_DECIDE ){
		return lw->hed.list[lw->lp + lw->cp].param;
	}
	if( sys.trg & PAD_BUTTON_CANCEL ){
		return BMPLIST_CANCEL;
	}
	if( sys.repeat & PAD_KEY_UP ){
		if( ListMoveUpDownCheck( lw, 1, 1, LIST_UP ) == 0 ){
			lw->work = BMPLIST_MOVE_UP;
		}
		return BMPLIST_NULL;
	}
	if( sys.repeat & PAD_KEY_DOWN ){
		if( ListMoveUpDownCheck( lw, 1, 1, LIST_DOWN ) == 0 ){
			lw->work = BMPLIST_MOVE_DOWN;
		}
		return BMPLIST_NULL;
	}
	//スキップフラグ判定
	switch( lw->hed.page_skip ){
	default:
	case BMPLIST_NO_SKIP:
		skip_u = 0;
		skip_d = 0;
		break;
	case BMPLIST_LRKEY_SKIP:
		skip_u = ( sys.repeat & PAD_KEY_LEFT );
		skip_d = ( sys.repeat & PAD_KEY_RIGHT );
		break;
	case BMPLIST_LRBTN_SKIP:
		skip_u = ( sys.repeat & PAD_BUTTON_L );
		skip_d = ( sys.repeat & PAD_BUTTON_R );
		break;
	}
	if( skip_u ){
		if( ListMoveUpDownCheck( lw, 1, (u8)lw->hed.line, LIST_UP ) == 0 ){
			lw->work = BMPLIST_MOVE_UP_SKIP;
		}
		return BMPLIST_NULL;
	}
	if( skip_d ){
		if( ListMoveUpDownCheck( lw, 1, (u8)lw->hed.line, LIST_DOWN ) == 0 ){
			lw->work = BMPLIST_MOVE_DOWN_SKIP;
		}
		return BMPLIST_NULL;
	}

	return BMPLIST_NULL;
}


//--------------------------------------------------------------------------------------------
/**
 * 終了関数
 *
 * @param	lw			BMPリストワーク
 * @param	list_bak	リスト位置バックアップワークポインタ
 * @param	cursor_bak	カーソル位置バックアップワークポインタ
 *
 * @return	none
 *
 * @li	lwをsys_FreeMemoryで開放
 * @li	バックアップワークは、NULL指定で保存しない
 */
//--------------------------------------------------------------------------------------------
void BmpListExit( BMPLIST_WORK * lw, u16 * list_bak, u16 * cursor_bak )
{
	if( list_bak != NULL ){
		*list_bak = lw->lp;
	}
	if( cursor_bak != NULL ){
		*cursor_bak = lw->cp;
	}
/*
	if( lw->cur_actID != 0xff ){
		CursorListActorDel( lw->cur_actID, lw->lh.c_disp_f - 2 );
	}
*/
	BMPCURSOR_Delete( lw->cursor );
	sys_FreeMemory( lw->mode, lw );
}

//--------------------------------------------------------------------------------------------
/**
 * リスト再描画
 *
 * @param	lw		BMPリストワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BmpListRewrite( BMPLIST_WORK * lw )
{
	// リストキャラデータ初期化
	GF_BGL_BmpWinDataFill( lw->hed.win, lw->hed.b_col );

	ListScreenPut( lw, lw->lp, 0, lw->hed.line );	// 全体リスト描画
	ListCursorPut( lw );							// カーソル描画
	GF_BGL_BmpWinOn( lw->hed.win );
}


//--------------------------------------------------------------------------------------------
/**
 * 文字色変更関数
 *
 * @param	lw			BMPリストワーク
 * @param	f_col		文字色
 * @param	b_col		背景色
 * @param	s_col		影色
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BmpListColorControl( BMPLIST_WORK * lw, u8 f_col, u8 b_col, u8 s_col )
{
	lw->hed.f_col = f_col;	//文字色ナンバー
	lw->hed.b_col = b_col;	//背景色ナンバー
	lw->hed.s_col = s_col;	//影色　ナンバー
}

//--------------------------------------------------------------------------------------------
/**
 * 表示位置変更関数
 *
 * @param	lw			BMPリストワーク
 * @param	x			表示Ｘ座標(キャラ単位)
 * @param	y			表示Ｙ座標(キャラ単位)
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BmpListMoveControl( BMPLIST_WORK * lw, u8 x, u8 y )
{
	GF_BGL_BmpWinSet_PosX( lw->hed.win, x );
	GF_BGL_BmpWinSet_PosY( lw->hed.win, y );
}


//--------------------------------------------------------------------------------------------
/**
 * 外部コントロール関数(描画・コールバック指定)
 *
 * @param	lw			BMPリストワーク
 * @param	lh			表示リストヘッダポインタ
 * @param	list_p		リスト初期位置
 * @param	cursor_p	カーソル初期位置
 * @param	print		描画フラグ
 * @param	direct		指定方向(キー定義)
 * @param	list_bak	リスト位置バックアップワークポインタ
 * @param	cursor_bak	カーソル位置バックアップワークポインタ
 *
 * @return	BMPLIST_NULL	
 *
 * リスト関数が動作していないとき、外部からの指定により
 * カーソル位置の変動をチェックし、指定バックアップワークに保存
 */
//--------------------------------------------------------------------------------------------
u32 BmpListMainOutControlEx(
		BMPLIST_WORK * lw, BMPLIST_HEADER * bmplist,
		u16 list_p, u16 cursor_p, u16 print, u16 direct, u16 * list_bak, u16 * cursor_bak )
{
    if( bmplist ){
		lw->hed = *bmplist;
	}
	lw->lp		= list_p;
	lw->cp		= cursor_p;
	lw->seq		= 0;
	lw->scrwork	= 0;

	if( direct == PAD_KEY_UP ){
		ListMoveUpDownCheck( lw, print, 1, LIST_UP );
	}else if( direct == PAD_KEY_DOWN ){
		ListMoveUpDownCheck( lw, print, 1, LIST_DOWN );
	}
	if( list_bak != NULL ){
		*list_bak = lw->lp;
	}
	if( cursor_bak != NULL ){
		*cursor_bak = lw->cp;
	}

	return BMPLIST_NULL;
}

//--------------------------------------------------------------------------------------------
/**
 * 外部コントロール関数(カーソル移動判定)
 *
 * @param	lw			BMPリストワーク
 * @param	bmplist		表示リストヘッダポインタ
 * @param	list_p		リスト初期位置
 * @param	cursor_p	カーソル初期位置
 * @param	direct		指定方向(キー定義)
 * @param	list_bak	リスト位置バックアップワークポインタ
 * @param	cursor_bak	カーソル位置バックアップワークポインタ
 *
 * @return	BMPLIST_NULL	
 *
 * リスト関数が動作していないとき、外部からの指定により
 * カーソル位置の変動をチェックし、指定バックアップワークに保存
 */
//--------------------------------------------------------------------------------------------
u32 BmpListMainOutControl(
		BMPLIST_WORK * lw, BMPLIST_HEADER * bmplist,
		u16 list_p, u16 cursor_p, u16 direct, u16 * list_bak, u16 * cursor_bak )
{
	return BmpListMainOutControlEx(lw,bmplist,list_p,cursor_p,0,direct,list_bak,cursor_bak);
/*
    if(bmplist){
        lw->hed		= *bmplist;
    }
	lw->lp		= list_p;
	lw->cp		= cursor_p;
	lw->seq		= 0;
	lw->scrwork	= 0;

	if( direct == PAD_KEY_UP ){
		ListMoveUpDownCheck( lw, 0, 1, LIST_UP );
	}else if( direct == PAD_KEY_DOWN ){
		ListMoveUpDownCheck( lw, 0, 1, LIST_DOWN );
	}
	if( list_bak != NULL ){
		*list_bak = lw->lp;
	}
	if( cursor_bak != NULL ){
		*cursor_bak = lw->cp;
	}

	return BMPLIST_NULL;
*/
}

//--------------------------------------------------------------------------------------------
/**
 * 文字色一時変更
 *
 * @param	lw		BMPリストワーク
 * @param	f_col	文字色
 * @param	b_col	背景色
 * @param	s_col	影色
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BmpListTmpColorChange( BMPLIST_WORK * lw, u8 f_col, u8 b_col, u8 s_col )
{
	lw->tmp.f_col = f_col;		// 文字色ナンバー
	lw->tmp.b_col = b_col;		// 背景色ナンバー
	lw->tmp.s_col = s_col;		// 影色　ナンバー
	lw->tmp.sw = 1;	
}

//--------------------------------------------------------------------------------------------
/**
 * BMPリストの全体位置を取得
 *
 * @param	lw			BMPリストワーク
 * @param	pos_bak		全体リスト位置バックアップワークポインタ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BmpListDirectPosGet( BMPLIST_WORK * lw, u16 * pos_bak )
{
	*pos_bak = (u16)(lw->lp + lw->cp);
}

//--------------------------------------------------------------------------------------------
/**
 * BMPリストのリスト位置、カーソル位置を取得
 *
 * @param	lw			BMPリストワーク
 * @param	list_bak	リスト位置バックアップワークポインタ
 * @param	cursor_bak	カーソル位置バックアップワークポインタ
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BmpListPosGet( BMPLIST_WORK * lw, u16 * list_bak, u16 * cursor_bak )
{
	if( list_bak != NULL ){
		*list_bak = lw->lp;
	}
	if( cursor_bak != NULL ){
		*cursor_bak = lw->cp;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * BMPリストのカーソルY座標を取得
 *
 * @param	lw		BMPリストワーク
 *
 * @return	カーソルY座標
 */
//--------------------------------------------------------------------------------------------
u16 BmpListCursorYGet( BMPLIST_WORK * lw )
{
	u8	yblk = FontHeaderGet( lw->hed.font, FONT_HEADER_SIZE_Y ) + lw->hed.line_spc;
	return  (u16)((lw->cp * yblk) + lw->hed.line_y);
}

//--------------------------------------------------------------------------------------------
/**
 * BMPリストのカーソル移動方向取得
 *
 * @param	lw		BMPリストワーク
 *
 * @return	カーソル移動方向取得
 */
//--------------------------------------------------------------------------------------------
u8 BmpListMoveSiteGet( BMPLIST_WORK * lw )
{
	return lw->work;
}

//--------------------------------------------------------------------------------------------
/**
 * 指定位置のパラメータ取得
 *
 * @param	lw		BMPリストワーク
 * @param	pos		位置
 *
 * @return	パラメータ
 */
//--------------------------------------------------------------------------------------------
u32 BmpListPosParamGet( BMPLIST_WORK * lw, u16 pos )
{
	return lw->hed.list[ pos ].param;
}

//--------------------------------------------------------------------------------------------
/**
 * パラメータ取得関数
 *
 * @param	lw		BMPリストワーク
 * @param	mode	パラメータ取得ＩＤ
 *
 * @retval	"0xffffffff = エラー"
 * @retval	"0xffffffff != パラメータ"
 */
//--------------------------------------------------------------------------------------------
u32	BmpListParamGet( BMPLIST_WORK * lw, u8 mode )
{
	u32	ret;

	switch( mode ){
	case BMPLIST_ID_CALLBACK:	// カーソル移動ごとのコールバック関数
		ret = (u32)lw->hed.call_back;
		break;
	case BMPLIST_ID_ICONFUNC:	// 一列表示ごとのコールバック関数
		ret = (u32)lw->hed.icon;
		break;
	case BMPLIST_ID_COUNT:		// リスト項目数
		ret = (u32)lw->hed.count;
		break;
	case BMPLIST_ID_LINE:		// 表示最大項目数
		ret = (u32)lw->hed.line;
		break;
	case BMPLIST_ID_RABEL_X:	// ラベル表示Ｘ座標
		ret = (u32)lw->hed.rabel_x;
		break;
	case BMPLIST_ID_DATA_X:		// 項目表示Ｘ座標
		ret = (u32)lw->hed.data_x;
		break;
	case BMPLIST_ID_CURSOR_X:	// カーソル表示Ｘ座標
		ret = (u32)lw->hed.cursor_x;
		break;
	case BMPLIST_ID_LINE_Y:		// 表示Ｙ座標
		ret = (u32)lw->hed.line_y;
		break;
	case BMPLIST_ID_LINE_YBLK:		//１行分シフト量取得(フォントの大きさ＋Ｙ間隔)
		ret = (u32)FontHeaderGet( lw->hed.font, FONT_HEADER_SIZE_Y ) + lw->hed.line_spc;
		break;
	case BMPLIST_ID_F_COL:		// 表示文字色
		ret = (u32)lw->hed.f_col;
		break;
	case BMPLIST_ID_B_COL:		// 表示背景色
		ret = (u32)lw->hed.b_col;
		break;
	case BMPLIST_ID_S_COL:		// 表示文字影色
		ret = (u32)lw->hed.s_col;
		break;
	case BMPLIST_ID_MSG_SPC:	// 文字間隔Ｘ
		ret = (u32)lw->hed.msg_spc;
		break;
	case BMPLIST_ID_LINE_SPC:	// 文字間隔Ｙ
		ret = (u32)lw->hed.line_spc;
		break;
	case BMPLIST_ID_PAGE_SKIP:	// ページスキップタイプ
		ret = (u32)lw->hed.page_skip;
		break;
	case BMPLIST_ID_FONT:		// 文字指定
		ret = (u32)lw->hed.font;
		break;
	case BMPLIST_ID_C_DISP_F:	// ＢＧカーソル(allow)表示フラグ
		ret = (u32)lw->hed.c_disp_f;
		break;
	case BMPLIST_ID_WIN:		// ウィンドウデータ
		ret = (u32)lw->hed.win;
		break;
	case BMPLIST_ID_WORK:		// ワーク
		ret = (u32)lw->hed.work;
		break;

	default:
		ret = 0xffffffff;
	}
	return ret;
}

//--------------------------------------------------------------------------------------------
/**
 * パラメータ変更関数
 *
 * @param	lw		BMPリストワーク
 * @param	mode	パラメータ取得ＩＤ
 * @param	param	変更値
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BmpListParamSet( BMPLIST_WORK * lw, u8 mode, u32 param )
{
	switch( mode ){
	case BMPLIST_ID_CALLBACK:	// カーソル移動ごとのコールバック関数
		lw->hed.call_back = (void *)param;
		break;
	case BMPLIST_ID_ICONFUNC:	// 一列表示ごとのコールバック関数
		lw->hed.icon = (void *)param;
		break;
	case BMPLIST_ID_COUNT:		// リスト項目数
		lw->hed.count = (u16)param;
		break;
	case BMPLIST_ID_LINE:		// 表示最大項目数
		lw->hed.line = (u16)param;
		break;
	case BMPLIST_ID_RABEL_X:	// ラベル表示Ｘ座標
		lw->hed.rabel_x = (u8)param;
		break;
	case BMPLIST_ID_DATA_X:		// 項目表示Ｘ座標
		lw->hed.data_x = (u8)param;
		break;
	case BMPLIST_ID_CURSOR_X:	// カーソル表示Ｘ座標
		lw->hed.cursor_x = (u8)param;
		break;
	case BMPLIST_ID_LINE_Y:		// 表示Ｙ座標
		lw->hed.line_y = (u8)param;
		break;
	case BMPLIST_ID_F_COL:		// 表示文字色
		lw->hed.f_col = (u8)param;
		break;
	case BMPLIST_ID_B_COL:		// 表示背景色
		lw->hed.b_col = (u8)param;
		break;
	case BMPLIST_ID_S_COL:		// 表示文字影色
		lw->hed.s_col = (u8)param;
		break;
	case BMPLIST_ID_MSG_SPC:	// 文字間隔Ｘ
		lw->hed.msg_spc = (u8)param;
		break;
	case BMPLIST_ID_LINE_SPC:	// 文字間隔Ｙ
		lw->hed.line_spc = (u8)param;
		break;
	case BMPLIST_ID_PAGE_SKIP:	// ページスキップタイプ
		lw->hed.page_skip = (u8)param;
		break;
	case BMPLIST_ID_FONT:		// 文字指定
		lw->hed.font = (u8)param;
		break;
	case BMPLIST_ID_C_DISP_F:	// ＢＧカーソル(allow)表示フラグ
		lw->hed.c_disp_f = (u8)param;
		break;
	case BMPLIST_ID_WIN:		// ウィンドウデータ
		lw->hed.win = (GF_BGL_BMPWIN *)param;
		break;
	case BMPLIST_ID_WORK:		// ワーク
		lw->hed.work = (void *)param;
		break;
	}
}

//--------------------------------------------------------------------------------------------
/**
 * BMP_MENULIST_DATAを再度設定する
 *
 * @param	BMP_MENULIST_DATA			BMPMENUリストポインタ
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void BmpListSetMenuListData(BMPLIST_WORK * lw, BMP_MENULIST_DATA* pList)
{
    lw->hed.list = pList;
}




/********************************************************************/
/*                                                                  */
/*                                                                  */
/*					内部処理関数									*/
/*                                                                  */
/*                                                                  */
/********************************************************************/
#include "gflib/strbuf.h"

//------------------------------------------------------------------
//		メッセージ表示
//------------------------------------------------------------------
static void LocalMsgPrint( BMPLIST_WORK * lw, void * msg, u8 x, u8 y )
{
    if(msg==NULL){
        return;
    }
    
	if( lw->tmp.sw )					// 一時変更スイッチ
	{
		GF_STR_PrintExpand( lw->hed.win, lw->tmp.font, msg, x, y, MSG_NO_PUT, 
				GF_PRINTCOLOR_MAKE(lw->tmp.f_col, lw->tmp.s_col, lw->tmp.b_col),
				lw->tmp.msg_spc, 0, NULL );
	}
	else
	{
		GF_STR_PrintExpand( lw->hed.win, lw->hed.font, msg, x, y, MSG_NO_PUT, 
				GF_PRINTCOLOR_MAKE(lw->hed.f_col, lw->hed.s_col, lw->hed.b_col),
				lw->hed.msg_spc, 0, NULL );
	}
}


//------------------------------------------------------------------
//		リスト表示
//------------------------------------------------------------------
static void ListScreenPut( BMPLIST_WORK * lw, u16 print_p, u16 line, u16 len )
{
	int	i;
	u8	x,y,yblk;

	yblk = FontHeaderGet(lw->hed.font,FONT_HEADER_SIZE_Y) + lw->hed.line_spc;

	for( i=0; i<len ;i++ ){
		if( lw->hed.list[print_p].param != BMPLIST_RABEL ){
			x = lw->hed.data_x;		// 描画Ｘオフセット
		}else{
			x = lw->hed.rabel_x;	// 描画Ｘオフセット
		}
		y = (u8)(((i + line) * yblk) + lw->hed.line_y);//描画Ｙオフセット
		if( lw->hed.icon != NULL ){
			lw->hed.icon( lw, lw->hed.list[print_p].param,y );
		}
		LocalMsgPrint( lw, (void*)lw->hed.list[print_p].str, x, y );
		print_p++;
	}
}


//------------------------------------------------------------------
//		カーソル表示
//static u8 ListCursorActorSet(BMPLIST_WORK* lw,int mode);
//------------------------------------------------------------------
static void ListCursorPut( BMPLIST_WORK * lw )
{
	u8	x,y,yblk;

	yblk = FontHeaderGet(lw->hed.font,FONT_HEADER_SIZE_Y) + lw->hed.line_spc;
	x = lw->hed.cursor_x;	//描画Ｘオフセット
	y = (u8)((lw->cp * yblk) + lw->hed.line_y);//描画Ｙオフセット

	switch(lw->hed.c_disp_f){
	case 0:
		BMPCURSOR_Print( lw->cursor, lw->hed.win, x, y );
		break;
	case 1:
		break;
	case 2:
/*
		if(lw->cur_actID == 0xff){
			//初期化(新規設定)
			lw->cur_actID = ListCursorActorSet(lw,0);
		}
		CursorListActorPosSet(	lw->cur_actID,
								BMPWIN_StatusGet(lw->lh.index,BMPWIN_GET_POS_X) * 8 - 1,
								BMPWIN_StatusGet(lw->lh.index,BMPWIN_GET_POS_Y) * 8 + y - 1,
								0);
*/
		break;
	case 3:
/*
		if(lw->cur_actID == 0xff){
			//初期化(新規設定)
			lw->cur_actID = ListCursorActorSet(lw,1);
		}
		CursorListActorPosSet(	lw->cur_actID,
								BMPWIN_StatusGet(lw->lh.index,BMPWIN_GET_POS_X) * 8 + x,
								BMPWIN_StatusGet(lw->lh.index,BMPWIN_GET_POS_Y) * 8 + y,
								1);
*/
		break;
	}
}

/*
static u8 ListCursorActorSet(BMPLIST_WORK* lw,int mode)
{
	ACT_CURSORLIST_HEADER header;

	header.x		= 0;		//表示位置Ｘ
	header.y		= 160;		//表示位置Ｙ
	header.xsize	= BMPWIN_StatusGet(lw->lh.index,BMPWIN_GET_SIZ_X) * 8 + 2;	//表示サイズＸ
	header.ysize	= FontHeaderGet(lw->lh.font,FONT_HEADER_SIZE_Y) + 2;		//表示サイズＹ
	header.cellID	= 0x4000;		//カーソルセルＩＤ
	header.palID	= ACT_OAMPAL;	//カーソルパレットＩＤ
	header.palnum	= 15;			//カーソルパレット指定の場合に使用

	return CursorListActorSet(&header,mode);

	return 0;
}
*/

//------------------------------------------------------------------
//		カーソル消去
//------------------------------------------------------------------
static void ListCursorCls( BMPLIST_WORK * lw, u16 p )
{
	u8	yblk;

	switch(lw->hed.c_disp_f){
	case 0:
		yblk = FontHeaderGet(lw->hed.font,FONT_HEADER_SIZE_Y) + lw->hed.line_spc;

		GF_BGL_BmpWinFill(
				lw->hed.win,						//表示ウインドウINDEX
				(u8)lw->hed.b_col,					//背景色データ
				lw->hed.cursor_x,					//Ｘ座標
				(u16)(p * yblk + lw->hed.line_y),	//Ｙ座標
				8, 16 );
		break;
	case 1:
	case 2:
	case 3:
		break;
	}
}

//------------------------------------------------------------------
//		カーソル移動
//------------------------------------------------------------------
static u8 ListCursorMoveUpDown( BMPLIST_WORK * lw, u8 mode )
{
	u16	list_p,cursor_p,check_p;

	cursor_p	= lw->cp;
	list_p		= lw->lp;

	if(mode == LIST_UP){

		//スクロール判定地点(リストの半分を過ぎたら)
		if(lw->hed.line == 1){
			check_p = 0;
		}else{
			check_p = (u16)(lw->hed.line - ((lw->hed.line / 2) + (lw->hed.line % 2)) - 1);
/*
			if( ( lw->hed.line & 1 ) != 0 ){
				check_p = (u16)((lw->hed.line / 2));
			}else{
				check_p = (u16)(lw->hed.line - ((lw->hed.line / 2) + (lw->hed.line % 2)) - 1);
			}
*/
		}

		if(list_p == 0){	//リスト最初の部分
			while(cursor_p > 0){
				cursor_p--;
				if(lw->hed.list[list_p + cursor_p].param != BMPLIST_RABEL){
					lw->cp = cursor_p;
					return 1;
				}
			}
			return 0;
		}
		while(cursor_p > check_p){
			cursor_p--;
			if(lw->hed.list[list_p + cursor_p].param != BMPLIST_RABEL){
				lw->cp = cursor_p;
				return 1;
			}
		}
		list_p--;
		lw->cp = check_p;
		lw->lp = list_p;

	}else{

		//スクロール判定地点(リストの半分を過ぎたら)
		if(lw->hed.line == 1){
			check_p = 0;
		}else{
			check_p = (u16)((lw->hed.line / 2) + (lw->hed.line % 2));
/*
			if( ( lw->hed.line & 1 ) != 0 ){
				check_p = (u16)((lw->hed.line / 2));
			}else{
				check_p = (u16)((lw->hed.line / 2) + (lw->hed.line % 2));
			}
*/
		}

		if(list_p == (lw->hed.count - lw->hed.line)){//リスト最後の部分
			while(cursor_p < (lw->hed.line - 1)){
				cursor_p++;
				if(lw->hed.list[list_p + cursor_p].param != BMPLIST_RABEL){
					lw->cp = cursor_p;
					return 1;
				}
			}
			return 0;
		}
		while(cursor_p < check_p){
			cursor_p++;
			if(lw->hed.list[list_p + cursor_p].param != BMPLIST_RABEL){
				lw->cp = cursor_p;
				return 1;
			}
		}
		list_p++;
		lw->cp = check_p;
		lw->lp = list_p;

	}

	return 2;
}

//------------------------------------------------------------------
//		画面スクロール移動
//------------------------------------------------------------------
static void ListScrollMoveUpDown( BMPLIST_WORK * lw, u8 len, u8 mode )
{
	u8	yblk;
	u16	ypos;

	if( len >= lw->hed.line ){
		GF_BGL_BmpWinDataFill( lw->hed.win, lw->hed.b_col );
		ListScreenPut( lw, lw->lp, 0, lw->hed.line );	//ライン描画
		return;
	}
	//１行分シフト量取得(フォントの大きさ＋Ｙ間隔)
	yblk = FontHeaderGet( lw->hed.font, FONT_HEADER_SIZE_Y ) + lw->hed.line_spc;

	if( mode == LIST_UP ){
		//データシフト
		GF_BGL_BmpWinShift(
			lw->hed.win, GF_BGL_BMPWIN_SHIFT_D,
			(u8)(len * yblk), (u8)((lw->hed.b_col<<4)|lw->hed.b_col) );

		ListScreenPut( lw, lw->lp, 0, len );	//追加ライン描画

		ypos = (u16)( lw->hed.line * yblk + lw->hed.line_y );

		//下部を消す
		GF_BGL_BmpWinFill(
			lw->hed.win,					//表示ウインドウINDEX
			(u8)lw->hed.b_col,				//背景色データ
			0, ypos,
			(u16)(GF_BGL_BmpWinGet_SizeX( lw->hed.win ) * 8),
			(u16)(GF_BGL_BmpWinGet_SizeY( lw->hed.win ) * 8 - ypos) );

	}else{
		//データシフト
		GF_BGL_BmpWinShift(
				lw->hed.win, GF_BGL_BMPWIN_SHIFT_U,
				(u8)(len * yblk), (u8)((lw->hed.b_col<<4)|lw->hed.b_col) );
		//追加ライン描画
		ListScreenPut(
			lw, (u16)(lw->lp + (lw->hed.line-len)), (u16)(lw->hed.line - len), (u16)len );
		//上部を消す
		GF_BGL_BmpWinFill(
			lw->hed.win,
			(u8)lw->hed.b_col,				//背景色データ
			0, 0,
			(u16)(GF_BGL_BmpWinGet_SizeX( lw->hed.win ) * 8),
			(u16)lw->hed.line_y );
	}
}



//------------------------------------------------------------------
//		リスト移動判定
//------------------------------------------------------------------
static u8 ListMoveUpDownCheck( BMPLIST_WORK * lw, u8 print_f, u8 req_line, u8 mode )
{
	u16	cursor_bak;	//消去カーソル位置
	u8	write_flg,write_req;	//転送フラグ
	u8	reqcount,linecount;		//処理カウント

	cursor_bak	= lw->cp;	//カーソル位置保存
	linecount = 0;
	write_req = 0;

	for(reqcount=0;reqcount<req_line;reqcount++){
		do{
			write_flg = ListCursorMoveUpDown( lw, mode );	//移動判定
			write_req |= write_flg;
			if(write_flg != 2){
				break;
			}
			linecount++;
		//カーソル位置がラベルにかからなくなるまで移動
		}while(lw->hed.list[lw->lp + lw->cp].param == BMPLIST_RABEL);
	}

	if(print_f){	//表示スイッチ
		//キャラデータ作成
		switch(write_req){
		//移動不可
		default:
		case 0:
			return 1;
			break;
		//カーソルのみ移動
		case 1:
			ListCursorCls( lw, cursor_bak );
			ListCursorPut( lw );
			CallBackSet( lw, 0 );
			GF_BGL_BmpWinOn( lw->hed.win );
			break;
		//表示リスト移動 or リスト＋カーソル移動
		case 2:
		case 3:
			ListCursorCls( lw, cursor_bak );
			ListScrollMoveUpDown( lw, linecount, mode );
			ListCursorPut( lw );
			CallBackSet( lw, 0 );
			GF_BGL_BmpWinOn( lw->hed.win );
			break;
		}
	}

	return 0;
}



//------------------------------------------------------------------
//		コールバック関数呼び出し(初期化時 mode = 1,通常動作時 mode = 0)
//------------------------------------------------------------------
static void CallBackSet( BMPLIST_WORK * lw, u8 mode )
{
	if( lw->hed.call_back != NULL){
		lw->hed.call_back( lw, lw->hed.list[lw->lp + lw->cp].param, mode );
	}
}



