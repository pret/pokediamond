//==============================================================================
/**
 * @file	con_record.c
 * @brief	コンテスト通信対戦成績画面
 * @author	matsuda
 * @date	2006.06.05(月)
 */
//==============================================================================
#include "common.h"
#include "contest/contest.h"
#include "con_tool.h"

#include "field/field.h"
#include "field/fieldsys.h"
#include "field/fld_bmp.h"
#include "field/fieldmap.h"
#include "gflib/bg_system.h"
#include "system/window.h"

#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/fontproc.h"
#include "system/msgdata.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_cmsg_linkresult.h"

#include "contest/contest.h"
#include "savedata/contest_savedata.h"

#include "field/ev_mapchange.h"


//==============================================================================
//	定数定義
//==============================================================================
#define RECORD_WINDOW_CGX_START	(1)

#define RECORD_TALK_PAL			(FLD_MESFONT_PAL)

#define RECORD_BMPWIN_PAL		(MENU_WIN_PAL)
#define RECORD_BMPWIN_CHAROFS	(RECORD_WINDOW_CGX_START + 10)
#define RECORD_BMPWIN_FRAME		(FLD_MBGFRM_FONT)

#define RECORD_BMPWIN_POS_X		(1)
#define RECORD_BMPWIN_POS_Y		(3)
#define RECORD_BMPWIN_SIZE_X	(30)
#define RECORD_BMPWIN_SIZE_Y	(17)

///座標設定タイプ
enum{
	POSTYPE_LEFT,			///<左端座標
	POSTYPE_CENTER,			///<中心座標
	POSTYPE_RIGHT,			///<右端座標
};

//--------------------------------------------------------------
//	メッセージ表示座標
//--------------------------------------------------------------
#define CR_MY_NAME_X		(15*8)		//中央寄せ
#define CR_MY_NAME_Y		(8 * 0)

#define CR_TITLE_X			(CR_MY_NAME_X)		//中央寄せ
#define CR_TITLE_Y			(8 * 2)


//==============================================================================
//	構造体定義
//==============================================================================
///コンテスト通信対戦成績画面システムワーク構造体
typedef struct {
	GF_BGL_BMPWIN	win;
	MSGDATA_MANAGER * mman;	// メッセージデータマネージャ
	WORDSET * wset;			// 単語セット
}CON_RECORD_WORK;

///メッセージデータID＆座標設定
typedef struct{
	u32 msg_id;		///<メッセージID
	s16 x;			///<座標X(BMPWIN内の)
	s16 y;			///<座標Y(BMPWIN内の)
}CR_MSG_DATA;

///通信対戦成績画面イベント制御タスクで使用するワーク
typedef struct{
	void *sys;			///<通信対戦成績画面システムワークへのポインタ
	int seq;			///<シーケンス番号
}CON_RECORD_SEQ_WORK;


//==============================================================================
//	データ
//==============================================================================
///コンテストタイプの表示メッセージIDと座標データ
static const CR_MSG_DATA MsgData_ConType[] = {
	{msg_con_link_result_03, 8*1, 8*7},		//X:左寄せ
	{msg_con_link_result_04, 8*1, 8*9},
	{msg_con_link_result_05, 8*1, 8*11},
	{msg_con_link_result_06, 8*1, 8*13},
	{msg_con_link_result_07, 8*1, 8*15},
};

///順位の表示メッセージIDと座標データ
static const CR_MSG_DATA MsgData_Ranking[] = {
	{msg_con_link_result_08, 8*14, 8*5},		//X:右寄せ
	{msg_con_link_result_09, 8*19, 8*5},
	{msg_con_link_result_10, 8*24, 8*5},
	{msg_con_link_result_11, 8*29, 8*5},
};

///勝利数の表示メッセージIDと座標データ
static const CR_MSG_DATA MsgData_Num[][BREEDER_MAX] = {	//X:右寄せ
	{//かっこよさ
		{msg_con_link_result_12, 8*14, 8*7},
		{msg_con_link_result_13, 8*19, 8*7},
		{msg_con_link_result_14, 8*24, 8*7},
		{msg_con_link_result_15, 8*29, 8*7},
	},
	{//うつくしさ
		{msg_con_link_result_16, 8*14, 8*9},
		{msg_con_link_result_17, 8*19, 8*9},
		{msg_con_link_result_18, 8*24, 8*9},
		{msg_con_link_result_19, 8*29, 8*9},
	},
	{//かわいさ
		{msg_con_link_result_20, 8*14, 8*11},
		{msg_con_link_result_21, 8*19, 8*11},
		{msg_con_link_result_22, 8*24, 8*11},
		{msg_con_link_result_23, 8*29, 8*11},
	},
	{//かしこさ
		{msg_con_link_result_24, 8*14, 8*13},
		{msg_con_link_result_25, 8*19, 8*13},
		{msg_con_link_result_26, 8*24, 8*13},
		{msg_con_link_result_27, 8*29, 8*13},
	},
	{//たくましさ
		{msg_con_link_result_28, 8*14, 8*15},
		{msg_con_link_result_29, 8*19, 8*15},
		{msg_con_link_result_30, 8*24, 8*15},
		{msg_con_link_result_31, 8*29, 8*15},
	},
};


//==============================================================================
//	プロトタイプ宣言
//==============================================================================
static int FontPosXGet(const STRBUF *strbuf, FONT_TYPE font_type, int pos_type, int x);
static BOOL GMEVENT_Sub_ConRecord(GMEVENT_CONTROL * event);



//--------------------------------------------------------------
/**
 * @brief   イベント擬似コマンド：コンテスト通信対戦成績画面
 *
 * @param   event		イベント制御ワークへのポインタ
 */
//--------------------------------------------------------------
void EventCmd_ConRecordDisp(GMEVENT_CONTROL *event)
{
	CON_RECORD_SEQ_WORK *crs;
	
	crs = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(CON_RECORD_SEQ_WORK));
	MI_CpuClear8(crs, sizeof(CON_RECORD_SEQ_WORK));
	
	FieldEvent_Call(event, GMEVENT_Sub_ConRecord, crs);
}

//--------------------------------------------------------------
/**
 * @brief   コンテスト通信対戦成績画面イベント進行タスク
 *
 * @param   event		イベント制御ワークへのポインタ
 */
//--------------------------------------------------------------
static BOOL GMEVENT_Sub_ConRecord(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK *fsys = FieldEvent_GetFieldSysWork(event);
	CON_RECORD_SEQ_WORK *crs = FieldEvent_GetSpecialWork(event);

	switch(crs->seq){
	case 0:
		crs->sys = ContestSioRecord_Create(fsys);
		crs->seq++;
		break;
	case 1:
		if(sys.trg & (PAD_BUTTON_DECIDE | PAD_BUTTON_CANCEL)){
			ContestSioRecord_Delete(crs->sys);
			crs->seq++;
		}
		break;
	case 2:
		sys_FreeMemoryEz(crs);
		return TRUE;
	}
	return FALSE;
}


//--------------------------------------------------------------
/**
 * @brief   コンテスト通信対戦成績画面作成
 *
 * @param   fsys		
 *
 * @retval  通信対戦成績画面システムワークへのポインタ
 */
//--------------------------------------------------------------
void * ContestSioRecord_Create( void * fsys )
{
	CON_RECORD_WORK * rec;
	GF_BGL_INI * bgl;
	STRBUF *strbuf, *dest_strbuf;
	int set_x, num, i, s;
	SAVEDATA *sv;
	
	bgl = FieldBglIniGet( fsys );
	sv = GameSystem_GetSaveData(fsys);
	
	rec = sys_AllocMemory(HEAPID_WORLD, sizeof(CON_RECORD_WORK));
	MI_CpuClear8(rec, sizeof(CON_RECORD_WORK));

	rec->mman = MSGMAN_Create(
				MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_cmsg_linkresult_dat, HEAPID_WORLD);
	rec->wset = WORDSET_Create(HEAPID_WORLD);

	GF_BGL_BmpWinAdd( bgl, &rec->win, RECORD_BMPWIN_FRAME, 
		RECORD_BMPWIN_POS_X, RECORD_BMPWIN_POS_Y, RECORD_BMPWIN_SIZE_X, RECORD_BMPWIN_SIZE_Y, 
		RECORD_TALK_PAL, RECORD_BMPWIN_CHAROFS);

	MenuWinGraphicSet(bgl, RECORD_BMPWIN_FRAME, RECORD_WINDOW_CGX_START, RECORD_BMPWIN_PAL,
		MENU_TYPE_SYSTEM, HEAPID_WORLD);
	BmpMenuWinWrite( &rec->win, WINDOW_TRANS_OFF, RECORD_WINDOW_CGX_START, RECORD_BMPWIN_PAL);

	GF_BGL_BmpWinDataFill(&rec->win, 15);
	
	//-- メッセージ描画 --//
	dest_strbuf = STRBUF_Create(100, HEAPID_WORLD);
	//じぶんの
	strbuf = MSGMAN_AllocString(rec->mman, msg_con_link_result_01);
	WORDSET_RegisterPlayerName(rec->wset, 0, SaveData_GetMyStatus(sv));
	WORDSET_ExpandStr(rec->wset, dest_strbuf, strbuf);
	set_x = FontPosXGet(dest_strbuf, FONT_SYSTEM, POSTYPE_CENTER, CR_MY_NAME_X);
	GF_STR_PrintSimple(&rec->win, FONT_SYSTEM, dest_strbuf, 
		set_x, CR_MY_NAME_Y, MSG_NO_PUT, NULL);
	STRBUF_Delete(strbuf);
	
	//つうしん　コンテスト　せいせき
	strbuf = MSGMAN_AllocString(rec->mman, msg_con_link_result_02);
	set_x = FontPosXGet(strbuf, FONT_SYSTEM, POSTYPE_CENTER, CR_TITLE_X);
	GF_STR_PrintSimple(&rec->win, FONT_SYSTEM, strbuf, 
		set_x, CR_TITLE_Y, MSG_NO_PUT, NULL);
	STRBUF_Delete(strbuf);
	
	//かっこよさ　うつくしさ・・・
	for(i = 0; i < CONTYPE_MAX; i++){
		strbuf = MSGMAN_AllocString(rec->mman, MsgData_ConType[i].msg_id);
		set_x = FontPosXGet(strbuf, FONT_SYSTEM, POSTYPE_LEFT, MsgData_ConType[i].x);
		GF_STR_PrintSimple(&rec->win, FONT_SYSTEM, strbuf, 
			set_x, MsgData_ConType[i].y, MSG_NO_PUT, NULL);
		STRBUF_Delete(strbuf);
	}
	
	//１い　２い　３い　４い
	for(i = 0; i < BREEDER_MAX; i++){
		strbuf = MSGMAN_AllocString(rec->mman, MsgData_Ranking[i].msg_id);
		set_x = FontPosXGet(strbuf, FONT_SYSTEM, POSTYPE_RIGHT, MsgData_Ranking[i].x);
		GF_STR_PrintSimple(&rec->win, FONT_SYSTEM, strbuf, 
			set_x, MsgData_Ranking[i].y, MSG_NO_PUT, NULL);
		STRBUF_Delete(strbuf);
	}

	for(s = 0; s < CONTYPE_MAX; s++){
		for(i = 0; i < BREEDER_MAX; i++){
			num = CONDATA_GetValue(sv, s, i);
			strbuf = MSGMAN_AllocString(rec->mman, MsgData_Num[s][i].msg_id);
			WORDSET_RegisterNumber(rec->wset, 0, num, 4, 
				NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT);
			WORDSET_ExpandStr(rec->wset, dest_strbuf, strbuf);
			set_x = FontPosXGet(dest_strbuf, FONT_SYSTEM, POSTYPE_RIGHT, MsgData_Num[s][i].x);
			GF_STR_PrintSimple(&rec->win, FONT_SYSTEM, dest_strbuf, 
				set_x, MsgData_Num[s][i].y, MSG_NO_PUT, NULL);
			STRBUF_Delete(strbuf);
		}
	}
	
	STRBUF_Delete(dest_strbuf);
	
	
	//-- 描画ON --//
	GF_BGL_BmpWinOn( &rec->win );
	
	return rec;
}

//--------------------------------------------------------------
/**
 * @brief   コンテスト通信対戦成績画面削除
 *
 * @param   rec		通信対戦成績画面システムワークへのポインタ
 */
//--------------------------------------------------------------
void ContestSioRecord_Delete(void *con_rec)
{
	CON_RECORD_WORK *rec = con_rec;
	
	BmpMenuWinClear( &rec->win, WINDOW_TRANS_OFF );

	GF_BGL_BmpWinOff( &rec->win );
	GF_BGL_BmpWinDel( &rec->win );

	MSGMAN_Delete( rec->mman );
	WORDSET_Delete( rec->wset );
	
	sys_FreeMemoryEz(rec);
}

//--------------------------------------------------------------
/**
 * @brief   文字列から表示するX座標を取得する
 *
 * @param   strbuf			文字列へのポインタ
 * @param   font_type		フォントタイプ
 * @param   pos_type		座標タイプ
 * @param   x				X座標(座標タイプで設定した時のX座標)
 *
 * @retval  X座標
 */
//--------------------------------------------------------------
static int FontPosXGet(const STRBUF *strbuf, FONT_TYPE font_type, int pos_type, int x)
{
	int dot_len, char_len;
	
	if(pos_type == POSTYPE_LEFT){
		return x;
	}
	
	//文字列のドット幅から、使用するキャラ数を算出する
	dot_len = FontProc_GetPrintStrWidth(font_type, strbuf, 0);
	switch(pos_type){
	case POSTYPE_CENTER:
		return x - dot_len / 2;
	case POSTYPE_RIGHT:
		return x - dot_len;
	}
	GF_ASSERT(0 && "不明なpos_type");
	return x;
}

