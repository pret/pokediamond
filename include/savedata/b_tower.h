/**
 *	@file	b_tower.h
 *	@brief	�o�g���^���[�֘A�@�Z�[�u�f�[�^
 *	@author	Miyuki Iwasawa
 *	@date	06.04.14
 */

#ifndef __H_B_TOWER_H__
#define __H_B_TOWER_H__

#include "b_tower_def.h"

/**
 * @brief	�o�g���^���[�@�v���C�f�[�^�\���̂ւ̕s���S�^�|�C���^
 *
 * ���g�͌����܂��񂪃|�C���^�o�R�ŎQ�Ƃł��܂�
 */
typedef struct _BTLTOWER_PLAYWORK	BTLTOWER_PLAYWORK;

/**
 * @brief	�o�g���^���[�@�X�R�A�f�[�^�\���̂ւ̕s���S�^�|�C���^
 *
 * ���g�͌����܂��񂪃|�C���^�o�R�ŎQ�Ƃł��܂�
 */
typedef struct _BTLTOWER_SCOREWORK	BTLTOWER_SCOREWORK;

/**
 * @brief	�o�g���^���[�@�v���C���[���b�Z�[�W�f�[�^�\���̂ւ̕s���S�^�|�C���^
 *
 * ���g�͌����܂��񂪃|�C���^�o�R�ŎQ�Ƃł��܂�
 */
typedef struct _BTLTOWER_PLAYER_MSG	BTLTOWER_PLAYER_MSG;

/**
 * @brief	�o�g���^���[�@WIFI�|�P�����f�[�^�\���̂ւ̕s���S�^�|�C���^
 *
 * ���g�͌����܂��񂪃|�C���^�o�R�ŎQ�Ƃł��܂�
 */
//typedef struct _BTLTOWER_POKE	BTLTOWER_POKE;
/**
 * @brief	�o�g���^���[�@WIFI�v���C���[�f�[�^�\���̂ւ̕s���S�^�|�C���^
 *
 * ���g�͌����܂��񂪃|�C���^�o�R�ŎQ�Ƃł��܂�
 */
typedef struct _BTLTOWER_WIFI_PLAYER	BTLTOWER_WIFI_PLAYER;
/**
 * @brief	�o�g���^���[�@WIFI���[�_�[�f�[�^�\���̂ւ̕s���S�^�|�C���^
 *
 * ���g�͌����܂��񂪃|�C���^�o�R�ŎQ�Ƃł��܂�
 */
//typedef struct _BTLTOWER_WIFI_LEADER	BTLTOWER_WIFI_LEADER;


/**
 * @brief	�o�g���^���[�@WIFI�f�[�^�\���̂ւ̕s���S�^�|�C���^
 *
 * ���g�͌����܂��񂪃|�C���^�o�R�ŎQ�Ƃł��܂�
 */
typedef struct _BTLTOWER_WIFI_DATA	BTLTOWER_WIFI_DATA;


/**
 *	@brief	�o�g���^���[�@�u���b�N�f�[�^�\���̂ւ̕s���S�^�|�C���^
 *
 * ���g�͌����܂��񂪃|�C���^�o�R�ŎQ�Ƃł��܂�
 */
typedef struct _BTLTOWER_SAVEWORK	BTLTOWER_SAVEWORK;

/**
 * �^���[�|�P�����f�[�^�^
 * �@battle/b_tower_data.h��K�v�ȉӏ��ȊO�ł�
 *	include���Ȃ��ōςނ悤�ɒ�`���Ă���
 */
typedef struct _B_TOWER_POKEMON	B_TOWER_POKEMON;

/**
 * �^���[�p�[�g�i�[�f�[�^�^
 * �@battle/b_tower_data.h��K�v�ȉӏ��ȊO�ł�
 *	include���Ȃ��ōςނ悤�ɒ�`���Ă���
 */
typedef struct _B_TOWER_PARTNER_DATA	B_TOWER_PARTNER_DATA;

/**
 * @brief	�o�g���^���[�@WIFI���[�_�[�f�[�^�\���̂ւ̕s���S�^�|�C���^
 *  battle/b_tower_data.h��K�v�ȉӏ��ȊO�ł�
 *	include���Ȃ��ōςނ悤�ɒ�`���Ă���
 *
 * ���g�͌����܂��񂪃|�C���^�o�R�ŎQ�Ƃł��܂�
 */
typedef struct _B_TOWER_LEADER_DATA	B_TOWER_LEADER_DATA;

/**
 *	@biref	�^���[AI�}���`�y�A�̕ۑ����K�v�ȃ|�P�����p�����[�^
 *	
 *  battle/b_tower_data.h��K�v�ȉӏ��ȊO�ł�
 *	include���Ȃ��ōςނ悤�ɒ�`���Ă���
 */
typedef struct _B_TOWER_PAREPOKE_PARAM B_TOWER_PAREPOKE_PARAM;


/**
 *	@brief	�o�g���^���[ WIFI���C�u�����\���̂ւ̕s���S�|�C���^
 *	Wifi���C�u�����w�b�_���O���ɔ���J�ɂ��Ă������߂ɒ�`
 */
typedef struct Dpw_Bt_PokemonData	DPW_BT_POKEMON_DATA;
typedef struct Dpw_Bt_Player	DPW_BT_PLAYER;
typedef struct Dpw_Bt_Leader	DPW_BT_LEADER;
typedef struct Dpw_Bt_Room		DPW_BT_ROOM;

/**
 *	@biref	�o�g���^���[ WIFI���[���f�[�^ID(rank��roomno)
 *
 *	�����N�ƃ��[���i���o�[���擾�������Ƃ��悤�̌��J�\���̃f�[�^�^
 */
typedef struct{
	u8	rank;	//���[�������N(1-10)
	u8	no;		//���[��No(1-200)
}BTOWER_ROOMID;

//========================================================
//�Z�[�u�f�[�^�A�N�Z�X
//========================================================

#ifdef GLOBAL
#undef GLOBAL
#endif

#ifdef _B_TOWER_H_GLOBAL
#define GLOBAL	/***/
#else
#define GLOBAL	extern
#endif

///���[�N�T�C�Y�擾���N���A
//////////////////////////////////
/**
 *	@brief	�^���[�@�v���C�f�[�^�T�C�Y
 */
GLOBAL int TowerPlayData_GetWorkSize(void);

/**
 *	@brief	�^���[�@�v���C���[�X�R�A�f�[�^�T�C�Y
 */
GLOBAL int	TowerSocreData_GetWorkSize(void);

/**
 *	@brief	�^���[�@�|�P�����f�[�^�T�C�Y
 */
GLOBAL int TowerWifiPoke_GetWorkSize(void);

/**
 *	@brief	�^���[�@Wifi�f�[�^�T�C�Y
 */
GLOBAL int	TowerWifiData_GetWorkSize(void);
/**
 *	@brief�@�^���[ Wifi/�g���[�i�[���[�h�v���C���[�f�[�^�\���̃f�[�^�T�C�Y
 */
GLOBAL int TowerDpwBtPlayer_GetWorkSize(void);

/**
 *	@brief	�^���[�@�v���C�f�[�^�N���A
 */
GLOBAL void TowerPlayData_Clear(BTLTOWER_PLAYWORK* dat);

/**
 *	@brief	�^���[	�X�R�A�f�[�^�N���A
 */
GLOBAL void TowerScoreData_Clear(BTLTOWER_SCOREWORK* dat);

/**
 *	@brief	�^���[�@�v���C���[���b�Z�[�W�f�[�^�N���A
 */
GLOBAL void TowerPlayerMsg_Clear(BTLTOWER_PLAYER_MSG* dat);

/**
 *	@brief	�^���[�@Wifi�f�[�^�N���A
 */
GLOBAL void TowerWifiData_Clear(BTLTOWER_WIFI_DATA* dat);

///�u���b�N�f�[�^�A�N�Z�X�n
/////////////////////////////////
/**
 *	@brief	�^���[�@�Z�[�u�f�[�^�u���b�N�T�C�Y���擾
 */
GLOBAL int TowerData_GetWorkSize(void);

/**
 *	@brief	�^���[�@�Z�[�u�f�[�^�u���b�N������
 */
GLOBAL void TowerData_Init(BTLTOWER_SAVEWORK* save);

/**
 *	@brief	�^���[�@�v���C�f�[�^�ւ̃|�C���^���擾
 */
GLOBAL BTLTOWER_PLAYWORK* SaveData_GetTowerPlayData(SAVEDATA* sv);

/**
 *	@brief	�^���[�@�X�R�A�f�[�^�ւ̃|�C���^���擾
 */
GLOBAL BTLTOWER_SCOREWORK* SaveData_GetTowerScoreData(SAVEDATA* sv);

/**
 *	@brief	�^���[ Wifi�f�[�^�ւ̃|�C���^���擾	
 */
GLOBAL BTLTOWER_WIFI_DATA*	SaveData_GetTowerWifiData(SAVEDATA* sv);

////////////////////////////////////////////////////////////
//�v���C�f�[�^�擾�n
////////////////////////////////////////////////////////////
/**
 *	@brief	�v���C�f�[�^�@�擾
 *
 *	@param	dat	BTLTOWRE_PLAYWORK*
 *	@param	id	�擾����f�[�^ID BTOWER_PSD_ID�^
 *	@param	buf	void*:�f�[�^�擾�|�C���^
 */
GLOBAL u32	TowerPlayData_Get(BTLTOWER_PLAYWORK* dat,BTWR_PSD_ID id,void* buf);

/**
 *	@brief	�v���C�f�[�^�@�Z�b�g
 *	
 *	@param	dat	BTLTOWRE_PLAYWORK*
 *	@param	id	�擾����f�[�^ID BTOWER_PSD_ID�^
 *	@param	buf	void*:�f�[�^���i�[�����o�b�t�@�ւ̃|�C���^
 */
GLOBAL void TowerPlayData_Put(BTLTOWER_PLAYWORK* dat,BTWR_PSD_ID id,const void* buf);

/**
 *	@brief �v���C�f�[�^�@Wifi���R�[�h�f�[�^Add	
 *
 *	@param	down	�|���ꂽ�|�P�����ǉ���
 *	@param	turn	���������^�[���ǉ���
 *	@param	damage	�󂯂��_���[�W�ǉ��l
 */
GLOBAL void TowerPlayData_WifiRecordAdd(BTLTOWER_PLAYWORK* dat,u8 down,u16 turn,u16 damage);

/**
 *	@brief	�v���C�f�[�^�@�������Z�[�u�ς݂��ǂ����H
 *
 *	@retval	TRUE	�������Z�[�u����Ă���
 *	@retval FALSE	�Z�[�u����Ă��Ȃ�
 */
GLOBAL BOOL TowerPlayData_GetSaveFlag(BTLTOWER_PLAYWORK* dat);
/**
 *	@brief	�v���C�f�[�^�@�Z�[�u��ԃt���O���Z�b�g
 */
GLOBAL void TowerPlayData_SetSaveFlag(BTLTOWER_PLAYWORK* dat,BOOL flag);


///�X�R�A�f�[�^�擾�n
/////////////////////////////////////////////////

/**
 *	@brief	�X�R�A�f�[�^ �o�g���|�C���g�Z�b�g
 *
 *	�L���R�}���h set/get/add/sub
 */
GLOBAL u16 TowerScoreData_SetBattlePoint(BTLTOWER_SCOREWORK* dat,u16 num,BTWR_DATA_SETID mode);

/**
 *	@brief	SAVEDATA����o�g���|�C���g��Get
 */
static inline u16 BattlePoint_Get(SAVEDATA* sv)
{
	return TowerScoreData_SetBattlePoint(SaveData_GetTowerScoreData(sv),0,BTWR_DATA_get);
}
/**
 *	@brief	SAVEDATA����o�g���|�C���g��Set
 */
static inline u16 BattlePoint_Set(SAVEDATA* sv,u16 num)
{
	return TowerScoreData_SetBattlePoint(SaveData_GetTowerScoreData(sv),num,BTWR_DATA_set);
}
/**
 *	@brief	SAVEDATA����o�g���|�C���g��Add
 */
static inline u16	BattlePoint_Add(SAVEDATA* sv,u16 num)
{
	return TowerScoreData_SetBattlePoint(SaveData_GetTowerScoreData(sv),num,BTWR_DATA_add);
}
/**
 *	@brief	SAVEDATA����o�g���|�C���g��Sub
 */
static inline u16	BattlePoint_Sub(SAVEDATA* sv,u16 num)
{
	return TowerScoreData_SetBattlePoint(SaveData_GetTowerScoreData(sv),num,BTWR_DATA_sub);
}

/**
 *	@brief	�X�R�A�f�[�^�@Wifi�A���s��J�E���g����
 *
 *	�L���R�}���h get/reset/inc
 *
 *	@return	�����̃J�E���g
 */
GLOBAL u8 TowerScoreData_SetWifiLoseCount(BTLTOWER_SCOREWORK* dat,BTWR_DATA_SETID mode);

/**
 *	@brief	�X�R�A�f�[�^�@Wifi�����N����
 *
 *	�L���R�}���h get/reset/inc/dec
 */
GLOBAL u8	TowerScoreData_SetWifiRank(BTLTOWER_SCOREWORK* dat,BTWR_DATA_SETID mode);

/**
 *	@brief	�g�p�|�P�����f�[�^�ۑ�
 */
GLOBAL void TowerScoreData_SetUsePokeData(BTLTOWER_SCOREWORK* dat,
				BTWR_SCORE_POKE_DATA mode,B_TOWER_POKEMON* poke);
/**
 *	@brief	�g�p�|�P�����f�[�^���o�b�t�@�ɃR�s�[���Ď擾(WiFi�\���̃f�[�^�^)
 */
GLOBAL void TowerScoreData_GetUsePokeDataDpw(BTLTOWER_SCOREWORK* dat,
			BTWR_SCORE_POKE_DATA mode,DPW_BT_POKEMON_DATA* poke);

/**
 *	@brief	�g�p�|�P�����f�[�^���o�b�t�@�ɃR�s�[���Ď擾
 */
GLOBAL void TowerScoreData_GetUsePokeData(BTLTOWER_SCOREWORK* dat,
			BTWR_SCORE_POKE_DATA mode,B_TOWER_POKEMON* poke);


/**
 *	@brief	�X�R�A�f�[�^�@���񐔑���
 */
GLOBAL u16 TowerScoreData_SetStage(BTLTOWER_SCOREWORK* dat,u16 id,BTWR_DATA_SETID mode);

#ifdef PM_DEBUG
/**
 *	@brief	�f�o�b�O����@���݂̃X�e�[�W�l�𒼐ڃZ�b�g����
 */
GLOBAL u16 TowerScoreData_DebugSetStageValue(BTLTOWER_SCOREWORK* dat,u16 id,u16 value);
#endif	//PM_DEBUG
/**
 *	@brief	�X�R�A�f�[�^ Wifi���ё���
 */
GLOBAL u16	TowerScoreData_SetWifiScore(BTLTOWER_SCOREWORK* dat,BTLTOWER_PLAYWORK *playdata);

/**
 *	@brief	�X�R�A�f�[�^�@Wifi����0�N���A
 */
GLOBAL void TowerScoreData_ClearWifiScore(BTLTOWER_SCOREWORK* dat);

/**
 *	@brief	�X�R�A�f�[�^�@Wifi���ю擾
 */
GLOBAL u16	TowerScoreData_GetWifiScore(BTLTOWER_SCOREWORK* dat);

/**
 *	@brief	�X�R�A�f�[�^���珟�������������擾
 */
GLOBAL u8	TowerScoreData_GetWifiWinNum(BTLTOWER_SCOREWORK* dat);

/**
 *	@brief	�X�R�A�f�[�^ �t���O�G���A�Z�b�g
 *
 *	�L���R�}���h�Freset/set/get
 */
GLOBAL BOOL TowerScoreData_SetFlags(BTLTOWER_SCOREWORK* dat,u16 id,BTWR_DATA_SETID mode);

/**
 *	@brief	�^���[�p���t�ω������_���V�[�h�ۑ�
 */
GLOBAL void TowerScoreData_SetDayRndSeed(BTLTOWER_SCOREWORK* dat,u32 rnd_seed);

/**
 *	@brief	�^���[�p���t�ω������_���V�[�h�擾
 */
GLOBAL u32 TowerScoreData_GetDayRndSeed(BTLTOWER_SCOREWORK* dat);


//=======================================================
//�@�^���[�@�v���C���[���b�Z�[�W�f�[�^�A�N�Z�X�n
//=======================================================
/**
 *	@brief	�ȈՉ�b�f�[�^���Z�b�g
 */
GLOBAL void TowerPlayerMsg_Set(SAVEDATA* sv,BTWR_PLAYER_MSG_ID id,PMS_DATA* src);

/**
 *	@brief	�ȈՉ�b�f�[�^���擾
 */
GLOBAL PMS_DATA* TowerPlayerMsg_Get(SAVEDATA* sv,BTWR_PLAYER_MSG_ID id);

//=======================================================
//�@�^���[�@Wifi�f�[�^�A�N�Z�X�n
//=======================================================
/**
 *	@brief	�w�肵�����[���f�[�^�̎擾�t���O�𗧂Ă�
 *
 *	@param	rank	1�I���W���Ȃ̂Œ���
 *	@param	roomno	1�I���W���Ȃ̂Œ���
 */
GLOBAL void TowerWifiData_SetRoomDataFlag(BTLTOWER_WIFI_DATA* dat,
		u8 rank,u8 roomno,RTCDate *day);

/**
 *	@brief	���[���f�[�^�擾�t���O���N���A����
 */
GLOBAL void TowerWifiData_ClearRoomDataFlag(BTLTOWER_WIFI_DATA* dat);

/**
 *	@brief	�w�肵�����[����DL�t���O�������Ă��邩�`�F�b�N
 *
 *	@param	rank	1�I���W���Ȃ̂Œ���
 *	@param	roomno	1�I���W���Ȃ̂Œ���
 */
GLOBAL BOOL TowerWifiData_CheckRoomDataFlag(BTLTOWER_WIFI_DATA* dat,u8 rank,u8 roomno,RTCDate* day);


/**
 *	@brief	�v���C���[�f�[�^�����݂��邩�`�F�b�N
 */
GLOBAL BOOL TowerWifiData_IsPlayerDataEnable(BTLTOWER_WIFI_DATA* dat);

/**
 *	@brief	���[�_�[�f�[�^�����邩�ǂ����`�F�b�N
 */
GLOBAL BOOL TowerWifiData_IsLeaderDataEnable(BTLTOWER_WIFI_DATA* dat);

/**
 *	@brief	�v���C���[�f�[�^���Z�[�u
 *	
 *	@param	rank	1�I���W���Ȃ̂Œ���
 *	@param	roomno	1�I���W���Ȃ̂Œ���
 */
GLOBAL void TowerWifiData_SetPlayerData(BTLTOWER_WIFI_DATA* dat,DPW_BT_PLAYER* src,u8 rank,u8 roomno);

/**
 *	@brief	�v���C���[�f�[�^���N���A
 */
GLOBAL void TowerWifiData_ClearPlayerData(BTLTOWER_WIFI_DATA* dat);

/**
 *	@brief	�v���C���[�f�[�^��RoomID(�����N��roomNo)���擾
 *
 *	@param	roomid	BTOWER_ROOMID�^(b_tower.h�Ō��J)
 */
GLOBAL void TowerWifiData_GetPlayerDataRoomID(BTLTOWER_WIFI_DATA* dat,BTOWER_ROOMID *roomid);

/**
 *	@brief	�v���C���[�f�[�^���^���[�퓬�p�ɉ�
 */
GLOBAL void TowerWifiData_GetBtlPlayerData(BTLTOWER_WIFI_DATA* dat,
		B_TOWER_PARTNER_DATA* player,const u8 round);

/**
 *	@brief	���[�_�[�f�[�^���Z�[�u
 *	
 *	@param	rank	1�I���W���Ȃ̂Œ���
 *	@param	roomno	1�I���W���Ȃ̂Œ���
 */
GLOBAL void TowerWifiData_SetLeaderData(BTLTOWER_WIFI_DATA* dat,DPW_BT_LEADER* src,u8 rank,u8 roomno);

/**
 *	@brief	���[�_�[�f�[�^���N���A
 */
GLOBAL void TowerWifiData_ClearLeaderData(BTLTOWER_WIFI_DATA* dat);

/**
 *	@brief	���[�_�[�f�[�^��RoomID(�����N��roomNo)���擾
 *
 *	@param	roomid	BTOWER_ROOMID�^(b_tower.h�Ō��J)
 */
GLOBAL void TowerWifiData_GetLeaderDataRoomID(BTLTOWER_WIFI_DATA* dat,BTOWER_ROOMID *roomid);

/**
 *	@brief	���[�_�[�f�[�^��Alloc�����������ɃR�s�[���Ď擾����
 *
 *	��������Alloc�����������̈��Ԃ��̂ŁA�Ăяo�����������I�ɉ�����邱�ƁI
 */
GLOBAL B_TOWER_LEADER_DATA* TowerWifiData_GetLeaderDataAlloc(BTLTOWER_WIFI_DATA* dat,int heapID) ;




#endif	//__H_B_TOWER_H__
