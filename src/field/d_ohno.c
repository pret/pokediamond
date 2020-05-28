//=============================================================================
/**
 * @file	d_ohno.c
 * @bfief	大野用デバッグルーチン
 * @author	katsumi ohno
 * @date	05/07/08
 */
//=============================================================================

#ifdef PM_DEBUG

#include "common.h"
#include "system/bmp_list.h"
#include "system/fontproc.h"
#include "system/bmp_menu.h"
#include "system/window.h"
#include "system/pm_str.h"
#include "field/fieldsys.h"

#include "communication/communication.h"
#include "underground/ug_manager.h"
#include "comm_field_state.h"
#include "comm_command_field.h"

#include "comm_player.h"
#include "comm_direct_counter.h"
#include "fieldmap.h"
#include "fld_bmp.h"
#include "ev_mapchange.h"
#include "sysflag.h"

#include "system/wordset.h"
#include "msgdata/msg_underworld.h"

#include "script.h"							//StartFieldScript

#include "..\fielddata\script\common_scr_def.h"		//SCRID_TRAINER_MOVE_SCRIPT
#include "..\fielddata\script\connect_def.h"		//SCRID_CONNECT_COLOSSEUM

#include "msgdata/msg.naix"
#include "msgdata/msg_debug_ohno.h"

#include "savedata/fushigi_data.h"
#include "savedata/undergrounddata.h"
#include "fielddata/base_goods/goods_id_def.h"
#include "field_subproc.h"
#include "wifi_autoregist.h"
#include "comm_regulation.h"
#include "poketool/poke_regulation.h"
#include "tv_topic.h"

#include "..\fielddata\script\debug_scr_def.h"	//

//==============================================================================
// extern宣言
//==============================================================================

#include "d_ohno.h"

//==============================================================================
// 定義
//==============================================================================

//#define COMM_DEBUG (1)   // 通信のデバッグをする場合定義する

// メニューをタスクに登録していく際のプライオリティー
// 重ねるごとにあがるようにするため定義しておく
enum menuTaskPri_e {
    _MENU_ROLE_PRI = 0,
    _MENU_TALK_PRI = _MENU_ROLE_PRI,
    _MENU_SELECT_PARENT_PRI = 0,
    _MENU_WAIT_PRI = 0,
    _MENU_CHILD_LIST_PRI = 0,
    _MENU_UG_PRI = 10000,
};


#define _TCB_COMMCHECK_PRT   (10)    ///< フィールドを歩く通信の監視ルーチンのPRI
#define _EVWIN_MSG_BUF_SIZE		(50*2)			//メッセージバッファサイズ


// ネットワーク状況構造体
typedef struct{
    FIELDSYS_WORK* pFSys;
    GF_BGL_BMPWIN win;		// BMPウィンドウワーク
    BMPLIST_WORK* lw;		// BMPメニューワーク
    MSGDATA_MANAGER* msgman;
    BMPMENU_WORK* pYesNoWork;
	BMPLIST_DATA*   menulist;
    WORDSET* pWordSetMain;  //ワードセット構造体
	STRBUF* pStrBuf[2]; // メッセージを合成して出力する場合の格納場所
    pEndFunc func;
    u32 list_id;
    u16 connectIndex;  // つなぐ親機のINDEX
    s16 packetByte;   // デバッグで送信するパケットバイト
    //	u8 mode;
    u8 waitMode;
    u8 endState;
    u8 work;
} _NET_INFO_WORK;

static _NET_INFO_WORK* _pNet = NULL;

#define _LOCAL_WIN_PX (2)   // GF_BGL_BmpAddで使用する 文字ウインドウのPX値
#define _LOCAL_WIN_PY (18)   // GF_BGL_BmpAddで使用する 文字ウインドウのPY値
#define _LOCAL_WIN_SX (28)   // GF_BGL_BmpAddで使用する 文字ウインドウのSX値
#define _LOCAL_WIN_SY (4)   // GF_BGL_BmpAddで使用する 文字ウインドウのSY値


//==============================================================================
//	型宣言
//==============================================================================
typedef void (*pNetFunc)(_NET_INFO_WORK *);

//==============================================================================
// static宣言
//==============================================================================

static void _listCreate(_NET_INFO_WORK* pNet,u8 x,u8 y,u8 width,u8 height,u16 chrofs, int length);
// 親機　子機選択
static void _roleMenuFunc(TCB_PTR tcb, void* work);
static void _roleMenuEnd(TCB_PTR tcb,_NET_INFO_WORK* pNet);
static void _commScriptBattle(_NET_INFO_WORK* pNet);
static void _commScriptContest(_NET_INFO_WORK* pNet);
static void _commBattleChild( _NET_INFO_WORK* pNet );
static void _battleChildMenuFunc(TCB_PTR tcb, void* work);
static void _commBattleChildConnect( _NET_INFO_WORK* pNet );
static void _commBattleParent( _NET_INFO_WORK* pNet );
static void _battleParentMenuFunc(TCB_PTR tcb, void* work);
static void _commBattleParentConnect( _NET_INFO_WORK* pNet );

static void _commContestChildConnect( _NET_INFO_WORK* pNet );
static void _commContestParentConnect( _NET_INFO_WORK* pNet );

   // フィールドを動く通信中の通信の監視
static void _commCheckFunc(TCB_PTR tcb, void* work);

//通信量を変更するデバッグ　＝　通信負荷
static void _commSendQuantity(_NET_INFO_WORK* pNetOld);
static void _commSendQuantityLineCallBack(void);
static void _commSendQuantityFunc(TCB_PTR tcb, void* work);

static void _commAutoMove(_NET_INFO_WORK* pNet);
static void _commUnder(_NET_INFO_WORK* pNet);
static void _commUnder1(_NET_INFO_WORK* pNet);
static void _commUnder2(_NET_INFO_WORK* pNet);
static void _commUnderParent(_NET_INFO_WORK* pNet);
static void _commUnderChild(_NET_INFO_WORK* pNet);
static void _commUnderNormal(_NET_INFO_WORK* pNet);
static void _commPcGoods(_NET_INFO_WORK* pNet);
static void _commGoodsPenaDel(_NET_INFO_WORK* pNet);
static void _commBagTrap(_NET_INFO_WORK* pNet);
static void _commDigFossil(_NET_INFO_WORK* pNet);
static void _commWifiNote(_NET_INFO_WORK* pNet);
static void _commWifiMatch(_NET_INFO_WORK* pNet);
static void _commPlatina(_NET_INFO_WORK* pNet);
static void _commPlatinaReturn(_NET_INFO_WORK* pNet);
static void _commWifiFriend(_NET_INFO_WORK* pNet);
static void _commDelay(_NET_INFO_WORK* pNet);
static void _commDebugDisp(_NET_INFO_WORK* pNet);
static void _stoneAdd99(_NET_INFO_WORK* pNet);
static void _stoneDAndP(_NET_INFO_WORK* pNet);
static void _underRecordMax(_NET_INFO_WORK* pNet);
static void _friendMax(_NET_INFO_WORK* pNet);

static void _flagLevelChangeFunc(TCB_PTR tcb, void* work);
static void _flagLevelChangeStart(_NET_INFO_WORK* pNetOld);
static void _flagChange(_NET_INFO_WORK* pNet);

//==============================================================================
// ワーク
//==============================================================================

//==============================================================================
//	親子選択メニューリスト用データ等
//==============================================================================
static const struct {
	u32  str_id;
	u32  param;
}DebugMenuList[] = {
//	{ DebugOhno_ScriptBattle, (u32)_commScriptBattle },
//	{ DebugOhno_ScriptContest, (u32)_commScriptContest },
//    { DebugOhno_EasyBattle_Child, (u32)_commBattleChild },
//    { DebugOhno_EasyBattle_Parent, (u32)_commBattleParent },
//    { DebugOhno_EasyContest_Child, (u32)_commContestChildConnect },
//    { DebugOhno_EasyContest_Parent, (u32)_commContestParentConnect },
    { DebugOhno_CommQuantity, (u32)_commSendQuantity },
    { DebugOhno_AutoMove,  (u32)_commDelay },
    { DebugOhno_WifiMatch,  (u32)_commWifiMatch},
    { DebugOhno_WifiFriend,  (u32)_commWifiFriend},
    { DebugOhno_Platina,(u32)_commPlatina},
    { DebugOhno_PlatinaReturn,(u32)_flagLevelChangeStart},
    { DebugOhno_DigFossil, (u32)_commDigFossil},
    { DebugOhno_Trap,  (u32)_commBagTrap },
    { DebugOhno_Goods,  (u32)_commPcGoods },
    { DebugOhno_GoodsPenaDel,  (u32)_commGoodsPenaDel },
    { DebugOhno_Stone99, (u32)_stoneAdd99 },
    { DebugOhno_RecordMax,  (u32)_underRecordMax },
    { DebugOhno_FriendMax,  (u32)_friendMax },
    { DebugOhno_DANDP, (u32)_stoneDAndP },
    { DebugOhno_Channel,(u32)DebugOhnoCommDebugDisp },
    { DebugOhno_Down0004,  (u32)_commUnderParent },
    { DebugOhno_Down0005,  (u32)_commUnderChild },
    { DebugOhno_Down0006,  (u32)_commUnderNormal},
    { DebugOhno_Down,  (u32)_commUnder },
    { DebugOhno_Down0002,  (u32)_commUnder1 },
    { DebugOhno_Down0003,  (u32)_commUnder2 },


};

///親子選択メニューのリスト
static const BMPLIST_HEADER DebugMenuListHeader = {
    NULL,			// 表示文字データポインタ
    NULL,					// カーソル移動ごとのコールバック関数
    NULL,					// 一列表示ごとのコールバック関数
    NULL,                   // 
    NELEMS(DebugMenuList),	// リスト項目数
    5,	// 表示最大項目数
    0,						// ラベル表示Ｘ座標
    8,						// 項目表示Ｘ座標
    0,						// カーソル表示Ｘ座標
    0,						// 表示Ｙ座標
    FBMP_COL_BLACK,			// 文字色
    FBMP_COL_WHITE,			// 背景色
    FBMP_COL_BLK_SDW,		// 文字影色
    0,						// 文字間隔Ｘ
    16,						// 文字間隔Ｙ
    BMPLIST_LRKEY_SKIP,		// ページスキップタイプ
    FONT_SYSTEM,				// 文字指定
    0,						// ＢＧカーソル(allow)表示フラグ(0:ON,1:OFF)
    NULL                    // work
};

//==============================================================================
// 関数
//==============================================================================

//--------------------------------------------------------------
/**
 * @brief   汎用リストの作成
 * @param   header リストヘッダー
 * @param   x,y   開始座標
 * @param   width,height  幅高さ
 * @param   chrofs  キャラクターをおくオフセット
 * @retval  none
 */
//--------------------------------------------------------------
static void _listCreate(_NET_INFO_WORK* pNet, u8 x,u8 y,u8 width,u8 height,u16 chrofs,int length)
{
    BMPLIST_HEADER list_h;
    //BMPウィンドウ生成
    GF_BGL_BmpWinAdd(pNet->pFSys->bgl,&pNet->win,
                     GF_BGL_FRAME3_M, x, y, width, height, FLD_SYSFONT_PAL, chrofs);
    BmpMenuWinWrite(&pNet->win, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL );
    list_h = DebugMenuListHeader;
	list_h.list = pNet->menulist;
    list_h.win = &pNet->win;
    list_h.count = length;
    if(length > 8){
        list_h.line = 8;
    }
    else{
        list_h.line = length;
    }
    pNet->lw = BmpListSet(&list_h, 0, 0, HEAPID_FIELD);
    GF_BGL_BmpWinOn(&pNet->win);
}

//==============================================================================
/**
 * 通信のデバッグの起動を行う
 * @param   none
 * @retval  none
 */
//==============================================================================

void DebugCommMenuInit(void* pFieldSys)
{
    _NET_INFO_WORK* pNet;
    FIELDSYS_WORK* pFSys = pFieldSys;

    pNet = sys_AllocMemory(HEAPID_FIELD, sizeof(_NET_INFO_WORK));
    MI_CpuFill8(pNet, 0, sizeof(_NET_INFO_WORK));
    pNet->pFSys = (FIELDSYS_WORK*)pFieldSys;


	pNet->menulist = BMP_MENULIST_Create( NELEMS(DebugMenuList), HEAPID_FIELD );
	{
		MSGDATA_MANAGER* msgman;
		int i;

		msgman = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_debug_ohno_dat, HEAPID_FIELD);
		for(i=0; i<NELEMS(DebugMenuList); i++)
		{
			BMP_MENULIST_AddArchiveString( pNet->menulist, msgman, DebugMenuList[i].str_id, DebugMenuList[i].param );
		}
		MSGMAN_Delete(msgman);
	}

    _listCreate(pNet,1,1,14, 8*2,
                FLD_MENU_WIN_CGX - NELEMS(DebugMenuList)*2, NELEMS(DebugMenuList));

    TCB_Add(_roleMenuFunc, pNet, _MENU_ROLE_PRI);
}

//--------------------------------------------------------------
/**
 * @brief   親子役割を決めるメニュー実行部分
 * @param   tcb			TCBへのポインタ
 * @param   work		ワークデータのポインタ
 * @retval  none
 */
//--------------------------------------------------------------
static void _roleMenuFunc(TCB_PTR tcb, void* work)
{
    _NET_INFO_WORK* pNet = work;
    u32	ret;

    ret = BmpListMain(pNet->lw);
    switch(ret){
    case BMPLIST_NULL:
        break;
    case BMPLIST_CANCEL:
        _roleMenuEnd(tcb, pNet);
        sys_FreeMemoryEz(pNet);
        FieldSystemProc_SeqHoldEnd();
        break;
    default:
        _roleMenuEnd(tcb, pNet);
        {
            pNetFunc func = (pNetFunc)ret;
            func(pNet);  // 関数ジャンプ
        }
        sys_FreeMemoryEz(pNet);
        break;
    }
}

//--------------------------------------------------------------
/**
 * @brief   親子選択メニューリストを閉じる
 * @param   tcb			TCBへのポインタ
 * @param   pNet		ネットワーク状況構造体のポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static void _roleMenuEnd(TCB_PTR tcb,_NET_INFO_WORK* pNet)
{
	BmpMenuWinClear(&pNet->win, WINDOW_TRANS_ON );
    BMP_MENULIST_Delete( pNet->menulist );
    BmpListExit(pNet->lw, NULL, NULL);
    GF_BGL_BmpWinOff(&pNet->win);
    GF_BGL_BmpWinDel(&pNet->win);
    TCB_Delete(tcb);
}

//--------------------------------------------------------------
/**
 * @brief   通信ダイレクト接続カウンターのメニューを起動
 * @param   pNet		ワークデータのポインタ
 * @retval  none
 */
//--------------------------------------------------------------
static void _commScriptBattle(_NET_INFO_WORK* pNet)
{
    FieldSystemProc_SeqHoldEnd();
	//話しかけ対象OBJのポインタは"NULL"なので注意！
	EventSet_Script( pNet->pFSys, SCRID_CONNECT_COLOSSEUM, NULL );
	//EventSet_Script( pNet->pFSys, SCRID_CONNECT_UNION, NULL );
	//EventSet_Script( pNet->pFSys, SCRID_CONNECT_RECORD, NULL );
}

//--------------------------------------------------------------
/**
 * @brief   通信ダイレクト接続カウンターのメニューを起動
 * @param   pNet		ワークデータのポインタ
 * @retval  none
 */
//--------------------------------------------------------------
static void _commScriptContest(_NET_INFO_WORK* pNet)
{
    FieldSystemProc_SeqHoldEnd();
	//話しかけ対象OBJのポインタは"NULL"なので注意！
    EventSet_Script( pNet->pFSys, SCRID_CONNECT_CONTEST, NULL );
}

//==============================================================================
//	親子選択メニューリスト用データ等
//==============================================================================
///親子選択メニューの項目メッセージ
static const struct {
	u32  str_id;
	u32  param;
}DebugBattleChildMenuList[] = {
	{ DebugOhno_EasyBattle_Child0001, (u32)_commBattleChildConnect },
	{ DebugOhno_EasyBattle_Child0002, (u32)_commBattleChildConnect },
    { DebugOhno_EasyBattle_Child0003, (u32)_commBattleChildConnect },
    { DebugOhno_EasyBattle_Child0004, (u32)_commBattleChildConnect },
    { DebugOhno_EasyBattle_Child0005, (u32)_commBattleChildConnect },
};

//--------------------------------------------------------------
/**
 * @brief   バトルの簡易接続を行う
 * @param   pNet		ワークデータのポインタ
 * @retval  none
 */
//--------------------------------------------------------------
static void _commBattleChild(_NET_INFO_WORK* pNetOld)
{
    _NET_INFO_WORK* pNet;

    pNet = sys_AllocMemory(HEAPID_FIELD, sizeof(_NET_INFO_WORK));
    MI_CpuFill8(pNet, 0, sizeof(_NET_INFO_WORK));
    pNet->pFSys = pNetOld->pFSys;

	pNet->menulist = BMP_MENULIST_Create( NELEMS(DebugBattleChildMenuList), HEAPID_FIELD );
	{
		MSGDATA_MANAGER* msgman;
		int i;

		msgman = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_debug_ohno_dat, HEAPID_FIELD);
		for(i=0; i<NELEMS(DebugBattleChildMenuList); i++)
		{
			BMP_MENULIST_AddArchiveString( pNet->menulist, msgman, DebugBattleChildMenuList[i].str_id, DebugBattleChildMenuList[i].param );
		}
		MSGMAN_Delete(msgman);
	}

    _listCreate(pNet,1,1,14,
                NELEMS(DebugBattleChildMenuList)*2,
                FLD_MENU_WIN_CGX - NELEMS(DebugBattleChildMenuList)*2, NELEMS(DebugBattleChildMenuList));
    TCB_Add(_battleChildMenuFunc, pNet, _MENU_ROLE_PRI);
}

//--------------------------------------------------------------
/**
 * @brief   親子役割を決めるメニュー実行部分
 * @param   tcb			TCBへのポインタ
 * @param   work		ワークデータのポインタ
 * @retval  none
 */
//--------------------------------------------------------------
static void _battleChildMenuFunc(TCB_PTR tcb, void* work)
{
    _NET_INFO_WORK* pNet = work;
    u32	ret;

    ret = BmpListMain(pNet->lw);
    switch(ret){
    case BMPLIST_NULL:
        break;
    case BMPLIST_CANCEL:
        _roleMenuEnd(tcb, pNet);
        sys_FreeMemoryEz(pNet);
        FieldSystemProc_SeqHoldEnd();
        break;
    default:
        _roleMenuEnd(tcb, pNet);
        {
            pNetFunc func = (pNetFunc)ret;
            func(pNet);  // 関数ジャンプ
        }
        sys_FreeMemoryEz(pNet);
        break;
    }
}

static void _commBattleChildConnect( _NET_INFO_WORK* pNet )
{
    u16 cur;

    FieldSystemProc_SeqHoldEnd();
    BmpListDirectPosGet(pNet->lw, &cur);

//    CommSelectParentWindowOpen(pNet->pFSys,cur+1,0,0);
//    CommStateConnectBattleChild_Debug(pNet->pFSys, cur+1, 0);

    CommDirectConnectSetParam_Debug(pNet->pFSys, cur+COMM_MODE_BATTLE_SINGLE, 0, 0);
    EventSet_Script( pNet->pFSys, SCRID_CONNECT_COLOSSEUM_DEBUG_KO, NULL );
/*  SCRID_CONNECT_COLOSSEUM_DEBUG_OYA
  SCRID_CONNECT_COLOSSEUM_DEBUG_KO
  SCRID_CONNECT_CONTEST_DEBUG_OYA
  SCRID_CONNECT_CONTEST_DEBUG_KO*/

    
}

//==============================================================================
//	親子選択メニューリスト用データ等
//==============================================================================
///親子選択メニューの項目
static const struct {
	u32  str_id;
	u32  param;
}DebugBattleMenuList[] = {
	{ DebugOhno_EasyBattle_Parent0001, (u32)_commBattleParentConnect },
	{ DebugOhno_EasyBattle_Parent0002, (u32)_commBattleParentConnect },
    { DebugOhno_EasyBattle_Parent0003, (u32)_commBattleParentConnect },
    { DebugOhno_EasyBattle_Parent0004, (u32)_commBattleParentConnect },
    { DebugOhno_EasyBattle_Parent0005, (u32)_commBattleParentConnect },
};

//--------------------------------------------------------------
/**
 * @brief   バトルの簡易接続を行う
 * @param   pNet		ワークデータのポインタ
 * @retval  none
 */
//--------------------------------------------------------------
static void _commBattleParent(_NET_INFO_WORK* pNetOld)
{
    _NET_INFO_WORK* pNet;

    pNet = sys_AllocMemory(HEAPID_FIELD, sizeof(_NET_INFO_WORK));
    MI_CpuFill8(pNet, 0, sizeof(_NET_INFO_WORK));
    pNet->pFSys = pNetOld->pFSys;
	pNet->menulist = BMP_MENULIST_Create( NELEMS(DebugBattleMenuList), HEAPID_FIELD );
	{
		MSGDATA_MANAGER* msgman;
		int i;

		msgman = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_debug_ohno_dat, HEAPID_FIELD);
		for(i=0; i<NELEMS(DebugBattleMenuList); i++)
		{
			BMP_MENULIST_AddArchiveString( pNet->menulist, msgman, DebugBattleMenuList[i].str_id, DebugBattleMenuList[i].param );
		}
		MSGMAN_Delete(msgman);
	}
    _listCreate(pNet,1,1,14,
                NELEMS(DebugBattleMenuList)*2,
                FLD_MENU_WIN_CGX - NELEMS(DebugMenuList)*2,NELEMS(DebugBattleMenuList));
    TCB_Add(_battleParentMenuFunc, pNet, _MENU_ROLE_PRI);
}

//--------------------------------------------------------------
/**
 * @brief   親子役割を決めるメニュー実行部分
 * @param   tcb			TCBへのポインタ
 * @param   work		ワークデータのポインタ
 * @retval  none
 */
//--------------------------------------------------------------
static void _battleParentMenuFunc(TCB_PTR tcb, void* work)
{
    _NET_INFO_WORK* pNet = work;
    u32	ret;

    ret = BmpListMain(pNet->lw);
    switch(ret){
    case BMPLIST_NULL:
        break;
    case BMPLIST_CANCEL:
        _roleMenuEnd(tcb, pNet);
        sys_FreeMemoryEz(pNet);
        FieldSystemProc_SeqHoldEnd();
        break;
    default:
        _roleMenuEnd(tcb, pNet);
        {
            pNetFunc func = (pNetFunc)ret;
            func(pNet);  // 関数ジャンプ
        }
        sys_FreeMemoryEz(pNet);
        break;
    }
}

static void _commBattleParentConnect( _NET_INFO_WORK* pNet )
{
    u16 cur;

    FieldSystemProc_SeqHoldEnd();
    BmpListDirectPosGet(pNet->lw, &cur);
    //CommChildWindowOpen(pNet->pFSys,cur+1,0,0);
//    CommStateEnterBattleParent_Debug(pNet->pFSys,cur+1);
    CommDirectConnectSetParam_Debug(pNet->pFSys, cur+COMM_MODE_BATTLE_SINGLE, 0, 0);
    EventSet_Script( pNet->pFSys, SCRID_CONNECT_COLOSSEUM_DEBUG_OYA, NULL );
/*  SCRID_CONNECT_COLOSSEUM_DEBUG_OYA
  SCRID_CONNECT_COLOSSEUM_DEBUG_KO
  SCRID_CONNECT_CONTEST_DEBUG_OYA
  SCRID_CONNECT_CONTEST_DEBUG_KO*/
}


//--------------------------------------------------------------
/**
 * @brief   コンテスト接続テスト
 * @param   tcb			TCBへのポインタ
 * @param   work		ワークデータのポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static void _commContestChildConnect( _NET_INFO_WORK* pNet )
{
    u16 cur;

    FieldSystemProc_SeqHoldEnd();
    BmpListDirectPosGet(pNet->lw, &cur);

    CommDirectConnectSetParam_Debug(pNet->pFSys, COMM_MODE_CONTEST, 0, 0);
    EventSet_Script( pNet->pFSys, SCRID_CONNECT_CONTEST_DEBUG_KO, NULL );
}

static void _commContestParentConnect( _NET_INFO_WORK* pNet )
{
    u16 cur;

    FieldSystemProc_SeqHoldEnd();
    BmpListDirectPosGet(pNet->lw, &cur);

    CommDirectConnectSetParam_Debug(pNet->pFSys, COMM_MODE_CONTEST, 0, 0);
    EventSet_Script( pNet->pFSys, SCRID_CONNECT_CONTEST_DEBUG_OYA, NULL );
}



//==============================================================================
//	通信量変更メニューリスト用データ等
//==============================================================================
///通信量変更メニューの項目メッセージ
static const struct {
	u32  str_id;
	u32  param;
}DebugSendQuantityMenuList[] = {
	{ DebugOhno_ID, (u32)0 },
};


#define _DEBUG_QUANTITY_MAX (250)   /// テスト送信量 250に設定  

//--------------------------------------------------------------
/**
 * @brief   通信量を変更するデバッグウインドウを開く
 * @param   pNet		ワークデータのポインタ
 * @retval  none
 */
//--------------------------------------------------------------
static void _commSendQuantity(_NET_INFO_WORK* pNetOld)
{
    _NET_INFO_WORK* pNet;
    int i;
    const int length = NELEMS(DebugSendQuantityMenuList);

    if(!CommIsInitialize()){
        FieldSystemProc_SeqHoldEnd();
        return;
    }

    
    pNet = sys_AllocMemory(HEAPID_FIELD, sizeof(_NET_INFO_WORK));
    MI_CpuFill8(pNet, 0, sizeof(_NET_INFO_WORK));
    _pNet = pNet;
    pNet->pFSys = pNetOld->pFSys;
	pNet->menulist = BMP_MENULIST_Create( length, HEAPID_FIELD );
    pNet->pWordSetMain = WORDSET_Create(HEAPID_FIELD);
    pNet->packetByte = 0;
    for(i = 0;i < 2; i++){
        pNet->pStrBuf[i] = STRBUF_Create( _EVWIN_MSG_BUF_SIZE, HEAPID_FIELD);
    }
    pNet->msgman = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_debug_ohno_dat, HEAPID_FIELD);
    {
		int i;
        for(i=0; i< length; i++){
			BMP_MENULIST_AddArchiveString( pNet->menulist,
                                           pNet->msgman,
                                           DebugSendQuantityMenuList[i].str_id,
                                           DebugSendQuantityMenuList[i].param );
		}
	}
    _listCreate(pNet, 1, 1, 24,
                length*2, FLD_MENU_WIN_CGX - length*2,NELEMS(DebugSendQuantityMenuList));
    TCB_Add(_commSendQuantityFunc, pNet, _MENU_ROLE_PRI);

#if 0
    CommCommandThrowOut();
#endif
}

//--------------------------------------------------------------
/**
 * @brief   一ラインコールバック
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

static void _commSendQuantityLineCallBack(void)
{
    u16 idx=0;

    if(_pNet->lw){
        BmpListPosGet(_pNet->lw, &idx, NULL);
    }
    
    WORDSET_RegisterNumber(_pNet->pWordSetMain, 0,
                           _pNet->packetByte, 3,
                           NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT);
    MSGMAN_GetString( _pNet->msgman, DebugOhno_CommQuantity01,
                      _pNet->pStrBuf[1] );
    WORDSET_ExpandStr(_pNet->pWordSetMain, _pNet->pStrBuf[0], _pNet->pStrBuf[1] );
    GF_STR_PrintSimple(&_pNet->win, FONT_SYSTEM, _pNet->pStrBuf[0], 14, 1, 0, NULL);
}

//--------------------------------------------------------------
/**
 * @brief   通信量を変更するデバッグメニュー実行部分
 * @param   tcb			TCBへのポインタ
 * @param   work		ワークデータのポインタ
 * @retval  none
 */
//--------------------------------------------------------------
static void _commSendQuantityFunc(TCB_PTR tcb, void* work)
{
    _NET_INFO_WORK* pNet = work;
    u32	ret;
    int i;
    char dummyBuff[_DEBUG_QUANTITY_MAX];   // 上限

#if 0
    if(CommCommandIsThrowOuted()){
        OHNO_PRINT("コマンド捨てました\n");
    }
#endif

    
    _commSendQuantityLineCallBack();
    if(pNet->packetByte != 0){
        if( CommIsConnect( CommGetCurrentID() ) ){
            CommSendData(CS_DEBUG_VARIABLE, &dummyBuff, pNet->packetByte);
        }
    }
    if(sys.trg & PAD_KEY_LEFT){
        pNet->packetByte -= 1;
    }
    if(sys.trg & PAD_KEY_RIGHT){
        pNet->packetByte += 1;
    }
    if(sys.trg & PAD_BUTTON_L){
        pNet->packetByte -= 10;
    }
    if(sys.trg & PAD_BUTTON_R){
        pNet->packetByte += 10;
    }
    if(pNet->packetByte < 0){
        pNet->packetByte = 0;
    }
    if(pNet->packetByte > _DEBUG_QUANTITY_MAX){
        pNet->packetByte = _DEBUG_QUANTITY_MAX;
    }




    
    ret = BmpListMain(pNet->lw);
    switch(ret){
    case BMPLIST_NULL:
        break;
    case BMPLIST_CANCEL:
    default:
        CommCommandThrowOut();
        
        _roleMenuEnd(tcb, pNet);
        if(pNet->pWordSetMain){
            WORDSET_Delete(pNet->pWordSetMain);
            pNet->pWordSetMain = NULL;
        }
        for(i = 0;i < 2; i++){
            sys_FreeMemoryEz(pNet->pStrBuf[i]);
        }
		MSGMAN_Delete(pNet->msgman);
        sys_FreeMemoryEz(pNet);
        FieldSystemProc_SeqHoldEnd();
        break;
    }
}

void CommDebugRecvHugeData(int netID, int size, void* pData, void* pWork)
{
    int i;
    u8* pBuff = pData;
    
}

extern void CommSwitchAutoMove_Debug(void);

static void _commAutoMove(_NET_INFO_WORK* pNet)
{
#if 0   // 大容量通信テスト
    int i;
    u8* pbuf = sys_AllocMemory(HEAPID_FIELD, 5000);

    for(i=0;i < 5000;i++){
        pbuf[i] = i;
    }
    if(CommGetCurrentID() == COMM_PARENT_ID){
        CommSendHugeData_ServerSide(CS_DEBUG_VARIABLE, pbuf, 5000);
    }
    else{
        CommSendHugeData(CS_DEBUG_VARIABLE, pbuf, 5000);
    }
#endif
    CommSwitchAutoMove_Debug();
    FieldSystemProc_SeqHoldEnd();
}

static void _commUnder(_NET_INFO_WORK* pNet)
{
    SpScriptStart( pNet->pFSys, SCRID_DEBUG_UG_MOUNT_OFF );
    SysFlag_UgFirstSet(SaveData_GetEventWork(pNet->pFSys->savedata));
    // デバッグ用に指定の位置に下りていくのに使用
    DebugOhnoCommDebugUnderNo(0);
    Debug_ChangeUnderGroundDirect(pNet->pFSys, 169, 392);
}

static void _commUnder1(_NET_INFO_WORK* pNet)
{
    SpScriptStart( pNet->pFSys, SCRID_DEBUG_UG_MOUNT_OFF );
    SysFlag_UgFirstSet(SaveData_GetEventWork(pNet->pFSys->savedata));
    // デバッグ用に指定の位置に下りていくのに使用
    DebugOhnoCommDebugUnderNo(1);
    Debug_ChangeUnderGroundDirect(pNet->pFSys, 169, 392);
}

static void _commUnder2(_NET_INFO_WORK* pNet)
{
    DebugOhnoCommDebugDisp(pNet);
    //_commBagTrap(pNet);
    SpScriptStart( pNet->pFSys, SCRID_DEBUG_UG_MOUNT_OFF );
    SysFlag_UgFirstSet(SaveData_GetEventWork(pNet->pFSys->savedata));
    // デバッグ用に指定の位置に下りていくのに使用
    DebugOhnoCommDebugUnderNo(2);
    Debug_ChangeUnderGroundDirect(pNet->pFSys, 169, 392);
}

static void _commUnderParent(_NET_INFO_WORK* pNet)
{
    DebugOhnoCommDebugUnderParentOnly(1);
    DebugOhnoCommDebugUnderChildOnly(0);
    FieldSystemProc_SeqHoldEnd();		
}
static void _commUnderChild(_NET_INFO_WORK* pNet)
{
    DebugOhnoCommDebugUnderParentOnly(0);
    DebugOhnoCommDebugUnderChildOnly(1);
    FieldSystemProc_SeqHoldEnd();		
}

static void _commUnderNormal(_NET_INFO_WORK* pNet)
{
    DebugOhnoCommDebugUnderParentOnly(0);
    DebugOhnoCommDebugUnderChildOnly(0);
    FieldSystemProc_SeqHoldEnd();		
}


//--------------------------------------------------------------
/**
 * @brief   デバッグ用 パソコンに全てのものを入れる
 * @param   tcb			TCBへのポインタ
 * @param   work		ワークデータのポインタ
 * @retval  none
 */
//--------------------------------------------------------------
static void _commPcGoods(_NET_INFO_WORK* pNet)
{
    int i;
    SAVEDATA* pSave = GameSystem_GetSaveData(pNet->pFSys);
    UNDERGROUNDDATA* pU = SaveData_GetUnderGroundData(pSave);
    SECRETBASEDATA* pS = SaveData_GetSecretBaseData(pSave);

    for(i = GOODS_CHAIR_PC01; i < GOODS_TYPE_MAX;i++){
        UnderGroundAddGoodsPCItem(pU, i);
    }
    FieldSystemProc_SeqHoldEnd();
}

//--------------------------------------------------------------
/**
 * @brief   デバッグ用 グッズにかかるペナルティーを消す
 * @param   tcb			TCBへのポインタ
 * @param   work		ワークデータのポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static void _commGoodsPenaDel(_NET_INFO_WORK* pNet)
{
    SAVEDATA* pSave = GameSystem_GetSaveData(pNet->pFSys);

    UnderGroundDataMinUpdate(pSave, 24*60+1, FALSE); // 時間を進めて
    UnderGroundDataLoadUpdate(pSave); // フラグ更新
    FieldSystemProc_SeqHoldEnd();
}


//--------------------------------------------------------------
/**
 * @brief   デバッグ用 ワナをかばんに追加
 * @param   tcb			TCBへのポインタ
 * @param   work		ワークデータのポインタ
 * @retval  none
 */
//--------------------------------------------------------------
static void _commBagTrap(_NET_INFO_WORK* pNet)
{
    int i;
    SAVEDATA* pSave = GameSystem_GetSaveData(pNet->pFSys);
    UNDERGROUNDDATA* pU = SaveData_GetUnderGroundData(pSave);

    for(i = 0; i < 40;i++){  // すて
        UnderGroundDelTrapBagItem(pU,0);
    }
    
    UnderGroundAddTrapBagItem(pU, UG_TRAPTYPE_DRILL);
    UnderGroundAddTrapBagItem(pU, UG_TRAPTYPE_ALART1);
    UnderGroundAddTrapBagItem(pU, UG_TRAPTYPE_ALART2);
    UnderGroundAddTrapBagItem(pU, UG_TRAPTYPE_ALART3);
    UnderGroundAddTrapBagItem(pU, UG_TRAPTYPE_ALART4);
    UnderGroundAddTrapBagItem(pU, UG_TRAPTYPE_FIRE);
    UnderGroundAddTrapBagItem(pU, UG_TRAPTYPE_BLAZE);
    UnderGroundAddTrapBagItem(pU, UG_TRAPTYPE_ROCK);
    UnderGroundAddTrapBagItem(pU, UG_TRAPTYPE_ROCKFALL);
    UnderGroundAddTrapBagItem(pU, UG_TRAPTYPE_HOLE);
    UnderGroundAddTrapBagItem(pU, UG_TRAPTYPE_BIG_HOLE);
    UnderGroundAddTrapBagItem(pU, UG_TRAPTYPE_REVERSE);
    UnderGroundAddTrapBagItem(pU, UG_TRAPTYPE_SMOG);
    UnderGroundAddTrapBagItem(pU, UG_TRAPTYPE_BIG_SMOG);
    UnderGroundAddTrapBagItem(pU, UG_TRAPTYPE_SUDS);
    UnderGroundAddTrapBagItem(pU, UG_TRAPTYPE_BUBBLE);
    UnderGroundAddTrapBagItem(pU, UG_TRAPTYPE_DIRTY_BLOSSOMS);
    UnderGroundAddTrapBagItem(pU, UG_TRAPTYPE_LEAF);
    UnderGroundAddTrapBagItem(pU, UG_TRAPTYPE_GIDDY);
    UnderGroundAddTrapBagItem(pU, UG_TRAPTYPE_BIGDIR_UP);
    UnderGroundAddTrapBagItem(pU, UG_TRAPTYPE_BIGDIR_DOWN);
    UnderGroundAddTrapBagItem(pU, UG_TRAPTYPE_BIGDIR_LEFT);
    UnderGroundAddTrapBagItem(pU, UG_TRAPTYPE_BIGDIR_RIGHT);
    UnderGroundAddTrapBagItem(pU, UG_TRAPTYPE_DIR_UP);
    UnderGroundAddTrapBagItem(pU, UG_TRAPTYPE_DIR_DOWN);
    UnderGroundAddTrapBagItem(pU, UG_TRAPTYPE_DIR_LEFT);
    UnderGroundAddTrapBagItem(pU, UG_TRAPTYPE_DIR_RIGHT);

    UnderGroundAddStoneBagItem(pU, STONE_TYPE_DIAMOND, 2);
    UnderGroundAddStoneBagItem(pU, STONE_TYPE_PEARL, 3);
    UnderGroundAddStoneBagItem(pU, STONE_TYPE_RED, 4);
    UnderGroundAddStoneBagItem(pU, STONE_TYPE_BLUE, 5);
    UnderGroundAddStoneBagItem(pU, STONE_TYPE_GREEN, 6);
    UnderGroundAddStoneBagItem(pU, STONE_TYPE_DIAMOND, 2);
    UnderGroundAddStoneBagItem(pU, STONE_TYPE_PEARL, 3);
    UnderGroundAddStoneBagItem(pU, STONE_TYPE_RED, 4);
    UnderGroundAddStoneBagItem(pU, STONE_TYPE_BLUE, 5);
    UnderGroundAddStoneBagItem(pU, STONE_TYPE_GREEN, 99);
    UnderGroundAddStoneBagItem(pU, STONE_TYPE_GREEN, 96);

    UnderGroundAddTreasureBagItem(pU, DIG_PARTS_PLATE_WATER);
    UnderGroundAddTreasureBagItem(pU, DIG_PARTS_KAI);
    UnderGroundAddTreasureBagItem(pU, DIG_PARTS_GENKI_S);

    UnderGroundAddGoodsBagItem(pU,GOODS_UG_POKE_24);

    
    FieldSystemProc_SeqHoldEnd();
}

//--------------------------------------------------------------
/**
 * @brief   デバッグ用 ちかにかせきをうめる
 * @param   tcb			TCBへのポインタ
 * @param   work		ワークデータのポインタ
 * @retval  none
 */
//--------------------------------------------------------------

extern void DebugUGDigFossilAddFossil(void);
static void _commDigFossil(_NET_INFO_WORK* pNet)
{
    if(CommFieldStateIsUnder()){
        DebugUGDigFossilAddFossil();
    }
    FieldSystemProc_SeqHoldEnd();
}

static void _commPlatina(_NET_INFO_WORK* pNet)
{
    int i;

    Debug_UgFlagGet();
/*    for(i = 0;i < FLAG_PLATINA_LV_NUM+3;i++){
        SecretBaseRecordSetFlagDeliveryNum(SaveData_GetSecretBaseRecord(pNet->pFSys->savedata));
    }  */
    FieldSystemProc_SeqHoldEnd();		
}

static void _commPlatinaReturn(_NET_INFO_WORK* pNet)
{
    int i;

    for(i = 0;i < FLAG_PLATINA_LV_NUM+3;i++){
        SecretBaseRecordSetFlagDeliveryNum(SaveData_GetSecretBaseRecord(pNet->pFSys->savedata));
    }
    FieldSystemProc_SeqHoldEnd();		
}

//------------------------------------------------------------------
/**
 * WIFIMATCH呼び出しテスト
 * @param   tcb		
 * @param   work		
 * @retval  none		
 */
//------------------------------------------------------------------
static void _commWifiMatch(_NET_INFO_WORK* pNet)
{
    //P2Pマッチングボード
	EventSet_Script( pNet->pFSys, SCRID_CONNECT_WIFI_P2P_MATCH, NULL );
}


//------------------------------------------------------------------
/**
 * 友達登録
 * @param   tcb		
 * @param   work		
 * @retval  none		
 */
//------------------------------------------------------------------
static void _commWifiFriend(_NET_INFO_WORK* pNet)
{

    ZKN_HEIGHT_GRAM_PTR pZKN = PokeRegulationInit(HEAPID_FIELD);
    PokeRegulationEnd(pZKN);

    //友達登録
    EventSet_WifiAutoReg(pNet->pFSys);
}

//------------------------------------------------------------------
/**
 * 遅延発生
 * @param   tcb		
 * @param   work		
 * @retval  none		
 */
//------------------------------------------------------------------

typedef struct{
    int timer;
    int num;
} _DELAY_WORK;

static void _delayTask(TCB_PTR tcb, void* work)
{
    _DELAY_WORK* pWork = work;

    while(1){
        if(sys.trg & PAD_BUTTON_L){
            pWork->num -= 1;
        }
        if(sys.trg & PAD_BUTTON_R){
            pWork->num += 1;
        }
        pWork->timer++;
        if(pWork->timer > pWork->num){
            OS_WaitIrq(TRUE, OS_IE_V_BLANK);
//            sys_MainKeyRead();	//キー情報読み取り
        }
        else{
            pWork->timer = 0;
            break;
        }
    }
}


static void _commDelay(_NET_INFO_WORK* pNet)
{
#if 0
    _DELAY_WORK* pWork = sys_AllocMemory(HEAPID_WORLD, sizeof(_DELAY_WORK));

    pWork->timer = 0;
    pWork->num = 2;
    TCB_Add(_delayTask, pWork, TCB_PRIORITY_NORMAL);
#endif

    FUSHIGIDATA_InitSlot(pNet->pFSys->savedata, HEAPID_FIELD);
    FUSHIGIDATA_DebugSetPokemon();
    FUSHIGIDATA_FinishSlot(pNet->pFSys->savedata, TRUE);
    FieldSystemProc_SeqHoldEnd();
}

static void _stoneAdd99(_NET_INFO_WORK* pNet)
{
    int i = 0;
    MATHRandContext32 sRand;

    CommRandSeedInitialize(&sRand);
    for(i = 0; i < 99 ;){
        int x = MATH_Rand32(&sRand, 400)+64;
        int z = MATH_Rand32(&sRand, 400)+64;
        if(!GetHitAttr(pNet->pFSys,x,z)){  // あたりがある場合
            continue;
        }
        Debug_UgDigStoneAdd( STONE_TYPE_PEARL,
                              11,
                              x,z);
        i++;
    }
    FieldSystemProc_SeqHoldEnd();		
}

static void _stoneDAndP(_NET_INFO_WORK* pNet)
{
    UnderGroundSetDiamondPearlEvent(SaveData_GetUnderGroundData(pNet->pFSys->savedata));
    FieldSystemProc_SeqHoldEnd();		
}



//==============================================================================
//	ハタレベル
//==============================================================================

static const struct {
	u32  str_id;
	u32  param;
}_debugLevelMenuList[] = {
	{ DebugOhno_FlagLEVEL00, (u32)_flagChange },
	{ DebugOhno_FlagLEVEL01, (u32)_flagChange },
	{ DebugOhno_FlagLEVEL02, (u32)_flagChange },
    { DebugOhno_FlagLEVEL03, (u32)_flagChange },
    { DebugOhno_FlagLEVEL04, (u32)_flagChange },
};

//--------------------------------------------------------------
/**
 * @brief   旗のレベルを変える
 * @param   pNet		ワークデータのポインタ
 * @retval  none
 */
//--------------------------------------------------------------
static void _flagLevelChangeStart(_NET_INFO_WORK* pNetOld)
{
    _NET_INFO_WORK* pNet;

    pNet = sys_AllocMemory(HEAPID_FIELD, sizeof(_NET_INFO_WORK));
    MI_CpuFill8(pNet, 0, sizeof(_NET_INFO_WORK));
    pNet->pFSys = pNetOld->pFSys;

	pNet->menulist = BMP_MENULIST_Create( NELEMS(_debugLevelMenuList), HEAPID_FIELD );
	{
		MSGDATA_MANAGER* msgman;
		int i;

		msgman = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_debug_ohno_dat, HEAPID_FIELD);
		for(i=0; i<NELEMS(_debugLevelMenuList); i++)
		{
			BMP_MENULIST_AddArchiveString( pNet->menulist, msgman,
                                           _debugLevelMenuList[i].str_id, _debugLevelMenuList[i].param );
		}
		MSGMAN_Delete(msgman);
	}

    _listCreate(pNet,1,1,14,
                NELEMS(_debugLevelMenuList)*2,
                FLD_MENU_WIN_CGX - NELEMS(_debugLevelMenuList)*2, NELEMS(_debugLevelMenuList));
    TCB_Add(_flagLevelChangeFunc, pNet, _MENU_ROLE_PRI);
}

//--------------------------------------------------------------
/**
 * @brief    旗のレベルを変える
 * @param   tcb			TCBへのポインタ
 * @param   work		ワークデータのポインタ
 * @retval  none
 */
//--------------------------------------------------------------
static void _flagLevelChangeFunc(TCB_PTR tcb, void* work)
{
    _NET_INFO_WORK* pNet = work;
    u32	ret;

    ret = BmpListMain(pNet->lw);
    switch(ret){
    case BMPLIST_NULL:
        break;
    case BMPLIST_CANCEL:
        _roleMenuEnd(tcb, pNet);
        sys_FreeMemoryEz(pNet);
        FieldSystemProc_SeqHoldEnd();
        break;
    default:
        _roleMenuEnd(tcb, pNet);
        {
            pNetFunc func = (pNetFunc)ret;
            func(pNet);  // 関数ジャンプ
        }
        sys_FreeMemoryEz(pNet);
        break;
    }
}

static void _flagChange(_NET_INFO_WORK* pNet)
{
    u16 cur,total,i;
    SB_RECORD_DATA* pRecData = SaveData_GetSecretBaseRecord(pNet->pFSys->savedata);
    
    BmpListDirectPosGet(pNet->lw, &cur);
    FieldSystemProc_SeqHoldEnd();

    switch(cur){
      case 0:
        total = 0;
      case 1:
        total = FLAG_BRONZE_LV_NUM;
        break;
      case 2:
        total = FLAG_SILVER_LV_NUM;
        break;
      case 3:
        total = FLAG_GOLD_LV_NUM;
        break;
      case 4:
        total = FLAG_PLATINA_LV_NUM;
        break;
    }
    D_SecretBaseRecordSetFlagDeliveryNum(pRecData,total);
}


static void _underRecordMax(_NET_INFO_WORK* pNet)
{
    int i;
    SB_RECORD_DATA* pRec = SaveData_GetSecretBaseRecord(pNet->pFSys->savedata);

    TVTOPIC_Entry_Record_GetFlag(pNet->pFSys, 0xffff-1);
    TVTOPIC_Entry_Record_RemoveTrap(pNet->pFSys, UG_TRAPTYPE_DIR_RIGHT, 0xffff-1);
    SecretBaseRecordSetStoneNum(pRec, 999999-1);
    SecretBaseRecordSetFossilNum(pRec,999999-1);
    SecretBaseRecordSetTreasureNum(pRec, 999999-1);
    for(i = 0 ;i < 999999-1;i++){
        SecretBaseRecordSetTrapConquerNum(pRec);
        SecretBaseRecordSetTalkNum(pRec,0);
        SecretBaseRecordSetFlagConquerNum(pRec);
        SecretBaseRecordSetFlagDeliveryNum(pRec);
        SecretBaseRecordSetSendItemNum(pRec);
        SecretBaseRecordSetTrapTumbleNum(pRec);
        SecretBaseRecordSetTrapRescueNum(pRec);
        SecretBaseRecordSetItemRecvNum(pRec);
        SecretBaseRecordSetFlagStealNum(pRec);
        SecretBaseRecordSetFlagReverseNum(pRec);
        SecretBaseRecordSetRelocateNum(pRec);
    }
    FieldSystemProc_SeqHoldEnd();
}

static void _friendMax(_NET_INFO_WORK* pNet)
{
    int i;
    WIFI_LIST* pList = SaveData_GetWifiListData(pNet->pFSys->savedata);

    for(i = 0;i < WIFILIST_FRIEND_MAX;i++){
        WifiList_SetResult( pList, i, WIFILIST_COUNT_RANGE_MAX-1,
                            WIFILIST_COUNT_RANGE_MAX-1,WIFILIST_COUNT_RANGE_MAX-1);
    }
    FieldSystemProc_SeqHoldEnd();
}

#endif  //PM_DEBUG
