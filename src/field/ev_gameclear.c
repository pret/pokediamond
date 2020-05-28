//============================================================================================
/**
 * @file	ev_gameover.c
 * @brief	ゲームクリア処理
 * @date	2006.05.09
 * @author	tamada GAME FREAK inc.
 */
//============================================================================================

#include "common.h"
#include "fieldsys.h"
#include "field_event.h"


#include "field_subproc.h"		//Field_DendouDemo_SetProc
#include "sysflag.h"
#include "syswork.h"
#include "situation_local.h"
#include "application/dendou_pc.h"
#include "savedata/dendou_data.h"
#include "savedata/record.h"
#include "savedata/mystatus.h"
#include "field/eventflag.h"		//EVENTWORK
#include "ev_mapchange.h"			//EventCmd_MapChangeByLocation
#include "system/pm_rtc.h"
#include "ev_time.h"				//EVTIME_SetGameClearDateTime
#include "ev_pokemon.h"				//EvPoke_SetChampionRibbon
#include "fieldmap.h"
#include "system\msgdata_util.h"
#include "system\window.h"
#include "system\wipe.h"
#include "system\snd_tool.h"
#include "talk_msg.h"
#include "fld_bmp.h"
#include "msgdata\msg.naix"
#include "msgdata\msg_common_scr.h"
#include "system\main.h"
#include "poketool\status_rcv.h"

#include "report.h"				//Field_Save

//==============================================================================================
//==============================================================================================
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
typedef struct {
	BOOL	already_clear_flag;
	DEMO_DENDOU_PARAM ddp;
	ENDING_PROC_PARAM edp;

	GF_BGL_BMPWIN     bmpWin;
	STRBUF*           str;
	void*             iconWork;
	int               msgIndex;
	int               wait;
}GAMECLEAR_WORK;




//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static void SetupMessageResources( FIELDSYS_WORK* fsys, GAMECLEAR_WORK* gcw );
static void StartReportMessage( FIELDSYS_WORK* fsys,  GAMECLEAR_WORK* gcw );
static void StartReportFinishMessage( FIELDSYS_WORK* fsys, GAMECLEAR_WORK* gcw, int save_result );
static void DeleteReportMessageResources( GAMECLEAR_WORK* gcw );
static void DeleteAllMessageResources( FIELDSYS_WORK* fsys, GAMECLEAR_WORK* gcw );

static BOOL WaitMessage( GAMECLEAR_WORK* gcw );


//-----------------------------------------------------------------------------
/**
 * @brief	殿堂入りデータのセーブ
 */
//-----------------------------------------------------------------------------
static void SaveDendouData(FIELDSYS_WORK * fsys, BOOL already_clear_flag)
{
	DENDOU_SAVEDATA*  dd;
	POKEPARTY* party;
	RTCDate	date;
	LOAD_RESULT result;

	dd = SaveData_Extra_LoadDendouData(fsys->savedata, HEAPID_WORLD, &result);
	if (result != LOAD_RESULT_OK || !already_clear_flag) {
		//データが壊れている場合、あるいは初回クリアの場合は初期化する
		DendouData_Init(dd);
	}
	party = SaveData_GetTemotiPokemon(fsys->savedata);
	GF_RTC_GetDate(&date);
	DendouData_AddRecord( dd, party, &date );
	SaveData_Extra_SaveDendouData(fsys->savedata, dd);
	sys_FreeMemoryEz(dd);
}

//==============================================================================================
//==============================================================================================
//-----------------------------------------------------------------------------
/**
 * @brief	ゲームクリア処理
 */
//-----------------------------------------------------------------------------
static BOOL GMEVENT_GameClear(GMEVENT_CONTROL * event)
{
	LOCATION_WORK * sp;
	EVENTWORK * ev;
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	GAMECLEAR_WORK * gcw = FieldEvent_GetSpecialWork(event);
	int * seq = FieldEvent_GetSeqWork(event);
	DEMO_DENDOU_PARAM * ddp = &gcw->ddp;

	switch (*seq) {
	case 0:
		/* 殿堂入りデモ呼び出し */
		Field_DendouDemo_SetProc( fsys, ddp );
		(*seq) ++;
		break;

	case 1:
		if( !FieldEvent_Cmd_WaitSubProcEnd(fsys) ){		//サブプロセス終了待ち
			sys_CreateHeap( HEAPID_BASE_APP, HEAPID_FIELD, 0x20000 );
			SetupMessageResources( fsys, gcw );
			WIPE_SYS_Start( WIPE_PATTERN_M, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN,
				WIPE_FADE_BLACK, 8, 1, HEAPID_EVENT );
			(*seq) ++;
		}
		break;

	case 2:
		if( WIPE_SYS_EndCheck() )
		{
			if( SaveData_IsOverwritingOtherData(fsys->savedata) == FALSE )
			{
				StartReportMessage( fsys, gcw );
				(*seq)++;
			}
			else
			{
				(*seq) = 7;
			}
		}
		break;

	case 3:
		if( WaitMessage( gcw ) )
		{
			(*seq)++;
		}
		break;

	case 4:
		/* セーブ */
		{
			int result;

			//強制的に全体セーブとなるようにしている

			PokeParty_RecoverAll( SaveData_GetTemotiPokemon(fsys->savedata) );
			SaveData_RequestTotalSave();

			result = SaveData_Save(fsys->savedata);
			SaveDendouData(fsys, gcw->already_clear_flag);

			/* セーブ完了のメッセージ表示 */
			DeleteReportMessageResources( gcw );
			StartReportFinishMessage( fsys, gcw, result );
			(*seq) ++;
		}
		break;

	case 5:
		if( WaitMessage( gcw ) )
		{
			Snd_SePlay( SEQ_SE_DP_SAVE );
			gcw->wait = 18;
			(*seq)++;
		}
		break;

	case 6:
		if( gcw->wait )
		{
			gcw->wait--;
		}
		else
		{
			(*seq)++;
		}
		break;

	case 7:
		WIPE_SYS_Start( WIPE_PATTERN_M, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT,
			WIPE_FADE_BLACK, 8, 1, HEAPID_EVENT );
		(*seq)++;
		break;

	case 8:
		if( WIPE_SYS_EndCheck() )
		{
			DeleteAllMessageResources( fsys, gcw );

			/* エンディングデモ呼び出し */
			Field_EndingDemo_SetProc( fsys, &(gcw->edp) );
			(*seq) ++;
		}
		break;

	case 9:
		if( !FieldEvent_Cmd_WaitSubProcEnd(fsys) )
		{
			sys_FreeMemoryEz(gcw);
			sys_DeleteHeap( HEAPID_FIELD );
			OS_ResetSystem( _SOFT_RESET_NORMAL );
			return TRUE;
		}
		break;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 * @brief		イベントコマンド関数：ゲームクリア
 * @param	event		イベント制御ワークへのポインタ
 */
//-----------------------------------------------------------------------------
void EventCmd_GameClear(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys;
	LOCATION_WORK * sp,* ep;
	EVENTWORK * ev;
	MYSTATUS  * my;
	GAMECLEAR_WORK * gcw;
	RECORD * rec;
	POKEPARTY * party;
	fsys = FieldEvent_GetFieldSysWork(event);
	gcw = sys_AllocMemory(HEAPID_EVENT, sizeof(GAMECLEAR_WORK));

	ev = SaveData_GetEventWork(fsys->savedata);
	my = SaveData_GetMyStatus( fsys->savedata );
	sp = Situation_GetSpecialLocation(SaveData_GetSituation(fsys->savedata));
	ep = Situation_GetEscapeLocation(SaveData_GetSituation(fsys->savedata));

	gcw->already_clear_flag = SysFlag_GameClearCheck(ev);
	gcw->ddp.player	= SaveData_GetMyStatus(fsys->savedata);
	gcw->ddp.party		= SaveData_GetTemotiPokemon(fsys->savedata);
	gcw->ddp.playTime	= SaveData_GetPlayTime(fsys->savedata);

	gcw->edp.playerSex = MyStatus_GetMySex( SaveData_GetMyStatus(fsys->savedata) );
	gcw->edp.clearFlag = SysFlag_GameClearCheck(ev);
	gcw->edp.zukanWork = SaveData_GetZukanWork(fsys->savedata);

	if (SysFlag_GameClearCheck(ev) == FALSE) {
		EVTIME_SetGameClearDateTime(fsys);	// 初めての殿堂入りの時間を記録する
	}
	party = SaveData_GetTemotiPokemon(fsys->savedata);
	EvPoke_SetChampionRibbon(party);		// チャンピオンリボンをセット
	LOCATION_SetFirstPos(sp);				// 特殊接続先を自宅の2階にセット
	LOCATION_SetFirstEscapePos(ep);			// エスケープ先を自宅の外にセット
	SysFlag_CommCounterSet(ev);				// コンティニュー時に特殊接続先から開始するフラグをセット
	SysFlag_GameClearSet(ev);				// ゲームクリアフラグをセット
	MyStatus_SetDpClearFlag( my );			// MYSTATUS内のゲームクリアフラグも立てる


//	SysWork_HideMapWorkSet(ev, HIDEMAP_ID_L04);	// L04を出現させるように　スクリプトからopenに変更 06.07.13 iwasawa
	rec = SaveData_GetRecord(fsys->savedata);
	RECORD_Inc(rec, RECID_DENDOU_CNT);		// 殿堂入りカウントアップ

	FieldEvent_Call(event, GMEVENT_GameClear, gcw);
}




//------------------------------------------------------------------
/**
 * 
 *
 * @param   fsys		
 * @param   gcw		
 *
 */
//------------------------------------------------------------------
static void SetupMessageResources( FIELDSYS_WORK* fsys, GAMECLEAR_WORK* gcw )
{
	static const GF_BGL_DISPVRAM SetBankData = {
		GX_VRAM_BG_128_B,				// メイン2DエンジンのBG
		GX_VRAM_BGEXTPLTT_NONE,			// メイン2DエンジンのBG拡張パレット
		GX_VRAM_SUB_BG_128_C,			// サブ2DエンジンのBG
		GX_VRAM_SUB_BGEXTPLTT_NONE,		// サブ2DエンジンのBG拡張パレット
		GX_VRAM_OBJ_64_E,				// メイン2DエンジンのOBJ
		GX_VRAM_OBJEXTPLTT_NONE,		// メイン2DエンジンのOBJ拡張パレット
		GX_VRAM_SUB_OBJ_16_I,			// サブ2DエンジンのOBJ
		GX_VRAM_SUB_OBJEXTPLTT_NONE,	// サブ2DエンジンのOBJ拡張パレット
		GX_VRAM_TEX_0_A,				// テクスチャイメージスロット
		GX_VRAM_TEXPLTT_01_FG			// テクスチャパレットスロット
	};

	static const GF_BGL_SYS_HEADER BGsys_data = {
		GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_2D,
	};

	static const GF_BGL_BGCNT_HEADER header = {
		0, 0, 0x800, 0,	// scrX, scrY, scrbufSize, scrbufofs,
		GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
		0, 0,
		GX_BG_EXTPLTT_01, 1, 0, 0, FALSE	// pal, pri, areaover, dmy, mosaic
	};

	gcw->str = NULL;
	gcw->iconWork = NULL;
	GF_BGL_BmpWinInit( &gcw->bmpWin );

	GF_Disp_SetBank( &SetBankData );
	GX_SetDispSelect( GX_DISP_SELECT_MAIN_SUB );
	GF_BGL_InitBG( &BGsys_data );

	GF_BGL_BackGroundColorSet( FLD_MBGFRM_FONT, 0x0000 );

	GF_BGL_BGControlSet( fsys->bgl, FLD_MBGFRM_FONT, &header, GF_BGL_MODE_TEXT );
	GF_BGL_ClearCharSet( FLD_MBGFRM_FONT, 0x20, 0, HEAPID_EVENT );
	GF_BGL_ScrFill( fsys->bgl, FLD_MBGFRM_FONT, 0x0000, 0, 0, 32, 32, GF_BGL_SCRWRT_PALIN );

	GF_BGL_LoadScreenReq( fsys->bgl, FLD_MBGFRM_FONT );
}

//------------------------------------------------------------------
/**
 * 「レポートにかきこんでいます」メッセージの表示開始
 *
 * @param   fsys		
 * @param   gcw		
 *
 */
//------------------------------------------------------------------
static void StartReportMessage( FIELDSYS_WORK* fsys,  GAMECLEAR_WORK* gcw )
{
	CONFIG* config = SaveData_GetConfig(fsys->savedata);

	gcw->str = MSGDAT_GetStrDirectAlloc( ARC_MSG, NARC_msg_common_scr_dat, msg_common_report_03, HEAPID_EVENT );

    FldTalkBmpAdd( fsys->bgl, &gcw->bmpWin, FLD_MBGFRM_FONT );
	FieldTalkWinPut( &gcw->bmpWin, config );

	gcw->msgIndex = FieldTalkMsgStart( &gcw->bmpWin, gcw->str, config, 1 );
	gcw->iconWork = TimeWaitIconAdd( &gcw->bmpWin, TALK_WIN_CGX_NUM );
}

//------------------------------------------------------------------
/**
 * 「レポートにかきこんでいます」メッセージの表示終了待ち
 *
 * @param   gcw		
 *
 * @retval  BOOL	TRUEで終了
 */
//------------------------------------------------------------------
static BOOL WaitMessage( GAMECLEAR_WORK* gcw )
{
	return FldTalkMsgEndCheck( gcw->msgIndex );
}

//------------------------------------------------------------------
/**
 * 「レポートにかきこんでいます」メッセージ表示のためのリソース破棄
 *
 * @param   gcw		
 *
 */
//------------------------------------------------------------------
static void DeleteReportMessageResources( GAMECLEAR_WORK* gcw )
{
	STRBUF_Delete( gcw->str );
	TimeWaitIconDel( gcw->iconWork );

	// BitmapWindowは内容をクリアするだけで破棄しない（次のメッセージで使い回す）
	FieldTalkWinClear( &gcw->bmpWin );
}


static void StartReportFinishMessage( FIELDSYS_WORK* fsys, GAMECLEAR_WORK* gcw, int save_result )
{
	MSGDATA_MANAGER* mm = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_common_scr_dat, HEAPID_FIELD );

	if( save_result == SAVE_RESULT_OK )
	{
		WORDSET* wordset;

		wordset = WORDSET_Create( HEAPID_FIELD );
		WORDSET_RegisterPlayerName( wordset, 0, SaveData_GetMyStatus(fsys->savedata) );

		gcw->str = MSGDAT_UTIL_AllocExpandString( wordset, mm, msg_common_report_04, HEAPID_FIELD );

		WORDSET_Delete( wordset );
	}
	else
	{
		gcw->str = MSGMAN_AllocString( mm, msg_common_report_06 );
	}
	MSGMAN_Delete( mm );

	gcw->msgIndex = FieldTalkMsgStart( &gcw->bmpWin, gcw->str, SaveData_GetConfig(fsys->savedata), 1 );
}


static void DeleteAllMessageResources( FIELDSYS_WORK* fsys, GAMECLEAR_WORK* gcw )
{
	if( gcw->str )
	{
		STRBUF_Delete( gcw->str );
	}

	if( GF_BGL_BmpWinAddCheck(&gcw->bmpWin) )
	{
		GF_BGL_BmpWinDel( &gcw->bmpWin );
	}

	GF_BGL_BGControlExit( fsys->bgl, FLD_MBGFRM_FONT );
}
