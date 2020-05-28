
//==============================================================================================
/**
 * @file	d_fight.h
 * @brief	デバッグファイト
 * @author	sogabe
 * @date	2006.04.13
 */
//==============================================================================================

#ifndef	__D_FIGHT_H__
#define	__D_FIGHT_H__

//==============================================================================================
//
//	構造体
//
//==============================================================================================

enum{
	STATUS_HP=0,
	STATUS_POW,
	STATUS_DEF,
	STATUS_AGI,
	STATUS_SPEPOW,
	STATUS_SPEDEF,
	STATUS_MAX
};

enum{
	COND_NORMAL=0,
	COND_NEMURI,
	COND_DOKU,
	COND_YAKEDO,
	COND_MAHI,
	COND_KOORI,
	COND_DOKUDOKU,

	DF_COND_MAX=COND_DOKUDOKU,
};

static	const	cond_table[]={
	CONDITION_NOCHECK,
	CONDITION_NEMURI,
	CONDITION_DOKU,
	CONDITION_YAKEDO,
	CONDITION_MAHI,
	CONDITION_KOORI,
	CONDITION_DOKUDOKU,
};

typedef struct{
	u32	exp;
	u32	id;
	u32	personal_rnd;

	u32	waza[4];

	u32	pp[4];
	u32	pp_count[4];

	u32	mons_no;
	u32	item;

	u32	level;
	u32	sex;
	u32	chr;
	u32	condition;

	u32	friend;
	u32	pokerus;
	u32	speabi;
	u32	fur;

	u32	status_rnd[STATUS_MAX];
	u32	status_exp[STATUS_MAX];

	u32	get_place;
	u32	get_level;
	u32	get_cassette;
	u32	get_ball;

	u32	style;
	u32	beautiful;
	u32	cute;
	u32	clever;

	u32	strong;

	u32	hp_max;
	u32	default_hp;
	u32	speabino;
	u32	speabino_set;

	u32	rare;
	u32	form_no;
	u32	egg_flag;
}DEBUG_POKEMON_PARAM;

typedef struct{
	DEBUG_POKEMON_PARAM	dpp[12];
	int					ground;
	int					bg;
	int					weather;
	int					time_zone;
	int					my_sex;
	int					fight_type;
	int					trainer_id;
	int					rule;
	int					effect_flag;
	int					msg_speed;
	u32					ai_bit;
	int					version;
	u32					battle_status_flag;
}DEBUG_SAVE_PARAM;

typedef struct{
	GF_BGL_INI			*bgl;
	GF_BGL_BMPWIN		*win_m;
	GF_BGL_BMPWIN		*win_s;
	int					seq_no;
	int					sub_seq_no;
	int					sub_act_seq_no;
	BOOL				end_flag;
	MSGDATA_MANAGER		*man_msg;
	MSGDATA_MANAGER		*man_poke;
	MSGDATA_MANAGER		*man_waza;
	MSGDATA_MANAGER		*man_chr;
	MSGDATA_MANAGER		*man_speabi;
	MSGDATA_MANAGER		*man_item;
	int					cur_pos_m;
	int					cur_pos_s;
	int					cur_pos_keta;
	int					page;
	int					flag;
	int					put_req;
	STRBUF				*msg_buf;
	WORDSET				*wordset;
	PROC				*proc;
	BATTLE_PARAM		*param;
	DEBUG_SAVE_PARAM	dsp;
	POKEMON_PARAM		*pp;
	SAVEDATA			*sv;
	DEBUG_POKEMON_PARAM	dpp_temp;
	SHINKA_WORK			*sw;
	int					auto_timer;
	int					trainer_id;
	int					bt_trainer_id;
}DEBUG_FIGHT_PARAM;

typedef BOOL (*DF_FUNC)(DEBUG_FIGHT_PARAM *,DEBUG_POKEMON_PARAM *);

typedef struct
{
	u8		cursor_pos_x;	//カーソルX位置
	u8		cursor_pos_y;	//カーソルY位置
	u8		move_up;		//上キーを押したときの移動先
	u8		move_down;		//下キーを押したときの移動先
	u8		move_left;		//左キーを押したときの移動先
	u8		move_right;		//右キーを押したときの移動先
	DF_FUNC	a_button_act;	//Aボタンを押したときのアクション
}MENU_LIST_PARAM;

//==================================================================================================
//
//	データ
//
//==================================================================================================

#define	CREATE_HEAP_SIZE	(0x28000)	//CreateHeapSize

#define	CUR_DEL				(0)
#define	CUR_PUT				(1)

#define	MINE_X				(24)		//「じぶん」表示X座標
#define	MINE_Y				(8)			//「じぶん」表示Y座標
#define	ENEMY_X				(152)		//「あいて」表示X座標
#define	ENEMY_Y				(8)			//「あいて」表示Y座標

#define	POKE_TOP			(28)

#define	MINE_POKE_X			(24)		//じぶんの手持ちポケモン1体目表示X座標
#define	MINE_POKE_Y			(POKE_TOP)	//じぶんの手持ちポケモン1体目表示Y座標
#define	MINE_POKE_Y_OFS		(16)		//じぶんの手持ちポケモンY座標オフセット

#define	ENEMY_POKE_X		(152)		//あいての手持ちポケモン1体目表示X座標
#define	ENEMY_POKE_Y		(POKE_TOP)	//あいての手持ちポケモン1体目表示Y座標
#define	ENEMY_POKE_Y_OFS	(16)		//あいての手持ちポケモンY座標オフセット

#define	GROUND_TOP			(128)

#define	GROUND_X			(24)			//「ちけい」表示X座標
#define	GROUND_Y			(GROUND_TOP)	//「ちけい」表示Y座標

#define	BG_X				(104)			//「ちけい」表示X座標
#define	BG_Y				(GROUND_TOP)	//「ちけい」表示Y座標

#define	WEATHER_X			(184)			//「てんこう」表示X座標
#define	WEATHER_Y			(GROUND_TOP)	//「てんこう」表示Y座標

#define	RULE_DATA_X			(24)			//「せんとうルール」表示X座標
#define	RULE_DATA_Y			(GROUND_TOP+16)	//「せんとうルール」表示Y座標

#define	EFF_FLAG_DATA_X		(104)			//「エフェクトＯＮ／ＯＦＦ」表示X座標
#define	EFF_FLAG_DATA_Y		(GROUND_TOP+16)	//「エフェクトＯＮ／ＯＦＦ」表示Y座標

#define	MSG_SPEED_DATA_X	(184)			//「メッセージスピード」表示X座標
#define	MSG_SPEED_DATA_Y	(GROUND_TOP+16)	//「メッセージスピード」表示Y座標

#define	MYSEX_X				(24)			//「じぶんのせいべつ」表示X座標
#define	MYSEX_Y				(GROUND_TOP+32)	//「じぶんのせいべつ」表示Y座標

#define	TIMEZONE_X			(96)			//「タイムゾーン」表示X座標
#define	TIMEZONE_Y			(GROUND_TOP+32)	//「タイムゾーン」表示Y座標

#define	MYSEX_DATA_X		(24)			//「じぶんのせいべつ」データ表示X座標
#define	MYSEX_DATA_Y		(GROUND_TOP+32)	//「じぶんのせいべつ」データ表示Y座標

#define	FIGHT_TYPE_X		(24)			//「せんとうタイプ」表示X座標
#define	FIGHT_TYPE_Y		(GROUND_TOP+32)	//「せんとうタイプ」表示Y座標

#define	FIGHT_TYPE_DATA_X	(152)			//「せんとうタイプ」データ表示X座標
#define	FIGHT_TYPE_DATA_Y	(GROUND_TOP+32)	//「せんとうタイプ」データ表示Y座標

#define	LOAD_X				(24)
#define	LOAD_Y				(GROUND_TOP+48)

#define	SAVE_X				(152)
#define	SAVE_Y				(GROUND_TOP+48)

#define	VERSION_DATA_X		(240)			//「サーババージョン」データ表示X座標
#define	VERSION_DATA_Y		(GROUND_TOP+48)	//「サーババージョン」データ表示Y座標

#define	MINE_POKE1_CUR_X	(12)			//じぶんの手持ちポケモン1体目カーソル表示X座標
#define	MINE_POKE1_CUR_Y	(POKE_TOP)		//じぶんの手持ちポケモン1体目カーソル表示Y座標
#define	MINE_POKE2_CUR_X	(12)			//じぶんの手持ちポケモン2体目カーソル表示X座標
#define	MINE_POKE2_CUR_Y	(POKE_TOP+16)	//じぶんの手持ちポケモン2体目カーソル表示Y座標
#define	MINE_POKE3_CUR_X	(12)			//じぶんの手持ちポケモン3体目カーソル表示X座標
#define	MINE_POKE3_CUR_Y	(POKE_TOP+32)	//じぶんの手持ちポケモン3体目カーソル表示Y座標
#define	MINE_POKE4_CUR_X	(12)			//じぶんの手持ちポケモン4体目カーソル表示X座標
#define	MINE_POKE4_CUR_Y	(POKE_TOP+48)	//じぶんの手持ちポケモン4体目カーソル表示Y座標
#define	MINE_POKE5_CUR_X	(12)			//じぶんの手持ちポケモン5体目カーソル表示X座標
#define	MINE_POKE5_CUR_Y	(POKE_TOP+64)	//じぶんの手持ちポケモン5体目カーソル表示Y座標
#define	MINE_POKE6_CUR_X	(12)			//じぶんの手持ちポケモン6体目カーソル表示X座標
#define	MINE_POKE6_CUR_Y	(POKE_TOP+80)	//じぶんの手持ちポケモン6体目カーソル表示Y座標
#define	ENEMY_POKE1_CUR_X	(140)			//あいての手持ちポケモン1体目カーソル表示X座標
#define	ENEMY_POKE1_CUR_Y	(POKE_TOP)		//あいての手持ちポケモン1体目カーソル表示Y座標
#define	ENEMY_POKE2_CUR_X	(140)			//あいての手持ちポケモン2体目カーソル表示X座標
#define	ENEMY_POKE2_CUR_Y	(POKE_TOP+16)	//あいての手持ちポケモン2体目カーソル表示Y座標
#define	ENEMY_POKE3_CUR_X	(140)			//あいての手持ちポケモン3体目カーソル表示X座標
#define	ENEMY_POKE3_CUR_Y	(POKE_TOP+32)	//あいての手持ちポケモン3体目カーソル表示Y座標
#define	ENEMY_POKE4_CUR_X	(140)			//あいての手持ちポケモン4体目カーソル表示X座標
#define	ENEMY_POKE4_CUR_Y	(POKE_TOP+48)	//あいての手持ちポケモン4体目カーソル表示Y座標
#define	ENEMY_POKE5_CUR_X	(140)			//あいての手持ちポケモン5体目カーソル表示X座標
#define	ENEMY_POKE5_CUR_Y	(POKE_TOP+64)	//あいての手持ちポケモン5体目カーソル表示Y座標
#define	ENEMY_POKE6_CUR_X	(140)			//あいての手持ちポケモン6体目カーソル表示X座標
#define	ENEMY_POKE6_CUR_Y	(POKE_TOP+80)	//あいての手持ちポケモン6体目カーソル表示Y座標

#define	GROUND_CUR_X		(12)			//「ちけい」カーソル表示X座標
#define	GROUND_CUR_Y		(GROUND_TOP)	//「ちけい」カーソル表示Y座標

#define	BG_CUR_X			(92)			//「はいけい」カーソル表示X座標
#define	BG_CUR_Y			(GROUND_TOP)	//「はいけい」カーソル表示Y座標

#define	WEATHER_CUR_X		(172)			//「はいけい」カーソル表示X座標
#define	WEATHER_CUR_Y		(GROUND_TOP)	//「はいけい」カーソル表示Y座標

#define	RULE_CUR_X			(12)			//「せんとうルール」カーソル表示X座標
#define	RULE_CUR_Y			(GROUND_TOP+16)	//「せんとうルール」カーソル表示Y座標

#define	EFFECT_FLAG_CUR_X	(92)			//「技エフェクトON/OFF」カーソル表示X座標
#define	EFFECT_FLAG_CUR_Y	(GROUND_TOP+16)	//「技エフェクトON/OFF」カーソル表示Y座標

#define	MSG_SPEED_CUR_X		(172)			//「メッセージスピード」カーソル表示X座標
#define	MSG_SPEED_CUR_Y		(GROUND_TOP+16)	//「メッセージスピード」カーソル表示Y座標

#define	MYSEX_CUR_X			(12)			//「じぶんのせいべつ」カーソル表示X座標
#define	MYSEX_CUR_Y			(GROUND_TOP+32)	//「じぶんのせいべつ」カーソル表示Y座標

#define	TIMEZONE_CUR_X		(84)			//「タイムゾーン」カーソル表示X座標
#define	TIMEZONE_CUR_Y		(GROUND_TOP+32)	//「タイムゾーン」カーソル表示Y座標

#define	FIGHT_TYPE_CUR_X	(140)			//「せんとうタイプ」カーソル表示X座標
#define	FIGHT_TYPE_CUR_Y	(GROUND_TOP+32)	//「せんとうタイプ」カーソル表示Y座標

#define	LOAD_CUR_X			(12)
#define	LOAD_CUR_Y			(GROUND_TOP+48)

#define	SAVE_CUR_X			(140)
#define	SAVE_CUR_Y			(GROUND_TOP+48)

#define	VERSION_CUR_X		(VERSION_DATA_X-12)		//「サーババージョン」カーソル表示X座標
#define	VERSION_CUR_Y		(GROUND_TOP+48)			//「サーババージョン」カーソル表示Y座標

//メインスクリーンメニューデータ
enum{
	MS_MINE_POKE_1=0,
	MS_MINE_POKE_2,
	MS_MINE_POKE_3,
	MS_MINE_POKE_4,
	MS_MINE_POKE_5,
	MS_MINE_POKE_6,
	MS_ENEMY_POKE_1,
	MS_ENEMY_POKE_2,
	MS_ENEMY_POKE_3,
	MS_ENEMY_POKE_4,
	MS_ENEMY_POKE_5,
	MS_ENEMY_POKE_6,
	MS_GROUND,
	MS_BG,
	MS_WEATHER,
	MS_RULE,
	MS_EFFECT_FLAG,
	MS_MSG_SPEED,
	MS_MYSEX,
	MS_TIMEZONE,
	MS_FIGHT_TYPE,
	MS_LOAD,
	MS_SAVE,
	MS_VERSION,
	MS_END
};

#define	NO_MOVE		(0xff)

enum{
	MENU1_KIND=0,
	MENU1_RARE,
	MENU1_LEVEL,
	MENU1_EXP,
	MENU1_SEX,
	MENU1_CHR,
	MENU1_HP_RND,
	MENU1_POW_RND,
	MENU1_DEF_RND,
	MENU1_AGI_RND,
	MENU1_SPEPOW_RND,
	MENU1_SPEDEF_RND,
	MENU1_HP_EXP,
	MENU1_POW_EXP,
	MENU1_DEF_EXP,
	MENU1_AGI_EXP,
	MENU1_SPEPOW_EXP,
	MENU1_SPEDEF_EXP
};

#define	MENU1_LIST_L_X		(24)
#define	MENU1_LIST_R_X		(140)
#define	MENU1_LIST_Y		(8)
#define	MENU1_LIST_OFS		(16)

#define	RARE_LIST_X			(180)
#define	EXP_LIST_X			(112)
#define	CHR_LIST_X			(112)

#define	KIND_CUR_X			(MENU1_LIST_L_X-12)
#define	KIND_CUR_Y			(MENU1_LIST_Y+MENU1_LIST_OFS*0)
#define	RARE_CUR_X			(RARE_LIST_X-12)
#define	RARE_CUR_Y			(MENU1_LIST_Y+MENU1_LIST_OFS*0)
#define	LEVEL_CUR_X			(MENU1_LIST_L_X-12)
#define	LEVEL_CUR_Y			(MENU1_LIST_Y+MENU1_LIST_OFS*1)
#define	EXP_CUR_X			(EXP_LIST_X-12)
#define	EXP_CUR_Y			(MENU1_LIST_Y+MENU1_LIST_OFS*1)
#define	SEX_CUR_X			(MENU1_LIST_L_X-12)
#define	SEX_CUR_Y			(MENU1_LIST_Y+MENU1_LIST_OFS*2)
#define	CHR_CUR_X			(CHR_LIST_X-12)
#define	CHR_CUR_Y			(MENU1_LIST_Y+MENU1_LIST_OFS*2)
#define	HP_RND_CUR_X		(MENU1_LIST_L_X-12)
#define	HP_RND_CUR_Y		(MENU1_LIST_Y+MENU1_LIST_OFS*3)
#define	POW_RND_CUR_X		(MENU1_LIST_L_X-12)
#define	POW_RND_CUR_Y		(MENU1_LIST_Y+MENU1_LIST_OFS*4)
#define	DEF_RND_CUR_X		(MENU1_LIST_L_X-12)
#define	DEF_RND_CUR_Y		(MENU1_LIST_Y+MENU1_LIST_OFS*5)
#define	AGI_RND_CUR_X		(MENU1_LIST_L_X-12)
#define	AGI_RND_CUR_Y		(MENU1_LIST_Y+MENU1_LIST_OFS*6)
#define	SPEPOW_RND_CUR_X	(MENU1_LIST_L_X-12)
#define	SPEPOW_RND_CUR_Y	(MENU1_LIST_Y+MENU1_LIST_OFS*7)
#define	SPEDEF_RND_CUR_X	(MENU1_LIST_L_X-12)
#define	SPEDEF_RND_CUR_Y	(MENU1_LIST_Y+MENU1_LIST_OFS*8)
#define	HP_EXP_CUR_X		(MENU1_LIST_R_X-12)
#define	HP_EXP_CUR_Y		(MENU1_LIST_Y+MENU1_LIST_OFS*3)
#define	POW_EXP_CUR_X		(MENU1_LIST_R_X-12)
#define	POW_EXP_CUR_Y		(MENU1_LIST_Y+MENU1_LIST_OFS*4)
#define	DEF_EXP_CUR_X		(MENU1_LIST_R_X-12)
#define	DEF_EXP_CUR_Y		(MENU1_LIST_Y+MENU1_LIST_OFS*5)
#define	AGI_EXP_CUR_X		(MENU1_LIST_R_X-12)
#define	AGI_EXP_CUR_Y		(MENU1_LIST_Y+MENU1_LIST_OFS*6)
#define	SPEPOW_EXP_CUR_X	(MENU1_LIST_R_X-12)
#define	SPEPOW_EXP_CUR_Y	(MENU1_LIST_Y+MENU1_LIST_OFS*7)
#define	SPEDEF_EXP_CUR_X	(MENU1_LIST_R_X-12)
#define	SPEDEF_EXP_CUR_Y	(MENU1_LIST_Y+MENU1_LIST_OFS*8)

#define	PARAM1_Y			(MENU1_LIST_Y+MENU1_LIST_OFS*9+4)
#define	PARAM2_Y			(MENU1_LIST_Y+MENU1_LIST_OFS*10+4)

#define	PARAM_POW_X			(4)
#define	PARAM_POW_NUM_X		(30)
#define	PARAM_OFS_X			(50)

#define	KIND_DATA_X			(72)
#define	KIND_DATA_Y			(8)
#define	KIND_NAME_X			(112)

#define	RARE_DATA_X			(180)
#define	RARE_DATA_Y			(8)

#define	LEVEL_DATA_X		(72)
#define	LEVEL_DATA_Y		(24)
#define	LEVEL_KETA			(3)

#define	EXP_DATA_X			(180)
#define	EXP_DATA_Y			(24)
#define	EXP_KETA			(7)

#define	SEX_DATA_X			(72)
#define	SEX_DATA_Y			(40)

#define	CHR_DATA_X			(180)
#define	CHR_DATA_Y			(40)

#define	STRND_DATA_X		(96)
#define	STRND_DATA_Y		(MENU1_LIST_Y+MENU1_LIST_OFS*3)
#define	STRND_DATA_OFS		(16)
#define	STRND_KETA			(2)

#define	STEXP_DATA_X		(216)
#define	STEXP_DATA_Y		(MENU1_LIST_Y+MENU1_LIST_OFS*3)
#define	STEXP_DATA_OFS		(16)
#define	STEXP_KETA			(3)

enum{
	MENU2_WAZA1=0,
	MENU2_WAZA2,
	MENU2_WAZA3,
	MENU2_WAZA4,
	MENU2_PP1,
	MENU2_PP2,
	MENU2_PP3,
	MENU2_PP4,
	MENU2_PP_COUNT1,
	MENU2_PP_COUNT2,
	MENU2_PP_COUNT3,
	MENU2_PP_COUNT4,
	MENU2_SPEABI,
	MENU2_SPEABI_SET,
	MENU2_ITEM,
	MENU2_FRIEND,
	MENU2_CONDITION,
	MENU2_DEFAULT_HP,
	MENU2_GETBALL,
};

#define	MENU2_LIST_X		(24)
#define	MENU2_LIST_Y		(8)
#define	MENU2_LIST_OFS		(16)
#define	MENU2_LIST_X_OFS1	(48)
#define	MENU2_LIST_X_OFS2	(64)
#define	MENU2_LIST_X_OFS3	(144)
#define	MENU2_LIST_X_OFS4	(200)


#define	WAZA1_CUR_X			(MENU2_LIST_X-12)
#define	WAZA1_CUR_Y			(MENU2_LIST_Y+MENU2_LIST_OFS*0)
#define	WAZA2_CUR_X			(MENU2_LIST_X-12)
#define	WAZA2_CUR_Y			(MENU2_LIST_Y+MENU2_LIST_OFS*1)
#define	WAZA3_CUR_X			(MENU2_LIST_X-12)
#define	WAZA3_CUR_Y			(MENU2_LIST_Y+MENU2_LIST_OFS*2)
#define	WAZA4_CUR_X			(MENU2_LIST_X-12)
#define	WAZA4_CUR_Y			(MENU2_LIST_Y+MENU2_LIST_OFS*3)
#define	PP1_CUR_X			(MENU2_LIST_X+MENU2_LIST_X_OFS3-12)
#define	PP1_CUR_Y			(MENU2_LIST_Y+MENU2_LIST_OFS*0)
#define	PP2_CUR_X			(MENU2_LIST_X+MENU2_LIST_X_OFS3-12)
#define	PP2_CUR_Y			(MENU2_LIST_Y+MENU2_LIST_OFS*1)
#define	PP3_CUR_X			(MENU2_LIST_X+MENU2_LIST_X_OFS3-12)
#define	PP3_CUR_Y			(MENU2_LIST_Y+MENU2_LIST_OFS*2)
#define	PP4_CUR_X			(MENU2_LIST_X+MENU2_LIST_X_OFS3-12)
#define	PP4_CUR_Y			(MENU2_LIST_Y+MENU2_LIST_OFS*3)
#define	PP_COUNT1_CUR_X		(MENU2_LIST_X+MENU2_LIST_X_OFS4-12)
#define	PP_COUNT1_CUR_Y		(MENU2_LIST_Y+MENU2_LIST_OFS*0)
#define	PP_COUNT2_CUR_X		(MENU2_LIST_X+MENU2_LIST_X_OFS4-12)
#define	PP_COUNT2_CUR_Y		(MENU2_LIST_Y+MENU2_LIST_OFS*1)
#define	PP_COUNT3_CUR_X		(MENU2_LIST_X+MENU2_LIST_X_OFS4-12)
#define	PP_COUNT3_CUR_Y		(MENU2_LIST_Y+MENU2_LIST_OFS*2)
#define	PP_COUNT4_CUR_X		(MENU2_LIST_X+MENU2_LIST_X_OFS4-12)
#define	PP_COUNT4_CUR_Y		(MENU2_LIST_Y+MENU2_LIST_OFS*3)
#define	SPEABI_CUR_X		(MENU2_LIST_X-12)
#define	SPEABI_CUR_Y		(MENU2_LIST_Y+MENU2_LIST_OFS*4)
#define	SPEABI_SET_CUR_X	(MENU2_LIST_X-12)
#define	SPEABI_SET_CUR_Y	(MENU2_LIST_Y+MENU2_LIST_OFS*5)
#define	ITEM_CUR_X			(MENU2_LIST_X-12)
#define	ITEM_CUR_Y			(MENU2_LIST_Y+MENU2_LIST_OFS*6)
#define	FRIEND_CUR_X		(MENU2_LIST_X-12)
#define	FRIEND_CUR_Y		(MENU2_LIST_Y+MENU2_LIST_OFS*7)
#define	CONDITION_CUR_X		(MENU2_LIST_X-12)
#define	CONDITION_CUR_Y		(MENU2_LIST_Y+MENU2_LIST_OFS*8)
#define	DEFAULT_HP_CUR_X	(MENU2_LIST_X-12)
#define	DEFAULT_HP_CUR_Y	(MENU2_LIST_Y+MENU2_LIST_OFS*9)
#define	GETBALL_CUR_X		(MENU2_LIST_X-12)
#define	GETBALL_CUR_Y		(MENU2_LIST_Y+MENU2_LIST_OFS*10)

#define	WAZA_NUM_X			(MENU2_LIST_X)
#define	WAZA_NUM_Y			(MENU2_LIST_Y+MENU2_LIST_OFS*0)
#define	WAZA_NUM_OFS		(MENU2_LIST_OFS)
#define	WAZA_DATA_X			(MENU2_LIST_X+8*4)
#define	WAZA_DATA_Y			(MENU2_LIST_Y+MENU2_LIST_OFS*0)
#define	WAZA_DATA_OFS		(MENU2_LIST_OFS)

#define	PP_X				(MENU2_LIST_X+MENU2_LIST_X_OFS3)
#define	PP_Y				(MENU2_LIST_Y+MENU2_LIST_OFS*0)
#define	PP_COUNT_X			(MENU2_LIST_X+MENU2_LIST_X_OFS4)
#define	PP_COUNT_Y			(MENU2_LIST_Y+MENU2_LIST_OFS*0)

#define	SPEABI_DATA_X		(MENU2_LIST_X+MENU2_LIST_X_OFS2)
#define	SPEABI_DATA_Y		(MENU2_LIST_Y+MENU2_LIST_OFS*4)
#define	SPEABI_SET_NUM_X	(MENU2_LIST_X+MENU2_LIST_X_OFS2)
#define	SPEABI_SET_NUM_Y	(MENU2_LIST_Y+MENU2_LIST_OFS*5)
#define	SPEABI_SET_DATA_X	(MENU2_LIST_X+MENU2_LIST_X_OFS2+8*4)
#define	SPEABI_SET_DATA_Y	(MENU2_LIST_Y+MENU2_LIST_OFS*5)
#define	ITEM_NUM_X			(MENU2_LIST_X+MENU2_LIST_X_OFS2)
#define	ITEM_NUM_Y			(MENU2_LIST_Y+MENU2_LIST_OFS*6)
#define	ITEM_DATA_X			(MENU2_LIST_X+MENU2_LIST_X_OFS2+8*4)
#define	ITEM_DATA_Y			(MENU2_LIST_Y+MENU2_LIST_OFS*6)
#define	FRIEND_DATA_X		(MENU2_LIST_X+MENU2_LIST_X_OFS2)
#define	FRIEND_DATA_Y		(MENU2_LIST_Y+MENU2_LIST_OFS*7)
#define	CONDITION_DATA_X	(MENU2_LIST_X+MENU2_LIST_X_OFS2)
#define	CONDITION_DATA_Y	(MENU2_LIST_Y+MENU2_LIST_OFS*8)
#define	DEFAULT_HP_DATA_X	(MENU2_LIST_X+MENU2_LIST_X_OFS2)
#define	DEFAULT_HP_DATA_Y	(MENU2_LIST_Y+MENU2_LIST_OFS*9)
#define	GETBALL_DATA_X		(MENU2_LIST_X+MENU2_LIST_X_OFS2)
#define	GETBALL_DATA_Y		(MENU2_LIST_Y+MENU2_LIST_OFS*10)

enum{
	MENU3_FORMNO=0,
	MENU3_EGG_FLAG,
};

#define	MENU3_LIST_X		(24)
#define	MENU3_LIST_Y		(8)
#define	MENU3_LIST_OFS		(16)

#define	FORMNO_X			(MENU3_LIST_X)
#define	FORMNO_Y			(MENU3_LIST_Y+MENU3_LIST_OFS*0)
#define	FORMNO_DATA_X		(MENU3_LIST_X+12*6)
#define	FORMNO_DATA_Y		(MENU3_LIST_Y+MENU3_LIST_OFS*0)
#define	FORMNO_CUR_X		(FORMNO_X-12)
#define	FORMNO_CUR_Y		(FORMNO_Y)
#define	EGG_FLAG_X			(MENU3_LIST_X)
#define	EGG_FLAG_Y			(MENU3_LIST_Y+MENU3_LIST_OFS*1)
#define	EGG_FLAG_DATA_X		(MENU3_LIST_X)
#define	EGG_FLAG_DATA_Y		(MENU3_LIST_Y+MENU3_LIST_OFS*1)
#define	EGG_FLAG_CUR_X		(EGG_FLAG_X-12)
#define	EGG_FLAG_CUR_Y		(EGG_FLAG_Y)

enum{
	SEQ_MAIN_MENU_MOVE=0,
	SEQ_A_BUTTON_ACT,
	SEQ_BATTLE_INIT,
	SEQ_BATTLE_MAIN,
	SEQ_SHINKA_INIT,
	SEQ_SHINKA_MAIN,
	SEQ_AI_FLAG_INIT,
	SEQ_AI_FLAG_MAIN,
	SEQ_AUTO_FLAG_INIT,
	SEQ_AUTO_FLAG_MAIN
};

enum{
	MOVE_MAIN=0,
	MOVE_SUB,
	MOVE_AI,
};

enum{
	MODE_NORMAL=0,
	MODE_ACTIVE,
	MODE_LOOP,
	MODE_STOP,
	MODE_DEFAULT_PARAM,
	MODE_DEFAULT_WAZA,
};

#define	TRAINER_ID_X			(24)
#define	TRAINER_ID_Y			(56)
#define	TRAINER_ID_DATA_X		(56)
#define	TRAINER_ID_DATA_Y		(56)
#define	BT_TRAINER_ID_X			(24)
#define	BT_TRAINER_ID_Y			(72)
#define	BT_TRAINER_ID_DATA_X	(56)
#define	BT_TRAINER_ID_DATA_Y	(72)

#define	NORMAL_LETTER	(1)
#define	NORMAL_SHADOW	(2)
#define	NORMAL_GROUND	(15)

#define	ACTIVE_LETTER	(3)
#define	ACTIVE_SHADOW	(2)
#define	ACTIVE_GROUND	(15)

#define	CURSOR_LETTER	(4)
#define	CURSOR_SHADOW	(2)
#define	CURSOR_GROUND	(15)

#define	PARA_UP_LETTER	(4)
#define	PARA_UP_SHADOW	(2)
#define	PARA_UP_GROUND	(15)

#define	PARA_DOWN_LETTER	(5)
#define	PARA_DOWN_SHADOW	(2)
#define	PARA_DOWN_GROUND	(15)

#define	COL_NORMAL		(GF_PRINTCOLOR_MAKE(NORMAL_LETTER,NORMAL_SHADOW,NORMAL_GROUND))
#define	COL_ACTIVE		(GF_PRINTCOLOR_MAKE(ACTIVE_LETTER,ACTIVE_SHADOW,ACTIVE_GROUND))
#define	COL_CURSOR		(GF_PRINTCOLOR_MAKE(CURSOR_LETTER,CURSOR_SHADOW,CURSOR_GROUND))
#define	COL_PARA_UP		(GF_PRINTCOLOR_MAKE(PARA_UP_LETTER,PARA_UP_SHADOW,PARA_UP_GROUND))
#define	COL_PARA_DOWN	(GF_PRINTCOLOR_MAKE(PARA_DOWN_LETTER,PARA_DOWN_SHADOW,PARA_DOWN_GROUND))

enum{
	NUM_CALC_NONE=0,
	NUM_CALC_MOVE,
	NUM_CALC_CHANGE,
	NUM_CALC_END,
};

enum{
	FT_YASEI=0,
	FT_TRAINER,
	FT_2vs2,
	FT_1vs1_SIO_P,
	FT_1vs1_SIO_C,
	FT_2vs2_SIO_P,
	FT_2vs2_SIO_C,
	FT_MULTI_SIO_P,
	FT_MULTI_SIO_C,
	FT_1vs1_WIFI_P,
	FT_1vs1_WIFI_C,
	FT_1vs1_SAFARI,
	FT_1vs1_POKE_PARK,
	FT_1vs1_GET_DEMO,
	FT_2vs2_YASEI,
	FT_AI_MULTI,
	FT_BT_MULTI_SIO_P,
	FT_BT_MULTI_SIO_C,
	FIGHT_TYPE_MAX

};

#define	DEBUG_FIGHT_END_KEY	(PAD_BUTTON_L|PAD_BUTTON_R|PAD_BUTTON_SELECT)

#define	SUB_PAGE_MAX	(2)

#define	AUTO_BATTLE			(0x04)
#define	AUTO_BATTLE_WAIT	(30*5)

//==================================================================================================
//
//	extern宣言
//
//==================================================================================================

extern	BOOL	DebugFightStart(DEBUG_FIGHT_PARAM *dfp);
extern	void	DebugFightBGCreate(DEBUG_FIGHT_PARAM *dfp,GF_BGL_INI *bgl);
extern	void	DebugFightPokemonParamInit(DEBUG_POKEMON_PARAM *dpp);
extern	void	DebugFightDefaultPokeSet(DEBUG_FIGHT_PARAM *dfp,int pos);
extern	void	DebugFightAIScreenCreate(DEBUG_FIGHT_PARAM *dfp);
extern	void	DebugFightAutoScreenCreate(DEBUG_FIGHT_PARAM *dfp);
extern	void	DebugFightMainScreenCreate(DEBUG_FIGHT_PARAM *dfp);
extern	void	DebugFightSubScreenCreate(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp,int page);
extern	void	CursorMove(DEBUG_FIGHT_PARAM *dfp,int side,int pos,int mode);
extern	const	MENU_LIST_PARAM	mlp_m[];
extern	const	MENU_LIST_PARAM	*	const	mlp_s_list[];

#endif
