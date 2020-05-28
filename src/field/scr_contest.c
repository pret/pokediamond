//============================================================================================
/**
 * @file	scr_contest.c
 * @bfief	スクリプトコマンド：コンテスト関連
 * @author	Satoshi Nohara
 * @date	06.06.23
 */
//============================================================================================
#include "common.h"
#include "system/lib_pack.h"
#include "fieldsys.h"

#include "script.h"
#include "scrcmd_def.h"
#include "field/eventflag.h"
#include "field/evwkdef.h"
#include "sysflag.h"
#include "syswork.h"

#include "contest/contest.h"
#include "savedata/perapvoice.h"
#include "field/field_hblank.h"
#include "field/fieldmap_work.h"
#include "savedata/zukanwork.h"
#include "field/zonedata.h"
#include "savedata/fnote_mem.h"


//============================================================================================
//
//	プロトタイプ宣言
//
//============================================================================================
static BOOL EvWaitConSioTimingCheck(VM_MACHINE * core);
static BOOL EvWaitConSioParamInitSet(VM_MACHINE * core);
static BOOL EvWaitConCameraFlashCheck(VM_MACHINE * core);
BOOL EvCmdConSioTimingSend( VM_MACHINE * core );
BOOL EvCmdConSioTimingCheck( VM_MACHINE * core );
BOOL EvCmdConSystemCreate( VM_MACHINE * core );
BOOL EvCmdConSystemExit( VM_MACHINE * core );
BOOL EvCmdConJudgeNameGet( VM_MACHINE * core );
BOOL EvCmdConBreederNameGet( VM_MACHINE * core );
BOOL EvCmdConNickNameGet( VM_MACHINE * core );
BOOL EvCmdConSioParamInitSet( VM_MACHINE * core );
BOOL EvCmdContestProc( VM_MACHINE * core );
BOOL EvCmdConRankNameGet( VM_MACHINE * core );
BOOL EvCmdConTypeNameGet( VM_MACHINE * core );
BOOL EvCmdConVictoryBreederNameGet( VM_MACHINE * core );
BOOL EvCmdConVictoryItemNoGet( VM_MACHINE * core );
BOOL EvCmdConVictoryNickNameGet( VM_MACHINE * core );
BOOL EvCmdConRankingCheck( VM_MACHINE * core );
BOOL EvCmdConVictoryEntryNoGet( VM_MACHINE * core );
BOOL EvCmdConMyEntryNoGet( VM_MACHINE * core );
BOOL EvCmdConObjCodeGet( VM_MACHINE * core );
BOOL EvCmdConPopularityGet( VM_MACHINE * core );
BOOL EvCmdConCameraFlashSet( VM_MACHINE * core );
BOOL EvCmdConCameraFlashCheck( VM_MACHINE * core );
BOOL EvCmdConHBlankStop( VM_MACHINE * core );
BOOL EvCmdConHBlankStart( VM_MACHINE * core );
BOOL EvCmdConEndingSkipCheck( VM_MACHINE * core );
BOOL EvCmdConRecordDisp( VM_MACHINE * core );
BOOL EvCmdConMsgPrintFlagSet( VM_MACHINE * core );
BOOL EvCmdConMsgPrintFlagReset( VM_MACHINE * core );
BOOL EvCmdConNumTagSet( VM_MACHINE * core );
BOOL EvCmdConDeskModeGet( VM_MACHINE * core );
BOOL EvCmdConEntryParamGet( VM_MACHINE * core );
BOOL EvCmdConHaveRibbonCheck( VM_MACHINE * core );
BOOL EvCmdConRibbonNameGet( VM_MACHINE * core );
BOOL EvCmdConAcceNoGet( VM_MACHINE * core );


//============================================================================================
//
//	コマンド
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * 送信
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConSioTimingSend( VM_MACHINE * core )
{
	void** pwork	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	u16 timing_no	= VMGetWorkValue(core);

	ConScr_SioTimingSend( *pwork, timing_no );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 同期チェック
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConSioTimingCheck( VM_MACHINE * core )
{
	void** pwork	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	u16 timing_no	= VMGetWorkValue(core);

	//仮想マシンの汎用レジスタにワークのIDを格納
	core->reg[0] = timing_no;

	VM_SetWait( core, EvWaitConSioTimingCheck );
	return 1;
}

//return 1 = 終了
static BOOL EvWaitConSioTimingCheck(VM_MACHINE * core)
{
	void** pwork		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	return ConScr_SioTimingCheck( *pwork, core->reg[0] );
}

//--------------------------------------------------------------------------------------------
/**
 * システムワーク作成
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConSystemCreate( VM_MACHINE * core )
{
	STRBUF* buf;
	POKEMON_PARAM * poke;
	void** pwork	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	MYSTATUS* my	= SaveData_GetMyStatus( GameSystem_GetSaveData(core->fsys) );
	u16 rank		= VMGetWorkValue(core);
	u16 type		= VMGetWorkValue(core);
	u16 mode		= VMGetWorkValue(core);
	u16 pos			= VMGetWorkValue(core);
	CONTEST_INIT_DATA cid;
	
	//ポケモンへのポインタ取得
	poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(core->fsys->savedata), pos );

	//自分の名前取得
	buf	= MyStatus_CreateNameString( my, HEAPID_FIELD );

	cid.type = type;
	cid.rank = rank;
	cid.mode = mode;
	cid.hof_flag = SysFlag_GameClearCheck(SaveData_GetEventWork(core->fsys->savedata));
	cid.zenkoku_zukan_flag = 
		ZukanWork_GetZenkokuZukanFlag(SaveData_GetZukanWork(core->fsys->savedata));
	cid.temoti_pos = pos;
	cid.my_pp = poke;
	cid.player_name_str = buf;
	cid.my_status = my;
	cid.imc_save = SaveData_GetImcSaveData(core->fsys->savedata);
	cid.config = SaveData_GetConfig(core->fsys->savedata);
	cid.sv = core->fsys->savedata;
	cid.perap_voice = SaveData_GetPerapVoice(core->fsys->savedata);
	
	*pwork = Contest_SystemCreate(&cid);

	//STRBUF開放
	STRBUF_Delete( buf );

#if 0
	//コンテストは、受付マップから、オープニング会場マップへ切り替わるので、
	//スクリプトを終了すると、コンテストシステムのポインタが保持できないので、
	//セーブワークに保存している(暫定)
	SysWork_ContestAdrsSet( core->fsys, *pwork );
#endif

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * システムワーク削除
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConSystemExit( VM_MACHINE * core )
{
#if 1
	POKEMON_PARAM * poke;
	void** pwork	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	u16 pos			= VMGetWorkValue(core);	//参加したポケモンが手持ちの何番目か取得
	u32 place_id = ZoneData_GetPlaceNameID(core->fsys->location->zone_id);

	//ポケモンへのポインタ取得
//	poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(core->fsys->savedata), pos );

	//各種パラメータ更新
	ConScr_EndParamSet( *pwork, core->fsys->savedata, place_id, core->fsys->fnote );

	Contest_SystemExit( *pwork );
#else
	//コンテストは、受付マップから、オープニング会場マップへ切り替わるので、
	//スクリプトを終了すると、コンテストシステムのポインタが保持できないので、
	//セーブワークに保存している(暫定)
	Contest_SystemExit( SysWork_ContestAdrsGet(core->fsys) );
#endif
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 審判名取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConJudgeNameGet( VM_MACHINE * core )
{
	void** pwork		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	WORDSET** wordset	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_WORDSET );
	u16 judge_no		= VMGetWorkValue(core);
	u16 buf_id			= VMGetWorkValue(core);

#if 1
	ConScr_JudgeNameGet( *pwork, judge_no, *wordset, buf_id );
#else
	ConScr_JudgeNameGet( SysWork_ContestAdrsGet(core->fsys), judge_no, *wordset, buf_id );
#endif
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ブリーダー名取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConBreederNameGet( VM_MACHINE * core )
{
	void** pwork		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	WORDSET** wordset	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_WORDSET );
	u16 entry_no		= VMGetWorkValue(core);
	u16 buf_id			= VMGetWorkValue(core);

#if 1
	ConScr_BreederNameGet( *pwork, entry_no, *wordset, buf_id );
#else
	ConScr_BreederNameGet( SysWork_ContestAdrsGet(core->fsys), entry_no, *wordset, buf_id );
#endif
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ニックネーム取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConNickNameGet( VM_MACHINE * core )
{
	void** pwork		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	WORDSET** wordset	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_WORDSET );
	u16 entry_no		= VMGetWorkValue(core);
	u16 buf_id			= VMGetWorkValue(core);

#if 1
	ConScr_NickNameGet( *pwork, entry_no, *wordset, buf_id );
#else
	ConScr_NickNameGet( SysWork_ContestAdrsGet(core->fsys), entry_no, *wordset, buf_id );
#endif
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 数値をタグセット
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConNumTagSet( VM_MACHINE * core )
{
	void** pwork		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	WORDSET** wordset	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_WORDSET );
	u16 num				= VMGetWorkValue(core);
	u16 buf_id			= VMGetWorkValue(core);

	WORDSET_RegisterNumber(*wordset, buf_id, num, 1, 
		NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 通信用にワークの初期設定と最初の通信を行うタスクを生成
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConSioParamInitSet( VM_MACHINE * core )
{
	void** pwork		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	Contest_SioParamInitSet( *pwork );
	VM_SetWait( core, EvWaitConSioParamInitSet );
	return 1;
}

//return 1 = 終了
static BOOL EvWaitConSioParamInitSet(VM_MACHINE * core)
{
	void** pwork		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
#if 1
	return Contest_SioFastDataEndCheck( *pwork );
#else
	return Contest_SioFastDataEndCheck( SysWork_ContestAdrsGet(core->fsys) );
#endif
}

//--------------------------------------------------------------------------------------------
/**
 * コンテスト呼び出し
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdContestProc( VM_MACHINE * core )
{
	void** pwork = GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
#if 1
	EventCmd_ContestProc( core->event_work, *pwork );	//イベント切り替え
#else
	EventCmd_ContestProc( core->event_work, SysWork_ContestAdrsGet(core->fsys) );//イベント切り替え
#endif
	//VM_SetWait( core, EvCmdWaitSubProcEnd );
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * ランク名取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConRankNameGet( VM_MACHINE * core )
{
	void** pwork		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	WORDSET** wordset	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_WORDSET );
	u16 buf_id			= VMGetWorkValue(core);

#if 1
	ConScr_RankNameGet( *pwork, *wordset, buf_id );
#else
	ConScr_RankNameGet( SysWork_ContestAdrsGet(core->fsys), *wordset, buf_id );
#endif
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * タイプ名取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConTypeNameGet( VM_MACHINE * core )
{
	void** pwork		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	WORDSET** wordset	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_WORDSET );
	u16 buf_id			= VMGetWorkValue(core);

#if 1
	ConScr_TypeNameGet( *pwork, *wordset, buf_id );
#else
	ConScr_TypeNameGet( SysWork_ContestAdrsGet(core->fsys), *wordset, buf_id );
#endif
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 優勝者名取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConVictoryBreederNameGet( VM_MACHINE * core )
{
	void** pwork		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	WORDSET** wordset	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_WORDSET );
	u16 buf_id			= VMGetWorkValue(core);

#if 1
	ConScr_VictoryBreederNameGet( *pwork, *wordset, buf_id );
#else
	ConScr_VictoryBreederNameGet( SysWork_ContestAdrsGet(core->fsys), *wordset, buf_id );
#endif
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 優勝商品ナンバー取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConVictoryItemNoGet( VM_MACHINE * core )
{
	void** pwork		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	u16* ret_wk			= VMGetWork( core );

#if 1
	*ret_wk = ConScr_VictoryItemNoGet( *pwork );
#else
	*ret_wk = ConScr_VictoryItemNoGet( SysWork_ContestAdrsGet(core->fsys) );
#endif
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 優勝したブリーダーのポケモンニックネームを取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConVictoryNickNameGet( VM_MACHINE * core )
{
	void** pwork		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	WORDSET** wordset	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_WORDSET );
	u16 buf_id			= VMGetWorkValue(core);

	ConScr_VictoryNickNameGet( *pwork, *wordset, buf_id );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 今参加していたコンテストで自分が何位だったかを取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 *
 * @li	順位(0オリジンです。 0=1位、1=2位、2=3位、3=4位)
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConRankingCheck( VM_MACHINE * core )
{
	void** pwork		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	u16* ret_wk			= VMGetWork( core );

	*ret_wk = ConScr_RankingCheck( *pwork );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 優勝したブリーダーのエントリー番号を取得する
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConVictoryEntryNoGet( VM_MACHINE * core )
{
	void** pwork		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	u16* ret_wk			= VMGetWork( core );

	*ret_wk = ConScr_VictoryEntryNoGet( *pwork );
	OS_TPrintf("victory_entry = %d\n", *ret_wk);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 自分のエントリー番号を取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConMyEntryNoGet( VM_MACHINE * core )
{
	void** pwork		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	u16* ret_wk			= VMGetWork( core );

	*ret_wk = ConScr_MyEntryNoGet( *pwork );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * OBJコードを取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConObjCodeGet( VM_MACHINE * core )
{
	void** pwork		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	u16 entry_no		= VMGetWorkValue( core );
	u16* ret_wk			= VMGetWork( core );

	*ret_wk = ConScr_OBJCodeGet( *pwork, entry_no );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 人気を取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConPopularityGet( VM_MACHINE * core )
{
	void** pwork		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	u16 entry_no		= VMGetWorkValue( core );
	u16* ret_wk			= VMGetWork( core );

	*ret_wk = ConScr_PopularityGet( *pwork, entry_no );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 受付ナンバー(シングルDESK_SINGLE、マルチDESK_MULTI, 練習DESK_PRACTICE)を取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConDeskModeGet( VM_MACHINE * core )
{
	void** pwork		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	u16* ret_wk			= VMGetWork( core );

	*ret_wk = ConScr_DeskModeGet(*pwork);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * コンテストシステムワークからランクやモードなどを取得する
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConEntryParamGet( VM_MACHINE * core )
{
	void** pwork		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	u16* ret_rank			= VMGetWork( core );
	u16* ret_type			= VMGetWork( core );
	u16* ret_mode			= VMGetWork( core );
	u16* ret_temoti_pos		= VMGetWork( core );

	ConScr_EntryParamGet(*pwork, ret_rank, ret_type, ret_mode, ret_temoti_pos);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 参加しているコンテストで優勝した時に貰えるリボンを既に持っているかチェック
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 *
 * TRUE:既に持っている(優勝経験済み)。　FALSE:持っていない
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConHaveRibbonCheck( VM_MACHINE * core )
{
	void** pwork		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	u16* ret_wk			= VMGetWork( core );

	*ret_wk = ConScr_HaveRibbonCheck(*pwork);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 参加しているコンテストで優勝した時に貰えるリボンの名前を取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 *
 * TRUE:既に持っている(優勝経験済み)。　FALSE:持っていない
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConRibbonNameGet( VM_MACHINE * core )
{
	void** pwork		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	WORDSET** wordset	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_WORDSET );
	u16 buf_id			= VMGetWorkValue(core);

	ConScr_RibbonItemNameGet(*pwork, *wordset, buf_id, HEAPID_WORLD);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 受付で貰えるアクセサリ番号を取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 *
 * ret_wk = アクセサリ番号。※優勝していない or 既に限界数まで所持している場合は0xffff
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConAcceNoGet( VM_MACHINE * core )
{
	void** pwork		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	u16* ret_wk			= VMGetWork( core );

	*ret_wk = ConScr_AcceNoGet(*pwork);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * コンテストのメッセージ送り設定を行う
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConMsgPrintFlagSet( VM_MACHINE * core )
{
	void** pwork		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );

	ConScr_MsgPrintFlagSet(*pwork);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * コンテストのメッセージ送り設定をリセットする
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConMsgPrintFlagReset( VM_MACHINE * core )
{
	void** pwork		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );

	ConScr_MsgPrintFlagReset(*pwork);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * カメラのフラッシュエフェクトタスクを生成する
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConCameraFlashSet( VM_MACHINE * core )
{
	void** pwork		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	u16 entry_no		= VMGetWorkValue( core );

	ConScr_FlashTaskCreate(*pwork, entry_no);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * カメラのフラッシュエフェクトが終了しているか確認
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConCameraFlashCheck( VM_MACHINE * core )
{
	void** pwork		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );

	VM_SetWait(core, EvWaitConCameraFlashCheck);
	return 1;
}

//return 1 = 終了
static BOOL EvWaitConCameraFlashCheck(VM_MACHINE * core)
{
	void** pwork		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );

	if(ConScr_FlashTaskCheck(*pwork) == TRUE){
		return 1;
	}
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * フィールドのHブランクを停止する
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConHBlankStop( VM_MACHINE * core )
{
	FLDHBLANK_SYS_Stop(core->fsys->fldmap->hblanksys);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * EvCmdConHBlankStopで停止させたフィールドのHブランクを再開させる
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConHBlankStart( VM_MACHINE * core )
{
	FLDHBLANK_SYS_Start(core->fsys->fldmap->hblanksys);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * CPUが優勝した時、又は通信対戦の時はエンディングの一部をスキップする
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 *
 * ret_wk：1、CPUが優勝or通信対戦
 * ret_wk：0、どちらの条件も満たさなかった
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConEndingSkipCheck( VM_MACHINE * core )
{
	void** pwork		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	u16* ret_wk			= VMGetWork( core );
	int entry_no, sio_flag, cpu_flag, tutorial, practice;
	
	ConScr_VictoryParamGet(*pwork, &entry_no, &sio_flag, &cpu_flag, &tutorial, &practice);
	if(sio_flag == TRUE || cpu_flag == TRUE || tutorial == TRUE || practice == TRUE){
		*ret_wk = 1;
	}
	else{
		*ret_wk = 0;
	}
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * コンテスト通信対戦成績画面呼び出し
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdConRecordDisp( VM_MACHINE * core )
{
	EventCmd_ConRecordDisp(core->event_work);
	return 1;
}

