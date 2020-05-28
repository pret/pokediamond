/*---------------------------------------------------------------------------*
  Project:  DP WiFi Library
  File:     dpw_tr.h

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
		@li Dpw_Tr_Data::mail ���폜���܂����B
		@li Dpw_Tr_PokemonData �̑傫����172�o�C�g�ɕύX���܂����B
		@li ::DpwTrError �ŁANG���[�h�Ɋւ���G���[���ו������܂����B
		@li Dpw_Tr_Db_ShuffleServerData() ��ǉ����܂����B
	@version beta1	(2006/3/17)
		@li ���ł������[�X���܂����B
*/

#ifndef DPW_TR_H_
#define DPW_TR_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _NITRO
#include <dwc.h>
#else
#include <nitro.h>
#include <dwc.h>
#endif


#define DPW_SERVER_PUBLIC
//#define DPW_SERVER_SUB

/*-----------------------------------------------------------------------*
					�^�E�萔�錾
 *-----------------------------------------------------------------------*/

//! ���O�̃T�C�Y
#define DPW_TR_NAME_SIZE 8

//! Dpw_Tr_DownloadMatchDataAsync() �Ŏ擾�\�ȃf�[�^�̍ő�l
#define DPW_TR_DOWNLOADMATCHDATA_MAX	7

//! Dpw_Tr_Callback �̌��ʂ��G���[�ƂȂ�ꍇ�̎��
typedef enum {
	DPW_TR_ERROR_SERVER_FULL = -1,		//!< �T�[�o�[�e�ʃI�[�o�[
	DPW_TR_ERROR_SERVER_TIMEOUT = -2,	//!< �T�[�o�[����̉������Ȃ�
	DPW_TR_ERROR_NO_DATA = -3,			//!< �T�[�o�Ƀf�[�^�����݂��Ȃ��B�f�[�^�𕜌����Ă��������B
	DPW_TR_ERROR_DATA_TIMEOUT = -4,		//!< �a�����f�[�^�̃^�C���A�E�g�B�^�}�S��߂��Ă��������B
	DPW_TR_ERROR_ILLIGAL_REQUEST = -5,	//!< �T�[�o�ւ̕s���ȗv���B���ɗa���Ă���̂ɗa���悤�Ƃ����Ƃ��ȂǁB
	DPW_TR_ERROR_ILLEGAL_DATA = -6,		//!< �A�b�v���[�h���ꂽ�f�[�^�����Ă���B
	DPW_TR_ERROR_CHEAT_DATA = -7,		//!< �A�b�v���[�h���ꂽ�f�[�^���s��
	DPW_TR_ERROR_NG_POKEMON_NAME = -8,	//!< �A�b�v���[�h���ꂽ�|�P�����̖��O��NG���[�h���܂�ł���
	DPW_TR_ERROR_NG_PARENT_NAME = -9,	//!< �A�b�v���[�h���ꂽ�|�P�����̐e�̖��O��NG���[�h���܂�ł���
	DPW_TR_ERROR_NG_MAIL_NAME = -10,	//!< �A�b�v���[�h���ꂽ���[���̖��O��NG���[�h���܂�ł���
	DPW_TR_ERROR_NG_OWNER_NAME = -11,	//!< �A�b�v���[�h���ꂽ��l������NG���[�h���܂�ł���
	DPW_TR_ERROR_CANCEL	= -12,			//!< ������ Dpw_Tr_CancelAsync() �ɂ���ăL�����Z�����ꂽ�B
	DPW_TR_ERROR_FATAL = -13,			//!< �ʐM�v���I�G���[�B�d���̍ē������K�v�ł�
	DPW_TR_ERROR_DISCONNECTED = -14,	//!< �ʐM�s�\�G���[�B���C�u�����̏��������K�v�ł��B
	DPW_TR_ERROR_FAILURE = -15			//!< �ʐM���s�G���[�B���g���C���Ă�������
} DpwTrError;

//! �T�[�o�[�X�e�[�^�X
typedef enum {
	DPW_TR_STATUS_SERVER_OK,				//!< ����
	DPW_TR_STATUS_SERVER_STOP_SERVICE,		//!< �T�[�r�X�ꎞ��~��
	DPW_TR_STATUS_SERVER_FULL				//!< �T�[�o�[�e�ʃI�[�o�[
} DpwTrServerStatus;

//! �����\����
typedef struct {
	u16 year;	//!< �N
	u8 month;	//!< ��
	u8 day;		//!< ��
	u8 hour;	//!< ��
	u8 minutes;	//!< ��
	u8 sec;		//!< �b
	u8 padding;	// �p�f�B���O
} Dpw_Tr_Date;

//! �|�P�����̐���
typedef enum {
	DPW_TR_GENDER_MALE = 1,		//!< �I�X
	DPW_TR_GENDER_FEMALE = 2,	//!< ���X
	DPW_TR_GENDER_NONE = 3		//!< ���ʂȂ��B�������ɐ��ʂ���Ȃ��悤�ɂ��邽�߂ɂ́A���̒l���w�肵�Ă��������B
} Dpw_Tr_PokemonGender;

//! �|�P�����f�[�^�̃T�[�o�[�����p�\����
typedef struct {
	s16 characterNo;	//!< �L�����N�^�ԍ�
	s8 gender;			//!< ���ʁB Dpw_Tr_PokemonGender �̒l�ɂȂ�B
	s8 level;			//!< ���x���B
} Dpw_Tr_PokemonDataSimple;

//! �|�P�����f�[�^�̃T�[�o�[���������\����
typedef struct {
	s16 characterNo;	//!< �L�����N�^�ԍ�
	s8 gender;			//!< ���ʁB Dpw_Tr_PokemonGender �̒l�ɂȂ�B
	s8 level_min;		//!< ���x���̉����B0�͎w��Ȃ��A1�`100�͂��̃��x���ȏ�̃|�P�����Ƃ����Ӗ��ɂȂ�B
	s8 level_max;		//!< ���x���̏���B0�͎w��Ȃ��A1�`100�͂��̃��x���ȉ��̃|�P�����Ƃ����Ӗ��ɂȂ�B
	s8 padding;			// �p�f�B���O
} Dpw_Tr_PokemonSearchData;

//! �|�P�����̃f�[�^�B�f�[�^�̓��e�͌��m���Ȃ�
typedef struct {
	u8 data[236];		//!< �|�P�����̃f�[�^
} Dpw_Tr_PokemonData;

//! Dpw_Tr���C�u�����ŃT�[�o�[�Ƃ���肳��郁�C���f�[�^�\����
typedef struct {
	Dpw_Tr_PokemonData postData;			//!< �u�a����v�|�P�����̏ڍ׃f�[�^
	Dpw_Tr_PokemonDataSimple postSimple;	//!< �u�a����v�|�P�����̊ȗ��f�[�^�i�T�[�o�[�����p�j
	Dpw_Tr_PokemonSearchData wantSimple;	//!< �u�ق����v�|�P�����̊ȗ��f�[�^�i�T�[�o�[�����p�j
	u8 gender;								//!< ��l���̐���
	u8 padding;								// �p�f�B���O
	Dpw_Tr_Date postDate;					//!< �a���������i�T�[�o�[�ɂăZ�b�g�j
	Dpw_Tr_Date tradeDate;					//!< �������������i�T�[�o�[�ɂăZ�b�g�j
	s32 id;									//!< ���̃f�[�^��ID�i�T�[�o�[�ɂăZ�b�g�j
	u16 name[DPW_TR_NAME_SIZE];				//!< ��l����
	u16 trainerID;							//!< �g���[�i�[��ID
	u8 countryCode;							//!< �Z��ł��鍑�R�[�h
	u8 localCode;							//!< �Z��ł���n���R�[�h
	u8 trainerType;							//!< �g���[�i�[�^�C�v
	s8 isTrade;								//!< �����ς݃t���O�i�T�[�o�[�ɂăZ�b�g�j
	u8 versionCode;							//!< �o�[�W�����R�[�h
	u8 langCode;							//!< ����R�[�h
} Dpw_Tr_Data;


/*-----------------------------------------------------------------------*
					�O���[�o���ϐ���`
 *-----------------------------------------------------------------------*/



/*-----------------------------------------------------------------------*
					�֐��O���錾
 *-----------------------------------------------------------------------*/

extern void Dpw_Tr_Init(s32 pid, u64 friend_key);
extern void Dpw_Tr_Main(void);
extern void Dpw_Tr_End(void);
extern BOOL Dpw_Tr_IsAsyncEnd(void);
extern s32 Dpw_Tr_GetAsyncResult(void);
extern void Dpw_Tr_UploadAsync(const Dpw_Tr_Data* data);
extern void Dpw_Tr_UploadFinishAsync(void);
extern void Dpw_Tr_DownloadAsync(Dpw_Tr_Data* data);
extern void Dpw_Tr_GetUploadResultAsync(Dpw_Tr_Data* data);
extern void Dpw_Tr_DeleteAsync(void);
extern void Dpw_Tr_ReturnAsync(void);
extern void Dpw_Tr_CancelAsync(void);
extern void Dpw_Tr_DownloadMatchDataAsync(const Dpw_Tr_PokemonSearchData* searchData, s32 maxNum, Dpw_Tr_Data* downloadData);
extern void Dpw_Tr_TradeAsync(s32 id, const Dpw_Tr_Data* uploadData, Dpw_Tr_Data* downloadData);
extern void Dpw_Tr_TradeFinishAsync(void);
extern void Dpw_Tr_GetServerStateAsync(void);

#ifndef SDK_FINALROM
BOOL Dpw_Tr_Db_InitServer(void);
BOOL Dpw_Tr_Db_UpdateServer(void);
BOOL Dpw_Tr_Db_ShuffleServerData(void);
#else
#define Dpw_Tr_Db_InitServer( ... )		(NULL)
#define Dpw_Tr_Db_UpdateServer( ... )	(NULL)
#define Dpw_Tr_Db_ShuffleServerData( ... )	(NULL)
#endif


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif // DPW_TR_H_