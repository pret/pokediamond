//=============================================================================
/**
 * @file	gym_init.c
 * @bfief	�W���d�|���������Ƃ�
 * @author	Nozomu Saito
 *
 */
//=============================================================================
#include "common.h"
#include "fieldsys.h"
#include "fieldmap_work.h"
#include "system/snd_tool.h"
#include "include/savedata/gimmickwork.h"
#include "../fielddata/build_model/build_model_id.h"

#include "field_gimmick_def.h"
#include "sysflag.h"

#include "gym_def.h"

#include "gym_local.h"
#include "gym_init.h"

static void SetBit(const u8 inBit, const u8 inVal, int *outData);

//�|���t�g�f�t�H���g�ʒu���
//0:�f�t�H���g�ʒu�@1:�ړ���	�㉺�͉��A��O���͉��A���E�͍����f�t�H���g
static const u8 SteelLiftDefault[STEEL_LIFT_MAX] =
{
	0, 0, 0, 0, 0, 0,
	1, 1, 1, 0, 1,
	1, 0, 0, 0, 0, 1, 0, 1,
	1, 0, 1, 0,1
};

//������ʒu���
//0:�f�t�H���g�ʒu�@1:�ړ���	�����f�t�H���g
static const u8 WallDefault[COMBAT_WALL_MAX] =
{
	0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1,
};

//---------------------------------------------------------------------------
/**
 * @brief	���W��:������
 * 
 * @param	fsys	�t�B�[���h�V�X�e���|�C���^
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GYM_InitWaterGym(FIELDSYS_WORK *fsys)
{	
	GIMMICKWORK *work;
	WATER_GYM_WORK *water_gym_work;
	work = SaveData_GetGimmickWork(GameSystem_GetSaveData(fsys));
	GIMMICKWORK_Assign(work, FLD_GIMMICK_WATER_GYM);

	water_gym_work = (WATER_GYM_WORK*)GIMMICKWORK_Get(work, FLD_GIMMICK_WATER_GYM);
	water_gym_work->Water = GYM_WATER_LV2;
}

//---------------------------------------------------------------------------
/**
 * @brief	�S�[�X�g�W��:������
 * 
 * @param	fsys	�t�B�[���h�V�X�e���|�C���^
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GYM_InitGhostGym(FIELDSYS_WORK *fsys)
{	
	GIMMICKWORK *work;
	GHOST_GYM_WORK *ghost_gym_work;
	work = SaveData_GetGimmickWork(GameSystem_GetSaveData(fsys));
	GIMMICKWORK_Assign(work, FLD_GIMMICK_GHOST_GYM);

	ghost_gym_work = (GHOST_GYM_WORK*)GIMMICKWORK_Get(work, FLD_GIMMICK_GHOST_GYM);

	//�����Ă����ꏊ��Z���W�ŁA���t�g�̈ʒu������i���邱�Ƃɂ���j
	//���n�`�Ɉˑ���������Ȃ̂ŁA�n�`���ς�����ꍇ�͒��ӂ��K�v
	if (fsys->location->grid_z == GHOST_LIFT_ROOM_START_Z){
/**		
		MYSTATUS *my_st  = SaveData_GetMyStatus(GameSystem_GetSaveData(fsys));
		//�V�i���I�i�s�ɂ���āA���t�g�̈ʒu�𕪊�(�b7�g�o���Ƃb6�m���Z�̃o�b�W�t���O���`�F�b�N)
		if ( MyStatus_GetBadgeFlag(my_st, BADGE_ID_C07) &&
				MyStatus_GetBadgeFlag(my_st, BADGE_ID_C06) ){
			ghost_gym_work->Lift = GYM_GHOST_LIFT_LV1;	//���t�g���i�W������j
		}else{
			ghost_gym_work->Lift = GYM_GHOST_LIFT_LV2;	//���t�g��i�W������s�j
		}
*/	//<<�V�i���I�ύX�ɂ��A���̏����͕s�v�ɂȂ�܂����@20060626
		//�V�i���I�i�s�ɂ���āA���t�g�̈ʒu�𕪊�(�J���i�M�ŃM���K�c�{�X�Ƙb�����Ă��邩���`�F�b�N)
		if ( SysFlag_T05GingaEventCheck( SaveData_GetEventWork( fsys->savedata ) ) ){
			ghost_gym_work->Lift = GYM_GHOST_LIFT_LV1;	//���t�g���i�W������j
		}else{
			ghost_gym_work->Lift = GYM_GHOST_LIFT_LV2;	//���t�g��i�W������s�j
		}
	}else{
		ghost_gym_work->Lift = GYM_GHOST_LIFT_LV2;
	}
}

//---------------------------------------------------------------------------
/**
 * @brief	�|�W��:������
 * 
 * @param	fsys	�t�B�[���h�V�X�e���|�C���^
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GYM_InitSteelGym(FIELDSYS_WORK *fsys)
{	
	GIMMICKWORK *work;
	STEEL_GYM_WORK *steel_gym_work;
	work = SaveData_GetGimmickWork(GameSystem_GetSaveData(fsys));
	GIMMICKWORK_Assign(work, FLD_GIMMICK_STEEL_GYM);

	steel_gym_work = (STEEL_GYM_WORK*)GIMMICKWORK_Get(work, FLD_GIMMICK_STEEL_GYM);

	//���t�g�ʒu������
	{
		int i;
		for(i=0;i<STEEL_LIFT_MAX;i++){
			SetBit(i,SteelLiftDefault[i],&steel_gym_work->LiftPosBit);
		}
	}
}

//---------------------------------------------------------------------------
/**
 * @brief	�i���W��:������
 * 
 * @param	fsys	�t�B�[���h�V�X�e���|�C���^
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GYM_InitCombatGym(FIELDSYS_WORK *fsys)
{	
	GIMMICKWORK *work;
	COMBAT_GYM_WORK *combat_gym_work;
	work = SaveData_GetGimmickWork(GameSystem_GetSaveData(fsys));
	GIMMICKWORK_Assign(work, FLD_GIMMICK_COMBAT_GYM);

	combat_gym_work = (COMBAT_GYM_WORK*)GIMMICKWORK_Get(work, FLD_GIMMICK_COMBAT_GYM);

	//������ʒu������
	{
		int i;
		for(i=0;i<COMBAT_WALL_MAX;i++){
			SetBit(i,WallDefault[i],&combat_gym_work->WallPosBit);
		}
	}
}

//---------------------------------------------------------------------------
/**
 * @brief	�d�C�W��:������
 * 
 * @param	fsys	�t�B�[���h�V�X�e���|�C���^
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void GYM_InitElecGym(FIELDSYS_WORK *fsys, const u8 inRoomNo)
{	
	GIMMICKWORK *work;
	ELEC_GYM_WORK *elec_gym_work;
	u16 start_z;

	GF_ASSERT(inRoomNo<ELEC_ROOM_MAX&&"ERROR:ElecGym RoomMaxOver");
	
	work = SaveData_GetGimmickWork(GameSystem_GetSaveData(fsys));
	GIMMICKWORK_Assign(work, FLD_GIMMICK_ELEC_GYM);

	elec_gym_work = (ELEC_GYM_WORK*)GIMMICKWORK_Get(work, FLD_GIMMICK_ELEC_GYM);

	elec_gym_work->RoomNo = inRoomNo;
	
	switch(elec_gym_work->RoomNo){
	case ELEC_GYM_ROOM1:			//1������
		elec_gym_work->GearRotateCode = GEAR_ROT_ST_180;
		start_z = ELEC_ROOM1_START_Z;
		break;
	case ELEC_GYM_ROOM2:			//2������
		elec_gym_work->GearRotateCode = GEAR_ROT_ST_90;
		start_z = ELEC_ROOM2_START_Z;
		break;
	case ELEC_GYM_ROOM3:			//3�����ڂ͍s���~�܂�Ȃ̂ŁA�ǂ�ȏꍇ�ł��f�t�H���g���Z�b�g
		elec_gym_work->GearRotateCode = GEAR_ROT_ST_0;
		start_z = ELEC_ROOM3_START_Z;
		break;
	default:
		GF_ASSERT(0);
	}
	
	if (fsys->location->grid_z == start_z){
		elec_gym_work->GearRotateCode = GEAR_ROT_ST_0;
	}
}

//---------------------------------------------------------------------------
/**
 * @brief	����r�b�g�Z�b�g
 * 
 * @param	inBit				�Ώۃr�b�g
 * @param	inVal				�l
 * @param	outData			�f�[�^
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
static void SetBit(const u8 inBit, const u8 inVal, int *outData)
{
	int u,m,d;
	GF_ASSERT((inVal<=1)&&"2�ȏ�̒l���Z�b�g����Ă��܂�");
	
	u = (*outData) & (0xffffffff<<(inBit+1));
	d = (*outData) & (0xffffffff>>(32-inBit));
	m = inVal<<inBit;
	(*outData) = (u|m|d);
}
