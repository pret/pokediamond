/*---------------------------------------------------------------------------*
  Project:  DP WiFi Library
  File:     dpw_tr.c

  Copyright 2003-2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $NoKeywords: $
 *---------------------------------------------------------------------------*/

/*! @file
	@brief	DP WiFi Trade ���C�u����
	
	@author	kitayama(kitayama_shigetoshi@nintendo.co.jp)
	
	@version beta16 (2006/7/27)
		@li Dpw_Tr_ReturnAsync() ��ǉ����܂����B�|�P�������������ۂɂ�Dpw_Tr_ReturnAsync()
			���g�p���ADpw_Tr_DeleteAsync()�͌����ς݂̃f�[�^���폜����ꍇ�ɂ̂ݎg�p���Ă��������B
	@version beta14 (2006/7/5)
		@li �T�[�o�[�A�b�v�f�[�g���ɃA�N�Z�X�����ꍇ�A::DPW_TR_ERROR_SERVER_TIMEOUT�G���[�ɂȂ�悤�ɂ��܂����B
	@version beta13 (2006/6/30)
		@li Dpw_Tr_TradeAsync() �Ő������T�[�o�[����̃��X�|���X���󂯎��Ă��Ȃ������o�O���C�����܂����B
	@version beta12 (2006/6/15)
		@li ::DPW_TR_ERROR_ILLEGAL_DATA, ::DPW_TR_ERROR_CHEAT_DATA, ::DPW_TR_ERROR_NG_POKEMON_NAME, ::DPW_TR_ERROR_NG_PARENT_NAME, ::DPW_TR_ERROR_NG_MAIL_NAME, ::DPW_TR_ERROR_NG_OWNER_NAME ���A Dpw_Tr_Data::name �����̒l�ɂ����Ƃ��ɕԂ�悤�ɂ��܂����B
	@version beta11 (2006/6/9)
		@li ::DPW_TR_ERROR_SERVER_TIMEOUT �̍ۂ̃G���[�\�����ׂ������܂����B
	@version beta10	(2006/5/23)
		@li Dpw_Tr_Data::friend_key���폜���܂����B
	@version beta9	(2006/5/22)
		@li Dpw_Tr_Init() �Ɉ��� friend_key ��ǉ����܂����B
		@li Dpw_Tr_Data::friend_key��ǉ����܂����B
	@version beta7	(2006/5/15)
		@li Dpw_Tr_Data::gender��ǉ����܂����B
	@version beta6	(2006/5/8)
		@li ::DPW_TR_GENDER_NONE �̃R�����g���C�����܂����B
		@li Dpw_Tr_PokemonSearchData ��ǉ����܂����B
		@li Dpw_Tr_Data::wantSimple �̌^�� Dpw_Tr_PokemonSearchData �֕ύX���܂����B
		@li Dpw_Tr_DownloadMatchDataAsync() �̈�����ύX���܂����B
		@li Dpw_Tr_Db_InitServer(), Dpw_Tr_Db_UpdateServer(), Dpw_Tr_Db_ShuffleServerData() �ŃG���[����������Ă����o�O���C�����܂����B
		@li Dpw_Tr_Data::postDate, Dpw_Tr_Data::tradeDate �֓��錎���A1�}�C�i�X���ꂽ�l�ɂȂ��Ă����o�O���C�����܂����B
	@version beta5	(2006/4/27)
		@li ::DPW_TR_ERROR_NG_TRAINER_NAME��p�~���A::DPW_TR_ERROR_NG_PARENT_NAME��::DPW_TR_ERROR_NG_OWNER_NAME��ǉ����܂����B
		@li �n���h�����Ă��Ȃ����������G���[�������������C�����܂����B
	@version beta3	(2006/4/10)
		@li Dpw_Tr_PokemonData �̃T�C�Y��ύX���܂����B
		@li Dpw_Tr_Data::comment ���폜���܂����B
		@li Dpw_Tr_Data::trainerID ��ǉ����܂����B
		@li Dpw_Tr_Data::langCode ��ǉ����܂����B	
		@li ����̃^�C�~���O�� Dpw_Tr_CancelAsync() ���ĂԂƎ~�܂��Ă����s����C�����܂����B
	@version beta2	(2006/3/27)
		@li Dpw_Tr_DownloadMatchDataAsync() �Ō��������f�[�^�������_���ɕύX���܂����B
			�قȂ�PID�ł́A�قȂ錟�����ʂƂȂ�܂��B
		@li HTTP���C�u�����̃��C���[�ŃG���[���N�������Ƃ��ɁA�G���[���N���A�ł��Ă��Ȃ������s����C�����܂����B
		@li �֐��̃R�����g�ɁA�Ԃ��Ă���G���[�̎�ނ�ǉ����܂����B
		@li Dpw_Tr_Data::trainerType �����������悤�ɂ��܂����B
		@li Dpw_Tr_Data::mail ���폜���A Dpw_Tr_Data::postData �֊܂߂܂����B
		@li Dpw_Tr_PokemonData �̑傫����172�o�C�g�ɕύX���܂����B
		@li ::DpwTrError �ŁANG���[�h�Ɋւ���G���[���ו������܂����B
		@li Dpw_Tr_Db_ShuffleServerData() ��ǉ����܂����B
	@version beta1	(2006/3/17)
		@li ���ł������[�X���܂����B
*/

#ifdef _NITRO
#include <nitroWiFi/socl.h>
#endif

#include "include/libdpw/dpw_tr.h"
#include "include/libdpw/dpwi_session.h"
#include "include/libdpw/dpwi_assert.h"

/*-----------------------------------------------------------------------*
					�^�E�萔�錾
 *-----------------------------------------------------------------------*/

#ifdef DPW_SERVER_PUBLIC
#define TR_SERVER_URL		"http://gamestats2.gs.nintendowifi.net/pokemondpds/"
#else
#ifdef DPW_SERVER_SUB
#define TR_SERVER_URL		"http://kiyoshi.servebeer.com/web/"
#else
#define TR_SERVER_URL		"http://sdkdev.gamespy.com/games/pokemondpds/web/"
#endif
#endif
//#define TR_SERVER_URL		"http://sdkdev.gamespy.com/games/mariokartds/web/"
//#define TR_SERVER_URL		"http://ishikawa.servebeer.com/web/"
//#define TR_SERVER_URL		"http://gamestats2.gs.nintendowifi.net/pokemondpds/"

#ifdef _NITRO
// �\���̂��z��̃T�C�Y�ƂȂ��Ă��邩�`�F�b�N
SDK_COMPILER_ASSERT(sizeof(Dpw_Tr_Data) == 292);
#endif

#define TR_URL_UPLOAD	((const unsigned char *)TR_SERVER_URL "worldexchange/post.asp")
#define TR_URL_UPLOADFINISH	((const unsigned char *)TR_SERVER_URL "worldexchange/post_finish.asp")
#define TR_URL_DOWNLOAD	((const unsigned char *)TR_SERVER_URL "worldexchange/get.asp")
#define TR_URL_GETUPLOADRESULT	((const unsigned char *)TR_SERVER_URL "worldexchange/result.asp")
#define TR_URL_DELETE	((const unsigned char *)TR_SERVER_URL "worldexchange/delete.asp")
#define TR_URL_RETURN	((const unsigned char *)TR_SERVER_URL "worldexchange/return.asp")
#define TR_URL_DOWNLOADMATCHDATA ((const unsigned char *)TR_SERVER_URL "worldexchange/search.asp")
#define TR_URL_TRADE	((const unsigned char *)TR_SERVER_URL "worldexchange/exchange.asp")
#define TR_URL_TRADEFINISH	((const unsigned char *)TR_SERVER_URL "worldexchange/exchange_finish.asp")
#define TR_URL_GETSERVERSTATE ((const unsigned char *)TR_SERVER_URL "worldexchange/info.asp")
#define TR_URL_INIT	((const char *)TR_SERVER_URL "worldexchange/init.asp")
#define TR_URL_UPDATE ((const char *)TR_SERVER_URL "worldexchange/update.asp")
#define TR_URL_SHUFFLE ((const char *)TR_SERVER_URL "worldexchange/shuffle.asp")

#define DB_HTTP_FLAG_NOT_COMPLETED	(-1)

#define TR_RESPONSE_SUCCESS	(1)
#define TR_RESPONSE_ILLIGAL_REQUEST	(2)
#define TR_RESPONSE_TIMEOUT	(3)
#define TR_RESPONSE_NOT_EXCHANGED (4)
#define TR_RESPONSE_NO_DATA (5)
#define TR_RESPONSE_STOP_SERVICE (6)
#define TR_RESPONSE_SERVER_FULL (7)
#define TR_RESPONSE_NG_POKEMON_NAME (8)
#define TR_RESPONSE_NG_PARENT_NAME (9)
#define TR_RESPONSE_NG_MAIL_NAME (10)
#define TR_RESPONSE_NG_OWNER_NAME (11)
#define TR_RESPONSE_ILLEGAL_DATA (12)
#define TR_RESPONSE_CHEAT_DATA (13)
#define TR_RESPONSE_SERVER_TIMEOUT (14)

typedef enum {
	DPWi_TR_NOT_INIT,
	DPWi_TR_NORMAL,
	DPWi_TR_RROCESS_UPLOAD,
	DPWi_TR_CANCEL_UPLOAD,
	DPWi_TR_RROCESS_UPLOADFINISH,
	DPWi_TR_CANCEL_UPLOADFINISH,
	DPWi_TR_RROCESS_DOWNLOAD,
	DPWi_TR_CANCEL_DOWNLOAD,
	DPWi_TR_RROCESS_GETUPLOADRESULT,
	DPWi_TR_CANCEL_GETUPLOADRESULT,
	DPWi_TR_RROCESS_DELETE,
	DPWi_TR_CANCEL_DELETE,
	DPWi_TR_RROCESS_RETURN,
	DPWi_TR_CANCEL_RETURN,
	DPWi_TR_RROCESS_DOWNLOADMATCHDATA,
	DPWi_TR_CANCEL_DOWNLOADMATCHDATA,
	DPWi_TR_RROCESS_TRADE,
	DPWi_TR_CANCEL_TRADE,
	DPWi_TR_RROCESS_TRADEFINISH,
	DPWi_TR_CANCEL_TRADEFINISH,
	DPWi_TR_RROCESS_GETSERVERSTATE,
	DPWi_TR_CANCEL_GETSERVERSTATE,
	DPWi_TR_END_ASYNC
} DpwiTrState;

typedef struct {
	DpwiTrState state;
	s32 last_result;
	s32 pid;
	u64 friend_key;
	u8 send_buf[sizeof(Dpw_Tr_Data) + 4];
	u8 recv_buf[4];
	u8* user_recv_buf;
} DpwiTrCtrl;

/*-----------------------------------------------------------------------*
					�֐��v���g�^�C�v�錾
 *-----------------------------------------------------------------------*/

void Dpw_Tr_Init(s32 pid, u64 friend_key);
void Dpw_Tr_Main(void);
void Dpw_Tr_End(void);
BOOL Dpw_Tr_IsAsyncEnd(void);
s32 Dpw_Tr_GetAsyncResult(void);
void Dpw_Tr_UploadAsync(const Dpw_Tr_Data* data);
void Dpw_Tr_UploadFinishAsync(void);
void Dpw_Tr_DownloadAsync(Dpw_Tr_Data* data);
void Dpw_Tr_GetUploadResultAsync(Dpw_Tr_Data* data);
void Dpw_Tr_DeleteAsync(void);
void Dpw_Tr_ReturnAsync(void);
void Dpw_Tr_CancelAsync(void);
void Dpw_Tr_DownloadMatchDataAsync(const Dpw_Tr_PokemonSearchData* searchData, s32 maxNum, Dpw_Tr_Data* downloadData);
void Dpw_Tr_TradeAsync(s32 id, const Dpw_Tr_Data* uploadData, Dpw_Tr_Data* downloadData);
void Dpw_Tr_TradeFinishAsync(void);
void Dpw_Tr_GetServerStateAsync(void);
static BOOL Dpwi_Tr_CallSessionRequest(const u8* url, const void* data, int len, void* resbuf, int ressize );
static DpwTrError Dpwi_Tr_HandleCommonError(DpwiHttpError error);
static void Dpwi_Db_GhttpCopleteCallback(const char* buf, int len, DWCGHTTPResult result, void* param);

/*-----------------------------------------------------------------------*
					�O���[�o���ϐ���`
 *-----------------------------------------------------------------------*/

static DpwiTrCtrl dpw_tr;
static int db_ghttp_flag;

/*-----------------------------------------------------------------------*
					�O���[�o���֐���`
 *-----------------------------------------------------------------------*/

/*!
	Dpw_Tr ���C�u���������������܂��B�S�Ă�Dpw_Tr �̕t���֐������s����O�ɃR�[�����܂��B
	
	GS�v���t�@�C��ID�́A DWC_LoginAsync() �֐��̃R�[���o�b�N�Ŏ擾�ł���l�ŁA�T�[�o�[���ň�ӂɃN���C�A���g
	�𔻕ʂ��邽�߂̒l�ł��B
	
	���̊֐����R�[������ۂ́ADWC ���C�u�����̃C���^�[�l�b�g�ڑ��֐��Ńl�b�g���[�N�ɐڑ����Ă���s���Ă���
	�����B�������A���O�C�����s���Ă���K�v�͂���܂���B
	
	@param[in] pid	������GS�v���t�@�C��ID
	@param[in] friend_key	�����̃t�����h�L�[�BDWC_CreateFriendKey() �Ŏ擾�ł��܂��B
*/
void Dpw_Tr_Init(s32 pid, u64 friend_key) {
	
	DPW_TASSERTMSG(dpw_tr.state == DPWi_TR_NOT_INIT, "dpw tr is already initialized.\n");
	
	dpw_tr.state = DPWi_TR_NORMAL;
	dpw_tr.last_result = 0;
	dpw_tr.pid = pid;
	dpw_tr.friend_key = friend_key;
}

/*!
	���Q�[���t���[���Ăт����A������i�߂܂��B
	
	���֐��̂��߁A���̊֐��͏�ɌĂяo�����Ƃ��ł��܂��B����������Ԃł͉����s���܂���B
*/
void Dpw_Tr_Main(void) {
	
	switch (dpw_tr.state) {
	case DPWi_TR_NOT_INIT:
		break;
	case DPWi_TR_NORMAL:
		break;
	case DPWi_TR_RROCESS_UPLOAD:
		switch( DpwiSessionThink() ){
		case DPWI_COMMON_SESSION_STATE_ERROR:
			dpw_tr.state = DPWi_TR_END_ASYNC;
			dpw_tr.last_result = Dpwi_Tr_HandleCommonError(DpwiGetLastError());
			DpwiSessionShutdown();
			break;
		case DPWI_COMMON_SESSION_STATE_COMPLETED:
			dpw_tr.state = DPWi_TR_END_ASYNC;
			switch (dpw_tr.recv_buf[0]) {
			case TR_RESPONSE_SUCCESS:
				dpw_tr.last_result = 0;
				break;
			case TR_RESPONSE_ILLIGAL_REQUEST:
				dpw_tr.last_result = DPW_TR_ERROR_ILLIGAL_REQUEST;
				break;
			case TR_RESPONSE_TIMEOUT:
				dpw_tr.last_result = DPW_TR_ERROR_DATA_TIMEOUT;
				break;
			case TR_RESPONSE_SERVER_FULL:
				dpw_tr.last_result = DPW_TR_ERROR_SERVER_FULL;
				break;
			case TR_RESPONSE_ILLEGAL_DATA:
				dpw_tr.last_result = DPW_TR_ERROR_ILLEGAL_DATA;
				break;
			case TR_RESPONSE_CHEAT_DATA:
				dpw_tr.last_result = DPW_TR_ERROR_CHEAT_DATA;
				break;
			case TR_RESPONSE_NG_POKEMON_NAME:
				dpw_tr.last_result = DPW_TR_ERROR_NG_POKEMON_NAME;
				break;
			case TR_RESPONSE_NG_PARENT_NAME:
				dpw_tr.last_result = DPW_TR_ERROR_NG_PARENT_NAME;
				break;
			case TR_RESPONSE_NG_MAIL_NAME:
				dpw_tr.last_result = DPW_TR_ERROR_NG_MAIL_NAME;
				break;
			case TR_RESPONSE_NG_OWNER_NAME:
				dpw_tr.last_result = DPW_TR_ERROR_NG_OWNER_NAME;
				break;
			case TR_RESPONSE_SERVER_TIMEOUT:
				dpw_tr.last_result = DPW_TR_ERROR_SERVER_TIMEOUT;
				break;
			default:
				DPW_TASSERTMSG(FALSE, "illigal response: %d", dpw_tr.recv_buf[0]);
				dpw_tr.last_result = DPW_TR_ERROR_FATAL;
				break;
			}
			DpwiSessionShutdown();
			break;
		}
		break;
	case DPWi_TR_RROCESS_UPLOADFINISH:
		switch( DpwiSessionThink() ){
		case DPWI_COMMON_SESSION_STATE_ERROR:
			dpw_tr.state = DPWi_TR_END_ASYNC;
			dpw_tr.last_result = Dpwi_Tr_HandleCommonError(DpwiGetLastError());
			DpwiSessionShutdown();
			break;
		case DPWI_COMMON_SESSION_STATE_COMPLETED:
			dpw_tr.state = DPWi_TR_END_ASYNC;
			switch (dpw_tr.recv_buf[0]) {
			case TR_RESPONSE_SUCCESS:
				dpw_tr.last_result = 0;
				break;
			case TR_RESPONSE_ILLIGAL_REQUEST:
				dpw_tr.last_result = DPW_TR_ERROR_ILLIGAL_REQUEST;
				break;
			case TR_RESPONSE_TIMEOUT:
				dpw_tr.last_result = DPW_TR_ERROR_DATA_TIMEOUT;
				break;
			case TR_RESPONSE_NO_DATA:
				dpw_tr.last_result = DPW_TR_ERROR_NO_DATA;
				break;
			case TR_RESPONSE_SERVER_TIMEOUT:
				dpw_tr.last_result = DPW_TR_ERROR_SERVER_TIMEOUT;
				break;
			default:
				DPW_TASSERTMSG(FALSE, "illigal response: %d", dpw_tr.recv_buf[0]);
				dpw_tr.last_result = DPW_TR_ERROR_FATAL;
				break;
			}
			DpwiSessionShutdown();
			break;
		}
		break;
	case DPWi_TR_RROCESS_DOWNLOAD:
		switch( DpwiSessionThink() ){
		case DPWI_COMMON_SESSION_STATE_ERROR:
			dpw_tr.state = DPWi_TR_END_ASYNC;
			dpw_tr.last_result = Dpwi_Tr_HandleCommonError(DpwiGetLastError());
			DpwiSessionShutdown();
			break;
		case DPWI_COMMON_SESSION_STATE_COMPLETED:
			dpw_tr.state = DPWi_TR_END_ASYNC;
			if (DpwiGetResponseSize() == sizeof(Dpw_Tr_Data)) {
				dpw_tr.last_result = 0;
			} else {
				switch (dpw_tr.user_recv_buf[0]) {
				case TR_RESPONSE_NO_DATA:
					dpw_tr.last_result = DPW_TR_ERROR_NO_DATA;
					break;
				case TR_RESPONSE_TIMEOUT:
					dpw_tr.last_result = DPW_TR_ERROR_DATA_TIMEOUT;
					break;
				case TR_RESPONSE_SERVER_TIMEOUT:
					dpw_tr.last_result = DPW_TR_ERROR_SERVER_TIMEOUT;
					break;
				default:
					DPW_TASSERTMSG(FALSE, "illigal response: %d", dpw_tr.user_recv_buf[0]);
					dpw_tr.last_result = DPW_TR_ERROR_FATAL;
					break;
				}
			}
			DpwiSessionShutdown();
			break;
		}
		break;
	case DPWi_TR_RROCESS_GETUPLOADRESULT:
		switch( DpwiSessionThink() ){
		case DPWI_COMMON_SESSION_STATE_ERROR:
			dpw_tr.state = DPWi_TR_END_ASYNC;
			dpw_tr.last_result = Dpwi_Tr_HandleCommonError(DpwiGetLastError());
			DpwiSessionShutdown();
			break;
		case DPWI_COMMON_SESSION_STATE_COMPLETED:
			dpw_tr.state = DPWi_TR_END_ASYNC;
			if (DpwiGetResponseSize() == sizeof(Dpw_Tr_Data)) {
				dpw_tr.last_result = 1;
			} else {
				switch (dpw_tr.user_recv_buf[0]) {
				case TR_RESPONSE_NO_DATA:
					dpw_tr.last_result = DPW_TR_ERROR_NO_DATA;
					break;
				case TR_RESPONSE_TIMEOUT:
					dpw_tr.last_result = DPW_TR_ERROR_DATA_TIMEOUT;
					break;
				case TR_RESPONSE_NOT_EXCHANGED:
					dpw_tr.last_result = 0;
					break;
				case TR_RESPONSE_SERVER_TIMEOUT:
					dpw_tr.last_result = DPW_TR_ERROR_SERVER_TIMEOUT;
					break;
				default:
					DPW_TASSERTMSG(FALSE, "illigal response: %d", dpw_tr.user_recv_buf[0]);
					dpw_tr.last_result = DPW_TR_ERROR_FATAL;
					break;
				}
			}
			DpwiSessionShutdown();
			break;
		}
		break;
	case DPWi_TR_RROCESS_DELETE:
		switch( DpwiSessionThink() ){
		case DPWI_COMMON_SESSION_STATE_ERROR:
			dpw_tr.state = DPWi_TR_END_ASYNC;
			dpw_tr.last_result = Dpwi_Tr_HandleCommonError(DpwiGetLastError());
			DpwiSessionShutdown();
			break;
		case DPWI_COMMON_SESSION_STATE_COMPLETED:
			dpw_tr.state = DPWi_TR_END_ASYNC;
			switch (dpw_tr.recv_buf[0]) {
			case TR_RESPONSE_SUCCESS:
				dpw_tr.last_result = 0;
				break;
			case TR_RESPONSE_NO_DATA:
				dpw_tr.last_result = DPW_TR_ERROR_NO_DATA;
				break;
			case TR_RESPONSE_TIMEOUT:
				dpw_tr.last_result = DPW_TR_ERROR_DATA_TIMEOUT;
				break;
			case TR_RESPONSE_SERVER_TIMEOUT:
				dpw_tr.last_result = DPW_TR_ERROR_SERVER_TIMEOUT;
				break;
			default:
				DPW_TASSERTMSG(FALSE, "illigal response: %d", dpw_tr.recv_buf[0]);
				dpw_tr.last_result = DPW_TR_ERROR_FATAL;
				break;
			}
			DpwiSessionShutdown();
			break;
		}
		break;
	case DPWi_TR_RROCESS_RETURN:
		switch( DpwiSessionThink() ){
		case DPWI_COMMON_SESSION_STATE_ERROR:
			dpw_tr.state = DPWi_TR_END_ASYNC;
			dpw_tr.last_result = Dpwi_Tr_HandleCommonError(DpwiGetLastError());
			DpwiSessionShutdown();
			break;
		case DPWI_COMMON_SESSION_STATE_COMPLETED:
			dpw_tr.state = DPWi_TR_END_ASYNC;
			switch (dpw_tr.recv_buf[0]) {
			case TR_RESPONSE_SUCCESS:
				dpw_tr.last_result = 0;
				break;
			case TR_RESPONSE_NO_DATA:
				dpw_tr.last_result = DPW_TR_ERROR_NO_DATA;
				break;
			case TR_RESPONSE_ILLIGAL_REQUEST:
				dpw_tr.last_result = DPW_TR_ERROR_ILLIGAL_REQUEST;
				break;
			case TR_RESPONSE_TIMEOUT:
				dpw_tr.last_result = DPW_TR_ERROR_DATA_TIMEOUT;
				break;
			case TR_RESPONSE_SERVER_TIMEOUT:
				dpw_tr.last_result = DPW_TR_ERROR_SERVER_TIMEOUT;
				break;
			default:
				DPW_TASSERTMSG(FALSE, "illigal response: %d", dpw_tr.recv_buf[0]);
				dpw_tr.last_result = DPW_TR_ERROR_FATAL;
				break;
			}
			DpwiSessionShutdown();
			break;
		}
		break;
	case DPWi_TR_RROCESS_DOWNLOADMATCHDATA:
		switch( DpwiSessionThink() ){
		case DPWI_COMMON_SESSION_STATE_ERROR:
			dpw_tr.state = DPWi_TR_END_ASYNC;
			dpw_tr.last_result = Dpwi_Tr_HandleCommonError(DpwiGetLastError());
			DpwiSessionShutdown();
			break;
		case DPWI_COMMON_SESSION_STATE_COMPLETED:
			dpw_tr.state = DPWi_TR_END_ASYNC;
			{
				int response_size = DpwiGetResponseSize();
				
				if (response_size >= sizeof(Dpw_Tr_Data)) {
					// �A���Ă����T�C�Y��sizeof(Dpw_Tr_Data)�ȏ�̂Ƃ��́A�f�[�^���A���Ă��Ă���
					dpw_tr.last_result = (s32)(DpwiGetResponseSize() / sizeof(Dpw_Tr_Data));
				} else if (response_size == 0) {
					// �A���Ă����T�C�Y��0�̂Ƃ��́A������Ȃ�����
					dpw_tr.last_result = 0;
				} else {
					// ����ȊO�̂Ƃ��̓T�[�o�[����̃��X�|���X�R�[�h�ɂ��
					switch (dpw_tr.user_recv_buf[0]) {
					case TR_RESPONSE_SERVER_TIMEOUT:
						dpw_tr.last_result = DPW_TR_ERROR_SERVER_TIMEOUT;
						break;
					default:
						DPW_TASSERTMSG(FALSE, "illigal response: %d", dpw_tr.user_recv_buf[0]);
						dpw_tr.last_result = DPW_TR_ERROR_FATAL;
						break;
					}
				}
			}
			DpwiSessionShutdown();
			break;
		}
		break;
	case DPWi_TR_RROCESS_TRADE:
		switch( DpwiSessionThink() ){
		case DPWI_COMMON_SESSION_STATE_ERROR:
			dpw_tr.state = DPWi_TR_END_ASYNC;
			dpw_tr.last_result = Dpwi_Tr_HandleCommonError(DpwiGetLastError());
			DpwiSessionShutdown();
			break;
		case DPWI_COMMON_SESSION_STATE_COMPLETED:
			dpw_tr.state = DPWi_TR_END_ASYNC;
			if (DpwiGetResponseSize() == sizeof(Dpw_Tr_Data)) {
				dpw_tr.last_result = 0;
			} else {
				switch (dpw_tr.user_recv_buf[0]) {
				case TR_RESPONSE_ILLIGAL_REQUEST:
					dpw_tr.last_result = DPW_TR_ERROR_ILLIGAL_REQUEST;
					break;
				case TR_RESPONSE_ILLEGAL_DATA:
					dpw_tr.last_result = DPW_TR_ERROR_ILLEGAL_DATA;
					break;
				case TR_RESPONSE_CHEAT_DATA:
					dpw_tr.last_result = DPW_TR_ERROR_CHEAT_DATA;
					break;
				case TR_RESPONSE_NG_POKEMON_NAME:
					dpw_tr.last_result = DPW_TR_ERROR_NG_POKEMON_NAME;
					break;
				case TR_RESPONSE_NG_PARENT_NAME:
					dpw_tr.last_result = DPW_TR_ERROR_NG_PARENT_NAME;
					break;
				case TR_RESPONSE_NG_MAIL_NAME:
					dpw_tr.last_result = DPW_TR_ERROR_NG_MAIL_NAME;
					break;
				case TR_RESPONSE_NG_OWNER_NAME:
					dpw_tr.last_result = DPW_TR_ERROR_NG_OWNER_NAME;
					break;
				case TR_RESPONSE_SERVER_TIMEOUT:
					dpw_tr.last_result = DPW_TR_ERROR_SERVER_TIMEOUT;
					break;
				default:
					DPW_TASSERTMSG(FALSE, "illigal response: %d", dpw_tr.user_recv_buf[0]);
					dpw_tr.last_result = DPW_TR_ERROR_FATAL;
					break;
				}
			}
			DpwiSessionShutdown();
			break;
		}
		break;
	case DPWi_TR_RROCESS_TRADEFINISH:
		switch( DpwiSessionThink() ){
		case DPWI_COMMON_SESSION_STATE_ERROR:
			dpw_tr.state = DPWi_TR_END_ASYNC;
			dpw_tr.last_result = Dpwi_Tr_HandleCommonError(DpwiGetLastError());
			DpwiSessionShutdown();
			break;
		case DPWI_COMMON_SESSION_STATE_COMPLETED:
			dpw_tr.state = DPWi_TR_END_ASYNC;
			switch (dpw_tr.recv_buf[0]) {
			case TR_RESPONSE_SUCCESS:
				dpw_tr.last_result = 0;
				break;
			case TR_RESPONSE_SERVER_TIMEOUT:
				dpw_tr.last_result = DPW_TR_ERROR_SERVER_TIMEOUT;
				break;
			case TR_RESPONSE_ILLIGAL_REQUEST:
				dpw_tr.last_result = DPW_TR_ERROR_ILLIGAL_REQUEST;
				break;
			}
			DpwiSessionShutdown();
			break;
		}
		break;
	case DPWi_TR_RROCESS_GETSERVERSTATE:
		switch( DpwiSessionThink() ){
		case DPWI_COMMON_SESSION_STATE_ERROR:
			dpw_tr.state = DPWi_TR_END_ASYNC;
			dpw_tr.last_result = Dpwi_Tr_HandleCommonError(DpwiGetLastError());
			DpwiSessionShutdown();
			break;
		case DPWI_COMMON_SESSION_STATE_COMPLETED:
			dpw_tr.state = DPWi_TR_END_ASYNC;
			switch (dpw_tr.recv_buf[0]) {
			case TR_RESPONSE_SUCCESS:
				dpw_tr.last_result = DPW_TR_STATUS_SERVER_OK;
				break;
			case TR_RESPONSE_STOP_SERVICE:
				dpw_tr.last_result = DPW_TR_STATUS_SERVER_STOP_SERVICE;
				break;
			case TR_RESPONSE_SERVER_FULL:
				dpw_tr.last_result = DPW_TR_STATUS_SERVER_FULL;
				break;
			case TR_RESPONSE_SERVER_TIMEOUT:
				dpw_tr.last_result = DPW_TR_ERROR_SERVER_TIMEOUT;
				break;
			default:
				DPW_TASSERTMSG(FALSE, "illigal response: %d", dpw_tr.recv_buf[0]);
				dpw_tr.last_result = DPW_TR_ERROR_FATAL;
				break;
			}
			DpwiSessionShutdown();
			break;
		}
		break;
	case DPWi_TR_CANCEL_UPLOAD:
	case DPWi_TR_CANCEL_UPLOADFINISH:
	case DPWi_TR_CANCEL_DOWNLOAD:
	case DPWi_TR_CANCEL_GETUPLOADRESULT:
	case DPWi_TR_CANCEL_DELETE:
	case DPWi_TR_CANCEL_RETURN:
	case DPWi_TR_CANCEL_DOWNLOADMATCHDATA:
	case DPWi_TR_CANCEL_TRADE:
	case DPWi_TR_CANCEL_TRADEFINISH:
	case DPWi_TR_CANCEL_GETSERVERSTATE:
		dpw_tr.state = DPWi_TR_END_ASYNC;
		dpw_tr.last_result = DPW_TR_ERROR_CANCEL;
		DpwiSessionShutdown();
		break;
	case DPWi_TR_END_ASYNC:
		break;
	}
}

/*!
	�������̊J���ȂǏI���������s���܂��B
	
	���̊֐��́A�񓯊����������s���Ă���Ƃ��ɂ̓R�[�����邱�Ƃ��ł��܂���B
	Dpw_Tr_IsAsyncEnd() �Ŕ񓯊������̏I�����m�F���Ă���R�[�����Ă��������B
*/
void Dpw_Tr_End(void) {
	
	DPW_TASSERTMSG(dpw_tr.state != DPWi_TR_NOT_INIT, "dpw tr is not initialized.\n");
	DPW_TASSERTMSG(dpw_tr.state == DPWi_TR_NORMAL, "async process is running.\n");
	
	dpw_tr.state = DPWi_TR_NOT_INIT;
}

/*!
	Dpw_Tr���C�u�����̔񓯊��������I�����Ă��邩�ۂ���Ԃ��܂��B
	
	�֐����ɁuAsync�v���t���֐����R�[�������ۂ́A���̊֐������I�ɃR�[�����āA�I�����m�F���Ă��������B
	
	@retval TRUE	�񓯊��������I�����Ă���
	@retval FALSE	�񓯊��������I�����Ă��Ȃ�
*/
BOOL Dpw_Tr_IsAsyncEnd(void) {
	
	DPW_TASSERTMSG(dpw_tr.state != DPWi_TR_NOT_INIT, "dpw tr is not initialized.\n");
	
	switch (dpw_tr.state) {
	case DPWi_TR_NORMAL:
		return TRUE;
		break;
	case DPWi_TR_END_ASYNC:
		dpw_tr.state = DPWi_TR_NORMAL;
		return TRUE;
		break;
	default:
		break;
	}

	return FALSE;
}

/*!
	���O�̔񓯊������̌��ʂ��擾���܂��B
	Bpw_Tr_IsAsyncEnd() �ŏI�����m�F���Ă���R�[�����Ă��������B
	
	�񓯊��������s�����ꍇ�́A�K�����̊֐��Ō��ʁi���ɃG���[���N�����Ă��Ȃ����j���m�F���Ă��������B
	�G���[�̎�ނ͔񓯊������ɂ���ĈقȂ�܂����A�ȉ��̃G���[�͋��ʂł��B
	
	@li ::DPW_TR_ERROR_SERVER_TIMEOUT
	@li ::DPW_TR_ERROR_CANCEL
	@li ::DPW_TR_ERROR_FATAL
	@li ::DPW_TR_ERROR_DISCONNECTED
	@li ::DPW_TR_ERROR_FAILURE
	
	@return	�񓯊������̌��ʁB���̒l�̓G���[�������A ::DpwTrError �̒l���Ԃ�܂��B
*/
s32 Dpw_Tr_GetAsyncResult(void) {
	
	DPW_TASSERTMSG(dpw_tr.state != DPWi_TR_NOT_INIT, "dpw tr is not initialized.\n");
	
	return dpw_tr.last_result;
}

/*!
	�|�P�����f�[�^��a���鏈�����J�n���܂��B
	
	���������ꍇ�́A Dpw_Tr_GetAsyncResult() ��0���Ԃ���܂��B
	�G���[���N�������ꍇ�́A���ʂ̃G���[�������͈ȉ��̃G���[���Ԃ���܂��B
	
	@li ::DPW_TR_ERROR_SERVER_FULL		�F �T�[�o�[�̗e�ʃI�[�o�[�ł��B
	@li ::DPW_TR_ERROR_DATA_TIMEOUT		�F �ȑO�a�����f�[�^���^�C���A�E�g���Ă��܂��B�^�}�S��Ԃ��Ă��������B
	@li ::DPW_TR_ERROR_ILLIGAL_REQUEST	�F �T�[�o�[�Ɋ��Ƀf�[�^������܂��B Dpw_Tr_DownloadAsync() �Ŋm�F���Ă��������B
	@li ::DPW_TR_ERROR_ILLEGAL_DATA		�F �A�b�v���[�h���ꂽ�f�[�^�����Ă��܂��B
	@li ::DPW_TR_ERROR_CHEAT_DATA		�F �A�b�v���[�h���ꂽ�f�[�^���s���ł��B
	@li ::DPW_TR_ERROR_NG_POKEMON_NAME	�F �A�b�v���[�h���ꂽ�|�P�����̖��O��NG���[�h���܂�ł��܂��B
	@li ::DPW_TR_ERROR_NG_PARENT_NAME	�F �A�b�v���[�h���ꂽ�|�P�����̐e�̖��O��NG���[�h���܂�ł��܂��B
	@li ::DPW_TR_ERROR_NG_MAIL_NAME		�F �A�b�v���[�h���ꂽ���[���̖��O��NG���[�h���܂�ł��܂��B
	@li ::DPW_TR_ERROR_NG_OWNER_NAME	�F �A�b�v���[�h���ꂽ��l������NG���[�h���܂�ł��܂��B
	
	@param[in] data	�A�b�v���[�h����f�[�^�B�֐����ŃR�s�[���܂��̂ŁA�ÓI�ɕێ�����K�v�͂���܂���B
	
	@sa Dpw_Tr_UploadFinishAsync()
*/
void Dpw_Tr_UploadAsync(const Dpw_Tr_Data* data) {
	
	DPW_TASSERTMSG(dpw_tr.state != DPWi_TR_NOT_INIT, "dpw tr is not initialized.\n");
	DPW_TASSERTMSG(dpw_tr.state == DPWi_TR_NORMAL, "async process is already running.\n");
	DPW_NULL_TASSERT(data);
	
	memcpy(&dpw_tr.send_buf[0], data, sizeof(Dpw_Tr_Data));
	
	// �Z�b�V����������
	DpwiSessionInitialize();

	// �ʐM�J�n
	if (Dpwi_Tr_CallSessionRequest(TR_URL_UPLOAD, dpw_tr.send_buf, sizeof(Dpw_Tr_Data), dpw_tr.recv_buf, 2)) {
		dpw_tr.state = DPWi_TR_RROCESS_UPLOAD;
	} else {
		dpw_tr.state = DPWi_TR_END_ASYNC;
		dpw_tr.last_result = DPW_TR_ERROR_FATAL;
		DpwiSessionShutdown();
	}
}

/*!
	Dpw_Tr_UploadAsync()�ŃA�b�v���[�h�����T�[�o�[��̃f�[�^��L���ɂ��܂��B
	
	���������ꍇ�A Dpw_Tr_GetAsyncResult() ��0���Ԃ���܂��B
	�G���[���N�������ꍇ�́A���ʂ̃G���[�������͈ȉ��̃G���[���Ԃ���܂��B
	
	@li ::DPW_TR_ERROR_NO_DATA			�F �T�[�o�[�Ƀf�[�^�����݂��܂���B�f�[�^�𕜌����Ă��������B
	@li ::DPW_TR_ERROR_DATA_TIMEOUT		�F �ȑO�a�����f�[�^���^�C���A�E�g���Ă��܂��B�^�}�S��Ԃ��Ă��������B
	@li ::DPW_TR_ERROR_ILLIGAL_REQUEST	�F �T�[�o�[�Ɋ��Ƀf�[�^������܂��B Dpw_Tr_DownloadAsync() �Ŋm�F���Ă��������B
	
	@sa Dpw_Tr_UploadAsync()
*/
void Dpw_Tr_UploadFinishAsync(void) {
	
	DPW_TASSERTMSG(dpw_tr.state != DPWi_TR_NOT_INIT, "dpw tr is not initialized.\n");
	DPW_TASSERTMSG(dpw_tr.state == DPWi_TR_NORMAL, "async process is already running.\n");
	
	// �����̃t�����h�L�[�𑗂�
	memcpy(&dpw_tr.send_buf[0], &dpw_tr.friend_key, 8);
	
	// �Z�b�V����������
	DpwiSessionInitialize();

	// �ʐM�J�n
	if (Dpwi_Tr_CallSessionRequest(TR_URL_UPLOADFINISH, dpw_tr.send_buf, 8, dpw_tr.recv_buf, 2)) {
		dpw_tr.state = DPWi_TR_RROCESS_UPLOADFINISH;
	} else {
		dpw_tr.state = DPWi_TR_END_ASYNC;
		dpw_tr.last_result = DPW_TR_ERROR_FATAL;
		DpwiSessionShutdown();
	}
}

/*!
	�������Ō�ɗa�����f�[�^���擾���܂��B
	
	���������ꍇ�A Dpw_Tr_GetAsyncResult() ��0���Ԃ���܂��B
	�G���[���N�������ꍇ�́A���ʂ̃G���[�������͈ȉ��̃G���[���Ԃ���܂��B
	
	@li ::DPW_TR_ERROR_NO_DATA			�F �T�[�o�[�Ƀf�[�^�����݂��܂���B�f�[�^�𕜌����Ă��������B
	@li ::DPW_TR_ERROR_DATA_TIMEOUT		�F �ȑO�a�����f�[�^���^�C���A�E�g���Ă��܂��B�^�}�S��Ԃ��Ă��������B
	
	�T�[�o�[�ɂ���Č������ꂽ��ł��擾�ł��܂��B
	Dpw_Tr_DeleteAsync() �����s������͎擾�ł��܂���B
	
	@param[out] data	�_�E�����[�h�����f�[�^���L�^����o�b�t�@
*/
void Dpw_Tr_DownloadAsync(Dpw_Tr_Data* data) {
	
	DPW_TASSERTMSG(dpw_tr.state != DPWi_TR_NOT_INIT, "dpw tr is not initialized.\n");
	DPW_TASSERTMSG(dpw_tr.state == DPWi_TR_NORMAL, "async process is already running.\n");
	DPW_NULL_TASSERT(data);
	
	dpw_tr.user_recv_buf = (u8*)data;
	
	// �Z�b�V����������
	DpwiSessionInitialize();
	
	// �ʐM�J�n
	if (Dpwi_Tr_CallSessionRequest(TR_URL_DOWNLOAD, dpw_tr.send_buf, 0, data, sizeof(Dpw_Tr_Data))) {
		dpw_tr.state = DPWi_TR_RROCESS_DOWNLOAD;
	} else {
		dpw_tr.state = DPWi_TR_END_ASYNC;
		dpw_tr.last_result = DPW_TR_ERROR_FATAL;
		DpwiSessionShutdown();
	}
}

/*!
	�ȑO�ɗa�����f�[�^���������ꂽ�����T�[�o�[�ɖ₢���킹�A��������Ă����
	�������ꂽ�f�[�^�̃_�E�����[�h�������s���܂��B
	
	�������s�����Ȃ�0���A���������Ȃ��1�� Dpw_Tr_GetAsyncResult() �ŕԂ���܂��B
	�G���[���N�������ꍇ�́A���ʂ̃G���[�������͈ȉ��̃G���[���Ԃ���܂��B
	
	@li ::DPW_TR_ERROR_NO_DATA			�F �T�[�o�[�Ƀf�[�^�����݂��܂���B�f�[�^�𕜌����Ă��������B
	@li ::DPW_TR_ERROR_DATA_TIMEOUT		�F �ȑO�a�����f�[�^���^�C���A�E�g���Ă��܂��B�^�}�S��Ԃ��Ă��������B
	
	�T�[�o�[�ɂČ��������f�[�^�́A Dpw_Tr_Data �^�̈ȉ��̃����o�ł��B����ȊO�͕ύX����܂���B
	
	@li Dpw_Tr_PokemonData postData;
	@li u8 gender;
	@li u16 name[DPW_TR_NAME_SIZE];
	@li u16 trainerID;
	@li u8 countryCode;
	@li s16 localCode;
	@li u8 trainerType;
	@li u8 versionCode;
	
	@param[out] data	�_�E�����[�h�����f�[�^���L�^����o�b�t�@
*/
void Dpw_Tr_GetUploadResultAsync(Dpw_Tr_Data* data) {
	
	DPW_TASSERTMSG(dpw_tr.state != DPWi_TR_NOT_INIT, "dpw tr is not initialized.\n");
	DPW_TASSERTMSG(dpw_tr.state == DPWi_TR_NORMAL, "async process is already running.\n");
	DPW_NULL_TASSERT(data);
	
	dpw_tr.user_recv_buf = (u8*)data;

	// �Z�b�V����������
	DpwiSessionInitialize();
	
	// �ʐM�J�n
	if (Dpwi_Tr_CallSessionRequest(TR_URL_GETUPLOADRESULT, dpw_tr.send_buf, 0, data, sizeof(Dpw_Tr_Data))) {
		dpw_tr.state = DPWi_TR_RROCESS_GETUPLOADRESULT;
	} else {
		dpw_tr.state = DPWi_TR_END_ASYNC;
		dpw_tr.last_result = DPW_TR_ERROR_FATAL;
		DpwiSessionShutdown();
	}
}

/*!
	���łɃA�b�v���[�h����Ă���f�[�^�̍폜���s���܂��B
	���̊֐��́A�����ς݂̃f�[�^���폜����ꍇ�ɂ̂ݎg�p���Ă��������B
	
	���������ꍇ�A Dpw_Tr_GetAsyncResult() ��0���Ԃ���܂��B
	�G���[���N�������ꍇ�́A���ʂ̃G���[�������͈ȉ��̃G���[���Ԃ���܂��B
	
	@li ::DPW_TR_ERROR_NO_DATA			�F �T�[�o�[�Ƀf�[�^�����݂��܂���B�f�[�^�𕜌����Ă��������B
	@li ::DPW_TR_ERROR_DATA_TIMEOUT		�F �ȑO�a�����f�[�^���^�C���A�E�g���Ă��܂��B�^�}�S��Ԃ��Ă��������B
*/
void Dpw_Tr_DeleteAsync(void) {
	
	DPW_TASSERTMSG(dpw_tr.state != DPWi_TR_NOT_INIT, "dpw tr is not initialized.\n");
	DPW_TASSERTMSG(dpw_tr.state == DPWi_TR_NORMAL, "async process is already running.\n");
	
	// �Z�b�V����������
	DpwiSessionInitialize();
	
	// �ʐM�J�n
	if (Dpwi_Tr_CallSessionRequest(TR_URL_DELETE, dpw_tr.send_buf, 0, dpw_tr.recv_buf, 2)) {
		dpw_tr.state = DPWi_TR_RROCESS_DELETE;
	} else {
		dpw_tr.state = DPWi_TR_END_ASYNC;
		dpw_tr.last_result = DPW_TR_ERROR_FATAL;
		DpwiSessionShutdown();
	}
}

/*!
	���łɃA�b�v���[�h����Ă���f�[�^�̍폜���s���܂��B
	���̊֐��́A�T�[�o�[��̃f�[�^����������Ă��Ȃ��ꍇ�̂ݍ폜�ɐ������܂��B
	
	���������ꍇ�A Dpw_Tr_GetAsyncResult() ��0���Ԃ���܂��B
	�G���[���N�������ꍇ�́A���ʂ̃G���[�������͈ȉ��̃G���[���Ԃ���܂��B
	
	@li ::DPW_TR_ERROR_NO_DATA			�F �T�[�o�[�Ƀf�[�^�����݂��܂���B�f�[�^�𕜌����Ă��������B
	@li ::DPW_TR_ERROR_DATA_TIMEOUT		�F �ȑO�a�����f�[�^���^�C���A�E�g���Ă��܂��B�^�}�S��Ԃ��Ă��������B
	@li ::DPW_TR_ERROR_ILLIGAL_REQUEST	�F �f�[�^�������ς݂��������߁A�폜�Ɏ��s���܂����B Dpw_Tr_DownloadAsync() �Ŋm�F���Ă��������B
*/
void Dpw_Tr_ReturnAsync(void) {
	
	DPW_TASSERTMSG(dpw_tr.state != DPWi_TR_NOT_INIT, "dpw tr is not initialized.\n");
	DPW_TASSERTMSG(dpw_tr.state == DPWi_TR_NORMAL, "async process is already running.\n");
	
	// �Z�b�V����������
	DpwiSessionInitialize();
	
	// �ʐM�J�n
	if (Dpwi_Tr_CallSessionRequest(TR_URL_RETURN, dpw_tr.send_buf, 0, dpw_tr.recv_buf, 2)) {
		dpw_tr.state = DPWi_TR_RROCESS_RETURN;
	} else {
		dpw_tr.state = DPWi_TR_END_ASYNC;
		dpw_tr.last_result = DPW_TR_ERROR_FATAL;
		DpwiSessionShutdown();
	}
}

/*!
	Dpw_Tr���C�u�����Ō��ݍs���Ă���񓯊��������L�����Z�����܂��B
	
	�L�����Z�������ꍇ�A Dpw_Tr_GetAsyncResult() �̕Ԓl�� DPW_TR_ERROR_CANCEL �ƂȂ�܂��B
	
	���ɒʐM���I�����Ă��邱�Ƃ�����܂��̂ŁA�L�����Z���͏�ɐ�������Ƃ͌���܂���B
	�L�����Z���ł������ǂ����́A Dpw_Tr_GetAsyncResult() �̕Ԓl�� DPW_TR_ERROR_CANCEL �ƂȂ��Ă��邩�Ŕ��f���Ă��������B
	
	Dpw_Tr_CancelAsync() ���̂��񓯊��������s���܂����A������L�����Z�����邱�Ƃ͂ł��܂���B
*/
void Dpw_Tr_CancelAsync(void) {
	
	DPW_TASSERTMSG(dpw_tr.state != DPWi_TR_NOT_INIT, "dpw tr is not initialized.\n");
	
	switch (dpw_tr.state) {
	case DPWi_TR_RROCESS_UPLOAD:
		DpwiSessionCancel();
		dpw_tr.state = DPWi_TR_CANCEL_UPLOAD;
		break;
	case DPWi_TR_RROCESS_UPLOADFINISH:
		DpwiSessionCancel();
		dpw_tr.state = DPWi_TR_CANCEL_UPLOADFINISH;
		break;
	case DPWi_TR_RROCESS_DOWNLOAD:
		DpwiSessionCancel();
		dpw_tr.state = DPWi_TR_CANCEL_DOWNLOAD;
		break;
	case DPWi_TR_RROCESS_GETUPLOADRESULT:
		DpwiSessionCancel();
		dpw_tr.state = DPWi_TR_CANCEL_GETUPLOADRESULT;
		break;
	case DPWi_TR_RROCESS_DELETE:
		DpwiSessionCancel();
		dpw_tr.state = DPWi_TR_CANCEL_DELETE;
		break;
	case DPWi_TR_RROCESS_RETURN:
		DpwiSessionCancel();
		dpw_tr.state = DPWi_TR_CANCEL_RETURN;
		break;
	case DPWi_TR_RROCESS_DOWNLOADMATCHDATA:
		DpwiSessionCancel();
		dpw_tr.state = DPWi_TR_CANCEL_DOWNLOADMATCHDATA;
		break;
	case DPWi_TR_RROCESS_TRADE:
		DpwiSessionCancel();
		dpw_tr.state = DPWi_TR_CANCEL_TRADE;
		break;
	case DPWi_TR_RROCESS_TRADEFINISH:
		DpwiSessionCancel();
		dpw_tr.state = DPWi_TR_CANCEL_TRADEFINISH;
		break;
	case DPWi_TR_RROCESS_GETSERVERSTATE:
		DpwiSessionCancel();
		dpw_tr.state = DPWi_TR_CANCEL_GETSERVERSTATE;
		break;
	default:
		break;
	}
}

/*!
	�~�����|�P�����f�[�^�ƍ��v�����f�[�^�̃_�E�����[�h���J�n���܂��B
	
	���������ꍇ�� Dpw_Tr_GetAsyncResult() �Ń_�E�����[�h���ꂽ�f�[�^��(0-7)���Ԃ���܂��B
	�G���[���N�������ꍇ�́A���ʂ̃G���[�̂����ꂩ���Ԃ���܂��B
	
	@param[in] searchData	��������|�P�����̃f�[�^�B�֐����ŃR�s�[���܂��̂ŁA�ÓI�ɕێ�����K�v�͂���܂���B
	@param[in] maxNum	�_�E�����[�h����|�P�����f�[�^�̍ő吔(7�܂�)
	@param[out] downloadData	�_�E�����[�h�����f�[�^���L�^����o�b�t�@�BmaxNum�Ŏw�肵�����ȏ�̃T�C�Y��p�ӂ��Ă��������B
*/
void Dpw_Tr_DownloadMatchDataAsync(const Dpw_Tr_PokemonSearchData* searchData, s32 maxNum, Dpw_Tr_Data* downloadData) {
	
	DPW_TASSERTMSG(dpw_tr.state != DPWi_TR_NOT_INIT, "dpw tr is not initialized.\n");
	DPW_TASSERTMSG(dpw_tr.state == DPWi_TR_NORMAL, "async process is already running.\n");
	DPW_NULL_TASSERT(searchData);
	DPW_MINMAX_TASSERT(maxNum, 1, 7);
	DPW_NULL_TASSERT(downloadData);
	
	dpw_tr.user_recv_buf = (u8*)downloadData;
	
	// �Z�b�V����������
	DpwiSessionInitialize();
	
	memcpy(&dpw_tr.send_buf[0], searchData, sizeof(Dpw_Tr_PokemonSearchData));
	dpw_tr.send_buf[sizeof(Dpw_Tr_PokemonSearchData)] = (u8)maxNum;
	
	// �ʐM�J�n
	if (Dpwi_Tr_CallSessionRequest(TR_URL_DOWNLOADMATCHDATA, dpw_tr.send_buf,
								   sizeof(Dpw_Tr_PokemonSearchData) + 1, downloadData, (int)sizeof(Dpw_Tr_Data)*maxNum))
	{
		dpw_tr.state = DPWi_TR_RROCESS_DOWNLOADMATCHDATA;
	} else {
		dpw_tr.state = DPWi_TR_END_ASYNC;
		dpw_tr.last_result = DPW_TR_ERROR_FATAL;
		DpwiSessionShutdown();
	}
}

/*!
	�T�[�o�[���id �̃f�[�^�ƌ������J�n���܂��B
	
	uploadData��downloadData�ɂ͓����|�C���^��^���邱�Ƃ��ł��܂��B
	
	���������ꍇ�A Dpw_Tr_GetAsyncResult() ��0���Ԃ���AdownloadData�Ɍ��������f�[�^������܂��B
	�G���[���N�������ꍇ�́A���ʂ̃G���[�������͈ȉ��̃G���[���Ԃ���܂��B
	
	@li ::DPW_TR_ERROR_ILLIGAL_REQUEST	�F �g���[�h�����s���܂����B�g���[�h���s���O�̏�Ԃɖ߂��Ă��������B
	@li ::DPW_TR_ERROR_ILLEGAL_DATA		�F �A�b�v���[�h���ꂽ�f�[�^�����Ă��܂��B
	@li ::DPW_TR_ERROR_CHEAT_DATA		�F �A�b�v���[�h���ꂽ�f�[�^���s���ł��B
	@li ::DPW_TR_ERROR_NG_POKEMON_NAME	�F �A�b�v���[�h���ꂽ�|�P�����̖��O��NG���[�h���܂�ł��܂��B
	@li ::DPW_TR_ERROR_NG_PARENT_NAME	�F �A�b�v���[�h���ꂽ�|�P�����̐e�̖��O��NG���[�h���܂�ł��܂��B
	@li ::DPW_TR_ERROR_NG_MAIL_NAME		�F �A�b�v���[�h���ꂽ���[���̖��O��NG���[�h���܂�ł��܂��B
	@li ::DPW_TR_ERROR_NG_OWNER_NAME	�F �A�b�v���[�h���ꂽ��l������NG���[�h���܂�ł��܂��B
	
	@param[in] id	���������ID
	@param[in] uploadData	�A�b�v���[�h����f�[�^�B�֐����ŃR�s�[���܂��̂ŁA�ÓI�ɕێ�����K�v�͂���܂���B
	@param[out] downloadData	�_�E�����[�h�����f�[�^���L�^����o�b�t�@
	
	@sa Dpw_Tr_TradeFinish()
*/
void Dpw_Tr_TradeAsync(s32 id, const Dpw_Tr_Data* uploadData, Dpw_Tr_Data* downloadData) {
	
	DPW_TASSERTMSG(dpw_tr.state != DPWi_TR_NOT_INIT, "dpw tr is not initialized.\n");
	DPW_TASSERTMSG(dpw_tr.state == DPWi_TR_NORMAL, "async process is already running.\n");
	DPW_NULL_TASSERT(uploadData);
	DPW_NULL_TASSERT(downloadData);
	
	dpw_tr.user_recv_buf = (u8*)downloadData;
	
	// �Z�b�V����������
	DpwiSessionInitialize();
	
	memcpy(&dpw_tr.send_buf[0], uploadData, sizeof(Dpw_Tr_Data));
//	memcpy(&((Dpw_Tr_Data*)dpw_tr.send_buf)->friend_key, &dpw_tr.friend_key, 8);
	*(s32*)(&dpw_tr.send_buf[sizeof(Dpw_Tr_Data)]) = id;
	
	// �ʐM�J�n
	if (Dpwi_Tr_CallSessionRequest(TR_URL_TRADE, dpw_tr.send_buf, sizeof(Dpw_Tr_Data)+4, downloadData, sizeof(Dpw_Tr_Data))) {
		dpw_tr.state = DPWi_TR_RROCESS_TRADE;
	} else {
		dpw_tr.state = DPWi_TR_END_ASYNC;
		dpw_tr.last_result = DPW_TR_ERROR_FATAL;
		DpwiSessionShutdown();
	}
}

/*!
	Dpw_Tr_TradeAsync() �ŃA�b�v���[�h�����T�[�o�[��̃f�[�^��L���ɂ��܂��B
	
	���������ꍇ�A Dpw_Tr_GetAsyncResult() ��0���Ԃ���܂��B
	�G���[���N�������ꍇ�́A���ʂ̃G���[�������͈ȉ��̃G���[���Ԃ���܂��B
	
	@li ::DPW_TR_ERROR_ILLIGAL_REQUEST	�F �g���[�h�����s���܂����B�g���[�h���s���O�̏�Ԃɖ߂��Ă��������B
*/
void Dpw_Tr_TradeFinishAsync(void) {
	
	DPW_TASSERTMSG(dpw_tr.state != DPWi_TR_NOT_INIT, "dpw tr is not initialized.\n");
	DPW_TASSERTMSG(dpw_tr.state == DPWi_TR_NORMAL, "async process is already running.\n");
	
	// �����̃t�����h�L�[�𑗂�
	memcpy(&dpw_tr.send_buf[0], &dpw_tr.friend_key, 8);
	
	// �Z�b�V����������
	DpwiSessionInitialize();

	// �ʐM�J�n
	if (Dpwi_Tr_CallSessionRequest(TR_URL_TRADEFINISH, dpw_tr.send_buf, 8, dpw_tr.recv_buf, 2)) {
		dpw_tr.state = DPWi_TR_RROCESS_TRADEFINISH;
	} else {
		dpw_tr.state = DPWi_TR_END_ASYNC;
		dpw_tr.last_result = DPW_TR_ERROR_FATAL;
		DpwiSessionShutdown();
	}
}

/*!
	�T�[�o�[��Ԃ̒������J�n���܂��B
	
	�T�[�o�[�Ɛ���ɒʐM�ł����ꍇ�́A Dpw_Tr_GetAsyncResult() �� DpwTrServerStatus �̒l���Ԃ���܂��B
	
	����ɒʐM�ł��Ȃ������ꍇ�́A ���ʂ̃G���[�̂����ꂩ���Ԃ���܂��B
*/
void Dpw_Tr_GetServerStateAsync(void) {
	
	DPW_TASSERTMSG(dpw_tr.state != DPWi_TR_NOT_INIT, "dpw tr is not initialized.\n");
	DPW_TASSERTMSG(dpw_tr.state == DPWi_TR_NORMAL, "async process is already running.\n");
	
	// �Z�b�V����������
	DpwiSessionInitialize();

	// �ʐM�J�n
	if (Dpwi_Tr_CallSessionRequest(TR_URL_GETSERVERSTATE, dpw_tr.send_buf, 0, dpw_tr.recv_buf, 2)) {
		dpw_tr.state = DPWi_TR_RROCESS_GETSERVERSTATE;
	} else {
		dpw_tr.state = DPWi_TR_END_ASYNC;
		dpw_tr.last_result = DPW_TR_ERROR_FATAL;
		DpwiSessionShutdown();
	}
}

#ifndef SDK_FINALROM
/*!
	���E�ʐM�����̃T�[�o��Ԃ����������܂��B
	�����Ńu���b�N���܂��B
	
	���̊֐��́A�f�o�b�O�^�e�X�g�p�ł��BFINALROM�ł͖����ƂȂ�܂��B
	
	@retval TRUE	�������ɐ�������
	@retval FALSE	�������Ɏ��s����
*/
BOOL Dpw_Tr_Db_InitServer(void) {
	
	int ret;
	
	DPW_TASSERTMSG(dpw_tr.state != DPWi_TR_NOT_INIT, "dpw tr is not initialized.\n");
	DPW_TASSERTMSG(dpw_tr.state == DPWi_TR_NORMAL, "async process is already running.\n");
	
	db_ghttp_flag = DB_HTTP_FLAG_NOT_COMPLETED;
	
	(void)DWC_InitGHTTP(NULL);
	
	ret = DWC_GetGHTTPData(TR_URL_INIT, Dpwi_Db_GhttpCopleteCallback, NULL);
	
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
	���E�����ʐM�̃T�[�o�̈�����̃A�b�v�f�[�g���s���܂��B
	�����Ńu���b�N���܂��B
	
	���̊֐��́A�f�o�b�O�^�e�X�g�p�ł��BFINALROM�ł͖����ƂȂ�܂��B
*/
BOOL Dpw_Tr_Db_UpdateServer(void) {
	
	int ret;
	
	DPW_TASSERTMSG(dpw_tr.state != DPWi_TR_NOT_INIT, "dpw tr is not initialized.\n");
	DPW_TASSERTMSG(dpw_tr.state == DPWi_TR_NORMAL, "async process is already running.\n");
	
	db_ghttp_flag = DB_HTTP_FLAG_NOT_COMPLETED;
	
	(void)DWC_InitGHTTP(NULL);
	
	ret = DWC_GetGHTTPData(TR_URL_UPDATE, Dpwi_Db_GhttpCopleteCallback, NULL);
	
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
	���E�ʐM�����́A�a�����Ă���|�P��������������鏇�Ԃ�ύX���܂��B
	���̏����́A���i�ŃT�[�o�[�ł͈���Ɉ��s����\��ł��B
	
	���̊֐��́A�f�o�b�O�^�e�X�g�p�ł��BFINALROM�ł͖����ƂȂ�܂��B
*/
BOOL Dpw_Tr_Db_ShuffleServerData(void) {
	
	int ret;
	
	DPW_TASSERTMSG(dpw_tr.state != DPWi_TR_NOT_INIT, "dpw tr is not initialized.\n");
	DPW_TASSERTMSG(dpw_tr.state == DPWi_TR_NORMAL, "async process is already running.\n");
	
	db_ghttp_flag = DB_HTTP_FLAG_NOT_COMPLETED;
	
	(void)DWC_InitGHTTP(NULL);
	
	ret = DWC_GetGHTTPData(TR_URL_SHUFFLE, Dpwi_Db_GhttpCopleteCallback, NULL);
	
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

static BOOL Dpwi_Tr_CallSessionRequest(const u8* url, const void* data, int len, void* resbuf, int ressize) {
	
	switch (DpwiSessionRequest(url, dpw_tr.pid, data, len, (u8*)resbuf, ressize)) {
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

static DpwTrError Dpwi_Tr_HandleCommonError(DpwiHttpError error) {
	
	DpwTrError ret;
	
	OS_TPrintf("[DPW TR] ghttp error: %d\n", error);
	
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
		ret = DPW_TR_ERROR_FATAL;
		break;
	case DPWI_COMMON_SESSION_ERROR_INSUFFICIENT_MEMORY:	// �������s�� 
	case DPWI_COMMON_SESSION_ERROR_OUT_OF_MEMORY:		// ���������蓖�Ď��s 
	case DPWI_COMMON_SESSION_ERROR_MEMORY_ERROR: 		// ���������蓖�Ď��s 
		DPW_TASSERTMSG(FALSE, "common session memory shortage.");
		ret = DPW_TR_ERROR_FATAL;
		break;
	case DPWI_COMMON_SESSION_ERROR_HOST_LOOKUP_FAILED:	// �z�X�g���������s 
		OS_TPrintf("[DPW TR] dns lookup failed.\n");
		ret = DPW_TR_ERROR_FAILURE;
		break;
	case DPWI_COMMON_SESSION_ERROR_SOCKET_FAILED:		// �\�P�b�g�̍쐬�A�������A�ǂݏo���A�������ݎ��s 
	case DPWI_COMMON_SESSION_ERROR_CONNECT_FAILED:		// HTTP�T�[�o�ւ̐ڑ����s 
		OS_TPrintf("[DPW TR] socket error.\n");
		ret = DPW_TR_ERROR_FAILURE;
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
		OS_TPrintf("[DPW TR] server internal error.  please contact server administrator.\n");
		ret = DPW_TR_ERROR_SERVER_TIMEOUT;
		break;
	case DPWI_COMMON_SESSION_ERROR_REQUEST_REJECTED:	// HTTP�T�[�o�̃��N�G�X�g���� 
	case DPWI_COMMON_SESSION_ERROR_TOKEN_EXPIRED:		// COMMON�w: �g�[�N���̗L�������؂�
		OS_TPrintf("[DPW TR] server is now heavy.\n");
		ret = DPW_TR_ERROR_SERVER_TIMEOUT;
		break;
	default:
		DPW_TASSERTMSG(FALSE, "illigal ghttp error: %d", error);
		ret = DPW_TR_ERROR_FATAL;
		break;
	}
	
	// FATAL�G���[�łȂ��ꍇ
	if (ret != DPW_TR_ERROR_FATAL) {
#ifdef _NITRO
		// NitroWiFi�̃��C���[�Ŗ������؂�Ă��Ȃ����`�F�b�N����
		if (WCM_GetPhase() != WCM_PHASE_DCF) {
			OS_TPrintf("[DPW TR] disconnected from access point.\n");
			ret = DPW_TR_ERROR_DISCONNECTED;
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

