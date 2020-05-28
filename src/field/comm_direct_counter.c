//=============================================================================
/**
 * @file	comm_direct_counter.c
 * @bfief	�ʐM�_�C���N�g�R�[�i�[�̃J�E���^�[
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
// extern�錾
//==============================================================================

#include "comm_direct_counter.h"

//==============================================================================
// ��`
//==============================================================================

/// ID�𕶎���ɂ����ꍇ�̒���
#define _ID_STR_LENGTH   (5)
/// ID���o�b�t�@�ɓ���鎞�Ɂ{����l 10�͑��߂ɐݒ�
#define _ID_STR_BUFF_LENGTH   (_ID_STR_LENGTH + 10 + EOM_SIZE)
// �؂̎��N���b�V���ő�l���ŏ����Ă���
#define _DIRECT_CORNER_CREATURE_MAX (5)
// �\������e�@���X�g
#define _DISP_SCAN_PARENT_COUNT_MAX (5)

// �e�@�I���̃��X�g����
#define _PARENT_MENU_LIST_WIDTH (20)
// �q�@�\�����X�g�̉���
#define _CHILD_MENU_LIST_WIDTH (17)
// �\������q�@���X�g
#define _DISP_CONNECT_CHILD_COUNT_MAX (6)

#define _EVWIN_MSG_BUF_SIZE		(70 * GLOBAL_MSGLEN)			//���b�Z�[�W�o�b�t�@�T�C�Y
#define _STRBUF_TEMP_ELEMENTS_NUM (8)

#define _CGX_COUNTER_TOP_NUM (1)
#define _CGX_COUNTER_PSUB_NUM  (_CGX_COUNTER_TOP_NUM + _PARENT_MENU_LIST_WIDTH * _DISP_SCAN_PARENT_COUNT_MAX * 2)
#define _CGX_COUNTER_CSUB_NUM  (_CGX_COUNTER_TOP_NUM + _CHILD_MENU_LIST_WIDTH * _DISP_CONNECT_CHILD_COUNT_MAX * 2)


enum{
    _TIMING_GUESTROOM = 10,    // ������ăQ�X�g���[���ɓ���ꍇ�̃^�C�~���O�ԍ�

};


enum yesno_list_e {
    _YESNO_YES_RESULT = 2,
    _YESNO_NO_RESULT,
    _YESNO_DIFFER_REGULATION,
    _YESNO_ALL_EXIT,

};


typedef struct __INFO_WORK* _INFO_WORK_PTR;		// �V�C����f�[�^�|�C���^

typedef void (*INFO_FUNC_PTR)(_INFO_WORK_PTR pInfo);
typedef void (*STATE_FUNC_PTR)(TCB_PTR tcb, void* work);

// �󋵍\����
typedef struct __INFO_WORK{
	STRBUF* pStrBuf[_STRBUF_TEMP_ELEMENTS_NUM]; // ���b�Z�[�W���������ďo�͂���ꍇ�̊i�[�ꏊ

    GF_BGL_BMPWIN win;		 // BMP�E�B���h�E���[�N
    GF_BGL_BMPWIN subWin;	 // BMPSub�E�B���h�E���[�N
    GF_BGL_BMPWIN talkWin;   // ��b�p�E�C���h�E���[�N

    WORDSET* pWordSetMain;  //���[�h�Z�b�g�\����
    WORDSET* pWordSetSub;   //���[�h�Z�b�g�\����
    WORDSET* pWordSetTalk;  //���[�h�Z�b�g�\����

    BMPLIST_WORK* lw;		 // ���j���[���[�N�|�C���^
    BMPMENU_WORK* yesNoWork; // YesNo���j���[���[�N�|�C���^
	BMPLIST_DATA*   menulist;
    FIELDSYS_WORK* pFSys;    // �t�B�[���h�V�X�e���̃|�C���^
    STATE_FUNC_PTR pState;    // �������X�e�[�g�ŊǗ�
    INFO_FUNC_PTR pFunc;         // YesNo���j���[��Yes�I�������ꍇ�̓���
    MSGDATA_MANAGER* msg_man;   // ���b�Z�[�W�}�l�[�W���[
    MYSTATUS* pMyStatus;
    MYSTATUS* pBconStatus;
    u8 bNewInfoTrg[COMM_MACHINE_MAX];
    u32 retCode;  // �O���ɕԂ��R�[�h
    u16 curPos;              // �J�[�\���ʒu
    u16 connectIndex;
    u8 connectNum;
    u8 selectGameMode;
    u8 type1;
    u8 type2;
    u8 msgIndex;          // ���b�Z�[�W�C���f�b�N�X ���b�Z�[�W�I���҂��Ɏg�p
    u8 selectChildNetID;  // ���ݏ������̎q�@��ID
    u8 waitMsgCount;
    u8 bSubWin;              // SubWindow���g�p���Ă��邩�ǂ���
    u8 bReWrite;
} _INFO_WORK;

typedef void (*pInfoFunc)(_INFO_WORK *);




// ���j���[���ڂ̐e�@�����i�[���Ă���o�b�t�@

//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================

// �ėp��`
static void _commonFunc(TCB_PTR tcb, void* work);
static void _changeState(STATE_FUNC_PTR pState);  // �X�e�[�g��ύX����
static void _talkStart(int messageIdx, BOOL bExpand);

static void _chkFunc(TCB_PTR tcb, void* work);

// �R���V�A�����[�h�I��
static void _gameModeMatchWaitAndListCreate(TCB_PTR tcb, void* work);
static void _gameModeMatchFunc(TCB_PTR tcb, void* work);
static void _childStart(_INFO_WORK* pInfo);
static void _parentStart(_INFO_WORK* pInfo);

static void	_parentMenuListCursor(BMPLIST_WORK * wk,u32 param,u8 mode);
static void _parentMenuListLineCallBackAllPrint(BMPLIST_WORK * wk,u32 param,u8 y);
static void _parentMenuListLineCallBack(BMPLIST_WORK * wk,u32 param,u8 y);

// ���[�h�I������
static void _exit(_INFO_WORK* pInfo);
static void _chkFuncExit(TCB_PTR tcb, void* work);

// �q�@���e�@��I��������
static void _selectParentWindowOpen(_INFO_WORK* pInfo);
static void _myNameAndIDDisp(_INFO_WORK* pInfo);
static void _selectParentListWaitAndListCreate(TCB_PTR tcb, void* work);
static void _selectParentListFunc(TCB_PTR tcb, void* work);
static void _selectParentSetName(_INFO_WORK* pInfo);
static void _selectParentExec(TCB_PTR tcb, void* work);

static void _waitWindowFunc(TCB_PTR tcb, void* work);
static void _selectParentCancelYesNoCheck1(TCB_PTR tcb, void* work);
static void _selectParentCancelYesNoCheck(TCB_PTR tcb, void* work);


// �e�@���q�@�ڑ���҂��Ă�����
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

// �����Ɉē����郁�b�Z�[�W
static void _pleaseGuestRoomStart(_INFO_WORK* pInfo);

// �Q�[�����[�h�ɂ��ő�A�ŏ��l���𓾂�
static int _getMaxPlayNum(void);
static int _getMinPlayNum(void);
// ���M�����[�V�����l�𓾂�
static int _getRegulationNo(void);
   

static _INFO_WORK* _pInfo = NULL;  // ���̊֐��̎��̂����|�C���^

// ���j���[���^�X�N�ɓo�^���Ă����ۂ̃v���C�I���e�B�[
// �d�˂邲�Ƃɂ�����悤�ɂ��邽�ߒ�`���Ă���
enum menuTaskPri_e {
    _TCB_PRI_TOP = 0,
    _MENU_TALK_PRI = _TCB_PRI_TOP,
    _MENU_SELECT_PARENT_PRI = 0,
    _MENU_WAIT_PRI = 0,
    _MENU_CHILD_LIST_PRI = 0,
    _PARENT_CONNECT_OK_PRI = 0
};

#define _TCB_COMMCHECK_PRT   (10)    ///< �t�B�[���h������ʐM�̊Ď����[�`����PRI

// ���΂炭����Ƒҋ@���b�Z�[�W�ɕύX����
#define _CHILD_WAIT_MSG_CHANGE_TIME (30*3)


//==============================================================================
//	YesNo���j���[���X�g�p�f�[�^
//==============================================================================
static const BMPWIN_DAT _yesNoBmpDat = {
    FLD_MBGFRM_FONT, FLD_YESNO_WIN_PX, FLD_YESNO_WIN_PY,
    FLD_YESNO_WIN_SX, FLD_YESNO_WIN_SY, FLD_YESNO_WIN_PAL, FLD_YESNO_WIN_CGX
    };


//--------------------------------------------------------------
/**
 * @brief   �ʐM�_�C���N�g�R�[�i�[�̃J�E���^�[�p���j���[  �X�^�[�g
 * @param   pMsg �\�����b�Z�[�W
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
 * @brief   �ėp���X�g�̍쐬
 * @param   header ���X�g�w�b�_�[
 * @param   x,y   �J�n���W
 * @param   width,height  ������
 * @param   chrofs  �L�����N�^�[�������I�t�Z�b�g
 * @retval  none
 */
//--------------------------------------------------------------
static void _listCreate(BMPLIST_HEADER header,u8 x,u8 y,u8 width,u8 height,u16 chrofs)
{
    BMPLIST_HEADER list_h;
    //BMP�E�B���h�E����
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
 * @brief   �ʐM�_�C���N�g�R�[�i�[�̃J�E���^�[�p���j���[  �X�^�[�g
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

static void _infoInitialize(FIELDSYS_WORK* pFSys)
{
    int i;
    
    GF_ASSERT_RETURN((_pInfo==NULL) && "�Q�d�m�ۂ͂�������",);
    _pInfo = sys_AllocMemory(HEAPID_FIELD, sizeof(_INFO_WORK));
    MI_CpuFill8(_pInfo, 0, sizeof(_INFO_WORK));

    _pInfo->retCode = COMM_RETVAL_NULL;
    _pInfo->pFSys = pFSys;
    _pInfo->bSubWin = FALSE;

	// ���b�Z�[�W�}�l�[�W���쐬
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
 * @brief   �J������
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
 * @brief   �I������
 * @param   pInfo		���[�N�f�[�^�̃|�C���^
 * @retval  none
 */
//--------------------------------------------------------------

static void _exit(_INFO_WORK* pInfo)
{
    _pInfo->retCode = COMM_RETVAL_CANCEL;
}

//--------------------------------------------------------------
/**
 * @brief   �q�@�X�^�[�g
 * @param   pInfo		���[�N�f�[�^�̃|�C���^
 * @retval  none
 */
//--------------------------------------------------------------

static void _childStart(_INFO_WORK* pInfo)
{
    CommFieldStateEnterBattleChild(pInfo->pFSys, pInfo->selectGameMode, _getRegulationNo());
}

///�f�o�b�O���j���[�e�@�I���̃��X�g
static const BMPLIST_HEADER _parentMenuListHeader = {
    NULL,  // �\�������f�[�^�|�C���^
    _parentMenuListCursor,// �J�[�\���ړ����Ƃ̃R�[���o�b�N�֐�
    _parentMenuListLineCallBackAllPrint,// ���\�����Ƃ̃R�[���o�b�N�֐�
    NULL,                   // GF_BGL_BMPWIN* win
    SCAN_PARENT_COUNT_MAX,	// ���X�g���ڐ�
    _DISP_SCAN_PARENT_COUNT_MAX,	// �\���ő區�ڐ�
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
    NULL                    // work
};

//--------------------------------------------------------------
/**
 * @brief   �J�[�\���ړ����̃R�[���o�b�N
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

static void	_parentMenuListCursor(BMPLIST_WORK * wk,u32 param,u8 mode)
{
    _pInfo->bReWrite = TRUE;
//	_parentMenuListLineCallBackAllPrint( wk, param, mode );
//
	if( mode == 0 ){	//�������ȊO
		Snd_SePlay( SEQ_SE_DP_SELECT );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	�S���X�g��`�悵�Ȃ���
 *
 *	@param	wk		���[�N
 *	@param	param	������p�����[�^�ibmplistdata�����I�ɂ͏��XheapID�Ɏg�p���Ă���j
 *	@param	y		�x�ʒu
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
 * @brief   �e�ꗗ�̂P���C���R�[���o�b�N
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
 * @brief   �e�@��I������E�C���h�E���J��
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

static void _selectParentWindowOpen(_INFO_WORK* pInfo)
{
    int i;

    // �����̖��O�{ID�̕\��
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
 * @brief   ���O��ID��\������
 * @param   pInfo		���[�N�\���̂̃|�C���^
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

    // �����̖��O��ID�\��
    GF_STR_PrintSimple( &_pInfo->subWin, FONT_SYSTEM, _pInfo->pStrBuf[7], 2, 2, 0, NULL );


}

//--------------------------------------------------------------
/**
 * @brief   �e�@�ꗗ���j���[�̎��s����
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   pInfo		���[�N�\���̂̃|�C���^
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

			// ���X�g�̐������������Ă���
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
 * @brief   �e�@�ꗗ���j���[�̎��s����
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   pInfo		���[�N�\���̂̃|�C���^
 * @retval  none
 */
//--------------------------------------------------------------

static void _selectParentListFunc(TCB_PTR tcb, void* work)
{
    u32	ret;
    int i;
    _INFO_WORK* pInfo = (_INFO_WORK*)work;

    _myNameAndIDDisp(pInfo);

    if(CommIsError()){  // �G���[���̓L�����Z�������ɂ���
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
				//BMPList�̈ʒu����Beacon�����ۂɑ��݂���Index���擾���Ȃ���
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
 * @brief   �e�@�̖��O���E�����тɃ��j���[�ɒǉ�����
 * @param   pNet		�l�b�g���[�N�󋵍\���̂̃|�C���^
 * @retval  none
 */
//--------------------------------------------------------------

static void _selectParentSetName(_INFO_WORK* pInfo)
{
    if(CommMPIsScanListChange() || _pInfo->bReWrite){
        // �������X�g�ɍX�V���Ȃ���Ε`��ύX�����Ȃ�
        _pInfo->bReWrite = FALSE;
        CommMPResetScanChangeFlag();

//        BmpListRewrite(_pInfo->lw);
//        GF_BGL_BmpWinDataFill( &_pInfo->win, 15 );
//

		// �\���ύX����Ƃ�����N���A
		GF_BGL_BmpWinFill( &_pInfo->win, 15, 8, 0, _PARENT_MENU_LIST_WIDTH - 8, (_DISP_SCAN_PARENT_COUNT_MAX*2)*8 );

		// �S���ڕ`��
		_parentMenuListLineCallBackAllPrint(_pInfo->lw, 0, 0);
//        GF_BGL_BmpWinOnVReq(&_pInfo->win);
        GF_BGL_BmpWinOn(&_pInfo->win);
    }
}

//--------------------------------------------------------------
/**
 * @brief   �q�@�@�e�@�ɐڑ����N�G�X�g���o���āA�ҋ@���
 * @param   void
 * @retval  none
 */
//--------------------------------------------------------------
static void _selectParentExec(TCB_PTR tcb, void* work)
{
    _INFO_WORK* pInfo = (_INFO_WORK*)work;

    CommMPGetParentName(pInfo->connectIndex, _pInfo->pBconStatus);
    WORDSET_RegisterPlayerName( pInfo->pWordSetTalk, TARGET_PLAYER_WORD_IDX, _pInfo->pBconStatus);
    if(_getMinPlayNum() <= 2){  //1vs1 1on1�̏ꍇ
        _talkStart(DBCChildWait, TRUE);
    }
    else{
        _talkStart(DBCChildWaitMulti, TRUE);
    }
    _changeState(_waitWindowFunc);

}



//--------------------------------------------------------------
/**
 * @brief   �q�@�@�e�@�ɐڑ����N�G�X�g���o���āA�ҋ@��Ԃ̎��s����
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   pNet		�l�b�g���[�N�󋵍\���̂̃|�C���^
 * @retval  none
 */
//--------------------------------------------------------------

static BOOL _waitWindowCommonFunc(TCB_PTR tcb, void* work)
{
    _INFO_WORK* pInfo = work;
    
    if(CommIsError()){  // �G���[���͐e�@�I���ɖ߂�
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
        // �e�@���烌�M�����[�V�����ᔽ���󂯂�
        _talkStart(DBCDifferRule, FALSE);
        _changeState(_regulationDiffer);
    }
    else if( CommListGet(COMM_PARENT_ID , _YESNO_YES_RESULT) == CommGetCurrentID() ){
        CommListReset();
        // �e�@����YES����M
        pInfo->connectNum = CommInfoGetEntryNum();
        if(!FldTalkMsgEndCheck(_pInfo->msgIndex)){
            GF_STR_PrintForceStop(_pInfo->msgIndex);
        }
        _listEnd(tcb, pInfo);
        _startChildConnectOK(pInfo);
    }
    else if(CommRecvIsExit()){     // �S���ۂ��ꂽ�ꍇ
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
 * @brief   �q�@�@�e�@�ɐڑ����N�G�X�g���o���āA�ҋ@��Ԃ̎��s����
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   pNet		�l�b�g���[�N�󋵍\���̂̃|�C���^
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
    else if(PAD_BUTTON_CANCEL & sys.trg){  // �Q������߂邩�ǂ����₢���킹
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
        // �͂��������E�C���h�E���o��
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
    if(ret == 0){ // �͂���I�������ꍇ
        _listEnd(tcb, pInfo);
        _talkStart(DBCMemberCancel, FALSE);
        _startChildConnectReset(pInfo);
    }
    else if(ret != BMPMENU_NULL){ // ��������I�������ꍇ
 //       _talkStart(DBCChildWait, FALSE);
        _changeState(_selectParentExec);
    }

}

///�f�o�b�O���j���[�e�@�I���̃��X�g
static const BMPLIST_HEADER _childListHeader = {
    NULL,  // �\�������f�[�^�|�C���^
    NULL,					// �J�[�\���ړ����Ƃ̃R�[���o�b�N�֐�
    NULL,					// ���\�����Ƃ̃R�[���o�b�N�֐�
    NULL,                   // win
    _DIRECT_CORNER_CREATURE_MAX,	// ���X�g���ڐ�
    _DIRECT_CORNER_CREATURE_MAX,	// �\���ő區�ڐ�
    0,						// ���x���\���w���W
    1,						// ���ڕ\���w���W
    0,						// �J�[�\���\���w���W
    0,						// �\���x���W
    FBMP_COL_BLACK,			// �����F
    FBMP_COL_WHITE,			// �w�i�F
    FBMP_COL_BLK_SDW,		// �����e�F
    0,						// �����Ԋu�w
    16,						// �����Ԋu�x
    BMPLIST_LRKEY_SKIP,		// �y�[�W�X�L�b�v�^�C�v
    FONT_SYSTEM,				// �����w��
    1,						// �a�f�J�[�\��(allow)�\���t���O(0:ON,1:OFF)
    NULL                    //work
};

//--------------------------------------------------------------
/**
 * @brief   �e�ꗗ�̈ꃉ�C���R�[���o�b�N
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
    //_childListWindowOpen(pInfo);  // �ڑ����Ă���q�@���X�g��\��
}

//--------------------------------------------------------------
/**
 * @brief   ����ؒf
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
 * �Ǘ��X�e�[�g�̕ύX
 * @param   state  �ς���X�e�[�g�̊֐�
 * @param   time   �X�e�[�g�ێ�����
 * @retval  none
 */
//==============================================================================

static void _changeState(STATE_FUNC_PTR pState)
{
    _pInfo->pState = pState;
}

//--------------------------------------------------------------
/**
 * @brief   �ڑ�����q�@�ꗗ�E�C���h�E���J��
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

static void _childListWindowOpen(_INFO_WORK* pInfo)
{
    int i;

    TCB_Add(_commonFunc, pInfo, _MENU_CHILD_LIST_PRI);
    _childListStartMessage();
    
    // ���ƁH�ɂ�̕\��
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

    // �����̃f�[�^�𑗐M
    //CommInfoSendPokeData();
    CommInfoSetEntry(0);// �����͂��łɎ�t����

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
 * @brief   �l���̕\��
 * @param   pInfo		���[�N�\���̂̃|�C���^
 * @retval  none
 */
//--------------------------------------------------------------

static void _numDisp(_INFO_WORK* pInfo)
{
    int msgno,num;

    // �l���\��
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
    // �Q�[�����[�h�ɂ��킹���Z���t�ꗗ
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
 * @brief   �e�@�ꗗ���j���[�̎��s����
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   pInfo		���[�N�\���̂̃|�C���^
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
 * @brief   ���b�Z�[�W���o����A�q�@���X�g���o��
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   pInfo		���[�N�\���̂̃|�C���^
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
 * @brief   �q�@���X�g��\�����Ă���
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   pInfo		���[�N�\���̂̃|�C���^
 * @retval  none
 */
//--------------------------------------------------------------

static void _childListSelectFunc(TCB_PTR tcb, void* work)
{
    _INFO_WORK* pInfo = (_INFO_WORK*)work;
    u32	ret = BMPLIST_NULL;
    int i;

    _numDisp(pInfo);

    for(i = 0;i < COMM_MACHINE_MAX;i++){  // mustatus����
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
        BmpListRewrite(_pInfo->lw); // �E�C���h�E�ĕ`��
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
    if(CommIsError()){  // �G���[���̓L�����Z�������ɂ���
        // ����ؒf
        _commDisconnect();
        _listEnd(tcb, pInfo);
        _pInfo->retCode = COMM_RETVAL_ERROR;
    }
    else{
        switch(ret){
          case BMPLIST_NULL:
            break;
          case BMPLIST_CANCEL:  // �߂�
            _changeState(_childListBCancelCheck);
            break;
          default:   // �Œ�l���ɒB���Ă�����J�n�̊m�F
            if(_getMinPlayNum() <= CommInfoGetEntryNum()){  // �Œ�ڑ��l���ɒB����
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
 * @brief   �͂��A�������E�C���h�E���o�����򂷂�
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   pInfo		���[�N�\���̂̃|�C���^
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
    if(!CommIsConnect(pInfo->selectChildNetID)){   //�Q�����~
        if(ret == BMPMENU_NULL){
            BmpYesNoWinDel(pInfo->yesNoWork, HEAPID_FIELD);
        }
        if(pInfo->selectGameMode == COMM_MODE_CONTEST){  // �R���e�X�g�Ɍ������͖���
            for(i = 1 ; i < _getMaxPlayNum() ; i++){
                if(CommIsConnect(i)){
                    CommInfoDeletePlayer( i ); // �o�^������
                    CommListSet(_YESNO_ALL_EXIT, i);
                }
            }
            _talkStart(DBCConnectError, FALSE);
            _changeState(_waitAndChildListSelect2);
        }
        else{
            CommInfoDeletePlayer( pInfo->selectChildNetID ); // �o�^������
            _talkStart(DBCConnectError, FALSE);
            _changeState(_waitAndChildListSelect2);
        }
    }
    else if(CommIsError() ||   // �G���[���̓L�����Z�������ɂ���
       CommRecvIsExit()){   // �q�@�������ۂ��Ă���
        if(ret == BMPMENU_NULL){
            BmpYesNoWinDel(pInfo->yesNoWork, HEAPID_FIELD);
        }
        CommInfoDeletePlayer( pInfo->selectChildNetID ); // �o�^������
        _talkStart(DBCConnectError, FALSE);
        _changeState(_waitAndChildListSelect2);
    }
    else if(ret == 0){ // �͂���I�������ꍇ

        if((pInfo->selectGameMode == COMM_MODE_BATTLE_SINGLE) ||
           (pInfo->selectGameMode == COMM_MODE_BATTLE_DOUBLE)){
            if(!CommInfoRegulationCheck()){  // �ʐM�������M�����[�V�������قȂ� ���M�����[�V�����Ȃ��ꍇ�͂�����ۂ̂͂�
                _talkStart(DBCDifferRule, FALSE);
                _changeState(_regulationDiffer);
                CommListSet(_YESNO_DIFFER_REGULATION, pInfo->selectChildNetID);
                return;
            }
        }
        CommInfoSetEntry( pInfo->selectChildNetID );  //�G���g���[����
        CommListSet(_YESNO_YES_RESULT, pInfo->selectChildNetID);
        if(_getMaxPlayNum() == CommInfoGetEntryNum()){  // �ڑ��l���ɒB����
            pInfo->connectNum = CommInfoGetEntryNum();
            if(_getMaxPlayNum() > 2){ // ��l�ȏ�̂Ƃ��͍Ċm�F���[�h��
                _changeState(_childListFinalCheck);
            }
            else{
                _listEnd(tcb,pInfo);   // ���̂܂܂��ē�
                _startParentExec(pInfo);
            }
        }
        else{
            _childListStartMessage();
            _changeState(_waitAndChildListSelect);
        }
    }
    else if(ret != BMPMENU_NULL){ // ��������I�������ꍇ
        if(pInfo->selectGameMode == COMM_MODE_CONTEST){  // �R���e�X�g�Ɍ������͖���
            for(i = 1 ; i < _getMaxPlayNum() ; i++){
                if(CommIsConnect(i)){
                    CommInfoDeletePlayer( i ); // �o�^������
                    CommListSet(_YESNO_ALL_EXIT, i);
                }
            }
            _childListStartMessage();
            _changeState(_waitAndChildListSelect);
        }
        else{
            CommInfoDeletePlayer( pInfo->selectChildNetID ); // �o�^������
            CommListSet(_YESNO_NO_RESULT, pInfo->selectChildNetID);
            _childListStartMessage();
            _changeState(_waitAndChildListSelect);
        }
    }
}

//--------------------------------------------------------------
/**
 * @brief   ���M�����[�V�������قȂ�
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   pInfo		���[�N�\���̂̃|�C���^
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
 * @brief   ���b�Z�[�W���o����A�ҋ@��Ԃւ����B ���X�g�͏o���܂�
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   pInfo		���[�N�\���̂̃|�C���^
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
 * @brief   ���b�Z�[�W���o����A�ҋ@��Ԃւ����B ���X�g�͏o���܂�
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   pInfo		���[�N�\���̂̃|�C���^
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
 * @brief   �Q�[�����J�n���Ă������ǂ����̂͂��������E�C���h�E
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   pInfo		���[�N�\���̂̃|�C���^
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
 * @brief   �Q�[�����J�n���Ă������ǂ����̂͂��������E�C���h�E�ҋ@
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   pInfo		���[�N�\���̂̃|�C���^
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
    if(CommIsError() || (CommGetConnectNum() != pInfo->connectNum)){  // �G���[���̓L�����Z�������ɂ���
        if(ret == BMPMENU_NULL){
            BmpYesNoWinDel(pInfo->yesNoWork,HEAPID_FIELD);
        }
        pInfo->yesNoWork = NULL;
        _changeState(_exitBattle);
    }
    else if(ret == 0){ // �͂���I�������ꍇ
        if(pInfo->selectGameMode == COMM_MODE_CONTEST){  // �R���e�X�g�Ɍ������͖���
            for(i = 1 ; i < CommGetConnectNum() ; i++){
                if(!CommIsConnect(i)){
                    _changeState(_exitBattle);
                    //���������Ă���
//                    CommStateSetEntryChildEnable(TRUE);
  //                  _commDisconnect();
    //                _listEnd(tcb, pInfo);
      //              _pInfo->retCode = COMM_RETVAL_CANCEL;
                    return;
                }
            }
        }
        CommTimingSyncStart(_TIMING_GUESTROOM); // �Q�X�g���[���ɍs�����M
        _changeState(_childListGuestRoomMessageWait);
    }
    else if(ret != BMPMENU_NULL){ // ��������I�������ꍇ
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
 * @brief   B�L�����Z���Ŕ����鎞�̂͂��������E�C���h�E����
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   pInfo		���[�N�\���̂̃|�C���^
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
        // �q�@������ꍇ �߂�O�Ɋm�F
        _talkStart(_msgsParentBCancel[pInfo->selectGameMode], FALSE);
        _changeState(_childListBCancelCheckFunc1);
    }
    else{   //�N���o�^���Ȃ��ꍇ���ǂ�
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
 * @brief   B�L�����Z���Ŕ����鎞�̂͂��������E�C���h�E�҂�
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   pInfo		���[�N�\���̂̃|�C���^
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
    if(CommIsError()){  // �G���[���̓L�����Z�������ɂ���
        ret = BMPLIST_CANCEL;
    }
    if(ret == 0){ // �͂���I�������ꍇ
        _commDisconnect();
        _listEnd(tcb, pInfo);
        _pInfo->retCode = COMM_RETVAL_CANCEL;
    }
    else if(ret != BMPMENU_NULL){ // ��������I�������ꍇ
        _childListStartMessage();
        _changeState(_waitAndChildListSelect);
    }
}

//--------------------------------------------------------------
/**
 * @brief   �o�^�����A�S���̒ʐM�J�n��҂�
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   pInfo		���[�N�\���̂̃|�C���^
 * @retval  none
 */
//--------------------------------------------------------------

static void _childListGuestRoomMessageWait(TCB_PTR tcb, void* work)
{
    _INFO_WORK* pInfo = (_INFO_WORK*)work;
    u32	ret = BMPLIST_NULL;

    if(CommIsError() || (CommGetConnectNum() != pInfo->connectNum)){  // �G���[���̓L�����Z�������ɂ���
        _changeState(_exitBattle);
    }
    else{
        _numDisp(pInfo);
        BmpListMain(pInfo->lw);
        if(CommIsTimingSync(_TIMING_GUESTROOM)){ // ��M�����ꍇ
            if(CommToolIsInitialize()){  // �ʐM���Ă�Ȃ�
                _listEnd(tcb, pInfo);
                _pleaseGuestRoomStart(pInfo);
            }
        }
    }
}

//--------------------------------------------------------------
/**
 * @brief   ���b�Z�[�W�ҋ@��͂��������E�C���h�E���o��
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   pInfo		���[�N�\���̂̃|�C���^
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
 * @brief   �q�@���X�g�����
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   pInfo		���[�N�\���̂̃|�C���^
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
 * @brief   �I�񂾐e�@�ɐڑ����ɂ���
 * @param   pInfo		���[�N�\���̂̃|�C���^
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
 * @brief   �I�񂾐e�@�ɐڑ����ɂ���
 * @param   pInfo		���[�N�\���̂̃|�C���^
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
 * @brief   �S���̃R�}���h��M��҂��Ĉē������
 * @param   pInfo		���[�N�\���̂̃|�C���^
 * @retval  none
 */
//--------------------------------------------------------------

static void _guestRoomOKFunc(TCB_PTR tcb, void* work)
{
    _INFO_WORK* pInfo = (_INFO_WORK*)work;

    if((CommGetCurrentID() == COMM_PARENT_ID) && (CommGetConnectNum() != pInfo->connectNum) ){
        _changeState(_guestRoomExitFunc);
    }
    else if(CommRecvIsExit() || CommIsError()){  // ���U����
        _changeState(_guestRoomExitFunc);
    }
    else if(FldTalkMsgEndCheck(_pInfo->msgIndex)){
        CommTimingSyncStart(_TIMING_GUESTROOM); // �Q�X�g���[���ɍs�����M
        _changeState(_guestRoomOKFunc2);
    }
}



//--------------------------------------------------------------
/**
 * @brief   �S���̃R�}���h��M��҂��Ĉē������
 * @param   pInfo		���[�N�\���̂̃|�C���^
 * @retval  none
 */
//--------------------------------------------------------------

static void _guestRoomOKFunc2(TCB_PTR tcb, void* work)
{
    _INFO_WORK* pInfo = (_INFO_WORK*)work;

    if((CommGetCurrentID() == COMM_PARENT_ID) && (CommGetConnectNum() != pInfo->connectNum) ){
        _changeState(_guestRoomExitFunc);
    }
    else if(CommRecvIsExit() || CommIsError()){  // ���U����
        _changeState(_guestRoomExitFunc);
        return;
    }
    else if(!CommIsConnect(COMM_PARENT_ID)){  // �G���[���̓L�����Z�������ɂ���
       _changeState(_guestRoomExitFunc);
        return;
    }
    else if( CommListGet(COMM_PARENT_ID , _YESNO_ALL_EXIT) != INVALID_LIST_NO ){
        _changeState(_guestRoomExitFunc);
        return;
    }
    else if(CommIsTimingSync(_TIMING_GUESTROOM)){ // ��M�����ꍇ
        if(CommToolIsInitialize()){  // �ʐM���Ă�Ȃ�
            if(!FldTalkMsgEndCheck(_pInfo->msgIndex)){
                GF_STR_PrintForceStop(_pInfo->msgIndex);
            }
            pInfo->connectNum = CommGetConnectNum(); // �l����
            _pleaseGuestRoomStart(pInfo);
            TCB_Delete(tcb);
            return;
        }
    }
        // ������x���Ԃ��߂����烁�b�Z�[�W�ύX
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
 * @brief   �Q�X�g������Ԃ����������ɖ߂邱�ƂɂȂ���
 * @param   pInfo		���[�N�\���̂̃|�C���^
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
 * @brief   NG���A���Ă����̂Őe��I�тȂ���
 * @param   pInfo		���[�N�\���̂̃|�C���^
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
//    CommSendData(CS_EXIT, NULL, 0); // �S�̃R�}���h���M����Ȃ��͂� 2005.8.31
}

//--------------------------------------------------------------
/**
 * @brief   NG���A���Ă����̂Őe��I�тȂ��������ֈړ�
 * @param   pInfo		���[�N�\���̂̃|�C���^
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
 * @brief   �G���[�A�ċN���ɂȂ����̂Őe��I�тȂ���
 * @param   pInfo		���[�N�\���̂̃|�C���^
 * @retval  none
 */
//--------------------------------------------------------------

static void _startChildConnectReset(_INFO_WORK* pInfo)
{
    CommFieldStateRebootBattleChild();
    TCB_Add(_childConnectResetFunc, pInfo, _PARENT_CONNECT_OK_PRI);
//    CommSendData(CS_EXIT, NULL, 0); //�ؒf�R�}���h���ꉞ���M ��������悤�Ȃ�؂�
}

//--------------------------------------------------------------
/**
 * @brief   �G���[���A���Ă����̂Őe��I�тȂ��������ֈړ�
 * @param   pInfo		���[�N�\���̂̃|�C���^
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
    CommMPSetNoChildError(TRUE);  // ���������NOCHILD�G���[�L��
}


//--------------------------------------------------------------
/**
 * @brief   �Q�[�����[�h�ɕK�v�ȍŏ��l�����A��
 * @param   none
 * @retval  �ŏ��l��
 */
//--------------------------------------------------------------

int _getMinPlayNum(void)
{
    return CommGetMinEntry(_pInfo->selectGameMode);
}

//--------------------------------------------------------------
/**
 * @brief   �Q�[�����[�h�ɕK�v�ȍő�l�����A��
 * @param   none
 * @retval  �ő�l��
 */
//--------------------------------------------------------------

static int _getMaxPlayNum(void)
{
    return CommGetMaxEntry(_pInfo->selectGameMode);
}

//--------------------------------------------------------------
/**
 * @brief   ���M�����[�V�����l�𓾂�
 * @param   none
 * @retval  �ő�l��
 */
//--------------------------------------------------------------

static int _getRegulationNo(void)
{
    return _pInfo->type1 + (_pInfo->type2 << 4);
}

//--------------------------------------------------------------
/**
 * @brief   ���X�g�����
 * @param   pInfo		���[�N�\���̂̃|�C���^
 * @retval  none
 */
//--------------------------------------------------------------
//static void _windowDestroy(_INFO_WORK* pInfo)
//{
  //  GF_BGL_BmpWinDel(&pInfo->talkWin);
//}

//--------------------------------------------------------------
/**
 * @brief   �e�@��I������E�C���h�E���J��
 * @param   FIELDSYS_WORK* pFSys   �t�B�[���h�V�X�e�����[�N�|�C���^
 * @param   connectMode      �ʐM���[�h
 * @param   type1            ���M�����[�V�������  ��  �����N
 * @param   type2            �R���e�X�g���
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
 * @brief   �e�@��I������E�C���h�E����������
 * @param   none
 * @retval  COMM_RETVAL_NULL    BMPLIST_NULL      �I��
            COMM_RETVAL_CANCEL  BMPLIST_CANCEL    user�L�����Z��
            COMM_RETVAL_OK      (0)               �I������
            COMM_RETVAL_ERROR   (1)               �ʐM�G���[
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
 * @brief   �q�@�ꗗ�E�C���h�E���J��
 * @param   FIELDSYS_WORK* pFSys   �t�B�[���h�V�X�e�����[�N�|�C���^
 * @param   connectMode      �ʐM���[�h
 * @param   type1            ���M�����[�V�������  ��  �����N
 * @param   type2            �R���e�X�g���
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
    _childListWindowOpen(_pInfo);  // �ڑ����Ă���q�@���X�g��\��
}


//--------------------------------------------------------------
/**
 * @brief   �e�@��I������E�C���h�E����������
 * @param   none
 * @retval  COMM_RETVAL_NULL    BMPLIST_NULL      �I��
            COMM_RETVAL_CANCEL  BMPLIST_CANCEL    user�L�����Z��
            COMM_RETVAL_OK      (0)               �I������
            COMM_RETVAL_ERROR   (1)               �ʐM�G���[
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
 * @brief   �_�C���N�g�R�[�i�[���[���ɓ��������̏���
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
 * �I�����ЂƂł��󂯎�������ǂ����m�点��
 * @param   none
 * @retval  ��M���Ă����ꍇTRUE ��M���Ă��Ȃ�������FALSE
 */
//==============================================================================

BOOL CommRecvIsExit(void)
{
    return FALSE;
}



#ifdef PM_DEBUG

//--------------------------------------------------------------
/**
 * @brief   �f�o�b�O�p�_�C���N�g�R�[�i�[�e�@�ڑ�
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
 * @brief   �f�o�b�O�p�_�C���N�g�R�[�i�[�q�@�ڑ�
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
 * @brief   �f�o�b�O�p�_�C���N�g�R�[�i�[�ڑ�����
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

void CommDirectConnect_Debug(void)
{
    // �����Ɉē����郁�b�Z�[�W
    _pleaseGuestRoomStart(_pInfo);
}


//--------------------------------------------------------------
/**
 * @brief   �f�o�b�O�p�_�C���N�g�R�[�i�[�����p�����[�^�ݒ�
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

