//=============================================================================================
/**
 * @file	pmfprint.c
 * @brief	文字表示関数
 * @author	tetsu
 * @date	2003.04.08
 *
 * @data	2004.11.04 AGB -> NDS
 * @author	Hiroyuki Nakamura
 */
//=============================================================================================
#include "common.h"
#include "fntsys.h"

#define __PMFPRINT_H_GLOBAL__
#include	"system/pmfprint.h"

#include	"system/snd_tool.h"
#include	"system\fontproc.h"
#include "../field/fld_bmp.h"




#define	CURSOR_WAIT_TIME		(8)

#define WRITE_SKIP_CURSOR_W		( 8)
#define WRITE_SKIP_CURSOR_H		(16)


extern void	BmpPrintMsg(MSG_DATA_HEADER* mdh_p);


#include "skip_cur.dat"			//送りカーソルデータ

static MSG_PRINT_MODE msg_print_flag;


#define	AFF_FONT_POS_CHG		// 拡大フォントの位置変更（コメントアウトで上揃え）

#ifdef	AFF_FONT_POS_CHG
//#define	AFF_FONT_CENTER		// 拡大フォントを中揃えで表示（コメントアウトで下揃え）
#endif




//=============================================================================================
#define	PRINTSEQ_WRITE			(0)
#define	PRINTSEQ_TRGWAIT		(1)
#define	PRINTSEQ_TRGWAIT_CLEAR	(2)
#define	PRINTSEQ_TRGWAIT_SCROLL	(3)
#define	PRINTSEQ_SCROLL			(4)
#define	PRINTSEQ_SE_WAIT		(5)
#define	PRINTSEQ_FORCEWAIT		(6)

#define	SCR_SPEED_FAST		(4)
#define	SCR_SPEED_NORMAL	(2)
#define	SCR_SPEED_SLOW		(1)
static	const u8 scr_speed_value[] = {
	SCR_SPEED_SLOW,
	SCR_SPEED_NORMAL,
	SCR_SPEED_FAST,
};

//---------------------------------------------------------------------------------------------
/*
 *	文字データ取得
 *
 * @param	ini			BGLデータ
 * @param	mdh_p		メッセージデータ構造体ポインタ
 *
 * @retval	w_flag		文字取得パラメータ
 *
 */
//---------------------------------------------------------------------------------------------
PRINT_RESULT PokeFontPrint( MSG_DATA_HEADER * mdh_p )
{
	const MSG_FONT_DATA* font_bmp;
	MSG_PRINT_USER*	mpu_p;
	int msg_speed, scr_sp;
	u16	fcode;

//	mdh_p->mph->bmpwin->ini

	mpu_p = (MSG_PRINT_USER *)&(mdh_p->userwork[0]);

	switch(mdh_p->seq){

	case PRINTSEQ_WRITE:		//通常処理

		//押しっぱなしの場合の判定(最初のトリガーが検出されていれば有効)
		if( ( (sys.cont & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL)) && (mpu_p->skip_f) ) ||
			( (sys.tp_cont) && (msg_print_flag.tp_f) ) ){
			mdh_p->waitwork = 0;
			if( mdh_p->wait != MSG_ALLPUT ){
				msg_print_flag.btl_skip_f = 1;
			}
		}
		if((mdh_p->waitwork)&&(mdh_p->wait)){
			(mdh_p->waitwork)--;

			if(msg_print_flag.skip_f){//スキップ機能が有効の場合の処理
				//最初のトリガーを検出
				if( ( sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL) ) ||
					( (sys.tp_trg) && (msg_print_flag.tp_f) ) ){
					mpu_p->skip_f = 1;
					mdh_p->waitwork = 0;
				}
			}
			return PRINT_RESULT_COMMAND;
		}

/*		結局、スキップフラグを立てるとボタンで送られるので、ウェイトはプリント速度に依存
		if(msg_print_flag.auto_f){
			mdh_p->waitwork = AUTO_MSGWAIT;		//オート中はウェイト一定
		}else{
			mdh_p->waitwork = mdh_p->wait;
		}
*/
		mdh_p->waitwork = mdh_p->wait;


		//フォントデータ取得
		fcode = *(u16*)(mdh_p->mph.msg);
		mdh_p->mph.msg++; 

		switch(fcode){

		/* 終了コード */
		case EOM_:	
			return PRINT_RESULT_END;

		/* 改行コード */
		case CR_:	
			mdh_p->mph.write_x = mdh_p->mph.start_x;
			mdh_p->mph.write_y +=( FontHeaderGet( mdh_p->mph.fnt_index, FONT_HEADER_SIZE_Y ) + mdh_p->mph.space_y ); 
			return PRINT_RESULT_LOOP;

		/* 指定INDEXバッファのメッセージ展開	*/
		case I_MSG_:	
			//未作成(DATA = 1byte)
			mdh_p->mph.msg++; 
			return PRINT_RESULT_LOOP;


		/* フォント制御コマンド */
		case _CTRL_TAG:
			// タグコード出現位置までポインタを戻す
			mdh_p->mph.msg--;

			fcode = STRCODE_GetTagType( mdh_p->mph.msg );

			switch( fcode ){
			case NC_FONT_COL_:				// フォント制御コード
				{
					u16	 param = STRCODE_GetTagParam( mdh_p->mph.msg, 0 );

					mdh_p->mph.f_col = 1 + (param*2);
					mdh_p->mph.s_col = 1 + (param*2) + 1;
					FntDataColorSet(mdh_p->mph.f_col, mdh_p->mph.b_col, mdh_p->mph.s_col);
				}
				break;

			case NC_NOTE_ICON:		// ここに注目アイコン処理を記述する
				{
					u16	 param = STRCODE_GetTagParam( mdh_p->mph.msg, 0 );
					GF_MSG_PrintDispIcon( mdh_p, mdh_p->mph.write_x, mdh_p->mph.write_y, param );
				}
				if( mdh_p->wait_flg != 0 ){
					GF_BGL_BmpWinOn( mdh_p->mph.bmpwin );
				}
				break;

			case NC_FORCE_WAIT:
				{
					mdh_p->waitwork = STRCODE_GetTagParam( mdh_p->mph.msg, 0 );
					mdh_p->mph.msg = STRCODE_SkipTag( mdh_p->mph.msg );
					mdh_p->seq = PRINTSEQ_FORCEWAIT;
					return PRINT_RESULT_COMMAND;
				}
				break;

			case NC_CALLBACK_ARG:
				mdh_p->callback_arg = STRCODE_GetTagParam( mdh_p->mph.msg, 0 );
				mdh_p->mph.msg = STRCODE_SkipTag( mdh_p->mph.msg );
				return PRINT_RESULT_COMMAND;

			case NC_WRITEPOS_CHANGE_X:
				mdh_p->mph.write_x = STRCODE_GetTagParam( mdh_p->mph.msg, 0 );
				break;

			case NC_WRITEPOS_CHANGE_Y:
				mdh_p->mph.write_y = STRCODE_GetTagParam( mdh_p->mph.msg, 0 );
				break;

			case NC_FONT_SIZE_:
				{
					u16 param = STRCODE_GetTagParam( mdh_p->mph.msg, 0 );

					switch( param ) {
					case NC_FAFF_100_:		// サイズ：100％
						mdh_p->mph.dot_tbl = 0;
						mdh_p->mph.dot_wy = 0;
						break;
					case NC_FAFF_200_:		// サイズ：200％
						mdh_p->mph.dot_tbl = 0xfffc;
						mdh_p->mph.dot_wy = 0;
						break;
					}
				}
				break;

			case NC_MOVE_:				// 動作制御コード
				{
					u16	 c_move = STRCODE_GetTagParam( mdh_p->mph.msg, 0 );

					switch( c_move ){
					case NC_MV_CLEAR_:		// キー待ちクリア
						mdh_p->seq	= PRINTSEQ_TRGWAIT_CLEAR;
						PokeFontTriggerCursorAnimeInit(mdh_p);
						mdh_p->mph.msg = STRCODE_SkipTag( mdh_p->mph.msg );
						return PRINT_RESULT_COMMAND;
					case NC_MV_SCROLL_:		// キー待ちスクロール
						mdh_p->seq	= PRINTSEQ_TRGWAIT_SCROLL;
						PokeFontTriggerCursorAnimeInit(mdh_p);
						mdh_p->mph.msg = STRCODE_SkipTag( mdh_p->mph.msg );
						return PRINT_RESULT_COMMAND;
					}
				}
				break;
			}

			mdh_p->mph.msg = STRCODE_SkipTag( mdh_p->mph.msg );
			return PRINT_RESULT_LOOP;

		/* "▼"		トリガー待ち→MSGエリアクリア(＋描画開始リセット) */
		case NORMAL_WAIT_:
			mdh_p->seq	= PRINTSEQ_TRGWAIT_CLEAR;
			PokeFontTriggerCursorAnimeInit(mdh_p);
			return PRINT_RESULT_COMMAND;
	
		/* "▽"		トリガー待ち→一行スクロール(＋改行) */
		case SCROLL_WAIT_:
			mdh_p->seq	= PRINTSEQ_TRGWAIT_SCROLL;
			PokeFontTriggerCursorAnimeInit(mdh_p);
			return PRINT_RESULT_COMMAND;

		}
		font_bmp = FontDataGet( mpu_p->fmode, fcode );

		//各種フォント描画
		GF_BGL_BmpWinPrintMsgWide(
			mdh_p->mph.bmpwin, font_bmp->data,
			font_bmp->size_x, font_bmp->size_y,
			mdh_p->mph.write_x,mdh_p->mph.write_y, mdh_p->mph.dot_tbl );

		//次の文字の描画位置を設定
		mdh_p->mph.write_x += (font_bmp->size_x + mdh_p->mph.space_x);
		return PRINT_RESULT_WRITE;

	case PRINTSEQ_TRGWAIT:		//トリガー待ち
		if(PokeFontTriggerWait2(mdh_p)){
			PokeFontTriggerCursorAnimeExit2(mdh_p);
			mdh_p->seq	= PRINTSEQ_WRITE;
		}
		return PRINT_RESULT_COMMAND;

	case PRINTSEQ_TRGWAIT_CLEAR:		//トリガー待ち→MSGエリアクリア
		if(PokeFontTriggerWait(mdh_p)){
			//エリアクリア
			PokeFontTriggerCursorAnimeExit2(mdh_p);	//下で同時にクリア
			GF_BGL_BmpWinDataFill( mdh_p->mph.bmpwin, mdh_p->mph.b_col );
			mdh_p->mph.write_x = mdh_p->mph.start_x;
			mdh_p->mph.write_y = mdh_p->mph.start_y;
			mdh_p->seq	= PRINTSEQ_WRITE;
		}
		return PRINT_RESULT_COMMAND;

	case PRINTSEQ_TRGWAIT_SCROLL:		//トリガー待ち→スクロール
		if(PokeFontTriggerWait( mdh_p )){
			PokeFontTriggerCursorAnimeExit2(mdh_p);
			//スクロール幅設定(Yの高さ分 + 表示幅)
			mdh_p->scrwork	=( FontHeaderGet( mdh_p->mph.fnt_index, FONT_HEADER_SIZE_Y ) + mdh_p->mph.space_y ); 
			mdh_p->mph.write_x = mdh_p->mph.start_x;
			mdh_p->seq	= PRINTSEQ_SCROLL;
		}
		return PRINT_RESULT_COMMAND;

	case PRINTSEQ_SCROLL:				//スクロール処理
		if( mdh_p->scrwork )
		{
			scr_sp = scr_speed_value[2];

			if(mdh_p->scrwork < scr_sp)
			{
				GF_BGL_BmpWinShift(
					mdh_p->mph.bmpwin, GF_BGL_BMPWIN_SHIFT_U,
					mdh_p->scrwork, (mdh_p->mph.b_col<<4)|mdh_p->mph.b_col );
				mdh_p->scrwork = 0;
			}
			else
			{
				GF_BGL_BmpWinShift(
					mdh_p->mph.bmpwin, GF_BGL_BMPWIN_SHIFT_U,
					scr_sp, (mdh_p->mph.b_col<<4)|mdh_p->mph.b_col );
				mdh_p->scrwork -= scr_sp;
			}

			GF_BGL_BmpWinOn( mdh_p->mph.bmpwin );

		}
		else
		{
			mdh_p->seq	= PRINTSEQ_WRITE;
		}
		return PRINT_RESULT_COMMAND;

	case PRINTSEQ_SE_WAIT:			//SEウェイト
		mdh_p->seq	= PRINTSEQ_WRITE;
		return PRINT_RESULT_COMMAND;

	case PRINTSEQ_FORCEWAIT:		//強制ウェイト
		if( mdh_p->waitwork )
		{
			mdh_p->waitwork--;
		}
		else
		{
			mdh_p->seq	= PRINTSEQ_WRITE;
		}
		return PRINT_RESULT_COMMAND;
	}
	return PRINT_RESULT_END;
}

//=============================================================================================
/**
 *		トリガー待ちカーソル表示
 */
//=============================================================================================
static u16 TrgCursorCgxPos = 0;

void PokeFontTrgCursorCgxSet( u16 cgx )
{
	TrgCursorCgxPos = cgx;
}

void		PokeFontTriggerCursorAnimeInit(MSG_DATA_HEADER* mdh_p)
{
	MSG_PRINT_USER*	mpu_p;

	mpu_p = (MSG_PRINT_USER*)&(mdh_p->userwork[0]);

	if(msg_print_flag.auto_f){
		mpu_p->rep_wait = 0;	//オート中ウェイトワーク初期化
	}else{
		mpu_p->cur_anm  = 0;
		mpu_p->cur_wait = 0;
	}
}

static const u8 CursorAnmData[] = {0,1,2,1,};

void PokeFontTriggerCursorAnime2( MSG_DATA_HEADER * mdh_p )
{
	MSG_PRINT_USER * mpu_p;
	void * cgx;

	mpu_p = (MSG_PRINT_USER *)&(mdh_p->userwork[0]);

	if(msg_print_flag.auto_f){
		return;
	}
	if(mpu_p->cur_wait){
		mpu_p->cur_wait--;
		return;
	}

	{
		u16	cgx;
		u8	frm, px, py, sx;

		frm = GF_BGL_BmpWinGet_Frame( mdh_p->mph.bmpwin );
		px  = GF_BGL_BmpWinGet_PosX( mdh_p->mph.bmpwin );
		py  = GF_BGL_BmpWinGet_PosY( mdh_p->mph.bmpwin );
		sx  = GF_BGL_BmpWinGet_SizeX( mdh_p->mph.bmpwin );
		cgx = TrgCursorCgxPos;

		GF_BGL_ScrFill(
			mdh_p->mph.bmpwin->ini, frm, cgx+18+(CursorAnmData[mpu_p->cur_anm]*4),
			px+sx+1, py+2, 1, 1, GF_BGL_SCRWRT_PALNL );
		GF_BGL_ScrFill(
			mdh_p->mph.bmpwin->ini, frm, cgx+19+(CursorAnmData[mpu_p->cur_anm]*4),
			px+sx+2, py+2, 1, 1, GF_BGL_SCRWRT_PALNL );
		GF_BGL_ScrFill(
			mdh_p->mph.bmpwin->ini, frm, cgx+20+(CursorAnmData[mpu_p->cur_anm]*4),
			px+sx+1, py+3, 1, 1, GF_BGL_SCRWRT_PALNL );
		GF_BGL_ScrFill(
			mdh_p->mph.bmpwin->ini, frm, cgx+21+(CursorAnmData[mpu_p->cur_anm]*4),
			px+sx+2, py+3, 1, 1, GF_BGL_SCRWRT_PALNL );
		GF_BGL_LoadScreenReq( mdh_p->mph.bmpwin->ini, frm );

		mpu_p->cur_wait = CURSOR_WAIT_TIME;
		mpu_p->cur_anm++;
	}
}

void PokeFontTriggerCursorAnimeExit2( MSG_DATA_HEADER* mdh_p )
{
	u16	cgx;
	u8	frm, px, py, sx;

	frm = GF_BGL_BmpWinGet_Frame( mdh_p->mph.bmpwin );
	px  = GF_BGL_BmpWinGet_PosX( mdh_p->mph.bmpwin );
	py  = GF_BGL_BmpWinGet_PosY( mdh_p->mph.bmpwin );
	sx  = GF_BGL_BmpWinGet_SizeX( mdh_p->mph.bmpwin );
	cgx = TrgCursorCgxPos;

	GF_BGL_ScrFill(
		mdh_p->mph.bmpwin->ini, frm, cgx+10, px+sx+1, py+2, 1, 2, GF_BGL_SCRWRT_PALNL );
	GF_BGL_ScrFill(
		mdh_p->mph.bmpwin->ini, frm, cgx+11, px+sx+2, py+2, 1, 2, GF_BGL_SCRWRT_PALNL );

	GF_BGL_LoadScreenReq( mdh_p->mph.bmpwin->ini, frm );
}















//=============================================================================================
/**
 *		トリガー待ち関数(0:wait中,1:次へ)
 */
//=============================================================================================
static BOOL PokeFontTriggerWaitCheck( MSG_DATA_HEADER * mdh_p )
{
	if( ( sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL) ) ||
		( (sys.tp_trg) && (msg_print_flag.tp_f) ) ){
		Snd_SePlay( SE_MSG_SKIP );
		msg_print_flag.btl_wait_f = 1;
		return TRUE;
	}
	return FALSE;
}

BOOL PokeFontTriggerWaitReplayCheck(MSG_DATA_HEADER* mdh_p)
{
	MSG_PRINT_USER*	mpu_p;
	u16	wait_len;

	mpu_p = (MSG_PRINT_USER*)&(mdh_p->userwork[0]);

	wait_len = AUTO_MSGTRGWAIT;

	if(mpu_p->rep_wait == wait_len){	//リプレイ中ウェイト一定
		return TRUE;
	}
	mpu_p->rep_wait++;

	if( msg_print_flag.auto_f_skip ){
		return PokeFontTriggerWaitCheck( mdh_p );
	}

	return FALSE;
}


BOOL PokeFontTriggerWait( MSG_DATA_HEADER* mdh_p )
{
	BOOL flg = FALSE;

	if(msg_print_flag.auto_f){
		//オート送りウェイトチェック
		flg = PokeFontTriggerWaitReplayCheck(mdh_p);
	}else{
		PokeFontTriggerCursorAnime2(mdh_p);
		flg = PokeFontTriggerWaitCheck( mdh_p );
	}
	return flg;
}

BOOL PokeFontTriggerWait2(MSG_DATA_HEADER* mdh_p)
{
	u8	flg = FALSE;

	if(msg_print_flag.auto_f){
		//オート送りウェイトチェック
		flg = PokeFontTriggerWaitReplayCheck(mdh_p);
	}else{
		flg = PokeFontTriggerWaitCheck( mdh_p );
	}
	return flg;
}









//=============================================================================================
//	描画制御
//=============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * スキップ設定
 *
 * @param	flg		フラグ
 *
 * @return	none
 *
 *	flg = MSG_SKIP_OFF : スキップ無効
 *	flg = MSG_SKIP_ON  : スキップ有効
 */
//--------------------------------------------------------------------------------------------
void MsgPrintSkipFlagSet( int flg )
{
	msg_print_flag.skip_f = flg;
}

//--------------------------------------------------------------------------------------------
/**
 * 自動送り設定
 *
 * @param	flg		フラグ
 *
 * @return	none
 *
 *	flg = MSG_AUTO_OFF     : 自動送り無効
 *	flg = MSG_AUTO_ON      : 自動送り有効
 *	flg = MSG_AOTO_SKIP_ON : 自動送り有効/ボタンスキップ有効
 */
//--------------------------------------------------------------------------------------------
void MsgPrintAutoFlagSet( int flg )
{
	msg_print_flag.auto_f      = (flg&1);
	msg_print_flag.auto_f_skip = ((flg>>1)&1);
}

//--------------------------------------------------------------------------------------------
/**
 * タッチパネル送り設定
 *
 * @param	flg		フラグ
 *
 * @return	none
 *
 *	flg = MSG_TP_OFF : タッチパネル無効
 *	flg = MSG_TP_ON  : タッチパネル有効
 */
//--------------------------------------------------------------------------------------------
void MsgPrintTouchPanelFlagSet( int flg )
{
	msg_print_flag.tp_f = flg;
}


//--------------------------------------------------------------------------------------------
/**
 * 戦闘用：スキップ中か
 *
 * @param	none
 *
 * @retval	"1 = 送り中"
 * @retval	"0 = それ以外"
 */
//--------------------------------------------------------------------------------------------
u8 MsgPrintBattleSkipPushFlagGet(void)
{
	return msg_print_flag.btl_skip_f;
}

void MsgPrintBattleSkipPushFlagClear(void)
{
	msg_print_flag.btl_skip_f = 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 戦闘用：▼を送ったか
 *
 * @param	none
 *
 * @retval	"1 = 送り中"
 * @retval	"0 = それ以外"
 */
//--------------------------------------------------------------------------------------------
u8 MsgPrintBattleWaitPushFlagGet(void)
{
	return msg_print_flag.btl_wait_f;
}
void MsgPrintBattleWaitPushFlagClear(void)
{
	msg_print_flag.btl_wait_f = 0;
}
