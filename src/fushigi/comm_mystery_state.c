//=============================================================================
/**
 * @file	comm_mystery_state.c
 * @brief	�ʐM��Ԃ��Ǘ�����T�[�r�X  �ʐM�̏�ʂɂ���
 *          	�X���b�h�̂ЂƂƂ��ē����A�����̒ʐM��Ԃ⑼�̋@���
 *          	�J�n��I�����Ǘ�����
 *		��comm_field_state.c�̐^�����q
 * @author	Satoshi Mitsuhara
 * @date    	2006.05.17
 */
//=============================================================================
#include "common.h"
#include "system/main.h"

#include "communication/communication.h"
#include "communication/comm_state.h"

#include "comm_command_mystery.h"
#include "comm_mystery_state.h"
#include "comm_mystery_gift.h"

//==============================================================================
//	�^�錾
//==============================================================================
// �R�[���o�b�N�֐��̏���
typedef void (*PTRStateFunc)(void);
//==============================================================================
// ���[�N
//==============================================================================
typedef struct{
  MYSTERYGIFT_WORK *pMSys;
  MATHRandContext32 sRand; 			//< �e�q�@�l�S�V�G�[�V�����p�����L�[
  TCB_PTR pTcb;
  PTRStateFunc state;
  u16 timer;
  u8 bStateNoChange;
  u8 connectIndex;   				// �q�@���ڑ�����e�@��index�ԍ�
  MYSTATUS *status[SCAN_PARENT_COUNT_MAX];

  GIFT_DATA recv_data;				// ��M�����f�[�^
  u8 recv_flag;					// ��M�����t���O
  u8 result_flag[SCAN_PARENT_COUNT_MAX];	// �����Ǝ�M���܂����Ԏ�

  //  u8 beacon_data[MYSTERY_BEACON_DATA_SIZE];	// �r�[�R���f�[�^
  
} _COMM_STATE_WORK;

static _COMM_STATE_WORK *_pCommStateM = NULL;  ///<�@���[�N�\���̂̃|�C���^

//==============================================================================
// ��`
//==============================================================================
#define _START_TIME (50)     // �J�n����
#define _CHILD_P_SEARCH_TIME (12) ///�q�@�Ƃ��Đe��T������
#define _PARENT_WAIT_TIME (40) ///�e�Ƃ��Ă̂�т�҂���
#define _FINALIZE_TIME (2)
#define _EXIT_SENDING_TIME (5)
#define _PARENT_END_TIME (2)
#define _SEND_NAME_TIME (10)
#define _PARENTSCAN_PA (3)  // �e�@�Ƃ��Č�������m����1/3

#define _TCB_COMMCHECK_PRT   (10)    ///< �t�B�[���h������ʐM�̊Ď����[�`����PRI

//==============================================================================
// static�錾
//==============================================================================
static void _commCheckFunc(TCB_PTR tcb, void* work);  // �X�e�[�g�����s���Ă���^�X�N
static void _mysteryParentInit(void);
static void _mysteryParentWaiting(void);

static void _mysteryChildInit(void);
static void _mysteryChildBconScanning(void);
static void _mysteryChildConnecting(void);
static void _mysteryChildSendName(void);
static void _mysteryChildWaiting(void);

#define   _CHANGE_STATE(state, time)  _changeState(state, time)

//==============================================================================
/**
 * �ʐM�Ǘ��X�e�[�g�̏���������
 * @param   none
 * @retval  none
 */
//==============================================================================
static void _commStateInitialize(MYSTERYGIFT_WORK *pMSys)
{
  void* pWork;

  if(_pCommStateM != NULL)		// ���łɓ��쒆�̏ꍇ�K�v�Ȃ�
    return;

  CommCommandMysteryInitialize((void *)pMSys);
  // ������
  _pCommStateM = (_COMM_STATE_WORK*)sys_AllocMemory(HEAPID_COMMUNICATION, sizeof(_COMM_STATE_WORK));
  MI_CpuFill8(_pCommStateM, 0, sizeof(_COMM_STATE_WORK));
  _pCommStateM->timer = _START_TIME;
  _pCommStateM->pTcb = TCB_Add(_commCheckFunc, NULL, _TCB_COMMCHECK_PRT);
  _pCommStateM->pMSys = pMSys;
  CommRandSeedInitialize(&_pCommStateM->sRand);
}


//==============================================================================
/**
 * �ʐM�Ǘ��X�e�[�g�̕ύX
 * @param   state  �ς���X�e�[�g�̊֐�
 * @param   time   �X�e�[�g�ێ�����
 * @retval  none
 */
//==============================================================================
static void _changeState(PTRStateFunc state, int time)
{
    _pCommStateM->state = state;
    _pCommStateM->timer = time;
}


//==============================================================================
/**
 * �e�@�Ƃ��ď��������s��
 * @param   none
 * @retval  none
 */
//==============================================================================
static void _mysteryParentInit(void)
{
  int i;
  //  MYSTERYGIFT_WORK *wk;
  
  // �܂��͎����Ɛڑ�������
  if(!CommIsConnect(CommGetCurrentID()))
    return;

  for(i = 0; i < SCAN_PARENT_COUNT_MAX; i++)
    _pCommStateM->result_flag[i] = FALSE;
  // �e�@�Ƃ��Ă̏��������������̂ŁA�r�[�R������Y�t����
  //  wk = PROC_GetWork(MyseryGiftGetProcp());
  // �����̃f�[�^�͑���˂�
  CommInfoSendPokeData();
  _CHANGE_STATE(_mysteryParentWaiting, 0);
}


//==============================================================================
/**
 * �e�@�Ƃ��đҋ@��
 * @param   none
 * @retval  none
 */
//==============================================================================
static void _mysteryParentWaiting(void)
{
  int i;
  for(i = 0; i < SCAN_PARENT_COUNT_MAX; i++){
    if(_pCommStateM->status[i] == NULL && CommIsConnect(i) == TRUE){
      _pCommStateM->status[i] = CommInfoGetMyStatus(i);
      if(_pCommStateM->status[i]){
#if 0//def DEBUG_ONLY_FOR_mituhara
	OS_Printf("�q�@ %d ����ԐM������܂����I\n", i);
#endif
      }
    }
  }
}


//==============================================================================
/**
 * �q�@�̏�����
 * @param   none
 * @retval  none
 */
//==============================================================================
static void _mysteryChildInit(void)
{
  if(!CommIsVRAMDInitialize()){
    return;
  }
  _CHANGE_STATE(_mysteryChildBconScanning, 0);
}


//==============================================================================
/**
 * �q�@�ҋ@���  �e�@�r�[�R�����W��
 * @param   none
 * @retval  none
 */
//==============================================================================
static void _mysteryChildBconScanning(void)
{
  //  CommParentBconCheck();
}


//==============================================================================
/**
 * �q�@�ҋ@���  �e�@�ɋ����炢��
 * @param   none
 * @retval  none
 */
//==============================================================================
static void _mysteryChildConnecting(void)
{
  CommStateConnectBattleChild(_pCommStateM->connectIndex);
  _CHANGE_STATE(_mysteryChildSendName, 0);
}


//==============================================================================
/**
 * �q�@�ҋ@���  �e�@�ɏ��𑗐M
 * @param   none
 * @retval  none
 */
//==============================================================================
static void _mysteryChildSendName(void)
{
  if(!CommIsBattleConnectingState())
    return;

  _pCommStateM->recv_flag = 0;
  CommInfoSendPokeData();
  CommTimingSyncStart(MYSTERYGIFT_SYNC_CODE);
  _CHANGE_STATE(_mysteryChildWaiting, 0);
}


//==============================================================================
/**
 * �q�@�ҋ@���
 * @param   none
 * @retval  none
 */
//==============================================================================
static void _mysteryChildWaiting(void)
{
  //Exit���󂯎������q�@�ؒf
}




//==============================================================================
/**
 * �ʐM�Ǘ��X�e�[�g�̏���
 * @param
 * @retval  none
 */
//==============================================================================
void _commCheckFunc(TCB_PTR tcb, void* work)
{
  if(_pCommStateM==NULL){
    TCB_Delete(tcb);
  } else {
    if(_pCommStateM->state != NULL){
      PTRStateFunc state = _pCommStateM->state;
      if(!_pCommStateM->bStateNoChange){
	state();
      }
    }
  }
}


//==============================================================================
/**
 * �u�ӂ����Ȃ�������́v�̐e�Ƃ��Ă̒ʐM�����J�n
 * @param   serviceNo  �ʐM�T�[�r�X�ԍ�
 * @retval  none
 */
//==============================================================================
void CommMysteryStateEnterGiftParent(MYSTERYGIFT_WORK *pMSys, SAVEDATA *sv, int serviceNo)
{
  if(CommIsInitialize())
    return;      // �Ȃ����Ă���ꍇ���͏��O����

  CommStateEnterMysteryParent(sv, serviceNo);
  _commStateInitialize(pMSys);
  _CHANGE_STATE(_mysteryParentInit, 0);
}

//==============================================================================
/**
 * ���������������q�̐���Ԃ�
 * @param   none
 * @retval  none
 */
//==============================================================================
int CommMysteryGetCommChild(void)
{
  int i, max;
  for(max = 0, i = 1; i < SCAN_PARENT_COUNT_MAX; i++)
    if(_pCommStateM->status[i])	max++;
  return max;
}

//==============================================================================
/**
 * �e�@�F�q�����Ă���q�@�փf�[�^�𑗂�
 * @param   none
 * @retval  none
 */
//==============================================================================
void CommMysterySendGiftDataParent(const void *p, int size)
{
  CommSendHugeData_ServerSide(CM_GIFT_DATA, p, size);
}










//==============================================================================
/**
 * �u�ӂ����Ȃ�������́v�̎q�Ƃ��Ă̒ʐM�����J�n
 * @param   serviceNo  �ʐM�T�[�r�X�ԍ�
 * @retval  none
 */
//==============================================================================
void CommMysteryStateEnterGiftChild(MYSTERYGIFT_WORK *pMSys, int serviceNo)
{
  SAVEDATA *sv;
  if(CommIsInitialize())
    return;      // �Ȃ����Ă���ꍇ���͏��O����

  // �ʐM�q�[�v�쐬
  sv = ((MAINWORK *)PROC_GetParentWork(MyseryGiftGetProcp()))->savedata;
  CommStateEnterMysteryChild(sv, serviceNo);
    _commStateInitialize(pMSys);
    _CHANGE_STATE(_mysteryChildInit, 0);
}


//==============================================================================
/**
 * �u�ӂ����Ȃ�������́v�̎q�Ƃ��Ă̒ʐM�����J�n
 * @param   connectIndex �ڑ�����e�@��Index
 * @retval  none
 */
//==============================================================================
void CommMysteryStateConnectGiftChild(int connectIndex)
{
  _pCommStateM->connectIndex = connectIndex;
  _CHANGE_STATE(_mysteryChildConnecting, 0);
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	�L���ȃr�[�R�������󂯎�������Ԃ�
 * @param	NONE
 * @return	0�`15: �󂯎���� -1: �󂯎��Ȃ�����
 *		���󂯎�����ꍇ��beacon_data�ɏ�񂪃R�s�[�����
*/
//--------------------------------------------------------------------------------------------
int CommMysteryCheckParentBeacon(MYSTERYGIFT_WORK *wk)
{
  int i;
  GIFT_BEACON *p;

  for(i = 0; i < SCAN_PARENT_COUNT_MAX; i++){
    p = (GIFT_BEACON *)CommMPGetBeaconTempData(i);
    if(p){
      if(p->event_id){
#if 0
	memcpy(&wk->gift_data.gd2.b, p, sizeof(GIFT_DATA2_B));
#endif
	memcpy(&wk->gift_data.beacon, p, sizeof(GIFT_BEACON));
#if 0//def DEBUG_ONLY_FOR_mituhara
	OS_Printf("�r�[�R���f�[�^�� %d �Ɏ󂯎��܂����I\n", i);
	OS_Printf("event_id = %d\n", p->event_id);
	OS_Printf("have_card = %d\n", p->have_card);
#endif
	return i;
      }
    }
  }
  return -1;
}

//--------------------------------------------------------------------------------------------
/**
 * @brief	�����ƃf�[�^���󂯎�ꂽ����e�@�֓`�B
 * @param	NONE
 * @return	NONE
 */
//--------------------------------------------------------------------------------------------
void CommMysteryResultRecvData(void)
{
  CommSendData(CM_RECV_RESULT, NULL, 0);
}


//==============================================================================
/**
 * ��������́@�̃f�[�^���󂯎�����ۂɌĂ΂��R�[���o�b�N
 * @param   netID    ���M���Ă���ID
 * @param   size     �����Ă����f�[�^�T�C�Y
 * @param   pData    ��������̂ւ̃f�[�^�|�C���^
 * @retval  none
 */
//==============================================================================
void CommMysteryGiftRecvPlace(int netID, int size, void* pBuff, void* pWork)
{
  /* �m��Ȃ����肩��f�[�^�������Ă����疳�� */
  if(_pCommStateM->connectIndex != netID)
    return;
  _pCommStateM->recv_flag = 1;
#if 0//def DEBUG_ONLY_FOR_mituhara
  OS_Printf("��������̂̃f�[�^���󂯎��܂����I\n");
#endif
}

//==============================================================================
/**
 * @brief	��������̂̃f�[�^�������Ă������Ԃ�
 * @param	NONE
 * @return	TRUE: �����Ă��� : FALSE: �����Ă��Ă��Ȃ�
 */
//==============================================================================
int CommMysteryCheckRecvData(void)
{
  return _pCommStateM->recv_flag;
}

//==============================================================================
/**
 * ��������́@�̃f�[�^�T�C�Y��Ԃ�
 * @param   none
 * @retval  �f�[�^�T�C�Y
 */
//==============================================================================
int CommMysteryGetRecvPlaceSize(void)
{
  return sizeof(GIFT_DATA);
}

//==============================================================================
/**
 * ��������́@���i�[����|�C���^��Ԃ�
 * @param   none
 * @retval  �|�C���^
 */
//==============================================================================
u8* CommGetMysteryGiftRecvBuff( int netID, void* pWork, int size)
{
  return (u8 *)&_pCommStateM->recv_data;
}

//==============================================================================
/**
 * ��������́@�������Ă������Ƃ𑗂�
 * @param   none
 * @retval  �|�C���^
 */
//==============================================================================
void CommMysterySendRecvResult(int netID, int size, void* pBuff, void* pWork)
{
#if 0//def DEBUG_ONLY_FOR_mituhara
  OS_Printf("%d %d %08X %08X\n", netID, size, pBuff, pWork);
#endif

  _pCommStateM->result_flag[netID] = TRUE;
}

//==============================================================================
/**
 * �ڑ�����Ă��邷�ׂĂ̎q�@����Ԏ����Ԃ��Ă������Ԃ�
 * @param   none
 * @retval  TRUE: �Ԃ��Ă��� : FALSE: �Ԃ��Ă��Ă��Ȃ�
 */
//==============================================================================
int CommMysteryGiftGetRecvCheck(void)
{
  int i;
  for(i = 1; i < SCAN_PARENT_COUNT_MAX; i++){
    if(CommInfoGetMyStatus(i) && _pCommStateM->status[i] && _pCommStateM->result_flag[i] != TRUE)
      return FALSE;
  }
  return TRUE;
}


//==============================================================================
/**
 * �ʐM���I��������
 * @param   none
 * @retval  none
 */
//==============================================================================
void CommMysteryExitGift(void)
{
  sys_FreeMemory(HEAPID_COMMUNICATION, _pCommStateM);
  _pCommStateM = NULL;
  CommStateExitBattle();
}

/*  */
