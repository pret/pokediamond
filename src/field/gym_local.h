//=============================================================================
/**
 * @file	gym_local.h
 * @bfief	ジム仕掛けとか
 * @author	Nozomu Saito
 *
 */
//=============================================================================
#ifndef __GYM_LOCAL_H__
#define __GYM_LOCAL_H__

//水ジム
//swtich用
#define GYM_WATER_LV1	(0)
#define GYM_WATER_LV2	(1)
#define GYM_WATER_LV3	(2)

//ゴーストジム
//swtich用
#define GYM_GHOST_LIFT_LV1	(0)
#define GYM_GHOST_LIFT_LV2	(1)

#define GHOST_LIFT_ROOM_START_Z		(22)	//リフトの部屋に初めて入ったときの、自機Z座標

//鋼ジム
#define STEEL_LIFT_MAX	(24)

//格闘ジム
#define COMBAT_WALL_MAX	(12)

//電気ジム
#define GEAR_ROT_ST_0	(0)			//0°
#define GEAR_ROT_ST_90	(1)			//90°
#define GEAR_ROT_ST_180	(2)			//180°
#define GEAR_ROT_ST_270	(3)			//270°
#define GEAR_ROT_ST_MAX	(4)

#define ELEC_ROOM1_START_Z	(14)
#define ELEC_ROOM2_START_Z	(21)
#define ELEC_ROOM3_START_Z	(25)

#define ELEC_ROOM_MAX	(3)


///////ジムワーク///////
//水ジムワーク---------------------
typedef struct WATER_GYM_WORK_tag
{
	u8 Water;//水ジムの水位
}WATER_GYM_WORK;

//ゴーストジムワーク-------------------
typedef struct GHOST_GYM_WORK_tag
{
	u8 Lift;	//リフトの位置（上か下か）
}GHOST_GYM_WORK;

//鋼ジムワーク---------------------
typedef struct STEEL_GYM_WORK_tag
{
	int LiftPosBit;	//リフトの位置を格納
}STEEL_GYM_WORK;

//格闘ジムワーク--------------------
typedef struct COMBAT_GYM_WORK_tag
{
	int WallPosBit;	//しきりの位置を格納
}COMBAT_GYM_WORK;

//電気ジムワーク--------------------
typedef struct ELEC_GYM_WORK_tag
{
	int GearRotateCode;	//ギア回転状況
	int RoomNo;		//部屋番号0～2
}ELEC_GYM_WORK;

#endif	//__GYM_LOCAL_H__
