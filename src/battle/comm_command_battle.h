//=============================================================================
/**
 * @file	comm_command_battle.h
 * @brief	�ʐM�̃R�}���h�ꗗ  �o�g���p
 * @author	Katsumi Ohno
 * @date    2005.11.08
 */
//=============================================================================

#ifndef __COMM_COMMAND_BATTLE_H__
#define __COMM_COMMAND_BATTLE_H__

#include "communication/comm_command.h"
#include "battle/battle_common.h"

//==============================================================================
//  �\���̐錾
//==============================================================================

typedef struct
{
	u8	access;
	u8	para;
	u16	size;
}SIO_SEND_DATA;

typedef struct
{
	BATTLE_WORK	*bw;
	u8			seq_no;
}TCB_SIO_SEND;

typedef struct
{
	BATTLE_WORK	*bw;
	u8			seq_no;
}TCB_SIO_RECV;

//==============================================================================
//  define��`
//==============================================================================
#define	SIO_BUF_ACCESS		(0)			//�ʐM�o�b�t�@���ł�access�f�[�^�ւ̓Y����
#define	SIO_BUF_PARA		(1)			//�ʐM�o�b�t�@���ł�para�f�[�^�ւ̓Y����
#define	SIO_BUF_SIZE_LOW	(2)			//�ʐM�o�b�t�@���ł̃T�C�Y�f�[�^�ւ̓Y����
#define	SIO_BUF_SIZE_HIGH	(3)			//�ʐM�o�b�t�@���ł̃T�C�Y�f�[�^�ւ̓Y����

/// ������ޒ�`
enum CommCommandBattleTiming_e {
	COMM_BATTLE_STRAT_SYNC_NUM = 50,
	COMM_BATTLE_SV_SYNC_NUM,
	COMM_BATTLE_MS_SYNC_NUM,
	COMM_BATTLE_TR_SYNC_NUM,
	COMM_BATTLE_POKE_SYNC_NUM,
	COMM_BATTLE_POKEV_SYNC_NUM,
	COMM_BATTLE_FLIST_SYNC_NUM,
	COMM_BATTLE_TTDATA1_SYNC_NUM,
	COMM_BATTLE_TTDATA2_SYNC_NUM,
	COMM_BATTLE_TPDATA1_SYNC_NUM,
	COMM_BATTLE_TPDATA2_SYNC_NUM,
	COMM_BATTLE_START_WAIT_NUM,
	COMM_BATTLE_WIN_LOSE_WAIT_NUM
};

/// �o�g����p�ʐM�R�}���h�̒�`�B
enum CommCommandBattle_e {
  CB_EXIT_BATTLE = CS_COMMAND_MAX, ///< �o�g�����I�����t�B�[���h�ɖ߂鎖�𑗐M

	CB_BATTLE_DATA,					///<�퓬�f�[�^���M
	CB_BATTLE_SERVER_VERSION_DATA,	///<�퓬�f�[�^���M
	CB_BATTLE_MYSTATUS_DATA,		///<�퓬�f�[�^���M
	CB_BATTLE_TRAINER_DATA,			///<�퓬�f�[�^���M
	CB_BATTLE_POKE_DATA,			///<�퓬�f�[�^���M
	CB_BATTLE_POKE_VOICE,			///<�y���b�v�{�C�X�f�[�^���M
	CB_BATTLE_TTDATA1,				///<�퓬�f�[�^���M
	CB_BATTLE_TTDATA2,				///<�퓬�f�[�^���M
	CB_BATTLE_TPDATA1,				///<�퓬�f�[�^���M
	CB_BATTLE_TPDATA2,				///<�퓬�f�[�^���M
	CB_BATTLE_FRIEND_LIST,			///<�Ƃ������O���[�v�f�[�^���M

  //------------------------------------------------�����܂�
  CB_COMMAND_MAX   // �I�[--------------����͈ړ������Ȃ��ł�������
};

extern	void CommCommandBattleInitialize(void* pWork);
extern	void CommCommandBattleCPInitialize(void* pWork);
extern	void CommCommandBattleSendData(BATTLE_WORK *bw,int access,int para,void *data,u8 size);
extern	BOOL CommCommandBattleSendServerVersionData(BATTLE_SIO_WORK *bsw,u32 version);

extern	BOOL CommCommandBattleSendMyStatusDataMake(BATTLE_SIO_WORK *bsw);
extern	BOOL CommCommandBattleSendMyStatusDataWait(BATTLE_SIO_WORK *bsw);
extern	BOOL CommCommandBattleSendTrainerDataMake(BATTLE_SIO_WORK *bsw);
extern	BOOL CommCommandBattleSendTrainerDataWait(BATTLE_SIO_WORK *bsw);
extern	BOOL CommCommandBattleSendPokeDataMake(BATTLE_SIO_WORK *bsw);
extern	BOOL CommCommandBattleSendPokeDataWait(BATTLE_SIO_WORK *bsw);
extern	BOOL CommCommandBattleSendPokeVoiceMake(BATTLE_SIO_WORK *bsw);
extern	BOOL CommCommandBattleSendPokeVoiceWait(BATTLE_SIO_WORK *bsw);
extern	BOOL CommCommandBattleSendTowerTrDataMake(BATTLE_SIO_WORK *bsw,int no);
extern	BOOL CommCommandBattleSendTowerTrDataWait(BATTLE_SIO_WORK *bsw,int no,int sync_num);
extern	BOOL CommCommandBattleSendTowerPokeDataMake(BATTLE_SIO_WORK *bsw,int no);
extern	BOOL CommCommandBattleSendTowerPokeDataWait(BATTLE_SIO_WORK *bsw,int no,int sync_num);

extern	BOOL CommCommandBattleSendFriendListWait(BATTLE_SIO_WORK *bsw);
extern	BOOL CommCommandBattleSendFriendListMake(BATTLE_SIO_WORK *bsw);


#endif// __COMM_COMMAND_FIELD_H__

