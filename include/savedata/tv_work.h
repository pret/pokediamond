//============================================================================================
/**
 * @file	tv_work.h
 * @brief
 * @author	tamada GAME FREAK inc.
 * @date	2006.05.11
 */
//============================================================================================
#ifndef	__TV_WORK_H__
#define	__TV_WORK_H__

#include "savedata/savedata_def.h"
#include "gflib/gf_date.h"
//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	�e���r�ԑg�f�[�^�ւ̕s���S�^��`
 */
//----------------------------------------------------------
typedef struct TV_WORK TV_WORK;

typedef struct TVTOPIC TVTOPIC;
typedef struct MY_TOPIC MY_TOPIC;
typedef struct OTHER_TOPIC OTHER_TOPIC;
typedef OTHER_TOPIC SEND_TOPIC;

//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	�e���r�g�s�b�N�̎��
 */
//----------------------------------------------------------
typedef enum {
	TVTOPICTYPE_NOTHING = 0,
	TVTOPICTYPE_INTERVIEW,		///<����^�g�s�b�N
	TVTOPICTYPE_WATCH,			///<�Ď��^�g�s�b�N
	TVTOPICTYPE_RECORD,			///<�M�l�X�^�g�s�b�N
	TVTOPICTYPE_EVENT,			///<�C�x���g�^�g�s�b�N

	TVTOPICTYPE_MAX,
}TVTOPICTYPE;

//----------------------------------------------------------
/**
 * @brief	�ėp�g�s�b�N���e�ێ����[�N�̃T�C�Y
 */
//----------------------------------------------------------
enum {
	TOPIC_DATA_SIZE = 40,
};

//----------------------------------------------------------
/**
 * @brief	�R���e�X�g�p�󋵕ێ����[�N��`
 */
//----------------------------------------------------------
typedef struct TOPICTEMP_CONTEST{
	u8 exist_flag;
	u16 monsno;
	u8 mons_sex;
	u8 mons_region;
	u8 mons_rom;
	u8 contest_rank;
	u8 contest_type;
	u8 contest_result;
}TOPICTEMP_CONTEST;

//----------------------------------------------------------
/**
 * @brief	�A����������ł̏E������
 */
//----------------------------------------------------------
enum {
	PARKPICK_ID_NOTHING = 0,	///<�E���Ă��Ȃ�
	PARKPICK_ID_ITEM,			///<�A�C�e���E����
	PARKPICK_ID_ACCESSORIES,	///<�A�N�Z�T���E����
};
//----------------------------------------------------------
/**
 * @brief	���R�����p�󋵕ێ����[�N��`
 */
//----------------------------------------------------------
typedef struct TOPICTEMP_PARK {
	u8 exist_flag;
	u16 monsno;
	u8 mons_sex;
	u8 mons_region;
	u8 mons_rom;
	u8 nickname_flag;
	STRCODE nickname[MONS_NAME_SIZE + EOM_SIZE];
	u8 poke_character;			///<�|�P�����̐��i
	u8 pick_type;				///<�Ō�ɏE�������̂̎��
	u8 accessories;				///<�E�����A�N�Z�T��
	u16 item_no;				///<�E�����A�C�e��
}TOPICTEMP_PARK;

//----------------------------------------------------------
/**
 * @brief	�|���g�~�j�Q�[���p�󋵕ێ����[�N��`
 */
//----------------------------------------------------------
typedef struct TOPICTEMP_PORUTO {
	u8 exist_flag;		///<�f�[�^���݃`�F�b�N
	u8 taste_type;		///<�|���g�̎�ށi���j
}TOPICTEMP_PORUTO;

//----------------------------------------------------------
/**
 * @brief	�o�g���^���[�p�󋵕ێ����[�N��`
 */
//----------------------------------------------------------
typedef struct TOPICTEMP_BTOWER {
	u8 exist_flag;		///<�f�[�^���݃`�F�b�N
	u8 continue_flag;	///<�A�������ǂ����̃`�F�b�N
	u16 win_count;		///<���̎��_�ł̘A����
} TOPICTEMP_BTOWER;

//----------------------------------------------------------
/**
 * @brief	�T�t�@���p�󋵕ێ����[�N��`
 */
//----------------------------------------------------------
typedef struct TOPICTEMP_SAFARI {
	u8 exist_flag;
	u16 monsno;
	u8 mons_sex;
	u8 mons_region;
	u8 mons_rom;
	u8 capture_count;
}TOPICTEMP_SAFARI;

//============================================================================================
//
//			�֐��O���Q�Ɛ錾
//
//============================================================================================
//----------------------------------------------------------
//	�Z�[�u�f�[�^�֘A����
//----------------------------------------------------------
extern int TVWORK_GetWorkSize(void);
extern void TVWORK_Init(TV_WORK * tv);
extern TV_WORK * SaveData_GetTvWork(SAVEDATA * sv);

//----------------------------------------------------------
//	���Ԃɂ��ԑg�X�V����
//----------------------------------------------------------
extern void TVWORK_UpdateMinuteCount(TV_WORK * tvwk, int min_diff, int now_minute);

extern MY_TOPIC * TVWORK_GetMyTopicByIndex(TV_WORK * tvwk, TVTOPICTYPE topic_type, int index);
extern OTHER_TOPIC * TVWORK_GetOtherTopicByIndex(TV_WORK * tvwk, TVTOPICTYPE topic_type, int index);

//----------------------------------------------------------
//�g�s�b�N�̒ǉ�����
//----------------------------------------------------------
extern BOOL TVWORK_MakeTopic(TV_WORK * tvwk, TVTOPICTYPE topic_type, int topic_id, const u8 * data);

//----------------------------------------------------------
//	�ԑg���e����֘A
//----------------------------------------------------------
extern int TVWORK_SearchTopics(const TV_WORK * tvwk, TVTOPICTYPE topic_type,
		int topic_id, BOOL mine, BOOL see, u8 * array);
extern BOOL TVWORK_EnableMakeTopic(TV_WORK * tvwk, TVTOPICTYPE topic_type, int topic_id);
extern BOOL TVWORK_IsUsedTopicIndex(const TV_WORK * tvwk, int index);
extern void TVWORK_SetUsedTopicIndex(TV_WORK * tvwk, int index);
extern BOOL TVWORK_IsProgramEnd(const TV_WORK * tvwk);
extern void TVWORK_SetProgramEnd(TV_WORK * tvwk, BOOL flag);
extern void TVWORK_StartProgram(TV_WORK * tvwk);

extern int TVWORK_GetUsedTopicNumber(const TV_WORK * tvwk);

//----------------------------------------------------------
//	�g�s�b�N�̃N���A
//----------------------------------------------------------
extern void TVWORK_ClearMyTopic(TV_WORK * tvwk);
extern void TVWORK_ClearOtherTopic(TV_WORK * tvwk);

//----------------------------------------------------------
//	OTHER_TOPIC����̎擾����
//----------------------------------------------------------
extern const STRCODE * OTHERTOPIC_GetName(const OTHER_TOPIC * ot);
extern int OTHERTOPIC_GetSex(const OTHER_TOPIC * ot);
extern int OTHERTOPIC_GetRegionCode(const OTHER_TOPIC * ot);
extern int OTHERTOPIC_GetRomVersion(const OTHER_TOPIC * ot);
extern int OTHERTOPIC_GetSenderID(const OTHER_TOPIC * ot);
extern u32 OTHERTOPIC_GetOwnerID(const OTHER_TOPIC * ot);
extern TVTOPIC * OTHERTOPIC_GetTopicData(OTHER_TOPIC * ot);

//----------------------------------------------------------
//	MY_TOPIC����̎擾����
//----------------------------------------------------------
extern TVTOPIC * MYTOPIC_GetTopic(MY_TOPIC * mt);

//----------------------------------------------------------
//	TVTOPIC�֘A
//----------------------------------------------------------
extern void TVTOPIC_CountUpBroadcast(TVTOPIC * topic);
extern void * TVTOPIC_GetData(TVTOPIC * topic);
extern int TVTOPIC_GetTopicID(const TVTOPIC * topic);

extern GF_DATE TVTOPIC_GetDate(const TVTOPIC * topic);
extern int TVTOPIC_GetSeeCount(const TVTOPIC * topic);

extern BOOL TVWORK_IsMineIndex(int index);
extern int TVWORK_MakeOtherIndex(int index);

//----------------------------------------------------------
//	�󋵕ێ����[�N�̎擾
//----------------------------------------------------------
extern TOPICTEMP_CONTEST * TVWORK_GetContestTemp(TV_WORK * tvwk);
extern TOPICTEMP_PARK * TVWORK_GetParkTemp(TV_WORK * tvwk);
extern TOPICTEMP_PORUTO * TVWORK_GetPorutoTemp(TV_WORK * tvwk);
extern TOPICTEMP_BTOWER * TVWORK_GetBTowerTemp(TV_WORK * tvwk);
extern TOPICTEMP_SAFARI * TVWORK_GetSafariTemp(TV_WORK * tvwk);

//----------------------------------------------------------
//	���R�[�h�֘A
//
//	���풓�̈�ɔz�u����Ă��Ȃ����߁A���R�[�h���炵���ĂԂ��Ƃ͂ł��Ȃ�
//----------------------------------------------------------
extern u32 TVWORK_GetSendQandADataSize(const SAVEDATA * sv);
extern u32 TVWORK_GetSendWatchDataSize(const SAVEDATA * sv);
extern u32 TVWORK_GetSendRecordDataSize(const SAVEDATA * sv);

extern SEND_TOPIC * TVWORK_AllocSendQandAData(SAVEDATA * sv, int headID, u32 size);
extern SEND_TOPIC * TVWORK_AllocSendWatchData(SAVEDATA * sv, int headID, u32 size);
extern SEND_TOPIC * TVWORK_AllocSendRecordData(SAVEDATA * sv, int headID, u32 size);

extern void TVWORK_MixWatchData(TV_WORK * tv, int member, int my_id, const void ** darray);
extern void TVWORK_MixRecordData(TV_WORK * tv, int member, int my_id, const void ** darray);
extern void TVWORK_MixQandAData(TV_WORK * tv, int member, int my_id, const void ** darray);

//----------------------------------------------------------
//		�f�o�b�O�p
//----------------------------------------------------------
#ifdef	PM_DEBUG
extern void TVWORK_DEBUG_Info(const TV_WORK * tvwk);
#endif

#endif	/* __TV_WORK_H__ */

