//=============================================================================
/**
 * @file	dwc_rap.c
 * @bfief	DWC���b�p�[�B�I�[�o�[���C���W���[���ɒu������
 * @author	kazuki yoshihara
 * @date	06/02/23
 */
//=============================================================================

#include "common.h"
#include "communication/comm_def.h"
#include "communication/comm_state.h"
#include "wifi/dwc_rap.h"
#include "wifi/vchat.h"
#include "system/pm_debug_wifi.h"
#include <vct.h>


// ���b�ԒʐM���͂��Ȃ��ƃ^�C���A�E�g�Ɣ��f���邩
#define MYDWC_TIMEOUTSEC 10


// ���t���[�����M���Ȃ��ƁAKEEP_ALIVE�g�[�N���𑗂邩�B
#define KEEPALIVE_TOKEN_TIME 120

// �{�C�X�`���b�g�𗘗p����ꍇ�͒�`����B
#define MYDWC_USEVCHA

#ifdef MYDWC_USEVCHA
// �ڑ����Ď����I�Ƀ{�C�X�`���b�g���X�^�[�g������ꍇ�ɒ�`����B
#define VCHAT_AUTOSTQART
#endif

//#define YOSHIHARA_VCHAT_ONOFFTEST


// �q�[�v�̈�̍ő�g�p�ʂ��Ď�����ꍇ��`
#define CHEAK_HEAPSPACE

// �f�o�b�O�o�͂��ʂɓf���o���ꍇ��`
//#define DEBUGPRINT_ON

#ifdef DEBUGPRINT_ON
#define MYDWC_DEBUGPRINT(...) \
    (void) ((OS_TPrintf(__VA_ARGS__)))
#else
#define MYDWC_DEBUGPRINT(...)           ((void) 0)
#endif



// �e�X�g�p�T�[�o�Ɍq���Ƃ��ɒ�`
//#define USE_AUTHSERVER_DEVELOP

// �t�����h���X�g�̃T�C�Y
#define FRIENDLIST_MAXSIZE 32

// �P�t���[���ɉ��l���̃f�[�^���X�V���邩�B
#define FRIENDINFO_UPDATA_PERFRAME 4

// WiFi�Ŏg��Heap�̃T�C�Y(128K�o�C�g�A���j+7000
#define MYDWC_HEAPSIZE (0x2B000)

#define MYDWC_HEAPID HEAPID_WIFIMENU

// ���̕ӂ̓e�X�g�p�B�����Ɋ��蓖�Ă�ꂽ��A�w�肷��B
#define GAME_NAME        "pokemondpds"  // �g�p����Q�[����
#define GAME_SECRET_KEY  "1vTlwb"  // �g�p����V�[�N���b�g�L�[
#define GAME_PRODUCTID   10727         // �g�p����v���_�N�gID

#define SIZE_RECV_BUFFER (4 * 1024)
#define SIZE_SEND_BUFFER 256

typedef struct
{
	u8 recvBuffer[ SIZE_RECV_BUFFER ];
	u8 sendBuffer[ SIZE_SEND_BUFFER ];
	DWCFriendData *keyList;  // DWC�`���̗F�B���X�g	
	DWCFriendsMatchControl stDwcCnt;    // DWC����\����	
    DWCUserData *myUserData;		// DWC�̃��[�U�f�[�^�i�����̃f�[�^�j
	DWCInetControl stConnCtrl;
    SAVEDATA* pSaveData;   // 2006.04.07 k.ohno  �Z�[�u�f�[�^��ێ�
	
	void *heapPtr;
	NNSFndHeapHandle headHandle;

	MYDWCReceiverFunc serverCallback;
	MYDWCReceiverFunc clientCallback;
	
	void (*fetalErrorCallback)(int);
	
	u8 friend_status[FRIENDLIST_MAXSIZE];
	void *friendinfo;	
	int infosize;	
	u32 friendupdate_index;	
	
	int state;
	int matching_type;
	
	int sendbufflag;
	
	int op_aid;			// �����aid
	
	int heapID;
	
	int isvchat;
	int friendindex;
	BOOL newFriendConnect;  // �ڑ����Ă�����TRUE 2006.05.24 k.ohno
    BOOL bDelay;     // �x���e�X�g
    BOOL bVChat;     // VCHATONOFF�e�X�g
	
	int vchatcodec;
	
	int timeoutflag;
	
	int sendintervaltime;		// �O��f�[�^�𑗐M���Ă���̃t���[�����B
	
	int myvchaton;				// �����̃{�C�X�`���b�g���I�����I�t��
	int opvchaton;				// ����̃{�C�X�`���b�g���I�����I�t��
	
	u8 myseqno;				// ���������M����p�P�b�g�̃V�[�P���XNo
	u8 opseqno;				// ���肪�Ō�ɑ����Ă����p�P�b�g�̃V�[�P���XNo
    u8 bHeapError;  // HEAP�m�ێ��s�̏ꍇ
	
	u16 firstflag;
	
	// �e�X�g�p
	int s_param;
} MYDWC_WORK;

// �{�C�X�`���b�g�̃g�[�N���ƍ������Ȃ��悤�ɂ��邽�߁A
// �{�C�X�`���b�g�ƈႤ�R�Q�o�C�g�̐������p�P�b�g�̐擪�ɂ���B
#define MYDWC_PACKETYPE_MASK 0x000000ff
#define MYDWC_PACKET_VCHAT_MASK 0x00000100
#define MYDWC_PACKET_VCHAT_SHIFT 8
#define MYDWC_PACKET_SEQNO_POS 2

#define MYDWC_GAME_PACKET 0x0001

// �^�C���A�E�g������h�����߁A��莞�ԑ��M���Ȃ��ꍇ�A
// ����̃f�[�^�𑗂�B���̂Ƃ��̐���
#define MYDWC_KEEPALIVE_PACKET 0x0002

enum{
	MDSTATE_INIT,	
	MDSTATE_CONNECTING,
	MDSTATE_CONNECTED,
	MDSTATE_TRYLOGIN,
	MDSTATE_LOGIN,
	
	MDSTATE_MATCHING,
	MDSTATE_CANCEL,	
	MDSTATE_MATCHED,	
	MDSTATE_CANCELFINISH,	
	
	MDSTATE_FAIL,			// 2006.7.4 yoshihara�ǉ�
	MDSTATE_FAILFINISH,	
	
	MDSTATE_ERROR,
	MDSTATE_ERROR_FM,
	MDSTATE_ERROR_DISCONNECT,
	MDSTATE_ERROR_FETAL,
	
	MDSTATE_DISCONNECTTING,	
	MDSTATE_DISCONNECT,	
	
	MDSTATE_TIMEOUT,
	
	MDSTATE_LAST
};

enum {
	MDTYPE_RANDOM,
	MDTYPE_PARENT,
	MDTYPE_CHILD
};
	

void *_dWork_temp = NULL;
static MYDWC_WORK *_dWork = NULL;


static void LoginCallback(DWCError error, int profileID, void *param);
static void UpdateServersCallback(DWCError error, BOOL isChanged, void* param);
static void FriendStatusCallback(int index, u8 status, const char* statusString, void* param);
static void DeleteFriendListCallback(int deletedIndex, int srcIndex, void* param);
static void BuddyFriendCallback(int index, void* param);

static void ConnectToAnybodyCallback(DWCError error, BOOL cancel, void* param);
static void SendDoneCallback( int size, u8 aid );
static void UserRecvCallback( u8 aid, u8* buffer, int size );
static void ConnectionClosedCallback(DWCError error, BOOL isLocal, BOOL isServer, u8  aid, int index, void* param);
//static int handleError();
static int EvaluateAnybodyCallback(int index, void* param);

static void recvTimeoutCallback(u8 aid);

static void mydwc_updateFriendInfo( );

#ifdef _WIFI_DEBUG_TUUSHIN

#define _USER_PARAM_MAGIC (55)

static void _NNSFndHeapVisitor(void* memBlock, NNSFndHeapHandle heap, u32 userParam)
{
    if(userParam == _USER_PARAM_MAGIC){
        GF_ASSERT(NNS_FndCheckExpHeap(heap, NNS_FND_HEAP_ERROR_PRINT));
        GF_ASSERT(NNS_FndCheckForMBlockExpHeap(memBlock, heap, NNS_FND_HEAP_ERROR_PRINT));
    }
}

#endif


//==============================================================================
/**
 * �C���^�[�l�b�g�֐ڑ��J�n
 * @param   userdata �����̃��O�C���f�[�^�ւ̃|�C���^
 * @param   list �t�����h���X�g�̐擪�|�C���^
 * @retval  MYDWC_STARTCONNECT_OK �c OK
 * @retval  MYDWC_STARTCONNECT_FIRST �c ���߂Đڑ�����ꍇ�B�i���b�Z�[�W�\���̕K�v�L
 * @retval  MYDWC_STARTCONNECT_DIFFERENTDS �c �قȂ�c�r�Őڑ����悤���Ă�ꍇ�B�i�v�x���j
 */
//==============================================================================
int mydwc_startConnect(SAVEDATA* pSaveData, int heapID)
{
    // �q�[�v�̈悩�烏�[�N�̈���m�ہB
	GF_ASSERT( _dWork_temp == NULL );
#ifdef _WIFI_DEBUG_TUUSHIN
#ifdef DEBUGPRINT_ON
	DWC_SetReportLevel(DWC_REPORTFLAG_ALL);
#endif
#endif
    
    OS_TPrintf("dwcrasp   %d \n",sizeof(MYDWC_WORK) + 32);
    
	_dWork_temp = sys_AllocMemory(heapID, sizeof(MYDWC_WORK) + 32);
	_dWork = (MYDWC_WORK *)( ((u32)_dWork_temp + 31) / 32 * 32 );
    // 2006.04.07 k.ohno �Z�[�u�f�[�^�|�C���^��ێ�
    _dWork->pSaveData = pSaveData;
	_dWork->serverCallback = NULL;
	_dWork->clientCallback = NULL;	
	_dWork->fetalErrorCallback = NULL;
	_dWork->state = MDSTATE_INIT;
	_dWork->heapID = heapID;
	_dWork->heapPtr = sys_AllocMemory(heapID, MYDWC_HEAPSIZE + 32);
	_dWork->headHandle = NNS_FndCreateExpHeap( (void *)( ((u32)_dWork->heapPtr + 31) / 32 * 32 ), MYDWC_HEAPSIZE);
	_dWork->vchatcodec = VCHAT_NONE;
	_dWork->friendindex = -1;
	_dWork->friendupdate_index = 0;
    _dWork->op_aid = -1;
    _dWork->newFriendConnect = -1;
    _dWork->bDelay = FALSE;
    _dWork->bVChat = TRUE;
    _dWork->bHeapError = FALSE;
    
    // 2006.7.22 yoshihara �����ŁASeqno���Z�b�g
    _dWork->myseqno = 0;
    _dWork->opseqno = 0;
    _dWork->myvchaton = 1;
    _dWork->opvchaton = 1;
    
    // 2006.04.07 k.ohno �����ύX �Z�[�u�f�[�^���瓾��
    if(pSaveData!=NULL){
        _dWork->myUserData = WifiList_GetMyUserInfo(SaveData_GetWifiListData(_dWork->pSaveData));
        _dWork->keyList = (DWCFriendData*)WifiList_GetDwcDataPtr(SaveData_GetWifiListData(_dWork->pSaveData),0);
    }

#ifdef PM_DEBUG
    DWC_ReportUserData(_dWork->myUserData);
#endif

#ifdef DEBUG_ONLY_FOR_ohno
   if( !DWC_CheckUserData( _dWork->myUserData ) ){
       GF_ASSERT(0);  //�C���m�F�̂��ߓ���Ă���k.ohno
   }
#endif

	_dWork->friendinfo = NULL;
	{
		int i;
		for( i = 0; i < FRIENDLIST_MAXSIZE; i++ )
		{
			_dWork->friend_status[i] = DWC_STATUS_OFFLINE;
		}
	}
	

	// ���[�U�f�[�^�̏�Ԃ��`�F�b�N�B
	mydwc_showFriendInfo();	
	

	if( !DWC_CheckHasProfile( _dWork->myUserData ) ) 
	{
		// �܂����̃f�[�^�ň�x���v���e���Ɍq���ł��Ȃ��B
		return MYDWC_STARTCONNECT_FIRST;
	}
	
	if( !DWC_CheckValidConsole( _dWork->myUserData ) )
	{
		// �{�̏�񂪈Ⴄ���Ⴄ�c�r�Őڑ����悤�Ƃ��Ă���B
		return 	MYDWC_STARTCONNECT_DIFFERENTDS;
	}
	


	return MYDWC_STARTCONNECT_OK;
}

//==============================================================================
/**
 * dwc_rap.c���m�ۂ����̈���J������B
 * @param   none
 * @retval  none
 */
//==============================================================================
void mydwc_free()
{
    if(_dWork){

        NNS_FndDestroyExpHeap( _dWork->headHandle );
        sys_FreeMemory( _dWork->heapID, _dWork->heapPtr  );
        sys_FreeMemory( _dWork->heapID, _dWork_temp  );
        _dWork_temp = NULL;
        _dWork = NULL;
        OS_TPrintf("dwcrap�I��\n");
    }
	DWC_ClearError();
}

//==============================================================================
/**
 * �C���^�[�l�b�g�ڑ����ɖ��t���[���Ăяo�����֐�
 * @param   userdata �����̃��O�C���f�[�^�ւ̃|�C���^
 * @param   list �t�����h���X�g�̐擪�|�C���^
 * @retval  ���c�ڑ������B�O�c�ڑ����B���c�G���[�i�G���[�R�[�h���Ԃ�j
 */
//==============================================================================
int mydwc_connect()
{

    switch( _dWork->state )
	{
		case MDSTATE_INIT:
		// �������
		{
		    // �������m�ۊ֐��ݒ�
		    DWC_SetMemFunc( mydwc_AllocFunc, mydwc_FreeFunc );
		    
		    // �l�b�g�ڑ�������
            DWC_InitInetEx(&_dWork->stConnCtrl,COMM_DMA_NO,COMM_POWERMODE,COMM_SSL_PRIORITY);
		    
#if defined( USE_AUTHSERVER_DEVELOP )
		    DWC_SetAuthServer(DWC_CONNECTINET_AUTH_TEST);
#else
		    DWC_SetAuthServer(DWC_CONNECTINET_AUTH_RELEASE);
#endif
			
			// �񓯊��Ƀl�b�g�ɐڑ�
			DWC_ConnectInetAsync();
			
			_dWork->state = MDSTATE_CONNECTING;
			_dWork->isvchat = 0;
		}
		
		case MDSTATE_CONNECTING:
		{
			// ���肵���󋵂ɂȂ�܂ő҂B
			if( DWC_CheckInet() )
			{
				if( DWC_GetInetStatus() == DWC_CONNECTINET_STATE_CONNECTED )
				{
					_dWork->state = MDSTATE_CONNECTED;
				}
				else
				{
					_dWork->state = MDSTATE_ERROR;
				}
			}
			else
			{
				// �����ڑ�������
		        DWC_ProcessInet();
  
				break;	
			}
		}
		
		case MDSTATE_CONNECTED:
			// �G���[���������Ă��Ȃ�������
			{
				int ret = mydwc_HandleError();
				if( ret < 0 ) return ret;
			}
			// ���O�C����
			// �Ƃ肠�����A�F�B���X�g�͏�����Ԃɂ��Ă����B   k.ohno 4.16�C��
//			MI_CpuClear32( &(_dWork->keyList[0]), sizeof(_dWork->keyList) );

			// �t�����h���C�u����������
		    DWC_InitFriendsMatch(&(_dWork->stDwcCnt), (_dWork->myUserData), 
		    			 GAME_PRODUCTID, GAME_NAME,
                         GAME_SECRET_KEY, 0, 0,
                         _dWork->keyList, FRIENDLIST_MAXSIZE);

            // �Ƃ肠�����AIPL�̃��[�U�����g���ă��O�C��
		    {
		    	// �����̃��[�U�������k�B
				OSOwnerInfo info;
				OS_GetOwnerInfo( &info );
			    DWC_LoginAsync( &(info.nickName[0]), NULL, LoginCallback, NULL);       
		    }
		    _dWork->state = MDSTATE_TRYLOGIN;
		
		case MDSTATE_TRYLOGIN:
			// ���O�C������������܂ő҂B
			DWC_ProcessFriendsMatch();
			break;
			
		case MDSTATE_LOGIN:
            DWC_ProcessFriendsMatch();   // 2006.04.07 k.ohno ���O�C�����������̏�Ԃ����������
			return 1;
	}
	return mydwc_HandleError();	
}

//==============================================================================
/**
 * ��M�����Ƃ��̃R�[���o�b�N��ݒ肷��֐�
 * @param client �c �N���C�A���g�Ƃ��ẴR�[���o�b�N�֐�
 * @param server �c �T�[�o�Ƃ��ẴR�[���o�b�N�֐�
 * @retval  none
 */
//==============================================================================
void mydwc_setReceiver( MYDWCReceiverFunc server, MYDWCReceiverFunc client )
{
	_dWork->serverCallback = server;
	_dWork->clientCallback = client;	
}

//==============================================================================
/**
 * �����_���ΐ���s���֐��B�����_���}�b�`���͐��\�t���[���������Ԃ��Ă��Ȃ����Ƃ�����B
 * @retval  ���c�����B�O�c���s�B
 */
//==============================================================================
static char randommatch_query[] = "gn = 'pe'";
int mydwc_startmatch( )
{
	if( _dWork->state != MDSTATE_LOGIN ) return 0;

    (void)DWC_AddMatchKeyString(0,"gn","pe");
                              
    _dWork->state = MDSTATE_MATCHING;
    DWC_ConnectToAnybodyAsync
    (
    	2,
        randommatch_query,
        ConnectToAnybodyCallback,
        NULL,
        EvaluateAnybodyCallback,
        NULL
    );
	_dWork->matching_type = MDTYPE_RANDOM;
    // ���M�R�[���o�b�N�̐ݒ�	
    DWC_SetUserSendCallback( SendDoneCallback ); 

    // ��M�R�[���o�b�N�̐ݒ�	
    DWC_SetUserRecvCallback( UserRecvCallback ); 
    
    // �R�l�N�V�����N���[�Y�R�[���o�b�N��ݒ�
    DWC_SetConnectionClosedCallback(ConnectionClosedCallback, NULL);
    
    // �^�C���A�E�g�R�[���o�b�N�̐ݒ�
    DWC_SetUserRecvTimeoutCallback( recvTimeoutCallback );
    
    _dWork->sendbufflag = 0;
    
	// �e�X�g�p
	_dWork->s_param = 0;    
    
    return 1;    
}

// 2006.7.4 yoshihara �ǉ�
static void finishcancel()
{
    if( _dWork->state == MDSTATE_FAIL ){
		_dWork->state = MDSTATE_FAILFINISH;
    }
    else
    {
		_dWork->state = MDSTATE_CANCELFINISH;
    }	
}

//==============================================================================
/**
 * �����_���ΐ�}�b�`���O���ɖ��t���[���Ă΂��֐��B
 * @retval  
 	STEPMATCH_CONTINUE�c�}�b�`���O��
 	STEPMATCH_SUCCESS�c����
 	STEPMATCH_CANCEL�c�L�����Z��
 	STEPMATCH_FAIL  �c���肪�e����߂����߁A�ڑ��𒆒f
 	���c�G���[����
 */
//==============================================================================
int mydwc_stepmatch( int isCancel )
{
	switch ( _dWork->state )
	{
		case MDSTATE_MATCHING:
			// ���ݒT����
			if( isCancel ) 
			{
				_dWork->state = MDSTATE_CANCEL;
			}
			// 2006.7.4 yoshihara�C�� ��������
			// �q�@�̏ꍇ�A�Ȃ��ɂ����Ă�e�����݂��T�[�o���[�h���ǂ����`�F�b�N����B
			if( _dWork->matching_type == MDTYPE_CHILD )
			{
				if( _dWork->friendindex >= 0 ) // ����if�͔O�̂���
				{
					if( _dWork->friend_status[_dWork->friendindex] != DWC_STATUS_MATCH_SC_SV )
					{
						OS_TPrintf("���肪�T�[�o����߂Ă��܂����̂ŁA�L�����Z�����܂��B\n");
						// ���ɐe�łȂ��Ȃ��Ă��܂��Ă���B�L�����Z���ֈڍ�
						_dWork->state = MDSTATE_FAIL;	
					}
				}
			}
			// 2006.7.4 yoshihara�C�� �����܂�
			
			break;
			
      case MDSTATE_CANCEL:
      case MDSTATE_FAIL:      
			if( _dWork->state == MDTYPE_RANDOM)
			{
				// �����_���}�b�`
				// �L�����Z��������
				if( !DWC_CancelMatching() )
				{
				}
				break;
			} else {
				int ret;
				ret = DWC_CloseAllConnectionsHard();
				if( ret == 1 )
				{
					// �q�@�����Ȃ����R�[���o�b�N�����ŏI��
		            // 2006.7.4 yoshihara �C��
					finishcancel();	
				}
				else if (ret == 0)
				{
					// �R�[���o�b�N���A���Ă��Ă���͂�
				}
				else
				{
		            // 2006.7.4 yoshihara �C��
					finishcancel();	
//					MYDWC_DEBUGPRINT("Now unable to disconnect.\n");
				}
			}
        break;    //@@OO   06.05.12�ǉ�
		case MDSTATE_MATCHED:
			// �����B
			{
				_dWork->firstflag = 1;
#ifdef VCHAT_AUTOSTQART
			// yoshihara�ύX�@06.6.15
//                if(_dWork->bVChat){
                    mydwc_startvchat();
//                }

                if(_dWork->bVChat)
                {
	                _dWork->myvchaton = 1;
                }
                else{
	                _dWork->myvchaton = 0;
                }

#else
				if( _dWork->vchatcodec != VCHAT_NONE ) mydwc_startvchat();
#endif
				return STEPMATCH_SUCCESS;	
			}
			break;
		case MDSTATE_CANCELFINISH:
			// ���O�C������̏�Ԃ�
			_dWork->state = MDSTATE_LOGIN;
			_dWork->sendbufflag = 0;
            _dWork->newFriendConnect = -1;
            OS_TPrintf("�L�����Z����������\n");
			return STEPMATCH_CANCEL;
		case MDSTATE_FAILFINISH:
			// ���O�C������̏�Ԃ�
			_dWork->state = MDSTATE_LOGIN;
			_dWork->sendbufflag = 0;
            _dWork->newFriendConnect = -1;
            OS_TPrintf("�t�B�j�b�V����������\n");
			return STEPMATCH_FAIL;			
		case MDSTATE_ERROR:
			{
				int ret;
				
				ret = mydwc_HandleError();
				return ret;
			}	
			
		default:
			break;		
//			return handleError();
	}
	return mydwc_step();	
		
//    DWC_ProcessFriendsMatch();  // DWC�ʐM�����X�V			
//	return handleError();
}



//==============================================================================
/**
 * �T�[�o�Ƀf�[�^���M���s�����Ƃ��ł��邩
 * @retval  1 - �����@ 0 - ���s�i���M�o�b�t�@���l�܂��Ă��铙�j
 */
//==============================================================================
BOOL mydwc_canSendToServer()
{
	return ( DWC_GetMyAID() == 0 || ( _dWork->sendbufflag == 0 && DWC_IsSendableReliable( 0 ) ) );
}

//==============================================================================
/**
 * �N���C�A���g�Ƀf�[�^���M���s�����Ƃ��ł��邩
 * @retval  1 - �����@ 0 - ���s�i���M�o�b�t�@���l�܂��Ă��铙�j
 */
//==============================================================================
BOOL mydwc_canSendToClient()
{
	return ( _dWork->sendbufflag == 0 && DWC_IsSendableReliable( 1 ) );
}

//==============================================================================
/**
 * �T�[�o�Ƀf�[�^���M���s���֐�
 * @param   data - ���M����f�[�^�ւ̃|�C���^�Bsize - ���M����f�[�^�̃T�C�Y
 * @retval  1 - �����@ 0 - ���s�i���M�o�b�t�@���l�܂��Ă��铙�j
 */
//==============================================================================
int mydwc_sendToServer(void *data, int size)
{
    if( !(size < SIZE_SEND_BUFFER) ){
        return 0;
    }

    
	MYDWC_DEBUGPRINT("mydwc_sendToServer(data=%d)\n", *((u32*)data));

	if( DWC_GetMyAID() == 0 )
	{
		// �������e
		// �R�[���o�b�N���ŏ�����������\�����l���Adata���R�s�[���Ă����B
//		void *buf = mydwc_AllocFunc( NULL, size, 32 );
//		MI_CpuCopy8	( data, buf, size );
		
		// �������g�̃T�[�o��M�R�[���o�b�N���Ăяo���B
		if( _dWork->serverCallback != NULL ) _dWork->serverCallback(0, data, size);
		
		// �R�[���o�b�N���Ăяo�����炷���ɊJ���B
//		mydwc_FreeFunc( NULL, buf, size );
		
		return 1;
	}
	else
	{
		// ���肪�e�B����ɑ΂��ăf�[�^���M�B
		if( _dWork->sendbufflag || !DWC_IsSendableReliable( 0 ) ) // ���M�o�b�t�@���`�F�b�N�B
		{
			// ���M�o�b�t�@�������ς��Ȃǂő���Ȃ��B
			return 0;
		}
		
		// ���M�o�b�t�@�ɃR�s�[
		*((u32*)&(_dWork->sendBuffer[0])) = MYDWC_GAME_PACKET | (_dWork->myvchaton << MYDWC_PACKET_VCHAT_SHIFT);
		_dWork->sendBuffer[MYDWC_PACKET_SEQNO_POS] = ++_dWork->myseqno;
		MI_CpuCopy8( data, &(_dWork->sendBuffer[4]), size );
		_dWork->sendbufflag = 1;
		
		// �e�@�Ɍ����đ��M
		DWC_SendReliable( 0, &(_dWork->sendBuffer[0]), size + 4);
//		OS_TPrintf("-");
		return 1;
	}
}

//==============================================================================
/**
 * �e�@���q�@�Ƀf�[�^���M���s���֐�
 * @param   data - ���M����f�[�^�ւ̃|�C���^�Bsize - ���M����f�[�^�̃T�C�Y
 * @retval  1 - �����@ 0 - ���s�i���M�o�b�t�@���l�܂��Ă��铙�j
 */
//==============================================================================
int mydwc_sendToClient(void *data, int size)
{
    if( !(size < SIZE_SEND_BUFFER) ){
        return 0;
    }
	// �e�@�������̓���͍s��Ȃ��͂��B
    if( !(DWC_GetMyAID() == 0) ){
        return 0;
    }
	
	MYDWC_DEBUGPRINT("sendToClient(data=%d)\n", *((u32*)data));
	
	{
		// ����ɑ΂��ăf�[�^���M�B
		if( _dWork->sendbufflag || !DWC_IsSendableReliable( 1 ) ) // ���M�o�b�t�@���`�F�b�N�B
		{
            OS_TPrintf("wifi failed %d\n",size);
			// ���M�o�b�t�@�������ς��Ȃǂő���Ȃ��B
			return 0;
		}
		
		// ���M�o�b�t�@�ɃR�s�[
		*((u32*)&(_dWork->sendBuffer[0])) = MYDWC_GAME_PACKET | (_dWork->myvchaton << MYDWC_PACKET_VCHAT_SHIFT);
		_dWork->sendBuffer[MYDWC_PACKET_SEQNO_POS] = ++_dWork->myseqno;
		MI_CpuCopy8( data, &(_dWork->sendBuffer[4]), size );
        _dWork->sendbufflag = 1;
		
		// �q�@�Ɍ����đ��M
        if(!DWC_SendReliable( 1, &(_dWork->sendBuffer[0]), size + 4)){
            OS_TPrintf("wifi failed %d\n",size);
			// ���M�o�b�t�@�������ς��Ȃǂő���Ȃ��B
            _dWork->sendbufflag = 0;
            return 0;
        }
//		OS_TPrintf("-");
	}	
	
	{
		// �����ɑ΂��đ��M
//		// �R�[���o�b�N���ŏ�����������\�����l���Adata���R�s�[���Ă����B
//		void *buf = mydwc_AllocFunc( NULL, size, 32 );
//		MI_CpuCopy8	( data, buf, size );
		
		// �������g�̃T�[�o��M�R�[���o�b�N���Ăяo���B
		if( _dWork->clientCallback != NULL ) _dWork->clientCallback(0, data, size);
		
		// �R�[���o�b�N���Ăяo�����炷���ɊJ���B
//		mydwc_FreeFunc( NULL, buf, size );
	}  
	
	return 1;
}
/*---------------------------------------------------------------------------*
  ���O�C���R�[���o�b�N�֐�
 *---------------------------------------------------------------------------*/
static void LoginCallback(DWCError error, int profileID, void *param)
{
    BOOL result;

    // stUserData���X�V����Ă��邩�ǂ������m�F�B
    if ( DWC_CheckDirtyFlag( (_dWork->myUserData)) )
    {
	    // �K�����̃^�C�~���O�Ń`�F�b�N���āAdirty flag���L���ɂȂ��Ă�����A
	    // DWCUserData��DS�J�[�h�̃o�b�N�A�b�v�ɕۑ�����悤�ɂ��Ă��������B
	    // 2006.04.07 k.ohno  �Z�[�u�G���A�ɓ����
	    DWCUserData *userdata = NULL;
	    DWC_ClearDirtyFlag(_dWork->myUserData);
	    SaveData_SaveParts(_dWork->pSaveData, SVBLK_ID_NORMAL);  //�Z�[�u�� k.ohno 06.06.05
	    
	//          userdata = WifiList_GetMyUserInfo(SaveData_GetWifiListData(_dWork->pSaveData));
	//          MI_CpuCopy32( &_dWork->myUserData, userdata,  sizeof(_dWork->myUserData) );	
	    OS_TPrintf("�����̃t�����h�R�[�h���ύX\n");
    }

    if (error == DWC_ERROR_NONE){
        // �F�ؐ����A�v���t�@�C��ID�擾


       
        result = DWC_UpdateServersAsync(NULL, //�i�ߋ��Ƃ̌݊����̂��߁A�K��NULL)
                                        UpdateServersCallback, _dWork->myUserData,
                                        FriendStatusCallback, param,
                                        DeleteFriendListCallback, param);

        if (result == FALSE){
            // �Ă�ł�������ԁi���O�C�����������Ă��Ȃ���ԁj�ŌĂ񂾎��̂�
            // FALSE���Ԃ��Ă���̂ŁA���ʂ�TRUE
            OS_TPrintf("DWC_UpdateServersAsync error teminated.\n");
            CommStateSetError(COMM_ERROR_RESET_SAVEPOINT);
            return;
        }

        // GameSpy�T�[�o��o�f�B�����R�[���o�b�N��o�^����
        DWC_SetBuddyFriendCallback(BuddyFriendCallback, NULL);
        
    }
    else
    {
        // �F�؎��s
		_dWork->state = MDSTATE_ERROR;
    }
}

/*---------------------------------------------------------------------------*
  �^�C���A�E�g�R�[���o�b�N�֐�
 *---------------------------------------------------------------------------*/
static void recvTimeoutCallback(u8 aid)
{
	OS_TPrintf("�^�C���A�E�g - ");
	// �R�l�N�V���������
	if( _dWork->timeoutflag )
	{
		OS_TPrintf("�ڑ���ؒf���܂�\n");
		DWC_CloseAllConnectionsHard( );
        _dWork->newFriendConnect = -1;
		// �^�C���A�E�g
		_dWork->state = MDSTATE_TIMEOUT;	
	}
}

/*---------------------------------------------------------------------------*
  GameSpy�T�[�o�A�b�v�f�[�g�R�[���o�b�N�֐�
 *---------------------------------------------------------------------------*/
static void UpdateServersCallback(DWCError error, BOOL isChanged, void* param)
{
#pragma unused(param)
    if (error == DWC_ERROR_NONE){
        if (isChanged){
            // �F�B���X�g���ύX����Ă���
        }
       	_dWork->state = MDSTATE_LOGIN;		// ���O�C������  
    }
    else {
        // ���O�C�����s�����ɂ��Ƃ��H
        _dWork->state = MDSTATE_ERROR;
    }
}


/*---------------------------------------------------------------------------*
  �F�B��ԕω��ʒm�R�[���o�b�N�֐�
 *---------------------------------------------------------------------------*/
static void FriendStatusCallback(int index, u8 status, const char* statusString, void* param)
{
#pragma unused(param)

    MYDWC_DEBUGPRINT("Friend[%d] changed status -> %d (statusString : %s).\n",
               index, status, statusString);
            
}


/*---------------------------------------------------------------------------*
  �F�B���X�g�폜�R�[���o�b�N�֐�
 *---------------------------------------------------------------------------*/
static void DeleteFriendListCallback(int deletedIndex, int srcIndex, void* param)
{
#pragma unused(param)
	// �t�����h���X�g���폜���ꂽ�B
	
    MYDWC_DEBUGPRINT("friend[%d] was deleted (equal friend[%d]).\n",
               deletedIndex, srcIndex);

    OS_TPrintf("friend[%d] was deleted (equal friend[%d]).\n",
               deletedIndex, srcIndex);
    // �����߂�
    MI_CpuCopy8(_dWork->keyList,WifiList_GetDwcDataPtr(SaveData_GetWifiListData(_dWork->pSaveData), 0),FRIENDLIST_MAXSIZE * sizeof(DWCFriendData));
    WifiList_DataMarge(SaveData_GetWifiListData(_dWork->pSaveData),
                       deletedIndex, srcIndex);

}


/*---------------------------------------------------------------------------*
  GameSpy�o�f�B�����R�[���o�b�N�֐�
 *---------------------------------------------------------------------------*/
static void BuddyFriendCallback(int index, void* param)
{
#pragma unused(param)

    MYDWC_DEBUGPRINT("I was authorized by friend[%d].\n", index);
}

static void setConnectionBuffer()
{
	_dWork->state = MDSTATE_MATCHED;
    // ��M�o�b�t�@�Z�b�g  // ��l�ΐ�ƌ��߂���
    if( DWC_GetMyAID() == 0 )
    {
        _dWork->op_aid = 1;
    } 
    else
    {
    	_dWork->op_aid = 0;
	}   
    DWC_SetRecvBuffer( _dWork->op_aid, &(_dWork->recvBuffer[0]), SIZE_RECV_BUFFER );	
   	DWC_SetRecvTimeoutTime( _dWork->op_aid, MYDWC_TIMEOUTSEC * 1000 );
	_dWork->timeoutflag = 0;
	_dWork->sendintervaltime = 0;

#ifdef PM_DEBUG  // �f�o�b�O�x��
    if(_dWork->bDelay){
        DWC_SetRecvDelay( 1000, _dWork->op_aid );
    }
    else{
        DWC_SetRecvDelay( 0, _dWork->op_aid );
    }
#endif
}

/*---------------------------------------------------------------------------*
  �F�B���w��ڑ��R�[���o�b�N�֐�
 *---------------------------------------------------------------------------*/
static void ConnectToAnybodyCallback(DWCError error, BOOL cancel, void* param)
{
#pragma unused(param)
    if (error == DWC_ERROR_NONE){
        if (!cancel){
            // ���m��ʐl�����Ƃ̃R�l�N�V�����ݗ�����
            MYDWC_DEBUGPRINT("�ڑ�����\n\n");
            setConnectionBuffer();
        }
        else {
            MYDWC_DEBUGPRINT("�L�����Z������\n");
            // ���O�C�����Ԃɖ߂�
            
            // 2006.7.4 yoshihara �C��
			finishcancel();	
        }
    }
    else {
        MYDWC_DEBUGPRINT("�}�b�`���O���ɃG���[���������܂����B %d\n\n", error);
		_dWork->state = MDSTATE_ERROR; 
    }
}

/*---------------------------------------------------------------------------*
  �F�B���w��}�b�`���O���v���C���[�]���R�[���o�b�N�֐�
 *---------------------------------------------------------------------------*/
static int  EvaluateAnybodyCallback(int index, void* param)
{
#pragma unused(param, index)
	return 1;
}


/** -------------------------------------------------------------------------
  ���M�����R�[���o�b�N  
  ---------------------------------------------------------------------------*/
static void SendDoneCallback( int size, u8 aid )
{
#pragma unused(size)
	// ���M�o�b�t�@��������
	_dWork->sendbufflag = 0;
	_dWork->sendintervaltime = 0;
//	MYDWC_DEBUGPRINT( "���M\n" );
//	OS_TPrintf( "*" );
}

/** -------------------------------------------------------------------------
  ��M�����R�[���o�b�N  
  ---------------------------------------------------------------------------*/
static void UserRecvCallback( u8 aid, u8* buffer, int size )
{
#pragma unused( aid, buffer, size )

//	OS_TPrintf("[%d,%d,%d,%d]", buffer[0], buffer[1], buffer[2], buffer[3]);

	u32 topcode;
	topcode = (buffer[3] << 24) | (buffer[2] << 16) | (buffer[1] << 8) | buffer[0];

	// ��x��M���Ă͂��߂ă^�C���A�E�g��ݒ肷��B
	_dWork->timeoutflag = 1;

	// �܂��A�擪�̂S�o�C�g���݂āA�Q�[���̏�񂩂ǂ����𔻒f
	if( (topcode & MYDWC_PACKETYPE_MASK) == MYDWC_GAME_PACKET ){
		if( topcode & MYDWC_PACKET_VCHAT_MASK ) 
		{
			// ����̃{�C�X�`���b�g�̓I��
			_dWork->opvchaton = 1;		
		}
		else
		{
			// ����̃{�C�X�`���b�g�̓I��
			_dWork->opvchaton = 0;		
		}
		
		// 2006.7.22 yoshihara�ǉ��B����̃V�[�P���XNo����є�тɂȂ��Ă��Ȃ����m�F
        // ���ʒʐM�r���ł͌��o�ł��Ȃ������̂ŃR�����g�ɕύX 7.28 k.ohno
//		GF_ASSERT( _dWork->firstflag == 1 || buffer[MYDWC_PACKET_SEQNO_POS] == (u8)( _dWork->opseqno + 1 ) );
        _dWork->firstflag = 0;
		_dWork->opseqno = buffer[MYDWC_PACKET_SEQNO_POS];
		
		
	}
	else {
#ifdef MYDWC_USEVCHA		
		if( myvct_checkData( aid, buffer,size ) ) return;
#endif	
		// ���Ӗ��ȏ��i�R�l�N�V������ێ����邽�߂̂��̂Ǝv����j
		if( topcode & MYDWC_PACKET_VCHAT_MASK ) 
		{
			// ����̃{�C�X�`���b�g�̓I��
			_dWork->opvchaton = 1;		
		}
		else
		{
			// ����̃{�C�X�`���b�g�̓I��
			_dWork->opvchaton = 0;		
		}		
		return;
	}
	MYDWC_DEBUGPRINT( "��M(%d)\n",*((s32*)buffer) );
	_dWork->s_param = *((s32*)buffer);
	
	// �A���C�����g���m���ɂ��邽�߂ɁA�R�s�[
	{
		u16 *temp = (u16*)mydwc_AllocFunc( NULL, size - 4, 4);
        if(temp==NULL){
            return;
        }
        
		MI_CpuCopy8(buffer + 4, (void*)temp, size - 4);
		
		if( DWC_GetMyAID() == 0 )
		{	
			// �������e�̏ꍇ�c�N���C���g����T�[�o�ɑ΂��đ����Ă������̂Ɣ��f�B
			// �T�[�o�p��M�֐����Ăяo���B
			if( _dWork->serverCallback != NULL ) _dWork->serverCallback(aid, temp, size-4);
		} else {
			// �T�[�o����N���C�A���g�ɑ΂��đ����Ă������̂Ɣ��f�B	
			if( _dWork->clientCallback != NULL ) _dWork->clientCallback(aid, temp, size-4);
		}
		
		mydwc_FreeFunc(NULL, temp, size - 4);
	}
}

/*---------------------------------------------------------------------------*
  �R�l�N�V�����N���[�Y�R�[���o�b�N�֐�
 *---------------------------------------------------------------------------*/
static void ConnectionClosedCallback(DWCError error,
                                     BOOL isLocal,
                                     BOOL isServer,
                                     u8  aid,
                                     int index,
                                     void* param)
{
#pragma unused(param, index)
    if (error == DWC_ERROR_NONE){

        if (!isLocal && isServer){
//            // �T�[�o�N���C�A���g�^�}�b�`���O�ŁA�������N���C�A���g�̎��ɁA
//            // �T�[�o���R�l�N�V�������N���[�Y�����B
        }
        
        if (DWC_GetNumConnectionHost() == 1){
            // �S�ẴR�l�N�V�������N���[�Y���ꂽ�ꍇ         
          
            // �L�����Z�����Ȃ�΁A�L�����Z�������������B
			if(	_dWork->state == MDSTATE_CANCEL )
			{
				_dWork->state = MDSTATE_CANCELFINISH;
			}
			else {
				_dWork->state = MDSTATE_DISCONNECT;
			}
			
			if( _dWork->isvchat )
			{
				// �܂��{�C�X�`���b�g���C�u������������Ă��Ȃ��ꍇ�B
				myvct_free();
			}
			
        }
        
        if (isLocal){
            MYDWC_DEBUGPRINT("Closed connection to aid %d (friendListIndex = %d) Rest %d.\n",
                       aid, index, DWC_GetNumConnectionHost());
        }
        else {
            MYDWC_DEBUGPRINT("Connection to aid %d (friendListIndex = %d) was closed. Rest %d.\n",
                       aid, index, DWC_GetNumConnectionHost());
        }
    }
    else {
        OS_TPrintf("Failed to close connections. %d\n\n", error);
    }
}

#ifdef CHEAK_HEAPSPACE
static int _heapspace = MYDWC_HEAPSIZE;
static int _heapmaxspace = MYDWC_HEAPSIZE;
#endif

/*---------------------------------------------------------------------------*
  �������m�ۊ֐�
 *---------------------------------------------------------------------------*/
void*
mydwc_AllocFunc( DWCAllocType name, u32   size, int align )
{
#pragma unused( name )
    void * ptr;
    OSIntrMode old;

#ifdef _WIFI_DEBUG_TUUSHIN
#ifdef DEBUGPRINT_ON
    OS_TPrintf("HEAP�擾(%d, %d) from %p %x\n", size, align, _dWork->headHandle, _dWork->headHandle->signature);
#endif
#endif
    
    old = OS_DisableInterrupts();
    ptr = NNS_FndAllocFromExpHeapEx( _dWork->headHandle, size, align );

    if(ptr == NULL){
#ifdef _WIFI_DEBUG_TUUSHIN
//        GF_ASSERT_MSG(ptr,"HEAP faqiled");
#endif
        // �q�[�v�������ꍇ�̏C��
        CommStateSetError(COMM_ERROR_RESET_SAVEPOINT);  // �G���[�ɂ���
        OS_RestoreInterrupts( old );
        return NULL;//sys_AllocMemory(HEAPID_COMMUNICATION,size);  // �j�Z���m�����܂�ARM9�ǂ܂�𔭐������Ȃ�
    }

    
#ifdef CHEAK_HEAPSPACE
#ifdef _WIFI_DEBUG_TUUSHIN
    {
		int hspace = NNS_FndGetTotalFreeSizeForExpHeap( _dWork->headHandle );
		if( hspace < _heapspace )
		{
			OS_TPrintf("�q�[�v�c��F%d\n", hspace);
			_heapspace = hspace;
		}
	}
	{
		int maxspace = NNS_FndGetAllocatableSizeForExpHeap( _dWork->headHandle );
		if( maxspace < _heapmaxspace )
		{
			OS_TPrintf("�q�[�v�c��F%d\n", maxspace);
			_heapmaxspace = maxspace;
		}		
	}
#endif	
#endif	
    OS_RestoreInterrupts( old );
#ifdef DEBUGPRINT_ON
//	OS_TPrintf("dwc_rap:�q�[�v�擾�isize = %d�j�F�c��%d\n", size, NNS_FndGetTotalFreeSizeForExpHeap( _dWork->headHandle ) );
#endif
    return ptr;
}

/*---------------------------------------------------------------------------*
  �������J���֐�
 *---------------------------------------------------------------------------*/
void
mydwc_FreeFunc( DWCAllocType name, void* ptr,  u32 size  )
{
#pragma unused( name, size )
    OSIntrMode old;

    if ( !ptr ) return;
//    OS_TPrintf("HEAP���(%p) to %p\n", ptr, _dWork->headHandle);    
    old = OS_DisableInterrupts();
    NNS_FndFreeToExpHeap( _dWork->headHandle, ptr );
    OS_RestoreInterrupts( old );
}

//==============================================================================
/**
 * �G���[���N�����Ă��Ȃ����`�F�b�N���A�G���[�ɉ����ĒʐM��������鏈��������B
 *  ���E�����A���E�o�g���^���[�ŌĂяo�����߂ɑ������� k.ohno 06.06.08
 * @retval  �O�c�G���[�Ȃ��B���c�G���[
 * �i�G���[�R�[�h���Ԃ�B�G���[�R�[�h�O�̏ꍇ��ERRORCODE_0�j
 */
//==============================================================================
int mydwc_HandleError(void)
{
	int errorCode;
	DWCErrorType myErrorType;
	int ret;
	

#ifdef _WIFI_DEBUG_TUUSHIN
    if(_dWork){
        OSIntrMode old;
        // �q�[�v�e�X�g
        old = OS_DisableInterrupts();
        NNS_FndVisitAllocatedForExpHeap(_dWork->headHandle, _NNSFndHeapVisitor, _USER_PARAM_MAGIC);
        OS_RestoreInterrupts( old );
    }
#endif

    ret = DWC_GetLastErrorEx( &errorCode, &myErrorType );

	if( ret != 0 )
	{
		// ���炩�̃G���[�������B
		OS_TPrintf("error occured!(%d, %d, %d)\n", ret, errorCode, myErrorType); 	
		
		switch(myErrorType)
		{
			case DWC_ETYPE_LIGHT:
				// �Q�[���ŗL�̕\���݂̂ŁA�G���[�R�[�h�\���͕K�v�Ȃ��B
				// DWC_ClearError()���Ăяo���΁A���A�\�B
				DWC_ClearError();
                if(ret >= DWC_ERROR_FRIENDS_SHORTAGE) return ret; // �y�x�̃G���[�͂��̂܂ܕԂ� k.ohno
				if( errorCode == 0 ) return ERRORCODE_0;
				break;
			case DWC_ETYPE_SHUTDOWN_FM:
				// DWC_ShutdownFriendsMatch()���Ăяo���āAFriendsMatch�������I������K�v������B
				// �G���[�R�[�h�̕\�����K�v�B
				// ���̏ꍇ�A�Ƃ肠����DWC_ETYPE_DISCONNECT�Ɠ������������Ă����B
			case DWC_ETYPE_DISCONNECT:
				//FriendsMatch�������Ȃ�DWC_ShutdownFriendsMatch()���Ăяo���A
				//�X��DWC_CleanupInet()�ŒʐM�̐ؒf���s���K�v������B
				//�G���[�R�[�h�̕\�����K�v�B 
				if(_dWork){
					switch( _dWork->state )
					{			
						case MDSTATE_TRYLOGIN:
						case MDSTATE_LOGIN:		
						case MDSTATE_MATCHING:
						case MDSTATE_CANCEL:
						case MDSTATE_MATCHED:
						case MDSTATE_CANCELFINISH:
						case MDSTATE_ERROR:
						case MDSTATE_TIMEOUT:
						case MDSTATE_DISCONNECTTING:
						case MDSTATE_DISCONNECT:
							DWC_ShutdownFriendsMatch(  );
						case MDSTATE_INIT:	
						case MDSTATE_CONNECTING:
						case MDSTATE_CONNECTED:
							// �܂����̎��_�ł́A�t�����h�}�b�`���C�u�����͌Ă΂�Ă��Ȃ��B
							DWC_CleanupInet( );
					}
					
					DWC_ClearError();
				}
				if(_dWork){
                    _dWork->state = MDSTATE_ERROR_DISCONNECT;
                }
				if( errorCode == 0 ) return ERRORCODE_0;
				return errorCode;
				
			case DWC_ETYPE_FATAL:
				// FatalError�����Ȃ̂ŁA�d��OFF�𑣂��K�v������B
				if(_dWork){
                    _dWork->state = MDSTATE_ERROR_FETAL;
				// ���̃R�[���o�b�N���珈�����������Ă��Ȃ��͂��B
                    if( _dWork->fetalErrorCallback != NULL ){
                        _dWork->fetalErrorCallback( -errorCode );
                    }
                }
				
				if( errorCode == 0 ) return ERRORCODE_0;
				return errorCode;
				break;
		}
	}

    if(_dWork->bHeapError){
        return ERRORCODE_HEAP;        
    }
	return 0;
}

static int _buffer;

static void _sendData(int param)
{
	_buffer = param;
	if( !DWC_IsSendableReliable( _dWork->op_aid ) ) // ���M�o�b�t�@���`�F�b�N�B
	{
		DWC_SendReliable( _dWork->op_aid, &(_buffer), 4 );
	}	
}

#ifdef YOSHIHARA_VCHAT_ONOFFTEST		

static u16 debug_trg;
static u16 debug_cont = 0;

static void vchat_onoff()
{
	{
	    u16 ReadData = PAD_Read();
	    debug_trg  = (u16)(ReadData & (ReadData ^ debug_cont));            // �g���K ����
	    debug_cont = ReadData;      	
	}	
	
	if( debug_trg & PAD_BUTTON_R )
	{
		if( _dWork->myvchaton )
		{
			mydwc_VChatPause();
		}
		else
		{
			mydwc_VChatRestart();
		}
	}
}

#endif

static void sendKeepAlivePacket()
{
	
    OS_TPrintf("keep   %d %d\n",_dWork->sendbufflag,DWC_IsSendableReliable( 1-DWC_GetMyAID() ) );
    
	if( (_dWork->sendbufflag == 0) && DWC_IsSendableReliable( 1-DWC_GetMyAID() ) ) // ���M�o�b�t�@���`�F�b�N�B
	{
		_dWork->sendbufflag = 1;
		*((u32*)&(_dWork->sendBuffer[0])) = MYDWC_KEEPALIVE_PACKET | (_dWork->myvchaton << MYDWC_PACKET_VCHAT_SHIFT);;
		DWC_SendReliable( _dWork->op_aid, &(_dWork->sendBuffer[0]), 4);
		_dWork->sendintervaltime = 0;
		OS_TPrintf("SEND KEEP ALIVE PACKET\n");	
	}	
}

// �ʐM�m����A���t���[���Ăяo���Ă��������B
//==============================================================================
/**
 * DWC�ʐM�����X�V���s��
 * @param none
 * @retval 0�c����, ���c�G���[���� 1�c�^�C���A�E�g 2�c���肩��ؒf���ꂽ
 */
//==============================================================================
int mydwc_step()
{
	DWC_ProcessFriendsMatch();  // DWC�ʐM�����X�V
	mydwc_updateFriendInfo( );	
	
#ifdef MYDWC_USEVCHA
	if( _dWork->isvchat ) 
	{
#ifdef YOSHIHARA_VCHAT_ONOFFTEST		
		vchat_onoff();
#endif		
		if( _dWork->myvchaton == 1 && _dWork->opvchaton == 1 )
		{
			myvct_onVchat();
		}
		else
		{
			myvct_offVchat();
		}
				
		myvct_main();
	}
#endif
	if( _dWork->state == MDSTATE_TIMEOUT ) return 1;
	if( _dWork->state == MDSTATE_DISCONNECT ) return 2;
	
	if( _dWork->state == MDSTATE_MATCHED ) 
	{
		if( _dWork->sendintervaltime++ >= KEEPALIVE_TOKEN_TIME && _dWork->sendbufflag == 0) 
		{
			sendKeepAlivePacket();
		}
	}
	
	return mydwc_HandleError();
}

//==============================================================================
/**
 * aid��Ԃ��܂��B�ڑ�����܂ł�-1��Ԃ��܂��B
 * @retval  aid�B�������ڑ��O��-1
 */
//==============================================================================
int mydwc_getaid()
{
    if(_dWork){
        if( _dWork->state == MDSTATE_MATCHED || _dWork->state == MDSTATE_DISCONNECTTING )
        {
            return DWC_GetMyAID();
        }
    }
	return -1;
}

// �{�C�X�`���b�g�̐ؒf�R�[���o�b�N�B
static void vct_endcallback(){
	_dWork->isvchat = 0;
}

//==============================================================================
/**
 * �ʐM�m����A�{�C�X�`���b�g���J�n���܂��B
 * @param none
 * @retval none
 */
//==============================================================================
void mydwc_startvchat()
{
	switch( _dWork->vchatcodec ){
		case VCHAT_G711_ULAW:
			myvct_init( _dWork->heapID, VCT_CODEC_G711_ULAW );
		break;
		case VCHAT_2BIT_ADPCM:
			myvct_init( _dWork->heapID, VCT_CODEC_2BIT_ADPCM );
		break;
		case VCHAT_3BIT_ADPCM:
			myvct_init( _dWork->heapID, VCT_CODEC_3BIT_ADPCM );
		break;
		case VCHAT_4BIT_ADPCM:		
			myvct_init( _dWork->heapID, VCT_CODEC_4BIT_ADPCM );
		break;
		default:
			myvct_init( _dWork->heapID, VCT_CODEC_4BIT_ADPCM );   //VCT_CODEC_8BIT_RAW
		break;
	}
	myvct_setDisconnectCallback( vct_endcallback );
	_dWork->isvchat = 1;
}

//==============================================================================
/**
 * �{�C�X�`���b�g�̃R�[�f�b�N���w�肵�܂��B
 * �R�l�N�V�����m���O�ɃR�[�f�b�N���w�肵�Ă����ƁA
 * �R�l�N�V�����m�����Ɏ����I�Ƀ{�C�X�`���b�g���J�n���܂��B
 * @param �R�[�f�b�N�̃^�C�v
 * @retval none
 */
//==============================================================================
void mydwc_setVchat(int codec){
	_dWork->vchatcodec = codec;

	if( _dWork->isvchat ){
		switch( _dWork->vchatcodec ){
			case VCHAT_G711_ULAW:
				myvct_setCodec( VCT_CODEC_G711_ULAW );
			break;
			case VCHAT_2BIT_ADPCM:
				myvct_setCodec( VCT_CODEC_2BIT_ADPCM );
			break;
			case VCHAT_3BIT_ADPCM:
				myvct_setCodec( VCT_CODEC_3BIT_ADPCM );
			break;
			case VCHAT_4BIT_ADPCM:		
				myvct_setCodec( VCT_CODEC_4BIT_ADPCM );
			break;
			case VCHAT_8BIT_RAW:
				myvct_setCodec( VCT_CODEC_8BIT_RAW );
			break;
		}
	}
}

//==============================================================================
/**
 * DWC�G���[�ԍ��ɑΉ����郁�b�Z�[�W��ID��Ԃ��܂��B
 * @param code - �G���[�R�[�h�i���̒l�����Ă�������
 * @retval ���b�Z�[�W�^�C�v
 */
//==============================================================================
int mydwc_errorType(int code)
{
	int code100 = code / 100;
	if( code == 20100 ) return 0;
	if( code >= 20102 && code <= 20107 ) return 0;
	if( code == 20109 ) return 0;
	if( code >= 20111 && code <= 20999 ) return 0;
	if( code >= 52004 && code <= 52098 ) return 0;
	if( code >= 52104 && code <= 52198 ) return 0;
	if( code >= 52204 && code <= 52298 ) return 0;
	if( code100 == 523 ) return 0;
	if( code100 == 530 ) return 0;
	if( code100 == 531 ) return 0;
	if( code100 == 532 ) return 0;

    if( code == 20101 ) return 1;
	if( code / 1000 == 23 ) return 1;

	if( code == 20108 ) return 2;

	if( code == 20110 ) return 3;

	if( code100 == 512 ) return 4;

	if( code100 == 500 ) return 5;
    
	if( code == 51099 ) return 6;
	if( code >= 51100 && code <= 51102 ) return 6;
	if( code >= 51104 && code <= 51198 ) return 6;
	if( code >= 51300 && code <= 51398 ) return 6;

	if( code == 51103 ) return 7;

	if( code >= 52000 && code <= 52003 ) return 8;
	if( code >= 52100 && code <= 52103 ) return 8;
	if( code >= 52200 && code <= 52203 ) return 8;

	if( code == 80430 ) return 9;

	if( code >= 60000 && code < 99999 ) return 10;

    if( code < 10000 ) return 11; // �G���[�R�[�h���P�O�O�O�O�ȉ��̏ꍇ�́A�G���[�R�[�h�̕\���̕K�v���Ȃ��B

    return -1;
}

//==============================================================================
/**
 * �ʐM��ؒf���܂��B
 * @param sync �c 0 = ��������ؒf���ɂ����B1 = ���肪�ؒf����̂�҂B
 * @retval �@�@�@ 1 = �ڑ����������B0 = �ؒf�������B
 */
//==============================================================================
int mydwc_disconnect( int sync )
{
	if( sync == 0 ){
        OS_TPrintf(" state %d \n",_dWork->state);
		switch( _dWork->state )
		{
            case MDSTATE_MATCHING:   // k.ohno 06.07.08  �ǉ�
            case MDSTATE_MATCHED:
			{
				if( _dWork->isvchat )
				{
					// �{�C�X�`���b�g�ғ���
					// �~�߂�
                    OS_TPrintf("�{�C�X�`���b�g�ғ��� �~�߂�\n");
					myvct_endConnection();
					_dWork->state = MDSTATE_DISCONNECTTING;
				}
                else{// �ғ����Ė����Ȃ�I��
					DWC_CloseAllConnectionsHard( );
					_dWork->state = MDSTATE_DISCONNECT;
                    return 1;
                }
				break;
			}	
	
			case MDSTATE_DISCONNECTTING:
			{
				// �{�C�X�`���b�g�̏I����҂��Ă�����
				if( _dWork->isvchat == 0 )
				{
					// �{�C�X�`���b�g�̐ؒf�����B
					// �ʐM���̂�؂�B
                    OS_TPrintf("�{�C�X�`���b�g�̐ؒf�����B\n");
					DWC_CloseAllConnectionsHard( );
					_dWork->state = MDSTATE_DISCONNECT;
					return 1;
				}
//                else{
//					myvct_endConnection();  //�ؒf���� k.ohno  �����ł͌Ă΂Ȃ��悤�ɏC��
//                }
				break;
			}	
            case MDSTATE_LOGIN:     //�e�@�ؒf���ɓ��������킹�邽�߂ɒǉ� k.ohno 06.07.04
            case MDSTATE_ERROR_DISCONNECT:
			case MDSTATE_DISCONNECT:
			case MDSTATE_TIMEOUT:
			{
				return 1;
				break;
			}
		}
	} else {
		switch( _dWork->state )
		{
            case MDSTATE_LOGIN:     //�e�@�ؒf���ɓ��������킹�邽�߂ɒǉ� k.ohno 06.07.04
			case MDSTATE_DISCONNECT:
			case MDSTATE_TIMEOUT:
			{
				return 1;
				break;
			}			
		}		
	}
	
	return 0;
}

//==============================================================================
/**
 * �ʐM���ؒf������A���̊֐����ĂԂ��Ƃœ�����Ԃ����O�C������̏�Ԃɂ��܂��B
 * @param 	nonte
 * @retval  1 = �����B0 = ���s�B
 */
//==============================================================================
int mydwc_returnLobby()
{
    if( _dWork->state == MDSTATE_DISCONNECT || _dWork->state == MDSTATE_TIMEOUT ) {
        _dWork->op_aid = -1;
        _dWork->state = MDSTATE_LOGIN;
        _dWork->newFriendConnect = -1;
        return 1;
	 }
	 return 0;
}

//==============================================================================
/**
 * fetal error�������ɌĂ΂��֐��A���̃R�[���o�b�N�̒��ŏ������Ƃ߂ĉ������B
 * @param 	nonte
 * @retval  1 = �����B0 = ���s�B
 */
//==============================================================================
void mydwc_setFetalErrorCallback( void (*func)(int) )
{
    if(_dWork){
        _dWork->fetalErrorCallback = func;
    }
}



//-----2006.04.11 k.ohno
//==============================================================================
/**
 * ���O�A�E�g����
 * @param 	none
 * @retval  none
 */
//==============================================================================

void mydwc_Logout(void)
{
    DWC_ShutdownFriendsMatch();
    DWC_CleanupInet();
    myvct_free();
    mydwc_free();
}


//==============================================================================
/**
 * �I�����C���̗F�B���T�[�o�ɃA�b�v���Ă�����������߂�z����w�肵�܂��B
 * ���̔z���mydwc_step, mydwc_stepmatch���Ăяo�����ۂɍX�V�����\��������܂��B
 * @param 	array - �f�[�^�������߂�z��̐擪
 * @param 	size  - ��l������̃f�[�^�T�C�Y
 * @retval  none
 */
//==============================================================================
void mydwc_setFriendStateBuffer( void *array, int size )
{
	_dWork->friendinfo = array;	
	_dWork->infosize = size;
	

}

// FRIENDINFO_UPDATA_PERFRAME�l���̃f�[�^���X�V����B
static void mydwc_updateFriendInfo( )
{
	int i;
	if( _dWork->friendinfo == NULL ) return;
	for(i = 0; i < FRIENDINFO_UPDATA_PERFRAME; i++)
	{
		int index = _dWork->friendupdate_index % FRIENDLIST_MAXSIZE;
		int size;
	
		if( DWC_IsBuddyFriendData( &(_dWork->keyList[index]) ) ) 
		{
			_dWork->friend_status[index] = 
				DWC_GetFriendStatusData( 
					&_dWork->keyList[ index ], 
					(void *)(((u32)_dWork->friendinfo) + _dWork->infosize * index),
					&size
				);
				
			if( size > _dWork->infosize )
			{
				OS_TPrintf("\n!!!!!!!!!!!!!!!size > _dWork->infosize!!!!!!!!!!!!!!!!\n");
			}
		}
			
		_dWork->friendupdate_index = (_dWork->friendupdate_index + 1) % FRIENDLIST_MAXSIZE;
	}
}

//==============================================================================
/**
 * �����̏�Ԃ��T�[�o�ɃA�b�v���܂��B
 * @param 	data - �f�[�^�ւ̃|�C���^
 * @param 	size  - �f�[�^�T�C�Y
 * @retval  �����̉�
 */
//==============================================================================
BOOL mydwc_setMyInfo( const void *data, int size )
{
	OS_TPrintf("upload status change(%p, %d)\n", data, size);
	return DWC_SetOwnStatusData( data, size );
}

//==============================================================================
/**
 * �F�B���T�[�o�ɃA�b�v���Ă�������擾���܂��i���[�J���ɃL���b�V�����Ă�����̂�\�����܂��j�B
 * @param 	index �t�����h���X�g��̔ԍ�
 * @retval  �f�[�^�ւ̃|�C���^�B���g�͏��������Ȃ��ŉ������B
 */
//==============================================================================
void *mydwc_getFriendInfo( int index )
{
	return (void *)(((u32)_dWork->friendinfo) + _dWork->infosize * index);
}

//==============================================================================
/**
 * �F�B���T�[�o�ɃA�b�v���Ă�������擾���܂��i���[�J���ɃL���b�V�����Ă�����̂�\�����܂��j�B
 * @param 	index �t�����h���X�g��̔ԍ�
 * @retval  �F�B�̏�ԁBDWC_GetFriendStatusData�̕Ԃ�l�Ɠ���
 */
//==============================================================================
u8 mydwc_getFriendStatus( int index )
{
	return _dWork->friend_status[index];
}


static void SetupGameServerCallback(DWCError error, BOOL cancel, BOOL self, BOOL isServer, int  index, void* param);
static void ConnectToGameServerCallback(DWCError error, BOOL cancel, BOOL self, BOOL isServer, int  index, void* param);
static void NewClientCallback(int index, void* param);

//==============================================================================
/**
 * �Q�[����W�E�Q�����s���֐��B
 * @target   ���c�����ŃQ�[�����J�ÁB�O�ȏ�c�ڑ����ɍs������́A�t�����h���X�g��̈ʒu
 * @retval  ���c�����B�O�c���s�B
 */
//==============================================================================
int mydwc_startgame( int target )
{
	if( _dWork->state != MDSTATE_LOGIN ) return 0;

	_dWork->friendindex = target;

	if ( target < 0 ){
	    DWC_SetupGameServerAsync(
	    	(u8)2,			// ��l�ΐ����
	        SetupGameServerCallback,
	        NULL,
	        NewClientCallback,
	        NULL
	    );
	    
	    _dWork->matching_type = MDTYPE_PARENT;
    } else {
        DWC_ConnectToGameServerAsync(target,
                                     ConnectToGameServerCallback,
                                     NULL,
                                     NewClientCallback,
                                     NULL);	    
                                     
	    _dWork->matching_type = MDTYPE_CHILD;
    }

                              
    _dWork->state = MDSTATE_MATCHING;
  
    // ���M�R�[���o�b�N�̐ݒ�	
    DWC_SetUserSendCallback( SendDoneCallback ); 

    // ��M�R�[���o�b�N�̐ݒ�	
    DWC_SetUserRecvCallback( UserRecvCallback ); 
    
    // �R�l�N�V�����N���[�Y�R�[���o�b�N��ݒ�
    DWC_SetConnectionClosedCallback(ConnectionClosedCallback, NULL);
    
    // �^�C���A�E�g�R�[���o�b�N�̐ݒ�
    DWC_SetUserRecvTimeoutCallback( recvTimeoutCallback );
    
    _dWork->sendbufflag = 0;
    
	// �e�X�g�p
	_dWork->s_param = 0;    

    
    return 1;    
}

//==============================================================================
/**
 * ���ڑ����Ă���F�B�̃t�����h���X�g��̈ʒu��Ԃ��܂��B
 * �܂��A�ڑ����������Ă��Ȃ��Ă��F�B�ԍ���Ԃ����Ƃ�����܂��̂ŁA�ڑ���
 * �����������̔���ɂ͎g��Ȃ��ł��������B
 * @retval  �O�ȏ�c�F�B�ԍ��B�|�P�c�܂��ڑ����ĂȂ��B
 */
//==============================================================================
int mydwc_getFriendIndex()
{
    if(_dWork){
        // ���ڑ����Ă���F�B�̃t�����h���X�g��̈ʒu��Ԃ��܂��B
        return _dWork->friendindex;
    }
    return -1;
}
/*---------------------------------------------------------------------------*
  �Q�[���T�[�o�N���R�[���o�b�N�֐�
 *---------------------------------------------------------------------------*/
static void SetupGameServerCallback(DWCError error,
                                    BOOL cancel,
                                    BOOL self,
                                    BOOL isServer,
                                    int  index,
                                    void* param)
{
#pragma unused(isServer, param, index)
    if (error == DWC_ERROR_NONE){
        if (!cancel){
            // �l�b�g���[�N�ɐV�K�N���C�A���g���������
            OS_TPrintf("�F�B���ڑ����Ă��܂����B�i�C���f�b�N�X��%d�j\n", index);
			_dWork->friendindex = index;
            // �o�b�t�@�̊m��
            setConnectionBuffer();
        }
        else 
        {
            if (self){
                // �������}�b�`���O���L�����Z������
                OS_TPrintf("�}�b�`���O�̃L�����Z�����������܂����B\n\n");
	            // ���O�C�����Ԃɖ߂�
//				s_dwcstate = MYDWCSTATE_MATCH_CANCELFINISH;  
            }
            else {
                // �q���ł����q�@���A�ڑ����L�����Z�������B
                OS_TPrintf("Client (friendListIndex = %d) canceled matching.\n\n", index);
                // �q���ł����q�@�����Ȃ��Ȃ����B2006.7.3 yoshihara
                _dWork->newFriendConnect = -1;
            }
        }
    }
    else {
        // �G���[�����������B�G���[�R�[�h�́Astep�֐��̒��ŏE���B
        OS_TPrintf("Game server error occured. %d\n\n", error);

//        s_dwcstate = MYDWCSTATE_MATCH_CANCELFINISH; 
    }
}

/*---------------------------------------------------------------------------*
  �Q�[���T�[�o�ڑ��R�[���o�b�N�֐�
 *---------------------------------------------------------------------------*/
static void ConnectToGameServerCallback(DWCError error,
                                        BOOL cancel,
                                        BOOL self,
                                        BOOL isServer,
                                        int  index,
                                        void* param)
{
#pragma unused(param)
    if (error == DWC_ERROR_NONE){
        if (!cancel){
            if (self){
                // �������Q�[���T�[�o�Ƃ����ɂł��Ă���l�b�g���[�N�ւ̐ڑ���
                // ���������ꍇ
                OS_TPrintf("�ڑ��ɐ������܂���\n\n");
            }
            else {
                // �l�b�g���[�N�ɐV�K�N���C�A���g����������ꍇ�B
                // ��l�ΐ����Ȃ̂ŁA�����ɂ͂��Ȃ��͂��B
            }

            // ��M�o�b�t�@�Z�b�g
            setConnectionBuffer();
        }
        else {
            if (self){
                // �������}�b�`���O���L�����Z������
                OS_TPrintf("�L�����Z�����������܂����B\n\n");
                // ���O�C�����Ԃɖ߂�
//                s_dwcstate = MYDWCSTATE_MATCH_CANCELFINISH;  
            }
            else {
                if (isServer){
                    // �Q�[���T�[�o���}�b�`���O���L�����Z������
                    OS_TPrintf("�e���ڑ����L�����Z�����܂���\n\n");
                    // �}�b�`���O���I�����ă��O�C�����Ԃɖ߂�
//                    s_dwcstate = MYDWCSTATE_MATCH_CANCELFINISH;
                }
                else {
                    // ���̃N���C�A���g���}�b�`���O���L�����Z�������B
                    // ��l�ΐ�Ȃ炱���ɂ��Ȃ��͂��B
                }
            }
        }
    }
    else {
        // �G���[�����������B�G���[�R�[�h�́Astep�֐��̒��ŏE���B
        OS_TPrintf("Game server error occured. %d\n\n", error);

        // ������x�ŏ�����B������������
//        s_dwcstate = MYDWCSTATE_MATCH_ERRORFINISH; 
    }

//    s_blocking = 0;
}

/*---------------------------------------------------------------------------*
  �T�[�o�N���C�A���g�^�}�b�`���O���̐V�K�ڑ��N���C�A���g�ʒm�R�[���o�b�N�֐�
 *---------------------------------------------------------------------------*/
static void NewClientCallback(int index, void* param)
{
#pragma unused(param)
    // �V�K�ڑ��N���C�A���g�̐ڑ��������I���܂ł́A
    // �R���g���[��������֎~����
//    s_blocking = 1;

    _dWork->newFriendConnect = index;
    
    OS_TPrintf("�V�����l���ڑ����Ă��܂����B\n");
    if (index != -1){
        OS_TPrintf("�F�B[%d].\n", index);
    }
    else {
        OS_TPrintf("�F�B�ł͂Ȃ�.\n");
    }
}

//==============================================================================
/**
 * �����̃m�C�Y�J�b�g���x���𒲐����܂��i�O������A�N�Z�X�������̂ŁA������Ɂj
 * @param   d �c �����臒l�������邩�A�グ�邩�i������قǏE���₷���Ȃ�j
 * @retval  none
 */
//==============================================================================
void mydwc_changeVADLevel(int d)
{
//	myvct_changeVADLevel(d);
}

//==============================================================================
/**
 * ���݂̃t�����h���X�g��\�����܂��B�i�f�o�b�O�p�j
 * @param 	none
 * @retval  none
 */
//==============================================================================
void mydwc_showFriendInfo()
{
	int i;
	
	if( !DWC_CheckHasProfile( _dWork->myUserData ) ) 
	{
		DWCFriendData token;
		u32 *ptr;

		DWC_CreateExchangeToken( _dWork->myUserData, &token ); 
		ptr = (u32*)&token;
		OS_TPrintf("�܂��A�v���t�@�C���h�c�擾�O\n���O�C���h�c:(%d, %d, %d)\n\n", ptr[0], ptr[1], ptr[2] );		
	}
	else
	{
		// �ڑ��ς�	
		DWCFriendData token;
		DWC_CreateExchangeToken( _dWork->myUserData, &token );
		OS_TPrintf("�v���t�@�C���h�c:%d \n\n", DWC_GetGsProfileId( _dWork->myUserData, &token ) );	
	}
	
	for( i = 0; i < FRIENDLIST_MAXSIZE; i++ )
	{
		int ret = DWC_GetFriendDataType( &(_dWork->keyList[i]) );
		u32 *ptr = (u32*)(&_dWork->keyList[i]);
		switch(ret)
		{
			case DWC_FRIENDDATA_LOGIN_ID:
				OS_TPrintf("%d:���O�C���h�c:(%d, %d, %d)",i, ptr[0], ptr[1], ptr[2] );
				break;

			case DWC_FRIENDDATA_FRIEND_KEY:
				OS_TPrintf("%d:�t�����h�R�[�h:(%d)", i, DWC_GetGsProfileId( _dWork->myUserData, &_dWork->keyList[i] ) );			
				break;

			case DWC_FRIENDDATA_GS_PROFILE_ID:
				OS_TPrintf("%d:�v���t�@�C���h�c:(%d)", i, DWC_GetGsProfileId( _dWork->myUserData, &_dWork->keyList[ i ]) );
				break;

			case DWC_FRIENDDATA_NODATA:
			default:
				OS_TPrintf("%d:��", i);
				break;
		}			
		
		if( DWC_IsBuddyFriendData( &(_dWork->keyList[i]) ) )
		{
			OS_TPrintf("(���v��)");
		}
		OS_TPrintf("\n");
	}
}


// ���M�������ǂ�����Ԃ��܂�
BOOL mydwc_IsSendVoiceAndInc(void)
{
    return myvct_IsSendVoiceAndInc();
}


//==============================================================================
/**
 * �{�C�X�`���b�g��Ԃ��ǂ�����Ԃ��܂�   k.ohno 06.05.23 07.22 �t���O������
 * @retval  TRUE�c�{�C�X�`���b�g   FALSE�c�{�C�X�`���b�g�ł͂Ȃ� 
 */
//==============================================================================
BOOL mydwc_IsVChat(void)
{
    if(_dWork){
        return _dWork->bVChat;
    }
    return FALSE;
}

//==============================================================================
/**
 * �ڑ����Ă������ǂ�����Ԃ��܂�    k.ohno 06.05.24
 * @retval  TRUE�c�ڑ��J�n�Ȃ̂ŃL�[������u���b�N   FALSE�c
 */
//==============================================================================
BOOL mydwc_IsNewPlayer(void)
{
    if(_dWork){
        return _dWork->newFriendConnect;
    }
    return FALSE;
}

//==============================================================================
/**
 * �ڑ����Ă������ǂ����t���O�𗎂Ƃ��܂� k.ohno 06.08.04
 * @retval  none
 */
//==============================================================================
void mydwc_ResetNewPlayer(void)
{
    if(_dWork){
        _dWork->newFriendConnect = -1;
    }
}

//==============================================================================
/**
 * �x����ONOFF     k.ohno 06.05.30
 */
//==============================================================================
BOOL mydwc_toggleDelay(void)
{
    _dWork->bDelay = 1 - _dWork->bDelay;
    return _dWork->bDelay;
}

//==============================================================================
/**
 * VCHAT��ONOFF     k.ohno 06.05.24
 */
//==============================================================================
void mydwc_setVChat(BOOL bVChat)
{
    _dWork->bVChat = bVChat;
}

static void sendPacket()
{
	if( _dWork->sendbufflag || !DWC_IsSendableReliable( DWC_GetMyAID() ) ) // ���M�o�b�t�@���`�F�b�N�B
	{
		_dWork->sendbufflag = 1;
		*((u32*)&(_dWork->sendBuffer[0])) = MYDWC_KEEPALIVE_PACKET | (_dWork->myvchaton << MYDWC_PACKET_VCHAT_SHIFT);;
		DWC_SendReliable( _dWork->op_aid, &(_dWork->sendBuffer[0]), 4);
		_dWork->sendintervaltime = 0;
	}
}

void mydwc_VChatPause()
{
	if( _dWork->myvchaton != 0 )
	{
		_dWork->myvchaton = 0;
		sendPacket();
	}
}

void mydwc_VChatRestart()
{
	if( _dWork->myvchaton != 1 )
	{
		_dWork->myvchaton = 1;
		sendPacket();
	}
}