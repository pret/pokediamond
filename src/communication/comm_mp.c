//=============================================================================
/**
 * @file	comm_mp.c
 * @brief	�ʐM�̐ڑ����Ǘ����Ă���N���X  comm_system.c ���番��
            �ŏI�I�� WIFI���C�u�����ƕ���ɂȂ��Ă���...�\��

            comm_sys    ---   comm_mp         --   comm_local.c
                         |                     |--  wh.c
                         |
                         |
                         --   comm_wifi      --   comm_local.c
                                              |----wifi.lib

   
 * @author	Katsumi Ohno
 * @date    2006.01.25
 */
//=============================================================================


#include "common.h"
#include "wh_config.h"
#include "wh.h"
#include "communication/communication.h"
#include "communication/comm_state.h"
#include "comm_local.h"

#include "system/pm_str.h"
#include "system/gamedata.h"  //PERSON_NAME_SIZE

#include "comm_ring_buff.h"
#include "system/pm_rtc.h"  //GF_RTC
#include "system/savedata.h"
#include "savedata/regulation.h"

//==============================================================================
// extern�錾
//==============================================================================

// �R���p�C�����Ƀ��[�j���O���o��̂Œ�`���Ă���
#include "communication/comm_system.h"


//==============================================================================
// ��`
//==============================================================================


#define _PORT_DATA_RETRANSMISSION   (14)    // �ؒf����܂Ŗ����đ����s��  ��������g�p���Ă���
#define _PORT_DATA_PARENT           _PORT_DATA_RETRANSMISSION
#define _PORT_DATA_CHILD            _PORT_DATA_RETRANSMISSION

#define _KEEP_CHANNEL_TIME_MAX   (5)

#define _NOT_INIT_BITMAP  (0xffff)   // �ڑ��l�����Œ�Ɏw��Ȃ��ꍇ�̒l

typedef enum{    // �ؒf���
    _DISCONNECT_NONE,
    _DISCONNECT_END,
    _DISCONNECT_SECRET,
    _DISCONNECT_STEALTH,
};

#define _BEACON_SIZE_MAX   MATH_MAX(sizeof(_GF_BSS_MYSTERY),sizeof(_GF_BSS_DATA_INFO))


//�Ǘ��\���̒�`
typedef struct{
    u8 mysteryData[MYSTERY_BEACON_DATA_SIZE];
    WMBssDesc sBssDesc[SCAN_PARENT_COUNT_MAX];  ///< �e�@�̏����L�����Ă���\����
    u8  backupBssid[COMM_MACHINE_MAX][WM_SIZE_BSSID];   // ���܂Őڑ����Ă���
    u16 bconUnCatchTime[SCAN_PARENT_COUNT_MAX]; ///< �e�@�̃r�[�R�����E��Ȃ���������+�f�[�^�����邩�ǂ���
    void* _pWHWork;                           ///wh���C�u�������g�p���郏�[�N�̃|�C���^
    PMS_DATA pmsData;
    int sBeaconCount;                           ///< �r�[�R���J�E���^
//    MATHRandContext32 sRand;                    ///< wep�p�����L�[
    u8 bScanCallBack;  ///< �e�̃X�L���������������ꍇTRUE, ������FALSE
    u8 regulationNo;   ///< �Q�[�����M�����[�V����
#ifdef PM_DEBUG		//DebugROM
    u8 soloDebugNo;
#endif
    /// ----------------------------�q�@�p
    MYSTATUS* pMyStatus;            // �����̃X�e�[�^�X
    REGULATION* pRegulation;        // �T�����M�����[�V���� �K�v�Ȃ��ꍇ��NULL
//    u32 wepSeed;
    u32 ggid;
    u16 gameInfoBuff[WM_SIZE_USER_GAMEINFO];
    u16 keepChannelNo;
    u16 errCheckBitmap;      ///< ����BITMAP���H���Ⴄ�ƃG���[�ɂȂ�
    u8 channel;
    u8 keepChannelTime;
    u8 disconnectType;    ///< �ؒf��
    u8 bSetReceiver;
    u8 bEndScan;  // endscan
    u8 bErrorState:1;     ///< �G���[�������N�����Ă���ꍇ���̏�Ԃ������܂�
    u8 bErrorDisconnectOther:1;     ///< �N����������ƃG���[�ɂȂ�܂�
    u8 bErrorNoChild:1;  ///< �q�@�������ꍇ�G���[�������邩�ǂ���
    u8 bTGIDChange:1;
    u8 bAutoExit:1;
    u8 bEntry:1;   // �q�@�̐V�K�Q��
//    u8 bStalth:1;
} _COMM_WORK;

//==============================================================================
// ���[�N
//==============================================================================

///< ���[�N�\���̂̃|�C���^
static _COMM_WORK* _pCommMP = NULL;

// �e�@�ɂȂ�ꍇ��TGID �\���̂ɓ���Ă��Ȃ��̂�
// �ʐM���C�u�����[��؂����Ƃ��Ă��C���N�������g����������
/// TGID�Ǘ�
static u16 _sTgid = 0;


// WEP Key �쐬�p�̋��ʌ��i�e�q�ŋ��ʂ̌����g�p����j
// �A�v���P�[�V�������ƂɌŗL�̂��̂Ƃ��邱��
// ASCII ������ł���K�v�͂Ȃ��A�C�ӂ̒����̃o�C�i���f�[�^�ł悢
//static char* _sSecretKey = " http://www.gamefreak.co.jp/ ";



// �R���|�[�l���g�]���I���̊m�F�p
// �C�N�j���[�����R���|�[�l���g�������ړ�������Ƃ��͂�����ړ�
static volatile int   startCheck;	

//==============================================================================
// static�錾
//==============================================================================

static void _whInitialize(void);
static void _childDataInit(void);
static void _parentDataInit(BOOL bTGIDChange);
static void _commInit(void);
static void _setUserGameInfo( void );
static BOOL _isMachBackupMacAddress(u8* pMac);
static u16 _getServiceBeaconPeriod(u16 serviceNo);

static void _scanCallback(WMBssDesc *bssdesc);
static void _startUpCallback(void *arg, WVRResult result);
static void _indicateCallback(void *arg);
static int _connectNum(void);

//==============================================================================
/**
 * �ڑ��N���X�̏�����
 * @param   pMyStatus   MYSTATUS�|�C���^
 * @retval  none
 */
//==============================================================================

void CommMPInitialize(MYSTATUS* pMyStatus)
{
    int i;
    
    if(_pCommMP!=NULL){  // ���łɏ��������Ă���ꍇ��return
        return;
    }
    _pCommMP = (_COMM_WORK*)sys_AllocMemory(HEAPID_COMMUNICATION, sizeof(_COMM_WORK));
    MI_CpuClear8(_pCommMP, sizeof(_COMM_WORK));
    _pCommMP->_pWHWork = sys_AllocMemory(HEAPID_COMMUNICATION, WH_GetHeapSize());
    MI_CpuClear8(_pCommMP->_pWHWork, WH_GetHeapSize());
    _pCommMP->pRegulation = sys_AllocMemory(HEAPID_COMMUNICATION, Regulation_GetWorkSize());
    MI_CpuClear8(_pCommMP->pRegulation, Regulation_GetWorkSize());
    _pCommMP->ggid = _DP_GGID;
    _pCommMP->pMyStatus = pMyStatus;
	// �ȈՉ�b������
	PMSDAT_Clear( (PMS_DATA*)&_pCommMP->pmsData );
    // �������C�u�����쓮�J�n
    _whInitialize();
}

BOOL CommMPIsConnect(void)
{
    if(_pCommMP){
        return TRUE;
    }
    return FALSE;
}

//==============================================================================
/**
 * ��r�֐�
 * @param   pCmp1,pCmp2   ��r�Ώ�
 * @retval  ��v������TRUE
 */
//==============================================================================

static BOOL _bmemcmp(const u8* pCmp1,const u8* pCmp2, int size)
{
    int i;
    const u8* pc1 = pCmp1;
    const u8* pc2 = pCmp2;

    for(i = 0; i < size; i++){
        if(*pc1 != *pc2){
            return FALSE;
        }
        pc1++;
        pc2++;
    }
    return TRUE;
}

//==============================================================================
/**
 * �q�@���e�@��T���o�������ɌĂ΂��R�[���o�b�N�֐�
 * �e�@���E�����тɌĂ΂��
 * @param   bssdesc   �O���[�v���
 * @retval  none
 */
//==============================================================================

static void DEBUG_MACDISP(char* msg,WMBssDesc *bssdesc)
{
    OHNO_PRINT("%s %02x%02x%02x%02x%02x%02x\n",msg,
               bssdesc->bssid[0],bssdesc->bssid[1],bssdesc->bssid[2],
               bssdesc->bssid[3],bssdesc->bssid[4],bssdesc->bssid[5]);
}

static void _scanCallback(WMBssDesc *bssdesc)
{
    int i;
    _GF_BSS_DATA_INFO* pGF;
    int serviceNo = CommStateGetServiceNo();
    int regulationNo = CommStateGetRegulationNo();
#ifdef PM_DEBUG		//DebugROM
    int soloDebugNo = CommStateGetSoloDebugNo();
#endif

    // catch�����e�f�[�^
    pGF = (_GF_BSS_DATA_INFO*)bssdesc->gameInfo.userGameInfo;
    if(serviceNo == COMM_MODE_POKETCH){  // �|�P�b�`�͉��ł��E��
    }
    else if(CommLocalIsUnionGroup(pGF->serviceNo) && CommLocalIsUnionGroup(serviceNo)){  // ���݂����E��
    }
    else if(pGF->pause && (pGF->serviceNo == COMM_MODE_UNDERGROUND)){
        OHNO_PRINT("pGF->pause\n");
        return;  // �|�[�Y���̐e�@�͖���
    }
    else if(pGF->serviceNo != serviceNo){
//        DEBUG_MACDISP("�T�[�r�X���قȂ�ꍇ�͏E��Ȃ�\n",bssdesc);
        return;   // �T�[�r�X���قȂ�ꍇ�͏E��Ȃ�
    }
    if(pGF->regulationNo != regulationNo){
//        DEBUG_MACDISP("���M�����[�V�������قȂ�ꍇ�͏E��Ȃ�\n",bssdesc);
        return;   // ���M�����[�V�������قȂ�ꍇ�͏E��Ȃ�
    }
#ifdef PM_DEBUG		//DebugROM
    if(serviceNo != COMM_MODE_POKETCH){
        if(pGF->soloDebugNo != soloDebugNo){
//            DEBUG_MACDISP("�f�o�b�O���قȂ�ꍇ�͏E��Ȃ�x\n",bssdesc);
            return;   // �f�o�b�O���ʔԍ����قȂ�ꍇ�͏E��Ȃ�
        }
    }
#endif
    
    // ���̃��[�v�͓������̂Ȃ̂��ǂ�������
    for (i = 0; i < SCAN_PARENT_COUNT_MAX; ++i) {
        if(_pCommMP->bconUnCatchTime[i] == 0 ){
            // �e�@��񂪓����Ă��Ȃ��ꍇcontinue
            continue;
        }
        if (_bmemcmp(_pCommMP->sBssDesc[i].bssid, bssdesc->bssid, WM_SIZE_BSSID)) {
#ifdef DEBUG_ONLY_FOR_mori
            OS_TPrintf("�r�[�R�����X�V %02x%02x%02x%02x%02x%02x\n",
                       bssdesc->bssid[0],bssdesc->bssid[1],bssdesc->bssid[2],
                       bssdesc->bssid[3],bssdesc->bssid[4],bssdesc->bssid[5]);
#endif
            // ������x�E�����ꍇ�Ƀ^�C�}�[���Z
            _pCommMP->bconUnCatchTime[i] = _DEFAULT_TIMEOUT_FRAME;
            // �V�����e����ۑ����Ă����B
            MI_CpuCopy8( bssdesc, &_pCommMP->sBssDesc[i], sizeof(WMBssDesc));

//            DEBUG_DUMP(pGF->regulationBuff, Regulation_GetWorkSize(),"�󂯎�������M��");
            return;
        }
    }
    // ���̃��[�v�͋󂫂����邩�ǂ�������
    for (i = 0; i < SCAN_PARENT_COUNT_MAX; ++i) {
        if(_pCommMP->bconUnCatchTime[i] == 0 ){
            // �e�@��񂪓����Ă��Ȃ��ꍇbreak;
            break;
        }
    }
    if(i >= SCAN_PARENT_COUNT_MAX){
        // �\���̂������ς��̏ꍇ�͐e�@���E��Ȃ�
        // @@OO�e�@���������݂���ꍇ�A�����@�\�Ƃ��K�v�Ǝv����
        return;
    }
    // �V�����e����ۑ����Ă����B
#ifdef DEBUG_ONLY_FOR_mori
    OS_TPrintf("�V�K�e�@�r�[�R�����E���� %02x%02x%02x%02x%02x%02x\n",
               bssdesc->bssid[0],bssdesc->bssid[1],bssdesc->bssid[2],
               bssdesc->bssid[3],bssdesc->bssid[4],bssdesc->bssid[5]);
#endif
    _pCommMP->bconUnCatchTime[i] = _DEFAULT_TIMEOUT_FRAME;
    MI_CpuCopy8( bssdesc, &_pCommMP->sBssDesc[i],sizeof(WMBssDesc));
    _pCommMP->bScanCallBack = TRUE;
}

//------------------------------------------------------------------
/**
 * �����쓮���䃉�C�u�����̔񓯊��I�ȏ����I�����ʒm�����R�[���o�b�N�֐��B
 *
 * @param   arg		WVR_StartUpAsync�R�[�����Ɏw�肵�������B���g�p�B
 * @param   result	�񓯊��֐��̏������ʁB
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void _startUpCallback(void *arg, WVRResult result)
{
    if (result != WVR_RESULT_SUCCESS) {
        OS_TPanic("WVR_StartUpAsync error.[%08xh]\n", result);
    }
    else{
		OS_Printf("WVR Trans VRAM-D.\n");
	}
    startCheck = 2;
}

//------------------------------------------------------------------
/**
 * �����쓮���䃉�C�u�����̔񓯊��I�ȏ����I�����ʒm�����R�[���o�b�N�֐��B
 *
 * @param   arg		WVR_StartUpAsync�R�[�����Ɏw�肵�������B���g�p�B
 * @param   result	�񓯊��֐��̏������ʁB
 *
 * @retval  none		
 */
//------------------------------------------------------------------
static void _endCallback(void *arg, WVRResult result)
{
    startCheck = 0;
    sys_SleepOK(SLEEPTYPE_COMM);  // �X���[�v��������
}

//==============================================================================
/**
 * WVR��VRAMD�Ɉړ�
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommVRAMDInitialize(void)
{
    //************************************
//	GX_DisableBankForTex();			// �e�N�X�`���C���[�W

    sys_SleepNG(SLEEPTYPE_COMM);  // �X���[�v���֎~
    // �������C�u�����쓮�J�n
	// �C�N�j���[�����R���|�[�l���g��VRAM-D�ɓ]������
    startCheck = 1;
    if (WVR_RESULT_OPERATING != WVR_StartUpAsync(GX_VRAM_ARM7_128_D, _startUpCallback, NULL)) {
        OS_TPanic("WVR_StartUpAsync failed. \n");
    }
    else{
        OHNO_PRINT("WVRStart\n");
    }
}

//==============================================================================
/**
 * WVR��VRAMD�Ɉړ����I�������1
 * @param   none
 * @retval  none
 */
//==============================================================================

BOOL CommIsVRAMDInitialize(void)
{
    return (startCheck==2);
}

//==============================================================================
/**
 * WVR��VRAMD�Ɉړ����͂��߂���P
 * @param   none
 * @retval  none
 */
//==============================================================================

BOOL CommIsVRAMDStart(void)
{
    return (startCheck!=0);
}

//==============================================================================
/**
 * �C�N�j���[�����J��
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommVRAMDFinalize(void)
{
    OHNO_PRINT("VRAMD Finalize\n");
    WVR_TerminateAsync(_endCallback,NULL);  // �C�N�j���[�����ؒf
}


//==============================================================================
/**
 * �ʐM��Ԃ�m�点��̃R�[���o�b�N
 * @param   arg WMIndCallback�\����
 * @retval  none
 */
//==============================================================================
static void _indicateCallback(void *arg)
{
    WMIndCallback *cb;
    cb = (WMIndCallback *)arg;
    if (cb->state == WM_STATECODE_BEACON_RECV) {
        if(_pCommMP){
            _pCommMP->sBeaconCount = 2;
        }
    }
}

//==============================================================================
/**
 * WH���C�u�����̏�����
 * @param   bReInit  �ď��������ǂ���
 * @param   pLocal  �ʐM���ʍ\����
 * @retval  none
 */
//==============================================================================

static void _whInitialize(void)
{
    
    _pCommMP->sBeaconCount = 0;

    
    // ����������
    {
        u32 addr = (u32)_pCommMP->_pWHWork;
        addr = 32 - (addr % 32) + addr;   //32byte�A���C�����g
        (void)WH_Initialize((void*)addr);
        (void)WM_SetIndCallback(_indicateCallback);
    }

    // WH �����ݒ�
    WH_SetGgid(_pCommMP->ggid);

    // WEP Key �̎�p�̗��������@�̏�����
//    CommRandSeedInitialize(&_pCommMP->sRand);
}

//==============================================================================
/**
 * �q�@�̎g�p���Ă���f�[�^�̏�����
 * @param   bssdesc   �O���[�v���
 * @retval  none
 */
//==============================================================================

void ChildBconDataInit(void)
{
    int i;

    for (i = 0; i < SCAN_PARENT_COUNT_MAX; ++i) {
        _pCommMP->bconUnCatchTime[i] = 0;
    }
    MI_CpuClear8(_pCommMP->sBssDesc,sizeof(WMBssDesc)*SCAN_PARENT_COUNT_MAX);
}

//==============================================================================
/**
 * �e�@�̎g�p���Ă���f�[�^�̏�����
 * @param   bTGIDChange  �V�K�̃Q�[���̏������̏ꍇTRUE �Â��r�[�R���ł̌듮���h�����ߗp
 * @retval  none
 */
//==============================================================================

static void _parentDataInit(BOOL bTGIDChange)
{
    _pCommMP->bTGIDChange = bTGIDChange;
}

//==============================================================================
/**
 * �e�q���ʁA�ʐM�̏��������܂Ƃ߂�
 * @param   work_area �@�V�X�e���Ŏg���������[�̈�
 *                      NULL�̏ꍇ���łɏ������ς݂Ƃ��ē���
 * @retval  �������ɐ���������TRUE
 */
//==============================================================================

static void _commInit(void)
{
    _pCommMP->bScanCallBack = FALSE;
    _pCommMP->bErrorState = FALSE;
    _pCommMP->bErrorNoChild = FALSE;
    
    _pCommMP->disconnectType = _DISCONNECT_NONE;
    _pCommMP->bAutoExit = FALSE;
    _pCommMP->bEndScan = 0;

    _pCommMP->bSetReceiver = FALSE;
    
    return;
}


//==============================================================================
/**
 * �ʐM���C�u�����ɕK�v�ȃ��[�N�T�C�Y��Ԃ�
 * @param   none
 * @retval  ���[�N�T�C�Y
 */
//==============================================================================
u32 CommGetWorkSize(void)
{
    OHNO_PRINT("_COMM_WORK size %d \n", sizeof(_COMM_WORK));
    return sizeof(_COMM_WORK);
}

//==============================================================================
/**
 * �e�@�̐ڑ��J�n���s��
 * @param   work_area �@�V�X�e���Ŏg���������[�̈�
 *                      NULL�̏ꍇ���łɏ������ς݂Ƃ��ē���
 * @param   serviceNo     �Q�[���̎��
 * @param   regulationNo  �Q�[���̎��
 * @param   bTGIDChange  �V�K�̃Q�[���̏������̏ꍇTRUE �Â��r�[�R���ł̌듮���h�����ߗp
 * @param  �q�@���󂯕t���邩�ǂ���
 * @retval  �������ɐ���������TRUE
 */
//==============================================================================
BOOL CommMPParentInit(BOOL bAlloc, BOOL bTGIDChange, BOOL bEntry)
{
    _commInit();
    _parentDataInit(bTGIDChange);

    WH_ParentDataInit();
    if(!_pCommMP->bSetReceiver){
        WH_SetReceiver(CommRecvParentCallback, _PORT_DATA_CHILD);
      _pCommMP->bSetReceiver = TRUE;
    }
    _pCommMP->bEntry = bEntry;

    // �d�g�g�p������œK�ȃ`�����l�����擾���Đڑ�����B�񓯊��֐�
    if(WH_GetSystemState() == WH_SYSSTATE_IDLE){
        if(WH_StartMeasureChannel()){
            return TRUE;
        }
    }
    return FALSE;
}

//==============================================================================
/**
 * �q�@�̐ڑ��J�n���s��
 * @param   work_area �@�V�X�e���Ŏg���������[�̈�
 *                      NULL�̏ꍇ�͂��łɏ������ς݂Ƃ��Ĉ���
 * @param   serviceNo  �Q�[���̎��
 * @param   regulationNo  �Q�[���̎��
 * @param   bBconInit  �r�[�R���f�[�^������������̂��ǂ���
 * @retval  �������ɐ���������TRUE
 */
//==============================================================================
BOOL CommMPChildInit(BOOL bAlloc, BOOL bBconInit)
{
    _commInit();
    if(bBconInit){
        OHNO_PRINT("�r�[�R���̏�����\n");
        ChildBconDataInit(); // �f�[�^�̏�����
    }
    if(!_pCommMP->bSetReceiver ){
        WH_SetReceiver(CommRecvCallback, _PORT_DATA_PARENT);
        _pCommMP->bSetReceiver = TRUE;
    }
    // �e�@�����X�^�[�g
    if(WH_GetSystemState() == WH_SYSSTATE_IDLE){
        // MAC�A�h���X�w��@�@�S��FF�őS�Ă�T���ɂ���
        const u8 sAnyParent[6] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
        if(WH_StartScan(_scanCallback, sAnyParent, _SCAN_ALL_CHANNEL)){
            return TRUE;
        }
    }
    return FALSE;
}

//==============================================================================
/**
 * �ʐM�؂�ւ����s���i�e�q���]�ɕK�v�ȏ����j
 * @param   none
 * @retval  ���Z�b�g������TRUE
 */
//==============================================================================

BOOL CommMPSwitchParentChild(void)
{
    if(!_pCommMP){
        return TRUE;
    }
    switch(_pCommMP->bEndScan){
      case 0:
        if(WH_IsSysStateScan()){
            WH_EndScan();
            _pCommMP->bEndScan = 1;
            break;
        }
        else if(WH_IsSysStateBusy()){  //���΂炭�҂�
        }
        else{
            WH_Finalize();
            _pCommMP->bEndScan = 2;
        }
        break;
      case 1:
        if(!WH_IsSysStateBusy()){
            WH_Finalize();
            _pCommMP->bEndScan = 2;
        }
        break;
      case 2:
        if(WH_IsSysStateIdle()){
            return TRUE;
        }
        if(WH_IsSysStateError()){
            _pCommMP->bEndScan = 1;
        }
        break;
    }
    return FALSE;
}

//==============================================================================
/**
 * �ʐM�ؒf���s��  �����ł͂����܂ŒʐM�I���葱���ɓ��邾��
 *  �z���g�ɏ����͉̂���_commEnd
 * @param   none
 * @retval  �I�������Ɉڂ����ꍇTRUE
 */
//==============================================================================
BOOL CommMPFinalize(void)
{
    if(_pCommMP){
        if(_pCommMP->disconnectType == _DISCONNECT_NONE){
            _pCommMP->disconnectType = _DISCONNECT_END;
            WH_Finalize();
            return TRUE;
        }
    }
    return FALSE;
}

//==============================================================================
/**
 * �ʐM�ؒf���s��  �������������[�J�����s��Ȃ�
 * @param   �ؒf�̏ꍇTRUE
 * @retval  none
 */
//==============================================================================
void CommMPStealth(BOOL bStalth)
{
    if(!_pCommMP){
        return;
    }
    if(bStalth){
        _pCommMP->disconnectType = _DISCONNECT_SECRET;
    }
    else{
        _pCommMP->disconnectType = _DISCONNECT_NONE;
        _whInitialize();  // �����쓮�ĊJ
    }
}

//==============================================================================
/**
 * �ʐM�̑S�Ă�����
 * @param   none
 * @retval  none
 */
//==============================================================================
static void _commEnd(void)
{
    sys_FreeMemoryEz(_pCommMP->pRegulation);
    sys_FreeMemoryEz(_pCommMP->_pWHWork);
    sys_FreeMemoryEz(_pCommMP);
    _pCommMP = NULL;
}

//==============================================================================
/**
 * �T�����Ƃ��ł����e�̐���Ԃ�
 * @param   none
 * @retval  �e�@�̐�
 */
//==============================================================================

int CommMPGetParentCount(void)
{
    int i, cnt;

    if(!CommIsInitialize()){
        return 0;
    }

    cnt = 0;
    for (i = 0; i < SCAN_PARENT_COUNT_MAX; ++i) {
        if(_pCommMP->bconUnCatchTime[i] != 0 ){
            cnt++;
        }
    }
    return cnt;
}

//--------------------------------------------------------------
/**
 * @brief   BmpList�̈ʒu����Bcon�̑��݂���Index�ʒu���擾����
 * @param   index		BmpList�ʒu
 * @retval  Index
 */
//--------------------------------------------------------------
int CommBmpListPosBconIndexGet(int index)
{
	int i, count;
	
//	for(i = 0; i < SCAN_PARENT_COUNT_MAX; i++){
//		OS_TPrintf("List�̃r�[�R���`�F�b�N %d = %d\n", i, _pCommMP->bconUnCatchTime[i]);
//	}
	
	count = 0;
	for(i = 0; i < SCAN_PARENT_COUNT_MAX; i++){
		if(_pCommMP->bconUnCatchTime[i] != 0){
			if(count == index){
				return i;
			}
			count++;
		}
	}
	GF_ASSERT(0 && "�����ɂ͗��Ȃ��͂�");
	return 0;
}

//==============================================================================
/**
 * �e�@���X�g�ɕω����������ꍇTRUE
 * @param   none
 * @retval  �e�@���X�g�ɕω����������ꍇTRUE �Ȃ����FALSE
 */
//==============================================================================

BOOL CommMPIsScanListChange(void)
{
    return _pCommMP->bScanCallBack;
}

//==============================================================================
/**
 * �e�@�̕ω���m�点��t���O�����Z�b�g����
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommMPResetScanChangeFlag(void)
{
    _pCommMP->bScanCallBack = FALSE;
}

//==============================================================================
/**
 * ���̐e�@�������ƃR�l�N�V�����������Ă���̂��𓾂�
 * @param   index   �e�̃��X�g��index
 * @retval  �R�l�N�V������ 0-16
 */
//==============================================================================

int CommMPGetParentConnectionNum(int index)
{
    int cnt;
    _GF_BSS_DATA_INFO* pGF;

    cnt = 0;
    if(_pCommMP->bconUnCatchTime[index] != 0){
        pGF = (_GF_BSS_DATA_INFO*)_pCommMP->sBssDesc[index].gameInfo.userGameInfo;
        if(pGF->connectNum==0){
            return 1;
        }
        return pGF->connectNum;
    }
    return 0;
}

//==============================================================================
/**
 * �ڑ��l���ɊY������e��Ԃ�
 * @param   none
 * @retval  �e��index
 */
//==============================================================================

static int _getParentNum(int machNum)
{
    int i,num;

    for (i = SCAN_PARENT_COUNT_MAX-1; i >= 0; i--) {
        num = CommMPGetParentConnectionNum(i);
        if((num > machNum) && (num < COMM_MACHINE_MAX)){
            return i;
        }
    }
    return -1;
}

//==============================================================================
/**
 * �����ɐڑ����Ă����l�����������ꍇindex��Ԃ�
 * @param   none
 * @retval  �Y��������index��Ԃ�
 */
//==============================================================================

int CommMPGetFastConnectIndex(void)
{
    int i,num;

    if(CommMPGetParentCount()==0){
        return -1;
    }
    for (i = SCAN_PARENT_COUNT_MAX -1; i >= 0; i--) {
        if(_pCommMP->bconUnCatchTime[i] != 0){
            if(_isMachBackupMacAddress(&_pCommMP->sBssDesc[i].bssid[0])){  // �Â�MAC�ɍ��v
                num = CommMPGetParentConnectionNum(i);
                if(( num > 1) && (num < COMM_MACHINE_MAX)){      // �{�e�ɊY������ �܂��Q���\
                    return i;
                }
            }
        }
    }
    return -1;
}

//==============================================================================
/**
 * ���̃��x���Ōq���ł����l�������炻��index��Ԃ��܂�
 * @param   none
 * @retval  �Y��������index��Ԃ�
 */
//==============================================================================

int CommMPGetNextConnectIndex(void)
{
    int i;
 
    if(CommMPGetParentCount()==0){  // �r�[�R�����������
        return -1;
    }
    for (i = SCAN_PARENT_COUNT_MAX-1; i >= 0; i--) {
        if(_pCommMP->bconUnCatchTime[i] != 0){
            if(_isMachBackupMacAddress(&_pCommMP->sBssDesc[i].bssid[0])){  // �Â�MAC�ɍ��v
                OHNO_PRINT("�̂̐e %d\n",i);
                return i;
            }
        }
    }
    i = _getParentNum(1);
    if(i != -1 ){
        OHNO_PRINT("�����Ȃ��{�e %d \n", i);
        return i;
    }
    i = _getParentNum(0);
    if(i != -1){
        OHNO_PRINT("�����Ȃ����e %d \n", i);
        return i;
    }
    return i;
}

//==============================================================================
/**
 * �e�@���X�g��index���ɕԂ�
 * @param   index      �e�̃��X�g��index
 * @param   pMyStatus  �i�[����MYSTATUS�̃|�C���^
 * @retval  none
 */
//==============================================================================

void CommMPGetParentName(int index, MYSTATUS* pMyStatus)
{
    int i, cnt;
    _GF_BSS_DATA_INFO* pGF;

    cnt = 0;
    for (i = 0; i < SCAN_PARENT_COUNT_MAX; ++i) {
        if(_pCommMP->bconUnCatchTime[i] != 0){
            if(index == cnt){
                MyStatus_Copy( CommMPGetBconMyStatus(i), pMyStatus);
                return;
            }
            cnt++;
        }
    }
    OHNO_PRINT("���O���擾�ł��Ȃ����� index = %d\n", index);
}

//==============================================================================
/**
 * �e�@�ۂ�ID��index���ɕԂ�
 * @param   index   �e�̃��X�g��index
 * @retval  pokeID
 */
//==============================================================================

u32 CommMPGetPokeID(int index)
{
    int i, cnt;
    _GF_BSS_DATA_INFO *pGF;

    cnt = 0;
    for (i = 0; i < SCAN_PARENT_COUNT_MAX; ++i) {
        if(_pCommMP->bconUnCatchTime[i] != 0 ){
            if(index == cnt){
                pGF = (_GF_BSS_DATA_INFO*)_pCommMP->sBssDesc[i].gameInfo.userGameInfo;
                return pGF->pokeID;
            }
            cnt++;
        }
    }
    return 0;
}

//==============================================================================
/**
 * �q�@�@MP��ԂŐڑ�
 * @param   index   �e�̃��X�g��index
 * @retval  �q�@�ڑ���e�@�ɑ�������TRUE
 */
//==============================================================================
BOOL CommMPChildIndexConnect(u16 index)
{
    int serviceNo;
    
    if (WH_GetSystemState() == WH_SYSSTATE_SCANNING) {
        (void)WH_EndScan();
        return FALSE;
    }
    if (WH_GetSystemState() == WH_SYSSTATE_IDLE) {
        OHNO_PRINT("�q�@ �ڑ��J�n WH_ChildConnect\n");
        serviceNo = CommStateGetServiceNo();
        _pCommMP->channel = _pCommMP->sBssDesc[index].channel;
        if(CommLocalIsUnionGroup(serviceNo)){
           WH_ChildConnectAuto(WH_CONNECTMODE_MP_CHILD, _pCommMP->sBssDesc[index].bssid,0);
        }
        else{
            WH_ChildConnect(WH_CONNECTMODE_MP_CHILD, &(_pCommMP->sBssDesc[index]));
        }
//        WH_ChildConnectAuto(WH_CONNECTMODE_MP_CHILD, _pCommMP->sBssDesc[index].bssid,0);
        return TRUE;
    }
    return FALSE;
}

//==============================================================================
/**
 * �r�[�R���f�[�^�̒���m�F
 *  �ڑ�����������Ԃł̊ԁA���̊֐����ĂсA�^�C���A�E�g�������s��
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommMPParentBconCheck(void)
{
    int id;

    for(id = 0; id < SCAN_PARENT_COUNT_MAX; id++){
        if(_pCommMP->bconUnCatchTime[id] == 0 ){
            continue;
        }
        if(_pCommMP->bconUnCatchTime[id] > 0){
            _pCommMP->bconUnCatchTime[id]--;
            if(_pCommMP->bconUnCatchTime[id] == 0){
                OHNO_PRINT("�e�@�����Ȃ� %d\n", id);
                _pCommMP->bScanCallBack = TRUE;   // �f�[�^��ύX�����̂�TRUE
            }
        }
    }
}

//==============================================================================
/**
 *  ���[�U��`�̐e�@����ݒ肵�܂��B
 *  _GF_BSS_DATA_INFO�\���̂̒��g�𑗂�܂�
 *  @param   userGameInfo  ���[�U��`�̐e�@���ւ̃|�C���^
 *  @param   length        ���[�U��`�̐e�@���̃T�C�Y
 *  @retval  none
 */
//==============================================================================
static void _setUserGameInfo( void )
{
    u8 macBuff[6];
    MYSTATUS* pMyStatus;
    _GF_BSS_DATA_INFO* pGF;
    _GF_BSS_MYSTERY* pMist;
    int serviceNo = CommStateGetServiceNo();

    pMyStatus = CommMPGetMyStatus();
    if(serviceNo != COMM_MODE_MYSTERY){
        pGF = (_GF_BSS_DATA_INFO*)_pCommMP->gameInfoBuff;

        GF_ASSERT(COMM_SEND_REGULATION_SIZE >= Regulation_GetWorkSize());  // regulation���\����傫��
        GF_ASSERT(COMM_SEND_MYSTATUS_SIZE == MyStatus_GetWorkSize());  // mystatus���\����傫��
        GF_ASSERT(WM_SIZE_USER_GAMEINFO >= _BEACON_SIZE_MAX);  // bcon�T�C�Y���GF�r�[�R�����傫��

        MI_CpuCopy8( pMyStatus, pGF->myStatusBuff, MyStatus_GetWorkSize());
        MI_CpuCopy8( _pCommMP->pRegulation,pGF->regulationBuff, Regulation_GetWorkSize());
        pGF->pokeID = MyStatus_GetID(pMyStatus);
        pGF->serviceNo = CommStateGetServiceNo();
        pGF->regulationNo = CommStateGetRegulationNo();
        // �ȈՉ�b
        MI_CpuCopy8( &_pCommMP->pmsData, &pGF->pmsData, sizeof(PMS_DATA));
#ifdef PM_DEBUG		//DebugROM
        pGF->soloDebugNo = CommStateGetSoloDebugNo();
#endif
        pGF->pause = WHGetParentConnectPause();
    }
    else{
        pMist = (_GF_BSS_MYSTERY*)_pCommMP->gameInfoBuff;

        pMist->pokeID = MyStatus_GetID(pMyStatus);
        pMist->serviceNo = CommStateGetServiceNo();
        pMist->regulationNo = CommStateGetRegulationNo();
#ifdef PM_DEBUG		//DebugROM
        pMist->soloDebugNo = CommStateGetSoloDebugNo();
#endif
        MI_CpuCopy8(_pCommMP->mysteryData, pMist->mysteryData, MYSTERY_BEACON_DATA_SIZE);
    }
    DC_FlushRange(_pCommMP->gameInfoBuff, _BEACON_SIZE_MAX);
    WH_SetUserGameInfo(_pCommMP->gameInfoBuff, _BEACON_SIZE_MAX);
}


//==============================================================================
/**
 *  ���[�U��`�̐e�@���� �l���������Ď�����ɍX�V����
 *  _GF_BSS_DATA_INFO�\���̂̒��g�𑗂�܂�
 *  @param   none
 *  @retval  none
 */
//==============================================================================
static void _funcBconDataChange( void )
{
    _GF_BSS_DATA_INFO* pGF = (_GF_BSS_DATA_INFO*)_pCommMP->gameInfoBuff;

    if(_connectNum() != pGF->connectNum){
        pGF->connectNum = _connectNum();
        DC_FlushRange(_pCommMP->gameInfoBuff, _BEACON_SIZE_MAX);
        WH_SetUserGameInfo(_pCommMP->gameInfoBuff, _BEACON_SIZE_MAX);
        WHSetGameInfo(_pCommMP->gameInfoBuff, _BEACON_SIZE_MAX,
                      _pCommMP->ggid,_sTgid);
    }
}

//==============================================================================
/**
 * �ʐM���C�u�����[�����̏�Ԃ����āA����������֐�
 * VBlank�Ƃ͊֌W�Ȃ��̂�process�̎��ɏ�������΂���
 * @param   none
 * @retval  none
 */
//==============================================================================
static void _stateProcess(u16 bitmap)
{
    int state = WH_GetSystemState();
    CommInfoFunc();
    _funcBconDataChange();      // �r�[�R���̒��g������������
    if((WH_GetCurrentAid() == COMM_PARENT_ID) && (!CommMPIsChildsConnecting())){
        if(_pCommMP->bErrorNoChild){
            _pCommMP->bErrorState = TRUE;   ///< �G���[�������N�����Ă���ꍇ���̏�Ԃ������܂�
//            OHNO_PRINT("�G���[�� NOCHILD \n");
        }
    }
    if(_pCommMP->errCheckBitmap == _NOT_INIT_BITMAP){
        _pCommMP->errCheckBitmap = bitmap;  // ���̂Ƃ��̐ڑ��l����ێ�
    }
    if(_pCommMP->bErrorDisconnectOther){ // �G���[�������s��
        if(_pCommMP->errCheckBitmap > bitmap){  // �ؒf�����ꍇ�K������������ �����镪�ɂ�OK
            _pCommMP->bErrorState = TRUE;   ///< �G���[�������N�����Ă���ꍇ���̏�Ԃ������܂�
//            OHNO_PRINT("�G���[�� �N�������� \n");
        }
    }
    if(WH_ERRCODE_FATAL == WH_GetLastError()){
        CommFatalErrorFunc(0);  // ���荞�ݒ��ɉ�ʕ\�����ł��Ȃ��̂ňړ�
    }
    switch (state) {
      case WH_SYSSTATE_STOP:
        if(_pCommMP->disconnectType == _DISCONNECT_END){
            OHNO_SP_PRINT("WHEnd ���Ă�ŏI�����܂���\n");
            _commEnd();  // ���[�N���牽����S�ĊJ��
            return;
        }
        if(_pCommMP->disconnectType == _DISCONNECT_SECRET){
            OHNO_SP_PRINT("WHEnd ���Ă�Ŏ��񂾂ӂ�J�n\n");
            _pCommMP->disconnectType = _DISCONNECT_STEALTH;
            return;
        }
        break;
      case WH_SYSSTATE_IDLE:
        if(_pCommMP->disconnectType == _DISCONNECT_END){
            if(WH_End()){
                return;
            }
        }
        if(_pCommMP->disconnectType == _DISCONNECT_SECRET){
            if(WH_End()){
                return;
            }
        }
        break;
      case WH_SYSSTATE_CONNECT_FAIL:
      case WH_SYSSTATE_ERROR:
        OHNO_PRINT("�G���[�� %d \n",WH_GetLastError());
        if(_pCommMP){
            _pCommMP->bErrorState = TRUE;   ///< �G���[�������N�����Ă���ꍇ���̏�Ԃ������܂�
        }
        break;
      case WH_SYSSTATE_MEASURECHANNEL:
        {
            u16 channel;
            // ���p�\�Ȓ������Ԏg�p���̒Ⴂ�`�����l����Ԃ��܂��B
            channel = WH_GetMeasureChannel();  //WH_SYSSTATE_MEASURECHANNEL => WH_SYSSTATE_IDLE
            if(_pCommMP->keepChannelTime==0){
                _pCommMP->keepChannelNo = channel;
                _pCommMP->keepChannelTime = _KEEP_CHANNEL_TIME_MAX;
            }
            else{
                _pCommMP->keepChannelTime--;
            }
            channel = _pCommMP->keepChannelNo;  
            if(_pCommMP->bTGIDChange){
                _sTgid++;
            }
            _setUserGameInfo();
//            OHNO_PRINT("�e�@�ڑ��J�n   tgid=%d channel=%d \n",_sTgid, channel);
            (void)WH_ParentConnect(WH_CONNECTMODE_MP_PARENT,
                                   _sTgid, channel,
                                   CommLocalGetServiceMaxEntry(CommStateGetServiceNo()),
                                   _getServiceBeaconPeriod(CommStateGetServiceNo()),
                                   _pCommMP->bEntry);
            _pCommMP->channel = channel;
        }
        break;
      default:
        break;
    }

}

//==============================================================================
/**
 * �ʐM���C�u�����[�����̏�Ԃ����āA����������֐�
 * VBlank�Ƃ͊֌W�Ȃ��̂�process�̎��ɏ�������΂���
 * �q�@�͂��݂��̐ڑ����킩��Ȃ��̂ŁA�ʐM���ʂ�commsystem���������ăG���[��������
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommMpProcess(u16 bitmap)
{
    if(_pCommMP){
        _stateProcess(bitmap);
    }
}

//==============================================================================
/**
 * �ʐM�\��ԂȂ̂��ǂ�����Ԃ�
 * @param   �e�q�@��netID
 * @retval  TRUE  �ʐM�\    FALSE �ʐM�ؒf
 */
//==============================================================================
static BOOL _isConnect(u16 netID)
{
    if(!_pCommMP){
        return FALSE;
    }
    if (WH_GetSystemState() != WH_SYSSTATE_CONNECTED) {
        return FALSE;
    }
    {
        u16 bitmap = WH_GetBitmap();
        if( bitmap & (1<<netID)){
            return TRUE;
        }
    }
    return FALSE;
}

//==============================================================================
/**
 * �ʐM�\��Ԃ̐l����Ԃ�
 * @param   none
 * @retval  �ڑ��l��
 */
//==============================================================================
static int _connectNum(void)
{
    int num = 0,i;

    for(i = 0; i < COMM_MACHINE_MAX; i++){
        if(_isConnect(i)){
            num++;
        }
    }
    return num;
}

//==============================================================================
/**
 * �ʐM�ؒf���[�h�ɂ͂��������ǂ���
 * @param   none
 * @retval  �ڑ��l��
 */
//==============================================================================

BOOL CommMPIsConnectStalth(void)
{
    if(_pCommMP && (_pCommMP->disconnectType == _DISCONNECT_STEALTH)){
        return TRUE;
    }
    return FALSE;
}

//==============================================================================
/**
 * ���������Ă��邩�ǂ�����Ԃ�
 * @param   none
 * @retval  �������I����Ă�����TRUE
 */
//==============================================================================
BOOL CommMPIsInitialize(void)
{
    return (_pCommMP!=NULL);
}

//==============================================================================
/**
 * WH���C�u�����Ł@��Ԃ�IDLE�ɂȂ��Ă��邩�m�F����
 * @param   none
 * @retval  IDLE�ɂȂ��Ă���=TRUE
 */
//==============================================================================

BOOL CommMPIsStateIdle(void)
{
    if(_pCommMP){
        return WH_IsSysStateIdle();
    }
    return TRUE;
}


//==============================================================================
/**
 * WH���C�u�����Ł@�ʐM��Ԃ�BIT���m�F  �q�@���Ȃ����Ă��邩�ǂ���
 * @param   none
 * @retval  �Ȃ�������TRUE
 */
//==============================================================================

BOOL CommMPIsChildsConnecting(void)
{
    if(_pCommMP){
        return( WH_GetBitmap() & 0xfffe);
    }
    return FALSE;
}

//==============================================================================
/**
 * �e�@�����������ǂ���
 * @param   none
 * @retval  �������ꍇTRUE
 */
//==============================================================================

BOOL CommMPParentDisconnect(void)
{
    if(CommMPIsError() && ( WH_ERRCODE_DISCONNECTED == WH_GetLastError())){
        return TRUE;
    }
    return FALSE;
}


//==============================================================================
/**
 * �G���[��Ԃ��ǂ���
 * @param   none
 * @retval  �G���[�̎�TRUE
 */
//==============================================================================

BOOL CommMPIsError(void)
{
    if(_pCommMP){
        if(_pCommMP->bErrorState){
            return TRUE;
        }
    }
    return FALSE;
}

//==============================================================================
/**
 * �q�@�����Ȃ��̂��G���[�����ɂ��邩�ǂ�����SET
 * @param   bOn  �L������TRUE
 * @retval  none
 */
//==============================================================================

void CommMPSetNoChildError(BOOL bOn)
{
    if(_pCommMP){
        _pCommMP->bErrorNoChild = bOn;
    }
}

//==============================================================================
/**
 * �N�����������̂��G���[�����ɂ��邩�ǂ�����SET
 * @param   bOn  �L������TRUE
 * @retval  none
 */
//==============================================================================

void CommMPSetDisconnectOtherError(BOOL bOn)
{
    if(_pCommMP){
        _pCommMP->bErrorDisconnectOther = bOn;
        _pCommMP->errCheckBitmap = _NOT_INIT_BITMAP;
    }
}

//==============================================================================
/**
 * �T�[�r�X�ԍ��ɑΉ������r�[�R���Ԋu�𓾂܂�
 * �T�[�r�X�ԍ��� include/communication/comm_def.h�ɂ���܂�
 * @param   serviceNo �T�[�r�X�ԍ�
 * @retval  beacon�Ԋu msec
 */
//==============================================================================

u16 _getServiceBeaconPeriod(u16 serviceNo)
{
    u16 beaconPeriod = WM_GetDispersionBeaconPeriod();
    GF_ASSERT_RETURN(serviceNo < COMM_MODE_MAX, beaconPeriod);

    if(COMM_MODE_UNDERGROUND == serviceNo){
        return beaconPeriod/4;
    }
    if((COMM_MODE_UNION == serviceNo) ||
       (COMM_MODE_PICTURE == serviceNo)){
        return (beaconPeriod / 4);
    }
    return beaconPeriod;
}

//==============================================================================
/**
 * �r�[�R���f�[�^�𓾂�
 * @param   index �r�[�R���o�b�t�@�ɑ΂���index
 * @retval   WMBssDesc*  �r�[�R���o�b�t�@�|�C���^
 */
//==============================================================================

WMBssDesc* CommMPGetWMBssDesc(int index)
{
    if(_pCommMP && (_pCommMP->bconUnCatchTime[index]!=0)){
        return &_pCommMP->sBssDesc[index];
    }
    return NULL;
}

//==============================================================================
/**
 * GF�r�[�R���f�[�^�𓾂�
 * @param   index �r�[�R���o�b�t�@�ɑ΂���index
 * @retval   GF_BSS_DATA_INFO*  �r�[�R���o�b�t�@�|�C���^
 */
//==============================================================================

_GF_BSS_DATA_INFO* CommMPGetGFBss(int index)
{
    if(_pCommMP && (_pCommMP->bconUnCatchTime[index]!=0)){
        return (_GF_BSS_DATA_INFO*)_pCommMP->sBssDesc[index].gameInfo.userGameInfo;
    }
    return NULL;
}

//==============================================================================
/**
 * �r�[�R���f�[�^������
 * @param    index �r�[�R���o�b�t�@�ɑ΂���index
 * @retval   none
 */
//==============================================================================

void CommMPResetWMBssDesc(int index)
{
    if(_pCommMP && (_pCommMP->bconUnCatchTime[index]!=0)){
        _pCommMP->bconUnCatchTime[index] = 0;
    }
}

//==============================================================================
/**
 * �r�[�R���f�[�^������
 * @param    index �r�[�R���o�b�t�@�ɑ΂���index
 * @retval   none
 */
//==============================================================================

void CommMPResetGFBss(int index)
{
    if(_pCommMP && (_pCommMP->bconUnCatchTime[index]!=0)){
        _pCommMP->bconUnCatchTime[index] = 0;
    }
}

//==============================================================================
/**
 * �ʐM�p�Ɏ�����MYSTATUS�𓾂�
 * @param    none
 * @retval   MYSTATUS*
 */
//==============================================================================

MYSTATUS* CommMPGetMyStatus(void)
{
    return _pCommMP->pMyStatus;
}

//==============================================================================
/**
 * BCON���Ɋ܂܂��MYSTATUS��Ԃ�
 * @param   index   �e�̃��X�g��index
 * @retval  MYSTATUS*
 */
//==============================================================================

MYSTATUS* CommMPGetBconMyStatus(int index)
{
    MYSTATUS* pMyStatus;
    _GF_BSS_DATA_INFO* pGF;
    
    if(_pCommMP->bconUnCatchTime[index] == 0){
        return NULL;
    }
    pGF = (_GF_BSS_DATA_INFO*)_pCommMP->sBssDesc[index].gameInfo.userGameInfo;
    pMyStatus = (MYSTATUS*)&pGF->myStatusBuff[0];
    return pMyStatus;
}

//==============================================================================
/**
 * mac�A�h���X���o�b�N�A�b�v����
 * @param   pMac   mac address
 * @retval  none
 */
//==============================================================================

void CommMPSetBackupMacAddress(u8* pMac, int netID)
{
    if(_pCommMP){
        GF_ASSERT_RETURN(netID < COMM_MACHINE_MAX,);
        MI_CpuCopy8(pMac, _pCommMP->backupBssid[netID], WM_SIZE_BSSID);
    }
}

//==============================================================================
/**
 * �o�b�N�A�b�v����MAC�A�h���X�ɊY�����邩�ǂ����𓾂�
 * @param   pMac   mac address
 * @retval  none
 */
//==============================================================================

static BOOL _isMachBackupMacAddress(u8* pMac)
{
    int i;
    
    for(i = 0; i < COMM_MACHINE_MAX; i++){
        if(WM_IsBssidEqual(_pCommMP->backupBssid[i], pMac)){
            return TRUE;
        }
    }
    return FALSE;
}


//==============================================================================
/**
 * �����ؒf���[�h�ɓ��������ǂ�����Ԃ�
 * @param   none
 * @retval  �����Ă���Ȃ��TRUE
 */
//==============================================================================

BOOL CommMPIsAutoExit(void)
{
    if(_pCommMP){
        return _pCommMP->bAutoExit;
    }
    return FALSE;
}

//==============================================================================
/**
 * �����ؒf���[�hON
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommMPSetAutoExit(void)
{
    if(_pCommMP){
        _pCommMP->bAutoExit = TRUE;
    }
}

//==============================================================================
/**
 * ������BCON��PMS�f�[�^������������ ���̊֐���CommMPFlashMyBss���ĂԂ��ƂŔ��f�����
 * @param   PMS_DATA
 * @retval  none
 */
//==============================================================================

void CommMPSetMyPMS(PMS_DATA* pPMS)
{
    MI_CpuCopy8( pPMS, &_pCommMP->pmsData, sizeof(PMS_DATA));
}


//==============================================================================
/**
 * ������BCON�̃��M�����[�V�����f�[�^������������ ���̊֐���CommMPFlashMyBss���ĂԂ��ƂŔ��f�����
 * @param   pRegulation  ���M�����[�V�����f�[�^�\���̂̃|�C���^
 * @retval  none
 */
//==============================================================================

void CommMPSetMyRegulation(void* pRegulation)
{

    MI_CpuCopy8( pRegulation,_pCommMP->pRegulation, Regulation_GetWorkSize());
}

//==============================================================================
/**
 * �r�[�R���f�[�^�Ɍ��݂̏󋵂𔽉f������
 * @param   none
 * @retval  none
 */
//==============================================================================

void CommMPFlashMyBss(void)
{
    _setUserGameInfo();
    WHSetGameInfo(_pCommMP->gameInfoBuff, _BEACON_SIZE_MAX,
                  _pCommMP->ggid,_sTgid);
}

//==============================================================================
/**
 * ���C�t�^�C�������������� �܂��͌��ɖ߂�
 * @param   bMinimum TRUE�Ȃ珬��������
 * @retval  none
 */
//==============================================================================

void CommMPSetLifeTime(BOOL bMinimum)
{
    WHSetLifeTime(bMinimum);
}

//------------------------------------------------------
/**
 * @brief   �T�[�r�X�ԍ��̃r�[�R������Ԃ��܂�
 * @param   serviceNo   comm_def.h�ɂ���T�[�r�X�ԍ�
 * @retval  ���p�Ґ�
 */
//------------------------------------------------------

int CommMPGetServiceNumber(int serviceNo)
{
    int i,num=0;
    
    for (i = 0; i < SCAN_PARENT_COUNT_MAX; i++) {
        _GF_BSS_DATA_INFO* pGF = CommMPGetGFBss(i);
        if(pGF){
            if( pGF->serviceNo == serviceNo){
                num += pGF->connectNum;
            }
        }
    }
    //
    return num;
}

//------------------------------------------------------
/**
 * @brief   �e�@�����ł��r�[�R���𑗐M���I��������ǂ���
 * @param   none
 * @retval  ���M����=TRUE
 */
//------------------------------------------------------

BOOL CommMPIsParentBeaconSent(void)
{
    return HWIsParentBeaconSent();
}

//------------------------------------------------------
/**
 * @brief   �X�L������Ԃ��ǂ���
 * @param   none
 * @retval  ���M����=TRUE
 */
//------------------------------------------------------

BOOL CommMPIsChildStateScan(void)
{
    return WH_IsSysStateScan();
}

//------------------------------------------------------
/**
 * @brief   �r�[�R���f�[�^�Ɏ��R�Ƀf�[�^���ڂ��܂�
 * @param   pData   �f�[�^   COMM_SEND_REGULATION_SIZE�܂ł̂�����܂�
 * @retval  none
 */
//------------------------------------------------------

void CommMPSetBeaconTempData(void* pData)
{
    MI_CpuCopy8(pData,_pCommMP->mysteryData,MYSTERY_BEACON_DATA_SIZE);
    CommMPFlashMyBss();
}

//------------------------------------------------------
/**
 * @brief   �r�[�R���f�[�^����f�[�^�������o���܂�
 * @param   index     ���Ԗڂ̃r�[�R���Ȃ̂�
 * @retval  �f�[�^�|�C���^
 */
//------------------------------------------------------

const void* CommMPGetBeaconTempData(int index)
{
    if(_pCommMP && (_pCommMP->bconUnCatchTime[index]!=0)){
        _GF_BSS_MYSTERY* pMyst;
        pMyst = (_GF_BSS_MYSTERY*)_pCommMP->sBssDesc[index].gameInfo.userGameInfo;
        return pMyst->mysteryData;
    }
    return NULL;
}

//------------------------------------------------------
/**
 * @brief   �`�����l����Ԃ�
 * @retval  �ڑ��`�����l��
 */
//------------------------------------------------------

int CommMPGetChannel(void)
{
    return _pCommMP->channel;
}

//==============================================================================
/**
 * @brief	���@�r�[�R�����M���e�̎擾
 */
//==============================================================================
void * CommMPGetMyGFBss(void)
{
	if (_pCommMP == NULL) {
		return NULL;
	}
	return _pCommMP->gameInfoBuff;
}

//------------------------------------------------------
/**
 * @brief	�r�[�R�����E���Ă���̃J�E���g�_�E���^�C�}�擾
 * @param	index	�ʒu
 */
//------------------------------------------------------
int CommMPGetBConUncacheTime(int index)
{
	if (_pCommMP == NULL) {
		return 0;
	}
	return _pCommMP->bconUnCatchTime[index];
}

