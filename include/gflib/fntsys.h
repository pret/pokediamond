#ifndef __FNTSYS_H__
#define __FNTSYS_H__

#include "gflib\bg_system.h"
#include "gflib\msg_print.h"





//------------------------------------------------------------------
/**
 * タグコード開始箇所のポインタを受け取り、タグ種類コードを返す
 *
 * @param   str		文字列ポインタ
 *
 * @retval  u32		タグ種類コード
 */
//------------------------------------------------------------------
extern u32  STRCODE_GetTagType( const STRCODE* str );

//------------------------------------------------------------------
/**
 * タグコード開始箇所のポインタを受け取り、タグ内容が単語セットタグか調べる
 *
 * @param   str			文字列ポインタ
 *
 * @retval  BOOL		TRUEなら単語セットタグ
 */
//------------------------------------------------------------------
extern BOOL STRCODE_CheckWordSetTagType( const STRCODE* str );

//------------------------------------------------------------------
/**
 * タグコード箇所のポインタを受け取り、パラメータ値を読み取って返す
 *
 * @param   str			文字列ポインタ
 * @param   param_no	パラメータナンバー（0 org）
 *
 * @retval  u32		パラメータ値
 */
//------------------------------------------------------------------
extern u32  STRCODE_GetTagParam( const STRCODE* str, u32 param_no );

//------------------------------------------------------------------
/**
 * タグコード開始箇所のポインタを受け取り、パラメータ部をスキップして返す
 *
 * @param   str			文字列ポインタ
 *
 * @retval  STRCODE*	パラメータ部スキップ後のポインタ
 */
//------------------------------------------------------------------
extern STRCODE*  STRCODE_SkipTag( const STRCODE* str );

#if 0
//---------------------------------------------------------------------------------------------
/*
 *	文字コード変換　ポケモンＡＧＢ->ポケモンＤＳ
 *	※通常文字、終了、改行、トリガー待ち、バッファメッセージに対応
 *
 * @param	c_id		国番号(0:日本,1:....)
 * @param	agb_str		入力するＡＧＢ文字列のポインタ
 * @param	ds_str		出力するＤＳ文字列のポインタ
 *
 * @retval	ret		0:問題なし,1:解釈不可能なコードがあった（変換失敗）
 */
//---------------------------------------------------------------------------------------------
extern u8	GBAcode2DSuni(u8 c_id, u8 *agb_str, STRCODE *ds_str);

//---------------------------------------------------------------------------------------------
/*
 *	文字コード変換　ポケモンＤＳ->ポケモンＡＧＢ
 *	※通常文字、終了、改行、トリガー待ち、バッファメッセージに対応
 *
 * @param	c_id		国番号(0:日本,1:....)
 * @param	ds_str		入力するＤＳ文字列のポインタ
 * @param	agb_str		出力するＡＧＢ文字列のポインタ
 *
 * @retval	ret		0:問題なし,1:解釈不可能なコードがあった（変換失敗）
 */
//---------------------------------------------------------------------------------------------
extern u8	DSuni2GBAcode(u8 c_id, STRCODE *ds_str, u8 *agb_str);
#endif
#ifdef PM_DEBUG
//---------------------------------------------------------------------------------------------
/*
 *	文字コード変換　ASCII->ポケモンＤＰ
 *	※通常文字、終了、改行対応
 *	　トリガー待ち、バッファメッセージ、その他ポケモン特殊コード非対応
 *
 *	デバッグ専用です！
 * 
 * @param	c_id		国番号(0:日本,1:....)　非対応
 * @param	agb_str		入力するASCII文字列のポインタ
 * @param	ds_str		出力するDS文字列のポインタ
 *
 * @retval	ret		0:問題なし,1:解釈不可能なコードがあった（変換失敗）
 */
//---------------------------------------------------------------------------------------------
extern u8	ASCIIcode2DSuni(u8 c_id, u8 *ascii_str, u16 *ds_str);
#endif	//PM_DEBUG

//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------
/* 文字列表示制御コードの定義 */
#include "strcode.h"


#define CR_				0xe000		/* 改行コード */




//=============================================================================================
//	仮コード
//=============================================================================================
//=============================================================================================
//=============================================================================================

/* 文字列表示制御コードの定義 */
#define S_MSG_			0xf0f7		/* 指定バッファのメッセージ展開(任意)*/
#define	EXICON_			0xf0f8		/* 拡張アイコン(キーアイコン) */

#define I_MSG_			0xf0fd		/* 指定バッファのメッセージ展開(ID)	*/
#define CTRL_			0xf0fc		/* フォント制御コマンド */

#define	NORMAL_WAIT_	0x25bc		/* "▼"		トリガー待ち→MSGエリアクリア	*/
#define	SCROLL_WAIT_	0x25bd		/* "▽"		トリガー待ち→一行スクロール */
#define	SIMPLE_WAIT_	0x25a0		/* "■"		トリガー待ちのみ */

#define	C_FCOL_		0xf001		/* フォント制御サブコマンド:文字色変更 */
#define	C_BCOL_		0xf002		/* フォント制御サブコマンド:背景色変更 */
#define C_SCOL_		0xf003		/* フォント制御サブコマンド:影色変更 */
#define C_ACOL_		0xf004		/* フォント制御サブコマンド:全色指定変更(パラメータはFBSの順) */
#define C_PAL_		0xf005		/* フォント制御サブコマンド:パレット変更 */
#define C_FCHG_		0xf006		/* フォント制御サブコマンド:フォント変更 */
#define C_FNML_		0xf007		/* フォント制御サブコマンド:フォント復帰 */
#define	C_WAIT_		0xf008		/* フォント制御サブコマンド:ウェイトセット */
#define C_TRGWAIT_	0xf009		/* フォント制御サブコマンド:キーウェイト */
#define C_SEWAIT_	0xf00a		/* フォント制御サブコマンド:SEの鳴り終わりまで待つ */
#define C_MUSPLAY_	0xf00b		/* フォント制御サブコマンド:BGMをならす */
#define C_EXFONT_	0xf00c		/* フォント制御サブコマンド:拡張フォント指定 */
#define C_XCHG_		0xf00d		/* フォント制御サブコマンド:表示X位置移動 */
#define C_YCHG_		0xf00e		/* フォント制御サブコマンド:表示Y位置移動 */
#define C_CLR_		0xf00f		/* フォント制御サブコマンド:MSGエリアクリア */
#define C_SEPLAY_	0xf010		/* フォント制御サブコマンド:SEをならす */

//サブコード0x11～0x16	は海外版サブコード
#define C_STRUT_	0xf011		/* 引数１ */
#define C_OFSX_		0xf012		/* 引数１ */
#define C_BLANK_	0xf013		/* 引数１ */
#define C_WIDTH_	0xf014		/* 引数１ */
#define C_LANG_JP	0xf015		/* 引数なし */
#define C_LANG_DEF	0xf016		/* 引数なし */

#define C_MUSPAUSE_	0xf017		/* フォント制御サブコマンド:BGMをPAUSE */
#define C_MUSCONTINUE_	0xf018	/* フォント制御サブコマンド:BGMをCONTINUE */

#define	C_FSIZCHG_		0xf019	/* フォントサイズ変更（ドット制御） */
#define	C_FSIZCHG2_		0xf01a	/* フォントサイズ変更（ドット制御（２倍）） */
#define	C_FSIZCHGEND_	0xf01b	/* フォントサイズ変更終了（ドット制御） */

#define C_DCOL_			0xf01c	/* フォント制御サブコマンド:一括指定変更(FS) */


//=============================================================================================
//	定数
//=============================================================================================
// C_FSIZCHG_で制御するドット位置
#define	FSIZ_1PLUS_		( 0x0080 )	// 0000_0000_1000_0000
#define	FSIZ_2PLUS_		( 0x0440 )	// 0000_0010_0010_0000
#define	FSIZ_3PLUS_		( 0x0490 )	// 0000_0100_1001_0000
#define	FSIZ_4PLUS_		( 0x2490 )	// 0010_0100_1001_0000
#define	FSIZ_5PLUS_		( 0x1294 )	// 0001_0010_1001_0100
#define	FSIZ_6PLUS_		( 0x1554 )	// 0001_0101_0101_0100
#define	FSIZ_7PLUS_		( 0x3554 )	// 0011_0101_0101_0100
#define	FSIZ_8PLUS_		( 0x355c )	// 0011_0101_0101_1100
#define	FSIZ_9PLUS_		( 0x357c )	// 0011_0101_0111_1100
#define	FSIZ_10PLUS_	( 0x377c )	// 0011_0111_0111_1100
#define	FSIZ_11PLUS_	( 0x37fc )	// 0011_0111_1111_1100
#define	FSIZ_12PLUS_	( 0x3ffc )	// 0011_1111_1111_1100
#define	FSIZ_13PLUS_	( 0x7ffc )	// 0111_1111_1111_1100
#define	FSIZ_14PLUS_	( 0x7ffe )	// 0111_1111_1111_1110
#define	FSIZ_15PLUS_	( 0xfffe )	// 1111_1111_1111_1110
#define	FSIZ_16PLUS_	( 0xffff )	// 1111_1111_1111_1111

// 通常のフォントカラー
#define	FBMP_COL_NULL		(0)
#define	FBMP_COL_BLACK		(1)
#define	FBMP_COL_BLK_SDW	(2)
#define	FBMP_COL_RED		(3)
#define	FBMP_COL_RED_SDW	(4)
#define	FBMP_COL_GREEN		(5)
#define	FBMP_COL_GRN_SDW	(6)
#define	FBMP_COL_BLUE		(7)
#define	FBMP_COL_BLU_SDW	(8)
#define	FBMP_COL_PINK		(9)
#define	FBMP_COL_PNK_SDW	(10)

#define	FBMP_COL_WHITE		(15)

//#define	FBMP_COL_WHT_SDW	(2)
//#define	FBMP_COL_YELLOW		(11)
//#define	FBMP_COL_YLW_SDW	(12)

// C_DCOL_で制御する色 ( (文字色<<4) + (影色) )
#define	DCOL_BLACK_		( ( FBMP_COL_BLACK << 4 ) + FBMP_COL_BLK_SDW )	// 黒
//#define	DCOL_WHITE_		( ( FBMP_COL_WHITE << 4 ) + FBMP_COL_WHT_SDW )	// 白
#define	DCOL_BLUE_		( ( FBMP_COL_BLUE << 4 ) + FBMP_COL_BLU_SDW )	// 青
#define	DCOL_RED_		( ( FBMP_COL_RED << 4 ) + FBMP_COL_RED_SDW )	// 赤
#define	DCOL_PINK_		( ( FBMP_COL_PINK << 4 ) + FBMP_COL_PNK_SDW )	// ピンク
//#define	DCOL_YELLOW_	( ( FBMP_COL_YELLOW << 4 ) + FBMP_COL_YLW_SDW )	// 黄
#define	DCOL_GREEN_		( ( FBMP_COL_GREEN << 4 ) + FBMP_COL_GRN_SDW )	// 緑



//============================================================================================
//	任天堂ツール　テストコード
//============================================================================================
#define	_CTRL_TAG		0xfffe			// タグコード

#define	NC_FONT_COL_	0xff00			// フォント制御コード
#define	NC_FONT_SIZE_	0xff01			// フォント制御コード
#define	NC_MOVE_		0xfe06			// 動作制御コード

#define	NC_FCOL_BLACK_	0x0000		// 文字色：黒
#define	NC_FCOL_RED_	0x0001		// 文字色：赤

#define	NC_FAFF_100_	0x0064		// サイズ：100％
#define	NC_FAFF_200_	0x00c8		// サイズ：200％

#define	NC_MV_CLEAR_	0xfe01			// キー待ちクリア
#define	NC_MV_SCROLL_	0xfe00			// キー待ちスクロール

#define NC_WORDSET_MASK		0xff00
#define NC_WORDSET			0x0100

#define NC_NOTE_ICON			(0x0200)	// 注目アイコン
#define NC_FORCE_WAIT			(0x0201)	// 次の文字を表示する前の強制ウェイトフレーム
#define NC_CALLBACK_ARG			(0x0202)
#define NC_WRITEPOS_CHANGE_X	(0x0203)
#define NC_WRITEPOS_CHANGE_Y	(0x0204)

#define NC_ACTIVE_ICON_	0xff02

/*
001a ff08 0000 0001 色変更：赤
001a ff08 0000 0000 色変更：黒
001a ff08 0001 00c8 サイズ：200％
001a fe06 fe01 		キー待ちクリア
001a fe06 fe00		キー待ちスクロール
*/


#endif
