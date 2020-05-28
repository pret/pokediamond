//============================================================================================
/**
 * @file	zonedata.c
 * @brief	�]�[���ŗL�̊Ǘ��f�[�^
 * @author	tamada
 * @date	2005.08.05
 */
//============================================================================================

#include "common.h"

#include "fieldsys.h"

#include "zonedata.h"

#include "mapdefine.h"
#include "maptype.h"


#include "../fielddata/script/scr_seq.naix"

#include "../msgdata/msg.naix"

#include "../data/sound/sound_data.sadl"

#include "../fielddata/eventdata/zone_event.naix"

#include "../fielddata/encountdata/enc_data.naix"

#include "msgdata/msg_place_name.h"

#include "weather_sys.h"
#include "mapdata_weather_def.h"

#include "battle/attr_def.h"

#include "../fielddata/mm_list/mmlist_def.h"

//===========================================================================
//===========================================================================
//------------------------------------------------------------------
/**
 * @brief	�]�[�����Ɏ��f�[�^�̍\��
 */
//------------------------------------------------------------------
typedef struct{
	u8 area_id;							///<AREA_ID�̎w��
	u8 movemodel_id;					///<���샂�f���̎w��
	u16 matrix_id;						///<�}�b�v�}�g���b�N�X�̎w��
	u16 script_id;						///<�X�N���v�g�t�@�C���̃A�[�J�C�uID
	u16 sp_script_id;					///<����X�N���v�g�t�@�C���̃A�[�J�C�uID
	u16 msg_id;							///<���b�Z�[�W�t�@�C���̃A�[�J�C�uID
	u16 bgm_day_id;						///<BGM�w��i���j��ID
	u16 bgm_night_id;					///<BGM�w��i��j��ID
	u16 enc_data_id;					///<�G���J�E���g�w��
	u16 event_data_id;					///<�C�x���g�f�[�^�t�@�C���̃A�[�J�C�uID
	u16 placename_id;					///<�n�����b�Z�[�W�̂h�c
	u8 weather_id;						///<�V��w���ID
	u8 camera_id;						///<�J�����w���ID
	u8 maptype;							///<�}�b�v�^�C�v�̎w��(MAPTYPE��`�Q�Ɓj
	u8 battle_bg_type:4;				///<�퓬�w�i�̎w��
	u8 bicycle_flag:1;					///<���]�Ԃɏ��邩�ǂ���
	u8 dash_flag:1;						///<�_�b�V���ł��邩�ǂ���
	u8 escape_flag:1;					///<���Ȃʂ��ł��邩�ǂ���
	u8 fly_flag:1;
}ZONE_DATA;
//------------------------------------------------------------------
//------------------------------------------------------------------

enum {
	sp_scr_dummy = NARC_scr_seq_sp_dummy_bin,
	scr_dummy = NARC_scr_seq_dummy_bin,
	//sp_scr_dummy = NARC_scr_seq_sp_c01_bin,
	//scr_dummy = NARC_scr_seq_c01_bin,
	msg_dummy = NARC_msg_c01_dat,
	enc_dummy = 0xffff,
};

#include "../fielddata/maptable/maptable.dat"

static int ZoneData_GetMapType(int zone_id);
//===========================================================================
//===========================================================================
//------------------------------------------------------------------
//------------------------------------------------------------------
int ZoneData_CheckRange(int zone_id)
{
	if (zone_id >= NELEMS(ZoneData)) {
		GF_ASSERT_MSG(0, "%d/%d:zone_id error\n",zone_id,NELEMS(ZoneData)-1);
		return ZONE_ID_C01;
	}
	return zone_id;
}

//===========================================================================
//===========================================================================
//------------------------------------------------------------------
/**
 * @brief	�G���AID�̎擾
 * @param	zone_id		�]�[���w��
 * @return	u16			�G���A�w��
 */
//------------------------------------------------------------------
const u16 ZoneData_GetAreaID(int zone_id)
{
	zone_id = ZoneData_CheckRange(zone_id);
	return ZoneData[zone_id].area_id;
}

//------------------------------------------------------------------
//------------------------------------------------------------------
const u16 ZoneData_GetMoveModelID(int zone_id)
{
	zone_id = ZoneData_CheckRange(zone_id);
	return ZoneData[zone_id].movemodel_id;
}

//------------------------------------------------------------------
/**
 * @brief	�}�b�v�}�g���b�N�XID�̎擾
 * @param	zone_id		�]�[���w��
 * @return	u16			�}�b�v�}�g���b�N�X�w��
 */
//------------------------------------------------------------------
const u16 ZoneData_GetMatrixID(int zone_id)
{
	u16 mtx_id;
	zone_id = ZoneData_CheckRange(zone_id);
	mtx_id = ZoneData[zone_id].matrix_id;
	if (mtx_id == MATRIX_ID_DUN0514){
		if (CasetteVersion == VERSION_PEARL) {
			mtx_id = MATRIX_ID_DUN0515;
		}
	}
	return mtx_id;
}
//------------------------------------------------------------------
/**
 * @brief	���b�Z�[�W�A�[�J�C�uID�̎擾
 * @param	zone_id		�]�[���w��
 * @return	u32			���b�Z�[�W�A�[�J�C�uID
 */
//------------------------------------------------------------------
u32 ZoneData_GetMsgArchiveID(int zone_id)
{
	zone_id = ZoneData_CheckRange(zone_id);
	return ZoneData[zone_id].msg_id;
}

//------------------------------------------------------------------
/**
 * @brief	�X�N���v�g�A�[�J�C�uID�̎擾
 * @param	zone_id		�]�[���w��
 * @return	u32			�X�N���v�g�A�[�J�C�uID
 */
//------------------------------------------------------------------
u32 ZoneData_GetScriptArchiveID(int zone_id)
{
	zone_id = ZoneData_CheckRange(zone_id);
	return ZoneData[zone_id].script_id;
}
//------------------------------------------------------------------
/**
 * @brief	�X�N���v�g�A�[�J�C�uID�̎擾
 * @param	zone_id		�]�[���w��
 * @return	u32			�X�N���v�g�A�[�J�C�uID
 */
//------------------------------------------------------------------
u32 ZoneData_GetSpScriptArchiveID(int zone_id)
{
	zone_id = ZoneData_CheckRange(zone_id);
	return ZoneData[zone_id].sp_script_id;
}


//------------------------------------------------------------------
/**
 * @brief	BGM�w��̎擾
 * @param	zone_id		�]�[���w��
 * @return	u16			BGM�w��
 */
//------------------------------------------------------------------
u16 ZoneData_GetDayBGMID(int zone_id)
{
	zone_id = ZoneData_CheckRange(zone_id);
	return ZoneData[zone_id].bgm_day_id;
}

//------------------------------------------------------------------
/**
 * @brief	BGM�w��̎擾
 * @param	zone_id		�]�[���w��
 * @return	u16			BGM�w��
 */
//------------------------------------------------------------------
u16 ZoneData_GetNightBGMID(int zone_id)
{
	zone_id = ZoneData_CheckRange(zone_id);
	return ZoneData[zone_id].bgm_night_id;
}

//------------------------------------------------------------------
/**
 * @brief	�G���J�E���g�t���O�̎擾
 * @param	zone_id		�]�[���w��
 * @return	TRUE�F�G���J�E���g�f�[�^����AFALSE:�G���J�E���g�f�[�^�Ȃ�
 */
//------------------------------------------------------------------
BOOL ZoneData_GetEncountFlag (int zone_id)
{
	zone_id = ZoneData_CheckRange(zone_id);
	return (ZoneData[zone_id].enc_data_id != enc_dummy);
}

//------------------------------------------------------------------
/**
 * @brief	�G���J�E���g�A�[�J�C�uID�̎擾
 * @param	zone_id		�]�[���w��
 * @return	u32	�A�[�J�C�uID�w��
 */
//------------------------------------------------------------------
u32 ZoneData_GetEncountArchiveID(int zone_id)
{
	zone_id = ZoneData_CheckRange(zone_id);
	return ZoneData[zone_id].enc_data_id;
}

//------------------------------------------------------------------
/**
 * @brief	�C�x���g�f�[�^�A�[�J�C�uID�̎擾
 * @param	zone_id		�]�[���w��
 * @return	u32			�C�x���g�f�[�^�A�[�J�C�uID
 */
//------------------------------------------------------------------
u32 ZoneData_GetEventID(int zone_id)
{
	zone_id = ZoneData_CheckRange(zone_id);
	return ZoneData[zone_id].event_data_id;
}

//------------------------------------------------------------------
/**
 * @brief	�n�����b�Z�[�W�w��ID�̎擾
 * @param	zone_id		�]�[���w��
 * @return	u32			�n�����b�Z�[�W�w��h�c
 */
//------------------------------------------------------------------
u32 ZoneData_GetPlaceNameID(int zone_id)
{
	zone_id = ZoneData_CheckRange(zone_id);
	return ZoneData[zone_id].placename_id;
}

//------------------------------------------------------------------
/**
 * @brief	�V��w��ID�̎擾
 * @param	zone_id		�]�[���w��
 * @return	u32			�V��w���ID
 */
//------------------------------------------------------------------
u32 ZoneData_GetWeatherID(int zone_id)
{
	zone_id = ZoneData_CheckRange(zone_id);
	return ZoneData[zone_id].weather_id;
}

//------------------------------------------------------------------
/**
 * @brief	�J�����w��ID�̎擾
 * @param	zone_id		�]�[���w��
 * @return	u32			�J�����w���ID
 */
//------------------------------------------------------------------
u32 ZoneData_GetCameraID(int zone_id)
{
	zone_id = ZoneData_CheckRange(zone_id);
	return ZoneData[zone_id].camera_id;
}

//------------------------------------------------------------------
/**
 * @brief	�J�����w��ID�̎擾
 * @param	zone_id		�]�[���w��
 * @return	u32			�퓬�w�i�w���ID
 */
//------------------------------------------------------------------
u32 ZoneData_GetBattleBGID(int zone_id)
{
	zone_id = ZoneData_CheckRange(zone_id);
	return ZoneData[zone_id].battle_bg_type;
}
//------------------------------------------------------------------
/**
 * @brief	���Ȃʂ����ł��邩�ǂ����̃t���O�擾
 * @param	zone_id		�]�[���w��
 * @return	BOOL		�ł��邩�ǂ���
 */
//------------------------------------------------------------------
BOOL ZoneData_GetEnableEscapeFlag(int zone_id)
{
	zone_id = ZoneData_CheckRange(zone_id);
	return ZoneData[zone_id].escape_flag;
}
//------------------------------------------------------------------
/**
 * @brief	������ƂԁE�e���|�[�g���ł��邩�ǂ����̃t���O�擾
 * @param	zone_id		�]�[���w��
 * @return	BOOL		�ł��邩�ǂ���
 */
//------------------------------------------------------------------
BOOL ZoneData_GetEnableFlyFlag(int zone_id)
{
	zone_id = ZoneData_CheckRange(zone_id);
	return ZoneData[zone_id].fly_flag;
}

//------------------------------------------------------------------
/**
 * @brief	�_�b�V�����ł��邩�ǂ����̃t���O�擾
 * @param	zone_id		�]�[���w��
 * @return	BOOL		�ł��邩�ǂ���
 */
//------------------------------------------------------------------
BOOL ZoneData_GetEnableDashFlag(int zone_id)
{
	zone_id = ZoneData_CheckRange(zone_id);
	return ZoneData[zone_id].dash_flag;
}
//------------------------------------------------------------------
/**
 * @brief	���Ă񂵂�������邩�ǂ����̃t���O�擾
 * @param	zone_id		�]�[���w��
 * @return	BOOL		�ł��邩�ǂ���
 */
//------------------------------------------------------------------
BOOL ZoneData_GetEnableBicycleFlag(int zone_id)
{
	zone_id = ZoneData_CheckRange(zone_id);
	return ZoneData[zone_id].bicycle_flag;
}
//------------------------------------------------------------------
/**
 * @brief	�}�b�v�^�C�v�̎擾
 * @param	zone_id		�]�[���w��
 * @return	int			�}�b�v�^�C�v�w��ID
 *
 * �}�b�v�^�C�v���g�p��������͕��U������ƌ�X�̃^�C�v�ǉ��Ȃǂ�
 * ��ςɂȂ�̂ł��̊֐��͊O�����J���Ă��Ȃ�
 */
//------------------------------------------------------------------
static int ZoneData_GetMapType(int zone_id)
{
	zone_id = ZoneData_CheckRange(zone_id);
	return ZoneData[zone_id].maptype;
}
//============================================================================================
//
//
//	�]�[��ID�ɂ��e�픻�胍�W�b�N
//
//
//============================================================================================
//------------------------------------------------------------------
/**
 * @brief	�e���|�[�g���g���邩�ǂ����̃`�F�b�N
 * @param	zone_id		�]�[���w��
 * @retval	BOOL	TRUE�̂Ƃ��A�e���|�[�g���g����
 */
//------------------------------------------------------------------
BOOL ZoneData_GetEnableTeleportFlag(int zone_id)
{
	if (ZoneData_GetEnableFlyFlag(zone_id) == FALSE) {
		return FALSE;
	}
	return (ZoneData_GetMapType(zone_id) != MAPTYPE_TOWN);
}

//------------------------------------------------------------------
/**
 * @brief	�t�B�[���h���ǂ����̃`�F�b�N
 * @param	zone_id		�]�[���w��
 * @retval	BOOL	TRUE�̂Ƃ��A�t�B�[���h�i�����ł��_���W�����ł��Ȃ��j
 */
//------------------------------------------------------------------
BOOL ZoneData_IsSinouField(int zone_id)
{
	return (ZoneData_GetMatrixID(zone_id) == MATRIX_ID_FIELD);
}

//------------------------------------------------------------------
/**
 * @brief	�|�P�Z�����ǂ����̃`�F�b�N
 * @param	zone_id		�]�[���w��
 * @retval	BOOL	TRUE�̂Ƃ��A�|�P�Z��
 */
//------------------------------------------------------------------
BOOL ZoneData_IsPokecen(int zone_id)
{
	return (ZoneData_GetMapType(zone_id) == MAPTYPE_POKECEN);
}

//------------------------------------------------------------------
/**
 * @brief	�_���W�������ǂ����̃`�F�b�N
 * @param	zone_id		�]�[���w��
 * @retval	BOOL	TRUE�̂Ƃ��A�_���W����
 */
//------------------------------------------------------------------
BOOL ZoneData_IsDungeon(int zone_id)
{
	return (ZoneData_GetMapType(zone_id) == MAPTYPE_CAVE);
}

//------------------------------------------------------------------
/**
 * @brief	�������ǂ����̃`�F�b�N
 * @param	zone_id		�]�[���w��
 * @retval	BOOL	TRUE�̂Ƃ��A����
 */
//------------------------------------------------------------------
BOOL ZoneData_IsRoom(int zone_id)
{
	return ( (ZoneData_GetMapType(zone_id) == MAPTYPE_ROOM) ||
			 (ZoneData_GetMapType(zone_id) == MAPTYPE_POKECEN) );
}

//------------------------------------------------------------------
/**
 * @brief	���O���ǂ����̃`�F�b�N
 * @param	zone_id		�]�[���w��
 * @retval	BOOL	TRUE�̂Ƃ��A���O
 */
//------------------------------------------------------------------
BOOL ZoneData_IsOutDoor(int zone_id)
{
	return ( (ZoneData_GetMapType(zone_id) == MAPTYPE_TOWN) ||
			 (ZoneData_GetMapType(zone_id) == MAPTYPE_ROAD) );
}

//------------------------------------------------------------------
/**
 * @brief	�ʐM�𗘗p����\���̂���]�[�����ǂ����`�F�b�N
 *
 * @param   zone_id		�]�[���w��
 *
 * @retval  BOOL		TRUE�̂Ƃ��A�ʐM�𗘗p���邩��
 */
//------------------------------------------------------------------
BOOL ZoneData_IsCommPlayableZone(int zone_id)
{
	if( ZoneData_IsPokecen(zone_id) )
	{
		return TRUE;
	}


	return FALSE;
}

//------------------------------------------------------------------
/**
 * @brief	���j�I�����[�����ǂ����̃`�F�b�N
 * @param   zone_id		�]�[���w��
 * @return	BOOL	TRUE�̂Ƃ��A���j�I�����[��
 */
//------------------------------------------------------------------
BOOL ZoneData_IsUnionRoom(const int zone_id)
{
	return (zone_id == ZONE_ID_UNION);
}

//------------------------------------------------------------------
/**
 * @brief	����ނ�G���J�E���g����]�[�����ǂ����`�F�b�N
 *
 * @param   zone_id		�]�[���w��
 *
 * @retval  BOOL		TRUE�̂Ƃ��A����ނ�G���J�E���g�]�[��
 */
//------------------------------------------------------------------
BOOL ZoneData_IsSpFishingZone(const int zone_id)
{
	return (zone_id == ZONE_ID_D05R0113);
}

//------------------------------------------------------------------
/**
 * @brief	���R�G���J�E���g����]�[�����ǂ����`�F�b�N
 *
 * @param   zone_id		�]�[���w��
 *
 * @retval  BOOL		TRUE�̂Ƃ��A���R�G���J�E���g�]�[��
 */
//------------------------------------------------------------------
BOOL ZoneData_IsHillBackZone(const int zone_id)
{
	return (zone_id == ZONE_ID_D23R0101);
}

//------------------------------------------------------------------
/**
 * @brief	���R�������ǂ����̃`�F�b�N
 * @param   zone_id		�]�[���w��
 * @retval	BOOL		TRUE�̂Ƃ��A���R����
 */
//------------------------------------------------------------------
BOOL ZoneData_IsNaturalPark(const int zone_id)
{
	return (zone_id == ZONE_ID_D11R0101);
}

//------------------------------------------------------------------
/**
 * @brief	�Ă񂩂��̂ӂ����g����]�[�����ǂ����`�F�b�N
 *
 * @param   zone_id		�]�[���w��
 *
 * @retval  BOOL		TRUE�̂Ƃ��A�g����]�[��
 */
//------------------------------------------------------------------
BOOL ZoneData_IsUseTenkainofueZone(const int zone_id)
{
	return (zone_id == ZONE_ID_D05R0114);
}

//------------------------------------------------------------------
/**
 * @brief	�|�P�Z���QF�ɂ��邩�ǂ����̃`�F�b�N
 * @param   zone_id		�]�[���w��
 */
//------------------------------------------------------------------
BOOL ZoneData_IsPokecen2F(const int zone_id)
{
	static const u16 pc2f[] = {
		ZONE_ID_T02PC0102,
		ZONE_ID_T03PC0102,
		ZONE_ID_T04PC0102,
		ZONE_ID_T05PC0102,
		ZONE_ID_T06PC0102,
		ZONE_ID_T07PC0102,
		ZONE_ID_C01PC0102,
		ZONE_ID_C02PC0102,
		ZONE_ID_C03PC0102,
		ZONE_ID_C03PC0102,
		ZONE_ID_C04PC0102,
		ZONE_ID_C05PC0102,
		ZONE_ID_C06PC0102,
		ZONE_ID_C07PC0102,
		ZONE_ID_C08PC0102,
		ZONE_ID_C09PC0102,
		ZONE_ID_C10PC0102,
		ZONE_ID_C11PC0102,
	};

	int index;
	for (index = 0; index < NELEMS(pc2f); index++ ) {
		if (zone_id == pc2f[index]) {
			return TRUE;
		}
	}
	return FALSE;

}

//============================================================================================
//
//
//
//	�}�b�v���Ƃ̌ʃf�[�^�擾
//
//
//
//============================================================================================
//-----------------------------------------------------------------------------
/**
 * @brief	�ꏊ�i���̏���Ԃ�
 * @param	zone_id		�]�[���w��ID
 * @retval	SHINKA_NONE
 * @retval	SHINKA_PLACE_TENGANZAN
 * @retval	SHINKA_PLACE_KOKE
 * @retval	SHINKA_PLACE_ICE
 */
//-----------------------------------------------------------------------------
int ZoneData_GetShinkaPlaceID(int zone_id)
{
	static const u16 tbl[] = {
		ZONE_ID_R217,		SHINKA_PLACE_ICE,
		ZONE_ID_D03R0101,	SHINKA_PLACE_KOKE,
		ZONE_ID_D05R0101,	SHINKA_PLACE_TENGANZAN,
		ZONE_ID_D05R0102,	SHINKA_PLACE_TENGANZAN,
		ZONE_ID_D05R0103,	SHINKA_PLACE_TENGANZAN,
		ZONE_ID_D05R0104,	SHINKA_PLACE_TENGANZAN,
		ZONE_ID_D05R0105,	SHINKA_PLACE_TENGANZAN,
		ZONE_ID_D05R0106,	SHINKA_PLACE_TENGANZAN,
		ZONE_ID_D05R0107,	SHINKA_PLACE_TENGANZAN,
		ZONE_ID_D05R0108,	SHINKA_PLACE_TENGANZAN,
		ZONE_ID_D05R0109,	SHINKA_PLACE_TENGANZAN,
		ZONE_ID_D05R0110,	SHINKA_PLACE_TENGANZAN,
		ZONE_ID_D05R0111,	SHINKA_PLACE_TENGANZAN,
		ZONE_ID_D05R0112,	SHINKA_PLACE_TENGANZAN,
		ZONE_ID_D05R0113,	SHINKA_PLACE_TENGANZAN,
		ZONE_ID_D05R0114,	SHINKA_PLACE_TENGANZAN,
		ZONE_ID_D05R0115,	SHINKA_PLACE_TENGANZAN,
	};
	int i;
	for (i = 0; i < NELEMS(tbl); i += 2) {
		if (tbl[i] == zone_id) {
			return tbl[i + 1];
		}
	}
	return SHINKA_NONE;
}

