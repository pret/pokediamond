//=============================================================================
/**
 * @file	ug_dig_stone.c
 * @brief	�ʂ��Ǘ�����N���X
 * @author	Katsumi Ohno
 * @date    2005.10.26
 */
//=============================================================================


#include <nitro/os.h>
#include "common.h"

#include "../fieldsys.h"
#include "communication/communication.h"
#include "../comm_field_state.h"
#include "ug_manager.h"

#include "../worldmap.h"
#include "../fieldobj.h"
#include "../fld_bmp.h"
#include "system/pm_str.h"
#include "system/fontproc.h"
#include "system/bmp_list.h"
#include "system/window.h"
#include "system/wordset.h"
#include "msgdata/msg_underworld.h"

#include "system/snd_tool.h"
#include "field/eventflag.h"
#include "../sysflag.h"

#include "../d_ohno.h"  // �f�o�b�O�p



//==============================================================================
// ��`
//==============================================================================

#define _EVWIN_MSG_BUF_SIZE		(50*2)			//���b�Z�[�W�o�b�t�@�T�C�Y

#define _RESULT_CMD_SIZE (2) // �f�[�^����M�̌��ʂ�Ԃ����̃f�[�^�o�C�g��
#define _TOUCH_OBJ_MAX (3)  //Touch�������ɕ\������㩂̌��E��
#define _STONE_NUM_SINGLE_MAX (UG_STONE_PLACE_NUM_MAX)   // ��l���̐�
#define _STONE_NUM_MAX (_STONE_NUM_SINGLE_MAX)      // �� 100

#define _INTERVAL_STONE_DISP (20)

// ���肦�Ȃ�ID
#define _INVALID_ID  (0xff)

enum _result_e {
    _RESULT_NONE,
    _RESULT_OK,
    _RESULT_NG
};

//==============================================================================
//	�^�錾
//==============================================================================

typedef struct{
    u16 xpos;   // �΂̈ʒu
    u16 zpos;
    u8 carat;   // �傫��=�J���b�g 1-99
    u8 addCarat;   // ����=�J���b�g 1-99
    u8 type;     // ���
//    u8 order;   // ���߂�����  (�������񖄂߂�ƌÂ����̂������Ă����Ă��܂���)
} _Stone;

typedef struct{
    _Stone stone;
    u8 netID;
    u8 result;
} _StoneResult;


typedef struct{
    u8 pcRadarIndex;  //�p�\�R�����[�_�[��M�p
    u16 pcRadarTimer;  //�p�\�R�����[�_�[�\���p
} _EVENT_PCRADAR_WORK;

typedef struct{
    _Stone myStone[_STONE_NUM_SINGLE_MAX];    // ���߂Ă��鎩���̐΁i�Z�[�u�\�j
    _Stone* pStoneTbl[_STONE_NUM_SINGLE_MAX]; // �����p�e�[�u��
    u8 recvCounter[COMM_MACHINE_MAX];
    u8 recvCounterBackup[COMM_MACHINE_MAX];
    TCB_PTR pPcRadar;
    _EVENT_PCRADAR_WORK* pPcRadarWork;
    FIELDSYS_WORK* pFSys;
    u8 logMsgGetStone[COMM_MACHINE_MAX];
    int intervalTimer;
    u8 sendNum;
    u8 result;
    u8 bStopDisp;
} CommDigWork;

// �V���O���g��
static CommDigWork* _pCommWork = NULL;

//==============================================================================
//	static�錾
//==============================================================================

static _Stone* _getOldOrderData(_Stone* pStoneTbl);
static Grid* _getStoneTblPos(Grid* pGrid, int index);
static void _delStone(_Stone* pStone);
static void _resetOrderNo(_Stone* pStoneTbl);
static void _myStoneDel(_Stone* pStone);
static void _myStoneAdd(_Stone* pStone);
static void _insertStoneTbl(_Stone* pStone);

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
 * �Ζ������b�Z�[�W�̕\��
 * @param   type   �΃^�C�v
 * @param   message   GMM���b�Z�[�WID
 * @retval  none
 */
//==============================================================================

static void _digAddCaratMessage(int num)
{
    if(num > 0){
        CommMsgRegisterNumber2Index(CommUnderGetMsgUnderWorld(), 0, num);
        CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(),
                               msg_underworld_75, TRUE, _msgEndCallBack);
    }
    else{
        _msgEndCallBack(num);
    }
}

//==============================================================================
/**
 * �Ό@��Ǘ��̏�����
 * @param   pWork   ��ƃ������[
 * @retval  none
 */
//==============================================================================

void CommDigStoneInitialize(void* pWork, FIELDSYS_WORK* pFSys)
{
    int i;
    UNDERGROUNDDATA* pUGData;

    if(_pCommWork){
        return;
    }
    _pCommWork = pWork;
    MI_CpuFill8(_pCommWork, 0, sizeof(CommDigWork));
    _pCommWork->pFSys = pFSys;
    pUGData = SaveData_GetUnderGroundData(GameSystem_GetSaveData(pFSys));

    for(i = 0; i < _STONE_NUM_SINGLE_MAX; i++){
        _pCommWork->myStone[i].type = UnderGroundGetStoneGroundItemType(pUGData,i);
        _pCommWork->myStone[i].xpos = UnderGroundGetStoneGroundItemX(pUGData,i);
        _pCommWork->myStone[i].zpos = UnderGroundGetStoneGroundItemZ(pUGData,i);
        _pCommWork->myStone[i].carat = UnderGroundGetStoneGroundItemCaratOrg(pUGData,i);
     //   _pCommWork->myStone[i].order = UnderGroundGetStoneGroundItemOrder(pUGData,i);
        _pCommWork->myStone[i].addCarat = UnderGroundGetStoneGroundItemCaratMul(pUGData,i);
        if(_pCommWork->myStone[i].type != STONE_TYPE_NONE){
            _insertStoneTbl(&_pCommWork->myStone[i]);
        }
    }
}


//==============================================================================
/**
 * �����̐΂��o�b�N�A�b�v����
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _myStoneBackup(void)
{
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(GameSystem_GetSaveData(_pCommWork->pFSys));
    int i;
    for(i = 0; i < _STONE_NUM_SINGLE_MAX; i++){
        UnderGroundAddStoneGroundItem( pUGData, _pCommWork->myStone[i].type,i,
                                      _pCommWork->myStone[i].xpos,
                                      _pCommWork->myStone[i].zpos,
                                    // _pCommWork->myStone[i].order,
                                      _pCommWork->myStone[i].carat,
                                       _pCommWork->myStone[i].addCarat
                                       );
    }
}

//==============================================================================
/**
 * �Ό@��̃��[�N�T�C�Y�𓾂�
 * @param   none
 * @retval  �T�C�Y
 */
//==============================================================================

int CommDigStoneManagerGetWorkSize(void)
{
    return sizeof(CommDigWork);
}

//==============================================================================
/**
 * �Ό@��̃��Z�b�g
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommDigStoneManagerReset(void)
{
    _pCommWork->bStopDisp = TRUE;
}

//==============================================================================
/**
 * �Ό@��̕��A����
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommDigStoneManagerReboot(void)
{
    _pCommWork->bStopDisp = FALSE;
}

//==============================================================================
/**
 * �Ό@��̏I��
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommDigStoneFinalize(void)
{
    if(_pCommWork){
        sys_FreeMemoryEz(_pCommWork);
        _pCommWork = NULL;
    }
}

//==============================================================================
/**
 * �Ό@��̖��t���[������
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommDigStoneStep(void)
{
    if(_pCommWork->bStopDisp)
        return;
    
    _pCommWork->intervalTimer++;
    if(_pCommWork->intervalTimer >= (_STONE_NUM_MAX * _INTERVAL_STONE_DISP)){
        _pCommWork->intervalTimer = 0;
    }
    if((_pCommWork->intervalTimer % _INTERVAL_STONE_DISP) == 10){
        int stoneID = _pCommWork->intervalTimer / _INTERVAL_STONE_DISP;
        int x = UgStoneGetMyStoneX(stoneID);
        int z = UgStoneGetMyStoneZ(stoneID);
        if((x != 0) && (z != 0)){
            FE_FldOBJGFlashSet(_pCommWork->pFSys, x, z);
        }
    }
}



//==============================================================================
/**
 * �e�[�u����ɂ���΂̈ʒu��Ԃ�
 * @param   pGrid  �Ԃ��ʒu
 * @param   index  ��������index
 * @retval  none�T�C�Y
 */
//==============================================================================

static Grid* _getStoneTblPos(Grid* pGrid, int index)
{
    if(_pCommWork->pStoneTbl[index]==NULL){
        return NULL;
    }
    pGrid->xpos = _pCommWork->pStoneTbl[index]->xpos;
    pGrid->zpos = _pCommWork->pStoneTbl[index]->zpos;
    return pGrid;
}

//==============================================================================
/**
 * �e�[�u���ɐ΂�}������
 * @param   pGrid  �Ԃ��ʒu
 * @param   index  ��������index
 * @retval  none�T�C�Y
 */
//==============================================================================

static void _insertStoneTbl(_Stone* pStone)
{
    int ins,i;
    Grid grid;

    grid.xpos = pStone->xpos;
    grid.zpos = pStone->zpos;
    CommUnderItemSearchInitialize(_STONE_NUM_MAX, _getStoneTblPos);
    ins = CommUnderSearchItemTbl(&grid);

    OHNO_PRINT("�e�[�u���ɓ���� %d\n",ins);
    GF_ASSERT_RETURN(ins < (_STONE_NUM_MAX),);

    for(i = (_STONE_NUM_MAX - 1); i > ins  ; i--){
        _pCommWork->pStoneTbl[ i ] = _pCommWork->pStoneTbl[ i - 1 ];
    }
    
/*    memmove(&_pCommWork->pStoneTbl[ins+1],
            &_pCommWork->pStoneTbl[ins],
            (_STONE_NUM_MAX - ins - 1)*sizeof(u32));*/
    _pCommWork->pStoneTbl[ins] = pStone;

}

//==============================================================================
/**
 * �����e�[�u������Ȃ���
 * @param   netID     ID
 * @retval  _Stone*
 */
//==============================================================================

static void _delStoneTbl(_Stone* pStone)
{
    int match = -1;
    Grid grid;
    int i;

    MI_CpuClear8(_pCommWork->pStoneTbl,sizeof(u32)*_STONE_NUM_MAX);

    for(i = 0; i < _STONE_NUM_MAX; i++){
        if(_pCommWork->myStone[i].type != STONE_TYPE_NONE){
            _insertStoneTbl(&_pCommWork->myStone[i]); //�č\�z
        }
    }
    
#if 0
    for(i = 0; i < _STONE_NUM_MAX; i++){
        OHNO_PRINT("�΃e�[�u�� %d %d %d\n",i, _pCommWork->pStoneTbl[ i ]->xpos,_pCommWork->pStoneTbl[ i ]->zpos);
        if(_pCommWork->pStoneTbl[ i ] == pStone){
            match = i;
            break;
        }
    }
    GF_ASSERT_RETURN(match != -1,);
    for(i = match; i < (_STONE_NUM_MAX-1); i++){
        _pCommWork->pStoneTbl[ i ] = _pCommWork->pStoneTbl[ i+1 ];
    }
    _pCommWork->pStoneTbl[_STONE_NUM_MAX-1] = NULL;
#endif
    
#if 0
    
    
    grid.xpos = pStone->xpos;
    grid.zpos = pStone->zpos;
    CommUnderItemSearchInitialize(_STONE_NUM_MAX, _getStoneTblPos);
    match = CommUnderMatchItemTbl(&grid);
    OHNO_PRINT("�e�[�u��������� %d\n",match);
    

    GF_ASSERT_RETURN(match != -1,);

    for(i = match; i < (_STONE_NUM_MAX-1); i++){
        _pCommWork->pStoneTbl[ i ] = _pCommWork->pStoneTbl[ i+1 ];
    }

//    memmove(&_pCommWork->pStoneTbl[match],
//            &_pCommWork->pStoneTbl[match+1],
//            (_STONE_NUM_MAX - match - 1)*sizeof(u32));
    _pCommWork->pStoneTbl[_STONE_NUM_MAX-1] = NULL;
#endif
}

//==============================================================================
/**
 * �����Ă�΃o�b�t�@��Ԃ�
 * @param   netID     ID
 * @retval  _Stone*
 */
//==============================================================================

static _Stone* _getFreeStone( _Stone* pStoneTbl )
{
    int i;
    
    for(i = 0; i < _STONE_NUM_SINGLE_MAX; i++){
        if(pStoneTbl->type == STONE_TYPE_NONE){
            return pStoneTbl;
        }
        pStoneTbl++;
    }
    return NULL;
}

//==============================================================================
/**
 * �����Ă�΂�index��Ԃ�
 * @param   netID     ID
 * @retval  _Stone*
 */
//==============================================================================

static int _getFreeStoneIndex( _Stone* pStoneTbl )
{
    int i;
    
    for(i = 0; i < _STONE_NUM_SINGLE_MAX; i++){
        if(pStoneTbl->type == STONE_TYPE_NONE){
            return i;
        }
        pStoneTbl++;
    }
    return 0;
}



//==============================================================================
/**
 * �΂̏���
 * @param   TrapInfo* pTrap �
 * @retval  none
 */
//==============================================================================
#if 0
static void _delStone(_Stone* pStone)
{
    u32 baseAddr = (u32)&_pCommWork->myStone[0];
    u32 nowStone = (u32)pStone;
    u32 stoneNo = (nowStone-baseAddr)/sizeof(_Stone);
    u32 id = stoneNo;
    
    pStone->type = STONE_TYPE_NONE;
    pStone->order = 0;
    _delStoneTbl(pStone);
}
#endif
//--------------------------------------------------------------
/**
 * �ŏ��ɐ��������΂𓾂�
 * @param    netID  �@��ԍ�
 * @retval   �����ԍ�
 */
//--------------------------------------------------------------
static _Stone* _getOldOrderData(_Stone* pStoneTbl)
{
    return pStoneTbl;
}

//==============================================================================
/**
 *  �΂����������ǂ�����Ԃ�
 * @param   ���ׂ������W��X���W
   @param   ���ׂ������W��Z���W
 * @retval  �������������
 */
//==============================================================================

static _Stone* _checkStone(int x, int z)
{
    Grid grid;
    int ret;

    grid.xpos = x;
    grid.zpos = z;
    CommUnderItemSearchInitialize(_STONE_NUM_MAX, _getStoneTblPos);
    ret = CommUnderMatchItemTbl(&grid);

    if(-1 == ret){
        return NULL;
    }
    return _pCommWork->pStoneTbl[ret];
}

//==============================================================================
/**
 *  �΂��E�������Ƃ��E�����N���C�A���g�ɕ\�� CF_DIG_STONE_PICKUP
 * @param   netID    ���M���Ă���ID
 * @param   x,y      �ʒu���
 * @retval  ���������ꍇTRUE 
 */
//==============================================================================

void CommDigStoneRecvPickUp(int netID, int size, void* pData, void* pWork)
{
    u8* pBuff = pData;
    int id = CommGetCurrentID();
    int x,z,ca;
    _Stone* pStone;

    if(pBuff[0] == id){
        x = CommPlayerGetPosXDirAdd(id);
        z = CommPlayerGetPosZDirAdd(id);
        pStone = _checkStone(x, z);
        if(pStone){       // �΂��E��
            CommPlayerHold();
            if(CommUnderBagAddStone(pStone->type, pStone->carat + pStone->addCarat)){  // �{�[�����o�b�O�ɒǉ�
                _pCommWork->logMsgGetStone[id] = pStone->type;
                Snd_SePlay(UG_SE_FIND);
                ca = UG_STONE_CARAT_MAX;
                if(pStone->carat+ pStone->addCarat < UG_STONE_CARAT_MAX){
                    ca = pStone->carat+ pStone->addCarat;
                }
                CommMsgRegisterNumber2Index(CommUnderGetMsgUnderWorld(), 1, ca);
                CommMsgRegisterUGItemNameIndex(CommUnderGetMsgUnderWorld(), 2, pStone->type);
                ca = pStone->addCarat;
                if((ca + pStone->carat) > UG_STONE_CARAT_MAX){
                    ca = UG_STONE_CARAT_MAX - pStone->carat;
                }
                CommMsgTalkWindowStartSendNum(CommUnderGetMsgUnderWorld(),
                                              msg_underworld_69, TRUE, _digAddCaratMessage, ca);
                CommMsgTalkWindowMeWait(CommUnderGetMsgUnderWorld());  //ME�̏I���҂�ON
                _myStoneDel(pStone);  // �Â��̂�����
                _myStoneBackup();
            }
            else{
                CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(),
                                       msg_underworld_83, TRUE, _msgEndCallBack);
            }
        }
    }
}

//==============================================================================
/**
 * �����ɋ߂��܂����W�������Ă����
 * @param   none
 * @retval  none
 */
//==============================================================================

void NearHexInitialize(NearHexWork* pWork, int maxDist)
{
    pWork->maxDist = maxDist;
    pWork->iterater = 0;
}

//==============================================================================
/**
 * �����ɋ߂��܂����W�������Ă����
 * @param   none
 * @retval  none
 */
//==============================================================================

BOOL NearHexGetHex(NearHexWork* pWork, NearHex* pHex)
{
    int i, ite, x, y;

    ite = pWork->iterater;

    for(i = 0 ; i <= pWork->maxDist; i++){
        if((ite - (i*4)) > 0){
            ite = ite - (i*4);
        }
        else{
            if(ite!=0){
                ite--;
            }
            if(ite < (i*2)){
                y = i - ite;
            }
            else{
                y = ite - i*3;
            }
            if(ite < (i)){
                x = ite;
            }
            else if(ite < (i*3)){
                x = i*3 - (ite + i);
            }
            else{
                x = -i + (ite - i*3);
            }
            pHex->xpos = x;
            pHex->zpos = y;
//            OHNO_PRINT("%d x=%d y=%d\n",pWork->iterater,x,y);
            pWork->iterater++;
            return TRUE;
        }
    }
    return FALSE;
}

//==============================================================================
/**
 *  �ʂ𖄂߂�
 * @param   type      �^�}
 * @param   carat     �J���b�g
 * @retval  ���b�Z�[�W������ꍇTRUE
 */
//==============================================================================

void CommDigStoneAddStone( int type, int carat ,int x,int z)
{
    _Stone stone;
    _Stone* pStone;
    BOOL bDig = FALSE;
    
    stone.xpos = x;   // �΂̈ʒu
    stone.zpos = z;
    stone.carat = carat;   // �傫��=�J���b�g 1-99
    stone.type = type;     // ���
    stone.addCarat = 0;

    if(UgSecretBaseIsSecretBasePlace(x,z)){
        CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(), msg_underworld_84, FALSE, NULL);
        return;
    }
    if(CommPlayerNPCHitCheck(x, z)){
        CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(), msg_underworld_55, FALSE, NULL);
        return;
    }    
    if(GetHitAttr(_pCommWork->pFSys,x,z)){
        CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(), msg_underworld_60, FALSE, NULL);
        return;
    }
    pStone = _checkStone(x, z);
    if(pStone){  // ��񂪂���
        if(pStone->type == stone.type){ // �����΂̏ꍇ
            if(pStone->carat > carat){
                pStone->carat = pStone->carat + (carat / 5) + 1;
            }
            else{
                pStone->carat = carat + (pStone->carat / 5) + 1;
            }
            if(pStone->carat > UG_STONE_CARAT_MAX){
                pStone->carat = UG_STONE_CARAT_MAX;
            }
            bDig = TRUE;
        }
        else{
            CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(), msg_underworld_59, FALSE, NULL);
        }
    }
    else{
        _myStoneAdd(&stone);
        bDig = TRUE;
    }
    if(bDig){
        CommMsgRegisterUGItemNameIndex(CommUnderGetMsgUnderWorld(), 0, type);
        CommMsgRegisterNumber2Index(CommUnderGetMsgUnderWorld(), 1, carat);
        CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(), msg_underworld_58, FALSE, NULL);
        CommUnderBagDeleteStone(type);
        Snd_SePlay(UG_SE_BURY);  // ���߂�
        //Snd_SePlay(UG_SE_SMOKE);
        SysFlag_UgTamaSet(SaveData_GetEventWork(_pCommWork->pFSys->savedata));
        FE_FldOBJGFlashSet(_pCommWork->pFSys, x, z);
    }
}

//==============================================================================
/**
 * �����̐΂�����
 * @param   pStone    �΃f�[�^
 * @retval  none
 */
//==============================================================================

static void _myStoneDel(_Stone* pStone)
{
    _Stone* pFreeStone;
    int index = -1,i;

    
    for(i = 0; i< _STONE_NUM_SINGLE_MAX; i++){
        pFreeStone = &_pCommWork->myStone[i];
        if(pStone == pFreeStone){
            index = i;
            break;
        }
    }
    GF_ASSERT_RETURN(index != -1,);

    for( ; i < (_STONE_NUM_SINGLE_MAX-1); i++){
        MI_CpuCopy8(&_pCommWork->myStone[i+1],&_pCommWork->myStone[i],sizeof(_Stone));
    }
    _pCommWork->myStone[_STONE_NUM_SINGLE_MAX-1].type = STONE_TYPE_NONE;

    _delStoneTbl(pStone);

}

//==============================================================================
/**
 * �����̐΂�ǉ�����
 * @param   pStone
 * @retval  none
 */
//==============================================================================

static void _myStoneAdd(_Stone* pStone)
{
    _Stone* pFreeStone = _getFreeStone(_pCommWork->myStone);
    int index;

    if(pFreeStone==NULL){
        pFreeStone = _getOldOrderData(_pCommWork->myStone);
        _myStoneDel(pFreeStone);  // �Â��̂�����
        pFreeStone = _getFreeStone(_pCommWork->myStone);
        GF_ASSERT_RETURN(pFreeStone,);
    }
//    index = _getFreeStoneIndex(_pCommWork->myStone);
    MI_CpuCopy8( pStone, pFreeStone, sizeof(_Stone));
    _insertStoneTbl(pFreeStone);
    _myStoneBackup();
}

//==============================================================================
/**
 *  �^�}���ǂ�����Ԃ�
 * @param   message   ���b�Z�[�W
 * @retval  ���b�Z�[�W������ꍇTRUE
 */
//==============================================================================
BOOL CommDigIsStone(int type)
{
    if((type != STONE_TYPE_NONE) && (type < DIG_PARTS_TREASURE_MIN)){
        return TRUE;
    }
    return FALSE;
}


//==============================================================================
/**
 *  �΂����������ǂ�����Ԃ�
 * @param   ���ׂ������W��X���W
   @param   ���ׂ������W��Z���W
 * @retval  ���������ǂ���
 */
//==============================================================================

BOOL UgStoneCheck(int x, int z)
{
    if(_checkStone(x,z)){
        return TRUE;
    }
    return FALSE;
}



//--------------------------------------------------------------
/**
 * �΂̈ʒuX���W�𓾂�
 * @param    index
 * @retval   X���W
 */
//--------------------------------------------------------------

int UgStoneGetMyStoneX(int index)
{
    if(_pCommWork  &&
       (_pCommWork->myStone[index].type != STONE_TYPE_NONE) ){
        return _pCommWork->myStone[index].xpos;
    }
    return 0;
}

//--------------------------------------------------------------
/**
 * �΂̈ʒuZ���W�𓾂�
 * @param    index
 * @retval   Z���W
 */
//--------------------------------------------------------------

int UgStoneGetMyStoneZ(int index)
{
    if(_pCommWork  &&
       (_pCommWork->myStone[index].type != STONE_TYPE_NONE) ){
        return _pCommWork->myStone[index].zpos;
    }
    return 0;
}

//==============================================================================
/**
 * ��log���b�Z�[�W��Ԃ�
 * @param   message   ���b�Z�[�W
 * @retval  ���b�Z�[�W������ꍇTRUE
 */
//==============================================================================

BOOL UgDigStoneGetActionMessage(STRBUF* pStrBuf)
{
    int i;
    WORDSET* pWordSetMain=NULL;  //���[�h�Z�b�g�\����
    STRBUF* tmp_buf1=NULL;
    BOOL bRet = FALSE;

    if(!_pCommWork){
        return bRet;
    }
    for(i = 0; i< COMM_MACHINE_MAX; i++){
        if(_pCommWork->logMsgGetStone[i] != STONE_TYPE_NONE){
            pWordSetMain = WORDSET_Create(HEAPID_FIELD);
            tmp_buf1 = STRBUF_Create( _EVWIN_MSG_BUF_SIZE, HEAPID_FIELD );
            WORDSET_RegisterUGItemName(pWordSetMain, 2, _pCommWork->logMsgGetStone[i]);
            MSGMAN_GetString( CommMsgGetMsgManager(CommUnderGetMsgUnderWorld()), UGBallGet, tmp_buf1 );
            WORDSET_ExpandStr( pWordSetMain, pStrBuf, tmp_buf1 );
            _pCommWork->logMsgGetStone[i] = STONE_TYPE_NONE;
            bRet = TRUE;
            break;
        }
    }
    if(tmp_buf1)
        STRBUF_Delete( tmp_buf1 );
    if(pWordSetMain)
        WORDSET_Delete(pWordSetMain);
    return bRet;
}

//==============================================================================
/**
 * �Έ�̋߂��ɉ��Έ�𖄂߂�
 * @param   �����|�C���^
 * @retval  ���߂�����
 */
//==============================================================================

int UgDigStoneSetOneFossil(MATHRandContext16* pRand)
{
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(GameSystem_GetSaveData(_pCommWork->pFSys));
    int x,z,i;
    
    for(i = 0; i < _STONE_NUM_SINGLE_MAX; i++){
        if(STONE_TYPE_NONE != UnderGroundGetStoneGroundItemType(pUGData,i)){
            x = UnderGroundGetStoneGroundItemX(pUGData,i);
            z = UnderGroundGetStoneGroundItemZ(pUGData,i);
            UgFossilOneSetup(x,z, pRand);
        }
    }
    return i;
}

//--------------------------------------------------------------
/**
 * �p�\�R�����[�_�[�N���C�A���g�^�X�N
 * @param    tcb   tcb
 * @param    work   _EVENT_PCRADAR_WORK
 * @retval   none
 */
//--------------------------------------------------------------

static void _GMEVENT_PcRadar(TCB_PTR tcb, void *work)
{
    _EVENT_PCRADAR_WORK* pWork = work;

    pWork->pcRadarTimer++;
    if(_STONE_NUM_SINGLE_MAX < pWork->pcRadarTimer){
        Snd_SePlay(UG_SE_RADAR_ECHO);
        pWork->pcRadarTimer = 0;
    }
}


//--------------------------------------------------------------
/**
 * �p�\�R�����[�_�[�X�^�[�g
 * @param    none
 * @retval   none
 */
//--------------------------------------------------------------

void UgStonePcRadarStart(void)
{
    _EVENT_PCRADAR_WORK* mdw;
    GF_ASSERT_RETURN(!_pCommWork->pPcRadarWork,);  // ��d�N���֎~
    GF_ASSERT_RETURN(!_pCommWork->pPcRadar,);

    mdw = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(_EVENT_PCRADAR_WORK));
    MI_CpuFill8(mdw, 0, sizeof(_EVENT_PCRADAR_WORK));
    mdw->pcRadarTimer = _STONE_NUM_SINGLE_MAX;
    _pCommWork->pPcRadarWork = mdw;
    _pCommWork->pPcRadar = TCB_Add(_GMEVENT_PcRadar , mdw,TCB_PRIORITY_NORMAL);
}

//--------------------------------------------------------------
/**
 * �p�\�R�����[�_�[�G���h
 * @param    none
 * @retval   none
 */
//--------------------------------------------------------------

void UgStonePcRadarEnd(void)
{
    if(_pCommWork->pPcRadar){
        TCB_Delete(_pCommWork->pPcRadar);
        sys_FreeMemoryEz(_pCommWork->pPcRadarWork);
        _pCommWork->pPcRadar = NULL;
        _pCommWork->pPcRadarWork = NULL;
    }
}

#define _DTIME  (2)  // ���[�_�[��������茩����ׂ̊Ԋu

//--------------------------------------------------------------
/**
 * �����̐΂̈ʒuX���W�𓾂�
 * @param    index
 * @retval   X���W
 */
//--------------------------------------------------------------

int UgStoneGetRadarStoneX(int index)
{
    if(_pCommWork && _pCommWork->pPcRadarWork){
        int a = _pCommWork->pPcRadarWork->pcRadarTimer / _DTIME;
        a = (a + index) % (_STONE_NUM_SINGLE_MAX);
        return UgStoneGetMyStoneX(a);
    }
    return 0;
}

//--------------------------------------------------------------
/**
 * �����̐΂�TRAP�̈ʒuZ���W�𓾂�
 * @param    index
 * @retval   Z���W
 */
//--------------------------------------------------------------

int UgStoneGetRadarStoneZ(int index)
{
    if(_pCommWork && _pCommWork->pPcRadarWork){
        int a = _pCommWork->pPcRadarWork->pcRadarTimer / _DTIME;
        a = (a + index) % (_STONE_NUM_SINGLE_MAX);
        return UgStoneGetMyStoneZ(a);
    }
    return 0;
}



#ifdef PM_DEBUG

void Debug_UgDigStoneAdd( int type, int carat ,int x,int z)
{
    _Stone stone;
    stone.xpos = x;   // �΂̈ʒu
    stone.zpos = z;
    stone.carat = carat;   // �傫��=�J���b�g 1-99
    stone.type = type;     // ���
    stone.addCarat = 0;

    _myStoneAdd(&stone);
}

#endif
