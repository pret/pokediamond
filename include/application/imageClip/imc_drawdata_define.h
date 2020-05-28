//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_drawdata_define.h
 *	@brief		イメージクリップ描画データ定数郡
 *	@author		tomoya takahashi
 *	@data		2005.09.21
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __IMC_DRAWDATA_DEFINE_H__
#define __IMC_DRAWDATA_DEFINE_H__

#include "include/application/imageClip/imageclip.naix"
#include "include/system/arc_tool.dat"
#include "include/msgdata/msg.naix"
#include "include/msgdata/msg_imageclip.h"
#include "include/msgdata/msg_imageclip_acce.h"
#include "include/msgdata/msg_imageclip_bg.h"
#include "include/application/imageClip/imc_itemid_define.h"


#undef GLOBAL
#ifdef	__IMC_DRAWDATA_DEFINE_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
*	オブジェリスト用オブジェクトデータ定数
*/
//-----------------------------------------------------------------------------
enum{
	IMC_OBJLIST_ACCE,		// アクセサリオブジェクト
	IMC_OBJLIST_BG,			// BGサムネイルオブジェクト
	IMC_OBJLIST_SND,		// SNDサムネイルオブジェクト
	IMC_OBJLIST_POKE,		// ポケモンオブジェクト

	// アクセサリ　BGサムネイル　音サムネイル
	// は同じように管理するため
	// ポケモン以外での最大数も作成
	IMC_OBJLIST_ACCE_MAX = IMC_OBJLIST_POKE,
};




//-----------------------------------------------------------------------------
/**
 *				アクセサリ用定数宣言
*/
//-----------------------------------------------------------------------------
// アクセサリ入手可能数
#define IMC_ACCE_GET_9_NUM	( 61 )	// 9個もてるアクセサリの数
#define IMC_ACCE_GET_1_NUM	( 39 )// 1個しかもてないアクセサリの数
#define IMC_ACCE_GET_1_START	( IMC_ACCE_GET_9_NUM )


//-------------------------------------
//	
//	アクセサリ登録最大数
//	
//=====================================
#define IMC_SYS_ACCESSORIE_MAX				(700)					// アクセサリ登録最大数

//-------------------------------------
//	
//	アクセサリLinkデータアーカイブデータidx
//	
//=====================================
#define IMC_ACCESSORIE_PLTT_LINK	(NARC_imageclip_imc_ac_data_dat)

//-------------------------------------
//	
//	パレットファイル定数
//	
//=====================================
#define	IMC_DRAW_ACCESSORIE_PLTT_FILENUM	(1)						// パレットファイル数
#define	IMC_DRAW_ACCESSORIE_PLTT_NUM		(3)						// パレット使用数
#define IMC_DRAW_ACCESSORIE_PLTT_ID			(0)						// リソースマネージャパレットID

//-------------------------------------
//	
//	アーカイブデータ参照用マクロ
//	
//=====================================
#define IMC_DRAW_ACCESSORIE_PLTT_ARC	( NARC_imageclip_imgclip_access_NCLR )				// パレットアーカイブ先頭
#define IMC_DRAW_ACCESSORIE_CHAR_ARC	( NARC_imageclip_imgclip_access_001_0_NCBR )			// キャラクタアーカイブ先頭

// キャラクタアーカイブファイルナンバー取得
#define IMC_ACCE_ARC_NO_GET(x)		( (x) + IMC_DRAW_ACCESSORIE_CHAR_ARC )

//-------------------------------------
//	
//	フォントデータ用
//	
//=====================================
#define IMC_ACCE_FONT_START		(imgclipacc_001)
#define IMC_ACCE_FONT_NOGET(x)	( (x)+IMC_ACCE_FONT_START )
//BG
#define IMC_BG_FONT_START		(imgclipback_00)
#define IMC_BG_FONT_NOGET(x)	( (x)+IMC_BG_FONT_START )



//-----------------------------------------------------------------------------
/**
*		BGデータ
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
// BGデータ列挙
//	
//=====================================
// 左画面用
enum{
	IMC_BG_LEFT_00,
	IMC_BG_LEFT_01,
	IMC_BG_LEFT_MAX
};
// フレーム用
enum{
	IMC_BG_FRAME_00,
	IMC_BG_FRAME_01,
	IMC_BG_MAX
};

//-------------------------------------
//	
//	パレット管理用
//	
//=====================================
#define IMC_BG_COLOR_NUM		(1)	// 使用するパレットは1ポン


//-------------------------------------
//	
// アーカイブデータ管理用
//	
//=====================================
// アーカイブファイル開始位置
#define IMC_BG_RIGHT_ARC_S		(NARC_imageclip_imgclip_rback_00_NCGR)
#define IMC_BG_LEFT_ARC_S		(NARC_imageclip_imgclip_lback_00_NCGR)
#define IMC_BG_FRAME_ARC_S		(NARC_imageclip_imgclip_frame_00_NCGR)
#define IMC_BG_LEFT_FRAME_CL	(NARC_imageclip_imgclip_lback_frame_NCLR)

//-------------------------------------
//	
//	アーカイブデータ取得マクロ
//	
// 各データ取得マクロ
// ファイル名からこの順番でアーカイブされるため、このように管理しています。
// アーカイブ順番がファイル名ではなく任意に変えるような事があれば、この方式を
// 変える必要があります
//	
//=====================================
// 右画面
#define IMC_BG_RIGHT_CG_ARC_GET(x)	( ((x)*4)+IMC_BG_RIGHT_ARC_S )
#define IMC_BG_RIGHT_CL_ARC_GET(x)	( ((x)*4)+IMC_BG_RIGHT_ARC_S+1 )
#define IMC_BG_RIGHT_SC_ARC_GET(x)	( ((x)*4)+IMC_BG_RIGHT_ARC_S+2 )
#define IMC_BG_RIGHT_SC_ANM_ARC_GET(x)	( ((x)*4)+IMC_BG_RIGHT_ARC_S+3 )
// 左画面
#define IMC_BG_LEFT_CG_ARC_GET(x)	( ((x)*2)+IMC_BG_LEFT_ARC_S )
#define IMC_BG_LEFT_SC_ARC_GET(x)	( ((x)*2)+IMC_BG_LEFT_ARC_S+1 )
// フレーム画面
//#define IMC_BG_FRAME_CG_ARC_GET(x)	( IMC_BG_FRAME_ARC_S )
#define IMC_BG_FRAME_CG_ARC_GET(x)	( ((x)*2)+IMC_BG_FRAME_ARC_S )
//#define IMC_BG_FRAME_SC_ARC_GET(x)	( ((x))+IMC_BG_FRAME_ARC_S+1 )
#define IMC_BG_FRAME_SC_ARC_GET(x)	( ((x)*2)+IMC_BG_FRAME_ARC_S+1 )
// サムネイル用データ
//	パレットはBGと一緒の物を使用する
//
//
#define IMC_BG_THUMB_CG_ARC_S		(NARC_imageclip_imgclip_rback_thumb_00_NCBR)	// キャラクタデータアーカイブファイル先頭番号
#define IMC_BG_THUMB_CG_ARC_GET(x)	( (x) + IMC_BG_THUMB_CG_ARC_S )					// キャラクタデータアーカイブファイル番号を取得






//-----------------------------------------------------------------------------
/**
*		ボックスデータ
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
// ボックスのフレームの幅
//
//	フレーム部分の　絵で書いてあるフレーム
//	の幅
//	
//=====================================
#define IMC_BOX_AREA_FRAME_WIDHT	(2)
#define IMC_BOX_AREA_FRAME_HEIGHT	(2)

//-------------------------------------
//	
//	右ボックスエリア
//	
//=====================================
#define IMC_RBOX_AREA_X			( 136 )	
#define IMC_RBOX_AREA_Y			( 16 )		
#define IMC_RBOX_AREA_WIDTH		( 112 )
#define IMC_RBOX_AREA_HEIGHT	( 129 )

// 動作可能エリア
#define IMC_RBOX_AREA_X_MOVEOK		( IMC_RBOX_AREA_X + IMC_BOX_AREA_FRAME_WIDHT )	
#define IMC_RBOX_AREA_Y_MOVEOK		( IMC_RBOX_AREA_Y + IMC_BOX_AREA_FRAME_HEIGHT )
#define IMC_RBOX_AREA_WIDTH_MOVEOK	( IMC_RBOX_AREA_WIDTH - (IMC_BOX_AREA_FRAME_WIDHT*2) )
#define IMC_RBOX_AREA_HEIGHT_MOVEOK	( IMC_RBOX_AREA_HEIGHT - (IMC_BOX_AREA_FRAME_HEIGHT*2) )


//-------------------------------------
//	
//	左ボックスエリア
//	
//=====================================
#define IMC_LBOX_AREA_X	( 8 )	
#define IMC_LBOX_AREA_Y	( 16 )		
#define IMC_LBOX_AREA_WIDTH		( 112 )
#define IMC_LBOX_AREA_HEIGHT	( 129 )

// 動作可能エリア
#define IMC_LBOX_AREA_X_MOVEOK		( IMC_LBOX_AREA_X + IMC_BOX_AREA_FRAME_WIDHT )	
#define IMC_LBOX_AREA_Y_MOVEOK		( IMC_LBOX_AREA_Y + IMC_BOX_AREA_FRAME_HEIGHT )
#define IMC_LBOX_AREA_WIDTH_MOVEOK	( IMC_LBOX_AREA_WIDTH - (IMC_BOX_AREA_FRAME_WIDHT*2) )
#define IMC_LBOX_AREA_HEIGHT_MOVEOK	( IMC_LBOX_AREA_HEIGHT - (IMC_BOX_AREA_FRAME_HEIGHT*2) )


// ０以外なら１を返す
#define IMC_NUM_0_CHECK(x)	( (x) ? 1 : 0 )

//-------------------------------------
//	
//	左ボックス
//	リスト格納制限数
//	
//=====================================
// アクセサリリスト
// 必要なリスト数
#define IMC_LBOX_ACCE_NEAD_LIST_NUM	( 14 )
// この値までがリスト0
#define IMC_LBOX_ACCE_LIST00_END	( 5 )
// この値までがリスト1
#define IMC_LBOX_ACCE_LIST01_END	( 11 )
// この値までがリスト2
#define IMC_LBOX_ACCE_LIST02_END	( 17 )
// この値までがリスト3
#define IMC_LBOX_ACCE_LIST03_END	( 21 )
// この値までがリスト4
#define IMC_LBOX_ACCE_LIST04_END	( 28 )
// この値までがリスト5
#define IMC_LBOX_ACCE_LIST05_END	( 33 )
// この値までがリスト6
#define IMC_LBOX_ACCE_LIST06_END	( 38 )
// この値までがリスト7
#define IMC_LBOX_ACCE_LIST07_END	( 42 )
// この値までがリスト8
#define IMC_LBOX_ACCE_LIST08_END	( 49 )
// この値までがリスト9
#define IMC_LBOX_ACCE_LIST09_END	( 55 )
// この値までがリスト10
#define IMC_LBOX_ACCE_LIST10_END	( 60 )
// この値までがリスト11
#define IMC_LBOX_ACCE_LIST11_END	( 71 )
// この値までがリスト12
#define IMC_LBOX_ACCE_LIST12_END	( 91 )
// この値までがリスト13
#define IMC_LBOX_ACCE_LIST13_END	( 99 )

// BGサムネイルリスト
// 何種類ずつリストに分けるか
#define IMC_LBOX_BG_ONE_LIST_NUM	(9)
// あまりの数
#define IMC_LBOX_BG_REST_LIST_NUM	( (IMC_BG_RIGHT_MAX % IMC_LBOX_BG_ONE_LIST_NUM) )
// 必要なリスト数
#define IMC_LBOX_BG_NEAD_LIST_NUM	( (IMC_BG_RIGHT_MAX / IMC_LBOX_BG_ONE_LIST_NUM) + IMC_NUM_0_CHECK(IMC_LBOX_BG_REST_LIST_NUM) )

// 音サムネイルリスト
// 何種類ずつリストに分けるか
#define IMC_LBOX_SND_ONE_LIST_NUM	(9)
#define IMC_LBOX_SND_NEAD_LIST_NUM	(1)


//-----------------------------------------------------------------------------
/**
*		ボタン描画データ用
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	ボタン列挙
//	
//=====================================
enum{
	IMC_BTTN_RET,		// 左パレットをめくる
	IMC_BTTN_RETB,		// 左パレットをめくって戻す
	IMC_BTTN_ACE,		// アクセサリ変更に移る
	IMC_BTTN_BG,		// BG変更に移る
//	IMC_BTTN_SND,		// 音変更に移る
	IMC_BTTN_END,		// 終わる
	IMC_BTTN_MAX		// <-文字キャラクタのID
};
#define IMC_BTTN_NORM_MAX (IMC_BTTN_END)

//-------------------------------------
//	
//	パレット定義
//	
//=====================================
#define IMC_BTTN_ARC_FILE_PLTT	(NARC_imageclip_imgclip_button_NCLR)
#define IMC_BTTN_PLTT_LOAD_NUM	(3)
#define	IMC_BTTN_RES_MAN_PLTT	(0)	// リソースマネージャに登録するID

// OK文字フォント用
#define IMC_BTTN_ARC_FILE_PLTT_FONT		(NARC_imageclip_imgclip_button_font00_NCLR)
#define IMC_BTTN_PLTT_LOAD_NUM_FONT		(2)
#define IMC_BTTN_RES_MAN_PLTT_FONT	(1)	// リソースマネージャに登録するID

//-------------------------------------
//	
//	アーカイブファイル取得用マクロ
//	
//=====================================
// キャラクタ.セルファイルIDX開始位置
#define IMC_BTTN_ARC_FILE_CELL	(NARC_imageclip_imgclip_button_00_NANR)
// キャラクタ。セル。セルアニメ取得マクロ
#define IMC_BTTN_ARC_CANM_GET(x)	( ((x)*3) + IMC_BTTN_ARC_FILE_CELL + 0 )
#define IMC_BTTN_ARC_CELL_GET(x)	( ((x)*3) + IMC_BTTN_ARC_FILE_CELL + 1 )
#define IMC_BTTN_ARC_CHAR_GET(x)	( ((x)*3) + IMC_BTTN_ARC_FILE_CELL + 2 )


//-------------------------------------
//	
// 各種ボタン座標
// 各種ボタンサイズ
//	
//=====================================
// 各種ボタン座標
#define IMC_BTTN_Y		(144)
#define IMC_BTTN_RET_Y	(144)
#define IMC_BTTN_RET_X	(48)
#define IMC_BTTN_RETB_X	(8)
#define IMC_BTTN_ACE_X	(96)
#define IMC_BTTN_BG_X	(136)
#define IMC_BTTN_END_X	(184)

// 各種ボタンサイズ
#define IMC_BTTN_RET_SIZE_X		(40)
#define IMC_BTTN_RET_SIZE_Y		(32)
#define IMC_BTTN_NOR_SIZE_X		(42)
#define IMC_BTTN_NOR_SIZE_Y		(42)
#define IMC_BTTN_END_SIZE_X		(72)
#define IMC_BTTN_END_SIZE_Y		(42)

#define IMC_BTTN_HIT_Y_OFS	(8)
#define IMC_BTTN_HIT_Y_OFS_NOR_END	(12)

//-------------------------------------
//	
//	終了ボタン列挙
//	
//=====================================
enum{
	IMC_BTTN_ENDCK_CANCEL,	// キャンセル
	IMC_BTTN_ENDCK_END,		// 終わる
	IMC_BTTN_ENDCK_MAX		// <-文字キャラクタのID
};

//-------------------------------------
//	
//	アーカイブファイル取得用マクロ
//	
//=====================================
// キャラクタ.セルファイルIDX開始位置
#define IMC_BTTN_ENDCK_ARC_FILE_CELL	(NARC_imageclip_imgclip_button_04_NANR)
// キャラクタ。セル。セルアニメ取得マクロ
#define IMC_BTTN_ENDCK_ARC_CANM	( IMC_BTTN_ENDCK_ARC_FILE_CELL + 0 )
#define IMC_BTTN_ENDCK_ARC_CELL	( IMC_BTTN_ENDCK_ARC_FILE_CELL + 1 )
#define IMC_BTTN_ENDCK_ARC_CHAR	( IMC_BTTN_ENDCK_ARC_FILE_CELL + 2 )

// 各種ボタン座標
#define IMC_BTTN_ENDCK_Y				(144)
#define	IMC_BTTN_ENDCK_CHANCEL_X	(32)
#define IMC_BTTN_ENDCK_END_X		(168)

// 各種ボタンサイズ
#define IMC_BTTN_ENDCK_SIZE_X		(56)
#define IMC_BTTN_ENDCK_SIZE_Y		(32)


//-----------------------------------------------------------------------------
/**
*		サブウィンドウ描画データ定数
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	背景アーカイブデータ
//	
//=====================================
#define IMC_SUBWIN_CG_ARC	(NARC_imageclip_imgclip_top_00_NCGR)
#define IMC_SUBWIN_SC_ARC	(NARC_imageclip_imgclip_top_00_NSCR)
#define IMC_SUBWIN_PL_ARC	(NARC_imageclip_imgclip_top_00_NCLR)
#define IMC_SUBWIN_PL_NUM	(1)


//-------------------------------------
//	
//	ビットマップウィンドウ描画座標
//	
//=====================================
#define IMC_SUBWIN_BMP_X		(2)		// キャラ単位
#define IMC_SUBWIN_BMP_Y		(19)
#define IMC_SUBWIN_BMP_SIZE_X	(27)
#define	IMC_SUBWIN_BMP_SIZE_Y	(4)		
#define IMC_SUBWIN_BMP_WAKU_PLTT_NO	(1)				// フォント枠使用パレット番号
#define IMC_SUBWIN_BMP_PLTT_NO	(2)				// フォント使用パレット番号

#define IMC_SUBWIN_BMP_FRAME_CHAR_OFS	(1)

// ランク描画用
#define IMC_SUBWIN_RANKBMP_X		(2)		// キャラ単位
#define IMC_SUBWIN_RANKBMP_Y		(1)
#define IMC_SUBWIN_RANKBMP_SIZE_X	(27)
#define	IMC_SUBWIN_RANKBMP_SIZE_Y	(2)		
#define IMC_SUBWIN_RANKBMP_FRAME_CHAR_OFS	(IMC_SUBWIN_BMP_FRAME_CHAR_OFS +(IMC_SUBWIN_BMP_SIZE_X * IMC_SUBWIN_BMP_SIZE_Y) )

// ｶｳﾝﾀ描画用
#define IMC_SUBWIN_COUNTBMP_X		(10)		// キャラ単位
#define IMC_SUBWIN_COUNTBMP_Y		(8)
#define IMC_SUBWIN_COUNTBMP_SIZE_X	(14)
#define	IMC_SUBWIN_COUNTBMP_SIZE_Y	(4)		
#define IMC_SUBWIN_COUNTBMP_FRAME_CHAR_OFS	(IMC_SUBWIN_RANKBMP_FRAME_CHAR_OFS + (IMC_SUBWIN_RANKBMP_SIZE_X*IMC_SUBWIN_RANKBMP_SIZE_Y) )



//-----------------------------------------------------------------------------
/**
*	右ボックスプレイヤー
*/
//-----------------------------------------------------------------------------
// BGアニメタイミング
#define IMC_RBOX_PLAYER_BG_ANM_TIMING		(16)
#define IMC_RBOX_PLAYER_BG_ANM_FRAME		(1)


//-----------------------------------------------------------------------------
/**
*	オブジェクトリスト最大数
*/
//-----------------------------------------------------------------------------
#define	IMC_OBJLIST_MAX	(IMC_SYS_ACCESSORIE_MAX + 1 + IMC_BG_RIGHT_MAX)
// 内訳
//	アクセサリ	ポケモン１体	BGサムネイル
//	IMC_OBJLIST_TBL	作成などに使用
//
//	タッチぺんで選択したりするスプライトオブジェの数



//-----------------------------------------------------------------------------
/**
*		スプライトファイルデータ数
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	スプライトシステム
//	作成時などに使用する
//	データ登録最大数
//	
//=====================================
#define IMC_SPRITE_OBJ_NUM		(IMC_SYS_ACCESSORIE_MAX + IMC_BG_RIGHT_MAX)
#define	IMC_SPRITE_CHAR_NUM		(IMC_ACCE_MAX + IMC_BG_RIGHT_MAX)
#define	IMC_SPRITE_PLTT_NUM		(IMC_DRAW_ACCESSORIE_PLTT_FILENUM + IMC_BG_RIGHT_MAX)

//-------------------------------------
//	
//	ポケモンオブジェは別システム
//	しかし、キャラクタデータは
//	スプライトシステムの物と一緒に
//	管理するため定数を作成
//	現在キャラクタデータを保存しているもの
//	アクセサリ　ポケモン　BGサムネイル
//	
//=====================================
// ポケモン用キャラクタ登録ID
#define IMC_DRAW_POKE_CHAR_ID		(IMC_SPRITE_CHAR_NUM)	
// ポケモンも入れたキャラクタデータ数
#define IMC_SPRITE_OBJ_CHAR_NUM	(IMC_DRAW_POKE_CHAR_ID + 1)				

//-------------------------------------
//	
//	アクセサリの
//	キャラクタ・パレットデータを取得
//	するときのID（要素数）を取得
//	
//=====================================
#define IMC_ACCE_CHAR_CONT_ID(x)	( (x) )
#define IMC_ACCE_PLTT_CONT_ID(x)	( IMC_DRAW_ACCESSORIE_PLTT_ID)

//-------------------------------------
//	
//	BGサムネイルの
//	キャラクタ・パレットデータを取得
//	するときのID（要素数）を取得
//	
//=====================================
#define IMC_BG_THUMB_CHAR_CONT_ID(x)	( (x) + IMC_ACCE_MAX )
#define IMC_BG_THUMB_PLTT_CONT_ID(x)	( (x) + IMC_DRAW_ACCESSORIE_PLTT_FILENUM )	//アクセサリパレット１本分ずらす

//-------------------------------------
//	
//	SNDサムネイルの
//	キャラクタ・パレットデータを取得
//	するときのID（要素数）を取得
//	
//=====================================
#define IMC_SND_THUMB_CHAR_CONT_ID(x)	( (x) + IMC_ACCE_MAX )
#define IMC_SND_THUMB_PLTT_CONT_ID(x)	( (x) + IMC_DRAW_ACCESSORIE_PLTT_FILENUM )	//アクセサリパレット１本分ずらす



//-------------------------------------
//	
//	終了チェック画面ウィンドウメニュー用	
//	
//=====================================
#define IMC_ENDCHECK_YESNO_CHAR_OFFS	( 0 )	// YESNOボタンのキャラクタオフセット
#define IMC_ENDCHECK_YESNO_PLTT_OFFS	( 5 )	// 使用パレット
#define IMC_ENDCHECK_YESNO_X			( 25 )	// Xキャラ位置
#define IMC_ENDCHECK_YESNO_Y			( 4 )	// Yキャラ位置
#define IMC_ENDCHECK_WND_X				( 2 )	// Xキャラ位置
#define IMC_ENDCHECK_WND_Y				( 1 )	// Yキャラ位置
#define IMC_ENDCHECK_WND_SIZX			( 27 )	// Xキャラサイズ
#define IMC_ENDCHECK_WND_SIZY			( 2 )	// Yキャラサイズ
#define IMC_ENDCHECK_WND_PAL			( 7 )	// 使用パレット番号
#define IMC_ENDCHECK_WND_CHROFS			( 0+TOUCH_SW_USE_CHAR_NUM+TALK_WIN_CGX_SIZ )	// 使用キャラクタオフセット　キャラクタ単位
#define IMC_ENDCHECK_WND_PRICOLOR	( GF_PRINTCOLOR_MAKE(1,2,15) )	// カラーマスク
#define IMC_ENDCHECK_WNDWAKU_PAL		( 8 )	// 枠パレット
#define IMC_ENDCHECK_WNDWAKU_CHROFS		(0+TOUCH_SW_USE_CHAR_NUM)	// 枠キャラクタオフセット

// コンテスト説明用
#define IMC_CONTESTTEXT_WND_X				( 2 )	// Xキャラ位置
#define IMC_CONTESTTEXT_WND_Y				( 19 )	// Yキャラ位置
#define IMC_CONTESTTEXT_WND_SIZX			( 27 )	// Xキャラサイズ
#define IMC_CONTESTTEXT_WND_SIZY			( 4 )	// Yキャラサイズ

//-------------------------------------
//	ｴﾌｪｸﾄ動作定数
//=====================================
#define IMC_SEENFADE_BRIGHTNESS_FADE_SYNC	(8)
#define IMC_SEENFADE_MOVE_ADD_X				(8)
#define IMC_SEENFADE_MOVE_ADD_Y				(5)
#define IMC_SEENFADE_MOVE_COUNT				(8)
#define IMC_SEENFADE_BG_MOVE_Y				( IMC_SEENFADE_MOVE_ADD_Y * IMC_SEENFADE_MOVE_COUNT )
#define IMC_SEENFADE_BTTNMOVE_DIS			(64)
#define IMC_SEENFADE_BTTNMOVE_ADD_Y			(8)
#define IMC_SEENFADE_BTTNMOVE_COUNT			(8)

// 終了チェック画面での右ボックスグラフィックの描画位置
#define IMC_RBOX_END_SX						(IMC_RBOX_AREA_X - (IMC_SEENFADE_MOVE_ADD_X*IMC_SEENFADE_MOVE_COUNT))
#define IMC_RBOX_END_SY						(IMC_RBOX_AREA_Y + (IMC_SEENFADE_MOVE_ADD_Y*IMC_SEENFADE_MOVE_COUNT))


// セルアクターセットサブ面サーフェース位置
#define IMC_CLACT_SUB_SURFACE_Y	( 512*FX32_ONE )

//-------------------------------------
//	コンテストデータ
//=====================================
#define IMC_POKE_MAT_CONTEST_Y_OFS	( -4 )


//-----------------------------------------------------------------------------
/**
*		プロトタイプ宣言
*/
//-----------------------------------------------------------------------------


#undef	GLOBAL
#endif		// IMC_DRAWDATA_DEFINE_H__

