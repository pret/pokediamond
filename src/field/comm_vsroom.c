//=============================================================================
/**
 * @file	comm_vsroom.c
 * @bfief	対戦部屋のイベント
 * @author	katsumi ohno
 * @date	06/05/13
 */
//=============================================================================

#include "common.h"
#include "system/bmp_list.h"
#include "system/fontproc.h"
#include "system/bmp_menu.h"
#include "field/fieldsys.h"
//#include "system/pm_str.h"
#include "system/gamedata.h"
#include "system/window.h"
#include "system/wipe.h"
#include "system\bmp_cursor.h"

#include "communication/communication.h"
#include "communication/comm_state.h"
#include "comm_command_field.h"
#include "comm_player.h"
#include "comm_field_state.h"
#include "msgdata/msg.naix"
#include "system/wordset.h"
#include "msgdata/msg_directbattlecorner.h"
#include "msgdata/msg_battle_room.h"

#include "fieldmap.h"
#include "fld_bmp.h"
#include "talk_msg.h"
#include "field_subproc.h"
#include "field/field.h"
#include "application/pokelist.h"
#include "field_battle.h"
#include "battle/attr_def.h"

#include "savedata/zukanwork.h"
#include "poketool/poke_number.h"
#include "savedata/perapvoice.h"
#include "ev_time.h"
#include "comm_direct_counter_def.h"
#include "system\snd_tool.h"

#include "savedata/sp_ribbon.h"

#include "comm_vsroom.h"

#define _EVWIN_MSG_BUF_SIZE		(100*2)			//メッセージバッファサイズ

typedef struct{
    PSTATUS_DATA* pPokeStatus;
    PLIST_DATA* pPokeList;
    StartLineCallBack* pCallBack;
	STRBUF* TalkString;							// 会話メッセージ用
	STRBUF* TalkStringEx;						// 会話メッセージ展開用
	GF_BGL_BMPWIN MsgWin;									// 会話ウインドウ
    FIELDSYS_WORK* pFSys;
	WORDSET* WordSet;					// メッセージ展開用ワークマネージャー
	MSGDATA_MANAGER* MsgManager;				// 名前入力メッセージデータマネージャー
	int	msgIndex;								// 終了検出用ワーク
    int seq;
    int ret_val;
	u8	pos;
	u8	sel[6];
    u8 timer;
    u8 timer2;

    u8*  mixPokeRecvBuffer;
    u8*  mixPokeSendBuffer;
    POKEPARTY*  mixPokeParty;
    GF_BGL_BMPWIN   MenuWinPoke;
    GF_BGL_BMPWIN   MenuWinAction;
    MYSTATUS*       friendStatus;
    BMPCURSOR*      ListCursor;
    GF_BGL_BMPWIN*  listWin;
    u8              listMaxElems;
    s8              listPos;
    u8              MyPokeSelectDecideFlag;
    u8              RivalsPokeSelectDecideFlag;
    u8              MyTradePokePos;
    u8              RivalsTradePokePos;

    u16  commID;
    u8   battleMode;
    u8   commSeq;

} EV_STARTLINE_WORK;


// --------------------------ここから対戦部屋

static void _initWork(EV_STARTLINE_WORK* wk);

typedef enum {
    _STARTLINE_MESSAGE_WAIT,
    _STARTLINE_MESSAGE,
    _STARTLINE_WAIT,
    _STARTLINE_WAIT_TIMING,
    _STARTLINE_CANCEL_TIMING,
    _STARTLINE_END,
    _STARTLINE_END2,
    _STARTLINE_BATTLE_START,
    _STARTLINE_EXIT,
    _STARTLINE_POKELIST_START_MESSAGE,
    _STARTLINE_POKELIST_START_MESSAGE_STW,
    _STARTLINE_POKELIST_START_MESSAGE2,
    _STARTLINE_POKELIST_START_MESSAGE_WAIT,
    _STARTLINE_POKELIST_START,
    _STARTLINE_POKELIST_WAIT,
    _STARTLINE_POKELIST,
    _STARTLINE_POKELISTEND,
    _STARTLINE_POKESTATUS,
    _STARTLINE_POKESTATUSEND,
    _RETURN_FIELD,
    _RETURN_FIELD_EXIT,
    _RETURN_FIELD2,
    _RETURN_FIELD_END2,

	_MIXBATTLE_START_POKESELECT_MESSAGE,
    _MIXBATTLE_START_POKESELECT_MESSAGE2,
	_MIXBATTLE_WAIT_POKESELECT_MESSAGE,
    _MIXBATTLE_START_COMM_POKEDATA,
    _MIXBATTLE_WAIT_SYNC_POKE_SELECT,
    _MIXBATTLE_WAIT_SEND_POKE,
    _MIXBATTLE_WAIT_SYNC_POKESEND,
    _MIXBATTLE_WAIT_TRADEINFO_MESSAGE,
    _MIXBATTLE_START_TRADE_POKELIST,
    _MIXBATTLE_CTRL_TRADE_POKELIST,
    _MIXBATTLE_GOTO_POKESTATUS,
	_MIXBATTLE_WAIT_POKESTATUS,
	_MIXBATTLE_WAIT_FIELD_RETURN,
	_MIXBATTLE_START_MENU_ACTION,
	_MIXBATTLE_WAIT_SYNC_TRADESELECT,
	_MIXBATTLE_CTRL_MENU_ACTION,
	_MIXBATTLE_WAIT_SYNC_TRADEPOS_SELECT,
	_MIXBATTLE_START_SEND_TRADEPOS,
	_MIXBATTLE_WAIT_SEND_TRADEPOS,
	_MIXBATTLE_START_CANCEL_MESSAGE,
	_MIXBATTLE_WAIT_CANCEL_MESSAGE,
	_MIXBATTLE_WAIT_SYNC_CANCEL,
	_MIXBATTLE_CANCEL,
};

enum {
	_STARTLINE_POKELIST_RESULT_CANCEL,
	_STARTLINE_POKELIST_RESULT_DECIDE,
	_STARTLINE_POKELIST_RESULT_STATUS,
};


/**
 *	マルチバトル用ポケモンステータス呼び出し
 */
static void _PokeStatusCall(EV_STARTLINE_WORK* wk,FIELDSYS_WORK* fsys, POKEPARTY* party, int pos, int psd_mode, int heapID )
{
	PSTATUS_DATA* psd;
	SAVEDATA	*sv;

	static const u8 PST_PageTbl[] = {
		PST_PAGE_INFO,			// 「ポケモンじょうほう」
		PST_PAGE_MEMO,			// 「トレーナーメモ」
		PST_PAGE_PARAM,			// 「ポケモンのうりょく」
		PST_PAGE_CONDITION,		// 「コンディション」
		PST_PAGE_B_SKILL,		// 「たたかうわざ」
		PST_PAGE_C_SKILL,		// 「コンテストわざ」
		PST_PAGE_RIBBON,		// 「きねんリボン」
		PST_PAGE_RET,			// 「もどる」
		PST_PAGE_MAX
	};
	
	sv = fsys->savedata;

	//ポケモンステータスを呼び出す
	//
	psd = sys_AllocMemoryLo(heapID, sizeof(PSTATUS_DATA));
	MI_CpuClear8(psd,sizeof(PSTATUS_DATA));
    PokeStatus_PlayerSet(psd, SaveData_GetMyStatus(fsys->savedata));
    psd->zukan_mode = PMNumber_GetMode(sv);
	psd->ev_contest = PokeStatus_ContestFlagGet(sv);
	psd->cfg  = SaveData_GetConfig(sv);
	psd->ppd  = party;
	psd->ppt  = PST_PP_TYPE_POKEPARTY;
	psd->pos  = pos;
	psd->max  = (u8)PokeParty_GetPokeCount( psd->ppd );
	psd->waza = 0;
	psd->mode = psd_mode;
	psd->ribbon = SaveData_GetSpRibbon(sv);
	PokeStatus_PageSet( psd, PST_PageTbl);
	
	GameSystem_StartSubProc( fsys, &PokeStatusProcData, psd );
	
	wk->pPokeStatus = psd;
}

/**
 *	@brief	マルチバトル用ポケモン選択呼出し
 *	@param	num	選択させるポケモン数
 *	@param	savedata	セーブデータへのポインタ
 */
static void _SelectPoke(EV_STARTLINE_WORK* wk,int heapID)
{
    int i;
    PLIST_DATA * pld = sys_AllocMemory(heapID,sizeof(PLIST_DATA));

	MI_CpuClear8(pld,sizeof(PLIST_DATA));
	pld->cfg = SaveData_GetConfig(wk->pFSys->savedata);
    pld->reg = (void*)wk->pFSys->regulation;
	pld->pp = SaveData_GetTemotiPokemon(wk->pFSys->savedata);
	pld->myitem = SaveData_GetMyItem(wk->pFSys->savedata);

	pld->type = PL_TYPE_SINGLE;
	pld->mode = PL_MODE_SELECT;

    if(wk->pFSys->regulation){
        pld->in_min = Regulation_GetParam(wk->pFSys->regulation, REGULATION_POKE_NUM);
        pld->in_max = pld->in_min;
    }
    else{
        pld->in_min = 3;
        pld->in_max = 3;
    }
	pld->in_lv = 100;
	pld->ret_sel = wk->pos;
	for(i = 0;i < 6;i++){
		pld->in_num[i] = wk->sel[i];
	}
	GameSystem_StartSubProc( wk->pFSys, &PokeListProcData, pld );
	wk->pPokeList = pld;
}

/**
 *	@brief	ポケモンリスト終了待ち
 */
static BOOL _PokeListWait(EV_STARTLINE_WORK* wk,FIELDSYS_WORK* fsys)
{
	int	ret;

	// サブプロセス終了待ち
	if( FieldEvent_Cmd_WaitSubProcEnd( fsys ) ) {
		return FALSE;
	}

	//現在選ばれているポケモンを保存
	MI_CpuCopy8(wk->pPokeList->in_num, wk->sel, 6);

	//データ取得
	switch(wk->pPokeList->ret_sel){
	case PL_SEL_POS_EXIT:	//やめる
		wk->ret_val = _STARTLINE_POKELIST_RESULT_CANCEL;
		break;
	case PL_SEL_POS_ENTER:	//決定
		wk->ret_val = _STARTLINE_POKELIST_RESULT_DECIDE;
		break;
	default:	//つよさをみる
		wk->ret_val = _STARTLINE_POKELIST_RESULT_STATUS;
		break;
	}
	//ポジションを保存
	wk->pos = wk->pPokeList->ret_sel;
	sys_FreeMemoryEz(wk->pPokeList);
	wk->pPokeList = NULL;

	return TRUE;
}

/**
 *	@brief	ポケモンステータス終了待ち
 */
static BOOL _PokeStatusWait(EV_STARTLINE_WORK* wk,FIELDSYS_WORK* fsys)
{
	PSTATUS_DATA* psd;

	// サブプロセス終了待ち
	if( FieldEvent_Cmd_WaitSubProcEnd(fsys) ) {
		return FALSE;
	}

	//切り替えられたカレントを保存する
	wk->pos = wk->pPokeStatus->pos;

	sys_FreeMemoryEz(wk->pPokeStatus);
	wk->pPokeStatus = NULL;

	return TRUE;
}




static BOOL _mapChangeWait( EV_STARTLINE_WORK* wk )
{
    if (FieldEvent_Cmd_WaitMapProcStart(wk->pFSys)) {
//        FieldOBJSys_MoveStopAll( wk->pFSys->fldobjsys );
        FieldFadeWipeSet( FLD_DISP_BRIGHT_BLACKIN );
        CommPlayerManagerReboot();
        return TRUE;
    }
    return FALSE;
}





enum {
	MIXBATTLE_POKE_COUNT = 3,		///< 参加させるポケモン数

	MIX_COMMFLG_FREE = 0,
	MIX_COMMFLG_SEND = 1,
	MIX_COMMFLG_RECV = 2,
	MIX_COMMFLG_COMPLETE = MIX_COMMFLG_SEND | MIX_COMMFLG_RECV,

	MIX_TRADELIST_WAIT = 0,
	MIX_TRADELIST_DECIDE,
	MIX_TRADELIST_CANCEL,
	MIX_TRADELIST_STATUS,

	MIX_SYNC_POKE_SELECT = 0,
	MIX_SYNC_POKE_SEND,
	MIX_SYNC_TRADE_SELECT,
	MIX_SYNC_TRADE_SEND,
	MIX_SYNC_CANCEL,


	MIX_MENUWIN_LINE_HEIGHT = 16,
	MIX_MENUWIN_WRITE_MARGIN = 16,

	MIX_ACTIONMENU_STATUS = 0,
	MIX_ACTIONMENU_DECIDE,
	MIX_ACTIONMENU_BACK,
	MIX_ACTIONMENU_MAX,

	MIX_MENUWIN_FRAME_CGXPOS = 1,
	MIX_MENUWIN_FRAME_PALPOS = FLD_MENUFRAME_PAL,

	MIX_MENUWIN_PALPOS = FLD_SYSFONT_PAL,

	MIX_MENUWIN_POKE_CGXPOS = MIX_MENUWIN_FRAME_CGXPOS + MENU_WIN_CGX_SIZE,
	MIX_MENUWIN_POKE_SIZE_X = 10,
	MIX_MENUWIN_POKE_SIZE_Y = (MIXBATTLE_POKE_COUNT+1)*2,
	MIX_MENUWIN_POKE_POS_X = 32 - (MIX_MENUWIN_POKE_SIZE_X+1),
	MIX_MENUWIN_POKE_POS_Y = 18 - (MIX_MENUWIN_POKE_SIZE_Y+1),

	MIX_MENUWIN_ACTION_CGXPOS = MIX_MENUWIN_POKE_CGXPOS + (MIX_MENUWIN_POKE_SIZE_X*MIX_MENUWIN_POKE_SIZE_Y),
	MIX_MENUWIN_ACTION_SIZE_X = 11,
	MIX_MENUWIN_ACTION_SIZE_Y = MIX_ACTIONMENU_MAX*2,
	MIX_MENUWIN_ACTION_POS_X = 32 - (MIX_MENUWIN_ACTION_SIZE_X+1),
	MIX_MENUWIN_ACTION_POS_Y = 18 - (MIX_MENUWIN_ACTION_SIZE_Y+1),

	MIX_MENUWIN_CLEAR_COLOR = 15,
	MIX_TRADEPOS_CANCEL_VALUE = 0xff,

};

//--------------------------------------------------
/**
 *  ミックスバトル交換ポケモンデータ付属情報
 */
//--------------------------------------------------
typedef struct {
	u32     decideFlag;		///< TRUEなら通常終了。FALSEならキャンセル終了。
}MIXBATTLE_POKEDATA_PARAM;



static void free_startline_work( EV_STARTLINE_WORK* wk );
static void setup_mixbattle_send_pokemon( EV_STARTLINE_WORK* wk, BOOL decideFlag );
static BOOL start_mixbattle_send_pokemon( EV_STARTLINE_WORK* wk );
static BOOL wait_mixbattle_send_pokemon( EV_STARTLINE_WORK* wk );
static void start_mixbattle_trade_pokelist( EV_STARTLINE_WORK* wk, int pos );
static int  ctrl_mixbattle_list( EV_STARTLINE_WORK* wk );
static void clear_mixbattle_list( EV_STARTLINE_WORK* wk );
static BOOL start_mixbattle_send_tradepos( EV_STARTLINE_WORK* wk );
static BOOL wait_mixbattle_send_tradepos( EV_STARTLINE_WORK* wk );
static void setup_mixbattle_party( EV_STARTLINE_WORK* wk );
static void setup_mixbattle_trade_party( EV_STARTLINE_WORK* wk );
static int  startline_event_print_message( EV_STARTLINE_WORK* wk, const STRBUF* str );
static void startline_event_delete_bmpwin( EV_STARTLINE_WORK* wk,BOOL bDispClear );
static void start_mixbattle_menu_action( EV_STARTLINE_WORK* wk, int pos );
static BOOL get_rivals_pokeselect_flag( EV_STARTLINE_WORK* wk );



//------------------------------------------------------------------
/**
 * 対戦相手が部屋を出てしまったかチェック
 *
 * @retval  BOOL		
 */
//------------------------------------------------------------------
static BOOL IsPartnerExit( void )
{
	int i, max;

	max = CommGetConnectNum();
	for(i=0; i<max; i++)
	{
		if( CommGetTimingSyncNo(i) == DBC_TIM_BATTLE_EXIT )
		{
			OS_TPrintf("partner exited\n");
			return TRUE;
		}
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 * @brief	対戦部屋スタートライン上でのイベント
 * @param	event		イベント制御ワークへのポインタ
 * @retval	TRUE		イベント終了
 * @retval	FALSE		イベント継続中
 */
//-----------------------------------------------------------------------------
static BOOL GMEVENT_StartLine(GMEVENT_CONTROL * event)
{
	EV_STARTLINE_WORK* wk = FieldEvent_GetSpecialWork(event);
	FIELDSYS_WORK* fsys = FieldEvent_GetFieldSysWork(event);

    switch (wk->seq) {
      case _STARTLINE_MESSAGE_WAIT:
        wk->timer--;
        if(wk->timer==0){
            wk->seq = _STARTLINE_MESSAGE;
            CommPlayerBattleDirSet();
        }
        break;
      case _STARTLINE_MESSAGE:
        MSGMAN_GetString( wk->MsgManager, msg_battle_room_01_02, wk->TalkString );
        wk->msgIndex = startline_event_print_message( wk, wk->TalkString );
        wk->seq = _STARTLINE_WAIT;
		break;
      case _STARTLINE_WAIT:
        if(FldTalkMsgEndCheck(wk->msgIndex)){
            CommTimingSyncStart(DBC_TIM_BATTLE_START);
            wk->seq = _STARTLINE_WAIT_TIMING;
        }
        break;
      case _STARTLINE_WAIT_TIMING:
        if(CommIsTimingSync(DBC_TIM_BATTLE_START)){
            wk->seq = _STARTLINE_BATTLE_START;
            FieldOBJSys_MoveStopAll( wk->pFSys->fldobjsys );
            wk->pCallBack(TRUE, wk->mixPokeParty);
        }
        else if(sys.trg & PAD_BUTTON_CANCEL){
            wk->seq = _STARTLINE_CANCEL_TIMING;
            CommTimingSyncStart(DBC_TIM_BATTLE_PAUSE);
            wk->timer=5;
        }
        break;
      case _STARTLINE_CANCEL_TIMING:
        if(CommIsTimingSync(DBC_TIM_BATTLE_START)){
            wk->seq = _STARTLINE_BATTLE_START;
            FieldOBJSys_MoveStopAll( wk->pFSys->fldobjsys );
            wk->pCallBack(TRUE, wk->mixPokeParty);
        }
        wk->timer--;
        if(wk->timer==0){
            wk->seq = _STARTLINE_EXIT;
        }
        break;
      case _STARTLINE_BATTLE_START:
        free_startline_work( wk );
        sys_FreeMemoryEz(wk);
        return TRUE;
      case _STARTLINE_END:
        free_startline_work( wk );
        sys_FreeMemoryEz(wk);
        CommPlayerHoldEnd();
        return TRUE;
      case _STARTLINE_EXIT:
        if(CommIsTimingSync(DBC_TIM_BATTLE_START)){  // この瞬間スタートがきたらスタートする
            wk->seq = _STARTLINE_END;
            wk->pCallBack(TRUE, wk->mixPokeParty);
        }
        else{
            wk->pCallBack(FALSE, wk->mixPokeParty);
            wk->seq = _STARTLINE_END;
        }
        break;
      case _STARTLINE_POKELIST_START_MESSAGE:
        wk->seq = _STARTLINE_POKELIST_START_MESSAGE_STW;
        wk->timer2 = 5;
        break;
      case _STARTLINE_POKELIST_START_MESSAGE_STW:
        if(wk->timer2!=0){
            wk->timer2--;
        }
        else{
            if(FieldOBJ_AcmdEndCheck(Player_FieldOBJGet(fsys->player))){
                wk->seq = _STARTLINE_POKELIST_START_MESSAGE2;
            }
        }
        break;
      case _STARTLINE_POKELIST_START_MESSAGE2:
        CommPlayerBattleDirSet();
		MSGMAN_GetString( wk->MsgManager, msg_battle_room_04_01, wk->TalkString );
		wk->msgIndex = startline_event_print_message( wk, wk->TalkString );
        wk->seq = _STARTLINE_POKELIST_START_MESSAGE_WAIT;
        break;
      case _STARTLINE_POKELIST_START_MESSAGE_WAIT:
        if( FldTalkMsgEndCheck(wk->msgIndex) ){
			wk->seq = _STARTLINE_POKELIST_START;
		}
        break;
      case _STARTLINE_POKELIST_START:
        FieldFadeWipeSet(FLD_DISP_BRIGHT_BLACKOUT);
        wk->seq = _STARTLINE_POKELIST_WAIT;
        break;
      case _STARTLINE_POKELIST_WAIT:
        wk->timer--;
        if(wk->timer==0){
            CommPlayerBattleDirSet();
            wk->seq = _STARTLINE_POKELIST;
        }
        break;
      case _STARTLINE_POKELIST:
        //CommPlayerManagerReset();
		startline_event_delete_bmpwin( wk,FALSE );
        _SelectPoke(wk, HEAPID_WORLD);
        wk->seq = _STARTLINE_POKELISTEND;
        break;

      case _STARTLINE_POKELISTEND:
        if( _PokeListWait(wk, wk->pFSys) )
        {
			switch( wk->ret_val ){
			case _STARTLINE_POKELIST_RESULT_CANCEL:
				wk->seq = _RETURN_FIELD_EXIT;
				break;

			case _STARTLINE_POKELIST_RESULT_DECIDE:
				wk->seq = _RETURN_FIELD;
				break;

			case _STARTLINE_POKELIST_RESULT_STATUS:
				wk->seq = _STARTLINE_POKESTATUS;
				break;
			}
		}
        break;

      case _STARTLINE_POKESTATUS:
        _PokeStatusCall(wk, wk->pFSys, SaveData_GetTemotiPokemon(wk->pFSys->savedata), wk->pos, PST_MODE_NORMAL, HEAPID_WORLD);
        wk->seq = _STARTLINE_POKESTATUSEND;
        break;

      case _STARTLINE_POKESTATUSEND:
        if( _PokeStatusWait(wk, wk->pFSys) )
        {
			wk->seq = _STARTLINE_POKELIST;
		}
        break;

      case _RETURN_FIELD:
		FieldEvent_Cmd_SetMapProc(wk->pFSys);
		if( wk->battleMode != COMM_MODE_BATTLE_MIX_1ON1 )
		{
			wk->timer = 5;
			wk->seq = _RETURN_FIELD2;
		}
		else
		{
			wk->seq = _MIXBATTLE_START_COMM_POKEDATA;
		}
        break;

      case _RETURN_FIELD2:
        CommStateSetPokemon(wk->sel);
        if( _mapChangeWait(wk) )
        {
			wk->timer = 5;
			wk->seq = _STARTLINE_MESSAGE_WAIT;
		}
        break;

      case _RETURN_FIELD_EXIT:
		FieldEvent_Cmd_SetMapProc(wk->pFSys);
		if( wk->battleMode != COMM_MODE_BATTLE_MIX_1ON1 )
		{
			wk->seq = _RETURN_FIELD_END2;
		}
		else
		{
			wk->seq = _MIXBATTLE_START_COMM_POKEDATA;
		}
        break;

      case _RETURN_FIELD_END2:
        if(  _mapChangeWait(wk) )
        {
			wk->seq = _STARTLINE_EXIT;
		}
        break;

	//-----------------------------------------------------------------------------
	// ここから下はミックスバトル用処理
	//-----------------------------------------------------------------------------

	//-----------------------------------------------------------------------------
	// 「３ひきえらんでください」メッセージ表示
	//-----------------------------------------------------------------------------
	case _MIXBATTLE_START_POKESELECT_MESSAGE:
        wk->timer2--;
        if(wk->timer2==0){
            wk->seq = _MIXBATTLE_START_POKESELECT_MESSAGE2;
        }
        break;
    case _MIXBATTLE_START_POKESELECT_MESSAGE2:
		CommPlayerBattleDirSet();
		MSGMAN_GetString( wk->MsgManager, msg_mixbattle_06, wk->TalkString );
		wk->msgIndex = startline_event_print_message( wk, wk->TalkString );
		wk->seq = _MIXBATTLE_WAIT_POKESELECT_MESSAGE;
		break;

	//-----------------------------------------------------------------------------
	// 「３ひきえらんでください」メッセージ終了後、選択画面へ
	//-----------------------------------------------------------------------------
	case _MIXBATTLE_WAIT_POKESELECT_MESSAGE:
		if( FldTalkMsgEndCheck(wk->msgIndex) )
		{
			wk->seq = _STARTLINE_POKELIST_START;
		}
		break;

	//-----------------------------------------------------------------------------
	// 送信するポケモンデータを作成しておき、通信同期を開始。
	//-----------------------------------------------------------------------------
    case _MIXBATTLE_START_COMM_POKEDATA:
		if( _mapChangeWait(wk) )
		{
			if( IsPartnerExit() )
			{
				wk->seq = _STARTLINE_END;
			}
			else
			{
				wk->MyPokeSelectDecideFlag = (wk->ret_val != _STARTLINE_POKELIST_RESULT_CANCEL);
				setup_mixbattle_send_pokemon( wk, wk->MyPokeSelectDecideFlag );
				CommTimingSyncStart( MIX_SYNC_POKE_SELECT );
				WORDSET_RegisterPlayerName( wk->WordSet, 0, wk->friendStatus );
				MSGMAN_GetString( wk->MsgManager, msg_mixbattle_01, wk->TalkString );
				WORDSET_ExpandStr( wk->WordSet, wk->TalkStringEx, wk->TalkString );
				wk->msgIndex = startline_event_print_message( wk, wk->TalkStringEx );
				wk->seq = _MIXBATTLE_WAIT_SYNC_POKE_SELECT;
			}
		}
		break;

	//-----------------------------------------------------------------------------
	// メッセージが流れた後、通信同期を待ってから送信開始
	//-----------------------------------------------------------------------------
	case _MIXBATTLE_WAIT_SYNC_POKE_SELECT:
		if( FldTalkMsgEndCheck(wk->msgIndex) )
		{
			if( IsPartnerExit() )
			{
				wk->seq = _STARTLINE_END;
			}
			else if(CommIsTimingSync(MIX_SYNC_POKE_SELECT))
			{
				start_mixbattle_send_pokemon( wk );
				wk->seq = _MIXBATTLE_WAIT_SEND_POKE;
			}
		}
		break;

	//-----------------------------------------------------------------------------
	// データ送受信完了したら通信同期開始
	//-----------------------------------------------------------------------------
	case _MIXBATTLE_WAIT_SEND_POKE:
		if( wait_mixbattle_send_pokemon( wk ) )
		{
			CommTimingSyncStart( MIX_SYNC_POKE_SEND );
			wk->seq = _MIXBATTLE_WAIT_SYNC_POKESEND;
		}
		break;

	//-----------------------------------------------------------------------------
	// 通信同期を待った後、
	// 互いにポケモンを３体選んでいたらミックスバトル説明表示へ
	// どちらかがキャンセルしていたら、キャンセル処理へ
	//-----------------------------------------------------------------------------
	case _MIXBATTLE_WAIT_SYNC_POKESEND:
		if( CommIsTimingSync(MIX_SYNC_POKE_SEND) )
		{
			wk->RivalsPokeSelectDecideFlag = get_rivals_pokeselect_flag( wk );

			if( wk->MyPokeSelectDecideFlag && wk->RivalsPokeSelectDecideFlag )
			{
		   		MSGMAN_GetString( wk->MsgManager, msg_mixbattle_07, wk->TalkString );
				wk->msgIndex = startline_event_print_message( wk, wk->TalkString );
				wk->seq = _MIXBATTLE_WAIT_TRADEINFO_MESSAGE;
			}
			else
			{
				wk->seq = _MIXBATTLE_START_CANCEL_MESSAGE;
			}
		}
		break;

	//-----------------------------------------------------------------------------
	// ミックスバトル説明メッセージ表示後、メニュー選択メッセージ表示
	//------------------------------------------------------------------------------
	case _MIXBATTLE_WAIT_TRADEINFO_MESSAGE:
		if( FldTalkMsgEndCheck(wk->msgIndex) )
		{
			wk->commSeq = MIX_COMMFLG_FREE;
			MSGMAN_GetString( wk->MsgManager, msg_mixbattle_04, wk->TalkString );
			wk->msgIndex = startline_event_print_message( wk, wk->TalkString );
			wk->MyTradePokePos = 0;
			wk->seq = _MIXBATTLE_START_TRADE_POKELIST;
		}
		break;

	//-----------------------------------------------------------------------------
	// メッセージ表示後、メニュー選択処理へ
	//------------------------------------------------------------------------------
	case _MIXBATTLE_START_TRADE_POKELIST:
		if( FldTalkMsgEndCheck(wk->msgIndex) )
		{
			setup_mixbattle_trade_party( wk );
			start_mixbattle_trade_pokelist( wk, wk->MyTradePokePos );
			wk->seq = _MIXBATTLE_CTRL_TRADE_POKELIST;
		}
		break;

	//-----------------------------------------------------------------------------
	// メニュー選択（相手のポケモンからどれを選ぶか？）
	//-----------------------------------------------------------------------------
	case _MIXBATTLE_CTRL_TRADE_POKELIST:
		switch( ctrl_mixbattle_list(wk) ){
		case MIX_TRADELIST_DECIDE:
			clear_mixbattle_list(wk);
			wk->MyTradePokePos = wk->listPos;
			wk->seq = _MIXBATTLE_START_MENU_ACTION;
			break;

		case MIX_TRADELIST_CANCEL:
			clear_mixbattle_list(wk);
			wk->MyTradePokePos = MIX_TRADEPOS_CANCEL_VALUE;
			MSGMAN_GetString( wk->MsgManager, msg_mixbattle_02, wk->TalkString );
			wk->msgIndex = startline_event_print_message( wk, wk->TalkString );
			CommTimingSyncStart( MIX_SYNC_TRADE_SELECT );
			wk->seq = _MIXBATTLE_WAIT_SYNC_TRADEPOS_SELECT;
			break;
		}
		break;

	//-----------------------------------------------------------------------------
	// 「○○○（選択されたポケモン）でいいですか？」メッセージ表示
	//-----------------------------------------------------------------------------
	case _MIXBATTLE_START_MENU_ACTION:
		WORDSET_RegisterPokeMonsName( wk->WordSet, 1, PPPPointerGet( PokeParty_GetMemberPointer(wk->mixPokeParty, wk->MyTradePokePos) ) );
		MSGMAN_GetString( wk->MsgManager, msg_mixbattle_05, wk->TalkString );
		WORDSET_ExpandStr( wk->WordSet, wk->TalkStringEx, wk->TalkString );
		wk->msgIndex = startline_event_print_message( wk, wk->TalkStringEx );
		wk->seq = _MIXBATTLE_WAIT_SYNC_TRADESELECT;
		break;

	//-----------------------------------------------------------------------------
	// メッセージ表示後、けってい・つよさを見る・もどるのメニュー処理へ
	//-----------------------------------------------------------------------------
	case _MIXBATTLE_WAIT_SYNC_TRADESELECT:
		if(FldTalkMsgEndCheck(wk->msgIndex))
		{
			start_mixbattle_menu_action( wk, 0 );
			wk->seq = _MIXBATTLE_CTRL_MENU_ACTION;
		}
		break;

	//-----------------------------------------------------------------------------
	// けってい・つよさを見る・もどるのメニュー処理
	//-----------------------------------------------------------------------------
	case _MIXBATTLE_CTRL_MENU_ACTION:
		switch( ctrl_mixbattle_list(wk) ){
		case MIX_TRADELIST_CANCEL:
			// もどる→ポケモン選択メニューへ
			clear_mixbattle_list(wk);
			MSGMAN_GetString( wk->MsgManager, msg_mixbattle_04, wk->TalkString );
			wk->msgIndex = startline_event_print_message( wk, wk->TalkString );
			wk->seq = _MIXBATTLE_START_TRADE_POKELIST;
//			wk->seq = _MIXBATTLE_CTRL_TRADE_POKELIST;
			break;

		case MIX_TRADELIST_DECIDE:
			// けってい→決定インデックスの通信交換処理へ
			if( wk->listPos == MIX_ACTIONMENU_DECIDE )
			{
				clear_mixbattle_list(wk);
				MSGMAN_GetString( wk->MsgManager, msg_mixbattle_01, wk->TalkString );
				WORDSET_ExpandStr( wk->WordSet, wk->TalkStringEx, wk->TalkString );
				wk->msgIndex = startline_event_print_message( wk, wk->TalkStringEx );
				CommTimingSyncStart( MIX_SYNC_TRADE_SELECT );
				wk->seq = _MIXBATTLE_WAIT_SYNC_TRADEPOS_SELECT;
			}
			// つよさをみる→ステータス画面へ
			else
			{
		        FieldFadeWipeSet(FLD_DISP_BRIGHT_BLACKOUT);
				wk->seq = _MIXBATTLE_GOTO_POKESTATUS;
			}
			break;
		}
		break;

	case _MIXBATTLE_GOTO_POKESTATUS:
		if( WIPE_SYS_EndCheck() )
		{
			startline_event_delete_bmpwin( wk,FALSE );
			_PokeStatusCall( wk, wk->pFSys, wk->mixPokeParty, wk->MyTradePokePos, PST_MODE_NO_WAZACHG, HEAPID_WORLD );
			wk->seq = _MIXBATTLE_WAIT_POKESTATUS;
		}
		break;

	//--------------------------------------------------------------------------
	// ステータス画面からの復帰を待ち、フィールド再構築
	//--------------------------------------------------------------------------
	case _MIXBATTLE_WAIT_POKESTATUS:
		if( _PokeStatusWait(wk, wk->pFSys) )
		{
			FieldEvent_Cmd_SetMapProc(wk->pFSys);
			wk->seq = _MIXBATTLE_WAIT_FIELD_RETURN;
		}
		break;

	//--------------------------------------------------------------------------
	// フィールド再構築を待ち、「○○○（選択されたポケモン）でいいですか？」メッセージ表示へ
	//--------------------------------------------------------------------------
	case _MIXBATTLE_WAIT_FIELD_RETURN:
		if( _mapChangeWait(wk) )
		{
			wk->seq = _MIXBATTLE_START_MENU_ACTION;
		}
		break;

	//--------------------------------------------------------------------------
	// 相手の選択待ちメッセージを表示後、通信同期を待つ
	//--------------------------------------------------------------------------
	case _MIXBATTLE_WAIT_SYNC_TRADEPOS_SELECT:
		if(FldTalkMsgEndCheck(wk->msgIndex))
		{
			if( CommIsTimingSync( MIX_SYNC_TRADE_SELECT ) )
			{
				start_mixbattle_send_tradepos( wk );
				wk->seq = _MIXBATTLE_WAIT_SEND_TRADEPOS;
			}
		}
		break;

	case _MIXBATTLE_WAIT_SEND_TRADEPOS:
		if( wait_mixbattle_send_tradepos( wk ) )
		{
			if( wk->MyTradePokePos == MIX_TRADEPOS_CANCEL_VALUE )
			{
				CommTimingSyncStart( MIX_SYNC_CANCEL );
				wk->seq = _MIXBATTLE_WAIT_SYNC_CANCEL;
			}
			else if( wk->RivalsTradePokePos == MIX_TRADEPOS_CANCEL_VALUE )
			{
				wk->seq = _MIXBATTLE_START_CANCEL_MESSAGE;
			}
			else
			{
				setup_mixbattle_party( wk );
				CommTimingSyncStart(DBC_TIM_BATTLE_START);
				wk->seq = _STARTLINE_WAIT;
			}
		}
		break;

	//--------------------------------------------------------------------------
	// 対戦キャンセルメッセージを流す
	//--------------------------------------------------------------------------
	case _MIXBATTLE_START_CANCEL_MESSAGE:
		MSGMAN_GetString( wk->MsgManager, msg_mixbattle_02, wk->TalkString );
		wk->msgIndex = startline_event_print_message( wk, wk->TalkString );
		wk->timer = 0;
		wk->seq = _MIXBATTLE_WAIT_CANCEL_MESSAGE;
		break;

	//--------------------------------------------------------------------------
	// 対戦キャンセルメッセージ表示後、一定時間ウェイトして、同期待ち
	//--------------------------------------------------------------------------
	case _MIXBATTLE_WAIT_CANCEL_MESSAGE:
		if(FldTalkMsgEndCheck(wk->msgIndex))
		{
			if(++(wk->timer) > 60)
			{
				CommTimingSyncStart( MIX_SYNC_CANCEL );
				wk->seq = _MIXBATTLE_WAIT_SYNC_CANCEL;
			}
		}
		break;

	//--------------------------------------------------------------------------
	// キャンセルメッセージ後の通信同期を待ち、イベント終了
	//--------------------------------------------------------------------------
	case _MIXBATTLE_WAIT_SYNC_CANCEL:
		if( CommIsTimingSync(MIX_SYNC_CANCEL) )
		{
			BmpTalkWinClear( &(wk->MsgWin), WINDOW_TRANS_ON );
            wk->pCallBack(FALSE, NULL);
            wk->seq = _STARTLINE_END;
		}
		break;

	}
	return FALSE;
}

static int startline_event_print_message( EV_STARTLINE_WORK* wk, const STRBUF* str )
{
	GF_BGL_BMPWIN* win = &(wk->MsgWin);

	if( GF_BGL_BmpWinAddCheck(win) == FALSE )
	{
	    FldTalkBmpAdd( wk->pFSys->bgl, win, FLD_MBGFRM_FONT );
		FieldTalkWinPut( win, SaveData_GetConfig(wk->pFSys->savedata) );
	}
	else
	{
		FieldTalkWinClear( win );
	}
	return FieldTalkMsgStart( win, (STRBUF*)str, SaveData_GetConfig(wk->pFSys->savedata), 1 );
}

static void startline_event_delete_bmpwin( EV_STARTLINE_WORK* wk,BOOL bDispClear )
{
	if( GF_BGL_BmpWinAddCheck(&(wk->MsgWin)) )
	{
        if(bDispClear){
            BmpTalkWinClear(&wk->MsgWin, WINDOW_TRANS_ON );
            GF_BGL_BmpWinOff(&wk->MsgWin);
        }
		GF_BGL_BmpWinDel(&wk->MsgWin);
		GF_BGL_BmpWinInit(&wk->MsgWin);
	}

	if( GF_BGL_BmpWinAddCheck(&(wk->MenuWinPoke)) )
	{
		GF_BGL_BmpWinDel(&wk->MenuWinPoke);
		GF_BGL_BmpWinInit(&wk->MenuWinPoke);
	}

	if( GF_BGL_BmpWinAddCheck(&(wk->MenuWinAction)) )
	{
		GF_BGL_BmpWinDel(&wk->MenuWinAction);
		GF_BGL_BmpWinInit(&wk->MenuWinAction);
	}
}

//-----------------------------------------------------------------------------
/**
 * @brief	対戦部屋スタートライン上でのイベントセット
 * @param	FIELDSYS_WORK
 * @retval	none
 */
//-----------------------------------------------------------------------------

void EventCmd_StartLine(FIELDSYS_WORK* pFSys, StartLineCallBack* pCallBack)
{
	EV_STARTLINE_WORK * wk;
    GMEVENT_CONTROL * event = pFSys->event;

    if(event){
        return;
    }
    wk = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(EV_STARTLINE_WORK));
    MI_CpuClear8(wk,sizeof(EV_STARTLINE_WORK));
    wk->timer = 5;
    wk->pFSys = pFSys;
    wk->pCallBack = pCallBack;

    wk->WordSet    = WORDSET_Create( HEAPID_WORLD );
    wk->MsgManager = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_battle_room_dat, HEAPID_WORLD );
    wk->TalkString =  STRBUF_Create( _EVWIN_MSG_BUF_SIZE, HEAPID_WORLD );
    wk->TalkStringEx =  STRBUF_Create( _EVWIN_MSG_BUF_SIZE, HEAPID_WORLD );
    GF_BGL_BmpWinInit( &wk->MsgWin );
    GF_BGL_BmpWinInit( &wk->MenuWinPoke );
    GF_BGL_BmpWinInit( &wk->MenuWinAction );
    wk->ListCursor = BMPCURSOR_Create( HEAPID_WORLD );

	wk->battleMode = CommStateGetServiceNo();
	wk->mixPokeSendBuffer = NULL;
	wk->mixPokeRecvBuffer = NULL;
	wk->mixPokeParty = NULL;
	wk->commSeq = MIX_COMMFLG_FREE;
	wk->commID = CommGetCurrentID();
	wk->friendStatus = CommInfoGetMyStatus( wk->commID^1 );

	switch( wk->battleMode ){
	case COMM_MODE_BATTLE_MIX_1ON1:
		{
			u32 bufSize = CommMixBattleGetDataSize();
			wk->mixPokeSendBuffer = sys_AllocMemoryLo( HEAPID_WORLD, bufSize );
			wk->mixPokeRecvBuffer = sys_AllocMemoryLo( HEAPID_WORLD, bufSize );
			wk->mixPokeParty = PokeParty_AllocPartyWork( HEAPID_WORLD );
			PokeParty_Init( wk->mixPokeParty, MIXBATTLE_POKE_COUNT );
            wk->timer2 = 5;
			wk->seq = _MIXBATTLE_START_POKESELECT_MESSAGE;
		}
		break;
	case COMM_MODE_BATTLE_MULTI:
		wk->seq = _STARTLINE_POKELIST_START_MESSAGE;
		break;

	default:
        if(wk->pFSys->regulation){
            wk->seq = _STARTLINE_POKELIST_START_MESSAGE;
        }
        else{
            wk->seq = _STARTLINE_MESSAGE_WAIT;
        }
		break;
	}

    FieldEvent_Set(pFSys, GMEVENT_StartLine, wk);
}


static void free_startline_work( EV_STARTLINE_WORK* wk )
{
	if( wk->mixPokeParty )
	{
		sys_FreeMemoryEz( wk->mixPokeParty );
	}
	if( wk->mixPokeSendBuffer )
	{
		sys_FreeMemoryEz( wk->mixPokeSendBuffer );
	}
	if( wk->mixPokeRecvBuffer )
	{
		sys_FreeMemoryEz( wk->mixPokeRecvBuffer );
	}

	MSGMAN_Delete( wk->MsgManager );
	WORDSET_Delete( wk->WordSet );
	STRBUF_Delete( wk->TalkString );
	STRBUF_Delete( wk->TalkStringEx );
	BMPCURSOR_Delete( wk->ListCursor );

	startline_event_delete_bmpwin( wk,TRUE );
}

//------------------------------------------------------------------
/**
 * イベントワークポインタ取得
 *
 * @param   fsys		フィールドシステムワーク
 *
 * @retval  EV_STARTLINE_WORK*		イベントワークポインタ
 */
//------------------------------------------------------------------
static EV_STARTLINE_WORK* get_startline_work( FIELDSYS_WORK* fsys )
{
	return FieldEvent_GetSpecialWork( fsys->event );
}
//------------------------------------------------------------------
/**
 * ミックスバトル参加ポケモン送信データをバッファに作成
 *
 * @param   wk				イベントワークポインタ
 *
 */
//------------------------------------------------------------------
static void setup_mixbattle_send_pokemon( EV_STARTLINE_WORK* wk, BOOL decideFlag )
{
	POKEPARTY* party;
	MIXBATTLE_POKEDATA_PARAM* param;
	u8 *buf;

	int i, size;

	party = SaveData_GetTemotiPokemon(wk->pFSys->savedata);
	buf = wk->mixPokeSendBuffer;
	size = PokemonParamSizeGet();
	param = (MIXBATTLE_POKEDATA_PARAM*)(buf + size * MIXBATTLE_POKE_COUNT);
	param->decideFlag = decideFlag;

	if (param->decideFlag )
	{
		for(i=0; i<MIXBATTLE_POKE_COUNT; i++)
		{
			MI_CpuCopy8( PokeParty_GetMemberPointer(party, wk->sel[i]-1), buf, size );
			buf += size;
		}
	}
}

//------------------------------------------------------------------
/**
 * リストで選んだポケモンデータの送受信を開始
 *
 * @param   wk			イベントワークポインタ
 *
 * @retval  BOOL		TRUEで成功
 */
//------------------------------------------------------------------
static BOOL start_mixbattle_send_pokemon( EV_STARTLINE_WORK* wk )
{
	if( wk->commSeq & MIX_COMMFLG_SEND )
	{
		return TRUE;
	}
	else
	{
		BOOL result;
		u8 *buf;
		u32 size;

		buf = wk->mixPokeSendBuffer;
		size = CommMixBattleGetDataSize();

		if( wk->commID == COMM_PARENT_ID )
		{
			result = CommSendHugeData_ServerSide( CF_MIXBATTLE, buf, size );
		}
		else
		{
			result = CommSendHugeData( CF_MIXBATTLE, buf, size );
		}

		if( result )
		{
			wk->commSeq |= MIX_COMMFLG_SEND;
		}

		return result;
	}
}

//------------------------------------------------------------------
/**
 * ポケモンデータ送受信の終了待ち
 *
 * @param   wk		イベントワークポインタ
 *
 * @retval  BOOL	TRUEで終了
 */
//------------------------------------------------------------------
static BOOL wait_mixbattle_send_pokemon( EV_STARTLINE_WORK* wk )
{
	if( wk->commSeq == MIX_COMMFLG_COMPLETE )
	{
		return TRUE;
	}

	return FALSE;
}

//------------------------------------------------------------------
/**
 * 対戦相手がポケモンを３体選んだか、キャンセルしたかフラグを取得
 *
 * @param   wk			イベントワークポインタ
 *
 * @retval  BOOL		TRUEなら３体選んだ。FALSEだとキャンセルした。
 */
//------------------------------------------------------------------
static BOOL get_rivals_pokeselect_flag( EV_STARTLINE_WORK* wk )
{
	MIXBATTLE_POKEDATA_PARAM* param;

	param = (MIXBATTLE_POKEDATA_PARAM*)((u8*)(wk->mixPokeRecvBuffer) + (PokemonParamSizeGet() * MIXBATTLE_POKE_COUNT));
	return param->decideFlag;
}

static BOOL start_mixbattle_send_tradepos( EV_STARTLINE_WORK* wk )
{
	BOOL result;

	if( wk->commID == COMM_PARENT_ID )
	{
		result = CommSendData_ServerSide( CF_MIXBATTLE_TRADE, &(wk->MyTradePokePos), 1 );
	}
	else
	{
		result = CommSendData( CF_MIXBATTLE_TRADE, &(wk->MyTradePokePos), 1 );
	}

	if( result )
	{
		wk->commSeq |= MIX_COMMFLG_SEND;
	}

	return result;
}

static BOOL wait_mixbattle_send_tradepos( EV_STARTLINE_WORK* wk )
{
	if( wk->commSeq == MIX_COMMFLG_COMPLETE )
	{
		return TRUE;
	}
	return FALSE;
}

static void setup_mixbattle_trade_party( EV_STARTLINE_WORK* wk )
{
	u32  pokeSize;
	int  i;

	pokeSize = PokemonParamSizeGet();

	PokeParty_Init( wk->mixPokeParty, MIXBATTLE_POKE_COUNT );
	for(i=0; i<MIXBATTLE_POKE_COUNT; i++)
	{
		PokeParty_Add( wk->mixPokeParty, (POKEMON_PARAM*)(&wk->mixPokeRecvBuffer[ i*pokeSize ]) );
	}
}


static void setup_mixbattle_party( EV_STARTLINE_WORK* wk )
{
	u32  pokeSize;
	u8   *dst, *src;
	int  i;

	pokeSize = PokemonParamSizeGet();
	dst = &wk->mixPokeSendBuffer[ wk->RivalsTradePokePos * pokeSize ];
	src = &wk->mixPokeRecvBuffer[ wk->MyTradePokePos * pokeSize ];

	MI_CpuCopy8( src, dst, pokeSize );

	PokeParty_Init( wk->mixPokeParty, MIXBATTLE_POKE_COUNT );
	for(i=0; i<MIXBATTLE_POKE_COUNT; i++)
	{
		PokeParty_Add( wk->mixPokeParty, (POKEMON_PARAM*)(&wk->mixPokeSendBuffer[ i*pokeSize ]) );
	}
}





//------------------------------------------------------------------
/**
 * ポケモンリスト画面へ
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void start_mixbattle_trade_pokelist( EV_STARTLINE_WORK* wk, int pos )
{
	GF_BGL_BMPWIN* win = &(wk->MenuWinPoke);

	if( GF_BGL_BmpWinAddCheck(win) == FALSE )
	{
		int i, monsno, size;
		MSGDATA_MANAGER* mmMonsName;

		mmMonsName = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_monsname_dat, HEAPID_FIELD );
		size = PokemonParamSizeGet();

		GF_BGL_BmpWinAdd( wk->pFSys->bgl, win, FLD_MBGFRM_FONT,
			MIX_MENUWIN_POKE_POS_X, MIX_MENUWIN_POKE_POS_Y, MIX_MENUWIN_POKE_SIZE_X, MIX_MENUWIN_POKE_SIZE_Y,
			MIX_MENUWIN_PALPOS, MIX_MENUWIN_POKE_CGXPOS );

		MenuWinGraphicSet( wk->pFSys->bgl, FLD_MBGFRM_FONT, MIX_MENUWIN_FRAME_CGXPOS, MIX_MENUWIN_FRAME_PALPOS, 
							MENU_TYPE_SYSTEM, HEAPID_FIELD );

		GF_BGL_BmpWinDataFill(win, MIX_MENUWIN_CLEAR_COLOR);
		for(i=0; i<MIXBATTLE_POKE_COUNT; i++)
		{
			monsno = PokeParaGet( (POKEMON_PARAM*)( &wk->mixPokeRecvBuffer[i*size] ), ID_PARA_monsno, NULL );
			MSGMAN_GetString( mmMonsName, monsno, wk->TalkString );
			GF_STR_PrintSimple( win, FONT_SYSTEM, wk->TalkString, 
				MIX_MENUWIN_WRITE_MARGIN, i*MIX_MENUWIN_LINE_HEIGHT, MSG_NO_PUT, NULL );
		}

		MSGMAN_GetString( wk->MsgManager, msg_mixbattle_menu0, wk->TalkString );
		GF_STR_PrintSimple( win, FONT_SYSTEM, wk->TalkString, 
			MIX_MENUWIN_WRITE_MARGIN, i*MIX_MENUWIN_LINE_HEIGHT, MSG_NO_PUT, NULL );

		MSGMAN_Delete(mmMonsName);
	}

	GF_BGL_BmpWinFill( win, MIX_MENUWIN_CLEAR_COLOR, 0, 0, MIX_MENUWIN_WRITE_MARGIN, win->sizy*8 );
	BMPCURSOR_Print( wk->ListCursor, &wk->MenuWinPoke, 0, pos * MIX_MENUWIN_LINE_HEIGHT );
	BmpMenuWinWrite( &wk->MenuWinPoke, WINDOW_TRANS_ON, MIX_MENUWIN_FRAME_CGXPOS, MIX_MENUWIN_FRAME_PALPOS );

	wk->listPos = pos;
	wk->listMaxElems = MIXBATTLE_POKE_COUNT + 1;
	wk->listWin = win;
}

//------------------------------------------------------------------
/**
 * ポケモン選択後のリストメニュー表示
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void start_mixbattle_menu_action( EV_STARTLINE_WORK* wk, int pos )
{
	GF_BGL_BMPWIN* win = &(wk->MenuWinAction);

	if( GF_BGL_BmpWinAddCheck(win) == FALSE )
	{
		int i;

		GF_BGL_BmpWinAdd( wk->pFSys->bgl, win, FLD_MBGFRM_FONT,
			MIX_MENUWIN_ACTION_POS_X, MIX_MENUWIN_ACTION_POS_Y, MIX_MENUWIN_ACTION_SIZE_X, MIX_MENUWIN_ACTION_SIZE_Y,
			MIX_MENUWIN_PALPOS, MIX_MENUWIN_ACTION_CGXPOS );

		MenuWinGraphicSet( wk->pFSys->bgl, FLD_MBGFRM_FONT, MIX_MENUWIN_FRAME_CGXPOS, MIX_MENUWIN_FRAME_PALPOS, 
							MENU_TYPE_SYSTEM, HEAPID_FIELD );

		GF_BGL_BmpWinDataFill(win, MIX_MENUWIN_CLEAR_COLOR);
		for(i=0; i<MIX_ACTIONMENU_MAX; i++)
		{
			MSGMAN_GetString( wk->MsgManager, msg_mixbattle_menu1+i, wk->TalkString );
			GF_STR_PrintSimple( win, FONT_SYSTEM, wk->TalkString, 
				MIX_MENUWIN_WRITE_MARGIN, i*MIX_MENUWIN_LINE_HEIGHT, MSG_NO_PUT, NULL );
		}
	}

	wk->listMaxElems = MIX_ACTIONMENU_MAX;
	wk->listWin = win;
	wk->listPos = pos;

	GF_BGL_BmpWinFill( win, MIX_MENUWIN_CLEAR_COLOR, 0, 0, MIX_MENUWIN_WRITE_MARGIN, win->sizy*8 );
	BMPCURSOR_Print( wk->ListCursor, wk->listWin, 0, pos * MIX_MENUWIN_LINE_HEIGHT );
	BmpMenuWinWrite( wk->listWin, WINDOW_TRANS_ON, MIX_MENUWIN_FRAME_CGXPOS, MIX_MENUWIN_FRAME_PALPOS );
}

/**
 *	@brief	ポケモンリスト終了待ち
 */
static int ctrl_mixbattle_list( EV_STARTLINE_WORK* wk )
{
	do
	{
		if( sys.trg & PAD_KEY_UP )
		{
			wk->listPos = ((wk->listPos==0)? (wk->listMaxElems-1) : (wk->listPos-1));
			break;
		}
		if( sys.trg & PAD_KEY_DOWN )
		{
			wk->listPos = (wk->listPos == (wk->listMaxElems-1))?  0 : (wk->listPos+1);
			break;
		}
		if( sys.trg & PAD_BUTTON_A )
		{
			Snd_SePlay( SEQ_SE_DP_SELECT );
			if( wk->listPos < (wk->listMaxElems-1) )
			{
				return MIX_TRADELIST_DECIDE;
			}
			else
			{
				return MIX_TRADELIST_CANCEL;
			}
		}
		if( sys.trg & PAD_BUTTON_B )
		{
			Snd_SePlay( SEQ_SE_DP_SELECT );
			return MIX_TRADELIST_CANCEL;
		}

		return MIX_TRADELIST_WAIT;

	}while(0);

	Snd_SePlay( SEQ_SE_DP_SELECT );
	GF_BGL_BmpWinFill( wk->listWin, MIX_MENUWIN_CLEAR_COLOR, 0, 0, MIX_MENUWIN_WRITE_MARGIN, wk->listWin->sizy*8 );
	BMPCURSOR_Print( wk->ListCursor, wk->listWin, 0, wk->listPos * MIX_MENUWIN_LINE_HEIGHT );
	GF_BGL_BmpWinCgxOn( wk->listWin );

	return MIX_TRADELIST_WAIT;
}

static void clear_mixbattle_list( EV_STARTLINE_WORK* wk )
{
	BmpMenuWinClear( wk->listWin, TRUE );
}


void CommMixBattleRecv(int netID, int size, void* pBuff, void* pWork)
{
	EV_STARTLINE_WORK* wk = get_startline_work( pWork );

	if( wk->commID != netID )
	{
		wk->commSeq |= MIX_COMMFLG_RECV;
	}
}

int  CommMixBattleGetDataSize( void )
{
	return PokemonParamSizeGet() * MIXBATTLE_POKE_COUNT + sizeof(MIXBATTLE_POKEDATA_PARAM);
}
u8* CommMixBattleGetBuffer( int netID, void* pWork, int size )
{
	EV_STARTLINE_WORK* wk = get_startline_work( pWork );

	if( wk->commID != netID )
	{
		return wk->mixPokeRecvBuffer;
	}
	else
	{
		return NULL;
	}
}

void CommMixBattleTradeRecv( int netID, int size, void* pBuff, void* pWork )
{
	EV_STARTLINE_WORK* wk = get_startline_work( pWork );

	if( wk->commID != netID )
	{
		wk->RivalsTradePokePos = *((u8*)pBuff);
		wk->commSeq |= MIX_COMMFLG_RECV;
	}
}

//-----------------------------------------------------------------------------
/**
 * @brief	トレーナーカード
 * @param	FIELDSYS_WORK
 * @retval	none
 */
//-----------------------------------------------------------------------------

typedef struct{
	STRBUF* TalkString;							// 会話メッセージ用
	STRBUF* TalkStringEx;							// 会話メッセージExpand用
	GF_BGL_BMPWIN MsgWin;									// 会話ウインドウ
	WORDSET* WordSet;					// メッセージ展開用ワークマネージャー
	MSGDATA_MANAGER* MsgManager;				// 名前入力メッセージデータマネージャー
	int	msgIndex;								// 終了検出用ワーク
    int targetID;
    int seq;
} _EV_TRCARD_WORK;


static BOOL GMEVENT_TrCard(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	_EV_TRCARD_WORK *wk = FieldEvent_GetSpecialWork(event);
    TR_CARD_DATA* pTargetCard = (TR_CARD_DATA*)CommDCGetTrainerCardRecvBuff(wk->targetID,NULL,0);
    enum{
        _INIT,
        _MSG,
        _FADEOUT,
		_TRAINER_CARD_DISP,
        _TRAINER_CARD_DISP_END,
        _RETURN_FIELD,
        _RETURN_FIELD2,
        _FREE,
        _NOP
	};
		
	switch (wk->seq) {
      case _INIT:
        wk->WordSet    = WORDSET_Create( HEAPID_FIELD );
        wk->MsgManager = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_battle_room_dat, HEAPID_FIELD );
        wk->TalkString =  STRBUF_Create( _EVWIN_MSG_BUF_SIZE, HEAPID_FIELD );
        wk->TalkStringEx =  STRBUF_Create( _EVWIN_MSG_BUF_SIZE, HEAPID_FIELD );
        MSGMAN_GetString( wk->MsgManager,
                          msg_battle_room_02_01 + pTargetCard->CardRank,
                          wk->TalkString );
        WORDSET_RegisterPlayerName( wk->WordSet, 0, CommInfoGetMyStatus(wk->targetID));
        WORDSET_ExpandStr( wk->WordSet, wk->TalkStringEx, wk->TalkString );
        FldTalkBmpAdd( fsys->bgl, &wk->MsgWin, FLD_MBGFRM_FONT );
        FieldTalkWinPut( &wk->MsgWin, SaveData_GetConfig(fsys->savedata) );
        wk->msgIndex = FieldTalkMsgStart(&wk->MsgWin, wk->TalkStringEx,
                                         SaveData_GetConfig(fsys->savedata), 1);
        wk->seq ++;
        break;
      case _MSG:
        if(FldTalkMsgEndCheck(wk->msgIndex)){
            if(sys.trg & PAD_BUTTON_DECIDE){
                MSGMAN_Delete( wk->MsgManager );
                WORDSET_Delete( wk->WordSet );
                STRBUF_Delete( wk->TalkString );
                STRBUF_Delete( wk->TalkStringEx );
                BmpTalkWinClear( &wk->MsgWin, WINDOW_TRANS_ON );
                GF_BGL_BmpWinDel(&wk->MsgWin);
                FieldFadeWipeSet(FLD_DISP_BRIGHT_BLACKOUT);
                wk->seq ++;
            }
        }
        break;
      case _FADEOUT:
        if(WIPE_SYS_EndCheck()){
            wk->seq++;
        }
        break;
      case _TRAINER_CARD_DISP:
        FieldTrCard_SetProc(fsys, pTargetCard);
        wk->seq++;
        break;
      case _TRAINER_CARD_DISP_END:
        if( !FieldEvent_Cmd_WaitSubProcEnd( fsys ) ) {
            wk->seq++;
        }
		break;
      case _RETURN_FIELD:
        FieldEvent_Cmd_SetMapProc(fsys);
        wk->seq++;
        break;
      case _RETURN_FIELD2:
        if( !FieldEvent_Cmd_WaitMapProcStart(fsys) ){
            FieldFadeWipeSet( FLD_DISP_BRIGHT_BLACKIN );
            CommPlayerManagerReboot();
            wk->seq++;
        }
        break;
      case _FREE:
//        FieldSystemProc_SeqHoldEnd();
        CommPlayerHoldEnd();
		sys_FreeMemoryEz(wk);
		return TRUE;
      default:
		return TRUE;
	}
	return FALSE;
}



void EventCmd_VSRoomTrainer(FIELDSYS_WORK * pFSys)
{
    int i;
    int myID = CommGetCurrentID();
    int x = CommPlayerGetPosXDirAdd(myID);
    int z = CommPlayerGetPosZDirAdd(myID);

    
    for(i = 0;i < CommGetConnectNum();i++){
        if(i == myID){
            continue;  // 自分が探せるはずは無いが念のため
        }
        if((x ==CommPlayerGetPosX(i)) && (z ==CommPlayerGetPosZ(i))){
            _EV_TRCARD_WORK *wk = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(_EV_TRCARD_WORK));
            wk->targetID = i;
            wk->seq = 0;
            FieldEvent_Set(pFSys, GMEVENT_TrCard, wk);
            FieldSystemProc_SeqHold();
            break;
        }
    }
}

