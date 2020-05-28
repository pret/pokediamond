//============================================================================================
/**
 * @file	b_tower_data.h
 * @bfief	バトルタワー用定義
 * @author	HisashiSogabe/Miyuki Iwasawa
 * @date	06.04.20
 */
//============================================================================================

#ifndef __B_TOWER_H_
#define __B_TOWER_H_

//============================================================================================
/**
 *	ロムデータ
 */
//============================================================================================

//バトルタワーロム用トレーナーデータ構造体
//トレーナー名、会話データは、gmmで管理（トレーナーIDから取得）
typedef struct{
	u16		tr_type;				//トレーナータイプ
	u16		use_poke_cnt;			//使用可能ポケモン数	
	u16		use_poke_table[1];		//使用可能ポケモンINDEXテーブル（可変長）
}B_TOWER_TRAINER_ROM_DATA;

//バトルタワーロム用ポケモンデータ構造体
typedef struct{
	u16		mons_no;				//モンスターナンバー
	u16		waza[WAZA_TEMOTI_MAX];	//所持技
	u8		exp_bit;				//努力値振り分けビット
	u8		chr;					//性格
	u16		item_no;				//装備道具
	u16		dummy;					//4バイト境界補正
}B_TOWER_POKEMON_ROM_DATA;

//============================================================================================
/**
 *	Wifiデータ
 */
//============================================================================================
/**
 * @biref	タワー用ポケモンデータ型
 * セーブデータとやり取りするのでsavedata/b_tower.hにtypedef定義を切り
 * 不完全ポインタでやり取りできるようにしておく
 */
struct _B_TOWER_POKEMON{
	union{
		struct{
			u16	mons_no:11;	///<モンスターナンバー
			u16	form_no:5;	///<モンスターナンバー
		};
		u16	mons_param;
	};
	u16	item_no;	///<装備道具

	u16	waza[WAZA_TEMOTI_MAX];		///<所持技

	u32	id_no;					///<IDNo
	u32	personal_rnd;			///<個性乱数

	union{
		struct{
		u32	hp_rnd		:5;		///<HPパワー乱数
		u32	pow_rnd		:5;		///<POWパワー乱数
		u32	def_rnd		:5;		///<DEFパワー乱数
		u32	agi_rnd		:5;		///<AGIパワー乱数
		u32	spepow_rnd	:5;		///<SPEPOWパワー乱数
		u32	spedef_rnd	:5;		///<SPEDEFパワー乱数
		u32	ngname_f	:1;		///<NGネームフラグ
		u32				:1;		//1ch 余り
		};
		u32 power_rnd;
	};

	union{
		struct{
		u8	hp_exp;				///<HP努力値
		u8	pow_exp;			///<POW努力値
		u8	def_exp;			///<DEF努力値
		u8	agi_exp;			///<AGI努力値
		u8	spepow_exp;			///<SPEPOW努力値
		u8	spedef_exp;			///<SPEDEF努力値
		};
		u8 exp[6];
	};
	union{
		struct{
		u8	pp_count0:2;	///<技1ポイントアップ
		u8	pp_count1:2;	///<技2ポイントアップ
		u8	pp_count2:2;	///<技3ポイントアップ
		u8	pp_count3:2;	///<技4ポイントアップ
		};
		u8 pp_count;
	};

	u8	country_code;			///<国コード

	u8	tokusei;				///<特性
	u8	natuki;				///<なつき度

	///ニックネーム ((MONS_NAME_SIZE:10)+(EOM_SIZE:1))*(STRCODE:u16)=22
	STRCODE	nickname[MONS_NAME_SIZE+EOM_SIZE];
};

//タワートレーナーデータ
typedef struct _B_TOWER_TRAINER{
	u32		player_id;	///<トレーナーのID
	u16		tr_type;	///<トレーナータイプ
	u16		dummy;		///<ダミー
	STRCODE	name[PERSON_NAME_SIZE+EOM_SIZE];
	
	u16		appear_word[4];						//登場メッセージ	
	u16		win_word[4];						//勝利メッセージ	
	u16		lose_word[4];						//敗退メッセージ
}B_TOWER_TRAINER;

//バトルタワー　対戦相手データ構造体
struct _B_TOWER_PARTNER_DATA{
	B_TOWER_TRAINER	bt_trd;			//トレーナーデータ
	struct _B_TOWER_POKEMON	btpwd[4];		//持ちポケモンデータ
};


/**
 * @brief	Wifiバトルタワーリーダーデータ構造体
 * セーブデータとやり取りするのでsavedata/b_tower.hにtypedef定義を切り
 * 不完全ポインタでやり取りできるようにしておく
 */
struct _B_TOWER_LEADER_DATA{
	STRCODE	name[PERSON_NAME_SIZE+EOM_SIZE];	//トレーナー名((PERSON_NAME_SIZE:7)+(EOM_SIZE:1))*(STRCODE:u16)=16

	u8		casette_version;				//カセットバージョン
	u8		lang_version;					//言語バージョン
	u8		country_code;					//国コード
	u8		address;						//住んでいるところ

	u8		id_no[4];						//!< プレイヤーID(u32型だが構造体サイズを34にするためu8[4]にしている)
//	u32		id_no;							//IDNo	

	u16		leader_word[4];					//リーダーメッセージ

	union{
		struct{
			u8	ngname_f:1;	//NGネームフラグ(onならNGネーム)
			u8	gender	:1;	//性別
			u8			:6;	//あまり6bit
		};
		u8	flags;
	};
	u8	padding;							///<パディング
};

/**
 *	@biref	タワーAIマルチペアの保存が必要なポケモンパラメータ
 *
 * セーブデータとやり取りするのでsavedata/b_tower.hにtypedef定義を切り
 * 不完全ポインタでやり取りできるようにしておく
 */
struct _B_TOWER_PAREPOKE_PARAM{
	u32	poke_id;	///<ポケモンのid保存
	u16	poke_no[BTOWER_STOCK_PAREPOKE_MAX];	///<タワーデータ内ポケモンデータ参照index0-999
	u32	poke_rnd[BTOWER_STOCK_PAREPOKE_MAX];	///<ポケモンの個性乱数保存
};

#endif __B_TOWER_H_
