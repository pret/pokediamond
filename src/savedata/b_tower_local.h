/**
 *	@file	b_tower_local.h
 *	@brief	バトルタワー　セーブデータ構造体定義
 *	@author	Miyuki Iwasawa
 *	@date	06.04.18	
 */

#ifndef __H_BTOWER_LOCAL_H__
#define __H_BTOWER_LOCAL_H__

#include "savedata/b_tower_def.h"
#include "libdpw/dpw_bt.h"
#include "battle/battle_common.h"
#include "system/gamedata.h"
#include "gflib/gf_date.h"
#include "battle/b_tower_data.h"

/**
 * @brief	バトルタワープレイ進行データ
 *
 * size=20byte
 * 挑戦開始時にクリアされる
*/
struct _BTLTOWER_PLAYWORK{
	u8	itemfix_f	:1;	///<固定アイテムかどうかのフラグ
	u8	saved_f		:1;	///<セーブ済みかどうか
	u8	play_mode	:3;	///<現在どこにチャレンジ中か?
	u8	partner		:3;	///<現在誰と組んでいるか?
	u8	dummy;			///<4byte境界ダミー

	u8	tower_round;		///<バトルタワー今何人目？

	u8	wifi_rec_down;		///<勝ち抜きまでに倒されたポケモン数
	u16	wifi_rec_turn;		///<勝ち抜きにかかったターン数
	u16	wifi_rec_damage;	///<勝ち抜きまでに受けたダメージ数

	u8	member_poke[BTOWER_STOCK_MEMBER_MAX];		///<選択したポケモンの位置
	u16	trainer_no[BTOWER_STOCK_TRAINER_MAX];		///<対戦トレーナーNo保存
	
	u32	play_rnd_seed;	///<タワープレイ変化ランダムシード保存場所

	struct	_B_TOWER_PAREPOKE_PARAM	pare_poke;	///<AIマルチのペアのポケモン再生成に必要なパラメータ
};

/**
 *	@brief	バトルタワー　スコアデータ
 *
 *	size= 20+168+168=356byte
 *	ゲームを通して保存&管理しておく、プレイヤー成績
 */
struct _BTLTOWER_SCOREWORK{
	u16	btl_point;	///<バトルポイント
	u8	wifi_lose;	///<連続敗戦カウント
	u8	wifi_rank;	///<WiFiランク

	u32	day_rnd_seed;	///<タワー用日付変化ランダムシード保存場所
	
	union{
		struct{
		u16	silver_get:1;		///<シルバートロフィーゲット
		u16	gold_get:1;			///<ゴールドトロフィーゲット
		u16	silver_ready:1;		///<シルバー貰えます
		u16	gold_ready:1;		///<ゴールド貰えます
		u16	wifi_lose_f:1;		///<wifi連続敗戦フラグ
		u16	wifi_update:1;		///<wifi成績アップロードフラグ
		u16	wifi_poke_data:1;	///<wifiポケモンデータストック有りナシフラグ
		u16	single_poke_data:1;	///<singleポケモンデータストック有りナシフラグ
		u16	single_record:1;	///<シングルレコード挑戦中フラグ
		u16	double_record:1;	///<ダブルレコード挑戦中フラグ
		u16	multi_record:1;		///<マルチレコード挑戦中フラグ
		u16	cmulti_record:1;	///<通信マルチレコード挑戦中フラグ
		u16	wifi_record:1;		///<Wifiレコード挑戦中フラグ
		u16	copper_get:1;		///<カッパートロフィーゲット
		u16	copper_ready:1;		///<カッパー貰えます
		u16	:1;	///<境界ダミー
		};
		u16	flags;
	};
	u16	padding;	///<4byte境界ダミー
	
	u16	tower_stage[5];		///<バトルタワー周回数

	//WiFiチャレンジデータ
	u16	wifi_score;	///<WiFi成績
	//WiFiポケモンデータストック
	struct _B_TOWER_POKEMON	wifi_poke[3];
	//トレーナーロード用シングルデータストック
	struct _B_TOWER_POKEMON	single_poke[3];
	
};

/**
 *	@brief	バトルタワー プレイヤーメッセージデータ
 *
 *	8*4=32byte
 */
struct _BTLTOWER_PLAYER_MSG{
	PMS_DATA	msg[4];	///<自分用メッセージ
};


/**
 *	@brief	バトルタワー WIFI プレイヤーデータ
 *
 *	56*3+60=228byte
 */
struct _BTLTOWER_WIFI_PLAYER{
	struct _B_TOWER_POKEMON	poke[3];
	
	STRCODE	name[PERSON_NAME_SIZE+EOM_SIZE];	//トレーナー名((PERSON_NAME_SIZE:7)+(EOM_SIZE:1))*(STRCODE:u16)=16

	u8	casette_version;					//カセットversion
	u8	lang_version;						//言語バージョン
	u8	country_code;						//国コード
	u8	address;							//住んでいるところ

	u32	id_no;								//IDNo	

	u16	leader_word[4];						//リーダーメッセージ

	union{
		struct{
		u8	ngname_f:1;						//NGネームフラグ
		u8	gender:1;						//性別
		u8			:6;						//あまり6bit
		};
		u8	flags;
	};
	u8	tr_type;							//トレーナータイプ
	u16	appear_word[4];						//登場メッセージ	
	u16	win_word[4];						//勝利メッセージ	
	u16	lose_word[4];						//敗退メッセージ	

	u16	result;								//成績
};


/**
 *	@brief	バトルタワー WIFI DLデータ
 *
 *	280byte+1596(228*7)byte+1020(34*30)byte=2836byte
 */
struct _BTLTOWER_WIFI_DATA{
	GF_DATE	day;	///<DLした日付4byte
	u8		flags[BTOWER_ROOM_DATA_FLAGS_LEN];	///<DL済みフラグエリア(2000bit)
	u8		player_data_f;	///<プレイヤーデータが有効かどうか？
	u8		leader_data_f;	///<リーダーデータが有効かどうか？

	//DLデータのルームID
	u8	player_room;	///<プレイヤーデータルームNo
	u8	player_rank;	///<プレイヤーデータルームランク
	u8	leader_room;	///<リーダーデータルームNo
	u8	leader_rank;	///<リーダーデータルームランク

	///プレイヤーデータ
	struct _BTLTOWER_WIFI_PLAYER player[BTOWER_STOCK_WIFI_PLAYER_MAX];
	///リーダーデータ
	struct _B_TOWER_LEADER_DATA leader[BTOWER_STOCK_WIFI_LEADER_MAX];
};

/**
 *	@brief	バトルタワー　WiFi DLデータ
 */
struct _BTLTOWER_SAVEWORK{
	//プレイデータ
	struct _BTLTOWER_PLAYWORK	play;
	//スコアデータ
	struct _BTLTOWER_SCOREWORK	score;
	//WiFi プレイヤーメッセージデータ
	struct _BTLTOWER_PLAYER_MSG	player_msg;
	//WiFi データ
	struct _BTLTOWER_WIFI_DATA	wifi;
};

#endif	//__H_BTOWER_LOCAL_H__
