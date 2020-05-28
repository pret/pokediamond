//============================================================================================
/**
 * @file	situation.c
 * @brief	�󋵃f�[�^�A�N�Z�X
 * @author	tamada GAME FREAK inc.
 * @date	2005.12.03
 */
//============================================================================================

#include "common.h"
#include "system/savedata_def.h"	//SAVEDATA�Q�Ƃ̂���
#include "fieldsys.h"
#include "field/situation.h"
#include "townmap_footmark.h"

#include "system/savedata.h"

#include "situation_local.h"


#include "fieldobj_header.h"

#include "mapdata_warp.h"

//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	�󋵃f�[�^�^��`
 */
//----------------------------------------------------------
struct _SITUATION {
	LOCATION_WORK now;
	LOCATION_WORK entrance;
	LOCATION_WORK before;
	LOCATION_WORK special;
	LOCATION_WORK escape;
	//LOCATION_WORK teleport;
	u16 bgm;
	u16 weather_id;
	u16 warp_id;
	u8 camera_id;
	TOWN_MAP_FOOTMARK TownMapFootMark;
	PLAYER_SAVE_DATA	player_sv;

	u16 poison_step_count;
	u16 safari_step_count;
	u16 safari_ball_count;
	u16 friendly_step_count;
	u16 revenge_step_count;
};

//----------------------------------------------------------
//----------------------------------------------------------
struct _FIELDOBJ_SAVE{
	FIELD_OBJ_SAVE_DATA fldobj_sv[FLDOBJ_ENTRY_MAX];
};

//============================================================================================
//
//	�Z�[�u�f�[�^�V�X�e�����ˑ�����֐�
//
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	�󋵃��[�N�̃T�C�Y�擾
 * @return	int		�T�C�Y�i�o�C�g�P�ʁj
 */
//----------------------------------------------------------
int Situation_GetWorkSize(void)
{
	return sizeof(SITUATION);
}

//----------------------------------------------------------
//----------------------------------------------------------
int FieldObjSv_GetWorkSize(void)
{
	return sizeof(FIELDOBJ_SAVE);
}

//----------------------------------------------------------
//----------------------------------------------------------
void FieldObjSv_Init(FIELDOBJ_SAVE * sv)
{
	MI_CpuClear32(sv, sizeof(FIELDOBJ_SAVE));
}

//============================================================================================
//
//	�󋵃f�[�^����̂��߂̊֐�
//
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	�󋵃f�[�^�̏�����
 * @param	st	�󋵃��[�N�ւ̃|�C���^
 */
//----------------------------------------------------------
void Situation_Init(SITUATION * st)
{
	memset(st, 0, sizeof(SITUATION));
	TMFootMark_Init(&st->TownMapFootMark);
	Player_SaveDataInit(&st->player_sv);
	st->warp_id = WARPDATA_GetInitializeID();
}

//----------------------------------------------------------
/**
 * @brief	���݂�LOCATION_WORK��Ԃ�
 * @param	st	�󋵃��[�N�ւ̃|�C���^
 * @return	LOCATION_WORK�ւ̃|�C���^
 */
//----------------------------------------------------------
LOCATION_WORK * Situation_GetNowLocation(SITUATION * st)
{
	return &st->now;
}

//----------------------------------------------------------
/**
 * @brief	���O�ɓ������o����������LOCATION_WORK�ւ̃|�C���^
 * @param	st	�󋵃��[�N�ւ̃|�C���^
 * @return	LOCATION_WORK�ւ̃|�C���^
 */
//----------------------------------------------------------
LOCATION_WORK * Situation_GetEntranceLocation(SITUATION * st)
{
	return &st->entrance;
}

//----------------------------------------------------------
/**
 * @param	st	�󋵃��[�N�ւ̃|�C���^
 */
//----------------------------------------------------------
LOCATION_WORK * Situation_GetBeforeLocation(SITUATION * st)
{
	return &st->before;
}

//----------------------------------------------------------
/**
 * @param	st	�󋵃��[�N�ւ̃|�C���^
 */
//----------------------------------------------------------
LOCATION_WORK * Situation_GetEscapeLocation(SITUATION * st)
{
	return &st->escape;
}
//----------------------------------------------------------
/**
 * @brief	����ڑ����̎擾
 * @param	st	�󋵃��[�N�ւ̃|�C���^
 * @return	LOCATION_WORK	����ڑ����ւ̃|�C���^
 */
//----------------------------------------------------------
LOCATION_WORK * Situation_GetSpecialLocation(SITUATION * st)
{
	return &st->special;
}

//----------------------------------------------------------
/**
 * @brief	����ڑ����̃Z�b�g
 * @param	st	�󋵃��[�N�ւ̃|�C���^
 * @param	sp	LOCATION_WORK�f�[�^�̃|�C���^
 * @return	none
 */
//----------------------------------------------------------
void Situation_SetSpecialLocation(SITUATION * st, LOCATION_WORK* lw)
{
	st->special = *lw;
	return;
}

//----------------------------------------------------------
/**
 * @brief	BGMID�A�N�Z�X
 * @param	st	�󋵃��[�N�ւ̃|�C���^
 * @param	u16	BGMID�ւ̃|�C���^
 */
//----------------------------------------------------------
u16 * Situation_GetBGMWork(SITUATION * st)
{
	return &st->bgm;
}

//----------------------------------------------------------
/**
 * @brief	�V��ID�擾
 * @param	st	�󋵃��[�N�ւ̃|�C���^
 * @return	u16	�V��ID�ւ̃|�C���^
 */
//----------------------------------------------------------
u16 Situation_GetWeatherID(const SITUATION * st)
{
	return st->weather_id;
}

//----------------------------------------------------------
/**
 * @brief	�V��ID�Z�b�g
 * @param	st	�󋵃��[�N�ւ̃|�C���^
 * @param	weather_id	�V��ID
 */
//----------------------------------------------------------
void Situation_SetWeatherID(SITUATION * st, u16 weather_id)
{
	st->weather_id = weather_id;
}

//----------------------------------------------------------
/**
 * @brief	���[�vID�̎擾
 * @param	st	�󋵃��[�N�ւ̃|�C���^
 * @return	u16	���[�vID
 */
//----------------------------------------------------------
u16 Situation_GetWarpID(const SITUATION * st)
{
	return st->warp_id;
}
//----------------------------------------------------------
/**
 * @brief	���[�vID�̐ݒ�
 * @param	st		�󋵃��[�N�ւ̃|�C���^
 * @param	warp_id	���[�vID
 */
//----------------------------------------------------------
void Situation_SetWarpID(SITUATION * st, u16 warp_id)
{
	st->warp_id = warp_id;
}

//----------------------------------------------------------
/**
 * @param	st	�󋵃��[�N�ւ̃|�C���^
 */
//----------------------------------------------------------
TOWN_MAP_FOOTMARK * Situation_GetTMFootMark(SITUATION * st)
{
	return &st->TownMapFootMark;
}

//----------------------------------------------------------
/**
 * @brief	�J�����w��ID�̎擾
 * @param	st	�󋵃��[�N�ւ̃|�C���^
 * @return	int �J�����w���ID
 */
//----------------------------------------------------------
int Situation_GetCameraID(const SITUATION * st)
{
	return st->camera_id;
}

//----------------------------------------------------------
/**
 * @brief	�J�����w��ID�̃Z�b�g
 * @param	st	�󋵃��[�N�ւ̃|�C���^
 * @param	camera_id	�J�����w���ID
 */
//----------------------------------------------------------
void Situation_SetCameraID(SITUATION * st, int camera_id)
{
	st->camera_id = camera_id;
}

//----------------------------------------------------------
/**
 * @brief	���@�Z�[�u���擾
 * @param	st	�󋵃��[�N�ւ̃|�C���^
 * @return	PLAYER_SAVE_DATA�ւ̃|�C���^
 */
//----------------------------------------------------------
PLAYER_SAVE_DATA * Situation_GetPlayerSaveData(SITUATION * st)
{
	return &st->player_sv;
}


//----------------------------------------------------------
/**
 * @brief	�T�t�@���{�[�����[�N�擾
 * @param	st	�󋵃��[�N�ւ̃|�C���^
 * @return	u16	���[�N�ւ̃|�C���^
 */
//----------------------------------------------------------
u16 * Situation_GetSafariBallCount(SITUATION * st)
{
	return &st->safari_ball_count;
}

//----------------------------------------------------------
/**
 * @brief	�T�t�@���������[�N�擾
 * @param	st	�󋵃��[�N�ւ̃|�C���^
 * @return	u16	���[�N�ւ̃|�C���^
 */
//----------------------------------------------------------
u16 * Situation_GetSafariStepCount(SITUATION * st)
{
	return &st->safari_step_count;
}

//----------------------------------------------------------
/**
 * @brief	�Ń_���[�W�p�������[�N�擾
 * @param	st	�󋵃��[�N�ւ̃|�C���^
 * @return	u16	���[�N�ւ̃|�C���^
 */
//----------------------------------------------------------
u16 * Situation_GetPoisonStepCount(SITUATION * st)
{
	return &st->poison_step_count;
}

//----------------------------------------------------------
/**
 * @brief	�Đ�p�������[�N�擾
 * @param	st	�󋵃��[�N�ւ̃|�C���^
 * @return	u16	���[�N�ւ̃|�C���^
 */
//----------------------------------------------------------
u16 * Situation_GetRevengeStepCount(SITUATION * st)
{
	return &st->poison_step_count;
}

//----------------------------------------------------------
/**
 * @brief	�Đ�p�������[�N�擾
 * @param	st	�󋵃��[�N�ւ̃|�C���^
 * @return	u16	���[�N�ւ̃|�C���^
 */
//----------------------------------------------------------
u16 * Situation_GetFriendlyStepCount(SITUATION * st)
{
	return &st->friendly_step_count;
}

//============================================================================================
//
//	�Z�[�u�f�[�^�擾�̂��߂̊֐�
//
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	�󋵃f�[�^�ւ̃|�C���^�擾
 * @param	sv			�Z�[�u�f�[�^�ێ����[�N�ւ̃|�C���^
 * @return	SITUATION	�󋵕ێ����[�N�ւ̃|�C���^
 */
//----------------------------------------------------------
SITUATION * SaveData_GetSituation(SAVEDATA * sv)
{
		SITUATION * st;
		st = SaveData_Get(sv, GMDATA_ID_SITUATION);
		return st;
}

FIELDOBJ_SAVE * SaveData_GetFieldObjSv(SAVEDATA * sv)
{
	FIELDOBJ_SAVE * fld;
	fld = SaveData_Get(sv, GMDATA_ID_FIELDOBJSV);
	return fld;
}

#if 0
FIELDOBJ_SAVE * SaveData_GetFieldObjSv2(SAVEDATA * sv)
{
	FIELDOBJ_SAVE * fld;
	fld = SaveData_Get(sv, GMDATA_ID_FIELDOBJSV2);
	return fld;
}
#endif

//----------------------------------------------------------
/**
 * @brief	�t�B�[���hOBJ�̃Z�[�u
 * @param	fsys			�Q�[�����䃏�[�N�ւ̃|�C���^
 */
//----------------------------------------------------------
void Field_SaveFieldObj(FIELDSYS_WORK * fsys)
{
	FIELD_OBJ_SAVE_DATA * fldobjsv;
	fldobjsv = ((FIELDOBJ_SAVE *)SaveData_GetFieldObjSv(fsys->savedata))->fldobj_sv;
	FieldOBJSys_DataSaveAll(fsys, fsys->fldobjsys, fldobjsv, FLDOBJ_ENTRY_MAX);
}

//----------------------------------------------------------
/**
 * @brief	�t�B�[���hOBJ�̃��[�h
 * @param	fsys			�Q�[�����䃏�[�N�ւ̃|�C���^
 */
//----------------------------------------------------------
void Field_LoadFieldObj(FIELDSYS_WORK * fsys)
{
	FIELD_OBJ_SAVE_DATA * fldobjsv;
	fldobjsv = ((FIELDOBJ_SAVE *)SaveData_GetFieldObjSv(fsys->savedata))->fldobj_sv;
	FieldOBJSys_DataLoadAll(fsys->fldobjsys, fldobjsv, FLDOBJ_ENTRY_MAX);
}

//============================================================================================
//
//	�f�o�b�O�p
//
//============================================================================================
