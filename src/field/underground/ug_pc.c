//=============================================================================
/**
 * @file	ug_pc.c
 * @brief	�n���p�\�R�����Ǘ�����N���X
 * @author	k.ohno
 * @date    2006.02.02
 */
//=============================================================================

#include "common.h"
#include "../fieldsys.h"
#include "communication/communication.h"
#include "ug_manager.h"

#include "system/bmp_menu.h"
#include "system/bmp_list.h"
#include "system/fontproc.h"
#include "system/window.h"
#include "system/clact_tool.h"
#include "system/snd_tool.h"
#include "system/wipe.h"
#include "system/brightness.h"

#include "../fld_bmp.h"
#include "../field_clact.h"

#include "msgdata/msg_uwflag.h"
#include "msgdata/msg_underworld.h"
#include "msgdata/msg_uwpersonal.h"
#include "msgdata/msg.naix"

#include "../fld_comact.h"
#include "ug_base.h"
#include "ug_base_se_def.h"
#include "ug_local.h"
#include "ug_shop.h"
#include "field/eventflag.h"
#include "../sysflag.h"



#define _RADAR_BRIGHTNESS_FL   (-6)   // �Ԃт�̕��ŏ��̃t�F�[�h���x�� -16�Ő^����

typedef struct {
    u8 accessNetID;     // �A�N�Z�X��
    u8 targetPCNetID;   // �^�[�Q�b�g�p�\�R��
    u8 bFlagGet;      // �����Ƃ���
} _resultAccessCommand;


typedef struct{
    int seq;
    int index;
//    BOOL bFade;
    u8 netID;
}_EVENT_EDITRAP_WORK;


#define _DEF_ALONE_X (15)   // �p�\�R���̈ʒu
#define _DEF_X (15+32)   // �p�\�R���̈ʒu
#define _DEF_Z (12)    // �p�\�R���̈ʒu
#define _ADD_X (32)   // �p�\�R����ID�ɂ��ړ��ʒu
#define _ADD_Z (32)   // �p�\�R����ID�ɂ��ړ��ʒu

static const BMPWIN_DAT _yesNoBmpDat = {
    GF_BGL_FRAME3_M, FLD_YESNO_WIN_PX, FLD_YESNO_WIN_PY,
    FLD_YESNO_WIN_SX, FLD_YESNO_WIN_SY, FLD_YESNO_WIN_PAL, FLD_YESNO_WIN_CGX
    };


static void _flagGetYesNoInit(FIELDSYS_WORK* pFSys, _resultAccessCommand* pAC);
// �p�\�R�����j���[���J��
static void UgPcMenuInit(FIELDSYS_WORK* pFSys);

static void UgListMoveSe( _START_WORK* pStart );

//==============================================================================
/**
 * �㉺�J�[�\���̕\������
 * @param   pTouch    �����ʒu
 * @retval  INVALID_NETID �� netID
 */
//==============================================================================

void _udCurDisp(_START_WORK* pPc, int line,  int maxLine , int windowNum)
{
    if(maxLine <= windowNum){
        return ;
    }
    if(line != 0){
        FComAct_SetDrawFlg(pPc->fca,FCA_UCURSOR,TRUE);
    }
    else{
        FComAct_SetDrawFlg(pPc->fca,FCA_UCURSOR,FALSE);
    }
    
    if(maxLine != (line+windowNum)){
        FComAct_SetDrawFlg(pPc->fca,FCA_DCURSOR,TRUE);
    }
    else{
        FComAct_SetDrawFlg(pPc->fca,FCA_DCURSOR,FALSE);
    }
    FActCom_Main(pPc->fca);
}

//==============================================================================
/**
 * �p�\�R���̃`�F�b�N�̏���
 * @param   pTouch    �����ʒu
 * @retval  INVALID_NETID �� netID
 */
//==============================================================================

int CommUnderPCCheck(Grid* pTouch,int dir)
{
    int i;
    int x = pTouch->xpos;
    int z = pTouch->zpos;
    int add = 0;

    if(dir != -1){
        if(dir != DIR_UP){
            return INVALID_NETID;
        }
    }
    if(z == _DEF_Z){
        add = 0;
    }
    else if(z == (_DEF_Z + _ADD_Z)){
        add = 8;
    }
    else{
        return INVALID_NETID;
    }
    if((x == _DEF_ALONE_X) || (x == (_DEF_ALONE_X+1))){
        return 0;
    }
    for(i = 0; i < COMM_MACHINE_MAX; i++){
        if((x == _DEF_X) || (x == (_DEF_X+1))){
            return i + add;
        }
        x -= _ADD_X;
    }
    return INVALID_NETID;
}

//==============================================================================
/**
 * ��n�ԍ�����p�\�R����X�l��Ԃ�
 * @param   ��n�ԍ�
 * @retval  X�l
 */
//==============================================================================

int UgPCGetPosX(int roomNo)
{
    if(CommMPIsConnectStalth()){
        return _DEF_ALONE_X;
    }
    if(roomNo < COMM_MACHINE_MAX){
        return _DEF_X + (_ADD_X * (roomNo % 8));
    }
    return _DEF_ALONE_X;
}

//==============================================================================
/**
 * ��n�ԍ�����p�\�R����Z�l��Ԃ�
 * @param   ��n�ԍ�
 * @retval  Z�l
 */
//==============================================================================

int UgPCGetPosZ(int roomNo)
{
/*    if(roomNo < COMM_MACHINE_MAX){
        return _DEF_Z + (_ADD_Z * (roomNo / 8));
    }*/
    return _DEF_Z;
}

//==============================================================================
/**
 * �p�\�R���̃`�F�b�N�̏���
 * @param   netID   netID
 * @param   pTouch    �����ʒu
 * @retval  �p�\�R���̑O����TRUE
 */
//==============================================================================

BOOL CommUnderPCCheckAndMessage(int netID, Grid* pTouch)
{
    int i;
    int x = pTouch->xpos;
    int z = pTouch->zpos;
    _resultAccessCommand ret;
    int id = CommUnderPCCheck(pTouch, CommPlayerGetSDir(netID));

    if( CommPlayerGetDir(id) == DIR_NOT ){
        id = INVALID_NETID;
    }
    
    if(id != INVALID_NETID){
        CommPlayerSetMoveControl_Server(netID,FALSE);
        ret.targetPCNetID = id;
        ret.accessNetID = netID;
        ret.bFlagGet = FALSE;
        if(id != netID){  //���l�̃p�\�R��
            if(!CommPlayerIsFlagData(netID)){
                ret.bFlagGet = TRUE;            // �͂�GET�\��
            }
            else{
                // �͂����łɎ����Ă���
            }
        }
        else{  // �����̃p�\�R��
            if(CommPlayerIsFlagData(netID)){   // ���������Ă���΂���
                u8 state = UNDER_FLAG_DELIVERY;  // ���������A����
                CommPlayerRecvFlagState(netID, 1,&state, NULL);
                return TRUE;
            }
            else{
            }
        }
        CommSendFixSizeData_ServerSide(CF_PC_ACCESS,&ret);
        return TRUE;
    }
    return FALSE;
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
    CommPlayerHoldBitEnd(_HOLD_FLAG_PC_GET);
}

//==============================================================================
/**
 * �p�\�R���ւ̃A�N�Z�X��������  CF_PC_ACCESS
 * @param   netID   netID
 * @param   pTouch    �����ʒu
 * @retval  �p�\�R���̑O����TRUE
 */
//==============================================================================

void CommUnderPCRecvAccess(int netID, int size, void* pData, void* pWork)
{
    _resultAccessCommand* pRet = pData;
    FIELDSYS_WORK* pFSys = pWork;

    if(!CommIsSendMoveData()){
        return;
    }
    if(pRet->accessNetID == CommGetCurrentID()){  // �����̏�
        if(pRet->targetPCNetID == CommGetCurrentID()){ // �����̃}�V��
			Snd_SePlay( SEQ_SE_DP_PC_ON );
            CommPlayerHold();
            UgPcMenuInit(pFSys);  // �p�\�R�����j���[
        }
        else{  // ���l�̃}�V��  -- flagGet
            CommPlayerHoldBit(_HOLD_FLAG_PC_GET);
            if(pRet->bFlagGet){
                _flagGetYesNoInit(pFSys,pRet);
            }
            else{
                CommMsgTalkWindowStart(CommUnderGetMsgUnderFlag(),mes_uw_flag_14,TRUE,_msgEndCallBack);
            }
        }
    }
    else{  // ���l�̃A�N�Z�X
    }
    if(pRet->bFlagGet){
        // �����Ƃ����l�Ɋ�����
//        CommPlayerGetFlag(pRet->accessNetID, pRet->targetPCNetID);
    }
}

//==============================================================================
/**
 * �p�\�R���ւ̃A�N�Z�X�R�}���h�̃T�C�Y
 * @param   none
 * @retval  size
 */
//==============================================================================

int CommUnderPCGetAccessSize(void)
{
    return sizeof(_resultAccessCommand);
}



//-------------------------------------------�p�\�R��

//==============================================================================
/**
 * �莝���O�b�Y���p�\�R���ɓ����
 * @param   index    ���Ԗڂ�GOODS�𓾂邩
 * @retval  ��������TRUE
 */
//==============================================================================

static BOOL _underBagGoodsSendPC(int index,_START_WORK* pStart)
{
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(GameSystem_GetSaveData(pStart->pFSys));
    int type;

    type = UnderGroundGetGoodsBagItem(pUGData, index);
    if(UnderGroundAddGoodsPCItem(pUGData, type)){
        UnderGroundDelGoodsBagItem(pUGData,index);
        return TRUE;
    }
    return FALSE;
}

//==============================================================================
/**
 * �p�\�R���̃O�b�Y���o�b�O�ɓ����
 * @param   index    ���Ԗڂ�GOODS�𓾂邩
 * @retval  ��������1  �����ς��Ȃ�O �z�u���Ă�����̂́[�P
 */
//==============================================================================

static int _underPcGoodsSendBag(int index,_START_WORK* pStart)
{
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(GameSystem_GetSaveData(pStart->pFSys));
    int type;

    if(UnderGroundIsEntryGoodsPCItem(pUGData, index)){
        return -1;
    }
    type = UnderGroundGetGoodsPCItem(pUGData, index);
    if(  CommUnderBagAddGoods(type) ){
        UnderGroundDelGoodsPCItem(pUGData, index);  // ����
        return TRUE;
    }
    return FALSE;
}

//---------------------------------------------
enum{
    _PC_START,
    _PC_START_WAIT,
    _PC_END,
    _PC_REMODELING,
    _PC_REMODELING_FADE,
    _PC_REMODELING_END,
    _PC_FLAG_START,
    _PC_FLAG_WAIT,
    _PC_RADAR_START,
    _PC_RADAR_WAIT,
    _FOSSIL_RADAR,
    _FOSSIL_RADAR_FAILED,
    _STONE_RADAR,
    _STONE_RADAR_FAILED,
    _TRAP_RADAR,
    _TRAP_RADAR_FAILED,
    _RADAR_MSG_END,
    _PC_SEND_GOODS_START,
    _PC_SEND_GOODS_WAIT,
    _PC_SEND_GOODS_END,
    _PC_RECV_GOODS_START,
    _PC_RECV_GOODS_WAIT,
    _PC_RECV_GOODS_END,
    _PC_MSG_AND_START,
} PcSeq_e;


static void _pcTopMenuLineSelect(BMPLIST_WORK * wk,u32 param,u8 mode)
{
    _START_WORK* pStart = (_START_WORK*)BmpListParamGet(wk, BMPLIST_ID_WORK);
    int idx = param;
    
    if(param == BMPLIST_CANCEL){
        idx = 5;
    }
    CommMsgTalkWindowAllWrite(CommUnderGetMsgUnderShop(),mes_uw_pers_051+idx,FALSE,NULL);
}

static void _pcRadarMenuLineSelect(BMPLIST_WORK * wk,u32 param,u8 mode)
{
    _START_WORK* pStart = (_START_WORK*)BmpListParamGet(wk, BMPLIST_ID_WORK);
    int idx = param;
    
    if(param == BMPLIST_CANCEL){
        idx = 3;
    }
    CommMsgTalkWindowAllWrite(CommUnderGetMsgUnderShop(),mes_uw_pers_51+idx,FALSE,NULL);
}

//--------------------------------------------------------------
/**
 * @brief   �p�\�R�����C�����j���[����
 * @param   tcb         �^�X�N
 * @param   work		���[�N�|�C���^
 * @retval  none
 */
//--------------------------------------------------------------

static BOOL _pcTopMenuFunc(TCB_PTR tcb, void* work)
{
    _START_WORK* pStart = work;
    u32	ret;
    u16 line,cursor;

    ret = BmpListMain(pStart->lw);
    BmpListPosGet( pStart->lw, &line, &cursor );
    UgMgrSetRecordKey(_KEY_MENU_PC_MAIN, cursor, line);

	UgListMoveSe( pStart );

    switch(ret){
      case BMPLIST_NULL:
        return FALSE;
      case BMPLIST_CANCEL:
		Snd_SePlay( SEQ_SE_DP_PC_LOGOFF );
        pStart->seq = _PC_END;
        break;
      case 0:  // �͗l�ւ�
        {
            UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(pStart->pFSys->savedata);
            if( 0 == UnderGroundGetNumGoodsPCItem(pUGData)){
                CommMsgTalkWindowStart(CommUnderGetMsgUnderShop(),
                                       mes_uw_pers_67, FALSE, NULL);
                pStart->seq = _PC_MSG_AND_START;
            }
            else if(CommMPIsConnectStalth()){
                UgMgrEndNowTCB();
                pStart->seq = _PC_REMODELING;
            }
            else{
                CommMsgTalkWindowStart(CommUnderGetMsgUnderShop(),
                                       mes_uw_pers_63, FALSE, NULL);
                pStart->seq = _PC_MSG_AND_START;
            }
        }
        break;
      case 4:  // ���[�_�[
		Snd_SePlay( SEQ_SE_DP_SELECT );
        pStart->seq = _PC_RADAR_START;
        break;
      case 3:  // ��
		Snd_SePlay( SEQ_SE_DP_SELECT );
        pStart->seq = _PC_FLAG_START;
        break;
      case 1:  // �a����
		Snd_SePlay( SEQ_SE_DP_SELECT );
        pStart->seq = _PC_SEND_GOODS_START;//_PC_SEND_START;
        break;
      case 2:  // �����o��
		Snd_SePlay( SEQ_SE_DP_SELECT );
        pStart->seq = _PC_RECV_GOODS_START;//_PC_RECV_START;
        break;
      default:
        break;
    }
    return TRUE;
}



//--------------------------------------------------------------
/**
 * @brief   �p�\�R���a���郁�j���[�X�^�[�g
 * @param   pStart		���[�N�|�C���^
 * @retval  none
 */
//--------------------------------------------------------------

#define _PCMAIN_MENU_POSX    (17)
#define _PCMAIN_MENU_POSY    (3)
#define _PCMAIN_MENU_SIZE_X  (14)
#define _PCMAIN_MENU_SIZE_Y  (16)

// �؂�ւ����Ƀ`�����̂ŁA�L�����ʒu��ʂ̈ʒu�ɍő�T�C�Y�ŌŒ� 2006/08/01 by nakahiro
// PC���j���[�̃L�����ʒu
#define	_PCMAIN_MENU_CGX	( MENU_WIN_CGX_NUM-_PCMAIN_MENU_SIZE_X*_PCMAIN_MENU_SIZE_Y )
// PC���j���[���ڂ̃L�����ʒu
#define	_PCPARAM_MENU_CGX	( _PCMAIN_MENU_CGX-_PCMAIN_MENU_SIZE_X*_PCMAIN_MENU_SIZE_Y )


static void _pcMainMenuStart(_START_WORK* pStart,int msgNo,int count, pBmpCallBack pCallBack, int curWorkNo)
{
    BMPLIST_HEADER list_h;
    int line = count + 1;
    BOOL bRadar = TRUE;

#ifdef  DEBUG_ONLY_FOR_ohno
#else
    if(FLAG_LV_GOLD > SecretBaseRecordGetFlagType(SaveData_GetSecretBaseRecord(pStart->pFSys->savedata))){  // �S�[���h�t���b�O�ȉ�
        bRadar = FALSE;
        line -= 1;
    }
#endif
    _startMenuEnd(pStart);
//	GF_BGL_LoadScreenReq( pStart->pFSys->bgl, GF_BGL_FRAME3_M );

    //BMP�E�B���h�E����
    pStart->menulist = BMP_MENULIST_Create( line, HEAPID_FIELD );
/*
    GF_BGL_BmpWinAdd(pStart->pFSys->bgl,&pStart->win,
                     GF_BGL_FRAME3_M, _PCMAIN_MENU_POSX, _PCMAIN_MENU_POSY,
                     _PCMAIN_MENU_SIZE_X, line * 2, FLD_SYSFONT_PAL,
                     FLD_MSG_WIN_CGX - (10 * (line + 3) * 2));
*/
    GF_BGL_BmpWinAdd(pStart->pFSys->bgl,&pStart->win,
                     GF_BGL_FRAME3_M, _PCMAIN_MENU_POSX, _PCMAIN_MENU_POSY,
                     _PCMAIN_MENU_SIZE_X, line * 2, FLD_SYSFONT_PAL,
                     _PCMAIN_MENU_CGX);

    BmpMenuWinWrite(&pStart->win, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL );
	{
		MSGDATA_MANAGER* msgman;
		int i=0;

		msgman = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_uwpersonal_dat, HEAPID_FIELD);
		for(i = 0; i < line ; i++)
		{
            if(i == (line-1)){  // ��߂�
                BMP_MENULIST_AddArchiveString( pStart->menulist, msgman,
                                               msgNo + 5, BMPLIST_CANCEL );
            }
            else{
                BMP_MENULIST_AddArchiveString( pStart->menulist, msgman,
                                               msgNo+i, i );
            }
		}
		MSGMAN_Delete(msgman);
	}

    MI_CpuCopy8( CommMsgGetNormalBmpListHeader(), &list_h, sizeof(BMPLIST_HEADER));
//    list_h = MenuListHeader;
    list_h.count = line;
    list_h.line = line;
    list_h.list = pStart->menulist;
    list_h.win = &pStart->win;
    if(pCallBack){
        list_h.call_back = pCallBack;
    }
    list_h.work = pStart;
    UgBagCursorLineLimit(pStart, line, list_h.count);
    pStart->lw = BmpListSet(&list_h,
                            pStart->line,
                            pStart->cursor,
                            HEAPID_FIELD);
//    GF_BGL_BmpWinOn(&pStart->win);
}

static void _pcMenuStart(_START_WORK* pStart,int msgNo,int count, pBmpCallBack pCallBack, int curWorkNo)
{
    BMPLIST_HEADER list_h;
    int line = count + 1;
    BOOL bRadar = TRUE;

    _startMenuEnd(pStart);
//	GF_BGL_LoadScreenReq( pStart->pFSys->bgl, GF_BGL_FRAME3_M );

    //BMP�E�B���h�E����
    pStart->menulist = BMP_MENULIST_Create( line, HEAPID_FIELD );
/*
    GF_BGL_BmpWinAdd(pStart->pFSys->bgl,&pStart->win,
                     GF_BGL_FRAME3_M, _PCMAIN_MENU_POSX, _PCMAIN_MENU_POSY,
                     _PCMAIN_MENU_SIZE_X, line * 2, FLD_SYSFONT_PAL,
                     FLD_MSG_WIN_CGX - (10 * (line + 3) * 2));
*/
    GF_BGL_BmpWinAdd(pStart->pFSys->bgl,&pStart->win,
                     GF_BGL_FRAME3_M, _PCMAIN_MENU_POSX, _PCMAIN_MENU_POSY,
                     _PCMAIN_MENU_SIZE_X, line * 2, FLD_SYSFONT_PAL,
                     _PCPARAM_MENU_CGX);
    BmpMenuWinWrite(&pStart->win, WINDOW_TRANS_OFF, MENU_WIN_CGX_NUM, MENU_WIN_PAL );
	{
		MSGDATA_MANAGER* msgman;
		int i=0;

		msgman = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_uwpersonal_dat, HEAPID_FIELD);
		for(i = 0; i < line ; i++)
		{
            if(i == count){  // ��߂�
                BMP_MENULIST_AddArchiveString( pStart->menulist, msgman,
                                               msgNo+i, BMPLIST_CANCEL );
            }
            else{
                BMP_MENULIST_AddArchiveString( pStart->menulist, msgman,
                                               msgNo+i, i );
            }
		}
		MSGMAN_Delete(msgman);
	}

    MI_CpuCopy8( CommMsgGetNormalBmpListHeader(), &list_h, sizeof(BMPLIST_HEADER));
    list_h.count = count + 1;
    list_h.line = line;
    list_h.list = pStart->menulist;
    list_h.win = &pStart->win;
    if(pCallBack){
        list_h.call_back = pCallBack;
    }
    list_h.work = pStart;
    UgBagCursorLineLimit(pStart, line, list_h.count);
    pStart->lw = BmpListSet(&list_h,
                            pStart->line,
                            pStart->cursor,
                            HEAPID_FIELD);
//    GF_BGL_BmpWinOn(&pStart->win);
}

//--------------------------------------------------------------
/**
 * @brief   ���[�_�[���j���[����
 * @param   tcb         �^�X�N
 * @param   work		���[�N�|�C���^
 * @retval  none
 */
//--------------------------------------------------------------

static BOOL _pcRadarMenuFunc(TCB_PTR tcb, void* work)
{
    _START_WORK* pStart = work;
    u32	ret;
    u16 line,cursor;

    ret = BmpListMain(pStart->lw);
    BmpListPosGet( pStart->lw, &line, &cursor );
    UgMgrSetRecordKey(_KEY_MENU_PC_RADAR, cursor, line);
//    ret = BmpListMain(pStart->lw);

	UgListMoveSe( pStart );

    switch(ret){
      case BMPLIST_NULL:
        return FALSE;
      case BMPLIST_CANCEL:
		Snd_SePlay( SEQ_SE_DP_SELECT );
        pStart->seq = _PC_START;
        break;
      case 0:  // ���������[�_�[
        if(CommMPIsConnectStalth()){
            pStart->seq = _FOSSIL_RADAR_FAILED;
        }
        else{
            pStart->seq = _FOSSIL_RADAR;
        }
        break;
      case 1:  // ���܃��[�_�[
        if(CommMPIsConnectStalth()){
            pStart->seq = _STONE_RADAR_FAILED;
        }
        else{
            pStart->seq = _STONE_RADAR;
        }
        break;
      case 2:  // �g���b�v���[�_�[
        if(CommMPIsConnectStalth()){
            pStart->seq = _TRAP_RADAR_FAILED;
        }
        else{
            pStart->seq = _TRAP_RADAR;
        }
        break;
      default:
        pStart->seq = _PC_END;
        break;
    }
    return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   �O�b�Y��a���郁�j���[����
 * @param   tcb         �^�X�N
 * @param   work		���[�N�|�C���^
 * @retval  none
 */
//--------------------------------------------------------------

static BOOL _pcSendGoodsMenuFunc(TCB_PTR tcb, void* work)
{
    _START_WORK* pStart = work;
    u32	ret,type;
    u16 line,cursor;

//    ret = BmpListMain(pStart->lw);
//    BmpListPosGet( pStart->lw, &line, &cursor );
//    UgMgrSetRecordKey(_KEY_MENU_PC_SEND_GOODS, cursor, line);
//    _udCurDisp(pStart, line,  BmpListParamGet(pStart->lw,BMPLIST_ID_COUNT), _FIELD_MENU_MAX);

    ret = Ug_BmpListMain(pStart->pUGlw);
    BmpListPosGet( pStart->pUGlw->pBmpList, &line, &cursor );
    UgMgrSetRecordKey(_KEY_MENU_PC_SEND_GOODS, cursor, line);
    _udCurDisp(pStart, line,  BmpListParamGet(pStart->pUGlw->pBmpList,BMPLIST_ID_COUNT), _FIELD_MENU_MAX);

    
    if(ret == _MENURETURN_EXIT){
        ret = BMPLIST_CANCEL;
    }
    switch(ret){
    case BMPLIST_NULL:
        return FALSE;
    case BMPLIST_CANCEL:
        CommMsgTalkWindowEnd(CommUnderGetMsgUnderItem());
        pStart->seq = _PC_START; //_PC_SEND_START;
        break;
    default:
        CommMsgTalkWindowEnd(CommUnderGetMsgUnderItem());
        type = _underBagGetGoodsID(ret, pStart);  //�O�b�Y�ԍ�
        if(_underBagGoodsSendPC(ret, pStart)){  // �p�\�R���ɓ����
            CommMsgRegisterUGGoodsName(CommUnderGetMsgUnderShop(), type);
            CommMsgTalkWindowStart(CommUnderGetMsgUnderShop(),mes_uw_pers_41,FALSE,NULL);
        }
        else{
            CommMsgTalkWindowStart(CommUnderGetMsgUnderShop(),mes_uw_pers_42,FALSE,NULL);
        }
        pStart->seq = _PC_SEND_GOODS_END;
        _startMenuEnd(pStart);
        break;
    }
    return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   �O�b�Y�����炤���j���[����
 * @param   tcb         �^�X�N
 * @param   work		���[�N�|�C���^
 * @retval  none
 */
//--------------------------------------------------------------

static BOOL _pcRecvGoodsMenuFunc(TCB_PTR tcb, void* work)
{
    _START_WORK* pStart = work;
    u32	ret,type;
    u16 line,cursor;
    int getRet;

//    ret = BmpListMain(pStart->lw);
//    BmpListPosGet( pStart->lw, &line, &cursor );
//    UgMgrSetRecordKey(_KEY_MENU_PC_RECV_GOODS, cursor, line);
//    _udCurDisp(pStart, line,  BmpListParamGet(pStart->lw,BMPLIST_ID_COUNT), _FIELD_MENU_MAX);

    ret = Ug_BmpListMain(pStart->pUGlw);
    BmpListPosGet( pStart->pUGlw->pBmpList, &line, &cursor );
    UgMgrSetRecordKey(_KEY_MENU_PC_RECV_GOODS, cursor, line);
    _udCurDisp(pStart, line,  BmpListParamGet(pStart->pUGlw->pBmpList,BMPLIST_ID_COUNT), _FIELD_MENU_MAX);


    if(ret == _MENURETURN_EXIT){
        ret = BMPLIST_CANCEL;
    }
    switch(ret){
    case BMPLIST_NULL:
        return FALSE;
    case BMPLIST_CANCEL:
        CommMsgTalkWindowEnd(CommUnderGetMsgUnderItem());
        pStart->seq = _PC_START; //_PC_RECV_START;
        break;
    default:
        CommMsgTalkWindowEnd(CommUnderGetMsgUnderItem());
        type = _underPcGetGoodsID(ret, pStart);  // �O�b�Y�ԍ�
        getRet = _underPcGoodsSendBag(ret, pStart);
        if(1 == getRet){  // �o�b�O�ɓ����
            CommMsgRegisterUGGoodsName(CommUnderGetMsgUnderShop(), type);
            CommMsgTalkWindowStart(CommUnderGetMsgUnderShop(),mes_uw_pers_40,FALSE,NULL);
        }
        else if(-1 == getRet){
            CommMsgTalkWindowStart(CommUnderGetMsgUnderShop(),mes_uw_pers_62,FALSE,NULL);
        }
        else{
            CommMsgTalkWindowStart(CommUnderGetMsgUnderShop(),mes_uw_pers_43,FALSE,NULL);
        }
        pStart->seq = _PC_RECV_GOODS_END;
        _startMenuEnd(pStart);
        break;
    }
    FComAct_SetDrawFlg(pStart->fca, FCA_UCURSOR, FALSE);
    FComAct_SetDrawFlg(pStart->fca, FCA_DCURSOR, FALSE);
    return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   ���b�Z�[�W�I���{�L�[��҂�
 * @param   pStart		���[�N�|�C���^
 * @retval  none
 */
//--------------------------------------------------------------

static BOOL _msgEndWait(_START_WORK* pPc)
{
    if( CommMsgIsOutputing(CommUnderGetMsgUnderShop()) == 0 ){
        if(sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL)){
            CommMsgTalkWindowEnd(CommUnderGetMsgUnderShop());
            return TRUE;
        }
    }
    return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   �J������閧��n�����ɂ���A�܂��͖߂�
 * @param   bCenter		�^��=TRUE
 * @retval  none
 */
//--------------------------------------------------------------

static void _camMove(BOOL bCenter, FIELDSYS_WORK* pFSys)
{
    VecFx32 pos;

    pos.y = 0;
    pos.x = 15*FX32_ONE*16 - Player_NowGPosXGet( pFSys->player )*FX32_ONE*16;
    pos.z = 17*FX32_ONE*16 - Player_NowGPosZGet( pFSys->player )*FX32_ONE*16;
    if(!bCenter){
        pos.x = -pos.x;
        pos.z = -pos.z;
    }
    //�J�����ƒ����_�𓯎��ɕ��s�ړ�
   GFC_ShiftCamera(&pos, pFSys->camera_ptr);
}



//--------------------------------------------------------------
/**
 * @brief   FIELDEDIT���Ăяo�����߂̃��b�p�[�C�x���g
 * @param   pStart		���[�N�|�C���^
 * @retval  none
 */
//--------------------------------------------------------------

typedef enum{
    _RAP_START,
    _REMODELING_FADE,
    _REMODELING_END,
    _BACK_EDIT,
    _BACK_EDIT_END,
    _RAP_END,
};

static BOOL _GMEVENT_EditRap(GMEVENT_CONTROL * event)
{
    FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
    _EVENT_EDITRAP_WORK * mdw = FieldEvent_GetSpecialWork(event);
    LOCATION_WORK locationWork;
    u32 ret;
    BOOL bExit = FALSE;
    int msgNo;

    switch (mdw->seq) {
      case _RAP_START:
        Snd_SePlay(UG_BASE_SE_LOGIN);
        WIPE_SYS_Start(WIPE_PATTERN_FSAM,
                   WIPE_TYPE_FADEOUT,
                   WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK,COMM_BRIGHTNESS_SYNC,
                   1,HEAPID_FIELD);
        mdw->seq = _REMODELING_FADE;
        break;
      case _REMODELING_FADE:
        if(WIPE_SYS_EndCheck()){
            Player_DispON_OFF_Set(fsys->player,FALSE);
            //�J�����ړ�����
            _camMove(TRUE, fsys);
            WIPE_SYS_Start(WIPE_PATTERN_FMAS,
                       WIPE_TYPE_PESOCOMIN,
                       WIPE_TYPE_PESOCOMIN, WIPE_FADE_BLACK,COMM_BRIGHTNESS_SYNC,
                       1,HEAPID_FIELD);
            mdw->seq = _REMODELING_END;
        }
        break;
      case _REMODELING_END:
        if(WIPE_SYS_EndCheck()){
            UGBase_CallBaseEditEvent(fsys, event);
            mdw->seq = _BACK_EDIT;
        }
        break;
      case _BACK_EDIT:
        Snd_SePlay(UG_BASE_SE_LOGOUT);
        WIPE_SYS_Start(WIPE_PATTERN_FSAM,
                       WIPE_TYPE_PESOCOMOUT,
                       WIPE_TYPE_PESOCOMOUT, WIPE_FADE_BLACK,COMM_BRIGHTNESS_SYNC,
                       1,HEAPID_FIELD);
        mdw->seq = _BACK_EDIT_END;
        break;
      case _BACK_EDIT_END:
        if(WIPE_SYS_EndCheck()){
            //�J�����ړ�����
            Player_DispON_OFF_Set(fsys->player,TRUE);
            _camMove(FALSE, fsys);
            WIPE_SYS_Start(WIPE_PATTERN_FMAS,
                       WIPE_TYPE_FADEIN,
                       WIPE_TYPE_FADEIN, WIPE_FADE_BLACK,COMM_BRIGHTNESS_SYNC,
                       1,HEAPID_FIELD);
            mdw->seq = _RAP_END;
        }
        break;
      case _RAP_END:
        if(WIPE_SYS_EndCheck()){
            UgSecretBaseMakeMyAttr(fsys);
            SysFlag_UgGoodsSet(SaveData_GetEventWork(fsys->savedata));
            UgPcMenuInit(fsys);
            sys_FreeMemoryEz(mdw);
            return TRUE;
        }
        break;
    }
    return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   �E�C���h�E����
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		���[�N�f�[�^�̃|�C���^
 * @retval  none
 */
//--------------------------------------------------------------

static void _delEnd(TCB_PTR tcb, _START_WORK* pStart)
{
    STRBUF_Delete(pStart->pStrBuf1);
    STRBUF_Delete(pStart->pStrBuf2);
    WORDSET_Delete(pStart->pWordSet);
    
    if(pStart->endfunc != NULL){
        pStart->endfunc(0);
    }
    if(pStart->fca){
        FComAct_Delete(pStart->fca);
        pStart->fca = NULL;
    }
    _startMenuEnd(pStart);
    CommMsgTalkWindowEnd(CommUnderGetMsgUnderShop());
    TCB_Delete(tcb);
    sys_FreeMemoryEz(pStart);
}


//--------------------------------------------------------------
/**
 * @brief   GOODS���j���[����
 * @param   pStart		���[�N�|�C���^
 * @retval  none
 */
//--------------------------------------------------------------

static void _pcMenuFunc(TCB_PTR tcb, void* work)
{
    _START_WORK* pPc = work;
    u32	ret;
    _EVENT_EDITRAP_WORK * mdw;

    switch(pPc->seq){
      case _PC_START:
        pPc->cursor = UgMgrGetRecordKeyCursor(_KEY_MENU_PC_MAIN);
        pPc->line = UgMgrGetRecordKeyLine(_KEY_MENU_PC_MAIN);
		pPc->pos_bak = pPc->cursor;
        _pcMainMenuStart(work, mes_uw_pers_011,5,_pcTopMenuLineSelect, 0);
        pPc->seq = _PC_START_WAIT;
        break;
      case _PC_START_WAIT:
        _pcTopMenuFunc(tcb, work);
        break;
      case _PC_END:
        CommPlayerHoldEnd();
        UgMgrEndNowTCB();  // �I���Ȃ̂ŊJ���֐��N���A
        _delEnd(tcb, pPc);
        break;
      case _PC_FLAG_START:
        _startMenuEnd(work);
        CommMsgTalkWindowEnd(CommUnderGetMsgUnderShop());
        pPc->pWork = UgRecordFlagListStart(pPc->pFSys->bgl,
                              SaveData_GetMyStatus(GameSystem_GetSaveData(pPc->pFSys)),
                              SaveData_GetUnderGroundData(GameSystem_GetSaveData(pPc->pFSys)),
                              NULL,NULL);
        pPc->seq = _PC_FLAG_WAIT;
        break;
      case _PC_FLAG_WAIT:
        if(sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL)){
            UgRecordFlagListEnd(pPc->pWork);
            pPc->pWork = NULL;
            pPc->seq = _PC_START;
        }
        break;
      case _PC_RADAR_START:
        CommMsgTalkWindowEnd(CommUnderGetMsgUnderShop());
        pPc->cursor = UgMgrGetRecordKeyCursor(_KEY_MENU_PC_RADAR);
        pPc->line = UgMgrGetRecordKeyLine(_KEY_MENU_PC_RADAR);
        _pcMenuStart(work, mes_uw_pers_46,3,_pcRadarMenuLineSelect, 1);
        pPc->seq = _PC_RADAR_WAIT;
        break;
      case _PC_RADAR_WAIT:
        _pcRadarMenuFunc(tcb, work);
        break;
      case _FOSSIL_RADAR:
        _startMenuEnd(pPc);
        UgMgrSetFossilRadarDisp();
        UgFossilPcRadarStart();
        ChangeBrightnessRequest(1,_RADAR_BRIGHTNESS_FL,BRIGHTNESS_NORMAL,
                                PLANEMASK_BG0,MASK_MAIN_DISPLAY);
        CommMsgTalkWindowStart(CommUnderGetMsgUnderShop(),mes_uw_pers_55,FALSE,NULL);
        pPc->seq = _RADAR_MSG_END;
        break;
      case _FOSSIL_RADAR_FAILED:
        CommMsgTalkWindowStart(CommUnderGetMsgUnderShop(),mes_uw_pers_64,FALSE,NULL);
        pPc->seq = _RADAR_MSG_END;
        break;
      case _STONE_RADAR:
        _startMenuEnd(pPc);
        UgMgrSetStoneRadarDisp();
        UgStonePcRadarStart();
        ChangeBrightnessRequest(1,_RADAR_BRIGHTNESS_FL,BRIGHTNESS_NORMAL,
                                PLANEMASK_BG0,MASK_MAIN_DISPLAY);
        CommMsgTalkWindowStart(CommUnderGetMsgUnderShop(),mes_uw_pers_56,FALSE,NULL);
        pPc->seq = _RADAR_MSG_END;
        break;
      case _STONE_RADAR_FAILED:
        CommMsgTalkWindowStart(CommUnderGetMsgUnderShop(),mes_uw_pers_65,FALSE,NULL);
        pPc->seq = _RADAR_MSG_END;
        break;
      case _TRAP_RADAR:
        _startMenuEnd(pPc);
        UgMgrSetTrapRadarDisp();
        UgTrapRecvNatureRadarStart();
        ChangeBrightnessRequest(1,_RADAR_BRIGHTNESS_FL,BRIGHTNESS_NORMAL,
                                PLANEMASK_BG0,MASK_MAIN_DISPLAY);
        CommMsgTalkWindowStart(CommUnderGetMsgUnderShop(),mes_uw_pers_57,FALSE,NULL);
        pPc->seq = _RADAR_MSG_END;
        break;
      case _TRAP_RADAR_FAILED:
        CommMsgTalkWindowStart(CommUnderGetMsgUnderShop(),mes_uw_pers_66,FALSE,NULL);
        pPc->seq = _RADAR_MSG_END;
        break;
      case _RADAR_MSG_END:
        if( CommMsgIsOutputing(CommUnderGetMsgUnderShop()) == 0 ){
            if(sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL)){
                ChangeBrightnessRequest(1,BRIGHTNESS_NORMAL,_RADAR_BRIGHTNESS_FL,
                                        PLANEMASK_BG0,MASK_MAIN_DISPLAY);
                CommMsgTalkWindowEnd(CommUnderGetMsgUnderShop());
                if(CommMPIsConnectStalth()){
                    UgMgrSetNoneRadarDisp();
                }
                else{
                    UgMgrSetMyTrapRadarDisp();  // ������㩂ɖ߂�
                }
                UgTrapRecvNatureRadarEnd();  // �I������
                UgFossilPcRadarEnd();
                UgStonePcRadarEnd();
                pPc->seq = _PC_RADAR_START;
            }
        }
        break;
      case _PC_REMODELING:
        // �I�� �C�x���g�Ɉ��p��
        if(pPc->pFSys->event==NULL){
            mdw = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(_EVENT_EDITRAP_WORK));
            MI_CpuClear8(mdw, sizeof(_EVENT_EDITRAP_WORK));
            mdw->seq = _RAP_START;
            mdw->index = 0;
            FieldEvent_Set(pPc->pFSys, _GMEVENT_EditRap, mdw);
        }
        _delEnd(tcb, pPc);
        break;
      case _PC_SEND_GOODS_START:
        pPc->cursor = UgMgrGetRecordKeyCursor(_KEY_MENU_PC_SEND_GOODS);
        pPc->line = UgMgrGetRecordKeyLine(_KEY_MENU_PC_SEND_GOODS);
        _goodsMenuStart_BagPc(work);
        UgShopMiniInfoDispWindow(work, mes_uw_pers_32);
        pPc->seq = _PC_SEND_GOODS_WAIT;
        break;
      case _PC_SEND_GOODS_WAIT:
        _pcSendGoodsMenuFunc(tcb, work);
        break;
      case _PC_SEND_GOODS_END:
        if( _msgEndWait( pPc ) ){
            pPc->seq = _PC_SEND_GOODS_START;
        }
        break;
      case _PC_RECV_GOODS_START:
        pPc->cursor = UgMgrGetRecordKeyCursor(_KEY_MENU_PC_RECV_GOODS);
        pPc->line = UgMgrGetRecordKeyLine(_KEY_MENU_PC_RECV_GOODS);
        _goodsMenuStart_Pc(work);
        UgShopMiniInfoDispWindow(work, mes_uw_pers_36);
        pPc->seq = _PC_RECV_GOODS_WAIT;
        break;
      case _PC_RECV_GOODS_WAIT:
        _pcRecvGoodsMenuFunc(tcb, work);
        break;
      case _PC_RECV_GOODS_END:
        if( _msgEndWait( pPc ) ){
            pPc->seq = _PC_RECV_GOODS_START;
        }
        break;
      case _PC_MSG_AND_START:
        if( _msgEndWait( pPc ) ){
            pPc->seq = _PC_START;
        }
        break;
    }
}

//--------------------------------------------------------------
/**
 * @brief   �p�\�R�����j���[���J��
 * @param   FIELDSYS_WORK   �t�B�[���h�V�X�e�����[�N�|�C���^
 * @retval  none
 */
//--------------------------------------------------------------

static void UgPcMenuInit(FIELDSYS_WORK* pFSys)
{
    BMPLIST_HEADER list_h;
    _START_WORK* pPc;
    const int LISTMAX = 6;  // ���X�g�̍ő�

    UgMgrOpenRecordKey(_KEY_NAME_PC);
    pPc = sys_AllocMemory(HEAPID_FIELD, sizeof(_START_WORK));
    MI_CpuFill8(pPc, 0, sizeof(_START_WORK));
    pPc->pFSys = pFSys;
    CommMsgChangeMSGMAN(CommUnderGetMsgUnderShop(),NARC_msg_uwpersonal_dat, MSGMAN_TYPE_DIRECT);
    pPc->seq = _PC_START;
    pPc->pStrBuf1 = STRBUF_Create( _EVWIN_MSG_BUF_SIZE, HEAPID_FIELD );
    pPc->pStrBuf2 = STRBUF_Create( _EVWIN_MSG_BUF_SIZE, HEAPID_FIELD );
    pPc->pWordSet = WORDSET_Create( HEAPID_FIELD );


	//�J�[�\���A�N�^�[������
	pPc->fca = FComAct_Init(HEAPID_FIELD);
	FComAct_CursorPosSet(pPc->fca,200,20,122);
	FComAct_SetDrawFlg(pPc->fca,FCA_UCURSOR,FALSE);
	FComAct_SetDrawFlg(pPc->fca,FCA_DCURSOR,FALSE);

    pPc->pTCB = TCB_Add(_pcMenuFunc, pPc, _MENU_UG_PRI);

    UgMgrSetNowTCB(pPc, pPc->pTCB, UgGoodsMenuForceDelete2);  // �p�\�R�����j���[
}

//--------------------------------------------------------------
/**
 * @brief   
 * @param   FIELDSYS_WORK   �t�B�[���h�V�X�e�����[�N�|�C���^
 * @retval  none
 */
//--------------------------------------------------------------

typedef struct {
    int seq;
    FIELDSYS_WORK* pFSys;
    BMPMENU_WORK*  pYesNoWork;
    _resultAccessCommand ac;
    TCB_PTR pTCB;
} _FLAG_YESNO_WORK;



static void _flagGetYesNoFunc(TCB_PTR tcb, void* work)
{
    _FLAG_YESNO_WORK* wk = work;
    int ret;
    enum{
        _MSG_YESNO,
        _MSG_WAIT,
        _END
    };

    switch(wk->seq){
      case _MSG_YESNO:
        if( CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0 ){
            wk->pYesNoWork = BmpYesNoSelectInit(wk->pFSys->bgl,
                                                &_yesNoBmpDat, MENU_WIN_CGX_NUM,
                                                MENU_WIN_PAL, HEAPID_FIELD );
            wk->seq = _MSG_WAIT;
        }
        break;
      case _MSG_WAIT:
        ret = BmpYesNoSelectMain(wk->pYesNoWork, HEAPID_FIELD);
        if(ret == BMPMENU_NULL){ // ��������I�������ꍇ �I��
            return;
        }
        else if(ret == 0){ // �͂���I�������ꍇ
            CommSendFixSizeData(CF_GET_FLAG,&wk->ac);
        }
        else{ // ��������I�������ꍇ �I��
            CommPlayerHoldBitEnd(_HOLD_FLAG_PC_GET);
            CommMsgTalkWindowEnd(CommUnderGetMsgUnderWorld());
        }
        wk->seq = _END;
        wk->pYesNoWork=NULL;
        break;
      case _END:
        sys_FreeMemoryEz(wk);
        UgMgrEndNowTCB();
        TCB_Delete(tcb);
        break;
    }
}

//--------------------------------------------------------------
/**
 * @brief   �G�̊�n����n�^����邽�߂̃��[�`���������I��
 * @param   FIELDSYS_WORK   �t�B�[���h�V�X�e�����[�N�|�C���^
 * @retval  none
 */
//--------------------------------------------------------------

static void _flagGetTCBForceDel(TCB_PTR pTCB, void* work)
{
    _FLAG_YESNO_WORK* wk = work;

    if(wk->pYesNoWork){
        BmpYesNoWinDel( wk->pYesNoWork, HEAPID_FIELD );
    }
    sys_FreeMemoryEz(wk);
    TCB_Delete(pTCB);
}

//--------------------------------------------------------------
/**
 * @brief   �G�̊�n����n�^����邽�߂̃��[�`��
 * @param   FIELDSYS_WORK   �t�B�[���h�V�X�e�����[�N�|�C���^
 * @retval  none
 */
//--------------------------------------------------------------

static void _flagGetYesNoInit(FIELDSYS_WORK* pFSys,_resultAccessCommand* pAC)
{
    _FLAG_YESNO_WORK* wk = sys_AllocMemory(HEAPID_FIELD, sizeof(_START_WORK));
    MI_CpuFill8(wk, 0, sizeof(_FLAG_YESNO_WORK));
    wk->seq = 0;
    wk->pFSys = pFSys;

    wk->pTCB = TCB_Add(_flagGetYesNoFunc, wk, _MENU_UG_PRI);
    CommMsgRegisterTargetName(CommUnderGetMsgUnderWorld(), CommInfoGetMyStatus(pAC->targetPCNetID));
    CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(),msg_underworld_67,
                                          FALSE,NULL);
    wk->ac.accessNetID = pAC->accessNetID;
    wk->ac.targetPCNetID = pAC->targetPCNetID;
    wk->ac.bFlagGet = pAC->bFlagGet;

    UgMgrSetNowTCB(wk, wk->pTCB, _flagGetTCBForceDel);  // �p�\�R�����j���[

}

//--------------------------------------------------------------
/**
 * @brief   �N���C�A���g����n�^�����w�߂����� CF_GET_FLAG
 * @param   FIELDSYS_WORK   �t�B�[���h�V�X�e�����[�N�|�C���^
 * @retval  none
 */
//--------------------------------------------------------------

void UgPcRecvFlagGet(int netID, int size, void* pData, void* pWork)
{
    _resultAccessCommand* pAC = pData;

    if(CommPlayerGetFlag(pAC->accessNetID, pAC->targetPCNetID)){   // �����Ƃ��Ă݂�
        CommSendFixSizeData_ServerSide(CF_GET_FLAG_RET, pAC);
    }
}

//--------------------------------------------------------------
/**
 * @brief   �N���C�A���g����n�^�����w�߂����� CF_GET_FLAG_RET
 * @param   FIELDSYS_WORK   �t�B�[���h�V�X�e�����[�N�|�C���^
 * @retval  none
 */
//--------------------------------------------------------------

void UgPcRecvFlagGetRet(int netID, int size, void* pData, void* pWork)
{
    FIELDSYS_WORK* pFSys = pWork;
    _resultAccessCommand* pAC = pData;
   //, CommUnderPCGetAccessSize,  NULL},  //CF_GET_FLAG_RET,   

    if(CommGetCurrentID() == pAC->accessNetID){
        CommMsgTalkWindowStart(CommUnderGetMsgUnderFlag(),mes_uw_flag_13, TRUE, _msgEndCallBack);
        Snd_BgmPlay( SEQ_HATANIGE );
    }
    // �����Ƃ����l�Ɋ�����
        
    CommPlayerGetFlag(pAC->accessNetID, pAC->targetPCNetID);
    // ���[�_�[���O
    UgSecretBaseSetFlagGetLog(pAC->accessNetID, pAC->targetPCNetID);
}




#ifdef PM_DEBUG

void Debug_UgFlagGet(void)
{
    _resultAccessCommand ac;

    ac.accessNetID = CommGetCurrentID();
    ac.targetPCNetID = COMM_PARENT_ID;
    ac.bFlagGet = TRUE;

    CommSendFixSizeData(CF_GET_FLAG, &ac);
}

#endif


static void UgListMoveSe( _START_WORK* pStart )
{
	u16 tmp_pos_bak;

	//BMP���X�g�̑S�̈ʒu���擾
	tmp_pos_bak = pStart->pos_bak;		//�ޔ�
	BmpListDirectPosGet( pStart->lw, &pStart->pos_bak );

	//�J�[�\�������������`�F�b�N
	if( tmp_pos_bak != pStart->pos_bak ){
		Snd_SePlay( SEQ_SE_DP_SELECT );
	}

	return;
}
