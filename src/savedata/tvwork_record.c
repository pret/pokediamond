//============================================================================================
/**
 * @file	tvwork_record.c
 * @brief	�e���r�f�[�^�̃��R�[�h����
 * @author	tamada GAME FREAK inc.
 * @date	2006.05.31
 *
 * ���R�[�h��������Ă΂�邽�߂ɏ풓�̈�ɔz�u����Ă��Ȃ��B
 * ���̂��߂ǂ�����ł��Ăׂ�킯�ł͂Ȃ����Ƃɒ���
 */
//============================================================================================

#include "common.h"
#include "savedata/savedata_def.h"
#include "system/gamedata.h"

#include "gflib/gf_date.h"

#include "savedata/tv_work.h"
#include "tvwork_local.h"

#include "field/tv_topic.h"

#include "system/pm_rtc.h"
#include "system/pm_str.h"


#ifdef	DEBUG_ONLY_FOR_tamada
#define	DEBUG_PRT_TAMADA(...)	OS_TPrintf( __VA_ARGS__ )
#else
#define	DEBUG_PRT_TAMADA(...)	((void)0)
#endif

//============================================================================================
//
//			��`�Ȃ�
//
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	����M����e���r�g�s�b�N�̐�
 */
//----------------------------------------------------------
#define	TV_RECV_MAX			(4)			

//----------------------------------------------------------
/**
 * @brief	�ʐM����l��
 *
 * �z��ł��Ȃ��̂łƂ肠�����B���ۂ�5�l�m�肩�H
 */
//----------------------------------------------------------
#define	TV_COMM_MEMBER_MAX	(16)

//============================================================================================
//
//			���M�f�[�^�T�C�Y�擾
//
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	�e���r�p���M�f�[�^�T�C�Y
 * @param	sv		�Z�[�u�f�[�^�ւ̃A�h���X
 * @return	u32		���M�f�[�^�̃T�C�Y
 */
//----------------------------------------------------------
u32 TVWORK_GetSendQandADataSize(const SAVEDATA * sv)
{
	return sizeof(SEND_TOPIC) * MY_QANDA_MAX;
}
//----------------------------------------------------------
/**
 * @brief	�e���r�p���M�f�[�^�T�C�Y
 * @param	sv		�Z�[�u�f�[�^�ւ̃A�h���X
 * @return	u32		���M�f�[�^�̃T�C�Y
 */
//----------------------------------------------------------
u32 TVWORK_GetSendWatchDataSize(const SAVEDATA * sv)
{
	return sizeof(SEND_TOPIC) * MY_WATCH_MAX;
}

//----------------------------------------------------------
/**
 * @brief	�e���r�p���M�f�[�^�T�C�Y
 * @param	sv		�Z�[�u�f�[�^�ւ̃A�h���X
 * @return	u32		���M�f�[�^�̃T�C�Y
 */
//----------------------------------------------------------
u32 TVWORK_GetSendRecordDataSize(const SAVEDATA * sv)
{
	return sizeof(SEND_TOPIC) * MY_RECORD_MAX;
}


//============================================================================================
//
//
//			���M�f�[�^����
//
//
//============================================================================================
//----------------------------------------------------------
/**
 * @brief		�����f�[�^���瑗�M�f�[�^���쐬����
 * @param		sv		�Z�[�u�f�[�^�ւ̃A�h���X
 * @param		send	���M�f�[�^���i�[����o�b�t�@
 * @param		mt		�����f�[�^�ւ̃|�C���^
 * @param		max		�����f�[�^�̐�
 */
//----------------------------------------------------------
static void MakeSendTopicByMyTopic(SAVEDATA * sv, SEND_TOPIC * send,
		MY_TOPIC * mt, int max)
{
	int i;
	MYSTATUS * my = SaveData_GetMyStatus(sv);

	for (i = 0; i < max; i++, send++) {
		MI_CpuClearFast(send, sizeof(SEND_TOPIC));

		//���M�ҏ��𖄂ߍ���
		send->owner_id = MyStatus_GetID(my);
		send->sex = MyStatus_GetMySex(my);
		send->rom_ver = PM_VERSION;
		send->region_code = PM_LANG;
		PM_strncpy(send->owner_name, MyStatus_GetMyName(my), PERSON_NAME_SIZE + EOM_SIZE);

		send->topic = mt[i].topic;
		send->topic.see_count = 0;	//���M�f�[�^�̎����J�E���g�̓N���A
	}
	//���M�f�[�^�𐶐������玩���f�[�^�͍폜����
	//MI_CpuClearFast(mt, sizeof(MY_TOPIC) * max);
}
//----------------------------------------------------------
/**
 * @brief	����^�g�s�b�N�����f�[�^��Alloc
 * @param	sv
 * @param	headID
 * @param	size
 */
//----------------------------------------------------------
SEND_TOPIC * TVWORK_AllocSendQandAData(SAVEDATA * sv, int headID, u32 size)
{
	SEND_TOPIC * buf;
	TV_WORK * tvwk;
	buf = sys_AllocMemoryLo(headID, size);
	tvwk = SaveData_GetTvWork(sv);
	GF_ASSERT(size == TVWORK_GetSendQandADataSize(sv));
	MakeSendTopicByMyTopic(sv, buf, tvwk->MyQandATopic, MY_QANDA_MAX);
	return buf;
}
//----------------------------------------------------------
/**
 * @brief	�Ď��^�g�s�b�N�����f�[�^��Alloc
 * @param	sv
 * @param	headID
 * @param	size
 */
//----------------------------------------------------------
SEND_TOPIC * TVWORK_AllocSendWatchData(SAVEDATA * sv, int headID, u32 size)
{
	SEND_TOPIC * buf;
	TV_WORK * tvwk;
	buf = sys_AllocMemoryLo(headID, size);
	tvwk = SaveData_GetTvWork(sv);
	GF_ASSERT(size == TVWORK_GetSendWatchDataSize(sv));
	MakeSendTopicByMyTopic(sv, buf, tvwk->MyWatchTopic, MY_WATCH_MAX);
	return buf;
}
//----------------------------------------------------------
/**
 * @brief	�M�l�X�^�g�s�b�N�����f�[�^��Alloc
 * @param	sv
 * @param	headID
 * @param	size
 */
//----------------------------------------------------------
SEND_TOPIC * TVWORK_AllocSendRecordData(SAVEDATA * sv, int headID, u32 size)
{
	SEND_TOPIC * buf;
	TV_WORK * tvwk;
	buf = sys_AllocMemoryLo(headID, size);
	tvwk = SaveData_GetTvWork(sv);
	GF_ASSERT(size == TVWORK_GetSendRecordDataSize(sv));
	MakeSendTopicByMyTopic(sv, buf, tvwk->MyRecordTopic, MY_RECORD_MAX);
	return buf;
}


//============================================================================================
//
//
//			��M�f�[�^����
//
//
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	��M�g�s�b�N�𑼐l�g�s�b�N�̈�ɃZ�b�g����
 * @param	ot			���l�g�s�b�N�̈�ւ̃|�C���^
 * @param	max			���l�g�s�b�N�̈�̃T�C�Y
 * @param	st			��M�g�s�b�N�f�[�^
 * @retval	TRUE		�V���ɃZ�b�g����
 * @retval	FALSE		�Z�b�g���Ȃ�����
 */
//----------------------------------------------------------
static BOOL AddOtherTopic(OTHER_TOPIC * ot, int max, const SEND_TOPIC * st)
{
	int i;
	if (st->topic.topic_id == 0) {
		DEBUG_PRT_TAMADA("NULL topic tr_id=%d\n",st->owner_id & 0xffff);
		//��̃g�s�b�N�f�[�^�������ꍇ
		return FALSE;
	}
	for (i = 0; i < max; i++) {
		if (ot[i].topic.topic_id == 0) {
			DEBUG_PRT_TAMADA("SET! pos=%d topic=%d tr_id=%d\n",i, st->topic.topic_id, st->owner_id & 0xffff);
			ot[i] = *st;
			return TRUE;
		}
	}
	for (i = 0; i < max; i++) {
		if (ot[i].topic.see_count >= BROADCAST_MAX) {
			DEBUG_PRT_TAMADA("SET! pos=%d topic=%d tr_id=%d\n",i, st->topic.topic_id, st->owner_id & 0xffff);
			ot[i] = *st;
			return TRUE;
		}
	}
	return FALSE;
}
//----------------------------------------------------------
/**
 * @brief	�e���r��M�f�[�^�܂��鏈���{��
 * @param	ot			���l�g�s�b�N�̈�ւ̃|�C���^
 * @param	max			���l�g�s�b�N�̈�̃T�C�Y
 * @param	member		�ʐM�l��
 * @param	my_id		�����̒ʐMID
 * @param	darray		��M�f�[�^�ւ̃|�C���^�̔z��ւ̃|�C���^
 */
//----------------------------------------------------------
static void MixRecvData(OTHER_TOPIC * ot, int max, int member, int my_id, const void ** darray)
{
	u8 count[TV_COMM_MEMBER_MAX];
	int pos, i, j;
	DEBUG_PRT_TAMADA("OT=%08x max=%2d my_id=%5d\n", ot, max, my_id);
	for (i = 0; i < member; i++) {
		DEBUG_PRT_TAMADA("ID[%d]%08x\n", i, darray[i]);
	}

	MI_CpuClear8(count, TV_COMM_MEMBER_MAX);

	pos = 0;
	for (i = 0; i < member; i++) {
		if (darray[i] == NULL) { continue; }//���Ȃ��ꍇ�͎��̐l��
		for (j = 0; j < TV_RECV_MAX; j ++) {
			while (darray[pos] == NULL || pos == i || count[pos] == TV_RECV_MAX) {
				//���Ȃ��l�Ǝ����Ƃ��łɂ��炢�����̐l�̓p�X
				pos ++;
				pos %= member;
			}
			count[pos] ++;
			DEBUG_PRT_TAMADA(" %d[%d]->%d[%d]",i,j, pos, count[pos]);
			if (pos != my_id) {
				//�l�̃f�[�^�̏ꍇ�A�ǉ�����
				AddOtherTopic(ot, max, &((SEND_TOPIC *)darray[pos])[j]);
			}
		}
		DEBUG_PRT_TAMADA("\n");
	}
}

//----------------------------------------------------------
/**
 * @brief	�e���r�p�f�[�^�����鏈���i�Ď��^�j
 * @param	tvwk			�e���r�f�[�^�ւ̃|�C���^
 * @param	member		�ʐM�l��
 * @param	my_id		�����̒ʐMID
 * @param	darray		��M�f�[�^�ւ̃|�C���^�̔z��ւ̃|�C���^
 *
 */
//----------------------------------------------------------
void TVWORK_MixWatchData(TV_WORK * tv, int member, int my_id, const void ** darray)
{
	MixRecvData(tv->OtherWatchTopic, OTHER_WATCH_MAX, member, my_id, darray);
}

//----------------------------------------------------------
/**
 * @brief	�e���r�p�f�[�^�����鏈���i����^�j
 * @param	tvwk			�e���r�f�[�^�ւ̃|�C���^
 * @param	member		�ʐM�l��
 * @param	my_id		�����̒ʐMID
 * @param	darray		��M�f�[�^�ւ̃|�C���^�̔z��ւ̃|�C���^
 *
 */
//----------------------------------------------------------
void TVWORK_MixRecordData(TV_WORK * tv, int member, int my_id, const void ** darray)
{
	MixRecvData(tv->OtherRecordTopic, OTHER_RECORD_MAX, member, my_id, darray);
}

//----------------------------------------------------------
/**
 * @brief	�e���r�p�f�[�^�܂��鏈���i����^�j
 * @param	tvwk			�e���r�f�[�^�ւ̃|�C���^
 * @param	member		�ʐM�l��
 * @param	my_id		�����̒ʐMID
 * @param	darray		��M�f�[�^�ւ̃|�C���^�̔z��ւ̃|�C���^
 *
 */
//----------------------------------------------------------
void TVWORK_MixQandAData(TV_WORK * tv, int member, int my_id, const void ** darray)
{
	MixRecvData(tv->OtherQandATopic, OTHER_QANDA_MAX, member, my_id, darray);
}

