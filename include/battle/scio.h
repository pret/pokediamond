
//============================================================================================
/**
 * @file	scio.h
 * @bfief	戦闘サーバ、クライアントデータ送受信関数
 * @author	HisashiSogabe
 * @date	05.07.19
 */
//============================================================================================

#ifndef __SCIO_H_
#define __SCIO_H_

#include	"system/gamedata.h"
#include	"battle/fight.h"
#include	"system/clact_tool.h"

enum{
	SCIO_SERVER=0,
	SCIO_CLIENT,
	SCIO_SERVER_QUE
};

//POKEMON_ENCOUNT用
typedef struct{
	u8	command_code;		//命令コードインデックス
	u8	sex		:2;			//性別
	u8	rare	:1;			//レアかどうか？
	u8	form_no	:5;
	u16	monsno;				//ポケモンナンバー
	u32	personal_rnd;		//個性乱数
	int	voice;
	u16	wazano[WAZA_TEMOTI_MAX];
	u16	pp[WAZA_TEMOTI_MAX];
	u16	ppmax[WAZA_TEMOTI_MAX];
	STRCODE	nickname[MONS_NAME_SIZE+EOM_SIZE];
}POKEMON_ENCOUNT_PARAM;

//POKEMON_APPEAR用
typedef struct{
	u8	command_code;		//命令コードインデックス
	u8	sex			:2;		//性別
	u8	rare		:1;		//レアかどうか？
	u8	form_no		:5;		//FormNo
	u16	monsno;				//ポケモンナンバー
	u32	personal_rnd;		//個性乱数
	int	voice;
	int	sel_mons_no;		//SelMonsNo
	int	ballID;
	int	flag;
	u16	wazano[WAZA_TEMOTI_MAX];
	u16	pp[WAZA_TEMOTI_MAX];
	u16	ppmax[WAZA_TEMOTI_MAX];
	STRCODE	nickname[MONS_NAME_SIZE+EOM_SIZE];
	int	pair_sel_mons_no;	//パートナーのSelMonsNo
	//ここから下は、みがわりのために必要
	int	migawari_flag;
	u16	wep_mons_no[CLIENT_MAX];
	u8	wep_sex[CLIENT_MAX];
	u8	wep_rare[CLIENT_MAX];
	u8	wep_form_no[CLIENT_MAX];
	u32	wep_personal_rnd[CLIENT_MAX];
}POKEMON_APPEAR_PARAM;

//POKEMON_RETURN用
typedef struct{
	u8	command_code;		//命令コードインデックス
	u8	height;				//ポケモン高さ情報
	u16	ballID;
	int	migawari_flag;

	//ここから下は、みがわりのために必要
	u16	mons_no[CLIENT_MAX];
	u8	sex[CLIENT_MAX];
	u8	rare[CLIENT_MAX];
	u8	form_no[CLIENT_MAX];
	u32	personal_rnd[CLIENT_MAX];
}POKEMON_RETURN_PARAM;

//POKEMON_INHALE用
typedef struct{
	u8	command_code;		//命令コードインデックス
	u8	height;				//ポケモン高さ情報
	u16	ballID;
}POKEMON_INHALE_PARAM;

//TRAINER_ENCOUNT用
typedef struct{
	u8	command_code;		//命令コードインデックス
	u8	tr_sex;				//トレーナーの性別
	u16	trtype;				//トレーナーID
}TRAINER_ENCOUNT_PARAM;

//TRAINER_THROW用
typedef struct{
	u8	command_code;		//命令コードインデックス
	u8	type;				//エフェクトタイプ
	u16	pair_sel_mons_no;
}TRAINER_THROW_PARAM;

//TRAINER_IN用
typedef struct{
	u8	command_code;		//命令コードインデックス
	u8	tr_sex;				//トレーナーの性別
	u16	trtype;				//トレーナーID
	int	pos;				//登場位置情報
}TRAINER_IN_PARAM;

//WAZA_SELECT用
typedef struct{
	u8			command_code;				//命令コードインデックス
	u8			sel_mons_no;
	u16			wazabit;
	u16			wazano[WAZA_TEMOTI_MAX];	//wazano
	u8			pp[WAZA_TEMOTI_MAX];		//pp
	u8			ppmax[WAZA_TEMOTI_MAX];		//ppmax
}WAZA_SELECT_PARAM;

//DIR_SELECT用
typedef struct{
	u8		sel_mons_no;				//PokemonParamの何番目か
	u8		sex		:2;					//性別
	u8		exist	:1;					//選択可否
	u8				:5;					//選択可否

	u8		status;
	u8		dummy;						//4バイト境界ダミー
	
	s16		hp;						//現在のHP
	u16		hpmax;					//現在のHPMAX
}DIR_SELECT_POKE_PARAM;

typedef struct{
	u8						command_code;	//命令コードインデックス
	u8						flag;			//1：入力画面背景を明るくしてください
	u16						range;			//効果範囲
	DIR_SELECT_POKE_PARAM	dspp[CLIENT_MAX];	
}DIR_SELECT_PARAM;

//ITEM_SELECT用
typedef struct{
	u8				command_code;		//命令コードインデックス
	u8				enc_double;			//野生2vs2戦でボールを投げれるかフラグ
	u8				waza_vanish;		//消えているかフラグ
	u8				waza_migawari;		//みがわりをだしているかフラグ
	u8				sel_mons_no[CLIENT_MAX];
	u8				list_row[CLIENT_MAX][POKEMON_TEMOTI_MAX];
	u8				shutout_flag[CLIENT_MAX];
}ITEM_SELECT_PARAM;

//POKEMON_SELECT用
typedef struct{
	u8				command_code;		//命令コードインデックス
	u8				client_no;
	u8				list_mode;
	u8				double_sel;

	u8				sel_mons_no[CLIENT_MAX];
	u8				list_row[CLIENT_MAX][POKEMON_TEMOTI_MAX];

	int				chg_waza;
	u8				no_reshuffle_client;
	u8				dummy[3];
}POKEMON_SELECT_PARAM;

//HP_GAUGE_IN用
typedef struct{
	u8	command_code;		//命令コードインデックス
	u8	level;
	s16	hp;					//現在のHP

	u16	hpmax;				//現在のHPMAX
	u8	sel_mons_no;		//選択ナンバー
	u8	status	:5;			//状態異常
	u8	sex		:2;			//性別
	u8	get_mark:1;			//捕獲フラグ

	u32	now_exp;			//現在のEXP
	u32	max_exp;			//最大EXP

	int	safari_ball;		//サファリボールの数（サファリゾーン専用）

	u8	wait;
}HP_GAUGE_IN_PARAM;

//COMMAND_SELECT用
typedef struct{
	u8		command_code;		//命令コードインデックス
	u8		sel_mons_no;
	u8		motivation[POKEMON_TEMOTI_MAX];
	u8		status[2][POKEMON_TEMOTI_MAX];

	u16		wazano[WAZA_TEMOTI_MAX];	//wazano
	u8		pp[WAZA_TEMOTI_MAX];		//pp
	u8		ppmax[WAZA_TEMOTI_MAX];		//ppmax

	s16		icon_hp;				//現在のHP
	u16		icon_hpmax;				//現在のHPMAX

	u8		icon_status;
	u8		no_reshuffle_client;
	u16		dummy;
}COMMAND_SELECT_PARAM;

//YES_NO_SELECT用
typedef struct{
	u8	command_code;		//命令コードインデックス
	u8	flag;				///<セレクトタイプ
	u16	msg_id;				///<表示するメッセージナンバー
	int	waza_no;
	int	nickname;
}YES_NO_SELECT_PARAM;

//ATTACK_MESSAGE用
typedef struct{
	u8	command_code;		//命令コードインデックス
	u8	sel_mons_no;		//先頭から何番目のポケモン？
	u16	waza_no;			///<メッセージを出す技ナンバー
}ATTACK_MESSAGE_PARAM;

//MESSAGE用
typedef struct{
	u8	command_code;		//命令コードインデックス
	u8	msg_tag;
	u16	msg_id;				///<メッセージID
	int	msg_para[6];
	int	msg_keta;
	int	msg_client;
}MESSAGE_PARAM;

//WAZA_EFFECT用
typedef struct{
	u8	command_code;		//命令コードインデックス
	u8	mode;				///< 戦闘・コンテスト・コンクール？
	u16	waza_no;			///<エフェクトを出す技ナンバー

	s32 waza_eff_damage;	///< 技で受けるダメージ(回復の時は[ - ])

	u16	waza_eff_power;		///< 出ている技の威力
	u16 waza_eff_cnt;		///< 技エフェクトのカウンタ(空を飛ぶとか)

	u16	waza_eff_natuki;	///< なつき度
	u16	migawari_flag	:1;	///< みがわりフラグ			
	u16	henshin_flag	:1;				
	u16					:14;				

	u32	waza_eff_weather;	///< 天候
	
	u16	at_client_no;		///< 攻撃側のクライアント番号
	u16	df_client_no;		///< 防御側のクライアント番号

	u16	mons_no[CLIENT_MAX];
	u8	sex[CLIENT_MAX];
	u8	rare[CLIENT_MAX];
	u8	form_no[CLIENT_MAX];
	u32	personal_rnd[CLIENT_MAX];
	u32	waza_kouka[CLIENT_MAX];
	int	flag;
	int	data;
	int	ground_id;
}WAZA_EFFECT_PARAM;

//HP_GAUGE_CALC用
typedef struct{
	u8	command_code;		//命令コードインデックス
	u8	level;
	s16	hp;					//現在のHP

	u16	hpmax;				//現在のHPMAX
	u8	dummy;				
	u8	sex;				//性別

	int	damage;				//ダメージ量

	u32	now_exp;			//現在のEXP
	u32	max_exp;			//最大EXP

}HP_GAUGE_CALC_PARAM;

//EXP_GAUGE_CALC用
typedef struct{
	u8	command_code;		//命令コードインデックス
	u8	dummy[3];
	u32	now_exp;			//現在のEXP
	u32	next_exp;			//次のEXP
	u32	max_exp;			//最大EXP
}EXP_GAUGE_CALC_PARAM;

//KIZETSU_EFFECT用
typedef struct{
	u8	command_code;		//命令コードインデックス
	u8	sex;
	u16	monsno;				//気絶ポケモンナンバー

	u32	personal_rnd;

	u8	form_no;
	u8	migawari_flag;
	u8	henshin_flag;
	u8	dummy;
	//ここから下は、みがわりのために必要
	u16	wep_mons_no[CLIENT_MAX];
	u8	wep_sex[CLIENT_MAX];
	u8	wep_rare[CLIENT_MAX];
	u8	wep_form_no[CLIENT_MAX];
	u32	wep_personal_rnd[CLIENT_MAX];
}KIZETSU_EFFECT_PARAM;

//SE_PLAY用
typedef struct{
	u8	command_code;		//命令コードインデックス
	u8	dummy;
	u16	se_no;				///<鳴らすSENo
}SE_PLAY_PARAM;

//POKEMON_VANISH_ON_OFF用
typedef struct{
	u8	command_code;		//命令コードインデックス
	u8	sw;					//ON/OFFフラグ
	u8	migawari_flag;
	u8	dummy;
	//ここから下は、みがわりのために必要
	u16	wep_mons_no[CLIENT_MAX];
	u8	wep_sex[CLIENT_MAX];
	u8	wep_rare[CLIENT_MAX];
	u8	wep_form_no[CLIENT_MAX];
	u32	wep_personal_rnd[CLIENT_MAX];
}POKEMON_VANISH_ON_OFF;

//HP_GAUGE_STATUS_SET用
typedef struct{
	u8	command_code;		//命令コードインデックス
	u8	status;				//状態異常ナンバー
	u16	dummy;				
}HP_GAUGE_STATUS_SET_PARAM;

//TRAINER_MESSAGE_SET用
typedef struct{
	u8	command_code;		//命令コードインデックス
	u8	type;				//メッセージタイプ
	u16	dummy;				
}TRAINER_MESSAGE_PARAM;

//STATUS_EFFECT用
typedef struct{
	u8	command_code;		//命令コードインデックス
	u8	status;				//状態異常ナンバー
	u16	dummy;				
}STATUS_EFFECT_PARAM;

//MODOSU_MESSAGE用
typedef struct{
	u8	command_code;		//命令コードインデックス
	u8	sel_mons_no;
	u16	rate;				//メッセージ変換に必要なパラメータ
}MODOSU_MESSAGE_PARAM;

//KURIDASU_MESSAGE用
typedef struct{
	u8	command_code;		//命令コードインデックス
	u8	sel_mons_no;
	u16	rate;				//メッセージ変換に必要なパラメータ
}KURIDASU_MESSAGE_PARAM;

//ENCOUNT_KURIDASU_MESSAGE用
typedef struct{
	u8	command_code;		//命令コードインデックス
	u8	dummy[3];
	u8	sel_mons_no[CLIENT_MAX];
}ENCOUNT_KURIDASU_MESSAGE_PARAM;

//ALERT_MESSAGE用
typedef struct{
	u8	command_code;		//命令コードインデックス
	u8	dummy[3];
	MESSAGE_PARAM	mp;				
}ALERT_MESSAGE_PARAM;

//HP_GAUGE_REFRESH用
typedef struct{
	u8	command_code;		//命令コードインデックス
	u8	level;
	s16	hp;					//現在のHP

	u16	hpmax;				//現在のHPMAX
	u8	sel_mons_no;		//選択ナンバー
	u8	status	:5;			//状態異常
	u8	sex		:2;			//性別
	u8	get_mark:1;			//捕獲フラグ

	u32	now_exp;			//現在のEXP
	u32	max_exp;			//最大EXP
	int	safari_ball;		//サファリボールの数（サファリゾーン専用）
}HP_GAUGE_REFRESH_PARAM;

//PSP_TO_PP_COPY用
typedef struct{
	u8	command_code;		//命令コードインデックス
	u8	sel_mons_no	:4;
	u8	monomane_bit:4;
	s16	hp;
	u32	condition;
	u32	hatakiotosu;
	u16	item;
	u16	waza[WAZA_TEMOTI_MAX];		//waza
	u8	pp[WAZA_TEMOTI_MAX];		//pp
	u32	condition2;	
}PSP_TO_PP_COPY_PARAM;

//POKEMON_REFRESH_SET用
typedef struct{
	u8	command_code;		//命令コードインデックス
	u8	speabi;
	u16	waza_no;			//waza
}POKEMON_REFRESH_PARAM;

//SERVER_QUE_CLEAR用
typedef struct{
	u8	index;
	u8	id;
	u16	dummy;
}SERVER_QUE_CLEAR_PARAM;

//WAZA_WASURE用
typedef struct{
	u8	command_code;		//命令コードインデックス
	u8	sel_mons_no;
	u16	waza_no;			//waza
}WAZA_WASURE_PARAM;

//ITEM_SELECT_RETURN_SET用
typedef struct{
	u16	item_no;
	u8	page;
	u8	sel_mons_no;
}ITEM_SELECT_RETURN_PARAM;

//MOSAIC_SET_PARAM用
typedef struct{
	u8	command_code;		//命令コードインデックス
	u8	mosaic;
	u8	wait;				//waza
	u8	dummy;
}MOSAIC_SET_PARAM;

//FORM_CHG_PARAM用
typedef struct{
	u8	command_code;		//命令コードインデックス
	u8	form_no;
	u16	mons_no;

	u8	sex;
	u8	rare;
	u16 dummy;

	u32 personal_rnd;
}FORM_CHG_PARAM;

//WIN_LOSE_SET用
typedef struct{
	u8	command_code;
	u8	dummy[3];

	u32	win_lose_flag;
}WIN_LOSE_SET_PARAM;

//BALL_GAUGE_SET用
typedef struct{
	u8		command_code;		//命令コードインデックス
	u8		dummy;
	u8		status[POKEMON_TEMOTI_MAX];
}BALL_GAUGE_PARAM;

//INC_RECORD_PARAM用
typedef struct{
	u8		command_code;		//命令コードインデックス
	u8		flag;
	u16		id;
}INC_RECORD_PARAM;

//ESCAPE_MESSAGE用
typedef struct{
	u8		command_code;		//命令コードインデックス
	u8		escape_flag;
	u16		dummy;
}ESCAPE_MESSAGE_PARAM;

//WAZAKOUKA_SE用
typedef struct{
	u8		command_code;		//命令コードインデックス
	u8		kouka;
	u16		dummy;
}WAZAKOUKA_SE_PARAM;

//BGM_PLAY用
typedef struct{
	u8		command_code;		//命令コードインデックス
	u8		dummy;
	u16		bgm_no;
}BGM_PLAY_PARAM;

//関数extern宣言
extern	void	SCIO_EncountEffectSet(BATTLE_WORK *bw,int send_client);
extern	void	SCIO_PokemonEncountSet(BATTLE_WORK *bw,int send_client);
extern	void	SCIO_PokemonEncountAppearSet(BATTLE_WORK *bw,int send_client);
extern	void	SCIO_PokemonAppearSet(BATTLE_WORK *bw,int send_client,int ballID,int flag);
extern	void	SCIO_PokemonReturnSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client);
extern	void	SCIO_PokemonInhaleSet(BATTLE_WORK *bw,int send_client,int ballID);
extern	void	SCIO_PokemonDeleteSet(BATTLE_WORK *bw,int send_client);
extern	void	SCIO_TrainerEncountSet(BATTLE_WORK *bw,int send_client);
extern	void	SCIO_TrainerThrowSet(BATTLE_WORK *bw,int send_client,int type);
extern	void	SCIO_TrainerOutSet(BATTLE_WORK *bw,int send_client);
extern	void	SCIO_TrainerInSet(BATTLE_WORK *bw,int send_client,int pos);
extern	void	SCIO_HPGaugeInSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client,int wait);
extern	void	SCIO_HPGaugeOutSet(BATTLE_WORK *bw,int send_client);
extern	void	SCIO_CommandSelectSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client,int sel_mons_no);
extern	void	SCIO_CommandSelectReturnSet(BATTLE_WORK *bw,int send_client,int data);
extern	void	SCIO_WazaSelectSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client);
extern	void	SCIO_WazaSelectReturnSet(BATTLE_WORK *bw,int send_client,int data);
extern	void	SCIO_DirSelectSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int range,int send_client);
extern	void	SCIO_DirSelectReturnSet(BATTLE_WORK *bw,int send_client,int data);
extern	void	SCIO_ItemSelectSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client);
extern	void	SCIO_ItemSelectReturnSet(BATTLE_WORK *bw,int send_client,ITEM_SELECT_RETURN_PARAM isrp);
extern	void	SCIO_PokemonSelectSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client,int list_mode,int chg_waza,int double_sel);
extern	void	SCIO_PokemonSelectReturnSet(BATTLE_WORK *bw,int send_client,int data);
extern	void	SCIO_YesNoSelectSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client,int msg_id,int flag,int waza_no,int nickname);
extern	void	SCIO_YesNoSelectReturnSet(BATTLE_WORK *bw,int send_client,int data);
extern	void	SCIO_AttackMessageSet(BATTLE_WORK *bw,SERVER_PARAM *sp);
extern	void	SCIO_MessageSet(BATTLE_WORK *bw,SERVER_PARAM *sp,MESSAGE_PARAM *mp);
extern	void	SCIO_WazaEffectSet(BATTLE_WORK *bw,SERVER_PARAM *sp,u16 waza_no);
extern	void	SCIO_WazaEffect2Set(BATTLE_WORK *bw,SERVER_PARAM *sp,u16 waza_no,int attack,int defence);
extern	void	SCIO_PokemonBlinkSet(BATTLE_WORK *bw,int send_client,u32 waza_status_flag);
extern	void	SCIO_HPGaugeCalcSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client);
extern	void	SCIO_EXPGaugeCalcSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client,int now_exp);
extern	void	SCIO_KizetsuEffectSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client);
extern	void	SCIO_SePlaySet(BATTLE_WORK *bw,SERVER_PARAM *sp,int se_no,int send_client);
extern	void	SCIO_FadeOutSet(BATTLE_WORK *bw,SERVER_PARAM *sp);
extern	void	SCIO_PokemonVanishOnOff(BATTLE_WORK *bw,int send_client,int sw);
extern	void	SCIO_HPGaugeStatusSet(BATTLE_WORK *bw,int send_client,int status);
extern	void	SCIO_TrainerMessageSet(BATTLE_WORK *bw,int send_client,int type);
extern	void	SCIO_StatusEffectSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client,int status);
extern	void	SCIO_StatusEffect2Set(BATTLE_WORK *bw,SERVER_PARAM *sp,int cl1,int cl2,int status);
extern	void	SCIO_ModosuMessageSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client,int sel_mons_no);
extern	void	SCIO_KuridasuMessageSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client,int sel_mons_no);
extern	void	SCIO_EncountMessageSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client);
extern	void	SCIO_EncountKuridasuMessageSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client);
extern	void	SCIO_LevelUpEffectSet(BATTLE_WORK *bw,int send_client);
extern	void	SCIO_AlertMessageSet(BATTLE_WORK *bw,int send_client,MESSAGE_PARAM mp);
extern	void	SCIO_AlertMessageEndSet(BATTLE_WORK *bw,int send_client);
extern	void	SCIO_HPGaugeRefreshSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client);
extern	void	SCIO_PSPtoPPCopy(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client);
extern	void	SCIO_TrainerBGSlideInSet(BATTLE_WORK *bw,int send_client);
extern	void	SCIO_GaugeAnimeStop(BATTLE_WORK *bw,int send_client);
extern	void	SCIO_PokemonRefreshSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client,int waza_no);
extern	void	SCIO_WazaWasureSet(BATTLE_WORK *bw,int send_client,int waza_no,int sel_mons_no);
extern	void	SCIO_MosaicSet(BATTLE_WORK *bw,int send_client,int mosaic,int wait);
extern	void	SCIO_FormChgSet(BATTLE_WORK *bw,int send_client);
extern	void	SCIO_BGChgSet(BATTLE_WORK *bw,int send_client);
extern	void	SCIO_SubBGWallPut(BATTLE_WORK *bw,int send_client);
extern	void	SCIO_BallGaugeEncountSet(BATTLE_WORK *bw,int send_client);
extern	void	SCIO_BallGaugeEncountOut(BATTLE_WORK *bw,int send_client);
extern	void	SCIO_BallGaugeSet(BATTLE_WORK *bw,int send_client);
extern	void	SCIO_BallGaugeOut(BATTLE_WORK *bw,int send_client);
extern	void	SCIO_BallGaugeResourceLoad(BATTLE_WORK *bw);
extern	void	SCIO_BallGaugeResourceDelete(BATTLE_WORK *bw);
extern	void	SCIO_IncRecord(BATTLE_WORK *bw,int send_client,int flag,int id);
extern	void	SCIO_SioWaitMessage(BATTLE_WORK *bw,int send_client);
extern	void	SCIO_ChrPop(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client);
extern	void	SCIO_SStoOAMCall(BATTLE_WORK *bw,int send_client);
extern	void	SCIO_OAMtoSSCall(BATTLE_WORK *bw,int send_client);
extern	void	SCIO_WinLoseMessage(BATTLE_WORK *bw);
extern	void	SCIO_EscapeMessage(BATTLE_WORK *bw,SERVER_PARAM *sp);
extern	void	SCIO_GiveUpMessage(BATTLE_WORK *bw);
extern	void	SCIO_MigawariChrSet(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client);
extern	void	SCIO_WazaKoukaSESet(BATTLE_WORK *bw,SERVER_PARAM *sp,int send_client);
extern	void	SCIO_BGMPlay(BATTLE_WORK *bw,int send_client,int bgm_no);

extern	void	SCIO_WinLoseFlagSet(BATTLE_WORK *bw);
extern	void	SCIO_BlankMessage(BATTLE_WORK *bw);

extern	void	SCIO_ServerQueClear(BATTLE_WORK *bw,int send_client,int index);
extern	void	SCIO_CommRecvData(BATTLE_WORK *bw,void *data);
extern	void	SCIO_EffectDataSet(BATTLE_WORK *bw,SERVER_PARAM *sp,WAZA_EFFECT_PARAM *wep,int flag,int data,int attack,int defence,u16 waza_no);

extern	void	ScioBattleRecvData(BATTLE_WORK *bw);

#endif __SCIO_H_
