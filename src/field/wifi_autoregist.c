//============================================================================================
/**
 * @file	wifi_autoregist.c
 * @bfief	WIFI友達手帳登録   ->  削除はノートappへ
 * @author	k.ohno
 * @date	06.04.16
 */
//============================================================================================


#include "common.h"

#include "fieldsys.h"
#include "field_event.h"
#include "fld_bmp.h"

#include "system/bmp_menu.h"
#include "system/bmp_list.h"
#include "system/wordset.h"
#include "system/window.h"
#include "system/fontproc.h"
#include "system/snd_tool.h"
#include "gflib/strbuf_family.h"

#include "savedata/wifilist.h"

#include "communication/communication.h"
#include "communication/comm_state.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_wifi_note.h"

#include "wifi/dwc_rapfriend.h"
#include "itemtool/itemsym.h"

#include "fieldmap.h"
#include "fld_bmp.h"
#include "talk_msg.h"

#include "wifi_autoregist.h"


// 会話ウィンドウ
#define COMM_MESFRAME_PAL     ( 10 )         //  メッセージウインドウ
#define COMM_MENUFRAME_PAL    ( 11 )         //  メニューウインドウ
#define COMM_MESFONT_PAL      ( 12 )         //  メッセージフォント
#define COMM_SYSFONT_PAL	  ( 13 )         //  システムフォント
#define	COMM_TALK_WIN_CGX_SIZE	( 18+12 )
#define	COMM_TALK_WIN_CGX_NUM	( 512 - COMM_TALK_WIN_CGX_SIZE)
#define	COMM_MSG_WIN_PX		( 2 )
#define	COMM_MSG_WIN_PY		( 19 )
#define	COMM_MSG_WIN_SX		( 27 )
#define	COMM_MSG_WIN_SY		( 4 )
#define	COMM_MSG_WIN_PAL		( COMM_MESFONT_PAL )
#define	COMM_MSG_WIN_CGX		( (COMM_TALK_WIN_CGX_NUM - 73) - ( COMM_MSG_WIN_SX * COMM_MSG_WIN_SY ) )
#define TALK_MESSAGE_BUF_NUM (110)

enum {    // 自動登録
    WIFINOTE_MODE_AUTOINPUT_CHECK,
    WIFINOTE_MODE_AUTOINPUT_INIT,
    WIFINOTE_MODE_AUTOINPUT_YESNO,
    WIFINOTE_MODE_AUTOINPUT_WAIT,
    WIFINOTE_MODE_DEL_YESNO,
    WIFINOTE_MODE_DEL_WAIT,
    WIFINOTE_MODE_END_YESNO,
    WIFINOTE_MODE_END_WAIT,
    WIFINOTE_MODE_DELMENU_INIT,
    WIFINOTE_MODE_DELMENU_WAIT,
    WIFINOTE_MODE_ERASE_YESNO,
    WIFINOTE_MODE_ERASE_WAIT,
    WIFINOTE_MODE_END,
} _event_seq;




typedef struct{
	BMPLIST_DATA*   menulist;
    BMPLIST_WORK* lw;		// BMPメニューワーク
    STRBUF*         pExpStrBuf;
	STRBUF			*TalkString;							// 会話メッセージ用
	GF_BGL_BMPWIN			MsgWin;									// 会話ウインドウ
	GF_BGL_BMPWIN			listWin;									// 会話ウインドウ
    FIELDSYS_WORK* pFSys;
    SAVEDATA*  pSaveData;
	WORDSET			*WordSet;					// メッセージ展開用ワークマネージャー
	MSGDATA_MANAGER *MsgManager;				// 名前入力メッセージデータマネージャー
	int	MsgIndex;								// 終了検出用ワーク
    BMPMENU_WORK* pYesNoWork;
    int seq;
    int checkFriend[COMM_MACHINE_MAX];
    int indexFriend[COMM_MACHINE_MAX];
    int addFriendNo;
    int erasePos;
}EV_WIFIAUTOREG_WORK;


static void _messagePrint( EV_WIFIAUTOREG_WORK *wk, int msgno );
static void _freeWork(EV_WIFIAUTOREG_WORK* wk);

static void BmpListMoveSeCall(BMPLIST_WORK * wk,u32 param,u8 mode);


//------------------------------------------------------------------
/**
 * $brief   接続している人のフレンドコード検査  登録する人が見つかったら登録
            WIFINOTE_MODE_AUTOINPUT_CHECK
 * @param   wk		
 * @param   seq		
 * @retval  int 			
 */
//------------------------------------------------------------------

static BOOL _friendAutoInputCheck( EV_WIFIAUTOREG_WORK* wk)
{
    int i,hit = FALSE;
    DWCFriendData *keyList  = WifiList_GetDwcDataPtr(SaveData_GetWifiListData(wk->pSaveData),0);
    DWCFriendData* pFriend;

    if(FALSE == dwc_friendAutoInputCheck(wk->pSaveData, wk->checkFriend, HEAPID_FIELD)){
        return TRUE;
    }
    wk->addFriendNo = 0;  // 登録開始
    TalkWinGraphicSet(
        wk->pFSys->bgl, GF_BGL_FRAME3_M, COMM_TALK_WIN_CGX_NUM,
        COMM_MESFRAME_PAL, CONFIG_GetWindowType(SaveData_GetConfig(wk->pSaveData)), HEAPID_FIELD );
	MenuWinGraphicSet( wk->pFSys->bgl, FLD_MBGFRM_FONT, MENU_WIN_CGX_NUM,
                       MENU_WIN_PAL, 0, HEAPID_FIELD );

    wk->seq = WIFINOTE_MODE_AUTOINPUT_INIT;
    return FALSE;
}

//------------------------------------------------------------------
/**
 * $brief   一人ずつ登録するかどうか問い合わせる
            WIFINOTE_MODE_AUTOINPUT_INIT
 * @param   wk		
 * @param   seq		
 * @retval  int 			
 */
//------------------------------------------------------------------

static BOOL _friendAutoInputInit( EV_WIFIAUTOREG_WORK* wk )
{
    int i;
    MYSTATUS* pMyStatus;
    
    wk->addFriendNo = -1;
    for(i = 0; i < CommGetConnectNum(); i++){
        if(wk->checkFriend[i] == DWCFRIEND_NODATA){
            wk->addFriendNo = i;
            wk->checkFriend[i] = DWCFRIEND_INLIST;
            break;
        }
    }
    if(wk->addFriendNo == -1){  // 登録完了
        return TRUE;
    }


	//手帳を持っていたら
	if( MyItem_CheckItem( SaveData_GetMyItem(wk->pSaveData),
							ITEM_TOMODATITETYOU,1,HEAPID_FIELD) == TRUE ){
        pMyStatus = CommInfoGetMyStatus(wk->addFriendNo);
        WORDSET_RegisterPlayerName(wk->WordSet, 0, pMyStatus);
        _messagePrint(wk,msg_wifi_note_add_01);
        wk->seq = WIFINOTE_MODE_AUTOINPUT_YESNO;
        return FALSE;
    }
    // 持ってないならAUTO
    {
        WIFI_LIST* pList = SaveData_GetWifiListData(wk->pSaveData);
        for(i = 0; i < WIFILIST_FRIEND_MAX;i++){
            if( !WifiList_IsFriendData( pList, i ) ){
                dwc_friendWrite(wk->pSaveData, wk->addFriendNo,
                                i, HEAPID_FIELD, FALSE);
                break;
            }
        }
    }
    wk->seq = WIFINOTE_MODE_AUTOINPUT_INIT;
    return FALSE;
}

//------------------------------------------------------------------
/**
 * $brief   登録のYESNO呼び出し
            WIFINOTE_MODE_AUTOINPUT_CHECK
 * @param   wk		
 * @param   seq		
 * @retval  int 			
 */
//------------------------------------------------------------------

static const BMPWIN_DAT _yesNoBmpDat = {
    GF_BGL_FRAME3_M, FLD_YESNO_WIN_PX, FLD_YESNO_WIN_PY,
    FLD_YESNO_WIN_SX, FLD_YESNO_WIN_SY, FLD_YESNO_WIN_PAL, FLD_YESNO_WIN_CGX
    };


static BOOL _friendAutoInputYesNo( EV_WIFIAUTOREG_WORK* wk )
{
    if( GF_MSG_PrintEndCheck( wk->MsgIndex ) == 0 ){
        wk->pYesNoWork =
            BmpYesNoSelectInit( wk->pFSys->bgl,
                                &_yesNoBmpDat,
                                MENU_WIN_CGX_NUM, MENU_WIN_PAL,
                                HEAPID_FIELD );
        wk->seq = WIFINOTE_MODE_AUTOINPUT_WAIT;
    }
    return FALSE;
}

//------------------------------------------------------------------
/**
 * $brief   登録YESNO待ち
 * @param   wk		
 * @param   seq		
 * @retval  int 			
 */
//------------------------------------------------------------------

static BOOL _friendAutoInputWait( EV_WIFIAUTOREG_WORK* wk )
{
    DWCFriendData* pFriend;
    STRBUF* pBuf;
    int i;
    int ret = BmpYesNoSelectMain(wk->pYesNoWork, HEAPID_FIELD);

    if(ret == BMPMENU_NULL){  // まだ選択中
        return FALSE;
    }else if(ret == 0){ // はいを選択した場合
        //書き込み
        WIFI_LIST* pList = SaveData_GetWifiListData(wk->pSaveData);
        for(i = 0; i < WIFILIST_FRIEND_MAX;i++){
            if( !WifiList_IsFriendData( pList, i ) ){

                dwc_friendWrite(wk->pSaveData, wk->addFriendNo, i, HEAPID_FIELD, FALSE);
                break;
            }
        }
        if(i == WIFILIST_FRIEND_MAX){
            // 書き込めない場合
            _messagePrint(wk, msg_wifi_note_add_02);
            wk->seq = WIFINOTE_MODE_DEL_YESNO;
            return FALSE;
        }
    }
    wk->seq = WIFINOTE_MODE_AUTOINPUT_INIT;
    return FALSE;
}

//------------------------------------------------------------------
/**
 * $brief   削除するかどうかYESNO待ち  WIFINOTE_MODE_DEL_YESNO
 * @param   wk		
 * @param   seq		
 * @retval  int 			
 */
//------------------------------------------------------------------

static BOOL _anyOneDeleteYesNo( EV_WIFIAUTOREG_WORK* wk )
{
    if( GF_MSG_PrintEndCheck( wk->MsgIndex ) == 0 ){
        wk->pYesNoWork =
            BmpYesNoSelectInit( wk->pFSys->bgl,
                                &_yesNoBmpDat,
                                MENU_WIN_CGX_NUM, MENU_WIN_PAL,
                                HEAPID_FIELD );
        wk->seq = WIFINOTE_MODE_DEL_WAIT;
    }
    return FALSE;
}

//------------------------------------------------------------------
/**
 * $brief   削除するかどうかYESNO待ち  WIFINOTE_MODE_DEL_YESNO
 * @param   wk		
 * @param   seq		
 * @retval  int 			
 */
//------------------------------------------------------------------

static BOOL _anyOneDeleteWait( EV_WIFIAUTOREG_WORK* wk )
{
    MYSTATUS* pMyStatus;
    DWCFriendData* pFriend;
    STRBUF* pBuf;
    int i;
    int ret = BmpYesNoSelectMain(wk->pYesNoWork, HEAPID_FIELD);

    if(ret == BMPMENU_NULL){  // まだ選択中
        return FALSE;
    }else if(ret == 0){ // はいを選択した場合
        wk->seq = WIFINOTE_MODE_DELMENU_INIT;
        // 削除メニュ
    }
    else{  // いいえの場合
        pMyStatus = CommInfoGetMyStatus(wk->addFriendNo);
        WORDSET_RegisterPlayerName(wk->WordSet, 0, pMyStatus);
        _messagePrint(wk, msg_wifi_note_add_03);
        wk->seq = WIFINOTE_MODE_END_YESNO;
    }
    return FALSE;
}

//------------------------------------------------------------------
/**
 * $brief   あきらめるかどうかYESNO待ち  WIFINOTE_MODE_END_YESNO
 * @param   wk		
 * @param   seq		
 * @retval  int 			
 */
//------------------------------------------------------------------

static BOOL _exitYesNo( EV_WIFIAUTOREG_WORK* wk )
{
    if( GF_MSG_PrintEndCheck( wk->MsgIndex ) == 0 ){
        wk->pYesNoWork =
            BmpYesNoSelectInit( wk->pFSys->bgl,
                                &_yesNoBmpDat,
                                MENU_WIN_CGX_NUM, MENU_WIN_PAL,
                                HEAPID_FIELD );
        wk->seq = WIFINOTE_MODE_END_WAIT;
    }
    return FALSE;
}

//------------------------------------------------------------------
/**
 * $brief   あきらめるかどうかのYESNOWAIT  WIFINOTE_MODE_END_WAIT
 * @param   wk		
 * @param   seq		
 * @retval  int 			
 */
//------------------------------------------------------------------

static BOOL _exitWait( EV_WIFIAUTOREG_WORK* wk )
{
    MYSTATUS* pMyStatus;
    DWCFriendData* pFriend;
    STRBUF* pBuf;
    int i;
    int ret = BmpYesNoSelectMain(wk->pYesNoWork, HEAPID_FIELD);

    if(ret == BMPMENU_NULL){  // まだ選択中
        return FALSE;
    }else if(ret == 0){ // はいを選択した場合
        wk->seq = WIFINOTE_MODE_END;
    }
    else{  // いいえの場合
        _messagePrint(wk, msg_wifi_note_add_02);
        wk->seq = WIFINOTE_MODE_DEL_YESNO;
    }
    return FALSE;
}

//------------------------------------------------------------------
/**
 * $brief   削除するリスト表示
 * @param   wk		
 * @param   seq		
 * @retval  int 			
 */
//------------------------------------------------------------------
#define _TREASUREMENU_POSX    (19)
#define _TREASUREMENU_POSY    (1)
#define _TREASUREMENU_SIZE_X  (12)
#define FLD_SYSFONT_PAL	     ( 13 )         //  システムフォント

///汎用選択メニューのリスト
static const BMPLIST_HEADER MenuListHeader = {
    NULL,			// 表示文字データポインタ
    NULL,					// カーソル移動ごとのコールバック関数
    NULL,					// 一列表示ごとのコールバック関数
    NULL,					// 
    WIFILIST_FRIEND_MAX,	// リスト項目数
    WIFILIST_FRIEND_MAX,	// 表示最大項目数
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
    FONT_SYSTEM,			// 文字指定
    0,						// ＢＧカーソル(allow)表示フラグ(0:ON,1:OFF)
    NULL,                   // ワーク
};


static BOOL _delMenuInit( EV_WIFIAUTOREG_WORK* wk )
{
    WIFI_LIST* pList = SaveData_GetWifiListData(wk->pSaveData);
    BMPLIST_HEADER list_h;
    int count = WifiList_GetFriendDataNum(pList);
    int line = 5;

    //BMPウィンドウ生成
    wk->menulist = BMP_MENULIST_Create( count+1, HEAPID_FIELD );
    GF_BGL_BmpWinAdd(wk->pFSys->bgl, &wk->listWin,
                     GF_BGL_FRAME3_M, _TREASUREMENU_POSX, _TREASUREMENU_POSY,
                     _TREASUREMENU_SIZE_X, line * 2, FLD_SYSFONT_PAL,
                     FLD_MSG_WIN_CGX - (10* (line+2) * 2));
    BmpMenuWinWrite(&wk->listWin, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL );
	{
		MSGDATA_MANAGER* msgman;
		int i=0;

        for(i = 0; i < WIFILIST_FRIEND_MAX ; i++){
            if(WifiList_IsFriendData( pList, i )){
                STRBUF_SetStringCode(wk->pExpStrBuf, WifiList_GetFriendNamePtr(pList,i));
                BMP_MENULIST_AddString( wk->menulist, wk->pExpStrBuf, i);
            }
		}
        BMP_MENULIST_AddArchiveString( wk->menulist, wk->MsgManager,
                                       msg_wifi_note_12, BMPLIST_CANCEL);
    }

    list_h = MenuListHeader;
    list_h.count = count + 1;
    list_h.line = line;
    list_h.list = wk->menulist;
    list_h.win = &wk->listWin;
//    list_h.call_back = wk->pLineCallBack;
    list_h.call_back = BmpListMoveSeCall;
    list_h.work = wk;
    wk->lw = BmpListSet(&list_h, 0, 0, HEAPID_FIELD);
    GF_BGL_BmpWinOn(&wk->listWin);
    wk->seq = WIFINOTE_MODE_DELMENU_WAIT;


    return FALSE;
}


static BOOL _delMenuWait( EV_WIFIAUTOREG_WORK* wk )
{
    MYSTATUS* pMyStatus;
    int ret;
    
    ret = BmpListMain(wk->lw);
    switch(ret){
    case BMPLIST_NULL:
        return FALSE;
    case BMPLIST_CANCEL:
		Snd_SePlay( SEQ_SE_DP_SELECT );
        pMyStatus = CommInfoGetMyStatus(wk->addFriendNo);
        WORDSET_RegisterPlayerName(wk->WordSet, 0, pMyStatus);
        _messagePrint(wk, msg_wifi_note_add_03);
        wk->seq = WIFINOTE_MODE_END_YESNO;
        break;
    default:
		Snd_SePlay( SEQ_SE_DP_SELECT );
        wk->erasePos = ret;
        {
            WIFI_LIST* pList = SaveData_GetWifiListData(wk->pSaveData);
            MYSTATUS* pMy = MyStatus_AllocWork(HEAPID_FIELD);
            MyStatus_SetMyName(pMy,WifiList_GetFriendNamePtr(pList,ret));
            WORDSET_RegisterPlayerName(wk->WordSet, 0, pMy);
            sys_FreeMemoryEz(pMy);
        }
        _messagePrint(wk, msg_wifi_note_add_04);
        wk->seq = WIFINOTE_MODE_ERASE_YESNO;
        break;
    }

    BmpMenuWinClear(&wk->listWin, WINDOW_TRANS_ON );
    GF_BGL_BmpWinDel(&wk->listWin);
    BmpListExit(wk->lw, NULL, NULL);
    BMP_MENULIST_Delete( wk->menulist );
    return FALSE;
}

//------------------------------------------------------------------
/**
 * $brief   削除するかどうかYESNO待ち  WIFINOTE_MODE_END_YESNO
 * @param   wk		
 * @param   seq		
 * @retval  int 			
 */
//------------------------------------------------------------------

static BOOL _eraseYesNo( EV_WIFIAUTOREG_WORK* wk )
{
    if( GF_MSG_PrintEndCheck( wk->MsgIndex ) == 0 ){
        wk->pYesNoWork =
            BmpYesNoSelectInit( wk->pFSys->bgl,
                                &_yesNoBmpDat,
                                MENU_WIN_CGX_NUM, MENU_WIN_PAL,
                                HEAPID_FIELD );
        wk->seq = WIFINOTE_MODE_ERASE_WAIT;
    }
    return FALSE;
}

//------------------------------------------------------------------
/**
 * $brief   削除するかどうかのYESNOWAIT  WIFINOTE_MODE_DELMENU_INIT
 * @param   wk		
 * @param   seq		
 * @retval  int 			
 */
//------------------------------------------------------------------

static BOOL _eraseWait( EV_WIFIAUTOREG_WORK* wk )
{
    WIFI_LIST* pList = SaveData_GetWifiListData(wk->pSaveData);
    MYSTATUS* pMyStatus;
    DWCFriendData* pFriend;
    STRBUF* pBuf;
    int ret = BmpYesNoSelectMain(wk->pYesNoWork, HEAPID_FIELD);

    if(ret == BMPMENU_NULL){  // まだ選択中
        return FALSE;
    }else if(ret == 0){ // はいを選択した場合
        WifiList_ResetData(pList, wk->erasePos);  //消す
        // 最後に追加
        dwc_friendWrite(wk->pSaveData, wk->addFriendNo, WIFILIST_FRIEND_MAX-1, HEAPID_FIELD, FALSE);
        wk->seq = WIFINOTE_MODE_AUTOINPUT_INIT;
    }
    else{  // いいえの場合
        pMyStatus = CommInfoGetMyStatus(wk->addFriendNo);
        WORDSET_RegisterPlayerName(wk->WordSet, 0, pMyStatus);
        _messagePrint(wk, msg_wifi_note_add_03);
        wk->seq = WIFINOTE_MODE_END_YESNO;
    }
    return FALSE;
}







//-----------------------------------------------------------------------------
/**
 * @brief	WIFI戦闘イベントシーケンス    k.ohno作成
 * @param	event		イベント制御ワークへのポインタ
 * @retval	TRUE		イベント終了
 * @retval	FALSE		イベント継続中
 */
//-----------------------------------------------------------------------------
static BOOL GMEVENT_WifiAutoReg(GMEVENT_CONTROL * event)
{
	EV_WIFIAUTOREG_WORK* wk = FieldEvent_GetSpecialWork(event);
	FIELDSYS_WORK* fsys = FieldEvent_GetFieldSysWork(event);

    switch (wk->seq) {
	case WIFINOTE_MODE_AUTOINPUT_CHECK:
        if(_friendAutoInputCheck(wk)){
            wk->seq = WIFINOTE_MODE_END;
        }
		break;
      case WIFINOTE_MODE_AUTOINPUT_INIT:
        if(_friendAutoInputInit(wk)){
            wk->seq = WIFINOTE_MODE_END;
        }
        break;
      case WIFINOTE_MODE_AUTOINPUT_YESNO:
        _friendAutoInputYesNo(wk);
        break;
      case WIFINOTE_MODE_AUTOINPUT_WAIT:
        _friendAutoInputWait(wk);
        break;
      case WIFINOTE_MODE_DEL_YESNO:
        _anyOneDeleteYesNo(wk);
        break;
      case WIFINOTE_MODE_DEL_WAIT:
        _anyOneDeleteWait(wk);
        break;
      case WIFINOTE_MODE_END_YESNO:
        _exitYesNo(wk);
        break;
      case WIFINOTE_MODE_END_WAIT:
        _exitWait(wk);
        break;
      case WIFINOTE_MODE_DELMENU_INIT:
        _delMenuInit(wk);
        break;
      case WIFINOTE_MODE_DELMENU_WAIT:
        _delMenuWait(wk);
        break;
      case WIFINOTE_MODE_ERASE_YESNO:
        _eraseYesNo(wk);
        break;
      case WIFINOTE_MODE_ERASE_WAIT:
        _eraseWait(wk);
        break;
        
      case WIFINOTE_MODE_END:
        _freeWork(wk);
        sys_FreeMemoryEz(wk);
        FieldSystemProc_SeqHoldEnd();		
        return TRUE;
	}
	return FALSE;
}


//------------------------------------------------------------------
/**
 * $brief   会話ウインドウ表示
 *
 * @param   wk		
 *
 * @retval  none		
 */
//------------------------------------------------------------------


static void _messagePrint( EV_WIFIAUTOREG_WORK *wk, int msgno )
{
//    u8 speed = CONFIG_GetMsgPrintSpeed(SaveData_GetConfig(wk->pFSys->savedata));

    // 文字列取得
    if(GF_BGL_BmpWinAddCheck(&wk->MsgWin)){
        GF_BGL_BmpWinDel(&wk->MsgWin);
    }
  //  GF_BGL_BmpWinAdd(wk->pFSys->bgl, &wk->MsgWin,
    //                 GF_BGL_FRAME3_M,
      //               COMM_MSG_WIN_PX, COMM_MSG_WIN_PY,
        //             COMM_MSG_WIN_SX, COMM_MSG_WIN_SY,
          //           COMM_MESFONT_PAL, COMM_MSG_WIN_CGX);

	MSGMAN_GetString(  wk->MsgManager, msgno, wk->pExpStrBuf );
	WORDSET_ExpandStr( wk->WordSet, wk->TalkString, wk->pExpStrBuf );

    FldTalkBmpAdd( wk->pFSys->bgl, &wk->MsgWin, FLD_MBGFRM_FONT );
	// 会話ウインドウ枠描画
//    GF_BGL_BmpWinDataFill(&wk->MsgWin, 15 );
//    BmpTalkWinWrite(&wk->MsgWin, WINDOW_TRANS_ON, COMM_TALK_WIN_CGX_NUM, COMM_MESFRAME_PAL );

    FieldTalkWinPut( &wk->MsgWin,SaveData_GetConfig(wk->pFSys->savedata) );
	// 文字列描画開始
	wk->MsgIndex = FieldTalkMsgStart( &wk->MsgWin, wk->TalkString,
                                      SaveData_GetConfig(wk->pFSys->savedata), 1);

}



static void _initWork(EV_WIFIAUTOREG_WORK* wk)
{
    MI_CpuClear8(wk,sizeof(EV_WIFIAUTOREG_WORK));
    wk->WordSet    = WORDSET_Create( HEAPID_FIELD );
    wk->MsgManager = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_wifi_note_dat, HEAPID_FIELD );

    wk->TalkString =  STRBUF_Create( TALK_MESSAGE_BUF_NUM, HEAPID_FIELD );
    wk->pExpStrBuf = STRBUF_Create( TALK_MESSAGE_BUF_NUM, HEAPID_FIELD );
}

static void _freeWork(EV_WIFIAUTOREG_WORK* wk)
{
	MSGMAN_Delete( wk->MsgManager );
	WORDSET_Delete( wk->WordSet );

	STRBUF_Delete( wk->TalkString );
    STRBUF_Delete(wk->pExpStrBuf);
    if(GF_BGL_BmpWinAddCheck(&wk->MsgWin)){
  //      BmpTalkWinClear( &wk->MsgWin, WINDOW_TRANS_ON );
        GF_BGL_BmpWinDel(&wk->MsgWin);
    }
}

void EventSet_WifiAutoReg(FIELDSYS_WORK* pFSys)
{
	EV_WIFIAUTOREG_WORK * eww;
    GMEVENT_CONTROL * event = pFSys->event;

    eww = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(EV_WIFIAUTOREG_WORK));
    _initWork(eww);
    eww->pFSys = pFSys;
    eww->pSaveData = pFSys->savedata;
    eww->seq = WIFINOTE_MODE_AUTOINPUT_CHECK;
    if(event == NULL){
        FieldEvent_Set(pFSys, GMEVENT_WifiAutoReg, eww);
    }
    else{
        FieldEvent_Call(event, GMEVENT_WifiAutoReg, eww);
    }
}

//リスト表示用コールバック
static void BmpListMoveSeCall(BMPLIST_WORK * wk,u32 param,u8 mode)
{
	if( mode == 0 ){	//初期化時
		Snd_SePlay( SEQ_SE_DP_SELECT );
	}
}

