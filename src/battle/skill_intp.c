
//============================================================================================
/**
 * @file	skill_intp.c
 * @bfief	�Z�V�[�P���X���߃v���O����
 * @author	HisashiSogabe
 * @date	05.05.25
 */
//============================================================================================

#include "common.h"

#include "battle/attr_def.h"
#include "battle/battle_common.h"
#include "battle/battle_server.h"
#include "battle/fight_tool.h"
#include "battle/server.h"
#include "battle/server_tool.h"
#include "battle/scio.h"
#include "battle/tokusyu_def.h"
#include "battle/wazano_def.h"
#include "battle/battle_id.h"

#include "itemtool/item.h"
#include "itemtool/itemequip.h"
#include "itemtool/itemsym.h"

#include "poketool/boxdata.h"
#include "poketool/pokeparty.h"
#include "poketool/tr_tool.h"
#include "poketool/waza_tool.h"
#include "poketool/monsno.h"
#include "poketool/poke_number.h"
#include "poketool/pokeicon.h"

#include "system/arc_tool.h"
#include "system/bmp_menu.h"
#include "system/brightness.h"
#include "system/fontproc.h"
#include "system/fontoam.h"
#include "system/font_arc.h"
#include "system/snd_def.h"
#include "system/snd_perap.h"
#include "system/snd_tool.h"
#include "system/window.h"
#include "system/timezone.h"
#include "system/msg_ds_icon.h"
#include "system/wipe.h"

#include "application/app_tool.h"
#include "application/namein.h"
#include "application/zukanlist/zkn_fight_text.h"
#include "application/zukanlist/zkn_height_gram.h"

#include "msgdata/msg_fightmsg_dp.h"
#include "msgdata/msg_status.h"

#include "tr_ai_def.h"

#include "battle_snd_def.h"

#include "fight_def.h"		///<BattleWork�ւ̈ˑ��x�������\�[�X�Ȃ̂ŁA����
#include "server_def.h"		///<ServerParam�ւ̈ˑ��x�������\�[�X�Ȃ̂ŁA����
#include "client_def.h"		///<ClientParam�ւ̈ˑ��x�������\�[�X�Ȃ̂ŁA����

//MAKE�̈ˑ��֌W�Ɋ܂߂邽�߂�Include�i�{���͕K�v�Ȃ��j
#include "battle/skill/waza_seq.naix"
#include "battle/skill/be_seq.naix"
#include "battle/skill/sub_seq.naix"

#ifdef DEBUG_ONLY_FOR_sogabe
//#define DEBUG_PRINT_BATTLE	///<�퓬�p�f�o�b�O�v�����g��L���ɂ���
#endif

//============================================================================================
//	BMPWIN�f�[�^
//============================================================================================
static const BMPWIN_DAT YesNoBmpWin = {
	GF_BGL_FRAME2_M, 23, 13, 7, 4, MENU_MSG_PAL_NO, MENU_MSG_START
};

//============================================================================================
/**
 *	�\���̐錾
 */
//============================================================================================
//============================================================================================
/**
 *	�v���g�^�C�v�錾
 */
//============================================================================================

//�O�����J�֐�
BOOL	SkillIntp(BATTLE_WORK *bw,SERVER_PARAM *sp);

//���߉��ߊ֐��Q
static	BOOL	WS_ENCOUNT_EFFECT(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_POKEMON_ENCOUNT(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_POKEMON_ENCOUNT_APPEAR(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_POKEMON_APPEAR(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_POKEMON_RETURN(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_POKEMON_DELETE(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_TRAINER_ENCOUNT(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_TRAINER_THROW(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_TRAINER_OUT(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_TRAINER_IN(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_TRAINER_BG_SLIDEIN(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_HP_GAUGE_IN(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_HP_GAUGE_IN_WAIT(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_HP_GAUGE_OUT(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_SERVER_WAIT(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_DAMAGE_CALC(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_DAMAGE_CALC_NO_LOSS(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_ATTACK_MESSAGE(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_MESSAGE(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_MESSAGE_NO_DIR(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_MESSAGE_WORK(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_MESSAGE_PARAM(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_MESSAGE_DIR(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_WAZA_EFFECT(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_WAZA_EFFECT2(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_POKEMON_BLINK(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_HP_CALC(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_HP_GAUGE_CALC(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_KIZETSU_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_KIZETSU_EFFECT(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_WAIT(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_SE_PLAY(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_IF(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_IF_PSP(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_FADE_OUT(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_JUMP(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_JUMP_BE_SEQ(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_JUMP_WAZA_WORK(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_CRITICAL_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_GET_EXP_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_GET_EXP_INIT(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_GET_EXP(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_GET_EXP_LOOP(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_POKEMON_LIST(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_POKEMON_LIST_WAIT(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_POKEMON_RESHUFFLE(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_POKEMON_RESHUFFLE_LOOP(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_POKEMON_GET_INIT(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_POKEMON_GET(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_RENZOKU(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_VALUE(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_ABICNT_CALC(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_PSP_VALUE(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_CONDITION2_OFF(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_VANISH_ON_OFF(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_TOKUSEI_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_RANDOM_GET(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_VALUE_WORK(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_PSP_VALUE_WORK(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_BRANCH(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_GOSUB(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_GOSUB_WORK(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_OUMU_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_KUROIKIRI(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_KEEP_ON(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_KEEP_OFF(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_STATUS_SET(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_TRAINER_MESSAGE(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_OKODUKAI_CALC(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_STATUS_EFFECT(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_STATUS_EFFECT2(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_STATUS_EFFECT_WORK(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_MODOSU_MESSAGE(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_KURIDASU_MESSAGE(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_ENCOUNT_MESSAGE(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_ENCOUNT_KURIDASU_MESSAGE(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_TRAINER_MESSAGE_WORK(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_TEXTURE(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_IF_WORK(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_IF_PSP_WORK(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_KOBAN_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_HIKARINOKABE(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_RIHUREKUTAA(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_SIROIKIRI(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_ICHIGEKI(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_DAMAGE_DIV(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_DAMAGE_DIV_WORK(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_MONOMANE(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_YUBIWOHURU(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_KANASIBARI(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_COUNTER(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_MIRROR_CORT(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_ENCORE(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_TEXTURE2(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_SKETCH(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_NEGOTO(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_JITABATA(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_URAMI(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_IYASINOSUZU(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_DOROBOU(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_GUARD_SUCCESS_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_MIGAWARI(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_HUKITOBASI(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_HENSIN(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_MAKIBISI(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_MAKIBISI_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_HOROBINOUTA(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_CLIENT_NO_GET_AGI(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_CLIENT_SET_MAX_LOOP(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_TENKOU_DAMAGE(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_KOROGARU(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_RENZOKUGIRI(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_MEROMERO(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_SHINPI(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_PRESENT(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_MAGNITUDE(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_RESHUFFLE_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_KOUSOKUSPIN(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_WEATHER_KAIFUKU(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_MEZAMERU_POWER(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_JIKOANJI(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_MIRAIYOCHI(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_HITCHECK(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_TELEPORT(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_HUKURODATAKI(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_KONOYUBITOMARE(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_TEDASUKE(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_TRICK(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_NEGAIGOTO(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_NEKONOTE(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_MAGIC_CORT(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_MAGIC_CORT_A_D(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_REVENGE(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_KAWARAWARI(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_AKUBI(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_HATAKIOTOSU(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_HUNKA(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_HUUIN(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_ONNEN(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_YOKODORI(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_KETAGURI(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_WEATHER_BALL(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_OIUCHI_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_TYPE_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_OTF_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_OTF_SET(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_GIROBALL(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_METALMIRROR(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_TAMEUCHI(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_KIRIHUDA(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_SIBORITORU(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_SAKIDORI(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_MANEKKO(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_OSIOKI(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_HUIUCHI(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_SIDE_CONDITION_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_FEINT(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_SURIKOMI(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_TOTTEOKI(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_DOKUBISI(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_DOKUBISI_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_KATAYABURI_TOKUSEI_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_SIDE_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_MONOHIROI(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_TRICKROOM(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_WAZA_OUT_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_SOUBI_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_SOUBI_EQP_GET(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_SOUBI_ATK_GET(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_HOGOSYOKU(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_SHIZENNOCHIKARA(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_HIMITSUNOCHIKARA(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_SHIZENNOMEGUMI(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_TSUIBAMU(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_NAGETSUKERU(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_YES_NO_SELECT(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_YES_NO_SELECT_WAIT(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_POKEMON_LIST_CALL(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_POKEMON_LIST_CALL_WAIT(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_WIN_LOSE_SET(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_STEALTHROCK_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_ADD_STATUS_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_OSYABERI(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_WAZA_PARAM_GET(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_MOSAIC(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_FORM_CHG(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_BG_CHG(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_STATUS_RECOVER(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_ESCAPE_ACT_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_BALL_GAUGE_ENCOUNT_SET(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_BALL_GAUGE_ENCOUNT_OUT(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_BALL_GAUGE_SET(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_BALL_GAUGE_OUT(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_BALL_GAUGE_RESOURCE_LOAD(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_BALL_GAUGE_RESOURCE_DELETE(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_INC_RECORD(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_CHR_POP(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_WAZA_HIT_TOKUSEI_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_SS_TO_OAM_CALL(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_OAM_TO_SS_CALL(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_ZENMETSU_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_TUBOWOTUKU(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_KILL_ITEM(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_RECYCLE(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_WAZA_HIT_SOUBI_ITEM_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_WIN_LOSE_MESSAGE(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_ESCAPE_MESSAGE(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_GIVEUP_MESSAGE(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_HP1_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_SIZENKAIHUKU_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_MIGAWARI_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_NOOTENKI_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_DIR_CLIENT_GET(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_WAZA_HIT_SOUBI_ITEM_CHECK_TONBOGAERI(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_MIGAWARI_CHR_SET(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_WAZAKOUKA_SE(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_BGM_PLAY(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	BOOL	WS_SAFARI_END_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp);

static	BOOL	WS_SEQ_END(BATTLE_WORK *bw,SERVER_PARAM *sp);

//�O������J�֐�
static	int		SkillSeqDataRead(SERVER_PARAM *sp);
static	void	SkillSeqInc(SERVER_PARAM *sp,int cnt);
static	void	SkillSequenceJump(SERVER_PARAM *sp,int arc_kind,int adrs);
static	void	SkillSequenceGosub(SERVER_PARAM *sp,int arc_kind,int adrs);
static	void	*WS_SrcPointerGet(BATTLE_WORK *bw,SERVER_PARAM *sp,int para);
static	int		SideClientNoGet(BATTLE_WORK *bw,SERVER_PARAM *sp,int side);
static	void	MessageParamDataMake(SERVER_PARAM *sp,MESSAGE_PARAM_DATA *mpd);
static	void	MessageParamMake(BATTLE_WORK *bw,SERVER_PARAM *sp,MESSAGE_PARAM_DATA *mpd,MESSAGE_PARAM *mp);
static	int		MessageParamNicknameGet(BATTLE_WORK *bw,SERVER_PARAM *sp,int para);
static	int		MessageParamWazaGet(SERVER_PARAM *sp,int para);
static	int		MessageParamItemGet(SERVER_PARAM *sp,int para);
static	int		MessageParamNumGet(SERVER_PARAM *sp,int para);
static	int		MessageParamTypeGet(SERVER_PARAM *sp,int para);
static	int		MessageParamTokuseiGet(BATTLE_WORK *bw,SERVER_PARAM *sp,int para);
static	int		MessageParamStatusGet(SERVER_PARAM *sp,int para);
static	int		MessageParamConditionGet(SERVER_PARAM *sp,int para);
static	int		MessageParamPokenameGet(BATTLE_WORK *bw,SERVER_PARAM *sp,int para);
static	int		MessageParamPolockGet(SERVER_PARAM *sp,int para);
static	int		MessageParamTasteGet(SERVER_PARAM *sp,int para);
static	int		MessageParamTRTypeGet(BATTLE_WORK *bw,SERVER_PARAM *sp,int para);
static	int		MessageParamTRNameGet(BATTLE_WORK *bw,SERVER_PARAM *sp,int para);
static	u32		OkodukaiCalcAct(BATTLE_WORK *bw,SERVER_PARAM *sp,int num);
static	void	PokeExpCalc(POKEPARTY *ppt,int pos,int mons_no);
static	int		PokemonGetCalc(BATTLE_WORK *bw,SERVER_PARAM *sp);
static	void	BenchLevelUpPokeIconActorSet(BATTLE_WORK *bw,TCB_SKILL_INTP_WORK *tsiw,POKEMON_PARAM *pp);
static	void	BenchLevelUpPokeIconActorDelete(BATTLE_WORK *bw,TCB_SKILL_INTP_WORK *tsiw);
static	void	FontLenGet(const STRBUF *str, FONT_TYPE font_type, int *ret_dot_len, int *ret_char_len);
static	void	HinshiFriendCalc(BATTLE_WORK *bw,SERVER_PARAM *sp,int kizetsu_client);
static	void	TokusyuNoSet(SERVER_PARAM *sp,u8 client_no,u8 speabino);
static	void	TokusyuNoClear(SERVER_PARAM *sp,u8 client_no);
static	void	SoubiItemSet(SERVER_PARAM *sp,u8 client_no,u16 item_no);
static	void	SoubiItemClear(SERVER_PARAM *sp,u8 client_no);

//TCB�֐�
static	void	TCB_GetExp(TCB_PTR tcb,void *work);
static	void	TCB_GetPokemon(TCB_PTR tcb,void *work);

//============================================================================================
/**
 *	���߃e�[�u��
 *	waza_seq_def.h�̃C���f�b�N�X�ƈ�΂ɂȂ�悤�ɂ���
 */
//============================================================================================

static	const	siFunc	SkillIntpTable[]={
	WS_ENCOUNT_EFFECT,
	WS_POKEMON_ENCOUNT,
	WS_POKEMON_ENCOUNT_APPEAR,
	WS_POKEMON_APPEAR,
	WS_POKEMON_RETURN,
	WS_POKEMON_DELETE,
	WS_TRAINER_ENCOUNT,
	WS_TRAINER_THROW,
	WS_TRAINER_OUT,
	WS_TRAINER_IN,
	WS_TRAINER_BG_SLIDEIN,
	WS_HP_GAUGE_IN,
	WS_HP_GAUGE_IN_WAIT,
	WS_HP_GAUGE_OUT,
	WS_SERVER_WAIT,
	WS_DAMAGE_CALC,
	WS_DAMAGE_CALC_NO_LOSS,
	WS_ATTACK_MESSAGE,
	WS_MESSAGE,
	WS_MESSAGE_NO_DIR,
	WS_MESSAGE_WORK,
	WS_MESSAGE_PARAM,
	WS_MESSAGE_DIR,
	WS_WAZA_EFFECT,
	WS_WAZA_EFFECT2,
	WS_POKEMON_BLINK,
	WS_HP_CALC,
	WS_HP_GAUGE_CALC,
	WS_KIZETSU_CHECK,
	WS_KIZETSU_EFFECT,
	WS_WAIT,
	WS_SE_PLAY,
	WS_IF,
	WS_IF_PSP,
	WS_FADE_OUT,
	WS_JUMP,
	WS_JUMP_BE_SEQ,
	WS_JUMP_WAZA_WORK,
	WS_CRITICAL_CHECK,
	WS_GET_EXP_CHECK,
	WS_GET_EXP_INIT,
	WS_GET_EXP,
	WS_GET_EXP_LOOP,
	WS_POKEMON_LIST,
	WS_POKEMON_LIST_WAIT,
	WS_POKEMON_RESHUFFLE,
	WS_POKEMON_RESHUFFLE_LOOP,
	WS_POKEMON_GET_INIT,
	WS_POKEMON_GET,
	WS_RENZOKU,
	WS_VALUE,
	WS_ABICNT_CALC,
	WS_PSP_VALUE,
	WS_CONDITION2_OFF,
	WS_VANISH_ON_OFF,
	WS_TOKUSEI_CHECK,
	WS_RANDOM_GET,
	WS_VALUE_WORK,
	WS_PSP_VALUE_WORK,
	WS_BRANCH,
	WS_GOSUB,
	WS_GOSUB_WORK,
	WS_OUMU_CHECK,
	WS_KUROIKIRI,
	WS_KEEP_ON,
	WS_KEEP_OFF,
	WS_STATUS_SET,
	WS_TRAINER_MESSAGE,
	WS_OKODUKAI_CALC,
	WS_STATUS_EFFECT,
	WS_STATUS_EFFECT2,
	WS_STATUS_EFFECT_WORK,
	WS_MODOSU_MESSAGE,
	WS_KURIDASU_MESSAGE,
	WS_ENCOUNT_MESSAGE,
	WS_ENCOUNT_KURIDASU_MESSAGE,
	WS_TRAINER_MESSAGE_WORK,
	WS_TEXTURE,
	WS_IF_WORK,
	WS_IF_PSP_WORK,
	WS_KOBAN_CHECK,
	WS_HIKARINOKABE,
	WS_RIHUREKUTAA,
	WS_SIROIKIRI,
	WS_ICHIGEKI,
	WS_DAMAGE_DIV,
	WS_DAMAGE_DIV_WORK,
	WS_MONOMANE,
	WS_YUBIWOHURU,
	WS_KANASIBARI,
	WS_COUNTER,
	WS_MIRROR_CORT,
	WS_ENCORE,
	WS_TEXTURE2,
	WS_SKETCH,
	WS_NEGOTO,
	WS_JITABATA,
	WS_URAMI,
	WS_IYASINOSUZU,
	WS_DOROBOU,
	WS_GUARD_SUCCESS_CHECK,
	WS_MIGAWARI,
	WS_HUKITOBASI,
	WS_HENSIN,
	WS_MAKIBISI,
	WS_MAKIBISI_CHECK,
	WS_HOROBINOUTA,
	WS_CLIENT_NO_GET_AGI,
	WS_CLIENT_SET_MAX_LOOP,
	WS_TENKOU_DAMAGE,
	WS_KOROGARU,
	WS_RENZOKUGIRI,
	WS_MEROMERO,
	WS_SHINPI,
	WS_PRESENT,
	WS_MAGNITUDE,
	WS_RESHUFFLE_CHECK,
	WS_KOUSOKUSPIN,
	WS_WEATHER_KAIFUKU,
	WS_MEZAMERU_POWER,
	WS_JIKOANJI,
	WS_MIRAIYOCHI,
	WS_HITCHECK,
	WS_TELEPORT,
	WS_HUKURODATAKI,
	WS_KONOYUBITOMARE,
	WS_TEDASUKE,
	WS_TRICK,
	WS_NEGAIGOTO,
	WS_NEKONOTE,
	WS_MAGIC_CORT,
	WS_MAGIC_CORT_A_D,
	WS_REVENGE,
	WS_KAWARAWARI,
	WS_AKUBI,
	WS_HATAKIOTOSU,
	WS_HUNKA,
	WS_HUUIN,
	WS_ONNEN,
	WS_YOKODORI,
	WS_KETAGURI,
	WS_WEATHER_BALL,
	WS_OIUCHI_CHECK,
	WS_TYPE_CHECK,
	WS_OTF_CHECK,
	WS_OTF_SET,
	WS_GIROBALL,
	WS_METALMIRROR,
	WS_TAMEUCHI,
	WS_KIRIHUDA,
	WS_SIBORITORU,
	WS_SAKIDORI,
	WS_MANEKKO,
	WS_OSIOKI,
	WS_HUIUCHI,
	WS_SIDE_CONDITION_CHECK,
	WS_FEINT,
	WS_SURIKOMI,
	WS_TOTTEOKI,
	WS_DOKUBISI,
	WS_DOKUBISI_CHECK,
	WS_KATAYABURI_TOKUSEI_CHECK,
	WS_SIDE_CHECK,
	WS_MONOHIROI,
	WS_TRICKROOM,
	WS_WAZA_OUT_CHECK,
	WS_SOUBI_CHECK,
	WS_SOUBI_EQP_GET,
	WS_SOUBI_ATK_GET,
	WS_HOGOSYOKU,
	WS_SHIZENNOCHIKARA,
	WS_HIMITSUNOCHIKARA,
	WS_SHIZENNOMEGUMI,
	WS_TSUIBAMU,
	WS_NAGETSUKERU,
	WS_YES_NO_SELECT,
	WS_YES_NO_SELECT_WAIT,
	WS_POKEMON_LIST_CALL,
	WS_POKEMON_LIST_CALL_WAIT,
	WS_WIN_LOSE_SET,
	WS_STEALTHROCK_CHECK,
	WS_ADD_STATUS_CHECK,
	WS_OSYABERI,
	WS_WAZA_PARAM_GET,
	WS_MOSAIC,
	WS_FORM_CHG,
	WS_BG_CHG,
	WS_STATUS_RECOVER,
	WS_ESCAPE_ACT_CHECK,
	WS_BALL_GAUGE_ENCOUNT_SET,
	WS_BALL_GAUGE_ENCOUNT_OUT,
	WS_BALL_GAUGE_SET,
	WS_BALL_GAUGE_OUT,
	WS_BALL_GAUGE_RESOURCE_LOAD,
	WS_BALL_GAUGE_RESOURCE_DELETE,
	WS_INC_RECORD,
	WS_CHR_POP,
	WS_WAZA_HIT_TOKUSEI_CHECK,
	WS_SS_TO_OAM_CALL,
	WS_OAM_TO_SS_CALL,
	WS_ZENMETSU_CHECK,
	WS_TUBOWOTUKU,
	WS_KILL_ITEM,
	WS_RECYCLE,
	WS_WAZA_HIT_SOUBI_ITEM_CHECK,
	WS_WIN_LOSE_MESSAGE,
	WS_ESCAPE_MESSAGE,
	WS_GIVEUP_MESSAGE,
	WS_HP1_CHECK,
	WS_SIZENKAIHUKU_CHECK,
	WS_MIGAWARI_CHECK,
	WS_NOOTENKI_CHECK,
	WS_DIR_CLIENT_GET,
	WS_WAZA_HIT_SOUBI_ITEM_CHECK_TONBOGAERI,
	WS_MIGAWARI_CHR_SET,
	WS_WAZAKOUKA_SE,
	WS_BGM_PLAY,
	WS_SAFARI_END_CHECK,

	WS_SEQ_END
};

//============================================================================================
/**
 *	���߉��ߊ֐��փW�����v
 *
 * @param[in]	bw	�퓬���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
BOOL	SkillIntp(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	return SkillIntpTable[sp->SkillSeqWork[sp->skill_seq_no]](bw,sp);
}

//============================================================================================
//	���ߊ֐��Q
//============================================================================================
//============================================================================================
/**
 *	�G���J�E���g�G�t�F�N�g���Z�b�g
 *
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_ENCOUNT_EFFECT(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("ENCOUNT_EFFECT\n");
#endif

	SCIO_EncountEffectSet(bw,CLIENT_NO_MINE);

	return	FALSE;
}

//============================================================================================
/**
 *	�G���J�E���g�p�|�P�������Z�b�g
 *
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 *
 * �f�[�^�����F
 * 0:�G���J�E���g�|�P�������Z�b�g���鑤�̎w��(SIDE_ALL:���ׂ� SIDE_MINE:������ SIDE_ENEMY�F���葤)
 */
//============================================================================================
static	BOOL	WS_POKEMON_ENCOUNT(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	client_no;
	int	dir;
	int	client_set_max=BattleWorkClientSetMaxGet(bw);

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//�Z�b�g���鑤�f�[�^�����[�h
	dir=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("POKEMON_ENCOUNT dir:%d\n",dir);
#endif

	switch(dir){
	default:
	case SIDE_ALL:
		for(client_no=0;client_no<client_set_max;client_no++){
			SCIO_PokemonEncountSet(bw,client_no);
			FT_ZukanFlagSetSee(bw,client_no);
		}
		break;
	case SIDE_MINE:
		OS_Printf("�����ɂ͂��Ȃ��͂�\n");
		break;
	case SIDE_ENEMY:
		{
			CLIENT_PARAM	*cp;
			for(client_no=0;client_no<client_set_max;client_no++){
				cp=BattleWorkClientParamGet(bw,client_no);
				if(cp->client_type&CLIENT_ENEMY_FLAG){
					SCIO_PokemonEncountSet(bw,client_no);
					FT_ZukanFlagSetSee(bw,client_no);
				}
			}
		}
		break;
	}

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_POKEMON_ENCOUNT_APPEAR(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	client_no;
	int	dir;
	int	client_set_max=BattleWorkClientSetMaxGet(bw);
	CLIENT_PARAM	*cp;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//�Z�b�g���鑤�f�[�^�����[�h
	dir=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("POKEMON_ENCOUNT_APPEAR dir:%d\n",dir);
#endif

	switch(dir){
	default:
	case SIDE_ALL:
		for(client_no=0;client_no<client_set_max;client_no++){
			SCIO_PokemonEncountAppearSet(bw,client_no);
			FT_ZukanFlagSetSee(bw,client_no);
		}
		break;
	case SIDE_MINE:
		for(client_no=0;client_no<client_set_max;client_no++){
			cp=BattleWorkClientParamGet(bw,client_no);
			if((cp->client_type&CLIENT_ENEMY_FLAG)==0){
				SCIO_PokemonEncountAppearSet(bw,client_no);
				FT_ZukanFlagSetSee(bw,client_no);
			}
		}
		ST_ServerGetExpRightFlagSet(bw,sp,CLIENT_NO_ENEMY);
		ST_ServerGetExpRightFlagSet(bw,sp,CLIENT_NO_ENEMY2);
		break;
	case SIDE_ENEMY:
		for(client_no=0;client_no<client_set_max;client_no++){
			cp=BattleWorkClientParamGet(bw,client_no);
			if(cp->client_type&CLIENT_ENEMY_FLAG){
				ST_ServerGetExpRightFlagClear(sp,client_no);
				ST_ServerGetExpRightFlagSet(bw,sp,client_no);
				SCIO_PokemonEncountAppearSet(bw,client_no);
				FT_ZukanFlagSetSee(bw,client_no);
			}
		}
		break;
	case SIDE_ATTACK:
		cp=BattleWorkClientParamGet(bw,sp->attack_client);
		if((cp->client_type&CLIENT_ENEMY_FLAG)==0){
			ST_ServerGetExpRightFlagSet(bw,sp,CLIENT_NO_ENEMY);
			ST_ServerGetExpRightFlagSet(bw,sp,CLIENT_NO_ENEMY2);
		}
		else{
			ST_ServerGetExpRightFlagClear(sp,sp->attack_client);
			ST_ServerGetExpRightFlagSet(bw,sp,sp->attack_client);
		}
		FT_ZukanFlagSetSee(bw,sp->attack_client);
		SCIO_PokemonEncountAppearSet(bw,sp->attack_client);
		break;
	case SIDE_DEFENCE:
		cp=BattleWorkClientParamGet(bw,sp->defence_client);
		if((cp->client_type&CLIENT_ENEMY_FLAG)==0){
			ST_ServerGetExpRightFlagSet(bw,sp,CLIENT_NO_ENEMY);
			ST_ServerGetExpRightFlagSet(bw,sp,CLIENT_NO_ENEMY2);
		}
		else{
			ST_ServerGetExpRightFlagClear(sp,sp->defence_client);
			ST_ServerGetExpRightFlagSet(bw,sp,sp->defence_client);
		}
		FT_ZukanFlagSetSee(bw,sp->defence_client);
		SCIO_PokemonEncountAppearSet(bw,sp->defence_client);
		break;
	case SIDE_RESHUFFLE:
		cp=BattleWorkClientParamGet(bw,sp->reshuffle_client);
		if((cp->client_type&CLIENT_ENEMY_FLAG)==0){
			ST_ServerGetExpRightFlagSet(bw,sp,CLIENT_NO_ENEMY);
			ST_ServerGetExpRightFlagSet(bw,sp,CLIENT_NO_ENEMY2);
		}
		else{
			ST_ServerGetExpRightFlagClear(sp,sp->reshuffle_client);
			ST_ServerGetExpRightFlagSet(bw,sp,sp->reshuffle_client);
		}
		FT_ZukanFlagSetSee(bw,sp->reshuffle_client);
		SCIO_PokemonEncountAppearSet(bw,sp->reshuffle_client);
		break;
	}

	return	FALSE;
}
//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_POKEMON_APPEAR(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	client_no;
	int	dir;
	int	client_set_max=BattleWorkClientSetMaxGet(bw);
	CLIENT_PARAM	*cp;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//�Z�b�g���鑤�f�[�^�����[�h
	dir=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("POKEMON_APPEAR dir:%d\n",dir);
#endif

	switch(dir){
	default:
	case SIDE_ALL:
		for(client_no=0;client_no<client_set_max;client_no++){
			SCIO_PokemonAppearSet(bw,client_no,NULL,POKEMON_APPEAR_KURIDASI);
			FT_ZukanFlagSetSee(bw,client_no);
		}
		break;
	case SIDE_MINE:
		for(client_no=0;client_no<client_set_max;client_no++){
			cp=BattleWorkClientParamGet(bw,client_no);
			if((cp->client_type&CLIENT_ENEMY_FLAG)==0){
				SCIO_PokemonAppearSet(bw,client_no,NULL,POKEMON_APPEAR_KURIDASI);
				FT_ZukanFlagSetSee(bw,client_no);
			}
		}
		ST_ServerGetExpRightFlagSet(bw,sp,CLIENT_NO_ENEMY);
		ST_ServerGetExpRightFlagSet(bw,sp,CLIENT_NO_ENEMY2);
		break;
	case SIDE_ENEMY:
		for(client_no=0;client_no<client_set_max;client_no++){
			cp=BattleWorkClientParamGet(bw,client_no);
			if(cp->client_type&CLIENT_ENEMY_FLAG){
				ST_ServerGetExpRightFlagClear(sp,client_no);
				ST_ServerGetExpRightFlagSet(bw,sp,client_no);
				SCIO_PokemonAppearSet(bw,client_no,NULL,POKEMON_APPEAR_KURIDASI);
				FT_ZukanFlagSetSee(bw,client_no);
			}
		}
		break;
	case SIDE_ATTACK:
		cp=BattleWorkClientParamGet(bw,sp->attack_client);
		if((cp->client_type&CLIENT_ENEMY_FLAG)==0){
			ST_ServerGetExpRightFlagSet(bw,sp,CLIENT_NO_ENEMY);
			ST_ServerGetExpRightFlagSet(bw,sp,CLIENT_NO_ENEMY2);
		}
		else{
			ST_ServerGetExpRightFlagClear(sp,sp->attack_client);
			ST_ServerGetExpRightFlagSet(bw,sp,sp->attack_client);
		}
		FT_ZukanFlagSetSee(bw,sp->attack_client);
		SCIO_PokemonAppearSet(bw,sp->attack_client,NULL,POKEMON_APPEAR_KURIDASI);
		break;
	case SIDE_DEFENCE:
		cp=BattleWorkClientParamGet(bw,sp->defence_client);
		if((cp->client_type&CLIENT_ENEMY_FLAG)==0){
			ST_ServerGetExpRightFlagSet(bw,sp,CLIENT_NO_ENEMY);
			ST_ServerGetExpRightFlagSet(bw,sp,CLIENT_NO_ENEMY2);
		}
		else{
			ST_ServerGetExpRightFlagClear(sp,sp->defence_client);
			ST_ServerGetExpRightFlagSet(bw,sp,sp->defence_client);
		}
		FT_ZukanFlagSetSee(bw,sp->defence_client);
		SCIO_PokemonAppearSet(bw,sp->defence_client,NULL,POKEMON_APPEAR_KURIDASI);
		break;
	case SIDE_RESHUFFLE:
		cp=BattleWorkClientParamGet(bw,sp->reshuffle_client);
		if((cp->client_type&CLIENT_ENEMY_FLAG)==0){
			ST_ServerGetExpRightFlagSet(bw,sp,CLIENT_NO_ENEMY);
			ST_ServerGetExpRightFlagSet(bw,sp,CLIENT_NO_ENEMY2);
		}
		else{
			ST_ServerGetExpRightFlagClear(sp,sp->reshuffle_client);
			ST_ServerGetExpRightFlagSet(bw,sp,sp->reshuffle_client);
		}
		FT_ZukanFlagSetSee(bw,sp->reshuffle_client);
		SCIO_PokemonAppearSet(bw,sp->reshuffle_client,NULL,POKEMON_APPEAR_KURIDASI);
		break;
	}

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_POKEMON_RETURN(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	client_no;
	int	side;
	int	client_set_max=BattleWorkClientSetMaxGet(bw);
	CLIENT_PARAM	*cp;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//�Z�b�g���鑤�f�[�^�����[�h
	side=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("POKEMON_RETURN side:%d\n",side);
#endif

	switch(side){
	case SIDE_ALL:
		for(client_no=0;client_no<client_set_max;client_no++){
			SCIO_PokemonReturnSet(bw,sp,client_no);
		}
		break;
	case SIDE_MINE:
		for(client_no=0;client_no<client_set_max;client_no++){
			cp=BattleWorkClientParamGet(bw,client_no);
			if((cp->client_type&CLIENT_ENEMY_FLAG)==0){
				SCIO_PokemonReturnSet(bw,sp,client_no);
			}
		}
		break;
	case SIDE_ENEMY:
		for(client_no=0;client_no<client_set_max;client_no++){
			cp=BattleWorkClientParamGet(bw,client_no);
			if((cp->client_type&CLIENT_ENEMY_FLAG)&&
			  ((sp->no_reshuffle_client&No2Bit(client_no))==0)){
				SCIO_PokemonReturnSet(bw,sp,client_no);
			}
		}
		break;
	default:
		client_no=SideClientNoGet(bw,sp,side);
		SCIO_PokemonReturnSet(bw,sp,client_no);
		break;
	}

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_POKEMON_DELETE(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	client_no;
	int	side;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//side�����[�h
	side=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("POKEMON_DELETE side:%d\n",side);
#endif

	client_no=SideClientNoGet(bw,sp,side);

	SCIO_PokemonDeleteSet(bw,client_no);

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_TRAINER_ENCOUNT(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	client_no;
	int	dir;
	int	client_set_max=BattleWorkClientSetMaxGet(bw);
	CLIENT_PARAM	*cp;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//�Z�b�g���鑤�f�[�^�����[�h
	dir=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("TRAINER_ENCOUNT dir:%d\n",dir);
#endif

	switch(dir){
	default:
	case SIDE_ALL:
		if(BattleWorkFightTypeGet(bw)&FIGHT_TYPE_TAG){
			for(client_no=0;client_no<client_set_max;client_no++){
				cp=BattleWorkClientParamGet(bw,client_no);
				if(cp->client_type!=CLIENT_TYPE_C){
					SCIO_TrainerEncountSet(bw,client_no);
				}
			}
		}
		else{
			for(client_no=0;client_no<client_set_max;client_no++){
				if(((BattleWorkFightTypeGet(bw)&FIGHT_TYPE_MULTI)==0)&&
				    (BattleWorkFightTypeGet(bw)&FIGHT_TYPE_2vs2)&&
					(client_no>1)){
					break;
				}
				SCIO_TrainerEncountSet(bw,client_no);
			}
		}
		break;
	case SIDE_MINE:
		for(client_no=0;client_no<client_set_max;client_no++){
			cp=BattleWorkClientParamGet(bw,client_no);
			if((cp->client_type&CLIENT_ENEMY_FLAG)==0){
				SCIO_TrainerEncountSet(bw,client_no);
				if(((BattleWorkFightTypeGet(bw)&FIGHT_TYPE_MULTI)==0)&&
				    (BattleWorkFightTypeGet(bw)&FIGHT_TYPE_2vs2)){
					break;
				}
			}
		}
		break;
	case SIDE_ENEMY:
		for(client_no=0;client_no<client_set_max;client_no++){
			cp=BattleWorkClientParamGet(bw,client_no);
			if(cp->client_type&CLIENT_ENEMY_FLAG){
				SCIO_TrainerEncountSet(bw,client_no);
				if(((BattleWorkFightTypeGet(bw)&FIGHT_TYPE_MULTI)==0)&&
				   ((BattleWorkFightTypeGet(bw)&FIGHT_TYPE_TAG)==0)&&
				    (BattleWorkFightTypeGet(bw)&FIGHT_TYPE_2vs2)){
					break;
				}
			}
		}
		break;
	}

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_TRAINER_THROW(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	client_no;
	int	side;
	int	type;
	int	client_set_max=BattleWorkClientSetMaxGet(bw);
	CLIENT_PARAM	*cp;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//�Z�b�g���鑤�f�[�^�����[�h
	side=SkillSeqDataRead(sp);

	//�^�C�v�����[�h
	type=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("TRAINER_THROW side:%d type%d\n",side,type);
#endif

	switch(side){
	default:
	case SIDE_ALL:
		for(client_no=0;client_no<client_set_max;client_no++){
			if(((BattleWorkFightTypeGet(bw)&FIGHT_TYPE_MULTI)==0)&&
			    (BattleWorkFightTypeGet(bw)&FIGHT_TYPE_2vs2)&&
				(client_no>1)){
				break;
			}
			SCIO_TrainerThrowSet(bw,client_no,type);
		}
		break;
	case SIDE_MINE:
		for(client_no=0;client_no<client_set_max;client_no++){
			cp=BattleWorkClientParamGet(bw,client_no);
			if((cp->client_type&CLIENT_ENEMY_FLAG)==0){
				SCIO_TrainerThrowSet(bw,client_no,type);
				if(((BattleWorkFightTypeGet(bw)&FIGHT_TYPE_MULTI)==0)&&
				    (BattleWorkFightTypeGet(bw)&FIGHT_TYPE_2vs2)){
					break;
				}
			}
		}
		break;
	case SIDE_ENEMY:
		for(client_no=0;client_no<client_set_max;client_no++){
			cp=BattleWorkClientParamGet(bw,client_no);
			if(cp->client_type&CLIENT_ENEMY_FLAG){
				SCIO_TrainerThrowSet(bw,client_no,type);
				if(((BattleWorkFightTypeGet(bw)&FIGHT_TYPE_MULTI)==0)&&
				   ((BattleWorkFightTypeGet(bw)&FIGHT_TYPE_TAG)==0)&&
				    (BattleWorkFightTypeGet(bw)&FIGHT_TYPE_2vs2)){
					break;
				}
			}
		}
		break;
	}
	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_TRAINER_OUT(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	client_no;
	int	dir;
	int	client_set_max=BattleWorkClientSetMaxGet(bw);
	CLIENT_PARAM	*cp;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//�Z�b�g���鑤�f�[�^�����[�h
	dir=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("TRAINER_OUT dir:%d\n",dir);
#endif

	switch(dir){
	default:
	case SIDE_ALL:
		for(client_no=0;client_no<client_set_max;client_no++){
			if(((BattleWorkFightTypeGet(bw)&FIGHT_TYPE_MULTI)==0)&&
			    (BattleWorkFightTypeGet(bw)&FIGHT_TYPE_2vs2)&&
				(client_no>1)){
				break;
			}
			SCIO_TrainerOutSet(bw,client_no);
		}
		break;
	case SIDE_MINE:
		for(client_no=0;client_no<client_set_max;client_no++){
			cp=BattleWorkClientParamGet(bw,client_no);
			if((cp->client_type&CLIENT_ENEMY_FLAG)==0){
				SCIO_TrainerOutSet(bw,client_no);
				if(((BattleWorkFightTypeGet(bw)&FIGHT_TYPE_MULTI)==0)&&
				    (BattleWorkFightTypeGet(bw)&FIGHT_TYPE_2vs2)){
					break;
				}
			}
		}
		break;
	case SIDE_ENEMY:
		for(client_no=0;client_no<client_set_max;client_no++){
			cp=BattleWorkClientParamGet(bw,client_no);
			if(cp->client_type&CLIENT_ENEMY_FLAG){
				SCIO_TrainerOutSet(bw,client_no);
				if(((BattleWorkFightTypeGet(bw)&FIGHT_TYPE_MULTI)==0)&&
				   ((BattleWorkFightTypeGet(bw)&FIGHT_TYPE_TAG)==0)&&
				    (BattleWorkFightTypeGet(bw)&FIGHT_TYPE_2vs2)){
					break;
				}
			}
		}
		break;
	case SIDE_MINE_1:
		for(client_no=0;client_no<client_set_max;client_no++){
			cp=BattleWorkClientParamGet(bw,client_no);
			if((cp->client_type==CLIENT_TYPE_AA)||(cp->client_type==CLIENT_TYPE_A)){
				SCIO_TrainerOutSet(bw,client_no);
				break;
			}
		}
		break;
	case SIDE_ENEMY_1:
		for(client_no=0;client_no<client_set_max;client_no++){
			cp=BattleWorkClientParamGet(bw,client_no);
			if((cp->client_type==CLIENT_TYPE_BB)||(cp->client_type==CLIENT_TYPE_B)){
				SCIO_TrainerOutSet(bw,client_no);
				break;
			}
		}
		break;
	case SIDE_MINE_2:
		for(client_no=0;client_no<client_set_max;client_no++){
			cp=BattleWorkClientParamGet(bw,client_no);
			if(cp->client_type==CLIENT_TYPE_C){
				SCIO_TrainerOutSet(bw,client_no);
				break;
			}
		}
		break;
	case SIDE_ENEMY_2:
		for(client_no=0;client_no<client_set_max;client_no++){
			cp=BattleWorkClientParamGet(bw,client_no);
			if(cp->client_type==CLIENT_TYPE_D){
				SCIO_TrainerOutSet(bw,client_no);
				break;
			}
		}
		break;
	}

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_TRAINER_IN(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	client_no;
	int	dir;
	int	pos;
	int	client_set_max=BattleWorkClientSetMaxGet(bw);
	CLIENT_PARAM	*cp;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//�Z�b�g���鑤�f�[�^�����[�h
	dir=SkillSeqDataRead(sp);

	//�o��ʒu�f�[�^�����[�h
	pos=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("TRAINER_IN dir:%d pos:%d\n",dir,pos);
#endif

	switch(dir){
	default:
	case SIDE_ALL:
		for(client_no=0;client_no<client_set_max;client_no++){
			if((BattleWorkFightTypeGet(bw)&FIGHT_TYPE_2vs2)&&(client_no>1)){
				break;
			}
			SCIO_TrainerInSet(bw,client_no,pos);
		}
		break;
	case SIDE_MINE:
		for(client_no=0;client_no<client_set_max;client_no++){
			cp=BattleWorkClientParamGet(bw,client_no);
			if((cp->client_type&CLIENT_ENEMY_FLAG)==0){
				SCIO_TrainerInSet(bw,client_no,pos);
				if(BattleWorkFightTypeGet(bw)&FIGHT_TYPE_2vs2){
					break;
				}
			}
		}
		break;
	case SIDE_ENEMY:
		for(client_no=0;client_no<client_set_max;client_no++){
			cp=BattleWorkClientParamGet(bw,client_no);
			if(cp->client_type&CLIENT_ENEMY_FLAG){
				SCIO_TrainerInSet(bw,client_no,pos);
				if(BattleWorkFightTypeGet(bw)&FIGHT_TYPE_2vs2){
					break;
				}
			}
		}
		break;
	case SIDE_MINE_1:
		for(client_no=0;client_no<client_set_max;client_no++){
			cp=BattleWorkClientParamGet(bw,client_no);
			if((cp->client_type==CLIENT_TYPE_AA)||(cp->client_type==CLIENT_TYPE_A)){
				SCIO_TrainerInSet(bw,client_no,pos);
				break;
			}
		}
		break;
	case SIDE_ENEMY_1:
		for(client_no=0;client_no<client_set_max;client_no++){
			cp=BattleWorkClientParamGet(bw,client_no);
			if((cp->client_type==CLIENT_TYPE_BB)||(cp->client_type==CLIENT_TYPE_B)){
				SCIO_TrainerInSet(bw,client_no,pos);
				break;
			}
		}
		break;
	case SIDE_MINE_2:
		for(client_no=0;client_no<client_set_max;client_no++){
			cp=BattleWorkClientParamGet(bw,client_no);
			if(cp->client_type==CLIENT_TYPE_C){
				SCIO_TrainerInSet(bw,client_no,pos);
				break;
			}
		}
		break;
	case SIDE_ENEMY_2:
		for(client_no=0;client_no<client_set_max;client_no++){
			cp=BattleWorkClientParamGet(bw,client_no);
			if(cp->client_type==CLIENT_TYPE_D){
				SCIO_TrainerInSet(bw,client_no,pos);
				break;
			}
		}
		break;
	}

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_TRAINER_BG_SLIDEIN(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	client_no;
	int	client_set_max=BattleWorkClientSetMaxGet(bw);

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("TRAINER_BG_SLIDEIN\n");
#endif

	for(client_no=0;client_no<client_set_max;client_no++){
		SCIO_TrainerBGSlideInSet(bw,client_no);
	}

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_HP_GAUGE_IN(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	client_no;
	int	side;
	int	client_set_max=BattleWorkClientSetMaxGet(bw);
	CLIENT_PARAM	*cp;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//�Z�b�g���鑤�f�[�^�����[�h
	side=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("HP_GAUGE_IN side:%d\n",side);
#endif

	switch(side){
	case SIDE_ALL:
		for(client_no=0;client_no<client_set_max;client_no++){
			SCIO_HPGaugeInSet(bw,sp,client_no,0);
		}
		break;
	case SIDE_MINE:
		for(client_no=0;client_no<client_set_max;client_no++){
			cp=BattleWorkClientParamGet(bw,client_no);
			if((cp->client_type&CLIENT_ENEMY_FLAG)==0){
				SCIO_HPGaugeInSet(bw,sp,client_no,0);
			}
		}
		break;
	case SIDE_ENEMY:
		for(client_no=0;client_no<client_set_max;client_no++){
			cp=BattleWorkClientParamGet(bw,client_no);
			if(cp->client_type&CLIENT_ENEMY_FLAG){
				SCIO_HPGaugeInSet(bw,sp,client_no,0);
			}
		}
		break;
	default:
		client_no=SideClientNoGet(bw,sp,side);
		SCIO_HPGaugeInSet(bw,sp,client_no,0);
		break;
	}

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_HP_GAUGE_IN_WAIT(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	client_no;
	int	side;
	int	client_set_max=BattleWorkClientSetMaxGet(bw);
	CLIENT_PARAM	*cp;
	u8	wait;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//�Z�b�g���鑤�f�[�^�����[�h
	side=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("HP_GAUGE_IN_WAIT side:%d\n",side);
#endif

	wait=0;

	switch(side){
	case SIDE_ALL:
		for(client_no=0;client_no<client_set_max;client_no++){
			SCIO_HPGaugeInSet(bw,sp,client_no,0);
		}
		break;
	case SIDE_MINE:
		for(client_no=0;client_no<client_set_max;client_no++){
			cp=BattleWorkClientParamGet(bw,client_no);
			if((cp->client_type&CLIENT_ENEMY_FLAG)==0){
				SCIO_HPGaugeInSet(bw,sp,client_no,wait);
				wait+=HP_GAUGE_IN_WAIT;
			}
		}
		break;
	case SIDE_ENEMY:
		for(client_no=0;client_no<client_set_max;client_no++){
			cp=BattleWorkClientParamGet(bw,client_no);
			if(cp->client_type&CLIENT_ENEMY_FLAG){
				SCIO_HPGaugeInSet(bw,sp,client_no,wait);
				wait+=HP_GAUGE_IN_WAIT;
			}
		}
		break;
	default:
		client_no=SideClientNoGet(bw,sp,side);
		SCIO_HPGaugeInSet(bw,sp,client_no,wait);
		break;
	}

	return	FALSE;
}


//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_HP_GAUGE_OUT(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	client_no;
	int	side;
	int	client_set_max=BattleWorkClientSetMaxGet(bw);
	CLIENT_PARAM	*cp;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//�Z�b�g���鑤�f�[�^�����[�h
	side=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("HP_GAUGE_OUT side:%d\n",side);
#endif

	switch(side){
	case SIDE_ALL:
		for(client_no=0;client_no<client_set_max;client_no++){
			SCIO_HPGaugeOutSet(bw,client_no);
		}
		break;
	case SIDE_MINE:
		for(client_no=0;client_no<client_set_max;client_no++){
			cp=BattleWorkClientParamGet(bw,client_no);
			if(((cp->client_type&CLIENT_ENEMY_FLAG)==0)&&
			   ((sp->no_reshuffle_client&No2Bit(client_no))==0)){
				SCIO_HPGaugeOutSet(bw,client_no);
			}
		}
		break;
	case SIDE_ENEMY:
		for(client_no=0;client_no<client_set_max;client_no++){
			cp=BattleWorkClientParamGet(bw,client_no);
			if(cp->client_type&CLIENT_ENEMY_FLAG){
				SCIO_HPGaugeOutSet(bw,client_no);
			}
		}
		break;
	default:
		client_no=SideClientNoGet(bw,sp,side);
		SCIO_HPGaugeOutSet(bw,client_no);
		break;
	}

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_SERVER_WAIT(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	if(ST_ServerQueCheck(sp)){
		SkillSeqInc(sp,1);
#ifdef DEBUG_PRINT_BATTLE
		OS_TPrintf("SERVER_WAIT\n");
#endif

	}
	else{
		ST_ServerQueTimeOutCheck(sp);
	}

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	void	DamageCalcAct(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	type;

	//�����m�[�}���X�L���́A�Z�^�C�v���m�[�}���ɂ���
	if(ST_ServerTokuseiGet(sp,sp->attack_client)==TOKUSYU_NOOMARUSUKIN){
		type=NORMAL_TYPE;
	}
	else if(sp->waza_type){
		type=sp->waza_type;
	}
	else{
		type=sp->AIWT.wtd[sp->waza_no_now].wazatype;
	}

	sp->damage=ST_WazaDamageCalc(bw,sp,
								 sp->waza_no_now,
								 sp->side_condition[BattleWorkMineEnemyCheck(bw,sp->defence_client)],
								 sp->field_condition,
								 sp->damage_power,
								 type,
								 sp->attack_client,sp->defence_client,sp->critical);

	sp->damage*=sp->critical;		//�N���e�B�J���q�b�g�ɂ��_���[�W�v�Z

	//�������ʈЗ̓A�b�v�́A�З́��_���[�W�ʃA�b�v
	if(ST_ServerSoubiEqpGet(sp,sp->attack_client)==SOUBI_WAZAIRYOKUUPHPMAINASU){
		sp->damage=sp->damage*(100+ST_ServerSoubiAtkGet(sp,sp->attack_client,ATK_CHECK_NORMAL))/100;
	}

	//�������ʂœ����Z�𑱂��Ă��鎞�ɈЗ͂��グ��ꍇ�́A�_���[�W�A�b�v
	if(ST_ServerSoubiEqpGet(sp,sp->attack_client)==SOUBI_ONAZIWAZANOIRYOKUUP){
		sp->damage=sp->damage*(10+sp->psp[sp->attack_client].wkw.metronome_work)/10;
	}

	//�����ǂ�̎��́A1.5�{�ɂ���
	if(sp->psp[sp->attack_client].wkw.sakidori_flag){
		if(sp->sakidori_total_turn==sp->psp[sp->attack_client].wkw.sakidori_count){
			sp->psp[sp->attack_client].wkw.sakidori_count--;
		}
		if((sp->sakidori_total_turn-sp->psp[sp->attack_client].wkw.sakidori_count)<2){
			sp->damage=sp->damage*15/10;
		}
		else{
			sp->psp[sp->attack_client].wkw.sakidori_flag=0;
		}
	}
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_DAMAGE_CALC(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("DAMAGE_CALC\n");
#endif

	DamageCalcAct(bw,sp);

	sp->damage=ST_DamageLossCalc(sp,sp->damage);
	sp->damage*=-1;

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_DAMAGE_CALC_NO_LOSS(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("DAMAGE_CALC_NO_LOSS\n");
#endif

	DamageCalcAct(bw,sp);

	sp->damage*=-1;

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_ATTACK_MESSAGE(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("ATTACK_MESSAGE\n");
#endif

#if 0
	//�A���U���̎��́A�ŏ���1��ڂ����\��
	if((sp->loop_flag==0)&&
	//�A�^�b�N���b�Z�[�W�\���Ȃ��t���O�������Ă��鎞�́A�\���Ȃ�
	  ((sp->server_status_flag&SERVER_STATUS_FLAG_NO_ATTACK_MSG)==0)){
		SCIO_AttackMessageSet(bw,sp);
	}
#endif
	//�A�^�b�N���b�Z�[�W�\���Ȃ��t���O�������Ă��鎞�́A�\���Ȃ�
	if((sp->server_status_flag&SERVER_STATUS_FLAG_NO_ATTACK_MSG)==0){
		SCIO_AttackMessageSet(bw,sp);
	}
	//�\���Ȃ��t���O��ON
	sp->server_status_flag|=SERVER_STATUS_FLAG_NO_ATTACK_MSG;
	sp->server_status_flag2|=SERVER_STATUS_FLAG2_ATTACK_MSG;

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_MESSAGE(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	MESSAGE_PARAM_DATA	mpd;
	MESSAGE_PARAM		mp;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("MESSAGE\n");
#endif

	MessageParamDataMake(sp,&mpd);
	MessageParamMake(bw,sp,&mpd,&mp);

	SCIO_MessageSet(bw,sp,&mp);

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_MESSAGE_NO_DIR(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	MESSAGE_PARAM_DATA	mpd;
	MESSAGE_PARAM		mp;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("MESSAGE_NO_DIR\n");
#endif

	MessageParamDataMake(sp,&mpd);
	MessageParamMake(bw,sp,&mpd,&mp);

	mp.msg_tag|=TAG_NO_DIR;

	SCIO_MessageSet(bw,sp,&mp);

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_MESSAGE_WORK(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("MESSAGE_WORK\n");
#endif

	SCIO_MessageSet(bw,sp,&sp->mp);

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_MESSAGE_PARAM(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	MESSAGE_PARAM_DATA	mpd;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("MESSAGE_PARAM\n");
#endif

	MessageParamDataMake(sp,&mpd);
	MessageParamMake(bw,sp,&mpd,&sp->mp);

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_MESSAGE_DIR(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	MESSAGE_PARAM_DATA	mpd;
	MESSAGE_PARAM		mp;
	int					side;
	int					client_no;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//side�����[�h
	side=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("MESSAGE_DIR\n");
#endif

	MessageParamDataMake(sp,&mpd);
	MessageParamMake(bw,sp,&mpd,&mp);

	mp.msg_tag|=TAG_DIR;
	mp.msg_client=SideClientNoGet(bw,sp,side);

	SCIO_MessageSet(bw,sp,&mp);

	return	FALSE;
}


//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_WAZA_EFFECT(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	side;
	u16	waza_no;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//side�����[�h
	side=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("WAZA_EFFECT\n");
#endif

	if(side==SIDE_WORK){
		waza_no=sp->waza_work;
	}
	else{
		waza_no=sp->waza_no_now;
	}

	//�Z�G�t�F�N�g�\���Ȃ��t���O�������Ă��鎞�́A�\���Ȃ�
	if((((sp->server_status_flag&SERVER_STATUS_FLAG_NO_WAZA_EFFECT)==0)&&
	//�Q�[���R���t�B�O�ŁA�Z�G�t�F�N�g��OFF�̎��́A�\���Ȃ�
		(BattleWorkConfigWazaEffectOnOffCheck(bw)==TRUE))||
	//�ւ񂵂�G�t�F�N�g�́A��ɕ\��
		(waza_no==WAZANO_HENSIN)){
		sp->server_status_flag|=SERVER_STATUS_FLAG_NO_WAZA_EFFECT;
		SCIO_WazaEffectSet(bw,sp,waza_no);
	}
	//�Q�[���R���t�B�O�ŁA�Z�G�t�F�N�g��OFF�̎��́A�E�G�C�g�V�[�P���X�փW�����v
	if(BattleWorkConfigWazaEffectOnOffCheck(bw)==FALSE){
		SkillSequenceGosub(sp,ARC_SUB_SEQ,SUB_SEQ_WAZA_EFFECT_WAIT);
	}

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_WAZA_EFFECT2(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	side;
	int	attack;
	int	defence;
	int	cli_a;
	int	cli_d;
	u16	waza_no;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//side�����[�h
	side=SkillSeqDataRead(sp);

	//attack�����[�h
	attack=SkillSeqDataRead(sp);

	//defence�����[�h
	defence=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("WAZA_EFFECT\n");
#endif

	if(side==SIDE_WORK){
		waza_no=sp->waza_work;
	}
	else{
		waza_no=sp->waza_no_now;
	}

	cli_a=SideClientNoGet(bw,sp,attack);
	cli_d=SideClientNoGet(bw,sp,defence);

	//�Z�G�t�F�N�g�\���Ȃ��t���O�������Ă��鎞�́A�\���Ȃ�
	if((((sp->server_status_flag&SERVER_STATUS_FLAG_NO_WAZA_EFFECT)==0)&&
	//�Q�[���R���t�B�O�ŁA�Z�G�t�F�N�g��OFF�̎��́A�\���Ȃ�
		(BattleWorkConfigWazaEffectOnOffCheck(bw)==TRUE))||
	//�ւ񂵂�G�t�F�N�g�́A��ɕ\��
		(waza_no==WAZANO_HENSIN)){
		sp->server_status_flag|=SERVER_STATUS_FLAG_NO_WAZA_EFFECT;
		SCIO_WazaEffect2Set(bw,sp,waza_no,cli_a,cli_d);
	}
	//�Q�[���R���t�B�O�ŁA�Z�G�t�F�N�g��OFF�̎��́A�E�G�C�g�V�[�P���X�փW�����v
	if(BattleWorkConfigWazaEffectOnOffCheck(bw)==FALSE){
		SkillSequenceGosub(sp,ARC_SUB_SEQ,SUB_SEQ_WAZA_EFFECT_WAIT);
	}

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_POKEMON_BLINK(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	side;
	int	client_no;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//�Z�b�g���鑤�f�[�^�����[�h
	side=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("POKEMON_BLINK side:%d\n",side);
#endif

	client_no=SideClientNoGet(bw,sp,side);

	SCIO_PokemonBlinkSet(bw,client_no,sp->waza_status_flag);

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_HP_CALC(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	side,client_no;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//�v�Z���鑤�f�[�^�����[�h
	side=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("HP_CALC side:%d\n",side);
#endif

#ifdef PM_DEBUG
	if(BattleWorkBattleStatusFlagGet(bw)&BATTLE_STATUS_FLAG_NO_HP_DEC){
		return	FALSE;
	}
#endif PM_DEBUG

	client_no=SideClientNoGet(bw,sp,side);

	//�����_���[�W�p�ɂg�o�����炵�����ۗʂ��i�[
	if((sp->psp[client_no].hp+sp->hp_calc_work)<=0){
		sp->hit_damage=sp->psp[client_no].hp*-1;
	}
	else{
		sp->hit_damage=sp->hp_calc_work;
	}

	//�_���[�W�̎������A�l��ݐ�
	if(sp->hit_damage<0){
		sp->total_damage[client_no]+=(sp->hit_damage*-1);
	}

	sp->psp[client_no].hp+=sp->hp_calc_work;
	if(sp->psp[client_no].hp<0){
		sp->psp[client_no].hp=0;
	}
	else if(sp->psp[client_no].hp>sp->psp[client_no].hpmax){
		sp->psp[client_no].hp=sp->psp[client_no].hpmax;
	}
	ST_PSPtoPPCopy(bw,sp,client_no);

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_HP_GAUGE_CALC(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	side,client_no;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//�v�Z���鑤�f�[�^�����[�h
	side=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("HP_GAUGE_CALC side:%d\n",side);
#endif

#ifdef PM_DEBUG
	if(BattleWorkBattleStatusFlagGet(bw)&BATTLE_STATUS_FLAG_NO_HP_DEC){
		return	FALSE;
	}
#endif PM_DEBUG


	client_no=SideClientNoGet(bw,sp,side);

	SCIO_HPGaugeCalcSet(bw,sp,client_no);

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_KIZETSU_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	side,client_no,adrs;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//�v�Z���鑤�f�[�^�����[�h
	side=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("KIZETSU_CHECK side:%d\n",side);
#endif

	client_no=SideClientNoGet(bw,sp,side);

	if(sp->psp[client_no].hp==0){
		sp->kizetsu_client=client_no;
		sp->server_status_flag|=(No2Bit(client_no)<<SERVER_STATUS_FLAG_KIZETSU_SHIFT);
		//�m���񐔂��J�E���g
		sp->total_hinshi[client_no]++;
		//�m�����̂Ȃ��x�v�Z
		HinshiFriendCalc(bw,sp,client_no);
	}

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_KIZETSU_EFFECT(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("KIZETSU_EFFECT\n");
#endif

	SCIO_KizetsuEffectSet(bw,sp,sp->kizetsu_client);

	sp->server_status_flag&=(No2Bit(sp->kizetsu_client)<<SERVER_STATUS_FLAG_KIZETSU_SHIFT)^0xffffffff;
	sp->server_status_flag2|=No2Bit(sp->kizetsu_client)<<SERVER_STATUS_FLAG2_GET_EXP_SHIFT;
	sp->client_act_work[sp->kizetsu_client][ACT_PARA_ACT_NO]=SERVER_WAZA_END_NO;

	ST_ServerKizetsuWorkInit(bw,sp,sp->kizetsu_client);

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_WAIT(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	wait;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//WAIT_TIME�����[�h
	wait=SkillSeqDataRead(sp);

	//�ʐM�ΐ�łȂ����́A�{�^�����^�b�`���ꂽ��A�E�G�C�g���Ȃ���
	if((BattleWorkFightTypeGet(bw)&FIGHT_TYPE_SIO)==0){
		if((sys.trg&(PAD_BUTTON_A|PAD_BUTTON_B|PAD_BUTTON_X|PAD_BUTTON_Y))||(GF_TP_GetTrg())){
			sp->wait_cnt=wait;
		}
	}

	if(wait!=sp->wait_cnt){
		//�V�[�P���X�J�E���^�𖽗߃R�[�h�܂ł܂��߂�
		SkillSeqInc(sp,-2);
		sp->wait_cnt++;
	}
	else{
		sp->wait_cnt=0;
#ifdef DEBUG_PRINT_BATTLE
		OS_TPrintf("WAIT wait:%d\n",wait);
#endif

	}

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_SE_PLAY(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	side;
	int	se_no;
	int	client_no;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//side�����[�h
	side=SkillSeqDataRead(sp);

	//se_no�����[�h
	se_no=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("SE_PLAY se_no:%d\n",se_no);
#endif

	client_no=SideClientNoGet(bw,sp,side);

	SCIO_SePlaySet(bw,sp,se_no,client_no);

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_IF(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	act;
	int	src;
	int	dest;
	int	adrs;
	int	*data;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//act�����[�h
	act=SkillSeqDataRead(sp);

	//src�����[�h
	src=SkillSeqDataRead(sp);

	//dest�����[�h
	dest=SkillSeqDataRead(sp);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("IF act:%d src:%d dest:%d adrs:%d\n",act,src,dest,adrs);
#endif

	data=WS_SrcPointerGet(bw,sp,src);

	switch(act){
	case IF_FLAG_EQ:		//��v
		if(data[0]!=dest){
			adrs=0;
		}
		break;
	case IF_FLAG_NE:		//�s��v
		if(data[0]==dest){
			adrs=0;
		}
		break;
	case IF_FLAG_C:			//������
		if(data[0]<=dest){
			adrs=0;
		}
		break;
	case IF_FLAG_NC:		//�ȉ�
		if(data[0]>dest){
			adrs=0;
		}
		break;
	case IF_FLAG_BIT:		//�r�b�gON
		if((data[0]&dest)==0){
			adrs=0;
		}
		break;
	case IF_FLAG_NBIT:		//�r�b�gOFF
		if(data[0]&dest){
			adrs=0;
		}
		break;
	case IF_FLAG_AND:		//�r�b�gMASK���Ċ��S��v���邩�H
		if((data[0]&dest)!=dest){
			adrs=0;
		}
		break;
	default:
		GF_ASSERT_MSG(TRUE,"�s���Ȓ�`�ł�\n");
		break;
	}
	if(adrs){
		SkillSeqInc(sp,adrs);
	}

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_IF_PSP(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	act;
	int	side;
	int	src;
	int	dest;
	int	adrs;
	int	data;
	int	client_no;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//act�����[�h
	act=SkillSeqDataRead(sp);

	//side�����[�h
	side=SkillSeqDataRead(sp);

	//src�����[�h
	src=SkillSeqDataRead(sp);

	//dest�����[�h
	dest=SkillSeqDataRead(sp);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("IF_PSP act:%d src:%d dest:%d adrs:%d\n",act,src,dest,adrs);
#endif

	client_no=SideClientNoGet(bw,sp,side);

	data=ST_ServerPokemonServerParamGet(sp,client_no,src,NULL);

	switch(act){
	case IF_FLAG_EQ:		//��v
		if(data!=dest){
			adrs=0;
		}
		break;
	case IF_FLAG_NE:		//�s��v
		if(data==dest){
			adrs=0;
		}
		break;
	case IF_FLAG_C:			//������
		if(data<=dest){
			adrs=0;
		}
		break;
	case IF_FLAG_NC:		//�ȉ�
		if(data>dest){
			adrs=0;
		}
		break;
	case IF_FLAG_BIT:		//�r�b�gON
		if((data&dest)==0){
			adrs=0;
		}
		break;
	case IF_FLAG_NBIT:		//�r�b�gOFF
		if(data&dest){
			adrs=0;
		}
		break;
	case IF_FLAG_AND:		//�r�b�gMASK���Ċ��S��v���邩�H
		if((data&dest)!=dest){
			adrs=0;
		}
		break;
	default:
		GF_ASSERT_MSG(TRUE,"�s���Ȓ�`�ł�\n");
		break;
	}
	if(adrs){
		SkillSeqInc(sp,adrs);
	}
	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_FADE_OUT(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("FADE_OUT\n");
#endif

	SCIO_FadeOutSet(bw,sp);

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_JUMP(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	seq_no;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//be_seq_no�����[�h
	seq_no=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("JUMP seq_no:%d\n",seq_no);
#endif

	SkillSequenceJump(sp,ARC_SUB_SEQ,seq_no);

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_JUMP_BE_SEQ(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//��ѐ���Q�b�g
//	adrs=WT_WazaDataParaGet(sp->waza_no_now,ID_WTD_battleeffect);
	adrs=sp->AIWT.wtd[sp->waza_no_now].battleeffect;

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("JUMP_BE_SEQ adrs:%d\n",adrs);
#endif

	SkillSequenceJump(sp,ARC_BE_SEQ,adrs);

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_JUMP_WAZA_WORK(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	flag;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//flag�����[�h
	flag=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("JUMP_WAZA_WORK flag:%d\n",flag);
#endif

	//ATTACK_MESSAGE�o���悤�Ƀt���O�𗎂Ƃ�
	sp->server_status_flag&=SERVER_STATUS_FLAG_NO_ATTACK_MSG_OFF;
	//WAZA_EFFECT�o���悤�Ƀt���O�𗎂Ƃ�
	sp->server_status_flag&=SERVER_STATUS_FLAG_NO_WAZA_EFFECT_OFF;

	sp->waza_no_now=sp->waza_work;

	if(flag==JWW_FLAG_NORMAL){
		sp->defence_client=ST_ServerDefenceClientSet(bw,sp,sp->attack_client,sp->waza_work,1,0);
		sp->client_act_work[sp->attack_client][ACT_PARA_CLIENT_NO]=sp->defence_client;
	}

	if(sp->defence_client==NONE_CLIENT_NO){
		sp->next_server_seq_no=SERVER_WAZA_NO_BUFFER_SET_NO;
		SkillSequenceJump(sp,ARC_SUB_SEQ,SUB_SEQ_NO_DEFENCE);
	}
	else{
		SkillSequenceJump(sp,ARC_WAZA_SEQ,sp->waza_no_now);
	}

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_CRITICAL_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("CRITICAL_CHECK\n");
#endif

	//�ŏ��̐퓬�ƁA�ߊl�f���ł́A�}���ɂ�����Ȃ�
	if((BattleWorkFightTypeGet(bw)&FIGHT_TYPE_GET_DEMO)||
	   (BattleWorkBattleStatusFlagGet(bw)&BATTLE_STATUS_FLAG_FIRST_BATTLE)){
		sp->critical=1;
	}
	else{
		sp->critical=ST_CriticalCheck(sp,sp->attack_client,sp->defence_client,sp->critical_count,
									  ST_ServerParamDataGet(bw,sp,ID_SP_side_condition,sp->defence_client));
	}

#ifdef PM_DEBUG
	if(sp->dbp.debug_flag&DEBUG_FLAG_CRITICAL){
		sp->critical=2;
	}
#endif

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_GET_EXP_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int				adrs;
	u32				fight_type=BattleWorkFightTypeGet(bw);
	CLIENT_PARAM	*cp=BattleWorkClientParamGet(bw,sp->kizetsu_client);

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//�o���l�Q�b�g���������Ȃ��Ƃ��̂Ƃѐ�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("GET_EXP_CHECK adrs:%d\n",adrs);
#endif

	if((cp->client_type&CLIENT_ENEMY_FLAG)&&((fight_type&FIGHT_TYPE_NO_EXP)==0)){
		{
			int	i;
			int	total_exp;
			int	get_exp_poke_total=0;
			int	get_exp_item_total=0;
			u16	itemno;
			u16	totalexp;
			int	eqp;
			POKEMON_PARAM	*pp;

			//�莝���|�P�������w�K���u�������Ă��邩�`�F�b�N
			for(i=0;i<PokeParty_GetPokeCount(BattleWorkPokePartyGet(bw,CLIENT_NO_MINE));i++){
				pp=BattleWorkPokemonParamGet(bw,CLIENT_NO_MINE,i);
				if((PokeParaGet(pp,ID_PARA_monsno,NULL))&&(PokeParaGet(pp,ID_PARA_hp,NULL))){
					if(sp->get_exp_right_flag[(sp->kizetsu_client>>1)&1]&No2Bit(i)){
						get_exp_poke_total++;
					}
					itemno=PokeParaGet(pp,ID_PARA_item,NULL);
//					eqp=ItemParamGet(itemno,ITEM_PRM_EQUIP,HEAPID_BATTLE);
					eqp=ST_ItemParamGet(sp,itemno,ITEM_PRM_EQUIP);
					if(eqp==SOUBI_KEIKENTIGET){
						get_exp_item_total++;
					}
				}
			}
			totalexp=PokePersonalParaGet(sp->psp[sp->kizetsu_client].monsno,ID_PER_give_exp);
			totalexp=(totalexp*sp->psp[sp->kizetsu_client].level)/7;
			if(get_exp_item_total){
				sp->get_exp=(totalexp/2)/get_exp_poke_total;
				if(sp->get_exp==0){
					sp->get_exp=1;
				}
				sp->gakusyuu_get_exp=(totalexp/2)/get_exp_item_total;
				if(sp->gakusyuu_get_exp==0){
					sp->gakusyuu_get_exp=1;
				}
			}
			else{
				sp->get_exp=totalexp/get_exp_poke_total;
				if(sp->get_exp==0){
					sp->get_exp=1;
				}
				sp->gakusyuu_get_exp=0;
			}
		}
	}
	else{
		SkillSeqInc(sp,adrs);
	}

	return	FALSE;
}

//============================================================================================
/**
 *	GET_EXP��tsiw->work�̓Y����
 */
//============================================================================================
enum{
	GE_MSG_INDEX=0,
	GE_MSG_WAIT,
	GE_WAZA_CNT,
	GE_NOW_EXP,
	GE_WAZANO,
	GE_WAZAPOS,
	GE_SEL_MONS_NO,
};
//============================================================================================
/**
 *	GET_EXP��tsiw->work_p�̓Y����
 */
//============================================================================================
enum{
	GE_FONTOAM=0,
};

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_GET_EXP_INIT(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("GET_EXP_INIT\n");
#endif

	sp->tsiw=(TCB_SKILL_INTP_WORK *)sys_AllocMemory(HEAPID_BATTLE,sizeof(TCB_SKILL_INTP_WORK));
	sp->tsiw->bw=bw;
	sp->tsiw->sp=sp;
	sp->tsiw->seq_no=0;
	sp->tsiw->work[GE_SEL_MONS_NO]=0;
	TCB_Add(TCB_GetExp,sp->tsiw,NULL);

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_GET_EXP(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	if(sp->tsiw==NULL){
		//���߃R�[�h����ǂݔ�΂�
		SkillSeqInc(sp,1);
	}

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("GET_EXP\n");
#endif

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_GET_EXP_LOOP(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//�o���l�Q�b�g���������[�v���Ȃ��Ƃ��̂Ƃѐ�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("GET_EXP_LOOP adrs:%d\n",adrs);
#endif

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_POKEMON_LIST(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	client_no;
	int	pair_client;
	int	client_bit;
	int	client_set_max=BattleWorkClientSetMaxGet(bw);

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("POKEMON_LIST\n");
#endif

	client_bit=0;

	for(client_no=0;client_no<client_set_max;client_no++){
		if(sp->client_status[client_no]&CLIENT_STATUS_POKE_RESHUFFLE){
			client_bit|=No2Bit(client_no);
			SCIO_PokemonSelectSet(bw,sp,client_no,BPL_MODE_NO_CANCEL,0,NO_DOUBLE_SEL);
		}
	}

	for(client_no=0;client_no<client_set_max;client_no++){
		if(BattleWorkFightTypeGet(bw)==FIGHT_TYPE_2vs2_SIO){
			pair_client=BattleWorkPartnerClientNoGet(bw,client_no);
			if(((client_bit&No2Bit(client_no))==0)&&
			   ((client_bit&No2Bit(pair_client))==0)){
				client_bit|=No2Bit(client_no);
				SCIO_SioWaitMessage(bw,client_no);
			}
		}
		else{
			if((client_bit&No2Bit(client_no))==0){
				SCIO_SioWaitMessage(bw,client_no);
			}
		}
	}

	for(client_no=0;client_no<client_set_max;client_no++){
		if(sp->client_status[client_no]&CLIENT_STATUS_POKE_RESHUFFLE){
			sp->reshuffle_client=client_no;
			break;
		}
	}

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_POKEMON_LIST_WAIT(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	client_no;
	int	client_set_max;
	int	reshuffle_count;

	client_set_max=BattleWorkClientSetMaxGet(bw);
	reshuffle_count=0;

	for(client_no=0;client_no<client_set_max;client_no++){
		if(sp->client_status[client_no]&CLIENT_STATUS_POKE_RESHUFFLE){
			reshuffle_count++;
		}
	}

	for(client_no=0;client_no<client_set_max;client_no++){
		if((sp->client_status[client_no]&CLIENT_STATUS_POKE_RESHUFFLE)&&(ST_ServerBufferResGet(sp,client_no))){
			sp->reshuffle_sel_mons_no[client_no]=sp->server_buffer[client_no][0]-1;
			reshuffle_count--;
			if((sp->server_status_flag2&(No2Bit(client_no)<<SERVER_STATUS_FLAG2_SIO_WAIT_SHIFT))==0){
				sp->server_status_flag2|=(No2Bit(client_no)<<SERVER_STATUS_FLAG2_SIO_WAIT_SHIFT);
				SCIO_SioWaitMessage(bw,client_no);
			}
		}
	}

	if(reshuffle_count==0){
		sp->server_status_flag2&=SERVER_STATUS_FLAG2_SIO_WAIT_OFF;
		//���߃R�[�h����ǂݔ�΂�
		SkillSeqInc(sp,1);
#ifdef DEBUG_PRINT_BATTLE
		OS_TPrintf("POKEMON_LIST_WAIT\n");
#endif
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_POKEMON_RESHUFFLE(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	client_no;
	int	side;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//�Z�b�g���鑤�f�[�^�����[�h
	side=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("POKEMON_RESHUFFLE side:%d\n",side);
#endif

	switch(side){
	default:
		OS_Printf("WS_POKEMON_RESHUFFLE:�����ɂ���̂͂�������\n");
		break;
	case SIDE_ATTACK:
		client_no=sp->attack_client;
		break;
	case SIDE_RESHUFFLE:
		client_no=sp->reshuffle_client;
		break;
	case SIDE_HUKITOBASI:
		client_no=sp->defence_client;
		break;
	}

	//����ւ��t���O���I�t
	sp->client_status[client_no]&=CLIENT_STATUS_POKE_RESHUFFLE_OFF;

	//����ւ����Ȃ��t���O���I�t
	sp->no_reshuffle_client&=(No2Bit(client_no)^0xffffffff);

	sp->sel_mons_no[client_no]=sp->reshuffle_sel_mons_no[client_no];
	sp->reshuffle_sel_mons_no[client_no]=6;
	ST_PokemonParamGet(bw,sp,client_no,sp->sel_mons_no[client_no]);
	ST_ServerListRowChange(bw,sp,client_no,sp->sel_mons_no[client_no]);

	//�ΐ푊��̌���HP��ۑ�
	sp->hp_temp=sp->psp[CLIENT_NO_ENEMY].hp;

	ST_ServerReshuffleWorkInit(bw,sp,client_no);

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_POKEMON_RESHUFFLE_LOOP(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	client_no;
	int	client_set_max=BattleWorkClientSetMaxGet(bw);
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//�|�P��������ւ����������[�v���Ȃ��Ƃ��̔�ѐ�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("POKEMON_RESHUFFLE_LOOP adrs:%d\n",adrs);
#endif

	for(client_no=0;client_no<client_set_max;client_no++){
		if(sp->client_status[client_no]&CLIENT_STATUS_POKE_RESHUFFLE){
			sp->reshuffle_client=client_no;
			SkillSeqInc(sp,adrs);
			break;
		}
	}

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_POKEMON_GET_INIT(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	flag;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//flag�����[�h
	flag=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("POKEMON_GET_INIT flag:%d\n",flag);
#endif

	sp->tsiw=(TCB_SKILL_INTP_WORK *)sys_AllocMemory(HEAPID_BATTLE,sizeof(TCB_SKILL_INTP_WORK));
	sp->tsiw->bw=bw;
	sp->tsiw->sp=sp;
	sp->tsiw->seq_no=0;
	sp->tsiw->flag=flag;
	sp->tsiw->ballID=sp->item_work;
	TCB_Add(TCB_GetPokemon,sp->tsiw,NULL);

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_POKEMON_GET(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	if(sp->tsiw==NULL){
		//���߃R�[�h����ǂݔ�΂�
		SkillSeqInc(sp,1);
	}

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("POKEMON_GET\n");
#endif

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_RENZOKU(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	para;
	int	flag;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//���[�v�p�����[�^�����[�h
	para=SkillSeqDataRead(sp);

	//HITCHECK�L���t���O�����[�h
	flag=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("RENZOKU para:%d flag:%d\n",para,flag);
#endif

	if(sp->renzoku_count_temp==0){
		if(para==0){
			//�����X�L�������N�́A�A���U���J�E���^���ő�ɂ���
			if(ST_ServerTokuseiGet(sp,sp->attack_client)==TOKUSYU_SUKIRURINKU){
				para=5;
			}
			else{
				if((para=gf_rand()&3)<2){
					para+=2;
				}
				else{
					para=(gf_rand()&3)+2;
				}
			}
		}
		sp->renzoku_count=para;
		sp->renzoku_count_temp=para;
		sp->loop_hit_check=flag;
	}

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_VALUE(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	act;
	int	src;
	int	value;
	int	*data;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//act�����[�h
	act=SkillSeqDataRead(sp);

	//src�����[�h
	src=SkillSeqDataRead(sp);

	//value�����[�h
	value=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("VALUE act:%d src:%d value:%d\n",act,src,value);
#endif

	data=WS_SrcPointerGet(bw,sp,src);

	switch(act){
	case VAL_SET:		//�Z�b�g
		data[0]=value;
		break;
	case VAL_ADD:		//���Z
		data[0]+=value;
		break;
	case VAL_SUB:		//���Z
		data[0]-=value;
		break;
	case VAL_BIT:		//OR
		data[0]|=value;
		break;
	case VAL_NBIT:		//�l���r�b�g���]����AND
		data[0]&=(value^0xffffffff);
		break;
	case VAL_MUL:		//�|���Z
		data[0]*=value;
		break;
	case VAL_DIV:		//����Z
		data[0]/=value;
		break;
	case VAL_LSH:		//���V�t�g
		data[0]=data[0]<<value;
		break;
	case VAL_RSH:		//�E�V�t�g
		data[0]=data[0]>>value;
		break;
	case VAL_TO_BIT:	//�l���r�b�g�ɕϊ�
		data[0]=No2Bit(value);
		break;
	case VAL_GET:		//�l���擾
		GF_ASSERT_MSG(0,"VAL_GET�͎w��ł��܂���");
		break;
	case VAL_SUB_ZERO:	//���Z
		data[0]-=value;
		if(data[0]<0){
			data[0]=0;
		}
		break;
	case VAL_XOR:		//XOR
		data[0]^=value;
		break;
	case VAL_AND:		//AND
		data[0]&=value;
		break;
	default:
		GF_ASSERT_MSG(0,"�s���Ȓ�`�ł�\n");
		break;
	}

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_ABICNT_CALC(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	adrs1;
	int	adrs2;
	int	adrs3;
	int	para;
	int	value;
	int	flag;
	POKEMON_SERVER_PARAM	*psp=&sp->psp[sp->tsuika_client];

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//adrs�����[�h
	adrs1=SkillSeqDataRead(sp);
	adrs2=SkillSeqDataRead(sp);
	adrs3=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("ABICNT_CALC adrs1:%d adrs2:%d adrs3:%d\n",adrs1,adrs2,adrs3);
#endif

	flag=0;

	//abiritycnt���グ�����o���Ȃ������t���O��������
	sp->server_status_flag&=SERVER_STATUS_FLAG_COND_CHG_NG_OFF;

	//2�i�KDOWN
	if(sp->tsuika_para>=ADD_COND2_POWDOWN2){
		para=sp->tsuika_para-ADD_COND2_POWDOWN2;
		value=-2;
		sp->temp_work=STATUS_EFF_DOWN;
	}
	//2�i�KUP
	else if(sp->tsuika_para>=ADD_COND2_POWUP2){
		para=sp->tsuika_para-ADD_COND2_POWUP2;
		value=2;
		sp->temp_work=STATUS_EFF_UP;
	}
	//1�i�KDOWN
	else if(sp->tsuika_para>=ADD_COND2_POWDOWN){
		para=sp->tsuika_para-ADD_COND2_POWDOWN;
		value=-1;
		sp->temp_work=STATUS_EFF_DOWN;
	}
	//1�i�KUP
	else{
		para=sp->tsuika_para-ADD_COND2_POWUP;
		value=1;
		sp->temp_work=STATUS_EFF_UP;
	}
	if(value>0){
		if(psp->abiritycnt[COND_POW+para]==12){
			//abiritycnt���グ�����o���Ȃ������t���O���Z�b�g
			sp->server_status_flag|=SERVER_STATUS_FLAG_COND_CHG_NG;
			if((sp->tsuika_type==ADD_STATUS_INDIRECT)||
			   (sp->tsuika_type==ADD_STATUS_TOKUSEI)){
				SkillSeqInc(sp,adrs2);
			}
			else{
				sp->mp.msg_id=StatusNoUpMineMsg;
				sp->mp.msg_tag=TAG_NICK_STAT;
				sp->mp.msg_para[0]=ST_ServerTagNickParaMake(sp,sp->tsuika_client);
				sp->mp.msg_para[1]=COND_POW+para;
				SkillSeqInc(sp,adrs1);
			}
		}
		else{
			if(sp->tsuika_type==ADD_STATUS_TOKUSEI){
				sp->mp.msg_id=TokuseiStatusUpMineMsg;
				sp->mp.msg_tag=TAG_NICK_TOKU_STAT;
				sp->mp.msg_para[0]=ST_ServerTagNickParaMake(sp,sp->tsuika_client);
				sp->mp.msg_para[1]=sp->psp[sp->tsuika_client].speabino;
				sp->mp.msg_para[2]=COND_POW+para;
			}
			else if(sp->tsuika_type==ADD_STATUS_SOUBIITEM){
				sp->mp.msg_id=ItemCondUp1MineMsg;
				sp->mp.msg_tag=TAG_NICK_ITEM_STAT;
				sp->mp.msg_para[0]=ST_ServerTagNickParaMake(sp,sp->tsuika_client);
				sp->mp.msg_para[1]=sp->item_work;
				sp->mp.msg_para[2]=COND_POW+para;
			}
			else{
				sp->mp.msg_id=(value==1?CondUp1MineMsg:CondUp2MineMsg);
				sp->mp.msg_tag=TAG_NICK_STAT;
				sp->mp.msg_para[0]=ST_ServerTagNickParaMake(sp,sp->tsuika_client);
				sp->mp.msg_para[1]=COND_POW+para;
			}
			psp->abiritycnt[COND_POW+para]+=value;
			if(psp->abiritycnt[COND_POW+para]>12){
				psp->abiritycnt[COND_POW+para]=12;
			}
		}
	}
	else{
		if((sp->tsuika_flag&ADD_STATUS_NO_TOKUSEI)==0){
			//������\�͒ቺ������ꍇ�́A�Z���ʂ�����ł͖h���Ȃ�
			if(sp->attack_client!=sp->tsuika_client){
				//���낢����́A�\�͒ቺ���󂯂Ȃ�
				if(sp->scw[BattleWorkMineEnemyCheck(bw,sp->tsuika_client)].shiroikiri_count){
					sp->mp.msg_id=ShiroikiriGuardMineMsg;
					sp->mp.msg_tag=TAG_NICK;
					sp->mp.msg_para[0]=ST_ServerTagNickParaMake(sp,sp->tsuika_client);
					flag=1;
				}
				//�����N���A�{�f�B�A���낢���ނ�́A�\�͒ቺ���󂯂Ȃ�
				else if((ST_ServerKatayaburiTokuseiCheck(sp,sp->attack_client,sp->tsuika_client,TOKUSYU_KURIABODHI)==TRUE)||
						(ST_ServerKatayaburiTokuseiCheck(sp,sp->attack_client,sp->tsuika_client,TOKUSYU_SIROIKEMURI)==TRUE)){
					if(sp->tsuika_type==ADD_STATUS_TOKUSEI){
						sp->mp.msg_id=TokuseiNoTokuseiM2MMsg;
						sp->mp.msg_tag=TAG_NICK_TOKU_NICK_TOKU;
						sp->mp.msg_para[0]=ST_ServerTagNickParaMake(sp,sp->tsuika_client);
						sp->mp.msg_para[1]=sp->psp[sp->tsuika_client].speabino;
						sp->mp.msg_para[2]=ST_ServerTagNickParaMake(sp,sp->attack_client);
						sp->mp.msg_para[3]=sp->psp[sp->attack_client].speabino;
					}
					else{
						sp->mp.msg_id=ClearBodyMineMsg;
						sp->mp.msg_tag=TAG_NICK_TOKU;
						sp->mp.msg_para[0]=ST_ServerTagNickParaMake(sp,sp->tsuika_client);
						sp->mp.msg_para[1]=sp->psp[sp->tsuika_client].speabino;
					}
					flag=1;
				}
				//��������ǂ��߂́A��������������Ȃ�
				//���������肫�o�T�~�́A�U���͂�������Ȃ�
				else if( ((ST_ServerKatayaburiTokuseiCheck(sp,sp->attack_client,sp->tsuika_client,TOKUSYU_SURUDOIME)==TRUE)&&
						 ((COND_POW+para)==COND_HIT))||
						 ((ST_ServerKatayaburiTokuseiCheck(sp,sp->attack_client,sp->tsuika_client,TOKUSYU_KAIRIKIBASAMI)==TRUE)&&
						 ((COND_POW+para)==COND_POW))){
					if(sp->tsuika_type==ADD_STATUS_TOKUSEI){
						sp->mp.msg_id=TokuseiNoTokuseiM2MMsg;
						sp->mp.msg_tag=TAG_NICK_TOKU_NICK_TOKU;
						sp->mp.msg_para[0]=ST_ServerTagNickParaMake(sp,sp->tsuika_client);
						sp->mp.msg_para[1]=sp->psp[sp->tsuika_client].speabino;
						sp->mp.msg_para[2]=ST_ServerTagNickParaMake(sp,sp->attack_client);
						sp->mp.msg_para[3]=sp->psp[sp->attack_client].speabino;
					}
					else{
						sp->mp.msg_id=TokuseiNoCondDownMineMsg;
						sp->mp.msg_tag=TAG_NICK_TOKU_STAT;
						sp->mp.msg_para[0]=ST_ServerTagNickParaMake(sp,sp->tsuika_client);
						sp->mp.msg_para[1]=sp->psp[sp->tsuika_client].speabino;
						sp->mp.msg_para[2]=COND_POW+para;
					}
					flag=1;
				}
				else if(psp->abiritycnt[COND_POW+para]==0){
					//abiritycnt���グ�����o���Ȃ������t���O���Z�b�g
					sp->server_status_flag|=SERVER_STATUS_FLAG_COND_CHG_NG;
					if((sp->tsuika_type==ADD_STATUS_INDIRECT)||
					   (sp->tsuika_type==ADD_STATUS_TOKUSEI)){
						SkillSeqInc(sp,adrs2);
						return FALSE;
					}
					else{
						sp->mp.msg_id=StatusNoDownMineMsg;
						sp->mp.msg_tag=TAG_NICK_STAT;
						sp->mp.msg_para[0]=ST_ServerTagNickParaMake(sp,sp->tsuika_client);
						sp->mp.msg_para[1]=COND_POW+para;
						SkillSeqInc(sp,adrs1);
						return FALSE;
					}
				}
				//�������Ղ�́A�ǉ����ʂ��󂯂Ȃ�
				else if((ST_ServerKatayaburiTokuseiCheck(sp,sp->attack_client,sp->tsuika_client,TOKUSYU_RINPUN)==TRUE)&&
						(sp->tsuika_type==ADD_STATUS_INDIRECT)){
					flag=1;
				}
				//�݂���肪����ꍇ�́A������Ȃ�
				else if(sp->psp[sp->tsuika_client].condition2&CONDITION2_MIGAWARI){
					flag=2;
				}
			}
			else if(psp->abiritycnt[COND_POW+para]==0){
				//abiritycnt���グ�����o���Ȃ������t���O���Z�b�g
				sp->server_status_flag|=SERVER_STATUS_FLAG_COND_CHG_NG;
				if((sp->tsuika_type==ADD_STATUS_INDIRECT)||
				   (sp->tsuika_type==ADD_STATUS_TOKUSEI)){
					SkillSeqInc(sp,adrs2);
					return FALSE;
				}
				else{
					sp->mp.msg_id=StatusNoDownMineMsg;
					sp->mp.msg_tag=TAG_NICK_STAT;
					sp->mp.msg_para[0]=ST_ServerTagNickParaMake(sp,sp->tsuika_client);
					sp->mp.msg_para[1]=COND_POW+para;
					SkillSeqInc(sp,adrs1);
					return FALSE;
				}
			}
			if((flag==2)&&(sp->tsuika_type==ADD_STATUS_DIRECT)){
				SkillSeqInc(sp,adrs3);
				return FALSE;
			}
			else if((flag)&&(sp->tsuika_type==ADD_STATUS_INDIRECT)){
				SkillSeqInc(sp,adrs2);
				return FALSE;
			}
			else if(flag){
				SkillSeqInc(sp,adrs1);
				return FALSE;
			}
		}
		if(sp->tsuika_type==ADD_STATUS_TOKUSEI){
			sp->mp.msg_id=TokuseiStatusDownM2MMsg;
			sp->mp.msg_tag=TAG_NICK_TOKU_NICK_STAT;
			sp->mp.msg_para[0]=ST_ServerTagNickParaMake(sp,sp->attack_client);
			sp->mp.msg_para[1]=sp->psp[sp->attack_client].speabino;
			sp->mp.msg_para[2]=ST_ServerTagNickParaMake(sp,sp->tsuika_client);
			sp->mp.msg_para[3]=COND_POW+para;
		}
		else{
			sp->mp.msg_id=(value==-1?CondDown1MineMsg:CondDown2MineMsg);
			sp->mp.msg_tag=TAG_NICK_STAT;
			sp->mp.msg_para[0]=ST_ServerTagNickParaMake(sp,sp->tsuika_client);
			sp->mp.msg_para[1]=COND_POW+para;
		}
		psp->abiritycnt[COND_POW+para]+=value;
		if(psp->abiritycnt[COND_POW+para]<0){
			psp->abiritycnt[COND_POW+para]=0;
		}
#if 0
		if(psp->abiritycnt[COND_POW+para]==0){
			//abiritycnt���グ�����o���Ȃ������t���O���Z�b�g
			sp->server_status_flag|=SERVER_STATUS_FLAG_COND_CHG_NG;
			if((sp->tsuika_type==ADD_STATUS_INDIRECT)||
			   (sp->tsuika_type==ADD_STATUS_TOKUSEI)){
				SkillSeqInc(sp,adrs2);
			}
			else{
				sp->mp.msg_id=StatusNoDownMineMsg;
				sp->mp.msg_tag=TAG_NICK_STAT;
				sp->mp.msg_para[0]=ST_ServerTagNickParaMake(sp,sp->tsuika_client);
				sp->mp.msg_para[1]=COND_POW+para;
				SkillSeqInc(sp,adrs1);
			}
		}
		else{
			if((sp->tsuika_flag&ADD_STATUS_NO_TOKUSEI)==0){
				//������\�͒ቺ������ꍇ�́A�Z���ʂ�����ł͖h���Ȃ�
				if(sp->attack_client!=sp->tsuika_client){
					//���낢����́A�\�͒ቺ���󂯂Ȃ�
					if(sp->scw[BattleWorkMineEnemyCheck(bw,sp->tsuika_client)].shiroikiri_count){
						sp->mp.msg_id=ShiroikiriGuardMineMsg;
						sp->mp.msg_tag=TAG_NICK;
						sp->mp.msg_para[0]=ST_ServerTagNickParaMake(sp,sp->tsuika_client);
						flag=1;
					}
					//�����N���A�{�f�B�A���낢���ނ�́A�\�͒ቺ���󂯂Ȃ�
					else if((ST_ServerKatayaburiTokuseiCheck(sp,sp->attack_client,sp->tsuika_client,TOKUSYU_KURIABODHI)==TRUE)||
							(ST_ServerKatayaburiTokuseiCheck(sp,sp->attack_client,sp->tsuika_client,TOKUSYU_SIROIKEMURI)==TRUE)){
						if(sp->tsuika_type==ADD_STATUS_TOKUSEI){
							sp->mp.msg_id=TokuseiNoTokuseiM2MMsg;
							sp->mp.msg_tag=TAG_NICK_TOKU_NICK_TOKU;
							sp->mp.msg_para[0]=ST_ServerTagNickParaMake(sp,sp->tsuika_client);
							sp->mp.msg_para[1]=sp->psp[sp->tsuika_client].speabino;
							sp->mp.msg_para[2]=ST_ServerTagNickParaMake(sp,sp->attack_client);
							sp->mp.msg_para[3]=sp->psp[sp->attack_client].speabino;
						}
						else{
							sp->mp.msg_id=ClearBodyMineMsg;
							sp->mp.msg_tag=TAG_NICK_TOKU;
							sp->mp.msg_para[0]=ST_ServerTagNickParaMake(sp,sp->tsuika_client);
							sp->mp.msg_para[1]=sp->psp[sp->tsuika_client].speabino;
						}
						flag=1;
					}
					//��������ǂ��߂́A��������������Ȃ�
					//���������肫�o�T�~�́A�U���͂�������Ȃ�
					else if( ((ST_ServerKatayaburiTokuseiCheck(sp,sp->attack_client,sp->tsuika_client,TOKUSYU_SURUDOIME)==TRUE)&&
							 ((COND_POW+para)==COND_HIT))||
							 ((ST_ServerKatayaburiTokuseiCheck(sp,sp->attack_client,sp->tsuika_client,TOKUSYU_KAIRIKIBASAMI)==TRUE)&&
							 ((COND_POW+para)==COND_POW))){
						if(sp->tsuika_type==ADD_STATUS_TOKUSEI){
							sp->mp.msg_id=TokuseiNoTokuseiM2MMsg;
							sp->mp.msg_tag=TAG_NICK_TOKU_NICK_TOKU;
							sp->mp.msg_para[0]=ST_ServerTagNickParaMake(sp,sp->tsuika_client);
							sp->mp.msg_para[1]=sp->psp[sp->tsuika_client].speabino;
							sp->mp.msg_para[2]=ST_ServerTagNickParaMake(sp,sp->attack_client);
							sp->mp.msg_para[3]=sp->psp[sp->attack_client].speabino;
						}
						else{
							sp->mp.msg_id=TokuseiNoCondDownMineMsg;
							sp->mp.msg_tag=TAG_NICK_TOKU_STAT;
							sp->mp.msg_para[0]=ST_ServerTagNickParaMake(sp,sp->tsuika_client);
							sp->mp.msg_para[1]=sp->psp[sp->tsuika_client].speabino;
							sp->mp.msg_para[2]=COND_POW+para;
						}
						flag=1;
					}
					//�������Ղ�́A�ǉ����ʂ��󂯂Ȃ�
					else if((ST_ServerKatayaburiTokuseiCheck(sp,sp->attack_client,sp->tsuika_client,TOKUSYU_RINPUN)==TRUE)&&
							(sp->tsuika_type==ADD_STATUS_INDIRECT)){
						flag=1;
					}
					//�݂���肪����ꍇ�́A������Ȃ�
					else if(sp->psp[sp->tsuika_client].condition2&CONDITION2_MIGAWARI){
						flag=2;
					}
				}
				if((flag==2)&&(sp->tsuika_type==ADD_STATUS_DIRECT)){
					SkillSeqInc(sp,adrs3);
					return FALSE;
				}
				else if((flag)&&(sp->tsuika_type==ADD_STATUS_INDIRECT)){
					SkillSeqInc(sp,adrs2);
					return FALSE;
				}
				else if(flag){
					SkillSeqInc(sp,adrs1);
					return FALSE;
				}
			}
			if(sp->tsuika_type==ADD_STATUS_TOKUSEI){
				sp->mp.msg_id=TokuseiStatusDownM2MMsg;
				sp->mp.msg_tag=TAG_NICK_TOKU_NICK_STAT;
				sp->mp.msg_para[0]=ST_ServerTagNickParaMake(sp,sp->attack_client);
				sp->mp.msg_para[1]=sp->psp[sp->attack_client].speabino;
				sp->mp.msg_para[2]=ST_ServerTagNickParaMake(sp,sp->tsuika_client);
				sp->mp.msg_para[3]=COND_POW+para;
			}
			else{
				sp->mp.msg_id=(value==-1?CondDown1MineMsg:CondDown2MineMsg);
				sp->mp.msg_tag=TAG_NICK_STAT;
				sp->mp.msg_para[0]=ST_ServerTagNickParaMake(sp,sp->tsuika_client);
				sp->mp.msg_para[1]=COND_POW+para;
			}
			psp->abiritycnt[COND_POW+para]+=value;
			if(psp->abiritycnt[COND_POW+para]<0){
				psp->abiritycnt[COND_POW+para]=0;
			}
		}
#endif
	}

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_PSP_VALUE(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	act;
	int	side;
	int	src;
	int	value;
	int	client_no;
	int	data;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//act�����[�h
	act=SkillSeqDataRead(sp);

	//side�����[�h
	side=SkillSeqDataRead(sp);

	//src�����[�h
	src=SkillSeqDataRead(sp);

	//value�����[�h
	value=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("PSP_VALUE act:%d side:%d src:%d value:%d\n",act,side,src,value);
#endif

	client_no=SideClientNoGet(bw,sp,side);

	data=ST_ServerPokemonServerParamGet(sp,client_no,src,NULL);

	switch(act){
	case VAL_SET:		//�Z�b�g
		data=value;
		break;
	case VAL_ADD:		//���Z
		data+=value;
		break;
	case VAL_SUB:		//���Z
		data-=value;
		break;
	case VAL_BIT:		//�l��OR
		data|=value;
		break;
	case VAL_NBIT:		//�l���r�b�g���]����AND
		data&=(value^0xffffffff);
		break;
	case VAL_MUL:		//�|���Z
		data*=value;
		break;
	case VAL_DIV:		//����Z
		data/=value;
		break;
	case VAL_LSH:		//���V�t�g
		data=data<<value;
		break;
	case VAL_RSH:		//�E�V�t�g
		data=data>>value;
		break;
	case VAL_TO_BIT:	//�l���r�b�g�ɕϊ�
		data=No2Bit(value);
		break;
	case VAL_GET:		//�l���擾
		GF_ASSERT_MSG(0,"VAL_GET�͎w��ł��܂���");
		break;
	case VAL_SUB_ZERO:		//���Z
		data-=value;
		if(data<0){
			data=0;
		}
		break;
	case VAL_XOR:		//XOR
		data^=value;
		break;
	case VAL_AND:		//AND
		data&=value;
		break;
	default:
		GF_ASSERT_MSG(0,"�s���Ȓ�`�ł�\n");
		break;
	}

	//��������Ȃ�AI�ɒm�点��
	if(src==ID_PSP_speabino){
		TokusyuNoSet(sp,client_no,data);
	}

	ST_ServerPokemonServerParamPut(sp,client_no,src,(u8 *)&data);
	ST_PSPtoPPCopy(bw,sp,client_no);

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_CONDITION2_OFF(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	client_no;
	int	side;
	int	value;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//side�����[�h
	side=SkillSeqDataRead(sp);

	//value�����[�h
	value=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("CONDITION2_OFF side:%d value:%d\n",side,value);
#endif

	client_no=SideClientNoGet(bw,sp,side);

	sp->condition2_off_req[client_no]|=value;

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_VANISH_ON_OFF(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	side;
	int	sw;
	int	client_no;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//side�����[�h
	side=SkillSeqDataRead(sp);

	//sw�����[�h
	sw=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("VANISH_ON_OFF side:%d sw:%d\n",side,sw);
#endif

	client_no=SideClientNoGet(bw,sp,side);

	SCIO_PokemonVanishOnOff(bw,client_no,sw);

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_TOKUSEI_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	flag;
	int	side;
	int	tokusei;
	int	adrs;
	int	client_no;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//flag�����[�h
	flag=SkillSeqDataRead(sp);

	//side�����[�h
	side=SkillSeqDataRead(sp);

	//tokusei�����[�h
	tokusei=SkillSeqDataRead(sp);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);
	
#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("TOKUSEI_CHECK flag:%d side:%d tokusei:%d adrs:%d\n",flag,side,tokusei,adrs);
#endif

	//SIDE_ALL�̎��́A��ɂłĂ���|�P�������ׂĂ��`�F�b�N
	if(side==SIDE_ALL){
		{
			int	client_set_max;

			client_set_max=BattleWorkClientSetMaxGet(bw);

			for(client_no=0;client_no<client_set_max;client_no++){
				if(flag==TOKUSEI_HAVE){
					if(ST_ServerTokuseiGet(sp,client_no)==tokusei){
						SkillSeqInc(sp,adrs);
						sp->tokusei_client=client_no;
						break;
					}
				}
				else{
					//�N�������Ă��Ȃ����Ƃ��`�F�b�N
					if(ST_ServerTokuseiGet(sp,client_no)==tokusei){
						break;
					}
				}
			}
		}
	}
	else{
		client_no=SideClientNoGet(bw,sp,side);
	
		if(flag==TOKUSEI_HAVE){
			if(ST_ServerTokuseiGet(sp,client_no)==tokusei){
				SkillSeqInc(sp,adrs);
				sp->tokusei_client=client_no;
			}
		}
		else{
			if(ST_ServerTokuseiGet(sp,client_no)!=tokusei){
				SkillSeqInc(sp,adrs);
				sp->tokusei_client=client_no;
			}
		}
	}

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_RANDOM_GET(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	range;
	int	ofs;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//range�����[�h
	range=SkillSeqDataRead(sp);
	range+=1;

	//ofs�����[�h
	ofs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("RANDOM_GET range:%d ofs:%d\n",range,ofs);
#endif

	sp->calc_work=(gf_rand()%range)+ofs;

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_VALUE_WORK(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	act;
	int	src;
	int	dest;
	int	*data_s;
	int	*data_d;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//act�����[�h
	act=SkillSeqDataRead(sp);

	//src�����[�h
	src=SkillSeqDataRead(sp);

	//dest�����[�h
	dest=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("VALUE_WORK act:%d src:%d dest :%d\n",act,src,dest);
#endif

	data_s=WS_SrcPointerGet(bw,sp,src);
	data_d=WS_SrcPointerGet(bw,sp,dest);

	switch(act){
	case VAL_SET:		//�Z�b�g
		data_s[0]=data_d[0];
		break;
	case VAL_ADD:		//���Z
		data_s[0]+=data_d[0];
		break;
	case VAL_SUB:		//���Z
		data_s[0]-=data_d[0];
		break;
	case VAL_BIT:		//OR
		data_s[0]|=data_d[0];
		break;
	case VAL_NBIT:		//�l���r�b�g���]����AND
		data_s[0]&=(data_d[0]^0xffffffff);
		break;
	case VAL_MUL:		//�|���Z
		data_s[0]*=data_d[0];
		break;
	case VAL_DIV:		//����Z
		data_s[0]/=data_d[0];
		break;
	case VAL_LSH:		//���V�t�g
		data_s[0]=data_s[0]<<data_d[0];
		break;
	case VAL_RSH:		//�E�V�t�g
		data_s[0]=data_s[0]>>data_d[0];
		break;
	case VAL_TO_BIT:	//�l���r�b�g�ɕϊ�
		data_s[0]=No2Bit(data_d[0]);
		break;
	case VAL_GET:		//�l���擾
		data_d[0]=data_s[0];
		break;
	case VAL_SUB_ZERO:	//���Z
		data_s[0]-=data_d[0];
		if(data_s[0]<0){
			data_s[0]=0;
		}
		break;
	case VAL_XOR:		//XOR
		data_s[0]^=data_d[0];
		break;
	case VAL_AND:		//AND
		data_s[0]&=data_d[0];
		break;
	default:
		GF_ASSERT_MSG(0,"�s���Ȓ�`�ł�\n");
		break;
	}

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_PSP_VALUE_WORK(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	act;
	int	side;
	int	src;
	int	dest;
	int	client_no;
	int	data;
	int	*data_d;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//act�����[�h
	act=SkillSeqDataRead(sp);

	//side�����[�h
	side=SkillSeqDataRead(sp);

	//src�����[�h
	src=SkillSeqDataRead(sp);

	//dest�����[�h
	dest=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("PSP_VALUE_WORK act:%d side:%d src:%d dest:%d\n",act,side,src,dest);
#endif

	client_no=SideClientNoGet(bw,sp,side);

	data=ST_ServerPokemonServerParamGet(sp,client_no,src,NULL);
	data_d=WS_SrcPointerGet(bw,sp,dest);

	switch(act){
	case VAL_SET:		//�Z�b�g
		data=data_d[0];
		break;
	case VAL_ADD:		//���Z
		data+=data_d[0];
		break;
	case VAL_SUB:		//���Z
		data-=data_d[0];
		break;
	case VAL_BIT:		//�l��OR
		data|=data_d[0];
		break;
	case VAL_NBIT:		//�l���r�b�g���]����AND
		data&=(data_d[0]^0xffffffff);
		break;
	case VAL_MUL:		//�|���Z
		data*=data_d[0];
		break;
	case VAL_DIV:		//����Z
		data/=data_d[0];
		break;
	case VAL_LSH:		//���V�t�g
		data=data<<data_d[0];
		break;
	case VAL_RSH:		//�E�V�t�g
		data=data>>data_d[0];
		break;
	case VAL_TO_BIT:	//�l���r�b�g�ɕϊ�
		data=No2Bit(data_d[0]);
		break;
	case VAL_GET:		//�l���擾
		data_d[0]=data;
		break;
	case VAL_SUB_ZERO:
		data-=data_d[0];
		if(data<0){
			data=0;
		}
		break;
	case VAL_XOR:		//XOR
		data^=data_d[0];
		break;
	case VAL_AND:		//AND
		data&=data_d[0];
		break;
	default:
		GF_ASSERT_MSG(0,"�s���Ȓ�`�ł�\n");
		break;
	}

	if(act!=VAL_GET){
		//��������Ȃ�AI�ɒm�点��
		if(src==ID_PSP_speabino){
			TokusyuNoSet(sp,client_no,data);
		}
		ST_ServerPokemonServerParamPut(sp,client_no,src,(u8 *)&data);
		ST_PSPtoPPCopy(bw,sp,client_no);
	}

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_BRANCH(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("BRANCH adrs:%d\n",adrs);
#endif

	SkillSeqInc(sp,adrs);

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_GOSUB(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	seq_no;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//seq_no�����[�h
	seq_no=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("GOSUB seq_no:%d\n",seq_no);
#endif

	SkillSequenceGosub(sp,ARC_SUB_SEQ,seq_no);

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_GOSUB_WORK(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	para;
	int	*data;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//para�����[�h
	para=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("GOSUB_WORK para:%d\n",para);
#endif

	data=WS_SrcPointerGet(bw,sp,para);

	SkillSequenceGosub(sp,ARC_SUB_SEQ,data[0]);

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_OUMU_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	fight_type;
	int	waza_no;

	waza_no=0;
	fight_type=BattleWorkFightTypeGet(bw);

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("OUMU_CHECK\n");
#endif

	if(sp->waza_no_oumu[sp->attack_client]){
		waza_no=sp->waza_no_oumu[sp->attack_client];
	}
	else{
		if(fight_type&FIGHT_TYPE_2vs2){
			//�󂯂Ă���Z�̒����烉���_���ŌJ��o��
			waza_no=sp->waza_no_oumu_hit[sp->attack_client][0]+
					sp->waza_no_oumu_hit[sp->attack_client][1]+
					sp->waza_no_oumu_hit[sp->attack_client][2]+
					sp->waza_no_oumu_hit[sp->attack_client][3];
			if(waza_no){
				do{
					waza_no=sp->waza_no_oumu_hit[sp->attack_client][gf_rand()%4];
				}while(waza_no==0);
			}
		}
	}
	if((waza_no)&&(ST_OumuEncoreNGCheck(sp,waza_no)==TRUE)){
		//ATTACK_MESSAGE�o���悤�Ƀt���O�𗎂Ƃ�
		sp->server_status_flag&=SERVER_STATUS_FLAG_NO_ATTACK_MSG_OFF;
		//WAZA_EFFECT�o���悤�Ƀt���O�𗎂Ƃ�
		sp->server_status_flag&=SERVER_STATUS_FLAG_NO_WAZA_EFFECT_OFF;
		//�ʂ̋Z�V�[�P���X�փW�����v
		sp->waza_no_now=waza_no;
		sp->defence_client=ST_ServerDefenceClientSet(bw,sp,sp->attack_client,waza_no,1,0);
		if(sp->defence_client==NONE_CLIENT_NO){
			sp->next_server_seq_no=SERVER_WAZA_NO_BUFFER_SET_NO;
			SkillSequenceJump(sp,ARC_SUB_SEQ,SUB_SEQ_NO_DEFENCE);
		}
		else{
			sp->client_act_work[sp->attack_client][ACT_PARA_CLIENT_NO]=sp->defence_client;
			SkillSequenceJump(sp,ARC_WAZA_SEQ,waza_no);
		}
	}
	else{
		sp->ostf[sp->attack_client].no_pressure_flag=1;
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_KUROIKIRI(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	i;
	int	client_no;
	int	client_set_max;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("KUROIKIRI\n");
#endif

	client_set_max=BattleWorkClientSetMaxGet(bw);

	for(client_no=0;client_no<client_set_max;client_no++){
		for(i=COND_HP;i<COND_MAX;i++){
			sp->psp[client_no].abiritycnt[i]=COND_NUM_DEFAULT;
		}
		sp->psp[client_no].condition2&=CONDITION2_KIAIDAME_OFF;
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_KEEP_ON(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	side;
	int	client_no;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//side�����[�h
	side=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("KEEP_ON side:%d\n",side);
#endif

	client_no=SideClientNoGet(bw,sp,side);

	ST_ServerKeepOn(bw,sp,client_no);

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_KEEP_OFF(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	side;
	int	client_no;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//side�����[�h
	side=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("KEEP_OFF side:%d\n",side);
#endif

	client_no=SideClientNoGet(bw,sp,side);

	ST_ServerKeepOff(bw,sp,client_no);

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_STATUS_SET(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	side;
	int	status;
	int	client_no;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//side�����[�h
	side=SkillSeqDataRead(sp);

	//status�����[�h
	status=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("STATUS_SET side:%d status:%d\n",side,status);
#endif

	client_no=SideClientNoGet(bw,sp,side);

	SCIO_HPGaugeStatusSet(bw,client_no,status);

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_TRAINER_MESSAGE(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	side;
	int	type;
	int	client_no;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//side�����[�h
	side=SkillSeqDataRead(sp);

	//type�����[�h
	type=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("TRAINER_MESSAGE side:%d type:%d\n",side,type);
#endif

	client_no=SideClientNoGet(bw,sp,side);

	SCIO_TrainerMessageSet(bw,client_no,type);

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================

static	u8	OkodukaiTable[]={
	0,
	0,
	4,
	4,
	4,
	4,
	4,
	8,
	4,
	8,
	4,
	8,
	8,
	8,
	6,
	12,
	12,
	12,
	4,
	8,
	16,
	16,
	2,
	16,
	15,
	15,
	8,
	20,
	2,
	8,
	8,
	30,
	40,
	40,
	50,
	50,
	14,
	16,
	10,
	15,
	15,
	12,
	4,
	4,
	1,
	1,
	8,
	5,
	12,
	8,
	8,
	30,
	6,
	15,
	15,
	8,
	8,
	6,
	6,
	10,
	5,
	5,
	30,
	25,
	30,
	30,
	30,
	30,
	30,
	50,
	14,
	10,
	20,
	10,
	30,
	30,
	30,
	30,
	30,
	30,
	8,
	8,
	18,
	8,
	10,
	18,
	45,
	20,
	20,
	10,
	30,
	30,
	30,
	30,
	30,
	25,
	25,
};

static	u32	OkodukaiCalcAct(BATTLE_WORK *bw,SERVER_PARAM *sp,int num)
{
	int				i=0;
	void			*buf;
	u32				money;
	u8				level=0;
	TRAINER_DATA	td;

	buf=sys_AllocMemory(HEAPID_BATTLE,sizeof(POKEDATA_TYPE_MULTI)*POKEMON_TEMOTI_MAX);
	TT_TrainerDataGet(bw->trainer_id[num],&td);
	TT_TrainerPokeDataGet(bw->trainer_id[num],buf);

	switch(td.data_type){
	default:
	case DATATYPE_NORMAL:
		{
			POKEDATA_TYPE_NORMAL	*ptn;

			ptn=(POKEDATA_TYPE_NORMAL *)buf;
			level=ptn[td.poke_count-1].level;
		}
		break;
	case DATATYPE_WAZA:
		{
			POKEDATA_TYPE_WAZA	*ptw;

			ptw=(POKEDATA_TYPE_WAZA *)buf;
			level=ptw[td.poke_count-1].level;
		}
		break;
	case DATATYPE_ITEM:
		{
			POKEDATA_TYPE_ITEM	*pti;

			pti=(POKEDATA_TYPE_ITEM *)buf;
			level=pti[td.poke_count-1].level;
		}
		break;
	case DATATYPE_MULTI:
		{
			POKEDATA_TYPE_MULTI	*ptm;

			ptm=(POKEDATA_TYPE_MULTI *)buf;
			level=ptm[td.poke_count-1].level;
		}
		break;
	}

	//�^�b�O�o�g���AAI�}���`�͓��{
	if((bw->fight_type&FIGHT_TYPE_TAG)||
	   (bw->fight_type==FIGHT_TYPE_AI_MULTI)){
		money=level*4*sp->okodukai_value*OkodukaiTable[td.tr_type];
	}
	//�_�u���o�g���͂Q�{
	else if(bw->fight_type&FIGHT_TYPE_2vs2){
		money=level*4*sp->okodukai_value*2*OkodukaiTable[td.tr_type];
	}
	//�V���O���o�g���͓��{
	else{
		money=level*4*sp->okodukai_value*OkodukaiTable[td.tr_type];
	}

	sys_FreeMemoryEz(buf);

	return money;
}

static	BOOL	WS_OKODUKAI_CALC(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	u32	money;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("OKODUKAI_CALC\n");
#endif

	if(bw->win_lose_flag==FIGHT_WIN){
		money=OkodukaiCalcAct(bw,sp,CLIENT_NO_ENEMY);
		if((bw->fight_type&FIGHT_TYPE_TAG)||
		   (bw->fight_type==FIGHT_TYPE_AI_MULTI)){
			money+=OkodukaiCalcAct(bw,sp,CLIENT_NO_ENEMY2);
		}
		Mystatus_AddGold(BattleWorkMyStatusGet(bw,CLIENT_NO_MINE),money);
	}
	else{
		money=CalcLosePenalty(bw->poke_party[CLIENT_NO_MINE],bw->my_status[CLIENT_NO_MINE]);
		Mystatus_SubGold(BattleWorkMyStatusGet(bw,CLIENT_NO_MINE),money);
	}

	if(money){
		sp->msg_work=money;
	}
	else{
		sp->msg_work=0;
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_STATUS_EFFECT(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	client_no;
	int	side;
	int	status;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//side�����[�h
	side=SkillSeqDataRead(sp);

	//status�����[�h
	status=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("STATUS_EFFECT side:%d status:%d\n",side,status);
#endif

	if((BattleWorkConfigWazaEffectOnOffCheck(bw)==TRUE)||
		//�݂����n�́A��ɕ\��
	   (status==STATUS_EFF_MIGAWARI_OUT)||
	   (status==STATUS_EFF_MIGAWARI_IN)||
	   (status==STATUS_ACTION_DOLL_OFF)||
	   (status==STATUS_ACTION_DOLL_ON)){
		client_no=SideClientNoGet(bw,sp,side);
		if(ST_ServerStatusEffectMigawariCheck(sp,client_no,status)==TRUE){
			SCIO_StatusEffectSet(bw,sp,client_no,status);
		}
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_STATUS_EFFECT2(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	cl1,cl2;
	int	side1;
	int	side2;
	int	status;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//side1�����[�h
	side1=SkillSeqDataRead(sp);

	//side2�����[�h
	side2=SkillSeqDataRead(sp);

	//status�����[�h
	status=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("STATUS_EFFECT2 side1:%d side2:%d status:%d\n",side1,side2,status);
#endif

	if((BattleWorkConfigWazaEffectOnOffCheck(bw)==TRUE)||
		//�݂����n�́A��ɕ\��
	   (status==STATUS_EFF_MIGAWARI_OUT)||
	   (status==STATUS_EFF_MIGAWARI_IN)||
	   (status==STATUS_ACTION_DOLL_OFF)||
	   (status==STATUS_ACTION_DOLL_ON)){
		cl1=SideClientNoGet(bw,sp,side1);
		cl2=SideClientNoGet(bw,sp,side2);
		if((ST_ServerStatusEffectMigawariCheck(sp,cl1,status)==TRUE)&&
		   (ST_ServerStatusEffectMigawariCheck(sp,cl2,status)==TRUE)){
			SCIO_StatusEffect2Set(bw,sp,cl1,cl2,status);
		}
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_STATUS_EFFECT_WORK(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	client_no;
	int	side;
	int	status;
	int	*data;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//side�����[�h
	side=SkillSeqDataRead(sp);

	//status�����[�h
	status=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("STATUS_EFFECT_WORK side:%d status:%d\n",side,status);
#endif

	client_no=SideClientNoGet(bw,sp,side);
	data=WS_SrcPointerGet(bw,sp,status);

	if((BattleWorkConfigWazaEffectOnOffCheck(bw)==TRUE)||
		//�݂����n�́A��ɕ\��
	   (status==STATUS_EFF_MIGAWARI_OUT)||
	   (status==STATUS_EFF_MIGAWARI_IN)||
	   (data[0]==STATUS_ACTION_DOLL_OFF)||
	   (data[0]==STATUS_ACTION_DOLL_ON)){
		if(ST_ServerStatusEffectMigawariCheck(sp,client_no,data[0])==TRUE){
			SCIO_StatusEffectSet(bw,sp,client_no,data[0]);
		}
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_MODOSU_MESSAGE(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	client_no;
	int	side;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//side�����[�h
	side=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("MODOSU_MESSAGE side:%d\n",side);
#endif

	client_no=SideClientNoGet(bw,sp,side);

	SCIO_ModosuMessageSet(bw,sp,client_no,sp->sel_mons_no[client_no]);

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_KURIDASU_MESSAGE(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	client_no;
	int	side;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//side�����[�h
	side=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("KURIDASU_MESSAGE side:%d\n",side);
#endif

	client_no=SideClientNoGet(bw,sp,side);

	SCIO_KuridasuMessageSet(bw,sp,client_no,sp->sel_mons_no[client_no]);

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_ENCOUNT_MESSAGE(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	client_no;
	int	side;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//side�����[�h
	side=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("ENCOUNT_MESSAGE side:%d\n",side);
#endif

	client_no=SideClientNoGet(bw,sp,side);

	SCIO_EncountMessageSet(bw,sp,client_no);

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_ENCOUNT_KURIDASU_MESSAGE(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	client_no;
	int	side;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//side�����[�h
	side=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("ENCOUNT_KURIDASU_MESSAGE side:%d\n",side);
#endif

	client_no=SideClientNoGet(bw,sp,side);

	SCIO_EncountKuridasuMessageSet(bw,sp,client_no);

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_TRAINER_MESSAGE_WORK(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	side;
	int	client_no;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//side�����[�h
	side=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("TRAINER_MESSAGE_WORK side:%d\n",side);
#endif

	client_no=SideClientNoGet(bw,sp,side);

	SCIO_TrainerMessageSet(bw,client_no,sp->msg_work);

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_TEXTURE(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	cnt,i;
	int	adrs;
	int	wazatype;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("TEXTURE adrs:%d\n",adrs);
#endif

	//�����}���`�^�C�v�͎��g�̃^�C�v��ω�������Z�́A���s�ɂ���
	if(ST_ServerTokuseiGet(sp,sp->attack_client)==TOKUSYU_MARUTITAIPU){
		SkillSeqInc(sp,adrs);
		return FALSE;
	}

	//�����Z�������Ă��邩���o
	for(cnt=0;cnt<4;cnt++){
		if(sp->psp[sp->attack_client].waza[cnt]==0){
			break;
		}
	}
	//�����Ă���Z�̃^�C�v�̒�����A���݂̎����̃^�C�v�ł͂Ȃ����̂����邩�`�F�b�N
	for(i=0;i<cnt;i++){
		if(sp->psp[sp->attack_client].waza[i]!=WAZANO_TEKUSUTYAA){
			wazatype=sp->AIWT.wtd[sp->psp[sp->attack_client].waza[i]].wazatype;
			if(wazatype==HATE_TYPE){
				if((ST_ServerPokemonServerParamGet(sp,sp->attack_client,ID_PSP_type1,NULL)==GHOST_TYPE)||
				   (ST_ServerPokemonServerParamGet(sp,sp->attack_client,ID_PSP_type2,NULL)==GHOST_TYPE)){
					wazatype=GHOST_TYPE;
				}
				else{
					wazatype=NORMAL_TYPE;
				}
			}
			if((wazatype!=ST_ServerPokemonServerParamGet(sp,sp->attack_client,ID_PSP_type1,NULL))&&
			   (wazatype!=ST_ServerPokemonServerParamGet(sp,sp->attack_client,ID_PSP_type2,NULL))){
				break;
			}
		}
	}
	//�Ȃ������ꍇ�́A���܂����܂��ɂ���
	if(i==cnt){
		SkillSeqInc(sp,adrs);
	}
	else{
		//�����Ă���Z�̃^�C�v����A�����̃^�C�v�ł͂Ȃ����̂������_���őI��
		do{
			do{
				i=gf_rand()%cnt;
			}while(sp->psp[sp->attack_client].waza[i]==WAZANO_TEKUSUTYAA);
			wazatype=sp->AIWT.wtd[sp->psp[sp->attack_client].waza[i]].wazatype;
			if(wazatype==HATE_TYPE){
				if((ST_ServerPokemonServerParamGet(sp,sp->attack_client,ID_PSP_type1,NULL)==GHOST_TYPE)||
				   (ST_ServerPokemonServerParamGet(sp,sp->attack_client,ID_PSP_type2,NULL)==GHOST_TYPE)){
					wazatype=GHOST_TYPE;
				}
				else{
					wazatype=NORMAL_TYPE;
				}
			}
		}while((wazatype==ST_ServerPokemonServerParamGet(sp,sp->attack_client,ID_PSP_type1,NULL))||
			   (wazatype==ST_ServerPokemonServerParamGet(sp,sp->attack_client,ID_PSP_type2,NULL)));
		sp->psp[sp->attack_client].type1=wazatype;
		sp->psp[sp->attack_client].type2=wazatype;
		sp->msg_work=wazatype;
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_IF_WORK(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	act;
	int	src;
	int	dest;
	int	adrs;
	u32	*data_s;
	u32	*data_d;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//act�����[�h
	act=SkillSeqDataRead(sp);

	//src�����[�h
	src=SkillSeqDataRead(sp);

	//dest�����[�h
	dest=SkillSeqDataRead(sp);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("IF_WORK act:%d src:%d dest:%d adrs:%d\n",act,src,dest,adrs);
#endif

	data_s=WS_SrcPointerGet(bw,sp,src);
	data_d=WS_SrcPointerGet(bw,sp,dest);

	switch(act){
	case IF_FLAG_EQ:		//��v
		if(data_s[0]!=data_d[0]){
			adrs=0;
		}
		break;
	case IF_FLAG_NE:		//�s��v
		if(data_s[0]==data_d[0]){
			adrs=0;
		}
		break;
	case IF_FLAG_C:			//������
		if(data_s[0]<=data_d[0]){
			adrs=0;
		}
		break;
	case IF_FLAG_NC:		//�ȉ�
		if(data_s[0]>data_d[0]){
			adrs=0;
		}
		break;
	case IF_FLAG_BIT:		//�r�b�gON
		if((data_s[0]&data_d[0])==0){
			adrs=0;
		}
		break;
	case IF_FLAG_NBIT:		//�r�b�gOFF
		if(data_s[0]&data_d[0]){
			adrs=0;
		}
		break;
	case IF_FLAG_AND:		//�r�b�gMASK���Ċ��S��v���邩�H
		if((data_s[0]&data_d[0])!=data_d[0]){
			adrs=0;
		}
		break;
	default:
		GF_ASSERT_MSG(TRUE,"�s���Ȓ�`�ł�\n");
		break;
	}
	if(adrs){
		SkillSeqInc(sp,adrs);
	}
	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_IF_PSP_WORK(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	act;
	int	side;
	int	src;
	int	dest;
	int	adrs;
	u32	data_s;
	u32	*data_d;
	int	client_no;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//act�����[�h
	act=SkillSeqDataRead(sp);

	//side�����[�h
	side=SkillSeqDataRead(sp);

	//src�����[�h
	src=SkillSeqDataRead(sp);

	//dest�����[�h
	dest=SkillSeqDataRead(sp);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("IF_PSP_WORK act:%d side:%d src:%d dest:%d adrs:%d\n",act,side,src,dest,adrs);
#endif

	client_no=SideClientNoGet(bw,sp,side);

	data_s=ST_ServerPokemonServerParamGet(sp,client_no,src,NULL);
	data_d=WS_SrcPointerGet(bw,sp,dest);

	switch(act){
	case IF_FLAG_EQ:		//��v
		if(data_s!=data_d[0]){
			adrs=0;
		}
		break;
	case IF_FLAG_NE:		//�s��v
		if(data_s==data_d[0]){
			adrs=0;
		}
		break;
	case IF_FLAG_C:			//������
		if(data_s<=data_d[0]){
			adrs=0;
		}
		break;
	case IF_FLAG_NC:		//�ȉ�
		if(data_s>data_d[0]){
			adrs=0;
		}
		break;
	case IF_FLAG_BIT:		//�r�b�gON
		if((data_s&data_d[0])==0){
			adrs=0;
		}
		break;
	case IF_FLAG_NBIT:		//�r�b�gOFF
		if(data_s&data_d[0]){
			adrs=0;
		}
		break;
	case IF_FLAG_AND:		//�r�b�gMASK���Ċ��S��v���邩�H
		if((data_s&data_d[0])!=data_d[0]){
			adrs=0;
		}
		break;
	default:
		GF_ASSERT_MSG(TRUE,"�s���Ȓ�`�ł�\n");
		break;
	}
	if(adrs){
		SkillSeqInc(sp,adrs);
	}
	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_KOBAN_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("KOBAN_CHECK\n");
#endif

	sp->msg_work=sp->koban_counter*sp->okodukai_value;
	if(sp->msg_work>KOBAN_MAX){
		sp->msg_work=KOBAN_MAX;
	}
	Mystatus_AddGold(BattleWorkMyStatusGet(bw,CLIENT_NO_MINE),sp->msg_work);

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_HIKARINOKABE(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	adrs;
	int	dir;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("HIKARINOKABE adrs:%d\n",adrs);
#endif

	dir=BattleWorkMineEnemyCheck(bw,sp->attack_client);


	if(sp->side_condition[dir]&SIDE_CONDITION_TOKUSYUGUARD){
		SkillSeqInc(sp,adrs);
		sp->waza_status_flag|=WAZA_STATUS_FLAG_UMAKUKIMARAN;
	}
	else{
		sp->side_condition[dir]|=SIDE_CONDITION_TOKUSYUGUARD;
		sp->scw[dir].tokusyu_guard_count=5;
		sp->scw[dir].tokusyu_guard_client=sp->attack_client;
		//�������ʂŕǂ̃J�E���^��������
		if(ST_ServerSoubiEqpGet(sp,sp->attack_client)==SOUBI_KABENOZIKANHUERU){
			sp->scw[dir].tokusyu_guard_count+=ST_ServerSoubiAtkGet(sp,sp->attack_client,ATK_CHECK_NORMAL);
		}
		sp->mp.msg_tag=TAG_WAZA_DIR;
		sp->mp.msg_para[0]=sp->waza_no_now;
		sp->mp.msg_para[1]=sp->attack_client;
		if(ST_ServerHitCountCheck(bw,sp,SHCC_SIDE,sp->attack_client)==2){
			sp->mp.msg_id=TokusyuGuardMineMsg2vs2;
		}
		else{
			sp->mp.msg_id=TokusyuGuardMineMsg;
		}
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_RIHUREKUTAA(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	adrs;
	int	dir;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("RIHUREKUTAA adrs:%d\n",adrs);
#endif

	dir=BattleWorkMineEnemyCheck(bw,sp->attack_client);

	if(sp->side_condition[dir]&SIDE_CONDITION_BUTSURIGUARD){
		SkillSeqInc(sp,adrs);
		sp->waza_status_flag|=WAZA_STATUS_FLAG_UMAKUKIMARAN;
	}
	else{
		sp->side_condition[dir]|=SIDE_CONDITION_BUTSURIGUARD;
		sp->scw[dir].butsuri_guard_count=5;
		sp->scw[dir].butsuri_guard_client=sp->attack_client;
		//�������ʂŕǂ̃J�E���^��������
		if(ST_ServerSoubiEqpGet(sp,sp->attack_client)==SOUBI_KABENOZIKANHUERU){
			sp->scw[dir].butsuri_guard_count+=ST_ServerSoubiAtkGet(sp,sp->attack_client,ATK_CHECK_NORMAL);
		}
		sp->mp.msg_tag=TAG_WAZA_DIR;
		sp->mp.msg_para[0]=sp->waza_no_now;
		sp->mp.msg_para[1]=sp->attack_client;
		if(ST_ServerHitCountCheck(bw,sp,SHCC_SIDE,sp->attack_client)==2){
			sp->mp.msg_id=ButsuriGuardMineMsg2vs2;
		}
		else{
			sp->mp.msg_id=ButsuriGuardMineMsg;
		}
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_SIROIKIRI(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	adrs;
	int	dir;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("SIROIKIRI adrs:%d\n",adrs);
#endif

	dir=BattleWorkMineEnemyCheck(bw,sp->attack_client);

	if(sp->side_condition[dir]&SIDE_CONDITION_SHIROIKIRI){
		SkillSeqInc(sp,adrs);
		sp->waza_status_flag|=WAZA_STATUS_FLAG_UMAKUKIMARAN;
	}
	else{
		sp->side_condition[dir]|=SIDE_CONDITION_SHIROIKIRI;
		sp->scw[dir].shiroikiri_count=5;
		sp->scw[dir].shiroikiri_client=sp->attack_client;
//		sp->mp.msg_tag=TAG_NONE_DIR;
//		sp->mp.msg_para[0]=sp->attack_client;
//		sp->mp.msg_id=ShiroikiriMineMsg;
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_ICHIGEKI(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	u16	hit;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("ICHIGEKI\n");
#endif

	//�ʏ�̖������v�Z�����Ȃ��悤�ɂ���
	sp->server_status_flag|=SERVER_STATUS_FLAG_OTHER_HIT_CALC;

	//�������񂶂傤�́A�ꌂ�K�E�ł��Ȃ�
	if(ST_ServerKatayaburiTokuseiCheck(sp,sp->attack_client,sp->defence_client,TOKUSYU_GANZYOU)==TRUE){
		sp->waza_status_flag|=WAZA_STATUS_FLAG_GANZYOU_NOHIT;
	}
	else{
		if(((sp->psp[sp->defence_client].waza_kouka&WAZAKOUKA_LOCKON)==0)&&
		    (ST_ServerTokuseiGet(sp,sp->attack_client)!=TOKUSYU_NOOGAADO)&&
		    (ST_ServerTokuseiGet(sp,sp->defence_client)!=TOKUSYU_NOOGAADO)){
//			hit=WT_WazaDataParaGet(sp->waza_no_now,ID_WTD_hitprobability)+
			hit=sp->AIWT.wtd[sp->waza_no_now].hitprobability+
				(sp->psp[sp->attack_client].level-sp->psp[sp->defence_client].level);
			if(((gf_rand()%100)<hit)&&(sp->psp[sp->attack_client].level>=sp->psp[sp->defence_client].level)){
				hit=1;
			}
			else{
				hit=0;
			}
		}
		else{
			if((((sp->psp[sp->defence_client].wkw.lockon_client_no==sp->attack_client)&&
				 (sp->psp[sp->defence_client].waza_kouka&WAZAKOUKA_LOCKON))||
				 (ST_ServerTokuseiGet(sp,sp->attack_client)==TOKUSYU_NOOGAADO)||
				 (ST_ServerTokuseiGet(sp,sp->defence_client)==TOKUSYU_NOOGAADO))&&
				 (sp->psp[sp->attack_client].level>=sp->psp[sp->defence_client].level)){
				hit=1;
			}
			else{
//				hit=WT_WazaDataParaGet(sp->waza_no_now,ID_WTD_hitprobability)+
				hit=sp->AIWT.wtd[sp->waza_no_now].hitprobability+
					(sp->psp[sp->attack_client].level-sp->psp[sp->defence_client].level);
				if(((gf_rand()%100)<hit)&&(sp->psp[sp->attack_client].level>=sp->psp[sp->defence_client].level)){
					hit=1;
				}
				else{
					hit=0;
				}
			}
			sp->waza_status_flag|=WAZA_STATUS_FLAG_LOCK_ON;
		}
		if(hit){
			sp->damage=sp->psp[sp->defence_client].hp*-1;
			sp->waza_status_flag|=WAZA_STATUS_FLAG_ICHIGEKI;
		}
		else{
			if(sp->psp[sp->attack_client].level>=sp->psp[sp->defence_client].level){
				sp->waza_status_flag|=WAZA_STATUS_FLAG_NOHIT;
			}
			else{
				sp->waza_status_flag|=WAZA_STATUS_FLAG_ICHIGEKI_NOHIT;
			}
		}
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_DAMAGE_DIV(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	para;
	int	value;
	int	*data;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//para�����[�h
	para=SkillSeqDataRead(sp);

	//value�����[�h
	value=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("DAMAGE_DIV para:%d value:%d\n",para,value);
#endif

	data=WS_SrcPointerGet(bw,sp,para);

	data[0]=ST_ServerDamageDiv(data[0],value);

	return FALSE;
}
//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_DAMAGE_DIV_WORK(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	para;
	int	value;
	int	zero_work;
	int	*data_s;
	int	*data_d;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//para�����[�h
	para=SkillSeqDataRead(sp);

	//value�����[�h
	value=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("DAMAGE_DIV_WORK para:%d value:%d\n",para,value);
#endif

	data_s=WS_SrcPointerGet(bw,sp,para);
	data_d=WS_SrcPointerGet(bw,sp,value);

	if(data_s[0]<0){
		zero_work=-1;
	}
	else{
		zero_work=1;
	}

	data_s[0]/=data_d[0];

	if(data_s[0]==0){
		data_s[0]=zero_work;
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_MONOMANE(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("MONOMANE adrs:%d\n",adrs);
#endif
	
		//���̂܂˂ł��Ȃ��Z���A
	if((ST_MonomaneNGCheck(sp->waza_no_old[sp->defence_client])==FALSE)||
		//�ւ񂵂񒆂��A
	   (sp->psp[sp->attack_client].condition2&CONDITION2_HENSHIN)||
		//�݂������o����Ă��邩�A
	   (sp->psp[sp->defence_client].condition2&CONDITION2_MIGAWARI)||
	   //���肪�Z���o���̂����s���Ă��鎞�́A���̂܂ˎ��s
	   (sp->waza_no_old[sp->defence_client]==0)){
		SkillSeqInc(sp,adrs);
	}
	else{
		{
			int	waza_pos;
			int	waza_set_pos=-1;

			//���Ƃ��Ǝ����Ă���Z�������玸�s����
			for(waza_pos=0;waza_pos<WAZA_TEMOTI_MAX;waza_pos++){
				if(sp->psp[sp->attack_client].waza[waza_pos]==sp->waza_no_old[sp->defence_client]){
					break;
				}
				if((sp->psp[sp->attack_client].waza[waza_pos]==WAZANO_MONOMANE)&&(waza_set_pos==-1)){
					waza_set_pos=waza_pos;
				}
			}
			if(waza_pos==WAZA_TEMOTI_MAX){
				sp->waza_work=sp->waza_no_old[sp->defence_client];
				sp->psp[sp->attack_client].waza[waza_set_pos]=sp->waza_work;
//				if(WT_WazaDataParaGet(sp->waza_work,ID_WTD_pp)<5){
				if(sp->AIWT.wtd[sp->waza_work].pp<5){
//					sp->psp[sp->attack_client].pp[waza_set_pos]=WT_WazaDataParaGet(sp->waza_work,ID_WTD_pp);
					sp->psp[sp->attack_client].pp[waza_set_pos]=sp->AIWT.wtd[sp->waza_work].pp;
				}
				else{
					sp->psp[sp->attack_client].pp[waza_set_pos]=5;
				}
				sp->psp[sp->attack_client].wkw.monomane_bit|=No2Bit(waza_set_pos);
				//�Ƃ��Ă������R�s�[������A�J�E���^�����Z�b�g
				if(sp->waza_work==WAZANO_TOTTEOKI){
					sp->psp[sp->attack_client].wkw.totteoki_count=0;
				}
			}
			else{
				SkillSeqInc(sp,adrs);
			}
		}
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_YUBIWOHURU(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	waza_pos;
	u16	waza_no;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("YUBIWOHURU\n");
#endif

	while(1){
#ifdef PM_DEBUG
		if((sp->dbp.debug_flag&DEBUG_FLAG_YUBIHURU_DEBUG_SET)&&(sp->dbp.yubihuru_waza[0])){
			waza_no=sp->dbp.yubihuru_waza[sp->dbp.yubihuru_no];
			sp->dbp.yubihuru_no++;
			if((sp->dbp.yubihuru_no>7)||(sp->dbp.yubihuru_waza[sp->dbp.yubihuru_no]==0)){
				sp->dbp.yubihuru_no=0;
			}
		}
		else if((sp->dbp.debug_flag&DEBUG_FLAG_YUBIHURU_DEBUG_RANGE)&&
				(sp->dbp.yubihuru_waza[0])&&
				(sp->dbp.yubihuru_waza[1])){
			waza_no=sp->dbp.yubihuru_no;
			sp->dbp.yubihuru_no++;
			if(sp->dbp.yubihuru_waza[1]<sp->dbp.yubihuru_no){
				sp->dbp.yubihuru_no=sp->dbp.yubihuru_waza[0];
			}
		}
		else{
			waza_no=(gf_rand()%WAZANO_MAX)+1;
		}
#else
		waza_no=(gf_rand()%WAZANO_MAX)+1;
#endif
		//�����Ă���Z�͏o���Ȃ�
		for(waza_pos=0;waza_pos<WAZA_TEMOTI_MAX;waza_pos++){
			if(sp->psp[sp->attack_client].waza[waza_pos]==waza_no){
				break;
			}
		}
		if(waza_pos!=WAZA_TEMOTI_MAX){
			continue;
		}
		if(ST_YubiwohuruNGCheck(waza_no)==FALSE){
			continue;
		}
		//�ʂ̋Z�V�[�P���X�փW�����v
		sp->waza_work=waza_no;
//		sp->waza_no_now=waza_no;
//		sp->defence_client=ST_ServerDefenceClientSet(bw,sp,sp->attack_client,waza_no,1,0);
//		sp->client_act_work[sp->attack_client][ACT_PARA_CLIENT_NO]=sp->defence_client;
//		SkillSequenceJump(sp,ARC_WAZA_SEQ,waza_no);
//		//ATTACK_MESSAGE�o���悤�Ƀt���O�𗎂Ƃ�
//		sp->server_status_flag&=SERVER_STATUS_FLAG_NO_ATTACK_MSG_OFF;
//		//WAZA_EFFECT�o���悤�Ƀt���O�𗎂Ƃ�
//		sp->server_status_flag&=SERVER_STATUS_FLAG_NO_WAZA_EFFECT_OFF;
		break;
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_KANASIBARI(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	adrs;
	int	waza_pos;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("KANASIBARI adrs:%d\n",adrs);
#endif

	waza_pos=ST_ServerWazaPosGet(&sp->psp[sp->defence_client],sp->waza_no_old[sp->defence_client]);

	if((sp->psp[sp->defence_client].wkw.kanashibari_wazano==0)&&
	   (waza_pos!=WAZA_TEMOTI_MAX)&&
	   (sp->psp[sp->defence_client].pp[waza_pos])&&
	   (sp->waza_no_old[sp->defence_client])){
		sp->waza_work=sp->waza_no_old[sp->defence_client];
		sp->psp[sp->defence_client].wkw.kanashibari_wazano=sp->waza_work;
		sp->psp[sp->defence_client].wkw.kanashibari_count=gf_rand()%4+3;	//�Q�`�T�i���ۂ͂R�`�U�ɂ���j
	}
	else{
		SkillSeqInc(sp,adrs);
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_COUNTER(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	dir_a,dir_d;
	int	client_no;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("COUNTER\n");
#endif

	client_no=sp->otf[sp->attack_client].butsuri_otf_client;
	dir_a=BattleWorkMineEnemyCheck(bw,sp->attack_client);
	dir_d=BattleWorkMineEnemyCheck(bw,client_no);

	if((sp->otf[sp->attack_client].butsuri_otf_damage[client_no])&&
	   (dir_a!=dir_d)&&
	   (sp->psp[client_no].hp)){
		sp->damage=sp->otf[sp->attack_client].butsuri_otf_damage[client_no]*2;
		if((sp->scw[dir_d].konoyubitomare_flag)&&(sp->psp[sp->scw[dir_d].konoyubitomare_client].hp)){
			sp->defence_client=sp->scw[dir_d].konoyubitomare_client;
		}
		else{
			sp->defence_client=client_no;
		}
		if(sp->psp[sp->defence_client].hp==0){
			sp->defence_client=ST_ServerDirClientGet(bw,sp,sp->attack_client);
			if(sp->psp[sp->defence_client].hp==0){
				sp->next_server_seq_no=SERVER_WAZA_NO_BUFFER_SET_NO;
				SkillSequenceJump(sp,ARC_SUB_SEQ,SUB_SEQ_NO_DEFENCE);
			}
		}
		ST_ServerPressurePPDecCheck(sp,sp->attack_client,sp->defence_client);
	}
	else{
		//�����v���b�V���[�̉e�����󂯂Ȃ��悤�ɂ���
		sp->ostf[sp->attack_client].no_pressure_flag=1;
		sp->waza_status_flag|=WAZA_STATUS_FLAG_UMAKUKIMARAN;
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_MIRROR_CORT(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	dir_a,dir_d;
	int	client_no;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("MIRROR_CORT\n");
#endif

	client_no=sp->otf[sp->attack_client].tokusyu_otf_client;
	dir_a=BattleWorkMineEnemyCheck(bw,sp->attack_client);
	dir_d=BattleWorkMineEnemyCheck(bw,client_no);

	if((sp->otf[sp->attack_client].tokusyu_otf_damage[client_no])&&
	   (dir_a!=dir_d)&&
	   (sp->psp[client_no].hp)){
		sp->damage=sp->otf[sp->attack_client].tokusyu_otf_damage[client_no]*2;
		if((sp->scw[dir_d].konoyubitomare_flag)&&(sp->psp[sp->scw[dir_d].konoyubitomare_client].hp)){
			sp->defence_client=sp->scw[dir_d].konoyubitomare_client;
		}
		else{
			sp->defence_client=client_no;
		}
		if(sp->psp[sp->defence_client].hp==0){
			sp->defence_client=ST_ServerDirClientGet(bw,sp,sp->attack_client);
			if(sp->psp[sp->defence_client].hp==0){
				sp->next_server_seq_no=SERVER_WAZA_NO_BUFFER_SET_NO;
				SkillSequenceJump(sp,ARC_SUB_SEQ,SUB_SEQ_NO_DEFENCE);
			}
		}
		ST_ServerPressurePPDecCheck(sp,sp->attack_client,sp->defence_client);
	}
	else{
		//�����v���b�V���[�̉e�����󂯂Ȃ��悤�ɂ���
		sp->ostf[sp->attack_client].no_pressure_flag=1;
		sp->waza_status_flag|=WAZA_STATUS_FLAG_UMAKUKIMARAN;
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_ENCORE(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	adrs;
	int	waza_pos;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("ENCORE adrs:%d\n",adrs);
#endif

	waza_pos=ST_ServerWazaPosGet(&sp->psp[sp->defence_client],sp->waza_no_old[sp->defence_client]);

	//�A���R�[���ł��Ȃ��Z�̎w��
	if(ST_OumuEncoreNGCheck(sp,sp->waza_no_old[sp->defence_client])==FALSE){
		waza_pos=WAZA_TEMOTI_MAX;
	}

	if((sp->psp[sp->defence_client].wkw.encore_wazano==0)&&
	   (waza_pos!=WAZA_TEMOTI_MAX)&&
	   (sp->psp[sp->defence_client].pp[waza_pos])&&
	   (sp->waza_no_old[sp->defence_client])){
		sp->waza_work=sp->waza_no_old[sp->defence_client];
		sp->psp[sp->defence_client].wkw.encore_wazano=sp->waza_work;
		sp->psp[sp->defence_client].wkw.encore_wazapos=waza_pos;
		sp->psp[sp->defence_client].wkw.encore_count=gf_rand()%5+3;		//�Q�`�U�i���ۂ́A�R�`�V�j
	}
	else{
		sp->waza_status_flag|=WAZA_STATUS_FLAG_UMAKUKIMARAN;
		SkillSeqInc(sp,adrs);
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_TEXTURE2(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	i,j;
	int	adrs;
	int	wazatype;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("TEXTURE2 adrs:%d\n",adrs);
#endif

	//�����}���`�^�C�v�͎��g�̃^�C�v��ω�������Z�́A���s�ɂ���
	if(ST_ServerTokuseiGet(sp,sp->attack_client)==TOKUSYU_MARUTITAIPU){
		SkillSeqInc(sp,adrs);
		return FALSE;
	}

	if((sp->waza_no_texture2[sp->attack_client])&&(sp->waza_no_texture2_client[sp->attack_client]!=NONE_CLIENT_NO)){
		if((ST_TameWazaCheck(sp,sp->waza_no_texture2[sp->attack_client]))&&
		   (sp->psp[sp->waza_no_texture2_client[sp->attack_client]].condition2&CONDITION2_KEEP)){
			SkillSeqInc(sp,adrs);
			return FALSE;
		}
		else{
			{
				u8	type_w,type_p,value;

				wazatype=sp->waza_no_texture2_type[sp->attack_client];
				//�ꉞ�A1000��񂵂ă^�C�v���擾���Ă݂�
				for(i=0;i<1000;i++){
					ST_ServerTypeCheckTableParaGet(0xffff,&type_w,&type_p,&value);
					if((type_w==wazatype)&&(value<=5)&&
					   (ST_ServerPokemonServerParamGet(sp,sp->attack_client,ID_PSP_type1,NULL)!=type_p)&&
					   (ST_ServerPokemonServerParamGet(sp,sp->attack_client,ID_PSP_type2,NULL)!=type_p)){
					   sp->psp[sp->attack_client].type1=type_p;
					   sp->psp[sp->attack_client].type2=type_p;
					   sp->msg_work=type_p;
					   return FALSE;
					}
				}
				//1000��񂵂Ă��_���Ȏ��̓e�[�u�����ォ��Ȃ߂Ĉ�v������̂�T��
				i=0;
				while(ST_ServerTypeCheckTableParaGet(i,&type_w,&type_p,&value)==TRUE){
					if((type_w==wazatype)&&(value<=5)&&
					   (ST_ServerPokemonServerParamGet(sp,sp->attack_client,ID_PSP_type1,NULL)!=type_p)&&
					   (ST_ServerPokemonServerParamGet(sp,sp->attack_client,ID_PSP_type2,NULL)!=type_p)){
					   sp->psp[sp->attack_client].type1=type_p;
					   sp->psp[sp->attack_client].type2=type_p;
					   sp->msg_work=type_p;
					   return FALSE;
					}
					i++;
				}
			}
		}
	}
	SkillSeqInc(sp,adrs);

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_SKETCH(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	pos;
	int	set_pos=-1;
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("SKETCH adrs:%d\n",adrs);
#endif

	if((sp->psp[sp->attack_client].condition2&CONDITION2_HENSHIN)||
	   (sp->waza_no_sketch[sp->defence_client]==WAZANO_WARUAGAKI)||
	   (sp->waza_no_sketch[sp->defence_client]==WAZANO_SUKETTI)||
	   (sp->waza_no_sketch[sp->defence_client]==WAZANO_OSYABERI)||
	   (sp->waza_no_sketch[sp->defence_client]==0)){
		SkillSeqInc(sp,adrs);
	}
	else{
		for(pos=0;pos<WAZA_TEMOTI_MAX;pos++){
			if((sp->psp[sp->attack_client].waza[pos]!=WAZANO_SUKETTI)&&
			   (sp->psp[sp->attack_client].waza[pos]==sp->waza_no_sketch[sp->defence_client])){
				break;
			}
			if((sp->psp[sp->attack_client].waza[pos]==WAZANO_SUKETTI)&&(set_pos==-1)){
				set_pos=pos;
			}
		}
		if(pos==WAZA_TEMOTI_MAX){
			sp->psp[sp->attack_client].waza[set_pos]=sp->waza_no_sketch[sp->defence_client];
//			sp->psp[sp->attack_client].pp[set_pos]=WT_WazaDataParaGet(sp->waza_no_sketch[sp->defence_client],ID_WTD_pp);
			sp->psp[sp->attack_client].pp[set_pos]=sp->AIWT.wtd[sp->waza_no_sketch[sp->defence_client]].pp;
			SCIO_PSPtoPPCopy(bw,sp,sp->attack_client);
			sp->waza_work=sp->waza_no_sketch[sp->defence_client];
			//�Ƃ��Ă������R�s�[������A�J�E���^�����Z�b�g
			if(sp->waza_work==WAZANO_TOTTEOKI){
				sp->psp[sp->attack_client].wkw.totteoki_count=0;
			}
		}
		else{
			SkillSeqInc(sp,adrs);
		}
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_NEGOTO(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	pos;
	int	wazabit;
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("NEGOTO adrs:%d\n",adrs);
#endif

	wazabit=0;

	for(pos=0;pos<WAZA_TEMOTI_MAX;pos++){
		if((ST_RendouWazaCheck(sp->psp[sp->attack_client].waza[pos]))||
		   (sp->psp[sp->attack_client].waza[pos]==WAZANO_KIAIPANTI)||
		   (sp->psp[sp->attack_client].waza[pos]==WAZANO_SAWAGU)||
		   (sp->psp[sp->attack_client].waza[pos]==WAZANO_OSYABERI)||
		   (ST_TameWazaCheck(sp,sp->psp[sp->attack_client].waza[pos]))){
			wazabit|=No2Bit(pos);
		}
	}

	wazabit=ST_ServerWaruagakiCheck(bw,sp,sp->attack_client,wazabit,(SSWC_PP_NONE^SSWC_ALL));

	if(wazabit==0x0f){
		SkillSeqInc(sp,adrs);
	}
	else{
		do{
			pos=gf_rand()%4;
		}while((wazabit&No2Bit(pos)));
		sp->waza_work=sp->psp[sp->attack_client].waza[pos];
	}
	return FALSE;
}

//============================================================================================
/**
 *	�����΂��U���̓e�[�u��
 */
//============================================================================================

enum{
	HP_DOT=0,
	POWER
};

static	const	u8	JitabataPowerTable[][2]={
	{ 1,200},
	{ 5,150},
	{12,100},
	{21, 80},
	{42, 40},
	{64, 20},
};

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_JITABATA(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	i;
	int	dot;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("JITABATA\n");
#endif

	dot=GetNumDotto(sp->psp[sp->attack_client].hp,sp->psp[sp->attack_client].hpmax,64);
	for(i=0;i<NELEMS(JitabataPowerTable);i++){
		if(dot<=JitabataPowerTable[i][HP_DOT]){
			break;
		}
	}
	sp->damage_power=JitabataPowerTable[i][POWER];

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_URAMI(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	adrs;
	int	waza_pos;
	int	pp_dec;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("URAMI adrs:%d\n",adrs);
#endif

	if(sp->waza_no_old[sp->defence_client]){
		waza_pos=ST_ServerWazaPosGet(&sp->psp[sp->defence_client],sp->waza_no_old[sp->defence_client]);
		if((waza_pos==WAZA_TEMOTI_MAX)||
		   (sp->psp[sp->defence_client].pp[waza_pos]==0)){
			SkillSeqInc(sp,adrs);
		}
		else{
			pp_dec=4;
			if(sp->psp[sp->defence_client].pp[waza_pos]<pp_dec){
				pp_dec=sp->psp[sp->defence_client].pp[waza_pos];
			}
			sp->waza_work=sp->waza_no_old[sp->defence_client];
			sp->msg_work=pp_dec;
			sp->psp[sp->defence_client].pp[waza_pos]-=pp_dec;
			ST_PSPtoPPCopy(bw,sp,sp->defence_client);
//���ߌn�́A�Z���o�����u�Ԃ�PP�����炵�Ă���̂ŁA�Z���p�����邱�ƂɎd�l�ύX�i�A�h�o���X�łƂ͈Ⴂ�܂��jby soga 2006.04.29
//			//PP���O�ɂȂ�����A���ߌn�t���O�𗎂Ƃ�
//			if(sp->psp[sp->defence_client].pp[waza_pos]==0){
//				ST_ServerKeepOff(bw,sp,sp->defence_client);
//			}
		}
	}
	else{
		SkillSeqInc(sp,adrs);
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_IYASINOSUZU(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	u32	fight_type;
	int	client_no;

	fight_type=BattleWorkFightTypeGet(bw);

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("IYASINOSUZU\n");
#endif

	//�ڂ�����Ŗh�����t���O�ɗ��p
	sp->calc_work=0;

	if(sp->waza_no_now==WAZANO_IYASINOSUZU){
		sp->waza_work=sp->waza_no_now;
		//���₵�̂����́A�h���`�F�b�N������
		if(ST_ServerTokuseiGet(sp,sp->attack_client)!=TOKUSYU_BOUON){
			sp->psp[sp->attack_client].condition=0;
			sp->psp[sp->attack_client].condition2&=CONDITION2_AKUMU_OFF;
		}
		else{
			sp->calc_work|=(BOUON_SIDE_1|NOSET_SIDE_1);
		}
			
		if(fight_type&FIGHT_TYPE_2vs2){
			client_no=SideClientNoGet(bw,sp,SIDE_ATTACK_PAIR);
			if((sp->no_reshuffle_client&No2Bit(client_no))==0){
				if(ST_ServerKatayaburiTokuseiCheck(sp,sp->attack_client,client_no,TOKUSYU_BOUON)==FALSE){
					sp->psp[client_no].condition=0;
					sp->psp[client_no].condition2&=CONDITION2_AKUMU_OFF;
				}
				else{
					sp->client_work=client_no;
					sp->calc_work|=(BOUON_SIDE_2|NOSET_SIDE_2);
				}
			}
		}
		else{
			sp->calc_work|=NOSET_SIDE_2;
		}
	}
	else{
		//�A���}�Z���s�[�͑S�����Ȃ���
		sp->psp[sp->attack_client].condition=0;
		sp->psp[sp->attack_client].condition2&=CONDITION2_AKUMU_OFF;
		if(fight_type&FIGHT_TYPE_2vs2){
			client_no=SideClientNoGet(bw,sp,SIDE_ATTACK_PAIR);
			if((sp->no_reshuffle_client&No2Bit(client_no))==0){
				sp->psp[client_no].condition=0;
				sp->psp[client_no].condition2&=CONDITION2_AKUMU_OFF;
			}
		}
		else{
			sp->calc_work|=NOSET_SIDE_2;
		}
	}

	SCIO_PokemonRefreshSet(bw,sp,sp->attack_client,sp->waza_no_now);

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_DOROBOU(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	adrs1;
	int	adrs2;
	u32	fight_type;
	int	dir;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//adrs1�����[�h
	adrs1=SkillSeqDataRead(sp);

	//adrs2�����[�h
	adrs2=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("DOROBOU adrs1:%d adrs2:%d\n",adrs1,adrs2);
#endif

	fight_type=BattleWorkFightTypeGet(bw);
	dir=BattleWorkMineEnemyCheck(bw,sp->attack_client);

	//�G������̂ǂ�ڂ��ŁA���s����FightType���`�F�b�N
	if((BattleWorkMineEnemyCheck(bw,sp->attack_client))&&((fight_type&FIGHT_TYPE_DOROBOU)==0)){
		SkillSeqInc(sp,adrs1);
	}
	//�@�����Ƃ���Ă��鎞�́A���s����
	else if(sp->scw[dir].hatakiotosu_item&No2Bit(sp->sel_mons_no[sp->attack_client])){
		SkillSeqInc(sp,adrs1);
	}
	//�ǂ��炩���A�����}���`�^�C�v�Ȃ�A���s����
	else if((ST_ServerTokuseiGet(sp,sp->attack_client)==TOKUSYU_MARUTITAIPU)||
			(ST_ServerTokuseiGet(sp,sp->defence_client)==TOKUSYU_MARUTITAIPU)){
		SkillSeqInc(sp,adrs1);
	}
	else{
		if((sp->psp[sp->defence_client].item)&&
		   (ST_ServerKatayaburiTokuseiCheck(sp,sp->attack_client,sp->defence_client,TOKUSYU_NENTYAKU)==TRUE)){
			SkillSeqInc(sp,adrs2);
		}
		else if((sp->psp[sp->attack_client].item)||
				(ST_ServerDorobouItemCheck(bw,sp,sp->defence_client)==FALSE)){
			SkillSeqInc(sp,adrs1);
		}
	}

	return FALSE;
}

//============================================================================================
/**
 * WS_GUARD_SUCCESS_CHECK�p�m���e�[�u��
 */
//============================================================================================
static	const	u16	GSC_Table[]={
	0xffff/1,
	0xffff/2,
	0xffff/4,
	0xffff/8,
};

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_GUARD_SUCCESS_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	i;
	int	flag;
	int	client_set_max;
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("GUARD_SUCCESS_CHECK adrs:%d\n",adrs);
#endif
	
	if((sp->waza_no_mamoru[sp->attack_client]!=WAZANO_MAMORU)&&
	   (sp->waza_no_mamoru[sp->attack_client]!=WAZANO_MIKIRI)&&
	   (sp->waza_no_mamoru[sp->attack_client]!=WAZANO_KORAERU)){
		sp->psp[sp->attack_client].wkw.success_count=0;
	}

	client_set_max=0;
	for(i=0;i<BattleWorkClientSetMaxGet(bw);i++){
		if(sp->psp[i].hp){
			client_set_max++;
		}
	}

	//�������Ō�Ȃ玸�s�ɂ���i���Ă��Ӗ����Ȃ��̂Łj
	if(sp->agi_cnt==client_set_max-1){
		flag=0;
	}
	else{
		flag=1;
	}

	if((GSC_Table[sp->psp[sp->attack_client].wkw.success_count]>=gf_rand())&&(flag)){
		//�܂���A�݂���
//		if(WT_WazaDataParaGet(sp->waza_no_now,ID_WTD_battleeffect)==111){
		if(sp->AIWT.wtd[sp->waza_no_now].battleeffect==111){
			sp->otf[sp->attack_client].mamoru_flag=1;
			sp->mp.msg_id=MamoruMineMsg;
		}
		//���炦��
//		if(WT_WazaDataParaGet(sp->waza_no_now,ID_WTD_battleeffect)==116){
		if(sp->AIWT.wtd[sp->waza_no_now].battleeffect==116){
			sp->otf[sp->attack_client].koraeru_flag=1;
			sp->mp.msg_id=KoraeruMineMsg;
		}
		sp->mp.msg_tag=TAG_NICK;
		sp->mp.msg_para[0]=ST_ServerTagNickParaMake(sp,sp->attack_client);
		if(sp->psp[sp->attack_client].wkw.success_count<NELEMS(GSC_Table)-1){
			sp->psp[sp->attack_client].wkw.success_count++;
		}
	}
	else{
		sp->psp[sp->attack_client].wkw.success_count=0;
		SkillSeqInc(sp,adrs);
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_MIGAWARI(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	adrs;
	int	hpmax;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("MIGAWARI adrs:%d\n",adrs);
#endif

	hpmax=ST_ServerDamageDiv(sp->psp[sp->attack_client].hpmax,4);

	if(sp->psp[sp->attack_client].hp<=hpmax){
		SkillSeqInc(sp,adrs);
	}
	else{
		sp->hp_calc_work=hpmax*-1;
//		sp->psp[sp->attack_client].condition2|=CONDITION2_MIGAWARI;
		sp->psp[sp->attack_client].wkw.migawari_hp=hpmax;
		//�O��Ƃ̐������̂��߁A�g������o��������ߋZ�n����J��
		sp->psp[sp->attack_client].condition2&=CONDITION2_SHIME_OFF;
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_HUKITOBASI(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	adrs;
	u32	fight_type;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("HUKITOBASI adrs:%d\n",adrs);
#endif

	fight_type=BattleWorkFightTypeGet(bw);

	if(fight_type&FIGHT_TYPE_TRAINER){
		{
			POKEPARTY		*poke_p;
			POKEMON_PARAM	*pp;
			int				poke_count;
			int				cnt=0,cntmax,i,start,end,rnd_max;
			int				selmons1,selmons2;

			poke_p=BattleWorkPokePartyGet(bw,sp->defence_client);
			poke_count=BattleWorkPokeCountGet(bw,sp->defence_client);

			//�}���`&�^�b�O�o�g�����葤
			if((fight_type&FIGHT_TYPE_MULTI)||
			  ((fight_type&FIGHT_TYPE_TAG)&&(BattleWorkMineEnemyCheck(bw,sp->defence_client)))){
				start=0;
				end=poke_count;
				rnd_max=poke_count;
				cntmax=1;
				selmons1=sp->sel_mons_no[sp->defence_client];
				selmons2=sp->sel_mons_no[sp->defence_client];
			}
			//�_�u��
			else if(fight_type&FIGHT_TYPE_2vs2){
				start=0;
				end=poke_count;
				rnd_max=poke_count;
				cntmax=2;
				selmons1=sp->sel_mons_no[sp->defence_client];
				selmons2=sp->sel_mons_no[BattleWorkPartnerClientNoGet(bw,sp->defence_client)];
			}
			//�V���O��
			else{
				start=0;
				end=poke_count;
				rnd_max=poke_count;
				cntmax=1;
				selmons1=sp->sel_mons_no[sp->defence_client];
				selmons2=sp->sel_mons_no[sp->defence_client];
			}

			for(i=start;i<end;i++){
				pp=PokeParty_GetMemberPointer(poke_p,i);
				if((PokeParaGet(pp,ID_PARA_monsno,NULL))&&
				   (PokeParaGet(pp,ID_PARA_tamago_flag,NULL)==0)&&
				   (PokeParaGet(pp,ID_PARA_hp,NULL))){
					cnt++;
				}
			}
			if(cnt<=cntmax){
				SkillSeqInc(sp,adrs);
			}
			else{
				if(ST_ServerHukitobasiCheck(sp)){
					do{
						do{
							i=gf_rand()%rnd_max;
							i+=start;
						}while((i==selmons1)||(i==selmons2));
						pp=PokeParty_GetMemberPointer(poke_p,i);
					}while((PokeParaGet(pp,ID_PARA_monsno,NULL)==0)||
						   (PokeParaGet(pp,ID_PARA_tamago_flag,NULL)==1)||
						   (PokeParaGet(pp,ID_PARA_hp,NULL)==0));
					sp->reshuffle_sel_mons_no[sp->defence_client]=i;
				}
				else{
					SkillSeqInc(sp,adrs);
				}
			}
		}
	}
	else{
		if(ST_ServerHukitobasiCheck(sp)==FALSE){
			SkillSeqInc(sp,adrs);
		}
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_HENSIN(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	i;
	u8	*src,*dest;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("HENSIN\n");
#endif

	sp->psp[sp->attack_client].condition2|=CONDITION2_HENSHIN;
	sp->psp[sp->attack_client].wkw.kanashibari_wazano=0;
	sp->psp[sp->attack_client].wkw.kanashibari_count=0;
	sp->psp[sp->attack_client].wkw.henshin_rnd=sp->psp[sp->defence_client].personal_rnd;
	sp->psp[sp->attack_client].wkw.henshin_sex=sp->psp[sp->defence_client].sex;
	sp->psp[sp->attack_client].wkw.monomane_bit=0;
	sp->psp[sp->attack_client].wkw.totteoki_count=0;

	src=(u8 *)&sp->psp[sp->attack_client];
	dest=(u8 *)&sp->psp[sp->defence_client];

	for(i=0;i<XtOffset(POKEMON_SERVER_PARAM *,speabino)+1;i++){
		src[i]=dest[i];
	}

	sp->psp[sp->attack_client].appear_check_flag=0;
	sp->psp[sp->attack_client].ikaku_flag=0;
	sp->psp[sp->attack_client].trace_flag=0;
	sp->psp[sp->attack_client].download_flag=0;
	sp->psp[sp->attack_client].kikenyochi_flag=0;
	sp->psp[sp->attack_client].yochimu_flag=0;
	sp->psp[sp->attack_client].omitooshi_flag=0;
	sp->psp[sp->attack_client].katayaburi_flag=0;
	sp->psp[sp->attack_client].pressure_flag=0;
	//���̃^�[���ɂȂ܂���悤�ɂ���
	sp->psp[sp->attack_client].wkw.namake_bit=sp->total_turn&1;
	//�X���[�X�^�[�g�̃J�E���^�����Z�b�g
	sp->psp[sp->attack_client].wkw.slow_start_count=sp->total_turn+1;
	sp->psp[sp->attack_client].slow_start_flag=0;
	sp->psp[sp->attack_client].slow_start_end_flag=0;
	
	//�Z��PP�͂T�ɂ���i�f�t�H���g���T�����̂��̂́A���̂܂܂̒l������j
	for(i=0;i<WAZA_TEMOTI_MAX;i++){
//		if(WT_WazaDataParaGet(sp->psp[sp->attack_client].waza[i],ID_WTD_pp)<5){
		if(sp->AIWT.wtd[sp->psp[sp->attack_client].waza[i]].pp<5){
//			sp->psp[sp->attack_client].pp[i]=WT_WazaDataParaGet(sp->psp[sp->attack_client].waza[i],ID_WTD_pp);
			sp->psp[sp->attack_client].pp[i]=sp->AIWT.wtd[sp->psp[sp->attack_client].waza[i]].pp;
		}
		else{
			sp->psp[sp->attack_client].pp[i]=5;
		}
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_MAKIBISI(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	adrs;
	int	dir;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("MAKIBISI adrs:%d\n",adrs);
#endif

	dir=BattleWorkMineEnemyCheck(bw,sp->attack_client)^1;

	if(sp->scw[dir].makibisi_count==3){
		sp->ostf[sp->attack_client].no_pressure_flag=1;
		SkillSeqInc(sp,adrs);
	}
	else{
		sp->side_condition[dir]|=SIDE_CONDITION_MAKIBISHI;
		sp->scw[dir].makibisi_count++;
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_MAKIBISI_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	side;
	int	adrs;
	int	client_no;
	int	dir;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//side�����[�h
	side=SkillSeqDataRead(sp);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("MAKIBISI_CHECK side:%d adrs:%d\n",side,adrs);
#endif

	client_no=SideClientNoGet(bw,sp,side);
	dir=BattleWorkMineEnemyCheck(bw,client_no);

	if((sp->scw[dir].makibisi_count)&&(sp->psp[client_no].hp)){
		sp->hp_calc_work=(5-sp->scw[dir].makibisi_count)*2;
		sp->hp_calc_work=ST_ServerDamageDiv(sp->psp[client_no].hpmax*-1,sp->hp_calc_work);
	}
	else{
		SkillSeqInc(sp,adrs);
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_HOROBINOUTA(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	adrs;
	int	client_no;
	int	count;
	int	client_set_max;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("HOROBINOUTA adrs:%d\n",adrs);
#endif

	client_set_max=BattleWorkClientSetMaxGet(bw);
	sp->calc_work=client_set_max;
	count=0;

	for(client_no=0;client_no<client_set_max;client_no++){
		if((sp->psp[client_no].waza_kouka&WAZAKOUKA_HOROBINOUTA)||
		   (sp->psp[client_no].hp==0)||
		   (ST_ServerKatayaburiTokuseiCheck(sp,sp->attack_client,client_no,TOKUSYU_BOUON)==TRUE)){
			count++;
		}
		else{
			sp->psp[client_no].waza_kouka|=WAZAKOUKA_HOROBINOUTA;
			sp->psp[client_no].wkw.horobinouta_count=3;
		}
	}
	if(count==client_set_max){
		SkillSeqInc(sp,adrs);
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_CLIENT_NO_GET_AGI(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	para;
	u32	*data;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//para1�����[�h
	para=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("CLIENT_NO_GET_AGI para:%d\n",para);
#endif

	data=WS_SrcPointerGet(bw,sp,para);

	data[0]=sp->psp_agi_work[sp->client_no_agi];

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_CLIENT_SET_MAX_LOOP(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	para;
	int	adrs;
	u32	*data;
	int	client_set_max;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//para�����[�h
	para=SkillSeqDataRead(sp);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("CLIENT_SET_MAX_LOOP para:%d adrs:%d\n",para,adrs);
#endif

	data=WS_SrcPointerGet(bw,sp,para);
	client_set_max=BattleWorkClientSetMaxGet(bw);

	if(data[0]<client_set_max){
		SkillSeqInc(sp,adrs);
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_TENKOU_DAMAGE(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	side;
	int	client_no;
	int	type1;
	int	type2;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//side�����[�h
	side=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("TENKOU_DAMAGE side:%d\n",side);
#endif

	client_no=SideClientNoGet(bw,sp,side);

	sp->temp_work=0;
	sp->hp_calc_work=0;

	type1=ST_ServerPokemonServerParamGet(sp,client_no,ID_PSP_type1,NULL);
	type2=ST_ServerPokemonServerParamGet(sp,client_no,ID_PSP_type2,NULL);

	if((ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ALL_HP,0,TOKUSYU_NOOTENKI)==0)&&
	   (ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ALL_HP,0,TOKUSYU_EAROKKU)==0)){
		//���Ȃ��炵�`�F�b�N
		if(sp->field_condition&FIELD_CONDITION_SUNAARASHI_ALL){
			if((type1!=IWA_TYPE)&&
			   (type2!=IWA_TYPE)&&
			   (type1!=METAL_TYPE)&&
			   (type2!=METAL_TYPE)&&
			   (type1!=JIMEN_TYPE)&&
			   (type2!=JIMEN_TYPE)&&
			   (sp->psp[client_no].hp)&&
			   (ST_ServerTokuseiGet(sp,client_no)!=TOKUSYU_SUNAGAKURE)&&
			  ((sp->psp[client_no].waza_kouka&(WAZAKOUKA_ANAWOHORU|WAZAKOUKA_DAIBINGU))==0)){
				sp->waza_work=WAZANO_SUNAARASI;
				sp->hp_calc_work=ST_ServerDamageDiv(sp->psp[client_no].hpmax*-1,16);
			}
		}
		//�ɂق�΂�`�F�b�N
		if(sp->field_condition&FIELD_CONDITION_HARE_ALL){
			if((sp->psp[client_no].hp)&&
			  ((sp->psp[client_no].waza_kouka&(WAZAKOUKA_ANAWOHORU|WAZAKOUKA_DAIBINGU))==0)){
				//�������񂻂��͂��A�T���p���[�́A�͂�̎��AHPMAX��1/8�_���[�W
				if((ST_ServerTokuseiGet(sp,client_no)==TOKUSYU_KANSOUHADA)||
				   (ST_ServerTokuseiGet(sp,client_no)==TOKUSYU_SANPAWAA)){
					sp->hp_calc_work=ST_ServerDamageDiv(sp->psp[client_no].hpmax*-1,8);
				}
				if(ST_ServerTokuseiGet(sp,client_no)==TOKUSYU_SANPAWAA){
					sp->temp_work=TENKOU_SUNPOWER;
				}
			}
		}
		//�����`�F�b�N
		if(sp->field_condition&FIELD_CONDITION_ARARE_ALL){
			if((sp->psp[client_no].hp)&&
			  ((sp->psp[client_no].waza_kouka&(WAZAKOUKA_ANAWOHORU|WAZAKOUKA_DAIBINGU))==0)){
				//�����A�C�X�{�f�B�́A�����̎��AHPMAX��1/16��
				if(ST_ServerTokuseiGet(sp,client_no)==TOKUSYU_AISUBODHI){
					if(sp->psp[client_no].hp<sp->psp[client_no].hpmax){
						sp->hp_calc_work=ST_ServerDamageDiv(sp->psp[client_no].hpmax,16);
					}
				}
				else if((type1!=KOORI_TYPE)&&
						(type2!=KOORI_TYPE)&&
						(ST_ServerTokuseiGet(sp,client_no)!=TOKUSYU_YUKIGAKURE)){
					sp->waza_work=WAZANO_ARARE;
					sp->hp_calc_work=ST_ServerDamageDiv(sp->psp[client_no].hpmax*-1,16);
				}
			}
		}
		//���܂����`�F�b�N
		if(sp->field_condition&FIELD_CONDITION_AME_ALL){
			if((sp->psp[client_no].hp)&&
			   (sp->psp[client_no].hp<sp->psp[client_no].hpmax)&&
			   (ST_ServerTokuseiGet(sp,client_no)==TOKUSYU_AMEUKEZARA)){
				sp->hp_calc_work=ST_ServerDamageDiv(sp->psp[client_no].hpmax,16);
			}
			if((sp->psp[client_no].hp)&&
			   (sp->psp[client_no].hp<sp->psp[client_no].hpmax)&&
			   (ST_ServerTokuseiGet(sp,client_no)==TOKUSYU_KANSOUHADA)){
				sp->hp_calc_work=ST_ServerDamageDiv(sp->psp[client_no].hpmax,8);
			}
			if((sp->psp[client_no].hp)&&
			   (sp->psp[client_no].condition&CONDITION_BAD)&&
			   (ST_ServerTokuseiGet(sp,client_no)==TOKUSYU_URUOIBODHI)){
				if(sp->psp[client_no].condition&CONDITION_NEMURI){
					sp->msg_work=MSG_COND_NEMURI;
				}
				else if(sp->psp[client_no].condition&CONDITION_DOKUALL){
					sp->msg_work=MSG_COND_DOKU;
				}
				else if(sp->psp[client_no].condition&CONDITION_YAKEDO){
					sp->msg_work=MSG_COND_YAKEDO;
				}
				else if(sp->psp[client_no].condition&CONDITION_MAHI){
					sp->msg_work=MSG_COND_MAHI;
				}
				else{
					sp->msg_work=MSG_COND_KOORI;
				}
				sp->temp_work=TENKOU_URUOIBODY;
			}
		}
	}
	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_KOROGARU(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	i,j;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("KOROGARU\n");
#endif

	//���g���m�[������p���[�N�ɑ��
	sp->ostf[sp->attack_client].korogaru_count=sp->psp[sp->attack_client].wkw.korogaru_count;

	if((sp->psp[sp->attack_client].condition2&CONDITION2_KEEP)==0){
		ST_ServerKeepOn(bw,sp,sp->attack_client);
		sp->psp[sp->attack_client].wkw.korogaru_count=5;
	}

	if(--sp->psp[sp->attack_client].wkw.korogaru_count==0){
		ST_ServerKeepOff(bw,sp,sp->attack_client);
	}

//	sp->damage_power=WT_WazaDataParaGet(sp->waza_no_now,ID_WTD_damage);
	sp->damage_power=sp->AIWT.wtd[sp->waza_no_now].damage;

	j=5-sp->psp[sp->attack_client].wkw.korogaru_count;

	for(i=1;i<j;i++){
		sp->damage_power*=2;
	}

	if(sp->psp[sp->attack_client].condition2&CONDITION2_MARUKUNARU){
		sp->damage_power*=2;
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_RENZOKUGIRI(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	i;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("RENZOKUGIRI\n");
#endif

	if(sp->psp[sp->attack_client].wkw.renzokugiri_count<5){
		sp->psp[sp->attack_client].wkw.renzokugiri_count++;
	}

//	sp->damage_power=WT_WazaDataParaGet(sp->waza_no_now,ID_WTD_damage);
	sp->damage_power=sp->AIWT.wtd[sp->waza_no_now].damage;

	for(i=1;i<sp->psp[sp->attack_client].wkw.renzokugiri_count;i++){
		sp->damage_power*=2;
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_MEROMERO(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("MEROMERO adrs:%d\n",adrs);
#endif

	if((sp->psp[sp->client_work].sex==sp->psp[sp->tsuika_client].sex)||
	   (sp->psp[sp->tsuika_client].condition2&CONDITION2_MEROMERO)||
	   (sp->psp[sp->client_work].sex==PARA_UNK)||
	   (sp->psp[sp->tsuika_client].sex==PARA_UNK)){
		SkillSeqInc(sp,adrs);
	}
	else{
		sp->psp[sp->tsuika_client].condition2|=No2Bit(sp->client_work)<<MEROMERO_SHIFT;
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_SHINPI(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	adrs;
	int	dir;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("SHINPI adrs:%d\n",adrs);
#endif

	dir=BattleWorkMineEnemyCheck(bw,sp->attack_client);

	if(sp->side_condition[dir]&SIDE_CONDITION_SHINPI){
		SkillSeqInc(sp,adrs);
		sp->waza_status_flag|=WAZA_STATUS_FLAG_UMAKUKIMARAN;
	}
	else{
		sp->side_condition[dir]|=SIDE_CONDITION_SHINPI;
		sp->scw[dir].shinpi_count=5;
		sp->scw[dir].shinpi_client=sp->attack_client;
		sp->mp.msg_tag=TAG_NONE_DIR;
		sp->mp.msg_para[0]=sp->attack_client;
		sp->mp.msg_id=ShinpiMineMsg;
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_PRESENT(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	adrs;
	int	present;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("PRESENT adrs:%d\n",adrs);
#endif

	present=gf_rand()&0xff;

	if(present<(255*40/100)){
		sp->damage_power=40;
	}
	else if(present<(255*70/100)){
		sp->damage_power=80;
	}
	else if(present<(255*80/100)){
		sp->damage_power=120;
	}
	else{
		sp->hp_calc_work=ST_ServerDamageDiv(sp->psp[sp->defence_client].hpmax,4);
		SkillSeqInc(sp,adrs);
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_MAGNITUDE(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("MAGNITUDE\n");
#endif

	if(sp->magnitude==0){
		sp->magnitude=gf_rand()%100;
		if(sp->magnitude<5){
			sp->damage_power=10;
			sp->magnitude=4;
		}
		else if(sp->magnitude<15){
			sp->damage_power=30;
			sp->magnitude=5;
		}
		else if(sp->magnitude<35){
			sp->damage_power=50;
			sp->magnitude=6;
		}
		else if(sp->magnitude<65){
			sp->damage_power=70;
			sp->magnitude=7;
		}
		else if(sp->magnitude<85){
			sp->damage_power=90;
			sp->magnitude=8;
		}
		else if(sp->magnitude<95){
			sp->damage_power=110;
			sp->magnitude=9;
		}
		else{
			sp->damage_power=150;
			sp->magnitude=10;
		}
	}

	sp->msg_work=sp->magnitude;

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_RESHUFFLE_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	side;
	int	flag;
	int	adrs;
	int	client_no;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);
	
	//side�����[�h
	side=SkillSeqDataRead(sp);

	//flag�����[�h
	flag=SkillSeqDataRead(sp);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("RESHUFFLE_CHECK side:%d flag:%d adrs:%d\n",side,flag,adrs);
#endif

	client_no=SideClientNoGet(bw,sp,side);

	if(ST_ServerReshuffleCheck(bw,sp,client_no)==FALSE){
		SkillSeqInc(sp,adrs);
	}
	else{
		if(flag==POKE_LIST_ON){
			sp->client_status[client_no]|=CLIENT_STATUS_POKE_RESHUFFLE;
		}
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_KOUSOKUSPIN(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	dir;

	dir=BattleWorkMineEnemyCheck(bw,sp->attack_client);

	//���ߌn�̋Z
	if(sp->psp[sp->attack_client].condition2&CONDITION2_SHIME){
		sp->psp[sp->attack_client].condition2&=CONDITION2_SHIME_OFF;
		sp->client_work=sp->psp[sp->attack_client].wkw.shime_client_no;
		sp->waza_work=sp->psp[sp->attack_client].wkw.shime_wazano;
		SkillSequenceGosub(sp,ARC_SUB_SEQ,SUB_SEQ_SHIME_ESCAPE);
		return FALSE;
	}
	//��ǂ肬�̂���
	if(sp->psp[sp->attack_client].waza_kouka&WAZAKOUKA_YADORARE){
		sp->psp[sp->attack_client].waza_kouka&=WAZAKOUKA_YADORARE_OFF;
		sp->psp[sp->attack_client].waza_kouka&=WAZAKOUKA_YADORIGI_OFF;
		sp->waza_work=WAZANO_YADORIGINOTANE;
		SkillSequenceGosub(sp,ARC_SUB_SEQ,SUB_SEQ_KOUSOKUSPIN_ESCAPE);
		return FALSE;
	}
	//�܂��т�
	if(sp->scw[dir].makibisi_count){
		sp->side_condition[dir]&=SIDE_CONDITION_MAKIBISHI_OFF;
		sp->scw[dir].makibisi_count=0;
		sp->waza_work=WAZANO_MAKIBISI;
		SkillSequenceGosub(sp,ARC_SUB_SEQ,SUB_SEQ_KOUSOKUSPIN_ESCAPE);
		return FALSE;
	}
	//�ǂ��т�
	if(sp->scw[dir].dokubisi_count){
		sp->side_condition[dir]&=SIDE_CONDITION_DOKUBISHI_OFF;
		sp->scw[dir].dokubisi_count=0;
		sp->waza_work=WAZANO_DOROBAKUDAN;
		SkillSequenceGosub(sp,ARC_SUB_SEQ,SUB_SEQ_KOUSOKUSPIN_ESCAPE);
		return FALSE;
	}
	//�X�e���X���b�N
	if(sp->side_condition[dir]&SIDE_CONDITION_STEALTHROCK){
		sp->side_condition[dir]&=SIDE_CONDITION_STEALTHROCK_OFF;
		sp->waza_work=WAZANO_SUTERUSUROKKU;
		SkillSequenceGosub(sp,ARC_SUB_SEQ,SUB_SEQ_KOUSOKUSPIN_ESCAPE);
		return FALSE;
	}

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);
	
#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("KOUSOKUSPIN\n");
#endif

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_WEATHER_KAIFUKU(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("WEATHER_KAIFUKU\n");
#endif

	//�V��ω����Ȃ����A�V�󖳌��ɂ�������̃|�P���������鎞�́AMAX�̔���
	if((sp->field_condition==0)||
	   (ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ALL_HP,0,TOKUSYU_NOOTENKI))||
	   (ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ALL_HP,0,TOKUSYU_EAROKKU))){
		sp->hp_calc_work=sp->psp[sp->attack_client].hpmax/2;
	}
	//����̎��́AMAX��2/3
	else if(sp->field_condition&FIELD_CONDITION_HARE_ALL){
		sp->hp_calc_work=ST_ServerDamageDiv(sp->psp[sp->attack_client].hpmax*20,30);
	}
	//����ȊO�̓V��́AMAX��1/4
	else{
		sp->hp_calc_work=ST_ServerDamageDiv(sp->psp[sp->attack_client].hpmax,4);
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_MEZAMERU_POWER(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("MEZAMERU_POWER\n");
#endif

	sp->damage_power=	((sp->psp[sp->attack_client].hp_rnd&2)		>>1)|
						((sp->psp[sp->attack_client].pow_rnd&2)		>>0)|
						((sp->psp[sp->attack_client].def_rnd&2)		<<1)|
						((sp->psp[sp->attack_client].agi_rnd&2)		<<2)|
						((sp->psp[sp->attack_client].spepow_rnd&2)	<<3)|
						((sp->psp[sp->attack_client].spedef_rnd&2)	<<4);
	sp->waza_type=		((sp->psp[sp->attack_client].hp_rnd&1)		>>0)|
						((sp->psp[sp->attack_client].pow_rnd&1)		<<1)|
						((sp->psp[sp->attack_client].def_rnd&1)		<<2)|
						((sp->psp[sp->attack_client].agi_rnd&1)		<<3)|
						((sp->psp[sp->attack_client].spepow_rnd&1)	<<4)|
						((sp->psp[sp->attack_client].spedef_rnd&1)	<<5);

	sp->damage_power=sp->damage_power*40/63+30;
	sp->waza_type=(sp->waza_type*15/63)+1;

	if(sp->waza_type>=HATE_TYPE){
		sp->waza_type++;
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_JIKOANJI(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	i;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("JIKOANJI\n");
#endif

	//�\�͌n�R�s�[
	for(i=COND_HP;i<COND_MAX;i++){
		sp->psp[sp->attack_client].abiritycnt[i]=sp->psp[sp->defence_client].abiritycnt[i];
	}
	//�N���e�B�J�����㏸���R�s�[
	sp->psp[sp->attack_client].condition2|=(sp->psp[sp->defence_client].condition2&CONDITION2_KIAIDAME);

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_MIRAIYOCHI(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	adrs;
	int	dir;
	int	damage;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);
	
	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("MIRAIYOCHI adrs:%d\n",adrs);
#endif

	if(sp->fcc.miraiyochi_count[sp->defence_client]==0){
		dir=BattleWorkMineEnemyCheck(bw,sp->defence_client);
		sp->side_condition[dir]|=SIDE_CONDITION_MIRAIYOCHI;
		sp->fcc.miraiyochi_count[sp->defence_client]=3;
		sp->fcc.miraiyochi_wazano[sp->defence_client]=sp->waza_no_now;
		sp->fcc.miraiyochi_client_no[sp->defence_client]=sp->attack_client;
		damage=ST_WazaDamageCalc(bw,sp,
								 sp->waza_no_now,
								 sp->side_condition[dir],
								 sp->field_condition,
								 0,0,sp->attack_client,sp->defence_client,1)*-1;
		sp->fcc.miraiyochi_damage[sp->defence_client]=ST_DamageLossCalc(sp,damage);
		if(sp->otf[sp->attack_client].tedasuke_flag){
			sp->fcc.miraiyochi_damage[sp->defence_client]=
			sp->fcc.miraiyochi_damage[sp->defence_client]*15/10;
		}
	}
	else{
		SkillSeqInc(sp,adrs);
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_HITCHECK(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	side_a;
	int	side_d;
	int	waza;
	int	adrs;
	int	attack;
	int	defence;
	int	waza_no;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//side_a�����[�h
	side_a=SkillSeqDataRead(sp);

	//side_d�����[�h
	side_d=SkillSeqDataRead(sp);

	//waza�����[�h
	waza=SkillSeqDataRead(sp);
	
	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("HITCHECK side_a:%d side_d:%d waza:%d adrs:%d\n",side_a,side_d,waza,adrs);
#endif

	attack=SideClientNoGet(bw,sp,side_a);
	defence=SideClientNoGet(bw,sp,side_d);
	waza_no=MessageParamWazaGet(sp,waza);

	ServerHitCheckAct(bw,sp,attack,defence,waza_no);

	if(sp->waza_status_flag&WAZA_STATUS_FLAG_HAZURE){
		SkillSeqInc(sp,adrs);
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_TELEPORT(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("TELEPORT adrs:%d\n",adrs);
#endif

	if(ST_EscapeNGCheck(bw,sp,sp->attack_client,NULL)){
		SkillSeqInc(sp,adrs);
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_HUKURODATAKI(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int				pos;
	int				poke_count;
	int				mons_no;
	int				form_no;
	int				level;
	POKEMON_PARAM	*pp;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("HUKURODATAKI\n");
#endif

	poke_count=BattleWorkPokeCountGet(bw,sp->attack_client);
	
	if(sp->renzoku_count_temp==0){
		sp->renzoku_count_temp=2;
		sp->loop_hit_check=RENZOKU_HIT_OFF;
		sp->hukurodataki_count=0;

		while(1){
			pp=BattleWorkPokemonParamGet(bw,sp->attack_client,sp->hukurodataki_count);
			if((sp->hukurodataki_count==sp->sel_mons_no[sp->attack_client])||
			  ((PokeParaGet(pp,ID_PARA_hp,NULL)!=0)&&
			   (PokeParaGet(pp,ID_PARA_monsno_egg,NULL)!=0)&&
			   (PokeParaGet(pp,ID_PARA_monsno_egg,NULL)!=MONSNO_TAMAGO)&&
			   (PokeParaGet(pp,ID_PARA_condition,NULL)==0))){
				break;
			}
			sp->hukurodataki_count++;
		}
	}

	pp=BattleWorkPokemonParamGet(bw,sp->attack_client,sp->hukurodataki_count);
	mons_no=PokeParaGet(pp,ID_PARA_monsno,NULL);
	form_no=PokeParaGet(pp,ID_PARA_form_no,NULL);
	level=PokeParaGet(pp,ID_PARA_level,NULL);
	sp->damage=PokeFormNoPersonalParaGet(mons_no,form_no,ID_PER_basic_pow);
	sp->damage*=sp->AIWT.wtd[sp->waza_no_now].damage;
	sp->damage*=((level*2/5)+2);

	sp->damage/=PokeFormNoPersonalParaGet(sp->psp[sp->defence_client].monsno,sp->psp[sp->defence_client].form_no,ID_PER_basic_def);
	sp->damage/=50;
	sp->damage+=2;
	sp->damage*=sp->critical;
	if(sp->otf[sp->attack_client].tedasuke_flag){
		sp->damage=sp->damage*15/10;
	}
	sp->damage=ST_DamageLossCalc(sp,sp->damage);
	sp->damage*=-1;

	sp->mp.msg_id=HukurodatakiMineMsg;
	sp->mp.msg_tag=TAG_NICK;
	sp->mp.msg_para[0]=(sp->attack_client|(sp->hukurodataki_count<<8));

	sp->hukurodataki_count++;
	sp->renzoku_count=2;

	if(sp->hukurodataki_count<poke_count){
		while(1){
			pp=BattleWorkPokemonParamGet(bw,sp->attack_client,sp->hukurodataki_count);
			if((sp->hukurodataki_count==sp->sel_mons_no[sp->attack_client])||
			  ((PokeParaGet(pp,ID_PARA_hp,NULL)!=0)&&
			   (PokeParaGet(pp,ID_PARA_monsno_egg,NULL)!=0)&&
			   (PokeParaGet(pp,ID_PARA_monsno_egg,NULL)!=MONSNO_TAMAGO)&&
			   (PokeParaGet(pp,ID_PARA_condition,NULL)==0))){
				break;
			}
			sp->hukurodataki_count++;
			if(sp->hukurodataki_count>=poke_count){
				sp->renzoku_count=1;
				break;
			}
		}
	}
	else{
		sp->renzoku_count=1;
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_KONOYUBITOMARE(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	dir;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("KONOYUBITOMARE\n");
#endif

	dir=BattleWorkMineEnemyCheck(bw,sp->attack_client);
	sp->scw[dir].konoyubitomare_flag=1;
	sp->scw[dir].konoyubitomare_client=sp->attack_client;

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_TEDASUKE(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	adrs;
	int	client_no;
	int	fight_type;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("TEDASUKE adrs:%d\n",adrs);
#endif

	fight_type=BattleWorkFightTypeGet(bw);
	
	if(fight_type&FIGHT_TYPE_2vs2){
		client_no=SideClientNoGet(bw,sp,SIDE_ATTACK_PAIR);
		if(((sp->no_reshuffle_client&No2Bit(client_no))==0)&&
			(sp->psp[client_no].hp)&&
			(sp->otf[sp->attack_client].tedasuke_flag==0)&&
			(sp->otf[client_no].tedasuke_flag==0)){
			sp->client_work=client_no;
			sp->otf[client_no].tedasuke_flag=1;
		}
		else{
			SkillSeqInc(sp,adrs);
		}
	}
	else{
		SkillSeqInc(sp,adrs);
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_TRICK(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	adrs1;
	int	adrs2;
	u32	fight_type;
	int	dir_a;
	int	dir_d;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//adrs1�����[�h
	adrs1=SkillSeqDataRead(sp);

	//adrs2�����[�h
	adrs2=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("TRICK adrs1:%d adrs2:%d\n",adrs1,adrs2);
#endif

	fight_type=BattleWorkFightTypeGet(bw);
	dir_a=BattleWorkMineEnemyCheck(bw,sp->attack_client);
	dir_d=BattleWorkMineEnemyCheck(bw,sp->defence_client);

	//�G������̃g���b�N�ŁA���s����FightType���`�F�b�N
	if((BattleWorkMineEnemyCheck(bw,sp->attack_client))&&((fight_type&FIGHT_TYPE_DOROBOU)==0)){
		SkillSeqInc(sp,adrs1);
	}
	//�@�����Ƃ���Ă��鎞�́A���s����
	else if((sp->scw[dir_a].hatakiotosu_item&No2Bit(sp->sel_mons_no[sp->attack_client]))||
			(sp->scw[dir_d].hatakiotosu_item&No2Bit(sp->sel_mons_no[sp->defence_client]))){
		SkillSeqInc(sp,adrs1);
	}
	else if(((sp->psp[sp->attack_client].item==0)&&(sp->psp[sp->defence_client].item==0))||
			 (ST_ServerTrickItemCheck(sp,sp->attack_client)==FALSE)||
			 (ST_ServerTrickItemCheck(sp,sp->defence_client)==FALSE)){
		SkillSeqInc(sp,adrs1);
	}
	else{
		if(ST_ServerKatayaburiTokuseiCheck(sp,sp->attack_client,sp->defence_client,TOKUSYU_NENTYAKU)==TRUE){
			SkillSeqInc(sp,adrs2);
		}
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_NEGAIGOTO(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	adrs;
	u32	fight_type;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("NEGAIGOTO adrs:%d\n",adrs);
#endif

	if(sp->fcc.negaigoto_count[sp->attack_client]){
		SkillSeqInc(sp,adrs);
	}
	else{
		sp->fcc.negaigoto_count[sp->attack_client]=2;
		sp->fcc.negaigoto_sel_mons[sp->attack_client]=sp->sel_mons_no[sp->attack_client];
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_NEKONOTE(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int				adrs;
	u16				waza_no[POKEMON_TEMOTI_MAX*WAZA_TEMOTI_MAX];
	u16				waza;
	int				i,j;
	int				poke_count;
	int				waza_count;
	POKEMON_PARAM	*pp;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("NEKONOTE adrs:%d\n",adrs);
#endif

	waza_count=0;
	poke_count=BattleWorkPokeCountGet(bw,sp->attack_client);

	for(i=0;i<poke_count;i++){
		if(i!=sp->sel_mons_no[sp->attack_client]){
			pp=BattleWorkPokemonParamGet(bw,sp->attack_client,i);
			if((PokeParaGet(pp,ID_PARA_monsno_egg,NULL)!=0)&&
			   (PokeParaGet(pp,ID_PARA_monsno_egg,NULL)!=MONSNO_TAMAGO)){
				for(j=0;j<WAZA_TEMOTI_MAX;j++){
					waza=PokeParaGet(pp,ID_PARA_waza1+j,NULL);
					if((ST_RendouWazaCheck(waza)==FALSE)&&(ST_YubiwohuruNGCheck(waza)==TRUE)){
						waza_no[waza_count]=waza;
						waza_count++;
					}
				}
			}
		}
	}

	if(waza_count){
		sp->waza_work=waza_no[gf_rand()%waza_count];
	}
	else{
		SkillSeqInc(sp,adrs);
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_MAGIC_CORT(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	i;
	int	adrs;
	u32	client_set_max;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("MAGIC_CORT adrs:%d\n",adrs);
#endif

	client_set_max=0;
	for(i=0;i<BattleWorkClientSetMaxGet(bw);i++){
		if(sp->psp[i].hp){
			client_set_max++;
		}
	}

	//�����̃^�[�����ŏI��������A���s����
	if(sp->agi_cnt==client_set_max-1){
		SkillSeqInc(sp,adrs);
	}
	else{
		sp->otf[sp->attack_client].magic_cort_flag=1;
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_MAGIC_CORT_A_D(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	dir;
	int	client_no;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("MAGIC_CORT_A_D\n");
#endif

	dir=BattleWorkMineEnemyCheck(bw,sp->attack_client);
	client_no=sp->attack_client;
	sp->magic_cort_client=client_no;
	sp->attack_client=sp->defence_client;

	if((sp->scw[dir].konoyubitomare_flag)&&(sp->psp[sp->scw[dir].konoyubitomare_client].hp)){
		sp->defence_client=sp->scw[dir].konoyubitomare_client;
	}
	else if((sp->AIWT.wtd[sp->waza_no_now].attackrange==RANGE_DOUBLE)||
			(sp->AIWT.wtd[sp->waza_no_now].attackrange==RANGE_TRIPLE)){
		sp->defence_client=client_no;
	}
	else{
		dir=ST_ServerDefenceClientSet(bw,sp,sp->attack_client,sp->waza_no_now,1,0);
		if((sp->ostf[dir].hiraisin_flag)||(sp->ostf[dir].yobimizu_flag)){
			sp->defence_client=dir;
		}
		else{
			sp->defence_client=client_no;
		}
	}

	//�}�W�b�N�R�[�g�ł�Attack�ADefence����ւ��t���O�𗧂Ă�
	sp->server_status_flag2|=SERVER_STATUS_FLAG2_MAGIC_CORT_A_D;

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_REVENGE(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("REVENGE\n");
#endif

	if( ((sp->otf[sp->attack_client].butsuri_otf_damage[sp->defence_client])&&
		 (sp->otf[sp->attack_client].butsuri_otf_client_bit&No2Bit(sp->defence_client))) ||
	    ((sp->otf[sp->attack_client].tokusyu_otf_damage[sp->defence_client])&&
		 (sp->otf[sp->attack_client].tokusyu_otf_client_bit&No2Bit(sp->defence_client))) ){
		sp->damage_value=20;
	}
	else{
		sp->damage_value=10;
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_KAWARAWARI(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	adrs;
	int	dir;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("KAWARAWARI adrs:%d\n",adrs);
#endif

	dir=BattleWorkMineEnemyCheck(bw,sp->defence_client);

	if((sp->side_condition[dir]&SIDE_CONDITION_BUTSURIGUARD)||
	   (sp->side_condition[dir]&SIDE_CONDITION_TOKUSYUGUARD)){
		sp->side_condition[dir]&=SIDE_CONDITION_BUTSURIGUARD_OFF;
		sp->side_condition[dir]&=SIDE_CONDITION_TOKUSYUGUARD_OFF;
		sp->scw[dir].butsuri_guard_count=0;
		sp->scw[dir].tokusyu_guard_count=0;
	}
	else{
		SkillSeqInc(sp,adrs);
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_AKUBI(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("AKUBI adrs:%d\n",adrs);
#endif

	if(sp->psp[sp->defence_client].waza_kouka&WAZAKOUKA_AKUBI){
		SkillSeqInc(sp,adrs);
	}
	else{
		sp->psp[sp->defence_client].waza_kouka|=AKUBI_COUNT<<1;
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_HATAKIOTOSU(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	adrs;
	int	dir;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("HATAKIOTOSU adrs:%d\n",adrs);
#endif

	dir=BattleWorkMineEnemyCheck(bw,sp->defence_client);

	if((sp->psp[sp->defence_client].item)&&
	   (ST_ServerKatayaburiTokuseiCheck(sp,sp->attack_client,sp->defence_client,TOKUSYU_NENTYAKU)==TRUE)){
		sp->mp.msg_id=TokuseiNoWazaMineMsg;
		sp->mp.msg_tag=TAG_NICK_TOKU_WAZA;
		sp->mp.msg_para[0]=ST_ServerTagNickParaMake(sp,sp->defence_client);
		sp->mp.msg_para[1]=sp->psp[sp->defence_client].speabino;
		sp->mp.msg_para[2]=sp->waza_no_now;
	}
	else if(sp->psp[sp->defence_client].item){
		sp->mp.msg_id=HatakiotosuM2MMsg;
		sp->mp.msg_tag=TAG_NICK_NICK_ITEM;
		sp->mp.msg_para[0]=ST_ServerTagNickParaMake(sp,sp->attack_client);
		sp->mp.msg_para[1]=ST_ServerTagNickParaMake(sp,sp->defence_client);
		sp->mp.msg_para[2]=sp->psp[sp->defence_client].item;
		sp->psp[sp->defence_client].item=0;
		sp->scw[dir].hatakiotosu_item|=No2Bit(sp->sel_mons_no[sp->defence_client]);
	}
	else{
		SkillSeqInc(sp,adrs);
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_HUNKA(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("HUNKA\n");
#endif

	//2�̂ɓ�����Z���ƁAHP������������2�̖ڂōČv�Z���ꂽ���ɈЗ͂������̂ŁA2��ڂ̓p�X����悤�ɂ���
	if(sp->damage_power==0){
//		sp->damage_power=WT_WazaDataParaGet(sp->waza_no_now,ID_WTD_damage)*
		sp->damage_power=sp->AIWT.wtd[sp->waza_no_now].damage*
						 sp->psp[sp->attack_client].hp/sp->psp[sp->attack_client].hpmax;
		if(sp->damage_power==0){
			sp->damage_power=1;
		}
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_HUUIN(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	adrs;
	int	dir;
	int	pos_a;
	int	pos_d;
	int	client_no;
	int	client_set_max;
	int	def1;
	int	def2;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("HUUIN adrs:%d\n",adrs);
#endif

	//�ӂ���������߂����t���O�𗧂Ă�i�ZAI�p�j
	def1=BattleWorkEnemyClientNoGet(bw,sp->attack_client,BWECNG_SIDE_RIGHT);
	def2=BattleWorkEnemyClientNoGet(bw,sp->attack_client,BWECNG_SIDE_LEFT);
	sp->psp[def1].waza_kouka|=WAZAKOUKA_HUUIN_DID;
	sp->psp[def2].waza_kouka|=WAZAKOUKA_HUUIN_DID;

	if(sp->psp[sp->attack_client].waza_kouka&WAZAKOUKA_HUUIN){
		SkillSeqInc(sp,adrs);
	}
	else{
		dir=BattleWorkMineEnemyCheck(bw,sp->attack_client);
		client_set_max=BattleWorkClientSetMaxGet(bw);
		for(client_no=0;client_no<client_set_max;client_no++){
			if(dir!=BattleWorkMineEnemyCheck(bw,client_no)){
				for(pos_a=0;pos_a<WAZA_TEMOTI_MAX;pos_a++){
					for(pos_d=0;pos_d<WAZA_TEMOTI_MAX;pos_d++){
						if((sp->psp[sp->attack_client].waza[pos_a]==sp->psp[client_no].waza[pos_d])&&
						   (sp->psp[sp->attack_client].waza[pos_a])&&(sp->psp[client_no].waza[pos_d])){
							break;
						}
					}
					if(pos_d!=WAZA_TEMOTI_MAX){
						break;
					}
				}
				if(pos_d!=WAZA_TEMOTI_MAX){
					break;
				}
			}
		}
		if(client_no==client_set_max){
			SkillSeqInc(sp,adrs);
		}
		else{
			sp->psp[sp->attack_client].waza_kouka|=WAZAKOUKA_HUUIN;
		}
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_ONNEN(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	adrs;
	int	dir;
	int	pos;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("ONNEN adrs:%d\n",adrs);
#endif

	dir=BattleWorkMineEnemyCheck(bw,sp->defence_client);

	if((sp->psp[sp->kizetsu_client].waza_kouka&WAZAKOUKA_ONNEN)&&
	   (BattleWorkMineEnemyCheck(bw,sp->attack_client)!=BattleWorkMineEnemyCheck(bw,sp->kizetsu_client))&&
	   (sp->psp[sp->attack_client].hp)&&
	   (sp->waza_no_temp!=WAZANO_WARUAGAKI)){
		sp->waza_work=sp->waza_no_temp;
		pos=ST_ServerWazaPosGet(&sp->psp[sp->attack_client],sp->waza_no_temp);
		sp->psp[sp->attack_client].pp[pos]=0;
		ST_PSPtoPPCopy(bw,sp,sp->attack_client);
	}
	else{
		SkillSeqInc(sp,adrs);
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_YOKODORI(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	i;
	int	adrs;
	u32	client_set_max;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("YOKODORI adrs:%d\n",adrs);
#endif

	client_set_max=0;
	for(i=0;i<BattleWorkClientSetMaxGet(bw);i++){
		if(sp->psp[i].hp){
			client_set_max++;
		}
	}

	//�����̃^�[�����ŏI��������A���s����
	if(sp->agi_cnt==client_set_max-1){
		SkillSeqInc(sp,adrs);
	}
	else{
		sp->otf[sp->attack_client].yokodori_flag=1;
	}

	return FALSE;
}

//============================================================================================
/**
 *	��������З̓e�[�u��
 */
//============================================================================================

enum{
	KT_WEIGHT=0,
	KT_POWER,
	KT_MAX
};

static	const	u16	KetaguriTable[][KT_MAX]={
	{   100,    20},
	{   250,    40},
	{   500,    60},
	{  1000,    80},
	{  2000,   100},
	{0xffff,0xffff},
};

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_KETAGURI(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int					cnt;
	int					weight;
//	ZKN_HEIGHT_GRAM_PTR	zhgp;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	cnt=0;

	//�}�ӂ̍����d����񃏁[�N���m��
//	zhgp=ZKN_HEIGHTGRAM_Alloc(HEAPID_BATTLE);
	//�}�ӂ̍����d���������[�h
//	ZKN_HEIGHTGRAM_Load(zhgp,ZKN_HEIGHT_GRAM_TYPE_MAN,HEAPID_BATTLE);

//	weight=ZKN_HEIGHTGRAM_GetGram(zhgp,sp->psp[sp->defence_client].monsno);

	//�}�ӂ̍����d������j��
//	ZKN_HEIGHTGRAM_Release(zhgp);

	weight=sp->psp[sp->defence_client].weight;

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("KETAGURI weight:%d\n",weight);
#endif

	while(KetaguriTable[cnt][KT_WEIGHT]!=0xffff){
		if(KetaguriTable[cnt][KT_WEIGHT]>=weight){
			break;
		}
		cnt++;
	}

	if(KetaguriTable[cnt][KT_WEIGHT]!=0xffff){
		sp->damage_power=KetaguriTable[cnt][KT_POWER];
	}
	else{
		sp->damage_power=120;
	}

	//�}�ӂ̍����d����񃏁[�N���J��
//	ZKN_HEIGHTGRAM_Free(zhgp);

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_WEATHER_BALL(BATTLE_WORK *bw,SERVER_PARAM *sp)
{

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("WEATHER_BALL\n");
#endif

	if((ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ALL_HP,0,TOKUSYU_NOOTENKI)==0)&&
	   (ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ALL_HP,0,TOKUSYU_EAROKKU)==0)){
		//�V��ω����Ă�΁A�_���[�W��{
		if(sp->field_condition&FIELD_CONDITION_TENKI){
			sp->damage_power=sp->AIWT.wtd[sp->waza_no_now].damage*2;
			if(sp->field_condition&FIELD_CONDITION_AME_ALL){
				sp->waza_type=WATER_TYPE;
			}
			if(sp->field_condition&FIELD_CONDITION_SUNAARASHI_ALL){
				sp->waza_type=IWA_TYPE;
			}
			if(sp->field_condition&FIELD_CONDITION_HARE_ALL){
				sp->waza_type=FIRE_TYPE;
			}
			if(sp->field_condition&FIELD_CONDITION_ARARE_ALL){
				sp->waza_type=KOORI_TYPE;
			}
		}
		else{
			sp->damage_power=sp->AIWT.wtd[sp->waza_no_now].damage;
		}
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_OIUCHI_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	adrs;
	int	client_no;
	int	client_set_max;
	int	waza_no;
	int	pos;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("OIUCHI_CHECK adrs:%d\n",adrs);
#endif

	client_set_max=BattleWorkClientSetMaxGet(bw);

	for(client_no=0;client_no<client_set_max;client_no++){
		if((sp->client_act_work[client_no][ACT_PARA_ACT_NO]!=SERVER_WAZA_END_NO)&&
		   (sp->psp[client_no].hp)&&
		  ((sp->psp[client_no].condition&(CONDITION_NEMURI|CONDITION_KOORI))==0)&&
		   (ST_ServerNamakeCheck(sp,client_no)==FALSE)&&
		   (BattleWorkMineEnemyCheck(bw,client_no)!=BattleWorkMineEnemyCheck(bw,sp->reshuffle_client))){
			//�A���R�[�����̃`�F�b�N
			if((sp->psp[client_no].wkw.encore_wazano)&&
			   (sp->psp[client_no].wkw.encore_wazano==
				sp->psp[client_no].waza[sp->psp[client_no].wkw.encore_wazapos])){
				waza_no=sp->psp[client_no].wkw.encore_wazano;
			}
			else{
				waza_no=ST_ServerSelectWazaGet(sp,client_no);
			}
			if(waza_no){
				pos=ST_ServerWazaPosGet(&sp->psp[client_no],waza_no);
				if((sp->AIWT.wtd[waza_no].battleeffect==128)&&
				   (sp->psp[client_no].pp[pos])){
					sp->psp[client_no].pp[pos]--;
					if((ST_ServerTokuseiGet(sp,sp->reshuffle_client)==TOKUSYU_PURESSYAA)&&
					   (sp->psp[client_no].pp[pos])){
						sp->psp[client_no].pp[pos]--;
					}
					ST_ServerLoopInit(bw,sp);
					sp->attack_client=client_no;
					sp->defence_client=sp->reshuffle_client;
					sp->damage_value=20;
					sp->waza_no_now=waza_no;
					sp->waza_no_old[client_no]=waza_no;
					sp->client_act_work[client_no][ACT_PARA_ACT_NO]=SERVER_WAZA_END_NO;
					break;
				}
			}
		}
	}

	if(client_no==client_set_max){
		SkillSeqInc(sp,adrs);
	}
	//�������������Ȃ�A�������n�̃`�F�b�N������
	else{
		{
			int	eqp;
			int	atk;

			eqp=ST_ServerSoubiEqpGet(sp,sp->attack_client);
			atk=ST_ServerSoubiAtkGet(sp,sp->attack_client,ATK_CHECK_NORMAL);

			//�����A�C�e���u�������͂��܂��v�́A�Z�̔����Ń��[�N�֑��
			if((eqp==SOUBI_ONAZIWAZAONLY)||
			   (eqp==SOUBI_ONAZIWAZAONLYSUBAYASAUP)||
			   (eqp==SOUBI_ONAZIAWZAONLYTOKUSYUUP)){
				sp->psp[sp->attack_client].wkw.kodawari_wazano=sp->waza_no_temp;
			}
		}
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_TYPE_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("TYPE_CHECK\n");
#endif

	sp->damage=ST_ServerTypeCheck(bw,sp,sp->waza_no_now,sp->waza_type,sp->attack_client,sp->defence_client,sp->damage,&sp->waza_status_flag);

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_OTF_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	side;
	int	flag;
	int	value;
	int	adrs;
	int	client_no;
	int	ret=0;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//side�����[�h
	side=SkillSeqDataRead(sp);

	//flag�����[�h
	flag=SkillSeqDataRead(sp);

	//value�����[�h
	value=SkillSeqDataRead(sp);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("OTF_CHECK side:%d flag:%d adrs:%d\n",side,flag,adrs);
#endif

	client_no=SideClientNoGet(bw,sp,side);

	switch(flag){
	case OTF_waruagaki_flag:	//��邠�����t���O
		if(sp->otf[client_no].waruagaki_flag==value){
			ret=1;
		}
		break;
	case OTF_pp_dec_flag:		//PP�����炵���t���O
		if(sp->otf[client_no].pp_dec_flag==value){
			ret=1;
		}
		break;
	case OTF_mamoru_flag:		//�܂���t���O
		if(sp->otf[client_no].mamoru_flag==value){
			ret=1;
		}
		break;
	case OTF_tedasuke_flag:		//�Ă������t���O
		if(sp->otf[client_no].tedasuke_flag==value){
			ret=1;
		}
		break;
	case OTF_magic_cort_flag:
		if(sp->otf[client_no].magic_cort_flag==value){
			ret=1;
		}
		break;
	case OTF_yokodori_flag:
		if(sp->otf[client_no].yokodori_flag==value){
			ret=1;
		}
		break;
	case OTF_haneyasume_flag:
		if(sp->otf[client_no].haneyasume_flag==value){
			ret=1;
		}
		break;
	}

	if(ret){
		SkillSeqInc(sp,adrs);
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_OTF_SET(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	side;
	int	flag;
	int	value;
	int	client_no;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//side�����[�h
	side=SkillSeqDataRead(sp);

	//flag�����[�h
	flag=SkillSeqDataRead(sp);

	//value�����[�h
	value=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("OTF_SET side:%d flag:%d\n",side,flag);
#endif

	client_no=SideClientNoGet(bw,sp,side);

	switch(flag){
	case OTF_waruagaki_flag:	//��邠�����t���O
		sp->otf[client_no].waruagaki_flag=value;
		break;
	case OTF_pp_dec_flag:		//PP�����炵���t���O
		sp->otf[client_no].pp_dec_flag=value;
		break;
	case OTF_mamoru_flag:		//�܂���t���O
		sp->otf[client_no].mamoru_flag=value;
		break;
	case OTF_tedasuke_flag:		//�Ă������t���O
		sp->otf[client_no].tedasuke_flag=value;
		break;
	case OTF_magic_cort_flag:
		sp->otf[client_no].magic_cort_flag=value;
		break;
	case OTF_yokodori_flag:
		sp->otf[client_no].yokodori_flag=value;
		break;
	case OTF_haneyasume_flag:
		sp->otf[client_no].haneyasume_flag=value;
		break;
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_GIROBALL(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("GIROBALL\n");
#endif

	sp->damage_power=1+25*sp->psp_agi_point[sp->defence_client]/sp->psp_agi_point[sp->attack_client];

	if(sp->damage_power>150){
		sp->damage_power=150;
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_METALMIRROR(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	adrs;
	int	dir_a;
	int	dir_d;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("METALMIRROR adrs:%d\n",adrs);
#endif

	dir_a=BattleWorkMineEnemyCheck(bw,sp->attack_client);
	dir_d=BattleWorkMineEnemyCheck(bw,sp->otf[sp->attack_client].last_otf_client);

	if((sp->otf[sp->attack_client].last_otf_damage)&&
	   (dir_a!=dir_d)&&
	   (sp->psp[sp->otf[sp->attack_client].last_otf_client].hp)){
		sp->damage=sp->otf[sp->attack_client].last_otf_damage*15/10;
		if((sp->scw[dir_d].konoyubitomare_flag)&&(sp->psp[sp->scw[dir_d].konoyubitomare_client].hp)){
			sp->defence_client=sp->scw[dir_d].konoyubitomare_client;
		}
		else{
			sp->defence_client=sp->otf[sp->attack_client].last_otf_client;
		}
		if(sp->psp[sp->defence_client].hp==0){
			sp->defence_client=ST_ServerDirClientGet(bw,sp,sp->attack_client);
			if(sp->psp[sp->defence_client].hp==0){
				sp->next_server_seq_no=SERVER_WAZA_NO_BUFFER_SET_NO;
				SkillSequenceJump(sp,ARC_SUB_SEQ,SUB_SEQ_NO_DEFENCE);
			}
		}
		ST_ServerPressurePPDecCheck(sp,sp->attack_client,sp->defence_client);
	}
	else{
		SkillSeqInc(sp,adrs);
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_TAMEUCHI(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("TAMEUSHI\n");
#endif

	if(sp->client_act_work[sp->defence_client][ACT_PARA_ACT_NO]==SERVER_WAZA_END_NO){
		sp->damage_power=sp->AIWT.wtd[sp->waza_no_now].damage*2;
	}
	else{
		sp->damage_power=sp->AIWT.wtd[sp->waza_no_now].damage;
	}

	return FALSE;
}

//============================================================================================
/**
 *	����ӂ��З̓e�[�u��
 */
//============================================================================================
static	const	u8	KirihudaPowerTable[]={
	200,
	80,
	60,
	50,
	40,
};

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_KIRIHUDA(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	u8	pp;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("KIRIHUDA\n");
#endif

	pp=sp->psp[sp->attack_client].pp[sp->waza_no_pos[sp->attack_client]];

	if(pp>4){
		pp=4;
	}

	sp->damage_power=KirihudaPowerTable[pp];

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_SIBORITORU(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	u8	pp;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("SIBORITORU\n");
#endif

	sp->damage_power=1+(120*sp->psp[sp->defence_client].hp)/sp->psp[sp->defence_client].hpmax;

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_SAKIDORI(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int				adrs;
	u16				waza;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("SAKIDORI adrs:%d\n",adrs);
#endif

	//�A���R�[�����̃`�F�b�N
	if((sp->psp[sp->defence_client].wkw.encore_wazano)&&
	   (sp->psp[sp->defence_client].wkw.encore_wazano==
		sp->psp[sp->defence_client].waza[sp->psp[sp->defence_client].wkw.encore_wazapos])){
		waza=sp->psp[sp->defence_client].wkw.encore_wazano;
	}
	else{
		waza=ST_ServerSelectWazaGet(sp,sp->defence_client);
	}

	if((sp->client_act_work[sp->defence_client][ACT_PARA_ACT_NO]!=SERVER_WAZA_END_NO)&&
	   (sp->otf[sp->defence_client].waruagaki_flag==0)&&
	   (ST_SakidoriNGCheck(sp,waza)==TRUE)&&
	   (sp->AIWT.wtd[waza].damage)){
		sp->psp[sp->attack_client].wkw.sakidori_flag=1;
		sp->psp[sp->attack_client].wkw.sakidori_count=sp->sakidori_total_turn;
		sp->waza_work=waza;
	}
	else{
		SkillSeqInc(sp,adrs);
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_MANEKKO(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("MANEKKO adrs:%d\n",adrs);
#endif

	if((ST_RendouWazaCheck(sp->waza_no_last)==FALSE)&&
	   (sp->waza_no_last)&&
	   (ST_YubiwohuruNGCheck(sp->waza_no_last)==TRUE)){
		sp->waza_work=sp->waza_no_last;
	}
	else{
		SkillSeqInc(sp,adrs);
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_OSIOKI(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	para;
	int	cnt;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("OSIOKI\n");
#endif

	cnt=0;

	for(para=COND_HP;para<COND_MAX;para++){
		if(sp->psp[sp->defence_client].abiritycnt[para]>6){
			cnt+=(sp->psp[sp->defence_client].abiritycnt[para]-6);
		}
	}

	sp->damage_power=60+20*cnt;
	
	if(sp->damage_power>200){
		sp->damage_power=200;
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_HUIUCHI(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	adrs;
	int	waza;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("HUIUCHI adrs:%d\n",adrs);
#endif

	//�A���R�[�����̃`�F�b�N
	if((sp->psp[sp->defence_client].wkw.encore_wazano)&&
	   (sp->psp[sp->defence_client].wkw.encore_wazano==
		sp->psp[sp->defence_client].waza[sp->psp[sp->defence_client].wkw.encore_wazapos])){
		waza=sp->psp[sp->defence_client].wkw.encore_wazano;
	}
	else{
		waza=ST_ServerSelectWazaGet(sp,sp->defence_client);
	}

	if((sp->client_act_work[sp->defence_client][ACT_PARA_ACT_NO]==SERVER_WAZA_END_NO)||
	   ((sp->AIWT.wtd[waza].damage==0)&&(sp->otf[sp->defence_client].waruagaki_flag==0))){
		SkillSeqInc(sp,adrs);
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_SIDE_CONDITION_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	side;
	int	mode;
	int	flag;
	int	adrs;
	int	client_no;
	int	dir;
	int	count;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//side�����[�h
	side=SkillSeqDataRead(sp);

	//mode�����[�h
	mode=SkillSeqDataRead(sp);

	//flag�����[�h
	flag=SkillSeqDataRead(sp);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("SIDE_CONDITION_CHECK side:%d mode:%d flag:%d adrs:%d\n",side,mode,flag,adrs);
#endif

	client_no=SideClientNoGet(bw,sp,side);
	dir=BattleWorkMineEnemyCheck(bw,client_no);

	switch(mode){
	case SCC_MODE_Z_CHECK:
	case SCC_MODE_NZ_CHECK:
		switch(flag){
		case SCC_butsuri_guard_count:
			count=sp->scw[dir].butsuri_guard_count;
			break;
		case SCC_tokusyu_guard_count:
			count=sp->scw[dir].tokusyu_guard_count;
			break;
		case SCC_shiroikiri_count:
			count=sp->scw[dir].shiroikiri_count;
			break;
		case SCC_shinpi_count:
			count=sp->scw[dir].shinpi_count;
			break;
		case SCC_makibisi_count:
			count=sp->scw[dir].makibisi_count;
			break;
		case SCC_dokubisi_count:
			count=sp->scw[dir].dokubisi_count;
			break;
		}
		break;
	case SCC_MODE_CLEAR:
		switch(flag){
		case SCC_butsuri_guard_count:
			sp->scw[dir].butsuri_guard_count=0;
			sp->side_condition[dir]&=SIDE_CONDITION_BUTSURIGUARD_OFF;
			break;
		case SCC_tokusyu_guard_count:
			sp->scw[dir].tokusyu_guard_count=0;
			sp->side_condition[dir]&=SIDE_CONDITION_TOKUSYUGUARD_OFF;
			break;
		case SCC_shiroikiri_count:
			sp->scw[dir].shiroikiri_count=0;
			sp->side_condition[dir]&=SIDE_CONDITION_SHIROIKIRI_OFF;
			break;
		case SCC_shinpi_count:
			sp->scw[dir].shinpi_count=0;
			sp->side_condition[dir]&=SIDE_CONDITION_SHINPI_OFF;
			break;
		case SCC_makibisi_count:
			sp->scw[dir].makibisi_count=0;
			sp->side_condition[dir]&=SIDE_CONDITION_MAKIBISHI_OFF;
			break;
		case SCC_dokubisi_count:
			sp->scw[dir].dokubisi_count=0;
			sp->side_condition[dir]&=SIDE_CONDITION_DOKUBISHI_OFF;
			break;
		}
		break;
	}

	if((mode==SCC_MODE_Z_CHECK)&&(count==0)){
		SkillSeqInc(sp,adrs);
	}
	if((mode==SCC_MODE_NZ_CHECK)&&(count)){
		SkillSeqInc(sp,adrs);
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_FEINT(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	adrs;
	int	waza;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("FEINT adrs:%d\n",adrs);
#endif

	if(sp->otf[sp->defence_client].mamoru_flag==0){
		SkillSeqInc(sp,adrs);
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_SURIKOMI(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	adrs;
	int	waza;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("SURIKOMI adrs:%d\n",adrs);
#endif

	if((sp->psp[sp->defence_client].condition)||
	   (sp->psp[sp->defence_client].condition2&CONDITION2_MIGAWARI)||
	   (sp->psp[sp->attack_client].condition==0)){
		SkillSeqInc(sp,adrs);
	}
#if 0
	else{
		if(sp->psp[sp->attack_client].condition&CONDITION_NEMURI){
			sp->add_status_flag_direct=ADD_COND_NEMURI|ADD_STATUS_DEFENCE|ADD_STATUS_WAZAKOUKA_NOHIT;
		}
		else if(sp->psp[sp->attack_client].condition&CONDITION_DOKU){
			sp->add_status_flag_direct=ADD_COND_DOKU|ADD_STATUS_DEFENCE|ADD_STATUS_WAZAKOUKA_NOHIT;
		}
		else if(sp->psp[sp->attack_client].condition&CONDITION_YAKEDO){
			sp->add_status_flag_direct=ADD_COND_YAKEDO|ADD_STATUS_DEFENCE|ADD_STATUS_WAZAKOUKA_NOHIT;
		}
		else if(sp->psp[sp->attack_client].condition&CONDITION_MAHI){
			sp->add_status_flag_direct=ADD_COND_MAHI|ADD_STATUS_DEFENCE|ADD_STATUS_WAZAKOUKA_NOHIT;
		}
		else if(sp->psp[sp->attack_client].condition&CONDITION_DOKUDOKU){
			sp->add_status_flag_direct=ADD_COND_DOKUDOKU|ADD_STATUS_DEFENCE|ADD_STATUS_WAZAKOUKA_NOHIT;
		}
	}
#endif

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_TOTTEOKI(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	adrs;
	int	count;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("TOTTEOKI adrs:%d\n",adrs);
#endif

	count=ST_ServerWazaCountGet(bw,sp,sp->attack_client);

	//�����Ă���Z���o���؂��Ă��Ȃ����A�����Ă���Z��2�ȏ�Ȃ��ꍇ�͎��s
	if( (sp->psp[sp->attack_client].wkw.totteoki_count<(count-1)) || (count<2) ){
		SkillSeqInc(sp,adrs);
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_DOKUBISI(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	adrs;
	int	dir;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("DOKUBISI adrs:%d\n",adrs);
#endif

	dir=BattleWorkMineEnemyCheck(bw,sp->attack_client)^1;

	if(sp->scw[dir].dokubisi_count==2){
		sp->ostf[sp->attack_client].no_pressure_flag=1;
		SkillSeqInc(sp,adrs);
	}
	else{
		sp->side_condition[dir]|=SIDE_CONDITION_DOKUBISHI;
		sp->scw[dir].dokubisi_count++;
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_DOKUBISI_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	side;
	int	adrs;
	int	client_no;
	int	dir;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//side�����[�h
	side=SkillSeqDataRead(sp);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("DOKUBISI_CHECK side:%d adrs:%d\n",side,adrs);
#endif

	client_no=SideClientNoGet(bw,sp,side);
	dir=BattleWorkMineEnemyCheck(bw,client_no);

	if(sp->scw[dir].dokubisi_count){
		sp->calc_work=sp->scw[dir].dokubisi_count;
		sp->tsuika_type=ADD_STATUS_DOKUBISI;
		sp->tsuika_client=client_no;
		if((ST_ServerPokemonServerParamGet(sp,sp->reshuffle_client,ID_PSP_type1,NULL)==POISON_TYPE)||
		   (ST_ServerPokemonServerParamGet(sp,sp->reshuffle_client,ID_PSP_type2,NULL)==POISON_TYPE)){
			sp->side_condition[dir]&=SIDE_CONDITION_DOKUBISHI_OFF;
			sp->scw[dir].dokubisi_count=0;
			sp->calc_work=0;
		}
	}
	else{
		SkillSeqInc(sp,adrs);
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_KATAYABURI_TOKUSEI_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	flag;
	int	side;
	int	tokusei;
	int	adrs;
	int	client_no;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//flag�����[�h
	flag=SkillSeqDataRead(sp);

	//side�����[�h
	side=SkillSeqDataRead(sp);

	//tokusei�����[�h
	tokusei=SkillSeqDataRead(sp);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("KATAYABURI_TOKUSEI_CHECK flag:%d side:%d tokusei:%d adrs:%d\n",flag,side,tokusei,adrs);
#endif

	//SIDE_ALL�̎��́A��ɂłĂ���|�P�������ׂĂ��`�F�b�N
	if(side==SIDE_ALL){
		{
			int	no;
			int	client_set_max;

			client_set_max=BattleWorkClientSetMaxGet(bw);

			for(no=0;no<client_set_max;no++){
				client_no=sp->psp_agi_work[no];
				if(flag==TOKUSEI_HAVE){
					if((ST_ServerKatayaburiTokuseiCheck(sp,sp->attack_client,client_no,tokusei)==TRUE)&&(sp->psp[client_no].hp)){
						SkillSeqInc(sp,adrs);
						sp->tokusei_client=client_no;
						break;
					}
				}
				else{
					//�N�������Ă��Ȃ����Ƃ��`�F�b�N
					if((ST_ServerKatayaburiTokuseiCheck(sp,sp->attack_client,client_no,tokusei)==FALSE)||
					   (sp->psp[client_no].hp==0)){
						SkillSeqInc(sp,adrs);
						sp->tokusei_client=client_no;
						break;
					}
				}
			}
		}
	}
	else{
		client_no=SideClientNoGet(bw,sp,side);
	
		if(flag==TOKUSEI_HAVE){
			if((ST_ServerKatayaburiTokuseiCheck(sp,sp->attack_client,client_no,tokusei)==TRUE)&&(sp->psp[client_no].hp)){
				SkillSeqInc(sp,adrs);
				sp->tokusei_client=client_no;
			}
		}
		else{
			if((ST_ServerKatayaburiTokuseiCheck(sp,sp->attack_client,client_no,tokusei)==FALSE)||(sp->psp[client_no].hp==0)){
				SkillSeqInc(sp,adrs);
				sp->tokusei_client=client_no;
			}
		}
	}

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_SIDE_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	src;
	int	dest;
	int	adrs;
	int	client_s;
	int	client_d;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//src�����[�h
	src=SkillSeqDataRead(sp);

	//dest�����[�h
	dest=SkillSeqDataRead(sp);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("SIDE_CHECK src:%d dest:%d adrs:%d\n",src,dest,adrs);
#endif

	client_s=SideClientNoGet(bw,sp,src);
	client_d=SideClientNoGet(bw,sp,dest);

	if(BattleWorkMineEnemyCheck(bw,client_s)==BattleWorkMineEnemyCheck(bw,client_d)){
		SkillSeqInc(sp,adrs);
	}

	return	FALSE;
}

//============================================================================================
/**
 *	���̂Ђ낢�e�[�u��
 */
//============================================================================================
static const u16 MonohiroiTable1[]={
	ITEM_KIZUGUSURI,
	ITEM_DOKUKESI,
	ITEM_IIKIZUGUSURI,
	ITEM_SUUPAABOORU,
	ITEM_MUSIYOKESUPUREE,
	ITEM_ANANUKENOHIMO,
	ITEM_NANDEMONAOSI,
	ITEM_SUGOIKIZUGUSURI,
	ITEM_HAIPAABOORU,
	ITEM_GENKINOKAKERA,
	ITEM_HUSIGINAAME,
	ITEM_YAMINOISI,
	ITEM_HIKARINOISI,
	ITEM_MEZAMEISI,
	ITEM_KAIHUKUNOKUSURI,
	ITEM_GENKINOKATAMARI,
	ITEM_POINTOAPPU,
	ITEM_PIIPIIMAKKUSU,
};

static const u16 MonohiroiTable2[]={
	ITEM_SUGOIKIZUGUSURI,
	ITEM_KINNOTAMA,
	ITEM_OUZYANOSIRUSI,
	ITEM_KAIHUKUNOKUSURI,
	ITEM_PIIPIIEIDO,
	ITEM_SIROIHAABU,
	ITEM_WAZAMASIN44,	//�˂ނ�
	ITEM_PIIPIIEIDAA,
	ITEM_WAZAMASIN01,	//�������p���`
	ITEM_TABENOKOSI,
	ITEM_WAZAMASIN26,	//������
};

static	const u8 ItemProb[] = {		//�E���A�C�e���̊m��
	30,		// 30%
	40,		// 10%
	50,		// 10%
	60,		// 10%
	70,		// 10%
	80,		// 10%
	90,		// 10%
	94,		// 4%
	98,		// 4%
};//�c��2���͕ʂŊǗ�

//�݂��ߗp�m���e�[�u��
static	const	u8	MitsuatsumeProb[]={
	 5,		// ( 1- 10)
	10,		// (11- 20)
	15,		// (21- 30)
	20,		// (31- 40)
	25,		// (41- 50)
	30,		// (51- 60)
	35,		// (61- 70)
	40,		// (71- 80)
	45,		// (81- 90)
	50,		// (91-100)
};

//============================================================================================
/**
 *	�������̂Ђ낢�̃`�F�b�N�i�݂��߁A�~�m���b�`�̃t�H�����`�F���W���^�C�~���O�͈ꏏ�Ȃ̂ō��킹�ă`�F�b�N�j
 *
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_MONOHIROI(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	rnd;
	int	i,j,k;
	u16 monsno;
	u16 itemno;
	u8	speabi;
	u8	LvOffset;
	POKEMON_PARAM	*pp;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("MONOHIROI\n");
#endif

	for(i=0;i<BattleWorkPokeCountGet(bw,CLIENT_NO_MINE);i++){
		pp=BattleWorkPokemonParamGet(bw,CLIENT_NO_MINE,i);
		monsno=PokeParaGet(pp,ID_PARA_monsno_egg,NULL);
		itemno=PokeParaGet(pp,ID_PARA_item,NULL);
		speabi=PokeParaGet(pp,ID_PARA_speabino,NULL);
		//���̂Ђ낢�`�F�b�N
		if((speabi==TOKUSYU_MONOHIROI)&&(monsno!=0)&&(monsno!=MONSNO_TAMAGO)&&(itemno==0)&&((gf_rand()%10)==0)){
			rnd=gf_rand()%100;
			LvOffset=(PokeParaGet(pp,ID_PARA_level,NULL)-1)/10;
			if(LvOffset>=10){
				LvOffset=9;//���x����100�𒴂��Ȃ���΂��肦�Ȃ����A�O�̂���
			}
			for(j=0;j<9;j++){
				if(ItemProb[j]>rnd){
					PokeParaPut(pp,ID_PARA_item,(u8 *)&MonohiroiTable1[LvOffset+j]);
					break;
				}
				else if((rnd>=98)&&(rnd<=99)){
					PokeParaPut(pp,ID_PARA_item,(u8 *)&MonohiroiTable2[LvOffset+(99-rnd)]);
					break;
				}
			}
		}
		//�݂��߃`�F�b�N
		if((speabi==TOKUSYU_MITUATUME)&&(monsno!=0)&&(monsno!=MONSNO_TAMAGO)&&(itemno==0)){
			j=0;
			k=10;
			LvOffset=PokeParaGet(pp,ID_PARA_level,NULL);
			while(LvOffset>k){
				j++;
				k+=10;
			}
			//�e�[�u���I�[�o�[���Ď����邽�߂ɃA�T�[�g�����܂�
			GF_ASSERT(j<10);
			if(gf_rand()%100<MitsuatsumeProb[j]){
				j=ITEM_AMAIMITU;
				PokeParaPut(pp,ID_PARA_item,(u8 *)&j);
			}
		}
	}

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_TRICKROOM(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
#if 0
	int	i,j;
	int	cl1;
	int	cl2;
	int	flag;
	int	client_set_max;
#endif

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);
	
#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("TRICKROOM\n");
#endif

#if 0
	client_set_max=BattleWorkClientSetMaxGet(bw);

	for(i=0;i<client_set_max-1;i++){
		for(j=i+1;j<client_set_max;j++){
			cl1=sp->client_agi_work[i];
			cl2=sp->client_agi_work[j];
			if(sp->client_act_work[cl1][ACT_PARA_SELECT_COMMAND]==sp->client_act_work[cl2][ACT_PARA_SELECT_COMMAND]){
				if(sp->client_act_work[cl1][ACT_PARA_SELECT_COMMAND]==SELECT_FIGHT_COMMAND){
					flag=0;
				}
				else{
					flag=1;
				}
				if(ST_ServerAgiCalc(bw,sp,cl1,cl2,flag)){
					sp->client_agi_work[i]=cl2;
					sp->client_agi_work[j]=cl1;
				}
			}
		}
	}
#endif

	sp->ostf[sp->attack_client].trickroom_flag=1;

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_WAZA_OUT_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	client_no;
	int	side;
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//side�����[�h
	side=SkillSeqDataRead(sp);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("WAZA_OUT_CHECK side:%d adrs:%d\n",side,adrs);
#endif

	client_no=SideClientNoGet(bw,sp,side);

	if(ST_ServerWazaEndCheck(sp,client_no)==TRUE){
		SkillSeqInc(sp,adrs);
	}

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_SOUBI_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	client_no;
	int	flag;
	int	side;
	int	adrs;
	u16	item_no;
	int	eqp;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//flag�����[�h
	flag=SkillSeqDataRead(sp);

	//side�����[�h
	side=SkillSeqDataRead(sp);

	//eqp�����[�h
	eqp=SkillSeqDataRead(sp);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("SOUBI_CHECK flag:%d side:%d eqp:%d adrs:%d\n",flag,side,eqp,adrs);
#endif

	client_no=SideClientNoGet(bw,sp,side);

	if(flag==SOUBI_HAVE){
		if(ST_ServerSoubiEqpGet(sp,client_no)==eqp){
			SkillSeqInc(sp,adrs);
		}
	}
	else{
		if(ST_ServerSoubiEqpGet(sp,client_no)!=eqp){
			SkillSeqInc(sp,adrs);
		}
	}

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_SOUBI_EQP_GET(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	client_no;
	int	side;
	int	para;
	int	*data;
	u16	item_no;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//side�����[�h
	side=SkillSeqDataRead(sp);

	//para�����[�h
	para=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("SOUBI_EQP_GET side:%d para:%d\n",side,para);
#endif

	data=WS_SrcPointerGet(bw,sp,para);

	client_no=SideClientNoGet(bw,sp,side);

	item_no=ST_ServerSoubiItemNoGet(sp,client_no);
//	data[0]=ItemParamGet(item_no,ITEM_PRM_EQUIP,HEAPID_BATTLE);
	data[0]=ST_ItemParamGet(sp,item_no,ITEM_PRM_EQUIP);

	return	FALSE;
}


//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_SOUBI_ATK_GET(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	client_no;
	int	side;
	int	para;
	int	*data;
	u16	item_no;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//side�����[�h
	side=SkillSeqDataRead(sp);

	//para�����[�h
	para=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("SOUBI_ATK_GET side:%d para:%d\n",side,para);
#endif

	data=WS_SrcPointerGet(bw,sp,para);

	client_no=SideClientNoGet(bw,sp,side);

	item_no=ST_ServerSoubiItemNoGet(sp,client_no);
//	data[0]=ItemParamGet(item_no,ITEM_PRM_ATTACK,HEAPID_BATTLE);
	data[0]=ST_ItemParamGet(sp,item_no,ITEM_PRM_ATTACK);

	return	FALSE;
}

//============================================================================================
/**
 *	�ق����傭�e�[�u��
 */
//============================================================================================
static	const	u8	HogosyokuTypeTable[]={
	JIMEN_TYPE,		//����
	JIMEN_TYPE,		//���l
	KUSA_TYPE,		//�Ő�
	KUSA_TYPE,		//�����܂�
	IWA_TYPE,		//�┧
	IWA_TYPE,		//���A
	KOORI_TYPE,		//�ጴ
	WATER_TYPE,		//����
	KOORI_TYPE,		//�X��
	NORMAL_TYPE,	//��
	JIMEN_TYPE,		//���n
	HIKOU_TYPE,		//�݂苴
	NORMAL_TYPE,	//����ȊO�i�ꉞ��`�j
};

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_HOGOSYOKU(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	adrs;
	int	ground;
	int	type;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("HOGOSYOKU adrs:%d\n",adrs);
#endif

	//�����}���`�^�C�v�͎��g�̃^�C�v��ω�������Z�́A���s�ɂ���
	if(ST_ServerTokuseiGet(sp,sp->attack_client)==TOKUSYU_MARUTITAIPU){
		SkillSeqInc(sp,adrs);
		return FALSE;
	}

	ground=BattleWorkGroundIDGet(bw);
	type=HogosyokuTypeTable[ground];

	if((ST_ServerPokemonServerParamGet(sp,sp->attack_client,ID_PSP_type1,NULL)!=type)&&
	   (ST_ServerPokemonServerParamGet(sp,sp->attack_client,ID_PSP_type2,NULL)!=type)){
		sp->psp[sp->attack_client].type1=type;
		sp->psp[sp->attack_client].type2=type;
		sp->msg_work=type;
	}
	else{
		SkillSeqInc(sp,adrs);
	}

	return	FALSE;
}

//============================================================================================
/**
 *	������̂�����e�[�u��
 */
//============================================================================================
static	const	u16	ShizennochikaraWazaTable[]={
	WAZANO_ZISIN,			//����
	WAZANO_ZISIN,			//���l
	WAZANO_TANEBAKUDAN,		//�Ő�
	WAZANO_TANEBAKUDAN,		//�����܂�
	WAZANO_IWANADARE,		//�┧
	WAZANO_IWANADARE,		//���A
	WAZANO_HUBUKI,			//�ጴ
	WAZANO_HAIDOROPONPU,	//����
	WAZANO_REITOUBIIMU,		//�X��
	WAZANO_TORAIATAKKU,		//��
	WAZANO_DOROBAKUDAN,		//���n
	WAZANO_EASURASSYU,		//�݂苴
	WAZANO_TORAIATAKKU,		//����ȊO�i�ꉞ��`�j
};

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_SHIZENNOCHIKARA(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	ground;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("SHIZENNOCHIKARA\n");
#endif

	ground=BattleWorkGroundIDGet(bw);

	sp->waza_work=ShizennochikaraWazaTable[ground];

	return FALSE;
}

//============================================================================================
/**
 *	�Ђ݂̂�����e�[�u��
 */
//============================================================================================
static	const	u32	HimitsunochikaraAddTable[]={
	ADD_COND2_HITDOWN|	ADD_STATUS_DEFENCE,		//����
	ADD_COND2_HITDOWN|	ADD_STATUS_DEFENCE,		//���l
	ADD_COND_NEMURI|	ADD_STATUS_DEFENCE,		//�Ő�
	ADD_COND_NEMURI|	ADD_STATUS_DEFENCE,		//�����܂�
	ADD_COND2_HIRUMU|	ADD_STATUS_DEFENCE,		//�┧
	ADD_COND2_HIRUMU|	ADD_STATUS_DEFENCE,		//���A
	ADD_COND_KOORI|		ADD_STATUS_DEFENCE,		//�ጴ
	ADD_COND2_POWDOWN|	ADD_STATUS_DEFENCE,		//����
	ADD_COND_KOORI|		ADD_STATUS_DEFENCE,		//�X��
	ADD_COND_MAHI|		ADD_STATUS_DEFENCE,		//��
	ADD_COND2_AGIDOWN|	ADD_STATUS_DEFENCE,		//���n
	ADD_COND2_AVOIDDOWN|ADD_STATUS_DEFENCE,		//�݂苴
	ADD_COND_MAHI|		ADD_STATUS_DEFENCE,		//����ȊO�i�ꉞ��`�j
};

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_HIMITSUNOCHIKARA(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	ground;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("HIMITSUNOCHIKARA\n");
#endif

	ground=BattleWorkGroundIDGet(bw);

	sp->add_status_flag_indirect=HimitsunochikaraAddTable[ground];

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_SHIZENNOMEGUMI(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	adrs;
	int	atk;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("SHIZENNOMEGUMI adrs:%d\n",adrs);
#endif

	atk=ST_ServerShizennomegumiAtkGet(sp,sp->attack_client);

	if(atk){
		sp->damage_power=atk;
		sp->waza_type=ST_ServerShizennomegumiTypeGet(sp,sp->attack_client);
	}
	else{
		SkillSeqInc(sp,adrs);
	}

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_TSUIBAMU(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	adrs1;
	int	adrs2;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//adrs1�����[�h
	adrs1=SkillSeqDataRead(sp);

	//adrs2�����[�h
	adrs2=SkillSeqDataRead(sp);
	
#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("TSUIBAMU adrs1:%d adrs2:%d\n",adrs1,adrs2);
#endif

	if((sp->psp[sp->defence_client].item)&&
	   (ST_ServerKatayaburiTokuseiCheck(sp,sp->attack_client,sp->defence_client,TOKUSYU_NENTYAKU)==TRUE)){
		SkillSeqInc(sp,adrs1);
	}
	else if(ST_ServerTsuibamuCheck(bw,sp,sp->defence_client)!=TRUE){
		SkillSeqInc(sp,adrs2);
	}

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_NAGETSUKERU(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("NAGETSUKERU adrs:%d\n",adrs);
#endif

	if(ST_ServerNagetsukeruCheck(bw,sp,sp->attack_client)!=TRUE){
		SkillSeqInc(sp,adrs);
	}

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_YES_NO_SELECT(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	type;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//type�����[�h
	type=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("YES_NO_SELECT type:%d\n",type);
#endif

	SCIO_YesNoSelectSet(bw,sp,CLIENT_NO_MINE,NULL,type,NULL,NULL);

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_YES_NO_SELECT_WAIT(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	u8	res;
	int	adrs1;
	int	adrs2;

	res=ST_ServerBufferResGet(sp,CLIENT_NO_MINE);

	if(res){
		//���߃R�[�h����ǂݔ�΂�
		SkillSeqInc(sp,1);
		//adrs1�����[�h
		adrs1=SkillSeqDataRead(sp);
		//adrs2�����[�h
		adrs2=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("YES_NO_SELECT_WAIT adrs1:%d adrs2:%d\n",adrs1,adrs2);
#endif

		//No��I��
		if(res==SELECT_CANCEL){
			SkillSeqInc(sp,adrs2);
		}
		//Yes��I��
		else{
			SkillSeqInc(sp,adrs1);
		}
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_POKEMON_LIST_CALL(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	client_no;
	int	client_set_max=BattleWorkClientSetMaxGet(bw);

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("POKEMON_LIST_CALL\n");
#endif

	SCIO_PokemonSelectSet(bw,sp,CLIENT_NO_MINE,BPL_MODE_NORMAL,0,NO_DOUBLE_SEL);
	sp->reshuffle_client=CLIENT_NO_MINE;

	return	FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_POKEMON_LIST_CALL_WAIT(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	u8	res;
	int	adrs;

	res=ST_ServerBufferResGet(sp,CLIENT_NO_MINE);

	if(res){
		//���߃R�[�h����ǂݔ�΂�
		SkillSeqInc(sp,1);

		//adrs�����[�h
		adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
		OS_TPrintf("POKEMON_LIST_CALL_WAIT adrs:%d\n",adrs);
#endif

		//�L�����Z��
		if(res==SELECT_CANCEL){
			SkillSeqInc(sp,adrs);
		}
		else{
			sp->reshuffle_sel_mons_no[CLIENT_NO_MINE]=res-1;
		}
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_WIN_LOSE_SET(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	if(BattleWorkFightTypeGet(bw)&FIGHT_TYPE_SIO){
		SCIO_WinLoseFlagSet(bw);
	}

	return FALSE;
}
//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_STEALTHROCK_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	side;
	int	adrs;
	int	client_no;
	int	dir;
	int	type1;
	int	type2;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//side�����[�h
	side=SkillSeqDataRead(sp);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("STEALTHROCK_CHECK side:%d adrs:%d\n",side,adrs);
#endif

	client_no=SideClientNoGet(bw,sp,side);
	dir=BattleWorkMineEnemyCheck(bw,client_no);
	type1=ST_ServerPokemonServerParamGet(sp,client_no,ID_PSP_type1,NULL);
	type2=ST_ServerPokemonServerParamGet(sp,client_no,ID_PSP_type2,NULL);

	if((sp->side_condition[dir]&SIDE_CONDITION_STEALTHROCK)&&(sp->psp[client_no].hp)){
		switch(ST_ServerTypeCheckTablePowerGet(IWA_TYPE,type1,type2)){
		case AISYOU_4BAI:		//4�{����
			sp->hp_calc_work=2;
			break;
		case AISYOU_2BAI:		//2�{����
			sp->hp_calc_work=4;
			break;
		case AISYOU_1BAI:		//1�{����
			sp->hp_calc_work=8;
			break;
		case AISYOU_1_2BAI:		//1/2�{����
			sp->hp_calc_work=16;
			break;
		case AISYOU_1_4BAI:		//1/4�{����
			sp->hp_calc_work=32;
			break;
		case AISYOU_0BAI:		//���ʂȂ�
			SkillSeqInc(sp,adrs);
			return FALSE;
		default:
			GF_ASSERT(0);
			break;
		}
		sp->hp_calc_work=ST_ServerDamageDiv(sp->psp[client_no].hpmax*-1,sp->hp_calc_work);
	}
	else{
		SkillSeqInc(sp,adrs);
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_ADD_STATUS_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	adrs;
	u16	kakuritsu;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

	//����\�͂Ă�̂߂��݂́A�m����{�ɂ���
	if(ST_ServerTokuseiGet(sp,sp->attack_client)==TOKUSYU_TENNOMEGUMI){
//		kakuritsu=WT_WazaDataParaGet(sp->waza_no_now,ID_WTD_addeffect)*2;
		kakuritsu=sp->AIWT.wtd[sp->waza_no_now].addeffect*2;
	}
	else{
//		kakuritsu=WT_WazaDataParaGet(sp->waza_no_now,ID_WTD_addeffect);
		kakuritsu=sp->AIWT.wtd[sp->waza_no_now].addeffect;
	}
	//�ԐڂŊm���O�͂��肦�Ȃ��̂ŁA�A�T�[�g
	GF_ASSERT(kakuritsu!=0);
#ifdef PM_DEBUG
	if((((gf_rand()%100)<kakuritsu)||(sp->dbp.debug_flag&DEBUG_FLAG_ADD_STATUS))&&
		 (sp->psp[sp->tsuika_client].hp)){
		return FALSE;
	}
#else
	if(((gf_rand()%100)<kakuritsu)&&
	    (sp->psp[sp->tsuika_client].hp)){
		return FALSE;
	}
#endif PM_DEBUG

	SkillSeqInc(sp,adrs);

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_OSYABERI(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	adrs;
	u16	kakuritsu;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("OSYABERI adrs:%d\n",adrs);
#endif

#ifdef PM_DEBUG
	//�f�o�b�O���[�h�ł�����ׂ胉���N�Œ�̏ꍇ�́A���̒l�Œǉ����ʊm�����v�Z
	if(sp->dbp.osyaberi_rank){
		if((sp->psp[sp->attack_client].monsno==MONSNO_PERAPPU)&&
		   (sp->psp[sp->defence_client].hp)&&
		  ((sp->psp[sp->attack_client].condition2&CONDITION2_HENSHIN)==0)){
			switch(sp->dbp.osyaberi_rank){
			default:
			case 0:
				kakuritsu=0;
				break;
			case 1:
				kakuritsu=10;
				break;
			case 2:
				kakuritsu=30;
				break;
			}
			if((gf_rand()%100)>kakuritsu){
				SkillSeqInc(sp,adrs);
			}
		}
		else{
			SkillSeqInc(sp,adrs);
		}
	}
	else{
		if((sp->psp[sp->attack_client].monsno==MONSNO_PERAPPU)&&
		   (sp->psp[sp->defence_client].hp)&&
		  ((sp->psp[sp->attack_client].condition2&CONDITION2_HENSHIN)==0)){
			switch(Snd_PerapVoiceWazaParamGet(BattleWorkPerapVoiceGet(bw,sp->attack_client))){
			default:
			case 0:
				kakuritsu=0;
				break;
			case 1:
				kakuritsu=10;
				break;
			case 2:
				kakuritsu=30;
				break;
			}
			if((gf_rand()%100)>kakuritsu){
				SkillSeqInc(sp,adrs);
			}
		}
		else{
			SkillSeqInc(sp,adrs);
		}
	}
#else
	if((sp->psp[sp->attack_client].monsno==MONSNO_PERAPPU)&&
	   (sp->psp[sp->defence_client].hp)&&
	  ((sp->psp[sp->attack_client].condition2&CONDITION2_HENSHIN)==0)){
		switch(Snd_PerapVoiceWazaParamGet(BattleWorkPerapVoiceGet(bw,sp->attack_client))){
		default:
		case 0:
			kakuritsu=0;
			break;
		case 1:
			kakuritsu=10;
			break;
		case 2:
			kakuritsu=30;
			break;
		}
		if((gf_rand()%100)>kakuritsu){
			SkillSeqInc(sp,adrs);
		}
	}
	else{
		SkillSeqInc(sp,adrs);
	}
#endif

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_WAZA_PARAM_GET(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	id;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//id�����[�h
	id=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("WAZA_PARAM_GET id:%d\n",id);
#endif

//	sp->calc_work=WT_WazaDataParaGet(sp->waza_no_now,id);
	sp->calc_work=WT_WazaDataParaGetAct(&sp->AIWT.wtd[sp->waza_no_now],id);
	
	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_MOSAIC(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	side;
	int	para;
	int	wait;
	int	client_no;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//side�����[�h
	side=SkillSeqDataRead(sp);

	//para�����[�h
	para=SkillSeqDataRead(sp);

	//wait�����[�h
	wait=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("MOSAIC side:%d para:%d wait:%d\n",side,para,wait);
#endif

	client_no=SideClientNoGet(bw,sp,side);

	SCIO_MosaicSet(bw,client_no,para,wait);

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_FORM_CHG(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	side;
	int	client_no;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//side�����[�h
	side=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("FORM_CHG side:%d\n",side);
#endif

	client_no=SideClientNoGet(bw,sp,side);

	SCIO_FormChgSet(bw,client_no);

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_BG_CHG(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	SCIO_BGChgSet(bw,CLIENT_NO_MINE);

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_STATUS_RECOVER(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	side;
	int	client_no;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//side�����[�h
	side=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("STATUS_RECOVER side:%d\n",side);
#endif

	client_no=SideClientNoGet(bw,sp,side);

	BattleWorkStatusRecover(bw,client_no,sp->sel_mons_no[client_no],NULL,sp->item_work);

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_ESCAPE_ACT_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	side;
	int	client_no;
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//side�����[�h
	side=SkillSeqDataRead(sp);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("ESCAPE_ACT_CHECK side:%d adrs:%d\n",side,adrs);
#endif

	client_no=SideClientNoGet(bw,sp,side);

	if(ST_EscapeActCheck(bw,sp,client_no)){
		SkillSeqInc(sp,adrs);
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_BALL_GAUGE_ENCOUNT_SET(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	side;
	int	client_no;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//side�����[�h
	side=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("BALL_GAUGE_ENCOUNT_SET side:%d\n",side);
#endif

	client_no=SideClientNoGet(bw,sp,side);

	SCIO_BallGaugeEncountSet(bw,client_no);

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_BALL_GAUGE_ENCOUNT_OUT(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	side;
	int	client_no;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//side�����[�h
	side=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("BALL_GAUGE_ENCOUNT_SET side:%d\n",side);
#endif

	client_no=SideClientNoGet(bw,sp,side);

	SCIO_BallGaugeEncountOut(bw,client_no);

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_BALL_GAUGE_SET(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	side;
	int	client_no;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//side�����[�h
	side=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("BALL_GAUGE_SET side:%d\n",side);
#endif

	client_no=SideClientNoGet(bw,sp,side);

	SCIO_BallGaugeSet(bw,client_no);

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_BALL_GAUGE_OUT(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	side;
	int	client_no;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//side�����[�h
	side=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("BALL_GAUGE_OUT side:%d\n",side);
#endif

	client_no=SideClientNoGet(bw,sp,side);

	SCIO_BallGaugeOut(bw,client_no);

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_BALL_GAUGE_RESOURCE_LOAD(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("BALL_GAUGE_RESOURCE_LOAD\n");
#endif

	SCIO_BallGaugeResourceLoad(bw);

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_BALL_GAUGE_RESOURCE_DELETE(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("BALL_GAUGE_RESOURCE_DELETE\n");
#endif

	SCIO_BallGaugeResourceDelete(bw);

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_INC_RECORD(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	side;
	int	flag;
	int	id;
	int	client_no;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//side�����[�h
	side=SkillSeqDataRead(sp);

	//flag�����[�h
	flag=SkillSeqDataRead(sp);

	//id�����[�h
	id=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("INC_RECORD side:%d flag:%d id:%d\n",side,flag,id);
#endif

	client_no=SideClientNoGet(bw,sp,side);

	SCIO_IncRecord(bw,client_no,flag,id);

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_CHR_POP(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	side;
	int	client_no;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//side�����[�h
	side=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("CHR_POP side:%d\n",side);
#endif

	client_no=SideClientNoGet(bw,sp,side);

	SCIO_ChrPop(bw,sp,client_no);

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_WAZA_HIT_TOKUSEI_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("WAZA_HIT_TOKUSEI_CHECK adrs:%d\n",adrs);
#endif

	//�Z���q�b�g�����Ƃ��Ƀ`�F�b�N����������`�F�b�N
	if(ST_ServerWazaHitTokuseiCheck(bw,sp,&sp->temp_work)==FALSE){
		SkillSeqInc(sp,adrs);
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_SS_TO_OAM_CALL(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int				side;
	int				client_no;
	CLIENT_PARAM	*cp;
	int				client_set_max=BattleWorkClientSetMaxGet(bw);

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//side�����[�h
	side=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("SS_TO_OAM_CALL side:%d\n",side);
#endif

	switch(side){
	case SIDE_MINE:
		for(client_no=0;client_no<client_set_max;client_no++){
			cp=BattleWorkClientParamGet(bw,client_no);
			if((cp->client_type&CLIENT_ENEMY_FLAG)==0){
				SCIO_SStoOAMCall(bw,client_no);
			}
		}
		break;
	case SIDE_ENEMY:
		for(client_no=0;client_no<client_set_max;client_no++){
			cp=BattleWorkClientParamGet(bw,client_no);
			if(cp->client_type&CLIENT_ENEMY_FLAG){
				SCIO_SStoOAMCall(bw,client_no);
			}
		}
		break;
	default:
		client_no=SideClientNoGet(bw,sp,side);
		SCIO_SStoOAMCall(bw,client_no);
		break;
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_OAM_TO_SS_CALL(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int				side;
	int				client_no;
	CLIENT_PARAM	*cp;
	int				client_set_max=BattleWorkClientSetMaxGet(bw);

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//side�����[�h
	side=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("SS_TO_OAM_CALL side:%d\n",side);
#endif

	switch(side){
	case SIDE_MINE:
		for(client_no=0;client_no<client_set_max;client_no++){
			cp=BattleWorkClientParamGet(bw,client_no);
			if((cp->client_type&CLIENT_ENEMY_FLAG)==0){
				SCIO_OAMtoSSCall(bw,client_no);
			}
		}
		break;
	case SIDE_ENEMY:
		for(client_no=0;client_no<client_set_max;client_no++){
			cp=BattleWorkClientParamGet(bw,client_no);
			if(cp->client_type&CLIENT_ENEMY_FLAG){
				SCIO_OAMtoSSCall(bw,client_no);
			}
		}
		break;
	default:
		client_no=SideClientNoGet(bw,sp,side);
		SCIO_OAMtoSSCall(bw,client_no);
		break;
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_ZENMETSU_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int				side;
	int				adrs;
	int				client_no;
	int				i;
	int				hp=0;
	u32				fight_type;
	POKEMON_PARAM	*pp;
	CLIENT_PARAM	*cp;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//side�����[�h
	side=SkillSeqDataRead(sp);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("ZENMETSU_CHECK side:%d adrs:%d\n",side,adrs);
#endif

	fight_type=BattleWorkFightTypeGet(bw);
	client_no=SideClientNoGet(bw,sp,side);

	if((fight_type&FIGHT_TYPE_MULTI)||((fight_type&FIGHT_TYPE_TAG)&&(BattleWorkMineEnemyCheck(bw,client_no)))){
		{
			POKEPARTY		*poke_party1;
			POKEPARTY		*poke_party2;
	
			poke_party1=BattleWorkPokePartyGet(bw,client_no);
			poke_party2=BattleWorkPokePartyGet(bw,BattleWorkPartnerClientNoGet(bw,client_no));
			cp=BattleWorkClientParamGet(bw,client_no);

			for(i=0;i<PokeParty_GetPokeCount(poke_party1);i++){
				pp=PokeParty_GetMemberPointer(poke_party1,i);
				if((PokeParaGet(pp,ID_PARA_monsno_egg,NULL)!=0)&&
				   (PokeParaGet(pp,ID_PARA_monsno_egg,NULL)!=MONSNO_TAMAGO)){
					hp+=PokeParaGet(pp,ID_PARA_hp,NULL);
				}
			}
			//AI�}���`��ł́A�����������ŏ��s�����߂�
			if(((fight_type==FIGHT_TYPE_AI_MULTI)||
			    (fight_type==FIGHT_TYPE_BATTLE_TOWER_AI_MULTI)||
			    (fight_type==FIGHT_TYPE_2vs2_YASEI))&&
				(BattleWorkMineEnemyCheck(bw,client_no)==0)){
				;
			}
			else{
				for(i=0;i<PokeParty_GetPokeCount(poke_party2);i++){
					pp=PokeParty_GetMemberPointer(poke_party2,i);
					if((PokeParaGet(pp,ID_PARA_monsno_egg,NULL)!=0)&&
					   (PokeParaGet(pp,ID_PARA_monsno_egg,NULL)!=MONSNO_TAMAGO)){
						hp+=PokeParaGet(pp,ID_PARA_hp,NULL);
					}
				}
			}

			if(hp==0){
				SkillSeqInc(sp,adrs);
			}
		}
	}
	else{
		{
			POKEPARTY		*poke_party;

			poke_party=BattleWorkPokePartyGet(bw,client_no);
			cp=BattleWorkClientParamGet(bw,client_no);
	
			for(i=0;i<PokeParty_GetPokeCount(poke_party);i++){
				pp=PokeParty_GetMemberPointer(poke_party,i);
				if((PokeParaGet(pp,ID_PARA_monsno_egg,NULL)!=0)&&
				   (PokeParaGet(pp,ID_PARA_monsno_egg,NULL)!=MONSNO_TAMAGO)){
					hp+=PokeParaGet(pp,ID_PARA_hp,NULL);
				}
			}

			if(hp==0){
				SkillSeqInc(sp,adrs);
			}
		}
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_TUBOWOTUKU(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	i,cnt;
	int	abirity[COND_MAX];
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

	cnt=0;
	for(i=COND_POW;i<COND_MAX;i++){
		if(sp->psp[sp->defence_client].abiritycnt[i]<12){
			abirity[cnt++]=i-1;
		}
	}

	if(cnt){
		sp->add_status_flag_direct=ADD_COND2_POWUP2+abirity[gf_rand()%cnt];
		sp->add_status_flag_direct|=ADD_STATUS_DEFENCE;
	}
	else{
		SkillSeqInc(sp,adrs);
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_KILL_ITEM(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	side;
	int	client_no;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//side�����[�h
	side=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("KILL_ITEM side:%d\n",side);
#endif

	client_no=SideClientNoGet(bw,sp,side);

	sp->recycle_item[client_no]=sp->psp[client_no].item;

	sp->psp[client_no].item=0;

	ST_PSPtoPPCopy(bw,sp,client_no);

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_RECYCLE(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("RECYCLE adrs:%d\n",adrs);
#endif

	if(sp->recycle_item[sp->attack_client]){
		sp->item_work=sp->recycle_item[sp->attack_client];
		sp->recycle_item[sp->attack_client]=0;
	}
	else{
		SkillSeqInc(sp,adrs);
	}
	
	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_WAZA_HIT_SOUBI_ITEM_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("WAZA_HIT_SOUBI_ITEM_CHECK adrs:%d\n",adrs);
#endif

	//�Z���q�b�g�����Ƃ��Ƀ`�F�b�N����������`�F�b�N
	if(ST_ServerWazaHitSoubiItemCheck(bw,sp,&sp->temp_work)==FALSE){
		SkillSeqInc(sp,adrs);
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_WIN_LOSE_MESSAGE(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("WIN_LOSE_MESSAGE\n");
#endif

	SCIO_WinLoseMessage(bw);

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_ESCAPE_MESSAGE(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("ESCAPE_MESSAGE\n");
#endif

	SCIO_EscapeMessage(bw,sp);

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_GIVEUP_MESSAGE(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("GIVEUP_MESSAGE\n");
#endif

	SCIO_GiveUpMessage(bw);

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_HP1_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	side;
	int	client_no;
	int	eqp;
	int	atk;
	int	flag=0;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//side�����[�h
	side=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("HP1_CEHCK side:%d\n",side);
#endif

	client_no=SideClientNoGet(bw,sp,side);
	eqp=ST_ServerSoubiEqpGet(sp,client_no);
	atk=ST_ServerSoubiAtkGet(sp,client_no,ATK_CHECK_NORMAL);

#ifdef PM_DEBUG
	if((eqp==SOUBI_HPITIDETAERU)&&(((gf_rand()%100)<atk)||(sp->dbp.debug_flag&DEBUG_FLAG_SOUBI))){
#else
	if((eqp==SOUBI_HPITIDETAERU)&&((gf_rand()%100)<atk)){
#endif
		flag=1;
	}
	if((eqp==SOUBI_HPMAXDEITIGEKISISINAI)&&(sp->psp[client_no].hp==sp->psp[client_no].hpmax)){
		flag=1;
	}
	if(flag){
		//�C�₵�Ă��܂����́A�P�c���悤�ɂ���
		if((sp->psp[client_no].hp+sp->hp_calc_work)<=0){
			sp->hp_calc_work=(sp->psp[client_no].hp-1)*-1;
			sp->waza_status_flag|=WAZA_STATUS_FLAG_ITEM_KORAETA;
		}
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_SIZENKAIHUKU_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int				side;
	int				client_no;
	int				adrs;
	POKEMON_PARAM	*pp;
	int				tokusei;
	int				condition;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//side�����[�h
	side=SkillSeqDataRead(sp);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("SIZENKAIHUKU_CHECK side:%d adrs:%d\n",side,adrs);
#endif

	client_no=SideClientNoGet(bw,sp,side);
	if((sp->psp[client_no].hp)&&(sp->sel_mons_no[client_no]!=POKEMON_TEMOTI_MAX)){
		pp=BattleWorkPokemonParamGet(bw,client_no,sp->sel_mons_no[client_no]);
		tokusei=PokeParaGet(pp,ID_PARA_speabino,NULL);
		condition=PokeParaGet(pp,ID_PARA_condition,NULL);
		if((sp->psp[client_no].speabino!=TOKUSYU_SIZENKAIHUKU)&&
		   (ST_ServerTokuseiStatusRecoverReshuffleCheck(sp,tokusei,condition)==FALSE)){
			SkillSeqInc(sp,adrs);
		}
	}
	else{
		SkillSeqInc(sp,adrs);
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_MIGAWARI_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	side;
	int	client_no;
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//side�����[�h
	side=SkillSeqDataRead(sp);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("MIGAWARI_CHECK side:%d adrs:%d\n",side,adrs);
#endif

	client_no=SideClientNoGet(bw,sp,side);

	if((sp->psp[client_no].condition2&CONDITION2_MIGAWARI)||
	   (sp->ostf[client_no].status_flag&OSTF_STATUS_FLAG_MIGAWARI_HIT)){
		SkillSeqInc(sp,adrs);
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_NOOTENKI_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	side;
	int	client_no;
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("NOOTENKI_CHECK adrs:%d\n",adrs);
#endif

	if((ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ALL_HP,0,TOKUSYU_NOOTENKI)==0)&&
	   (ST_ServerTokuseiCheck(bw,sp,STC_HAVE_ALL_HP,0,TOKUSYU_EAROKKU)==0)){
		;
	}
	else{
		SkillSeqInc(sp,adrs);
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_DIR_CLIENT_GET(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	side;
	int	client_no;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//side�����[�h
	side=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("DIR_CLIENT_GET side:%d\n",side);
#endif

	client_no=SideClientNoGet(bw,sp,side);

	sp->defence_client=ST_ServerDirClientGet(bw,sp,client_no);

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_WAZA_HIT_SOUBI_ITEM_CHECK_TONBOGAERI(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("WAZA_HIT_SOUBI_ITEM_CHECK adrs:%d\n",adrs);
#endif

	//�Z���q�b�g�����Ƃ��Ƀ`�F�b�N����������`�F�b�N
	if(ST_ServerWazaHitSoubiItemCheckTonbogaeri(bw,sp,&sp->temp_work)==FALSE){
		SkillSeqInc(sp,adrs);
	}

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_MIGAWARI_CHR_SET(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	side;
	int	client_no;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//side�����[�h
	side=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("MIGAWARI_CHR_SET side:%d\n",side);
#endif

	client_no=SideClientNoGet(bw,sp,side);

	SCIO_MigawariChrSet(bw,sp,client_no);

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_WAZAKOUKA_SE(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	side;
	int	client_no;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//side�����[�h
	side=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("WAZAKOUKA_SE side:%d\n",side);
#endif

	client_no=SideClientNoGet(bw,sp,side);

	SCIO_WazaKoukaSESet(bw,sp,client_no);

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_BGM_PLAY(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	side;
	int	bgm_no;
	int	client_no;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//side�����[�h
	side=SkillSeqDataRead(sp);

	//bgm_no�����[�h
	bgm_no=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("BGM_SET side:%d bgm_no:%d\n",side,bgm_no);
#endif

	client_no=SideClientNoGet(bw,sp,side);

	SCIO_BGMPlay(bw,client_no,bgm_no);

	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_SAFARI_END_CHECK(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	adrs;

	//���߃R�[�h����ǂݔ�΂�
	SkillSeqInc(sp,1);

	//adrs�����[�h
	adrs=SkillSeqDataRead(sp);

#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("SAFARI_END_CHECK adrs:%d\n",adrs);
#endif

	if(((BattleWorkPokeCountGet(bw,CLIENT_NO_MINE)!=6)||
		(BOXDAT_GetEmptyTrayNumber(bw->box)!=BOXDAT_TRAYNUM_ERROR))&&
		(bw->safari_ball)){
		SkillSeqInc(sp,adrs);
	}
	return FALSE;
}

//============================================================================================
/**
 * @param[in]	bw	�퓬�p���[�N�\����
 * @param[in]	sp	�T�[�o�p�p�����[�^���[�N�\����
 */
//============================================================================================
static	BOOL	WS_SEQ_END(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
#ifdef DEBUG_PRINT_BATTLE
	OS_TPrintf("SEQ_END\n");
#endif

	return	ST_ServerSequencePushCheck(sp);
}

//============================================================================================
/**
 *	�V�[�P���X�f�[�^���[�N����f�[�^�����[�h
 *
 * @param[in]	sp	�T�[�o���[�N�\����
 */
//============================================================================================
static	int		SkillSeqDataRead(SERVER_PARAM *sp)
{
	int	data;

	data=sp->SkillSeqWork[sp->skill_seq_no];
	sp->skill_seq_no++;

	return	data;
}

//============================================================================================
/**
 *	�V�[�P���X�f�[�^�C���f�b�N�X���C���N�������g
 *
 * @param[in]	sp	�T�[�o���[�N�\����
 * @param[in]	cnt	�C���N�������g���鐔
 */
//============================================================================================
static	void	SkillSeqInc(SERVER_PARAM *sp,int cnt)
{
	sp->skill_seq_no+=cnt;
}

//============================================================================================
/**
 *	�ʂ̃V�[�P���X�ɃW�����v
 *
 * @param[in]	sp			�T�[�o���[�N�\����
 * @param[in]	arc_kind	�V�[�P���X�f�[�^�̃A�[�J�C�u�̎��
 * @param[in]	adrs		��ѐ�V�[�P���X��INDEX
 */
//============================================================================================
static	void	SkillSequenceJump(SERVER_PARAM *sp,int arc_kind,int adrs)
{
	ST_ServerSequenceLoad(sp,arc_kind,adrs);
}

//============================================================================================
/**
 *	�ʂ̃V�[�P���X�ɃT�u���[�`���W�����v
 *
 * @param[in]	sp			�T�[�o���[�N�\����
 * @param[in]	arc_kind	�V�[�P���X�f�[�^�̃A�[�J�C�u�̎��
 * @param[in]	adrs		��ѐ�V�[�P���X��INDEX
 */
//============================================================================================
static	void	SkillSequenceGosub(SERVER_PARAM *sp,int arc_kind,int adrs)
{
	ST_ServerSequenceLoadGosub(sp,arc_kind,adrs);
}

//============================================================================================
/**
 *	src�p�����[�^�Ɏw�肳�ꂽ�o�b�t�@�̃|�C���^���擾
 *
 * @param[in]	sp			�T�[�o���[�N�\����
 * @param[in]	arc_kind	�V�[�P���X�f�[�^�̃A�[�J�C�u�̎��
 * @param[in]	adrs		��ѐ�V�[�P���X��INDEX
 */
//============================================================================================
static	void	*WS_SrcPointerGet(BATTLE_WORK *bw,SERVER_PARAM *sp,int para)
{
	switch(para){
	case BUF_PARA_FIGHT_TYPE:
		return &bw->fight_type;
	case BUF_PARA_CRITICAL_COUNT:
		return &sp->critical_count;
	case BUF_PARA_ADD_STATUS_DIRECT:
		return &sp->add_status_flag_direct;
	case BUF_PARA_ADD_STATUS_INDIRECT:
		return &sp->add_status_flag_indirect;
	case BUF_PARA_ADD_STATUS_TOKUSEI:
		return &sp->add_status_flag_tokusei;
	case BUF_PARA_TSUIKA_TYPE:
		return &sp->tsuika_type;
	case BUF_PARA_SERVER_STATUS_FLAG:
		return &sp->server_status_flag;
	case BUF_PARA_FIELD_CONDITION:
		return &sp->field_condition;
	case BUF_PARA_DAMAGE_VALUE:
		return &sp->damage_value;
	case BUF_PARA_CALC_WORK:
		return &sp->calc_work;
	case BUF_PARA_WAZA_STATUS_FLAG:
		return &sp->waza_status_flag;
	case BUF_PARA_SIDE_CONDITION_ATTACK:
		return &sp->side_condition[BattleWorkMineEnemyCheck(bw,sp->attack_client)];
	case BUF_PARA_SIDE_CONDITION_DEFENCE:
		return &sp->side_condition[BattleWorkMineEnemyCheck(bw,sp->defence_client)];
	case BUF_PARA_SIDE_CONDITION_TSUIKA:
		return &sp->side_condition[BattleWorkMineEnemyCheck(bw,sp->tsuika_client)];
	case BUF_PARA_DAMAGE:
		return &sp->damage;
	case BUF_PARA_ATTACK_CLIENT:
		return &sp->attack_client;
	case BUF_PARA_DEFENCE_CLIENT:
		return &sp->defence_client;
	case BUF_PARA_TSUIKA_CLIENT:
		return &sp->tsuika_client;
	case BUF_PARA_KIZETSU_CLIENT:
		return &sp->kizetsu_client;
	case BUF_PARA_RESHUFFLE_CLIENT:
		return &sp->reshuffle_client;
	case BUF_PARA_CLIENT_WORK:
		return &sp->client_work;
	case BUF_PARA_STORE_DAMAGE_ATTACK:
		return &sp->store_damage[sp->attack_client];
	case BUF_PARA_MSG_WORK:
		return &sp->msg_work;
	case BUF_PARA_KOBAN_COUNTER:
		return &sp->koban_counter;
	case BUF_PARA_WAZA_NO_NOW:
		return &sp->waza_no_now;
	case BUF_PARA_TOTAL_TURN:
		return &sp->total_turn;
	case BUF_PARA_ATTACK_CLIENT_WORK:
		return &sp->attack_client_work;
	case BUF_PARA_DEFENCE_CLIENT_WORK:
		return &sp->defence_client_work;
	case BUF_PARA_WAZA_NO_TEMP:
		return &sp->waza_no_temp;
	case BUF_PARA_PUSH_CLIENT:
		return &sp->push_client;
	case BUF_PARA_DAMAGE_POWER:
		return &sp->damage_power;
	case BUF_PARA_SWOAM_TYPE:
		return &sp->swoam_type;
	case BUF_PARA_HP_CALC_WORK:
		return &sp->hp_calc_work;
	case BUF_PARA_WIN_LOSE_FLAG:
		return &bw->win_lose_flag;
	case BUF_PARA_TSUIKA_PARA:
		return &sp->tsuika_para;
	case BUF_PARA_WAZA_WORK:
		return &sp->waza_work;
	case BUF_PARA_ITEM_WORK:
		return &sp->item_work;
	case BUF_PARA_TOKUSEI_WORK:
		return &sp->tokusei_work;
	case BUF_PARA_WEATHER_COUNT:
		return &sp->fcc.weather_count;
	case BUF_PARA_CLIENT_NO_AGI:
		return &sp->client_no_agi;
	case BUF_PARA_LOOP_FLAG:
		return &sp->loop_flag;
	case BUF_PARA_BUTSURI_DAMAGE_ATTACK:
		return &sp->otf[sp->attack_client].butsuri_otf_client_bit;
	case BUF_PARA_TOKUSYU_DAMAGE_ATTACK:
		return &sp->otf[sp->attack_client].tokusyu_otf_client_bit;
	case BUF_PARA_TEMP_WORK:
		return &sp->temp_work;
	case BUF_PARA_CRITICAL:
		return &sp->critical;
	case BUF_PARA_LAST_DAMAGE_ATTACK:
		return &sp->otf[sp->attack_client].last_otf_damage;
	case BUF_PARA_LAST_DAMAGE_DEFENCE:
		return &sp->otf[sp->defence_client].last_otf_damage;
	case BUF_PARA_OSTF_STATUS_FLAG_ATTACK:
		return &sp->ostf[sp->attack_client].status_flag;
	case BUF_PARA_OSTF_STATUS_FLAG_DEFENCE:
		return &sp->ostf[sp->defence_client].status_flag;
	case BUF_PARA_OSTF_STATUS_FLAG_TSUIKA:
		return &sp->ostf[sp->tsuika_client].status_flag;
	case BUF_PARA_NAGETSUKERU_WORK:
		return &sp->nagetsukeru_work;
	case BUF_PARA_NAGETSUKERU_SEQ_NO:
		return &sp->nagetsukeru_seq_no;
	case BUF_PARA_BATTLE_STATUS_FLAG:
		return &bw->battle_status_flag;
	case BUF_PARA_WAZA_NO_KEEP_ATTACK:
		return &sp->waza_no_keep[sp->attack_client];
	case BUF_PARA_HIT_DAMAGE:
		return &sp->hit_damage;
	case BUF_PARA_SAFARI_BALL_COUNT:
		return &bw->safari_ball;
	case BUF_PARA_RESHUFFLE_CLIENT_TEMP:
		return &sp->reshuffle_client_temp;
	case BUF_PARA_WAZA_TYPE:
		return &sp->waza_type;
	case BUF_PARA_WAZA_EFF_CNT:
		return &sp->waza_eff_cnt;
	case BUF_PARA_REGULATION_FLAG:
		return &bw->regulation_flag;
	case BUF_PARA_SERVER_STATUS_FLAG2:
		return &sp->server_status_flag2;
	case BUF_PARA_AGI_CNT:
		return &sp->agi_cnt;
	case BUF_PARA_CLIENT_SET_MAX:
		return &bw->client_set_max;
	case BUF_PARA_ATTACK_CLIENT_TEMP:
		return &sp->attack_client_temp;
	case BUF_PARA_DEFENCE_CLIENT_TEMP:
		return &sp->defence_client_temp;
	case BUF_PARA_BUTSURI_OSTF_DAMAGE_D:
		return &sp->ostf[sp->defence_client].butsuri_ostf_damage;
	case BUF_PARA_DAMEOSHI_DAMAGE:
		return &sp->otf[sp->client_work].dameoshi_damage;
	case BUF_PARA_DAMEOSHI_DAMAGE_DEFENCE:
		return &sp->otf[sp->defence_client].dameoshi_damage;
	}
	OS_Printf("WS_SrcPointerGet:�����ɂ���̂͊ԈႢ�I\n");
	return NULL;
}

//============================================================================================
/**
 *	TCB�֘A
 */
//============================================================================================
//============================================================================================
/**
 *	GET_EXP�p�V�[�P���X��`
 */
//============================================================================================
enum{
	SEQ_GE_INIT=0,
	SEQ_GE_EXP_MESSAGE_INDEX_WAIT,
	SEQ_GE_EXP_MESSAGE_WAIT,
	SEQ_GE_EXP_GAUGE,
	SEQ_GE_EXP_GAUGE_WAIT,
	SEQ_GE_LEVELUP_CHECK,
	SEQ_GE_LEVELUP_EFFECT_WAIT,
	SEQ_GE_LEVELUP_MSG_INDEX_WAIT,
	SEQ_GE_STATUS_PRINT_INIT1,
	SEQ_GE_STATUS_PRINT_INIT2,
	SEQ_GE_STATUS_PRINT1,
	SEQ_GE_STATUS_PRINT_KEY_WAIT,
	SEQ_GE_STATUS_PRINT2,
	SEQ_GE_STATUS_PRINT_KEY_WAIT2,
	SEQ_GE_STATUS_PRINT_END,
	SEQ_GE_WAZAOBOE_CHECK,
	SEQ_GE_WAZAWASURE_MSG1,
	SEQ_GE_WAZAWASURE_MSG1_WAIT,
	SEQ_GE_WAZAWASURE_MSG2,
	SEQ_GE_WAZAWASURE_MSG2_WAIT,
	SEQ_GE_WAZAWASURE_YES_NO_INIT,
	SEQ_GE_WAZAWASURE_YES_NO,
	SEQ_GE_WAZAWASURE_SELECT_INIT,
	SEQ_GE_WAZAWASURE_SELECT,
	SEQ_GE_WAZAWASURE_ACT_MSG1,
	SEQ_GE_WAZAWASURE_ACT_MSG1_WAIT,
	SEQ_GE_WAZAWASURE_ACT_MSG2,
	SEQ_GE_WAZAWASURE_ACT_MSG2_WAIT,
	SEQ_GE_WAZAWASURE_ACT_MSG3,
	SEQ_GE_WAZAWASURE_ACT_MSG3_WAIT,
	SEQ_GE_WAZAWASURE_ACT_MSG4,
	SEQ_GE_WAZAAKIRAME_MSG1,
	SEQ_GE_WAZAAKIRAME_MSG1_WAIT,
	SEQ_GE_WAZAAKIRAME_INIT,
	SEQ_GE_WAZAAKIRAME,
	SEQ_GE_WAZAAKIRAME_ACT,
	SEQ_GE_WAZAOBOE_MSG_INDEX_WAIT,
	SEQ_GE_END_CHECK,
	SEQ_GE_END
};

//============================================================================================
/**
 *	�o���l�l���pTCB
 *
 * @param[in]	tcb		TCB�V�X�e�����[�N
 * @param[in]	work	���[�N�G���A�|�C���^
 */
//============================================================================================
static	void	TCB_GetExp(TCB_PTR tcb,void *work)
{
	int					i;
	int					sel_mons_no;
	TCB_SKILL_INTP_WORK	*tsiw=work;
	POKEMON_PARAM		*pp;
	MESSAGE_PARAM		mp;
	int					client_no;
	int					exp_client_no;
	MSGDATA_MANAGER		*msg_m;
	u32					fight_type;
	int					itemno;
	int					eqp;

	msg_m=BattleWorkFightMsgGet(tsiw->bw);
	fight_type=BattleWorkFightTypeGet(tsiw->bw);
	client_no=(tsiw->sp->kizetsu_client)>>1&1;
	exp_client_no=CLIENT_NO_MINE;

	for(sel_mons_no=tsiw->work[GE_SEL_MONS_NO];sel_mons_no<BattleWorkPokeCountGet(tsiw->bw,exp_client_no);sel_mons_no++){
		pp=BattleWorkPokemonParamGet(tsiw->bw,exp_client_no,sel_mons_no);
		itemno=PokeParaGet(pp,ID_PARA_item,NULL);
		eqp=ItemParamGet(itemno,ITEM_PRM_EQUIP,HEAPID_BATTLE);
		if((eqp==SOUBI_KEIKENTIGET)||(tsiw->sp->get_exp_right_flag[client_no]&No2Bit(sel_mons_no))){
			break;
		}
	}
	if(sel_mons_no==BattleWorkPokeCountGet(tsiw->bw,exp_client_no)){
		tsiw->seq_no=SEQ_GE_END;
	}
	else if((fight_type&FIGHT_TYPE_2vs2)&&((fight_type&FIGHT_TYPE_AI)==0)){
		if(tsiw->sp->sel_mons_no[CLIENT_NO_MINE2]==sel_mons_no){
			exp_client_no=CLIENT_NO_MINE2;
		}
	}

	switch(tsiw->seq_no){
	case SEQ_GE_INIT:
		{
			u32				get_exp_total;
			u32				exp;

			itemno=PokeParaGet(pp,ID_PARA_item,NULL);
			eqp=ItemParamGet(itemno,ITEM_PRM_EQUIP,HEAPID_BATTLE);


			//�쐶�|�P�����Ƃ̐퓬�ł�
			//�o���l���炦�鎞�_�ŏ������y
			if(((fight_type&FIGHT_TYPE_TRAINER)==0)&&
			   ((tsiw->sp->psp[CLIENT_NO_ENEMY].hp+tsiw->sp->psp[CLIENT_NO_ENEMY2].hp)==0)&&
				(PokeParaGet(pp,ID_PARA_hp,NULL))&&
			    (tsiw->sp->jingle_flag==0)){
				Snd_BgmPlay(SEQ_WINPOKE);
			    tsiw->sp->jingle_flag=1;
				BattleWorkPinchSEFlagSet(tsiw->bw,2);
			}

			get_exp_total=0;
			//�o���l�擾���b�Z�[�W�Z�b�g
			mp.msg_id=KeikentiGetMsg;

			if((PokeParaGet(pp,ID_PARA_hp,NULL))&&(PokeParaGet(pp,ID_PARA_level,NULL)!=100)){

				if(tsiw->sp->get_exp_right_flag[client_no]&No2Bit(sel_mons_no)){
					get_exp_total=tsiw->sp->get_exp;
				}
	
				//�w�K���u�������Ă�����A���̕���ǉ�
				if(eqp==SOUBI_KEIKENTIGET){
					get_exp_total+=tsiw->sp->gakusyuu_get_exp;
				}
				//�o���l����������ʂ̃A�C�e���������Ă�����A1.5�{��
				if(eqp==SOUBI_KEIKENTIHUERU){
					get_exp_total=get_exp_total*150/100;
				}
				//�g���[�i�[�킾������A1.5�{��
				if(fight_type&FIGHT_TYPE_TRAINER){
					get_exp_total=get_exp_total*150/100;
				}
				//�l�����������|�P������������A1.5�{��
				if(ST_ServerPokeOneSelfCheckActPP(tsiw->bw,pp)==FALSE){
					//����ɈႤ���̃|�P������������A1.7�{��
					if(PokeParaGet(pp,ID_PARA_country_code,NULL)!=CasetteLanguage){
						get_exp_total=get_exp_total*170/100;
					}
					else{
						get_exp_total=get_exp_total*150/100;
					}
					mp.msg_id=KeikentiGetOomeMsg;
				}
				exp=PokeParaGet(pp,ID_PARA_exp,NULL);
				tsiw->work[GE_NOW_EXP]=exp-PokeParaLevelExpGet(pp);
				exp+=get_exp_total;
				if(sel_mons_no==tsiw->sp->sel_mons_no[exp_client_no]){
					tsiw->sp->psp[exp_client_no].exp=exp;
				}
				PokeParaPut(pp,ID_PARA_exp,(u8 *)&exp);

				PokeExpCalc(BattleWorkPokePartyGet(tsiw->bw,exp_client_no),
							sel_mons_no,
							tsiw->sp->psp[tsiw->sp->kizetsu_client].monsno);
			}

			if(get_exp_total){
				mp.msg_tag=TAG_NICK_NUM;
				mp.msg_para[0]=exp_client_no|(sel_mons_no<<8);
				mp.msg_para[1]=get_exp_total;
				tsiw->work[GE_MSG_INDEX]=BattleMSG_Print(tsiw->bw,msg_m,&mp,BattleWorkConfigMsgSpeedGet(tsiw->bw));
				tsiw->work[GE_MSG_WAIT]=MSG_WAIT;
				tsiw->seq_no++;
			}
			else{
				tsiw->seq_no=SEQ_GE_END_CHECK;
			}
		}
		break;
	case SEQ_GE_EXP_MESSAGE_INDEX_WAIT:
		if(GF_MSG_PrintEndCheck(tsiw->work[GE_MSG_INDEX])==0){
			tsiw->seq_no++;
		}
		break;
	case SEQ_GE_EXP_MESSAGE_WAIT:
		if(--tsiw->work[GE_MSG_WAIT]==0){
			tsiw->seq_no++;
		}
		break;
	case SEQ_GE_EXP_GAUGE:
		if(sel_mons_no==tsiw->sp->sel_mons_no[exp_client_no]){
			SCIO_EXPGaugeCalcSet(tsiw->bw,tsiw->sp,exp_client_no,tsiw->work[GE_NOW_EXP]);
			tsiw->work[GE_NOW_EXP]=0;
			tsiw->seq_no++;
		}
		else{
			tsiw->seq_no=SEQ_GE_LEVELUP_CHECK;
		}
		break;
	case SEQ_GE_EXP_GAUGE_WAIT:
		if(ST_ServerQueCheck(tsiw->sp)){
			tsiw->seq_no++;
		}
		break;
	case SEQ_GE_LEVELUP_CHECK:
		if(PokeLevelUpCheck(pp)){
			if(tsiw->sp->sel_mons_no[exp_client_no]==sel_mons_no){
				SCIO_StatusEffectSet(tsiw->bw,tsiw->sp,exp_client_no,STATUS_LVUP);
				SCIO_LevelUpEffectSet(tsiw->bw,exp_client_no);
			}
			tsiw->seq_no=SEQ_GE_LEVELUP_EFFECT_WAIT;
		}
		else{
			tsiw->seq_no=SEQ_GE_END_CHECK;
		}
		break;
	case SEQ_GE_LEVELUP_EFFECT_WAIT:
		if(ST_ServerQueCheck(tsiw->sp)){
			{
				int					level;
				int					status_id[6]={ID_PARA_hpmax,ID_PARA_pow,ID_PARA_def,
												  ID_PARA_spepow,ID_PARA_spedef,ID_PARA_agi};
				PUSH_POKEMON_PARAM	*ppp;

				level=PokeParaGet(pp,ID_PARA_level,NULL);

				tsiw->sp->work=sys_AllocMemory(HEAPID_BATTLE,sizeof(PUSH_POKEMON_PARAM));
				ppp=(PUSH_POKEMON_PARAM *)tsiw->sp->work;

				for(i=0;i<6;i++){
					ppp->para[i]=PokeParaGet(pp,status_id[i],NULL);
				}

				FriendCalc(pp,FRIEND_LEVELUP,BattleWorkPlaceIDGet(tsiw->bw));
				PokeParaCalcLevelUp(pp);
				if(tsiw->sp->sel_mons_no[exp_client_no]==sel_mons_no){
					ST_PokemonParamReload(tsiw->bw,tsiw->sp,exp_client_no,tsiw->sp->sel_mons_no[exp_client_no]);
				}
				tsiw->sp->level_up_pokemon|=No2Bit(sel_mons_no);
				SCIO_HPGaugeRefreshSet(tsiw->bw,tsiw->sp,exp_client_no);

				mp.msg_id=LevelUpMsg;
				mp.msg_tag=TAG_NICK_NUM;
				mp.msg_para[0]=exp_client_no|(sel_mons_no<<8);
				mp.msg_para[1]=level;
				tsiw->work[GE_MSG_INDEX]=BattleMSG_Print(tsiw->bw,msg_m,&mp,BattleWorkConfigMsgSpeedGet(tsiw->bw));
				tsiw->seq_no=SEQ_GE_LEVELUP_MSG_INDEX_WAIT;
			}
		}
		break;
	case SEQ_GE_LEVELUP_MSG_INDEX_WAIT:
		if(GF_MSG_PrintEndCheck(tsiw->work[GE_MSG_INDEX])==0){
			tsiw->seq_no=SEQ_GE_STATUS_PRINT_INIT1;
			tsiw->work[GE_WAZA_CNT]=0;
		}
		break;
	case SEQ_GE_STATUS_PRINT_INIT1:
		if(tsiw->sp->sel_mons_no[exp_client_no]!=sel_mons_no){
			//�T���̃��x���A�b�v
			BenchLevelUpPokeIconActorSet(tsiw->bw,tsiw,pp);
		}
		tsiw->seq_no=SEQ_GE_STATUS_PRINT_INIT2;
		break;
	case SEQ_GE_STATUS_PRINT_INIT2:
		{
			GF_BGL_INI			*bgl;
			GF_BGL_BMPWIN		*win;
			PALETTE_FADE_PTR	pfd;

			bgl=BattleWorkGF_BGL_INIGet(tsiw->bw);
			win=BattleWorkGF_BGL_BMPWINGet(tsiw->bw,MENU_WIN_NO);
			pfd=BattleWorkPfdGet(tsiw->bw);

			G2_SetBG0Priority(BATTLE_3DBG_PRIORITY+1);
			GF_BGL_PrioritySet(BATTLE_FRAME_WINDOW,BATTLE_BGPRI_EFFECT);
			GF_BGL_PrioritySet(BATTLE_FRAME_EFFECT,BATTLE_BGPRI_WINDOW);

			BattleGaugePriSet(tsiw->bw,GAUGE_DEFAULT_BGPRI+2);

			MenuWinCgxSet(bgl,GF_BGL_FRAME2_M,MENU_WIN_CGX_START,MENU_TYPE_SYSTEM,HEAPID_BATTLE);
			PaletteWorkSet_Arc(pfd, ARC_WINFRAME, MenuWinPalArcGet(), HEAPID_BATTLE, 
							FADE_MAIN_BG, 0x20, MENU_WIN_PAL_NO*0x10);
			GF_BGL_BmpWinAdd(bgl,win,GF_BGL_FRAME2_M,
							 MENU_WIN_X,MENU_WIN_Y,MENU_WIN_SIZE_X,MENU_WIN_SIZE_Y,MENU_MSG_PAL_NO,MENU_MSG_START);
			GF_BGL_BmpWinDataFill(win,0xff);
			BmpMenuWinWrite(win,WINDOW_TRANS_ON,MENU_WIN_CGX_START,MENU_WIN_PAL_NO);

			tsiw->seq_no=SEQ_GE_STATUS_PRINT1;

		}
		break;
	case SEQ_GE_STATUS_PRINT1:
		{
			int					status_msg[6]={STATUS_008,STATUS_001,STATUS_002,STATUS_004,STATUS_005,STATUS_003};
			int					status_id[6]={ID_PARA_hpmax,ID_PARA_pow,ID_PARA_def,ID_PARA_spepow,ID_PARA_spedef,ID_PARA_agi};
			GF_BGL_BMPWIN		*win;
			PUSH_POKEMON_PARAM	*ppp;

			win=BattleWorkGF_BGL_BMPWINGet(tsiw->bw,MENU_WIN_NO);
			ppp=(PUSH_POKEMON_PARAM *)tsiw->sp->work;

			for(i=0;i<6;i++){
				mp.msg_id=LevelUpStatusMsg;
				mp.msg_tag=TAG_STAT;
				mp.msg_para[0]=status_msg[i];
				StatusMSG_Print(tsiw->bw,win,msg_m,&mp,0,16*i,0,0,0);
				mp.msg_id=LevelUpStatusUpMsg;
				mp.msg_tag=TAG_NUMS;
				mp.msg_para[0]=PokeParaGet(pp,status_id[i],NULL)-ppp->para[i];
				mp.msg_keta=2;
				StatusMSG_Print(tsiw->bw,win,msg_m,&mp,80,16*i,0,0,0);
			}
			tsiw->seq_no=SEQ_GE_STATUS_PRINT_KEY_WAIT;
		}
		break;
	case SEQ_GE_STATUS_PRINT2:
		{
			int					status_msg[6]={STATUS_008,STATUS_001,STATUS_002,STATUS_004,STATUS_005,STATUS_003};
			int					status_id[6]={ID_PARA_hpmax,ID_PARA_pow,ID_PARA_def,ID_PARA_spepow,ID_PARA_spedef,ID_PARA_agi};
			GF_BGL_BMPWIN		*win;
			PUSH_POKEMON_PARAM	*ppp;

			win=BattleWorkGF_BGL_BMPWINGet(tsiw->bw,MENU_WIN_NO);
			ppp=(PUSH_POKEMON_PARAM *)tsiw->sp->work;

			GF_BGL_BmpWinFill(win,0x0f,80,0,36,96);

			for(i=0;i<6;i++){
				mp.msg_id=LevelUpStatusValueMsg;
				mp.msg_tag=TAG_NUMS;
				mp.msg_para[0]=PokeParaGet(pp,status_id[i],NULL);
				mp.msg_keta=3;
				StatusMSG_Print(tsiw->bw,win,msg_m,&mp,72,16*i,BATTLE_MSG_WIDTH_OFS,36,0);
			}
			tsiw->seq_no=SEQ_GE_STATUS_PRINT_KEY_WAIT2;
		}
		break;
	case SEQ_GE_STATUS_PRINT_KEY_WAIT:
	case SEQ_GE_STATUS_PRINT_KEY_WAIT2:
#ifdef PM_DEBUG
		if(BattleWorkBattleStatusFlagGet(tsiw->bw)&BATTLE_STATUS_FLAG_AUTO_BATTLE){
			Snd_SePlay(BSE_OKURI);
			tsiw->seq_no++;
		}
#endif PM_DEBUG
		if((sys.trg&(PAD_BUTTON_A|PAD_BUTTON_B|PAD_BUTTON_X|PAD_BUTTON_Y))||
		   (GF_TP_GetTrg())){
			Snd_SePlay(BSE_OKURI);
			tsiw->seq_no++;
		}
		break;
	case SEQ_GE_STATUS_PRINT_END:
		{
			GF_BGL_BMPWIN		*win;

			win=BattleWorkGF_BGL_BMPWINGet(tsiw->bw,MENU_WIN_NO);

			BmpMenuWinClear(win,WINDOW_TRANS_ON);
			GF_BGL_BmpWinDel(win);

			G2_SetBG0Priority(BATTLE_3DBG_PRIORITY);
			GF_BGL_PrioritySet(BATTLE_FRAME_WINDOW,BATTLE_BGPRI_WINDOW);
			GF_BGL_PrioritySet(BATTLE_FRAME_EFFECT,BATTLE_BGPRI_EFFECT);

			BattleGaugePriSet(tsiw->bw,GAUGE_DEFAULT_BGPRI);

			if(tsiw->sp->sel_mons_no[exp_client_no]!=sel_mons_no){
				//�T���̃��x���A�b�v
				BenchLevelUpPokeIconActorDelete(tsiw->bw,tsiw);
			}

			sys_FreeMemoryEz(tsiw->sp->work);

			tsiw->seq_no=SEQ_GE_WAZAOBOE_CHECK;
		}
		break;
	case SEQ_GE_WAZAOBOE_CHECK:
		{
			u16	wazano;
			GF_BGL_INI			*bgl=BattleWorkGF_BGL_INIGet(tsiw->bw);

			switch(PokeWazaOboeCheck(pp,&tsiw->work[GE_WAZA_CNT],&wazano)){
			case SAME_WAZA_SET:
				//�����Z�͊o�����Ȃ��̂ŁA�ēx�`�F�b�N�̃��[�v�ɉ�
				break;
			case NO_WAZA_OBOE:
				tsiw->seq_no=SEQ_GE_EXP_GAUGE;
				break;
			case NO_WAZA_SET:
				tsiw->work[GE_WAZANO]=wazano;
				tsiw->seq_no=SEQ_GE_WAZAWASURE_MSG1;
				break;
			default:
				if(tsiw->sp->sel_mons_no[exp_client_no]==sel_mons_no){
					ST_PokemonParamReload(tsiw->bw,tsiw->sp,exp_client_no,tsiw->sp->sel_mons_no[exp_client_no]);
				}
				mp.msg_id=WazaOboeMsg;
				mp.msg_tag=TAG_NICK_WAZA;
				mp.msg_para[0]=exp_client_no|(sel_mons_no<<8);
				mp.msg_para[1]=wazano;
				tsiw->work[GE_MSG_INDEX]=BattleMSG_Print(tsiw->bw,msg_m,&mp,BattleWorkConfigMsgSpeedGet(tsiw->bw));
				tsiw->seq_no=SEQ_GE_WAZAOBOE_MSG_INDEX_WAIT;
				break;
			}
		}
		break;
	case SEQ_GE_WAZAWASURE_MSG1:
		mp.msg_id=battle_WazaOboeMsg1;
		mp.msg_tag=TAG_NICK_WAZA;
		mp.msg_para[0]=exp_client_no|(sel_mons_no<<8);
		mp.msg_para[1]=tsiw->work[GE_WAZANO];
		tsiw->work[GE_MSG_INDEX]=BattleMSG_Print(tsiw->bw,msg_m,&mp,BattleWorkConfigMsgSpeedGet(tsiw->bw));
		tsiw->seq_no++;
		break;
	case SEQ_GE_WAZAWASURE_MSG2:
		mp.msg_id=battle_WazaOboeMsg2;
		mp.msg_tag=TAG_NICK;
		mp.msg_para[0]=exp_client_no|(sel_mons_no<<8);
		tsiw->work[GE_MSG_INDEX]=BattleMSG_Print(tsiw->bw,msg_m,&mp,BattleWorkConfigMsgSpeedGet(tsiw->bw));
		tsiw->seq_no++;
		break;
	case SEQ_GE_WAZAWASURE_MSG1_WAIT:
	case SEQ_GE_WAZAWASURE_MSG2_WAIT:
	case SEQ_GE_WAZAWASURE_ACT_MSG1_WAIT:
	case SEQ_GE_WAZAWASURE_ACT_MSG2_WAIT:
	case SEQ_GE_WAZAWASURE_ACT_MSG3_WAIT:
	case SEQ_GE_WAZAAKIRAME_MSG1_WAIT:
		if(GF_MSG_PrintEndCheck(tsiw->work[GE_MSG_INDEX])==0){
			tsiw->seq_no++;
		}
		break;
	case SEQ_GE_WAZAWASURE_YES_NO_INIT:
		SCIO_YesNoSelectSet(tsiw->bw,tsiw->sp,exp_client_no,battle_WazaWasureMsg1,YNTYPE_WASURE,NULL,NULL);
		tsiw->seq_no++;
		break;
	case SEQ_GE_WAZAWASURE_YES_NO:
		if(ST_ServerBufferResGet(tsiw->sp,exp_client_no)){
			if(ST_ServerBufferResGet(tsiw->sp,exp_client_no)==SELECT_CANCEL){
				tsiw->seq_no=SEQ_GE_WAZAAKIRAME_MSG1;
			}
			else{
				mp.msg_id=battle_WazaWasureMsg2;
				mp.msg_tag=TAG_NONE;
				tsiw->work[GE_MSG_INDEX]=BattleMSG_Print(tsiw->bw,msg_m,&mp,BattleWorkConfigMsgSpeedGet(tsiw->bw));
				tsiw->seq_no=SEQ_GE_WAZAWASURE_SELECT_INIT;
			}
		}
		break;
	case SEQ_GE_WAZAWASURE_SELECT_INIT:
		if(GF_MSG_PrintEndCheck(tsiw->work[GE_MSG_INDEX])==0){
			SCIO_WazaWasureSet(tsiw->bw,exp_client_no,tsiw->work[GE_WAZANO],sel_mons_no);
			tsiw->seq_no++;
		}
		break;
	case SEQ_GE_WAZAWASURE_SELECT:
		if(ST_ServerBufferResGet(tsiw->sp,exp_client_no)==SELECT_CANCEL){
			tsiw->seq_no=SEQ_GE_WAZAAKIRAME_MSG1;
		}
		else if(ST_ServerBufferResGet(tsiw->sp,exp_client_no)){
			tsiw->work[GE_WAZAPOS]=tsiw->sp->server_buffer[exp_client_no][0]-1;
			tsiw->seq_no=SEQ_GE_WAZAWASURE_ACT_MSG1;
		}
		break;
	case SEQ_GE_WAZAAKIRAME_MSG1:
		mp.msg_id=battle_WazaAkirameMsg1;
		mp.msg_tag=TAG_NONE;
		tsiw->work[GE_MSG_INDEX]=BattleMSG_Print(tsiw->bw,msg_m,&mp,BattleWorkConfigMsgSpeedGet(tsiw->bw));
		tsiw->seq_no++;
		break;
	case SEQ_GE_WAZAAKIRAME_INIT:
		SCIO_YesNoSelectSet(tsiw->bw,tsiw->sp,exp_client_no,battle_WazaAkirameMsg2,YNTYPE_AKIRAME,tsiw->work[GE_WAZANO],NULL);
		tsiw->seq_no++;
		break;
	case SEQ_GE_WAZAAKIRAME:
		if(ST_ServerBufferResGet(tsiw->sp,exp_client_no)){
			if(ST_ServerBufferResGet(tsiw->sp,exp_client_no)==SELECT_CANCEL){
				tsiw->seq_no=SEQ_GE_WAZAWASURE_MSG1;
			}
			else{
				mp.msg_id=battle_WazaAkirameMsg3;
				mp.msg_tag=TAG_NICK_WAZA;
				mp.msg_para[0]=exp_client_no|(sel_mons_no<<8);
				mp.msg_para[1]=tsiw->work[GE_WAZANO];
				tsiw->work[GE_MSG_INDEX]=BattleMSG_Print(tsiw->bw,msg_m,&mp,BattleWorkConfigMsgSpeedGet(tsiw->bw));
				tsiw->seq_no=SEQ_GE_WAZAAKIRAME_ACT;
			}
		}
		break;
	case SEQ_GE_WAZAAKIRAME_ACT:
		if(GF_MSG_PrintEndCheck(tsiw->work[GE_MSG_INDEX])==0){
			tsiw->seq_no=SEQ_GE_WAZAOBOE_CHECK;
		}
		break;
	case SEQ_GE_WAZAWASURE_ACT_MSG1:
		mp.msg_id=battle_WazaWasureMsg3;
		mp.msg_tag=TAG_NONE;
		tsiw->work[GE_MSG_INDEX]=BattleMSG_Print(tsiw->bw,msg_m,&mp,BattleWorkConfigMsgSpeedGet(tsiw->bw));
		tsiw->seq_no++;
		break;
	case SEQ_GE_WAZAWASURE_ACT_MSG2:
		mp.msg_id=battle_WazaWasureMsg4;
		mp.msg_tag=TAG_NICK_WAZA;
		mp.msg_para[0]=exp_client_no|(sel_mons_no<<8);
		mp.msg_para[1]=PokeParaGet(pp,ID_PARA_waza1+tsiw->work[GE_WAZAPOS],NULL);
		tsiw->work[GE_MSG_INDEX]=BattleMSG_Print(tsiw->bw,msg_m,&mp,BattleWorkConfigMsgSpeedGet(tsiw->bw));
		tsiw->seq_no++;
		break;
	case SEQ_GE_WAZAWASURE_ACT_MSG3:
		mp.msg_id=battle_WazaOboeMsg3;
		mp.msg_tag=TAG_NONE;
		tsiw->work[GE_MSG_INDEX]=BattleMSG_Print(tsiw->bw,msg_m,&mp,BattleWorkConfigMsgSpeedGet(tsiw->bw));
		tsiw->seq_no++;
		break;
	case SEQ_GE_WAZAWASURE_ACT_MSG4:
		mp.msg_id=battle_WazaOboeMsg4;
		mp.msg_tag=TAG_NICK_WAZA;
		mp.msg_para[0]=exp_client_no|(sel_mons_no<<8);
		mp.msg_para[1]=tsiw->work[GE_WAZANO];
		tsiw->work[GE_MSG_INDEX]=BattleMSG_Print(tsiw->bw,msg_m,&mp,BattleWorkConfigMsgSpeedGet(tsiw->bw));
		i=0;
		PokeParaPut(pp,ID_PARA_pp_count1+tsiw->work[GE_WAZAPOS],&i);		//pp_count���N���A
		PokeWazaSetPos(pp,tsiw->work[GE_WAZANO],tsiw->work[GE_WAZAPOS]);
		if(tsiw->sp->sel_mons_no[exp_client_no]==sel_mons_no){
			ST_PokemonParamReload(tsiw->bw,tsiw->sp,exp_client_no,tsiw->sp->sel_mons_no[exp_client_no]);
		}
		tsiw->seq_no=SEQ_GE_WAZAOBOE_MSG_INDEX_WAIT;
		break;
	case SEQ_GE_WAZAOBOE_MSG_INDEX_WAIT:
		if(GF_MSG_PrintEndCheck(tsiw->work[GE_MSG_INDEX])==0){
			tsiw->seq_no=SEQ_GE_WAZAOBOE_CHECK;
		}
		break;
	case SEQ_GE_END_CHECK:
		tsiw->sp->get_exp_right_flag[client_no]&=(No2Bit(sel_mons_no)^0xffffffff);
		tsiw->work[GE_SEL_MONS_NO]=sel_mons_no+1;
		tsiw->seq_no=SEQ_GE_INIT;
		break;
	case SEQ_GE_END:
		tsiw->sp->tsiw=NULL;
		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		break;
	}
}

//============================================================================================
/**
 *	�w�͒l�v�Z
 *
 * @param[in]	pp		POKEMON_PARAM�\���̂̃|�C���^
 * @param[in]	mons_no	���炦��w�͒l�v�Z�̌��ƂȂ�|�P�����i���o�[
 */
//============================================================================================
static	void	PokeExpCalc(POKEPARTY *ppt,int pos,int mons_no)
{
	int	i;
	s16	work=0;
	u8	para[6];
	u16	totalpara;
	u16	item_no;
	int	eqp;
	int	atk;
	POKEMON_PARAM *pp;
	POKEMON_PERSONAL_DATA *ppd;

	ppd=PokePersonalPara_Open(mons_no,HEAPID_BATTLE);
	pp=PokeParty_GetMemberPointer(ppt,pos);

	item_no=PokeParaGet(pp,ID_PARA_item,NULL);
	eqp=ItemParamGet(item_no,ITEM_PRM_EQUIP,HEAPID_BATTLE);
	atk=ItemParamGet(item_no,ITEM_PRM_ATTACK,HEAPID_BATTLE);

	totalpara=0;

	for(i=0;i<6;i++){
		para[i]=PokeParaGet(pp,ID_PARA_hp_exp+i,NULL);
		totalpara+=para[i];
	}

	for(i=0;i<6;i++){
		if(totalpara>=PARA_EXP_TOTAL_MAX){
			break;
		}
		switch(i){
			case 0:
				work=PokePersonalPara_Get(ppd,ID_PER_pains_hp);
				//�������ʂŁAHP�w�͒l�A�b�v
				if(eqp==SOUBI_HPDORYOKUTIUP){
					work+=atk;
				}
				break;
			case 1:
				work=PokePersonalPara_Get(ppd,ID_PER_pains_pow);
				//�������ʂŁA�U���w�͒l�A�b�v
				if(eqp==SOUBI_KOUGEKIDORYOKUTIUP){
					work+=atk;
				}
				break;
			case 2:
				work=PokePersonalPara_Get(ppd,ID_PER_pains_def);
				//�������ʂŁA�h��w�͒l�A�b�v
				if(eqp==SOUBI_BOUGYODORYOKUTIUP){
					work+=atk;
				}
				break;
			case 3:
				work=PokePersonalPara_Get(ppd,ID_PER_pains_agi);
				//�������ʂŁA�f�����w�͒l�A�b�v
				if(eqp==SOUBI_SUBAYASADORYOKUTIUP){
					work+=atk;
				}
				break;
			case 4:
				work=PokePersonalPara_Get(ppd,ID_PER_pains_spepow);
				//�������ʂŁA���U�w�͒l�A�b�v
				if(eqp==SOUBI_TOKUKOUDORYOKUTIUP){
					work+=atk;
				}
				break;
			case 5:
				work=PokePersonalPara_Get(ppd,ID_PER_pains_spedef);
				//�������ʂŁA���h�w�͒l�A�b�v
				if(eqp==SOUBI_TOKUBOUDORYOKUTIUP){
					work+=atk;
				}
				break;
		}
		//�|�P���X��Ԃ́A�w�͒l��2�{
		if(PokerusedCheck(ppt,No2Bit(pos))){
			work=work*2;
		}
		//�A�C�e���œw�͒l2�{�̌��ʂ𑕔����Ă���ꍇ��2�{����
		if(eqp==SOUBI_DORYOKUTINIBAI){
			work=work*2;
		}
		if(totalpara+work>PARA_EXP_TOTAL_MAX){
			work-=((totalpara+work)-PARA_EXP_TOTAL_MAX);
		}
		if(para[i]+work>255){
			work-=((para[i]+work)-255);
		}
		para[i]+=work;
		totalpara+=work;
		PokeParaPut(pp,ID_PARA_hp_exp+i,(u8 *)&para[i]);
	}

	PokePersonalPara_Close(ppd);
}

//============================================================================================
/**
 *	GET_POKEMON�p�V�[�P���X��`
 */
//============================================================================================
enum{
	SEQ_GP_BALL_THROW=0,
	SEQ_GP_BALL_THROW_WAIT,
	SEQ_GP_BALL_OPEN_WAIT,
	SEQ_GP_BALL_FALL,
	SEQ_GP_BALL_FALL_WAIT,
	SEQ_GP_BALL_SHAKE,
	SEQ_GP_BALL_SHAKE_WAIT,
	SEQ_GP_POKEMON_SUCCESS_WAIT,
	SEQ_GP_POKEMON_MESSAGE,
	SEQ_GP_POKEMON_MESSAGE_WAIT,
	SEQ_GP_POKEMON_GET_WAIT,
	SEQ_GP_ZUKAN_MESSAGE,
	SEQ_GP_ZUKAN_INIT,
	SEQ_GP_ZUKAN,
	SEQ_GP_ZUKAN_END,
	SEQ_GP_ZUKAN_END_GET_SCREEN_MAKE,
	SEQ_GP_POKEMON_GET_SCREEN_INIT,
	SEQ_GP_POKEMON_GET_SCREEN,
	SEQ_GP_POKEMON_NICKNAME_YES_NO_INIT,
	SEQ_GP_POKEMON_NICKNAME_YES_NO,
	SEQ_GP_POKEMON_NICKNAME_INIT,
	SEQ_GP_POKEMON_NICKNAME_MAIN,
	SEQ_GP_POKEMON_GET,
	SEQ_GP_POKEMON_GET_NICKNAME_AFTER,
	SEQ_GP_PASOCOM_MOVE_WAIT,
	SEQ_GP_TRAINER_POKE_ALERT1,
	SEQ_GP_TRAINER_POKE_ALERT2,
	SEQ_GP_TRAINER_POKE_ALERT_WAIT,
	SEQ_GP_POKEMON_GET_FAILED_INIT,
	SEQ_GP_POKEMON_GET_FAILED_BALL_DELETE,
	SEQ_GP_POKEMON_GET_FAILED,
	SEQ_GP_POKEMON_GET_FAILED_WAIT,
	SEQ_GP_END
};

//============================================================================================
/**
 *	GET_POKEMON��tsiw->work�̓Y����
 */
//============================================================================================
enum{
	GP_MSG_INDEX=0,
	GP_MSG_WAIT,
	GP_HOKAKU,
	GP_SHAKE_COUNT,

	POKEMON_INHALE_WAIT=23,	//�|�P�����z�����ނ܂ł̃E�G�C�g
	BALL_SHAKE_WAIT=12		//�{�[���h�炵����̃E�G�C�g
};

//============================================================================================
/**
 *	GET_POKEMON��tsiw->work_p�̓Y����
 */
//============================================================================================
enum{
	GP_ZUKAN_P=0,
	GP_CHAR_MAN_P,

	GP_YES_NO=0,

	GP_NICKNAME_PROC=0,
	GP_NICKNAME_PARAM,
};

//============================================================================================
/**
 *	�|�P�����ߊl�pTCB
 *
 * @param[in]	tcb		TCB�V�X�e�����[�N
 * @param[in]	work	���[�N�G���A�|�C���^
 */
//============================================================================================
static	void	TCB_GetPokemon(TCB_PTR tcb,void *work)
{
	int					sel_mons_no;
	int					get_client_no;
	TCB_SKILL_INTP_WORK	*tsiw=work;
	POKEMON_PARAM		*pp;
	PALETTE_FADE_PTR	pfd;
	SOFT_SPRITE_MANAGER	*ssm_p;
	MSGDATA_MANAGER		*msg_m;

	msg_m=BattleWorkFightMsgGet(tsiw->bw);

	pfd=BattleWorkPfdGet(tsiw->bw);
	ssm_p=BattleWorkSoftSpriteManagerGet(tsiw->bw);

	get_client_no=CLIENT_NO_ENEMY;
	if(tsiw->sp->no_reshuffle_client&No2Bit(get_client_no)){
		get_client_no=CLIENT_NO_ENEMY2;
	}

	switch(tsiw->seq_no){
	case SEQ_GP_BALL_THROW:
		//�ʏ�ߊl
		if(tsiw->flag==GET_NORMAL){
			{
				TBALL_MOVE_DATA bmd;
	
				bmd.mode=EBMM_CAPTURE;		///< �G�ɓ�����
				bmd.heap_id=HEAPID_BATTLE;
				bmd.id=get_client_no+20000;	///<���s�̎���PokemonAppear�̕���id�Ɣ��Ȃ��悤�ɂ��肦�Ȃ��l�ɂ��Ă���
				bmd.ball_id=tsiw->ballID;
				bmd.csp=BattleWorkCATS_SYS_PTRGet(tsiw->bw);
				bmd.pfd=BattleWorkPfdGet(tsiw->bw);
				bmd.bg_pri=BM_BG_PRI_BATTLE;
				bmd.surface = 0;
				bmd.bw = tsiw->bw;
				if(BattleWorkFightTypeGet(tsiw->bw)&FIGHT_TYPE_2vs2){
					if(get_client_no==CLIENT_NO_ENEMY){
						bmd.type=EBMT_CAPTURE_B;
					}
					else{
						bmd.type=EBMT_CAPTURE_D;
					}
				}
				else{
					bmd.type=EBMT_CAPTURE_BB;
				}
				
				tsiw->bms=BM_Init(&bmd);
				tsiw->seq_no=SEQ_GP_BALL_THROW_WAIT;
				Snd_SePlay(BSE_BALL_THROW);
	
				//�{�[���������J�E���g���C���N�������g
				tsiw->bw->ball_count++;
	
				BM_SceneSet(tsiw->bms,EBM_DEMO_SCENE_THROW);
			}
		}
		else{
			{
				CLIENT_PARAM *cp;

				cp=BattleWorkClientParamGet(tsiw->bw,CLIENT_NO_MINE);

				if(BM_ModeGet(cp->bms)!=EBMM_FREE){
					tsiw->bms=cp->bms;
					cp->bms=NULL;
					tsiw->seq_no=SEQ_GP_BALL_THROW_WAIT;
					Snd_SePlay(BSE_BALL_THROW);
					//�{�[���������J�E���g���C���N�������g
					tsiw->bw->ball_count++;
	
					BM_SceneSet(tsiw->bms,EBM_DEMO_SCENE_THROW);
				}
			}
		}
		break;
	case SEQ_GP_BALL_THROW_WAIT:
		if(BM_SceneStateGet(tsiw->bms,EBM_DEMO_SCENE_THROW)==FALSE){
			{
				u32	fight_type;

				fight_type=BattleWorkFightTypeGet(tsiw->bw);
				if(fight_type&FIGHT_TYPE_TRAINER){
					Snd_SePlayPan(BSE_BALL_HIT,WAZA_SE_PAN_R);
					BM_SceneSet(tsiw->bms,EBM_DEMO_SCENE_SHED);
					tsiw->seq_no=SEQ_GP_TRAINER_POKE_ALERT1;
				}
				else{
					Snd_SePlayPan(BSE_BALL_HIT_OPEN,WAZA_SE_PAN_R);
					BM_SceneSet(tsiw->bms,EBM_DEMO_SCENE_OPEN);
					tsiw->seq_no=SEQ_GP_BALL_OPEN_WAIT;
					tsiw->work[GP_MSG_WAIT]=POKEMON_INHALE_WAIT;
				}
			}
		}
		break;
	case SEQ_GP_BALL_OPEN_WAIT:
		if(--tsiw->work[GP_MSG_WAIT]==0){
			//Snd_SePlayPan(BSE_BALL_INHALE,WAZA_SE_PAN_R);
			SCIO_PokemonInhaleSet(tsiw->bw,get_client_no,tsiw->ballID);
			tsiw->work[GP_HOKAKU]=PokemonGetCalc(tsiw->bw,tsiw->sp);
			if(tsiw->work[GP_HOKAKU]<4){
				tsiw->work[GP_SHAKE_COUNT]=tsiw->work[GP_HOKAKU];
			}
			else{
				tsiw->work[GP_SHAKE_COUNT]=3;
			}
			tsiw->seq_no=SEQ_GP_BALL_FALL;
		}
		break;
	case SEQ_GP_BALL_FALL:
		if((BM_SceneStateGet(tsiw->bms,EBM_DEMO_SCENE_OPEN)==FALSE)&&
		   (ST_ServerQueCheck(tsiw->sp))){
			BM_SceneSet(tsiw->bms,EBM_DEMO_SCENE_FALL);
			tsiw->seq_no=SEQ_GP_BALL_FALL_WAIT;
		}
		break;
	case SEQ_GP_BALL_FALL_WAIT:
		if(BM_SceneStateGet(tsiw->bms,EBM_DEMO_SCENE_FALL)==FALSE){
			tsiw->seq_no=SEQ_GP_BALL_SHAKE;
		}
		break;
	case SEQ_GP_BALL_SHAKE:
		if(tsiw->work[GP_SHAKE_COUNT]==0){
			if(tsiw->work[GP_HOKAKU]==4){
				tsiw->seq_no=SEQ_GP_POKEMON_SUCCESS_WAIT;
				tsiw->work[GP_MSG_WAIT]=BALL_SHAKE_WAIT;
			}
			else{
				tsiw->seq_no=SEQ_GP_POKEMON_GET_FAILED_INIT;
			}
		}
		else{
			BM_SceneSet(tsiw->bms,EBM_DEMO_SCENE_ROLL);
			tsiw->seq_no=SEQ_GP_BALL_SHAKE_WAIT;
			tsiw->work[GP_MSG_WAIT]=BALL_SHAKE_WAIT;
		}
		break;
	case SEQ_GP_BALL_SHAKE_WAIT:
		if(BM_SceneStateGet(tsiw->bms,EBM_DEMO_SCENE_ROLL)==FALSE){
			if(--tsiw->work[GP_MSG_WAIT]==0){
				tsiw->work[GP_SHAKE_COUNT]--;
				tsiw->seq_no=SEQ_GP_BALL_SHAKE;
			}
		}
		break;
	case SEQ_GP_POKEMON_SUCCESS_WAIT:
		if(--tsiw->work[GP_MSG_WAIT]==0){
			BM_SceneSet(tsiw->bms,EBM_DEMO_SCENE_END_SUCCESS);
			Snd_SePlayPan(BSE_POKEMON_GET,WAZA_SE_PAN_R);
			tsiw->seq_no=SEQ_GP_POKEMON_MESSAGE;
		}
		break;
	case SEQ_GP_POKEMON_MESSAGE:
		if(BM_SceneStateGet(tsiw->bms,EBM_DEMO_SCENE_END_SUCCESS)==FALSE){
			{
				MESSAGE_PARAM	mp;
	
				mp.msg_id=GetSuccessMsg;
				mp.msg_tag=TAG_NICK|TAG_NO_DIR;
				mp.msg_para[0]=get_client_no;
				tsiw->work[GP_MSG_INDEX]=BattleMSG_Print(tsiw->bw,msg_m,&mp,BattleWorkConfigMsgSpeedGet(tsiw->bw));
				tsiw->work[GP_MSG_WAIT]=MSG_WAIT;
				tsiw->seq_no=SEQ_GP_POKEMON_MESSAGE_WAIT;
				Snd_BgmPlay(SEQ_WINPOKE);
				BattleWorkPinchSEFlagSet(tsiw->bw,2);
			}
		}
		break;
	case SEQ_GP_POKEMON_MESSAGE_WAIT:
		if(GF_MSG_PrintEndCheck(tsiw->work[GP_MSG_INDEX])==0){
			tsiw->seq_no=SEQ_GP_POKEMON_GET_WAIT;
			BM_SceneSet(tsiw->bms,EBM_DEMO_SCENE_END_SUCCESS_2);
		}
		break;
	case SEQ_GP_POKEMON_GET_WAIT:
		if(BM_SceneStateGet(tsiw->bms,EBM_DEMO_SCENE_END_SUCCESS_2)==FALSE){
			if(--tsiw->work[GE_MSG_WAIT]==0){
				//�ߊl�����|�P������ClientNo��ۑ�
				BattleWorkGetPokemonClientSet(tsiw->bw,get_client_no);
				pp=BattleWorkPokemonParamGet(tsiw->bw,get_client_no,tsiw->sp->sel_mons_no[get_client_no]);
				//�|�P�p�[�N�Ȃ�΁A�ȍ~�̏������X���[
				if(BattleWorkFightTypeGet(tsiw->bw)&(FIGHT_TYPE_POKE_PARK|FIGHT_TYPE_GET_DEMO)){
					pp=BattleWorkPokemonParamGet(tsiw->bw,get_client_no,tsiw->sp->sel_mons_no[get_client_no]);
					ST_ServerPokemonGetParamSet(tsiw->bw,tsiw->sp,pp);
					//���b�Z�[�W�E�C���h�EDS�A�C�R���p���b�g�A�j���ꎞ��~
					MSG_DsIconFlashReq(BattleWorkMsgIconGet(tsiw->bw),MSG_DSI_REQ_STOP);
					PaletteFadeReq(pfd,PF_BIT_NORMAL_ALL,0xffff,1,0,16,0x0000);
					SoftSpritePalFadeSetAll(ssm_p,0,16,0,0x0000);
					tsiw->seq_no=SEQ_GP_END;
				}
				else if(FT_ZukanFlagCheckGet(tsiw->bw,PokeParaGet(pp,ID_PARA_monsno,NULL))){
					//���b�Z�[�W�E�C���h�EDS�A�C�R���p���b�g�A�j���ꎞ��~
					MSG_DsIconFlashReq(BattleWorkMsgIconGet(tsiw->bw),MSG_DSI_REQ_STOP);
					PaletteFadeReq(pfd,PF_BIT_MAIN_ALL,0xffff,1,0,16,0x0000);
					SoftSpritePalFadeSetAll(ssm_p,0,16,0,0x0000);
					tsiw->seq_no=SEQ_GP_POKEMON_GET_SCREEN_INIT;
				}
				else{
					{
						MESSAGE_PARAM	mp;
	
						mp.msg_id=ZukanSaveMsg;
						mp.msg_tag=TAG_NICK|TAG_NO_DIR;
						mp.msg_para[0]=get_client_no;
						tsiw->work[GP_MSG_INDEX]=BattleMSG_Print(tsiw->bw,msg_m,&mp,BattleWorkConfigMsgSpeedGet(tsiw->bw));
						tsiw->work[GP_MSG_WAIT]=MSG_WAIT;
						tsiw->seq_no=SEQ_GP_ZUKAN_MESSAGE;
					}
					//�}�ӓo�^�̃X�R�A�A�b�v
					BattleWorkZukanSetScoreAdd(tsiw->bw);
				}
			}
		}
		break;
	case SEQ_GP_ZUKAN_MESSAGE:
		if(GF_MSG_PrintEndCheck(tsiw->work[GP_MSG_INDEX])==0){
			if(--tsiw->work[GP_MSG_WAIT]==0){
				tsiw->seq_no=SEQ_GP_ZUKAN_INIT;
				PaletteFadeReq(pfd,PF_BIT_MAIN_ALL,0xffff,1,0,16,0x0000);
				SoftSpritePalFadeSetAll(ssm_p,0,16,0,0x0000);
				//���b�Z�[�W�E�C���h�EDS�A�C�R���p���b�g�A�j���ꎞ��~
				MSG_DsIconFlashReq(BattleWorkMsgIconGet(tsiw->bw),MSG_DSI_REQ_STOP);
			}
		}
		break;
	case SEQ_GP_ZUKAN_INIT:
		if(PaletteFadeCheck(pfd)==0){
			{
				ZKN_FIGHT_TEXT_PARAM	zftp;

				BM_Delete(tsiw->bms);
				SoftSpriteClear(ssm_p);
				FightScreenPokemonGetEnd(tsiw->bw);
				Ground_EnableSet(BattleWorkGroundWorkGet(tsiw->bw,GROUND_MINE),CATS_ENABLE_FALSE);
				Ground_EnableSet(BattleWorkGroundWorkGet(tsiw->bw,GROUND_ENEMY),CATS_ENABLE_FALSE);
	
				zftp.p_bgl=BattleWorkGF_BGL_INIGet(tsiw->bw);
				zftp.p_pfd=BattleWorkPfdGet(tsiw->bw);
				zftp.p_ssm=ssm_p;
				zftp.heap=HEAPID_BATTLE;
				zftp.p_pp=BattleWorkPokemonParamGet(tsiw->bw,get_client_no,tsiw->sp->sel_mons_no[get_client_no]);
				zftp.pokenum_mode=PMNumber_GetMode_ZW(BattleWorkZukanWorkGet(tsiw->bw));

				tsiw->work_p[GP_CHAR_MAN_P]=CharManagerPtrGet();
				tsiw->work_p[GP_ZUKAN_P]=ZKN_FIGHT_TextDrawReq(&zftp);
				tsiw->seq_no=SEQ_GP_ZUKAN;
			}
		}
		break;
	case SEQ_GP_ZUKAN:
		if(ZKN_FIGHT_TexDrawEndCheck(tsiw->work_p[GP_ZUKAN_P])){
			if(sys.trg&PAD_BUTTON_A){
				tsiw->seq_no=SEQ_GP_ZUKAN_END;
			}
			else if(GF_TP_GetTrg()){
				Snd_SePlay(BSE_OKURI);
				tsiw->seq_no=SEQ_GP_ZUKAN_END;
			}
			if(tsiw->seq_no==SEQ_GP_ZUKAN_END){
				PaletteFadeReq(pfd,PF_BIT_MAIN_ALL,0xffff,1,0,16,0x0000);
				ZKN_FIGHT_PalAnmFlagSet(tsiw->work_p[GP_ZUKAN_P],FALSE);
			}
		}
		break;
	case SEQ_GP_ZUKAN_END:
		{
			SOFT_SPRITE	*ss;
			
			ss=ZKN_FIGHT_TexDrawGetSsp(tsiw->work_p[GP_ZUKAN_P]);
			SoftSpriteParaCalc(ss,SS_PARA_POS_X,4);
			if(SoftSpriteParaGet(ss,SS_PARA_POS_X)>=128){
				SoftSpriteParaSet(ss,SS_PARA_POS_X,128);
				tsiw->seq_no=SEQ_GP_ZUKAN_END_GET_SCREEN_MAKE;
			}

		}
		break;
	case SEQ_GP_ZUKAN_END_GET_SCREEN_MAKE:
		ZKN_FIGHT_TextDrawDelete(tsiw->work_p[GP_ZUKAN_P]);
		CharManagerPtrSet(tsiw->work_p[GP_CHAR_MAN_P]);
		FightScreenPokemonGet(tsiw->bw);
		PaletteFadeReq(pfd,PF_BIT_MAIN_ALL,0xffff,1,16,0,0x0000);
		tsiw->seq_no=SEQ_GP_POKEMON_GET_SCREEN;
		break;
	case SEQ_GP_POKEMON_GET_SCREEN_INIT:
		if(PaletteFadeCheck(pfd)==0){
			{
				SOFT_SPRITE_ARC	ssa;

				pp=BattleWorkPokemonParamGet(tsiw->bw,get_client_no,tsiw->sp->sel_mons_no[get_client_no]);
				BM_Delete(tsiw->bms);
				SoftSpriteClear(ssm_p);
				FightScreenPokemonGetEnd(tsiw->bw);
				FightScreenPokemonGet(tsiw->bw);
				PokeGraArcDataGetPP(&ssa,pp,PARA_FRONT);
				SoftSpriteAdd(ssm_p,&ssa,128,ZKN_FIGHT_POKEGRA_MAT_Y,0,0,NULL,NULL);
				PaletteFadeReq(pfd,PF_BIT_MAIN_ALL,0xffff,1,16,0,0x0000);
				SoftSpritePalFadeSetAll(ssm_p,16,0,0,0x0000);
				tsiw->seq_no=SEQ_GP_POKEMON_GET_SCREEN;
			}
		}
		break;
	case SEQ_GP_POKEMON_GET_SCREEN:
		if(PaletteFadeCheck(pfd)==0){
			{
#if 0
				MESSAGE_PARAM		mp;
	
				mp.msg_id=NickNameMsg;
				mp.msg_tag=TAG_NICK|TAG_NO_DIR;
				mp.msg_para[0]=CLIENT_NO_ENEMY;
				tsiw->work[GP_MSG_INDEX]=BattleMSG_Print(tsiw->bw,msg_m,&mp,BattleWorkConfigMsgSpeedGet(tsiw->bw));
#endif
				tsiw->seq_no=SEQ_GP_POKEMON_NICKNAME_YES_NO_INIT;

				//���b�Z�[�W�E�C���h�EDS�A�C�R���p���b�g�A�j���ĊJ
				MSG_DsIconFlashReq(BattleWorkMsgIconGet(tsiw->bw),MSG_DSI_REQ_START);
				PaletteTrans_AutoSet(pfd,TRUE);
			}
		}
		break;
	case SEQ_GP_POKEMON_NICKNAME_YES_NO_INIT:
		{
			int	nickname;

			nickname=get_client_no|(tsiw->sp->sel_mons_no[get_client_no]);

			SCIO_YesNoSelectSet(tsiw->bw,tsiw->sp,CLIENT_NO_MINE,NickNameMsg,YNTYPE_NICK_NAME,NULL,nickname);
			tsiw->seq_no++;
		}
#if 0
		if(GF_MSG_PrintEndCheck(tsiw->work[GP_MSG_INDEX])==0){
			{
				GF_BGL_INI			*bgl;

				bgl=BattleWorkGF_BGL_INIGet(tsiw->bw);

				MenuWinCgxSet(bgl,GF_BGL_FRAME2_M,MENU_WIN_CGX_START,MENU_TYPE_SYSTEM,HEAPID_BATTLE);
				PaletteWorkSet_Arc(pfd, ARC_WINFRAME, MenuWinPalArcGet(), HEAPID_BATTLE, 
								FADE_MAIN_BG, 0x20, MENU_WIN_PAL_NO*0x10);
				tsiw->work_p[GP_YES_NO]=BmpYesNoSelectInit(bgl,&YesNoBmpWin,MENU_WIN_CGX_START,MENU_WIN_PAL_NO,HEAPID_BATTLE);
				tsiw->seq_no=SEQ_GP_POKEMON_NICKNAME_YES_NO;
			}
		}
#endif
		break;
	case SEQ_GP_POKEMON_NICKNAME_YES_NO:
		if(ST_ServerBufferResGet(tsiw->sp,CLIENT_NO_MINE)){
			if(ST_ServerBufferResGet(tsiw->sp,CLIENT_NO_MINE)==SELECT_CANCEL){
				tsiw->seq_no=SEQ_GP_POKEMON_GET;
			}
			else{
				//���b�Z�[�W�E�C���h�EDS�A�C�R���p���b�g�A�j���ꎞ��~
				MSG_DsIconFlashReq(BattleWorkMsgIconGet(tsiw->bw),MSG_DSI_REQ_STOP);
				PaletteFadeReq(pfd,PF_BIT_NORMAL_ALL,0xffff,1,0,16,0x0000);
				SoftSpritePalFadeSetAll(ssm_p,0,16,0,0x0000);
				tsiw->seq_no=SEQ_GP_POKEMON_NICKNAME_INIT;
			}
		}
#if 0
		switch(BmpYesNoSelectMain(tsiw->work_p[GP_YES_NO],HEAPID_BATTLE)){
		case 0:					//�͂���I��
			PaletteFadeReq(pfd,PF_BIT_NORMAL_ALL,0xffff,1,0,16,0x0000);
			SoftSpritePalFadeSetAll(ssm_p,0,16,0,0x0000);
			tsiw->seq_no=SEQ_GP_POKEMON_NICKNAME_INIT;
			break;
		case BMPMENU_CANCEL:	//������or�L�����Z��
			tsiw->seq_no=SEQ_GP_POKEMON_GET;
			break;
		}
#endif
		break;
	case SEQ_GP_POKEMON_NICKNAME_INIT:
		if(PaletteFadeCheck(pfd)==0){
			{
				NAMEIN_PARAM	*np;

				WIPE_SetBrightness(WIPE_DISP_MAIN,WIPE_FADE_BLACK);
				WIPE_SetBrightness(WIPE_DISP_SUB,WIPE_FADE_BLACK);

				pp=BattleWorkPokemonParamGet(tsiw->bw,get_client_no,tsiw->sp->sel_mons_no[get_client_no]);

				np=NameIn_ParamAllocMake(HEAPID_BATTLE,NAMEIN_POKEMON,
										 PokeParaGet(pp,ID_PARA_monsno,NULL),NAMEIN_POKEMON_LENGTH,
										 BattleWorkConfigGet(tsiw->bw));
				tsiw->work_p[GP_NICKNAME_PARAM]=np;

				if(BattleWorkPokeCountGet(tsiw->bw,CLIENT_NO_MINE)<POKEMON_TEMOTI_MAX){
					np->get_msg_id=0;
				}
				else{
					np->get_msg_id=BoxTensoDarekaMsg+BattleWorkMizukiFlagGet(tsiw->bw);
				}
				np->form = PokeParaGet(pp, ID_PARA_form_no, NULL);
				np->boxdata=BattleWorkBoxDataGet(tsiw->bw);
				np->sex  = PokeParaGet(pp, ID_PARA_sex, NULL);
				tsiw->work_p[GP_NICKNAME_PROC]=PROC_Create(&NameInProcData,np,HEAPID_BATTLE);
				tsiw->seq_no=SEQ_GP_POKEMON_NICKNAME_MAIN;
				BattleWorkGaugeDelete(tsiw->bw);
				FightScreenEnd(tsiw->bw);
				BattleWorkProcModeSet(tsiw->bw,BW_PROC_MODE_NAMEIN);
			}
		}
		break;
	case SEQ_GP_POKEMON_NICKNAME_MAIN:
		if(ProcMain(tsiw->work_p[GP_NICKNAME_PROC])){
			{
				NAMEIN_PARAM	*np;
				int				flag;

				np=tsiw->work_p[GP_NICKNAME_PARAM];
				pp=BattleWorkPokemonParamGet(tsiw->bw,get_client_no,tsiw->sp->sel_mons_no[get_client_no]);

				if(np->cancel==0){
					PokeParaPut(pp,ID_PARA_nickname_buf_flag,np->strbuf);
				}
				
				NameIn_ParamDelete(np);
				PROC_Delete(tsiw->work_p[GP_NICKNAME_PROC]);
				BattleWorkProcModeSet(tsiw->bw,BW_PROC_MODE_NAMEIN_AFTER);
				tsiw->seq_no=SEQ_GP_POKEMON_GET_NICKNAME_AFTER;
			}
		}
		break;
	case SEQ_GP_POKEMON_GET:
	case SEQ_GP_POKEMON_GET_NICKNAME_AFTER:
		if(PaletteFadeCheck(pfd)==0){
			{
				MESSAGE_PARAM		mp;
				POKEPARTY			*poke_party;
				int					work;
	
				poke_party=BattleWorkPokePartyGet(tsiw->bw,CLIENT_NO_MINE);
				pp=BattleWorkPokemonParamGet(tsiw->bw,get_client_no,tsiw->sp->sel_mons_no[get_client_no]);
	
				FT_ZukanFlagSetGet(tsiw->bw,get_client_no);

				ST_ServerPokemonGetParamSet(tsiw->bw,tsiw->sp,pp);

				//�|�P�b�`�f�[�^�ɓo�^
				BattleWorkPoketchDataSet(tsiw->bw,pp);

				//TV�ԑg�R�[��
				//�Q�b�g���́A�߂܂����|�P������PP
				//����ȊO�́A�ΐ푊���PP
				BattleWorkTVDataSet(tsiw->bw,pp);

				//�߂܂����|�P�����̕C�����J�E���g�A�b�v
				SCIO_IncRecord(tsiw->bw,CLIENT_NO_MINE,CLIENT_BOOT_TYPE_MINE,RECID_CAPTURE_POKE);

				if(PokeParty_Add(poke_party,pp)==TRUE){
					if(tsiw->seq_no==SEQ_GP_POKEMON_GET){
						MSG_DsIconFlashReq(BattleWorkMsgIconGet(tsiw->bw),MSG_DSI_REQ_STOP);
						PaletteFadeReq(pfd,PF_BIT_NORMAL_ALL,0xffff,1,0,16,0x0000);
						SoftSpritePalFadeSetAll(ssm_p,0,16,0,0x0000);
					}
					tsiw->seq_no=SEQ_GP_END;
				}
				else{
					{
						BOX_DATA	*box;
						u32			cur_box;
						u32			in_box;
						int			i;
						int			ppmax;

						box=BattleWorkBoxDataGet(tsiw->bw);
						cur_box=BOXDAT_GetCureentTrayNumber(box);
						in_box=BOXDAT_GetEmptyTrayNumber(box);
						BOXDAT_SetCureentTrayNumber(box,in_box);
						//�{�b�N�X�]�����鎞�́APP���񕜂��Ă���
						for(i=0;i<WAZA_TEMOTI_MAX;i++){
							ppmax=PokeParaGet(pp,ID_PARA_pp_max1+i,NULL);
							PokeParaPut(pp,ID_PARA_pp1+i,&ppmax);
						}
						BOXDAT_PutPokemonBox(box,in_box,PPPPointerGet(pp));

						if(tsiw->seq_no==SEQ_GP_POKEMON_GET){
							if(cur_box==in_box){
								mp.msg_id=BoxTensoDarekaMsg+BattleWorkMizukiFlagGet(tsiw->bw);
								mp.msg_tag=TAG_NICK_BOX|TAG_NO_DIR;
								mp.msg_para[0]=get_client_no;
								mp.msg_para[1]=cur_box;
							}
							else{
								mp.msg_id=BoxTensoKirikaeDarekaMsg+BattleWorkMizukiFlagGet(tsiw->bw);
								mp.msg_tag=TAG_NICK_BOX_BOX|TAG_NO_DIR;
								mp.msg_para[0]=get_client_no;
								mp.msg_para[1]=cur_box;
								mp.msg_para[2]=in_box;
							}
							tsiw->work[GP_MSG_INDEX]=BattleMSG_Print(tsiw->bw,msg_m,&mp,BattleWorkConfigMsgSpeedGet(tsiw->bw));
							tsiw->work[GP_MSG_WAIT]=MSG_WAIT;
							tsiw->seq_no=SEQ_GP_PASOCOM_MOVE_WAIT;
						}
						else{
							tsiw->seq_no=SEQ_GP_END;
						}
					}
				}
			}
		}
		break;
	case SEQ_GP_PASOCOM_MOVE_WAIT:
		if(GF_MSG_PrintEndCheck(tsiw->work[GP_MSG_INDEX])==0){
			if(--tsiw->work[GP_MSG_WAIT]==0){
				{
					MSG_DsIconFlashReq(BattleWorkMsgIconGet(tsiw->bw),MSG_DSI_REQ_STOP);
					PaletteFadeReq(pfd,PF_BIT_NORMAL_ALL,0xffff,1,0,16,0x0000);
					SoftSpritePalFadeSetAll(ssm_p,0,16,0,0x0000);
					tsiw->seq_no=SEQ_GP_END;
				}
			}
		}
		break;
	case SEQ_GP_TRAINER_POKE_ALERT1:
		if(BM_SceneStateGet(tsiw->bms,EBM_DEMO_SCENE_SHED)==FALSE){
			{
				MESSAGE_PARAM	mp;
	
				BM_Delete(tsiw->bms);
				mp.msg_id=TrainerMonsMsg1;
				mp.msg_tag=TAG_NONE;
				tsiw->work[GP_MSG_INDEX]=BattleMSG_Print(tsiw->bw,msg_m,&mp,BattleWorkConfigMsgSpeedGet(tsiw->bw));
				tsiw->work[GP_MSG_WAIT]=MSG_WAIT;
				tsiw->seq_no=SEQ_GP_TRAINER_POKE_ALERT2;
			}
		}
		break;
	case SEQ_GP_TRAINER_POKE_ALERT2:
		if(GF_MSG_PrintEndCheck(tsiw->work[GP_MSG_INDEX])==0){
			if(--tsiw->work[GP_MSG_WAIT]==0){
				{
					MESSAGE_PARAM	mp;

					mp.msg_id=TrainerMonsMsg2;
					mp.msg_tag=TAG_NONE;
					tsiw->work[GP_MSG_INDEX]=BattleMSG_Print(tsiw->bw,msg_m,&mp,BattleWorkConfigMsgSpeedGet(tsiw->bw));
					tsiw->work[GP_MSG_WAIT]=MSG_WAIT;
					tsiw->seq_no=SEQ_GP_TRAINER_POKE_ALERT_WAIT;
				}
			}
		}
		break;
	case SEQ_GP_TRAINER_POKE_ALERT_WAIT:
		if(GF_MSG_PrintEndCheck(tsiw->work[GP_MSG_INDEX])==0){
			if(--tsiw->work[GP_MSG_WAIT]==0){
				tsiw->sp->tsiw=NULL;
				sys_FreeMemoryEz(work);
				TCB_Delete(tcb);
			}
		}
		break;
	case SEQ_GP_POKEMON_GET_FAILED_INIT:
		SCIO_PokemonAppearSet(tsiw->bw,get_client_no,tsiw->ballID,POKEMON_APPEAR_GET_FAILED);
		tsiw->seq_no=SEQ_GP_POKEMON_GET_FAILED_BALL_DELETE;
		tsiw->work[GP_MSG_WAIT]=2;
		break;
	case SEQ_GP_POKEMON_GET_FAILED_BALL_DELETE:
		if(--tsiw->work[GP_MSG_WAIT]==0){
			BM_Delete(tsiw->bms);
			tsiw->seq_no=SEQ_GP_POKEMON_GET_FAILED;
		}
		break;
	case SEQ_GP_POKEMON_GET_FAILED:
		if(ST_ServerQueCheck(tsiw->sp)){
			{
				MESSAGE_PARAM	mp;

				mp.msg_id=GetFailMsg3+tsiw->work[GP_HOKAKU];
				mp.msg_tag=TAG_NONE;
				tsiw->work[GP_MSG_INDEX]=BattleMSG_Print(tsiw->bw,msg_m,&mp,BattleWorkConfigMsgSpeedGet(tsiw->bw));
				tsiw->work[GP_MSG_WAIT]=MSG_WAIT;
				tsiw->seq_no=SEQ_GP_POKEMON_GET_FAILED_WAIT;
			}
		}
		break;
	case SEQ_GP_POKEMON_GET_FAILED_WAIT:
		if(GF_MSG_PrintEndCheck(tsiw->work[GP_MSG_INDEX])==0){
			if(--tsiw->work[GP_MSG_WAIT]==0){
				tsiw->sp->tsiw=NULL;
				sys_FreeMemoryEz(work);
				TCB_Delete(tcb);
			}
		}
		break;
	case SEQ_GP_END:
		if(PaletteFadeCheck(pfd)==0){
			//�|�P�p�[�N�A�ߊl�f���̎��́A���̂Q���폜����Ă��Ȃ��̂ō폜
			if(BattleWorkFightTypeGet(tsiw->bw)&(FIGHT_TYPE_POKE_PARK|FIGHT_TYPE_GET_DEMO)){
				BM_Delete(tsiw->bms);
				SoftSpriteClear(ssm_p);
			}
			tsiw->bw->win_lose_flag=FIGHT_POKE_GET;
			tsiw->sp->tsiw=NULL;
			sys_FreeMemoryEz(work);
			TCB_Delete(tcb);
		}
		break;
	}
}

//============================================================================================
/**
 *	�ߊl���v�Z�p�{�[���ߊl���e�[�u��
 */
//============================================================================================
static	const u8 BallRate[]={
		20,		//�n�C�p�[�{�[��
		15,		//�X�[�p�[�{�[��
		10,		//�����X�^�[�{�[��
		15,		//�T�t�@���{�[��
};

static	const	u8	SafariBallRateTable[][2]={
		{10,40},
		{10,35},
		{10,30},
		{10,25},
		{10,20},
		{10,15},
		{10,10},
		{15,10},
		{20,10},
		{25,10},
		{30,10},
		{35,10},
		{40,10},
};

//============================================================================================
/**
 *	�ߊl���v�Z�֐�
 *
 * @param[in]	bw		�퓬�p�����[�^�\����
 * @param[in]	sp		�T�[�o�p�����[�^�\����
 */
//============================================================================================
static	int	PokemonGetCalc(BATTLE_WORK *bw,SERVER_PARAM *sp)
{
	int	i;
	u32	hokakuritsu;
	u32	hokakuritsu2;
	u32	rate;
	u32	ballrate;
	int	type1;
	int	type2;

	//�|�P�p�[�N�A�ߊl�f���Ȃ�A100%�ߊl����
	if(BattleWorkFightTypeGet(bw)&(FIGHT_TYPE_POKE_PARK|FIGHT_TYPE_GET_DEMO)){
		return 4;
	}

//�T�t�@���{�[���Ȃ�G�T�ƃh���𓊂����񐔂ŕߊl����ϓ�
	if(sp->item_work==ITEM_SAFARIBOORU){
		rate=PokePersonalParaGet(sp->psp[sp->defence_client].monsno,ID_PER_get_rate);
		rate=rate*SafariBallRateTable[sp->safari_get_count][0]/SafariBallRateTable[sp->safari_get_count][1];
	}
	else{
		rate=PokePersonalParaGet(sp->psp[sp->defence_client].monsno,ID_PER_get_rate);
	}
	
	ballrate=10;
	type1=ST_ServerPokemonServerParamGet(sp,sp->defence_client,ID_PSP_type1,NULL);
	type2=ST_ServerPokemonServerParamGet(sp,sp->defence_client,ID_PSP_type2,NULL);

	if(sp->item_work>ITEM_SAFARIBOORU){
		switch(sp->item_work){
		case ITEM_NETTOBOORU:
			if((type1==WATER_TYPE)||(type2==WATER_TYPE)||
			   (type1==MUSHI_TYPE)||(type2==MUSHI_TYPE)){
				ballrate=30;
			}
			break;
		case ITEM_DAIBUBOORU:
			if(BattleWorkGroundIDGet(bw)==GROUND_ID_WATER){
				ballrate=35;
			}
			break;
		case ITEM_NESUTOBOORU:
			if(sp->psp[sp->defence_client].level<40){
				ballrate=40-sp->psp[sp->defence_client].level;
				if(ballrate<10){
					ballrate=10;
				}
			}
			break;
		case ITEM_RIPIITOBOORU:
			if(FT_ZukanFlagCheckGet(bw,sp->psp[sp->defence_client].monsno)==TRUE){
				ballrate=30;
			}
			break;
		case ITEM_TAIMAABOORU:
			ballrate=10+sp->total_turn;
			if(ballrate>40){
				ballrate=40;
			}
			break;
		case ITEM_DAAKUBOORU:
			if((BattleWorkTimeZoneGet(bw)==TIMEZONE_NIGHT)||
			   (BattleWorkTimeZoneGet(bw)==TIMEZONE_MIDNIGHT)||
			   (BattleWorkGroundIDGet(bw)==GROUND_ID_CAVE)){
				ballrate=35;
			}
			break;
		case ITEM_KUIKKUBOORU:
			if(sp->total_turn<1){
				ballrate=40;
			}
			break;
		}
	}
	else{
		ballrate=BallRate[sp->item_work-2];
	}

	hokakuritsu=((rate*ballrate)/10)*
				(sp->psp[sp->defence_client].hpmax*3-sp->psp[sp->defence_client].hp*2)/(sp->psp[sp->defence_client].hpmax*3);

	if(sp->psp[sp->defence_client].condition&(CONDITION_NEMURI|CONDITION_KOORI)){
		hokakuritsu*=2;
	}

	if(sp->psp[sp->defence_client].condition&(CONDITION_DOKU|CONDITION_MAHI|CONDITION_YAKEDO|CONDITION_DOKUDOKU)){
		hokakuritsu=hokakuritsu*15/10;
	}

	if(hokakuritsu>=255){
		i=4;
	}
	else{
		hokakuritsu2=(255<<16)/hokakuritsu;
		CP_SetSqrt32(hokakuritsu2);
		CP_WaitSqrt();
		hokakuritsu2=CP_GetSqrtResult32();
		CP_SetSqrt32(hokakuritsu2);
		CP_WaitSqrt();
		hokakuritsu=CP_GetSqrtResult32();
		hokakuritsu=(65535<<4)/hokakuritsu;
		for(i=0;i<4;i++){
			if(gf_rand()>=hokakuritsu) break;
		}
		if(sp->item_work==ITEM_MASUTAABOORU){
			i=4;				//�}�X�^�[�{�[��
		}
	}
	return i;
}

//============================================================================================
/**
 *	ClientNo�擾�֐�
 *
 * @param[in]	sp		�T�[�o�p�����[�^�\����
 * @param[in]	side	�擾���鑤���w��
 */
//============================================================================================
static	int	SideClientNoGet(BATTLE_WORK *bw,SERVER_PARAM *sp,int side)
{
	int	client_no;

	switch(side){
	default:
		OS_Printf("SideClientNoGet:�����ɂ���̂͂�������\n");
	case SIDE_ATTACK:
		client_no=sp->attack_client;
		break;
	case SIDE_DEFENCE:
		client_no=sp->defence_client;
		break;
	case SIDE_KIZETSU:
		client_no=sp->kizetsu_client;
		break;
	case SIDE_RESHUFFLE:
	case SIDE_RESHUFFLE_AFTER:
		client_no=sp->reshuffle_client;
		break;
	case SIDE_TSUIKA:
		client_no=sp->tsuika_client;
		break;
	case SIDE_TOKUSEI:
		client_no=sp->tokusei_client;
		break;
	case SIDE_ENEMY:
		{
			CLIENT_PARAM	*cp;
			int	client_set_max;

			client_set_max=BattleWorkClientSetMaxGet(bw);
			for(client_no=0;client_no<client_set_max;client_no++){
				cp=BattleWorkClientParamGet(bw,client_no);
				if(cp->client_type&CLIENT_ENEMY_FLAG){
					break;
				}
			}
		}
		break;
	case SIDE_ENEMY_1:
		{
			CLIENT_PARAM	*cp;
			int	client_set_max;

			client_set_max=BattleWorkClientSetMaxGet(bw);
			for(client_no=0;client_no<client_set_max;client_no++){
				cp=BattleWorkClientParamGet(bw,client_no);
				if((cp->client_type==CLIENT_TYPE_B)||(cp->client_type==CLIENT_TYPE_BB)){
					break;
				}
			}
		}
		break;
	case SIDE_ENEMY_2:
		{
			CLIENT_PARAM	*cp;
			int	client_set_max;
			int	type;

			if(BattleWorkFightTypeGet(bw)&FIGHT_TYPE_2vs2){
				type=CLIENT_TYPE_D;
			}
			else{
				type=CLIENT_TYPE_BB;
			}

			client_set_max=BattleWorkClientSetMaxGet(bw);
			for(client_no=0;client_no<client_set_max;client_no++){
				cp=BattleWorkClientParamGet(bw,client_no);
				if(cp->client_type==type){
					break;
				}
			}
		}
		break;
	case SIDE_MINE:
		{
			CLIENT_PARAM	*cp;
			int	client_set_max;

			client_set_max=BattleWorkClientSetMaxGet(bw);
			for(client_no=0;client_no<client_set_max;client_no++){
				cp=BattleWorkClientParamGet(bw,client_no);
				if((cp->client_type&CLIENT_ENEMY_FLAG)==0){
					break;
				}
			}
		}
		break;
	case SIDE_MINE_1:
		{
			CLIENT_PARAM	*cp;
			int	client_set_max;

			client_set_max=BattleWorkClientSetMaxGet(bw);
			for(client_no=0;client_no<client_set_max;client_no++){
				cp=BattleWorkClientParamGet(bw,client_no);
				if((cp->client_type==CLIENT_TYPE_A)||(cp->client_type==CLIENT_TYPE_AA)){
					break;
				}
			}
		}
		break;
	case SIDE_MINE_2:
		{
			CLIENT_PARAM	*cp;
			int	client_set_max;
			int	type;

			if(BattleWorkFightTypeGet(bw)&FIGHT_TYPE_2vs2){
				type=CLIENT_TYPE_C;
			}
			else{
				type=CLIENT_TYPE_AA;
			}

			client_set_max=BattleWorkClientSetMaxGet(bw);
			for(client_no=0;client_no<client_set_max;client_no++){
				cp=BattleWorkClientParamGet(bw,client_no);
				if(cp->client_type==type){
					break;
				}
			}
		}
		break;
	case SIDE_ATTACK_WORK:
		client_no=sp->attack_client_work;
		break;
	case SIDE_DEFENCE_WORK:
		client_no=sp->defence_client_work;
		break;
	case SIDE_ATTACK_PAIR:
		{
			int	client_set_max;

			client_set_max=BattleWorkClientSetMaxGet(bw);
			for(client_no=0;client_no<client_set_max;client_no++){
				if((client_no!=sp->attack_client)&&
				   (BattleWorkMineEnemyCheck(bw,client_no)==BattleWorkMineEnemyCheck(bw,sp->attack_client))){
					break;
				}
			}
			if(client_no==client_set_max){
				GF_ASSERT("�p�[�g�i�[��������܂���ł����@SIDE_ATTACK_PAIR���w��ł��܂���I\n");
				client_no=0;
			}
		}
		break;
	case SIDE_DEFENCE_PAIR:
		{
			int	client_set_max;

			client_set_max=BattleWorkClientSetMaxGet(bw);
			for(client_no=0;client_no<client_set_max;client_no++){
				if((client_no!=sp->defence_client)&&
				   (BattleWorkMineEnemyCheck(bw,client_no)==BattleWorkMineEnemyCheck(bw,sp->defence_client))){
					break;
				}
			}
			if(client_no==client_set_max){
				GF_ASSERT("�p�[�g�i�[��������܂���ł����@SIDE_DEFENCE_PAIR���w��ł��܂���I\n");
				client_no=0;
			}
		}
		break;
	case SIDE_ATTACK_ENEMY:
		{
			int	client_set_max;
			int	dir;

			client_set_max=BattleWorkClientSetMaxGet(bw);
			dir=BattleWorkMineEnemyCheck(bw,sp->attack_client);
			for(client_no=0;client_no<client_set_max;client_no++){
				if(dir!=BattleWorkMineEnemyCheck(bw,client_no)){
					break;
				}
			}
		}
		break;
	case SIDE_DEFENCE_ENEMY:
		{
			int	client_set_max;
			int	dir;

			client_set_max=BattleWorkClientSetMaxGet(bw);
			dir=BattleWorkMineEnemyCheck(bw,sp->defence_client);
			for(client_no=0;client_no<client_set_max;client_no++){
				if(dir!=BattleWorkMineEnemyCheck(bw,client_no)){
					break;
				}
			}
		}
		break;
	case SIDE_WORK:
	case SIDE_CLIENT_WORK:
		client_no=sp->client_work;
		break;
	}

	return client_no;
}

//============================================================================================
/**
 *	MessageParamMake�p�̃p�����[�^�\���̃f�[�^�����֐�
 *
 * @param[in]	sp		�T�[�o�p�����[�^�\����
 */
//============================================================================================
static	void	MessageParamDataMake(SERVER_PARAM *sp,MESSAGE_PARAM_DATA *mpd)
{
	int	i,max=0;

	mpd->msg_id=SkillSeqDataRead(sp);
	mpd->msg_tag=SkillSeqDataRead(sp);

	switch(mpd->msg_tag){
	case TAG_NONE:							//�^�O�Ȃ�
		max=0;
		break;
	case TAG_NONE_DIR:						//�^�O�Ȃ��i�Ă��A�݂������肠��j
	case TAG_NICK:							//nickname
	case TAG_WAZA:							//�Z��
	case TAG_STAT:							//�X�e�[�^�X��
	case TAG_ITEM:							//�X�e�[�^�X��
	case TAG_NUM:							//���l
	case TAG_NUMS:							//���l�i�E�l�߁j
	case TAG_TRNAME:						//trainer��
		max=1;
		break;
	case TAG_NICK_NICK:						//nickname		nickname
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
	case TAG_WAZA_DIR:						//�Z���i�Ă��A�݂������肠��j
	case TAG_WAZA_NICK:						//�Z��			nickname
	case TAG_WAZA_WAZA:						//�Z��			�Z��
	case TAG_TOKU_NICK:						//������		nickname
	case TAG_ITEM_WAZA:						//���		�Z��
	case TAG_NUM_NUM:						//���l			���l
	case TAG_TRNAME_TRNAME:					//trainer��		trainer��
	case TAG_TRNAME_NICK:					//trainer��		nickname
	case TAG_TRNAME_ITEM:					//trainer��		���
	case TAG_TRNAME_NUM:					//trainer��		���l
	case TAG_TRTYPE_TRNAME:					//trainer���	trainer��
		max=2;
		break;
	case TAG_NICK_NICK_WAZA:				//nickname		nickname		�Z��
	case TAG_NICK_NICK_TOKU:				//nickname		nickname		������
	case TAG_NICK_NICK_ITEM:				//nickname		nickname		���
	case TAG_NICK_WAZA_WAZA:				//nickname		�Z��			�Z��
	case TAG_NICK_WAZA_NUM:					//nickname		�Z��			���l
	case TAG_NICK_TOKU_NICK:				//nickname		������			nickname
	case TAG_NICK_TOKU_WAZA:				//nickname		������			�Z��
	case TAG_NICK_TOKU_ITEM:				//nickname		������			���
	case TAG_NICK_TOKU_STAT:				//nickname		������			�X�e�[�^�X��
	case TAG_NICK_TOKU_TYPE:				//nickname		������			�^�C�v��
	case TAG_NICK_TOKU_COND:				//nickname		������			��Ԉُ햼
	case TAG_NICK_TOKU_NUM:					//nickname		������			���l
	case TAG_NICK_ITEM_NICK:				//nickname		���			nickname
	case TAG_NICK_ITEM_WAZA:				//nickname		���			�Z��
	case TAG_NICK_ITEM_STAT:				//nickname		���			�X�e�[�^�X��
	case TAG_NICK_ITEM_COND:				//nickname		���			��Ԉُ햼
	case TAG_NICK_BOX_BOX:					//nickname		�{�b�N�X��		�{�b�N�X��
	case TAG_ITEM_NICK_TASTE:				//���		nickname		�؂̎��̖�
	case TAG_TRNAME_NICK_NICK:				//trainer��		nickname		nickname
	case TAG_TRTYPE_TRNAME_NICK:			//trainer���	trainer��		nickname
	case TAG_TRTYPE_TRNAME_ITEM:			//trainer���	trainer��		���
		max=3;
		break;
	case TAG_NICK_TOKU_NICK_WAZA:			//nickname		������			nickname		�Z��
	case TAG_NICK_TOKU_NICK_TOKU:			//nickname		������			nickname		������
	case TAG_NICK_TOKU_NICK_STAT:			//nickname		������			nickname		�X�e�[�^�X��
	case TAG_NICK_ITEM_NICK_ITEM:			//nickname		���			nickname		���
	case TAG_TRNAME_NICK_TRNAME_NICK:		//trainer��		nickname		trainer��		nickname
	case TAG_TRTYPE_TRNAME_NICK_NICK:		//trainer���	trainer��		nickname		nickname
	case TAG_TRTYPE_TRNAME_NICK_TRNAME:		//trainer���	trainer��		nickname		trainer��
	case TAG_TRTYPE_TRNAME_TRTYPE_TRNAME:	//trainer���	trainer��		trainer���		trainer��
		max=4;
		break;
	case TAG_TRTYPE_TRNAME_NICKx2:			//trainer���	trainer��		nickname ���Q
		max=6;
		break;
	default:
		GF_ASSERT("���݂��Ȃ�TAG�ł��I\n");
		break;
	}

	for(i=0;i<max;i++){
		mpd->msg_para[i]=SkillSeqDataRead(sp);
	}
}

//============================================================================================
/**
 *	MESSAGE_PARAM�\���̃f�[�^�����֐�
 *
 * @param[in]	bw		BATTLE_WORK�\���̂ւ̃|�C���^
 * @param[in]	sp		�T�[�o�p�����[�^�\����
 * @param[in]	mpd		MESSAGE_PARAM_DATA�\���̃f�[�^�ւ̃|�C���^
 * @param[in]	mp		MESSAGE_PARAM�\���̃f�[�^�ւ̃|�C���^
 */
//============================================================================================
static	void	MessageParamMake(BATTLE_WORK *bw,SERVER_PARAM *sp,MESSAGE_PARAM_DATA *mpd,MESSAGE_PARAM *mp)
{
	mp->msg_id=mpd->msg_id;
	mp->msg_tag=mpd->msg_tag;

	switch(mp->msg_tag){
	case TAG_NONE:						//�^�O�Ȃ�
		break;
	case TAG_NONE_DIR:					//�^�O�Ȃ��i�Ă��A�݂������肠��j
		mp->msg_para[0]=SideClientNoGet(bw,sp,mpd->msg_para[0]);
		break;
	case TAG_NICK:						//nickname
		mp->msg_para[0]=MessageParamNicknameGet(bw,sp,mpd->msg_para[0]);
		break;
	case TAG_WAZA:						//�Z��
		mp->msg_para[0]=MessageParamWazaGet(sp,mpd->msg_para[0]);
		break;
	case TAG_STAT:						//�Z��
		mp->msg_para[0]=MessageParamStatusGet(sp,mpd->msg_para[0]);
		break;
	case TAG_ITEM:						//���
		mp->msg_para[0]=MessageParamItemGet(sp,mpd->msg_para[0]);
		break;
	case TAG_NUM:						//���l
	case TAG_NUMS:						//���l
		mp->msg_para[0]=MessageParamNumGet(sp,mpd->msg_para[0]);
		break;
	case TAG_TRNAME:					//trainer��
		mp->msg_para[0]=MessageParamTRNameGet(bw,sp,mpd->msg_para[0]);
		break;
	case TAG_NICK_NICK:					//nickname		nickname
		mp->msg_para[0]=MessageParamNicknameGet(bw,sp,mpd->msg_para[0]);
		mp->msg_para[1]=MessageParamNicknameGet(bw,sp,mpd->msg_para[1]);
		break;
	case TAG_NICK_WAZA:					//nickname		�Z��
		mp->msg_para[0]=MessageParamNicknameGet(bw,sp,mpd->msg_para[0]);
		mp->msg_para[1]=MessageParamWazaGet(sp,mpd->msg_para[1]);
		break;
	case TAG_NICK_TOKU:					//nickname		������
		mp->msg_para[0]=MessageParamNicknameGet(bw,sp,mpd->msg_para[0]);
		mp->msg_para[1]=MessageParamTokuseiGet(bw,sp,mpd->msg_para[1]);
		break;
	case TAG_NICK_STAT:					//nickname		�X�e�[�^�X��
		mp->msg_para[0]=MessageParamNicknameGet(bw,sp,mpd->msg_para[0]);
		mp->msg_para[1]=MessageParamStatusGet(sp,mpd->msg_para[1]);
		break;
	case TAG_NICK_TYPE:					//nickname		�^�C�v��
		mp->msg_para[0]=MessageParamNicknameGet(bw,sp,mpd->msg_para[0]);
		mp->msg_para[1]=MessageParamTypeGet(sp,mpd->msg_para[1]);
		break;
	case TAG_NICK_POKE:					//nickname		�|�P������
		mp->msg_para[0]=MessageParamNicknameGet(bw,sp,mpd->msg_para[0]);
		mp->msg_para[1]=MessageParamPokenameGet(bw,sp,mpd->msg_para[1]);
		break;
	case TAG_NICK_ITEM:					//nickname		���
		mp->msg_para[0]=MessageParamNicknameGet(bw,sp,mpd->msg_para[0]);
		mp->msg_para[1]=MessageParamItemGet(sp,mpd->msg_para[1]);
		break;
	case TAG_NICK_PLOC:					//nickname		�|���b�N��
		mp->msg_para[0]=MessageParamNicknameGet(bw,sp,mpd->msg_para[0]);
		mp->msg_para[1]=MessageParamPolockGet(sp,mpd->msg_para[1]);
		break;
	case TAG_NICK_NUM:					//nickname		���l
		mp->msg_para[0]=MessageParamNicknameGet(bw,sp,mpd->msg_para[0]);
		mp->msg_para[1]=MessageParamNumGet(sp,mpd->msg_para[1]);
		break;
	case TAG_NICK_TRNAME:				//nickname		trainer��
		mp->msg_para[0]=MessageParamNicknameGet(bw,sp,mpd->msg_para[0]);
		mp->msg_para[1]=MessageParamTRNameGet(bw,sp,mpd->msg_para[1]);
		break;
	case TAG_NICK_BOX:					//nickname		�{�b�N�X��
		mp->msg_para[0]=MessageParamNicknameGet(bw,sp,mpd->msg_para[0]);
		mp->msg_para[1]=mpd->msg_para[1];
		break;
	case TAG_WAZA_DIR:					//�Z���i�Ă��A�݂������肠��j
		mp->msg_para[0]=MessageParamWazaGet(sp,mpd->msg_para[0]);
		mp->msg_para[1]=SideClientNoGet(bw,sp,mpd->msg_para[1]);
		break;
	case TAG_WAZA_NICK:					//�Z��			nickname
		mp->msg_para[0]=MessageParamWazaGet(sp,mpd->msg_para[0]);
		mp->msg_para[1]=MessageParamNicknameGet(bw,sp,mpd->msg_para[1]);
		break;
	case TAG_WAZA_WAZA:					//�Z��			�Z��
		mp->msg_para[0]=MessageParamWazaGet(sp,mpd->msg_para[0]);
		mp->msg_para[1]=MessageParamWazaGet(sp,mpd->msg_para[1]);
		break;
	case TAG_TOKU_NICK:					//������		nickname
		mp->msg_para[0]=MessageParamTokuseiGet(bw,sp,mpd->msg_para[0]);
		mp->msg_para[1]=MessageParamNicknameGet(bw,sp,mpd->msg_para[1]);
		break;
	case TAG_ITEM_WAZA:					//���		�Z��
		mp->msg_para[0]=MessageParamItemGet(sp,mpd->msg_para[0]);
		mp->msg_para[1]=MessageParamWazaGet(sp,mpd->msg_para[1]);
		break;
	case TAG_NUM_NUM:					//���l			���l
		mp->msg_para[0]=MessageParamNumGet(sp,mpd->msg_para[0]);
		mp->msg_para[1]=MessageParamNumGet(sp,mpd->msg_para[1]);
		break;
	case TAG_TRNAME_TRNAME:				//trainer��		trainer��
		mp->msg_para[0]=MessageParamTRNameGet(bw,sp,mpd->msg_para[0]);
		mp->msg_para[1]=MessageParamTRNameGet(bw,sp,mpd->msg_para[1]);
		break;
	case TAG_TRNAME_NICK:				//trainer��		nickname
		mp->msg_para[0]=MessageParamTRNameGet(bw,sp,mpd->msg_para[0]);
		mp->msg_para[1]=MessageParamNicknameGet(bw,sp,mpd->msg_para[1]);
		break;
	case TAG_TRNAME_ITEM:				//trainer��		���
		mp->msg_para[0]=MessageParamTRNameGet(bw,sp,mpd->msg_para[0]);
		mp->msg_para[1]=MessageParamItemGet(sp,mpd->msg_para[1]);
		break;
	case TAG_TRNAME_NUM:				//trainer��		���l
		mp->msg_para[0]=MessageParamTRNameGet(bw,sp,mpd->msg_para[0]);
		mp->msg_para[1]=MessageParamNumGet(sp,mpd->msg_para[1]);
		break;
	case TAG_TRTYPE_TRNAME:				//trainer���	trainer��
		mp->msg_para[0]=MessageParamTRTypeGet(bw,sp,mpd->msg_para[0]);
		mp->msg_para[1]=MessageParamTRNameGet(bw,sp,mpd->msg_para[1]);
		break;
	case TAG_NICK_NICK_WAZA:			//nickname		nickname		�Z��
		mp->msg_para[0]=MessageParamNicknameGet(bw,sp,mpd->msg_para[0]);
		mp->msg_para[1]=MessageParamNicknameGet(bw,sp,mpd->msg_para[1]);
		mp->msg_para[2]=MessageParamWazaGet(sp,mpd->msg_para[2]);
		break;
	case TAG_NICK_NICK_TOKU:			//nickname		nickname		������
		mp->msg_para[0]=MessageParamNicknameGet(bw,sp,mpd->msg_para[0]);
		mp->msg_para[1]=MessageParamNicknameGet(bw,sp,mpd->msg_para[1]);
		mp->msg_para[2]=MessageParamTokuseiGet(bw,sp,mpd->msg_para[2]);
		break;
	case TAG_NICK_NICK_ITEM:			//nickname		nickname		���
		mp->msg_para[0]=MessageParamNicknameGet(bw,sp,mpd->msg_para[0]);
		mp->msg_para[1]=MessageParamNicknameGet(bw,sp,mpd->msg_para[1]);
		mp->msg_para[2]=MessageParamItemGet(sp,mpd->msg_para[2]);
		break;
	case TAG_NICK_WAZA_WAZA:			//nickname		�Z��			�Z��
		mp->msg_para[0]=MessageParamNicknameGet(bw,sp,mpd->msg_para[0]);
		mp->msg_para[1]=MessageParamWazaGet(sp,mpd->msg_para[1]);
		mp->msg_para[2]=MessageParamWazaGet(sp,mpd->msg_para[2]);
		break;
	case TAG_NICK_WAZA_NUM:				//nickname		�Z��			���l
		mp->msg_para[0]=MessageParamNicknameGet(bw,sp,mpd->msg_para[0]);
		mp->msg_para[1]=MessageParamWazaGet(sp,mpd->msg_para[1]);
		mp->msg_para[2]=MessageParamNumGet(sp,mpd->msg_para[2]);
		break;
	case TAG_NICK_TOKU_NICK:			//nickname		������			nickname
		mp->msg_para[0]=MessageParamNicknameGet(bw,sp,mpd->msg_para[0]);
		mp->msg_para[1]=MessageParamTokuseiGet(bw,sp,mpd->msg_para[1]);
		mp->msg_para[2]=MessageParamNicknameGet(bw,sp,mpd->msg_para[2]);
		break;
	case TAG_NICK_TOKU_WAZA:			//nickname		������			�Z��
		mp->msg_para[0]=MessageParamNicknameGet(bw,sp,mpd->msg_para[0]);
		mp->msg_para[1]=MessageParamTokuseiGet(bw,sp,mpd->msg_para[1]);
		mp->msg_para[2]=MessageParamWazaGet(sp,mpd->msg_para[2]);
		break;
	case TAG_NICK_TOKU_ITEM:			//nickname		������			���
		mp->msg_para[0]=MessageParamNicknameGet(bw,sp,mpd->msg_para[0]);
		mp->msg_para[1]=MessageParamTokuseiGet(bw,sp,mpd->msg_para[1]);
		mp->msg_para[2]=MessageParamItemGet(sp,mpd->msg_para[2]);
		break;
	case TAG_NICK_TOKU_STAT:			//nickname		������			�X�e�[�^�X��
		mp->msg_para[0]=MessageParamNicknameGet(bw,sp,mpd->msg_para[0]);
		mp->msg_para[1]=MessageParamTokuseiGet(bw,sp,mpd->msg_para[1]);
		mp->msg_para[2]=MessageParamStatusGet(sp,mpd->msg_para[2]);
		break;
	case TAG_NICK_TOKU_TYPE:			//nickname		������			�^�C�v��
		mp->msg_para[0]=MessageParamNicknameGet(bw,sp,mpd->msg_para[0]);
		mp->msg_para[1]=MessageParamTokuseiGet(bw,sp,mpd->msg_para[1]);
		mp->msg_para[2]=MessageParamTypeGet(sp,mpd->msg_para[2]);
		break;
	case TAG_NICK_TOKU_COND:			//nickname		������			��Ԉُ햼
		mp->msg_para[0]=MessageParamNicknameGet(bw,sp,mpd->msg_para[0]);
		mp->msg_para[1]=MessageParamTokuseiGet(bw,sp,mpd->msg_para[1]);
		mp->msg_para[2]=MessageParamConditionGet(sp,mpd->msg_para[2]);
		break;
	case TAG_NICK_TOKU_NUM:				//nickname		������			���l
		mp->msg_para[0]=MessageParamNicknameGet(bw,sp,mpd->msg_para[0]);
		mp->msg_para[1]=MessageParamTokuseiGet(bw,sp,mpd->msg_para[1]);
		mp->msg_para[2]=MessageParamNumGet(sp,mpd->msg_para[2]);
		break;
	case TAG_NICK_ITEM_NICK:			//nickname		���			nickname
		mp->msg_para[0]=MessageParamNicknameGet(bw,sp,mpd->msg_para[0]);
		mp->msg_para[1]=MessageParamItemGet(sp,mpd->msg_para[1]);
		mp->msg_para[2]=MessageParamNicknameGet(bw,sp,mpd->msg_para[2]);
		break;
	case TAG_NICK_ITEM_WAZA:			//nickname		���			�Z��
		mp->msg_para[0]=MessageParamNicknameGet(bw,sp,mpd->msg_para[0]);
		mp->msg_para[1]=MessageParamItemGet(sp,mpd->msg_para[1]);
		mp->msg_para[2]=MessageParamWazaGet(sp,mpd->msg_para[2]);
		break;
	case TAG_NICK_ITEM_STAT:			//nickname		���			�X�e�[�^�X��
		mp->msg_para[0]=MessageParamNicknameGet(bw,sp,mpd->msg_para[0]);
		mp->msg_para[1]=MessageParamItemGet(sp,mpd->msg_para[1]);
		mp->msg_para[2]=MessageParamStatusGet(sp,mpd->msg_para[2]);
		break;
	case TAG_NICK_ITEM_COND:			//nickname		���			��Ԉُ햼
		mp->msg_para[0]=MessageParamNicknameGet(bw,sp,mpd->msg_para[0]);
		mp->msg_para[1]=MessageParamItemGet(sp,mpd->msg_para[1]);
		mp->msg_para[2]=MessageParamConditionGet(sp,mpd->msg_para[2]);
		break;
	case TAG_NICK_BOX_BOX:				//nickname		�{�b�N�X��		�{�b�N�X��
		mp->msg_para[0]=MessageParamNicknameGet(bw,sp,mpd->msg_para[0]);
		mp->msg_para[1]=mpd->msg_para[1];
		mp->msg_para[2]=mpd->msg_para[2];
		break;
	case TAG_ITEM_NICK_TASTE:			//���		nickname		�؂̎��̖�
		mp->msg_para[0]=MessageParamItemGet(sp,mpd->msg_para[0]);
		mp->msg_para[1]=MessageParamNicknameGet(bw,sp,mpd->msg_para[1]);
		mp->msg_para[2]=MessageParamTasteGet(sp,mpd->msg_para[2]);
		break;
	case TAG_TRNAME_NICK_NICK:			//trainer��		nickname		nickname
		mp->msg_para[0]=MessageParamTRNameGet(bw,sp,mpd->msg_para[0]);
		mp->msg_para[1]=MessageParamNicknameGet(bw,sp,mpd->msg_para[1]);
		mp->msg_para[2]=MessageParamNicknameGet(bw,sp,mpd->msg_para[2]);
		break;
	case TAG_TRTYPE_TRNAME_NICK:		//trainer���	trainer��		nickname
		mp->msg_para[0]=MessageParamTRTypeGet(bw,sp,mpd->msg_para[0]);
		mp->msg_para[1]=MessageParamTRNameGet(bw,sp,mpd->msg_para[1]);
		mp->msg_para[2]=MessageParamNicknameGet(bw,sp,mpd->msg_para[2]);
		break;
	case TAG_TRTYPE_TRNAME_ITEM:		//trainer���	trainer��		���
		mp->msg_para[0]=MessageParamTRTypeGet(bw,sp,mpd->msg_para[0]);
		mp->msg_para[1]=MessageParamTRNameGet(bw,sp,mpd->msg_para[1]);
		mp->msg_para[2]=MessageParamItemGet(sp,mpd->msg_para[2]);
		break;
	case TAG_NICK_TOKU_NICK_WAZA:		//nickname		������			nickname		�Z��
		mp->msg_para[0]=MessageParamNicknameGet(bw,sp,mpd->msg_para[0]);
		mp->msg_para[1]=MessageParamTokuseiGet(bw,sp,mpd->msg_para[1]);
		mp->msg_para[2]=MessageParamNicknameGet(bw,sp,mpd->msg_para[2]);
		mp->msg_para[3]=MessageParamWazaGet(sp,mpd->msg_para[3]);
		break;
	case TAG_NICK_TOKU_NICK_TOKU:		//nickname		������			nickname		������
		mp->msg_para[0]=MessageParamNicknameGet(bw,sp,mpd->msg_para[0]);
		mp->msg_para[1]=MessageParamTokuseiGet(bw,sp,mpd->msg_para[1]);
		mp->msg_para[2]=MessageParamNicknameGet(bw,sp,mpd->msg_para[2]);
		mp->msg_para[3]=MessageParamTokuseiGet(bw,sp,mpd->msg_para[3]);
		break;
	case TAG_NICK_TOKU_NICK_STAT:		//nickname		������			nickname		�X�e�[�^�X��
		mp->msg_para[0]=MessageParamNicknameGet(bw,sp,mpd->msg_para[0]);
		mp->msg_para[1]=MessageParamTokuseiGet(bw,sp,mpd->msg_para[1]);
		mp->msg_para[2]=MessageParamNicknameGet(bw,sp,mpd->msg_para[2]);
		mp->msg_para[3]=MessageParamStatusGet(sp,mpd->msg_para[3]);
		break;
	case TAG_NICK_ITEM_NICK_ITEM:		//nickname		���			nickname		���
		mp->msg_para[0]=MessageParamNicknameGet(bw,sp,mpd->msg_para[0]);
		mp->msg_para[1]=MessageParamItemGet(sp,mpd->msg_para[1]);
		mp->msg_para[2]=MessageParamNicknameGet(bw,sp,mpd->msg_para[2]);
		mp->msg_para[3]=MessageParamItemGet(sp,mpd->msg_para[3]);
		break;
	case TAG_TRNAME_NICK_TRNAME_NICK:	//trainer��		nickname		trainer��		nickname
		mp->msg_para[0]=MessageParamTRNameGet(bw,sp,mpd->msg_para[0]);
		mp->msg_para[1]=MessageParamNicknameGet(bw,sp,mpd->msg_para[1]);
		mp->msg_para[2]=MessageParamTRNameGet(bw,sp,mpd->msg_para[2]);
		mp->msg_para[3]=MessageParamNicknameGet(bw,sp,mpd->msg_para[3]);
		break;
	case TAG_TRTYPE_TRNAME_NICK_NICK:	//trainer���	trainer��		nickname		nickname
		mp->msg_para[0]=MessageParamTRTypeGet(bw,sp,mpd->msg_para[0]);
		mp->msg_para[1]=MessageParamTRNameGet(bw,sp,mpd->msg_para[1]);
		mp->msg_para[2]=MessageParamNicknameGet(bw,sp,mpd->msg_para[2]);
		mp->msg_para[3]=MessageParamNicknameGet(bw,sp,mpd->msg_para[3]);
		break;
	case TAG_TRTYPE_TRNAME_NICK_TRNAME:	//trainer���	trainer��		nickname		trainer��
		mp->msg_para[0]=MessageParamTRTypeGet(bw,sp,mpd->msg_para[0]);
		mp->msg_para[1]=MessageParamTRNameGet(bw,sp,mpd->msg_para[1]);
		mp->msg_para[2]=MessageParamNicknameGet(bw,sp,mpd->msg_para[2]);
		mp->msg_para[3]=MessageParamTRNameGet(bw,sp,mpd->msg_para[3]);
		break;
	case TAG_TRTYPE_TRNAME_TRTYPE_TRNAME:	//trainer���	trainer��		trainer���		trainer��
		mp->msg_para[0]=MessageParamTRTypeGet(bw,sp,mpd->msg_para[0]);
		mp->msg_para[1]=MessageParamTRNameGet(bw,sp,mpd->msg_para[1]);
		mp->msg_para[2]=MessageParamTRTypeGet(bw,sp,mpd->msg_para[2]);
		mp->msg_para[3]=MessageParamTRNameGet(bw,sp,mpd->msg_para[3]);
		break;
	case TAG_TRTYPE_TRNAME_NICKx2:		//trainer���	trainer��		nickname ���Q
		mp->msg_para[0]=MessageParamTRTypeGet(bw,sp,mpd->msg_para[0]);
		mp->msg_para[1]=MessageParamTRNameGet(bw,sp,mpd->msg_para[1]);
		mp->msg_para[2]=MessageParamNicknameGet(bw,sp,mpd->msg_para[2]);
		mp->msg_para[3]=MessageParamTRTypeGet(bw,sp,mpd->msg_para[3]);
		mp->msg_para[4]=MessageParamTRNameGet(bw,sp,mpd->msg_para[4]);
		mp->msg_para[5]=MessageParamNicknameGet(bw,sp,mpd->msg_para[5]);
		break;
	default:
		GF_ASSERT("���݂��Ȃ�TAG�ł��I\n");
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
static	int	MessageParamNicknameGet(BATTLE_WORK *bw,SERVER_PARAM *sp,int para)
{
	int ret;
	int	client_no;

	client_no=SideClientNoGet(bw,sp,para);

	ret=client_no;

	if(para==SIDE_RESHUFFLE_AFTER){
		ret|=sp->reshuffle_sel_mons_no[client_no]<<8;
	}
	else{
		ret|=sp->sel_mons_no[client_no]<<8;
	}

	return ret;
}

//============================================================================================
/**
 *	MESSAGE_PARAM�\���̃f�[�^�����֐��i�Z�i���o�[�j
 *
 * @param[in]	sp		�T�[�o�p�����[�^�\����
 * @param[in]	para	�����Ώۃp�����[�^�iSIDE_ATTACK�ASIDE_DEFENCE�Ȃǁj
 */
//============================================================================================
static	int	MessageParamWazaGet(SERVER_PARAM *sp,int para)
{
	int ret;

	switch(para){
	case SIDE_ATTACK:
		ret=sp->waza_no_now;
		break;
	case SIDE_WORK:
		ret=sp->waza_work;
		break;
	default:
		OS_Printf("MessageParamWazaGet:�����ɂ���̂͂�������\n");
		break;
	}
	return ret;
}

//============================================================================================
/**
 *	MESSAGE_PARAM�\���̃f�[�^�����֐��i����i���o�[�j
 *
 * @param[in]	sp		�T�[�o�p�����[�^�\����
 * @param[in]	para	�����Ώۃp�����[�^�iSIDE_ATTACK�ASIDE_DEFENCE�Ȃǁj
 */
//============================================================================================
static	int	MessageParamItemGet(SERVER_PARAM *sp,int para)
{
	int ret;

	switch(para){
	case SIDE_ATTACK:
		ret=sp->psp[sp->attack_client].item;
		SoubiItemSet(sp,sp->attack_client,ret);
		break;
	case SIDE_DEFENCE:
		ret=sp->psp[sp->defence_client].item;
		SoubiItemSet(sp,sp->defence_client,ret);
		break;
	case SIDE_CLIENT_WORK:
		ret=sp->psp[sp->client_work].item;
		SoubiItemSet(sp,sp->client_work,ret);
		break;
	case SIDE_WORK:
		ret=sp->item_work;
		break;
	default:
		OS_Printf("MessageParamItemGet:�����ɂ���̂͂�������\n");
		break;
	}
	return ret;
}

//============================================================================================
/**
 *	MESSAGE_PARAM�\���̃f�[�^�����֐��i���l�j
 *
 * @param[in]	sp		�T�[�o�p�����[�^�\����
 * @param[in]	para	�����Ώۃp�����[�^�iSIDE_ATTACK�ASIDE_DEFENCE�Ȃǁj
 */
//============================================================================================
static	int	MessageParamNumGet(SERVER_PARAM *sp,int para)
{
	int ret;

	switch(para){
	case SIDE_WORK:
		ret=sp->msg_work;
		break;
	default:
		OS_Printf("MessageParamNumGet:�����ɂ���̂͂�������\n");
		break;
	}
	return ret;
}

//============================================================================================
/**
 *	MESSAGE_PARAM�\���̃f�[�^�����֐��i�^�C�v�j
 *
 * @param[in]	sp		�T�[�o�p�����[�^�\����
 * @param[in]	para	�����Ώۃp�����[�^�iSIDE_ATTACK�ASIDE_DEFENCE�Ȃǁj
 */
//============================================================================================
static	int	MessageParamTypeGet(SERVER_PARAM *sp,int para)
{
	int ret;

	switch(para){
	case SIDE_WORK:
		ret=sp->msg_work;
		break;
	default:
		OS_Printf("MessageParamTypeGet:�����ɂ���̂͂�������\n");
		break;
	}
	return ret;
}

//============================================================================================
/**
 *	MESSAGE_PARAM�\���̃f�[�^�����֐��i�����j
 *
 * @param[in]	sp		�T�[�o�p�����[�^�\����
 * @param[in]	para	�����Ώۃp�����[�^�iSIDE_ATTACK�ASIDE_DEFENCE�Ȃǁj
 */
//============================================================================================
static	int	MessageParamTokuseiGet(BATTLE_WORK *bw,SERVER_PARAM *sp,int para)
{
	int ret;
	int	client_no;

	switch(para){
	case SIDE_WORK:
		ret=sp->tokusei_work;
		break;
	default:
		client_no=SideClientNoGet(bw,sp,para);
		ret=sp->psp[client_no].speabino;
		TokusyuNoSet(sp,client_no,ret);
		break;
	}
	return ret;
}

//============================================================================================
/**
 *	MESSAGE_PARAM�\���̃f�[�^�����֐��i�X�e�[�^�X���j
 *
 * @param[in]	sp		�T�[�o�p�����[�^�\����
 * @param[in]	para	�����Ώۃp�����[�^�iSIDE_ATTACK�ASIDE_DEFENCE�Ȃǁj
 */
//============================================================================================
static	int	MessageParamStatusGet(SERVER_PARAM *sp,int para)
{
	int ret;

	switch(para){
	case SIDE_WORK:
		ret=sp->msg_work;
		break;
	default:
		OS_Printf("MessageParamStatusGet:�����ɂ���̂͂�������\n");
		break;
	}
	return ret;
}

//============================================================================================
/**
 *	MESSAGE_PARAM�\���̃f�[�^�����֐��i��Ԉُ햼�j
 *
 * @param[in]	sp		�T�[�o�p�����[�^�\����
 * @param[in]	para	�����Ώۃp�����[�^�iSIDE_ATTACK�ASIDE_DEFENCE�Ȃǁj
 */
//============================================================================================
static	int	MessageParamConditionGet(SERVER_PARAM *sp,int para)
{
	int ret;

	switch(para){
	case SIDE_WORK:
		ret=sp->msg_work;
		break;
	default:
		OS_Printf("MessageParamConditionGet:�����ɂ���̂͂�������\n");
		break;
	}
	return ret;
}

//============================================================================================
/**
 *	MESSAGE_PARAM�\���̃f�[�^�����֐��i�|�P�������j
 *
 * @param[in]	sp		�T�[�o�p�����[�^�\����
 * @param[in]	para	�����Ώۃp�����[�^�iSIDE_ATTACK�ASIDE_DEFENCE�Ȃǁj
 */
//============================================================================================
static	int	MessageParamPokenameGet(BATTLE_WORK *bw,SERVER_PARAM *sp,int para)
{
	int ret;
	int	client_no;

	client_no=SideClientNoGet(bw,sp,para);

	ret=client_no;
	ret|=sp->sel_mons_no[client_no]<<8;

	return ret;
}

//============================================================================================
/**
 *	MESSAGE_PARAM�\���̃f�[�^�����֐��i�|���b�N���j
 *
 * @param[in]	sp		�T�[�o�p�����[�^�\����
 * @param[in]	para	�����Ώۃp�����[�^�iSIDE_ATTACK�ASIDE_DEFENCE�Ȃǁj
 */
//============================================================================================
static	int	MessageParamPolockGet(SERVER_PARAM *sp,int para)
{
	int ret;

	switch(para){
	case SIDE_WORK:
		ret=sp->msg_work;
		break;
	default:
		OS_Printf("MessageParamPolockGet:�����ɂ���̂͂�������\n");
		break;
	}
	return ret;
}

//============================================================================================
/**
 *	MESSAGE_PARAM�\���̃f�[�^�����֐��i�؂̎��̖��j
 *
 * @param[in]	sp		�T�[�o�p�����[�^�\����
 * @param[in]	para	�����Ώۃp�����[�^�iSIDE_ATTACK�ASIDE_DEFENCE�Ȃǁj
 */
//============================================================================================
static	int	MessageParamTasteGet(SERVER_PARAM *sp,int para)
{
	int ret;

	switch(para){
	case SIDE_WORK:
		ret=sp->msg_work;
		break;
	default:
		OS_Printf("MessageParamTasteGet:�����ɂ���̂͂�������\n");
		break;
	}
	return ret;
}

//============================================================================================
/**
 *	MESSAGE_PARAM�\���̃f�[�^�����֐��i�g���[�i�[��ʁj
 *
 * @param[in]	sp		�T�[�o�p�����[�^�\����
 * @param[in]	para	�����Ώۃp�����[�^�iSIDE_ATTACK�ASIDE_DEFENCE�Ȃǁj
 */
//============================================================================================
static	int	MessageParamTRTypeGet(BATTLE_WORK *bw,SERVER_PARAM *sp,int para)
{
#if 0
	ret=BattleWorkTrainerIDGet(bw,client_no);
	ret=TT_TrainerDataParaGet(ret,ID_TD_tr_type);
#endif
	return SideClientNoGet(bw,sp,para);
}

//============================================================================================
/**
 *	MESSAGE_PARAM�\���̃f�[�^�����֐��i�g���[�i�[���j
 *
 * @param[in]	sp		�T�[�o�p�����[�^�\����
 * @param[in]	para	�����Ώۃp�����[�^�iSIDE_ATTACK�ASIDE_DEFENCE�Ȃǁj
 */
//============================================================================================
static	int	MessageParamTRNameGet(BATTLE_WORK *bw,SERVER_PARAM *sp,int para)
{
	return SideClientNoGet(bw,sp,para);
}

//============================================================================================
/**
 *	�T���|�P�����̃��x���A�b�v���ɕ\������A�C�R���̐���
 *
 * @param[in]	bw		�퓬�V�X�e���\����
 * @param[in]	tsiw	TCB_SKILL_INTP_WORK�\����
 * @param[in]	mons_no	�����Ώۃ����X�^�[�i���o�[
 */
//============================================================================================

#define	BENCH_LEVELUP_ICON_X		(128)
#define	BENCH_LEVELUP_ICON_Y		(0)
#define	BENCH_LEVELUP_POKEICON_X	(152)
#define	BENCH_LEVELUP_POKEICON_Y	(24)
#define	BENCH_LEVELUP_NAME_X		(176)
#define	BENCH_LEVELUP_NAME_Y		(8)

#define	BENCH_LEVELUP_ICON_PRI		(200)
#define	BENCH_LEVELUP_POKEICON_PRI	(100)
#define	BENCH_LEVELUP_NAME_PRI		(100)

///�v���[�g�A�C�R���F�A�N�^�[�w�b�_
static const TCATS_OBJECT_ADD_PARAM_S PlateIconObjParam = {
	BENCH_LEVELUP_ICON_X, BENCH_LEVELUP_ICON_Y, 0,		//x, y, z
	0, BENCH_LEVELUP_ICON_PRI, 0,		//�A�j���ԍ��A�D�揇�ʁA�p���b�g�ԍ�
	NNS_G2D_VRAM_TYPE_2DMAIN,		//�`��G���A
	{	//�g�p���\�[�XID�e�[�u��
		CHARID_BENCH_LEVELUP_ICON,		//�L����
		PLTTID_BENCH_LEVELUP_ICON,		//�p���b�g
		CELLID_BENCH_LEVELUP_ICON,		//�Z��
		CELLANMID_BENCH_LEVELUP_ICON,	//�Z���A�j��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z��
		CLACT_U_HEADER_DATA_NONE,		//�}���`�Z���A�j��
	},
	1,			//BG�v���C�I���e�B
	0,			//Vram�]���t���O
};

///�|�P�����A�C�R���F�A�N�^�[�w�b�_
static const TCATS_OBJECT_ADD_PARAM_S PokeIconObjParam = {
	BENCH_LEVELUP_POKEICON_X, BENCH_LEVELUP_POKEICON_Y, 0,		//x, y, z
	0, BENCH_LEVELUP_POKEICON_PRI, 0,		//�A�j���ԍ��A�D�揇�ʁA�p���b�g�ԍ�
	NNS_G2D_VRAM_TYPE_2DMAIN,				//�`��G���A
	{	//�g�p���\�[�XID�e�[�u��
		CHARID_BENCH_LEVELUP_POKEICON,		//�L����
		PLTTID_BENCH_LEVELUP_POKEICON,		//�p���b�g
		CELLID_BENCH_LEVELUP_POKEICON,		//�Z��
		CELLANMID_BENCH_LEVELUP_POKEICON,	//�Z���A�j��
		CLACT_U_HEADER_DATA_NONE,			//�}���`�Z��
		CLACT_U_HEADER_DATA_NONE,			//�}���`�Z���A�j��
	},
	1,			//BG�v���C�I���e�B
	0,			//Vram�]���t���O
};

static void BenchLevelUpPokeIconActorSet(BATTLE_WORK *bw,TCB_SKILL_INTP_WORK *tsiw,POKEMON_PARAM *pp)
{
	TCATS_OBJECT_ADD_PARAM_S	obj_param;
	CATS_SYS_PTR				csp;
	CATS_RES_PTR				crp;
	PALETTE_FADE_PTR			pfd;
	MSGDATA_MANAGER				*msg_man;
	WORDSET						*wordset;
	STRBUF						*str_src,*str_buf;
	GF_BGL_INI					*bgl;
	GF_BGL_BMPWIN				bmpwin;
	int							vram_size;
	CHAR_MANAGER_ALLOCDATA		cma;
	FONTOAM_INIT				finit;
	int							sex;
	
	msg_man=BattleWorkFightMsgGet(bw);
	str_buf=BattleWorkSTRBUFGet(bw);
	wordset=BattleWorkWORDSETGet(bw);
	bgl=BattleWorkGF_BGL_INIGet(bw);
	csp=BattleWorkCATS_SYS_PTRGet(bw);
	crp=BattleWorkCATS_RES_PTRGet(bw);
	pfd=BattleWorkPfdGet(bw);
	
	//�v���[�g
	CATS_LoadResourceCharArc(csp,crp,ARC_BATT_OBJ,LV_UP_PLATE_NCGR_BIN,1,NNS_G2D_VRAM_TYPE_2DMAIN,CHARID_BENCH_LEVELUP_ICON);
	CATS_LoadResourcePlttWorkArc(pfd,FADE_MAIN_OBJ,csp,crp,ARC_BATT_OBJ,LV_UP_PLATE_NCLR,0,2,NNS_G2D_VRAM_TYPE_2DMAIN,PLTTID_BENCH_LEVELUP_ICON);
	CATS_LoadResourceCellArc(csp,crp,ARC_BATT_OBJ,LV_UP_PLATE_NCER_BIN,1,CELLID_BENCH_LEVELUP_ICON);
	CATS_LoadResourceCellAnmArc(csp,crp,ARC_BATT_OBJ,LV_UP_PLATE_NANR_BIN,1,CELLANMID_BENCH_LEVELUP_ICON);

	tsiw->cap[0]=CATS_ObjectAdd_S(csp,crp,&PlateIconObjParam);
	CATS_ObjectUpdateCap(tsiw->cap[0]);

	//�|�P�����A�C�R��
	//�L�������\�[�X
	CATS_LoadResourceCharArcModeAdjustAreaCont(csp,crp,ARC_POKEICON,PokeIconCgxArcIndexGetByPP(pp),0,
							 NNS_G2D_VRAM_TYPE_2DMAIN,CHARID_BENCH_LEVELUP_POKEICON);
	//�p���b�g
	CATS_LoadResourcePlttWorkArc(pfd,FADE_MAIN_OBJ,csp,crp,ARC_POKEICON,PokeIconPalArcIndexGet(),0,POKEICON_PAL_MAX, 
								 NNS_G2D_VRAM_TYPE_2DMAIN,PLTTID_BENCH_LEVELUP_POKEICON);
	//�Z��
	CATS_LoadResourceCellArc(csp,crp,ARC_POKEICON,PokeIcon64kCellArcIndexGet(),0,CELLID_BENCH_LEVELUP_POKEICON);
	//�Z���A�j��
	CATS_LoadResourceCellAnmArc(csp,crp,ARC_POKEICON,PokeIcon64kCellAnmArcIndexGet(),0,CELLANMID_BENCH_LEVELUP_POKEICON);
	
	tsiw->cap[1]=CATS_ObjectAdd_S(csp, crp, &PokeIconObjParam);
	//�p���b�g�؂�ւ�
	CLACT_PaletteOffsetChgAddTransPlttNo(tsiw->cap[1]->act,PokeIconPalNumGetByPP(pp));
	
	CATS_ObjectUpdateCap(tsiw->cap[1]);

	//FontOam
	tsiw->work_p[GE_FONTOAM]=FONTOAM_SysInit(1,HEAPID_BATTLE);
	if(PokeParaGet(pp,ID_PARA_nidoran_nickname,NULL)==FALSE){
		sex=PARA_UNK;
	}
	else{
		sex=PokeParaGet(pp,ID_PARA_sex,NULL);
	}

	if(sex==PARA_MALE){
		str_src=MSGMAN_AllocString(msg_man,LevelUpBenchMaleMsg);
	}
	else if(sex==PARA_FEMALE){
		str_src=MSGMAN_AllocString(msg_man,LevelUpBenchFemaleMsg);
	}
	else{
		str_src=MSGMAN_AllocString(msg_man,LevelUpBenchUnknownMsg);
	}
	WORDSET_RegisterPokeNickName(wordset,0,PPPPointerGet(pp));
	WORDSET_RegisterNumber(wordset,1,PokeParaGet(pp,ID_PARA_level,NULL),3,NUMBER_DISPTYPE_LEFT,NUMBER_CODETYPE_DEFAULT);
	WORDSET_ExpandStr(wordset,str_buf,str_src);
	STRBUF_Delete(str_src);

	GF_BGL_BmpWinInit(&bmpwin);
	GF_BGL_BmpWinObjAdd(bgl,&bmpwin,BUFLEN_POKEMON_NAME,4,0,0);
	GF_STR_PrintColor(&bmpwin,FONT_SYSTEM,str_buf,0,0,MSG_NO_PUT,GF_PRINTCOLOR_MAKE(1,2,0),NULL);

	vram_size=FONTOAM_NeedCharSize(&bmpwin,NNS_G2D_VRAM_TYPE_2DMAIN,HEAPID_BATTLE);
	CharVramAreaAlloc(vram_size,CHARM_CONT_AREACONT,NNS_G2D_VRAM_TYPE_2DMAIN,&cma);
	finit.fontoam_sys=tsiw->work_p[GE_FONTOAM];
	finit.bmp=&bmpwin;
	finit.clact_set=CATS_GetClactSetPtr(crp);
	finit.pltt=CATS_PlttProxy(crp,PLTTID_BENCH_LEVELUP_ICON);
	finit.parent=NULL;
	finit.char_ofs=cma.alloc_ofs;
	finit.x=BENCH_LEVELUP_NAME_X;
	finit.y=BENCH_LEVELUP_NAME_Y;
	finit.bg_pri=0;
	finit.soft_pri=BENCH_LEVELUP_NAME_PRI;
	finit.draw_area=NNS_G2D_VRAM_TYPE_2DMAIN;
	finit.heap=HEAPID_BATTLE;

	tsiw->fop=FONTOAM_Init(&finit);
	tsiw->cma=cma;

	FONTOAM_SetPaletteOffsetAddTransPlttNo(tsiw->fop,1);

	GF_BGL_BmpWinDel(&bmpwin);
}

//============================================================================================
/**
 *	�T���|�P�����̃��x���A�b�v���ɕ\������A�C�R���̍폜
 *
 * @param[in]	bw		�퓬�V�X�e���\����
 * @param[in]	tsiw	TCB_SKILL_INTP_WORK�\����
 */
//============================================================================================
static void BenchLevelUpPokeIconActorDelete(BATTLE_WORK *bw,TCB_SKILL_INTP_WORK *tsiw)
{
	CATS_RES_PTR				crp;

	crp=BattleWorkCATS_RES_PTRGet(bw);

	CATS_ActorPointerDelete_S(tsiw->cap[0]);
	CATS_ActorPointerDelete_S(tsiw->cap[1]);
	FONTOAM_Delete(tsiw->fop);
	CharVramAreaFree(&tsiw->cma);

	//�v���[�g
	CATS_FreeResourceChar(crp,CHARID_BENCH_LEVELUP_ICON);
	CATS_FreeResourcePltt(crp,PLTTID_BENCH_LEVELUP_ICON);
	CATS_FreeResourceCell(crp,CELLID_BENCH_LEVELUP_ICON);
	CATS_FreeResourceCellAnm(crp,CELLANMID_BENCH_LEVELUP_ICON);

	//�|�P�����A�C�R��
	CATS_FreeResourceChar(crp,CHARID_BENCH_LEVELUP_POKEICON);
	CATS_FreeResourcePltt(crp,PLTTID_BENCH_LEVELUP_POKEICON);
	CATS_FreeResourceCell(crp,CELLID_BENCH_LEVELUP_POKEICON);
	CATS_FreeResourceCellAnm(crp,CELLANMID_BENCH_LEVELUP_POKEICON);

	FONTOAM_SysDelete(tsiw->work_p[GE_FONTOAM]);
}

//=========================================================================
/**
 *	�m���̂Ƃ��̂Ȃ��x�v�Z���[�`��
 *
 * @param[in]	bw				�퓬�V�X�e���\����
 * @param[in]	kizetsu_client	�m���ɂȂ���ClientNo
 */
//=========================================================================

static	void	HinshiFriendCalc(BATTLE_WORK *bw,SERVER_PARAM *sp,int kizetsu_client)
{
	POKEMON_PARAM	*pp;
	u8				clientno,clientno2;

	//�G���́A�v�Z�Ȃ�
	if(BattleWorkMineEnemyCheck(bw,kizetsu_client)){
		return;
	}

	if(BattleWorkFightTypeGet(bw)&FIGHT_TYPE_2vs2){
		clientno=BattleWorkClientNoGet(bw,CLIENT_TYPE_B);
		clientno2=BattleWorkClientNoGet(bw,CLIENT_TYPE_D);
		if(sp->psp[clientno2].level>sp->psp[clientno].level){
			clientno=clientno2;
		}
	}
	else{
		clientno=BattleWorkClientNoGet(bw,CLIENT_TYPE_BB);
	}

	pp=BattleWorkPokemonParamGet(bw,kizetsu_client,sp->sel_mons_no[kizetsu_client]);

	if(sp->psp[clientno].level>sp->psp[kizetsu_client].level){
		if(sp->psp[clientno].level-sp->psp[kizetsu_client].level>=30){
			FriendCalc(pp,FRIEND_LEVEL30_HINSHI,BattleWorkPlaceIDGet(bw));
		}
		else{
			FriendCalc(pp,FRIEND_HINSHI,BattleWorkPlaceIDGet(bw));
		}
	}
	else{
		FriendCalc(pp,FRIEND_HINSHI,BattleWorkPlaceIDGet(bw));
	}
}

//=========================================================================
/**
 *	AI�p�������[�N�ɓ����i���o�[���Z�b�g
 *
 * @param[in]	sp			�T�[�o�V�X�e���\����
 * @param[in]	client_no	�Z�b�g����ClientNo
 * @param[in]	speabino	�Z�b�g��������i���o�[
 */
//=========================================================================
static	void	TokusyuNoSet(SERVER_PARAM *sp,u8 client_no,u8 speabino)
{
	sp->AIWT.AI_TOKUSYUNO[client_no]=speabino;
}

//=========================================================================
/**
 *	AI�p�����A�C�e�����[�N�ɃA�C�e���i���o�[���Z�b�g
 *
 * @param[in]	sp			�T�[�o�V�X�e���\����
 * @param[in]	client_no	�Z�b�g����ClientNo
 * @param[in]	item_no		�Z�b�g����A�C�e���i���o�[
 */
//=========================================================================
static	void	SoubiItemSet(SERVER_PARAM *sp,u8 client_no,u16 item_no)
{
	sp->AIWT.AI_SOUBIITEM[client_no]=item_no;
}

