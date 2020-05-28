//=============================================================================
/**
 * @file	ug_talk.c
 * @brief	地下会話を管理するクラス
 * @author	Katsumi Ohno
 * @date    2005.12.19
 */
//=============================================================================


#include "common.h"

#include "../fieldsys.h"
#include "system/bmp_menu.h"
#include "system/bmp_list.h"
#include "system/fontproc.h"
#include "system/window.h"
#include "system/snd_tool.h"
#include "system/clact_tool.h"

#include "../fld_bmp.h"
#include "../syswork.h"
#include "system/wordset.h"

#include "msgdata/msg_underworld.h"
#include "msgdata/msg_undersecretquestion.h"
#include "msgdata/msg_undersecretanswer.h"
#include "msgdata/msg.naix"

#include "../fieldmap.h"
#include "../fld_bmp.h"
#include "../field_clact.h"
#include "../fld_comact.h"
#include "communication/communication.h"
#include "ug_manager.h"
#include "ug_local.h"
#include "../goods_data.h"


//==============================================================================
//	定数定義
//==============================================================================

#define _EVWIN_MSG_BUF_SIZE		(50*2)			//メッセージバッファサイズ
#define _MENU_UG_PRI  (10000)   // メニューのタスクpriorty

#define _QUESTION_LIST_NUM   (4)   // 表示する質問数
#define _QUESTION_LIST_MAX   (12)   // 質問最大
//#define _QUESTION_LIST_BOTH  (50)    // 同じ答えを選んだ場合
#define _QUESTION_LIST_CANCEL  (51)  // 質問に答えたくなかった場合

#define _QUESTION_END_TIMING  (100)
#define _QUESTION_END_TIMING2  (101)


typedef enum{
    _TALK_SEQ_NONE,
    _TALK_INIT,            // 話しかけた
    _TALK_MENU,            // メニューが出ている
    _MSG_PLUS_TALK_END,    // メッセージを出して、会話をやめる
    _TALK_END,             // 会話をやめる
    _TALK_CARD_WAIT,       // カードを見せてもらおうと待機中
    _TALK_REJECT_CARD,     // カードを見せるのを拒否
    _TALK_TALKCHEKCEND,    // 会話の終了を待って終わる
    _TALK_CANCELASKER_END,  // 用事があるので終了する場合
    _TALK_CARD_DISP,
    _TALK_CARD_DISP_WAIT,
    _TALK_CARD_DISP_FIN,
    _TALK_CARD_FIN_WAIT,
    _TALK_CARD_CALLBACK_WAIT,
    _TALK_NEXT,
    _TALK_WAIT_NEXT,
    _TALK_ITEMMENU_OPEN,
    _TALK_ITEMMENU_WAIT,
    _TALK_ITEMMENU_END,
    _TALK_ITEM_SEND_CHECK,
    _TALK_ITEM_SEND_CHECK_WAIT,
    _TALK_ITEM_SEND_ASK_WAIT,
    _TALK_ITEM_SEND_OK,
    _TALK_ITEM_SEND_FULL,
    _TALK_ITEM_SEND_NO,
    _TALK_ITEM_SEND_OK_ZINGLE,
    _TALK_ITEMEND_TIMING,
    _TALK_QES_CATEGORY,  // カテゴリー選択
    _TALK_QES_CATEGORY_LIST,    // メニュー
    _TALK_QES_CATEGORY_LIST_WAIT,  // 選択
    _TALK_QES_CATEGORY_WAIT,
    _TALK_QES_CATEGORY_RECV,
    _TALK_CATCH_ANSWER,
    _TALK_WAIT_NEXT_QUES_CANCEL,
    _TALK_ANSWER_LIST_INIT,
    _TALK_ANSWER_LIST_WAIT,
    _TALK_QES_END_WAIT,
    _TALK_QES_END_WAIT2,
    _TALK_QES_END_WAIT25,
    _TALK_QES_END_WAIT3,
    _TALK_QES_END_WAIT4,
    _TALK_QES_END_WAIT5,
    _TALK_QUES_CANCEL_STOPER,
};

typedef enum{
    _ASK_SEQ_NONE,
    _ASK_INIT,             // 話しかけられた
    _ASK_WAIT,             // 話しかけられ中
    _MSG_PLUS_ASK_END,    
    _ASK_END,
    _ASK_CARD,
    _ASK_CARD_WAIT,        // カードを見せるよう要求が来た
    _ASK_CARD_YESNO_WAIT,
    _ASK_CANCELTALK_END,
    _ASK_TALKCHEKCEND,   // 会話の終了を待って終わる
    _ASK_CARD_DISP,
    _ASK_CARD_DISP_WAIT,
    _ASK_CARD_DISP_FIN,
    _ASK_CARD_FIN_WAIT,
    _ASK_CARD_CALLBACK_WAIT,
    _ASK_NEXT,
    _ASK_WAIT_NEXT,
    _ASK_RECV_ITEM,
    _ASK_RECV_ITEM_YESNO_WAIT,
    _ASK_ITEM_RECVED,
    _ASK_ITEM_RECVED_WAIT,
    _ASK_ITEM_RECVED_WAIT_END,

    _ASK_QES_START,
    _ASK_QES_RECV_WAIT,
    _ASK_QES_CATEGORY_MSG,
    _ASK_QES_ANSWER_LIST,
    _ASK_ANSWERED_WAIT,
    _ASK_ANSERED_RETURN,
    _ASK_ANSERED_RETURN_WAIT,
    _ASK_SECRET_TALK_END,
    _ASK_SECRET_TALK_END2,
    _ASK_SECRET_TALK_END3,
    _ASK_SECRET_TALK_END4,
};


typedef enum{
    _QUESTION_TALK,
    _ANSWER_ASK,
    _ANSWER_TALK,
} QuestionType_e;

//==============================================================================
//	構造体定義
//==============================================================================

typedef struct{
    u8 netID;
    u8 seq;
} _SEQ_COMMAND;


typedef struct{
    u8 no;
    u8 targetID;
    u8 questionType;
} _SECRET_QUESTION_COMMAND;


typedef struct{
    u8 netID;
    u8 itemType;
    u8 itemNo;
} _ITEMSEND_COMMAND;


// 話しかけ状況構造体
typedef struct{
    TCB_PTR pMyTCB;
    _START_WORK* pStartWin;
    FIELDSYS_WORK* pFSys;
    GF_BGL_BMPWIN  win;		// BMPウィンドウワーク
	BMPLIST_DATA*  menulist;
    BMPLIST_WORK*  lw;		// BMPメニューワーク
    BMPMENU_WORK*  pYesNoWork;
    _ITEMSEND_COMMAND sendItem;  // 受け取る予定のアイテム
    pEndFunc endfunc;
    u16 connectIndex;  // つなぐ親機のINDEX
    u8 list_id;
    u8 list_ans;
    u8 waitMode;
    u8 endState;
    u8 work;
    u8 seq;        // 自分のシーケンス
    u8 reqSeq;     // 相手から来たシーケンス
	u16 pos_bak;
} _TALK_WORK;


static _TALK_WORK* _pTalkWork = NULL;

// 話しかけられ状況構造体
typedef struct{
    TCB_PTR pMyTCB;
    FIELDSYS_WORK* pFSys;
    GF_BGL_BMPWIN  win;		// BMPウィンドウワーク
	BMPLIST_DATA*  menulist;
    BMPLIST_WORK*  lw;		// BMPメニューワーク
    BMPMENU_WORK*  pYesNoWork;
    _ITEMSEND_COMMAND recvItem;  // 受け取る予定のアイテム
    pEndFunc endfunc;
    u16 connectIndex;  // つなぐ親機のINDEX
    u8 list_id;
    u8 list_ans;
    u8 list_ans2;
    u8 waitMode;
    u8 endState;
    u8 work;
    u8 seq;        // 自分のシーケンス
    u8 reqSeq;     // 相手から来たシーケンス
	u16 pos_bak;
} _ASK_WORK;


static _ASK_WORK* _pAskWork = NULL;


//==============================================================================
//	型宣言
//==============================================================================
typedef void (*pTalkFunc)(_TALK_WORK *);

//==============================================================================
//	static定義
//==============================================================================

static void _mainFunc(TCB_PTR tcb, void* work);
static BOOL _talkMenuFunc(TCB_PTR tcb, void* work);
static void _talkMenuEnd(TCB_PTR tcb, _TALK_WORK* pTalk);
static void _cardStart(_TALK_WORK* pTalk);
static void _trapSet( _TALK_WORK* pTalk );
static void _questionStart( _TALK_WORK* pTalk );
static void _sendItem( _TALK_WORK* pTalk );
static void _talkExit( _TALK_WORK* pTalk );
static void _askMenuEnd(TCB_PTR tcb, _ASK_WORK* pAsk);

static void UgTalkListMoveSe( _TALK_WORK* pTalk );

//==============================================================================
//	話しかけメニューリスト用データ等
//==============================================================================

static const struct {
	u32  str_id;
	u32  param;
}MenuParamList[] = {
    { msg_underworld_04, (u32)_cardStart },
    { msg_underworld_05, (u32)_questionStart },
    { msg_underworld_06, (u32)_sendItem },
    { msg_underworld_07, (u32)_talkExit },
};

///はなしかけ選択メニューのリスト
static const BMPLIST_HEADER TalkMenuListHeader = {
    NULL,			// 表示文字データポインタ
    NULL,					// カーソル移動ごとのコールバック関数
    NULL,					// 一列表示ごとのコールバック関数
    NULL,					// 
    NELEMS(MenuParamList),	// リスト項目数
    NELEMS(MenuParamList),	// 表示最大項目数
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
    NULL,                   // ワーク
};

//==============================================================================
//	YesNoメニューリスト用データ
//==============================================================================
static const BMPWIN_DAT _yesNoBmpDat = {
    GF_BGL_FRAME3_M, FLD_YESNO_WIN_PX, FLD_YESNO_WIN_PY,
    FLD_YESNO_WIN_SX, FLD_YESNO_WIN_SY, FLD_YESNO_WIN_PAL, FLD_YESNO_WIN_CGX
    };


//==============================================================================
// 関数
//==============================================================================

//--------------------------------------------------------------
/**
 * @brief   話しかけ側にコマンドを送信
 * @param   netID  話しかけ側ID
 * @param   seq    命令
 * @retval  none
 */
//--------------------------------------------------------------

static void _seqTalkCommandSend(_ASK_WORK* pWork, int seq)
{
    _SEQ_COMMAND seqComm;

    seqComm.netID = pWork->connectIndex;
    seqComm.seq = seq;
    CommSendFixSizeData(CF_TALKSEQ_SET, &seqComm);
}

//--------------------------------------------------------------
/**
 * @brief   話しかけられ側にコマンドを送信
 * @param   netID  話しかけられ側ID
 * @param   seq    命令
 * @retval  none
 */
//--------------------------------------------------------------

static void _seqAskCommandSend(_TALK_WORK* pWork, int seq)
{
    _SEQ_COMMAND seqComm;

    seqComm.netID = pWork->connectIndex;
    seqComm.seq = seq;
    CommSendFixSizeData(CF_ASKSEQ_SET, &seqComm);
}

//--------------------------------------------------------------
/**
 * @brief   会話をする
 * @param   pWork  ワークポインタ
 * @param   no     会話番号
 * @retval  none
 */
//--------------------------------------------------------------

static void _talkTalk(_TALK_WORK* pWork,int no)
{
    int gmm = no;

    if(no >= msg_uw_ask_01){
        MYSTATUS* pTarget = CommInfoGetMyStatus(pWork->connectIndex);
        if(PM_FEMALE == MyStatus_GetMySex(pTarget)){
            gmm = gmm - msg_uw_ask_01 + msg_uw_ask_w01;
        }
    }
    CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(), gmm, FALSE, NULL);
}

//--------------------------------------------------------------
/**
 * @brief   会話をする
 * @param   pWork  ワークポインタ
 * @param   no     会話番号
 * @retval  none
 */
//--------------------------------------------------------------

static void _askTalk(_ASK_WORK* pWork,int no)
{
    int gmm = no;

    if(no >= msg_uw_ask_01){
        MYSTATUS* pTarget = CommInfoGetMyStatus(pWork->connectIndex);
        if(PM_FEMALE == MyStatus_GetMySex(pTarget)){
            gmm = gmm - msg_uw_ask_01 + msg_uw_ask_w01;
        }
    }
    CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(),
                           gmm, FALSE, NULL);
}

//--------------------------------------------------------------
/**
 * @brief   話しかけ側会話開始
 * @param   targetID  話しかけられ側ID
 * @param   func      終わりに呼び出したい命令
 * @param   pFSys     フィールドシステムポインタ
 * @retval  none
 */
//--------------------------------------------------------------

void CommUnderTalkInit(int targetID, pEndFunc func, FIELDSYS_WORK* pFSys)
{
    _TALK_WORK* pTalk;
    BMPLIST_HEADER list_h;

    pTalk = sys_AllocMemory(HEAPID_UNDERGROUND, sizeof(_TALK_WORK));
    MI_CpuFill8(pTalk, 0, sizeof(_TALK_WORK));
    _pTalkWork = pTalk;
    pTalk->pFSys = pFSys;
    pTalk->endfunc = func;
    pTalk->connectIndex = targetID;   // 話し相手のIDを保存
    pTalk->seq = _TALK_INIT;
    pTalk->reqSeq = _TALK_SEQ_NONE;
    pTalk->sendItem.itemType = 0;
    pTalk->sendItem.itemNo = UG_GOODS_NONE;
    pTalk->sendItem.netID = pTalk->connectIndex;

	Snd_SePlay( SEQ_SE_DP_SELECT );
    _talkTalk(pTalk, msg_underworld_01);
    pTalk->pMyTCB = TCB_Add(_mainFunc, pTalk, _MENU_UG_PRI);
}

//==============================================================================
/**
 * 話しかけのメニューを出す
 * @param   pTalk   ワークメニューポインタ
 * @retval  none
 */
//==============================================================================

static void _talkMenuInit(_TALK_WORK* pTalk)
{
    BMPLIST_HEADER list_h;

    //BMPウィンドウ生成
    pTalk->menulist = BMP_MENULIST_Create( NELEMS(MenuParamList), HEAPID_FIELD );
    GF_BGL_BmpWinAdd(pTalk->pFSys->bgl,&pTalk->win,
                     GF_BGL_FRAME3_M, 1, 1, 10, NELEMS(MenuParamList)*2, FLD_SYSFONT_PAL,
                     FLD_MSG_WIN_CGX-(10*NELEMS(MenuParamList)*2));
    BmpMenuWinWrite(&pTalk->win, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL );
	{
		MSGDATA_MANAGER* msgman;
		int i;

		msgman = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_underworld_dat, HEAPID_FIELD);
		for(i=0; i<NELEMS(MenuParamList); i++)
		{
			BMP_MENULIST_AddArchiveString( pTalk->menulist, msgman, MenuParamList[i].str_id, MenuParamList[i].param );
		}
		MSGMAN_Delete(msgman);
	}

    MI_CpuCopy8( CommMsgGetNormalBmpListHeader(), &list_h, sizeof(BMPLIST_HEADER));
    list_h.list = pTalk->menulist;
    list_h.win = &pTalk->win;
    list_h.count = NELEMS(MenuParamList);
    list_h.line = NELEMS(MenuParamList);
    
	pTalk->pos_bak = 0;
    pTalk->lw = BmpListSet(&list_h, 0, 0, HEAPID_FIELD);
    GF_BGL_BmpWinOn(&pTalk->win);
    CommPlayerHold();
    //Snd_SePlay( SEQ_SE_DP_WIN_OPEN );
}

//--------------------------------------------------------------
/**
 * @brief   話しかけ状態終了処理
 * @param   tcb			TCBへのポインタ
 * @param   pTalk		ワークデータのポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static void _talkEnd(TCB_PTR tcb, _TALK_WORK* pTalk)
{

    if(pTalk->pYesNoWork){
        BmpYesNoWinDel(pTalk->pYesNoWork,HEAPID_FIELD);
        pTalk->pYesNoWork=NULL;
    }
    if(pTalk->pStartWin){
        UgGoodsMenuForceDelete(pTalk->pStartWin, BMPLIST_CANCEL);
        UgMgrEndNowTCB();
    }
    _talkMenuEnd(tcb, pTalk);
    if(pTalk->endfunc){
        pTalk->endfunc(0);
    }
    sys_FreeMemoryEz(pTalk);
    CommPlayerHoldEnd();
    TCB_Delete(tcb);
//    sys_DeleteHeap(HEAPID_UNDERGROUND);
    _pTalkWork = NULL;
}


//==============================================================================
/**
 * 質問コーナー ジャンル選択
 * @param   pTalk   ワークメニューポインタ
 * @retval  none
 */
//==============================================================================

static void _categoryMenuInit(_TALK_WORK* pTalk)
{
    BMPLIST_HEADER list_h;

    //BMPウィンドウ生成
    pTalk->menulist = BMP_MENULIST_Create( _QUESTION_LIST_NUM, HEAPID_FIELD );
    GF_BGL_BmpWinAdd(pTalk->pFSys->bgl,&pTalk->win,
                     GF_BGL_FRAME3_M, 1, 1, 16, _QUESTION_LIST_NUM*2, FLD_SYSFONT_PAL,
                     FLD_MSG_WIN_CGX-(16*_QUESTION_LIST_NUM*2));
    BmpMenuWinWrite(&pTalk->win, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL );
	{
		MSGDATA_MANAGER* msgman;
		int i, j;
        u8 sList[_QUESTION_LIST_NUM];
		msgman = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_undersecretquestion_dat, HEAPID_FIELD);
		for(i = 0; i < _QUESTION_LIST_NUM; i++) {
            u32 rand = gf_mtRand() % _QUESTION_LIST_MAX;
            for(j = 0; j < i; j++) {
                if((sList[j] == rand)){
                    break;
                }
            }
            if(j==i){
                sList[i] = rand;
                BMP_MENULIST_AddArchiveString( pTalk->menulist, msgman,
                                               msg_uw_ask_que_01 + rand, rand );
            }
            else{
                i--;
            }
		}
		MSGMAN_Delete(msgman);
	}

    list_h = TalkMenuListHeader;
    list_h.list = pTalk->menulist;
    list_h.win = &pTalk->win;
	pTalk->pos_bak = 0;
    pTalk->lw = BmpListSet(&list_h, 0, 0, HEAPID_FIELD);
    GF_BGL_BmpWinOn(&pTalk->win);
    //Snd_SePlay( SEQ_SE_DP_WIN_OPEN );
}

//--------------------------------------------------------------
/**
 * @brief   カテゴリーを決めるメニュー実行部分
 * @param   tcb			TCBへのポインタ
 * @param   work		ワークデータのポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static BOOL _categoryMenuFunc(TCB_PTR tcb, void* work)
{
    _TALK_WORK* pTalk = work;
    u32	ret;
	u16 tmp_pos_bak;

    ret = BmpListMain(pTalk->lw);
	UgTalkListMoveSe( pTalk );

    if(CommIsError()){  // エラー時はキャンセル扱いにする
        pTalk->seq = _MSG_PLUS_TALK_END;
        _talkMenuEnd(tcb, pTalk);
        return TRUE;
    }
    switch(ret){
    case BMPLIST_CANCEL:
    case BMPLIST_NULL:
        return FALSE;
        break;
    default:
		Snd_SePlay( SEQ_SE_DP_SELECT );
        {
            _SECRET_QUESTION_COMMAND comm;
            comm.no = ret;
            comm.targetID = pTalk->connectIndex;
            comm.questionType = _QUESTION_TALK;
            CommSendFixSizeData(CF_SECRET_QUESTION, &comm);
            pTalk->list_id = ret; // メニュー項目
            pTalk->seq = _TALK_QES_CATEGORY_WAIT;
            _talkMenuEnd(tcb, pTalk);
        }
        break;
    }
    return TRUE;
}

//==============================================================================
/**
 * 質問コーナー ジャンル選択
 * @param   pAsk   ワークメニューポインタ
 * @retval  none
 */
//==============================================================================

static void _talkReturnAnswerListInit(_TALK_WORK* pTalk)
{
    BMPLIST_HEADER list_h;

    //BMPウィンドウ生成
    pTalk->menulist = BMP_MENULIST_Create( _QUESTION_LIST_NUM, HEAPID_FIELD );
    GF_BGL_BmpWinAdd(pTalk->pFSys->bgl,&pTalk->win,
                     GF_BGL_FRAME3_M, 1, 1, 16, _QUESTION_LIST_NUM*2, FLD_SYSFONT_PAL,
                     FLD_MSG_WIN_CGX-(16*_QUESTION_LIST_NUM*2));
    BmpMenuWinWrite(&pTalk->win, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL );
	{
		MSGDATA_MANAGER* msgman;
		int i;
		msgman = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_undersecretanswer_dat, HEAPID_FIELD);
		for(i = 0; i < _QUESTION_LIST_NUM; i++) {
            u32 ans = _QUESTION_LIST_NUM * pTalk->list_id + i;
			BMP_MENULIST_AddArchiveString( pTalk->menulist, msgman,
                                           msg_uw_ask_ans_01_01 + ans, i );
		}
		MSGMAN_Delete(msgman);
	}

    list_h = TalkMenuListHeader;
    list_h.list = pTalk->menulist;
    list_h.win = &pTalk->win;

	pTalk->pos_bak = 0;
    pTalk->lw = BmpListSet(&list_h, 0, 0, HEAPID_FIELD);
    GF_BGL_BmpWinOn(&pTalk->win);
    //Snd_SePlay( SEQ_SE_DP_WIN_OPEN );
}

//--------------------------------------------------------------
/**
 * @brief   カテゴリーを決めるメニュー実行部分
 * @param   tcb			TCBへのポインタ
 * @param   work		ワークデータのポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static BOOL _talkReturnAnswerListFunc(TCB_PTR tcb, void* work)
{
    _TALK_WORK* pTalk = work;
    u32	ret;
    _SECRET_QUESTION_COMMAND comm;

    ret = BmpListMain(pTalk->lw);
	UgTalkListMoveSe( pTalk );

    if(CommIsError()){  // エラー時は勝手に終了
        _talkMenuEnd(tcb, pTalk);
        pTalk->seq = _MSG_PLUS_TALK_END;
        return TRUE;
    }
    switch(ret){
    case BMPLIST_NULL:
    case BMPLIST_CANCEL:   //キャンセルが無い
        return FALSE;
    default:
		Snd_SePlay( SEQ_SE_DP_SELECT );
        _talkMenuEnd(tcb, pTalk);
        comm.no = (ret + pTalk->list_id * _QUESTION_LIST_NUM);
        comm.targetID = pTalk->connectIndex;
        comm.questionType = _ANSWER_TALK;
        CommSendFixSizeData(CF_SECRET_QUESTION , &comm);
        CommMsgRegisterSecretAnswerName(CommUnderGetMsgUnderWorld(), comm.no);
        CommMsgRegisterSecretAnswerNameIndex(CommUnderGetMsgUnderWorld(), 6, pTalk->list_ans);
        if(pTalk->list_ans == comm.no){
            // 同じ答え
            _talkTalk(pTalk, msg_uw_ask_06);
        }
        else{
            _talkTalk(pTalk, msg_uw_ask_05);
        }
        pTalk->seq = _TALK_QES_END_WAIT;
        _seqAskCommandSend(pTalk, _ASK_ANSERED_RETURN);// 
        break;
    }
    return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   アイテムをもらったメッセージを表示
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

static void _talkItemSendedTalk(_TALK_WORK* pTalk)
{
    CommMsgRegisterTargetName(CommUnderGetMsgUnderWorld(), CommInfoGetMyStatus(pTalk->connectIndex));
    CommMsgRegisterUGGoodsName(CommUnderGetMsgUnderWorld(), pTalk->sendItem.itemNo);
    CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(),
                                             msg_underworld_15 ,FALSE, NULL);
    SecretBaseRecordSetSendItemNum(SaveData_GetSecretBaseRecord(GameSystem_GetSaveData(pTalk->pFSys))); //= アイテムをあげた
    UgBagDeleteGoods(pTalk->sendItem.itemNo);
    Snd_SePlay(UG_SE_SEND_GOODS);
}

//--------------------------------------------------------------
/**
 * @brief   渡すアイテムを選択した時の
 * @param   pTalk		ワークポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static void _sendItemTalk(_TALK_WORK* pTalk, int itemNo)
{
    CommMsgRegisterUGGoodsName(CommUnderGetMsgUnderWorld(), itemNo);
    CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(),
                                             msg_underworld_13 ,FALSE, NULL);
}

//--------------------------------------------------------------
/**
 * @brief   アイテムをあげるかどうか最終確認
 * @param   pTalk		ワークポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static void _sendItemYesNoCheck(TCB_PTR tcb, _TALK_WORK* pTalk)
{
    u32	ret;
    
    ret = BmpYesNoSelectMain(pTalk->pYesNoWork, HEAPID_FIELD);
    if(ret == BMPMENU_NULL){
        return;
    }
    if(ret == 0){ // はいを選択した場合
        //相手の返事待ち
        pTalk->sendItem.netID = pTalk->connectIndex;
        CommSendFixSizeData(CF_SEND_ITEM, &pTalk->sendItem);
        pTalk->seq = _TALK_ITEM_SEND_ASK_WAIT;
    }
    else{ // いいえを選択した場合
        // あ、またこんどでもいいよー
        _talkTalk(pTalk, msg_underworld_12);
        // 相手は特に変化なし
        pTalk->seq = _TALK_WAIT_NEXT;
    }
    pTalk->pYesNoWork=NULL;
}

//--------------------------------------------------------------
/**
 * @brief   話しかけを決めるメニュー実行部分
 * @param   tcb			TCBへのポインタ
 * @param   work		ワークデータのポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static BOOL _talkMenuFunc(TCB_PTR tcb, void* work)
{
    _TALK_WORK* pTalk = work;
    u32	ret;

    ret = BmpListMain(pTalk->lw);
	UgTalkListMoveSe( pTalk );

    if(CommIsError()){  // エラー時はキャンセル扱いにする
        ret = BMPLIST_CANCEL;
    }
    switch(ret){
    case BMPLIST_NULL:
        return FALSE;
    case BMPLIST_CANCEL:
		Snd_SePlay( SEQ_SE_DP_SELECT );
        _talkExit(pTalk);
        _talkMenuEnd(tcb, pTalk);
        break;
    default:
		Snd_SePlay( SEQ_SE_DP_SELECT );
        {
            pTalkFunc func = (pTalkFunc)ret;
            func(pTalk);  // 関数ジャンプ
            _talkMenuEnd(tcb, pTalk);
        }
        break;
    }
    return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   話しかけ選択メニューリストを閉じる
 * @param   tcb			TCBへのポインタ
 * @param   pTalk		ワークポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static void _talkMenuEnd(TCB_PTR tcb, _TALK_WORK* pTalk)
{
    if(pTalk->menulist){
        BmpMenuWinClear(&pTalk->win, WINDOW_TRANS_ON );
        BmpListExit(pTalk->lw, NULL, NULL);
        GF_BGL_BmpWinOff(&pTalk->win);
        GF_BGL_BmpWinDel(&pTalk->win);
        BMP_MENULIST_Delete(pTalk->menulist);
        pTalk->menulist=NULL;
    }
}

//--------------------------------------------------------------
/**
 * @brief   会話表示スタート
 * @param   pTalk		ワークポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static void _cardStart(_TALK_WORK* pTalk)
{
    _seqAskCommandSend(pTalk, _ASK_CARD);
    _talkTalk(pTalk, msg_underworld_08);
    pTalk->seq = _TALK_CARD_WAIT;
}

//--------------------------------------------------------------
/**
 * @brief   罠設置
 * @param   pTalk		ワークポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static void _questionStart( _TALK_WORK* pTalk )
{
    _seqAskCommandSend(pTalk, _ASK_QES_START);
    pTalk->seq = _TALK_QES_CATEGORY;
}

//--------------------------------------------------------------
/**
 * @brief   アイテムあげる
 * @param   pTalk		ワークポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static void _sendItem( _TALK_WORK* pTalk )
{
    pTalk->seq = _TALK_ITEMMENU_OPEN;
}

//--------------------------------------------------------------
/**
 * @brief   グッズメニュー終了処理
 * @param   selectNo  選択したグッズの番号
 * @retval  none
 */
//--------------------------------------------------------------
static void _goodsMenuEndFunc(int selectNo)
{
    _pTalkWork->sendItem.itemNo = selectNo;
    _pTalkWork->seq = _TALK_ITEMMENU_END;
}

//--------------------------------------------------------------
/**
 * @brief   カードを見終わった際に呼ばれるコールバック
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------
static void _talkCardDispCallback(void* pWork)
{
    _TALK_WORK* pTalk = pWork;
    pTalk->seq = _TALK_CARD_DISP_FIN;
}

//--------------------------------------------------------------
/**
 * @brief   話しかけシーケンスメイン
 * @param   tcb			TCBへのポインタ
 * @param   work		ワークデータのポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static void _mainFunc(TCB_PTR tcb, void* work)
{
    _TALK_WORK* pTalk = work;
    u32	ret;

    if (pTalk->seq != _TALK_ITEMMENU_WAIT){
        if(!CommIsConnect(pTalk->connectIndex)){
            pTalk->pStartWin=NULL;  // すでに削除済み
            UnderRecordReset();
            pTalk->seq = _TALK_END;
        }
    }
    
    switch(pTalk->seq){
      case _TALK_INIT:
        if( CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0 ){
            _talkMenuInit(pTalk);
            pTalk->seq++;
        }
        break;
      case _TALK_MENU:
        _talkMenuFunc(tcb, work);
        break;
      case _MSG_PLUS_TALK_END:
      case _TALK_END:
        CommMsgTalkWindowEnd(CommUnderGetMsgUnderWorld());
        _talkEnd(tcb, pTalk);
        break;
      case _TALK_CARD_WAIT:
        // 相手の返事待ち
        if( CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0 ){
            if(pTalk->reqSeq  == _TALK_CARD_DISP){
                pTalk->seq = _TALK_CARD_DISP;
                UgRecordSendMyData(pTalk->connectIndex);
            }
            if(pTalk->reqSeq == _TALK_REJECT_CARD){
                pTalk->seq = _TALK_REJECT_CARD;
            }
        }
        break;
      case _TALK_CANCELASKER_END:
        _talkTalk(pTalk, msg_underworld_16);
        pTalk->seq = _TALK_TALKCHEKCEND;
        break;
      case _TALK_REJECT_CARD:
        _talkTalk(pTalk, msg_underworld_09);
        pTalk->seq = _TALK_TALKCHEKCEND;
        break;
      case _TALK_TALKCHEKCEND:
        if( CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0 ){
            if(PAD_BUTTON_DECIDE & sys.trg){
                pTalk->seq = _TALK_END;
            }
        }
        break;
      case _TALK_CARD_DISP:
        if(UgRecordIsTargetRecord()){
            CommMsgTalkWindowEnd(CommUnderGetMsgUnderWorld());
            UgRecordStatusListStart(pTalk->pFSys->bgl,
                                    CommInfoGetMyStatus(pTalk->connectIndex),
                                    _talkCardDispCallback,
                                    pTalk, FALSE);
            pTalk->seq = _TALK_CARD_DISP_WAIT;
        }
        break;
      case _TALK_CARD_DISP_WAIT:
        break;
      case _TALK_CARD_DISP_FIN:
        // トレーナーカード閲覧終わり
        RECORD_Score_Add(SaveData_GetRecord(pTalk->pFSys->savedata), SCORE_ID_HELLO);
        UgRecordResetTargetRecord();
        _talkTalk(pTalk, msg_underworld_10);
        pTalk->seq = _TALK_CARD_FIN_WAIT;
        break;
      case _TALK_CARD_FIN_WAIT:  // MSGEND待ち
        if( CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0 ){
            _seqAskCommandSend(pTalk, _ASK_CARD_CALLBACK_WAIT);  // 相手に終了を送信
            pTalk->seq = _TALK_CARD_CALLBACK_WAIT;
        }
        break;
      case _TALK_CARD_CALLBACK_WAIT:  // 相手からの要求待ち
        if( pTalk->reqSeq ==  _TALK_CARD_CALLBACK_WAIT){
            pTalk->seq = _TALK_NEXT;
        }
        break;
      case _TALK_NEXT:
        _talkTalk(pTalk, msg_underworld_11);  // ほかにもなにかする？
        pTalk->seq = _TALK_INIT;
        break;
      case _TALK_WAIT_NEXT:
        if( CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0 ){
            if(PAD_BUTTON_DECIDE & sys.trg){
                pTalk->seq = _TALK_NEXT;
            }
        }
        break;
      case _TALK_ITEMMENU_OPEN:
        pTalk->pStartWin = UgBagGoodsMenuStart(_goodsMenuEndFunc, pTalk->pFSys);
        pTalk->seq = _TALK_ITEMMENU_WAIT;
        break;
      case _TALK_ITEMMENU_WAIT:
        ///--------------------------------メニュー選択中 通信エラーでもひらきっぱなしで
        break;
      case _TALK_ITEMMENU_END:
        pTalk->pStartWin = NULL;
        ///-------------------------------アイテムメニューが終わったあと
        if(_pTalkWork->sendItem.itemNo == UG_GOODS_NONE){
            _talkTalk(pTalk, msg_underworld_12);
            pTalk->seq = _TALK_WAIT_NEXT;
        }
        else if(CommInfoGetMyPenalty(pTalk->connectIndex)){
            _talkTalk(pTalk, msg_underworld_87);
            pTalk->seq = _TALK_WAIT_NEXT;
        }
        else if(!UnderGroundDataIsGoodsSend(pTalk->pFSys->savedata)){
            _talkTalk(pTalk, msg_underworld_87);
            pTalk->seq = _TALK_WAIT_NEXT;
        }
        else if(GOODS_GetLear(_pTalkWork->sendItem.itemNo)){ // レアだった場合
            _talkTalk(pTalk, msg_underworld_86);
            pTalk->seq = _TALK_WAIT_NEXT;
        }
        else{
            _sendItemTalk(pTalk, _pTalkWork->sendItem.itemNo);  // アイテムをあげる事にした
            pTalk->seq = _TALK_ITEM_SEND_CHECK;
        }
        break;
      case _TALK_ITEM_SEND_CHECK:
        if( CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0 ){
            pTalk->pYesNoWork = BmpYesNoSelectInit(pTalk->pFSys->bgl,
                                                   &_yesNoBmpDat, MENU_WIN_CGX_NUM,
                                                   MENU_WIN_PAL, HEAPID_FIELD );
            pTalk->seq = _TALK_ITEM_SEND_CHECK_WAIT;
            if(pTalk->reqSeq != _TALK_CANCELASKER_END){  // 緊急停止命令は即実行
                pTalk->reqSeq = _TALK_INIT;// 初期
            }
        }
        break;
      case _TALK_ITEM_SEND_CHECK_WAIT:
        _sendItemYesNoCheck(tcb, pTalk);
        break;
      case _TALK_ITEM_SEND_ASK_WAIT:   // アイテムを相手に送信、返事待ち
        if( CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0 ){
            if(pTalk->reqSeq  == _TALK_ITEM_SEND_OK){
                pTalk->seq = _TALK_ITEM_SEND_OK;
            }
            if(pTalk->reqSeq == _TALK_ITEM_SEND_NO){
                pTalk->seq = _TALK_ITEM_SEND_NO;
            }
            if(pTalk->reqSeq == _TALK_ITEM_SEND_FULL){
                pTalk->seq = _TALK_ITEM_SEND_FULL;
            }
        }
        break;
      case _TALK_ITEM_SEND_FULL:  // どうぐがいっぱい
        _talkTalk(pTalk, msg_underworld_33);
        pTalk->seq = _TALK_ITEMEND_TIMING;
        break;
      case _TALK_ITEM_SEND_NO:  // 受け取らなかった
        _talkTalk(pTalk, msg_underworld_14);
        pTalk->seq = _TALK_ITEMEND_TIMING;
        break;
      case _TALK_ITEM_SEND_OK:  // アイテムを相手が追加した
        _talkItemSendedTalk(pTalk);
        {
            EVENTWORK* pEV = SaveData_GetEventWork( pTalk->pFSys->savedata );
            SysWork_UGToolGiveCountSet(pEV,SysWork_UGToolGiveCountGet(pEV)+1);
        }
        RECORD_Score_Add(SaveData_GetRecord(pTalk->pFSys->savedata), SCORE_ID_ITEM_DEPOSIT);
        pTalk->seq = _TALK_ITEM_SEND_OK_ZINGLE;
        break;
      case _TALK_ITEM_SEND_OK_ZINGLE:
//        if(Snd_MePlayCheckBgmPlay()==0){
            pTalk->seq = _TALK_ITEMEND_TIMING;
//        }
        break;
      case _TALK_ITEMEND_TIMING:
        if( CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0 ){
            if(pTalk->reqSeq == _TALK_WAIT_NEXT){
                pTalk->seq = _TALK_NEXT;
            }
        }
        break;
      case _TALK_QES_CATEGORY:
        _talkTalk(pTalk, msg_uw_ask_01);   // なにをききたいの？
        pTalk->seq = _TALK_QES_CATEGORY_LIST;
        break;
      case _TALK_QES_CATEGORY_LIST:
        if( CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0 ){
            _categoryMenuInit(pTalk);
            pTalk->seq = _TALK_QES_CATEGORY_LIST_WAIT;
        }
        break;
      case _TALK_QES_CATEGORY_LIST_WAIT:
        _categoryMenuFunc(tcb, work);
        break;
      case _TALK_QES_CATEGORY_WAIT:
        CommMsgRegisterSecretQuestionName(CommUnderGetMsgUnderWorld(), pTalk->list_id);
        _talkTalk(pTalk, msg_uw_ask_02);
        pTalk->seq = _TALK_QES_CATEGORY_RECV;
        break;
      case _TALK_QES_CATEGORY_RECV:  //相手待ち
        if( CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0 ){
            if( pTalk->reqSeq ==  _TALK_CATCH_ANSWER){
                pTalk->seq = _TALK_CATCH_ANSWER;
            }
        }
        break;
      case _TALK_CATCH_ANSWER:
        if(_QUESTION_LIST_CANCEL == pTalk->list_ans){
            _talkTalk(pTalk, msg_uw_ask_04);
            pTalk->reqSeq = 0;
            pTalk->seq = _TALK_WAIT_NEXT_QUES_CANCEL;
        }
        else{
            CommMsgRegisterSecretAnswerName(CommUnderGetMsgUnderWorld(), pTalk->list_ans);
            _talkTalk(pTalk, msg_uw_ask_03);
            pTalk->seq = _TALK_ANSWER_LIST_INIT;
        }
        break;
      case _TALK_WAIT_NEXT_QUES_CANCEL:
        if( CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0 ){
            if(pTalk->reqSeq == _TALK_QUES_CANCEL_STOPER){
                pTalk->reqSeq = 0;
                pTalk->seq = _TALK_NEXT;
            }
        }
        break;
      case _TALK_ANSWER_LIST_INIT:
        if( CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0 ){
            _talkReturnAnswerListInit(pTalk);
            pTalk->seq = _TALK_ANSWER_LIST_WAIT;
        }
        break;
      case _TALK_ANSWER_LIST_WAIT:
        _talkReturnAnswerListFunc(tcb, work);
        break;
      case _TALK_QES_END_WAIT:
        if( CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0 ){
            RECORD_Score_Add(SaveData_GetRecord(pTalk->pFSys->savedata), SCORE_ID_QUESTION);
            _talkTalk(pTalk, msg_uw_ask_07);
            pTalk->seq = _TALK_QES_END_WAIT2;
        }
        break;
      case _TALK_QES_END_WAIT2:
        if( CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0 ){
            if(sys.trg & PAD_BUTTON_DECIDE){
                pTalk->seq = _TALK_QES_END_WAIT25;
            }
        }
        break;
      case _TALK_QES_END_WAIT25:
        if(pTalk->reqSeq == _TALK_QES_END_WAIT2){
            _seqAskCommandSend(pTalk, _QUESTION_END_TIMING);  // 相手に終了を送信
            pTalk->seq = _TALK_QES_END_WAIT3;
        }
        break;
      case _TALK_QES_END_WAIT3:
        if(pTalk->reqSeq == _QUESTION_END_TIMING){   // 相手からの終了待ち
            _talkTalk(pTalk, msg_uw_ask_15);
            pTalk->seq = _TALK_QES_END_WAIT4;
        }
        break;
      case _TALK_QES_END_WAIT4:
        if( CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0 ){
            _seqAskCommandSend(pTalk, _QUESTION_END_TIMING2);  // 相手に終了を送信
            pTalk->seq = _TALK_QES_END_WAIT5;
        }
        break;
      case _TALK_QES_END_WAIT5:
        if(pTalk->reqSeq == _QUESTION_END_TIMING2){   // 相手からの終了待ち
            pTalk->seq = _TALK_NEXT;
        }
        break;
    }
    if(pTalk->reqSeq == _TALK_CANCELASKER_END){  // 緊急停止命令は即実行
        if((pTalk->seq == _TALK_END) || (pTalk->seq == _TALK_TALKCHEKCEND)){
            // しかし終了している最中ならば実行必要ない
            return;
        }
        if(pTalk->pYesNoWork){
            BmpYesNoWinDel(pTalk->pYesNoWork,HEAPID_FIELD);
            pTalk->pYesNoWork = NULL;
        }
        if(pTalk->pStartWin){
            UgGoodsMenuForceDelete(pTalk->pStartWin, BMPLIST_CANCEL);
            UgMgrEndNowTCB();
            CommMsgTalkWindowEnd(CommUnderGetMsgUnderItem());
            pTalk->pStartWin = NULL;
        }
        _talkMenuEnd(tcb, pTalk);
        pTalk->seq = _TALK_CANCELASKER_END;
        pTalk->reqSeq = _TALK_SEQ_NONE;
    }
}

//--------------------------------------------------------------
/**
 * @brief   会話をやめる
 * @param   pTalk		ワークポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static void _talkExit( _TALK_WORK* pTalk )
{
    _talkTalk(pTalk,msg_underworld_16);
    _seqAskCommandSend(pTalk, _ASK_CANCELTALK_END);
    pTalk->seq = _TALK_TALKCHEKCEND;
}

//--------------------------------------------------------------
/**
 * @brief   カードを見せるかどうか
 * @param   pTalk		ワークポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static void _selectCardInfoYesNoCheck(TCB_PTR tcb, _ASK_WORK* pAsk)
{
    u32	ret;
    
    ret = BmpYesNoSelectMain(pAsk->pYesNoWork, HEAPID_FIELD);
    if(ret == BMPMENU_NULL){
        return;
    }
    if(ret == 0){ // はいを選択した場合
        //地下用トレーナーケースの画面にいく
        _seqTalkCommandSend(pAsk, _TALK_CARD_DISP);
        UgRecordSendMyData(pAsk->connectIndex);// 相手にレコードを送る
        pAsk->seq = _ASK_CARD_DISP;
    }
    else{ // いいえを選択した場合
        // 自動終了
        _seqTalkCommandSend(pAsk, _TALK_REJECT_CARD);
        pAsk->seq = _ASK_CANCELTALK_END;
    }
    pAsk->pYesNoWork=NULL;
}


//--------------------------------------------------------------
/**
 * @brief   アイテムをもらうかどうか
 * @param   pTalk		ワークポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static void _recvItemYesNoCheck(TCB_PTR tcb, _ASK_WORK* pAsk)
{
    u32	ret;
    
    ret = BmpYesNoSelectMain(pAsk->pYesNoWork, HEAPID_FIELD);
    if(ret == BMPMENU_NULL){
        return;
    }
    if(ret == 0){ // はいを選択した場合      // アイテム追加
        if(CommUnderBagAddGoods(pAsk->recvItem.itemNo)){
            SecretBaseRecordSetItemRecvNum(SaveData_GetSecretBaseRecord(GameSystem_GetSaveData(pAsk->pFSys)));  // アイテムをもらった回数
            Snd_SePlay(UG_SE_SEND_GOODS);
            _seqTalkCommandSend(pAsk, _TALK_ITEM_SEND_OK);
            pAsk->seq = _ASK_ITEM_RECVED;
        }
        else{  // アイテムが入らなかった
            _seqTalkCommandSend(pAsk, _TALK_ITEM_SEND_FULL);
            _askTalk(pAsk, msg_underworld_24);
            pAsk->seq = _ASK_ITEM_RECVED_WAIT_END;
        }
    }
    else{ // いいえを選択した場合
        // 自動終了
        _seqTalkCommandSend(pAsk, _TALK_ITEM_SEND_NO);
        _askTalk(pAsk, msg_underworld_32);
        pAsk->seq = _ASK_ITEM_RECVED_WAIT_END;
    }
    pAsk->pYesNoWork=NULL;
}

//--------------------------------------------------------------
/**
 * @brief   話しかけられ状態終了処理
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

static void _askEnd(TCB_PTR tcb, _ASK_WORK* pAsk)
{
    if(pAsk->pYesNoWork){
        BmpYesNoWinDel(pAsk->pYesNoWork,HEAPID_FIELD);
        pAsk->pYesNoWork=NULL;
    }
    if(pAsk->endfunc){
        pAsk->endfunc(0);
    }
    _askMenuEnd(tcb, pAsk);
    sys_FreeMemoryEz(pAsk);
    CommPlayerHoldEnd();
    TCB_Delete(tcb);
//    sys_DeleteHeap(HEAPID_UNDERGROUND);
    _pAskWork = NULL;
}

//--------------------------------------------------------------
/**
 * @brief   話しかけ選択メニューリストを閉じる
 * @param   tcb			TCBへのポインタ
 * @param   pTalk		ワークポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static void _askMenuEnd(TCB_PTR tcb, _ASK_WORK* pAsk)
{
    if(pAsk->menulist){
        BmpMenuWinClear(&pAsk->win, WINDOW_TRANS_ON );
        BmpListExit(pAsk->lw, NULL, NULL);
        GF_BGL_BmpWinOff(&pAsk->win);
        GF_BGL_BmpWinDel(&pAsk->win);
        BMP_MENULIST_Delete(pAsk->menulist);
        pAsk->menulist=NULL;
    }
}

//--------------------------------------------------------------
/**
 * @brief   人物名をexpandしてメッセージ表示
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

static void _askNamePlusTalk(_ASK_WORK* pAsk, int targetID, int no)
{
    CommMsgRegisterTargetName(CommUnderGetMsgUnderWorld(), CommInfoGetMyStatus(targetID));
    CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(),
                           no,FALSE,NULL);
}

//--------------------------------------------------------------
/**
 * @brief   アイテムをもらったメッセージを表示
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

static void _askItemRecvedTalk(_ASK_WORK* pAsk)
{
    CommMsgRegisterTargetName(CommUnderGetMsgUnderWorld(), CommInfoGetMyStatus(pAsk->connectIndex));
    CommMsgRegisterUGGoodsName(CommUnderGetMsgUnderWorld(), pAsk->recvItem.itemNo);
    CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(),
                           msg_underworld_34 ,FALSE,NULL);

}

//==============================================================================
/**
 * 質問コーナー ジャンル選択
 * @param   pAsk   ワークメニューポインタ
 * @retval  none
 */
//==============================================================================

static void _askQuestionListInit(_ASK_WORK* pAsk)
{
    BMPLIST_HEADER list_h;

    const int menuNum = _QUESTION_LIST_NUM + 1;
    
    //BMPウィンドウ生成
    pAsk->menulist = BMP_MENULIST_Create( menuNum, HEAPID_FIELD );
    GF_BGL_BmpWinAdd(pAsk->pFSys->bgl,&pAsk->win,
                     GF_BGL_FRAME3_M, 1, 1, 16, menuNum*2, FLD_SYSFONT_PAL,
                     FLD_MSG_WIN_CGX-(16*menuNum*2));
    BmpMenuWinWrite(&pAsk->win, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL );
	{
		MSGDATA_MANAGER* msgman;
		int i;
		msgman = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_undersecretanswer_dat, HEAPID_FIELD);
		for(i = 0; i < _QUESTION_LIST_NUM; i++) {
            u32 ans = _QUESTION_LIST_NUM * pAsk->list_id + i;
			BMP_MENULIST_AddArchiveString( pAsk->menulist, msgman,
                                           msg_uw_ask_ans_01_01 + ans, i );
		}
        BMP_MENULIST_AddArchiveString( pAsk->menulist, msgman,
                                       msg_uw_ask_ans_cancel, _QUESTION_LIST_CANCEL );
		MSGMAN_Delete(msgman);
	}

    list_h = TalkMenuListHeader;
    list_h.list = pAsk->menulist;
    list_h.win = &pAsk->win;
	list_h.count = menuNum;		//リスト項目数
	list_h.line = menuNum;		//表示最大項目数
	pAsk->pos_bak = 0;
    pAsk->lw = BmpListSet(&list_h, 0, 0, HEAPID_FIELD);
    GF_BGL_BmpWinOn(&pAsk->win);
    //Snd_SePlay( SEQ_SE_DP_WIN_OPEN );
}

//--------------------------------------------------------------
/**
 * @brief   カテゴリーを決めるメニュー実行部分
 * @param   tcb			TCBへのポインタ
 * @param   work		ワークデータのポインタ
 * @retval  none
 */
//--------------------------------------------------------------

static BOOL _askQuestionListFunc(TCB_PTR tcb, void* work)
{
    _ASK_WORK* pAsk = work;
    u32	ret;
    _SECRET_QUESTION_COMMAND comm;
	u16 tmp_pos_bak;

    ret = BmpListMain(pAsk->lw);

#if 1
	//BMPリストの全体位置を取得
	tmp_pos_bak = pAsk->pos_bak;		//退避
	BmpListDirectPosGet( pAsk->lw, &pAsk->pos_bak );

	//カーソルが動いたかチェック
	if( tmp_pos_bak != pAsk->pos_bak ){
		Snd_SePlay( SEQ_SE_DP_SELECT );
	}
#endif

    if(CommIsError()){  // エラー時はキャンセル扱いにする
        ret = BMPLIST_CANCEL;
    }
    switch(ret){
    case BMPLIST_NULL:
        return FALSE;
    case BMPLIST_CANCEL:   //
        ret = _QUESTION_LIST_CANCEL;
    default:
		Snd_SePlay( SEQ_SE_DP_SELECT );
        _askMenuEnd(tcb, pAsk);
        if(ret != _QUESTION_LIST_CANCEL){
            pAsk->list_ans = (ret + pAsk->list_id * _QUESTION_LIST_NUM); // 答え項目
            pAsk->seq = _ASK_ANSWERED_WAIT;
            CommMsgRegisterSecretAnswerName(CommUnderGetMsgUnderWorld(), pAsk->list_ans);
            _askTalk(pAsk, msg_uw_ask_11);
        }
        else{
            pAsk->list_ans = _QUESTION_LIST_CANCEL;
            pAsk->seq = _ASK_WAIT_NEXT;
            pAsk->reqSeq = _ASK_SEQ_NONE;
            _askTalk(pAsk, msg_uw_ask_10);
        }
        comm.no = pAsk->list_ans;
        comm.targetID = pAsk->connectIndex;
        comm.questionType = _ANSWER_ASK;
        CommSendFixSizeData(CF_SECRET_QUESTION , &comm);
        _seqTalkCommandSend(pAsk, _TALK_CATCH_ANSWER);
        break;
    }
    return TRUE;
}


//--------------------------------------------------------------
/**
 * @brief   カードを見終わった際に呼ばれるコールバック
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------
static void _askCardDispCallback(void* pWork)
{
    _ASK_WORK* pAsk = pWork;
    pAsk->seq = _ASK_CARD_DISP_FIN;
}

//--------------------------------------------------------------
/**
 * @brief   話しかけられ状態管理
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

static void _askTask(TCB_PTR tcb, void* pWork)
{
    _ASK_WORK* pAsk = pWork;

    if(!CommIsConnect(pAsk->connectIndex)){
        UnderRecordReset();
        pAsk->seq = _ASK_END;
    }
    switch(pAsk->seq){
      case _ASK_END:
        CommMsgTalkWindowEnd(CommUnderGetMsgUnderWorld());
        _askEnd(tcb, pAsk);
        break;
      case _ASK_WAIT:
        pAsk->list_id = _QUESTION_LIST_MAX;
        if (sys.trg & PAD_BUTTON_CANCEL) {
            _seqTalkCommandSend(pAsk, _TALK_CANCELASKER_END);
            pAsk->seq = _ASK_CANCELTALK_END;
        }
        else if( pAsk->reqSeq ==  _ASK_CARD ){
            pAsk->seq = _ASK_CARD;
        }
        else if(pAsk->reqSeq ==  _ASK_QES_START ){
            pAsk->seq = _ASK_QES_START;
        }
        break;
      case _ASK_CARD:
        _askTalk(pAsk, msg_underworld_27);
        pAsk->seq = _ASK_CARD_WAIT;
        break;
      case _ASK_CARD_WAIT:
        if( CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0 ){
            pAsk->seq = _ASK_CARD_YESNO_WAIT;
            pAsk->pYesNoWork = BmpYesNoSelectInit(pAsk->pFSys->bgl,
                                                  &_yesNoBmpDat, MENU_WIN_CGX_NUM,
                                                  MENU_WIN_PAL, HEAPID_FIELD );
        }
        break;
      case _ASK_CARD_YESNO_WAIT:
        _selectCardInfoYesNoCheck(tcb, pAsk);
        break;
      case _ASK_CANCELTALK_END:
        _askTalk(pAsk, msg_underworld_16);
        pAsk->seq = _ASK_TALKCHEKCEND;
        break;
      case _ASK_TALKCHEKCEND:
        if( CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0 ){
            if(PAD_BUTTON_DECIDE & sys.trg){
                pAsk->seq = _ASK_END;
            }
        }
        break;
      case _ASK_CARD_DISP:
        if(UgRecordIsTargetRecord()){
            CommMsgTalkWindowEnd(CommUnderGetMsgUnderWorld());
            UgRecordStatusListStart(pAsk->pFSys->bgl,
                                    CommInfoGetMyStatus(pAsk->connectIndex),
                                    _askCardDispCallback,
                                    pAsk, FALSE);
            pAsk->seq = _ASK_CARD_DISP_WAIT;
        }
        break;
      case _ASK_CARD_DISP_WAIT:
        break;
      case _ASK_CARD_DISP_FIN:
        // トレーナーカード閲覧終わり
        UgRecordResetTargetRecord();
        _askNamePlusTalk(pAsk, pAsk->connectIndex, msg_underworld_29);
        pAsk->seq = _ASK_CARD_FIN_WAIT;
        break;
      case _ASK_CARD_FIN_WAIT:  // MSGEND待ち
        if( CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0 ){
            _seqTalkCommandSend(pAsk, _TALK_CARD_CALLBACK_WAIT);  // 相手に終了を送信
            pAsk->seq = _ASK_CARD_CALLBACK_WAIT;
        }
        break;
      case _ASK_CARD_CALLBACK_WAIT:  // 相手からの要求待ち
        if( pAsk->reqSeq ==  _ASK_CARD_CALLBACK_WAIT ){
            pAsk->seq = _ASK_NEXT;
        }
        break;
      case _ASK_NEXT:
        _askTalk(pAsk, msg_underworld_30);  // 後は…
        pAsk->seq = _ASK_WAIT;
        break;
      case _ASK_WAIT_NEXT:
        if( CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0 ){
            pAsk->seq = _ASK_NEXT;
            _seqTalkCommandSend(pAsk, _TALK_QUES_CANCEL_STOPER);
        }
        break;
      case _ASK_RECV_ITEM:
        if( CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0 ){
            pAsk->seq = _ASK_RECV_ITEM_YESNO_WAIT;
            pAsk->pYesNoWork = BmpYesNoSelectInit(pAsk->pFSys->bgl,
                                                  &_yesNoBmpDat, MENU_WIN_CGX_NUM,
                                                  MENU_WIN_PAL, HEAPID_FIELD );
        }
        break;
      case _ASK_RECV_ITEM_YESNO_WAIT:
        _recvItemYesNoCheck(tcb, pAsk);
        break;
      case _ASK_ITEM_RECVED:
        _askItemRecvedTalk(pAsk);
        pAsk->seq = _ASK_ITEM_RECVED_WAIT;
        break;
      case _ASK_ITEM_RECVED_WAIT:
//        if(Snd_MePlayCheckBgmPlay() == 0){
            pAsk->seq = _ASK_ITEM_RECVED_WAIT_END;
//        }
        break;
      case _ASK_ITEM_RECVED_WAIT_END:
        if( CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0 ){
            if(PAD_BUTTON_DECIDE & sys.trg){
                _seqTalkCommandSend(pAsk, _TALK_WAIT_NEXT);
                pAsk->seq = _ASK_NEXT;
            }
        }
        break;
      case _ASK_QES_START:
        _askTalk(pAsk, msg_uw_ask_08);  // ねえすこし
        pAsk->seq++;
        break;
      case _ASK_QES_RECV_WAIT:
        if( CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0 ){
            if(pAsk->list_id != _QUESTION_LIST_MAX){   // 話しかけ側のジャンルを受信していた
                CommMsgRegisterSecretQuestionName(CommUnderGetMsgUnderWorld(), pAsk->list_id);
                _askTalk(pAsk, msg_uw_ask_09); 
                pAsk->seq = _ASK_QES_CATEGORY_MSG;
            }
        }
        break;
      case _ASK_QES_CATEGORY_MSG:
        if( CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0 ){
            _askQuestionListInit( pAsk );
            pAsk->seq = _ASK_QES_ANSWER_LIST;
        }
        break;
      case _ASK_QES_ANSWER_LIST:
        _askQuestionListFunc(tcb, pAsk);   // 話しかけ側に選択結果送信
        break;
      case _ASK_ANSWERED_WAIT:
        if( CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0 ){
            if( pAsk->reqSeq ==  _ASK_ANSERED_RETURN){
                _seqTalkCommandSend(pAsk, _TALK_QES_END_WAIT2);
                pAsk->seq = _ASK_ANSERED_RETURN;
            }
        }
        break;
      case _ASK_ANSERED_RETURN:
        CommMsgRegisterSecretAnswerName(CommUnderGetMsgUnderWorld(), pAsk->list_ans2);
        CommMsgRegisterSecretAnswerNameIndex(CommUnderGetMsgUnderWorld(), 6, pAsk->list_ans);
        if(pAsk->list_ans == pAsk->list_ans2){
            _askTalk(pAsk, msg_uw_ask_13); 
        }
        else{
            _askTalk(pAsk, msg_uw_ask_12); 
        }
        pAsk->seq = _ASK_ANSERED_RETURN_WAIT;
        break;
      case _ASK_ANSERED_RETURN_WAIT:
        if( CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0 ){
            _askTalk(pAsk, msg_uw_ask_14);
            pAsk->seq = _ASK_SECRET_TALK_END;
        }
        break;
      case _ASK_SECRET_TALK_END:
        if( CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0 ){
          //  _seqTalkCommandSend(pAsk, _QUESTION_END_TIMING);  // 相手に終了を送信
            pAsk->seq = _ASK_SECRET_TALK_END2;
        }
        break;
      case _ASK_SECRET_TALK_END2:
        if(pAsk->reqSeq == _QUESTION_END_TIMING){   // 相手からの終了待ち
            _seqTalkCommandSend(pAsk, _QUESTION_END_TIMING);  // 相手に終了を送信
            _askTalk(pAsk, msg_uw_ask_15);
            pAsk->seq = _ASK_SECRET_TALK_END3;
        }
        break;
      case _ASK_SECRET_TALK_END3:
        if( CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0 ){
    //        _seqTalkCommandSend(pAsk, _QUESTION_END_TIMING2);  // 相手に終了を送信
            pAsk->seq = _ASK_SECRET_TALK_END4;
        }
        break;
      case _ASK_SECRET_TALK_END4:
        if(pAsk->reqSeq == _QUESTION_END_TIMING2){   // 相手からの終了待ち
            _seqTalkCommandSend(pAsk, _QUESTION_END_TIMING2);  // 相手に終了を送信
            pAsk->seq = _ASK_NEXT;
        }
        break;
    }
    if(pAsk->reqSeq == _ASK_CANCELTALK_END){  // 緊急停止命令は即実行
        if((pAsk->seq == _ASK_END) || (pAsk->seq == _ASK_TALKCHEKCEND)){
            // しかし終了している最中ならば実行必要ない
            return;
        }
        if(pAsk->pYesNoWork){
            BmpYesNoWinDel(pAsk->pYesNoWork,HEAPID_FIELD);
            pAsk->pYesNoWork=NULL;
        }
        _askMenuEnd(tcb, pAsk);
        pAsk->seq = _ASK_CANCELTALK_END;
        pAsk->reqSeq = _ASK_SEQ_NONE;
    }
}


//--------------------------------------------------------------
/**
 * @brief   話しかけられ状態コマンドが来た
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

void CommUnderTalkBind(int askID, int talkID, FIELDSYS_WORK* pFSys)
{
    _ASK_WORK* pAsk;

    if(_pAskWork){
        GF_ASSERT(0 && "double");
        return;
    }
    pAsk = sys_AllocMemory(HEAPID_UNDERGROUND, sizeof(_ASK_WORK));
    MI_CpuFill8(pAsk, 0, sizeof(_ASK_WORK));
    _pAskWork = pAsk;
    pAsk->pFSys = pFSys;
    pAsk->connectIndex = talkID;   // 話し相手のIDを保存
    pAsk->seq = _ASK_WAIT;
    pAsk->reqSeq = _ASK_SEQ_NONE;
    pAsk->list_id = _QUESTION_LIST_MAX;
    CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(),
                           msg_underworld_25 ,FALSE,NULL);
    CommSetForceDir();
//    CommPlayerHold();
    // 話しかけられ状態になる
    pAsk->pMyTCB = TCB_Add(_askTask, pAsk, _MENU_UG_PRI);
}

//--------------------------------------------------------------
/**
 * @brief   話しかけられのシーケンスを変更する命令が来た
 * @command CF_ASKSEQ_SET
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

void CommUnderTalkRecvAskSeq(int netID, int size, void* pData, void* pWork)
{
    CommSendFixSizeData_ServerSide(CF_ASKSEQ_SET_CALL,pData); // リダイレクト返信
}

//--------------------------------------------------------------
/**
 * @brief   話しかけのシーケンスを変更する命令が来た
 * @command CF_TALKSEQ_SET
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

void CommUnderTalkRecvTalkSeq(int netID, int size, void* pData, void* pWork)
{
    CommSendFixSizeData_ServerSide(CF_TALKSEQ_SET_CALL,pData); // リダイレクト返信
}

//--------------------------------------------------------------
/**
 * @brief   話しかけられのシーケンスを変更する命令が来た
 * @command CF_ASKSEQ_SET_CALL
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

void CommUnderTalkRecvAskSeqCall(int netID, int size, void* pData, void* pWork)
{
    _SEQ_COMMAND* pSeq = pData;

    if((CommGetCurrentID() == pSeq->netID) && (_pAskWork)){
        GF_ASSERT(size == sizeof(_SEQ_COMMAND));
        _pAskWork->reqSeq = pSeq->seq;
    }
}

//--------------------------------------------------------------
/**
 * @brief   話しかけのシーケンスを変更する命令が来た
 * @command CF_TALKSEQ_SET_CALL
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

void CommUnderTalkRecvTalkSeqCall(int netID, int size, void* pData, void* pWork)
{
    _SEQ_COMMAND* pSeq = pData;

    if((CommGetCurrentID() == pSeq->netID) && (_pTalkWork)){
        GF_ASSERT(size == sizeof(_SEQ_COMMAND));
        GF_ASSERT(_pTalkWork!=NULL);
        _pTalkWork->reqSeq = pSeq->seq;
    }
}

//--------------------------------------------------------------
/**
 * @brief   シーケンスを変更する命令のサイズ
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

int CommUnderTalkGetSeqCommandSize(void)
{
    return sizeof(_SEQ_COMMAND);
}


//--------------------------------------------------------------
/**
 * @brief   アイテムをあげる命令が来た
 * @command CF_SEND_ITEM
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

void CommUnderTalkRecvSendItem(int netID, int size, void* pData, void* pWork)
{
    CommSendFixSizeData_ServerSide(CF_SEND_ITEM_CALL,pData);
}

//--------------------------------------------------------------
/**
 * @brief   アイテムをあげる命令が来た
 * @command CF_SEND_ITEM_CALL
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

void CommUnderTalkRecvSendItemCall(int netID, int size, void* pData, void* pWork)
{
    _ASK_WORK* pAsk = _pAskWork;
    _ITEMSEND_COMMAND* pSend = pData;

    if(CommGetCurrentID() != pSend->netID){
        return;
    }
    GF_ASSERT(_pAskWork!=NULL);
    if(pAsk->seq != _ASK_WAIT){   // 待機状態でなければおかしい 同時にBを押した事が考えられる
        _seqTalkCommandSend(pAsk, _TALK_CANCELASKER_END);  // 相手に終了を送信
        pAsk->seq = _ASK_CANCELTALK_END;
        return;
    }

    pAsk->recvItem.netID = pSend->netID;
    pAsk->recvItem.itemType = pSend->itemType;
    pAsk->recvItem.itemNo = pSend->itemNo;
    pAsk->seq = _ASK_RECV_ITEM;
    
    CommMsgRegisterUGGoodsName(CommUnderGetMsgUnderWorld(), pSend->itemNo);
    CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(),
                                            msg_underworld_31 ,FALSE, NULL);
}

//--------------------------------------------------------------
/**
 * @brief   アイテムをあげる命令のサイズ
 * @param   none
 * @retval  パケットサイズ
 */
//--------------------------------------------------------------

int CommUnderTalkGetSendItemSize(void)
{
    return sizeof(_ITEMSEND_COMMAND);
}

//--------------------------------------------------------------
/**
 * @brief   秘密の質問に関する命令が来た
 * @command CF_SECRET_QUESTION
 * @param   コールバックパラメータ
 * @retval  none
 */
//--------------------------------------------------------------

void UgTalkRecvSecretQ(int netID, int size, void* pData, void* pWork)
{
    CommSendFixSizeData_ServerSide(CF_SECRET_QUESTION_CALL, pData);
}

//--------------------------------------------------------------
/**
 * @brief   秘密の質問に関する命令が来た
 * @command CF_SECRET_QUESTION_CALL
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

void UgTalkRecvSecretQCall(int netID, int size, void* pData, void* pWork)
{
    _ASK_WORK* pAsk = _pAskWork;
    _TALK_WORK* pTalk = _pTalkWork;
    _SECRET_QUESTION_COMMAND* pSQC = pData;

    if(pSQC->targetID == CommGetCurrentID()){
        switch(pSQC->questionType){
          case _QUESTION_TALK:
            pAsk->list_id = pSQC->no;  // 質問項目
            break;
          case _ANSWER_ASK:
            pTalk->list_ans = pSQC->no;  // 質問項目
            break;
          case _ANSWER_TALK:
//            if(pAsk->list_ans == pSQC->no){
  //              pAsk->list_ans = _QUESTION_LIST_BOTH;  // 質問項目
   //         }
     //       else{
                pAsk->list_ans2 = pSQC->no;
       //     }
            break;
        }
    }
}

//--------------------------------------------------------------
/**
 * @brief   秘密の質問通信サイズ
 * @param   none
 * @retval  パケットサイズ
 */
//--------------------------------------------------------------

int UgTalkGetSecretQSize(void)
{
    return sizeof(_SECRET_QUESTION_COMMAND);
}

//--------------------------------------------------------------
/**
 * @brief   会話を強制的に終わらせる
 * @param   none
 * @retval  パケットサイズ
 */
//--------------------------------------------------------------

void TalkAskForceReset(void)
{
    if(_pTalkWork){
        _talkEnd(_pTalkWork->pMyTCB,_pTalkWork);
    }
    if(_pAskWork){
        _askEnd(_pAskWork->pMyTCB,_pAskWork);
    }

}

static void UgTalkListMoveSe( _TALK_WORK* pTalk )
{
	u16 tmp_pos_bak;

	//BMPリストの全体位置を取得
	tmp_pos_bak = pTalk->pos_bak;		//退避
	BmpListDirectPosGet( pTalk->lw, &pTalk->pos_bak );

	//カーソルが動いたかチェック
	if( tmp_pos_bak != pTalk->pos_bak ){
		Snd_SePlay( SEQ_SE_DP_SELECT );
	}
	return;
}

