//==============================================================================================
/**
 * @file	d_fight_tool.c
 * @brief	デバッグファイト
 * @author	sogabe
 * @date	2006.01.06
 */
//==============================================================================================

#ifdef PM_DEBUG

#include "common.h"
#include "system/fontproc.h"
#include "system/pm_str.h"
#include "system/msgdata.h"						//MSGDATA_MANAGER
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/softsprite.h"
#include "system/timezone.h"
#include "poke_test.h"

#include "msgdata/msg.naix"						//NARC_msg_??_dat
#include "msgdata/msg_debug_fight.h"
#include "battle/battle_common.h"
#include "battle/battle_server.h"
#include "battle/trtype_def.h"
#include "poketool/monsno.h"
#include "battle/attr_def.h"
#include "battle/wazano_def.h"
#include "battle/chr_def.h"
#include "battle/tokusyu_def.h"
#include "battle/fight.h"
#include "battle/b_tower_data.h"
#include "poketool/poke_tool.h"
#include "poketool/pokeparty.h"
#include "poketool/tr_tool.h"
#include "poketool/waza_tool.h"
#include "system/snd_tool.h"
#include "system/wordset.h"
#include "system/brightness.h"
#include "system/wipe.h"
#include "itemtool/item.h"
#include "itemtool/itemsym.h"
#include "itemtool/myitem.h"
#include "field/weather_no.h"
#include "gflib/strbuf_family.h"

#include "communication/communication.h"
#include "communication/comm_state.h"

#include "system/main.h"
#include "demo/title.h"
#include "savedata/savedata.h"
#include "savedata/config.h"
#include "savedata/friendlist.h"
#include "savedata/wifihistory.h"

#include "d_fight.h"

extern	BOOL	PMSVLD_Load(u32 src, void * dst, u32 len);
extern	BOOL	PMSVLD_Save(u32 src, void * dst, u32 len);

//==============================================================================================
//
//	プロトタイプ宣言
//
//==============================================================================================

BOOL	DebugFightStart(DEBUG_FIGHT_PARAM *dfp);

void	DebugFightBGCreate(DEBUG_FIGHT_PARAM *dfp,GF_BGL_INI *bgl);
void	DebugFightPokemonParamInit(DEBUG_POKEMON_PARAM *dpp);
void	DebugFightAIScreenCreate(DEBUG_FIGHT_PARAM *dfp);
void	DebugFightAutoScreenCreate(DEBUG_FIGHT_PARAM *dfp);
void	DebugFightMainScreenCreate(DEBUG_FIGHT_PARAM *dfp);
void	DebugFightSubScreenCreate(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp,int page);
static	void	DebugFightMonsNamePut(DEBUG_FIGHT_PARAM *dfp,int pos,GF_PRINTCOLOR col);
static	void	DebugFightRuleDataPut(DEBUG_FIGHT_PARAM *dfp,GF_PRINTCOLOR col);
static	void	DebugFightEffectFlagDataPut(DEBUG_FIGHT_PARAM *dfp,GF_PRINTCOLOR col);
static	void	DebugFightMsgSpeedDataPut(DEBUG_FIGHT_PARAM *dfp,GF_PRINTCOLOR col);
static	void	DebugFightFightTypePut(DEBUG_FIGHT_PARAM *dfp);
static	void	DebugFightFightTypeDataPut(DEBUG_FIGHT_PARAM *dfp,GF_PRINTCOLOR col);
static	void	DebugFightVersionDataPut(DEBUG_FIGHT_PARAM *dfp,GF_PRINTCOLOR col);
static	void	DebugFightGroundDataPut(DEBUG_FIGHT_PARAM *dfp,GF_PRINTCOLOR col);
static	void	DebugFightBGDataPut(DEBUG_FIGHT_PARAM *dfp,GF_PRINTCOLOR col);
static	void	DebugFightWeatherDataPut(DEBUG_FIGHT_PARAM *dfp,GF_PRINTCOLOR col);
static	void	DebugFightTimeZoneDataPut(DEBUG_FIGHT_PARAM *dfp,GF_PRINTCOLOR col);
static	void	DebugFightMySexPut(DEBUG_FIGHT_PARAM *dfp);
static	void	DebugFightMySexDataPut(DEBUG_FIGHT_PARAM *dfp,GF_PRINTCOLOR col);
static	void	DebugFightKindPut(DEBUG_FIGHT_PARAM *dfp);
static	void	DebugFightKindDataPut(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp,int mode);
static	void	DebugFightRareDataPut(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp,GF_PRINTCOLOR col);
static	void	DebugFightLevelPut(DEBUG_FIGHT_PARAM *dfp);
static	void	DebugFightLevelDataPut(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp,int mode);
static	void	DebugFightExpPut(DEBUG_FIGHT_PARAM *dfp);
static	void	DebugFightExpDataPut(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp,int mode);
static	void	DebugFightSexPut(DEBUG_FIGHT_PARAM *dfp);
static	void	DebugFightSexDataPut(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp,GF_PRINTCOLOR col);
static	void	DebugFightChrPut(DEBUG_FIGHT_PARAM *dfp);
static	void	DebugFightChrDataPut(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp,GF_PRINTCOLOR col);

static	void	DebugFightHPRndPut(DEBUG_FIGHT_PARAM *dfp);
static	void	DebugFightPowRndPut(DEBUG_FIGHT_PARAM *dfp);
static	void	DebugFightDefRndPut(DEBUG_FIGHT_PARAM *dfp);
static	void	DebugFightAgiRndPut(DEBUG_FIGHT_PARAM *dfp);
static	void	DebugFightSpePowRndPut(DEBUG_FIGHT_PARAM *dfp);
static	void	DebugFightSpeDefRndPut(DEBUG_FIGHT_PARAM *dfp);

static	void	DebugFightHPExpPut(DEBUG_FIGHT_PARAM *dfp);
static	void	DebugFightPowExpPut(DEBUG_FIGHT_PARAM *dfp);
static	void	DebugFightDefExpPut(DEBUG_FIGHT_PARAM *dfp);
static	void	DebugFightAgiExpPut(DEBUG_FIGHT_PARAM *dfp);
static	void	DebugFightSpePowExpPut(DEBUG_FIGHT_PARAM *dfp);
static	void	DebugFightSpeDefExpPut(DEBUG_FIGHT_PARAM *dfp);

static	void	DebugFightStatusRndDataPut(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp,int status,int mode);
static	void	DebugFightStatusExpDataPut(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp,int status,int mode);

static	void	DebugFightParamPut(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp);
static	void	DebugFightDefaultSet(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp,int mode);

static	void	DebugFightWazaPut(DEBUG_FIGHT_PARAM *dfp,int pos);
static	void	DebugFightWazaDataPut(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp,int pos,int mode);
static	void	DebugFightPPDataPut(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp,int pos,int mode);
static	void	DebugFightPPCountDataPut(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp,int pos,int mode);
static	void	DebugFightSpeAbiPut(DEBUG_FIGHT_PARAM *dfp);
static	void	DebugFightSpeAbiDataPut(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp,GF_PRINTCOLOR col);
static	void	DebugFightSpeAbiSetPut(DEBUG_FIGHT_PARAM *dfp);
static	void	DebugFightSpeAbiSetDataPut(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp,int mode);
static	void	DebugFightItemPut(DEBUG_FIGHT_PARAM *dfp);
static	void	DebugFightItemDataPut(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp,int mode);
static	void	DebugFightFriendPut(DEBUG_FIGHT_PARAM *dfp);
static	void	DebugFightFriendDataPut(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp,int mode);
static	void	DebugFightConditionPut(DEBUG_FIGHT_PARAM *dfp);
static	void	DebugFightConditionDataPut(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp,GF_PRINTCOLOR col);
static	void	DebugFightDefaultHPPut(DEBUG_FIGHT_PARAM *dfp);
static	void	DebugFightDefaultHPDataPut(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp,int mode);
static	void	DebugFightGetBallPut(DEBUG_FIGHT_PARAM *dfp);
static	void	DebugFightGetBallDataPut(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp,GF_PRINTCOLOR col);

static	void	DebugFightFormNoPut(DEBUG_FIGHT_PARAM *dfp);
static	void	DebugFightFormNoDataPut(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp,int max,int mode);
static	void	DebugFightEggFlagDataPut(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp);

static	void	DebugFightTrainerIDPut(DEBUG_FIGHT_PARAM *dfp);
static	void	DebugFightTrainerIDDataPut(DEBUG_FIGHT_PARAM *dfp);
static	void	DebugFightBT_TrainerIDPut(DEBUG_FIGHT_PARAM *dfp);
static	void	DebugFightBT_TrainerIDDataPut(DEBUG_FIGHT_PARAM *dfp);

static	void	DebugFightNumPut(DEBUG_FIGHT_PARAM *dfp,int x,int y,int param,int keta,int pos,int mode);
void	CursorMove(DEBUG_FIGHT_PARAM *dfp,int side,int pos,int mode);

static	BOOL	DebugFightPokeAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp);
static	BOOL	DebugFightGroundAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp);
static	BOOL	DebugFightBGAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp);
static	BOOL	DebugFightWeatherAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp);
static	BOOL	DebugFightTimeZoneAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp);
static	BOOL	DebugFightMySexAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp);
static	BOOL	DebugFightRuleAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp);
static	BOOL	DebugFightEffectFlagAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp);
static	BOOL	DebugFightMsgSpeedAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp);
static	BOOL	DebugFightFightTypeAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp);
static	BOOL	DebugFightLoadAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp);
static	BOOL	DebugFightSaveAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp);
static	BOOL	DebugFightVersionAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp);
//サブ：ページ１
static	BOOL	DebugFightKindAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp);
static	BOOL	DebugFightRareAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp);
static	BOOL	DebugFightLevelAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp);
static	BOOL	DebugFightExpAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp);
static	BOOL	DebugFightSexAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp);
static	BOOL	DebugFightChrAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp);
static	BOOL	DebugFightStatusRndAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp);
static	BOOL	DebugFightStatusExpAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp);
//サブ：ページ２
static	BOOL	DebugFightWazaAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp);
static	BOOL	DebugFightPPAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp);
static	BOOL	DebugFightPPCountAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp);
static	BOOL	DebugFightSpeAbiAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp);
static	BOOL	DebugFightSpeAbiSetAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp);
static	BOOL	DebugFightItemAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp);
static	BOOL	DebugFightFriendAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp);
static	BOOL	DebugFightConditionAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp);
static	BOOL	DebugFightDefaultHPAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp);
static	BOOL	DebugFightGetBallAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp);
//サブ：ページ３
static	BOOL	DebugFightFormNoAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp);
static	BOOL	DebugFightEggFlagAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp);

void	DebugFightDefaultPokeSet(DEBUG_FIGHT_PARAM *dfp,int pos);

static	int		DebugFightNumCalc(DEBUG_FIGHT_PARAM *dfp,u32 *param,int keta,int min,int max,int mode);

static	u32		PokeRndGet(int mons_no,int sex,int chr,int rare);

static	int		DebugFightFormNoMaxGet(DEBUG_POKEMON_PARAM *dpp);

static	void	DebugFightVBlank(void *work);

extern	BATTLE_PARAM *BattleParam_Create(int heapID,u32 fight_type);

const	MENU_LIST_PARAM	mlp_m[]={
	//MS_MINE_POKE_1
	{
		MINE_POKE1_CUR_X,		//カーソルX位置
		MINE_POKE1_CUR_Y,		//カーソルY位置
		MS_LOAD,				//上キーを押したときの移動先
		MS_MINE_POKE_2,			//下キーを押したときの移動先
		NO_MOVE,				//左キーを押したときの移動先
		MS_ENEMY_POKE_1,		//右キーを押したときの移動先
		DebugFightPokeAct,		//Aボタンを押したときのアクション
	},
	//MS_MINE_POKE_2
	{
		MINE_POKE2_CUR_X,		//カーソルX位置
		MINE_POKE2_CUR_Y,		//カーソルY位置
		MS_MINE_POKE_1,			//上キーを押したときの移動先
		MS_MINE_POKE_3,			//下キーを押したときの移動先
		NO_MOVE,				//左キーを押したときの移動先
		MS_ENEMY_POKE_2,		//右キーを押したときの移動先
		DebugFightPokeAct,		//Aボタンを押したときのアクション
	},
	//MS_MINE_POKE_3
	{
		MINE_POKE3_CUR_X,		//カーソルX位置
		MINE_POKE3_CUR_Y,		//カーソルY位置
		MS_MINE_POKE_2,			//上キーを押したときの移動先
		MS_MINE_POKE_4,			//下キーを押したときの移動先
		NO_MOVE,				//左キーを押したときの移動先
		MS_ENEMY_POKE_3,		//右キーを押したときの移動先
		DebugFightPokeAct,		//Aボタンを押したときのアクション
	},
	//MS_MINE_POKE_4
	{
		MINE_POKE4_CUR_X,		//カーソルX位置
		MINE_POKE4_CUR_Y,		//カーソルY位置
		MS_MINE_POKE_3,			//上キーを押したときの移動先
		MS_MINE_POKE_5,			//下キーを押したときの移動先
		NO_MOVE,				//左キーを押したときの移動先
		MS_ENEMY_POKE_4,		//右キーを押したときの移動先
		DebugFightPokeAct,		//Aボタンを押したときのアクション
	},
	//MS_MINE_POKE_5
	{
		MINE_POKE5_CUR_X,		//カーソルX位置
		MINE_POKE5_CUR_Y,		//カーソルY位置
		MS_MINE_POKE_4,			//上キーを押したときの移動先
		MS_MINE_POKE_6,			//下キーを押したときの移動先
		NO_MOVE,				//左キーを押したときの移動先
		MS_ENEMY_POKE_5,		//右キーを押したときの移動先
		DebugFightPokeAct,		//Aボタンを押したときのアクション
	},
	//MS_MINE_POKE_6
	{
		MINE_POKE6_CUR_X,		//カーソルX位置
		MINE_POKE6_CUR_Y,		//カーソルY位置
		MS_MINE_POKE_5,			//上キーを押したときの移動先
		MS_GROUND,				//下キーを押したときの移動先
		NO_MOVE,				//左キーを押したときの移動先
		MS_ENEMY_POKE_6,		//右キーを押したときの移動先
		DebugFightPokeAct,		//Aボタンを押したときのアクション
	},
	//MS_ENEMY_POKE_1
	{
		ENEMY_POKE1_CUR_X,		//カーソルX位置
		ENEMY_POKE1_CUR_Y,		//カーソルY位置
		MS_SAVE,				//上キーを押したときの移動先
		MS_ENEMY_POKE_2,		//下キーを押したときの移動先
		MS_MINE_POKE_1,			//左キーを押したときの移動先
		NO_MOVE,				//右キーを押したときの移動先
		DebugFightPokeAct,		//Aボタンを押したときのアクション
	},
	//MS_ENEMY_POKE_2
	{
		ENEMY_POKE2_CUR_X,		//カーソルX位置
		ENEMY_POKE2_CUR_Y,		//カーソルY位置
		MS_ENEMY_POKE_1,		//上キーを押したときの移動先
		MS_ENEMY_POKE_3,		//下キーを押したときの移動先
		MS_MINE_POKE_2,			//左キーを押したときの移動先
		NO_MOVE,				//右キーを押したときの移動先
		DebugFightPokeAct,		//Aボタンを押したときのアクション
	},
	//MS_ENEMY_POKE_3
	{
		ENEMY_POKE3_CUR_X,		//カーソルX位置
		ENEMY_POKE3_CUR_Y,		//カーソルY位置
		MS_ENEMY_POKE_2,		//上キーを押したときの移動先
		MS_ENEMY_POKE_4,		//下キーを押したときの移動先
		MS_MINE_POKE_3,			//左キーを押したときの移動先
		NO_MOVE,				//右キーを押したときの移動先
		DebugFightPokeAct,		//Aボタンを押したときのアクション
	},
	//MS_ENEMY_POKE_4
	{
		ENEMY_POKE4_CUR_X,		//カーソルX位置
		ENEMY_POKE4_CUR_Y,		//カーソルY位置
		MS_ENEMY_POKE_3,		//上キーを押したときの移動先
		MS_ENEMY_POKE_5,		//下キーを押したときの移動先
		MS_MINE_POKE_4,			//左キーを押したときの移動先
		NO_MOVE,				//右キーを押したときの移動先
		DebugFightPokeAct,		//Aボタンを押したときのアクション
	},
	//MS_ENEMY_POKE_5
	{
		ENEMY_POKE5_CUR_X,		//カーソルX位置
		ENEMY_POKE5_CUR_Y,		//カーソルY位置
		MS_ENEMY_POKE_4,		//上キーを押したときの移動先
		MS_ENEMY_POKE_6,		//下キーを押したときの移動先
		MS_MINE_POKE_5,			//左キーを押したときの移動先
		NO_MOVE,				//右キーを押したときの移動先
		DebugFightPokeAct,		//Aボタンを押したときのアクション
	},
	//MS_ENEMY_POKE_6
	{
		ENEMY_POKE6_CUR_X,		//カーソルX位置
		ENEMY_POKE6_CUR_Y,		//カーソルY位置
		MS_ENEMY_POKE_5,		//上キーを押したときの移動先
		MS_BG,					//下キーを押したときの移動先
		MS_MINE_POKE_6,			//左キーを押したときの移動先
		NO_MOVE,				//右キーを押したときの移動先
		DebugFightPokeAct,		//Aボタンを押したときのアクション
	},
	//MS_GROUND
	{
		GROUND_CUR_X,			//カーソルX位置
		GROUND_CUR_Y,			//カーソルY位置
		MS_MINE_POKE_6,			//上キーを押したときの移動先
		MS_RULE,				//下キーを押したときの移動先
		NO_MOVE,				//左キーを押したときの移動先
		MS_BG,					//右キーを押したときの移動先
		DebugFightGroundAct,	//Aボタンを押したときのアクション
	},
	//MS_BG
	{
		BG_CUR_X,				//カーソルX位置
		BG_CUR_Y,				//カーソルY位置
		MS_ENEMY_POKE_6,		//上キーを押したときの移動先
		MS_EFFECT_FLAG,			//下キーを押したときの移動先
		MS_GROUND,				//左キーを押したときの移動先
		MS_WEATHER,				//右キーを押したときの移動先
		DebugFightBGAct,		//Aボタンを押したときのアクション
	},
	//MS_WEATHER
	{
		WEATHER_CUR_X,			//カーソルX位置
		WEATHER_CUR_Y,			//カーソルY位置
		MS_ENEMY_POKE_6,		//上キーを押したときの移動先
		MS_MYSEX,				//下キーを押したときの移動先
		MS_BG,					//左キーを押したときの移動先
		NO_MOVE,				//右キーを押したときの移動先
		DebugFightWeatherAct,	//Aボタンを押したときのアクション
	},
	//MS_RULE,
	{
		RULE_CUR_X,				//カーソルX位置
		RULE_CUR_Y,				//カーソルY位置
		MS_GROUND,				//上キーを押したときの移動先
		MS_MYSEX,				//下キーを押したときの移動先
		NO_MOVE,				//左キーを押したときの移動先
		MS_EFFECT_FLAG,			//右キーを押したときの移動先
		DebugFightRuleAct,		//Aボタンを押したときのアクション
	},
	//MS_EFFECT_FLAG,
	{
		EFFECT_FLAG_CUR_X,		//カーソルX位置
		EFFECT_FLAG_CUR_Y,		//カーソルY位置
		MS_BG,					//上キーを押したときの移動先
		MS_TIMEZONE,			//下キーを押したときの移動先
		MS_RULE,				//左キーを押したときの移動先
		MS_MSG_SPEED,			//右キーを押したときの移動先
		DebugFightEffectFlagAct,//Aボタンを押したときのアクション
	},
	//MS_MSG_SPEED,
	{
		MSG_SPEED_CUR_X,		//カーソルX位置
		MSG_SPEED_CUR_Y,		//カーソルY位置
		MS_WEATHER,				//上キーを押したときの移動先
		MS_FIGHT_TYPE,			//下キーを押したときの移動先
		MS_EFFECT_FLAG,			//左キーを押したときの移動先
		NO_MOVE,				//右キーを押したときの移動先
		DebugFightMsgSpeedAct,	//Aボタンを押したときのアクション
	},
	//MS_MYSEX,
	{
		MYSEX_CUR_X,			//カーソルX位置
		MYSEX_CUR_Y,			//カーソルY位置
		MS_RULE,				//上キーを押したときの移動先
		MS_LOAD,				//下キーを押したときの移動先
		NO_MOVE,				//左キーを押したときの移動先
		MS_TIMEZONE,			//右キーを押したときの移動先
		DebugFightMySexAct,		//Aボタンを押したときのアクション
	},
	//MS_TIMEZONE,
	{
		TIMEZONE_CUR_X,			//カーソルX位置
		TIMEZONE_CUR_Y,			//カーソルY位置
		MS_EFFECT_FLAG,			//上キーを押したときの移動先
		MS_LOAD,				//下キーを押したときの移動先
		MS_MYSEX,				//左キーを押したときの移動先
		MS_FIGHT_TYPE,			//右キーを押したときの移動先
		DebugFightTimeZoneAct,	//Aボタンを押したときのアクション
	},
	//MS_FIGHT_TYPE
	{
		FIGHT_TYPE_CUR_X,		//カーソルX位置
		FIGHT_TYPE_CUR_Y,		//カーソルY位置
		MS_MSG_SPEED,			//上キーを押したときの移動先
		MS_SAVE,				//下キーを押したときの移動先
		MS_TIMEZONE,			//左キーを押したときの移動先
		NO_MOVE,				//右キーを押したときの移動先
		DebugFightFightTypeAct,	//Aボタンを押したときのアクション
	},
	//MS_LOAD
	{
		LOAD_CUR_X,				//カーソルX位置
		LOAD_CUR_Y,				//カーソルY位置
		MS_MYSEX,				//上キーを押したときの移動先
		MS_MINE_POKE_1,			//下キーを押したときの移動先
		NO_MOVE,				//左キーを押したときの移動先
		MS_SAVE,				//右キーを押したときの移動先
		DebugFightLoadAct,		//Aボタンを押したときのアクション
	},
	//MS_SAVE
	{
		SAVE_CUR_X,				//カーソルX位置
		SAVE_CUR_Y,				//カーソルY位置
		MS_FIGHT_TYPE,			//上キーを押したときの移動先
		MS_ENEMY_POKE_1,		//下キーを押したときの移動先
		MS_LOAD,				//左キーを押したときの移動先
		MS_VERSION,				//右キーを押したときの移動先
		DebugFightSaveAct,		//Aボタンを押したときのアクション
	},
	//MS_VERSION,
	{
		VERSION_CUR_X,			//カーソルX位置
		VERSION_CUR_Y,			//カーソルY位置
		MS_FIGHT_TYPE,			//上キーを押したときの移動先
		MS_ENEMY_POKE_1,		//下キーを押したときの移動先
		MS_SAVE,				//左キーを押したときの移動先
		MS_LOAD,				//右キーを押したときの移動先
		DebugFightVersionAct,	//Aボタンを押したときのアクション
	},
};

static	const	MENU_LIST_PARAM	mlp_s1[]={
	//MENU1_KIND
	{
		KIND_CUR_X,				//カーソルX位置
		KIND_CUR_Y,				//カーソルY位置
		MENU1_SPEDEF_RND,		//上キーを押したときの移動先
		MENU1_LEVEL,			//下キーを押したときの移動先
		NO_MOVE,				//左キーを押したときの移動先
		MENU1_RARE,				//右キーを押したときの移動先
		DebugFightKindAct,		//Aボタンを押したときのアクション
	},
	//MENU1_RARE
	{
		RARE_CUR_X,				//カーソルX位置
		RARE_CUR_Y,				//カーソルY位置
		MENU1_SPEDEF_EXP,		//上キーを押したときの移動先
		MENU1_EXP,				//下キーを押したときの移動先
		MENU1_KIND,				//左キーを押したときの移動先
		NO_MOVE,				//右キーを押したときの移動先
		DebugFightRareAct,		//Aボタンを押したときのアクション
	},
	//MENU1_LEVEL
	{
		LEVEL_CUR_X,			//カーソルX位置
		LEVEL_CUR_Y,			//カーソルY位置
		MENU1_KIND,				//上キーを押したときの移動先
		MENU1_SEX,				//下キーを押したときの移動先
		NO_MOVE,				//左キーを押したときの移動先
		MENU1_EXP,				//右キーを押したときの移動先
		DebugFightLevelAct,		//Aボタンを押したときのアクション
	},
	//MENU1_EXP
	{
		EXP_CUR_X,				//カーソルX位置
		EXP_CUR_Y,				//カーソルY位置
		MENU1_RARE,				//上キーを押したときの移動先
		MENU1_CHR,				//下キーを押したときの移動先
		MENU1_LEVEL,			//左キーを押したときの移動先
		NO_MOVE,				//右キーを押したときの移動先
		DebugFightExpAct,		//Aボタンを押したときのアクション
	},
	//MENU1_SEX
	{
		SEX_CUR_X,				//カーソルX位置
		SEX_CUR_Y,				//カーソルY位置
		MENU1_LEVEL,			//上キーを押したときの移動先
		MENU1_HP_RND,			//下キーを押したときの移動先
		NO_MOVE,				//左キーを押したときの移動先
		MENU1_CHR,				//右キーを押したときの移動先
		DebugFightSexAct,		//Aボタンを押したときのアクション
	},
	//MENU1_CHR
	{
		CHR_CUR_X,				//カーソルX位置
		CHR_CUR_Y,				//カーソルY位置
		MENU1_EXP,				//上キーを押したときの移動先
		MENU1_HP_EXP,			//下キーを押したときの移動先
		MENU1_SEX,				//左キーを押したときの移動先
		NO_MOVE,				//右キーを押したときの移動先
		DebugFightChrAct,		//Aボタンを押したときのアクション
	},
	//MENU1_HP_RND
	{
		HP_RND_CUR_X,			//カーソルX位置
		HP_RND_CUR_Y,			//カーソルY位置
		MENU1_SEX,				//上キーを押したときの移動先
		MENU1_POW_RND,			//下キーを押したときの移動先
		NO_MOVE,				//左キーを押したときの移動先
		MENU1_HP_EXP,			//右キーを押したときの移動先
		DebugFightStatusRndAct,					//Aボタンを押したときのアクション
	},
	//MENU1_POW_RND
	{
		POW_RND_CUR_X,			//カーソルX位置
		POW_RND_CUR_Y,			//カーソルY位置
		MENU1_HP_RND,			//上キーを押したときの移動先
		MENU1_DEF_RND,			//下キーを押したときの移動先
		NO_MOVE,				//左キーを押したときの移動先
		MENU1_POW_EXP,			//右キーを押したときの移動先
		DebugFightStatusRndAct,					//Aボタンを押したときのアクション
	},
	//MENU1_DEF_RND
	{
		DEF_RND_CUR_X,			//カーソルX位置
		DEF_RND_CUR_Y,			//カーソルY位置
		MENU1_POW_RND,			//上キーを押したときの移動先
		MENU1_AGI_RND,			//下キーを押したときの移動先
		NO_MOVE,				//左キーを押したときの移動先
		MENU1_DEF_EXP,			//右キーを押したときの移動先
		DebugFightStatusRndAct,					//Aボタンを押したときのアクション
	},
	//MENU1_AGI_RND
	{
		AGI_RND_CUR_X,			//カーソルX位置
		AGI_RND_CUR_Y,			//カーソルY位置
		MENU1_DEF_RND,			//上キーを押したときの移動先
		MENU1_SPEPOW_RND,		//下キーを押したときの移動先
		NO_MOVE,				//左キーを押したときの移動先
		MENU1_AGI_EXP,			//右キーを押したときの移動先
		DebugFightStatusRndAct,					//Aボタンを押したときのアクション
	},
	//MENU1_SPEPOW_RND
	{
		SPEPOW_RND_CUR_X,		//カーソルX位置
		SPEPOW_RND_CUR_Y,		//カーソルY位置
		MENU1_AGI_RND,			//上キーを押したときの移動先
		MENU1_SPEDEF_RND,		//下キーを押したときの移動先
		NO_MOVE,				//左キーを押したときの移動先
		MENU1_SPEPOW_EXP,		//右キーを押したときの移動先
		DebugFightStatusRndAct,					//Aボタンを押したときのアクション
	},
	//MENU1_SPEDEF_RND
	{
		SPEDEF_RND_CUR_X,		//カーソルX位置
		SPEDEF_RND_CUR_Y,		//カーソルY位置
		MENU1_SPEPOW_RND,		//上キーを押したときの移動先
		MENU1_KIND,				//下キーを押したときの移動先
		NO_MOVE,				//左キーを押したときの移動先
		MENU1_SPEDEF_EXP,		//右キーを押したときの移動先
		DebugFightStatusRndAct,					//Aボタンを押したときのアクション
	},
	//MENU1_HP_EXP
	{
		HP_EXP_CUR_X,			//カーソルX位置
		HP_EXP_CUR_Y,			//カーソルY位置
		MENU1_CHR,				//上キーを押したときの移動先
		MENU1_POW_EXP,			//下キーを押したときの移動先
		MENU1_HP_RND,			//左キーを押したときの移動先
		NO_MOVE,				//右キーを押したときの移動先
		DebugFightStatusExpAct,					//Aボタンを押したときのアクション
	},
	//MENU1_POW_EXP
	{
		POW_EXP_CUR_X,			//カーソルX位置
		POW_EXP_CUR_Y,			//カーソルY位置
		MENU1_HP_EXP,			//上キーを押したときの移動先
		MENU1_DEF_EXP,			//下キーを押したときの移動先
		MENU1_POW_RND,			//左キーを押したときの移動先
		NO_MOVE,				//右キーを押したときの移動先
		DebugFightStatusExpAct,					//Aボタンを押したときのアクション
	},
	//MENU1_DEF_EXP
	{
		DEF_EXP_CUR_X,			//カーソルX位置
		DEF_EXP_CUR_Y,			//カーソルY位置
		MENU1_POW_EXP,			//上キーを押したときの移動先
		MENU1_AGI_EXP,			//下キーを押したときの移動先
		MENU1_DEF_RND,			//左キーを押したときの移動先
		NO_MOVE,				//右キーを押したときの移動先
		DebugFightStatusExpAct,					//Aボタンを押したときのアクション
	},
	//MENU1_AGI_EXP
	{
		AGI_EXP_CUR_X,			//カーソルX位置
		AGI_EXP_CUR_Y,			//カーソルY位置
		MENU1_DEF_EXP,			//上キーを押したときの移動先
		MENU1_SPEPOW_EXP,		//下キーを押したときの移動先
		MENU1_AGI_RND,			//左キーを押したときの移動先
		NO_MOVE,				//右キーを押したときの移動先
		DebugFightStatusExpAct,					//Aボタンを押したときのアクション
	},
	//MENU1_SPEPOW_EXP
	{
		SPEPOW_EXP_CUR_X,		//カーソルX位置
		SPEPOW_EXP_CUR_Y,		//カーソルY位置
		MENU1_AGI_EXP,			//上キーを押したときの移動先
		MENU1_SPEDEF_EXP,		//下キーを押したときの移動先
		MENU1_SPEPOW_RND,		//左キーを押したときの移動先
		NO_MOVE,				//右キーを押したときの移動先
		DebugFightStatusExpAct,					//Aボタンを押したときのアクション
	},
	//MENU1_SPEDEF_EXP
	{
		SPEDEF_EXP_CUR_X,		//カーソルX位置
		SPEDEF_EXP_CUR_Y,		//カーソルY位置
		MENU1_SPEPOW_EXP,		//上キーを押したときの移動先
		MENU1_RARE,				//下キーを押したときの移動先
		MENU1_SPEDEF_RND,		//左キーを押したときの移動先
		NO_MOVE,				//右キーを押したときの移動先
		DebugFightStatusExpAct,					//Aボタンを押したときのアクション
	},
};

static	const	MENU_LIST_PARAM	mlp_s2[]={
	//MENU2_WAZA1
	{
		WAZA1_CUR_X,			//カーソルX位置
		WAZA1_CUR_Y,			//カーソルY位置
		MENU2_GETBALL,			//上キーを押したときの移動先
		MENU2_WAZA2,			//下キーを押したときの移動先
		MENU2_PP_COUNT1,		//左キーを押したときの移動先
		MENU2_PP1,				//右キーを押したときの移動先
		DebugFightWazaAct,		//Aボタンを押したときのアクション
	},
	//MENU2_WAZA2
	{
		WAZA2_CUR_X,			//カーソルX位置
		WAZA2_CUR_Y,			//カーソルY位置
		MENU2_WAZA1,			//上キーを押したときの移動先
		MENU2_WAZA3,			//下キーを押したときの移動先
		MENU2_PP_COUNT2,		//左キーを押したときの移動先
		MENU2_PP2,				//右キーを押したときの移動先
		DebugFightWazaAct,		//Aボタンを押したときのアクション
	},
	//MENU2_WAZA3
	{
		WAZA3_CUR_X,			//カーソルX位置
		WAZA3_CUR_Y,			//カーソルY位置
		MENU2_WAZA2,			//上キーを押したときの移動先
		MENU2_WAZA4,			//下キーを押したときの移動先
		MENU2_PP_COUNT3,		//左キーを押したときの移動先
		MENU2_PP3,				//右キーを押したときの移動先
		DebugFightWazaAct,		//Aボタンを押したときのアクション
	},
	//MENU2_WAZA4
	{
		WAZA4_CUR_X,			//カーソルX位置
		WAZA4_CUR_Y,			//カーソルY位置
		MENU2_WAZA3,			//上キーを押したときの移動先
		MENU2_SPEABI,			//下キーを押したときの移動先
		MENU2_PP_COUNT4,		//左キーを押したときの移動先
		MENU2_PP4,				//右キーを押したときの移動先
		DebugFightWazaAct,		//Aボタンを押したときのアクション
	},
	//MENU2_PP1
	{
		PP1_CUR_X,				//カーソルX位置
		PP1_CUR_Y,				//カーソルY位置
		MENU2_DEFAULT_HP,		//上キーを押したときの移動先
		MENU2_PP2,				//下キーを押したときの移動先
		MENU2_WAZA1,			//左キーを押したときの移動先
		MENU2_PP_COUNT1,		//右キーを押したときの移動先
		DebugFightPPAct,		//Aボタンを押したときのアクション
	},
	//MENU2_PP2
	{
		PP2_CUR_X,				//カーソルX位置
		PP2_CUR_Y,				//カーソルY位置
		MENU2_PP1,				//上キーを押したときの移動先
		MENU2_PP3,				//下キーを押したときの移動先
		MENU2_WAZA2,			//左キーを押したときの移動先
		MENU2_PP_COUNT2,		//右キーを押したときの移動先
		DebugFightPPAct,		//Aボタンを押したときのアクション
	},
	//MENU2_PP3
	{
		PP3_CUR_X,				//カーソルX位置
		PP3_CUR_Y,				//カーソルY位置
		MENU2_PP2,				//上キーを押したときの移動先
		MENU2_PP4,				//下キーを押したときの移動先
		MENU2_WAZA3,			//左キーを押したときの移動先
		MENU2_PP_COUNT3,		//右キーを押したときの移動先
		DebugFightPPAct,		//Aボタンを押したときのアクション
	},
	//MENU2_PP4
	{
		PP4_CUR_X,				//カーソルX位置
		PP4_CUR_Y,				//カーソルY位置
		MENU2_PP3,				//上キーを押したときの移動先
		MENU2_SPEABI,			//下キーを押したときの移動先
		MENU2_WAZA4,			//左キーを押したときの移動先
		MENU2_PP_COUNT4,		//右キーを押したときの移動先
		DebugFightPPAct,		//Aボタンを押したときのアクション
	},
	//MENU2_PP_COUNT_1
	{
		PP_COUNT1_CUR_X,		//カーソルX位置
		PP_COUNT1_CUR_Y,		//カーソルY位置
		MENU2_DEFAULT_HP,		//上キーを押したときの移動先
		MENU2_PP_COUNT2,		//下キーを押したときの移動先
		MENU2_PP1,				//左キーを押したときの移動先
		MENU2_WAZA1,			//右キーを押したときの移動先
		DebugFightPPCountAct,	//Aボタンを押したときのアクション
	},
	//MENU2_PP_COUNT_2
	{
		PP_COUNT2_CUR_X,		//カーソルX位置
		PP_COUNT2_CUR_Y,		//カーソルY位置
		MENU2_PP_COUNT1,		//上キーを押したときの移動先
		MENU2_PP_COUNT3,		//下キーを押したときの移動先
		MENU2_PP2,				//左キーを押したときの移動先
		MENU2_WAZA2,			//右キーを押したときの移動先
		DebugFightPPCountAct,	//Aボタンを押したときのアクション
	},
	//MENU2_PP_COUNT_3
	{
		PP_COUNT3_CUR_X,		//カーソルX位置
		PP_COUNT3_CUR_Y,		//カーソルY位置
		MENU2_PP_COUNT2,		//上キーを押したときの移動先
		MENU2_PP_COUNT4,		//下キーを押したときの移動先
		MENU2_PP3,				//左キーを押したときの移動先
		MENU2_WAZA3,			//右キーを押したときの移動先
		DebugFightPPCountAct,	//Aボタンを押したときのアクション
	},
	//MENU2_PP_COUNT_4
	{
		PP_COUNT4_CUR_X,		//カーソルX位置
		PP_COUNT4_CUR_Y,		//カーソルY位置
		MENU2_PP_COUNT3,		//上キーを押したときの移動先
		MENU2_SPEABI,			//下キーを押したときの移動先
		MENU2_PP4,				//左キーを押したときの移動先
		MENU2_WAZA4,			//右キーを押したときの移動先
		DebugFightPPCountAct,	//Aボタンを押したときのアクション
	},
	//MENU2_SPEABI
	{
		SPEABI_CUR_X,			//カーソルX位置
		SPEABI_CUR_Y,			//カーソルY位置
		MENU2_WAZA4,			//上キーを押したときの移動先
		MENU2_SPEABI_SET,		//下キーを押したときの移動先
		NO_MOVE,				//左キーを押したときの移動先
		NO_MOVE,				//右キーを押したときの移動先
		DebugFightSpeAbiAct,	//Aボタンを押したときのアクション
	},
	//MENU2_SPEABI_SET
	{
		SPEABI_SET_CUR_X,		//カーソルX位置
		SPEABI_SET_CUR_Y,		//カーソルY位置
		MENU2_SPEABI,			//上キーを押したときの移動先
		MENU2_ITEM,				//下キーを押したときの移動先
		NO_MOVE,				//左キーを押したときの移動先
		NO_MOVE,				//右キーを押したときの移動先
		DebugFightSpeAbiSetAct,	//Aボタンを押したときのアクション
	},
	//MENU2_ITEM
	{
		ITEM_CUR_X,				//カーソルX位置
		ITEM_CUR_Y,				//カーソルY位置
		MENU2_SPEABI_SET,		//上キーを押したときの移動先
		MENU2_FRIEND,			//下キーを押したときの移動先
		NO_MOVE,				//左キーを押したときの移動先
		NO_MOVE,				//右キーを押したときの移動先
		DebugFightItemAct,		//Aボタンを押したときのアクション
	},
	//MENU2_FRIEND
	{
		FRIEND_CUR_X,			//カーソルX位置
		FRIEND_CUR_Y,			//カーソルY位置
		MENU2_ITEM,				//上キーを押したときの移動先
		MENU2_CONDITION,		//下キーを押したときの移動先
		NO_MOVE,				//左キーを押したときの移動先
		NO_MOVE,				//右キーを押したときの移動先
		DebugFightFriendAct,	//Aボタンを押したときのアクション
	},
	//MENU2_CONDITION
	{
		CONDITION_CUR_X,		//カーソルX位置
		CONDITION_CUR_Y,		//カーソルY位置
		MENU2_FRIEND,			//上キーを押したときの移動先
		MENU2_DEFAULT_HP,		//下キーを押したときの移動先
		NO_MOVE,				//左キーを押したときの移動先
		NO_MOVE,				//右キーを押したときの移動先
		DebugFightConditionAct,	//Aボタンを押したときのアクション
	},
	//MENU2_DEFAULT_HP
	{
		DEFAULT_HP_CUR_X,		//カーソルX位置
		DEFAULT_HP_CUR_Y,		//カーソルY位置
		MENU2_CONDITION,		//上キーを押したときの移動先
		MENU2_GETBALL,			//下キーを押したときの移動先
		NO_MOVE,				//左キーを押したときの移動先
		NO_MOVE,				//右キーを押したときの移動先
		DebugFightDefaultHPAct,	//Aボタンを押したときのアクション
	},
	//MENU2_GETBALL
	{
		GETBALL_CUR_X,			//カーソルX位置
		GETBALL_CUR_Y,			//カーソルY位置
		MENU2_DEFAULT_HP,		//上キーを押したときの移動先
		MENU2_WAZA1,			//下キーを押したときの移動先
		NO_MOVE,				//左キーを押したときの移動先
		NO_MOVE,				//右キーを押したときの移動先
		DebugFightGetBallAct,	//Aボタンを押したときのアクション
	},
};

static	const	MENU_LIST_PARAM	mlp_s3[]={
	//MENU3_FORMNO
	{
		FORMNO_CUR_X,			//カーソルX位置
		FORMNO_CUR_Y,			//カーソルY位置
		MENU3_EGG_FLAG,			//上キーを押したときの移動先
		MENU3_EGG_FLAG,			//下キーを押したときの移動先
		NO_MOVE,				//左キーを押したときの移動先
		NO_MOVE,				//右キーを押したときの移動先
		DebugFightFormNoAct,	//Aボタンを押したときのアクション
	},
	//MENU3_EGG_FLAG
	{
		EGG_FLAG_CUR_X,			//カーソルX位置
		EGG_FLAG_CUR_Y,			//カーソルY位置
		MENU3_FORMNO,			//上キーを押したときの移動先
		MENU3_FORMNO,			//下キーを押したときの移動先
		NO_MOVE,				//左キーを押したときの移動先
		NO_MOVE,				//右キーを押したときの移動先
		DebugFightEggFlagAct,	//Aボタンを押したときのアクション
	},
};

const	MENU_LIST_PARAM	*	const	mlp_s_list[]={
	mlp_s1,
	mlp_s2,
	mlp_s3,
};

static	const	u16	pal[]={
		GX_RGB(31,31,31),				//0:白
		GX_RGB(13,13,13),				//1:濃い灰
		GX_RGB(24,24,24),				//2:薄い灰
		GX_RGB(15,31,15),				//3:うすみどり
		GX_RGB(31,15,15),				//4:うすあか
		GX_RGB(15,15,31),				//5:うすあお
		GX_RGB( 0, 0, 0),
		GX_RGB( 0, 0, 0),
		GX_RGB( 0, 0, 0),
		GX_RGB( 0, 0, 0),
		GX_RGB( 0, 0, 0),
		GX_RGB( 0, 0, 0),
		GX_RGB( 0, 0, 0),
		GX_RGB( 0, 0, 0),
		GX_RGB( 0, 0, 0),
		GX_RGB(31,31,31),				//15:白
};

static	const	int	param_mode_tbl[]={
	MODE_DEFAULT_PARAM,
	MODE_DEFAULT_WAZA,
};

static	const	u32	fight_type_table[][2]={
	{FIGHT_TYPE_YASEI,			0x03},
	{FIGHT_TYPE_TRAINER,		0x03},
	{FIGHT_TYPE_2vs2_TRAINER,	0x0f},
	{FIGHT_TYPE_1vs1_SIO,		0x03},
	{FIGHT_TYPE_1vs1_SIO,		0x03},
	{FIGHT_TYPE_2vs2_SIO,		0x0f},
	{FIGHT_TYPE_2vs2_SIO,		0x0f},
	{FIGHT_TYPE_MULTI_SIO,		0x03},
	{FIGHT_TYPE_MULTI_SIO,		0x03},
	{FIGHT_TYPE_1vs1_SIO,		0x03},
	{FIGHT_TYPE_1vs1_SIO,		0x03},
	{FIGHT_TYPE_SAFARI,			0x03},
	{FIGHT_TYPE_POKE_PARK,		0x03},
	{FIGHT_TYPE_GET_DEMO,		0x03},
	{FIGHT_TYPE_2vs2_YASEI,		0x0f},
	{FIGHT_TYPE_AI_MULTI,		0x0f},
	{FIGHT_TYPE_BATTLE_TOWER_SIO_MULTI,		0x0f},
	{FIGHT_TYPE_BATTLE_TOWER_SIO_MULTI,		0x0f},
};

static	const	int	weather_table[]={
	WEATHER_SYS_SUNNY,			// 晴れ
	WEATHER_SYS_RAIN,			// 雨
	WEATHER_SYS_STRAIN,			// 大雨
	WEATHER_SYS_SPARK,			// 大雨
	WEATHER_SYS_SNOW,			// 雪
	WEATHER_SYS_SNOWSTORM,		// 吹雪
	WEATHER_SYS_SNOWSTORM_H,	// 猛吹雪
	WEATHER_SYS_SANDSTORM,		// BG使用砂嵐
	WEATHER_SYS_MIST1,			// 霧払いの霧
	WEATHER_SYS_MIST2,			// 霧払いの霧
};

//============================================================================================
/**
 *	戦闘背景画面初期化＆画面生成
 */
//============================================================================================
void	DebugFightBGCreate(DEBUG_FIGHT_PARAM *dfp,GF_BGL_INI *bgl)
{
	sys_VBlankFuncChange(NULL,NULL);

	GF_Disp_GX_VisibleControlInit();
	WIPE_ResetBrightness(WIPE_DISP_MAIN);		// メイン面
	WIPE_ResetBrightness(WIPE_DISP_SUB);		// サブ面

	//VRAM設定
	{
		GF_BGL_DISPVRAM vramSetTable = {
			GX_VRAM_BG_128_B,				// メイン2DエンジンのBG
			GX_VRAM_BGEXTPLTT_NONE,			// メイン2DエンジンのBG拡張パレット
			GX_VRAM_SUB_BG_128_C,			// サブ2DエンジンのBG
			GX_VRAM_SUB_BGEXTPLTT_NONE,		// サブ2DエンジンのBG拡張パレット
			GX_VRAM_OBJ_64_E,				// メイン2DエンジンのOBJ
			GX_VRAM_OBJEXTPLTT_NONE,		// メイン2DエンジンのOBJ拡張パレット
			GX_VRAM_SUB_OBJ_16_I,			// サブ2DエンジンのOBJ
			GX_VRAM_SUB_OBJEXTPLTT_NONE,	// サブ2DエンジンのOBJ拡張パレット
			GX_VRAM_TEX_0_A,				// テクスチャイメージスロット
			GX_VRAM_TEXPLTT_01_FG			// テクスチャパレットスロット
		};
		GF_Disp_SetBank( &vramSetTable );

		//VRAMクリア
		MI_CpuClear32((void*)HW_BG_VRAM, HW_BG_VRAM_SIZE);
		MI_CpuClear32((void*)HW_DB_BG_VRAM, HW_DB_BG_VRAM_SIZE);
		MI_CpuClear32((void*)HW_OBJ_VRAM, HW_OBJ_VRAM_SIZE);
		MI_CpuClear32((void*)HW_DB_OBJ_VRAM, HW_DB_OBJ_VRAM_SIZE);
	}

	// BG SYSTEM
	{
		GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_3D,
		};
		GF_BGL_InitBG( &BGsys_data );
	}

	//メイン画面フレーム設定
	{
		GF_BGL_BGCNT_HEADER TextBgCntDat[] = {
			///<FRAME1_M
			{
				0, 0, 0x0800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
				GX_BG_SCRBASE_0x0000, GX_BG_CHARBASE_0x04000, GX_BG_EXTPLTT_01,
				0, 0, 0, FALSE
			},
		};
		GF_BGL_BGControlSet(bgl, GF_BGL_FRAME1_M, &TextBgCntDat[0], GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear(bgl, GF_BGL_FRAME1_M );
	}
	//サブ画面フレーム設定
	{
		GF_BGL_BGCNT_HEADER TextBgCntDat[] = {
			///<FRAME1_S
			{
				0, 0, 0x0800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
				GX_BG_SCRBASE_0x0000, GX_BG_CHARBASE_0x04000, GX_BG_EXTPLTT_01,
				0, 0, 0, FALSE
			},
		};
		GF_BGL_BGControlSet(bgl, GF_BGL_FRAME1_S, &TextBgCntDat[0], GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear(bgl, GF_BGL_FRAME1_S );
	}

	//背景グラフィックデータロード
	{
		DC_FlushRange((void *)&pal,sizeof(pal));
		GX_LoadBGPltt((void *)&pal,0,sizeof(pal));
		DC_FlushRange((void *)&pal,sizeof(pal));
		GXS_LoadBGPltt((void *)&pal,0,sizeof(pal));
	}

	GF_Disp_DispOn();

	FontProc_LoadBitData(FONT_SYSTEM,HEAPID_DEBUG_APPLICATION);

	sys_VBlankFuncChange(DebugFightVBlank,dfp);
}

//============================================================================================
/**
 *	デバッグファイト用ポケモンパラメータ初期化
 */
//============================================================================================
void	DebugFightPokemonParamInit(DEBUG_POKEMON_PARAM *dpp)
{
	MI_CpuClearFast(dpp,sizeof(DEBUG_POKEMON_PARAM));

	dpp->level=1;
	dpp->exp=0;
	dpp->waza[0]=WAZANO_HATAKU;
	dpp->pp[0]=WT_WazaDataParaGet(WAZANO_HATAKU,ID_WTD_pp);
	dpp->get_ball=ITEM_MONSUTAABOORU;
}

//============================================================================================
/**
 *	AIスクリーン生成
 */
//============================================================================================

void	DebugFightAIScreenCreate(DEBUG_FIGHT_PARAM *dfp)
{
	int		i,cnt;

	GF_BGL_BmpWinDataFill(dfp->win_m,0xff);

	for(i=DF_BASIC_AI;i<DF_HARASS_AI+1;i++){
		cnt=i-DF_BASIC_AI;
		MSGMAN_GetString(dfp->man_msg,i,dfp->msg_buf);
		GF_STR_PrintSimple(dfp->win_m,FONT_SYSTEM,dfp->msg_buf,MINE_X,MINE_Y+16*cnt,MSG_NO_PUT,NULL);
		if(dfp->dsp.ai_bit&No2Bit(cnt)){
			MSGMAN_GetString(dfp->man_msg,DF_AI_ON,dfp->msg_buf);
			GF_STR_PrintSimple(dfp->win_m,FONT_SYSTEM,dfp->msg_buf,ENEMY_X,MINE_Y+16*cnt,MSG_NO_PUT,NULL);
		}
		else{
			MSGMAN_GetString(dfp->man_msg,DF_AI_OFF,dfp->msg_buf);
			GF_STR_PrintSimple(dfp->win_m,FONT_SYSTEM,dfp->msg_buf,ENEMY_X,MINE_Y+16*cnt,MSG_NO_PUT,NULL);
		}
	}

	dfp->put_req=1;
}

//============================================================================================
/**
 *	AUTOモードスクリーン生成
 */
//============================================================================================

void	DebugFightAutoScreenCreate(DEBUG_FIGHT_PARAM *dfp)
{
	int		i,cnt;

	GF_BGL_BmpWinDataFill(dfp->win_m,0xff);

	for(i=DF_PP_NO_DEC;i<DF_AUTO_BATTLE+1;i++){
		cnt=i-DF_PP_NO_DEC;
		MSGMAN_GetString(dfp->man_msg,i,dfp->msg_buf);
		GF_STR_PrintSimple(dfp->win_m,FONT_SYSTEM,dfp->msg_buf,MINE_X,MINE_Y+16*cnt,MSG_NO_PUT,NULL);
		if(dfp->dsp.battle_status_flag&No2Bit(cnt)){
			MSGMAN_GetString(dfp->man_msg,DF_AI_ON,dfp->msg_buf);
			GF_STR_PrintSimple(dfp->win_m,FONT_SYSTEM,dfp->msg_buf,ENEMY_X,MINE_Y+16*cnt,MSG_NO_PUT,NULL);
		}
		else{
			MSGMAN_GetString(dfp->man_msg,DF_AI_OFF,dfp->msg_buf);
			GF_STR_PrintSimple(dfp->win_m,FONT_SYSTEM,dfp->msg_buf,ENEMY_X,MINE_Y+16*cnt,MSG_NO_PUT,NULL);
		}
	}

	DebugFightTrainerIDPut(dfp);
	DebugFightTrainerIDDataPut(dfp);
	DebugFightBT_TrainerIDPut(dfp);
	DebugFightBT_TrainerIDDataPut(dfp);

	dfp->put_req=1;
}

//============================================================================================
/**
 *	メインスクリーン生成
 */
//============================================================================================

void	DebugFightMainScreenCreate(DEBUG_FIGHT_PARAM *dfp)
{
	int		i;

	GF_BGL_BmpWinDataFill(dfp->win_m,0xff);

	MSGMAN_GetString(dfp->man_msg,DF_MINE,dfp->msg_buf);
	GF_STR_PrintSimple(dfp->win_m,FONT_SYSTEM,dfp->msg_buf,MINE_X,MINE_Y,MSG_NO_PUT,NULL);
	MSGMAN_GetString(dfp->man_msg,DF_ENEMY,dfp->msg_buf);
	GF_STR_PrintSimple(dfp->win_m,FONT_SYSTEM,dfp->msg_buf,ENEMY_X,ENEMY_Y,MSG_NO_PUT,NULL);

	MSGMAN_GetString(dfp->man_msg,DF_LOAD,dfp->msg_buf);
	GF_STR_PrintSimple(dfp->win_m,FONT_SYSTEM,dfp->msg_buf,LOAD_X,LOAD_Y,MSG_NO_PUT,NULL);
	MSGMAN_GetString(dfp->man_msg,DF_SAVE,dfp->msg_buf);
	GF_STR_PrintSimple(dfp->win_m,FONT_SYSTEM,dfp->msg_buf,SAVE_X,SAVE_Y,MSG_NO_PUT,NULL);

	for(i=0;i<12;i++){
		DebugFightMonsNamePut(dfp,i,COL_NORMAL);
	}

	DebugFightRuleDataPut(dfp,COL_NORMAL);
	DebugFightEffectFlagDataPut(dfp,COL_NORMAL);
	DebugFightMsgSpeedDataPut(dfp,COL_NORMAL);
	DebugFightFightTypeDataPut(dfp,COL_NORMAL);
	DebugFightVersionDataPut(dfp,COL_NORMAL);
	DebugFightGroundDataPut(dfp,COL_NORMAL);
	DebugFightBGDataPut(dfp,COL_NORMAL);
	DebugFightWeatherDataPut(dfp,COL_NORMAL);
	DebugFightTimeZoneDataPut(dfp,COL_NORMAL);
	DebugFightMySexDataPut(dfp,COL_NORMAL);

	dfp->put_req=1;
}

static	const	u16	MonsNamePosTable[][2]={
	{MINE_POKE_X,MINE_POKE_Y+MINE_POKE_Y_OFS*0},
	{MINE_POKE_X,MINE_POKE_Y+MINE_POKE_Y_OFS*1},
	{MINE_POKE_X,MINE_POKE_Y+MINE_POKE_Y_OFS*2},
	{MINE_POKE_X,MINE_POKE_Y+MINE_POKE_Y_OFS*3},
	{MINE_POKE_X,MINE_POKE_Y+MINE_POKE_Y_OFS*4},
	{MINE_POKE_X,MINE_POKE_Y+MINE_POKE_Y_OFS*5},
	{ENEMY_POKE_X,ENEMY_POKE_Y+ENEMY_POKE_Y_OFS*0},
	{ENEMY_POKE_X,ENEMY_POKE_Y+ENEMY_POKE_Y_OFS*1},
	{ENEMY_POKE_X,ENEMY_POKE_Y+ENEMY_POKE_Y_OFS*2},
	{ENEMY_POKE_X,ENEMY_POKE_Y+ENEMY_POKE_Y_OFS*3},
	{ENEMY_POKE_X,ENEMY_POKE_Y+ENEMY_POKE_Y_OFS*4},
	{ENEMY_POKE_X,ENEMY_POKE_Y+ENEMY_POKE_Y_OFS*5},
};

static	void	DebugFightMonsNamePut(DEBUG_FIGHT_PARAM *dfp,int pos,GF_PRINTCOLOR col)
{
	GF_BGL_BmpWinFill(dfp->win_m,0x0f,MonsNamePosTable[pos][0],MonsNamePosTable[pos][1],120,16);
	MSGMAN_GetString(dfp->man_poke,dfp->dsp.dpp[pos].mons_no,dfp->msg_buf);
	GF_STR_PrintColor(dfp->win_m,FONT_SYSTEM,dfp->msg_buf,MonsNamePosTable[pos][0],MonsNamePosTable[pos][1],MSG_NO_PUT,col,NULL);
	dfp->put_req=1;
}

static	void	DebugFightRuleDataPut(DEBUG_FIGHT_PARAM *dfp,GF_PRINTCOLOR col)
{
	GF_BGL_BmpWinFill(dfp->win_m,0x0f,RULE_DATA_X,RULE_DATA_Y,12*4,16);
	MSGMAN_GetString(dfp->man_msg,DF_RULE_IREKAE+dfp->dsp.rule,dfp->msg_buf);
	GF_STR_PrintColor(dfp->win_m,FONT_SYSTEM,dfp->msg_buf,RULE_DATA_X,RULE_DATA_Y,MSG_NO_PUT,col,NULL);
	dfp->put_req=1;
}

static	void	DebugFightEffectFlagDataPut(DEBUG_FIGHT_PARAM *dfp,GF_PRINTCOLOR col)
{
	GF_BGL_BmpWinFill(dfp->win_m,0x0f,EFF_FLAG_DATA_X,EFF_FLAG_DATA_Y,12*6,16);
	MSGMAN_GetString(dfp->man_msg,DF_EFFECT_ON+dfp->dsp.effect_flag,dfp->msg_buf);
	GF_STR_PrintColor(dfp->win_m,FONT_SYSTEM,dfp->msg_buf,EFF_FLAG_DATA_X,EFF_FLAG_DATA_Y,MSG_NO_PUT,col,NULL);
	dfp->put_req=1;
}

static	void	DebugFightMsgSpeedDataPut(DEBUG_FIGHT_PARAM *dfp,GF_PRINTCOLOR col)
{
	GF_BGL_BmpWinFill(dfp->win_m,0x0f,MSG_SPEED_DATA_X,MSG_SPEED_DATA_Y,12*3,16);
	MSGMAN_GetString(dfp->man_msg,DF_MSG_SPEED_SLOW+dfp->dsp.msg_speed,dfp->msg_buf);
	GF_STR_PrintColor(dfp->win_m,FONT_SYSTEM,dfp->msg_buf,MSG_SPEED_DATA_X,MSG_SPEED_DATA_Y,MSG_NO_PUT,col,NULL);
	dfp->put_req=1;
}

static	void	DebugFightFightTypePut(DEBUG_FIGHT_PARAM *dfp)
{
	MSGMAN_GetString(dfp->man_msg,DF_FIGHTTYPE,dfp->msg_buf);
	GF_STR_PrintSimple(dfp->win_m,FONT_SYSTEM,dfp->msg_buf,FIGHT_TYPE_X,FIGHT_TYPE_Y,MSG_NO_PUT,NULL);
	dfp->put_req=1;
}

static	void	DebugFightFightTypeDataPut(DEBUG_FIGHT_PARAM *dfp,GF_PRINTCOLOR col)
{
	GF_BGL_BmpWinFill(dfp->win_m,0x0f,FIGHT_TYPE_DATA_X,FIGHT_TYPE_DATA_Y,120,16);
	MSGMAN_GetString(dfp->man_msg,DF_FT_1VS1+dfp->dsp.fight_type,dfp->msg_buf);
	GF_STR_PrintColor(dfp->win_m,FONT_SYSTEM,dfp->msg_buf,FIGHT_TYPE_DATA_X,FIGHT_TYPE_DATA_Y,MSG_NO_PUT,col,NULL);
	dfp->put_req=1;
}

static	void	DebugFightVersionDataPut(DEBUG_FIGHT_PARAM *dfp,GF_PRINTCOLOR col)
{
	GF_BGL_BmpWinFill(dfp->win_m,0x0f,VERSION_DATA_X,VERSION_DATA_Y,12,16);

	STRBUF_SetNumber(dfp->msg_buf,dfp->dsp.version,1,NUMBER_DISPTYPE_LEFT,NUMBER_CODETYPE_DEFAULT);
	GF_STR_PrintColor(dfp->win_m,FONT_SYSTEM,dfp->msg_buf,VERSION_DATA_X,VERSION_DATA_Y,MSG_NO_PUT,col,NULL);

	dfp->put_req=1;
}

static	void	DebugFightGroundDataPut(DEBUG_FIGHT_PARAM *dfp,GF_PRINTCOLOR col)
{
	GF_BGL_BmpWinFill(dfp->win_m,0x0f,GROUND_X,GROUND_Y,12*6,16);
	MSGMAN_GetString(dfp->man_msg,DF_GROUND_GRAVEL+dfp->dsp.ground,dfp->msg_buf);
	GF_STR_PrintColor(dfp->win_m,FONT_SYSTEM,dfp->msg_buf,GROUND_X,GROUND_Y,MSG_NO_PUT,col,NULL);
	dfp->put_req=1;
}

static	void	DebugFightBGDataPut(DEBUG_FIGHT_PARAM *dfp,GF_PRINTCOLOR col)
{
	GF_BGL_BmpWinFill(dfp->win_m,0x0f,BG_X,BG_Y,12*5,16);
	MSGMAN_GetString(dfp->man_msg,DF_BG_SOUGEN+dfp->dsp.bg,dfp->msg_buf);
	GF_STR_PrintColor(dfp->win_m,FONT_SYSTEM,dfp->msg_buf,BG_X,BG_Y,MSG_NO_PUT,col,NULL);
	dfp->put_req=1;
}

static	void	DebugFightWeatherDataPut(DEBUG_FIGHT_PARAM *dfp,GF_PRINTCOLOR col)
{
	GF_BGL_BmpWinFill(dfp->win_m,0x0f,WEATHER_X,WEATHER_Y,12*6,16);
	MSGMAN_GetString(dfp->man_msg,DF_WEATHER_NORMAL+dfp->dsp.weather,dfp->msg_buf);
	GF_STR_PrintColor(dfp->win_m,FONT_SYSTEM,dfp->msg_buf,WEATHER_X,WEATHER_Y,MSG_NO_PUT,col,NULL);
	dfp->put_req=1;
}

static	void	DebugFightTimeZoneDataPut(DEBUG_FIGHT_PARAM *dfp,GF_PRINTCOLOR col)
{
	GF_BGL_BmpWinFill(dfp->win_m,0x0f,TIMEZONE_X,TIMEZONE_Y,12*4,16);
	MSGMAN_GetString(dfp->man_msg,DF_TIMEZONE_MORNING+dfp->dsp.time_zone,dfp->msg_buf);
	GF_STR_PrintColor(dfp->win_m,FONT_SYSTEM,dfp->msg_buf,TIMEZONE_X,TIMEZONE_Y,MSG_NO_PUT,col,NULL);
	dfp->put_req=1;
}

static	void	DebugFightMySexPut(DEBUG_FIGHT_PARAM *dfp)
{
	MSGMAN_GetString(dfp->man_msg,DF_MYSEX,dfp->msg_buf);
	GF_STR_PrintSimple(dfp->win_m,FONT_SYSTEM,dfp->msg_buf,MYSEX_X,MYSEX_Y,MSG_NO_PUT,NULL);
	dfp->put_req=1;
}

static	void	DebugFightMySexDataPut(DEBUG_FIGHT_PARAM *dfp,GF_PRINTCOLOR col)
{
	GF_BGL_BmpWinFill(dfp->win_m,0x0f,MYSEX_DATA_X,MYSEX_DATA_Y,12*3,16);
	MSGMAN_GetString(dfp->man_msg,DF_BOY_NAME+dfp->dsp.my_sex,dfp->msg_buf);
	GF_STR_PrintColor(dfp->win_m,FONT_SYSTEM,dfp->msg_buf,MYSEX_DATA_X,MYSEX_DATA_Y,MSG_NO_PUT,col,NULL);
	dfp->put_req=1;
}

//============================================================================================
/**
 *	サブスクリーン生成
 */
//============================================================================================

void	DebugFightSubScreenCreate(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp,int page)
{
	switch(page){
	case 0:
		{
			int	i;

//			if(page!=dfp->flag){
//				dfp->flag=page;

				GF_BGL_BmpWinDataFill(dfp->win_s,0xff);

				DebugFightKindPut(dfp);
				DebugFightLevelPut(dfp);
				DebugFightExpPut(dfp);
				DebugFightSexPut(dfp);
				DebugFightChrPut(dfp);

				DebugFightHPRndPut(dfp);
				DebugFightPowRndPut(dfp);
				DebugFightDefRndPut(dfp);
				DebugFightAgiRndPut(dfp);
				DebugFightSpePowRndPut(dfp);
				DebugFightSpeDefRndPut(dfp);

				DebugFightHPExpPut(dfp);
				DebugFightPowExpPut(dfp);
				DebugFightDefExpPut(dfp);
				DebugFightAgiExpPut(dfp);
				DebugFightSpePowExpPut(dfp);
				DebugFightSpeDefExpPut(dfp);
//			}

			DebugFightKindDataPut(dfp,dpp,MODE_NORMAL);
			DebugFightRareDataPut(dfp,dpp,COL_NORMAL);
			DebugFightLevelDataPut(dfp,dpp,MODE_NORMAL);
			DebugFightExpDataPut(dfp,dpp,MODE_NORMAL);
			DebugFightSexDataPut(dfp,dpp,COL_NORMAL);
			DebugFightChrDataPut(dfp,dpp,COL_NORMAL);

			for(i=STATUS_HP;i<STATUS_MAX;i++){
				DebugFightStatusRndDataPut(dfp,dpp,i,MODE_NORMAL);
				DebugFightStatusExpDataPut(dfp,dpp,i,MODE_NORMAL);
			}

			DebugFightParamPut(dfp,dpp);
		}
		break;
	case 1:
		{
			int	i;

//			if(page!=dfp->flag){
//				dfp->flag=page;

				GF_BGL_BmpWinDataFill(dfp->win_s,0xff);

//				for(i=0;i<4;i++){
//					DebugFightWazaPut(dfp,i);
//				}

				DebugFightSpeAbiPut(dfp);
				DebugFightSpeAbiSetPut(dfp);
				DebugFightItemPut(dfp);
				DebugFightFriendPut(dfp);
				DebugFightConditionPut(dfp);
				DebugFightDefaultHPPut(dfp);
				DebugFightGetBallPut(dfp);
//			}

			for(i=0;i<4;i++){
				DebugFightWazaDataPut(dfp,dpp,i,MODE_NORMAL);
				DebugFightPPDataPut(dfp,dpp,i,MODE_NORMAL);
				DebugFightPPCountDataPut(dfp,dpp,i,MODE_NORMAL);
			}

			DebugFightSpeAbiDataPut(dfp,dpp,COL_NORMAL);
			DebugFightSpeAbiSetDataPut(dfp,dpp,MODE_NORMAL);
			DebugFightItemDataPut(dfp,dpp,MODE_NORMAL);
			DebugFightFriendDataPut(dfp,dpp,MODE_NORMAL);
			DebugFightConditionDataPut(dfp,dpp,COL_NORMAL);
			DebugFightDefaultHPDataPut(dfp,dpp,MODE_NORMAL);
			DebugFightGetBallDataPut(dfp,dpp,COL_NORMAL);
		}
		break;
	case 2:
		{
			int	form_no_max;

			GF_BGL_BmpWinDataFill(dfp->win_s,0xff);

			form_no_max=DebugFightFormNoMaxGet(dpp);
			DebugFightFormNoPut(dfp);
			DebugFightFormNoDataPut(dfp,dpp,form_no_max,MODE_NORMAL);
			DebugFightEggFlagDataPut(dfp,dpp);
		}
		break;
	default:
//		dfp->flag=page;
		GF_BGL_BmpWinOn(dfp->win_s);
		break;
	}
}

static	void	DebugFightKindPut(DEBUG_FIGHT_PARAM *dfp)
{
	MSGMAN_GetString(dfp->man_msg,DF_KIND,dfp->msg_buf);
	GF_STR_PrintSimple(dfp->win_s,FONT_SYSTEM,dfp->msg_buf,MENU1_LIST_L_X,MENU1_LIST_Y+MENU1_LIST_OFS*0,MSG_NO_PUT,NULL);
	dfp->put_req=1;
}

static	void	DebugFightKindDataPut(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp,int mode)
{
	GF_BGL_BmpWinFill(dfp->win_s,0x0f,KIND_DATA_X,KIND_DATA_Y,12*8,16);

	DebugFightNumPut(dfp,KIND_DATA_X,KIND_DATA_Y,dpp->mons_no,3,dfp->cur_pos_keta,mode);

	MSGMAN_GetString(dfp->man_poke,dpp->mons_no,dfp->msg_buf);
	GF_STR_PrintSimple(dfp->win_s,FONT_SYSTEM,dfp->msg_buf,KIND_NAME_X,KIND_DATA_Y,MSG_NO_PUT,NULL);
	dfp->put_req=1;
}

static	void	DebugFightRareDataPut(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp,GF_PRINTCOLOR col)
{
	GF_BGL_BmpWinFill(dfp->win_s,0x0f,RARE_DATA_X,RARE_DATA_Y,12*4,16);

	MSGMAN_GetString(dfp->man_msg,DF_NO_RARE+dpp->rare,dfp->msg_buf);
	GF_STR_PrintColor(dfp->win_s,FONT_SYSTEM,dfp->msg_buf,RARE_DATA_X,RARE_DATA_Y,MSG_NO_PUT,col,NULL);
	dfp->put_req=1;
}

static	void	DebugFightLevelPut(DEBUG_FIGHT_PARAM *dfp)
{
	MSGMAN_GetString(dfp->man_msg,DF_LEVEL,dfp->msg_buf);
	GF_STR_PrintSimple(dfp->win_s,FONT_SYSTEM,dfp->msg_buf,MENU1_LIST_L_X,MENU1_LIST_Y+MENU1_LIST_OFS*1,MSG_NO_PUT,NULL);
	dfp->put_req=1;
}

static	void	DebugFightLevelDataPut(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp,int mode)
{
	GF_BGL_BmpWinFill(dfp->win_s,0x0f,LEVEL_DATA_X,LEVEL_DATA_Y,12*LEVEL_KETA,16);
	DebugFightNumPut(dfp,LEVEL_DATA_X,LEVEL_DATA_Y,dpp->level,LEVEL_KETA,dfp->cur_pos_keta,mode);
}

static	void	DebugFightExpPut(DEBUG_FIGHT_PARAM *dfp)
{
	MSGMAN_GetString(dfp->man_msg,DF_EXP,dfp->msg_buf);
	GF_STR_PrintSimple(dfp->win_s,FONT_SYSTEM,dfp->msg_buf,EXP_LIST_X,MENU1_LIST_Y+MENU1_LIST_OFS*1,MSG_NO_PUT,NULL);
	dfp->put_req=1;
}

static	void	DebugFightExpDataPut(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp,int mode)
{
	GF_BGL_BmpWinFill(dfp->win_s,0x0f,EXP_DATA_X,EXP_DATA_Y,12*EXP_KETA,16);
	DebugFightNumPut(dfp,EXP_DATA_X,EXP_DATA_Y,dpp->exp,EXP_KETA,dfp->cur_pos_keta,mode);
}

static	void	DebugFightSexPut(DEBUG_FIGHT_PARAM *dfp)
{
	MSGMAN_GetString(dfp->man_msg,DF_SEX,dfp->msg_buf);
	GF_STR_PrintSimple(dfp->win_s,FONT_SYSTEM,dfp->msg_buf,MENU1_LIST_L_X,MENU1_LIST_Y+MENU1_LIST_OFS*2,MSG_NO_PUT,NULL);
	dfp->put_req=1;
}

static	void	DebugFightSexDataPut(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp,GF_PRINTCOLOR col)
{
	GF_BGL_BmpWinFill(dfp->win_s,0x0f,SEX_DATA_X,SEX_DATA_Y,12*3,16);
	MSGMAN_GetString(dfp->man_msg,DF_MALE+dpp->sex,dfp->msg_buf);
	GF_STR_PrintColor(dfp->win_s,FONT_SYSTEM,dfp->msg_buf,SEX_DATA_X,SEX_DATA_Y,MSG_NO_PUT,col,NULL);
	dfp->put_req=1;
}

static	void	DebugFightChrPut(DEBUG_FIGHT_PARAM *dfp)
{
	MSGMAN_GetString(dfp->man_msg,DF_CHR,dfp->msg_buf);
	GF_STR_PrintSimple(dfp->win_s,FONT_SYSTEM,dfp->msg_buf,CHR_LIST_X,MENU1_LIST_Y+MENU1_LIST_OFS*2,MSG_NO_PUT,NULL);
	dfp->put_req=1;
}

static	void	DebugFightChrDataPut(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp,GF_PRINTCOLOR col)
{
	GF_BGL_BmpWinFill(dfp->win_s,0x0f,CHR_DATA_X,CHR_DATA_Y,12*5,16);
	MSGMAN_GetString(dfp->man_chr,dpp->chr,dfp->msg_buf);
	GF_STR_PrintColor(dfp->win_s,FONT_SYSTEM,dfp->msg_buf,CHR_DATA_X,CHR_DATA_Y,MSG_NO_PUT,col,NULL);
	dfp->put_req=1;
}

static	void	DebugFightHPRndPut(DEBUG_FIGHT_PARAM *dfp)
{
	MSGMAN_GetString(dfp->man_msg,DF_HPRND,dfp->msg_buf);
	GF_STR_PrintSimple(dfp->win_s,FONT_SYSTEM,dfp->msg_buf,MENU1_LIST_L_X,MENU1_LIST_Y+MENU1_LIST_OFS*3,MSG_NO_PUT,NULL);
	dfp->put_req=1;
}

static	void	DebugFightHPExpPut(DEBUG_FIGHT_PARAM *dfp)
{
	MSGMAN_GetString(dfp->man_msg,DF_HPEXP,dfp->msg_buf);
	GF_STR_PrintSimple(dfp->win_s,FONT_SYSTEM,dfp->msg_buf,MENU1_LIST_R_X,MENU1_LIST_Y+MENU1_LIST_OFS*3,MSG_NO_PUT,NULL);
	dfp->put_req=1;
}

static	void	DebugFightPowRndPut(DEBUG_FIGHT_PARAM *dfp)
{
	MSGMAN_GetString(dfp->man_msg,DF_POWRND,dfp->msg_buf);
	GF_STR_PrintSimple(dfp->win_s,FONT_SYSTEM,dfp->msg_buf,MENU1_LIST_L_X,MENU1_LIST_Y+MENU1_LIST_OFS*4,MSG_NO_PUT,NULL);
	dfp->put_req=1;
}

static	void	DebugFightPowExpPut(DEBUG_FIGHT_PARAM *dfp)
{
	MSGMAN_GetString(dfp->man_msg,DF_POWEXP,dfp->msg_buf);
	GF_STR_PrintSimple(dfp->win_s,FONT_SYSTEM,dfp->msg_buf,MENU1_LIST_R_X,MENU1_LIST_Y+MENU1_LIST_OFS*4,MSG_NO_PUT,NULL);
	dfp->put_req=1;
}

static	void	DebugFightDefRndPut(DEBUG_FIGHT_PARAM *dfp)
{
	MSGMAN_GetString(dfp->man_msg,DF_DEFRND,dfp->msg_buf);
	GF_STR_PrintSimple(dfp->win_s,FONT_SYSTEM,dfp->msg_buf,MENU1_LIST_L_X,MENU1_LIST_Y+MENU1_LIST_OFS*5,MSG_NO_PUT,NULL);
	dfp->put_req=1;
}

static	void	DebugFightDefExpPut(DEBUG_FIGHT_PARAM *dfp)
{
	MSGMAN_GetString(dfp->man_msg,DF_DEFEXP,dfp->msg_buf);
	GF_STR_PrintSimple(dfp->win_s,FONT_SYSTEM,dfp->msg_buf,MENU1_LIST_R_X,MENU1_LIST_Y+MENU1_LIST_OFS*5,MSG_NO_PUT,NULL);
	dfp->put_req=1;
}

static	void	DebugFightAgiRndPut(DEBUG_FIGHT_PARAM *dfp)
{
	MSGMAN_GetString(dfp->man_msg,DF_AGIRND,dfp->msg_buf);
	GF_STR_PrintSimple(dfp->win_s,FONT_SYSTEM,dfp->msg_buf,MENU1_LIST_L_X,MENU1_LIST_Y+MENU1_LIST_OFS*6,MSG_NO_PUT,NULL);
	dfp->put_req=1;
}

static	void	DebugFightAgiExpPut(DEBUG_FIGHT_PARAM *dfp)
{
	MSGMAN_GetString(dfp->man_msg,DF_AGIEXP,dfp->msg_buf);
	GF_STR_PrintSimple(dfp->win_s,FONT_SYSTEM,dfp->msg_buf,MENU1_LIST_R_X,MENU1_LIST_Y+MENU1_LIST_OFS*6,MSG_NO_PUT,NULL);
	dfp->put_req=1;
}

static	void	DebugFightSpePowRndPut(DEBUG_FIGHT_PARAM *dfp)
{
	MSGMAN_GetString(dfp->man_msg,DF_SPEPOWRND,dfp->msg_buf);
	GF_STR_PrintSimple(dfp->win_s,FONT_SYSTEM,dfp->msg_buf,MENU1_LIST_L_X,MENU1_LIST_Y+MENU1_LIST_OFS*7,MSG_NO_PUT,NULL);
	dfp->put_req=1;
}

static	void	DebugFightSpePowExpPut(DEBUG_FIGHT_PARAM *dfp)
{
	MSGMAN_GetString(dfp->man_msg,DF_SPEPOWEXP,dfp->msg_buf);
	GF_STR_PrintSimple(dfp->win_s,FONT_SYSTEM,dfp->msg_buf,MENU1_LIST_R_X,MENU1_LIST_Y+MENU1_LIST_OFS*7,MSG_NO_PUT,NULL);
	dfp->put_req=1;
}

static	void	DebugFightSpeDefRndPut(DEBUG_FIGHT_PARAM *dfp)
{
	MSGMAN_GetString(dfp->man_msg,DF_SPEDEFRND,dfp->msg_buf);
	GF_STR_PrintSimple(dfp->win_s,FONT_SYSTEM,dfp->msg_buf,MENU1_LIST_L_X,MENU1_LIST_Y+MENU1_LIST_OFS*8,MSG_NO_PUT,NULL);
	dfp->put_req=1;
}

static	void	DebugFightSpeDefExpPut(DEBUG_FIGHT_PARAM *dfp)
{
	MSGMAN_GetString(dfp->man_msg,DF_SPEDEFEXP,dfp->msg_buf);
	GF_STR_PrintSimple(dfp->win_s,FONT_SYSTEM,dfp->msg_buf,MENU1_LIST_R_X,MENU1_LIST_Y+MENU1_LIST_OFS*8,MSG_NO_PUT,NULL);
	dfp->put_req=1;
}

static	void	DebugFightStatusRndDataPut(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp,int status,int mode)
{
	GF_BGL_BmpWinFill(dfp->win_s,0x0f,STRND_DATA_X,STRND_DATA_Y+STRND_DATA_OFS*status,12*STRND_KETA,16);
	DebugFightNumPut(dfp,STRND_DATA_X,STRND_DATA_Y+STRND_DATA_OFS*status,dpp->status_rnd[status],
					STRND_KETA,dfp->cur_pos_keta,mode);
}

static	void	DebugFightStatusExpDataPut(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp,int status,int mode)
{
	GF_BGL_BmpWinFill(dfp->win_s,0x0f,STEXP_DATA_X,STEXP_DATA_Y+STEXP_DATA_OFS*status,12*STEXP_KETA,16);
	DebugFightNumPut(dfp,STEXP_DATA_X,STEXP_DATA_Y+STEXP_DATA_OFS*status,dpp->status_exp[status],
					STEXP_KETA,dfp->cur_pos_keta,mode);
}

static	void	DebugFightParamPut(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp)
{
	int	i;
	int	col;
	MSGDATA_MANAGER *man;

	man=MSGMAN_Create(MSGMAN_TYPE_DIRECT,ARC_MSG,NARC_msg_typename_dat,HEAPID_DEBUG_APPLICATION);

	GF_BGL_BmpWinFill(dfp->win_s,0x0f,0,PARAM1_Y,256,32);

	for(i=COND_POW;i<COND_SPEDEF+1;i++){
		switch(PokeChrAbiTableGet(dpp->chr,i)){
		case 1:
			col=COL_PARA_UP;
			break;
		case 0:
			col=COL_NORMAL;
			break;
		case -1:
			col=COL_PARA_DOWN;
			break;
		}
		MSGMAN_GetString(dfp->man_msg,DF_PARAM_POW+(i-1),dfp->msg_buf);
		GF_STR_PrintColor(dfp->win_s,FONT_SYSTEM,dfp->msg_buf,PARAM_POW_X+(i-1)*PARAM_OFS_X,PARAM1_Y,MSG_NO_PUT,col,NULL);
	}
	for(i=0;i<3;i++){
		MSGMAN_GetString(dfp->man_msg,DF_PARAM_HP+i,dfp->msg_buf);
		GF_STR_PrintSimple(dfp->win_s,FONT_SYSTEM,dfp->msg_buf,PARAM_POW_X+i*PARAM_OFS_X,PARAM2_Y,MSG_NO_PUT,NULL);
	}

	if(dpp->mons_no){
		{
			u32		hp_max;
			int		mpp;
			int		mpt;
			int		data;
			u32		rnd;
			BOOL	flag;

			flag=PokeParaFastModeOn(dfp->pp);

			PokeParaPut(dfp->pp,ID_PARA_monsno,&dpp->mons_no);
			PokeParaPut(dfp->pp,ID_PARA_level,&dpp->level);
			PokeParaPut(dfp->pp,ID_PARA_exp,&dpp->exp);
			rnd=PokeParaSexChrRndGet(dpp->mons_no,
									 dpp->sex,
									 dpp->chr);
			PokeParaPut(dfp->pp,ID_PARA_personal_rnd,&rnd);

			for(i=STATUS_HP;i<STATUS_MAX;i++){
				PokeParaPut(dfp->pp,ID_PARA_hp_rnd+i,&dpp->status_rnd[i]);
				PokeParaPut(dfp->pp,ID_PARA_hp_exp+i,&dpp->status_exp[i]);
			}
			mpp=	((dpp->status_rnd[0]&2)>>1)|
					((dpp->status_rnd[1]&2)>>0)|
					((dpp->status_rnd[2]&2)<<1)|
					((dpp->status_rnd[3]&2)<<2)|
					((dpp->status_rnd[4]&2)<<3)|
					((dpp->status_rnd[5]&2)<<4);
			mpt=	((dpp->status_rnd[0]&1)>>0)|
					((dpp->status_rnd[1]&1)<<1)|
					((dpp->status_rnd[2]&1)<<2)|
					((dpp->status_rnd[3]&1)<<3)|
					((dpp->status_rnd[4]&1)<<4)|
					((dpp->status_rnd[5]&1)<<5);

			mpp=mpp*40/63+30;
			mpt=(mpt*15/63)+1;

			if(mpt>=HATE_TYPE){
				mpt++;
			}
			PokeParaCalc(dfp->pp);
			hp_max=PokeParaGet(dfp->pp,ID_PARA_hpmax,NULL);

			for(i=COND_POW;i<COND_SPEDEF+1;i++){
				switch(PokeChrAbiTableGet(dpp->chr,i)){
				case 1:
					col=COL_PARA_UP;
					break;
				case 0:
					col=COL_NORMAL;
					break;
				case -1:
					col=COL_PARA_DOWN;
					break;
				}
				data=PokeParaGet(dfp->pp,ID_PARA_pow+(i-1),NULL);
				STRBUF_SetNumber(dfp->msg_buf,data,3,NUMBER_DISPTYPE_ZERO,NUMBER_CODETYPE_DEFAULT);
				GF_STR_PrintColor(dfp->win_s,FONT_SYSTEM,dfp->msg_buf,PARAM_POW_NUM_X+(i-1)*PARAM_OFS_X,PARAM1_Y,MSG_NO_PUT,col,NULL);
			}
			STRBUF_SetNumber(dfp->msg_buf,hp_max,3,NUMBER_DISPTYPE_ZERO,NUMBER_CODETYPE_DEFAULT);
			GF_STR_PrintSimple(dfp->win_s,FONT_SYSTEM,dfp->msg_buf,PARAM_POW_NUM_X+0*PARAM_OFS_X,PARAM2_Y,MSG_NO_PUT,NULL);
			STRBUF_SetNumber(dfp->msg_buf,mpp,3,NUMBER_DISPTYPE_ZERO,NUMBER_CODETYPE_DEFAULT);
			GF_STR_PrintSimple(dfp->win_s,FONT_SYSTEM,dfp->msg_buf,PARAM_POW_NUM_X+1*PARAM_OFS_X,PARAM2_Y,MSG_NO_PUT,NULL);
			MSGMAN_GetString(man,mpt,dfp->msg_buf);
			GF_STR_PrintSimple(dfp->win_s,FONT_SYSTEM,dfp->msg_buf,PARAM_POW_NUM_X+2*PARAM_OFS_X,PARAM2_Y,MSG_NO_PUT,NULL);
			if((hp_max<dpp->default_hp)||(dpp->hp_max==dpp->default_hp)){
				dpp->default_hp=hp_max;
			}
			dpp->hp_max=hp_max;
			dfp->put_req=1;
			PokeParaFastModeOff(dfp->pp,flag);
		}
	}
	else{
		for(i=COND_POW;i<COND_SPEDEF+1;i++){
			STRBUF_SetNumber(dfp->msg_buf,0,3,NUMBER_DISPTYPE_ZERO,NUMBER_CODETYPE_DEFAULT);
			GF_STR_PrintSimple(dfp->win_s,FONT_SYSTEM,dfp->msg_buf,PARAM_POW_NUM_X+(i-1)*PARAM_OFS_X,PARAM1_Y,MSG_NO_PUT,NULL);
		}
		STRBUF_SetNumber(dfp->msg_buf,0,3,NUMBER_DISPTYPE_ZERO,NUMBER_CODETYPE_DEFAULT);
		GF_STR_PrintSimple(dfp->win_s,FONT_SYSTEM,dfp->msg_buf,PARAM_POW_NUM_X+0*PARAM_OFS_X,PARAM2_Y,MSG_NO_PUT,NULL);
		STRBUF_SetNumber(dfp->msg_buf,0,3,NUMBER_DISPTYPE_ZERO,NUMBER_CODETYPE_DEFAULT);
		GF_STR_PrintSimple(dfp->win_s,FONT_SYSTEM,dfp->msg_buf,PARAM_POW_NUM_X+1*PARAM_OFS_X,PARAM2_Y,MSG_NO_PUT,NULL);
		MSGMAN_GetString(man,0,dfp->msg_buf);
		GF_STR_PrintSimple(dfp->win_s,FONT_SYSTEM,dfp->msg_buf,PARAM_POW_NUM_X+2*PARAM_OFS_X,PARAM2_Y,MSG_NO_PUT,NULL);
		dfp->put_req=1;
	}

	//メッセージマネージャ関連削除
	MSGMAN_Delete(man);
}

static	void	DebugFightDefaultSet(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp,int mode)
{
	int				i;

	PokeParaSetSexChr(dfp->pp,
					  dpp->mons_no,
					  dpp->level,
					  POW_RND,
					  dpp->sex,
					  dpp->chr,
					  0);
	switch(mode){
	case MODE_DEFAULT_PARAM:
		for(i=STATUS_HP;i<STATUS_MAX;i++){
			dpp->status_rnd[i]=PokeParaGet(dfp->pp,ID_PARA_hp_rnd+i,NULL);
		}
		break;
	case MODE_DEFAULT_WAZA:
		for(i=0;i<4;i++){
			dpp->waza[i]=PokeParaGet(dfp->pp,ID_PARA_waza1+i,NULL);
			dpp->pp[i]=WT_PPMaxGet(dpp->waza[i],dpp->pp_count[i]);
		}
		break;
	default:
		break;
	}
}

static	void	DebugFightWazaPut(DEBUG_FIGHT_PARAM *dfp,int pos)
{
	MSGMAN_GetString(dfp->man_msg,DF_WAZA1+pos,dfp->msg_buf);
	GF_STR_PrintSimple(dfp->win_s,FONT_SYSTEM,dfp->msg_buf,MENU2_LIST_X,MENU2_LIST_Y+MENU2_LIST_OFS*pos,MSG_NO_PUT,NULL);
	dfp->put_req=1;
}

static	void	DebugFightWazaDataPut(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp,int pos,int mode)
{
	int	ppmax;

	GF_BGL_BmpWinFill(dfp->win_s,0x0f,WAZA_NUM_X,WAZA_NUM_Y+WAZA_NUM_OFS*pos,128,16);

	//技ナンバー
	DebugFightNumPut(dfp,WAZA_NUM_X,WAZA_NUM_Y+WAZA_NUM_OFS*pos,dpp->waza[pos],3,dfp->cur_pos_keta,mode);

	//技名
	MSGMAN_GetString(dfp->man_waza,dpp->waza[pos],dfp->msg_buf);
	GF_STR_PrintSimple(dfp->win_s,FONT_SYSTEM,dfp->msg_buf,WAZA_DATA_X,WAZA_DATA_Y+WAZA_DATA_OFS*pos,MSG_NO_PUT,NULL);

	dfp->put_req=1;
}

static	void	DebugFightPPDataPut(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp,int pos,int mode)
{
	int	ppmax;

	GF_BGL_BmpWinFill(dfp->win_s,0x0f,PP_X,PP_Y+WAZA_NUM_OFS*pos,40,16);

	//PP
	DebugFightNumPut(dfp,PP_X,PP_Y+WAZA_NUM_OFS*pos,dpp->pp[pos],2,dfp->cur_pos_keta,mode);

	ppmax=WT_PPMaxGet(dpp->waza[pos],dpp->pp_count[pos]);

	//PPMAX
	DebugFightNumPut(dfp,PP_X+12*2,PP_Y+WAZA_NUM_OFS*pos,ppmax,2,NULL,MODE_NORMAL);
}

static	void	DebugFightPPCountDataPut(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp,int pos,int mode)
{
	GF_BGL_BmpWinFill(dfp->win_s,0x0f,PP_COUNT_X,PP_COUNT_Y+WAZA_NUM_OFS*pos,16,16);

	//PP_COUNT
	DebugFightNumPut(dfp,PP_COUNT_X,PP_COUNT_Y+WAZA_NUM_OFS*pos,dpp->pp_count[pos],1,dfp->cur_pos_keta,mode);
}


static	void	DebugFightSpeAbiPut(DEBUG_FIGHT_PARAM *dfp)
{
	MSGMAN_GetString(dfp->man_msg,DF_SPEABI,dfp->msg_buf);
	GF_STR_PrintSimple(dfp->win_s,FONT_SYSTEM,dfp->msg_buf,MENU2_LIST_X,SPEABI_DATA_Y,MSG_NO_PUT,NULL);
	dfp->put_req=1;
}

static	void	DebugFightSpeAbiDataPut(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp,GF_PRINTCOLOR col)
{
	GF_BGL_BmpWinFill(dfp->win_s,0x0f,SPEABI_DATA_X,SPEABI_DATA_Y,12*7,16);

	if(dpp->speabi){
		dpp->speabino=PokePersonalParaGet(dpp->mons_no,ID_PER_speabi2);
	}
	else{
		dpp->speabino=PokePersonalParaGet(dpp->mons_no,ID_PER_speabi1);
	}

	MSGMAN_GetString(dfp->man_speabi,dpp->speabino,dfp->msg_buf);
	GF_STR_PrintColor(dfp->win_s,FONT_SYSTEM,dfp->msg_buf,SPEABI_DATA_X,SPEABI_DATA_Y,MSG_NO_PUT,col,NULL);
	dfp->put_req=1;
}

static	void	DebugFightSpeAbiSetPut(DEBUG_FIGHT_PARAM *dfp)
{
	MSGMAN_GetString(dfp->man_msg,DF_SPEABI_SET,dfp->msg_buf);
	GF_STR_PrintSimple(dfp->win_s,FONT_SYSTEM,dfp->msg_buf,MENU2_LIST_X,SPEABI_SET_DATA_Y,MSG_NO_PUT,NULL);
	dfp->put_req=1;
}

static	void	DebugFightSpeAbiSetDataPut(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp,int mode)
{
	GF_BGL_BmpWinFill(dfp->win_s,0x0f,SPEABI_DATA_X,SPEABI_SET_DATA_Y,12*11,16);

	DebugFightNumPut(dfp,SPEABI_SET_NUM_X,SPEABI_SET_NUM_Y,dpp->speabino_set,3,dfp->cur_pos_keta,mode);

	MSGMAN_GetString(dfp->man_speabi,dpp->speabino_set,dfp->msg_buf);
	GF_STR_PrintSimple(dfp->win_s,FONT_SYSTEM,dfp->msg_buf,SPEABI_SET_DATA_X,SPEABI_SET_DATA_Y,MSG_NO_PUT,NULL);
	dfp->put_req=1;
}

static	void	DebugFightItemPut(DEBUG_FIGHT_PARAM *dfp)
{
	MSGMAN_GetString(dfp->man_msg,DF_ITEM,dfp->msg_buf);
	GF_STR_PrintSimple(dfp->win_s,FONT_SYSTEM,dfp->msg_buf,MENU2_LIST_X,ITEM_DATA_Y,MSG_NO_PUT,NULL);
	dfp->put_req=1;
}

static	void	DebugFightItemDataPut(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp,int mode)
{
	GF_BGL_BmpWinFill(dfp->win_s,0x0f,ITEM_NUM_X,ITEM_NUM_Y,256-ITEM_NUM_X,16);

	DebugFightNumPut(dfp,ITEM_NUM_X,ITEM_NUM_Y,dpp->item,3,dfp->cur_pos_keta,mode);

	MSGMAN_GetString(dfp->man_item,dpp->item,dfp->msg_buf);
	GF_STR_PrintSimple(dfp->win_s,FONT_SYSTEM,dfp->msg_buf,ITEM_DATA_X,ITEM_DATA_Y,MSG_NO_PUT,NULL);
	dfp->put_req=1;
}

static	void	DebugFightFriendPut(DEBUG_FIGHT_PARAM *dfp)
{
	MSGMAN_GetString(dfp->man_msg,DF_FRIEND,dfp->msg_buf);
	GF_STR_PrintSimple(dfp->win_s,FONT_SYSTEM,dfp->msg_buf,MENU2_LIST_X,FRIEND_DATA_Y,MSG_NO_PUT,NULL);
	dfp->put_req=1;
}

static	void	DebugFightFriendDataPut(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp,int mode)
{
	GF_BGL_BmpWinFill(dfp->win_s,0x0f,FRIEND_DATA_X,FRIEND_DATA_Y,12*3,16);
	DebugFightNumPut(dfp,FRIEND_DATA_X,FRIEND_DATA_Y,dpp->friend,3,dfp->cur_pos_keta,mode);
}

static	void	DebugFightConditionPut(DEBUG_FIGHT_PARAM *dfp)
{
	MSGMAN_GetString(dfp->man_msg,DF_CONDITION,dfp->msg_buf);
	GF_STR_PrintSimple(dfp->win_s,FONT_SYSTEM,dfp->msg_buf,MENU2_LIST_X,CONDITION_DATA_Y,MSG_NO_PUT,NULL);
	dfp->put_req=1;
}

static	void	DebugFightConditionDataPut(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp,GF_PRINTCOLOR col)
{
	GF_BGL_BmpWinFill(dfp->win_s,0x0f,CONDITION_DATA_X,CONDITION_DATA_Y,256-CONDITION_DATA_X,16);
	MSGMAN_GetString(dfp->man_msg,DF_COND_NORMAL+dpp->condition,dfp->msg_buf);
	GF_STR_PrintColor(dfp->win_s,FONT_SYSTEM,dfp->msg_buf,CONDITION_DATA_X,CONDITION_DATA_Y,MSG_NO_PUT,col,NULL);
	dfp->put_req=1;
}

static	void	DebugFightDefaultHPPut(DEBUG_FIGHT_PARAM *dfp)
{
	MSGMAN_GetString(dfp->man_msg,DF_DEFAULT_HP,dfp->msg_buf);
	GF_STR_PrintSimple(dfp->win_s,FONT_SYSTEM,dfp->msg_buf,MENU2_LIST_X,DEFAULT_HP_DATA_Y,MSG_NO_PUT,NULL);
	dfp->put_req=1;
}

static	void	DebugFightDefaultHPDataPut(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp,int mode)
{
	GF_BGL_BmpWinFill(dfp->win_s,0x0f,DEFAULT_HP_DATA_X,DEFAULT_HP_DATA_Y,256-DEFAULT_HP_DATA_X,16);
	DebugFightNumPut(dfp,DEFAULT_HP_DATA_X,DEFAULT_HP_DATA_Y,dpp->default_hp,3,dfp->cur_pos_keta,mode);
	DebugFightNumPut(dfp,DEFAULT_HP_DATA_X+12*3,DEFAULT_HP_DATA_Y,dpp->hp_max,3,NULL,MODE_NORMAL);
}

static	void	DebugFightGetBallPut(DEBUG_FIGHT_PARAM *dfp)
{
	MSGMAN_GetString(dfp->man_msg,DF_GETBALL,dfp->msg_buf);
	GF_STR_PrintSimple(dfp->win_s,FONT_SYSTEM,dfp->msg_buf,MENU2_LIST_X,GETBALL_DATA_Y,MSG_NO_PUT,NULL);
	dfp->put_req=1;
}

static	void	DebugFightGetBallDataPut(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp,GF_PRINTCOLOR col)
{
	GF_BGL_BmpWinFill(dfp->win_s,0x0f,GETBALL_DATA_X,GETBALL_DATA_Y,256-GETBALL_DATA_X,16);
	MSGMAN_GetString(dfp->man_item,dpp->get_ball,dfp->msg_buf);
	GF_STR_PrintColor(dfp->win_s,FONT_SYSTEM,dfp->msg_buf,GETBALL_DATA_X,GETBALL_DATA_Y,MSG_NO_PUT,col,NULL);
	dfp->put_req=1;
}

static	void	DebugFightFormNoPut(DEBUG_FIGHT_PARAM *dfp)
{
	MSGMAN_GetString(dfp->man_msg,DF_FORMNO,dfp->msg_buf);
	GF_STR_PrintSimple(dfp->win_s,FONT_SYSTEM,dfp->msg_buf,FORMNO_X,FORMNO_Y,MSG_NO_PUT,NULL);
	dfp->put_req=1;
}

static	void	DebugFightFormNoDataPut(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp,int max,int mode)
{
	GF_BGL_BmpWinFill(dfp->win_s,0x0f,FORMNO_DATA_X,FORMNO_DATA_Y,12*6,16);
	DebugFightNumPut(dfp,FORMNO_DATA_X,FORMNO_DATA_Y,dpp->form_no,3,dfp->cur_pos_keta,mode);
	DebugFightNumPut(dfp,FORMNO_DATA_X+12*3,FORMNO_DATA_Y,max,3,NULL,MODE_NORMAL);
}

static	void	DebugFightEggFlagDataPut(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp)
{
	GF_BGL_BmpWinFill(dfp->win_s,0x0f,EGG_FLAG_DATA_X,EGG_FLAG_DATA_Y,12*9,16);

	MSGMAN_GetString(dfp->man_msg,DF_EGG_OFF+dpp->egg_flag,dfp->msg_buf);
	GF_STR_PrintSimple(dfp->win_s,FONT_SYSTEM,dfp->msg_buf,EGG_FLAG_DATA_X,EGG_FLAG_DATA_Y,MSG_NO_PUT,NULL);
	dfp->put_req=1;
}

static	void	DebugFightTrainerIDPut(DEBUG_FIGHT_PARAM *dfp)
{
	MSGMAN_GetString(dfp->man_msg,DF_TRAINER_ID,dfp->msg_buf);
	GF_STR_PrintSimple(dfp->win_m,FONT_SYSTEM,dfp->msg_buf,TRAINER_ID_X,TRAINER_ID_Y,MSG_NO_PUT,NULL);
	dfp->put_req=1;
}

static	void	DebugFightTrainerIDDataPut(DEBUG_FIGHT_PARAM *dfp)
{
	int	trtype;

	GF_BGL_BmpWinFill(dfp->win_m,0x0f,TRAINER_ID_DATA_X,TRAINER_ID_DATA_Y,256-TRAINER_ID_DATA_X,16);
	STRBUF_SetNumber(dfp->msg_buf,dfp->trainer_id,3,NUMBER_DISPTYPE_ZERO,NUMBER_CODETYPE_DEFAULT);
	GF_STR_PrintColor(dfp->win_m,FONT_SYSTEM,dfp->msg_buf,TRAINER_ID_DATA_X,TRAINER_ID_DATA_Y,MSG_NO_PUT,COL_NORMAL,NULL);

	if(dfp->trainer_id){
		{
			MSGDATA_MANAGER	*man;

			man=MSGMAN_Create(MSGMAN_TYPE_DIRECT,ARC_MSG,NARC_msg_trtype_dat,HEAPID_DEBUG_APPLICATION);

			trtype=TT_TrainerDataParaGet(dfp->trainer_id,ID_TD_tr_type);
			MSGMAN_GetString(man,trtype,dfp->msg_buf);
			GF_STR_PrintSimple(dfp->win_m,FONT_SYSTEM,dfp->msg_buf,TRAINER_ID_DATA_X+12*2,TRAINER_ID_DATA_Y,MSG_NO_PUT,NULL);
			MSGMAN_Delete(man);

			man=MSGMAN_Create(MSGMAN_TYPE_DIRECT,ARC_MSG,NARC_msg_trname_dat,HEAPID_DEBUG_APPLICATION);
			MSGMAN_GetString(man,dfp->trainer_id,dfp->msg_buf);
			GF_STR_PrintSimple(dfp->win_m,FONT_SYSTEM,dfp->msg_buf,TRAINER_ID_DATA_X+12*11,TRAINER_ID_DATA_Y,MSG_NO_PUT,NULL);
			MSGMAN_Delete(man);
		}
	}

	dfp->put_req=1;
}

static	void	DebugFightBT_TrainerIDPut(DEBUG_FIGHT_PARAM *dfp)
{
	MSGMAN_GetString(dfp->man_msg,DF_BT_TRAINER_ID,dfp->msg_buf);
	GF_STR_PrintSimple(dfp->win_m,FONT_SYSTEM,dfp->msg_buf,BT_TRAINER_ID_X,BT_TRAINER_ID_Y,MSG_NO_PUT,NULL);
	dfp->put_req=1;
}

static	void	DebugFightBT_TrainerIDDataPut(DEBUG_FIGHT_PARAM *dfp)
{

	GF_BGL_BmpWinFill(dfp->win_m,0x0f,BT_TRAINER_ID_DATA_X,BT_TRAINER_ID_DATA_Y,256-BT_TRAINER_ID_DATA_X,16);
	STRBUF_SetNumber(dfp->msg_buf,dfp->bt_trainer_id,3,NUMBER_DISPTYPE_ZERO,NUMBER_CODETYPE_DEFAULT);
	GF_STR_PrintColor(dfp->win_m,FONT_SYSTEM,dfp->msg_buf,BT_TRAINER_ID_DATA_X,BT_TRAINER_ID_DATA_Y,MSG_NO_PUT,COL_NORMAL,NULL);

	if(dfp->bt_trainer_id){
		{
			B_TOWER_TRAINER_ROM_DATA	*trd;
			MSGDATA_MANAGER	*man;

			trd=ArchiveDataLoadMalloc(ARC_BTD_TR,dfp->bt_trainer_id-1,HEAPID_DEBUG_APPLICATION);

			man=MSGMAN_Create(MSGMAN_TYPE_DIRECT,ARC_MSG,NARC_msg_trtype_dat,HEAPID_DEBUG_APPLICATION);

			MSGMAN_GetString(man,trd->tr_type,dfp->msg_buf);
			GF_STR_PrintSimple(dfp->win_m,FONT_SYSTEM,dfp->msg_buf,BT_TRAINER_ID_DATA_X+12*2,BT_TRAINER_ID_DATA_Y,MSG_NO_PUT,NULL);
			MSGMAN_Delete(man);

			man=MSGMAN_Create(MSGMAN_TYPE_DIRECT,ARC_MSG,NARC_msg_btdtrname_dat,HEAPID_DEBUG_APPLICATION);
			MSGMAN_GetString(man,dfp->bt_trainer_id-1,dfp->msg_buf);
			GF_STR_PrintSimple(dfp->win_m,FONT_SYSTEM,dfp->msg_buf,BT_TRAINER_ID_DATA_X+12*11,BT_TRAINER_ID_DATA_Y,MSG_NO_PUT,NULL);
			MSGMAN_Delete(man);

			sys_FreeMemoryEz(trd);
		}
	}

	dfp->put_req=1;
}

static	void	DebugFightNumPut(DEBUG_FIGHT_PARAM *dfp,int x,int y,int param,int keta,int pos,int mode)
{
	int		i;
	int		data,ofs;
	int		keta_tbl[10]={
		1000000000,
		100000000,
		10000000,
		1000000,
		100000,
		10000,
		1000,
		100,
		10,
		1,
	};

	ofs=0;
	for(i=0;i<keta;i++){
		data=param/keta_tbl[10-keta+i];
		param%=keta_tbl[10-keta+i];
		STRBUF_SetNumber(dfp->msg_buf,data,1,NUMBER_DISPTYPE_ZERO,NUMBER_CODETYPE_DEFAULT);
		if(mode==MODE_NORMAL){
			GF_STR_PrintColor(dfp->win_s,FONT_SYSTEM,dfp->msg_buf,x+ofs,y,MSG_NO_PUT,COL_NORMAL,NULL);
		}
		else{
			if((keta-1)-i==pos){
				GF_STR_PrintColor(dfp->win_s,FONT_SYSTEM,dfp->msg_buf,x+ofs,y,MSG_NO_PUT,COL_CURSOR,NULL);
			}
			else{
				GF_STR_PrintColor(dfp->win_s,FONT_SYSTEM,dfp->msg_buf,x+ofs,y,MSG_NO_PUT,COL_ACTIVE,NULL);
			}
		}
		ofs+=FontProc_GetPrintStrWidth(FONT_SYSTEM,dfp->msg_buf,0);
	}
	dfp->put_req=1;
}

//============================================================================================
/**
 *	戦闘開始
 */
//============================================================================================
static	u8	TrainerSexTable[]={
	PARA_MALE,
	PARA_FEMALE,
	PARA_MALE,
	PARA_FEMALE,
	PARA_MALE,
	PARA_FEMALE,
	PARA_MALE,
	PARA_FEMALE,
};

static	u8	TrTypeTable[]={
	TRTYPE_BOY,
	TRTYPE_GIRL,
	TRTYPE_RIVAL,
	TRTYPE_BTFIVE1,
	TRTYPE_BTFIVE2,
	TRTYPE_BTFIVE3,
	TRTYPE_BTFIVE4,
	TRTYPE_BTFIVE5,
};

BOOL	DebugFightStart(DEBUG_FIGHT_PARAM *dfp)
{
	int			i,j;
	int			cnt;
	int			form_no;
	u32			rnd;
	STRCODE		name[PERSON_NAME_SIZE+EOM_SIZE];

	cnt=0;
	for(i=0;i<6;i++){
		if((dfp->dsp.dpp[i].mons_no)&&(dfp->dsp.dpp[i].default_hp)){
			if(cnt&1){
				cnt|=4;
			}
			else{
				cnt|=1;
			}
		}
		if((dfp->dsp.dpp[i+6].mons_no)&&(dfp->dsp.dpp[i+6].default_hp)){
			if(cnt&2){
				cnt|=8;
			}
			else{
				cnt|=2;
			}
		}
	}
	if((cnt&fight_type_table[dfp->dsp.fight_type][1])!=fight_type_table[dfp->dsp.fight_type][1]){
		return FALSE;
	}
	dfp->param=BattleParam_Create(HEAPID_DEBUG_APPLICATION,fight_type_table[dfp->dsp.fight_type][0]);
	CONFIG_SetBattleRule(dfp->param->config,dfp->dsp.rule);
	CONFIG_SetWazaEffectMode(dfp->param->config,dfp->dsp.effect_flag);
	CONFIG_SetMsgSpeed(dfp->param->config,dfp->dsp.msg_speed);
	MSGMAN_GetStr(dfp->man_msg,DF_BOY_NAME+dfp->dsp.my_sex,name);
	Debug_MyStatus_Make(dfp->param->my_status[CLIENT_NO_MINE],name,TrainerSexTable[dfp->dsp.my_sex]);
	Debug_MyItem_MakeBag(dfp->param->my_item,HEAPID_DEBUG_APPLICATION);
	dfp->param->bag_cursor=MyItem_BagCursorAlloc(HEAPID_DEBUG_APPLICATION);
	dfp->param->box=SaveData_GetBoxData(dfp->sv);
	dfp->param->record=SaveData_GetRecord(dfp->sv);
	dfp->param->wifihistory=SaveData_GetWifiHistory(dfp->sv);
	dfp->param->safari_ball=2;
	dfp->param->poketch_data=NULL;
	dfp->param->weather=weather_table[dfp->dsp.weather];
	dfp->param->trainer_id[CLIENT_NO_MINE]=0;
	dfp->param->trainer_id[CLIENT_NO_MINE2]=0;
	dfp->param->friendlist = SaveData_GetFriendList( dfp->sv );
	
	dfp->param->trainer_data[CLIENT_NO_MINE].tr_type=TrTypeTable[dfp->dsp.my_sex];
	PM_strcpy(&dfp->param->trainer_data[CLIENT_NO_MINE].name[0],&name[0]);
	i=gf_rand()%5+3;
	MSGMAN_GetStr(dfp->man_msg,DF_BOY_NAME+i,name);
	Debug_MyStatus_Make(dfp->param->my_status[CLIENT_NO_MINE2],name,TrainerSexTable[i]);
	dfp->param->trainer_data[CLIENT_NO_MINE2].tr_type=TrTypeTable[i];
	PM_strcpy(&dfp->param->trainer_data[CLIENT_NO_MINE2].name[0],&name[0]);

	for(i=0;i<CLIENT_MAX;i++){
		PokeParty_Init(dfp->param->poke_party[i],POKEMON_TEMOTI_MAX);
	}

	if(dfp->trainer_id){
		dfp->param->fight_type=FIGHT_TYPE_1vs1_TRAINER;
		dfp->param->trainer_id[CLIENT_NO_ENEMY]=dfp->trainer_id;
		TT_EncountTrainerDataMake(dfp->param,dfp->sv,HEAPID_DEBUG_APPLICATION);
	}
	else if(dfp->bt_trainer_id){
		{
			MSGDATA_MANAGER				*man;
			B_TOWER_TRAINER_ROM_DATA	*trd;
			STRBUF						*name;

			man=MSGMAN_Create(MSGMAN_TYPE_DIRECT,ARC_MSG,NARC_msg_btdtrname_dat,HEAPID_DEBUG_APPLICATION);
			trd=ArchiveDataLoadMalloc(ARC_BTD_TR,dfp->bt_trainer_id-1,HEAPID_DEBUG_APPLICATION);

			dfp->param->fight_type=FIGHT_TYPE_BATTLE_TOWER_1vs1;
			dfp->param->trainer_id[CLIENT_NO_ENEMY]=dfp->bt_trainer_id-1;
			dfp->param->trainer_data[CLIENT_NO_ENEMY].tr_type=trd->tr_type;
			name=MSGMAN_AllocString(man,dfp->bt_trainer_id-1);
			STRBUF_GetStringCode(name,&dfp->param->trainer_data[CLIENT_NO_ENEMY].name[0],BUFLEN_PERSON_NAME);
			STRBUF_Delete(name);
			sys_FreeMemoryEz(trd);
			MSGMAN_Delete(man);
		}
	}
	else{
		do{
			i=gf_rand()%843+1;
		}while(TT_TrainerDataParaGet(i,ID_TD_fight_type)&FIGHT_TYPE_2vs2);
		dfp->param->trainer_id[CLIENT_NO_ENEMY]=i;
		do{
			i=gf_rand()%843+1;
		}while(TT_TrainerDataParaGet(i,ID_TD_fight_type)&FIGHT_TYPE_2vs2);
		dfp->param->trainer_id[CLIENT_NO_ENEMY2]=i;
		TT_EncountTrainerDataMake(dfp->param,dfp->sv,HEAPID_DEBUG_APPLICATION);
		for(i=0;i<CLIENT_MAX;i++){
			PokeParty_Init(dfp->param->poke_party[i],POKEMON_TEMOTI_MAX);
		}
	}
	if(dfp->dsp.ai_bit){
		dfp->param->trainer_data[CLIENT_NO_ENEMY].aibit=dfp->dsp.ai_bit;
		dfp->param->trainer_data[CLIENT_NO_ENEMY2].aibit=dfp->dsp.ai_bit;
	}

	for(i=0;i<6;i++){
		if(dfp->dsp.dpp[i].mons_no){
#if 0
			PokeParaSetSexChr(dfp->pp,
							  dfp->dsp.dpp[i].mons_no,
							  dfp->dsp.dpp[i].level,
							  0,
							  dfp->dsp.dpp[i].sex,
							  dfp->dsp.dpp[i].chr,
							  0);
#endif
			rnd=PokeRndGet(dfp->dsp.dpp[i].mons_no,dfp->dsp.dpp[i].sex,dfp->dsp.dpp[i].chr,dfp->dsp.dpp[i].rare);
			PokeParaSet(dfp->pp,dfp->dsp.dpp[i].mons_no,dfp->dsp.dpp[i].level,0,RND_SET,rnd,ID_SET,0);
	
			for(j=0;j<4;j++){
				PokeWazaSetPos(dfp->pp,dfp->dsp.dpp[i].waza[j],j);
				PokeParaPut(dfp->pp,ID_PARA_pp1+j,&dfp->dsp.dpp[i].pp[j]);
				PokeParaPut(dfp->pp,ID_PARA_pp_count1+j,&dfp->dsp.dpp[i].pp_count[j]);
			}
			for(j=STATUS_HP;j<STATUS_MAX;j++){
				PokeParaPut(dfp->pp,ID_PARA_hp_rnd+j,&dfp->dsp.dpp[i].status_rnd[j]);
				PokeParaPut(dfp->pp,ID_PARA_hp_exp+j,&dfp->dsp.dpp[i].status_exp[j]);
			}
			if(dfp->dsp.dpp[i].speabino_set){
				PokeParaPut(dfp->pp,ID_PARA_speabino,&dfp->dsp.dpp[i].speabino_set);
			}
			else{
				PokeParaPut(dfp->pp,ID_PARA_speabino,&dfp->dsp.dpp[i].speabino);
			}
			PokeParaPut(dfp->pp,ID_PARA_item,&dfp->dsp.dpp[i].item);
			PokeParaPut(dfp->pp,ID_PARA_friend,&dfp->dsp.dpp[i].friend);
			PokeParaPut(dfp->pp,ID_PARA_condition,&cond_table[dfp->dsp.dpp[i].condition]);
			PokeParaPut(dfp->pp,ID_PARA_exp,&dfp->dsp.dpp[i].exp);
			if(dfp->dsp.dpp[i].mons_no==MONSNO_AUSU){
				form_no=AusuTypeGet(ItemParamGet(dfp->dsp.dpp[i].item,ITEM_PRM_EQUIP,HEAPID_BASE_SYSTEM));
				PokeParaPut(dfp->pp,ID_PARA_form_no,&form_no);
			}
			else{
				PokeParaPut(dfp->pp,ID_PARA_form_no,&dfp->dsp.dpp[i].form_no);
			}
			PokeParaPut(dfp->pp,ID_PARA_tamago_flag,&dfp->dsp.dpp[i].egg_flag);
			PokeParaGetInfoSet(dfp->pp,dfp->param->my_status[0],dfp->dsp.dpp[i].get_ball,NULL,NULL,HEAPID_DEBUG_APPLICATION);

			PokeParaCalc(dfp->pp);

			PokeParaPut(dfp->pp,ID_PARA_hp,&dfp->dsp.dpp[i].default_hp);

			if(dfp->param->fight_type==FIGHT_TYPE_AI_MULTI){
				PokeParty_Add(dfp->param->poke_party[0],dfp->pp);
				PokeParty_Add(dfp->param->poke_party[1],dfp->pp);
			}
			else if(dfp->param->fight_type==FIGHT_TYPE_2vs2_YASEI){
				PokeParty_Add(dfp->param->poke_party[0],dfp->pp);
			}
			else{
				PokeParty_Add(dfp->param->poke_party[0],dfp->pp);
			}
		}
		if((dfp->dsp.dpp[i+6].mons_no)&&(dfp->trainer_id==0)){
#if 0
			PokeParaSetSexChr(dfp->pp,
							  dfp->dsp.dpp[i+6].mons_no,
							  dfp->dsp.dpp[i+6].level,
							  0,
							  dfp->dsp.dpp[i+6].sex,
							  dfp->dsp.dpp[i+6].chr,
							  0);
#endif
			rnd=PokeRndGet(dfp->dsp.dpp[i+6].mons_no,dfp->dsp.dpp[i+6].sex,dfp->dsp.dpp[i+6].chr,dfp->dsp.dpp[i+6].rare);
			PokeParaSet(dfp->pp,dfp->dsp.dpp[i+6].mons_no,dfp->dsp.dpp[i+6].level,0,RND_SET,rnd,ID_SET,0);
	
			for(j=0;j<4;j++){
				PokeWazaSetPos(dfp->pp,dfp->dsp.dpp[i+6].waza[j],j);
				PokeParaPut(dfp->pp,ID_PARA_pp1+j,&dfp->dsp.dpp[i+6].pp[j]);
				PokeParaPut(dfp->pp,ID_PARA_pp_count1+j,&dfp->dsp.dpp[i+6].pp_count[j]);
			}
			for(j=STATUS_HP;j<STATUS_MAX;j++){
				PokeParaPut(dfp->pp,ID_PARA_hp_rnd+j,&dfp->dsp.dpp[i+6].status_rnd[j]);
				PokeParaPut(dfp->pp,ID_PARA_hp_exp+j,&dfp->dsp.dpp[i+6].status_exp[j]);
			}
			if(dfp->dsp.dpp[i+6].speabino_set){
				PokeParaPut(dfp->pp,ID_PARA_speabino,&dfp->dsp.dpp[i+6].speabino_set);
			}
			else{
				PokeParaPut(dfp->pp,ID_PARA_speabino,&dfp->dsp.dpp[i+6].speabino);
			}
			PokeParaPut(dfp->pp,ID_PARA_item,&dfp->dsp.dpp[i+6].item);
			PokeParaPut(dfp->pp,ID_PARA_friend,&dfp->dsp.dpp[i+6].friend);
			PokeParaPut(dfp->pp,ID_PARA_condition,&cond_table[dfp->dsp.dpp[i+6].condition]);
			PokeParaPut(dfp->pp,ID_PARA_exp,&dfp->dsp.dpp[i+6].exp);
			if(dfp->dsp.dpp[i+6].mons_no==MONSNO_AUSU){
				form_no=AusuTypeGet(ItemParamGet(dfp->dsp.dpp[i+6].item,ITEM_PRM_EQUIP,HEAPID_BASE_SYSTEM));
				PokeParaPut(dfp->pp,ID_PARA_form_no,&form_no);
			}
			else{
				PokeParaPut(dfp->pp,ID_PARA_form_no,&dfp->dsp.dpp[i+6].form_no);
			}
			PokeParaPut(dfp->pp,ID_PARA_tamago_flag,&dfp->dsp.dpp[i+6].egg_flag);
			PokeParaGetInfoSet(dfp->pp,dfp->param->my_status[0],dfp->dsp.dpp[i+6].get_ball,NULL,NULL,HEAPID_DEBUG_APPLICATION);

			PokeParaCalc(dfp->pp);

			PokeParaPut(dfp->pp,ID_PARA_hp,&dfp->dsp.dpp[i+6].default_hp);

			if(dfp->param->fight_type==FIGHT_TYPE_AI_MULTI){
				PokeParty_Add(dfp->param->poke_party[2],dfp->pp);
				PokeParty_Add(dfp->param->poke_party[3],dfp->pp);
			}
			else if(dfp->param->fight_type==FIGHT_TYPE_2vs2_YASEI){
				if(i==0){
					PokeParty_Add(dfp->param->poke_party[1],dfp->pp);
				}
				else if(i==1){
					PokeParty_Add(dfp->param->poke_party[3],dfp->pp);
				}
				else{
					PokeParty_Add(dfp->param->poke_party[2],dfp->pp);
				}
			}
			else if(dfp->param->fight_type==FIGHT_TYPE_BATTLE_TOWER_SIO_MULTI){
				PokeParty_Add(dfp->param->poke_party[1],dfp->pp);
				PokeParty_Add(dfp->param->poke_party[3],dfp->pp);
			}
			else{
				PokeParty_Add(dfp->param->poke_party[1],dfp->pp);
			}
		}
	}
	//エンカウントフィールド情報
	dfp->param->ground_id=dfp->dsp.ground;
	dfp->param->bg_id=dfp->dsp.bg;
	dfp->param->time_zone=dfp->dsp.time_zone;
	dfp->param->battle_status_flag=(dfp->dsp.version<<28);
	dfp->param->battle_status_flag|=(dfp->dsp.battle_status_flag<<25);

	FontProc_UnloadBitData(FONT_SYSTEM);
	sys_VBlankFuncChange(NULL,NULL);

	return TRUE;
}

//==============================================================================================
//
//	メニューカーソル移動
//
//==============================================================================================
void	CursorMove(DEBUG_FIGHT_PARAM *dfp,int side,int pos,int mode)
{
	dfp->put_req=1;
	switch(side){
	case MOVE_MAIN:
	default:
		GF_BGL_BmpWinFill(dfp->win_m,0x0f,mlp_m[dfp->cur_pos_m].cursor_pos_x,mlp_m[dfp->cur_pos_m].cursor_pos_y,12,16);
		if(mode==CUR_PUT){
			MSGMAN_GetString(dfp->man_msg,DF_CURSOR,dfp->msg_buf);
			GF_STR_PrintSimple(dfp->win_m,FONT_SYSTEM,dfp->msg_buf,mlp_m[pos].cursor_pos_x,mlp_m[pos].cursor_pos_y,MSG_NO_PUT,NULL);
			dfp->cur_pos_m=pos;	
		}
		break;
	case MOVE_SUB:
		{
			MENU_LIST_PARAM	*mlp;

			mlp=(MENU_LIST_PARAM *)mlp_s_list[dfp->page];

			GF_BGL_BmpWinFill(dfp->win_s,0x0f,mlp[dfp->cur_pos_s].cursor_pos_x,mlp[dfp->cur_pos_s].cursor_pos_y,12,16);
			if(mode==CUR_PUT){
				MSGMAN_GetString(dfp->man_msg,DF_CURSOR,dfp->msg_buf);
				GF_STR_PrintSimple(dfp->win_s,FONT_SYSTEM,dfp->msg_buf,mlp[pos].cursor_pos_x,mlp[pos].cursor_pos_y,MSG_NO_PUT,NULL);
				dfp->cur_pos_s=pos;
				dfp->put_req=1;
			}
		}
		break;
	case MOVE_AI:
		GF_BGL_BmpWinFill(dfp->win_m,0x0f,MINE_X-12,MINE_Y+16*dfp->sub_seq_no,12,16);
		if(mode==CUR_PUT){
			MSGMAN_GetString(dfp->man_msg,DF_CURSOR,dfp->msg_buf);
			GF_STR_PrintSimple(dfp->win_m,FONT_SYSTEM,dfp->msg_buf,MINE_X-12,MINE_Y+16*pos,MSG_NO_PUT,NULL);
			dfp->sub_seq_no=pos;	
		}
		break;
	}
}

//==============================================================================================
//
//	戦闘タイプ編集
//
//==============================================================================================
enum{
	SEQ_FTA_INIT=0,
	SEQ_FTA_MAIN
};

static	BOOL	DebugFightFightTypeAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp)
{
	switch(dfp->sub_seq_no){
	case SEQ_FTA_INIT:
		DebugFightFightTypeDataPut(dfp,COL_ACTIVE);
		dfp->sub_seq_no=SEQ_FTA_MAIN;
		break;
	case SEQ_FTA_MAIN:
		if(sys.repeat&PAD_KEY_UP){
			if(dfp->dsp.fight_type){
				dfp->dsp.fight_type--;
			}
			else{
				dfp->dsp.fight_type=FIGHT_TYPE_MAX-1;
			}
			DebugFightFightTypeDataPut(dfp,COL_ACTIVE);
		}
		else if(sys.repeat&PAD_KEY_DOWN){
			if(dfp->dsp.fight_type<FIGHT_TYPE_MAX-1){
				dfp->dsp.fight_type++;
			}
			else{
				dfp->dsp.fight_type=0;
			}
			DebugFightFightTypeDataPut(dfp,COL_ACTIVE);
		}
		else if(sys.trg&PAD_BUTTON_A){
			if((dfp->dsp.fight_type==FT_2vs2)||
			   (dfp->dsp.fight_type==FT_2vs2_SIO_P)||
			   (dfp->dsp.fight_type==FT_2vs2_SIO_C)||
			   (dfp->dsp.fight_type==FT_2vs2_YASEI)||
			   (dfp->dsp.fight_type==FT_AI_MULTI)||
			   (dfp->dsp.fight_type==FT_BT_MULTI_SIO_P)||
			   (dfp->dsp.fight_type==FT_BT_MULTI_SIO_C)){
				if(dfp->dsp.dpp[1].mons_no==0){
					DebugFightDefaultPokeSet(dfp,1);
				}
				if(dfp->dsp.dpp[1+6].mons_no==0){
					DebugFightDefaultPokeSet(dfp,1+6);
				}
				DebugFightMainScreenCreate(dfp);
			}
			DebugFightFightTypeDataPut(dfp,COL_NORMAL);
			return TRUE;
		}
		break;
	}
	return FALSE;
}

//==============================================================================================
//
//	パラメータロード
//
//==============================================================================================
static	BOOL	DebugFightLoadAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp)
{
	PMSVLD_Load(DEBUG_FIGHT_SAVE,&dfp->dsp,sizeof(DEBUG_SAVE_PARAM));
	Snd_SePlay(SEQ_SE_DP_DECIDE);

	DebugFightMainScreenCreate(dfp);
	CursorMove(dfp,MOVE_MAIN,dfp->cur_pos_m,CUR_PUT);

	return TRUE;
}

//==============================================================================================
//
//	パラメータセーブ
//
//==============================================================================================
static	BOOL	DebugFightSaveAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp)
{
	PMSVLD_Save(DEBUG_FIGHT_SAVE,&dfp->dsp,sizeof(DEBUG_SAVE_PARAM));
	Snd_SePlay(SEQ_SE_DP_DECIDE);

	return TRUE;
}

//==============================================================================================
//
//	サーババージョンの編集
//
//==============================================================================================
static	BOOL	DebugFightVersionAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp)
{
	switch(dfp->sub_seq_no){
	case 0:
		DebugFightVersionDataPut(dfp,COL_ACTIVE);
		dfp->sub_seq_no=1;
		break;
	case 1:
		if((sys.repeat&PAD_KEY_UP)&&(dfp->dsp.version<9)){
			dfp->dsp.version++;
			DebugFightVersionDataPut(dfp,COL_ACTIVE);
		}
		else if((sys.repeat&PAD_KEY_DOWN)&&(dfp->dsp.version>0)){
			dfp->dsp.version--;
			DebugFightVersionDataPut(dfp,COL_ACTIVE);
		}
		else if(sys.trg&PAD_BUTTON_A){
			DebugFightVersionDataPut(dfp,COL_NORMAL);
			return TRUE;
		}
		break;
	}
	return FALSE;
}

//==============================================================================================
//
//	地形の編集
//
//==============================================================================================
static	BOOL	DebugFightGroundAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp)
{
	switch(dfp->sub_seq_no){
	case 0:
		DebugFightGroundDataPut(dfp,COL_ACTIVE);
		dfp->sub_seq_no=1;
		break;
	case 1:
		if((sys.repeat&PAD_KEY_UP)&&(dfp->dsp.ground>0)){
			dfp->dsp.ground--;
			DebugFightGroundDataPut(dfp,COL_ACTIVE);
		}
		else if((sys.repeat&PAD_KEY_DOWN)&&(dfp->dsp.ground<GROUND_ID_BOG)){
			dfp->dsp.ground++;
			DebugFightGroundDataPut(dfp,COL_ACTIVE);
		}
		else if(sys.trg&PAD_BUTTON_A){
			DebugFightGroundDataPut(dfp,COL_NORMAL);
			return TRUE;
		}
		break;
	}
	return FALSE;
}

//==============================================================================================
//
//	背景の編集
//
//==============================================================================================
static	BOOL	DebugFightBGAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp)
{
	switch(dfp->sub_seq_no){
	case 0:
		DebugFightBGDataPut(dfp,COL_ACTIVE);
		dfp->sub_seq_no=1;
		break;
	case 1:
		if((sys.repeat&PAD_KEY_UP)&&(dfp->dsp.bg>0)){
			dfp->dsp.bg--;
			DebugFightBGDataPut(dfp,COL_ACTIVE);
		}
		else if((sys.repeat&PAD_KEY_DOWN)&&(dfp->dsp.bg<BG_ID_CAVE_C)){
			dfp->dsp.bg++;
			DebugFightBGDataPut(dfp,COL_ACTIVE);
		}
		else if(sys.trg&PAD_BUTTON_A){
			DebugFightBGDataPut(dfp,COL_NORMAL);
			return TRUE;
		}
		break;
	}
	return FALSE;
}

//==============================================================================================
//
//	天候の編集
//
//==============================================================================================
static	BOOL	DebugFightWeatherAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp)
{
	switch(dfp->sub_seq_no){
	case 0:
		DebugFightWeatherDataPut(dfp,COL_ACTIVE);
		dfp->sub_seq_no=1;
		break;
	case 1:
		if((sys.repeat&PAD_KEY_UP)&&(dfp->dsp.weather>0)){
			dfp->dsp.weather--;
			DebugFightWeatherDataPut(dfp,COL_ACTIVE);
		}
		else if((sys.repeat&PAD_KEY_DOWN)&&(dfp->dsp.weather<NELEMS(weather_table)-1)){
			dfp->dsp.weather++;
			DebugFightWeatherDataPut(dfp,COL_ACTIVE);
		}
		else if(sys.trg&PAD_BUTTON_A){
			DebugFightWeatherDataPut(dfp,COL_NORMAL);
			return TRUE;
		}
		break;
	}
	return FALSE;
}

//==============================================================================================
//
//	タイムゾーンの編集
//
//==============================================================================================
static	BOOL	DebugFightTimeZoneAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp)
{
	switch(dfp->sub_seq_no){
	case 0:
		DebugFightTimeZoneDataPut(dfp,COL_ACTIVE);
		dfp->sub_seq_no=1;
		break;
	case 1:
		if((sys.repeat&PAD_KEY_UP)&&(dfp->dsp.time_zone>0)){
			dfp->dsp.time_zone--;
			DebugFightTimeZoneDataPut(dfp,COL_ACTIVE);
		}
		else if((sys.repeat&PAD_KEY_DOWN)&&(dfp->dsp.time_zone<TIMEZONE_MIDNIGHT)){
			dfp->dsp.time_zone++;
			DebugFightTimeZoneDataPut(dfp,COL_ACTIVE);
		}
		else if(sys.trg&PAD_BUTTON_A){
			DebugFightTimeZoneDataPut(dfp,COL_NORMAL);
			return TRUE;
		}
		break;
	}
	return FALSE;
}

//==============================================================================================
//
//	自分の性別編集
//
//==============================================================================================
static	BOOL	DebugFightMySexAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp)
{
	switch(dfp->sub_seq_no){
	case 0:
		DebugFightMySexDataPut(dfp,COL_ACTIVE);
		dfp->sub_seq_no=1;
		break;
	case 1:
		if((sys.repeat&PAD_KEY_UP)&&(dfp->dsp.my_sex>0)){
			dfp->dsp.my_sex--;
			DebugFightMySexDataPut(dfp,COL_ACTIVE);
		}
		else if((sys.repeat&PAD_KEY_DOWN)&&(dfp->dsp.my_sex<7)){
			dfp->dsp.my_sex++;
			DebugFightMySexDataPut(dfp,COL_ACTIVE);
		}
		else if(sys.trg&PAD_BUTTON_A){
			DebugFightMySexDataPut(dfp,COL_NORMAL);
			return TRUE;
		}
		break;
	}
	return FALSE;
}

//==============================================================================================
//
//	戦闘ルール編集
//
//==============================================================================================
static	BOOL	DebugFightRuleAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp)
{
	switch(dfp->sub_seq_no){
	case 0:
		DebugFightRuleDataPut(dfp,COL_ACTIVE);
		dfp->sub_seq_no=1;
		break;
	case 1:
		if((sys.trg&PAD_KEY_UP)||(sys.trg&PAD_KEY_DOWN)){
			dfp->dsp.rule^=1;
			DebugFightRuleDataPut(dfp,COL_ACTIVE);
		}
		else if(sys.trg&PAD_BUTTON_A){
			DebugFightRuleDataPut(dfp,COL_NORMAL);
			return TRUE;
		}
		break;
	}
	return FALSE;
}

//==============================================================================================
//
//	技エフェクトＯＮ／ＯＦＦフラグ編集
//
//==============================================================================================
static	BOOL	DebugFightEffectFlagAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp)
{
	switch(dfp->sub_seq_no){
	case 0:
		DebugFightEffectFlagDataPut(dfp,COL_ACTIVE);
		dfp->sub_seq_no=1;
		break;
	case 1:
		if((sys.trg&PAD_KEY_UP)||(sys.trg&PAD_KEY_DOWN)){
			dfp->dsp.effect_flag^=1;
			DebugFightEffectFlagDataPut(dfp,COL_ACTIVE);
		}
		else if(sys.trg&PAD_BUTTON_A){
			DebugFightEffectFlagDataPut(dfp,COL_NORMAL);
			return TRUE;
		}
		break;
	}
	return FALSE;
}

//==============================================================================================
//
//	メッセージスピード編集
//
//==============================================================================================
static	BOOL	DebugFightMsgSpeedAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp)
{
	switch(dfp->sub_seq_no){
	case 0:
		DebugFightMsgSpeedDataPut(dfp,COL_ACTIVE);
		dfp->sub_seq_no=1;
		break;
	case 1:
		if((sys.trg&PAD_KEY_UP)&&(dfp->dsp.msg_speed>0)){
			dfp->dsp.msg_speed--;
			DebugFightMsgSpeedDataPut(dfp,COL_ACTIVE);
		}
		if((sys.trg&PAD_KEY_DOWN)&&(dfp->dsp.msg_speed<2)){
			dfp->dsp.msg_speed++;
			DebugFightMsgSpeedDataPut(dfp,COL_ACTIVE);
		}
		else if(sys.trg&PAD_BUTTON_A){
			DebugFightMsgSpeedDataPut(dfp,COL_NORMAL);
			return TRUE;
		}
		break;
	}
	return FALSE;
}

//==============================================================================================
//
//	ポケモンパラメータ編集
//
//==============================================================================================
enum{
	SEQ_SUB_MENU_INIT=0,
	SEQ_SUB_MENU_WRITE,
	SEQ_SUB_MENU_MOVE,
	SEQ_SUB_MENU_ACT,
};

static	BOOL	DebugFightPokeAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp)
{
	int				move=NO_MOVE;
	MENU_LIST_PARAM	*mlp;

	switch(dfp->sub_seq_no){
	case SEQ_SUB_MENU_INIT:
		DebugFightMonsNamePut(dfp,dfp->cur_pos_m,COL_ACTIVE);
		if(dpp->mons_no==0){
			dfp->page=0;
		}
		dfp->dpp_temp=*dpp;
	case SEQ_SUB_MENU_WRITE:
		dfp->cur_pos_s=0;
		DebugFightSubScreenCreate(dfp,&dfp->dpp_temp,dfp->page);
		CursorMove(dfp,MOVE_SUB,dfp->cur_pos_s,CUR_PUT);
		dfp->sub_seq_no=SEQ_SUB_MENU_MOVE;
	case SEQ_SUB_MENU_MOVE:
		mlp=(MENU_LIST_PARAM *)mlp_s_list[dfp->page];

		if((sys.trg==PAD_KEY_LEFT)&&(dfp->dpp_temp.mons_no)){
			move=mlp[dfp->cur_pos_s].move_left;
		}
		else if((sys.trg==PAD_KEY_RIGHT)&&(dfp->dpp_temp.mons_no)){
			move=mlp[dfp->cur_pos_s].move_right;
		}
		if((sys.trg==PAD_KEY_UP)&&(dfp->dpp_temp.mons_no)){
			move=mlp[dfp->cur_pos_s].move_up;
		}
		else if((sys.trg==PAD_KEY_DOWN)&&(dfp->dpp_temp.mons_no)){
			move=mlp[dfp->cur_pos_s].move_down;
		}
		else if((sys.trg==PAD_BUTTON_L)&&(dfp->page)&&(dfp->dpp_temp.mons_no)){
			dfp->page--;
			dfp->sub_seq_no=SEQ_SUB_MENU_WRITE;
		}
		else if((sys.trg==PAD_BUTTON_R)&&(dfp->page<NELEMS(mlp_s_list)-1)&&(dfp->dpp_temp.mons_no)){
			dfp->page++;
			dfp->sub_seq_no=SEQ_SUB_MENU_WRITE;
		}
		else if(sys.trg==PAD_BUTTON_X){
			DebugFightDefaultSet(dfp,&dfp->dpp_temp,param_mode_tbl[dfp->page]);
			DebugFightSubScreenCreate(dfp,&dfp->dpp_temp,dfp->page);
			CursorMove(dfp,MOVE_SUB,dfp->cur_pos_s,CUR_PUT);
		}
		else if(sys.trg==PAD_BUTTON_A){
			if(mlp[dfp->cur_pos_s].a_button_act!=NULL){
				dfp->sub_act_seq_no=0;
				dfp->sub_seq_no=SEQ_SUB_MENU_ACT;
			}
		}
		if((sys.trg==PAD_BUTTON_START)||(sys.trg==PAD_BUTTON_B)){
			if(sys.trg==PAD_BUTTON_START){
				*dpp=dfp->dpp_temp;
			}
			DebugFightMainScreenCreate(dfp);
			DebugFightSubScreenCreate(dfp,dpp,dfp->page);
			CursorMove(dfp,MOVE_MAIN,dfp->cur_pos_m,CUR_PUT);
			CursorMove(dfp,MOVE_SUB,dfp->cur_pos_s,CUR_DEL);
			return TRUE;
		}
		if(move!=NO_MOVE){
			CursorMove(dfp,MOVE_SUB,move,CUR_PUT);
		}
		break;
	case SEQ_SUB_MENU_ACT:
		mlp=(MENU_LIST_PARAM *)mlp_s_list[dfp->page];
		if(mlp[dfp->cur_pos_s].a_button_act(dfp,&dfp->dpp_temp)==TRUE){
			dfp->sub_seq_no=SEQ_SUB_MENU_MOVE;
		}
		break;
	}
	return FALSE;
}

//==============================================================================================
//
//	ポケモン種類編集
//
//==============================================================================================
static	BOOL	DebugFightKindAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp)
{
	BOOL	ret=FALSE;
	int		min;

	switch(dfp->sub_act_seq_no){
	case 0:
		DebugFightKindDataPut(dfp,dpp,MODE_ACTIVE);
		dfp->sub_act_seq_no++;
	case 1:
		if((dfp->cur_pos_m==MS_MINE_POKE_1)||(dfp->cur_pos_m==MS_ENEMY_POKE_1)){
			min=MONSNO_HUSIGIDANE;
		}
		else{
			min=0;
		}
		switch(DebugFightNumCalc(dfp,&dpp->mons_no,3,min,MONSNO_END,MODE_LOOP)){
		case NUM_CALC_NONE:
			break;
		case NUM_CALC_CHANGE:
			//経験値取得
			dpp->exp=PokeLevelExpGet(dpp->mons_no,dpp->level);
			DebugFightExpDataPut(dfp,dpp,MODE_NORMAL);
			//性別取得
			switch(PokePersonalParaGet(dpp->mons_no,ID_PER_sex)){
			case MONS_MALE:
			default:
				dpp->sex=PARA_MALE;
				break;
			case MONS_FEMALE:
				dpp->sex=PARA_FEMALE;
				break;
			case MONS_UNKNOWN:
				dpp->sex=PARA_UNK;
				break;
			}
			DebugFightSexDataPut(dfp,dpp,COL_NORMAL);
			//パラメータ計算
			DebugFightParamPut(dfp,dpp);
			//特性No変更
			dpp->speabino=PokePersonalParaGet(dpp->mons_no,ID_PER_speabi1);
		case NUM_CALC_MOVE:
			DebugFightKindDataPut(dfp,dpp,MODE_ACTIVE);
			break;
		case NUM_CALC_END:
			DebugFightKindDataPut(dfp,dpp,MODE_NORMAL);
			if(dpp->mons_no==0){
				DebugFightPokemonParamInit(dpp);
			}
			ret=TRUE;
			break;
		}
		break;
	}
	return ret;
}

//==============================================================================================
//
//	レア編集
//
//==============================================================================================
static	BOOL	DebugFightRareAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp)
{
	switch(dfp->sub_act_seq_no){
	case 0:
		DebugFightRareDataPut(dfp,dpp,COL_ACTIVE);
		dfp->sub_act_seq_no++;
	case 1:
		if((sys.trg&PAD_KEY_UP)||(sys.trg&PAD_KEY_DOWN)){
			dpp->rare^=1;
			DebugFightRareDataPut(dfp,dpp,COL_ACTIVE);
		}
		else if(sys.trg&PAD_BUTTON_A){
			DebugFightRareDataPut(dfp,dpp,COL_NORMAL);
			return TRUE;
		}
		break;
	}
	return FALSE;
}

//==============================================================================================
//
//	レベル編集
//
//==============================================================================================
static	BOOL	DebugFightLevelAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp)
{
	BOOL	ret=FALSE;

	switch(dfp->sub_act_seq_no){
	case 0:
		DebugFightLevelDataPut(dfp,dpp,MODE_ACTIVE);
		dfp->sub_act_seq_no++;
	case 1:
		switch(DebugFightNumCalc(dfp,&dpp->level,3,1,100,MODE_LOOP)){
		case NUM_CALC_NONE:
			break;
		case NUM_CALC_CHANGE:
			dpp->exp=PokeLevelExpGet(dpp->mons_no,dpp->level);
			DebugFightExpDataPut(dfp,dpp,MODE_NORMAL);
			DebugFightParamPut(dfp,dpp);
		case NUM_CALC_MOVE:
			DebugFightLevelDataPut(dfp,dpp,MODE_ACTIVE);
			break;
		case NUM_CALC_END:
			DebugFightLevelDataPut(dfp,dpp,MODE_NORMAL);
			ret=TRUE;
			break;
		}
		break;
	}
	return ret;
}

//==============================================================================================
//
//	経験値編集
//
//==============================================================================================
static	BOOL	DebugFightExpAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp)
{
	BOOL	ret=FALSE;

	switch(dfp->sub_act_seq_no){
	case 0:
		DebugFightExpDataPut(dfp,dpp,MODE_ACTIVE);
		dfp->sub_act_seq_no++;
	case 1:
		{
			u32	exp_max;

			exp_max=PokeLevelExpGet(dpp->mons_no,100);
			switch(DebugFightNumCalc(dfp,&dpp->exp,EXP_KETA,1,exp_max,MODE_LOOP)){
			case NUM_CALC_NONE:
				break;
			case NUM_CALC_CHANGE:
				dpp->level=PokeLevelCalc(dpp->mons_no,dpp->exp);
				DebugFightLevelDataPut(dfp,dpp,MODE_NORMAL);
				DebugFightParamPut(dfp,dpp);
			case NUM_CALC_MOVE:
				DebugFightExpDataPut(dfp,dpp,MODE_ACTIVE);
				break;
			case NUM_CALC_END:
				DebugFightExpDataPut(dfp,dpp,MODE_NORMAL);
				ret=TRUE;
				break;
			}
		}
		break;
	}
	return ret;
}

//==============================================================================================
//
//	性別編集
//
//==============================================================================================
static	BOOL	DebugFightSexAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp)
{
	//性別固定の場合は、編集なし
	switch(PokePersonalParaGet(dpp->mons_no,ID_PER_sex)){
	case MONS_MALE:
	case MONS_FEMALE:
	case MONS_UNKNOWN:
		return TRUE;
	default:
		break;
	}
	switch(dfp->sub_act_seq_no){
	case 0:
		DebugFightSexDataPut(dfp,dpp,COL_ACTIVE);
		dfp->sub_act_seq_no++;
	case 1:
		if((sys.repeat&PAD_KEY_UP)&&(dpp->sex)){
			dpp->sex--;
			DebugFightSexDataPut(dfp,dpp,COL_ACTIVE);
		}
		if((sys.repeat&PAD_KEY_DOWN)&&(dpp->sex<PARA_FEMALE)){
			dpp->sex++;
			DebugFightSexDataPut(dfp,dpp,COL_ACTIVE);
		}
		else if(sys.trg&PAD_BUTTON_A){
			DebugFightSexDataPut(dfp,dpp,COL_NORMAL);
			return TRUE;
		}
		break;
	}
	return FALSE;
}

//==============================================================================================
//
//	性格編集
//
//==============================================================================================
static	BOOL	DebugFightChrAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp)
{
	switch(dfp->sub_act_seq_no){
	case 0:
		DebugFightChrDataPut(dfp,dpp,COL_ACTIVE);
		dfp->sub_act_seq_no++;
	case 1:
		if((sys.repeat&PAD_KEY_UP)&&(dpp->chr)){
			dpp->chr--;
			DebugFightChrDataPut(dfp,dpp,COL_ACTIVE);
			DebugFightParamPut(dfp,dpp);
		}
		if((sys.repeat&PAD_KEY_DOWN)&&(dpp->chr<CHR_MAX)){
			dpp->chr++;
			DebugFightChrDataPut(dfp,dpp,COL_ACTIVE);
			DebugFightParamPut(dfp,dpp);
		}
		else if(sys.trg&PAD_BUTTON_A){
			DebugFightChrDataPut(dfp,dpp,COL_NORMAL);
			return TRUE;
		}
		break;
	}
	return FALSE;
}

//==============================================================================================
//
//	パワー乱数編集
//
//==============================================================================================
static	BOOL	DebugFightStatusRndAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp)
{
	BOOL	ret=FALSE;
	int		status;

	status=dfp->cur_pos_s-MENU1_HP_RND;

	switch(dfp->sub_act_seq_no){
	case 0:
		DebugFightStatusRndDataPut(dfp,dpp,status,MODE_ACTIVE);
		dfp->sub_act_seq_no++;
	case 1:
		switch(DebugFightNumCalc(dfp,&dpp->status_rnd[status],STRND_KETA,0,31,MODE_LOOP)){
		case NUM_CALC_NONE:
			break;
		case NUM_CALC_CHANGE:
			DebugFightParamPut(dfp,dpp);
		case NUM_CALC_MOVE:
			DebugFightStatusRndDataPut(dfp,dpp,status,MODE_ACTIVE);
			break;
		case NUM_CALC_END:
			DebugFightStatusRndDataPut(dfp,dpp,status,MODE_NORMAL);
			ret=TRUE;
			break;
		}
		break;
	}
	return ret;
}

//==============================================================================================
//
//	努力値編集
//
//==============================================================================================
static	BOOL	DebugFightStatusExpAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp)
{
	BOOL	ret=FALSE;
	int		status;

	status=dfp->cur_pos_s-MENU1_HP_EXP;

	switch(dfp->sub_act_seq_no){
	case 0:
		DebugFightStatusExpDataPut(dfp,dpp,status,MODE_ACTIVE);
		dfp->sub_act_seq_no++;
	case 1:
		{
			int	i;
			int	exp_total;
			int	exp_max;

			exp_total=0;
			for(i=STATUS_HP;i<STATUS_MAX;i++){
				exp_total+=dpp->status_exp[i];
			}
			if(PARA_EXP_TOTAL_MAX<exp_total+(PARA_EXP_MAX-dpp->status_exp[status])){
				exp_max=PARA_EXP_MAX-
						((exp_total+(PARA_EXP_MAX-dpp->status_exp[status]))-PARA_EXP_TOTAL_MAX);
			}
			else{
				exp_max=PARA_EXP_MAX;
			}
			switch(DebugFightNumCalc(dfp,&dpp->status_exp[status],STEXP_KETA,0,exp_max,MODE_LOOP)){
			case NUM_CALC_NONE:
				break;
			case NUM_CALC_CHANGE:
				DebugFightParamPut(dfp,dpp);
			case NUM_CALC_MOVE:
				DebugFightStatusExpDataPut(dfp,dpp,status,MODE_ACTIVE);
				break;
			case NUM_CALC_END:
				DebugFightStatusExpDataPut(dfp,dpp,status,MODE_NORMAL);
				ret=TRUE;
				break;
			}
		}
		break;
	}
	return ret;
}

//==============================================================================================
//
//	持ち技編集
//
//==============================================================================================
static	BOOL	DebugFightWazaAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp)
{
	BOOL	ret=FALSE;
	int		min;

	switch(dfp->sub_act_seq_no){
	case 0:
		DebugFightWazaDataPut(dfp,dpp,dfp->cur_pos_s,MODE_ACTIVE);
		dfp->sub_act_seq_no++;
	case 1:
		if(dfp->cur_pos_s){
			min=0;
		}
		else{
			min=WAZANO_HATAKU;
		}
		switch(DebugFightNumCalc(dfp,&dpp->waza[dfp->cur_pos_s],3,min,WAZANO_MAX,MODE_LOOP)){
		case NUM_CALC_NONE:
			break;
		case NUM_CALC_CHANGE:
		case NUM_CALC_MOVE:
			DebugFightWazaDataPut(dfp,dpp,dfp->cur_pos_s,MODE_ACTIVE);
			dpp->pp[dfp->cur_pos_s]=WT_PPMaxGet(dpp->waza[dfp->cur_pos_s],dpp->pp_count[dfp->cur_pos_s]);
			DebugFightPPDataPut(dfp,dpp,dfp->cur_pos_s,MODE_NORMAL);
			break;
		case NUM_CALC_END:
			DebugFightWazaDataPut(dfp,dpp,dfp->cur_pos_s,MODE_NORMAL);
			ret=TRUE;
			break;
		}
		break;
	}
	return ret;
}

//==============================================================================================
//
//	PP編集
//
//==============================================================================================
static	BOOL	DebugFightPPAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp)
{
	BOOL	ret=FALSE;
	int		max;
	int		pos;

	pos=dfp->cur_pos_s-MENU2_PP1;

	switch(dfp->sub_act_seq_no){
	case 0:
		DebugFightPPDataPut(dfp,dpp,pos,MODE_ACTIVE);
		dfp->sub_act_seq_no++;
	case 1:
		max=WT_PPMaxGet(dpp->waza[pos],dpp->pp_count[pos]);
		switch(DebugFightNumCalc(dfp,&dpp->pp[pos],2,0,max,MODE_LOOP)){
		case NUM_CALC_NONE:
			break;
		case NUM_CALC_CHANGE:
		case NUM_CALC_MOVE:
			DebugFightPPDataPut(dfp,dpp,pos,MODE_ACTIVE);
			break;
		case NUM_CALC_END:
			DebugFightPPDataPut(dfp,dpp,pos,MODE_NORMAL);
			ret=TRUE;
			break;
		}
		break;
	}
	return ret;
}

//==============================================================================================
//
//	PP_COUNT編集
//
//==============================================================================================
static	BOOL	DebugFightPPCountAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp)
{
	BOOL	ret=FALSE;
	int		ppmax;
	int		pos;

	pos=dfp->cur_pos_s-MENU2_PP_COUNT1;

	switch(dfp->sub_act_seq_no){
	case 0:
		DebugFightPPCountDataPut(dfp,dpp,pos,MODE_ACTIVE);
		dfp->sub_act_seq_no++;
	case 1:
		ppmax=WT_PPMaxGet(dpp->waza[pos],dpp->pp_count[pos]);
		switch(DebugFightNumCalc(dfp,&dpp->pp_count[pos],1,0,3,MODE_LOOP)){
		case NUM_CALC_NONE:
			break;
		case NUM_CALC_CHANGE:
		case NUM_CALC_MOVE:
			DebugFightPPCountDataPut(dfp,dpp,pos,MODE_ACTIVE);
			if(ppmax==dpp->pp[pos]){
				dpp->pp[pos]=WT_PPMaxGet(dpp->waza[pos],dpp->pp_count[pos]);
			}
			DebugFightPPDataPut(dfp,dpp,pos,MODE_NORMAL);
			break;
		case NUM_CALC_END:
			DebugFightPPCountDataPut(dfp,dpp,pos,MODE_NORMAL);
			ret=TRUE;
			break;
		}
		break;
	}
	return ret;
}

//==============================================================================================
//
//	特性編集
//
//==============================================================================================
static	BOOL	DebugFightSpeAbiAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp)
{
	switch(dfp->sub_act_seq_no){
	case 0:
		DebugFightSpeAbiDataPut(dfp,dpp,COL_ACTIVE);
		dfp->sub_act_seq_no++;
	case 1:
		if((sys.repeat&PAD_KEY_UP)||(sys.repeat&PAD_KEY_DOWN)){
			dpp->speabi^=1;
			DebugFightSpeAbiDataPut(dfp,dpp,COL_ACTIVE);
		}
		else if(sys.trg&PAD_BUTTON_A){
			DebugFightSpeAbiDataPut(dfp,dpp,COL_NORMAL);
			return TRUE;
		}
		break;
	}
	return FALSE;
}

//==============================================================================================
//
//	特性編集（パーソナルデータに依存しない）
//
//==============================================================================================
static	BOOL	DebugFightSpeAbiSetAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp)
{
	BOOL	ret;

	ret=FALSE;

	switch(dfp->sub_act_seq_no){
	case 0:
		DebugFightSpeAbiSetDataPut(dfp,dpp,MODE_ACTIVE);
		dfp->sub_act_seq_no++;
	case 1:
		switch(DebugFightNumCalc(dfp,&dpp->speabino_set,3,0,TOKUSYU_MAX,MODE_LOOP)){
		case NUM_CALC_NONE:
			break;
		case NUM_CALC_CHANGE:
		case NUM_CALC_MOVE:
			DebugFightSpeAbiSetDataPut(dfp,dpp,MODE_ACTIVE);
			break;
		case NUM_CALC_END:
			DebugFightSpeAbiSetDataPut(dfp,dpp,MODE_NORMAL);
			ret=TRUE;
			break;
		}
		break;
	}
	return ret;
}

//==============================================================================================
//
//	装備アイテム編集
//
//==============================================================================================
static	BOOL	DebugFightItemAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp)
{
	BOOL	ret=FALSE;

	switch(dfp->sub_act_seq_no){
	case 0:
		DebugFightItemDataPut(dfp,dpp,MODE_ACTIVE);
		dfp->sub_act_seq_no++;
	case 1:
		switch(DebugFightNumCalc(dfp,&dpp->item,3,0,ITEM_DATA_MAX,MODE_LOOP)){
		case NUM_CALC_NONE:
			break;
		case NUM_CALC_CHANGE:
		case NUM_CALC_MOVE:
			DebugFightItemDataPut(dfp,dpp,MODE_ACTIVE);
			break;
		case NUM_CALC_END:
			DebugFightItemDataPut(dfp,dpp,MODE_NORMAL);
			ret=TRUE;
			break;
		}
		break;
	}
	return ret;
}

//==============================================================================================
//
//	なつき度編集
//
//==============================================================================================
static	BOOL	DebugFightFriendAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp)
{
	BOOL	ret=FALSE;

	switch(dfp->sub_act_seq_no){
	case 0:
		DebugFightFriendDataPut(dfp,dpp,MODE_ACTIVE);
		dfp->sub_act_seq_no++;
	case 1:
		switch(DebugFightNumCalc(dfp,&dpp->friend,3,0,255,MODE_LOOP)){
		case NUM_CALC_NONE:
			break;
		case NUM_CALC_CHANGE:
		case NUM_CALC_MOVE:
			DebugFightFriendDataPut(dfp,dpp,MODE_ACTIVE);
			break;
		case NUM_CALC_END:
			DebugFightFriendDataPut(dfp,dpp,MODE_NORMAL);
			ret=TRUE;
			break;
		}
	}
	return ret;
}

//==============================================================================================
//
//	状態異常編集
//
//==============================================================================================
static	BOOL	DebugFightConditionAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp)
{
	switch(dfp->sub_act_seq_no){
	case 0:
		DebugFightConditionDataPut(dfp,dpp,COL_ACTIVE);
		dfp->sub_act_seq_no++;
	case 1:
		if((sys.repeat&PAD_KEY_UP)&&(dpp->condition)){
			dpp->condition--;
			DebugFightConditionDataPut(dfp,dpp,COL_ACTIVE);
		}
		if((sys.repeat&PAD_KEY_DOWN)&&(dpp->condition<DF_COND_MAX)){
			dpp->condition++;
			DebugFightConditionDataPut(dfp,dpp,COL_ACTIVE);
		}
		else if(sys.trg&PAD_BUTTON_A){
			DebugFightConditionDataPut(dfp,dpp,COL_NORMAL);
			return TRUE;
		}
		break;
	}
	return FALSE;
}

//==============================================================================================
//
//	初期ＨＰ編集
//
//==============================================================================================
static	BOOL	DebugFightDefaultHPAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp)
{
	BOOL	ret=FALSE;

	switch(dfp->sub_act_seq_no){
	case 0:
		DebugFightDefaultHPDataPut(dfp,dpp,MODE_ACTIVE);
		dfp->sub_act_seq_no++;
	case 1:
		switch(DebugFightNumCalc(dfp,&dpp->default_hp,3,0,dpp->hp_max,MODE_LOOP)){
		case NUM_CALC_NONE:
			break;
		case NUM_CALC_CHANGE:
		case NUM_CALC_MOVE:
			DebugFightDefaultHPDataPut(dfp,dpp,MODE_ACTIVE);
			break;
		case NUM_CALC_END:
			DebugFightDefaultHPDataPut(dfp,dpp,MODE_NORMAL);
			ret=TRUE;
			break;
		}
	}
	return ret;
}

//==============================================================================================
//
//	捕獲ボール編集
//
//==============================================================================================
static	BOOL	DebugFightGetBallAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp)
{
	BOOL	ret=FALSE;

	switch(dfp->sub_act_seq_no){
	case 0:
		DebugFightGetBallDataPut(dfp,dpp,COL_ACTIVE);
		dfp->sub_act_seq_no++;
	case 1:
		if((sys.repeat&PAD_KEY_UP)&&(dpp->get_ball>1)){
			dpp->get_ball--;
			DebugFightGetBallDataPut(dfp,dpp,COL_ACTIVE);
		}
		if((sys.repeat&PAD_KEY_DOWN)&&(dpp->get_ball<ITEM_PURESYASUBOORU)){
			dpp->get_ball++;
			DebugFightGetBallDataPut(dfp,dpp,COL_ACTIVE);
		}
		else if(sys.trg&PAD_BUTTON_A){
			DebugFightGetBallDataPut(dfp,dpp,COL_NORMAL);
			return TRUE;
		}
		break;
	}
	return ret;
}

//==============================================================================================
//
//	フォルムナンバー編集
//
//==============================================================================================
static	BOOL	DebugFightFormNoAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp)
{
	BOOL	ret=FALSE;
	int		form_no_max;

	form_no_max=DebugFightFormNoMaxGet(dpp);

	switch(dfp->sub_act_seq_no){
	case 0:
		DebugFightFormNoDataPut(dfp,dpp,form_no_max,MODE_ACTIVE);
		dfp->sub_act_seq_no++;
	case 1:
		switch(DebugFightNumCalc(dfp,&dpp->form_no,3,0,form_no_max,MODE_LOOP)){
		case NUM_CALC_NONE:
			break;
		case NUM_CALC_CHANGE:
		case NUM_CALC_MOVE:
			DebugFightFormNoDataPut(dfp,dpp,form_no_max,MODE_ACTIVE);
			break;
		case NUM_CALC_END:
			DebugFightFormNoDataPut(dfp,dpp,form_no_max,MODE_NORMAL);
			ret=TRUE;
			break;
		}
	}
	return ret;
}

//==============================================================================================
//
//	タマゴフラグ編集
//
//==============================================================================================
static	BOOL	DebugFightEggFlagAct(DEBUG_FIGHT_PARAM *dfp,DEBUG_POKEMON_PARAM *dpp)
{
	dpp->egg_flag^=1;
	DebugFightEggFlagDataPut(dfp,dpp);

	return TRUE;
}

//==============================================================================================
//
//	数値編集
//
//==============================================================================================
static	int	DebugFightNumCalc(DEBUG_FIGHT_PARAM *dfp,u32 *param,int keta,int min,int max,int mode)
{
	int ret=NUM_CALC_NONE;
	u32	calc_work[]={
		1,
		10,
		100,
		1000,
		10000,
		100000,
		1000000,
		10000000,
		100000000,
		1000000000,
	};

	if((sys.repeat & PAD_KEY_LEFT)&&(dfp->cur_pos_keta<(keta-1))){
		dfp->cur_pos_keta++;
		ret=NUM_CALC_MOVE;
	}
	else if((sys.repeat & PAD_KEY_RIGHT)&&(dfp->cur_pos_keta)){
		dfp->cur_pos_keta--;
		ret=NUM_CALC_MOVE;
	}
	else if(sys.repeat & PAD_KEY_UP){
		if(mode==MODE_LOOP){
			if((param[0]+calc_work[dfp->cur_pos_keta])>max){
				param[0]=min;
				ret=NUM_CALC_CHANGE;
			}
			else{
				param[0]+=calc_work[dfp->cur_pos_keta];
				ret=NUM_CALC_CHANGE;
			}
		}
		else{
			if((param[0]+calc_work[dfp->cur_pos_keta])>max){
				param[0]=max;
				ret=NUM_CALC_CHANGE;
			}
			else{
				param[0]+=calc_work[dfp->cur_pos_keta];
				ret=NUM_CALC_CHANGE;
			}
		}
	}
	else if(sys.repeat & PAD_KEY_DOWN){
		if(mode==MODE_LOOP){
			if((param[0]<calc_work[dfp->cur_pos_keta])||((param[0]-calc_work[dfp->cur_pos_keta])<min)){
				param[0]=max;
				ret=NUM_CALC_CHANGE;
			}
			else{
				param[0]-=calc_work[dfp->cur_pos_keta];
				ret=NUM_CALC_CHANGE;
			}
		}
		else{
			if((param[0]<calc_work[dfp->cur_pos_keta])||((param[0]-calc_work[dfp->cur_pos_keta])<min)){
				param[0]=min;
				ret=NUM_CALC_CHANGE;
			}
			else{
				param[0]-=calc_work[dfp->cur_pos_keta];
				ret=NUM_CALC_CHANGE;
			}
		}
	}
	else if(sys.trg & PAD_BUTTON_A){
		dfp->cur_pos_keta=0;
		ret=NUM_CALC_END;
	}

	return ret;
}

//==============================================================================================
//
//	個性乱数取得
//
//	@param	mons_no		取得したいポケモンナンバー
//	@param	sex			取得したい性別
//	@param	chr			取得したい性格
//	@param	rare		取得したいカラー
//
//==============================================================================================
static u32 PokeRndGet(int mons_no,int sex,int chr,int rare)
{
	int	i;
	u32	rnd;

	rnd=PokeParaSexChrRndGet(mons_no,sex,chr);

	if(rare){
		if(PokeRareGetPara(0,rnd)){
			return rnd;
		}
		for(i=3;i<8;i++){
			if(rnd&No2Bit(i)){
				rnd|=No2Bit(i+16);
			}
		}
		if((rnd%25)<chr){
			i=chr-(rnd%25);
		}
		else{
			i=(25+chr)-(rnd%25);
		}
		switch(i){
		case 0:
			break;
		case 1:
			rnd|=0x08000800;
			break;
		case 2:
			rnd|=0x10001000;
			break;
		case 3:
			rnd|=0x18001800;
			break;
		case 4:
			rnd|=0x20002000;
			break;
		case 5:
			rnd|=0x28002800;
			break;
		case 6:
			rnd|=0x30003000;
			break;
		case 7:
			rnd|=0x38003800;
			break;
		case 8:
			rnd|=0x40004000;
			break;
		case 9:
			rnd|=0x48004800;
			break;
		case 10:
			rnd|=0x50005000;
			break;
		case 11:
			rnd|=0x58005800;
			break;
		case 12:
			rnd|=0x60006000;
			break;
		case 13:
			rnd|=0x04000400;
			break;
		case 14:
			rnd|=0x0c000c00;
			break;
		case 15:
			rnd|=0x14001400;
			break;
		case 16:
			rnd|=0x80008000;
			break;
		case 17:
			rnd|=0x88008800;
			break;
		case 18:
			rnd|=0x90009000;
			break;
		case 19:
			rnd|=0x02000200;
			break;
		case 20:
			rnd|=0x0a000a00;
			break;
		case 21:
			rnd|=0x12001200;
			break;
		case 22:
			rnd|=0x01000100;
			break;
		case 23:
			rnd|=0x09000900;
			break;
		case 24:
			rnd|=0x03000300;
			break;
		}
		return rnd;
	}
	else{
		if(PokeRareGetPara(0,rnd)==0){
			return rnd;
		}
		else{
			return (rnd|0x19000000);
		}
	}
	OS_Printf("個性乱数がみつかりませんでした\n");
	return 0;
}

void	DebugFightDefaultPokeSet(DEBUG_FIGHT_PARAM *dfp,int pos)
{
	dfp->dsp.dpp[pos].mons_no=MONSNO_HUSIGIDANE;
	PokeParaSetSexChr(dfp->pp,
					  dfp->dsp.dpp[pos].mons_no,
					  dfp->dsp.dpp[pos].level,
					  0,
					  dfp->dsp.dpp[pos].sex,
					  dfp->dsp.dpp[pos].chr,
					  0);
	dfp->dsp.dpp[pos].default_hp=PokeParaGet(dfp->pp,ID_PARA_hpmax,NULL);
	dfp->dsp.dpp[pos].hp_max=PokeParaGet(dfp->pp,ID_PARA_hpmax,NULL);
	dfp->dsp.dpp[pos].speabino=PokePersonalParaGet(dfp->dsp.dpp[pos].mons_no,ID_PER_speabi1);
	dfp->dsp.dpp[pos].get_ball=PokeParaGet(dfp->pp,ID_PARA_get_ball,NULL);
}

//--------------------------------------------------------------
/**
 * @brief	フォルムナンバーの最大値を取得
 *
 * @retval	フォルムナンバーの最大値	
 */
//--------------------------------------------------------------
static	int	DebugFightFormNoMaxGet(DEBUG_POKEMON_PARAM *dpp)
{
	int	max;

	switch(dpp->mons_no){
	case MONSNO_MINOMESU:
	case MONSNO_MINOMUTTI:
		max=FORMNO_MINOMUTTI_MAX;	///<ミノムッチの別フォルムMAX
		break;
	case MONSNO_SIIUSI:
	case MONSNO_SIIDORUGO:
		max=FORMNO_SII_MAX;			///<シーウシ・シードルゴの別フォルムMAX
		break;
	case MONSNO_DEOKISISU:
		max=FORMNO_DEOKISISU_MAX;	///<デオキシスの別フォルムMAX
		break;
	case MONSNO_ANNOON:
		max=UNK_END-1;				///<アンノーンの別フォルムMAX
		break;
	default:
		max=0;
		break;
	}

	return max;
}

//--------------------------------------------------------------
/**
 * @brief	VBLANK関数
 *
 * @param	work	VBLankには引数が必要なので定義してあるが実際にはNULLが入っているので、アクセスは禁止！
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static	void	DebugFightVBlank(void *work)
{
	OS_SetIrqCheckFlag( OS_IE_V_BLANK);
}

#endif //PM_DEBUG
