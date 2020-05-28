
//============================================================================================
/**
 * @file	fight_tool.h
 * @bfief	戦闘システム用ツールプログラム
 * @author	HisashiSogabe
 * @date	05.07.22
 */
//============================================================================================

#ifndef __FIGHT_TOOL_H_
#define __FIGHT_TOOL_H_

//BattleWorkEnemyClientNoGetのside指定
#define	BWECNG_SIDE_RIGHT	(0)
#define	BWECNG_SIDE_LEFT	(2)

#include	"battle/battle_common.h"
#include	"poketool/poke_tool.h"
#include	"poketool/pokeparty.h"
#include	"system/softsprite.h"
#include	"system/clact_tool.h"
#include	"wazaeffect/we_mana.h"
#include	"battle/battle_input.h"
#include	"system/numfont.h"
#include	"battle/ground.h"
#include	"system/mystatus.h"
#include	"system/msgdata.h"
#include	"system/palanm.h"
#include	"system/wordset.h"
#include	"savedata/config.h"
#include	"battle/temoti_gauge.h"

//ポケモンプログラムアニメ
typedef struct POKE_ANIME_SYS_tag * POKE_ANM_SYS_PTR;

extern	GF_BGL_INI			*BattleWorkGF_BGL_INIGet(BATTLE_WORK *bw);
extern	GF_BGL_BMPWIN		*BattleWorkGF_BGL_BMPWINGet(BATTLE_WORK *bw,int no);
extern	u32					BattleWorkFightTypeGet(BATTLE_WORK *bw);
extern	SERVER_PARAM		*BattleWorkServerParamGet(BATTLE_WORK *bw);
extern	CLIENT_PARAM		*BattleWorkClientParamGet(BATTLE_WORK *bw,int client_no);
extern	int					BattleWorkClientSetMaxGet(BATTLE_WORK *bw);
extern	POKEPARTY			*BattleWorkPokePartyGet(BATTLE_WORK *bw,int client_no);
extern	int					BattleWorkPokeCountGet(BATTLE_WORK *bw,int client_no);
extern	POKEMON_PARAM		*BattleWorkPokemonParamGet(BATTLE_WORK *bw,int client_no,int sel_mons_no);
extern	SOFT_SPRITE_MANAGER	*BattleWorkSoftSpriteManagerGet(BATTLE_WORK *bw);
extern	WE_SYS_PTR			BattleWorkWE_SYS_PTRGet(BATTLE_WORK *bw);
extern	CATS_SYS_PTR		BattleWorkCATS_SYS_PTRGet(BATTLE_WORK *bw);
extern	CATS_RES_PTR		BattleWorkCATS_RES_PTRGet(BATTLE_WORK *bw);
extern	GROUND_WORK			*BattleWorkGroundWorkGet(BATTLE_WORK *bw,int ground_no);
extern	BI_PARAM_PTR		BattleWorkGF_BGL_BIPGet(BATTLE_WORK *bw);
extern TEMOTIGAUGE_PTR		BattleWorkGF_BGL_TGGet(BATTLE_WORK *bw, TEMOTI_SIDE side);
extern void			BattleWorkGF_BGL_TGSet(BATTLE_WORK *bw, TEMOTI_SIDE side, TEMOTIGAUGE_PTR tg);
extern	NUMFONT				*BattleWorkGF_BGL_NumFontHPGet(BATTLE_WORK *bw);
extern	NUMFONT				*BattleWorkGF_BGL_NumFontLVGet(BATTLE_WORK *bw);
extern	MSGDATA_MANAGER		*BattleWorkFightMsgGet(BATTLE_WORK *bw);
extern	MSGDATA_MANAGER		*BattleWorkAttackMsgGet(BATTLE_WORK *bw);
extern	PALETTE_FADE_PTR	BattleWorkPfdGet(BATTLE_WORK *bw);
extern	ZUKAN_WORK			*BattleWorkZukanWorkGet(BATTLE_WORK *bw);
extern	u8					*BattleWorkSioSendBufGet(BATTLE_WORK *bw);
extern	u8					*BattleWorkSioRecvBufGet(BATTLE_WORK *bw);
extern	u16					*BattleWorkSioSendReadGet(BATTLE_WORK *bw);
extern	u16					*BattleWorkSioSendWriteGet(BATTLE_WORK *bw);
extern	u16					*BattleWorkSioSendOverGet(BATTLE_WORK *bw);
extern	u16					*BattleWorkSioRecvReadGet(BATTLE_WORK *bw);
extern	u16					*BattleWorkSioRecvWriteGet(BATTLE_WORK *bw);
extern	u16					*BattleWorkSioRecvOverGet(BATTLE_WORK *bw);
extern	EXCHR_PARAM			*BattleWorkExChrParamGet(BATTLE_WORK *bw);
extern	WORDSET				*BattleWorkWORDSETGet(BATTLE_WORK *bw);
extern	STRBUF				*BattleWorkSTRBUFGet(BATTLE_WORK *bw);
extern	u16					BattleWorkTrainerIDGet(BATTLE_WORK *bw,int client_no);
extern	TRAINER_DATA		*BattleWorkTrainerDataGet(BATTLE_WORK *bw,int client_no);
extern	MYSTATUS			*BattleWorkMyStatusGet(BATTLE_WORK *bw,int client_no);
extern	MYITEM				*BattleWorkMyItemGet(BATTLE_WORK *bw);
extern	BAG_CURSOR			*BattleWorkBagCursorGet(BATTLE_WORK *bw);
extern	u32					BattleWorkMySexGet(BATTLE_WORK *bw,int client_no);
extern	int					BattleWorkClientNoGet(BATTLE_WORK *bw,int client_type);
extern	u8					BattleWorkClientTypeGet(BATTLE_WORK *bw,int client_no);
extern	u8					BattleWorkMineEnemyCheck(BATTLE_WORK *bw,int client_no);
extern	void				*BattleWorkMsgIconGet(BATTLE_WORK *bw);
extern	void				BattleWorkMsgIconSet(BATTLE_WORK *bw,void *icon);
extern	BOX_DATA			*BattleWorkBoxDataGet(BATTLE_WORK *bw);
extern	int					BattleWorkGroundIDGet(BATTLE_WORK *bw);
extern	int					BattleWorkBGIDGet(BATTLE_WORK *bw);
extern	int					BattleWorkPlaceIDGet(BATTLE_WORK *bw);
extern	int					BattleWorkPartnerClientNoGet(BATTLE_WORK *bw,int client_no);
extern	int					BattleWorkEnemyClientNoGet(BATTLE_WORK *bw,int client_no,int side);
extern	BOOL				BattleWorkStatusRecover(BATTLE_WORK *bw,int client_no,int sel_mons_no,int waza_pos,int item_no);
extern	u32					BattleWorkBattleStatusFlagGet(BATTLE_WORK *bw);
extern	int					BattleWorkTimeZoneGet(BATTLE_WORK *bw);
extern	int					BattleWorkTimeZoneOffsetGet(BATTLE_WORK *bw);
extern	BOOL				BattleWorkEscCanCheck(BATTLE_WORK *bw,int client_no);
extern	u16					BattleWorkShinkaCheck(BATTLE_PARAM *bp,int *sel_mons_no,int *shinka_cond);
extern	u8					BattleWorkServerFlagGet(BATTLE_WORK *bw);
extern	u8					BattleWorkSafariEscapeCountGet(BATTLE_WORK *bw);
extern	int					BattleWorkSafariBallCountGet(BATTLE_WORK *bw);
extern	void				BattleWorkSafariBallCountSet(BATTLE_WORK *bw,int count);
extern	CONFIG				*BattleWorkConfigGet(BATTLE_WORK *bw);
extern	BOOL				BattleWorkConfigWazaEffectOnOffCheck(BATTLE_WORK *bw);
extern	WINTYPE				BattleWorkConfigWinTypeGet(BATTLE_WORK *bw);
extern	u8					BattleWorkConfigMsgSpeedGet(BATTLE_WORK *bw);
extern	BATTLERULE			BattleWorkConfigBattleRuleGet(BATTLE_WORK *bw);
extern	POKE_ANM_SYS_PTR	BattleWorkPokeAnmSysPTRGet(BATTLE_WORK *bw);
extern	PERAPVOICE			*BattleWorkPerapVoiceGet(BATTLE_WORK *bw,int client_no);
extern	void				BattleWorkFormChgCheck(BATTLE_WORK *bw);
extern	void				BattleWorkAppearFlagSet(BATTLE_WORK *bw,int client_no,int sel_mons_no);
extern	void				BattleWorkPoketchDataSet(BATTLE_WORK *bw,POKEMON_PARAM *pp);
extern	void				BattleWorkTVDataSet(BATTLE_WORK *bw,POKEMON_PARAM *pp);
extern	void				BattleWorkGroundBGChg(BATTLE_WORK *bw);
extern	int					BattleWorkShinkaPlaceModeGet(BATTLE_WORK *bw);
extern	u8					*BattleWorkBGAreaGet(BATTLE_WORK *bw);
extern	u16					*BattleWorkPalAreaGet(BATTLE_WORK *bw);
extern	int					BattleWorkContestSeeFlagGet(BATTLE_WORK *bw);
extern	u16					*BattleWorkPushBGPaletteGet(BATTLE_WORK *bw);
extern	u16					*BattleWorkPushOBJPaletteGet(BATTLE_WORK *bw);
extern	int					BattleWorkWeatherGet(BATTLE_WORK *bw);
extern	u8					BattleWorkDemoSeqNoGet(BATTLE_WORK *bw);
extern	void				BattleWorkDemoSeqNoSet(BATTLE_WORK *bw,u8 data);
extern	int					BattleWorkMizukiFlagGet(BATTLE_WORK *bw);
extern	void				BattleWorkIncRecord(BATTLE_WORK *bw,int id);
extern	void				BattleWorkZukanSetScoreAdd(BATTLE_WORK *bw);
extern	int					BattleWorkCommandSelectFlagGet(BATTLE_WORK *bw);
extern	void				BattleWorkCommandSelectFlagSet(BATTLE_WORK *bw,int data);
extern	void				BattleWorkNoReshuffleClientSet(BATTLE_WORK *bw,int data);
extern	void				*BattleWorkTimeIconGet(BATTLE_WORK *bw);
extern	void				BattleWorkTimeIconSet(BATTLE_WORK *bw,void *data);
extern	BOOL				BattleWorkCustomBallCheck(BATTLE_WORK *bw,int client_no,int sel_mons_no);

extern	EXCHR_PARAM			*BattleWorkExChrClientParamGet(BATTLE_WORK *bw, int no);
extern	u8					*ExChrParamExChrBufferGet(EXCHR_PARAM *ep,int no);
extern	int					ExChrParamArcIDGet(EXCHR_PARAM *ep,int no);
extern	void				ExChrParamArcIDSet(EXCHR_PARAM *ep,int no,int data);
extern	int					ExChrParamPalIndexGet(EXCHR_PARAM *ep,int no);
extern	void				ExChrParamPalIndexSet(EXCHR_PARAM *ep,int no,int data);
extern	int					ExChrParamHeightGet(EXCHR_PARAM *ep,int no);
extern	void				ExChrParamHeightSet(EXCHR_PARAM *ep,int no,int data);

extern	void				BattleWorkProcModeSet(BATTLE_WORK *bw,int mode);
extern	void				BattleWorkTSSSeqNoAdrsSet(BATTLE_WORK *bw,u8 *seq_no);
extern	void				BattleWorkTSRSeqNoAdrsSet(BATTLE_WORK *bw,u8 *seq_no);
extern	void				BattleWorkTSSSeqNoSet(BATTLE_WORK *bw,u8 seq_no);
extern	void				BattleWorkTSRSeqNoSet(BATTLE_WORK *bw,u8 seq_no);
extern	void				BattleWorkFightEndFlagSet(BATTLE_WORK *bw,u8 data);
extern	void				BattleWorkGaugeInit(BATTLE_WORK *bw);
extern	void				BattleWorkGaugeOn(BATTLE_WORK *bw);
extern	void				BattleWorkGaugeOff(BATTLE_WORK *bw);
extern	void				BattleWorkGaugeDelete(BATTLE_WORK *bw);
extern	u8					BattleWorkWinLoseGet(BATTLE_WORK *bw);
extern	void				BattleWorkWinLoseSet(BATTLE_WORK *bw,u8 flag);
extern	u8					BattleWorkPinchSEFlagGet(BATTLE_WORK *bw);
extern	void				BattleWorkPinchSEFlagSet(BATTLE_WORK *bw,u8 flag);
extern	u8					BattleWorkPinchSEWaitGet(BATTLE_WORK *bw);
extern	void				BattleWorkPinchSEWaitSet(BATTLE_WORK *bw,u8 flag);
extern	void				BattleWorkGetPokemonClientSet(BATTLE_WORK *bw,int client_no);

extern	void				BattleClientNoBufMake(BATTLE_WORK *bw,u8 *buf);
extern	void				BattleClientTypeBufMake(BATTLE_WORK *bw,u8 *buf);
extern	void				BattleSoftSpriteBufMake(BATTLE_WORK *bw,SOFT_SPRITE **buf);

extern	void				BattleGaugePriSet(BATTLE_WORK *bw,int pri);
extern	u32					CalcLosePenalty(POKEPARTY *ppt,MYSTATUS *my_status);

extern	void				FT_ZukanFlagSetSee(BATTLE_WORK *bw,int client_no);
extern	void				FT_ZukanFlagSetGet(BATTLE_WORK *bw,int client_no);
extern	BOOL				FT_ZukanFlagCheckGet(BATTLE_WORK *bw,int mons_no);

extern	void				BattleDefaultBlendSet(void);

extern	u8					TrainerMSG_Print(BATTLE_WORK *bw,int tr_id,int client_no,int msg_type,int wait);
extern	u8					BattleMSG_Print(BATTLE_WORK *bw,MSGDATA_MANAGER *msg_m,MESSAGE_PARAM *mp,int wait);
extern	u8					StatusMSG_Print(BATTLE_WORK *bw,GF_BGL_BMPWIN *win,MSGDATA_MANAGER *msg_m,MESSAGE_PARAM *mp,
											  int x,int y,int flag,int width,int wait);
extern void *	BattleWorkGaugeWorkGet(BATTLE_WORK *bw, int client_no);

#endif __FIGHT_TOOL_H_
