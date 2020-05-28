//=============================================================================
/**
 * @file	ug_message.c
 * @brief	�n���p ���b�Z�[�W���ȒP�Ɉ������߂̃N���X
 * @author	k.ohno
 * @date    2006.03.25
 */
//=============================================================================


//---------------------------------------------------------
// include 
//---------------------------------------------------------
#include "common.h"
#include "communication/communication.h"
#include "system/window.h"      //TalkWinGraphicSet etc..
#include "system/wordset.h"				//WORDSET_ExpandStr
#include "system/fontproc.h"  // FONT_TALK
#include "system/arc_util.h"
#include "system/snd_tool.h"

#include "ug_message.h"

#include "msgdata/msg_communication.h"
#include "msgdata/msg.naix"
#include "system/pmfprint.h"

extern void CommUnderAllMsgForceDel(void);

#define PRINTTASK_MAX (8)

//---------------------------------------------------------
// typedef
//---------------------------------------------------------
typedef struct _COMM_MESSAGE{
    STRBUF* pStrBuf;
    STRBUF* pExpStrBuf;
    GF_BGL_BMPWIN win;		// BMP�E�B���h�E���[�N

    GF_BGL_INI* bgl;
    PTRCommMsgCallback pCallBackFunc;
    TCB_PTR pWinTask;
    MSGDATA_MANAGER* msg_man;
    WORDSET* pWordSet;
    int msgManagerNo;
    int msgIndex;
    int heapID;
    int speed;
//    int type;
    int callbackNum;
    BOOL bTalkMenuDisp:1;
    BOOL bExpand:1;
    BOOL bMeStart:1;
};

#define _MSG_BUF_SIZE   (230)
#define _TALK_WINDOW_PRI (100)


#define _TALK_TARGET_INDEX_WORK (0)  ///< ��b�f�[�^�@�b�����ID�̈ʒu
#define _TALK_MY_INDEX_WORK     (1)  ///< ��b�f�[�^�@�b���Ă���ID�̈ʒu
#define _UGITEM_INDEX_WORK      (2)   ///< �A�C�e��
#define _UGTRAP_INDEX_WORK      (3)   ///< trap
#define _SECRET_QUESTION_WORK   (5)  ///< �閧�̎���
#define _SECRET_ANSWER_WORK   (5)  ///< �閧�̓���
#define _UNDER_GOODS_WORK   (2)    /// �O�b�Y

static void _talkWindowEnd(COMM_MESSAGE* pComm, BOOL bClear);

///�I�����j���[�̃��X�g�x�[�X
static const BMPLIST_HEADER MenuListHeader = {
    NULL,			// �\�������f�[�^�|�C���^
    NULL,					// �J�[�\���ړ����Ƃ̃R�[���o�b�N�֐�
    NULL,					// ���\�����Ƃ̃R�[���o�b�N�֐�
    NULL,					// 
    0,	// ���X�g���ڐ�
    0,	// �\���ő區�ڐ�
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

const BMPLIST_HEADER* CommMsgGetNormalBmpListHeader(void)
{
    return &MenuListHeader;
}

//---------------------------------------------------------
// function
//---------------------------------------------------------

//--------------------------------------------------------------
/**
 * @brief   ������
 * @param   msgManagerNo ���b�Z�[�W�f�[�^�ԍ�
 * @param   heapID �g�p����HEAP
 * @param   GF_BGL_INI* bgl  bgl�|�C���^
 * @param   speed
 * @param   type
 * @retval  COMM_MESSAGE�|�C���^
 */
//--------------------------------------------------------------

COMM_MESSAGE* CommMsgInitialize(int msgManagerNo,int heapID, GF_BGL_INI* bgl,
                                int speed, int msgSize)
{
    int size = msgSize;
    COMM_MESSAGE* pComm = sys_AllocMemory( heapID,sizeof(COMM_MESSAGE));

    MI_CpuClear8(pComm,sizeof(COMM_MESSAGE));
    if(0==size){
        size = _MSG_BUF_SIZE;
    }
    pComm->pStrBuf = STRBUF_Create( size, heapID );
    pComm->pExpStrBuf = STRBUF_Create( size, heapID );
    pComm->pWordSet = WORDSET_Create(heapID);

	// ���b�Z�[�W�}�l�[�W���쐬
    pComm->msgManagerNo = msgManagerNo;
	pComm->msg_man = MSGMAN_Create(
        MSGMAN_TYPE_DIRECT, ARC_MSG, msgManagerNo, heapID );
    pComm->heapID = heapID;
    pComm->bgl = bgl;
//    pComm->win = win;
    GF_BGL_BmpWinInit( &pComm->win );		// BMP�E�B���h�E���[�N
    pComm->bTalkMenuDisp = FALSE;
    pComm->bExpand = FALSE;
    pComm->pWinTask = NULL;
    pComm->speed = speed;
//    pComm->type = WINTYPE_01;
    
    return pComm;
}

//--------------------------------------------------------------
/**
 * @brief   �J������
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

void CommMsgFinalize(COMM_MESSAGE* pComm)
{
    STRBUF_Delete(pComm->pStrBuf);
    STRBUF_Delete(pComm->pExpStrBuf);
    WORDSET_Delete(pComm->pWordSet);
	MSGMAN_Delete(pComm->msg_man);
    sys_FreeMemoryEz(pComm);
}

//--------------------------------------------------------------
/**
 * @brief   MSGMANAGER�ύX
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

void CommMsgChangeMSGMAN(COMM_MESSAGE* pComm, int msgManagerNo, int type)
{
    if(pComm->msgManagerNo != msgManagerNo){
        pComm->msgManagerNo = msgManagerNo;
        MSGMAN_Delete(pComm->msg_man);
        pComm->msg_man = MSGMAN_Create(
            type, ARC_MSG, msgManagerNo, pComm->heapID );
        GF_ASSERT(pComm->msg_man != NULL);
    }
}

//--------------------------------------------------------------
/**
 * @brief   bgl��ύX����
 * @param   void
 * @retval  MSGDATA_MANAGER*
 */
//--------------------------------------------------------------

void CommMsgSetBgl(COMM_MESSAGE* pComm,GF_BGL_INI* bgl)
{
    pComm->bgl = bgl;
}



//--------------------------------------------------------------
/**
 * @brief   ���b�Z�[�W�}�l�[�W���[�𓾂�
 * @param   void
 * @retval  MSGDATA_MANAGER*
 */
//--------------------------------------------------------------

MSGDATA_MANAGER* CommMsgGetMsgManager(COMM_MESSAGE* pComm)
{
    return pComm->msg_man;
}

//--------------------------------------------------------------
/**
 * @brief   ��b�E�C���h�E�\����
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   pTalk		��b�\���̂̃|�C���^
 * @retval  none
 */
//--------------------------------------------------------------

static void _talkWindowFunc(TCB_PTR tcb, void* work)
{
    COMM_MESSAGE* pComm = work;
    
//    if(pComm->bMeStart){
//        if(Snd_MePlayCheckBgmPlay() != 0){
  //      return;
//        }
    //}
    if(pComm->msgIndex < PRINTTASK_MAX){
        if( GF_MSG_PrintEndCheck( pComm->msgIndex ) != 0 ){
            return;
        }
    }
    if( sys.trg & PAD_BUTTON_DECIDE ){
        CommMsgTalkWindowEnd(pComm);
    }
}

//--------------------------------------------------------------
/**
 * @brief   ��b���o�b�t�@�ɓ��ꂻ�̃o�b�t�@��RETURN����
 * @param   pComm  COMM_MESSAGE
 * @param   msgNo  ��b�ԍ�
 * @retval  none
 */
//--------------------------------------------------------------

static STRBUF* _expandStrBuf(COMM_MESSAGE* pComm)
{
    STRBUF* pStr = pComm->pStrBuf;

    if(pComm->bExpand){
        WORDSET_ExpandStr( pComm->pWordSet, pComm->pExpStrBuf, pComm->pStrBuf );
        pStr = pComm->pExpStrBuf;
        pComm->bExpand = FALSE;
    }
    return pStr;
}

//--------------------------------------------------------------
/**
 * @brief   ��b�E�C���h�E�\��
 * @param   pComm  COMM_MESSAGE�|�C���^
 * @param   bTask  �^�X�N�ŏI�����Ǘ�����ꍇTRUE
 * @param   pEndCallBack �I�����ɌĂԃR�[���o�b�N
 * @retval  �E�C���h�E�C���f�b�N�X
 */
//--------------------------------------------------------------

static int _talkStart(COMM_MESSAGE* pComm, BOOL bTask, PTRCommMsgCallback pEndCallBack, int callbackNum)
{
    STRBUF* pStr;


    _talkWindowEnd(pComm, FALSE);
    CommUnderAllMsgForceDel();
    //BMP�E�B���h�E����
    if(!GF_BGL_BmpWinAddCheck(&pComm->win)){
        GF_BGL_BmpWinAdd(pComm->bgl, &pComm->win,
                         GF_BGL_FRAME3_M,
                         COMM_MSG_WIN_PX, COMM_MSG_WIN_PY,
                         COMM_MSG_WIN_SX, COMM_MSG_WIN_SY,
                         COMM_MESFONT_PAL, COMM_MSG_WIN_CGX);
    }
    
    GF_BGL_BmpWinDataFill(&pComm->win, 15 );
    BmpTalkWinWrite(&pComm->win, WINDOW_TRANS_OFF,COMM_TALK_WIN_CGX_NUM, COMM_MESFRAME_PAL );

    if(bTask){
        pComm->pWinTask = TCB_Add(_talkWindowFunc, pComm, _TALK_WINDOW_PRI);
    }
    pComm->bTalkMenuDisp = TRUE;
    pComm->bMeStart = FALSE;
    pStr = _expandStrBuf(pComm);

//	MsgPrintSkipFlagSet(MSG_SKIP_ON);
//	MsgPrintAutoFlagSet(MSG_AUTO_ON);
    pComm->msgIndex = GF_STR_PrintSimple(&pComm->win, FONT_TALK,
                                         pStr, 0, 0, pComm->speed, NULL);
    pComm->pCallBackFunc = pEndCallBack;
    pComm->callbackNum = callbackNum;
    return pComm->msgIndex;
}


//--------------------------------------------------------------
/**
 * @brief   ��b���o�b�t�@�ɓ��ꂻ�̃o�b�t�@��RETURN����
 * @param   pComm  COMM_MESSAGE
 * @param   msgNo  ��b�ԍ�
 * @retval  none
 */
//--------------------------------------------------------------

STRBUF* CommMsgGetExpandStrBuf(COMM_MESSAGE* pComm, int msgNo)
{
    MSGMAN_GetString( pComm->msg_man, msgNo, pComm->pStrBuf );
    return _expandStrBuf(pComm);
}

//--------------------------------------------------------------
/**
 * @brief   ��b�E�C���h�E�\��
 * @param   msgNo  ��b�ԍ�
 * @param   bgl  GF_BGL_INI* 
 * @param   bTask  �L�[�������^�X�N�ɔC���Ď����I�����邩�ǂ���
 * @param   pEndCallBack  �I�����ɃR�[���o�b�N���ĂԂ��ǂ���
 * @retval  none
 */
//--------------------------------------------------------------
int CommMsgTalkWindowStart(COMM_MESSAGE* pComm, int msgNo, BOOL bTask, PTRCommMsgCallback pEndCallBack)
{
    MSGMAN_GetString( pComm->msg_man, msgNo, pComm->pStrBuf );
    return _talkStart(pComm, bTask,  pEndCallBack, 0);
}

//--------------------------------------------------------------
/**
 * @brief   ��b�E�C���h�E�ꊇ�\��
 * @param   msgNo  ��b�ԍ�
 * @param   bgl  GF_BGL_INI* 
 * @param   bTask  �L�[�������^�X�N�ɔC���Ď����I�����邩�ǂ���
 * @param   pEndCallBack  �I�����ɃR�[���o�b�N���ĂԂ��ǂ���
 * @retval  none
 */
//--------------------------------------------------------------
int CommMsgTalkWindowAllWrite(COMM_MESSAGE* pComm, int msgNo, BOOL bTask, PTRCommMsgCallback pEndCallBack)
{
    int ret,speed;
    speed = pComm->speed;
    pComm->speed = MSG_ALLPUT;
    ret = CommMsgTalkWindowStart(pComm, msgNo,  bTask, pEndCallBack);
    pComm->msgIndex = PRINTTASK_MAX;
    pComm->speed = speed;
    return ret;
}

//--------------------------------------------------------------
/**
 * @brief   ��b�E�C���h�E�\�� �������R�[���o�b�N�ɓn��
 * @param   msgNo  ��b�ԍ�
 * @param   bgl  GF_BGL_INI* 
 * @param   bTask  �L�[�������^�X�N�ɔC���Ď����I�����邩�ǂ���
 * @param   pEndCallBack  �I�����ɃR�[���o�b�N���ĂԂ��ǂ���
 * @param   callbackNum �R�[���o�b�N�ɓn������
 * @retval  none
 */
//--------------------------------------------------------------
int CommMsgTalkWindowStartSendNum(COMM_MESSAGE* pComm, int msgNo, BOOL bTask, PTRCommMsgCallback pEndCallBack,
                           int callbackNum)
{
    MSGMAN_GetString( pComm->msg_man, msgNo, pComm->pStrBuf );
    return _talkStart(pComm, bTask,  pEndCallBack, callbackNum);
}

//--------------------------------------------------------------
/**
 * @brief   ME�̏I�����R�[���o�b�N�ő҂ꍇ�Ă�
 * @param   COMM_MESSAGE  ���b�Z�[�W�n���h��
 * @retval  �E�C���h�E�C���f�b�N�X
 */
//--------------------------------------------------------------

void CommMsgTalkWindowMeWait(COMM_MESSAGE* pComm)
{
    pComm->bMeStart = TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   ��b�E�C���h�E����  ���p����
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

static void _talkWindowEnd(COMM_MESSAGE* pComm, BOOL bClear)
{
    if(pComm->bTalkMenuDisp){
        pComm->bTalkMenuDisp = FALSE;

        if((pComm->msgIndex < PRINTTASK_MAX) && (GF_MSG_PrintEndCheck(pComm->msgIndex))){
            GF_STR_PrintForceStop(pComm->msgIndex);
        }
        if(TRUE == bClear){
            BmpTalkWinClear(&pComm->win, WINDOW_TRANS_ON );
            GF_BGL_BmpWinOff(&pComm->win);
            GF_BGL_BmpWinDel(&pComm->win);
        }
        else{
            BmpTalkWinClear(&pComm->win, WINDOW_TRANS_OFF );
        }
        pComm->msgIndex = PRINTTASK_MAX;
        if(pComm->pWinTask != NULL){
            TCB_Delete(pComm->pWinTask);
            pComm->pWinTask = NULL;
        }
        if(pComm->pCallBackFunc){
            PTRCommMsgCallback func = pComm->pCallBackFunc;
            func(pComm->callbackNum);
        }
    }
}

//--------------------------------------------------------------
/**
 * @brief   ��b�E�C���h�E����
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

void CommMsgTalkWindowEnd(COMM_MESSAGE* pComm)
{
    _talkWindowEnd(pComm, TRUE);
}


void CommMsgRegisterMyName(COMM_MESSAGE* pComm, MYSTATUS* pMy)
{
    WORDSET_RegisterPlayerName( pComm->pWordSet, _TALK_MY_INDEX_WORK, pMy);
    pComm->bExpand = TRUE;
}

void CommMsgRegisterTargetName(COMM_MESSAGE* pComm,MYSTATUS* pTarget)
{
    WORDSET_RegisterPlayerName( pComm->pWordSet, _TALK_TARGET_INDEX_WORK, pTarget);
    pComm->bExpand = TRUE;
}

void CommMsgRegisterUGItemName(COMM_MESSAGE* pComm,int type)
{
    WORDSET_RegisterUGItemName(pComm->pWordSet, _UGITEM_INDEX_WORK, type );
    pComm->bExpand = TRUE;
}

void CommMsgRegisterUGTrapName(COMM_MESSAGE* pComm,int type)
{
    WORDSET_RegisterUGTrapName(pComm->pWordSet, _UGTRAP_INDEX_WORK, type );
    pComm->bExpand = TRUE;
}

void CommMsgRegisterSecretQuestionName(COMM_MESSAGE* pComm,int type)
{
    WORDSET_RegisterSecretQuestion(pComm->pWordSet, _SECRET_QUESTION_WORK, type );
    pComm->bExpand = TRUE;
}

void CommMsgRegisterSecretAnswerName(COMM_MESSAGE* pComm,int type)
{
    WORDSET_RegisterSecretAnswer(pComm->pWordSet, _SECRET_ANSWER_WORK, type );
    pComm->bExpand = TRUE;
}

void CommMsgRegisterSecretAnswerNameIndex(COMM_MESSAGE* pComm,int index,int type)
{
    WORDSET_RegisterSecretAnswer(pComm->pWordSet, index, type );
    pComm->bExpand = TRUE;
}

void CommMsgRegisterUGGoodsName(COMM_MESSAGE* pComm,int type)
{
    WORDSET_RegisterUGGoodsName(pComm->pWordSet, _UNDER_GOODS_WORK, type );
    pComm->bExpand = TRUE;
}

void CommMsgRegisterNumber1Index(COMM_MESSAGE* pComm,int index,int num)
{
    WORDSET_RegisterNumber(pComm->pWordSet, index, num, 1,
                           NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT);
    pComm->bExpand = TRUE;
}

void CommMsgRegisterNumber2(COMM_MESSAGE* pComm,int num)
{
    WORDSET_RegisterNumber(pComm->pWordSet, 6, num, 2,
                           NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT);
    pComm->bExpand = TRUE;
}

void CommMsgRegisterNumber2Index(COMM_MESSAGE* pComm,int index,int num)
{
    WORDSET_RegisterNumber(pComm->pWordSet, index, num, 2,
                           NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT);
    pComm->bExpand = TRUE;
}

void CommMsgRegisterNumber5(COMM_MESSAGE* pComm,int num)
{
    WORDSET_RegisterNumber(pComm->pWordSet, 6, num, 5,
                           NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT);
    pComm->bExpand = TRUE;
}

void CommMsgRegisterNumber6(COMM_MESSAGE* pComm,int num)
{
    WORDSET_RegisterNumber(pComm->pWordSet, 6, num, 6,
                           NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT);
    pComm->bExpand = TRUE;
}

void CommMsgRegisterUGItemNameIndex(COMM_MESSAGE* pComm,int index,int type)
{
    WORDSET_RegisterUGItemName(pComm->pWordSet, index, type );
    pComm->bExpand = TRUE;
}

void CommMsgRegisterUGTrapNameIndex(COMM_MESSAGE* pComm,int index,int type)
{
    WORDSET_RegisterUGTrapName(pComm->pWordSet, index, type );
    pComm->bExpand = TRUE;
}

void CommMsgRegisterUGGoodsNameIndex(COMM_MESSAGE* pComm,int index,int type)
{
    WORDSET_RegisterUGGoodsName(pComm->pWordSet, index, type );
    pComm->bExpand = TRUE;
}


void CommMsgPrintStop(COMM_MESSAGE* pComm)
{
   if(pComm->msgIndex < PRINTTASK_MAX){
       if(GF_MSG_PrintEndCheck(pComm->msgIndex)){
           GF_STR_PrintForceStop(pComm->msgIndex);
           pComm->msgIndex = PRINTTASK_MAX;
       }
   }
}


//--------------------------------------------------------------
/**
 * @brief   ��b�E�C���h�E���o�͒����ǂ���
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

BOOL CommMsgIsOutputing(COMM_MESSAGE* pComm)
{
    if(pComm->msgIndex == PRINTTASK_MAX){
        return FALSE;
    }
    return GF_MSG_PrintEndCheck(pComm->msgIndex);
}

//--------------------------------------------------------------
/**
 * @brief   ��b�E�C���h�E����
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

void CommMsgFunc(COMM_MESSAGE* pComm)
{
   if((pComm->msgIndex < PRINTTASK_MAX) && (!GF_MSG_PrintEndCheck(pComm->msgIndex))){
       pComm->msgIndex = PRINTTASK_MAX;
   }
}

