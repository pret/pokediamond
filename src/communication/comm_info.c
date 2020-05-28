//=============================================================================
/**
 * @file	comm_info.c
 * @brief	�ʐM�œ����e�J�Z�b�g�̊�{����~���Ă����N���X
 * @author	Katsumi Ohno
 * @date    2005.08.22
 */
//=============================================================================

#include "common.h"
#include "communication/communication.h"
#include "comm_local.h"

#include "system/gamedata.h"
#include "system/pm_str.h"

#include "communication/comm_info.h"
#include "system/savedata.h"
#include "savedata/randomgroup.h"
#include "savedata/undergrounddata.h"
#include "savedata/wifihistory.h"
#include "wifi/dwc_rapfriend.h"

//==============================================================================
// ���[�N
//==============================================================================

enum _info_e {
    _INFO_EMPTY,      // ��
    _INFO_NEW_ENTRY,  // ��M���ĉ����Ή����Ă��Ȃ����[�U�[
    _INFO_ENTRY,      // ��t���� �����o�[�ɂȂ���
    _INFO_ENTRY_MSGSENDED,      // ���b�Z�[�W������I��������
    _INFO_MAX
};


// MYSTATUS�ɂȂ��v�f���������\����
typedef struct{
    u8 myRegulation[COMM_SEND_REGULATION_SIZE]; //
    u8 myStatusBuff[COMM_SEND_MYSTATUS_SIZE];  	// ���ۂ�mystatus�̑傫���͎��s���łȂ��Ƃ킩��Ȃ��̂ŏ�ɐ؂��Ă���
    DWCFriendData friendData;   //�ʐM�œn���p�̃t�����h�R�[�h
    STRCODE groupName[PERSON_NAME_SIZE + EOM_SIZE];     //�����_���O���[�v�� MYUSE��
    u8 mac[WM_SIZE_BSSID];  ///mac
    u8 netID;     /// ID
    u8 my_nation;			///<�����̍�
    u8 my_area;				///<�����̒n��
    u8 myPenalty;
} PlayerInfo;


#define _RESULT_TYPE_WIN  (0)  //������������
#define _RESULT_TYPE_LOSE  (1) // ������
#define _RESULT_TYPE_TRADE  (2) //����

typedef struct{
    u16 win;
    u16 lose;
    u16 trade;
} PlayerResult;

typedef struct{
    const REGULATION* pReg;
    SAVEDATA* pSaveData;
    PlayerInfo sPlayerData[COMM_MACHINE_MAX];  // �ʐM�p info
    MYSTATUS* pMyStatus[COMM_MACHINE_MAX];     // myStatus
    PlayerResult sPlayerResult[COMM_MACHINE_MAX];
    u8 info[COMM_MACHINE_MAX];    /// ���
    u8 _infoEnd;
    u8 bNewInfoData;
    u8 nowNetID;
} _COMM_INFO_WORK;

static _COMM_INFO_WORK* _pCommInfo;

#define _INVALID_POKEID (-1)  /// �����ȃ|�P����ID
#define _ID_STR_LENGTH  (5)  /// ID�̌�����������

//--------------------------------------------------------------
/**
 * @brief   �ʐM���Ǘ��̏�����
 * @param   pWork       �����Ŏg�p���郏�[�N�G���A
 * @retval  none
 */
//--------------------------------------------------------------

void CommInfoInitialize(SAVEDATA* pSaveData, const REGULATION* pReg)
{
    int i;
    MYSTATUS* pMyStatus = SaveData_GetMyStatus(pSaveData);

    if(_pCommInfo){
        return;
    }
    _pCommInfo = sys_AllocMemory(HEAPID_COMMUNICATION, sizeof(_COMM_INFO_WORK));
    MI_CpuClear8(_pCommInfo, sizeof(_COMM_INFO_WORK));
    for(i = 0; i < COMM_MACHINE_MAX ; i++){
        _pCommInfo->pMyStatus[i] = (MYSTATUS*)&_pCommInfo->sPlayerData[i].myStatusBuff[0]; //MyStatus_AllocWork(HEAPID_COMMUNICATION);
        CommInfoDeletePlayer( i );
    }
    _pCommInfo->_infoEnd = FALSE;
    _pCommInfo->bNewInfoData = FALSE;
    _pCommInfo->nowNetID = 0;
    _pCommInfo->pSaveData = pSaveData;
    _pCommInfo->pReg = pReg;

    // ������MYSTATUS���R�s�[
    MyStatus_Copy( pMyStatus, _pCommInfo->pMyStatus[0]);
}

//--------------------------------------------------------------
/**
 * @brief   �ʐM���Ǘ��̊J��
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

void CommInfoFinalize(void)
{
    int i;

    if(_pCommInfo){
        for(i = 0; i < COMM_MACHINE_MAX ; i++){
            //            sys_FreeMemoryEz(_pCommInfo->pMyStatus[i]);
            _pCommInfo->pMyStatus[i] = NULL;
        }
        if(_pCommInfo){
            sys_FreeMemoryEz(_pCommInfo);
        }
        _pCommInfo = NULL;
    }
}

//--------------------------------------------------------------
/**
 * @brief   ������������ł��邩�ǂ�����Ԃ�
 * @param   none
 * @retval  �����������̏ꍇTRUE
 */
//--------------------------------------------------------------

BOOL CommInfoIsInitialize(void)
{
    return (_pCommInfo != NULL);
}



//--------------------------------------------------------------
/**
 * @brief   ������ID,name�Ȃǂ𑗐M���܂�
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------


void CommInfoSendPokeData(void)
{
    u16 netID = CommGetCurrentID();
    MYSTATUS* pMyStatus;
    const STRCODE *pStr;
    RANDOM_GROUP* pRG = SaveData_GetRandomGroup(_pCommInfo->pSaveData);
    WIFI_LIST* pList = SaveData_GetWifiListData(_pCommInfo->pSaveData);
    WIFI_HISTORY* pHistry = SaveData_GetWifiHistory(_pCommInfo->pSaveData);

    pMyStatus = SaveData_GetMyStatus(_pCommInfo->pSaveData);
    MyStatus_Copy( pMyStatus, _pCommInfo->pMyStatus[netID]);
    OS_GetMacAddress(&_pCommInfo->sPlayerData[netID].mac[0]);

    pStr = RandomGroup_GetNamePtr( pRG, RANDOMGROUP_MYUSE, RANDOMGROUP_NAME_GROUP );

    OHNO_PRINT("�R�s�[�T�C�Y  %d \n",sizeof(_pCommInfo->sPlayerData[netID].groupName));
    MI_CpuCopy8(pStr,_pCommInfo->sPlayerData[netID].groupName,
                sizeof(_pCommInfo->sPlayerData[netID].groupName));

    _pCommInfo->sPlayerData[netID].my_nation = WIFIHISTORY_GetMyNation(pHistry);
    _pCommInfo->sPlayerData[netID].my_area = WIFIHISTORY_GetMyArea(pHistry);
    _pCommInfo->sPlayerData[netID].myPenalty = UnderGroundDataIsGoodsSend(_pCommInfo->pSaveData);
    _pCommInfo->sPlayerData[netID].myPenalty = 1 - _pCommInfo->sPlayerData[netID].myPenalty;
    
    DWC_CreateExchangeToken(WifiList_GetMyUserInfo(pList), &_pCommInfo->sPlayerData[netID].friendData);

    MI_CpuClear8(_pCommInfo->sPlayerData[netID].myRegulation, COMM_SEND_REGULATION_SIZE);
    if(_pCommInfo->pReg){
        Regulation_Copy(_pCommInfo->pReg, (REGULATION*)_pCommInfo->sPlayerData[netID].myRegulation);
    }
    CommSendData(CS_COMM_INFO, &_pCommInfo->sPlayerData[netID], sizeof(PlayerInfo));
}

//--------------------------------------------------------------
/**
 * @brief   �v���[���[���̃T�C�Y��Ԃ��܂�
 * @param   netID           �l�b�g���[�NID
 * @param   size            ��M�f�[�^�T�C�Y
 * @param   pData           ��M�f�[�^
 * @retval  none
 */
//--------------------------------------------------------------
int CommInfoGetPlayerDataSize(void)
{
    return sizeof(PlayerInfo);
}

//--------------------------------------------------------------
/**
 * @brief   info�f�[�^�����ׂĂ������Ƃ������R�}���h�̎�M
 * @param   netID           �l�b�g���[�NID
 * @param   size            ��M�f�[�^�T�C�Y
 * @param   pData           ��M�f�[�^
 * @retval  none
 */
//--------------------------------------------------------------

void CommInfoRecvEnd( int netID, int size, void* pData, void* pWork)
{
    if(_pCommInfo){
        _pCommInfo->_infoEnd = TRUE;
    }
    else{
        OHNO_PRINT("comminfo������������Ă��Ȃ�\n");
    }
}


//--------------------------------------------------------------
/**
 * @brief   �T�[�o�[����݂�Ȃ̏�񂪑����Ă������ǂ����m�F
 * @param   none
 * @retval  �����Ă�����TRUE
 */
//--------------------------------------------------------------
BOOL CommInfoIsInfoCollected(void)
{
    return _pCommInfo->_infoEnd;
}

//--------------------------------------------------------------
/**
 * @brief   ��M�R�[���o�b�N���Ăяo���܂�   CS_COMM_INFO_ARRAY
 * @param   netID           �l�b�g���[�NID
 * @param   size            ��M�f�[�^�T�C�Y
 * @param   pData           ��M�f�[�^
 * @retval  none
 */
//--------------------------------------------------------------

void CommInfoRecvArrayPlayerData( int netID, int size, void* pData, void* pWork)
{
    PlayerInfo* pPlayer = (PlayerInfo*)pData;
    if(!_pCommInfo){
        OHNO_PRINT("comminfo������������Ă��Ȃ�\n");
        return;
    }
    MI_CpuCopy8( pData, &_pCommInfo->sPlayerData[pPlayer->netID], sizeof(PlayerInfo));
    _pCommInfo->nowNetID = pPlayer->netID;

    if(_pCommInfo->info[_pCommInfo->nowNetID] < _INFO_ENTRY){
        OHNO_PRINT("CommInfo �V���ȃG���g���[ %d\n", _pCommInfo->nowNetID);
        _pCommInfo->info[_pCommInfo->nowNetID] = _INFO_NEW_ENTRY;  // �V���ȃG���g���[
        if(CommGetCurrentID() == _pCommInfo->nowNetID){  // �������g�͂��łɎ�t������Ԃɂ���
            _pCommInfo->info[_pCommInfo->nowNetID] = _INFO_ENTRY_MSGSENDED;
        }
    }

}

//--------------------------------------------------------------
/**
 * @brief   ��M�R�[���o�b�N���Ăяo���܂� CS_COMM_INFO
 * @param   netID           �l�b�g���[�NID
 * @param   size            ��M�f�[�^�T�C�Y
 * @param   pData           ��M�f�[�^
 * @retval  none
 */
//--------------------------------------------------------------

void CommInfoRecvPlayerData( int netID, int size, void* pData, void* pWork)
{
    int i;

    if(!_pCommInfo){
        OHNO_SP_PRINT("comminfo������������Ă��Ȃ�\n");
        return;
    }
    OHNO_SP_PRINT("CommInfo %d\n", netID);

    MI_CpuCopy8( pData, &_pCommInfo->sPlayerData[netID], sizeof(PlayerInfo));
    CommMPSetBackupMacAddress(&_pCommInfo->sPlayerData[netID].mac[0], netID);

    _pCommInfo->info[netID] = _INFO_NEW_ENTRY;  // �V���ȃG���g���[
    if(CommGetCurrentID() == netID){  // �������g�͂��łɎ�t������Ԃɂ���
        _pCommInfo->info[netID] = _INFO_ENTRY_MSGSENDED;
    }
    else{
        _pCommInfo->bNewInfoData = TRUE;
    }

}

//--------------------------------------------------------------
/**
 * @brief   My�X�e�[�^�X����M  CS_COMM_MYSTATUS
 * @param   netID           �l�b�g���[�NID
 * @param   size            ��M�f�[�^�T�C�Y
 * @param   pData           ��M�f�[�^
 * @retval  none
 */
//--------------------------------------------------------------

#if 0
void CommInfoRecvMyStatusData( int netID, int size, void* pData, void* pWork)
{
    if(!_pCommInfo){
        OHNO_PRINT("comminfo������������Ă��Ȃ�\n");
        return;
    }
    OHNO_SP_PRINT("CommInfoServer��M %d \n",netID);

    OHNO_PRINT("CommInfoServer �V���ȃG���g���[ %d\n", netID);
    OHNO_PRINT("CommInfo mystatusGET %d\n", netID);
    MI_CpuCopy8( pData, _pCommInfo->pMyStatus[netID], MyStatus_GetWorkSize());
    _pCommInfo->info[netID] = _INFO_NEW_ENTRY;  // �V���ȃG���g���[
    if(CommGetCurrentID() == netID){  // �������g�͂��łɎ�t������Ԃɂ���
        _pCommInfo->info[netID] = _INFO_ENTRY_MSGSENDED;
    }
    else{
        _pCommInfo->bNewInfoData = TRUE;
    }
}
#endif

//--------------------------------------------------------------
/**
 * @brief   My�X�e�[�^�X����M  CS_COMM_MYSTATUS_ARRAY
 * @param   netID           �l�b�g���[�NID
 * @param   size            ��M�f�[�^�T�C�Y
 * @param   pData           ��M�f�[�^
 * @retval  none
 */
//--------------------------------------------------------------

#if 0
void CommInfoRecvMyStatusArrayData( int netID, int size, void* pData, void* pWork)
{
    if(!_pCommInfo){
        OHNO_PRINT("comminfo������������Ă��Ȃ�\n");
        return;
    }
    OHNO_SP_PRINT("CommInfoClient��M %d \n",_pCommInfo->nowNetID);
    OHNO_PRINT("CommInfo mystatusArrayGET %d\n", _pCommInfo->nowNetID);
    MI_CpuCopy8(pData, _pCommInfo->pMyStatus[_pCommInfo->nowNetID],
                MyStatus_GetWorkSize());
#ifdef PM_DEBUG
    {
        const STRCODE* pN = MyStatus_GetMyName(_pCommInfo->pMyStatus[_pCommInfo->nowNetID]);
        OHNO_PRINT("%d %d %d %d\n",pN[0],pN[1],pN[2],pN[3]);
    }
#endif
    if(_pCommInfo->info[_pCommInfo->nowNetID] < _INFO_ENTRY){
        OHNO_PRINT("CommInfo �V���ȃG���g���[ %d\n", _pCommInfo->nowNetID);
        _pCommInfo->info[_pCommInfo->nowNetID] = _INFO_NEW_ENTRY;  // �V���ȃG���g���[
        if(CommGetCurrentID() == _pCommInfo->nowNetID){  // �������g�͂��łɎ�t������Ԃɂ���
            _pCommInfo->info[_pCommInfo->nowNetID] = _INFO_ENTRY_MSGSENDED;
        }
    }

}
#endif

//--------------------------------------------------------------
/**
 * @brief   �T�[�o�[����q�@�ɑS���̃��\�[�X�𑗐M���܂�
 * @param   none
 * @retval  �Ԃ��I������^�C�~���O��TRUE
 */
//--------------------------------------------------------------

BOOL CommInfoSendArray_ServerSide(void)
{
    int i;
    if(!_pCommInfo->bNewInfoData){
        return FALSE;
    }

    if(!CommIsSendCommand_ServerSize(CS_COMM_INFO_END)){
        OHNO_PRINT("comminfoarray-------�q�@�ɑ��M\n");
        for(i=0;i<COMM_MACHINE_MAX;i++){
            if(_pCommInfo->info[i] != _INFO_EMPTY){
                OHNO_PRINT("%d �𑗐M\n", i);
                _pCommInfo->sPlayerData[i].netID = i;
                MI_CpuCopy8(_pCommInfo->pMyStatus[i], _pCommInfo->sPlayerData[i].myStatusBuff,MyStatus_GetWorkSize());
                CommSetSendQueue_ServerSide(CS_COMM_INFO_ARRAY,
                                            &_pCommInfo->sPlayerData[i],
                                            sizeof(PlayerInfo));
                //                CommSetSendQueue_ServerSide(CS_COMM_MYSTATUS_ARRAY,
                //                                          _pCommInfo->pMyStatus[i],
                //                                        MyStatus_GetWorkSize());
            }
        }
        // INFO�f�[�^��S�đ���I��������𑗐M ����ID�̃��N�G�X�g�ŏI�����
        CommSetSendQueue_ServerSide(CS_COMM_INFO_END, NULL,0);
        _pCommInfo->bNewInfoData = FALSE;
        return TRUE;
    }
    return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   �V����info�f�[�^���������ǂ���
 * @param   none
 * @retval  �V����info�f�[�^�������ꍇTRUE
 */
//--------------------------------------------------------------

BOOL CommInfoIsNewInfoData(void)
{
    return _pCommInfo->bNewInfoData;
}

//--------------------------------------------------------------
/**
 * @brief   ���[�N�ɂ��閼�O�𓾂܂�
 * @param   index       �l����index�ԍ�
 * @param   name        �l���̖��O������o�b�t�@�̃|�C���^
 * @retval  ���O����������TRUE
 */
//--------------------------------------------------------------

BOOL CommInfoGetName(int index,u16* name)
{
    return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   ���[�N�ɂ���l����ID�𕶎���œ��܂�
 * @param   index       �l����index�ԍ�
 * @param   idStr       �l����ID������o�b�t�@�̃|�C���^
 * @retval  ID����������TRUE
 */
//--------------------------------------------------------------

BOOL CommInfoGetIDString(int netID, u16* idStr)
{
    return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   ��������
 * @param   netID           �l�b�g���[�NID
 * @retval  none
 */
//--------------------------------------------------------------

void CommInfoDeletePlayer(int netID)
{
    //    _pCommInfo->sPlayerData[netID].pokeNickName[0] = 0;
    //    _pCommInfo->sPlayerData[netID].pokeID = _INVALID_POKEID;
    MyStatus_Init(_pCommInfo->pMyStatus[ netID ]);
    _pCommInfo->info[ netID ] = _INFO_EMPTY;

}

//--------------------------------------------------------------
/**
 * @brief   �V�������O�����������ǂ������ׂ�
 * @param   netID           �l�b�g���[�NID
 * @retval  �V�������O�̏ꍇTRUE��Ԃ�
 */
//--------------------------------------------------------------

BOOL CommInfoIsBattleNewName(int netID)
{
    return (_pCommInfo->info[netID] == _INFO_NEW_ENTRY);
}

//--------------------------------------------------------------
/**
 * @brief   �V�������O�����������ǂ������ׂ�
 * @param   netID           �l�b�g���[�NID
 * @retval  �V�������O�̏ꍇTRUE��Ԃ�
 */
//--------------------------------------------------------------

BOOL CommInfoIsNewName(int netID)
{
    return (_pCommInfo->info[netID] == _INFO_ENTRY) || (_pCommInfo->info[netID] == _INFO_NEW_ENTRY);
}

//--------------------------------------------------------------
/**
 * @brief   �V�Ԓ��ԂƂ��ĔF�؂���
 * @param   netID           �l�b�g���[�NID
 * @retval  none
 */
//--------------------------------------------------------------

void CommInfoSetEntry(int netID)
{
    _pCommInfo->info[netID] = _INFO_ENTRY;
}

//--------------------------------------------------------------
/**
 * @brief   �󂯎�����Ƃ������b�Z�[�W�\�����I��������Ƃ��i�[����
 * @param   netID           �l�b�g���[�NID
 * @retval  none
 */
//--------------------------------------------------------------

void CommInfoSetMessageEnd(int netID)
{
    _pCommInfo->info[netID] = _INFO_ENTRY_MSGSENDED;
}


//--------------------------------------------------------------
/**
 * @brief   �V�������O�����������ǂ������ׂ�
 * @param   netID           �l�b�g���[�NID
 * @retval  �V�������O�̏ꍇ0�ȏ��Ԃ�
 */
//--------------------------------------------------------------

int CommInfoGetNewNameID(void)
{
    int i;

    for(i = 0; i < COMM_MACHINE_MAX ; i++){
        if(_pCommInfo->info[i] == _INFO_NEW_ENTRY){
            return i;
        }
    }
    return INVALID_NETID;
}

//--------------------------------------------------------------
/**
 * @brief   �����G���g���[�����l�����A��
 * @param   none
 * @retval  num
 */
//--------------------------------------------------------------

int CommInfoGetEntryNum(void)
{
    int i;
    int j = 0;

    for(i = 0; i < COMM_MACHINE_MAX ; i++){
        switch(_pCommInfo->info[i]){
          case _INFO_ENTRY:
          case _INFO_ENTRY_MSGSENDED:
            j++;
            break;
        }
    }
    return j;
}

//--------------------------------------------------------------
/**
 * @brief   �ڑ��ɉ����ăf�[�^������
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

void CommInfoFunc(void)
{
    int i;

    if(_pCommInfo){
        if(CommGetConnectNum()==0){
            return;
        }
        for(i = 0; i < COMM_MACHINE_MAX ; i++){
            if( !CommIsConnect(i) && !( (i == COMM_PARENT_ID) && CommGetAloneMode())  ){
                if(_pCommInfo->info[i] != _INFO_EMPTY){
                    CommInfoDeletePlayer(i);
                }
            }
        }
    }
}


//==============================================================================
/**
 *  MyStatus��Ԃ�
 * @param   netID   id
 * @retval  MYSTATUS*
 */
//==============================================================================

MYSTATUS* CommInfoGetMyStatus(int netID)
{
    if(!_pCommInfo){
        return NULL;
    }
    switch(_pCommInfo->info[netID]){
      case _INFO_NEW_ENTRY:
      case _INFO_ENTRY:
      case _INFO_ENTRY_MSGSENDED:
        return _pCommInfo->pMyStatus[netID];
    }
    return NULL;
}

//==============================================================================
/**
 * REGULATION��Ԃ�
 * @param   netID   id
 * @retval  REGULATION*
 */
//==============================================================================

const REGULATION* CommInfoGetRegulation(int netID)
{
    if(!_pCommInfo){
        return NULL;
    }
    switch(_pCommInfo->info[netID]){
      case _INFO_NEW_ENTRY:
      case _INFO_ENTRY:
      case _INFO_ENTRY_MSGSENDED:
        return (const REGULATION*)_pCommInfo->sPlayerData[netID].myRegulation;
    }
    return NULL;
}

//==============================================================================
/**
 *  DWCFriendData��Ԃ�
 * @param   netID   id
 * @retval  DWCFriendData*
 */
//==============================================================================

DWCFriendData* CommInfoGetDWCFriendCode(int netID)
{
    if(_pCommInfo->info[netID] != _INFO_EMPTY){
        return &_pCommInfo->sPlayerData[netID].friendData;   //�ʐM�œn���p�̃t�����h�R�[�h
    }
    return NULL;
}

//==============================================================================
/**
 *  GroupName��Ԃ�
 * @param   netID   id
 * @retval  STRCODE*
 */
//==============================================================================

STRCODE* CommInfoGetGroupName(int netID)
{
    if(_pCommInfo->info[netID] != _INFO_EMPTY){
        return _pCommInfo->sPlayerData[netID].groupName;
    }
    return NULL;
}

//==============================================================================
/**
 * myNation��Ԃ�
 * @param   netID   id
 * @retval  ���s�����ꍇ�͂O
 */
//==============================================================================

int CommInfoGetMyNation(int netID)
{
    if(_pCommInfo->info[netID] != _INFO_EMPTY){
        return _pCommInfo->sPlayerData[netID].my_nation;
    }
    return 0;
}

//==============================================================================
/**
 * myArea��Ԃ�
 * @param   netID   id
 * @retval  ���s�����ꍇ�͂O
 */
//==============================================================================

int CommInfoGetMyArea(int netID)
{
    if(_pCommInfo->info[netID] != _INFO_EMPTY){
        return _pCommInfo->sPlayerData[netID].my_area;
    }
    return 0;
}

//==============================================================================
/**
 * myPenalty��Ԃ�
 * @param   netID   id
 * @retval  ���s�����ꍇ�͂O
 */
//==============================================================================

int CommInfoGetMyPenalty(int netID)
{
    if(_pCommInfo->info[netID] != _INFO_EMPTY){
        return _pCommInfo->sPlayerData[netID].myPenalty;
    }
    return 0;
}




//==============================================================================
/**
 * �ڑ����Ă���l�̃��M�����[�V�������������ǂ�����������
 * @param   void
 * @retval  ���s�����ꍇ�͂O
 */
//==============================================================================

BOOL CommInfoRegulationCheck(void)
{
    int i,j;

    for(i = 0; i < COMM_MACHINE_MAX-1 ; i++){
        if( CommIsConnect(i) && (_pCommInfo->info[i] != _INFO_EMPTY)){
            if( CommIsConnect(i+1) && (_pCommInfo->info[i+1] != _INFO_EMPTY)){
                DEBUG_DUMP(_pCommInfo->sPlayerData[i].myRegulation, COMM_SEND_REGULATION_SIZE,"");
                DEBUG_DUMP(_pCommInfo->sPlayerData[i+1].myRegulation, COMM_SEND_REGULATION_SIZE,"");
                for(j = 0;j < COMM_SEND_REGULATION_SIZE ; j++){
                    if(_pCommInfo->sPlayerData[i].myRegulation[j] != _pCommInfo->sPlayerData[i+1].myRegulation[j]){
                        return FALSE;
                    }
                }
            }
        }
    }
    return TRUE;
}

//==============================================================================
/**
 * �������������̋L�^������
 * @param   type �J�E���g���
 * @param   num  ��
 * @retval  none
 */
//==============================================================================

static void _commInfoSetResult(int type,int num)
{
    int i;
    int myStandBit,targetBit;

    if(_pCommInfo==NULL){
        return;
    }
    if(type != _RESULT_TYPE_TRADE){
        myStandBit = CommGetStandNo(CommGetCurrentID()) & 0x1;  // �����̗���
    }

    
    for(i = 0; i < CommGetConnectNum(); i++){
        if( CommIsConnect(i) && (_pCommInfo->info[i] != _INFO_EMPTY)){
            if(type == _RESULT_TYPE_WIN){
                targetBit = CommGetStandNo(i) & 0x1;
                if(myStandBit != targetBit){
                    _pCommInfo->sPlayerResult[i].win += num;
                    OHNO_PRINT("������ %d %d %d\n",i,type,num);
                }
            }
            else if(type == _RESULT_TYPE_LOSE){
                targetBit = CommGetStandNo(i) & 0x1;
                if(myStandBit != targetBit){
                    _pCommInfo->sPlayerResult[i].lose += num;
                    OHNO_PRINT("�܂��� %d %d %d\n",i,type,num);
                }
            }
            else{
                _pCommInfo->sPlayerResult[i].trade += num;
            }
        }
    }
}

//------------------------------------------------------------------
/**
 * $brief   ��������������񐔂�o�^����
 * @param   wk
 * @param   seq
 * @retval  int
 */
//------------------------------------------------------------------

void CommInfoWriteResult(SAVEDATA* pSaveData)
{
    WIFI_LIST* pList = SaveData_GetWifiListData(pSaveData);
    int i,ret,pos;

    for(i = 0; i < CommGetConnectNum(); i++){
        DWCFriendData* pFriend = CommInfoGetDWCFriendCode(i);
        if(pFriend == NULL){
            continue;
        }
        ret = dwc_checkfriendByToken(pSaveData, pFriend, &pos);
        switch(ret){
          case DWCFRIEND_INLIST:// �c ���łɁA�����f�[�^�����X�g��ɂ���B���̏ꍇ�͉�������K�v�Ȃ��B
          case DWCFRIEND_OVERWRITE:// �c ���łɁA�����f�[�^�����X�g��ɂ��邪�A�㏑�����邱�Ƃ��]�܂����ꍇ�B
            GF_ASSERT(pos >= 0);

            OHNO_PRINT("���������L�^  %d %d  %d %d %d \n",i,pos,
                       _pCommInfo->sPlayerResult[i].win,
                       _pCommInfo->sPlayerResult[i].lose,
                       _pCommInfo->sPlayerResult[i].trade);
            WifiList_SetResult(pList, pos,
                               _pCommInfo->sPlayerResult[i].win,
                               _pCommInfo->sPlayerResult[i].lose,
                               _pCommInfo->sPlayerResult[i].trade);
            break;
        }
    }
    // �����܂�
    for(i = 0;i < COMM_MACHINE_MAX;i++){
        _pCommInfo->sPlayerResult[i].win = 0;
        _pCommInfo->sPlayerResult[i].lose = 0;
        _pCommInfo->sPlayerResult[i].trade = 0;
    }

}

//------------------------------------------------------------------
/**
 * $brief   ���������̓o�^
 * @param   wk
 * @param   seq
 * @retval  int
 */
//------------------------------------------------------------------

void CommInfoSetBattleResult(SAVEDATA* pSaveData, int bWin )
{
    if(bWin==1){
        _commInfoSetResult(_RESULT_TYPE_WIN, 1);
    }
    else if(bWin == -1){
        _commInfoSetResult(_RESULT_TYPE_LOSE, 1);
    }
    CommInfoWriteResult(pSaveData);
}

void CommInfoSetTradeResult(SAVEDATA* pSaveData, int num)
{
    _commInfoSetResult(_RESULT_TYPE_TRADE, num);
    CommInfoWriteResult(pSaveData);
}

