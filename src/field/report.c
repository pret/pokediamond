//============================================================================================
/**
 * @file	report.c
 * @brief	セーブ関連
 * @author	tamada GAME FREAK inc.
 * @date	2005.12.05
 *
 * 「レポートをかく」の情報ウィンドウの制御関数などがある
 *
 * 修正予定：
 *	プレイ時間をリアルタイムで更新する
 *	ゲーム開始時のウィンドウでも同じ内容が引っ張れるように外部インターフェイスを作る
 *
 */
//============================================================================================

#include "common.h"

#include "fieldsys.h"

#include "fld_bmp.h"
#include "system/window.h"
#include "system/fontproc.h"

#include "report.h"
#include "zonedata.h"
#include "savedata/savedata.h"

#include "field/situation.h"
#include "situation_local.h"
#include "savedata/mystatus.h"
#include "savedata/zukanwork.h"
#include "savedata/playtime.h"

#include "system/msgdata.h"
#include "system/wordset.h"
#include "system/msgdata_util.h"

#include "msgdata/msg.naix"
#include "msgdata/msg_report.h"


#include "ev_mapchange.h"		//DOOR_ID_JUMP_CODEのため
#include "field_poketch.h"

#include "fieldobj.h"

//============================================================================================
//
//			定義
//
//============================================================================================
typedef struct INFO_PARAM {
	int zukan_count;
	int place_name_id;
	MYSTATUS * my;
	PLAYTIME * playtime;
}INFO_PARAM;

//--------------------------------------------------------------------
/**
 * @brief	レポート情報ウィンドウ制御ワークの定義
 */
//--------------------------------------------------------------------
struct REPORT_INFO{
	FIELDSYS_WORK * fsys;		///<ゲーム制御ワークへのポインタ
	int heapID;					///<使用するヒープID
	u8 frame_no;				///<使用するBGフレーム指定
	GF_BGL_INI * bgl;			///<使用するBG制御ワークへのポインタ
	GF_BGL_BMPWIN * win;		///<BMP制御ワークへのポインタ
	WORDSET * word;				///<単語モジュール制御ワークへのポインタ
	MSGDATA_MANAGER * msgman;	///<MSGデータマネージャへのポインタ
	INFO_PARAM iprm;
	int width;
	int height;
};

//--------------------------------------------------------------------
//--------------------------------------------------------------------
enum {
	RINFO_WIN_PX = 1,
	RINFO_WIN_PY = 1,
	RINFO_WIN_SX = 15,
	RINFO_WIN_SY = 10,
	
	RINFO_MSG_PAL = FLD_MENU_WIN_PAL,
	RINFO_WIN_PAL = MENU_WIN_PAL,
	RINFO_WIN_CGX = MENU_WIN_CGX_NUM,

	//はい・いいえウィンドウ、MSGウィンドウと共存できる配置で定義
	RINFO_MSG_CGX = FLD_YESNO_WIN_CGX - (RINFO_WIN_SX * RINFO_WIN_SY),
};

//単語埋め込みタグID。report.gmmときちんと対応するように維持しなければならない
enum {
	RINFO_WORD_PLACENAME = 0,
	RINFO_WORD_PLAYERNAME,
	RINFO_WORD_BADGE_NUM,
	RINFO_WORD_ZUKAN_NUM,
	RINFO_WORD_PLAYTIME_H,
	RINFO_WORD_PLAYTIME_M,
};

enum {
	RINFO_KETA_BADGE_NUM = 1,
	RINFO_KETA_ZUKAN_NUM = 3,
	RINFO_KETA_PLAYTIME_H = 3,
	RINFO_KETA_PLAYTIME_M = 2,
};

static const int MsgID[] = {
	PLACE_NAME,
	HERO_NAME,
	BADGE_NUM,
	ZUKAN_NUM,
	PLAY_TIME,
};
//============================================================================================
//
//			関数
//
//============================================================================================
//--------------------------------------------------------------------
/**
 * @brief	表示パラメータの設定
 * @param	iprm	表示パラメータ保持ワークへのポインタ
 * @param	fsys	ゲーム制御ワークへのポインタ
 * 
 */
//--------------------------------------------------------------------
static void makeinfo(INFO_PARAM * iprm, const FIELDSYS_WORK * fsys)
{
	SAVEDATA * sv = fsys->savedata;
	LOCATION_WORK * now = Situation_GetNowLocation(SaveData_GetSituation(sv));
	ZUKAN_WORK * zw = SaveData_GetZukanWork(sv);

	iprm->place_name_id = ZoneData_GetPlaceNameID(now->zone_id);

	if (ZukanWork_GetZukanGetFlag(zw)) {
		iprm->zukan_count = ZukanWork_GetZukanPokeSeeCount(zw);
	} else {
		iprm->zukan_count = 0;
	}
	iprm->my = SaveData_GetMyStatus(sv);
	iprm->playtime = SaveData_GetPlayTime(sv);
}
//--------------------------------------------------------------------
/**
 * @brief	セーブデータ情報表示に必要な単語生成
 * @param	word	単語モジュール制御ワークへのポインタ
 * @param	iprm	表示パラメータ保持ワークへのポインタ
 */
//--------------------------------------------------------------------
static void makewords(WORDSET * word, const INFO_PARAM * iprm)
{
	int keta, type, count;

	WORDSET_RegisterPlaceName(word, RINFO_WORD_PLACENAME, iprm->place_name_id);

	WORDSET_RegisterPlayerName(word, RINFO_WORD_PLAYERNAME, iprm->my);

	WORDSET_RegisterNumber(word, RINFO_WORD_BADGE_NUM,
			MyStatus_GetBadgeCount(iprm->my),
			RINFO_KETA_BADGE_NUM, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT);

	if (iprm->zukan_count >= 100) {
		keta = RINFO_KETA_ZUKAN_NUM;
		type = NUMBER_DISPTYPE_LEFT;
	} else if (iprm->zukan_count >= 10) {
		keta = RINFO_KETA_ZUKAN_NUM;
		type = NUMBER_DISPTYPE_SPACE;
	} else {
		keta = RINFO_KETA_ZUKAN_NUM - 1;
		type = NUMBER_DISPTYPE_SPACE;
	}
	WORDSET_RegisterNumber(word, RINFO_WORD_ZUKAN_NUM,
			iprm->zukan_count,
			keta, type, NUMBER_CODETYPE_DEFAULT);

	count = PLAYTIME_GetHour(iprm->playtime);
	if (count >= 100) {
		keta = RINFO_KETA_PLAYTIME_H;
		type = NUMBER_DISPTYPE_LEFT;
	} else if (count >= 10) {
		keta = RINFO_KETA_PLAYTIME_H;
		type = NUMBER_DISPTYPE_SPACE;
	} else {
		keta = RINFO_KETA_PLAYTIME_H - 1;
		type = NUMBER_DISPTYPE_SPACE;
	}
	WORDSET_RegisterNumber(word, RINFO_WORD_PLAYTIME_H,
			count,
			keta, type, NUMBER_CODETYPE_DEFAULT);
	WORDSET_RegisterNumber(word, RINFO_WORD_PLAYTIME_M,
			PLAYTIME_GetMinute(iprm->playtime),
			RINFO_KETA_PLAYTIME_M, NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT);

}

//--------------------------------------------------------------------
/**
 * @brief	ウィンドウ幅の取得
 * @param	riw		レポート情報ウィンドウ制御ワークへのポインタ
 * @return	int		表示ウィンドウの幅（キャラ単位）
 */
//--------------------------------------------------------------------
static int CountWidth(const REPORT_INFO * riw)
{
	int id, width, max;
	STRBUF * msg;
	max = 0;
	for (id = 0; id < NELEMS(MsgID); id++) {
		msg = MSGDAT_UTIL_AllocExpandString(riw->word, riw->msgman, id, riw->heapID);
		width = FontProc_GetPrintStrWidth(FONT_SYSTEM, msg,
				FontHeaderGet(FONT_SYSTEM, FONT_HEADER_SPACE_X));
		if (width > max) {
			max = width;
		}
		STRBUF_Delete(msg);
	}
	//キャラ単位の幅（余り切り上げ）を返す
	return (max + 7) / 8;
}

//--------------------------------------------------------------------
/**
 * @brief	ウィンドウ高さの取得
 * @param	iprm	表示パラメータ保持ワークへのポインタ
 * @return	int		表示ウィンドウの高さ（キャラ単位）
 */
//--------------------------------------------------------------------
static int CountHeight(const INFO_PARAM * iprm)
{
	if (iprm->zukan_count != 0) {
		return RINFO_WIN_SY;
	} else {
		return RINFO_WIN_SY - 2;
	}
}

//--------------------------------------------------------------------
/**
 * @brief	レポート情報の文字列を表示する
 * @param	riw		レポート情報ウィンドウ制御ワークへのポインタ
 */
//--------------------------------------------------------------------
static void printinfo(const REPORT_INFO * riw)
{
	STRBUF * msg;
	int x, y;
	int my;
	int i;

	my = FontHeaderGet(FONT_SYSTEM, FONT_HEADER_SIZE_Y)
				+ FontHeaderGet(FONT_SYSTEM, FONT_HEADER_SPACE_Y);
	x = 0;
	y = 0;
	for (i = 0; i < NELEMS(MsgID); i++) {
		if (MsgID[i] == ZUKAN_NUM && riw->iprm.zukan_count == 0) {
			//ずかん表示しない
			continue;
		}
		msg = MSGDAT_UTIL_AllocExpandString(riw->word, riw->msgman, MsgID[i], riw->heapID);
		GF_STR_PrintSimple(riw->win, FONT_SYSTEM, msg, x, y, MSG_NO_PUT, NULL);
		STRBUF_Delete(msg);
		y += my;
	}
}

//--------------------------------------------------------------------
/**
 * @brief	レポート情報ウィンドウ：ウィンドウ表示
 * @param	riw		レポート情報ウィンドウ制御ワークへのポインタ
 */
//--------------------------------------------------------------------
void ReportInfo_WriteWindow(REPORT_INFO * riw)
{
	//BMP制御ワークを確保
	riw->win = sys_AllocMemory(riw->heapID, sizeof(GF_BGL_BMPWIN));
	//bitmap領域を追加
	GF_BGL_BmpWinAdd(riw->bgl, riw->win, riw->frame_no,
			RINFO_WIN_PX, RINFO_WIN_PY, riw->width, riw->height,
			RINFO_MSG_PAL, RINFO_MSG_CGX);
	//ウィンドウ枠キャラ、パレットをセット
	MenuWinGraphicSet(
		riw->bgl, riw->frame_no, RINFO_WIN_CGX, RINFO_WIN_PAL, MENU_TYPE_SYSTEM, riw->heapID); 
	//ウィンドウ枠内を塗りつぶす
	GF_BGL_BmpWinDataFill(riw->win, FontHeaderGet(FONT_SYSTEM, FONT_HEADER_B_COLOR));
	//内容を描画
	printinfo(riw);
	//ウィンドウ枠描画
	BmpMenuWinWrite(riw->win, WINDOW_TRANS_ON, RINFO_WIN_CGX, RINFO_WIN_PAL);
}

//--------------------------------------------------------------------
/**
 * @brief	レポート情報ウィンドウ：ウィンドウ消去
 * @param	riw		レポート情報ウィンドウ制御ワークへのポインタ
 */
//--------------------------------------------------------------------
void ReportInfo_EraseWindow(REPORT_INFO * riw)
{
	//ウィンドウ消去
	BmpMenuWinClear(riw->win, WINDOW_TRANS_ON);
	//bitmap領域を削除
	GF_BGL_BmpWinDel(riw->win);
	//BMP制御ワークを削除
	sys_FreeMemoryEz(riw->win);
}

//--------------------------------------------------------------------
/**
 * @brief	レポート情報ウィンドウ：生成
 * @param	fsys			ゲーム制御ワークへのポインタ
 * @param	heapID			使用するヒープID
 * @param	frame_no		表示に使用するBGフレーム指定
 * @return	REPORT_INFO		生成したレポート情報ウィンドウ制御ワークへのポインタ
 */
//--------------------------------------------------------------------
REPORT_INFO * ReportInfo_Create(FIELDSYS_WORK * fsys, int heapID, u8 frame_no)
{
	REPORT_INFO * riw;

	riw = sys_AllocMemory(heapID, sizeof(REPORT_INFO));
	riw->fsys = fsys;
	riw->heapID = heapID;
	riw->frame_no = frame_no;
	riw->bgl = fsys->bgl;
	riw->word = WORDSET_Create(heapID);
	riw->msgman = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_report_dat, heapID);

	makeinfo(&riw->iprm, riw->fsys);
	makewords(riw->word, &riw->iprm);
	riw->width = CountWidth(riw);
	//GF_ASSERT(riw->width <= RINFO_WIN_SX);
	riw->height = CountHeight(&riw->iprm);
	//GF_ASSERT(riw->height <= RINFO_WIN_SY);
	return riw;
}

//--------------------------------------------------------------------
/**
 * @brief	レポート情報ウィンドウ：削除
 * @param	riw		レポート情報ウィンドウ制御ワークへのポインタ
 */
//--------------------------------------------------------------------
void ReportInfo_Delete(REPORT_INFO * riw)
{
	MSGMAN_Delete(riw->msgman);
	WORDSET_Delete(riw->word);
	sys_FreeMemoryEz(riw);
}


//============================================================================================
//============================================================================================
//--------------------------------------------------------------------
/**
 * @brief	フィールドでのセーブ処理
 * @param	fsys			ゲーム制御ワークへのポインタ
 * @retval	TRUE
 * @retval	FALSE
 */
//--------------------------------------------------------------------
BOOL Field_Save(FIELDSYS_WORK * fsys)
{
	FIELD_OBJ_SAVE_DATA_PTR fldobjsv;

	//フィールド動作モデルのセーブ
	Field_SaveFieldObj(fsys);

	// ポケッチ関連データのセーブ
	Field_SendPoketchInfo( fsys, POKETCH_SEND_SAVE, 0 );

	//位置を引っ張る
	fsys->location->grid_x = Player_NowGPosXGet( fsys->player );
	fsys->location->grid_z = Player_NowGPosZGet( fsys->player );
	fsys->location->door_id = DOOR_ID_JUMP_CODE;
	fsys->location->dir = Player_DirGet( fsys->player );
	if (SaveData_Save(fsys->savedata) == SAVE_RESULT_OK) {
		return TRUE;
	} else {
		//SAVE_RESULT_OK以外の場合はなんにせよ
		//動作がおかしいので失敗とみなす
		return FALSE;
	}
}




