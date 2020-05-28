//=============================================================================
/**
 * @file	dwc_test.c
 * @bfief	DWC���b�p�[�̃e�X�g�p
 * @date	06/02/24
 */
//=============================================================================

#include "common.h"
#include "wifi/dwc_test.h"
#include "wifi/dwc_rap.h"

#define MYDWC_HEAPID HEAPID_COMMUNICATION

#define SERVERBUF_SIZE 16

typedef struct{
	u32 aid;
	u32 data;
} T_SERVERCOM;

typedef struct
{
	// �T�[�o�ɗ��܂��Ă���f�[�^�̃L���[
	T_SERVERCOM serverbuf[SERVERBUF_SIZE];
	
	int start;			// �L���[�̐擪
	int end;			// �L���[�̍Ō�
	
	int state;
	int heapID;
	
	int ret;			// �ڑ����
	
	MATHRandContext16 context;
	int index;
} DWCTEST_WORK;

static DWCTEST_WORK *_testWork;

enum {
	DWCTESTSTATE_INIT,
	DWCTESTSTATE_CONNECTING,
	DWCTESTSTATE_LOGIN,
	DWCTESTSTATE_MATCHING,
	DWCTESTSTATE_CANCELING,
	DWCTESTSTATE_CONNECT,
	DWCTESTSTATE_DISCONNECTING,
	DWCTESTSTATE_END,	
	DWCTESTSTATE_DISCONNECTED,
		
	DWCTESTSTATE_ERROR,
	DWCTESTSTATE_LAST
};

static void serverCallback(u16 aid, u16 *data, u16 size);
static void clientCallback(u16 aid, u16 *data, u16 size);
static void testMain();
static void fetal_error( int errorcode );

static u32 getRand32()
{
	u32 buffer[8];
	u32 ans;
	MATHCRC32Table table;
	MATH_CRC32InitTable( &table );

	OS_GetLowEntropyData( buffer );
	ans = MATH_CalcCRC32( &table, buffer, sizeof(buffer) );
	OS_TPrintf("my id = %d\n", ans);
	return ans;
}


void dwctest_init( int heapID )
{
	_testWork = (DWCTEST_WORK *) sys_AllocMemory( heapID, sizeof(DWCTEST_WORK) );
	_testWork->start = 0;
	_testWork->end = 0;
	_testWork->state = DWCTESTSTATE_INIT;
	_testWork->index = 0;
	_testWork->heapID = heapID;
	
	MATH_InitRand16( &_testWork->context, getRand32() );
}

static void dwctest_reinit(){
	_testWork->start = 0;
	_testWork->end = 0;
	_testWork->state = DWCTESTSTATE_INIT;
	_testWork->index = 0;
}

static const char* _mesType[] = {
	// �G���[�R�[�h���P�O�O�O�O�ȉ��̏ꍇ�́A�G���[�R�[�h�̕\���̕K�v���Ȃ��B
	"Wi-Fi�R�l�N�V������ �ڑ��ł��܂���B �ڂ����͎戵�������� �������������B�i�G���[�R�[�h%d�j",
	"���q�l��Wi-Fi�R�l�N�V����ID�͒����� �g�p����Ȃ��������ߍ폜����܂����B �ڂ����͎戵���������������������B�i�G���[�R�[�h%d�j",
	"���̃\�t�g�� Wi-Fi�R�l�N�V�����T�[�r�X�� �I�����܂����B �����p���肪�Ƃ��������܂����B�i�G���[�R�[�h%d�j",
	"�ڑ��ł���A�N�Z�X�|�C���g�� ������܂���B Wi-Fi�R�l�N�V�����ݒ�� �ڑ���̐ݒ�����m�F���������B�i�G���[�R�[�h%d�j",
	"Wi-Fi�R�l�N�V������ �ڑ��ł��܂���B Wi-Fi�R�l�N�V�����ݒ�� �ڑ���̐ݒ�����m�F���������B�i�G���[�R�[�h%d�j",
	"�j���e���h�[Wi-Fi�R�l�N�^�� �ڑ��ł��܂���B Wi-Fi�R�l�N�V�����ݒ�� �j���e���h�[Wi-Fi�R�l�N�^�� �ڑ������m�F���������B�i�G���[�R�[�h%d�j",
	"�A�N�Z�X�|�C���g��������܂���B �A�N�Z�X�|�C���g�ɋ߂Â��� ������x�����߂����������B�i�G���[�R�[�h%d�j",
	"Wi-Fi�R�l�N�V���������ݍ����Ă��邩 �T�[�r�X����~���Ă��邽�߂� �ڑ��ł��܂���B ���΂炭�҂��Ă�蒼���Ă��������B�G���[�R�[�h%d�j",
	"�A�N�Z�X�|�C���g�����ݍ����Ă��邽�� �ڑ��ł��܂���B ���΂炭�҂��Ă�蒼���Ă��������B�i�G���[�R�[�h%d�j",
	"�v���|�e���R�l�N�V�������ؒf����܂����B�i�G���[�R�[�h�F%d�j",
	"�l�b�g���[�N����ؒf����܂����B"
};

void dwctest_main(  )
{
	switch( _testWork->state )
	{
		case DWCTESTSTATE_INIT:
		{
			// ������ԁB
			_testWork->ret = mydwc_startConnect(NULL, _testWork->heapID);
			// �t�F�[�^���G���[�i�ċN�s�\�̃G���[�j�����������ۂɌĂ΂��֐����w�肵�܂��B
			mydwc_setFetalErrorCallback( fetal_error );
			_testWork->state = DWCTESTSTATE_CONNECTING;
			if( _testWork->ret == MYDWC_STARTCONNECT_OK )
			{
				OS_TPrintf("�u�v���|�e���R�l�N�V�����ɐڑ����܂����H[Y/N]�v\n");				
			} 
			else if ( _testWork->ret == MYDWC_STARTCONNECT_FIRST )
			{
				OS_TPrintf("�u�v���|�e���R�l�N�V�����ł́A�c�r�J�[�h�Ƃc�r�{�̂��Z�b�g�ň����܂��B\n");
				OS_TPrintf("���g�p���̂c�r�{�̂łv���|�e���R�l�N�V�����ɐڑ����܂����H[Y/N]�v\n");
			} else if( _testWork->ret == MYDWC_STARTCONNECT_DIFFERENTDS ) {
				OS_TPrintf("�uDS�{�̂�DS�J�[�h��Wi-Fi���[�U��񂪂���������Wi-Fi�R�l�N�V�����ɐڑ��ł��܂���B�v\n");
				OS_TPrintf("�uDS�J�[�h�ɕۑ�����Ă���Wi-Fi���[�U�����X�V���܂����H����܂�Wi-Fi�R�l�N�V�����ł��g���ɂȂ��Ă����f�[�^�͎����Ă��܂��܂��B[Y/N]�v\n");
				OS_TPrintf("�u(�Q�[���Ǝ��̏C���p���\��)�v\n");
				OS_TPrintf("�u�{���ɍX�V���Ă���낵���ł����H[Y/N]�v\n");
			}
			OS_TPrintf("�uWi-Fi�R�l�N�V�����ɐڑ����Ă��܂��B���΂炭���҂����������B�v\n");
			break;
		}
		
		case DWCTESTSTATE_CONNECTING:
		{
			// �ڑ���
			int ret = mydwc_connect();
			if( ret < 0 ){
				OS_TPrintf(_mesType[mydwc_errorType(-ret)], -ret);
				OS_TPrintf("�`�{�^���������ƍēx�ڑ������݂܂��B\n");
				_testWork->state = DWCTESTSTATE_ERROR;
			}
			else if ( ret > 0 ) 
			{
				if( _testWork->ret != MYDWC_STARTCONNECT_OK ) {				
					OS_TPrintf("�uDS�J�[�h�ɂ��g�p����DS�{�̂�Wi-Fi���[�U����ۑ����܂����B����Wi-Fi�R�l�N�V�����ւ̐ڑ��́A���g�p����DS�{�̂����g�p���������v\n");
				}
				OS_TPrintf("WiFi�R�l�N�V�����ɐڑ����܂����B\n	");
				OS_TPrintf("A�{�^���������ƃ}�b�`���O���J�n���܂��B\n");	
				_testWork->state = DWCTESTSTATE_LOGIN;
			}
			
			break;
		}
		
		case DWCTESTSTATE_LOGIN:
		{
			// �ڑ���������������B
			int ret = mydwc_step( );
				
			if( ret < 0 ){ // �G���[����
				OS_TPrintf(_mesType[mydwc_errorType(-ret)], -ret);
				OS_TPrintf("�`�{�^���������ƍēx�ڑ������݂܂��B\n");
				_testWork->state = DWCTESTSTATE_ERROR;
			}			
			
			if(sys.trg & PAD_BUTTON_A)
			{
				// �}�b�`���O����������܂łɃR�[���o�b�N��ݒ肷��K�v������̂ŁA�����ł��Ă����A
				mydwc_setReceiver( serverCallback, clientCallback );
				// �}�b�`���O�������I�ɊJ�n����B	
				if( mydwc_startmatch( ) ){
					OS_TPrintf("�}�b�`���O���J�n\n");
					_testWork->state = DWCTESTSTATE_MATCHING;
				}
			}
			break;
		}
		
		case DWCTESTSTATE_MATCHING:
		{
			int ret;
			if( sys.trg & PAD_BUTTON_B )
			{
				// �}�b�`���O�L�����Z��
				ret = mydwc_stepmatch( 1 );
			} 
			else
			{
				ret = mydwc_stepmatch( 0 );				
			}
				
			if( ret < 0 ){
				OS_TPrintf(_mesType[mydwc_errorType(-ret)], -ret);
				OS_TPrintf("�`�{�^���������ƍēx�ڑ������݂܂��B\n");
				_testWork->state = DWCTESTSTATE_ERROR;
			}
			else if ( ret == 1 ) 
			{
				OS_TPrintf("�ΐ푊�肪������܂����B\n");
				_testWork->state = DWCTESTSTATE_CONNECT;
			}
			else if ( ret == 2 )
			{
				OS_TPrintf("�L�����Z�����܂����B\n");	
				OS_TPrintf("A�{�^���������ƃ}�b�`���O���J�n���܂��B\n");	
				_testWork->state = DWCTESTSTATE_LOGIN;							
			}
			break;
		}
		
		case DWCTESTSTATE_DISCONNECTING:
		// �ؒf����������܂ŁA���t���[��mydwc_disconnect���Ăяo���Ă��������B
		// ���̌�Amydwc_step���ĂԕK�v������܂��B
		if( mydwc_disconnect( 0 ) ) {
			_testWork->state = DWCTESTSTATE_DISCONNECTED;
			break;
		}
		case DWCTESTSTATE_CONNECT:
		{
			// �ڑ�������	
			int ret;
			
			if( (_testWork->state == DWCTESTSTATE_CONNECT) && (sys.trg & PAD_BUTTON_START) ){			
				_testWork->state = DWCTESTSTATE_DISCONNECTING;
				break;	
			}
			testMain();
			ret = mydwc_step();

			if( ret < 0 ){
				// �G���[�����B
				OS_TPrintf(_mesType[mydwc_errorType(-ret)], -ret);
				OS_TPrintf("�`�{�^���������ƍēx�ڑ������݂܂��B\n");
				_testWork->state = DWCTESTSTATE_ERROR;
			}		
			else if( ret == 1 )
			{
				// �^�C���A�E�g�i���肩��P�O�b�ȏチ�b�Z�[�W���͂��Ȃ��j
				// ��莞�ԑ��M���Ȃ��ꍇ�́A��̃f�[�^������ő��M���Ă��܂��B
				OS_TPrintf("�^�C���A�E�g���������܂����B\n");	
				_testWork->state = DWCTESTSTATE_DISCONNECTED;			
			}
			else if(ret == 2)
			{
				// �ؒf���ꂽ�B
				OS_TPrintf("���肩��ؒf����܂����B\n");
				_testWork->state = DWCTESTSTATE_DISCONNECTED;
			}	
			break;
		}
		
		case DWCTESTSTATE_DISCONNECTED:
		{
			// �ؒf�����B	
			OS_TPrintf("����Ƃ̒ʐM���I�����܂����B\n");
			OS_TPrintf("A�{�^���������ƍēx�}�b�`���O���J�n���܂��B\n");
			mydwc_returnLobby();
			_testWork->state = DWCTESTSTATE_LOGIN;			
		}
		
		case DWCTESTSTATE_ERROR:
		{
			if(sys.trg & PAD_BUTTON_A)
			{
				// ��x�J��
				mydwc_free();
				
				dwctest_reinit();
			}
		}
		break;
	}
}

static void serverCallback(u16 aid, u16 *data, u16 size)
{
	// �f�[�^����M
	_testWork->serverbuf[_testWork->end].aid = aid;
	_testWork->serverbuf[_testWork->end].data = *((u32*)data);
	_testWork->end++;
	if( _testWork->end >= SERVERBUF_SIZE ) _testWork->end = 0;
	if( _testWork->end == _testWork->start )
	{
		// �o�b�t�@�I�[�o�[�t���[
		OS_TPrintf("!!!!!!!!!!!�I�[�o�[�t���[!!!!!!!!!!!!!!!!");	
	}
}

static void clientCallback(u16 aid, u16 *data, u16 size)
{
	T_SERVERCOM *comm;
	
	comm = (T_SERVERCOM*) data;
	
	// �P�ɕ\�����邾���B
	if( comm->aid == 0 ){
		OS_TPrintf("%d\n", comm->data);
	}else{
		OS_TPrintf("        %d\n", comm->data);
	}
}

static void testMain()
{
	// �T�[�o�p�L���[�Ƀf�[�^���c���Ă���ꍇ�A���M�B
	if( _testWork->end != _testWork->start )
	{
		if( mydwc_sendToClient( &(_testWork->serverbuf[_testWork->start]), sizeof(T_SERVERCOM) ))
		{
			// ���M��������
			_testWork->start++;
			if( _testWork->start >= SERVERBUF_SIZE ) _testWork->start = 0;
		}
	}
	
	// �Q�O�t���[���Ɉ�x���炢�A���M�B
//	if( MATH_Rand16( &_testWork->context, 20 ) == 0 )
	// �����{�^������������
	if( sys.trg )
	{
		if ( mydwc_sendToServer( &(_testWork->index), 4) )
		{
			_testWork->index++;
		}
	}
}

static void fetal_error( int errorcode ){
	OS_TPrintf(_mesType[mydwc_errorType(errorcode)], errorcode);
	OS_TPrintf("�d����؂��Ă��������B\n");	
	while(1){}
}