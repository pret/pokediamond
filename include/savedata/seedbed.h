//============================================================================================
/**
 * @file	seedbed.h
 * @author	tamada
 * @date	2005.02.01
 * @brief	���݂̂̏�ԃf�[�^��`
 */
//============================================================================================
#ifndef	__SEEDBED_H__
#define	__SEEDBED_H__

#include "savedata/savedata_def.h"

//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	���̂ݏ�ԃf�[�^�̕s���S�^��`
 */
//----------------------------------------------------------
typedef struct _SEEDBED SEEDBED;

//----------------------------------------------------------
/**
 * @brief	���݂̂̏�Ԓ�`
 */
//----------------------------------------------------------
typedef enum {
	SEEDSTAT_NOTHING = 0,	///<���݂̂��A�����Ă��Ȃ�
	SEEDSTAT_UNDERGROUND,	///<���݂̂�A�������
	SEEDSTAT_HUTABA,		///<�肪�o�Ă������
	SEEDSTAT_MIKI,			///<���������������
	SEEDSTAT_FLOWER,		///<�Ԃ��炢�Ă�����
	SEEDSTAT_FRUIT,			///<�����Ȃ��Ă�����

	SEEDSTAT_CHANGE = 0xff,	///<��ԕω���
}SEEDSTAT;

//----------------------------------------------------------
/**
 * @brief	����C�̏��
 */
//----------------------------------------------------------
typedef enum {
	SEEDGROUND_DRY = 0,	///<���������ăq�r���łĂ�����
	SEEDGROUND_WET,		///<�������������
	SEEDGROUND_FULL,		///<�\��������������
}SEEDGROUND;

//----------------------------------------------------------
/**
 * @brief	�엿�̎��
 */
//----------------------------------------------------------
typedef enum {
	SEEDCOMPOST_NOTHING = 0,
	SEEDCOMPOST_SUKUSUKU,
	SEEDCOMPOST_YURURI,
	SEEDCOMPOST_MINAARU,
	SEEDCOMPOST_NEBARI,
}SEEDCOMPOST;

//----------------------------------------------------------
/**
 * @brief	���݂̂̐��������ɕK�v�ȃp�����[�^
 */
//----------------------------------------------------------
typedef struct {
	u8 grow_speed;		///<�������x�i���ԒP�ʁj
	u8 root_power;		///<�z����
	u8 nuts_rate;		///<���̐��鐔�̔{��
}SEED_TABLE;

//============================================================================================
//============================================================================================
//----------------------------------------------------------
//----------------------------------------------------------
extern int SEEDBED_GetWorkSize(void);
extern SEEDBED * SEEDBED_AllocWork(u32 heapID);
extern void SEEDBED_Init(SEEDBED * sbed);

//�����p�e�[�u������
extern SEED_TABLE * SEEDBED_CreateParamTable(int heapID);

//������ԃZ�b�g����
extern void SEEDBED_SetDefaultData(SEEDBED * sbed, int heapID, const u16 * init_data, int max);
//----------------------------------------------------------
//----------------------------------------------------------
//��Ԏ擾
extern SEEDSTAT SEEDBED_GetSeedStatus(const SEEDBED * sbed, int id);

//���݂̂̎�ނ��擾
extern int SEEDBED_GetSeedType(const SEEDBED * sbed, int id);

//�����̏�Ԃ��擾
extern SEEDGROUND SEEDBED_GetGroundStatus(const SEEDBED * sbed, int id);

//���݂̂�HP���擾
extern int SEEDBED_GetSeedHP(const SEEDBED * sbed, int id);

//���݂̂�A����
extern void SEEDBED_SetNuts(SEEDBED * sbed, int id, const SEED_TABLE * param, int type);
//����������
extern void SEEDBED_SetSeedWater(SEEDBED * sbed, int id);
//�R���V���܂�
//�R���V�̎�ނ��擾
extern void SEEDBED_SetCompost(SEEDBED * sbed, int id, SEEDCOMPOST compost);

//�����t���O�̐ݒ�
extern BOOL SEEDBED_GetGrowthFlag(const SEEDBED * sbed, int id);
//�����t���O�̎擾
extern void SEEDBED_SetGrowthFlag(SEEDBED * sbed, int id, BOOL flag);

//���݂̂̐����擾
extern int SEEDBED_GetSeedCount(const SEEDBED * sbed, int id);

extern SEEDCOMPOST SEEDBED_GetCompost(const SEEDBED * sbed, int id);
//----------------------------------------------------------
//----------------------------------------------------------
//���݂̂����n
extern int SEEDBED_GetHarvest(SEEDBED * sbed, int id);

//���݂̂𐬒�������
extern void SEEDBED_Growth(SEEDBED * sbed, const SEED_TABLE * param, int minute);

//----------------------------------------------------------
//----------------------------------------------------------
extern SEEDBED * SaveData_GetSeedBed(SAVEDATA * sv);

#endif /* __SEEDBED_H__ */
