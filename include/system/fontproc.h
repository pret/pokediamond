#ifndef __FONTPROC_H__
#define __FONTPROC_H__

#include "gflib\fontdata_loadtype.h"
#include "gflib\msg_print.h"
#include "gflib\strbuf.h"

//--------------------------------------------------------------
/**
 *		フォントタイプ
 */
//--------------------------------------------------------------
typedef enum {
	FONT_SYSTEM = 0,
	FONT_TALK,
	FONT_BUTTON,
	FONT_UNKNOWN,

	FONT_MAX,

	// ------ 以下は make を通すために残す -----
	// ------ いずれ全て置き換えてもらいたい ---

	POKE_8x16 = FONT_SYSTEM,
	POKE_9x12 = FONT_SYSTEM,
	POKE_11x16 = FONT_TALK,
	POKE_SYS = FONT_SYSTEM,
	POKE_SYSTEM = FONT_SYSTEM,
	POKE_FNTEND = FONT_MAX,

}FONT_TYPE;


//--------------------------------------------------------------
/**
 * 戦闘ゲージOBJ用のフォント定義
 *		font_header_dataの配列データには必要ないので別に定義。
 *		数値だけは被らないようにする必要がある
 */
//--------------------------------------------------------------
#define POKE_8x12BATTLE		(POKE_FNTEND)

enum {
	FONT_HEADER_SIZE_X = 0,		// フォントXサイズ指定
	FONT_HEADER_SIZE_Y,			// フォントYサイズ指定
	FONT_HEADER_SPACE_X,		// 文字間隔X(初期設定)
	FONT_HEADER_SPACE_Y,		// 文字間隔Y(初期設定)
	FONT_HEADER_STYLE,			// フォントスタイル(初期設定)
	FONT_HEADER_F_COLOR,		// 文字色ナンバー
	FONT_HEADER_B_COLOR,		// 背景色ナンバー
	FONT_HEADER_S_COLOR			// 影色　ナンバー
};

#define	FONT_CURSOR_SIZE_X		( 0 )
#define	FONT_CURSOR_SIZE_Y		( 1 )


//------------------------------------------------------------------
/**
 * フォント処理システム初期化（メインで１度呼ぶだけ）
 *
 * @param   none		
 */
//------------------------------------------------------------------
extern void FontProcInit( void );


//------------------------------------------------------------------
/**
 * フォントデータをRAM上にロードする
 *
 * @param   font		フォントＩＤ
 * @param   heapID		ロードするヒープのＩＤ
 *
 */
//------------------------------------------------------------------
extern void FontProc_LoadFont( FONT_TYPE font, u32 heapID );

//------------------------------------------------------------------
/**
 * RAM上にロードされているフォントデータをアンロードする
 *
 * @param   font		フォントタイプ
 */
//------------------------------------------------------------------
extern void FontProc_UnloadFont( FONT_TYPE font );






//------------------------------------------------------------------
/**
 * フォントのビットデータをメモリに常駐させ、読み込み処理を高速化する
 *
 * @param   font			フォントID
 * @param   heapID			ビットデータ常駐用ヒープID
 *
 */
//------------------------------------------------------------------
extern void FontProc_LoadBitData( FONT_TYPE font, u32 heapID );

//------------------------------------------------------------------
/**
 * FontProc_LoadBitData で常駐させたビットデータを破棄し、
 * 逐次ファイル読み込み方式に戻す
 *
 * @param   font			フォントID
 *
 */
//------------------------------------------------------------------
extern void FontProc_UnloadBitData( FONT_TYPE font );




//------------------------------------------------------------------
/**
 * フォントBMPデータ１文字分をワークに読み込み、そのアドレスを渡す
 *
 * @param   font		フォントタイプ
 * @param   code		文字コード
 *
 * @retval  const MSG_FONT_DATA*		読み込み先アドレス
 */
//------------------------------------------------------------------
extern const MSG_FONT_DATA* FontDataGet( FONT_TYPE font, STRCODE code );


//--------------------------------------------------------------------------------------------
/**
 * フォントヘッダデータ取得
 *
 * @param	fnt_index	フォントインデックス
 * @param	param		取得パラメータ
 *
 * @return	指定されたパラメータ
 */
//--------------------------------------------------------------------------------------------
extern u8 FontHeaderGet( u8 fnt_index, u8 param );

//--------------------------------------------------------------------------------------------
/**
 * システムフォントパレット読み込み
 *
 * @param	type	パレット転送先タイプ
 * @param	offs	読み込みオフセット（バイト単位）
 * @param	heap	ヒープID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
extern void SystemFontPaletteLoad( u32 type, u32 offs, u32 heap );

//--------------------------------------------------------------------------------------------
/**
 * 会話フォントパレット読み込み
 *
 * @param	type	パレット転送先タイプ
 * @param	offs	読み込みオフセット（バイト単位）
 * @param	heap	ヒープID
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
extern void TalkFontPaletteLoad( u32 type, u32 offs, u32 heap );



//------------------------------------------------------------------
/**
 * フォントデータをウィンドウキャラワーク領域に描画
 *
 * @param   font		フォントタイプ
 * @param   ini			BGLシステムワーク
 * @param   mdh		
 *
 */
//------------------------------------------------------------------
extern PRINT_RESULT FontDataPrint( FONT_TYPE font, MSG_DATA_HEADER * mdh_p );


//------------------------------------------------------------------
/**
 * 文字列をビットマップ化した時の横幅取得
 *
 * @param   font		フォントタイプ
 * @param   str			文字列
 * @param   margin		字間（ドット）
 *
 * @retval  u32			横幅（ドット）
 */
//------------------------------------------------------------------
extern u32 FontProc_GetStrWidth( FONT_TYPE font, const STRCODE* str, u32 margin );
extern u32 FontProc_GetPrintStrWidth( FONT_TYPE font, const STRBUF* str, u32 margin );

//--------------------------------------------------------------------------------------------
/**
 * カーソルサイズ取得
 *
 * @param	fnt_index	フォントインデックス
 * @param	param		取得パラメータ
 *
 * @return	指定されたパラメータ
 */
//--------------------------------------------------------------------------------------------
extern u8 FontCursorSizeGet( u8 fnt_index, u8 param );


#endif
