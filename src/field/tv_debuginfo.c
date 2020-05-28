//============================================================================================
/**
 * @file	tv_debuginfo.c
 * @brief
 * @date	2006.07.09
 * @author	tamada GAME FREAK inc.
 */
//============================================================================================

#include "common.h"
#include "fieldsys.h"

#include "fld_bmp.h"
#include "system/window.h"
#include "system/fontproc.h"
#include "fieldmap.h"

#include "savedata/tv_work.h"
#include "gflib/gf_date.h"

#include "fld_debug.h"

#include "system/msgdata.h"
#include "system/wordset.h"
#include "system/msgdata_util.h"
#include "gflib/strbuf_family.h"

#include "msgdata/msg.naix"
#include "msgdata/msg_debug_tv.h"

//============================================================================================
//============================================================================================

enum {
	DTV_WIN_PX = 1,
	DTV_WIN_PY = 1,
	DTV_WIN_SX = 30,
	DTV_WIN_SY = 22,

	DTV_MSG_PAL = FLD_MENU_WIN_PAL,
	DTV_WIN_PAL = MENU_WIN_PAL,
	DTV_WIN_CGX = MENU_WIN_CGX_NUM,

	DTV_MSG_CGX = 1,
};

//--------------------------------------------------------------------
//--------------------------------------------------------------------
typedef struct {
	int page;
	int heapID;
	u8 frame_no;
	FIELDSYS_WORK * fsys;
	GF_BGL_INI * bgl;
	GF_BGL_BMPWIN * win;
	WORDSET * ws;
	MSGDATA_MANAGER * msgman;
	MATHCRC16Table crc_table;
}DEBUG_TV_WORK;

//--------------------------------------------------------------------
//--------------------------------------------------------------------
typedef struct {
	u8 isMine;
	u8 type;
	u8 ofs;
}PAGE_PARAM;

static const PAGE_PARAM PageParamData[] = {
	{ TRUE,	TVTOPICTYPE_INTERVIEW, 0, },
	{ TRUE, TVTOPICTYPE_WATCH,	0},
	{ TRUE,	TVTOPICTYPE_RECORD,	0},
	{ FALSE, TVTOPICTYPE_INTERVIEW, 0},	
	{ FALSE, TVTOPICTYPE_INTERVIEW, 1},	
	{ FALSE, TVTOPICTYPE_WATCH, 0},
	{ FALSE, TVTOPICTYPE_WATCH, 1},
	{ FALSE, TVTOPICTYPE_WATCH, 2},
	{ FALSE, TVTOPICTYPE_WATCH, 3},
	{ FALSE, TVTOPICTYPE_RECORD, 0},
	{ FALSE, TVTOPICTYPE_RECORD, 1},
};

//============================================================================================
//============================================================================================
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Print(DEBUG_TV_WORK * dtw, int id, int x, int y)
{
	STRBUF * msg;
	msg = MSGDAT_UTIL_AllocExpandString(dtw->ws, dtw->msgman, id, dtw->heapID);
	GF_STR_PrintSimple(dtw->win, FONT_SYSTEM, msg, x, y, MSG_NO_PUT, NULL);
	STRBUF_Delete(msg);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void PrintTopic(DEBUG_TV_WORK * dtw, TVTOPIC * topic, int x, int y)
{
	int topic_id;
	STRBUF * msg;
	u16 crc;

	topic_id = TVTOPIC_GetTopicID(topic);

	if (topic_id == 0) {
		Print(dtw, MSG_DEBUGTV_NO_TOPIC, x, y);
	} else {
		GF_DATE date = TVTOPIC_GetDate(topic);
		crc = MATH_CalcCRC16CCITT(&dtw->crc_table, TVTOPIC_GetData(topic), TOPIC_DATA_SIZE);
		WORDSET_RegisterNumber(dtw->ws, 0, topic_id, 2,
				NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT);
		WORDSET_RegisterNumber(dtw->ws, 1, TVTOPIC_GetSeeCount(topic), 1,
				NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT);
		WORDSET_RegisterNumber(dtw->ws, 2, GFDate_GetYear(date), 2,
				NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT);
		WORDSET_RegisterNumber(dtw->ws, 3, GFDate_GetMonth(date), 2,
				NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT);
		WORDSET_RegisterNumber(dtw->ws, 4, GFDate_GetDay(date), 2,
				NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT);
		WORDSET_RegisterNumber(dtw->ws, 5, crc, 5,
				NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT);
		Print(dtw, MSG_DEBUGTV_TOPIC, x, y);
	}
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void PrintOtherInfo(DEBUG_TV_WORK * dtw, OTHER_TOPIC * ot, int x, int y)
{
	TVTOPIC * topic;
	STRBUF * strbuf;
	STRBUF * msg;

	topic = OTHERTOPIC_GetTopicData(ot);
	if (TVTOPIC_GetTopicID(topic) == 0) {
		return;
	}
	strbuf = STRBUF_Create(64, dtw->heapID);
	STRBUF_SetStringCode(strbuf, OTHERTOPIC_GetName(ot));
	WORDSET_RegisterNumber(dtw->ws, 0, OTHERTOPIC_GetOwnerID(ot) & 0xffff, 5,
			NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT);
	WORDSET_RegisterWord(dtw->ws, 1, strbuf, OTHERTOPIC_GetSex(ot), TRUE, OTHERTOPIC_GetRegionCode(ot));
	WORDSET_RegisterNumber(dtw->ws, 2, OTHERTOPIC_GetRegionCode(ot), 2,
			NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT);

	Print(dtw, MSG_DEBUGTV_OTHER_INFO, x, y);

	STRBUF_Delete(strbuf);
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void PrintMyTopic(DEBUG_TV_WORK * dtw, TVTOPICTYPE type)
{
	static u8 MsgID[] = {
		MSG_DEBUGTV_MY_QANDA,
		MSG_DEBUGTV_MY_WATCH,
		MSG_DEBUGTV_MY_RECORD,
	};
	STRBUF * msg;
	TV_WORK * tvwk = SaveData_GetTvWork(dtw->fsys->savedata);
	TVTOPIC * topic;
	int topic_id;
	int i;
	int x, y, my;
	x = 0;
	y = 0;
	my = FontHeaderGet(FONT_SYSTEM, FONT_HEADER_SIZE_Y)
				+ FontHeaderGet(FONT_SYSTEM, FONT_HEADER_SPACE_Y);

	Print(dtw, MsgID[type - 1], x, y);
	y += my * 2;

	for (i = 0; i < 4; i++) {
		topic = MYTOPIC_GetTopic(TVWORK_GetMyTopicByIndex(tvwk, type, i + 1));
		PrintTopic(dtw, topic, x, y);
		y += my;
	}
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void PrintOtherTopic(DEBUG_TV_WORK * dtw, TVTOPICTYPE type, int offset)
{
	static u8 MsgID[] = {
		MSG_DEBUGTV_OTHER_QANDA,
		MSG_DEBUGTV_OTHER_WATCH,
		MSG_DEBUGTV_OTHER_RECORD,
	};
	STRBUF * msg;
	TV_WORK * tvwk = SaveData_GetTvWork(dtw->fsys->savedata);
	OTHER_TOPIC * ot;
	TVTOPIC * topic;
	int topic_id;
	int i;
	int x, y, my;
	x = 0;
	y = 0;
	my = FontHeaderGet(FONT_SYSTEM, FONT_HEADER_SIZE_Y)
				+ FontHeaderGet(FONT_SYSTEM, FONT_HEADER_SPACE_Y);

	WORDSET_RegisterNumber(dtw->ws, 0, offset + 1, 2,
				NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT);
	Print(dtw, MsgID[type - 1], x, y);
	y += my * 2;

	for (i = 0; i < 4; i++) {
		ot = TVWORK_GetOtherTopicByIndex(tvwk, type, TVWORK_MakeOtherIndex(i + 1 + offset * 4));
		topic = OTHERTOPIC_GetTopicData(ot);
		PrintOtherInfo(dtw, ot, x, y);
		y += my;
		PrintTopic(dtw, topic, x, y);
		y += my;
	}
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void DEBUGTV_WriteWindow(DEBUG_TV_WORK * dtw)
{
	//BMP制御ワークを確保
	dtw->win = sys_AllocMemory(dtw->heapID, sizeof(GF_BGL_BMPWIN));
	//bitmap領域を追加
	GF_BGL_BmpWinAdd(dtw->bgl, dtw->win, dtw->frame_no,
			DTV_WIN_PX, DTV_WIN_PY, DTV_WIN_SX, DTV_WIN_SY,
			DTV_MSG_PAL, DTV_MSG_CGX);
	//ウィンドウ枠キャラ、パレットをセット
	MenuWinGraphicSet(
		dtw->bgl, dtw->frame_no, DTV_WIN_CGX, DTV_WIN_PAL, MENU_TYPE_SYSTEM, dtw->heapID); 
	//ウィンドウ枠内を塗りつぶす
	GF_BGL_BmpWinDataFill(dtw->win, FontHeaderGet(FONT_SYSTEM, FONT_HEADER_B_COLOR));
	//内容を描画
	//printinfo(dtw);
	//ウィンドウ枠描画
	BmpMenuWinWrite(dtw->win, WINDOW_TRANS_ON, DTV_WIN_CGX, DTV_WIN_PAL);
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void DEBUGTV_EraseWindow(DEBUG_TV_WORK * dtw)
{
	//ウィンドウ消去
	BmpMenuWinClear(dtw->win, WINDOW_TRANS_ON);
	//bitmap領域を削除
	GF_BGL_BmpWinDel(dtw->win);
	//BMP制御ワークを削除
	sys_FreeMemoryEz(dtw->win);
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
static DEBUG_TV_WORK * DEBUGTV_Create(FIELDSYS_WORK * fsys, int heapID, int frame_no)
{
	DEBUG_TV_WORK * dtw = sys_AllocMemory(heapID, sizeof(DEBUG_TV_WORK));
	dtw->page = 0;
	dtw->fsys = fsys;
	dtw->bgl = fsys->bgl;
	dtw->frame_no = frame_no;
	dtw->heapID = heapID;
	dtw->ws = WORDSET_Create(heapID);
	dtw->msgman = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_debug_tv_dat, heapID);
	MATH_CRC16CCITTInitTable(&dtw->crc_table);

	return dtw;
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void DEBUGTV_Delete(DEBUG_TV_WORK * dtw)
{
	WORDSET_Delete(dtw->ws);
	MSGMAN_Delete(dtw->msgman);
	sys_FreeMemoryEz(dtw);
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void PrintPage(DEBUG_TV_WORK * dtw)
{
	const PAGE_PARAM * prm = &PageParamData[dtw->page];
	GF_BGL_BmpWinDataFill(dtw->win, FontHeaderGet(FONT_SYSTEM, FONT_HEADER_B_COLOR));
	if (prm->isMine) {
		PrintMyTopic(dtw, prm->type);
	} else {
		PrintOtherTopic(dtw, prm->type, prm->ofs);
	}
	GF_BGL_BmpWinOnVReq(dtw->win);
}
//============================================================================================
//============================================================================================
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static BOOL GMEVENT_TVDebugInfo(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	DEBUG_TV_WORK * dtw = FieldEvent_GetSpecialWork(event);
	int * seq = FieldEvent_GetSeqWork(event);

	switch (*seq) {
	case 0:
		DEBUGTV_WriteWindow(dtw);
		PrintPage(dtw);
		(*seq) ++;
	case 1:
		if (sys.trg & PAD_KEY_LEFT) {
			dtw->page --;
			if (dtw->page < 0) {
				dtw->page = NELEMS(PageParamData) - 1;
			}
			PrintPage(dtw);
		} else if (sys.trg & PAD_KEY_RIGHT) {
			dtw->page ++;
			if (dtw->page == NELEMS(PageParamData)) {
				dtw->page = 0;
			}
			PrintPage(dtw);
		} else if (sys.trg & (PAD_BUTTON_A|PAD_BUTTON_B)) {
			(*seq) ++;
		}
		break;
	case 2:
		DEBUGTV_EraseWindow(dtw);
		(*seq) ++;
		break;
	case 3:
		DEBUGTV_Delete(dtw);
		return TRUE;
	}
	return FALSE;
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
void EventSet_TVDebugInfo(FIELDSYS_WORK * fsys)
{
	DEBUG_TV_WORK * dtw;
	dtw = DEBUGTV_Create(fsys, HEAPID_FIELD, FLD_MBGFRM_FONT);
	FieldEvent_Set(fsys, GMEVENT_TVDebugInfo, dtw);
}



