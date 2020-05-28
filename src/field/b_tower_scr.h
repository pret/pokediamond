/**
 *	@file	btower_scr.h
 *	@brief	�o�g���^���[�@�X�N���v�g�n
 *	@author	Miyuki Iwasawa
 *	@date	06.04.17
 */

#ifndef __H_B_TOWER_SCR_H__
#define __H_B_TOWER_SCR_H__

#ifdef GLOBAL
#undef GLOBAL
#endif

#ifdef __B_TOWER_SCR_H_GLOBAL
#define GLOBAL	/***/
#else
#define GLOBAL	extern
#endif

#include "b_tower_scr_def.h"
#include "battle/battle_common.h"
#include "battle/b_tower_data.h"

///�o�g���^���[�@�X�N���v�g���[�N
typedef struct _BTOWER_SCRWORK{
	int	magicNo;	///<�}�W�b�N�i���o�[
	int	heapID;	///<�q�[�v
	u32	play_rnd_seed;	///<�v���C�p�����_���V�[�h
	u8	now_round;	///<���݉��l�ځH
	u8	now_win;	///<���݉��l�ɏ������H
	u8	member_num;	///<�����o�[��
	u8	play_mode;	///<�v���C�f�[�^

	u8	clear_f:1;	///<�N���A�t���O
	u8	leader_f:2;	///<�^�C�N�[��2
	u8	retire_f:1;	///<���^�C�A�t���O
	u8	prize_f:1;	///<���J���t���O
	u8	partner:3;	///<�p�[�g�i�[No

	u8	my_sex;			///<�����̐���
	u8	pare_sex;		///<�����ƃp�[�g�i�[�̐���
	u16	pare_stage;		///<�ʐM�}���`�p�[�g�i�[�̎���
	u16	pare_poke[2];	///<�ʐM�}���`�p�[�g�i�[�����|�P����No
	
	u16	renshou;	///<���݂̘A����
	u16	stage;		///<���݂̎���
	u32	win_cnt;	///<���݂܂ł̑�������

	u16	rec_turn;	///<���������^�[����
	u16	rec_damage;	///<�H������_���[�W
	u16	rec_down;	///<�|�P�����̃_�E����

	u8	member[BTOWER_STOCK_MEMBER_MAX];	///<�I�񂾃|�P�����̎莝��No
	u16	mem_poke[BTOWER_STOCK_MEMBER_MAX];	///<�I�񂾃|�P������monsno
	u16	mem_item[BTOWER_STOCK_MEMBER_MAX];	///<�I�񂾃|�P�����̃A�C�e��no
	u16	trainer[BTOWER_STOCK_TRAINER_MAX];	///<�ΐ�g���[�i�[No

	//���݂̃��P�[�V�������L�����Ă���
	LOCATION_WORK	now_location;

	BTLTOWER_PLAYWORK*	playSave;	///<�Z�[�u�f�[�^�ւ̃|�C���^
	BTLTOWER_SCOREWORK*	scoreSave;	///<�Z�[�u�f�[�^�ւ̃|�C���^

	//�ΐ푊��f�[�^�i�[�ꏊ
	B_TOWER_PARTNER_DATA	tr_data[2];
	
	//5�l�O���I�f�[�^�i�[�ꏊ
	B_TOWER_PARTNER_DATA	five_data[BTWR_FIVE_NUM];

	//5�l�O���I�|�P�����p�����[�^�i�[�ꏊ
	B_TOWER_PAREPOKE_PARAM	five_poke[BTWR_FIVE_NUM];

	//5�l�O���I�|�P�����A�C�e��fix�t���O
	u8						five_item[BTWR_FIVE_NUM];

	//�ʐM�p�f�[�^�o�b�t�@
	u16	send_buf[35];
	u16	recv_buf[35];
}BTOWER_SCRWORK;


///�X�N���v�g�R�}���h����Ăяo�����[�`���Q
///////////////////////////////////////////////////////
/**
 *	@brief	�v���C���[�h�ʂ̃����o�[�����擾����
 */
GLOBAL u16	TowerScrTools_GetMemberNum(u16 mode);

/**
 *	@brief	�o�g���^���[�@�Q���\�ȃ|�P�������̃`�F�b�N
 *
 *	@param	num		�Q���ɕK�v�ȃ|�P������
 *
 *	@retval	true	�Q���\
 *	@retval	false	�Q���s��
 */
GLOBAL BOOL TowerScrTools_CheckEntryPokeNum(u16 num,SAVEDATA *savedata);

/**
 *	@brief	���Z�b�g���ă^�C�g���ɖ߂�
 */
GLOBAL void TowerScrTools_SystemReset(void);

/**
 *	@brief	new game���Ƀv���C�f�[�^���N���A����
 */
GLOBAL void TowerScrTools_ClearPlaySaveData(BTLTOWER_PLAYWORK* playSave);

/**
 * @brief	�Z�[�u�f�[�^���L�����ǂ����Ԃ�
 */
GLOBAL BOOL TowerScrTools_IsSaveDataEnable(BTLTOWER_PLAYWORK* playSave);

/**
 *	@brief	�E�o�p�Ɍ��݂̃��P�[�V�������L������
 */
GLOBAL void TowerScrTools_PushNowLocation(FIELDSYS_WORK* fsys);

/**
 *	@brief	�Q�[�g����o�鎞�ɓ���ڑ�������ɖ߂�
 */
GLOBAL void TowerScrTools_PopNowLocation(FIELDSYS_WORK* fsys);

/**
 *	@brief	�������Q�[�g�̈ʒu���擾����
 */
GLOBAL void TowerScrTools_GetGateLocation(FIELDSYS_WORK* fsys,u16* x,u16* y);

/**
 *	@brief	�v���C���[�h�ʃ��R�[�h�Z�[�u�f�[�^�A������Ԃ�
 */
GLOBAL u16	TowerScrTools_GetRenshouRecord(SAVEDATA* sv,u16 play_mode);

/**
 *	@brief	�X�R�A�f�[�^�̃t���O��Ԃ�
 */
GLOBAL u16 TowerScrTools_GetScoreFlags(SAVEDATA* sv,BTWR_SFLAG_ID flagid);

/**
 *	@brief	Wifi���т̖��A�b�v���[�h�t���O�𐧌䂷��
 */
GLOBAL void TowerScrTools_SetWifiUploadFlag(SAVEDATA* sv,u8 flag);

/**
 *	@brief	WiFi�v���C���т̖��A�b�v���[�h�t���O���擾����
 */
GLOBAL u16 TowerScrTools_GetWifiUploadFlag(SAVEDATA* sv);

/**
 *	@brief	�Z�[�u�����Ɏ~�߂��Ƃ��̃G���[����
 *
 *	@return	�v���C���Ă������[�h��Ԃ�
 */
GLOBAL u16 TowerScrTools_SetNGScore(SAVEDATA* savedata);

/**
 *	@brief	WIFI�̃v���C���[DL�f�[�^�����邩�ǂ����`�F�b�N
 */
GLOBAL u16	TowerScrTools_IsPlayerDataEnable(SAVEDATA* sv);


//*****************************************************
//=====================================================
//���[�N�̏������Ɖ��
//=====================================================
//*****************************************************
/**
 *	@brief	fsys���̃o�g���^���[���䃏�[�N�|�C���^������������
 *			�o�g���^���[�J�n���ɕK���Ăяo��
 */
GLOBAL void TowerScr_WorkClear(BTOWER_SCRWORK** pp);

/**
 *	@brief	���[�N�G���A���擾���ď���������
 *
 *	@param	savedata	�Z�[�u�f�[�^�ւ̃|�C���^
 *	@param	init		���������[�h BTWR_PLAY_NEW:���߂���ABTWR_PLAY_CONTINE:��������
 *	@param	playmode	�v���C���[�h�w�� BTWR_MODE_�`
 *	
 *	�����Ȃ炸 TowerScr_WorkRelease()�ŗ̈���J�����邱��
 */
GLOBAL BTOWER_SCRWORK* TowerScr_WorkInit(SAVEDATA* savedata,u16 init,u16 playmode);

/**
 *	@brief	���[�N�G���A���J������
 */
GLOBAL void TowerScr_WorkRelease(BTOWER_SCRWORK* wk);


/**
 *	@brief	�o�g���^���[�p�|�P�����I���ďo��
 */
GLOBAL void TowerScr_SelectPoke(BTOWER_SCRWORK* wk,
				GMEVENT_CONTROL *ev_work,void** proc_wk);

/**
 *	@brief	�I�������|�P�������擾
 *	
 *	@retval	TRUE	�I������
 *	@retval	FALSE	�I�������ɂ�߂�
 */
GLOBAL BOOL TowerScr_GetEntryPoke(BTOWER_SCRWORK* wk,void** app_work,SAVEDATA* sv);

/**
 *	@brief	�Q���w�肵���莝���|�P�����̏����`�F�b�N
 *
 *	@retval	0	�Q��OK
 *	@retval	1	�����|�P����������
 *	@retval 2	�����A�C�e���������Ă���
 */
GLOBAL int TowerScr_CheckEntryPoke(BTOWER_SCRWORK* wk,SAVEDATA* savedata);

/**
 *	@brief�@�ΐ�g���[�i�[No���I
 */
GLOBAL void TowerScr_BtlTrainerNoSet(BTOWER_SCRWORK* wk,SAVEDATA* sv);

/**
 *	@brief	���݂̃��E���h�����X�N���v�g���[�N�Ɏ擾����
 */
GLOBAL u16	TowerScr_GetNowRound(BTOWER_SCRWORK* wk);

/**
 *	@brief	���E���h�����C���N�������g
 */
GLOBAL u16	TowerScr_IncRound(BTOWER_SCRWORK* wk);

/**
 *	@brief	7�A�����Ă��邩�ǂ����`�F�b�N
 */
GLOBAL BOOL TowerScr_IsClear(BTOWER_SCRWORK* wk);

/**
 *	@brief	���݂̘A�������擾����
 */
GLOBAL u16 TowerScr_GetRenshouCount(BTOWER_SCRWORK* wk);

/**
 *	@brief	�s�폈��	
 */
GLOBAL void TowerScr_SetLoseScore(BTOWER_SCRWORK* wk,FIELDSYS_WORK* fsys);

/**
 *	@brief	�N���A����
 */
GLOBAL void TowerScr_SetClearScore(BTOWER_SCRWORK* wk,FIELDSYS_WORK* fsys);


/**
 *	@brief	�x�ނƂ��Ɍ��݂̃v���C�󋵂��Z�[�u�ɏ����o��
 */
GLOBAL void TowerScr_SaveRestPlayData(BTOWER_SCRWORK* wk);


/**
 *	@brief	�ΐ�g���[�i�[���I
 */
GLOBAL void TowerScr_ChoiceBtlPartner(BTOWER_SCRWORK* wk,SAVEDATA* sv);
/**
 *	@brief	AI�}���`�y�A�|�P�������I
 */
GLOBAL void TowerScr_ChoiceBtlSeven(BTOWER_SCRWORK* wk);

/**
 *	@brief	�ΐ�g���[�i�[OBJ�R�[�h�擾
 */
GLOBAL u16 TowerScr_GetEnemyObj(BTOWER_SCRWORK* wk,u16 idx);

/**
 *	@brief	�퓬�Ăяo��
 */
GLOBAL void TowerScr_LocalBattleCall(GMEVENT_CONTROL* event,BTOWER_SCRWORK* wk,BOOL* win_flag);

/**
 *	@brief	���݂̃v���C���[�h��Ԃ�
 */
GLOBAL u16	TowerScr_GetPlayMode(BTOWER_SCRWORK* wk);

/**
 *	@brief	���[�_�[�N���A�t���O�𗧂Ă�
 */
GLOBAL void TowerScr_SetLeaderClearFlag(BTOWER_SCRWORK* wk,u16 mode);

/**
 *	@brief	���[�_�[�N���A�t���O���擾����
 */
GLOBAL	u16	TowerScr_GetLeaderClearFlag(BTOWER_SCRWORK* wk);

/**
 *	@brief	�^���[�N���A���Ƀo�g���|�C���g�����Z����
 *
 *	@return	�V���Ɏ擾�����o�g���|�C���g
 */
GLOBAL u16	TowerScr_AddBtlPoint(BTOWER_SCRWORK* wk);

/**
 *	@brief	�V���O���ŘA���������̂��J���̃g���t�B�[��������t���O�𗧂ĂĂ���
 */
GLOBAL	u16	TowerScr_GoodsFlagSet(BTOWER_SCRWORK* wk,SAVEDATA* sv);

/**
 *	@brief	���݂�WIFI�����N�𑀍삵�ĕԂ�
 */
GLOBAL u16	TowerScr_SetWifiRank(BTOWER_SCRWORK* wk,SAVEDATA* sv,u8 mode);


/**
 *	@brief	���[�_�[��|�������J�����{����������
 */
GLOBAL u16 TowerScr_LeaderRibbonSet(BTOWER_SCRWORK* wk,SAVEDATA* sv);

/**
 *	@brief	�A���̂��J�����{����������	
 */
GLOBAL u16 TowerScr_RenshouRibbonSet(BTOWER_SCRWORK* wk,SAVEDATA* sv);

/**
 *	@biref	�v���C�����_���V�[�h���X�V����
 */
GLOBAL u16 TowerScr_PlayRandUpdate(BTOWER_SCRWORK* wk,SAVEDATA* sv);



#endif	//__H_BTOWER_SCR_H__

