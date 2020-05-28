//=============================================================================
/**
 * @file	gym_init.c
 * @bfief	ジム仕掛け初期化とか
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

//鋼リフトデフォルト位置情報
//0:デフォルト位置　1:移動先	上下は下、手前奥は奥、左右は左がデフォルト
static const u8 SteelLiftDefault[STEEL_LIFT_MAX] =
{
	0, 0, 0, 0, 0, 0,
	1, 1, 1, 0, 1,
	1, 0, 0, 0, 0, 1, 0, 1,
	1, 0, 1, 0,1
};

//しきり位置情報
//0:デフォルト位置　1:移動先	左がデフォルト
static const u8 WallDefault[COMBAT_WALL_MAX] =
{
	0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1,
};

//---------------------------------------------------------------------------
/**
 * @brief	水ジム:初期化
 * 
 * @param	fsys	フィールドシステムポインタ
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
 * @brief	ゴーストジム:初期化
 * 
 * @param	fsys	フィールドシステムポインタ
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

	//入ってきた場所のZ座標で、リフトの位置を決定（することにする）
	//※地形に依存した判定なので、地形が変わった場合は注意が必要
	if (fsys->location->grid_z == GHOST_LIFT_ROOM_START_Z){
/**		
		MYSTATUS *my_st  = SaveData_GetMyStatus(GameSystem_GetSaveData(fsys));
		//シナリオ進行によって、リフトの位置を分岐(Ｃ7トバリとＣ6ノモセのバッジフラグをチェック)
		if ( MyStatus_GetBadgeFlag(my_st, BADGE_ID_C07) &&
				MyStatus_GetBadgeFlag(my_st, BADGE_ID_C06) ){
			ghost_gym_work->Lift = GYM_GHOST_LIFT_LV1;	//リフト下（ジム挑戦可）
		}else{
			ghost_gym_work->Lift = GYM_GHOST_LIFT_LV2;	//リフト上（ジム挑戦不可）
		}
*/	//<<シナリオ変更により、この処理は不要になりました　20060626
		//シナリオ進行によって、リフトの位置を分岐(カンナギでギンガ団ボスと話をしているかをチェック)
		if ( SysFlag_T05GingaEventCheck( SaveData_GetEventWork( fsys->savedata ) ) ){
			ghost_gym_work->Lift = GYM_GHOST_LIFT_LV1;	//リフト下（ジム挑戦可）
		}else{
			ghost_gym_work->Lift = GYM_GHOST_LIFT_LV2;	//リフト上（ジム挑戦不可）
		}
	}else{
		ghost_gym_work->Lift = GYM_GHOST_LIFT_LV2;
	}
}

//---------------------------------------------------------------------------
/**
 * @brief	鋼ジム:初期化
 * 
 * @param	fsys	フィールドシステムポインタ
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

	//リフト位置初期化
	{
		int i;
		for(i=0;i<STEEL_LIFT_MAX;i++){
			SetBit(i,SteelLiftDefault[i],&steel_gym_work->LiftPosBit);
		}
	}
}

//---------------------------------------------------------------------------
/**
 * @brief	格闘ジム:初期化
 * 
 * @param	fsys	フィールドシステムポインタ
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

	//しきり位置初期化
	{
		int i;
		for(i=0;i<COMBAT_WALL_MAX;i++){
			SetBit(i,WallDefault[i],&combat_gym_work->WallPosBit);
		}
	}
}

//---------------------------------------------------------------------------
/**
 * @brief	電気ジム:初期化
 * 
 * @param	fsys	フィールドシステムポインタ
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
	case ELEC_GYM_ROOM1:			//1部屋目
		elec_gym_work->GearRotateCode = GEAR_ROT_ST_180;
		start_z = ELEC_ROOM1_START_Z;
		break;
	case ELEC_GYM_ROOM2:			//2部屋目
		elec_gym_work->GearRotateCode = GEAR_ROT_ST_90;
		start_z = ELEC_ROOM2_START_Z;
		break;
	case ELEC_GYM_ROOM3:			//3部屋目は行き止まりなので、どんな場合でもデフォルトをセット
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
 * @brief	制御ビットセット
 * 
 * @param	inBit				対象ビット
 * @param	inVal				値
 * @param	outData			データ
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
static void SetBit(const u8 inBit, const u8 inVal, int *outData)
{
	int u,m,d;
	GF_ASSERT((inVal<=1)&&"2以上の値がセットされています");
	
	u = (*outData) & (0xffffffff<<(inBit+1));
	d = (*outData) & (0xffffffff>>(32-inBit));
	m = inVal<<inBit;
	(*outData) = (u|m|d);
}
