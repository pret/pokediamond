//=============================================================================================
/**
 * @file	msg_print.h
 * @brief	ビットマップ文字列表示用システム
 * @author	tomo
 * @date	2004.10.28
 */
//=============================================================================================
#ifndef	__MSG_PRINT_H__
#define	__MSG_PRINT_H__

#include <nitro.h>
#include <nnsys.h>
#include "tcb.h"
#include "gflib\bg_system.h"
#include "gflib\strbuf.h"


#undef	GLOBAL
#ifdef	__MSG_PRINT_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//---------------------------------------------------------------------------------------------
/**
	定数定義
 */
//---------------------------------------------------------------------------------------------
typedef u16		STRCODE;

//---------------------------------------------------------------------------------------------
/// 色番号指定 PRINT のための定数・マクロ定義

typedef u32		GF_PRINTCOLOR;

#define  GF_PRINTCOLOR_MASK			(0xff)
#define  GF_PRINTCOLOR_LETTER_SHIFT	(16)
#define  GF_PRINTCOLOR_SHADOW_SHIFT	(8)
#define  GF_PRINTCOLOR_GROUND_SHIFT	(0)

// GF_MSG_PrintColor の引数 GF_PRINT_COLOR を作成するためのマクロ（ 文字色、影色、背景色の順に番号を渡す ）
#define  GF_PRINTCOLOR_MAKE(letter, shadow, ground)	(GF_PRINTCOLOR)(	(((letter)&GF_PRINTCOLOR_MASK) << GF_PRINTCOLOR_LETTER_SHIFT)|\
																		(((shadow)&GF_PRINTCOLOR_MASK) << GF_PRINTCOLOR_SHADOW_SHIFT)|\
																		(((ground)&GF_PRINTCOLOR_MASK) << GF_PRINTCOLOR_GROUND_SHIFT)	)

// GF_PRINTCOLOR_MAKE で作った値から各色番号を取り出すマクロ
#define GF_PRINTCOLOR_GET_LETTER(c)		(((c)>>GF_PRINTCOLOR_LETTER_SHIFT)&GF_PRINTCOLOR_MASK)
#define GF_PRINTCOLOR_GET_SHADOW(c)		(((c)>>GF_PRINTCOLOR_SHADOW_SHIFT)&GF_PRINTCOLOR_MASK)
#define GF_PRINTCOLOR_GET_GROUND(c)		(((c)>>GF_PRINTCOLOR_GROUND_SHIFT)&GF_PRINTCOLOR_MASK)

//---------------------------------------------------------------------------------------------
///メッセージ表示wait定義

#define	MSG_NO_PUT	(0xff)	//ディスプレイ転送なし
#define	MSG_ALLPUT	(0)		//ディスプレイ一括転送

//---------------------------------------------------------------------------------------------
///フォントデータ作成プログラム用返り値定義

typedef enum {
	PRINT_RESULT_WRITE = 0,
	PRINT_RESULT_END,
	PRINT_RESULT_LOOP,
	PRINT_RESULT_COMMAND,
}PRINT_RESULT;


//---------------------------------------------------------------------------------------------
/// FntDataColorGe() 用モード定義
enum COLOR_GET_MODE {
	COLOR_F,
	COLOR_S,
	COLOR_B
};

///表示文字列設定構造体
typedef struct mph_tag{
	union {
		const u16* msg;		//表示メッセージ
		const STRBUF* strbuf;
	};
	GF_BGL_BMPWIN * bmpwin;	//BMPウィンドウデータ

	u8		msg_index;		//メッセージインデックス

	u8		fnt_index;		//使用フォントINDEX
	u8		start_x;		//ウインドウ内表示開始Xオフセット
	u8		start_y;		//ウインドウ内表示開始Yオフセット

	u8		write_x;	//ウインドウ内描画Xオフセット
	u8		write_y;	//ウインドウ内描画Yオフセット
	u8		space_x;	//文字間隔
	u8		space_y;	//文字間隔

	u8		style;		//フォントスタイル
	u8		f_col;		//文字色ナンバー
	u8		b_col;		//背景色ナンバー
	u8		s_col;		//影色　ナンバー

	u16		dot_tbl;	//拡大用ドットテーブル
	u8		dot_wy;		//拡大時のY座標の描画補正値
	u8		dummy;

/*	4bit color mode
u8		style:4;	//フォントスタイル
u8		f_col:4;	//文字色ナンバー
u8		b_col:4;	//背景色ナンバー
u8		s_col:4;	//影色　ナンバー
u8		work[2];	//※数あわせで追加
*/
}MSG_PRINT_HEADER;

//---------------------------------------------------------------------------------------------
/**
 *	表示システム使用ワーク構造体
 */
//---------------------------------------------------------------------------------------------
#define MDH_WORKSIZE	(7)

// FALSEを返せばPrint処理を継続。TRUEを返すとPrintを中断してCallbackを呼び続ける
typedef  BOOL (*pStrPrintCallBack)(MSG_PRINT_HEADER*, u16);

typedef struct {
	MSG_PRINT_HEADER		mph;
	pStrPrintCallBack		call_back;
	u8		userwork[MDH_WORKSIZE];//ユーザーワーク
	u8		sw;			//動作スイッチ
	u8		seq;		//シーケンス
	u8		wait:7;		//文字描画ウェイト(0:一括～)
	u8		wait_flg:1;	//ウェイトフラグ 0=一括表示, 1=１文字ずつ表示
	u8		waitwork;	//ワーク(ウェイト)
	u8		scrwork;	//ワーク(スクロール)
	u8		msg_index;	//メッセージインデックス
	u8		callback_cont_flag;	// 連続コールバック呼び出しフラグ
	u16		callback_arg;	// コールバック関数に引き渡す値
//	void * trg_wk;
	void * disp_icon;	//操作画面変更アイコン
}MSG_DATA_HEADER;

//---------------------------------------------------------------------------------------------
/**
 *	表示文字データ構造体（クライアント設定）
 */
//---------------------------------------------------------------------------------------------
typedef struct {
u8		size_x;		//フォントXサイズ指定
u8		size_y;		//フォントYサイズ指定
u8		space_x;	//文字間隔(初期設定)
u8		space_y;	//文字間隔(初期設定)
u8		style;	//フォントスタイル(初期設定)
u8		f_col;	//文字色ナンバー
u8		b_col;	//背景色ナンバー
u8		s_col;	//影色　ナンバー
//u8		work[2];	//※数あわせで追加
}MSG_FONT_HEADER;


//---------------------------------------------------------------------------------------------
/**
 *	文字データ格納構造体
 */
//---------------------------------------------------------------------------------------------
typedef struct {
u8		data[0x20*4];
u8		size_x;	//表示Xサイズ
u8		size_y;	//表示Yサイズ
}MSG_FONT_DATA;



//---------------------------------------------------------------------------------------------
/**
 *	文字表示システム初期化関数(ユーザー設定)
 *
 * @param	フォント関数群ヘッダ
 *
 */
//---------------------------------------------------------------------------------------------
GLOBAL void	MSG_PrintSysInit( const MSG_FONT_HEADER* header );





extern u8 GF_STR_PrintSimple( GF_BGL_BMPWIN* win, u32 fontID, const STRBUF* msg, u32 xofs, u32 yofs, u32 wait, pStrPrintCallBack callback );

extern u8 GF_STR_PrintColor(
		GF_BGL_BMPWIN * win, u32 fontID, const STRBUF* msg, u32 xofs, u32 yofs, u32 wait,
		GF_PRINTCOLOR col, pStrPrintCallBack call_back );

extern u8 GF_STR_PrintExpand(
		GF_BGL_BMPWIN * win, u32 fontID, const STRBUF* msg, u32 xofs, u32 yofs, u32 wait,
		GF_PRINTCOLOR col, u32 xspc, u32 yspc, pStrPrintCallBack  call_back );

extern u8 GF_STR_Print( const MSG_PRINT_HEADER* mph_p, u32 wait, pStrPrintCallBack call_back );



//=============================================================================================
//文字表示システム関数
//=============================================================================================
//---------------------------------------------------------------------------------------------
/**
 *	文字表示初期化関数
 *
 * @param	なし
 *
 * @retval	なし
 */
//---------------------------------------------------------------------------------------------
GLOBAL void	MSG_PrintInit(void);
//---------------------------------------------------------------------------------------------
/*
 *	文字データ設定
 *
 * @param	radrs		読み込みデータ開始アドレス
 * @param	wadrs		書き込みデータバッファアドレス
 *
 * @retval	none
 */
//---------------------------------------------------------------------------------------------
GLOBAL void FntDataSet8x8_2bit(u32 radrs,u32 wadrs);

//---------------------------------------------------------------------------------------------
/*
 *	FntDataSet8x8_2bit を呼ぶ前に、色番号をセットしておく（高速化のため）
 *
 * @param	col_f	文字色番号
 * @param	col_b	背景色番号
 * @param	col_s	影色番号
 */
//---------------------------------------------------------------------------------------------
GLOBAL void FntDataColorSet(u8 col_f, u8 col_b, u8 col_s);

GLOBAL void FntDataColorBackUp(u8* col_f, u8* col_b, u8* col_s);
GLOBAL void FntDataColorRecover(u8* col_f, u8* col_b, u8* col_s);
//---------------------------------------------------------------------------------------------
/*
 *	FntDataColorSet で設定した色番号を取得
 *
 * @param	mode	モード（enum COLOR_GET_MODE : msg_print.h）
 *
 * @retval	色番号
 */
//---------------------------------------------------------------------------------------------
GLOBAL u8 FntDataColorGet(u8 mode);







//---------------------------------------------------------------------------------------------
/*
 * 終了チェック関数
 *
 * @param	msg_index	メッセージインデックス
 *
 * @retval	0	終了
 * @retval	1	処理中
 */
//---------------------------------------------------------------------------------------------
GLOBAL u8 GF_MSG_PrintEndCheck( u8 msg_index );

//---------------------------------------------------------------------------------------------
/*
 * １文字ごとの表示タスクを強制的に停止する
 *
 * @param	msg_index	メッセージインデックス
 */
//---------------------------------------------------------------------------------------------
GLOBAL void GF_STR_PrintForceStop( u8 msg_index );



GLOBAL void GF_MSG_PrintDispIcon( MSG_DATA_HEADER * mdh, u16 px, u16 py, u16 pat );




#undef	GLOBAL
#endif	/*	__MSG_PRINT_H__ */

