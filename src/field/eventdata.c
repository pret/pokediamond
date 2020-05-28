//============================================================================================
/**
 * @file	eventdata.c
 * @brief	�]�[�����ɓǂݍ��ރC�x���g�f�[�^�̏���
 * @author	tamada	GAME FREAK Inc.
 * @date	2005.10.17
 */
//============================================================================================

#include "common.h"
#include "mapdefine.h"

#include "fieldsys.h"

#include "zonedata.h"

#include "fieldobj.h"

#include "system/arc_tool.h"

#include "eventdata.h"

#include "encount_dat.h"

//===========================================================================
//===========================================================================
//------------------------------------------------------------------
/**
 * @brief	�]�[�����̃C�x���g�f�[�^�\��
 *
 * �]�[�����ɐ�������đg�ݍ��܂��C�x���g�f�[�^�o�C�i����
 * ��͂��Ă��̍\���̂ɒl������B
 */
//------------------------------------------------------------------
struct EVENT_DATA{
	u32 bg_count;
	u32 npc_count;
	u32 connect_count;
	u32 posevent_count;
	const BG_TALK_DATA * bg_data;
	const struct _TAG_FIELD_OBJ_H * npc_data;
	const CONNECT_DATA * connect_data;
	const POS_EVENT_DATA * posevent_data;
	u32 buffer[0x800 / sizeof(u32)];
	u32 sp_scr[0x100 / sizeof(u32)];
	ENCOUNT_DATA enc_work;
};


//------------------------------------------------------------------
//------------------------------------------------------------------

static void LoadEventData(EVENT_DATA * eventdata, int zone_id);
static void MakeEventData(EVENT_DATA * event_data);
static void LoadSpecialScriptData(EVENT_DATA * eventdata, int zone_id);
//===========================================================================
//===========================================================================
//------------------------------------------------------------------
/**
 * @brief	�C�x���g�f�[�^�F��������
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 */
//------------------------------------------------------------------
void EventData_Sys_Create(FIELDSYS_WORK * fsys, int heapID)
{
	EVENT_DATA * eventdata;
	GF_ASSERT(fsys->eventdata == NULL);
	fsys->eventdata = sys_AllocMemory(heapID, sizeof(EVENT_DATA));
}

//------------------------------------------------------------------
/**
 * @brief	�C�x���g�f�[�^�F��������
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 */
//------------------------------------------------------------------
void EventData_Sys_Delete(FIELDSYS_WORK * fsys)
{
	GF_ASSERT(fsys->eventdata != NULL);
	sys_FreeMemoryEz(fsys->eventdata);
}

//===========================================================================
//===========================================================================
//------------------------------------------------------------------
/**
 * @brief	�]�[�����Ƃ̃C�x���g�f�[�^�ǂݍ���
 * @param	zone_id		�]�[��ID�̎w��
 *
 * �]�[�����Ƃ̃C�x���g�f�[�^�o�C�i����ǂݍ���ŃC�x���g�f�[�^�\���̂�
 * ��������
 */
//------------------------------------------------------------------
void EventData_LoadZoneData(FIELDSYS_WORK * fsys, int zone_id)
{
	GF_ASSERT(fsys->eventdata != NULL);
	LoadEventData(fsys->eventdata, zone_id);
	MakeEventData(fsys->eventdata);
	EventData_LoadEncountData(&fsys->eventdata->enc_work, zone_id);
	LoadSpecialScriptData(fsys->eventdata, zone_id);
}

//------------------------------------------------------------------
//------------------------------------------------------------------
static void LoadEventData(EVENT_DATA * eventdata, int zone_id)
{
	int index;
	index = ZoneData_GetEventID(zone_id);
	GF_ASSERT(ArchiveDataSizeGet(ARC_EVENTDATA, index) < sizeof(eventdata->buffer));
	ArchiveDataLoad(eventdata->buffer, ARC_EVENTDATA, index);
}

//===========================================================================
//===========================================================================
//------------------------------------------------------------------
/**
 * @brief	�t�B�[���hNPC�̃Z�b�g
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 */
//------------------------------------------------------------------
void EventData_SetFieldOBJ(FIELDSYS_WORK * fsys)
{
	int num = fsys->eventdata->npc_count;
	GF_ASSERT(fsys->eventdata != NULL);
	if (num != 0) {
		FieldOBJ_AddBin(fsys->fldobjsys, fsys->location->zone_id, num, fsys->eventdata->npc_data);
	}
}

//------------------------------------------------------------------
/**
 * @brief	BG�b�������C�x���g�f�[�^�̎擾
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @return	�f�[�^�擪�ւ̃|�C���^
 */
//------------------------------------------------------------------
const BG_TALK_DATA * EventData_GetNowBgTalkData(const FIELDSYS_WORK * fsys)
{
	return fsys->eventdata->bg_data;
}
//------------------------------------------------------------------
/**
 * @brief	BG�b�������C�x���g�f�[�^���̎擾
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @return	�f�[�^��
 */
//------------------------------------------------------------------
int EventData_GetNowBgTalkDataSize(const FIELDSYS_WORK * fsys)
{
	return fsys->eventdata->bg_count;
}

//------------------------------------------------------------------
/**
 * @brief	�}�b�v�ڑ��f�[�^���̎擾
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @return	�f�[�^��
 */
//------------------------------------------------------------------
int EventData_GetNowConnectDataSize(const FIELDSYS_WORK * fsys)
{
	return fsys->eventdata->connect_count;
}
//------------------------------------------------------------------
/**
 * @brief	�}�b�v�ڑ��f�[�^�̎擾
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	id		�o�����ID
 * @retval	NULL�ȊO	�w�肵���f�[�^�ւ̃|�C���^
 * @retval	NULL		�f�[�^�����݂��Ȃ�
 */
//------------------------------------------------------------------
const CONNECT_DATA * EventData_GetNowConnectDataByID(const FIELDSYS_WORK * fsys, int door_id)
{
	if (door_id >= fsys->eventdata->connect_count) {
		OS_Printf("door_id error\n");
		return NULL;
	}
	return &fsys->eventdata->connect_data[door_id];
}
//------------------------------------------------------------------
/**
 * @brief	�}�b�v�ڑ��f�[�^ID�̎擾
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	x		�T��X�ʒu�i�O���b�h�P�ʁj
 * @param	z		�T��Z�ʒu�i�O���b�h�P�ʁj
 * @return	int	�o����ID
 * @return	-1	�o���������݂��Ȃ������ꍇ
 */
//------------------------------------------------------------------
int EventData_SearchNowConnectIDByXZ(const FIELDSYS_WORK * fsys, int x, int z)
{
	int door_id;

	for (door_id = 0; door_id < fsys->eventdata->connect_count; door_id ++) {
		if (fsys->eventdata->connect_data[door_id].x == x &&
			fsys->eventdata->connect_data[door_id].z == z) {
			return door_id;
		}
	}
	return -1;
}

//------------------------------------------------------------------
/**
 * @brief	POS�����C�x���g�̃f�[�^���擾
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @return	POS�����C�x���g�̃f�[�^��
 */
//------------------------------------------------------------------
int EventData_GetNowPosEventDataSize(const FIELDSYS_WORK * fsys)
{
	return fsys->eventdata->posevent_count;
}
//------------------------------------------------------------------
/**
 * @brief	POS�����C�x���g�̃f�[�^�擾
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @return	�f�[�^�擪�ւ̃|�C���^
 */
//------------------------------------------------------------------
const POS_EVENT_DATA * EventData_GetNowPosEventData(const FIELDSYS_WORK * fsys)
{
	return fsys->eventdata->posevent_data;
}

//------------------------------------------------------------------
/**
 * @brief	npc_count�擾
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @return	"npc_count"
 */
//------------------------------------------------------------------
u32 EventData_GetNpcCount(const FIELDSYS_WORK * fsys)
{
	return fsys->eventdata->npc_count;
}

//------------------------------------------------------------------
/**
 * @brief	npc_data�擾
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @return	"npc_data"
 */
//------------------------------------------------------------------
const FIELD_OBJ_H* EventData_GetNpcData(const FIELDSYS_WORK * fsys)
{
	return fsys->eventdata->npc_data;
}

//------------------------------------------------------------------
/**
 * @brief	npc_data�̍��W������������
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	id		��������ID
 * @param	gx		�O���b�hX
 * @param	gz		�O���b�hZ
 * @return	"TRUE=�����AFALSE=���s"
 */
//------------------------------------------------------------------
BOOL EventData_NpcDataPosChange(FIELDSYS_WORK * fsys, int id, u16 gx, u16 gz )
{
	int i;
	FIELD_OBJ_H* p	= (FIELD_OBJ_H*)fsys->eventdata->npc_data;
	u32 max			= fsys->eventdata->npc_count;

	for( i=0; i < max ;i++ ){
		if( p[i].id == id ){		//����ID������
			p[i].gx = gx;
			p[i].gz = gz;
			return TRUE;
		}
	}

	GF_ASSERT( (0) && "����ID��������܂���ł����I" );
	return FALSE;
}

//------------------------------------------------------------------
/**
 * @brief	npc_data�̕���������������
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	id		��������ID
 * @param	dir		����
 * @return	"TRUE=�����AFALSE=���s"
 */
//------------------------------------------------------------------
BOOL EventData_NpcDataDirChange(FIELDSYS_WORK * fsys, int id, int dir );
BOOL EventData_NpcDataDirChange(FIELDSYS_WORK * fsys, int id, int dir )
{
	int i;
	FIELD_OBJ_H* p	= (FIELD_OBJ_H*)fsys->eventdata->npc_data;
	u32 max			= fsys->eventdata->npc_count;

	for( i=0; i < max ;i++ ){
		if( p[i].id == id ){		//����ID������
			p[i].dir = dir;
			return TRUE;
		}
	}

	GF_ASSERT( (0) && "����ID��������܂���ł����I" );
	return FALSE;
}

//------------------------------------------------------------------
/**
 * @brief	npc_data�̓���R�[�h������������
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	id		��������ID
 * @param	mv		����R�[�h
 * @return	"TRUE=�����AFALSE=���s"
 */
//------------------------------------------------------------------
BOOL EventData_NpcDataMoveCodeChange(FIELDSYS_WORK * fsys, int id, int mv );
BOOL EventData_NpcDataMoveCodeChange(FIELDSYS_WORK * fsys, int id, int mv )
{
	int i;
	FIELD_OBJ_H* p	= (FIELD_OBJ_H*)fsys->eventdata->npc_data;
	u32 max			= fsys->eventdata->npc_count;

	for( i=0; i < max ;i++ ){
		if( p[i].id == id ){		//����ID������
			p[i].move_code =mv;
			return TRUE;
		}
	}

	GF_ASSERT( (0) && "����ID��������܂���ł����I" );
	return FALSE;
}

//------------------------------------------------------------------
/**
 * @brief	connect_data�̍��W������������
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	id		��������ID
 * @param	x		�Z�b�g����X
 * @param	z		�Z�b�g����Z
 * @return	"TRUE=�����AFALSE=���s"
 */
//------------------------------------------------------------------
BOOL EventData_ConnectDataPosChange(FIELDSYS_WORK * fsys, u16 id, u16 x, u16 z );
BOOL EventData_ConnectDataPosChange(FIELDSYS_WORK * fsys, u16 id, u16 x, u16 z )
{
	CONNECT_DATA* p	= (CONNECT_DATA*)fsys->eventdata->connect_data;
	//OS_Printf( "�ύX�O x = %d\n", p[id].x );
	//OS_Printf( "�ύX�O z = %d\n", p[id].z );
	p[id].x			= x;
	p[id].z			= z;
	//OS_Printf( "�ύX�� x = %d\n", p[id].x );
	//OS_Printf( "�ύX�� z = %d\n", p[id].z );
	return TRUE;
}

//------------------------------------------------------------------
/**
 * @brief	connect_data�̐ڑ���]�[��ID������������
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	id		��������ID
 * @param	zone	�Z�b�g����]�[��
 * @return	"TRUE=�����AFALSE=���s"
 */
//------------------------------------------------------------------
BOOL EventData_ConnectDataZoneChange(FIELDSYS_WORK * fsys, u16 id, u16 zone );
BOOL EventData_ConnectDataZoneChange(FIELDSYS_WORK * fsys, u16 id, u16 zone)
{
	CONNECT_DATA* p	= (CONNECT_DATA*)fsys->eventdata->connect_data;
	
	p[id].link_zone_id	= zone;
	return TRUE;
}
//------------------------------------------------------------------
/**
 * @brief	bg_data�̍��W������������
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	id		��������ID
 * @param	x		�Z�b�g����X
 * @param	z		�Z�b�g����Z
 * @return	"TRUE=�����AFALSE=���s"
 */
//------------------------------------------------------------------
BOOL EventData_BgDataPosChange(FIELDSYS_WORK * fsys, u16 id, u16 x, u16 z );
BOOL EventData_BgDataPosChange(FIELDSYS_WORK * fsys, u16 id, u16 x, u16 z )
{
	BG_TALK_DATA* p = (BG_TALK_DATA*)EventData_GetNowBgTalkData( fsys );

	//OS_Printf( "�ύX�O p = %d\n", p );
	//OS_Printf( "�ύX�O x = %d\n", p->gx );
	//OS_Printf( "�ύX�O x = %d\n", p->gz );
	(p)+=id;
	p->gx = x;
	p->gz = z;
	//OS_Printf( "�ύX�� p = %d\n", p );
	//OS_Printf( "�ύX�� x = %d\n", p->gx );
	//OS_Printf( "�ύX�� x = %d\n", p->gz );
	return TRUE;
}

//------------------------------------------------------------------
/**
 * @brief	�C�x���g�f�[�^��������
 * @param	event_data	EVENT_DATA�\���̂ւ̃|�C���^
 *
 * EVENT_DATA::buffer�ɓǂݍ��܂�Ă���o�C�i���f�[�^��
 * ��͂���EVENT_DATA�\���̂̂ق��̃����o�[�𐶐�����B
 */
//------------------------------------------------------------------
static void MakeEventData(EVENT_DATA * event_data)
{
	const u8 * buffer = (const u8 *)event_data->buffer;

	//BG�b�������C�x���g�f�[�^�ǂݍ���
	event_data->bg_count = *(u32 *)buffer;
	buffer += sizeof(u32);
	if (event_data->bg_count != 0) {
		event_data->bg_data = (const BG_TALK_DATA *)buffer;
	} else {
		event_data->bg_data = NULL;
	}
	buffer += sizeof(BG_TALK_DATA) * event_data->bg_count;

	//NPC�z�u�f�[�^�ǂݍ���
	event_data->npc_count = *(u32 *)buffer;
	buffer += sizeof(u32);
	if (event_data->npc_count != 0) {
		event_data->npc_data = (const struct _TAG_FIELD_OBJ_H *)buffer;
	} else {
		event_data->npc_data = NULL;
	}
	buffer += sizeof(struct _TAG_FIELD_OBJ_H) * event_data->npc_count;

	//�}�b�v�ڑ��f�[�^�ǂݍ���
	event_data->connect_count = *(u32 *)buffer;
	buffer += sizeof(u32);
	if (event_data->connect_count != 0) {
		event_data->connect_data = (const CONNECT_DATA *)buffer;
	} else {
		event_data->connect_data = NULL;
	}
	buffer += sizeof(CONNECT_DATA) * event_data->connect_count;

	//POS�����C�x���g�f�[�^�ǂݍ���
	event_data->posevent_count = *(u32 *)buffer;
	buffer += sizeof(u32);
	if (event_data->posevent_count != 0) {
		event_data->posevent_data = (const POS_EVENT_DATA *)buffer;
	} else {
		event_data->posevent_data = NULL;
	}
	buffer += sizeof(POS_EVENT_DATA) * event_data->posevent_count;

}

//===========================================================================
//===========================================================================
//------------------------------------------------------------------
/**
 * @brief	�]�[�����̃G���J�E���g�f�[�^�̓ǂݍ���
 * @param	zone_id		�]�[��ID�̎w��
 * @param	event_data	EVENT_DATA�\���̂ւ̃|�C���^
 */
//------------------------------------------------------------------
void EventData_LoadEncountData(ENCOUNT_DATA *enc_data, int zone_id)
{
	int arc_version;
	memset(enc_data, 0, sizeof(ENCOUNT_DATA));
	if (ZoneData_GetEncountFlag(zone_id)) {
		if (PM_VERSION == VERSION_DIAMOND){
			arc_version = ARC_D_ENCOUNT;
		}else{
			arc_version = ARC_P_ENCOUNT;
		}
		ArchiveDataLoad(enc_data, arc_version,
				ZoneData_GetEncountArchiveID(zone_id));
	}
}

//------------------------------------------------------------------
/**
 * @brief	�G���J�E���g�f�[�^�̎擾
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @return	ENCOUNT_DATA * �G���J�E���g�f�[�^�̐擪�A�h���X
 *
 * 
 * 
 */
//------------------------------------------------------------------
const ENCOUNT_DATA * EventData_GetEncountData(const FIELDSYS_WORK * fsys)
{
	return &fsys->eventdata->enc_work;
}

//===========================================================================
//===========================================================================
//------------------------------------------------------------------
/**
 * @brief	�]�[�����̓���X�N���v�g�f�[�^�̓ǂݍ���
 * @param	zone_id		�]�[��ID�̎w��
 * @param	event_data	EVENT_DATA�\���̂ւ̃|�C���^
 */
//------------------------------------------------------------------
static void LoadSpecialScriptData(EVENT_DATA * eventdata, int zone_id)
{
	int index;
	index = ZoneData_GetSpScriptArchiveID(zone_id);
	MI_CpuClearFast(eventdata->sp_scr, sizeof(eventdata->sp_scr));
	GF_ASSERT(ArchiveDataSizeGet(ARC_SCRIPT, index) < sizeof(eventdata->sp_scr));
	ArchiveDataLoad(eventdata->sp_scr, ARC_SCRIPT, index);
}

//------------------------------------------------------------------
/**
 * @brief	����X�N���v�g�f�[�^�̎擾
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @return	void * ����X�N���v�g�f�[�^�̐擪�A�h���X
 *
 */
//------------------------------------------------------------------
void * EventData_GetSpecialScript(const FIELDSYS_WORK * fsys)
{
	GF_ASSERT(fsys->eventdata != NULL);
	return &fsys->eventdata->sp_scr;
}


//------------------------------------------------------------------
/**
 * �n���ɐ��邱�Ƃ��o������W���ǂ������`�F�b�N
 *
 * @param   fsys		�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param   gx			�`�F�b�N����w���W
 * @param   gz			�`�F�b�N����y���W
 *
 * @retval  BOOL		"TRUE=���邱�Ƃ��ł��� FALSE=�ł��Ȃ�"
 */
//------------------------------------------------------------------
BOOL EventData_CheckIntoUGPos( const FIELDSYS_WORK* fsys, u16 gx, u16 gz )
{
	const EVENT_DATA* eventdata = fsys->eventdata;
	u32 i;

	for(i=0; i<eventdata->npc_count; i++)
	{
		if( (eventdata->npc_data[i].gx == gx)
		&&	(eventdata->npc_data[i].gz == gz)
		){
			return FALSE;
		}
	}
	return TRUE;
}

