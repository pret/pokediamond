//============================================================================================
/**
 * @file	mapdata_warp.c
 * @brief	���[�v�p�f�[�^�֘A�\�[�X
 * @date	2005.12.19
 */
//============================================================================================

#include "common.h"

#include "fieldsys.h"
#include "field_common.h"
#include "mapdata_warp.h"

#include "mapdefine.h"
#include "fieldobj_code.h"		//DIR_UP DIR_DOWN
#include "ev_mapchange.h"		//DOOR_ID_JUMP_CODE

#include "sysflag.h"			//SysFlag_ArriveSet

//�������������͂��̃V���{����`
#include "../fielddata/warpdata/warpdata.h"

//============================================================================================
//============================================================================================
//------------------------------------------------------------------
//------------------------------------------------------------------
typedef struct {
	u16 room_id, room_gx, room_gz;
	u16 fld_id, fld_gx, fld_gz;
	u8 IsTeleportPos;
	u8 AutoSetArriveFlag;
	u16 arrive_id;
}WARPDATA;

//�������������͂��̃f�[�^��`
#include "../fielddata/warpdata/warpdata.c"


//============================================================================================
//============================================================================================
//------------------------------------------------------------------
/**
 * @brief	���[�vID�̐��K��
 * @param	warp_id		���[�vID
 * @return	int			���K���������[�vID
 *
 * �s���Ȓl�͕ϊ�����B1�I���W����0�I���W���ɕϊ�����B
 */
//------------------------------------------------------------------
static int RegulateWarpID(int warp_id)
{
	if(warp_id <= 0 || warp_id > NELEMS(WarpData)) {
		GF_ASSERT_MSG(0, "�s���ȃ��[�vID�i%d�j�ł��B\n", warp_id);
		warp_id = 1;		//���i�łł͕s���Ȓl�ł����삷��悤�ɕ␳����
	}
	warp_id --;		//1 origin --> 0 origin
	return warp_id;
}

//------------------------------------------------------------------
/**
 * @brief	���[�vID�̏����l���擾����
 */
//------------------------------------------------------------------
int WARPDATA_GetInitializeID(void)
{
	return 1;
}

//------------------------------------------------------------------
/**
 * @brief	���[�v�ꏊ�̎擾
 * @param	warp_id		���[�vID
 * @param	loc			�ꏊ���󂯎��LOCATION_WORK�ւ̃|�C���^
 */
//------------------------------------------------------------------
void WARPDATA_GetWarpLocation(int warp_id, LOCATION_WORK * loc)
{
	warp_id = RegulateWarpID(warp_id);

	loc->zone_id = WarpData[warp_id].fld_id;
	loc->door_id = DOOR_ID_JUMP_CODE;
	loc->grid_x = WarpData[warp_id].fld_gx;
	loc->grid_z = WarpData[warp_id].fld_gz;
	loc->dir = DIR_DOWN;
}

//------------------------------------------------------------------
/**
 * @brief	�����ꏊ�̎擾
 * @param	warp_id		���[�vID
 * @param	loc			�ꏊ���󂯎��LOCATION_WORK�ւ̃|�C���^
 */
//------------------------------------------------------------------
void WARPDATA_GetRevivalLocation(int warp_id, LOCATION_WORK * loc)
{
	warp_id = RegulateWarpID(warp_id);

	loc->zone_id = WarpData[warp_id].room_id;
	loc->door_id = DOOR_ID_JUMP_CODE;
	loc->grid_x = WarpData[warp_id].room_gx;
	loc->grid_z = WarpData[warp_id].room_gz;
	loc->dir = DIR_UP;
}

//------------------------------------------------------------------
/**
 * @brief	���[�vID�̎擾
 * @param	zone_id		�������鉮���̃]�[��ID
 * @retval	int			���[�vID�i�P�I���W���j
 * @retval	0			������Ȃ�����
 */
//------------------------------------------------------------------
int WARPDATA_SearchByRoomID(int zone_id)
{
	int i;
	for (i = 0; i < NELEMS(WarpData); i++) {
		if (WarpData[i].room_id == zone_id
				&& WarpData[i].IsTeleportPos) {
			return i + 1;
		}
	}
	return 0;
}

//------------------------------------------------------------------
/**
 * @brief	���[�vID�̎擾
 * @param	zone_id		��������t�B�[���h�̃]�[��ID
 * @retval	int			���[�vID�i�P�I���W���j
 * @retval	0			������Ȃ�����
 */
//------------------------------------------------------------------
int WARPDATA_SearchByFieldID(int zone_id)
{
	int i;
	for (i = 0; i < NELEMS(WarpData); i++) {
		if (WarpData[i].fld_id == zone_id
				&& WarpData[i].IsTeleportPos) {
			return i + 1;
		}
	}
	return 0;
}

//------------------------------------------------------------------
/**
 * @brief	���[�vID�̎擾�i�u������Ƃԁv�p�j
 * @param	zone_id		��������t�B�[���h�̃]�[��ID
 * @param	gx			��������X�ʒu�i�O���b�h�P�ʁj
 * @param	gz			��������Y�ʒu�i�O���b�h�P�ʁj
 * @retval	int			���[�vID�i�P�I���W���j
 * @retval	0			������Ȃ�����
 *
 * ����]�[�����ɓ�ӏ��u������Ƃԁv�̔�ѐ悪����̂ŁA
 * �^�E���}�b�v���Ԃ��u���b�N�P�ʂ̑I���ʒu�����ɂ���𔻕�
 * �ł���悤�ɂ��Ă���B
 */
//------------------------------------------------------------------
int WARPDATA_SearchForFly(int zone_id, int gx, int gz)
{
	int i;
	int blk_x = gx / 32;
	int blk_z = gz / 32;
	int id = 0;
	for (i = 0; i < NELEMS(WarpData); i++) {
		if (WarpData[i].fld_id == zone_id) {
			id = i + 1;
			if (blk_x == WarpData[i].fld_gx / 32 && blk_z == WarpData[i].fld_gz / 32) {
				return id;
			}
		}
	}
	return id;
}

//============================================================================================
//============================================================================================
//------------------------------------------------------------------
/**
 * @brief	�����t���O�̃Z�b�g
 * @param	fsys		�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	zone_id		�Z�b�g����ꏊ�̃]�[��ID
 */
//------------------------------------------------------------------
void ARRIVEDATA_SetArriveFlag( FIELDSYS_WORK * fsys, int zone_id)
{
	int i;
	for (i = 0; i < NELEMS(WarpData); i++) {
		if (WarpData[i].fld_id == zone_id && WarpData[i].AutoSetArriveFlag) {
			SysFlag_ArriveSet(SaveData_GetEventWork(fsys->savedata), WarpData[i].arrive_id);
			return;
		}
	}
}

//------------------------------------------------------------------
/**
 * @brief	�����t���O���Q�Ƃ���
 * @param	fsys		�t�B�[���h���䃏�[�N�ւ̃|�C���^
 * @param	warp_id		�ΏۂƂȂ�}�b�v�̃��[�vID
 * @retval	BOOL		TRUE�̂Ƃ��A�������Ƃ�����
 */
//------------------------------------------------------------------
BOOL ARRIVEDATA_GetArriveFlag(FIELDSYS_WORK * fsys, int warp_id)
{
	int reg_id = RegulateWarpID(warp_id);
	return SysFlag_ArriveGet(SaveData_GetEventWork(fsys->savedata), WarpData[reg_id].arrive_id);
}

