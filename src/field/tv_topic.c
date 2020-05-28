//============================================================================================
/**
 * @file	tv_topic.c
 * @brief	�e���r�g�s�b�N�����E�����p
 * @author	tamada GAME FREAK inc.
 * @date	2006.05.19
 */
//============================================================================================

#include "common.h"
#include "system/gamedata.h"

#include "fieldsys.h"
#include "fieldmap_work.h"

#include "savedata/tv_work.h"

#include "tv_define.h"

#include "system/pm_rtc.h"
#include "ev_time.h"

#include "tv.h"

#include "tv_topic.h"
#include "field/tvtopic_battle.h"
#include "field/tvtopic_extern.h"

#include "msgdata/msg.naix"

#include "system/pm_rtc.h"
#include "gflib/strbuf_family.h"
#include "system/wordset.h"

#include "savedata/randomgroup.h"
#include "savedata/imageclip_data.h"
#include "savedata/seedbed.h"
#include "savedata/zukanwork.h"
#include "savedata/encount.h"
#include "generate_zone.h"
#include "field/eventflag.h"
#include "zonedata.h"
#include "itemtool/nuts.h"
#include "field/poketch.h"

#include "sysflag.h"
#include "ev_pokemon.h"

#include "mapdefine.h"
#include "weather_sys.h"
#include "mapdata_weather.h"

#include "system/arc_tool.h"
#include "../arc/tv.naix"

#include "msgdata/msg.naix"
#include "msgdata/msg_tv_program.h"
#include "msgdata/msg_tvcm.h"
#include "msgdata/msg_msg_tv_01.h"
#include "msgdata/msg_msg_tv_02.h"
#include "msgdata/msg_msg_tv_03.h"
#include "msgdata/msg_msg_tv_04.h"

//============================================================================================
//============================================================================================

//--------------------------------------------------------------------
///	�_�~�[��`
//--------------------------------------------------------------------
typedef struct {
	u8 dummy[TOPIC_DATA_SIZE];
}TOPIC_DUMMY_DATA;


//--------------------------------------------------------------------
/**
 * @brief	�o�g���ł̃e���r�g�s�b�N�p��񃏁[�N��`
 *
 *
 * �Ď��^�P�A�Q�F�ߊl
 */
//--------------------------------------------------------------------
struct TVWATCH_BATTLE_WORK{
	int win_lose_flag;
	u16 ball_count;
	u16 monsno;
	u8 mons_sex;
	u8 mons_region;
	u8 mons_rom;
	u8 nickname_flag;
	STRCODE nickname[MONS_NAME_SIZE + EOM_SIZE];
	u16 ball_item_no;
};

//--------------------------------------------------------------------
///	�Ď��^�R�F��
//--------------------------------------------------------------------
typedef struct {
	u16 monsno;
	u8 mons_sex;
	u8 mons_region;
	u8 mons_rom;
	u16 itemno;
	BOOL success_flag;
}WATCH_FISHING_WORK;
//--------------------------------------------------------------------
///	�Ď��^�S�O���[�v��芷���C�Q�O�O���[�v�쐬�p��`
//--------------------------------------------------------------------
typedef struct {
	STRCODE groupname[MONS_NAME_SIZE + EOM_SIZE];
}WATCH_GROUP_WORK;

//--------------------------------------------------------------------
///	�Ď��^�U�F�B���A�C�e�������p��`
//--------------------------------------------------------------------
typedef struct {
	u16 item_no;
	u16 place_name_id;
}WATCH_HIDEITEM_WORK;

//--------------------------------------------------------------------
///	�Ď��^�W�F�^�}�S�z���p��`
//--------------------------------------------------------------------
typedef struct {
	u16 monsno;
	u8 mons_sex;
	u8 mons_region;
	u8 mons_rom;
	u16 place_name_id;
}WATCH_HATCHEGG_WORK;
//--------------------------------------------------------------------
///	�Ď��P�O�F�������f
//--------------------------------------------------------------------
typedef struct {
	u16 monsno;
	u8 mons_sex;
	u8 mons_region;
	u8 mons_rom;
	STRCODE newname[MONS_NAME_SIZE + EOM_SIZE];
}WATCH_MONSNAMECHG_WORK;

//--------------------------------------------------------------------
///	�Ď��P�R�F�n���A�C�e��
//--------------------------------------------------------------------
typedef struct {
	u16 fossil_type;
	u16 fossil_num;
}WATCH_DIG_FOSSIL_WORK;

//--------------------------------------------------------------------
///	�Ď��P�T�F�T�t�@��
//--------------------------------------------------------------------
typedef struct {
	u16 monsno;
	u8 mons_sex;
	u8 mons_region;
	u8 mons_rom;
	u8 get_count;
}WATCH_SAFARI_WORK;

//--------------------------------------------------------------------
///	�Ď��P�V�F������
//--------------------------------------------------------------------
typedef struct {
	u16 monsno;
	u8 mons_sex;
	u8 mons_region;
	u8 mons_rom;
	u16 itemno;
}WATCH_KANPO_WORK;

//--------------------------------------------------------------------
///	�Ď��P�W�C�P�X�A�M�l�X�O�U�F���̂ݖL��A�s��A���l
//--------------------------------------------------------------------
typedef struct {
	u16 nuts_item_no;
	u8	hp;
	u16 nuts_count;
}COMMON_TAKE_NUTS_WORK;
//--------------------------------------------------------------------
///	�Ď��Q�P�F�J�X�^���J�v�Z��
//--------------------------------------------------------------------
typedef struct {
	u16 monsno;
	u8 mons_sex;
	u8 mons_region;
	u8 mons_rom;
	u8 rand;
	u8 seal_no;
}WATCH_CUSTOMCAPSULE_WORK;

//--------------------------------------------------------------------
///	�Ď��Q�Q�A�Q�R�F����������E�������ꂽ
//--------------------------------------------------------------------
typedef struct {
	int size;
	u8 data[TOPIC_DATA_SIZE - sizeof(int)];
}WATCH_UG_FLAG_WORK;

//--------------------------------------------------------------------
///	�M�l�X�^�O�P�F�o�g���^���[�A����
//--------------------------------------------------------------------
typedef struct {
	u16 renshou;
	u16 monsno;
	u8 mons_sex;
	u8 mons_region;
	u8 mons_rom;
	u8 IsSingleFlag;
}RECORD_BTOWER_WORK;
//--------------------------------------------------------------------
///	�M�l�X�^�O�R�F�傫����׋L�^
//--------------------------------------------------------------------
typedef struct {
	u16 monsno;
	u8 mons_sex;
	u8 mons_region;
	u8 mons_rom;
	u32 size;
}RECORD_OOKISA_WORK;
//--------------------------------------------------------------------
///	�M�l�X�^�O�S�F�X���b�g�B�l
//--------------------------------------------------------------------
typedef struct {
	u32 start_coin;
	u32 end_coin;
	u32 playtime;
}RECORD_SLOT_WORK;
//--------------------------------------------------------------------
///	�M�l�X�^�O�W�F���i�������l
//--------------------------------------------------------------------
typedef struct {
	u16	trap_no;
	u16 remove_count;
}RECORD_REMOVE_TRAP_WORK;
//--------------------------------------------------------------------
///	�M�l�X�^�O�X�F�n�^�g�����l
//--------------------------------------------------------------------
typedef struct {
	u16 flag_count;
}RECORD_GET_FLAG_WORK;
//--------------------------------------------------------------------
///	����^�O�Q�F�o�g���^���[
//--------------------------------------------------------------------
typedef struct {
	TOPICTEMP_BTOWER btower;
	PMS_WORD word;
}QANDA_BTOWER_WORK;
//--------------------------------------------------------------------
///	����^�O�S�F�|�P����
//--------------------------------------------------------------------
typedef struct {
	u16 monsno;
	u8 mons_sex;
	u8 mons_region;
	u8 mons_rom;
	u8 nickname_flag;
	STRCODE nickname[MONS_NAME_SIZE + EOM_SIZE];
	PMS_WORD word;
}QANDA_POKEMON_WORK;
//--------------------------------------------------------------------
///	����^�O�U�F�|�P�b�`
//--------------------------------------------------------------------
typedef struct {
	int poketch_id;
	PMS_WORD word;
}QANDA_POKETCH_WORK;
//--------------------------------------------------------------------
///	����^�O�V�F�R���e�X�g
//--------------------------------------------------------------------
typedef struct {
	TOPICTEMP_CONTEST contest;
	PMS_WORD word;
}QANDA_CONTEST_WORK;
//--------------------------------------------------------------------
///	����^�O�X�F�N���b�v
//--------------------------------------------------------------------
typedef struct {
	u16 monsno;
	PMS_WORD word;
}QANDA_CLIP_WORK;
//--------------------------------------------------------------------
///	����^�P�O�F�^�C�v
//--------------------------------------------------------------------
typedef struct {
	int type;
}QANDA_POKETYPE_WORK;

//--------------------------------------------------------------------
///	����^�P�P�F�|���g
//--------------------------------------------------------------------
typedef struct {
	TOPICTEMP_PORUTO poruto;
	PMS_WORD word;
}QANDA_PORUTO_WORK;
//--------------------------------------------------------------------
///	����^�P�R�F�A�����
//--------------------------------------------------------------------
typedef struct {
	TOPICTEMP_PARK park;
	PMS_WORD word;
}QANDA_PARK_WORK;

//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N�ێ��f�[�^�p���L�̒�`
 */
//--------------------------------------------------------------------
typedef union {
//�_�~�[��`
	TOPIC_DUMMY_DATA DummyData;

//�Ď��^�p
	TVWATCH_BATTLE_WORK WatchCaptureWork;
	WATCH_FISHING_WORK WatchFishingWork;
	WATCH_GROUP_WORK WatchGroupWork;
	WATCH_HIDEITEM_WORK WatchHideItemWork;
	WATCH_HATCHEGG_WORK WatchHatchEggWork;
	WATCH_MONSNAMECHG_WORK WatchMonsNameChgWork;
	WATCH_DIG_FOSSIL_WORK WatchDigFossilWork;
	WATCH_SAFARI_WORK WatchSafariWork;
	WATCH_KANPO_WORK WatchKanpoWork;
	COMMON_TAKE_NUTS_WORK TakeNutsWork;
	WATCH_CUSTOMCAPSULE_WORK WatchCustomCapsuleWork;
	WATCH_UG_FLAG_WORK WatchUgFlagWork;

//�M�l�X�^�p
	RECORD_BTOWER_WORK RecordBTowerWork;
	RECORD_OOKISA_WORK RecordOokisaWork;
	RECORD_SLOT_WORK RecordSlotWork;
	RECORD_REMOVE_TRAP_WORK RecordRemoveTrapWork;
	RECORD_GET_FLAG_WORK RecordGetFlagWork;

//����^�p
	QANDA_BTOWER_WORK QandABtowerWork;
	QANDA_POKEMON_WORK QandAPokemonWork;
	QANDA_POKETCH_WORK QandAPoketchWork;
	QANDA_CONTEST_WORK QandAContestWork;
	QANDA_CLIP_WORK QandAClipWork;
	QANDA_POKETYPE_WORK QandAPokeTypeWork;
	QANDA_PORUTO_WORK QandAPorutoWork;
	QANDA_PARK_WORK QandAParkWork;
}TOPIC_DATA;


//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N�����֐��̌^��`
 */
//--------------------------------------------------------------------
typedef int (* MAKE_TOPIC_FUNC)(FIELDSYS_WORK *, WORDSET *, TVBCD *);

//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N���������`�F�b�N�֐��̌^��`
 */
//--------------------------------------------------------------------
typedef BOOL (* CHK_LIMIT_FUNC)(FIELDSYS_WORK *, TVBCD *);

typedef struct {
	MAKE_TOPIC_FUNC make_func;
	CHK_LIMIT_FUNC chk_limit_func;
}TOPIC_FUNC_DATA;

typedef struct {
	TVTOPICTYPE topic_type;
	u16 arc_id;
	u16 topic_max;
	const TOPIC_FUNC_DATA * func_data;
}TOPIC_INFO_DATA;

static const TOPIC_FUNC_DATA WatchNewsFuncTable[TVTOPIC_WATCH_MAX - 1];
static const TOPIC_FUNC_DATA RecordNewsFuncTable[TVTOPIC_RECORD_MAX - 1];
static const TOPIC_FUNC_DATA QandANewsFuncTable[TVTOPIC_INTERVIEW_TYPE_MAX - 1];
static const TOPIC_FUNC_DATA EventNewsFuncTable[TVTOPIC_EVENT_TYPE_MAX - 1];

//--------------------------------------------------------------------
//--------------------------------------------------------------------
static const TOPIC_INFO_DATA TopicInfoData[] = {
	{
		TVTOPICTYPE_INTERVIEW,
		NARC_msg_msg_tv_01_dat,
		TVTOPIC_INTERVIEW_TYPE_MAX,
		QandANewsFuncTable,
	},
	{
		TVTOPICTYPE_WATCH,
		NARC_msg_msg_tv_02_dat,
		TVTOPIC_WATCH_MAX,
		WatchNewsFuncTable,
	},
	{
		TVTOPICTYPE_RECORD,
		NARC_msg_msg_tv_03_dat,
		TVTOPIC_RECORD_MAX,
		RecordNewsFuncTable,
	},
	{
		TVTOPICTYPE_EVENT,
		NARC_msg_msg_tv_04_dat,
		TVTOPIC_EVENT_TYPE_MAX,
		EventNewsFuncTable,
	},
};

//============================================================================================
//============================================================================================
//--------------------------------------------------------------------
///	�g�s�b�N��`�f�[�^�擾
//--------------------------------------------------------------------
static const TOPIC_INFO_DATA * GetBCData(TVTOPICTYPE topic_type)
{
	const TOPIC_INFO_DATA * tpdata;
	GF_ASSERT(TVTOPICTYPE_NOTHING< topic_type && topic_type < TVTOPICTYPE_MAX);
	tpdata = &TopicInfoData[topic_type - 1];
	GF_ASSERT(tpdata->topic_type == topic_type);
	return tpdata;
}

//--------------------------------------------------------------------
///	�g�s�b�N�֐��擾
//--------------------------------------------------------------------
static const TOPIC_FUNC_DATA * GetFuncData(const TOPIC_INFO_DATA * tpdata, const TVBCD * bcd)
{
	int topic_id;
	topic_id = TVBCD_GetTopicID(bcd);
	GF_ASSERT(0 < topic_id && topic_id < tpdata->topic_max);
	return &(tpdata->func_data[topic_id - 1]);
}

//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N��������
 *
 * @param	topic_type	��������g�s�b�N�̎�ށiTVTOPICTYPE�j
 * @param	fsys		�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	ws			WORDSET�ւ̃|�C���^
 * @param	bcd			�������e�f�[�^�ւ̃|�C���^
 * @return	int			��������MSG��ID
 *
 * MSG��ID��Ԃ��ƂƂ��ɁAWORDSET�ɕK�v�ȍ��ړo�^���s��
 */
//--------------------------------------------------------------------
int TVTOPIC_Make(TVTOPICTYPE topic_type, FIELDSYS_WORK * fsys, WORDSET * ws, TVBCD * bcd, u16 * arc_id)
{
	MAKE_TOPIC_FUNC func;
	const TOPIC_INFO_DATA * tpdata;
	const TOPIC_FUNC_DATA * funcdata;
	
	tpdata = GetBCData(topic_type);
	*arc_id = tpdata->arc_id;
	funcdata = GetFuncData(tpdata, bcd);
	func = funcdata->make_func;
	GF_ASSERT(func != NULL);
	return func(fsys, ws, bcd);
}

//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N�����`�F�b�N
 *
 * @param	topic_type	��������g�s�b�N�̎�ށiTVTOPICTYPE�j
 * @param	fsys		�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	bcd			�������e�f�[�^�ւ̃|�C���^
 * @return	BOOL		�����ł��邩�ǂ���
 */
//--------------------------------------------------------------------
BOOL TVTOPIC_CheckLimit(TVTOPICTYPE topic_type, FIELDSYS_WORK * fsys, TVBCD * bcd)
{
	CHK_LIMIT_FUNC check_func;
	const TOPIC_INFO_DATA * tpdata;
	const TOPIC_FUNC_DATA * funcdata;
	
	tpdata = GetBCData(topic_type);
	funcdata = GetFuncData(tpdata, bcd);
	if (funcdata->make_func == NULL) {
		//�����֐����Ȃ��ꍇ�́A�������ŕ������Ȃ�
		return FALSE;
	}
	check_func = funcdata->chk_limit_func;
	if (check_func == NULL) {
		//�`�F�b�N�֐����Ȃ��ꍇ�͖������ɕ����ł���
		return TRUE;
	}
	return check_func(fsys, bcd);
}




//============================================================================================
//
//
//			���ʃc�[���֐�
//
//
//============================================================================================
//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N�o�^�Ăяo��
 * @param	fsys
 * @param	prog_type
 * @param	topic_id
 * @param	data
 */
//--------------------------------------------------------------------
static void MakeTopic(FIELDSYS_WORK * fsys, int prog_type, int topic_id, const void * data)
{
	TV_WORK * tvwk = SaveData_GetTvWork(fsys->savedata);

	//�ėp�f�[�^�T�C�Y�͂S�O�o�C�g�Œ�łȂ���΂Ȃ�Ȃ�
	GF_ASSERT(sizeof(TOPIC_DATA) == TOPIC_DATA_SIZE);

	TVWORK_MakeTopic(tvwk, prog_type, topic_id, (const u8 *)data);
}


//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void WORDSET_RegisterSTRCODE(WORDSET * ws, int buf_id,
		const STRCODE * str, int sex, int region, int single)
{
	STRBUF * strbuf = STRBUF_Create(64, HEAPID_FIELD);
	STRBUF_SetStringCode(strbuf, str);
	WORDSET_RegisterWord(ws, buf_id, strbuf, sex, single, region);
	STRBUF_Delete(strbuf);
}

//--------------------------------------------------------------------
/**
 * @brief	�����f�[�^�̐���Җ���o�^����
 */
//--------------------------------------------------------------------
static void WORDSET_RegisterOwnerName(WORDSET * ws, int buf_id, const TVBCD * bcd)
{
	WORDSET_RegisterSTRCODE(ws, buf_id, TVBCD_GetName(bcd),
			TVBCD_GetSex(bcd), TVBCD_GetRegionCode(bcd), TRUE);
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void GetNickNameSTRCODE(int heapID, STRCODE * namebuf, POKEMON_PARAM * pp)
{
	STRBUF * strbuf = STRBUF_Create(64, heapID);
	PokeParaGet(pp, ID_PARA_nickname_buf, strbuf);
	STRBUF_GetStringCode(strbuf, namebuf, MONS_NAME_SIZE + EOM_SIZE);
	STRBUF_Delete(strbuf);

}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void SetMonsParams(POKEMON_PARAM * pp, u16 * monsno, u8 * sex, u8 * region, u8 * rom)
{
	*monsno = PokeParaGet(pp, ID_PARA_monsno, NULL);
	*sex = PokeParaGet(pp, ID_PARA_sex, NULL);
	*region = PokeParaGet(pp, ID_PARA_country_code, NULL);
	*rom = PokeParaGet(pp, ID_PARA_get_cassette, NULL);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void WORDSET_RegisterMonsName(WORDSET * ws, int buf_id, u16 monsno,
		u8 sex, u8 region, u8 rom)
{
	STRCODE monsname[MONS_NAME_SIZE + EOM_SIZE];
	MSGDAT_MonsNameGet(monsno, HEAPID_FIELD, monsname);
	WORDSET_RegisterSTRCODE(ws, buf_id, monsname, sex, region, TRUE);

}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void WORDSET_RegisterMonsNameEasy(WORDSET * ws, int buf_id, u16 monsno)
{
	STRCODE monsname[MONS_NAME_SIZE + EOM_SIZE];
	MSGDAT_MonsNameGet(monsno, HEAPID_FIELD, monsname);
	WORDSET_RegisterSTRCODE(ws, buf_id, monsname, PM_MALE, PM_LANG, TRUE);
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void StoreNickName(int heapID, POKEMON_PARAM * pp, u8 * nickname_flag, STRCODE * nickname)
{
	*nickname_flag = PokeParaGet(pp, ID_PARA_nickname_flag, NULL);
	if (*nickname_flag) {
		STRBUF * strbuf = STRBUF_Create(64, heapID);
		PokeParaGet(pp, ID_PARA_nickname_buf, strbuf);
		STRBUF_GetStringCode(strbuf, nickname, MONS_NAME_SIZE + EOM_SIZE);
		STRBUF_Delete(strbuf);
	}
}

//============================================================================================
//
//
//				�g�s�b�N�����p�󋵕ێ�
//
//
//============================================================================================
//--------------------------------------------------------------------
/**
 * @brief	�R���e�X�g�I���󋵂̕ێ�
 * @param	tvwk		�e���r�Z�[�u�f�[�^�ւ̃|�C���^
 * @param	pp			�Q�������|�P������POKEMON_PARAM�ւ̃|�C���^
 * @param	type		�R���e�X�g�̎��
 * @param	rank		�R���e�X�g�����N
 * @param	result		�R���e�X�g����
 *
 * �R���e�X�g���I�������Ƃ��ɂ�т����Ă�������
 */
//--------------------------------------------------------------------
void TVTOPIC_ContestTemp_Set(TV_WORK * tvwk, POKEMON_PARAM * pp,
		int type, int rank, int result)
{
	TOPICTEMP_CONTEST * pcnt = TVWORK_GetContestTemp(tvwk);

	pcnt->exist_flag = TRUE;
	SetMonsParams(pp, &pcnt->monsno, &pcnt->mons_sex, &pcnt->mons_region, &pcnt->mons_rom);
	pcnt->contest_type = type;
	pcnt->contest_rank = rank;
	pcnt->contest_result = result;
}

//--------------------------------------------------------------------
/**
 * @brief	�A����������󋵂̕ێ��F�A��čs���|�P����
 * @param	tvwk		�e���r�Z�[�u�f�[�^�ւ̃|�C���^
 * @param	pp			�A��čs���|�P������POKEMON_PARAM
 *
 * �A��čs���|�P���������肵���Ƃ��ɌĂяo���Ă�������
 */
//--------------------------------------------------------------------
void TVTOPIC_ParkTemp_Init(TV_WORK * tvwk, POKEMON_PARAM * pp, int heapID)
{
	TOPICTEMP_PARK * ptemp = TVWORK_GetParkTemp(tvwk);

	ptemp->exist_flag = TRUE;
	ptemp->pick_type = PARKPICK_ID_NOTHING;
	ptemp->poke_character = PokeSeikakuGet(pp);
	SetMonsParams(pp, &ptemp->monsno, &ptemp->mons_sex, &ptemp->mons_region, &ptemp->mons_rom);
	ptemp->nickname_flag = PokeParaGet(pp, ID_PARA_nickname_flag, NULL);
	StoreNickName(heapID, pp, &ptemp->nickname_flag, ptemp->nickname);
}

//--------------------------------------------------------------------
/**
 * @brief	�A����������󋵂̕ێ��F�A�N�Z�T���擾
 * @param	tvwk		�e���r�Z�[�u�f�[�^�ւ̃|�C���^
 * @param	accessories		�E�����A�N�Z�T����ID
 *
 *
 * �A�N�Z�T�����E�����Ƃ��ɌĂяo���Ă�������
 */
//--------------------------------------------------------------------
void TVTOPIC_ParkTemp_SetAccessories(TV_WORK * tvwk, int accessories)
{
	TOPICTEMP_PARK * ptemp = TVWORK_GetParkTemp(tvwk);

	ptemp->pick_type = PARKPICK_ID_ACCESSORIES;
	ptemp->accessories = accessories;
}

//--------------------------------------------------------------------
/**
 * @brief	�A����������󋵂̕ێ��F�A�C�e���擾
 * @param	tvwk		�e���r�Z�[�u�f�[�^�ւ̃|�C���^
 * @param	item_no		�E�����A�C�e��
 *
 *
 * �A�C�e�����E�����Ƃ��ɌĂяo���Ă�������
 */
//--------------------------------------------------------------------
void TVTOPIC_ParkTemp_SetKinomi(TV_WORK * tvwk, int item_no)
{
	TOPICTEMP_PARK * ptemp = TVWORK_GetParkTemp(tvwk);

	ptemp->pick_type = PARKPICK_ID_ITEM;
	ptemp->item_no = item_no;
}

//--------------------------------------------------------------------
/**
 * @brief	�|���g�~�j�Q�[���󋵂̕ێ�
 * @param	tvwk		�e���r�Z�[�u�f�[�^�ւ̃|�C���^
 * @param	taste_type	�|���g�̎��
 *
 * �|���g���쐬�����Ƃ��ɌĂяo���Ă�������
 */
//--------------------------------------------------------------------
void TVTOPIC_PorutoTemp_Set(TV_WORK * tvwk, int taste_type)
{
	TOPICTEMP_PORUTO * poruto = TVWORK_GetPorutoTemp(tvwk);

	poruto->exist_flag = TRUE;
	poruto->taste_type = taste_type;
}

//--------------------------------------------------------------------
/**
 * @brief	�o�g���^���[�󋵂̕ێ�
 * @param	tvwk		�e���r�Z�[�u�f�[�^�ւ̃|�C���^
 * @param	continue_flag		�����������Â��Ă��邩�ǂ���
 *
 * �o�g���^���[�̎�t�ɖ߂����Ƃ��ɌĂяo���Ă�������
 */
//--------------------------------------------------------------------
void TVTOPIC_BTowerTemp_Set(TV_WORK * tvwk, BOOL continue_flag, u16 win_count)
{
	TOPICTEMP_BTOWER * bt = TVWORK_GetBTowerTemp(tvwk);

	bt->exist_flag = TRUE;
	bt->continue_flag = continue_flag;
	bt->win_count = win_count;

}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
void TVTOPIC_SafariTemp_Init(TV_WORK * tvwk)
{
	TOPICTEMP_SAFARI * psaf = TVWORK_GetSafariTemp(tvwk);

	psaf->exist_flag = TRUE;
	psaf->capture_count = 0;
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
void TVTOPIC_SafariTemp_Set(TV_WORK * tvwk, POKEMON_PARAM * pp)
{
	TOPICTEMP_SAFARI * psaf = TVWORK_GetSafariTemp(tvwk);
	if (psaf->capture_count == 0) {
		SetMonsParams(pp, &psaf->monsno, &psaf->mons_sex, &psaf->mons_region, &psaf->mons_rom);
	}
	psaf->capture_count ++;
}



//============================================================================================
//
//
//				�Ď��^�g�s�b�N
//
//
//============================================================================================
//============================================================================================
//	�O�Q�|�O�P�A�O�Q�|�O�Q	�ߊl	
//============================================================================================
//--------------------------------------------------------------------
/**
 */
//--------------------------------------------------------------------
TVWATCH_BATTLE_WORK * TVWatchBattleWork_Create(int heapID)
{
	TVWATCH_BATTLE_WORK * tvwbw;
	tvwbw = sys_AllocMemory(heapID, sizeof(TVWATCH_BATTLE_WORK));
	MI_CpuClearFast(tvwbw, sizeof(TVWATCH_BATTLE_WORK));
	return tvwbw;
}

//--------------------------------------------------------------------
/**
 */
//--------------------------------------------------------------------
void TVWatchBattleWork_Delete(TVWATCH_BATTLE_WORK * tvwbw)
{
	sys_FreeMemoryEz(tvwbw);
}

//--------------------------------------------------------------------
/**
 * @brief	�e���r�g�s�b�N���������F�o�g���ߊl
 * @param	tvwbw			�e���r�g�s�b�N�p���ێ����[�N
 * @param	pp				�Ώۂ̃|�P����
 * @param	win_lose_flag	�퓬����
 * @param	ball_count		�g�p�����{�[���̐�
 * @param	heapID			���p�\�ȃq�[�v�w��
 */
//--------------------------------------------------------------------
void TVBATTLE_StoreResult(TVWATCH_BATTLE_WORK * tvwbw, POKEMON_PARAM * pp,
		int win_lose_flag, int ball_count, u32 heapID)
{
	MI_CpuClear32(tvwbw, sizeof(TVWATCH_BATTLE_WORK));

	/* �ǂ���炱�̎��_�ł�win_lose_flag�̓Z�b�g����Ă��Ȃ��炵�� */
	tvwbw->win_lose_flag = win_lose_flag;
	tvwbw->ball_count = ball_count;
	SetMonsParams(pp, &tvwbw->monsno, &tvwbw->mons_sex, &tvwbw->mons_region, &tvwbw->mons_rom);

	tvwbw->ball_item_no = PokeParaGet(pp, ID_PARA_get_ball, NULL);
	GF_ASSERT(tvwbw->ball_item_no);
	StoreNickName(heapID, pp, &tvwbw->nickname_flag, tvwbw->nickname);
}
//--------------------------------------------------------------------
/**
 * @brief	�e���r�g�s�b�N�����F�ߊl
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	tvwbw			�e���r�g�s�b�N�p���ێ����[�N
 */
//--------------------------------------------------------------------
void TVTOPIC_Entry_Watch_Capture(FIELDSYS_WORK * fsys,
		const TVWATCH_BATTLE_WORK * wcw_result, int win_lose_flag)
{
	TOPIC_DATA TopicData;
	TVWATCH_BATTLE_WORK * tvwbw = &TopicData.WatchCaptureWork;

	*tvwbw = *wcw_result;
	tvwbw->win_lose_flag = win_lose_flag;

	if (tvwbw->ball_count == 0) {
		//�{�[���𓊂��Ă��Ȃ��ꍇ�A�������Ȃ�
		return;
	}

	if (tvwbw->ball_count > 999) {
		//�\����3���܂łȂ̂Ő�������
		tvwbw->ball_count = 999;
	}
	
	switch (win_lose_flag) {
	case FIGHT_POKE_GET:
		MakeTopic(fsys, TVTOPICTYPE_WATCH, TVTOPIC_WATCH_POKE_GET_SUCCESS, tvwbw);
		break;
	case FIGHT_WIN:
	case FIGHT_ESCAPE:
	case FIGHT_ENEMY_ESCAPE:
		if (tvwbw->ball_count > 2) {
			MakeTopic(fsys, TVTOPICTYPE_WATCH, TVTOPIC_WATCH_POKE_GET_FAILURE, tvwbw);
		}
		break;
	}
}

//--------------------------------------------------------------------
//�|�P�����ߊl�����I	�|�P�����ߊl�I����
//--------------------------------------------------------------------
static int TVTOPIC_Make_Watch_SuccessCapture(FIELDSYS_WORK * fsys, WORDSET * ws, TVBCD * bcd)
{
	TVWATCH_BATTLE_WORK * tvwbw = TVBCD_GetTopicData(bcd);

	if (tvwbw->nickname_flag) {
		//�j�b�N�l�[���������ꍇ
		WORDSET_RegisterOwnerName(ws, 0, bcd);		//�g���[�i�[��
		WORDSET_RegisterMonsName(ws, 1, tvwbw->monsno,
				tvwbw->mons_sex, tvwbw->mons_region, tvwbw->mons_rom);
		WORDSET_RegisterItemName(ws, 2, tvwbw->ball_item_no);
		WORDSET_RegisterNumber(ws, 3, tvwbw->ball_count, 3,
				NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT);
		WORDSET_RegisterSTRCODE(ws, 4, tvwbw->nickname,
				tvwbw->mons_sex, tvwbw->mons_region, TRUE);
		return msg_tv_02_01_01;
	} else {
		//�j�b�N�l�[�������Ȃ������ꍇ
		WORDSET_RegisterOwnerName(ws, 0, bcd);		//�g���[�i�[��
		WORDSET_RegisterMonsName(ws, 1, tvwbw->monsno,
				tvwbw->mons_sex, tvwbw->mons_region, tvwbw->mons_rom);
		WORDSET_RegisterItemName(ws, 2, tvwbw->ball_item_no);
		WORDSET_RegisterNumber(ws, 3, tvwbw->ball_count, 3,
				NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT);
		return msg_tv_02_01_02;
	}
}

//--------------------------------------------------------------------
//�|�P�����ߊl���s		�{�[�������R�ȏ�œ|���A������
//--------------------------------------------------------------------
static int TVTOPIC_Make_Watch_FailureCapture(FIELDSYS_WORK * fsys, WORDSET * ws, TVBCD * bcd)
{
	TVWATCH_BATTLE_WORK * tvwbw = TVBCD_GetTopicData(bcd);
	WORDSET_RegisterOwnerName(ws, 0, bcd);		//�g���[�i�[��
	WORDSET_RegisterNumber(ws, 1, tvwbw->ball_count, 3,
			NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT);
	if (tvwbw->win_lose_flag == FIGHT_WIN) {
		return msg_tv_02_02_01;
	} else {
		return msg_tv_02_02_02;
	}
}
//--------------------------------------------------------------------
///	�g�s�b�N�����`�F�b�N�F�|�P�����ߊl
//--------------------------------------------------------------------
static BOOL TVTOPIC_Limit_Watch_Capture(FIELDSYS_WORK * fsys, TVBCD * bcd)
{
	ZUKAN_WORK * zw = SaveData_GetZukanWork(fsys->savedata);
	TVWATCH_BATTLE_WORK * tvwbw = TVBCD_GetTopicData(bcd);
	return ZukanWork_GetPokeSeeFlag(zw, tvwbw->monsno);
}

//============================================================================================
//	�O�Q�|�O�R	��
//============================================================================================
//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N�����F���E��ނ�I
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	success_flag	�����������ǂ���
 * @param	itemno			�g�p�����肴���̃A�C�e���i���o�[
 * @param	pp				�ނ�グ���|�P������POKEMON_PARAM�ւ̃|�C���^
 *
 * �ނ�グ���Ȃ������ꍇ�Asuccess_flag == FALSE��PP==NULL�ł悢
 */
//--------------------------------------------------------------------
void TVTOPIC_Entry_Watch_Fishing(FIELDSYS_WORK * fsys, BOOL success_flag,
		u16 itemno, POKEMON_PARAM * pp)
{
	TOPIC_DATA TopicData;
	WATCH_FISHING_WORK * wfw = &TopicData.WatchFishingWork;

	if (success_flag) {
		SetMonsParams(pp, &wfw->monsno, &wfw->mons_sex, &wfw->mons_region, &wfw->mons_rom);
	}
	wfw->itemno = itemno;
	wfw->success_flag = success_flag;

	MakeTopic(fsys, TVTOPICTYPE_WATCH, TVTOPIC_WATCH_FISHING, wfw);
}
//--------------------------------------------------------------------
///	�g�s�b�N�����F���E��ނ�I
//--------------------------------------------------------------------
static int TVTOPIC_Make_Watch_Fishing(FIELDSYS_WORK * fsys, WORDSET * ws, TVBCD * bcd)
{
	WATCH_FISHING_WORK * wfw = (WATCH_FISHING_WORK * )TVBCD_GetTopicData(bcd);

	WORDSET_RegisterOwnerName(ws, 0, bcd);
	if (wfw->success_flag) {
		//�ނ�グ���ꍇ
		WORDSET_RegisterItemName(ws, 1, wfw->itemno);
		WORDSET_RegisterMonsName(ws, 2, wfw->monsno,
				wfw->mons_sex, wfw->mons_region, wfw->mons_rom);
		return msg_tv_02_03_01;
	} else {
		//���s�����ꍇ
		return msg_tv_02_03_02;
	}
}
//--------------------------------------------------------------------
///	�g�s�b�N�����`�F�b�N�F���E��ނ�I
//--------------------------------------------------------------------
static BOOL TVTOPIC_Limit_Watch_Fishing(FIELDSYS_WORK * fsys, TVBCD * bcd)
{
	WATCH_FISHING_WORK * wfw = (WATCH_FISHING_WORK * )TVBCD_GetTopicData(bcd);
	if (wfw->success_flag == FALSE) {
		//���s�����ꍇ�̓|�P�����̎�ނ͊֌W�Ȃ��̂ŕ�������
		return TRUE;
	}
	return ZukanWork_GetPokeSeeFlag(SaveData_GetZukanWork(fsys->savedata),wfw->monsno);
}

//============================================================================================
//	�O�Q�|�O�S	�O���[�v�����ւ���
//	�O�Q�|�Q�O	�V�O���[�v�쐬
//============================================================================================
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void TV_Entry_CommonGroupTopic(FIELDSYS_WORK  * fsys, int topic_id)
{
	TOPIC_DATA TopicData;
	WATCH_GROUP_WORK * wgw = &TopicData.WatchGroupWork;

	RANDOM_GROUP * rg = SaveData_GetRandomGroup(fsys->savedata);

	GF_ASSERT(sizeof(TOPIC_DATA) == TOPIC_DATA_SIZE);
	MI_CpuClearFast(&TopicData, TOPIC_DATA_SIZE);

	PM_strncpy(wgw->groupname,
			RandomGroup_GetNamePtr(rg, RANDOMGROUP_MYUSE, RANDOMGROUP_NAME_GROUP),
			MONS_NAME_SIZE + EOM_SIZE);
	MakeTopic(fsys, TVTOPICTYPE_WATCH, topic_id, wgw);
}
//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N�����F�O���[�v�쐬
 */
//--------------------------------------------------------------------
void TVTOPIC_Entry_Watch_MakeGroup(FIELDSYS_WORK * fsys)
{
	TV_Entry_CommonGroupTopic(fsys, TVTOPIC_WATCH_MAKE_NEW_GROUP);
}
//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N�����F�O���[�v����ւ�
 */
//--------------------------------------------------------------------
void TVTOPIC_Entry_Watch_ChangeGroup(FIELDSYS_WORK * fsys)
{
	TV_Entry_CommonGroupTopic(fsys, TVTOPIC_WATCH_CHANGE_GROUP);
}

//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N�����F�O���[�v����ւ�
 */
//--------------------------------------------------------------------
static int TVTOPIC_Make_Watch_ChangeGroup(FIELDSYS_WORK * fsys, WORDSET * ws, TVBCD * bcd)
{
	WATCH_GROUP_WORK * wgw = (WATCH_GROUP_WORK * )TVBCD_GetTopicData(bcd);
	WORDSET_RegisterSTRCODE(ws, 1, wgw->groupname, PM_MALE, TVBCD_GetRegionCode(bcd), TRUE);
	WORDSET_RegisterOwnerName(ws, 0, bcd);
	
	return msg_tv_02_04_01;
}
//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N�����F�O���[�v�쐬
 */
//--------------------------------------------------------------------
static int TVTOPIC_Make_Watch_MakeNewGroup(FIELDSYS_WORK * fsys, WORDSET * ws, TVBCD * bcd)
{
	WATCH_GROUP_WORK * wgw = (WATCH_GROUP_WORK * )TVBCD_GetTopicData(bcd);
	WORDSET_RegisterSTRCODE(ws, 1, wgw->groupname, PM_MALE, TVBCD_GetRegionCode(bcd), TRUE);
	WORDSET_RegisterOwnerName(ws, 0, bcd);
	
	return msg_tv_02_20_01;
}

//============================================================================================
//	�O�Q�|�O�U	�B��������I		�B��������������Ƃ�
//============================================================================================
//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N�����F�B���A�C�e�������I
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	item_no		�������A�C�e���̃i���o�[
 */
//--------------------------------------------------------------------
void TVTOPIC_Entry_Watch_HideItem(FIELDSYS_WORK * fsys, u16 item_no)
{
	TOPIC_DATA TopicData;
	WATCH_HIDEITEM_WORK * whw = &TopicData.WatchHideItemWork;
	whw->item_no = item_no;
	whw->place_name_id = ZoneData_GetPlaceNameID(fsys->location->zone_id);

	MakeTopic(fsys, TVTOPICTYPE_WATCH, TVTOPIC_WATCH_GET_HIDE_ITEM, whw);
}
//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N�����F�B���A�C�e�������I
 */
//--------------------------------------------------------------------
static int TVTOPIC_Make_Watch_HideItem(FIELDSYS_WORK * fsys, WORDSET * ws, TVBCD * bcd)
{
	WATCH_HIDEITEM_WORK * whw = (WATCH_HIDEITEM_WORK *)TVBCD_GetTopicData(bcd);
	WORDSET_RegisterPlaceName(ws, 0, whw->place_name_id);
	WORDSET_RegisterOwnerName(ws, 1, bcd);
	WORDSET_RegisterItemName(ws, 2, whw->item_no);

	return msg_tv_02_06_01;
}
//============================================================================================
//	�O�Q�|�O�W	�^�}�S���z�����I
//============================================================================================
//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N�����F�^�}�S���z�����I
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	�z�����|�P�����ւ̃|�C���^
 */
//--------------------------------------------------------------------
void TVTOPIC_Entry_Watch_HatchEgg(FIELDSYS_WORK * fsys, POKEMON_PARAM * pp)
{
	TOPIC_DATA TopicData;
	WATCH_HATCHEGG_WORK * whew = &TopicData.WatchHatchEggWork;

	SetMonsParams(pp, &whew->monsno, &whew->mons_sex, &whew->mons_region, &whew->mons_rom);
	whew->place_name_id = ZoneData_GetPlaceNameID(fsys->location->zone_id);

	MakeTopic(fsys, TVTOPICTYPE_WATCH, TVTOPIC_WATCH_BORN_EGG, whew);
}
//--------------------------------------------------------------------
///	�g�s�b�N�����F�^�}�S���z�����I	�^�}�S���z�������Ƃ�
//--------------------------------------------------------------------
static int TVTOPIC_Make_Watch_HatchEgg(FIELDSYS_WORK * fsys, WORDSET * ws, TVBCD * bcd)
{
	WATCH_HATCHEGG_WORK * whew = (WATCH_HATCHEGG_WORK *)TVBCD_GetTopicData(bcd);
	WORDSET_RegisterPlaceName(ws, 1, whew->place_name_id);
	WORDSET_RegisterOwnerName(ws, 0, bcd);
	WORDSET_RegisterMonsName(ws, 2, whew->monsno,
			whew->mons_sex, whew->mons_region, whew->mons_rom);
	return msg_tv_02_08_01;
}
//--------------------------------------------------------------------
///	�g�s�b�N�����`�F�b�N�F�^�}�S���z�����I	�^�}�S���z�������Ƃ�
//--------------------------------------------------------------------
static BOOL TVTOPIC_Limit_Watch_HatchEgg(FIELDSYS_WORK * fsys, TVBCD * bcd)
{
	WATCH_HATCHEGG_WORK * whew = (WATCH_HATCHEGG_WORK *)TVBCD_GetTopicData(bcd);
	return ZukanWork_GetPokeSeeFlag(SaveData_GetZukanWork(fsys->savedata),whew->monsno);
}
//============================================================================================
//	�O�Q�|�P�O	�������f
//============================================================================================
//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N�����F�������f	�j�b�N�l�[����ύX�����Ƃ�
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	pp		���O��ς����|�P�����ւ̃|�C���^
 */
//--------------------------------------------------------------------
void TVTOPIC_Entry_Watch_ChangeName(FIELDSYS_WORK * fsys, POKEMON_PARAM * pp)
{
	TOPIC_DATA TopicData;
	WATCH_MONSNAMECHG_WORK * wmcw = &TopicData.WatchMonsNameChgWork;

	SetMonsParams(pp, &wmcw->monsno, &wmcw->mons_sex, &wmcw->mons_region, &wmcw->mons_rom);
	GetNickNameSTRCODE(HEAPID_FIELD, wmcw->newname, pp);

	MakeTopic(fsys, TVTOPICTYPE_WATCH, TVTOPIC_WATCH_CHANGE_NICKNAME, wmcw);
}
//--------------------------------------------------------------------
///	�g�s�b�N�����F�������f	�j�b�N�l�[����ύX�����Ƃ�
//--------------------------------------------------------------------
static int TVTOPIC_Make_Watch_ChangeName(FIELDSYS_WORK * fsys, WORDSET * ws, TVBCD * bcd)
{
	WATCH_MONSNAMECHG_WORK * wmcw = (WATCH_MONSNAMECHG_WORK *)TVBCD_GetTopicData(bcd);
	WORDSET_RegisterOwnerName(ws, 0, bcd);
	WORDSET_RegisterMonsName(ws, 1, wmcw->monsno,
			wmcw->mons_sex, wmcw->mons_region, wmcw->mons_rom);
	WORDSET_RegisterSTRCODE(ws, 2, wmcw->newname, wmcw->mons_sex, wmcw->mons_region, TRUE);

	return msg_tv_02_10_01 + gf_p_rand(5);
}

//--------------------------------------------------------------------
///	�g�s�b�N�����`�F�b�N�F�������f	�j�b�N�l�[����ύX�����Ƃ�
//--------------------------------------------------------------------
static BOOL TVTOPIC_Limit_Watch_ChangeName(FIELDSYS_WORK * fsys, TVBCD * bcd)
{
	ZUKAN_WORK * zw = SaveData_GetZukanWork(fsys->savedata);
	WATCH_MONSNAMECHG_WORK * wmcw = (WATCH_MONSNAMECHG_WORK *)TVBCD_GetTopicData(bcd);
	return ZukanWork_GetPokeSeeFlag(zw, wmcw->monsno);
}

//============================================================================================
//	�O�Q�|�P�R�@���Ό@��
//============================================================================================
//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N�����F���Ό@��	���Ό@�����������
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	fossil_type		���΂̃A�C�e���i���o�[
 * @param	fossil_num		��ꂽ���΂̐�
 */
//--------------------------------------------------------------------
void TVTOPIC_Entry_Watch_DigFossil(FIELDSYS_WORK  *fsys, int fossil_type, int fossil_num)
{
	TOPIC_DATA TopicData;
	WATCH_DIG_FOSSIL_WORK * wdfw = &TopicData.WatchDigFossilWork;
	wdfw->fossil_type = fossil_type;
	wdfw->fossil_num = fossil_num;

	MakeTopic(fsys, TVTOPICTYPE_WATCH, TVTOPIC_WATCH_DIG_FOSSIL, wdfw);
}
//--------------------------------------------------------------------
///	�g�s�b�N�����F���Ό@��	���Ό@�����������
//--------------------------------------------------------------------
static int TVTOPIC_Make_Watch_DigFossil(FIELDSYS_WORK * fsys, WORDSET * ws, TVBCD * bcd)
{
	WATCH_DIG_FOSSIL_WORK * wdfw = (WATCH_DIG_FOSSIL_WORK *)TVBCD_GetTopicData(bcd);
	WORDSET_RegisterOwnerName(ws, 0, bcd);
	WORDSET_RegisterUGItemName(ws, 1, wdfw->fossil_type);
	WORDSET_RegisterNumber(ws, 2, wdfw->fossil_num, 3,
			NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT);
	return msg_tv_02_13_01;
}
//============================================================================================
//	�O�Q�|�P�T	�T�t�@���Q�[��
//============================================================================================
//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N�����F�T�t�@���Q�[��	�T�t�@���Q�[�����I���������Ƃ�
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------------
void TVTOPIC_Entry_Watch_Safari(FIELDSYS_WORK * fsys)
{
	TOPIC_DATA TopicData;
	WATCH_SAFARI_WORK * wsw = &TopicData.WatchSafariWork;
	TV_WORK * tvwk = SaveData_GetTvWork(fsys->savedata);
	TOPICTEMP_SAFARI * psaf = TVWORK_GetSafariTemp(tvwk);
	if (psaf->capture_count == 0) {
		//��C���߂܂��Ă��Ȃ��ꍇ�A�g�s�b�N��������Ȃ�
		return;
	}
	wsw->monsno = psaf->monsno;
	wsw->mons_sex = psaf->mons_sex;
	wsw->mons_region = psaf->mons_region;
	wsw->mons_rom = psaf->mons_rom;
	wsw->get_count = psaf->capture_count;

	MakeTopic(fsys, TVTOPICTYPE_WATCH, TVTOPIC_WATCH_SAFARI, wsw);
}
//--------------------------------------------------------------------
///	�g�s�b�N�����F�T�t�@���Q�[��	�T�t�@���Q�[�����I���������Ƃ�
//--------------------------------------------------------------------
static int TVTOPIC_Make_Watch_Safari(FIELDSYS_WORK * fsys, WORDSET * ws, TVBCD * bcd)
{
	WATCH_SAFARI_WORK * wsw = (WATCH_SAFARI_WORK *)TVBCD_GetTopicData(bcd);
	WORDSET_RegisterOwnerName(ws, 0, bcd);
	WORDSET_RegisterMonsName(ws, 1, wsw->monsno, wsw->mons_sex, wsw->mons_region, wsw->mons_rom);
	WORDSET_RegisterNumber(ws, 2, wsw->get_count, 2, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT);

	return msg_tv_02_15_01;
}
//--------------------------------------------------------------------
///	�g�s�b�N�����`�F�b�N�F�T�t�@���Q�[��	�T�t�@���Q�[�����I���������Ƃ�
//--------------------------------------------------------------------
static BOOL TVTOPIC_Limit_Watch_Safari(FIELDSYS_WORK * fsys, TVBCD * bcd)
{
	ZUKAN_WORK * zw = SaveData_GetZukanWork(fsys->savedata);
	WATCH_SAFARI_WORK * wsw = (WATCH_SAFARI_WORK *)TVBCD_GetTopicData(bcd);
	return ZukanWork_GetPokeSeeFlag(zw, wsw->monsno);
}

//============================================================================================
//	�O�Q�|�P�V	�ǖ�͌��ɋꂵ�I	�|�P�����Ɋ�������������Ƃ�
//============================================================================================
//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N�����F�ǖ�͌��ɋꂵ�I	�|�P�����Ɋ�������������Ƃ�
 * @param	tvwk		�e���r�Z�[�u�f�[�^�ւ̃|�C���^
 * @param	pp			����������|�P�����ւ̃|�C���^
 * @param	itemno		��̃A�C�e���i���o�[
 */
//--------------------------------------------------------------------
void TVTOPIC_Entry_Watch_UseKanpo(TV_WORK * tvwk, POKEMON_PARAM * pp, u16 itemno)
{
	TOPIC_DATA TopicData;
	WATCH_KANPO_WORK * wkw = &TopicData.WatchKanpoWork;

	SetMonsParams(pp, &wkw->monsno, &wkw->mons_sex, &wkw->mons_region, &wkw->mons_rom);
	wkw->itemno = itemno;

	TVWORK_MakeTopic(tvwk, TVTOPICTYPE_WATCH, TVTOPIC_WATCH_KANPOU, (const u8 *)wkw);
}
//--------------------------------------------------------------------
///	�g�s�b�N�����F�ǖ�͌��ɋꂵ�I	�|�P�����Ɋ�������������Ƃ�
//--------------------------------------------------------------------
static int TVTOPIC_Make_Watch_UseKanpo(FIELDSYS_WORK * fsys, WORDSET * ws, TVBCD * bcd)
{
	WATCH_KANPO_WORK * wkw = (WATCH_KANPO_WORK *)TVBCD_GetTopicData(bcd);
	WORDSET_RegisterOwnerName(ws, 0, bcd);
	WORDSET_RegisterMonsName(ws, 1, wkw->monsno, wkw->mons_sex, wkw->mons_region, wkw->mons_rom);
	WORDSET_RegisterItemName(ws, 2, wkw->itemno);

	return msg_tv_02_17_01;
}
//--------------------------------------------------------------------
///	�g�s�b�N�����`�F�b�N�F�ǖ�͌��ɋꂵ�I	�|�P�����Ɋ�������������Ƃ�
//--------------------------------------------------------------------
static BOOL TVTOPIC_Limit_Watch_UseKanpo(FIELDSYS_WORK * fsys, TVBCD * bcd)
{
	WATCH_KANPO_WORK * wkw = (WATCH_KANPO_WORK *)TVBCD_GetTopicData(bcd);
	return ZukanWork_GetPokeSeeFlag(SaveData_GetZukanWork(fsys->savedata),wkw->monsno);
}

//============================================================================================
//	�O�Q�|�P�W	�Ď��^�F���̂ݖL��
//	�O�Q�|�P�X	�Ď��^�F���̂ݕs��
//	�O�R�|�O�U	�M�l�X�^�F���̂ݖ��l
//============================================================================================
//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N�����F���݂̂��Ƃ����Ƃ�
 * @param	fsys			�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	nuts_item_no	�Ƃ������݂̂̃A�C�e���i���o�[
 * @param	hp				�Ƃ����Ƃ���HP�̒l
 * @param	nuts_count		�Ƃ������݂̂̐�
 */
//--------------------------------------------------------------------
void TVTOPIC_Entry_TakeNuts(FIELDSYS_WORK  *fsys, u16 nuts_item_no, u8 hp, u16 nuts_count)
{
	TOPIC_DATA TopicData;
	COMMON_TAKE_NUTS_WORK * tnw = &TopicData.TakeNutsWork;
	tnw->nuts_item_no = nuts_item_no;
	tnw->hp = hp;
	tnw->nuts_count = nuts_count;
	if (hp == 5) {
		//HP�����^���̂Ƃ��A�M�l�X�^�g�s�b�N����
		MakeTopic(fsys, TVTOPICTYPE_RECORD, TVTOPIC_RECORD_NUTS_MASTER, tnw);
	} else if (hp == 4) {
		//HP���S�̂Ƃ��A�Ď��^�g�s�b�N����
		MakeTopic(fsys, TVTOPICTYPE_WATCH, TVTOPIC_WATCH_NUTS_HARVEST, tnw);
	} else if (hp == 0) {
		//HP���O�̂Ƃ��A�Ď��^�g�s�b�N����
		MakeTopic(fsys, TVTOPICTYPE_WATCH, TVTOPIC_WATCH_NUTS_POOR, tnw);
	}
	/* �g�s�b�N����������Ȃ��ꍇ������ */
}
//--------------------------------------------------------------------
///	�g�s�b�N�����F�L��I�؂̎�������������n�����Ƃ��i���n���A�؂�HP���W�A�X�������Ƃ��j
//--------------------------------------------------------------------
static int TVTOPIC_Make_Watch_NutsHarvest(FIELDSYS_WORK * fsys, WORDSET * ws, TVBCD * bcd)
{
	COMMON_TAKE_NUTS_WORK * tnw = TVBCD_GetTopicData(bcd);
	WORDSET_RegisterOwnerName(ws, 0, bcd);
	WORDSET_RegisterItemName(ws, 1, tnw->nuts_item_no);
	WORDSET_RegisterNumber(ws, 2, tnw->nuts_count, 2, NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT);
	return msg_tv_02_18_01;
}
//--------------------------------------------------------------------
///	�g�s�b�N�����F�s��E�E�E�؂̎����P�������n�ł��Ȃ������Ƃ�
//--------------------------------------------------------------------
static int TVTOPIC_Make_Watch_NutsPoor(FIELDSYS_WORK * fsys, WORDSET * ws, TVBCD * bcd)
{
	COMMON_TAKE_NUTS_WORK * tnw = TVBCD_GetTopicData(bcd);
	WORDSET_RegisterOwnerName(ws, 0, bcd);
	WORDSET_RegisterItemName(ws, 1, tnw->nuts_item_no);
	return msg_tv_02_19_01;
}
//--------------------------------------------------------------------
///	�g�s�b�N�����F�M�l�X�^�F�؂̎���Ă̖��l	���n���A�؂�HP��10�������Ƃ�
//--------------------------------------------------------------------
static int TVTOPIC_Make_Record_NutsMaster(FIELDSYS_WORK * fsys, WORDSET * ws, TVBCD * bcd)
{
	STRBUF * strbuf;
	COMMON_TAKE_NUTS_WORK * tnw = TVBCD_GetTopicData(bcd);
	WORDSET_RegisterOwnerName(ws, 0, bcd);
	strbuf = NutsNameGetAlloc(tnw->nuts_item_no - NUTS_START_ITEMNUM, HEAPID_FIELD);
	WORDSET_RegisterWord(ws, 1, strbuf, PM_MALE, TRUE, PM_LANG);
	STRBUF_Delete(strbuf);
	return msg_tv_03_06_01;
}

//============================================================================================
//	�O�Q�|�Q�P	�J�X�^���J�v�Z��
//============================================================================================
//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N�����F�J�X�^���{�[���쐬�I	�J�X�^���J�v�Z�����|�P�����ɃZ�b�g�����Ƃ�
 * @param	tvwk		�e���r�Z�[�u�f�[�^�ւ̃|�C���^
 * @param	pp			�Z�b�g�����|�P�����ւ̃|�C���^
 * @param	seal_no		�V�[���̎�ށi�ǂꂩ��A�K���ł悢�j
 */
//--------------------------------------------------------------------
void TVTOPIC_Entry_Watch_CustomBall(TV_WORK * tvwk, POKEMON_PARAM * pp, u8 seal_no)
{
	TOPIC_DATA TopicData;
	WATCH_CUSTOMCAPSULE_WORK * wccw = &TopicData.WatchCustomCapsuleWork;
	wccw->seal_no = seal_no;
	wccw->rand = gf_mtRand() % 3;
	SetMonsParams(pp, &wccw->monsno, &wccw->mons_sex, &wccw->mons_region, &wccw->mons_rom);
	//MakeTopic(fsys, TVTOPICTYPE_WATCH, TVTOPIC_WATCH_SET_CUSTOMBALL, wccw);
	TVWORK_MakeTopic(tvwk, TVTOPICTYPE_WATCH, TVTOPIC_WATCH_SET_CUSTOMBALL, (const u8 *)wccw);
}
//--------------------------------------------------------------------
///	�g�s�b�N�����F�J�X�^���{�[���쐬�I	�J�X�^���J�v�Z�����|�P�����ɃZ�b�g�����Ƃ�
//--------------------------------------------------------------------
static int TVTOPIC_Make_Watch_CustomBall(FIELDSYS_WORK * fsys, WORDSET * ws, TVBCD * bcd)
{
	WATCH_CUSTOMCAPSULE_WORK * wccw = (WATCH_CUSTOMCAPSULE_WORK *)TVBCD_GetTopicData(bcd);
	WORDSET_RegisterOwnerName(ws, 0, bcd);
	WORDSET_RegisterSealName(ws, 1, wccw->seal_no);
	WORDSET_RegisterMonsName(ws, 2, wccw->monsno,
			wccw->mons_sex, wccw->mons_region, wccw->mons_rom);
	return msg_tv_02_21_01 + gf_p_rand(3);
}
//--------------------------------------------------------------------
///	�g�s�b�N�����`�F�b�N�J�X�^���{�[���쐬�I	�J�X�^���J�v�Z�����|�P�����ɃZ�b�g�����Ƃ��F
//--------------------------------------------------------------------
static BOOL TVTOPIC_Limit_Watch_CustomBall(FIELDSYS_WORK * fsys, TVBCD * bcd)
{
	WATCH_CUSTOMCAPSULE_WORK * wccw = (WATCH_CUSTOMCAPSULE_WORK *)TVBCD_GetTopicData(bcd);
	return ZukanWork_GetPokeSeeFlag(SaveData_GetZukanWork(fsys->savedata),wccw->monsno);
}
//============================================================================================
//	�O�Q�|�Q�Q	�����Ƃ����I
//	�O�Q�|�Q�R	�������ꂽ�I
//============================================================================================
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Entry_Watch_FlagCommon(WATCH_UG_FLAG_WORK * wufw, const MYSTATUS * rival)
{
	wufw->size = MyStatus_GetWorkSize();
	MyStatus_Copy(rival, (MYSTATUS *)wufw->data);
}

//--------------------------------------------------------------------
//--------------------------------------------------------------------
static void Make_Watch_FlagCommon(FIELDSYS_WORK * fsys, WORDSET * ws, TVBCD * bcd)
{
	WATCH_UG_FLAG_WORK * wufw = (WATCH_UG_FLAG_WORK *)TVBCD_GetTopicData(bcd);
	MYSTATUS * rival = (MYSTATUS *)&wufw->data;

	GF_ASSERT(MyStatus_GetWorkSize() == wufw->size);
	WORDSET_RegisterOwnerName(ws, 0, bcd);
	WORDSET_RegisterPlayerName(ws, 1, rival);
}
//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N�����F����������I		�l�̊��������A�����I
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	rival		�����MYSTATUS�ւ̃|�C���^
 */
//--------------------------------------------------------------------
void TVTOPIC_Entry_Watch_GetFlag(FIELDSYS_WORK * fsys, const MYSTATUS * rival)
{
	TOPIC_DATA TopicData;
	WATCH_UG_FLAG_WORK * wufw = &TopicData.WatchUgFlagWork;

	Entry_Watch_FlagCommon(wufw, rival);
	MakeTopic(fsys, TVTOPICTYPE_WATCH, TVTOPIC_WATCH_GET_FLAG, wufw);
}

//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N�����F�������ꂽ�I		�����̊��������A��ꂽ�I
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	rival		�����MYSTATUS�ւ̃|�C���^
 */
//--------------------------------------------------------------------
void TVTOPIC_Entry_Watch_LoseFlag(FIELDSYS_WORK * fsys, const MYSTATUS * rival)
{
	TOPIC_DATA TopicData;
	WATCH_UG_FLAG_WORK * wufw = &TopicData.WatchUgFlagWork;

	Entry_Watch_FlagCommon(wufw, rival);
	MakeTopic(fsys, TVTOPICTYPE_WATCH, TVTOPIC_WATCH_LOSE_FLAG, wufw);
}

//--------------------------------------------------------------------
///�g�s�b�N�����F����������I		�l�̊��������A�����I
//--------------------------------------------------------------------
static int TVTOPIC_Make_Watch_GetFlag(FIELDSYS_WORK * fsys, WORDSET * ws, TVBCD * bcd)
{
	Make_Watch_FlagCommon(fsys, ws, bcd);
	return msg_tv_02_22_01;
}

//--------------------------------------------------------------------
///�g�s�b�N�����F�������ꂽ�I		�����̊��������A��ꂽ�I
//--------------------------------------------------------------------
static int TVTOPIC_Make_Watch_LoseFlag(FIELDSYS_WORK * fsys, WORDSET * ws, TVBCD * bcd)
{
	Make_Watch_FlagCommon(fsys, ws, bcd);
	return msg_tv_02_23_01;
}

//--------------------------------------------------------------------
///	�g�s�b�N�����`�F�b�N�F�������ꂽ�I		�����̊��������A��ꂽ�I
///	�g�s�b�N�����`�F�b�N�F����������I		�l�̊��������A�����I
//--------------------------------------------------------------------
static BOOL TVTOPIC_Limit_Watch_Tankou(FIELDSYS_WORK * fsys, TVBCD * bcd)
{
	return MyItem_CheckItem(SaveData_GetMyItem(fsys->savedata), ITEM_TANKENSETTO, 1, HEAPID_EVENT);
}



//============================================================================================
//
//
//			�M�l�X�^�g�s�b�N
//
//
//============================================================================================

//============================================================================================
//	�O�R�|�O�P�F�o�g���^���[�A���L�^�X�V	�o�g���^���[�A���L�^���X�V�����Ƃ�
//============================================================================================
//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N�����F�o�g���^���[�A��
 * @param	fsys		�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	renshou		�A����
 * @param	pp			�擪�̃|�P�����ւ̃|�C���^
 * @param	IsSingleFlag	�V���O���킩�ǂ���
 */
//--------------------------------------------------------------------
void TVTOPIC_Entry_Record_BTower(FIELDSYS_WORK * fsys, 
		u32 renshou, POKEMON_PARAM * pp, BOOL IsSingleFlag)
{
	TOPIC_DATA TopicData;
	RECORD_BTOWER_WORK * rbtw = &TopicData.RecordBTowerWork;
	SetMonsParams(pp, &rbtw->monsno, &rbtw->mons_sex, &rbtw->mons_region, &rbtw->mons_rom);
	rbtw->renshou = renshou;
	rbtw->IsSingleFlag = IsSingleFlag;
	MakeTopic(fsys, TVTOPICTYPE_RECORD, TVTOPIC_RECORD_BTOWER, rbtw);
}

//--------------------------------------------------------------------
///	�g�s�b�N�����F�o�g���^���[�A��
//--------------------------------------------------------------------
static int TVTOPIC_Make_Record_BTower(FIELDSYS_WORK * fsys, WORDSET * ws, TVBCD * bcd)
{
	RECORD_BTOWER_WORK * rbtw = (RECORD_BTOWER_WORK *)TVBCD_GetTopicData(bcd);

	WORDSET_RegisterOwnerName(ws, 0, bcd);
	WORDSET_RegisterMonsName(ws, 1, rbtw->monsno,
			rbtw->mons_sex, rbtw->mons_region, rbtw->mons_rom);
	WORDSET_RegisterNumber(ws, 2, rbtw->renshou, 4,
			NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT);
	if (rbtw->IsSingleFlag) {
		return msg_tv_03_01_01;
	} else {
		return msg_tv_03_01_02;
	}
}
//--------------------------------------------------------------------
///	�g�s�b�N�����`�F�b�N�F�o�g���^���[�A��
//--------------------------------------------------------------------
static BOOL TVTOPIC_Limit_Record_BTower(FIELDSYS_WORK * fsys, TVBCD * bcd)
{
	RECORD_BTOWER_WORK * rbtw = (RECORD_BTOWER_WORK *)TVBCD_GetTopicData(bcd);
	if (ZukanWork_GetPokeSeeFlag(SaveData_GetZukanWork(fsys->savedata), rbtw->monsno) == FALSE) {
		return FALSE;
	}
	return SysFlag_ArriveGet(SaveData_GetEventWork(fsys->savedata), FLAG_ARRIVE_C11);
}
//============================================================================================
//	�O�R�|�O�R�F�傫������L�^�X�V	�傫������ŋL�^���X�V�����Ƃ�
//============================================================================================
//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N�����F�傫������L�^�X�V	�傫������ŋL�^���X�V�����Ƃ�
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	size		�L�^
 * @param	pp			�X�V�����|�P�����ւ̃|�C���^
 */
//--------------------------------------------------------------------
void TVTOPIC_Entry_Record_Ookisa(FIELDSYS_WORK * fsys, u32 size, POKEMON_PARAM * pp)
{
	TOPIC_DATA TopicData;
	RECORD_OOKISA_WORK * row = &TopicData.RecordOokisaWork;
	SetMonsParams(pp, &row->monsno, &row->mons_sex, &row->mons_region, &row->mons_rom);
	row->size = size;
	MakeTopic(fsys, TVTOPICTYPE_RECORD, TVTOPIC_RECORD_OOKISA, row);
}

//--------------------------------------------------------------------
///	�g�s�b�N�����F�傫������L�^�X�V	�傫������ŋL�^���X�V�����Ƃ�
//--------------------------------------------------------------------
static int TVTOPIC_Make_Record_Ookisa(FIELDSYS_WORK * fsys, WORDSET * ws, TVBCD * bcd)
{
	RECORD_OOKISA_WORK * row = (RECORD_OOKISA_WORK *)TVBCD_GetTopicData(bcd);

	WORDSET_RegisterOwnerName(ws, 0, bcd);
	WORDSET_RegisterMonsName(ws, 1, row->monsno,
			row->mons_sex, row->mons_region, row->mons_rom);
	WORDSET_RegisterNumber(ws, 2, row->size / 10, 3,
			NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT);
	WORDSET_RegisterNumber(ws, 3, row->size % 10, 1,
			NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT);

	return msg_tv_03_03_01;
}
//--------------------------------------------------------------------
///	�g�s�b�N�����`�F�b�N�F�o�g���^���[�A��
//--------------------------------------------------------------------
static BOOL TVTOPIC_Limit_Record_Ookisa(FIELDSYS_WORK * fsys, TVBCD * bcd)
{
	RECORD_OOKISA_WORK * row = (RECORD_OOKISA_WORK *)TVBCD_GetTopicData(bcd);
	return ZukanWork_GetPokeSeeFlag(SaveData_GetZukanWork(fsys->savedata), row->monsno);
}

//============================================================================================
//	�O�R�|�O�S�F�X���b�g�B�l	�X���b�g�ň�薇���ȏ���҂����Ƃ�
//============================================================================================
//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N�����F�X���b�g�B�l	�X���b�g�ň�薇���ȏ���҂����Ƃ�
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	start_coin		�J�n���̃R�C������
 * @param	end_coin		�I�����̃R�C������
 * @param	playtime		�v���C���ԁi���P�ʁj
 */
//--------------------------------------------------------------------
void TVTOPIC_Entry_Record_Slot(FIELDSYS_WORK * fsys, u32 start_coin, u32 end_coin, u32 playtime)
{
	TOPIC_DATA TopicData;
	RECORD_SLOT_WORK * rsw = &TopicData.RecordSlotWork;
	if (end_coin < 1000 + start_coin) return;
	rsw->start_coin = start_coin;
	rsw->end_coin = end_coin;
	rsw->playtime = playtime;
	MakeTopic(fsys, TVTOPICTYPE_RECORD, TVTOPIC_RECORD_SLOT, rsw);
}
//--------------------------------------------------------------------
///	�g�s�b�N�����F�X���b�g�L�^
//--------------------------------------------------------------------
static int TVTOPIC_Make_Record_Slot(FIELDSYS_WORK * fsys, WORDSET * ws, TVBCD * bcd)
{
	RECORD_SLOT_WORK * rsw = TVBCD_GetTopicData(bcd);

	WORDSET_RegisterOwnerName(ws, 0, bcd);
	WORDSET_RegisterNumber(ws, 1, rsw->playtime, 10,
			NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT);
	WORDSET_RegisterNumber(ws, 2, rsw->start_coin, 6,
			NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT);
	WORDSET_RegisterNumber(ws, 3, rsw->end_coin, 6,
			NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT);

	return msg_tv_03_04_01;
}
//============================================================================================
//	�O�R�|�O�W	���i�������l	�n���ɓ������Ƃ��A��������̃��i������������쐬
//============================================================================================
//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N�����F���i�������l	�n���ɓ������Ƃ��A��������̃��i������������쐬
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	trap_no			�ŏ��ɉ����������i�̃i���o�[
 * @param	remove_count	���i������������
 *
 * �n���ɓ����Ă���o��܂ł̊Ԃ̉񐔂ł��B��x�o���烊�Z�b�g����܂��B
 */
//--------------------------------------------------------------------
void TVTOPIC_Entry_Record_RemoveTrap(FIELDSYS_WORK * fsys, u16 trap_no, u16 remove_count)
{
	TOPIC_DATA TopicData;
	RECORD_REMOVE_TRAP_WORK * rrtw = &TopicData.RecordRemoveTrapWork;
	rrtw->trap_no = trap_no;
	rrtw->remove_count = remove_count;
	MakeTopic(fsys, TVTOPICTYPE_RECORD, TVTOPIC_RECORD_TRAP_REMOVER, rrtw);
}
//--------------------------------------------------------------------
///	�g�s�b�N�����F���i�������l	�n���ɓ������Ƃ��A��������̃��i������������쐬
//--------------------------------------------------------------------
static int TVTOPIC_Make_Record_RemoveTrap(FIELDSYS_WORK * fsys, WORDSET * ws, TVBCD * bcd)
{
	RECORD_REMOVE_TRAP_WORK * rrtw = TVBCD_GetTopicData(bcd);
	WORDSET_RegisterOwnerName(ws, 0, bcd);
	WORDSET_RegisterUGTrapName(ws, 1, rrtw->trap_no);
	WORDSET_RegisterNumber(ws, 2, rrtw->remove_count, 3,
			NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT);
	return msg_tv_03_08_01;
}
//============================================================================================
//	�O�R�|�O�X	�n�^�g�����l
//============================================================================================
//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N�����F�n�^�g�����l
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	flag_count		�����������
 *
 * �n���ɓ����Ă���o��܂ł̊Ԃ̉񐔂ł��B��x�o���烊�Z�b�g����܂��B
 */
//--------------------------------------------------------------------
void TVTOPIC_Entry_Record_GetFlag(FIELDSYS_WORK * fsys, u16 flag_count)
{
	TOPIC_DATA TopicData;
	RECORD_GET_FLAG_WORK * rgfw = &TopicData.RecordGetFlagWork;
	rgfw->flag_count = flag_count;
	if (flag_count > 1) {
		MakeTopic(fsys, TVTOPICTYPE_RECORD, TVTOPIC_RECORD_FLAG_GET, rgfw);
	}
}
//--------------------------------------------------------------------
///	�g�s�b�N�����F�n�^�g�����l
//--------------------------------------------------------------------
static int TVTOPIC_Make_Record_GetFlag(FIELDSYS_WORK * fsys, WORDSET * ws, TVBCD * bcd)
{
	RECORD_GET_FLAG_WORK * rgfw = TVBCD_GetTopicData(bcd);
	WORDSET_RegisterOwnerName(ws, 0, bcd);
	WORDSET_RegisterNumber(ws, 1, rgfw->flag_count, 3,
			NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT);
	return msg_tv_03_09_01;
}
//--------------------------------------------------------------------
///	�g�s�b�N�����`�F�b�N�F�n�^�g�����l
//--------------------------------------------------------------------
static BOOL TVTOPIC_Limit_Record_Tankou(FIELDSYS_WORK * fsys, TVBCD * bcd)
{
	return MyItem_CheckItem(SaveData_GetMyItem(fsys->savedata), ITEM_TANKENSETTO, 1, HEAPID_EVENT);
}




//============================================================================================
//
//
//				����^�g�s�b�N
//
//
//============================================================================================
//============================================================================================
//	�O�P�|�O�Q	����I�o�g���^���[	1	�o�g���^���[	����I����
//============================================================================================
//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N�����F�o�g���^���[�C���^�r���[
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	count		�A����
 * @param	word		�ȈՉ�b�P��ID
 */
//--------------------------------------------------------------------
void TVTOPIC_Entry_QandA_BTower(FIELDSYS_WORK * fsys, PMS_WORD word)
{
	TOPIC_DATA TopicData;
	QANDA_BTOWER_WORK * qbtw = &TopicData.QandABtowerWork;
	TOPICTEMP_BTOWER * pbt = TVWORK_GetBTowerTemp(SaveData_GetTvWork(fsys->savedata));
	qbtw->btower = *pbt;
	pbt->exist_flag = FALSE;
	qbtw->word = word;
	MakeTopic(fsys, TVTOPICTYPE_INTERVIEW, TVTOPIC_INTERVIEW_BTOWER, qbtw);
}

//--------------------------------------------------------------------
///	�g�s�b�N�����F�o�g���^���[�C���^�r���[
//--------------------------------------------------------------------
static int TVTOPIC_Make_QandA_BTower(FIELDSYS_WORK * fsys, WORDSET * ws, TVBCD * bcd)
{
	QANDA_BTOWER_WORK* qbtw = TVBCD_GetTopicData(bcd);
	WORDSET_RegisterNumber(ws, 0, qbtw->btower.win_count, 4,
			NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT);
	WORDSET_RegisterOwnerName(ws, 1, bcd);		//�g���[�i�[��
	WORDSET_RegisterPMSWord(ws, 2, qbtw->word);
	if (qbtw->btower.continue_flag == TRUE) {
		return msg_tv_01_02_01;
	} else {
		return msg_tv_01_02_02;
	}
}
//--------------------------------------------------------------------
///	�g�s�b�N�����`�F�b�N�F�o�g���^���[�A��
//--------------------------------------------------------------------
static BOOL TVTOPIC_Limit_QandA_BTower(FIELDSYS_WORK * fsys, TVBCD * bcd)
{
	return SysFlag_ArriveGet(SaveData_GetEventWork(fsys->savedata), FLAG_ARRIVE_C11);
}
//============================================================================================
//	�O�P�|�O�S	���Ȃ��̃|�P����	1	�|�P������D���N���u	
//============================================================================================
//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N�����F���Ȃ��̃|�P�����C���^�r���[
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	word		�ȈՉ�b�P��ID
 */
//--------------------------------------------------------------------
void TVTOPIC_Entry_QandA_Pokemon(FIELDSYS_WORK * fsys, PMS_WORD word)
{
	TOPIC_DATA TopicData;
	QANDA_POKEMON_WORK * qpw = &TopicData.QandAPokemonWork;
	POKEMON_PARAM * pp;
	
	//�擪�̃|�P����
	pp = EvPoke_GetPokemonTop(SaveData_GetTemotiPokemon(fsys->savedata));
	SetMonsParams(pp, &qpw->monsno, &qpw->mons_sex, &qpw->mons_region, &qpw->mons_rom);
	StoreNickName(HEAPID_EVENT, pp, &qpw->nickname_flag, qpw->nickname);
	qpw->word = word;
	MakeTopic(fsys, TVTOPICTYPE_INTERVIEW, TVTOPIC_INTERVIEW_POKEMON, qpw);
}

//--------------------------------------------------------------------
///	�g�s�b�N�����F���Ȃ��̃|�P�����C���^�r���[
//--------------------------------------------------------------------
static int TVTOPIC_Make_QandA_Pokemon(FIELDSYS_WORK * fsys, WORDSET * ws, TVBCD * bcd)
{
	QANDA_POKEMON_WORK * qpw = TVBCD_GetTopicData(bcd);

	if (qpw->nickname_flag) {
		//�j�b�N�l�[���������ꍇ
		WORDSET_RegisterOwnerName(ws, 0, bcd);		//�g���[�i�[��
		WORDSET_RegisterMonsName(ws, 1, qpw->monsno,
				qpw->mons_sex, qpw->mons_region, qpw->mons_rom);
		WORDSET_RegisterSTRCODE(ws, 2, qpw->nickname,
				qpw->mons_sex, qpw->mons_region, TRUE);
		WORDSET_RegisterPMSWord(ws, 3, qpw->word);
		return msg_tv_01_04_01;
	} else {
		//�j�b�N�l�[�������Ȃ������ꍇ
		WORDSET_RegisterOwnerName(ws, 0, bcd);		//�g���[�i�[��
		WORDSET_RegisterMonsName(ws, 1, qpw->monsno,
				qpw->mons_sex, qpw->mons_region, qpw->mons_rom);
	//	WORDSET_RegisterSTRCODE(ws, 2, qpw->nickname,
	//			qpw->mons_sex, qpw->mons_region, TRUE);
		WORDSET_RegisterPMSWord(ws, 3, qpw->word);
		return msg_tv_01_04_02;
	}
}
//--------------------------------------------------------------------
///	�g�s�b�N�����`�F�b�N�F�o�g���^���[�A��
//--------------------------------------------------------------------
static BOOL TVTOPIC_Limit_QandA_Pokemon(FIELDSYS_WORK * fsys, TVBCD * bcd)
{
	QANDA_POKEMON_WORK * qpw = TVBCD_GetTopicData(bcd);
	return ZukanWork_GetPokeSeeFlag(SaveData_GetZukanWork(fsys->savedata), qpw->monsno);
}
//============================================================================================
//	�O�P�|�O�U	���C�ɓ���̃|�P�b�`	2	�J���p�j�[	
//============================================================================================
//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N�����F���C�ɓ���̃|�P�b�`
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	word		�ȈՉ�b�P��ID
 */
//--------------------------------------------------------------------
void TVTOPIC_Entry_QandA_Poketch(FIELDSYS_WORK * fsys, PMS_WORD word)
{
	TOPIC_DATA TopicData;
	QANDA_POKETCH_WORK * qptw = &TopicData.QandAPoketchWork;
	qptw->poketch_id = Poketch_GetRunningApplication(fsys->fldmap->poketch);
	qptw->word = word;
	MakeTopic(fsys, TVTOPICTYPE_INTERVIEW, TVTOPIC_INTERVIEW_POKETCH, qptw);
}
//--------------------------------------------------------------------
///	�g�s�b�N�����F�|�P�b�`�C���^�r���[
//--------------------------------------------------------------------
static int TVTOPIC_Make_QandA_Poketch(FIELDSYS_WORK * fsys, WORDSET * ws, TVBCD * bcd)
{
	QANDA_POKETCH_WORK * qptw = TVBCD_GetTopicData(bcd);
	WORDSET_RegisterOwnerName(ws, 0, bcd);		//�g���[�i�[��
	WORDSET_RegisterPoketchAppName(ws, 1, qptw->poketch_id);
	WORDSET_RegisterPMSWord(ws, 2, qptw->word);
	return msg_tv_01_06_01;
}
//============================================================================================
//	�O�P�|�O�V	����I�R���e�X�g		�R���e�X�g���	�R���e�X�g�I����
//============================================================================================
//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N�����F����I�R���e�X�g
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	word		�ȈՉ�b�P��ID
 */
//--------------------------------------------------------------------
void TVTOPIC_Entry_QandA_Contest(FIELDSYS_WORK * fsys, PMS_WORD word)
{
	TOPIC_DATA TopicData;
	QANDA_CONTEST_WORK * qctw = &TopicData.QandAContestWork;
	TOPICTEMP_CONTEST * pcnt = TVWORK_GetContestTemp(SaveData_GetTvWork(fsys->savedata));
	qctw->contest = *pcnt;
	pcnt->exist_flag = FALSE;
	qctw->word = word;
	MakeTopic(fsys, TVTOPICTYPE_INTERVIEW, TVTOPIC_INTERVIEW_CONTEST, qctw);
}
#include "../contest/con_tool.h"
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static int TVTOPIC_Make_QandA_Contest(FIELDSYS_WORK * fsys, WORDSET * ws, TVBCD * bcd)
{
	QANDA_CONTEST_WORK * qctw = TVBCD_GetTopicData(bcd);
	WORDSET_RegisterMonsName(ws, 0, qctw->contest.monsno,
			qctw->contest.mons_sex, qctw->contest.mons_region, qctw->contest.mons_rom);
	WORDSET_RegisterContestType(ws, 1, ConTool_IMCGetTypeMsgID(qctw->contest.contest_type));
	WORDSET_RegisterContestRank(ws, 2, ConTool_IMCGetRankMsgID(qctw->contest.contest_rank));
	WORDSET_RegisterNumber(ws, 3, qctw->contest.contest_result, 1,
			NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT);
	WORDSET_RegisterOwnerName(ws, 4, bcd);		//�g���[�i�[��
	WORDSET_RegisterPMSWord(ws, 5, qctw->word);
	if (qctw->contest.contest_result == 1) {
		return msg_tv_01_07_02;		//�D���p���b�Z�[�W
	} else {
		return msg_tv_01_07_01;
	}
}
//--------------------------------------------------------------------
///	�g�s�b�N�����`�F�b�N�F�R���e�X�g
//--------------------------------------------------------------------
static BOOL TVTOPIC_Limit_QandA_Contest(FIELDSYS_WORK * fsys, TVBCD * bcd)
{
	QANDA_CONTEST_WORK * qctw = TVBCD_GetTopicData(bcd);
	return ZukanWork_GetPokeSeeFlag(SaveData_GetZukanWork(fsys->savedata), qctw->contest.monsno);
}
//============================================================================================
//	�O�P�|�O�X	�|�P�����N���b�v�I	2	�N���b�v�����ꏊ	�N���b�v�����������
//============================================================================================
//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N�����F�|�P�����N���b�v�I
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	word		�ȈՉ�b�P��ID
 */
//--------------------------------------------------------------------
void TVTOPIC_Entry_QandA_Clip(FIELDSYS_WORK * fsys, PMS_WORD word)
{
	TOPIC_DATA TopicData;
	QANDA_CLIP_WORK * qclw = &TopicData.QandAClipWork;
	qclw->word = word;
	{
		IMC_SAVEDATA* iw = SaveData_GetImcSaveData(fsys->savedata);
		IMC_TELEVISION_SAVEDATA * itv = ImcSaveData_GetTelevisionSaveData(iw, 0);
		qclw->monsno = ImcSaveData_GetTelevisionPokeMonsNo(itv);
	}
	MakeTopic(fsys, TVTOPICTYPE_INTERVIEW, TVTOPIC_INTERVIEW_CLIP, qclw);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static int TVTOPIC_Make_QandA_Clip(FIELDSYS_WORK * fsys, WORDSET * ws, TVBCD * bcd)
{
	QANDA_CLIP_WORK * qclw = TVBCD_GetTopicData(bcd);
	WORDSET_RegisterOwnerName(ws, 0, bcd);		//�g���[�i�[��
	WORDSET_RegisterMonsNameEasy(ws, 1, qclw->monsno);
	WORDSET_RegisterPMSWord(ws, 2, qclw->word);
	return msg_tv_01_09_01;
}
//--------------------------------------------------------------------
///	�g�s�b�N�����`�F�b�N�F�o�g���^���[�A��
//--------------------------------------------------------------------
static BOOL TVTOPIC_Limit_QandA_Clip(FIELDSYS_WORK * fsys, TVBCD * bcd)
{
	QANDA_CLIP_WORK * qclw = TVBCD_GetTopicData(bcd);
	return ZukanWork_GetPokeSeeFlag(SaveData_GetZukanWork(fsys->savedata), qclw->monsno);
}
//============================================================================================
//	�O�P�|�P�O	���i�f�f�I	2		
//============================================================================================
//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N�����F���i�f�f�I
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	word		�ȈՉ�b�P��ID
 */
//--------------------------------------------------------------------
void TVTOPIC_Entry_QandA_Character(FIELDSYS_WORK * fsys, PMS_WORD word)
{
	TOPIC_DATA TopicData;
	QANDA_POKETYPE_WORK * qptype = &TopicData.QandAPokeTypeWork;
	qptype->type = word;
	MakeTopic(fsys, TVTOPICTYPE_INTERVIEW, TVTOPIC_INTERVIEW_CHARACTOR, qptype);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static int TVTOPIC_Make_QandA_Character(FIELDSYS_WORK * fsys, WORDSET * ws, TVBCD * bcd)
{
	QANDA_POKETYPE_WORK * qptype = TVBCD_GetTopicData(bcd);
	WORDSET_RegisterOwnerName(ws, 0, bcd);		//�g���[�i�[��
	return msg_tv_01_10_01 + qptype->type - 1;
}
//============================================================================================
//	�O�P�|�P�P		�|���g����		�|���g�����ꏊ	�|���g���������
//============================================================================================
//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N�����F�|���g����
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	word		�ȈՉ�b�P��ID
 */
//--------------------------------------------------------------------
void TVTOPIC_Entry_QandA_Poruto(FIELDSYS_WORK * fsys, PMS_WORD word)
{
	TOPIC_DATA TopicData;
	QANDA_PORUTO_WORK * qporuto = &TopicData.QandAPorutoWork;
	TOPICTEMP_PORUTO * poruto = TVWORK_GetPorutoTemp(SaveData_GetTvWork(fsys->savedata));
	qporuto->poruto = *poruto;
	qporuto->word = word;
	poruto->exist_flag = FALSE;
	MakeTopic(fsys, TVTOPICTYPE_INTERVIEW, TVTOPIC_INTERVIEW_PORUTO, qporuto);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static int TVTOPIC_Make_QandA_Poruto(FIELDSYS_WORK * fsys, WORDSET * ws, TVBCD * bcd)
{
	QANDA_PORUTO_WORK * qporuto = TVBCD_GetTopicData(bcd);
	int taste = qporuto->poruto.taste_type;
	WORDSET_RegisterOwnerName(ws, 0, bcd);		//�g���[�i�[��
	WORDSET_RegisterPorutoName(ws, 1, taste);
	WORDSET_RegisterPMSWord(ws, 2, qporuto->word);
	switch (taste) {
	case PORUTO_FLAVOR_HEAVY:
		return msg_tv_01_11_02;
	case PORUTO_FLAVOR_THICK:
		return msg_tv_01_11_03;
	case PORUTO_FLAVOR_NGOOD:
		return msg_tv_01_11_04;
	case PORUTO_FLAVOR_MILD:
		return msg_tv_01_11_05;
	default:
		return msg_tv_01_11_01;
	}
}

//============================================================================================
//	�O�P�|�P�R		�|�P�����A�����
//============================================================================================
//--------------------------------------------------------------------
/**
 * @brief	�g�s�b�N�����F�|�P�����A�����
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	word		�ȈՉ�b�P��ID
 */
//--------------------------------------------------------------------
void TVTOPIC_Entry_QandA_Park(FIELDSYS_WORK * fsys, PMS_WORD word)
{
	TOPIC_DATA TopicData;
	QANDA_PARK_WORK * qpark = &TopicData.QandAParkWork;
	TOPICTEMP_PARK * ptemp = TVWORK_GetParkTemp(SaveData_GetTvWork(fsys->savedata));
	qpark->park = *ptemp;
	qpark->word = word;
	ptemp->exist_flag = FALSE;
	MakeTopic(fsys, TVTOPICTYPE_INTERVIEW, TVTOPIC_INTERVIEW_TUREARUKI, qpark);
}
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static int TVTOPIC_Make_QandA_Park(FIELDSYS_WORK * fsys, WORDSET * ws, TVBCD * bcd)
{
	QANDA_PARK_WORK * qpark = TVBCD_GetTopicData(bcd);
	WORDSET_RegisterOwnerName(ws, 0, bcd);		//�g���[�i�[��
	WORDSET_RegisterMonsName(ws, 1, qpark->park.monsno,
			qpark->park.mons_sex, qpark->park.mons_region, qpark->park.mons_rom);
	WORDSET_RegisterSeikaku(ws, 2, qpark->park.poke_character);
	WORDSET_RegisterPMSWord(ws, 5, qpark->word);
	switch (qpark->park.pick_type) {
	case PARKPICK_ID_NOTHING:
		return msg_tv_01_13_02;
	case PARKPICK_ID_ACCESSORIES:
		WORDSET_RegisterAccessoryName(ws, 3, qpark->park.accessories);
		return msg_tv_01_13_01;
	case PARKPICK_ID_ITEM:
		WORDSET_RegisterItemName(ws, 3, qpark->park.item_no);
		return msg_tv_01_13_03;
	}
	return msg_tv_01_13_02;
}




//============================================================================================
//
//
//			�C�x���g�^�g�s�b�N
//
//
//============================================================================================
//============================================================================================
//�O�S�|�O�P	�O���[�v�Љ�
//============================================================================================
static const u8 RandomGroupID[] = {
	RANDOMGROUP_MYUSE,
	RANDOMGROUP_DATA0,
	RANDOMGROUP_DATA1,
	RANDOMGROUP_DATA2,
	RANDOMGROUP_DATA3,
};
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static int CountRandomGroup(RANDOM_GROUP * rg)
{
	int i,n;
	for (i = 0, n = 0; i< NELEMS(RandomGroupID); i++) {
		if (RandomGroup_ExistCheck(rg, RandomGroupID[i])) {
			//OS_TPrintf("RGROUP[%d] OK!\n",RandomGroupID[i]);
			n ++;
		}
	}
	return n;
}

//--------------------------------------------------------------------
///	�g�s�b�N�����F�O���[�v�Љ�
//--------------------------------------------------------------------
static int TVTOPIC_Make_Event_Group(FIELDSYS_WORK * fsys, WORDSET * ws, TVBCD * bcd)
{
	int i, n, id;
	int type;
	RANDOM_GROUP * rg = SaveData_GetRandomGroup(fsys->savedata);
	n = CountRandomGroup(rg);
	GF_ASSERT(n > 0);
	if (n > 1) {
		n = gf_mtRand() % n;
	} else {
		n = 0;
	}
	for (i = 0; i < NELEMS(RandomGroupID); i++) {
		if (RandomGroup_ExistCheck(rg, RandomGroupID[i])) {
			if (n == 0) {
				//OS_TPrintf("RGROUP:choose %d\n",RandomGroupID[i]);
				id = RandomGroupID[i];
				break;
			} else {
				n --;
			}
		}
	}
	GF_ASSERT(n == 0);

	type = gf_p_rand(17);
	if (type >= HATE_TYPE) {
		type ++;
	}
	WORDSET_RegisterGroupName(ws, fsys->savedata, id, 0, RANDOMGROUP_NAME_LEADER);
	WORDSET_RegisterGroupName(ws, fsys->savedata, id, 1, RANDOMGROUP_NAME_GROUP);
	WORDSET_RegisterPokeTypeName(ws, 2, type);
	return msg_tv_04_01_01;
}
//--------------------------------------------------------------------
///	�g�s�b�N�����`�F�b�N�F�O���[�v�Љ�
//--------------------------------------------------------------------
static BOOL TVTOPIC_Limit_Event_Group(FIELDSYS_WORK * fsys, TVBCD * bcd)
{
	RANDOM_GROUP * rg = SaveData_GetRandomGroup(fsys->savedata);
	if (CountRandomGroup(rg) != 0) {
		return TRUE;
	} else {
		return FALSE;
	}
}

//============================================================================================
//�O�S�|�O�Q	�V�C�\��
//============================================================================================
static u16 WeatherTable[] = {
	ZONE_ID_R212B,
	ZONE_ID_R213,
	ZONE_ID_R216,
	ZONE_ID_L03,
	ZONE_ID_C09,
};

//--------------------------------------------------------------------
///	�g�s�b�N�����F�V�C�\��
//--------------------------------------------------------------------
static int TVTOPIC_Make_Event_Weather(FIELDSYS_WORK * fsys, WORDSET * ws, TVBCD * bcd)
{
	int zone, weather;
	zone = WeatherTable[gf_p_rand(NELEMS(WeatherTable))];
	weather = WeatherData_Get(fsys, zone);
	WORDSET_RegisterPlaceName(ws, 0, ZoneData_GetPlaceNameID(zone));
	switch (weather) {
	case WEATHER_SYS_SUNNY:
		switch (gf_p_rand(4)) {
		case 0:
			return msg_tv_04_02_01;
		case 1:
			return msg_tv_04_02_02;
		case 2:
			return msg_tv_04_02_03;
		case 3:
			return msg_tv_04_02_04;
		}
	case WEATHER_SYS_CLOUDINESS:
		return msg_tv_04_02_05;
	case WEATHER_SYS_RAIN:
		return msg_tv_04_02_06;
	case WEATHER_SYS_STRAIN:
		return msg_tv_04_02_07;
	case WEATHER_SYS_SNOW:
		return msg_tv_04_02_08;
	case WEATHER_SYS_SNOWSTORM:
		return msg_tv_04_02_09;
	case WEATHER_SYS_SNOWSTORM_H:
		return msg_tv_04_02_10;
	case WEATHER_SYS_SPARK:
		return msg_tv_04_02_11;
	case WEATHER_SYS_DIAMONDDUST:
		return msg_tv_04_02_12;
	default:
		GF_ASSERT(0);
	}
	return msg_tv_04_02_01;		//���肦�Ȃ��͂������A�Ƃ肠����
}
//--------------------------------------------------------------------
///	�g�s�b�N�����`�F�b�N�F�V�C�\��
//--------------------------------------------------------------------
static BOOL TVTOPIC_Limit_Event_Weather(FIELDSYS_WORK * fsys, TVBCD * bcd)
{
	return TRUE;
}
//============================================================================================
//�O�S�|�O�T	��ʔ����I
//============================================================================================
//--------------------------------------------------------------------
///	�g�s�b�N�����F��ʔ����I
//--------------------------------------------------------------------
static int TVTOPIC_Make_Event_Outbreak(FIELDSYS_WORK * fsys, WORDSET * ws, TVBCD * bcd)
{
	u16 zone, poke;
	ENC_SV_PTR data = EncDataSave_GetSaveDataPtr(fsys->savedata);
	GenerateZone_GetInfo( EncDataSave_GetRandSeed(data, ENC_RND_SEED_GENERATE), &zone, &poke );
	WORDSET_RegisterPlaceName(ws, 0, ZoneData_GetPlaceNameID(zone));
	WORDSET_RegisterMonsNameEasy(ws, 1, poke);

	return msg_tv_04_05_01;
}
//--------------------------------------------------------------------
///	�g�s�b�N�����`�F�b�N�F��ʔ����I
//--------------------------------------------------------------------
static BOOL TVTOPIC_Limit_Event_Outbreak(FIELDSYS_WORK * fsys, TVBCD * bcd)
{
	ENC_SV_PTR data = EncDataSave_GetSaveDataPtr(fsys->savedata);
	return EncDataSave_IsGenerate(data);
}

//============================================================================================
//�O�S�|�O�V	�|�P���������`�����l��
//============================================================================================
//============================================================================================
/**
 *	�Z�ƃ|�P�����̑����`�F�b�N�p�����e�[�u��
 */
//============================================================================================
#define	KOUKANAI	(0)
#define	IMAHITOTSU	(1)
#define	BATSUGUN	(2)
#define	HUTSUU		(3)


enum{
	WAZA_TYPE=0,
	POKE_TYPE,
	POWER
};

static	const	u8	TypeCheckTable[][3]={
	{NORMAL_TYPE,	IWA_TYPE,		IMAHITOTSU},	// NORMAL �� IWA �ɍU������ƁA
													// �З͂O�D�T�{
	{NORMAL_TYPE,	METAL_TYPE,		IMAHITOTSU},

	{FIRE_TYPE,		FIRE_TYPE,		IMAHITOTSU},
	{FIRE_TYPE,		WATER_TYPE,		IMAHITOTSU},
	{FIRE_TYPE,		KUSA_TYPE,		BATSUGUN},	
	{FIRE_TYPE,		KOORI_TYPE,		BATSUGUN},	
	{FIRE_TYPE,		MUSHI_TYPE,		BATSUGUN},
	{FIRE_TYPE,		IWA_TYPE,		IMAHITOTSU},
	{FIRE_TYPE,		DRAGON_TYPE,	IMAHITOTSU},
	{FIRE_TYPE,		METAL_TYPE,		BATSUGUN},

	{WATER_TYPE,	FIRE_TYPE,		BATSUGUN},
	{WATER_TYPE,	WATER_TYPE,		IMAHITOTSU},
	{WATER_TYPE,	KUSA_TYPE,		IMAHITOTSU},
	{WATER_TYPE,	JIMEN_TYPE,		BATSUGUN},
	{WATER_TYPE,	IWA_TYPE,		BATSUGUN},
	{WATER_TYPE,	DRAGON_TYPE,	IMAHITOTSU},

	{ELECTRIC_TYPE,	WATER_TYPE,		BATSUGUN},
	{ELECTRIC_TYPE,	ELECTRIC_TYPE,	IMAHITOTSU},
	{ELECTRIC_TYPE,	KUSA_TYPE,		IMAHITOTSU},
	{ELECTRIC_TYPE,	JIMEN_TYPE,		KOUKANAI},
	{ELECTRIC_TYPE,	HIKOU_TYPE,		BATSUGUN},
	{ELECTRIC_TYPE,	DRAGON_TYPE,	IMAHITOTSU},

	{KUSA_TYPE,		FIRE_TYPE,		IMAHITOTSU},
	{KUSA_TYPE,		WATER_TYPE,		BATSUGUN},
	{KUSA_TYPE,		KUSA_TYPE,		IMAHITOTSU},
	{KUSA_TYPE,		POISON_TYPE,	IMAHITOTSU},
	{KUSA_TYPE,		JIMEN_TYPE,		BATSUGUN},
	{KUSA_TYPE,		HIKOU_TYPE,		IMAHITOTSU},
	{KUSA_TYPE,		MUSHI_TYPE,		IMAHITOTSU},
	{KUSA_TYPE,		IWA_TYPE,		BATSUGUN},
	{KUSA_TYPE,		DRAGON_TYPE,	IMAHITOTSU},
	{KUSA_TYPE,		METAL_TYPE,		IMAHITOTSU},

	{KOORI_TYPE,	WATER_TYPE,		IMAHITOTSU},
	{KOORI_TYPE,	KUSA_TYPE,		BATSUGUN},
	{KOORI_TYPE,	KOORI_TYPE,		IMAHITOTSU},
	{KOORI_TYPE,	JIMEN_TYPE,		BATSUGUN},
	{KOORI_TYPE,	HIKOU_TYPE,		BATSUGUN},
	{KOORI_TYPE,	DRAGON_TYPE,	BATSUGUN},
	{KOORI_TYPE,	METAL_TYPE,		IMAHITOTSU},
	{KOORI_TYPE,	FIRE_TYPE,		IMAHITOTSU},

	{BATTLE_TYPE,	NORMAL_TYPE,	BATSUGUN},
	{BATTLE_TYPE,	KOORI_TYPE,		BATSUGUN},
	{BATTLE_TYPE,	POISON_TYPE,	IMAHITOTSU},
	{BATTLE_TYPE,	HIKOU_TYPE,		IMAHITOTSU},
	{BATTLE_TYPE,	SP_TYPE,		IMAHITOTSU},
	{BATTLE_TYPE,	MUSHI_TYPE,		IMAHITOTSU},
	{BATTLE_TYPE,	IWA_TYPE,		BATSUGUN},
	{BATTLE_TYPE,	AKU_TYPE,		BATSUGUN},
	{BATTLE_TYPE,	METAL_TYPE,		BATSUGUN},

	{POISON_TYPE,	KUSA_TYPE,		BATSUGUN},
	{POISON_TYPE,	POISON_TYPE,	IMAHITOTSU},
	{POISON_TYPE,	JIMEN_TYPE,		IMAHITOTSU},
	{POISON_TYPE,	IWA_TYPE,		IMAHITOTSU},
	{POISON_TYPE,	GHOST_TYPE,		IMAHITOTSU},
	{POISON_TYPE,	METAL_TYPE,		KOUKANAI},

	{JIMEN_TYPE,	FIRE_TYPE,		BATSUGUN},
	{JIMEN_TYPE,	ELECTRIC_TYPE,	BATSUGUN},
	{JIMEN_TYPE,	KUSA_TYPE,		IMAHITOTSU},
	{JIMEN_TYPE,	POISON_TYPE,	BATSUGUN},
	{JIMEN_TYPE,	HIKOU_TYPE,		KOUKANAI},
	{JIMEN_TYPE,	MUSHI_TYPE,		IMAHITOTSU},
	{JIMEN_TYPE,	IWA_TYPE,		BATSUGUN},
	{JIMEN_TYPE,	METAL_TYPE,		BATSUGUN},

	{HIKOU_TYPE,	ELECTRIC_TYPE,	IMAHITOTSU},
	{HIKOU_TYPE,	KUSA_TYPE,		BATSUGUN},
	{HIKOU_TYPE,	BATTLE_TYPE,	BATSUGUN},
	{HIKOU_TYPE,	MUSHI_TYPE,		BATSUGUN},
	{HIKOU_TYPE,	IWA_TYPE,		IMAHITOTSU},
	{HIKOU_TYPE,	METAL_TYPE,		IMAHITOTSU},

	{SP_TYPE,		BATTLE_TYPE,	BATSUGUN},
	{SP_TYPE,		POISON_TYPE,	BATSUGUN},
	{SP_TYPE,		SP_TYPE,		IMAHITOTSU},
	{SP_TYPE,		AKU_TYPE,		KOUKANAI},
	{SP_TYPE,		METAL_TYPE,		IMAHITOTSU},	

	{MUSHI_TYPE,	FIRE_TYPE,		IMAHITOTSU},
	{MUSHI_TYPE,	KUSA_TYPE,		BATSUGUN},
	{MUSHI_TYPE,	BATTLE_TYPE,	IMAHITOTSU},
	{MUSHI_TYPE,	POISON_TYPE,	IMAHITOTSU},
	{MUSHI_TYPE,	HIKOU_TYPE,		IMAHITOTSU},
	{MUSHI_TYPE,	SP_TYPE,		BATSUGUN},
	{MUSHI_TYPE,	GHOST_TYPE,		IMAHITOTSU},
	{MUSHI_TYPE,	AKU_TYPE,		BATSUGUN},
	{MUSHI_TYPE,	METAL_TYPE,		IMAHITOTSU},

	{IWA_TYPE,		FIRE_TYPE,		BATSUGUN},
	{IWA_TYPE,		KOORI_TYPE,		BATSUGUN},
	{IWA_TYPE,		BATTLE_TYPE,	IMAHITOTSU},
	{IWA_TYPE,		JIMEN_TYPE,		IMAHITOTSU},
	{IWA_TYPE,		HIKOU_TYPE,		BATSUGUN},
	{IWA_TYPE,		MUSHI_TYPE,		BATSUGUN},
	{IWA_TYPE,		METAL_TYPE,		IMAHITOTSU},

	{GHOST_TYPE,	NORMAL_TYPE,	KOUKANAI},
	{GHOST_TYPE,	SP_TYPE,		BATSUGUN},
	{GHOST_TYPE,	AKU_TYPE,		IMAHITOTSU},
	{GHOST_TYPE,	METAL_TYPE,		IMAHITOTSU},
	{GHOST_TYPE,	GHOST_TYPE,		BATSUGUN},	

	{DRAGON_TYPE,	DRAGON_TYPE,	BATSUGUN},
	{DRAGON_TYPE,	METAL_TYPE,		IMAHITOTSU},

	{AKU_TYPE,		BATTLE_TYPE,	IMAHITOTSU},
	{AKU_TYPE,		SP_TYPE,		BATSUGUN},
	{AKU_TYPE,		GHOST_TYPE,		BATSUGUN},
	{AKU_TYPE,		AKU_TYPE,		IMAHITOTSU},
	{AKU_TYPE,		METAL_TYPE,		IMAHITOTSU},

	{METAL_TYPE,	FIRE_TYPE,		IMAHITOTSU},
	{METAL_TYPE,	WATER_TYPE,		IMAHITOTSU},
	{METAL_TYPE,	ELECTRIC_TYPE,	IMAHITOTSU},
	{METAL_TYPE,	KOORI_TYPE,		BATSUGUN},
	{METAL_TYPE,	IWA_TYPE,		BATSUGUN},
	{METAL_TYPE,	METAL_TYPE,		IMAHITOTSU},

	{NORMAL_TYPE,	GHOST_TYPE,		KOUKANAI},
	{BATTLE_TYPE,	GHOST_TYPE,		KOUKANAI},

};
static int GetWazaKouka(int attack, int deffence)
{
	int i;
	for (i = 0; i < NELEMS(TypeCheckTable); i++) {
		if ((TypeCheckTable[i][WAZA_TYPE] == attack) && (TypeCheckTable[i][POKE_TYPE] == deffence)) {
			return TypeCheckTable[i][POWER];
		}
	}
	return HUTSUU;
}
//--------------------------------------------------------------------
///	�g�s�b�N�����F
//--------------------------------------------------------------------
static int TVTOPIC_Make_Event_Aishou(FIELDSYS_WORK * fsys, WORDSET * ws, TVBCD * bcd)
{
	int a_type, d_type;
	a_type = gf_p_rand(17);
	if (a_type >= HATE_TYPE) {
		a_type ++;
	}
	d_type = gf_p_rand(17);
	if (d_type >= HATE_TYPE) {
		d_type ++;
	}
	WORDSET_RegisterPokeTypeName(ws, 0, a_type);
	WORDSET_RegisterPokeTypeName(ws, 1, d_type);
	switch (GetWazaKouka(a_type, d_type)) {
	case BATSUGUN:
		return msg_tv_04_07_01;
	case HUTSUU:
	default:
		return msg_tv_04_07_02;
	case IMAHITOTSU:
		return msg_tv_04_07_03;
	case KOUKANAI:
		return msg_tv_04_07_04;
	}
}

//--------------------------------------------------------------------
///	�g�s�b�N�����`�F�b�N�F
//--------------------------------------------------------------------
static BOOL TVTOPIC_Limit_Event_Aishou(FIELDSYS_WORK * fsys, TVBCD * bcd)
{
	return TRUE;
}
//============================================================================================
//�O�S�|�O�X	���݂̂��傤�ق�
//============================================================================================
static const u16 KinomiFlagTable[] = {
	FLAG_ARRIVE_T01,	//( 0)
	FLAG_ARRIVE_T02,	//( 1)
	FLAG_ARRIVE_T03,	//( 2)
	FLAG_ARRIVE_T04,	//( 3)
	FLAG_ARRIVE_T05,	//( 4)
	FLAG_ARRIVE_T06,	//( 5)
	FLAG_ARRIVE_T07,	//( 6)
	FLAG_ARRIVE_C01,	//( 7)
	FLAG_ARRIVE_C02,	//( 8)
	FLAG_ARRIVE_C03,	//( 9)
	FLAG_ARRIVE_C04,	//(10)
	FLAG_ARRIVE_C05,	//(11)
	FLAG_ARRIVE_C06,	//(12)
	FLAG_ARRIVE_C07,	//(13)
	FLAG_ARRIVE_C08,	//(14)
	FLAG_ARRIVE_C09,	//(15)
	FLAG_ARRIVE_C10,	//(16)
	FLAG_ARRIVE_C11,	//(17)
};
#include "..\fielddata\setting\kinomi_zone.c"

//--------------------------------------------------------------------
//--------------------------------------------------------------------
static int GetNutsID(FIELDSYS_WORK * fsys)
{
	u8 flags[NELEMS(KinomiFlagTable)];
	u8 id[NELEMS(KinomiZoneTable)/2];
	int i, n;
	EVENTWORK * ev = SaveData_GetEventWork(fsys->savedata);
	for (i = 0; i < NELEMS(KinomiFlagTable); i ++) {
		flags[i] = SysFlag_ArriveGet(ev, KinomiFlagTable[i]);
		OS_TPrintf("FLAG %02d = %d\n",KinomiFlagTable[i], flags[i]);
	}
	for (i = 0, n = 0; i < NELEMS(KinomiZoneTable)/2; i++ ) {
		if (flags[KinomiZoneTable[i*2]]) {
			OS_TPrintf("ID:%02d FLAG%02d\n",i, KinomiZoneTable[i*2]);
			id[n] = i;
			n ++;
		}
	}
	return id[gf_p_rand(n)];
}
//--------------------------------------------------------------------
///	�g�s�b�N�����F���݂̂��傤�ق�
//--------------------------------------------------------------------
static int TVTOPIC_Make_Event_NutsInfo(FIELDSYS_WORK * fsys, WORDSET * ws, TVBCD * bcd)
{
	SEEDBED * sbed = SaveData_GetSeedBed(fsys->savedata);
	int id, zone;

	id = GetNutsID(fsys);
	zone = KinomiZoneTable[id*2+1];
	WORDSET_RegisterPlaceName(ws, 0, ZoneData_GetPlaceNameID(zone));

	switch (SEEDBED_GetSeedStatus(sbed, id)) {
	case SEEDSTAT_FRUIT:
		return msg_tv_04_09_01;
	case SEEDSTAT_FLOWER:
		return msg_tv_04_09_02;
	case SEEDSTAT_MIKI:
		return msg_tv_04_09_03;
	case SEEDSTAT_HUTABA:
		return msg_tv_04_09_04;
	case SEEDSTAT_NOTHING:
	case SEEDSTAT_UNDERGROUND:
	default:
		return msg_tv_04_09_05;
	}
}

//--------------------------------------------------------------------
///	�g�s�b�N�����`�F�b�N�F���݂̂��傤�ق�
//--------------------------------------------------------------------
static BOOL TVTOPIC_Limit_Event_NutsInfo(FIELDSYS_WORK * fsys, TVBCD * bcd)
{
	EVENTWORK * ev = SaveData_GetEventWork(fsys->savedata);
	//�V�i���I�I�ɂ����Ƃ��߂��ꏊ�Ȃ̂�
	return SysFlag_ArriveGet(ev, FLAG_ARRIVE_C03);
}

//============================================================================================
//�O�S�|�P�P	�ǂ����������Ă�쐶�|�P����
//============================================================================================
//--------------------------------------------------------------------
///	�g�s�b�N�����F�ǂ����������Ă�쐶�|�P����
//--------------------------------------------------------------------
static int TVTOPIC_Make_Event_PokemonItem(FIELDSYS_WORK * fsys, WORDSET * ws, TVBCD * bcd)
{
	int size, ofs, pos;
	u16 poke, item;
	ArchiveDataLoadOfs(&size, ARC_TV, NARC_tv_pokeitem_bin, 0, sizeof(int));
	pos = gf_p_rand(size);
	ofs = sizeof(int) + pos * sizeof(u16) * 2;
	ArchiveDataLoadOfs(&poke, ARC_TV, NARC_tv_pokeitem_bin, ofs, sizeof(u16));
	ArchiveDataLoadOfs(&item, ARC_TV, NARC_tv_pokeitem_bin, ofs + sizeof(u16), sizeof(u16));
	WORDSET_RegisterMonsNameEasy(ws, 0, poke);
	WORDSET_RegisterItemName(ws, 1, item);
	return msg_tv_04_11_01;
}
//--------------------------------------------------------------------
///	�g�s�b�N�����`�F�b�N�F�ǂ����������Ă�쐶�|�P����
//--------------------------------------------------------------------
static BOOL TVTOPIC_Limit_Event_PokemonItem(FIELDSYS_WORK * fsys, TVBCD * bcd)
{
	return TRUE;
}
//============================================================================================
//�O�S�|�P�V	�|�P�����t�@�b�V�����`�F�b�N
//============================================================================================
//--------------------------------------------------------------------
//--------------------------------------------------------------------
static int CountClipInfo(IMC_SAVEDATA * iw)
{
	int i, n;
	for (i = 0, n = 0; i < IMC_SAVEDATA_TELEVISION_SAVENUM; i++) {
		if (ImcSaveData_CheckTelevisionSaveData(iw, i) == TRUE) {
			n ++;
		}
	}
	return n;
}
//--------------------------------------------------------------------
///	�g�s�b�N�����F�|�P�����t�@�b�V�����`�F�b�N
//--------------------------------------------------------------------
static int TVTOPIC_Make_Event_ClipInfo(FIELDSYS_WORK * fsys, WORDSET * ws, TVBCD * bcd)
{
	IMC_TELEVISION_SAVEDATA * itv;
	int i,n,count,id;
	IMC_SAVEDATA* iw = SaveData_GetImcSaveData(fsys->savedata);
	n = CountClipInfo(iw);
	if (n > 1) {
		count = gf_mtRand() % n;
	} else {
		count = 0;
	}
	for (i = 0; i < IMC_SAVEDATA_TELEVISION_SAVENUM; i++ ) {
		if (ImcSaveData_CheckTelevisionSaveData(iw, i) == TRUE) {
			if (count == 0) {
				id = i;
				break;
			} else {
				count --;
			}
		}
	}
	GF_ASSERT(i < IMC_SAVEDATA_TELEVISION_SAVENUM);
	itv= ImcSaveData_GetTelevisionSaveData(iw, id);
	{
		//PMS_DATA pmsdata;
		PMS_WORD pmsword;
		STRBUF * strbuf = STRBUF_Create(PERSON_NAME_SIZE + EOM_SIZE, HEAPID_FIELD);
		int sex = ImcSaveData_GetTelevisionPokeOyaSex(itv);
		ImcSaveData_GetTelevisionPokeOyaName(itv, strbuf);
		WORDSET_RegisterWord(ws, 0, strbuf, sex, TRUE, ImcSaveData_GetCountryCode(itv));
		STRBUF_Delete(strbuf);
		pmsword = ImcSaveData_GetTelevisionTitlePmsWord(itv);
		WORDSET_RegisterPMSWord(ws, 1, pmsword);
		//ImcSaveData_GetTelevisionTitle(itv, &pmsdata);
		//WORDSET_RegisterPMSWord(ws, 1, pmsdata.word[0]);
	}

	return msg_tv_04_17_01;
}
//--------------------------------------------------------------------
///	�g�s�b�N�����`�F�b�N�F�|�P�����t�@�b�V�����`�F�b�N
//--------------------------------------------------------------------
static BOOL TVTOPIC_Limit_Event_ClipInfo(FIELDSYS_WORK * fsys, TVBCD * bcd)
{
	IMC_SAVEDATA* iw = SaveData_GetImcSaveData(fsys->savedata);
	if (CountClipInfo(iw) != 0) {
		return TRUE;
	} else {
		return FALSE;
	}
}




//============================================================================================
//============================================================================================
//--------------------------------------------------------------------
/**
 * @brief	�Ď��^�g�s�b�N�����֐��e�[�u��
 */
//--------------------------------------------------------------------
static const TOPIC_FUNC_DATA WatchNewsFuncTable[] = {
	{//TVTOPIC_WATCH_POKE_GET_SUCCESS
		TVTOPIC_Make_Watch_SuccessCapture,
		TVTOPIC_Limit_Watch_Capture,
	},
	{//TVTOPIC_WATCH_POKE_GET_FAILURE
		TVTOPIC_Make_Watch_FailureCapture,
		NULL,
	},
	{//TVTOPIC_WATCH_FISHING
		TVTOPIC_Make_Watch_Fishing,
		TVTOPIC_Limit_Watch_Fishing,
	},
	{//TVTOPIC_WATCH_CHANGE_GROUP
		TVTOPIC_Make_Watch_ChangeGroup,
		NULL,
	},
	{//TVTOPIC_WATCH_SEE_RARE_POKEMON,		///<���A�|�P���������I	3	���A�|�P�����Ƃ̃G���J�E���g��
		NULL,
		NULL,
	},
	{//TVTOPIC_WATCH_GET_HIDE_ITEM,
		TVTOPIC_Make_Watch_HideItem,
		NULL,
	},
	{//TVTOPIC_WATCH_SHOPPING,				///<�������`�F�b�N	4	��x��10�ȏ�̓���𔃂����Ƃ�
		NULL,
		NULL,
	},
	{//TVTOPIC_WATCH_BORN_EGG
		TVTOPIC_Make_Watch_HatchEgg,
		TVTOPIC_Limit_Watch_HatchEgg,
	},
	{//TVTOPIC_WATCH_CHECK_SODATEYA,		///<��ĉ��`�F�b�N		��ĉ��ɗa�����Ƃ�
		NULL,
		NULL,
	},
	{//TVTOPIC_WATCH_CHANGE_NICKNAME
		TVTOPIC_Make_Watch_ChangeName,
		TVTOPIC_Limit_Watch_ChangeName,
	},
	{//TVTOPIC_WATCH_POISON_DEAD,			///<�łłЂ񎀁c�c		�t�B�[���h�Ń|�P�������m���ɂȂ����Ƃ�
		NULL,
		NULL,
	},
	{//TVTOPIC_WATCH_WIN_LOT,				///<�|�P�����������I�I		�|�P���������ɓ��������Ƃ�
		NULL,
		NULL,
	},
	{//TVTOPIC_WATCH_DIG_FOSSIL
		TVTOPIC_Make_Watch_DigFossil,
		TVTOPIC_Limit_Watch_Tankou,
	},
	{//TVTOPIC_WATCH_DENDOU,				///<�a������I	�͂��߂ēa�����肵���Ƃ�
		NULL,
		NULL,
	},
	{//TVTOPIC_WATCH_SAFARI
		TVTOPIC_Make_Watch_Safari,
		TVTOPIC_Limit_Watch_Safari,
	},
	{//TVTOPIC_WATCH_OSU_MESU,				///<�I�X�����I���X�����I	�p�\�R�����甲�����Ƃ��̎莝���ɂ��
		NULL,
		NULL,
	},
	{//TVTOPIC_WATCH_KANPOU
		TVTOPIC_Make_Watch_UseKanpo,
		TVTOPIC_Limit_Watch_UseKanpo,
	},
	{//TVTOPIC_WATCH_NUTS_HARVEST
		TVTOPIC_Make_Watch_NutsHarvest,
		NULL,
	},
	{//TVTOPIC_WATCH_NUTS_POOR
		TVTOPIC_Make_Watch_NutsPoor,
		NULL,
	},
	{//TVTOPIC_WATCH_MAKE_NEW_GROUP,		///<�V�O���[�v�a���I	�V�����O���[�v��������Ƃ�
		TVTOPIC_Make_Watch_MakeNewGroup,
		NULL,
	},
	{//TVTOPIC_WATCH_SET_CUSTOMBALL
		TVTOPIC_Make_Watch_CustomBall,
		TVTOPIC_Limit_Watch_CustomBall,
	},
	{//TVTOPIC_WATCH_GET_FLAG,
		TVTOPIC_Make_Watch_GetFlag,
		TVTOPIC_Limit_Watch_Tankou,
	},
	{//TVTOPIC_WATCH_LOSE_FLAG
		TVTOPIC_Make_Watch_LoseFlag,
		TVTOPIC_Limit_Watch_Tankou,
	},
	{//TVTOPIC_WATCH_RIBBON,				///<���{��		
		NULL,
		NULL,
	},
};



//============================================================================================
//============================================================================================
//--------------------------------------------------------------------
/**
 * @brief	�M�l�X�^�g�s�b�N�����֐��e�[�u��
 */
//--------------------------------------------------------------------
static const TOPIC_FUNC_DATA RecordNewsFuncTable[TVTOPIC_RECORD_MAX - 1] = {
	{//TVTOPIC_RECORD_BTOWER
		TVTOPIC_Make_Record_BTower,
		TVTOPIC_Limit_Record_BTower,
	},
	{//TVTOPIC_RECORD_BFACTORY,		///<�t�@�N�g���[�A���L�^�X�V	�t�@�N�g���[�A���L�^���X�V�����Ƃ�
		NULL,
		NULL,
	},
	{//TVTOPIC_RECORD_OOKISA
		TVTOPIC_Make_Record_Ookisa,
		TVTOPIC_Limit_Record_Ookisa,
	},
	{//TVTOPIC_RECORD_SLOT
		TVTOPIC_Make_Record_Slot,
		NULL,
	},
	{//TVTOPIC_RECORD_RIBBON,			///<���{���R���N�^�[	���{������薇���ȏ�l�����ɍ쐬
		NULL,
		NULL,
	},
	{//TVTOPIC_RECORD_NUTS_MASTER
		TVTOPIC_Make_Record_NutsMaster,
		NULL,
	},
	{//TVTOPIC_RECORD_POKE_SEARCHER,	///<�h�ꑐ���l		�h�ꑐ�G���J�E���g���I�������Ƃ��A������10�ȏ�
		NULL,
		NULL,
	},
	{//TVTOPIC_RECORD_TRAP_REMOVER
		TVTOPIC_Make_Record_RemoveTrap,
		TVTOPIC_Limit_Record_Tankou,
	},
	{//TVTOPIC_RECORD_FLAG_GET
		TVTOPIC_Make_Record_GetFlag,
		TVTOPIC_Limit_Record_Tankou,
	},

};


//============================================================================================
//============================================================================================
//--------------------------------------------------------------------
/**
 * @brief	����^�g�s�b�N�����֐��e�[�u��
 */
//--------------------------------------------------------------------
static const TOPIC_FUNC_DATA QandANewsFuncTable[TVTOPIC_INTERVIEW_TYPE_MAX - 1] = {
	{//TVTOPIC_INTERVIEW_GYM_BADGE = 1,///<�W�����e�I	1	�W���̂���V�e�B	�W�����[�_�[��|��������
		NULL,
		NULL,
	},
	{//TVTOPIC_INTERVIEW_BTOWER,
		TVTOPIC_Make_QandA_BTower,
		TVTOPIC_Limit_QandA_BTower,
	},
	{//TVTOPIC_INTERVIEW_BFACTORY,		///<����I�t�@�N�g���[	1	�o�g���t�@�N�g���[	����I����
		NULL,
		NULL,
	},
	{//TVTOPIC_INTERVIEW_POKEMON,
		TVTOPIC_Make_QandA_Pokemon,
		TVTOPIC_Limit_QandA_Pokemon,
	},
	{//TVTOPIC_INTERVIEW_ITEM,			///<�������߂̂ǂ����I	2	�t�����h���B�V���b�v	
		NULL,
		NULL,
	},
	{//TVTOPIC_INTERVIEW_POKETCH,
		TVTOPIC_Make_QandA_Poketch,
		NULL,
	},
	{//TVTOPIC_INTERVIEW_CONTEST,
		TVTOPIC_Make_QandA_Contest,
		TVTOPIC_Limit_QandA_Contest,
	},
	{//TVTOPIC_INTERVIEW_TATOE,		///<�|�P�����ɗႦ����H	2	��D���N���u	
		NULL,
		NULL,
	},
	{//TVTOPIC_INTERVIEW_CLIP,
		TVTOPIC_Make_QandA_Clip,
		TVTOPIC_Limit_QandA_Clip,
	},
	{//TVTOPIC_INTERVIEW_CHARACTOR,
		TVTOPIC_Make_QandA_Character,
		NULL,
	},
	{//TVTOPIC_INTERVIEW_PORUTO,
		TVTOPIC_Make_QandA_Poruto,
		NULL,
	},
	{//TVTOPIC_INTERVIEW_KOUKAN,		///<���������|�P����	1		
		NULL,
		NULL,
	},
	{//TVTOPIC_INTERVIEW_TUREARUKI,	///<�A������𖞋i�I		���R�����Q�[�g	�A�������
		TVTOPIC_Make_QandA_Park,
		NULL,
	},
};

//============================================================================================
//============================================================================================
//--------------------------------------------------------------------
/**
 * @brief	�C�x���g�^�g�s�b�N�����֐��e�[�u��
 */
//--------------------------------------------------------------------
static const TOPIC_FUNC_DATA EventNewsFuncTable[TVTOPIC_EVENT_TYPE_MAX - 1] = {
	{	//TVTOPIC_EVENT_RANDOMGROUP = 1,		///<�O���[�v�Љ�
		TVTOPIC_Make_Event_Group,
		TVTOPIC_Limit_Event_Group,
	},
	{	//TVTOPIC_EVENT_WEATHER,				///<�V�C�\��
		TVTOPIC_Make_Event_Weather,
		TVTOPIC_Limit_Event_Weather,
	},
	{	//TVTOPIC_EVENT_TOWNGUIDE,			///<�V���I�E���̊X���̊X
		NULL,
		NULL,
	},
	{	//TVTOPIC_EVENT_BARGAIN,				///<�V���b�v��������
		NULL,
		NULL,
	},
	{	//TVTOPIC_EVENT_POKEMON_OUTBREAK,		///<��ʔ����I
		TVTOPIC_Make_Event_Outbreak,
		TVTOPIC_Limit_Event_Outbreak,
	},
	{	//TVTOPIC_EVENT_POKEMON_ENCOUNT,		///<�|�P�����o�v���I
		NULL,
		NULL,
	},
	{	//TVTOPIC_EVENT_POKEMON_AISHOU,		///<�|�P���������`�����l��
		TVTOPIC_Make_Event_Aishou,
		TVTOPIC_Limit_Event_Aishou,
	},
	{	//TVTOPIC_EVENT_POSTMAN,				///<�z�B�������
		NULL,
		NULL,
	},
	{	//TVTOPIC_EVENT_NUTS_INFOMATION,		///<���݂̂��傤�ق�
		TVTOPIC_Make_Event_NutsInfo,
		TVTOPIC_Limit_Event_NutsInfo,
	},
	{	//TVTOPIC_EVENT_WAZAMACHINE,			///<�킴�}�V�����傤�ق�
		NULL,
		NULL,
	},
	{	//TVTOPIC_EVENT_POKEMON_ITEM,			///<�ǂ����������Ă�쐶�|�P����
		TVTOPIC_Make_Event_PokemonItem,
		TVTOPIC_Limit_Event_PokemonItem,
	},
	{	//TVTOPIC_EVENT_POKEMON_CHARACTOR,	///<���������f�f
		NULL,
		NULL,
	},
	{	//TVTOPIC_EVENT_SLOT_INFO,			///<�X���b�g�̏o�ʏ��
		NULL,
		NULL,
	},
	{	//TVTOPIC_EVENT_TV_SHOPPING,			///<�s�u�V���b�s���O
		NULL,
		NULL,
	},
	{	//TVTOPIC_EVENT_TV_MOVE_POKEMON,		///<�ړ��|�P�����ڌ����I
		NULL,
		NULL,
	},
	{	//TVTOPIC_EVENT_TV_TAMAGO_INFO,		///<�^�}�S������
		NULL,
		NULL,
	},
	{	//TVTOPIC_EVENT_TV_CLIP_INFO,			///<�|�P�����t�@�b�V�����`�F�b�N
		TVTOPIC_Make_Event_ClipInfo,
		TVTOPIC_Limit_Event_ClipInfo,
	},
};
