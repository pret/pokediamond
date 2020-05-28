//============================================================================================
/**
 * @file	scrcmd.c
 * @bfief	スクリプトコマンド用関数
 * @author	Satoshi Nohara
 * @date	05.08.04
 *
 * 05.04.26 Hiroyuki Nakamura
 */
//============================================================================================
#include "common.h"

#include <nitro/code16.h> 
#include "system/pm_str.h"
#include "system\msgdata.h"			//MSGMAN_GetString
#include "system/brightness.h"		//ChangeBrightnessRequest
#include "system\wordset.h"			//WordSet_RegistPlayerName
#include "system/bmp_menu.h"
#include "system/bmp_list.h"
#include "system/get_text.h"
#include "system/window.h"
#include "system/fontproc.h"
#include "system/pms_data.h"
#include "system/wipe.h"

#include "fieldsys.h"
#include "fieldmap.h"
#include "fieldmap_work.h"
#include "fld_bmp.h"
#include "talk_msg.h"
#include "fieldobj.h"
#include "fld_bgm.h"
#include "field_subproc.h"
#include "field/field.h"
#include "field/poketch_data.h"
#include "field/eventflag.h"
#include "field/evwkdef.h"
#include "sysflag.h"
#include "syswork.h"
#include "vm.h"
#include "scrcmd.h"
#include "script.h"
#include "scr_tool.h"
#include "scrcmd_def.h"
#include "ev_win.h"
#include "ev_time.h"
#include "guinness_win.h"
#include "msgdata\msg.naix"			//NARC_msg_??_dat
#include "wifi_autoregist.h"
#include "application/wifi_p2pmatch.h"
#include "application/namein.h"
#include "poketool/pokeparty.h"
#include "battle/battle_common.h"	//↓インクルードに必要
#include "poketool/tr_tool.h"		//TT_TrainerMessageGet
#include "poketool/poke_tool.h"		//PokeParaWazaDelPos
#include "poketool/poke_memo.h"
#include "itemtool/myitem.h"		//MyItem_AddItem
#include "itemtool/item.h"			//ItemParamGet
#include "ev_mapchange.h"			//GMEVENT_Call_MapChange
#include "field_encount.h"			//DebugFieldEncount
#include "ev_poketch.h"
#include "comm_union.h"				//Union_ConnectIdSet
#include "field/union_beacon_tool.h"		// UnionView_GetTrainerType
#include "comm_union_beacon.h"		// Union_BeaconChange
#include "comm_union_def.h"	

#include "comm_regulation.h"
#include "comm_direct_counter.h"
#include "comm_field_state.h"
#include "communication/communication.h"
#include "communication/comm_def.h"
#include "communication/comm_state.h"
#include "underground/ug_manager.h"
#include "field/honey_tree_enc.h"
#include "report.h"
#include "ev_pokemon.h"				//EvPoke_Add
#include "situation_local.h"

#include "poketool/status_rcv.h"

#include "field_3d_anime_ev.h"

#include "savedata/poruto_util.h"
#include "savedata/fnote_mem.h"
#include "savedata/custom_ball.h"
#include "savedata/system_data.h"
#include "savedata/dendou_data.h"

#include "sodateya.h"

#include "gym.h"
#include "gym_init.h"
#include "eventdata.h"
#include "itemtool/nuts.h"

#include "application/trainer_card.h"	//TR_CARD_DATA
#include "tr_card_setup.h"				//TRCSET_MakeTrainerInfo
#include "application/pokelist.h"
#include "application/btwr_app.h"
#include "savedata/zukanwork.h"
#include "savedata/imageclip_data.h"	//ImageClipSave
#include "include/application/imageClip/imc_sys.h"	//ImageClipProcData
#include "include/application/imageClip/imc_preview.h"	//ImageClipProcData
#include "include/poketool/monsno.h"
#include "savedata/coin.h"				//コインを扱う関数用
#include "savedata/fnote_mem.h"			//冒険ノート
#include "include/demo/ev_poke_select.h"
#include "include/application/cb_sys.h"	///< custom ball
#include "include/system/pm_rtc.h"
#include "ookisa.h"						//大きさ比べ
#include "application/townmap.h"
#include "field/fld_nmixer.h"
#include "field/b_tower_fld.h"
#include "savedata/record.h"
#include "field/scr_btower.h"
#include "safari_scope.h"		//サファリ望遠鏡
#include "btl_searcher.h"
#include "field_cutin.h"
#include "scr_hideneff.h"
#include "safari_train.h"
#include "player.h"
#include "demo\demo_dendou.h"
#include "scr_msg.h"
#include "savedata/undergrounddata.h"
#include "wifi/dwc_rap.h"
#include "savedata/encount.h"
#include "move_pokemon.h"
#include "place_name.h"
#include "generate_zone.h"
#include "tv.h"
#include "field_trade_cmd.h"
#include "ashiato.h"
#include "pc_recover_anm.h"
#include "elevator_anm.h"
#include "paso_anm.h"
#include "ship_demo_call.h"
#include "hill_back_poke.h"
#include "..\application\p_status\ribbon.h"
#include "savedata/tv_work.h"
#include "tv_topic.h"		//テレビトピック生成用
#include "field/tvtopic_extern.h"
#include "field/msgboy.h"
#include "poketool/poke_tool.h"
#include "battle/wazano_def.h"
#include "poketool/boxdata.h"
#include "scr_boxpwd.h"
#include "dendou_ball_anm.h"
#include "contest/contest.h"
#include "system/pmfprint.h"
#include "demo/syoujyou.h"
#include "fld_lift.h"
#include "rah_cylinder_anm.h"
#include "weather_sys.h"
#include "system/pms_word.h"
#include "fielddata/maptable/zone_id.h"
#include "system/msgdata_util.h"
#include "field_demo.h"
#include "scr_nagisa_scope.h"
#include "fld_flg_init.h"

//============================================================================================
//
//	extern宣言
//
//============================================================================================
#include "scr_group.h"		//EvCmdRandomGroup
#include "scr_tv.h"			//EvCmdBroadcastTV
#include "scr_kinomi.h"		//EvCmdSeed～
#include "scr_shop.h"
#include "scr_contest.h"
#include "scr_name.h"
#include "scr_pokelot.h"
#include "scr_sound.h"
#include "scr_trainer.h"
#include "scr_postman.h"	//EvCmdMysteryPostMan
#include "scr_pokepark.h"	//EvCmdPokeParkControl他
#include "scr_coin.h"		//EvCmdCoin～
#include "scr_gold.h"		//EvCmdGold～
#include "scr_sodateya.h"	//EvCmdGetSodate～
#include "scr_n_park.h"		//EvCmdNatural～
#include "scr_poke.h"
#include "scr_kaseki.h"
#include "scr_exchange.h"
#include "scr_sysflag.h"
#include "scr_item.h"
#include "scr_goods.h"
#include "scr_wazalist.h"
#include "scr_dprint.h"
#include "scr_climaxdemo.h"	//ClimaxDemoCall

extern void EventCmd_ContestSioProc(GMEVENT_CONTROL * event);

//============================================================================================
//
//	定義
//
//============================================================================================
typedef u16 (* pMultiFunc)();

//レジスタ比較の結果定義
enum {
	MINUS_RESULT = 0,	//比較結果がマイナス
	EQUAL_RESULT,		//比較結果がイコール
	PLUS_RESULT			//比較結果がプラス
};


//============================================================================================
//
//	プロトタイプ宣言
//
//============================================================================================
static BOOL EvCmdNop( VM_MACHINE * core );				//
static BOOL EvCmdDummy( VM_MACHINE * core );				//
static BOOL EvCmdEnd( VM_MACHINE * core );				//
static BOOL EvCmdTimeWait( VM_MACHINE * core );			//
static BOOL EvWaitTime(VM_MACHINE * core);
static BOOL EvCmdLoadRegValue( VM_MACHINE * core );
static BOOL EvCmdLoadRegWData( VM_MACHINE * core );
static BOOL EvCmdLoadRegAdrs( VM_MACHINE * core );
static BOOL EvCmdLoadAdrsValue( VM_MACHINE * core );
static BOOL EvCmdLoadAdrsReg( VM_MACHINE * core );
static BOOL EvCmdLoadRegReg( VM_MACHINE * core );
static BOOL EvCmdLoadAdrsAdrs( VM_MACHINE * core );
static BOOL EvCmdCmpMain( u16 r1, u16 r2 );
static BOOL EvCmdCmpRegReg( VM_MACHINE * core );			//
static BOOL EvCmdCmpRegValue( VM_MACHINE * core );		//
static BOOL EvCmdCmpRegAdrs( VM_MACHINE * core );
static BOOL EvCmdCmpAdrsReg( VM_MACHINE * core );
static BOOL EvCmdCmpAdrsValue(VM_MACHINE * core);
static BOOL EvCmdCmpAdrsAdrs(VM_MACHINE * core);
static BOOL EvCmdCmpWkValue( VM_MACHINE * core );			//
static BOOL EvCmdCmpWkWk( VM_MACHINE * core );			//
static BOOL EvCmdVMMachineAdd( VM_MACHINE * core );
static BOOL EvCmdChangeCommonScr( VM_MACHINE * core );
static BOOL EvChangeCommonScrWait(VM_MACHINE * core);
static BOOL EvCmdChangeLocalScr( VM_MACHINE * core );
static BOOL EvCmdGlobalJump( VM_MACHINE * core );			//
static FIELD_OBJ_PTR FieldObjPtrGetByObjId( FIELDSYS_WORK* fsys, int obj_id );
static BOOL EvCmdObjIDJump( VM_MACHINE * core );
static BOOL EvCmdBgIDJump( VM_MACHINE * core );
static BOOL EvCmdPlayerDirJump( VM_MACHINE * core );
static BOOL EvCmdGlobalCall( VM_MACHINE * core );			//
static BOOL EvCmdRet( VM_MACHINE * core );				//
static BOOL EvCmdIfJump( VM_MACHINE * core );				//
static BOOL EvCmdIfCall(VM_MACHINE * core);
static BOOL EvCmdFlagSet( VM_MACHINE * core );			//
static BOOL EvCmdFlagReset( VM_MACHINE * core );			//
static BOOL EvCmdFlagCheck( VM_MACHINE * core );			//
static BOOL EvCmdFlagCheckWk( VM_MACHINE * core );			//
static BOOL EvCmdFlagSetWk( VM_MACHINE * core );
static BOOL EvCmdTrainerFlagSet( VM_MACHINE * core );			//
static BOOL EvCmdTrainerFlagReset( VM_MACHINE * core );			//
static BOOL EvCmdTrainerFlagCheck( VM_MACHINE * core );			//
static BOOL EvCmdWkAdd( VM_MACHINE * core );				//
static BOOL EvCmdWkSub( VM_MACHINE * core );				//
static BOOL EvCmdLoadWkValue( VM_MACHINE * core );		//
static BOOL EvCmdLoadWkWk( VM_MACHINE * core );
static BOOL EvCmdLoadWkWkValue( VM_MACHINE * core );		//
static BOOL EvCmdTalkMsgAllPut( VM_MACHINE * core );			//
static BOOL EvCmdTalkMsgAllPutOtherArc( VM_MACHINE * core);
static BOOL EvCmdTalkMsgOtherArc( VM_MACHINE * core);
static BOOL EvCmdTalkMsgAllPutPMS( VM_MACHINE * core);
static BOOL EvCmdTalkMsgPMS( VM_MACHINE * core);
static BOOL	EvCmdTalkMsgTowerApper(VM_MACHINE* core);
static BOOL EvCmdTalkMsgNgPokeName(VM_MACHINE * core );
static BOOL EvCmdTalkMsgUnknownFont(VM_MACHINE* core );
static BOOL EvCmdTalkMsg( VM_MACHINE * core );			//
static BOOL EvCmdTalkMsgSp( VM_MACHINE * core );
static BOOL EvCmdTalkMsgSpAuto( VM_MACHINE * core );
static BOOL EvCmdTalkMsgNoSkip( VM_MACHINE * core );
static BOOL EvCmdTalkConSioMsg( VM_MACHINE * core );
static BOOL TalkMsgWait(VM_MACHINE * core);
static BOOL EvCmdABKeyWait( VM_MACHINE * core );			//
static BOOL EvWaitABKey(VM_MACHINE * core);
static BOOL EvCmdLastKeyWait( VM_MACHINE * core );			//
static BOOL EvWaitLastKey(VM_MACHINE * core);
static BOOL EvCmdNextAnmLastKeyWait( VM_MACHINE * core );			//
static BOOL EvWaitNextAnmLastKey(VM_MACHINE * core);
static BOOL EvCmdTalkWinOpen( VM_MACHINE * core );			//
static BOOL EvCmdTalkWinClose( VM_MACHINE * core );		//
static BOOL EvCmdTalkWinCloseNoClear( VM_MACHINE * core );		//
static BOOL EvCmdBoardMake( VM_MACHINE * core );
static BOOL EvCmdInfoBoardMake( VM_MACHINE * core );
static BOOL EvCmdBoardReq( VM_MACHINE * core );
static BOOL EvCmdBoardWait( VM_MACHINE * core );
static BOOL BoardReqWait( VM_MACHINE * core );
static BOOL EvCmdBoardMsg( VM_MACHINE * core );
static BOOL BoardMsgWait( VM_MACHINE * core );
static BOOL EvCmdBoardEndWait( VM_MACHINE * core );
static BOOL BoardEndWait( VM_MACHINE * core );
static BOOL EvCmdMenuReq( VM_MACHINE * core );
static BOOL EvBgScrollWait( VM_MACHINE * core );
static BOOL EvCmdBgScroll( VM_MACHINE * core );
static BOOL EvCmdYesNoWin( VM_MACHINE * core );			//
static BOOL EvYesNoSelect(VM_MACHINE * core);
static BOOL EvCmdBmpMenuInit( VM_MACHINE * core );
static BOOL EvCmdBmpMenuInitEx( VM_MACHINE * core );
static BOOL EvCmdBmpMenuMakeList( VM_MACHINE * core );
static BOOL EvCmdBmpMenuMakeList16( VM_MACHINE * core );
static BOOL EvCmdBmpMenuStart( VM_MACHINE * core );
static BOOL EvSelWinWait(VM_MACHINE * core);
static BOOL EvCmdBmpListInit( VM_MACHINE * core );
static BOOL EvCmdBmpListInitEx( VM_MACHINE * core );
static BOOL EvCmdBmpListMakeList( VM_MACHINE * core );
static BOOL EvCmdBmpListStart( VM_MACHINE * core );
static BOOL EvCmdBmpMenuHVStart( VM_MACHINE * core );
static BOOL EvCmdObjAnime( VM_MACHINE * core );			//
static BOOL EvCmdObjAnimeWait( VM_MACHINE * core );			//
static BOOL EvCmdObjPauseAll( VM_MACHINE * core );		//
static BOOL EvCmdObjPauseClearAll( VM_MACHINE * core );	//	
static BOOL EvCmdObjPause( VM_MACHINE * core );
static BOOL EvCmdObjPauseClear( VM_MACHINE * core );
static BOOL EvCmdObjAdd( VM_MACHINE * core );
static BOOL EvCmdObjDel( VM_MACHINE * core );
static BOOL EvCmdVanishDummyObjAdd( VM_MACHINE * core );
static BOOL EvCmdVanishDummyObjDel( VM_MACHINE * core );
static BOOL EvCmdObjTurn( VM_MACHINE * core );			//
static BOOL EvCmdPlayerPosGet( VM_MACHINE * core );			//
static BOOL EvCmdObjPosGet( VM_MACHINE * core );			//
static BOOL EvCmdPlayerDirGet( VM_MACHINE * core );
static BOOL EvCmdPlayerPosOffsetSet( VM_MACHINE * core );
static BOOL EvCmdNotZoneDelSet( VM_MACHINE * core );
static BOOL EvCmdMoveCodeChange( VM_MACHINE * core );
static BOOL EvCmdMoveCodeGet( VM_MACHINE * core );
static BOOL EvCmdPairObjIdSet( VM_MACHINE * core );

static BOOL EvCmdCBItemNumGet(VM_MACHINE * core);
static BOOL EvCmdCBItemNumAdd(VM_MACHINE * core);
static BOOL EvCmdUnknownFormGet(VM_MACHINE * core);
static BOOL EvCmdRevengeTrainerSearch(VM_MACHINE * core);
static BOOL EvCmdSetWeather( VM_MACHINE * core );
static BOOL EvCmdInitWeather( VM_MACHINE * core );
static BOOL EvCmdUpdateWeather( VM_MACHINE * core );
static BOOL EvCmdGetMapPosition( VM_MACHINE * core );
static BOOL EvCmdSetMapProc( VM_MACHINE * core );
static BOOL EvCmdWaitMapProcStart( VM_MACHINE * core );
static BOOL EvCmdFinishMapProc(VM_MACHINE * core);
static BOOL EvCmdWiFiAutoReg( VM_MACHINE * core );
static BOOL EvCmdWiFiP2PMatchEventCall( VM_MACHINE * core );
static BOOL EvCmdWiFiP2PMatchSetDel( VM_MACHINE * core );
static BOOL EvCmdCommGetCurrentID( VM_MACHINE * core );
static BOOL EvCmdPokeWindowPut( VM_MACHINE * core );
static void Scr_ZukanSeeSet( FIELDSYS_WORK* fsys, u16 monsno );
static BOOL EvCmdPokeWindowDel( VM_MACHINE * core );
static BOOL EvCmdBtlSearcherEventCall( VM_MACHINE * core );
static BOOL EvCmdBtlSearcherDirMvSet( VM_MACHINE * core );
static BOOL EvCmdMsgBoyEvent( VM_MACHINE * core );
static BOOL EvCmdImageClipSetProc( VM_MACHINE * core );
static BOOL EvCmdImageClipPreviewTvProc( VM_MACHINE * core );
static BOOL EvCmdImageClipPreviewConProc( VM_MACHINE * core );
static BOOL EvCmdImageClipTvSaveDataCheck( VM_MACHINE * core );
static BOOL EvCmdImageClipConSaveDataCheck( VM_MACHINE * core );
static BOOL EvCmdImageClipTvSaveTitle( VM_MACHINE * core );
static BOOL	EvCmdCustomBallEventCall( VM_MACHINE * core );
static BOOL EvCmdTMapBGSetProc( VM_MACHINE * core );
static BOOL EvCmdNutMixerProc( VM_MACHINE * core );
static BOOL EvCmdNutMixerPlayStateCheck(VM_MACHINE* core);
static BOOL EvCmdBTowerAppSetProc( VM_MACHINE * core );
static BOOL EvCmdBoxSetProc( VM_MACHINE * core );
static BOOL EvCmdOekakiBoardSetProc( VM_MACHINE * core );
static BOOL EvCmdCallTrCard( VM_MACHINE * core );
static BOOL EvCmdTradeListSetProc( VM_MACHINE * core );
static BOOL EvCmdRecordCornerSetProc( VM_MACHINE * core );
static BOOL EvCmdDendouSetProc( VM_MACHINE * core );
static BOOL EvCmdPcDendouSetProc( VM_MACHINE * core );
static BOOL EvCmdWorldTradeSetProc( VM_MACHINE * core );
static BOOL EvCmdDPWInitProc( VM_MACHINE * core );
static BOOL EvCmdFirstPokeSelectProc( VM_MACHINE * core );
static BOOL EvCmdFirstPokeSelectSetAndDel( VM_MACHINE * core );
static BOOL EvCmdNameIn( VM_MACHINE * core );
static BOOL EvCmdNameInPoke( VM_MACHINE * core );
static BOOL EvCmdNameInStone( VM_MACHINE * core );
static BOOL EvCmdWipeFadeStart( VM_MACHINE * core );
static BOOL EvCmdWipeFadeCheck( VM_MACHINE * core );
static BOOL EvWaitWipeFadeCheck(VM_MACHINE * core);
static BOOL EvCmdMapChange( VM_MACHINE * core );
static BOOL EvCmdKabeNobori( VM_MACHINE * core );
static BOOL EvCmdNaminori( VM_MACHINE * core );
static BOOL EvCmdTakinobori( VM_MACHINE * core );
static BOOL EvCmdSorawotobu( VM_MACHINE * core );
static BOOL EvCmdHidenFlash(VM_MACHINE * core);
static BOOL EvCmdHidenKiribarai(VM_MACHINE * core);
static BOOL EvCmdCutIn( VM_MACHINE * core );
static BOOL EvWaitCutIn(VM_MACHINE * core);
static BOOL EvCmdConHeroChange( VM_MACHINE * core );
static BOOL EvCmdBicycleCheck( VM_MACHINE * core );
static BOOL EvCmdBicycleReq( VM_MACHINE * core );
static BOOL EvCmdCyclingRoadSet( VM_MACHINE * core );
static BOOL EvCmdPlayerFormGet( VM_MACHINE * core );
static BOOL EvCmdPlayerReqBitOn( VM_MACHINE * core );
static BOOL EvCmdPlayerReqStart( VM_MACHINE * core );
static BOOL EvCmdFirstPokeNoGet(VM_MACHINE * core );
static BOOL EvCmdGenerateInfoGet(VM_MACHINE * core );
static BOOL EvCmdTrainerMessageSet( VM_MACHINE * core );
static BOOL EvCmdConnectSelParentWin( VM_MACHINE * core );
static BOOL EvWaitConnectSelParentWin( VM_MACHINE * core );
static BOOL EvCmdConnectSelChildWin( VM_MACHINE * core );
static BOOL EvWaitConnectSelChildWin( VM_MACHINE * core );
static BOOL EvCmdConnectDebugParentWin( VM_MACHINE * core );
static BOOL EvCmdConnectDebugChildWin( VM_MACHINE * core );
static BOOL EvCmdDebugSioEncount( VM_MACHINE * core );
static BOOL EvCmdDebugSioContest( VM_MACHINE * core );
static BOOL EvCmdSpLocationSet( VM_MACHINE * core );
static BOOL EvCmdElevatorNowFloorGet( VM_MACHINE * core );
static BOOL EvCmdElevatorFloorWrite( VM_MACHINE * core );
static BOOL EvCmdGetShinouZukanSeeNum( VM_MACHINE * core );
static BOOL EvCmdGetShinouZukanGetNum( VM_MACHINE * core );
static BOOL EvCmdGetZenkokuZukanSeeNum( VM_MACHINE * core );
static BOOL EvCmdGetZenkokuZukanGetNum( VM_MACHINE * core );
static BOOL EvCmdChkZenkokuZukan( VM_MACHINE * core );
static BOOL EvCmdGetZukanHyoukaMsgID( VM_MACHINE * core );
static BOOL EvCmdWildBattleSet( VM_MACHINE * core );
static BOOL EvCmdSpWildBattleSet( VM_MACHINE * core );
static BOOL EvCmdFirstBattleSet( VM_MACHINE * core );
static BOOL EvCmdCaptureBattleSet( VM_MACHINE * core );
static BOOL EvCmdHoneyTree( VM_MACHINE * core );
static BOOL EvCmdGetHoneyTreeState( VM_MACHINE * core );
static BOOL EvCmdHoneyTreeBattleSet( VM_MACHINE * core );
static BOOL EvCmdHoneyAfterTreeBattleSet( VM_MACHINE * core );
static BOOL EvCmdTSignSetProc( VM_MACHINE * core );
static BOOL EvCmdReportSaveCheck( VM_MACHINE * core );
static BOOL EvCmdReportSave( VM_MACHINE * core );
static BOOL EvCmdGetPoketch( VM_MACHINE * core );
static BOOL EvCmdGetPoketchFlag( VM_MACHINE * core );
static BOOL EvCmdPoketchAppAdd( VM_MACHINE * core );
static BOOL EvCmdPoketchAppCheck( VM_MACHINE * core );
static BOOL EvCmdCommTimingSyncStart( VM_MACHINE * core );
static BOOL EvWaitCommIsTimingSync( VM_MACHINE * core );
static BOOL EvCmdCommTempDataReset( VM_MACHINE * core );
static BOOL EvCmdUnionParentCardTalkNo( VM_MACHINE * core );
static BOOL EvCmdUnionGetInfoTalkNo( VM_MACHINE * core );
static BOOL EvCmdUnionBeaconChange( VM_MACHINE * core );
static BOOL EvCmdUnionConnectTalkOk( VM_MACHINE * core );
static BOOL EvCmdUnionConnectTalkDenied( VM_MACHINE * core );
static BOOL EvCmdUnionTrainerNameRegist( VM_MACHINE * core );
static BOOL EvCmdUnionReturnSetUp( VM_MACHINE * core );
static BOOL EvCmdUnionConnectCutRestart( VM_MACHINE * core );
static BOOL EvWaitCommConnectCountZero(VM_MACHINE * core);
static BOOL EvCmdUnionGetTalkNumber( VM_MACHINE * core );
static BOOL EvCmdUnionIdSet( VM_MACHINE * core );
static BOOL EvCmdUnionConnectStart( VM_MACHINE * core );
static BOOL EvCmdUnionResultGet( VM_MACHINE * core );
static BOOL EvWaitUnionResultGet(VM_MACHINE * core);
static BOOL EvCmdUnionObjAllVanish( VM_MACHINE * core );
static BOOL EvCmdUnionScriptResultSet( VM_MACHINE * core );
static BOOL EvCmdUnionParentStartCommandSet( VM_MACHINE * core );
static BOOL EvWaitUnion_ParentStartCommandSet(VM_MACHINE * core);
static BOOL EvCmdUnionChildSelectCommandSet( VM_MACHINE * core );
static BOOL EvWaitUnion_ChildSelectCommandSet(VM_MACHINE * core);
static BOOL EvCmdUnionMapChange( VM_MACHINE * core );
static BOOL EvCmdUnionViewSetUpTrainerTypeSelect( VM_MACHINE * core );
static BOOL EvCmdUnionViewGetTrainerType( VM_MACHINE * core );
static BOOL EvCmdUnionViewGetTrainerTypeNo( VM_MACHINE * core );
static BOOL EvCmdUnionViewMyStatusSet( VM_MACHINE * core );
static BOOL EvCmdUnionBattleStartCheck( VM_MACHINE * core );
static BOOL EvCmdGameOverCall( VM_MACHINE * core );
static BOOL EvCmdSetWarpId( VM_MACHINE * core );
static BOOL EvCmdGetMySex( VM_MACHINE * core );
static BOOL EvCmdPcKaifuku( VM_MACHINE * core );
static BOOL EvCmdUgManShopNpcRandomPlace( VM_MACHINE * core );
static BOOL EvCmdCommDirectEnd( VM_MACHINE * core );
static BOOL EvWaitCommDirectEnd(VM_MACHINE * core);
static BOOL EvCmdCommDirectEnterBtlRoom( VM_MACHINE * core );
static BOOL EvCmdCommPlayerSetDir( VM_MACHINE * core );
static BOOL EvCmdSxyPosChange( VM_MACHINE * core );
static BOOL EvCmdObjPosChange( VM_MACHINE * core );
static BOOL EvCmdSxyMoveCodeChange( VM_MACHINE * core );
static BOOL EvCmdSxyDirChange( VM_MACHINE * core );
static BOOL EvCmdSxyExitPosChange( VM_MACHINE * core );
static BOOL EvCmdSxyBgPosChange( VM_MACHINE * core );
static BOOL EvCmdObjDirChange( VM_MACHINE * core );
static BOOL EvCmdReturnScriptWkSet( VM_MACHINE * core );

static BOOL EvCmdSetUpDoorAnime( VM_MACHINE * core );
static BOOL EvCmdWait3DAnime( VM_MACHINE * core );
static BOOL EvCmdFree3DAnime( VM_MACHINE * core );
static BOOL EvCmdOpenDoor( VM_MACHINE * core );
static BOOL EvCmdCloseDoor( VM_MACHINE * core );
static BOOL EvCmdInitWaterGym( VM_MACHINE * core );
static BOOL EvCmdPushWaterGymButton( VM_MACHINE * core );
static BOOL EvCmdInitGhostGym( VM_MACHINE * core );
static BOOL EvCmdMoveGhostGymLift( VM_MACHINE * core );
static BOOL EvCmdInitSteelGym( VM_MACHINE * core );
static BOOL EvCmdInitCombatGym( VM_MACHINE * core );
static BOOL EvCmdInitElecGym( VM_MACHINE * core );
static BOOL EvCmdRotElecGymGear( VM_MACHINE * core );

//新規追加2006.02～
static BOOL EvCmdBagSetProc( VM_MACHINE * core );
static BOOL EvCmdBagGetResult( VM_MACHINE * core);

static BOOL EvCmdPocketCheck(VM_MACHINE * core);

static BOOL EvCmdTimeWaitIconAdd(VM_MACHINE * core);
static BOOL EvCmdTimeWaitIconDel(VM_MACHINE * core);

static BOOL EvCmdABKeyTimeWait( VM_MACHINE * core );
static BOOL EvWaitABKeyTime(VM_MACHINE * core);

static BOOL EvCmdPokeListSetProc(VM_MACHINE * core);
static BOOL EvCmdPokeListGetResult(VM_MACHINE * core);
static BOOL EvCmdNpcTradePokeListSetProc(VM_MACHINE * core);

static BOOL EvCmdConPokeStatusSetProc(VM_MACHINE * core);
static BOOL EvCmdPokeStatusGetResult(VM_MACHINE * core);

static BOOL EvCmdUgShopMenuInit( VM_MACHINE * core );
static BOOL EvWaitUgShopMenuInit( VM_MACHINE * core );
static BOOL EvCmdUgShopTalkStart( VM_MACHINE * core );
static BOOL EvWaitUgShopTalkStart( VM_MACHINE * core );
static BOOL EvCmdUgShopTalkEnd( VM_MACHINE * core );
static BOOL EvCmdUgShopTalkRegisterItemName( VM_MACHINE * core );
static BOOL EvCmdUgShopTalkRegisterTrapName( VM_MACHINE * core );
static BOOL EvCmdGuinnessWin( VM_MACHINE * core );

static BOOL EvCmdTamagoDemo( VM_MACHINE * core );

static BOOL EvCmdObjVisible( VM_MACHINE * core );
static BOOL EvCmdObjInvisible( VM_MACHINE * core );

///メールボックス用 by iwasawa
static BOOL EvCmdMailBox( VM_MACHINE * core );
static BOOL EvCmdGetMailBoxDataNum( VM_MACHINE * core );
///ギネスランキング
static BOOL EvCmdRankingView( VM_MACHINE * core );

static BOOL EvCmdGetTimeZone( VM_MACHINE * core );
static BOOL EvCmdGetRand( VM_MACHINE * core );
static BOOL EvCmdGetRandNext( VM_MACHINE * core );

static BOOL EvCmdOokisaRecordChk( VM_MACHINE * core );
static BOOL EvCmdOokisaRecordSet( VM_MACHINE * core );
static BOOL EvCmdOokisaTemotiSet( VM_MACHINE * core );
static BOOL EvCmdOokisaKirokuSet( VM_MACHINE * core );
static BOOL EvCmdOokisaKurabeInit( VM_MACHINE * core );

static BOOL EvCmdFNoteStartSet( VM_MACHINE * core );
static BOOL EvCmdFNoteDataMake( VM_MACHINE * core );
static BOOL EvCmdFNoteDataSave( VM_MACHINE * core );

static BOOL EvCmdImcAcceAddItem(VM_MACHINE * core);
static BOOL EvCmdImcAcceAddItemChk(VM_MACHINE * core);
static BOOL EvCmdImcAcceCheckItem(VM_MACHINE * core);
static BOOL EvCmdImcBgAddItem(VM_MACHINE * core);
static BOOL EvCmdImcBgCheckItem(VM_MACHINE * core);
static BOOL EvCmdUnionPokeListSetProc(VM_MACHINE * core);
static BOOL EvCmdConPokeListSetProc(VM_MACHINE * core);
static BOOL EvCmdConPokeListGetResult(VM_MACHINE * core);

static BOOL EvCmdZukanChkShinou(VM_MACHINE * core);
static BOOL EvCmdZukanChkNational(VM_MACHINE * core);
static BOOL EvCmdZukanRecongnizeShinou(VM_MACHINE * core);
static BOOL EvCmdZukanRecongnizeNational(VM_MACHINE * core);

static BOOL EvCmdUrayamaEncountSet(VM_MACHINE * core);
static BOOL EvCmdUrayamaEncountNoChk(VM_MACHINE * core);

static BOOL EvCmdPaperplaneSet(VM_MACHINE * core);

static BOOL EvCmdRecordInc(VM_MACHINE* core);
static BOOL EvCmdRecordGet(VM_MACHINE* core);
static BOOL EvCmdRecordSet(VM_MACHINE* core);

static BOOL EvCmdDebugWatch(VM_MACHINE * core);

static BOOL EvCmdGetBeforeZoneID( VM_MACHINE * core);
static BOOL EvCmdGetNowZoneID( VM_MACHINE * core);
static BOOL EvCmdSafariControl( VM_MACHINE * core);

static BOOL EvCmdColosseumMapChangeIn( VM_MACHINE * core);
static BOOL EvCmdColosseumMapChangeOut( VM_MACHINE * core);

static BOOL EvCmdWifiEarthSetProc( VM_MACHINE * core );

static BOOL EvCmdCallSafariScope( VM_MACHINE * core );

static BOOL EvCmdMsgAutoGet(VM_MACHINE * core);

static BOOL	EvCmdClimaxDemoCall(VM_MACHINE * core);			//クライマックスデモ

static BOOL EvCmdInitSafariTrain(VM_MACHINE * core);		//サファリ電車初期化
static BOOL EvCmdMoveSafariTrain(VM_MACHINE * core);		//サファリ電車移動
static BOOL EvCmdCheckSafariTrain(VM_MACHINE * core);		//サファリ電車チェック

static BOOL EvCmdPlayerHeightValid(VM_MACHINE * core);

static BOOL EvCmdUnderGroundTalkCount(VM_MACHINE * core);
static BOOL EvCmdUnderGroundTalkCountClear(VM_MACHINE * core);

static BOOL EvCmdGetNewsPokeNo(VM_MACHINE * core);
static BOOL EvCmdNewsCountSet(VM_MACHINE * core);
static BOOL EvCmdNewsCountChk(VM_MACHINE * core);

static BOOL EvCmdStartGenerate(VM_MACHINE * core);
static BOOL EvCmdAddMovePoke(VM_MACHINE * core);

static BOOL EvCmdFldTradeAlloc(VM_MACHINE * core);
static BOOL EvCmdFldTradeMonsno(VM_MACHINE * core);
static BOOL EvCmdFldTradeChgMonsno(VM_MACHINE * core);
static BOOL EvCmdFldTradeEvent(VM_MACHINE * core);
static BOOL EvCmdFldTradeDel(VM_MACHINE * core);
static BOOL EvCmdZukanTextVerUp(VM_MACHINE * core);
static BOOL EvCmdZukanSexVerUp(VM_MACHINE * core);
static BOOL EvCmdZenkokuZukanFlag(VM_MACHINE * core);

static BOOL EvCmdChkPrmExp(VM_MACHINE * core);
static BOOL EvCmdChkWeek(VM_MACHINE * core);

static BOOL EvCmdRegulationListCall(VM_MACHINE * core);
static BOOL EvCmdAshiatoChk(VM_MACHINE * core);
static BOOL EvCmdPcRecoverAnm(VM_MACHINE * core);
static BOOL EvCmdElevatorAnm(VM_MACHINE * core);

static BOOL EvCmdCallShipDemo(VM_MACHINE * core);

static BOOL EvCmdPMSInputSingleProc(VM_MACHINE * core);
static BOOL EvCmdPMSInputDoubleProc(VM_MACHINE * core);
static BOOL EvCmdPMSBuf(VM_MACHINE * core);

static BOOL EvCmdPMVersionGet(VM_MACHINE * core);

static BOOL EvCmdAikotobaKabegamiSet(VM_MACHINE * core);
static BOOL EvCmdGetUgHataNum(VM_MACHINE * core);

static BOOL EvCmdSetUpPasoAnime( VM_MACHINE * core );
static BOOL EvCmdStartPasoOnAnime(VM_MACHINE * core);
static BOOL EvCmdStartPasoOffAnime(VM_MACHINE * core);

static BOOL EvCmdNickNamePC(VM_MACHINE * core);

static BOOL EvCmdPokeBoxCountEmptySpace(VM_MACHINE * core);

static BOOL EvCmdReportDrawProcSet( VM_MACHINE * core );
static BOOL EvCmdReportDrawProcDel( VM_MACHINE * core );

static BOOL EvCmdDendouBallAnm(VM_MACHINE * core);

static BOOL EvCmdInitFldLift(VM_MACHINE * core);
static BOOL EvCmdMoveFldLift(VM_MACHINE * core);
static BOOL EvCmdCheckFldLift(VM_MACHINE * core);

static BOOL EvCmdSetupRAHCyl(VM_MACHINE * core);
static BOOL EvCmdStartRAHCyl(VM_MACHINE * core);

static BOOL EvCmdAddScore(VM_MACHINE * core);

static BOOL EvCmdPartyMonsNoCheck(VM_MACHINE * core);
static BOOL EvCmdPartyDeokisisuFormChange(VM_MACHINE * core);
static BOOL EvCmdCheckMinomuchiComp( VM_MACHINE * core );

static BOOL EvCmdPoketchHookSet( VM_MACHINE * core );
static BOOL EvCmdPoketchHookReset( VM_MACHINE * core );

static BOOL EvCmdSlotMachine( VM_MACHINE * core );
static BOOL EvCmdGetNowHour( VM_MACHINE * core );

static BOOL EvCmdObjShakeAnm( VM_MACHINE * core );
static BOOL EvCmdObjBlinkAnm( VM_MACHINE * core );
static BOOL EvCmd_D20R0106Legend_IsUnseal( VM_MACHINE * core );

static BOOL EvCmdDressingImcAcceCheck(VM_MACHINE * core);
static BOOL EvCmdAgbCartridgeVerGet( VM_MACHINE * core );
static BOOL EvCmdHideMapStateChange( VM_MACHINE * core );

static BOOL EvCmdImcBgNameSet( VM_MACHINE * core );
static BOOL EvCmdSlotRentyanChk( VM_MACHINE * core );
static BOOL EvCmdLevelJijiiNo(VM_MACHINE * core);
static BOOL EvCmdImcAcceSubItem(VM_MACHINE * core);
static BOOL	EvCmdc08r0801ScopeCameraSet( VM_MACHINE * core );
static BOOL EvCmdLevelJijiiInit(VM_MACHINE * core);
static BOOL EvCmdNewNankaiWordSet(VM_MACHINE * core);
static BOOL EvCmdRegularCheck( VM_MACHINE * core );
static BOOL EvCmdNankaiWordCompleteCheck(VM_MACHINE * core);
static BOOL EvCmdBirthDayCheck(VM_MACHINE * core);
static BOOL EvCmdAnoonSeeNum( VM_MACHINE * core );
static BOOL EvCmdD17SystemMapSelect(VM_MACHINE * core);
static BOOL EvCmdUnderGroundToolGiveCount(VM_MACHINE * core);
static BOOL EvCmdUnderGroundKasekiDigCount(VM_MACHINE * core);
static BOOL EvCmdUnderGroundTrapHitCount(VM_MACHINE * core);
static BOOL EvCmdPofinAdd( VM_MACHINE * core );
static BOOL EvCmdPofinAddCheck( VM_MACHINE * core );
static BOOL EvCmdIsHaihuEventEnable(VM_MACHINE *core);
static BOOL EvCmdPokeWindowPutPP( VM_MACHINE * core );
static BOOL EvCmdPokeWindowAnm( VM_MACHINE * core );
static BOOL EvCmdPokeWindowAnmWait( VM_MACHINE * core );
static BOOL EvWaitPokeWindowAnmWait(VM_MACHINE * core);
static BOOL EvCmdDendouNumGet( VM_MACHINE * core );
static BOOL EvCmdGetRandomHit( VM_MACHINE * core );

static BOOL EvCmdSodateyaPokeListSetProc(VM_MACHINE * core);
static BOOL EvCmdSodateyaPokeListGetResult(VM_MACHINE * core);

static BOOL EvCmdHidenEffStart(VM_MACHINE * core);

static BOOL EvCmdUnderGroundTalkCount2(VM_MACHINE * core);
static BOOL EvCmdZishin( VM_MACHINE * core );
static BOOL EvCmdObjAnimePos(VM_MACHINE * core);
static BOOL EvCmdUgBallCheck(VM_MACHINE * core);
static BOOL EvCmdCheckMyGSID(VM_MACHINE * core);
static BOOL EvCmdGetFriendDataNum(VM_MACHINE * core);
static BOOL EvCmdAusuItemCheck(VM_MACHINE * core);
static BOOL EvCmdAikotobaOkurimonoChk(VM_MACHINE * core);
static BOOL EvCmdCBSealKindNumGet(VM_MACHINE * core);
static BOOL EvCmdWifiHusiginaokurimonoOpenFlagSet(VM_MACHINE * core);
static BOOL EvCmdUnionGetCardTalkNo( VM_MACHINE * core );
static BOOL EvCmdWirelessIconEasy( VM_MACHINE * core );
static BOOL EvCmdWirelessIconEasyEnd( VM_MACHINE * core );
static BOOL EvCmdSaveFieldObj( VM_MACHINE * core );
static BOOL EvCmdTalkObjPauseAll( VM_MACHINE * core );
static BOOL EvCmdSetEscapeLocation(VM_MACHINE* core);
static BOOL EvCmdFieldObjBitSetFellowHit( VM_MACHINE * core );
static BOOL EvSelUnionWinWait(VM_MACHINE * core);
static BOOL EvCmdUnionBmpMenuStart( VM_MACHINE * core );
static BOOL EvCmdCommDirectEndTiming( VM_MACHINE * core );
static BOOL EvCmdGetCardRank( VM_MACHINE * core );
static BOOL EvCmdBicycleReqNonBgm( VM_MACHINE * core );
/*  */

static BOOL EvCmdReportInfoWinOpen( VM_MACHINE * core );
static BOOL EvCmdReportInfoWinClose( VM_MACHINE * core );

static BOOL EvCmdFieldScopeModeSet( VM_MACHINE * core );

//============================================================================================
//
//	グローバル変数
//
//============================================================================================
//条件分岐用テーブル
static const u8 ConditionTable[6][3] =
{
//	  MINUS  EQUAL  PLUS
	{ TRUE,	 FALSE, FALSE },	// LT
	{ FALSE, TRUE,  FALSE },	// EQ
	{ FALSE, FALSE, TRUE  },	// GT
	{ TRUE,  TRUE,  FALSE },	// LE
	{ FALSE, TRUE,  TRUE  },	// GE
	{ TRUE,  FALSE, TRUE  }		// NE
};

static const BMPWIN_DAT YesNoBmpDat = {
	FLD_MBGFRM_FONT, FLD_YESNO_WIN_PX, FLD_YESNO_WIN_PY,
	FLD_YESNO_WIN_SX, FLD_YESNO_WIN_SY, FLD_YESNO_WIN_PAL, FLD_YESNO_WIN_CGX
};

const VM_CMD ScriptCmdTbl[] = {
	EvCmdNop,				
	EvCmdDummy,				
	EvCmdEnd,			
	EvCmdTimeWait,			//

	EvCmdLoadRegValue,
	EvCmdLoadRegWData,
	EvCmdLoadRegAdrs,
	EvCmdLoadAdrsValue,
	EvCmdLoadAdrsReg,
	EvCmdLoadRegReg,
	EvCmdLoadAdrsAdrs,		//10

	EvCmdCmpRegReg,
	EvCmdCmpRegValue,
	EvCmdCmpRegAdrs,		
	EvCmdCmpAdrsReg,		
	EvCmdCmpAdrsValue,
	EvCmdCmpAdrsAdrs,
	EvCmdCmpWkValue,
	EvCmdCmpWkWk,

	EvCmdVMMachineAdd,		//
	EvCmdChangeCommonScr,	//20
	EvCmdChangeLocalScr,	// 

	EvCmdGlobalJump,		//
	EvCmdObjIDJump,
	EvCmdBgIDJump,
	EvCmdPlayerDirJump,

	EvCmdGlobalCall,		//
	EvCmdRet,				//

	EvCmdIfJump,			//
	EvCmdIfCall,

	EvCmdFlagSet,			//30
	EvCmdFlagReset,
	EvCmdFlagCheck,
	EvCmdFlagCheckWk,
	EvCmdFlagSetWk,

	EvCmdTrainerFlagSet,
	EvCmdTrainerFlagReset,
	EvCmdTrainerFlagCheck,

	EvCmdWkAdd,
	EvCmdWkSub,

	EvCmdLoadWkValue,		//40
	EvCmdLoadWkWk,
	EvCmdLoadWkWkValue,

	EvCmdTalkMsgAllPut,		//
	EvCmdTalkMsg,			//
	EvCmdTalkMsgSp,			//
	EvCmdTalkMsgNoSkip,		//
	EvCmdTalkConSioMsg,		//
	EvCmdABKeyWait,			//
	EvCmdLastKeyWait,		//
	EvCmdNextAnmLastKeyWait,//
	EvCmdTalkWinOpen,		//50
	EvCmdTalkWinClose,		//
	EvCmdTalkWinCloseNoClear,//

	EvCmdBoardMake,			//看板作成（タウンマップ、標識、表札）
	EvCmdInfoBoardMake,		//看板作成（掲示板）
	EvCmdBoardReq,			//看板制御リクエスト
	EvCmdBoardWait,
	EvCmdBoardMsg,			//看板メッセージ表示
	EvCmdBoardEndWait,
	EvCmdMenuReq,			//メニューリクエスト
	EvCmdBgScroll,			//60

	EvCmdYesNoWin,			//
	EvCmdGuinnessWin,

	EvCmdBmpMenuInit,
	EvCmdBmpMenuInitEx,
	EvCmdBmpMenuMakeList,
	EvCmdBmpMenuStart,

	EvCmdBmpListInit,
	EvCmdBmpListInitEx,
	EvCmdBmpListMakeList,
	EvCmdBmpListStart,		//70

	EvCmdBmpMenuHVStart,

	EvCmdSePlay,			//
	EvCmdSeStop,			//
	EvCmdSeWait,
	EvCmdVoicePlay,			//
	EvCmdVoicePlayWait,		//
	EvCmdMePlay,
	EvCmdMeWait,
	EvCmdBgmPlay,
	EvCmdBgmStop,			//80
	EvCmdBgmNowMapPlay,
	EvCmdBgmSpecialSet,		//
	EvCmdBgmFadeOut,
	EvCmdBgmFadeIn,
	EvCmdBgmPlayerPause,
	EvCmdPlayerFieldDemoBgmPlay,
	EvCmdCtrlBgmFlagSet,
	EvCmdPerapDataCheck,
	EvCmdPerapRecStart,
	EvCmdPerapRecStop,		//90
	EvCmdPerapSave,
	EvCmdSndClimaxDataLoad,

	EvCmdObjAnime,			//
	EvCmdObjAnimeWait,		//
	EvCmdObjPauseAll,		//
	EvCmdObjPauseClearAll,	//
	EvCmdObjPause,			//
	EvCmdObjPauseClear,		//
	EvCmdObjAdd,			//
	EvCmdObjDel,			//

	EvCmdVanishDummyObjAdd,	//100
	EvCmdVanishDummyObjDel,	//

	EvCmdObjTurn,			//102
	EvCmdPlayerPosGet,		//
	EvCmdObjPosGet,			//
	EvCmdPlayerPosOffsetSet,

	EvCmdNotZoneDelSet,		//
	EvCmdMoveCodeChange,	//
	EvCmdPairObjIdSet,	//

	EvCmdAddGold,			//お金関連すべて
	EvCmdSubGold,
	EvCmdCompGold,
	EvCmdGoldWinWrite,
	EvCmdGoldWinDel,
	EvCmdGoldWrite,			//お金関連ここまで

	EvCmdCoinWinWrite,		//コイン関連すべて
	EvCmdCoinWinDel,
	EvCmdCoinWrite,
	EvCmdCheckCoin,
	EvCmdAddCoin,
	EvCmdSubCoin,			//コイン関連ここまで

	EvCmdAddItem,			
	EvCmdSubItem,
	EvCmdAddItemChk,
	EvCmdCheckItem,
	EvCmdWazaMachineItemNoCheck,

	EvCmdGetPocketNo,
	EvCmdAddPCBoxItem,		//※使用せず
	EvCmdCheckPCBoxItem,	//※使用せず。アイテム関連ここまで

	EvCmdAddGoods,			//グッズ関連すべて
	EvCmdSubGoods,
	EvCmdAddGoodsChk,
	EvCmdCheckGoods,		//グッズ関連ここまで

	EvCmdAddTrap,			//罠関連すべて
	EvCmdSubTrap,
	EvCmdAddTrapChk,
	EvCmdCheckTrap,			//罠関連ここまで

	EvCmdAddTreasure,			//お宝関連すべて
	EvCmdSubTreasure,
	EvCmdAddTreasureChk,
	EvCmdCheckTreasure,			//お宝罠関連ここまで

	EvCmdAddTama,			//タマ関連すべて
	EvCmdSubTama,
	EvCmdAddTamaChk,
	EvCmdCheckTama,			//タマ関連ここまで

	EvCmdCBItemNumGet,
	EvCmdCBItemNumAdd,
	EvCmdUnknownFormGet,

	EvCmdAddPokemon,		//ポケモン関連すべて
	EvCmdAddTamago,
	EvCmdChgPokeWaza,
	EvCmdChkPokeWaza,
	EvCmdChkPokeWazaGroup,		//ポケモン関連ここまで

	EvCmdRevengeTrainerSearch,

	EvCmdSetWeather,		//天候関連すべて			未対応
	EvCmdInitWeather,
	EvCmdUpdateWeather,		//天候関連ここまで

	EvCmdGetMapPosition,	//現在のマップ位置を取得	未対応
	EvCmdGetTemotiPokeNum,	//別命令があるのでいらない

	EvCmdSetMapProc,

	EvCmdWiFiAutoReg,
	EvCmdWiFiP2PMatchEventCall,
	EvCmdWiFiP2PMatchSetDel,
	EvCmdMsgBoyEvent,
	EvCmdImageClipSetProc,
	EvCmdImageClipPreviewTvProc,
	EvCmdImageClipPreviewConProc,
	EvCmdCustomBallEventCall,
	EvCmdTMapBGSetProc,
	EvCmdBoxSetProc,
	EvCmdOekakiBoardSetProc,
	EvCmdCallTrCard,
	EvCmdTradeListSetProc,
	EvCmdRecordCornerSetProc,
	EvCmdDendouSetProc,
	EvCmdPcDendouSetProc,
	EvCmdWorldTradeSetProc,
	EvCmdDPWInitProc,

	EvCmdFirstPokeSelectProc,
	EvCmdFirstPokeSelectSetAndDel,

	EvCmdEyeTrainerMoveSet,
	EvCmdEyeTrainerMoveCheck,
	EvCmdEyeTrainerTypeGet,
	EvCmdEyeTrainerIdGet,
	EvCmdNameIn,
	EvCmdNameInPoke,

	EvCmdWipeFadeStart,
	EvCmdWipeFadeCheck,

	EvCmdMapChange,
	EvCmdKabeNobori,
	EvCmdNaminori,
	EvCmdTakinobori,
	EvCmdSorawotobu,
	EvCmdHidenFlash,
	EvCmdHidenKiribarai,
	EvCmdCutIn,
	EvCmdConHeroChange,
	EvCmdBicycleCheck,
	EvCmdBicycleReq,
	EvCmdCyclingRoadSet,

	EvCmdPlayerFormGet,
	EvCmdPlayerReqBitOn,
	EvCmdPlayerReqStart,

	EvCmdPlayerName,
	EvCmdRivalName,
	EvCmdSupportName,
	EvCmdPokemonName,
	EvCmdItemName,
	EvCmdPocketName,
	EvCmdItemWazaName,
	EvCmdWazaName,
	EvCmdNumberName,
	EvCmdNickName,
	EvCmdPoketchName,
	EvCmdTrTypeName,
	EvCmdMyTrTypeName,
	EvCmdPokemonNameExtra,
	EvCmdFirstPokemonName,
	EvCmdRivalPokemonName,
	EvCmdSupportPokemonName,
	EvCmdFirstPokeNoGet,
	EvCmdGoodsName,
	EvCmdTrapName,
	EvCmdTamaName,
	EvCmdZoneName,
	EvCmdGenerateInfoGet,
	EvCmdTrainerIdGet,
	EvCmdTrainerBattleSet,
	EvCmdTrainerMessageSet,
	EvCmdTrainerTalkTypeGet,
	EvCmdRevengeTrainerTalkTypeGet,
	EvCmdTrainerTypeGet,
	EvCmdTrainerBgmSet,
	EvCmdTrainerLose,
	EvCmdTrainerLoseCheck,
	EvCmdSeacretPokeRetryCheck,
	EvCmd2vs2BattleCheck,
	EvCmdDebugBattleSet,
	EvCmdDebugTrainerFlagSet,
	EvCmdDebugTrainerFlagOnJump,

	EvCmdConnectSelParentWin,
	EvCmdConnectSelChildWin,
	EvCmdConnectDebugParentWin,
	EvCmdConnectDebugChildWin,

	EvCmdDebugSioEncount,
	EvCmdDebugSioContest,

	EvCmdConSioTimingSend,
	EvCmdConSioTimingCheck,
	EvCmdConSystemCreate,
	EvCmdConSystemExit,
	EvCmdConJudgeNameGet,
	EvCmdConBreederNameGet,
	EvCmdConNickNameGet,
	EvCmdConNumTagSet,
	EvCmdConSioParamInitSet,
	EvCmdContestProc,
	EvCmdConRankNameGet,
	EvCmdConTypeNameGet,
	EvCmdConVictoryBreederNameGet,
	EvCmdConVictoryItemNoGet,
	EvCmdConVictoryNickNameGet,
	EvCmdConRankingCheck,
	EvCmdConVictoryEntryNoGet,
	EvCmdConMyEntryNoGet,
	EvCmdConObjCodeGet,
	EvCmdConPopularityGet,
	EvCmdConDeskModeGet,
	EvCmdConHaveRibbonCheck,
	EvCmdConRibbonNameGet,
	EvCmdConAcceNoGet,
	EvCmdConEntryParamGet,
	EvCmdConCameraFlashSet,
	EvCmdConCameraFlashCheck,
	EvCmdConHBlankStop,
	EvCmdConHBlankStart,
	EvCmdConEndingSkipCheck,
	EvCmdConRecordDisp,
	EvCmdConMsgPrintFlagSet,
	EvCmdConMsgPrintFlagReset,

	EvCmdChkTemotiPokerus,
	EvCmdTemotiPokeSexGet,

	EvCmdSpLocationSet,
	EvCmdElevatorNowFloorGet,
	EvCmdElevatorFloorWrite,

	EvCmdGetShinouZukanSeeNum,
	EvCmdGetShinouZukanGetNum,
	EvCmdGetZenkokuZukanSeeNum,
	EvCmdGetZenkokuZukanGetNum,
	EvCmdChkZenkokuZukan,
	EvCmdGetZukanHyoukaMsgID,

	EvCmdWildBattleSet,
	EvCmdFirstBattleSet,
	EvCmdCaptureBattleSet,

	EvCmdHoneyTree,
	EvCmdGetHoneyTreeState,
	EvCmdHoneyTreeBattleSet,
	EvCmdHoneyAfterTreeBattleSet,

	EvCmdTSignSetProc,

	EvCmdReportSaveCheck,
	EvCmdReportSave,

	EvCmdImageClipTvSaveDataCheck,
	EvCmdImageClipConSaveDataCheck,
	EvCmdImageClipTvSaveTitle,

	EvCmdGetPoketch,
	EvCmdGetPoketchFlag,
	EvCmdPoketchAppAdd,
	EvCmdPoketchAppCheck,

	EvCmdCommTimingSyncStart,
	EvCmdCommTempDataReset,

	EvCmdUnionParentCardTalkNo,
	EvCmdUnionGetInfoTalkNo,
	EvCmdUnionBeaconChange,

	EvCmdUnionConnectTalkDenied,
	EvCmdUnionConnectTalkOk,

	EvCmdUnionTrainerNameRegist,
	EvCmdUnionReturnSetUp,
	EvCmdUnionConnectCutRestart,
	EvCmdUnionGetTalkNumber,
	EvCmdUnionIdSet,
	EvCmdUnionResultGet,
	EvCmdUnionObjAllVanish,
	EvCmdUnionScriptResultSet,
	EvCmdUnionParentStartCommandSet,
	EvCmdUnionChildSelectCommandSet,
	EvCmdUnionConnectStart,

	EvCmdShopCall,
	EvCmdFixShopCall,
	EvCmdFixGoodsCall,
	EvCmdFixSealCall,

	EvCmdGameOverCall,

	EvCmdSetWarpId,
	EvCmdGetMySex,
	EvCmdPcKaifuku,

	EvCmdUgManShopNpcRandomPlace,
	EvCmdCommDirectEnd,
	EvCmdCommDirectEnterBtlRoom,
	EvCmdCommPlayerSetDir,

	EvCmdUnionMapChange,
	EvCmdUnionViewSetUpTrainerTypeSelect,
	EvCmdUnionViewGetTrainerType,
	EvCmdUnionViewMyStatusSet,

	EvCmdSysFlagZukanGet,
	EvCmdSysFlagZukanSet,
	EvCmdSysFlagShoesGet,
	EvCmdSysFlagShoesSet,
	EvCmdSysFlagBadgeGet,
	EvCmdSysFlagBadgeSet,
	EvCmdSysFlagBadgeCount,
	EvCmdSysFlagBagGet,
	EvCmdSysFlagBagSet,
	EvCmdSysFlagPairGet,
	EvCmdSysFlagPairSet,
	EvCmdSysFlagPairReset,
	EvCmdSysFlagOneStepGet,
	EvCmdSysFlagOneStepSet,
	EvCmdSysFlagOneStepReset,
	EvCmdSysFlagGameClearGet,
	EvCmdSysFlagGameClearSet,

	EvCmdSetUpDoorAnime,
	EvCmdWait3DAnime,
	EvCmdFree3DAnime,
	EvCmdOpenDoor,
	EvCmdCloseDoor,

	EvCmdGetSodateyaName,
	EvCmdGetSodateyaZiisan,
	
	EvCmdInitWaterGym,			//水ジム初期化
	EvCmdPushWaterGymButton,	//水ジムボタンプッシュ
	EvCmdInitGhostGym,			//ゴーストジム初期化
	EvCmdMoveGhostGymLift,		//ゴーストジムリフトムーブ
	EvCmdInitSteelGym,			//鋼ジム初期化
	EvCmdInitCombatGym,			//格闘ジム初期化
	EvCmdInitElecGym,			//電気ジム
	EvCmdRotElecGymGear,		//電気ジムギミックギア
	
	EvCmdGetPokeCount,			//手持ちポケモン数取得

	EvCmdBagSetProc,			//バッグ画面呼び出し
	EvCmdBagGetResult,			//バッグ画面結果取り出し

	EvCmdPocketCheck,			//ポケットの中にどうぐがあるかチェック
	EvCmdNutsName,				//きのみタグの名前
	EvCmdSeikakuName,			//性格の名前

	EvCmdSeedGetStatus,			//木の実：状態取得
	EvCmdSeedGetType,
	EvCmdSeedGetCompost,
	EvCmdSeedGetGroundStatus,
	EvCmdSeedGetNutsCount,

	EvCmdSeedSetCompost,
	EvCmdSeedSetNuts,
	EvCmdSeedSetWater,
	EvCmdSeedTakeNuts,

	EvCmdSxyPosChange,
	EvCmdObjPosChange,
	EvCmdSxyMoveCodeChange,
	EvCmdSxyDirChange,
	EvCmdSxyExitPosChange,
	EvCmdSxyBgPosChange,
	EvCmdObjDirChange,

	EvCmdTimeWaitIconAdd,
	EvCmdTimeWaitIconDel,

	EvCmdReturnScriptWkSet,
	EvCmdABKeyTimeWait,

	EvCmdPokeListSetProc,
	EvCmdUnionPokeListSetProc,
	EvCmdPokeListGetResult,

	EvCmdConPokeListSetProc,
	EvCmdConPokeListGetResult,

	EvCmdConPokeStatusSetProc,
	EvCmdPokeStatusGetResult,

	EvCmdTemotiMonsNo,
	EvCmdMonsOwnChk,

	EvCmdGetPokeCount2,			//手持ちポケモン数取得
	EvCmdGetPokeCount3,			//手持ちポケモン数取得
	EvCmdGetPokeCount4,			//手持ちポケモン数取得
	EvCmdGetTamagoCount,		//手持ちタマゴ数取得

	EvCmdUgShopMenuInit,		//地下のお店　メニューを開く
	EvCmdUgShopTalkStart,		//地下のお店　会話開始
	EvCmdUgShopTalkEnd,			//地下のお店　会話終了
	EvCmdUgShopTalkRegisterItemName,	//地下のお店　アイテムの名前をお店の会話に登録
	EvCmdUgShopTalkRegisterTrapName,	//地下のお店　罠の名前をお店の会話に登録

	EvCmdSubMyGold,				//育てや関連一式
	EvCmdHikitoriPoke,
	EvCmdHikitoriList,			//060625 使用しません
	EvCmdMsgSodateyaAishou,		//060625 使用しません
	EvCmdMsgExpandBuf,			//060625 使用しません
	EvCmdDelSodateyaEgg,
	EvCmdGetSodateyaEgg,
	EvCmdHikitoriRyoukin,
	EvCmdCompMyGold,
	EvCmdTamagoDemo,
	EvCmdSodateyaPokeList,		//060625 使用しません
	EvCmdSodatePokeLevelStr,
	EvCmdMsgAzukeSet,
	EvCmdSetSodateyaPoke,

	EvCmdObjVisible,			//OBJ表示、不表示
	EvCmdObjInvisible,

	EvCmdMailBox,				///<メールボックス呼び出し
	EvCmdGetMailBoxDataNum,		///<メールボックス内のデータ数を取得
	EvCmdRankingView,			///<ギネスホールランキングView

	EvCmdGetTimeZone,
	EvCmdGetRand,				//ランダム取得
	EvCmdGetRandNext,			//ランダム取得
	EvCmdGetNatsuki,			//なつき度取得
	EvCmdAddNatsuki,			//なつき度増やす
	EvCmdSubNatsuki,			//なつき度減らす
	EvCmdHikitoriListNameSet,		//引き取りポケモン名をセット

	EvCmdPlayerDirGet,

	EvCmdGetSodateyaAishou,		//そだてや：2体の相性ゲット
	EvCmdGetSodateyaTamagoCheck,	//そだてや：たまごがうまれているか

	EvCmdTemotiPokeChk,
	EvCmdOokisaRecordChk,
	EvCmdOokisaRecordSet,
	EvCmdOokisaTemotiSet,
	EvCmdOokisaKirokuSet,
	EvCmdOokisaKurabeInit,

	EvCmdWazaListSetProc,
	EvCmdWazaListGetResult,
	EvCmdWazaCount,
	EvCmdWazaDel,
	EvCmdTemotiWazaNo,
	EvCmdTemotiWazaName,

	EvCmdFNoteStartSet,
	EvCmdFNoteDataMake,
	EvCmdFNoteDataSave,

	EvCmdSysFlagKairiki,
	EvCmdSysFlagFlash,
	EvCmdSysFlagKiribarai,

	EvCmdImcAcceAddItem,
	EvCmdImcAcceAddItemChk,
	EvCmdImcAcceCheckItem,
	EvCmdImcBgAddItem,
	EvCmdImcBgCheckItem,
	
	EvCmdNutMixerProc,
	EvCmdNutMixerPlayStateCheck,
	EvCmdBTowerAppSetProc,
	
	EvCmdBattleTowerWorkClear,
	EvCmdBattleTowerWorkInit,
	EvCmdBattleTowerWorkRelease,
	EvCmdBattleTowerTools,
	EvCmdBattleTowerGetSevenPokeData,
	EvCmdBattleTowerIsPrizeGet,
	EvCmdBattleTowerIsPrizemanSet,
	EvCmdBattleTowerSendBuf,
	EvCmdBattleTowerRecvBuf,
	EvCmdBattleTowerGetLeaderRoomID,
	EvCmdBattleTowerIsLeaderDataExist,
	EvCmdRecordInc,
	EvCmdRecordGet,
	EvCmdRecordSet,

	EvCmdZukanChkShinou,
	EvCmdZukanChkNational,
	EvCmdZukanRecongnizeShinou,
	EvCmdZukanRecongnizeNational,

	EvCmdUrayamaEncountSet,
	EvCmdUrayamaEncountNoChk,

	EvCmdPokeMailChk,
	EvCmdPaperplaneSet,
	EvCmdPokeMailDel,
	EvCmdKasekiCount,
	EvCmdItemListSetProc,			//※使用していません。
	EvCmdItemListGetResult,			//※使用していません。
	EvCmdItemNoToMonsNo,
	EvCmdKasekiItemNo,

	EvCmdPokeLevelChk,

	EvCmdApprovePoisonDead,			//どく気絶チェック

	EvCmdFinishMapProc,				//フィールドマッププロセス終了

	EvCmdDebugWatch,				//デバッグ用ワーク内容表示（デバッガのコマンドラインへ）

	EvCmdTalkMsgAllPutOtherArc,		//TALKMSG_ALLPUTアーカイブ指定あり
	EvCmdTalkMsgOtherArc,			//TALKMSG_ALLPUTアーカイブ指定あり
	EvCmdTalkMsgAllPutPMS,			//簡易会話パラメータ
	EvCmdTalkMsgPMS,				//簡易会話パラメータ
	EvCmdTalkMsgTowerApper,			//バトルタワー対戦前メッセージ
	EvCmdTalkMsgNgPokeName,			//タワーNGポケモン名展開

	EvCmdGetBeforeZoneID,
	EvCmdGetNowZoneID,

	EvCmdSafariControl,				//Safari制御コマンド

	EvCmdColosseumMapChangeIn,
	EvCmdColosseumMapChangeOut,

	EvCmdWifiEarthSetProc,
	EvCmdCallSafariScope,			//サファリ望遠鏡コール	

	EvCmdCommGetCurrentID,

	EvCmdPokeWindowPut,
	EvCmdPokeWindowDel,
	EvCmdBtlSearcherEventCall,
	EvCmdBtlSearcherDirMvSet,

	EvCmdMsgAutoGet,				//簡単メッセージ表示

	EvCmdClimaxDemoCall,			//クライマックスデモ

	EvCmdInitSafariTrain,			//サファリ電車初期化
	EvCmdMoveSafariTrain,			//サファリ電車移動
	EvCmdCheckSafariTrain,			//サファリ電車チェック

	EvCmdPlayerHeightValid,			//自機高さ取得有無

	EvCmdGetPokeSeikaku,
	EvCmdChkPokeSeikakuAll,
	EvCmdUnderGroundTalkCount,

	EvCmdNaturalParkWalkCountClear,
	EvCmdNaturalParkWalkCountGet,
	EvCmdNaturalParkAccessoryNoGet,

	EvCmdGetNewsPokeNo,
	EvCmdNewsCountSet,
	EvCmdNewsCountChk,
	EvCmdStartGenerate,
	EvCmdAddMovePoke,

	EvCmdRandomGroup,				//ランダムグループ関連

	EvCmdOshieWazaCount,
	EvCmdRemaindWazaCount,
	EvCmdOshieWazaListSetProc,
	EvCmdRemaindWazaListSetProc,
	EvCmdOshieWazaListGetResult,
	EvCmdRemaindWazaListGetResult,
	EvCmdNormalWazaListSetProc,
	EvCmdNormalWazaListGetResult,

	EvCmdFldTradeAlloc,
	EvCmdFldTradeMonsno,
	EvCmdFldTradeChgMonsno,
	EvCmdFldTradeEvent,
	EvCmdFldTradeDel,
	EvCmdZukanTextVerUp,
	EvCmdZukanSexVerUp,
	EvCmdZenkokuZukanFlag,

	EvCmdChkRibbonCount,
	EvCmdChkRibbonCountAll,
	EvCmdChkRibbon,
	EvCmdSetRibbon,
	EvCmdRibbonName,
	EvCmdChkPrmExp,

	EvCmdChkWeek,

	EvCmdBroadcastTV,
	EvCmdTVEntryWatchHideItem,
	EvCmdTVInterview,
	EvCmdTVInterviewerCheck,

	EvCmdRegulationListCall,

	EvCmdAshiatoChk,
	EvCmdPcRecoverAnm,
	EvCmdElevatorAnm,

	EvCmdCallShipDemo,

	EvCmdMysteryPostMan,			//ふしぎな贈り物配達員

	EvCmdDebugPrintWork,
	EvCmdDebugPrintFlag,
	EvCmdDebugPrintWorkStationed,
	EvCmdDebugPrintFlagStationed,

	EvCmdPMSInputSingleProc,		//簡易会話入力（単語一つ）
	EvCmdPMSInputDoubleProc,		//簡易会話入力（単語二つ）
	EvCmdPMSBuf,					//簡易会話の単語メッセージをバッファへ

	EvCmdPMVersionGet,

	EvCmdFrontPokemon,
	EvCmdTemotiPokeType,
	EvCmdAikotobaKabegamiSet,
	EvCmdGetUgHataNum,

	EvCmdSetUpPasoAnime,
	EvCmdStartPasoOnAnime,
	EvCmdStartPasoOffAnime,

	EvCmdGetKujiAtariNum,
	EvCmdKujiAtariChk,
	EvCmdKujiAtariInit,
	EvCmdNickNamePC,

	EvCmdPokeBoxCountEmptySpace,
	EvCmdPokeParkControl,
	EvCmdPokeParkDepositCount,
	EvCmdPokeParkTransMons,
	EvCmdPokeParkGetScore,

	EvCmdAcceShopCall,

	EvCmdReportDrawProcSet,
	EvCmdReportDrawProcDel,

	EvCmdDendouBallAnm,

	EvCmdInitFldLift,
	EvCmdMoveFldLift,
	EvCmdCheckFldLift,

	EvCmdSetupRAHCyl,
	EvCmdStartRAHCyl,

	EvCmdAddScore,
	EvCmdAcceName,

	EvCmdPartyMonsNoCheck,			// パーティに引数１のポケモンがいるかチェック
	EvCmdPartyDeokisisuFormChange,	// パーティ内のデオキシスのフォルムを変更

	EvCmdCheckMinomuchiComp,	// ミノムッチ3種そろったか

	EvCmdPoketchHookSet,
	EvCmdPoketchHookReset,

	EvCmdSlotMachine,

	EvCmdGetNowHour,
	
	EvCmdObjShakeAnm,
	EvCmdObjBlinkAnm,
	EvCmd_D20R0106Legend_IsUnseal,

	EvCmdDressingImcAcceCheck,
	EvCmdTalkMsgUnknownFont,		//アンノーンフォントでメッセージ出力
	EvCmdAgbCartridgeVerGet,	// ささっているAGBカートリッジVer取得

	EvCmdUnderGroundTalkCountClear,

	EvCmdHideMapStateChange,	//隠しマップチェンジ
	EvCmdNameInStone,			//石碑名前入力呼び出し
	EvCmdMonumantName,		//石碑名タグ展開

	EvCmdImcBgNameSet,		// イメージクリップ背景名をバッファに設定
	EvCmdCompCoin,
	EvCmdSlotRentyanChk,	//スロットレンチャンチェック
	EvCmdAddCoinChk,
	EvCmdLevelJijiiNo,
	EvCmdPokeLevelGet,
	EvCmdImcAcceSubItem,
	EvCmdc08r0801ScopeCameraSet,
	EvCmdLevelJijiiInit,

	EvCmdTVEntryParkInfo,

	EvCmdNewNankaiWordSet,
	
	EvCmdRegularCheck,
	EvCmdNankaiWordCompleteCheck,
	EvCmdNumberNameEx,		//数字タグ展開ディスプレイモード指定版
	EvCmdTemotiPokeContestStatusGet,
	EvCmdBirthDayCheck,
	EvCmdSndInitialVolSet,
	EvCmdAnoonSeeNum,
	EvCmdD17SystemMapSelect,	//戻らずの洞窟マップ抽選
	EvCmdUnderGroundToolGiveCount,
	EvCmdUnderGroundKasekiDigCount,
	EvCmdUnderGroundTrapHitCount,
	EvCmdPofinAdd,
	EvCmdPofinAddCheck,
	EvCmdIsHaihuEventEnable,

	EvCmdPokeWindowPutPP,
	EvCmdPokeWindowAnm,
	EvCmdPokeWindowAnmWait,
	EvCmdDendouNumGet,
	EvCmdSodateyaPokeListSetProc,
	EvCmdSodateyaPokeListGetResult,
	EvCmdGetRandomHit,
	EvCmdUnderGroundTalkCount2,
	//バトルポイント関連ここから
	EvCmdBtlPointWinWrite,
	EvCmdBtlPointWinDel,
	EvCmdBtlPointWrite,
	EvCmdCheckBtlPoint,
	EvCmdAddBtlPoint,
	EvCmdSubBtlPoint,
	EvCmdCompBtlPoint,
	EvCmdGetBtlPointGift,
//	EvCmdBmpMenuMakeListEx,
	//バトルポイント関連ここまで
	
	EvCmdUnionViewGetTrainerTypeNo,

	EvCmdBmpMenuMakeList16,

	EvCmdHidenEffStart,
	EvCmdZishin,

	EvCmdTrainerMultiBattleSet,

	EvCmdObjAnimePos,

	EvCmdUgBallCheck,
	EvCmdCheckMyGSID,
	EvCmdGetFriendDataNum,
	EvCmdNpcTradePokeListSetProc,

	EvCmdGetCoinGift,
	EvCmdAusuItemCheck,

	EvCmdSubWkCoin,
	EvCmdCompWkCoin,
	EvCmdAikotobaOkurimonoChk,
	EvCmdCBSealKindNumGet,
	EvCmdWifiHusiginaokurimonoOpenFlagSet,

	EvCmdMoveCodeGet,

	EvCmdBgmPlayCheck,
	EvCmdUnionGetCardTalkNo,

	EvCmdWirelessIconEasy,
	EvCmdWirelessIconEasyEnd,
	EvCmdSaveFieldObj,
	EvCmdSealName,
	EvCmdTalkObjPauseAll,
	EvCmdSetEscapeLocation,

	EvCmdFieldObjBitSetFellowHit,

	EvCmdDameTamagoChkAll,

	EvCmdTVEntryWatchChangeName,

	EvCmdUnionBmpMenuStart,
	EvCmdUnionBattleStartCheck,
	EvCmdCommDirectEndTiming,
	EvCmdHaifuPokeRetryCheck,
	EvCmdSpWildBattleSet,
	EvCmdGetCardRank,
	EvCmdBicycleReqNonBgm,
	
	EvCmdTalkMsgSpAuto,

	EvCmdReportInfoWinOpen,
	EvCmdReportInfoWinClose,

	EvCmdFieldScopeModeSet,
};


//--------------------------------------------------------------------------------------------
///	スクリプトコマンドの最大数
//--------------------------------------------------------------------------------------------
const u32 ScriptCmdMax = NELEMS(ScriptCmdTbl);

//============================================================================================
//
//	基本システム命令
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * ＮＯＰ命令（なにもしない）
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdNop( VM_MACHINE * core )
{
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 何もしない（デバッガで引っ掛けるための命令）
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdDummy( VM_MACHINE * core )
{
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * スクリプトの終了
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdEnd( VM_MACHINE * core )
{
	VM_End( core );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ウェイト処理
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdTimeWait( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	u16 num				= VMGetU16( core );
	u16 wk_id			= VMGetU16( core );
	u16* ret_wk			= GetEventWorkAdrs( fsys, wk_id );

	*ret_wk = num;

	//仮想マシンの汎用レジスタにワークのIDを格納
	core->reg[0] = wk_id;

	VM_SetWait( core, EvWaitTime );
	return 1;
}

//return 1 = 終了
static BOOL EvWaitTime(VM_MACHINE * core)
{
	FIELDSYS_WORK* fsys = core->fsys;
	u16* ret_wk = GetEventWorkAdrs( fsys, core->reg[0] );	//注意！

	(*ret_wk)--;
	if( *ret_wk == 0 ){ 
		return 1;
	}
	return 0;
}

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
static BOOL EvCmdDebugWatch(VM_MACHINE * core)
{
	u16 value = VMGetWorkValue(core);
	OS_Printf("SCR WORK: %d\n", value);
	return 0;
}

//============================================================================================
//
//	データロード・ストア関連
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * 仮想マシンの汎用レジスタに1byteの値を格納
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdLoadRegValue( VM_MACHINE * core )
{
	u8	r = VMGetU8( core );
	core->reg[r] = VMGetU8( core );

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 仮想マシンの汎用レジスタに4byteの値を格納
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdLoadRegWData( VM_MACHINE * core )
{
	u8	r;
	u32	wdata;

	r = VMGetU8( core );
	wdata = VMGetU32( core );
	core->reg[r] = wdata;
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 仮想マシンの汎用レジスタにアドレスを格納
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdLoadRegAdrs( VM_MACHINE * core )
{
	u8	r;
	VM_CODE * adrs;

	r = VMGetU8( core );
	adrs = (VM_CODE *)VMGetU32( core );
	core->reg[r] = *adrs;

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * アドレスの中身に値を代入
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdLoadAdrsValue( VM_MACHINE * core )
{
	VM_CODE * adrs;
	u8	r;

	adrs = (VM_CODE *)VMGetU32( core );
	r = VMGetU8( core );
	*adrs = r;

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * アドレスの中身に仮想マシンの汎用レジスタの値を代入
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdLoadAdrsReg( VM_MACHINE * core )
{
	VM_CODE * adrs;
	u8	r;

	adrs = (VM_CODE *)VMGetU32( core );
	r = VMGetU8( core) ;
	*adrs = core->reg[r];

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 仮想マシンの汎用レジスタの値を汎用レジスタにコピー
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdLoadRegReg( VM_MACHINE * core )
{
	u8	r1, r2;

	r1 = VMGetU8( core );
	r2 = VMGetU8( core );
	core->reg[r1] = core->reg[r2];

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * アドレスの中身にアドレスの中身を代入
 *  
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdLoadAdrsAdrs( VM_MACHINE * core )
{
	VM_CODE * adr1;
	VM_CODE * adr2;

	adr1 = (VM_CODE *)VMGetU32( core );
	adr2 = (VM_CODE *)VMGetU32( core );
	*adr1 = * adr2;

	return 0;
}


//============================================================================================
//
//	比較命令
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * ２つの値を比較
 *
 * @param	r1		値１
 * @param	r2		値２
 *
 * @retval	"r1 < r2 : MISUS_RESULT"
 * @retval	"r1 = r2 : EQUAL_RESULT"
 * @retval	"r1 > r2 : PLUS_RESULT"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdCmpMain( u16 r1, u16 r2 )
{
	if( r1 < r2 ){
		return MINUS_RESULT;
	}else if( r1 == r2 ){
		return EQUAL_RESULT;
	}
	return PLUS_RESULT;
}

//--------------------------------------------------------------------------------------------
/**
 * 仮想マシンの汎用レジスタを比較
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdCmpRegReg( VM_MACHINE * core )
{
	u8	r1, r2;

	r1 = core->reg[ VMGetU8(core) ];
	r2 = core->reg[ VMGetU8(core) ];
	core->cmp_flag = EvCmdCmpMain( r1, r2 );

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 仮想マシンの汎用レジスタと値を比較
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdCmpRegValue( VM_MACHINE * core )
{
	u8	r1, r2;

	r1 = core->reg[ VMGetU8(core) ];
	r2 = VMGetU8(core);
	core->cmp_flag = EvCmdCmpMain( r1, r2 );

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 仮想マシンの汎用レジスタとアドレスの中身を比較
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdCmpRegAdrs( VM_MACHINE * core )
{
	u8	r1, r2;

	r1 = core->reg[ VMGetU8(core) ];
	r2 = *(VM_CODE *)VMGetU32(core);
	core->cmp_flag = EvCmdCmpMain( r1, r2 );

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * アドレスの中身と仮想マシンの汎用レジスタを比較
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdCmpAdrsReg( VM_MACHINE * core )
{
	u8	r1, r2;

	r1 = *(VM_CODE *)VMGetU32(core);
	r2 = core->reg[ VMGetU8(core) ];
	core->cmp_flag = EvCmdCmpMain(r1,r2);

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * アドレスの中身と値を比較
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdCmpAdrsValue(VM_MACHINE * core)
{
	u8 r1,r2;

	r1 = *(VM_CODE *)VMGetU32(core);
	r2 = VMGetU8(core);
	core->cmp_flag = EvCmdCmpMain(r1,r2);

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * アドレスの中身とアドレスの中身を比較
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdCmpAdrsAdrs(VM_MACHINE * core)
{
	u8 r1,r2;

	r1 = *(VM_CODE *)VMGetU32(core);
	r2 = *(VM_CODE *)VMGetU32(core);
	core->cmp_flag = EvCmdCmpMain(r1,r2);

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ワークと値を比較
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdCmpWkValue( VM_MACHINE * core )
{
	u16 * wk;
	u16	r1, r2;

	wk = VMGetWork( core );
	r1 = *wk;
	r2 = VMGetU16( core );
	core->cmp_flag = EvCmdCmpMain( r1, r2 );

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ワークとワークを比較
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdCmpWkWk( VM_MACHINE * core )
{
	u16 * wk1;
	u16 * wk2;

	wk1 = VMGetWork( core );
	wk2 = VMGetWork( core );
	core->cmp_flag = EvCmdCmpMain( *wk1, *wk2 );

	return 0;
}

//============================================================================================
//
//	仮想マシン関連
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * 仮想マシン追加(切り替えはせず、並列で動作します！)
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdVMMachineAdd( VM_MACHINE * core )
{
	u16 id;
	FIELDSYS_WORK* fsys		= core->fsys;
	u8* vm_machine_count	= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_VM_MACHINE_COUNT );
	VM_MACHINE** vm			= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_VM_SUB1 );

	id = VMGetU16(core);

	//仮想マシン追加
	//*vm = VMMachineAdd(fsys, id, &ScriptCmdTbl[0], &ScriptCmdTbl[EVCMD_MAX]);
	*vm = VMMachineAdd(fsys, id);
	(*vm_machine_count)++;

	//イベントと切り離したTCB動作にするかも？
	//*vm = VMMachineAddTCB( fsys, id, &ScriptCmdTbl[0], &ScriptCmdTbl[EVCMD_MAX] );

	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * ローカルスクリプトをウェイト状態にして、共通スクリプトを動作させます
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdChangeCommonScr( VM_MACHINE * core )
{
	u16 scr_id;
	FIELDSYS_WORK* fsys		= core->fsys;
	u8* common_scr_flag		= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_COMMON_SCR_FLAG );
	u8* vm_machine_count	= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_VM_MACHINE_COUNT );
	VM_MACHINE** vm			= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_VM_SUB1 );

	scr_id = VMGetU16(core);

	//共通スクリプト以外にも切り替え可能になっている！

	//共通スクリプト切り替えフラグON
	*common_scr_flag = 1;

	//仮想マシン追加
	//*vm = VMMachineAdd(fsys, scr_id, &ScriptCmdTbl[0], &ScriptCmdTbl[EVCMD_MAX]);
	*vm = VMMachineAdd(fsys, scr_id);
	(*vm_machine_count)++;

	VM_SetWait( core, EvChangeCommonScrWait );
	return 1;
}

//return 1 = 終了
static BOOL EvChangeCommonScrWait(VM_MACHINE * core)
{
	FIELDSYS_WORK* fsys = core->fsys;
	u8* common_scr_flag = GetEvScriptWorkMemberAdrs(fsys,ID_EVSCR_COMMON_SCR_FLAG);

	if( *common_scr_flag == 0 ){
		return 1;
	}

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 共通スクリプトを終了して、ローカルスクリプトを再開させます
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdChangeLocalScr( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	u8* common_scr_flag = GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_COMMON_SCR_FLAG );

	//共通スクリプト切り替えフラグOFF
	*common_scr_flag = 0;

	//VM_End( core );
	return 0;	//注意！　この後に"END"に行くようにする
}


//============================================================================================
//
//	分岐命令
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * スクリプトジャンプ
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 *
 * @li	EVCMD_JUMP
 *
 *	表記：	EVCMD_JUMP	JumpOffset(s16)
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdGlobalJump( VM_MACHINE * core )
{
	s32	pos;
	pos = (s32)VMGetU32(core);
	VMJump( core, (VM_CODE *)(core->PC+pos) );	//JUMP
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 話し掛け対象OBJID比較ジャンプ
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdObjIDJump( VM_MACHINE * core )
{
	u8 id;
	s32	pos;
	FIELD_OBJ_PTR* fldobj;
	FIELDSYS_WORK* fsys = core->fsys;

	//話し掛け対象OBJ
	fldobj = GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_TARGET_OBJ );

	//比較する値
	id = VMGetU8(core);
	
	//飛び先
	pos = (s32)VMGetU32(core);

	//話し掛け対象OBJと、比較する値が同じか
	if( FieldOBJ_OBJIDGet(*fldobj) == id ){
		VMJump( core, (VM_CODE *)(core->PC+pos) );	//JUMP
	}
	
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 話し掛け対象BG比較ジャンプ
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdBgIDJump( VM_MACHINE * core )
{
	u8 id;
	s32	pos;
	//u32 *targetbg;
	u32 targetbg;

	//話し掛け対象BG
	targetbg = Event_GetTargetBg( core->event_work );

	//比較する値
	id = VMGetU8(core);
	
	//飛び先
	pos = (s32)VMGetU32(core);

	//話し掛け対象BGと、比較する値が同じか
	//if( *targetbg == id ){
	if( targetbg == id ){
		VMJump( core, (VM_CODE *)(core->PC+pos) );	//JUMP
	}
	
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * イベント起動時の主人公の向き比較ジャンプ
 * (現在の向きではないので注意！)
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdPlayerDirJump( VM_MACHINE * core )
{
	u8 dir;
	s32	pos;
	int* player_dir;
	FIELDSYS_WORK* fsys = core->fsys;

	player_dir = GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_PLAYER_DIR );

	//比較する値
	dir = VMGetU8(core);
	
	//飛び先
	pos = (s32)VMGetU32(core);

	if( *player_dir == dir ){
		VMJump( core, (VM_CODE *)(core->PC+pos) );	//JUMP
	}
	
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * スクリプトコール
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 *
 * @li	EVCMD_CALL
 *
 *	表記：	EVCMD_CALL	CallOffset(s16)
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdGlobalCall( VM_MACHINE * core )
{
	s32	pos = (s32)VMGetU32(core);
	VMCall( core, (VM_CODE *)(core->PC+pos) );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * スクリプトリターン
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdRet( VM_MACHINE * core )
{
	VMRet( core );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * スクリプト条件ジャンプ
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdIfJump( VM_MACHINE * core )
{
	u8	r;
	s32	pos;

	r   = VMGetU8(core);
	pos = (s32)VMGetU32(core);

	if( ConditionTable[r][core->cmp_flag] == TRUE ){
		VMJump( core, (VM_CODE *)(core->PC+pos) );
	}
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * スクリプト条件コール
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdIfCall( VM_MACHINE * core )	
{
	u8	r;
	s32	pos;

	r   = VMGetU8(core);
	pos = (s32)VMGetU32(core);

	if( ConditionTable[r][core->cmp_flag] == TRUE ){
		VMCall( core, (VM_CODE *)(core->PC+pos) );
	}
	return 0;
}


//============================================================================================
//
//	イベントフラグ関連
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * フラグのセット
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdFlagSet( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	u16	flag = VMGetU16( core );
	SetEventFlag( fsys, flag );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * フラグのリセット
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdFlagReset( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	u16	flag = VMGetU16( core );
	ResetEventFlag( fsys, flag );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * フラグのチェック
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdFlagCheck( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	u16	flag = VMGetU16( core );
	core->cmp_flag = CheckEventFlag( fsys, flag );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ワークの値をフラグナンバーとしてフラグチェック
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdFlagCheckWk( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	u16* wk				= VMGetWork( core );
	u16* ret_wk			= VMGetWork( core );

	*ret_wk = CheckEventFlag( fsys, (*wk) );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ワークの値をフラグナンバーとしてフラグセット
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdFlagSetWk( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	u16* wk				= VMGetWork( core );
	SetEventFlag( fsys, (*wk) );
	return 0;
}


//============================================================================================
//
//	トレーナーフラグ関連
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * トレーナーフラグのセット(トレーナーIDを渡す)
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdTrainerFlagSet( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	u16 flag = VMGetWorkValue(core);	//トレーナーIDを渡す！　ワークナンバーを渡すのはダメ！
	SetEventFlagTrainer( fsys, flag );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * トレーナーフラグのリセット(トレーナーIDを渡す)
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdTrainerFlagReset( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	u16 flag = VMGetWorkValue(core);	//トレーナーIDを渡す！　ワークナンバーを渡すのはダメ！
	ResetEventFlagTrainer( fsys, flag );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * トレーナーフラグのチェック(トレーナーIDを渡す)
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdTrainerFlagCheck( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	u16 flag = VMGetWorkValue(core);	//トレーナーIDを渡す！　ワークナンバーを渡すのはダメ！
	core->cmp_flag = CheckEventFlagTrainer( fsys, flag );
	return 0;
}


//============================================================================================
//
//	ワーク操作関連
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * ワークに値を足す
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdWkAdd( VM_MACHINE * core )
{
	u16 * work;
	u16 num;
	work = VMGetWork( core );
	*work += VMGetWorkValue( core );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ワークから値を引く
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdWkSub( VM_MACHINE * core )
{
	u16 * work;
	work = VMGetWork( core );
	*work -= VMGetWorkValue( core );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ワークに値を格納
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdLoadWkValue( VM_MACHINE * core )
{
	u16 * work;

	work = VMGetWork( core );
	*work = VMGetU16( core );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ワークにワークの値を格納
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdLoadWkWk( VM_MACHINE * core )
{
	u16 * wk1;
	u16 * wk2;

	wk1 = VMGetWork( core );
	wk2 = VMGetWork( core );
	*wk1 = *wk2;
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ワークに値かワークの値を格納
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdLoadWkWkValue( VM_MACHINE * core )
{
	u16 * work;

	work = VMGetWork( core );
	*work = VMGetWorkValue( core );
	return 0;
}


//============================================================================================
//
//	メッセージ・ウィンドウ関連
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * 登録された単語を使って文字列展開　メッセージ表示(MSG_ALLPUT版)
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdTalkMsgAllPut( VM_MACHINE * core )
{
	u8 msg_id = VMGetU8(core);
	TalkMsgAllPut(core, core->msgman, msg_id);
	return 0;
}
//--------------------------------------------------------------------------------------------
/**
 * 登録された単語を使って文字列展開　メッセージ表示(MSG_ALLPUT版)
 * MSGアーカイブも指定するバージョン
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 *
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdTalkMsgAllPutOtherArc( VM_MACHINE * core)
{
	MSGDATA_MANAGER * man;
	u16 arc_id = VMGetWorkValue(core);
	u16 msg_id = VMGetWorkValue(core);

	man = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, arc_id, HEAPID_EVENT );
	TalkMsgAllPut(core, man, msg_id);
	MSGMAN_Delete(man);
	return 0;
}
//--------------------------------------------------------------------------------------------
/**
 * 登録された単語を使って文字列展開　メッセージ表示
 * MSGアーカイブも指定するバージョン
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdTalkMsgOtherArc( VM_MACHINE * core)
{
	MSGDATA_MANAGER * man;
	u16 arc_id = VMGetWorkValue(core);
	u16 msg_id = VMGetWorkValue(core);

	man = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, arc_id, HEAPID_EVENT );
	ScrTalkMsg(core, man, msg_id,1, NULL);
	MSGMAN_Delete(man);
	
	VM_SetWait( core, TalkMsgWait );
	return 1;
}

/**
 *	@brief	簡易会話パラメータからメッセージデータを生成＆表示(ALL_PUT)
 */
static BOOL EvCmdTalkMsgAllPutPMS(VM_MACHINE* core)
{
	u16 stype = VMGetU16(core);
	u16	sid = VMGetU16(core);
	u16	word0 = VMGetU16(core);
	u16	word1 = VMGetU16(core);

	TalkMsgPMSParam(core,stype,sid,word0,word1,0xFF);
	return 0;
}

/**
 *	@brief	簡易会話パラメータからメッセージデータを生成＆表示
 */
static BOOL EvCmdTalkMsgPMS(VM_MACHINE* core)
{
	u16 stype = VMGetU16(core);
	u16	sid = VMGetU16(core);
	u16	word0 = VMGetU16(core);
	u16	word1 = VMGetU16(core);

	TalkMsgPMSParam(core,stype,sid,word0,word1,1);
	VM_SetWait( core, TalkMsgWait );
	return 1;
}
/**
 *	@brief	バトルタワー対戦前メッセージ専用表示
 */
static BOOL	EvCmdTalkMsgTowerApper(VM_MACHINE* core)
{
	u16	*msg;
	BTOWER_SCRWORK* wk;
	MSGDATA_MANAGER * man;
	u16	tr_idx = VMGetU8(core);	//一人目か二人目か？

	wk = core->fsys->btower_wk;
	if(wk == NULL){
		return 0;
	}

	msg = wk->tr_data[tr_idx].bt_trd.appear_word;

	if(msg[0] == 0xFFFF){	//ROMMSG
		man = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG,
				NARC_msg_tower_trainer_dat, HEAPID_EVENT );
		ScrTalkMsg(core, man,msg[1], 1, NULL);
		MSGMAN_Delete(man);
	}else{	//簡易会話
		TalkMsgPMSParam(core,msg[0],msg[1],msg[2],msg[3],1);
	}
	VM_SetWait( core, TalkMsgWait );
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * タワーに参加できないポケモンで見たことのあるポケモン名をタグ展開してメッセージ表示
 * (見たことがあるポケモン名だけ展開、見たことがないものはNULL文字列展開)
 *
 * 展開数がスクリプト専用のWORDSET登録数より多いので、自前で用意
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdTalkMsgNgPokeName(VM_MACHINE * core )
{
	FIELDSYS_WORK * fsys	= core->fsys;
	u8	msg_id				= VMGetU8(core);
	u16	pokenum				= VMGetWorkValue(core);
	u16 sex					= VMGetU16(core);
	u8 flag					= VMGetU8(core);
	u8	num;
	WORDSET*	wset;
	
	//タグ展開
	num = 0;
	wset = BtlTower_SetNgPokeName(fsys->savedata,pokenum,sex,flag,&num);
	TalkMsgExtraWordSet(core,wset,msg_id+num,1);
	WORDSET_Delete(wset);

	VM_SetWait( core, TalkMsgWait );
	return 1;
}


//------------------------------------------------------------------
/**
 * アンノーンフォントでメッセージ出力
 *
 * @param   core		
 *
 * @retval  BOOL		
 */
//------------------------------------------------------------------
static BOOL EvCmdTalkMsgUnknownFont( VM_MACHINE* core )
{
	SCR_TALK_EX_PARAM  exParam;
	u16 msgID = VMGetU16( core );

	ScrTalk_InitExParam( &exParam, core );
	exParam.font = FONT_UNKNOWN;

	ScrTalkMsg( core, core->msgman, msgID, FALSE, &exParam );
	VM_SetWait( core, TalkMsgWait );

	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * 登録された単語を使って文字列展開　メッセージ表示
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	常に1
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdTalkMsg( VM_MACHINE * core )
{
	u8 msg_id = VMGetU8(core);							//1byte
	ScrTalkMsg( core, core->msgman, (u8)msg_id, 1, NULL );
	VM_SetWait( core, TalkMsgWait );
	return 1;
}

static BOOL TalkMsgWait(VM_MACHINE * core)
{
	FIELDSYS_WORK * fsys = core->fsys;
	u8* msg_index = GetEvScriptWorkMemberAdrs(fsys,ID_EVSCR_MSGINDEX);
	return FldTalkMsgEndCheck( *msg_index );
}

//--------------------------------------------------------------------------------------------
/**
 * 登録された単語を使って文字列展開　メッセージ表示(特殊：メッセージIDをワーク指定可能)
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	常に1
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdTalkMsgSp( VM_MACHINE * core )
{
	u16 msg_id = VMGetWorkValue(core);					//2byte
	OS_TPrintf("MSG SP=%d\n",msg_id);
	ScrTalkMsg( core, core->msgman, (u8)msg_id, 1, NULL );
	VM_SetWait( core, TalkMsgWait );
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * 登録された単語を使って文字列展開　オートメッセージ表示(特殊：メッセージIDをワーク指定可能)
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	常に1
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdTalkMsgSpAuto( VM_MACHINE * core )
{
	u16 msg_id     = VMGetWorkValue(core);					//2byte
//	CONFIG *config = SaveData_GetConfig( core->fsys->savedata );	
	SCR_TALK_EX_PARAM ex_param;

	ScrTalk_InitExParam( &ex_param, core );
//	ex_param.msg_speed = CONFIG_GetMsgSpeed( config );
	ex_param.auto_flag = MSG_AUTO_ON;
	
	OS_TPrintf("MSG SP AUTO=%d speed = %d\n",msg_id, ex_param.msg_speed);
	ScrTalkMsg( core, core->msgman, (u8)msg_id, 1, &ex_param );
	VM_SetWait( core, TalkMsgWait );
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * 登録された単語を使って文字列展開　メッセージ表示(キースキップ不可)
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	常に1
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdTalkMsgNoSkip( VM_MACHINE * core )
{
	u16 msg_id = VMGetWorkValue(core);					//2byte
	ScrTalkMsg( core, core->msgman, (u8)msg_id, 0, NULL );
	VM_SetWait( core, TalkMsgWait );
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	メッセージ表示：SCRIDをMSGIDとみなして表示
 * @param	core		仮想マシン制御構造体へのポインタ
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdMsgAutoGet( VM_MACHINE * core)
{
	FIELD_OBJ_PTR *fldobj = GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_TARGET_OBJ );
	u8 msg_id = FieldOBJ_EventTypeGet(*fldobj);
	ScrTalkMsg( core, core->msgman, (u8)msg_id, 1, NULL );
	VM_SetWait( core, TalkMsgWait );
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * コンテスト用：登録された単語を使って文字列展開　メッセージ表示
 * ※通信、非通信でメッセージ送りの設定が変わります。
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	常に1
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdTalkConSioMsg( VM_MACHINE * core )
{
	u8 msg_id = VMGetU8(core);							//1byte
	
	if(CommIsInitialize() == FALSE){
		ScrTalkMsg( core, core->msgman, msg_id, 1, NULL );
	}
	else{
		SCR_TALK_EX_PARAM ex_param;
		ScrTalk_InitExParam( &ex_param, core );
		ex_param.msg_speed = CONTEST_SIO_MSG_SPEED;
		ex_param.auto_flag = MSG_AUTO_ON;
		ScrTalkMsg( core, core->msgman, msg_id, 0, &ex_param );
	}
	VM_SetWait( core, TalkMsgWait );
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * キーウェイト
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	常に1
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdABKeyWait( VM_MACHINE * core )
{
	VM_SetWait( core, EvWaitABKey );
	return 1;
}

//return 1 = 終了
static BOOL EvWaitABKey(VM_MACHINE * core)
{
	if( sys.trg & ( PAD_BUTTON_DECIDE | PAD_BUTTON_CANCEL ) ){
		return 1;
	}

	return 0;
}
//--------------------------------------------------------------------------------------------
/**
 * キーウェイト or 時間待ち
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	常に1
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdABKeyTimeWait( VM_MACHINE * core )
{
	core->reg[0] = VMGetWorkValue(core);
	VM_SetWait( core, EvWaitABKeyTime );
	return 1;
}

//キーor時間待ち
static BOOL EvWaitABKeyTime(VM_MACHINE * core)
{
	//if (sys.trg & (PAD_BUTTON_A | PAD_BUTTON_B)) {
	if (sys.trg & (PAD_BUTTON_DECIDE | PAD_BUTTON_CANCEL)) {
		return 1;
	}
	core->reg[0] --;
	if (core->reg[0] == 0) {
		return 1;
	}
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * イベントの最後のキーウェイト
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	常に1
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdLastKeyWait( VM_MACHINE * core )
{
	VM_SetWait( core, EvWaitLastKey );
	return 1;
}

//return 1 = 終了
static BOOL EvWaitLastKey(VM_MACHINE * core)
{
	//通常終了
	//if( sys.trg & ( PAD_BUTTON_A | PAD_BUTTON_B ) ){
	if( sys.trg & ( PAD_BUTTON_DECIDE | PAD_BUTTON_CANCEL ) ){
		return 1;
	}

#if 1
	//十字キー、スタートボタンのリクエスト処理をする
	if( sys.trg & PAD_KEY_UP ){
		Player_DirSet( core->fsys->player, DIR_UP );
	}else if( sys.trg & PAD_KEY_DOWN ){
		Player_DirSet( core->fsys->player, DIR_DOWN );
	}else if( sys.trg & PAD_KEY_LEFT ){
		Player_DirSet( core->fsys->player, DIR_LEFT );
	}else if( sys.trg & PAD_KEY_RIGHT ){
		Player_DirSet( core->fsys->player, DIR_RIGHT );
	}else if( sys.trg & PAD_BUTTON_X ){
		SetEvScriptNextFunc( core->fsys );
	}else{
		return 0;
	}

	return 1;
#else
	return 0;
#endif
}

//--------------------------------------------------------------------------------------------
/**
 * イベントの最後のキーウェイト(その後にアニメが続く時に使用)
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	常に1
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdNextAnmLastKeyWait( VM_MACHINE * core )
{
	VM_SetWait( core, EvWaitNextAnmLastKey );
	return 1;
}

//return 1 = 終了
static BOOL EvWaitNextAnmLastKey(VM_MACHINE * core)
{
	//if( sys.trg & ( PAD_BUTTON_A | PAD_BUTTON_B ) ){
	if( sys.trg & ( PAD_BUTTON_DECIDE | PAD_BUTTON_CANCEL ) ){
		return 1;
	}

	//十字キーでもメッセージ送り
	if( sys.trg & ( PAD_KEY_UP | PAD_KEY_DOWN | PAD_KEY_LEFT | PAD_KEY_RIGHT ) ){
		return 1;
	}

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 会話ウィンドウを開く
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdTalkWinOpen( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	u8* win_open_flag	= GetEvScriptWorkMemberAdrs( fsys,ID_EVSCR_WIN_OPEN_FLAG );

	FldTalkBmpAdd(fsys->bgl, GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_MSGWINDAT ),FLD_MBGFRM_FONT);
	FieldTalkWinPut( GetEvScriptWorkMemberAdrs(fsys,ID_EVSCR_MSGWINDAT),
						SaveData_GetConfig(core->fsys->savedata) );
	*win_open_flag = 1;	//ON;
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 会話ウィンドウを閉じる
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdTalkWinClose( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	GF_BGL_BMPWIN* pMsgWinDat = GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_MSGWINDAT );
	u8* win_open_flag	= GetEvScriptWorkMemberAdrs( fsys,ID_EVSCR_WIN_OPEN_FLAG );

	BmpTalkWinClear( pMsgWinDat, WINDOW_TRANS_ON );
	GF_BGL_BmpWinDel( pMsgWinDat );
	*win_open_flag = 0;	//OFF
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 会話ウィンドウを閉じる(クリアなし)
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdTalkWinCloseNoClear( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	GF_BGL_BMPWIN* pMsgWinDat = GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_MSGWINDAT );
	u8* win_open_flag	= GetEvScriptWorkMemberAdrs( fsys,ID_EVSCR_WIN_OPEN_FLAG );

	//BmpTalkWinClear( pMsgWinDat, WINDOW_TRANS_ON );
	GF_BGL_BmpWinDel( pMsgWinDat );
	*win_open_flag = 0;	//OFF
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * BGスクロール
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 *
 * REG	0-3
 * TMP	0,1
 * を使用しているので注意！
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdBgScroll( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	u16* reg0			= GetEvScriptWorkMemberAdrs( fsys,ID_EVSCR_WK_REG0 );
	u16* tmp0			= GetEvScriptWorkMemberAdrs( fsys,ID_EVSCR_WK_TEMP0 );
	u16* reg1			= GetEvScriptWorkMemberAdrs( fsys,ID_EVSCR_WK_REG1 );
	u16* reg2			= GetEvScriptWorkMemberAdrs( fsys,ID_EVSCR_WK_REG2 );
	u16* tmp1			= GetEvScriptWorkMemberAdrs( fsys,ID_EVSCR_WK_TEMP1 );
	u16* reg3			= GetEvScriptWorkMemberAdrs( fsys,ID_EVSCR_WK_REG3 );

	*reg0 = VMGetU8(core);	//Xスクロール値
	*tmp0 = VMGetU8(core);	//Xカウンタ
	*reg1 = VMGetU8(core);	//Xスクロール方向

	*reg2 = VMGetU8(core);	//Yスクロール値
	*tmp1 = VMGetU8(core);	//Yカウンタ
	*reg3 = VMGetU8(core);	//Yスクロール方向

	VM_SetWait( core, EvBgScrollWait );

	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * BGスクロール終了待ち
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @retval	"0 = 動作中"
 * @retval	"1 = 終了"
 *
 * REG	0-3
 * TMP	0,1
 * を使用しているので注意！
 */
//--------------------------------------------------------------------------------------------
static BOOL EvBgScrollWait( VM_MACHINE * core )
{
	FIELDSYS_WORK * fsys = core->fsys;

	u16* scroll_x	= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WK_REG0 );
	u16* mv_x		= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WK_REG1 );
	u16* scroll_y	= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WK_REG2 );
	u16* mv_y		= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WK_REG3 );
	u16* count_x	= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WK_TEMP0 );
	u16* count_y	= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WK_TEMP1 );

	if( *count_x == 0 && *count_y == 0 ){
		return 1;	//終了
	}

	if( *scroll_x != 0 ){
		if( *mv_x == 0 ){
			GF_BGL_ScrollSet( fsys->bgl, FLD_MBGFRM_FONT, GF_BGL_SCROLL_X_INC, *scroll_x );
		}else{
			GF_BGL_ScrollSet( fsys->bgl, FLD_MBGFRM_FONT, GF_BGL_SCROLL_X_DEC, *scroll_x );
		}
	}

	if( *scroll_y != 0 ){
		if( *mv_y == 0 ){
			GF_BGL_ScrollSet( fsys->bgl, FLD_MBGFRM_FONT, GF_BGL_SCROLL_Y_INC, *scroll_y );
		}else{
			GF_BGL_ScrollSet( fsys->bgl, FLD_MBGFRM_FONT, GF_BGL_SCROLL_Y_DEC, *scroll_y );
		}
	}

	if( *count_x != 0 ){ 
		(*count_x)--;
	}

	if( *count_y != 0 ){
		(*count_y)--;
	}

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 看板作成（タウンマップ、標識、表札）
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	1
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdBoardMake( VM_MACHINE * core )
{
	FIELDSYS_WORK * fsys;
	STRBUF** ptmp;
	STRBUF** pbuf;
	WORDSET** wordset;
	u16	map;
	u16	wk_id;
	u8	type;
	u8	msg_id;

	fsys = core->fsys;
	ptmp = GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_TMPBUF );
	pbuf = GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_MSGBUF );
	wordset = GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WORDSET );
	msg_id = VMGetU8(core);
	type = VMGetU8( core );
	map  = VMGetU16( core );
	wk_id = VMGetU16( core );
	if (map == 0) {
		//絵柄の指定が０の場合、OBJのパラメータから絵柄指定を取得する
		//話し掛け対象OBJ
		FIELD_OBJ_PTR *fldobj = GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_TARGET_OBJ );
		map = FieldOBJ_ParamGet(*fldobj, FLDOBJ_PARAM_0);
		OS_Printf("OBJID:%d PARAM0:%d X:%d Z:%d\n", FieldOBJ_OBJIDGet(*fldobj),
				FieldOBJ_ParamGet(*fldobj, FLDOBJ_PARAM_0),
				FieldOBJ_NowPosGX_Get(*fldobj), FieldOBJ_NowPosGZ_Get(*fldobj));
	}

	BoardDataSet( fsys->board, type, map );
	BoardSetRequest( fsys->board, BOARD_REQ_ADD );
	BoardMain( fsys );

	MSGMAN_GetString( core->msgman, msg_id, *ptmp );
	WORDSET_ExpandStr( *wordset, *pbuf, *ptmp );

	GF_STR_PrintSimple( BoardWinGet(fsys->board), FONT_TALK, *pbuf, 0, 0, MSG_ALLPUT, NULL );

	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * 看板作成（掲示板用）
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	1
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdInfoBoardMake( VM_MACHINE * core )
{
	FIELDSYS_WORK * fsys;
	u16 map;
	u8 type;

	fsys = core->fsys;
	type = VMGetU8( core );
	map  = VMGetU16( core );

	BoardDataSet( fsys->board, type, map );
	BoardSetRequest( fsys->board, BOARD_REQ_ADD );

	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * 看板制御リクエスト
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	1
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdBoardReq( VM_MACHINE * core )
{
	FIELDSYS_WORK * fsys;
	u8 req;

	fsys = core->fsys;
	req  = VMGetU8( core );

	BoardSetRequest( fsys->board, req );

	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * 看板リクエスト終了待ちセット
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @retval	"0 = 終了している"
 * @retval	"1 = 処理中"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdBoardWait( VM_MACHINE * core )
{
	FIELDSYS_WORK * fsys = core->fsys;

	if( BoardReqEndCheck( fsys->board ) == TRUE ){
		return 0;
	}
	VM_SetWait( core, BoardReqWait );
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * 看板リクエスト終了待ち
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @retval	"0 = 動作中"
 * @retval	"1 = 終了"
 */
//--------------------------------------------------------------------------------------------
static BOOL BoardReqWait( VM_MACHINE * core )
{
	FIELDSYS_WORK * fsys = core->fsys;

	if( BoardReqEndCheck( fsys->board ) == TRUE ){
		return 1;
	}
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 看板メッセージ表示
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @retrn	1
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdBoardMsg( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys		= core->fsys;
	u8* msg_index			= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_MSGINDEX );
	STRBUF** ptmp			= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_TMPBUF );
	STRBUF** pbuf			= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_MSGBUF );
	WORDSET** wordset		= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WORDSET );
	u8	msg_id				= VMGetU8(core);
	u16 wk_id				= VMGetU16( core );

	//GF_BGL_BmpWinDataFill( BoardWinGet( fsys->board ), FBMP_COL_WHITE );	//メッセージクリア

	MSGMAN_GetString( core->msgman, msg_id, *ptmp );

	//登録された単語を使って文字列展開する
	WORDSET_ExpandStr( *wordset, *pbuf, *ptmp );

	//看板TCB保存
	*msg_index = FieldTalkMsgStart( BoardWinGet(fsys->board),
									*pbuf, SaveData_GetConfig(core->fsys->savedata), 1 );

	//仮想マシンの汎用レジスタにワークのIDを格納
	core->reg[0] = wk_id;

	VM_SetWait( core, BoardMsgWait );

	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * メッセージ終了待ち
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @retval	"0 = 動作中"
 * @retval	"1 = 終了"
 *
 * @li	ANSWK = 0 : キャンセル
 * @li	ANSWK = 1 : メニューへ
 * @li	ANSWK = 2 : 通常終了
 */
//--------------------------------------------------------------------------------------------
static BOOL BoardMsgWait( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	u8* msg_index		= GetEvScriptWorkMemberAdrs( fsys,ID_EVSCR_MSGINDEX );
	u16* ret_wk			= GetEventWorkAdrs( fsys, core->reg[0] );	//注意！
	u8	type			= BoardTypeGet( fsys->board );
	int	dir = 0xffff;

	// 通常終了
	if( FldTalkMsgEndCheck( *msg_index ) == 1 ){
		*ret_wk = 2;
		return 1;
	}
/*
	// キャンセル
	if( sys.trg & ( PAD_KEY_UP|PAD_KEY_DOWN|PAD_KEY_LEFT|PAD_KEY_RIGHT ) ){
		GF_STR_PrintForceStop( *msg_index );
		*ret_wk = 0;
		return 1;
	}
*/
	// 十字キーのリクエスト処理
	if( sys.trg & PAD_KEY_UP ){
		dir = DIR_UP;
	}else if( sys.trg & PAD_KEY_DOWN ){
		dir = DIR_DOWN;
	}else if( sys.trg & PAD_KEY_LEFT ){
		dir = DIR_LEFT;
	}else if( sys.trg & PAD_KEY_RIGHT ){
		dir = DIR_RIGHT;
	}
	if( dir != 0xffff ){
		GF_STR_PrintForceStop( *msg_index );
		Player_DirSet( core->fsys->player, dir );
		*ret_wk = 0;
		return 1;
	}

	// メニューリクエスト
	if( sys.trg & PAD_BUTTON_X ){
		GF_STR_PrintForceStop( *msg_index );
		*ret_wk = 1;
		return 1;
	}

	return 0;
}


//--------------------------------------------------------------------------------------------
/**
 * 看板終了待ちセット
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @retrn	1
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdBoardEndWait( VM_MACHINE * core )
{
	u16 wk_id	= VMGetU16( core );

	//仮想マシンの汎用レジスタにワークのIDを格納
	core->reg[0] = wk_id;

	VM_SetWait( core, BoardEndWait );
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * 看板終了待ち
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @retval	"0 = 動作中"
 * @retval	"1 = 終了"
 *
 * @li	ANSWK = 0 : 通常終了
 * @li	ANSWK = 1 : メニューへ
 */
//--------------------------------------------------------------------------------------------
static BOOL BoardEndWait( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	u16* ret_wk			= GetEventWorkAdrs( fsys, core->reg[0] );	//注意！
	int	dir = 0xffff;

/*
	// 通常終了
//if( sys.trg & (PAD_KEY_UP|PAD_KEY_DOWN|PAD_KEY_LEFT|PAD_KEY_RIGHT|PAD_BUTTON_A|PAD_BUTTON_B) ){
	if( sys.trg & (PAD_KEY_UP|PAD_KEY_DOWN|PAD_KEY_LEFT|PAD_KEY_RIGHT|PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL) ){
		*ret_wk = 0;
		return 1;
	}
*/
	if( sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL) ){
		*ret_wk = 0;
		return 1;
	}

	// 十字キーのリクエスト処理
	if( sys.trg & PAD_KEY_UP ){
		dir = DIR_UP;
	}else if( sys.trg & PAD_KEY_DOWN ){
		dir = DIR_DOWN;
	}else if( sys.trg & PAD_KEY_LEFT ){
		dir = DIR_LEFT;
	}else if( sys.trg & PAD_KEY_RIGHT ){
		dir = DIR_RIGHT;
	}
	if( dir != 0xffff ){
		Player_DirSet( core->fsys->player, dir );
		*ret_wk = 0;
		return 1;
	}

	// メニューリクエスト
	if( sys.trg & PAD_BUTTON_X ){
		*ret_wk = 1;
		return 1;
	}

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * メニューリクエスト
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	0
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdMenuReq( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	SetEvScriptNextFunc( fsys );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 「はい・いいえ」処理
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	1
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdYesNoWin( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	BMPMENU_WORK** mw	= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_MENUWORK );
	u16 wk_id			= VMGetU16( core );

	MenuWinGraphicSet(
		fsys->bgl, FLD_MBGFRM_FONT, MENU_WIN_CGX_NUM, MENU_WIN_PAL, 0, HEAPID_FIELD );

	*mw = BmpYesNoSelectInit(
			fsys->bgl, &YesNoBmpDat, MENU_WIN_CGX_NUM, MENU_WIN_PAL, HEAPID_FIELD );

	//仮想マシンの汎用レジスタにワークのIDを格納
	core->reg[0] = wk_id;

	VM_SetWait( core, EvYesNoSelect );

	return 1;
}

static BOOL EvYesNoSelect(VM_MACHINE * core)
{
	u32	ret;
	FIELDSYS_WORK* fsys = core->fsys;
	BMPMENU_WORK** mw	= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_MENUWORK );
	u16* ret_wk			= GetEventWorkAdrs( fsys, core->reg[0] );	//注意！
	
	ret  = BmpYesNoSelectMain( *mw, HEAPID_FIELD );

	if( ret == BMPMENU_NULL ){ return 0; }

	if( ret == 0 ){
		*ret_wk = 0;
	}else{
		*ret_wk = 1;
	}
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	待機アイコン表示
 * @param	core		仮想マシン制御構造体へのポインタ
 * @return	0
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdTimeWaitIconAdd(VM_MACHINE * core)
{
	void **buf;
	GF_BGL_BMPWIN* pMsgWinDat = GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_MSGWINDAT );
	buf = GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_WAITICON);
	*buf = TimeWaitIconAdd(pMsgWinDat, TALK_WIN_CGX_NUM);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	待機アイコン消去
 * @param	core		仮想マシン制御構造体へのポインタ
 * @return	0
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdTimeWaitIconDel(VM_MACHINE * core)
{
	void **buf;
	buf = GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_WAITICON);
	TimeWaitIconDel(*buf);
	return 0;
}


//============================================================================================
//
//	BMPメニュー関連
//
//	"BMPリスト"関数と同じ関数を使っているので注意！
//	・リスト終了待ち関数
//
//============================================================================================

//--------------------------------------------------------------
/**
 * @brief	BMPメニュー	初期化
 *
 * @param	none
 *
 * @return	1
 */
//--------------------------------------------------------------
static BOOL EvCmdBmpMenuInit( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys	= core->fsys;
	EV_WIN_WORK** ev_win= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_EVWIN );
	WORDSET** wordset	= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WORDSET );
	u8 x				= VMGetU8(core);
	u8 y				= VMGetU8(core);
	u8 cursor			= VMGetU8(core);
	u8 cancel			= VMGetU8(core);
	u16 wk_id			= VMGetU16( core );
	
	//初期化
	*ev_win	= CmdEvBmpMenu_Init(fsys, x, y, cursor, cancel, 
								GetEventWorkAdrs(fsys,wk_id), *wordset, 
								GetEvScriptWorkMemberAdrs(core->fsys,ID_EVSCR_MSGWINDAT),
								NULL );

	//仮想マシンの汎用レジスタにワークのIDを格納
	core->reg[0] = wk_id;

	return 1;
}

//--------------------------------------------------------------
/**
 * @brief	BMPメニュー	初期化(読み込んでいるgmmファイルを使用する)
 *
 * @param	none
 *
 * @return	1
 */
//--------------------------------------------------------------
static BOOL EvCmdBmpMenuInitEx( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys	= core->fsys;
	EV_WIN_WORK** ev_win= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_EVWIN );
	WORDSET** wordset	= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WORDSET );
	u8 x				= VMGetU8(core);
	u8 y				= VMGetU8(core);
	u8 cursor			= VMGetU8(core);
	u8 cancel			= VMGetU8(core);
	u16 wk_id			= VMGetU16( core );
	
	//初期化
	*ev_win	= CmdEvBmpMenu_Init(fsys, x, y, cursor, cancel, 
								GetEventWorkAdrs(fsys,wk_id), *wordset, 
								GetEvScriptWorkMemberAdrs(core->fsys,ID_EVSCR_MSGWINDAT), 
								core->msgman );

	//仮想マシンの汎用レジスタにワークのIDを格納
	core->reg[0] = wk_id;

	return 1;
}

//--------------------------------------------------------------
/**
 * @brief	BMPメニュー	リスト作成
 *
 * @param	none
 *
 * @retval	0
 */
//--------------------------------------------------------------
static BOOL EvCmdBmpMenuMakeList( VM_MACHINE * core )
{
	u8 msg_id, param;
	FIELDSYS_WORK* fsys	= core->fsys;
	EV_WIN_WORK** ev_win= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_EVWIN );	//EV_WIN_WORK取得

	msg_id	= VMGetU8(core);
	param	= VMGetU8(core);

	CmdEvBmpMenu_MakeList( *ev_win, msg_id, param );
	return 0;
}

//--------------------------------------------------------------
/**
 * @brief	BMPメニュー	リスト作成(u16バージョン)
 *
 * @param	none
 *
 * @retval	0
 */
//--------------------------------------------------------------
static BOOL EvCmdBmpMenuMakeList16( VM_MACHINE * core )
{
	u16 msg_id,param;
	FIELDSYS_WORK* fsys	= core->fsys;
	EV_WIN_WORK** ev_win= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_EVWIN );	//EV_WIN_WORK取得

	msg_id	= VMGetWorkValue(core);
	param	= VMGetWorkValue(core);

	CmdEvBmpMenu_MakeList( *ev_win, msg_id, param );
	return 0;
}

//--------------------------------------------------------------
/**
 * @brief	BMPメニュー	開始
 *
 * @param	none
 *
 * @retval	1
 */
//--------------------------------------------------------------
static BOOL EvCmdBmpMenuStart( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys	= core->fsys;
	EV_WIN_WORK** ev_win= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_EVWIN );	//EV_WIN_WORK取得

	CmdEvBmpMenu_Start( *ev_win );
	
	VM_SetWait( core, EvSelWinWait );
	return 1;
}

//ウェイト関数
static BOOL EvSelWinWait(VM_MACHINE * core)
{
	FIELDSYS_WORK* fsys = core->fsys;
	u16* ret_wk = GetEventWorkAdrs( fsys, core->reg[0] );	//注意！

	if( *ret_wk == EV_WIN_NOTHING ){
		return FALSE;	//継続
	}

	return TRUE;		//終了
}


//--------------------------------------------------------------
/**
 * @brief	BMPメニュー	開始
 *
 * @param	none
 *
 * @retval	1
 */
//--------------------------------------------------------------
static BOOL EvCmdUnionBmpMenuStart( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys	= core->fsys;
	EV_WIN_WORK** ev_win= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_EVWIN );	//EV_WIN_WORK取得

	CmdEvBmpMenu_Start( *ev_win );
	
	VM_SetWait( core, EvSelUnionWinWait );
	return 1;
}

//ウェイト関数
static BOOL EvSelUnionWinWait(VM_MACHINE * core)
{
	FIELDSYS_WORK* fsys = core->fsys;
	u16* ret_wk = GetEventWorkAdrs( fsys, core->reg[0] );	//注意！
	EV_WIN_WORK** ev_win= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_EVWIN );	//EV_WIN_WORK取得


	if( *ret_wk == EV_WIN_NOTHING ){
		// BMPMenuList中でもキャンセルが来たら強制終了する
		if(Union_CancelRecv( fsys->union_work )){
			*ret_wk = UNION_PARENT_SELECT_CANCEL;
			EvBmpMenu_Del(*ev_win);
			return TRUE;
		}
		return FALSE;	//継続
	}

	return TRUE;		//終了
}


//============================================================================================
//
//	BMPリスト関連
//
//	"BMPメニュー"関数と同じ関数を使っているので注意！
//	・リスト終了待ち関数
//
//============================================================================================

//--------------------------------------------------------------
/**
 * @brief	BMPリスト	初期化
 *
 * @param	none
 *
 * @retval	1
 */
//--------------------------------------------------------------
static BOOL EvCmdBmpListInit( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys	= core->fsys;
	EV_WIN_WORK** ev_win= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_EVWIN );
	WORDSET** wordset	= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WORDSET );
	u8 x				= VMGetU8(core);
	u8 y				= VMGetU8(core);
	u8 cursor			= VMGetU8(core);
	u8 cancel			= VMGetU8(core);
	u16 wk_id			= VMGetU16( core );

	//初期化
	*ev_win	= CmdEvBmpList_Init( fsys, x, y, cursor, cancel, 
									GetEventWorkAdrs(fsys,wk_id), *wordset, 
									GetEvScriptWorkMemberAdrs(core->fsys,ID_EVSCR_MSGWINDAT),
									NULL );

	//仮想マシンの汎用レジスタにワークのIDを格納
	core->reg[0] = wk_id;

	return 1;
}

//--------------------------------------------------------------
/**
 * @brief	BMPリスト	初期化(読み込んでいるgmmファイルを使用する)
 *
 * @param	none
 *
 * @retval	1
 */
//--------------------------------------------------------------
static BOOL EvCmdBmpListInitEx( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys	= core->fsys;
	EV_WIN_WORK** ev_win= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_EVWIN );
	WORDSET** wordset	= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WORDSET );
	u8 x				= VMGetU8(core);
	u8 y				= VMGetU8(core);
	u8 cursor			= VMGetU8(core);
	u8 cancel			= VMGetU8(core);
	u16 wk_id			= VMGetU16( core );

	//初期化
	*ev_win	= CmdEvBmpList_Init( fsys, x, y, cursor, cancel, 
									GetEventWorkAdrs(fsys,wk_id), *wordset, 
									GetEvScriptWorkMemberAdrs(core->fsys,ID_EVSCR_MSGWINDAT),
									core->msgman );

	//仮想マシンの汎用レジスタにワークのIDを格納
	core->reg[0] = wk_id;

	return 1;
}

//--------------------------------------------------------------
/**
 * @brief	BMPリスト	リスト作成
 *
 * @param	none
 *
 * @retval	0
 */
//--------------------------------------------------------------
static BOOL EvCmdBmpListMakeList( VM_MACHINE * core )
{
	EV_WIN_WORK** ev_win= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_EVWIN );
	u8 msg_id			= VMGetWorkValue(core);
	u8 talk_msg_id		= VMGetWorkValue(core);
	u8 param			= VMGetWorkValue(core);

	CmdEvBmpList_MakeList( *ev_win, msg_id, talk_msg_id, param );
	return 0;
}

//--------------------------------------------------------------
/**
 * @brief	BMPリスト	開始
 *
 * @param	none
 *
 * @retval	1
 */
//--------------------------------------------------------------
static BOOL EvCmdBmpListStart( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys	= core->fsys;
	EV_WIN_WORK** ev_win= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_EVWIN );	//EV_WIN_WORK取得

	CmdEvBmpList_Start( *ev_win );
	
	VM_SetWait( core, EvSelWinWait );
	return 1;
}


//============================================================================================
//
//	BMPメニュー縦横関連
//
//	"BMPリスト"関数と同じ関数を使っているので注意！
//	・リスト終了待ち関数
//
//============================================================================================

//--------------------------------------------------------------
/**
 * @brief	BMPメニュー縦横	開始
 *
 * @param	none
 *
 * @retval	none
 */
//--------------------------------------------------------------
static BOOL EvCmdBmpMenuHVStart( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys	= core->fsys;
	EV_WIN_WORK** ev_win= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_EVWIN );	//EV_WIN_WORK取得
	u8 x_max			= VMGetU8(core);

	CmdEvBmpMenuHV_Start( *ev_win, x_max );
	
	VM_SetWait( core, EvSelWinWait );
	return 1;
}


//============================================================================================
//
//	OBJアニメーション関連
//
//============================================================================================
static BOOL EvObjAnimeWait(VM_MACHINE * core);
static void EvAnmSetTCB( FIELDSYS_WORK* fsys, TCB_PTR anm_tcb, FIELD_OBJ_ACMD_LIST * list );
static void EvAnmMainTCB( TCB_PTR tcb, void* wk );

//アニメーション終了監視ワーク
typedef struct{
	TCB_PTR	tcb;					//TCB
	TCB_PTR	anm_tcb;				//アニメーションTCB
	FIELD_OBJ_ACMD_LIST * list;
	FIELDSYS_WORK* fsys;			//
}EV_ANM_WORK;

//--------------------------------------------------------------------------------------------
/**
 * アニメーション
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdObjAnime( VM_MACHINE * core )
{
	VM_CODE* p;
	TCB_PTR anm_tcb;
	u8* num;
	FIELD_OBJ_PTR* dummy;
	FIELD_OBJ_PTR fldobj;		//対象のフィールドOBJのポインタ
	u16 obj_id	= VMGetWorkValue(core);
	u32 pos		= (s32)VMGetU32(core);

	fldobj = FieldObjPtrGetByObjId( core->fsys, obj_id );

	//エラーチェック
	if( fldobj == NULL ){
		GF_ASSERT( (0) && "対象のフィールドOBJのポインタ取得失敗！" );
	}

	//アニメーションコマンドリストセット
	p = (VM_CODE*)(core->PC+pos);
	anm_tcb = FieldOBJ_AcmdListSet( fldobj, (FIELD_OBJ_ACMD_LIST*)p );

	//アニメーションの数を足す
	num = GetEvScriptWorkMemberAdrs( core->fsys,ID_EVSCR_ANMCOUNT );
	(*num)++;

	//TCBセット
	EvAnmSetTCB( core->fsys, anm_tcb, NULL );

	return 0;
}
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
static BOOL EvCmdObjAnimePos(VM_MACHINE * core)
{
	VM_CODE* p;
	TCB_PTR anm_tcb;
	u8* num;
	FIELD_OBJ_PTR* dummy;
	FIELD_OBJ_PTR fldobj;		//対象のフィールドOBJのポインタ
	u16 obj_id	= VMGetWorkValue(core);
	u16 tx = VMGetWorkValue(core);
	u16 tz = VMGetWorkValue(core);
	u16 nx, nz;
	FIELD_OBJ_ACMD_LIST * list;
	int count;

	fldobj = FieldObjPtrGetByObjId( core->fsys, obj_id );

	//エラーチェック
	if( fldobj == NULL ){
		GF_ASSERT( (0) && "対象のフィールドOBJのポインタ取得失敗！" );
	}
	list = sys_AllocMemory(HEAPID_FIELD, sizeof(FIELD_OBJ_ACMD_LIST) * 64);

	nx = FieldOBJ_NowPosGX_Get( fldobj );
	nz = FieldOBJ_NowPosGZ_Get( fldobj );
	count = 0;
	if (nx < tx) {
		list[count].code = AC_WALK_R_8F;
		list[count].num = tx - nx;
		count ++;
	} else if (nx > tx) {
		list[count].code = AC_WALK_L_8F;
		list[count].num = nx - tx;
		count ++;
	}
	if (nz < tz) {
		list[count].code = AC_WALK_U_8F;
		list[count].num = tz - nz;
		count ++;
	} else if (nz > tz) {
		list[count].code = AC_WALK_D_8F;
		list[count].num = nz - tz;
		count ++;
	}
	list[count].code = ACMD_END;
	list[count].num = 0;

	//アニメーションコマンドリストセット
	anm_tcb = FieldOBJ_AcmdListSet( fldobj, list );

	//アニメーションの数を足す
	num = GetEvScriptWorkMemberAdrs( core->fsys,ID_EVSCR_ANMCOUNT );
	(*num)++;

	//TCBセット
	EvAnmSetTCB( core->fsys, anm_tcb, list );

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * FIELD_OBJ_PTRを取得
 *
 * @param	fsys	FIELDSYS_WORK型のポインタ
 * @param	obj_id	OBJID
 *
 * @return	"FIELD_OBJ_PTR"
 */
//--------------------------------------------------------------------------------------------
static FIELD_OBJ_PTR FieldObjPtrGetByObjId( FIELDSYS_WORK* fsys, int obj_id )
{
	FIELD_OBJ_PTR* dummy;
	FIELD_OBJ_PTR fldobj;		//対象のフィールドOBJのポインタ

	//連れ歩きOBJ判別IDが渡された時
	if( obj_id == SCR_OBJID_MV_PAIR ){
		fldobj = FieldOBJSys_MoveCodeSearch( fsys->fldobjsys, MV_PAIR );

	//透明ダミーOBJ判別IDが渡された時
	}else if( obj_id == SCR_OBJID_DUMMY ){
		dummy = GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_DUMMY_OBJ );
		fldobj = *dummy;

	//対象のフィールドOBJのポインタ取得
	}else{
		fldobj	= FieldOBJSys_OBJIDSearch( fsys->fldobjsys, obj_id );
	}

	return fldobj;
}

//--------------------------------------------------------------------------------------------
/**
 * アニメーション終了待ち
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdObjAnimeWait( VM_MACHINE * core )
{
	VM_SetWait( core, EvObjAnimeWait );
	return 1;
}

//return 1 = 終了
static BOOL EvObjAnimeWait(VM_MACHINE * core)
{
	FIELDSYS_WORK* fsys = core->fsys;
	u8* anm_count = GetEvScriptWorkMemberAdrs(fsys,ID_EVSCR_ANMCOUNT);

	//アニメーション数をチェック
	if( *anm_count == 0 ){
		return 1;
	}

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	アニメ終了監視TCB セット
 *
 * @param	fsys	FIELDSYS_WORK型のポインタ
 * @param	anm_tcb	TCB_PTR型
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
static void EvAnmSetTCB( FIELDSYS_WORK* fsys, TCB_PTR anm_tcb, FIELD_OBJ_ACMD_LIST * list )
{
	EV_ANM_WORK* wk = NULL;
	wk = sys_AllocMemory(HEAPID_FIELD, sizeof(EV_ANM_WORK));

	if( wk == NULL ){
		GF_ASSERT( (0) && "scrcmd.c メモリ確保失敗！" );
		return;
	}

	wk->fsys	= fsys;
	wk->anm_tcb	= anm_tcb;
	wk->list	= list;
	wk->tcb		= TCB_Add( EvAnmMainTCB, wk, 0 );
	return;
}

//--------------------------------------------------------------
/**
 * @brief	アニメ終了監視TCB メイン
 *
 * @param	tcb		TCB_PTR
 * @param	wk		ワークのアドレス
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void EvAnmMainTCB( TCB_PTR tcb, void* wk )
{
	EV_ANM_WORK *swk;
	u8* num;

	swk = (EV_ANM_WORK *)wk;
	num = GetEvScriptWorkMemberAdrs( swk->fsys, ID_EVSCR_ANMCOUNT );

	if( FieldOBJ_AcmdListEndCheck( swk->anm_tcb ) == TRUE ){	//終了チェック

		FieldOBJ_AcmdListEnd( swk->anm_tcb );

		TCB_Delete( swk->tcb );
		if (swk->list) {
			sys_FreeMemoryEz(swk->list);
		}
		sys_FreeMemoryEz( wk );

		//アニメーション数の管理
		if( *num == 0 ){
			GF_ASSERT( (0) && "アニメーション数の管理が不正です！" );
			return;
		}

		(*num)--;
	}

	return;
}

//--------------------------------------------------------------------------------------------
/**
 * 全OBJ動作停止
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	0
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdObjPauseAll( VM_MACHINE * core )
{
	FIELD_OBJ_SYS_PTR fldobjsys;
	FIELDSYS_WORK* fsys = core->fsys;
	FIELD_OBJ_PTR *fldobj = GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_TARGET_OBJ );
	
	if (*fldobj == NULL) {
		fldobjsys = fsys->fldobjsys;
		FieldOBJSys_MovePauseAll( fldobjsys );
	} else {
		EvCmdTalkObjPauseAll(core);
	}
	
	return 1;
}


//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
#define	PLAYER_BIT			(1<<0)
#define	PLAYER_PAIR_BIT		(1<<1)
#define	OTHER_BIT			(1<<2)
#define	OTHER_PAIR_BIT		(1<<3)

static u8 step_watch_bit;

//--------------------------------------------------------------
//--------------------------------------------------------------
static inline void InitStepWatchBit(void)
{
	step_watch_bit = 0;
}
//--------------------------------------------------------------
//--------------------------------------------------------------
static inline BOOL CheckStepWatchBit(int mask)
{
	return (step_watch_bit & mask) != 0;
}
//--------------------------------------------------------------
//--------------------------------------------------------------
static inline void SetStepWatchBit(int mask)
{
	step_watch_bit |= mask;
}
//--------------------------------------------------------------
//--------------------------------------------------------------
static inline void ResetStepWatchBit(int mask)
{
	step_watch_bit &= (0xff ^ mask);
}

//--------------------------------------------------------------
/**
 * @brief	OBJ動作終了待ち
 */
//--------------------------------------------------------------
static BOOL EvWaitTalkObj( VM_MACHINE * core )
{
	FIELDSYS_WORK * fsys = core->fsys;
	FIELD_OBJ_PTR *fldobj = GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_TARGET_OBJ );
	FIELD_OBJ_PTR player = Player_FieldOBJGet(fsys->player);

	//自機動作停止チェック
	if (CheckStepWatchBit(PLAYER_BIT) && FieldOBJ_AcmdEndCheck(player) == TRUE) {
		FieldOBJ_MovePause( player );
		ResetStepWatchBit(PLAYER_BIT);
	}
	//話しかけ対象動作停止チェック
	if (CheckStepWatchBit(OTHER_BIT) && FieldOBJ_StatusBitCheck_Move(*fldobj) == 0) {
		FieldOBJ_MovePause( *fldobj );
		ResetStepWatchBit(OTHER_BIT);
	}

	//自機の連れ歩き動作停止チェック
	if (CheckStepWatchBit(PLAYER_PAIR_BIT)) {
		FIELD_OBJ_PTR player_pair = FieldOBJSys_MoveCodeSearch( fsys->fldobjsys, MV_PAIR );
		if (FieldOBJ_StatusBitCheck_Move(player_pair) == 0) {
			FieldOBJ_MovePause(player_pair);
			ResetStepWatchBit(PLAYER_PAIR_BIT);
		}
	}

	//話しかけ対象の連れ歩き動作停止チェック
	if (CheckStepWatchBit(OTHER_PAIR_BIT)) {
		FIELD_OBJ_PTR other_pair = FieldOBJ_MovePairSearch(*fldobj);
		if (FieldOBJ_StatusBitCheck_Move(other_pair) == 0) {
			FieldOBJ_MovePause(other_pair);
			ResetStepWatchBit(OTHER_PAIR_BIT);
		}
	}

	if (step_watch_bit == 0) {
		return 1;
	}
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * @param	core
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdTalkObjPauseAll( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	FIELD_OBJ_PTR *fldobj = GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_TARGET_OBJ );
	FIELD_OBJ_PTR player = Player_FieldOBJGet(fsys->player);
	FIELD_OBJ_PTR player_pair = FieldOBJSys_MoveCodeSearch( fsys->fldobjsys, MV_PAIR );
	FIELD_OBJ_PTR other_pair = FieldOBJ_MovePairSearch(*fldobj);
	FIELD_OBJ_SYS_PTR fldobjsys;
	
	fldobjsys = fsys->fldobjsys;
	
	InitStepWatchBit();

	FieldOBJSys_MovePauseAll( fldobjsys );

	if (FieldOBJ_AcmdEndCheck(player) == FALSE) {
		SetStepWatchBit(PLAYER_BIT);
		FieldOBJ_MovePauseClear( player );
	}

	if (FieldOBJ_StatusBitCheck_Move(*fldobj) != 0) {
		SetStepWatchBit(OTHER_BIT);
		FieldOBJ_MovePauseClear( *fldobj );
	}


	if (player_pair) {
		if( SysFlag_PairCheck(SaveData_GetEventWork(fsys->savedata)) == 1
				&& FieldOBJ_StatusBitCheck_Move(player_pair) != 0) {
			SetStepWatchBit(PLAYER_PAIR_BIT);
			FieldOBJ_MovePauseClear( player_pair );
		}
	}

	if (other_pair) {
		if (FieldOBJ_StatusBitCheck_Move(other_pair) != 0) {
			SetStepWatchBit(OTHER_PAIR_BIT);
			FieldOBJ_MovePauseClear( other_pair );
		}
	}
	VM_SetWait( core, EvWaitTalkObj );
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * 全OBJ動作再開
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdObjPauseClearAll( VM_MACHINE * core )
{
	FIELD_OBJ_SYS_PTR fldobjsys;
	FIELDSYS_WORK* fsys = core->fsys;
	
	fldobjsys = fsys->fldobjsys;
	
	FieldOBJSys_MovePauseAllClear( fldobjsys );
	
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * OBJ動作停止(個々)
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	0
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdObjPause( VM_MACHINE * core )
{
	FIELD_OBJ_PTR fldobj;		//対象のフィールドOBJのポインタ
	FIELDSYS_WORK* fsys = core->fsys;
	
	//対象のフィールドOBJのポインタ取得
	fldobj = FieldOBJSys_OBJIDSearch( fsys->fldobjsys, VMGetU16(core) );

	//動作ポーズ ON
	FieldOBJ_MovePause( fldobj );
	
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * OBJ動作再開(個々)
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	0
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdObjPauseClear( VM_MACHINE * core )
{
	FIELD_OBJ_PTR fldobj;		//対象のフィールドOBJのポインタ
	FIELDSYS_WORK* fsys = core->fsys;
	
	//対象のフィールドOBJのポインタ取得
	fldobj = FieldOBJSys_OBJIDSearch( fsys->fldobjsys, VMGetU16(core) );
	FieldOBJ_MovePauseClear( fldobj );
	
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * OBJ出す
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdObjAdd( VM_MACHINE * core )
{
	FIELD_OBJ_PTR ret;
	FIELDSYS_WORK* fsys = core->fsys;
	u16 id				= VMGetWorkValue(core);
	
	ret= FieldOBJ_AddHEvent( fsys->fldobjsys, id, EventData_GetNpcCount(fsys),
								fsys->location->zone_id, EventData_GetNpcData(fsys) );

	if( ret == NULL ){
		GF_ASSERT( (0) && "指定したIDに該当するデータがありませんでした！" );
	}

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * OBJ消す
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdObjDel( VM_MACHINE * core )
{
	FIELD_OBJ_PTR fldobj;		//対象のフィールドOBJのポインタ
	FIELDSYS_WORK* fsys = core->fsys;
	
	//対象のフィールドOBJのポインタ取得
	fldobj	= FieldOBJSys_OBJIDSearch( fsys->fldobjsys, VMGetWorkValue(core) );

	FieldOBJ_DeleteEvent( fldobj );

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 透明ダミーOBJを追加
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdVanishDummyObjAdd( VM_MACHINE * core )
{
	u16 x	= VMGetWorkValue( core );
	u16 z	= VMGetWorkValue( core );
	FIELD_OBJ_PTR* fldobj = GetEvScriptWorkMemberAdrs(core->fsys,ID_EVSCR_DUMMY_OBJ);//ダミーOBJ

#if 0
	//汎用的に使う時
	u16 dir = VMGetWorkValue( core );
	u16 obj = VMGetWorkValue( core );	//OBJコード(HERO等)
	u16 move= VMGetWorkValue( core );	//動作コード
	u16 zone= VMGetU16( core );			//ゾーンID
	*fldobj = FieldOBJ_AddHMake( core->fsys->fldobjsys, x, z, dir, obj, move, zone_id );
#endif
	
	//ダミーOBJ用固定
	*fldobj = FieldOBJ_AddHMake( core->fsys->fldobjsys, x, z, DIR_UP, NONDRAW, 
								MV_DMY, core->fsys->location->zone_id );

	FieldOBJ_VecPosNowHeightGetSet( *fldobj );			//高さ即反映
	FieldOBJ_StatusBitSet_Vanish( *fldobj, TRUE );		//非表示
	FieldOBJ_StatusBitSet_FellowHit( *fldobj, FALSE );	//ヒットなし
	//FieldOBJ_NotZoneDeleteSet( *fldobj, TRUE );		//ゾーン切り替え時の削除禁止

#if 1
	//カメラ設定切り替え(透明ダミーへ)
	{
		const VecFx32* inTarget;

		inTarget = FieldOBJ_VecPosPtrGet( *fldobj );
		DivMapBindTarget( inTarget, core->fsys->map_cont_dat );	//地形バインド
		GFC_BindCameraTarget( inTarget, core->fsys->camera_ptr );
	}
#endif

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 透明ダミーOBJを削除
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdVanishDummyObjDel( VM_MACHINE * core )
{
	FIELD_OBJ_PTR* fldobj = GetEvScriptWorkMemberAdrs(core->fsys,ID_EVSCR_DUMMY_OBJ);	//ダミーOBJ
	FieldOBJ_Delete( *fldobj );

#if 1
	//カメラ設定切り替え(主人公へ)
	{
		FIELD_OBJ_PTR fldobj_player;
		const VecFx32* inTarget;

		fldobj_player = FieldOBJSys_OBJIDSearch( core->fsys->fldobjsys, FLDOBJ_ID_PLAYER );
		inTarget = FieldOBJ_VecPosPtrGet( fldobj_player );
		DivMapBindTarget( inTarget, core->fsys->map_cont_dat );	//地形バインド
		GFC_BindCameraTarget( inTarget, core->fsys->camera_ptr );
	}
#endif

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 話しかけたOBJ自機方向への振り向き
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdObjTurn( VM_MACHINE * core )
{
	int dir;
	FIELD_OBJ_PTR* fldobj;
	FIELDSYS_WORK* fsys = core->fsys;
	
	{
		FIELDSYS_WORK *fsys;
		PLAYER_STATE_PTR player;
		
		fsys = core->fsys;
		player = fsys->player;
	
		dir = Player_DirGet( player );
	}
	
	dir = FieldOBJTool_DirFlip( dir );
	
	fldobj = GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_TARGET_OBJ );
	if( *fldobj == NULL ){
		return 0;
	}

	//FieldOBJ_DirDispCheckSet( *fldobj, dir );
	FieldOBJ_DirDispDrawSet( *fldobj, dir );
	
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 主人公の位置情報取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdPlayerPosGet( VM_MACHINE * core )
{
	u16 *x, *z;
	FIELDSYS_WORK* fsys = core->fsys;
	
	x = VMGetWork( core );
	z = VMGetWork( core );

	//int x,z;
	//x = Player_NowGPosXGet( fsys->player );
	//z = Player_NowGPosZGet( fsys->player );

	*x = Player_NowGPosXGet( fsys->player );
	*z = Player_NowGPosZGet( fsys->player );

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * OBJの位置情報取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdObjPosGet( VM_MACHINE * core )
{
	FIELD_OBJ_PTR fldobj;
	u16 *x, *z;
	FIELDSYS_WORK* fsys = core->fsys;

	fldobj = FieldOBJSys_OBJIDSearch( fsys->fldobjsys, VMGetWorkValue(core) );

	x = VMGetWork( core );
	z = VMGetWork( core );

	*x = FieldOBJ_NowPosGX_Get( fldobj );
	*z = FieldOBJ_NowPosGZ_Get( fldobj );
	OS_Printf( "x = %d\n", *x );
	OS_Printf( "z = %d\n", *z );

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * プレイヤーの方向取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdPlayerDirGet( VM_MACHINE * core )
{
	u16 *dir;
	
	dir = VMGetWork( core );
	*dir = Player_DirGet(core->fsys->player);

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 主人公の位置に任意のオフセット値を指定する
 * カメラ位置を同時にずらすので注意！
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdPlayerPosOffsetSet( VM_MACHINE * core )
{
	u16	ofsx,ofsy,ofsz;
	VecFx32	vec;
	FIELDSYS_WORK* fsys = core->fsys;
	
	ofsx = VMGetWorkValue(core);
	ofsy = VMGetWorkValue(core);
	ofsz = VMGetWorkValue(core);
	
	vec.x = FX32_CONST(ofsx);
	vec.y = FX32_CONST(ofsy);
	vec.z = FX32_CONST(ofsz);
	
	FieldOBJ_VecDrawOffsOutSideSet(	Player_FieldOBJGet(core->fsys->player),&vec );
	GFC_ShiftCamera(&vec,core->fsys->camera_ptr);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ゾーン切り替え時の削除禁止(TRUE=禁止、FALSE=禁止しない)
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdNotZoneDelSet( VM_MACHINE * core )
{
	FIELD_OBJ_PTR fldobj;
	u8 flag;

	fldobj	= FieldOBJSys_OBJIDSearch( core->fsys->fldobjsys, VMGetWorkValue(core) );
	flag	= VMGetU8( core );

	FieldOBJ_NotZoneDeleteSet( fldobj, flag );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 動作コード変更
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdMoveCodeChange( VM_MACHINE * core )
{
	FIELD_OBJ_PTR fldobj;
	u16 code;

	fldobj	= FieldOBJSys_OBJIDSearch( core->fsys->fldobjsys, VMGetWorkValue(core) );
	code	= VMGetU16( core );

	FieldOBJ_MoveCodeChange( fldobj, code );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 動作コード取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdMoveCodeGet( VM_MACHINE * core )
{
	FIELD_OBJ_PTR fldobj;
	u16* ret_wk	= VMGetWork( core );

	*ret_wk = 0;

	fldobj	= FieldOBJSys_OBJIDSearch( core->fsys->fldobjsys, VMGetWorkValue(core) );
	if( fldobj != NULL ){
		*ret_wk = FieldOBJ_MoveCodeGet( fldobj );
	}

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 連れ歩きOBJのIDをセット
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdPairObjIdSet( VM_MACHINE * core )
{
	FIELD_OBJ_PTR fldobj;
	fldobj = FieldOBJSys_MoveCodeSearch( core->fsys->fldobjsys, MV_PAIR );
//	FieldOBJ_OBJIDSet( fldobj, FLDOBJ_ID_PAIR );
	FieldOBJ_OBJIDChange( fldobj, FLDOBJ_ID_PAIR );
	return 0;
}



//--------------------------------------------------------------------------------------------
/**
 * シールの種類数を取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdCBSealKindNumGet(VM_MACHINE * core)		
{
	CB_SAVE_DATA* cb_sv;
	u16* ret_wk	= VMGetWork( core );

	cb_sv = CB_SaveData_AllDataGet( core->fsys->savedata );
	*ret_wk = CB_Tool_SealCllectionGet( cb_sv );

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * シールの数取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdCBItemNumGet(VM_MACHINE * core)		
{
	CB_SAVE_DATA* cb_sv;
	u16 seal_id	= VMGetWorkValue( core );
	u16* ret_wk	= VMGetWork( core );

	//OS_Printf( "seal_id = %d\n", seal_id );

	cb_sv = CB_SaveData_AllDataGet( core->fsys->savedata );
	//*ret_wk = CB_SaveData_ItemNumGet( CB_SaveData_ItemDataGet(cb_sv), seal_id );
	*ret_wk = CB_Tool_SealTotalNumGet( cb_sv, seal_id );

	//OS_Printf( "*ret_wk = %d\n", *ret_wk );

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * シールを追加
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdCBItemNumAdd(VM_MACHINE * core)		
{
	u16 seal_id	= VMGetWorkValue( core );
	u16 num		= VMGetWorkValue( core );

	CB_SaveData_ItemNumAddCheck( CB_SaveData_AllDataGet(core->fsys->savedata), seal_id, num );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * アンノーンフォルムナンバーを取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdUnknownFormGet(VM_MACHINE * core)		
{
	POKEMON_PARAM * poke;
	u16 pos		= VMGetWorkValue( core );
	u16* ret_wk	= VMGetWork( core );

	//ポケモンへのポインタ取得
	poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(core->fsys->savedata), pos );

	//0-25:A-Z 26:! 27:?(poke_tool.h)
	*ret_wk = PokeParaUnknownFormGet( poke );
	
	//OS_Printf( "form_id = %d\n", *ret_wk );
	return 0;
}


//============================================================================================
//
//	ポケモン関連
//
//============================================================================================
//--------------------------------------------------------------------------------------------
/**
 * @brief	ポケモン選択画面呼び出し（選択のみ）
 *
 * @param	core	仮想マシン制御構造体へのポインタ
 *
 * @return	1		スクリプトからメイン制御に戻る
 *
 * @li EvCmdPokeListGetResultで、選択した位置を取得して、ワーク開放が必要
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdPokeListSetProc(VM_MACHINE * core)
{
	void ** buf;
	buf = GetEvScriptWorkMemberAdrs(core->fsys, ID_EVSCR_SUBPROC_WORK);
	*buf = FieldPokeListEvent_SetProc(HEAPID_EVENT, core->fsys);

	VM_SetWait( core, EvCmdWaitSubProcEnd );
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	ポケモン選択画面呼び出し（ゲーム内交換用）
 *
 * @param	core	仮想マシン制御構造体へのポインタ
 *
 * @return	1		スクリプトからメイン制御に戻る
 *
 * @li EvCmdPokeListGetResultで、選択した位置を取得して、ワーク開放が必要
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdNpcTradePokeListSetProc(VM_MACHINE * core)
{
	void ** buf;
	buf = GetEvScriptWorkMemberAdrs(core->fsys, ID_EVSCR_SUBPROC_WORK);
	*buf = FieldPokeListEventNpcTrade_SetProc(HEAPID_EVENT, core->fsys);

	VM_SetWait( core, EvCmdWaitSubProcEnd );
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	ユニオン ポケモン選択画面呼び出し
 *
 * @param	core	仮想マシン制御構造体へのポインタ
 * @return	1		スクリプトからメイン制御に戻る
 *
 * @li EvCmdPokeListGetResultで、選択した位置を取得して、ワーク開放が必要
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdUnionPokeListSetProc(VM_MACHINE * core)
{
	void ** buf;
	buf = GetEvScriptWorkMemberAdrs(core->fsys, ID_EVSCR_SUBPROC_WORK);
	//*buf = UnionPokeListEvent_SetProc(HEAPID_EVENT, core->fsys);
	//VM_SetWait( core, EvCmdWaitSubProcEnd );
	*buf = EventCmd_PokeListSelect(core->fsys->event, HEAPID_EVENT);
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	ポケモン選択画面呼び出し
 * @param	core		仮想マシン制御構造体へのポインタ
 * @return	1		スクリプトからメイン制御に戻る
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdPokeListGetResult(VM_MACHINE * core)
{
	void ** buf;
	u16 * ret_wk;

	ret_wk = VMGetWork(core);
	buf = GetEvScriptWorkMemberAdrs(core->fsys, ID_EVSCR_SUBPROC_WORK);

	GF_ASSERT(*buf != 0);

	*ret_wk = FieldPokeListEvent_GetSelect(*buf);
	if (*ret_wk == PL_SEL_POS_EXIT) {
		*ret_wk = 0xff;
	}

	sys_FreeMemoryEz(*buf);
	*buf = NULL;

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	コンテスト ポケモン選択画面呼び出し
 *
 * @param	core	仮想マシン制御構造体へのポインタ
 *
 * @return	1		スクリプトからメイン制御に戻る
 *
 * @li EvCmdConPokeListGetResultで、選択した位置、モードを取得して、ワーク開放が必要
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdConPokeListSetProc(VM_MACHINE * core)
{
	void** buf	= GetEvScriptWorkMemberAdrs(core->fsys, ID_EVSCR_SUBPROC_WORK);
	u16 pos		= VMGetWorkValue(core);
	u16 rank	= VMGetWorkValue(core);
	u16 type	= VMGetWorkValue(core);
	u16	sio_flag= VMGetWorkValue(core);

	*buf = ContestPokeListEvent_SetProc(HEAPID_EVENT, core->fsys, type, rank, sio_flag, pos);

	VM_SetWait( core, EvCmdWaitSubProcEnd );
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	コンテスト ポケモン選択画面呼び出し結果取得とワーク解放
 * @param	core		仮想マシン制御構造体へのポインタ
 * @return	1		スクリプトからメイン制御に戻る
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdConPokeListGetResult(VM_MACHINE * core)
{
	void ** buf;
	u16 * ret_wk, * ret_mode;

	ret_wk = VMGetWork(core);
	ret_mode = VMGetWork(core);
	buf = GetEvScriptWorkMemberAdrs(core->fsys, ID_EVSCR_SUBPROC_WORK);

	GF_ASSERT(*buf != 0);

	*ret_wk = FieldPokeListEvent_GetSelect(*buf);
	if (*ret_wk == PL_SEL_POS_EXIT) {
		*ret_wk = 0xff;
	}

	*ret_mode = FieldPokeListEvent_GetMode(*buf);
	if (*ret_mode == PL_RET_STATUS) {
		*ret_mode = 1;	//つよさをみる
	}
	else{
		*ret_mode = 0;	//通常
	}

	sys_FreeMemoryEz(*buf);
	*buf = NULL;

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	コンテスト ポケモンステータス画面呼び出し
 *
 * @param	core	仮想マシン制御構造体へのポインタ
 *
 * @return	1		スクリプトからメイン制御に戻る
 *
 * @li EvCmdPokeStatusGetResultで、選択した位置を取得して、ワーク開放が必要
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdConPokeStatusSetProc(VM_MACHINE * core)
{
	void** buf	= GetEvScriptWorkMemberAdrs(core->fsys, ID_EVSCR_SUBPROC_WORK);
	u16 pos	= VMGetWorkValue(core);

	*buf = ContestPokeStatusEvent_SetProc(HEAPID_EVENT, core->fsys, pos);

	VM_SetWait( core, EvCmdWaitSubProcEnd );
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	ポケモンステータス画面呼び出し後の結果取得とワーク解放
 * @param	core		仮想マシン制御構造体へのポインタ
 * @return	1		スクリプトからメイン制御に戻る
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdPokeStatusGetResult(VM_MACHINE * core)
{
	void ** buf;
	u16 * ret_wk;

	ret_wk = VMGetWork(core);
	buf = GetEvScriptWorkMemberAdrs(core->fsys, ID_EVSCR_SUBPROC_WORK);

	GF_ASSERT(*buf != 0);

	*ret_wk = FieldPokeStatusEvent_GetPos(*buf);
//	if (*ret_wk == PL_SEL_POS_EXIT) {
//		*ret_wk = 0xff;
//	}

	sys_FreeMemoryEz(*buf);
	*buf = NULL;

	return 0;
}


//============================================================================================
//
//	ポケサーチャー関連
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * 渡されたトレーナーが再戦可能かチェック
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdRevengeTrainerSearch(VM_MACHINE * core)		
{
	u8 index,level;
	FIELD_OBJ_PTR* fldobj	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_TARGET_OBJ );
	u16 tr_id				= VMGetWorkValue(core);
	u16* ret_wk				= VMGetWork( core );

#if 0
	//現状は、機能させない！
	*ret_wk = 0;
	return 0;
#endif

	//再戦動作コードがチェック
	*ret_wk = BS_TrainerIDCheck( core->fsys, *fldobj, tr_id );
	return 0;
}


//============================================================================================
//
//	天候関連
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * 天候コードのセット
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdSetWeather( VM_MACHINE * core )
{

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 天候コードの初期化
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdInitWeather( VM_MACHINE * core )
{
#if 0
	InitFieldWeatherValue();
#endif

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 天候コードの反映
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdUpdateWeather( VM_MACHINE * core )
{
	return 1;
}


//============================================================================================
//
//	ツール関連
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * 現在のマップ位置を取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdGetMapPosition( VM_MACHINE * core )
{
#if 0
	u16 *x, *y;
	x = VMGetWork( core );
	y = VMGetWork( core );
	*x = fld->MapXpos;
	*y = fld->MapYpos;
#endif

	return 0;
}


//============================================================================================
//
//	プログラム呼び出し関連
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * @brief	サブプロセス終了待ち＋ワーク解放
 * @param	core		仮想マシン制御構造体へのポインタ
 * @return	"継続=0、終了=1"
 *
 * EvCmdWaitSubProcEndとの違いは、サブプロセスが終了したときに
 * ID_EVSCR_SUBPROC_WORKに確保したワークの解放処理があること
 */
//--------------------------------------------------------------------------------------------
static BOOL EvWaitSubProcAndFree(VM_MACHINE * core)
{
	void ** buf;
	FIELDSYS_WORK * fsys = core->fsys;
	buf = GetEvScriptWorkMemberAdrs(core->fsys, ID_EVSCR_SUBPROC_WORK);

	if( FieldEvent_Cmd_WaitSubProcEnd(fsys) ){		//サブプロセス終了待ち
		return 0;
	}
	sys_FreeMemoryEz(*buf);
	*buf = NULL;

	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	サブプロセス終了待ち＋ワーク解放（ボックス用）
 * @param	core		仮想マシン制御構造体へのポインタ
 * @return	"継続=0、終了=1"
 *
 * EvCmdWaitSubProcEndとの違いは、サブプロセスが終了したときに
 * ID_EVSCR_SUBPROC_WORKに確保したワークの解放処理があること
 */
//--------------------------------------------------------------------------------------------
static BOOL EvWaitBoxProcAndFree(VM_MACHINE * core)
{
	void ** buf;
	FIELDSYS_WORK * fsys;
	BOX_PROC_PARAM * box;

	fsys = core->fsys;
	buf  = GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_SUBPROC_WORK );
	box  = *buf;

	if( FieldEvent_Cmd_WaitSubProcEnd(fsys) ){		//サブプロセス終了待ち
		return 0;
	}

	if( box->modifiedFlag == TRUE ){
		void * fnwk;
		fnwk = FNOTE_PokemonCenterDataMake( HEAPID_WORLD );
		FNOTE_DataSave( fsys->fnote, fnwk, FNOTE_TYPE_ACTION );
	}

	sys_FreeMemoryEz(*buf);
	*buf = NULL;

	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * サブプロセス終了待ち ※外部からの参照可能にするためstaticから変更
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"継続=0、終了=1"
 */
//--------------------------------------------------------------------------------------------
BOOL EvCmdWaitSubProcEnd( VM_MACHINE * core )
{
	FIELDSYS_WORK * fsys = core->fsys;

	if( FieldEvent_Cmd_WaitSubProcEnd(fsys) ){		//サブプロセス終了待ち
		return 0;
	}

	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * フィールドプロセス復帰
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdSetMapProc(VM_MACHINE * core)
{
	EventCmd_StartFieldMap(core->fsys->event);
	return 1;
}
//--------------------------------------------------------------------------------------------
/**
 * フィールドマッププロセス終了待ち
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdFinishMapProc(VM_MACHINE * core)
{
	EventCmd_FinishFieldMap(core->fsys->event);
	return 1;
}
	
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	イメージクリップ　セーブデータ有無チェック
 *
 *	@param	fsys		ｆｓｙｓ
 *	@param	con_tv		コンテスト　テレビフラグ	IMC_PREV_TV IMC_PREV_CON
 *	@param	data_idx	セーブデータ　インデックス
 *
 *	@retval	TRUE	データある
 *	@retval	FALSE	データなし
 */
//-----------------------------------------------------------------------------
static BOOL ImageClip_SaveDataCheck( FIELDSYS_WORK * fsys, int con_tv, int data_idx )
{
	IMC_SAVEDATA* iw = SaveData_GetImcSaveData( fsys->savedata );

	// セーブ済みチェック
	if( con_tv == IMC_PREV_TV ){
		if( ImcSaveData_CheckTelevisionSaveData( iw, data_idx ) == FALSE ){
			return FALSE;
		}
	}else{
		if( ImcSaveData_CheckContestSaveData( iw, data_idx ) == FALSE ){
			return FALSE;
		}
	}
	return TRUE;
}


//----------------------------------------------------------------------------
/**
 *	@brief	Viewerデータ作成
 *
 *	@param	heap		ヒープ
 *	@param	fsys		ｆｓｙｓ
 *	@param	con_tv		コンテスト　テレビフラグ	IMC_PREV_TV IMC_PREV_CON
 *	@param	data_idx	セーブデータ　インデックス
 *	
 *	@return	ワーク
 */
//-----------------------------------------------------------------------------
static IMC_PROC_PREV_WORK* ImageClipViewer_DataMake( int heap, FIELDSYS_WORK * fsys, int con_tv, int data_idx )
{
	IMC_PROC_PREV_WORK* p_work;
	IMC_TELEVISION_SAVEDATA* p_tv;
	IMC_CONTEST_SAVEDATA* p_con;
	IMC_SAVEDATA* iw = SaveData_GetImcSaveData( fsys->savedata );

	// セーブデータ有無チェック
	if( ImageClip_SaveDataCheck( fsys, con_tv, data_idx ) == FALSE ){
		return  NULL;
	}

	// ワーク取得
	p_work = sys_AllocMemory( heap, sizeof(IMC_PROC_PREV_WORK) );
	memset( p_work, 0, sizeof(IMC_PROC_PREV_WORK) );
	
	// セーブデータ取得
	p_work->p_imc_data = iw;
	p_work->prev_type = con_tv;
	p_work->data_idx = data_idx;

	return p_work;
}


#if 0
static void ImcClip_DataDelete( IMC_PROC_WORK* imc_w )
{
	sys_FreeMemoryEz( imc_w->p_poke_para );
	sys_FreeMemoryEz( imc_w );
}
#endif

//--------------------------------------------------------------------------------------------
/**
 * ともだちコード登録イベント
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdWiFiAutoReg( VM_MACHINE * core )
{
	EventSet_WifiAutoReg( core->fsys );
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * P2P対戦マッチングボード呼び出し
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdWiFiP2PMatchEventCall( VM_MACHINE * core )
{
	EventCmd_P2PMatchProc( core->event_work );
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * P2P対戦マッチングボードの戻り値を取得、確保したメモリ削除
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdWiFiP2PMatchSetDel( VM_MACHINE * core )
{
	WIFIP2PMATCH_PROC_PARAM* param;
	void** buf		= GetEvScriptWorkMemberAdrs(core->fsys, ID_EVSCR_SUBPROC_WORK);
	u16* ret_wk		= VMGetWork( core );

	param = (*buf);
	*ret_wk = param->seq;
	OS_Printf( "WiFi P2P Match = %d\n", *ret_wk );

	sys_FreeMemoryEz( *buf );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 自分のNET_IDを返す
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdCommGetCurrentID( VM_MACHINE * core )
{
	u16* ret_wk	= VMGetWork( core );

	*ret_wk = CommGetCurrentID();
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * ポケモンウィンドウ表示
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 *
 * @li ID_EVSCR_PWORK使用！
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdPokeWindowPut( VM_MACHINE * core )
{
	void** pwork	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	u16 monsno		= VMGetWorkValue(core);
	u16 sex			= VMGetWorkValue(core);

	MenuWinGraphicSet(
		core->fsys->bgl, FLD_MBGFRM_FONT, MENU_WIN_CGX_NUM, MENU_WIN_PAL, 0, HEAPID_FIELD );

	*pwork = PokeWindowPut( core->fsys->bgl, FLD_MBGFRM_FONT, 10, 5, 
							MENU_WIN_PAL, MENU_WIN_CGX_NUM, monsno, sex, HEAPID_FIELD );

	//図鑑見たフラグをセット
	Scr_ZukanSeeSet( core->fsys, monsno );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ポケモンウィンドウ表示(POKEMON_PARAM)
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 *
 * @li ID_EVSCR_PWORK使用！
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdPokeWindowPutPP( VM_MACHINE * core )
{
	POKEMON_PARAM * poke;
	void** pwork	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	u16 pos			= VMGetWorkValue(core);

	//ポケモンへのポインタ取得
	poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(core->fsys->savedata), pos);

	MenuWinGraphicSet(
		core->fsys->bgl, FLD_MBGFRM_FONT, MENU_WIN_CGX_NUM, MENU_WIN_PAL, 0, HEAPID_FIELD );

	*pwork = PokeWindowPutPP( core->fsys->bgl, FLD_MBGFRM_FONT, 10, 5, 
							MENU_WIN_PAL, MENU_WIN_CGX_NUM, poke, HEAPID_FIELD );

	//図鑑見たフラグをセット
	Scr_ZukanSeeSet( core->fsys, PokeParaGet(poke,ID_PARA_monsno,NULL) );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ポケモンウィンドウ削除
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdPokeWindowDel( VM_MACHINE * core )
{
	u8* end_flag;
	void** pwork= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );

	end_flag	= *pwork;
	//*end_flag	= 1;
	*end_flag	= POKEWIN_CMD_END;
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * ポケモンウィンドウアニメ
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdPokeWindowAnm( VM_MACHINE * core )
{
	u8* end_flag;
	void** pwork= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );

	end_flag	= *pwork;
	//*end_flag	= 1;
	*end_flag	= POKEWIN_CMD_ANM;
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * ポケモンウィンドウアニメウェイト
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdPokeWindowAnmWait( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	u16 wk_id			= VMGetU16( core );

	//仮想マシンの汎用レジスタにワークのIDを格納
	core->reg[0] = wk_id;

	VM_SetWait( core, EvWaitPokeWindowAnmWait );
	return 1;
}

//return 1 = 終了
static BOOL EvWaitPokeWindowAnmWait(VM_MACHINE * core)
{
	u8* end_flag;
	void** pwork= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	u16* ret_wk = GetEventWorkAdrs( core->fsys, core->reg[0] );	//注意！

	end_flag	= *pwork;

	if( *end_flag == POKEWIN_CMD_MOVE ){
		return 0;
	}

	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * バトルサーチャー呼び出し
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdBtlSearcherEventCall( VM_MACHINE * core )
{
	u16 wk_id			= VMGetU16( core );
	WORDSET** wordset	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_WORDSET );

	EventCmd_BtlSearcher( core->event_work, *wordset, GetEventWorkAdrs(core->fsys,wk_id) );
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * バトルサーチャー：戦闘後に表示方向固定の動作コードをセット
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdBtlSearcherDirMvSet( VM_MACHINE * core )
{
	FIELD_OBJ_PTR* fldobj = GetEvScriptWorkMemberAdrs(core->fsys,ID_EVSCR_TARGET_OBJ);//話掛対象OBJ

	if( *fldobj != NULL ){
		BS_MvReWarClearDirMvSet( core->fsys, *fldobj );
	}

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * メッセージ登録少年
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdMsgBoyEvent( VM_MACHINE * core )
{
	MSGBOY_EventStart( core->event_work );
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * イメージクリップ呼び出し
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdImageClipSetProc( VM_MACHINE * core )
{
	u16	pos = VMGetWorkValue(core);
	u16* p_result = VMGetWork( core );
	u16	reference = VMGetWorkValue(core);

	// イベントコール
	EventCmd_ImcClipTvStart( core->fsys->event, p_result, core->fsys->savedata, pos, reference );
	return 1;
}

//----------------------------------------------------------------------------
/**
 *	@brief	テレビドレスアップビューアー
 *
 *	@param	core		仮想マシン制御構造体へのポインタ
 *
 *	@return "1"
 */
//-----------------------------------------------------------------------------
static BOOL EvCmdImageClipPreviewTvProc( VM_MACHINE * core )
{
	void** buf = GetEvScriptWorkMemberAdrs(core->fsys, ID_EVSCR_SUBPROC_WORK);
	int data_idx = VMGetU16(core);
	u16* p_work = VMGetWork( core ); 

	//イメージクリップデータ作成
	*buf = ImageClipViewer_DataMake( HEAPID_WORLD, core->fsys, IMC_PREV_TV, data_idx );

	if( *buf == NULL ){
		*p_work = 1;
		// データがまだ設定されていない
		return 1;
	}
	*p_work = 0;
	FieldImageClipViewer_SetProc( core->fsys, *buf );			//イメージクリッププロックセット
	VM_SetWait( core, EvWaitSubProcAndFree );
	return 1;
}

//----------------------------------------------------------------------------
/**
 *	@brief	コンテストドレスアップビューアー
 *
 *	@param	core		仮想マシン制御構造体へのポインタ
 *
 *	@return "1"
 */
//-----------------------------------------------------------------------------
static BOOL EvCmdImageClipPreviewConProc( VM_MACHINE * core )
{
	void** buf = GetEvScriptWorkMemberAdrs(core->fsys, ID_EVSCR_SUBPROC_WORK);
	int data_idx = VMGetU16(core);
	u16* p_work = VMGetWork( core ); 

	//イメージクリップデータ作成
	*buf = ImageClipViewer_DataMake( HEAPID_WORLD, core->fsys, IMC_PREV_CON, data_idx );

	if( *buf == NULL ){
		*p_work = 1;
		// データがまだ設定されていない
		return 1;
	}
	*p_work = 0;
	FieldImageClipViewer_SetProc( core->fsys, *buf );			//イメージクリッププロックセット
	VM_SetWait( core, EvWaitSubProcAndFree );
	return 1;
}

//----------------------------------------------------------------------------
/**
 *	@brief	テレビドレスアップ	セーブデータ有無チェック
 *
 *	@param	core		仮想マシン制御構造体へのポインタ
 *
 *	@return "1"
 */
//-----------------------------------------------------------------------------
static BOOL EvCmdImageClipTvSaveDataCheck( VM_MACHINE * core )
{
	BOOL result;
	int data_idx = VMGetU16(core);
	u16* p_work = VMGetWork( core ); 
	
	result = ImageClip_SaveDataCheck( core->fsys, IMC_PREV_TV, data_idx );

	if( result == TRUE ){
		*p_work = 1;	// あった！
		return 1;
	}
	*p_work = 0;	// なし！
	return 1;
}

//----------------------------------------------------------------------------
/**
 *	@brief	コンテストドレスアップ	セーブデータ有無チェック
 *
 *	@param	core		仮想マシン制御構造体へのポインタ
 *
 *	@return "1"
 */
//-----------------------------------------------------------------------------
static BOOL EvCmdImageClipConSaveDataCheck( VM_MACHINE * core )
{
	BOOL result;
	int data_idx = VMGetU16(core);
	u16* p_work = VMGetWork( core ); 
	
	result = ImageClip_SaveDataCheck( core->fsys, IMC_PREV_CON, data_idx );

	if( result == TRUE ){
		*p_work = 1;	// あった！
		return 1;
	}
	*p_work = 0;	// なし！
	return 1;
}

//----------------------------------------------------------------------------
/**
 *	@brief	テレビ局　タイトル　入力処理
 *
 *	@param	core		仮想マシン制御構造体へのポインタ
 *
 *	@return "1"
 */
//-----------------------------------------------------------------------------
static BOOL EvCmdImageClipTvSaveTitle( VM_MACHINE * core )
{
	u16 pms_data = VMGetWorkValue(core);
	IMC_SAVEDATA* iw = SaveData_GetImcSaveData( core->fsys->savedata );
	IMC_TELEVISION_SAVEDATA* p_tv = ImcSaveData_GetTelevisionSaveData( iw, 0 );

	ImcSaveData_SetTelevisionTitlePmsWord( p_tv, pms_data );
	
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * 地球儀呼び出し
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdWifiEarthSetProc( VM_MACHINE * core )
{
	Field_WifiEarth_SetProc( core->fsys );
	VM_SetWait( core, EvCmdWaitSubProcEnd );
	return 1;
}

//--------------------------------------------------------------
/**
 * @brief	ボールカスタマイズ用データ作成
 *
 * @param	heap	
 * @param	fsys	
 *
 * @retval	static CB_PROC_WORK*	
 *
 */
//--------------------------------------------------------------
static CB_PROC_WORK* CustomBall_CreateData( int heap, FIELDSYS_WORK * fsys )
{
	int size;
	CB_PROC_WORK* bc = NULL;
	
	size = sizeof(CB_PROC_WORK);
	
	bc = sys_AllocMemory(heap, size);
	memset(bc, 0, size);

	///< セーブデータ取得
	bc->save_data = CB_SaveData_AllDataGet(fsys->savedata);
	
	///< 手持ちポケモン取得
	{
		int i;
		int poke_cnt;
		POKEPARTY* pparty = SaveData_GetTemotiPokemon(fsys->savedata);
		poke_cnt = PokeParty_GetPokeCount(pparty);
		bc->poke_cnt = poke_cnt;
		for (i = 0; i < poke_cnt; i++){
			bc->poke_para[i] = PokeParty_GetMemberPointer(pparty, i);
		}
		for ( ; i < TEMOTI_POKEMAX; i++){
			bc->poke_para[i] = NULL;
		}
	}
	
	return bc;
}

//--------------------------------------------------------------------------------------------
/**
 * 	ボールカスタマイズ呼び出し
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdCustomBallEventCall( VM_MACHINE * core )
{
	EventCmd_CustomBallEditProc(core->event_work, core->fsys->savedata);
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * タウンマップBGモード呼び出し
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdTMapBGSetProc( VM_MACHINE * core )
{
	TOWNMAP_PARAM* tp;
	void** buf = GetEvScriptWorkMemberAdrs(core->fsys, ID_EVSCR_SUBPROC_WORK);
	
	*buf = sys_AllocMemory(HEAPID_WORLD, sizeof(TOWNMAP_PARAM));

	FieldTMap_CallDataSet(core->fsys,*buf,TMAP_MBG);
	FieldTMap_SetProc( core->fsys, *buf );
	VM_SetWait( core, EvWaitSubProcAndFree );
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * まぜまぜ料理呼び出し(ローカル)
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdNutMixerProc( VM_MACHINE * core )
{
	u8	mode;
	TOWNMAP_PARAM* tp;
	void** buf = GetEvScriptWorkMemberAdrs(core->fsys, ID_EVSCR_SUBPROC_WORK);
	
	mode = VMGetU16(core);
	
	*buf = FieldNutMixer_InitCall(core->fsys,mode,HEAPID_WORLD);
	VM_SetWait( core, EvWaitSubProcAndFree );
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * まぜまぜ料理をプレイできる状態であるかチェックする
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdNutMixerPlayStateCheck(VM_MACHINE* core)
{
	u16 *ret_wk = GetEventWorkAdrs( core->fsys,VMGetU16(core));

	//木の実を持っているかチェック
	if(!MyItem_CheckItemPocket(SaveData_GetMyItem(core->fsys->savedata),BAG_POKE_NUTS)){
		*ret_wk = 1;
		return 0;
	}
	//ポルトケースがいっぱいでないかチェック
	if(PORUTO_GetDataNum(SaveData_GetPorutoBlock(core->fsys->savedata)) >= PORUTO_STOCK_MAX){
		*ret_wk = 2;
		return 0;
	}

	//プレイできる
	*ret_wk = 0;
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * タワーアプリ呼び出し
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdBTowerAppSetProc( VM_MACHINE * core )
{
	BTOWER_APP_PARAM* ap;
	u16	main = VMGetWorkValue(core);
	u16	sub = VMGetWorkValue(core);

	void** buf = GetEvScriptWorkMemberAdrs(core->fsys, ID_EVSCR_SUBPROC_WORK);
	
	*buf = sys_AllocMemory(HEAPID_WORLD, sizeof(BTOWER_APP_PARAM));

	ap = (BTOWER_APP_PARAM*)*buf;
	MI_CpuClear8(ap,sizeof(BTOWER_APP_PARAM));

	ap->mainMode = main;
	ap->subMode = sub;
	ap->save = core->fsys->savedata;

	BTowerApp_SetProc( core->fsys, *buf );
	VM_SetWait( core, EvWaitSubProcAndFree );
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * ボックス呼び出し
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdBoxSetProc( VM_MACHINE * core )
{
	void** buf				= GetEvScriptWorkMemberAdrs(core->fsys, ID_EVSCR_SUBPROC_WORK);
	BOX_PROC_PARAM* param	= sys_AllocMemory( HEAPID_WORLD, sizeof(BOX_PROC_PARAM) );

	param->savedata			= core->fsys->savedata;
	param->mode				= VMGetU8(core);
	*buf = param;

	FieldBox_SetProc( core->fsys, *buf );					//ボックスプロックセット
	VM_SetWait( core, EvWaitBoxProcAndFree );
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * おえかき呼び出し
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdOekakiBoardSetProc( VM_MACHINE * core )
{
	FIELDSYS_WORK * fsys = core->fsys;

	OekakiBoard_SetProc( fsys );
	VM_SetWait( core, EvCmdWaitSubProcEnd );
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * トレーナーカード呼び出し	(他人のカード参照用)
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdCallTrCard( VM_MACHINE * core )
{
	TRCSET_SetupTrCardEvent(core->fsys);
/**	
	TR_CARD_DATA * cd;
	

	void ** buf;
	buf = GetEvScriptWorkMemberAdrs(core->fsys, ID_EVSCR_SUBPROC_WORK);

	*buf = TRCSET_AllocTrainerCardData( HEAPID_WORLD );
//	*buf = (TR_CARD_DATA*)Union_GetTrainerCardWorkPtr(core->fsys->union_work);
	TRCSET_MakeTrainerInfo(0, 0, 0, core->fsys, *buf);

	FieldTrCard_SetProc( core->fsys, *buf );
	VM_SetWait( core, EvWaitSubProcAndFree );
*/	
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * こうかん呼び出し
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdTradeListSetProc( VM_MACHINE * core )
{
	EventCmd_UnionTrade(core->fsys->event);
	return 1;
#if 0
	FIELDSYS_WORK * fsys = core->fsys;
	void ** buf;
	buf = GetEvScriptWorkMemberAdrs(core->fsys, ID_EVSCR_SUBPROC_WORK);

	*buf = TradeList_SetProc( fsys );
	VM_SetWait( core, EvWaitSubProcAndFree );
	return 1;
#endif
}

//--------------------------------------------------------------------------------------------
/**
 * レコードコーナー呼び出し
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdRecordCornerSetProc( VM_MACHINE * core )
{
	void** buf				= GetEvScriptWorkMemberAdrs(core->fsys, ID_EVSCR_SUBPROC_WORK);
	*buf = RecordCorner_SetProc( core->fsys );
	//VM_SetWait( core, EvCmdWaitSubProcEnd );
	VM_SetWait( core, EvWaitSubProcAndFree );
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * 殿堂入り呼び出し
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdDendouSetProc( VM_MACHINE * core )
{
	EventCmd_GameClear(core->fsys->event);
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * パソコン殿堂入り呼び出し
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdPcDendouSetProc( VM_MACHINE * core )
{
	void** buf				= GetEvScriptWorkMemberAdrs(core->fsys, ID_EVSCR_SUBPROC_WORK);
	*buf = Field_DendouPC_Call(core->fsys);
#ifdef	PM_DEBUG
	//不要なはずだが、エラー対処
	if (*buf == NULL) {
		return 0;
	}
#endif
	VM_SetWait(core, EvWaitSubProcAndFree);
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * 世界交換画面呼び出し
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdWorldTradeSetProc( VM_MACHINE * core )
{
	u16 no		= VMGetWorkValue(core);
	u16* ret_wk = VMGetWork(core);

	if( mydwc_checkMyGSID(core->fsys->savedata) ){
		*ret_wk = 1;	//成功
		Field_WorldTrade_SetProc( core->fsys, no );
		VM_SetWait( core, EvCmdWaitSubProcEnd );
	}else{
		*ret_wk = 0;	//失敗
	}

	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * WIFI接続し初回ID取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdDPWInitProc( VM_MACHINE * core )
{
	u16 wk_id	= VMGetU16( core );

	//EventCmd_DPWInitProc( core->event_work );
	EventCmd_DPWInitProc2( core->event_work , GetEventWorkAdrs(core->fsys,wk_id) );
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * 最初のポケモン選択画面呼び出し
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdFirstPokeSelectProc( VM_MACHINE * core )
{
	EV_POKESELECT_PEARENT_DATA* pokesel;
	void** pwork = GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );

	//ペアレントデータ作成
	*pwork = sys_AllocMemory( HEAPID_WORLD, sizeof(EV_POKESELECT_PEARENT_DATA) );
	pokesel = *pwork;
	pokesel->cp_config = SaveData_GetConfig( core->fsys->savedata );

	Field_EVPokeSelect_SetProc( core->fsys, *pwork );

	VM_SetWait( core, EvCmdWaitSubProcEnd );
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * 最初のポケモン選択画面で選択したポケモンナンバーを取得して、確保したメモリ削除
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdFirstPokeSelectSetAndDel( VM_MACHINE * core )
{
	EV_POKESELECT_PEARENT_DATA* first_poke;
	void** pwork	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );

	first_poke = (*pwork);

	SysWork_FirstPokeNoSet( SaveData_GetEventWork(core->fsys->savedata),first_poke->select_monsno );
	sys_FreeMemoryEz( *pwork );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	バッグ画面のよびだし
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdBagSetProc( VM_MACHINE * core )
{
	void ** buf;
	u8 mode;
	if (VMGetU8(core) == 0) {
		mode = EVBAG_MODE_NORMAL_ONLY;
	} else {
		mode = EVBAG_MODE_KINOMI_ONLY;
	}
	buf = GetEvScriptWorkMemberAdrs(core->fsys, ID_EVSCR_SUBPROC_WORK);
	GF_ASSERT(*buf == 0);
	*buf = FieldBagEvent_SetProc(core->fsys, mode);

	VM_SetWait( core, EvCmdWaitSubProcEnd );
	return 1;
}
//--------------------------------------------------------------------------------------------
/**
 * @brief	バッグ画面での結果取得
 * @param	core		仮想マシン制御構造体へのポインタ
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdBagGetResult( VM_MACHINE * core)
{
	u16 * ret_wk;
	void ** buf;
	ret_wk = VMGetWork(core);
	buf = GetEvScriptWorkMemberAdrs(core->fsys, ID_EVSCR_SUBPROC_WORK);
	GF_ASSERT(*buf != 0);
	*ret_wk = FieldBagEvent_GetSelectedItem(*buf);
	sys_FreeMemoryEz(*buf);
	*buf = NULL;
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 名前入力呼び出し
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdNameIn( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;

	EventCmd_NameIn( core->event_work, NAMEIN_MYNAME, 0, NAMEIN_PERSON_LENGTH, 0, NULL, VMGetWork(core) );
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * ポケモン名前入力呼び出し
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdNameInPoke( VM_MACHINE * core )
{
	STRCODE msg_buf[MONS_NAME_SIZE*2];		//サイズ確認！
	POKEMON_PARAM * poke;
	FIELDSYS_WORK* fsys = core->fsys;
	u16 pos				= VMGetWorkValue(core);

	//ポケモンへのポインタ取得
	poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(fsys->savedata), pos);

	//ニックネーム取得
	PokeParaGet(poke, ID_PARA_nickname, msg_buf);

	EventCmd_NameIn(core->event_work, NAMEIN_POKEMON,PokeParaGet(poke,ID_PARA_monsno,NULL), 
			NAMEIN_POKEMON_LENGTH, pos, msg_buf, VMGetWork(core) );
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * 石碑名前入力呼び出し
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdNameInStone( VM_MACHINE * core )
{
	EventCmd_NameIn(core->event_work, NAMEIN_STONE, 
					0, MONUMENT_NAME_SIZE, 0, NULL, VMGetWork(core) );
	return 1;
}

//============================================================================================
//============================================================================================
//--------------------------------------------------------------
/**
 * @brief	簡易会話入力呼び出し（1単語）
 */
//--------------------------------------------------------------
static BOOL EvCmdPMSInputSingleProc(VM_MACHINE * core)
{
	u16 dmy = VMGetWorkValue(core);		//説明文分岐のためのダミー
	u16 * ret_wk = VMGetWork(core);
	u16 * ans_wk = VMGetWork(core);
	*ans_wk = PMS_WORD_NULL;
	EventCmd_PMSInput(core->fsys->event, ret_wk, ans_wk, NULL);
	return 1;
}

//--------------------------------------------------------------
/**
 * @brief	簡易会話入力呼び出し（2単語）
 */
//--------------------------------------------------------------
static BOOL EvCmdPMSInputDoubleProc(VM_MACHINE * core)
{
	u16 dmy = VMGetWorkValue(core);		//説明文分岐のためのダミー
	u16 * ret_wk = VMGetWork(core);
	u16 * ans_wk1 = VMGetWork(core);
	u16 * ans_wk2 = VMGetWork(core);
	*ans_wk1 = PMS_WORD_NULL;
	*ans_wk2 = PMS_WORD_NULL;
	EventCmd_PMSInput(core->fsys->event, ret_wk, ans_wk1, ans_wk2);
	return 1;
}

//--------------------------------------------------------------
/**
 * @brief	簡易会話の単語をバッファへ
 */
//--------------------------------------------------------------
static BOOL EvCmdPMSBuf(VM_MACHINE * core)
{
	WORDSET** wordset	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_WORDSET );
	u16 buf_num = VMGetWorkValue(core);
	PMS_WORD word = VMGetWorkValue(core);

	WORDSET_RegisterPMSWord(*wordset,buf_num,word );

	return 0;
}

//============================================================================================
//
//	ワイプフェード関連
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * ワイプフェードスタート
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 *
 * 注意！　フェードにかかるLCD、BG面の設定は固定にしている
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdWipeFadeStart( VM_MACHINE * core )
{
	u16 div				= VMGetU16(core);		//各ワイプ処理の分割数
	u16 sync			= VMGetU16(core);		//各ワイプの処理を分割した１片のシンク数
	u16 type			= VMGetU16(core);		//タイプ
	u16 color			= VMGetU16(core);		//カラー

	WIPE_SYS_Start( WIPE_PATTERN_WMS, type, type, color, div, sync, HEAPID_FIELD );

	//ウィンドウマスク状態を解除
	WIPE_ResetWndMask( WIPE_DISP_MAIN );
	WIPE_ResetWndMask( WIPE_DISP_SUB );

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ワイプフェード終了チェック
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 *
 * 注意！　チェックするLCDの設定は固定にしている
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdWipeFadeCheck( VM_MACHINE * core )
{
	VM_SetWait( core, EvWaitWipeFadeCheck );
	return 1;
}

//return 1 = 終了
static BOOL EvWaitWipeFadeCheck(VM_MACHINE * core)
{
	if( WIPE_SYS_EndCheck() == TRUE ){
		return 1;
	}

	return 0;
}


//============================================================================================
//
//	マップ遷移関連
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * マップ遷移
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdMapChange( VM_MACHINE * core )
{
//	u16 zone_id,door_id,x,z,dir;
	u16 zone_id,x,z,dir;
	s16 door_id;
	FIELDSYS_WORK * fsys = core->fsys;

	zone_id = VMGetU16(core);
	door_id = VMGetU16(core);
	x		= VMGetWorkValue(core);
	z		= VMGetWorkValue(core);
	dir		= VMGetU16(core);
	door_id = DOOR_ID_JUMP_CODE;

	EventCmd_MapChangeFull(core->event_work, zone_id, door_id, x, z, dir );
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * マップ遷移(コロシアム)イン
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdColosseumMapChangeIn( VM_MACHINE * core )
{
//	u16 zone_id,door_id,x,z,dir;
	u16 zone_id,x,z,dir;
	s16 door_id;
	FIELDSYS_WORK * fsys = core->fsys;

	zone_id = VMGetU16(core);
	door_id = VMGetU16(core);
	x		= VMGetWorkValue(core);
	z		= VMGetWorkValue(core);
	dir		= VMGetU16(core);
	door_id = DOOR_ID_JUMP_CODE;

    
	EventCmd_ColosseumMapChangeIn(core->fsys->event, zone_id, door_id, x, z, dir );
	//EventCmd_MapChangeFull(core->event_work, zone_id, door_id, x, z, dir );
	return 1;
}
//--------------------------------------------------------------------------------------------
/**
 * マップ遷移(コロシアム)アウト
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdColosseumMapChangeOut( VM_MACHINE * core )
{
	EventCmd_ColosseumMapChangeOut( core->fsys->event );
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * 前のゾーンIDを取得する
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdGetBeforeZoneID( VM_MACHINE * core)
{
	SITUATION* sit			= SaveData_GetSituation( core->fsys->savedata );
	LOCATION_WORK* before	= Situation_GetBeforeLocation( sit );
	u16 * ret_wk			= VMGetWork(core);

	OS_Printf( "before->zone_id = %d\n", before->zone_id );
	*ret_wk = before->zone_id;
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 現在のゾーンIDを取得する
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdGetNowZoneID( VM_MACHINE * core)
{
	u16 * ret_wk = VMGetWork(core);
	*ret_wk = core->fsys->location->zone_id;
	return 0;
}

//============================================================================================
//
//	秘伝技関連
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * 壁のぼり
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdKabeNobori( VM_MACHINE * core )
{
	EventCmd_KabeNoboriCall( core->event_work, 
								Player_DirGet(core->fsys->player), VMGetWorkValue(core) );
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * なみのり
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdNaminori( VM_MACHINE * core )
{
	//なみのり使用で揺れ草状態クリア
	SwayGrass_InitSwayGrass(core->fsys->SwayGrass);
	EventCmd_NaminoriCall( core->event_work, 
								Player_DirGet(core->fsys->player), VMGetWorkValue(core) );
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * たきのぼり
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdTakinobori( VM_MACHINE * core )
{
	EventCmd_TakiNoboriCall( core->event_work, 
								Player_DirGet(core->fsys->player), VMGetWorkValue(core) );
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * そらをとぶ
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdSorawotobu( VM_MACHINE * core )
{
	u16 zone_id,x,z;

	zone_id = VMGetU16(core);
	x		= VMGetWorkValue(core);
	z		= VMGetWorkValue(core);

	EventSet_MapChangeBySky( core->fsys, zone_id, DOOR_ID_JUMP_CODE, x, z, DIR_DOWN );
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	秘伝わざ：フラッシュ
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdHidenFlash(VM_MACHINE * core)
{
	SITUATION * sit = SaveData_GetSituation(core->fsys->savedata);
	Situation_SetWeatherID(sit, WEATHER_SYS_SUNNY);
	WEATHER_ChengeReq(core->fsys->fldmap->weather_data, Situation_GetWeatherID(sit));

	return 1;
}
//--------------------------------------------------------------------------------------------
/**
 * @brief	秘伝わざ：きりばらい
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdHidenKiribarai(VM_MACHINE * core)
{
	SITUATION * sit = SaveData_GetSituation(core->fsys->savedata);
	Situation_SetWeatherID(sit, WEATHER_SYS_SUNNY);
	WEATHER_ChengeReq(core->fsys->fldmap->weather_data, Situation_GetWeatherID(sit));

	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * カットイン
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 *
 * @li ID_EVSCR_PWORK使用！
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdCutIn( VM_MACHINE * core )
{
	POKEMON_PARAM * poke;
	void** pwork	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	u16 pos			= VMGetWorkValue(core);

	//ポケモンへのポインタ取得
	poke = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(core->fsys->savedata), pos );

	*pwork = FieldCutIn_Init(
			core->fsys, CUTIN_TYPE_HIDEN, 
			poke, Player_SexGet(core->fsys->player) );

	VM_SetWait( core, EvWaitCutIn );
	return 1;
}

//return 1 = 終了
static BOOL EvWaitCutIn(VM_MACHINE * core)
{
	void** pwork	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );

	if( FieldCutIn_EndCheck(*pwork) == TRUE ){ 
		FieldCutIn_End( *pwork );
		return 1;
	}

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * コンテスト着替え
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdConHeroChange( VM_MACHINE * core )
{
	EventCmd_ContestHeroChange( core->event_work );
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * 自転車に乗っているかチェック
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdBicycleCheck( VM_MACHINE * core )
{
	u16* ret_wk	= VMGetWork( core );

	if( Player_FormGet(core->fsys->player) == HERO_FORM_CYCLE ){
		*ret_wk = 1;
	}else{
		*ret_wk = 0;
	}

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 自転車、歩行形態に変更
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdBicycleReq( VM_MACHINE * core )
{
	u8 flag	= VMGetU8( core );

	if( flag == 1 ){
		//先にBGM処理を呼んでから、形状を自転車にする！(060803)
		Snd_FieldBgmSetSpecial( core->fsys, SEQ_BICYCLE );				//セット
		Snd_FadeOutNextPlayCall( core->fsys, SEQ_BICYCLE, BGM_FADE_FIELD_MODE );
		Player_RequestSet( core->fsys->player, HERO_REQBIT_CYCLE );		//自転車
		Player_Request( core->fsys->player );
	}else{
		//先に形状を戻してから、BGM処理を呼ぶ！(060803)
		Player_RequestSet( core->fsys->player, HERO_REQBIT_NORMAL );	//歩行
		Player_Request( core->fsys->player );
		Snd_FieldBgmSetSpecial( core->fsys, 0 );						//クリア
		Snd_FadeOutNextPlayCall(core->fsys, 
								Snd_FieldBgmNoGet(core->fsys,core->fsys->location->zone_id), 
								BGM_FADE_FIELD_MODE );
	}

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 自転車形態に変更(BGMは変更しない、マップ有効フラグは立つ)
 * このコマンドの後に「_BGM_PLAY	SEQ_BICYCLE」を呼ぶ
 * サイクリングロード専用
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdBicycleReqNonBgm( VM_MACHINE * core )
{
	//--------------------------------------------------
	//自転車曲のフェードがかわるので使用不可！(060803)
	//--------------------------------------------------

	Player_RequestSet( core->fsys->player, HERO_REQBIT_CYCLE );		//自転車
	Snd_FieldBgmSetSpecial( core->fsys, SEQ_BICYCLE );				//セット

	//BGM切替は呼ばない！
	//Snd_FadeOutNextPlayCall( core->fsys, SEQ_BICYCLE, BGM_FADE_FIELD_MODE );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * サイクリングロードセット
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdCyclingRoadSet( VM_MACHINE * core )
{
	Player_MoveBitSet_CyclingRoad( core->fsys->player, VMGetU8(core) );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 自機の形態を取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdPlayerFormGet( VM_MACHINE * core )
{
	u16* ret_wk	= VMGetWork( core );
	*ret_wk = Player_FormGet( core->fsys->player );
	OS_Printf( "player form ret_wk = %d\n", *ret_wk );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 自機へリクエスト
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdPlayerReqBitOn( VM_MACHINE * core )
{
	u16 bit	= VMGetU16( core );
	Player_RequestBit_ON( core->fsys->player, bit );
	return 1;
}
//--------------------------------------------------------------------------------------------
/**
 * 自機リクエスト実行
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdPlayerReqStart( VM_MACHINE * core )
{
	Player_Request( core->fsys->player );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 大量発生ゾーンを取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdGenerateInfoGet(VM_MACHINE * core ) 
{
	ENC_SV_PTR data = EncDataSave_GetSaveDataPtr(core->fsys->savedata);
	u16* ret_zone		= VMGetWork( core );
	u16* ret_poke		= VMGetWork( core );

	GenerateZone_GetInfo( EncDataSave_GetRandSeed(data, ENC_RND_SEED_GENERATE), ret_zone, ret_poke );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 最初のポケモンナンバー取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdFirstPokeNoGet(VM_MACHINE * core )
{
	u16* ret_wk	= VMGetWork( core );

	*ret_wk = SysWork_FirstPokeNoGet( SaveData_GetEventWork(core->fsys->savedata) );
	return 0;
}


//============================================================================================
//
//	戦闘関連(実験中)
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * トレーナー会話呼び出し
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdTrainerMessageSet( VM_MACHINE * core )
{
	FIELDSYS_WORK * fsys	= core->fsys;
	u16* script_id			= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_SCRIPT_ID );
	STRBUF** pbuf			= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_MSGBUF );
	u8* win_open_flag		= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WIN_OPEN_FLAG );
	u8* msg_index			= GetEvScriptWorkMemberAdrs( fsys,ID_EVSCR_MSGINDEX );
	u16 tr_id				= VMGetWorkValue(core);
	u16 kind_id				= VMGetWorkValue(core);

	TT_TrainerMessageGet( tr_id, kind_id, *pbuf, HEAPID_WORLD );

	//メッセージクリア
	GF_BGL_BmpWinDataFill( GetEvScriptWorkMemberAdrs(fsys, ID_EVSCR_MSGWINDAT), (FBMP_COL_WHITE) );

	*msg_index = FieldTalkMsgStart( GetEvScriptWorkMemberAdrs(fsys,ID_EVSCR_MSGWINDAT),
									*pbuf, SaveData_GetConfig(core->fsys->savedata), 1 );

	VM_SetWait( core, TalkMsgWait );
	return 1;
}


//============================================================================================
//
//	通信関連
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * 親機を選択するウィンドウを開く
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdConnectSelParentWin( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	u16 mode			= VMGetWorkValue(core);	//battle_mode
	u16 type			= VMGetWorkValue(core);	//regulation_type
	u16 type2			= VMGetWorkValue(core);	//
	u16 wk_id			= VMGetU16( core );

	CommSelectParentWindowOpen( fsys, mode, type, type2 );

	//仮想マシンの汎用レジスタにワークのIDを格納
	core->reg[0] = wk_id;

	VM_SetWait( core, EvWaitConnectSelParentWin );
	return 1;
}

//return 1 = 終了
static BOOL EvWaitConnectSelParentWin( VM_MACHINE * core )
{
	u32 ret;
	FIELDSYS_WORK* fsys = core->fsys;
	u16* ret_wk			= GetEventWorkAdrs( fsys, core->reg[0] );	//注意！

	ret = CommSelectParentWindowCheck();
	if( ret == COMM_RETVAL_NULL ){
		return 0;					//選択中
	}

	*ret_wk = ret;					//戻り値格納
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * 子機を選択するウィンドウを開く
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdConnectSelChildWin( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	u16 mode			= VMGetWorkValue(core);	//battle_mode
	u16 type			= VMGetWorkValue(core);	//regulation_type
	u16 type2			= VMGetWorkValue(core);	//
	u16 wk_id			= VMGetU16( core );

	CommChildWindowOpen( fsys, mode, type, type2 );

	//仮想マシンの汎用レジスタにワークのIDを格納
	core->reg[0] = wk_id;

	VM_SetWait( core, EvWaitConnectSelChildWin );
	return 1;
}

//return 1 = 終了
static BOOL EvWaitConnectSelChildWin( VM_MACHINE * core )
{
	u32 ret;
	FIELDSYS_WORK* fsys = core->fsys;
	u16* ret_wk			= GetEventWorkAdrs( fsys, core->reg[0] );	//注意！

	ret = CommChildWindowCheck();
	if( ret == COMM_RETVAL_NULL ){
		return 0;					//選択中
	}

	*ret_wk = ret;					//戻り値格納
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * デバック親機を選択するウィンドウを開く
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdConnectDebugParentWin( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	u16 wk_id			= VMGetU16( core );

#ifdef PM_DEBUG
	CommDirectParent_Debug( fsys );

	//仮想マシンの汎用レジスタにワークのIDを格納
	core->reg[0] = wk_id;

	VM_SetWait( core, EvWaitConnectSelParentWin );
#endif
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * デバック子機を選択するウィンドウを開く
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdConnectDebugChildWin( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	u16 wk_id			= VMGetU16( core );

#ifdef PM_DEBUG
	CommDirectChild_Debug( fsys );

	//仮想マシンの汎用レジスタにワークのIDを格納
	core->reg[0] = wk_id;

	VM_SetWait( core, EvWaitConnectSelChildWin );
#endif
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * デバック用　通信戦闘呼び出し
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdDebugSioEncount( VM_MACHINE * core )
{
	PLIST_DATA * pld;
	void ** buf;
	buf = GetEvScriptWorkMemberAdrs(core->fsys, ID_EVSCR_SUBPROC_WORK);
	pld = *buf;
	EventCmd_TemotiListBattle(core->fsys->event, pld->in_num, FIGHT_TYPE_1vs1_SIO);
	sys_FreeMemoryEz(pld);
	*buf = NULL;
	//u8 * array = sys_AllocMemoryLo(HEAPID_EVENT, sizeof(u8) * 6);
	//EventCmd_TemotiListBattle(core->fsys->event, array, FIGHT_TYPE_1vs1_SIO);
	//sys_FreeMemoryEz(array);
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * デバック用　通信コンテスト呼び出し
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdDebugSioContest( VM_MACHINE * core )
{
//	FIELDSYS_WORK* fsys = core->fsys;
	
	//ContestActin_FieldConnectStart(fsys);

	EventCmd_ContestSioProc(core->event_work);
	return 1;
}


//============================================================================================
//
//	特殊接続関連
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * 特殊接続情報のセット
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdSpLocationSet( VM_MACHINE * core )
{
	LOCATION_WORK lw;

	lw.zone_id	= VMGetWorkValue( core );
	lw.door_id	= VMGetWorkValue( core );
	lw.grid_x	= VMGetWorkValue( core );
	lw.grid_z	= VMGetWorkValue( core );
	lw.dir		= VMGetWorkValue( core );

	Situation_SetSpecialLocation( SaveData_GetSituation(core->fsys->savedata), &lw );
	return 0;
}


//============================================================================================
//
//	エレベータ関連
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * 特殊接続先から、現在のフロアナンバーを取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdElevatorNowFloorGet( VM_MACHINE * core )
{
	LOCATION_WORK* location;
	u16* wk				= VMGetWork( core );

	location = Situation_GetSpecialLocation( SaveData_GetSituation(core->fsys->savedata) );

	//特殊接続先から、現在のフロアナンバーを取得
	*wk = ElevatorNowFloorGet( location->zone_id );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 現在のフロアナンバーを表示
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdElevatorFloorWrite( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	WORDSET** wordset	= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WORDSET );
	u8 x				= VMGetU8(core);
	u8 y				= VMGetU8(core);
	u16* wk				= VMGetWork(core);

	ElevatorFloorWrite( fsys, x, y, wk, *wordset );
	return 0;
}


//============================================================================================
//
//	図鑑評価関連
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * シンオウ図鑑　見つけた数を取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdGetShinouZukanSeeNum( VM_MACHINE * core )
{
	const ZUKAN_WORK* zw = SaveData_GetZukanWork( core->fsys->savedata );
	u16* ret_wk	= VMGetWork( core );

	*ret_wk = ZukanWork_GetShinouPokeSeeCount(zw);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * シンオウ図鑑　捕まえた数を取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdGetShinouZukanGetNum( VM_MACHINE * core )
{
	const ZUKAN_WORK* zw = SaveData_GetZukanWork( core->fsys->savedata );
	u16* ret_wk	= VMGetWork( core );

	*ret_wk = ZukanWork_GetShinouPokeGetCount(zw);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 全国図鑑　見つけた数を取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdGetZenkokuZukanSeeNum( VM_MACHINE * core )
{
	const ZUKAN_WORK* zw = SaveData_GetZukanWork( core->fsys->savedata );
	u16* ret_wk	= VMGetWork( core );

	*ret_wk = ZukanWork_GetPokeSeeCount(zw);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 全国図鑑　捕まえた数を取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdGetZenkokuZukanGetNum( VM_MACHINE * core )
{
	const ZUKAN_WORK* zw = SaveData_GetZukanWork( core->fsys->savedata );
	u16* ret_wk	= VMGetWork( core );

	*ret_wk = ZukanWork_GetPokeGetCount(zw);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 全国図鑑かチェック
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdChkZenkokuZukan( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;

	//*ret_wk = (u16)ZukanSpecialFlagCheck();
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 評価メッセージID取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdGetZukanHyoukaMsgID( VM_MACHINE * core )
{
	const ZUKAN_WORK* zw= SaveData_GetZukanWork( core->fsys->savedata );
	const MYSTATUS *my = SaveData_GetMyStatus(core->fsys->savedata);
	u8 mode				= VMGetU8(core);
	u16* ret_wk			= VMGetWork( core );
	u16 num;

	if( mode == 0 ){
		num = ZukanWork_GetShinouSeeCompCount( zw );
		*ret_wk = GetShinouZukanHyoukaMsgID( num ,
			SysFlag_ArriveGet(SaveData_GetEventWork(core->fsys->savedata),FLAG_ARRIVE_C04));
	}else{
		num = ZukanWork_GetZenkokuGetCompCount( zw );
		*ret_wk = GetZenkokuZukanHyoukaMsgID( num , MyStatus_GetMySex(my));
	}

	return 0;
}


//============================================================================================
//
//	野生戦闘関連
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * ポケモンナンバーとレベルを指定して野生戦闘呼び出し
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdWildBattleSet( VM_MACHINE * core )
{
	BOOL* win_flag	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_WIN_FLAG );
	u16 monsno		= VMGetWorkValue(core);
	u8 level		= (u8)VMGetWorkValue(core);

	//イベントコールなので、スクリプトに復帰します。
	EventCmd_WildBattle( core->event_work, monsno, level, win_flag,FALSE );

	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * ポケモンナンバーとレベルを指定して特殊ポケモンイベント野生戦闘呼び出し
 * ※ノーマルとはエンカウントメッセージが違います
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdSpWildBattleSet( VM_MACHINE * core )
{
	BOOL* win_flag	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_WIN_FLAG );
	u16 monsno		= VMGetWorkValue(core);
	u8 level		= (u8)VMGetWorkValue(core);

	//イベントコールなので、スクリプトに復帰します。
	EventCmd_WildBattle( core->event_work, monsno, level, win_flag,TRUE );

	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * 最初のイベント戦闘呼び出し
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdFirstBattleSet( VM_MACHINE * core )
{
	//BOOL* win_flag	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_WIN_FLAG );
	u16 monsno		= VMGetWorkValue(core);
	u8 level		= (u8)VMGetWorkValue(core);

	//イベントコールなので、スクリプトに復帰します。
	EventCmd_FirstBattle( core->event_work, monsno, level );

	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * 捕獲デモのイベント戦闘呼び出し
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdCaptureBattleSet( VM_MACHINE * core )
{
	EventCmd_CaptureDemo( core->event_work );
	return 1;
}


//============================================================================================
//
//	ハニーツリー関連
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * ハニーツリー
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdHoneyTree( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	HTE_SetupNowLocHoneyTree(fsys);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ハニーツリーステート取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdGetHoneyTreeState( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	u16* ret_wk			= VMGetWork( core );

	//現在の自機のゾーンIDを取得し、それに対応する蜜木を特定する
	*ret_wk = HTE_GetNowLocHoneyTreeState(fsys);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 蜜塗り戦闘呼び出し
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdHoneyTreeBattleSet( VM_MACHINE * core )
{
	FIELDSYS_WORK * fsys = core->fsys;
	BOOL * win_flag			= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WIN_FLAG );

	//イベントコールなので、スクリプトに復帰します。
	EventCmd_HoneyTreeBattle( core->event_work ,win_flag );

	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * 蜜塗り戦闘終了後処理
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdHoneyAfterTreeBattleSet( VM_MACHINE * core )
{
	FIELDSYS_WORK * fsys = core->fsys;

	//イベントコールなので、スクリプトに復帰します。
	OS_Printf("戦闘後に呼び出し\n");
	HTE_SetHoneyTreeInfoAfterBtl(fsys);

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * サイン呼び出し
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdTSignSetProc( VM_MACHINE * core )
{
	Field_MySign_SetProc( core->fsys );
	VM_SetWait( core, EvCmdWaitSubProcEnd );
	return 1;
}


//============================================================================================
//
//	レポートセーブ関連
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * レポートデータチェック
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdReportSaveCheck( VM_MACHINE * core )
{
	SAVEDATA * savedata = core->fsys->savedata;
	u16* ret_wk			= VMGetWork( core );

	if (SaveData_IsOverwritingOtherData(savedata)) {
		//「さいしょから」で既にセーブデータが存在する場合＝書き込み禁止
		*ret_wk = 0;
	} else if (SaveData_GetExistFlag(savedata) == FALSE) {
		//セーブデータが存在しない＝初回セーブ（全体セーブ）
		*ret_wk = 1;
	} else if (SaveData_GetTotalSaveFlag(savedata)) {
		//セーブデータが存在して、全体セーブの場合
		*ret_wk = 2;
	} else {
		//セーブデータが存在して、部分セーブの場合
		*ret_wk = 3;
	}

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * レポート書き込み
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdReportSave( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	u16 * ret_wk = VMGetWork(core);
	*ret_wk = Field_Save(fsys);
	return 0;
}


//============================================================================================
//
//	ポケッチ関連
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * ポケッチゲット
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdGetPoketch( VM_MACHINE * core )
{
	EventCmd_GetPoketch( core->event_work );
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * ポケッチ入手済みフラグ取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdGetPoketchFlag( VM_MACHINE * core )
{
	POKETCH_DATA* pd = SaveData_GetPoketchData( core->fsys->savedata );
	u16* ret_wk			= VMGetWork( core );
	*ret_wk = PoketchData_GetPoketchGetFlag( pd );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ポケッチソフト追加
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdPoketchAppAdd( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	u16 app_id			= VMGetWorkValue(core);

	PoketchData_AddApplication(SaveData_GetPoketchData(fsys->savedata),app_id);

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ポケッチソフト追加済みかチェック
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdPoketchAppCheck( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	u16 app_id			= VMGetWorkValue(core);
	u16* ret_wk			= VMGetWork( core );

	*ret_wk = PoketchData_CheckApplicationRegisterd(SaveData_GetPoketchData(fsys->savedata),app_id);
	return 0;
}

//============================================================================================
//
//	通信関連
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * タイミングコマンドを発行する
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdCommTimingSyncStart( VM_MACHINE * core )
{
	u16 no = VMGetWorkValue( core );

	//仮想マシンの汎用レジスタにワークのIDを格納
	core->reg[0] = no;

	CommTimingSyncStart( no );

	VM_SetWait( core, EvWaitCommIsTimingSync );

	OS_Printf("同期待ち　番号＝%d\n",no);

	return 1;
}

//return 1 = 終了
static BOOL EvWaitCommIsTimingSync(VM_MACHINE * core)
{
	int result;
	if(CommGetConnectNum()<2){
		result = 1;
	}else{
		result = CommIsTimingSync( core->reg[0] );
	}
	return result;
}

//--------------------------------------------------------------------------------------------
/**
 * リセットコマンドを発行する
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdCommTempDataReset( VM_MACHINE * core )
{
	CommToolTempDataReset();
	return 0;
}


//============================================================================================
//
//	ユニオン関連
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * ユニオンルーム 通信の親機側でカードを見る前の会話番号を取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdUnionParentCardTalkNo( VM_MACHINE * core )
{
	FIELDSYS_WORK *fsys = core->fsys;
	WORDSET** wordset	= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WORDSET );
	u16* ret_wk	        = VMGetWork( core );

	*ret_wk = Union_GetCardTalkNo( *wordset );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ユニオンルーム 左上の人の話すメッセージID取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdUnionGetInfoTalkNo( VM_MACHINE * core )
{
	u16* ret_wk	        = VMGetWork( core );
	FIELDSYS_WORK *fsys = core->fsys;

	WORDSET** wordset	= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WORDSET );

	*ret_wk = Union_GetInfomationTalkNo( core->fsys->union_work, *wordset );
	return 0;
}


//--------------------------------------------------------------------------------------------
/**
 * ユニオンルーム ビーコン書き換え
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdUnionBeaconChange( VM_MACHINE * core )
{
	// ビーコン書き換えの際に子機も自分の接続モードを変更するようにする
	u16 mode = VMGetU16(core);

	// 通信モードをユニオンアプリケーションモードに変更
	if( mode==UNION_PARENT_MODE_CARDNOW   
	 || mode==UNION_PARENT_MODE_TRADENOW 
	 || mode==UNION_PARENT_MODE_RECORDNOW 
	 || mode==UNION_PARENT_MODE_BATTLENOW )
	{
		CommStateUnionAppStart();
	}else if( mode==UNION_PARENT_MODE_PARTY ){
		// アプリケーションモードから戻す
		CommStateUnionAppEnd();
	}
	
	// 親機の場合はビーコン書き換え
	if(CommGetCurrentID()==0){
		Union_BeaconChange( mode );
	}
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ユニオンルーム内で使用する会話用にトレーナー名をセットする
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdUnionTrainerNameRegist( VM_MACHINE * core )
{
	FIELD_OBJ_PTR* fldobj	= GetEvScriptWorkMemberAdrs(core->fsys,ID_EVSCR_TARGET_OBJ);//対象OBJ
	WORDSET** wordset		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_WORDSET );
	u16 type				= VMGetU16( core );
	MYSTATUS* my			= SaveData_GetMyStatus( GameSystem_GetSaveData(core->fsys) );
	PMSW_SAVEDATA *pmssave  = SaveData_GetPMSW( GameSystem_GetSaveData(core->fsys) );
	u16 no;

	if( type == UNION_TALK_CHILD ){
		no = FieldOBJ_OBJIDGet( *fldobj );
	}else{
		no = 0;
	}

	Union_TrainerNameRegist( *wordset, type, no, my, pmssave );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * フィールド用のコマンド体系に初期化
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdUnionReturnSetUp( VM_MACHINE * core )
{
	// ここにツウシンモードを「ユニオン話しかけ」に戻すコードを入れる
	CommCommandFieldInitialize( core->fsys );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ビーコン収集を再開する
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdUnionConnectCutRestart( VM_MACHINE * core )
{
	FIELDSYS_WORK *fsys = core->fsys;

	UnionRoomView_ObjAllRise( fsys->union_view );
//	UnionRoomView_ObjInit( fsys->union_view );
	CommStateUnionBconCollectionRestart();

	VM_SetWait( core, EvWaitCommConnectCountZero );


	return 1;
}

//return 1 = 終了
static BOOL EvWaitCommConnectCountZero(VM_MACHINE * core)
{
	return (CommGetConnectNum()<2);
}

//--------------------------------------------------------------------------------------------
/**
 * 話しかけで通信接続できない時に出す会話のインデックスを取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdUnionGetTalkNumber( VM_MACHINE * core )
{
	FIELD_OBJ_PTR* fldobj = GetEvScriptWorkMemberAdrs(core->fsys,ID_EVSCR_TARGET_OBJ);//話掛対象OBJ
	u16 type			  = VMGetU16( core );
	u16* ret_wk			  = VMGetWork( core );
	WORDSET** wordset	  = GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_WORDSET );

	*ret_wk = Union_GetTalkNumber( core->fsys->union_work, FieldOBJ_OBJIDGet(*fldobj), type, *wordset );
	return 0;
}

//------------------------------------------------------------------
/**
 * @brief   バトル開始の選択はどうなったのかを取得する
 *
 * @param   core		
 *
 * @retval  BOOL		
 */
//------------------------------------------------------------------
static BOOL EvCmdUnionBattleStartCheck( VM_MACHINE * core )
{
	PLIST_DATA * pld;
	void ** buf;
	u16* ret_wk			  = VMGetWork( core );
	
	
	// ポケモン選択結果取得
	*ret_wk = Union_GetBattleStartCheckResult( core->fsys->union_work );

	// 戦闘しないんだったらポケモンリストの選択結果データは破棄する
	if(*ret_wk!=UNION_BATTLE_OK){
		buf = GetEvScriptWorkMemberAdrs(core->fsys, ID_EVSCR_SUBPROC_WORK);
		pld = *buf;
		sys_FreeMemoryEz(pld);
	}
	
	return 0;
}
	

//--------------------------------------------------------------------------------------------
/**
 * 話しかけOBJのIDをセット
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdUnionIdSet( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys		= core->fsys;
	FIELD_OBJ_PTR* fldobj	= GetEvScriptWorkMemberAdrs(fsys,ID_EVSCR_TARGET_OBJ);//話し掛け対象OBJ
	u16* ret_wk				= VMGetWork( core );

	*ret_wk = Union_ConnectIdSet( fsys->union_work, FieldOBJ_OBJIDGet(*fldobj) );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ユニオンはなしかけ接続スタート（スクリプトからは話しかけOBJのIDを渡す）
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdUnionConnectStart( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys		= core->fsys;
	FIELD_OBJ_PTR* fldobj	= GetEvScriptWorkMemberAdrs(fsys,ID_EVSCR_TARGET_OBJ);//話し掛け対象OBJ
	u16  type				= VMGetWorkValue( core );
	u16* ret_wk				= VMGetWork( core );

	*ret_wk = Union_ConnectStart( fsys->union_work, FieldOBJ_OBJIDGet(*fldobj), type );
	return 0;
}



//--------------------------------------------------------------------------------------------
/**
 * 話しかけで接続してみた結果を返す
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdUnionResultGet( VM_MACHINE * core )
{
	u16 wk_id = VMGetU16( core );

	//仮想マシンの汎用レジスタにワークのIDを格納
	core->reg[0] = wk_id;

	VM_SetWait( core, EvWaitUnionResultGet );
	return 1;
}

//return 1 = 終了
static BOOL EvWaitUnionResultGet(VM_MACHINE * core)
{
	FIELDSYS_WORK* fsys	= core->fsys;
	u32 ret				= Union_ConnectResultGet( fsys->union_work );
	u16* ret_wk			= GetEventWorkAdrs( fsys, core->reg[0] );	//注意！

//	OS_TPrintf("接続待ち ret=%d\n",ret);

	//途中だったら
	if( ret == 0 ){
		return 0;
	}

	*ret_wk = ret;
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * ユニオンルームのOBJを隠す
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdUnionObjAllVanish( VM_MACHINE * core )
{
	FIELDSYS_WORK       *fsys = core->fsys;
	COMM_UNIONROOM_VIEW *view = fsys->union_view;

	Union_BeaconObjAllVanish( fsys->fldobjsys, view );

	return 0;
}


//--------------------------------------------------------------------------------------------
/**
 * ユニオンルームで話し掛け「られない」状態にする
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdUnionConnectTalkDenied( VM_MACHINE * core )
{
	// 今忙しいにビーコン書き換え
	Union_BeaconChange( UNION_PARENT_MODE_BUSY );	
	CommStateUnionPause();
	OS_Printf("ビーコン書き換え　＆　一旦接続拒否\n");

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ユニオンルームで話し掛け「られる」状態にもどす
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdUnionConnectTalkOk( VM_MACHINE * core )
{
	// 話し掛けＯＫにする

	CommStateUnionAppEnd();
	CommStateUnionBconCollectionRestart();
    Union_BeaconChange( UNION_PARENT_MODE_FREE );
	OS_Printf("ビーコン書き換え　＆　接続許可\n");
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 選択した値をユニオンワークに渡す
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdUnionScriptResultSet( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys	 = core->fsys;
	u16 type = VMGetWorkValue(core);
	u16 num = VMGetWorkValue(core);
	Union_ScriptResultGet( fsys->union_work, type, num );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 親機のスタートを待つ
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdUnionParentStartCommandSet( VM_MACHINE * core )
{
	u16 wk_id = VMGetU16( core );

	//仮想マシンの汎用レジスタにワークのIDを格納
	core->reg[0] = wk_id;

	VM_SetWait( core, EvWaitUnion_ParentStartCommandSet );
	return 1;
}

//return 1 = 終了
static BOOL EvWaitUnion_ParentStartCommandSet(VM_MACHINE * core)
{
	u16* ret_wk	= GetEventWorkAdrs( core->fsys, core->reg[0] );	//注意！
	u32 ret		= Union_ParentStartCommandSet(core->fsys->union_work);

	if( ret >= 1 ){
		*ret_wk = ret;

		// ユニオンルーム内で送受信した内容をクリア（戻ってきた時の誤動作防止用）
		Union_CommWorkClear(core->fsys->union_work);

		return 1;
	}

	*ret_wk = 0;
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 子機の選択を待つ
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdUnionChildSelectCommandSet( VM_MACHINE * core )
{
	u16 wk_id = VMGetU16( core );

	//仮想マシンの汎用レジスタにワークのIDを格納
	core->reg[0] = wk_id;
	
	VM_SetWait( core, EvWaitUnion_ChildSelectCommandSet );
	return 1;
}

//return 1 = 終了
static BOOL EvWaitUnion_ChildSelectCommandSet(VM_MACHINE * core)
{
	u16* ret_wk	= GetEventWorkAdrs( core->fsys, core->reg[0] );	//注意！
	u32 ret		= Union_ChildSelectCommandSet(core->fsys->union_work);

	// 話しかけられた側もキャンセルができる
	if(sys.trg & PAD_BUTTON_CANCEL){
		// ただし、子機からのイベント選択が到着していなければだが
		ret = Union_ParentSendCancel( core->fsys->union_work, UNION_PARENT_SELECT_CANCEL );
		OS_Printf("Bボタンがおされたが...");
		if(ret){
			OS_Printf("通った\n");
		}else{
			OS_Printf("子機の選択がきていたのでダメだった\n");
		}
	}

	if( ret != 0 ){
		*ret_wk = ret;
		return 1;
	}
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	ユニオンルームに入る
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdUnionMapChange( VM_MACHINE * core )
{
	EventCmd_UnionRoomMapChangeIn( core->fsys->event );
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * 4つの選択肢のトレーナーの名前をwordsetに格納する
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdUnionViewSetUpTrainerTypeSelect( VM_MACHINE * core )
{
	MYSTATUS* my		= SaveData_GetMyStatus( GameSystem_GetSaveData(core->fsys) );
	WORDSET** wordset	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_WORDSET );

	UnionView_SetUpTrainerTypeSelect( MyStatus_GetID(my), MyStatus_GetMySex(my), *wordset );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 選択した0-3の数字をトレーナーの見た目トレーナー文字列IDに変換
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdUnionViewGetTrainerType( VM_MACHINE * core )
{
	MYSTATUS* my	= SaveData_GetMyStatus( GameSystem_GetSaveData(core->fsys) );
	u16 ans			= VMGetWorkValue(core);
	u16* ret_wk		= VMGetWork( core );

	//OS_Printf( "ans = %d\n", ans );

	//IDと選択肢から見た目番号を取得
	*ret_wk = UnionView_GetTrainerType( MyStatus_GetID(my), MyStatus_GetMySex(my), ans );
	//OS_Printf( "ret_wk = %d\n", *ret_wk );

	//見た目番号から、トレーナーの文字列IDを取得
	*ret_wk = UnionView_GetTrainerInfo( MyStatus_GetMySex(my), *ret_wk, UNIONVIEW_MSGTYPE );
	//OS_Printf( "ret_wk = %d\n", *ret_wk );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 選択した0-3の数字をトレーナーの見た目番号に変換する関数
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdUnionViewGetTrainerTypeNo( VM_MACHINE * core )
{
	MYSTATUS* my	= SaveData_GetMyStatus( GameSystem_GetSaveData(core->fsys) );
	u16 ans			= VMGetWorkValue(core);
	u16* ret_wk		= VMGetWork( core );

	//OS_Printf( "ans = %d\n", ans );

	//IDと選択肢から見た目番号を取得
	*ret_wk = UnionView_GetTrainerType( MyStatus_GetID(my), MyStatus_GetMySex(my), ans );
	//OS_Printf( "ret_wk = %d\n", *ret_wk );

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 自分がトレーナーとして見られる時の番号をセット(ユニオンルーム用)
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdUnionViewMyStatusSet( VM_MACHINE * core )
{
	MYSTATUS* my	= SaveData_GetMyStatus( GameSystem_GetSaveData(core->fsys) );
	u16 type		= VMGetWorkValue(core);

	MyStatus_SetTrainerView( my, type );
	return 0;
}


//============================================================================================
//
//	ゲームオーバー関連
//
//============================================================================================
//--------------------------------------------------------------------------------------------
/**
 * ゲームオーバー呼び出し
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdGameOverCall( VM_MACHINE * core )
{
	//イベントコールなので、スクリプトに復帰します。
	EventCmd_NormalLose( core->event_work );
	return 1;
}


//============================================================================================
//
//	ワープ関連
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * ワープIDセット
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdSetWarpId( VM_MACHINE * core )
{
	u16 id = VMGetWorkValue(core);
	FIELDSYS_WORK* fsys = core->fsys;
	Situation_SetWarpID(SaveData_GetSituation(fsys->savedata), id);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 自分の性別取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdGetMySex( VM_MACHINE * core )
{
	MYSTATUS* my		= SaveData_GetMyStatus( GameSystem_GetSaveData(core->fsys) );
	u16* ret_wk			= VMGetWork( core );

	*ret_wk = MyStatus_GetMySex( my );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ポケセン回復処理
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdPcKaifuku( VM_MACHINE * core )
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(core->event_work);
	PokeParty_RecoverAll(SaveData_GetTemotiPokemon(fsys->savedata));
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 地下のNPCをランダムに配置する 
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdUgManShopNpcRandomPlace( VM_MACHINE * core )
{
//	UgManagerShopNpcRandomPlace( core->fsys );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 通信ダイレクトコーナーの終了処理を開始する
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdCommDirectEnd( VM_MACHINE * core )
{
    CommFieldStateExitBattle();
	VM_SetWait( core, EvWaitCommDirectEnd );
	return 1;
}

//return 1 = 終了
static BOOL EvWaitCommDirectEnd(VM_MACHINE * core)
{
	if( CommStateIsInitialize() != TRUE ){
        if(CommMPIsInitialize() != TRUE ){
            return 1;
        }
	}
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 終了処理手続き　タイミング同期版
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdCommDirectEndTiming( VM_MACHINE * core )
{
    CommFieldStateExitBattleTiming();
	VM_SetWait( core, EvWaitCommDirectEnd );
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * ダイレクトコーナールームに入った時の処理
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdCommDirectEnterBtlRoom( VM_MACHINE * core )
{
	CommFieldStateEnterBattleRoom( core->fsys );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 通信した上でプレイヤーの方向を変更
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdCommPlayerSetDir( VM_MACHINE * core )
{
	CommPlayerSetDir( VMGetU16(core) );
	return 0;
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	指定ポケットになにかはいっているかをチェック
 * @param	core		仮想マシン制御構造体へのポインタ
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdPocketCheck(VM_MACHINE * core)
{
	u16 pocket_id = VMGetWorkValue(core);
	u16 * ret_wk = VMGetWork(core);
	*ret_wk = MyItem_CheckItemPocket(SaveData_GetMyItem(core->fsys->savedata), pocket_id);
	return 0;
}


//============================================================================================
//
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * SXYデータの座標情報を変更
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdSxyPosChange( VM_MACHINE * core )
{
	u16 id = VMGetWorkValue(core);
	u16 gx = VMGetWorkValue(core);
	u16 gz = VMGetWorkValue(core);

	EventData_NpcDataPosChange( core->fsys, id, gx, gz );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * OBJデータの座標情報を変更
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdObjPosChange( VM_MACHINE * core )
{
	FIELD_OBJ_PTR fldobj;
	u16 obj_id	= VMGetWorkValue(core);
	u16 x		= VMGetWorkValue(core);
	u16 y		= VMGetWorkValue(core);
	u16 z		= VMGetWorkValue(core);
	u16 dir		= VMGetWorkValue(core);

	//対象のフィールドOBJのポインタ取得
	fldobj	= FieldOBJSys_OBJIDSearch( core->fsys->fldobjsys, obj_id );

	FieldOBJ_GPosDirInit( fldobj, x, y, z, dir );

	//高さ即反映
	FieldOBJ_VecPosNowHeightGetSet( fldobj );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * SXYデータの動作コードを変更
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdSxyMoveCodeChange( VM_MACHINE * core )
{
	u16 id	= VMGetWorkValue(core);
	u16 mv	= VMGetWorkValue(core);

	EventData_NpcDataMoveCodeChange( core->fsys, id, mv );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * SXYデータの方向を変更
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdSxyDirChange( VM_MACHINE * core )
{
	u16 id	= VMGetWorkValue(core);
	u16 dir	= VMGetWorkValue(core);

	EventData_NpcDataDirChange( core->fsys, id, dir );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * SXYデータの接続データの座標を変更
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdSxyExitPosChange( VM_MACHINE * core )
{
	u16 id		= VMGetWorkValue(core);
	u16 x		= VMGetWorkValue(core);
	u16 z		= VMGetWorkValue(core);

	EventData_ConnectDataPosChange( core->fsys, id, x, z );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * SXYデータのBGデータの座標を変更
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdSxyBgPosChange( VM_MACHINE * core )
{
	u16 id		= VMGetWorkValue(core);
	u16 x		= VMGetWorkValue(core);
	u16 z		= VMGetWorkValue(core);

	OS_Printf( "id = %d\n", id );
	OS_Printf( "x = %d\n", x );
	OS_Printf( "z = %d\n", z );

	EventData_BgDataPosChange( core->fsys, id, x, z );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * OBJの方向を変更
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdObjDirChange( VM_MACHINE * core )
{
	FIELD_OBJ_PTR fldobj;
	u16 obj_id	= VMGetWorkValue(core);
	u16 dir		= VMGetWorkValue(core);
	
	//対象のフィールドOBJのポインタ取得
	fldobj	= FieldOBJSys_OBJIDSearch( core->fsys->fldobjsys, obj_id );
	if( fldobj == NULL ){
		GF_ASSERT( (0) && "対象のフィールドOBJのポインタ取得失敗！" );
	}

	//FieldOBJ_DirDispCheckSet( fldobj, dir );
	FieldOBJ_DirDispDrawSet( fldobj, dir );
	return 0;
};

//--------------------------------------------------------------------------------------------
/**
 * スクリプト結果を代入するワークに値をセット
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdReturnScriptWkSet( VM_MACHINE * core )
{
	u16** return_script_wk	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_RETURN_SCRIPT_WK );
	u16 num					= VMGetWorkValue(core);

	if( *return_script_wk != NULL ){
		**return_script_wk = num;
	}
	return 0;
}


//--------------------------------------------------------------------------------------------
//

//============================================================================================
//
//	ドアアニメ関連
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * ドアアニメーションセットアップ
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdSetUpDoorAnime( VM_MACHINE * core )
{
	u16 block_x,block_z;
	u16 local_x,local_z;
	int grid_x,grid_z;
	u8 entry;
	
	FIELDSYS_WORK* fsys;
	
	//ブロック座標を取得
	block_x = VMGetU16(core);
	block_z = VMGetU16(core);
	//ローカルグリッド座標を取得
	local_x = VMGetWorkValue(core);
	local_z = VMGetWorkValue(core);
	//エントリーID取得
	entry = VMGetU8(core);

	OS_Printf("info:%d,%d,%d,%d,%d\n",block_x,block_z,local_x,local_z,entry);
	
	fsys = core->fsys;

	//ワールド座標を計算
	grid_x = block_x*32+local_x;
	grid_z = block_z*32+local_z;
	
	//指定座標のモデルのアニメーションセットアップ
	FLD_SCR_ANM_DOOR_Setup(fsys, grid_x, grid_z, entry);
	
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * アニメーションウェイト
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdWait3DAnime( VM_MACHINE * core )
{
	u8 entry;
	FIELDSYS_WORK* fsys;
	//エントリーID取得
	entry = VMGetU8(core);
	fsys = core->fsys;
	
	FLD_SCR_ANM_DOOR_WaitAnime(fsys, entry);
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * アニメーション解放
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdFree3DAnime( VM_MACHINE * core )
{
	u8 entry;
	FIELDSYS_WORK* fsys;
	//エントリーID取得
	entry = VMGetU8(core);
	fsys = core->fsys;
	FLD_SCR_ANM_DOOR_FreeDoor(fsys, entry);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ドアオープンアニメ
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdOpenDoor( VM_MACHINE * core )
{
	u8 entry;
	FIELDSYS_WORK* fsys;
	//エントリーID取得
	entry = VMGetU8(core);
	fsys = core->fsys;
	FLD_SCR_ANM_DOOR_StartOpenDoorAnm( fsys, entry );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ドアクローズアニメ
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdCloseDoor( VM_MACHINE * core )
{
	u8 entry;
	FIELDSYS_WORK* fsys;
	//エントリーID取得
	entry = VMGetU8(core);
	fsys = core->fsys;
	FLD_SCR_ANM_DOOR_StartCloseDoorAnm( fsys, entry );
	return 0;
}

//============================================================================================
//
//	ジム関連
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * 水ジム初期状態セット
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdInitWaterGym( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	GYM_InitWaterGym(fsys);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 水ジムボタン
 * @brief   イベントコールをかけるので、return 0でスクリプト本体が終了してしまわないように、1を返す
 * 
 * @param	core		仮想マシン制御構造体へのポインタ
 * 
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdPushWaterGymButton( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	GYM_CheckWaterGymButton(fsys);
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * ゴーストジム初期状態セット
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdInitGhostGym( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	GYM_InitGhostGym(fsys);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ゴーストジムリフト
 * @brief   イベントコールをかけるので、return 0でスクリプト本体が終了してしまわないように、1を返す
 * 
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdMoveGhostGymLift( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	GYM_MoveGhostGymLift(fsys);
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * 鋼ジム初期状態セット
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdInitSteelGym( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	GYM_InitSteelGym(fsys);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 格闘ジム初期状態セット
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdInitCombatGym( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	GYM_InitCombatGym(fsys);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 電気ジム初期状態セット
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdInitElecGym( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	u8 room 			= VMGetU8(core);
	GYM_InitElecGym(fsys, room);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 電気ジムギア
 * @brief   イベントコールをかけるので、return 0でスクリプト本体が終了してしまわないように、1を返す
 * 
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdRotElecGymGear( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	u8 rot 			= VMGetU8(core);
	GYM_RotateElecGymGear(fsys, rot);
	return 1;
}

//============================================================================================
/**
 * @brief	タマゴうまれるデモ
 */
//============================================================================================
static BOOL EvCmdTamagoDemo( VM_MACHINE * core )
{
	Field_EggDemo_Call(core->fsys);
	return 1;
}


//============================================================================================
//
//	地下お店関連
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * @brief   地下のお店のメニューを開く
 * 
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdUgShopMenuInit( VM_MACHINE * core )
{
	void** pwork			= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	FIELD_OBJ_PTR *fldobj	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_TARGET_OBJ );
	u16 type				= VMGetWorkValue( core );
	u16 wk_id				= VMGetU16( core );

	//仮想マシンの汎用レジスタにワークのIDを格納
	core->reg[0] = wk_id;

	*pwork = UgShopMenuInit2( type, core->fsys, FieldOBJ_OBJIDGet(*fldobj) );

	VM_SetWait( core, EvWaitUgShopMenuInit );
	return 1;
}

//return 1 = 終了
static BOOL EvWaitUgShopMenuInit(VM_MACHINE * core)
{
	void** pwork= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	u16* ret_wk = GetEventWorkAdrs( core->fsys, core->reg[0] );	//注意！

	*ret_wk = UgShopMenuFuncAndCheck( (*pwork) );

	if( (*ret_wk) == UG_SHOP_NONE ){	//選択中
		return 0;
	}

	OS_Printf( "UgShopMenuInit ret = %d\n", (*ret_wk) );
	//case UG_SHOP_BAG_FULL:			//バッグがいっぱい
	//case UG_SHOP_MISS_SELECT:			//選択したタマが異なる
	//case UG_SHOP_CANCEL:				//キャンセル
	//その他							//わな番号か、グッズ番号
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief   お店の会話開始
 * 
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdUgShopTalkStart( VM_MACHINE * core )
{
	u8* msg_index = GetEvScriptWorkMemberAdrs( core->fsys,ID_EVSCR_MSGINDEX );

	*msg_index = UgShopTalkStart( VMGetWorkValue(core) );

	VM_SetWait( core, EvWaitUgShopTalkStart );
	return 1;
}

//return 1 = 終了
static BOOL EvWaitUgShopTalkStart(VM_MACHINE * core)
{
	u8* msg_index = GetEvScriptWorkMemberAdrs( core->fsys,ID_EVSCR_MSGINDEX );
	return FldTalkMsgEndCheck( *msg_index );
}

//--------------------------------------------------------------------------------------------
/**
 * @brief   お店の会話終了
 * 
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdUgShopTalkEnd( VM_MACHINE * core )
{
	UgShopTalkEnd();
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief   アイテムの名前をお店の会話に登録
 * 
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdUgShopTalkRegisterItemName( VM_MACHINE * core )
{
	u8 idx		= VMGetU8(core);
	u16 type	= VMGetWorkValue(core);

	UgShopTalkRegisterItemName( idx, type );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief   罠の名前をお店の会話に登録
 * 
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdUgShopTalkRegisterTrapName( VM_MACHINE * core )
{
	u8 idx		= VMGetU8(core);
	u16 type	= VMGetWorkValue(core);

	UgShopTalkRegisterTrapName( idx, type );
	return 0;
}


//============================================================================================
//
//	ギネス関連
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * @brief   ギネスウィンドウ呼び出し
 * 
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdGuinnessWin( VM_MACHINE * core )
{
	EventCmd_GuinnessWin( core->event_work, 1, 1, 0, 0, NULL );
	return 1;
}

//-------------------------------------------------------------------------
//	ＯＢＪの見える・見えないスイッチ切り替え
//-------------------------------------------------------------------------
static BOOL EvCmdObjVisible( VM_MACHINE * core )
{
	FIELD_OBJ_PTR fldobj;		//対象のフィールドOBJのポインタ
	FIELDSYS_WORK * fsys = core->fsys;

	fldobj	= FieldOBJSys_OBJIDSearch( fsys->fldobjsys, VMGetWorkValue(core) );
	if( fldobj == NULL ){
		GF_ASSERT( (0) && "対象のフィールドOBJのポインタ取得失敗！" );
	}
	FieldOBJ_StatusBitSet_Vanish(fldobj, FALSE);
	return 0;
}

static BOOL EvCmdObjInvisible( VM_MACHINE * core )
{
	FIELD_OBJ_PTR fldobj;		//対象のフィールドOBJのポインタ
	FIELDSYS_WORK * fsys = core->fsys;

	fldobj	= FieldOBJSys_OBJIDSearch( fsys->fldobjsys, VMGetWorkValue(core) );
	if( fldobj == NULL ){
		GF_ASSERT( (0) && "対象のフィールドOBJのポインタ取得失敗！" );
	}
	FieldOBJ_StatusBitSet_Vanish(fldobj, TRUE);
	return 0;
}

//メールボックス
//--------------------------------------------------------------------------------------------
/**
 * メールボックス呼び出し
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
#include "savedata/mail_util.h"
#include "field/fld_mailbox.h"
static BOOL EvCmdMailBox( VM_MACHINE * core )
{
	EventCmd_MailBoxCall(core->event_work);	
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * メールボックス内のデータ数を取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdGetMailBoxDataNum( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	u16* ret_wk			= VMGetWork( core );
	MAIL_BLOCK* block = SaveData_GetMailBlock(fsys->savedata);
	
	*ret_wk = (u16)MAIL_GetEnableDataNum(block,MAILBLOCK_PASOCOM);
	return 0;
}

//ギネスホールランキング
//--------------------------------------------------------------------------------------------
/**
 * ランキング画面呼び出し
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
#include "field/fld_ranking.h"
static BOOL EvCmdRankingView( VM_MACHINE * core )
{
	u16	mode = VMGetWorkValue(core);
	EventCmd_RankingViewCall(core->event_work,mode);	
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * 時間帯の取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdGetTimeZone( VM_MACHINE * core )
{
	u16* ret_wk	= VMGetWork( core );
	*ret_wk		= EVTIME_GetTimeZone( core->fsys );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 乱数の取得		※gf_srandを外しましたのでNextと中身は同じです。
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdGetRand( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	u16* ret_wk			= VMGetWork( core );
	u16	limit			= VMGetWorkValue( core );

	*ret_wk = ( gf_rand() % limit );
	//OS_Printf("GET_RND[%d] limit[%d]\n",*ret_wk,limit);

	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * 乱数の取得 GET_RANDのタネを流用したまま呼びたいとき
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdGetRandNext( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	u16* ret_wk			= VMGetWork( core );
	u16	limit			= VMGetWorkValue( core );

	*ret_wk = ( gf_rand() % limit );

	return 1;
}


//--------------------------------------------------------------------------------------------
/**
 *　おおきさくらべ：記録と手持ちポケモンの比較
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdOokisaRecordChk( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;

	u16* ret_wk	= VMGetWork( core );
	u16		num = VMGetWorkValue(core);

	//チェック
	*ret_wk = OokisaRecordChk(fsys,num);

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 *　おおきさくらべ：手持ちのポケモンで記録更新
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdOokisaRecordSet( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	POKEMON_PARAM * pp;

	u16		num = VMGetWorkValue(core);

	//セット
	OokisaRecordSet(fsys,num);

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 *　おおきさくらべ：手持ちのポケモンの大きさを数値にして文字バッファへセット
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdOokisaTemotiSet( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	u16		buf_no1 = VMGetWorkValue(core);
	u16		buf_no2 = VMGetWorkValue(core);
	u16		num	= VMGetWorkValue(core);

	OokisaTemotiBufSet(fsys,buf_no1,buf_no2,num);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 *　おおきさくらべ：記録ポケモンの大きさを数値にして文字バッファへセット
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdOokisaKirokuSet( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	u16		buf_no1 = VMGetWorkValue(core);
	u16		buf_no2 = VMGetWorkValue(core);
	u16		monsno = VMGetWorkValue(core);

	OokisaRecordBufSet(fsys,buf_no1,buf_no2,monsno);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 *　おおきさくらべ：初期化。レコードクリア
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdOokisaKurabeInit( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;

	SysWork_OokisaRecordSet(SaveData_GetEventWork(fsys->savedata),OOKISA_KURABE_DEFAULT_RECORD);
	return 0;
}

//============================================================================================
//
//	冒険ノート関連
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 *　冒険ノート開始データセット
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 *
 * @li	冒険ノート入手時に呼んで下さい。
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdFNoteStartSet( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;

	SysFlag_FNoteSet( SaveData_GetEventWork(fsys->savedata) );		//冒険ノート入手フラグセット
	fsys->fnote = FNOTE_SavePageGet( SaveData_GetFNote(fsys->savedata), TRUE );
	FNoteStartDataSet( fsys );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 *　冒険ノートデータ作成
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdFNoteDataMake( VM_MACHINE * core )
{
	u8 type; 
	u16 id			= VMGetWorkValue(core);
	u16 wk1			= VMGetWorkValue(core);
	u16 wk2			= VMGetWorkValue(core);
	u16 wk3			= VMGetWorkValue(core);
	u16 wk4			= VMGetWorkValue(core);
	void** pwork	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );

	switch( id ){
#if 0
	// * データ作成 [ 行動：自宅 ]
	case FNOTE_ID_MYHOUSE:
		type = FNOTE_TYPE_ACTION;		//行動
		*pwork = FNOTE_ActionHouseDataMake( HEAPID_FIELD );
		break;

	// * データ作成 [ 行動：研究所 ]
	case FNOTE_ID_LABO:
		type = FNOTE_TYPE_ACTION;		//行動
		*pwork = FNOTE_ActionLaboDataMake( HEAPID_FIELD );
		break;
#endif

#if 0
	//プログラム側でセットしてもらう形に変更！

	// * データ作成 [ 行動：ジム（リーダーを倒す前） ]
	// * @param	map		マップID
	case FNOTE_ID_GYMBEFORE:
		type = FNOTE_TYPE_ACTION;		//行動
		*pwork = FNOTE_ActionGymBeforeDataMake( wk1, HEAPID_FIELD );
		break;

	// * データ作成 [ 行動：ジム（リーダーを倒した後） ]
	// * @param	map		マップID
	// * @param	trainer	トレーナーID
	case FNOTE_ID_GYMAFTER:
		type = FNOTE_TYPE_ACTION;		//行動
		*pwork = FNOTE_ActionGymAfterDataMake( wk1, wk2, HEAPID_FIELD );
		break;

	// * データ作成 [ 行動：四天王 ]
	// * @param	trainer	トレーナーID
	case FNOTE_ID_SITENNOU:
		type = FNOTE_TYPE_ACTION;		//行動
		*pwork = FNOTE_ActionSitenouDataMake( wk1, HEAPID_FIELD );
		break;

	// * データ作成 [ 行動：チャンピオン ]
	// * @param	trainer	トレーナーID
	case FNOTE_ID_CHAMPION:
		type = FNOTE_TYPE_ACTION;		//行動
		*pwork = FNOTE_ActionChampionDataMake( wk1, HEAPID_FIELD );
		break;
#endif

	// * データ作成 [ 行動：ゲームコーナー ]
	case FNOTE_ID_GAMECORNER:
		type = FNOTE_TYPE_ACTION;		//行動
		*pwork = FNOTE_ActionGameCornerDataMake( HEAPID_FIELD );
		break;

	// * データ作成 [ 行動：サファリゾーン ]
	case FNOTE_ID_SAFARIZONE:
		type = FNOTE_TYPE_ACTION;		//行動
		*pwork = FNOTE_ActionSafariDataMake( HEAPID_FIELD );
		break;

	// * データ作成 [ 行動：アイテム取得 ]
	// * @param	item	アイテムID
	case FNOTE_ID_ITEMGET:
		type = FNOTE_TYPE_ACTION;		//行動
		*pwork = FNOTE_ActionItemDataMake( wk1, HEAPID_FIELD );
		break;

	case FNOTE_ID_IAIGIRI:
	case FNOTE_ID_NAMINORI:
	case FNOTE_ID_KAIRIKI:
	case FNOTE_ID_KIRIBARAI:
	case FNOTE_ID_IWAKUDAKI:
	case FNOTE_ID_TAKINOBORI:
	case FNOTE_ID_ROCKCLIMB:
		type = FNOTE_TYPE_ACTION;		//行動
		*pwork = FNOTE_ActionSkillDataMake( id-FNOTE_ID_IAIGIRI, wk1, HEAPID_FIELD );
		break;

	default:
		return 1;
	};

	FNOTE_DataSave( core->fsys->fnote, *pwork, type );	//データセーブ
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 *　冒険ノートデータセーブ
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdFNoteDataSave( VM_MACHINE * core )
{
	//未使用
	return 0;
}


//============================================================================================
//
//	イメージクリップアイテム関連
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * イメージクリップ：アクセサリー：アイテムを加える
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdImcAcceAddItem(VM_MACHINE * core)		
{
	IMC_SAVEDATA* imc;
	IMC_ITEM_SAVEDATA* imc_item;
	u16 acce_no	= VMGetWorkValue(core);
	u16 num		= VMGetWorkValue(core);

	imc	= SaveData_GetImcSaveData( core->fsys->savedata );
	imc_item = ImcSaveData_GetItemSaveData( imc );	//アイテムセーブデータ取得

	ImcSaveData_AddAcceFlag( imc_item, acce_no, num );
	return 0;
};

//--------------------------------------------------------------------------------------------
/**
 * イメージクリップ：アクセサリー：アイテムを加えられるかチェック
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdImcAcceAddItemChk(VM_MACHINE * core)	
{
	IMC_SAVEDATA* imc;
	IMC_ITEM_SAVEDATA* imc_item;
	u16 acce_no	= VMGetWorkValue(core);
	u16 num		= VMGetWorkValue(core);
	u16* ret_wk	= VMGetWork( core );

	imc	= SaveData_GetImcSaveData( core->fsys->savedata );
	imc_item = ImcSaveData_GetItemSaveData( imc );	//アイテムセーブデータ取得

	*ret_wk = ImcSaveData_CheckAcceAdd( imc_item, acce_no, num );
	return 0;
};

//--------------------------------------------------------------------------------------------
/**
 * イメージクリップ：アクセサリー：バッグのアイテムチェック
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdImcAcceCheckItem(VM_MACHINE * core)			
{
	IMC_SAVEDATA* imc;
	IMC_ITEM_SAVEDATA* imc_item;
	u16 acce_no	= VMGetWorkValue(core);
	u16 num		= VMGetWorkValue(core);
	u16* ret_wk	= VMGetWork( core );

	imc	= SaveData_GetImcSaveData( core->fsys->savedata );
	imc_item = ImcSaveData_GetItemSaveData( imc );	//アイテムセーブデータ取得

	if( num <= ImcSaveData_GetAcceFlag(imc_item, acce_no) ){
		*ret_wk = 1;
	}else{
		*ret_wk = 0;
	}

	return 0;
};

//--------------------------------------------------------------------------------------------
/**
 * イメージクリップ：背景：アイテムを加える
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdImcBgAddItem(VM_MACHINE * core)		
{
	IMC_SAVEDATA* imc;
	IMC_ITEM_SAVEDATA* imc_item;
	u16 bg_no	= VMGetWorkValue(core);

	imc	= SaveData_GetImcSaveData( core->fsys->savedata );
	imc_item = ImcSaveData_GetItemSaveData( imc );	//アイテムセーブデータ取得

	ImcSaveData_SetBGFlag( imc_item, bg_no );
	return 0;
};

//--------------------------------------------------------------------------------------------
/**
 * イメージクリップ：背景：バッグのアイテムチェック
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdImcBgCheckItem(VM_MACHINE * core)			
{
	IMC_SAVEDATA* imc;
	IMC_ITEM_SAVEDATA* imc_item;
	u16 bg_no	= VMGetWorkValue(core);
	u16* ret_wk	= VMGetWork( core );

	imc	= SaveData_GetImcSaveData( core->fsys->savedata );
	imc_item = ImcSaveData_GetItemSaveData( imc );	//アイテムセーブデータ取得

	*ret_wk = ImcSaveData_CheckBgGet( imc_item, bg_no );
	return 0;
};

//--------------------------------------------------------------------------------------------
/**
 * 表彰状イベント：シンオウ図鑑チェック
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdZukanChkShinou(VM_MACHINE * core)
{
	const ZUKAN_WORK* zw = SaveData_GetZukanWork( core->fsys->savedata );
	u16* ret_wk	= VMGetWork( core );

	*ret_wk = 0;
	if(ZukanWork_CheckShinouComp(zw) == TRUE){
		*ret_wk = 1;
	}
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 表彰状イベント：全国図鑑チェック
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdZukanChkNational(VM_MACHINE * core)
{
	const ZUKAN_WORK* zw = SaveData_GetZukanWork( core->fsys->savedata );
	u16* ret_wk	= VMGetWork( core );

	*ret_wk = 0;
	if(ZukanWork_CheckZenkokuComp(zw) == TRUE){
		*ret_wk = 1;
	}
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 表彰状イベント：シンオウ図鑑表彰呼び出し
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdZukanRecongnizeShinou(VM_MACHINE * core)
{
	void** buf = GetEvScriptWorkMemberAdrs(core->fsys, ID_EVSCR_SUBPROC_WORK);
	*buf = Syoujyou_SetProc(core->fsys, HEAPID_EVENT,SYOUJYOU_TYPE_SINOU);
	VM_SetWait( core, EvWaitSubProcAndFree );
	return 1;
}
//--------------------------------------------------------------------------------------------
/**
 * 表彰状イベント：全国図鑑表彰呼び出し
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdZukanRecongnizeNational(VM_MACHINE * core)
{
//Field_MySign_SetProc( core->fsys );	//test
	void** buf = GetEvScriptWorkMemberAdrs(core->fsys, ID_EVSCR_SUBPROC_WORK);
	*buf = Syoujyou_SetProc(core->fsys, HEAPID_EVENT,SYOUJYOU_TYPE_ZENKOKU);
	VM_SetWait( core, EvWaitSubProcAndFree );
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * ウラヤマエンカウント：エンカウントするポケモンセット
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdUrayamaEncountSet(VM_MACHINE * core)
{
	HillBack_SetEncPokemon(core->fsys->savedata);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ウラヤマエンカウント：現在エンカウントするポケモンを取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdUrayamaEncountNoChk(VM_MACHINE * core)
{
	u16* ret_wk	= VMGetWork( core );
	(*ret_wk) = HillBack_GetMonsNo(core->fsys->savedata);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 *	紙飛行機の落とす場所を決める
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdPaperplaneSet(VM_MACHINE * core)
{
	u16* ret_wk	= VMGetWork( core );


//060709仕様が無くなった為不用に

	return 0;
}

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
/**
 *	@brief	レコードデータのインクリメント
 */
static BOOL EvCmdRecordInc(VM_MACHINE* core)
{
	u16 recid = VMGetU16(core);
	
	RECORD_Inc(SaveData_GetRecord(core->fsys->savedata),recid);
	return 0;
}

/**
 *	@brief	レコードデータを取得する
 */
static BOOL EvCmdRecordGet(VM_MACHINE* core)
{
	u32	val;
	u16	*h_wk,*l_wk;
	u16	recid = VMGetU16(core);
	u16	hwk_id = VMGetU16(core);	//上位
	u16	lwk_id = VMGetU16(core);	//下位

	h_wk = GetEventWorkAdrs(core->fsys,hwk_id);
	l_wk = GetEventWorkAdrs(core->fsys,lwk_id);

	val = RECORD_Get(SaveData_GetRecord(core->fsys->savedata),recid);

	*h_wk = ((val & 0xFFFF0000) >> 16);
	*l_wk = (val & 0x0000FFFF);
	return 0;
}

/**
 *	@brief	レコードデータをセットする
 */
static BOOL EvCmdRecordSet(VM_MACHINE* core)
{
	u32	val;
	u16	recid = VMGetU16(core);
	u16	val1 = VMGetU16(core);	//上位
	u16	val2 = VMGetU16(core);	//下位
	u8	mode = VMGetU8(core);	//0:Add,1:Set,2:SetIfLarge

	val = (u32)(val1)<<16;
	val |= val2;

	switch(mode){
	case 0:	//Add
		RECORD_Add(SaveData_GetRecord(core->fsys->savedata),recid,val);
		break;
	case 1:	//Set
		RECORD_Set(SaveData_GetRecord(core->fsys->savedata),recid,val);
		break;
	case 2:	//SetIfLarge
		RECORD_SetIfLarge(SaveData_GetRecord(core->fsys->savedata),recid,val);
		break;
	}
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief		スクリプトコマンド：サファリ制御
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdSafariControl(VM_MACHINE * core)
{
	u16 * ball;
	u16 * step;
	SITUATION * st = SaveData_GetSituation(core->fsys->savedata);
	EVENTWORK* ev = SaveData_GetEventWork(core->fsys->savedata);
	TV_WORK * tvwk = SaveData_GetTvWork(core->fsys->savedata);
	int flag = VMGetU8(core);

	ball = Situation_GetSafariBallCount(st);
	step = Situation_GetSafariStepCount(st);
	switch (flag) {
	case 0:		//開始
		SysFlag_SafariSet(ev);
		TVTOPIC_SafariTemp_Init(tvwk);
		*ball = 30;
		*step = 0;
		break;

	case 1:		//終了
		SysFlag_SafariReset(ev);
		TVTOPIC_Entry_Watch_Safari(core->fsys);
		{	// 冒険ノートデータ作成
			void * mem = FNOTE_ActionSafariDataMake( HEAPID_FIELD );
			FNOTE_DataSave( core->fsys->fnote, mem, FNOTE_TYPE_ACTION );
		}
		*ball = 0;
		*step = 0;
		break;
	}

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * サファリ望遠鏡
 * @brief   イベントコールをかけるので、return 0でスクリプト本体が終了してしまわないように、1を返す
 * 
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdCallSafariScope(VM_MACHINE * core)
{
	CallSafariScopeEvent(core->fsys);
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * クライマックスデモ呼び出し
 */
//--------------------------------------------------------------------------------------------
static BOOL	EvCmdClimaxDemoCall(VM_MACHINE * core)
{
	u8 id = VMGetU8(core);
	u16 *ret_wk = VMGetWork(core);

	*ret_wk = ClimaxDemoCall(core->fsys, id);
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * サファリ電車初期化
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdInitSafariTrain(VM_MACHINE * core)
{
	SafariTrain_Init(core->fsys);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * サファリ電車移動
 * @brief   イベントコールをかけるので、return 0でスクリプト本体が終了してしまわないように、1を返す
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdMoveSafariTrain(VM_MACHINE * core)
{
	u16 *pos = VMGetWork( core );
	u16 type = VMGetU16(core);

	Snd_DataSetByScene( SND_SCENE_SUB_TRAIN, 0, 0 );// サウンドデータロード(モロッコ号)(BGM引継ぎ)

	SafariTrain_Move(core->fsys, *pos, type);
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * サファリ電車チェック（電車が停車しているか）
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdCheckSafariTrain(VM_MACHINE * core)
{
	u16 pos = VMGetU16(core);
	u16 *ret_wk = VMGetWork(core);
	*ret_wk = SafariTrain_CheckPos(core->fsys, pos);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 自機高さ取得有無
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdPlayerHeightValid(VM_MACHINE * core)
{
	u8 valid = VMGetU8(core);
	Player_HeightGet_ON_OFF( core->fsys->player, valid );
	return 1;
}


//--------------------------------------------------------------------------------------------
/**
 *	地下で会話した人数の累計(ミカゲ専用）
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdUnderGroundTalkCount(VM_MACHINE * core)
{
	EVENTWORK* ev = SaveData_GetEventWork(core->fsys->savedata);
	u16* ret_wk	= VMGetWork( core );

	*ret_wk = SysWork_UGTalkCountGet(ev);
	return 0;
}


//-----------------------------------------------------------------------------
/**
 *	新聞社：つれてくるポケモン番号取得
 */
//-----------------------------------------------------------------------------
static BOOL EvCmdGetNewsPokeNo(VM_MACHINE * core)
{
	const ZUKAN_WORK* zw = SaveData_GetZukanWork( core->fsys->savedata );
	u16* ret_wk	= VMGetWork( core );
	u16 get_count,num_count,i,j;

	//捕まえた数を取得
//	get_count = ZukanWork_GetShinouPokeGetCount(zw);
	//見つけた数を取得　※060726変更。松宮さんより要望
	get_count = ZukanWork_GetShinouPokeSeeCount(zw);

	//捕まえた数内のランダムで、目的のポケモン(図鑑の何番目に載っているか)を決定
	num_count = gf_rand() % get_count;

	*ret_wk = MONSNO_PIKATYUU;	//※デバッグ等で捕まえた数が０のとき用に、念のため必ず初期化
	for( i=1,j=0; i<=MONSNO_END; i++ ){
		//ゲットしていて、 ｼﾝｵｳｽﾞｶﾝにいるかチェック
//		if(( ZukanWork_GetPokeGetFlag( zw, i ) == TRUE )&&( PokeZenkokuNo2ShinouNo( i ) != 0 )){
		//見つけてい、 ｼﾝｵｳｽﾞｶﾝにいるかチェック
		if(( ZukanWork_GetPokeSeeFlag( zw, i ) == TRUE )&&( PokeZenkokuNo2ShinouNo( i ) != 0 )){
			if(j==num_count){
				*ret_wk = i;
				break;
			}
			j++;
		}
	}

	return 0;
}

//-----------------------------------------------------------------------------
/**
 *	新聞社：締め切りまでの残り分セット
 */
//-----------------------------------------------------------------------------
static BOOL EvCmdNewsCountSet(VM_MACHINE * core)
{
	u16 no	= VMGetWorkValue(core);
	SysWork_NewsDaysCountSet( SaveData_GetEventWork(core->fsys->savedata),no );
	return 0;
}

//-----------------------------------------------------------------------------
/**
 *	新聞社：締め切りまでの残り分チェック
 *	1～	：締め切り前
 *	0	：締め切りを過ぎた
 */
//-----------------------------------------------------------------------------
static BOOL EvCmdNewsCountChk(VM_MACHINE * core)
{
	u16* ret_wk	= VMGetWork( core );

	*ret_wk = SysWork_NewsDaysCountGet( SaveData_GetEventWork(core->fsys->savedata) );
	return 0;
}

//-----------------------------------------------------------------------------
/**
 *	大量発生開始
 */
//-----------------------------------------------------------------------------
static BOOL EvCmdStartGenerate(VM_MACHINE * core)
{
	EncDataSave_StartGenerate( core->fsys->savedata );

	return 0;
}

//-----------------------------------------------------------------------------
/**
 *	移動ポケモン登録
 */
//-----------------------------------------------------------------------------
static BOOL EvCmdAddMovePoke(VM_MACHINE * core)
{
	u8 poke = VMGetU8( core );
	MP_AddMovePoke(core->fsys->savedata, poke);
	return 0;
}

//============================================================================================
//
//	ゲーム内交換
//
//	ID_EVSCR_PWORK使用！
//
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * 交換データ作成
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 *
 * @li ID_EVSCR_PWORK使用！
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdFldTradeAlloc(VM_MACHINE * core)
{
	void** pwork	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	u8 tradeno		= VMGetU8(core);

	*pwork = FLD_TradeAlloc( HEAPID_WORLD, tradeno );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * くれるポケモンナンバー取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 *
 * @li ID_EVSCR_PWORK使用！
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdFldTradeMonsno(VM_MACHINE * core)
{
	void** pwork	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	u16* ret_wk		= VMGetWork( core );

	*ret_wk = FLD_TradeMonsno( (FLD_TRADE_WORK*)*pwork );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * わたすポケモンナンバー取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 *
 * @li ID_EVSCR_PWORK使用！
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdFldTradeChgMonsno(VM_MACHINE * core)
{
	void** pwork	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	u16* ret_wk		= VMGetWork( core );

	*ret_wk = FLD_TradeChangeMonsno( (FLD_TRADE_WORK*)*pwork );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 交換イベント開始
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 *
 * @li ID_EVSCR_PWORK使用！
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdFldTradeEvent(VM_MACHINE * core)
{
	void** pwork	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );
	u16 pos			= VMGetWorkValue(core);

	EventCmd_FldTrade( core->event_work, (FLD_TRADE_WORK*)*pwork, pos, HEAPID_WORLD );
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * 交換データ削除
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 *
 * @li ID_EVSCR_PWORK使用！
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdFldTradeDel(VM_MACHINE * core)
{
	void** pwork	= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PWORK );

	FLD_TradeDelete( (FLD_TRADE_WORK*)*pwork );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 図鑑外国語バージョン　Masterフラグ
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdZukanTextVerUp(VM_MACHINE * core)
{
	ZukanWork_SetTextVersionUpMasterFlag( SaveData_GetZukanWork(core->fsys->savedata) );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 図鑑性別表示バージョンアップ
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdZukanSexVerUp(VM_MACHINE * core)
{
	ZukanWork_SetGraphicVersionUpFlag( SaveData_GetZukanWork(core->fsys->savedata) );
	return 0;
}



//--------------------------------------------------------------------------------------------
/**
 * 全国図鑑フラグ操作(FLAG_MODE_SET,FLAG_MODE_RESET,FLAG_MODE_GET)
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdZenkokuZukanFlag(VM_MACHINE * core)
{
	u8 mode		= VMGetU8( core );
	u16* ret_wk	= VMGetWork( core );

	*ret_wk = FALSE;

	if( mode == FLAG_MODE_SET ){
		ZukanWork_SetZenkokuZukanFlag( SaveData_GetZukanWork(core->fsys->savedata) );
		MyStatus_SetDpZenkokuFlag( SaveData_GetMyStatus(core->fsys->savedata) );
	}else if( mode == FLAG_MODE_GET ){
		*ret_wk = ZukanWork_GetZenkokuZukanFlag( SaveData_GetZukanWork(core->fsys->savedata) );
	}else{
		GF_ASSERT( (0) && "全国図鑑フラグ操作の引数が不正です！" );
	}

	return 0;
}

//-----------------------------------------------------------------------------
/**
 *	努力値を取得
 */
//-----------------------------------------------------------------------------
static BOOL EvCmdChkPrmExp(VM_MACHINE * core)
{
	POKEMON_PARAM * pp;
	u16* ret_wk	= VMGetWork( core );
	u16		tno	= VMGetWorkValue(core);
	u32	tmp[7];

	pp = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(core->fsys->savedata), tno);

	tmp[0] = PokeParaGet( pp, ID_PARA_hp_exp, NULL );
	tmp[1] = PokeParaGet( pp, ID_PARA_pow_exp, NULL );
	tmp[2] = PokeParaGet( pp, ID_PARA_def_exp, NULL );
	tmp[3] = PokeParaGet( pp, ID_PARA_agi_exp, NULL );
	tmp[4] = PokeParaGet( pp, ID_PARA_spepow_exp, NULL );
	tmp[5] = PokeParaGet( pp, ID_PARA_spedef_exp, NULL );
	*ret_wk = (tmp[0]+tmp[1]+tmp[2]+tmp[3]+tmp[4]+tmp[5]);

	return 0;
}

//-----------------------------------------------------------------------------
/**
 *	曜日チェック
 */
//-----------------------------------------------------------------------------
static BOOL EvCmdChkWeek(VM_MACHINE * core)
{
	RTCDate now_date;
	u16* ret_wk	= VMGetWork( core );

	GF_RTC_GetDate(&now_date);

	*ret_wk = now_date.week;

	return 0;
}

//-----------------------------------------------------------------------------
/**
 */
//-----------------------------------------------------------------------------
static BOOL EvCmdCollectNews(VM_MACHINE * core)
{
	return 0;
}

//-----------------------------------------------------------------------------
/**
 * レギュレーションルールブック
 *
 * @return	"1"
 */
//-----------------------------------------------------------------------------
static BOOL EvCmdRegulationListCall(VM_MACHINE * core)
{
	u16 wk_id = VMGetU16( core );
	EventCmd_RegulationListCall( core->event_work, GetEventWorkAdrs(core->fsys,wk_id) );
	return 1;
}

//-----------------------------------------------------------------------------
/**
 *	ポケモンの足跡の有無とグループを調べる
 * *ret_wk = 足跡の有無(無し0,あり1)、 *ret2_wk = グループ（１－５）
 */
//-----------------------------------------------------------------------------
static BOOL EvCmdAshiatoChk(VM_MACHINE * core)
{
	POKEMON_PARAM * pp;
	u16* ret_wk		= VMGetWork( core );
	u16* ret2_wk	= VMGetWork( core );
	u16	tno	= VMGetWorkValue(core);
	u16 mons_no;

	pp = PokeParty_GetMemberPointer( SaveData_GetTemotiPokemon(core->fsys->savedata), tno);
	mons_no = PokeParaGet(pp,ID_PARA_monsno,NULL);

	*ret_wk = ashiato_ato_chk( mons_no);
	*ret2_wk = ashiato_group_chk( mons_no);

	//OS_Printf("足跡分類[%d]\n",*ret2_wk);
	//OS_Printf("足跡有無[%d]\n",*ret_wk);
	return 0;
}

//-----------------------------------------------------------------------------
/**
 *	ポケモンの回復マシーンアニメ
 * @brief   イベントコールをかけるので、return 0でスクリプト本体が終了してしまわないように、1を返す
 */
//-----------------------------------------------------------------------------
static BOOL EvCmdPcRecoverAnm(VM_MACHINE * core)
{
	u16	ball_num = VMGetWorkValue(core);

	PcRecoverAnm_StartAnm(core->fsys, ball_num);

	return 1;
}

//-----------------------------------------------------------------------------
/**
 *	エレベーターアニメ
 * @brief   イベントコールをかけるので、return 0でスクリプト本体が終了してしまわないように、1を返す
 */
//-----------------------------------------------------------------------------
static BOOL EvCmdElevatorAnm(VM_MACHINE * core)
{
	u16	dir = VMGetWorkValue( core );
	u16	loop = VMGetWorkValue( core );

	ElevatorAnm_StartAnm(core->fsys, (u8)dir, (u8)loop);

	return 1;
}

//-----------------------------------------------------------------------------
/**
 *	船デモ(マップジャンプします)
 * @brief   イベントコールをかけるので、return 0でスクリプト本体が終了してしまわないように、1を返す
 */
//-----------------------------------------------------------------------------
static BOOL EvCmdCallShipDemo(VM_MACHINE * core)
{
	u8	ship_dir = VMGetU8( core );
	u8	play_dir = VMGetU8( core );
	int zone = VMGetU16( core );
	int x = VMGetU16( core );
	int z = VMGetU16( core );
	
	ShipDemo_CallDemo(core->fsys, ship_dir, play_dir, zone, x, z);

	return 1;
}

//-----------------------------------------------------------------------------
/**
 *	バージョン取得
 */
//-----------------------------------------------------------------------------
static BOOL EvCmdPMVersionGet(VM_MACHINE * core)
{
	u16* ret_wk	= VMGetWork( core );

	*ret_wk = PM_VERSION;
	return 0;
}

//-----------------------------------------------------------------------------
/**
 *	あいことばに該当する壁紙を有効に
 *	OUT *ret_wk  : 0xff:一致しない 0:既にある 1～8:有効になった壁紙番号
 */
//-----------------------------------------------------------------------------
static BOOL EvCmdAikotobaKabegamiSet(VM_MACHINE * core)
{
	FIELDSYS_WORK * fsys	= core->fsys;
	MYSTATUS* my	= SaveData_GetMyStatus( GameSystem_GetSaveData(core->fsys) );
	u16* ret_wk				= VMGetWork( core );
	BOX_DATA* boxDat = SaveData_GetBoxData( fsys->savedata );
	u16 aik1		= VMGetWorkValue(core);
	u16 aik2		= VMGetWorkValue(core);
	u16 aik3		= VMGetWorkValue(core);
	u16 aik4		= VMGetWorkValue(core);
	int kabe_no;

	kabe_no = BOXPWD_HitCheck(my,aik1,aik2,aik3,aik4);

	if((kabe_no == BOXPWD_RESULT_ERROR)||(kabe_no > 7)){
		*ret_wk = 0xff;			//あいことばが一致しない
		return 0;
	}

	if(BOXDAT_GetDaisukiKabegamiFlag( boxDat, kabe_no)){
		*ret_wk = 0;		//既に登録済み
	}else{
		BOXDAT_SetDaisukiKabegamiFlag( boxDat, kabe_no );
		*ret_wk = kabe_no+1;
	}

	return 0;
}

//-----------------------------------------------------------------------------
/**
 *	地下で取得したハタの総数取得
 */
//-----------------------------------------------------------------------------
static BOOL EvCmdGetUgHataNum(VM_MACHINE * core)
{
	FIELDSYS_WORK * fsys	= core->fsys;
	SAVEDATA * sv = fsys->savedata;
    SB_RECORD_DATA* pSBRecord;
	u16* ret_wk				= VMGetWork( core );

	pSBRecord = SaveData_GetSecretBaseRecord(sv);
	*ret_wk = SecretBaseRecordGetFlagDeliveryNum(pSBRecord);

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * パソコンアニメーションセットアップ
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdSetUpPasoAnime( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys;
	u8 entry;
	fsys = core->fsys;
	//エントリーID取得
	entry = VMGetU8(core);

	//パソコンアニメーションセットアップ
	FLD_SCR_ANM_PASO_Setup(fsys, entry);
	
	return 0;
}

//-----------------------------------------------------------------------------
/**
 *	パソコンつける
 */
//-----------------------------------------------------------------------------
static BOOL EvCmdStartPasoOnAnime(VM_MACHINE * core)
{
	FIELDSYS_WORK* fsys;
	u8 entry;
	fsys = core->fsys;
	//エントリーID取得
	entry = VMGetU8(core);
	FLD_SCR_ANM_PASO_PasoOnAnm(	fsys, entry );
	return 0;
}

//-----------------------------------------------------------------------------
/**
 *	パソコン消す
 */
//-----------------------------------------------------------------------------
static BOOL EvCmdStartPasoOffAnime(VM_MACHINE * core)
{
	FIELDSYS_WORK* fsys;
	u8 entry;
	fsys = core->fsys;
	//エントリーID取得
	entry = VMGetU8(core);
	FLD_SCR_ANM_PASO_PasoOffAnm( fsys, entry );
	return 0;
}



//============================================================================================
//============================================================================================
//
//--------------------------------------------------------------------------------------------
/**
 * 図鑑見たフラグをセット
 *
 * @param	monsno	ポケモンナンバー
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static void Scr_ZukanSeeSet( FIELDSYS_WORK* fsys, u16 monsno )
{
	ZUKAN_WORK * zw				= SaveData_GetZukanWork( fsys->savedata );
	POKEMON_PARAM* poke_param	= PokemonParam_AllocWork( HEAPID_EVENT );

	PokeParaInit( poke_param );
	PokeParaSet( poke_param, monsno, 50, POW_RND, RND_NO_SET, 0, ID_NO_SET, 0 );
	ZukanWork_SetPokeSee( zw, poke_param );
	sys_FreeMemoryEz( poke_param );
	return;
}


//============================================================================================
//============================================================================================
//-----------------------------------------------------------------------------
/**
 * @brief	ポケモンボックスの空きを数える
 */
//-----------------------------------------------------------------------------
static BOOL EvCmdPokeBoxCountEmptySpace(VM_MACHINE * core)
{
	u16 * ret_wk = VMGetWork(core);
	u16 count;
	count = BOXDAT_GetEmptySpaceTotal( SaveData_GetBoxData(core->fsys->savedata) );
	*ret_wk = BOX_MAX_TRAY * BOX_MAX_POS - count;
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * レポート描画処理追加(自機形態が徒歩以外であれば何もしない)
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 *
 * @li ID_EVSCR_PWORK使用！
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdReportDrawProcSet( VM_MACHINE * core )
{
	TCB_PTR* tcb = GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PLAYER_TCB );

	*tcb = NULL;
	*tcb = Player_ReportDrawProcSet( core->fsys );
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * レポート描画処理削除
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 *
 * @li ID_EVSCR_PWORK使用！
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdReportDrawProcDel( VM_MACHINE * core )
{
	TCB_PTR* tcb = GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_PLAYER_TCB );
	Player_ReportDrawProcDelete( *tcb );
	return 1;
}

//-----------------------------------------------------------------------------
/**
 *	殿堂マシーン上ボールアニメ
 * @brief   イベントコールをかけるので、return 0でスクリプト本体が終了してしまわないように、1を返す
 */
//-----------------------------------------------------------------------------
static BOOL EvCmdDendouBallAnm(VM_MACHINE * core)
{
	u16	ball_num = VMGetWorkValue(core);

	DendouBallAnm_StartAnm(core->fsys, ball_num);
	return 1;
}

//-----------------------------------------------------------------------------
/**
 *	フィールドリフト初期化
 */
//-----------------------------------------------------------------------------
static BOOL EvCmdInitFldLift(VM_MACHINE * core)
{
	FLIFT_Init(core->fsys);
	return 0;
}

//-----------------------------------------------------------------------------
/**
 *	フィールドリフト移動
 * @brief   イベントコールをかけるので、return 0でスクリプト本体が終了してしまわないように、1を返す
 */
//-----------------------------------------------------------------------------
static BOOL EvCmdMoveFldLift(VM_MACHINE * core)
{
	FLIFT_MoveLift(core->fsys);
	return 1;
}

//-----------------------------------------------------------------------------
/**
 *	フィールドリフト有効性チェック
 */
//-----------------------------------------------------------------------------
static BOOL EvCmdCheckFldLift(VM_MACHINE * core)
{
	u16* ret_wk			= VMGetWork( core );
	if( FLIFT_CheckValid(core->fsys) ){
		(*ret_wk) = 1;
	}else{
		(*ret_wk) = 0;
	}
	return 0;
}

//-----------------------------------------------------------------------------
/**
 *	レイ・アイ・ハイ　シリンダーアニメセットアップ
 */
//-----------------------------------------------------------------------------
static BOOL EvCmdSetupRAHCyl(VM_MACHINE * core)
{
	RAH_CYL_ANM_Setup(core->fsys);
	return 0;
}

//-----------------------------------------------------------------------------
/**
 *	レイ・アイ・ハイ　シリンダーアニメスタート
 * @brief   イベントコールをかけるので、return 0でスクリプト本体が終了してしまわないように、1を返す
 */
//-----------------------------------------------------------------------------
static BOOL EvCmdStartRAHCyl(VM_MACHINE * core)
{
	RAH_CYL_ANM_StartFreeEvent(core->fsys);
	return 1;
}

//-----------------------------------------------------------------------------
/**
 *	スコアの加算
 */
//-----------------------------------------------------------------------------
static BOOL EvCmdAddScore(VM_MACHINE * core)
{
	u16	score_id = VMGetU16(core);
	
	RECORD_Score_Add(SaveData_GetRecord(core->fsys->savedata), score_id);
	return 0;
}

//----------------------------------------------------------------------------
/**
 *	@brief	指定のポケモンがパーティ内にいるかチェック
 */
//-----------------------------------------------------------------------------
static BOOL EvCmdPartyMonsNoCheck(VM_MACHINE * core)
{
	u16	monsno = VMGetWorkValue(core);
	u16* ret_wk			= VMGetWork( core );
	POKEPARTY* p_party = SaveData_GetTemotiPokemon( core->fsys->savedata );
	*ret_wk = PokeParty_PokemonCheck( p_party, monsno );	
	return 1;
}

//----------------------------------------------------------------------------
/**
 *	@brief	パーティ内のデオキシスのフォルムを変更
 */
//-----------------------------------------------------------------------------
static BOOL EvCmdPartyDeokisisuFormChange(VM_MACHINE * core)
{
	u16 form = VMGetWorkValue(core);
	POKEPARTY* p_party = SaveData_GetTemotiPokemon( core->fsys->savedata );
	int i;
	int monsno;
	int poke_count = PokeParty_GetPokeCount( p_party );
	POKEMON_PARAM* p_pp;
	ZUKAN_WORK* zw = SaveData_GetZukanWork( core->fsys->savedata );
	
	for( i=0; i<poke_count; i++ ){
		// ポケモンパーティ　ないのデオキシスチェック
		p_pp = PokeParty_GetMemberPointer( p_party, i );
		monsno = PokeParaGet( p_pp, ID_PARA_monsno, NULL );

		if( monsno == MONSNO_DEOKISISU ){

			// フォルム設定し、
			// パラメータの再計算	攻撃力とか
			PokeParaPut( p_pp, ID_PARA_form_no, &form );
			PokeParaCalc( p_pp );

			// 図鑑に登録
			ZukanWork_SetPokeGet( zw, p_pp );
		}
	}

	return 1;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ミノムッチ3種類ポケパーティにそろっているかチェック
 *
 *	@param	core
 */
//-----------------------------------------------------------------------------
static BOOL EvCmdCheckMinomuchiComp( VM_MACHINE * core )
{
	u16* ret_wk			= VMGetWork( core );
	POKEPARTY* p_party = SaveData_GetTemotiPokemon( core->fsys->savedata );
	int i,j;
	int monsno;
	BOOL check_result;
	int poke_count = PokeParty_GetPokeCount( p_party );
	POKEMON_PARAM* p_pp;
	int form_arry[ TEMOTI_POKEMAX ] = { 0x7ffffff,0x7ffffff,0x7ffffff,0x7ffffff,0x7ffffff,0x7ffffff };	// ありえない数字で初期化しておく
	int form;
	int form_count;
	
	form_count = 0;
	for( i=0; i<poke_count; i++ ){
		// ポケモンパーティ　ないのミノムッチチェック
		p_pp = PokeParty_GetMemberPointer( p_party, i );
		monsno = PokeParaGet( p_pp, ID_PARA_monsno, NULL );
		form = PokeParaGet( p_pp, ID_PARA_form_no, NULL );

		if( monsno == MONSNO_MINOMUTTI ){
			form_arry[ i ] = form;

			// 以前に自分と同じナンバーがない場合カウント
			check_result = FALSE;
			for( j=0; j<i; j++ ){

				// おんなじならフラグをTRUEに
				if( form_arry[ j ] == form ){
					check_result = TRUE;
				}
			}

			if( check_result == FALSE ){
				form_count ++;
			}
		}
	}

	*ret_wk = form_count;

	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * ポケッチをフックする
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 *
 * FLAG_CHANGE_LABELの時など、フィールドマップがない状態で使用しないと不具合が出ます。
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdPoketchHookSet( VM_MACHINE * core )
{
	EVENTWORK* ev = SaveData_GetEventWork( core->fsys->savedata );
	
	SysFlag_PoketchHookSet(ev);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ポケッチのフックを解除する
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 *
 * FLAG_CHANGE_LABELの時など、フィールドマップがない状態で使用しないと不具合が出ます。
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdPoketchHookReset( VM_MACHINE * core )
{
	EVENTWORK* ev = SaveData_GetEventWork( core->fsys->savedata );

	SysFlag_PoketchHookReset(ev);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 *	スロットマシーン
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdSlotMachine( VM_MACHINE * core )
{
	u16 id = VMGetWorkValue(core);
	EventCmd_SlotMachine(core->fsys->event, id);
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * 現在の時刻（時間:0-23)
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdGetNowHour( VM_MACHINE * core )
{
	u16* ret_wk			= VMGetWork( core );

	*ret_wk = EVTIME_GetHour(core->fsys);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 *	@brief	フィールドオブジェを揺らすアニメーションコマンド
 *
 *	@param	objid	フィールドOBJのID
 *	@param	count	u16:揺らす回数
 *	@param	spd		u16:揺らすスピード
 *	@param	ofsx	u16:揺らす幅X
 *	@param	ofsz	u16:揺らす幅Z
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdObjShakeAnm( VM_MACHINE * core )
{
	FIELD_OBJ_PTR fldobj;		//対象のフィールドOBJのポインタ
	u16	objid = VMGetWorkValue(core);
	u16	count = VMGetWorkValue(core);
	u16	spd = VMGetWorkValue(core);
	u16	ofsx = VMGetWorkValue(core);
	u16	ofsz = VMGetWorkValue(core);
	
	fldobj	= FieldOBJSys_OBJIDSearch( core->fsys->fldobjsys,objid);
	if( fldobj == NULL ){
		GF_ASSERT( (0) && "対象のフィールドOBJのポインタ取得失敗！" );
	}

	EventCmd_ObjShakeAnm(core->event_work,fldobj,count,spd,ofsx,ofsz);
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 *	@brief	フィールドオブジェをblinkさせるアニメーションコマンド
 *
 *	@param	objid	フィールドOBJのID
 *	@param	count	u16:on/off回数
 *	@param	time	u16:on/offのインターバル
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdObjBlinkAnm( VM_MACHINE * core )
{
	FIELD_OBJ_PTR fldobj;		//対象のフィールドOBJのポインタ
	u16	objid = VMGetWorkValue(core);
	u16	count = VMGetWorkValue(core);
	u16	time = VMGetWorkValue(core);
	
	fldobj	= FieldOBJSys_OBJIDSearch( core->fsys->fldobjsys,objid);
	if( fldobj == NULL ){
		GF_ASSERT( (0) && "対象のフィールドOBJのポインタ取得失敗！" );
	}

	EventCmd_ObjBlinkAnm(core->event_work,fldobj,count,time);
	return 1;
}
/**
 *	@brief	レジキングイベント　条件チェック
 */
static BOOL EvCmd_D20R0106Legend_IsUnseal( VM_MACHINE * core )
{
	u16* ret_val = GetEventWorkAdrs(core->fsys,VMGetU16(core)); 

	*ret_val = EventCheck_IsReziUnseal(core->fsys->savedata);
	return 0;
}

//==============================================================================
//
//	お洒落お姉さん
//
//==============================================================================
///お洒落お姉さんイベント：取得出来るアクセサリの開始番号
#define DRESSING_ACCE_START_NO		(IMC_ACCE_DROP00)
///お洒落お姉さんイベント：取得出来るアクセサリの最終番号
#define DRESSING_ACCE_END_NO		(IMC_ACCE_KIRAKIRA_POWDER00)
///お洒落お姉さんイベント：取得出来るアクセサリの種類数		(END_NOのも含めるので＋１)
#define DRESSING_ACCE_NUM			(DRESSING_ACCE_END_NO - DRESSING_ACCE_START_NO + 1)

//--------------------------------------------------------------------------------------------
/**
 * お洒落お姉さん：ランダムで取得出来るイメージクリップのアクセサリー番号取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 *
 * ret_wk = 取得したアクセサリーの番号、　0xffff＝取得出来なかった
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdDressingImcAcceCheck(VM_MACHINE * core)
{
	IMC_SAVEDATA* imc;
	IMC_ITEM_SAVEDATA* imc_item;
	u16 acce_no[DRESSING_ACCE_NUM];
	int i, set_count, get_pos, get_acce;
	u16* ret_wk	= VMGetWork( core );
	
	imc	= SaveData_GetImcSaveData( core->fsys->savedata );
	imc_item = ImcSaveData_GetItemSaveData( imc );	//アイテムセーブデータ取得
	
	set_count = 0;
	for(i = 0; i < DRESSING_ACCE_NUM; i++){
		if(ImcSaveData_CheckAcceAdd( imc_item, DRESSING_ACCE_START_NO + i, 1 ) == TRUE){
			acce_no[i] = TRUE;
			set_count++;
		}
	}
	if(set_count == 0){		//全てのアクセサリーが既に取得済み
		*ret_wk = 0xffff;
		return 0;
	}
	
	get_pos = gf_rand() % set_count;
	for(i = 0; i < DRESSING_ACCE_NUM; i++){
		if(acce_no[i] == TRUE){
			if(get_pos == 0){
				break;
			}
			else{
				get_pos--;
			}
		}
	}
	GF_ASSERT(i < DRESSING_ACCE_NUM);
	get_acce = DRESSING_ACCE_START_NO + i;
	
	*ret_wk = get_acce;
	return 0;
};


//----------------------------------------------------------------------------
/**
 *	@brief	ささっているAGBカートリッジ取得
 */
//-----------------------------------------------------------------------------
static BOOL EvCmdAgbCartridgeVerGet( VM_MACHINE * core )
{
	u16* ret_wk			= VMGetWork( core );
	*ret_wk = sys.AgbCasetteVersion;
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 *	地下で会話した人数の累計をクリア(ミカゲ用）
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdUnderGroundTalkCountClear(VM_MACHINE * core)
{
	EVENTWORK* ev = SaveData_GetEventWork(core->fsys->savedata);

	SysWork_UGTalkCountSet(ev,0);	//0set
	return 0;
}

//----------------------------------------------------------------------------
/**
 *	@brief	隠しマップフラグon/off
 */
//-----------------------------------------------------------------------------
static BOOL EvCmdHideMapStateChange( VM_MACHINE * core )
{
	u16	hidemap_id	= VMGetWorkValue(core);
	u8	flag	= VMGetU8(core);
	EVENTWORK *ev = SaveData_GetEventWork(core->fsys->savedata);
	
	if(flag){
		SysWork_HideMapWorkSet(ev, hidemap_id);
	}else{
		SysWork_HideMapWorkClear(ev, hidemap_id);
	}
	return 0;
}


//----------------------------------------------------------------------------
/**
 *	@brief	イメージクリップ「背景名」を文字バッファに設定
 */
//-----------------------------------------------------------------------------
static BOOL EvCmdImcBgNameSet( VM_MACHINE * core )
{

	WORDSET** wordset		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_WORDSET );
	u8 idx		= VMGetU8(core);
	u16	bg_no	= VMGetWorkValue(core);

	WORDSET_RegisterImageClibBgName( *wordset, idx, bg_no );

	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * スロットでレンチャンしているか
 * TRUE=10回以上 FALSE=10より下
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdSlotRentyanChk( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	EVENTWORK *ev = SaveData_GetEventWork(core->fsys->savedata);
	u16* ret_wk			= VMGetWork( core );
	u32 rs;

	rs = SysWork_RensyouCountGet(ev);

	if(rs >= 10){		//１０レンチャン以上？
		*ret_wk = TRUE;
	}else{
		*ret_wk = FALSE;
	}

	return	0;
}

//--------------------------------------------------------------------------------------------
/**
 * レベルでアイテム取得オヤジの数字取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdLevelJijiiNo(VM_MACHINE * core)	
{
	u16* ret_wk	= VMGetWork( core );

	*ret_wk = SysWork_PokeLevelNoGet( SaveData_GetEventWork(core->fsys->savedata) );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * イメージクリップ：アクセサリー：アイテムを減らす
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdImcAcceSubItem(VM_MACHINE * core)		
{
	IMC_SAVEDATA* imc;
	IMC_ITEM_SAVEDATA* imc_item;
	u16 acce_no	= VMGetWorkValue(core);
	u16 num		= VMGetWorkValue(core);

	imc	= SaveData_GetImcSaveData( core->fsys->savedata );
	imc_item = ImcSaveData_GetItemSaveData( imc );	//アイテムセーブデータ取得

	ImcSaveData_SubAcceFlag( imc_item, acce_no, num );
	return 0;
};


//----------------------------------------------------------------------------
/**
 *	@brief	ナギサシティ　シルベの灯台　双眼鏡カメラ設定
 */
//-----------------------------------------------------------------------------
static BOOL	EvCmdc08r0801ScopeCameraSet( VM_MACHINE * core )
{
	FIELDSYS_WORK* p_fsys = core->fsys;

	CallNagisaScopeEvent( p_fsys );
/*
	VecFx32 matrix;
	CAMERA_ANGLE angle;

	// カメラパラメータ設定
	GFC_SetCameraPerspWay( 0x8c1, p_fsys->camera_ptr );	
	GFC_SetCameraDistance( 0xf81b8, p_fsys->camera_ptr );
	matrix.x = 0x350523d;
	matrix.y = 0x15edb7;
	matrix.z = 0x23da40e;
	GFC_SetLookTarget( &matrix, p_fsys->camera_ptr );
	angle.x = 0x823;
	angle.y = 0x520;
	angle.z = 0;
	GFC_SetCameraAngleRev( &angle, p_fsys->camera_ptr );

	GFC_SetCameraClip( 12*FX32_ONE, 1564*FX32_ONE, p_fsys->camera_ptr );
//*/
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * レベルジジイ初期化
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdLevelJijiiInit(VM_MACHINE * core)		
{
	FIELDSYS_WORK* fsys = core->fsys;
	SAVEDATA * sv = fsys->savedata;

	SysWorkUpdatePokeLevelNo(sv);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 難解ことばをランダムでひとつ覚えさせる
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 *
 * もう全て覚えている場合:0xffff
 * 新規にことばを覚えた場合：単語ID（0 ～ PMSW_NANKAI_WORD_MAX-1）
 * 新規にことばを覚えた場合はさらに、buf_idで指定した箇所に文字列をWORDSETします。
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdNewNankaiWordSet(VM_MACHINE * core)
{
	PMSW_SAVEDATA *pmsw;
	u32 nankai_id;
	u16* ret_wk	= VMGetWork( core );
	u16 buf_id = VMGetWorkValue(core);
	WORDSET** wordset		= GetEvScriptWorkMemberAdrs( core->fsys, ID_EVSCR_WORDSET );

	pmsw = SaveData_GetPMSW( core->fsys->savedata );
	nankai_id = PMSW_SetNewNankaiWord( pmsw );
	
	if(nankai_id == PMSW_NANKAI_WORD_MAX){
		*ret_wk = 0xffff;
		return 0;
	}
	else{
		*ret_wk = nankai_id;
	}

	//難解言葉IDからWORDSETを行う
	{
		PMS_WORD pmsword;
		
		pmsword = PMSW_NankaiWord_to_PMSWORD(nankai_id);
		WORDSET_RegisterPMSWord( *wordset, buf_id, pmsword);
	}
	
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 難解ことばを全て覚えているかチェック
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 *
 * もう全て覚えている場合:TRUE, 覚えていないのがある：FALSE
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdNankaiWordCompleteCheck(VM_MACHINE * core)
{
	PMSW_SAVEDATA *pmsw;
	u16* ret_wk	= VMGetWork( core );

	pmsw = SaveData_GetPMSW( core->fsys->savedata );
	if(PMSW_CheckNankaiWordComplete( pmsw ) == TRUE){
		*ret_wk = TRUE;
	}
	else{
		*ret_wk = FALSE;
	}
	
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 常連チェック
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdRegularCheck( VM_MACHINE * core )
{
	FIELDSYS_WORK* fsys = core->fsys;
	EVENTWORK *ev = SaveData_GetEventWork(core->fsys->savedata);
	u16* ret_wk			= VMGetWork( core );
	u16 rs;

	rs = SysWork_RegularCountGet(ev);

	if(rs >= 5){
		*ret_wk = TRUE;
	}else{
		*ret_wk = FALSE;
	}

	return	0;
}

//--------------------------------------------------------------------------------------------
/**
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdBirthDayCheck(VM_MACHINE * core)
{
	u16 * ret_wk = VMGetWork(core);
	FIELDSYS_WORK * fsys = core->fsys;
	SYSTEMDATA * sysdt; 
	sysdt = SaveData_GetSystemData(core->fsys->savedata);

	if (SYSTEMDATA_GetBirthMonth(sysdt) == EVTIME_GetMonth(fsys)
			&& SYSTEMDATA_GetBirthDay(sysdt) == EVTIME_GetDay(fsys)) {
		*ret_wk = 1;
	} else {
		*ret_wk = 0;
	}
	return 0;

}


//--------------------------------------------------------------------------------------------
/**
 * アンノーン形状の見た数を取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdAnoonSeeNum( VM_MACHINE * core )
{
	const ZUKAN_WORK* zw	= SaveData_GetZukanWork( core->fsys->savedata );
	u16* ret_wk				= VMGetWork( core );

	*ret_wk = ZukanWork_GetPokeAnoonSeeNum( zw );
	return 0;
}


//--------------------------------------------------------------------------------------------
/**
 * @brief	戻らずの洞窟　マップ抽選
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdD17SystemMapSelect(VM_MACHINE * core)
{
	u8	pos,i;
	u16	id,x,z;
	u16	point = VMGetWorkValue(core);	//現在のポイント
	u16	total = VMGetWorkValue(core);	//延べ通過部屋数
	FIELDSYS_WORK * fsys = core->fsys;
	
	static const u16 zone_id[] = {
		 ZONE_ID_D17R0105,ZONE_ID_D17R0106,ZONE_ID_D17R0107,ZONE_ID_D17R0108,
		 ZONE_ID_D17R0109,ZONE_ID_D17R0110,ZONE_ID_D17R0111,ZONE_ID_D17R0112,
		 ZONE_ID_D17R0113,ZONE_ID_D17R0114,ZONE_ID_D17R0115,ZONE_ID_D17R0116,
		 ZONE_ID_D17R0117,ZONE_ID_D17R0118,ZONE_ID_D17R0119,ZONE_ID_D17R0120,
		 ZONE_ID_D17R0121,ZONE_ID_D17R0122,
	};

	id = 0;
	//プレイヤー現在座標取得
	x = fsys->location->grid_x;	//Player_NowGPosXGet( fsys->player );
	z = fsys->location->grid_z;	//Player_NowGPosZGet( fsys->player );

#ifdef PM_DEBUG
	//デバッグ機能としてLA押しっぱなしだと必ず当たり
	//デバッグ機能としてLB押しっぱなしだと必ずハズレになる
	//ゴール？
	if(point >= 3){
		id = ZONE_ID_D17R0104;
	}else if(total >= 30){	//リミット？
		id = ZONE_ID_D17R0102;
	}else if(gf_rand()%100 < 25){	//当たり？
		if((sys.cont & PAD_BUTTON_L) && (sys.cont & PAD_BUTTON_B)){
			id = gf_rand()%6;
			id = zone_id[id+(point*6)];
		}else{
			id = ZONE_ID_D17R0103;	//当たり
		}
	}else{
		//外れたのでどの部屋へ行くか抽選
		if((sys.cont & PAD_BUTTON_L) && (sys.cont & PAD_BUTTON_A)){
			id = ZONE_ID_D17R0103;
		}else{
			id = gf_rand()%6;
			id = zone_id[id+(point*6)];
		}
	}
#else
	//ゴール？
	if(point >= 3){
		id = ZONE_ID_D17R0104;
	}else if(total >= 30){	//リミット？
		id = ZONE_ID_D17R0102;
	}else if(gf_rand()%100 < 25){	//当たり？
		id = ZONE_ID_D17R0103;	//当たり
	}else{
		//外れたのでどの部屋へ行くか抽選
		static const u16 zone_id[] = {
		 ZONE_ID_D17R0105,ZONE_ID_D17R0106,ZONE_ID_D17R0107,ZONE_ID_D17R0108,
		 ZONE_ID_D17R0109,ZONE_ID_D17R0110,ZONE_ID_D17R0111,ZONE_ID_D17R0112,
		 ZONE_ID_D17R0113,ZONE_ID_D17R0114,ZONE_ID_D17R0115,ZONE_ID_D17R0116,
		 ZONE_ID_D17R0117,ZONE_ID_D17R0118,ZONE_ID_D17R0119,ZONE_ID_D17R0120,
		 ZONE_ID_D17R0121,ZONE_ID_D17R0122,
		};
		id = gf_rand()%6;
		id = zone_id[id+(point*6)];
//		id = ZONE_ID_D17R0103;
	}
#endif

	if(x == 11){	//上下
		if(z == 1){
			pos = 0;
		}else if(z == 20){
			pos = 2;
		}else{
			pos = 5;
		}
	}else{
		if(x == 20){
			pos = 1;
		}else{
			pos = 3;
		}
	}
	OS_Printf("d17sys now_zone=%d  now_pos= %d  (%d:%d)\n",id,pos,x,z);
	for(i = 0;i < 4;i++){
		if(i == pos){
			continue;
		}
		EventData_ConnectDataZoneChange( core->fsys, i, id );
	}
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 *	地下で道具をあげた人数の累計
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdUnderGroundToolGiveCount(VM_MACHINE * core)
{
	EVENTWORK* ev = SaveData_GetEventWork(core->fsys->savedata);
	u16* ret_wk	= VMGetWork( core );

	*ret_wk = SysWork_UGToolGiveCountGet(ev);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 *	地下でかせきを掘った回数の累計
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdUnderGroundKasekiDigCount(VM_MACHINE * core)
{
	EVENTWORK* ev = SaveData_GetEventWork(core->fsys->savedata);
	u16* ret_wk	= VMGetWork( core );

	*ret_wk = SysWork_UGKasekiDigCountGet(ev);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 *	地下でトラップにかけた回数の累計
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdUnderGroundTrapHitCount(VM_MACHINE * core)
{
	EVENTWORK* ev = SaveData_GetEventWork(core->fsys->savedata);
	u16* ret_wk	= VMGetWork( core );

	*ret_wk = SysWork_UGTrapHitCountGet(ev);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ポフィン追加
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 *
 * ret_wk = 味ID(追加出来なかった場合は0xffff)
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdPofinAdd( VM_MACHINE * core )
{
	PORUTO_DATA *porutodata;
	PORUTO_FLAVORID flaver_id;
	PORUTO_BLOCK *poruto_block;
	u8 prm[PORUTO_FTYPE_NUM];
	u8 taste;
	u16 add_index;
	u16 *ret_wk;
	int i;
	
	ret_wk = VMGetWork( core );
	for(i = 0; i < PORUTO_FTYPE_NUM; i++){
		prm[i] = VMGetU8( core );
	}
	taste = VMGetU8( core );
	
	//ポフィンデータ作成
	porutodata = PorutoData_AllocWork(HEAPID_FIELD);
	flaver_id = PorutoData_CalcParam(porutodata, prm, taste, FALSE);
	
	//ポフィンデータ追加
	poruto_block = SaveData_GetPorutoBlock(core->fsys->savedata);
	add_index = PORUTO_AddData(poruto_block, porutodata);
	
	sys_FreeMemoryEz(porutodata);
	
	if(add_index == PORUTO_DATA_NULL){
		*ret_wk = 0xffff;
	}
	else{
		*ret_wk = flaver_id;
	}

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ポフィンを追加出来るか確認
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 *
 * ret_wk = TRUE：追加できる、　FALSE:追加出来ない
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdPofinAddCheck( VM_MACHINE * core )
{
	PORUTO_BLOCK *poruto_block;
	u16 *ret_wk;
	
	ret_wk = VMGetWork( core );
	
	poruto_block = SaveData_GetPorutoBlock(core->fsys->savedata);
	if(PORUTO_SearchNullData(poruto_block) == PORUTO_DATA_NULL){
		*ret_wk = FALSE;
	}
	else{
		*ret_wk = TRUE;
	}

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 *	@brief	配布イベントマジックナンバーチェック
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdIsHaihuEventEnable(VM_MACHINE *core)
{
	u8		id = VMGetU8(core);
	u16*	ret_wk = VMGetWork(core);
	EVENTWORK* ev = SaveData_GetEventWork(core->fsys->savedata);
	
	GF_ASSERT( (id <= 3) && "SysWork_HaihuEventWorkCheck() id over\n" );
	
	*ret_wk = SysWork_HaihuEventWorkCheck(ev,id);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 殿堂入り回数を取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"1"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdDendouNumGet( VM_MACHINE * core )
{
	LOAD_RESULT result;
	const DENDOU_SAVEDATA* data;
	u16* ret_wk = VMGetWork( core );

	data = SaveData_Extra_LoadDendouData( core->fsys->savedata, HEAPID_EVENT, &result);

	if( result == LOAD_RESULT_NULL ){								///<データなし
		OS_Printf( "でんどうデータ LOAD_RESULT_NULL\n" );
		*ret_wk = 0;
		sys_FreeMemoryEz( (void*)data );
		return 1;

	}else if( result == LOAD_RESULT_OK ){							///<データ正常読み込み
		OS_Printf( "でんどうデータ LOAD_RESULT_OK\n" );
		*ret_wk = DendouData_GetRecordNumber( data, 0 );
		sys_FreeMemoryEz( (void*)data );
		return 1;

	}else if( result == LOAD_RESULT_NG ){							///<データ異常
		OS_Printf( "でんどうデータ LOAD_RESULT_NG\n" );
		*ret_wk = 0;
		sys_FreeMemoryEz( (void*)data );
		return 1;
	}

	*ret_wk = 0;
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	そだてやポケモン選択画面呼び出し
 *
 * @param	core	仮想マシン制御構造体へのポインタ
 *
 * @return	1		スクリプトからメイン制御に戻る
 *
 * @li EvCmdPokeListGetResultで、選択した位置を取得して、ワーク開放が必要
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdSodateyaPokeListSetProc(VM_MACHINE * core)
{
	void ** buf;
	u16 pos		= VMGetWorkValue(core);

	buf = GetEvScriptWorkMemberAdrs(core->fsys, ID_EVSCR_SUBPROC_WORK);
	*buf = SodateyaPokeListEvent_SetProc(HEAPID_EVENT, core->fsys, pos);

	VM_SetWait( core, EvCmdWaitSubProcEnd );
	return 1;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	そだてやポケモン選択画面呼び出し
 * @param	core		仮想マシン制御構造体へのポインタ
 * @return	1		スクリプトからメイン制御に戻る
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdSodateyaPokeListGetResult(VM_MACHINE * core)
{
	void ** buf;
	u16 * ret_wk, * ret_mode;

	ret_wk = VMGetWork(core);
	ret_mode = VMGetWork(core);
	buf = GetEvScriptWorkMemberAdrs(core->fsys, ID_EVSCR_SUBPROC_WORK);

	GF_ASSERT(*buf != 0);

	*ret_wk = FieldPokeListEvent_GetSelect(*buf);
	if (*ret_wk == PL_SEL_POS_EXIT) {
		*ret_wk = 0xff;
	}

	*ret_mode = FieldPokeListEvent_GetMode(*buf);
	if (*ret_mode == PL_RET_STATUS) {
		*ret_mode = 1;	//つよさをみる
	}
	else{
		*ret_mode = 0;	//通常
	}

	sys_FreeMemoryEz(*buf);
	*buf = NULL;

	return 0;
}



//--------------------------------------------------------------------------------------------
/**
 *	指定した確立でワークにTRUE,FALSEを返す
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdGetRandomHit( VM_MACHINE * core )
{
	u16	rnd;	
	u8	per = VMGetU8(core);
	u16	*ret_wk  = VMGetWork(core);

	if(per > 100){
		per = 100;
	}
	rnd = gf_rand()%101;
	if(rnd <= per){
		*ret_wk = 1;
	}else{
		*ret_wk = 0;
	}
	return 0;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ヒデンエフェクト　エフェクト開始
 */
//-----------------------------------------------------------------------------
static BOOL EvCmdHidenEffStart(VM_MACHINE * core)
{
	u16	effect_type = VMGetWorkValue(core);
	u16	*ret_wk  = VMGetWork(core);	// 終了検知ワーク
	FIELDSYS_WORK * fsys = core->fsys;

	switch( effect_type ){
	case 0:
		ScrCmd_HidenEffContStart( fsys, ret_wk, SCR_HIDENEFF_IAIGIRI, HEAPID_EVENT );
		break;
	case 1:
		ScrCmd_HidenEffContStart( fsys, ret_wk, SCR_HIDENEFF_IWAKUDAKI, HEAPID_EVENT );
		break;
	case 2:
		ScrCmd_HidenEffContStart( fsys, ret_wk, SCR_HIDENEFF_IWAKUDAKI_KUROGANE, HEAPID_EVENT );
		break;
	default:
		GF_ASSERT(0);
		break;
	}
	return 1;
}


//--------------------------------------------------------------------------------------------
/**
 *	地下で会話した人数の累計
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdUnderGroundTalkCount2(VM_MACHINE * core)
{
	EVENTWORK* ev = SaveData_GetEventWork(core->fsys->savedata);
	u16* ret_wk	= VMGetWork( core );

	*ret_wk = SysWork_UGTalkCount2Get(ev);
	return 0;
}

//----------------------------------------------------------------------------
/**
 *	@brief	地震発生
 */
//-----------------------------------------------------------------------------
static BOOL EvCmdZishin( VM_MACHINE * core )
{
	u16 pattarn	= VMGetWorkValue(core);
	if( pattarn == 0 ){
		FLD_MAP_DEMO_ZishinEventCall( core->fsys->event );
	}else{
		FLD_MAP_DEMO_MioZishinEventCall( core->fsys->event );
	}
	return 1;
}

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------------
/**
 * @brief	
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	0			スクリプトからメイン制御に戻る
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdCheckMyGSID(VM_MACHINE * core)
{
	u16* ret_wk	= VMGetWork( core );

	*ret_wk = mydwc_checkMyGSID( core->fsys->savedata );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	0			スクリプトからメイン制御に戻る
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdGetFriendDataNum(VM_MACHINE * core)
{
	u16* ret_wk	= VMGetWork( core );

	*ret_wk = WifiList_GetFriendDataNum( SaveData_GetWifiListData(core->fsys->savedata) );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	こんごうだま・しらたまのチェック
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdUgBallCheck(VM_MACHINE * core)
{
	u16 itemno = VMGetWorkValue(core);
	UNDERGROUNDDATA * ug = SaveData_GetUnderGroundData(core->fsys->savedata);

	if (itemno == ITEM_KONGOUDAMA || itemno == ITEM_SIRATAMA) {
		UnderGroundSetDiamondPearlEvent(ug);
	}
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	アウスのプレートのチェック
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdAusuItemCheck(VM_MACHINE * core)
{
	u16 itemno	= VMGetWorkValue(core);
	u16* ret_wk	= VMGetWork( core );

	*ret_wk = 0;

	//「ひのたまプレート」～「こうてつプレート」
	if( (itemno >= ITEM_HINOTAMAPUREETO) && (itemno <= ITEM_KOUTETUPUREETO) ){
		*ret_wk = 1;
	}

	return 0;
}

//=========================================================================================
//=========================================================================================
#include "msgdata\msg_fushigi_pwd.h"

//-----------------------------------------------------------------------------
/**
 *	あいことばが”おくりものフラグ”に該当するかチェック
 *	OUT *ret_wk  : 1:有効 0:無効
 */
//-----------------------------------------------------------------------------
static BOOL EvCmdAikotobaOkurimonoChk(VM_MACHINE * core)
{
	enum {
		USABLE_HEAPID = HEAPID_EVENT,
	};

	FIELDSYS_WORK * fsys	= core->fsys;
	u16* ret_wk				= VMGetWork( core );
	u16 word0		= VMGetWorkValue(core);
	u16 word1		= VMGetWorkValue(core);
	u16 word2		= VMGetWorkValue(core);
	u16 word3		= VMGetWorkValue(core);

	WORDSET* wordset = WORDSET_Create( USABLE_HEAPID );
	MSGDATA_MANAGER* msgman = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_fushigi_pwd_dat, USABLE_HEAPID );
	STRBUF* input_pwd;
	STRBUF* correct_pwd;

	WORDSET_RegisterPMSWord( wordset, 0, word0 );
	WORDSET_RegisterPMSWord( wordset, 1, word1 );
	WORDSET_RegisterPMSWord( wordset, 2, word2 );
	WORDSET_RegisterPMSWord( wordset, 3, word3 );

	input_pwd = MSGDAT_UTIL_AllocExpandString( wordset, msgman, STRID_fushigi_pwd_fmt, USABLE_HEAPID );
	correct_pwd = MSGMAN_AllocString( msgman, STRID_fushigi_pwd );

	*ret_wk = ( STRBUF_Compare( input_pwd, correct_pwd ) == 0 );

	STRBUF_Delete( input_pwd );
	STRBUF_Delete( correct_pwd );
	MSGMAN_Delete( msgman );
	WORDSET_Delete( wordset );

	return 0;
}

//-----------------------------------------------------------------------------
/**
 *	WIFIふしぎなおくりものオープンフラグセット
 */
//-----------------------------------------------------------------------------
static BOOL EvCmdWifiHusiginaokurimonoOpenFlagSet(VM_MACHINE * core)
{
	FIELDSYS_WORK * fsys	= core->fsys;
	SYSTEMDATA * sysdt; 
	sysdt = SaveData_GetSystemData(core->fsys->savedata);

	SYSTEMDATA_SetWifiMPOpenFlag(sysdt,1);
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * ユニオンルーム
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdUnionGetCardTalkNo( VM_MACHINE * core )
{
	FIELDSYS_WORK *fsys = core->fsys;
	u16* ret_wk				= VMGetWork( core );

	WORDSET** wordset	= GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_WORDSET );

	*ret_wk = Union_GetCardTalkNo(*wordset );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 	WirelessIconEasy呼び出し
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdWirelessIconEasy( VM_MACHINE * core )
{
	WirelessIconEasy();
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 	WirelessIconEasyEnd呼び出し
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdWirelessIconEasyEnd( VM_MACHINE * core )
{
	WirelessIconEasyEnd();
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 主人公の位置を正しく記録するためにフィールド情報をSAVEDATAに反映させる
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdSaveFieldObj( VM_MACHINE * core )
{
	Field_SaveFieldObj( core->fsys );
	return 0;
}

//-----------------------------------------------------------------------------
/**
 *	@brief	エスケープロケーションを直接書き換える
 */
//-----------------------------------------------------------------------------
static BOOL EvCmdSetEscapeLocation(VM_MACHINE* core)
{
	u16	zone_id = VMGetWorkValue(core);
	u16	grid_x = VMGetWorkValue(core);
	u16	grid_z = VMGetWorkValue(core);
	SITUATION * sit = SaveData_GetSituation(core->fsys->savedata);
	LOCATION_WORK* loc = Situation_GetEscapeLocation(sit);

	loc->zone_id = zone_id;
	loc->grid_x = grid_x;
	loc->grid_z = grid_z;
	loc->door_id = DOOR_ID_JUMP_CODE;
	loc->dir = DIR_DOWN;
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * OBJ同士の当たり判定フラグを設定
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdFieldObjBitSetFellowHit( VM_MACHINE * core )
{
	FIELD_OBJ_PTR fldobj;
	u16	obj_id	= VMGetWorkValue(core);
	u16	flag	= VMGetU8(core);
	
	//対象のフィールドOBJのポインタ取得
	fldobj = FieldOBJSys_OBJIDSearch( core->fsys->fldobjsys, obj_id );

	if( fldobj == NULL ){
		GF_ASSERT( (0) && "指定したIDに該当するデータがありませんでした！" );
	}

	FieldOBJ_StatusBitSet_FellowHit( fldobj, flag );
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * トレーナーカードランク取得
 *
 * @param	core		仮想マシン制御構造体へのポインタ
 *
 * @return	"0"
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdGetCardRank( VM_MACHINE * core )
{
	FIELDSYS_WORK *fsys = core->fsys;
	u16* ret_wk				= VMGetWork( core );

	*ret_wk = TRCSET_GetCardRank(fsys);
	return 0;
}


//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
static BOOL EvCmdReportInfoWinOpen( VM_MACHINE * core )
{
	FIELDSYS_WORK * fsys = core->fsys;
	REPORT_INFO ** riw = GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_REPORTWIN );
	if (!SaveData_IsOverwritingOtherData(fsys->savedata)) {
		*riw = ReportInfo_Create(fsys, HEAPID_FIELD, FLD_MBGFRM_FONT);
		ReportInfo_WriteWindow(*riw);
	}
	return 0;
}


//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
static BOOL EvCmdReportInfoWinClose( VM_MACHINE * core )
{
	FIELDSYS_WORK * fsys = core->fsys;
	REPORT_INFO ** riw = GetEvScriptWorkMemberAdrs( fsys, ID_EVSCR_REPORTWIN );
	if (!SaveData_IsOverwritingOtherData(fsys->savedata)) {
		ReportInfo_EraseWindow(*riw);
		ReportInfo_Delete(*riw);
	}
	return 0;
}


//--------------------------------------------------------------------------------------------
/**
 * @brief		スクリプトコマンド：望遠鏡モードセット
 * @param		core
 */
//--------------------------------------------------------------------------------------------
static BOOL EvCmdFieldScopeModeSet( VM_MACHINE * core )
{
	FldFlg_SetScopeMode( core->fsys, VMGetU8(core) );
	return 0;
}
