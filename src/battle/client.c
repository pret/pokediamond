
//============================================================================================
/**
 * @file	client.c
 * @bfief	�퓬�N���C�A���g�v���O����
 * @author	HisashiSogabe
 * @date	05.05.24
 */
//============================================================================================

#include "common.h"
#include "battle/battle_server.h"
#include "battle/fight.h"
#include "battle/client.h"
#include "battle/client_tool.h"
#include "battle/wazano_def.h"
#include "battle/tokusyu_def.h"
#include "battle/battle_id.h"

#include "system/window.h"

#include "communication/communication.h"

#include "client_def.h"
#include "gauge.h"
#include "client_eff.h"
#include "temoti_gauge.h"

//============================================================================================
/**
 * �v���g�^�C�v�錾
 */
//============================================================================================

//�O�����J�֐��Q
CLIENT_PARAM	*ClientInit(BATTLE_WORK *bw,FIGHT_SYSTEM_BOOT_PARAM *fsbp);
void	ClientMain(BATTLE_WORK *battle_work,CLIENT_PARAM *client_param);
void	ClientEnd(BATTLE_WORK *bw,CLIENT_PARAM *cp,int mode);

void	ClientBMInit(BATTLE_WORK *battle_work,CLIENT_PARAM *client_param,int ballID,int sel_mons_no);

//�֐��W�����v�e�[�u��
static	void	ClientDummy(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientEncountEffect(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientPokemonEncount(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientPokemonEncountAppear(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientPokemonAppear(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientPokemonReturn(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientPokemonInhale(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientPokemonDelete(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientTrainerEncount(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientTrainerThrow(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientTrainerOut(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientTrainerIn(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientHPGaugeIn(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientHPGaugeOut(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientCommandSelect(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientWazaSelect(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientDirSelect(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientItemSelect(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientPokemonSelect(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientYesNoSelect(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientAttackMessage(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientMessage(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientWazaEffect(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientPokemonBlinkSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientHPGaugeCalcSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientEXPGaugeCalcSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClienKizetsuEffectSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientSePlaySet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientFadeOutSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientPokemonVanishOnOff(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientHPGaugeStatusSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientTrainerMessageSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientModosuMessageSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientKuridasuMessageSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientEncountMessageSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientEncountKuridasuMessageSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientLevelUpEffectSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientAlertMessageSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientHPGaugeRefresh(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientPSPtoPPCopy(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientTrainerBGSlideIn(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientGaugeAnimeStop(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientPokemonRefresh(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientWazaWasure(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientMosaicSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientFormChgSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientBGChgSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientSubBGWallPut(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientBallGaugeEncountSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientBallGaugeEncountOut(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientBallGaugeSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientBallGaugeOut(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientBallGaugeResourceLoad(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientBallGaugeResourceDelete(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientIncRecord(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientSioWaitMessage(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientChrPop(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientSStoOAMCall(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientOAMtoSSCall(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientWinLoseMessage(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientEscapeMessage(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientGiveUpMessage(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientMigawariChrSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientWazaKoukaSESet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientBGMPlay(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientWinLoseSet(BATTLE_WORK *bw,CLIENT_PARAM *cp);
static	void	ClientBlankMessage(BATTLE_WORK *bw,CLIENT_PARAM *cp);

//�O������J�֐��Q
static	void	ClientCommandReset(CLIENT_PARAM *cp);

extern	const	u8	BallMoveEffectTable[];

//============================================================================================
/**
 * @param
 */
//============================================================================================
CLIENT_PARAM	*ClientInit(BATTLE_WORK *bw,FIGHT_SYSTEM_BOOT_PARAM *fsbp)
{
	CLIENT_PARAM	*cp;
	int				i;

	cp=sys_AllocMemory(HEAPID_BATTLE,sizeof(CLIENT_PARAM));
	MI_CpuClearFast(cp,sizeof(CLIENT_PARAM));

	cp->client_no=fsbp->client_no;
	cp->client_type=fsbp->client_type;

	//fight_tool.c�Ɉړ�
#if 0
	//HP�Q�[�W����
	cp->gauge.bw = bw;
	cp->gauge.type = Gauge_TypeGet(cp->client_type, BattleWorkFightTypeGet(bw));
	Gauge_ActorResourceSet(&cp->gauge);
	Gauge_EnableSet(&cp->gauge, CATS_ENABLE_FALSE);
#endif
	
	return cp;
}

//============================================================================================
/**
 *	BM_Init���Ăԁi�ŏ���POKEMON_APPEAR���Ƀ��b�N��������Ȃ��悤�Ƀ��\�[�X���ǂ݂��Ă����j
 *
 * @param	bw		�퓬�V�X�e�����[�N�\����
 * @param	cp		�N���C�A���g�V�X�e�����[�N�\����
 * @param	ballID	�Z���Z�b�g����{�[��ID
 * @param	ballID	�Z���Z�b�g����{�[��ID
 */
//============================================================================================
void	ClientBMInit(BATTLE_WORK *bw,CLIENT_PARAM *cp,int ballID,int sel_mons_no)
{
	TBALL_MOVE_DATA bmd;
	s16				x,y;

	//�T�t�@���]�[���A�|�P�p�[�N�ł́A��ǂ݂���K�v�Ȃ�
	if(BattleWorkFightTypeGet(bw)&(FIGHT_TYPE_SAFARI|FIGHT_TYPE_POKE_PARK)){
		return;
	}
	//�g���[�i�[��łȂ���ΓG���̐�ǂ݂���K�v�Ȃ�
	if((cp->client_type&CLIENT_ENEMY_FLAG)&&((BattleWorkFightTypeGet(bw)&FIGHT_TYPE_TRAINER)==0)){
		return;
	}

	bmd.type=BallMoveEffectTable[cp->client_type];
	bmd.heap_id=HEAPID_BATTLE;
	bmd.mode=EBMM_FREE;
	bmd.id=cp->client_no;
	bmd.ball_id=ballID;
	bmd.csp=BattleWorkCATS_SYS_PTRGet(bw);
	bmd.pfd=BattleWorkPfdGet(bw);
	bmd.surface = 0;
	bmd.bg_pri = BM_BG_PRI_BATTLE;

	cp->bms=BM_Init(&bmd);

	BM_BallSoftPriSet(cp->bms,100);
	BM_BallBgPriSet(cp->bms,2);
	BM_BallEnable(cp->bms,CATS_ENABLE_FALSE);
	BM_BallAnimeFlagSet(cp->bms,FALSE);
}

//============================================================================================
/**
 *	�֐��W�����v�e�[�u��
 */
//============================================================================================

static	const	clFunc	ClientFunctionTable[]={
	ClientDummy,
	ClientEncountEffect,
	ClientPokemonEncount,
	ClientPokemonEncountAppear,
	ClientPokemonAppear,
	ClientPokemonReturn,
	ClientPokemonInhale,
	ClientPokemonDelete,
	ClientTrainerEncount,
	ClientTrainerThrow,
	ClientTrainerOut,
	ClientTrainerIn,
	ClientHPGaugeIn,
	ClientHPGaugeOut,
	ClientCommandSelect,
	ClientWazaSelect,
	ClientDirSelect,
	ClientItemSelect,
	ClientPokemonSelect,
	ClientYesNoSelect,
	ClientAttackMessage,
	ClientMessage,
	ClientWazaEffect,
	ClientPokemonBlinkSet,
	ClientHPGaugeCalcSet,
	ClientEXPGaugeCalcSet,
	ClienKizetsuEffectSet,
	ClientSePlaySet,
	ClientFadeOutSet,
	ClientPokemonVanishOnOff,
	ClientHPGaugeStatusSet,
	ClientTrainerMessageSet,
	ClientModosuMessageSet,
	ClientKuridasuMessageSet,
	ClientEncountMessageSet,
	ClientEncountKuridasuMessageSet,
	ClientLevelUpEffectSet,
	ClientAlertMessageSet,
	ClientHPGaugeRefresh,
	ClientPSPtoPPCopy,
	ClientTrainerBGSlideIn,
	ClientGaugeAnimeStop,
	ClientPokemonRefresh,
	ClientWazaWasure,
	ClientMosaicSet,
	ClientFormChgSet,
	ClientBGChgSet,
	ClientSubBGWallPut,
	ClientBallGaugeEncountSet,
	ClientBallGaugeEncountOut,
	ClientBallGaugeSet,
	ClientBallGaugeOut,
	ClientBallGaugeResourceLoad,
	ClientBallGaugeResourceDelete,
	ClientIncRecord,
	ClientSioWaitMessage,
	ClientChrPop,
	ClientSStoOAMCall,
	ClientOAMtoSSCall,
	ClientWinLoseMessage,
	ClientEscapeMessage,
	ClientGiveUpMessage,
	ClientMigawariChrSet,
	ClientWazaKoukaSESet,
	ClientBGMPlay,
	ClientWinLoseSet,
	ClientBlankMessage,
};

//============================================================================================
/**
 * @param
 */
//============================================================================================
void	ClientMain(BATTLE_WORK *battle_work,CLIENT_PARAM *client_param)
{
	if(client_param->client_buffer[0]){
		ClientFunctionTable[client_param->client_buffer[0]](battle_work,client_param);
	}
}

//============================================================================================
/**
 * @param
 */
//============================================================================================
void	ClientEnd(BATTLE_WORK *bw,CLIENT_PARAM *cp,int mode)
{
	//���O���͂�������́AGauge_ActorResourceDel���ĂԕK�v�͂Ȃ�
	if(mode!=BW_PROC_MODE_NAMEIN_AFTER){
		Gauge_ActorResourceDel(&cp->gauge);	//�Q�[�W�폜
	}
	
	Poke_SinCurveStop(cp);

	sys_FreeMemoryEz(cp);
}

//============================================================================================
/**
 *	�_�~�[�֐��i�֐��e�[�u���i���o�[�́A1�I���W���Ȃ̂ŁA�_�~�[�֐���p�Ӂj
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientDummy(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
}

//============================================================================================
/**
 *	�G���J�E���g�G�t�F�N�g���Z�b�g
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientEncountEffect(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	CT_EncountEffectSet(bw,cp);
	//�G���J�E���g�G�t�F�N�g�͏I���҂��̕K�v�Ȃ��i�̂͂��j
	SCIO_ServerQueClear(bw,cp->client_no,CL_ENCOUNT_EFFECT);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	�G���J�E���g�p�̃|�P�������Z�b�g
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientPokemonEncount(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	POKEMON_ENCOUNT_PARAM	*pep=(POKEMON_ENCOUNT_PARAM *)&cp->client_buffer[0];

	CT_PokemonEncountSet(bw,cp,pep);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	�|�P�����o���G�t�F�N�g���Z�b�g
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientPokemonEncountAppear(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	POKEMON_APPEAR_PARAM	*pap=(POKEMON_APPEAR_PARAM *)&cp->client_buffer[0];

	CT_PokemonEncountAppearSet(bw,cp,pap);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	�|�P�����o���G�t�F�N�g���Z�b�g
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientPokemonAppear(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	POKEMON_APPEAR_PARAM	*pap=(POKEMON_APPEAR_PARAM *)&cp->client_buffer[0];

	CT_PokemonAppearSet(bw,cp,pap);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	�|�P�����������߂�G�t�F�N�g���Z�b�g
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientPokemonReturn(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	POKEMON_RETURN_PARAM	*prp=(POKEMON_RETURN_PARAM *)&cp->client_buffer[0];

	CT_PokemonReturnSet(bw,cp,prp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	�|�P�����z�����ރG�t�F�N�g���Z�b�g
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientPokemonInhale(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	POKEMON_INHALE_PARAM	*pip=(POKEMON_INHALE_PARAM *)&cp->client_buffer[0];

	CT_PokemonInhaleSet(bw,cp,pip);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	�|�P�������폜
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientPokemonDelete(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	SoftSpriteDel(cp->poke_ss);
	SCIO_ServerQueClear(bw,cp->client_no,CL_POKEMON_DELETE);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	�G���J�E���g�p�̃g���[�i�[���Z�b�g
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientTrainerEncount(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	TRAINER_ENCOUNT_PARAM	*tep=(TRAINER_ENCOUNT_PARAM *)&cp->client_buffer[0];

	CT_TrainerEncountSet(bw,cp,tep);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	�g���[�i�[������G�t�F�N�g�̃Z�b�g
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientTrainerThrow(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	TRAINER_THROW_PARAM	*ttp=(TRAINER_THROW_PARAM *)&cp->client_buffer[0];

	CT_TrainerThrowSet(bw,cp,ttp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	�g���[�i�[��ʊO�G�t�F�N�g���Z�b�g
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientTrainerOut(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	CT_TrainerOutSet(bw,cp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	�g���[�i�[��ʓ��G�t�F�N�g���Z�b�g
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientTrainerIn(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	TRAINER_IN_PARAM	*tip=(TRAINER_IN_PARAM *)&cp->client_buffer[0];

	CT_TrainerInSet(bw,cp,tip);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	HP�Q�[�W���IN�G�t�F�N�g���Z�b�g
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientHPGaugeIn(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	HP_GAUGE_IN_PARAM	*hgip=(HP_GAUGE_IN_PARAM *)&cp->client_buffer[0];

	CT_HPGaugeInSet(bw,cp,hgip);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	HP�Q�[�W���OUT�G�t�F�N�g���Z�b�g
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientHPGaugeOut(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	CT_HPGaugeOutSet(bw,cp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	�R�}���h�I�����N��
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientCommandSelect(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	COMMAND_SELECT_PARAM	*csp=(COMMAND_SELECT_PARAM *)&cp->client_buffer[0];

	//����ւ��ł��Ȃ�ClientNo��bw�̃����o�ɃZ�b�g�i�ʐM�p�j
	BattleWorkNoReshuffleClientSet(bw,csp->no_reshuffle_client);

	CT_CommandSelectSet(bw,cp,csp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	�Z�I�����N��
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientWazaSelect(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	WAZA_SELECT_PARAM	*wsp=(WAZA_SELECT_PARAM *)&cp->client_buffer[0];

	CT_WazaSelectSet(bw,cp,wsp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	�U���ΏۑI�����N��
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientDirSelect(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	DIR_SELECT_PARAM	*dsp=(DIR_SELECT_PARAM *)&cp->client_buffer[0];

	CT_DirSelectSet(bw,cp,dsp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	����I�����N��
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientItemSelect(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	ITEM_SELECT_PARAM	*isp=(ITEM_SELECT_PARAM *)&cp->client_buffer[0];

	CT_ItemSelectSet(bw,cp,isp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	�|�P�����I�����N��
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientPokemonSelect(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	POKEMON_SELECT_PARAM	*psp=(POKEMON_SELECT_PARAM *)&cp->client_buffer[0];

	CT_PokemonSelectSet(bw,cp,psp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	Yes/No�I�����N��
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientYesNoSelect(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	YES_NO_SELECT_PARAM	*ynsp=(YES_NO_SELECT_PARAM *)&cp->client_buffer[0];

	CT_YesNoSelectSet(bw,cp,ynsp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	�A�^�b�N���b�Z�[�W��\��
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientAttackMessage(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	ATTACK_MESSAGE_PARAM	*amp=(ATTACK_MESSAGE_PARAM *)&cp->client_buffer[0];

	CT_AttackMessageSet(bw,cp,amp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	���b�Z�[�W��\��
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientMessage(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	MESSAGE_PARAM	*mp=(MESSAGE_PARAM *)&cp->client_buffer[0];

	CT_MessageSet(bw,cp,mp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	�Z�G�t�F�N�g���N��
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientWazaEffect(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	WAZA_EFFECT_PARAM	*wep=(WAZA_EFFECT_PARAM *)&cp->client_buffer[0];

	CT_WazaEffectSet(bw,cp,wep);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	�|�P�����_���[�W�u�����N�A�N�V�������Z�b�g
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientPokemonBlinkSet(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	//�o�j�b�V����Ԃ̎��̓u�����N���Ȃ�
	if(SoftSpriteParaGet(cp->poke_ss,SS_PARA_VANISH)==SW_VANISH_ON){
		SCIO_ServerQueClear(bw,cp->client_no,CL_POKEMON_BLINK);
	}
	else{
		CT_PokemonBlinkSet(bw,cp);
	}
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	HP�Q�[�W�v�Z���Z�b�g
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientHPGaugeCalcSet(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	HP_GAUGE_CALC_PARAM	*hgcp=(HP_GAUGE_CALC_PARAM *)&cp->client_buffer[0];

	CT_HPGaugeCalcSet(bw,cp,hgcp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	EXP�Q�[�W�v�Z���Z�b�g
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientEXPGaugeCalcSet(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	EXP_GAUGE_CALC_PARAM	*egcp=(EXP_GAUGE_CALC_PARAM *)&cp->client_buffer[0];

	CT_EXPGaugeCalcSet(bw,cp,egcp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	�C��G�t�F�N�g���Z�b�g
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClienKizetsuEffectSet(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	KIZETSU_EFFECT_PARAM	*kep=(KIZETSU_EFFECT_PARAM *)&cp->client_buffer[0];

	CT_KizetsuEffectSet(bw,cp,kep);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	�w�肳�ꂽSE��炷
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientSePlaySet(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	SE_PLAY_PARAM	*spp=(SE_PLAY_PARAM *)&cp->client_buffer[0];

	CT_SePlaySet(bw,cp,spp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	��ʃt�F�[�h�A�E�g���Z�b�g
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientFadeOutSet(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	CT_FadeOutSet(bw,cp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	�|�P�����o�j�b�V���t���O��ON/OFF
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientPokemonVanishOnOff(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	POKEMON_VANISH_ON_OFF	*pvoo=(POKEMON_VANISH_ON_OFF *)&cp->client_buffer[0];

	CT_PokemonVanishOnOff(bw,cp,pvoo);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	HP�Q�[�W�̏�Ԉُ�A�C�R���̕\��
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientHPGaugeStatusSet(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	HP_GAUGE_STATUS_SET_PARAM	*hgssp=(HP_GAUGE_STATUS_SET_PARAM *)&cp->client_buffer[0];

	CT_HPGaugeStatusSet(bw,cp,hgssp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	�g���[�i�[���b�Z�[�W�̕\��
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientTrainerMessageSet(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	TRAINER_MESSAGE_PARAM	*tmp=(TRAINER_MESSAGE_PARAM *)&cp->client_buffer[0];

	CT_TrainerMessageSet(bw,cp,tmp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	�߂����b�Z�[�W��\��
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientModosuMessageSet(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	MODOSU_MESSAGE_PARAM	*mmp=(MODOSU_MESSAGE_PARAM *)&cp->client_buffer[0];

	CT_ModosuMessageSet(bw,cp,mmp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	�J��o�����b�Z�[�W��\��
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientKuridasuMessageSet(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	KURIDASU_MESSAGE_PARAM	*kmp=(KURIDASU_MESSAGE_PARAM *)&cp->client_buffer[0];

	CT_KuridasuMessageSet(bw,cp,kmp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	�G���J�E���g���b�Z�[�W��\��
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientEncountMessageSet(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	CT_EncountMessageSet(bw,cp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	�G���J�E���g���̌J��o�����b�Z�[�W��\��
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientEncountKuridasuMessageSet(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	ENCOUNT_KURIDASU_MESSAGE_PARAM	*ekmp=(ENCOUNT_KURIDASU_MESSAGE_PARAM *)&cp->client_buffer[0];

	CT_EncountKuridasuMessageSet(bw,cp,ekmp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	���x���A�b�v�G�t�F�N�g��\��
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientLevelUpEffectSet(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	CT_LevelUpEffectSet(bw,cp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	�A���[�g���b�Z�[�W��\��
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientAlertMessageSet(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	ALERT_MESSAGE_PARAM	*amp=(ALERT_MESSAGE_PARAM *)&cp->client_buffer[0];

	CT_AlertMessageSet(bw,cp,amp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	HP�Q�[�W���ĕ`��
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientHPGaugeRefresh(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	HP_GAUGE_REFRESH_PARAM	*hgrp=(HP_GAUGE_REFRESH_PARAM *)&cp->client_buffer[0];

	CT_HPGaugeRefreshSet(bw,cp,hgrp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	PSP����K�v�ȃf�[�^��PP�ɏ����߂�
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientPSPtoPPCopy(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	PSP_TO_PP_COPY_PARAM	*ptpcp=(PSP_TO_PP_COPY_PARAM *)&cp->client_buffer[0];
	int						i;
	POKEMON_PARAM			*pp;

	pp=BattleWorkPokemonParamGet(bw,cp->client_no,ptpcp->sel_mons_no);

	//�ւ񂵂񒆂́AHP��condition�̂ݏ����߂�
	if((ptpcp->condition2&CONDITION2_HENSHIN)==0){
		for(i=0;i<WAZA_TEMOTI_MAX;i++){
			if((ptpcp->monomane_bit&No2Bit(i))==0){
				PokeParaPut(pp,ID_PARA_waza1+i,		(u8 *)&ptpcp->waza[i]);
				PokeParaPut(pp,ID_PARA_pp1+i,		(u8 *)&ptpcp->pp[i]);
			}
		}
		if((ptpcp->hatakiotosu&No2Bit(ptpcp->sel_mons_no))==0){
			PokeParaPut(pp,ID_PARA_item,	(u8 *)&ptpcp->item);
		}
	}

	PokeParaPut(pp,ID_PARA_hp,			(u8 *)&ptpcp->hp);
	PokeParaPut(pp,ID_PARA_condition,	(u8 *)&ptpcp->condition);

	SCIO_ServerQueClear(bw,cp->client_no,ptpcp->command_code);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	�^�b�`�p�l���Ƀg���[�i�[BG��SlideIn
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientTrainerBGSlideIn(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	u32				fight_type;
	BI_PARAM_PTR	bip;

	fight_type=BattleWorkFightTypeGet(bw);
	bip = BattleWorkGF_BGL_BIPGet(bw);

	if(cp->client_boot==CLIENT_BOOT_NORMAL){
		if((fight_type&FIGHT_TYPE_MULTI)||
		  (((fight_type&FIGHT_TYPE_MULTI)==0)&&(cp->client_type!=CLIENT_TYPE_C))){
			BINPUT_PlayerBG_ScrollX(bip, BIN_PLAYER_SCROLL_SP_X, 0);
		}
	}

	SCIO_ServerQueClear(bw,cp->client_no,cp->client_buffer[0]);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	�Q�[�W�̃A�j���[�V�������X�g�b�v
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientGaugeAnimeStop(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	Gauge_AnimeStop(&cp->gauge);
	Poke_SinCurveStop(cp);
	SCIO_ServerQueClear(bw,cp->client_no,cp->client_buffer[0]);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	�|�P�����̏�Ԉُ�𒼂�
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientPokemonRefresh(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	POKEMON_REFRESH_PARAM	*prp=(POKEMON_REFRESH_PARAM *)&cp->client_buffer[0];
	POKEMON_PARAM			*pp;
	int						i,poke_count,speabi;
	u32						condition;

	condition=0;

	poke_count=BattleWorkPokeCountGet(bw,cp->client_no);

	for(i=0;i<poke_count;i++){
		pp=BattleWorkPokemonParamGet(bw,cp->client_no,i);
		if(prp->speabi==TOKUSYU_KATAYABURI){
			speabi=0;
		}
		else{
			speabi=PokeParaGet(pp,ID_PARA_speabino,NULL);
		}
		if((prp->waza_no!=WAZANO_IYASINOSUZU)||
		   ((prp->waza_no==WAZANO_IYASINOSUZU)&&(speabi!=TOKUSYU_BOUON))){
			PokeParaPut(pp,ID_PARA_condition,(u8 *)&condition);
		}
	}

	SCIO_ServerQueClear(bw,cp->client_no,prp->command_code);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	�Z�Y�ꏈ�����Ăяo��
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientWazaWasure(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	WAZA_WASURE_PARAM	*wwp=(WAZA_WASURE_PARAM *)&cp->client_buffer[0];

	CT_WazaWasureSet(bw,cp,wwp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	�\�t�g�E�G�A�X�v���C�g�Ƀ��U�C�N��������
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientMosaicSet(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	MOSAIC_SET_PARAM	*msp=(MOSAIC_SET_PARAM *)&cp->client_buffer[0];

	CT_MosaicSet(bw,cp,msp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	�t�H�����i���o�[��ς���
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientFormChgSet(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	FORM_CHG_PARAM	*fcp=(FORM_CHG_PARAM *)&cp->client_buffer[0];
	SOFT_SPRITE_ARC	ssa_src;
	SOFT_SPRITE_ARC	*ssa;
	int				pos_y;
	int				dir;

	if(cp->client_type&CLIENT_ENEMY_FLAG){
		dir=PARA_FRONT;
	}
	else{
		dir=PARA_BACK;
	}

	PokeGraArcDataGet(&ssa_src,fcp->mons_no,fcp->sex,dir,fcp->rare,fcp->form_no,fcp->personal_rnd);
	ssa=SoftSpriteArcPointerGetSS(cp->poke_ss);
	*ssa=ssa_src;
	SoftSpriteRecoverSS(cp->poke_ss);

	Ex_ChangesInto_BattlePokeData(ssa->arc_no,ssa->index_chr,HEAPID_BATTLE,
								  ExChrParamExChrBufferGet(BattleWorkExChrParamGet(bw),cp->client_no), fcp->personal_rnd, FALSE, dir, ssa->strike_mons);
	ExChrParamArcIDSet(BattleWorkExChrParamGet(bw),cp->client_no,ssa->arc_no);
	ExChrParamPalIndexSet(BattleWorkExChrParamGet(bw),cp->client_no,ssa->index_pal);

	pos_y=PokeHeightGet(fcp->mons_no,fcp->sex,dir,fcp->form_no,fcp->personal_rnd);
	ExChrParamHeightSet(BattleWorkExChrParamGet(bw),cp->client_no,pos_y);

	pos_y=CT_PokemonAppearPosGet(cp->client_type,POS_ID_Y)+pos_y;
	SoftSpriteParaSet(cp->poke_ss,SS_PARA_POS_Y,pos_y);

	SCIO_ServerQueClear(bw,cp->client_no,fcp->command_code);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	�n�`OBJ��BG�ɕς���
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientBGChgSet(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	BattleWorkGroundBGChg(bw);
	SCIO_ServerQueClear(bw,cp->client_no,CL_BG_CHG);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	�T�u��ʂ̔w�i�ǎ���\��
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientSubBGWallPut(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	if(cp->client_boot==CLIENT_BOOT_NORMAL){
		{
			BI_PARAM_PTR	bip;
			int				partner_client;
			GAUGE_WORK		*partner_gauge;

			bip = BattleWorkGF_BGL_BIPGet(bw);

			BINPUT_CreateBG(bip, BINPUT_TYPE_WALL, FALSE, NULL);
			BINPUT_BackFadeReq(bip, BINPUT_BACKFADE_LIGHT);

			partner_client = BattleWorkPartnerClientNoGet(bw, cp->client_no);
			if(partner_client != cp->client_no){
				partner_gauge = BattleWorkGaugeWorkGet(bw, partner_client);
				Gauge_ColorNormalSet(partner_gauge);
			}
			Gauge_AnimeStop(&cp->gauge);
			BINPUT_StockBallOFF(bip);
			Poke_SinCurveStop(cp);
		}
	}
	SCIO_ServerQueClear(bw,cp->client_no,CL_SUBBG_WALL_PUT);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	�{�[���Q�[�W��\���i�G���J�E���g���j
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientBallGaugeEncountSet(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	BALL_GAUGE_PARAM	*bgp=(BALL_GAUGE_PARAM *)&cp->client_buffer[0];

	CT_BallGaugeEncountSet(bw,cp,bgp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	�{�[���Q�[�W�������i�G���J�E���g���j
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientBallGaugeEncountOut(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	BALL_GAUGE_PARAM	*bgp=(BALL_GAUGE_PARAM *)&cp->client_buffer[0];

	CT_BallGaugeEncountOut(bw,cp,bgp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	�{�[���Q�[�W��\��
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientBallGaugeSet(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	BALL_GAUGE_PARAM	*bgp=(BALL_GAUGE_PARAM *)&cp->client_buffer[0];

	//�G���J�E���g����Ȃ��{�[���Q�[�W�\���͓G���̂�
	if(BattleWorkMineEnemyCheck(bw,cp->client_no)){
		CT_BallGaugeSet(bw,cp,bgp);
	}
	else{
		SCIO_ServerQueClear(bw,cp->client_no,CL_BALL_GAUGE_SET);
	}
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	�{�[���Q�[�W������
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientBallGaugeOut(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	BALL_GAUGE_PARAM	*bgp=(BALL_GAUGE_PARAM *)&cp->client_buffer[0];

	//�G���J�E���g����Ȃ��{�[���Q�[�W�����͓G���̂�
	if(BattleWorkMineEnemyCheck(bw,cp->client_no)){
		CT_BallGaugeOut(bw,cp,bgp);
	}
	else{
		SCIO_ServerQueClear(bw,cp->client_no,CL_BALL_GAUGE_OUT);
	}
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	�{�[���Q�[�W�̃��\�[�X�����[�h
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientBallGaugeResourceLoad(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	CATS_SYS_PTR				csp;
	CATS_RES_PTR				crp;
	PALETTE_FADE_PTR			pfd;

	csp=BattleWorkCATS_SYS_PTRGet(bw);
	crp=BattleWorkCATS_RES_PTRGet(bw);
	pfd=BattleWorkPfdGet(bw);

	//���\�[�X���[�h�̊֐����Ăяo��
	TEMOTI_ResourceLoad(csp, crp, pfd);
	
	SCIO_ServerQueClear(bw,cp->client_no,CL_BALL_GAUGE_RESOURCE_LOAD);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	�{�[���Q�[�W�̃��\�[�X������
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientBallGaugeResourceDelete(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	CATS_RES_PTR				crp;

	crp=BattleWorkCATS_RES_PTRGet(bw);

	//���\�[�X�����̊֐����Ăяo��
	TEMOTI_ResourceFree(crp);
	
	SCIO_ServerQueClear(bw,cp->client_no,CL_BALL_GAUGE_RESOURCE_DELETE);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	�J�E���g�A�b�v���[�N�̃C���N�������g
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientIncRecord(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	INC_RECORD_PARAM	*irp=(INC_RECORD_PARAM *)&cp->client_buffer[0];

	if(irp->flag==CLIENT_BOOT_TYPE_MINE){
		//��������̃N���C�A���g�̂݃J�E���g�A�b�v
		if(cp->client_boot==CLIENT_BOOT_NORMAL){
			BattleWorkIncRecord(bw,irp->id);
		}
	}
	else{
		//��������̃N���C�A���g�ł͂Ȃ����ɃJ�E���g�A�b�v
		if(cp->client_boot!=CLIENT_BOOT_NORMAL){
			BattleWorkIncRecord(bw,irp->id);
		}
	}

	SCIO_ServerQueClear(bw,cp->client_no,irp->command_code);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	�ʐM�ҋ@���b�Z�[�W�̕\��
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientSioWaitMessage(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	CT_SioWaitMessage(bw,cp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	�ޔ����Ă����L�����̕��A
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientChrPop(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	WAZA_EFFECT_PARAM	*wep=(WAZA_EFFECT_PARAM *)&cp->client_buffer[0];

	CT_ChrPop(bw,cp,wep);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	�\�t�g�X�v���C�g��OAM�ɕϊ�
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientSStoOAMCall(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	CT_SStoOAM(bw, cp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	OAM���\�t�g�X�v���C�g�ɖ߂�
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientOAMtoSSCall(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	CT_OAMtoSS(bw, cp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	�ʐM�ΐ펞�̏��s���b�Z�[�W��\��
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientWinLoseMessage(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	CT_WinLoseMessageSet(bw,cp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	�ʐM�ΐ펞�̂ɂ��郁�b�Z�[�W��\��
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientEscapeMessage(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	ESCAPE_MESSAGE_PARAM	*emp=(ESCAPE_MESSAGE_PARAM *)&cp->client_buffer[0];

	CT_EscapeMessageSet(bw,cp,emp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	�o�g���^���[�̃��^�C�A���b�Z�[�W��\��
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientGiveUpMessage(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	CT_GiveUpMessageSet(bw,cp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	�݂����L�������Z�b�g
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientMigawariChrSet(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	WAZA_EFFECT_PARAM	*wep=(WAZA_EFFECT_PARAM *)&cp->client_buffer[0];

	CT_MigawariChrSet(bw,cp,wep);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	�Z����SE�̃Z�b�g
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientWazaKoukaSESet(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	WAZAKOUKA_SE_PARAM	*wsp=(WAZAKOUKA_SE_PARAM *)&cp->client_buffer[0];

	CT_WazaKoukaSESet(bw,cp,wsp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	�Ȃ̃Z�b�g
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientBGMPlay(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	BGM_PLAY_PARAM	*bpp=(BGM_PLAY_PARAM *)&cp->client_buffer[0];

	CT_BGMPlay(bw,cp,bpp);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	win_lose_flag���Z�b�g
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientWinLoseSet(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	WIN_LOSE_SET_PARAM	*wlsp=(WIN_LOSE_SET_PARAM *)&cp->client_buffer[0];
	POKEPARTY			*poke_party;
	POKEMON_PARAM		*pp;
	int	i;
	int	client_no;
	int	mine_hp=0;
	int	enemy_hp=0;
	u8	sio_id;

	//�o�g���^���[�́A�����Ă���win_lose_flag�����̂܂܃Z�b�g
	if(BattleWorkFightTypeGet(bw)&FIGHT_TYPE_TOWER){
		BattleWorkWinLoseSet(bw,wlsp->win_lose_flag);
	}
	else{
		for(client_no=0;client_no<BattleWorkClientSetMaxGet(bw);client_no++){
			poke_party=BattleWorkPokePartyGet(bw,client_no);
			for(i=0;i<PokeParty_GetPokeCount(poke_party);i++){
				pp=PokeParty_GetMemberPointer(poke_party,i);
				if((PokeParaGet(pp,ID_PARA_monsno,NULL))&&
				   (PokeParaGet(pp,ID_PARA_tamago_flag,NULL)==0)){
					if(BattleWorkMineEnemyCheck(bw,client_no)){
						enemy_hp+=PokeParaGet(pp,ID_PARA_hp,NULL);
					}
					else{
						mine_hp+=PokeParaGet(pp,ID_PARA_hp,NULL);
					}
				}
			}
		}
		if((mine_hp==0)&&(enemy_hp==0)){
			BattleWorkWinLoseSet(bw,FIGHT_DRAW);
		}
		else if(mine_hp==0){
			BattleWorkWinLoseSet(bw,FIGHT_LOSE);
		}
		else{
			BattleWorkWinLoseSet(bw,FIGHT_WIN);
		}
	}

	SCIO_ServerQueClear(bw,cp->client_no,wlsp->command_code);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	���b�Z�[�W�E�C���h�E���N���A
 *
 * @param[in]	bw		�퓬�V�X�e�����[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientBlankMessage(BATTLE_WORK *bw,CLIENT_PARAM *cp)
{
	GF_BGL_BMPWIN	*win=BattleWorkGF_BGL_BMPWINGet(bw,TALK_WIN_NO);

	GF_BGL_BmpWinDataFill(win,0xff);
	GF_BGL_BmpWinCgxOn(win);

	SCIO_ServerQueClear(bw,cp->client_no,CL_BLANK_MESSAGE);
	ClientCommandReset(cp);
}

//============================================================================================
/**
 *	�R�}���h�������Z�b�g
 *
 * @param[in]	cp		�N���C�A���g�p���[�N�̃|�C���^
 */
//============================================================================================
static	void	ClientCommandReset(CLIENT_PARAM *cp)
{
	cp->client_buffer[0]=0;
}

