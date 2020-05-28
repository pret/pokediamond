//=============================================================================
/**
 * @file	ug_talk.c
 * @brief	�n����b���Ǘ�����N���X
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
//	�萔��`
//==============================================================================

#define _EVWIN_MSG_BUF_SIZE		(50*2)			//���b�Z�[�W�o�b�t�@�T�C�Y
#define _MENU_UG_PRI  (10000)   // ���j���[�̃^�X�Npriorty

#define _QUESTION_LIST_NUM   (4)   // �\�����鎿�␔
#define _QUESTION_LIST_MAX   (12)   // ����ő�
//#define _QUESTION_LIST_BOTH  (50)    // ����������I�񂾏ꍇ
#define _QUESTION_LIST_CANCEL  (51)  // ����ɓ��������Ȃ������ꍇ

#define _QUESTION_END_TIMING  (100)
#define _QUESTION_END_TIMING2  (101)


typedef enum{
    _TALK_SEQ_NONE,
    _TALK_INIT,            // �b��������
    _TALK_MENU,            // ���j���[���o�Ă���
    _MSG_PLUS_TALK_END,    // ���b�Z�[�W���o���āA��b����߂�
    _TALK_END,             // ��b����߂�
    _TALK_CARD_WAIT,       // �J�[�h�������Ă��炨���Ƒҋ@��
    _TALK_REJECT_CARD,     // �J�[�h��������̂�����
    _TALK_TALKCHEKCEND,    // ��b�̏I����҂��ďI���
    _TALK_CANCELASKER_END,  // �p��������̂ŏI������ꍇ
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
    _TALK_QES_CATEGORY,  // �J�e�S���[�I��
    _TALK_QES_CATEGORY_LIST,    // ���j���[
    _TALK_QES_CATEGORY_LIST_WAIT,  // �I��
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
    _ASK_INIT,             // �b��������ꂽ
    _ASK_WAIT,             // �b��������ꒆ
    _MSG_PLUS_ASK_END,    
    _ASK_END,
    _ASK_CARD,
    _ASK_CARD_WAIT,        // �J�[�h��������悤�v��������
    _ASK_CARD_YESNO_WAIT,
    _ASK_CANCELTALK_END,
    _ASK_TALKCHEKCEND,   // ��b�̏I����҂��ďI���
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
//	�\���̒�`
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


// �b�������󋵍\����
typedef struct{
    TCB_PTR pMyTCB;
    _START_WORK* pStartWin;
    FIELDSYS_WORK* pFSys;
    GF_BGL_BMPWIN  win;		// BMP�E�B���h�E���[�N
	BMPLIST_DATA*  menulist;
    BMPLIST_WORK*  lw;		// BMP���j���[���[�N
    BMPMENU_WORK*  pYesNoWork;
    _ITEMSEND_COMMAND sendItem;  // �󂯎��\��̃A�C�e��
    pEndFunc endfunc;
    u16 connectIndex;  // �Ȃ��e�@��INDEX
    u8 list_id;
    u8 list_ans;
    u8 waitMode;
    u8 endState;
    u8 work;
    u8 seq;        // �����̃V�[�P���X
    u8 reqSeq;     // ���肩�痈���V�[�P���X
	u16 pos_bak;
} _TALK_WORK;


static _TALK_WORK* _pTalkWork = NULL;

// �b���������󋵍\����
typedef struct{
    TCB_PTR pMyTCB;
    FIELDSYS_WORK* pFSys;
    GF_BGL_BMPWIN  win;		// BMP�E�B���h�E���[�N
	BMPLIST_DATA*  menulist;
    BMPLIST_WORK*  lw;		// BMP���j���[���[�N
    BMPMENU_WORK*  pYesNoWork;
    _ITEMSEND_COMMAND recvItem;  // �󂯎��\��̃A�C�e��
    pEndFunc endfunc;
    u16 connectIndex;  // �Ȃ��e�@��INDEX
    u8 list_id;
    u8 list_ans;
    u8 list_ans2;
    u8 waitMode;
    u8 endState;
    u8 work;
    u8 seq;        // �����̃V�[�P���X
    u8 reqSeq;     // ���肩�痈���V�[�P���X
	u16 pos_bak;
} _ASK_WORK;


static _ASK_WORK* _pAskWork = NULL;


//==============================================================================
//	�^�錾
//==============================================================================
typedef void (*pTalkFunc)(_TALK_WORK *);

//==============================================================================
//	static��`
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
//	�b���������j���[���X�g�p�f�[�^��
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

///�͂Ȃ������I�����j���[�̃��X�g
static const BMPLIST_HEADER TalkMenuListHeader = {
    NULL,			// �\�������f�[�^�|�C���^
    NULL,					// �J�[�\���ړ����Ƃ̃R�[���o�b�N�֐�
    NULL,					// ���\�����Ƃ̃R�[���o�b�N�֐�
    NULL,					// 
    NELEMS(MenuParamList),	// ���X�g���ڐ�
    NELEMS(MenuParamList),	// �\���ő區�ڐ�
    0,						// ���x���\���w���W
    8,						// ���ڕ\���w���W
    0,						// �J�[�\���\���w���W
    0,						// �\���x���W
    FBMP_COL_BLACK,			// �����F
    FBMP_COL_WHITE,			// �w�i�F
    FBMP_COL_BLK_SDW,		// �����e�F
    0,						// �����Ԋu�w
    16,						// �����Ԋu�x
    BMPLIST_LRKEY_SKIP,		// �y�[�W�X�L�b�v�^�C�v
    FONT_SYSTEM,				// �����w��
    0,						// �a�f�J�[�\��(allow)�\���t���O(0:ON,1:OFF)
    NULL,                   // ���[�N
};

//==============================================================================
//	YesNo���j���[���X�g�p�f�[�^
//==============================================================================
static const BMPWIN_DAT _yesNoBmpDat = {
    GF_BGL_FRAME3_M, FLD_YESNO_WIN_PX, FLD_YESNO_WIN_PY,
    FLD_YESNO_WIN_SX, FLD_YESNO_WIN_SY, FLD_YESNO_WIN_PAL, FLD_YESNO_WIN_CGX
    };


//==============================================================================
// �֐�
//==============================================================================

//--------------------------------------------------------------
/**
 * @brief   �b���������ɃR�}���h�𑗐M
 * @param   netID  �b��������ID
 * @param   seq    ����
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
 * @brief   �b��������ꑤ�ɃR�}���h�𑗐M
 * @param   netID  �b��������ꑤID
 * @param   seq    ����
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
 * @brief   ��b������
 * @param   pWork  ���[�N�|�C���^
 * @param   no     ��b�ԍ�
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
 * @brief   ��b������
 * @param   pWork  ���[�N�|�C���^
 * @param   no     ��b�ԍ�
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
 * @brief   �b����������b�J�n
 * @param   targetID  �b��������ꑤID
 * @param   func      �I���ɌĂяo����������
 * @param   pFSys     �t�B�[���h�V�X�e���|�C���^
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
    pTalk->connectIndex = targetID;   // �b�������ID��ۑ�
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
 * �b�������̃��j���[���o��
 * @param   pTalk   ���[�N���j���[�|�C���^
 * @retval  none
 */
//==============================================================================

static void _talkMenuInit(_TALK_WORK* pTalk)
{
    BMPLIST_HEADER list_h;

    //BMP�E�B���h�E����
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
 * @brief   �b��������ԏI������
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   pTalk		���[�N�f�[�^�̃|�C���^
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
 * ����R�[�i�[ �W�������I��
 * @param   pTalk   ���[�N���j���[�|�C���^
 * @retval  none
 */
//==============================================================================

static void _categoryMenuInit(_TALK_WORK* pTalk)
{
    BMPLIST_HEADER list_h;

    //BMP�E�B���h�E����
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
 * @brief   �J�e�S���[�����߂郁�j���[���s����
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		���[�N�f�[�^�̃|�C���^
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

    if(CommIsError()){  // �G���[���̓L�����Z�������ɂ���
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
            pTalk->list_id = ret; // ���j���[����
            pTalk->seq = _TALK_QES_CATEGORY_WAIT;
            _talkMenuEnd(tcb, pTalk);
        }
        break;
    }
    return TRUE;
}

//==============================================================================
/**
 * ����R�[�i�[ �W�������I��
 * @param   pAsk   ���[�N���j���[�|�C���^
 * @retval  none
 */
//==============================================================================

static void _talkReturnAnswerListInit(_TALK_WORK* pTalk)
{
    BMPLIST_HEADER list_h;

    //BMP�E�B���h�E����
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
 * @brief   �J�e�S���[�����߂郁�j���[���s����
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		���[�N�f�[�^�̃|�C���^
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

    if(CommIsError()){  // �G���[���͏���ɏI��
        _talkMenuEnd(tcb, pTalk);
        pTalk->seq = _MSG_PLUS_TALK_END;
        return TRUE;
    }
    switch(ret){
    case BMPLIST_NULL:
    case BMPLIST_CANCEL:   //�L�����Z��������
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
            // ��������
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
 * @brief   �A�C�e��������������b�Z�[�W��\��
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
    SecretBaseRecordSetSendItemNum(SaveData_GetSecretBaseRecord(GameSystem_GetSaveData(pTalk->pFSys))); //= �A�C�e����������
    UgBagDeleteGoods(pTalk->sendItem.itemNo);
    Snd_SePlay(UG_SE_SEND_GOODS);
}

//--------------------------------------------------------------
/**
 * @brief   �n���A�C�e����I����������
 * @param   pTalk		���[�N�|�C���^
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
 * @brief   �A�C�e���������邩�ǂ����ŏI�m�F
 * @param   pTalk		���[�N�|�C���^
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
    if(ret == 0){ // �͂���I�������ꍇ
        //����̕Ԏ��҂�
        pTalk->sendItem.netID = pTalk->connectIndex;
        CommSendFixSizeData(CF_SEND_ITEM, &pTalk->sendItem);
        pTalk->seq = _TALK_ITEM_SEND_ASK_WAIT;
    }
    else{ // ��������I�������ꍇ
        // ���A�܂�����ǂł�������[
        _talkTalk(pTalk, msg_underworld_12);
        // ����͓��ɕω��Ȃ�
        pTalk->seq = _TALK_WAIT_NEXT;
    }
    pTalk->pYesNoWork=NULL;
}

//--------------------------------------------------------------
/**
 * @brief   �b�����������߂郁�j���[���s����
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		���[�N�f�[�^�̃|�C���^
 * @retval  none
 */
//--------------------------------------------------------------

static BOOL _talkMenuFunc(TCB_PTR tcb, void* work)
{
    _TALK_WORK* pTalk = work;
    u32	ret;

    ret = BmpListMain(pTalk->lw);
	UgTalkListMoveSe( pTalk );

    if(CommIsError()){  // �G���[���̓L�����Z�������ɂ���
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
            func(pTalk);  // �֐��W�����v
            _talkMenuEnd(tcb, pTalk);
        }
        break;
    }
    return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   �b�������I�����j���[���X�g�����
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   pTalk		���[�N�|�C���^
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
 * @brief   ��b�\���X�^�[�g
 * @param   pTalk		���[�N�|�C���^
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
 * @brief   㩐ݒu
 * @param   pTalk		���[�N�|�C���^
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
 * @brief   �A�C�e��������
 * @param   pTalk		���[�N�|�C���^
 * @retval  none
 */
//--------------------------------------------------------------

static void _sendItem( _TALK_WORK* pTalk )
{
    pTalk->seq = _TALK_ITEMMENU_OPEN;
}

//--------------------------------------------------------------
/**
 * @brief   �O�b�Y���j���[�I������
 * @param   selectNo  �I�������O�b�Y�̔ԍ�
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
 * @brief   �J�[�h�����I������ۂɌĂ΂��R�[���o�b�N
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
 * @brief   �b�������V�[�P���X���C��
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		���[�N�f�[�^�̃|�C���^
 * @retval  none
 */
//--------------------------------------------------------------

static void _mainFunc(TCB_PTR tcb, void* work)
{
    _TALK_WORK* pTalk = work;
    u32	ret;

    if (pTalk->seq != _TALK_ITEMMENU_WAIT){
        if(!CommIsConnect(pTalk->connectIndex)){
            pTalk->pStartWin=NULL;  // ���łɍ폜�ς�
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
        // ����̕Ԏ��҂�
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
        // �g���[�i�[�J�[�h�{���I���
        RECORD_Score_Add(SaveData_GetRecord(pTalk->pFSys->savedata), SCORE_ID_HELLO);
        UgRecordResetTargetRecord();
        _talkTalk(pTalk, msg_underworld_10);
        pTalk->seq = _TALK_CARD_FIN_WAIT;
        break;
      case _TALK_CARD_FIN_WAIT:  // MSGEND�҂�
        if( CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0 ){
            _seqAskCommandSend(pTalk, _ASK_CARD_CALLBACK_WAIT);  // ����ɏI���𑗐M
            pTalk->seq = _TALK_CARD_CALLBACK_WAIT;
        }
        break;
      case _TALK_CARD_CALLBACK_WAIT:  // ���肩��̗v���҂�
        if( pTalk->reqSeq ==  _TALK_CARD_CALLBACK_WAIT){
            pTalk->seq = _TALK_NEXT;
        }
        break;
      case _TALK_NEXT:
        _talkTalk(pTalk, msg_underworld_11);  // �ق��ɂ��Ȃɂ�����H
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
        ///--------------------------------���j���[�I�� �ʐM�G���[�ł��Ђ炫���ςȂ���
        break;
      case _TALK_ITEMMENU_END:
        pTalk->pStartWin = NULL;
        ///-------------------------------�A�C�e�����j���[���I���������
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
        else if(GOODS_GetLear(_pTalkWork->sendItem.itemNo)){ // ���A�������ꍇ
            _talkTalk(pTalk, msg_underworld_86);
            pTalk->seq = _TALK_WAIT_NEXT;
        }
        else{
            _sendItemTalk(pTalk, _pTalkWork->sendItem.itemNo);  // �A�C�e���������鎖�ɂ���
            pTalk->seq = _TALK_ITEM_SEND_CHECK;
        }
        break;
      case _TALK_ITEM_SEND_CHECK:
        if( CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0 ){
            pTalk->pYesNoWork = BmpYesNoSelectInit(pTalk->pFSys->bgl,
                                                   &_yesNoBmpDat, MENU_WIN_CGX_NUM,
                                                   MENU_WIN_PAL, HEAPID_FIELD );
            pTalk->seq = _TALK_ITEM_SEND_CHECK_WAIT;
            if(pTalk->reqSeq != _TALK_CANCELASKER_END){  // �ً}��~���߂͑����s
                pTalk->reqSeq = _TALK_INIT;// ����
            }
        }
        break;
      case _TALK_ITEM_SEND_CHECK_WAIT:
        _sendItemYesNoCheck(tcb, pTalk);
        break;
      case _TALK_ITEM_SEND_ASK_WAIT:   // �A�C�e���𑊎�ɑ��M�A�Ԏ��҂�
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
      case _TALK_ITEM_SEND_FULL:  // �ǂ����������ς�
        _talkTalk(pTalk, msg_underworld_33);
        pTalk->seq = _TALK_ITEMEND_TIMING;
        break;
      case _TALK_ITEM_SEND_NO:  // �󂯎��Ȃ�����
        _talkTalk(pTalk, msg_underworld_14);
        pTalk->seq = _TALK_ITEMEND_TIMING;
        break;
      case _TALK_ITEM_SEND_OK:  // �A�C�e���𑊎肪�ǉ�����
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
        _talkTalk(pTalk, msg_uw_ask_01);   // �Ȃɂ����������́H
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
      case _TALK_QES_CATEGORY_RECV:  //����҂�
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
            _seqAskCommandSend(pTalk, _QUESTION_END_TIMING);  // ����ɏI���𑗐M
            pTalk->seq = _TALK_QES_END_WAIT3;
        }
        break;
      case _TALK_QES_END_WAIT3:
        if(pTalk->reqSeq == _QUESTION_END_TIMING){   // ���肩��̏I���҂�
            _talkTalk(pTalk, msg_uw_ask_15);
            pTalk->seq = _TALK_QES_END_WAIT4;
        }
        break;
      case _TALK_QES_END_WAIT4:
        if( CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0 ){
            _seqAskCommandSend(pTalk, _QUESTION_END_TIMING2);  // ����ɏI���𑗐M
            pTalk->seq = _TALK_QES_END_WAIT5;
        }
        break;
      case _TALK_QES_END_WAIT5:
        if(pTalk->reqSeq == _QUESTION_END_TIMING2){   // ���肩��̏I���҂�
            pTalk->seq = _TALK_NEXT;
        }
        break;
    }
    if(pTalk->reqSeq == _TALK_CANCELASKER_END){  // �ً}��~���߂͑����s
        if((pTalk->seq == _TALK_END) || (pTalk->seq == _TALK_TALKCHEKCEND)){
            // �������I�����Ă���Œ��Ȃ�Ύ��s�K�v�Ȃ�
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
 * @brief   ��b����߂�
 * @param   pTalk		���[�N�|�C���^
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
 * @brief   �J�[�h�������邩�ǂ���
 * @param   pTalk		���[�N�|�C���^
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
    if(ret == 0){ // �͂���I�������ꍇ
        //�n���p�g���[�i�[�P�[�X�̉�ʂɂ���
        _seqTalkCommandSend(pAsk, _TALK_CARD_DISP);
        UgRecordSendMyData(pAsk->connectIndex);// ����Ƀ��R�[�h�𑗂�
        pAsk->seq = _ASK_CARD_DISP;
    }
    else{ // ��������I�������ꍇ
        // �����I��
        _seqTalkCommandSend(pAsk, _TALK_REJECT_CARD);
        pAsk->seq = _ASK_CANCELTALK_END;
    }
    pAsk->pYesNoWork=NULL;
}


//--------------------------------------------------------------
/**
 * @brief   �A�C�e�������炤���ǂ���
 * @param   pTalk		���[�N�|�C���^
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
    if(ret == 0){ // �͂���I�������ꍇ      // �A�C�e���ǉ�
        if(CommUnderBagAddGoods(pAsk->recvItem.itemNo)){
            SecretBaseRecordSetItemRecvNum(SaveData_GetSecretBaseRecord(GameSystem_GetSaveData(pAsk->pFSys)));  // �A�C�e�������������
            Snd_SePlay(UG_SE_SEND_GOODS);
            _seqTalkCommandSend(pAsk, _TALK_ITEM_SEND_OK);
            pAsk->seq = _ASK_ITEM_RECVED;
        }
        else{  // �A�C�e��������Ȃ�����
            _seqTalkCommandSend(pAsk, _TALK_ITEM_SEND_FULL);
            _askTalk(pAsk, msg_underworld_24);
            pAsk->seq = _ASK_ITEM_RECVED_WAIT_END;
        }
    }
    else{ // ��������I�������ꍇ
        // �����I��
        _seqTalkCommandSend(pAsk, _TALK_ITEM_SEND_NO);
        _askTalk(pAsk, msg_underworld_32);
        pAsk->seq = _ASK_ITEM_RECVED_WAIT_END;
    }
    pAsk->pYesNoWork=NULL;
}

//--------------------------------------------------------------
/**
 * @brief   �b����������ԏI������
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
 * @brief   �b�������I�����j���[���X�g�����
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   pTalk		���[�N�|�C���^
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
 * @brief   �l������expand���ă��b�Z�[�W�\��
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
 * @brief   �A�C�e��������������b�Z�[�W��\��
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
 * ����R�[�i�[ �W�������I��
 * @param   pAsk   ���[�N���j���[�|�C���^
 * @retval  none
 */
//==============================================================================

static void _askQuestionListInit(_ASK_WORK* pAsk)
{
    BMPLIST_HEADER list_h;

    const int menuNum = _QUESTION_LIST_NUM + 1;
    
    //BMP�E�B���h�E����
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
	list_h.count = menuNum;		//���X�g���ڐ�
	list_h.line = menuNum;		//�\���ő區�ڐ�
	pAsk->pos_bak = 0;
    pAsk->lw = BmpListSet(&list_h, 0, 0, HEAPID_FIELD);
    GF_BGL_BmpWinOn(&pAsk->win);
    //Snd_SePlay( SEQ_SE_DP_WIN_OPEN );
}

//--------------------------------------------------------------
/**
 * @brief   �J�e�S���[�����߂郁�j���[���s����
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		���[�N�f�[�^�̃|�C���^
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
	//BMP���X�g�̑S�̈ʒu���擾
	tmp_pos_bak = pAsk->pos_bak;		//�ޔ�
	BmpListDirectPosGet( pAsk->lw, &pAsk->pos_bak );

	//�J�[�\�������������`�F�b�N
	if( tmp_pos_bak != pAsk->pos_bak ){
		Snd_SePlay( SEQ_SE_DP_SELECT );
	}
#endif

    if(CommIsError()){  // �G���[���̓L�����Z�������ɂ���
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
            pAsk->list_ans = (ret + pAsk->list_id * _QUESTION_LIST_NUM); // ��������
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
 * @brief   �J�[�h�����I������ۂɌĂ΂��R�[���o�b�N
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
 * @brief   �b����������ԊǗ�
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
        // �g���[�i�[�J�[�h�{���I���
        UgRecordResetTargetRecord();
        _askNamePlusTalk(pAsk, pAsk->connectIndex, msg_underworld_29);
        pAsk->seq = _ASK_CARD_FIN_WAIT;
        break;
      case _ASK_CARD_FIN_WAIT:  // MSGEND�҂�
        if( CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0 ){
            _seqTalkCommandSend(pAsk, _TALK_CARD_CALLBACK_WAIT);  // ����ɏI���𑗐M
            pAsk->seq = _ASK_CARD_CALLBACK_WAIT;
        }
        break;
      case _ASK_CARD_CALLBACK_WAIT:  // ���肩��̗v���҂�
        if( pAsk->reqSeq ==  _ASK_CARD_CALLBACK_WAIT ){
            pAsk->seq = _ASK_NEXT;
        }
        break;
      case _ASK_NEXT:
        _askTalk(pAsk, msg_underworld_30);  // ��́c
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
        _askTalk(pAsk, msg_uw_ask_08);  // �˂�������
        pAsk->seq++;
        break;
      case _ASK_QES_RECV_WAIT:
        if( CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0 ){
            if(pAsk->list_id != _QUESTION_LIST_MAX){   // �b���������̃W����������M���Ă���
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
        _askQuestionListFunc(tcb, pAsk);   // �b���������ɑI�����ʑ��M
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
          //  _seqTalkCommandSend(pAsk, _QUESTION_END_TIMING);  // ����ɏI���𑗐M
            pAsk->seq = _ASK_SECRET_TALK_END2;
        }
        break;
      case _ASK_SECRET_TALK_END2:
        if(pAsk->reqSeq == _QUESTION_END_TIMING){   // ���肩��̏I���҂�
            _seqTalkCommandSend(pAsk, _QUESTION_END_TIMING);  // ����ɏI���𑗐M
            _askTalk(pAsk, msg_uw_ask_15);
            pAsk->seq = _ASK_SECRET_TALK_END3;
        }
        break;
      case _ASK_SECRET_TALK_END3:
        if( CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0 ){
    //        _seqTalkCommandSend(pAsk, _QUESTION_END_TIMING2);  // ����ɏI���𑗐M
            pAsk->seq = _ASK_SECRET_TALK_END4;
        }
        break;
      case _ASK_SECRET_TALK_END4:
        if(pAsk->reqSeq == _QUESTION_END_TIMING2){   // ���肩��̏I���҂�
            _seqTalkCommandSend(pAsk, _QUESTION_END_TIMING2);  // ����ɏI���𑗐M
            pAsk->seq = _ASK_NEXT;
        }
        break;
    }
    if(pAsk->reqSeq == _ASK_CANCELTALK_END){  // �ً}��~���߂͑����s
        if((pAsk->seq == _ASK_END) || (pAsk->seq == _ASK_TALKCHEKCEND)){
            // �������I�����Ă���Œ��Ȃ�Ύ��s�K�v�Ȃ�
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
 * @brief   �b����������ԃR�}���h������
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
    pAsk->connectIndex = talkID;   // �b�������ID��ۑ�
    pAsk->seq = _ASK_WAIT;
    pAsk->reqSeq = _ASK_SEQ_NONE;
    pAsk->list_id = _QUESTION_LIST_MAX;
    CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(),
                           msg_underworld_25 ,FALSE,NULL);
    CommSetForceDir();
//    CommPlayerHold();
    // �b����������ԂɂȂ�
    pAsk->pMyTCB = TCB_Add(_askTask, pAsk, _MENU_UG_PRI);
}

//--------------------------------------------------------------
/**
 * @brief   �b���������̃V�[�P���X��ύX���閽�߂�����
 * @command CF_ASKSEQ_SET
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

void CommUnderTalkRecvAskSeq(int netID, int size, void* pData, void* pWork)
{
    CommSendFixSizeData_ServerSide(CF_ASKSEQ_SET_CALL,pData); // ���_�C���N�g�ԐM
}

//--------------------------------------------------------------
/**
 * @brief   �b�������̃V�[�P���X��ύX���閽�߂�����
 * @command CF_TALKSEQ_SET
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

void CommUnderTalkRecvTalkSeq(int netID, int size, void* pData, void* pWork)
{
    CommSendFixSizeData_ServerSide(CF_TALKSEQ_SET_CALL,pData); // ���_�C���N�g�ԐM
}

//--------------------------------------------------------------
/**
 * @brief   �b���������̃V�[�P���X��ύX���閽�߂�����
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
 * @brief   �b�������̃V�[�P���X��ύX���閽�߂�����
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
 * @brief   �V�[�P���X��ύX���閽�߂̃T�C�Y
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
 * @brief   �A�C�e���������閽�߂�����
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
 * @brief   �A�C�e���������閽�߂�����
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
    if(pAsk->seq != _ASK_WAIT){   // �ҋ@��ԂłȂ���΂������� ������B�������������l������
        _seqTalkCommandSend(pAsk, _TALK_CANCELASKER_END);  // ����ɏI���𑗐M
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
 * @brief   �A�C�e���������閽�߂̃T�C�Y
 * @param   none
 * @retval  �p�P�b�g�T�C�Y
 */
//--------------------------------------------------------------

int CommUnderTalkGetSendItemSize(void)
{
    return sizeof(_ITEMSEND_COMMAND);
}

//--------------------------------------------------------------
/**
 * @brief   �閧�̎���Ɋւ��閽�߂�����
 * @command CF_SECRET_QUESTION
 * @param   �R�[���o�b�N�p�����[�^
 * @retval  none
 */
//--------------------------------------------------------------

void UgTalkRecvSecretQ(int netID, int size, void* pData, void* pWork)
{
    CommSendFixSizeData_ServerSide(CF_SECRET_QUESTION_CALL, pData);
}

//--------------------------------------------------------------
/**
 * @brief   �閧�̎���Ɋւ��閽�߂�����
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
            pAsk->list_id = pSQC->no;  // ���⍀��
            break;
          case _ANSWER_ASK:
            pTalk->list_ans = pSQC->no;  // ���⍀��
            break;
          case _ANSWER_TALK:
//            if(pAsk->list_ans == pSQC->no){
  //              pAsk->list_ans = _QUESTION_LIST_BOTH;  // ���⍀��
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
 * @brief   �閧�̎���ʐM�T�C�Y
 * @param   none
 * @retval  �p�P�b�g�T�C�Y
 */
//--------------------------------------------------------------

int UgTalkGetSecretQSize(void)
{
    return sizeof(_SECRET_QUESTION_COMMAND);
}

//--------------------------------------------------------------
/**
 * @brief   ��b�������I�ɏI��点��
 * @param   none
 * @retval  �p�P�b�g�T�C�Y
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

	//BMP���X�g�̑S�̈ʒu���擾
	tmp_pos_bak = pTalk->pos_bak;		//�ޔ�
	BmpListDirectPosGet( pTalk->lw, &pTalk->pos_bak );

	//�J�[�\�������������`�F�b�N
	if( tmp_pos_bak != pTalk->pos_bak ){
		Snd_SePlay( SEQ_SE_DP_SELECT );
	}
	return;
}

