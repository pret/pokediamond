//=============================================================================
/**
 * @file	comm_direct_counter.c
 * @bfief	通信ダイレクトコーナーのカウンター
 * @author	katsumi ohno
 * @date	05/08/04
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
#include "system/snd_tool.h"

#include "savedata/zukanwork.h"
#include "savedata/perapvoice.h"
#include "ev_time.h"

//==============================================================================
// extern宣言
//==============================================================================

#include "comm_direct_counter.h"

//==============================================================================
// 定義
//==============================================================================

/// IDを文字列にした場合の長さ
#define _ID_STR_LENGTH   (5)
/// IDをバッファに入れる時に＋する値 10は多めに設定
#define _ID_STR_BUFF_LENGTH   (_ID_STR_LENGTH + 10 + EOM_SIZE)
// 木の実クラッシュ最大人数で書いてある
#define _DIRECT_CORNER_CREATURE_MAX (5)
// 表示する親機リスト
#define _DISP_SCAN_PARENT_COUNT_MAX (5)

// 親機選択のリスト横幅
#define _PARENT_MENU_LIST_WIDTH (20)
// 子機表示リストの横幅
#define _CHILD_MENU_LIST_WIDTH (17)
// 表示する子機リスト
#define _DISP_CONNECT_CHILD_COUNT_MAX (6)

#define _EVWIN_MSG_BUF_SIZE		(70 * GLOBAL_MSGLEN)			//メッセージバッファサイズ
#define _STRBUF_TEMP_ELEMENTS_NUM (8)

#define _CGX_COUNTER_TOP_NUM (1)
#define _CGX_COUNTER_PSUB_NUM  (_CGX_COUNTER_TOP_NUM + _PARENT_MENU_LIST_WIDTH * _DISP_SCAN_PARENT_COUNT_MAX * 2)
#define _CGX_COUNTER_CSUB_NUM  (_CGX_COUNTER_TOP_NUM + _CHILD_MENU_LIST_WIDTH * _DISP_CONNECT_CHILD_COUNT_MAX * 2)


enum{
    _TIMING_GUESTROOM = 10,    // そろってゲストルームに入る場合のタイミング番号

};


enum yesno_list_e {
    _YESNO_YES_RESULT = 2,
    _YESNO_NO_RESULT,
    _YESNO_DIFFER_REGULATION,
    _YESNO_ALL_EXIT,

};


typedef struct __INFO_WORK* _INFO_WORK_PTR;		// 天気制御データポインタ

typedef void (*INFO_FUNC_PTR)(_INFO_WORK_PTR pInfo);
typedef void (*STATE_FUNC_PTR)(TCB_PTR tcb, void* work);

// 状況構造体
typedef struct __INFO_WORK{
	STRBUF* pStrBuf[_STRBUF_TEMP_ELEMENTS_NUM]; // メッセージを合成して出力する場合の格納場所

    GF_BGL_BMPWIN win;		 // BMPウィンドウワーク
    GF_BGL_BMPWIN subWin;	 // BMPSubウィンドウワーク
    GF_BGL_BMPWIN talkWin;   // 会話用ウインドウワーク

    WORDSET* pWordSetMain;  //ワードセット構造体
    WORDSET* pWordSetSub;   //ワードセット構造体
    WORDSET* pWordSetTalk;  //ワードセット構造体

    BMPLIST_WORK* lw;		 // メニューワークポインタ
    BMPMENU_WORK* yesNoWork; // YesNoメニューワークポインタ
	BMPLIST_DATA*   menulist;
    FIELDSYS_WORK* pFSys;    // フィールドシステムのポインタ
    STATE_FUNC_PTR pState;    // 処理をステートで管理
    INFO_FUNC_PTR pFunc;         // YesNoメニューでYes選択した場合の動作
    MSGDATA_MANAGER* msg_man;   // メッセージマネージャー
    MYSTATUS* pMyStatus;
    MYSTATUS* pBconStatus;
    u8 bNewInfoTrg[COMM_MACHINE_MAX];
    u32 retCode;  // 外部に返すコード
    u16 curPos;              // カーソル位置
    u16 connectIndex;
    u8 connectNum;
    u8 selectGameMode;
    u8 type1;
    u8 type2;
    u8 msgIndex;          // メッセージインデックス メッセージ終了待ちに使用
    u8 selectChildNetID;  // 現在処理中の子機のID
    u8 waitMsgCount;
    u8 bSubWin;              // SubWindowを使用しているかどうか
    u8 bReWrite;
} _INFO_WORK;

typedef void (*pInfoFunc)(_INFO_WORK *);




// メニュー項目の親機名を格納しているバッファ

//============================================================================================
//	プロトタイプ宣言
//============================================================================================

// 汎用定義
static void _commonFunc(TCB_PTR tcb, void* work);
static void _changeState(STATE_FUNC_PTR pState);  // ステートを変更する
static void _talkStart(int messageIdx, BOOL bExpand);

static void _chkFunc(TCB_PTR tcb, void* work);

// コロシアムモード選択
static void _gameModeMatchWaitAndListCreate(TCB_PTR tcb, void* work);
static void _gameModeMatchFunc(TCB_PTR tcb, void* work);
static void _childStart(_INFO_WORK* pInfo);
static void _parentStart(_INFO_WORK* pInfo);

static void	_parentMenuListCursor(BMPLIST_WORK * wk,u32 param,u8 mode);
static void _parentMenuListLineCallBackAllPrint(BMPLIST_WORK * wk,u32 param,u8 y);
static void _parentMenuListLineCallBack(BMPLIST_WORK * wk,u32 param,u8 y);

// モード終了処理
static void _exit(_INFO_WORK* pInfo);
static void _chkFuncExit(TCB_PTR tcb, void* work);

// 子機が親機を選択する状態
static void _selectParentWindowOpen(_INFO_WORK* pInfo);
static void _myNameAndIDDisp(_INFO_WORK* pInfo);
static void _selectParentListWaitAndListCreate(TCB_PTR tcb, void* work);
static void _selectParentListFunc(TCB_PTR tcb, void* work);
static void _selectParentSetName(_INFO_WORK* pInfo);
static void _selectParentExec(TCB_PTR tcb, void* work);

static void _waitWindowFunc(TCB_PTR tcb, void* work);
static void _selectParentCancelYesNoCheck1(TCB_PTR tcb, void* work);
static void _selectParentCancelYesNoCheck(TCB_PTR tcb, void* work);


// 親機が子機接続を待っている状態
static void _commDisconnect(void);
static void _childListWindowOpen(_INFO_WORK* pInfo);
static void _childListStartMessage(void);
static void _numDisp(_INFO_WORK* pInfo);
static void _childListLineCallBack(BMPLIST_WORK * wk,u32 param,u8 y);

static void _waitAndChildListCreate(TCB_PTR tcb, void* work);
static void _childListSelectFunc(TCB_PTR tcb, void* work);
static void _childListSelect_YesNoWait(TCB_PTR tcb, void* work);
static void _waitAndChildListSelect2(TCB_PTR tcb, void* work);
static void _waitAndChildListSelect(TCB_PTR tcb, void* work);
static void _childListFinalCheck(TCB_PTR tcb, void* work);
static void _childListFinalCheckFunc(TCB_PTR tcb, void* work);
static void _childListFinalCheckFunc2(TCB_PTR tcb, void* work);
static void _childListBCancelCheck(TCB_PTR tcb, void* work);
static void _exitBattle(TCB_PTR tcb, void* work);
static void _exitBattleFunc(TCB_PTR tcb, void* work);
static void _childListBCancelCheckFunc(TCB_PTR tcb, void* work);
static void _childListBCancelCheckFunc1(TCB_PTR tcb, void* work);
static void _childListGuestRoomMessageWait(TCB_PTR tcb, void* work);
static void _waitAndYesNoMenuCreate(TCB_PTR tcb, void* work);
static void _regulationDiffer(TCB_PTR tcb, void* work);

static void _listEnd(TCB_PTR tcb,_INFO_WORK* pInfo);
static void _yesnoMemberCheckStart(int netID, _INFO_WORK* pInfo);
static void _startParentExec(_INFO_WORK* pInfo);

static void _startChildConnectOK(_INFO_WORK* pInfo);
static void _guestRoomOKFunc(TCB_PTR tcb, void* work);
static void _guestRoomOKFunc2(TCB_PTR tcb, void* work);
static void _guestRoomExitFunc(TCB_PTR tcb, void* work);
static void _guestRoomExitFuncEnd(TCB_PTR tcb, void* work);
static void _startChildConnectNG(_INFO_WORK* pInfo);
static void _childConnectNGFunc(TCB_PTR tcb, void* work);
static void _startChildConnectReset(_INFO_WORK* pInfo);
static void _childConnectResetFunc(TCB_PTR tcb, void* work);

// 部屋に案内するメッセージ
static void _pleaseGuestRoomStart(_INFO_WORK* pInfo);

// ゲームモードによる最大、最少人数を得る
static int _getMaxPlayNum(void);
static int _getMinPlayNum(void);
// レギュレーション値を得る
static int _getRegulationNo(void);
   

static _INFO_WORK* _pInfo = NULL;  // この関数の実体をもつポインタ

// メニューをタスクに登録していく際のプライオリティー
// 重ねるごとにあがるようにするため定義しておく
enum menuTaskPri_e {
    _TCB_PRI_TOP = 0,
    _MENU_TALK_PRI = _TCB_PRI_TOP,
    _MENU_SELECT_PARENT_PRI = 0,
    _MENU_WAIT_PRI = 0,
    _MENU_CHILD_LIST_PRI = 0,
    _PARENT_CONNECT_OK_PRI = 0
};

#define _TCB_COMMCHECK_PRT   (10)    ///< フィールドを歩く通信の監視ルーチンのPRI

// しばらくすると待機メッセージに変更する
#define _CHILD_WAIT_MSG_CHANGE_TIME (30*3)


//==============================================================================
//	YesNoメニューリスト用データ
//==============================================================================
static const BMPWIN_DAT _yesNoBmpDat = {
    FLD_MBGFRM_FONT, FLD_YESNO_WIN_PX, FLD_YESNO_WIN_PY,
    FLD_YESNO_WIN_SX, FLD_YESNO_WIN_SY, FLD_YESNO_WIN_PAL, FLD_YESNO_WIN_CGX
    };


//--------------------------------------------------------------
/**
 * @brief   通信ダイレクトコーナーのカウンター用メニュー  スタート
 * @param   pMsg 表示メッセージ
 * @retval  none
 */
//--------------------------------------------------------------

static void _talkStart(int messageIdx, BOOL bExpand)
{
    if(!FldTalkMsgEndCheck(_pInfo->msgIndex)){
        GF_STR_PrintForceStop(_pInfo->msgIndex);
    }
    if(bExpand){
        MSGMAN_GetString( _pInfo->msg_man, messageIdx, _pInfo->pStrBuf[4] );
        WORDSET_ExpandStr( _pInfo->pWordSetTalk, _pInfo->pStrBuf[5], _pInfo->pStrBuf[4] );
    }
    else{
        MSGMAN_GetString( _pInfo->msg_man, messageIdx, _pInfo->pStrBuf[5] );
    }
    if(!GF_BGL_BmpWinAddCheck(&_pInfo->talkWin)){
        FldTalkBmpAdd( _pInfo->pFSys->bgl, &_pInfo->talkWin, FLD_MBGFRM_FONT );
    }
    FieldTalkWinPut( &_pInfo->talkWin,SaveData_GetConfig(_pInfo->pFSys->savedata) );
    _pInfo->msgIndex = FieldTalkMsgStart(&_pInfo->talkWin, _pInfo->pStrBuf[5], SaveData_GetConfig(_pInfo->pFSys->savedata), 1);
}

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
static void _listCreate(BMPLIST_HEADER header,u8 x,u8 y,u8 width,u8 height,u16 chrofs)
{
    BMPLIST_HEADER list_h;
    //BMPウィンドウ生成
    if(!GF_BGL_BmpWinAddCheck(&_pInfo->win)){
        GF_BGL_BmpWinAdd(_pInfo->pFSys->bgl,&_pInfo->win,
                         GF_BGL_FRAME3_M, x, y, width, height, FLD_SYSFONT_PAL, chrofs);
    }
    BmpMenuWinWrite(&_pInfo->win, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL );
    list_h = header;
	list_h.list = _pInfo->menulist;
    list_h.win = &_pInfo->win;
    _pInfo->lw = BmpListSet(&list_h, 0, 0, HEAPID_FIELD);
    GF_BGL_BmpWinOn(&_pInfo->win);
}


//--------------------------------------------------------------
/**
 * @brief   通信ダイレクトコーナーのカウンター用メニュー  スタート
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

static void _infoInitialize(FIELDSYS_WORK* pFSys)
{
    int i;
    
    GF_ASSERT_RETURN((_pInfo==NULL) && "２重確保はおかしい",);
    _pInfo = sys_AllocMemory(HEAPID_FIELD, sizeof(_INFO_WORK));
    MI_CpuFill8(_pInfo, 0, sizeof(_INFO_WORK));

    _pInfo->retCode = COMM_RETVAL_NULL;
    _pInfo->pFSys = pFSys;
    _pInfo->bSubWin = FALSE;

	// メッセージマネージャ作成
	_pInfo->msg_man = MSGMAN_Create(
        MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_directbattlecorner_dat, HEAPID_FIELD );

    _pInfo->pMyStatus = SaveData_GetMyStatus(GameSystem_GetSaveData(_pInfo->pFSys));
    _pInfo->pBconStatus = MyStatus_AllocWork(HEAPID_FIELD);
    
    GF_BGL_BmpWinInit(&_pInfo->win);
    GF_BGL_BmpWinInit(&_pInfo->subWin);
    GF_BGL_BmpWinInit(&_pInfo->talkWin);

    _pInfo->pWordSetMain = WORDSET_Create(HEAPID_FIELD);
    _pInfo->pWordSetSub = WORDSET_Create(HEAPID_FIELD);
    _pInfo->pWordSetTalk = WORDSET_Create(HEAPID_FIELD);
    _pInfo->bReWrite = FALSE;
    for(i = 0;i < COMM_MACHINE_MAX;i++){
        _pInfo->bNewInfoTrg[i] = FALSE;
    }
    for(i = 0;i < _STRBUF_TEMP_ELEMENTS_NUM; i++){
        _pInfo->pStrBuf[i] = STRBUF_Create( _EVWIN_MSG_BUF_SIZE, HEAPID_FIELD);
    }
    
}

//--------------------------------------------------------------
/**
 * @brief   開放処理
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

static void _infoFinalize(void)
{
    int i;
    
    for(i = 0;i < _STRBUF_TEMP_ELEMENTS_NUM; i++){
        STRBUF_Delete(_pInfo->pStrBuf[i]);
    }
    sys_FreeMemoryEz(_pInfo->pBconStatus);

    if(_pInfo->pWordSetMain){
        WORDSET_Delete(_pInfo->pWordSetMain);
        _pInfo->pWordSetMain = NULL;
    }
    if(_pInfo->pWordSetSub){
        WORDSET_Delete(_pInfo->pWordSetSub);
        _pInfo->pWordSetSub = NULL;
    }
    if(_pInfo->pWordSetTalk){
        WORDSET_Delete(_pInfo->pWordSetTalk);
        _pInfo->pWordSetTalk = NULL;
    }

    MSGMAN_Delete( _pInfo->msg_man );
    if(_pInfo->talkWin.chrbuf != NULL){
        GF_BGL_BmpWinDel(&_pInfo->talkWin);
    }
    sys_FreeMemoryEz(_pInfo);
    _pInfo = NULL;
}

//--------------------------------------------------------------
/**
 * @brief   終了部分
 * @param   pInfo		ワークデータのポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static void _exit(_INFO_WORK* pInfo)
{
    _pInfo->retCode = COMM_RETVAL_CANCEL;
}

//--------------------------------------------------------------
/**
 * @brief   子機スタート
 * @param   pInfo		ワークデータのポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static void _childStart(_INFO_WORK* pInfo)
{
    CommFieldStateEnterBattleChild(pInfo->pFSys, pInfo->selectGameMode, _getRegulationNo());
}

///デバッグメニュー親機選択のリスト
static const BMPLIST_HEADER _parentMenuListHeader = {
    NULL,  // 表示文字データポインタ
    _parentMenuListCursor,// カーソル移動ごとのコールバック関数
    _parentMenuListLineCallBackAllPrint,// 一列表示ごとのコールバック関数
    NULL,                   // GF_BGL_BMPWIN* win
    SCAN_PARENT_COUNT_MAX,	// リスト項目数
    _DISP_SCAN_PARENT_COUNT_MAX,	// 表示最大項目数
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

//--------------------------------------------------------------
/**
 * @brief   カーソル移動毎のコールバック
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

static void	_parentMenuListCursor(BMPLIST_WORK * wk,u32 param,u8 mode)
{
    _pInfo->bReWrite = TRUE;
//	_parentMenuListLineCallBackAllPrint( wk, param, mode );
//
	if( mode == 0 ){	//初期化以外
		Snd_SePlay( SEQ_SE_DP_SELECT );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	全リストを描画しなおす
 *
 *	@param	wk		ワーク
 *	@param	param	文字列パラメータ（bmplistdata内部的には所々heapIDに使用している）
 *	@param	y		Ｙ位置
 */
//-----------------------------------------------------------------------------
static void _parentMenuListLineCallBackAllPrint(BMPLIST_WORK * wk,u32 param,u8 y)
{
	int i;
	for(i = 0; i < BmpListParamGet(wk,BMPLIST_ID_LINE); i++){
		_parentMenuListLineCallBack( wk, 0, i);
	}
}

//--------------------------------------------------------------
/**
 * @brief   親一覧の１ラインコールバック
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

static void _parentMenuListLineCallBack(BMPLIST_WORK * wk,u32 param,u8 y)
{
    int cntMax = CommMPGetParentCount();
    u16 idx=0;

    if(_pInfo->lw){
        BmpListPosGet(_pInfo->lw, &idx, NULL);
    }
    idx += y;
    
	GF_BGL_BmpWinFill(
		&_pInfo->win, 15, 8, y*16,
		GF_BGL_BmpWinGet_SizeX(&_pInfo->win)*8-8, 16 );

    if(idx < cntMax){
        CommMPGetParentName(idx, _pInfo->pBconStatus);
        WORDSET_RegisterNumber(_pInfo->pWordSetMain, CURRENT_PLAYER_WORD_IDX,
                               idx+1, 2,
                               NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT);
        WORDSET_RegisterPlayerName(_pInfo->pWordSetMain, TARGET_PLAYER_WORD_IDX,
                                   _pInfo->pBconStatus);
        MSGMAN_GetString( _pInfo->msg_man, DBCParentNameList, _pInfo->pStrBuf[1] );
        WORDSET_ExpandStr(_pInfo->pWordSetMain, _pInfo->pStrBuf[0], _pInfo->pStrBuf[1] );
        GF_STR_PrintSimple(&_pInfo->win, FONT_SYSTEM, _pInfo->pStrBuf[0], 8, y*16, MSG_NO_PUT, NULL);

        WORDSET_RegisterNumber(_pInfo->pWordSetMain, ASSAILANT_PLAYER_WORD_IDX,
                             MyStatus_GetID(_pInfo->pBconStatus) % 0x10000 , _ID_STR_LENGTH,
                             NUMBER_DISPTYPE_ZERO,  NUMBER_CODETYPE_DEFAULT);
        MSGMAN_GetString( _pInfo->msg_man, DBCParentIDList, _pInfo->pStrBuf[3] );
        WORDSET_ExpandStr(_pInfo->pWordSetMain, _pInfo->pStrBuf[2], _pInfo->pStrBuf[3] );
        GF_STR_PrintSimple( &_pInfo->win, FONT_SYSTEM, _pInfo->pStrBuf[2], 11*8, y*16, MSG_NO_PUT, NULL );
    }
    else{
        WORDSET_RegisterNumber(_pInfo->pWordSetMain, CURRENT_PLAYER_WORD_IDX,
                               idx+1, 2,
                               NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT);
        MSGMAN_GetString( _pInfo->msg_man, DBCParentNameList02, _pInfo->pStrBuf[1] );
        WORDSET_ExpandStr(_pInfo->pWordSetMain, _pInfo->pStrBuf[0], _pInfo->pStrBuf[1] );
        GF_STR_PrintSimple(&_pInfo->win, FONT_SYSTEM, _pInfo->pStrBuf[0], 8, y*16, MSG_NO_PUT, NULL);
    }
//    GF_BGL_BmpWinOnVReq(&_pInfo->win);
}

//--------------------------------------------------------------
/**
 * @brief   親機を選択するウインドウを開く
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

static void _selectParentWindowOpen(_INFO_WORK* pInfo)
{
    int i;

    // 自分の名前＋IDの表示
    if(!GF_BGL_BmpWinAddCheck(&_pInfo->subWin)){
        GF_BGL_BmpWinAdd(_pInfo->pFSys->bgl,&_pInfo->subWin, GF_BGL_FRAME3_M,
                         23, 2, 8, 4,
                         FLD_SYSFONT_PAL,
                         _CGX_COUNTER_PSUB_NUM);
    }
    BmpMenuWinWrite(&_pInfo->subWin, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL );
    GF_BGL_BmpWinDataFill(&_pInfo->subWin, 15 );
    GF_BGL_BmpWinOn(&_pInfo->subWin);
    pInfo->bSubWin = TRUE;

    TCB_Add(_commonFunc, pInfo, _MENU_SELECT_PARENT_PRI);
    _myNameAndIDDisp(_pInfo);

    {
        int _msgsChildSelect[]={
            DBCChildSelectTrade,
            DBCChildSelectSingle,
            DBCChildSelectDouble,
            DBCChildSelectMix,
            DBCChildSelectMulti,
            DBCChildSelectMulti,
            DBCChildSelectNut,
            DBCChildSelectRecord,
            DBCChildSelectContest,
            0,0,0,0,0,0,0,
            DBCChildSelectBattleTower,
            };

        if(_pInfo->selectGameMode == COMM_MODE_CONTEST){
            _talkStart(DBC_Contest006 + _pInfo->type1, FALSE);
        }
        else{
            _talkStart(_msgsChildSelect[_pInfo->selectGameMode], FALSE);
        }
    }
    _changeState(_selectParentListWaitAndListCreate);
}

//--------------------------------------------------------------
/**
 * @brief   名前とIDを表示する
 * @param   pInfo		ワーク構造体のポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static void _myNameAndIDDisp(_INFO_WORK* pInfo)
{

    WORDSET_RegisterPlayerName( _pInfo->pWordSetSub,CURRENT_PLAYER_WORD_IDX, _pInfo->pMyStatus);
    WORDSET_RegisterNumber(_pInfo->pWordSetSub, TARGET_PLAYER_WORD_IDX,
                           MyStatus_GetID(_pInfo->pMyStatus) % 0x10000 , _ID_STR_LENGTH,
                           NUMBER_DISPTYPE_ZERO,  NUMBER_CODETYPE_DEFAULT);

    MSGMAN_GetString( _pInfo->msg_man, DBCNameAndID, _pInfo->pStrBuf[6] );
    WORDSET_ExpandStr(_pInfo->pWordSetSub, _pInfo->pStrBuf[7], _pInfo->pStrBuf[6] );

    // 自分の名前とID表示
    GF_STR_PrintSimple( &_pInfo->subWin, FONT_SYSTEM, _pInfo->pStrBuf[7], 2, 2, 0, NULL );


}

//--------------------------------------------------------------
/**
 * @brief   親機一覧メニューの実行部分
 * @param   tcb			TCBへのポインタ
 * @param   pInfo		ワーク構造体のポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static void _selectParentListWaitAndListCreate(TCB_PTR tcb, void* work)
{
    u32	ret;
    _INFO_WORK* pInfo = (_INFO_WORK*)work;

//    _myNameAndIDDisp(pInfo);
    if(FldTalkMsgEndCheck(_pInfo->msgIndex)){
		int i;
        
        _pInfo->menulist = BMP_MENULIST_Create( SCAN_PARENT_COUNT_MAX, HEAPID_FIELD );
        for(i=0; i< SCAN_PARENT_COUNT_MAX; i++){

			// リストの数字だけ書いておく
			WORDSET_RegisterNumber(_pInfo->pWordSetMain, CURRENT_PLAYER_WORD_IDX,
								   i+1, 2,
								   NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT);
			MSGMAN_GetString( _pInfo->msg_man, DBCParentNameList02, _pInfo->pStrBuf[1] );
			WORDSET_ExpandStr(_pInfo->pWordSetMain, _pInfo->pStrBuf[0], _pInfo->pStrBuf[1] );
			
            BMP_MENULIST_AddString( _pInfo->menulist,
                                    _pInfo->pStrBuf[0], 0 );

		}

        _listCreate(_parentMenuListHeader, 1, 2,
                    _PARENT_MENU_LIST_WIDTH, _DISP_SCAN_PARENT_COUNT_MAX*2,
                    _CGX_COUNTER_TOP_NUM);
        _changeState(_selectParentListFunc);

    }
}

//--------------------------------------------------------------
/**
 * @brief   親機一覧メニューの実行部分
 * @param   tcb			TCBへのポインタ
 * @param   pInfo		ワーク構造体のポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static void _selectParentListFunc(TCB_PTR tcb, void* work)
{
    u32	ret;
    int i;
    _INFO_WORK* pInfo = (_INFO_WORK*)work;

    _myNameAndIDDisp(pInfo);

    if(CommIsError()){  // エラー時はキャンセル扱いにする
        _pInfo->retCode = COMM_RETVAL_ERROR;
        _commDisconnect();
        _listEnd(tcb, pInfo);
    }
    else{
        if(!CommMPIsScanListChange()){
            ret = BmpListMain(_pInfo->lw);
        }
        else{
            ret = BMPLIST_NULL;
        }
        switch(ret){
          case BMPLIST_NULL:
            _selectParentSetName(pInfo);
            break;
          case BMPLIST_CANCEL:
            Snd_SePlay( SEQ_SE_DP_SELECT );
            _pInfo->retCode = COMM_RETVAL_CANCEL;
            _commDisconnect();
            _listEnd(tcb, pInfo);
            break;
          default:
            Snd_SePlay( SEQ_SE_DP_SELECT );
            BmpListDirectPosGet(pInfo->lw, &pInfo->connectIndex);
            if(CommMPGetParentCount() > pInfo->connectIndex){
				//BMPListの位置からBeaconが実際に存在するIndexを取得しなおす
				pInfo->connectIndex = CommBmpListPosBconIndexGet(pInfo->connectIndex);
                
                CommFieldStateConnectBattleChild(pInfo->connectIndex);
                CommListReset();
                _changeState(_selectParentExec);
            }
            break;
        }
    }
}


//--------------------------------------------------------------
/**
 * @brief   親機の名前を拾うたびにメニューに追加する
 * @param   pNet		ネットワーク状況構造体のポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static void _selectParentSetName(_INFO_WORK* pInfo)
{
    if(CommMPIsScanListChange() || _pInfo->bReWrite){
        // 何もリストに更新がなければ描画変更をしない
        _pInfo->bReWrite = FALSE;
        CommMPResetScanChangeFlag();

//        BmpListRewrite(_pInfo->lw);
//        GF_BGL_BmpWinDataFill( &_pInfo->win, 15 );
//

		// 表示変更するところをクリア
		GF_BGL_BmpWinFill( &_pInfo->win, 15, 8, 0, _PARENT_MENU_LIST_WIDTH - 8, (_DISP_SCAN_PARENT_COUNT_MAX*2)*8 );

		// 全項目描画
		_parentMenuListLineCallBackAllPrint(_pInfo->lw, 0, 0);
//        GF_BGL_BmpWinOnVReq(&_pInfo->win);
        GF_BGL_BmpWinOn(&_pInfo->win);
    }
}

//--------------------------------------------------------------
/**
 * @brief   子機　親機に接続リクエストを出して、待機状態
 * @param   void
 * @retval  none
 */
//--------------------------------------------------------------
static void _selectParentExec(TCB_PTR tcb, void* work)
{
    _INFO_WORK* pInfo = (_INFO_WORK*)work;

    CommMPGetParentName(pInfo->connectIndex, _pInfo->pBconStatus);
    WORDSET_RegisterPlayerName( pInfo->pWordSetTalk, TARGET_PLAYER_WORD_IDX, _pInfo->pBconStatus);
    if(_getMinPlayNum() <= 2){  //1vs1 1on1の場合
        _talkStart(DBCChildWait, TRUE);
    }
    else{
        _talkStart(DBCChildWaitMulti, TRUE);
    }
    _changeState(_waitWindowFunc);

}



//--------------------------------------------------------------
/**
 * @brief   子機　親機に接続リクエストを出して、待機状態の実行部分
 * @param   tcb			TCBへのポインタ
 * @param   pNet		ネットワーク状況構造体のポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static BOOL _waitWindowCommonFunc(TCB_PTR tcb, void* work)
{
    _INFO_WORK* pInfo = work;
    
    if(CommIsError()){  // エラー時は親機選択に戻る
        _listEnd(tcb, pInfo);
        _talkStart(DBCConnectError, FALSE);
        _startChildConnectReset(pInfo);
    }
    else if( CommListGet(COMM_PARENT_ID , _YESNO_NO_RESULT) == CommGetCurrentID() ){
        CommListReset();
        _listEnd(tcb, pInfo);
        _startChildConnectNG(pInfo);
    }
    else if( CommListGet(COMM_PARENT_ID , _YESNO_ALL_EXIT) != INVALID_LIST_NO ){
        CommListReset();
        _listEnd(tcb, pInfo);
        _startChildConnectNG(pInfo);
    }
    else if( CommListGet(COMM_PARENT_ID , _YESNO_DIFFER_REGULATION) == CommGetCurrentID() ){
        // 親機からレギュレーション違反を受けた
        _talkStart(DBCDifferRule, FALSE);
        _changeState(_regulationDiffer);
    }
    else if( CommListGet(COMM_PARENT_ID , _YESNO_YES_RESULT) == CommGetCurrentID() ){
        CommListReset();
        // 親機からYESを受信
        pInfo->connectNum = CommInfoGetEntryNum();
        if(!FldTalkMsgEndCheck(_pInfo->msgIndex)){
            GF_STR_PrintForceStop(_pInfo->msgIndex);
        }
        _listEnd(tcb, pInfo);
        _startChildConnectOK(pInfo);
    }
    else if(CommRecvIsExit()){     // 全拒否された場合
        _listEnd(tcb, pInfo);
        _startChildConnectNG(pInfo);
    }
    else{
        return FALSE;
    }
    return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   子機　親機に接続リクエストを出して、待機状態の実行部分
 * @param   tcb			TCBへのポインタ
 * @param   pNet		ネットワーク状況構造体のポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static void _waitWindowFunc(TCB_PTR tcb, void* work)
{
    _INFO_WORK* pInfo = work;

    if(!FldTalkMsgEndCheck(_pInfo->msgIndex)){
        return;
    }
    if(_waitWindowCommonFunc(tcb,work)){
    }
    else if(PAD_BUTTON_CANCEL & sys.trg){  // 参加をやめるかどうか問い合わせ
        _talkStart(DBCMemberCancelCheck, FALSE);
        _changeState(_selectParentCancelYesNoCheck1);
    }
}

static void _selectParentCancelYesNoCheck1(TCB_PTR tcb, void* work)
{
    _INFO_WORK* pInfo = work;
    if(_waitWindowCommonFunc(tcb,work)){
    }
    else if(FldTalkMsgEndCheck(_pInfo->msgIndex)){
        // はいいいえウインドウを出す
        pInfo->yesNoWork = BmpYesNoSelectInit(_pInfo->pFSys->bgl,
                                               &_yesNoBmpDat, MENU_WIN_CGX_NUM,
                                               MENU_WIN_PAL, HEAPID_FIELD );
        _changeState(_selectParentCancelYesNoCheck);
    }
}

static void _selectParentCancelYesNoCheck(TCB_PTR tcb, void* work)
{
    _INFO_WORK* pInfo = work;
    u32	ret;

    if(_waitWindowCommonFunc(tcb,work)){
        BmpYesNoWinDel(pInfo->yesNoWork,HEAPID_FIELD);
        pInfo->yesNoWork = NULL;
        return;
    }
    ret = BmpYesNoSelectMain(pInfo->yesNoWork, HEAPID_FIELD);
    if(ret == 0){ // はいを選択した場合
        _listEnd(tcb, pInfo);
        _talkStart(DBCMemberCancel, FALSE);
        _startChildConnectReset(pInfo);
    }
    else if(ret != BMPMENU_NULL){ // いいえを選択した場合
 //       _talkStart(DBCChildWait, FALSE);
        _changeState(_selectParentExec);
    }

}

///デバッグメニュー親機選択のリスト
static const BMPLIST_HEADER _childListHeader = {
    NULL,  // 表示文字データポインタ
    NULL,					// カーソル移動ごとのコールバック関数
    NULL,					// 一列表示ごとのコールバック関数
    NULL,                   // win
    _DIRECT_CORNER_CREATURE_MAX,	// リスト項目数
    _DIRECT_CORNER_CREATURE_MAX,	// 表示最大項目数
    0,						// ラベル表示Ｘ座標
    1,						// 項目表示Ｘ座標
    0,						// カーソル表示Ｘ座標
    0,						// 表示Ｙ座標
    FBMP_COL_BLACK,			// 文字色
    FBMP_COL_WHITE,			// 背景色
    FBMP_COL_BLK_SDW,		// 文字影色
    0,						// 文字間隔Ｘ
    16,						// 文字間隔Ｙ
    BMPLIST_LRKEY_SKIP,		// ページスキップタイプ
    FONT_SYSTEM,				// 文字指定
    1,						// ＢＧカーソル(allow)表示フラグ(0:ON,1:OFF)
    NULL                    //work
};

//--------------------------------------------------------------
/**
 * @brief   親一覧の一ラインコールバック
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

static void _childListLineCallBack(BMPLIST_WORK * wk,u32 param,u8 y)
{
    u16 idx=0;

    if(_pInfo->lw){
        BmpListPosGet(_pInfo->lw, &idx, NULL);
    }
    idx += y;
    
    if(NULL != CommInfoGetMyStatus(idx)){
        WORDSET_RegisterPlayerName( _pInfo->pWordSetMain, CURRENT_PLAYER_WORD_IDX,
                                    CommInfoGetMyStatus(idx));
        MSGMAN_GetString( _pInfo->msg_man, DBCChildList,  _pInfo->pStrBuf[1] );
        WORDSET_ExpandStr(  _pInfo->pWordSetMain,  _pInfo->pStrBuf[0],  _pInfo->pStrBuf[1] );
        GF_STR_PrintSimple(&_pInfo->win, FONT_SYSTEM,  _pInfo->pStrBuf[0], 8, y*16, 0, NULL);
        WORDSET_RegisterNumber(_pInfo->pWordSetMain, ASSAILANT_PLAYER_WORD_IDX,
                             MyStatus_GetID_Low(CommInfoGetMyStatus(idx)), _ID_STR_LENGTH,
                             NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT);
        MSGMAN_GetString( _pInfo->msg_man, DBCParentIDList,  _pInfo->pStrBuf[3] );
        WORDSET_ExpandStr( _pInfo->pWordSetMain,  _pInfo->pStrBuf[2],  _pInfo->pStrBuf[3] );
        GF_STR_PrintSimple( &_pInfo->win, FONT_SYSTEM,  _pInfo->pStrBuf[2], 9*8, y*16, 0, NULL );
    }
}



static void _parentStart(_INFO_WORK* pInfo)
{
    CommFieldStateEnterBattleParent(pInfo->pFSys, pInfo->selectGameMode, _getRegulationNo() );
    //_childListWindowOpen(pInfo);  // 接続してくる子機リストを表示
}

//--------------------------------------------------------------
/**
 * @brief   回線切断
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------
static void _commDisconnect(void)
{
    CommFieldStateExitBattle();
}

//==============================================================================
/**
 * 管理ステートの変更
 * @param   state  変えるステートの関数
 * @param   time   ステート保持時間
 * @retval  none
 */
//==============================================================================

static void _changeState(STATE_FUNC_PTR pState)
{
    _pInfo->pState = pState;
}

//--------------------------------------------------------------
/**
 * @brief   接続する子機一覧ウインドウを開く
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

static void _childListWindowOpen(_INFO_WORK* pInfo)
{
    int i;

    TCB_Add(_commonFunc, pInfo, _MENU_CHILD_LIST_PRI);
    _childListStartMessage();
    
    // あと？にんの表示
    if(!GF_BGL_BmpWinAddCheck(&_pInfo->subWin)){
        GF_BGL_BmpWinAdd(_pInfo->pFSys->bgl,&_pInfo->subWin, GF_BGL_FRAME3_M,
                         22, 2, 9, 4,
                         FLD_SYSFONT_PAL,
                         _CGX_COUNTER_CSUB_NUM);
    }
    BmpMenuWinWrite(&_pInfo->subWin, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM,
                    MENU_WIN_PAL );
    GF_BGL_BmpWinDataFill(&_pInfo->subWin, 15 );
    GF_BGL_BmpWinOn(&_pInfo->subWin);
    pInfo->bSubWin = TRUE;

    // 自分のデータを送信
    //CommInfoSendPokeData();
    CommInfoSetEntry(0);// 自分はすでに受付完了

    _changeState(_waitAndChildListCreate);

}

static void _childListStartMessage(void)
{
    int _msgsParentWait[]={
        DBCParentWaitTrade,
        DBCParentWaitSingle,
        DBCParentWaitDouble,
        DBCParentWaitMix,
        DBCParentWaitMulti,
        DBCParentWaitMulti,
        DBCParentWaitNut,
        DBCParentWaitRecord,
        DBCParentWaitContest,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        DBCParentWaitBattleTower,
        };
    GF_ASSERT(_pInfo->selectGameMode < (sizeof(_msgsParentWait)/sizeof(int)));

    if(_pInfo->selectGameMode == COMM_MODE_CONTEST){
        if(CommInfoGetEntryNum() > 1){
            _talkStart(DBC_Contest011 + _pInfo->type1, FALSE);
        }
        else{
            _talkStart(DBC_Contest001 + _pInfo->type1, FALSE);
        }
    }
    else{
        _talkStart(_msgsParentWait[_pInfo->selectGameMode], FALSE);
    }
}


//--------------------------------------------------------------
/**
 * @brief   人数の表示
 * @param   pInfo		ワーク構造体のポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static void _numDisp(_INFO_WORK* pInfo)
{
    int msgno,num;

    // 人数表示
    if(CommInfoGetEntryNum() >= _getMinPlayNum()){
        num = CommInfoGetEntryNum();
        msgno = DBCChildPlayNum;
    }
    else{
        num = _getMinPlayNum() - CommInfoGetEntryNum();
        msgno = DBCChildRestNum;
    }
    WORDSET_RegisterNumber( _pInfo->pWordSetSub,
                            CURRENT_PLAYER_WORD_IDX,
                            num,
                            NUM_MODE_ZERO, _ID_STR_LENGTH,
                            NUMBER_CODETYPE_DEFAULT);
    GF_BGL_BmpWinDataFill(&_pInfo->subWin, 15 );
    MSGMAN_GetString( _pInfo->msg_man, msgno,  _pInfo->pStrBuf[7]);
    WORDSET_ExpandStr( _pInfo->pWordSetSub,  _pInfo->pStrBuf[6],  _pInfo->pStrBuf[7] );
    GF_STR_PrintSimple( &_pInfo->subWin, FONT_SYSTEM,
                         _pInfo->pStrBuf[6], 2, 2, 0, NULL );
}


static void _yesnoMemberCheckStart(int netID, _INFO_WORK* pInfo)
{
    // ゲームモードにあわせたセリフ一覧
    int _msgsParentCheck[]={
        DBCParentCheckTrade,
        DBCParentCheckSingle,
        DBCParentCheckDouble,
        DBCParentCheckMix,
        DBCParentCheckMember,
        DBCParentCheckMember,
        DBCParentCheckPoro,
        DBCParentCheckMember,
        DBCParentCheckMember,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        DBCParentChecBT,
    };
    MYSTATUS* pMy = CommInfoGetMyStatus(netID);

    if(pMy){
        WORDSET_RegisterPlayerName( pInfo->pWordSetTalk, TARGET_PLAYER_WORD_IDX, pMy);
    }
    _talkStart(_msgsParentCheck[pInfo->selectGameMode], TRUE);
}

//--------------------------------------------------------------
/**
 * @brief   親機一覧メニューの実行部分
 * @param   tcb			TCBへのポインタ
 * @param   pInfo		ワーク構造体のポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static void _commonFunc(TCB_PTR tcb, void* work)
{
    _INFO_WORK* pInfo = (_INFO_WORK*)work;

    if(_pInfo->pState != NULL){
        STATE_FUNC_PTR state = _pInfo->pState;
        state(tcb, pInfo);
    }

}

//--------------------------------------------------------------
/**
 * @brief   メッセージが出たら、子機リストを出す
 * @param   tcb			TCBへのポインタ
 * @param   pInfo		ワーク構造体のポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static void _waitAndChildListCreate(TCB_PTR tcb, void* work)
{
    _INFO_WORK* pInfo = (_INFO_WORK*)work;
    u32	ret = BMPLIST_NULL;

    _numDisp(pInfo);

    if(FldTalkMsgEndCheck(_pInfo->msgIndex)){
		int i;
        
        _pInfo->menulist = BMP_MENULIST_Create( _DISP_SCAN_PARENT_COUNT_MAX, HEAPID_FIELD );
        for(i=0; i< _DISP_SCAN_PARENT_COUNT_MAX; i++){
            BMP_MENULIST_AddArchiveString( _pInfo->menulist, _pInfo->msg_man,
                                    DBCParentNoList, 0 );
		}
        _pInfo->bReWrite = TRUE;
        for(i = 0;i < COMM_MACHINE_MAX;i++){
            _pInfo->bNewInfoTrg[i] = FALSE;
        }
        _listCreate(_childListHeader, 1, 2,
                    _CHILD_MENU_LIST_WIDTH, _DISP_CONNECT_CHILD_COUNT_MAX*2,
                    _CGX_COUNTER_TOP_NUM);
        _changeState(_childListSelectFunc);
    }
}

//--------------------------------------------------------------
/**
 * @brief   子機リストを表示している
 * @param   tcb			TCBへのポインタ
 * @param   pInfo		ワーク構造体のポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static void _childListSelectFunc(TCB_PTR tcb, void* work)
{
    _INFO_WORK* pInfo = (_INFO_WORK*)work;
    u32	ret = BMPLIST_NULL;
    int i;

    _numDisp(pInfo);

    for(i = 0;i < COMM_MACHINE_MAX;i++){  // mustatus検査
        if(CommInfoIsBattleNewName(i) && (i != 0 )){
            _pInfo->bNewInfoTrg[i] = TRUE;
            _pInfo->bReWrite = TRUE;
        }
        else if((NULL != CommInfoGetMyStatus(i)) && !_pInfo->bNewInfoTrg[i]){
            _pInfo->bNewInfoTrg[i] = TRUE;
            _pInfo->bReWrite = TRUE;
        }
        else if((NULL == CommInfoGetMyStatus(i)) && _pInfo->bNewInfoTrg[i]){
            _pInfo->bNewInfoTrg[i] = FALSE;
            _pInfo->bReWrite = TRUE;
        }
    }

    if(_pInfo->bReWrite){
        _pInfo->bReWrite = FALSE;
        BmpListRewrite(_pInfo->lw); // ウインドウ再描画
        for(i = 0; i < BmpListParamGet(_pInfo->lw,BMPLIST_ID_LINE); i++){
            _childListLineCallBack(_pInfo->lw, 0, i);
        }
    }
    
    ret = BmpListMain(pInfo->lw);
    if(CommInfoGetNewNameID() != INVALID_NETID){
        pInfo->selectChildNetID = CommInfoGetNewNameID();
        Snd_SePlay(SEQ_SE_DP_PC_LOGIN);
        _yesnoMemberCheckStart(pInfo->selectChildNetID, pInfo);
        _changeState(_waitAndYesNoMenuCreate);
        return;
    }
    if(CommIsError()){  // エラー時はキャンセル扱いにする
        // 回線切断
        _commDisconnect();
        _listEnd(tcb, pInfo);
        _pInfo->retCode = COMM_RETVAL_ERROR;
    }
    else{
        switch(ret){
          case BMPLIST_NULL:
            break;
          case BMPLIST_CANCEL:  // 戻る
            _changeState(_childListBCancelCheck);
            break;
          default:   // 最低人数に達していたら開始の確認
            if(_getMinPlayNum() <= CommInfoGetEntryNum()){  // 最低接続人数に達した
                int _msgsParentFinalCheck[]={
                    0,
                    0,
                    0,
                    DBCFinalCheckMulti,
                    DBCFinalCheckMulti,
                    DBCFinalCheckMulti,
                    DBCFinalCheckNut,
                    DBCFinalCheckRecord,
                    DBCFinalCheckContest,
                    0,
                    0,
                    0,
                    0,
                    0,
                    0,
                    0,
                    0,
                };
                pInfo->connectNum = CommInfoGetEntryNum();
                _talkStart(_msgsParentFinalCheck[pInfo->selectGameMode], FALSE);
                _changeState(_childListFinalCheckFunc);
            }
            break;
        }
    }
}


//--------------------------------------------------------------
/**
 * @brief   はい、いいえウインドウを出し分岐する
 * @param   tcb			TCBへのポインタ
 * @param   pInfo		ワーク構造体のポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static void _childListSelect_YesNoWait(TCB_PTR tcb, void* work)
{
    _INFO_WORK* pInfo = (_INFO_WORK*)work;
    u32	ret = BMPLIST_NULL;
    int i;

    _numDisp(pInfo);
    
    BmpListMain(pInfo->lw);
    ret = BmpYesNoSelectMain(pInfo->yesNoWork, HEAPID_FIELD);
    if(!CommIsConnect(pInfo->selectChildNetID)){   //参加中止
        if(ret == BMPMENU_NULL){
            BmpYesNoWinDel(pInfo->yesNoWork, HEAPID_FIELD);
        }
        if(pInfo->selectGameMode == COMM_MODE_CONTEST){  // コンテストに穴抜けは無い
            for(i = 1 ; i < _getMaxPlayNum() ; i++){
                if(CommIsConnect(i)){
                    CommInfoDeletePlayer( i ); // 登録を消す
                    CommListSet(_YESNO_ALL_EXIT, i);
                }
            }
            _talkStart(DBCConnectError, FALSE);
            _changeState(_waitAndChildListSelect2);
        }
        else{
            CommInfoDeletePlayer( pInfo->selectChildNetID ); // 登録を消す
            _talkStart(DBCConnectError, FALSE);
            _changeState(_waitAndChildListSelect2);
        }
    }
    else if(CommIsError() ||   // エラー時はキャンセル扱いにする
       CommRecvIsExit()){   // 子機側が拒否してきた
        if(ret == BMPMENU_NULL){
            BmpYesNoWinDel(pInfo->yesNoWork, HEAPID_FIELD);
        }
        CommInfoDeletePlayer( pInfo->selectChildNetID ); // 登録を消す
        _talkStart(DBCConnectError, FALSE);
        _changeState(_waitAndChildListSelect2);
    }
    else if(ret == 0){ // はいを選択した場合

        if((pInfo->selectGameMode == COMM_MODE_BATTLE_SINGLE) ||
           (pInfo->selectGameMode == COMM_MODE_BATTLE_DOUBLE)){
            if(!CommInfoRegulationCheck()){  // 通信したレギュレーションが異なる レギュレーションない場合はからっぽのはず
                _talkStart(DBCDifferRule, FALSE);
                _changeState(_regulationDiffer);
                CommListSet(_YESNO_DIFFER_REGULATION, pInfo->selectChildNetID);
                return;
            }
        }
        CommInfoSetEntry( pInfo->selectChildNetID );  //エントリーする
        CommListSet(_YESNO_YES_RESULT, pInfo->selectChildNetID);
        if(_getMaxPlayNum() == CommInfoGetEntryNum()){  // 接続人数に達した
            pInfo->connectNum = CommInfoGetEntryNum();
            if(_getMaxPlayNum() > 2){ // 二人以上のときは再確認モードへ
                _changeState(_childListFinalCheck);
            }
            else{
                _listEnd(tcb,pInfo);   // そのままご案内
                _startParentExec(pInfo);
            }
        }
        else{
            _childListStartMessage();
            _changeState(_waitAndChildListSelect);
        }
    }
    else if(ret != BMPMENU_NULL){ // いいえを選択した場合
        if(pInfo->selectGameMode == COMM_MODE_CONTEST){  // コンテストに穴抜けは無い
            for(i = 1 ; i < _getMaxPlayNum() ; i++){
                if(CommIsConnect(i)){
                    CommInfoDeletePlayer( i ); // 登録を消す
                    CommListSet(_YESNO_ALL_EXIT, i);
                }
            }
            _childListStartMessage();
            _changeState(_waitAndChildListSelect);
        }
        else{
            CommInfoDeletePlayer( pInfo->selectChildNetID ); // 登録を消す
            CommListSet(_YESNO_NO_RESULT, pInfo->selectChildNetID);
            _childListStartMessage();
            _changeState(_waitAndChildListSelect);
        }
    }
}

//--------------------------------------------------------------
/**
 * @brief   レギュレーションが異なる
 * @param   tcb			TCBへのポインタ
 * @param   pInfo		ワーク構造体のポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static void _regulationDiffer(TCB_PTR tcb, void* work)
{
    _INFO_WORK* pInfo = (_INFO_WORK*)work;

    if(FldTalkMsgEndCheck(_pInfo->msgIndex)){
        if(sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL)){
            _listEnd(tcb,pInfo);
            _commDisconnect();
            _pInfo->retCode = COMM_RETVAL_DIFFER_REGULATION;
        }
    }
}

//--------------------------------------------------------------
/**
 * @brief   メッセージが出たら、待機状態へいく。 リストは出たまま
 * @param   tcb			TCBへのポインタ
 * @param   pInfo		ワーク構造体のポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static void _waitAndChildListSelect2(TCB_PTR tcb, void* work)
{
    _INFO_WORK* pInfo = (_INFO_WORK*)work;
    u32	ret = BMPLIST_NULL;

    _numDisp(pInfo);
    if(FldTalkMsgEndCheck(_pInfo->msgIndex)){
        if(sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL)){
            _childListStartMessage();
            _changeState(_waitAndChildListSelect);
        }
    }

}


//--------------------------------------------------------------
/**
 * @brief   メッセージが出たら、待機状態へいく。 リストは出たまま
 * @param   tcb			TCBへのポインタ
 * @param   pInfo		ワーク構造体のポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static void _waitAndChildListSelect(TCB_PTR tcb, void* work)
{
    _INFO_WORK* pInfo = (_INFO_WORK*)work;
    u32	ret = BMPLIST_NULL;

    _numDisp(pInfo);
    if(FldTalkMsgEndCheck(_pInfo->msgIndex)){
        _changeState(_childListSelectFunc);
    }

}

//--------------------------------------------------------------
/**
 * @brief   ゲームを開始していいかどうかのはいいいえウインドウ
 * @param   tcb			TCBへのポインタ
 * @param   pInfo		ワーク構造体のポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static void _childListFinalCheck(TCB_PTR tcb, void* work)
{
    _INFO_WORK* pInfo = (_INFO_WORK*)work;
    u32	ret = BMPLIST_NULL;
    int _msgsParentFinalCheck[]={
        0,
        0,
        0,
        DBCFinalCheckMulti,
        DBCFinalCheckMulti,
        DBCFinalCheckMulti,
        DBCFinalCheckNut,
        DBCFinalCheckRecord,
        DBCFinalCheckContest,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
    };

    _numDisp(pInfo);

    _talkStart(_msgsParentFinalCheck[pInfo->selectGameMode], FALSE);
    _changeState(_childListFinalCheckFunc);
}

//--------------------------------------------------------------
/**
 * @brief   ゲームを開始していいかどうかのはいいいえウインドウ待機
 * @param   tcb			TCBへのポインタ
 * @param   pInfo		ワーク構造体のポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static void _childListFinalCheckFunc(TCB_PTR tcb, void* work)
{
    _INFO_WORK* pInfo = (_INFO_WORK*)work;
    u32	ret = BMPLIST_NULL;

    _numDisp(pInfo);
    CommStateSetEntryChildEnable(FALSE);

    BmpListMain(pInfo->lw);

    if(FldTalkMsgEndCheck(_pInfo->msgIndex)){
        pInfo->yesNoWork = BmpYesNoSelectInit(_pInfo->pFSys->bgl,
                                               &_yesNoBmpDat,
                                               MENU_WIN_CGX_NUM, MENU_WIN_PAL, HEAPID_FIELD );
        _changeState(_childListFinalCheckFunc2);
    }
}


static void _childListFinalCheckFunc2(TCB_PTR tcb, void* work)
{
    _INFO_WORK* pInfo = (_INFO_WORK*)work;
    u32	ret = BMPLIST_NULL;
    int i;

    _numDisp(pInfo);

    BmpListMain(pInfo->lw);
    ret = BmpYesNoSelectMain(pInfo->yesNoWork, HEAPID_FIELD);
    if(CommIsError() || (CommGetConnectNum() != pInfo->connectNum)){  // エラー時はキャンセル扱いにする
        if(ret == BMPMENU_NULL){
            BmpYesNoWinDel(pInfo->yesNoWork,HEAPID_FIELD);
        }
        pInfo->yesNoWork = NULL;
        _changeState(_exitBattle);
    }
    else if(ret == 0){ // はいを選択した場合
        if(pInfo->selectGameMode == COMM_MODE_CONTEST){  // コンテストに穴抜けは無い
            for(i = 1 ; i < CommGetConnectNum() ; i++){
                if(!CommIsConnect(i)){
                    _changeState(_exitBattle);
                    //穴が抜けている
//                    CommStateSetEntryChildEnable(TRUE);
  //                  _commDisconnect();
    //                _listEnd(tcb, pInfo);
      //              _pInfo->retCode = COMM_RETVAL_CANCEL;
                    return;
                }
            }
        }
        CommTimingSyncStart(_TIMING_GUESTROOM); // ゲストルームに行く送信
        _changeState(_childListGuestRoomMessageWait);
    }
    else if(ret != BMPMENU_NULL){ // いいえを選択した場合
        CommStateSetEntryChildEnable(TRUE);
        _commDisconnect();
        _listEnd(tcb, pInfo);
        _pInfo->retCode = COMM_RETVAL_CANCEL;
    }
}

static void _exitBattle(TCB_PTR tcb, void* work)
{
    _INFO_WORK* pInfo = (_INFO_WORK*)work;
    int msgFinalNOs[]={
        0,
        0,
        0,
        0,
        0,
        0,
        DBCNutFinalNo,
        DBCRecordFinalNo,
        DBCContestFinalNo,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        };


    _listEnd(tcb,pInfo);

    if(_pInfo->selectGameMode == COMM_MODE_CONTEST){
        _talkStart(DBC_Contest021 + _pInfo->type1, FALSE);
    }
    else{
        _talkStart(msgFinalNOs[ pInfo->selectGameMode ], FALSE);
    }
    CommFieldStateExitBattle();
    TCB_Add(_exitBattleFunc, pInfo, _PARENT_CONNECT_OK_PRI);
}

static void _exitBattleFunc(TCB_PTR tcb, void* work)
{
    if(FldTalkMsgEndCheck(_pInfo->msgIndex)){
        if(sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL)){
            _pInfo->retCode = COMM_RETVAL_CANCEL;
            TCB_Delete(tcb);
        }
    }
}


//--------------------------------------------------------------
/**
 * @brief   Bキャンセルで抜ける時のはいいいえウインドウだし
 * @param   tcb			TCBへのポインタ
 * @param   pInfo		ワーク構造体のポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static void _childListBCancelCheck(TCB_PTR tcb, void* work)
{
    _INFO_WORK* pInfo = (_INFO_WORK*)work;
    u32	ret = BMPLIST_NULL;
    int _msgsParentBCancel[]={
        0,
        0,
        0,
        DBCBCancelMulti,
        DBCBCancelMulti,
        DBCBCancelMulti,
        DBCBCancelNut,
        DBCBCancelRecord,
        DBCBCancelContest,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
    };

    _numDisp(pInfo);

    if(CommInfoGetEntryNum() > 1){
        // 子機がいる場合 戻る前に確認
        _talkStart(_msgsParentBCancel[pInfo->selectGameMode], FALSE);
        _changeState(_childListBCancelCheckFunc1);
    }
    else{   //誰も登録がない場合もどる
        _commDisconnect();
        _listEnd(tcb, pInfo);
        _pInfo->retCode = COMM_RETVAL_CANCEL;
    }
}

static void _childListBCancelCheckFunc1(TCB_PTR tcb, void* work)
{
    _INFO_WORK* pInfo = (_INFO_WORK*)work;

    _numDisp(pInfo);
    BmpListMain(pInfo->lw);
    if(FldTalkMsgEndCheck(_pInfo->msgIndex)){
        pInfo->yesNoWork = BmpYesNoSelectInit(_pInfo->pFSys->bgl,
                                               &_yesNoBmpDat,
                                               MENU_WIN_CGX_NUM, MENU_WIN_PAL, HEAPID_FIELD );

        _changeState(_childListBCancelCheckFunc);
    }
}

//--------------------------------------------------------------
/**
 * @brief   Bキャンセルで抜ける時のはいいいえウインドウ待ち
 * @param   tcb			TCBへのポインタ
 * @param   pInfo		ワーク構造体のポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static void _childListBCancelCheckFunc(TCB_PTR tcb, void* work)
{
    _INFO_WORK* pInfo = (_INFO_WORK*)work;
    u32	ret = BMPLIST_NULL;

    _numDisp(pInfo);

    BmpListMain(pInfo->lw);
    ret = BmpYesNoSelectMain(pInfo->yesNoWork, HEAPID_FIELD);
    if(CommIsError()){  // エラー時はキャンセル扱いにする
        ret = BMPLIST_CANCEL;
    }
    if(ret == 0){ // はいを選択した場合
        _commDisconnect();
        _listEnd(tcb, pInfo);
        _pInfo->retCode = COMM_RETVAL_CANCEL;
    }
    else if(ret != BMPMENU_NULL){ // いいえを選択した場合
        _childListStartMessage();
        _changeState(_waitAndChildListSelect);
    }
}

//--------------------------------------------------------------
/**
 * @brief   登録完了、全員の通信開始を待つ
 * @param   tcb			TCBへのポインタ
 * @param   pInfo		ワーク構造体のポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static void _childListGuestRoomMessageWait(TCB_PTR tcb, void* work)
{
    _INFO_WORK* pInfo = (_INFO_WORK*)work;
    u32	ret = BMPLIST_NULL;

    if(CommIsError() || (CommGetConnectNum() != pInfo->connectNum)){  // エラー時はキャンセル扱いにする
        _changeState(_exitBattle);
    }
    else{
        _numDisp(pInfo);
        BmpListMain(pInfo->lw);
        if(CommIsTimingSync(_TIMING_GUESTROOM)){ // 受信した場合
            if(CommToolIsInitialize()){  // 通信してるなら
                _listEnd(tcb, pInfo);
                _pleaseGuestRoomStart(pInfo);
            }
        }
    }
}

//--------------------------------------------------------------
/**
 * @brief   メッセージ待機後はいいいえウインドウを出す
 * @param   tcb			TCBへのポインタ
 * @param   pInfo		ワーク構造体のポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static void _waitAndYesNoMenuCreate(TCB_PTR tcb, void* work)
{
    _INFO_WORK* pInfo = (_INFO_WORK*)work;
    u32	ret = BMPLIST_NULL;

    _numDisp(pInfo);

    BmpListMain(pInfo->lw);
    if(FldTalkMsgEndCheck(_pInfo->msgIndex)){
        pInfo->yesNoWork = BmpYesNoSelectInit(_pInfo->pFSys->bgl,
                                               &_yesNoBmpDat,
                                               MENU_WIN_CGX_NUM, MENU_WIN_PAL, HEAPID_FIELD );
        _changeState(_childListSelect_YesNoWait);
    }
}


//--------------------------------------------------------------
/**
 * @brief   子機リストを閉じる
 * @param   tcb			TCBへのポインタ
 * @param   pInfo		ワーク構造体のポインタ
 * @retval  none
 */
//--------------------------------------------------------------
static void _listEnd(TCB_PTR tcb,_INFO_WORK* pInfo)
{
    GF_BGL_BmpWinDataFill( &_pInfo->talkWin, 15 );
    BmpMenuWinClear(&pInfo->win, WINDOW_TRANS_ON );
    BMP_MENULIST_Delete( pInfo->menulist );
    BmpListExit(pInfo->lw, NULL, NULL);
    GF_BGL_BmpWinOff(&pInfo->win);
    GF_BGL_BmpWinDel(&pInfo->win);

    if(pInfo->bSubWin){
        BmpMenuWinClear(&_pInfo->subWin, WINDOW_TRANS_ON );
        GF_BGL_BmpWinOff(&_pInfo->subWin);
        GF_BGL_BmpWinDel(&_pInfo->subWin);
        pInfo->bSubWin = FALSE;
    }
    if(tcb){
        TCB_Delete(tcb);
    }
}

//--------------------------------------------------------------
/**
 * @brief   選んだ親機に接続しにいく
 * @param   pInfo		ワーク構造体のポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static void _startParentExec(_INFO_WORK* pInfo)
{
    WORDSET_RegisterPlayerName( pInfo->pWordSetTalk, TARGET_PLAYER_WORD_IDX, CommInfoGetMyStatus(1));
    _talkStart(DBCChildSelectOk, TRUE);

    TCB_Add(_commonFunc, pInfo, _PARENT_CONNECT_OK_PRI);
    _changeState(_guestRoomOKFunc);
}

//--------------------------------------------------------------
/**
 * @brief   選んだ親機に接続しにいく
 * @param   pInfo		ワーク構造体のポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static void _startChildConnectOK(_INFO_WORK* pInfo)
{
    CommMPGetParentName(pInfo->connectIndex, _pInfo->pBconStatus);
    WORDSET_RegisterPlayerName( pInfo->pWordSetTalk, TARGET_PLAYER_WORD_IDX, _pInfo->pBconStatus);
    _talkStart(DBCChildConnectOK, TRUE);
    pInfo->connectNum = CommGetConnectNum();

    TCB_Add(_commonFunc, pInfo, _PARENT_CONNECT_OK_PRI);
    _changeState(_guestRoomOKFunc);
    _pInfo->waitMsgCount = _CHILD_WAIT_MSG_CHANGE_TIME;
}




//--------------------------------------------------------------
/**
 * @brief   全員のコマンド受信を待って案内される
 * @param   pInfo		ワーク構造体のポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static void _guestRoomOKFunc(TCB_PTR tcb, void* work)
{
    _INFO_WORK* pInfo = (_INFO_WORK*)work;

    if((CommGetCurrentID() == COMM_PARENT_ID) && (CommGetConnectNum() != pInfo->connectNum) ){
        _changeState(_guestRoomExitFunc);
    }
    else if(CommRecvIsExit() || CommIsError()){  // 解散命令
        _changeState(_guestRoomExitFunc);
    }
    else if(FldTalkMsgEndCheck(_pInfo->msgIndex)){
        CommTimingSyncStart(_TIMING_GUESTROOM); // ゲストルームに行く送信
        _changeState(_guestRoomOKFunc2);
    }
}



//--------------------------------------------------------------
/**
 * @brief   全員のコマンド受信を待って案内される
 * @param   pInfo		ワーク構造体のポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static void _guestRoomOKFunc2(TCB_PTR tcb, void* work)
{
    _INFO_WORK* pInfo = (_INFO_WORK*)work;

    if((CommGetCurrentID() == COMM_PARENT_ID) && (CommGetConnectNum() != pInfo->connectNum) ){
        _changeState(_guestRoomExitFunc);
    }
    else if(CommRecvIsExit() || CommIsError()){  // 解散命令
        _changeState(_guestRoomExitFunc);
        return;
    }
    else if(!CommIsConnect(COMM_PARENT_ID)){  // エラー時はキャンセル扱いにする
       _changeState(_guestRoomExitFunc);
        return;
    }
    else if( CommListGet(COMM_PARENT_ID , _YESNO_ALL_EXIT) != INVALID_LIST_NO ){
        _changeState(_guestRoomExitFunc);
        return;
    }
    else if(CommIsTimingSync(_TIMING_GUESTROOM)){ // 受信した場合
        if(CommToolIsInitialize()){  // 通信してるなら
            if(!FldTalkMsgEndCheck(_pInfo->msgIndex)){
                GF_STR_PrintForceStop(_pInfo->msgIndex);
            }
            pInfo->connectNum = CommGetConnectNum(); // 人数決
            _pleaseGuestRoomStart(pInfo);
            TCB_Delete(tcb);
            return;
        }
    }
        // ある程度時間が過ぎたらメッセージ変更
    if(_pInfo->waitMsgCount!=0){
        _pInfo->waitMsgCount--;
        if(_pInfo->waitMsgCount==0){
            int _msgsChildOtherWait[]={
                NULL,
                NULL,
                NULL,
                DBCChildOtherWaitMulti,
                DBCChildOtherWaitMulti,
                DBCChildOtherWaitMulti,
                DBCChildOtherWaitNut,
                DBCChildOtherWaitRecord,
                DBCChildOtherWaitContest,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            };
            if(_pInfo->selectGameMode == COMM_MODE_CONTEST){
                _talkStart(DBC_Contest016 + _pInfo->type1, FALSE);
            }
            else{
                _talkStart(_msgsChildOtherWait[pInfo->selectGameMode], FALSE);
            }
        }
    }
}



//--------------------------------------------------------------
/**
 * @brief   ゲスト準備状態だったが元に戻ることになった
 * @param   pInfo		ワーク構造体のポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static void _guestRoomExitFunc(TCB_PTR tcb, void* work)
{
    _INFO_WORK* pInfo = (_INFO_WORK*)work;

    if(FldTalkMsgEndCheck(_pInfo->msgIndex)){
        _talkStart(DBCConnectError, FALSE);
        _changeState(_guestRoomExitFuncEnd);
    }
}

static void _guestRoomExitFuncEnd(TCB_PTR tcb, void* work)
{
    _INFO_WORK* pInfo = (_INFO_WORK*)work;

    if(FldTalkMsgEndCheck(_pInfo->msgIndex)){
        if(sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL)){
            TCB_Delete(tcb);
            _commDisconnect();
            _pInfo->retCode = COMM_RETVAL_CANCEL;
        }
    }
}

//--------------------------------------------------------------
/**
 * @brief   NGが帰ってきたので親を選びなおす
 * @param   pInfo		ワーク構造体のポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static void _startChildConnectNG(_INFO_WORK* pInfo)
{
    CommMPGetParentName(pInfo->connectIndex, _pInfo->pBconStatus);
    WORDSET_RegisterPlayerName( pInfo->pWordSetTalk, TARGET_PLAYER_WORD_IDX, _pInfo->pBconStatus);
    _talkStart(DBCChildConnectNG, TRUE);
    CommFieldStateRebootBattleChild();
    TCB_Add(_childConnectNGFunc, pInfo, _PARENT_CONNECT_OK_PRI);
//    CommSendData(CS_EXIT, NULL, 0); // 全体コマンド発信いらないはず 2005.8.31
}

//--------------------------------------------------------------
/**
 * @brief   NGが帰ってきたので親を選びなおす処理へ移動
 * @param   pInfo		ワーク構造体のポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static void _childConnectNGFunc(TCB_PTR tcb, void* work)
{
    _INFO_WORK* pInfo = (_INFO_WORK*)work;

    if(FldTalkMsgEndCheck(_pInfo->msgIndex)){
//        if(sys.trg & (PAD_BUTTON_CANCEL|PAD_BUTTON_DECIDE)){
            CommFieldStateRebootBattleChild();
            _selectParentWindowOpen(pInfo);
            TCB_Delete(tcb);
//        }
    }
}


//--------------------------------------------------------------
/**
 * @brief   エラー、再起動になったので親を選びなおす
 * @param   pInfo		ワーク構造体のポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static void _startChildConnectReset(_INFO_WORK* pInfo)
{
    CommFieldStateRebootBattleChild();
    TCB_Add(_childConnectResetFunc, pInfo, _PARENT_CONNECT_OK_PRI);
//    CommSendData(CS_EXIT, NULL, 0); //切断コマンドを一応発信 悪さするようなら切り
}

//--------------------------------------------------------------
/**
 * @brief   エラーが帰ってきたので親を選びなおす処理へ移動
 * @param   pInfo		ワーク構造体のポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static void _childConnectResetFunc(TCB_PTR tcb, void* work)
{
    _INFO_WORK* pInfo = (_INFO_WORK*)work;

    if(FldTalkMsgEndCheck(_pInfo->msgIndex)){
        if(sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL)){
//            CommFieldStateRebootBattleChild();
            _selectParentWindowOpen(pInfo);
            TCB_Delete(tcb);
        }
    }
}

static void _pleaseGuestRoomStart(_INFO_WORK* pInfo)
{
    CommStateSetEntryChildEnable(FALSE);
    _pInfo->retCode = COMM_RETVAL_OK;
    CommStateSetErrorCheck(TRUE,TRUE);
    CommInfoSendPokeData();
    CommMPSetNoChildError(TRUE);  // ここからはNOCHILDエラー有効
}


//--------------------------------------------------------------
/**
 * @brief   ゲームモードに必要な最小人数を帰す
 * @param   none
 * @retval  最小人数
 */
//--------------------------------------------------------------

int _getMinPlayNum(void)
{
    return CommGetMinEntry(_pInfo->selectGameMode);
}

//--------------------------------------------------------------
/**
 * @brief   ゲームモードに必要な最大人数を帰す
 * @param   none
 * @retval  最大人数
 */
//--------------------------------------------------------------

static int _getMaxPlayNum(void)
{
    return CommGetMaxEntry(_pInfo->selectGameMode);
}

//--------------------------------------------------------------
/**
 * @brief   レギュレーション値を得る
 * @param   none
 * @retval  最大人数
 */
//--------------------------------------------------------------

static int _getRegulationNo(void)
{
    return _pInfo->type1 + (_pInfo->type2 << 4);
}

//--------------------------------------------------------------
/**
 * @brief   リストを閉じる
 * @param   pInfo		ワーク構造体のポインタ
 * @retval  none
 */
//--------------------------------------------------------------
//static void _windowDestroy(_INFO_WORK* pInfo)
//{
  //  GF_BGL_BmpWinDel(&pInfo->talkWin);
//}

//--------------------------------------------------------------
/**
 * @brief   親機を選択するウインドウを開く
 * @param   FIELDSYS_WORK* pFSys   フィールドシステムワークポインタ
 * @param   connectMode      通信モード
 * @param   type1            レギュレーション状態  か  ランク
 * @param   type2            コンテスト種類
 * @retval  none
 */
//--------------------------------------------------------------

void CommSelectParentWindowOpen(FIELDSYS_WORK* pFSys,
                                    int connectMode,int type1,int type2)
{
    _infoInitialize(pFSys);
    _pInfo->selectGameMode = connectMode;
    if((connectMode == COMM_MODE_BATTLE_MIX_1ON1) || (connectMode == COMM_MODE_BATTLE_MULTI)){
        pFSys->regulation = NULL;
    }
    _pInfo->type1 = type1;
    _pInfo->type2 = type2;
    _childStart(_pInfo);
}


void CommParentSelectParentWindowOpen(void)
{
   _selectParentWindowOpen(_pInfo);
}

//--------------------------------------------------------------
/**
 * @brief   親機を選択するウインドウを検査する
 * @param   none
 * @retval  COMM_RETVAL_NULL    BMPLIST_NULL      選択中
            COMM_RETVAL_CANCEL  BMPLIST_CANCEL    userキャンセル
            COMM_RETVAL_OK      (0)               選択完了
            COMM_RETVAL_ERROR   (1)               通信エラー
 */
//--------------------------------------------------------------

u32 CommSelectParentWindowCheck(void)
{
    u32 ret = _pInfo->retCode;

    if(COMM_RETVAL_NULL != ret){
        _infoFinalize();
    }
    return ret;
}

//--------------------------------------------------------------
/**
 * @brief   子機一覧ウインドウを開く
 * @param   FIELDSYS_WORK* pFSys   フィールドシステムワークポインタ
 * @param   connectMode      通信モード
 * @param   type1            レギュレーション状態  か  ランク
 * @param   type2            コンテスト種類
 * @retval  none
 */
//--------------------------------------------------------------

void CommChildWindowOpen(FIELDSYS_WORK* pFSys,
                         int connectMode,int type1,int type2)
{
    _infoInitialize(pFSys);
    _pInfo->selectGameMode = connectMode;
    if((connectMode == COMM_MODE_BATTLE_MIX_1ON1) || (connectMode == COMM_MODE_BATTLE_MULTI)){
        pFSys->regulation = NULL;
    }
    _pInfo->type1 = type1;
    _pInfo->type2 = type2;
    _parentStart(_pInfo);
}

void CommChildListWindowOpen(void)
{
    _childListWindowOpen(_pInfo);  // 接続してくる子機リストを表示
}


//--------------------------------------------------------------
/**
 * @brief   親機を選択するウインドウを検査する
 * @param   none
 * @retval  COMM_RETVAL_NULL    BMPLIST_NULL      選択中
            COMM_RETVAL_CANCEL  BMPLIST_CANCEL    userキャンセル
            COMM_RETVAL_OK      (0)               選択完了
            COMM_RETVAL_ERROR   (1)               通信エラー
 */
//--------------------------------------------------------------

u32 CommChildWindowCheck(void)
{
    u32 ret = _pInfo->retCode;
    if(COMM_RETVAL_NULL != ret){
        _infoFinalize();
    }
    return ret;
}

//--------------------------------------------------------------
/**
 * @brief   ダイレクトコーナールームに入った時の処理
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

BOOL CommDirectIsRoomInitialize(void)
{
    return CommFieldStateIsCopyEnd();
}


//==============================================================================
/**
 * 終了をひとつでも受け取ったかどうか知らせる
 * @param   none
 * @retval  受信していた場合TRUE 受信していなかったらFALSE
 */
//==============================================================================

BOOL CommRecvIsExit(void)
{
    return FALSE;
}



#ifdef PM_DEBUG

//--------------------------------------------------------------
/**
 * @brief   デバッグ用ダイレクトコーナー親機接続
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

void CommDirectParent_Debug(FIELDSYS_WORK* pFSys)
{
    CommFieldStateEnterBattleParent_Debug(_pInfo->pFSys, _pInfo->selectGameMode,
                                          _getRegulationNo());
}

//--------------------------------------------------------------
/**
 * @brief   デバッグ用ダイレクトコーナー子機接続
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

void CommDirectChild_Debug(FIELDSYS_WORK* pFSys)
{
    CommFieldStateConnectBattleChild_Debug(_pInfo->pFSys,
                                      _pInfo->selectGameMode, _getRegulationNo(), 0);
}

//--------------------------------------------------------------
/**
 * @brief   デバッグ用ダイレクトコーナー接続完了
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

void CommDirectConnect_Debug(void)
{
    // 部屋に案内するメッセージ
    _pleaseGuestRoomStart(_pInfo);
}


//--------------------------------------------------------------
/**
 * @brief   デバッグ用ダイレクトコーナー初期パラメータ設定
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

void CommDirectConnectSetParam_Debug(FIELDSYS_WORK* pFSys,int gameMode, int type1, int type2)
{
    _infoInitialize(pFSys);
    _pInfo->selectGameMode = gameMode;
    _pInfo->type1 = type1;
    _pInfo->type2 = type2;
}

#endif //PM_DEBUG

