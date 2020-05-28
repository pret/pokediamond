//============================================================================================
/**
 * @file	eventdata.h
 * @brief	�C�x���g�N���`�F�b�N�p�f�[�^��`�w�b�_
 * @date	2005.10.14
 *
 * 2005.10.18	check_data.h-->eventdata.h�Ƀ��l�[������
 */
//============================================================================================
#ifndef	__EVENTDATA_H__
#define	__EVENTDATA_H__

#include "check_data.h"
#include "encount_dat.h"

extern void EventData_Sys_Create(FIELDSYS_WORK * fsys, int heapID);
extern void EventData_Sys_Delete(FIELDSYS_WORK * fsys);

extern const BG_TALK_DATA * EventData_GetNowBgTalkData(const FIELDSYS_WORK * fsys);
extern int EventData_GetNowBgTalkDataSize(const FIELDSYS_WORK * fsys);
extern int EventData_GetNowConnectDataSize(const FIELDSYS_WORK * fsys);
extern int EventData_SearchNowConnectIDByXZ(const FIELDSYS_WORK * fsys, int x, int z);
extern const CONNECT_DATA * EventData_GetNowConnectDataByID(const FIELDSYS_WORK * fsys, int door_id);
extern int EventData_GetNowPosEventDataSize(const FIELDSYS_WORK * fsys);
extern const POS_EVENT_DATA * EventData_GetNowPosEventData(const FIELDSYS_WORK * fsys);
extern void EventData_LoadEncountData(ENCOUNT_DATA *enc_data, int zone_id);
//------------------------------------------------------------------
/**
 * @brief	npc_count�擾
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @return	"npc_count"
 */
//------------------------------------------------------------------
extern u32 EventData_GetNpcCount(const FIELDSYS_WORK * fsys);

//------------------------------------------------------------------
/**
 * @brief	npc_data�擾
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @return	"npc_data"
 */
//------------------------------------------------------------------
extern const FIELD_OBJ_H* EventData_GetNpcData(const FIELDSYS_WORK * fsys);

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
extern BOOL EventData_NpcDataPosChange(FIELDSYS_WORK * fsys, int id, u16 gx, u16 gz );

//------------------------------------------------------------------
/**
 * @brief	npc_data�̕���������������
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	id		��������ID
 * @param	dir		����
 * @return	"TRUE=�����AFALSE=���s"
 */
//------------------------------------------------------------------
extern BOOL EventData_NpcDataDirChange(FIELDSYS_WORK * fsys, int id, int dir );

//------------------------------------------------------------------
/**
 * @brief	npc_data�̓���R�[�h������������
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	id		��������ID
 * @param	mv		����R�[�h
 * @return	"TRUE=�����AFALSE=���s"
 */
//------------------------------------------------------------------
extern BOOL EventData_NpcDataMoveCodeChange(FIELDSYS_WORK * fsys, int id, int mv );

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
extern BOOL EventData_ConnectDataPosChange(FIELDSYS_WORK * fsys, u16 id, u16 x, u16 z );

//------------------------------------------------------------------
/**
 * @brief	connect_data�̐ڑ���]�[��ID������������
 * @param	fsys	�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	id		��������ID
 * @param	zone	�Z�b�g����]�[��
 * @return	"TRUE=�����AFALSE=���s"
 */
//------------------------------------------------------------------
extern BOOL EventData_ConnectDataZoneChange(FIELDSYS_WORK * fsys, u16 id, u16 zone );

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
extern BOOL EventData_BgDataPosChange(FIELDSYS_WORK * fsys, u16 id, u16 x, u16 z );

extern void EventData_LoadZoneData(FIELDSYS_WORK * fsys, int zone_id);
extern void EventData_SetFieldOBJ(FIELDSYS_WORK * fsys);

extern const ENCOUNT_DATA * EventData_GetEncountData(const FIELDSYS_WORK * fsys);
extern void * EventData_GetSpecialScript(const FIELDSYS_WORK * fsys);

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
extern BOOL EventData_CheckIntoUGPos( const FIELDSYS_WORK* fsys, u16 gx, u16 gz );


#endif	/*	__EVENTDATA_H__ */
