/**
 *	@file	b_tower_def.h
 *	@brief	バトルタワー　セーブデータ定数定義
 *	@author	Miyuki Iwasawa
 *	@date	06.04.17
 */

#ifndef __H_B_TOWER_DEF_H__
#define __H_B_TOWER_DEF_H__

///プレイデータ取得ID
typedef enum{
 BTWR_PSD_playmode,
 BTWR_PSD_round,
 BTWR_PSD_rec_down,
 BTWR_PSD_rec_turn,
 BTWR_PSD_rec_damage,
 BTWR_PSD_pokeno,
 BTWR_PSD_pare_poke,
 BTWR_PSD_pare_itemfix,
 BTWR_PSD_trainer,
 BTWR_PSD_partner,
 BTWR_PSD_rnd_seed,
}BTWR_PSD_ID;

///スコアデータ操作モード
typedef enum{
 BTWR_DATA_get,		///<データ取得
 BTWR_DATA_set,		///<セット
 BTWR_DATA_reset,	///<リセット
 BTWR_DATA_inc,		///<1++
 BTWR_DATA_dec,		///<1--
 BTWR_DATA_add,		///<add
 BTWR_DATA_sub,		///<sub
}BTWR_DATA_SETID;

///スコアデータフラグ アクセスID
typedef enum{
 BTWR_SFLAG_SILVER_GET,
 BTWR_SFLAG_GOLD_GET,
 BTWR_SFLAG_SILVER_READY,
 BTWR_SFLAG_GOLD_READY,
 BTWR_SFLAG_WIFI_LOSE_F,
 BTWR_SFLAG_WIFI_UPLOAD,
 BTWR_SFLAG_WIFI_POKE_DATA,
 BTWR_SFLAG_SINGLE_POKE_DATA,
 BTWR_SFLAG_SINGLE_RECORD,
 BTWR_SFLAG_DOUBLE_RECORD,
 BTWR_SFLAG_MULTI_RECORD,
 BTWR_SFLAG_CMULTI_RECORD,
 BTWR_SFLAG_WIFI_RECORD,
 BTWR_SFLAG_COPPER_GET,
 BTWR_SFLAG_COPPER_READY,
}BTWR_SFLAG_ID;

///プレイヤーメッセージデータ　アクセスID
typedef enum{
 BTWR_MSG_PLAYER_READY,
 BTWR_MSG_PLAYER_WIN,
 BTWR_MSG_PLAYER_LOSE,
 BTWR_MSG_LEADER,
}BTWR_PLAYER_MSG_ID;

///スコアデータ　ポケモンデータアクセスモード
typedef enum{
 BTWR_SCORE_POKE_SINGLE,
 BTWR_SCORE_POKE_WIFI,
}BTWR_SCORE_POKE_DATA;

///選択する手持ちポケモン数のMAX
#define BTOWER_STOCK_MEMBER_MAX	(4)
///保存しておく対戦トレーナーナンバーの数
#define BTOWER_STOCK_TRAINER_MAX	(14)
///保存しておくAIマルチペアのポケモンパラメータ数
#define BTOWER_STOCK_PAREPOKE_MAX	(2)
///WiFi DLプレイヤーデータ数
#define BTOWER_STOCK_WIFI_PLAYER_MAX	(7)
///WiFi DLリーダーデータ数
#define BTOWER_STOCK_WIFI_LEADER_MAX	(30)
///ルームデータのDLフラグエリアバッファ長
#define BTOWER_ROOM_DATA_FLAGS_LEN	(250)

#endif	//__H_B_TOWER_DEF_H__
