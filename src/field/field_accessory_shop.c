//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		field_accessory_shop.c
 *	@brief		アクセサリー交換所
 *	@author		tomoya takahashi
 *	@data		2006.06.06
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "common.h"
#include "talk_msg.h"
#include "include/savedata/config.h"
#include "include/savedata/imageclip_data.h"
#include "include/itemtool/myitem.h"
#include "include/itemtool/nuts.h"

#include "include/system/wordset.h"
#include "include/system/msgdata.h"

#include "include/msgdata/msg.naix"
#include "include/msgdata/msg_t03r0101.h"

#include "include/system/window.h"
#include "include/system/bmp_menu.h"
#include "include/system/fontproc.h"

#include "include/system/arc_util.h"

#include "fieldmap.h"

#include "include/system/bmp_list.h"
#include "include/application/imageClip/imc_drawdata_define.h"

#include "system/snd_play.h"
#include "system/snd_tool.h"

// リスト上下アイコン用
#include "shop_gra.naix"


//////// accessoryショップデータ
#include "acce_shop.dat"


#define __FIELD_ACCESSORY_SHOP_H_GLOBAL
#include "field_accessory_shop.h"

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
//-------------------------------------
//	セルアクター
//=====================================
#define ACCE_SHOP_CLACT_WORK_NUM	( 2 )



//-------------------------------------
//	常駐キャラクタ　パレット位置
//=====================================
#define ACCE_SHOP_TALK_CHAROFS		( 1 )
#define ACCE_SHOP_TALK_PLTT			( 10 )
#define ACCE_SHOP_SYSTEM_CHAROFS	( 1+TALK_WIN_CGX_SIZ )
#define ACCE_SHOP_SYSTEM_PLTT		( 11 )
#define ACCE_SHOP_TALKFONT_PLTT			( 12 )
#define ACCE_SHOP_SYSTEMFONT_PLTT		( 13 )

#define ACCE_SHOP_FONTBMP_TALK_COLOR		( GF_PRINTCOLOR_MAKE(1,2,15) )
#define ACCE_SHOP_FONTBMP_SYS_COLOR			( GF_PRINTCOLOR_MAKE(1,2,15) )


//-------------------------------------
//	メインメッセージ構造体定数
//=====================================
#define ACCE_SHOP_MAIN_MSGWIN_X		( 2 )
#define ACCE_SHOP_MAIN_MSGWIN_Y		( 19 )
#define ACCE_SHOP_MAIN_MSGWIN_SX	( 27 )
#define ACCE_SHOP_MAIN_MSGWIN_SY	( 4 )
#define ACCE_SHOP_MAIN_MSGWIN_CHAR	( ACCE_SHOP_SYSTEM_CHAROFS+MENU_WIN_CGX_SIZ )
#define ACCE_SHOP_MAIN_MSGWIN_PLTT	( ACCE_SHOP_TALKFONT_PLTT )

//-------------------------------------
//	データ画面構造体定数
//=====================================
#define ACCE_SHOP_DATA_WINWIN_X		( 1 )
#define ACCE_SHOP_DATA_WINWIN_Y		( 11 )
#define ACCE_SHOP_DATA_WINWIN_SX	( 14 )
#define ACCE_SHOP_DATA_WINWIN_SY	( 6 )
#define ACCE_SHOP_DATA_WINWIN_CHAR	( ACCE_SHOP_MAIN_MSGWIN_CHAR + (ACCE_SHOP_MAIN_MSGWIN_SX*ACCE_SHOP_MAIN_MSGWIN_SY) )
#define ACCE_SHOP_DATA_WINWIN_PLTT	( ACCE_SHOP_SYSTEMFONT_PLTT )
enum{
	ACCE_SHOP_DATA_WIN_NUTS_NAME,
	ACCE_SHOP_DATA_WIN_NUTS_NEED,
	ACCE_SHOP_DATA_WIN_NUTS_HAVE,
	ACCE_SHOP_DATA_WIN_NUM,
};
#define ACCE_SHOP_DATA_WINWIN_DRAW_YOFS	( 16 )


//-------------------------------------
//	accessoryリスト構造体定数
//=====================================
#define ACCE_SHOP_LIST_WINWIN_X		( 17 )
#define ACCE_SHOP_LIST_WINWIN_Y		( 1 )
#define ACCE_SHOP_LIST_WINWIN_SX	( 14 )
#define ACCE_SHOP_LIST_WINWIN_SY	( 16 )
#define ACCE_SHOP_LIST_WINWIN_CHAR	( ACCE_SHOP_DATA_WINWIN_CHAR + (ACCE_SHOP_DATA_WINWIN_SX*ACCE_SHOP_DATA_WINWIN_SY) )
#define ACCE_SHOP_LIST_WINWIN_PLTT	( ACCE_SHOP_SYSTEMFONT_PLTT )

#define ACCE_SHOP_LIST_WIN_DRAWLINE		( 7 )	// 表示ライン
#define ACCE_SHOP_LIST_WIN_DATA_X		( 16 )	// 項目表示位置
#define ACCE_SHOP_LIST_WIN_CURSOR_X		( 0 )	// カーソル表示位置
#define ACCE_SHOP_LIST_WIN_DRAW_Y		( 8 )	// 表示開始Y座標
#define ACCE_SHOP_LIST_WIN_FONT_COL_F	( 1 )	// 文字色
#define ACCE_SHOP_LIST_WIN_FONT_COL_B	( 15 )	// 背景色
#define ACCE_SHOP_LIST_WIN_FONT_COL_S	( 2 )	// 影色
#define ACCE_SHOP_LIST_WIN_MSG_SPC		( 0 )	// 文字間隔
#define ACCE_SHOP_LIST_WIN_LINE_SPC		( 0 )	// ライン間隔
#define ACCE_SHOP_LIST_WIN_PAGE_SKIP	( FALSE )	// スキップ
#define ACCE_SHOP_LIST_WIN_FONT			( FONT_SYSTEM )	// 文字タイプ
#define ACCE_SHOP_LIST_WIN_DISP			( 0 )

#define ACCE_SHOP_LIST_WIN_CLACT_RESNUM	( 4 )	// キャラ　パレット　セル　セルアニメ
#define ACCE_SHOP_LIST_WIN_CLACT_RESMAN_WORKNUM	( 1 )	// リソースマネージャワーク
#define ACCE_SHOP_LIST_WIN_CLACT_RESCONT_ID	( 5000 )
#define ACCE_SHOP_LIST_WIN_CLACT_OBJNUM	( 2 )

#define ACCE_SHOP_LIST_WIN_CLACT_X		( 192 )
#define ACCE_SHOP_LIST_WIN_CLACT_Y_0	( 8 )
#define ACCE_SHOP_LIST_WIN_CLACT_Y_1	( 136 )


//-------------------------------------
//	YESNOウィンドウ
//=====================================
#define ACCE_SHOP_YESNO_WIN_X	( 24 )		// ｘ位置
#define ACCE_SHOP_YESNO_WIN_Y	( 13 )		// ｙ位置
#define ACCE_SHOP_YESNO_WIN_SX	( 7 )		// ｘサイズ
#define ACCE_SHOP_YESNO_WIN_SY	( 4 )		// yサイズ
#define ACCE_SHOP_YESNO_WIN_CHAR	( ACCE_SHOP_LIST_WINWIN_CHAR + (ACCE_SHOP_LIST_WINWIN_SX*ACCE_SHOP_LIST_WINWIN_SY) )
#define ACCE_SHOP_YESNO_WIN_PLTT	( ACCE_SHOP_SYSTEMFONT_PLTT )




//-------------------------------------
//	全体シーケンス
//=====================================
enum{
	ACCE_SHOP_SEQ_STARTMSG,			// こんにちは！
	ACCE_SHOP_SEQ_FULLHAVE_CHECK,	// 全てのアクセサリーを持っているかチェック
	ACCE_SHOP_SEQ_LIST_START,		// リスト画面の開始
	ACCE_SHOP_SEQ_LIST_RESTART,		// リスト画面の再開始
	ACCE_SHOP_SEQ_LIST_MAIN,		// リスト処理メイン

	ACCE_SHOP_SEQ_YESNO_START,		// ハイイイエ
	ACCE_SHOP_SEQ_YESNO_MAIN,		// ハイイイエ

	ACCE_SHOP_SEQ_GET_ACCE,			// アクセサリ交換処理
	ACCE_SHOP_SEQ_GET_ACCE_FULL,	// アクセサリ全部あつまった
	ACCE_SHOP_SEQ_GET_ACCE_FULL2,	// アクセサリ全部あつまった

	ACCE_SHOP_SEQ_MSG_WAIT,	// メッセージ待ち
	ACCE_SHOP_SEQ_KEY_WAIT,	// キー待ち
	ACCE_SHOP_SEQ_END,		// 終わり
};



//-------------------------------------
//	音定義
//=====================================
#define ACCE_SHOP_SND_KEY_ON	( SEQ_SE_DP_SELECT )		// キー待ちで押されたときの音
#define ACCE_SHOP_SND_LIST_MOVE	( SEQ_SE_DP_SELECT )		// リスト動さ音
#define ACCE_SHOP_SND_LIST_SELECT	( SEQ_SE_DP_SELECT )	// リスト決定
#define ACCE_SHOP_SND_LIST_CANCEL	( SEQ_SE_DP_SELECT )	// CANCEL


//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------




//-------------------------------------
//	メインメッセージ構造体
//=====================================
typedef struct {
	u32 init;
	GF_BGL_BMPWIN* p_bmp;
	u32 msg_speed;
	u32 msg_idx;
	STRBUF* p_str;	// 表示中の文字列バッファ
} ACCE_SHOP_MAIN_MSG;

//-------------------------------------
//	交換データウィンドウ
//=====================================
typedef struct {
	u32 init;
	GF_BGL_BMPWIN* p_bmp;
	WORDSET* p_wordset;
	STRBUF* p_drawstr;
	STRBUF* p_wordstr[ACCE_SHOP_DATA_WIN_NUM];
} ACCE_SHOP_DATA_WIN;

#define ACCE_SHOP_DATA_LIST_NUM	( ACCE_SHOP_DATA_NUM + 1 )
//-------------------------------------
//	リストウィンドウ
//=====================================
typedef struct {
	u32 init;
	GF_BGL_BMPWIN* p_bmp;
	BMPLIST_WORK* p_bmplist;
	BMPLIST_DATA list[ ACCE_SHOP_DATA_LIST_NUM ];
	STRBUF* p_list_str[ ACCE_SHOP_DATA_LIST_NUM ];
	s32 data_num;
	WORDSET* p_wordset;
	STRBUF* p_drawstr;
	u16 now_pos;
	u16 now_pos_param;
	void* p_work;		// リストが動いたときに呼ぶコールバックワーク
	void (*callback)( void* p_work, u32 listnum );	// コールバック関数


	// セルアクター
	CLACT_U_RES_MANAGER_PTR	resMan[ACCE_SHOP_LIST_WIN_CLACT_RESNUM];	// リソースマネージャ
	CLACT_U_RES_OBJ_PTR		resObj[ACCE_SHOP_LIST_WIN_CLACT_RESNUM];	// それぞれのリソースオブジェ数
	CLACT_WORK_PTR clact[ ACCE_SHOP_LIST_WIN_CLACT_OBJNUM ];
} ACCE_SHOP_LIST_WIN;
typedef void (*pAcceListMoveFunc)( void* p_work, u32 listnum );

//-------------------------------------
//	YES NO ウィンドウオブジェ
//=====================================
typedef struct {
	u32 init;
	BMPMENU_WORK* p_yesno;	// YESNOメニュー
	u32 heapID;				// ヒープ
} ACCE_SHOP_YESNO_MENU;


//-------------------------------------
//	リスト動作時
//	データウィンドウ変更	処理ワーク
//=====================================
typedef struct {
	u32 heapID;
	GF_BGL_INI* p_bgl;
	ACCE_SHOP_DATA_WIN* p_data_wnd;	// データメッセージウィンドウ
	const ACCE_SHOP_DATA* cp_data;	// データ
	MYITEM* p_myitem;		// アイテム
} ACCE_SHOP_DATA_WIN_CHG;



//-------------------------------------
//	accessory交換所
//=====================================
typedef struct _FIELD_ACCE_SHOP{
	u32 seq;
	u32 seq_sub;
	SAVEDATA* p_savedata;
	IMC_ITEM_SAVEDATA* p_item;
	MYITEM* p_myitem;
	GF_BGL_INI* p_bgl;
	u32 heapID;
	CLACT_SET_PTR			clactSet;	// セルアクターセット
	CLACT_U_EASYRENDER_DATA	renddata;	// 簡易レンダーデータ

	// メッセージマネージャ
	MSGDATA_MANAGER* p_msgman;

	// コンフィグデータ
	u32 win_type;
	u32 msg_speed;
	
	// 各描画管理オブジェ
	ACCE_SHOP_MAIN_MSG main_msgwnd;	// メインメッセージウィンドウ
	ACCE_SHOP_DATA_WIN data_msgwnd;	// データメッセージウィンドウ
	ACCE_SHOP_LIST_WIN list_wnd;	// リストウィンドウ
	ACCE_SHOP_YESNO_MENU yes_no;	// はい　いいえ　メニュー
	
	// 表示変更オブジェ
	ACCE_SHOP_DATA_WIN_CHG data_msgwnd_chg;	// データウィンドウ変更
} ;

//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
static void AcceShop_BGL_Init( FIELD_ACCE_SHOP* p_acce_shop );
static void AcceShop_BGL_Delete( FIELD_ACCE_SHOP* p_acce_shop );
static void AcceShop_CLACT_Init( FIELD_ACCE_SHOP* p_acce_shop );
static void AcceShop_CLACT_Delete( FIELD_ACCE_SHOP* p_acce_shop );
static void AcceShop_ConfigGet( FIELD_ACCE_SHOP* p_acce_shop );


static void AcceShop_MainMsgInit( ACCE_SHOP_MAIN_MSG* p_win, GF_BGL_INI* p_bgl, u32 heapID, u32 msg_speed );
static void AcceShop_MainMsgDelete( ACCE_SHOP_MAIN_MSG* p_win );
static void AcceShop_MainMsgSet( ACCE_SHOP_MAIN_MSG* p_win, STRBUF* p_str, u32 heapID );
static void AcceShop_MainMsgSet_noWait( ACCE_SHOP_MAIN_MSG* p_win, STRBUF* p_str );
static BOOL AcceShop_MainMsgWait( ACCE_SHOP_MAIN_MSG* p_win );

static void AcceShop_MainMsgChangeStrSet( ACCE_SHOP_MAIN_MSG* p_win, MSGDATA_MANAGER* p_msgman, u32 heapID, const ACCE_SHOP_DATA* cp_data, u32 data_idx );
static void AcceShop_MainMsgChangeEndStrSet( ACCE_SHOP_MAIN_MSG* p_win, MSGDATA_MANAGER* p_msgman, u32 heapID, const ACCE_SHOP_DATA* cp_data, u32 data_idx );


static void AcceShop_DataMsgInit( ACCE_SHOP_DATA_WIN* p_win, GF_BGL_INI* p_bgl, MSGDATA_MANAGER* p_msgman, u32 heapID );
static void AcceShop_DataMsgDelete( ACCE_SHOP_DATA_WIN* p_win );
static void AcceShop_DataMsgSet( ACCE_SHOP_DATA_WIN* p_win, u32 nut, u32 nut_need_num, u32 nut_get_num );

static void AcceShop_ListWinInit( ACCE_SHOP_LIST_WIN* p_win, GF_BGL_INI* p_bgl, u32 heapID, const ACCE_SHOP_DATA* cp_data, u32 data_num, MSGDATA_MANAGER* p_msgman, void* p_work, pAcceListMoveFunc callback, CLACT_SET_PTR clact_set );
static void AcceShop_ListWinDelete( ACCE_SHOP_LIST_WIN* p_win );
static u32 AcceShop_ListWinMain( ACCE_SHOP_LIST_WIN* p_win );
static void AcceShop_ListWinReTrans( ACCE_SHOP_LIST_WIN* p_win );
static void AcceShop_ListWinDrawClean( ACCE_SHOP_LIST_WIN* p_win );
static void AcceShop_ListWinClactResLoad( CLACT_HEADER* p_head, ACCE_SHOP_LIST_WIN* p_win, u32 heapID );
static void AcceShop_ListWinClactResDelete( ACCE_SHOP_LIST_WIN* p_win );
static void AcceShop_ListWinClactDrawSet( ACCE_SHOP_LIST_WIN* p_win );


static void AcceShop_YesNoWinInit( ACCE_SHOP_YESNO_MENU* p_win, GF_BGL_INI* p_bgl, u32 heapID );
static void AcceShop_YesNoWinDelete( ACCE_SHOP_YESNO_MENU* p_win );
static u32 AcceShop_YesNoWinMain( ACCE_SHOP_YESNO_MENU* p_win );


// リストのコールバックで、データウィンドウを変更する
static void AcceShop_DataWinChgDataInit( ACCE_SHOP_DATA_WIN_CHG* p_obj, ACCE_SHOP_DATA_WIN* data_win, const ACCE_SHOP_DATA* cp_data, MYITEM* p_save, u32 heapID, GF_BGL_INI* p_bgl );
static void AcceShop_DataWinChgCallBack( void* p_work, u32 listnum );

static BOOL AcceShop_FullAcceCheck( const IMC_ITEM_SAVEDATA* cp_item, const ACCE_SHOP_DATA* cp_data, u32 data_num );
static BOOL AcceShop_NutsOkCheck( MYITEM* p_save, const ACCE_SHOP_DATA* cp_data, u32 data_idx, u32 heapID );
static BOOL AcceShop_AcceHaveOkCheck( const IMC_ITEM_SAVEDATA* cp_item, const ACCE_SHOP_DATA* cp_data, u32 data_idx );

// アイテム交換処理
static void AcceShop_AcceChange( IMC_ITEM_SAVEDATA* p_acceitem, MYITEM* p_myitem, const ACCE_SHOP_DATA* cp_data, u32 data_idx, u32 heapID );




//----------------------------------------------------------------------------
/**
 *	@brief	アクセサリショップ作成
 *
 *	@param	heapID		ヒープID
 *	@param	p_save		セーブデータ
 *	@param	p_bgl		BGL
 *
 *	@return	ワーク
 */
//-----------------------------------------------------------------------------
FIELD_ACCE_SHOP* FIELD_AcceShop_Alloc( u32 heapID, SAVEDATA* p_save, GF_BGL_INI* p_bgl )
{
	FIELD_ACCE_SHOP* p_acce_shop = sys_AllocMemory( heapID, sizeof(FIELD_ACCE_SHOP) );
	memset( p_acce_shop, 0, sizeof(FIELD_ACCE_SHOP) );

	p_acce_shop->heapID = heapID;
	p_acce_shop->p_bgl = p_bgl;
	p_acce_shop->p_savedata = p_save;

	// イメージクリップアクセサリデータ
	p_acce_shop->p_item = ImcSaveData_GetItemSaveData( SaveData_GetImcSaveData( p_acce_shop->p_savedata ) );

	// myitem
	p_acce_shop->p_myitem = SaveData_GetMyItem( p_save );

	// メッセージマネージャ作成
	p_acce_shop->p_msgman = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_t03r0101_dat, p_acce_shop->heapID );

	// コンフィグ初期化
	AcceShop_ConfigGet( p_acce_shop );

	// BGL初期化
	AcceShop_BGL_Init( p_acce_shop );

	// セルアクター
	AcceShop_CLACT_Init( p_acce_shop );

	return p_acce_shop;
}

//----------------------------------------------------------------------------
/**
 *	@brief	アクセサリショップ破棄
 *
 *	@param	p_acce_shop		ワーク
 */
//-----------------------------------------------------------------------------
void FIELD_AcceShop_Free( FIELD_ACCE_SHOP* p_acce_shop )
{
	// メッセージマネージャ破棄
	MSGMAN_Delete( p_acce_shop->p_msgman );
	
	// BGL破棄
	AcceShop_BGL_Delete( p_acce_shop );

	// セルアクタ-
	AcceShop_CLACT_Delete( p_acce_shop );

	memset( p_acce_shop, 0, sizeof(FIELD_ACCE_SHOP) );
	sys_FreeMemoryEz( p_acce_shop );
}

//----------------------------------------------------------------------------
/**
 *	@brief	アクセサリショップ　メイン
 *
 *	@param	p_acce_shop		ワーク
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
BOOL FIELD_AcceShop_Main( FIELD_ACCE_SHOP* p_acce_shop )
{
	STRBUF* p_str;
	BOOL result;
	
	switch( p_acce_shop->seq ){
	case ACCE_SHOP_SEQ_STARTMSG:			// こんにちは！
		AcceShop_MainMsgInit( &p_acce_shop->main_msgwnd, 
				p_acce_shop->p_bgl, p_acce_shop->heapID, p_acce_shop->msg_speed );

		p_str = MSGMAN_AllocString( p_acce_shop->p_msgman, mes_accessory_01_01 );
		AcceShop_MainMsgSet( &p_acce_shop->main_msgwnd, p_str, p_acce_shop->heapID );
		STRBUF_Delete( p_str );
		p_acce_shop->seq = ACCE_SHOP_SEQ_KEY_WAIT;
		p_acce_shop->seq_sub = ACCE_SHOP_SEQ_FULLHAVE_CHECK;
		break;

	case ACCE_SHOP_SEQ_FULLHAVE_CHECK:	// 全てのアクセサリーを持っているかチェック
		// アクセサリフルに持っているかチェック
		if( AcceShop_FullAcceCheck( p_acce_shop->p_item, AcceShopData, ACCE_SHOP_DATA_NUM ) ){

			// フルに持っている
			p_str = MSGMAN_AllocString( p_acce_shop->p_msgman, mes_accessory_01_02 );
			AcceShop_MainMsgSet( &p_acce_shop->main_msgwnd, p_str, p_acce_shop->heapID );
			STRBUF_Delete( p_str );
			p_acce_shop->seq = ACCE_SHOP_SEQ_KEY_WAIT;	// 終了へ
			p_acce_shop->seq_sub = ACCE_SHOP_SEQ_END;
		}else{
			// フルに持っていない
			p_acce_shop->seq = ACCE_SHOP_SEQ_LIST_START;
		}
		break;
		
	case ACCE_SHOP_SEQ_LIST_START:		// リスト画面の開始
		AcceShop_DataMsgInit( &p_acce_shop->data_msgwnd, 
				p_acce_shop->p_bgl, p_acce_shop->p_msgman, 
				p_acce_shop->heapID );
		AcceShop_DataWinChgDataInit( &p_acce_shop->data_msgwnd_chg,
				&p_acce_shop->data_msgwnd,
				AcceShopData, p_acce_shop->p_myitem, 
				p_acce_shop->heapID, p_acce_shop->p_bgl );
		AcceShop_ListWinInit( &p_acce_shop->list_wnd, 
				p_acce_shop->p_bgl, p_acce_shop->heapID,
				AcceShopData, ACCE_SHOP_DATA_NUM, p_acce_shop->p_msgman,
				&p_acce_shop->data_msgwnd_chg, AcceShop_DataWinChgCallBack, p_acce_shop->clactSet );
		// 引き続き↓
	case ACCE_SHOP_SEQ_LIST_RESTART:		// リスト画面の再開始
		AcceShop_ListWinReTrans( &p_acce_shop->list_wnd );

		// どのアクセサリがほしい？
		p_str = MSGMAN_AllocString( p_acce_shop->p_msgman, mes_accessory_01_03 );
		AcceShop_MainMsgSet( &p_acce_shop->main_msgwnd, p_str, p_acce_shop->heapID );
		STRBUF_Delete( p_str );
		p_acce_shop->seq = ACCE_SHOP_SEQ_MSG_WAIT;
		p_acce_shop->seq_sub = ACCE_SHOP_SEQ_LIST_MAIN;
		break;
		
	case ACCE_SHOP_SEQ_LIST_MAIN:		// リスト処理メイン
		result = AcceShop_ListWinMain( &p_acce_shop->list_wnd );
		
		if( (result != BMPLIST_NULL) && (result != BMPLIST_CANCEL) ){

			// リスト表示領域のスクリーンを初期化
			GF_BGL_ScrFill( p_acce_shop->p_bgl, FLD_MBGFRM_FONT,
				0, 0, 0, 32, 18, GF_BGL_SCRWRT_PALIN );

			// OAMOFF
			AcceShop_ListWinDrawClean( &p_acce_shop->list_wnd );

			// メインウィンドウ変更
			AcceShop_MainMsgChangeStrSet( &p_acce_shop->main_msgwnd, p_acce_shop->p_msgman, p_acce_shop->heapID, AcceShopData, p_acce_shop->list_wnd.now_pos );	

			p_acce_shop->seq = ACCE_SHOP_SEQ_MSG_WAIT;
			p_acce_shop->seq_sub = ACCE_SHOP_SEQ_YESNO_START;

			Snd_SePlay( ACCE_SHOP_SND_LIST_SELECT );
			
		}else if( result == BMPLIST_CANCEL ){
			// またどうぞ
			p_str = MSGMAN_AllocString( p_acce_shop->p_msgman, mes_accessory_01_08 );
			AcceShop_MainMsgSet( &p_acce_shop->main_msgwnd, p_str, p_acce_shop->heapID );
			STRBUF_Delete( p_str );
			p_acce_shop->seq = ACCE_SHOP_SEQ_KEY_WAIT;	// 終了へ
			p_acce_shop->seq_sub = ACCE_SHOP_SEQ_END;
			
			Snd_SePlay( ACCE_SHOP_SND_LIST_CANCEL );
		}
		break;
		
	case ACCE_SHOP_SEQ_YESNO_START:		// ハイイイエ
		// はい、いいえ　ウィンドウ表示
		AcceShop_YesNoWinInit( &p_acce_shop->yes_no, p_acce_shop->p_bgl, p_acce_shop->heapID );

		p_acce_shop->seq = ACCE_SHOP_SEQ_YESNO_MAIN;
		break;
		
	case ACCE_SHOP_SEQ_YESNO_MAIN:		// ハイイイエ
		result = AcceShop_YesNoWinMain( &p_acce_shop->yes_no );
		if( result == 0 ){
			// ハイ選択
			// 木の実足りてるかチェック
			if( AcceShop_NutsOkCheck( p_acce_shop->p_myitem, AcceShopData, p_acce_shop->list_wnd.now_pos, p_acce_shop->heapID ) == FALSE ){
				
				// 木の実がたりないよ！
				p_str = MSGMAN_AllocString( p_acce_shop->p_msgman, mes_accessory_01_06 );
				AcceShop_MainMsgSet( &p_acce_shop->main_msgwnd, p_str, p_acce_shop->heapID );
				STRBUF_Delete( p_str );
				p_acce_shop->seq = ACCE_SHOP_SEQ_KEY_WAIT;	// メインへへ
				p_acce_shop->seq_sub = ACCE_SHOP_SEQ_LIST_RESTART;
				AcceShop_YesNoWinDelete( &p_acce_shop->yes_no );
				break;
			}

			// それ以上アクセサリついか出来るかチェック
			if( AcceShop_AcceHaveOkCheck( p_acce_shop->p_item, AcceShopData, p_acce_shop->list_wnd.now_pos ) == FALSE ){

				// それ以上もてない
				p_str = MSGMAN_AllocString( p_acce_shop->p_msgman, mes_accessory_01_07 );
				AcceShop_MainMsgSet( &p_acce_shop->main_msgwnd, p_str, p_acce_shop->heapID );
				STRBUF_Delete( p_str );

				AcceShop_YesNoWinDelete( &p_acce_shop->yes_no );
				p_acce_shop->seq = ACCE_SHOP_SEQ_KEY_WAIT;	// メインへ
				p_acce_shop->seq_sub = ACCE_SHOP_SEQ_LIST_RESTART;
				break;
			}

			// どうもありがとう
			p_str = MSGMAN_AllocString( p_acce_shop->p_msgman, mes_accessory_01_05 );
			AcceShop_MainMsgSet( &p_acce_shop->main_msgwnd, p_str, p_acce_shop->heapID );
			STRBUF_Delete( p_str );

			AcceShop_YesNoWinDelete( &p_acce_shop->yes_no );

			p_acce_shop->seq = ACCE_SHOP_SEQ_KEY_WAIT;	// アクセサリ交換へ
			p_acce_shop->seq_sub = ACCE_SHOP_SEQ_GET_ACCE;

		}else if( result == BMPMENU_CANCEL ){
			// イイエ選択
			AcceShop_YesNoWinDelete( &p_acce_shop->yes_no );
			p_acce_shop->seq = ACCE_SHOP_SEQ_LIST_RESTART;
		}
		break;
		
	case ACCE_SHOP_SEQ_GET_ACCE:			// アクセサリ交換処理
		// アクセサリとアイテム設定
		AcceShop_AcceChange( p_acce_shop->p_item, p_acce_shop->p_myitem, AcceShopData, p_acce_shop->list_wnd.now_pos, p_acce_shop->heapID );

		// 交換メッセージ表示
		AcceShop_MainMsgChangeEndStrSet( &p_acce_shop->main_msgwnd, p_acce_shop->p_msgman, p_acce_shop->heapID, AcceShopData, p_acce_shop->list_wnd.now_pos );

		// 全部集まったか
		if( AcceShop_FullAcceCheck( p_acce_shop->p_item, AcceShopData, ACCE_SHOP_DATA_NUM ) ){
			p_acce_shop->seq = ACCE_SHOP_SEQ_KEY_WAIT;	// 全部集まった処理へ
			p_acce_shop->seq_sub = ACCE_SHOP_SEQ_GET_ACCE_FULL;
		}else{
			p_acce_shop->seq = ACCE_SHOP_SEQ_KEY_WAIT;	// もう一度
			p_acce_shop->seq_sub = ACCE_SHOP_SEQ_LIST_RESTART;
		}
		break;

	case ACCE_SHOP_SEQ_GET_ACCE_FULL:	// アクセサリ全部あつまった
		// 全部集めてくれてありがとう
		p_str = MSGMAN_AllocString( p_acce_shop->p_msgman, mes_accessory_01_10 );
		AcceShop_MainMsgSet( &p_acce_shop->main_msgwnd, p_str, p_acce_shop->heapID );
		STRBUF_Delete( p_str );
		p_acce_shop->seq = ACCE_SHOP_SEQ_KEY_WAIT;	// 全部集まった処理へ
		p_acce_shop->seq_sub = ACCE_SHOP_SEQ_GET_ACCE_FULL2;
		break;

	case ACCE_SHOP_SEQ_GET_ACCE_FULL2:	// アクセサリ全部あつまった
		// 全部集めてくれてありがとう
		p_str = MSGMAN_AllocString( p_acce_shop->p_msgman, mes_accessory_01_02 );
		AcceShop_MainMsgSet( &p_acce_shop->main_msgwnd, p_str, p_acce_shop->heapID );
		STRBUF_Delete( p_str );
		p_acce_shop->seq = ACCE_SHOP_SEQ_KEY_WAIT;	// 終了へ
		p_acce_shop->seq_sub = ACCE_SHOP_SEQ_END;
		break;


	case ACCE_SHOP_SEQ_MSG_WAIT:	// メッセージ待ち
		if( AcceShop_MainMsgWait( &p_acce_shop->main_msgwnd ) ){
			p_acce_shop->seq = p_acce_shop->seq_sub;
		}
		break;
		
	case ACCE_SHOP_SEQ_KEY_WAIT:// キー待ち
		if( AcceShop_MainMsgWait( &p_acce_shop->main_msgwnd ) ){
			if( sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL)  ){
				p_acce_shop->seq = p_acce_shop->seq_sub;
			}
		}
		break;
		
	case ACCE_SHOP_SEQ_END:		// 終わり
		// 終了処理
		AcceShop_MainMsgDelete( &p_acce_shop->main_msgwnd );	
		AcceShop_DataMsgDelete( &p_acce_shop->data_msgwnd );	
		AcceShop_ListWinDelete( &p_acce_shop->list_wnd );	
		AcceShop_YesNoWinDelete( &p_acce_shop->yes_no );	
		return TRUE;

	default:
		break;
	}

	CLACT_Draw( p_acce_shop->clactSet );
	
	return FALSE;
}





//-----------------------------------------------------------------------------
/**
 *		プライベート関数
 */
//-----------------------------------------------------------------------------

//----------------------------------------------------------------------------
/**
 *	@brief	コンフィグデータ取得
 *
 *	@param	p_acce_shop		ワーク
 */
//-----------------------------------------------------------------------------
static void AcceShop_ConfigGet( FIELD_ACCE_SHOP* p_acce_shop )
{
	CONFIG * cfg = SaveData_GetConfig( p_acce_shop->p_savedata );
	p_acce_shop->win_type = CONFIG_GetWindowType( cfg );
	p_acce_shop->msg_speed = CONFIG_GetMsgPrintSpeed( cfg );
}

//----------------------------------------------------------------------------
/**
 *	@brief	BGL初期化　メッセージ用面の　BG３を使用
 *
 *	@param	p_acce_shop 
 */
//-----------------------------------------------------------------------------
static void AcceShop_BGL_Init( FIELD_ACCE_SHOP* p_acce_shop )
{
	// トークウィンドウ
	// システムウィンドウ
	// 初期化
	TalkWinGraphicSet( p_acce_shop->p_bgl, FLD_MBGFRM_FONT,
			ACCE_SHOP_TALK_CHAROFS,
			ACCE_SHOP_TALK_PLTT,
			p_acce_shop->win_type, 
			p_acce_shop->heapID );
	TalkFontPaletteLoad( PALTYPE_MAIN_BG, 
			ACCE_SHOP_TALKFONT_PLTT * 32, 
			p_acce_shop->heapID );
	MenuWinGraphicSet( p_acce_shop->p_bgl, FLD_MBGFRM_FONT,
			ACCE_SHOP_SYSTEM_CHAROFS,
			ACCE_SHOP_SYSTEM_PLTT,
			p_acce_shop->win_type, 
			p_acce_shop->heapID );
	SystemFontPaletteLoad( PALTYPE_MAIN_BG, 
			ACCE_SHOP_SYSTEMFONT_PLTT * 32, 
			p_acce_shop->heapID );
	
	// スクリーンクリーン	
	GF_BGL_ScrClear( p_acce_shop->p_bgl, FLD_MBGFRM_FONT );
}

static void AcceShop_BGL_Delete( FIELD_ACCE_SHOP* p_acce_shop )
{
	// スクリーンクリーン	
	GF_BGL_ScrClear( p_acce_shop->p_bgl, FLD_MBGFRM_FONT );

	// フィールド常駐キャラクタ復帰
	FieldMsgPrintInit( PALTYPE_MAIN_BG, MSG_PRINT_INIT_ON );
}

//----------------------------------------------------------------------------
/**
 *	@brief	セルアクター設定
 *
 *	@param	p_acce_shop 
 */
//-----------------------------------------------------------------------------
static void AcceShop_CLACT_Init( FIELD_ACCE_SHOP* p_acce_shop )
{
	p_acce_shop->clactSet = CLACT_U_SetEasyInit( ACCE_SHOP_CLACT_WORK_NUM , &p_acce_shop->renddata, p_acce_shop->heapID );
}
static void AcceShop_CLACT_Delete( FIELD_ACCE_SHOP* p_acce_shop )
{
	CLACT_DestSet( p_acce_shop->clactSet );
}



//----------------------------------------------------------------------------
/**
 *	@brief	メインメッセージウィンドウ　オブジェ　初期化
 *
 *	@param	p_win		ウィンドウオブジェ
 *	@param	p_bgl		BGL
 *	@param	heapID		ヒープID
 *	@param	msg_speed	メッセージスピード
 */
//-----------------------------------------------------------------------------
static void AcceShop_MainMsgInit( ACCE_SHOP_MAIN_MSG* p_win, GF_BGL_INI* p_bgl, u32 heapID, u32 msg_speed )
{
	if( p_win->init == 1 ){
		return ;
	}
	
	p_win->msg_speed = msg_speed;
	
	p_win->p_bmp = GF_BGL_BmpWinAllocGet( heapID, 1 );

	// ビットマップウィンドウ確保
	GF_BGL_BmpWinAdd( p_bgl, p_win->p_bmp, FLD_MBGFRM_FONT,
			ACCE_SHOP_MAIN_MSGWIN_X, ACCE_SHOP_MAIN_MSGWIN_Y,
			ACCE_SHOP_MAIN_MSGWIN_SX, ACCE_SHOP_MAIN_MSGWIN_SY,
			ACCE_SHOP_MAIN_MSGWIN_PLTT, ACCE_SHOP_MAIN_MSGWIN_CHAR );

	GF_BGL_BmpWinDataFill( p_win->p_bmp, 15 );

	// 枠描画
	BmpTalkWinWrite( p_win->p_bmp, WINDOW_TRANS_ON, ACCE_SHOP_TALK_CHAROFS, ACCE_SHOP_TALK_PLTT );

	p_win->init = 1;
}

//----------------------------------------------------------------------------
/**
 *	@brief	メインメッセージオブジェ　破棄
 *
 *	@param	p_win	ウィンドウオブジェ
 */
//-----------------------------------------------------------------------------
static void AcceShop_MainMsgDelete( ACCE_SHOP_MAIN_MSG* p_win )
{
	if( p_win->init == 0 ){
		return ;
	}
	
	GF_BGL_BmpWinOff( p_win->p_bmp );
	GF_BGL_BmpWinDel( p_win->p_bmp );
	GF_BGL_BmpWinFree( p_win->p_bmp, 1 );

	p_win->init = 0;
}

//----------------------------------------------------------------------------
/**
 *	@brief	メインメッセージ設定
 *
 *	@param	p_win		ウィンドウオブジェ
 *	@param	p_str		文字列
 *	@param	heapID
 */
//-----------------------------------------------------------------------------
static void AcceShop_MainMsgSet( ACCE_SHOP_MAIN_MSG* p_win, STRBUF* p_str, u32 heapID )
{
	GF_ASSERT( p_win->p_str == NULL );
	
	GF_BGL_BmpWinDataFill( p_win->p_bmp, 15 );

	p_win->p_str = STRBUF_CreateBufferCopy( p_str, heapID );
	
	p_win->msg_idx = GF_STR_PrintColor( p_win->p_bmp, FONT_TALK, p_win->p_str, 0, 0, p_win->msg_speed, ACCE_SHOP_FONTBMP_TALK_COLOR, NULL );

	GF_BGL_BmpWinOn( p_win->p_bmp );
}

//----------------------------------------------------------------------------
/**
 *	@brief	メッセージウエイトなし
 *
 *	@param	p_win	ウィンドウ
 *	@param	p_str	文字列
 */
//-----------------------------------------------------------------------------
static void AcceShop_MainMsgSet_noWait( ACCE_SHOP_MAIN_MSG* p_win, STRBUF* p_str )
{
	GF_BGL_BmpWinDataFill( p_win->p_bmp, 15 );
	p_win->msg_idx = GF_STR_PrintColor( p_win->p_bmp, FONT_TALK, p_str, 0, 0, MSG_NO_PUT, ACCE_SHOP_FONTBMP_TALK_COLOR, NULL );

	GF_BGL_BmpWinOn( p_win->p_bmp );
}

//----------------------------------------------------------------------------
/**
 *	@brief	メッセージ終了待ち
 *	
 *	@param	p_win	ウィンドウオブジェ
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
static BOOL AcceShop_MainMsgWait( ACCE_SHOP_MAIN_MSG* p_win )
{
	if( GF_MSG_PrintEndCheck( p_win->msg_idx ) == 0 ){

		// 保持していた文字列バッファ破棄
		if( p_win->p_str != NULL ){
			STRBUF_Delete( p_win->p_str );
			p_win->p_str = NULL;
		}
		return TRUE;
	}
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	メイン画面に　～と～を交換しますか？　テキストを出す
 *
 *	@param	p_win		ウィンドウオブジェ
 *	@param	p_msgman	メッセージマネージャ
 *	@param	heapID		ヒープ
 *	@param	cp_data		ショップデータ
 *	@param	data_idx	表示データインデックス
 */
//-----------------------------------------------------------------------------
static void AcceShop_MainMsgChangeStrSet( ACCE_SHOP_MAIN_MSG* p_win, MSGDATA_MANAGER* p_msgman, u32 heapID, const ACCE_SHOP_DATA* cp_data, u32 data_idx )
{
	STRBUF* p_str;
	STRBUF* p_drawstr;
	WORDSET* p_wordset;
	
	// 簡易会話作成
	p_wordset = WORDSET_Create( heapID );

	// 展開先文字列作成
	p_drawstr = STRBUF_Create( WORDSET_DEFAULT_BUFLEN, heapID );
	p_str = MSGMAN_AllocString( p_msgman, mes_accessory_01_04 );
	
	WORDSET_RegisterItemName( p_wordset, 0, cp_data[ data_idx ].item_no + NUTS_START_ITEMNUM );
	WORDSET_RegisterNumber( p_wordset, 1, cp_data[ data_idx ].need_num,
			3, NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT );
	WORDSET_RegisterAccessoryName( p_wordset, 2, cp_data[ data_idx ].acce_no );
	WORDSET_ExpandStr( p_wordset, p_drawstr, p_str );

	// テキスト設定
	AcceShop_MainMsgSet( p_win, p_drawstr, heapID );
	
	WORDSET_Delete( p_wordset );
	STRBUF_Delete( p_drawstr );
	STRBUF_Delete( p_str );
	
}

//----------------------------------------------------------------------------
/**
 *	@brief	交換終了	文字列表示
 *
 *	@param	p_win		メインウィンドウオブジェ
 *	@param	p_msgman	メッセージマネージャ
 *	@param	heapID		ヒープID
 *	@param	cp_data		データ
 *	@param	data_idx	データインデックス
 */
//-----------------------------------------------------------------------------
static void AcceShop_MainMsgChangeEndStrSet( ACCE_SHOP_MAIN_MSG* p_win, MSGDATA_MANAGER* p_msgman, u32 heapID, const ACCE_SHOP_DATA* cp_data, u32 data_idx )
{
	STRBUF* p_str;
	STRBUF* p_drawstr;
	WORDSET* p_wordset;
	
	// 簡易会話作成
	p_wordset = WORDSET_Create( heapID );

	// 展開先文字列作成
	p_drawstr = STRBUF_Create( 200, heapID );
	p_str = MSGMAN_AllocString( p_msgman, mes_accessory_01_09 );
	
	WORDSET_RegisterItemName( p_wordset, 0, cp_data[ data_idx ].item_no + NUTS_START_ITEMNUM );
	WORDSET_RegisterNumber( p_wordset, 1, cp_data[ data_idx ].need_num,
			3, NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT );
	WORDSET_RegisterAccessoryName( p_wordset, 2, cp_data[ data_idx ].acce_no );
	WORDSET_ExpandStr( p_wordset, p_drawstr, p_str );

	// テキスト設定
	AcceShop_MainMsgSet( p_win, p_drawstr, heapID );
	
	WORDSET_Delete( p_wordset );
	STRBUF_Delete( p_drawstr );
	STRBUF_Delete( p_str );
}

//----------------------------------------------------------------------------
/**
 *	@brief	データ画面初期化
 *
 *	@param	p_win		ウィンドウオブジェ
 *	@param	p_bgl		BGL
 *	@param	heapID		ヒープ
 */
//-----------------------------------------------------------------------------
static void AcceShop_DataMsgInit( ACCE_SHOP_DATA_WIN* p_win, GF_BGL_INI* p_bgl, MSGDATA_MANAGER* p_msgman, u32 heapID )
{
	int i;

	if( p_win->init == 1 ){
		return ;
	}
	
	p_win->p_bmp = GF_BGL_BmpWinAllocGet( heapID, 1 );

	// ビットマップウィンドウ確保
	GF_BGL_BmpWinAdd( p_bgl, p_win->p_bmp, FLD_MBGFRM_FONT,
			ACCE_SHOP_DATA_WINWIN_X, ACCE_SHOP_DATA_WINWIN_Y,
			ACCE_SHOP_DATA_WINWIN_SX, ACCE_SHOP_DATA_WINWIN_SY,
			ACCE_SHOP_DATA_WINWIN_PLTT, ACCE_SHOP_DATA_WINWIN_CHAR );


	// 簡易会話作成
	p_win->p_wordset = WORDSET_Create( heapID );
	for( i=0; i<ACCE_SHOP_DATA_WIN_NUM; i++ ){
		p_win->p_wordstr[i] = MSGMAN_AllocString( p_msgman, mes_accessory_03_01+i );
	}

	// 展開先文字列作成
	p_win->p_drawstr = STRBUF_Create( WORDSET_DEFAULT_BUFLEN, heapID );


	GF_BGL_BmpWinDataFill( p_win->p_bmp, 15 );

	p_win->init = 1;
}

//----------------------------------------------------------------------------
/**
 *	@brief	データ画面破棄
 *	
 *	@param	p_win	ウィンドウオブジェ
 */
//-----------------------------------------------------------------------------
static void AcceShop_DataMsgDelete( ACCE_SHOP_DATA_WIN* p_win )
{
	int i;

	if( p_win->init == 0 ){
		return ;
	}
	
	for( i=0; i<ACCE_SHOP_DATA_WIN_NUM; i++ ){
		// 文字列破棄
		STRBUF_Delete( p_win->p_wordstr[i] );
	}
	STRBUF_Delete( p_win->p_drawstr );


	WORDSET_Delete( p_win->p_wordset );	
	GF_BGL_BmpWinOff( p_win->p_bmp );
	GF_BGL_BmpWinDel( p_win->p_bmp );
	GF_BGL_BmpWinFree( p_win->p_bmp, 1 );

	p_win->init = 0;
}

//----------------------------------------------------------------------------
/**
 *	@brief	データウィンドウ設定
 *
 *	@param	p_win		ウィンドウ
 *	@param	nut			木の実	（道具ナンバー）
 *	@param	nut_need_num木の実交換に必要な数
 *	@param	nut_get_num	木の実保持数
 */
//-----------------------------------------------------------------------------
static void AcceShop_DataMsgSet( ACCE_SHOP_DATA_WIN* p_win, u32 nut, u32 nut_need_num, u32 nut_get_num )
{
	int i;

	// ワードセット
	WORDSET_RegisterItemName( p_win->p_wordset, ACCE_SHOP_DATA_WIN_NUTS_NAME, nut + NUTS_START_ITEMNUM );
	WORDSET_RegisterNumber( p_win->p_wordset, ACCE_SHOP_DATA_WIN_NUTS_NEED,
			nut_need_num, 3, NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT );
	WORDSET_RegisterNumber( p_win->p_wordset, ACCE_SHOP_DATA_WIN_NUTS_HAVE,
			nut_get_num, 3, NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT );

	GF_BGL_BmpWinDataFill( p_win->p_bmp, 15 );

	// 文字列展開
	for( i=0; i<ACCE_SHOP_DATA_WIN_NUM; i++ ){
		WORDSET_ExpandStr( p_win->p_wordset, p_win->p_drawstr, p_win->p_wordstr[ i ] );

		GF_STR_PrintColor( p_win->p_bmp, FONT_SYSTEM, p_win->p_drawstr,
				0, 
				ACCE_SHOP_DATA_WINWIN_DRAW_YOFS * i,
				MSG_NO_PUT, ACCE_SHOP_FONTBMP_SYS_COLOR, NULL );
	}

	// 枠の描画
	BmpMenuWinWrite( p_win->p_bmp, WINDOW_TRANS_ON, ACCE_SHOP_SYSTEM_CHAROFS, ACCE_SHOP_SYSTEM_PLTT );
}

//----------------------------------------------------------------------------
/**
 *	@brief	リストウィンドウ初期化
 *
 *	@param	p_win		ワーク
 *	@param	p_bgl		BGL
 *	@param	heapID		ヒープ
 *	@param	cp_data		データテーブル
 *	@param	data_num	データ数
 *	@param	p_msgman	メッセージマネージャ
 *	@param	clact_set	セルアクターセット
 */
//-----------------------------------------------------------------------------
static void AcceShop_ListWinInit( ACCE_SHOP_LIST_WIN* p_win, GF_BGL_INI* p_bgl, u32 heapID, const ACCE_SHOP_DATA* cp_data, u32 data_num, MSGDATA_MANAGER* p_msgman, void* p_work, pAcceListMoveFunc callback, CLACT_SET_PTR clact_set )
{
	int i;
	STRBUF* p_str;
	CLACT_HEADER head;
	CLACT_ADD_SIMPLE add;

	static const u8 CLACT_Add_Y[ ACCE_SHOP_LIST_WIN_CLACT_OBJNUM ] = {
		ACCE_SHOP_LIST_WIN_CLACT_Y_0,
		ACCE_SHOP_LIST_WIN_CLACT_Y_1
	};
	static BMPLIST_HEADER BmpListHeader = {
		NULL,
		NULL,
		NULL,
		NULL,
		0,
		ACCE_SHOP_LIST_WIN_DRAWLINE,
		0,
		ACCE_SHOP_LIST_WIN_DATA_X,
		ACCE_SHOP_LIST_WIN_CURSOR_X,
		ACCE_SHOP_LIST_WIN_DRAW_Y,
		ACCE_SHOP_LIST_WIN_FONT_COL_F,
		ACCE_SHOP_LIST_WIN_FONT_COL_B,
		ACCE_SHOP_LIST_WIN_FONT_COL_S,
		ACCE_SHOP_LIST_WIN_MSG_SPC,
		ACCE_SHOP_LIST_WIN_LINE_SPC,
		ACCE_SHOP_LIST_WIN_PAGE_SKIP,
		ACCE_SHOP_LIST_WIN_FONT,
		ACCE_SHOP_LIST_WIN_DISP,
		NULL
	};

	if( p_win->init == 1 ){
		return ;
	}

	
	p_win->init = 1;

	p_win->data_num = data_num + 1;
	
	p_win->p_work = p_work;
	p_win->callback = callback;
	p_win->p_bmp = GF_BGL_BmpWinAllocGet( heapID, 1 );

	// ビットマップウィンドウ確保
	GF_BGL_BmpWinAdd( p_bgl, p_win->p_bmp, FLD_MBGFRM_FONT,
			ACCE_SHOP_LIST_WINWIN_X, ACCE_SHOP_LIST_WINWIN_Y,
			ACCE_SHOP_LIST_WINWIN_SX, ACCE_SHOP_LIST_WINWIN_SY,
			ACCE_SHOP_LIST_WINWIN_PLTT, ACCE_SHOP_LIST_WINWIN_CHAR );

	// 簡易会話作成
	p_win->p_wordset = WORDSET_Create( heapID );

	// 展開先文字列作成
	p_win->p_drawstr = STRBUF_Create( WORDSET_DEFAULT_BUFLEN, heapID );
	p_str = MSGMAN_AllocString( p_msgman, mes_accessory_03_01 );
	
	// リストデータ作成
	for( i=0; i<data_num; i++ ){
		WORDSET_RegisterAccessoryName( p_win->p_wordset, 0, cp_data[ i ].acce_no );
		WORDSET_ExpandStr( p_win->p_wordset, p_win->p_drawstr, p_str );
		p_win->p_list_str[ i ] = STRBUF_CreateBufferCopy( p_win->p_drawstr, heapID );
		p_win->list[ i ].str = p_win->p_list_str[ i ];
		p_win->list[ i ].param = i;
	}
	
	// 終わる
	p_win->p_list_str[ data_num ] = MSGMAN_AllocString( p_msgman, mes_accessory_04_01 );
	p_win->list[ data_num ].str = p_win->p_list_str[ data_num ];
	p_win->list[ data_num ].param = data_num;
	
	WORDSET_Delete( p_win->p_wordset );
	STRBUF_Delete( p_win->p_drawstr );
	STRBUF_Delete( p_str );

	// ビットマップリストに設定
	BmpListHeader.win = p_win->p_bmp;
	BmpListHeader.count = p_win->data_num;
	BmpListHeader.list = p_win->list;
	p_win->p_bmplist = BmpListSet( &BmpListHeader, 0, 0, heapID );

	// 枠の描画
	BmpMenuWinWrite( p_win->p_bmp, WINDOW_TRANS_ON, ACCE_SHOP_SYSTEM_CHAROFS, ACCE_SHOP_SYSTEM_PLTT );

	// リソースマネージャ作成
	for( i=0; i<ACCE_SHOP_LIST_WIN_CLACT_RESNUM; i++ ){
		p_win->resMan[ i ] = CLACT_U_ResManagerInit( ACCE_SHOP_LIST_WIN_CLACT_RESMAN_WORKNUM,
				i, heapID );
	}

	// リソース読み込み
	AcceShop_ListWinClactResLoad( &head, p_win, heapID );

	// アクターの登録
	add.ClActSet = clact_set;
	add.ClActHeader = &head;
	add.pri		= 0;
	add.DrawArea = NNS_G2D_VRAM_TYPE_2DMAIN;
	add.heap	= heapID;
	add.mat.x	= ACCE_SHOP_LIST_WIN_CLACT_X * FX32_ONE;
	for( i=0; i<ACCE_SHOP_LIST_WIN_CLACT_OBJNUM; i++ ){
		add.mat.y	= CLACT_Add_Y[ i ] * FX32_ONE;
		p_win->clact[ i ] = CLACT_AddSimple( &add );
		CLACT_AnmChg( p_win->clact[ i ], i );
		CLACT_SetAnmFlag( p_win->clact[ i ], TRUE );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	リストウィンドウ破棄
 *
 *	@param	p_win	ワーク
 */
//-----------------------------------------------------------------------------
static void AcceShop_ListWinDelete( ACCE_SHOP_LIST_WIN* p_win )
{
	int i;

	if( p_win->init == 0 ){
		return ;
	}

	// アクター破棄
	for( i=0; i<ACCE_SHOP_LIST_WIN_CLACT_OBJNUM; i++ ){

		CLACT_Delete( p_win->clact[ i ] );
	}

	// アクターリソース破棄
	AcceShop_ListWinClactResDelete( p_win );

	// リストない文字破棄
	for( i=0; i<p_win->data_num; i++ ){
		STRBUF_Delete( p_win->p_list_str[ i ] );
	}

	// ビットマップリスト破棄
	BmpListExit( p_win->p_bmplist, NULL, NULL );
	GF_BGL_BmpWinOff( p_win->p_bmp );
	GF_BGL_BmpWinDel( p_win->p_bmp );
	GF_BGL_BmpWinFree( p_win->p_bmp, 1 );

	p_win->init = 1;
}

//----------------------------------------------------------------------------
/**
 *	@brief	リストウィンドウ　メイン
 *
 *	@param	p_win	ウィンドウ
 *
 *	@retval	"param = 選択パラメータ"
 *	@retval	"BMPLIST_NULL = 選択中"
 *	@retval	"BMPLIST_CANCEL	= キャンセル(Ｂボタン)"
 */
//-----------------------------------------------------------------------------
static u32 AcceShop_ListWinMain( ACCE_SHOP_LIST_WIN* p_win )
{
	u32 result;
	u16 now_pos;
	
	result = BmpListMain( p_win->p_bmplist );

	// 選択やBボタン以外なら現在ポジション設定
	if( result == BMPLIST_NULL ){
		BmpListDirectPosGet( p_win->p_bmplist, &now_pos );
		if( p_win->now_pos != now_pos ){
			p_win->now_pos = now_pos;
			p_win->callback( p_win->p_work, p_win->now_pos );

			Snd_SePlay( ACCE_SHOP_SND_LIST_MOVE );

			AcceShop_ListWinClactDrawSet( p_win );

		}
	}else if( result != BMPLIST_CANCEL ){

		// 最終項目を選択したらやめる　なのでCANCELを返す
		if( p_win->now_pos == (p_win->data_num - 1) ){
			result = BMPLIST_CANCEL;
		}
	}
	
	return result;
}

//----------------------------------------------------------------------------
/**
 *	@brief	再転送
 *
 *	@param	p_win	ワーク
 */
//-----------------------------------------------------------------------------
static void AcceShop_ListWinReTrans( ACCE_SHOP_LIST_WIN* p_win )
{
//	BmpListRewrite( p_win->p_bmplist );
	p_win->callback( p_win->p_work, p_win->now_pos );

	// 枠の描画
	BmpMenuWinWrite( p_win->p_bmp, WINDOW_TRANS_ON, ACCE_SHOP_SYSTEM_CHAROFS, ACCE_SHOP_SYSTEM_PLTT );

	// OAM描画設定	
	AcceShop_ListWinClactDrawSet( p_win );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ウィンドウ描画OFF
 *
 *	@param	p_win 
 */
//-----------------------------------------------------------------------------
static void AcceShop_ListWinDrawClean( ACCE_SHOP_LIST_WIN* p_win )
{
	CLACT_SetDrawFlag( p_win->clact[ 0 ], FALSE );
	CLACT_SetDrawFlag( p_win->clact[ 1 ], FALSE );
}

//----------------------------------------------------------------------------
/**
 *	@brief	アクターリソース読み込み
 *	
 *	@param	p_head	ヘッダー
 *	@param	p_win	
 */
//-----------------------------------------------------------------------------
static void AcceShop_ListWinClactResLoad( CLACT_HEADER* p_head, ACCE_SHOP_LIST_WIN* p_win, u32 heapID )
{
	// リソース読み込み
	p_win->resObj[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerResAddArcChar( 
			p_win->resMan[ CLACT_U_CHAR_RES ],
			ARC_SHOP_GRA, NARC_shop_gra_shop_arw_NCGR, 
			FALSE, ACCE_SHOP_LIST_WIN_CLACT_RESCONT_ID, 
			NNS_G2D_VRAM_TYPE_2DMAIN, heapID );	

	p_win->resObj[ CLACT_U_PLTT_RES ] = CLACT_U_ResManagerResAddArcPltt( 
			p_win->resMan[ CLACT_U_PLTT_RES ],
			ARC_SHOP_GRA, NARC_shop_gra_shop_obj_NCLR, 
			FALSE, ACCE_SHOP_LIST_WIN_CLACT_RESCONT_ID, 
			NNS_G2D_VRAM_TYPE_2DMAIN, 1,  heapID );	

	p_win->resObj[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerResAddArcKindCell( 
			p_win->resMan[ CLACT_U_CELL_RES ],
			ARC_SHOP_GRA, NARC_shop_gra_shop_arw_NCER, 
			FALSE, ACCE_SHOP_LIST_WIN_CLACT_RESCONT_ID, 
			CLACT_U_CELL_RES, heapID );	

	p_win->resObj[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerResAddArcKindCell( 
			p_win->resMan[ CLACT_U_CELLANM_RES ],
			ARC_SHOP_GRA, NARC_shop_gra_shop_arw_NANR, 
			FALSE, ACCE_SHOP_LIST_WIN_CLACT_RESCONT_ID, 
			CLACT_U_CELLANM_RES, heapID );


	CLACT_U_CharManagerSetAreaCont( p_win->resObj[ CLACT_U_CHAR_RES ] );
	CLACT_U_PlttManagerSetCleanArea( p_win->resObj[ CLACT_U_PLTT_RES ] );

	// ヘッダー作成
	CLACT_U_MakeHeader(
			p_head,
			ACCE_SHOP_LIST_WIN_CLACT_RESCONT_ID,
			ACCE_SHOP_LIST_WIN_CLACT_RESCONT_ID,
			ACCE_SHOP_LIST_WIN_CLACT_RESCONT_ID,
			ACCE_SHOP_LIST_WIN_CLACT_RESCONT_ID,
			CLACT_U_HEADER_DATA_NONE,
			CLACT_U_HEADER_DATA_NONE,
			0, 0,
			p_win->resMan[ 0 ],
			p_win->resMan[ 1 ],
			p_win->resMan[ 2 ],
			p_win->resMan[ 3 ],
			NULL, NULL );
}

//----------------------------------------------------------------------------
/**
 *	@brief	アクターリソース破棄
 *
 *	@param	p_win 
 */
//-----------------------------------------------------------------------------
static void AcceShop_ListWinClactResDelete( ACCE_SHOP_LIST_WIN* p_win )
{
	int i;
	CLACT_U_CharManagerDelete( p_win->resObj[ CLACT_U_CHAR_RES ] );
	CLACT_U_PlttManagerDelete( p_win->resObj[ CLACT_U_PLTT_RES ] );

	for( i=0; i<ACCE_SHOP_LIST_WIN_CLACT_RESNUM; i++ ){
		CLACT_U_ResManagerDelete( p_win->resMan[ i ] );
	}
}

//----------------------------------------------------------------------------
/**
*	@brief	描画設定
 *
 *	@param	* p_win 
 */
//-----------------------------------------------------------------------------
static void AcceShop_ListWinClactDrawSet( ACCE_SHOP_LIST_WIN* p_win )
{
	u16 list_pos;
	
	// リスト位置取得
	BmpListPosGet( p_win->p_bmplist, &list_pos, NULL );
	
	if( (list_pos <= 0) ){
		CLACT_SetDrawFlag( p_win->clact[ 0 ], FALSE );
	}else{
		CLACT_SetDrawFlag( p_win->clact[ 0 ], TRUE );
	}
	if( list_pos >= (p_win->data_num - 7) ){
		CLACT_SetDrawFlag( p_win->clact[ 1 ], FALSE );
	}else{
		CLACT_SetDrawFlag( p_win->clact[ 1 ], TRUE );
	}
}



//----------------------------------------------------------------------------
/**
 *	@brief	データウィンドウ変更　オブジェ
 *
 *	@param	p_obj			オブジェ
 *	@param	data_win		データウィンドウ
 *	@param	cp_data			アクセサリーデータ
 *	@param	p_save			セーブデータ
 *	@param	heapID			ヒープ
 *	@param	p_bgl			BGL
 */
//-----------------------------------------------------------------------------
static void AcceShop_DataWinChgDataInit( ACCE_SHOP_DATA_WIN_CHG* p_obj, ACCE_SHOP_DATA_WIN* data_win, const ACCE_SHOP_DATA* cp_data, MYITEM* p_save, u32 heapID, GF_BGL_INI* p_bgl )
{
	p_obj->p_bgl = p_bgl;
	p_obj->p_data_wnd = data_win;
	p_obj->cp_data = cp_data;
	p_obj->p_myitem = p_save;
	p_obj->heapID	= heapID;
}

//----------------------------------------------------------------------------
/**
 *	@brief	リストに呼んでもらう　データウィンドウ更新コールバック
 *
 *	@param	p_work
 *	@param	listnum 
 */
//-----------------------------------------------------------------------------
static void AcceShop_DataWinChgCallBack( void* p_work, u32 listnum )
{
	ACCE_SHOP_DATA_WIN_CHG* p_obj = p_work;
	u32 have_item;
	
	// ショップデータ項目数以下なら　データ更新
	if( listnum < ACCE_SHOP_DATA_NUM ){
		
		have_item = MyItem_GetItemNum( p_obj->p_myitem, p_obj->cp_data[ listnum ].item_no + NUTS_START_ITEMNUM, p_obj->heapID );
		AcceShop_DataMsgSet( p_obj->p_data_wnd, 
				p_obj->cp_data[ listnum ].item_no, 
				p_obj->cp_data[ listnum ].need_num, 
				have_item );
	}else{
		// スクリーン初期化		
		GF_BGL_ScrFill( p_obj->p_bgl, FLD_MBGFRM_FONT,
				0,
				ACCE_SHOP_DATA_WINWIN_X-1, ACCE_SHOP_DATA_WINWIN_Y-1,
				ACCE_SHOP_DATA_WINWIN_SX+2, ACCE_SHOP_DATA_WINWIN_SY+2, 
				GF_BGL_SCRWRT_PALIN );
		GF_BGL_LoadScreenReq( p_obj->p_bgl, FLD_MBGFRM_FONT );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	YESNOウィンドウ初期化
 *
 *	@param	p_win	ウィンドウワーク
 *	@param	p_bgl	BGL
 *	@param	heapID	ヒープ
 */
//-----------------------------------------------------------------------------
static void AcceShop_YesNoWinInit( ACCE_SHOP_YESNO_MENU* p_win, GF_BGL_INI* p_bgl, u32 heapID )
{
	static const BMPWIN_DAT BmpWinDat = {
		FLD_MBGFRM_FONT,
		ACCE_SHOP_YESNO_WIN_X,
		ACCE_SHOP_YESNO_WIN_Y,
		ACCE_SHOP_YESNO_WIN_SX,
		ACCE_SHOP_YESNO_WIN_SY,
		ACCE_SHOP_YESNO_WIN_PLTT,
		ACCE_SHOP_YESNO_WIN_CHAR
	};

	if( p_win->init == 1 ){
		return ;
	}
	
	p_win->p_yesno = BmpYesNoSelectInit( p_bgl, &BmpWinDat, ACCE_SHOP_SYSTEM_CHAROFS, ACCE_SHOP_SYSTEM_PLTT, heapID );
	p_win->heapID = heapID;

	p_win->init = 1;
}

//----------------------------------------------------------------------------
/**
 *	@brief	YESNOウィンドウ破棄
 *
 *	@param	p_win	ウィンドウワーク
 */
//-----------------------------------------------------------------------------
static void AcceShop_YesNoWinDelete( ACCE_SHOP_YESNO_MENU* p_win )
{
	if( p_win->init == 0 ){
		return ;
	}
	
	// 勝手に破棄されるのでコメントアウト
//	BmpYesNoWinDel( p_win->p_yesno, p_win->heapID );

	p_win->init = 0;
}

//----------------------------------------------------------------------------
/**
 *	@brief	YESNOウィンドウメイン
 *
 *	@param	p_win	ワーク
 *
 * @retval	"BMPMENU_NULL	選択されていない"
 * @retval	"0				はいを選択"
 * @retval	"BMPMENU_CANCEL	いいえorキャンセル"
 */
//-----------------------------------------------------------------------------
static u32 AcceShop_YesNoWinMain( ACCE_SHOP_YESNO_MENU* p_win )
{
	u32 result;
	result = BmpYesNoSelectMain( p_win->p_yesno, p_win->heapID );
	return result;
}


//----------------------------------------------------------------------------
/**
 *	@brief	ショップのアクセサリをフルに持っているかチェック
 *
 *	@param	cp_item		セーブデータ
 *	@param	cp_data		ショップデータ
 *	@param	data_num	データ数
 *
 *	@retval	TRUE	フルに持っている
 *	@retval	FALSE	フルにもって良いない
 */
//-----------------------------------------------------------------------------
static BOOL AcceShop_FullAcceCheck( const IMC_ITEM_SAVEDATA* cp_item, const ACCE_SHOP_DATA* cp_data, u32 data_num )
{
	int i;

	// 全データアクセサリを追加できるかチェックする
	for( i=0; i<data_num; i++ ){
		if( ImcSaveData_CheckAcceAdd( cp_item, cp_data[i].acce_no, 1 ) == TRUE ){
			return FALSE;
		}
	}
	return TRUE;
}


//----------------------------------------------------------------------------
/**
 *	@brief	木の実足りているかチェック
 *
 *	@param	p_save		セーブ
 *	@param	cp_data		データ
 *	@param	data_idx	インデックス
 *
 *	@retval	TRUE	足りている
 *	@retval	FALSE	たりていない
 */
//-----------------------------------------------------------------------------
static BOOL AcceShop_NutsOkCheck( MYITEM* p_save, const ACCE_SHOP_DATA* cp_data, u32 data_idx, u32 heapID )
{
	u32 item_num;
	
	item_num = MyItem_GetItemNum( p_save, cp_data[ data_idx ].item_no + NUTS_START_ITEMNUM, heapID );

	if( item_num >= cp_data[ data_idx ].need_num ){
		return TRUE;
	}
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	アクセサリをもてるかチェック
 *
 *	@param	cp_item		ワーク	
 *	@param	cp_data		データ
 *	@param	data_idx	インデックス
 */
//-----------------------------------------------------------------------------
static BOOL AcceShop_AcceHaveOkCheck( const IMC_ITEM_SAVEDATA* cp_item, const ACCE_SHOP_DATA* cp_data, u32 data_idx )
{
	return ImcSaveData_CheckAcceAdd( cp_item, cp_data[ data_idx ].acce_no, 1 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	アクセサリ変更　処理
 *
 *	@param	p_acceitem		アクセサリセーブデータ
 *	@param	p_myitem		自分アイテム
 *	@param	cp_data			ショップデータ
 *	@param	data_idx		データインデックス
 */
//-----------------------------------------------------------------------------
static void AcceShop_AcceChange( IMC_ITEM_SAVEDATA* p_acceitem, MYITEM* p_myitem, const ACCE_SHOP_DATA* cp_data, u32 data_idx, u32 heapID )
{
	u32 acce_no = cp_data[ data_idx ].acce_no;
	u32 item_no = cp_data[ data_idx ].item_no + NUTS_START_ITEMNUM;
	u32 need_num = cp_data[ data_idx ].need_num;
	BOOL result;

	ImcSaveData_AddAcceFlag( p_acceitem, acce_no, 1 );
	result = MyItem_SubItem( p_myitem, item_no, need_num, heapID );
	GF_ASSERT( result == TRUE );
}
