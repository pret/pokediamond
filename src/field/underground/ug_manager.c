//=============================================================================
/**
 * @file	ug_manager.c
 * @brief	�n���̒ʐM�֘A�̃v���O�������܂Ƃ߂�N���X
 * @author	Katsumi Ohno
 * @date    2005.11.18
 */
//=============================================================================

#include <nitro/os.h>
#include "common.h"
#include "gflib/blact.h"
#include "../map_tool.h"
#include "../floor_touch.h"
#include "../comm_command_field.h"
#include "ug_manager.h"

#include "../fieldobj.h"
#include "../eventdata.h"

#include "communication/communication.h"
#include "system/gamedata.h"
#include "system/bmp_menu.h"
#include "system/window.h"      //TalkWinGraphicSet
#include "system/pm_str.h"
#include "system/snd_tool.h"
#include "msgdata/msg.naix"
#include "system/wordset.h"
#include "system/arc_util.h"
#include "msgdata/msg_underworld.h"
#include "../fld_bmp.h"
#include "../script.h"
#include "system/clact_tool.h"
#include "../field_clact.h"
#include "../fld_comact.h"
#include "ug_local.h"
#include "ug_trap.naix"
#include "ug_shop.h"

#include "field/eventflag.h"
#include "../sysflag.h"

//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================

#include "../field_effect.h"	//DEBUG_BLACT_NEW_HOOK

//==============================================================================
// ��`
//==============================================================================

enum _radarDispType_e {
    _RADAR_NONE,   // �\�����Ȃ�
    _RADAR_NORMAL,   // ������㩂�\��
    _RADAR_STONE,   // �����̐΂�\��
    _RADAR_FOSSIL,   // �����̐΂�\��
    _RADAR_NATU_TRAP,   // ���R�Ǝ�����㩂�\��
    _RADAR_RANDOM_FOSSIL,  // ���܂ɉ��΂�\��
};




#define _TOUCH_INTERVAL_DOWN_TIME (30)  // �^�b�`�p�l����������Ԋu
#define _ABUTTON_INTERVAL_DOWN_TIME (8)  // �^�b�`�p�l����������Ԋu
#define _EVWIN_MSG_BUF_SIZE		(50*2)			//���b�Z�[�W�o�b�t�@�T�C�Y
#define _TOUCH_OBJ_MAX (8)
#define PRINTTASK_MAX (8)



typedef struct{
    void* pNowWork;  // ���N������bag,pc�̃��j���[
    TCB_PTR pNowTCB;  // ���N������bag,pc�̃��j���[
    ForceDeleteFunc pForceFunc;  // ���N������bag,pc�̃��j���[
    FIELDSYS_WORK* pFSys;
    UNDER_RECORD* pUnderRecord;
    TCB_PTR pPrintTCB;
    Grid TouchScr;
    Grid Touch;
    _RECORD_MENU_KEY recordKey[_KEY_RESERVE_BUFF];
    u16 openKeyName;
    u8 logTalk[COMM_MACHINE_MAX];
    u8 initEnd[COMM_MACHINE_MAX];
    u8 logTalkOther[COMM_MACHINE_MAX];
    STRBUF* logReturnBuff[COMM_MACHINE_MAX];
    u8 touchBuff1[_TOUCH_OBJ_MAX];
    u8 touchBuff2[_TOUCH_OBJ_MAX];
    u8 touchBuff3[_TOUCH_OBJ_MAX];
    PTRCommSearchFunc searchFunc;
    COMM_MESSAGE* pCommMsgUW;
    COMM_MESSAGE* pCommMsgFlag;
    COMM_MESSAGE* pCommMsgShop;
    COMM_MESSAGE* pCommMsgEdit;
    COMM_MESSAGE* pCommMsgItem;
    int searchLimit;

    int debugNum;

    u8 touchIntervalDownTimer;
    u8 connect[COMM_MACHINE_MAX];
    u8 logReturn[COMM_MACHINE_MAX];
    u8 intervalTimer;
    u8 abuttonNum;
    u8 radarDispType;
    u8 touchSize1;
    u8 touchSize2;
    u8 touchSize3;
    u8 bHalt;
    u8 bMessageSend;
} COMM_UNDER;


typedef struct{
    u8 bOpen;
    u8 netID;
    u8 targetID;
} _ugMenuOpen;

static COMM_UNDER* _pCommUnder = NULL;


static void _undergroundMsgTask( TCB_PTR tcb, void *work );



//==============================================================================
/**
 * ������
 * @param   pWork COMM_UNDER���[�N�|�C���^
 * @retval  none
 */
//==============================================================================

static void _initialize(COMM_UNDER* pWork,FIELDSYS_WORK* pFSys)
{
    u8 speed = CONFIG_GetMsgPrintSpeed(SaveData_GetConfig(pFSys->savedata));
    int i;
    
    _pCommUnder = pWork;
    MI_CpuFill8(_pCommUnder, 0, sizeof(COMM_UNDER));
    _pCommUnder->pFSys = pFSys;
    _pCommUnder->touchIntervalDownTimer = 0;
    _pCommUnder->Touch.xpos=0;
    _pCommUnder->Touch.zpos=0;
    _pCommUnder->bHalt=FALSE;
    _pCommUnder->radarDispType = _RADAR_NORMAL;

    _pCommUnder->pCommMsgUW =
        CommMsgInitialize(NARC_msg_underworld_dat, HEAPID_UNDERGROUND, pFSys->bgl,
                          speed, 500);
    _pCommUnder->pCommMsgFlag =
        CommMsgInitialize(NARC_msg_uwflag_dat, HEAPID_UNDERGROUND, pFSys->bgl,
                          speed, 0);
    _pCommUnder->pCommMsgShop =
        CommMsgInitialize(NARC_msg_uwbuy_dat, HEAPID_UNDERGROUND, pFSys->bgl,
                          speed, 1000);
    _pCommUnder->pCommMsgEdit =
        CommMsgInitialize(NARC_msg_uwedit_dat, HEAPID_UNDERGROUND, pFSys->bgl,
                          speed, 0);
    _pCommUnder->pCommMsgItem =
        CommMsgInitialize(NARC_msg_undergroundtrap_dat, HEAPID_UNDERGROUND, pFSys->bgl,
                          speed, 0);

    TalkWinGraphicSet(
        _pCommUnder->pFSys->bgl, GF_BGL_FRAME3_M, COMM_TALK_WIN_CGX_NUM,
        COMM_MESFRAME_PAL, WINTYPE_01, HEAPID_FIELD );
    ArcUtil_PalSet(ARC_UG_TRAP_GRA, NARC_ug_trap_ug_menu_NCLR, PALTYPE_MAIN_BG, FLD_MESFRAME_PAL*0x20, 4*0x20,  HEAPID_FIELD);
	MenuWinGraphicSet(
        _pCommUnder->pFSys->bgl, GF_BGL_FRAME3_M, MENU_WIN_CGX_NUM,
        MENU_WIN_PAL, MENU_TYPE_UG, HEAPID_FIELD );


    for(i = 0; i < COMM_MACHINE_MAX; i++){
        _pCommUnder->logTalk[i] = INVALID_NETID;
        _pCommUnder->logTalkOther[i] = INVALID_NETID;
        _pCommUnder->logReturnBuff[i] = NULL;//STRBUF_Create( _EVWIN_MSG_BUF_SIZE, HEAPID_COMMUNICATION );
    }

    SysFlag_UgArriveSet(SaveData_GetEventWork(_pCommUnder->pFSys->savedata));

    _pCommUnder->pPrintTCB = TCB_Add(_undergroundMsgTask,NULL, 0);  // �Y�z���[�_�[��葁��

    //  FLD_MESFONT_PAL
//        GX_LoadBGPltt(&pal,_NUKI_FONT_PALNO*0x20 + 2*14, 2);

/*
#define FLD_MESFRAME_PAL     ( 10 )         //  ���b�Z�[�W�E�C���h�E
#define FLD_MENUFRAME_PAL    ( 11 )         //  ���j���[�E�C���h�E
#define FLD_MESFONT_PAL      ( 12 )         //  ���b�Z�[�W�t�H���g
#define FLD_SYSFONT_PAL	     ( 13 )         //  �V�X�e���t�H���g
*/
    // �Â��t�H���g�p���b�g
}

//==============================================================================
/**
 * @brief �J��
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _finalize(void)
{
    int i;
    for(i = 0; i < COMM_MACHINE_MAX; i++){
        if(_pCommUnder->logReturnBuff[i]){
            STRBUF_Delete(_pCommUnder->logReturnBuff[i]);
        }
    }

    TCB_Delete(_pCommUnder->pPrintTCB);
    CommMsgFinalize(_pCommUnder->pCommMsgUW);
    CommMsgFinalize(_pCommUnder->pCommMsgFlag);
    CommMsgFinalize(_pCommUnder->pCommMsgShop);
    CommMsgFinalize(_pCommUnder->pCommMsgEdit);
    CommMsgFinalize(_pCommUnder->pCommMsgItem);
    _pCommUnder->pFSys->startmenu_pos = 0;		// ���j���[�ʒu�N���A

    sys_FreeMemoryEz(_pCommUnder);
    _pCommUnder = NULL;
}

//==============================================================================
/**
 * @brief   �n���ėp���b�Z�[�W�|�C���^��Ԃ�
 * @param   none
 * @retval  none
 */
//==============================================================================

COMM_MESSAGE* CommUnderGetMsgUnderWorld(void)
{
    return _pCommUnder->pCommMsgUW;
}

//==============================================================================
/**
 * @brief   �n���t���b�O���b�Z�[�W�|�C���^��Ԃ�
 * @param   none
 * @retval  none
 */
//==============================================================================

COMM_MESSAGE* CommUnderGetMsgUnderFlag(void)
{
    return _pCommUnder->pCommMsgFlag;
}

//==============================================================================
/**
 * @brief   �n��Shop���b�Z�[�W�|�C���^��Ԃ�
 * @param   none
 * @retval  none
 */
//==============================================================================

COMM_MESSAGE* CommUnderGetMsgUnderShop(void)
{
    return _pCommUnder->pCommMsgShop;
}

//==============================================================================
/**
 * @brief   �n��Edit���b�Z�[�W�|�C���^��Ԃ�
 * @param   none
 * @retval  none
 */
//==============================================================================

COMM_MESSAGE* CommUnderGetMsgUnderEdit(void)
{
    return _pCommUnder->pCommMsgEdit;
}

//==============================================================================
/**
 * @brief   �n���A�C�e���p���b�Z�[�W�|�C���^��Ԃ�
 * @param   none
 * @retval  none
 */
//==============================================================================

COMM_MESSAGE* CommUnderGetMsgUnderItem(void)
{
    return _pCommUnder->pCommMsgItem;
}



//==============================================================================
/**
 *  �o���Ă���Œ��̃��b�Z�[�W��؂�
 * @param   message   ���b�Z�[�W
 * @retval  ���b�Z�[�W������ꍇTRUE
 */
//==============================================================================

void CommUnderAllMsgForceDel(void)
{
    CommMsgPrintStop(_pCommUnder->pCommMsgUW);
    CommMsgPrintStop(_pCommUnder->pCommMsgFlag);
    CommMsgPrintStop(_pCommUnder->pCommMsgShop);
    CommMsgPrintStop(_pCommUnder->pCommMsgEdit);
    CommMsgPrintStop(_pCommUnder->pCommMsgItem);
}

//==============================================================================
/**
 *  �����ƃ^�[�Q�b�g���֌W���郍�O�𐶐�
 * @param   message   ���b�Z�[�W
 * @retval  ���b�Z�[�W������ꍇTRUE
 */
//==============================================================================

BOOL UgMgrRadarLogDouble(MYSTATUS* pMy, MYSTATUS* pTarget, int msgNo, STRBUF* pStrBuf)
{
    WORDSET* pWordSetMain;  //���[�h�Z�b�g�\����
    STRBUF* tmp_buf1;

    if(pMy && pTarget){
        pWordSetMain = WORDSET_Create(HEAPID_FIELD);
        tmp_buf1 = STRBUF_Create( _EVWIN_MSG_BUF_SIZE, HEAPID_FIELD );
        WORDSET_RegisterPlayerName( pWordSetMain, 0, pMy);
        WORDSET_RegisterPlayerName( pWordSetMain, 1, pTarget);
        MSGMAN_GetString( CommMsgGetMsgManager(CommUnderGetMsgUnderWorld()), msgNo, tmp_buf1 );
        WORDSET_ExpandStr( pWordSetMain, pStrBuf, tmp_buf1 );
        STRBUF_Delete( tmp_buf1 );
        WORDSET_Delete(pWordSetMain);
        return TRUE;
    }
    return FALSE;
}

//==============================================================================
/**
 *  �������֌W���郍�O�𐶐�
 * @param   message   ���b�Z�[�W
 * @retval  ���b�Z�[�W������ꍇTRUE
 */
//==============================================================================

BOOL UgMgrRadarLogSingle(MYSTATUS* pMy, int index, int msgNo, STRBUF* pStrBuf)
{
    WORDSET* pWordSetMain;  //���[�h�Z�b�g�\����
    STRBUF* tmp_buf1;

    if(pMy){
        pWordSetMain = WORDSET_Create(HEAPID_FIELD);
        tmp_buf1 = STRBUF_Create( _EVWIN_MSG_BUF_SIZE, HEAPID_FIELD );
        WORDSET_RegisterPlayerName( pWordSetMain, index, pMy);
        MSGMAN_GetString( CommMsgGetMsgManager(CommUnderGetMsgUnderWorld()), msgNo, tmp_buf1 );
        WORDSET_ExpandStr( pWordSetMain, pStrBuf, tmp_buf1 );
        STRBUF_Delete( tmp_buf1 );
        WORDSET_Delete(pWordSetMain);
        return TRUE;
    }
    return FALSE;
}


//==============================================================================
/**
 *  �n���ɓ����Ă����󋵃��b�Z�[�W��Ԃ�
 * @param   message   ���b�Z�[�W
 * @retval  ���b�Z�[�W������ꍇTRUE
 */
//==============================================================================

static BOOL _underGetEnterMessage(STRBUF* pStrBuf)
{
    int i;
    WORDSET* pWordSetMain;  //���[�h�Z�b�g�\����
    STRBUF* tmp_buf1;
    MYSTATUS* pMy;
    MYSTATUS* pTarget;

    if(!_pCommUnder){
        return FALSE;
    }
    
    for(i = 0; i< COMM_MACHINE_MAX; i++){
        if(CommInfoIsNewName( i )){
            pMy = CommInfoGetMyStatus(i);
            CommInfoSetMessageEnd( i );
            if(UgMgrRadarLogSingle(pMy,TARGET_PLAYER_WORD_IDX,UGEnter,pStrBuf)){
                return TRUE;
            }
        }
        if(_pCommUnder->logTalk[i] != INVALID_NETID){
            pMy = CommInfoGetMyStatus(i);
            pTarget = CommInfoGetMyStatus(_pCommUnder->logTalk[i]);
            _pCommUnder->logTalk[i] = INVALID_NETID;
            if(UgMgrRadarLogDouble(pMy,pTarget,UGtalk01,pStrBuf)){
                return TRUE;
            }
        }
        if(_pCommUnder->logTalkOther[i] != INVALID_NETID){
            pMy = CommInfoGetMyStatus(i);
            _pCommUnder->logTalkOther[i] = INVALID_NETID;
            if(UgMgrRadarLogSingle(pMy, 0, UGtalk02, pStrBuf)){
                return TRUE;
            }
        }
        if(_pCommUnder->logReturn[i] == TRUE){
            if(_pCommUnder->logReturnBuff[i]){
                STRBUF_Copy(pStrBuf,_pCommUnder->logReturnBuff[i]);
                STRBUF_Delete( _pCommUnder->logReturnBuff[i] );
                _pCommUnder->logReturnBuff[i]=NULL;
                _pCommUnder->initEnd[i] = FALSE;
            }
            _pCommUnder->logReturn[i] = FALSE;
            return TRUE;
        }
    }
    return FALSE;
}

//==============================================================================
/**
 * �����ɉ������u���Ă��邩�ǂ���������
 * @param   x
 * @param   y
 * @retval  �u���Ă���ꍇTRUE
 */
//==============================================================================

BOOL CommUnderCheckPlace(int x,int z)
{
    Grid pos;

    pos.xpos = x;
    pos.zpos = z;
    
    if(GetHitAttr(_pCommUnder->pFSys,x,z)){  // �����肪����ꍇ
       // �z�u�ł��Ȃ�
        return TRUE;
    }

    if(CommTrapCheck(x,z)){
        return TRUE;
    }
    // �q�~�c��n��������u���Ă��邩�ǂ���

    // ���܂����܂��Ă��邩�ǂ���
    // �����������܂��Ă��邩�ǂ���

    // �p�\�R�������邩�ǂ���
    if(CommUnderPCCheck(&pos,-1) != INVALID_NETID){
        return TRUE;
    }
    
    return FALSE;
}

//==============================================================================
/**
 * �^�b�`�p�l���Ń^�b�`�����ʒu�𑗐M
 * @param   none
 * @retval  �����J�n=TRUE
 */
//==============================================================================

BOOL UgMgrTouchCheck(void)
{
    VecFx32 vec;
    FIELD_OBJ_PTR fldobj;
    int xGrid,yGrid;
    Grid pos;

    if((_pCommUnder->abuttonNum != 0) && (_pCommUnder->touchIntervalDownTimer!=0)){ // �A�ł���ƃL���[�����ӂ�₷����
        return FALSE;
    }
    if(sys.tp_trg){
        _pCommUnder->touchIntervalDownTimer = _TOUCH_INTERVAL_DOWN_TIME;
        if(!_pCommUnder->bHalt){
            if(CommPlayerIsMyMoveControl() && !CommPlayerIsTrapBind(CommGetCurrentID())){
            // �^�b�`�p�l�����M
                if(CommIsError()){
                    OHNO_PRINT("�G���[���͑��M���Ȃ�\n");
                    return FALSE;
                }
                if(0!=CommPlayerGetWalkCount(CommGetCurrentID())){  // �ړ����ĂȂ�����������
                    return FALSE;
                }
                vec = FTouch_CalcTpXYTo3D(sys.tp_x, sys.tp_y, _pCommUnder->pFSys->TpTo3DPtr);
                GetGridXZ(vec.x, vec.z, &xGrid, &yGrid);
                pos.xpos = xGrid;
                pos.zpos = yGrid;
                OHNO_PRINT("Touch %d %d\n", xGrid, yGrid);
                _pCommUnder->TouchScr.xpos = sys.tp_x;
                _pCommUnder->TouchScr.zpos = sys.tp_y;
                _pCommUnder->Touch.xpos = xGrid;
                _pCommUnder->Touch.zpos = yGrid;
                CommSendData(CF_TOUCH_GROUND, &pos, sizeof(Grid));
//                Snd_SePlay(UG_SE_RADAR);
                return TRUE;
            }
        }
    }
    if(_pCommUnder->touchIntervalDownTimer > 0){
        _pCommUnder->touchIntervalDownTimer--;
    }
    return FALSE;
}

//==============================================================================
/**
 *  �w��͈͓��̏ꏊ�ɉ�����������o�b�t�@�ɓ����
 * @param   netID    ���M���Ă���ID
 * @param   size     �����Ă����f�[�^�T�C�Y
 * @param   pData    �f�[�^�{�̂̃|�C���^
 * @retval  none
 */
//==============================================================================

typedef BOOL (*_CheckFunc)(int xp, int zp);

static int _getTouchPosBuff(u8* pResultBuff, _CheckFunc func, Grid* pTouch)
{
    NearHexWork work;
    NearHex hex;
    int j=1;
    int x,z,xp,zp;

    x = pTouch->xpos - 6;
    z = pTouch->zpos - 6;
    NearHexInitialize(&work, 6);
    while(NearHexGetHex(&work, &hex)){
        xp = pTouch->xpos + hex.xpos;
        zp = pTouch->zpos + hex.zpos;
        if(func(xp, zp)){
            pResultBuff[j] = (xp - x) + (zp - z) * 16;
            if(j == _TOUCH_OBJ_MAX){
                j++;
                break;
            }
            j++;
        }
    }
    return j;
}

//==============================================================================
/**
 *  �^�b�`�����f�[�^���T�[�o�[�ɓ͂����̂Ł@�^�b�`�f�[�^��Ԃ�
 * @param   netID    ���M���Ă���ID
 * @param   size     �����Ă����f�[�^�T�C�Y
 * @param   pData    �f�[�^�{�̂̃|�C���^
 * @retval  none
 */
//==============================================================================

static void _ugTouchCheck(int netID, Grid* pTouch)
{
    u8 resultBuff[_TOUCH_OBJ_MAX+1];
    NearHexWork work;
    NearHex hex;
    int j=1;
    int x,z,xp,zp;
    
    resultBuff[0] = netID;  // ����������ɑ���Ԃ�

    j = _getTouchPosBuff(resultBuff, CommTrapCheck, pTouch);
    CommSendData_ServerSide(CF_TOUCH_RESULT1, resultBuff, j);
    j = _getTouchPosBuff(resultBuff, UGFossileCheck, pTouch);
    CommSendData_ServerSide(CF_TOUCH_RESULT2, resultBuff, j);
}


//==============================================================================
/**
 *  �^�b�`�����f�[�^���T�[�o�[�ɓ͂����̂Ł@㩂�Ԃ�  CF_TOUCH_GROUND
 * @param   netID    ���M���Ă���ID
 * @param   size     �����Ă����f�[�^�T�C�Y
 * @param   pData    �f�[�^�{�̂̃|�C���^
 * @retval  none
 */
//==============================================================================

void CommTrapInfoRecvTouch(int netID, int size, void* pData, void* pWork)
{
    Grid* pTouch = pData;

    if(!CommPlayerGetMoveControl(netID)){
        return;
    }
    if(CommPlayerIsTrapBind(netID)){
        return;
    }
    CommPlayerSetMoveControl_Server(netID,FALSE);
    _ugTouchCheck(netID, pTouch);
}

//==============================================================================
/**
 *  �^�b�`�f�[�^���͕\���f�[�^�󂯎��
 * @param   none
 * @retval  �T�C�Y
 */
//==============================================================================

void UgManagerRecvTouchResult1(int netID, int size, void* pData, void* pWork)
{
    int i;
    u8* pBuff = pData;
    Grid grid;

    if(CommGetCurrentID() != pBuff[0]){
        return;   // �قȂ�q�@�͎󂯎��Ȃ�
    }
    MI_CpuCopy8(&pBuff[1],_pCommUnder->touchBuff1,size-1);
    _pCommUnder->touchSize1 = size-1;
}


//==============================================================================
/**
 *  �^�b�`�f�[�^���͕\���f�[�^�󂯎��  CF_TOUCH_RESULT2
 * @param   none
 * @retval  �T�C�Y
 */
//==============================================================================

void UgManagerRecvTouchResult2(int netID, int size, void* pData, void* pWork)
{
    int i;
    u8* pBuff = pData;
    Grid grid;
    u8 dummyBuf[9];

    if(CommGetCurrentID() != pBuff[0]){
        return;   // �قȂ�q�@�͎󂯎��Ȃ�
    }
    MI_CpuCopy8(&pBuff[1],_pCommUnder->touchBuff2,size-1);
    _pCommUnder->touchSize2 = size-1;

    _pCommUnder->touchSize3 = _getTouchPosBuff(dummyBuf,
                                               UgStoneCheck,&_pCommUnder->Touch);
    _pCommUnder->touchSize3 -= 1;
    MI_CpuCopy8(&dummyBuf[1],_pCommUnder->touchBuff3,_pCommUnder->touchSize3);
    UgTouchRadarStart(_pCommUnder->pFSys,
                      _pCommUnder->Touch.xpos,_pCommUnder->Touch.zpos,
                      _pCommUnder->TouchScr.xpos,_pCommUnder->TouchScr.zpos,
                      _pCommUnder->touchBuff1,_pCommUnder->touchSize1,
                      _pCommUnder->touchBuff2,_pCommUnder->touchSize2,
                      _pCommUnder->touchBuff3,_pCommUnder->touchSize3
                      );
}

#define _UG_BLOCK_MAX (30)

//==============================================================================
/**
 * item��xz�̑傫����]������
 * @param   x
 * @param   y
 * @retval  �u���Ă���ꍇTRUE
 */
//==============================================================================

static int _itemXZ(Grid* pGrid)
{
    int x = 0,z = 0;

    if(pGrid==NULL){
        return _UG_BLOCK_MAX * _UG_BLOCK_MAX * BLOCK_GRID_W * BLOCK_GRID_H;
    }
    x = pGrid->xpos;
    z = pGrid->zpos;
    return (z * _UG_BLOCK_MAX * BLOCK_GRID_W) +x;
}

//==============================================================================
/**
 * item��match���邩�ǂ�����������
 * @param   pGrid �����������ʒu
 * @retval  �u���Ă���ꍇindex
 */
//==============================================================================

int CommUnderMatchItemTbl(Grid* pGrid)
{
    int mid;
    int left = 0;
    int right = _pCommUnder->searchLimit-1;
    int xIndex = _itemXZ(pGrid);
    Grid grid;
    PTRCommSearchFunc func = _pCommUnder->searchFunc;

    while(left < right){
        mid = (left + right) / 2;
        if(_itemXZ(func(&grid, mid)) < xIndex){
            left = mid+1;
        }
        else{
            right = mid;
        }
    }
    if(_itemXZ(func(&grid, left)) == xIndex){
        return left;
    }
    return -1;
}


//==============================================================================
/**
 * �����e�[�u������w��̃A�C�e��������
 * @param   none
 * @retval  �T�C�Y
 */
//==============================================================================

int CommUnderSearchItemTbl(Grid* pGrid)
{
    int mid;
    int left = 0;
    int right = _pCommUnder->searchLimit-2;
    int xIndex = _itemXZ(pGrid);
    PTRCommSearchFunc func = _pCommUnder->searchFunc;
    Grid grid;

//    OHNO_PRINT("�ŏ���index %d  %d \n",xIndex,_itemXZ(NULL));
    right++;
    while(left < right){
        mid = (left + right) / 2;
        if(_itemXZ(func(&grid, mid)) < xIndex){
            left = mid + 1;
        }
        else{
            right = mid;
        }
    }
    return left;
}

//==============================================================================
/**
 * �A�C�e����������ꍇ�̏�����
 * @param   limit   �e�[�u���̌��E
 * @param   pFunc   �e�[�u���ɃA�N�Z�X���邽�߂̊֐�
 * @retval  none
 */
//==============================================================================

void CommUnderItemSearchInitialize(int limit, PTRCommSearchFunc pFunc)
{
    _pCommUnder->searchFunc = pFunc;
    _pCommUnder->searchLimit = limit;
}

//--------------------------------------------------------------
/**
 * @brief   �q�@�Ń��j���[�{�^���������ꂽ�̂ŃR�}���h���M
 * @param   bTalkCheck
 * @retval  none
 */
//--------------------------------------------------------------

void UgMgrMenuCheck(void)
{
    if(0==CommPlayerGetWalkCount(CommGetCurrentID())){
        CommSendFixData(CF_CHECK_FIELDMENU_OPEN);
        CommActionCommandSet();
    }
}

//--------------------------------------------------------------
/**
 * @brief   A�{�^���̃C���^�[�o���^�C�}�[
 * @param   bTalkCheck
 * @retval  none
 */
//--------------------------------------------------------------

void UgMgrKeyCountDown(void)
{
    if(_pCommUnder->abuttonNum != 0){ // �A�ł���ƃL���[�����ӂ�₷����
        _pCommUnder->abuttonNum--;
    }
}

//--------------------------------------------------------------
/**
 * @brief   �q�@��A�{�^���������ꂽ�̂ŃR�}���h���M
 * @param   bTalkCheck
 * @retval  none
 */
//--------------------------------------------------------------

typedef struct{
    u8 bit;
    u8 posXZ;
} _resultAbutton;


void UgMgrTalkCheck(u8 bTalkCheck)
{
    u8 bit = bTalkCheck;
    _resultAbutton aRet;
    int x,z;
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(_pCommUnder->pFSys->savedata);

    if((_pCommUnder->abuttonNum != 0) && (_pCommUnder->touchIntervalDownTimer!=0)){ // �A�ł���ƃL���[�����ӂ�₷����
        return;
    }
    if(0!=CommPlayerGetWalkCount(CommGetCurrentID())){  // �ړ����ĂȂ���
        return;
    }

    
    if(UG_ITEM_BAG_NUM_MAX == UnderGroundGetNumTrapBagItem(pUGData)){
        bit = bit | _NOTGET_TRAP_RESERVE;  // 㩂������ς��Ȃ̂ŏE���Ȃ�
    }
    x = CommPlayerGetPosXDirAdd(CommGetCurrentID());
    z = CommPlayerGetPosZDirAdd(CommGetCurrentID());
    if(UgStoneCheck(x,z)){
        bit = bit | _GET_STONE_RESERVE;  // �΂��E���i�\��j
        OS_TPrintf("talkcheck %d %d\n",x,z);
    }
    aRet.bit = bit;
    aRet.posXZ = (x & 0xf) * 16 + (z & 0x0f);
    CommSendFixSizeData(CF_CHECK_ABUTTON_ACTION, &aRet);
    CommActionCommandSet();
    _pCommUnder->abuttonNum = _ABUTTON_INTERVAL_DOWN_TIME;
}

/*
   �R�}���h�̑傫��
 */
int CommUnderRecvCheckAbuttonSize(void)
{
    return sizeof(_resultAbutton);
}

//--------------------------------------------------------------
/**
 * @brief   �q�@��A�{�^���������ꂽ���̃R�[���o�b�N  CF_CHECK_ABUTTON_ACTION
 * @param   netID
 * @param   size
 * @param   pData
 * @param   pWork
 * @retval  none
 */
//--------------------------------------------------------------

void CommUnderRecvCheckAbutton(int netID, int size, void* pData, void* pWork)
{
    _ugMenuOpen menuOpen;
    _resultAbutton* pRet = pData;
    Grid pos;
    int targetID;
    u8 id;

    id = netID;
    pos.xpos = CommPlayerGetPosSXDirAdd(netID);
    pos.zpos = CommPlayerGetPosSZDirAdd(netID);

    if(netID == 2){
        OHNO_PRINT("CommPlayerGetMoveControl %d \n",CommPlayerGetMoveControl(netID));
    }

    if( (CommPlayerGetPosSX(netID) == COMM_PLAYER_INVALID_GRID) &&
        ( CommPlayerGetPosSZ(netID) == COMM_PLAYER_INVALID_GRID)){
        // ���W�s��̏ꍇ���̎���A�{�^���̕Ԏ���Ԃ��Ȃ�
        return;
    }

    if(!CommPlayerGetMoveControl(netID)){
        // �������g�����łɖZ�����ꍇ������B���̎���A�{�^���̕Ԏ���Ԃ��Ȃ�
        return;
    }
    if(CommPlayerIsTrapBind(netID)){
        return;
    }
    // �ڂ̑O�Ƀv���[���[�����邩�ǂ���
    targetID = CommPlayerIsAlive(pos.xpos, pos.zpos);
    if(targetID != COMM_INVALID_ID){
        if(CommSecretBaseIsTraveling(targetID)){ // �ړ����̑���ɂ͎�o���ł��Ȃ�
            OHNO_PRINT("��n�ړ���\n");
        }
        else if(UgDigFossilIsDig(targetID)){
            menuOpen.bOpen = _RESULT_FOSSIL;
            menuOpen.targetID = targetID;
            menuOpen.netID = netID;
            CommSendData_ServerSide(CF_RESULT_UGMENU_OPEN, &menuOpen, sizeof(menuOpen));
            CommPlayerSetMoveControl_Server(netID,FALSE);
        }
        else if(CommPlayerFlagTalkCheck(netID, targetID, 0)){ // ���������������Ă�����Ȃɂ����Ȃ�
        }
        else if(CommPlayerIsTrapBind(targetID)){  // 㩂ɂ������Ă���ꍇ����
            if(!CommTrapIsGoodsTrap(targetID)){
                CommTrapSendRelease(netID,targetID);  // �����R�}���h���M
            }
            else{
                menuOpen.bOpen = _RESULT_NG;
                menuOpen.targetID = targetID;
                menuOpen.netID = netID;
                CommSendData_ServerSide(CF_RESULT_UGMENU_OPEN, &menuOpen, sizeof(menuOpen));
                CommPlayerSetMoveControl_Server(netID,FALSE);
            }
        }
        else if(!CommPlayerGetMoveControl(netID)){
            // �������g�����łɖZ�����ꍇ������B���̎��͕Ԏ���Ԃ��Ȃ�
        }
        else if(!CommPlayerGetMoveControl(targetID) || (0!=CommPlayerGetWalkCountServer(targetID))){
            // ���肪�Z�����ꍇ�͘b���������Ȃ�
            menuOpen.bOpen = _RESULT_NG;
            menuOpen.targetID = targetID;
            menuOpen.netID = netID;
            CommSendData_ServerSide(CF_RESULT_UGMENU_OPEN, &menuOpen, sizeof(menuOpen));
            CommPlayerSetMoveControl_Server(netID,FALSE);
        }
        else{  // �b���������j���[
            menuOpen.bOpen = _RESULT_OK;
            menuOpen.targetID = targetID;
            menuOpen.netID = netID;
            if(CommPlayerGetMoveControl(targetID)){
                if(CommSendData_ServerSide(CF_RESULT_UGMENU_OPEN, &menuOpen, sizeof(menuOpen))){
                    CommPlayerSetMoveControl_Server(netID, FALSE);
                    CommPlayerSetMoveControl_Server(targetID, FALSE);
                    CommPlayerSetLook_Server(netID, targetID);
                }
            }
        }
        return;
    }
    // 㩌��� �ڂ̑O��㩂�����ꍇ��������
    if(CommTrapFrontTrapDefuse(netID, &pos, pRet->bit)){
        CommPlayerSetMoveControl_Server(netID,FALSE);
        return;
    }
    if(CommFossilCheck(netID, &pos)){  // ���Δ���
        OHNO_PRINT("���Δ���\n");
        CommPlayerSetMoveControl_Server(netID,FALSE);
        return;
    }
    if(CommUnderPCCheckAndMessage(netID, &pos)){  // �p�\�R���̑O������
        CommPlayerSetMoveControl_Server(netID,FALSE);
        return;
    }
    if(UgSecretBaseGoodsCheck(netID, &pos)){  // �ڂ̑O�ɃO�b�Y��������
        CommPlayerSetMoveControl_Server(netID,FALSE);
        return;
    }
    if(CommPlayerNPCHitCheck(pos.xpos,pos.zpos)){
        if(CommPlayerFlagTalkCheck(netID, INVALID_NETID, 0)){ // ���������������Ă�����Ȃɂ����Ȃ�
            return;
        }
        CommSendFixSizeData_ServerSide(CF_NPC_TALK,&id);
        CommPlayerSetMoveControl_Server(netID,FALSE);
        return;
    }
    if(pRet->bit & _GET_STONE_RESERVE ){
        if(CommPlayerFlagDigCheck(netID)){   // �����̊�����
            return;
        }
        // �ȈՈʒu�`�F�b�N server������Ă���Ȃ�
        if(pRet->posXZ == (pos.xpos & 0xf) * 16 + (pos.zpos & 0x0f)){
            CommSendFixSizeData_ServerSide(CF_DIG_STONE_PICKUP,&id);
            CommPlayerSetMoveControl_Server(netID,FALSE);
        }
    }
}

//==============================================================================
/**
 * �n���֘A�T�[�r�X����
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommUnderProcess(void)
{
    int i;

    if(CommGetCurrentID() == COMM_PARENT_ID){
        for(i = 0; i < COMM_MACHINE_MAX; i++){
            if((NULL!=CommInfoGetMyStatus(i)) && !_pCommUnder->connect[i]){
                UgSecretBaseResetPlayer(i);  // �t���OOFF
            }
            if(CommInfoGetMyStatus(i)){
                _pCommUnder->connect[i] = TRUE;
            }
            else{
                _pCommUnder->connect[i] = FALSE;
            }
        }
        // �l������
        CommStateSetLimitNum( CommUgGetChildStateNormalNum()+2 );

    }
    _pCommUnder->intervalTimer++;
    if(CommGetCurrentID() == COMM_PARENT_ID){
        if(CommInfoSendArray_ServerSide()){  // �q�@����₢���킹����������info�𑗐M
//            UgSecretBaseResetPlayer(COMM_PARENT_ID);  // �����l���閧��n�ړ����Ă������͗v��Ȃ�
            CommPlayerSendPos(TRUE);
        }
    }

    CommDigStoneStep();
    CommTrapInfoProcess();  // 㩂�1/256�ŕ\������ׂ̏���
    UgFossilProcess();

    if(!_pCommUnder->bHalt){  // ������������ HALT���ɂ͓��삵�Ȃ�
        UgTrapProcess(_pCommUnder->pFSys->bgl);   // 㩂����������ꍇ�̎��s����
    }


}

//==============================================================================
/**
 * �n���֘A�T�[�r�X�̏�����   �풓��������̂͂����ŏ���������
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommUnderOptionInitialize(FIELDSYS_WORK* pFSys)
{
    void* pWork;

    if(_pCommUnder==NULL){
        pWork = sys_AllocMemory(HEAPID_COMMUNICATION, sizeof(COMM_UNDER));
        _initialize(pWork,pFSys);
        pWork = sys_AllocMemory(HEAPID_COMMUNICATION, CommPlayerGetWorkSize());
        CommPlayerManagerInitialize(pWork, pFSys, TRUE);
        pWork = sys_AllocMemory(HEAPID_COMMUNICATION, CommTrapInfoGetWorkSize());
        CommTrapInfoInitialize(pWork, pFSys);
        pWork = sys_AllocMemory(HEAPID_COMMUNICATION, CommSecretBaseInfoGetWorkSize());
        CommSecretBaseInfoInitialize(pWork, pFSys);
        pWork = sys_AllocMemory(HEAPID_COMMUNICATION, CommDigStoneManagerGetWorkSize());
        CommDigStoneInitialize(pWork, pFSys);
        pWork = sys_AllocMemory(HEAPID_COMMUNICATION, CommFossilGetWorkSize());
        CommFossilInitialize(pWork, pFSys);
        pWork = sys_AllocMemory(HEAPID_COMMUNICATION, UnderRecordGetWorkSize());
        UnderRecordInitialize(pWork, SaveData_GetSecretBaseRecord(GameSystem_GetSaveData(pFSys)), GameSystem_GetSaveData(pFSys));
        CommUnderBagInitialize(SaveData_GetUnderGroundData(GameSystem_GetSaveData(pFSys)));
    }
}


void CommUnderOptionReset(void)
{
    if(_pCommUnder){
        UnderRecordReset();
        CommDigStoneManagerReset();
        CommSecretBaseInfoReset();
        CommTrapInfoReset();
        CommPlayerManagerReset();
        CommFossilReset();
        CommUnderAllMsgForceDel();
        _pCommUnder->bHalt=TRUE;
    }
}

void CommUnderOptionReboot(void)
{
    if(_pCommUnder){
        CommPlayerManagerReboot();
        UnderRecordReboot();
        CommDigStoneManagerReboot();
        CommSecretBaseInfoReboot();
        CommTrapInfoReboot();
        CommFossilReboot();
        _pCommUnder->bHalt=FALSE;
        
        TalkWinGraphicSet(
            _pCommUnder->pFSys->bgl, GF_BGL_FRAME3_M, COMM_TALK_WIN_CGX_NUM,
            COMM_MESFRAME_PAL, WINTYPE_01, HEAPID_FIELD );
    }
}


void CommUnderOptionFinalize(void)
{
    if(_pCommUnder!=NULL){
        UnderGroundDataAfterUG(_pCommUnder->pFSys->savedata);
        CommSecretBaseInfoFinalize();
        CommTrapInfoFinalize();
        CommPlayerManagerFinalize(TRUE);
        CommDigStoneFinalize();
        CommFossilFinalize();
        CommUnderBagFinalize();
        UnderRecordFinalize();
        _finalize();
    }
}

//==============================================================================
/**
 * @brief   �e�@�A�q�@�ؒf���ɌĂ΂�� RESET�֐�
 * @param   
 * @retval  
 */
//==============================================================================

void CommUnderOptionReInit(FIELDSYS_WORK* pFSys)
{
    void* pWork;

    if(_pCommUnder!=NULL){
        CommTrapInfoReInit(pFSys);
        CommPlayerManagerReInit();
        CommSecretBaseInfoReInit();
        
    }
}

//==============================================================================
/**
 * @brief   �A�N�V�����֌W�̃��b�Z�[�W�������o���B �����o������Ȃ��Ȃ�
 * @param   pMessage    ���b�Z�[�W���i�[����̈���������|�C���^
 * @retval  �����Ȃ����FALSE
 */
//==============================================================================

BOOL CommUnderGetActionMessage(STRBUF* pStrBuf)
{
    if(_pCommUnder->bMessageSend){  // ���ɂ��ЂƂ�
        _pCommUnder->bMessageSend=FALSE;
        return FALSE;
    }
    if(_underGetEnterMessage(pStrBuf)){
        _pCommUnder->bMessageSend=TRUE;
        return TRUE;
    }
    else if(CommTrapGetActionMessage(pStrBuf)){
        _pCommUnder->bMessageSend=TRUE;
        return TRUE;
    }
    else if(CommTrapSetActionMessage(pStrBuf)){
        _pCommUnder->bMessageSend=TRUE;
        return TRUE;
    }
    else if(CommSecretBaseInfoGetActionMessage(pStrBuf)){
        _pCommUnder->bMessageSend=TRUE;
        return TRUE;
    }
    else if(UgDigFossilGetActionMessage(pStrBuf)){
        _pCommUnder->bMessageSend=TRUE;
        return TRUE;
    }
    else if(UgDigStoneGetActionMessage(pStrBuf)){
        _pCommUnder->bMessageSend=TRUE;
        return TRUE;
    }
    return FALSE;
}

//  �n�����I�[�o�[���C�����̂Ł@�@���̃A�N�Z�X�֐��������ɂ���

//==============================================================================
/**
 * @brief   ������Z�b�g�A�b�v����閧��n�O�b�Y�f�[�^��Ԃ�
 * @param   sv  SAVEDATA*
 * @retval  SECRETBASEDATA*
 */
//==============================================================================

SECRETBASEDATA* UgManUgSetupSecretBaseData(SAVEDATA * sv)
{
    if(!_pCommUnder){
        return NULL;
    }
    return UgSetupSecretBaseData(sv);
}

//==============================================================================
/**
 * @brief   ������Z�b�g�A�b�v����閧��n��X�u���b�N��Ԃ�
 * @param   none
 * @retval  X�O���b�h
 */
//==============================================================================

int UgManUgSetupSecretBaseBlockX(void)
{
    if(!_pCommUnder){
        return 0;
    }
    OHNO_SP_PRINT("UgSetupSecretBaseBlockX %d\n",UgSetupSecretBaseBlockX());
    return UgSetupSecretBaseBlockX();
}

//==============================================================================
/**
 * @brief   ������Z�b�g�A�b�v����閧��n��Z�u���b�N��Ԃ�
 * @param   none
 * @retval  Z�O���b�h
 */
//==============================================================================

int UgManUgSetupSecretBaseBlockZ(void)
{
    if(!_pCommUnder){
        return 0;
    }
    OHNO_SP_PRINT("UgSetupSecretBaseBlockZ %d\n",UgSetupSecretBaseBlockZ());
    return UgSetupSecretBaseBlockZ();
}

//==============================================================================
/**
 * @brief   �閧��n���W�ɂ��邩�ǂ�����Ԃ�
 * @param   x,z    ���ׂ���XZ���W
 * @retval  �閧��n�ɂ���ꍇTRUE
 */
//==============================================================================

BOOL UgSecretBaseIsSecretBasePlace(int x, int z)
{
    if((RADAR_SCOPE_XS < x) && (RADAR_SCOPE_ZS < z) && (RADAR_SCOPE_XE > x) && (RADAR_SCOPE_ZE > z)){ 			//���W���擾�ł����Ȃ���W�ƍX�V
        return FALSE;
    }
    return TRUE;
}

//--------------------------------------------------------------
/**
 * ���[�_�[�ɕ\�����������W��Ԃ�
 * @param    index
 * @retval   X���W
 */
//--------------------------------------------------------------

int UgMgrGetDispPointX(int index)
{
    int val,i;
    
    if(_pCommUnder){
        if(index < 16 ){  //�������
            i = index;
            switch(_pCommUnder->radarDispType){
              case _RADAR_NONE:
                return 0;
              case _RADAR_NORMAL:
                if(index < 8){
                    return UgFossilGetIntervalRadarPointX(i);
                }
              case _RADAR_STONE:
                return UgStoneGetRadarStoneX(i);
              case _RADAR_NATU_TRAP:
                return UgTrapGetNatureTrapX(i);
              case _RADAR_FOSSIL:
                return UgFossilGetRadarPointX(i);
            }
        }
        else{  // �閧��n
            SECRETBASEDATA* pSecret = SaveData_GetSecretBaseData(_pCommUnder->pFSys->savedata);
            return SecretBaseGetSecretBasePositionX(pSecret);
        }
    }
    return 0;
}

//--------------------------------------------------------------
/**
 * ���[�_�[�ɕ\�����������W��Ԃ�
 * @param    index
 * @retval   Z���W
 */
//--------------------------------------------------------------

int UgMgrGetDispPointZ(int index)
{
    int val,i, num;
    
    if(_pCommUnder){
        if(index < 16 ){  //�������
            i = index;
            switch(_pCommUnder->radarDispType){
              case _RADAR_NONE:
                return 0;
              case _RADAR_NORMAL:
                if(index < 8){
                    return UgFossilGetIntervalRadarPointZ(i);
                }
              case _RADAR_STONE:
                return UgStoneGetRadarStoneZ(i);
              case _RADAR_NATU_TRAP:
                return UgTrapGetNatureTrapZ(i);
              case _RADAR_FOSSIL:
                return UgFossilGetRadarPointZ(i);
            }
        }
        else{  // �閧��n
            SECRETBASEDATA* pSecret = SaveData_GetSecretBaseData(_pCommUnder->pFSys->savedata);
            return SecretBaseGetSecretBasePositionZ(pSecret);
        }
    }
    return 0;
}

//--------------------------------------------------------------
/**
 * ���[�_�[�ɕ\������������Ԃ�
 * @param    index
 * @retval   RADAR_DISP_TYPE_ENUM  ug_manager.h�Q��
 */
//--------------------------------------------------------------

int UgMgrGetDispPointInfo(int index)
{
    if(_pCommUnder){
        if(index < 16 ){
            switch(_pCommUnder->radarDispType){
              case _RADAR_NORMAL:
                if(index < 8){
                    return RADAR_TYPE_FOSSIL;
                }
              case _RADAR_STONE:
                return RADAR_TYPE_BALL;
              case _RADAR_NATU_TRAP:
                return RADAR_TYPE_TRAP_NATURAL;
              case _RADAR_FOSSIL:
                return RADAR_TYPE_FOSSIL;
            }
        }
        else{  // �閧��n
            SECRETBASEDATA* pSecret = SaveData_GetSecretBaseData(_pCommUnder->pFSys->savedata);
            if( SecretBaseIsSecretBaseMake(pSecret)){
                return RADAR_TYPE_SECLETBASE;
            }
        }
    }
    return RADAR_TYPE_NONE;
}




//--------------------------------------------------------------
/**
 * ���[�_�[�ɉ����\�������Ȃ�
 * @param    none
 * @retval   none
 */
//--------------------------------------------------------------

void UgMgrSetNoneRadarDisp(void)
{
    _pCommUnder->radarDispType = _RADAR_NONE;
}

//--------------------------------------------------------------
/**
 * ���[�_�[�Ɏ�����㩂�\��������
 * @param    none
 * @retval   none
 */
//--------------------------------------------------------------

void UgMgrSetMyTrapRadarDisp(void)
{
    _pCommUnder->radarDispType = _RADAR_NORMAL;
}

//--------------------------------------------------------------
/**
 * ���[�_�[�ɐ΂�\��������
 * @param    none
 * @retval   none
 */
//--------------------------------------------------------------

void UgMgrSetStoneRadarDisp(void)
{
    _pCommUnder->radarDispType = _RADAR_STONE;
}

//--------------------------------------------------------------
/**
 * ���[�_�[��㩂�\��������
 * @param    none
 * @retval   none
 */
//--------------------------------------------------------------

void UgMgrSetTrapRadarDisp(void)
{
    _pCommUnder->radarDispType = _RADAR_NATU_TRAP;
}

//--------------------------------------------------------------
/**
 * ���[�_�[�ɉ��΂�\��������
 * @param    none
 * @retval   none
 */
//--------------------------------------------------------------

void UgMgrSetFossilRadarDisp(void)
{
    _pCommUnder->radarDispType = _RADAR_FOSSIL;
}


void UgMgrSetTalkLog(int myNetID, int targetID)
{
    if(_pCommUnder){
        _pCommUnder->logTalk[myNetID] = targetID;
    }
}

void UgMgrSetTalkOtherLog(int myNetID)
{
    if(_pCommUnder){
        _pCommUnder->logTalkOther[myNetID] = TRUE;
    }
}

void UgMgrSetReturnLog(int myNetID)
{
    WORDSET* pWordSetMain;  //���[�h�Z�b�g�\����
    STRBUF* tmp_buf1;

    if(_pCommUnder){
        if(_pCommUnder->logReturnBuff[myNetID] == NULL){
            _pCommUnder->logReturnBuff[myNetID] = STRBUF_Create( _EVWIN_MSG_BUF_SIZE, HEAPID_COMMUNICATION );
            pWordSetMain = WORDSET_Create(HEAPID_WORLD);
            tmp_buf1 = STRBUF_Create( _EVWIN_MSG_BUF_SIZE, HEAPID_WORLD );
            WORDSET_RegisterPlayerName( pWordSetMain, 0, CommInfoGetMyStatus(myNetID));
            MSGMAN_GetString( CommMsgGetMsgManager(CommUnderGetMsgUnderWorld()), UGreturn01, tmp_buf1 );
            WORDSET_ExpandStr( pWordSetMain, _pCommUnder->logReturnBuff[myNetID], tmp_buf1 );
            STRBUF_Delete( tmp_buf1 );
            WORDSET_Delete(pWordSetMain);
        }
    }
}

void UgMgrStartReturnLog(int myNetID)
{
    _pCommUnder->logReturn[myNetID] = TRUE;
}

//--------------------------------------------------------------
/**
 * ���R�[�h�L�[�@�\���J�n����
 * @param    none
 * @retval   none
 */
//--------------------------------------------------------------

void UgMgrOpenRecordKey(u16 keyBaseName)
{
    _pCommUnder->openKeyName = keyBaseName;
}

//--------------------------------------------------------------
/**
 * ���R�[�h�L�[���L������
 * @param    none
 * @retval   none
 */
//--------------------------------------------------------------

void UgMgrSetRecordKey(u16 windowName, u16 cursor, u16 line)
{
    int i;

    if(_pCommUnder->openKeyName == _KEY_NAME_NONE){
        return;
    }
    
    for(i = 0;i < _KEY_RESERVE_BUFF; i++){
        if(_pCommUnder->openKeyName == _pCommUnder->recordKey[i].keyBaseName){
            if(_pCommUnder->recordKey[i].windowName == windowName){
                // �����ꏊ���������̂ŋL��
         //       OHNO_SP_PRINT("�L�[�L�� %d %d %d \n",i, cursor, line);
                _pCommUnder->recordKey[i].oldCursor = cursor;
                _pCommUnder->recordKey[i].oldLine = line;
                return;
            }
        }
    }
    for(i = 0;i < _KEY_RESERVE_BUFF; i++){
        if(_KEY_NAME_NONE == _pCommUnder->recordKey[i].keyBaseName){
            OHNO_SP_PRINT("�󂫃L�[�L�� %d %d %d \n",i, _pCommUnder->openKeyName, windowName);
            _pCommUnder->recordKey[i].keyBaseName = _pCommUnder->openKeyName;
            _pCommUnder->recordKey[i].windowName = windowName;  // �󂫂ɋL��
            _pCommUnder->recordKey[i].oldCursor = cursor;
            _pCommUnder->recordKey[i].oldLine = line;
            return;
        }
    }
    GF_ASSERT(0);  // _KEY_RESERVE_BUFF���𑝂₷
}

//--------------------------------------------------------------
/**
 * ���R�[�h�L�[�������o��
 * @param    none
 * @retval   none
 */
//--------------------------------------------------------------

u16 UgMgrGetRecordKeyLine(u16 windowName)
{
    int i;
    
    for(i = 0;i < _KEY_RESERVE_BUFF; i++){
        if(_pCommUnder->openKeyName == _pCommUnder->recordKey[i].keyBaseName){
            if(_pCommUnder->recordKey[i].windowName == windowName){
                return _pCommUnder->recordKey[i].oldLine;
            }
        }
    }
    return 0;
}

//--------------------------------------------------------------
/**
 * ���R�[�h�L�[�������o��
 * @param    none
 * @retval   none
 */
//--------------------------------------------------------------

u16 UgMgrGetRecordKeyCursor(u16 windowName)
{
    int i;
    
    for(i = 0;i < _KEY_RESERVE_BUFF; i++){
        if(_pCommUnder->openKeyName == _pCommUnder->recordKey[i].keyBaseName){
            if(_pCommUnder->recordKey[i].windowName == windowName){
                return _pCommUnder->recordKey[i].oldCursor;
            }
        }
    }
    return 0;
}

//--------------------------------------------------------------
/**
 * ���R�[�h�L�[������
 * @param    none
 * @retval   none
 */
//--------------------------------------------------------------

void UgMgrEraseRecordKey(u16 windowName, u16 cursor, u16 line)
{
    int i;

    if(_pCommUnder->openKeyName == _KEY_NAME_NONE){
        return;
    }
    
    for(i = 0;i < _KEY_RESERVE_BUFF; i++){
        if(_pCommUnder->openKeyName == _pCommUnder->recordKey[i].keyBaseName){
            if(_pCommUnder->recordKey[i].windowName == windowName){
                // �����ꏊ���������̂ŋL��
         //       OHNO_SP_PRINT("�L�[�L�� %d %d %d \n",i, cursor, line);
                _pCommUnder->recordKey[i].oldCursor = cursor;
                _pCommUnder->recordKey[i].oldLine = line;
                return;
            }
        }
    }
    for(i = 0;i < _KEY_RESERVE_BUFF; i++){
        if(_KEY_NAME_NONE == _pCommUnder->recordKey[i].keyBaseName){
            OHNO_SP_PRINT("�󂫃L�[�L�� %d %d %d \n",i, _pCommUnder->openKeyName, windowName);
            _pCommUnder->recordKey[i].keyBaseName = _pCommUnder->openKeyName;
            _pCommUnder->recordKey[i].windowName = windowName;  // �󂫂ɋL��
            _pCommUnder->recordKey[i].oldCursor = cursor;
            _pCommUnder->recordKey[i].oldLine = line;
            return;
        }
    }
    GF_ASSERT(0);  // _KEY_RESERVE_BUFF���𑝂₷
}


//--------------------------------------------------------------
/**
 * @brief   NPC�Ƙb��   CF_NPC_TALK
 * @param   none
 * @retval  �p�P�b�g�T�C�Y
 */
//--------------------------------------------------------------

void UgMgrRecvNPCTalk(int netID, int size, void* pData, void* pWork)
{
    u8* pBuff = pData;
    int id = pBuff[0];

    if(id == CommGetCurrentID()){
        UgShopManInit(_pCommUnder->pFSys);
        CommSendFixData(CF_OTHER_TALK);
        CommPlayerHold();
    }
}


//--------------------------------------------------------------
/**
 * @brief   ���ݓ����Ă�^�X�N��o�^
 * @param   void* work     ���[�N�|�C���^
 * @param   TCB_PTR pTCB   �^�X�N�|�C���^
 * @param   ForceDeleteFunc pFunc  �����I���֐�
 * @retval  none
 */
//--------------------------------------------------------------

void UgMgrSetNowTCB(void* work,TCB_PTR pTCB,ForceDeleteFunc pFunc)
{
#ifdef DEBUG_ONLY_FOR_ohno
//    GF_ASSERT_MSG(_pCommUnder->pNowTCB==NULL,"double %x",(u32)pFunc);
#endif
    OHNO_PRINT("TCB---set %x\n",(u32)pFunc);
    _pCommUnder->pNowWork = work;
    _pCommUnder->pNowTCB = pTCB;
    _pCommUnder->pForceFunc = pFunc;
}

//--------------------------------------------------------------
/**
 * @brief   ���ݓ����Ă�^�X�N�o�^�𖕏�
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------
//
void UgMgrEndNowTCB(void)
{
    OHNO_PRINT("UgMgrEndNowTCB %x \n",(u32)_pCommUnder->pForceFunc);
    _pCommUnder->pNowWork = NULL;
    _pCommUnder->pNowTCB = NULL;
    _pCommUnder->pForceFunc = NULL;
}

//--------------------------------------------------------------
/**
 * @brief   �^�X�N�����I��
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

BOOL UgMgrForceExitNowTCB(void)
{
    BOOL ret = FALSE;

    if(_pCommUnder->pNowTCB){
        OHNO_PRINT("UgGoodsMenuForceDelete\n");
        _pCommUnder->pForceFunc(_pCommUnder->pNowTCB, _pCommUnder->pNowWork);
        UgMgrEndNowTCB();
        ret = TRUE;
    }
    CommUnderAllMsgForceDel();
    CommMsgTalkWindowEnd(_pCommUnder->pCommMsgUW);
    CommMsgTalkWindowEnd(_pCommUnder->pCommMsgFlag);
    CommMsgTalkWindowEnd(_pCommUnder->pCommMsgShop);
    CommMsgTalkWindowEnd(_pCommUnder->pCommMsgEdit);
    CommMsgTalkWindowEnd(_pCommUnder->pCommMsgItem);
    CommMsgTalkWindowEnd(_pCommUnder->pCommMsgUW); // ���ܖ��߁A�E���Ƃ��ɐ������Ă����ꍇ�ɓd���؂������p
    return ret;
}

//--------------------------------------------------------------
/**
 * @brief   ���Ղ̃R���g���[���������Ă����̂��ǂ���
 * @param   netID     �ʐMID
 * @retval  ���Ȃ�TRUE
 */
//--------------------------------------------------------------

BOOL UgMgrIsFirstMoveControlEnable(int netID)
{
    int x,z;


    if(_pCommUnder->pNowTCB){  // ��b��
        OHNO_PRINT("��b��������\n");
        return FALSE;
    }
    if(_pCommUnder->pFSys->event){  // �C�x���g��
        _pCommUnder->debugNum++;
        if(_pCommUnder->debugNum > 100){
            GF_ASSERT(0);
        }
        OHNO_PRINT("�C�x���g��������\n");
        return FALSE;
    }
    if(CommPlayerIsTrapBind(netID)){
        OHNO_PRINT("��Ȃ����蒆������\n");
        return FALSE;
    }
    x = CommPlayerGetPosXOrg(netID);
    z = CommPlayerGetPosZOrg(netID);
    if(UgSecretBaseIsSecretBasePlace(x,z) && (netID != COMM_PARENT_ID)){
        OHNO_PRINT("�閧��n�̒��Œǂ��o�����O\n");
        return FALSE;
    }
    _pCommUnder->debugNum = 0;
   
    return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   ���ʂ̎������b�Z�[�W�̏I���Ƃ�����ʂ̃��b�Z�[�WID��
            ���݂��Ă��܂��̂ŁA�^�X�N�̃g�b�v�ŊǗ����Ă���
 * @param   TCB_PTR tcb   void *work 
 * @retval  none
 */
//--------------------------------------------------------------

static void _undergroundMsgTask( TCB_PTR tcb, void *work )
{
    // �n���̏��ʂɂ�������Ɠ��삪������Ȃ��悤�ɂ��鏈����
    
    CommMsgFunc(_pCommUnder->pCommMsgUW);
    CommMsgFunc(_pCommUnder->pCommMsgFlag);
    CommMsgFunc(_pCommUnder->pCommMsgShop);
    CommMsgFunc(_pCommUnder->pCommMsgEdit);
    CommMsgFunc(_pCommUnder->pCommMsgItem);
}

//--------------------------------------------------------------
/**
 * @brief   ���΁{�G�X�P�[�v�ꏊ�𑗐M
 * @param   TCB_PTR tcb   void *work 
 * @retval  none
 */
//--------------------------------------------------------------

typedef struct{
    u16 x;
    u16 z;
    u8 dir;
    u8 bFossil;
} _initDataPack;


void UgInitialDataSend(void)
{
    _initDataPack pack;

    pack.x = UgSecretBaseEscapePosX();
    pack.z = UgSecretBaseEscapePosZ();
    pack.dir = UgSecretBaseEscapeDir();
    pack.bFossil = UgDigFossilIsNow();
    CommSendFixSizeData(CF_DIG_FOSSIL_INIT,&pack);
}

void UgInitialDataRecv(int netID, int size, void* pData, void* pWork)
{
    _initDataPack* pPack = pData;

    UgSecretBaseEscapePosSXSet(netID, pPack->x);
    UgSecretBaseEscapePosSZSet(netID, pPack->z);
    UgSecretBaseEscapeDirSet(netID, pPack->dir);
    UgDigFossilSetNow(netID,pPack->bFossil);
}

int UgInitialDataSendSize(void)
{
    return sizeof(_initDataPack);
}

//--------------------------------------------------------------
/**
 * @brief   ���̃��b�Z�[�W�͎q�@�����������̑��M���I�������ɑ��M����܂�  CF_PLAYER_INIT_END
 * @param   TCB_PTR tcb   void *work 
 * @retval  none
 */
//--------------------------------------------------------------

void CommUgRecvChildStateNormal(int netID, int size, void* pData, void* pWork)
{
    _pCommUnder->initEnd[netID] = TRUE;
    OHNO_PRINT("����%d ��t����\n",CommUgGetChildStateNormalNum());
}

//--------------------------------------------------------------
/**
 * @brief   �q�@�����������̑��M���I������
 * @param   none
 * @retval  num
 */
//--------------------------------------------------------------

int CommUgGetChildStateNormalNum(void)
{
    int i,num=0;

    for(i = 0;i < COMM_MACHINE_MAX;i++){
        if(_pCommUnder->initEnd[i]){
            num++;
        }
    }
    return num;
}

