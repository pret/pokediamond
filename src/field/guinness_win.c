//==============================================================================================
/**
 * @file	guinness_win.c
 * @brief	ギネスウィンドウ
 * @author	Satoshi Nohara
 * @date	2006.03.01
 */
//==============================================================================================
#include "common.h"
#include "gflib/msg_print.h"			//STRCODE
#include "system/msgdata.h"				//MSGMAN_TYPE_DIRECT
#include "system/fontproc.h"
#include "system/snd_tool.h"
#include "system/pm_str.h"
#include "system/bmp_menu.h"
#include "system/bmp_list.h"
#include "system\wordset.h"				//WORDSET_ExpandStr
#include "fieldsys.h"
#include "fieldmap.h"
#include "fld_bmp.h"
#include "talk_msg.h"
#include "guinness_win.h"

#include "msgdata/msg.naix"				//NARC_msg_??_dat

#include "system/window.h"

#include "msgdata/msg.naix"				//NARC_msg_??_dat
#include "msgdata/msg_ev_win.h"			//msg_ev_win_016


//==============================================================================================
//
//	extern宣言
//
//==============================================================================================


//==============================================================================================
//
//	プロトタイプ宣言
//
//==============================================================================================
void EventCmd_GuinnessWin( GMEVENT_CONTROL* event, u8 x, u8 y, u8 cursor, u8 cancel, WORDSET* wordset );

static BOOL GMEVENT_GuinnessWin( GMEVENT_CONTROL* event );

static void GuinnessWin_Init( FIELDSYS_WORK* fsys, GUINNESS_WIN_WORK* wk, u8 cancel, WORDSET* wordset );
static void GuinnessWin_Start( GUINNESS_WIN_WORK* wk, u8 x, u8 y, u8 cursor );

static void BmpList_list_make( GUINNESS_WIN_WORK* wk, u32 msg_id, u32 param  );
static void BmpList_h_default_set(GUINNESS_WIN_WORK* wk);
static void	BmpList_CallBack( BMPLIST_WORK* lw, u32 param, u8 y );

static void ListMake_01( GUINNESS_WIN_WORK* wk );
static void talk_msg_print( GUINNESS_WIN_WORK* wk, u16 msg_id, u32 wait );

//各シーケンス処理
static void NextSeqSet( GUINNESS_WIN_WORK* wk, u8 next_seq );
static void seq_list_sub( GUINNESS_WIN_WORK* wk );
static void seq_ranking_sub( GUINNESS_WIN_WORK* wk );
static void seq_yesno_sub( GUINNESS_WIN_WORK* wk );
static void seq_del_sub( GUINNESS_WIN_WORK* wk );
static void seq_end_sub( GUINNESS_WIN_WORK* wk );


//==============================================================================================
//
//	定義
//
//==============================================================================================
#define GUINNESS_WIN_FONT		(FONT_SYSTEM)	//フォント指定
//#define GUINNESS_WIN_FONT	(FONT_TALK)			//フォント指定

#define GUINNESS_WIN_MSG_BUF_SIZE	(32*2)		//メッセージバッファサイズ

//BMPメニュー
#define GUINNESS_WIN_MENU_MAX	(12)			//メニュー項目の最大数

//BMPリスト
#define GUINNESS_WIN_LIST_MAX	(16)			//リスト項目の最大数

//BMPリストヘッダー定義
#define EV_LIST_LINE			(6)				//表示最大項目数
#define EV_LIST_RABEL_X			(1)				//ラベル表示Ｘ座標
#define EV_LIST_DATA_X			(12)			//項目表示Ｘ座標
#define EV_LIST_LINE_Y			(8)				//表示Ｙ座標

//シーケンス定義
enum{
	SEQ_LIST,
	SEQ_RANKING,
	SEQ_YESNO,
	SEQ_DEL,
	SEQ_END,
};


//==============================================================================================
//
//	文字インデックス置き換え定義
//
//==============================================================================================
#define MSG_INDEX_SINGLE_BTL		(msg_ev_win_007)	//「シングルバトル」
#define MSG_INDEX_DOUBLE_BTL		(msg_ev_win_008)	//「ダブルバトル」
#define MSG_INDEX_MULTI_BTL			(msg_ev_win_010)	//「マルチバトル」
#define MSG_INDEX_MULTI_COMM_BTL	(msg_ev_win_010)	//「マルチバトルつうしん」
#define MSG_INDEX_WIFI_BTL			(msg_ev_win_010)	//「Wi-Fiバトル」
#define MSG_INDEX_AVERAGE_WIN		(msg_ev_win_021)	//「へいきんれんしょうすう」
//...
//...
#define MSG_INDEX_FISHING			(msg_ev_win_051)	//「つりあげたかず」

#define MSG_INDEX_WIN				(msg_ev_win_003)	//「しょう」
#define MSG_INDEX_CLOSE				(msg_ev_win_012)	//「とじる」
#define MSG_INDEX_START				(msg_ev_win_011)	//「どのれんしょうきろくをみますか？」
#define MSG_INDEX_DEL				(msg_ev_win_041)	//「けしてもいいですか？」


//==============================================================================================
//
//	CGX
//
//==============================================================================================
#define GUINNESS_WIN_SX				(20)			//ウィンドウサイズ
#define GUINNESS_WIN_SY				(14)			//ウィンドウサイズ

//fld_bmp.h参照
enum{
	GUINNESS_LIST_CGX_NUM =		(1),				//1
	GUINNESS_WIN_CGX_NUM =		(MENU_WIN_CGX_NUM),	//473

	GUINNESS_YESNO_CGX_NUM =	(GUINNESS_WIN_CGX_NUM - (FLD_YESNO_WIN_SX * FLD_YESNO_WIN_SY))
	//GUINNESS_YESNO_CGX_NUM =	(FLD_YESNO_WIN_CGX),//277
	//GUINNESS_YESNO_CGX_NUM =	(GUINNESS_LIST_CGX_NUM + GUINNESS_WIN_SX * GUINNESS_WIN_SY),//281
	//GUINNESS_YESNO_CGX_NUM =	(512),
};

#if 0
OS_Printf("CGX_NUM = %d\n",(FLD_YESNO_WIN_CGX) );										//277
OS_Printf("CGX_NUM = %d\n",(GUINNESS_LIST_CGX_NUM+GUINNESS_WIN_SX*GUINNESS_WIN_SY));	//281
OS_Printf("CGX_NUM = %d\n",(FLD_MSG_WIN_CGX) );											//301
OS_Printf("CGX_NUM = %d\n",(MENU_WIN_CGX_NUM) );										//473
#endif


//==============================================================================================
//
//	構造体
//
//==============================================================================================
struct _GUINNESS_WIN_WORK{
	FIELDSYS_WORK * fsys;						//FIELDSYS_WORKのポインタ

 	GF_BGL_BMPWIN bmpwin;						//BMPウィンドウデータ
 	GF_BGL_BMPWIN talk_bmpwin;					//会話BMPウィンドウデータ
	
	STRBUF* msg_buf[GUINNESS_WIN_MENU_MAX];		//メッセージデータのポインタ
	MSGDATA_MANAGER* msgman;					//メッセージマネージャー
	WORDSET* wordset;							//単語セット

	u8 seq;										//シーケンスナンバー
	u8 cancel;									//キャンセル
	u8 list_no;									//メニュー項目の何番目か
	u8 del_mode;								//削除モードフラグ

	u16 work1;									//ワーク1
	u16 work2;									//ワーク2
 
	BMPMENU_WORK* mw;							//「はい・いいえ」ウィンドウ

	//BMPリスト
	BMPLIST_HEADER ListH;						//BMPリストヘッダー
	BMPLIST_WORK* lw;							//BMPリストデータ
	u16 list_bak;								//リスト位置バックアップ
	u16 cursor_bak;								//カーソル位置バックアップ
	BMPLIST_DATA list_Data[GUINNESS_WIN_LIST_MAX];	//リストデータ
};

//「はい・いいえ」ウィンドウデータ
static const BMPWIN_DAT YesNoBmpDat = {
	FLD_MBGFRM_FONT, FLD_YESNO_WIN_PX, FLD_YESNO_WIN_PY,
	FLD_YESNO_WIN_SX, FLD_YESNO_WIN_SY, FLD_YESNO_WIN_PAL, GUINNESS_YESNO_CGX_NUM
};


//==============================================================================================
//
//	外から呼び出される関数	
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	イベント擬似コマンド：ギネスウィンドウ呼び出し
 *
 * @param	x			ウィンドウ表示X座標
 * @param	y			ウィンドウ表示X座標
 * @param	cursor		カーソル位置
 * @param	cancel		Bキャンセルフラグ(TRUE=有効、FALSE=無効)
 * @param	wordset		WORDSET型のポインタ
 * @param	talk_bmpwin	GF_BGL_BMPWIN型のポインタ(会話BMPWINを渡す)
 *
 * @retval	none
 */
//--------------------------------------------------------------
void EventCmd_GuinnessWin( GMEVENT_CONTROL* event, u8 x, u8 y, u8 cursor, u8 cancel, WORDSET* wordset )
{
	GUINNESS_WIN_WORK* wk;
	FIELDSYS_WORK* fsys = FieldEvent_GetFieldSysWork(event);

	//開始音
	Snd_SePlay( SE_GUINNESS_WIN_START );

	wk = sys_AllocMemory( HEAPID_FIELD, sizeof(GUINNESS_WIN_WORK) );
	if( wk == NULL ){
		GF_ASSERT( (0) && "ギネスウィンドウメモリ確保失敗！" );
		return;	//何もしない
	}
	memset( wk, 0, sizeof(GUINNESS_WIN_WORK) );

	//ワーク初期化	
	GuinnessWin_Init( fsys, wk, cancel, wordset );

	//会話ビットマップウィンドウデータ追加
	FldTalkBmpAdd( wk->fsys->bgl, &wk->talk_bmpwin ,FLD_MBGFRM_FONT);
	FieldTalkWinPut( &wk->talk_bmpwin, SaveData_GetConfig(wk->fsys->savedata) );
	talk_msg_print( wk, MSG_INDEX_START, MSG_ALLPUT );

	//リスト作成
	ListMake_01( wk );

	//BmpList_list_make( wk, MSG_INDEX_WIN, 0 );

	GuinnessWin_Start( wk, x, y, cursor );

	FieldEvent_Call( event, GMEVENT_GuinnessWin, wk );
	return;
}


//==============================================================================================
//
//
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	イベントウィンドウ　ワーク初期化
 *
 * @param	wk			GUINNESS_WIN_WORK型のポインタ
 * @param	cancel		Bキャンセルフラグ(TRUE=有効、FALSE=無効)
 * @param	wordset		WORDSET型のポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void GuinnessWin_Init( FIELDSYS_WORK* fsys, GUINNESS_WIN_WORK* wk, u8 cancel, WORDSET* wordset )
{
	int i;

	//メッセージデータマネージャー作成
	wk->msgman = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, 
									NARC_msg_ev_win_dat, HEAPID_FIELD );

	//単語セットモジュール作成
	wk->wordset = WORDSET_Create( HEAPID_FIELD );
	//wk->wordset	= wordset;		//スクリプトを引き継ぐ

	wk->fsys		= fsys;
	wk->cancel		= cancel;
	wk->list_no		= 0;

	for( i=0; i < GUINNESS_WIN_LIST_MAX ;i++ ){
		wk->list_Data[i].str	= NULL;
		wk->list_Data[i].param	= 0;
	}

	//MSGMAN_Createの後に処理
	for( i=0; i < GUINNESS_WIN_MENU_MAX ;i++ ){
		wk->msg_buf[i] = STRBUF_Create( GUINNESS_WIN_MSG_BUF_SIZE, HEAPID_FIELD );
	}

	return;
}

//--------------------------------------------------------------
/**
 * @brief	BMPリスト　開始
 *
 * @param	wk			GUINNESS_WIN_WORK型のポインタ
 * @param	x			ウィンドウ表示X座標
 * @param	y			ウィンドウ表示X座標
 * @param	cursor		カーソル位置
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void GuinnessWin_Start( GUINNESS_WIN_WORK* wk, u8 x, u8 y, u8 cursor )
{
	//表示最大項目数チェック
	GF_BGL_BmpWinAdd( wk->fsys->bgl, &wk->bmpwin, FLD_MBGFRM_FONT, x, y, 
									GUINNESS_WIN_SX, GUINNESS_WIN_SY, 
									FLD_SYSFONT_PAL, GUINNESS_LIST_CGX_NUM );


	//あとで対応
	//Ｙサイズは表示項目数が少ないときは、可変になる！

	//メニューウィンドウのグラフィックをセット(409-511使用)
	MenuWinGraphicSet(
		wk->fsys->bgl, FLD_MBGFRM_FONT, GUINNESS_WIN_CGX_NUM, MENU_WIN_PAL, 0, HEAPID_FIELD );

	//メニューウィンドウを描画
	BmpMenuWinWrite(&wk->bmpwin, WINDOW_TRANS_OFF, GUINNESS_WIN_CGX_NUM, MENU_WIN_PAL);

	//リストヘッダー初期設定
	BmpList_h_default_set(wk);

	wk->lw = BmpListSet( (const BMPLIST_HEADER*)&wk->ListH, 0, cursor, HEAPID_FIELD );

	return;
}

//--------------------------------------------------------------
/**
 * @brief	BMPリスト	リスト作成
 *
 * @param	wk			GUINNESS_WIN_WORK型のポインタ
 * @param	msg_id		メッセージID
 * @param	param		BMPLISTパラメータ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void BmpList_list_make( GUINNESS_WIN_WORK* wk, u32 msg_id, u32 param  )
{
	int i;
	void* msg;

	SDK_ASSERTMSG( wk->list_no < GUINNESS_WIN_LIST_MAX, "リスト項目数オーバー！" );

	MSGMAN_GetString( wk->msgman, msg_id, wk->msg_buf[wk->list_no] );
	wk->list_Data[ wk->list_no ].str = (const void *)wk->msg_buf[wk->list_no];
	//*st = (const void *)&wk->msg_buf[wk->list_no][0];

	if( param == GUINNESS_WIN_LIST_LABEL ){
		wk->list_Data[ wk->list_no ].param = BMPLIST_RABEL;
		//*pa = BMPLIST_RABEL;
	}else{
		wk->list_Data[ wk->list_no ].param = param;
		//*pa = param;
	}

	wk->list_no++;

	return;
}

//--------------------------------------------------------------
/**
 * @brief	BMPリスト	ヘッダー初期設定
 *
 * @param	wk			GUINNESS_WIN_WORK型のポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void BmpList_h_default_set(GUINNESS_WIN_WORK* wk)
{
	wk->ListH.list		= wk->list_Data;
	wk->ListH.call_back = NULL;
	wk->ListH.icon		= BmpList_CallBack;
	wk->ListH.win		= &wk->bmpwin;

	wk->ListH.count		= wk->list_no;
	wk->ListH.line		= EV_LIST_LINE;

	wk->ListH.rabel_x	= EV_LIST_RABEL_X;
	wk->ListH.data_x	= EV_LIST_DATA_X;
	wk->ListH.cursor_x	= 0;
	wk->ListH.line_y	= EV_LIST_LINE_Y;

	wk->ListH.f_col		= FBMP_COL_BLACK;
	wk->ListH.b_col		= FBMP_COL_WHITE;		
	wk->ListH.s_col		= FBMP_COL_BLK_SDW;

	wk->ListH.msg_spc	= 0;
	wk->ListH.line_spc	= 16;
	wk->ListH.page_skip	= BMPLIST_LRKEY_SKIP;
	wk->ListH.font		= GUINNESS_WIN_FONT;
	wk->ListH.c_disp_f	= 0;

	return;
}

//--------------------------------------------------------------
/**
 * @brief	リストシステムからのコールバック※一行表示ごと
 *
 * @param	lw			BMPLIST_WORK型のポインタ
 * @param	param		選択時リターンパラメータ
 * @param	y			
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void	BmpList_CallBack(BMPLIST_WORK* lw,u32 param,u8 y)
{
	if( param == BMPLIST_RABEL ){
		BmpListTmpColorChange( lw, FBMP_COL_RED, FBMP_COL_WHITE, FBMP_COL_RED_SDW );
	}else{
		BmpListTmpColorChange( lw, FBMP_COL_BLACK, FBMP_COL_WHITE, FBMP_COL_BLK_SDW );
	}

	return;
}

//--------------------------------------------------------------
/**
 * @brief	イベントメイン
 *
 * @param	event		GMEVENT_CONTROL型のポインタ
 *
 * @retval	"FALSE=継続、TRUE=終了"
 */
//--------------------------------------------------------------
static BOOL GMEVENT_GuinnessWin( GMEVENT_CONTROL* event )
{
	u32	ret;
	GUINNESS_WIN_WORK* wk = FieldEvent_GetSpecialWork(event);

	switch( wk->seq ){

	//リスト処理(項目を選ぶ)
	case SEQ_LIST:
		seq_list_sub( wk );
		break;

	//ランキング処理
	case SEQ_RANKING:
		seq_ranking_sub( wk );
		break;

	//「はい・いいえ」選択中
	case SEQ_YESNO:
		seq_yesno_sub( wk );
		break;

	//削除処理
	case SEQ_DEL:
		seq_del_sub( wk );
		break;

	//終了処理
	case SEQ_END:
		seq_end_sub( wk );
		sys_FreeMemoryEz( wk );
		return TRUE;			//終了！
	};

	return FALSE;
};


//==============================================================================================
//
//	各シーケンス処理
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	シーケンス	セット
 *
 * @param	wk			GUINNESS_WIN_WORK型のポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void NextSeqSet( GUINNESS_WIN_WORK* wk, u8 next_seq )
{
	wk->seq = next_seq;
	return;
}

//--------------------------------------------------------------
/**
 * @brief	シーケンス	リスト
 *
 * @param	wk			GUINNESS_WIN_WORK型のポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void seq_list_sub( GUINNESS_WIN_WORK* wk )
{
	u32 ret = BmpListMain( wk->lw );

	switch( ret ){

	case BMPLIST_NULL:
		break;

	case BMPLIST_CANCEL:
		NextSeqSet( wk, SEQ_END );
		break;

	default:
		wk->work1 = ret;						//選択した値をワークに代入
		NextSeqSet( wk, SEQ_RANKING );
		break;;
	};

	return;
}

//--------------------------------------------------------------
/**
 * @brief	シーケンス	ランキング
 *
 * @param	wk			GUINNESS_WIN_WORK型のポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void seq_ranking_sub( GUINNESS_WIN_WORK* wk )
{
	u32 ret;

	if( sys.trg & PAD_BUTTON_SELECT ){
		wk->del_mode = 1;					//削除モードON
		return;
	}

	ret = BmpListMain( wk->lw );

	switch( ret ){

	case BMPLIST_NULL:
		break;

	case BMPLIST_CANCEL:
		if( wk->del_mode == 1 ){;
			wk->del_mode = 0;				//削除モードOFF
		}

		NextSeqSet( wk, SEQ_LIST );
		break;

	default:
		//削除モードONだったら
		if( wk->del_mode == 1 ){;
			wk->work1 = ret;				//選択した値をワークに代入

			wk->mw = BmpYesNoSelectInit( wk->fsys->bgl, &YesNoBmpDat, 
											GUINNESS_WIN_CGX_NUM, MENU_WIN_PAL, HEAPID_FIELD );

			talk_msg_print( wk, MSG_INDEX_DEL, MSG_ALLPUT );

			NextSeqSet( wk, SEQ_YESNO );
		}
		break;
	};

	return;
}

//--------------------------------------------------------------
/**
 * @brief	シーケンス	「はい・いいえ」
 *
 * @param	wk			GUINNESS_WIN_WORK型のポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void seq_yesno_sub( GUINNESS_WIN_WORK* wk )
{
	u32 ret  = BmpYesNoSelectMain( wk->mw, HEAPID_FIELD );

	if( ret == 0 ){								//はい
		NextSeqSet( wk, SEQ_DEL );
	}else if( ret == BMPMENU_CANCEL ){			//いいえ、キャンセル
		NextSeqSet( wk, SEQ_RANKING );
	}

	return;
}

//--------------------------------------------------------------
/**
 * @brief	シーケンス	削除
 *
 * @param	wk			GUINNESS_WIN_WORK型のポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void seq_del_sub( GUINNESS_WIN_WORK* wk )
{
	//選択しているデータを削除
	//

	//データをソートし直す
	//
		
	//再描画
	//
		
	NextSeqSet( wk, SEQ_RANKING );

	return;
}

//--------------------------------------------------------------
/**
 * @brief	シーケンス	終了
 *
 * @param	wk			GUINNESS_WIN_WORK型のポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void seq_end_sub( GUINNESS_WIN_WORK* wk )
{
	int i;

	Snd_SePlay( SE_DECIDE );	//注意！

	//会話ウィンドウ終了
	BmpTalkWinClear( &wk->talk_bmpwin, WINDOW_TRANS_ON );
	GF_BGL_BmpWinDel( &wk->talk_bmpwin );

	//リスト終了
	BmpListExit( wk->lw, NULL, NULL );
	BmpMenuWinClear( wk->ListH.win, WINDOW_TRANS_ON );
	GF_BGL_BmpWinDel( &wk->bmpwin );

	for( i=0; i < GUINNESS_WIN_MENU_MAX ;i++ ){
		STRBUF_Delete( wk->msg_buf[i] );
	}

	WORDSET_Delete( wk->wordset );
	MSGMAN_Delete( wk->msgman );

	return;
}


//==============================================================================================
//
//
//
//==============================================================================================

//--------------------------------------------------------------
/**
 * @brief	会話ウィンドウにメッセージを一括表示
 *
 * @param	wk			GUINNESS_WIN_WORK型のアドレス
 * @param	msg_id		メッセージID
 * @param	wait		メッセージウェイト
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void talk_msg_print( GUINNESS_WIN_WORK* wk, u16 msg_id, u32 wait )
{
	STRBUF* tmp_buf = STRBUF_Create( GUINNESS_WIN_MSG_BUF_SIZE, HEAPID_FIELD );
	STRBUF* tmp_buf2= STRBUF_Create( GUINNESS_WIN_MSG_BUF_SIZE, HEAPID_FIELD );

	//メッセージクリア
	GF_BGL_BmpWinDataFill( &wk->talk_bmpwin, (FBMP_COL_WHITE) );

	MSGMAN_GetString( wk->msgman, msg_id, tmp_buf );

	//登録された単語を使って文字列展開する
	WORDSET_ExpandStr( wk->wordset, tmp_buf2, tmp_buf );

	GF_STR_PrintSimple( &wk->talk_bmpwin, FONT_TALK, tmp_buf2, 0, 0, wait, NULL );

	STRBUF_Delete( tmp_buf );
	STRBUF_Delete( tmp_buf2 );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	表示するかチェックしてリスト作成01
 *
 * @param	wk			GUINNESS_WIN_WORK型のポインタ
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void ListMake_01( GUINNESS_WIN_WORK* wk )
{
	//シングルバトル連勝数
	if( 1 ){
		BmpList_list_make( wk, MSG_INDEX_SINGLE_BTL, 0 );
	}

	//ダブルバトル連勝数
	if( 1 ){
		BmpList_list_make( wk, MSG_INDEX_DOUBLE_BTL, 1 );
	}

	//マルチバトル連勝数
	if( 1 ){
		BmpList_list_make( wk, MSG_INDEX_MULTI_BTL, 2 );
	}

	//通信マルチバトル連勝数
	if( 1 ){
		BmpList_list_make( wk, MSG_INDEX_MULTI_COMM_BTL, 3 );
	}

	//Wi-Fiバトル連勝数
	if( 1 ){
		BmpList_list_make( wk, MSG_INDEX_WIFI_BTL, 4 );
	}

	//バトルタワー平均連勝数連勝数
	if( 1 ){
		BmpList_list_make( wk, MSG_INDEX_AVERAGE_WIN, 5 );
	}

	BmpList_list_make( wk, MSG_INDEX_CLOSE, 6 );			//「とじる」
	return;
}


