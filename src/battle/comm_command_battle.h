//=============================================================================
/**
 * @file	comm_command_battle.h
 * @brief	通信のコマンド一覧  バトル用
 * @author	Katsumi Ohno
 * @date    2005.11.08
 */
//=============================================================================

#ifndef __COMM_COMMAND_BATTLE_H__
#define __COMM_COMMAND_BATTLE_H__

#include "communication/comm_command.h"
#include "battle/battle_common.h"

//==============================================================================
//  構造体宣言
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
//  define定義
//==============================================================================
#define	SIO_BUF_ACCESS		(0)			//通信バッファ内でのaccessデータへの添え字
#define	SIO_BUF_PARA		(1)			//通信バッファ内でのparaデータへの添え字
#define	SIO_BUF_SIZE_LOW	(2)			//通信バッファ内でのサイズデータへの添え字
#define	SIO_BUF_SIZE_HIGH	(3)			//通信バッファ内でのサイズデータへの添え字

/// 同期種類定義
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

/// バトル専用通信コマンドの定義。
enum CommCommandBattle_e {
  CB_EXIT_BATTLE = CS_COMMAND_MAX, ///< バトルを終了しフィールドに戻る事を送信

	CB_BATTLE_DATA,					///<戦闘データ送信
	CB_BATTLE_SERVER_VERSION_DATA,	///<戦闘データ送信
	CB_BATTLE_MYSTATUS_DATA,		///<戦闘データ送信
	CB_BATTLE_TRAINER_DATA,			///<戦闘データ送信
	CB_BATTLE_POKE_DATA,			///<戦闘データ送信
	CB_BATTLE_POKE_VOICE,			///<ペラップボイスデータ送信
	CB_BATTLE_TTDATA1,				///<戦闘データ送信
	CB_BATTLE_TTDATA2,				///<戦闘データ送信
	CB_BATTLE_TPDATA1,				///<戦闘データ送信
	CB_BATTLE_TPDATA2,				///<戦闘データ送信
	CB_BATTLE_FRIEND_LIST,			///<ともだちグループデータ送信

  //------------------------------------------------ここまで
  CB_COMMAND_MAX   // 終端--------------これは移動させないでください
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

