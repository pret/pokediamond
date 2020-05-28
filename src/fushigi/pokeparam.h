#ifndef _POKEPARAM_H
#define _POKEPARAM_H

#define MONS_NAME_SIZE		10		// ポケモン名の長さ
#define PERSON_NAME_SIZE 7

typedef struct
{
	u16	monsno;
	u16 item;
	u32	exp;
	u8	pp_count;
	u8	friend;
	u16	amari;
}PokemonPara1;

typedef struct
{
	u16	waza[4];
	u8	pp[4];								//12バイト
}PokemonPara2;

typedef struct
{
	u8	hp_exp;
	u8	pow_exp;
	u8	def_exp;
	u8	agi_exp;
	u8	spepow_exp;
	u8	spedef_exp;
	u8	style;						//	かっこよさ
	u8	beautiful;					//	うつくしさ
	u8	cute;						//	かわいさ
	u8	clever;						//　かしこさ
	u8	strong;						//	たくましさ
	u8	fur;						//	毛艶	12バイト
}PokemonPara3;
	
typedef struct
{
	u32	pokerus		:8;
	u32	get_place	:8;				//	捕まえた場所
	u32	get_level	:7;				//	捕まえたレベル
	u32	get_cassette:4;				//	捕まえたカセット（カラーバージョン）
	u32	get_ball	:4;				//	捕まえたボール
	u32	oyasex		:1;				//	親の性別
	
	u32	hp_rnd		:5;
	u32	pow_rnd		:5;
	u32	def_rnd		:5;
	u32	agi_rnd		:5;
	u32	spepow_rnd	:5;
	u32	spedef_rnd	:5;
	u32	tamago_flag	:1;				//	0:タマゴじゃない1:タマゴだよ
	u32	speabi		:1;				//	特殊能力（0:特殊能力1　1:特殊能力2）

	u32	stylemedal			:3;		//	かっこよさ勲章
	u32	beautifulmedal		:3;		//	うつくしさ勲章
	u32	cutemedal			:3;		//	かわいさ勲章
	u32	clevermedal			:3;		//	かしこさ勲章
	u32	strongmedal			:3;		//	たくましさ勲章
	u32	champ_ribbon		:1;		//	チャンプリボン
	u32	winning_ribbon		:1;		//	ウィニングリボン
	u32	victory_ribbon		:1;		//	ビクトリーリボン
	u32	bromide_ribbon		:1;		//	ブロマイドリボン
	u32	ganba_ribbon		:1;		//	がんばリボン
	u32	marine_ribbon		:1;		//	マリンリボン
	u32	land_ribbon			:1;		//	ランドリボン
	u32	sky_ribbon			:1;		//	スカイリボン
	u32	country_ribbon		:1;		//	カントリーリボン
	u32	national_ribbon		:1;		//	ナショナルリボン
	u32	earth_ribbon		:1;		//	アースリボン
	u32	world_ribbon		:1;		//	ワールドリボン
	u32	amari_ribbon		:4;		//	あまってます
	u32	event_get_flag		:1;		//	イベントで配布されたことを示すフラグ
}PokemonPara4;

typedef struct
{
	u32	personal_rnd;
	u32	id_no;
	u8	nickname[MONS_NAME_SIZE];			//M_N_S=10
	u8	country_code;						//国コード
	u8	fusei_tamago_flag	:1;				//データ改ざん時のタマゴフラグ
	u8	poke_exist_flag		:1;				//ポケモン存在フラグ
	u8	egg_exist_flag		:1;				//タマゴとしての存在フラグ
	u8	poke_no_move_flag	:1;				//ポケモンを移動できないようにするためのフラグ
											//（対メモリーボックス用）
	u8						:4;
	u8	oyaname[PERSON_NAME_SIZE];			//P_N_S=7
	u8	mark;								//ポケモンにつけるマーク（ボックス）
	u16	checksum;
	u16	amari;								//	続編のための余り領域
											//32バイト
	u8	paradata[sizeof(PokemonPara1)+
				 sizeof(PokemonPara2)+
				 sizeof(PokemonPara3)+
				 sizeof(PokemonPara4)];
}PokemonPasoParam;

#define BOX_NUM		(14)		//ボックスの数
#define BOX_X_MAX	(6)		///< 横に何体ポケモンを表示するか
#define BOX_Y_MAX	(5)		///< 縦に何体ポケモンを表示するか
#define BOX_POKE_NUM (BOX_X_MAX*BOX_Y_MAX)	///< １ボックスのポケモン最大数
#define PM_TAIHI	(BOX_POKE_NUM*2)//BoxPMStructの一番後ろ
#define BOXNAME_MAX  (8)
#define	EOM_SIZE			1	// 終了コードの長さ

typedef struct{
	u8 CurrentBoxNo;
	PokemonPasoParam	PPPBox[BOX_NUM][BOX_POKE_NUM];
	u8  BoxName[BOX_NUM][BOXNAME_MAX+EOM_SIZE];
	u8  BGNum[BOX_NUM];
}POKEBOX_SAVE_DATA;

#endif