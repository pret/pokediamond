//=============================================================================
/**
 * @file	gym_local.h
 * @bfief	�W���d�|���Ƃ�
 * @author	Nozomu Saito
 *
 */
//=============================================================================
#ifndef __GYM_LOCAL_H__
#define __GYM_LOCAL_H__

//���W��
//swtich�p
#define GYM_WATER_LV1	(0)
#define GYM_WATER_LV2	(1)
#define GYM_WATER_LV3	(2)

//�S�[�X�g�W��
//swtich�p
#define GYM_GHOST_LIFT_LV1	(0)
#define GYM_GHOST_LIFT_LV2	(1)

#define GHOST_LIFT_ROOM_START_Z		(22)	//���t�g�̕����ɏ��߂ē������Ƃ��́A���@Z���W

//�|�W��
#define STEEL_LIFT_MAX	(24)

//�i���W��
#define COMBAT_WALL_MAX	(12)

//�d�C�W��
#define GEAR_ROT_ST_0	(0)			//0��
#define GEAR_ROT_ST_90	(1)			//90��
#define GEAR_ROT_ST_180	(2)			//180��
#define GEAR_ROT_ST_270	(3)			//270��
#define GEAR_ROT_ST_MAX	(4)

#define ELEC_ROOM1_START_Z	(14)
#define ELEC_ROOM2_START_Z	(21)
#define ELEC_ROOM3_START_Z	(25)

#define ELEC_ROOM_MAX	(3)


///////�W�����[�N///////
//���W�����[�N---------------------
typedef struct WATER_GYM_WORK_tag
{
	u8 Water;//���W���̐���
}WATER_GYM_WORK;

//�S�[�X�g�W�����[�N-------------------
typedef struct GHOST_GYM_WORK_tag
{
	u8 Lift;	//���t�g�̈ʒu�i�ォ�����j
}GHOST_GYM_WORK;

//�|�W�����[�N---------------------
typedef struct STEEL_GYM_WORK_tag
{
	int LiftPosBit;	//���t�g�̈ʒu���i�[
}STEEL_GYM_WORK;

//�i���W�����[�N--------------------
typedef struct COMBAT_GYM_WORK_tag
{
	int WallPosBit;	//������̈ʒu���i�[
}COMBAT_GYM_WORK;

//�d�C�W�����[�N--------------------
typedef struct ELEC_GYM_WORK_tag
{
	int GearRotateCode;	//�M�A��]��
	int RoomNo;		//�����ԍ�0�`2
}ELEC_GYM_WORK;

#endif	//__GYM_LOCAL_H__
