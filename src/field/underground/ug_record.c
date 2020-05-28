//=============================================================================
/**
 * @file	ug_record.c
 * @brief	�n���̋L�^��ۑ�����N���X
 * @author	k.ohno
 * @date    2006.01.31
 */
//=============================================================================

#include "common.h"
#include "ug_manager.h"

#include "system/bmp_list.h"
#include "system/fontproc.h"
#include "system/window.h"
#include "system/snd_tool.h"
#include "system/wordset.h"



#include "../fld_bmp.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_uwstatus.h"
#include "msgdata/msg_uwpersonal.h"

#include "savedata/undergrounddata.h"
#include "savedata/record.h"

// �b�������󋵍\����
typedef struct{
    UgRecordEndCallBack pFunc;
    void* pCallBackWork;
    GF_BGL_BMPWIN  win;		// BMP�E�B���h�E���[�N
	BMPLIST_DATA*  menulist;
    BMPLIST_WORK*  lw;		// BMP���j���[���[�N
    pEndFunc endfunc;
    u16 connectIndex;  // �Ȃ��e�@��INDEX
    int msgIndex;
} _TALK_WORK;



typedef struct _UNDER_RECORD {
    _TALK_WORK* pTalk;
    TCB_PTR pTCB;
    SAVEDATA* pSaveData;
    SB_RECORD_DATA* pMyData;
    SB_RECORD_DATA* pTargetData;
    MATHRandContext32 sRand;
    u8 bTargetIn;
};


static UNDER_RECORD* _pUnderRecord = NULL;
static void _talkDelele(TCB_PTR tcb, void* work);

#define _MAX  (999999)   // �l�̍ő�


//==============================================================================
/**
 * ������
 * @param   heapArea
 * @retval  none
 */
//==============================================================================

void UnderRecordInitialize(UNDER_RECORD* pRecord, SB_RECORD_DATA* pMyRec, SAVEDATA* pSaveData)
{
    MI_CpuFill8(pRecord, 0, sizeof(UNDER_RECORD));
    _pUnderRecord = pRecord;

    _pUnderRecord->pSaveData = pSaveData;
    _pUnderRecord->pMyData = pMyRec;
    _pUnderRecord->pTargetData = SecretBaseRecord_AllocWork(HEAPID_COMMUNICATION);
    CommRandSeedInitialize(&_pUnderRecord->sRand);
}

//==============================================================================
/**
 * �J��
 * @param   heapArea
 * @retval  none
 */
//==============================================================================

void UnderRecordFinalize(void)
{
    sys_FreeMemoryEz(_pUnderRecord->pTargetData);
    sys_FreeMemoryEz(_pUnderRecord);
    _pUnderRecord = NULL;
}

//==============================================================================
/**
 * ���R�[�h���j���[�̃��Z�b�g
 * @param   none
 * @retval  none
 */
//==============================================================================

void UnderRecordReset(void)
{
    if(_pUnderRecord->pTCB){
        _talkDelele(_pUnderRecord->pTCB,_pUnderRecord->pTalk);
    }
}

//==============================================================================
/**
 * �Ό@��̕��A����
 * @param   none
 * @retval  none
 */
//==============================================================================

void UnderRecordReboot(void)
{
}

//==============================================================================
/**
 * ���[�N�T�C�Y��Ԃ�
 * @param   none
 * @retval  size
 */
//==============================================================================

int UnderRecordGetWorkSize(void)
{
    return sizeof(UNDER_RECORD);
}

//---------------------------------------------
//   
//---------------------------------------------


//==============================================================================
/**
 * �X�e�[�^�X���   �����\��
 * @param   none
 * @retval  none
 */
//==============================================================================


typedef int(*NumGetFunc)(const SB_RECORD_DATA* pSBRecord);

static NumGetFunc funcTbl[]={
    SecretBaseRecordGetPoint,
    SecretBaseRecordGetTalkNum,
    SecretBaseRecordGetSendItemNum,
    SecretBaseRecordGetFlagDeliveryNum,
    SecretBaseRecordGetStoneNum,
    SecretBaseRecordGetFossilNum,
    SecretBaseRecordGetTrapConquerNum,
// �����܂Ł@�ꗗ�Ƌ���

    SecretBaseRecordGetTrapTumbleNum,
    SecretBaseRecordGetTrapRescueNum,
    SecretBaseRecordGetItemRecvNum,
    SecretBaseRecordGetFlagStealNum,
    SecretBaseRecordGetFlagReverseNum,
    SecretBaseRecordGetRelocateNum,
    SecretBaseRecordGetFlagDeliveryNum,

};


static void _statusListMessage(GF_BGL_BMPWIN* pWin, MSGDATA_MANAGER* msgman,
                               MYSTATUS* pMyStatus, const SB_RECORD_DATA* pRecord)
{
    WORDSET* pWordSet;
    STRBUF* pBuf1;
    STRBUF* pBuf2;
    int i,ans;
    const int _HEAD_UP = 17;
    const int _STATE_UP = 39;
    const int _HEAD_LEFT = 2;
    const int _HEIGHT = 16;
    const int _COLON = 55;
    const int _ID = 130;
    const int _ID_NUM = 146;
    const int _NUMBER = 146;
    

    pWordSet = WORDSET_Create(HEAPID_FIELD);
    pBuf1 = STRBUF_Create( 30, HEAPID_FIELD);
    pBuf2 = STRBUF_Create( 30, HEAPID_FIELD);


    MSGMAN_GetString( msgman, mes_uw_status_01, pBuf1 );   // ���傤����
    GF_STR_PrintSimple(pWin, FONT_SYSTEM, pBuf1, _HEAD_LEFT, 1, MSG_NO_PUT, NULL);

    MSGMAN_GetString( msgman, mes_uw_status_02, pBuf1 );   // ���傤����
    GF_STR_PrintSimple(pWin, FONT_SYSTEM, pBuf1, _HEAD_LEFT, _HEAD_UP, MSG_NO_PUT, NULL);

    MSGMAN_GetString( msgman, mes_uw_status_04, pBuf1 );   // �F
    GF_STR_PrintSimple(pWin, FONT_SYSTEM, pBuf1, _HEAD_LEFT + _COLON, 1, MSG_NO_PUT, NULL);
    MSGMAN_GetString( msgman, mes_uw_status_03, pBuf1 );   // id
    GF_STR_PrintSimple(pWin, FONT_SYSTEM, pBuf1, _HEAD_LEFT + _ID, 1, MSG_NO_PUT, NULL);
    MSGMAN_GetString( msgman, mes_uw_status_04, pBuf1 );   // �F
    GF_STR_PrintSimple(pWin, FONT_SYSTEM, pBuf1, _HEAD_LEFT + _COLON, _HEAD_UP, MSG_NO_PUT, NULL);

    WORDSET_RegisterNumber(pWordSet, 6,
                           MyStatus_GetID_Low(pMyStatus), 5,
                           NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT);
    MSGMAN_GetString( msgman, mes_uw_status_06, pBuf1 );   // idnum
    WORDSET_ExpandStr(pWordSet, pBuf2, pBuf1 );
    GF_STR_PrintSimple(pWin, FONT_SYSTEM, pBuf2, _HEAD_LEFT+_NUMBER,
                       1, MSG_NO_PUT, NULL);


    WORDSET_RegisterPlayerName( pWordSet, 0, pMyStatus);
    MSGMAN_GetString( msgman, mes_uw_status_05, pBuf1 );   //�Ȃ܂�
    WORDSET_ExpandStr(pWordSet, pBuf2, pBuf1 );
    GF_STR_PrintSimple(pWin, FONT_SYSTEM, pBuf2, _HEAD_LEFT + _COLON, 1, MSG_NO_PUT, NULL);

    i = SecretBaseRecordGetFlagType(pRecord);
    MSGMAN_GetString( msgman, mes_uw_status_21+i, pBuf1 );   //���傤����
    GF_STR_PrintSimple(pWin, FONT_SYSTEM, pBuf1, _HEAD_LEFT + _COLON, _HEAD_UP, MSG_NO_PUT, NULL);

    
    for(i = 0;i < 7;i++){
        MSGMAN_GetString( msgman, mes_uw_status_07+i, pBuf1 );   // �����ۂ����
        GF_STR_PrintSimple(pWin, FONT_SYSTEM, pBuf1, _HEAD_LEFT,
                           _STATE_UP+_HEIGHT*i, MSG_NO_PUT, NULL);
    }

    for(i = 0;i < 7;i++){
        NumGetFunc func = funcTbl[i];
        ans = func(pRecord);
        WORDSET_RegisterNumber(pWordSet, 6,
                               ans, 6,
                               NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT);
        MSGMAN_GetString( msgman, mes_uw_status_14, pBuf1 );   // �����ۂ���Ɛ�
        WORDSET_ExpandStr(pWordSet, pBuf2, pBuf1 );
        
        GF_STR_PrintSimple(pWin, FONT_SYSTEM, pBuf2, _HEAD_LEFT+_NUMBER,
                           _STATE_UP+_HEIGHT*i, MSG_NO_PUT, NULL);
    }

    
    STRBUF_Delete(pBuf1);
    STRBUF_Delete(pBuf2);
    WORDSET_Delete(pWordSet);
}

//--------------------------------------------------------------
/**
 * @brief   �b�������V�[�P���X���C��
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		���[�N�f�[�^�̃|�C���^
 * @retval  none
 */
//--------------------------------------------------------------

static void _talkDelele(TCB_PTR tcb, void* work)
{
    _TALK_WORK* pTalk = work;

    BmpMenuWinClear(&pTalk->win, WINDOW_TRANS_ON );
    GF_BGL_BmpWinOff(&pTalk->win);
    GF_BGL_BmpWinDel(&pTalk->win);
    {
        UgRecordEndCallBack func = pTalk->pFunc;
        if(func != NULL)
            func(pTalk->pCallBackWork);
    }
    sys_FreeMemoryEz(pTalk);
    TCB_Delete(tcb);
    _pUnderRecord->pTCB = NULL;
    _pUnderRecord->pTalk = NULL;
}


static void _talkFunc(TCB_PTR tcb, void* work)
{
    _TALK_WORK* pTalk = work;

    if(sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL)){
        _talkDelele(tcb,work);
    }
}

//==============================================================================
/**
 * �X�e�[�^�X���
 * @param   none
 * @retval  none
 */
//==============================================================================

void UgRecordStatusListStart(GF_BGL_INI* bgl, MYSTATUS* pMyStatus,
                             UgRecordEndCallBack pFunc,void* pWork,BOOL bMyRecord)
{
    SB_RECORD_DATA* pRecord;
    MSGDATA_MANAGER* msgman;
    BMPLIST_HEADER list_h;
    int winHeight = 10;
    _TALK_WORK* pTalk = sys_AllocMemory(HEAPID_FIELD, sizeof(_TALK_WORK));
    MI_CpuClear8(pTalk,sizeof(_TALK_WORK));
    
    pTalk->pFunc = pFunc;
    pTalk->pCallBackWork = pWork;
    //BMP�E�B���h�E����
//    pTalk->menulist = BMP_MENULIST_Create( 1, HEAPID_FIELD );
    GF_BGL_BmpWinAdd(bgl, &pTalk->win,
                     GF_BGL_FRAME3_M, 4, 2, 24, 19, FLD_SYSFONT_PAL,
                     1);//FLD_MSG_WIN_CGX - (10 * 28  * 3));
    BmpMenuWinWrite(&pTalk->win, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL );
    msgman = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_uwstatus_dat, HEAPID_FIELD);

	GF_BGL_BmpWinDataFill( &pTalk->win, FBMP_COL_WHITE );
//    GF_BGL_BmpWinOn(&pTalk->win);

    if(bMyRecord){
        pRecord = _pUnderRecord->pMyData;
    }
    else{
        pRecord = _pUnderRecord->pTargetData;
    }
    _statusListMessage(&pTalk->win, msgman, pMyStatus, pRecord);

    GF_BGL_BmpWinOnVReq( &pTalk->win );

    Snd_SePlay( SEQ_SE_DP_WIN_OPEN );

    _pUnderRecord->pTCB = TCB_Add(_talkFunc, pTalk, 10);
    _pUnderRecord->pTalk = pTalk;
    MSGMAN_Delete(msgman);
}

//==============================================================================
/**
 * �X�e�[�^�X��ʐM�ő���
 * @param   targetID   �����
 * @retval  none
 */
//==============================================================================

void UgRecordSendMyData(int targetID)
{
    int size = SecretBaseRecord_GetWorkSize();
    int score = RECORD_Score_Get(SaveData_GetRecord(_pUnderRecord->pSaveData));
    u8* pData = sys_AllocMemory(HEAPID_FIELD, size + 1);
    
    MI_CpuClear8(pData,size+1);
    pData[0] = targetID;
    if(score >= _MAX)	score = _MAX;
    SecretBaseRecordSetPoint(_pUnderRecord->pMyData, score);
    MI_CpuCopy8( _pUnderRecord->pMyData, &pData[1], size);
    CommSendData(CF_TARGET_RECORD, pData, size + 1);
    sys_FreeMemoryEz(pData);
}

//==============================================================================
/**
 * �X�e�[�^�X�̃X�R�A��n��̂��̂����
 * @param   targetID   �����
 * @retval  none
 */
//==============================================================================

void UgRecordUpdateMyData(void)
{
    int score = RECORD_Score_Get(SaveData_GetRecord(_pUnderRecord->pSaveData));
    if(score >= _MAX)	score = _MAX;
    SecretBaseRecordSetPoint(_pUnderRecord->pMyData, score);
}

//==============================================================================
/**
 * �ʐM�ł�������X�e�[�^�X�𑊎��ɍđ�  CF_TARGET_RECORD
 * @param   �R�[���o�b�N����
 * @retval  none
 */
//==============================================================================

void UgRecordRecvTargetData(int netID, int size, void* pData, void* pWork)
{
    CommSendData_ServerSide(CF_TARGET_RECORD_CALL, pData, size);
}

//==============================================================================
/**
 * �ʐM�ł�������X�e�[�^�X���i�[  CF_TARGET_RECORD_CALL
 * @param   �R�[���o�b�N����
 * @retval  none
 */
//==============================================================================

void UgRecordRecvTargetDataCall(int netID, int size, void* pData, void* pWork)
{
    u8* pBuff = pData;

    if(pBuff[0] == CommGetCurrentID()){
        MI_CpuCopy8( &pBuff[1], _pUnderRecord->pTargetData, size-1);
        _pUnderRecord->bTargetIn = TRUE;
    }
}

//==============================================================================
/**
 * �ʐM�ŃX�e�[�^�X���󂯎�������ǂ����𒲂ׂ�
 * @param   none
 * @retval  �󂯎���Ă�����TRUE
 */
//==============================================================================

BOOL UgRecordIsTargetRecord(void)
{
    return _pUnderRecord->bTargetIn;
}

//==============================================================================
/**
 * �ʐM�ŃX�e�[�^�X���󂯎�����t���O�����Z�b�g����
 * @param   none
 * @retval  none
 */
//==============================================================================

void UgRecordResetTargetRecord(void)
{
    _pUnderRecord->bTargetIn= FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   ���b�Z�[�W�������\�������ꍇ�̏I�����R�[���o�b�N
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

static void _msgEndCallBack(int num)
{
    CommPlayerHoldEnd();
}

//==============================================================================
/**
 * �����_���Ƀ��R�[�h���e��\������
 * @param   none
 * @retval  none
 */
//==============================================================================

void UgRecordGoodsMessage(SB_RECORD_DATA* pRec, int messageNo)
{
    s32 num;
    SB_RECORD_DATA* pCopyRec;
    NumGetFunc func = funcTbl[messageNo - mes_uw_status_33];

    GF_ASSERT(messageNo >= mes_uw_status_33);
    GF_ASSERT(messageNo <= mes_uw_status_46);

    CommPlayerHold();
    CommMsgChangeMSGMAN(CommUnderGetMsgUnderShop(),NARC_msg_uwstatus_dat, MSGMAN_TYPE_DIRECT);

    pCopyRec = SecretBaseRecord_AllocWork(HEAPID_FIELD);  // �A���C�����g�����낦�邽�߂̑Ώ�
    MI_CpuCopy8(pRec,pCopyRec,SecretBaseRecord_GetWorkSize());
    num = func(pCopyRec);
    sys_FreeMemoryEz(pCopyRec);

    CommMsgRegisterNumber6(CommUnderGetMsgUnderShop(), num);
    CommMsgTalkWindowStart(CommUnderGetMsgUnderShop(), messageNo, TRUE, _msgEndCallBack);
}


static void _flagListMessage(GF_BGL_BMPWIN* pWin, MSGDATA_MANAGER* msgman,
                             MYSTATUS* pMyStatus, const SB_RECORD_DATA* pRecord,
                             const UNDERGROUNDDATA* pUGData)
{
    WORDSET* pWordSet;
    STRBUF* pBuf1;
    STRBUF* pBuf2;
    int i,ans;
    const int _HEAD_UP = 17;
    const int _STATE_UP = 39;
    const int _HEAD_LEFT = 2;
    const int _HEIGHT = 17;
    const int _COLON = 55;
    const int _ID = 130;
    const int _ID_NUM = 146;
    const int _NUMBER = 100;
    

    pWordSet = WORDSET_Create(HEAPID_FIELD);
    pBuf1 = STRBUF_Create( 40, HEAPID_FIELD);
    pBuf2 = STRBUF_Create( 40, HEAPID_FIELD);

    WORDSET_RegisterPlayerName( pWordSet, 1, pMyStatus);
    MSGMAN_GetString( msgman, mes_uw_pers_08, pBuf1 );  // ������������
    WORDSET_ExpandStr(pWordSet, pBuf2, pBuf1 );
    GF_STR_PrintSimple(pWin, FONT_SYSTEM, pBuf2, _HEAD_LEFT, 1, MSG_NO_PUT, NULL);
    
    MSGMAN_GetString( msgman, mes_uw_pers_09, pBuf1 );   //�Ƃ����͂��̂���
    GF_STR_PrintSimple(pWin, FONT_SYSTEM, pBuf1, _HEAD_LEFT , 1+_HEIGHT, MSG_NO_PUT, NULL);

    WORDSET_RegisterNumber(pWordSet, 6,
                           SecretBaseRecordGetFlagDeliveryNum(pRecord), 6,
                           NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT);
    MSGMAN_GetString( msgman, mes_uw_pers_10, pBuf1 );   // ��
    WORDSET_ExpandStr(pWordSet, pBuf2, pBuf1 );
    GF_STR_PrintSimple(pWin, FONT_SYSTEM, pBuf2, _HEAD_LEFT+100,1+_HEIGHT, MSG_NO_PUT, NULL);

    MSGMAN_GetString( msgman, mes_uw_pers_11, pBuf1 );   // ��������@�Ƃ����n�^
    GF_STR_PrintSimple(pWin, FONT_SYSTEM, pBuf1, _HEAD_LEFT, 1+_HEIGHT*3, MSG_NO_PUT, NULL);

    for(i = 0;i < 5;i++){
        MYSTATUS* pMyFlag = UnderGroundGetFlag(pUGData, HEAPID_FIELD, i);
        if(pMyFlag){
            WORDSET_RegisterPlayerName( pWordSet, 0, pMyFlag);
            MSGMAN_GetString( msgman, mes_uw_pers_12, pBuf1 );   //�Ȃ܂�
            WORDSET_ExpandStr(pWordSet, pBuf2, pBuf1 );
            GF_STR_PrintSimple(pWin, FONT_SYSTEM, pBuf2, _HEAD_LEFT, 1+_HEIGHT*(4+i), MSG_NO_PUT, NULL);

            WORDSET_RegisterNumber(pWordSet, 5,
                                   MyStatus_GetID_Low(pMyFlag), 5,
                                   NUMBER_DISPTYPE_ZERO, NUMBER_CODETYPE_DEFAULT);
            MSGMAN_GetString( msgman, mes_uw_pers_17, pBuf1 );   // ID
            WORDSET_ExpandStr(pWordSet, pBuf2, pBuf1 );
        
            GF_STR_PrintSimple(pWin, FONT_SYSTEM, pBuf2, _HEAD_LEFT+_NUMBER,
                               1+_HEIGHT*(4+i), MSG_NO_PUT, NULL);
            sys_FreeMemoryEz(pMyFlag);
        }
        else{
            MSGMAN_GetString( msgman, mes_uw_pers_58, pBuf1 );   //�Ȃ܂�
            GF_STR_PrintSimple(pWin, FONT_SYSTEM, pBuf1, _HEAD_LEFT, 1+_HEIGHT*(4+i), MSG_NO_PUT, NULL);
            MSGMAN_GetString( msgman, mes_uw_pers_59, pBuf1 );   // ID
            GF_STR_PrintSimple(pWin, FONT_SYSTEM, pBuf1, _HEAD_LEFT+_NUMBER, 1+_HEIGHT*(4+i), MSG_NO_PUT, NULL);
        }
    }
    
    STRBUF_Delete(pBuf1);
    STRBUF_Delete(pBuf2);
    WORDSET_Delete(pWordSet);
}

//==============================================================================
/**
 * �l���������
 * @param   none
 * @retval  none
 */
//==============================================================================

void* UgRecordFlagListStart(GF_BGL_INI* bgl, MYSTATUS* pMyStatus,UNDERGROUNDDATA* pUGData,
                            UgRecordEndCallBack pFunc,void* pWork)
{
    SB_RECORD_DATA* pRecord;
    MSGDATA_MANAGER* msgman;
    BMPLIST_HEADER list_h;
    int winHeight = 10;
    _TALK_WORK* pTalk = sys_AllocMemory(HEAPID_FIELD, sizeof(_TALK_WORK));
    MI_CpuClear8(pTalk,sizeof(_TALK_WORK));
    
    pTalk->pFunc = pFunc;
    pTalk->pCallBackWork = pWork;
    //BMP�E�B���h�E����
//    pTalk->menulist = BMP_MENULIST_Create( 1, HEAPID_FIELD );
    GF_BGL_BmpWinAdd(bgl, &pTalk->win,
                     GF_BGL_FRAME3_M, 4, 2, 24, 19, FLD_SYSFONT_PAL,
                     1);//FLD_MSG_WIN_CGX - (10 * 28  * 3));
    BmpMenuWinWrite(&pTalk->win, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL );
    msgman = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_uwpersonal_dat, HEAPID_FIELD);

	GF_BGL_BmpWinDataFill( &pTalk->win, FBMP_COL_WHITE );
//    GF_BGL_BmpWinOn(&pTalk->win);

    pRecord = _pUnderRecord->pMyData;
    _flagListMessage(&pTalk->win, msgman, pMyStatus, pRecord, pUGData );
    Snd_SePlay( SEQ_SE_DP_WIN_OPEN );

    GF_BGL_BmpWinOnVReq( &pTalk->win );

//    TCB_Add(_talkFunc, pTalk, 10);
    MSGMAN_Delete(msgman);
    return pTalk;
}



//--------------------------------------------------------------
/**
 * @brief   ������\���I��
 * @param   work		���[�N�f�[�^�̃|�C���^
 * @retval  none
 */
//--------------------------------------------------------------

void UgRecordFlagListEnd(void* work)
{
    _TALK_WORK* pTalk = work;

    BmpMenuWinClear(&pTalk->win, WINDOW_TRANS_ON );
    GF_BGL_BmpWinOff(&pTalk->win);
    GF_BGL_BmpWinDel(&pTalk->win);
    {
        UgRecordEndCallBack func = pTalk->pFunc;
        if(func != NULL)
            func(pTalk->pCallBackWork);
    }
    sys_FreeMemoryEz(pTalk);
}

