/*---------------------------------------------------------------------------*
  Project:  DP WiFi Library
  File:     dpw_bt.c

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

/*! @file
	@brief	DP WiFi Battle Tower ���C�u����
	
	@author	kitayama(kitayama_shigetoshi@nintendo.co.jp)
	
	@version beta15 (2006/7/7)
		@li ::Dpw_Bt_Player�y��::Dpw_Bt_Leader�̐��ʂ����Ă����������r�b�g�t���O�Ƃ��A
			���ʃt���O��NG�l�[���t���O�����悤�ɂ��܂����B
	@version beta14 (2006/7/5)
		@li ���[�����̍ő�l::DPW_BT_ROOM_NUM_MAX��100�ɕύX���܂����B
		@li �T�[�o�[�A�b�v�f�[�g���ɃA�N�Z�X�����ꍇ�A::DPW_BT_ERROR_SERVER_TIMEOUT�G���[�ɂȂ�悤�ɂ��܂����B
	@version beta11 (2006/6/9)
		@li Dpw_Bt_UploadPlayerAsync() �̈��� win ��0�̂Ƃ��ɃA�T�[�g�ɂȂ��Ă����o�O���C�����܂����B
		@li ::DPW_BT_ERROR_SERVER_TIMEOUT �̍ۂ̃G���[�\�����ׂ������܂����B
	@version beta10	(2006/5/23)
		@li �T�[�o�[�̏������Ń��[���f�[�^������������Ȃ��Ȃ�܂����B
		@li Dpw_Bt_Player::friend_key���폜���܂����B
		@li Dpw_Bt_Leader::friend_key���폜���܂����B
	@version beta9	(2006/5/22)
		@li Dpw_Bt_Init() �Ɉ��� friend_key ��ǉ����܂����B
		@li Dpw_Bt_Player::friend_key��ǉ����܂����B
		@li Dpw_Bt_Leader::friend_key��ǉ����܂����B
		@li �A�b�v�f�[�g���ɁA���[�_�[��₪��l�����Ȃ��ꍇ�����[���̍X�V���s���Ă����o�O���C�����܂����B
	@version beta8	(2006/5/19)
		@li Dpw_Bt_PokemonData �̃T�C�Y��ύX���܂����B
	@version beta7	(2006/5/15)
		@li Dpw_Bt_Leader::gender��ǉ����܂����B
		@li Dpw_Bt_Player::gender��ǉ����܂����B
		@li Dpw_Bt_Player::playerName��NG�l�[�����܂܂��ꍇ�A�A�b�v�f�[�g���ɒu����������悤�ɂȂ�܂����B
	@version beta6	(2006/5/8)
		@li ::DPW_BT_RANK_NUM��ǉ����܂����B
		@li Dpw_Bt_GetRoomNumAsync(), Dpw_Bt_DownloadRoomAsync(), Dpw_Bt_UploadPlayerAsync() �ŁA����rank�͈̔̓`�F�b�N������Ă���
			�o�O���C�����܂����B
		@li Dpw_Bt_Db_InitServer(), Dpw_Bt_Db_UpdateServer() �ŃG���[����������Ă����o�O���C�����܂����B
	@version beta5	(2006/4/27)
		@li ::DPW_BT_ROOM_NUM_MAX��ǉ����܂����B�i�b��I��20�Ƃ��Ă��܂��B�j
		@li �n���h�����Ă��Ȃ����������G���[�������������C�����܂����B
	@version beta4	(2006/4/17)
		@li Dpw_Bt_Leader::leaderMessage �̃T�C�Y��ύX���܂����B
		@li Dpw_Bt_Player::leaderMessage, Dpw_Bt_Player::message �̃T�C�Y��ύX���܂����B
	@version beta3	(2006/4/10)
		@li Dpw_Bt_PokemonData �̃T�C�Y��ύX���܂����B
		@li Dpw_Bt_Leader::versionCode, Dpw_Bt_Leader::langCode, Dpw_Bt_Leader::countryCode, Dpw_Bt_Leader::localCode ��ǉ����܂����B
		@li Dpw_Bt_Player::versionCode, Dpw_Bt_Player::langCode, Dpw_Bt_Player::countryCode, Dpw_Bt_Player::localCode ��ǉ����܂����B
		@li Dpw_Bt_Room::leader �̃T�C�Y��ύX���܂����B
		@li ����̃^�C�~���O�� Dpw_Bt_CancelAsync() ���ĂԂƎ~�܂��Ă����s����C�����܂����B
	@version beta2	(2006/3/27)
		@li HTTP���C�u�����̃��C���[�ŃG���[���N�������Ƃ��ɁA�G���[���N���A�ł��Ă��Ȃ������s����C�����܂����B
		@li �֐��̃R�����g�ɁA�Ԃ��Ă���G���[�̎�ނ�ǉ����܂����B
		@li Dpw_Bt_PokemonData �̑傫����172�o�C�g�ɕύX���܂����B
	@version beta1	(2006/3/17)
		@li ���ł������[�X���܂����B
*/

#ifdef _NITRO
#include <nitroWiFi/socl.h>
#endif

#include "include/libdpw/dpw_bt.h"
#include "include/libdpw/dpwi_session.h"
#include "include/libdpw/dpwi_assert.h"

/*-----------------------------------------------------------------------*
					�^�E�萔�錾
 *-----------------------------------------------------------------------*/

#ifdef DPW_SERVER_PUBLIC
#define BT_SERVER_URL		"http://gamestats2.gs.nintendowifi.net/pokemondpds/"
#else
#ifdef DPW_SERVER_SUB
#define BT_SERVER_URL		"http://kiyoshi.servebeer.com/web/"
#else
#define BT_SERVER_URL		"http://sdkdev.gamespy.com/games/pokemondpds/web/"
#endif
#endif
//#define BT_SERVER_URL		"http://sdkdev.gamespy.com/games/mariokartds/web/"
//#define BT_SERVER_URL		"http://ishikawa.servebeer.com/web/"
//#define BT_SERVER_URL		"http://gamestats2.gs.nintendowifi.net/pokemondpds/"

#define BT_URL_GETROOMNUM	(const u8*)(BT_SERVER_URL "battletower/roomnum.asp")
#define BT_URL_DOWNLOADROOM	(const u8*)(BT_SERVER_URL "battletower/download.asp")
#define BT_URL_UPLOADPLAYER	(const u8*)(BT_SERVER_URL "battletower/upload.asp")
#define BT_URL_GETSERVERSTATE (const u8*)(BT_SERVER_URL "battletower/info.asp")
#define BT_URL_INIT			(BT_SERVER_URL "battletower/init.asp")
#define BT_URL_UPDATE 		(BT_SERVER_URL "battletower/update.asp")

#ifdef _NITRO
// �\���̂��z��̃T�C�Y�ƂȂ��Ă��邩�`�F�b�N
SDK_COMPILER_ASSERT(sizeof(Dpw_Bt_Leader) == 34);
SDK_COMPILER_ASSERT(sizeof(Dpw_Bt_Player) == 228);
SDK_COMPILER_ASSERT(sizeof(Dpw_Bt_Room) == sizeof(Dpw_Bt_Player) * 7 + sizeof(Dpw_Bt_Leader) * 30);
#endif

#define DB_HTTP_FLAG_NOT_COMPLETED	(-1)

#define BT_RESPONSE_SUCCESS			(1)
#define BT_RESPONSE_ILLIGAL_REQUEST	(2)
#define BT_RESPONSE_STOP_SERVICE	(3)
#define BT_RESPONSE_SERVER_FULL		(4)
#define BT_RESPONSE_SERVER_TIMEOUT	(5)

typedef enum {
	DPWi_BT_NOT_INIT,
	DPWi_BT_NORMAL,
	DPWi_BT_RROCESS_GETROOMNUM,
	DPWi_BT_CANCEL_GETROOMNUM,
	DPWi_BT_RROCESS_DOWNLOADROOM,
	DPWi_BT_CANCEL_DOWNLOADROOM,
	DPWi_BT_RROCESS_UPLOADPLAYER,
	DPWi_BT_CANCEL_UPLOADPLAYER,
	DPWi_BT_RROCESS_GETSERVERSTATE,
	DPWi_BT_CANCEL_GETSERVERSTATE,
	DPWi_BT_END_ASYNC
} DpwiBtState;

typedef struct {
	DpwiBtState state;		// ���C�u�����̏��
	s32 last_result;		// �Ō�ɍs�����񓯊������̌���
	s32 pid;				// �g�p����PID
	u64 friend_key;			// �t�����h�L�[
	u8 send_buf[sizeof(Dpw_Bt_Player) + 11];	// ���M�o�b�t�@
	u8 recv_buf[2];			// ��M�o�b�t�@
	u8* user_recv_buf;		// ���[�U�[����^����ꂽ��M�o�b�t�@
} DpwiBtCtrl;

/*-----------------------------------------------------------------------*
					�֐��v���g�^�C�v�錾
 *-----------------------------------------------------------------------*/

void Dpw_Bt_Init(s32 pid, u64 friend_key);
void Dpw_Bt_Main(void);
void Dpw_Bt_End(void);
BOOL Dpw_Bt_IsAsyncEnd(void);
s32 Dpw_Bt_GetAsyncResult(void);
void Dpw_Bt_GetRoomNumAsync(s32 rank);
void Dpw_Bt_DownloadRoomAsync(s32 rank, s32 roomNo, Dpw_Bt_Room* roomData);
void Dpw_Bt_UploadPlayerAsync(s32 rank, s32 roomNo, s32 win, const Dpw_Bt_Player* player);
void Dpw_Bt_CancelAsync(void);
void Dpw_Bt_GetServerStateAsync(void);
static BOOL Dpwi_Bt_CallSessionRequest(const u8* url, const void* data, int len, void* resbuf, int ressize );
static DpwBtError Dpwi_Bt_HandleCommonError(DpwiHttpError error);
static void Dpwi_Db_GhttpCopleteCallback(const char* buf, int len, DWCGHTTPResult result, void* param);

/*-----------------------------------------------------------------------*
					�O���[�o���ϐ���`
 *-----------------------------------------------------------------------*/

static DpwiBtCtrl dpw_bt;
static int db_ghttp_flag;

/*-----------------------------------------------------------------------*
					�O���[�o���֐���`
 *-----------------------------------------------------------------------*/

/*!
	Dpw_Bt ���C�u���������������܂��B�S�Ă�Dpw_Bt �̕t���֐������s����O�ɃR�[�����܂��B
	
	GS�v���t�@�C��ID�́A DWC_LoginAsync() �֐��̃R�[���o�b�N�Ŏ擾�ł���l�ŁA�T�[�o�[���ň�ӂɃN���C�A���g
	�𔻕ʂ��邽�߂̒l�ł��B
	
	���̊֐����R�[������ۂ́ADWC ���C�u�����̃C���^�[�l�b�g�ڑ��֐��Ńl�b�g���[�N�ɐڑ����Ă���s���Ă���
	�����B�������A���O�C�����s���Ă���K�v�͂���܂���B
	
	@param[in] pid	������GS�v���t�@�C��ID
	@param[in] friend_key	�����̃t�����h�L�[�BDWC_CreateFriendKey() �Ŏ擾�ł��܂��B
*/
void Dpw_Bt_Init(s32 pid, u64 friend_key) {

	DPW_TASSERTMSG(dpw_bt.state == DPWi_BT_NOT_INIT, "dpw bt is already initialized.\n");

	dpw_bt.state = DPWi_BT_NORMAL;
	dpw_bt.last_result = 0;
	dpw_bt.pid = pid;
	dpw_bt.friend_key = friend_key;
}

/*!
	���Q�[���t���[���Ăт����A������i�߂܂��B
	
	���֐��̂��߁A���̊֐��͏�ɌĂяo�����Ƃ��ł��܂��B����������Ԃł͉����s���܂���B
*/
void Dpw_Bt_Main(void) {
	
	switch (dpw_bt.state) {
	case DPWi_BT_NOT_INIT:
		break;
	case DPWi_BT_NORMAL:
		break;
	case DPWi_BT_RROCESS_GETROOMNUM:
		switch( DpwiSessionThink() ){
		case DPWI_COMMON_SESSION_STATE_ERROR:
			dpw_bt.state = DPWi_BT_END_ASYNC;
			dpw_bt.last_result = Dpwi_Bt_HandleCommonError(DpwiGetLastError());
			DpwiSessionShutdown();
			break;
		case DPWI_COMMON_SESSION_STATE_COMPLETED:
			dpw_bt.state = DPWi_BT_END_ASYNC;
			if (DpwiGetResponseSize() > 0) {
				dpw_bt.last_result = dpw_bt.recv_buf[0];
			} else {
				dpw_bt.last_result = DPW_BT_ERROR_SERVER_TIMEOUT;
			}
			DpwiSessionShutdown();
			break;
		}
		break;
	case DPWi_BT_RROCESS_DOWNLOADROOM:
		switch( DpwiSessionThink() ){
		case DPWI_COMMON_SESSION_STATE_ERROR:
			dpw_bt.state = DPWi_BT_END_ASYNC;
			dpw_bt.last_result = Dpwi_Bt_HandleCommonError(DpwiGetLastError());
			DpwiSessionShutdown();
			break;
		case DPWI_COMMON_SESSION_STATE_COMPLETED:
			dpw_bt.state = DPWi_BT_END_ASYNC;
			if (DpwiGetResponseSize() == sizeof(Dpw_Bt_Room)) {
				dpw_bt.last_result = 0;
			} else {
				switch (dpw_bt.user_recv_buf[0]) {
				case BT_RESPONSE_ILLIGAL_REQUEST:
					dpw_bt.last_result = DPW_BT_ERROR_ILLIGAL_REQUEST;
					break;
				case BT_RESPONSE_SERVER_TIMEOUT:
					dpw_bt.last_result = DPW_BT_ERROR_SERVER_TIMEOUT;
					break;
				default:
					DPW_TASSERTMSG(FALSE, "illigal response: %d", dpw_bt.user_recv_buf[0]);
					dpw_bt.last_result = DPW_BT_ERROR_FATAL;
					break;
				}
			}
			DpwiSessionShutdown();
			break;
		}
		break;
	case DPWi_BT_RROCESS_UPLOADPLAYER:
		switch( DpwiSessionThink() ){
		case DPWI_COMMON_SESSION_STATE_ERROR:
			dpw_bt.state = DPWi_BT_END_ASYNC;
			dpw_bt.last_result = Dpwi_Bt_HandleCommonError(DpwiGetLastError());
			DpwiSessionShutdown();
			break;
		case DPWI_COMMON_SESSION_STATE_COMPLETED:
			dpw_bt.state = DPWi_BT_END_ASYNC;
			switch (dpw_bt.recv_buf[0]) {
			case BT_RESPONSE_SUCCESS:
				dpw_bt.last_result = 0;
				break;
			case BT_RESPONSE_ILLIGAL_REQUEST:
				dpw_bt.last_result = DPW_BT_ERROR_ILLIGAL_REQUEST;
				break;
			case BT_RESPONSE_SERVER_FULL:
				dpw_bt.last_result = DPW_BT_ERROR_SERVER_FULL;
				break;
			case BT_RESPONSE_SERVER_TIMEOUT:
				dpw_bt.last_result = DPW_BT_ERROR_SERVER_TIMEOUT;
				break;
			default:
				DPW_TASSERTMSG(FALSE, "illigal response: %d", dpw_bt.recv_buf[0]);
				dpw_bt.last_result = DPW_BT_ERROR_FATAL;
				break;
			}
			DpwiSessionShutdown();
			break;
		}
		break;
	case DPWi_BT_RROCESS_GETSERVERSTATE:
		switch( DpwiSessionThink() ){
		case DPWI_COMMON_SESSION_STATE_ERROR:
			dpw_bt.state = DPWi_BT_END_ASYNC;
			dpw_bt.last_result = Dpwi_Bt_HandleCommonError(DpwiGetLastError());
			DpwiSessionShutdown();
			break;
		case DPWI_COMMON_SESSION_STATE_COMPLETED:
			dpw_bt.state = DPWi_BT_END_ASYNC;
			switch (dpw_bt.recv_buf[0]) {
			case BT_RESPONSE_SUCCESS:
				dpw_bt.last_result = DPW_BT_STATUS_SERVER_OK;
				break;
			case BT_RESPONSE_STOP_SERVICE:
				dpw_bt.last_result = DPW_BT_STATUS_SERVER_STOP_SERVICE;
				break;
			case BT_RESPONSE_SERVER_FULL:
				dpw_bt.last_result = DPW_BT_STATUS_SERVER_FULL;
				break;
			case BT_RESPONSE_SERVER_TIMEOUT:
				dpw_bt.last_result = DPW_BT_ERROR_SERVER_TIMEOUT;
				break;
			default:
				DPW_TASSERTMSG(FALSE, "illigal response: %d", dpw_bt.recv_buf[0]);
				dpw_bt.last_result = DPW_BT_ERROR_FATAL;
				break;
			}
			DpwiSessionShutdown();
			break;
		}
		break;
	case DPWi_BT_CANCEL_GETROOMNUM:
	case DPWi_BT_CANCEL_DOWNLOADROOM:
	case DPWi_BT_CANCEL_UPLOADPLAYER:
	case DPWi_BT_CANCEL_GETSERVERSTATE:
		dpw_bt.state = DPWi_BT_END_ASYNC;
		dpw_bt.last_result = DPW_BT_ERROR_CANCEL;
		DpwiSessionShutdown();
		break;
	case DPWi_BT_END_ASYNC:
		break;
	}
}

/*!
	�������̊J���ȂǏI���������s���܂��B
	
	���̊֐��́A�񓯊����������s���Ă���Ƃ��ɂ̓R�[�����邱�Ƃ��ł��܂���BDpw_Bt_IsAsyncEnd()�Ŕ񓯊���
	���̏I�����m�F���Ă���R�[�����Ă��������B
*/
void Dpw_Bt_End(void) {
	
	DPW_TASSERTMSG(dpw_bt.state != DPWi_BT_NOT_INIT, "dpw bt is not initialized.\n");
	DPW_TASSERTMSG(dpw_bt.state == DPWi_BT_NORMAL, "async process is running.\n");
	
	dpw_bt.state = DPWi_BT_NOT_INIT;
}

/*!
	Dpw_Bt���C�u�����̔񓯊��������I�����Ă��邩�ۂ���Ԃ��܂��B
	
	�֐����ɁuAsync�v���t���֐����R�[�������ۂ́A���̊֐������I�ɃR�[�����āA�I�����m�F���Ă��������B
	
	@retval TRUE	�񓯊��������I�����Ă���
	@retval FALSE	�񓯊��������I�����Ă��Ȃ�
*/
BOOL Dpw_Bt_IsAsyncEnd(void) {
	
	DPW_TASSERTMSG(dpw_bt.state != DPWi_BT_NOT_INIT, "dpw bt is not initialized.\n");
	
	switch (dpw_bt.state) {
	case DPWi_BT_NORMAL:
		return TRUE;
		break;
	case DPWi_BT_END_ASYNC:
		dpw_bt.state = DPWi_BT_NORMAL;
		return TRUE;
		break;
	}

	return FALSE;
}

/*!
	���O�̔񓯊������̌��ʂ��擾���܂��B
	Bpw_Bt_IsAsyncEnd() �ŏI�����m�F���Ă���Ă�ł��������B
	
	�񓯊��������s�����ꍇ�́A�K�����̊֐��Ō��ʁi���ɃG���[���N�����Ă��Ȃ����j���m�F���Ă��������B@n
	�G���[�̎�ނ͔񓯊������ɂ���ĈقȂ�܂����A�ȉ��̃G���[�͋��ʂł��B
	
	@li ::DPW_BT_ERROR_SERVER_TIMEOUT
	@li ::DPW_BT_ERROR_CANCEL
	@li ::DPW_BT_ERROR_FATAL
	@li ::DPW_BT_ERROR_DISCONNECTED
	@li ::DPW_BT_ERROR_FAILURE
	
	@return	�񓯊������̌��ʁB���̒l�̓G���[�������ADpwBtError�̒l���Ԃ�܂��B
*/
s32 Dpw_Bt_GetAsyncResult(void) {
	
	DPW_TASSERTMSG(dpw_bt.state != DPWi_BT_NOT_INIT, "dpw bt is not initialized.\n");
	
	return dpw_bt.last_result;
}

/*!
	���݃I�[�v�����Ă��郋�[�����̎擾���J�n���܂��B
	
	�擾�o�����ꍇ�� Dpw_Bt_GetAsyncResult() �Ń��[�������Ԃ���܂��B
	�G���[���N�������ꍇ�́A���ʂ̃G���[�̂����ꂩ���Ԃ���܂��B
	
	@param[in] rank	�����N
*/
void Dpw_Bt_GetRoomNumAsync(s32 rank) {
	
	DPW_TASSERTMSG(dpw_bt.state != DPWi_BT_NOT_INIT, "dpw bt is not initialized.\n");
	DPW_TASSERTMSG(dpw_bt.state == DPWi_BT_NORMAL, "async process is already running.\n");
	DPW_MINMAX_TASSERT(rank, 1, DPW_BT_RANK_NUM);
	
	// �Z�b�V����������
	DpwiSessionInitialize();

	dpw_bt.send_buf[0] = (u8)(rank - 1);	// �T�[�o�[����0�x�[�X�Ȃ̂ŁA���킹��
	
	// �ʐM�J�n
	if (Dpwi_Bt_CallSessionRequest(BT_URL_GETROOMNUM, dpw_bt.send_buf, 1, dpw_bt.recv_buf, 2)) {
		dpw_bt.state = DPWi_BT_RROCESS_GETROOMNUM;
	} else {
		dpw_bt.state = DPWi_BT_END_ASYNC;
		dpw_bt.last_result = DPW_BT_ERROR_FATAL;
		DpwiSessionShutdown();
	}
}

/*!
	���[���f�[�^���_�E�����[�h���܂��B
	
	���������ꍇ�A Dpw_Bt_GetAsyncResult() ��0���Ԃ���܂��B
	�G���[���N�������ꍇ�́A���ʂ̃G���[�������͈ȉ��̃G���[���Ԃ���܂��B
	
	@li ::DPW_BT_ERROR_ILLIGAL_REQUEST	�F ���[���ԍ��̎w�肪����Ă��܂��B
	
	@param[in] rank	�����N
	@param[in] roomNo ���[���ԍ�
	@param[out] roomData �_�E�����[�h�������[���f�[�^���L�^����o�b�t�@
*/
void Dpw_Bt_DownloadRoomAsync(s32 rank, s32 roomNo, Dpw_Bt_Room* roomData) {
	
	DPW_TASSERTMSG(dpw_bt.state != DPWi_BT_NOT_INIT, "dpw bt is not initialized.\n");
	DPW_TASSERTMSG(dpw_bt.state == DPWi_BT_NORMAL, "async process is already running.\n");
	DPW_MINMAX_TASSERT(rank, 1, DPW_BT_RANK_NUM);
	DPW_MINMAX_TASSERT(roomNo, 1, DPW_BT_ROOM_NUM_MAX);
	DPW_NULL_TASSERT(roomData);
	
	dpw_bt.user_recv_buf = (u8*)roomData;
	
	// �Z�b�V����������
	DpwiSessionInitialize();

	dpw_bt.send_buf[0] = (u8)(rank - 1);	// �T�[�o�[����0�x�[�X�Ȃ̂ŁA���킹��
	dpw_bt.send_buf[1] = (u8)(roomNo - 1);	// �T�[�o�[����0�x�[�X�Ȃ̂ŁA���킹��
	
	// �ʐM�J�n
	if (Dpwi_Bt_CallSessionRequest(BT_URL_DOWNLOADROOM, dpw_bt.send_buf, 2, roomData, sizeof(Dpw_Bt_Room))) {
		dpw_bt.state = DPWi_BT_RROCESS_DOWNLOADROOM;
	} else {
		dpw_bt.state = DPWi_BT_END_ASYNC;
		dpw_bt.last_result = DPW_BT_ERROR_FATAL;
		DpwiSessionShutdown();
	}
}

/*!
	�v���C���[�f�[�^���A�b�v���[�h���܂��B
	
	���������ꍇ�A Dpw_Bt_GetAsyncResult() ��0���Ԃ���܂��B
	�G���[���N�������ꍇ�́A���ʂ̃G���[�������͈ȉ��̃G���[���Ԃ���܂��B
	
	@li ::DPW_BT_ERROR_SERVER_FULL		�F �T�[�o�[�̗e�ʃI�[�o�[�ł��B
	@li ::DPW_BT_ERROR_ILLIGAL_REQUEST	�F ���[���ԍ��̎w�肪����Ă��܂��B
	
	@param[in] rank	�����N
	@param[in] roomNo	���[���ԍ�
	@param[in] win	�v���C���[�̏�����
	@param[in] player	�v���C���[�f�[�^�B�֐����ŃR�s�[���܂��̂ŁA�ÓI�ɕێ�����K�v�͂���܂���B
*/
void Dpw_Bt_UploadPlayerAsync(s32 rank, s32 roomNo, s32 win, const Dpw_Bt_Player* player) {
	
	DPW_TASSERTMSG(dpw_bt.state != DPWi_BT_NOT_INIT, "dpw bt is not initialized.\n");
	DPW_TASSERTMSG(dpw_bt.state == DPWi_BT_NORMAL, "async process is already running.\n");
	DPW_MINMAX_TASSERT(rank, 1, DPW_BT_RANK_NUM);
	DPW_MINMAX_TASSERT(roomNo, 1, DPW_BT_ROOM_NUM_MAX);
	DPW_MINMAX_TASSERT(win, 0, 7);
	DPW_NULL_TASSERT(player);
	
	// �Z�b�V����������
	DpwiSessionInitialize();

	memcpy(&dpw_bt.send_buf[0], player, sizeof(Dpw_Bt_Player));
	dpw_bt.send_buf[sizeof(Dpw_Bt_Player)] = (u8)(rank - 1);	// �T�[�o�[����0�x�[�X�Ȃ̂ŁA���킹��
	dpw_bt.send_buf[sizeof(Dpw_Bt_Player) + 1] = (u8)(roomNo - 1);	// �T�[�o�[����0�x�[�X�Ȃ̂ŁA���킹��
	dpw_bt.send_buf[sizeof(Dpw_Bt_Player) + 2] = (u8)win;
	memcpy(&dpw_bt.send_buf[sizeof(Dpw_Bt_Player) + 3], &dpw_bt.friend_key, 8);
	
	// �ʐM�J�n
	if (Dpwi_Bt_CallSessionRequest(BT_URL_UPLOADPLAYER, dpw_bt.send_buf, sizeof(Dpw_Bt_Player) + 11, dpw_bt.recv_buf, 2)) {
		dpw_bt.state = DPWi_BT_RROCESS_UPLOADPLAYER;
	} else {
		dpw_bt.state = DPWi_BT_END_ASYNC;
		dpw_bt.last_result = DPW_BT_ERROR_FATAL;
		DpwiSessionShutdown();
	}
}

/*!
	Dpw_Bt ���C�u�����Ō��ݍs���Ă���񓯊��������L�����Z�����܂��B
	
	�L�����Z�������ꍇ�A Dpw_Bt_GetAsyncResult() �̕Ԓl�� DPW_BT_ERROR_CANCEL �ƂȂ�܂��B
	
	���ɒʐM���I�����Ă��邱�Ƃ�����܂��̂ŁA�L�����Z���͏�ɐ�������Ƃ͌���܂���B
	�L�����Z���ł������ǂ����́A Dpw_Bt_GetAsyncResult() �̕Ԓl�� DPW_BT_ERROR_CANCEL �ƂȂ��Ă��邩�Ŕ��f���Ă��������B
	
	Dpw_Bt_CancelAsync()���̂��񓯊������ł����A������L�����Z�����邱�Ƃ͂ł��܂���B
*/
void Dpw_Bt_CancelAsync(void) {
	
	DPW_TASSERTMSG(dpw_bt.state != DPWi_BT_NOT_INIT, "dpw bt is not initialized.\n");
	
	switch (dpw_bt.state) {
	case DPWi_BT_RROCESS_GETROOMNUM:
		DpwiSessionCancel();
		dpw_bt.state = DPWi_BT_CANCEL_GETROOMNUM;
		break;
	case DPWi_BT_RROCESS_DOWNLOADROOM:
		DpwiSessionCancel();
		dpw_bt.state = DPWi_BT_CANCEL_DOWNLOADROOM;
		break;
	case DPWi_BT_RROCESS_UPLOADPLAYER:
		DpwiSessionCancel();
		dpw_bt.state = DPWi_BT_CANCEL_UPLOADPLAYER;
		break;
	case DPWi_BT_RROCESS_GETSERVERSTATE:
		DpwiSessionCancel();
		dpw_bt.state = DPWi_BT_CANCEL_GETSERVERSTATE;
		break;
	}
}

/*!
	�T�[�o�[��Ԃ̒������J�n���܂��B
	
	�T�[�o�[�Ɛ���ɒʐM�ł����ꍇ�́A Dpw_Bt_GetAsyncResult() �� DpwBtServerStatus �̒l���Ԃ���܂��B
	
	����ɒʐM�ł��Ȃ������ꍇ�́A ���ʂ̃G���[�̂����ꂩ���Ԃ���܂��B
*/
void Dpw_Bt_GetServerStateAsync(void) {
	
	DPW_TASSERTMSG(dpw_bt.state != DPWi_BT_NOT_INIT, "dpw bt is not initialized.\n");
	DPW_TASSERTMSG(dpw_bt.state == DPWi_BT_NORMAL, "async process is already running.\n");
	
	// �Z�b�V����������
	DpwiSessionInitialize();

	// �ʐM�J�n
	if (Dpwi_Bt_CallSessionRequest(BT_URL_GETSERVERSTATE, dpw_bt.send_buf, 0, dpw_bt.recv_buf, 2)) {
		dpw_bt.state = DPWi_BT_RROCESS_GETSERVERSTATE;
	} else {
		dpw_bt.state = DPWi_BT_END_ASYNC;
		dpw_bt.last_result = DPW_BT_ERROR_FATAL;
		DpwiSessionShutdown();
	}
}

#ifndef SDK_FINALROM
/*!
	�o�g���^���[�̃T�[�o��Ԃ����������܂��B
	�����Ńu���b�N���܂��B
	
	���̊֐��́A�f�o�b�O�^�e�X�g�p�ł��BFINALROM�ł͖����ƂȂ�܂��B
	
	@retval TRUE	�������ɐ�������
	@retval FALSE	�������Ɏ��s����
*/
BOOL Dpw_Bt_Db_InitServer(void) {
	
	int ret;
	
	DPW_TASSERTMSG(dpw_bt.state != DPWi_BT_NOT_INIT, "dpw bt is not initialized.\n");
	DPW_TASSERTMSG(dpw_bt.state == DPWi_BT_NORMAL, "async process is already running.\n");
	
	db_ghttp_flag = DB_HTTP_FLAG_NOT_COMPLETED;
	
	(void)DWC_InitGHTTP(NULL);
	
	ret = DWC_GetGHTTPData(BT_URL_INIT, Dpwi_Db_GhttpCopleteCallback, NULL);
	
	while (db_ghttp_flag == DB_HTTP_FLAG_NOT_COMPLETED) {
		
		if (!DWC_ProcessGHTTP()) {
			DWC_ClearError();
			return FALSE;
		}
		
		OS_Sleep(16);
	}
	
	DWC_ShutdownGHTTP();

	if (db_ghttp_flag == DWC_GHTTP_SUCCESS) {
		return TRUE;
	} else {
		DWC_ClearError();
		return FALSE;
	}
}
#endif

#ifndef SDK_FINALROM
/*!
	�o�g���^���[�̃T�[�o�̈�����̃A�b�v�f�[�g�s���܂��B
	�����Ńu���b�N���܂��B
	
	���̊֐��́A�f�o�b�O�^�e�X�g�p�ł��BFINALROM�ł͖����ƂȂ�܂��B
*/
BOOL Dpw_Bt_Db_UpdateServer(void) {
	
	int ret;
	
	DPW_TASSERTMSG(dpw_bt.state != DPWi_BT_NOT_INIT, "dpw bt is not initialized.\n");
	DPW_TASSERTMSG(dpw_bt.state == DPWi_BT_NORMAL, "async process is already running.\n");
	
	db_ghttp_flag = DB_HTTP_FLAG_NOT_COMPLETED;
	
	(void)DWC_InitGHTTP(NULL);
	
	ret = DWC_GetGHTTPData(BT_URL_UPDATE, Dpwi_Db_GhttpCopleteCallback, NULL);
	
	while (db_ghttp_flag == DB_HTTP_FLAG_NOT_COMPLETED) {
		
		if (!DWC_ProcessGHTTP()) {
			DWC_ClearError();
			return FALSE;
		}
		
		OS_Sleep(16);
	}
	
	DWC_ShutdownGHTTP();

	if (db_ghttp_flag == DWC_GHTTP_SUCCESS) {
		return TRUE;
	} else {
		DWC_ClearError();
		return FALSE;
	}
}
#endif

/*-----------------------------------------------------------------------*
					���[�J���֐���`
 *-----------------------------------------------------------------------*/

static BOOL Dpwi_Bt_CallSessionRequest(const u8* url, const void* data, int len, void* resbuf, int ressize) {
	
	switch (DpwiSessionRequest(url, dpw_bt.pid, data, len, (u8*)resbuf, ressize)) {
	case DPWI_COMMON_SESSION_SUCCESS:				// ����I��
		return TRUE;
		break;
	case DPWI_COMMON_SESSION_ERROR_NOTINITIALIZED:	// ��������
		DPW_TASSERTMSG(FALSE, "common session not initialized.");
		break;
	case DPWI_COMMON_SESSION_ERROR_NOMEMORY:		// �������[�s��
		DPW_TASSERTMSG(FALSE, "common session memory shortage.");
		break;
	}
	
	return FALSE;
}

static DpwBtError Dpwi_Bt_HandleCommonError(DpwiHttpError error) {
	
	DpwBtError ret;
	
	OS_TPrintf("[DPW BT] ghttp error: %d\n", error);
	
	switch (error) {
	case DPWI_COMMON_SESSION_ERROR_IN_ERROR:			// �G���[������ 
	case DPWI_COMMON_SESSION_ERROR_INVALID_POST:		// �����ȑ��M 
	case DPWI_COMMON_SESSION_ERROR_INVALID_FILE_NAME:	// �����ȃt�@�C���� 
	case DPWI_COMMON_SESSION_ERROR_INVALID_BUFFER_SIZE:	// �����ȃo�b�t�@�T�C�Y 
	case DPWI_COMMON_SESSION_ERROR_INVALID_URL:			// ������URL
	case DPWI_COMMON_SESSION_ERROR_UNSPECIFIED_ERROR:	// ���̑��̃G���[
	case DPWI_COMMON_SESSION_ERROR_BUFFER_OVERFLOW:		// �������ꂽ�o�b�t�@�����������邽�߁A�t�@�C���̎擾���s 
	case DPWI_COMMON_SESSION_ERROR_PARSE_URL_FAILED:	// URL��̓G���[ 
//	case DPWI_COMMON_SESSION_ERROR_ENCRYPTION_ERROR:	// �Í����G���[ 
	case DPWI_COMMON_SESSION_ERROR_FILE_TOO_BIG:		// �t�@�C�����傫�����邽�߃_�E�����[�h�s�\ 
	case DPWI_COMMON_SESSION_ERROR_FILE_INCOMPLETE:		// �_�E�����[�h�̒��f 
	case DPWI_COMMON_SESSION_ERROR_FILE_WRITE_FAILED:	// ���[�J���t�@�C���ւ̏������݃G���[ 
	case DPWI_COMMON_SESSION_ERROR_FILE_READ_FAILED:	// ���[�J���t�@�C������̓ǂݏo���G���[ 
	case DPWI_COMMON_SESSION_ERROR_BAD_RESPONSE:		// HTTP�T�[�o����̃��X�|���X�̉�̓G���[ 
	case DPWI_COMMON_SESSION_ERROR_BUFFER_OVER:			// COMMON�w: ��M�o�b�t�@���I�[�o�[����
		DPW_TASSERTMSG(FALSE, "library internal error. please contact author.");
		ret = DPW_BT_ERROR_FATAL;
		break;
	case DPWI_COMMON_SESSION_ERROR_INSUFFICIENT_MEMORY:	// �������s�� 
	case DPWI_COMMON_SESSION_ERROR_OUT_OF_MEMORY:		// ���������蓖�Ď��s 
	case DPWI_COMMON_SESSION_ERROR_MEMORY_ERROR: 		// ���������蓖�Ď��s 
		DPW_TASSERTMSG(FALSE, "common session memory shortage.");
		ret = DPW_BT_ERROR_FATAL;
		break;
	case DPWI_COMMON_SESSION_ERROR_HOST_LOOKUP_FAILED:	// �z�X�g���������s 
		OS_TPrintf("[DPW BT] dns lookup failed.\n");
		ret = DPW_BT_ERROR_FAILURE;
		break;
	case DPWI_COMMON_SESSION_ERROR_SOCKET_FAILED:		// �\�P�b�g�̍쐬�A�������A�ǂݏo���A�������ݎ��s 
	case DPWI_COMMON_SESSION_ERROR_CONNECT_FAILED:		// HTTP�T�[�o�ւ̐ڑ����s 
		OS_TPrintf("[DPW BT] socket error.\n");
		ret = DPW_BT_ERROR_FAILURE;
		break;
	case DPWI_COMMON_SESSION_ERROR_UNAUTHORIZED:		// �t�@�C���擾������ 
	case DPWI_COMMON_SESSION_ERROR_FORBIDDEN:			// HTTP�T�[�o�̃t�@�C�����M���� 
	case DPWI_COMMON_SESSION_ERROR_FILE_NOT_FOUND:		// HTTP�T�[�o��̃t�@�C���������s 
	case DPWI_COMMON_SESSION_ERROR_SERVER_ERROR:		// HTTP�T�[�o�����G���[
	case DPWI_COMMON_SESSION_ERROR_CHECKSUM:			// COMMON�w: �`�F�b�N�T���̕s��v
	case DPWI_COMMON_SESSION_ERROR_PID:					// COMMON�w: PID�̕s��v
	case DPWI_COMMON_SESSION_ERROR_DATA_LENGTH: 		// COMMON�w: �f�[�^�̒������s��
	case DPWI_COMMON_SESSION_ERROR_TOKEN_NOT_FOUND:		// COMMON�w: �g�[�N�����Ȃ�
	case DPWI_COMMON_SESSION_ERROR_INCORRECT_HASH:		// COMMON�w: �n�b�V��������Ȃ�
		OS_TPrintf("[DPW BT] server internal error.  please contact server administrator.\n");
		ret = DPW_BT_ERROR_SERVER_TIMEOUT;
		break;
	case DPWI_COMMON_SESSION_ERROR_REQUEST_REJECTED:	// HTTP�T�[�o�̃��N�G�X�g���� 
	case DPWI_COMMON_SESSION_ERROR_TOKEN_EXPIRED:		// COMMON�w: �g�[�N���̗L�������؂�
		OS_TPrintf("[DPW BT] server is now heavy.\n");
		ret = DPW_BT_ERROR_SERVER_TIMEOUT;
		break;
	default:
		DPW_TASSERTMSG(FALSE, "illigal ghttp error: %d", error);
		ret = DPW_BT_ERROR_FATAL;
		break;
	}
	
	// FATAL�G���[�łȂ��ꍇ
	if (ret != DPW_BT_ERROR_FATAL) {
#ifdef _NITRO
		// NitroWiFi�̃��C���[�Ŗ������؂�Ă��Ȃ����`�F�b�N����
		if (WCM_GetPhase() != WCM_PHASE_DCF) {
			OS_TPrintf("[DPW BT] disconnected from access point.\n");
			ret = DPW_BT_ERROR_DISCONNECTED;
		}
#endif
		// DWC�̃G���[��Ԃ��N���A����
		DWC_ClearError();
	}
	
	return ret;
}

#ifndef SDK_FINALROM
static void Dpwi_Db_GhttpCopleteCallback(const char* buf, int len, DWCGHTTPResult result, void* param) {
#pragma unused(buf, len, param)
	
	db_ghttp_flag = result;
}
#endif
