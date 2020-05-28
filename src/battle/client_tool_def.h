
//============================================================================================
/**
 * @file	client_tool_def.h
 * @bfief	戦闘クライアントツールプログラム
 * @author	HisashiSogabe
 * @date	05.07.25
 */
//============================================================================================

#ifndef __CLIENT_TOOL_DEF_H_
#define __CLIENT_TOOL_DEF_H_

#include	"battle/scio.h"
#include	"system/softsprite.h"
#include	"wazaeffect/we_mana.h"
#include	"wazaeffect/ball_effect.h"
#include	"wazaeffect/ec_eff.h"
#include	"poketool/pokeparty.h"
#include	"b_plist.h"
#include	"b_bag.h"
#include	"battle_input_type.h"

///<POKEMON_ENCOUNT用TCBパラメータ構造体宣言
typedef struct
{
	BATTLE_WORK		*bw;
	CLIENT_PARAM	*cp;
	SOFT_SPRITE		*ss;
	GROUND_WORK		*gw;
	u8				command_code;
	u8				client_no;
	u8				seq_no;
	u8				dir;

	s16				appear_pos;
	u16				mons_no;

	int				voice;
	int				client_type;
	int				wait;
	int				chr;
	int				rare;
}TCB_POKEMON_ENCOUNT;

///<POKEMON_APPEAR用TCBパラメータ構造体宣言
typedef struct
{
	BATTLE_WORK			*bw;
	CLIENT_PARAM		*cp;
	BES_PTR				bes;			///< ボールエフェクト
	BMS_PTR				bms;
	OAM_DROP_SYS*		ods;			///< OAM 変換

	SOFT_SPRITE_ARC		ssa;
	WE_SYS_PTR			wsp;
	WAZA_EFFECT_PARAM 	wep;

	u8					command_code;
	u8					client_no;
	u8					client_type;
	u8					seq_no;

	u8					dir;
	u8					ofs_y;
	u16					mons_no;

	int					voice;
	u8					sel_mons_no;
	u8					chr;
	u16					ballID;

	s8					height;
	s8					ofs_x;
	u8					rare;
	u8					shadow;
	u16					flag;			///<繰り出しor捕獲失敗フラグ
	u8					wait;
	int					migawari_flag;
}TCB_POKEMON_APPEAR;

///<POKEMON_RETURN用TCBパラメータ構造体宣言
typedef struct
{
	BATTLE_WORK			*bw;
	CLIENT_PARAM		*cp;
	SOFT_SPRITE			*ss;
	BMS_PTR				bms;
	WAZA_EFFECT_PARAM 	wep;

	u8					command_code;
	u8					client_no;
	u8					client_type;
	u8					seq_no;

	u8					height;
	u8					wait;
	u16					ballID;

	int					migawari_flag;
}TCB_POKEMON_RETURN;

///<POKEMON_INHALE用TCBパラメータ構造体宣言
typedef struct
{
	BATTLE_WORK	*bw;
	SOFT_SPRITE	*ss;

	u8			command_code;
	u8			client_no;
	u8			client_type;
	u8			seq_no;

	u8			height;
	u8			wait;
	u16			dummy;
}TCB_POKEMON_INHALE;

///<TRAINER_ENCOUNT用TCBパラメータ構造体宣言
typedef struct
{
	BATTLE_WORK		*bw;
	SOFT_SPRITE		*ss;
	GROUND_WORK		*gw;
	CATS_ACT_PTR	cap;

	u8				command_code;
	u8				client_no;
	u8				seq_no;
	u8				dir;

	s16				appear_pos;
	u16				dummy;

	int				client_type;
	int				wait;
	int				scroll_time;
}TCB_TRAINER_ENCOUNT;

///<TRAINER_THROW用TCBパラメータ構造体宣言
typedef struct
{
	BATTLE_WORK		*bw;
	CLIENT_PARAM	*cp;

	u8				command_code;
	u8				client_no;
	u8				seq_no;
	u8				dir;
	int				trtype;
	int				type;
	int				wait;
	int				throw_type;
}TCB_TRAINER_THROW;

///<TRAINER_OUT用TCBパラメータ構造体宣言
typedef struct
{
	BATTLE_WORK		*bw;
	CLIENT_PARAM	*cp;

	u8				command_code;
	u8				client_no;
	u8				seq_no;
	u8				dir;
	int				trtype;
}TCB_TRAINER_OUT;

///<TRAINER_IN用TCBパラメータ構造体宣言
typedef struct
{
	BATTLE_WORK	*bw;
	SOFT_SPRITE	*ss;

	u8			command_code;
	u8			client_no;
	u8			seq_no;
	u8			dir;

	s16			appear_pos;
	u16			dummy;
}TCB_TRAINER_IN;

///<HP_GAUGE_IN用TCBパラメータ構造体宣言
typedef struct
{
	BATTLE_WORK	*bw;
	CATS_ACT_PTR cap;

	u8			command_code;
	u8			client_no;
	u8			seq_no;
	u8			client_type;

	s16			hp;
	u16			hpmax;
	
	s16			be_hp;		///<受けたダメージ(回復する場合はマイナスで入れる) 変動させる値
	s16			hp_work;	///<ゲージ増減作業用ワーク
	
	u8			level;
	u8			dummy[3];
}TCB_HP_GAUGE_IN;

///<COMMAND_SELECT用TCBパラメータ構造体宣言
typedef struct
{
	BATTLE_WORK	*bw;
	void		*gauge;

	u8			command_code;
	u8			client_no;
	u8			seq_no;
	s8			wait;

	int			tp_ret;

	u8			status[2][POKEMON_TEMOTI_MAX];

	u8			motivation[POKEMON_TEMOTI_MAX];
	u8			msg_index;
	u8			sel_mons_no;

	u16			wazano[WAZA_TEMOTI_MAX];		//wazano
	u8			pp[WAZA_TEMOTI_MAX];			//pp
	u8			ppmax[WAZA_TEMOTI_MAX];			//ppmax

	u8			client_type;
	u8			index;
	s16			icon_hp;				//現在のHP

	u16			icon_hpmax;				//現在のHPMAX
	u8			icon_status;
	u8			dummy;
}TCB_COMMAND_SELECT;

///<WAZA_SELECT用TCBパラメータ構造体宣言
typedef struct
{
	BATTLE_WORK	*bw;
	void		*gauge;
	int			tp_ret;

	u16			wazano[WAZA_TEMOTI_MAX];		//wazano
	u8			pp[WAZA_TEMOTI_MAX];			//pp
	u8			ppmax[WAZA_TEMOTI_MAX];			//ppmax

	u8			command_code;
	u8			client_no;
	u8			client_type;
	u8			sel_mons_no;

	u8			seq_no;
	u8			dummy;
	u16			wazabit;
}TCB_WAZA_SELECT;

///<DIR_SELECT用TCBパラメータ構造体宣言
typedef struct
{
	BATTLE_WORK	*bw;
	void		*gauge;
	int			tp_ret;

	u8			command_code;
	u8			client_no;
	u8			client_type;
	u8			seq_no;

	DIR_SELECT_POKE_PARAM	dspp[CLIENT_MAX];	

	u16			range;			//効果範囲
	u8			light_flag;		///1：入力画面背景を明るくしてください
	u8			dummy;
}TCB_DIR_SELECT;

///<POKEMON_SELECT用TCBパラメータ構造体宣言
typedef struct
{
	BATTLE_WORK	*bw;
	BPLIST_DATA	*plist;

	u8			command_code;
	u8			client_no;
	u8			seq_no;
	u8			list_mode;

	u8			sel_mons_no[CLIENT_MAX];

	int			chg_waza;

	u16			item;
	u8			double_sel;
	u8			decend_key;
	
	u8			no_reshuffle_client;
	u8			dummy[3];

	u8			list_row[CLIENT_MAX][POKEMON_TEMOTI_MAX];
}TCB_POKEMON_SELECT;

///<ITEM_SELECT用TCBパラメータ構造体宣言
typedef struct
{
	BATTLE_WORK			*bw;
	BBAG_DATA			*bag_buf;
	TCB_POKEMON_SELECT	*tps;

	u8					command_code;
	u8					client_no;
	u8					seq_no;
	u8					client_type;

	u8					decend_key;
	u8					msg_index;
	u16					next_seq_no;

	u8					enc_double;
	u8					waza_vanish;
	u8					waza_migawari;
	u8					wait;

	u8					list_row[CLIENT_MAX][POKEMON_TEMOTI_MAX];
	u8					shutout_flag[CLIENT_MAX];
}TCB_ITEM_SELECT;

///<YES_NO_SELECT用TCBパラメータ構造体宣言
typedef struct
{
	BATTLE_WORK	*bw;
	void		*gauge;
	int			tp_ret;

	u8			command_code;
	u8			client_no;
	u8			seq_no;
	u8			flag;

	int			msg_id;
	int			nickname;

	u16			waza_no;
	u16			msg_index;
}TCB_YES_NO_SELECT;

///<POKEMON_BLINK用TCBパラメータ構造体宣言
typedef struct
{
	BATTLE_WORK	*bw;
	SOFT_SPRITE	*ss;

	u8			client_no;
	u8			seq_no;
	u8			wait;			///<BLINK_WAIT
	u8			dummy;
}TCB_POKEMON_BLINK;

///<HP_GAUGE_CALC用TCBパラメータ構造体宣言
typedef struct
{
	BATTLE_WORK	*bw;

	u8			command_code;
	u8			client_no;
	u8			seq_no;
	u8			dir;

	s16			hp;
	u16			hpmax;

	int			damage;

	u8			level;
	u8			dummy[3];
}TCB_HP_GAUGE_CALC;

///<KIZETSU_EFFECT用TCBパラメータ構造体宣言
typedef struct
{
	BATTLE_WORK			*bw;
	CLIENT_PARAM		*cp;
	SOFT_SPRITE			*ss;
	WAZA_EFFECT_PARAM 	wep;

	u8					command_code;
	u8					client_no;
	u8					seq_no;
	u8					dir;

	u16					monsno;
	u8					sex;
	u8					form_no;

	u32					personal_rnd;

	u16					migawari_flag;
	u16					henshin_flag;
}TCB_KIZETSU_EFFECT;

///<FADE_OUT用TCBパラメータ構造体宣言
typedef struct
{
	BATTLE_WORK	*bw;

	u8			command_code;
	u8			client_no;
	u8			seq_no;
	u8			dummy;
}TCB_FADE_OUT;

///<POKEMON_VANISH_ON_OFF用TCBパラメータ構造体宣言
typedef struct
{
	BATTLE_WORK			*bw;
	CLIENT_PARAM		*cp;
	WAZA_EFFECT_PARAM 	wep;

	u8					command_code;
	u8					client_no;
	u8					seq_no;
	u8					sw;
	int					migawari_flag;
}TCB_POKEMON_VANISH_ON_OFF;

///<WAZA_EFFECT用TCBパラメータ構造体宣言
typedef struct
{
	BATTLE_WORK			*bw;
	CLIENT_PARAM		*cp;
	SOFT_SPRITE			*ss;
	WE_SYS_PTR			wsp;
	WAZA_EFFECT_PARAM 	wep;

	u8					command_code;
	u8					client_no;
	u8					seq_no;
	u8					we_on_off_flag;
	u8					we_shadow_flag;
	u8					dummy[3];
}TCB_WAZA_EFFECT;

typedef struct
{
	BATTLE_WORK	*bw;

	u8			command_code;
	u8			client_no;
	u8			msg_index;
	u8			dummy;
}TCB_MESSAGE_WAIT;

///<STATUS_EFFECT用TCBパラメータ構造体宣言
typedef struct
{
	BATTLE_WORK	*bw;
	int			flag;

	u8			command_code;
	u8			client_no;
	u8			seq_no;
	u8			dummy;
}TCB_STATUS_EFFECT;

typedef struct
{
	BATTLE_WORK	*bw;

	u8			command_code;
	u8			client_no;
	u8			msg_index;
	u8			seq_no;

	u8			wait;
	u8			dummy[3];
}TCB_ALERT_MESSAGE_WAIT;

///<ENCOUNT_EFFECT用TCBパラメータ構造体宣言
typedef struct
{
	BATTLE_WORK	*bw;
	ECEM_PTR	ecem;
	ECE_PTR		ece[3];

	u8			seq_no;
	u8			wait;
	u16			dummy;
}TCB_ENCOUNT_EFFECT;

///<LEVEL_UP_EFFECT用TCBパラメータ構造体宣言
typedef struct
{
	BATTLE_WORK	*bw;
	void		*gauge;

	u8			command_code;
	u8			client_no;
	u8			seq_no;
	u8			flag;
}TCB_LEVEL_UP_EFFECT;

///<WAZA_WASURE用TCBパラメータ構造体宣言
typedef struct
{
	BATTLE_WORK	*bw;
	BPLIST_DATA	*plist;

	u8			command_code;
	u8			client_no;
	u8			seq_no;
	u8			list_mode;

	u16			waza_no;
	u8			sel_mons_no;
	u8			dummy;
}TCB_WAZA_WASURE;

///<MOSAIC_SET用TCBパラメータ構造体宣言
typedef struct
{
	BATTLE_WORK	*bw;
	SOFT_SPRITE	*ss;

	u8			command_code;
	u8			client_no;
	u8			seq_no;
	u8			mosaic;

	u8			wait;
	u8			wait_temp;
	u16			dummy;
}TCB_MOSAIC_SET;

///<BALL_GAUGE用TCBパラメータ構造体宣言
typedef struct
{
	BATTLE_WORK	*bw;

	u8			command_code;
	u8			client_no;
	u8			client_type;
	u8			seq_no;

	u8			status[POKEMON_TEMOTI_MAX];
	u8			encount_change;		///<0:エンカウント、1:入れ替え
	u8			dummy[1];
}TCB_BALL_GAUGE;

///<ソフトスプライト＞OAM変換用TCBパラメータ構造体宣言
typedef struct
{
	BATTLE_WORK			*bw;
	CLIENT_PARAM		*cp;
	SOFT_SPRITE			*ss;

	u8					command_code;
	u8					client_no;
	u8					seq_no;
	
	u8 dummy[1];	///<4バイト境界オフセット
}TCB_SS_TO_OAM;

///<OAM＞ソフトスプライトに戻すTCBパラメータ構造体宣言
typedef struct
{
	BATTLE_WORK			*bw;
	CLIENT_PARAM		*cp;
	SOFT_SPRITE			*ss;

	u8					command_code;
	u8					client_no;
	u8					seq_no;
	
	u8 dummy[1];	///<4バイト境界オフセット
}TCB_OAM_TO_SS;


#endif __CLIENT_TOOL_DEF_H_
