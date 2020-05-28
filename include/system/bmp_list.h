//=============================================================================
/**
 * @file	bmp_list.h	
 * @brief	ビットマップＢＧ上でのリスト表示システム
 * @author	GAME FREAK inc.
 * @date	tetsu
 */
//=============================================================================
#ifndef __BMP_LIST_H__
#define __BMP_LIST_H__


#include "bmp_menu_list.h"


#undef GLOBAL
#ifdef __BMP_LIST_H_GLOBAL__
#define GLOBAL /*	*/
#else
#define GLOBAL extern
#endif

#undef GLOBAL_WORK
#ifdef __BMP_LIST_H_GLOBAL__
#define GLOBAL_WORK //
#else
#define GLOBAL_WORK extern
#endif

/********************************************************************/
/*                                                                  */
/*				使用定義											*/
/*                                                                  */
/********************************************************************/
#define	BMPLIST_MAX		( 4 )		// 登録最大数（適当）


typedef struct _BMPLIST_WORK	BMPLIST_WORK;


///リストヘッダ構造体
typedef struct {
	const BMPLIST_DATA*	list;//表示文字データポインタ
	void	(*call_back)(BMPLIST_WORK * wk,u32 param,u8 mode);	//カーソル移動ごとのコールバック関数
	void	(*icon)(BMPLIST_WORK * wk,u32 param,u8 y);	//一列表示ごとのコールバック関数

	GF_BGL_BMPWIN * win;

	u16		count;		//リスト項目数
	u16		line;		//表示最大項目数
	u8		rabel_x;	//ラベル表示Ｘ座標
	u8		data_x;		//項目表示Ｘ座標
	u8		cursor_x;	//カーソル表示Ｘ座標
	u8		line_y:4;	//表示Ｙ座標
	u8		f_col:4;	//表示文字色
	u8		b_col:4;	//表示背景色
	u8		s_col:4;	//表示文字影色
	u16		msg_spc:3;	//文字間隔Ｘ
	u16		line_spc:4;	//文字間隔Ｙ
	u16		page_skip:2;//ページスキップタイプ
	u16		font:6;		//文字指定(本来は u8 だけど、そんなに作らないと思うので)
	u16		c_disp_f:1;	//ＢＧカーソル(allow)表示フラグ(0:ON,1:OFF)

	void * work;
}BMPLIST_HEADER;






///リストヘッダ定義
#define	BMPLIST_NO_SKIP		(0)
#define	BMPLIST_LRKEY_SKIP	(1)
#define	BMPLIST_LRBTN_SKIP	(2)

///リストアトリビュート構造体
typedef struct {
	u8		pos_x;		//開始Ｘ座標オフセット(キャラ単位)
	u8		pos_y;		//開始Ｙ座標オフセット(キャラ単位)
	u8		siz_x;		//Ｘサイズ(キャラ単位)
	u8		siz_y;		//Ｙサイズ(キャラ単位)
	u8		pal;		//指定パレット
}BMPLIST_ATTR;

///リストパラメータ＆返り値定義
#define	BMPLIST_NULL	(0xffffffff)
#define	BMPLIST_CANCEL	(0xfffffffe)
#define	BMPLIST_RABEL	(0xfffffffd)


// パラメータ取得・変更ＩＤ
enum {
	BMPLIST_ID_CALLBACK = 0,	///<カーソル移動ごとのコールバック関数
	BMPLIST_ID_ICONFUNC,		///<一列表示ごとのコールバック関数
	BMPLIST_ID_COUNT,			///<リスト項目数
	BMPLIST_ID_LINE,			///<表示最大項目数
	BMPLIST_ID_INDEX,			///<使用ビットマップＩＮＤＥＸ
	BMPLIST_ID_RABEL_X,			///<ラベル表示Ｘ座標
	BMPLIST_ID_DATA_X,			///<項目表示Ｘ座標
	BMPLIST_ID_CURSOR_X,		///<カーソル表示Ｘ座標
	BMPLIST_ID_LINE_Y,			///<表示Ｙ座標
	BMPLIST_ID_LINE_YBLK,       ///<１行分シフト量取得(フォントの大きさ＋Ｙ間隔)
	BMPLIST_ID_F_COL,			///<表示文字色
	BMPLIST_ID_B_COL,			///<表示背景色
	BMPLIST_ID_S_COL,			///<表示文字影色
	BMPLIST_ID_MSG_SPC,			///<文字間隔Ｘ
	BMPLIST_ID_LINE_SPC,		///<文字間隔Ｙ
	BMPLIST_ID_PAGE_SKIP,		///<ページスキップタイプ
	BMPLIST_ID_FONT,			///<文字指定
	BMPLIST_ID_C_DISP_F,		///<ＢＧカーソル(allow)表示フラグ
	BMPLIST_ID_WIN,				///<ウィンドウデータ
	BMPLIST_ID_WORK				///<ワーク
};

// 移動方向
enum {
	BMPLIST_MOVE_NONE = 0,	// 動作なし
	BMPLIST_MOVE_UP,		// 上へ移動
	BMPLIST_MOVE_DOWN,		// 下へ移動
	BMPLIST_MOVE_UP_SKIP,	// 上へ移動（スキップ）
	BMPLIST_MOVE_DOWN_SKIP,	// 下へ移動（スキップ）
};


/********************************************************************/
/**
 *					簡易リスト関数
 *
 * @param	bmpdata		リスト用ビットマップデータポインタ
 * @param	bmplist		表示リストヘッダポインタ
 * @param	mode		標準ウインドウ枠表示スイッチ
 *							EASYBMPLIST_NO_FRAME	枠なし
 *							EASYBMPLIST_SCRFRAME	枠あり、キャラ転送なし
 *							EASYBMPLIST_ALLFRAME	枠、キャラ転送あり
 * @param	cgx			枠ＣＧＸ転送オフセット
 * @param	pal			枠ＰＡＬ転送オフセット(palanm.h の定義に準拠)
 *
 * @retval	param		BMPLIST_NULLでなければ、選択された項目パラメータ
 */
/********************************************************************/
#define	EASYBMPLIST_NO_FRAME	(0)
#define	EASYBMPLIST_SCRFRAME	(1)
#define	EASYBMPLIST_ALLFRAME	(2)



/*u32	BmpListEasy
(const BMPWIN_DAT *bmpdata,const BMPLIST_HEADER *bmplist,u8 mode,u16 cgx,u16 pal);
*/

/********************************************************************/
/**
 *					設定関数（拡張）
 *
 * @param	bmplist		表示リストヘッダポインタ
 * @param	bmplist		表示リストパレットアトリビュートポインタ
 * @param	list_p		リスト初期位置
 * @param	cursor_p	カーソル初期位置
 *
 * @retval	id			リストＩＤ(=work_id)
 *						※メイン関数の引数となるので管理を忘れずに
 *
 * call_back 設定に関して、この関数からの引数は 
 *   BMPLIST_DATA 構造体 param
 * となる
 */
/********************************************************************/
/*
GLOBAL u8		BmpListSetExpand
	(const BMPLIST_HEADER* bmplist,const BMPLIST_ATTR* bmpattr,u16 list_p,u16 cursor_p);
*/










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
GLOBAL BMPLIST_WORK * BmpListSet(
						const BMPLIST_HEADER * bmplist, u16 list_p, u16 cursor_p, u8 mode );

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
GLOBAL u32 BmpListMain( BMPLIST_WORK * lw );

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
GLOBAL void BmpListExit( BMPLIST_WORK * lw, u16 * list_bak, u16 * cursor_bak );

//--------------------------------------------------------------------------------------------
/**
 * リスト再描画
 *
 * @param	lw		BMPリストワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void BmpListRewrite( BMPLIST_WORK * lw );

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
GLOBAL void BmpListColorControl( BMPLIST_WORK * lw, u8 f_col, u8 b_col, u8 s_col );

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
GLOBAL void BmpListMoveControl( BMPLIST_WORK * lw, u8 x, u8 y );

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
GLOBAL u32 BmpListMainOutControlEx(
			BMPLIST_WORK * lw, BMPLIST_HEADER * bmplist,
			u16 list_p, u16 cursor_p, u16 print, u16 direct, u16 * list_bak, u16 * cursor_bak );

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
GLOBAL u32 BmpListMainOutControl(
				BMPLIST_WORK * lw, BMPLIST_HEADER * bmplist,
				u16 list_p, u16 cursor_p, u16 direct, u16 * list_bak, u16 * cursor_bak );

//--------------------------------------------------------------------------------------------
/**
 * BMP_MENULIST_DATAを再度設定する
 *
 * @param	BMP_MENULIST_DATA			BMPMENUリストポインタ
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void BmpListSetMenuListData(BMPLIST_WORK * lw, BMP_MENULIST_DATA* pList);

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
GLOBAL void BmpListTmpColorChange( BMPLIST_WORK * lw, u8 f_col, u8 b_col, u8 s_col );

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
GLOBAL void BmpListDirectPosGet( BMPLIST_WORK * lw, u16 * pos_bak );

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
GLOBAL void BmpListPosGet( BMPLIST_WORK * lw, u16 * list_bak, u16 * cursor_bak );

//--------------------------------------------------------------------------------------------
/**
 * BMPリストのカーソルY座標を取得
 *
 * @param	lw		BMPリストワーク
 *
 * @return	カーソルY座標
 */
//--------------------------------------------------------------------------------------------
GLOBAL u16 BmpListCursorYGet( BMPLIST_WORK * lw );

//--------------------------------------------------------------------------------------------
/**
 * BMPリストのカーソル移動方向取得
 *
 * @param	lw		BMPリストワーク
 *
 * @return	カーソル移動方向取得
 */
//--------------------------------------------------------------------------------------------
GLOBAL u8 BmpListMoveSiteGet( BMPLIST_WORK * lw );

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
GLOBAL u32 BmpListPosParamGet( BMPLIST_WORK * lw, u16 pos );

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
GLOBAL u32	BmpListParamGet( BMPLIST_WORK * lw, u8 mode );

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
GLOBAL void BmpListParamSet( BMPLIST_WORK * lw, u8 mode, u32 param );



#undef GLOBAL_WORK
#undef GLOBAL

#endif
