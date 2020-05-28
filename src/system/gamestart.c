//============================================================================================
/**
 * @file	gamestart.c
 * @brief	ゲーム開始処理
 * @author	tamada GAME FREAK inc.
 * @date	2006.05.10
 *
 *
 * 実質的内容はオーバーレイ領域にある初期化処理を呼びだしているだけです
 */
//============================================================================================

#include "common.h"

#include "system/main.h"
#include "system/gamestart.h"

#include "field/game_init.h"
#include "savedata/config.h"
#include "gflib/heapsys.h"
#include "system/heapdefine.h"
#include "savedata/system_data.h"
#include "savedata/gametime.h"

#include "savedata/mystatus.h"
#include "savedata/randomgroup.h"
#include "savedata/seedbed.h"
#include "gflib/strbuf_family.h"
#include "system/gamedata.h"
#include "system/wordset.h"
#include "field/union_beacon_tool.h"
#include "field/b_tower_ev.h"
#include "system/playtime_ctrl.h"

#include "system/debug_flag.h"

//============================================================================================
//============================================================================================
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
enum {
	GAMEINIT_HEAP_SIZE	= 0x20000,
};

//============================================================================================
//============================================================================================
static PROC_RESULT NewGameStart_ProcInit(PROC * proc, int * seq);
static PROC_RESULT NewGameStart_ProcMain(PROC * proc, int * seq);
static PROC_RESULT NewGameStart_ProcEnd(PROC * proc, int * seq);
static PROC_RESULT AfterOpening_ProcInit(PROC * proc, int * seq);
static PROC_RESULT AfterOpening_ProcMain(PROC * proc, int * seq);
static PROC_RESULT AfterOpening_ProcEnd(PROC * proc, int * seq);
static PROC_RESULT ContinueGameStart_ProcInit(PROC * proc, int * seq);
static PROC_RESULT ContinueGameStart_ProcMain(PROC * proc, int * seq);
static PROC_RESULT ContinueGameStart_ProcEnd(PROC * proc, int * seq);
#ifdef	PM_DEBUG
static PROC_RESULT DebugNewGameStart_ProcInit(PROC * proc, int * seq);
static PROC_RESULT DebugNewGameStart_ProcMain(PROC * proc, int * seq);
static PROC_RESULT DebugNewGameStart_ProcEnd(PROC * proc, int * seq);

static void Debug_SetRandomGroup(SAVEDATA * sv);
#endif

static void AfterOpeningSetting(int heapID, SAVEDATA * sv, BOOL set_id);


//============================================================================================
//============================================================================================
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
const PROC_DATA NewGameStartProcData = {
	NewGameStart_ProcInit,
	NewGameStart_ProcMain,
	NewGameStart_ProcEnd,
	NO_OVERLAY_ID,
};

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
const PROC_DATA AfterOpeningProcData = {
	AfterOpening_ProcInit,
	AfterOpening_ProcMain,
	AfterOpening_ProcEnd,
	NO_OVERLAY_ID,
};

#ifdef	PM_DEBUG
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
const PROC_DATA DebugNewGameStartProcData = {
	DebugNewGameStart_ProcInit,
	DebugNewGameStart_ProcMain,
	DebugNewGameStart_ProcEnd,
	NO_OVERLAY_ID,
};
#endif

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
const PROC_DATA ContinueGameStartProcData = {
	ContinueGameStart_ProcInit,
	ContinueGameStart_ProcMain,
	ContinueGameStart_ProcEnd,
	NO_OVERLAY_ID,
};


//============================================================================================
//
//		新規でゲーム開始（オープニングへ）
//
//============================================================================================
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
static PROC_RESULT NewGameStart_ProcInit(PROC * proc, int * seq)
{
	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_GAMEINIT, GAMEINIT_HEAP_SIZE);
	Main_InitRandom();
#ifdef	PM_DEBUG
	DebugFlagData.debug_mode = FALSE;
#endif
	return PROC_RES_FINISH;
}
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
static PROC_RESULT NewGameStart_ProcMain(PROC * proc, int * seq)
{
	SAVEDATA * savedata = ((MAINWORK *)PROC_GetParentWork(proc))->savedata;
	GameData_SetNewGame(HEAPID_GAMEINIT, savedata);
	return PROC_RES_FINISH;
}
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
static PROC_RESULT NewGameStart_ProcEnd(PROC * proc, int * seq)
{
	sys_DeleteHeap(HEAPID_GAMEINIT);
	Main_SetNextProc(NO_OVERLAY_ID, &OpeningProcData);
	return PROC_RES_FINISH;
}

//============================================================================================
//
//		オープニングからゲームへ
//
//============================================================================================
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
static PROC_RESULT AfterOpening_ProcInit(PROC * proc, int * seq)
{
	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_GAMEINIT, GAMEINIT_HEAP_SIZE);
	Main_InitRandom();
	return PROC_RES_FINISH;
}
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
static PROC_RESULT AfterOpening_ProcMain(PROC * proc, int * seq)
{
	SAVEDATA * savedata = ((MAINWORK *)PROC_GetParentWork(proc))->savedata;

	AfterOpeningSetting(HEAPID_GAMEINIT, savedata, TRUE);
	PlayTimeCtrl_Start( SaveData_GetPlayTime(savedata) );

	return PROC_RES_FINISH;
}
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
static PROC_RESULT AfterOpening_ProcEnd(PROC * proc, int * seq)
{
	sys_DeleteHeap(HEAPID_GAMEINIT);
	Main_SetNextProc(NO_OVERLAY_ID, &FirstGameProcData);
	return PROC_RES_FINISH;
}

//============================================================================================
//
//		コンティニューでゲーム開始
//
//============================================================================================
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
static PROC_RESULT ContinueGameStart_ProcInit(PROC * proc, int * seq)
{
	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_GAMEINIT, GAMEINIT_HEAP_SIZE);
	Main_InitRandom();
#ifdef	PM_DEBUG
	DebugFlagData.debug_mode = FALSE;
#endif
	return PROC_RES_FINISH;
}
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
static PROC_RESULT ContinueGameStart_ProcMain(PROC * proc, int * seq)
{
	SAVEDATA * savedata = ((MAINWORK *)PROC_GetParentWork(proc))->savedata;
	SYSTEMDATA *sysdt = SaveData_GetSystemData(savedata);

	GameData_SetContinueData(HEAPID_GAMEINIT, savedata);
	CONFIG_SetKeyConfigFormSave(savedata);
	if (!SYSTEMDATA_IdentifyMACAddress(sysdt) || !SYSTEMDATA_IdentifyRTCOffset(sysdt)) {
		//ペナルティ時間を設定
		GMTIME_SetPenaltyTime(SaveData_GetGameTime(savedata));
		//現在のＤＳの設定を今後の設定とする
		SYSTEMDATA_Update(sysdt);
	}
	PlayTimeCtrl_Start( SaveData_GetPlayTime(savedata) );
	return PROC_RES_FINISH;
}
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
static PROC_RESULT ContinueGameStart_ProcEnd(PROC * proc, int * seq)
{
	sys_DeleteHeap(HEAPID_GAMEINIT);
	Main_SetNextProc(NO_OVERLAY_ID, &ContinueGameProcData);
	return PROC_RES_FINISH;
}

//============================================================================================
//
//		デバッグゲーム開始
//
//============================================================================================
#ifdef	PM_DEBUG
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
static PROC_RESULT DebugNewGameStart_ProcInit(PROC * proc, int * seq)
{
	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_GAMEINIT, GAMEINIT_HEAP_SIZE);
	Main_InitRandom();
#ifdef	PM_DEBUG
	DebugFlagData.debug_mode = TRUE;
#endif
	return PROC_RES_FINISH;
}
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
static PROC_RESULT DebugNewGameStart_ProcMain(PROC * proc, int * seq)
{
	MAINWORK * mainwork = PROC_GetParentWork(proc);
	SAVEDATA * savedata = mainwork->savedata;
	GameData_SetDebugNewGame(HEAPID_GAMEINIT, savedata, mainwork->select_id);
	AfterOpeningSetting(HEAPID_GAMEINIT, savedata, FALSE);
	//Debug_SetRandomGroup(savedata);
	PlayTimeCtrl_Start( SaveData_GetPlayTime(savedata) );
	return PROC_RES_FINISH;
}
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
static PROC_RESULT DebugNewGameStart_ProcEnd(PROC * proc, int * seq)
{
	sys_DeleteHeap(HEAPID_GAMEINIT);
	Main_SetNextProc(NO_OVERLAY_ID, &FirstGameProcData);
	return PROC_RES_FINISH;
}
#endif


//============================================================================================
//
//
//
//============================================================================================
#ifdef	PM_DEBUG
//--------------------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------------------
static void Debug_SetRandomGroup(SAVEDATA * sv)
{
	STRBUF * strbuf;
	MYSTATUS * my = SaveData_GetMyStatus(sv);
	RANDOM_GROUP * rg = SaveData_GetRandomGroup(sv);

	strbuf = STRBUF_Create(PERSON_NAME_SIZE + EOM_SIZE, HEAPID_BASE_DEBUG);
	STRBUF_SetStringCode(strbuf, MyStatus_GetMyName(my));
	RandomGroup_SetName(rg, RANDOMGROUP_MINE, RANDOMGROUP_NAME_LEADER, strbuf);
	RandomGroup_SetName(rg, RANDOMGROUP_MINE, RANDOMGROUP_NAME_GROUP, strbuf);
	RandomGroup_SetRandomSeed(rg, RANDOMGROUP_MINE, gf_mtRand());
	RandomGroup_Copy(rg, RANDOMGROUP_MINE, RANDOMGROUP_MYUSE);

//	RandomGroup_Debug_RecordMix(sv);
}
#endif


#include "../fielddata/setting/kinomi_init.c"
//--------------------------------------------------------------------------------------------
/**
 * @brief	オープニング後の設定
 * @param	sv		セーブデータへのポインタ
 */
//--------------------------------------------------------------------------------------------
static void AfterOpeningSetting(int heapID, SAVEDATA * sv, BOOL set_id)
{
	u32 id;
	SEEDBED * sbed;
	MYSTATUS * my;
	GMTIME * gt;
	RANDOM_GROUP * rg;

	//ＤＳ本体情報のセット
	SYSTEMDATA_Update(SaveData_GetSystemData(sv));

	//ゲーム内時間初期化
	gt = SaveData_GetGameTime(sv);
	GMTIME_Init(gt);

	//ランダムグループのデフォルト参照箇所の値を乱数で初期化する
	rg = SaveData_GetRandomGroup(sv);
	RandomGroup_SetRandomSeed(rg, RANDOMGROUP_MYUSE, gf_mtRand());

	//タワーランダムシード更新
	BtlTower_UpdateDayRndSeed(sv);

	my = SaveData_GetMyStatus(sv);
	id = gf_mtRand();
	if (set_id) {
		MyStatus_SetID(my, id);
	}
	// ユニオンルーム内での見た目をIDから生成
	MyStatus_SetTrainerView(my, UnionView_GetTrainerType( id, MyStatus_GetMySex(my), 0 ));	

	//きのみ配置初期化
	sbed = SaveData_GetSeedBed(sv);
	SEEDBED_SetDefaultData(sbed, heapID, KinomiInitTable, NELEMS(KinomiInitTable)/2);
}






