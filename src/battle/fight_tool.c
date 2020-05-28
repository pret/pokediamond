
//============================================================================================
/**
 * @file	fight_tool.c
 * @bfief	�퓬�V�X�e���p�c�[���v���O����
 * @author	HisashiSogabe
 * @date	05.07.22
 */
//============================================================================================

#include "common.h"
#include "battle/battle_server.h"
#include "battle/fight.h"
#include "battle/fight_def.h"
#include "battle/client_tool.h"
#include "battle/server_tool.h"
#include "battle/attr_def.h"

#include "field/poketch_data.h"
#include "field/tvtopic_battle.h"

#include "gflib/strbuf_family.h"

#include "poketool/pokeparty.h"
#include "poketool/tr_tool.h"

#include "system/mystatus.h"
#include "system/numfont.h"
#include "system/fontproc.h"
#include "system/msgdata.h"
#include "system/snd_tool.h"
#include "system/timezone.h"
#include "system/wordset.h"
#include "system/zukanwork.h"
#include "msgdata/msg.naix"
#include "savedata/config.h"
#include "savedata/record.h"
#include "wazaeffect/we_mana.h"

#include "gauge.h"

#include "itemtool\item.h"

//============================================================================================
//	�v���g�^�C�v�錾
//============================================================================================

GF_BGL_INI			*BattleWorkGF_BGL_INIGet(BATTLE_WORK *bw);
GF_BGL_BMPWIN		*BattleWorkGF_BGL_BMPWINGet(BATTLE_WORK *bw,int no);
u32					BattleWorkFightTypeGet(BATTLE_WORK *bw);
SERVER_PARAM		*BattleWorkServerParamGet(BATTLE_WORK *bw);
CLIENT_PARAM		*BattleWorkClientParamGet(BATTLE_WORK *bw,int client_no);
int					BattleWorkClientSetMaxGet(BATTLE_WORK *bw);
POKEPARTY			*BattleWorkPokePartyGet(BATTLE_WORK *bw,int client_no);
int					BattleWorkPokeCountGet(BATTLE_WORK *bw,int client_no);
POKEMON_PARAM		*BattleWorkPokemonParamGet(BATTLE_WORK *bw,int client_no,int sel_mons_no);
SOFT_SPRITE_MANAGER	*BattleWorkSoftSpriteManagerGet(BATTLE_WORK *bw);
WE_SYS_PTR			BattleWorkWE_SYS_PTRGet(BATTLE_WORK *bw);
CATS_SYS_PTR		BattleWorkCATS_SYS_PTRGet(BATTLE_WORK *bw);
CATS_RES_PTR		BattleWorkCATS_RES_PTRGet(BATTLE_WORK *bw);
GROUND_WORK			*BattleWorkGroundWorkGet(BATTLE_WORK *bw,int ground_no);
BI_PARAM_PTR		BattleWorkGF_BGL_BIPGet(BATTLE_WORK *bw);
NUMFONT				*BattleWorkGF_BGL_NumFontHPGet(BATTLE_WORK *bw);
NUMFONT				*BattleWorkGF_BGL_NumFontLVGet(BATTLE_WORK *bw);
MSGDATA_MANAGER		*BattleWorkFightMsgGet(BATTLE_WORK *bw);
MSGDATA_MANAGER		*BattleWorkAttackMsgGet(BATTLE_WORK *bw);
PALETTE_FADE_PTR	BattleWorkPfdGet(BATTLE_WORK *bw);
ZUKAN_WORK			*BattleWorkZukanWorkGet(BATTLE_WORK *bw);
u8					*BattleWorkSioSendBufGet(BATTLE_WORK *bw);
u8					*BattleWorkSioRecvBufGet(BATTLE_WORK *bw);
u16					*BattleWorkSioSendReadGet(BATTLE_WORK *bw);
u16					*BattleWorkSioSendWriteGet(BATTLE_WORK *bw);
u16					*BattleWorkSioSendOverGet(BATTLE_WORK *bw);
u16					*BattleWorkSioRecvReadGet(BATTLE_WORK *bw);
u16					*BattleWorkSioRecvWriteGet(BATTLE_WORK *bw);
u16					*BattleWorkSioRecvOverGet(BATTLE_WORK *bw);
EXCHR_PARAM			*BattleWorkExChrParamGet(BATTLE_WORK *bw);
WORDSET				*BattleWorkWORDSETGet(BATTLE_WORK *bw);
STRBUF				*BattleWorkSTRBUFGet(BATTLE_WORK *bw);
u16					BattleWorkTrainerIDGet(BATTLE_WORK *bw,int client_no);
TRAINER_DATA		*BattleWorkTrainerDataGet(BATTLE_WORK *bw,int client_no);
MYSTATUS			*BattleWorkMyStatusGet(BATTLE_WORK *bw,int client_no);
MYITEM				*BattleWorkMyItemGet(BATTLE_WORK *bw);
BAG_CURSOR			*BattleWorkBagCursorGet(BATTLE_WORK *bw);
u32					BattleWorkMySexGet(BATTLE_WORK *bw,int client_no);
int					BattleWorkClientNoGet(BATTLE_WORK *bw,int client_type);
u8					BattleWorkClientTypeGet(BATTLE_WORK *bw,int client_no);
u8					BattleWorkMineEnemyCheck(BATTLE_WORK *bw,int client_no);
void				*BattleWorkMsgIconGet(BATTLE_WORK *bw);
void				BattleWorkMsgIconSet(BATTLE_WORK *bw,void *icon);
BOX_DATA			*BattleWorkBoxDataGet(BATTLE_WORK *bw);
int					BattleWorkGroundIDGet(BATTLE_WORK *bw);
int					BattleWorkBGIDGet(BATTLE_WORK *bw);
int					BattleWorkPlaceIDGet(BATTLE_WORK *bw);
int					BattleWorkPartnerClientNoGet(BATTLE_WORK *bw,int client_no);
int					BattleWorkEnemyClientNoGet(BATTLE_WORK *bw,int client_no,int side);
BOOL				BattleWorkStatusRecover(BATTLE_WORK *bw,int client_no,int sel_mons_no,int waza_pos,int item_no);
u32					BattleWorkBattleStatusFlagGet(BATTLE_WORK *bw);
int					BattleWorkTimeZoneGet(BATTLE_WORK *bw);
int					BattleWorkTimeZoneOffsetGet(BATTLE_WORK *bw);
BOOL				BattleWorkEscCanCheck(BATTLE_WORK *bw,int client_no);
u16					BattleWorkShinkaCheck(BATTLE_PARAM *bp,int *sel_mons_no,int *shinka_cond);
u8					BattleWorkServerFlagGet(BATTLE_WORK *bw);
u8					BattleWorkSafariEscapeCountGet(BATTLE_WORK *bw);
int					BattleWorkSafariBallCountGet(BATTLE_WORK *bw);
void				BattleWorkSafariBallCountSet(BATTLE_WORK *bw,int count);
CONFIG				*BattleWorkConfigGet(BATTLE_WORK *bw);
BOOL				BattleWorkConfigWazaEffectOnOffCheck(BATTLE_WORK *bw);
WINTYPE				BattleWorkConfigWinTypeGet(BATTLE_WORK *bw);
u8					BattleWorkConfigMsgSpeedGet(BATTLE_WORK *bw);
BATTLERULE			BattleWorkConfigBattleRuleGet(BATTLE_WORK *bw);
POKE_ANM_SYS_PTR	BattleWorkPokeAnmSysPTRGet(BATTLE_WORK *bw);
PERAPVOICE			*BattleWorkPerapVoiceGet(BATTLE_WORK *bw,int client_no);
void				BattleWorkFormChgCheck(BATTLE_WORK *bw);
void				BattleWorkAppearFlagSet(BATTLE_WORK *bw,int client_no,int sel_mons_no);
void				BattleWorkPoketchDataSet(BATTLE_WORK *bw,POKEMON_PARAM *pp);
void				BattleWorkTVDataSet(BATTLE_WORK *bw,POKEMON_PARAM *pp);
void				BattleWorkGroundBGChg(BATTLE_WORK *bw);
int					BattleWorkShinkaPlaceModeGet(BATTLE_WORK *bw);
u8					*BattleWorkBGAreaGet(BATTLE_WORK *bw);
u16					*BattleWorkPalAreaGet(BATTLE_WORK *bw);
int					BattleWorkContestSeeFlagGet(BATTLE_WORK *bw);
u16					*BattleWorkPushBGPaletteGet(BATTLE_WORK *bw);
u16					*BattleWorkPushOBJPaletteGet(BATTLE_WORK *bw);
int					BattleWorkWeatherGet(BATTLE_WORK *bw);
u8					BattleWorkDemoSeqNoGet(BATTLE_WORK *bw);
void				BattleWorkDemoSeqNoSet(BATTLE_WORK *bw,u8 data);
int					BattleWorkMizukiFlagGet(BATTLE_WORK *bw);
void				BattleWorkIncRecord(BATTLE_WORK *bw,int id);
void				BattleWorkZukanSetScoreAdd(BATTLE_WORK *bw);
int					BattleWorkCommandSelectFlagGet(BATTLE_WORK *bw);
void				BattleWorkCommandSelectFlagSet(BATTLE_WORK *bw,int data);
void				BattleWorkNoReshuffleClientSet(BATTLE_WORK *bw,int data);
void				*BattleWorkTimeIconGet(BATTLE_WORK *bw);
void				BattleWorkTimeIconSet(BATTLE_WORK *bw,void *data);
BOOL				BattleWorkCustomBallCheck(BATTLE_WORK *bw,int client_no,int sel_mons_no);

u8					*ExChrParamExChrBufferGet(EXCHR_PARAM *ep,int no);
int					ExChrParamArcIDGet(EXCHR_PARAM *ep,int no);
void				ExChrParamArcIDSet(EXCHR_PARAM *ep,int no,int data);
int					ExChrParamPalIndexGet(EXCHR_PARAM *ep,int no);
void				ExChrParamPalIndexSet(EXCHR_PARAM *ep,int no,int data);
int					ExChrParamHeightGet(EXCHR_PARAM *ep,int no);
void				ExChrParamHeightSet(EXCHR_PARAM *ep,int no,int data);

void				BattleWorkProcModeSet(BATTLE_WORK *bw,int mode);
void				BattleWorkTSSSeqNoAdrsSet(BATTLE_WORK *bw,u8 *seq_no);
void				BattleWorkTSRSeqNoAdrsSet(BATTLE_WORK *bw,u8 *seq_no);
void				BattleWorkTSSSeqNoSet(BATTLE_WORK *bw,u8 seq_no);
void				BattleWorkTSRSeqNoSet(BATTLE_WORK *bw,u8 seq_no);
void				BattleWorkFightEndFlagSet(BATTLE_WORK *bw,u8 data);
void				BattleWorkGaugeInit(BATTLE_WORK *bw);
void				BattleWorkGaugeOn(BATTLE_WORK *bw);
void				BattleWorkGaugeOff(BATTLE_WORK *bw);
void				BattleWorkGaugeDelete(BATTLE_WORK *bw);
u8					BattleWorkWinLoseGet(BATTLE_WORK *bw);
void				BattleWorkWinLoseSet(BATTLE_WORK *bw,u8 flag);
u8					BattleWorkPinchSEFlagGet(BATTLE_WORK *bw);
void				BattleWorkPinchSEFlagSet(BATTLE_WORK *bw,u8 flag);
u8					BattleWorkPinchSEWaitGet(BATTLE_WORK *bw);
void				BattleWorkPinchSEWaitSet(BATTLE_WORK *bw,u8 flag);
void				BattleWorkGetPokemonClientSet(BATTLE_WORK *bw,int client_no);

void				BattleClientNoBufMake(BATTLE_WORK *bw,u8 *buf);
void				BattleClientTypeBufMake(BATTLE_WORK *bw,u8 *buf);
void				BattleSoftSpriteBufMake(BATTLE_WORK *bw,SOFT_SPRITE **buf);

void				BattleGaugePriSet(BATTLE_WORK *bw,int pri);
u32					CalcLosePenalty(POKEPARTY *ppt,MYSTATUS *my_status);

void				FT_ZukanFlagSetSee(BATTLE_WORK *bw,int client_no);
void				FT_ZukanFlagSetGet(BATTLE_WORK *bw,int client_no);
BOOL				FT_ZukanFlagCheckGet(BATTLE_WORK *bw,int mons_no);

void				BattleDefaultBlendSet(void);

u8					TrainerMSG_Print(BATTLE_WORK *bw,int tr_id,int client_no,int msg_type,int wait);
u8					BattleMSG_Print(BATTLE_WORK *bw,MSGDATA_MANAGER *msg_m,MESSAGE_PARAM *mp,int wait);
u8					StatusMSG_Print(BATTLE_WORK *bw,GF_BGL_BMPWIN *win,MSGDATA_MANAGER *msg_m,MESSAGE_PARAM *mp,
									  int x,int y,int flag,int width,int wait);

static	void	BattleMSG_DirCheck(BATTLE_WORK *bw,MESSAGE_PARAM *mp);
static	void	BattleMSG_TagExpand(BATTLE_WORK *bw,MESSAGE_PARAM *mp);
static	void	BattleMSG_MsgExpand(BATTLE_WORK *bw,MSGDATA_MANAGER *msg_m,MESSAGE_PARAM *mp);
static	BOOL	BattleMSG_CallBack(MSG_PRINT_HEADER *mph,u16 value);

static	void	BattleMSG_NicknameGet(BATTLE_WORK *bw,	u32 buf_id,int para);
static	void	BattleMSG_WazaGet(BATTLE_WORK *bw,		u32 buf_id,int para);
static	void	BattleMSG_ItemGet(BATTLE_WORK *bw,		u32 buf_id,int para);
static	void	BattleMSG_NumGet(BATTLE_WORK *bw,		u32 buf_id,int para);
static	void	BattleMSG_NumsGet(BATTLE_WORK *bw,		u32 buf_id,int para,int keta);
static	void	BattleMSG_TypeGet(BATTLE_WORK *bw,		u32 buf_id,int para);
static	void	BattleMSG_TokuseiGet(BATTLE_WORK *bw,	u32 buf_id,int para);
static	void	BattleMSG_StatusGet(BATTLE_WORK *bw,	u32 buf_id,int para);
static	void	BattleMSG_ConditionGet(BATTLE_WORK *bw,	u32 buf_id,int para);
static	void	BattleMSG_PokenameGet(BATTLE_WORK *bw,	u32 buf_id,int para);
static	void	BattleMSG_PolockGet(BATTLE_WORK *bw,	u32 buf_id,int para);
static	void	BattleMSG_TasteGet(BATTLE_WORK *bw,		u32 buf_id,int para);
static	void	BattleMSG_TRTypeGet(BATTLE_WORK *bw,	u32 buf_id,int para);
static	void	BattleMSG_TRNameGet(BATTLE_WORK *bw,	u32 buf_id,int para);
static	void	BattleMSG_BoxNameGet(BATTLE_WORK *bw,	u32 buf_id,int para);

//============================================================================================
//	BattleWork�\���̃��[�N�擾�֐��Q
//============================================================================================
//============================================================================================
/**
 *	GF_BGL_INI���擾
 *
 * @param[in]	bw		�퓬���[�N�\����
 *
 * @retval	bgl
 */
//============================================================================================
GF_BGL_INI	*BattleWorkGF_BGL_INIGet(BATTLE_WORK *bw)
{
	return	bw->bgl;
}

//============================================================================================
/**
 *	GF_BGL_BMPWIN���擾
 *
 * @param[in]	bw		�퓬���[�N�\����
 * @param[in]	no		�擾����WinNo
 *
 * @retval	win
 */
//============================================================================================
GF_BGL_BMPWIN	*BattleWorkGF_BGL_BMPWINGet(BATTLE_WORK *bw,int no)
{
	return	&bw->win[no];
}

//============================================================================================
/**
 *	fight_type���擾
 *
 * @param[in]	bw		�퓬���[�N�\����
 *
 * @retval	fight_type
 */
//============================================================================================
u32	BattleWorkFightTypeGet(BATTLE_WORK *bw)
{
	return	bw->fight_type;
}

//============================================================================================
/**
 *	server_param���擾
 *
 * @param[in]	bw		�퓬���[�N�\����
 *
 * @retval	server_param
 */
//============================================================================================
SERVER_PARAM	*BattleWorkServerParamGet(BATTLE_WORK *bw)
{
	return	bw->server_param;
}

//============================================================================================
/**
 *	client_param���擾
 *
 * @param[in]	bw			�퓬���[�N�\����
 * @param[in]	client_no	�擾������client_no
 *
 * @retval	client_param
 */
//============================================================================================
CLIENT_PARAM	*BattleWorkClientParamGet(BATTLE_WORK *bw,int client_no)
{
	return	bw->client_param[client_no];
}

//============================================================================================
/**
 *	client_set_max���擾
 *
 * @param[in]	bw		�퓬���[�N�\����
 *
 * @retval	client_set_max
 */
//============================================================================================
int	BattleWorkClientSetMaxGet(BATTLE_WORK *bw)
{
	return	bw->client_set_max;
}

//============================================================================================
/**
 *	POKEPARTY���擾
 *
 * @param[in]	bw			�퓬���[�N�\����
 * @param[in]	client_no	�擾����client_no
 *
 * @retval	poke_party[client_no]
 */
//============================================================================================
POKEPARTY		*BattleWorkPokePartyGet(BATTLE_WORK *bw,int client_no)
{
	if((bw->fight_type&FIGHT_TYPE_MULTI)||
	  ((bw->fight_type&FIGHT_TYPE_TAG)&&(BattleWorkClientTypeGet(bw,client_no)&CLIENT_ENEMY_FLAG))){
		return	bw->poke_party[client_no];
	}
	else if(bw->fight_type&FIGHT_TYPE_2vs2){
		return	bw->poke_party[client_no&1];
	}
	else{
		return	bw->poke_party[client_no];
	}
}

//============================================================================================
/**
 *	PokeCount���擾
 *
 * @param[in]	bw			�퓬���[�N�\����
 * @param[in]	client_no	�擾����client_no
 *
 * @retval	poke_party[client_no]->PokeCount
 */
//============================================================================================
int	BattleWorkPokeCountGet(BATTLE_WORK *bw,int client_no)
{
	if((bw->fight_type&FIGHT_TYPE_MULTI)||
	  ((bw->fight_type&FIGHT_TYPE_TAG)&&(BattleWorkClientTypeGet(bw,client_no)&CLIENT_ENEMY_FLAG))){
		return	PokeParty_GetPokeCount(bw->poke_party[client_no]);
	}
	else if(bw->fight_type&FIGHT_TYPE_2vs2){
		return	PokeParty_GetPokeCount(bw->poke_party[client_no&1]);
	}
	else{
		return	PokeParty_GetPokeCount(bw->poke_party[client_no]);
	}
}

//============================================================================================
/**
 *	PokemonParam���擾
 *
 * @param[in]	bw			�퓬���[�N�\����
 * @param[in]	client_no	�擾����client_no
 * @param[in]	sel_mons_no	�擾����PokemonParam�̐擪����̈ʒu
 *
 * @retval	pp[client_no][sel_mons_no]
 */
//============================================================================================
POKEMON_PARAM	*BattleWorkPokemonParamGet(BATTLE_WORK *bw,int client_no,int sel_mons_no)
{
	if((bw->fight_type&FIGHT_TYPE_MULTI)||
	  ((bw->fight_type&FIGHT_TYPE_TAG)&&(BattleWorkClientTypeGet(bw,client_no)&CLIENT_ENEMY_FLAG))){
		return	PokeParty_GetMemberPointer(bw->poke_party[client_no],sel_mons_no);
	}
	else if(bw->fight_type&FIGHT_TYPE_2vs2){
		return	PokeParty_GetMemberPointer(bw->poke_party[client_no&1],sel_mons_no);
	}
	else{
		return	PokeParty_GetMemberPointer(bw->poke_party[client_no],sel_mons_no);
	}
}

//============================================================================================
/**
 *	soft_sprite_manager���擾
 *
 * @param[in]	bw		�퓬���[�N�\����
 *
 * @retval	soft_sprite_manager
 */
//============================================================================================
SOFT_SPRITE_MANAGER	*BattleWorkSoftSpriteManagerGet(BATTLE_WORK *bw)
{
	return	bw->soft_sprite;
}

//============================================================================================
/**
 *	wsp���擾
 *
 * @param[in]	bw		�퓬���[�N�\����
 *
 * @retval	wsp
 */
//============================================================================================
WE_SYS_PTR	BattleWorkWE_SYS_PTRGet(BATTLE_WORK *bw)
{
	return bw->wsp;
}

//============================================================================================
/**
 *	csp���擾
 *
 * @param[in]	bw		�퓬���[�N�\����
 *
 * @retval	csp
 */
//============================================================================================
CATS_SYS_PTR		BattleWorkCATS_SYS_PTRGet(BATTLE_WORK *bw)
{
	return bw->csp;
}

//============================================================================================
/**
 *	csp���擾
 *
 * @param[in]	bw		�퓬���[�N�\����
 *
 * @retval	crp
 */
//============================================================================================
CATS_RES_PTR		BattleWorkCATS_RES_PTRGet(BATTLE_WORK *bw)
{
	return bw->crp;
}

//============================================================================================
/**
 *	GROUND_WORK���擾
 *
 * @param[in]	bw			�퓬���[�N�\����
 * @param[in]	ground_no	GroundNo
 *
 * @retval	GROUND_WORK
 */
//============================================================================================
GROUND_WORK			*BattleWorkGroundWorkGet(BATTLE_WORK *bw,int ground_no)
{
	return &bw->ground[ground_no];
}

//============================================================================================
/**
 *	bip���擾
 *
 * @param[in]	bw		�퓬���[�N�\����
 *
 * @retval	bip
 */
//============================================================================================
BI_PARAM_PTR	BattleWorkGF_BGL_BIPGet(BATTLE_WORK *bw)
{
	return	bw->bip;
}

//============================================================================================
/**
 *	tg���擾
 *
 * @param[in]	bw		�퓬���[�N�\����
 * @param[in]	side	
 *
 * @retval	tg
 */
//============================================================================================
TEMOTIGAUGE_PTR	BattleWorkGF_BGL_TGGet(BATTLE_WORK *bw, TEMOTI_SIDE side)
{
	return	bw->tg[side];
}

//============================================================================================
/**
 *	tg���Z�b�g
 *
 * @param[in]	bw		�퓬���[�N�\����
 * @param[in]	side	
 * @param[in]	tg		�莝���Q�[�W���[�N�ւ̃|�C���^
 */
//============================================================================================
void	BattleWorkGF_BGL_TGSet(BATTLE_WORK *bw, TEMOTI_SIDE side, TEMOTIGAUGE_PTR tg)
{
	bw->tg[side] = tg;
}

//============================================================================================
/**
 *	numfont_hp���擾
 *
 * @param[in]	bw		�퓬���[�N�\����
 *
 * @retval	numfont_hp
 */
//============================================================================================
NUMFONT *	BattleWorkGF_BGL_NumFontHPGet(BATTLE_WORK *bw)
{
	return	bw->numfont_hp;
}

//============================================================================================
/**
 *	numfont_lv���擾
 *
 * @param[in]	bw		�퓬���[�N�\����
 *
 * @retval	numfont_lv
 */
//============================================================================================
NUMFONT *	BattleWorkGF_BGL_NumFontLVGet(BATTLE_WORK *bw)
{
	return	bw->numfont_lv;
}

//============================================================================================
/**
 *	fight_msg���擾
 *
 * @param[in]	bw		�퓬���[�N�\����
 *
 * @retval	fight_msg
 */
//============================================================================================
MSGDATA_MANAGER		*BattleWorkFightMsgGet(BATTLE_WORK *bw)
{
	return bw->fight_msg;
}

//============================================================================================
/**
 *	attack_msg���擾
 *
 * @param[in]	bw		�퓬���[�N�\����
 *
 * @retval	attack_msg
 */
//============================================================================================
MSGDATA_MANAGER		*BattleWorkAttackMsgGet(BATTLE_WORK *bw)
{
	return bw->attack_msg;
}

//============================================================================================
/**
 *	pfd���擾
 *
 * @param[in]	bw		�퓬���[�N�\����
 *
 * @retval	pfd
 */
//============================================================================================
PALETTE_FADE_PTR		BattleWorkPfdGet(BATTLE_WORK *bw)
{
	return bw->pfd;
}

//============================================================================================
/**
 *	ZUKAN_WORK���擾
 *
 * @param[in]	bw		�퓬���[�N�\����
 *
 * @retval	zw
 */
//============================================================================================
ZUKAN_WORK	*BattleWorkZukanWorkGet(BATTLE_WORK *bw)
{
#ifdef PM_DEBUG
	GF_ASSERT(bw->zw!=NULL);
#endif
	return bw->zw;
}

//============================================================================================
/**
 *	sio_send_buffer���擾
 *
 * @param[in]	bw		�퓬���[�N�\����
 *
 * @retval	sio_send_buffer
 */
//============================================================================================
u8	*BattleWorkSioSendBufGet(BATTLE_WORK *bw)
{
	return &bw->sio_send_buffer[0];
}

//============================================================================================
/**
 *	sio_recv_buffer���擾
 *
 * @param[in]	bw		�퓬���[�N�\����
 *
 * @retval	sio_recv_buffer
 */
//============================================================================================
u8	*BattleWorkSioRecvBufGet(BATTLE_WORK *bw)
{
	return &bw->sio_recv_buffer[0];
}

//============================================================================================
/**
 *	sio_send_read���擾
 *
 * @param[in]	bw		�퓬���[�N�\����
 *
 * @retval	sio_send_read
 */
//============================================================================================
u16	*BattleWorkSioSendReadGet(BATTLE_WORK *bw)
{
	return &bw->sio_send_read;
}

//============================================================================================
/**
 *	sio_send_write���擾
 *
 * @param[in]	bw		�퓬���[�N�\����
 *
 * @retval	sio_send_write
 */
//============================================================================================
u16	*BattleWorkSioSendWriteGet(BATTLE_WORK *bw)
{
	return &bw->sio_send_write;
}

//============================================================================================
/**
 *	sio_send_over���擾
 *
 * @param[in]	bw		�퓬���[�N�\����
 *
 * @retval	sio_send_over
 */
//============================================================================================
u16	*BattleWorkSioSendOverGet(BATTLE_WORK *bw)
{
	return &bw->sio_send_over;
}

//============================================================================================
/**
 *	sio_recv_read���擾
 *
 * @param[in]	bw		�퓬���[�N�\����
 *
 * @retval	sio_recv_read
 */
//============================================================================================
u16	*BattleWorkSioRecvReadGet(BATTLE_WORK *bw)
{
	return &bw->sio_recv_read;
}

//============================================================================================
/**
 *	sio_recv_write���擾
 *
 * @param[in]	bw		�퓬���[�N�\����
 *
 * @retval	sio_recv_write
 */
//============================================================================================
u16	*BattleWorkSioRecvWriteGet(BATTLE_WORK *bw)
{
	return &bw->sio_recv_write;
}

//============================================================================================
/**
 *	sio_recv_over���擾
 *
 * @param[in]	bw		�퓬���[�N�\����
 *
 * @retval	sio_recv_over
 */
//============================================================================================
u16	*BattleWorkSioRecvOverGet(BATTLE_WORK *bw)
{
	return &bw->sio_recv_over;
}

//============================================================================================
/**
 *	exchr_param���擾
 *
 * @param[in]	bw		�퓬���[�N�\����
 *
 * @retval	exchr_buffer
 */
//============================================================================================
EXCHR_PARAM	*BattleWorkExChrParamGet(BATTLE_WORK *bw)
{
	return &bw->exchr_param[0];
}

//============================================================================================
/**
 *	wordset���擾
 *
 * @param[in]	bw		�퓬���[�N�\����
 *
 * @retval	wordset
 */
//============================================================================================
WORDSET	*BattleWorkWORDSETGet(BATTLE_WORK *bw)
{
	return bw->wordset;
}

//============================================================================================
/**
 *	strbuf���擾
 *
 * @param[in]	bw		�퓬���[�N�\����
 *
 * @retval	msg_buf
 */
//============================================================================================
STRBUF	*BattleWorkSTRBUFGet(BATTLE_WORK *bw)
{
	return bw->msg_buf;
}

//============================================================================================
/**
 *	�g���[�i�[ID���擾
 *
 * @param[in]	bw			�퓬���[�N�\����
 * @param[in]	client_no	�擾����ClientNo
 *
 * @retval	trainer_id
 */
//============================================================================================
u16	BattleWorkTrainerIDGet(BATTLE_WORK *bw,int client_no)
{
	if((bw->fight_type&FIGHT_TYPE_MULTI)||
	  ((bw->fight_type&FIGHT_TYPE_TAG)&&(BattleWorkClientTypeGet(bw,client_no)&CLIENT_ENEMY_FLAG))){
		return bw->trainer_id[client_no];
	}
	else if(bw->fight_type&FIGHT_TYPE_2vs2){
		return bw->trainer_id[client_no&1];
	}
	else{
		return bw->trainer_id[client_no];
	}
}

//============================================================================================
/**
 *	TRAINER_DATA���擾
 *
 * @param[in]	bw			�퓬���[�N�\����
 * @param[in]	client_no	�擾����TRAINER_DATA��ClientNo
 *
 * @retval	trainer_data
 */
//============================================================================================
TRAINER_DATA	*BattleWorkTrainerDataGet(BATTLE_WORK *bw,int client_no)
{
	if((bw->fight_type&FIGHT_TYPE_MULTI)||
	  ((bw->fight_type&FIGHT_TYPE_TAG)&&(BattleWorkClientTypeGet(bw,client_no)&CLIENT_ENEMY_FLAG))){
		return &bw->trainer_data[client_no];
	}
	else if(bw->fight_type&FIGHT_TYPE_2vs2){
		return &bw->trainer_data[client_no&1];
	}
	else{
		return &bw->trainer_data[client_no];
	}
}

//============================================================================================
/**
 *	�}�C�X�e�[�^�X���擾
 *
 * @param[in]	bw			�퓬���[�N�\����
 * @param[in]	client_no	�擾����ClientNo
 *
 * @retval	my_item
 */
//============================================================================================
MYSTATUS	*BattleWorkMyStatusGet(BATTLE_WORK *bw,int client_no)
{
	if((bw->fight_type&FIGHT_TYPE_MULTI)||
	  ((bw->fight_type&FIGHT_TYPE_TAG)&&(BattleWorkClientTypeGet(bw,client_no)&CLIENT_ENEMY_FLAG))){
#ifdef PM_DEBUG
		GF_ASSERT(bw->my_status[client_no]!=NULL);
#endif
		return bw->my_status[client_no];
	}
	else if(bw->fight_type&FIGHT_TYPE_2vs2){
#ifdef PM_DEBUG
		GF_ASSERT(bw->my_status[client_no&1]!=NULL);
#endif
		return bw->my_status[client_no&1];
	}
	else{
#ifdef PM_DEBUG
		GF_ASSERT(bw->my_status[client_no]!=NULL);
#endif
		return bw->my_status[client_no];
	}
}

//============================================================================================
/**
 *	�莝���A�C�e�����擾
 *
 * @param[in]	bw			�퓬���[�N�\����
 *
 * @retval	my_item
 */
//============================================================================================
MYITEM	*BattleWorkMyItemGet(BATTLE_WORK *bw)
{
#ifdef PM_DEBUG
	GF_ASSERT(bw->my_item!=NULL);
#endif
	return bw->my_item;
}

//============================================================================================
/**
 *	�o�b�O�J�[�\�����擾
 *
 * @param[in]	bw			�퓬���[�N�\����
 *
 * @retval	bag_cursor
 */
//============================================================================================
BAG_CURSOR	*BattleWorkBagCursorGet(BATTLE_WORK *bw)
{
#ifdef PM_DEBUG
	GF_ASSERT(bw->bag_cursor!=NULL);
#endif
	return bw->bag_cursor;
}

//============================================================================================
/**
 *	�}�C�f�[�^�̐��ʂ��擾
 *
 * @param[in]	bw			�퓬���[�N�\����
 *
 * @retval	�����̐���
 */
//============================================================================================
u32	BattleWorkMySexGet(BATTLE_WORK *bw,int client_no)
{
#ifdef PM_DEBUG
	GF_ASSERT(bw->my_status[client_no]!=NULL);
#endif
	return MyStatus_GetMySex(bw->my_status[client_no]);
}

//============================================================================================
/**
 *	ClientType����ClientNo���擾
 *
 * @param[in]	bw			�퓬���[�N�\����
 * @param[in]	client_no	ClientNo���擾����ClientType
 *
 * @retval	ClientNo
 */
//============================================================================================
int	BattleWorkClientNoGet(BATTLE_WORK *bw,int client_type)
{
	int	client_no;

	for(client_no=0;client_no<bw->client_set_max;client_no++){
		if(CT_CPClientTypeGet(bw->client_param[client_no])==client_type){
			break;
		}
	}

	GF_ASSERT(client_no<bw->client_set_max);

	return client_no;
}

//============================================================================================
/**
 *	ClientType���擾
 *
 * @param[in]	bw			�퓬���[�N�\����
 * @param[in]	client_no	ClientType���擾����ClientNo
 *
 * @retval	ClientType
 */
//============================================================================================
u8	BattleWorkClientTypeGet(BATTLE_WORK *bw,int client_no)
{
	return CT_CPClientTypeGet(bw->client_param[client_no]);
}

//============================================================================================
/**
 *	�G���������������擾
 *
 * @param[in]	bw			�퓬���[�N�\����
 * @param[in]	client_no	�擾����ClientNo
 *
 * @retval	0:�����@1:�G
 */
//============================================================================================
u8	BattleWorkMineEnemyCheck(BATTLE_WORK *bw,int client_no)
{
	return CT_CPClientTypeGet(bw->client_param[client_no])&1;
}

//============================================================================================
/**
 *	���b�Z�[�W�E�C���h�E�pDS�A�C�R���L�����̃|�C���^���擾
 *
 * @param[in]	bw			�퓬���[�N�\����
 *
 * @retval	bw->msg_icon
 */
//============================================================================================
void	*BattleWorkMsgIconGet(BATTLE_WORK *bw)
{
#ifdef PM_DEBUG
	GF_ASSERT(bw->msg_icon!=NULL);
#endif
	return bw->msg_icon;
}

//============================================================================================
/**
 *	���b�Z�[�W�E�C���h�E�pDS�A�C�R���L�����̃|�C���^���擾
 *
 * @param[in]	bw			�퓬���[�N�\����
 *
 * @retval	bw->msg_icon
 */
//============================================================================================
void	BattleWorkMsgIconSet(BATTLE_WORK *bw,void *icon)
{
	bw->msg_icon=icon;
}

//============================================================================================
/**
 *	�{�b�N�X�\���̃|�C���^���擾
 *
 * @param[in]	bw			�퓬���[�N�\����
 *
 * @retval	bw->box
 */
//============================================================================================
BOX_DATA	*BattleWorkBoxDataGet(BATTLE_WORK *bw)
{
#ifdef PM_DEBUG
	GF_ASSERT(bw->box!=NULL);
#endif
	return bw->box;
}

//============================================================================================
/**
 *	ground_id���擾
 *
 * @param[in]	bw			�퓬���[�N�\����
 *
 * @retval	bw->ground_id
 */
//============================================================================================
int	BattleWorkGroundIDGet(BATTLE_WORK *bw)
{
	if((bw->ground_id>GROUND_ID_ALL)||(bw->ground_id<0)){
		return GROUND_ID_ALL;
	}
	return	bw->ground_id;
}

//============================================================================================
/**
 *	bg_id���擾
 *
 * @param[in]	bw			�퓬���[�N�\����
 *
 * @retval	bw->bg_id
 */
//============================================================================================
int	BattleWorkBGIDGet(BATTLE_WORK *bw)
{
	return	bw->bg_id;
}

//============================================================================================
/**
 *	place_id���擾
 *
 * @param[in]	bw			�퓬���[�N�\����
 *
 * @retval	bw->place_id
 */
//============================================================================================
int	BattleWorkPlaceIDGet(BATTLE_WORK *bw)
{
	return	bw->place_id;
}

//============================================================================================
/**
 *	�w�肵��ClientNo�̃p�[�g�i�[��ClientNo���擾
 *
 * @param[in]	bw			�퓬�V�X�e�����[�N�\����
 * @param[in]	client_no	�擾����ClientNo
 *
 * @retval	ClientNo
 */
//============================================================================================
int	BattleWorkPartnerClientNoGet(BATTLE_WORK *bw,int client_no)
{
	int	partner_client_no;
	int	client_set_max;
	u32	fight_type;

	client_set_max=BattleWorkClientSetMaxGet(bw);
	fight_type=BattleWorkFightTypeGet(bw);

	//1vs1�͎������g��Ԃ�
	if((fight_type&FIGHT_TYPE_2vs2)==0){
		return client_no;
	}

	for(partner_client_no=0;partner_client_no<client_set_max;partner_client_no++){
		if((partner_client_no!=client_no)&&
		   (BattleWorkMineEnemyCheck(bw,partner_client_no)==BattleWorkMineEnemyCheck(bw,client_no))){
			break;
		}
	}
#ifdef PM_DEBUG
	if(partner_client_no==client_set_max){
		GF_ASSERT_MSG(0,"�p�[�g�i�[��������܂���ł���\n");
		partner_client_no=0;
	}
#endif
	return partner_client_no;
}

//============================================================================================
/**
 *	�w�肵��ClientNo�̑����ClientNo���擾
 *
 * @param[in]	bw			�퓬�V�X�e�����[�N�\����
 * @param[in]	client_no	�擾����ClientNo
 * @param[in]	side		�擾���鑤(BWECNG_SIDE_RIGHT:�E�@BWECNG_SIDE_LEFT:���j
 *
 * @retval	ClientNo
 */
//============================================================================================
int	BattleWorkEnemyClientNoGet(BATTLE_WORK *bw,int client_no,int side)
{
	int	enemy_client_no;
	int	client_set_max;
	u32	fight_type;

	client_set_max=BattleWorkClientSetMaxGet(bw);
	fight_type=BattleWorkFightTypeGet(bw);

	//1vs1�͑f���ɑ����Ԃ�
	if((fight_type&FIGHT_TYPE_2vs2)==0){
		return client_no^1;
	}

	for(enemy_client_no=0;enemy_client_no<client_set_max;enemy_client_no++){
		if((enemy_client_no!=client_no)&&
		  ((BattleWorkClientTypeGet(bw,enemy_client_no)&2)==side)&&
		   (BattleWorkMineEnemyCheck(bw,enemy_client_no)!=BattleWorkMineEnemyCheck(bw,client_no))){
			break;
		}
	}
#ifdef PM_DEBUG
	if(enemy_client_no==client_set_max){
		GF_ASSERT_MSG(0,"�p�[�g�i�[��������܂���ł���\n");
		enemy_client_no=0;
	}
#endif
	return enemy_client_no;
}

//============================================================================================
/**
 *	�A�C�e�����g�p���ă|�P�����̃p�����[�^��ω��i�퓬�p�A�C�e���j
 *
 * @param[in]	bw			�퓬�V�X�e�����[�N�\����
 * @param[in]	client_no	�ω�������ClientNo
 * @param[in]	sel_mons_no	�ω�������SelMonsNo
 * @param[in]	waza_pos	�ω�������WazaPos
 * @param[in]	item_no		�g�p����A�C�e��
 *
 * @retval	FALSE:�A�C�e���g�p�ł��Ȃ��@TRUE:�A�C�e���g�p�i�p�����[�^���ω��ς݁j
 */
//============================================================================================

#define	FRIEND1	(100)	//�Ȃ��x�v�Z�̒i�K
#define	FRIEND2	(200)	//�Ȃ��x�v�Z�̒i�K

BOOL	BattleWorkStatusRecover(BATTLE_WORK *bw,int client_no,int sel_mons_no,int waza_pos,int item_no)
{
	SERVER_PARAM	*sp;
	POKEMON_PARAM	*pp;
	BOOL			ret;
	int				data;
	int				pos1;
	int				pos2;
	int				friend;

	sp=bw->server_param;
	ret=FALSE;
	pos1=ST_ServerParamDataGet(bw,sp,ID_SP_sel_mons_no,client_no);
	if((BattleWorkFightTypeGet(bw)&FIGHT_TYPE_2vs2)&&
	  ((BattleWorkFightTypeGet(bw)&FIGHT_TYPE_MULTI)==0)){
		pos2=ST_ServerParamDataGet(bw,sp,ID_SP_sel_mons_no,BattleWorkPartnerClientNoGet(bw,client_no));
		if(pos2==sel_mons_no){
			client_no=BattleWorkPartnerClientNoGet(bw,client_no);
		}
	}
	else{
		pos2=pos1;
	}
	pp=BattleWorkPokemonParamGet(bw,client_no,sel_mons_no);
	friend=0;

	// �����
	if(ItemParamGet(item_no,ITEM_PRM_SLEEP_RCV,HEAPID_BATTLE)){
		data=PokeParaGet(pp,ID_PARA_condition,NULL);
		if(data&CONDITION_NEMURI){
			data&=CONDITION_NEMURI_OFF;
			PokeParaPut(pp,ID_PARA_condition,&data);
			if((pos1==sel_mons_no)||(pos2==sel_mons_no)){
				data=ST_ServerPokemonServerParamGet(sp,client_no,ID_PSP_condition,NULL);
				data&=CONDITION_NEMURI_OFF;
				ST_ServerPokemonServerParamPut(sp,client_no,ID_PSP_condition,&data);
				data=ST_ServerPokemonServerParamGet(sp,client_no,ID_PSP_condition2,NULL);
				data&=CONDITION2_AKUMU_OFF;
				ST_ServerPokemonServerParamPut(sp,client_no,ID_PSP_condition2,&data);
			}
			ret=TRUE;
		}
	}
	// �ŉ�
	if(ItemParamGet(item_no,ITEM_PRM_POISON_RCV,HEAPID_BATTLE)){
		data=PokeParaGet(pp,ID_PARA_condition,NULL);
		if(data&CONDITION_DOKUALL){
			data&=CONDITION_POISON_OFF;
			PokeParaPut(pp,ID_PARA_condition,&data);
			if((pos1==sel_mons_no)||(pos2==sel_mons_no)){
				data=ST_ServerPokemonServerParamGet(sp,client_no,ID_PSP_condition,NULL);
				data&=CONDITION_POISON_OFF;
				ST_ServerPokemonServerParamPut(sp,client_no,ID_PSP_condition,&data);
			}
			ret=TRUE;
		}
	}
	// �Ώ���
	if(ItemParamGet(item_no,ITEM_PRM_BURN_RCV,HEAPID_BATTLE)){
		data=PokeParaGet(pp,ID_PARA_condition,NULL);
		if(data&CONDITION_YAKEDO){
			data&=CONDITION_YAKEDO_OFF;
			PokeParaPut(pp,ID_PARA_condition,&data);
			if((pos1==sel_mons_no)||(pos2==sel_mons_no)){
				data=ST_ServerPokemonServerParamGet(sp,client_no,ID_PSP_condition,NULL);
				data&=CONDITION_YAKEDO_OFF;
				ST_ServerPokemonServerParamPut(sp,client_no,ID_PSP_condition,&data);
			}
			ret=TRUE;
		}
	}
	// �X��
	if(ItemParamGet(item_no,ITEM_PRM_ICE_RCV,HEAPID_BATTLE)){
		data=PokeParaGet(pp,ID_PARA_condition,NULL);
		if(data&CONDITION_KOORI){
			data&=CONDITION_KOORI_OFF;
			PokeParaPut(pp,ID_PARA_condition,&data);
			if((pos1==sel_mons_no)||(pos2==sel_mons_no)){
				data=ST_ServerPokemonServerParamGet(sp,client_no,ID_PSP_condition,NULL);
				data&=CONDITION_KOORI_OFF;
				ST_ServerPokemonServerParamPut(sp,client_no,ID_PSP_condition,&data);
			}
			ret=TRUE;
		}
	}
	// ��჉�
	if(ItemParamGet(item_no,ITEM_PRM_PARALYZE_RCV,HEAPID_BATTLE)){
		data=PokeParaGet(pp,ID_PARA_condition,NULL);
		if(data&CONDITION_MAHI){
			data&=CONDITION_MAHI_OFF;
			PokeParaPut(pp,ID_PARA_condition,&data);
			if((pos1==sel_mons_no)||(pos2==sel_mons_no)){
				data=ST_ServerPokemonServerParamGet(sp,client_no,ID_PSP_condition,NULL);
				data&=CONDITION_MAHI_OFF;
				ST_ServerPokemonServerParamPut(sp,client_no,ID_PSP_condition,&data);
			}
			ret=TRUE;
		}
	}
	// ������
	if(ItemParamGet(item_no,ITEM_PRM_PANIC_RCV,HEAPID_BATTLE)){
		if((pos1==sel_mons_no)||(pos2==sel_mons_no)){
			data=ST_ServerPokemonServerParamGet(sp,client_no,ID_PSP_condition2,NULL);
			if(data&CONDITION2_KONRAN){
				data&=CONDITION2_KONRAN_OFF;
				ST_ServerPokemonServerParamPut(sp,client_no,ID_PSP_condition2,&data);
				ret=TRUE;
			}
		}
	}
	// ����������
	if(ItemParamGet(item_no,ITEM_PRM_MEROMERO_RCV,HEAPID_BATTLE)){
		if((pos1==sel_mons_no)||(pos2==sel_mons_no)){
			data=ST_ServerPokemonServerParamGet(sp,client_no,ID_PSP_condition2,NULL);
			if(data&CONDITION2_MEROMERO){
				data&=CONDITION2_MEROMERO_OFF;
				ST_ServerPokemonServerParamPut(sp,client_no,ID_PSP_condition2,&data);
				ret=TRUE;
			}
		}
	}
	// �\�̓K�[�h
	if(ItemParamGet(item_no,ITEM_PRM_ABILITY_GUARD,HEAPID_BATTLE)){
		data=ST_ServerParamDataGet(bw,sp,ID_SP_shiroikiri_count,client_no);
		if(data==0){
			data=ST_ServerParamDataGet(bw,sp,ID_SP_side_condition,client_no);
			data|=SIDE_CONDITION_SHIROIKIRI;
			ST_ServerParamDataPut(bw,sp,ID_SP_side_condition,client_no,data);
			ST_ServerParamDataPut(bw,sp,ID_SP_shiroikiri_count,client_no,5);
			ret=TRUE;
		}
	}
	// �U���̓A�b�v
	if(ItemParamGet(item_no,ITEM_PRM_ATTACK_UP,HEAPID_BATTLE)){
		if((pos1==sel_mons_no)||(pos2==sel_mons_no)){
			if(ST_ServerPokemonServerParamGet(sp,client_no,ID_PSP_abiritycnt_pow,NULL)<12){
				ST_ServerPokemonServerParamAdd(sp,client_no,ID_PSP_abiritycnt_pow,1);
				ret=TRUE;
			}
		}
	}
	// �h��̓A�b�v
	if(ItemParamGet(item_no,ITEM_PRM_DEFENCE_UP,HEAPID_BATTLE)){
		if((pos1==sel_mons_no)||(pos2==sel_mons_no)){
			if(ST_ServerPokemonServerParamGet(sp,client_no,ID_PSP_abiritycnt_def,NULL)<12){
				ST_ServerPokemonServerParamAdd(sp,client_no,ID_PSP_abiritycnt_def,1);
				ret=TRUE;
			}
		}
	}
	// ���U�A�b�v
	if(ItemParamGet(item_no,ITEM_PRM_SP_ATTACK_UP,HEAPID_BATTLE)){
		if((pos1==sel_mons_no)||(pos2==sel_mons_no)){
			if(ST_ServerPokemonServerParamGet(sp,client_no,ID_PSP_abiritycnt_spepow,NULL)<12){
				ST_ServerPokemonServerParamAdd(sp,client_no,ID_PSP_abiritycnt_spepow,1);
				ret=TRUE;
			}
		}
	}
	// ���h�A�b�v
	if(ItemParamGet(item_no,ITEM_PRM_SP_DEFENCE_UP,HEAPID_BATTLE)){
		if((pos1==sel_mons_no)||(pos2==sel_mons_no)){
			if(ST_ServerPokemonServerParamGet(sp,client_no,ID_PSP_abiritycnt_spedef,NULL)<12){
				ST_ServerPokemonServerParamAdd(sp,client_no,ID_PSP_abiritycnt_spedef,1);
				ret=TRUE;
			}
		}
	}
	// �f�����A�b�v
	if(ItemParamGet(item_no,ITEM_PRM_AGILITY_UP,HEAPID_BATTLE)){
		if((pos1==sel_mons_no)||(pos2==sel_mons_no)){
			if(ST_ServerPokemonServerParamGet(sp,client_no,ID_PSP_abiritycnt_agi,NULL)<12){
				ST_ServerPokemonServerParamAdd(sp,client_no,ID_PSP_abiritycnt_agi,1);
				ret=TRUE;
			}
		}
	}
	// �������A�b�v
	if(ItemParamGet(item_no,ITEM_PRM_HIT_UP,HEAPID_BATTLE)){
		if((pos1==sel_mons_no)||(pos2==sel_mons_no)){
			if(ST_ServerPokemonServerParamGet(sp,client_no,ID_PSP_abiritycnt_hit,NULL)<12){
				ST_ServerPokemonServerParamAdd(sp,client_no,ID_PSP_abiritycnt_hit,1);
				ret=TRUE;
			}
		}
	}
	// �N���e�B�J�����A�b�v
	if(ItemParamGet(item_no,ITEM_PRM_CRITICAL_UP,HEAPID_BATTLE)){
		if((pos1==sel_mons_no)||(pos2==sel_mons_no)){
			data=ST_ServerPokemonServerParamGet(sp,client_no,ID_PSP_condition2,NULL);
			if((data&CONDITION2_KIAIDAME)==0){
				data|=CONDITION2_KIAIDAME;
				ST_ServerPokemonServerParamPut(sp,client_no,ID_PSP_condition2,&data);
				ret=TRUE;
			}
		}
	}
	// PP��
	if(ItemParamGet(item_no,ITEM_PRM_PP_RCV,HEAPID_BATTLE)){
		data=ItemParamGet(item_no,ITEM_PRM_PP_RCV_POINT,HEAPID_BATTLE);
		if(PokeParaGet(pp,ID_PARA_pp1+waza_pos,NULL)!=PokeParaGet(pp,ID_PARA_pp_max1+waza_pos,NULL)){
			PokeParaAdd(pp,ID_PARA_pp1+waza_pos,data);
			if((pos1==sel_mons_no)||(pos2==sel_mons_no)){
				if(((ST_ServerPokemonServerParamGet(sp,client_no,ID_PSP_condition2,NULL)&CONDITION2_HENSHIN)==0)&&
				  ((ST_ServerPokemonServerParamGet(sp,client_no,ID_PSP_wkw_monomane_bit,NULL)&No2Bit(waza_pos))==0)){
					ST_ServerPokemonServerParamAdd(sp,client_no,ID_PSP_pp1+waza_pos,data);
				}
			}
			ret=TRUE;
		}
	}
	// PP�񕜁i�S�Ă̋Z�j
	if(ItemParamGet(item_no,ITEM_PRM_ALL_PP_RCV,HEAPID_BATTLE)){
		data=ItemParamGet(item_no,ITEM_PRM_PP_RCV_POINT,HEAPID_BATTLE);
		for(waza_pos=0;waza_pos<WAZA_TEMOTI_MAX;waza_pos++){
			if(PokeParaGet(pp,ID_PARA_pp1+waza_pos,NULL)!=PokeParaGet(pp,ID_PARA_pp_max1+waza_pos,NULL)){
				PokeParaAdd(pp,ID_PARA_pp1+waza_pos,data);
				if((pos1==sel_mons_no)||(pos2==sel_mons_no)){
					if(((ST_ServerPokemonServerParamGet(sp,client_no,ID_PSP_condition2,NULL)&CONDITION2_HENSHIN)==0)&&
					  ((ST_ServerPokemonServerParamGet(sp,client_no,ID_PSP_wkw_monomane_bit,NULL)&No2Bit(waza_pos))==0)){
						ST_ServerPokemonServerParamAdd(sp,client_no,ID_PSP_pp1+waza_pos,data);
					}
				}
				ret=TRUE;
			}
		}
	}
	// HP��
	if(ItemParamGet(item_no,ITEM_PRM_HP_RCV,HEAPID_BATTLE)){
		data=0;
		// �m����
		if(ItemParamGet(item_no,ITEM_PRM_DEATH_RCV,HEAPID_BATTLE)){
			if(PokeParaGet(pp,ID_PARA_hp,NULL)==0){
				data=1;
			}
		}
		else{
			data=PokeParaGet(pp,ID_PARA_hp,NULL);
		}
		if((data)&&(PokeParaGet(pp,ID_PARA_hp,NULL)!=PokeParaGet(pp,ID_PARA_hpmax,NULL))){
			data=ItemParamGet(item_no,ITEM_PRM_HP_RCV_POINT,HEAPID_BATTLE);
			switch(data){
			case HP_MAX_RECOVER:
				data=PokeParaGet(pp,ID_PARA_hpmax,NULL);
				break;
			case HP_HALF_RECOVER:
				data=PokeParaGet(pp,ID_PARA_hpmax,NULL)/2;
				if(data==0){
					data=1;
				}
				break;
			case HP_25PER_RECOVER:
				data=PokeParaGet(pp,ID_PARA_hpmax,NULL)*25/100;
				if(data==0){
					data=1;
				}
				break;
			default:
				break;
			}
			PokeParaAdd(pp,ID_PARA_hp,data);
			if(!ItemParamGet(item_no,ITEM_PRM_DEATH_RCV,HEAPID_BATTLE)){
				if(BattleWorkMineEnemyCheck(bw,client_no)){
					ST_ServerPokemonServerParamPut(sp,client_no,ID_PSP_wkw_item_hp_recover,&data);
				}
				else{
					if((pos1==sel_mons_no)||(pos2==sel_mons_no)){
						ST_ServerPokemonServerParamAdd(sp,client_no,ID_PSP_hp,data);
					}
				}
			}
			ret=TRUE;
		}
	}
	// �Ȃ��x�P
	if(ItemParamGet(item_no,ITEM_PRM_FRIEND1,HEAPID_BATTLE)){
		if((PokeParaGet(pp,ID_PARA_friend,NULL)<FRIEND1)&&(ret==TRUE)){
			friend=ItemParamGet(item_no,ITEM_PRM_FRIEND1_POINT,HEAPID_BATTLE);
		}
	}
	// �Ȃ��x�Q
	if(ItemParamGet(item_no,ITEM_PRM_FRIEND2,HEAPID_BATTLE)){
		if((PokeParaGet(pp,ID_PARA_friend,NULL)>=FRIEND1)&&
		   (PokeParaGet(pp,ID_PARA_friend,NULL)<FRIEND2)&&
		   (ret==TRUE)){
			friend=ItemParamGet(item_no,ITEM_PRM_FRIEND2_POINT,HEAPID_BATTLE);
		}
	}
	// �Ȃ��x�R
	if(ItemParamGet(item_no,ITEM_PRM_FRIEND3,HEAPID_BATTLE)){
		if((PokeParaGet(pp,ID_PARA_friend,NULL)>=FRIEND2)&&(ret==TRUE)){
			friend=ItemParamGet(item_no,ITEM_PRM_FRIEND3_POINT,HEAPID_BATTLE);
		}
	}
	if(friend){
		if(friend>0){
			//�����Ă���{�[������
			if(PokeParaGet(pp,ID_PARA_get_ball,NULL)==ITEM_GOOZYASUBOORU){
				friend++;
			}
			//�߂܂����ꏊ�Ɠ�������
			if(PokeParaGet(pp,ID_PARA_get_place,NULL)==BattleWorkPlaceIDGet(bw)){
				friend++;
			}
			//��������
			data=PokeParaGet(pp,ID_PARA_item,NULL);
			if(ItemParamGet(item_no,ITEM_PRM_EQUIP,HEAPID_BATTLE)==SOUBI_NATUKIDOUP){
				friend=friend*150/100;
			}
		}
		PokeParaAdd(pp,ID_PARA_friend,friend);
		if((pos1==sel_mons_no)||(pos2==sel_mons_no)){
			ST_ServerPokemonServerParamAdd(sp,client_no,ID_PSP_friend,friend);
		}
	}
	return ret;
}

//============================================================================================
/**
 *	battle_status_flag���擾
 *
 * @param[in]	bw		�퓬���[�N�\����
 *
 * @retval	battle_status_flag
 */
//============================================================================================
u32	BattleWorkBattleStatusFlagGet(BATTLE_WORK *bw)
{
	return bw->battle_status_flag;
}

//============================================================================================
/**
 *	time_zone���擾
 *
 * @param[in]	bw		�퓬���[�N�\����
 *
 * @retval	time_zone
 */
//============================================================================================
int	BattleWorkTimeZoneGet(BATTLE_WORK *bw)
{
	return bw->time_zone;
}

//============================================================================================
/**
 *	time_zone���擾�i3�����j
 *
 * @param[in]	bw		�퓬���[�N�\����
 *
 * @retval	time_zone��3�����ɂ���
 */
//============================================================================================
int	BattleWorkTimeZoneOffsetGet(BATTLE_WORK *bw)
{
	int	ofs;

	switch(bw->bg_id){
	//���Ԕ��f�͈ȉ���ID����
	case BG_ID_BASIC:
	case BG_ID_SEA:
	case BG_ID_CITY:
	case BG_ID_FOREST:
	case BG_ID_MOUNTAIN:
	case BG_ID_SNOW_MOUNTAIN:
		switch(bw->time_zone){
		case TIMEZONE_MORNING:
		case TIMEZONE_NOON:
			ofs=0;
			break;
		case TIMEZONE_EVENING:
			ofs=1;
			break;
		case TIMEZONE_NIGHT:
		case TIMEZONE_MIDNIGHT:
			ofs=2;
			break;
		}
		break;
	//����ȊO�͒��ŕԂ�
	default:
		ofs=0;
		break;
	}

	return ofs;
}

//============================================================================================
/**
 *	CommandSelect�Łu�ɂ���v�Ȃ̂��u���ǂ�v�Ȃ̂����`�F�b�N
 *
 * @param[in]	bw			�퓬���[�N�\����
 * @param[in]	client_no	�`�F�b�N����N���C�A���g�i���o�[
 *
 * @retval	FALSE:�u�ɂ���v TRUE:�u���ǂ�v
 */
//============================================================================================
BOOL	BattleWorkEscCanCheck(BATTLE_WORK *bw,int client_no)
{
	u16	item;

	if(((BattleWorkClientTypeGet(bw,client_no)==CLIENT_TYPE_C)&&
	    (bw->fight_type&FIGHT_TYPE_MULTI)==0)){
		if(bw->fight_type&FIGHT_TYPE_SIO){
			if((bw->no_reshuffle_client&No2Bit(BattleWorkPartnerClientNoGet(bw,client_no)))==0){
				return TRUE;
			}
		}
		else{
			//���2�o�C�g�́A�o�b�O�̃y�[�W�i���o�[�Ȃ̂ŁA�}�X�N����
			item=ST_ServerParamDataGet(bw,bw->server_param,ID_SP_act_work,CLIENT_NO_MINE)&0xffff;
			if(((ST_ServerParamDataGet(bw,bw->server_param,ID_SP_act_no,CLIENT_NO_MINE)==SERVER_ITEM_COMMAND_NO)&&
			    (item>ITEM_PURESYASUBOORU))||
			    (ST_ServerParamDataGet(bw,bw->server_param,ID_SP_no_reshuffle_client,NULL)&No2Bit(CLIENT_NO_MINE))){
				return FALSE;
			}
			else{
				return TRUE;
			}
		}
	}
	return FALSE;
}

//============================================================================================
/**
 * @brief	�퓬�i���`�F�b�N
 *
 * @param[in]	bp			�퓬�V�X�e���p���[�N�\����
 * @param[in]	pp			�|�P�����p�����[�^�p���[�N�\����
 */
//============================================================================================
u16	BattleWorkShinkaCheck(BATTLE_PARAM *bp,int *sel_mons_no,int *shinka_cond)
{
	POKEMON_PARAM	*pp;
	u16				mons_no;

	mons_no=0;

	if((bp->win_lose_flag!=FIGHT_WIN)&&(bp->win_lose_flag!=FIGHT_POKE_GET)&&(bp->win_lose_flag!=FIGHT_ESCAPE)){
		return 0;
	}

	while(bp->level_up_flag){
		for(sel_mons_no[0]=0;sel_mons_no[0]<POKEMON_TEMOTI_MAX;sel_mons_no[0]++){
			if(bp->level_up_flag&No2Bit(sel_mons_no[0])){
				bp->level_up_flag&=(No2Bit(sel_mons_no[0])^0xffffffff);
				break;
			}
		}
		if(sel_mons_no[0]<POKEMON_TEMOTI_MAX){
			pp=PokeParty_GetMemberPointer(bp->poke_party[CLIENT_NO_MINE],sel_mons_no[0]);
			if((mons_no=PokeShinkaCheck(bp->poke_party[CLIENT_NO_MINE],pp,LEVELUP_SHINKA,bp->shinka_place_mode,shinka_cond))){
				return mons_no;
			}
		}
	}
	return mons_no;
}

//============================================================================================
/**
 *	server_flag���擾
 *
 * @param[in]	bw		�퓬���[�N�\����
 *
 * @retval	server_flag
 */
//============================================================================================
u8	BattleWorkServerFlagGet(BATTLE_WORK *bw)
{
	return	bw->server_flag;
}

//============================================================================================
/**
 *	safari_escape_count���擾
 *
 * @param[in]	bw		�퓬���[�N�\����
 *
 * @retval	safari_escape_count
 */
//============================================================================================
u8	BattleWorkSafariEscapeCountGet(BATTLE_WORK *bw)
{
	GF_ASSERT(bw->server_param!=NULL);

	return ST_ServerParamDataGet(bw,bw->server_param,ID_SP_safari_escape_count,NULL);
}

//============================================================================================
/**
 *	safari_ball���擾
 *
 * @param[in]	bw		�퓬���[�N�\����
 *
 * @retval	safari_ball
 */
//============================================================================================
int	BattleWorkSafariBallCountGet(BATTLE_WORK *bw)
{
	return bw->safari_ball;
}

//============================================================================================
/**
 *	safari_ball���Z�b�g
 *
 * @param[in]	bw		�퓬���[�N�\����
 *
 * @retval	safari_ball
 */
//============================================================================================
void	BattleWorkSafariBallCountSet(BATTLE_WORK *bw,int count)
{
	bw->safari_ball=count;
}

//============================================================================================
/**
 *	�Q�[���R���t�B�O�̎擾
 *
 * @param[in]	bw		�퓬���[�N�\����
 *
 * @retval	config
 */
//============================================================================================
CONFIG	*BattleWorkConfigGet(BATTLE_WORK *bw)
{
#ifdef PM_DEBUG
	GF_ASSERT(bw->config!=NULL);
#endif
	return bw->config;
}

//============================================================================================
/**
 *	�Q�[���R���t�B�O�̋Z�G�t�F�N�g�I���^�I�t���`�F�b�N
 *
 * @param[in]	bw		�퓬���[�N�\����
 *
 * @retval	FALSE:OFF TRUE:ON
 */
//============================================================================================
BOOL	BattleWorkConfigWazaEffectOnOffCheck(BATTLE_WORK *bw)
{
	//�ʐM�ΐ�ł́A���ON
	if(bw->fight_type&FIGHT_TYPE_SIO){
		return TRUE;
	}
	return (CONFIG_GetWazaEffectMode(bw->config)==WAZAEFF_MODE_ON);
}

//============================================================================================
/**
 *	�Q�[���R���t�B�O�̃E�B���h�E��ނ��擾
 *
 * @param[in]	bw		�퓬���[�N�\����
 *
 * @retval	WINTYPE
 */
//============================================================================================
WINTYPE	BattleWorkConfigWinTypeGet(BATTLE_WORK *bw)
{
	return CONFIG_GetWindowType(bw->config);
}

//============================================================================================
/**
 *	�Q�[���R���t�B�O�̃��b�Z�[�W�X�s�[�h���擾
 *
 * @param[in]	bw		�퓬���[�N�\����
 *
 * @retval	���b�Z�[�W�X�s�[�h
 */
//============================================================================================
#define	MSG_SPEED_FAST	(1)

u8	BattleWorkConfigMsgSpeedGet(BATTLE_WORK *bw)
{
	//�ʐM�ΐ�ł́A��Ƀm�[�}���X�s�[�h
	if(bw->fight_type&FIGHT_TYPE_SIO){
		return MSG_SPEED_FAST;
	}
	return CONFIG_GetMsgPrintSpeed(bw->config);
}

//============================================================================================
/**
 *	�Q�[���R���t�B�O�̐퓬�^�C�v���擾
 *
 * @param[in]	bw		�퓬���[�N�\����
 *
 * @retval	BATTLERULE
 */
//============================================================================================
BATTLERULE	BattleWorkConfigBattleRuleGet(BATTLE_WORK *bw)
{
	return CONFIG_GetBattleRule(bw->config);
}

//============================================================================================
/**
 *	�|�P�����A�j���V�X�e�����[�N�̃|�C���^���擾
 *
 * @param[in]	bw		�퓬���[�N�\����
 *
 * @retval	bw->pasp;
 */
//============================================================================================
POKE_ANM_SYS_PTR	BattleWorkPokeAnmSysPTRGet(BATTLE_WORK *bw)
{
	return bw->pasp;
}

//============================================================================================
/**
 *	�|�P�����̖����f�[�^���擾�i�؃��b�v�f�[�^�j
 *
 * @param[in]	bw			�퓬���[�N�\����
 * @param[in]	client_no	�擾����ClientNo
 *
 * @retval	bw->poke_voice[client_no];
 */
//============================================================================================
PERAPVOICE	*BattleWorkPerapVoiceGet(BATTLE_WORK *bw,int client_no)
{
	if((bw->fight_type&FIGHT_TYPE_MULTI)||
	  ((bw->fight_type&FIGHT_TYPE_TAG)&&(BattleWorkClientTypeGet(bw,client_no)&CLIENT_ENEMY_FLAG))){
		return	bw->poke_voice[client_no];
	}
	else if(bw->fight_type&FIGHT_TYPE_2vs2){
		return	bw->poke_voice[client_no&1];
	}
	else{
		return	bw->poke_voice[client_no];
	}
}

//============================================================================================
/**
 *	�퓬��Ƀt�H�����`�F���W����|�P�����̃`�F�b�N
 *
 * @param[in]	bw			�퓬���[�N�\����
 */
//============================================================================================
void	BattleWorkFormChgCheck(BATTLE_WORK *bw)
{
	int				i,form;
	POKEMON_PARAM	*pp;
	u16				monsno;

	//FightType�Ńt�H�����`�F���W�Ȃ��́A���Ȃ�
	if(bw->fight_type&FIGHT_TYPE_NO_FORM_CHG){
		return;
	}

	for(i=0;i<BattleWorkPokeCountGet(bw,CLIENT_NO_MINE);i++){
		pp=BattleWorkPokemonParamGet(bw,CLIENT_NO_MINE,i);
		monsno=PokeParaGet(pp,ID_PARA_monsno_egg,NULL);
		//�~�m���b�`�t�H�����`�F���W
		if((monsno==MONSNO_MINOMUTTI)&&(bw->appear_flag[CLIENT_NO_MINE]&No2Bit(i))){
			switch(BattleWorkGroundIDGet(bw)){
			default:
			case GROUND_ID_LAWN:
				form=FORMNO_MINOMUTTI_KUSA;
				break;
			case GROUND_ID_GRAVEL:
			case GROUND_ID_SANDS:
			case GROUND_ID_ROCK:
			case GROUND_ID_CAVE:
				form=FORMNO_MINOMUTTI_SUNA;
				break;
			case GROUND_ID_FLOOR:
			case GROUND_ID_BRIDGE:
				form=FORMNO_MINOMUTTI_TETSU;
				break;
			}
			PokeParaPut(pp,ID_PARA_form_no,&form);
		}
	}
}

//============================================================================================
/**
 *	�J��o�����|�P������SelMonsNo���r�b�g�Ŋi�[
 *
 * @param[in]	bw			�퓬���[�N�\����
 * @param[in]	client_no	�i�[����ClientNo
 * @param[in]	sel_mons_no	�i�[����SleMonsNo
 */
//============================================================================================
void	BattleWorkAppearFlagSet(BATTLE_WORK *bw,int client_no,int sel_mons_no)
{
	bw->appear_flag[client_no]|=No2Bit(sel_mons_no);
}

//============================================================================================
/**
 *	�|�P�b�`�f�[�^�ɕߊl�|�P���������Z�b�g
 *
 * @param[in]	bw	�퓬���[�N�\����
 * @param[in]	pp	�Z�b�g����|�P�����\����
 */
//============================================================================================
void	BattleWorkPoketchDataSet(BATTLE_WORK *bw,POKEMON_PARAM *pp)
{
#ifdef PM_DEBUG
	GF_ASSERT(bw->poketch_data!=NULL);
#endif
	//�O�̂��߁A�A�h���X���͂����Ă��邩�`�F�b�N����
	if(bw->poketch_data){
		PoketchData_PokeHistory_Add(bw->poketch_data,PPPPointerGet(pp));
	}
}

//============================================================================================
/**
 *	�e���r�f�[�^�ɕߊl�|�P���������Z�b�g
 *
 * @param[in]	bw	�퓬���[�N�\����
 * @param[in]	pp	�Z�b�g����|�P�����\����
 */
//============================================================================================
void	BattleWorkTVDataSet(BATTLE_WORK *bw,POKEMON_PARAM *pp)
{
#ifdef PM_DEBUG
	GF_ASSERT(bw->TVWatchBattleWork!=NULL);
#endif
	TVBATTLE_StoreResult(bw->TVWatchBattleWork,pp,bw->win_lose_flag,bw->ball_count,HEAPID_BATTLE);
}

//============================================================================================
/**
 *	�n�`�O���t�B�b�N��BG�ɕϊ�����
 *
 * @param[in]	bw	�퓬���[�N�\����
 * @param[in]	pp	�Z�b�g����|�P�����\����
 */
//============================================================================================
void	BattleWorkGroundBGChg(BATTLE_WORK *bw)
{
	NNSG2dImageProxy	*image;
	int					bg_x,bg_y,obj_x,obj_y,obj_data,i;
	u8					*obj_vram;
		
	bw->bg_area=sys_AllocMemory(HEAPID_BATTLE,0x10000);
	bw->pal_area=sys_AllocMemory(HEAPID_BATTLE,0x200);
		
	//BG�L�����f�[�^�R�s�[
	MI_CpuCopy32((void*)(HW_BG_VRAM+0x10000),bw->bg_area,0x10000);

	//BG�p���b�g�f�[�^�R�s�[
	MI_CpuCopy32(PaletteWorkDefaultWorkGet(bw->pfd,FADE_MAIN_BG),bw->pal_area,HW_BG_PLTT_SIZE);

	//�G���n�`�f�[�^�A�h���X�擾
	obj_vram=G2_GetOBJCharPtr();
	image=CLACT_ImageProxyGet(bw->ground[GROUND_ENEMY].cap->act);
	obj_vram+=image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN];

	//�G���n�`�f�[�^��BG�L�����o�b�t�@�ɏ㏑��
	for(bg_y=20;bg_y<20+8;bg_y++){
		for(bg_x=16;bg_x<32;bg_x++){
			obj_x=bg_x-16;
			obj_y=bg_y-20;
			for(i=0;i<0x40;i++){
				if(obj_x<8){
					if(i&1){
						obj_data=(obj_vram[obj_y*0x100+obj_x*0x20+i/2]&0xf0)>>4;
					}
					else{
						obj_data=(obj_vram[obj_y*0x100+obj_x*0x20+i/2]&0x0f);
					}
				}
				else{
					if(i&1){
						obj_data=(obj_vram[0x700+obj_y*0x100+obj_x*0x20+i/2]&0xf0)>>4;
					}
					else{
						obj_data=(obj_vram[0x700+obj_y*0x100+obj_x*0x20+i/2]&0x0f);
					}
				}
				if(obj_data){
					bw->bg_area[bg_y*0x800+bg_x*0x40+i]=obj_data+0x70;
				}
			}
		}
	}

	//�������n�`�f�[�^�A�h���X�擾
	obj_vram=G2_GetOBJCharPtr();
	image=CLACT_ImageProxyGet(bw->ground[GROUND_MINE].cap->act);
	obj_vram+=image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN];

	//�G���n�`�f�[�^��BG�L�����o�b�t�@�ɏ㏑��
	for(i=0;i<0x40*32;i++){
		if(i&1){
			obj_data=(obj_vram[i/2]&0xf0)>>4;
		}
		else{
			obj_data=(obj_vram[i/2]&0x0f);
		}
		if(obj_data){
			bw->bg_area[19*0x800+i]=obj_data+0x70;
		}
	}
	for(bg_y=28;bg_y<28+4;bg_y++){
		for(bg_x=0;bg_x<24;bg_x++){
			obj_x=bg_x;
			obj_y=bg_y-28;
			for(i=0;i<0x40;i++){
				if(i&1){
					obj_data=(obj_vram[0x400+(obj_x/8)*0x400+((obj_x%8)*0x20)+(obj_y*0x100)+i/2]&0xf0)>>4;
				}
				else{
					obj_data=(obj_vram[0x400+(obj_x/8)*0x400+((obj_x%8)*0x20)+(obj_y*0x100)+i/2]&0x0f);
			}
				if(obj_data){
					bw->bg_area[bg_y*0x800+bg_x*0x40+i]=obj_data+0x70;
				}
			}
		}
	}

	//VRAM�ɓ]��
	GF_BGL_LoadCharacter(bw->bgl,GF_BGL_FRAME3_M,bw->bg_area,0x10000,0);
	//�n�`CLACT�폜
	Ground_ActorResourceDel(&bw->ground[0]);
	Ground_ActorResourceDel(&bw->ground[1]);
}

//============================================================================================
/**
 *	�ꏊ�i�������擾
 *
 * @param[in]	bw		�퓬���[�N�\����
 *
 * @retval	shinka_place_mode
 */
//============================================================================================
int	BattleWorkShinkaPlaceModeGet(BATTLE_WORK *bw)
{
	return bw->shinka_place_mode;
}

//============================================================================================
/**
 *	�w�iVRAM�ޔ�̈�̎擾
 *
 * @param[in]	bw		�퓬���[�N�\����
 *
 * @retval	bg_area
 */
//============================================================================================
u8	*BattleWorkBGAreaGet(BATTLE_WORK *bw)
{
	return bw->bg_area;
}

//============================================================================================
/**
 *	�w�iCGVRAM�ޔ�̈�̎擾
 *
 * @param[in]	bw		�퓬���[�N�\����
 *
 * @retval	pal_area
 */
//============================================================================================
u16	*BattleWorkPalAreaGet(BATTLE_WORK *bw)
{
	return bw->pal_area;
}

//============================================================================================
/**
 *	�R���e�X�g���������ǂ����t���O�̎擾
 *
 * @param[in]	bw		�퓬���[�N�\����
 *
 * @retval	contest_see_flag
 */
//============================================================================================
int	BattleWorkContestSeeFlagGet(BATTLE_WORK *bw)
{
	return bw->contest_see_flag;
}

//============================================================================================
/**
 *	BG�p���b�g�ޔ����[�N�̃A�h���X�̎擾
 *
 * @param[in]	bw		�퓬���[�N�\����
 *
 * @retval	push_bg_palette
 */
//============================================================================================
u16	*BattleWorkPushBGPaletteGet(BATTLE_WORK *bw)
{
	return &bw->push_bg_palette[0];
}

//============================================================================================
/**
 *	OBJ�p���b�g�ޔ����[�N�̃A�h���X�̎擾
 *
 * @param[in]	bw		�퓬���[�N�\����
 *
 * @retval	push_bg_palette
 */
//============================================================================================
u16	*BattleWorkPushOBJPaletteGet(BATTLE_WORK *bw)
{
	return &bw->push_obj_palette[0];
}

//============================================================================================
/**
 *	�t�B�[���h�V������擾
 *
 * @param[in]	bw		�퓬���[�N�\����
 *
 * @retval	weather
 */
//============================================================================================
int	BattleWorkWeatherGet(BATTLE_WORK *bw)
{
	return bw->weather;
}

//============================================================================================
/**
 *	�ߊl�f���p�V�[�P���X�i���o�[���擾
 *
 * @param[in]	bw		�퓬���[�N�\����
 *
 * @retval	demo_seq_no
 */
//============================================================================================
u8	BattleWorkDemoSeqNoGet(BATTLE_WORK *bw)
{
	return bw->demo_seq_no;
}

//============================================================================================
/**
 *	�ߊl�f���p�V�[�P���X�i���o�[�ɒl���Z�b�g
 *
 * @param[in]	bw		�퓬���[�N�\����
 *
 * @retval	demo_seq_no
 */
//============================================================================================
void	BattleWorkDemoSeqNoSet(BATTLE_WORK *bw,u8 data)
{
	bw->demo_seq_no=data;
}

//============================================================================================
/**
 *	�~�Y�L�ɂ��������ǂ����t���O�̎擾
 *
 * @param[in]	bw		�퓬���[�N�\����
 *
 * @retval	mizuki_flag
 */
//============================================================================================
int	BattleWorkMizukiFlagGet(BATTLE_WORK *bw)
{
	return bw->mizuki_flag;
}

//============================================================================================
/**
 *	�J�E���g�A�b�v���[�N���C���N�������g
 *
 * @param[in]	bw		�퓬���[�N�\����
 * @param[in]	id		�J�E���g�A�b�v����ID
 */
//============================================================================================
void	BattleWorkIncRecord(BATTLE_WORK *bw,int id)
{
#ifdef PM_DEBUG
	GF_ASSERT(bw->record!=NULL);
#endif
	RECORD_Inc(bw->record,id);
}

//============================================================================================
/**
 *	�}�ӓo�^�X�R�A�����Z
 *
 * @param[in]	bw		�퓬���[�N�\����
 */
//============================================================================================
void	BattleWorkZukanSetScoreAdd(BATTLE_WORK *bw)
{
#ifdef PM_DEBUG
	GF_ASSERT(bw->record!=NULL);
#endif
	RECORD_Score_Add(bw->record,SCORE_ID_ZUKAN_ENTRY);
}

//============================================================================================
/**
 *	�R�}���h�Z���N�g�Ń{�^���̃X���C�h�C���̏I�����ŗ��Ƃ��t���O�̎擾
 *
 * @param[in]	bw		�퓬���[�N�\����
 *
 * @retval	bw->command_select_flag
 */
//============================================================================================
int	BattleWorkCommandSelectFlagGet(BATTLE_WORK *bw)
{
	return bw->command_select_flag;
}

//============================================================================================
/**
 *	�R�}���h�Z���N�g�Ń{�^���̃X���C�h�C���̏I�����ŗ��Ƃ��t���O�ɒl���Z�b�g
 *
 * @param[in]	bw		�퓬���[�N�\����
 * @param[in]	data	�Z�b�g����l
 */
//============================================================================================
void	BattleWorkCommandSelectFlagSet(BATTLE_WORK *bw,int data)
{
	bw->command_select_flag=data;
}

//============================================================================================
/**
 *	����ւ��ł��Ȃ�ClientNo���Z�b�g
 *
 * @param[in]	bw		�퓬���[�N�\����
 * @param[in]	data	�Z�b�g����l
 */
//============================================================================================
void	BattleWorkNoReshuffleClientSet(BATTLE_WORK *bw,int data)
{
	bw->no_reshuffle_client=data;
}

//============================================================================================
/**
 *	�ʐM�ҋ@���̎��v�A�C�R���^�X�N�|�C���^�擾
 *
 * @param[in]	bw		�퓬���[�N�\����
 *
 * @retval	bw->time_icon
 */
//============================================================================================
void	*BattleWorkTimeIconGet(BATTLE_WORK *bw)
{
	return bw->time_icon;
}

//============================================================================================
/**
 *	�ʐM�ҋ@���̎��v�A�C�R���^�X�N�|�C���^�i�[
 *
 * @param[in]	bw		�퓬���[�N�\����
 * @param[in]	data	�Z�b�g����l
 */
//============================================================================================
void	BattleWorkTimeIconSet(BATTLE_WORK *bw,void *data)
{
	bw->time_icon=data;
}

//============================================================================================
/**
 *	�J�X�^���{�[�����ǂ����`�F�b�N
 *
 * @param[in]	bw			�퓬���[�N�\����
 * @param[in]	client_no	�`�F�b�N����client_no
 * @param[in]	sel_mons_no	�`�F�b�N����SelMonsNo
 *
 * @retval	TRUE:�J�X�^���{�[��
 */
//============================================================================================
BOOL	BattleWorkCustomBallCheck(BATTLE_WORK *bw,int client_no,int sel_mons_no)
{
	POKEMON_PARAM	*pp;
	
	pp=BattleWorkPokemonParamGet(bw,client_no,sel_mons_no);

	if(PokeParaGet(pp,ID_PARA_cb_id,NULL) != 0){
		return TRUE;	//�J�X�^���{�[��
	}
	return FALSE;
}

//============================================================================================
/**
 *	client_no���w�肵��exchr_param���擾
 *
 * @param[in]	bw		�퓬���[�N�\����
 * @param[in]	no		���Ԗڂ��擾���邩(0-3)
 *
 * @retval	exchr_param
 */
//============================================================================================
EXCHR_PARAM	*BattleWorkExChrClientParamGet(BATTLE_WORK *bw, int no)
{
	return &bw->exchr_param[no];
}

//============================================================================================
/**
 *	exchr_buffer���擾
 *
 * @param[in]	ep		EXCHR_PARAM�\����
 * @param[in]	no		���Ԗڂ��擾���邩(0-3)
 *
 * @retval	exchr_buffer
 */
//============================================================================================
u8	*ExChrParamExChrBufferGet(EXCHR_PARAM *ep,int no)
{
	GF_ASSERT(no<4);
	return ep[no].exchr_buffer;
}

//============================================================================================
/**
 *	arcID���擾
 *
 * @param[in]	ep		EXCHR_PARAM�\����
 * @param[in]	no		���Ԗڂ��擾���邩(0-3)
 *
 * @retval	arcID
 */
//============================================================================================
int	ExChrParamArcIDGet(EXCHR_PARAM *ep,int no)
{
	GF_ASSERT(no<4);
	return ep[no].arcID;
}

//============================================================================================
/**
 *	arcID�Ɋi�[
 *
 * @param[in]	ep		EXCHR_PARAM�\����
 * @param[in]	no		���ԖڂɊi�[���邩(0-3)
 * @param[in]	data	�i�[����l
 */
//============================================================================================
void	ExChrParamArcIDSet(EXCHR_PARAM *ep,int no,int data)
{
	GF_ASSERT(no<4);

	ep[no].arcID=data;
}

//============================================================================================
/**
 *	pal_index���擾
 *
 * @param[in]	ep		EXCHR_PARAM�\����
 * @param[in]	no		���Ԗڂ��擾���邩(0-3)
 *
 * @retval	pal_index
 */
//============================================================================================
int	ExChrParamPalIndexGet(EXCHR_PARAM *ep,int no)
{
	GF_ASSERT(no<4);
	return ep[no].pal_index;
}

//============================================================================================
/**
 *	pal_index�Ɋi�[
 *
 * @param[in]	ep		EXCHR_PARAM�\����
 * @param[in]	no		���ԖڂɊi�[���邩(0-3)
 * @param[in]	data	�i�[����l
 */
//============================================================================================
void	ExChrParamPalIndexSet(EXCHR_PARAM *ep,int no,int data)
{
	GF_ASSERT(no<4);

	ep[no].pal_index=data;
}

//============================================================================================
/**
 *	height���擾
 *
 * @param[in]	ep		EXCHR_PARAM�\����
 * @param[in]	no		���Ԗڂ��擾���邩(0-3)
 *
 * @retval	height
 */
//============================================================================================
int	ExChrParamHeightGet(EXCHR_PARAM *ep,int no)
{
	GF_ASSERT(no<4);
	return ep[no].height;
}

//============================================================================================
/**
 *	height�Ɋi�[
 *
 * @param[in]	ep		EXCHR_PARAM�\����
 * @param[in]	no		���ԖڂɊi�[���邩(0-3)
 * @param[in]	data	�i�[����l
 */
//============================================================================================
void	ExChrParamHeightSet(EXCHR_PARAM *ep,int no,int data)
{
	GF_ASSERT(no<4);

	ep[no].height=data;
}

//============================================================================================
/**
 *	ProcMode���Z�b�g
 *
 * @param[in]	bw		�퓬���[�N�\����
 * @param[in]	mode	�Z�b�g���郂�[�h�i���o�[
 */
//============================================================================================
void	BattleWorkProcModeSet(BATTLE_WORK *bw,int mode)
{
	bw->proc_mode=mode;
}

//============================================================================================
/**
 *	tcb_sio_send_seq_no���Z�b�g
 *
 * @param[in]	bw		�퓬���[�N�\����
 * @param[in]	seq		�Z�b�g����V�[�P���X�i���o�[���[�N�̃|�C���^
 */
//============================================================================================
void	BattleWorkTSSSeqNoAdrsSet(BATTLE_WORK *bw,u8 *seq_no)
{
	bw->tcb_sio_send_seq_no=seq_no;
}

//============================================================================================
/**
 *	tcb_sio_recv_seq_no���Z�b�g
 *
 * @param[in]	bw		�퓬���[�N�\����
 * @param[in]	seq		�Z�b�g����V�[�P���X�i���o�[���[�N�̃|�C���^
 */
//============================================================================================
void	BattleWorkTSRSeqNoAdrsSet(BATTLE_WORK *bw,u8 *seq_no)
{
	bw->tcb_sio_recv_seq_no=seq_no;
}

//============================================================================================
/**
 *	tcb_sio_send_seq_no�ɃZ�b�g
 *
 * @param[in]	bw		�퓬���[�N�\����
 * @param[in]	seq		�Z�b�g����V�[�P���X�i���o�[
 */
//============================================================================================
void	BattleWorkTSSSeqNoSet(BATTLE_WORK *bw,u8 seq_no)
{
	bw->tcb_sio_send_seq_no[0]=seq_no;
}

//============================================================================================
/**
 *	tcb_sio_recv_seq_no�ɃZ�b�g
 *
 * @param[in]	bw		�퓬���[�N�\����
 * @param[in]	seq		�Z�b�g����V�[�P���X�i���o�[
 */
//============================================================================================
void	BattleWorkTSRSeqNoSet(BATTLE_WORK *bw,u8 seq_no)
{
	bw->tcb_sio_recv_seq_no[0]=seq_no;
}

//============================================================================================
/**
 *	fight_end_flag�ɃZ�b�g
 *
 * @param[in]	bw		�퓬���[�N�\����
 * @param[in]	data	�Z�b�g����i���o�[
 */
//============================================================================================
void	BattleWorkFightEndFlagSet(BATTLE_WORK *bw,u8 data)
{
	bw->fight_end_flag=data;
}

//============================================================================================
/**
 *	HP�Q�[�W���[�N���擾
 *
 * @param[in]	bw			�퓬���[�N�\����
 * @param[in]	client_no	�N���C�A���gNo
 * @retval		GAUGE_WORK�\���̂̃|�C���^
 */
//============================================================================================
void *	BattleWorkGaugeWorkGet(BATTLE_WORK *bw, int client_no)
{
	return CT_CPGaugeWorkGet(bw->client_param[client_no]);
}

//============================================================================================
/**
 *	HP�Q�[�W��������
 *
 * @param[in]	bw		�퓬���[�N�\����
 */
//============================================================================================
void	BattleWorkGaugeInit(BATTLE_WORK *bw)
{
	int	i;
	GAUGE_WORK	*gauge;

	for(i=0;i<bw->client_set_max;i++){
		gauge=CT_CPGaugeWorkGet(bw->client_param[i]);
		//HP�Q�[�W����
		gauge->bw = bw;
		gauge->type = Gauge_TypeGet(CT_CPClientTypeGet(bw->client_param[i]), BattleWorkFightTypeGet(bw));
		Gauge_ActorResourceSet(gauge);
		Gauge_EnableSet(gauge, CATS_ENABLE_FALSE);
	}
}

//============================================================================================
/**
 *	HP�Q�[�W��\��
 *
 * @param[in]	bw		�퓬���[�N�\����
 * @param[in]	bw		�퓬���[�N�\����
 */
//============================================================================================
void	BattleWorkGaugeOn(BATTLE_WORK *bw)
{
	int			i;
	GAUGE_WORK	*gauge;

	for(i=0;i<bw->client_set_max;i++){
		gauge=CT_CPGaugeWorkGet(bw->client_param[i]);
		if(gauge->hp){
			Gauge_EnableSet(gauge,CATS_ENABLE_TRUE);
		}
	}
}

//============================================================================================
/**
 *	HP�Q�[�W���\��
 *
 * @param[in]	bw		�퓬���[�N�\����
 */
//============================================================================================
void	BattleWorkGaugeOff(BATTLE_WORK *bw)
{
	int			i;
	GAUGE_WORK	*gauge;

	for(i=0;i<bw->client_set_max;i++){
		gauge=CT_CPGaugeWorkGet(bw->client_param[i]);
		Gauge_EnableSet(gauge,CATS_ENABLE_FALSE);
	}
}

//============================================================================================
/**
 *	HP�Q�[�W���폜
 *
 * @param[in]	bw		�퓬���[�N�\����
 */
//============================================================================================
void	BattleWorkGaugeDelete(BATTLE_WORK *bw)
{
	int			i;
	GAUGE_WORK	*gauge;

	for(i=0;i<bw->client_set_max;i++){
		gauge=CT_CPGaugeWorkGet(bw->client_param[i]);
		Gauge_ActorResourceDel(gauge);
	}
}

//============================================================================================
/**
 *	win_lose_flag����l���擾
 *
 * @param[in]	bw		�퓬���[�N�\����
 */
//============================================================================================
u8	BattleWorkWinLoseGet(BATTLE_WORK *bw)
{
	return bw->win_lose_flag;
}

//============================================================================================
/**
 *	win_lose_flag�ɒl���Z�b�g
 *
 * @param[in]	bw		�퓬���[�N�\����
 * @param[in]	flag	�Z�b�g����l
 */
//============================================================================================
void	BattleWorkWinLoseSet(BATTLE_WORK *bw,u8 flag)
{
	bw->win_lose_flag=flag;
}

//============================================================================================
/**
 *	pinch_se_flag����l���擾
 *
 * @param[in]	bw		�퓬���[�N�\����
 */
//============================================================================================
u8	BattleWorkPinchSEFlagGet(BATTLE_WORK *bw)
{
	return bw->pinch_se_flag;
}

//============================================================================================
/**
 *	pinch_se_flag�ɒl���Z�b�g
 *
 * @param[in]	bw		�퓬���[�N�\����
 * @param[in]	flag	�Z�b�g����l
 */
//============================================================================================
void	BattleWorkPinchSEFlagSet(BATTLE_WORK *bw,u8 flag)
{
	bw->pinch_se_flag=flag;
}

//============================================================================================
/**
 *	pinch_se_wait����l���擾
 *
 * @param[in]	bw		�퓬���[�N�\����
 */
//============================================================================================
u8	BattleWorkPinchSEWaitGet(BATTLE_WORK *bw)
{
	return bw->pinch_se_wait;
}

//============================================================================================
/**
 *	pinch_se_wait�ɒl���Z�b�g
 *
 * @param[in]	bw		�퓬���[�N�\����
 * @param[in]	wait	�Z�b�g����l
 */
//============================================================================================
void	BattleWorkPinchSEWaitSet(BATTLE_WORK *bw,u8 wait)
{
	GF_ASSERT_MSG(wait<15,"Pinch SE Wait Over\n");
	bw->pinch_se_wait=wait;
}

//============================================================================================
/**
 *	get_pokemon_client�ɒl���Z�b�g
 *
 * @param[in]	bw			�퓬���[�N�\����
 * @param[in]	client_no	�Z�b�g����l
 */
//============================================================================================
void	BattleWorkGetPokemonClientSet(BATTLE_WORK *bw,int client_no)
{
	bw->get_pokemon_client=client_no;
}

//============================================================================================
/**
 *	ClientType����ClientNo���擾���邽�߂̃o�b�t�@�𐶐�����
 *
 * @param[in]	bw		�퓬���[�N�\����
 * @param[in]	buf		�o�b�t�@�ւ̃|�C���^
 */
//============================================================================================
void	BattleClientNoBufMake(BATTLE_WORK *bw,u8 *buf)
{
	int	i;

	for(i=0;i<bw->client_set_max;i++){
		buf[CT_CPClientTypeGet(bw->client_param[i])]=i;
	}
}

//============================================================================================
/**
 *	ClientNo����ClientType���擾���邽�߂̃o�b�t�@�𐶐�����
 *
 * @param[in]	bw		�퓬���[�N�\����
 * @param[in]	buf		�o�b�t�@�ւ̃|�C���^
 */
//============================================================================================
void	BattleClientTypeBufMake(BATTLE_WORK *bw,u8 *buf)
{
	int	i;

	for(i=0;i<CLIENT_MAX;i++){
		buf[i]=CLIENT_TYPE_NONE;
	}

	for(i=0;i<bw->client_set_max;i++){
		buf[i]=CT_CPClientTypeGet(bw->client_param[i]);
	}
}

//============================================================================================
/**
 *	ClientNo����SoftSprite���擾���邽�߂̃o�b�t�@�𐶐�����
 *
 * @param[in]	bw		�퓬���[�N�\����
 * @param[in]	buf		�o�b�t�@�ւ̃|�C���^
 */
//============================================================================================
void	BattleSoftSpriteBufMake(BATTLE_WORK *bw,SOFT_SPRITE **buf)
{
	int	i;

	for(i=0;i<CLIENT_MAX;i++){
		buf[i]=NULL;
	}

	for(i=0;i<bw->client_set_max;i++){
		buf[i]=CT_CPSoftSpriteGet(bw->client_param[i]);
	}
}

//============================================================================================
/**
 *	�퓬�Q�[�W�̃v���C�I���e�B���Z�b�g
 *
 * @param[in]	bw		�퓬���[�N�\����
 * @param[in]	pri		�Z�b�g����v���C�I���e�B
 */
//============================================================================================
void	BattleGaugePriSet(BATTLE_WORK *bw,int pri)
{
	int	i;
	GAUGE_WORK	*gw;

	for(i=0;i<bw->client_set_max;i++){
		gw=CT_CPGaugeWorkGet(bw->client_param[i]);
		Gauge_BGPriSet(gw,pri);
	}
}

//============================================================================================
/**
 * �s�펞�̃y�i���e�B�v�Z
 *
 * @param[in]	pp			�莝���|�P�����f�[�^�\����
 * @param[in]	my_status	�}�C�X�e�[�^�X
 *
 * @retval  u32		������邨��
 */
//============================================================================================
u32 CalcLosePenalty(POKEPARTY *ppt,MYSTATUS *my_status)
{
	static const u8 Late[] = {
		2, 4, 6, 9, 12, 16, 20, 25, 30,
	};
	u32 sum, my_gold;
	u8	badge_cnt;

	badge_cnt = MyStatus_GetBadgeCount(my_status);
	sum =  GetStockPokeMaxLevel(ppt) * 4 * Late[badge_cnt];

	my_gold = MyStatus_GetGold(my_status);

	if(sum > my_gold){
		sum = my_gold;
	}

	return sum;
}

//============================================================================================
/**
 * �|�P���������t���O���Z�b�g
 *
 * @param[in]	bw			�퓬���[�N�\����
 * @param[in]	client_no	�Z�b�g����|�P������ClientNo
 */
//============================================================================================
void	FT_ZukanFlagSetSee(BATTLE_WORK *bw,int client_no)
{
	int				client_type;
	POKEMON_PARAM	*pp;
	int				sel_mons_no;

	client_type=CT_CPClientTypeGet(bw->client_param[client_no]);
	sel_mons_no=ST_ServerParamDataGet(bw,bw->server_param,ID_SP_sel_mons_no,client_no);
	pp=BattleWorkPokemonParamGet(bw,client_no,sel_mons_no);

	if((bw->fight_type&FIGHT_TYPE_NO_ZUKAN)==0){
		if((client_type&CLIENT_ENEMY_FLAG)||
		   (bw->fight_type==FIGHT_TYPE_2vs2_YASEI)||
		   (bw->fight_type==FIGHT_TYPE_AI_MULTI)){
			ZukanWork_SetPokeSee(bw->zw,pp);
		}
	}
	//�����̎莝���̃~�m���b�`�́A�t�H�������L�����邽�߂ɏ�ɍX�V
	if(((client_type&CLIENT_ENEMY_FLAG)==0)&&
	    (PokeParaGet(pp,ID_PARA_monsno_egg,NULL)==MONSNO_MINOMUTTI)){
		ZukanWork_SetPokeGet(bw->zw,pp);
	}
}

//============================================================================================
/**
 * �|�P�����Q�b�g�t���O���Z�b�g
 *
 * @param[in]	bw			�퓬���[�N�\����
 * @param[in]	client_no	�Z�b�g����|�P������ClientNo
 */
//============================================================================================
void	FT_ZukanFlagSetGet(BATTLE_WORK *bw,int client_no)
{
	int	client_type;

	client_type=CT_CPClientTypeGet(bw->client_param[client_no]);

	if((bw->fight_type&FIGHT_TYPE_NO_ZUKAN)==0){
		if(client_type&CLIENT_ENEMY_FLAG){
			{
				POKEMON_PARAM	*pp;
				int				sel_mons_no;

				sel_mons_no=ST_ServerParamDataGet(bw,bw->server_param,ID_SP_sel_mons_no,client_no);

				pp=BattleWorkPokemonParamGet(bw,client_no,sel_mons_no);
				ZukanWork_SetPokeGet(bw->zw,pp);
			}
		}
	}
}

//============================================================================================
/**
 * �|�P�����Q�b�g�t���O���`�F�b�N
 *
 * @param[in]	bw			�퓬���[�N�\����
 * @param[in]	client_no	�Z�b�g����|�P������ClientNo
 */
//============================================================================================
BOOL	FT_ZukanFlagCheckGet(BATTLE_WORK *bw,int mons_no)
{
	return ZukanWork_GetPokeGetFlag(bw->zw,mons_no);
}

//============================================================================================
/**
 * �퓬�̃f�t�H���g�u�����h�ݒ������
 */
//============================================================================================
void	BattleDefaultBlendSet(void)
{
	G2_BlendNone();
}

//============================================================================================
/**
 *	�g���[�i�[���b�Z�[�W�\���֐�
 *
 * @param[in]	bw			�퓬�V�X�e���\���̂ւ̃|�C���^
 * @param[in]	tr_id		�\�����郁�b�Z�[�W�̃g���[�i�[ID
 * @param[in]	msg_type	�\�����郁�b�Z�[�W�̃^�C�v
 * @param[in]	wait		���b�Z�[�W�\���E�G�C�g
 *
 */
//============================================================================================
u8	TrainerMSG_Print(BATTLE_WORK *bw,int tr_id,int client_no,int msg_type,int wait)
{
	GF_BGL_BMPWIN	*win=BattleWorkGF_BGL_BMPWINGet(bw,TALK_WIN_NO);
	int				index;

	//�o�g���^���[�́A�ʂ̕���
	if(bw->fight_type&FIGHT_TYPE_TOWER){
		//Wifi�g���[�i�[�Ȃ�A�ȈՉ�b�𐶐�
		if(tr_id==BATTLE_TOWER_TRAINER_ID){
			{
				STRBUF	*msg;

				if(msg_type==TRMSG_FIGHT_WIN){
					msg=PMSDAT_ToString(&bw->trainer_data[client_no].win_word,HEAPID_BATTLE);
				}
				else{
					msg=PMSDAT_ToString(&bw->trainer_data[client_no].lose_word,HEAPID_BATTLE);
				}
				GF_BGL_BmpWinDataFill(win,0xff);
				index=GF_STR_PrintSimple(win,FONT_TALK,msg,0,0,wait,BattleMSG_CallBack);
				STRBUF_Delete(msg);
			}
		}
		else{
			{
				MSGDATA_MANAGER	*man;  
				STRBUF			*msg;
				int				strID;

				if(msg_type==TRMSG_FIGHT_WIN){
					strID=tr_id*3+1;
				}
				else{
					strID=tr_id*3+2;
				}

				man=MSGMAN_Create(MSGMAN_TYPE_NORMAL,ARC_MSG,NARC_msg_tower_trainer_dat,HEAPID_BATTLE);
				msg=MSGMAN_AllocString(man,strID);
				GF_BGL_BmpWinDataFill(win,0xff);
				index=GF_STR_PrintSimple(win,FONT_TALK,msg,0,0,wait,BattleMSG_CallBack);
				STRBUF_Delete(msg);
				MSGMAN_Delete(man);
			}
		}
	}
	else{
		TT_TrainerMessageGet(tr_id,msg_type,bw->msg_buf,HEAPID_BATTLE);
		GF_BGL_BmpWinDataFill(win,0xff);
		index=GF_STR_PrintSimple(win,FONT_TALK,bw->msg_buf,0,0,wait,BattleMSG_CallBack);
	}
	return index;
}

//============================================================================================
/**
 *	�퓬���b�Z�[�W�\���֐�
 *
 * @param[in]	bw			�퓬�V�X�e���\���̂ւ̃|�C���^
 * @param[in]	win			BMPWIN�V�X�e���ݒ�\���̂ւ̃|�C���^
 * @param[in]	msg_m		���b�Z�[�W�}�l�[�W���[�\���̂ւ̃|�C���^
 * @param[in]	mp			���b�Z�[�W�p�����[�^�\���̂ւ̃|�C���^
 * @param[in]	wait		���b�Z�[�W�\���E�G�C�g
 *
 */
//============================================================================================
u8	BattleMSG_Print(BATTLE_WORK *bw,MSGDATA_MANAGER *msg_m,MESSAGE_PARAM *mp,int wait)
{
	GF_BGL_BMPWIN	*win=BattleWorkGF_BGL_BMPWINGet(bw,TALK_WIN_NO);

	BattleMSG_DirCheck(bw,mp);
	BattleMSG_TagExpand(bw,mp);
	BattleMSG_MsgExpand(bw,msg_m,mp);

	GF_BGL_BmpWinDataFill(win,0xff);

	return GF_STR_PrintSimple(win,FONT_TALK,bw->msg_buf,0,0,wait,BattleMSG_CallBack);
}

//============================================================================================
/**
 *	�퓬���b�Z�[�W�\���֐��iX,Y�w�肠��j
 *
 * @param[in]	bw			�퓬�V�X�e���\���̂ւ̃|�C���^
 * @param[in]	win			BMPWIN�V�X�e���ݒ�\���̂ւ̃|�C���^
 * @param[in]	msg_m		���b�Z�[�W�}�l�[�W���[�\���̂ւ̃|�C���^
 * @param[in]	mp			���b�Z�[�W�p�����[�^�\���̂ւ̃|�C���^
 * @param[in]	x			���b�Z�[�W�J�n�ʒu�I�t�Z�b�g�iX�j
 * @param[in]	y			���b�Z�[�W�J�n�ʒu�I�t�Z�b�g�iY�j
 * @param[in]	flag		�E�C���h�E���̃N���A�����邩�ǂ���(FALSE:�N���A���Ȃ��@TRUE:�N���A�j
 * @param[in]	width		���b�Z�[�W��\������̈�̉����i�E�l�߂���Ƃ��̊J�n�ʒu�̕␳�Ɏg�p�j
 * @param[in]	wait		���b�Z�[�W�\���E�G�C�g
 *
 */
//============================================================================================
u8	StatusMSG_Print(BATTLE_WORK *bw,GF_BGL_BMPWIN *win,MSGDATA_MANAGER *msg_m,MESSAGE_PARAM *mp,
					  int x,int y,int flag,int width,int wait)
{
	int	ofs;

	BattleMSG_DirCheck(bw,mp);
	BattleMSG_TagExpand(bw,mp);
	BattleMSG_MsgExpand(bw,msg_m,mp);

	if(flag&BATTLE_MSG_WIN_CLEAR){
		GF_BGL_BmpWinDataFill(win,0xff);
	}

	if(flag&BATTLE_MSG_WIDTH_OFS){
		ofs=width-FontProc_GetPrintStrWidth(FONT_SYSTEM,bw->msg_buf,0);
	}
	else{
		ofs=0;
	}

	return GF_STR_PrintSimple(win,FONT_SYSTEM,bw->msg_buf,x+ofs,y,wait,BattleMSG_CallBack);
}

//============================================================================================
/**
 *	�퓬���b�Z�[�WDirCheck�i���b�Z�[�W�́A�u�����Ắv��u�₹���́v�Ȃǂ̌����Ɋւ��锻�������j
 *
 * @param[in]	bw			�퓬�V�X�e���\���̂ւ̃|�C���^
 * @param[in]	mp			MESSAGE_PARAM�\���̂ւ̃|�C���^
 *
 */
//============================================================================================
static	void	BattleMSG_DirCheck(BATTLE_WORK *bw,MESSAGE_PARAM *mp)
{
	u32	fight_type;

	fight_type=BattleWorkFightTypeGet(bw);

	if(mp->msg_tag&TAG_NO_DIR){
		return;
	}

	if(mp->msg_tag&TAG_DIR){
		if(BattleWorkMineEnemyCheck(bw,mp->msg_client)){
			mp->msg_id++;
		}
		return;
	}

	switch(mp->msg_tag&TAG_NO_DIR_OFF){
	case TAG_NONE:							//�^�O�Ȃ�
	case TAG_WAZA:							//�Z��
	case TAG_STAT:							//�X�e�[�^�X��
	case TAG_ITEM:							//���
	case TAG_NUM:							//���l
	case TAG_NUMS:							//���l�i�E�l�߁j
	case TAG_TRNAME:						//trainer��
	case TAG_WAZA_WAZA:						//�Z��			�Z��
	case TAG_ITEM_WAZA:						//���		�Z��
	case TAG_NUM_NUM:						//���l			���l
	case TAG_TRNAME_TRNAME:					//trainer��		trainer��
	case TAG_TRNAME_NICK:					//trainer��		nickname
	case TAG_TRNAME_ITEM:					//trainer��		���
	case TAG_TRNAME_NUM:					//trainer��		���l
	case TAG_TRTYPE_TRNAME:					//trainer���	trainer��
	case TAG_TRNAME_NICK_NICK:				//trainer��		nickname		nickname
	case TAG_TRTYPE_TRNAME_NICK:			//trainer���	trainer��		nickname
	case TAG_TRTYPE_TRNAME_ITEM:			//trainer���	trainer��		���
	case TAG_TRNAME_NICK_TRNAME_NICK:		//trainer��		nickname		trainer��		nickname
	case TAG_TRTYPE_TRNAME_NICK_NICK:		//trainer���	trainer��		nickname		nickname
	case TAG_TRTYPE_TRNAME_NICK_TRNAME:		//trainer���	trainer��		nickname		trainer��
	case TAG_TRTYPE_TRNAME_TRTYPE_TRNAME:	//trainer���	trainer��		trainer���		trainer��
	case TAG_TRTYPE_TRNAME_NICKx2:			//trainer���	trainer��		nickname ���Q
		break;
	case TAG_NONE_DIR:						//�^�O�Ȃ��i�Ă��A�݂������肠��j
		if(BattleWorkMineEnemyCheck(bw,mp->msg_para[0]&0xff)){
			mp->msg_id++;
		}
		break;
	case TAG_NICK:							//nickname
	case TAG_NICK_WAZA:						//nickname		�Z��
	case TAG_NICK_TOKU:						//nickname		������
	case TAG_NICK_STAT:						//nickname		�X�e�[�^�X��
	case TAG_NICK_TYPE:						//nickname		�^�C�v��
	case TAG_NICK_POKE:						//nickname		�|�P������
	case TAG_NICK_ITEM:						//nickname		���
	case TAG_NICK_PLOC:						//nickname		�|���b�N��
	case TAG_NICK_NUM:						//nickname		���l
	case TAG_NICK_TRNAME:					//nickname		trainer��
	case TAG_NICK_BOX:						//nickname		�{�b�N�X��
	case TAG_NICK_WAZA_WAZA:				//nickname		�Z��			�Z��
	case TAG_NICK_WAZA_NUM:					//nickname		�Z��			���l
	case TAG_NICK_TOKU_WAZA:				//nickname		������			�Z��
	case TAG_NICK_TOKU_ITEM:				//nickname		������			���
	case TAG_NICK_TOKU_STAT:				//nickname		������			�X�e�[�^�X��
	case TAG_NICK_TOKU_TYPE:				//nickname		������			�^�C�v��
	case TAG_NICK_TOKU_COND:				//nickname		������			��Ԉُ햼
	case TAG_NICK_TOKU_NUM:					//nickname		������			���l
	case TAG_NICK_ITEM_WAZA:				//nickname		���			�Z��
	case TAG_NICK_ITEM_STAT:				//nickname		���			�X�e�[�^�X��
	case TAG_NICK_ITEM_COND:				//nickname		���			��Ԉُ햼
	case TAG_NICK_BOX_BOX:					//nickname		�{�b�N�X��		�{�b�N�X��
		if(BattleWorkMineEnemyCheck(bw,mp->msg_para[0]&0xff)){
			mp->msg_id++;
			if(fight_type&FIGHT_TYPE_TRAINER){
				mp->msg_id++;
			}
		}
		break;
	case TAG_WAZA_DIR:						//�Z���i�Ă��A�݂������肠��j
		if(BattleWorkMineEnemyCheck(bw,mp->msg_para[1]&0xff)){
			mp->msg_id++;
		}
		break;
	case TAG_WAZA_NICK:						//�Z��			nickname
	case TAG_TOKU_NICK:						//������		nickname
	case TAG_ITEM_NICK_TASTE:				//���		nickname		�؂̎��̖�
		if(BattleWorkMineEnemyCheck(bw,mp->msg_para[1]&0xff)){
			mp->msg_id++;
			if(fight_type&FIGHT_TYPE_TRAINER){
				mp->msg_id++;
			}
		}
		break;
	case TAG_NICK_NICK:						//nickname		nickname
	case TAG_NICK_NICK_WAZA:				//nickname		nickname		�Z��
	case TAG_NICK_NICK_TOKU:				//nickname		nickname		������
	case TAG_NICK_NICK_ITEM:				//nickname		nickname		���
		if(BattleWorkMineEnemyCheck(bw,mp->msg_para[0]&0xff)){
			mp->msg_id+=3;
			if(fight_type&FIGHT_TYPE_TRAINER){
				mp->msg_id+=2;
			}
			if(BattleWorkMineEnemyCheck(bw,mp->msg_para[1]&0xff)){
				mp->msg_id++;
			}
		}
		else{
			if(BattleWorkMineEnemyCheck(bw,mp->msg_para[1]&0xff)){
				mp->msg_id++;
				if(fight_type&FIGHT_TYPE_TRAINER){
					mp->msg_id++;
				}
			}
		}
		break;
	case TAG_NICK_TOKU_NICK:				//nickname		������			nickname
	case TAG_NICK_ITEM_NICK:				//nickname		������			nickname
	case TAG_NICK_TOKU_NICK_WAZA:			//nickname		������			nickname		�Z��
	case TAG_NICK_TOKU_NICK_TOKU:			//nickname		������			nickname		������
	case TAG_NICK_TOKU_NICK_STAT:			//nickname		������			nickname		�X�e�[�^�X��
	case TAG_NICK_ITEM_NICK_ITEM:			//nickname		���			nickname		���
		if(BattleWorkMineEnemyCheck(bw,mp->msg_para[0]&0xff)){
			mp->msg_id+=3;
			if(fight_type&FIGHT_TYPE_TRAINER){
				mp->msg_id+=2;
			}
			if(BattleWorkMineEnemyCheck(bw,mp->msg_para[2]&0xff)){
				mp->msg_id++;
			}
		}
		else{
			if(BattleWorkMineEnemyCheck(bw,mp->msg_para[2]&0xff)){
				mp->msg_id++;
				if(fight_type&FIGHT_TYPE_TRAINER){
					mp->msg_id++;
				}
			}
		}
		break;
	default:
		GF_ASSERT_MSG(0,"���݂��Ȃ�TAG�ł��I\n");
		break;
	}
}

//============================================================================================
/**
 *	�퓬���b�Z�[�W�^�O�W�J�֐�
 *
 * @param[in]	bw			�퓬�V�X�e���\���̂ւ̃|�C���^
 * @param[in]	mp			MESSAGE_PARAM�\���̂ւ̃|�C���^
 *
 */
//============================================================================================
static	void	BattleMSG_TagExpand(BATTLE_WORK *bw,MESSAGE_PARAM *mp)
{
	switch(mp->msg_tag&TAG_NO_DIR_OFF){
	case TAG_NONE:						//�^�O�Ȃ�
	case TAG_NONE_DIR:					//�^�O�Ȃ��i�Ă��A�݂������肠��j
		break;
	case TAG_NICK:						//nickname
		BattleMSG_NicknameGet(	bw,STR_TEMP_BUF0,mp->msg_para[0]);
		break;
	case TAG_WAZA:						//�Z��
	case TAG_WAZA_DIR:					//�Z���i�Ă��A�݂������肠��j	
		BattleMSG_WazaGet(		bw,STR_TEMP_BUF0,mp->msg_para[0]);
		break;
	case TAG_STAT:						//�X�e�[�^�X��
		BattleMSG_StatusGet(	bw,STR_TEMP_BUF0,mp->msg_para[0]);
		break;
	case TAG_ITEM:						//���
		BattleMSG_ItemGet(		bw,STR_TEMP_BUF0,mp->msg_para[0]);
		break;
	case TAG_NUM:						//���l
		BattleMSG_NumGet(		bw,STR_TEMP_BUF0,mp->msg_para[0]);
		break;
	case TAG_NUMS:						//���l�i�E�l�߁j
		BattleMSG_NumsGet(		bw,STR_TEMP_BUF0,mp->msg_para[0],mp->msg_keta);
		break;
	case TAG_TRNAME:					//trainer��
		BattleMSG_TRNameGet(	bw,STR_TEMP_BUF0,mp->msg_para[0]);
		break;
	case TAG_NICK_NICK:					//nickname		nickname
		BattleMSG_NicknameGet(	bw,STR_TEMP_BUF0,mp->msg_para[0]);
		BattleMSG_NicknameGet(	bw,STR_TEMP_BUF1,mp->msg_para[1]);
		break;
	case TAG_NICK_WAZA:					//nickname		�Z��
		BattleMSG_NicknameGet(	bw,STR_TEMP_BUF0,mp->msg_para[0]);
		BattleMSG_WazaGet(		bw,STR_TEMP_BUF1,mp->msg_para[1]);
		break;
	case TAG_NICK_TOKU:					//nickname		������
		BattleMSG_NicknameGet(	bw,STR_TEMP_BUF0,mp->msg_para[0]);
		BattleMSG_TokuseiGet(	bw,STR_TEMP_BUF1,mp->msg_para[1]);
		break;
	case TAG_NICK_STAT:					//nickname		�X�e�[�^�X��
		BattleMSG_NicknameGet(	bw,STR_TEMP_BUF0,mp->msg_para[0]);
		BattleMSG_StatusGet(	bw,STR_TEMP_BUF1,mp->msg_para[1]);
		break;
	case TAG_NICK_TYPE:					//nickname		�^�C�v��
		BattleMSG_NicknameGet(	bw,STR_TEMP_BUF0,mp->msg_para[0]);
		BattleMSG_TypeGet(		bw,STR_TEMP_BUF1,mp->msg_para[1]);
		break;
	case TAG_NICK_POKE:					//nickname		�|�P������
		BattleMSG_NicknameGet(	bw,STR_TEMP_BUF0,mp->msg_para[0]);
		BattleMSG_PokenameGet(	bw,STR_TEMP_BUF1,mp->msg_para[1]);
		break;
	case TAG_NICK_ITEM:					//nickname		���
		BattleMSG_NicknameGet(	bw,STR_TEMP_BUF0,mp->msg_para[0]);
		BattleMSG_ItemGet(		bw,STR_TEMP_BUF1,mp->msg_para[1]);
		break;
	case TAG_NICK_PLOC:					//nickname		�|���b�N��
		BattleMSG_NicknameGet(	bw,STR_TEMP_BUF0,mp->msg_para[0]);
		BattleMSG_PolockGet(	bw,STR_TEMP_BUF1,mp->msg_para[1]);
		break;
	case TAG_NICK_NUM:					//nickname		���l
		BattleMSG_NicknameGet(	bw,STR_TEMP_BUF0,mp->msg_para[0]);
		BattleMSG_NumGet(		bw,STR_TEMP_BUF1,mp->msg_para[1]);
		break;
	case TAG_NICK_TRNAME:				//nickname		trainer��
		BattleMSG_NicknameGet(	bw,STR_TEMP_BUF0,mp->msg_para[0]);
		BattleMSG_TRNameGet(	bw,STR_TEMP_BUF1,mp->msg_para[1]);
		break;
	case TAG_NICK_BOX:					//nickname		�{�b�N�X��
		BattleMSG_NicknameGet(	bw,STR_TEMP_BUF0,mp->msg_para[0]);
		BattleMSG_BoxNameGet(	bw,STR_TEMP_BUF1,mp->msg_para[1]);
		break;
	case TAG_WAZA_NICK:					//�Z��			nickname
		BattleMSG_WazaGet(		bw,STR_TEMP_BUF0,mp->msg_para[0]);
		BattleMSG_NicknameGet(	bw,STR_TEMP_BUF1,mp->msg_para[1]);
		break;
	case TAG_WAZA_WAZA:					//�Z��			�Z��
		BattleMSG_WazaGet(		bw,STR_TEMP_BUF0,mp->msg_para[0]);
		BattleMSG_WazaGet(		bw,STR_TEMP_BUF1,mp->msg_para[1]);
		break;
	case TAG_TOKU_NICK:					//������		nickname
		BattleMSG_TokuseiGet(	bw,STR_TEMP_BUF0,mp->msg_para[0]);
		BattleMSG_NicknameGet(	bw,STR_TEMP_BUF1,mp->msg_para[1]);
		break;
	case TAG_ITEM_WAZA:					//���		�Z��
		BattleMSG_ItemGet(		bw,STR_TEMP_BUF0,mp->msg_para[0]);
		BattleMSG_WazaGet(		bw,STR_TEMP_BUF1,mp->msg_para[1]);
		break;
	case TAG_NUM_NUM:					//���l			���l
		BattleMSG_NumGet(		bw,STR_TEMP_BUF0,mp->msg_para[0]);
		BattleMSG_NumGet(		bw,STR_TEMP_BUF1,mp->msg_para[1]);
		break;
	case TAG_TRNAME_TRNAME:				//trainer��		trainer��
		BattleMSG_TRNameGet(	bw,STR_TEMP_BUF0,mp->msg_para[0]);
		BattleMSG_TRNameGet(	bw,STR_TEMP_BUF1,mp->msg_para[1]);
		break;
	case TAG_TRNAME_NICK:				//trainer��		nickname
		BattleMSG_TRNameGet(	bw,STR_TEMP_BUF0,mp->msg_para[0]);
		BattleMSG_NicknameGet(	bw,STR_TEMP_BUF1,mp->msg_para[1]);
		break;
	case TAG_TRNAME_ITEM:				//trainer��		���
		BattleMSG_TRNameGet(	bw,STR_TEMP_BUF0,mp->msg_para[0]);
		BattleMSG_ItemGet(		bw,STR_TEMP_BUF1,mp->msg_para[1]);
		break;
	case TAG_TRNAME_NUM:				//trainer��		���l
		BattleMSG_TRNameGet(	bw,STR_TEMP_BUF0,mp->msg_para[0]);
		BattleMSG_NumGet(		bw,STR_TEMP_BUF1,mp->msg_para[1]);
		break;
	case TAG_TRTYPE_TRNAME:				//trainer���	trainer��
		BattleMSG_TRTypeGet(	bw,STR_TEMP_BUF0,mp->msg_para[0]);
		BattleMSG_TRNameGet(	bw,STR_TEMP_BUF1,mp->msg_para[1]);
		break;
	case TAG_NICK_NICK_WAZA:			//nickname		nickname		�Z��
		BattleMSG_NicknameGet(	bw,STR_TEMP_BUF0,mp->msg_para[0]);
		BattleMSG_NicknameGet(	bw,STR_TEMP_BUF1,mp->msg_para[1]);
		BattleMSG_WazaGet(		bw,STR_TEMP_BUF2,mp->msg_para[2]);
		break;
	case TAG_NICK_NICK_TOKU:			//nickname		nickname		������
		BattleMSG_NicknameGet(	bw,STR_TEMP_BUF0,mp->msg_para[0]);
		BattleMSG_NicknameGet(	bw,STR_TEMP_BUF1,mp->msg_para[1]);
		BattleMSG_TokuseiGet(	bw,STR_TEMP_BUF2,mp->msg_para[2]);
		break;
	case TAG_NICK_NICK_ITEM:			//nickname		nickname		���
		BattleMSG_NicknameGet(	bw,STR_TEMP_BUF0,mp->msg_para[0]);
		BattleMSG_NicknameGet(	bw,STR_TEMP_BUF1,mp->msg_para[1]);
		BattleMSG_ItemGet(		bw,STR_TEMP_BUF2,mp->msg_para[2]);
		break;
	case TAG_NICK_WAZA_WAZA:			//nickname		�Z��			�Z��
		BattleMSG_NicknameGet(	bw,STR_TEMP_BUF0,mp->msg_para[0]);
		BattleMSG_WazaGet(		bw,STR_TEMP_BUF1,mp->msg_para[1]);
		BattleMSG_WazaGet(		bw,STR_TEMP_BUF2,mp->msg_para[2]);
		break;
	case TAG_NICK_WAZA_NUM:				//nickname		�Z��			���l
		BattleMSG_NicknameGet(	bw,STR_TEMP_BUF0,mp->msg_para[0]);
		BattleMSG_WazaGet(		bw,STR_TEMP_BUF1,mp->msg_para[1]);
		BattleMSG_NumGet(		bw,STR_TEMP_BUF2,mp->msg_para[2]);
		break;
	case TAG_NICK_TOKU_NICK:			//nickname		������			nickname
		BattleMSG_NicknameGet(	bw,STR_TEMP_BUF0,mp->msg_para[0]);
		BattleMSG_TokuseiGet(	bw,STR_TEMP_BUF1,mp->msg_para[1]);
		BattleMSG_NicknameGet(	bw,STR_TEMP_BUF2,mp->msg_para[2]);
		break;
	case TAG_NICK_TOKU_WAZA:			//nickname		������			�Z��
		BattleMSG_NicknameGet(	bw,STR_TEMP_BUF0,mp->msg_para[0]);
		BattleMSG_TokuseiGet(	bw,STR_TEMP_BUF1,mp->msg_para[1]);
		BattleMSG_WazaGet(		bw,STR_TEMP_BUF2,mp->msg_para[2]);
		break;
	case TAG_NICK_TOKU_ITEM:			//nickname		������			���
		BattleMSG_NicknameGet(	bw,STR_TEMP_BUF0,mp->msg_para[0]);
		BattleMSG_TokuseiGet(	bw,STR_TEMP_BUF1,mp->msg_para[1]);
		BattleMSG_ItemGet(		bw,STR_TEMP_BUF2,mp->msg_para[2]);
		break;
	case TAG_NICK_TOKU_STAT:			//nickname		������			�X�e�[�^�X��
		BattleMSG_NicknameGet(	bw,STR_TEMP_BUF0,mp->msg_para[0]);
		BattleMSG_TokuseiGet(	bw,STR_TEMP_BUF1,mp->msg_para[1]);
		BattleMSG_StatusGet(	bw,STR_TEMP_BUF2,mp->msg_para[2]);
		break;
	case TAG_NICK_TOKU_TYPE:			//nickname		������			�^�C�v��
		BattleMSG_NicknameGet(	bw,STR_TEMP_BUF0,mp->msg_para[0]);
		BattleMSG_TokuseiGet(	bw,STR_TEMP_BUF1,mp->msg_para[1]);
		BattleMSG_TypeGet(		bw,STR_TEMP_BUF2,mp->msg_para[2]);
		break;
	case TAG_NICK_TOKU_COND:			//nickname		������			��Ԉُ햼
		BattleMSG_NicknameGet(	bw,STR_TEMP_BUF0,mp->msg_para[0]);
		BattleMSG_TokuseiGet(	bw,STR_TEMP_BUF1,mp->msg_para[1]);
		BattleMSG_ConditionGet(	bw,STR_TEMP_BUF2,mp->msg_para[2]);
		break;
	case TAG_NICK_TOKU_NUM:				//nickname		������			���l
		BattleMSG_NicknameGet(	bw,STR_TEMP_BUF0,mp->msg_para[0]);
		BattleMSG_TokuseiGet(	bw,STR_TEMP_BUF1,mp->msg_para[1]);
		BattleMSG_NumGet(		bw,STR_TEMP_BUF2,mp->msg_para[2]);
		break;
	case TAG_NICK_ITEM_NICK:			//nickname		������			nickname
		BattleMSG_NicknameGet(	bw,STR_TEMP_BUF0,mp->msg_para[0]);
		BattleMSG_ItemGet(		bw,STR_TEMP_BUF1,mp->msg_para[1]);
		BattleMSG_NicknameGet(	bw,STR_TEMP_BUF2,mp->msg_para[2]);
		break;
	case TAG_NICK_ITEM_WAZA:			//nickname		���			�Z��
		BattleMSG_NicknameGet(	bw,STR_TEMP_BUF0,mp->msg_para[0]);
		BattleMSG_ItemGet(		bw,STR_TEMP_BUF1,mp->msg_para[1]);
		BattleMSG_WazaGet(		bw,STR_TEMP_BUF2,mp->msg_para[2]);
		break;
	case TAG_NICK_ITEM_STAT:			//nickname		���			�X�e�[�^�X��
		BattleMSG_NicknameGet(	bw,STR_TEMP_BUF0,mp->msg_para[0]);
		BattleMSG_ItemGet(		bw,STR_TEMP_BUF1,mp->msg_para[1]);
		BattleMSG_StatusGet(	bw,STR_TEMP_BUF2,mp->msg_para[2]);
		break;
	case TAG_NICK_ITEM_COND:			//nickname		���			��Ԉُ햼
		BattleMSG_NicknameGet(	bw,STR_TEMP_BUF0,mp->msg_para[0]);
		BattleMSG_ItemGet(		bw,STR_TEMP_BUF1,mp->msg_para[1]);
		BattleMSG_ConditionGet(	bw,STR_TEMP_BUF2,mp->msg_para[2]);
		break;
	case TAG_NICK_BOX_BOX:				//nickname		�{�b�N�X��		�{�b�N�X��
		BattleMSG_NicknameGet(	bw,STR_TEMP_BUF0,mp->msg_para[0]);
		BattleMSG_BoxNameGet(	bw,STR_TEMP_BUF1,mp->msg_para[1]);
		BattleMSG_BoxNameGet(	bw,STR_TEMP_BUF2,mp->msg_para[2]);
		break;
	case TAG_ITEM_NICK_TASTE:			//���		nickname		�؂̎��̖�
		BattleMSG_ItemGet(		bw,STR_TEMP_BUF0,mp->msg_para[0]);
		BattleMSG_NicknameGet(	bw,STR_TEMP_BUF1,mp->msg_para[1]);
		BattleMSG_TasteGet(		bw,STR_TEMP_BUF2,mp->msg_para[2]);
		break;
	case TAG_TRNAME_NICK_NICK:			//trainer��		nickname		nickname
		BattleMSG_TRNameGet(	bw,STR_TEMP_BUF0,mp->msg_para[0]);
		BattleMSG_NicknameGet(	bw,STR_TEMP_BUF1,mp->msg_para[1]);
		BattleMSG_NicknameGet(	bw,STR_TEMP_BUF2,mp->msg_para[2]);
		break;
	case TAG_TRTYPE_TRNAME_NICK:		//trainer���	trainer��		nickname
		BattleMSG_TRTypeGet(	bw,STR_TEMP_BUF0,mp->msg_para[0]);
		BattleMSG_TRNameGet(	bw,STR_TEMP_BUF1,mp->msg_para[1]);
		BattleMSG_NicknameGet(	bw,STR_TEMP_BUF2,mp->msg_para[2]);
		break;
	case TAG_TRTYPE_TRNAME_ITEM:		//trainer���	trainer��		���
		BattleMSG_TRTypeGet(	bw,STR_TEMP_BUF0,mp->msg_para[0]);
		BattleMSG_TRNameGet(	bw,STR_TEMP_BUF1,mp->msg_para[1]);
		BattleMSG_ItemGet(		bw,STR_TEMP_BUF2,mp->msg_para[2]);
		break;
	case TAG_NICK_TOKU_NICK_WAZA:		//nickname		������			nickname		�Z��
		BattleMSG_NicknameGet(	bw,STR_TEMP_BUF0,mp->msg_para[0]);
		BattleMSG_TokuseiGet(	bw,STR_TEMP_BUF1,mp->msg_para[1]);
		BattleMSG_NicknameGet(	bw,STR_TEMP_BUF2,mp->msg_para[2]);
		BattleMSG_WazaGet(		bw,STR_TEMP_BUF3,mp->msg_para[3]);
		break;
	case TAG_NICK_TOKU_NICK_TOKU:		//nickname		������			nickname		������
		BattleMSG_NicknameGet(	bw,STR_TEMP_BUF0,mp->msg_para[0]);
		BattleMSG_TokuseiGet(	bw,STR_TEMP_BUF1,mp->msg_para[1]);
		BattleMSG_NicknameGet(	bw,STR_TEMP_BUF2,mp->msg_para[2]);
		BattleMSG_TokuseiGet(	bw,STR_TEMP_BUF3,mp->msg_para[3]);
		break;
	case TAG_NICK_TOKU_NICK_STAT:		//nickname		������			nickname		�X�e�[�^�X��
		BattleMSG_NicknameGet(	bw,STR_TEMP_BUF0,mp->msg_para[0]);
		BattleMSG_TokuseiGet(	bw,STR_TEMP_BUF1,mp->msg_para[1]);
		BattleMSG_NicknameGet(	bw,STR_TEMP_BUF2,mp->msg_para[2]);
		BattleMSG_StatusGet(	bw,STR_TEMP_BUF3,mp->msg_para[3]);
		break;
	case TAG_NICK_ITEM_NICK_ITEM:		//nickname		���			nickname		���
		BattleMSG_NicknameGet(	bw,STR_TEMP_BUF0,mp->msg_para[0]);
		BattleMSG_ItemGet(		bw,STR_TEMP_BUF1,mp->msg_para[1]);
		BattleMSG_NicknameGet(	bw,STR_TEMP_BUF2,mp->msg_para[2]);
		BattleMSG_ItemGet(		bw,STR_TEMP_BUF3,mp->msg_para[3]);
		break;
	case TAG_TRNAME_NICK_TRNAME_NICK:	//trainer��		nickname		trainer��		nickname
		BattleMSG_TRNameGet(	bw,STR_TEMP_BUF0,mp->msg_para[0]);
		BattleMSG_NicknameGet(	bw,STR_TEMP_BUF1,mp->msg_para[1]);
		BattleMSG_TRNameGet(	bw,STR_TEMP_BUF2,mp->msg_para[2]);
		BattleMSG_NicknameGet(	bw,STR_TEMP_BUF3,mp->msg_para[3]);
		break;
	case TAG_TRTYPE_TRNAME_NICK_NICK:	//trainer���	trainer��		nickname		nickname
		BattleMSG_TRTypeGet(	bw,STR_TEMP_BUF0,mp->msg_para[0]);
		BattleMSG_TRNameGet(	bw,STR_TEMP_BUF1,mp->msg_para[1]);
		BattleMSG_NicknameGet(	bw,STR_TEMP_BUF2,mp->msg_para[2]);
		BattleMSG_NicknameGet(	bw,STR_TEMP_BUF3,mp->msg_para[3]);
		break;
	case TAG_TRTYPE_TRNAME_NICK_TRNAME:	//trainer���	trainer��		nickname		trainer��
		BattleMSG_TRTypeGet(	bw,STR_TEMP_BUF0,mp->msg_para[0]);
		BattleMSG_TRNameGet(	bw,STR_TEMP_BUF1,mp->msg_para[1]);
		BattleMSG_NicknameGet(	bw,STR_TEMP_BUF2,mp->msg_para[2]);
		BattleMSG_TRNameGet(	bw,STR_TEMP_BUF3,mp->msg_para[3]);
		break;
	case TAG_TRTYPE_TRNAME_TRTYPE_TRNAME:	//trainer���	trainer��		trainer���		trainer��
		BattleMSG_TRTypeGet(	bw,STR_TEMP_BUF0,mp->msg_para[0]);
		BattleMSG_TRNameGet(	bw,STR_TEMP_BUF1,mp->msg_para[1]);
		BattleMSG_TRTypeGet(	bw,STR_TEMP_BUF2,mp->msg_para[2]);
		BattleMSG_TRNameGet(	bw,STR_TEMP_BUF3,mp->msg_para[3]);
		break;
	case TAG_TRTYPE_TRNAME_NICKx2:		//trainer���	trainer��		nickname ���Q
		BattleMSG_TRTypeGet(	bw,STR_TEMP_BUF0,mp->msg_para[0]);
		BattleMSG_TRNameGet(	bw,STR_TEMP_BUF1,mp->msg_para[1]);
		BattleMSG_NicknameGet(	bw,STR_TEMP_BUF2,mp->msg_para[2]);
		BattleMSG_TRTypeGet(	bw,STR_TEMP_BUF3,mp->msg_para[3]);
		BattleMSG_TRNameGet(	bw,STR_TEMP_BUF4,mp->msg_para[4]);
		BattleMSG_NicknameGet(	bw,STR_TEMP_BUF5,mp->msg_para[5]);
		break;
	default:
		GF_ASSERT_MSG(0,"���݂��Ȃ�TAG�ł��I\n");
		break;
	}
}

//============================================================================================
/**
 *	MESSAGE_PARAM�\���̃f�[�^�����֐��i�j�b�N�l�[���j
 *
 * @param[in]	sp		�T�[�o�p�����[�^�\����
 * @param[in]	para	�����Ώۃp�����[�^�iSIDE_ATTACK�ASIDE_DEFENCE�Ȃǁj
 */
//============================================================================================
static	void	BattleMSG_NicknameGet(BATTLE_WORK *bw,u32 buf_id,int para)
{
	POKEMON_PARAM		*pp;

	pp=BattleWorkPokemonParamGet(bw,para&0xff,(para&0xff00)>>8);

	WORDSET_RegisterPokeNickName(bw->wordset,buf_id,&pp->ppp);
}

//============================================================================================
/**
 *	MESSAGE_PARAM�\���̃f�[�^�����֐��i�Z�i���o�[�j
 *
 * @param[in]	sp		�T�[�o�p�����[�^�\����
 * @param[in]	para	�����Ώۃp�����[�^�iSIDE_ATTACK�ASIDE_DEFENCE�Ȃǁj
 */
//============================================================================================
static	void	BattleMSG_WazaGet(BATTLE_WORK *bw,u32 buf_id,int para)
{
	WORDSET_RegisterWazaName(bw->wordset,buf_id,para);
}

//============================================================================================
/**
 *	MESSAGE_PARAM�\���̃f�[�^�����֐��i����i���o�[�j
 *
 * @param[in]	sp		�T�[�o�p�����[�^�\����
 * @param[in]	para	�����Ώۃp�����[�^�iSIDE_ATTACK�ASIDE_DEFENCE�Ȃǁj
 */
//============================================================================================
static	void	BattleMSG_ItemGet(BATTLE_WORK *bw,u32 buf_id,int para)
{
	WORDSET_RegisterItemName(bw->wordset,buf_id,para);
}

//============================================================================================
/**
 *	MESSAGE_PARAM�\���̃f�[�^�����֐��i���l�j
 *
 * @param[in]	sp		�T�[�o�p�����[�^�\����
 * @param[in]	para	�����Ώۃp�����[�^�iSIDE_ATTACK�ASIDE_DEFENCE�Ȃǁj
 */
//============================================================================================
static	void	BattleMSG_NumGet(BATTLE_WORK *bw,u32 buf_id,int para)
{
	WORDSET_RegisterNumber(bw->wordset,buf_id,para,5,NUMBER_DISPTYPE_LEFT,NUMBER_CODETYPE_DEFAULT);
}

//============================================================================================
/**
 *	MESSAGE_PARAM�\���̃f�[�^�����֐��i���l�E�l�߁j
 *
 * @param[in]	sp		�T�[�o�p�����[�^�\����
 * @param[in]	para	�����Ώۃp�����[�^�iSIDE_ATTACK�ASIDE_DEFENCE�Ȃǁj
 */
//============================================================================================
static	void	BattleMSG_NumsGet(BATTLE_WORK *bw,u32 buf_id,int para,int keta)
{
	if(keta){
		WORDSET_RegisterNumber(bw->wordset,buf_id,para,keta,NUMBER_DISPTYPE_SPACE,NUMBER_CODETYPE_DEFAULT);
	}
	else{
		WORDSET_RegisterNumber(bw->wordset,buf_id,para,5,NUMBER_DISPTYPE_SPACE,NUMBER_CODETYPE_DEFAULT);
	}
}

//============================================================================================
/**
 *	MESSAGE_PARAM�\���̃f�[�^�����֐��i�^�C�v�j
 *
 * @param[in]	sp		�T�[�o�p�����[�^�\����
 * @param[in]	para	�����Ώۃp�����[�^�iSIDE_ATTACK�ASIDE_DEFENCE�Ȃǁj
 */
//============================================================================================
static	void	BattleMSG_TypeGet(BATTLE_WORK *bw,u32 buf_id,int para)
{
	WORDSET_RegisterPokeTypeName(bw->wordset,buf_id,para);
}

//============================================================================================
/**
 *	MESSAGE_PARAM�\���̃f�[�^�����֐��i�����j
 *
 * @param[in]	sp		�T�[�o�p�����[�^�\����
 * @param[in]	para	�����Ώۃp�����[�^�iSIDE_ATTACK�ASIDE_DEFENCE�Ȃǁj
 */
//============================================================================================
static	void	BattleMSG_TokuseiGet(BATTLE_WORK *bw,u32 buf_id,int para)
{
	WORDSET_RegisterTokuseiName(bw->wordset,buf_id,para);
}

//============================================================================================
/**
 *	MESSAGE_PARAM�\���̃f�[�^�����֐��i�X�e�[�^�X���j
 *
 * @param[in]	sp		�T�[�o�p�����[�^�\����
 * @param[in]	para	�����Ώۃp�����[�^�iSIDE_ATTACK�ASIDE_DEFENCE�Ȃǁj
 */
//============================================================================================
static	void	BattleMSG_StatusGet(BATTLE_WORK *bw,u32 buf_id,int para)
{
	WORDSET_RegisterPokeStatusName(bw->wordset,buf_id,para);
}

//============================================================================================
/**
 *	MESSAGE_PARAM�\���̃f�[�^�����֐��i��Ԉُ햼�j
 *
 * @param[in]	sp		�T�[�o�p�����[�^�\����
 * @param[in]	para	�����Ώۃp�����[�^�iSIDE_ATTACK�ASIDE_DEFENCE�Ȃǁj
 */
//============================================================================================
static	void	BattleMSG_ConditionGet(BATTLE_WORK *bw,u32 buf_id,int para)
{
	WORDSET_RegisterBadConditionName(bw->wordset,buf_id,para);
}

//============================================================================================
/**
 *	MESSAGE_PARAM�\���̃f�[�^�����֐��i�|�P�������j
 *
 * @param[in]	sp		�T�[�o�p�����[�^�\����
 * @param[in]	para	�����Ώۃp�����[�^�iSIDE_ATTACK�ASIDE_DEFENCE�Ȃǁj
 */
//============================================================================================
static	void	BattleMSG_PokenameGet(BATTLE_WORK *bw,u32 buf_id,int para)
{
	POKEMON_PARAM		*pp;

	pp=BattleWorkPokemonParamGet(bw,para&0xff,(para&0xff00)>>8);

	WORDSET_RegisterPokeMonsName(bw->wordset,buf_id,&pp->ppp);
}

//============================================================================================
/**
 *	MESSAGE_PARAM�\���̃f�[�^�����֐��i�|���b�N���j
 *
 * @param[in]	sp		�T�[�o�p�����[�^�\����
 * @param[in]	para	�����Ώۃp�����[�^�iSIDE_ATTACK�ASIDE_DEFENCE�Ȃǁj
 */
//============================================================================================
static	void	BattleMSG_PolockGet(BATTLE_WORK *bw,u32 buf_id,int para)
{
}

//============================================================================================
/**
 *	MESSAGE_PARAM�\���̃f�[�^�����֐��i�؂̎��̖��j
 *
 * @param[in]	sp		�T�[�o�p�����[�^�\����
 * @param[in]	para	�����Ώۃp�����[�^�iSIDE_ATTACK�ASIDE_DEFENCE�Ȃǁj
 */
//============================================================================================
static	void	BattleMSG_TasteGet(BATTLE_WORK *bw,u32 buf_id,int para)
{
	WORDSET_RegisterSeedTasteName(bw->wordset,buf_id,para);
}

//============================================================================================
/**
 *	MESSAGE_PARAM�\���̃f�[�^�����֐��i�g���[�i�[��ʁj
 *
 * @param[in]	sp		�T�[�o�p�����[�^�\����
 * @param[in]	para	�����Ώۃp�����[�^�iSIDE_ATTACK�ASIDE_DEFENCE�Ȃǁj
 */
//============================================================================================
static	void	BattleMSG_TRTypeGet(BATTLE_WORK *bw,u32 buf_id,int para)
{
	TRAINER_DATA	*tr_data;

	tr_data=BattleWorkTrainerDataGet(bw,para);

	WORDSET_RegisterTrTypeNameBattle(bw->wordset,buf_id,tr_data);
}

//============================================================================================
/**
 *	MESSAGE_PARAM�\���̃f�[�^�����֐��i�g���[�i�[���j
 *
 * @param[in]	sp		�T�[�o�p�����[�^�\����
 * @param[in]	para	�����Ώۃp�����[�^�iSIDE_ATTACK�ASIDE_DEFENCE�Ȃǁj
 */
//============================================================================================
static	void	BattleMSG_TRNameGet(BATTLE_WORK *bw,u32 buf_id,int para)
{
	TRAINER_DATA	*tr_data;

	tr_data=BattleWorkTrainerDataGet(bw,para);

	WORDSET_RegisterTrainerNameBattle(bw->wordset,buf_id,tr_data);
#if 0
	//�g���[�i�[ID�O�́A����
	if((para&0xffff)==0){
		WORDSET_RegisterPlayerName(bw->wordset,buf_id,BattleWorkMyStatusGet(bw,(para&0xffff0000)>>16));
	}
	else{
		WORDSET_RegisterTrainerName(bw->wordset,buf_id,(para&0xffff));
	}
#endif
}

//============================================================================================
/**
 *	MESSAGE_PARAM�\���̃f�[�^�����֐��i�{�b�N�X���j
 *
 * @param[in]	sp		�T�[�o�p�����[�^�\����
 * @param[in]	para	�����Ώۃp�����[�^�iSIDE_ATTACK�ASIDE_DEFENCE�Ȃǁj
 */
//============================================================================================
static	void	BattleMSG_BoxNameGet(BATTLE_WORK *bw,u32 buf_id,int para)
{
	WORDSET_RegisterBoxTrayName(bw->wordset,buf_id,bw->box,para);
}

//============================================================================================
/**
 *	�퓬���b�Z�[�W���b�Z�[�W�W�J�֐�
 *
 * @param[in]	bgl		BG�V�X�e���ݒ�\���̂ւ̃|�C���^
 * @param[in]	win		BMPWIN�V�X�e���ݒ�\���̂ւ̃|�C���^
 * @param[in]	arc_id	���b�Z�[�W�f�[�^�̃A�[�J�C�uID
 * @param[in]	msg_id	���b�Z�[�W�f�[�^�̃A�[�J�C�o���̃��b�Z�[�WINDEXID
 * @param[in]	wait	���b�Z�[�W�\���E�G�C�g
 *
 */
//============================================================================================
static	void	BattleMSG_MsgExpand(BATTLE_WORK *bw,MSGDATA_MANAGER *msg_m,MESSAGE_PARAM *mp)
{
	STRBUF	*src_buf;

	src_buf=MSGMAN_AllocString(msg_m,mp->msg_id);

	WORDSET_ExpandStr(bw->wordset,bw->msg_buf,src_buf);

	STRBUF_Delete(src_buf);
}

//============================================================================================
/**
 *	�퓬���b�Z�[�W�R�[���o�b�N�֐�
 */
//============================================================================================
static	BOOL	BattleMSG_CallBack(MSG_PRINT_HEADER *mph,u16 value)
{
	BOOL	ret;

	ret=FALSE;

	switch(value){
	//SE�I���҂�
	case 1:
		ret=Snd_SePlayCheckAll();
		break;
	//ME�I���҂�
	case 2:
		ret=Snd_MePlayCheckBgmPlay();
		break;
	case 3:
		Snd_MePlay( SEQ_FANFA5 );
		break;
	case 4:
		Snd_SePlay( SEQ_SE_DP_KON );
		break;
	case 5:
		Snd_MePlay( SEQ_FANFA1 );
		break;
	default:
		break;
	}

	return ret;
}

