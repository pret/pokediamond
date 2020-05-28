//============================================================================================
/**
 * @file	tvwork_local.h
 * @brief	�e���r�f�[�^�̃��R�[�h�R�[�i�[�����鏈��
 * @author	tamada GAME FREAK inc.
 * @date	2006.05.31
 */
//============================================================================================

#ifndef	__TVWORK_LOCAL_H__
#define	__TVWORK_LOCAL_H__

#include "savedata/tv_work.h"

//----------------------------------------------------------
//----------------------------------------------------------
enum {
	MY_TOPIC_COMMON_MAX = 4,
	MY_WATCH_MAX = MY_TOPIC_COMMON_MAX,
	MY_RECORD_MAX = MY_TOPIC_COMMON_MAX,
	MY_QANDA_MAX = MY_TOPIC_COMMON_MAX,

	OTHER_WATCH_MAX = 16,
	OTHER_RECORD_MAX = 8,
	OTHER_QANDA_MAX = 8,

	USED_TOPIC_MAX = 4,
};

#define	BROADCAST_MAX		3

//----------------------------------------------------------
/**
 * @brief	�g�s�b�N�f�[�^�{��
 */
//----------------------------------------------------------
struct TVTOPIC{
	u8 topic_id;			///<�g�s�b�NID
	u8 see_count;			///<�����񐔃J�E���^
	GF_DATE date;			///<������t
	u8 data[TOPIC_DATA_SIZE];
};

//----------------------------------------------------------
/**
 * @brief	�����g�s�b�N�f�[�^
 *
 * �g�s�b�N�f�[�^�ȊO�ɕt��������̂͂Ȃ�
 */
//----------------------------------------------------------
struct MY_TOPIC{
	TVTOPIC topic;		///<�g�s�b�N�f�[�^�{��
};

//----------------------------------------------------------
/**
 * @brief	���l�g�s�b�N�f�[�^
 *
 * �g�s�b�N�f�[�^�{����ҏ��Ȃǂ��t�������
 */
//----------------------------------------------------------
struct OTHER_TOPIC{
	u32 owner_id;			///<�����ID
	u8 sex;					///<����Ґ���
	u8 rom_ver;				///<����ROM�o�[�W����
	u8 region_code;			///<����ROM���R�[�h
	STRCODE owner_name[PERSON_NAME_SIZE + EOM_SIZE];	///<����Җ�
	TVTOPIC topic;		///<�g�s�b�N�f�[�^�{��
};

//----------------------------------------------------------
/**
 * @brief	�e���r�����Z�[�u�f�[�^
 */
//----------------------------------------------------------
struct TV_WORK {
	u8 used_index[USED_TOPIC_MAX];				///<�����ς݃f�[�^�C���f�b�N�X
	int minute_count;							///<�������ԗp�J�E���^
	u8 end_flag;								///<���f�I���t���O

	MY_TOPIC MyWatchTopic[MY_WATCH_MAX];		///<�����g�s�b�N�f�[�^�F�Ď��^�ԑg
	MY_TOPIC MyRecordTopic[MY_RECORD_MAX];		///<�����g�s�b�N�f�[�^�F�M�l�X�^�ԑg
	MY_TOPIC MyQandATopic[MY_QANDA_MAX];		///<�����g�s�b�N�f�[�^�F����^�ԑg

	OTHER_TOPIC OtherWatchTopic[OTHER_WATCH_MAX];	///<���l�g�s�b�N�f�[�^�F�Ď��^�ԑg
	OTHER_TOPIC OtherRecordTopic[OTHER_RECORD_MAX];	///<���l�g�s�b�N�f�[�^�F�M�l�X�^�ԑg
	OTHER_TOPIC OtherQandATopic[OTHER_QANDA_MAX];	///<���l�g�s�b�N�f�[�^�F����^�ԑg

	TOPICTEMP_CONTEST ContestTemp;			///<����^�F�R���e�X�g�p�󋵕ێ����[�N
	TOPICTEMP_PARK ParkTemp;				///<����^�F�A����������p�󋵕ێ����[�N
	TOPICTEMP_PORUTO PorutoTemp;			///<����^�F�|���g�p�󋵕ێ����[�N
	TOPICTEMP_BTOWER BTowerTemp;			///<����^�F�o�g���^���[�p�󋵕ێ����[�N
	TOPICTEMP_SAFARI SafariTemp;			///<�Ď��^�F�T�t�@���p�󋵕ێ����[�N
};

#endif	//__TVWORK_LOCAL_H__

