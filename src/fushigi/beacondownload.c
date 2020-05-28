/**
 * @version "$Id: beacondownload.c,v 1.3 2006/08/09 09:29:51 mitsuhara Exp $"
 *
 * @file beacondownload.cpp
 * @brief �r�[�R�����g�p�����f�[�^�_�E�����[�h����
 * 
 */
 
 
#include <nitro.h>
#include <nitro/wm.h>
#include <nitro/cht.h>
#include "beacondownload.h"
#include "nitrocrypto/crypto.h"

/* ======================================================================
   ����M����f�[�^�̃Q�[���f�[�^�\����
   ====================================================================== */  
#define BSDOWN_ONEPACKET_SIZE (WM_SIZE_USER_GAMEINFO - 8)
#define BSDOWN_PACKET_MAXSIZE ((BSOWN_MAXSIZE - 1) / BSDOWN_ONEPACKET_SIZE + 1)
typedef struct
{
	u16 crc;							// ���M����X�N���v�g��CRC
	u16 index;							// ���̃r�[�R���̒ʂ��ԍ�
	u32 size;							// ���낤�Ƃ��Ă���X�N���v�g�̑傫��
	u8 data[BSDOWN_ONEPACKET_SIZE];	// �f�[�^�{�́i�P�O�S�o�C�g�j
} BSDOWN_GAMEINFO_STRUCT;

/* ======================================================================
  ��Ɨ̈�̃f�[�^�\����
   ====================================================================== */
typedef struct
{
	/* WM �p�V�X�e�����[�N�̈�o�b�t�@ */
	u8  WmBuffer[ WM_SYSTEM_BUF_SIZE ] ATTRIBUTE_ALIGN(32);
	WMBssDesc BssDesc ATTRIBUTE_ALIGN(32);	
	WMScanParam ScanParam ATTRIBUTE_ALIGN(32);
	u8 fileinfo[BSDOWN_ONEPACKET_SIZE];
	int infoflag;
	CRYPTORC4Context rc4context;
	int SysState;
	// �G���[�R�[�h�i�[�p
	int ErrCode;	
	
	u16 state;	  // ���݂̏�
	u16 crc;	  // ���ݎ�M���̃f�[�^��CRC�i���ʂɗ��p�j
	u16 packets;  // ���ݎ�M���̃f�[�^�́A����������đ����Ă��邩
	u16 received; // ���݉��̃p�P�b�g���󂯎������
	u32 size;	  // ���ݎ�M���̃f�[�^�̃T�C�Y
	u32 count;
	int index;	  // ��ԍŌ�Ɏ󂯎�����p�P�b�g�̒ʂ��ԍ��i�e�@�����A�ǂ̂�����𑗐M���Ă��邩�𔻒f���邽�߁j
	int linklevel;
	u8 macaddress[6];
	u16 channel;
	u8 *target;	  // �X�N���v�g��ۑ������B�S�o�C�g�A���C�����g����Ă���K�v������܂��B
	BSDOWN_CALLBACK callback;
	u8 flags[ BSDOWN_PACKET_MAXSIZE ];	// �ǂ̃p�P�b�g�������ė��邩�B
} BSDOWN_WORK;

enum
{
	BSDOWNSTATE_STOP,			// �������
	BSDOWNSTATE_STARTSCAN,		// �X�L�������J�n���悤�Ƃ��Ă���Ƃ���
	BSDOWNSTATE_SCANNING,		// �X�L�������i�r�[�R����M�O�j
	BSDOWNSTATE_RECEVING,		// ���ł��r�[�R�����󂯎�������Ƃ�������
	BSDOWNSTATE_COMPLETE,		// ��M����
	
	BSDOWNSTATE_SIZE	
};

/* ======================================================================
   static contents
   ====================================================================== */

enum 
{
    mywh_SYSSTATE_STOP,           // �������
    mywh_SYSSTATE_IDLE,           // �ҋ@��
    mywh_SYSSTATE_SCANNING,       // �X�L������
    mywh_SYSSTATE_BUSY,           // �ڑ���ƒ�
    mywh_SYSSTATE_CONNECTED,      // �ڑ������i���̏�ԂŒʐM�\�j
    mywh_SYSSTATE_DATASHARING,    // data-sharing�L���Őڑ�����
    mywh_SYSSTATE_KEYSHARING,     // key-sharing�L���Őڑ�����
    mywh_SYSSTATE_MEASURECHANNEL, // �`�����l���̓d�g�g�p�����`�F�b�N
    mywh_SYSSTATE_CONNECT_FAIL,   // �e�@�ւ̐ڑ����s
    mywh_SYSSTATE_ERROR,          // �G���[����
    mywh_SYSSTATE_FATAL,          // FATAL�G���[����
    mywh_SYSSTATE_NUM
};

enum 
{
    mywh_CONNECTMODE_MP_PARENT,  // �e�@ MP �ڑ����[�h
    mywh_CONNECTMODE_MP_CHILD,   // �q�@ MP �ڑ����[�h
    mywh_CONNECTMODE_KS_PARENT,  // �e�@ key-sharing �ڑ����[�h
    mywh_CONNECTMODE_KS_CHILD,   // �q�@ key-sharing �ڑ����[�h
    mywh_CONNECTMODE_DS_PARENT,  // �e�@ data-sharing �ڑ����[�h
    mywh_CONNECTMODE_DS_CHILD,   // �q�@ data-sharing �ڑ����[�h
    mywh_CONNECTMODE_NUM
};

enum {
    // ���O�̃G���[�R�[�h
    mywh_ERRCODE_DISCONNECTED      = WM_ERRCODE_MAX, // �e����ؒf���ꂽ
    mywh_ERRCODE_PARENT_NOT_FOUND,                   // �e�����Ȃ�
    mywh_ERRCODE_NO_RADIO,                           // �����g�p�s��
    mywh_ERRCODE_LOST_PARENT,                        // �e����������
    mywh_ERRCODE_NOMORE_CHANNEL,                     // ���ׂẴ`�����l���̒������I����
    mywh_ERRCODE_MAX
};
#define mywh_DMA_NO                 2
typedef void (*WHStartScanCallbackFunc)( WMBssDesc* bssDesc );

static BSDOWN_WORK *s_work_ptr;   
#define s_work (*s_work_ptr)
//static BSDOWN_WORK s_work;   







// �͂��߂ăf�[�^���󂯂Ƃ����Ƃ��B
static void bsdown_c_startdownload( BSDOWN_GAMEINFO_STRUCT *info );
// ��M�X�e�b�v�B
static int bsdown_c_step( BSDOWN_GAMEINFO_STRUCT *info );

/* �f�o�b�O�o�̓t�b�N�֐� */
static void (*wh_trace)(const char *, ...) =
#if !defined(SDK_FINALROM)
    OS_TPrintf;
#else
    NULL;
#endif


/* ======================================================================
   state functions
   ====================================================================== */


#define mywh_MAX(a, b) ( ((a) > (b)) ? (a) : (b) )

/* �s����Ȓʒm���󂯎��֐� */
static void mywh_IndicateHandler( void* arg );

/* (stateless) -> READY -> STOP -> IDLE */
static BOOL mywh_StateInInitialize(void);

static void mywh_StateOutInitialize(void *arg);


/* IDLE -> SCAN */
static BOOL mywh_StateInStartScan(void);
static void mywh_StateOutStartScan(void *arg);

/* SCAN -> IDLE */
static BOOL mywh_StateInEndScan(void);
static void mywh_StateOutEndScan(void *arg);

/* IDLE -> STOP -> READY -> (stateless) */
static BOOL mywh_StateInPowerOff(void);
static void mywh_StateOutPowerOff(void *arg);
static BOOL mywh_StateInDisable(void);
static void mywh_StateOutDisable(void *arg);
static void mywh_StateOutEnd( void *arg );

/* X -> IDLE */
static BOOL mywh_StateInReset(void);
static void mywh_StateOutReset(void *arg);


/* ======================================================================
   debug codes
   ====================================================================== */
#define WMHIGH_DEBUG

#if defined(WMHIGH_DEBUG)

#define WH_TRACE    if(wh_trace) wh_trace

#define WH_TRACE_STATE OS_TPrintf("%s s_work.SysState = %d\n", __func__, s_work.SysState)

#define mywh_REPORT_FAILURE(result)                \
    do{ OS_TPrintf("Failed in %s, %s = %s\n",      \
                  __func__,                      \
                  #result,                       \
                  mywh_GetWMErrCodeName(result));  \
        mywh_SetError(result); }while(0)

#define mywh_ASSERT(exp) \
    (void) ((exp) || (OSi_Panic(__FILE__, __LINE__, "Failed assertion " #exp), 0))

#else /* defined(WMHIGH_DEBUG) */

#define WH_TRACE_STATE              /* */
#define WH_TRACE(...)               ((void)0)
#define mywh_REPORT_FAILURE(result)   mywh_SetError(result)
#define mywh_ASSERT(exp)              ((void) 0)

#endif



#if defined(WMHIGH_DEBUG)
static const char *sStateNames[] = {
    "WM_STATE_READY",
    "WM_STATE_STOP",
    "WM_STATE_IDLE",
    "WM_STATE_CLASS1",
    "WM_STATE_TESTMODE",
    "WM_STATE_SCAN",
    "WM_STATE_CONNECT",
    "WM_STATE_PARENT",
    "WM_STATE_CHILD",
    "WM_STATE_MP_PARENT",
    "WM_STATE_MP_CHILD",
    "WM_STATE_DCF_CHILD",
};

static const char *mywh_GetWMErrCodeName(int result)
{
    static const char *errnames[] = {
        "WM_ERRCODE_SUCCESS",
        "WM_ERRCODE_FAILED",
        "WM_ERRCODE_OPERATING",
        "WM_ERRCODE_ILLEGAL_STATE",
        "WM_ERRCODE_WM_DISABLE",
        "WM_ERRCODE_NO_DATASET",
        "WM_ERRCODE_INVALID_PARAM",
        "WM_ERRCODE_NO_CHILD",
        "WM_ERRCODE_FIFO_ERROR",
        "WM_ERRCODE_TIMEOUT",
        "WM_ERRCODE_SEND_QUEUE_FULL",
        "WM_ERRCODE_NO_ENTRY",
        "WM_ERRCODE_OVER_MAX_ENTRY",
        "WM_ERRCODE_INVALID_POLLBITMAP",
        "WM_ERRCODE_NO_DATA",
        "WM_ERRCODE_SEND_FAILED",
        "WM_ERRCODE_DCF_TEST" ,
        "WM_ERRCODE_WL_INVALID_PARAM" ,
        "WM_ERRCODE_WL_LENGTH_ERR" ,
        "WM_ERRCODE_FLASH_ERROR" ,
        
        "mywh_ERRCODE_DISCONNECTED",
        "mywh_ERRCODE_PARENT_NOT_FOUND",
        "mywh_ERRCODE_NO_RADIO",
    };

    if ( 0 <= result && result < sizeof(errnames) / sizeof(char*) )
    {
        return errnames[result];
    }
    else
    {
        return "N/A";
    }
}

static const char *mywh_GetWMStateCodeName(u16 code)
{
    static const char *statenames[] = {
        "WM_STATECODE_PARENT_START",
        "N/A",
        "WM_STATECODE_BEACON_SENT",
        "WM_STATECODE_SCAN_START",
        "WM_STATECODE_PARENT_NOT_FOUND",
        "WM_STATECODE_PARENT_FOUND",
        "WM_STATECODE_CONNECT_START",
        "WM_STATECODE_CONNECTED",
        "WM_STATECODE_BEACON_LOST",
        "WM_STATECODE_DISCONNECTED",
        "WM_STATECODE_MP_START",
        "WM_STATECODE_MPEND_IND",
        "WM_STATECODE_MP_IND",
        "WM_STATECODE_MPACK_IND",
        "WM_STATECODE_DCF_START",
        "WM_STATECODE_DCF_IND",
        "WM_STATECODE_BEACON_RECV",
        "WM_STATECODE_DISASSOCIATE",
        "WM_STATECODE_REASSOCIATE",
        "WM_STATECODE_AUTHENTICATE",
        "WM_STATECODE_PORT_SEND",
        "WM_STATECODE_PORT_RECV",
        "WM_STATECODE_FIFO_ERROR",
    };

    if ( 0 <= code && code < sizeof(statenames) / sizeof(char*) )
    {
        return statenames[code];
    }
    else
    {
        return "N/A";
    }
}

static const char *mywh_GetWMApiidName(u16 apiid)
{
    static const char *apinames[] = {
        "WM_APIID_INITIALIZE",
        "WM_APIID_RESET",
        "WM_APIID_END",

        "WM_APIID_ENABLE",
        "WM_APIID_DISABLE",
        "WM_APIID_POWER_ON",
        "WM_APIID_POWER_OFF",

        "WM_APIID_SET_P_PARAM",
        "WM_APIID_START_PARENT",
        "WM_APIID_END_PARENT",
        "WM_APIID_START_SCAN",
        "WM_APIID_END_SCAN",
        "WM_APIID_START_CONNECT",
        "WM_APIID_DISCONNECT",
        "WM_APIID_START_MP",
        "WM_APIID_SET_MP_DATA",
        "WM_APIID_END_MP",
        "WM_APIID_START_DCF",
        "WM_APIID_SET_DCF_DATA",
        "WM_APIID_END_DCF",
        "WM_APIID_SET_WEPKEY",
        "WM_APIID_START_KS",
        "WM_APIID_END_KS",
        "WM_APIID_GET_KEYSET",
        "WM_APIID_SET_GAMEINFO",
        "WM_APIID_SET_BEACON_IND",
        "WM_APIID_START_TESTMODE",
        "WM_APIID_STOP_TESTMODE",
        "WM_APIID_VALARM_MP",
        "WM_APIID_SET_LIFETIME",
        "WM_APIID_MEASURE_CHANNEL",
        "WM_APIID_INIT_W_COUNTER",
        "WM_APIID_GET_W_COUNTER",
        "WM_APIID_SET_ENTRY",
        "WM_APIID_AUTO_DEAUTH",
        "WM_APIID_SET_MP_FREQ",
        "WM_APIID_SET_BEACON_PERIOD",
        "WM_APIID_AUTO_DISCONNECT",

        "WM_APIID_KICK_MP_PARENT",
        "WM_APIID_KICK_MP_CHILD",
        "WM_APIID_KICK_MP_RESUME",
    };
    static const char *apinames_indicates[] = {
        "WM_APIID_INDICATION",
        "WM_APIID_PORT_SEND",
        "WM_APIID_PORT_RECV",
        "WM_APIID_READ_STATUS"
        };
    static const char *apiname_unknown =
        "WM_APIID_UNKNOWN";

    if ( 0 <= apiid && apiid < sizeof(apinames) / sizeof(char*) )
    {
        return apinames[apiid];
    }
    else if ( WM_APIID_INDICATION <= apiid &&
              apiid < WM_APIID_INDICATION + sizeof(apinames_indicates) / sizeof(char*) )
    {
        return apinames_indicates[apiid - WM_APIID_INDICATION];
    }
    else if ( apiid == WM_APIID_UNKNOWN )
    {
        return apiname_unknown;
    }
    else
    {
        return "N/A";
    }
}

static void mywh_ChangeSysState(int state)
{
    static const char *statenames[] = {
        "mywh_SYSSTATE_STOP",
        "mywh_SYSSTATE_IDLE",
        "mywh_SYSSTATE_SCANNING",
        "mywh_SYSSTATE_BUSY",
        "mywh_SYSSTATE_CONNECTED",
        "mywh_SYSSTATE_DATASHARING",
        "mywh_SYSSTATE_KEYSHARING",
        "mywh_SYSSTATE_MEASURECHANNEL",
        "mywh_SYSSTATE_CONNECT_FAIL",
        "mywh_SYSSTATE_ERROR",
    };
    
    WH_TRACE("%s -> ", statenames[s_work.SysState]);
    s_work.SysState = state;
    WH_TRACE("%s\n", statenames[s_work.SysState]);
}

#else

#define mywh_GetWMErrCodeName(result)    ("")
#define mywh_GetWMStateCodeName(result)  ("")
#define mywh_GetWMApiidName(result)      ("")

static void mywh_ChangeSysState(int state)
{
    s_work.SysState = state;
}

#endif

static void mywh_SetError(int code)
{
    // ���ɃV�X�e���� ERROR ��ԂɂȂ��Ă���ꍇ�́A�㏑�����Ȃ��B
    if ( s_work.SysState == mywh_SYSSTATE_ERROR ||
         s_work.SysState == mywh_SYSSTATE_FATAL )
    {
        return;
    }

    s_work.ErrCode = code;
}


/*---------------------------------------------------------------------------*
  Name:         mywh_StartScan

  Description:  �e�@�̃r�[�R�����擾����֐�

  Arguments:    callback - �e�@�������ɕԂ��R�[���o�b�N��ݒ肷��B
  
  Returns:      None.
 *---------------------------------------------------------------------------*/
static BOOL mywh_StartScan( void )
{
    WH_TRACE_STATE;
    mywh_ASSERT( s_work.SysState != mywh_SYSSTATE_CONNECTED );
    
    mywh_ChangeSysState( mywh_SYSSTATE_SCANNING );
    // ��������MAC�A�h���X�̏�����ݒ�
    *(u16*)(&(s_work.ScanParam).bssid[4]) = 0xffff;
    *(u16*)(&(s_work.ScanParam).bssid[2]) = 0xffff;
    *(u16*)(&(s_work.ScanParam).bssid[0]) = 0xffff;
    
    if ( ! mywh_StateInStartScan() )
    {
        mywh_ChangeSysState( mywh_SYSSTATE_ERROR );
        if( s_work.callback != NULL ) s_work.callback( BSDOWNCALLBACK_ERROR );
        return FALSE;
    }
    
    s_work.state = BSDOWNSTATE_SCANNING;
    if( s_work.callback != NULL ) s_work.callback( BSDOWNCALLBACK_STARTSCAN );
    return TRUE;
}

/* ----------------------------------------------------------------------
  state : StartScan
  ---------------------------------------------------------------------- */
static BOOL mywh_StateInStartScan( void )
{
    // ���̏�Ԃ̎��A�e�@��T�����܂��B
    WMErrCode result;
    u16 chanpat;
    
    mywh_ASSERT( s_work.SysState == mywh_SYSSTATE_SCANNING );
    
    chanpat = WM_GetAllowedChannel();
    
    // �������g�p�\���ǂ������`�F�b�N����
    if ( chanpat == 0x8000 )
    {
        // 0x8000 ���Ԃ��Ă����ꍇ�́A����������������Ă��Ȃ��Ȃ�
        // �������C�u�����̏�Ԉُ��\���Ă���̂ŃG���[�ɂ��܂��B
        mywh_REPORT_FAILURE( WM_ERRCODE_ILLEGAL_STATE );
        return FALSE;
    }
    if ( chanpat == 0 )
    {
        // �������g���Ȃ���ԁB
        mywh_REPORT_FAILURE( mywh_ERRCODE_NO_RADIO );
        return FALSE;
    }
    
    if( s_work.channel >= 16 )
    {
    	// �e�@�����O�B�`�����l����ς��Č���
    	int next = s_work.channel - 16;
    	int i;
    	for( i = 0; i < 13; i++ )
    	{
    		next = (next + 1) % 13;    	
    		if( chanpat & (1 << next) ) break;
    	}
    	s_work.channel = (u16)(16 + next);
    	s_work.ScanParam.channel = (u16)(next + 1);
    }
    else 
    {
    	// �e�@������
    	s_work.ScanParam.channel = s_work.channel;    	
    }
    s_work.ScanParam.maxChannelTime = BSDOWN_SCANTIME;
    s_work.ScanParam.scanBuf = &(s_work.BssDesc);
    
    if( s_work.state == BSDOWNSTATE_RECEVING ) 
    {
	    // ��������MAC�A�h���X�̏�����ݒ�
	    int i;
	    for(i = 0; i < 6; i++) s_work.ScanParam.bssid[i] = s_work.macaddress[i];
    }
    
    result = WM_StartScan( mywh_StateOutStartScan, &(s_work.ScanParam) );
    
    if (result != WM_ERRCODE_OPERATING) 
    {
        mywh_REPORT_FAILURE(result);
        return FALSE;
    }
    return TRUE;
}


static void mywh_StateOutStartScan( void *arg )
{
    WMstartScanCallback* cb  = (WMstartScanCallback*)arg;
    
    // �X�L�����R�}���h�Ɏ��s�����ꍇ
    if ( cb->errcode != WM_ERRCODE_SUCCESS )
    {
        mywh_REPORT_FAILURE(cb->errcode);
        mywh_ChangeSysState( mywh_SYSSTATE_ERROR );
        if( s_work.callback != NULL ) s_work.callback( BSDOWNCALLBACK_ERROR );
        return;
    }

    if ( s_work.SysState != mywh_SYSSTATE_SCANNING )
    {
        // ��Ԃ��ύX����Ă���΃X�L�����I��
        if ( ! mywh_StateInEndScan() )
        {
            mywh_ChangeSysState( mywh_SYSSTATE_ERROR );
            if( s_work.callback != NULL ) s_work.callback( BSDOWNCALLBACK_ERROR );
        }
        return;
    }
    
//    OS_TPrintf( "WMstartScanCallback state = %d\n", cb->state );
    
    switch ( cb->state ) 
    {
    case WM_STATECODE_SCAN_START:
        return;
        
    case WM_STATECODE_PARENT_NOT_FOUND:
        break;
        
    case WM_STATECODE_PARENT_FOUND:
        // �e�@�����������ꍇ
        // GUIDELINE : �K�C�h���C�������|�C���g(6.3.5)
        // ggid ���r���A����Ă����玸�s�Ƃ��܂��B
        // �܂��AWMBssDesc.gameInfoLength ���m�F���A
        // ggid �ɗL���Ȓl�������Ă��邱�Ƃ��璲�ׂ�K�v������܂��B

        // BssDesc�̏��ARM7�����珑�����܂�Ă��邽��
        // �o�b�t�@�ɐݒ肳�ꂽBssDesc�̃L���b�V����j��
        DC_InvalidateRange( &(s_work.BssDesc), sizeof(WMbssDesc) );
               
        if ( cb->gameInfoLength < 8 || cb->gameInfo.ggid != BDOWN_GGID )
        {
            // GGID������Ă���Ζ�������
            WH_TRACE("not my parent ggid (%d != %d)\n",  cb->gameInfo.ggid, BDOWN_GGID );
            break;
        }
      
      	// �Ō�ɂ����Ƃ����d�g�̃����N���x���L��
      	s_work.linklevel = cb->linkLevel;
        
        if( s_work.state == BSDOWNSTATE_SCANNING ) 
        {
			// �͂��߂ăf�[�^���󂯂Ƃ����Ƃ��B
        	bsdown_c_startdownload( (BSDOWN_GAMEINFO_STRUCT *) &(cb->gameInfo.userGameInfo[0]) );
        	// ��������}�b�N�A�h���X���Œ�
        	{
        		int i;
        		for(i = 0; i < 6; i++ ) s_work.macaddress[i] = cb->macAddress[i];
        	}
        	// ��������`�����l�����Œ�
        	s_work.channel = (u16)(s_work.channel - 16 + 1);
        	if( s_work.callback != NULL ) s_work.callback( BSDOWNCALLBACK_START );
        }
        
        if( bsdown_c_step( (BSDOWN_GAMEINFO_STRUCT *) &(cb->gameInfo.userGameInfo[0]) ) )
        {
     		// ��M����   	
     		OS_TPrintf("Complete!");
        	s_work.state = BSDOWNSTATE_COMPLETE;
        	bsdown_end();
        	return;
        }

        break;
    }

    // �ăX�L�������J�n���܂��B
    if ( ! mywh_StateInStartScan() )
    {
        mywh_ChangeSysState( mywh_SYSSTATE_ERROR );
        if( s_work.callback != NULL ) s_work.callback( BSDOWNCALLBACK_ERROR );
    }
}

/* ----------------------------------------------------------------------
   state : EndScan
  ---------------------------------------------------------------------- */

/*---------------------------------------------------------------------------*
  Name:         mywh_EndScan

  Description:  �e�@�̃r�[�R�����擾����֐�

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
static BOOL mywh_EndScan( void )
{
    if ( s_work.SysState != mywh_SYSSTATE_SCANNING )
    {
        return FALSE;
    }
    
    mywh_ChangeSysState( mywh_SYSSTATE_BUSY );
    return TRUE;
}


static BOOL mywh_StateInEndScan(void)
{
    WMErrCode result;
    WH_TRACE_STATE;

    // ���̏�Ԃł́A�X�L�����̏I���������s���܂��B
    result = WM_EndScan( mywh_StateOutEndScan );
    if ( result != WM_ERRCODE_OPERATING )
    {
        mywh_REPORT_FAILURE(result);
        return FALSE;
    }
    
    return TRUE;
}

static void mywh_StateOutEndScan( void *arg )
{
    WMCallback* cb  = (WMCallback*)arg;
    WH_TRACE_STATE;
    
    if ( cb->errcode != WM_ERRCODE_SUCCESS )
    {
        mywh_REPORT_FAILURE( cb->errcode );
        return;
    }
    
    mywh_ChangeSysState( mywh_SYSSTATE_IDLE );
    
}

/* ----------------------------------------------------------------------
  state : Reset
  ---------------------------------------------------------------------- */
static BOOL mywh_StateInReset(void)
{
    // ���̏�Ԃ́A�e�@�q�@���ʂł��B
    // �V�X�e����������Ԃɖ߂��܂��B
    WMErrCode result;
    WH_TRACE_STATE;

    mywh_ChangeSysState( mywh_SYSSTATE_BUSY );
    result = WM_Reset( mywh_StateOutReset );
    if ( result != WM_ERRCODE_OPERATING )
    {
        mywh_REPORT_FAILURE(result);
        return FALSE;
    }
    return TRUE;
}

static void mywh_StateOutReset(void *arg)
{
    WMCallback* cb  = (WMCallback*)arg;
    WH_TRACE_STATE;
    if ( cb->errcode != WM_ERRCODE_SUCCESS )
    {
        mywh_ChangeSysState( mywh_SYSSTATE_ERROR );
        mywh_REPORT_FAILURE( cb->errcode );
        if( s_work.callback != NULL ) s_work.callback( BSDOWNCALLBACK_ERROR );
        return;
    }
    // Reset �͎��̏�Ԃ��J�n�����A�A�C�h�����O�i�ҋ@���j��Ԃɂ��܂��B
    mywh_ChangeSysState(mywh_SYSSTATE_IDLE);
}
/* ----------------------------------------------------------------------
   power off
  ---------------------------------------------------------------------- */
static BOOL mywh_StateInPowerOff(void)
{
    // �����n�[�h�E�F�A�ւ̓d�͋������I�����܂��B
    // ���̏�Ԃ́A�e�@�q�@���ʂł��B
    WMErrCode result;
    WH_TRACE_STATE;

    result = WM_PowerOff( mywh_StateOutPowerOff );
    if (result != WM_ERRCODE_OPERATING)
    {
        mywh_REPORT_FAILURE(result);
        return FALSE;
    }
    return TRUE;
}

static void mywh_StateOutPowerOff(void *arg)
{
    // �d���ؒf���Ԃł��B
    WMCallback* cb  = (WMCallback*)arg;
    WH_TRACE_STATE;

    if (cb->errcode != WM_ERRCODE_SUCCESS)
    {
        mywh_REPORT_FAILURE(cb->errcode);
        return;
    }

    if ( ! mywh_StateInDisable() )
    {
        mywh_ChangeSysState(mywh_SYSSTATE_FATAL);
    }
}

/* ----------------------------------------------------------------------
   disable
  ---------------------------------------------------------------------- */
static BOOL mywh_StateInDisable(void)
{
    // �����n�[�h�E�F�A�̎g�p�I����ʒm���܂��B
    // ���̏�Ԃ́A�e�@�q�@���ʂł��B
    WMErrCode result;
    WH_TRACE_STATE;

    result = WM_Disable( mywh_StateOutDisable );
    if (result != WM_ERRCODE_OPERATING)
    {
        mywh_REPORT_FAILURE(result);
        return FALSE;
    }
    return TRUE;
}

static void mywh_StateOutDisable(void *arg)
{
    // �S�ďI�����܂����B
    WMCallback* cb  = (WMCallback*)arg;
    WH_TRACE_STATE;

    if ( cb->errcode != WM_ERRCODE_SUCCESS )
    {
        mywh_REPORT_FAILURE(cb->errcode);
    }
}


/* ----------------------------------------------------------------------
  state : End
  ---------------------------------------------------------------------- */

/* ----------------------------------------------------------------------
  state : WM_End
  ---------------------------------------------------------------------- */
static void mywh_StateOutEnd( void *arg )
{
    WMCallback *cb = (WMCallback*)arg;
    if ( cb->errcode != WM_ERRCODE_SUCCESS )
    {
        mywh_ChangeSysState( mywh_SYSSTATE_FATAL );
        return;
    }
    mywh_ChangeSysState( mywh_SYSSTATE_STOP );
   	if( s_work.callback != NULL ) s_work.callback( BSDOWNCALLBACK_FINISH );
}


/* ======================================================================
   Public Interfaces
   ====================================================================== */


/**************************************************************************
 * �ȉ��́AWH �̊e��ݒ�l��ύX����֐��ł��B
 **************************************************************************/

/*---------------------------------------------------------------------------*
  Name:         mywh_SetDebugOutput

  Description:  �f�o�b�O������o�͗p�̊֐���ݒ肵�܂��B

  Arguments:    func    �ݒ肷��f�o�b�O������o�͗p�̊֐�.

  Returns:      None.
 *---------------------------------------------------------------------------*/
static void mywh_SetDebugOutput( void (*func)(const char *, ...) )
{
    OSIntrMode enabled = OS_DisableInterrupts();
    wh_trace = func;
    (void)OS_RestoreInterrupts( enabled );
}


/* ----------------------------------------------------------------------
   Name:        mywh_GetSystemState
   Description: WH �̓�����Ԃ��擾���܂��B
   Arguments:   none.
   Returns:     ������ԁimywh_SYSSTATE_XXXX�j�B
   ---------------------------------------------------------------------- */
static int mywh_GetSystemState(void)
{
    return s_work.SysState;
}

/**************************************************************************
 * �ȉ��́A���������������ĒʐM�\��Ԃ܂őJ�ڂ���֐��ł��B
 **************************************************************************/

/* ----------------------------------------------------------------------
   Name:        mywh_Initialize
   Description: ��������Ƃ��s���A�������V�[�P���X���J�n���܂��B
   Arguments:   None.
   Returns:     �V�[�P���X�J�n�ɐ�������ΐ^�B
   ---------------------------------------------------------------------- */
static BOOL mywh_Initialize( void )
{
    s_work.ErrCode = WM_ERRCODE_SUCCESS;
    
    // �������V�[�P���X�J�n�B
    if ( ! mywh_StateInInitialize() )
    {
        return FALSE;
    }
    
    return TRUE;
}

/* ----------------------------------------------------------------------
   Indicate handler
   ---------------------------------------------------------------------- */
static void mywh_IndicateHandler( void* arg )
{
    WMindCallback*  cb = (WMindCallback*)arg;

    if( cb->errcode == WM_ERRCODE_FIFO_ERROR )
    {
        mywh_ChangeSysState( mywh_SYSSTATE_ERROR );
        if( s_work.callback != NULL ) s_work.callback( BSDOWNCALLBACK_ERROR );
    }
}

/* ----------------------------------------------------------------------
   state : Initialize
   ---------------------------------------------------------------------- */
static BOOL mywh_StateInInitialize(void)
{
    // �������V�[�P���X���J�n���܂��B
    WMErrCode result;
    WH_TRACE_STATE;
    
    mywh_ChangeSysState( mywh_SYSSTATE_BUSY );
    result = WM_Initialize( &(s_work.WmBuffer[0]), mywh_StateOutInitialize, mywh_DMA_NO );
    if ( result != WM_ERRCODE_OPERATING )
    {
        mywh_REPORT_FAILURE( result );
        mywh_ChangeSysState( mywh_SYSSTATE_FATAL );
        return FALSE;
    }
    
     return TRUE;
}

static void mywh_StateOutInitialize(void *arg)
{
    // �d���������Ԃł��B
    WMErrCode result;
    WMCallback* cb  = (WMCallback*)arg;
    WH_TRACE_STATE;
    
    if (cb->errcode != WM_ERRCODE_SUCCESS)
    {
        mywh_REPORT_FAILURE(cb->errcode);
        mywh_ChangeSysState( mywh_SYSSTATE_FATAL );
        return;
    }
    // �s����ɔ�������ʒm���󂯎��R�[���o�b�N�֐���ݒ肵�܂��B
    result = WM_SetIndCallback( mywh_IndicateHandler );
    if( result != WM_ERRCODE_SUCCESS )
    {
        mywh_REPORT_FAILURE( result );
        mywh_ChangeSysState( mywh_SYSSTATE_FATAL );
        return;
    }
    
    // �V�X�e����Ԃ��A�C�h�����O�i�ҋ@���j�ɕύX�B
    mywh_ChangeSysState( mywh_SYSSTATE_IDLE );
    
    // �X�L�������J�n���܂��B
    (void) mywh_StartScan();
}


/**************************************************************************
 * �ȉ��́A�ʐM���I�����ď�������Ԃ܂őJ�ڂ�����֐��ł��B
 **************************************************************************/

/* ----------------------------------------------------------------------
   Name:        mywh_Reset
   Description: ���Z�b�g�V�[�P���X���J�n���܂��B
                ���̊֐����ĂԂƁA���̏�Ԃɍ\�킸���Z�b�g���܂��B
        �G���[����̋������A�p�ł��B
   Arguments:   none.
   Returns:     �����J�n�ɐ�������ΐ^�B
   ---------------------------------------------------------------------- */
static void mywh_Reset(void)
{
    if ( ! mywh_StateInReset() )
    {
        mywh_ChangeSysState( mywh_SYSSTATE_FATAL );
    }
}

/* ----------------------------------------------------------------------
   Name:        mywh_Finalize
   Description: �㏈���E�I���V�[�P���X���J�n���܂��B
                ���̊֐����ĂԂƁA���̏�Ԃ����ēK�؂ȏI���V�[�P���X��
                ���s���܂��B
                �ʏ�̏I�������ɂ́imywh_Reset�ł͂Ȃ��j���̊֐����g�p���܂��B
   Arguments:   None.
   Returns:     None.
   ---------------------------------------------------------------------- */
static void mywh_Finalize(void)
{
    if ( s_work.SysState == mywh_SYSSTATE_IDLE )
    {
        WH_TRACE("already mywh_SYSSTATE_IDLE\n");
        return;
    }

    WH_TRACE("mywh_Finalize, state = %d\n", s_work.SysState);

    
    if ( (s_work.SysState != mywh_SYSSTATE_KEYSHARING)
         && (s_work.SysState != mywh_SYSSTATE_DATASHARING)
         && (s_work.SysState != mywh_SYSSTATE_CONNECTED) )
    {
        // �ڑ����Ă��Ȃ��E�G���[��ԂȂǂ̏ꍇ�̓��Z�b�g���Ă����B
        mywh_ChangeSysState( mywh_SYSSTATE_BUSY );
        mywh_Reset();
        return;
    }
    
    mywh_ChangeSysState( mywh_SYSSTATE_BUSY );
   
}

/*---------------------------------------------------------------------------*
  Name:         mywh_End

  Description:  �����ʐM���I������B

  Arguments:    None.

  Returns:      ��������ΐ^�B
 *---------------------------------------------------------------------------*/
static BOOL mywh_End( void )
{
    mywh_ASSERT( s_work.SysState == mywh_SYSSTATE_IDLE );
    
    mywh_ChangeSysState( mywh_SYSSTATE_BUSY );
    if ( WM_End( mywh_StateOutEnd ) != WM_ERRCODE_OPERATING )
    {
        mywh_ChangeSysState( mywh_SYSSTATE_ERROR );
        if( s_work.callback != NULL ) s_work.callback( BSDOWNCALLBACK_ERROR );
        return FALSE;
    }
    return TRUE;
}

static BOOL mywh_StateInMyReset(void);
static void mywh_StateOutMyReset(void *arg);
BOOL bsdown_end( void )
{
    if ( s_work.SysState == mywh_SYSSTATE_IDLE ) 
    {
    	return mywh_End( );
    }
    return mywh_StateInMyReset();
}

static BOOL mywh_StateInMyReset(void)
{
    // ���̏�Ԃ́A�e�@�q�@���ʂł��B
    // �V�X�e����������Ԃɖ߂��܂��B
    WMErrCode result;
    WH_TRACE_STATE;

    mywh_ChangeSysState( mywh_SYSSTATE_BUSY );
    result = WM_Reset( mywh_StateOutMyReset );
    if ( result != WM_ERRCODE_OPERATING )
    {
        mywh_REPORT_FAILURE(result);
        return FALSE;
    }
    return TRUE;
}

static void mywh_StateOutMyReset(void *arg)
{
    WMCallback* cb  = (WMCallback*)arg;
    WH_TRACE_STATE;
    if ( cb->errcode != WM_ERRCODE_SUCCESS )
    {
        mywh_ChangeSysState( mywh_SYSSTATE_ERROR );
        mywh_REPORT_FAILURE( cb->errcode );
        if( s_work.callback != NULL ) s_work.callback( BSDOWNCALLBACK_ERROR );
        return;
    }
    // �A�C�h�����O�i�ҋ@���j��Ԃɂ��܂��B
    mywh_ChangeSysState(mywh_SYSSTATE_IDLE);
    
    // �I���������J�n���܂��B
    mywh_End();
}

/*---------------------------------------------------------------------------*
  Name:         bsdown_c_init

  Description:  
	  �q�@�p�������B
	  ������WM_INIT���Ăяo���A�X�L�����J�n�܂ň�C�ɐi�߂܂��B
	  

  Arguments:    None.

  Returns:      ��������ΐ^�B
 *---------------------------------------------------------------------------*/
BOOL bsdown_c_init( void *target, BSDOWN_CALLBACK callback, void *buffer )
{
	s_work_ptr = (BSDOWN_WORK*) (((u32)buffer + 31) / 32 * 32);
	s_work.SysState = mywh_SYSSTATE_STOP;
	s_work.state = BSDOWNSTATE_STARTSCAN;
	s_work.target = (u8*)target;
	s_work.packets = 0;
	s_work.received = 0;
	s_work.callback = callback;	
	s_work.channel = 16 + 0;
	s_work.infoflag = 0;
	s_work.linklevel = -1;
	return mywh_Initialize();
}

// �͂��߂ăf�[�^���󂯂Ƃ����Ƃ��B
static void bsdown_c_startdownload( BSDOWN_GAMEINFO_STRUCT *info )
{
	int i;
	s_work.infoflag = 0;
	s_work.state = BSDOWNSTATE_RECEVING;
	s_work.crc = info->crc;
	s_work.size = info->size;
	s_work.packets = (u16)((s_work.size - 1) / BSDOWN_ONEPACKET_SIZE + 1);
	s_work.received = 0;
	s_work.count = 0;
	for(i = 0; i < s_work.packets; i++) s_work.flags[i] = 0;
}

// ��M�X�e�b�v�B
static int bsdown_c_step( BSDOWN_GAMEINFO_STRUCT *info )
{
	if( s_work.crc != info->crc || s_work.size != info->size ) 
	{
		OS_TPrintf("!!!!!\n");
		// �Ⴄ�^�C�v�̃X�N���v�g�����s���Ĕz�M���H
		if( s_work.count++ >= BSDOWN_TIMEOUT )
		{
			// �X�N���v�g�̎�M����蒼���B
			bsdown_c_startdownload( info );
			if( s_work.callback != NULL ) s_work.callback( BSDOWNCALLBACK_RESTART );
		}
		else 
		{
			return 0;
		}
	}
	
	OS_TPrintf("%d.", info->index);
	if( info->index == 0xffff )
	{
	  MI_CpuCopy32( &(info->data[0]), &(s_work.fileinfo[0]), BSDOWN_ONEPACKET_SIZE );
	  s_work.infoflag = 1;
		
	}
	 else
	{ 	
		s_work.index = info->index;
		if( info->index >= s_work.packets )
		{
		   // index�����������B�G���[
		   if( s_work.callback != NULL ) s_work.callback( BSDOWNCALLBACK_ERROR );
		   mywh_ChangeSysState( mywh_SYSSTATE_ERROR );
		}
		// ���̃p�P�b�g�͊��Ɏ󂯎��ς݂��ǂ���
		if( s_work.flags[info->index] == 0) 
		{
			// �܂��󂯎���Ă��Ȃ�
			s_work.flags[info->index] = 1;
			if( info->index == s_work.packets - 1 ) 
			{
				MI_CpuCopy32( &(info->data[0]), &(s_work.target[info->index * BSDOWN_ONEPACKET_SIZE]), s_work.size - info->index * BSDOWN_ONEPACKET_SIZE );
			}
			else 
			{
				MI_CpuCopy32( &(info->data[0]), &(s_work.target[info->index * BSDOWN_ONEPACKET_SIZE]), BSDOWN_ONEPACKET_SIZE );			
			}

			s_work.received++;
			OS_TPrintf("receive %d, (%d / %d)\n", info->index, s_work.received, s_work.packets); 
			if( s_work.received == s_work.packets ) 
			{
				if( s_work.callback != NULL ) s_work.callback( BSDOWNCALLBACK_SUCCESS );
				return 1;
			}
			
		}
	}
	
	return 0;
}

// ��M�f�[�^�̂b�q�b���v�Z
static u16 culcCRC(u8 *data, u32 size)
{
	u16 ans, i;
	u16 *target = (u16 *) data;
	ans = 0;
	for(i = 0; i < size / 2; i++ )
	{
		ans += target[i];
		ans = (u16)((ans << 1) | (ans >> 15));	
	}
	return ans;
}

// ���݂܂łɎ�M�����p�P�b�g�ʂ��擾
int bsdown_c_received(void)
{
	return s_work.received;	
}

// ��M���ׂ��p�P�b�g�̗�
int bsdown_c_total(void)
{
	return s_work.packets;
}

// ��M���Ă���f�[�^�̃T�C�Y�B�܂���M���J�n����Ă��Ȃ���΂O��Ԃ��B
int bsdown_c_size(void)
{
	return (int)s_work.size;	
}

// �Ō�Ɏ�M�����p�P�b�g�̃C���f�b�N�X
int bsdown_c_lastreceive(void)
{
	return s_work.index;	
}

// ���݂܂Ŏ󂯎�����p�P�b�g�̕\
u8 *bsdown_c_downloadpacket(void)
{
	return &(s_work.flags[0]);	
}

#define SECRET_KEY 0x3fa2

// ��M�ς݂̂b�q�b�����������`�F�b�N�B
int bsdown_c_checkcrc(void)
{
	{
		// �Í����Ɏg��key�B���M����MacAddr�i�U�o�C�g�j + CRC�i�Q�o�C�g�j
		u16 key[4];
		u16 *ptr;
		ptr = (u16*)&(s_work.macaddress[0]);
		key[0] = ptr[0];
		key[3] = ptr[1];
		key[2] = ptr[2];
		key[1] = s_work.crc;
		
		{
			int i;
			u16 mask = SECRET_KEY;
			for(i = 0; i < 4; i++)
			{
				key[i] = key[i] ^ mask;
				mask = key[i];
			}	
		}
		
		// �f�o�b�O�p
		{
			u8 *test = (u8*)&(key[0]);
			int i;
			OS_TPrintf("key = ");
			for( i = 0; i < 8; i++ ){
				OS_TPrintf("%d, ", key[i]);
			}	
			OS_TPrintf("\n");
		}
		OS_TPrintf("CRYPTO_RC4Init�J�n\n");
		
		CRYPTO_RC4Init( &(s_work.rc4context), &(key[0]), 8 );

		OS_TPrintf("CRYPTO_RC4Init�I��\n");
		
		CRYPTO_RC4Encrypt(
			&(s_work.rc4context),
			s_work.target,
			s_work.size,
			s_work.target
		);

		OS_TPrintf("CRYPTO_RC4Encrypt�I��\n");
		
		// �O�̂��߁A�R���e�L�X�g�͍폜���Ă���
		MI_CpuClear32( &(s_work.rc4context), sizeof(s_work.rc4context) );
	}	
	
	return ( culcCRC( s_work.target, s_work.size ) == s_work.crc );
}

// �Ō�ɂ����Ƃ����r�[�R���̋��x���擾
int bsdown_c_linklevel(void)
{
	return s_work.linklevel;	
}

int bsdown_c_worksize(void){
	return sizeof(BSDOWN_WORK) + 32;
}

void *bsdown_c_fileheader(void)
{
  if( s_work.infoflag ) return &(s_work.fileinfo[0]);
  return NULL;
}
//
