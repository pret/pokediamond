//============================================================================================
/**
 * @file	ev_mapchange.c
 * @brief	�t�B�[���h�}�b�v�ؑւ̃C�x���g�Ƃ��̐����`�F�b�N
 * @date	2005.08.01
 * @author	tamada / saito
 */
//============================================================================================

#include "common.h"
#include "fieldsys.h"

#include "field_event.h"

#include "fieldmap.h"
#include "field/location.h"

#include "ev_mapchange.h"

#include "worldmap.h"

#include "zonedata.h"
#include "mapdefine.h"
#include "eventdata.h"		//�]�[�����̃C�x���g�f�[�^�Q�Ƃ̂���

#include "system/snd_tool.h"
#include "fld_bgm.h"
#include "system/brightness.h"
#include "system/pm_overlay.h"  // �n���ڑ��̂���
#include "comm_player.h"  // �n���ڑ��̂���
#include "communication/communication.h"
#include "../fielddata/script/common_scr_def.h"		//SCRID_REPORT

#include "map_tool.h"

#include "field_3d_anime_ev.h"

#include "system/wipe.h"
#include "field_cutin.h"
#include "field_ananuke.h"
#include "effect_warppoint.h"

//���n��
#include "effect_uground.h"
#include "comm_field_state.h"  // �n���ʐM�p
#include "underground/ug_manager.h"  // �n���p
//
#include "script.h"

#include "savedata/mystatus.h"	//MyStatus_GetMySex
#include "savedata/gimmickwork.h"
#include "savedata/undergrounddata.h"
#include "field/situation_local.h"	//Situation_GetTMFootMark
#include "townmap_footmark.h"		//TMFootMark_SetNoDir
#include "mapdata_warp.h"			//WARPDATA_SearchByRoomID
#include "field_subscreen.h"
#include "report.h"
#include "mapdata_weather.h"		//WeatherData_Get
#include "weather_sys.h"
#include "savedata/fnote_mem.h"		//FNOTE_DATA
#include "itemtool/itemsym.h"
#include "savedata/savedata.h"
#include "sysflag.h"
#include "syswork.h"
#include "ev_time.h"				//EVTIME_Update

#include "savedata/encount.h"
#include "fieldmap_mem.h"			//FIELD_HEIGHT_DATA_SIZE

#include "fld_flg_init.h"
#include "place_name.h"

#include "msgdata/msg.naix"
#include "msgdata/msg_connect.h"

#include "system/window.h"
#include "system/bmp_menu.h"
#include "talk_msg.h"
#include "fld_bmp.h"


FS_EXTERN_OVERLAY(ol_underground);

static BOOL GMEVENT_MapChange(GMEVENT_CONTROL * event);
static BOOL GMEVENT_FirstMapIn(GMEVENT_CONTROL * event);
static BOOL GMEVENT_FieldChange_FadeIn(GMEVENT_CONTROL * event);

static void MapChg_SetNewLocation(FIELDSYS_WORK * fsys, const LOCATION_WORK * next);
static void MapChg_SetupMapTools(FIELDSYS_WORK * fsys);
static void MapChg_RemoveMapTools(FIELDSYS_WORK * fsys);
static void MapChg_FieldOBJ_Create(FIELDSYS_WORK * fsys);
static void MapChg_FieldOBJ_Delete(FIELDSYS_WORK * fsys);

//============================================================================================
//============================================================================================
//-----------------------------------------------------------------------------
/**
 * @brief	�}�b�v�J�ڃC�x���g�p���䃏�[�N
 */
//-----------------------------------------------------------------------------
typedef struct {
	int seq;							///<�V�[�P���X�ێ����[�N
	LOCATION_WORK next;					///<�}�b�v�J�ڐ�w��p���[�N
	FLD_3D_ANIME_WORK_PTR DoorAnimeWork;
}EVENT_MAPCHG_WORK;

//-----------------------------------------------------------------------------
/**
 * @brief	�}�b�v�V�X�e���̏������p�����[�^
 */
//-----------------------------------------------------------------------------
static const MAP_MODE_DATA MapModeData[] = {
	///MAP_MODE_GROUND		�ʏ�t�B�[���h
	{
		FIELD_SUBSCRN_POKETCH,		//�T�u��ʁF�|�P�b�`
		DIV_MAP_MODE_GROUND,		//�}�b�v�����]���V�X�e���w��F�ʏ�
		MAP_TOOL_MODE_GROUND,		//�}�b�v�c�[���w��F�ʏ�
		DISP_3D_TO_MAIN,			//���ʂ�3D
		FALSE,						//����A�g���r���[�g�V�X�e���F�g��Ȃ�
		TRUE,						//�T�u�I�[�o�[���C�F�����ǂݍ���
		0,							//����A�g���r���[�g�p�ɕێ�����f�[�^��
		0xc4000,					//�t�B�[���h�Ŋm�ۂ���q�[�v�̃T�C�Y
	},
	///MAP_MODE_UNDER		�Y�z
	{
		FIELD_SUBSCRN_UNDER,		//�T�u��ʁF���[�_�[
		DIV_MAP_MODE_UNDER,			//�}�b�v�����]���V�X�e���w��F�n���p
		MAP_TOOL_MODE_UNDER,		//�}�b�v�c�[���w��F�n���p
		DISP_3D_TO_SUB,				//����ʂ�3D
		TRUE,						//����A�g���r���[�g�V�X�e���F�g��
		FALSE,						//�T�u�I�[�o�[���C�F�ǂݍ��܂Ȃ�
		16,							//����A�g���r���[�g�p�ɕێ�����f�[�^��
		0xc4000,					//�t�B�[���h�Ŋm�ۂ���q�[�v�̃T�C�Y
	},
	///MAP_MODE_UNION		���j�I�����[��
	{
		FIELD_SUBSCRN_UNION,		//�T�u��ʁF���j�I���{�[�h
		DIV_MAP_MODE_GROUND,		//�}�b�v�����]���V�X�e���w��F�ʏ�
		MAP_TOOL_MODE_GROUND,		//�}�b�v�c�[���w��F�ʏ�
		DISP_3D_TO_MAIN,			//���ʂ�3D
		FALSE,						//����A�g���r���[�g�V�X�e���F�g��Ȃ�
		TRUE,						//�T�u�I�[�o�[���C�F�����ǂݍ���
		0,							//����A�g���r���[�g�p�ɕێ�����f�[�^��
		0xc4000,					//�t�B�[���h�Ŋm�ۂ���q�[�v�̃T�C�Y
	},
	///MAP_MODE_COLOSSEUM	�ʐM�ΐ핔��
	{
		FIELD_SUBSCRN_NO_POKETCH,	//�T�u��ʁF�����X�^�[�{�[���\������
		DIV_MAP_MODE_UNDER,			//�}�b�v�����]���V�X�e���w��F�n���p
		MAP_TOOL_MODE_UNDER,		//�}�b�v�c�[���w��F�n���p
		DISP_3D_TO_MAIN,			//���ʂ�3D
		TRUE,						//����A�g���r���[�g�V�X�e���F�g��
		TRUE,						//�T�u�I�[�o�[���C�F�����ǂݍ���
		1,							//����A�g���r���[�g�p�ɕێ�����f�[�^��
		0xc4000,					//�t�B�[���h�Ŋm�ۂ���q�[�v�̃T�C�Y
	},
	///MAP_MODE_BTOWER		�o�g���^���[
	{
		FIELD_SUBSCRN_POKETCH,		//�T�u��ʁF�|�P�b�`
		DIV_MAP_MODE_UNDER,			//�}�b�v�����]���V�X�e���w��F�n���p
		MAP_TOOL_MODE_UNDER,		//�}�b�v�c�[���w��F�n���p
		DISP_3D_TO_MAIN,			//���ʂ�3D
		TRUE,						//����A�g���r���[�g�V�X�e���F�g��
		TRUE,						//�T�u�I�[�o�[���C�F�����ǂݍ���
		1,							//����A�g���r���[�g�p�ɕێ�����f�[�^��
		0xc4000 - FIELD_HEIGHT_DATA_SIZE * 4,	//�t�B�[���h�Ŋm�ۂ���q�[�v�̃T�C�Y
	},
};

//============================================================================================
//
//
//	�c�[���֐�
//
//
//============================================================================================
//-----------------------------------------------------------------------------
/**
 * @brief	�}�b�v���[�h�C������
 * @param	fsys		�t�B�[���h���䃏�[�N�ւ̃|�C���^
 *
 * �o�g���^���[�ł͒ʐM�������Ȃ��ƃ��������s�����邽�߂ɁA����A�g���r���[�g��
 * �g�p����B�{���̓o�g���^���[�̏o����Ŗ����I��MapMode�̎w����s���ׂ��ł��邪
 * �����I�Ȕ��f����A���ꏈ����MapMode�̐ؑւ��s���B06.05.16 tamada
 */
//-----------------------------------------------------------------------------
static void MapChg_MapModeControl(FIELDSYS_WORK * fsys)
{
	BOOL IsBtower;

	switch (fsys->location->zone_id) {
	case ZONE_ID_D31R0201:
	case ZONE_ID_D31R0202:
	case ZONE_ID_D31R0203:
	case ZONE_ID_D31R0204:
	case ZONE_ID_D31R0205:
	case ZONE_ID_D31R0206:
	case ZONE_ID_D31R0207:
		IsBtower = TRUE;
		break;
	default:
		IsBtower = FALSE;
	}
	if (!IsBtower && fsys->MapMode == MAP_MODE_BTOWER) {
	//�o�g���^���[�ȊO�Ń}�b�v���[�h��BTOWER�̂Ƃ��A�ʏ탂�[�h�ɏC������
		fsys->MapMode = MAP_MODE_GROUND;
	} 
	if (IsBtower) {
	//�o�g���^���[�̂Ƃ��A�}�b�v���[�h��BTOWER�ɂ���
		fsys->MapMode = MAP_MODE_BTOWER;
	}
}

//-----------------------------------------------------------------------------
/**
 * @brief	�}�b�v�w��X�V
 * @param	fsys		�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	next		���̑J�ڐ���w��LOCATION_WORK�ւ̃|�C���^
 */
//-----------------------------------------------------------------------------
static void MapChg_SetNewLocation(FIELDSYS_WORK * fsys, const LOCATION_WORK * next)
{
	SITUATION * sit = SaveData_GetSituation(fsys->savedata);
	LOCATION_WORK * before = Situation_GetBeforeLocation(sit);
///	LOCATION_WORK * escape = Situation_GetEscapeLocation(sit);
	//���P�[�V�����X�V
	if (next != NULL) {
		*before = *fsys->location;
		*(fsys->location) = *next;
	}
	//�]�[���ʃf�[�^�̓ǂݍ���
	EventData_LoadZoneData(fsys, fsys->location->zone_id);

	if (fsys->location->door_id != DOOR_ID_JUMP_CODE){
		//�o�����ڑ��̏ꍇ�̏���
		const CONNECT_DATA* connect;
		connect = EventData_GetNowConnectDataByID(fsys, fsys->location->door_id);
		fsys->location->grid_x = connect->x;
		fsys->location->grid_z = connect->z;
		//����ڑ���ɏo���ꍇ�́A����ڑ����ێ�����悤�ɂ��Ă���
		if (connect->link_door_id == SPECIAL_SPEXIT01) {
			LOCATION_WORK *sp, *ent;
			sp = Situation_GetSpecialLocation(sit);
			ent = Situation_GetEntranceLocation(sit);
			*sp = *ent;
		}
	}
#ifdef	DEBUG_ONLY_FOR_tamada
	OS_Printf("ZONE:%d X:%d Z:%d\n",fsys->location->zone_id,
			fsys->location->grid_x, fsys->location->grid_z);
#endif
}

//-----------------------------------------------------------------------------
/**
 * @brief	�V�X�e���t���O������3D�ʂ��Z�b�g
 * @param	fsys		�t�B�[���h���䃏�[�N�ւ̃|�C���^
 */
//-----------------------------------------------------------------------------
void MapChg_Set3DDisplay(FIELDSYS_WORK *fsys)
{
	GF_ASSERT(fsys->MapMode < MAP_MODE_MAX);
	sys.disp3DSW = fsys->MapModeData->disp3DSW;
}

//-----------------------------------------------------------------------------
/**
 * @brief	�}�b�v�J�ڎ��̃f�[�^�X�V����
 * @param	fsys		�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	walk_flag	TRUE�̂Ƃ��A���邢�Đڑ�
 *						FALSE�̂Ƃ��A�}�b�v�ؑւŐڑ�
 */
//-----------------------------------------------------------------------------
void MapChg_UpdateGameData(FIELDSYS_WORK * fsys, BOOL walk_flag)
{
	int zone_id = fsys->location->zone_id;
	SITUATION * sit = SaveData_GetSituation(fsys->savedata);

	//--�}�b�v������BGM�w����N���A
	Snd_FieldBgmClearSpecial( fsys );

	//--�X�N���v�g�̃}�b�v������t���O�����[�N�̃N���A
	LocalEventFlagClear(fsys);

	//--�t���O�N���A
	if (!walk_flag) {
		FldFlgInit_MapJump(fsys);	//�}�b�v�W�����v�ł̃t���O���Ƃ�����
	}else{
		FldFlgInit_Walk(fsys);		//�n�����ł̃]�[���܂����t���O���Ƃ�����
	}
	
	//--�o�g���T�[�`���[���Z�b�g
	Sys_BtlSearcherReset( SaveData_GetEventWork(fsys->savedata) );

	//--���ԃC�x���g�X�V����
	if (!walk_flag) {
		EVTIME_Update(fsys);
	}

	//--�}�b�v����̎d�|���p���[�N�̃N���A
	if (!walk_flag){
		//�}�b�v�W�����v�̂Ƃ��̂ݏ���������i�����ă]�[�����؂�ւ�����ꍇ�͏��������Ȃ��j
		GIMMICKWORK_Init(SaveData_GetGimmickWork(fsys->savedata));
	}
	
	//--�V������X�V
	{
		EVENTWORK * ev = SaveData_GetEventWork(fsys->savedata);
		u16 id = WeatherData_Get(fsys, zone_id);
		if ((id == WEATHER_SYS_MIST1 && SysFlag_KiribaraiCheck(ev) == TRUE)
				|| (id == WEATHER_SYS_FLASH && SysFlag_FlashCheck(ev) == TRUE)
		   ) {
			id = WEATHER_SYS_SUNNY;
		}
		Situation_SetWeatherID(sit, id);
	}

	//--�J����
	if (walk_flag) {
		int old_camera = Situation_GetCameraID(sit);
		int new_camera = ZoneData_GetCameraID(zone_id);
		//�����ă]�[�����؂�ւ�����̂ɃJ�������ς���Ă͂܂���
		GF_ASSERT(old_camera == new_camera);
	} else {
		//�J�����w����X�V
		Situation_SetCameraID(sit, ZoneData_GetCameraID(zone_id));
	}

	//--���[�v��o�^
	if (!walk_flag){
		u16 warp_id;
		//���[�v�f�[�^�ɓo�^����Ă���}�b�v�Ȃ�΁A�߂��Ƃ��ēo�^���Ă���
		warp_id = WARPDATA_SearchByRoomID(zone_id);
		if (warp_id != 0) {
			Situation_SetWarpID(sit, warp_id);
		}
	}

	//--����X�N���v�g
	SpScriptSearch(fsys, SP_SCRID_FLAG_CHANGE);


	//�G���J�E���g�֘A������
	fsys->encount.walk_count = 0;
	fsys->encount.WinPokeCount = 0;
#if 0
	//�T�t�@���ɂ��Ȃ��Ƃ��̏���
	if ( !SysFlag_SafariCheck(SaveData_GetEventWork(fsys->savedata)) ){
		//�]�[���ύX���������ꍇ�́A�]�[���������X�V
		ENC_SV_PTR data;
		data = EncDataSave_GetSaveDataPtr(fsys->savedata);
		MP_UpdatePlayerZoneHist(data, fsys->location->zone_id);		
		//�����Ĉړ������ꍇ�͈ړ��|�P�����̈ړ�����
		if (walk_flag){
			//�ړ��|�P�����אڈړ�
			MP_MovePokemonNeighboring(data);
		}
	}
#endif	
}

//-----------------------------------------------------------------------------
/**
 * @brief	�}�b�v�J�n���̃t�B�[���hOBJ�֘A����
 * @param	fsys		�t�B�[���h���䃏�[�N�ւ̃|�C���^
 */
//-----------------------------------------------------------------------------
static void MapChg_FieldOBJ_Create(FIELDSYS_WORK * fsys)
{
	int sex;
	int form;
	SITUATION *situ;
	PLAYER_SAVE_DATA *jikisave;
	
	//�t�B�[���hOBJ������ ����,�l�͓K��
	fsys->fldobjsys = FieldOBJSys_Init( fsys, FLDOBJ_ENTRY_MAX, FLDMAP_PRI_OBJSYS );
	
	//���@�ǉ�����
	sex = MyStatus_GetMySex(SaveData_GetMyStatus(fsys->savedata));
	situ = SaveData_GetSituation( fsys->savedata );
	jikisave = Situation_GetPlayerSaveData( situ );
	fsys->player = Player_Init( fsys->fldobjsys,
			fsys->location->grid_x,
			fsys->location->grid_z,
			fsys->location->dir,
			jikisave->form, sex, jikisave );
	
	//�ŏ��̃]�[���S�t�B�[���hOBJ�ǉ�
	EventData_SetFieldOBJ( fsys );

	//�t�B�[���hOBJ���쏈���|�[�Y
	FieldOBJSys_MoveStopAll( fsys->fldobjsys );
}
//-----------------------------------------------------------------------------
/**
 * @brief	�}�b�v�I�����̃t�B�[���hOBJ�֘A����
 * @param	fsys		�t�B�[���h���䃏�[�N�ւ̃|�C���^
 */
//-----------------------------------------------------------------------------
static void MapChg_FieldOBJ_Delete(FIELDSYS_WORK * fsys)
{
    CommPlayerManagerReset();               // �ʐM���莩�@���
    Player_Delete( fsys->player );			// ���@���
	FieldOBJ_DeleteAll(fsys->fldobjsys);	// FieldOBJ�S���
	FieldOBJSys_Delete(fsys->fldobjsys);	// FieldOBJ�V�X�e�����
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static void MapChg_FieldOBJ_Continue(FIELDSYS_WORK * fsys)
{
	//�t�B�[���hOBJ������ ����,�l�͓K��
	fsys->fldobjsys = FieldOBJSys_Init( fsys, FLDOBJ_ENTRY_MAX, FLDMAP_PRI_OBJSYS );
	

	Field_LoadFieldObj(fsys);
	//���@�ǉ�����
	
	{
		SITUATION *situ = SaveData_GetSituation( fsys->savedata );
		PLAYER_SAVE_DATA *jikisave = Situation_GetPlayerSaveData( situ );
		int sex = MyStatus_GetMySex(SaveData_GetMyStatus(fsys->savedata));
		fsys->player = Player_FieldOBJUseRecover(fsys->fldobjsys,jikisave,sex);
	}

	//�t�B�[���hOBJ���쏈���|�[�Y
	FieldOBJSys_MoveStopAll( fsys->fldobjsys );
}

//-----------------------------------------------------------------------------
/**
 * @brief	�}�b�v�c�[���i�����A�A�g���r���[�g�Aetc.�j�̐ݒ�
 * @param	fsys		�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	type		�c�[���̃^�C�v�w��
 */
//-----------------------------------------------------------------------------
static void MapChg_SetupMapTools(FIELDSYS_WORK * fsys)
{
	//�o�g���^���[�̂��߂Ƀ}�b�v���[�h�̏C�����s���Ă���
	MapChg_MapModeControl(fsys);

	GF_ASSERT(fsys->map_tool_list == NULL);
	//���[���h�Z�b�g�A�b�v
	SetUpWorldMatrix( fsys->location->zone_id, fsys->World );
	//�}�b�v�}�g���N�X���㏑���FR224
	if (SysWork_HideMapWorkCheck(SaveData_GetEventWork(fsys->savedata),HIDEMAP_ID_D18)) {
		World_Overwrite_R224(fsys->World);
	}
	//�}�b�v�}�g���N�X���㏑���FL04
	if (!SysWork_HideMapWorkCheck(SaveData_GetEventWork(fsys->savedata),HIDEMAP_ID_L04)) {
		World_Overwrite_L04(fsys->World);
	}
	
	GF_ASSERT(fsys->MapMode < MAP_MODE_MAX);
	fsys->MapModeData = &MapModeData[fsys->MapMode];
	fsys->DivMapMode = fsys->MapModeData->DivMapMode;
	fsys->subscreen = fsys->MapModeData->subscreen;
	SetUpMapToolList(&fsys->map_tool_list, fsys->MapModeData->MapToolMode);

	if (fsys->MapModeData->SpecialAttrFlag) {
		//�A�g���r���[�g�ǂݍ���
		SPATTR_SetUpGroundAttr(fsys, fsys->MapModeData->SpecialAttrNum);
	}
	
}

//-----------------------------------------------------------------------------
/**
 * @brief	�}�b�v�c�[���i�����A�A�g���r���[�g�Aetc.�j�̔p��
 * @param	fsys		�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	type		�c�[���̃^�C�v�w��
 */
//-----------------------------------------------------------------------------
static void MapChg_RemoveMapTools(FIELDSYS_WORK * fsys)
{
	GF_ASSERT(fsys->map_tool_list != NULL);
	fsys->map_tool_list = NULL;
	fsys->subscreen = FIELD_SUBSCRN_MAX;

	if (fsys->MapModeData->SpecialAttrFlag) {
		//�n���A�g���r���[�g�j��
		SPATTR_FreeGroundAttr(fsys);
	}
	fsys->MapModeData = NULL;
}

//-----------------------------------------------------------------------------
/**
 * @brief	�`���m�[�g�̊J�n�f�[�^�쐬
 * @param	fsys		�t�B�[���h���䃏�[�N�ւ̃|�C���^
 */
//-----------------------------------------------------------------------------
void FNoteStartDataSet( FIELDSYS_WORK * fsys )
{
	if( fsys->fnote != NULL ){
		void * dat;

		dat = FNOTE_StartDataMake( fsys->location->zone_id, HEAPID_WORLD );
		FNOTE_DataSave( fsys->fnote, dat, FNOTE_TYPE_START );
	}
}

//-----------------------------------------------------------------------------
/**
 * @brief	���݈ʒu��LOCATION_WORK�ɃZ�b�g����
 * @param	loc			LOCATION_WORK�ւ̃|�C���^
 * @param	fsys		�t�B�[���h���䃏�[�N�ւ̃|�C���^
 */
//-----------------------------------------------------------------------------
static void SetLocationHere(LOCATION_WORK * loc, const FIELDSYS_WORK * fsys)
{
	SetLocation(loc, fsys->location->zone_id, DOOR_ID_JUMP_CODE,
			Player_NowGPosXGet(fsys->player), Player_NowGPosZGet(fsys->player), DIR_DOWN);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static BOOL IsUnionRoomSave(const FIELDSYS_WORK * fsys)
{
	if (ZoneData_IsPokecen2F(fsys->location->zone_id)
		&& fsys->location->grid_x == 7
		&& fsys->location->grid_z == 6) {
		return TRUE;
	} else {
		return FALSE;
	}
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static void SetUnionExit(FIELDSYS_WORK * fsys)
{
	//�|�P�Z���QF����J�n�̏ꍇ�͓���ڑ����ݒ�
	LOCATION_WORK * sp = Situation_GetSpecialLocation(SaveData_GetSituation(fsys->savedata));
	EVENTWORK * ev = SaveData_GetEventWork(fsys->savedata);
	SetLocation(sp, fsys->location->zone_id, DOOR_ID_JUMP_CODE, 8, 2, DIR_DOWN);
}
//============================================================================================
//
//
//							�Q�[���J�n
//
//
//============================================================================================
//-----------------------------------------------------------------------------
/**
 * @brief	�C�x���g�F�Q�[���J�n
 */
//-----------------------------------------------------------------------------
static BOOL GMEVENT_FirstMapIn(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	int * seq = FieldEvent_GetSeqWork(event);

	switch (*seq) {
	case 0:
		MapChg_SetNewLocation(fsys, fsys->location);

		//�����A�A�g���r���[�g�A�}�b�v���[�h�̕��@������
		MapChg_SetupMapTools(fsys);

		MapChg_UpdateGameData(fsys, FALSE);

		MapChg_FieldOBJ_Create(fsys);

		(*seq) ++;
		break;
	case 1:
		EventCmd_StartField_FadeIn(event);
		(*seq) ++;
		break;
	case 2:
		return TRUE;
	}
	return FALSE;
}
//-----------------------------------------------------------------------------
/**
 * @brief	�Q�[���J�n�C�x���g�Z�b�g
 * @param	fsys		�t�B�[���h���䃏�[�N�ւ̃|�C���^
 */
//-----------------------------------------------------------------------------
void EventSet_FirstMapIn(FIELDSYS_WORK * fsys)
{
	GMEVENT_CONTROL * event;

	fsys->MapMode = MAP_MODE_GROUND;	//�n�߂͒n�ォ��X�^�[�g
	GameStartScriptInit(fsys);				//�Q�[���J�n���̓���X�N���v�g����
	event = FieldEvent_Set(fsys, GMEVENT_FirstMapIn, NULL);
}

//-----------------------------------------------------------------------------
/**
 * @brief	�C�x���g�F�R���e�B�j���[
 */
//-----------------------------------------------------------------------------
static BOOL GMEVENT_ContinueMapIn(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENTWORK * ev = SaveData_GetEventWork(fsys->savedata);
	int * seq = FieldEvent_GetSeqWork(event);

	switch (*seq) {
	case 0:
        //���[�h����ɌĂԒn���f�[�^����
        UnderGroundDataLoadUpdate(fsys->savedata);
        // �`���m�[�g�\���`�F�b�N
		if( FNOTE_GameStartOpenCheck(SaveData_GetFNote(fsys->savedata),SysFlag_FNoteCheck(ev)) ){
			FieldFantasyNote_SetProc( fsys, NULL );
			(*seq) = 4;
			break;
		}
		OS_Printf( "FNOTE_FLAG : %d\n", SysFlag_FNoteCheck(ev) );

	case 1:		// �t�B�[���h����
		fsys->fnote = FNOTE_SavePageGet(SaveData_GetFNote(fsys->savedata),
				SysFlag_FNoteCheck(ev));//�`���m�[�g�y�[�W������

		if (SysFlag_CommCounterCheck(ev)) {
		//����ȏ󋵂���̕��A���s���R���e�B�j���[
			SITUATION * sit = SaveData_GetSituation(fsys->savedata);
			//�|�P�Z���QF����J�n�̏ꍇ�͓���ڑ����ݒ�
			if (IsUnionRoomSave(fsys)) {
				SetUnionExit(fsys);
			}
			SysFlag_CommCounterReset(ev);
			MapChg_SetNewLocation(fsys, Situation_GetSpecialLocation(sit));
			//�����A�A�g���r���[�g�A�}�b�v���[�h�̕��@������
			MapChg_SetupMapTools(fsys);
			MapChg_UpdateGameData(fsys, FALSE);
			MapChg_FieldOBJ_Create(fsys);
		} else {
		//�ʏ�̃R���e�B�j���[
			MapChg_SetNewLocation(fsys, NULL);
			//�����A�A�g���r���[�g�A�}�b�v���[�h�̕��@������
			MapChg_SetupMapTools(fsys);
			//MapChg_UpdateGameData(fsys, FALSE);	�R���e�B�j���[�ł͂���͌Ă΂Ȃ�
			EVTIME_Update(fsys);
			MapChg_FieldOBJ_Continue(fsys);
		}

		FNoteStartDataSet( fsys );		//�`���m�[�g�̊J�n�f�[�^�쐬

		FldFlgInit_Continue(fsys);		//�R���e�B�j���[���ŗL�t���O���Ƃ�����

		(*seq) = 2;
		break;

	case 2:		// �t�F�[�h�Z�b�g
		EventCmd_StartField_FadeIn(event);
		(*seq) = 3;
		break;

	case 3:		// �I��
		return TRUE;

	case 4:		// �`���m�[�g�I���҂�
		if( !( FieldEvent_Cmd_WaitSubProcEnd(fsys) ) ) {
			(*seq) = 1;
		}
		break;
	}

	return FALSE;
}
//-----------------------------------------------------------------------------
/**
 * @brief	�Q�[���J�n�C�x���g�Z�b�g
 * @param	fsys		�t�B�[���h���䃏�[�N�ւ̃|�C���^
 */
//-----------------------------------------------------------------------------
void EventSet_ContinueMapIn(FIELDSYS_WORK * fsys)
{
	GMEVENT_CONTROL * event;

	fsys->MapMode = MAP_MODE_GROUND;	//�n�߂͒n�ォ��X�^�[�g
	event = FieldEvent_Set(fsys, GMEVENT_ContinueMapIn, NULL);
}


//============================================================================================
//============================================================================================
//-----------------------------------------------------------------------------
/**
 * @brief
 */
//-----------------------------------------------------------------------------
typedef struct {
	BOOL WarpEffEnd;
	LOCATION_WORK union_loc;
}ERROR_CONTINUE_WORK;

//-----------------------------------------------------------------------------
/**
 * @brief
 */
//-----------------------------------------------------------------------------
static BOOL GMEVENT_ErrorContinueMapIn(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	ERROR_CONTINUE_WORK * ecw = FieldEvent_GetSpecialWork(event);
	EVENTWORK * ev = SaveData_GetEventWork(fsys->savedata);
	int * seq = FieldEvent_GetSeqWork(event);

	switch (*seq) {
	case 0:
		WIPE_SetBrightness( WIPE_DISP_MAIN, WIPE_FADE_BLACK );
		WIPE_SetBrightness( WIPE_DISP_SUB, WIPE_FADE_BLACK );

        //���[�h����ɌĂԒn���f�[�^����
        UnderGroundDataLoadUpdate(fsys->savedata);

		fsys->fnote = FNOTE_SavePageGet(SaveData_GetFNote(fsys->savedata),
				SysFlag_FNoteCheck(ev));//�`���m�[�g�y�[�W������

		(*seq) ++;
		break;

	case 1:
		MapChg_SetNewLocation(fsys, &ecw->union_loc);
		//�����A�A�g���r���[�g�A�}�b�v���[�h�̕��@������
		MapChg_SetupMapTools(fsys);
		MapChg_UpdateGameData(fsys, FALSE);
		MapChg_FieldOBJ_Create(fsys);
		(*seq) ++;
		break;

	case 2:
		// ���j�I�����[���ʐM�J�n
		fsys->union_work = Comm_UnionRoomInit(fsys);
		// ���j�I�����[��OBJ����^�X�N�N��
		fsys->union_view = Comm_UnionRoomViewInit(fsys->union_work);

		EventCmd_StartFieldMap(event);
		(*seq) ++;
		break;

	case 3:
		ecw->WarpEffEnd = FALSE;
        StartJumpPointEffect(fsys, FALSE, &ecw->WarpEffEnd);
		(*seq) ++;
		break;

	case 4:
		if (ecw->WarpEffEnd) {
			(*seq) ++;
		}
		break;
	case 5:
		sys_FreeMemoryEz(ecw);
		return TRUE;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 * @brief	�Q�[���J�n�C�x���g�Z�b�g
 * @param	fsys		�t�B�[���h���䃏�[�N�ւ̃|�C���^
 */
//-----------------------------------------------------------------------------
void EventSet_ErrorContinueMapIn(FIELDSYS_WORK * fsys)
{
	GMEVENT_CONTROL * event;
	ERROR_CONTINUE_WORK * ecw;

	if (ZoneData_IsUnionRoom(fsys->location->zone_id)) {
		/* ��p�����Ȃ� */
	} else if (IsUnionRoomSave(fsys)) {
		//�|�P�Z���QF����J�n�̏ꍇ�͓���ڑ����ݒ�
		EVENTWORK * ev = SaveData_GetEventWork(fsys->savedata);
		SetUnionExit(fsys);
		SysFlag_CommCounterSet(ev);

	} else {

		//�ʐM�G���[�ł����j�I���ȊO�̏ꍇ�͒ʏ�R���e�B�j���[�����֕���
		EventSet_ContinueMapIn(fsys);
		return;
	}

	ecw = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(ERROR_CONTINUE_WORK));
	ecw->WarpEffEnd = FALSE;
	SetLocation(&ecw->union_loc, ZONE_ID_UNION, DOOR_ID_JUMP_CODE, 8, 14, DIR_UP);

	fsys->MapMode = MAP_MODE_UNION;
	FieldEvent_Set(fsys, GMEVENT_ErrorContinueMapIn, ecw);
}


//============================================================================================
//
//
//							�Q�[���I��
//
//
//============================================================================================
//-----------------------------------------------------------------------------
/**
 * @brief	�C�x���g�F�Q�[���I��
 */
//-----------------------------------------------------------------------------
static BOOL GMEVENT_GameEnd(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	int * seq = FieldEvent_GetSeqWork(event);
	switch (*seq) {
	case 0:
		EventCmd_FieldFadeOut(event);
		(*seq) ++;
		break;

	case 1:
		EventCmd_FinishFieldMap(event);
		(*seq) ++;
		break;

	case 2:
		MapChg_FieldOBJ_Delete(fsys);
		MapChg_RemoveMapTools(fsys);

		GameSystem_FinishGame(fsys);

		return TRUE;
	}

	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 * @brief	�Q�[���I������
 *
 * �Q�[�����C���������I��������B
 * �f�o�b�O�p�Ń��������[�N�`�F�b�N�̂��ߍ쐬�����B
 * �|�P�����ł̓��[�U�[����ŃQ�[���I�������邱�Ƃ��Ȃ��̂ŁA���i�łł�
 * �g�p����Ȃ��͂��B
 */
//-----------------------------------------------------------------------------
void EventSet_ReturnToTitle(FIELDSYS_WORK * fsys)
{
	FieldEvent_Set(fsys, GMEVENT_GameEnd, NULL);
}



//============================================================================================
//============================================================================================
//-----------------------------------------------------------------------------
// @brief	�}�b�v�J�ڃC�x���g(�A�j���������W�����v)
//-----------------------------------------------------------------------------
static BOOL GMEVENT_MapChange(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_MAPCHG_WORK * mcw = FieldEvent_GetSpecialWork(event);
	LOCATION_WORK* location = &mcw->next;
	
	switch (mcw->seq) {
	case 0:
		Snd_SePlay( SEQ_SE_DP_KAIDAN2 );
		Snd_EvMapChangeBgmFadeCheck( fsys, location->zone_id );	//�t�B�[���hBGM�t�F�[�h�A�E�g
		EventCmd_FadeOut_FinishField(event);	//�T�u�C�x���g�Ăяo�������̃C�x���g�̓E�F�C�g
		(mcw->seq) ++;
		break;
	case 1:
		//�T�u�C�x���g�Ăяo�������̃C�x���g�̓E�F�C�g
		EventCmd_MapChangeByLocation(event, &mcw->next);
		(mcw->seq) ++;
		break;
	case 2:
		if( Snd_FadeCheck() != 0 ){								//�T�E���h�t�F�[�h��
			break;
		}
		Snd_EvMapChangeBgmPlay( fsys, location->zone_id );		//�t�B�[���hBGM�Đ�
		EventCmd_StartField_FadeIn(event);	//�T�u�C�x���g�Ăяo�������̃C�x���g�̓E�F�C�g
		(mcw->seq) ++;
		break;
	case 3:
		sys_FreeMemoryEz(mcw);
		return TRUE;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 * @brief	�}�b�v�J�ڃC�x���g�Z�b�g
 * @param	fsys		�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	next		�J�ڐ�}�b�v�w��
 */
//-----------------------------------------------------------------------------
void EventSet_EasyMapChangeByLocation(FIELDSYS_WORK * fsys, const LOCATION_WORK * next)
{
	EVENT_MAPCHG_WORK * mcw = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(EVENT_MAPCHG_WORK));
	mcw->seq = 0;
	mcw->next = *next;
	FieldEvent_Set(fsys, GMEVENT_MapChange, mcw);
}

//-----------------------------------------------------------------------------
/**
 * @brief	�}�b�v�J�ڃC�x���g�Z�b�g
 * @param	fsys		�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	zone		�J�ڐ�}�b�v�̃]�[���w��
 * @param	door_id		�J�ڐ�}�b�v�ł̏o���o�����w��
 * @param	x			�J�ڐ�}�b�v�ł�X�O���b�h�ʒu
 * @param	z			�J�ڐ�}�b�v�ł�Y�O���b�h�ʒu
 * @param	dir			�J�ڐ�}�b�v�ł̏�������
 *
 * �J�ڐ�}�b�v�̂ǂ��ɏo�����邩�̏��͎��̃}�b�v��ǂݍ��ނ܂ł͂킩��Ȃ��͂��Ȃ̂�
 * �{���͍��W�w��͖��ʂ�������Ȃ����ǁA�O�̂��߁B�܂��G���A�ƃ]�[���̊֌W�͍čl�����̂�
 * �G���A�w�������Ȃ��Ȃ�\��������B
 */
//-----------------------------------------------------------------------------
void EventSet_EasyMapChange(FIELDSYS_WORK * fsys, int zone, int door_id, int x, int z, int dir )
{
	LOCATION_WORK next;
	SetLocation(&next, zone, door_id, x, z, dir);
	EventSet_EasyMapChangeByLocation(fsys, &next);
}

//-----------------------------------------------------------------------------
/**
 * @brief	�}�b�v�J�ڃC�x���g�R�}���h
 * @param	fsys		�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	next		�J�ڐ�}�b�v�w��
 */
//-----------------------------------------------------------------------------
void EventCmd_EasyMapChangeByLocation(GMEVENT_CONTROL * event, const LOCATION_WORK * next)
{
	EVENT_MAPCHG_WORK * mcw = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(EVENT_MAPCHG_WORK));
	mcw->seq = 0;
	mcw->next = *next;
	FieldEvent_Call(event, GMEVENT_MapChange, mcw);
}
//-----------------------------------------------------------------------------
/**
 * @brief	�}�b�v�J�ڃC�x���g�R�}���h
 * @param	fsys		�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	zone		�J�ڐ�}�b�v�̃]�[���w��
 * @param	door_id		�J�ڐ�}�b�v�ł̏o���o�����w��
 * @param	x			�J�ڐ�}�b�v�ł�X�O���b�h�ʒu
 * @param	z			�J�ڐ�}�b�v�ł�Y�O���b�h�ʒu
 * @param	dir			�J�ڐ�}�b�v�ł̏�������
 */
//-----------------------------------------------------------------------------
void EventCmd_EasyMapChange(GMEVENT_CONTROL * event, int zone, int door_id, int x, int z, int dir )
{
	LOCATION_WORK next;
	SetLocation(&next, zone, door_id, x, z, dir);
	EventCmd_EasyMapChangeByLocation(event, &next);
}

//============================================================================================
//
//
//	�C�x���g�[���R�}���h�F�}�b�v�J�ڊ֘A
//
//	�T�u�C�x���g��FieldEvent_Call�ŌĂяo�����ƂŎg�p����B
//	���݂̃C�x���g���~���āA����ɃT�u�C�x���g����т����B
//	�T�u�C�x���g���I������ƌ��݂̃C�x���g���Ăяo�����B
//
//	�����I�ɂ�FieldEvent_Call���Ăяo���ăT�u�C�x���g���s���s���Ă��邪�A
//	�C�x���g������͒P���ȃR�}���h�Ăяo���Ŏ��s�ł���悤�Ȍ`�ɐ����Ă����\��B
//
//============================================================================================
//-----------------------------------------------------------------------------
/**
 * @brief	�[���R�}���h�p���[�N��`
 */
//-----------------------------------------------------------------------------
typedef struct {
	int seq;
	LOCATION_WORK next;
}SIMPLE_MAPCHG_WORK;

//-----------------------------------------------------------------------------
/**
 * @brief	�T�u�C�x���g�F�}�b�v�J��
 * @param	event	�C�x���g���䃏�[�N�ւ̃|�C���^
 * @retval	TRUE	�C�x���g�I��
 * @retval	FALSE	�C�x���g�p����
 *
 * �T�u�C�x���g��FieldEvent_Call�ŌĂяo�����ƂŎg�p����B
 * ���݂̃C�x���g���~���āA����ɃT�u�C�x���g����т����B
 * �T�u�C�x���g���I������ƌ��݂̃C�x���g���Ăяo�����B
 */
//-----------------------------------------------------------------------------
static BOOL GMEVENT_Sub_MapChange(GMEVENT_CONTROL * event)
{
	u16 bgm_no;
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	SIMPLE_MAPCHG_WORK * smw = FieldEvent_GetSpecialWork(event);

	switch (smw->seq) {
	case 0:
		//--------�I������--------
		MapChg_FieldOBJ_Delete(fsys);
		MapChg_RemoveMapTools(fsys);
		(smw->seq) ++;
		break;
		
	case 1:
		//--------�J�n����--------
		MapChg_SetNewLocation(fsys, &smw->next);

		//�����A�A�g���r���[�g�A�}�b�v���[�h�̕��@������
		MapChg_SetupMapTools(fsys);

		MapChg_UpdateGameData(fsys, FALSE);

		SwayGrass_InitSwayGrass(fsys->SwayGrass);	//�h�ꑐ������
		(smw->seq) ++;
		break;
		
	case 2:
		MapChg_FieldOBJ_Create(fsys);
		sys_FreeMemoryEz(smw);
		return TRUE;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 * @brief	�C�x���g�[���R�}���h�F�}�b�v�J��
 * @param	event		�C�x���g���䃏�[�N�ւ̃|�C���^
 * @param	next		�J�ڐ���w�肷��LOCATION_WORK�^�ւ̃|�C���^
 */
//-----------------------------------------------------------------------------
void EventCmd_MapChangeByLocation(GMEVENT_CONTROL * event, const LOCATION_WORK * next)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	SIMPLE_MAPCHG_WORK * smw = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(SIMPLE_MAPCHG_WORK));
	if (GameSystem_CheckFieldProcExists(fsys)) {
		GF_ASSERT("mainproc������̂Ƀ}�b�v�J�ڏ���\n" && 0);
		return;
	}
	smw->seq = 0;
	smw->next = *next;
	FieldEvent_Call(event, GMEVENT_Sub_MapChange, smw);
}

//-----------------------------------------------------------------------------
/**
 * @brief	�C�x���g�[���R�}���h�F�}�b�v�J��
 * @param	event		�C�x���g���䃏�[�N�ւ̃|�C���^
 * @param	zone_id		�J�ڐ�]�[��ID�w��
 * @param	door_id		�J�ڐ�o�����w��
 * @param	x			�J�ڐ�X���W�w��idoor_id == DOOR_ID_JUMP_CODE�̂Ƃ��̂ݗL���j
 * @param	z			�J�ڐ�Z���W�w��idoor_id == DOOR_ID_JUMP_CODE�̂Ƃ��̂ݗL���j
 * @param	dir			�o����ł̕����w��
 *
 */
//-----------------------------------------------------------------------------
void EventCmd_MapChange(GMEVENT_CONTROL * event, int zone_id, int door_id, int x, int z, int dir)
{
	LOCATION_WORK next;
	SetLocation(&next, zone_id, door_id, x, z, dir);
	EventCmd_MapChangeByLocation(event, &next);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static BOOL GMEVENT_Sub_MapChangeFull(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	SIMPLE_MAPCHG_WORK * mcw = FieldEvent_GetSpecialWork(event);
	LOCATION_WORK* location = &mcw->next;

	switch (mcw->seq) {
	case 0:
		Snd_EvMapChangeBgmFadeCheck( fsys, location->zone_id );	//�t�B�[���hBGM�t�F�[�h�A�E�g
		EventCmd_FinishFieldMap(event);
		(mcw->seq) ++;
		break;
	case 1:
		EventCmd_MapChangeByLocation(event, &mcw->next);
		(mcw->seq) ++;
		break;
	case 2:
		if( Snd_FadeCheck() != 0 ){								//�T�E���h�t�F�[�h��
			break;
		}
		Snd_EvMapChangeBgmPlay( fsys, location->zone_id );		//�t�B�[���hBGM�Đ�
		EventCmd_StartFieldMap(event);
		(mcw->seq) ++;
		break;
	case 3:
		sys_FreeMemoryEz(mcw);
		return TRUE;
	}
	return FALSE;
}
//-----------------------------------------------------------------------------
/**
 * @brief	�C�x���g�[���R�}���h�F�}�b�v�ؑ�
 * @param	event		�C�x���g���䃏�[�N�ւ̃|�C���^
 * @param	zone_id		�J�ڐ�]�[��ID�w��
 * @param	door_id		�J�ڐ�o�����w��
 * @param	x			�J�ڐ�X���W�w��idoor_id == DOOR_ID_JUMP_CODE�̂Ƃ��̂ݗL���j
 * @param	z			�J�ڐ�Z���W�w��idoor_id == DOOR_ID_JUMP_CODE�̂Ƃ��̂ݗL���j
 * @param	dir			�o����ł̕����w��
 *
 * �t�B�[���h�}�b�v�I�����}�b�v�ؑ֏������t�B�[���h�}�b�v�ĊJ�܂ł̏�������A�ōs��
 */
//-----------------------------------------------------------------------------
void EventCmd_MapChangeFull(GMEVENT_CONTROL * event,
		int zone_id, int door_id, int x, int z, int dir)
{
	SIMPLE_MAPCHG_WORK * smw = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(SIMPLE_MAPCHG_WORK));
	smw->seq = 0;
	SetLocation(&smw->next, zone_id, door_id, x, z, dir);
	FieldEvent_Call(event, GMEVENT_Sub_MapChangeFull, smw);
}

//============================================================================================
//
//
//			�Ђł�킴�@������Ƃԗp�}�b�v�ړ�
//
//
//============================================================================================
//-----------------------------------------------------------------------------
/**
 * @brief	����Ԑ�p�}�b�v�J�ڃC�x���g�p���䃏�[�N
 */
//-----------------------------------------------------------------------------
typedef struct {
	int seq;							///<�V�[�P���X�ێ����[�N
	TCB_PTR tcb_sky;					///<����ԓ���TCB_PTR
	LOCATION_WORK next;					///<�}�b�v�J�ڐ�w��p���[�N
	FLD_3D_ANIME_WORK_PTR DoorAnimeWork;
}EVENT_MAPCHG_WORK_SKY;

static BOOL GMEVENT_MapChangeBySky(GMEVENT_CONTROL * event);
static void EventCmd_Sky_FinishField(GMEVENT_CONTROL * event);
static void EventCmd_FadeOut_FinishField(GMEVENT_CONTROL * event);
static BOOL GMEVENT_Sub_Sky_FinishField(GMEVENT_CONTROL * event);
static void EventCmd_StartField_FadeInSky(GMEVENT_CONTROL * event);
static BOOL GMEVENT_Sub_StartField_FadeInSky(GMEVENT_CONTROL * event);
static void EventCmd_FieldFadeInSky(GMEVENT_CONTROL * event);
static BOOL GMEVENT_Sub_WaitFadeSky(GMEVENT_CONTROL * event);

//-----------------------------------------------------------------------------
/**
 * @brief	������ԗp�}�b�v�J�ڃC�x���g�Z�b�g
 * @param	fsys		�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	zone		�J�ڐ�}�b�v�̃]�[���w��
 * @param	door_id		�J�ڐ�}�b�v�ł̏o���o�����w��
 * @param	x			�J�ڐ�}�b�v�ł�X�O���b�h�ʒu
 * @param	z			�J�ڐ�}�b�v�ł�Y�O���b�h�ʒu
 * @param	dir			�J�ڐ�}�b�v�ł̏�������
 */
//-----------------------------------------------------------------------------
void EventSet_MapChangeBySky(
		FIELDSYS_WORK * fsys, int zone, int door_id, int x, int z, int dir )
{
	LOCATION_WORK next;
	SetLocation(&next, zone, door_id, x, z, dir);
	
	{
		EVENT_MAPCHG_WORK_SKY * mcw =
			sys_AllocMemoryLo(HEAPID_WORLD, sizeof(EVENT_MAPCHG_WORK_SKY));
		mcw->seq = 0;
		mcw->tcb_sky = NULL;
		mcw->next = next;
		FieldEvent_Set(fsys, GMEVENT_MapChangeBySky, mcw);
	}
}

//-----------------------------------------------------------------------------
/**
 * @brief	������ԗp�}�b�v�J�ڃC�x���g�Z�b�g�@�C�x���g�`�F���W�^
 * @param	fsys		�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	zone		�J�ڐ�}�b�v�̃]�[���w��
 * @param	door_id		�J�ڐ�}�b�v�ł̏o���o�����w��
 * @param	x			�J�ڐ�}�b�v�ł�X�O���b�h�ʒu
 * @param	z			�J�ڐ�}�b�v�ł�Y�O���b�h�ʒu
 * @param	dir			�J�ڐ�}�b�v�ł̏�������
 */
//-----------------------------------------------------------------------------
void EventChange_MapChangeBySky(
		GMEVENT_CONTROL *event, int zone, int door_id, int x, int z, int dir )
{
	LOCATION_WORK next;
	SetLocation(&next, zone, door_id, x, z, dir);
	
	{
		EVENT_MAPCHG_WORK_SKY * mcw =
			sys_AllocMemoryLo(HEAPID_WORLD, sizeof(EVENT_MAPCHG_WORK_SKY));
		mcw->seq = 0;
		mcw->tcb_sky = NULL;
		mcw->next = next;
		FieldEvent_Change(event, GMEVENT_MapChangeBySky, mcw);
	}
}

//-----------------------------------------------------------------------------
// @brief	�}�b�v�J�ڃC�x���g(������Ƃ�)
//-----------------------------------------------------------------------------
static BOOL GMEVENT_MapChangeBySky(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_MAPCHG_WORK_SKY * mcw = FieldEvent_GetSpecialWork(event);
	LOCATION_WORK* location = &mcw->next;
	
	switch (mcw->seq) {
	case 0:
		Snd_EvMapChangeBgmFadeCheck( fsys, location->zone_id );	//�t�B�[���hBGM�t�F�[�h�A�E�g
		EventCmd_Sky_FinishField(event);	//�T�u�C�x���g�Ăяo�������̃C�x���g�̓E�F�C�g
		(mcw->seq) ++;
		break;
	case 1:
		//���@��Ԃ�񑫕��s�ɂ���
		Player_FormSet(fsys->player, HERO_FORM_NORMAL);
		//�T�u�C�x���g�Ăяo�������̃C�x���g�̓E�F�C�g
		EventCmd_MapChangeByLocation(event, &mcw->next);
		(mcw->seq) ++;
		break;
	case 2:
		if( Snd_FadeCheck() != 0 ){								//�T�E���h�t�F�[�h��
			break;
		}
		Snd_EvMapChangeBgmPlay( fsys, location->zone_id );		//�t�B�[���hBGM�Đ�

		//����ԌŗL�t���O���Ƃ�����
		FldFlgInit_FlySky(fsys);

		EventCmd_StartField_FadeInSky(event);	//�T�u�C�x���g�Ăяo�������̃C�x���g�̓E�F�C�g
		(mcw->seq) ++;
		break;
	case 3:
		sys_FreeMemoryEz(mcw);
		return TRUE;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 * @brief	�C�x���g�[���R�}���h�F�t�B�[���h�v���Z�X�I���@������Ƃ�
 * @param	event		�C�x���g���䃏�[�N�ւ̃|�C���^
 */
//-----------------------------------------------------------------------------
static void EventCmd_Sky_FinishField(GMEVENT_CONTROL * event)
{
	FieldEvent_Call(event, GMEVENT_Sub_Sky_FinishField, NULL);
}

//-----------------------------------------------------------------------------
// @brief	�t�B�[���h�I��(������Ƃ�)
//-----------------------------------------------------------------------------
static BOOL GMEVENT_Sub_Sky_FinishField(GMEVENT_CONTROL * event)
{
	int * seq = FieldEvent_GetSeqWork(event);
	switch (*seq) {
	case 0:
		EventCmd_FinishFieldMap(event);
		(*seq) ++;
		break;
	case 1:
		return TRUE;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 * @brief	�C�x���g�[���R�}���h�F�t�B�[���h�v���Z�X�J�n���t�F�[�h�C���@������Ƃ�
 * @param	event		�C�x���g���䃏�[�N�ւ̃|�C���^
 */
//-----------------------------------------------------------------------------
static void EventCmd_StartField_FadeInSky(GMEVENT_CONTROL * event)
{
	EVENT_MAPCHG_WORK_SKY * mcw = FieldEvent_GetSpecialWork(event);
	FieldEvent_Call(event, GMEVENT_Sub_StartField_FadeInSky, mcw);
}

//-----------------------------------------------------------------------------
// @brief	�t�B�[���h�t�F�[�h�C���@������Ƃ�
//-----------------------------------------------------------------------------
static BOOL GMEVENT_Sub_StartField_FadeInSky(GMEVENT_CONTROL * event)
{
	int * seq = FieldEvent_GetSeqWork(event);
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);	
	switch (*seq) {
	case 0:
		EventCmd_StartFieldMap(event);
		(*seq) ++;
		break;
	case 1:
		//�n���\��
		PlaceNameRequestByFsys(fsys);
		
		EventCmd_FieldFadeInSky(event);
		(*seq) ++;
		break;
	case 2:
		return TRUE;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 * @brief	�C�x���g�[���R�}���h�F�t�F�[�h�C���@������Ƃ�
 * @param	event		�C�x���g���䃏�[�N�ւ̃|�C���^
 */
//-----------------------------------------------------------------------------
static void EventCmd_FieldFadeInSky(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_MAPCHG_WORK_SKY * mcw = FieldEvent_GetSpecialWork(event);
	
	if (!GameSystem_CheckFieldProcExists(fsys)) {
		GF_ASSERT("mainproc���Ȃ��̂Ƀt�F�[�h�����s\n" && 0);
		return;
	}
	
	//�����ɃJ�b�g�C����p�̂��̂����Ă�@�t�F�[�h�C���͂��̒���
	{
#if 0
		WIPE_SYS_Start(
            WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN,
            WIPE_TYPE_FADEIN, WIPE_FADE_WHITE, COMM_BRIGHTNESS_SYNC, 1, HEAPID_FIELD );
#else
		mcw->tcb_sky = FieldHidenSkyLanding_Init( fsys, Player_SexGet(fsys->player) );
#endif
		FieldEvent_Call(event, GMEVENT_Sub_WaitFadeSky, mcw);
	}
}

//-----------------------------------------------------------------------------
// @brief	�t�B�[���h�t�F�[�h�C���҂��@������ƂԁB
// �����ɋ���ԏI���G�t�F�N�g�҂��𓖂Ă�
//-----------------------------------------------------------------------------
static BOOL GMEVENT_Sub_WaitFadeSky(GMEVENT_CONTROL * event)
{
	EVENT_MAPCHG_WORK_SKY * mcw = FieldEvent_GetSpecialWork(event);
	
	if( FieldHidenSkyLanding_EndCheck(mcw->tcb_sky) == TRUE ){
		FieldHidenSkyLanding_End( mcw->tcb_sky );
		return( TRUE );
	}
	
	return FALSE;
}

//============================================================================================
//
//
//			���Ȃʂ��̂Ђ��A���Ȃ��ق�A�e���|�[�g�p�}�b�v�ړ�
//
//
//============================================================================================
//-----------------------------------------------------------------------------
/**
 * @brief	���Ȃʂ���p�}�b�v�J�ڃC�x���g�p���䃏�[�N
 */
//-----------------------------------------------------------------------------
typedef struct {
	int seq;							///<�V�[�P���X�ێ����[�N
	ANATYPE ana_type;					///<ANATYPE
	TCB_PTR tcb_jiki;					///<����TCB_PTR
	LOCATION_WORK next;					///<�}�b�v�J�ڐ�w��p���[�N
}EVENT_MAPCHG_WORK_ANANUKE;

static BOOL GMEVENT_MapChangeByAnanuke(GMEVENT_CONTROL * event);
static void EventCmd_Ananuke_FinishField(GMEVENT_CONTROL * event);
static void EventCmd_FadeOut_FinishField(GMEVENT_CONTROL * event);
static BOOL GMEVENT_Sub_Ananuke_FinishField(GMEVENT_CONTROL * event);
static void EventCmd_StartField_FadeInAnanuke(GMEVENT_CONTROL * event);
static BOOL GMEVENT_Sub_StartField_FadeInAnanuke(GMEVENT_CONTROL * event);
static void EventCmd_FieldFadeInAnanuke(GMEVENT_CONTROL * event);
static BOOL GMEVENT_Sub_WaitFadeAnanuke(GMEVENT_CONTROL * event);

//-----------------------------------------------------------------------------
/**
 * @brief	�������A���@��A�e���|�[�g�}�b�v�J�ڃC�x���g�`�F���W
 * @param	fsys		�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	escape		�J�ڐ�
 * @param	type		ANATYPE
 */
//-----------------------------------------------------------------------------
void EventChange_MapChangeByAnanuke(
	GMEVENT_CONTROL *event, const LOCATION_WORK *escape, u32 ana_type )
{
	EVENT_MAPCHG_WORK_ANANUKE * mcw =
		sys_AllocMemoryLo(HEAPID_WORLD, sizeof(EVENT_MAPCHG_WORK_ANANUKE));
	mcw->seq = 0;
	mcw->ana_type = ana_type;
	mcw->tcb_jiki = NULL;
	mcw->next = *escape;
	FieldEvent_Change( event, GMEVENT_MapChangeByAnanuke, mcw );
}

//-----------------------------------------------------------------------------
// @brief	�}�b�v�J�ڃC�x���g(���Ȃʂ��̂Ђ�)
//-----------------------------------------------------------------------------
static BOOL GMEVENT_MapChangeByAnanuke(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_MAPCHG_WORK_ANANUKE* mcw = FieldEvent_GetSpecialWork(event);
	LOCATION_WORK* location = &mcw->next;
	
	switch (mcw->seq) {
	case 0:
		Snd_EvMapChangeBgmFadeCheck( fsys, location->zone_id );	//�t�B�[���hBGM�t�F�[�h�A�E�g
		EventCmd_Ananuke_FinishField(event);	//�T�u�C�x���g�Ăяo��
		(mcw->seq) ++;
		break;
	case 1:
		//���@��Ԃ�񑫕��s�ɂ���
		Player_FormSet(fsys->player, HERO_FORM_NORMAL);
		//�T�u�C�x���g�Ăяo�������̃C�x���g�̓E�F�C�g
		EventCmd_MapChangeByLocation(event, &mcw->next);
		(mcw->seq) ++;
		break;
	case 2:
		if( Snd_FadeCheck() != 0 ){								//�T�E���h�t�F�[�h��
			break;
		}
		Snd_EvMapChangeBgmPlay( fsys, location->zone_id );		//�t�B�[���hBGM�Đ�

		//�e���|�[�g�E�������E���@��ŗL�t���O���Ƃ�����
		if (mcw->ana_type == ANATYPE_TEL){
			FldFlgInit_Teleport(fsys);
		}else if( (mcw->ana_type == ANATYPE_ANA)||
					(mcw->ana_type == ANATYPE_ANAHORI) ){
			FldFlgInit_Escape(fsys);
		}else{
			GF_ASSERT(0&&"�E�o���@���s��");
		}

		EventCmd_StartField_FadeInAnanuke(event);	//�T�u�C�x���g�Ăяo��
		(mcw->seq) ++;
		break;
	case 3:
		sys_FreeMemoryEz(mcw);
		return TRUE;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 * @brief	�C�x���g�[���R�}���h�F�t�B�[���h�v���Z�X�I���@���Ȃʂ��̂Ђ�
 * @param	event		�C�x���g���䃏�[�N�ւ̃|�C���^
 */
//-----------------------------------------------------------------------------
static void EventCmd_Ananuke_FinishField(GMEVENT_CONTROL * event)
{
	FieldEvent_Call(event, GMEVENT_Sub_Ananuke_FinishField, NULL);
}

//-----------------------------------------------------------------------------
// @brief	�t�B�[���h�I��(���Ȃʂ��̂Ђ�)
//-----------------------------------------------------------------------------
static BOOL GMEVENT_Sub_Ananuke_FinishField(GMEVENT_CONTROL * event)
{
	int * seq = FieldEvent_GetSeqWork(event);
	switch (*seq) {
	case 0:
		EventCmd_FinishFieldMap(event);
		(*seq) ++;
		break;
	case 1:
		return TRUE;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 * @brief	�C�x���g�[���R�}���h�F�t�B�[���h�v���Z�X�J�n���t�F�[�h�C���@���Ȃʂ��̂Ђ�
 * @param	event		�C�x���g���䃏�[�N�ւ̃|�C���^
 */
//-----------------------------------------------------------------------------
static void EventCmd_StartField_FadeInAnanuke(GMEVENT_CONTROL * event)
{
	EVENT_MAPCHG_WORK_ANANUKE * mcw = FieldEvent_GetSpecialWork(event);
	FieldEvent_Call(event, GMEVENT_Sub_StartField_FadeInAnanuke, mcw);
}

//-----------------------------------------------------------------------------
// @brief	�t�B�[���h�t�F�[�h�C���@���Ȃʂ��̂Ђ�
//-----------------------------------------------------------------------------
static BOOL GMEVENT_Sub_StartField_FadeInAnanuke(GMEVENT_CONTROL * event)
{
	int * seq = FieldEvent_GetSeqWork(event);
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_MAPCHG_WORK_ANANUKE* mcw = FieldEvent_GetSpecialWork(event);
	switch (*seq) {
	case 0:
		EventCmd_StartFieldMap(event);
		(*seq) ++;
		break;
	case 1:
		//�n���\��
		PlaceNameRequestByFsys(fsys);
		
		EventCmd_FieldFadeInAnanuke(event);
		(*seq) ++;
		break;
	case 2:
		return TRUE;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 * @brief	�C�x���g�[���R�}���h�F�t�F�[�h�C���@���Ȃʂ��̂Ђ�
 * @param	event		�C�x���g���䃏�[�N�ւ̃|�C���^
 */
//-----------------------------------------------------------------------------
static void EventCmd_FieldFadeInAnanuke(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_MAPCHG_WORK_ANANUKE * mcw = FieldEvent_GetSpecialWork(event);
	
	if (!GameSystem_CheckFieldProcExists(fsys)) {
		GF_ASSERT("mainproc���Ȃ��̂Ƀt�F�[�h�����s\n" && 0);
		return;
	}
	
	//�����ɃJ�b�g�C����p�̂��̂����Ă�@�t�F�[�h�C���͂��̒���
	{
		void *wk = EventWorkSet_AnanukeMapIn( fsys, HEAPID_FIELD, mcw->ana_type );
		FieldEvent_Call( event, GMEVENT_AnanukeMapIn, wk );
	}
}

//============================================================================================
//			���[�v�|�C���g
//============================================================================================
//-----------------------------------------------------------------------------
//          ���[�v�|�C���g��p�}�b�v�J�ڃC�x���g�p���䃏�[�N
//-----------------------------------------------------------------------------
typedef struct {
	int seq;							///<�V�[�P���X�ێ����[�N
    BOOL bEnd;
	LOCATION_WORK next;					///<�}�b�v�J�ڐ�w��p���[�N
} EVENT_MAPCHG_WARP_WORK;



//-----------------------------------------------------------------------------
// @brief	�}�b�v�J�ڃC�x���g
//-----------------------------------------------------------------------------
static BOOL GMEVENT_MapChangeWorpPoint(GMEVENT_CONTROL * event)
{
    FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
    EVENT_MAPCHG_WARP_WORK* mcw = FieldEvent_GetSpecialWork(event);
	LOCATION_WORK* location = &mcw->next;
	
	switch (mcw->seq) {
      case 0:
        StartJumpPointEffect( fsys, TRUE, &mcw->bEnd);
        mcw->seq++;
		break;
      case 1:
        if(mcw->bEnd){
			Snd_EvMapChangeBgmFadeCheck( fsys, location->zone_id );	//�t�B�[���hBGM�t�F�[�h�A�E�g
            EventCmd_FinishFieldMap(event);
            mcw->seq++;
        }
        break;
      case 2:
		//�T�u�C�x���g�Ăяo�������̃C�x���g�̓E�F�C�g
        EventCmd_MapChangeByLocation(event, &mcw->next);
        mcw->seq++;
        break;
      case 3:
		if( Snd_FadeCheck() != 0 ){									//�T�E���h�t�F�[�h��
			break;
		}
		Snd_EvMapChangeBgmPlay( fsys, location->zone_id );			//�t�B�[���hBGM�Đ�
		EventCmd_StartFieldMap(event);
        mcw->seq++;
		break;
      case 4:
        mcw->bEnd = FALSE;
        StartJumpPointEffect( fsys, FALSE, &mcw->bEnd);
        mcw->seq++;
		break;
      case 5:
        if(mcw->bEnd){
            mcw->seq++;
        }
        break;
      case 6:
		sys_FreeMemoryEz(mcw);
		return TRUE;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
// @brief	���[�v�|�C���g
//-----------------------------------------------------------------------------
void EventCmd_WarpPoint(FIELDSYS_WORK * fsys, int zone, int door_id)
{
	LOCATION_WORK next;
	EVENT_MAPCHG_WARP_WORK* mcw =
		sys_AllocMemoryLo(HEAPID_WORLD, sizeof(EVENT_MAPCHG_WARP_WORK));
    MI_CpuClear8(mcw, sizeof(EVENT_MAPCHG_WARP_WORK));
    
    SetLocation(&next, zone, door_id, 0, 0, Player_DirGet(fsys->player));

	mcw->next = next;
	FieldEvent_Set( fsys, GMEVENT_MapChangeWorpPoint, mcw );
}

///*************************************************************************************
//
//		������������������������������
//		�n��̃}�b�v�ړ�����
//
//
//
//
//		�n���̃}�b�v�ړ�����
//		������������������������������
//
///*************************************************************************************


//============================================================================================
//
//
//			�n���W�����v
//
//
//============================================================================================
static BOOL GMEVENT_UgJump(GMEVENT_CONTROL * event);	//�n�������n��
static BOOL UgChg_SubCall(GMEVENT_CONTROL * event, int no);

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
typedef struct {
	int seq;
	int subseq;
	int next_zone_id;
	int next_door_id;
	int next_x;
	int next_z;
	BOOL brightness;
    u16 saveResult;
	void * infowin;			// �Z�[�u���E�B���h�E�p�|�C���^
	GF_BGL_BMPWIN	win;	// ���b�Z�[�W�E�B���h�E
	STRBUF * str;			// �ʐM�J�n���b�Z�[�W�o�b�t�@
	u8	midx;				// ���b�Z�[�W�C���f�b�N�X
	BMPMENU_WORK * mw;		// �͂��E���������j���[���[�N
}EVENT_UGCHG_WORK;


//-----------------------------------------------------------------------------
/**
 * @brief	�n���ƒn����s��������C�x���g�p���[�N�̐���
 */
//-----------------------------------------------------------------------------
void * MakeUGChangeWork(FIELDSYS_WORK * fsys)
{
	EVENT_UGCHG_WORK * mcw;
	LOCATION_WORK * sp = Situation_GetSpecialLocation(SaveData_GetSituation(fsys->savedata));

	//�C�x���g����
	mcw = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(EVENT_UGCHG_WORK));
	mcw->seq = 0;
	mcw->subseq = 0;
	
	if (fsys->MapMode == MAP_MODE_UNDER){	//���ݒn���̏ꍇ
		//�n��փW�����v
		mcw->next_zone_id = sp->zone_id;
		mcw->next_door_id = DOOR_ID_JUMP_CODE;
		mcw->next_x = sp->grid_x;
		mcw->next_z = sp->grid_z;
	}else{
		SetLocationHere(sp, fsys);			//�؂�ւ��O�̏ꏊ���o���Ă���
		mcw->next_zone_id = ZONE_ID_UG;
		mcw->next_door_id = DOOR_ID_JUMP_CODE;
		//--�W�����v��̑I�o���@--
		//�u���b�N�����W8,8�̏ꏊ�ɃW�����v����悤�ɂ���
		//(�Y�z�T�C�Y�͒n���1/4)<<�m���ɂ��������W�����v�ł��镔���������l����Ƒ�E�\
		
		//30��30�n��̒Y�z�W�����v�L���u���b�N�͏c23�u���b�N�A��28�u���b�N
		//�i�c�J�n6�u���b�N�ƍŉ�1�u���b�N�͔͈͊O�B���͗��T�C�h1�u���b�N�����͈͊O�j
		//15��15�n���̃t���[���[�u�L���u���b�N�͏c13�u���b�N�A��14�u���b�N
		//�i�c�J�n2�u���b�N�͔閧��n�A���́A��1�u���b�N���ʂ��閧��n�j
		//���Ӑ}�Œn���t���[���[�u��1�u���b�N�ɂ̓W�����v�ł��Ȃ��悤�ɂ���Əc12�u���b�N
		//�n��c23�u���b�N�ł́A�v�Z�덷���o��̂ŁA�ŉ��͈͊O1�u���b�N���W�����v�ΏۂƂ���Əc24�u���b�N
		//����āA�n���W�����v��̃u���b�N�́A
		//�c�Ɋւ��ẮA
		//(���݂̒n��u���b�N-�c�I�t�Z�b�g6�u���b�N)/2+�閧��n�I�t�Z�b�g2�u���b�N+�W�����v����1�u���b�N
		//���Ɋւ��ẮA
		//(���݂̒n��u���b�N-���I�t�Z�b�g1�u���b�N)/2+�閧��n�I�t�Z�b�g1�u���b�N
		//
		//�W�����v�ꏊ�́A1�u���b�N�i32��32�j�̓����Ɍ������āA�㉺���E8�O���b�h�i�񂾏�
		{
			int x_ofs,z_ofs;
			int block_x,block_z;
			block_x = (sp->grid_x/32)-1;
			block_z = (sp->grid_z/32)-6;

			GF_ASSERT(block_x>=0);
			GF_ASSERT(block_z>=0);	
			
			if (block_x%2 == 0){
				x_ofs = 8;
			}else{
				x_ofs = 23;
			}
			if (block_z%2 == 0){
				z_ofs = 8;
			}else{
				z_ofs = 23;
			}

			block_x = (block_x/2)+1;
			block_z = (block_z/2)+2+1;
			mcw->next_x = block_x*32+x_ofs;
			mcw->next_z = block_z*32+z_ofs;
		}
	}
	return mcw;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void ChangeUnderGroundDirect(FIELDSYS_WORK * fsys)
{
	EVENT_UGCHG_WORK * mcw = MakeUGChangeWork(fsys);
	if (mcw == NULL) {
		return;
	}
	FieldEvent_Set(fsys, MapChg_GetUgChangeEvent(fsys), mcw);
}

//-----------------------------------------------------------------------------
/**
 * @brief	�C�x���g�F�n�ォ��n����
 */
//-----------------------------------------------------------------------------
enum {
	UGCHG_SEQ_SIO_INIT = 0,		// �ʐM�J�n���b�Z�[�W�Z�b�g
	UGCHG_SEQ_SIO_YNINIT,		// ���b�Z�[�W�҂����͂��E������������
	UGCHG_SEQ_SIO_YNWAIT,		// �͂��E�������҂�

	UGCHG_SEQ_REPORT_INIT,		// ���|�[�g������
	UGCHG_SEQ_REPORT_WAIT,		// ���|�[�g�I���҂�

	UGCHG_SEQ_CANCEL,			// �C�x���g�L�����Z��

	// ���G�t�F�N�g
	UGCHG_SEQ_0,
	UGCHG_SEQ_1,
	UGCHG_SEQ_2,
	UGCHG_SEQ_3,
	UGCHG_SEQ_4,
	UGCHG_SEQ_5,
	UGCHG_SEQ_6,
};

// �͂��E�������E�B���h�E�f�[�^
static const BMPWIN_DAT YesNoBmpDat = {
	FLD_MBGFRM_FONT, FLD_YESNO_WIN_PX, FLD_YESNO_WIN_PY,
	FLD_YESNO_WIN_SX, FLD_YESNO_WIN_SY, FLD_YESNO_WIN_PAL, FLD_YESNO_WIN_CGX
};


BOOL GMEVENT_GroundToUnderGround(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_UGCHG_WORK * mcw = FieldEvent_GetSpecialWork(event);
	
	switch (mcw->seq) {
	case UGCHG_SEQ_SIO_INIT:
		{
			MSGDATA_MANAGER * mman = MSGMAN_Create(
										MSGMAN_TYPE_DIRECT,ARC_MSG,NARC_msg_connect_dat,HEAPID_WORLD );
			mcw->str = MSGMAN_AllocString( mman, msg_connect_common_01 );
			MSGMAN_Delete( mman );
		}
		FldTalkBmpAdd( fsys->bgl, &mcw->win, FLD_MBGFRM_FONT );
		FieldTalkWinPut( &mcw->win, SaveData_GetConfig(fsys->savedata) );
		mcw->midx = FieldTalkMsgStart(
						&mcw->win, mcw->str, SaveData_GetConfig(fsys->savedata), 1 );
		mcw->seq = UGCHG_SEQ_SIO_YNINIT;
		break;

	case UGCHG_SEQ_SIO_YNINIT:
		if( FldTalkMsgEndCheck( mcw->midx ) == 1 ){
			STRBUF_Delete( mcw->str );
			MenuWinGraphicSet(
				fsys->bgl, FLD_MBGFRM_FONT, MENU_WIN_CGX_NUM, MENU_WIN_PAL, 0, HEAPID_WORLD );
			mcw->mw = BmpYesNoSelectInit(
						fsys->bgl, &YesNoBmpDat, MENU_WIN_CGX_NUM, MENU_WIN_PAL, HEAPID_WORLD );
			mcw->seq = UGCHG_SEQ_SIO_YNWAIT;
		}
		break;

	case UGCHG_SEQ_SIO_YNWAIT:
		switch( BmpYesNoSelectMain( mcw->mw, HEAPID_WORLD ) ){
		case 0:
			BmpTalkWinClear( &mcw->win, WINDOW_TRANS_ON );
			GF_BGL_BmpWinDel( &mcw->win );
			mcw->seq = UGCHG_SEQ_REPORT_INIT;
			break;

		case BMPMENU_CANCEL:
			BmpTalkWinClear( &mcw->win, WINDOW_TRANS_ON );
			GF_BGL_BmpWinDel( &mcw->win );
			mcw->seq = UGCHG_SEQ_CANCEL;
		}
		break;


	case UGCHG_SEQ_REPORT_INIT:		// ���|�[�g�Ăяo��
		if( SaveData_IsOverwritingOtherData(fsys->savedata) ) {
			EventCall_Script( event, SCRID_REPORT_NG, NULL, NULL );
		}else{
            // �n���ɓ���O�̃t���O����
            UnderGroundDataBeforeUGSave(fsys->savedata);
			//���|�[�g��񐶐�
			mcw->infowin = ReportInfo_Create( fsys, HEAPID_WORLD, FLD_MBGFRM_FONT );
			ReportInfo_WriteWindow( mcw->infowin );
			mcw->saveResult = FALSE;	// ���ʎ󂯎��p���[�N������
			EventCall_Script( event, SCRID_REPORT, NULL, &mcw->saveResult );
		}
		mcw->seq = UGCHG_SEQ_REPORT_WAIT;
		break;

	case UGCHG_SEQ_REPORT_WAIT:		// ���|�[�g�҂�
		if( SaveData_IsOverwritingOtherData(fsys->savedata) ){
			mcw->seq = UGCHG_SEQ_CANCEL;
		}else{
			ReportInfo_EraseWindow( mcw->infowin );
			ReportInfo_Delete( mcw->infowin );
			if( mcw->saveResult == FALSE ){		//�Z�[�u���Ă��Ȃ�
				mcw->seq = UGCHG_SEQ_CANCEL;
			}else{								//�Z�[�u����
				mcw->seq = UGCHG_SEQ_0;
			}
		}
		break;




	case UGCHG_SEQ_CANCEL:
		FieldOBJSys_MovePauseAllClear( fsys->fldobjsys );
		sys_FreeMemoryEz(mcw);
		return TRUE;

	case UGCHG_SEQ_0:
		Snd_BgmFadeOut( 0, BGM_FADE_UG_TIME );	//BGM�t�F�[�h�A�E�g
		(mcw->seq) ++;
		break;

	case UGCHG_SEQ_1:
		if (UgChg_SubCall(event, EFCT_UG_DOWN00)) {
			(mcw->seq) ++;
		}
		break;

	case UGCHG_SEQ_2:
		EventCmd_FinishFieldMap(event);
		(mcw->seq) ++;
		break;

	case UGCHG_SEQ_3:
		fsys->MapMode = MAP_MODE_UNDER;
        Overlay_Load( FS_OVERLAY_ID( ol_underground ), OVERLAY_LOAD_NOT_SYNCHRONIZE );
		//fsys->DivMapMode = DIV_MAP_MODE_UNDER;
		// �ʐM�J�n������
		CommFieldStateEnterUnderGround(fsys); // �ʐM�X�e�[�g��n���J�n�ɕύX
		EventCmd_MapChange(event,
								mcw->next_zone_id,
								DOOR_ID_JUMP_CODE,
								mcw->next_x,
								mcw->next_z,
								DIR_DOWN);

		(mcw->seq) ++;
		break;

	case UGCHG_SEQ_4:
		if( Snd_FadeCheck() != 0 ){				//BGM�t�F�[�h�҂�
			break;
		}
		Snd_SceneSet( SND_SCENE_DUMMY );		//�T�E���h�V�[���N���A
		Snd_FieldBgmClearSpecial( fsys );		//�}�b�v�������BGM�w��N���A

		EventCmd_StartFieldMap(event);
		(mcw->seq) ++;
		break;

	case UGCHG_SEQ_5:
		if (UgChg_SubCall(event, EFCT_UG_DOWN01)) {
			CommFieldStateArrivalUnderGround(); // �n���ɓ���
			fsys->UnderGroundRadar = UnderGround_RadarInit(fsys);		//�Y�z���[�_�[��ʂn�m
            ChangeBrightnessRequest(30,BRIGHTNESS_NORMAL,BRIGHTNESS_BLACK,
                                    PLANEMASK_BG0|PLANEMASK_BG3|PLANEMASK_OBJ,MASK_SUB_DISPLAY);
            (mcw->seq) ++;
		}
		break;
	case UGCHG_SEQ_6:
		if (IsFinishedBrightnessChg(MASK_SUB_DISPLAY)) {
            UgSecretBaseBootOn(TRUE); // �閧��n�̓����ON
            sys_FreeMemoryEz(mcw);
			return TRUE;
		}
		break;
	
	}
	return FALSE;
}
//-----------------------------------------------------------------------------
/**
 * @brief	�C�x���g�F�n������n���
 */
//-----------------------------------------------------------------------------
BOOL GMEVENT_UnderGroundToGround(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_UGCHG_WORK * mcw = FieldEvent_GetSpecialWork(event);
	int end_flg = 0;
		
	
	switch (mcw->seq) {
	case 0:
        // �ʐM�I��������
        UgSecretBaseBootOn(FALSE); // �閧��n�̓����OFF
        CommFieldStateExitUnderGround();  // �ʐM�X�e�[�g��n���I���ɕύX
		//�n���̎��̓��[�_�[���ɉ������
		UnderGround_RadarEnd(fsys->UnderGroundRadar);
		ChangeBrightnessRequest(30,BRIGHTNESS_BLACK,BRIGHTNESS_NORMAL,PLANEMASK_BG0,MASK_SUB_DISPLAY);
		mcw->seq++;
		break;
	case 1:
		if(IsFinishedBrightnessChg(MASK_SUB_DISPLAY)){
            if((fsys->UnderGroundRadar==NULL) && !CommIsInitialize()){
				Snd_BgmFadeOut( 0, BGM_FADE_UG_TIME );	//BGM�t�F�[�h�A�E�g
                mcw->seq++;
            }
        }
		break;
	case 2:
		if (UgChg_SubCall(event, EFCT_UG_UP00)) {
			(mcw->seq) ++;
		}
		break;
	case 3:
		EventCmd_FinishFieldMap(event);
		(mcw->seq) ++;
		break;

	case 4:
		fsys->MapMode = MAP_MODE_GROUND;
	    Overlay_UnloadID( FS_OVERLAY_ID(ol_underground) );
	//fsys->DivMapMode = DIV_MAP_MODE_GROUND;
		EventCmd_MapChange(event,
								mcw->next_zone_id,
								DOOR_ID_JUMP_CODE,
								mcw->next_x,
								mcw->next_z,
								DIR_DOWN);

		(mcw->seq) ++;
		break;
	case 5:
		if( Snd_FadeCheck() != 0 ){				//BGM�t�F�[�h�҂�
			break;
		}
		Snd_SceneSet( SND_SCENE_DUMMY );		//�T�E���h�V�[���N���A
		Snd_FieldBgmClearSpecial( fsys );		//�}�b�v�������BGM�w��N���A

		EventCmd_StartFieldMap(event);
		(mcw->seq) ++;
		break;
    case 6:
		if (UgChg_SubCall(event, EFCT_UG_UP01)) {
     		(mcw->seq) ++;
        }
        break;
    case 7:
        sys_FreeMemoryEz(mcw);
        return TRUE;
		break;
	
	}
	return FALSE;
}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
GMEVENT_FUNC MapChg_GetUgChangeEvent(const FIELDSYS_WORK * fsys)
{
	if (fsys->MapMode == MAP_MODE_GROUND) {
		return GMEVENT_GroundToUnderGround;
	} else if (fsys->MapMode == MAP_MODE_UNDER) {
		return GMEVENT_UnderGroundToGround;
	} else {
		GF_ASSERT_MSG(0,"Unknown MAP_MODE %d\n",fsys->MapMode);
		return NULL;
	}
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static BOOL UgChg_SubCall(GMEVENT_CONTROL * event, int no)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_UGCHG_WORK * mcw = FieldEvent_GetSpecialWork(event);
	BOOL	ret = FALSE;

	switch(mcw->subseq){
	case 0:		// �X�^�[�g
		mcw->brightness = 0;
		StartUnderGroundEffect(fsys, no, &mcw->brightness);
		mcw->subseq++;
		break;
	case 1:		// �I���҂�
		if(mcw->brightness){
			mcw->subseq = 0;
			ret = TRUE;
		}
		break;
	}
	return ret;
}


//============================================================================================
//
//
//			�C�x���g�R�}���h�F�n���`�n���̃}�b�v�ړ�
//
//
//============================================================================================
static void EventCmd_UgJump(GMEVENT_CONTROL * event, int zone_id, int door_id, int x, int z, int dir);
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
static BOOL GMEVENT_UgJump(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_UGCHG_WORK * mcw = FieldEvent_GetSpecialWork(event);
	int end_flg = 0;
		
	
	switch (mcw->seq) {
	case 0:
        UgSecretBaseBootOn(FALSE);
            //���[�_�[���ɉ������
		UnderGround_RadarEnd(fsys->UnderGroundRadar);
		CommStateJumpUnderGround();   // �ړ�����ꍇ�̒ʐM�֘A����
		mcw->seq++;
		break;

	case 1:
		if(fsys->UnderGroundRadar==NULL){
			mcw->seq++;
		}
		break;
	case 2:
		(mcw->seq) ++;
		break;
	case 3:
		EventCmd_FinishFieldMap(event);
		(mcw->seq) ++;
		break;
	case 4:
		
		EventCmd_UgJump(event,
						mcw->next_zone_id,
						DOOR_ID_JUMP_CODE,
						mcw->next_x,
						mcw->next_z,
						DIR_DOWN);

		(mcw->seq) ++;
		break;
	case 5:
		EventCmd_StartFieldMap(event);
		(mcw->seq) ++;
		break;
	case 6:
        UgSecretBaseBootOn(TRUE);
		CommStateJumpEndUnderGround(); // �ړ��I������ꍇ�̒ʐM�֘A����
		fsys->UnderGroundRadar = UnderGround_RadarInit(fsys);		//�Y�z���[�_�[��ʂn�m
		sys_FreeMemoryEz(mcw);
		return TRUE;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void JumpUnderGroundDirect(FIELDSYS_WORK * fsys, const int inX, const int inZ)
{
	EVENT_UGCHG_WORK * mcw;
	
	//�C�x���g����
	mcw = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(EVENT_UGCHG_WORK));
	mcw->seq = 0;
	mcw->subseq = 0;
	mcw->next_zone_id = ZONE_ID_UG;
	mcw->next_door_id = DOOR_ID_JUMP_CODE;
	//�����ŁA�W�����v������肵�܂�
	mcw->next_x = inX;
	mcw->next_z  = inZ;
	
	FieldEvent_Set(fsys, GMEVENT_UgJump, mcw);
	return;
}


//-----------------------------------------------------------------------------
/**
 * @brief	�T�u�C�x���g�F�}�b�v�J��(�n���`�n��)
 * @param	event	�C�x���g���䃏�[�N�ւ̃|�C���^
 * @retval	TRUE	�C�x���g�I��
 * @retval	FALSE	�C�x���g�p����
 *
 * �T�u�C�x���g��FieldEvent_Call�ŌĂяo�����ƂŎg�p����B
 * ���݂̃C�x���g���~���āA����ɃT�u�C�x���g����т����B
 * �T�u�C�x���g���I������ƌ��݂̃C�x���g���Ăяo�����B
 */
//-----------------------------------------------------------------------------
static BOOL GMEVENT_Sub_UgJump(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	SIMPLE_MAPCHG_WORK * smw = FieldEvent_GetSpecialWork(event);

	switch (smw->seq) {
	case 0:
		//--------�I������--------
		MapChg_FieldOBJ_Delete(fsys);
		(smw->seq) ++;
		break;
		
	case 1:
		//--------�J�n����--------
		MapChg_SetNewLocation(fsys, &smw->next);
        //--����X�N���v�g�̂ݎ��s  k.ohno & saito
        SpScriptSearch(fsys, SP_SCRID_FLAG_CHANGE);
        
		(smw->seq) ++;
		break;
		
	case 2:
		MapChg_FieldOBJ_Create(fsys);
		sys_FreeMemoryEz(smw);
		return TRUE;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 * @brief	�C�x���g�[���R�}���h�F�}�b�v�J��(�n���`�n��)
 * @param	event		�C�x���g���䃏�[�N�ւ̃|�C���^
 * @param	next		�J�ڐ���w�肷��LOCATION_WORK�^�ւ̃|�C���^
 */
//-----------------------------------------------------------------------------
void EventCmd_UgJumpByLocation(GMEVENT_CONTROL * event, const LOCATION_WORK * next)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	SIMPLE_MAPCHG_WORK * smw = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(SIMPLE_MAPCHG_WORK));
	if (GameSystem_CheckFieldProcExists(fsys)) {
		GF_ASSERT("mainproc������̂Ƀ}�b�v�J�ڏ���\n" && 0);
		return;
	}
	smw->seq = 0;
	smw->next = *next;
	FieldEvent_Call(event, GMEVENT_Sub_UgJump, smw);
}

//-----------------------------------------------------------------------------
/**
 * @brief	�C�x���g�[���R�}���h�F�}�b�v�J��(�n���`�n��)
 * @param	event		�C�x���g���䃏�[�N�ւ̃|�C���^
 * @param	zone_id		�J�ڐ�]�[��ID�w��
 * @param	door_id		�J�ڐ�o�����w��
 * @param	x			�J�ڐ�X���W�w��idoor_id == DOOR_ID_JUMP_CODE�̂Ƃ��̂ݗL���j
 * @param	z			�J�ڐ�Z���W�w��idoor_id == DOOR_ID_JUMP_CODE�̂Ƃ��̂ݗL���j
 * @param	dir			�o����ł̕����w��
 *
 */
//-----------------------------------------------------------------------------
static void EventCmd_UgJump(GMEVENT_CONTROL * event, int zone_id, int door_id, int x, int z, int dir)
{
	LOCATION_WORK next;
	SetLocation(&next, zone_id, door_id, x, z, dir);
	EventCmd_UgJumpByLocation(event, &next);
}



//============================================================================================
//
//
//			���j�I�����[���p�}�b�v�ړ�
//
//
//============================================================================================
//-----------------------------------------------------------------------------
//          ���j�I����p�}�b�v�J�ڃC�x���g�p���䃏�[�N
//-----------------------------------------------------------------------------
typedef struct {
	int seq;							///<�V�[�P���X�ێ����[�N
    BOOL bEnd;
	LOCATION_WORK next;					///<�}�b�v�J�ڐ�w��p���[�N
}EVENT_MAPCHG_UNION_WORK;



//-----------------------------------------------------------------------------
// @brief	�}�b�v�J�ڃC�x���g
//-----------------------------------------------------------------------------
static BOOL GMEVENT_UnionRoomOut(GMEVENT_CONTROL * event)
{
    FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
    EVENT_MAPCHG_UNION_WORK* emuw = FieldEvent_GetSpecialWork(event);
	int * seq = FieldEvent_GetSeqWork(event);
	
	switch (*seq) {
      case 0:
        //"�}�b�v�J�ڐ�p"�t�F�[�h�A�E�g �� BGM�Đ�
		{
			//�|�P�Z���Q�K�ƃ��j�I���͓���BGM�Ȃ̂ŃT�E���h���[�h�����͉������Ă��Ȃ��I
			LOCATION_WORK* location = &emuw->next;
			Snd_MapChangeFadeOutNextPlaySub( fsys, location->zone_id, BGM_FADE_ROOM_MODE );
		}
        StartJumpPointEffect( fsys, TRUE, &emuw->bEnd);
        (*seq)++;
		break;
      case 1:
        if(emuw->bEnd){
            EventCmd_FinishFieldMap(event);
            (*seq)++;
        }
        break;
      case 2:
		//�T�u�C�x���g�Ăяo�������̃C�x���g�̓E�F�C�g
        EventCmd_MapChangeByLocation(event, &emuw->next);
        (*seq)++;
        break;
      case 3:
		EventCmd_StartFieldMap(event);
        (*seq)++;
		break;
      case 4:
		EventCmd_FieldFadeIn(event);
        (*seq)++;
		break;
      case 5:
		sys_FreeMemoryEz(emuw);
		return TRUE;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
// �C�x���g�Z�b�g�F���j�I�����[���p�}�b�v�J�ځF������
//-----------------------------------------------------------------------------
void EventSet_UnionRoomMapChangeOut(FIELDSYS_WORK * fsys)
{
	LOCATION_WORK * sp = Situation_GetSpecialLocation(SaveData_GetSituation(fsys->savedata));
	EVENT_MAPCHG_UNION_WORK* emuw = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(EVENT_MAPCHG_UNION_WORK));
    MI_CpuClear8(emuw, sizeof(EVENT_MAPCHG_UNION_WORK));
    
	emuw->next = *sp;
	
	// ���j�I�����[���ʐM���
	Comm_UnionFinalize(fsys);
	// ���j�I�����[���\�������p���[�N���
	Comm_UnionRoomViewEnd(fsys->union_view);

	fsys->MapMode = MAP_MODE_GROUND;

	FieldEvent_Set(fsys, GMEVENT_UnionRoomOut, emuw);
	fsys->union_work = NULL;
}

//-----------------------------------------------------------------------------
// @brief	�}�b�v�J�ڃC�x���g
//-----------------------------------------------------------------------------
static BOOL GMEVENT_UnionRoomIn(GMEVENT_CONTROL * event)
{
    FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
    EVENT_MAPCHG_UNION_WORK* emuw = FieldEvent_GetSpecialWork(event);
	int * seq = FieldEvent_GetSeqWork(event);
	
	switch (*seq) {
      case 0:
        //"�}�b�v�J�ڐ�p"�t�F�[�h�A�E�g �� BGM�Đ�
		{
			//�|�P�Z���Q�K�ƃ��j�I���͓���BGM�Ȃ̂ŃT�E���h���[�h�����͉������Ă��Ȃ��I
			LOCATION_WORK* location = &emuw->next;
			Snd_MapChangeFadeOutNextPlaySub( fsys, location->zone_id, BGM_FADE_ROOM_MODE );
		}
		EventCmd_FieldFadeOut(event);
        (*seq)++;
		break;
      case 1:
		EventCmd_FinishFieldMap(event);
		(*seq)++;
        break;
      case 2:
		//�T�u�C�x���g�Ăяo�������̃C�x���g�̓E�F�C�g
        EventCmd_MapChangeByLocation(event, &emuw->next);
        (*seq)++;
        break;
      case 3:
		EventCmd_StartFieldMap(event);
        (*seq)++;
		break;
      case 4:
        emuw->bEnd = FALSE;
        StartJumpPointEffect( fsys, FALSE, &emuw->bEnd);
        (*seq)++;
		break;
      case 5:
        if(emuw->bEnd){
            (*seq)++;
        }
        break;
      case 6:
		sys_FreeMemoryEz(emuw);
		return TRUE;
	}
	return FALSE;
}

//-----------------------------------------------------------------------------
// �C�x���g�Z�b�g�F���j�I�����[���p�}�b�v�J�ځF����
//-----------------------------------------------------------------------------
void EventSet_UnionRoomMapChangeIn(FIELDSYS_WORK * fsys)
{
	LOCATION_WORK * sp = Situation_GetSpecialLocation(SaveData_GetSituation(fsys->savedata));

	SetLocationHere(sp, fsys);			//�؂�ւ��O�̏ꏊ���o���Ă���

	// ���j�I�����[���ʐM�J�n
	fsys->union_work = Comm_UnionRoomInit(fsys);
	// ���j�I�����[��OBJ����^�X�N�N��
	fsys->union_view = Comm_UnionRoomViewInit(fsys->union_work);

	fsys->MapMode = MAP_MODE_UNION;
	EventSet_EasyMapChange(fsys, ZONE_ID_UNION, DOOR_ID_JUMP_CODE, 9, 12, DIR_DOWN);
}

//-----------------------------------------------------------------------------
// �C�x���g�R�}���h�F���j�I�����[���p�}�b�v�J�ځF�o���藼���i�f�o�b�O�p�j
//-----------------------------------------------------------------------------
void EventSet_UnionRoomMapChange(FIELDSYS_WORK * fsys)
{
	if (fsys->location->zone_id == ZONE_ID_UNION) {
		EventSet_UnionRoomMapChangeOut(fsys);

		// �ʐM�Z�[�u�̑O�̂��܂��Ȃ�����
		SysFlag_CommCounterReset( SaveData_GetEventWork(fsys->savedata) );
	} else {
		// �ʐM�Z�[�u�̑O�̂��܂��Ȃ�
		SysFlag_CommCounterSet( SaveData_GetEventWork(fsys->savedata) );

		EventSet_UnionRoomMapChangeIn(fsys);
	}
}

#if 0
//-----------------------------------------------------------------------------
/// �C�x���g�R�}���h�F���j�I�����[���p�}�b�v�J�ځF������
//-----------------------------------------------------------------------------
void EventCmd_UnionRoomMapChangeOut(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	LOCATION_WORK * sp = Situation_GetSpecialLocation(SaveData_GetSituation(fsys->savedata));

	// ���j�I�����[���ʐM���
	Comm_UnionFinalize(fsys);
	// ���j�I�����[���\�������p���[�N���
	Comm_UnionRoomViewEnd(fsys->union_view);
	// UnionBoard���Ď����Ă邩��NULL�ɂ��Ȃ��ƌ듮�삷��
	fsys->union_view = NULL;

	fsys->MapMode = MAP_MODE_GROUND;
	EventCmd_EasyMapChangeByLocation(fsys->event, sp);
	fsys->union_work = NULL;
}
#endif
//-----------------------------------------------------------------------------
/// �C�x���g�R�}���h�F���j�I�����[���p�}�b�v�J�ځF����
//-----------------------------------------------------------------------------
void EventCmd_UnionRoomMapChangeIn(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	LOCATION_WORK * sp = Situation_GetSpecialLocation(SaveData_GetSituation(fsys->savedata));
	EVENT_MAPCHG_UNION_WORK* emuw = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(EVENT_MAPCHG_UNION_WORK));
    MI_CpuClear8(emuw, sizeof(EVENT_MAPCHG_UNION_WORK));

	SetLocationHere(sp, fsys);			//�؂�ւ��O�̏ꏊ���o���Ă���

	SetLocation(&emuw->next, ZONE_ID_UNION, DOOR_ID_JUMP_CODE, 8, 14, DIR_UP);

	// ���j�I�����[���ʐM�J�n
	fsys->union_work = Comm_UnionRoomInit(fsys);
	// ���j�I�����[��OBJ����^�X�N�N��
	fsys->union_view = Comm_UnionRoomViewInit(fsys->union_work);

	fsys->MapMode = MAP_MODE_UNION;
	FieldEvent_Call(event, GMEVENT_UnionRoomIn, emuw);
//	EventCmd_EasyMapChange(fsys->event, ZONE_ID_UNION, DOOR_ID_JUMP_CODE, 8, 14, DIR_UP);
}


//============================================================================================
//
//
//		�ʐM�ΐ핔���p�}�b�v�ړ�
//
//
//============================================================================================
//-----------------------------------------------------------------------------
// @brief	�}�b�v�J�ڃC�x���g(�ΐ핔���ɓ����p)
//-----------------------------------------------------------------------------
static BOOL GMEVENT_MapChangeColosseum(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_MAPCHG_WORK * mcw = FieldEvent_GetSpecialWork(event);
	LOCATION_WORK* location = &mcw->next;
	
	switch (mcw->seq) {
	case 0:
		Snd_SePlay( SEQ_SE_DP_KAIDAN2 );
		Snd_EvMapChangeBgmFadeCheck( fsys, location->zone_id );	//�t�B�[���hBGM�t�F�[�h�A�E�g
		EventCmd_FadeOut_FinishField(event);	//�T�u�C�x���g�Ăяo�������̃C�x���g�̓E�F�C�g
		(mcw->seq) ++;
		break;
	case 1:
		//�T�u�C�x���g�Ăяo�������̃C�x���g�̓E�F�C�g
		EventCmd_MapChangeByLocation(event, &mcw->next);
		(mcw->seq) ++;
		break;
	case 2:
		if( Snd_FadeCheck() != 0 ){								//�T�E���h�t�F�[�h��
			break;
		}
		Snd_EvMapChangeBgmPlay( fsys, location->zone_id );		//�t�B�[���hBGM�Đ�
		EventCmd_StartFieldMap(event);
		(mcw->seq) ++;
		break;
	case 3:
		sys_FreeMemoryEz(mcw);
		return TRUE;
	}
	return FALSE;
}


//-----------------------------------------------------------------------------
///	�C�x���g�R�}���h�F�ʐM�ΐ핔���p�}�b�v�J�ځF����
//-----------------------------------------------------------------------------
void EventCmd_ColosseumMapChangeIn(GMEVENT_CONTROL * event,
		int zone_id, int door_id, int x, int z, int dir)
{
    LOCATION_WORK next;
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	LOCATION_WORK * sp = Situation_GetSpecialLocation(SaveData_GetSituation(fsys->savedata));

	SetLocationHere(sp, fsys);			//�؂�ւ��O�̏ꏊ���o���Ă���

	fsys->MapMode = MAP_MODE_COLOSSEUM;	//�}�b�v���[�h��ʐM�ΐ핔���p��

    {
        EVENT_MAPCHG_WORK * mcw = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(EVENT_MAPCHG_WORK));
        
        SetLocation(&next, zone_id, door_id, x, z, dir);
        mcw->seq = 0;
        mcw->next = next;
        FieldEvent_Call(event, GMEVENT_MapChangeColosseum, mcw);
    }
}


//-----------------------------------------------------------------------------
///	�C�x���g�R�}���h�F�ʐM�ΐ핔���p�}�b�v�J�ځF������
//-----------------------------------------------------------------------------
void EventCmd_ColosseumMapChangeOut(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	LOCATION_WORK * sp = Situation_GetSpecialLocation(SaveData_GetSituation(fsys->savedata));
	fsys->MapMode = MAP_MODE_GROUND;		//�}�b�v���[�h��ʏ��
	EventCmd_EasyMapChangeByLocation(fsys->event, sp);
}

//-----------------------------------------------------------------------------
// �C�x���g�Z�b�g�F�ʐM�ΐ핔���p�}�b�v�J�ځF������
//-----------------------------------------------------------------------------
void EventSet_ColosseumMapChangeOut(FIELDSYS_WORK * fsys)
{
	LOCATION_WORK * sp = Situation_GetSpecialLocation(SaveData_GetSituation(fsys->savedata));

	fsys->MapMode = MAP_MODE_GROUND;
	EventSet_EasyMapChangeByLocation(fsys, sp);
}

#ifdef PM_DEBUG
//-----------------------------------------------------------------------------
//  �n���ɔC�ӂ̈ʒu�ɍ~���ׂɍ쐬 �f�o�b�O�p 2006.02.08
//-----------------------------------------------------------------------------
void Debug_ChangeUnderGroundDirect(FIELDSYS_WORK * fsys, int x, int z)
{
	EVENT_UGCHG_WORK * mcw = MakeUGChangeWork(fsys);
	if (mcw == NULL) {
		return;
	}
    mcw->next_x = x;
    mcw->next_z = z;
    mcw->seq = UGCHG_SEQ_0;
	FieldEvent_Set(fsys, MapChg_GetUgChangeEvent(fsys), mcw);
}
#endif //PM_DEBUG
