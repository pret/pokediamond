//=============================================================================
/**
 * @file	ug_secretbase.c
 * @brief	�n���̔閧��n�����Ǘ�����N���X
            �����̔閧��n��
            �T�[�o�[�p�S���̔閧��n
            �����̔閧��n
            16+1=17��
 * @author	Katsumi Ohno
 * @date    2005.10.03
 */
//=============================================================================


#include <nitro/os.h>
#include "common.h"
#include "gflib/blact.h"

#include "communication/communication.h"
#include "../fieldsys.h"

#include "../field_event.h"
#include "../fld_bmp.h"
#include "system/bmp_menu.h"
#include "../ev_mapchange.h"
#include "../mapdefine.h"
#include "../comm_field_state.h"
#include "../map3d_object.h"
#include "../../fielddata/build_model/build_model_id.h"

#include "ug_manager.h"
#include "system/pm_str.h"
#include "system/gamedata.h"
#include "system/wordset.h"
#include "../field_effect.h"
#include "msgdata/msg_underworld.h"
#include "msgdata/msg_uwflag.h"
#include "system/fontproc.h"
#include "gflib/bg_system.h"
#include "system/window.h"
#include "ug_snd_def.h"
#include "system/wipe.h"
#include "system/brightness.h"

#include "field/goods_data.h"
#include "savedata/undergrounddata.h"
#include "system/arc_util.h"
#include "field/eventflag.h"
#include "../sysflag.h"
#include "../../fielddata/base_goods/goods_id_def.h"
#include "ug_trap.naix"

#include "../../communication/wh.h"


//==============================================================================
// ��`
//==============================================================================

#define _EVWIN_MSG_BUF_SIZE		(50*2)			//���b�Z�[�W�o�b�t�@�T�C�Y
#define _SECRETBASE_NUM_MAX (17)  ///< �閧��n�o�b�t�@�̍ő�
#define _SECRETBASE_MY_ID (16)  ///< �����̔閧��n�̃f�[�^�������Ă���ID
#define _SECRETBASE_SPLIT_NUM (4)  ///< ���M�����₷�����邽�߂̕�����

#define _SECRETBASE_ATTR_MAX (32)

#define _SECLET_INNER_BASE_X  (15)
#define _SECLET_INNER_BASE_Z  (24)
#define _SECLET_INNER_BASE_Z_PLUS (32)

#define _INVALID_BASE (0xff)
#define _PLAYER_INVALID_GRID  (0xfff)   // ���W�͂P�QBIT���M���s�����ߕςȐ����ɂȂ��Ă���


#define _MOVE_TICKETS  (1)  //�閧��n�f�[�^�ړ��J�n
#define _ERROR_TICKETS (2)  //�閧��n��M���ɃG���[
#define _NONE_TICKETS (0)   // ��������
#define _DISCONECT_TICKETS (4) // �閧��n�ړ����ɃG���[
#define _TRANS_TICKETS  (5)  //�q�@�ړ��J�n
#define _RETURN_TICKETS  (6) // �A��̐ؕ�

typedef enum {
    _SB_INCOMPLETION,  // ������
    _SB_COMPLETION, // ����

} SecretBaseState;

#define _GOODS_NUM_MAX  (15)   // �u����O�b�Y�̐�   �p�\�R����

#define DEBUG_BLACT_NEW_HOOK //�r���{�[�h�d�l�ύX�ɂ��C���ӏ�

#define _M3DO_NONE (0xff)

//==============================================================================
//	�^�錾
//==============================================================================

#define _SECLET_BASE_DATA_SIZE  (148)

// �閧��n�\���̃f�[�^
typedef struct{
    u8 netID;
    u8 moveID;       //�ړ�����l
    u8 secretBaseDataBuff[_SECLET_BASE_DATA_SIZE];
} SecretBaseInfo;


typedef struct{
    u16 xpos;    // �h�A�̈ʒu
    u16 zpos;
    u8 dir;  // �ǂ��������ɓ����������̂�
} _Pos;

typedef struct{
    u16 xpos;    // �h�A�̈ʒu
    u16 zpos;
    u8 netID;    // �N���ړ����邩
    u8 dir;  // �ǂ��������ɓ����������̂�
    u8 bRemove;
} _SendPos;


// �閧��n�S��
typedef struct{
    FIELDSYS_WORK* pFSys;
    TCB_PTR pDoorTCB;
    SecretBaseInfo secretBaseData[_SECRETBASE_NUM_MAX];  // �閧��n�\����
    SecretBaseInfo* pNowMoveingBase;
    u32 aAttr[_SECRETBASE_NUM_MAX][32];  // �閧��n������f�[�^�R�Q���R�Q
    _Pos secretHeaderData[COMM_MACHINE_MAX]; // �h�A��\�����邽�߂̃f�[�^
    _Pos secretHDataServer[COMM_MACHINE_MAX]; // �h�A��\�����邽�߂̃f�[�^�T�[�o�p
    u8 moveTickets;
    u8 doorAct[ _SECRETBASE_NUM_MAX ];
    u16 doorActX[ _SECRETBASE_NUM_MAX ];
    u16 doorActZ[ _SECRETBASE_NUM_MAX ];
    u8 doorActDir[ _SECRETBASE_NUM_MAX ];
    u8 flagGetLog[COMM_MACHINE_MAX]; // LOG
    u8 flagConqureLog[COMM_MACHINE_MAX];
    u8 flagReverseLog[COMM_MACHINE_MAX];
    u8 travelBase[COMM_MACHINE_MAX]; // �����Ă���閧��n CLIENT�f�[�^
    u8 travelingBase[COMM_MACHINE_MAX]; //�������Ƃ��Ă���閧��n
    u8 travelingBaseSend[COMM_MACHINE_MAX]; //���M���Ă���閧��n
    u8 travelingBaseMessage[COMM_MACHINE_MAX]; //�������Ƃ��Ă���閧��n
    u8 bGoodsTrap[COMM_MACHINE_MAX]; //
    u8 sendBuff[COMM_MACHINE_MAX*4];    // �ړ��ʒu�𑗂�ׂ̃o�b�t�@

    u16 resquePosSX[COMM_MACHINE_MAX];  // ���鎞�ɏo�鎞�̈ʒu���L��
    u16 resquePosSZ[COMM_MACHINE_MAX];
    u16 resqueSDir[COMM_MACHINE_MAX];
    u16 resquePosX;  // ���鎞�ɏo�鎞�̈ʒu���L��
    u16 resquePosZ;
    u8 resqueDir;
    u8 sbNum;       // �e�@����󂯎�����閧��n�̐�
    u8 bChildRecv;    // �q�@�̃f�[�^����M������TRUE
    u8 bPosRecv;    // �q�@�̈ʒu����M������TRUE
    u8 bHalt;      // �T�[�r�X��~���̏ꍇTRUE
    u8 bDoorON;
    u8 bClientBaseIn;  // �N���C�A���g���A
} CommSecretBaseWork;


typedef struct {
    FIELDSYS_WORK* pFSys;
    BMPMENU_WORK*  pYesNoWork;
    TCB_PTR pTCB;
    int seq;
    int subseq;
    int next_zone_id;
    int next_door_id;
    int next_x;
    int next_z;
    int nextDir;
   // int index;
    u8 connectNum;
    u8 timer;
    u8 brightness;
    u8 netID;
    u8 moveID;
    u8 bRemove;
    u8 bMessage;
} EVENT_UGCHG_WORK;


typedef struct{
    FIELDSYS_WORK* pFSys;
    TCB_PTR pTCB;
    BMPMENU_WORK*  pYesNoWork;
    int seq;
   // int index;
    u8 netID;
    u8 timer;
    u8 bBaseDoor;
} _EVENT_DRILL_WORK;


// �V���O���g��
static CommSecretBaseWork* _pCommSecretBaseWork = NULL;

//==============================================================================
// static�錾
//==============================================================================

static void _makeAttr(SECRETBASEDATA* pSecret, u32* attr);
static void _sendSecretBasePosition(void);
static void _doorPictFinalize(void);
static void _doorPictAdd(int x, int z, int dir, int index);
static void _jumpMapForUG(FIELDSYS_WORK* pFSys, int x, int z, int dir, int netID,BOOL bRemove);
static void _returnUGMapEvent(FIELDSYS_WORK* pFSys, int x, int z, int dir, int netID, int moveID);
static void _enterSecretBaseEvent(FIELDSYS_WORK* pFSys, int x, int z, int dir, int netID, int moveID);
static BOOL _enterSecretBaseStart(int secretBaseNo, int playerID);
static void _returnUnderGroundStart(int secretBaseNo, int playerID, BOOL bRemove);
static void _createSecretBase(void);
static void _disconnectEVENT(TCB_PTR tcb, void *work);
static void _doorPictDelete(int netID);
static void _taskDoor(TCB_PTR tcb , void* work);
static void _connectDisable(void);
static void _connectEnable(void);

static const BMPWIN_DAT _yesNoBmpDat = {
    GF_BGL_FRAME3_M, FLD_YESNO_WIN_PX, FLD_YESNO_WIN_PY,
    FLD_YESNO_WIN_SX, FLD_YESNO_WIN_SY, FLD_YESNO_WIN_PAL, FLD_YESNO_WIN_CGX
    };

static const BMPWIN_DAT _connectBmpDat = {
    GF_BGL_FRAME3_M, (FLD_YESNO_WIN_PX-9), FLD_YESNO_WIN_PY,
    (FLD_YESNO_WIN_SX+9), FLD_YESNO_WIN_SY, FLD_YESNO_WIN_PAL, (FLD_YESNO_WIN_CGX-((FLD_YESNO_WIN_SX+13)*2))
    };


// ID�ɂ�镔����BLOCK�ʒu  �ŌオOFFLINE
static u8 _blockToRoomX[]={1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8,0};
static u8 _blockToRoomZ[]={0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0};


#define _DRILL_START_CHECK  (0)
#define _DRILL_START_REFORM  (1)
#define _DRILL_START_NEW  (2)
#define _DRILL_START_RENEW  (3)

#define _RESQUE_POSX (72)
#define _RESQUE_POSZ (437)


//==============================================================================
// �֐�
//==============================================================================

static int _getSecretIndex(int x,int z)
{
    int i;
    int bx = x / _SECRETBASE_ATTR_MAX;
    int bz = z / _SECRETBASE_ATTR_MAX;

    for(i = 0;i < _SECRETBASE_NUM_MAX;i++){
        if((bx == _blockToRoomX[i]) && (bz == _blockToRoomZ[i])){
            return i;
        }
    }
    return _SECRETBASE_MY_ID;  // �I�t���C�������̕���
}

//==============================================================================
/**
 * �閧��n�o���̍��W�����߂�
 * @param   netID
 * @retval  none
 */
//==============================================================================

static BOOL _checkSecretBaseOutPos(int x,int z)
{
    const _Pos base = {_SECLET_INNER_BASE_X, _SECLET_INNER_BASE_Z, DIR_UP};
    const int plus = _SECLET_INNER_BASE_Z_PLUS;
    int id;
    int i;

    for(i = 0; i< COMM_MACHINE_MAX;i++){
        if(x == (base.xpos + i * plus + plus) && 
           (z == base.zpos)){
            return TRUE;
        }
    }
    return FALSE;
}


//==============================================================================
/**
 * �閧��n�o���̍��W�����߂�
 * @param   netID
 * @retval  none
 */
//==============================================================================

static void _getSecretBaseOutPos_local(int netID, _Pos* pPos)
{
    const _Pos base = {_SECLET_INNER_BASE_X, _SECLET_INNER_BASE_Z, DIR_UP};
    const int plus = _SECLET_INNER_BASE_Z_PLUS;
    int id;

    if(CommMPIsConnectStalth()){   // �ʐM�ؒf��Ԃ̏ꍇ
        pPos->xpos = base.xpos;
        pPos->zpos = base.zpos;
        return;
    }
    id = netID;
    if(netID == _SECRETBASE_MY_ID){
        id = 0;
    }
//    pPos->xpos = base.xpos + (id % 8) * plus + plus;
//    pPos->zpos = base.zpos + (id / 8) * plus;
    pPos->xpos = base.xpos + id * plus + plus;
    pPos->zpos = base.zpos;
}

static void _getSecretBaseOutPos(int netID, _Pos* pPos)
{
    int id = netID;

    if(CommGetAloneMode()){
        id = _SECRETBASE_MY_ID;
    }
    _getSecretBaseOutPos_local(id, pPos);
}

//==============================================================================
/**
 * �閧��n��񏉊���
 * @param   ���[�N�|�C���^
 * @retval  none
 */
//==============================================================================

void CommSecretBaseInfoInitialize(void* pWork, FIELDSYS_WORK* pFSys)
{
    int i;
    SecretBaseInfo* pBase;
    SECRETBASEDATA* pSecret;


    if(_pCommSecretBaseWork){  // ���̂Ƃ��뉽�x�������������̂�
        return;
    }

    OHNO_PRINT("_SECLET_BASE_DATA_SIZE �傫���\�� %d\n",SecretBaseData_GetWorkSize());
    GF_ASSERT(_SECLET_BASE_DATA_SIZE == SecretBaseData_GetWorkSize());

    _pCommSecretBaseWork = (CommSecretBaseWork*)pWork;
    MI_CpuFill8(pWork, 0, sizeof(CommSecretBaseWork));
    _pCommSecretBaseWork->pFSys = pFSys;

    for(i = 0; i < COMM_MACHINE_MAX; i++){
        _pCommSecretBaseWork->secretHeaderData[i].xpos = _PLAYER_INVALID_GRID;
        _pCommSecretBaseWork->secretHeaderData[i].zpos = _PLAYER_INVALID_GRID;
        _pCommSecretBaseWork->secretHDataServer[i].xpos = _PLAYER_INVALID_GRID;
        _pCommSecretBaseWork->secretHDataServer[i].zpos = _PLAYER_INVALID_GRID;
        
        _pCommSecretBaseWork->travelingBase[i] = _INVALID_BASE;
        _pCommSecretBaseWork->travelingBaseSend[i]  = _INVALID_BASE;
        _pCommSecretBaseWork->travelBase[i] = _INVALID_BASE;
        // ���b�Z�[�W�\��
        _pCommSecretBaseWork->travelingBaseMessage[i] = _INVALID_BASE;
        _pCommSecretBaseWork->flagGetLog[i] = INVALID_NETID;
        _pCommSecretBaseWork->flagConqureLog[i] = INVALID_NETID;
        _pCommSecretBaseWork->flagReverseLog[i] = INVALID_NETID;

        _pCommSecretBaseWork->resquePosSX[i] = _RESQUE_POSX;
        _pCommSecretBaseWork->resquePosSZ[i] = _RESQUE_POSZ;
        _pCommSecretBaseWork->resqueSDir[i] = DIR_DOWN;
    }

    for(i = 0; i < _SECRETBASE_NUM_MAX; i++){
        pBase = &_pCommSecretBaseWork->secretBaseData[i];
        pSecret = (SECRETBASEDATA*)_pCommSecretBaseWork->secretBaseData[i].secretBaseDataBuff;
        SecretBaseData_Init(pSecret);
        _pCommSecretBaseWork->doorAct[i] = _M3DO_NONE;
        _pCommSecretBaseWork->doorActDir[i] = DIR_NOT;
    }
    MI_CpuFill8(_pCommSecretBaseWork->aAttr, 0xff,  _SECRETBASE_NUM_MAX * _SECRETBASE_ATTR_MAX * (_SECRETBASE_ATTR_MAX/8) );

    UgSecretBaseMakeMyAttr(pFSys);

    _pCommSecretBaseWork->resquePosX = _RESQUE_POSX;
    _pCommSecretBaseWork->resquePosZ = _RESQUE_POSZ;
    _pCommSecretBaseWork->resqueDir = DIR_DOWN;

    _pCommSecretBaseWork->pDoorTCB = TCB_Add(_taskDoor, NULL, TCB_PRIORITY_NORMAL);
    
    
    HWSetDisconnectCallBack(UgSecretBaseResetPlayer);
    
}

//==============================================================================
/**
 * �Z�[�u�f�[�^���玩���̂�����f�[�^�����
 * @param   ���[�N�|�C���^
 * @retval  none
 */
//==============================================================================

void UgSecretBaseMakeMyAttr(FIELDSYS_WORK* pFSys)
{
    SECRETBASEDATA* pSecret;
    SB_RECORD_DATA* pRecord;

    pSecret = SaveData_GetSecretBaseData(GameSystem_GetSaveData(pFSys));
    pRecord = SecretBaseGetSecretBaseRecord(pSecret);
    SecretBaseRecordSetPoint(pRecord,
                             RECORD_Score_Get(SaveData_GetRecord(pFSys->savedata)));

    MI_CpuCopy8(pSecret,_pCommSecretBaseWork->secretBaseData[_SECRETBASE_MY_ID].secretBaseDataBuff,_SECLET_BASE_DATA_SIZE);
    _makeAttr(pSecret,_pCommSecretBaseWork->aAttr[_SECRETBASE_MY_ID]);
    MI_CpuCopy8(pSecret,_pCommSecretBaseWork->secretBaseData[COMM_PARENT_ID].secretBaseDataBuff,_SECLET_BASE_DATA_SIZE);
    _makeAttr(pSecret,_pCommSecretBaseWork->aAttr[COMM_PARENT_ID]);
}

//==============================================================================
/**
 * ������f�[�^���ʂ�
 * @param   ���[�N�|�C���^
 * @retval  none
 */
//==============================================================================
static void _attrBitOff(int xinit, int zinit,const u8* pBuff, u32* attr)
{
    int x,z;

    for(z = 0;z < 3; z++){
        if((zinit+z) < 32){
            for(x = 0;x < 3; x++){
                if(pBuff[z*3 + x]){
                    if((xinit+x) < 32){
                        attr[z+zinit] &= ~(0x1 << (xinit+x));
                    }
                }
            }
        }
    }
}


//==============================================================================
/**
 * ������f�[�^���쐬����
 * @param   ���[�N�|�C���^
 * @retval  none
 */
//==============================================================================

static void _makeAttr(SECRETBASEDATA* pSecret, u32* attr)
{
    int i,x,z;
    const u8* pBuff;
    u8 pcBuff[]={1,1,0,0,0,0,0,0,0};
    u8 blockBuff[]={1,1,0,1,1,0,0,0,0};


    MI_CpuFill8(attr, 0xff,  _SECRETBASE_ATTR_MAX * (_SECRETBASE_ATTR_MAX/8) );

    for(i = 0; i < SECRETBASE_SETUPOBJ_NUM_MAX; i++){
        int type = SecretBaseData_GetGoodsType(pSecret, i);
        if(type == GOODS_INVALID){
            continue;
        }
        x = SecretBaseData_GetGoodsXPos(pSecret,i);
        z = SecretBaseData_GetGoodsZPos(pSecret,i);
        if(i == 0){
            pBuff = pcBuff;
        }
        else if(i < (SECRETBASE_GOODS_NUM_MAX + SECRETBASE_PC_NUM_MAX)){
            pBuff = GOODS_GetGoodsHitData(type);
        }
        else{
            pBuff = blockBuff;
        }
        _attrBitOff(x, z, pBuff, attr);
    }
#if 0
    for(i = 0; i < _SECRETBASE_ATTR_MAX; i++){
        OHNO_PRINT("ATTR>> %x \n",attr[i]);
    }
#endif
}

//==============================================================================
/**
 * �ꎞ�I�ɉ�ʂ���������ۂɌĂԃ��Z�b�g�֐�
 * @param   ���[�N�|�C���^
 * @retval  none
 */
//==============================================================================

void CommSecretBaseInfoReset(void)
{
    _doorPictFinalize();
    if(_pCommSecretBaseWork->pDoorTCB){
        TCB_Delete(_pCommSecretBaseWork->pDoorTCB);
        _pCommSecretBaseWork->pDoorTCB=NULL;
    }
    _pCommSecretBaseWork->bHalt = TRUE;
}

//==============================================================================
/**
 * ��ʂ𕜋A����ۂɌĂԊ֐�
 * @param   ���[�N�|�C���^
 * @retval  none
 */
//==============================================================================

void CommSecretBaseInfoReboot(void)
{
    int i;

    _pCommSecretBaseWork->bHalt = FALSE;

    if(_pCommSecretBaseWork->bClientBaseIn == FALSE){
        OHNO_PRINT("�閧��n�o��ۂɕ\��\n");
        for(i = 0;i < COMM_MACHINE_MAX;i++){
            _doorPictDelete( i );
        }
        for(i = 0; i < COMM_MACHINE_MAX;i++){
            _Pos* pHead = &_pCommSecretBaseWork->secretHeaderData[i];
            if((_PLAYER_INVALID_GRID != pHead->xpos) && (_PLAYER_INVALID_GRID != pHead->zpos)){
                _doorPictAdd(pHead->xpos, pHead->zpos, pHead->dir, i);
            }
        }
    }
    if(_pCommSecretBaseWork->pDoorTCB==NULL){
        _pCommSecretBaseWork->pDoorTCB = TCB_Add(_taskDoor, NULL, TCB_PRIORITY_NORMAL);
    }

}

//==============================================================================
/**
 * �閧��n��񏈗��I��
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommSecretBaseInfoFinalize(void)
{

    HWSetDisconnectCallBack(NULL);


    if(_pCommSecretBaseWork->pDoorTCB){
        TCB_Delete(_pCommSecretBaseWork->pDoorTCB);
        _pCommSecretBaseWork->pDoorTCB=NULL;
    }
    _doorPictFinalize();
    if(_pCommSecretBaseWork){
        sys_FreeMemoryEz(_pCommSecretBaseWork);
    }
    _pCommSecretBaseWork = NULL;
}

//==============================================================================
/**
 * �閧��n��񏈗��ēx������
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommSecretBaseInfoReInit(void)
{
    int i;
    
    for(i = 0; i < COMM_MACHINE_MAX; i++){
        SECRETBASEDATA* pSecret = (SECRETBASEDATA*)_pCommSecretBaseWork->secretBaseData[i].secretBaseDataBuff;
        SecretBaseData_SetMakeDown(pSecret);
        _pCommSecretBaseWork->secretHeaderData[i].xpos = _PLAYER_INVALID_GRID;
        _pCommSecretBaseWork->secretHeaderData[i].zpos = _PLAYER_INVALID_GRID;
        _pCommSecretBaseWork->secretHDataServer[i].xpos = _PLAYER_INVALID_GRID;
        _pCommSecretBaseWork->secretHDataServer[i].zpos = _PLAYER_INVALID_GRID;
        // ��������
//        OHNO_PRINT("��������  \n");
    }
    MI_CpuFill8(_pCommSecretBaseWork->aAttr, 0xff,  _SECRETBASE_NUM_MAX * _SECRETBASE_ATTR_MAX * (_SECRETBASE_ATTR_MAX/8) );
    UgSecretBaseMakeMyAttr(_pCommSecretBaseWork->pFSys);
}





void CommSecretBaseInfoParentDel(void)
{
    int i;
    SecretBaseInfo* pBase;
    SECRETBASEDATA* pSecret;

    for(i = 0; i < _SECRETBASE_NUM_MAX; i++){
        pBase = &_pCommSecretBaseWork->secretBaseData[i];
        pSecret = (SECRETBASEDATA*)_pCommSecretBaseWork->secretBaseData[i].secretBaseDataBuff;
        SecretBaseData_Init(pSecret);
    }
    UgSecretBaseMakeMyAttr(_pCommSecretBaseWork->pFSys);
}


//==============================================================================
/**
 * ���[�N�S�̂̃T�C�Y��Ԃ�
 * @param   none
 * @retval  �󂢂Ă���CommSecretBaseWork�̃|�C���^
 */
//==============================================================================

int CommSecretBaseInfoGetWorkSize(void)
{
    return sizeof(CommSecretBaseWork);
}

//==============================================================================
/**
 * �ʐM�Ŕ����Ă������l�̍폜���s��
 * @param   netID
 * @retval  none
 */
//==============================================================================
/*
void UgSecretBaseDestroyPlayer(int netID)
{
    if(_pCommSecretBaseWork){
        _pCommSecretBaseWork->travelBase[netID] = _INVALID_BASE; // �����Ă���閧��n CLIENT�f�[�^
        _pCommSecretBaseWork->travelingBase[netID] = _INVALID_BASE; //�������Ƃ��Ă���閧��n
        MI_CpuClear8(&_pCommSecretBaseWork->secretBaseData[netID],sizeof(SecretBaseInfo));
        _pCommSecretBaseWork->secretHeaderData[netID].xpos = _PLAYER_INVALID_GRID;
        _pCommSecretBaseWork->secretHeaderData[netID].zpos = _PLAYER_INVALID_GRID;
        if(_pCommSecretBaseWork->doorAct[netID] != _M3DO_NONE){
            M3DO_CleanMap3DObj(_pCommSecretBaseWork->doorAct[netID], _pCommSecretBaseWork->pFSys->Map3DObjExp);
            _pCommSecretBaseWork->doorAct[netID] = _M3DO_NONE;
        }
    }
}
*/
//==============================================================================
/**
 * ���������̔閧��n�ɂ��Ȃ��ꍇ�A�ʐM�Ŕ����Ă������l�̔閧��n�폜���s��
 * @param   netID
 * @retval  none
 */
//==============================================================================
/*
void UgSecretBaseDestroyPlayer(int netID)
{
    if(_pCommSecretBaseWork){
        OHNO_PRINT("������%d - %d��n\n",CommGetCurrentID(),_pCommSecretBaseWork->travelBase[CommGetCurrentID()]);
        if(_pCommSecretBaseWork->travelBase[CommGetCurrentID()] == netID){
            _Pos* pHead = &_pCommSecretBaseWork->secretHeaderData[netID];
            _pCommSecretBaseWork->resquePosX = pHead->xpos;
            _pCommSecretBaseWork->resquePosZ = pHead->zpos;
            _pCommSecretBaseWork->resqueDir = pHead->dir;
        }
        _pCommSecretBaseWork->travelBase[netID] = _INVALID_BASE; // �����Ă���閧��n CLIENT�f�[�^
        _pCommSecretBaseWork->travelingBase[netID] = _INVALID_BASE; //�������Ƃ��Ă���閧��n
        _pCommSecretBaseWork->travelingBaseSend[netID]  = _INVALID_BASE;
        MI_CpuClear8(&_pCommSecretBaseWork->secretBaseData[netID],sizeof(SecretBaseInfo));
        _pCommSecretBaseWork->secretHeaderData[netID].xpos = _PLAYER_INVALID_GRID;
        _pCommSecretBaseWork->secretHeaderData[netID].zpos = _PLAYER_INVALID_GRID;
        if(_pCommSecretBaseWork->doorAct[netID] != _M3DO_NONE){
            M3DO_CleanMap3DObj(_pCommSecretBaseWork->doorAct[netID], _pCommSecretBaseWork->pFSys->Map3DObjExp);
            _pCommSecretBaseWork->doorAct[netID] = _M3DO_NONE;
        }
    }
}
*/
//==============================================================================
/**
 * �ؒf�����q�@�̈ړ����͏���
 * @param   netID
 * @retval  none
 */
//==============================================================================

void UgSecretBaseResetPlayer(int netID)
{
    if(_pCommSecretBaseWork){
        _pCommSecretBaseWork->travelBase[netID] = _INVALID_BASE; // �����Ă���閧��n CLIENT�f�[�^
        _pCommSecretBaseWork->travelingBase[netID] = _INVALID_BASE; //�������Ƃ��Ă���閧��n
        _pCommSecretBaseWork->travelingBaseSend[netID]  = _INVALID_BASE;
        _pCommSecretBaseWork->secretHDataServer[netID].xpos = _PLAYER_INVALID_GRID;
        _pCommSecretBaseWork->secretHDataServer[netID].zpos = _PLAYER_INVALID_GRID;
    }
}

//==============================================================================
/**
 * �閧��n�̍폜�i�N���C�A���g�������ꏏ�ɏ����j���s��
 * @param   netID
 * @retval  none
 */
//==============================================================================

void UgSecretBaseDestroyDoor(int netID)
{
    if(_pCommSecretBaseWork){
        _doorPictDelete(netID);
        _pCommSecretBaseWork->secretHeaderData[netID].xpos = _PLAYER_INVALID_GRID;
        _pCommSecretBaseWork->secretHeaderData[netID].zpos = _PLAYER_INVALID_GRID;
//        MI_CpuClear8(&_pCommSecretBaseWork->secretBaseData[netID],sizeof(SecretBaseInfo));
    }
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
 * �閧��n�̓����������ꍇ�������Ԃ�
 * @param   none
 * @retval  ��������ID��Ԃ� ����������INVALID_NETID
 */
//==============================================================================

static int _getSecretBaseEnter(int x, int z)
{
    int i;

    for(i = 0; i < COMM_MACHINE_MAX; i++){
        SecretBaseInfo* pBase = &_pCommSecretBaseWork->secretBaseData[i];
        SECRETBASEDATA* pSecret = (SECRETBASEDATA*)_pCommSecretBaseWork->secretBaseData[i].secretBaseDataBuff;
        if(!SecretBaseIsSecretBaseMake(pSecret)){
            continue;
        }
        if(!CommPlayerIsActive(i)){
            continue;
        }
        if((x == SecretBaseGetSecretBasePositionX(pSecret)) &&
           (z == SecretBaseGetSecretBasePositionZ(pSecret)) ){   // �ʒu�q�b�g
            return i;
        }
    }
    return INVALID_NETID;
}

//==============================================================================
/**
 * @brief   �ʘH<>�閧��n�̈ړ��C�x���g�J�n CF_SECRETBASE_EVENT_START
 * @param   �R�[���o�b�N����
 * @retval  none
 */
//==============================================================================

typedef struct{
    u16 x;
    u16 z;
    u8 netID;   // �ړ�����l
    u8 baseID;  // �ړ�����ꏊ��ID
    u8 dir;
    u8 bEnterBase;
} _JumpEventPacket;


void UgSecretBaseRecvJumpEvent(int netID, int size, void* pData, void* pWork)
{
    _JumpEventPacket* pJump = pData;

    if(pJump->netID != CommGetCurrentID()){
        return;
    }
    if(_pCommSecretBaseWork->bHalt){
        return;
    }
    
    if(pJump->bEnterBase){
        _enterSecretBaseEvent(_pCommSecretBaseWork->pFSys,
                              pJump->x, pJump->z, DIR_UP,
                              pJump->netID, pJump->baseID);
    }
    else{
        _returnUGMapEvent(_pCommSecretBaseWork->pFSys,
                          pJump->x, pJump->z, pJump->dir,
                          pJump->netID, pJump->baseID);
    }
}

//==============================================================================
/**
 * @brief   �ʘH > �閧��n�̈ړ��Ɏ��s�����ꍇ
 * @param   none
 * @retval  �p�P�b�g�T�C�Y
 */
//==============================================================================

void UgSecretBaseRecvMoveFailed(int netID, int size, void* pData, void* pWork)
{
    u8* pBuff = pData;

    if(CommGetCurrentID() == pBuff[0]){
        CommPlayerHold();
        CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(),
                               msg_underworld_88, TRUE, _msgEndCallBack);
    }
}

//==============================================================================
/**
 * @brief   �ʘH<>�閧��n�̈ړ��C�x���g�J�n�̃p�P�b�g�T�C�Y
 * @param   none
 * @retval  �p�P�b�g�T�C�Y
 */
//==============================================================================

int UgSecretBaseRecvJumpEventSize(void)
{
    return sizeof(_JumpEventPacket);
}

//==============================================================================
/**
 * @brief   �ʘH<>�閧��n�̈ړ��C�x���g�̌��ʂ�Ԃ� CF_SECRETBASE_EVENT_RES
 * @param   �R�[���o�b�N����
 * @retval  none
 */
//==============================================================================

typedef struct {
    u8 baseNo;
    u8 bResult;
    u8 bBaseIn;
} _UgJumpEventResult;

void UgSecretBaseRecvJumpEventRes(int netID, int size, void* pData, void* pWork)
{
    _UgJumpEventResult* pRes = pData;
    u8 id = netID;

    if(CommGetCurrentID()!=COMM_PARENT_ID){
        GF_ASSERT(0);
        return;
    }
    
    if(pRes->bResult){
        if(pRes->bBaseIn){
            // �ʘH>��n
            if(!_enterSecretBaseStart(pRes->baseNo, netID)){
                _pCommSecretBaseWork->travelingBase[netID] = _INVALID_BASE;  // �閧��n�ړ�������
                CommSendFixSizeData_ServerSide(CF_SECRETBASE_MOVE_FAILED,&id);
            }
        }
        else{  // ��n>�ʘH
            _returnUnderGroundStart(pRes->baseNo, netID, FALSE);
        }
    }
    else{
        // �N���C�A���g������̃L�����Z��
        _pCommSecretBaseWork->travelingBase[netID] = _INVALID_BASE;  // �閧��n�ړ�������
        OHNO_PRINT("�L���������M\n");
    }
}

//==============================================================================
/**
 * @brief   �ʘH<>�閧��n�̈ړ��C�x���g�̌��ʂ�Ԃ��ׂ̃R�}���h�̃T�C�Y
 * @param   none
 * @retval  �T�C�Y
 */
//==============================================================================

int UgSecretBaseRecvJumpEventResSize(void)
{
    return sizeof(_UgJumpEventResult);
}

//==============================================================================
/**
 * �ʘH����閧��n�ɓ�����s�֐�
 * @param   secretBaseNo   �閧��n�ԍ�
 * @param   playerID       �v���[���[
 * @retval  �����ꍇTRUE
 */
//==============================================================================

static BOOL _enterSecretBaseStart(int secretBaseNo, int playerID)
{
    _Pos outDoorPos;
    int i;

    SecretBaseInfo* pBase = &_pCommSecretBaseWork->secretBaseData[secretBaseNo];
    SECRETBASEDATA* pSecret = (SECRETBASEDATA*)pBase->secretBaseDataBuff;

    if(!SecretBaseIsSecretBaseMake(pSecret)){  // �ł��Ă��Ȃ��閧��n�ւ̈ړ��͔j��
        return FALSE;
    }

    if(CommIsSendCommand_ServerSize(CF_SECRETBASE_DATA_SERVER)){  // ��������ł����낤�Ƃ��Ă���ꍇ�j��
        return FALSE;
    }
    

    for(i = 0;i < COMM_MACHINE_MAX;i++){
        if(CommIsConnect(i)){
            if(_pCommSecretBaseWork->travelingBaseSend[i] == secretBaseNo){ // ���łɓ�����n�ֈړ���
                OHNO_PRINT("��n�ړ����s %d \n", playerID,secretBaseNo);
                return FALSE;
            }
        }
    }
    _getSecretBaseOutPos(secretBaseNo, &outDoorPos);

    // �閧��n�𑊎�ɑ��M
    pBase->moveID = playerID;
    CommSecretBaseInfoParentSendStart(secretBaseNo); // i�̔閧��n���q�@�ɑ��M
    _pCommSecretBaseWork->travelingBase[playerID] = secretBaseNo;  // j����i�̔閧��n�ɍs�����Ƃ��Ă���
    _pCommSecretBaseWork->travelingBaseSend[playerID]  = secretBaseNo;

    CommPlayerBaseTeleportServer(playerID, outDoorPos.xpos, outDoorPos.zpos, DIR_UP);
    OHNO_PRINT("%d��%d�̔閧��n�ֈړ��J�n %d %d\n", playerID, secretBaseNo,
               CommPlayerGetPosSX(playerID),CommPlayerGetPosSZ(playerID) );
    return TRUE;
}

//==============================================================================
/**
 * �閧��n����ʘH�ɖ߂���s�֐�
 * @param   secretBaseNo   �閧��n�ԍ�
 * @param   playerID       �v���[���[
 * @retval  �����ꍇTRUE
 */
//==============================================================================

static void _returnUnderGroundStart(int secretBaseNo, int playerID, BOOL bRemove)
{
    _SendPos sendPos;
    _Pos outDoorPos;
    int x,z,dir;
    SecretBaseInfo* pBase = &_pCommSecretBaseWork->secretBaseData[secretBaseNo];
    SECRETBASEDATA* pSecret = (SECRETBASEDATA*)pBase->secretBaseDataBuff;

    _getSecretBaseOutPos_local(secretBaseNo, &outDoorPos);
    _pCommSecretBaseWork->travelingBase[playerID] = secretBaseNo;  // j����i�̔閧��n����ł悤�Ƃ��Ă���
//    x = SecretBaseGetSecretBasePositionX(pSecret);
//    z = SecretBaseGetSecretBasePositionZ(pSecret);
//    dir = SecretBaseGetSecretBasePositionDir(pSecret);

    if(CommGetAloneMode()){
        x = _pCommSecretBaseWork->resquePosX;
        z = _pCommSecretBaseWork->resquePosZ;
        dir = _pCommSecretBaseWork->resqueDir;
    }
    else{
        x = _pCommSecretBaseWork->resquePosSX[playerID];
        z = _pCommSecretBaseWork->resquePosSZ[playerID];
        dir = _pCommSecretBaseWork->resqueSDir[playerID];
    }
//    x = _pCommSecretBaseWork->resquePosX;
//    z = _pCommSecretBaseWork->resquePosZ;
//    dir = _pCommSecretBaseWork->resqueDir;
    
    CommPlayerBaseTeleportServer(playerID, x, z, dir);
//    GF_ASSERT((x != 0) && (z != 0));
    OHNO_PRINT("%d �� �閧��n ������ǂ� %d %d %d\n", playerID, x, z , dir);
    x += FieldOBJ_DirAddValueGX( dir);
    z += FieldOBJ_DirAddValueGZ( dir);
    sendPos.xpos = x;
    sendPos.zpos = z;
    sendPos.netID = playerID;
    sendPos.dir = dir;
    sendPos.bRemove = bRemove;
    CommSendFixSizeData_ServerSide(CF_SECRETBASE_RETJUMP,&sendPos);
    CommPlayerSetMoveControl_Server(playerID, FALSE);
}

//==============================================================================
/**
 * �閧��n�t���[������  �ʒu���m�F���Ĉړ�
 * @param   playerID   �v���[���[
 * @retval  �����ꍇTRUE
 */
//==============================================================================

BOOL CommSecretBaseSingleStepFunc(int playerID, int moveX, int moveZ)
{
    int secretBaseNo;
    _SendPos sendPos;
    _Pos outDoorPos;
    _JumpEventPacket jp;
    int x,z;

    if(!_pCommSecretBaseWork){
        return FALSE;
    }
    if((playerID != COMM_PARENT_ID) && !CommIsConnect(playerID) ){
        return FALSE;
    }
    if(CommPlayerIsTrapBind(playerID)){
        return FALSE;
    }
    if(_pCommSecretBaseWork->travelingBase[playerID] != _INVALID_BASE){ // ���łɈړ���
        return TRUE;
    }
    secretBaseNo = _getSecretBaseEnter(moveX, moveZ);
    if(secretBaseNo != INVALID_NETID){
		OHNO_PRINT("--�ړ� %d %d\n",playerID,secretBaseNo);
        _pCommSecretBaseWork->travelingBase[playerID] = secretBaseNo;  // j����i�̔閧��n��go-
        jp.bEnterBase = TRUE;
        jp.x = moveX;
        jp.z = moveZ;
        jp.dir = DIR_UP;
        jp.netID = playerID;
        jp.baseID = secretBaseNo;
        CommSendFixSizeData_ServerSide(CF_SECRETBASE_EVENT_START,&jp);
        CommPlayerSetMoveControl_Server(playerID,FALSE);
        //        _enterSecretBaseEvent(_pCommSecretBaseWork->pFSys,
        //                              moveX, moveZ, DIR_UP, playerID);
        return TRUE;
    }
    for(secretBaseNo = 0; secretBaseNo <= COMM_MACHINE_MAX; secretBaseNo++){
        SecretBaseInfo* pBase = &_pCommSecretBaseWork->secretBaseData[secretBaseNo];
        SECRETBASEDATA* pSecret = (SECRETBASEDATA*)_pCommSecretBaseWork->secretBaseData[secretBaseNo].secretBaseDataBuff;
        if(!SecretBaseIsSecretBaseMake(pSecret)){
            continue;
        }
        _getSecretBaseOutPos_local(secretBaseNo, &outDoorPos);
        if((moveX == outDoorPos.xpos) && (moveZ == outDoorPos.zpos) ){   // �ʒu�q�b�g
            _pCommSecretBaseWork->travelingBase[playerID] = secretBaseNo;  // j����i�̔閧��n����ł悤�Ƃ��Ă���
            jp.bEnterBase = FALSE;
            jp.x = moveX;
            jp.z = moveZ;
            jp.dir = DIR_UP;
            jp.netID = playerID;
            jp.baseID = secretBaseNo;
            CommSendFixSizeData_ServerSide(CF_SECRETBASE_EVENT_START,&jp);
            CommPlayerSetMoveControl_Server(playerID,FALSE);
            //            _returnUGMapEvent(_pCommSecretBaseWork->pFSys,
            //                              pBase->xpos, pBase->zpos, pBase->dir, playerID);
            return TRUE;
        }
    }
    if(_checkSecretBaseOutPos(moveX,moveZ)){  // �閧��n�͂Ȃ����߂��ꍇ
        sendPos.xpos = _pCommSecretBaseWork->resquePosSX[playerID];
        sendPos.zpos = _pCommSecretBaseWork->resquePosSZ[playerID];
        sendPos.netID = playerID;
        sendPos.dir = _pCommSecretBaseWork->resqueSDir[playerID];
        sendPos.bRemove = FALSE;
        _pCommSecretBaseWork->travelingBase[playerID] = COMM_PARENT_ID;  // �����E�o
        CommPlayerBaseTeleportServer(playerID, sendPos.xpos, sendPos.zpos, sendPos.dir);
        CommSendFixSizeData_ServerSide(CF_SECRETBASE_RETJUMP,&sendPos);
        return TRUE;
    }
    return FALSE;
}

//==============================================================================
/**
 * �閧��n����Y�z�ɖ߂�ۂ̃C�x���g���I��
 * @param   event �C�x���g�R���g���[��
 * @retval  none
 */
//==============================================================================

static void _returnUGMapEventForceDel(TCB_PTR tcb,void* work)
{
    EVENT_UGCHG_WORK* mcw = work;

    if(mcw->pYesNoWork){
        BmpYesNoWinDel( mcw->pYesNoWork, HEAPID_FIELD );
    }
    TCB_Delete(tcb);
    sys_FreeMemoryEz(mcw);
    UgMgrEndNowTCB();
}


//==============================================================================
/**
 * �Y�z����閧��n�֍s���̃C�x���g���I��
 * @param   event �C�x���g�R���g���[��
 * @retval  none
 */
//==============================================================================

static void _returnUGMapEventForceDelEnterBaseCheck(TCB_PTR tcb,void* work)
{
    EVENT_UGCHG_WORK* mcw = work;
    _UgJumpEventResult ugJump;

    if(mcw->pYesNoWork){
        BmpYesNoWinDel( mcw->pYesNoWork, HEAPID_FIELD );
    }

    ugJump.bResult = FALSE;
    ugJump.baseNo = mcw->moveID;
    ugJump.bBaseIn = FALSE;
    CommSendFixSizeData(CF_SECRETBASE_EVENT_RES, &ugJump);

    TCB_Delete(tcb);
    sys_FreeMemoryEz(mcw);
    UgMgrEndNowTCB();
    _connectEnable();

}

//==============================================================================
/**
 * �閧��n����Y�z�ɖ߂�ۂ̃C�x���g
 * @param   event �C�x���g�R���g���[��
 * @retval  none
 */
//==============================================================================

typedef enum {
    _RETURN_START,
    _ONLINE_MSGWAIT,
    _ONLINE_YESNO_WAIT,
    _OFFLINE_MSGWAIT,
    _OFFLINE_YESNO_WAIT,
    _CONNECT_CHKMSG,
    _CONNECT_YESNO_WAIT,
    _RETURN_UG,
} ReturnMapCheck_e;


static void GMEVENT_ReturnMapCheck(TCB_PTR tcb,void* work)
{
    EVENT_UGCHG_WORK* mcw = work;
    FIELDSYS_WORK * fsys = mcw->pFSys;
    LOCATION_WORK locationWork;
    int x=0,z=0,msgNo,ret, bClose = FALSE;
    _UgJumpEventResult ugJump;


    switch (mcw->seq) {
      case _RETURN_START:
        if(CommMPIsConnectStalth()){   // �ʐM�ؒf��Ԃ̏ꍇ
            msgNo = msg_underworld_47;
            mcw->seq = _OFFLINE_MSGWAIT;
        }
        else{
            msgNo = msg_underworld_50;
            mcw->seq = _ONLINE_MSGWAIT;
        }
        CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(), msgNo, FALSE, NULL);
        break;
      case _ONLINE_MSGWAIT:
        if(CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0){
            mcw->pYesNoWork = BmpYesNoSelectInit(fsys->bgl,
                                                 &_yesNoBmpDat, MENU_WIN_CGX_NUM,
                                                 MENU_WIN_PAL, HEAPID_FIELD );
            mcw->seq = _ONLINE_YESNO_WAIT;
        }
        break;
      case _ONLINE_YESNO_WAIT:
        ret = BmpYesNoSelectMain(mcw->pYesNoWork, HEAPID_FIELD);
        if(ret == 0){ // �͂���I�������ꍇ
            mcw->pYesNoWork = NULL;
            mcw->seq = _RETURN_UG;
        }
        else if(ret != BMPMENU_NULL){ // ��������I�������ꍇ �I��
            mcw->pYesNoWork = NULL;
            bClose = TRUE;
        }
        break;
      case _OFFLINE_MSGWAIT:
        if(CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0){
            mcw->pYesNoWork = BmpYesNoSelectInit(fsys->bgl,
                                                 &_yesNoBmpDat, MENU_WIN_CGX_NUM,
                                                 MENU_WIN_PAL, HEAPID_FIELD );
            mcw->seq = _OFFLINE_YESNO_WAIT;
        }
        break;
      case _OFFLINE_YESNO_WAIT:
        ret = BmpYesNoSelectMain(mcw->pYesNoWork, HEAPID_FIELD);
        if(ret == 0){ // �͂���I�������ꍇ
            mcw->pYesNoWork = NULL;
            CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(), msg_underworld_48, FALSE, NULL);
            mcw->seq = _CONNECT_CHKMSG;
        }
        else if(ret != BMPMENU_NULL){ // ��������I�������ꍇ �I��
            mcw->pYesNoWork = NULL;
            bClose = TRUE;
        }
        break;
      case _CONNECT_CHKMSG:
        if(CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0){
            mcw->pYesNoWork = BmpYesNoSelectInit(fsys->bgl,
                                                 &_yesNoBmpDat, MENU_WIN_CGX_NUM,
                                                 MENU_WIN_PAL, HEAPID_FIELD );
            mcw->seq = _CONNECT_YESNO_WAIT;
        }
        break;
      case _CONNECT_YESNO_WAIT:
        ret = BmpYesNoSelectMain(mcw->pYesNoWork, HEAPID_FIELD);
        if(ret == 0){ // �͂���I�������ꍇ
            mcw->pYesNoWork = NULL;
            mcw->seq = _RETURN_UG;
        }
        else if(ret != BMPMENU_NULL){ // ��������I�������ꍇ �I��
            mcw->pYesNoWork = NULL;
            bClose = TRUE;
        }
        break;
      case _RETURN_UG:
        CommMsgTalkWindowEnd(CommUnderGetMsgUnderWorld());
        ugJump.bResult = TRUE;
        ugJump.baseNo = mcw->moveID;
        ugJump.bBaseIn = FALSE;
        CommSendFixSizeData(CF_SECRETBASE_EVENT_RES, &ugJump);
        _returnUGMapEventForceDel(tcb,mcw);
        return;
    }

    if(!CommMPIsConnectStalth()){
        if((mcw->moveID < COMM_MACHINE_MAX) && !CommIsConnect(mcw->moveID)
           && (CommGetCurrentID() != COMM_PARENT_ID)){
            OHNO_PRINT("���������\��  %d \n",mcw->moveID);
            bClose = TRUE;
        }
    }
    if(bClose){
        CommMsgTalkWindowEnd(CommUnderGetMsgUnderWorld());
        //        �Ƃ��߂����[�΂ɂ�������
        _returnUGMapEventForceDelEnterBaseCheck(tcb,mcw);
        CommPlayerHoldEnd();
    }
}


//==============================================================================
/**
 * �閧��n����Y�z�ɖ߂�ۂ̃C�x���g
 * @param   pFSys �t�B�[���h�V�X�e��
 * @param   x,y,dir  �ړ���̈ʒu
 * @param   netID �ړ�����l
 * @retval  none
 */
//==============================================================================

static void _returnUGMapEvent(FIELDSYS_WORK* pFSys, int x, int z, int dir, int netID, int moveID)
{
    EVENT_UGCHG_WORK * mcw = NULL;

    _connectDisable();
    mcw = sys_AllocMemoryLo(HEAPID_FIELD, sizeof(EVENT_UGCHG_WORK));
    MI_CpuClear8(mcw, sizeof(EVENT_UGCHG_WORK));
    mcw->next_door_id = DOOR_ID_JUMP_CODE;
    mcw->next_x = x;
    mcw->next_z = z;
    mcw->netID = netID;
    mcw->moveID = moveID;
    mcw->next_zone_id = ZONE_ID_UG;
    mcw->nextDir = dir;
    mcw->pFSys = pFSys;

    mcw->pTCB = TCB_Add(GMEVENT_ReturnMapCheck, mcw,TCB_PRIORITY_NORMAL);
    UgMgrSetNowTCB(mcw,mcw->pTCB,_returnUGMapEventForceDelEnterBaseCheck);
    CommPlayerHold();
}

//==============================================================================
/**
 * �閧��n����Y�z�ɖ߂�ۂ̃C�x���g�R���X�g���N�^�̐���
 * @param   pFSys �t�B�[���h�V�X�e��
 * @param   x,y,dir  �ړ���̈ʒu
 * @param   netID �ړ�����l
 * @retval  �R���X�g���N�^
 */
//==============================================================================

static EVENT_UGCHG_WORK* _createFactoryUGCHG(FIELDSYS_WORK* pFSys, int x, int z, int dir, int netID, int moveID)
{
    //�W�����v
    EVENT_UGCHG_WORK * mcw = NULL;
    //�C�x���g����
    if(pFSys->event==NULL){
        mcw = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(EVENT_UGCHG_WORK));
        MI_CpuClear8(mcw, sizeof(EVENT_UGCHG_WORK));
        mcw->next_door_id = DOOR_ID_JUMP_CODE;
        mcw->next_x = x;
        mcw->next_z = z;
        mcw->netID = netID;
        mcw->moveID = moveID;
        GF_ASSERT(pFSys->location->zone_id == ZONE_ID_UG); //���n��
        mcw->next_zone_id = ZONE_ID_UG;
        mcw->nextDir = dir;
    }
    return mcw;
}

//==============================================================================
/**
 * �����̔閧��n�ɓ����Ă���l���𒲂ׂ�
 * @param   netID   ����
 * @retval  �l��
 */
//==============================================================================

static int _checkMySecretBaseEnterPlayersNum(int netID, BOOL bServer)
{
    int i,num=0,no,x,z;

    for(i = 0;i < COMM_MACHINE_MAX;i++){
        if(!CommIsConnect(i)){
            continue;
        }
        if(bServer){
            x = CommPlayerGetPosSX(i);
            z = CommPlayerGetPosSZ(i);
        }
        else{
            x = CommPlayerGetPosX(i);
            z = CommPlayerGetPosZ(i);
        }
        if((x==COMM_PLAYER_INVALID_GRID) && (z==COMM_PLAYER_INVALID_GRID)){
        }
        else if(UgSecretBaseIsSecretBasePlace(x,z)){
            no = _getSecretIndex( x, z);
            OHNO_PRINT("%d���� %d��n \n", i, no);
            if(no == netID){
                num++;
            }
        }
    }
    OHNO_PRINT("%d�ɓ����Ă���̂�%d�l�ł� \n",netID,num);
    return num;
}

//--------------------------------------------------------------------------------------------
/**
 * �����Ă����E���߂� �E�B���h�E�Z�b�g
 *
 * @param	ini		BGL�f�[�^
 * @param	data	�E�B���h�E�f�[�^
 * @param	cgx		�E�B���h�E�L�����ʒu
 * @param	pal		�E�B���h�E�p���b�g�ԍ�
 * @param	heap	�q�[�vID
 *
 * @return	BMP���j���[���[�N
 *
 * @li	BMP�E�B���h�E��BMP���j���[���[�N��Alloc�Ŏ擾���Ă���
 */
//--------------------------------------------------------------------------------------------
static BMPMENU_WORK * _connectSelectInit(
    GF_BGL_INI * ini, const BMPWIN_DAT * data, u16 cgx, u8 pal, u32 heap )
{
    BMPMENU_HEADER hed;
    MSGDATA_MANAGER * man = CommMsgGetMsgManager(CommUnderGetMsgUnderWorld());
    BMP_MENULIST_DATA * ld;

    ld  = BMP_MENULIST_Create( 2, heap );
    BMP_MENULIST_AddArchiveString( ld, man, msg_underworld_392, 0 );
    BMP_MENULIST_AddArchiveString( ld, man, msg_underworld_393, 1 );

    hed.menu     = ld;
    hed.win      = GF_BGL_BmpWinAllocGet( heap, 1 );
    hed.font     = FONT_SYSTEM;
    hed.x_max    = 1;
    hed.y_max    = 2;
    hed.line_spc = 0;
    hed.c_disp_f = 0;
    hed.line_spc = 0;

    GF_BGL_BmpWinAddEx( ini, hed.win, data );
    BmpMenuWinWrite( hed.win, WINDOW_TRANS_OFF, cgx, pal );
    return BmpMenuAddEx( &hed, 8, 0, 0, heap, PAD_BUTTON_CANCEL );
}

//==============================================================================
/**
 * �Y�z����閧��n�ɓ���ۂ̃C�x���g �l�̂Ǝ����̂ł͋������Ⴄ
 * @param   event �C�x���g�R���g���[��
 * @retval  none
 */
//==============================================================================

typedef enum {
    _ENTER_START,
    _TARGET_MSGWAIT,
    _TARGET_YESNO_WAIT,
    _TARGET_ENTER_SB_WAIT,
    _MY_MSGWAIT,
    _MY_YESNO_WAIT,
    _MYSB_CHANGE_WAIT,
    _MYSB_CHANGE_YESNO_WAIT,
    _ENTER_MYSB_CHANGE_WAIT,
    _ENTER_MYSB_CHANGE,
    _ENTER_SB,
} EnterBaseCheck_e;


static void GMEVENT_EnterBaseCheck(TCB_PTR tcb,void* work)
{
    EVENT_UGCHG_WORK* mcw = work;
    FIELDSYS_WORK * fsys = mcw->pFSys;
    LOCATION_WORK locationWork;
    int x=0,z=0,msgNo,ret, bClose = FALSE;
    _UgJumpEventResult ugJump;

    switch (mcw->seq) {
      case _ENTER_START:
        if(mcw->moveID != mcw->netID){
            msgNo = msg_underworld_45;   //
            mcw->seq = _TARGET_MSGWAIT;
        }
        else{
            msgNo = msg_underworld_41;
            mcw->seq = _MY_MSGWAIT;
        }
        CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(), msgNo, FALSE, NULL);
        break;
      case _TARGET_MSGWAIT:
        if(CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0){
            mcw->pYesNoWork = BmpYesNoSelectInit(fsys->bgl,
                                                 &_yesNoBmpDat, MENU_WIN_CGX_NUM,
                                                 MENU_WIN_PAL, HEAPID_FIELD );
            mcw->seq = _TARGET_YESNO_WAIT;
        }
        break;
      case _TARGET_YESNO_WAIT:
        ret = BmpYesNoSelectMain(mcw->pYesNoWork, HEAPID_FIELD);
        if(ret == 0){ // �͂���I�������ꍇ
            //            mcw->index = CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(), msg_underworld_46, FALSE, NULL);
            mcw->pYesNoWork = NULL;
            mcw->seq = _TARGET_ENTER_SB_WAIT;
        }
        else if(ret != BMPMENU_NULL){ // ��������I�������ꍇ �I��
            mcw->pYesNoWork = NULL;
            bClose = TRUE;
        }
        break;
      case _TARGET_ENTER_SB_WAIT:
        if(CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0){
            mcw->seq = _ENTER_SB;
        }
        break;
        // �����̔閧��n�ɓ���
      case _MY_MSGWAIT:
        if(CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0){
            mcw->pYesNoWork = BmpYesNoSelectInit(fsys->bgl,
                                                 &_yesNoBmpDat, MENU_WIN_CGX_NUM,
                                                 MENU_WIN_PAL, HEAPID_FIELD );
            mcw->seq = _MY_YESNO_WAIT;
        }
        break;
      case _MY_YESNO_WAIT:
        ret = BmpYesNoSelectMain(mcw->pYesNoWork, HEAPID_FIELD);
        if(ret == 0){ // �͂���I�������ꍇ
            mcw->pYesNoWork = NULL;
            if(CommPlayerIsFlagData(mcw->moveID) || (_checkMySecretBaseEnterPlayersNum(mcw->moveID,FALSE) > 0) ){  // ���������Ă�����
                CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(), msg_underworld_44, FALSE, NULL);
                mcw->seq = _TARGET_ENTER_SB_WAIT;
            }
            else{
                CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(), msg_underworld_391, FALSE, NULL);
                mcw->seq = _MYSB_CHANGE_WAIT;
            }
        }
        else if(ret != BMPMENU_NULL){ // ��������I�������ꍇ �I��
            mcw->pYesNoWork = NULL;
            bClose = TRUE;
        }
        break;
      case _MYSB_CHANGE_WAIT:
        if(CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0){
            mcw->pYesNoWork = _connectSelectInit(fsys->bgl,
                                                 &_connectBmpDat, MENU_WIN_CGX_NUM,
                                                 MENU_WIN_PAL, HEAPID_FIELD );
            mcw->seq = _MYSB_CHANGE_YESNO_WAIT;
        }
        break;
      case _MYSB_CHANGE_YESNO_WAIT:
        ret = BmpYesNoSelectMain(mcw->pYesNoWork, HEAPID_FIELD);
        if(ret == 0){ // �����Ă���
            mcw->pYesNoWork = NULL;
            mcw->seq = _TARGET_ENTER_SB_WAIT;
        }
        else if(ret == 1){ // �߂�
            mcw->pYesNoWork = NULL;
            mcw->seq = _ENTER_MYSB_CHANGE_WAIT;
        }
        else if(ret != BMPMENU_NULL){ // �߂�
            mcw->pYesNoWork = NULL;
            bClose = TRUE;
        }
        break;
      case _ENTER_MYSB_CHANGE_WAIT:
        if(CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0){
            // offline����
            CommMsgTalkWindowEnd(CommUnderGetMsgUnderWorld());
            CommFieldStateStalthUnderGround();
            mcw->seq = _ENTER_MYSB_CHANGE;
        }
        break;
      case _ENTER_MYSB_CHANGE:
        if(CommMPIsConnectStalth() && (CommGetCurrentID() == COMM_PARENT_ID)){
            u8 bFlag = _DRILL_START_REFORM;
            // �閧��n�쐬���T�[�o�[�ɑ��M �C�x���g�͏I�� ���b�N�͂������܂� ���ł�OFFLINE
            CommSendFixSizeData(CF_DRILL_START, &bFlag);
            _returnUGMapEventForceDel(tcb,mcw);
            //CommPlayerHoldEnd();
            return; // TRUE;
        }
        break;
      case _ENTER_SB:
        CommMsgTalkWindowEnd(CommUnderGetMsgUnderWorld());
        // ���ʂɓ��邾�� ONLINE
        ugJump.bResult = TRUE;
        ugJump.baseNo = mcw->moveID;
        ugJump.bBaseIn = TRUE;
        CommSendFixSizeData(CF_SECRETBASE_EVENT_RES, &ugJump);
        _returnUGMapEventForceDel(tcb,mcw);
        _pCommSecretBaseWork->moveTickets = _MOVE_TICKETS; // ����
        return;
    }

    if((mcw->moveID != _SECRETBASE_MY_ID) && !CommPlayerIsActive(mcw->moveID)){
        if((_ENTER_MYSB_CHANGE_WAIT != mcw->seq) &&
           (_ENTER_MYSB_CHANGE != mcw->seq)){
            bClose = TRUE;
        }
    }
    if(bClose){  // �Ƃ���
        CommMsgTalkWindowEnd(CommUnderGetMsgUnderWorld());
        _returnUGMapEventForceDelEnterBaseCheck(tcb,mcw);
        CommPlayerHoldEnd();
//        return TRUE;
    }
//    return FALSE;
}

//==============================================================================
/**
 * @brief �Y�z����閧��n�ɍs���ۂ̃C�x���g
 *        �����̔閧��n�̏ꍇ���C�A�E�g���邩�ǂ����������
 * @param   pFSys �t�B�[���h�V�X�e��
 * @param   x,y,dir  �ړ���̈ʒu
 * @param   netID �ړ�����l
 * @retval  none
 */
//==============================================================================

static void _enterSecretBaseEvent(FIELDSYS_WORK* pFSys, int x, int z, int dir,
                                  int netID, int moveID)
{
    EVENT_UGCHG_WORK * mcw = NULL;

    mcw = sys_AllocMemoryLo(HEAPID_FIELD, sizeof(EVENT_UGCHG_WORK));
    MI_CpuClear8(mcw, sizeof(EVENT_UGCHG_WORK));
    mcw->next_door_id = DOOR_ID_JUMP_CODE;
    mcw->next_x = x;
    mcw->next_z = z;
    mcw->netID = netID;
    mcw->moveID = moveID;
    mcw->next_zone_id = ZONE_ID_UG;
    mcw->nextDir = dir;
    mcw->pFSys = pFSys;
    mcw->timer = 0;

    _connectDisable();
    mcw->pTCB = TCB_Add(GMEVENT_EnterBaseCheck, mcw, TCB_PRIORITY_NORMAL);
    UgMgrSetNowTCB(mcw, mcw->pTCB, _returnUGMapEventForceDelEnterBaseCheck);
    CommPlayerHold();
}

//==============================================================================
/**
 * �閧��n�ړ��������������Ƃ��T�[�o�[�ɓ`����R�}���h�̃T�C�Y
 * @param   none
 * @retval  �R�}���h�T�C�Y
 */
//==============================================================================

int CommSecretBaseInfoGetRetJumpSize(void)
{
    return sizeof(_SendPos);
}

//==============================================================================
/**
 * �閧��n�ړ��������������Ƃ��T�[�o�[���������� CF_SECRETBASE_RETJUMP
 * @param   x   �ʒu
 * @param   y
 * @retval  none
 */
//==============================================================================

void CommSecretBaseInfoRecvRetJump(int netID, int size, void* pData, void* pWork)
{
    _SendPos* pSendPos = pData;


    _pCommSecretBaseWork->travelBase[pSendPos->netID] = _INVALID_BASE;
    OHNO_PRINT("_pCommSecretBaseWork->travelBase[] %d %d\n",pSendPos->netID,_INVALID_BASE);

    if(CommGetCurrentID() == pSendPos->netID){
        UnderRecordReset();
        TalkAskForceReset();
        UgMgrForceExitNowTCB();
        UgTrapForceExit(CommGetCurrentID(), FALSE);
//        CommSendFixData(CF_TRAP_END);    // �g���b�v�I���
        CommSendFixData(CF_TRAP_END_FORCE);    // �T�[�o�[������������
        // �ړ��J�n
        _pCommSecretBaseWork->bClientBaseIn = FALSE;
        OHNO_PRINT("�閧��n�Ŗ����ړ��J�n %d %d %d\n", pSendPos->netID,pSendPos->xpos,pSendPos->zpos);
        _jumpMapForUG(_pCommSecretBaseWork->pFSys, pSendPos->xpos, pSendPos->zpos, pSendPos->dir, pSendPos->netID, pSendPos->bRemove);
        _pCommSecretBaseWork->pNowMoveingBase = NULL;
    }
    else{  // �L���������ړ�
        UgTrapTurnDispEnd(pSendPos->netID);
        CommPlayerBaseTeleportClient(pSendPos->netID, pSendPos->xpos, pSendPos->zpos, pSendPos->dir);
    }
}

//==============================================================================
/**
 * �閧��n�ړ��������������Ƃ��T�[�o�[�ɓ`����
 * @param   x   �ʒu
 * @param   y
 * @retval  none
 */
//==============================================================================

void CommSecretBaseInfoJumpEnd(void)
{
    OHNO_PRINT("�閧��n�ړ������� ���MCF_SECRETBASE_JUMP_END\n");
    CommSendFixData(CF_SECRETBASE_JUMP_END);
}

//==============================================================================
/**
 * �閧��n�ړ�������   CF_SECRETBASE_JUMP_END
 * @param   x   �ʒu
 * @param   y
 * @retval  none
 */
//==============================================================================

void CommSecretBaseInfoRecvJumpEnd(int netID, int size, void* pData, void* pWork)
{
    OHNO_PRINT("��M\n");
    _pCommSecretBaseWork->travelingBase[netID] = _INVALID_BASE;
    _pCommSecretBaseWork->travelingBaseSend[netID]  = _INVALID_BASE;
//    CommPlayerManagerReboot();
}

//==============================================================================
/**
 * �閧��n�ړ����s���Ă��邩�ǂ���
 * @param   netID �v���[���[
 * @retval  �ړ����Ă�����TRUE
 */
//==============================================================================

BOOL CommSecretBaseIsTraveling(int netID)
{
    if(_pCommSecretBaseWork){
        if(_pCommSecretBaseWork->travelingBase[netID] != _INVALID_BASE){
            return TRUE;
        }
    }
    return FALSE;
}

//==============================================================================
/**
 * �閧��n����ǉ�����
 * @param   x   �ʒu
 * @param   y
 * @retval  none
 */
//==============================================================================

static void _insertBaseNetID(int x,int y, int dir, int netID)
{
    SecretBaseInfo* pWork = &_pCommSecretBaseWork->secretBaseData[netID];

    if(pWork){
        SECRETBASEDATA* pSecret = (SECRETBASEDATA*)pWork->secretBaseDataBuff;
        SecretBaseSetSecretBasePosition(pSecret,x,y,CommPlayerGetReverseDir(dir));
        pWork->netID = netID;
    }
}

// �q�@���̃v���O����

//==============================================================================
/**
 * �q�@���̃v���O����  �e�@�ɔ閧��n�𑗂�
 *  �Ƃ肠���������̈����
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommSecretBaseInfoChildSendStart(void)
{
    SECRETBASEDATA* pSecret = (SECRETBASEDATA*)_pCommSecretBaseWork->secretBaseData[_SECRETBASE_MY_ID].secretBaseDataBuff;
    int i;
    u8 num=0;
    int id=CommGetCurrentID();

    /// ������ǃL���[�ɂ�ł���
    OHNO_PRINT("�閧��n�𑗐M������-------------------%d-\n", id);

//    if(SecretBaseIsSecretBaseMake(pSecret)){

        OHNO_PRINT("�閧��n���L���[�ɓ��ꂽ----%d-\n", CF_SECRETBASE_DATA);
        CommSetSendQueue(CF_SECRETBASE_DATA,
                         &_pCommSecretBaseWork->secretBaseData[_SECRETBASE_MY_ID],
                         sizeof(SecretBaseInfo));
//    }
}

// �e�@���̃v���O����

//==============================================================================
/**
 * �e�@���̃v���O����  �q�@�Ɏw�肳�ꂽ�閧��n�𑗂�
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommSecretBaseInfoParentSendStart(int netID)
{
    OHNO_PRINT("�q�@�ɔ閧��n�𑗂�܂� %d \n", netID);
    CommSetSendQueue_ServerSide(CF_SECRETBASE_DATA_SERVER,
                                &_pCommSecretBaseWork->secretBaseData[netID],
                                sizeof(SecretBaseInfo));
}

//==============================================================================
/**
 * �q�@���̃v���O����  �e�@���炫��������ړ�����閧��n�f�[�^ CF_SECRETBASE_DATA_SERVER
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommSecretBaseInfoRecvDataServer(int netID, int size, void* pData, void* pWork)
{
    u8* pBuff = pData;
    SecretBaseInfo* pBase = pData;
    SECRETBASEDATA* pSecret;
    _Pos outDoorPos;
    int id,z;

    if(!_pCommSecretBaseWork){
        return;
    }

    if(CommGetCurrentID() == pBase->moveID){
        if(_pCommSecretBaseWork->moveTickets == _ERROR_TICKETS){
            _pCommSecretBaseWork->moveTickets = _NONE_TICKETS;
            CommPlayerHoldEnd();
            CommSendFixData(CF_SECRETBASE_JUMP_END);
            CommPlayerSendPos(FALSE);
            OHNO_PRINT("�G���[�`�P�b�g�Ȃ̂ō��W��߂�����\n");
            return;
        }
    }
    _pCommSecretBaseWork->moveTickets = _TRANS_TICKETS;

    id = pBase->netID;
    OHNO_PRINT("�ړ��\   ---   �閧��n��M���� %d\n",id);
    GF_ASSERT(id < _SECRETBASE_NUM_MAX);
    pBase = &_pCommSecretBaseWork->secretBaseData[id];
    MI_CpuCopy8(pData, pBase,  sizeof(SecretBaseInfo));

    _pCommSecretBaseWork->travelBase[pBase->moveID] = pBase->netID;
    OHNO_PRINT("_pCommSecretBaseWork->travelBase[pBase->moveID] %d %d\n",pBase->moveID,pBase->netID);
    // ���b�Z�[�W�\��
    if( pBase->netID != _SECRETBASE_MY_ID){
        _pCommSecretBaseWork->travelingBaseMessage[pBase->moveID] = pBase->netID;
    }
    // �ړ�����ʒu���v�Z
    _getSecretBaseOutPos(pBase->netID, &outDoorPos);
    if(CommGetCurrentID() == pBase->moveID){
        // �ړ��J�n
        OHNO_PRINT("�N���C�A���g���閧��n�ړ��J�n%d %d %d\n",pBase->netID, outDoorPos.xpos, outDoorPos.zpos-1);
        _pCommSecretBaseWork->bClientBaseIn = TRUE;
        _jumpMapForUG(_pCommSecretBaseWork->pFSys, outDoorPos.xpos, outDoorPos.zpos-1 , DIR_UP, pBase->moveID, FALSE);
        _pCommSecretBaseWork->pNowMoveingBase = pBase;

        pSecret = (SECRETBASEDATA*)pBase->secretBaseDataBuff;
        // �q�@���߂�ꏊ���L��
        _pCommSecretBaseWork->resquePosX = SecretBaseGetSecretBasePositionX(pSecret);
        _pCommSecretBaseWork->resquePosZ = SecretBaseGetSecretBasePositionZ(pSecret);
        _pCommSecretBaseWork->resqueDir = SecretBaseGetSecretBasePositionDir(pSecret);
        OHNO_PRINT("�߂�ꏊ���L�� %d %d %d\n",
                   _pCommSecretBaseWork->resquePosX,
                   _pCommSecretBaseWork->resquePosZ,
                   _pCommSecretBaseWork->resqueDir);
        UgInitialDataSend();
    }
    else{  // �L���������ړ�
        CommPlayerBaseTeleportClient(pBase->moveID, outDoorPos.xpos, outDoorPos.zpos, DIR_UP);
    }
}


//==============================================================================
/**
 * �e�@���̃v���O����  �q�@���炫���閧��n���i�[���� CF_SECRETBASE_DATA �̎󂯎�葤
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommSecretBaseInfoRecvData(int netID, int size, void* pData, void* pWork)
{
    u8* pBuff = pData;
    SecretBaseInfo* pBase;
    SECRETBASEDATA* pSecret;

    if(!_pCommSecretBaseWork){
        return;
    }
    pBase = &_pCommSecretBaseWork->secretBaseData[netID];
    MI_CpuCopy8(pData,  pBase, sizeof(SecretBaseInfo));
    pBase->netID = netID;

    _pCommSecretBaseWork->bChildRecv = TRUE;  //�q�@�f�[�^����M����
    OHNO_PRINT("�e�@���閧��n�󂯎���� %d\n", netID);
    OHNO_SP_PRINT("�e�@���閧��n�󂯎���� %d\n", netID);
    pSecret = (SECRETBASEDATA*)pBase->secretBaseDataBuff;

    // �ʒu�������ւ��Ďq�@�ɕ��z
    _pCommSecretBaseWork->secretHDataServer[netID].xpos = SecretBaseGetSecretBasePositionX(pSecret);
    _pCommSecretBaseWork->secretHDataServer[netID].zpos = SecretBaseGetSecretBasePositionZ(pSecret);
    _pCommSecretBaseWork->secretHDataServer[netID].dir = SecretBaseGetSecretBasePositionDir(pSecret);
    _sendSecretBasePosition();

    // ������f�[�^�쐬
    _makeAttr(pSecret,_pCommSecretBaseWork->aAttr[netID]);
    //UgSecretBaseResetPlayer(netID);

    UgSecretBaseFirstConnectChild(netID);
    
}

//==============================================================================
/**
 * �閧��n�f�[�^�T�C�Y��Ԃ�
 * @param   none
 * @retval  �T�C�Y
 */
//==============================================================================

int CommSecretBaseInfoGetDataSize(void)
{
    return sizeof(SecretBaseInfo);
}

BOOL CommSecretBaseInfoIsChildRecv(void)
{
    return _pCommSecretBaseWork->bChildRecv;
}

void CommSecretBaseResetChildRecv(void)
{
    _pCommSecretBaseWork->bChildRecv = FALSE;
}

BOOL CommSecretBaseInfoIsPosRecv(void)
{
    return _pCommSecretBaseWork->bPosRecv;
}

void CommSecretBaseResetPosRecv(void)
{
    _pCommSecretBaseWork->bPosRecv = FALSE;
}

//==============================================================================
/**
 *  �閧��n�̈ʒu�݂̂��R���p�N�g�����đ���
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _sendSecretBasePosition(void)
{
    int i,j;

    j = 0;
    for(i = 0; i < COMM_MACHINE_MAX;i++){
        _Pos* pHead = &_pCommSecretBaseWork->secretHDataServer[i];
        _pCommSecretBaseWork->sendBuff[j] = pHead->xpos & 0xff;
        j++;
        _pCommSecretBaseWork->sendBuff[j] = ((pHead->xpos >> 8) & 0xf) + ((pHead->zpos >> 4) & 0xf0);
        j++;
        _pCommSecretBaseWork->sendBuff[j] = pHead->zpos & 0xff;
        j++;
        _pCommSecretBaseWork->sendBuff[j] = pHead->dir;
        j++;
    }
    CommSetSendQueue_ServerSide(CF_SECRETBASE_POS,
                                &_pCommSecretBaseWork->sendBuff,
                                sizeof(_pCommSecretBaseWork->sendBuff));
}

//==============================================================================
/**
 *  �閧��n�̈ʒu�݂̂���M����   CF_SECRETBASE_POS
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommSecretBaseInfoRecvPos(int netID, int size, void* pData, void* pWork)
{
    u8* pBuff = (u8*)pData;
    _Pos aDoorData;
    _Pos* pHead;
    _Pos* pOldDoor;

    
    int i,j;
    if(!_pCommSecretBaseWork){
        return;
    }

    for(i = 0;i < COMM_MACHINE_MAX;i++){
        _doorPictDelete( i );
    }
    j = 0;
    for(i = 0; i < COMM_MACHINE_MAX;i++){
        pOldDoor = &_pCommSecretBaseWork->secretHeaderData[i];
        pHead = &aDoorData;
        pHead->xpos = pBuff[j];
        j++;
        pHead->xpos += ((int)pBuff[j] << 8 & 0xf00);
        pHead->zpos = ((int)pBuff[j] << 4 & 0xf00);
        j++;
        pHead->zpos += pBuff[j];
        j++;
        pHead->dir = pBuff[j];
        j++;
        if((_PLAYER_INVALID_GRID != pHead->xpos) && (_PLAYER_INVALID_GRID != pHead->zpos)){
//            if((pHead->xpos == pOldDoor->xpos) && (pHead->zpos == pOldDoor->zpos) && (pHead->dir == pOldDoor->dir)){
//                OHNO_PRINT("����������u���Ȃ�\n");
//            }
//            else{
                MI_CpuCopy8(pHead, pOldDoor, sizeof(_Pos));
                _doorPictAdd(pHead->xpos, pHead->zpos, pHead->dir, i);
//            }
        }
    }
    _pCommSecretBaseWork->bPosRecv = TRUE;
    OHNO_PRINT("�閧��n�ʒu��M\n");
}

//==============================================================================
/**
 *  �閧��n�̈ʒu�f�[�^�̃T�C�Y��Ԃ�
 * @param   none
 * @retval  none
 */
//==============================================================================

int CommSecretBaseInfoGetPosSize(void)
{
    return sizeof(_pCommSecretBaseWork->sendBuff);
}

//==============================================================================
/**
 * �h�A��\��
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _doorPictAdd(int x, int z, int dir, int index)
{
    VecFx32 vtx;
    int px,pz;

    _pCommSecretBaseWork->doorActDir[index] = dir;
    _pCommSecretBaseWork->doorActX[index] = x;
    _pCommSecretBaseWork->doorActZ[index] = z;
}

//==============================================================================
/**
 * �h�A����Ԃ��݂ĕ\��
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _taskDoor(TCB_PTR tcb , void* work)
{
    int i,x,z,dir,px,pz;
    
    if(_pCommSecretBaseWork->bHalt){
        return;
    }
    if(!_pCommSecretBaseWork->bDoorON){
        return;
    }
    if(_pCommSecretBaseWork->pFSys->player==NULL){
        return;
    }
    
    px = Player_NowGPosXGet( _pCommSecretBaseWork->pFSys->player );
    pz = Player_NowGPosZGet( _pCommSecretBaseWork->pFSys->player );
    if(UgSecretBaseIsSecretBasePlace(px,pz)){
 //       OHNO_PRINT("�閧��n�ł̓h�A�����Ȃ� %d %d\n",px,pz);
        return;  //�������閧��n�ɂ���ꍇ�������Ȃ�
    }


    for(i = 0;i < _SECRETBASE_NUM_MAX; i++){

        if(i < COMM_MACHINE_MAX){
            if(NULL==CommInfoGetMyStatus(i)){
                UgSecretBaseDestroyDoor(i);
                UgSecretBaseTrapGoodsReset(i);
//                UgSecretBaseResetPlayer(i);
            }
        }

        if(_pCommSecretBaseWork->doorActDir[i] != (u8)DIR_NOT){
            dir = _pCommSecretBaseWork->doorActDir[i];
            x = _pCommSecretBaseWork->doorActX[i];
            z = _pCommSecretBaseWork->doorActZ[i];
            if(_pCommSecretBaseWork->doorAct[i] != _M3DO_NONE){
                M3DO_CleanMap3DObj(_pCommSecretBaseWork->doorAct[i],
                                   _pCommSecretBaseWork->pFSys->Map3DObjExp);
            }
            {
                VecFx32 vtx;
                vtx.x = (x) * (FX32_ONE*16) + (FX32_ONE*8);
                vtx.y = 0;
                vtx.z = (z) * (FX32_ONE*16) + (FX32_ONE*8);
                _pCommSecretBaseWork->doorAct[i] =
                    M3DO_SetMap3DObjExp(_pCommSecretBaseWork->pFSys->Map3DObjExp,
                                        _pCommSecretBaseWork->pFSys->MapResource,
                                        BMID_UG_HOLE_B+dir,
                                        &vtx, NULL,
                                        _pCommSecretBaseWork->pFSys->field_3d_anime);
            }
        }
    }
}


//==============================================================================
/**
 * �h�A������
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _doorPictDelete(int netID)
{
    if(_pCommSecretBaseWork->doorAct[netID] != _M3DO_NONE){
        M3DO_CleanMap3DObj(_pCommSecretBaseWork->doorAct[netID],
                           _pCommSecretBaseWork->pFSys->Map3DObjExp);
        OHNO_PRINT("�h�A����^^^^^^ %d\n",netID);
        
        _pCommSecretBaseWork->doorAct[netID] = _M3DO_NONE;
        _pCommSecretBaseWork->doorActDir[netID] = DIR_NOT;
    }
}

//==============================================================================
/**
 * �h�A������
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _doorPictFinalize(void)
{
    int i;

    if(_pCommSecretBaseWork==NULL){
        return;
    }
    for(i = 0; i < _SECRETBASE_NUM_MAX; i++){
        _doorPictDelete(i);
    }
}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static BOOL Sub_UgFadeOut(GMEVENT_CONTROL * event)
{
    FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
    EVENT_UGCHG_WORK * mcw = FieldEvent_GetSpecialWork(event);

    switch (mcw->subseq) {
      case 0:
        GameSystem_FinishFieldProc(fsys);
        (mcw->subseq) ++;
        break;
      case 1:
        if (!GameSystem_CheckFieldProcExists(fsys)) {
            mcw->subseq = 0;
            return TRUE;
        }
        break;
    }
    return FALSE;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static BOOL Sub_UgFadeIn(GMEVENT_CONTROL * event)
{
    FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
    EVENT_UGCHG_WORK * mcw = FieldEvent_GetSpecialWork(event);

    switch (mcw->subseq) {
      case 0:
        GameSystem_CreateFieldProc(fsys);
        (mcw->subseq) ++;
        break;
      case 1:
        if (FieldEvent_Cmd_WaitMapProcStart(fsys)) {
            mcw->subseq = 0;
            return TRUE;
        }
        break;
    }
    return FALSE;
}


//==============================================================================
/**
 *  �w��ʒu�փW�����v����C�x���g
 * @param   event �C�x���g�R���g���[���[
 * @retval  none
 */
//==============================================================================

static BOOL GMEVENT_JumpMapForUG(GMEVENT_CONTROL * event)
{
    FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
    EVENT_UGCHG_WORK * mcw = FieldEvent_GetSpecialWork(event);
    LOCATION_WORK locationWork;
    int x=0,z=0;

    enum{
        _JP_START,
        _JP_START_WAIT,
        _RADAR_WAIT,
        _UG_FADE_WAIT,
        _MAP_CHANGE,
        _UG_FADEIN,
        _WIPE_IN,
        _FADE_END,
        _REMOVEPLAYER_MSGWAIT,
        _START_WALK,
        _START_TURN,
        _TURN_FRONT,
        _MESSAGE_WAIT,
        _END,

    };


    switch (mcw->seq) {
      case _JP_START:
        UgSecretBaseBootOn(FALSE);
        _connectDisable();
        mcw->connectNum = CommGetConnectNum();
        CommDisableSendMoveData();
        CommDigStoneManagerReset();  //�^�}�������Ă���Ɠs��������
        if( CommStateJumpUnderGround() ){
            mcw->seq = _JP_START_WAIT;
        }
		break;
      case _JP_START_WAIT:
        WIPE_SYS_ExeEnd(); 
        WIPE_SYS_Start(WIPE_PATTERN_FSAM,
                       WIPE_TYPE_HOLEOUT,WIPE_TYPE_TUNNELOUT,
                       WIPE_FADE_BLACK,COMM_BRIGHTNESS_SYNC,
                       1,HEAPID_FIELD);
        UnderGround_RadarEnd(fsys->UnderGroundRadar);
        Snd_SePlay(UG_SE_HOLE_IN);
        mcw->seq++;
        break;
      case _RADAR_WAIT:
        if(WIPE_SYS_EndCheck()){
            if (fsys->UnderGroundRadar == NULL){
                (mcw->seq) ++;
            }
        }
        break;
      case _UG_FADE_WAIT:
        if(Sub_UgFadeOut(event)){		// �v���b�NChange
            (mcw->seq) ++;
        }
        break;
      case _MAP_CHANGE:
        locationWork.zone_id = mcw->next_zone_id;
        locationWork.door_id = mcw->next_door_id;
        OHNO_PRINT("---�ړ��ڕW  %d %d \n",mcw->next_x,mcw->next_z);
        
        locationWork.grid_x = mcw->next_x;
        locationWork.grid_z = mcw->next_z;
        locationWork.dir = mcw->nextDir;
        //CommPlayerManagerReset();
        EventCmd_UgJumpByLocation(event, &locationWork);
        (mcw->seq) ++;
        break;
      case _UG_FADEIN:
        if(Sub_UgFadeIn(event)){		// �v���b�NChange
            //CommPlayerManagerReboot();
            (mcw->seq) ++;
        }
        break;
      case _WIPE_IN:
        fsys->UnderGroundRadar = UnderGround_RadarInit(fsys);		//�Y�z���[�_�[��ʂn�m
        WIPE_SYS_ExeEnd();
        WIPE_SYS_Start(WIPE_PATTERN_FMAS,
                       WIPE_TYPE_HOLEIN, WIPE_TYPE_TUNNELIN,
                       WIPE_FADE_BLACK,COMM_BRIGHTNESS_SYNC,
                       1,HEAPID_FIELD);
        (mcw->seq) ++;
        break;
      case _FADE_END:
        if(!WIPE_SYS_EndCheck()){
            break;
        }
        if( CommMPIsConnectStalth() && !UgSecretBaseIsSecretBasePlace(mcw->next_x, mcw->next_z)){
            mcw->bMessage = FALSE;
        }
        else{
            mcw->bMessage = TRUE;
        }
        CommEnableSendMoveData();
        CommPlayerHold();
        // �Â��t�H���g�p���b�g
        ArcUtil_PalSet(ARC_UG_TRAP_GRA, NARC_ug_trap_ug_menu_NCLR, PALTYPE_MAIN_BG, FLD_MESFRAME_PAL*0x20, 4*0x20,  HEAPID_FIELD);
        MenuWinGraphicSet(
            fsys->bgl, GF_BGL_FRAME3_M, MENU_WIN_CGX_NUM,
            MENU_WIN_PAL, MENU_TYPE_UG, HEAPID_FIELD );
        if(mcw->bRemove){
            CommPlayerHoldBitOff();
            CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(), msg_underworld_51, FALSE, NULL);
            mcw->seq = _REMOVEPLAYER_MSGWAIT;
        }
        else if(!_pCommSecretBaseWork->bClientBaseIn){
            mcw->seq = _END;
        }
        else{
            mcw->timer = 0;
            mcw->seq = _START_WALK;
        }
        break;
      case _START_WALK:
        mcw->timer++;
/*        if(mcw->timer > 20){
            int xpos = Player_NowGPosXGet( fsys->player );
            int zpos = Player_NowGPosZGet( fsys->player );
            if(!CommMPIsConnectStalth() || !mcw->bMessage){
                CommPlayerSendPosXZ(FALSE,xpos,zpos);
                mcw->timer = 0;
                mcw->seq = _START_TURN;
            }
            else{
                CommPlayerSendPosXZ(FALSE,xpos,zpos - 1);
                mcw->timer = 0;
                mcw->seq = _START_TURN;
            }
        }*/
        mcw->timer = 0;
        mcw->seq = _START_TURN;
        break;
      case _START_TURN:
        mcw->timer++;
        if(mcw->timer > 10){
            if(!CommMPIsConnectStalth() || !mcw->bMessage){
                mcw->seq = _END;
            }
            else{
                mcw->seq = _TURN_FRONT;
            }
        }
        break;
      case _TURN_FRONT:
        CommSetForceDir();
        Player_AcmdSet( fsys->player, FieldOBJ_AcmdCodeDirChange( DIR_DOWN, AC_STAY_WALK_U_4F ) );
        CommPlayerSetDir(DIR_DOWN);
        CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(), msg_underworld_68, FALSE, NULL);
        Snd_SePlay(UG_SE_CLOSE_DOOR);
        mcw->seq = _MESSAGE_WAIT;
        break;
      case _MESSAGE_WAIT:
        if(CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0){
            if(sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL)){
                mcw->seq = _END;
                CommMsgTalkWindowEnd(CommUnderGetMsgUnderWorld());
                CommPlayerSetDir(DIR_UP);
            }
        }
        break;
      case _END:
        if( CommMPIsConnectStalth() && !UgSecretBaseIsSecretBasePlace(mcw->next_x, mcw->next_z)){
            CommFieldStateUnderGroundReConnect();  // �Đڑ�����ꍇ�̏���
        }
        else{
            CommStateJumpEndUnderGround(); // �ړ��I������ꍇ�̒ʐM�֘A����
        }
        CommPlayerHoldEnd();
        sys_FreeMemoryEz(mcw);
        if( CommMPIsConnectStalth() && UgSecretBaseIsSecretBasePlace(mcw->next_x, mcw->next_z) ){
            UgMgrSetNoneRadarDisp();
        }
        else{
            UgMgrSetMyTrapRadarDisp();
        }
        OHNO_PRINT("�ړ��I���\n");
        if((_pCommSecretBaseWork->moveTickets == _DISCONECT_TICKETS) && (_pCommSecretBaseWork->bClientBaseIn)){
            OHNO_PRINT("�G���[�Ȃ�߂��\n");
            _pCommSecretBaseWork->moveTickets = _RETURN_TICKETS;
        }
        else{
            _pCommSecretBaseWork->moveTickets = _NONE_TICKETS;
        }
        _connectEnable();
        UgSecretBaseBootOn(TRUE);
        return TRUE;
      case _REMOVEPLAYER_MSGWAIT:
        if(CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0){
            if(sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL)){
                mcw->seq = _END;
                CommMsgTalkWindowEnd(CommUnderGetMsgUnderWorld());
                return FALSE;
            }
        }
        if((CommGetConnectNum() > 1)  && (mcw->connectNum==0)){  // �N���ƂȂ�������
            OHNO_PRINT("�Ȃ������̂ŃE�C���h�E�����܂�\n");
            mcw->seq = _END;
            CommMsgTalkWindowEnd(CommUnderGetMsgUnderWorld());
        }
        break;
    }
    return FALSE;
}

//==============================================================================
/**
 *  �w��ʒu�փW�����v����C�x���g�N��
 * @param   pFSys  FIELDSYS_WORK*
 * @param   int x, int z, int dir  �ړ�����ʒu�ƕ���
 * @retval  none
 */
//==============================================================================

static void _jumpMapForUG(FIELDSYS_WORK* pFSys, int x, int z, int dir, int netID, BOOL bRemove)
{
    EVENT_UGCHG_WORK * mcw = _createFactoryUGCHG(pFSys, x, z, dir, netID, netID);
    if(mcw){
        //�C�x���g����
        mcw->bRemove = bRemove;
        FieldEvent_Set(pFSys, GMEVENT_JumpMapForUG, mcw);
    }
}


//==============================================================================
/**
 *  �h�����Ŕ閧��n�����
 * @param   none
 * @retval  none
 */
//==============================================================================

typedef enum{
    _DRILL_ANIM,
    _ENTER_FIRST_WAIT,
    _HOLE_MODEL_PUT,
    _QUESTION_MSG,
    _NODIG_WAIT,
    _YESNO_MSG,
    _YESNO_WAIT,
    _SHUTDOWN_MSG,
    _SHUTDOWN_WAIT,
    _DISCONNECT_MSG_WAIT,
    _DISCONNECT_WAIT,
};

static void _GMEVENT_Drill(TCB_PTR tcb, void* work)
{
    _EVENT_DRILL_WORK * mdw = work;
    FIELDSYS_WORK* fsys = mdw->pFSys;
    LOCATION_WORK locationWork;
    u32 ret;
    BOOL bExit = FALSE;
    int msgNo;
    int x,z,dir;

    switch (mdw->seq) {
      case _DRILL_ANIM:
        {
            SECRETBASEDATA* pSecret = SaveData_GetSecretBaseData(fsys->savedata);
            mdw->bBaseDoor = SecretBaseIsSecretBaseMake(pSecret);
        }
        CommPlayerHold();
        CommMsgRegisterUGTrapName(CommUnderGetMsgUnderWorld(), UG_TRAPTYPE_DRILL);
        Snd_SePlay(UG_SE_DRILL);

        FE_FldOBJDrillSet( Player_FieldOBJGet(fsys->player), 0, 0, 0 );

        CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(), msg_underworld_36, FALSE, NULL);
        mdw->seq = _ENTER_FIRST_WAIT;
        mdw->timer = 0;
        break;
      case _ENTER_FIRST_WAIT:
        if(CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0){
            mdw->timer++;
            if(mdw->timer > 30){
                mdw->seq = _HOLE_MODEL_PUT;
            }
        }
        break;
      case _HOLE_MODEL_PUT:
        {
            x = CommPlayerGetPosXDirAdd(CommGetCurrentID());
            z = CommPlayerGetPosZDirAdd(CommGetCurrentID());
            dir = CommPlayerGetReverseDir(Player_DirGet( fsys->player ));
            CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(), msg_underworld_37, FALSE, NULL);
            _doorPictAdd(x, z, dir, _SECRETBASE_MY_ID);  // �O�̌��͊J�����܂�
            FE_FldOBJTrapsmogSet(fsys, x, 0, z);
            mdw->seq = _QUESTION_MSG;
        }
        break;
      case _QUESTION_MSG:
        if(CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0){
            if(_checkMySecretBaseEnterPlayersNum(CommGetCurrentID(),FALSE)){
                msgNo = msg_underworld_57;
                mdw->seq = _NODIG_WAIT;
            }
            else if(mdw->bBaseDoor){
                msgNo = msg_underworld_39;
                mdw->seq = _YESNO_MSG;
            }
            else{
                msgNo = msg_underworld_38;
                mdw->seq = _YESNO_MSG;
            }
            CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(), msgNo, FALSE, NULL);
        }
        break;
      case _NODIG_WAIT:
        if(CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0){
            if(sys.trg & PAD_BUTTON_DECIDE){
                bExit = TRUE;
            }
        }
        break;
      case _YESNO_MSG:
        if(CommMsgIsOutputing(CommUnderGetMsgUnderWorld()) == 0){
            mdw->pYesNoWork = BmpYesNoSelectInit(fsys->bgl,
                                                 &_yesNoBmpDat, MENU_WIN_CGX_NUM,
                                                 MENU_WIN_PAL, HEAPID_FIELD );
            mdw->seq = _YESNO_WAIT;
        }
        break;
      case _YESNO_WAIT:
        ret = BmpYesNoSelectMain(mdw->pYesNoWork, HEAPID_FIELD);
        if(ret == 0){ // �͂���I�������ꍇ
            mdw->seq = _DISCONNECT_MSG_WAIT;
            mdw->pYesNoWork = NULL;
        }
        else if(ret != BMPMENU_NULL){ // ��������I�������ꍇ �I��
            bExit = TRUE;
            mdw->pYesNoWork = NULL;
        }
        break;
      case _DISCONNECT_MSG_WAIT:
        // offline�̊�n�ֈړ� �ʐM�ؒf
        CommUnderBagDeleteTrap(UG_TRAPTYPE_DRILL);  // �h�����������ŏ���
        CommMsgTalkWindowEnd(CommUnderGetMsgUnderWorld());
//        CommStateFieldEnableChange();
        CommFieldStateStalthUnderGround();
        mdw->seq = _DISCONNECT_WAIT;
        break;
      case _DISCONNECT_WAIT:
        if(CommMPIsConnectStalth() && (CommGetCurrentID() == COMM_PARENT_ID)){
            u8 bFlag = _DRILL_START_NEW;

            if(mdw->bBaseDoor){
                bFlag = _DRILL_START_RENEW;
            }
            // �閧��n�쐬���T�[�o�[�ɑ��M �C�x���g�͏I�� ���b�N�͂������܂� ���ł�OFFLINE
            _createSecretBase();  // �V�K�쐬
            CommSendFixSizeData(CF_DRILL_START, &bFlag);
            TCB_Delete(tcb);
            sys_FreeMemoryEz(mdw);
            UgMgrEndNowTCB();
            return;
        }
        break;
    }
    if(bExit){
        CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(),
                               msg_underworld_56, TRUE, _msgEndCallBack);
        _doorPictDelete(_SECRETBASE_MY_ID);
        {
            x = CommPlayerGetPosXDirAdd(CommGetCurrentID());
            z = CommPlayerGetPosZDirAdd(CommGetCurrentID());
            FE_FldOBJTrapsmogSet(fsys, x, 0, z);
        }
        TCB_Delete(tcb);
        sys_FreeMemoryEz(mdw);
        UgMgrEndNowTCB();
        _connectEnable();
    }
}

//==============================================================================
/**
 * @brief   �閧��n�̌����@��
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommSecretBaseDrillStart(void)
{
    u8 bFlag = _DRILL_START_CHECK;
    CommSendFixSizeData(CF_DRILL_START, &bFlag);   // �܂��͌@���Ă������ǂ����₢���킹
}

//==============================================================================
/**
 * @brief   �閧��n�̌����@�� CF_DRILL_START
 * @param   none
 * @retval  none
 */
//==============================================================================

typedef struct{
    u8 netID;
    u8 result;
} _resultStruct;

typedef enum{
    _SB_CREATE_NG,
    _SB_CREATE_START,
    _SB_CREATED,
    _SB_CREATED_CHANGE,
    _SB_CREATED_NEW,
    _SB_CREATE_FAILED,
    _SB_INSB_FAILED,
};


int CommSecretBaseDrillStartResultSize(void)
{
    return sizeof(_resultStruct);
}

void CommSecretBaseRecvDrillStart(int netID, int size, void* pData, void* pWork)
{
    u8* pCreateFlag = pData;
    int x = CommPlayerGetPosSXDirAdd(netID);
    int z = CommPlayerGetPosSZDirAdd(netID);
    int x1,z1,x2,z2;
    int dir = CommPlayerGetSDir(netID);
    _resultStruct ret;
    int id;

    x2 = x - CommPlayerGetPosSX(netID);  //���E�̂����������
    z2 = z - CommPlayerGetPosSZ(netID);
    if(z2 != 0){
        x1 = x+1;
        x2 = x-1;
        z2 = z1 = z;
    }
    else{
        z1 = z+1;
        z2 = z-1;
        x2 = x1 = x;
    }
    ret.netID = netID;
    if(pCreateFlag[0] == FALSE){
        ret.result = _SB_CREATE_NG;
    }
    else{
        ret.result = _SB_CREATE_FAILED;
    }
    id = _getSecretBaseEnter(x, z);
//    if((id != INVALID_NETID) && (id != netID)){   // �N���̔閧��n������ꍇ���Ȃ�
    if((pCreateFlag[0] == FALSE) && (id != INVALID_NETID)){   // �N���̔閧��n������ꍇ���Ȃ�
        OHNO_PRINT("�������Ƃ���Ƃق�Ȃ�----\n");
    }
    else if(UgSecretBaseIsSecretBasePlace(x, z)){  // �������閧��n���̏ꍇ�ق�Ȃ�
        ret.result = _SB_INSB_FAILED;
    }
    else if(GetHitAttr(_pCommSecretBaseWork->pFSys,x,z) &&
            GetHitAttr(_pCommSecretBaseWork->pFSys,x1,z1) &&
            GetHitAttr(_pCommSecretBaseWork->pFSys,x2,z2)){  // �����肠��ꍇ
        if(pCreateFlag[0] == FALSE){    // ���C�x���g���J�n���Ă������𑗐M
            ret.result = _SB_CREATE_START;
        }
        else{
            _insertBaseNetID(x, z, dir, _SECRETBASE_MY_ID);  // ��쐬
            if(_enterSecretBaseStart(_SECRETBASE_MY_ID,netID)){  // ��W�����v
                OHNO_PRINT("CF_DRILL_START �ړ��J�n���b�Z�[�W������ %d\n",netID);
                switch(pCreateFlag[0]){
                  case _DRILL_START_REFORM:
                    ret.result = _SB_CREATED;
                    break;
                  case _DRILL_START_RENEW:
                    ret.result = _SB_CREATED_CHANGE;
                    break;
                  case _DRILL_START_NEW:
                    ret.result = _SB_CREATED_NEW;
                    break;
                }
            }
        }
    }
    CommSendFixSizeData_ServerSide(CF_DRILL_START_RESULT, &ret);
}



static void _returnDrillEventForceDel(TCB_PTR tcb,void* work)
{
    _EVENT_DRILL_WORK* mcw = work;


    _doorPictDelete(_SECRETBASE_MY_ID);

    if(mcw->pYesNoWork){
        BmpYesNoWinDel( mcw->pYesNoWork, HEAPID_FIELD );
    }
    TCB_Delete(tcb);
    sys_FreeMemoryEz(mcw);
    UgMgrEndNowTCB();
    CommPlayerHoldEnd();
    _connectEnable();
}

//==============================================================================
/**
 * @brief   �h�����C�x���g�Z�b�g
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _drillEventStart(void)
{
    _EVENT_DRILL_WORK * mdw;

    _connectDisable();
    mdw = sys_AllocMemoryLo(HEAPID_FIELD, sizeof(_EVENT_DRILL_WORK));
    MI_CpuClear8(mdw,sizeof(_EVENT_DRILL_WORK));
    mdw->seq = _DRILL_ANIM;
    mdw->netID = CommGetCurrentID();  // �J�n����ۂ�ID ���ꂪ�H��������狭���I��
    mdw->pFSys = _pCommSecretBaseWork->pFSys;
    
    mdw->pTCB = TCB_Add( _GMEVENT_Drill, mdw, TCB_PRIORITY_NORMAL);
    UgMgrSetNowTCB(mdw, mdw->pTCB, _returnDrillEventForceDel);

}

//==============================================================================
/**
 * @brief   �閧��n�̌����@�� �T�[�o�[����̖߂�   CF_DRILL_START_RESULT
 * @param   none
 * @retval  none
 */
//==============================================================================


void CommSecretBaseRecvDrillStartResult(int netID, int size, void* pData, void* pWork)
{
    _resultStruct* pRet = pData;
    SB_RECORD_DATA* pRec = SaveData_GetSecretBaseRecord(GameSystem_GetSaveData(_pCommSecretBaseWork->pFSys));

    if(pRet->netID != CommGetCurrentID()){  // �{�l�ȊO�֌W�Ȃ�
        return;
    }
    OS_TPrintf("���@�茋�� %d\n",pRet->result);
    if(pRet->result == _SB_CREATE_NG){
        CommPlayerHold();
        CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(), msg_underworld_54, TRUE, _msgEndCallBack);
        _connectEnable();
    }
    else if(pRet->result == _SB_CREATE_START){
        // �ǂɌ������鉉�o�J�n
        _drillEventStart();
    }
    else if(pRet->result ==_SB_INSB_FAILED){
        CommPlayerHold();
        CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(), msg_underworld_74, TRUE, _msgEndCallBack);
        _connectEnable();
    }
    else if(pRet->result == _SB_CREATE_FAILED){  //�����̌����łق�Ȃ�����
        CommPlayerHold();
        CommMsgTalkWindowStart(CommUnderGetMsgUnderWorld(), msg_underworld_88, TRUE, _msgEndCallBack);
        CommFieldStateUnderGroundReConnect();
        _connectEnable();
    }
    else if((pRet->result == _SB_CREATED) ||
            (pRet->result == _SB_CREATED_CHANGE) ||
            (pRet->result == _SB_CREATED_NEW)){  // ����������   // MAPCHANGE     // �ʐM�ؒf
        _Pos outDoorPos;
        int x = CommPlayerGetPosXDirAdd(pRet->netID);
        int z = CommPlayerGetPosZDirAdd(pRet->netID);
        int dir = CommPlayerGetDir(pRet->netID);
        _insertBaseNetID(x, z, dir, pRet->netID);        // �쐬
        _insertBaseNetID(x, z, dir, _SECRETBASE_MY_ID);  // �쐬

        if(pRet->result == _SB_CREATED_CHANGE){ // ����������   // MAPCHANGE     // �ʐM�ؒf
            SecretBaseRecordSetRelocateNum(pRec);  // ���z�������񐔃J�E���g
            OHNO_PRINT("���z�������񐔃J�E���g  %d\n",SecretBaseRecordGetRelocateNum(pRec));
        }
        if((pRet->result == _SB_CREATED_CHANGE) || (pRet->result == _SB_CREATED_NEW)){ // ����������   // MAPCHANGE     // �ʐM�ؒf
            void* pBuf = FNOTE_ActionUGBaseDataMake(HEAPID_WORLD);
            FNOTE_DataSave(_pCommSecretBaseWork->pFSys->fnote, pBuf, FNOTE_TYPE_ACTION);
            RECORD_Score_Add(SaveData_GetRecord(_pCommSecretBaseWork->pFSys->savedata), SCORE_ID_MAKE_BASE);
            OHNO_PRINT("�����+���z�������񐔃J�E���g\n");
        }
    }
}


//==============================================================================
/**
 * @brief   �閧��n�ɍs�����󋵃��b�Z�[�W��Ԃ�
 * @param   message   ���b�Z�[�W
 * @retval  ���b�Z�[�W������ꍇTRUE
 */
//==============================================================================

BOOL CommSecretBaseInfoGetActionMessage(STRBUF* pStrBuf)
{
    int i,target;
    MYSTATUS* pMy;
    MYSTATUS* pTarget;

    if(!_pCommSecretBaseWork){
        return FALSE;
    }
    for(i = 0; i< COMM_MACHINE_MAX; i++){
        if(_pCommSecretBaseWork->travelingBaseMessage[i] != _INVALID_BASE){
            target = _pCommSecretBaseWork->travelingBaseMessage[i];
            _pCommSecretBaseWork->travelingBaseMessage[i] = _INVALID_BASE;
            if(i != target ){
                pMy = CommInfoGetMyStatus(i);
                pTarget = CommInfoGetMyStatus(target);
                if(UgMgrRadarLogDouble(pMy,pTarget,UGSecretBaseIn01,pStrBuf)){
                    return TRUE;
                }
            }
        }
        if(_pCommSecretBaseWork->flagGetLog[i] != INVALID_NETID){
            pMy = CommInfoGetMyStatus(i);
            pTarget = CommInfoGetMyStatus(_pCommSecretBaseWork->flagGetLog[i]);
            _pCommSecretBaseWork->flagGetLog[i] = INVALID_NETID;
            if(UgMgrRadarLogDouble(pMy,pTarget,UGGetflag01,pStrBuf)){
                return TRUE;
            }
        }
        if(_pCommSecretBaseWork->flagReverseLog[i] != INVALID_NETID){
            pMy = CommInfoGetMyStatus(i);
            _pCommSecretBaseWork->flagReverseLog[i] = INVALID_NETID;
            if(UgMgrRadarLogSingle(pMy, 0, UGGetflag02, pStrBuf)){
                return TRUE;
            }
            break;
        }
        if(_pCommSecretBaseWork->flagConqureLog[i] != INVALID_NETID){
            pMy = CommInfoGetMyStatus(i);
            pTarget = CommInfoGetMyStatus(_pCommSecretBaseWork->flagConqureLog[i]);
            _pCommSecretBaseWork->flagConqureLog[i] = INVALID_NETID;
            if(UgMgrRadarLogDouble(pMy, pTarget, UGGetflag03, pStrBuf)){
                return TRUE;
            }
        }
    }
    return FALSE;
}

//==============================================================================
/**
 * @brief   ������Z�b�g�A�b�v����閧��n�O�b�Y�f�[�^��Ԃ�
 * @param   sv  SAVEDATA*
 * @retval  SECRETBASEDATA*
 */
//==============================================================================

SECRETBASEDATA* UgSetupSecretBaseData(SAVEDATA * sv)
{
    if(_pCommSecretBaseWork){
        if(_pCommSecretBaseWork->pNowMoveingBase){
            return (SECRETBASEDATA*)_pCommSecretBaseWork->pNowMoveingBase->secretBaseDataBuff;
        }
        //        return SaveData_GetSecretBaseData(sv);
    }
    return NULL;
}

//==============================================================================
/**
 * @brief   ������Z�b�g�A�b�v����閧��n��X�u���b�N��Ԃ�
 * @param   none
 * @retval  X�O���b�h
 */
//==============================================================================

int UgSetupSecretBaseBlockX(void)
{
    if(_pCommSecretBaseWork){
        if(_pCommSecretBaseWork->pNowMoveingBase){
            return _blockToRoomX[_pCommSecretBaseWork->pNowMoveingBase->netID];
        }
    }
    return 0;
}

//==============================================================================
/**
 * @brief   ������Z�b�g�A�b�v����閧��n��Z�u���b�N��Ԃ�
 * @param   none
 * @retval  Z�O���b�h
 */
//==============================================================================

int UgSetupSecretBaseBlockZ(void)
{
    if(_pCommSecretBaseWork){
        if(_pCommSecretBaseWork->pNowMoveingBase){
            return _blockToRoomZ[_pCommSecretBaseWork->pNowMoveingBase->netID];
        }
    }
    return 0;
}

//==============================================================================
/**
 * @brief   �閧��n�O�b�Y�ɓ������Ă��Ȃ����ǂ�������
 * @param   x,z �ʒu
 * @retval  ������ꍇTRUE
 */
//==============================================================================

BOOL UgSecretBaseMoveing(int x, int z)
{
    int blockX,blockZ,i;

    if(!_pCommSecretBaseWork){
        return TRUE;
    }
    if(z >= (_SECRETBASE_ATTR_MAX*2)){
        return TRUE;
    }
    blockX = x / _SECRETBASE_ATTR_MAX;
    blockZ = z / _SECRETBASE_ATTR_MAX;

    for(i = 0; i < _SECRETBASE_NUM_MAX;i++){
        if((blockX == _blockToRoomX[i]) &&
           (blockZ == _blockToRoomZ[i])){
            blockX = x % _SECRETBASE_ATTR_MAX;
            blockZ = z % _SECRETBASE_ATTR_MAX;
            if(_pCommSecretBaseWork->aAttr[i][blockZ] & (0x1 << blockX)){
                return TRUE;
            }
            else{
                return FALSE;
            }
        }
    }
    return TRUE;
}

//==============================================================================
/**
 * @brief   �V�K�ɕ��������ꍇ�₾�炯�ɂ���
 * @param   none
 * @retval  none
 */
//==============================================================================

static void _createSecretBase(void)
{
    SECRETBASEDATA* pSBData = SaveData_GetSecretBaseData(GameSystem_GetSaveData(_pCommSecretBaseWork->pFSys));
    UNDERGROUNDDATA* pUGData = SaveData_GetUnderGroundData(GameSystem_GetSaveData(_pCommSecretBaseWork->pFSys));
    int px = CommPlayerGetPosSXDirAdd(COMM_PARENT_ID);
    int pz = CommPlayerGetPosSZDirAdd(COMM_PARENT_ID);
    int dir = CommPlayerGetSDir(COMM_PARENT_ID);
    int i, ansX, ansZ, bOk, chk;
    const int x1 = 10,x2 = 18,z = 12, xMod = 5, zMod=6;
    MATHRandContext32 sRand;
    int add[SECRETBASE_LOCK_NUM_MAX+1][2];

    add[0][0] = 16; // �p�\�R���Ƃ��Ԃ�ʒu
    add[0][1] = 12;

    SysFlag_UgBaseSet(SaveData_GetEventWork(_pCommSecretBaseWork->pFSys->savedata));

    SecretBaseData_Reform(pSBData);  // �z�u���Ă��Ȃ���Ԃɂ���

    UnderGroundTrashAllGoodsPCItem(pUGData);

    CommRandSeedInitialize(&sRand);
    for(i = 0; i < SECRETBASE_LOCK_NUM_MAX; i++){
        ansX = MATH_Rand32(&sRand, xMod);
        if(ansX < 2){
            ansX = ansX * 2 + x1;
        }
        else{
            ansX = (ansX-3) * 2 + x2;
        }
        ansZ = MATH_Rand32(&sRand, zMod) * 2 + z;
        OHNO_PRINT("�������� %d %d\n",ansX,ansZ);
        bOk=TRUE;
        for(chk = 0; chk <= i; chk++){
            if((add[chk][0] == ansX) && (add[chk][1] == ansZ)){
                bOk = FALSE;
                break;
            }
        }
        if(!bOk){
            i--;
            continue;
        }
        SecretBaseData_ChangeGoodsPosition(pSBData,
                                           SECRETBASE_GOODS_NUM_MAX + SECRETBASE_PC_NUM_MAX+i,
                                           ansX, ansZ);
        add[i+1][0] = ansX;
        add[i+1][1] = ansZ;
    }

    MI_CpuFill8(_pCommSecretBaseWork->aAttr, 0xff,  _SECRETBASE_NUM_MAX * _SECRETBASE_ATTR_MAX * (_SECRETBASE_ATTR_MAX/8) );
    SecretBaseSetSecretBasePosition(pSBData,px,pz,CommPlayerGetReverseDir(dir));
    MI_CpuCopy8(pSBData,_pCommSecretBaseWork->secretBaseData[_SECRETBASE_MY_ID].secretBaseDataBuff,_SECLET_BASE_DATA_SIZE);
    // ����������
    _makeAttr(pSBData,_pCommSecretBaseWork->aAttr[_SECRETBASE_MY_ID]);
}

//--------------------------------------------------------------
/**
 * @brief   ���悤�������b�Z�[�W�J�n
 * @param   messageNo   gmm���x��
 * @retval  ���b�Z�[�W�C���f�b�N�X
 */
//--------------------------------------------------------------

int UgSecretBaseTalkStart(int messageNo)
{
    return CommMsgTalkWindowStart(CommUnderGetMsgUnderEdit(),messageNo,FALSE,NULL);

}

//--------------------------------------------------------------
/**
 * @brief   ���悤�����̉�b�I��
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

void UgSecretBaseTalkEnd(void)
{
    CommMsgTalkWindowEnd(CommUnderGetMsgUnderEdit());
}

//--------------------------------------------------------------
/**
 * @brief   �O�b�Y�̖��O�����b�Z�[�W�ɕ\��������ꍇ�̊֐�
 * @param   type     �O�b�Y�^�C�v = gmm�ԍ�
 * @retval  none
 */
//--------------------------------------------------------------

void UgSecretBaseTalkRegisterGoodsName(int type)
{
    CommMsgRegisterUGGoodsNameIndex(CommUnderGetMsgUnderEdit(),0,type);
}

//--------------------------------------------------------------
/**
 * @brief   �Q���̐��������b�Z�[�W�ɕ\��������ꍇ�̊֐�
 * @param   number     ����
 * @param   index      �����b�Z�[�W�ɏ����Ă���ԍ�
 * @retval  none
 */
//--------------------------------------------------------------

void UgSecretBaseTalkRegisterNum2(int number,int index)
{
    CommMsgRegisterNumber2Index(CommUnderGetMsgUnderEdit(),index,number);
}



//==============================================================================
/**
 * ���̂����肪���̃O�b�Y���Ԃ�
 * @param   ���[�N�|�C���^
 * @retval  none
 */
//==============================================================================

static int _getAttrGoodsType(SECRETBASEDATA* pSecret,int xa,int za)
{
    int i,x,z;
    const u8* pBuff;

    for(i = 0; i < SECRETBASE_SETUPOBJ_NUM_MAX; i++){
        int type = SecretBaseData_GetGoodsType(pSecret, i);
        if(type == GOODS_INVALID){
            continue;
        }
        if(i == 0){
            continue;  // ����Ȃ�
        }
        else if(i < (SECRETBASE_GOODS_NUM_MAX + SECRETBASE_PC_NUM_MAX)){
            pBuff = GOODS_GetGoodsHitData(type);
        }
        else{
            continue;  // ����Ȃ�
        }
        x = SecretBaseData_GetGoodsXPos(pSecret,i);
        z = SecretBaseData_GetGoodsZPos(pSecret,i);
        x = xa - x;
        z = za - z;
        if((x < 0) || (x > 2)){
            continue;
        }
        if((z < 0) || (z > 2)){
            continue;
        }
        if(pBuff[z*3+x]){
            return type;
        }
    }
    return GOODS_INVALID;
}

//--------------------------------------------------------------
/**
 * @brief   �O�b�Y���ڂ̑O�ɂ��邩�ǂ�������
 * @param   type     �O�b�Y�^�C�v = gmm�ԍ�
 * @retval  none
 */
//--------------------------------------------------------------

BOOL UgSecretBaseGoodsCheck(int netID, Grid* pTouch)
{
    int x = pTouch->xpos;
    int z = pTouch->zpos;
    int roomID, type , msg;
    SECRETBASEDATA* pSecret;

    if(UgSecretBaseMoveing(x,z) == FALSE){
        u8 ret[2];
        ret[0] = netID;

        roomID = _getSecretIndex(x,z);
        pSecret = (SECRETBASEDATA*)_pCommSecretBaseWork->secretBaseData[roomID].secretBaseDataBuff;

        type = _getAttrGoodsType(pSecret,x % _SECRETBASE_ATTR_MAX,z % _SECRETBASE_ATTR_MAX);
        ret[1] = GOODS_GetMessageNo(type);
        if(ret[1]!=0){
            CommPlayerSetMoveControl_Server(netID,FALSE);
            CommSendFixSizeData_ServerSide(CF_SECRETBASE_GOODS_CHECK,&ret);
            return TRUE;
        }
    }
    return FALSE;


}

//--------------------------------------------------------------
/**
 * @brief   �O�b�Y���ڂ̑O�ɂ������̂ŒʐM�������Ă��� CF_SECRETBASE_GOODS_CHECK
 * @param   �R�[���o�b�N����
 * @retval  none
 */
//--------------------------------------------------------------

void UgSecretBaseRecvGoodsCheck(int netID, int size, void* pData, void* pWork)
{
    u8* pBuff = pData;
    SECRETBASEDATA* pSecret = (SECRETBASEDATA*)_pCommSecretBaseWork->pNowMoveingBase->secretBaseDataBuff;
    SB_RECORD_DATA* pRec = SecretBaseGetSecretBaseRecord(pSecret);

    if(pBuff[0] == CommGetCurrentID()){
    //    int msg = GOODS_GetMessageNo(pBuff[1]);
        UgRecordGoodsMessage(pRec, pBuff[1]);
    }
}

//--------------------------------------------------------------
/**
 * @brief   �T�C�Y��Ԃ�
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

int UgSecretBaseGetRecvGoodsCheckSize(void)
{
    return 2;
}


//--------------------------------------------------------------
/**
 * @brief   �����Ƃ���LOG���Ȃ���
 * @param   �R�[���o�b�N����
 * @retval  none
 */
//--------------------------------------------------------------

void UgSecretBaseSetFlagGetLog(int netID, int targetPCNetID)
{
    if(_pCommSecretBaseWork){
        _pCommSecretBaseWork->flagGetLog[netID] = targetPCNetID;
    }
}

//
//--------------------------------------------------------------
/**
 * @brief   ���΂���LOG
 * @param   �R�[���o�b�N����
 * @retval  none
 */
//--------------------------------------------------------------
void UgSecretBaseSetFlagConquerLog(int myNetID, int targetID)
{
    if(_pCommSecretBaseWork){
        _pCommSecretBaseWork->flagConqureLog[myNetID] = targetID;
    }
}

//
//--------------------------------------------------------------
/**
 * @brief   �Ƃ���ǂ���LOG
 * @param   �R�[���o�b�N����
 * @retval  none
 */
//--------------------------------------------------------------
void UgSecretBaseSetFlagReverseLog(int myNetID)
{
    if(_pCommSecretBaseWork){
        _pCommSecretBaseWork->flagReverseLog[myNetID] = TRUE;
    }
}


typedef struct{
    int seq;
    u8 msgIndex;      ///< ���b�Z�[�W�C���f�b�N�X ���b�Z�[�W�I���҂��Ɏg�p
    u8 type; //LVUPTYPE
} _DELIVERY_PLAYER;

//--------------------------------------------------------------
/**
 * @brief   �p�\�R���ύX
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

static void _pcChange(_DELIVERY_PLAYER* pDeliv)
{
    VecFx32 vtx;
    M3DO_PTR pM3DO = M3DO_GetMap3DObjData(_pCommSecretBaseWork->pFSys->Map3DObjExp, 0);
    vtx = M3DO_GetGlobalVec(pM3DO);
    M3DO_CleanMap3DObj(0,_pCommSecretBaseWork->pFSys->Map3DObjExp);
    M3DO_SetMap3DObjExp(_pCommSecretBaseWork->pFSys->Map3DObjExp,
                        _pCommSecretBaseWork->pFSys->MapResource,
                        BMID_UG_TABLE_L02+pDeliv->type,
                        &vtx, NULL,
                        _pCommSecretBaseWork->pFSys->field_3d_anime);
}

#if GT384_060815_FIX
//--------------------------------------------------------------
/**
 * @brief   �p�\�R���ς��鏈���̋����I��
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

static void _deliveryForceEnd(TCB_PTR tcb, void* work)
{
    sys_FreeMemoryEz(work);
    TCB_Delete(tcb);
}
#endif //GT384_060815_FIX

//--------------------------------------------------------------
/**
 * @brief   �����N���オ�����̂Ńp�\�R����ς���
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

static void _deliveryPlayer(TCB_PTR tcb, void* work)
{
    _DELIVERY_PLAYER* pDeliv = work;

    enum{
        _DELIV_INIT,
        _DELIV_MSGWAIT1,
        _DELIV_MSGWAIT2,
        _DELIV_FADEOUT,
        _DELIV_END,
    };

    switch(pDeliv->seq){
      case _DELIV_INIT:
        CommPlayerHold();
        CommMsgTalkWindowStart(CommUnderGetMsgUnderFlag(),
                               mes_uw_flag_12, FALSE, NULL);
        Snd_SePlay(UG_SE_LEVELUP_FLAG);
        pDeliv->seq = _DELIV_MSGWAIT1;
        break;
      case _DELIV_MSGWAIT1:
//        if(Snd_MePlayCheckBgmPlay() == 0){
            if( CommMsgIsOutputing(CommUnderGetMsgUnderFlag()) == 0 ){
                if(sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL)){
                    int type = pDeliv->type;
                    CommMsgTalkWindowStart(CommUnderGetMsgUnderFlag(),
                                           mes_uw_flagLV_01+type, FALSE, NULL);
                    pDeliv->seq = _DELIV_MSGWAIT2;
                }
            }
//        }
        break;
      case _DELIV_MSGWAIT2:
        if( CommMsgIsOutputing(CommUnderGetMsgUnderFlag()) == 0 ){
            if(sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL)){
                _pcChange(pDeliv);
                pDeliv->seq = _DELIV_END;
                CommMsgTalkWindowEnd(CommUnderGetMsgUnderFlag());
                CommPlayerHoldEnd();
            }
        }
        break;
      case _DELIV_FADEOUT:
        WIPE_SYS_Start(WIPE_PATTERN_FSAM,
                       WIPE_TYPE_FADEOUT,
                       WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK,COMM_BRIGHTNESS_SYNC,
                       1,HEAPID_FIELD);
        break;
      case _DELIV_END:
        sys_FreeMemoryEz(work);
        TCB_Delete(tcb);
#if GT384_060815_FIX
        UgMgrEndNowTCB();
#endif //GT384_060815_FIX
        break;
    }
}

//--------------------------------------------------------------
/**
 * @brief   �p�\�R��LVUP  CF_LVUP_FLAG
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

void UgSBRecvLVUPFlag(int netID, int size, void* pData, void* pWork)
{
    u8 sBuff[2];
    u8* pRet = pData;

    sBuff[0] = netID;
    sBuff[1] = pRet[0];  //LV
    CommSendFixSizeData_ServerSide(CF_LVUP_FLAG_RET,sBuff);
}



//--------------------------------------------------------------
/**
 * @brief   �p�\�R��LVUP  CF_LVUP_FLAG_RET
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

void UgSBRecvLVUPFlagRet(int netID, int size, void* pData, void* pWork)
{
    int i;
    u8* pBuff = pData;
#if GT384_060815_FIX
    TCB_PTR pTCB;
#endif //GT384_060815_FIX

    if(pBuff[0] == CommGetCurrentID()){
        _DELIVERY_PLAYER* pDeliv = sys_AllocMemory(HEAPID_WORLD, sizeof(_DELIVERY_PLAYER));
        MI_CpuClear8(pDeliv,sizeof(pDeliv));
        pDeliv->seq = 0;
        pDeliv->type = pBuff[1];
#if GT384_060815_FIX
        pTCB = TCB_Add(_deliveryPlayer, pDeliv, TCB_PRIORITY_NORMAL);
        UgMgrSetNowTCB(pDeliv, pTCB, _deliveryForceEnd);
#else  //GT384_060815_FIX
        TCB_Add(_deliveryPlayer, pDeliv, TCB_PRIORITY_NORMAL);
#endif //GT384_060815_FIX
    }
    else{
#if GT384_060815_FIX 
#else  //GT384_060815_FIX
        int x = CommPlayerGetPosX(CommGetCurrentID());
        int z = CommPlayerGetPosZ(CommGetCurrentID());
        if(_getSecretIndex(x,z) == pBuff[0]){ // �������ύX�̂������閧��n�ɂ���
            _DELIVERY_PLAYER* pDeliv = sys_AllocMemory(HEAPID_WORLD, sizeof(_DELIVERY_PLAYER));
            MI_CpuClear8(pDeliv,sizeof(pDeliv));
            pDeliv->seq = 0;
            pDeliv->type = pBuff[1];
            OHNO_SP_PRINT("�ꏏ�ɂ����̂Ńp�\�R���X�V \n");
            _pcChange(pDeliv);
            sys_FreeMemoryEz(pDeliv);
        }
#endif  //GT384_060815_FIX
    }
}

//--------------------------------------------------------------
/**
 * @brief   �p�\�R��LVUP  �R�}���h�̃T�C�Y
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

int UgSBGetLVUPFlagRetSize(void)
{
    return 2;
}

//==============================================================================
/**
 * ���̑��������̃O�b�Y���Ԃ�
 * @param   ���[�N�|�C���^
 * @retval  none
 */
//==============================================================================

static int _getFootGoodsType(SECRETBASEDATA* pSecret,int xa,int za)
{
    int i,x,z;
    const u8* pBuff;

    for(i = 0; i < SECRETBASE_SETUPOBJ_NUM_MAX; i++){
        int type = SecretBaseData_GetGoodsType(pSecret, i);
        if(type == GOODS_INVALID){
            continue;
        }
        if(i == 0){
            continue;  // ����Ȃ�
        }
        else if(i < (SECRETBASE_GOODS_NUM_MAX + SECRETBASE_PC_NUM_MAX)){
            pBuff = GOODS_GetGoodsHitData(type);
        }
        else{
            continue;  // ����Ȃ�
        }
        x = SecretBaseData_GetGoodsXPos(pSecret,i);
        z = SecretBaseData_GetGoodsZPos(pSecret,i);
        x = xa - x;
        z = za - z;
        if((x == 0) && (z == 0)){
            return type;
        }
    }
    return GOODS_INVALID;
}

static int _trap2trap(int goodsTrap)
{
    switch(goodsTrap){
      case GOODS_UG_TRAP_03://	(62) // ���Ȃ�����
        return UG_TRAPTYPE_HOLE;
      case GOODS_UG_TRAP_04://	(63) // �������Ȃ�����
        return UG_TRAPTYPE_BIG_HOLE;
      case GOODS_UG_TRAP_10://	(66) // ���ނ肻����
        return UG_TRAPTYPE_SMOG;
      case GOODS_UG_TRAP_11://	(67) // ����܂�������
        return UG_TRAPTYPE_BIG_SMOG;
      case GOODS_UG_TRAP_12://	(68) // ���킻����
        return UG_TRAPTYPE_ROCK;
      case GOODS_UG_TRAP_13://	(69) // �炭����������
        return UG_TRAPTYPE_ROCKFALL;
      case GOODS_UG_TRAP_14://	(70) // ���킻����
        return UG_TRAPTYPE_SUDS;
      case GOODS_UG_TRAP_15://	(71) // �o�u��������
        return UG_TRAPTYPE_BUBBLE;
      case GOODS_UG_TRAP_16://	(72) // �������g���b�v�P
        return UG_TRAPTYPE_ALART1;
      case GOODS_UG_TRAP_17://	(73) // �������g���b�v�Q
        return UG_TRAPTYPE_ALART2;
      case GOODS_UG_TRAP_18://	(74) // �������g���b�v�R
        return UG_TRAPTYPE_ALART3;
      case GOODS_UG_TRAP_19://	(75) // �������g���b�v�S
        return UG_TRAPTYPE_ALART4;
      case GOODS_UG_TRAP_20://	(76) // ���̂͂�����
        return UG_TRAPTYPE_LEAF;
      case GOODS_UG_TRAP_21://	(77) // �͂Ȃт炻����
        return UG_TRAPTYPE_DIRTY_BLOSSOMS;
      case GOODS_UG_TRAP_22://	(78) // �Ђ̂�������
        return UG_TRAPTYPE_FIRE;
      case GOODS_UG_TRAP_23://	(79) // �ق̂�������
        return UG_TRAPTYPE_BLAZE;
    }
    return UG_TRAPTYPE_NONE;
}


//--------------------------------------------------------------
/**
 * @brief   �g���b�v�O�b�Y�𓥂񂾂��ǂ���
 * @param   netID  ���񂾐l
 * @param   pTouch �ʒu
 * @retval  ����ł���TRUE
 */
//--------------------------------------------------------------

BOOL UgSecretBaseTrapGoodsCheck(int netID)
{
    int trapType;
    int roomID;
    SECRETBASEDATA* pSecret;
    int x = CommPlayerGetPosSX(netID);
    int z = CommPlayerGetPosSZ(netID);
    int dir = CommPlayerGetSDir(netID);

    if(!UgSecretBaseIsSecretBasePlace(x,z)){
        return FALSE;
    }
    if((UgSecretBaseMoveing(x,z) == TRUE)
       && (!_pCommSecretBaseWork->bGoodsTrap[netID])){
        u8 ret[2];
        ret[0] = netID;

        roomID = _getSecretIndex(x,z);
        pSecret = (SECRETBASEDATA*)_pCommSecretBaseWork->secretBaseData[roomID].secretBaseDataBuff;

        ret[1] = _getFootGoodsType(pSecret,x % _SECRETBASE_ATTR_MAX,z % _SECRETBASE_ATTR_MAX);
        trapType = _trap2trap( ret[1] );
        if(UG_TRAPTYPE_NONE != trapType){
            _pCommSecretBaseWork->bGoodsTrap[netID] = TRUE;
            UgTrapGoodsBind(netID, INVALID_NETID, trapType, x, z, dir);
            OHNO_SP_PRINT("���u�ɂ�����%d x,z \n",netID,x,z);
            return TRUE;
        }
    }
    return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   �g���b�v�O�b�Y�𓥂݂������
 * @param   netID  ���񂾐l
 * @retval  ����ł���TRUE
 */
//--------------------------------------------------------------

BOOL UgSecretBaseTrapGoodsReset(int netID)
{
    BOOL bit = 0;

    if(_pCommSecretBaseWork){
        BOOL bit = _pCommSecretBaseWork->bGoodsTrap[netID];
        _pCommSecretBaseWork->bGoodsTrap[netID] = FALSE;
    }
    return bit;
}

//--------------------------------------------------------------
/**
 * @brief   �閧��n�ɂ���l��ǂ��o���i�e�@������ꍇ�j��ɌĂяo�����
 * @param   netID    ���̐l�̔閧��n�ɂ���ꍇ�ǂ��o��
 * @retval  none
 */
//--------------------------------------------------------------

void UgSecretBaseRemovePlayer(int netID)
{
    int i,no=0;
    int x,z;
    u8 buff[COMM_MACHINE_MAX];

    MI_CpuClear8(buff,COMM_MACHINE_MAX);
    

/*    for(i = 0 ; i < COMM_MACHINE_MAX ; i++){
        if((_pCommSecretBaseWork->travelBase[i] == netID)){
            if((_pCommSecretBaseWork->travelingBase[i] == _INVALID_BASE) &&
               (_pCommSecretBaseWork->travelingBaseSend[i] == _INVALID_BASE)){  // �閧��n�ړ������Ă��Ȃ�
                OHNO_PRINT("%d �� %d ���炨������---1\n",i, _pCommSecretBaseWork->travelBase[i]);
                if(!buff[i]){
                    _returnUnderGroundStart(_pCommSecretBaseWork->travelBase[i],i, TRUE);
                    buff[i]=TRUE;
                }
            }
        }
    } */
    for(i = 0 ; i < COMM_MACHINE_MAX ; i++){
        if(CommIsConnect(i)){
            x = CommPlayerGetPosSX(i);
            z = CommPlayerGetPosSZ(i);
            if((x==COMM_PLAYER_INVALID_GRID) && (z==COMM_PLAYER_INVALID_GRID)){
                continue;
            }
            no = _getSecretIndex(x,z);
            if((i == no) || (no == _SECRETBASE_MY_ID)){
                continue;
            }
            if(CommIsConnect(no)){
                continue;
            }
            if((_pCommSecretBaseWork->travelingBase[i] == _INVALID_BASE) &&
               (_pCommSecretBaseWork->travelingBaseSend[i] == _INVALID_BASE)){  // �閧��n�ړ������Ă��Ȃ�
                if(UgSecretBaseIsSecretBasePlace(x,z)){
                    OHNO_PRINT("%d �� %d ���炨������\n",i, no);
                    if(!buff[i]){
                        _returnUnderGroundStart(no, i, TRUE);
                        buff[i]=TRUE;
                    }
                }
            }
        }
    }
    i = CommGetCurrentID();
    if(_pCommSecretBaseWork->moveTickets == _RETURN_TICKETS){
        x = CommPlayerGetPosSX(i);
        z = CommPlayerGetPosSZ(i);
        if((x==COMM_PLAYER_INVALID_GRID) && (z==COMM_PLAYER_INVALID_GRID)){
        }
        else if(UgSecretBaseIsSecretBasePlace(x,z)){
            no = _getSecretIndex(x,z);
            OHNO_PRINT("%d �� %d ����escape\n",i, no);
            if(!buff[i]){
                _returnUnderGroundStart(no, i, TRUE);
                buff[i]=TRUE;
            }
        }
        if(buff[i]){  // �A�邱�Ƃ����܂��Ă����ꍇ�j��
            _pCommSecretBaseWork->moveTickets = _NONE_TICKETS;//
        }
    }
}

//--------------------------------------------------------------
/**
 * @brief   �閧��n�ɂ���l��ǂ��o���i�e�@���������ꍇ�j
 * @param   netID    ���̐l�̔閧��n
 * @retval  none
 */
//--------------------------------------------------------------

BOOL UgSecretBaseRemovePlayer_Client(int playerID, BOOL bRemove)
{
    _SendPos sendPos;
    _Pos outDoorPos;
    int x,z,dir,escapePlace;
    _Pos* pHead;


    if(_pCommSecretBaseWork->travelBase[playerID] == _INVALID_BASE){
        return FALSE;
    }
    escapePlace = _pCommSecretBaseWork->travelBase[playerID];
    x = CommPlayerGetPosX(CommGetCurrentID());
    z = CommPlayerGetPosZ(CommGetCurrentID());
    if(!UgSecretBaseIsSecretBasePlace(x,z)){
        _pCommSecretBaseWork->travelBase[playerID] = _INVALID_BASE; // �����ŏ���
        OHNO_PRINT("�閧��n�O");
        return FALSE;
    }
    UnderRecordReset();
    TalkAskForceReset();
    UgMgrForceExitNowTCB();
    UgTrapForceExit(CommGetCurrentID(),FALSE);

//    pHead = &_pCommSecretBaseWork->secretHeaderData[escapePlace];
//    x = pHead->xpos;
//    z = pHead->zpos;
//    dir = pHead->dir;

    x = _pCommSecretBaseWork->resquePosX;
    z = _pCommSecretBaseWork->resquePosZ;
    dir = _pCommSecretBaseWork->resqueDir;

    OHNO_PRINT("�ؒf�Ȃ̂�  %d %d %d �ɂ��ǂ�܂�\n", playerID,escapePlace , x, z , dir);
    GF_ASSERT((x != 0) && (z != 0));
    x += FieldOBJ_DirAddValueGX( dir);
    z += FieldOBJ_DirAddValueGZ( dir);

    _pCommSecretBaseWork->bClientBaseIn = FALSE;
    _jumpMapForUG(_pCommSecretBaseWork->pFSys, x, z, dir, playerID, bRemove);
    CommStateJumpUnderGround();
    _pCommSecretBaseWork->pNowMoveingBase = NULL;
    _pCommSecretBaseWork->travelBase[playerID] = _INVALID_BASE;
    return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   �閧��n�ɓ����Ă��邩�ǂ�����Ԃ�
 * @param   netID    ���̐l�̔閧��n
 * @retval  
 */
//--------------------------------------------------------------

BOOL UgSecretBaseIsOtherEnter(void)
{
    int id = _pCommSecretBaseWork->travelBase[COMM_PARENT_ID];
    switch(id){
      case _INVALID_BASE:
      case _SECRETBASE_MY_ID:
      case COMM_PARENT_ID:
        return FALSE;
    }
    return TRUE;
}


//--------------------------------------------------------------
/**
 * @brief   �閧��n�f�[�^��M���̃G���[�Ώ�
 * @param   netID    ���̐l�̔閧��n
 * @retval  
 */
//--------------------------------------------------------------

void UgSecretBaseErrorMoveTickets(void)
{
    if(_pCommSecretBaseWork->moveTickets == _MOVE_TICKETS){
        _pCommSecretBaseWork->moveTickets = _ERROR_TICKETS;
        CommPlayerMyDataInitialize();
        UgSecretBaseResetPlayer(COMM_PARENT_ID);
        OHNO_PRINT("�G���[�`�P�b�g�Ȃ̂Ń��Z�b�g\n");
    }
}

//--------------------------------------------------------------
/**
 * @brief   �閧��n�ړ����̃G���[
 * @param   netID    ���̐l�̔閧��n
 * @retval  
 */
//--------------------------------------------------------------

void UgSecretBaseErrorDisconnectTickets(void)
{
    if(_pCommSecretBaseWork->moveTickets == _TRANS_TICKETS){
        _pCommSecretBaseWork->moveTickets = _DISCONECT_TICKETS;
        OHNO_PRINT("�G���[�Ȃ̂Ń��Z�b�g\n");
    }
}

//--------------------------------------------------------------
/**
 * @brief   �q�@�ɂȂ����l���閧��n�ɂ����ꍇ�A��������O�ɏo�Ă��炤
 * @param   void
 * @retval  void
 */
//--------------------------------------------------------------

void UgSecretBaseFirstConnectChild(int netID)
{
    int x,z,no,id = netID;
    _UgJumpEventResult ugJump;

    x = CommPlayerGetPosSXOrg(id);
    z = CommPlayerGetPosSZOrg(id);

    if(!GetHitAttr(_pCommSecretBaseWork->pFSys, x, z)){   // �ςȈʒu�ɂ���Ƌ����ދ�
        if(netID == COMM_PARENT_ID){
            return;
        }
        if(CommMPIsConnectStalth()){
            return;
        }
    }
    OHNO_PRINT("�q�@�@%d �̈ʒu  %d %d\n",id, x, z); //
    if((x==COMM_PLAYER_INVALID_GRID) && (z==COMM_PLAYER_INVALID_GRID)){
#ifdef DEBUG_ONLY_FOR_ohno
//        GF_ASSERT(0);
#endif
        _returnUnderGroundStart(id, id, TRUE);
    }
    else if(UgSecretBaseIsSecretBasePlace(x, z) || GetHitAttr(_pCommSecretBaseWork->pFSys, x, z)){
        _returnUnderGroundStart(id, id, TRUE);
        OHNO_PRINT("%d �� %d ���� �������񂻂Ƃɂ���\n",id, id);
    }
}



int UgSecretBaseEscapePosX(void)
{
    if(_pCommSecretBaseWork){
        return _pCommSecretBaseWork->resquePosX;
    }
    return _RESQUE_POSX;
}

int UgSecretBaseEscapePosZ(void)
{
    if(_pCommSecretBaseWork){
        return _pCommSecretBaseWork->resquePosZ;
    }
    return _RESQUE_POSZ;
}

int UgSecretBaseEscapeDir(void)
{
    if(_pCommSecretBaseWork){
        return _pCommSecretBaseWork->resqueDir;
    }
    return DIR_DOWN;
}

void UgSecretBaseEscapePosSXSet(int netID,int x)
{
    if(_pCommSecretBaseWork){
        _pCommSecretBaseWork->resquePosSX[netID] = x;  // ���鎞�ɏo�鎞�̈ʒu���L��
    }
}

void UgSecretBaseEscapePosSZSet(int netID,int z)
{
    if(_pCommSecretBaseWork){
        _pCommSecretBaseWork->resquePosSZ[netID] = z;  // ���鎞�ɏo�鎞�̈ʒu���L��
    }
}

void UgSecretBaseEscapeDirSet(int netID,int dir)
{
    if(_pCommSecretBaseWork){
        _pCommSecretBaseWork->resqueSDir[netID] = dir;  // ���鎞�ɏo�鎞�̈ʒu���L��
    }
}

void UgSecretBaseBootOn(BOOL bOn)
{
    OHNO_PRINT("�h�A����\n");
    _pCommSecretBaseWork->bDoorON = bOn;
}

//--------------------------------------------------------------
/**
 * @brief   �ڑ��֎~
 * @param   void
 * @retval  void
 */
//--------------------------------------------------------------

static void _connectDisable(void)
{
    WHChildConnectPause(TRUE);
    WHParentConnectPause(TRUE);
    CommStaetUnderPause(TRUE);
    CommMPFlashMyBss();
}


static void _connectEnable(void)
{
    WHChildConnectPause(FALSE);
    WHParentConnectPause(FALSE);
    CommStaetUnderPause(FALSE);
    CommMPFlashMyBss();
}

