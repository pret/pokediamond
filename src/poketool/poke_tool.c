
//============================================================================================
/**
 * @file	poke_tool.c
 * @bfief	�|�P�����p�����[�^�c�[���Q
 * @author	HisashiSogabe
 * @date	05.05.30
 */
//============================================================================================

#include	"common.h"
#include    "gflib/strbuf_family.h"
#include	"battle/battle_common.h"
#include	"battle/battle_server.h"
#include	"battle/fight_tool.h"
#include	"battle/tokusyu_def.h"
#include	"battle/trtype_def.h"
#include	"poketool/poke_memo.h"
#include	"poketool/poke_tool.h"
#include	"poketool/pokeparty.h"
#include	"poketool/tr_tool.h"
#include	"poketool/waza_tool.h"
#include	"poke_tool_def.h"
#include	"system/arc_tool.h"
#include	"system/buflen.h"
#include	"system/gamedata.h"
#include	"system/msgdata.h"
#include	"system/msgdata_util.h"
#include	"system/pm_rtc.h"
#include	"system/softsprite.h"
#include	"system/snd_play.h"
#include	"system/snd_perap.h"
#include	"poketool/monsno.h"
#include	"pokeanime/p_anm_sys.h"

#include	"savedata/mystatus.h"

#include	"itemtool/item.h"
#include	"itemtool/itemequip.h"
#include	"itemtool/itemsym.h"

#include	"cubelike.dat"

//�X�V����������AMAKE��������悤�ɂ��邽�߂�INCLUDE
#include	"pokezukan.naix"
#include	"pokegra/pokegra.naix"
#include	"pokegra/otherpoke.naix"
#include	"pokegra/height_o.naix"
#include	"pokeanm/pokeanm.naix"
#include	"trgra/trbgra.naix"
#include	"trgra/trfgra.naix"

//============================================================================================
/**
 * �萔�錾
 */
//============================================================================================

#define	POKE_GRA_SIZE	(6)		///<�|�P�����P�̂ɂ��A���݂���O���t�B�b�N�t�@�C���̐�
#define	POKE_COL_OFS	(4)		///<�O���t�B�b�N�A�[�J�C�u�t�@�C�����̃p���b�g�f�[�^�܂ł̃I�t�Z�b�g

#define	TR_GRA_SIZE		(2)		///<�g���[�i�[�P�̂ɂ��A���݂���O���t�B�b�N�t�@�C���̐�
#define	TR_COL_OFS		(1)		///<�g���[�i�[�P�̂ɂ��A���݂���O���t�B�b�N�t�@�C���̐�

#define	POKE_HEIGHT_SIZE	(4)	///<�|�P�����P�̂ɂ��A���݂��鍂�����t�@�C���̐�

#define	DEOKISISU_OTHER_FORM_PERSONAL	(496-1)	//�f�I�L�V�X�̕ʃt�H�����p�[�\�i���̊J�n�i���o�[
#define	MINOMESU_OTHER_FORM_PERSONAL	(499-1)	//�~�m���X�̕ʃt�H�����p�[�\�i���̊J�n�i���o�[

//============================================================================================
/**
 * �v���g�^�C�v�錾
 */
//============================================================================================

void	PokeParaInit(POKEMON_PARAM *pp);
void	PokePasoParaInit(POKEMON_PASO_PARAM *ppp);

int		PokemonParam_GetWorkSize(void);
POKEMON_PARAM	*PokemonParam_AllocWork(u32 heapID);

BOOL	PokeParaFastModeOn(POKEMON_PARAM *pp);
BOOL	PokeParaFastModeOff(POKEMON_PARAM *pp,BOOL flag);
BOOL	PokePasoParaFastModeOn(POKEMON_PASO_PARAM *ppp);
BOOL	PokePasoParaFastModeOff(POKEMON_PASO_PARAM *ppp,BOOL flag);

void	PokeParaSet(POKEMON_PARAM *pp,int mons_no,int level,int pow,int rndflag,u32 rnd,int idflag,u32 id);
void	PokePasoParaSet(POKEMON_PASO_PARAM *ppp,int mons_no,int level,int pow,int rndflag,u32 rnd,int idflag,u32 id);
void	PokeParaSetChr(POKEMON_PARAM *,u16,u8,u8,u8);
void	PokeParaSetSexChr(POKEMON_PARAM *,u16,u8,u8,u8,u8,u8);
u32		PokeParaSexChrRndGet(u16 mons_no,u8 sex,u8 chr);
void	PokeParaSetPowRnd(POKEMON_PARAM *,u16,u8,u32,u32);
void	PokeParaSetPowRndBuf(POKEMON_PARAM *,u16,u8,u8*,u32);
void	PokeParaSetParaExp(POKEMON_PARAM *,u16,u8,u8,u8);
void	PokeParaSetBattleFrontier(POKEMON_PARAM *pp,u16 pokeno,u8 pokelevel,u8 chr,u8 pow,u8 expbit,u32 id);
void	PokeParaCalc(POKEMON_PARAM *pp);
void	PokeParaCalcLevelUp(POKEMON_PARAM *pp);

u32		PokeParaGet(POKEMON_PARAM *pp,int id,void *buf);
//u32		PokeParaGetFast(POKEMON_PARAM *pp,int id,void *buf);
static	u32		PokeParaGetAct(POKEMON_PARAM *pp,int id,void *buf);
u32		PokePasoParaGet(POKEMON_PASO_PARAM *ppp,int id,void *buf);
//u32		PokePasoParaGetFast(POKEMON_PASO_PARAM *ppp,int id,void *buf);
static	u32		PokePasoParaGetAct(POKEMON_PASO_PARAM *ppp,int id,void *buf);
void	PokeParaPut(POKEMON_PARAM *pp,int id,const void *buf);
//void	PokeParaPutFast(POKEMON_PARAM *pp,int id,const void *buf);
static	void	PokeParaPutAct(POKEMON_PARAM *pp,int id,const void *buf);
void	PokePasoParaPut(POKEMON_PASO_PARAM *ppp,int id,const void *buf);
//void	PokePasoParaPutFast(POKEMON_PASO_PARAM *ppp,int id,const void *buf);
static	void	PokePasoParaPutAct(POKEMON_PASO_PARAM *ppp,int id,const void *buf);
void	PokeParaAdd(POKEMON_PARAM *pp,int id,int value);
//void	PokeParaAddFast(POKEMON_PARAM *pp,int id,int value);
static	void	PokeParaAddAct(POKEMON_PARAM *pp,int id,int value);
void	PokePasoParaAdd(POKEMON_PASO_PARAM *ppp,int id,int value);
//void	PokePasoParaAddFast(POKEMON_PASO_PARAM *ppp,int id,int value);
static	void	PokePasoParaAddAct(POKEMON_PASO_PARAM *ppp,int id,int value);

u32		PokeParaPersonalParaGet(POKEMON_PARAM *pp,int para);
u32		PokePasoParaPersonalParaGet(POKEMON_PASO_PARAM *ppp,int para);
u32		PokeFormNoPersonalParaGet(int mons_no,int form_no,int para);

u32		PokePersonalParaGet(int mons_no,int para);

u8		PokeParaNextLevelExpRatioGet(POKEMON_PARAM *pp);

u32		PokeParaNextLevelExpGet(POKEMON_PARAM *pp);
u32		PokePasoParaNextLevelExpGet(POKEMON_PASO_PARAM *ppp);

u32		PokeParaLevelExpGet(POKEMON_PARAM *pp);
u32		PokeLevelExpGet(int	mons_no,int level);
void	PokeGrowDataGet(int para,u32 *grow_tbl);
u32		PokeGrowParaGet(int para,int level);

u32		PokeParaLevelCalc(POKEMON_PARAM *pp);
u32		PokePasoLevelCalc(POKEMON_PASO_PARAM *ppp);
u32		PokeLevelCalc(u16 mons_no,u32 exp);

u8		PokeSeikakuGet(POKEMON_PARAM *pp);
u8		PokePasoSeikakuGet(POKEMON_PASO_PARAM *ppp);
u8		PokeSeikakuGetRnd(u32 rnd);

u16		PokeChrAbiCalc(u8 chr,u16 para,u8 cond);
s8		PokeChrAbiTableGet(u8 chr,u8 cond);

void	FriendCalc(POKEMON_PARAM *pp,u8 id,u16 placeID);

u8		PokeSexGet(POKEMON_PARAM *pp);
u8		PokePasoSexGet(POKEMON_PASO_PARAM *ppp);
u8		PokeSexGetMonsNo(u16 monsno,u32 rnd);
u8		PokeRareGet(POKEMON_PARAM *pp);
u8		PokePasoRareGet(POKEMON_PASO_PARAM *ppp);
u8		PokeRareGetPara(u32 id,u32 rnd);
u32		PokeRareRndGet(u32 id);

void	PokeGraArcDataGetPP(SOFT_SPRITE_ARC *ssa,POKEMON_PARAM *pp,u8 dir);
void	PokeGraArcDataGetPPP(SOFT_SPRITE_ARC *ssa,POKEMON_PASO_PARAM *ppp,u8 dir);
void	PokeGraArcDataGet(SOFT_SPRITE_ARC *ssa,u16 mons_no,u8 sex,u8 dir,u8 col,u8 form_no,u32 rnd);
u8		PokeParaHeightGet(POKEMON_PARAM *pp,u8 dir);
u8		PokePasoParaHeightGet(POKEMON_PASO_PARAM *ppp,u8 dir);
u8		PokeHeightGet(u16 mons_no,u8 sex,u8 dir,u8 form_no,u32 rnd);
void	TrGraArcDataGet(SOFT_SPRITE_ARC *ssa,u16 trtype,u8 dir,u8 sex);
void	TrTypeGraArcDataGet(SOFT_SPRITE_ARC *ssa,u16 trtype);

void	PokeAnmDataSet(SOFT_SPRITE_ANIME *ssanm,u16 mons_no);
void	PokePrgAnmDataSet(POKE_ANM_SYS_PTR pasp,SOFT_SPRITE *ss,u16 mons_no,int dir,int chr,int reverse,int index);

u32		PokemonParamSizeGet(void);
u32		PokemonPasoParamSizeGet(void);

u8		PokeParaUnknownFormGet(POKEMON_PARAM *pp);
u8		PokePasoParaUnknownFormGet(POKEMON_PASO_PARAM *ppp);
//u8		PokemonUnknownFormGet(u32 rnd);

//u32		PokemonPasoUnknownFormRndGet(int form);

POKEMON_PASO_PARAM	*PPPPointerGet(POKEMON_PARAM *pp);

u8		PokeLevelUpCheck(POKEMON_PARAM *pp);
u16		PokeShinkaCheck(POKEPARTY *ppt,POKEMON_PARAM *pp,u8 type,u16 itemno,int *shinka_cond);

void	PokeWazaOboe(POKEMON_PARAM *pp);
void	PokePasoWazaOboe(POKEMON_PASO_PARAM *ppp);
u16		PokeWazaSet(POKEMON_PARAM *pp,u16 wazano);
u16		PokePasoWazaSet(POKEMON_PASO_PARAM *ppp,u16 wazano);
void	PokeWazaOboeOshidashi(POKEMON_PARAM *pp,u16 wazano);
void	PokePasoWazaOboeOshidashi(POKEMON_PASO_PARAM *ppp,u16 wazano);
void	PokeWazaSetPos(POKEMON_PARAM *pp,u16 wazano,u8 pos);
void	PokePasoWazaSetPos(POKEMON_PASO_PARAM *ppp,u16 wazano,u8 pos);
u16		PokeWazaOboeCheck(POKEMON_PARAM *pp,int *cnt,u16 *wazano);
void	PokeParaWazaReplace(POKEMON_PARAM *pp,int src_pos,int dest_pos);
void	PokePasoParaWazaReplace(POKEMON_PASO_PARAM *ppp,int src_pos,int dest_pos);
void	PokeParaWazaDelPos(POKEMON_PARAM *pp,u32 pos);
BOOL	PokeParaWazaHaveCheck(POKEMON_PARAM *pp,u16 waza_no);

void	PokeReplace(POKEMON_PASO_PARAM *ppp,POKEMON_PARAM *pp);
u8		GetStockPokeMaxLevel(POKEPARTY *ppt);

u16		PokeParaZenkokuNo2ShinouNo(POKEMON_PARAM *pp);
u16		PokePasoParaZenkokuNo2ShinouNo(POKEMON_PASO_PARAM *ppp);
u16		PokeZenkokuNo2ShinouNo(u16 mons_no);
u16		PokeShinouNo2ZenkokuNo(u16 mons_no);

void	PokeCopyPPtoPP(POKEMON_PARAM *pp_src,POKEMON_PARAM *pp_dest);
void	PokeCopyPPPtoPPP(POKEMON_PASO_PARAM *ppp_src,POKEMON_PASO_PARAM *ppp_dest);
void	PokeCopyPPtoPPP(POKEMON_PARAM *pp_src,POKEMON_PASO_PARAM *ppp_dest);

s8		PokeParaLikeTasteCheck(POKEMON_PARAM *pp,int taste);
s8		PokePasoParaLikeTasteCheck(POKEMON_PASO_PARAM *ppp,int taste);
s8		PokeLikeTasteCheck(u32 rnd,int taste);

void	PokerusSetCheck(POKEPARTY *ppt);
u8		PokerusCheck(POKEPARTY *ppt,u8 check_bit);
u8		PokerusedCheck(POKEPARTY *ppt,u8 check_bit);
void	PokerusCounterDec(POKEPARTY *ppt,s32 day);
void	PokerusCatchCheck(POKEPARTY *ppt);

BOOL	PokeParaPokerusCheck(POKEMON_PARAM *pp);
BOOL	PokePasoParaPokerusCheck(POKEMON_PASO_PARAM *ppp);
BOOL	PokeParaPokerusedCheck(POKEMON_PARAM *pp);
BOOL	PokePasoParaPokerusedCheck(POKEMON_PASO_PARAM *ppp);

void	PokeParaAusuFormChange(POKEMON_PARAM *pp);
void	PokePasoParaAusuFormChange(POKEMON_PASO_PARAM *ppp);
u8		AusuTypeGet(u16	item_param);

void	PokeWazaOboeDataGet(int monsno,u16 *wot);
void	PokeFormNoWazaOboeDataGet(int monsno,int form_no,u16 *wot);

void	PokeVoicePlaySet(PERAPVOICE *p_voice,int voice,u16 monsno,int pan,int vol,int flag,int heapID);


void	PokeParaGetInfoSet(POKEMON_PARAM *pp,MYSTATUS *status,int ball,int place,int ground_id,int heapID);
void	PokePasoParaGetInfoSet(POKEMON_PASO_PARAM *ppp,MYSTATUS *status,int ball,int place,int ground_id,int heapID);
void	PokeParaBirthInfoSet(POKEMON_PARAM *pp,MYSTATUS *status,int ball,int place,int ground_id,int heapID);
void	PokePasoParaBirthInfoSet(POKEMON_PASO_PARAM *ppp,MYSTATUS *status,int ball,int place,int ground_id,int heapID);

void	PokeItemSet(POKEMON_PARAM *pp,u32 fight_type,int range);

BOOL	PokeParaWazaMachineCheck(POKEMON_PARAM *pp,u8 machine_no);
BOOL	PokePasoParaWazaMachineCheck(POKEMON_PASO_PARAM *pp,u8 machine_no);
BOOL	PokeWazaMachineCheck(u16 mons_no,int form_no,u8 machine_no);

void	PokeParaSpeabiSet(POKEMON_PARAM *pp);
void	PokePasoParaSpeabiSet(POKEMON_PASO_PARAM *ppp);

void	PokeParaPersonalRndChange(POKEMON_PARAM *pp,u32 personal_rnd);

static	void	PokePersonalDataGet(int mons_no,POKEMON_PERSONAL_DATA *ppd);
static	void	PokeFormNoPersonalDataGet(int mons_no,int form_no,POKEMON_PERSONAL_DATA *ppd);
static	void	PokeShinkaDataGet(int mons_no,POKEMON_SHINKA_TABLE *pst);
static	void	PokeParaCoded(void *data,u32 size,u32 code);
static	void	PokeParaDecoded(void *data,u32 size,u32 code);
static	u16		CodeRand(u32 *code);
static	u16		PokeParaCheckSum(void *data,u32 size);
static	void	*PokeParaAdrsGet(POKEMON_PASO_PARAM *ppp,u32 rnd,u8 id);
static	int		PokeOtherFormMonsNoGet(int mons_no,int form_no);

u32		No2Bit(int no);
int		Bit2No(u32 bit);

BOOL BattleTowerExPokeCheck_MonsNo( u16 mons );
BOOL BattleTowerExPokeCheck_PokePara( POKEMON_PARAM * pp );

int	TrainerBTrTypeGet(int trtype);

//============================================================================================
/**
 *	�|�P�����p�����[�^�\���̂�����������
 *
 * @param[in]	pp	����������|�P�����p�����[�^�\���̂̃|�C���^
 */
//============================================================================================
void	PokeParaInit(POKEMON_PARAM *pp)
{
	MI_CpuClearFast(pp,sizeof(POKEMON_PARAM));
//�p�����[�^���Í���
	PokeParaCoded(&pp->ppp.paradata,sizeof(POKEMON_PASO_PARAM1)*4,pp->ppp.checksum);
	PokeParaCoded(&pp->pcp,sizeof(POKEMON_CALC_PARAM),pp->ppp.personal_rnd);
}

//============================================================================================
/**
 *	�{�b�N�X�|�P�����p�����[�^�\���̂�����������
 *
 * @param[in]	ppp	����������{�b�N�X�|�P�����p�����[�^�\���̂̃|�C���^
 */
//============================================================================================
void	PokePasoParaInit(POKEMON_PASO_PARAM *ppp)
{
	MI_CpuClearFast(ppp,sizeof(POKEMON_PASO_PARAM));
//�������Z�b�g�����Ƃ���ňÍ���
	PokeParaCoded(ppp->paradata,sizeof(POKEMON_PASO_PARAM1)*4,ppp->checksum);
}

//============================================================================================
/**
 *	POKEMON_PARAM�\���̂̃T�C�Y��Ԃ�
 *
 * @retval	POKEMON_PARAM�\���̂̃T�C�Y
 */
//============================================================================================
int		PokemonParam_GetWorkSize(void)
{
	return sizeof(POKEMON_PARAM);
}

//============================================================================================
/**
 *	POKEMON_PARAM�\���̂̃��[�N���m�ہA���������ă|�C���^��Ԃ�
 *
 *	@param[in]	heapID	���������m�ۂ���q�[�vID
 *
 * @retval	POKEMON_PARAM�\���̂ւ̃|�C���^
 */
//============================================================================================
POKEMON_PARAM	*PokemonParam_AllocWork(u32 heapID)
{
	POKEMON_PARAM	*pp;

	pp=sys_AllocMemory(heapID,sizeof(POKEMON_PARAM));
	PokeParaInit(pp);

	return pp;
}

//============================================================================================
/**
 *	�|�P�����p�����[�^�\���̂ւ̃A�N�Z�X�����������[�h��
 *
 * @param[in]	pp	�|�P�����p�����[�^�\���̂ւ̃|�C���^
 *
 * @retval	FALSE:���łɍ��������[�h�ɂȂ��Ă���@TRUE:���������[�h�ֈڍs
 */
//============================================================================================
BOOL	PokeParaFastModeOn(POKEMON_PARAM *pp)
{
	BOOL	ret;

	ret=FALSE;

	if(pp->ppp.pp_fast_mode==0){
		ret=TRUE;
		GF_ASSERT_MSG(pp->ppp.ppp_fast_mode==0,"ppp�����������[�h�ɂȂ��Ă��܂�\n");
		pp->ppp.pp_fast_mode=1;
		pp->ppp.ppp_fast_mode=1;
		PokeParaDecoded(&pp->pcp,sizeof(POKEMON_CALC_PARAM),pp->ppp.personal_rnd);
		PokeParaDecoded(&pp->ppp.paradata,sizeof(POKEMON_PASO_PARAM1)*4,pp->ppp.checksum);
	}

	return ret;
}

//============================================================================================
/**
 *	�|�P�����p�����[�^�\���̂ւ̃A�N�Z�X��ʏ탂�[�h��
 *
 * @param[in]	pp	�|�P�����p�����[�^�\���̂ւ̃|�C���^
 * @param[in]	flag	���[�h�ڍs�\�����f���邽�߂̃t���O�iFALSE:�ڍs�s�ATRUE:�ڍs����j
 *
 * @retval	FALSE:���łɒʏ탂�[�h�ɂȂ��Ă���@TRUE:�ʏ탂�[�h�ֈڍs
 */
//============================================================================================
BOOL	PokeParaFastModeOff(POKEMON_PARAM *pp,BOOL flag)
{
	BOOL	ret;

	ret=FALSE;

	if((pp->ppp.pp_fast_mode==1)&&(flag==TRUE)){
		ret=TRUE;
		pp->ppp.pp_fast_mode=0;
		pp->ppp.ppp_fast_mode=0;

		PokeParaCoded(&pp->pcp,sizeof(POKEMON_CALC_PARAM),pp->ppp.personal_rnd);
		pp->ppp.checksum=PokeParaCheckSum(&pp->ppp.paradata,sizeof(POKEMON_PASO_PARAM1)*4);
		PokeParaCoded(&pp->ppp.paradata,sizeof(POKEMON_PASO_PARAM1)*4,pp->ppp.checksum);
	}

	return ret;
}

//============================================================================================
/**
 *	�{�b�N�X�|�P�����p�����[�^�\���̂ւ̃A�N�Z�X�����������[�h��
 *
 * @param[in]	ppp	�{�b�N�X�|�P�����p�����[�^�\���̂ւ̃|�C���^
 *
 * @retval	FALSE:���łɍ��������[�h�ɂȂ��Ă���@TRUE:���������[�h�ֈڍs
 */
//============================================================================================
BOOL	PokePasoParaFastModeOn(POKEMON_PASO_PARAM *ppp)
{
	BOOL	ret;

	ret=FALSE;

	if(ppp->ppp_fast_mode==0){
		ret=TRUE;
		ppp->ppp_fast_mode=1;
		PokeParaDecoded(ppp->paradata,sizeof(POKEMON_PASO_PARAM1)*4,ppp->checksum);
	}

	return ret;
}

//============================================================================================
/**
 *	�{�b�N�X�|�P�����p�����[�^�\���̂ւ̃A�N�Z�X��ʏ탂�[�h��
 *
 * @param[in]	ppp		�{�b�N�X�|�P�����p�����[�^�\���̂ւ̃|�C���^
 * @param[in]	flag	���[�h�ڍs�\�����f���邽�߂̃t���O�iFALSE:�ڍs�s�ATRUE:�ڍs����j
 *
 * @retval	FALSE:���łɒʏ탂�[�h�ɂȂ��Ă���@TRUE:�ʏ탂�[�h�ֈڍs
 */
//============================================================================================
BOOL	PokePasoParaFastModeOff(POKEMON_PASO_PARAM *ppp,BOOL flag)
{
	BOOL	ret;

	ret=FALSE;

	if((ppp->ppp_fast_mode==1)&&(flag==TRUE)){
		ret=TRUE;
		ppp->ppp_fast_mode=0;

		ppp->checksum=PokeParaCheckSum(ppp->paradata,sizeof(POKEMON_PASO_PARAM1)*4);
		PokeParaCoded(ppp->paradata,sizeof(POKEMON_PASO_PARAM1)*4,ppp->checksum);
	}

	return ret;
}

//============================================================================================
/**
 *	�|�P�����p�����[�^�\���̂Ƀ|�P�����p�����[�^�𐶐�
 *
 * @param[in]	pp		�p�����[�^�𐶐�����|�P�����p�����[�^�\���̂̃|�C���^
 * @param[in]	mons_no	�p�����[�^�𐶐�����|�P�����i���o�[
 * @param[in]	level	�������郌�x��
 * @param[in]	pow		POW_RND�ȊO:�Z�b�g����p���[�����@POW_RND:�p���[�����������_���ŃZ�b�g
 * @param[in]	rndflag	�������Z�b�g�t���O�iRND_NO_SET:�������������_���ŃZ�b�g RND_SET:����rnd�̒l���Z�b�g
 * @param[in]	rnd		rndflag��RND_SET�̎��ɃZ�b�g�����l
 * @param[in]	idflag	IDNo�Z�b�g�t���O�iID_NO_SET:�v���C���[��ID���Z�b�g ID_SET:����id�̒l���Z�b�g
 *										�@ID_NO_RARE:�������Ƃ̑g�ݍ��킹�Ń��A�|�P�����ɂȂ�Ȃ��悤�ɒl�𒲐����ăZ�b�g�j
 * @param[in]	id		idflag��ID_SET�̎��ɃZ�b�g�����l
 */
//============================================================================================
void	PokeParaSet(POKEMON_PARAM *pp,int mons_no,int level,int pow,int rndflag,u32 rnd,int idflag,u32 id)
{
	u32				i;
	MAIL_DATA		*mail_data;
//	CB_SAVE_DATA	*cb_core;
	CB_CORE cb_core;

	PokeParaInit(pp);

	PokePasoParaSet((POKEMON_PASO_PARAM *)&pp->ppp,mons_no,level,pow,rndflag,rnd,idflag,id);

//�����������܂�����APCP���ĈÍ���
	PokeParaCoded(&pp->pcp,sizeof(POKEMON_CALC_PARAM),0);
	PokeParaCoded(&pp->pcp,sizeof(POKEMON_CALC_PARAM),pp->ppp.personal_rnd);

//���x���Z�b�g
	PokeParaPut(pp,ID_PARA_level,(u8 *)&level);

//���[���f�[�^
	mail_data=MailData_CreateWork(HEAPID_BASE_SYSTEM);
	PokeParaPut(pp,ID_PARA_mail_data,mail_data);
	sys_FreeMemoryEz(mail_data);

//�J�X�^���{�[��ID
	i=0;
	PokeParaPut(pp,ID_PARA_cb_id,(u8 *)&i);

//�J�X�^���{�[��
//	cb_core=CustomBall_AllocSaveData(HEAPID_BASE_SYSTEM);
//	PokeParaPut(pp,ID_PARA_cb_core,cb_core);
//	sys_FreeMemoryEz(cb_core);
	
	MI_CpuClearFast(&cb_core, sizeof(CB_CORE));
	PokeParaPut(pp,	ID_PARA_cb_core, (CB_CORE*)&cb_core);							

	PokeParaCalc(pp);
}

//============================================================================================
/**
 *	�{�b�N�X�|�P�����p�����[�^�\���̂Ƀ|�P�����p�����[�^�𐶐�
 *
 * @param[in]	ppp		�p�����[�^�𐶐�����{�b�N�X�|�P�����p�����[�^�\���̂̃|�C���^
 * @param[in]	mons_no	�p�����[�^�𐶐�����|�P�����i���o�[
 * @param[in]	level	�������郌�x��
 * @param[in]	pow		POW_RND�ȊO:�Z�b�g����p���[�����@POW_RND:�p���[�����������_���ŃZ�b�g
 * @param[in]	rndflag	�������Z�b�g�t���O�iRND_NO_SET:�������������_���ŃZ�b�g RND_SET:����rnd�̒l���Z�b�g
 * @param[in]	rnd		rndflag��RND_SET�̎��ɃZ�b�g�����l
 * @param[in]	idflag	IDNo�Z�b�g�t���O�iID_NO_SET:�v���C���[��ID���Z�b�g ID_SET:����id�̒l���Z�b�g
 *										�@ID_NO_RARE:�������Ƃ̑g�ݍ��킹�Ń��A�|�P�����ɂȂ�Ȃ��悤�ɒl�𒲐����ăZ�b�g�j
 * @param[in]	id		idflag��ID_SET�̎��ɃZ�b�g�����l
 */
//============================================================================================
void	PokePasoParaSet(POKEMON_PASO_PARAM *ppp,int mons_no,int level,int pow,int rndflag,u32 rnd,int idflag,u32 id)
{
	u16	sum;
	u32	i,j;
	BOOL	flag;

	PokePasoParaInit(ppp);

	flag=PokePasoParaFastModeOn(ppp);

//�������Z�b�g
	if(!rndflag){
		rnd=(gf_rand()|(gf_rand()<<16));
	}
	PokePasoParaPut(ppp,ID_PARA_personal_rnd,(u8 *)&rnd);

//ID�i���o�[�Z�b�g
	if(idflag==ID_NO_RARE){
		do{
			id=(gf_rand()|(gf_rand()<<16));
		}while((((id&0xffff0000)>>16)^(id&0xffff)^((rnd&0xffff0000)>>16)^(rnd&0xffff))<8);
	}
	else if(idflag!=ID_SET){
		id=0;
	}
	PokePasoParaPut(ppp,ID_PARA_id_no,(u8 *)&id);
	
//���R�[�h
	PokePasoParaPut(ppp,ID_PARA_country_code,(u8 *)&CasetteLanguage);

//�|�P�����i���o�[�Z�b�g
	PokePasoParaPut(ppp,ID_PARA_monsno,(u8 *)&mons_no);

//�j�b�N�l�[���Z�b�g
//	MSGDAT_MonsNameGet(mons_no,HEAPID_BASE_SYSTEM,buf);
//	PokePasoParaPut(ppp,ID_PARA_nickname,(u8 *)&buf);
	PokePasoParaPut(ppp,ID_PARA_default_name,NULL);

//�o���l�Z�b�g
	i=PokeLevelExpGet(mons_no,level);
	PokePasoParaPut(ppp,ID_PARA_exp,(u8 *)&i);

//�F�D�l�Z�b�g
	i=PokePersonalParaGet(mons_no,ID_PER_friend);
	PokePasoParaPut(ppp,ID_PARA_friend,(u8 *)&i);

//�ߊl�f�[�^�Z�b�g
	PokePasoParaPut(ppp,ID_PARA_get_level,(u8 *)&level);
	PokePasoParaPut(ppp,ID_PARA_get_cassette,(u8 *)&CasetteVersion);
	i=ITEM_MONSUTAABOORU;	//�f�t�H���g�̓����X�^�[�{�[���ɂ��Ă���	
	PokePasoParaPut(ppp,ID_PARA_get_ball,(u8 *)&i);

//�p���[�����Z�b�g
	if(pow<POW_RND){
		PokePasoParaPut(ppp,ID_PARA_hp_rnd,(u8 *)&pow);
		PokePasoParaPut(ppp,ID_PARA_pow_rnd,(u8 *)&pow);
		PokePasoParaPut(ppp,ID_PARA_def_rnd,(u8 *)&pow);
		PokePasoParaPut(ppp,ID_PARA_agi_rnd,(u8 *)&pow);
		PokePasoParaPut(ppp,ID_PARA_spepow_rnd,(u8 *)&pow);
		PokePasoParaPut(ppp,ID_PARA_spedef_rnd,(u8 *)&pow);
	}
	else{
		i=gf_rand();
		j=(i&(0x001f<< 0))>> 0;
		PokePasoParaPut(ppp,ID_PARA_hp_rnd,(u8 *)&j);
		j=(i&(0x001f<< 5))>> 5;
		PokePasoParaPut(ppp,ID_PARA_pow_rnd,(u8 *)&j);
		j=(i&(0x001f<<10))>>10;
		PokePasoParaPut(ppp,ID_PARA_def_rnd,(u8 *)&j);
		i=gf_rand();
		j=(i&(0x001f<< 0))>> 0;
		PokePasoParaPut(ppp,ID_PARA_agi_rnd,(u8 *)&j);
		j=(i&(0x001f<< 5))>> 5;
		PokePasoParaPut(ppp,ID_PARA_spepow_rnd,(u8 *)&j);
		j=(i&(0x001f<<10))>>10;
		PokePasoParaPut(ppp,ID_PARA_spedef_rnd,(u8 *)&j);
	}

//����\�̓Z�b�g
	i=PokePersonalParaGet(mons_no,ID_PER_speabi1);
	j=PokePersonalParaGet(mons_no,ID_PER_speabi2);
	if(j!=0){
		if(rnd&1){
			PokePasoParaPut(ppp,ID_PARA_speabino,(u8 *)&j);
		}
		else{
			PokePasoParaPut(ppp,ID_PARA_speabino,(u8 *)&i);
		}
	}
	else{
		PokePasoParaPut(ppp,ID_PARA_speabino,(u8 *)&i);
	}

//���ʃZ�b�g
	i=PokePasoSexGet(ppp);
	PokePasoParaPut(ppp,ID_PARA_sex,(u8 *)&i);

//�Z�Z�b�g
	PokePasoWazaOboe(ppp);

	PokePasoParaFastModeOff(ppp,flag);
}

//============================================================================================
/**
 *	PokeParaSetChr(�|�P�����̃p�����[�^���Z�b�g����B���i�����߂����Łj
 *
 *	@param[in]	PP			�p�����[�^���Z�b�g����\���̂̃|�C���^
 *	@param[in]	pokeno		�|�P�����i���o�[
 *	@param[in]	pokelevel	�|�P�����̃��x��
 *	@param[in]	pow			�Z�b�g����p���[����(POW_RND�̎��͗����ŃZ�b�g�j
 *	@param[in]	chr			�Z�b�g���鐫�i�i�O�`�Q�S�j
*/
//============================================================================================
void	PokeParaSetChr(POKEMON_PARAM *pp,u16 pokeno,u8 pokelevel,u8 pow,u8 chr)
{
	u32	i;

	do{
		i=(gf_rand()|(gf_rand()<<16));
	}while(chr!=PokeSeikakuGetRnd(i));

	PokeParaSet(pp,pokeno,pokelevel,pow,RND_SET,i,ID_NO_SET,0);
}

//============================================================================================
/**
 *	PokeParaSetSexChr(�|�P�����̃p�����[�^���Z�b�g����B���ʁA���i�����߂����Łj
 *	�i�G���J�E���g�̃|�P�����𐶐�����̂ɂ͎g��Ȃ��ł��������B���������΂�܂��j
 *
 *	@param[in]	PP			�p�����[�^���Z�b�g����\���̂̃|�C���^
 *	@param[in]	pokeno		�|�P�����i���o�[
 *	@param[in]	pokelevel	�|�P�����̃��x��
 *	@param[in]	pow			�Z�b�g����p���[����(POW_RND�̎��͗����ŃZ�b�g�j
 *	@param[in]	chr			�Z�b�g���鐫�i�i�O�`�Q�S�j
 *	@param[in]	annon		�A���m�[���̌`����i0:�֌W�����j
*/
//============================================================================================
void	PokeParaSetSexChr(POKEMON_PARAM *pp,u16 pokeno,u8 pokelevel,u8 pow,u8 sex,u8 chr,u8 annon)
{
	u32	i;
	u32	per_sex;
	u16	annon_rnd;

	if((annon)&&(annon<29)){
		do{
			i=(gf_rand()|(gf_rand()<<16));
			annon_rnd=(((i&0x03000000)>>18)|((i&0x030000)>>12)|((i&0x0300)>>6)|(i&0x03))%28;
		}while((chr!=PokeSeikakuGetRnd(i))||
			   (sex!=PokeSexGetMonsNo(pokeno,i))||
			   (annon_rnd!=(annon-1)));
	}
	else{
		i=PokeParaSexChrRndGet(pokeno,sex,chr);
	}
	PokeParaSet(pp,pokeno,pokelevel,pow,RND_SET,i,ID_NO_SET,0);
}

u32	PokeParaSexChrRndGet(u16 mons_no,u8 sex,u8 chr)
{
	u8	per_sex;
	u32	rnd;

	per_sex=PokePersonalParaGet(mons_no,ID_PER_sex);

	switch(per_sex){
	case MONS_MALE:
	case MONS_FEMALE:
	case MONS_UNKNOWN:
		rnd=chr;
		break;
	default:
		if(sex==PARA_MALE){
			rnd=25*((per_sex/25)+1);
			rnd+=chr;
		}
		else{
			rnd=chr;
		}
		break;
	}
	return rnd;
}

//============================================================================================
/**
 *
 *	PokeParaSetPowRnd(�|�P�����̃p�����[�^���Z�b�g����B�p���[������u32�Ŏ󂯎���đ���j
 *
 *	@param[in]	PP			�p�����[�^���Z�b�g����\���̂̃|�C���^
 *	@param[in]	pokeno		�|�P�����i���o�[
 *	@param[in]	pokelevel	�|�P�����̃��x��
 *	@param[in]	pow			�Z�b�g����p���[����
 *	@param[in]	rnd			�Z�b�g���������
*/
//============================================================================================
void	PokeParaSetPowRnd(POKEMON_PARAM *pp,u16 pokeno,u8 pokelevel,u32 pow,u32 rnd)
{
	PokeParaSet(pp,pokeno,pokelevel,0,RND_SET,rnd,ID_NO_SET,0);

	PokeParaPut(pp,ID_PARA_power_rnd,(u8 *)&pow);

	PokeParaCalc(pp);
}

//============================================================================================
/**
 *
 *	PokeParaSetPowRndBuf(�|�P�����̃p�����[�^���Z�b�g����B�p���[������u8 *�Ŏ󂯎���đ���j
 *
 *	@param[in]	PP			�p�����[�^���Z�b�g����\���̂̃|�C���^
 *	@param[in]	pokeno		�|�P�����i���o�[
 *	@param[in]	pokelevel	�|�P�����̃��x��
 *	@param[in]	pow			�Z�b�g����p���[����
 *	@param[in]	id			�Z�b�g����ID�i���o�[
*/
//============================================================================================
void	PokeParaSetPowRndBuf(POKEMON_PARAM *pp,u16 pokeno,u8 pokelevel,u8 *pow,u32 id)
{
	PokeParaSet(pp,pokeno,pokelevel,0,RND_NO_SET,0,ID_SET,id);

	PokeParaPut(pp,ID_PARA_hp_rnd,(u8 *)&pow[0]);
	PokeParaPut(pp,ID_PARA_pow_rnd,(u8 *)&pow[1]);
	PokeParaPut(pp,ID_PARA_def_rnd,(u8 *)&pow[2]);
	PokeParaPut(pp,ID_PARA_agi_rnd,(u8 *)&pow[3]);
	PokeParaPut(pp,ID_PARA_spepow_rnd,(u8 *)&pow[4]);
	PokeParaPut(pp,ID_PARA_spedef_rnd,(u8 *)&pow[5]);

	PokeParaCalc(pp);
}

//============================================================================================
/**
 *
 *	PokeParaSetParaExp(�|�P�����̃p�����[�^���Z�b�g����B�w�͒l���Z�b�g����j
 *
 *	@param[in]	pp			�p�����[�^���Z�b�g����\���̂̃|�C���^
 *	@param[in]	pokeno		�|�P�����i���o�[
 *	@param[in]	pokelevel	�|�P�����̃��x��
 *	@param[in]	pow			�Z�b�g����p���[����
 *	@param[in]	expbit		�Z�b�g����w�͒l�̃r�b�g(0bit:hp_exp 1bit:pow_exp 2bit:def_exp...�j
*/
//============================================================================================
void	PokeParaSetParaExp(POKEMON_PARAM *pp,u16 pokeno,u8 pokelevel,u8 pow,u8 expbit)
{
	int	i;
	int	cnt=0;
	u16	exp;
	u8	bit;

	PokeParaSet(pp,pokeno,pokelevel,pow,RND_NO_SET,0,ID_NO_SET,0);

	bit=expbit;
	for(i=0;i<6;i++){
		if(bit&1)
			cnt++;
		bit=bit>>1;
	}
	exp=PARA_EXP_TOTAL_MAX/cnt;
	bit=1;
	for(i=0;i<6;i++){
		if(expbit&bit)
			PokeParaPut(pp,ID_PARA_hp_exp+i,(u8 *)&exp);
		bit=bit<<1;
	}
	PokeParaCalc(pp);
}

//=========================================================================
/**
 *	�o�g���{�ݗp��PokeParaSet
 *
 *	@param	pp			�p�����[�^���Z�b�g����\���̂̃|�C���^
 *	@param	pokeno		�|�P�����i���o�[
 *	@param	pokelevel	�|�P�����̃��x��
 *	@param	chr			�Z�b�g���鐫�i
 *	@param	pow			�Z�b�g����p���[����
 *	@param	expbit		�Z�b�g����w�͒l�̃r�b�g(0bit:hp_exp 1bit:pow_exp 2bit:def_exp...�j
 *	@param	id			�Z�b�g����ID
 */
//=========================================================================
void	PokeParaSetBattleFrontier(POKEMON_PARAM *pp,u16 pokeno,u8 pokelevel,u8 chr,u8 pow,u8 expbit,u32 id)
{
	int	i;
	int	cnt=0;
	u16	exp;
	u8	bit;

	do{
		i=(gf_rand()|(gf_rand()<<16));
	}while(chr!=PokeSeikakuGetRnd(i));

	PokeParaSet(pp,pokeno,pokelevel,pow,RND_SET,i,ID_SET,id);

	bit=expbit;
	for(i=0;i<6;i++){
		if(bit&1){
			cnt++;
		}
		bit=bit>>1;
	}
	exp=PARA_EXP_TOTAL_MAX/cnt;
	bit=1;
	for(i=0;i<6;i++){
		if(expbit&bit){
			PokeParaPut(pp,ID_PARA_hp_exp+i,(u8 *)&exp);
		}
		bit=bit<<1;
	}
	PokeParaCalc(pp);
}

//============================================================================================
/**
 *	�|�P�����p�����[�^�v�Z���[�`��
 *
 * @param[in]	pp	�v�Z����|�P�����p�����[�^�\���̂̃|�C���^
 */
//============================================================================================
void	PokeParaCalc(POKEMON_PARAM *pp)
{
	int		level;
	BOOL	flag;

	flag=PokeParaFastModeOn(pp);

//���x���Z�b�g
	level=PokeParaLevelCalc(pp);
	PokeParaPut(pp,ID_PARA_level,(u8 *)&level);

	PokeParaCalcLevelUp(pp);

	PokeParaFastModeOff(pp,flag);
}

//============================================================================================
/**
 *	�|�P�����p�����[�^�v�Z���[�`���i���x���A�b�v����p�j
 *
 * @param[in]	pp	�v�Z����|�P�����p�����[�^�\���̂̃|�C���^
 */
//============================================================================================
void	PokeParaCalcLevelUp(POKEMON_PARAM *pp)
{
	int	oldhpmax,hp,hpmax;
	int	pow,def,agi,spepow,spedef;
	int	hp_rnd,pow_rnd,def_rnd,agi_rnd,spepow_rnd,spedef_rnd;
	int	hp_exp,pow_exp,def_exp,agi_exp,spepow_exp,spedef_exp;
	int	monsno;
	int	level;
	int	form_no;
	int	speabi1,speabi2,rnd;
	POKEMON_PERSONAL_DATA *ppd;
	BOOL	flag;

	flag=PokeParaFastModeOn(pp);

	level=		PokeParaGet(pp,ID_PARA_level,		0);
	oldhpmax=	PokeParaGet(pp,ID_PARA_hpmax,		0);
	hp=			PokeParaGet(pp,ID_PARA_hp,			0);
	hp_rnd=		PokeParaGet(pp,ID_PARA_hp_rnd,		0);
	hp_exp=		PokeParaGet(pp,ID_PARA_hp_exp,		0);
	pow_rnd=	PokeParaGet(pp,ID_PARA_pow_rnd,		0);
	pow_exp=	PokeParaGet(pp,ID_PARA_pow_exp,		0);
	def_rnd=	PokeParaGet(pp,ID_PARA_def_rnd,		0);
	def_exp=	PokeParaGet(pp,ID_PARA_def_exp,		0);
	agi_rnd=	PokeParaGet(pp,ID_PARA_agi_rnd,		0);
	agi_exp=	PokeParaGet(pp,ID_PARA_agi_exp,		0);
	spepow_rnd=	PokeParaGet(pp,ID_PARA_spepow_rnd,	0);
	spepow_exp=	PokeParaGet(pp,ID_PARA_spepow_exp,	0);
	spedef_rnd=	PokeParaGet(pp,ID_PARA_spedef_rnd,	0);
	spedef_exp=	PokeParaGet(pp,ID_PARA_spedef_exp,	0);
	form_no=	PokeParaGet(pp,ID_PARA_form_no,		0);

	monsno=PokeParaGet(pp,ID_PARA_monsno,0);

	ppd=sys_AllocMemory(HEAPID_BASE_SYSTEM,sizeof(POKEMON_PERSONAL_DATA));
	PokeFormNoPersonalDataGet(monsno,form_no,ppd);

	if(monsno==MONSNO_NUKENIN){
		hpmax=1;
	}
	else{
		hpmax=((2*ppd->basic_hp+hp_rnd+hp_exp/4)*level/100+level+10);
	}

	PokeParaPut(pp,ID_PARA_hpmax,(u8 *)&hpmax);

	pow=((2*ppd->basic_pow+pow_rnd+pow_exp/4)*level/100+5);
	pow=PokeChrAbiCalc(PokeSeikakuGet(pp),pow,COND_POW);
	PokeParaPut(pp,ID_PARA_pow,(u8 *)&pow);

	def=((2*ppd->basic_def+def_rnd+def_exp/4)*level/100+5);
	def=PokeChrAbiCalc(PokeSeikakuGet(pp),def,COND_DEF);
	PokeParaPut(pp,ID_PARA_def,(u8 *)&def);

	agi=((2*ppd->basic_agi+agi_rnd+agi_exp/4)*level/100+5);
	agi=PokeChrAbiCalc(PokeSeikakuGet(pp),agi,COND_AGI);
	PokeParaPut(pp,ID_PARA_agi,(u8 *)&agi);

	spepow=((2*ppd->basic_spepow+spepow_rnd+spepow_exp/4)*level/100+5);
	spepow=PokeChrAbiCalc(PokeSeikakuGet(pp),spepow,COND_SPEPOW);
	PokeParaPut(pp,ID_PARA_spepow,(u8 *)&spepow);

	spedef=((2*ppd->basic_spedef+spedef_rnd+spedef_exp/4)*level/100+5);
	spedef=PokeChrAbiCalc(PokeSeikakuGet(pp),spedef,COND_SPEDEF);
	PokeParaPut(pp,ID_PARA_spedef,(u8 *)&spedef);
	
	sys_FreeMemoryEz(ppd);

	if((hp==0)&&(oldhpmax!=0)){
		;
	}
	else{
		if(monsno==MONSNO_NUKENIN){
			hp=1;
		}
		else if(hp==0){
			hp=hpmax;
		}
		else{
			hp+=(hpmax-oldhpmax);
		}
	}

	if(hp){
		PokeParaPut(pp,ID_PARA_hp,(u8 *)&hp);
	}

	PokeParaFastModeOff(pp,flag);
}

//�ꉞ�c���Ă���
#if 0
	if(monsno==MONSNO_NUKENIN){
		if((hp==0)&&(oldhpmax!=0)){
			sys_FreeMemoryEz(ppd);
			return;
		}
		hp=1;
	}
	else{
		if((hp==0)&&(oldhpmax!=0)){
			sys_FreeMemoryEz(ppd);
			return;
		}
		if(hp==0){
			hp=hpmax-oldhpmax;
		}
		else{
			hp+=(hpmax-oldhpmax);
		}
	}
	PokeParaPut(pp,ID_PARA_hp,(u8 *)&hp);

	sys_FreeMemoryEz(ppd);

	PokeParaFastModeOff(pp,flag);
#endif

//============================================================================================
/**
 *	�|�P�����p�����[�^�\���̂���C�ӂŒl���擾�i�Í��^�����^�`�F�b�N�T���`�F�b�N����j
 *
 * @param[in]	pp	�擾����|�P�����p�����[�^�\���̂̃|�C���^
 * @param[in]	id	�擾�������f�[�^�̃C���f�b�N�X�ipoke_tool.h�ɒ�`�j
 * @param[out]	buf	�擾�������f�[�^���z��̎��Ɋi�[��̃A�h���X���w��
 *
 * @return		�擾�����f�[�^
 */
//============================================================================================
u32	PokeParaGet(POKEMON_PARAM *pp,int id,void *buf)
{
	u32	ret;
	u16	sum;

//�A�T�[�g���o�����߂ɌĂѕ����Ă������̂Ȃ���
//	GF_ASSERT_MSG(pp->ppp.pp_fast_mode==0,"���������[�h�̂܂܂ɂȂ��Ă܂�\n");

	if(pp->ppp.pp_fast_mode==0){
		PokeParaDecoded(&pp->pcp,sizeof(POKEMON_CALC_PARAM),pp->ppp.personal_rnd);
		PokeParaDecoded(&pp->ppp.paradata,sizeof(POKEMON_PASO_PARAM1)*4,pp->ppp.checksum);
		sum=PokeParaCheckSum(&pp->ppp.paradata,sizeof(POKEMON_PASO_PARAM1)*4);
		if(sum!=pp->ppp.checksum){
			GF_ASSERT_MSG((sum==pp->ppp.checksum),"checksum Crash!\n");
			pp->ppp.fusei_tamago_flag=1;
		}
	}

	ret=PokeParaGetAct(pp,id,buf);

	if(pp->ppp.pp_fast_mode==0){
		PokeParaCoded(&pp->pcp,sizeof(POKEMON_CALC_PARAM),pp->ppp.personal_rnd);
		PokeParaCoded(&pp->ppp.paradata,sizeof(POKEMON_PASO_PARAM1)*4,pp->ppp.checksum);
	}

	return ret;
}

//�A�T�[�g���o�����߂ɌĂѕ����Ă������ǁAPokeParaGet�ɓ���
#if 0
//============================================================================================
/**
 *	�|�P�����p�����[�^�\���̂���C�ӂŒl���擾�i���������[�h�j
 *
 * @param[in]	pp	�擾����|�P�����p�����[�^�\���̂̃|�C���^
 * @param[in]	id	�擾�������f�[�^�̃C���f�b�N�X�ipoke_tool.h�ɒ�`�j
 * @param[out]	buf	�擾�������f�[�^���z��̎��Ɋi�[��̃A�h���X���w��
 *
 * @return		�擾�����f�[�^
 */
//============================================================================================
u32	PokeParaGetFast(POKEMON_PARAM *pp,int id,void *buf)
{
	GF_ASSERT_MSG(pp->ppp.pp_fast_mode==1,"���������[�h�ł͂Ȃ��̂ɌĂ΂�Ă��܂�\n");

	return PokeParaGetAct(pp,id,buf);
}
#endif

//============================================================================================
/**
 *	�|�P�����p�����[�^�\���̂���C�ӂŒl���擾
 *
 * @param[in]	pp	�擾����|�P�����p�����[�^�\���̂̃|�C���^
 * @param[in]	id	�擾�������f�[�^�̃C���f�b�N�X�ipoke_tool.h�ɒ�`�j
 * @param[out]	buf	�擾�������f�[�^���z��̎��Ɋi�[��̃A�h���X���w��
 *
 * @return		�擾�����f�[�^
 */
//============================================================================================
static	u32	PokeParaGetAct(POKEMON_PARAM *pp,int id,void *buf)
{
	u32	ret=0;

	switch(id){
	case ID_PARA_condition:
		ret=pp->pcp.condition;
		break;
	case ID_PARA_level:
		ret=pp->pcp.level;
		break;
	case ID_PARA_cb_id:
		ret=pp->pcp.cb_id;
		break;
	case ID_PARA_hp:
		ret=pp->pcp.hp;
		break;
	case ID_PARA_hpmax:
		ret=pp->pcp.hpmax;
		break;
	case ID_PARA_pow:
		ret=pp->pcp.pow;
		break;
	case ID_PARA_def:
		ret=pp->pcp.def;
		break;
	case ID_PARA_agi:
		ret=pp->pcp.agi;
		break;
	case ID_PARA_spepow:
		ret=pp->pcp.spepow;
		break;
	case ID_PARA_spedef:
		ret=pp->pcp.spedef;
		break;
	case ID_PARA_mail_data:
		MailData_Copy(&pp->pcp.mail_data,(MAIL_DATA *)buf);
		ret=TRUE;
		break;
	case ID_PARA_cb_core:
		CB_Tool_CoreData_Copy(&pp->pcp.cb_core,(CB_CORE *)buf);
		ret=TRUE;
		break;
	default:
		ret=PokePasoParaGetAct((POKEMON_PASO_PARAM *)&pp->ppp,id,buf);
		break;
	}
	return	ret;
}

//============================================================================================
/**
 *	�{�b�N�X�|�P�����p�����[�^�\���̂���C�ӂŒl���擾�i�Í��^�����^�`�F�b�N�T���`�F�b�N����j
 *
 * @param[in]	pp	�擾����{�b�N�X�|�P�����p�����[�^�\���̂̃|�C���^
 * @param[in]	id	�擾�������f�[�^�̃C���f�b�N�X�ipoke_tool.h�ɒ�`�j
 * @param[out]	buf	�擾�������f�[�^���z��̎��Ɋi�[��̃A�h���X���w��
 *
 * @return		�擾�����f�[�^
 */
//============================================================================================
u32	PokePasoParaGet(POKEMON_PASO_PARAM *ppp,int id,void *buf)
{
	u16	sum;
	u32	ret;

//�A�T�[�g���o�����߂ɌĂѕ����Ă������̂Ȃ���
//	GF_ASSERT_MSG(ppp->ppp_fast_mode==0,"���������[�h�̂܂܂ɂȂ��Ă܂�\n");

	if(ppp->ppp_fast_mode==0){
		PokeParaDecoded(ppp->paradata,sizeof(POKEMON_PASO_PARAM1)*4,ppp->checksum);
		sum=PokeParaCheckSum(ppp->paradata,sizeof(POKEMON_PASO_PARAM1)*4);
		if(sum!=ppp->checksum){
			GF_ASSERT_MSG((sum==ppp->checksum),"checksum Crash!\n");
			ppp->fusei_tamago_flag=1;
		}
	}

	ret=PokePasoParaGetAct(ppp,id,buf);

	if(ppp->ppp_fast_mode==0){
		PokeParaCoded(ppp->paradata,sizeof(POKEMON_PASO_PARAM1)*4,ppp->checksum);
	}

	return ret;
}

//�A�T�[�g���o�����߂ɌĂѕ����Ă������ǁAPokePasoParaGet�ɓ���
#if 0
//============================================================================================
/**
 *	�{�b�N�X�|�P�����p�����[�^�\���̂���C�ӂŒl���擾�i���������[�h�j
 *
 * @param[in]	pp	�擾����{�b�N�X�|�P�����p�����[�^�\���̂̃|�C���^
 * @param[in]	id	�擾�������f�[�^�̃C���f�b�N�X�ipoke_tool.h�ɒ�`�j
 * @param[out]	buf	�擾�������f�[�^���z��̎��Ɋi�[��̃A�h���X���w��
 *
 * @return		�擾�����f�[�^
 */
//============================================================================================
u32	PokePasoParaGetFast(POKEMON_PASO_PARAM *ppp,int id,void *buf)
{
	GF_ASSERT_MSG(ppp->ppp_fast_mode==1,"���������[�h�ł͂Ȃ��̂ɌĂ΂�Ă��܂�\n");

	return PokePasoParaGetAct(ppp,id,buf);
}
#endif

//============================================================================================
/**
 *	�{�b�N�X�|�P�����p�����[�^�\���̂���C�ӂŒl���擾
 *
 * @param[in]	pp	�擾����{�b�N�X�|�P�����p�����[�^�\���̂̃|�C���^
 * @param[in]	id	�擾�������f�[�^�̃C���f�b�N�X�ipoke_tool.h�ɒ�`�j
 * @param[out]	buf	�擾�������f�[�^���z��̎��Ɋi�[��̃A�h���X���w��
 *
 * @return		�擾�����f�[�^
 */
//============================================================================================
static	u32	PokePasoParaGetAct(POKEMON_PASO_PARAM *ppp,int id,void *buf)
{
	u32	ret=0;
	u64	bit;
	POKEMON_PASO_PARAM1	*ppp1;
	POKEMON_PASO_PARAM2	*ppp2;
	POKEMON_PASO_PARAM3	*ppp3;
	POKEMON_PASO_PARAM4	*ppp4;

	ppp1=(POKEMON_PASO_PARAM1 *)PokeParaAdrsGet(ppp,ppp->personal_rnd,ID_POKEPARA1);
	ppp2=(POKEMON_PASO_PARAM2 *)PokeParaAdrsGet(ppp,ppp->personal_rnd,ID_POKEPARA2);
	ppp3=(POKEMON_PASO_PARAM3 *)PokeParaAdrsGet(ppp,ppp->personal_rnd,ID_POKEPARA3);
	ppp4=(POKEMON_PASO_PARAM4 *)PokeParaAdrsGet(ppp,ppp->personal_rnd,ID_POKEPARA4);

	switch(id){
		default:
			ret=0;
			break;
//PARAM
		case ID_PARA_personal_rnd:
			ret=ppp->personal_rnd;
			break;
		case ID_PARA_pp_fast_mode:
			ret=ppp->pp_fast_mode;
			break;
		case ID_PARA_ppp_fast_mode:
			ret=ppp->ppp_fast_mode;
			break;
		case ID_PARA_fusei_tamago_flag:
			ret=ppp->fusei_tamago_flag;
			break;
		case ID_PARA_checksum:
			ret=ppp->checksum;
			break;
		case ID_PARA_poke_exist:
			ret=(ppp1->monsno!=0);
			break;
		case ID_PARA_tamago_exist:
			if(ppp->fusei_tamago_flag){
				ret=ppp->fusei_tamago_flag;
			}
			else{
				ret=ppp2->tamago_flag;
			}
			break;
		case ID_PARA_monsno_egg:
			ret=ppp1->monsno;
			if(ret==0){
				break;
			}
			else if((ppp2->tamago_flag)||(ppp->fusei_tamago_flag)){
				ret=MONSNO_TAMAGO;
			}
			break;
		case ID_PARA_level:
			ret=PokeLevelCalc(ppp1->monsno,ppp1->exp);
			break;
//PARAM1
		case ID_PARA_monsno:
			if(ppp->fusei_tamago_flag){
				ret=MONSNO_TAMAGO;
			}
			else{
				ret=ppp1->monsno;
			}
			break;
		case ID_PARA_item:
			ret=ppp1->item;
			break;
		case ID_PARA_id_no:
			ret=ppp1->id_no;
			break;
		case ID_PARA_exp:
			ret=ppp1->exp;
			break;
		case ID_PARA_friend:
			ret=ppp1->friend;
			break;
		case ID_PARA_speabino:
			ret=ppp1->speabino;
			break;
		case ID_PARA_mark:
			ret=ppp1->mark;
			break;
		case ID_PARA_country_code:
			ret=ppp1->country_code;
			break;
		case ID_PARA_hp_exp:
			ret=ppp1->hp_exp;
			break;
		case ID_PARA_pow_exp:
			ret=ppp1->pow_exp;
			break;
		case ID_PARA_def_exp:
			ret=ppp1->def_exp;
			break;
		case ID_PARA_agi_exp:
			ret=ppp1->agi_exp;
			break;
		case ID_PARA_spepow_exp:
			ret=ppp1->spepow_exp;
			break;
		case ID_PARA_spedef_exp:
			ret=ppp1->spedef_exp;
			break;
		case ID_PARA_style:
			ret=ppp1->style;
			break;
		case ID_PARA_beautiful:
			ret=ppp1->beautiful;
			break;
		case ID_PARA_cute:
			ret=ppp1->cute;
			break;
		case ID_PARA_clever:
			ret=ppp1->clever;
			break;
		case ID_PARA_strong:
			ret=ppp1->strong;
			break;
		case ID_PARA_fur:
			ret=ppp1->fur;
			break;
		case ID_PARA_sinou_champ_ribbon:				//�V���I�E�`�����v���{��
		case ID_PARA_sinou_battle_tower_ttwin_first:	//�V���I�E�o�g���^���[�^���[�^�C�N�[������1���
		case ID_PARA_sinou_battle_tower_ttwin_second:	//�V���I�E�o�g���^���[�^���[�^�C�N�[������2���
		case ID_PARA_sinou_battle_tower_2vs2_win50:		//�V���I�E�o�g���^���[�^���[�_�u��50�A��
		case ID_PARA_sinou_battle_tower_aimulti_win50:	//�V���I�E�o�g���^���[�^���[AI�}���`50�A��
		case ID_PARA_sinou_battle_tower_siomulti_win50:	//�V���I�E�o�g���^���[�^���[�ʐM�}���`50�A��
		case ID_PARA_sinou_battle_tower_wifi_rank5:		//�V���I�E�o�g���^���[Wifi�����N�T����
		case ID_PARA_sinou_syakki_ribbon:				//�V���I�E����������{��
		case ID_PARA_sinou_dokki_ribbon:				//�V���I�E�ǂ������{��
		case ID_PARA_sinou_syonbo_ribbon:				//�V���I�E�����ڃ��{��
		case ID_PARA_sinou_ukka_ribbon:					//�V���I�E���������{��
		case ID_PARA_sinou_sukki_ribbon:				//�V���I�E���������{��
		case ID_PARA_sinou_gussu_ribbon:				//�V���I�E���������{��
		case ID_PARA_sinou_nikko_ribbon:				//�V���I�E�ɂ������{��
		case ID_PARA_sinou_gorgeous_ribbon:				//�V���I�E�S�[�W���X���{��
		case ID_PARA_sinou_royal_ribbon:				//�V���I�E���C�������{��
		case ID_PARA_sinou_gorgeousroyal_ribbon:		//�V���I�E�S�[�W���X���C�������{��
		case ID_PARA_sinou_ashiato_ribbon:				//�V���I�E�������ƃ��{��
		case ID_PARA_sinou_record_ribbon:				//�V���I�E���R�[�h���{��
		case ID_PARA_sinou_history_ribbon:				//�V���I�E�q�X�g���[���{��
		case ID_PARA_sinou_legend_ribbon:				//�V���I�E���W�F���h���{��
		case ID_PARA_sinou_red_ribbon:					//�V���I�E���b�h���{��
		case ID_PARA_sinou_green_ribbon:				//�V���I�E�O���[�����{��
		case ID_PARA_sinou_blue_ribbon:					//�V���I�E�u���[���{��
		case ID_PARA_sinou_festival_ribbon:				//�V���I�E�t�F�X�e�B�o�����{��
		case ID_PARA_sinou_carnival_ribbon:				//�V���I�E�J�[�j�o�����{��
		case ID_PARA_sinou_classic_ribbon:				//�V���I�E�N���V�b�N���{��
		case ID_PARA_sinou_premiere_ribbon:				//�V���I�E�v���~�A���{��
		case ID_PARA_sinou_amari_ribbon:				//���܂�
			bit=1;
			ret=((ppp1->sinou_ribbon&(bit<<id-ID_PARA_sinou_champ_ribbon))!=0);
			break;
//PARAM2
		case ID_PARA_waza1:
		case ID_PARA_waza2:
		case ID_PARA_waza3:
		case ID_PARA_waza4:
			ret=ppp2->waza[id-ID_PARA_waza1];
			break;
		case ID_PARA_pp1:
		case ID_PARA_pp2:
		case ID_PARA_pp3:
		case ID_PARA_pp4:
			ret=ppp2->pp[id-ID_PARA_pp1];
			break;
		case ID_PARA_pp_count1:
		case ID_PARA_pp_count2:
		case ID_PARA_pp_count3:
		case ID_PARA_pp_count4:
			ret=ppp2->pp_count[id-ID_PARA_pp_count1];
			break;
		case ID_PARA_pp_max1:
		case ID_PARA_pp_max2:
		case ID_PARA_pp_max3:
		case ID_PARA_pp_max4:
			ret=WT_PPMaxGet(ppp2->waza[id-ID_PARA_pp_max1],ppp2->pp_count[id-ID_PARA_pp_max1]);
			break;
		case ID_PARA_hp_rnd:
			ret=ppp2->hp_rnd;
			break;
		case ID_PARA_pow_rnd:
			ret=ppp2->pow_rnd;
			break;
		case ID_PARA_def_rnd:
			ret=ppp2->def_rnd;
			break;
		case ID_PARA_agi_rnd:
			ret=ppp2->agi_rnd;
			break;
		case ID_PARA_spepow_rnd:
			ret=ppp2->spepow_rnd;
			break;
		case ID_PARA_spedef_rnd:
			ret=ppp2->spedef_rnd;
			break;
		case ID_PARA_tamago_flag:
			if(ppp->fusei_tamago_flag){
				ret=ppp->fusei_tamago_flag;
			}
			else{
				ret=ppp2->tamago_flag;
			}
			break;
		case ID_PARA_nickname_flag:
			ret=ppp2->nickname_flag;
			break;
		case ID_PARA_stylemedal_normal:
		case ID_PARA_stylemedal_super:
		case ID_PARA_stylemedal_hyper:
		case ID_PARA_stylemedal_master:
		case ID_PARA_beautifulmedal_normal:
		case ID_PARA_beautifulmedal_super:
		case ID_PARA_beautifulmedal_hyper:
		case ID_PARA_beautifulmedal_master:
		case ID_PARA_cutemedal_normal:
		case ID_PARA_cutemedal_super:
		case ID_PARA_cutemedal_hyper:
		case ID_PARA_cutemedal_master:
		case ID_PARA_clevermedal_normal:
		case ID_PARA_clevermedal_super:
		case ID_PARA_clevermedal_hyper:
		case ID_PARA_clevermedal_master:
		case ID_PARA_strongmedal_normal:
		case ID_PARA_strongmedal_super:
		case ID_PARA_strongmedal_hyper:
		case ID_PARA_strongmedal_master:
		case ID_PARA_champ_ribbon:
		case ID_PARA_winning_ribbon:
		case ID_PARA_victory_ribbon:
		case ID_PARA_bromide_ribbon:
		case ID_PARA_ganba_ribbon:
		case ID_PARA_marine_ribbon:
		case ID_PARA_land_ribbon:
		case ID_PARA_sky_ribbon:
		case ID_PARA_country_ribbon:
		case ID_PARA_national_ribbon:
		case ID_PARA_earth_ribbon:
		case ID_PARA_world_ribbon:
			bit=1;
			ret=((ppp2->old_ribbon&(bit<<id-ID_PARA_stylemedal_normal))!=0);
			break;
		case ID_PARA_event_get_flag:
			ret=ppp2->event_get_flag;
			break;
		case ID_PARA_sex:
			ret=ppp2->sex;
			break;
		case ID_PARA_form_no:
			ret=ppp2->form_no;
			break;
		case ID_PARA_dummy_p2_1:
			ret=ppp2->dummy_p2_1;
			break;
		case ID_PARA_dummy_p2_2:
			ret=ppp2->dummy_p2_2;
			break;
//PARAM3
		case ID_PARA_nickname:
			if(ppp->fusei_tamago_flag){
				MSGDAT_MonsNameGet(MONSNO_DAMETAMAGO,HEAPID_BASE_SYSTEM,buf);
			}
			else{
				{
					u16	*buf16=buf;

					for(ret=0;ret<MONS_NAME_SIZE;ret++){
						buf16[ret]=ppp3->nickname[ret];
					}
					buf16[ret]=EOM_;
				}
			}
			break;
		case ID_PARA_nickname_buf_flag:
			ret=ppp2->nickname_flag;
		case ID_PARA_nickname_buf:
			if(ppp->fusei_tamago_flag){
				STRBUF*  default_monsname = MSGDAT_UTIL_GetMonsName(MONSNO_DAMETAMAGO, HEAPID_BASE_SYSTEM);
				STRBUF_Copy((STRBUF*)buf, default_monsname);
				STRBUF_Delete(default_monsname);
			}
			else{
				STRBUF_SetStringCode((STRBUF*)buf, ppp3->nickname);
			}
#if 0
			if( ppp2->nickname_flag )
			{
				STRBUF_SetStringCode((STRBUF*)buf, ppp3->nickname);
			}
			else
			{
				STRBUF*  default_monsname = MSGDAT_UTIL_GetMonsName(ppp1->monsno, HEAPID_BASE_SYSTEM);
				STRBUF_Copy((STRBUF*)buf, default_monsname);
				STRBUF_Delete(default_monsname);
			}
#endif
			break;

		case ID_PARA_pref_code:
			ret=ppp3->pref_code;
			break;
		case ID_PARA_get_cassette:
			ret=ppp3->get_cassette;
			break;
		case ID_PARA_trial_stylemedal_normal:
		case ID_PARA_trial_stylemedal_super:
		case ID_PARA_trial_stylemedal_hyper:
		case ID_PARA_trial_stylemedal_master:
		case ID_PARA_trial_beautifulmedal_normal:
		case ID_PARA_trial_beautifulmedal_super:
		case ID_PARA_trial_beautifulmedal_hyper:
		case ID_PARA_trial_beautifulmedal_master:
		case ID_PARA_trial_cutemedal_normal:
		case ID_PARA_trial_cutemedal_super:
		case ID_PARA_trial_cutemedal_hyper:
		case ID_PARA_trial_cutemedal_master:
		case ID_PARA_trial_clevermedal_normal:
		case ID_PARA_trial_clevermedal_super:
		case ID_PARA_trial_clevermedal_hyper:
		case ID_PARA_trial_clevermedal_master:
		case ID_PARA_trial_strongmedal_normal:
		case ID_PARA_trial_strongmedal_super:
		case ID_PARA_trial_strongmedal_hyper:
		case ID_PARA_trial_strongmedal_master:
		case ID_PARA_amari_ribbon:
			bit=1;
			ret=((ppp3->new_ribbon&(bit<<id-ID_PARA_trial_stylemedal_normal))!=0);
			break;
//PARAM4
		case ID_PARA_oyaname:
		{
			u16 *buf16=buf;
			for(ret=0;ret<PERSON_NAME_SIZE;ret++){
				buf16[ret]=ppp4->oyaname[ret];
			}
			buf16[ret]=EOM_;
			break;
		}

		case ID_PARA_oyaname_buf:
			STRBUF_SetStringCode((STRBUF*)buf, ppp4->oyaname);
			break;

		case ID_PARA_get_year:							//�߂܂����N
			ret=ppp4->get_year;							//�߂܂����N
			break;
		case ID_PARA_get_month:							//�߂܂�����
			ret=ppp4->get_month;							//�߂܂�����
			break;
		case ID_PARA_get_day:							//�߂܂�����
			ret=ppp4->get_day;							//�߂܂�����
			break;
		case ID_PARA_birth_year:						//���܂ꂽ�N
			ret=ppp4->birth_year;						//���܂ꂽ�N
			break;
		case ID_PARA_birth_month:						//���܂ꂽ��
			ret=ppp4->birth_month;						//���܂ꂽ��
			break;
		case ID_PARA_birth_day:							//���܂ꂽ��
			ret=ppp4->birth_day;							//���܂ꂽ��
			break;
		case ID_PARA_get_place:							//�߂܂����ꏊ
			ret=ppp4->get_place;							//�߂܂����ꏊ
			break;
		case ID_PARA_birth_place:						//���܂ꂽ�ꏊ
			ret=ppp4->birth_place;						//���܂ꂽ�ꏊ
			break;
		case ID_PARA_pokerus:							//�|�P���X
			ret=ppp4->pokerus;							//�|�P���X
			break;
		case ID_PARA_get_ball:							//�߂܂����{�[��
			ret=ppp4->get_ball;							//�߂܂����{�[��
			break;
		case ID_PARA_get_level:							//�߂܂������x��
			ret=ppp4->get_level;							//�߂܂������x��
			break;
		case ID_PARA_oyasex:							//�e�̐���
			ret=ppp4->oyasex;							//�e�̐���
			break;
		case ID_PARA_get_ground_id:						//�߂܂����ꏊ�̒n�`�A�g���r���[�g�i�~�m�b�`�p�j
			ret=ppp4->get_ground_id;						//�߂܂����ꏊ�̒n�`�A�g���r���[�g�i�~�m�b�`�p�j
			break;
		case ID_PARA_dummy_p4_1:						//���܂�
			ret=ppp4->dummy_p4_1;						//���܂�
			break;

		case ID_PARA_power_rnd:
			ret=(ppp2->hp_rnd		<< 0)|
				(ppp2->pow_rnd		<< 5)|
				(ppp2->def_rnd		<<10)|
				(ppp2->agi_rnd		<<15)|
				(ppp2->spepow_rnd	<<20)|
				(ppp2->spedef_rnd	<<25);
			break;
		//�����X�^�[�i���o�[���j�h�����̎���nickname_flag�������Ă��邩�`�F�b�N
		case ID_PARA_nidoran_nickname:
			if(((ppp1->monsno==MONSNO_NIDORAN_F)||(ppp1->monsno==MONSNO_NIDORAN_M))&&(ppp2->nickname_flag==0)){
				ret=FALSE;
			}
			else{
				ret=TRUE;
			}
			break;
		case ID_PARA_type1:
		case ID_PARA_type2:
			if((ppp1->monsno==MONSNO_AUSU)&&(ppp1->speabino==TOKUSYU_MARUTITAIPU)){
				ret=AusuTypeGet(ItemParamGet(ppp1->item,ITEM_PRM_EQUIP,HEAPID_BASE_SYSTEM));
			}
			else{
				ret=PokeFormNoPersonalParaGet(ppp1->monsno,ppp2->form_no,ID_PER_type1+(id-ID_PARA_type1));
			}
			break;
		case ID_PARA_default_name:						//�|�P�����̃f�t�H���g��
			MSGDAT_MonsNameGet(ppp1->monsno,HEAPID_BASE_SYSTEM,buf);
			break;
	}

	return	ret;
}

//============================================================================================
/**
 *	�|�P�����p�����[�^�\���̂ɔC�ӂŒl���i�[�i�Í��^�����^�`�F�b�N�T���`�F�b�N����j
 *
 * @param[in]	pp	�i�[�������|�P�����p�����[�^�\���̂̃|�C���^
 * @param[in]	id	�i�[�������f�[�^�̃C���f�b�N�X�ipoke_tool.h�ɒ�`�j
 * @param[in]	buf	�i�[�������f�[�^�̃|�C���^
 */
//============================================================================================
void	PokeParaPut(POKEMON_PARAM *pp,int id,const void *buf)
{
	u16	sum;

//�A�T�[�g���o�����߂ɌĂѕ����Ă������̂Ȃ���
//	GF_ASSERT_MSG(pp->ppp.pp_fast_mode==0,"���������[�h�̂܂܂ɂȂ��Ă܂�\n");

	if(pp->ppp.pp_fast_mode==0){
		PokeParaDecoded(&pp->pcp,sizeof(POKEMON_CALC_PARAM),pp->ppp.personal_rnd);
		PokeParaDecoded(&pp->ppp.paradata,sizeof(POKEMON_PASO_PARAM1)*4,pp->ppp.checksum);
		sum=PokeParaCheckSum(&pp->ppp.paradata,sizeof(POKEMON_PASO_PARAM1)*4);
		//�s���ȃf�[�^�̎��͏������݂����Ȃ�
		if(sum!=pp->ppp.checksum){
			GF_ASSERT_MSG((sum==pp->ppp.checksum),"checksum Crash!\n");
			pp->ppp.fusei_tamago_flag=1;
			PokeParaCoded(pp->ppp.paradata,sizeof(POKEMON_PASO_PARAM1)*4,pp->ppp.checksum);
			return;
		}
	}

	PokeParaPutAct(pp,id,buf);

	if(pp->ppp.pp_fast_mode==0){
		PokeParaCoded(&pp->pcp,sizeof(POKEMON_CALC_PARAM),pp->ppp.personal_rnd);
		pp->ppp.checksum=PokeParaCheckSum(&pp->ppp.paradata,sizeof(POKEMON_PASO_PARAM1)*4);
		PokeParaCoded(&pp->ppp.paradata,sizeof(POKEMON_PASO_PARAM1)*4,pp->ppp.checksum);
	}
}

//�A�T�[�g���o�����߂ɌĂѕ����Ă������ǁAPokeParaPut�ɓ���
#if 0
//============================================================================================
/**
 *	�|�P�����p�����[�^�\���̂ɔC�ӂŒl���i�[�i���������[�h�j
 *
 * @param[in]	pp	�i�[�������|�P�����p�����[�^�\���̂̃|�C���^
 * @param[in]	id	�i�[�������f�[�^�̃C���f�b�N�X�ipoke_tool.h�ɒ�`�j
 * @param[in]	buf	�i�[�������f�[�^�̃|�C���^
 */
//============================================================================================
void	PokeParaPutFast(POKEMON_PARAM *pp,int id,const void *buf)
{
	u16	sum;

	GF_ASSERT_MSG(pp->ppp.pp_fast_mode==1,"���������[�h�ł͂Ȃ��̂ɌĂ΂�Ă��܂�\n");

	PokeParaPutAct(pp,id,buf);
}
#endif

//============================================================================================
/**
 *	�|�P�����p�����[�^�\���̂ɔC�ӂŒl���i�[
 *
 * @param[in]	pp	�i�[�������|�P�����p�����[�^�\���̂̃|�C���^
 * @param[in]	id	�i�[�������f�[�^�̃C���f�b�N�X�ipoke_tool.h�ɒ�`�j
 * @param[in]	buf	�i�[�������f�[�^�̃|�C���^
 */
//============================================================================================
static	void	PokeParaPutAct(POKEMON_PARAM *pp,int id,const void *buf)
{
	u32	*buf32=(u32 *)buf;
	u16	*buf16=(u16 *)buf;
	u8	*buf8=(u8 *)buf;

	switch(id){
	case ID_PARA_condition:
		pp->pcp.condition=buf32[0];
		break;
	case ID_PARA_level:
		pp->pcp.level=buf8[0];
		break;
	case ID_PARA_cb_id:
		pp->pcp.cb_id=buf8[0];	
		break;
	case ID_PARA_hp:
		pp->pcp.hp=buf16[0];
		break;
	case ID_PARA_hpmax:
		pp->pcp.hpmax=buf16[0];
		break;
	case ID_PARA_pow:
		pp->pcp.pow=buf16[0];
		break;
	case ID_PARA_def:
		pp->pcp.def=buf16[0];
		break;
	case ID_PARA_agi:
		pp->pcp.agi=buf16[0];
		break;
	case ID_PARA_spepow:
		pp->pcp.spepow=buf16[0];
		break;
	case ID_PARA_spedef:
		pp->pcp.spedef=buf16[0];
		break;
	case ID_PARA_mail_data:
		MailData_Copy((MAIL_DATA *)buf,&pp->pcp.mail_data);
		break;
	case ID_PARA_cb_core:
		CB_Tool_CoreData_Copy((CB_CORE *)buf,&pp->pcp.cb_core);
		break;
	default:
		PokePasoParaPutAct((POKEMON_PASO_PARAM *)&pp->ppp,id,buf);
		break;
	}
}

//============================================================================================
/**
 *	�{�b�N�X�|�P�����p�����[�^�\���̂ɔC�ӂŒl���i�[�i�Í��^�����^�`�F�b�N�T���`�F�b�N����j
 *
 * @param[in]	ppp	�i�[�������{�b�N�X�|�P�����p�����[�^�\���̂̃|�C���^
 * @param[in]	id	�i�[�������f�[�^�̃C���f�b�N�X�ipoke_tool.h�ɒ�`�j
 * @param[in]	buf	�i�[�������f�[�^�̃|�C���^
 */
//============================================================================================
void	PokePasoParaPut(POKEMON_PASO_PARAM *ppp,int id,const void *buf)
{
	u16	sum;

//�A�T�[�g���o�����߂ɌĂѕ����Ă������̂Ȃ���
//	GF_ASSERT_MSG(ppp->ppp_fast_mode==0,"���������[�h�̂܂܂ɂȂ��Ă܂�\n");

	if(ppp->ppp_fast_mode==0){
		PokeParaDecoded(ppp->paradata,sizeof(POKEMON_PASO_PARAM1)*4,ppp->checksum);
		sum=PokeParaCheckSum(ppp->paradata,sizeof(POKEMON_PASO_PARAM1)*4);
		//�s���ȃf�[�^�̎��͏������݂����Ȃ�
		if(sum!=ppp->checksum){
			GF_ASSERT_MSG((sum==ppp->checksum),"checksum Crash!\n");
			ppp->fusei_tamago_flag=1;
			PokeParaCoded(ppp->paradata,sizeof(POKEMON_PASO_PARAM1)*4,ppp->checksum);
			return;
		}
	}

	PokePasoParaPutAct(ppp,id,buf);

	if(ppp->ppp_fast_mode==0){
		ppp->checksum=PokeParaCheckSum(ppp->paradata,sizeof(POKEMON_PASO_PARAM1)*4);
		PokeParaCoded(ppp->paradata,sizeof(POKEMON_PASO_PARAM1)*4,ppp->checksum);
	}
}

//�A�T�[�g���o�����߂ɌĂѕ����Ă������ǁAPokePasoParaPut�ɓ���
#if 0
//============================================================================================
/**
 *	�{�b�N�X�|�P�����p�����[�^�\���̂ɔC�ӂŒl���i�[�i���������[�h�j
 *
 * @param[in]	ppp	�i�[�������{�b�N�X�|�P�����p�����[�^�\���̂̃|�C���^
 * @param[in]	id	�i�[�������f�[�^�̃C���f�b�N�X�ipoke_tool.h�ɒ�`�j
 * @param[in]	buf	�i�[�������f�[�^�̃|�C���^
 */
//============================================================================================
void	PokePasoParaPutFast(POKEMON_PASO_PARAM *ppp,int id,const void *buf)
{
	u16	sum;

	GF_ASSERT_MSG(ppp->ppp_fast_mode==1,"���������[�h�ł͂Ȃ��̂ɌĂ΂�Ă��܂�\n");

	PokePasoParaPutAct(ppp,id,buf);
}
#endif

//============================================================================================
/**
 *	�{�b�N�X�|�P�����p�����[�^�\���̂ɔC�ӂŒl���i�[
 *
 * @param[in]	ppp	�i�[�������{�b�N�X�|�P�����p�����[�^�\���̂̃|�C���^
 * @param[in]	id	�i�[�������f�[�^�̃C���f�b�N�X�ipoke_tool.h�ɒ�`�j
 * @param[in]	buf	�i�[�������f�[�^�̃|�C���^
 */
//============================================================================================
static	void	PokePasoParaPutAct(POKEMON_PASO_PARAM *ppp,int id,const void *buf)
{
	int	i;
	u64	bit;
	u16	sum;
	u32	*buf32=(u32 *)buf;
	u16	*buf16=(u16 *)buf;
	u8	*buf8=(u8 *)buf;
	POKEMON_PASO_PARAM1	*ppp1;
	POKEMON_PASO_PARAM2	*ppp2;
	POKEMON_PASO_PARAM3	*ppp3;
	POKEMON_PASO_PARAM4	*ppp4;

	ppp1=(POKEMON_PASO_PARAM1 *)PokeParaAdrsGet(ppp,ppp->personal_rnd,ID_POKEPARA1);
	ppp2=(POKEMON_PASO_PARAM2 *)PokeParaAdrsGet(ppp,ppp->personal_rnd,ID_POKEPARA2);
	ppp3=(POKEMON_PASO_PARAM3 *)PokeParaAdrsGet(ppp,ppp->personal_rnd,ID_POKEPARA3);
	ppp4=(POKEMON_PASO_PARAM4 *)PokeParaAdrsGet(ppp,ppp->personal_rnd,ID_POKEPARA4);

	switch(id){
//PARAM
		case ID_PARA_personal_rnd:
			ppp->personal_rnd=buf32[0];
			break;
		case ID_PARA_pp_fast_mode:
			GF_ASSERT_MSG((0),"fast_mode�֕s���ȏ�������\n");
			ppp->pp_fast_mode=buf8[0];
			break;
		case ID_PARA_ppp_fast_mode:
			GF_ASSERT_MSG((0),"fast_mode�֕s���ȏ�������\n");
			ppp->ppp_fast_mode=buf8[0];
			break;
		case ID_PARA_fusei_tamago_flag:
			ppp->fusei_tamago_flag=buf8[0];
			break;
		case ID_PARA_checksum:
			ppp->checksum=buf16[0];
			break;
//PARAM1
		case ID_PARA_monsno:
			ppp1->monsno=buf16[0];
			break;
		case ID_PARA_item:
			ppp1->item=buf16[0];
			break;
		case ID_PARA_id_no:
			ppp1->id_no=buf32[0];
			break;
		case ID_PARA_exp:
			ppp1->exp=buf32[0];
			break;
		case ID_PARA_friend:
			ppp1->friend=buf8[0];
			break;
		case ID_PARA_speabino:
			ppp1->speabino=buf8[0];
			break;
		case ID_PARA_mark:
			ppp1->mark=buf8[0];		
			break;
		case ID_PARA_country_code:
			ppp1->country_code=buf8[0];		
			break;
		case ID_PARA_hp_exp:
			ppp1->hp_exp=buf8[0];
			break;
		case ID_PARA_pow_exp:
			ppp1->pow_exp=buf8[0];
			break;
		case ID_PARA_def_exp:
			ppp1->def_exp=buf8[0];
			break;
		case ID_PARA_agi_exp:
			ppp1->agi_exp=buf8[0];
			break;
		case ID_PARA_spepow_exp:
			ppp1->spepow_exp=buf8[0];
			break;
		case ID_PARA_spedef_exp:
			ppp1->spedef_exp=buf8[0];
			break;
		case ID_PARA_style:
			ppp1->style=buf8[0];
			break;
		case ID_PARA_beautiful:
			ppp1->beautiful=buf8[0];
			break;
		case ID_PARA_cute:
			ppp1->cute=buf8[0];
			break;
		case ID_PARA_clever:
			ppp1->clever=buf8[0];
			break;
		case ID_PARA_strong:
			ppp1->strong=buf8[0];	
			break;
		case ID_PARA_fur:
			ppp1->fur=buf8[0];		
			break;
		case ID_PARA_sinou_champ_ribbon:				//�V���I�E�`�����v���{��
		case ID_PARA_sinou_battle_tower_ttwin_first:	//�V���I�E�o�g���^���[�^���[�^�C�N�[������1���
		case ID_PARA_sinou_battle_tower_ttwin_second:	//�V���I�E�o�g���^���[�^���[�^�C�N�[������2���
		case ID_PARA_sinou_battle_tower_2vs2_win50:		//�V���I�E�o�g���^���[�^���[�_�u��50�A��
		case ID_PARA_sinou_battle_tower_aimulti_win50:	//�V���I�E�o�g���^���[�^���[AI�}���`50�A��
		case ID_PARA_sinou_battle_tower_siomulti_win50:	//�V���I�E�o�g���^���[�^���[�ʐM�}���`50�A��
		case ID_PARA_sinou_battle_tower_wifi_rank5:		//�V���I�E�o�g���^���[Wifi�����N�T����
		case ID_PARA_sinou_syakki_ribbon:				//�V���I�E����������{��
		case ID_PARA_sinou_dokki_ribbon:				//�V���I�E�ǂ������{��
		case ID_PARA_sinou_syonbo_ribbon:				//�V���I�E�����ڃ��{��
		case ID_PARA_sinou_ukka_ribbon:					//�V���I�E���������{��
		case ID_PARA_sinou_sukki_ribbon:				//�V���I�E���������{��
		case ID_PARA_sinou_gussu_ribbon:				//�V���I�E���������{��
		case ID_PARA_sinou_nikko_ribbon:				//�V���I�E�ɂ������{��
		case ID_PARA_sinou_gorgeous_ribbon:				//�V���I�E�S�[�W���X���{��
		case ID_PARA_sinou_royal_ribbon:				//�V���I�E���C�������{��
		case ID_PARA_sinou_gorgeousroyal_ribbon:		//�V���I�E�S�[�W���X���C�������{��
		case ID_PARA_sinou_ashiato_ribbon:				//�V���I�E�������ƃ��{��
		case ID_PARA_sinou_record_ribbon:				//�V���I�E���R�[�h���{��
		case ID_PARA_sinou_history_ribbon:				//�V���I�E�q�X�g���[���{��
		case ID_PARA_sinou_legend_ribbon:				//�V���I�E���W�F���h���{��
		case ID_PARA_sinou_red_ribbon:					//�V���I�E���b�h���{��
		case ID_PARA_sinou_green_ribbon:				//�V���I�E�O���[�����{��
		case ID_PARA_sinou_blue_ribbon:					//�V���I�E�u���[���{��
		case ID_PARA_sinou_festival_ribbon:				//�V���I�E�t�F�X�e�B�o�����{��
		case ID_PARA_sinou_carnival_ribbon:				//�V���I�E�J�[�j�o�����{��
		case ID_PARA_sinou_classic_ribbon:				//�V���I�E�N���V�b�N���{��
		case ID_PARA_sinou_premiere_ribbon:				//�V���I�E�v���~�A���{��
		case ID_PARA_sinou_amari_ribbon:				//���܂�
			bit=buf8[0];
			bit=bit<<(id-ID_PARA_sinou_champ_ribbon);
			if(buf8[0]){
				ppp1->sinou_ribbon|=bit;
			}
			else{
				ppp1->sinou_ribbon&=(bit^0xffffffff);
			}
			break;
//PARAM2
		case ID_PARA_waza1:
		case ID_PARA_waza2:
		case ID_PARA_waza3:
		case ID_PARA_waza4:
			ppp2->waza[id-ID_PARA_waza1]=buf16[0];
			break;
		case ID_PARA_pp1:
		case ID_PARA_pp2:
		case ID_PARA_pp3:
		case ID_PARA_pp4:
			ppp2->pp[id-ID_PARA_pp1]=buf8[0];
			break;
		case ID_PARA_pp_count1:
		case ID_PARA_pp_count2:
		case ID_PARA_pp_count3:
		case ID_PARA_pp_count4:
			ppp2->pp_count[id-ID_PARA_pp_count1]=buf8[0];
			break;
		case ID_PARA_pp_max1:
		case ID_PARA_pp_max2:
		case ID_PARA_pp_max3:
		case ID_PARA_pp_max4:
			OS_Printf("�s���ȏ�������\n");
			break;
		case ID_PARA_hp_rnd:
			ppp2->hp_rnd=buf8[0];
			break;
		case ID_PARA_pow_rnd:
			ppp2->pow_rnd=buf8[0];
			break;
		case ID_PARA_def_rnd:
			ppp2->def_rnd=buf8[0];
			break;
		case ID_PARA_agi_rnd:
			ppp2->agi_rnd=buf8[0];
			break;
		case ID_PARA_spepow_rnd:
			ppp2->spepow_rnd=buf8[0];
			break;
		case ID_PARA_spedef_rnd:
			ppp2->spedef_rnd=buf8[0];
			break;
		case ID_PARA_tamago_flag:
			ppp2->tamago_flag=buf8[0];
			break;
		case ID_PARA_nickname_flag:
			ppp2->nickname_flag=buf8[0];
			break;
		case ID_PARA_stylemedal_normal:
		case ID_PARA_stylemedal_super:
		case ID_PARA_stylemedal_hyper:
		case ID_PARA_stylemedal_master:
		case ID_PARA_beautifulmedal_normal:
		case ID_PARA_beautifulmedal_super:
		case ID_PARA_beautifulmedal_hyper:
		case ID_PARA_beautifulmedal_master:
		case ID_PARA_cutemedal_normal:
		case ID_PARA_cutemedal_super:
		case ID_PARA_cutemedal_hyper:
		case ID_PARA_cutemedal_master:
		case ID_PARA_clevermedal_normal:
		case ID_PARA_clevermedal_super:
		case ID_PARA_clevermedal_hyper:
		case ID_PARA_clevermedal_master:
		case ID_PARA_strongmedal_normal:
		case ID_PARA_strongmedal_super:
		case ID_PARA_strongmedal_hyper:
		case ID_PARA_strongmedal_master:
		case ID_PARA_champ_ribbon:
		case ID_PARA_winning_ribbon:
		case ID_PARA_victory_ribbon:
		case ID_PARA_bromide_ribbon:
		case ID_PARA_ganba_ribbon:
		case ID_PARA_marine_ribbon:
		case ID_PARA_land_ribbon:
		case ID_PARA_sky_ribbon:
		case ID_PARA_country_ribbon:
		case ID_PARA_national_ribbon:
		case ID_PARA_earth_ribbon:
		case ID_PARA_world_ribbon:
			bit=buf8[0];
			bit=bit<<(id-ID_PARA_stylemedal_normal);
			if(buf8[0]){
				ppp2->old_ribbon|=bit;
			}
			else{
				ppp2->old_ribbon&=(bit^0xffffffff);
			}
			break;
		case ID_PARA_event_get_flag:
			ppp2->event_get_flag=buf8[0];
			break;
		case ID_PARA_sex:
			ppp2->sex=buf8[0];
			break;
		case ID_PARA_form_no:
			ppp2->form_no=buf8[0];
			break;
		case ID_PARA_dummy_p2_1:
			ppp2->dummy_p2_1=buf8[0];
			break;
		case ID_PARA_dummy_p2_2:
			ppp2->dummy_p2_2=buf16[0];
			break;
//PARAM3
		case ID_PARA_nickname_code_flag:
			{
				STRCODE	def_name[MONS_NAME_SIZE+EOM_SIZE];

				//�f�t�H���g���Ɣ�r���āA�f�t�H���g����������A�j�b�N�l�[���t���O�𗎂Ƃ�
				//�C�O�ł��炫���|�P�����́A�j�b�N�l�[���̕ύX���s�Ȃ̂ŁA���R�[�h������K�v�͂Ȃ�
				MSGDAT_MonsNameGet(ppp1->monsno,HEAPID_BASE_SYSTEM,&def_name[0]);
				ppp2->nickname_flag=PM_strcmp(def_name,&buf16[0]);
			}
		case ID_PARA_nickname:
			for(i=0;i<NELEMS(ppp3->nickname);i++){
				ppp3->nickname[i]=buf16[i];
			}
			break;
		case ID_PARA_nickname_buf_flag:
			{
				STRCODE	def_name[MONS_NAME_SIZE+EOM_SIZE];
				STRCODE	buf_name[MONS_NAME_SIZE+EOM_SIZE];

				//�f�t�H���g���Ɣ�r���āA�f�t�H���g����������A�j�b�N�l�[���t���O�𗎂Ƃ�
				//�C�O�ł��炫���|�P�����́A�j�b�N�l�[���̕ύX���s�Ȃ̂ŁA���R�[�h������K�v�͂Ȃ�
				MSGDAT_MonsNameGet(ppp1->monsno,HEAPID_BASE_SYSTEM,&def_name[0]);
				STRBUF_GetStringCode((STRBUF*)buf, &buf_name[0], NELEMS(buf_name));
				ppp2->nickname_flag=PM_strcmp(def_name,buf_name);
			}
		case ID_PARA_nickname_buf:
			STRBUF_GetStringCode((STRBUF*)buf, ppp3->nickname, NELEMS(ppp3->nickname));
			break;
		case ID_PARA_pref_code:
			ppp3->pref_code=buf8[0];
			break;
		case ID_PARA_get_cassette:
			ppp3->get_cassette=buf8[0];
			break;
		case ID_PARA_trial_stylemedal_normal:
		case ID_PARA_trial_stylemedal_super:
		case ID_PARA_trial_stylemedal_hyper:
		case ID_PARA_trial_stylemedal_master:
		case ID_PARA_trial_beautifulmedal_normal:
		case ID_PARA_trial_beautifulmedal_super:
		case ID_PARA_trial_beautifulmedal_hyper:
		case ID_PARA_trial_beautifulmedal_master:
		case ID_PARA_trial_cutemedal_normal:
		case ID_PARA_trial_cutemedal_super:
		case ID_PARA_trial_cutemedal_hyper:
		case ID_PARA_trial_cutemedal_master:
		case ID_PARA_trial_clevermedal_normal:
		case ID_PARA_trial_clevermedal_super:
		case ID_PARA_trial_clevermedal_hyper:
		case ID_PARA_trial_clevermedal_master:
		case ID_PARA_trial_strongmedal_normal:
		case ID_PARA_trial_strongmedal_super:
		case ID_PARA_trial_strongmedal_hyper:
		case ID_PARA_trial_strongmedal_master:
		case ID_PARA_amari_ribbon:
			bit=buf8[0];
			bit=bit<<(id-ID_PARA_trial_stylemedal_normal);
			if(buf8[0]){
				ppp3->new_ribbon|=bit;
			}
			else{
				ppp3->new_ribbon&=(bit^0xffffffffffffffff);
			}
			break;
//PARAM4
		case ID_PARA_oyaname:
			for(i=0;i<NELEMS(ppp4->oyaname);i++)
				ppp4->oyaname[i]=buf16[i];
			break;
		case ID_PARA_oyaname_buf:
			STRBUF_GetStringCode((STRBUF*)buf, ppp4->oyaname, NELEMS(ppp4->oyaname));
			break;

		case ID_PARA_get_year:							//�߂܂����N
			ppp4->get_year=buf8[0];						//�߂܂����N
			break;
		case ID_PARA_get_month:							//�߂܂�����
			ppp4->get_month=buf8[0];					//�߂܂�����
			break;
		case ID_PARA_get_day:							//�߂܂�����
			ppp4->get_day=buf8[0];						//�߂܂�����
			break;
		case ID_PARA_birth_year:						//���܂ꂽ�N
			ppp4->birth_year=buf8[0];					//���܂ꂽ�N
			break;
		case ID_PARA_birth_month:						//���܂ꂽ��
			ppp4->birth_month=buf8[0];					//���܂ꂽ��
			break;
		case ID_PARA_birth_day:							//���܂ꂽ��
			ppp4->birth_day=buf8[0];					//���܂ꂽ��
			break;
		case ID_PARA_get_place:							//�߂܂����ꏊ
			ppp4->get_place=buf16[0];					//�߂܂����ꏊ
			break;
		case ID_PARA_birth_place:						//���܂ꂽ�ꏊ
			ppp4->birth_place=buf16[0];					//���܂ꂽ�ꏊ
			break;
		case ID_PARA_pokerus:							//�|�P���X
			ppp4->pokerus=buf8[0];						//�|�P���X
			break;
		case ID_PARA_get_ball:							//�߂܂����{�[��
			ppp4->get_ball=buf8[0];						//�߂܂����{�[��
			break;
		case ID_PARA_get_level:							//�߂܂������x��
			ppp4->get_level=buf8[0];					//�߂܂������x��
			break;
		case ID_PARA_oyasex:							//�e�̐���
			ppp4->oyasex=buf8[0];						//�e�̐���
			break;
		case ID_PARA_get_ground_id:						//�߂܂����ꏊ�̒n�`�A�g���r���[�g�i�~�m�b�`�p�j
			ppp4->get_ground_id=buf8[0];				//�߂܂����ꏊ�̒n�`�A�g���r���[�g�i�~�m�b�`�p�j
			break;
		case ID_PARA_dummy_p4_1:						//���܂�
			ppp4->dummy_p4_1=buf16[0];					//���܂�
			break;

		case ID_PARA_power_rnd:
			ppp2->hp_rnd	=(buf32[0]>> 0)&0x0000001f;
			ppp2->pow_rnd	=(buf32[0]>> 5)&0x0000001f;
			ppp2->def_rnd	=(buf32[0]>>10)&0x0000001f;
			ppp2->agi_rnd	=(buf32[0]>>15)&0x0000001f;
			ppp2->spepow_rnd=(buf32[0]>>20)&0x0000001f;
			ppp2->spedef_rnd=(buf32[0]>>25)&0x0000001f;
			break;
		//�����X�^�[�i���o�[���j�h�����̎���nickname_flag�������Ă��邩�`�F�b�N
		case ID_PARA_nidoran_nickname:
		case ID_PARA_type1:
		case ID_PARA_type2:
			OS_Printf("�s���ȏ�������\n");
			break;
		case ID_PARA_default_name:						//�|�P�����̃f�t�H���g��
			{
				STRBUF	*name_buf;

				name_buf=MSGDAT_UTIL_GetMonsName(ppp1->monsno, HEAPID_BASE_SYSTEM);
				STRBUF_GetStringCode(name_buf, ppp3->nickname, NELEMS(ppp3->nickname));
				STRBUF_Delete(name_buf);
			}
			break;
	}
}

//============================================================================================
/**
 *	�|�P�����p�����[�^�\���̂ɔC�ӂŒl�����Z�i�Í��^�����^�`�F�b�N�T���`�F�b�N����j
 *
 * @param[in]	pp		���Z�������|�P�����p�����[�^�\���̂̃|�C���^
 * @param[in]	id		���Z�������f�[�^�̃C���f�b�N�X�ipoke_tool.h�ɒ�`�j
 * @param[in]	value	���Z�������f�[�^�̃|�C���^
 */
//============================================================================================
void	PokeParaAdd(POKEMON_PARAM *pp,int id,int value)
{
	u16	sum;

//�A�T�[�g���o�����߂ɌĂѕ����Ă������̂Ȃ���
//	GF_ASSERT_MSG(pp->ppp.pp_fast_mode==0,"���������[�h�̂܂܂ɂȂ��Ă܂�\n");

	if(pp->ppp.pp_fast_mode==0){
		PokeParaDecoded(&pp->pcp,sizeof(POKEMON_CALC_PARAM),pp->ppp.personal_rnd);
		PokeParaDecoded(&pp->ppp.paradata,sizeof(POKEMON_PASO_PARAM1)*4,pp->ppp.checksum);
		sum=PokeParaCheckSum(&pp->ppp.paradata,sizeof(POKEMON_PASO_PARAM1)*4);
		//�s���ȃf�[�^�̎��͏������݂����Ȃ�
		if(sum!=pp->ppp.checksum){
			GF_ASSERT_MSG((sum==pp->ppp.checksum),"checksum Crash!\n");
			PokeParaCoded(pp->ppp.paradata,sizeof(POKEMON_PASO_PARAM1)*4,pp->ppp.checksum);
			return;
		}
	}

	PokeParaAddAct(pp,id,value);

	if(pp->ppp.pp_fast_mode==0){
		PokeParaCoded(&pp->pcp,sizeof(POKEMON_CALC_PARAM),pp->ppp.personal_rnd);
		pp->ppp.checksum=PokeParaCheckSum(&pp->ppp.paradata,sizeof(POKEMON_PASO_PARAM1)*4);
		PokeParaCoded(&pp->ppp.paradata,sizeof(POKEMON_PASO_PARAM1)*4,pp->ppp.checksum);
	}
}

//�A�T�[�g���o�����߂ɌĂѕ����Ă������ǁAPokeParaAdd�ɓ���
#if 0
//============================================================================================
/**
 *	�|�P�����p�����[�^�\���̂ɔC�ӂŒl�����Z�i���������[�h�j
 *
 * @param[in]	pp		���Z�������|�P�����p�����[�^�\���̂̃|�C���^
 * @param[in]	id		���Z�������f�[�^�̃C���f�b�N�X�ipoke_tool.h�ɒ�`�j
 * @param[in]	value	���Z�������f�[�^�̃|�C���^
 */
//============================================================================================
void	PokeParaAddFast(POKEMON_PARAM *pp,int id,int value)
{
	u16	sum;

	GF_ASSERT_MSG(pp->ppp.pp_fast_mode==1,"���������[�h�ł͂Ȃ��̂ɌĂ΂�Ă��܂�\n");

	PokeParaAddAct(pp,id,value);
}
#endif

//============================================================================================
/**
 *	�|�P�����p�����[�^�\���̂ɔC�ӂŒl�����Z
 *
 * @param[in]	pp		���Z�������|�P�����p�����[�^�\���̂̃|�C���^
 * @param[in]	id		���Z�������f�[�^�̃C���f�b�N�X�ipoke_tool.h�ɒ�`�j
 * @param[in]	value	���Z�������f�[�^�̃|�C���^
 */
//============================================================================================
static	void	PokeParaAddAct(POKEMON_PARAM *pp,int id,int value)
{
	switch(id){
		case ID_PARA_hp:
			if((pp->pcp.hp+value)>pp->pcp.hpmax){
				pp->pcp.hp=pp->pcp.hpmax;
			}
			else{
				pp->pcp.hp+=value;
			}
			break;
		case ID_PARA_condition:
		case ID_PARA_level:
		case ID_PARA_cb_id:
		case ID_PARA_hpmax:
		case ID_PARA_pow:
		case ID_PARA_def:
		case ID_PARA_agi:
		case ID_PARA_spepow:
		case ID_PARA_spedef:
		case ID_PARA_mail_data:
			GF_ASSERT_MSG((0),"Add�ł��Ȃ��p�����[�^�ł�\n");
			break;
		default:
			PokePasoParaAddAct((POKEMON_PASO_PARAM *)&pp->ppp,id,value);
			break;
	}
}

//============================================================================================
/**
 *	�{�b�N�X�|�P�����p�����[�^�\���̂ɔC�ӂŒl�����Z�i�Í��^�����^�`�F�b�N�T���`�F�b�N����j
 *
 * @param[in]	ppp		���Z�������{�b�N�X�|�P�����p�����[�^�\���̂̃|�C���^
 * @param[in]	id		���Z�������f�[�^�̃C���f�b�N�X�ipoke_tool.h�ɒ�`�j
 * @param[in]	value	���Z�������f�[�^�̃|�C���^
 */
//============================================================================================
void	PokePasoParaAdd(POKEMON_PASO_PARAM *ppp,int id,int value)
{
	u16	sum;

//�A�T�[�g���o�����߂ɌĂѕ����Ă������̂Ȃ���
//	GF_ASSERT_MSG(ppp->ppp_fast_mode==0,"���������[�h�̂܂܂ɂȂ��Ă܂�\n");

	if(ppp->ppp_fast_mode==0){
		PokeParaDecoded(ppp->paradata,sizeof(POKEMON_PASO_PARAM1)*4,ppp->checksum);
		sum=PokeParaCheckSum(ppp->paradata,sizeof(POKEMON_PASO_PARAM1)*4);
		//�s���ȃf�[�^�̎��͏������݂����Ȃ�
		if(sum!=ppp->checksum){
			GF_ASSERT_MSG((sum==ppp->checksum),"checksum Crash!\n");
			PokeParaCoded(ppp->paradata,sizeof(POKEMON_PASO_PARAM1)*4,ppp->checksum);
			return;
		}
	}

	PokePasoParaAddAct(ppp,id,value);

	if(ppp->ppp_fast_mode==0){
		ppp->checksum=PokeParaCheckSum(ppp->paradata,sizeof(POKEMON_PASO_PARAM1)*4);
		PokeParaCoded(ppp->paradata,sizeof(POKEMON_PASO_PARAM1)*4,ppp->checksum);
	}
}

//�A�T�[�g���o�����߂ɌĂѕ����Ă������ǁAPokePasoParaAdd�ɓ���
#if 0
//============================================================================================
/**
 *	�{�b�N�X�|�P�����p�����[�^�\���̂ɔC�ӂŒl�����Z�i���������[�h�j
 *
 * @param[in]	ppp		���Z�������{�b�N�X�|�P�����p�����[�^�\���̂̃|�C���^
 * @param[in]	id		���Z�������f�[�^�̃C���f�b�N�X�ipoke_tool.h�ɒ�`�j
 * @param[in]	value	���Z�������f�[�^�̃|�C���^
 */
//============================================================================================
void	PokePasoParaAddFast(POKEMON_PASO_PARAM *ppp,int id,int value)
{
	u16	sum;

	GF_ASSERT_MSG(ppp->ppp_fast_mode==1,"���������[�h�ł͂Ȃ��̂ɌĂ΂�Ă��܂�\n");

	PokePasoParaAddAct(ppp,id,value);
}
#endif

//============================================================================================
/**
 *	�{�b�N�X�|�P�����p�����[�^�\���̂ɔC�ӂŒl�����Z
 *
 * @param[in]	ppp		���Z�������{�b�N�X�|�P�����p�����[�^�\���̂̃|�C���^
 * @param[in]	id		���Z�������f�[�^�̃C���f�b�N�X�ipoke_tool.h�ɒ�`�j
 * @param[in]	value	���Z�������f�[�^�̃|�C���^
 */
//============================================================================================
static	void	PokePasoParaAddAct(POKEMON_PASO_PARAM *ppp,int id,int value)
{
	int	i;
	u16	sum;
	POKEMON_PASO_PARAM1	*ppp1;
	POKEMON_PASO_PARAM2	*ppp2;
	POKEMON_PASO_PARAM3	*ppp3;
	POKEMON_PASO_PARAM4	*ppp4;

	ppp1=(POKEMON_PASO_PARAM1 *)PokeParaAdrsGet(ppp,ppp->personal_rnd,ID_POKEPARA1);
	ppp2=(POKEMON_PASO_PARAM2 *)PokeParaAdrsGet(ppp,ppp->personal_rnd,ID_POKEPARA2);
	ppp3=(POKEMON_PASO_PARAM3 *)PokeParaAdrsGet(ppp,ppp->personal_rnd,ID_POKEPARA3);
	ppp4=(POKEMON_PASO_PARAM4 *)PokeParaAdrsGet(ppp,ppp->personal_rnd,ID_POKEPARA4);

	switch(id){
		case ID_PARA_exp:
			if((ppp1->exp+value)>PokeLevelExpGet(ppp1->monsno,POKE_LEVEL_MAX)){
				ppp1->exp=PokeLevelExpGet(ppp1->monsno,POKE_LEVEL_MAX);
			}
			else{
				ppp1->exp+=value;
			}
			break;
		case ID_PARA_friend:
			if((ppp1->friend+value)>FRIEND_MAX){
				ppp1->friend=FRIEND_MAX;
			}
			else{
				ppp1->friend+=value;
			}
			break;
		case ID_PARA_hp_exp:
			ppp1->hp_exp+=value;
			break;
		case ID_PARA_pow_exp:
			ppp1->pow_exp+=value;
			break;
		case ID_PARA_def_exp:
			ppp1->def_exp+=value;
			break;
		case ID_PARA_agi_exp:
			ppp1->agi_exp+=value;
			break;
		case ID_PARA_spepow_exp:
			ppp1->spepow_exp+=value;
			break;
		case ID_PARA_spedef_exp:
			ppp1->spedef_exp+=value;
			break;
		case ID_PARA_style:
			if((ppp1->style+value)>STYLE_MAX){
				ppp1->style=STYLE_MAX;
			}
			else{
				ppp1->style+=value;
			}
			break;
		case ID_PARA_beautiful:
			if((ppp1->beautiful+value)>BEAUTIFUL_MAX){
				ppp1->beautiful=BEAUTIFUL_MAX;
			}
			else{
				ppp1->beautiful+=value;
			}
			break;
		case ID_PARA_cute:
			if((ppp1->cute+value)>CUTE_MAX){
				ppp1->cute=CUTE_MAX;
			}
			else{
				ppp1->cute+=value;
			}
			break;
		case ID_PARA_clever:
			if((ppp1->clever+value)>CLEVER_MAX){
				ppp1->clever=CLEVER_MAX;
			}
			else{
				ppp1->clever+=value;
			}
			break;
		case ID_PARA_strong:
			if((ppp1->strong+value)>STRONG_MAX){
				ppp1->strong=STRONG_MAX;
			}
			else{
				ppp1->strong+=value;
			}
			break;
		case ID_PARA_fur:
			if((ppp1->fur+value)>FUR_MAX){
				ppp1->fur=FUR_MAX;
			}
			else{
				ppp1->fur+=value;
			}
			break;
		case ID_PARA_pp1:
		case ID_PARA_pp2:
		case ID_PARA_pp3:
		case ID_PARA_pp4:
			if((ppp2->pp[id-ID_PARA_pp1]+value)>WT_PPMaxGet(ppp2->waza[id-ID_PARA_pp1],ppp2->pp_count[id-ID_PARA_pp1])){
				ppp2->pp[id-ID_PARA_pp1]=WT_PPMaxGet(ppp2->waza[id-ID_PARA_pp1],ppp2->pp_count[id-ID_PARA_pp1]);
			}
			else{
				ppp2->pp[id-ID_PARA_pp1]+=value;
			}
			break;
		case ID_PARA_pp_count1:
		case ID_PARA_pp_count2:
		case ID_PARA_pp_count3:
		case ID_PARA_pp_count4:
			if((ppp2->pp_count[id-ID_PARA_pp_count1]+value)>PP_COUNT_MAX){
				ppp2->pp_count[id-ID_PARA_pp_count1]=PP_COUNT_MAX;
			}
			else{
				ppp2->pp_count[id-ID_PARA_pp_count1]+=value;
			}
			break;
		case ID_PARA_pp_max1:
		case ID_PARA_pp_max2:
		case ID_PARA_pp_max3:
		case ID_PARA_pp_max4:
			OS_Printf("�s���ȑ�������\n");
			break;
		case ID_PARA_hp_rnd:
			if((ppp2->hp_rnd+value)>POW_RND_MAX){
				ppp2->hp_rnd=POW_RND_MAX;
			}
			else{
				ppp2->hp_rnd+=value;
			}
			break;
		case ID_PARA_pow_rnd:
			if((ppp2->pow_rnd+value)>POW_RND_MAX){
				ppp2->pow_rnd=POW_RND_MAX;
			}
			else{
				ppp2->pow_rnd+=value;
			}
			break;
		case ID_PARA_def_rnd:
			if((ppp2->def_rnd+value)>POW_RND_MAX){
				ppp2->def_rnd=POW_RND_MAX;
			}
			else{
				ppp2->def_rnd+=value;
			}
			break;
		case ID_PARA_agi_rnd:
			if((ppp2->agi_rnd+value)>POW_RND_MAX){
				ppp2->agi_rnd=POW_RND_MAX;
			}
			else{
				ppp2->agi_rnd+=value;
			}
			break;
		case ID_PARA_spepow_rnd:
			if((ppp2->spepow_rnd+value)>POW_RND_MAX){
				ppp2->spepow_rnd=POW_RND_MAX;
			}
			else{
				ppp2->spepow_rnd+=value;
			}
			break;
		case ID_PARA_spedef_rnd:
			if((ppp2->spedef_rnd+value)>POW_RND_MAX){
				ppp2->spedef_rnd=POW_RND_MAX;
			}
			else{
				ppp2->spedef_rnd+=value;
			}
			break;
		case ID_PARA_personal_rnd:
		case ID_PARA_pp_fast_mode:
		case ID_PARA_ppp_fast_mode:
		case ID_PARA_checksum:
		case ID_PARA_monsno:
		case ID_PARA_item:
		case ID_PARA_id_no:
		case ID_PARA_speabino:
		case ID_PARA_mark:
		case ID_PARA_country_code:
		case ID_PARA_sinou_champ_ribbon:				//�V���I�E�`�����v���{��
		case ID_PARA_sinou_battle_tower_ttwin_first:	//�V���I�E�o�g���^���[�^���[�^�C�N�[������1���
		case ID_PARA_sinou_battle_tower_ttwin_second:	//�V���I�E�o�g���^���[�^���[�^�C�N�[������2���
		case ID_PARA_sinou_battle_tower_2vs2_win50:		//�V���I�E�o�g���^���[�^���[�_�u��50�A��
		case ID_PARA_sinou_battle_tower_aimulti_win50:	//�V���I�E�o�g���^���[�^���[AI�}���`50�A��
		case ID_PARA_sinou_battle_tower_siomulti_win50:	//�V���I�E�o�g���^���[�^���[�ʐM�}���`50�A��
		case ID_PARA_sinou_battle_tower_wifi_rank5:		//�V���I�E�o�g���^���[Wifi�����N�T����
		case ID_PARA_sinou_syakki_ribbon:				//�V���I�E����������{��
		case ID_PARA_sinou_dokki_ribbon:				//�V���I�E�ǂ������{��
		case ID_PARA_sinou_syonbo_ribbon:				//�V���I�E�����ڃ��{��
		case ID_PARA_sinou_ukka_ribbon:					//�V���I�E���������{��
		case ID_PARA_sinou_sukki_ribbon:				//�V���I�E���������{��
		case ID_PARA_sinou_gussu_ribbon:				//�V���I�E���������{��
		case ID_PARA_sinou_nikko_ribbon:				//�V���I�E�ɂ������{��
		case ID_PARA_sinou_gorgeous_ribbon:				//�V���I�E�S�[�W���X���{��
		case ID_PARA_sinou_royal_ribbon:				//�V���I�E���C�������{��
		case ID_PARA_sinou_gorgeousroyal_ribbon:		//�V���I�E�S�[�W���X���C�������{��
		case ID_PARA_sinou_ashiato_ribbon:				//�V���I�E�������ƃ��{��
		case ID_PARA_sinou_record_ribbon:				//�V���I�E���R�[�h���{��
		case ID_PARA_sinou_history_ribbon:				//�V���I�E�q�X�g���[���{��
		case ID_PARA_sinou_legend_ribbon:				//�V���I�E���W�F���h���{��
		case ID_PARA_sinou_red_ribbon:					//�V���I�E���b�h���{��
		case ID_PARA_sinou_green_ribbon:				//�V���I�E�O���[�����{��
		case ID_PARA_sinou_blue_ribbon:					//�V���I�E�u���[���{��
		case ID_PARA_sinou_festival_ribbon:				//�V���I�E�t�F�X�e�B�o�����{��
		case ID_PARA_sinou_carnival_ribbon:				//�V���I�E�J�[�j�o�����{��
		case ID_PARA_sinou_classic_ribbon:				//�V���I�E�N���V�b�N���{��
		case ID_PARA_sinou_premiere_ribbon:				//�V���I�E�v���~�A���{��
		case ID_PARA_sinou_amari_ribbon:				//���܂�
		case ID_PARA_waza1:
		case ID_PARA_waza2:
		case ID_PARA_waza3:
		case ID_PARA_waza4:
		case ID_PARA_tamago_flag:
		case ID_PARA_nickname_flag:
		case ID_PARA_stylemedal_normal:
		case ID_PARA_stylemedal_super:
		case ID_PARA_stylemedal_hyper:
		case ID_PARA_stylemedal_master:
		case ID_PARA_beautifulmedal_normal:
		case ID_PARA_beautifulmedal_super:
		case ID_PARA_beautifulmedal_hyper:
		case ID_PARA_beautifulmedal_master:
		case ID_PARA_cutemedal_normal:
		case ID_PARA_cutemedal_super:
		case ID_PARA_cutemedal_hyper:
		case ID_PARA_cutemedal_master:
		case ID_PARA_clevermedal_normal:
		case ID_PARA_clevermedal_super:
		case ID_PARA_clevermedal_hyper:
		case ID_PARA_clevermedal_master:
		case ID_PARA_strongmedal_normal:
		case ID_PARA_strongmedal_super:
		case ID_PARA_strongmedal_hyper:
		case ID_PARA_strongmedal_master:
		case ID_PARA_champ_ribbon:
		case ID_PARA_winning_ribbon:
		case ID_PARA_victory_ribbon:
		case ID_PARA_bromide_ribbon:
		case ID_PARA_ganba_ribbon:
		case ID_PARA_marine_ribbon:
		case ID_PARA_land_ribbon:
		case ID_PARA_sky_ribbon:
		case ID_PARA_country_ribbon:
		case ID_PARA_national_ribbon:
		case ID_PARA_earth_ribbon:
		case ID_PARA_world_ribbon:
		case ID_PARA_event_get_flag:
		case ID_PARA_sex:
		case ID_PARA_form_no:
		case ID_PARA_dummy_p2_1:
		case ID_PARA_dummy_p2_2:
		case ID_PARA_nickname:
		case ID_PARA_nickname_buf:
		case ID_PARA_nickname_buf_flag:
		case ID_PARA_pref_code:
		case ID_PARA_get_cassette:
		case ID_PARA_trial_stylemedal_normal:
		case ID_PARA_trial_stylemedal_super:
		case ID_PARA_trial_stylemedal_hyper:
		case ID_PARA_trial_stylemedal_master:
		case ID_PARA_trial_beautifulmedal_normal:
		case ID_PARA_trial_beautifulmedal_super:
		case ID_PARA_trial_beautifulmedal_hyper:
		case ID_PARA_trial_beautifulmedal_master:
		case ID_PARA_trial_cutemedal_normal:
		case ID_PARA_trial_cutemedal_super:
		case ID_PARA_trial_cutemedal_hyper:
		case ID_PARA_trial_cutemedal_master:
		case ID_PARA_trial_clevermedal_normal:
		case ID_PARA_trial_clevermedal_super:
		case ID_PARA_trial_clevermedal_hyper:
		case ID_PARA_trial_clevermedal_master:
		case ID_PARA_trial_strongmedal_normal:
		case ID_PARA_trial_strongmedal_super:
		case ID_PARA_trial_strongmedal_hyper:
		case ID_PARA_trial_strongmedal_master:
		case ID_PARA_amari_ribbon:
		case ID_PARA_oyaname:
		case ID_PARA_oyaname_buf:
		case ID_PARA_get_year:							//�߂܂����N
		case ID_PARA_get_month:							//�߂܂�����
		case ID_PARA_get_day:							//�߂܂�����
		case ID_PARA_birth_year:						//���܂ꂽ�N
		case ID_PARA_birth_month:						//���܂ꂽ��
		case ID_PARA_birth_day:							//���܂ꂽ��
		case ID_PARA_get_place:							//�߂܂����ꏊ
		case ID_PARA_birth_place:						//���܂ꂽ�ꏊ
		case ID_PARA_pokerus:							//�|�P���X
		case ID_PARA_get_ball:							//�߂܂����{�[��
		case ID_PARA_get_level:							//�߂܂������x��
		case ID_PARA_oyasex:							//�e�̐���
		case ID_PARA_get_ground_id:						//�߂܂����ꏊ�̒n�`�A�g���r���[�g�i�~�m�b�`�p�j
		case ID_PARA_dummy_p4_1:						//���܂�
		case ID_PARA_power_rnd:
		case ID_PARA_nidoran_nickname:
		case ID_PARA_type1:
		case ID_PARA_type2:
		case ID_PARA_default_name:						//�|�P�����̃f�t�H���g��
		default:
			GF_ASSERT_MSG((0),"�s���ȉ��Z\n");
			break;
	}
}

//==============================================================================
/**
 * �p�[�\�i���f�[�^�I�[�v��
 *
 * ���̊֐��ŃI�[�v�������f�[�^��PokePersonalPara_Get�Ŏ擾���܂�
 * PokePersonalPara_Close�ŉ��
 *
 * @param   mons_no		
 * @param   HeapID		
 *
 * @retval  POKEMON_PERSONAL_DATA *		
 */
//==============================================================================
POKEMON_PERSONAL_DATA *PokePersonalPara_Open( int mons_no, int HeapID )
{
	POKEMON_PERSONAL_DATA *ppd;
	
	ppd=sys_AllocMemory( HeapID, sizeof(POKEMON_PERSONAL_DATA) );
	PokePersonalDataGet(mons_no,ppd);
	
	return ppd;
}

//==============================================================================
/**
 * �p�[�\�i���f�[�^�擾
 *
 * PokePersonalPara_Open�Ŋ֐��ŏ������Ă���f�[�^���擾���܂�
 * PokePersonalPara_Close�ŉ��
 *
 * @param   ppd		
 * @param   para		
 *
 * @retval  u32		
 */
//==============================================================================
u32 PokePersonalPara_Get( POKEMON_PERSONAL_DATA *ppd, int para )
{
	u32 ret;

	GF_ASSERT( ppd );
	
	switch(para){
	case ID_PER_basic_hp:		//��{�g�o
		ret=ppd->basic_hp;
		break;
	case ID_PER_basic_pow:		//��{�U����
		ret=ppd->basic_pow;
		break;
	case ID_PER_basic_def:		//��{�h���
		ret=ppd->basic_def;
		break;
	case ID_PER_basic_agi:		//��{�f����
		ret=ppd->basic_agi;
		break;
	case ID_PER_basic_spepow:	//��{����U����
		ret=ppd->basic_spepow;
		break;
	case ID_PER_basic_spedef:	//��{����h���
		ret=ppd->basic_spedef;
		break;
	case ID_PER_type1:			//�����P
		ret=ppd->type1;
		break;
	case ID_PER_type2:			//�����Q
		ret=ppd->type2;
		break;
	case ID_PER_get_rate:		//�ߊl��
		ret=ppd->get_rate;
		break;
	case ID_PER_give_exp:		//���^�o���l
		ret=ppd->give_exp;
		break;
	case ID_PER_pains_hp:		//���^�w�͒l�g�o
		ret=ppd->pains_hp;
		break;
	case ID_PER_pains_pow:		//���^�w�͒l�U����
		ret=ppd->pains_pow;
		break;
	case ID_PER_pains_def:		//���^�w�͒l�h���
		ret=ppd->pains_def;
		break;
	case ID_PER_pains_agi:		//���^�w�͒l�f����
		ret=ppd->pains_agi;
		break;
	case ID_PER_pains_spepow:	//���^�w�͒l����U����
		ret=ppd->pains_spepow;
		break;
	case ID_PER_pains_spedef:	//���^�w�͒l����h���
		ret=ppd->pains_spedef;
		break;
	case ID_PER_item1:			//�A�C�e���P
		ret=ppd->item1;
		break;
	case ID_PER_item2:			//�A�C�e���Q
		ret=ppd->item2;
		break;
	case ID_PER_sex:			//���ʃx�N�g��
		ret=ppd->sex;
		break;
	case ID_PER_egg_birth:		//�^�}�S�̛z������
		ret=ppd->egg_birth;
		break;
	case ID_PER_friend:			//�Ȃ��x�����l
		ret=ppd->friend;
		break;
	case ID_PER_grow:			//�����Ȑ�����
		ret=ppd->grow;
		break;
	case ID_PER_egg_group1:		//���Â���O���[�v1
		ret=ppd->egg_group1;
		break;
	case ID_PER_egg_group2:		//���Â���O���[�v2
		ret=ppd->egg_group2;
		break;
	case ID_PER_speabi1:		//����\�͂P
		ret=ppd->speabi1;
		break;
	case ID_PER_speabi2:		//����\�͂Q
		ret=ppd->speabi2;
		break;
	case ID_PER_escape:			//�����闦
		ret=ppd->escape;
		break;
	case ID_PER_color:			//�F�i�}�ӂŎg�p�j
		ret=ppd->color;
		break;
	case ID_PER_reverse:		//���]�t���O
		ret=ppd->reverse;
		break;
	case ID_PER_machine1:		//�Z�}�V���t���O�P
		ret=ppd->machine1;
		break;
	case ID_PER_machine2:		//�Z�}�V���t���O�Q
		ret=ppd->machine2;
		break;
	case ID_PER_machine3:		//�Z�}�V���t���O�R
		ret=ppd->machine3;
		break;
	case ID_PER_machine4:		//�Z�}�V���t���O�S
		ret=ppd->machine4;
		break;
	}
	return ret;
}

//==============================================================================
/**
 * �p�[�\�i���f�[�^���
 *
 * PokePersonalPara_Open�Ŋm�ۂ�����������������܂�
 *
 * @param   ppd		
 *
 * @retval  none		
 */
//==============================================================================
void PokePersonalPara_Close( POKEMON_PERSONAL_DATA *ppd )
{
	GF_ASSERT( ppd );

	sys_FreeMemoryEz(ppd);
	
}

//============================================================================================
/**
 *	�|�P�����p�[�\�i���\���̃f�[�^����C�ӂŃf�[�^���擾
 *  �i�ꔭ�Ńf�[�^�����o�������Ƃ��Ɏg�p���Ă��������A
 *    �p�[�\�i���f�[�^������������o�������Ƃ���Open,Get,Close���������y���ł��j
 *  
 * @param[in]	pp		�擾������POKEMON_PARAM�\����
 * @param[in]	para	�擾�����f�[�^�̃C���f�b�N�X�ipoke_tool.h�ɒ�`�j
 *
 * @return	�擾�����f�[�^
 */
//============================================================================================
u32	PokeParaPersonalParaGet(POKEMON_PARAM *pp,int para)
{
	return PokePasoParaPersonalParaGet(&pp->ppp,para);
}

//============================================================================================
/**
 *	�|�P�����p�[�\�i���\���̃f�[�^����C�ӂŃf�[�^���擾
 *  �i�ꔭ�Ńf�[�^�����o�������Ƃ��Ɏg�p���Ă��������A
 *    �p�[�\�i���f�[�^������������o�������Ƃ���Open,Get,Close���������y���ł��j
 *  
 * @param[in]	ppp		�擾������POKEMON_PASO_PARAM�\����
 * @param[in]	para	�擾�����f�[�^�̃C���f�b�N�X�ipoke_tool.h�ɒ�`�j
 *
 * @return	�擾�����f�[�^
 */
//============================================================================================
u32	PokePasoParaPersonalParaGet(POKEMON_PASO_PARAM *ppp,int para)
{
	int	mons_no;
	int	form_no;
	int	flag;

	flag=PokePasoParaFastModeOn(ppp);

	mons_no=PokePasoParaGet(ppp,ID_PARA_monsno,NULL);
	form_no=PokePasoParaGet(ppp,ID_PARA_form_no,NULL);

	PokePasoParaFastModeOff(ppp,flag);

	return	PokeFormNoPersonalParaGet(mons_no,form_no,para);
}

//============================================================================================
/**
 *	�|�P�����p�[�\�i���\���̃f�[�^����C�ӂŃf�[�^���擾
 *  �i�ꔭ�Ńf�[�^�����o�������Ƃ��Ɏg�p���Ă��������A
 *    �p�[�\�i���f�[�^������������o�������Ƃ���Open,Get,Close���������y���ł��j
 *  
 * @param[in]	mons_no	�擾�������|�P�����i���o�[
 * @param[in]	form_no	�擾�������|�P�����̃t�H�����i���o�[
 * @param[in]	para	�擾�����f�[�^�̃C���f�b�N�X�ipoke_tool.h�ɒ�`�j
 *
 * @return	�擾�����f�[�^
 */
//============================================================================================
u32	PokeFormNoPersonalParaGet(int mons_no,int form_no,int para)
{
	u32	ret;
	POKEMON_PERSONAL_DATA *ppd;

	mons_no=PokeOtherFormMonsNoGet(mons_no,form_no);

	// �p�[�\�i���f�[�^Alloc�E�ǂݍ���
	ppd = PokePersonalPara_Open( mons_no, HEAPID_BASE_SYSTEM );

	// �l�擾
	ret = PokePersonalPara_Get( ppd, para );

	// �f�[�^���
	PokePersonalPara_Close( ppd );

	return ret;
}

//============================================================================================
/**
 *	�|�P�����p�[�\�i���\���̃f�[�^����C�ӂŃf�[�^���擾
 *  �i�ꔭ�Ńf�[�^�����o�������Ƃ��Ɏg�p���Ă��������A
 *    �p�[�\�i���f�[�^������������o�������Ƃ���Open,Get,Close���������y���ł��j
 *  
 * @param[in]	mons_no	�擾�������|�P�����i���o�[
 * @param[in]	para	�擾�����f�[�^�̃C���f�b�N�X�ipoke_tool.h�ɒ�`�j
 *
 * @return	�擾�����f�[�^
 */
//============================================================================================
u32	PokePersonalParaGet(int mons_no,int para)
{
	u32	ret;
	POKEMON_PERSONAL_DATA *ppd;

	// �p�[�\�i���f�[�^Alloc�E�ǂݍ���
	ppd = PokePersonalPara_Open( mons_no, HEAPID_BASE_SYSTEM );

	// �l�擾
	ret = PokePersonalPara_Get( ppd, para );

	// �f�[�^���
	PokePersonalPara_Close( ppd );

	return ret;
}

//============================================================================================
/**
 *	�|�P�����p�����[�^�\���̂��玟�̃��x���܂ł̌o���l�����Ŏ擾
 *
 * @param[in]	pp	�|�P�����p�����[�^�\���̂̃|�C���^
 */
//============================================================================================
u8	PokeParaNextLevelExpRatioGet(POKEMON_PARAM *pp)
{
	u16		mons_no;
	u8		level;
	u32		min_exp;
	u32		now_exp;
	u32		max_exp;
	u8		ratio;
	BOOL	flag;

	flag=PokeParaFastModeOn(pp);

	mons_no=PokeParaGet(pp,ID_PARA_monsno,NULL);
	level=PokeParaGet(pp,ID_PARA_level,NULL);
	min_exp=PokeLevelExpGet(mons_no,level);
	max_exp=PokeLevelExpGet(mons_no,level+1);
	now_exp=PokeParaGet(pp,ID_PARA_exp,NULL);

	PokeParaFastModeOff(pp,flag);

	ratio=((now_exp-min_exp)*100)/(max_exp-min_exp);

	return ratio;
}

//============================================================================================
/**
 *	�|�P�����p�����[�^�\���̂��玟�̃��x���܂ł̌o���l���擾
 *
 * @param[in]	pp	�|�P�����p�����[�^�\���̂̃|�C���^
 */
//============================================================================================
u32		PokeParaNextLevelExpGet(POKEMON_PARAM *pp)
{
	return PokePasoParaNextLevelExpGet(&pp->ppp);
}

//============================================================================================
/**
 *	�|�P�����p�����[�^�\���̂��玟�̃��x���܂ł̌o���l���擾
 *
 * @param[in]	pp	�|�P�����p�����[�^�\���̂̃|�C���^
 */
//============================================================================================
u32		PokePasoParaNextLevelExpGet(POKEMON_PASO_PARAM *ppp)
{
	u16	mons_no=PokePasoParaGet(ppp,ID_PARA_monsno,NULL);
	u16	level=PokePasoLevelCalc(ppp)+1;
	u32	exp=PokePasoParaGet(ppp,ID_PARA_exp,NULL);

	return PokeLevelExpGet(mons_no,level)-exp;
}

//============================================================================================
/**
 *	�|�P�����p�����[�^�\���̂���o���l�f�[�^���擾
 *
 * @param[in]	pp	�|�P�����p�����[�^�\���̂̃|�C���^
 */
//============================================================================================
u32	PokeParaLevelExpGet(POKEMON_PARAM *pp)
{
	return PokeLevelExpGet(PokeParaGet(pp,ID_PARA_monsno,NULL),PokeParaGet(pp,ID_PARA_level,NULL));
}

//============================================================================================
/**
 *	�|�P�����i���o�[�ƃ��x������o���l�f�[�^���擾
 *
 * @param[in]	mons_no		�擾���郂���X�^�[�i���o�[
 * @param[in]	level		�擾���郌�x��
 */
//============================================================================================
u32	PokeLevelExpGet(int	mons_no,int level)
{
	return	PokeGrowParaGet(PokePersonalParaGet(mons_no,ID_PER_grow),level);
}

//============================================================================================
/**
 *	�|�P���������e�[�u���f�[�^���擾
 *
 * @param[in]	para		�擾���鐬���e�[�u���̃C���f�b�N�X�i0�`7�j
 * @param[out]	grow_tbl	�擾���������e�[�u���̊i�[��
 */
//============================================================================================
void	PokeGrowDataGet(int para,u32 *grow_tbl)
{
	GF_ASSERT_MSG(para<8,"PokeGrowDataGet:TableIndexOver!");
	ArchiveDataLoad(grow_tbl,ARC_GROW_TBL,para);
}

//============================================================================================
/**
 *	�|�P���������e�[�u���f�[�^����C�ӂŌo���l�f�[�^���擾
 *
 * @param[in]	para		�擾���鐬���e�[�u���̃C���f�b�N�X�i0�`7�j
 * @param[in]	level		�擾���鐬���e�[�u���̃��x���i0�`100�j
 *
 * @return	�擾�����o���l�f�[�^
 */
//============================================================================================
u32	PokeGrowParaGet(int para,int level)
{
	u32	exp;
	u32	*grow_tbl;

	GF_ASSERT_MSG(para<8,"PokeGrowParaGet:TableIndexOver!");
	GF_ASSERT_MSG(level<=101,"PokeGrowParaGet:Level Over!");

	grow_tbl=sys_AllocMemory(HEAPID_BASE_SYSTEM,101*4);
	PokeGrowDataGet(para,grow_tbl);

	exp=grow_tbl[level];

	sys_FreeMemoryEz(grow_tbl);

	return	exp;
}

//============================================================================================
/**
 *	�|�P�����f�[�^����|�P�����̃��x�����擾
 *
 * @param[in]	pp	�擾�������|�P�����p�����[�^�\���̂̃|�C���^
 *
 * @return	�擾�������x��
 */
//============================================================================================
u32	PokeParaLevelCalc(POKEMON_PARAM *pp)
{
	return PokePasoLevelCalc(&pp->ppp);
}
//============================================================================================
/**
 *	�{�b�N�X�|�P�����f�[�^����|�P�����̃��x�����擾
 *
 * @param[in]	ppp	�擾�������{�b�N�X�|�P�����p�����[�^�\���̂̃|�C���^
 *
 * @return	�擾�������x��
 */
//============================================================================================
u32	PokePasoLevelCalc(POKEMON_PASO_PARAM *ppp)
{
	int	monsno;
	u32	exp;
	BOOL	flag;

	flag=PokePasoParaFastModeOn(ppp);

	monsno=PokePasoParaGet(ppp,ID_PARA_monsno,0);
	exp=PokePasoParaGet(ppp,ID_PARA_exp,0);

	PokePasoParaFastModeOff(ppp,flag);

	return PokeLevelCalc(monsno,exp);

}
//============================================================================================
/**
 *	�|�P�����i���o�[�A�o���l����|�P�����̃��x�����v�Z
 *	�i�����Ńp�[�\�i���f�[�^�����[�h����j
 *
 * @param[in]	mons_no	�擾�������|�P�����i���o�[
 * @param[in]	exp		�擾�������|�P�����̌o���l
 *
 * @return	�擾�������x��
 */
//============================================================================================
u32	PokeLevelCalc(u16 mons_no,u32 exp)
{
	int	grow;
	u32	level;
	u32	*grow_tbl;

	POKEMON_PERSONAL_DATA* personalData = PokePersonalPara_Open(mons_no, HEAPID_BASE_SYSTEM);

	level=PokePersonal_LevelCalc( personalData, mons_no, exp );

	PokePersonalPara_Close( personalData );

	return level;
}
//============================================================================================
/**
 *	�|�P�����i���o�[�A�o���l����|�P�����̃��x�����v�Z
 *	�i���[�h�ς݃p�[�\�i���f�[�^�𗘗p����j
 *
 * @param[in]	personalData	�|�P�����p�[�\�i���f�[�^
 * @param[in]	mons_no			�|�P�����i���o�[
 * @param[in]	exp				�o���l
 *
 * @return	�擾�������x��
 */
//============================================================================================
u32 PokePersonal_LevelCalc( POKEMON_PERSONAL_DATA* personalData, u16 monsno, u32 exp )
{
	static u32 grow_tbl[101];
	int grow, level;

	grow = PokePersonalPara_Get( personalData, ID_PER_grow );
	PokeGrowDataGet( grow, grow_tbl );

	for(level=1;level<101;level++){
		if(grow_tbl[level]>exp) break;
	}

	return level-1;
}





//============================================================================================
/**
 *	�|�P�����̐��i���擾�i������POKEMON_PARAM)
 *
 * @param[in]	pp	�擾�������|�P�����p�����[�^�\���̂̃|�C���^
 *
 * @return	�擾�������i
 */
//============================================================================================
u8	PokeSeikakuGet(POKEMON_PARAM *pp)
{
	return	PokePasoSeikakuGet(&pp->ppp);
}

//============================================================================================
/**
 *	�|�P�����̐��i���擾�i������POKEMON_PASO_PARAM)
 *
 * @param[in]	ppp	�擾�������|�P�����p�����[�^�\���̂̃|�C���^
 *
 * @return	�擾�������i
 */
//============================================================================================
u8	PokePasoSeikakuGet(POKEMON_PASO_PARAM *ppp)
{
	BOOL	flag;
	u32		rnd;

	flag=PokePasoParaFastModeOn(ppp);
	rnd=PokePasoParaGet(ppp,ID_PARA_personal_rnd,0);
	PokePasoParaFastModeOff(ppp,flag);

	return PokeSeikakuGetRnd(rnd);
}

//============================================================================================
/**
 *	�|�P�����̐��i���擾
 *
 *	���i�́A��������25�Ŋ������]�肩��Z�o�����
 *
 * @param[in]	rnd	�擾������������
 *
 * @return	�擾�������i
 */
//============================================================================================
u8	PokeSeikakuGetRnd(u32 rnd)
{
	return(u8)(rnd%25);
}

//============================================================================================
/**
 *	���i�ɂ��p�����[�^�ω��l�e�[�u��
 */
//============================================================================================
static	const	s8	SeikakuAbiTbl[][5]={
//		pow	def	agi	spepow	spedef
	{	 0,	 0,	 0,	 0,		 0},		//����΂��
	{	 1,	-1,	 0,	 0,		 0},		//���݂�����
	{	 1,	 0,	-1,	 0,		 0},		//�䂤����
	{	 1,	 0,	 0,	-1,		 0},		//�������ς�
	{	 1,	 0,	 0,	 0,		-1},		//��񂿂�
	{	-1,	 1,	 0,	 0,		 0},		//���ԂƂ�
	{	 0,	 0,	 0,	 0,		 0},		//���Ȃ�
	{	 0,	 1,	-1,	 0,		 0},		//�̂�
	{	 0,	 1,	 0,	-1,		 0},		//���ς�
	{	 0,	 1,	 0,	 0,		-1},		//�̂��Ă�
	{	-1,	 0,	 1,	 0,		 0},		//�����т傤
	{	 0,	-1,	 1,	 0,		 0},		//��������
	{	 0,	 0,	 0,	 0,		 0},		//�܂���
	{	 0,	 0,	 1,	-1,		 0},		//�悤��
	{	 0,	 0,	 1,	 0,		-1},		//�ނ��Ⴋ
	{	-1,	 0,	 0,	 1,		 0},		//�Ђ�����
	{	 0,	-1,	 0,	 1,		 0},		//�����Ƃ�
	{	 0,	 0,	-1,	 1,		 0},		//�ꂢ����
	{	 0,	 0,	 0,	 0,		 0},		//�Ă��
	{	 0,	 0,	 0,	 1,		-1},		//���������
	{	-1,	 0,	 0,	 0,		 1},		//�����₩
	{	 0,	-1,	 0,	 0,		 1},		//���ƂȂ���
	{	 0,	 0,	-1,	 0,		 1},		//�Ȃ܂���
	{	 0,	 0,	 0,	-1,		 1},		//���񂿂傤
	{	 0,	 0,	 0,	 0,		 0},		//���܂���
};

//============================================================================================
/**
 *	���i�ɂ��p�����[�^�ω��v�Z���[�`��
 *
 * @param[in]	chr		�v�Z���鐫�i
 * @param[in]	para	�v�Z����p�����[�^�l
 * @param[in]	cond	���o���p�����[�^�ω��l�e�[�u���̃C���f�b�N�X�ipoke_tool.h�ɒ�`�j
 *
 * @return	�v�Z����
 */
//============================================================================================
u16	PokeChrAbiCalc(u8 chr,u16 para,u8 cond)
{
	u16	ret;

	if((cond<COND_POW)||(cond>COND_SPEDEF)) return para;

	switch(SeikakuAbiTbl[chr][cond-1]){
		case 1:
			ret=para*110;
			ret/=100;
			break;
		case -1:
			ret=para*90;
			ret/=100;
			break;
		default:
			ret=para;
			break;
	}
	return	ret;
}

//============================================================================================
/**
 *	���i�ɂ��p�����[�^�ω��e�[�u���l�擾
 *
 * @param[in]	chr		�擾���鐫�i
 * @param[in]	cond	�擾����p�����[�^�ω��l�e�[�u���̃C���f�b�N�X�ipoke_tool.h�ɒ�`�j
 *
 * @return	�ω��e�[�u���l
 */
//============================================================================================
s8	PokeChrAbiTableGet(u8 chr,u8 cond)
{
	return SeikakuAbiTbl[chr][cond-1];
}

//============================================================================================
/**
 *	�Ȃ��x�v�Z�e�[�u��
 */
//============================================================================================
static	const	s8	FriendParaTbl[][3]={
	{  5,  3,  2},		//���x���A�b�v
	{  5,  3,  2},		//�w�͒l�A�b�v�A�C�e���i�^�E�������j�g�p
	{  1,  1,  0},		//�U���⏕�A�C�e���i�X�s�[�_�[���j�g�p
	{  3,  2,  1},		//�{�X��ɎQ���i�W�����[�_�[�A�l�V���A�`�����v�j
	{  1,  1,  0},		//�Z�}�V���g�p
	{  1,  1,  1},		//�A�����
	{ -1, -1, -1},		//�m��
	{ -5, -5,-10},		//�ǂ��̘A������ɂ��m��
	{ -5, -5,-10},		//���x���R�O���ȏ�̕m��
	{  3,  2,  1},		//�R���e�X�g�ŗD��
};

/*
	if(id==FRIEND_BOSS_BATTLE){
		if((FightType&FIGHT_TYPE_TRAINER)==0)
			return;
		if((TD[FieldTrainerID].type!=TRTYPE_ZIMURIIDAA)&&
		   (TD[FieldTrainerID].type!=TRTYPE_SITENNOU)&&
		   (TD[FieldTrainerID].type!=TRTYPE_TYANPION))
			return;
	}
*/

//============================================================================================
/**
 *	�Ȃ��x�v�Z
 *
 * @param[in]	pp		�Ȃ��x���v�Z����|�P�����\���̂̃|�C���^
 * @param[in]	id		�Ȃ��x�v�Z����|�P�����ɍs�����s��ID�i���o�[�ipoke_tool.h�ɒ�`�j
 * @param[in]	placeID	���ݒnID
 *
 */
//============================================================================================
void	FriendCalc(POKEMON_PARAM *pp,u8 id,u16 placeID)
{
	u16	monsno;
	u16	itemno;
	s16	friend;
	s8	friendtmp;
	u8	ofs;
	u8	eqp;

	//�A������̂Ȃ��x�v�Z�̊m����1/2
	if(id==FRIEND_TSUREARUKI){
		if(gf_rand()&1){
			return;
		}
	}

	monsno=PokeParaGet(pp,ID_PARA_monsno_egg,NULL);
	if((monsno==0)||(monsno==MONSNO_TAMAGO)){
		return;
	}

	itemno=PokeParaGet(pp,ID_PARA_item,NULL);
	eqp=ItemParamGet(itemno,ITEM_PRM_EQUIP,HEAPID_BASE_SYSTEM);

	ofs=0;
	friend=PokeParaGet(pp,ID_PARA_friend,NULL);
	if(friend>=100){
		ofs++;
	}
	if(friend>=200){
		ofs++;
	}

	friendtmp=FriendParaTbl[id][ofs];

	if( friendtmp>0 && (PokeParaGet(pp,ID_PARA_get_ball,NULL)==ITEM_GOOZYASUBOORU )){
		friendtmp++;
	}

	if( friendtmp>0 && (PokeParaGet(pp,ID_PARA_get_place,NULL)==placeID)){
		friendtmp++;
	}

	if(friendtmp>0){
		if(eqp==SOUBI_NATUKIDOUP){
			friendtmp=friendtmp*150/100;
		}
	}

	friend+=friendtmp;

	if(friend<0){
		friend=0;
	}
	if(friend>255){
		friend=255;
	}

	PokeParaPut(pp,ID_PARA_friend,(u8 *)&friend);
}

//============================================================================================
/**
 *	�|�P�����p�����[�^����|�P�����̐��ʂ��擾
 *
 * @param[in]	pp		�|�P�����p�����[�^�\����
 *
 * @retval	PARA_MALE:���@PARA_FEMALE:���@PARA_UNK:���ʕs��
 */
//============================================================================================
u8	PokeSexGet(POKEMON_PARAM *pp)
{
	return(PokePasoSexGet((POKEMON_PASO_PARAM *)&pp->ppp));
}
//============================================================================================
/**
 *	�{�b�N�X�|�P�����p�����[�^����|�P�����̐��ʂ��擾
 *
 * @param[in]	pp		�|�P�����p�����[�^�\����
 *
 * @retval	PARA_MALE:���@PARA_FEMALE:���@PARA_UNK:���ʕs��
 */
//============================================================================================
u8	PokePasoSexGet(POKEMON_PASO_PARAM *ppp)
{
	u16	monsno;
	u32	rnd;
	int	flag;

	flag=PokePasoParaFastModeOn(ppp);
	monsno=PokePasoParaGet(ppp,ID_PARA_monsno,0);
	rnd=PokePasoParaGet(ppp,ID_PARA_personal_rnd,0);
	PokePasoParaFastModeOff(ppp,flag);

	return	PokeSexGetMonsNo(monsno,rnd);
}
//============================================================================================
/**
 *	�|�P�����̐��ʂ��擾�i�����Ńp�[�\�i���f�[�^�����[�h����j
 *
 * @param[in]	monsno	���ʂ��擾����|�P�����i���o�[
 * @param[in]	rnd		���ʂ��擾����|�P�����̌�����
 *
 * @retval	PARA_MALE:���@PARA_FEMALE:���@PARA_UNK:���ʕs��
 */
//============================================================================================
u8	PokeSexGetMonsNo(u16 monsno,u32 rnd)
{
	POKEMON_PERSONAL_DATA* personal;
	u8 sex;

	personal = PokePersonalPara_Open( monsno, HEAPID_BASE_SYSTEM );
	sex = PokePersonal_SexGet( personal, monsno, rnd );
	PokePersonalPara_Close(personal);

	return sex;
}

//============================================================================================
/**
 *	�|�P�����̐��ʂ��擾�i���[�h�ς݃p�[�\�i���f�[�^�𗘗p����j
 *
 * @param[in]	personalData	�p�[�\�i���f�[�^�ւ̃|�C���^
 * @param[in]	monsno			���ʂ��擾����|�P�����i���o�[
 * @param[in]	rnd				���ʂ��擾����|�P�����̌�����
 *
 * @retval	PARA_MALE:���@PARA_FEMALE:���@PARA_UNK:���ʕs��
 */
//============================================================================================
u8 PokePersonal_SexGet( POKEMON_PERSONAL_DATA* personalData, u16 monsno, u32 rnd )
{
	u8 sex = PokePersonalPara_Get(personalData, ID_PER_sex);

	switch(sex){
		case	MONS_MALE:
			return	PARA_MALE;
		case	MONS_FEMALE:
			return	PARA_FEMALE;
		case	MONS_UNKNOWN:
			return	PARA_UNK;
	}
	if(sex>(rnd&0xff))
		return	PARA_FEMALE;
	else
		return	PARA_MALE;
}

//============================================================================================
/**
 *	�|�P���������A���ǂ����擾
 *
 * @param[in]	pp		�|�P�����p�����[�^�\����
 *
 * @retval	TRUE:���A�@FALSE:���A����Ȃ�
 */
//============================================================================================

u8		PokeRareGet(POKEMON_PARAM *pp)
{
	return(PokePasoRareGet(&pp->ppp));
}

u8		PokePasoRareGet(POKEMON_PASO_PARAM *ppp)
{
	u32	id;
	u32	rnd;

	id=PokePasoParaGet(ppp,ID_PARA_id_no,0);
	rnd=PokePasoParaGet(ppp,ID_PARA_personal_rnd,0);

	return(PokeRareGetPara(id,rnd));
}

//==============================================================================
/**
 * @brief   �h�c�ƌ��������烌�A���ǂ����𔻒肷��
 *
 * @param   id		ID
 * @param   rnd		������
 *
 * @retval  u8		0:���A����Ȃ�	0�ȊO:���A
 */
//==============================================================================
u8		PokeRareGetPara(u32 id,u32 rnd)
{
	return((((id&0xffff0000)>>16)^(id&0xffff)^((rnd&0xffff0000)>>16)^(rnd&0xffff))<8);
}

//============================================================================================
/**
 *	�|�P�����̌����������A�ɂ���l���擾
 *
 * @param[in]	id		�l�𓱂��g���[�i�[��ID
 *
 * @retval	������
 */
//============================================================================================
u32		PokeRareRndGet(u32 id)
{
	int	i;
	u32	rnd;
	u16	rnd_low;
	u16	rnd_high;

	id=(((id&0xffff0000)>>16)^(id&0xffff))>>3;

	rnd_low=gf_rand()&0x07;
	rnd_high=gf_rand()&0x07;

	for(i=0;i<13;i++){
		//Bit:1
		if(id&No2Bit(i)){
			if(gf_rand()&1){
				rnd_low|=No2Bit(i+3);
			}
			else{
				rnd_high|=No2Bit(i+3);
			}
		}
		//Bit:0
		else{
			if(gf_rand()&1){
				rnd_low|=No2Bit(i+3);
				rnd_high|=No2Bit(i+3);
			}
		}
	}

	rnd=rnd_low|(rnd_high<<16);

	return rnd;
}

//============================================================================================
/**
 *	�A�[�J�C�o�t�@�C�����o���p�w�b�_�f�[�^�������[�`���i�|�P�����O���t�B�b�N�j
 *
 *	PokemonParam�\���̂���|�P�����A���Y�A�F�����o���Đ���
 *
 * @param[out]	ssa		�w�b�_�f�[�^���i�[����ϐ��̃|�C���^
 * @param[in]	pp		PokemonParam�\���̂̃|�C���^
 * @param[in]	dir		��������|�P�����̌����iPARA_FRONT:���ʁ@PARA_BACK:�w�ʁj
 */
//============================================================================================
void	PokeGraArcDataGetPP(SOFT_SPRITE_ARC *ssa,POKEMON_PARAM *pp,u8 dir)
{
	PokeGraArcDataGetPPP(ssa,&pp->ppp,dir);
}

//============================================================================================
/**
 *	�A�[�J�C�o�t�@�C�����o���p�w�b�_�f�[�^�������[�`���i�|�P�����O���t�B�b�N�j
 *
 *	PokemonPasoParam�\���̂���|�P�����A���Y�A�F�����o���Đ���
 *
 * @param[out]	ssa		�w�b�_�f�[�^���i�[����ϐ��̃|�C���^
 * @param[in]	ppp		PokemonPasoParam�\���̂̃|�C���^
 * @param[in]	dir		��������|�P�����̌����iPARA_FRONT:���ʁ@PARA_BACK:�w�ʁj
 */
//============================================================================================
void	PokeGraArcDataGetPPP(SOFT_SPRITE_ARC *ssa,POKEMON_PASO_PARAM *ppp,u8 dir)
{
	BOOL fastModeFlag;
	u16 mons_no;
	u8 sex, col,form_no;
	u32	rnd;

	fastModeFlag = PokePasoParaFastModeOn(ppp);

	mons_no=PokePasoParaGet(ppp,ID_PARA_monsno_egg,NULL);
	sex=PokePasoSexGet(ppp);
	col=PokePasoRareGet(ppp);
	rnd=PokePasoParaGet(ppp,ID_PARA_personal_rnd,NULL);
	if(mons_no==MONSNO_TAMAGO){
		if(PokePasoParaGet(ppp,ID_PARA_monsno,NULL)==MONSNO_MANAFI){
			form_no=1;
		}
		else{
			form_no=0;
		}
	}
	else{
		form_no=PokePasoParaGet(ppp,ID_PARA_form_no,NULL);
	}

	PokeGraArcDataGet(ssa,mons_no,sex,dir,col,form_no,rnd);

	PokePasoParaFastModeOff(ppp, fastModeFlag);
}

//============================================================================================
/**
 *	�A�[�J�C�o�t�@�C�����o���p�w�b�_�f�[�^�������[�`���i�|�P�����O���t�B�b�N�j
 *
 * @param[out]	ssa		�w�b�_�f�[�^���i�[����ϐ��̃|�C���^
 * @param[in]	mons_no	��������|�P�����i���o�[
 * @param[in]	sex		��������|�P�����̎��Y�iPARA_MALE:���@PARA_FEMALE:���@PARA_UNK:Unknown�j
 * @param[in]	dir		��������|�P�����̌����iPARA_FRONT:���ʁ@PARA_BACK:�w�ʁj
 * @param[in]	col		��������|�P�����̐F�iPARA_NORMAL:�m�[�}���@PARA_RARE:���A�j
 * @param[in]	form_no	�������邽�߂̃t�H�����i���o�[�i�~�m���b�`�A�~�m���X�Ȃǁj
 * @param[in]	rnd		�������邽�߂̌������i�A���m�[���A�p�b�`�[���Ȃǁj
 */
//============================================================================================
void	PokeGraArcDataGet(SOFT_SPRITE_ARC *ssa,u16 mons_no,u8 sex,u8 dir,u8 col,u8 form_no,u32 rnd)
{
	//�Ԃ�����������
	ssa->strike_mons=0;
	ssa->form_no=0;
	ssa->personal_rnd=0;

	switch(mons_no){
	//�~�m���b�`
	case MONSNO_MINOMUTTI:
		//�l���s���Ȃ�A0�ɂ���
		if(form_no>FORMNO_MINOMUTTI_MAX){
			form_no=0;
		}
		ssa->arc_no=ARC_OTHER_POKE;
		ssa->index_chr=NARC_otherpoke_pmdp_455_back_kusa_NCBR+(dir/2)+form_no*2;
		ssa->index_pal=NARC_otherpoke_pmdp_455_n_kusa_NCLR+col+form_no*2;
		break;
	//�~�m���X
	case MONSNO_MINOMESU:
		//�l���s���Ȃ�A0�ɂ���
		if(form_no>FORMNO_MINOMUTTI_MAX){
			form_no=0;
		}
		ssa->arc_no=ARC_OTHER_POKE;
		ssa->index_chr=NARC_otherpoke_pmdp_457_back_kusa_NCBR+(dir/2)+form_no*2;
		ssa->index_pal=NARC_otherpoke_pmdp_457_n_kusa_NCLR+col+form_no*2;
		break;
	//�V�[�E�V
	case MONSNO_SIIUSI:
		//�l���s���Ȃ�A0�ɂ���
		if(form_no>FORMNO_SII_MAX){
			form_no=0;
		}
		ssa->arc_no=ARC_OTHER_POKE;
		ssa->index_chr=NARC_otherpoke_pmdp_458_back_west_NCBR+dir+form_no;
		ssa->index_pal=NARC_otherpoke_pmdp_458_n_west_NCLR+col+form_no*2;
		break;
	//�V�[�h���S
	case MONSNO_SIIDORUGO:
		//�l���s���Ȃ�A0�ɂ���
		if(form_no>FORMNO_SII_MAX){
			form_no=0;
		}
		ssa->arc_no=ARC_OTHER_POKE;
		ssa->index_chr=NARC_otherpoke_pmdp_459_back_west_NCBR+dir+form_no;
		ssa->index_pal=NARC_otherpoke_pmdp_459_n_west_NCLR+col+form_no*2;
		break;
	//�`�F���V��
	case MONSNO_THERISYU:
		//�l���s���Ȃ�A0�ɂ���
		if(form_no>FORMNO_THERISYU_MAX){
			form_no=0;
		}
		ssa->arc_no=ARC_OTHER_POKE;
		ssa->index_chr=NARC_otherpoke_pmdp_483_back_normal_NCBR+dir+form_no;
		ssa->index_pal=NARC_otherpoke_pmdp_483_n_normal_NCLR+(col*2)+form_no;
		break;
	//�A�E�X
	case MONSNO_AUSU:
		//�l���s���Ȃ�A0�ɂ���
		if(form_no>POKE_WAZA_TYPE_MAX){
			form_no=0;
		}
		ssa->arc_no=ARC_OTHER_POKE;
		ssa->index_chr=NARC_otherpoke_pmdp_518_back_normal_NCBR+(dir/2)+form_no*2;
		ssa->index_pal=NARC_otherpoke_pmdp_518_n_normal_NCLR+col+form_no*2;
		break;
	//�|������
	case MONSNO_POWARUN:
		//�l���s���Ȃ�A0�ɂ���
		if(form_no>FORMNO_POWARUN_MAX){
			form_no=0;
		}
		ssa->arc_no=ARC_OTHER_POKE;
		ssa->index_chr=NARC_otherpoke_pmdp_351_back_normal_NCBR+(dir*2)+form_no;
		ssa->index_pal=NARC_otherpoke_pmdp_351_n_normal_NCLR+(col*4)+form_no;
		break;
	//�f�I�L�V�X
	case MONSNO_DEOKISISU:
		//�l���s���Ȃ�A0�ɂ���
		if(form_no>FORMNO_DEOKISISU_MAX){
			form_no=0;
		}
		ssa->arc_no=ARC_OTHER_POKE;
		ssa->index_chr=NARC_otherpoke_pmdp_386_back_n_NCBR+(dir/2)+form_no*2;
		ssa->index_pal=NARC_otherpoke_pmdp_386_n_NCLR+col;
		break;
	//�A���m�[��
	case MONSNO_ANNOON:
		//�l���s���Ȃ�A0�ɂ���
		if(form_no>=UNK_END){
			form_no=0;
		}
		ssa->arc_no=ARC_OTHER_POKE;
//		ssa->index_chr=NARC_otherpoke_pmdp_una_back_o_NCBR+(dir/2)+PokemonUnknownFormGet(rnd)*2;
		ssa->index_chr=NARC_otherpoke_pmdp_una_back_o_NCBR+(dir/2)+form_no*2;
		ssa->index_pal=NARC_otherpoke_pmdp_201_n_NCLR+col;
		break;
	//�^�}�S
	case MONSNO_TAMAGO:
		//�l���s���Ȃ�A0�ɂ���
		if(form_no>1){
			form_no=0;
		}
		ssa->arc_no=ARC_OTHER_POKE;
		ssa->index_chr=NARC_otherpoke_pmdp_egg_normal_NCBR+form_no;
		ssa->index_pal=NARC_otherpoke_pmdp_egg_normal_NCLR+form_no;
		break;
	//�_���^�}�S
	case MONSNO_DAMETAMAGO:
		ssa->arc_no=ARC_OTHER_POKE;
		ssa->index_chr=NARC_otherpoke_pmdp_egg_normal_NCBR;
		ssa->index_pal=NARC_otherpoke_pmdp_egg_normal_NCLR;
		break;
	default:
		ssa->arc_no=ARC_POKE_GRA;
		ssa->index_chr=mons_no*POKE_GRA_SIZE+dir+(sex!=PARA_FEMALE?1:0);
		ssa->index_pal=mons_no*POKE_GRA_SIZE+POKE_COL_OFS+col;
		//�p�b�`�[���̎��́A�Ԃ��f�[�^���i�[
		if((mons_no==MONSNO_PATTIIRU)&&(dir==PARA_FRONT)){
			ssa->strike_mons=MONSNO_PATTIIRU;
			ssa->form_no=0;
			ssa->personal_rnd=rnd;
		}
		break;
	}
}

//============================================================================================
/**
 *	�|�P�����������擾
 *
 * @param[in]	pp		�擾����|�P�����̍\���̃f�[�^�ւ̃|�C���^
 * @param[in]	dir		�擾����|�P�����̌����iPARA_FRONT:���ʁ@PARA_BACK:�w�ʁj
 */
//============================================================================================
u8	PokeParaHeightGet(POKEMON_PARAM *pp,u8 dir)
{
	return PokePasoParaHeightGet(&pp->ppp,dir);
}

//============================================================================================
/**
 *	�|�P�����������擾
 *
 * @param[in]	ppp		�擾����|�P�����̍\���̃f�[�^�ւ̃|�C���^
 * @param[in]	dir		�擾����|�P�����̌����iPARA_FRONT:���ʁ@PARA_BACK:�w�ʁj
 */
//============================================================================================
u8	PokePasoParaHeightGet(POKEMON_PASO_PARAM *ppp,u8 dir)
{
	u16	mons_no;
	u8	sex;
	u8	form_no;
	u32	rnd;

	mons_no=PokePasoParaGet(ppp,ID_PARA_monsno_egg,NULL);
	sex=PokePasoSexGet(ppp);
	rnd=PokePasoParaGet(ppp,ID_PARA_personal_rnd,NULL);
	if(mons_no==MONSNO_TAMAGO){
		if(PokePasoParaGet(ppp,ID_PARA_monsno,NULL)==MONSNO_MANAFI){
			form_no=1;
		}
		else{
			form_no=0;
		}
	}
	else{
		form_no=PokePasoParaGet(ppp,ID_PARA_form_no,NULL);
	}

	return PokeHeightGet(mons_no,sex,dir,form_no,rnd);
}

//============================================================================================
/**
 *	�|�P�����������擾
 *
 * @param[in]	mons_no	�擾����|�P�����i���o�[
 * @param[in]	sex		�擾����|�P�����̐��ʁiPARA_MALE:�I�X�@PARA_FEMALE:���X�@PARA_UNKNOWN�F���ʂȂ��j
 * @param[in]	dir		�擾����|�P�����̌����iPARA_FRONT:���ʁ@PARA_BACK:�w�ʁj
 * @param[in]	form_no	�擾����|�P�����̃t�H�����i���o�[
 * @param[in]	rnd		�擾����|�P�����̌�����
 */
//============================================================================================
u8	PokeHeightGet(u16 mons_no,u8 sex,u8 dir,u8 form_no,u32 rnd)
{
	int	arcID;
	int	index;
	u8	height;

	switch(mons_no){
	//�~�m���b�`
	case MONSNO_MINOMUTTI:
		//�l���s���Ȃ�A0�ɂ���
		if(form_no>FORMNO_MINOMUTTI_MAX){
			form_no=0;
		}
		arcID=ARC_OTHER_HEIGHT;
		index=NARC_height_o_pmdp_455_back_kusa_bin+(dir/2)+form_no*2;
		break;
	//�~�m���X
	case MONSNO_MINOMESU:
		//�l���s���Ȃ�A0�ɂ���
		if(form_no>FORMNO_MINOMUTTI_MAX){
			form_no=0;
		}
		arcID=ARC_OTHER_HEIGHT;
		index=NARC_height_o_pmdp_457_back_kusa_bin+(dir/2)+form_no*2;
		break;
	//�V�[�E�V
	case MONSNO_SIIUSI:
		//�l���s���Ȃ�A0�ɂ���
		if(form_no>FORMNO_SII_MAX){
			form_no=0;
		}
		arcID=ARC_OTHER_HEIGHT;
		index=NARC_height_o_pmdp_458_back_west_bin+dir+form_no;
		break;
	//�V�[�h���S
	case MONSNO_SIIDORUGO:
		//�l���s���Ȃ�A0�ɂ���
		if(form_no>FORMNO_SII_MAX){
			form_no=0;
		}
		arcID=ARC_OTHER_HEIGHT;
		index=NARC_height_o_pmdp_459_back_west_bin+dir+form_no;
		break;
	//�`�F���V��
	case MONSNO_THERISYU:
		//�l���s���Ȃ�A0�ɂ���
		if(form_no>FORMNO_THERISYU_MAX){
			form_no=0;
		}
		arcID=ARC_OTHER_HEIGHT;
		index=NARC_height_o_pmdp_483_back_normal_bin+dir+form_no;
		break;
	//�A�E�X
	case MONSNO_AUSU:
		//�l���s���Ȃ�A0�ɂ���
		if(form_no>POKE_WAZA_TYPE_MAX){
			form_no=0;
		}
		arcID=ARC_OTHER_HEIGHT;
		index=NARC_height_o_pmdp_518_back_normal_bin+(dir/2)+form_no*2;
		break;
	//�|������
	case MONSNO_POWARUN:
		//�l���s���Ȃ�A0�ɂ���
		if(form_no>FORMNO_POWARUN_MAX){
			form_no=0;
		}
		arcID=ARC_OTHER_HEIGHT;
		index=NARC_height_o_pmdp_351_back_normal_bin+dir*2+form_no;
		break;
	//�f�I�L�V�X
	case MONSNO_DEOKISISU:
		//�l���s���Ȃ�A0�ɂ���
		if(form_no>FORMNO_DEOKISISU_MAX){
			form_no=0;
		}
		arcID=ARC_OTHER_HEIGHT;
		index=NARC_height_o_pmdp_386_back_n_bin+(dir/2)+form_no*2;
		break;
	//�A���m�[��
	case MONSNO_ANNOON:
		//�l���s���Ȃ�A0�ɂ���
		if(form_no>=UNK_END){
			form_no=0;
		}
		arcID=ARC_OTHER_HEIGHT;
//		index=NARC_height_o_pmdp_una_back_o_bin+(dir/2)+PokemonUnknownFormGet(rnd)*2;
		index=NARC_height_o_pmdp_una_back_o_bin+(dir/2)+form_no*2;
		break;
	//�^�}�S
	case MONSNO_TAMAGO:
		//�l���s���Ȃ�A0�ɂ���
		if(form_no>1){
			form_no=0;
		}
		arcID=ARC_OTHER_HEIGHT;
		index=NARC_height_o_pmdp_egg_normal_bin+form_no;
		break;
	//�_���^�}�S
	case MONSNO_DAMETAMAGO:
		arcID=ARC_OTHER_HEIGHT;
		index=NARC_height_o_pmdp_egg_normal_bin;
		break;
	default:
		arcID=ARC_POKE_HEIGHT;
		index=mons_no*POKE_HEIGHT_SIZE+dir+(sex!=PARA_FEMALE?1:0);
		break;
	}

	ArchiveDataLoad(&height,arcID,index);

	return	height;
}

//============================================================================================
/**
 *	�A�[�J�C�o�t�@�C�����o���p�w�b�_�f�[�^�������[�`���i�g���[�i�[�O���t�B�b�N�j
 *
 * @param[out]	ssa		�w�b�_�f�[�^���i�[����ϐ��̃|�C���^
 * @param[in]	trtype	��������g���[�i�[���
 * @param[in]	dir		��������g���[�i�[�̌����iPARA_FRONT:���ʁ@PARA_BACK:�w�ʁj
 * @param[in]	sex		��������g���[�i�[�̐���
 */
//============================================================================================
void	TrGraArcDataGet(SOFT_SPRITE_ARC *ssa,u16 trtype,u8 dir,u8 sex)
{
	if(dir==PARA_FRONT){
		ssa->arc_no=ARC_TRF_GRA;
	}
	else{
		ssa->arc_no=ARC_TRB_GRA;
		trtype=TrainerBTrTypeGet(trtype);
	}

	ssa->index_chr=trtype*TR_GRA_SIZE;
	ssa->index_pal=trtype*TR_GRA_SIZE+TR_COL_OFS;

	//�g���[�i�[�O���t�B�b�N�́A�`�ԕω��f�[�^���N���A
	ssa->strike_mons=0;
	ssa->form_no=0;
	ssa->personal_rnd=0;
}

//============================================================================================
/**
 *	�|�P�����̃A�j���[�V�����f�[�^���Z�b�g
 *
 * @param[out]	ssanm	�A�j���[�V�����f�[�^���i�[����ϐ��̃|�C���^
 * @param[in]	monsno	�Z�b�g����|�P�����i���o�[
 */
//============================================================================================
void	PokeAnmDataSet(SOFT_SPRITE_ANIME *ssanm,u16 mons_no)
{
	POKE_ANM_TABLE	pat;

	ArchiveDataLoadOfs(&pat,ARC_POKE_ANM_TBL,0,mons_no*sizeof(POKE_ANM_TABLE),sizeof(POKE_ANM_TABLE));
	MI_CpuCopy8(&pat.ssa[0],ssanm,sizeof(SOFT_SPRITE_ANIME)*10);
}

//============================================================================================
/**
 *	�|�P�����̃A�j���[�V�����f�[�^���Z�b�g�i�v���O�����A�j���j
 *
 * @param[in]	pasp	�A�j���[�V�����V�X�e�����[�N�̃|�C���^
 * @param[in]	ss		�A�j���[�V�����f�[�^���Z�b�g����SoftSprite�̃|�C���^
 * @param[in]	monsno	�Z�b�g����|�P�����i���o�[
 * @param[in]	dir		�Z�b�g�������
 * @param[in]	chr		�|�P�����̐��i�i�w�ʂ̃A�j���[�V���������肷��̂ɕK�v�j
 * @param[in]	reverse	HFLIP���邩�ǂ����H(PARA_HFLIP_OFF:HFLIP�Ȃ��@PARA_HFLIP_ON:HFLIP����j
 * @param[in]	index	�Z�b�g����V�X�e�����[�N�̃C���f�b�N�X
 */
//============================================================================================
void	PokePrgAnmDataSet(POKE_ANM_SYS_PTR pasp,SOFT_SPRITE *ss,u16 mons_no,int dir,int chr,int reverse,int index)
{
	P_ANM_SETTING_PARAM	pas_p;
	POKE_ANM_TABLE		pat;
	int					no;

	ArchiveDataLoadOfs(&pat,ARC_POKE_ANM_TBL,0,mons_no*sizeof(POKE_ANM_TABLE),sizeof(POKE_ANM_TABLE));

	if(dir==PARA_FRONT){
		pas_p.AnimeNo=pat.poke_f.patno;
		pas_p.Wait=pat.poke_f.wait;
		pas_p.Reverse=reverse;
	}
	else{
		no=PokeAnm_GetBackAnmSlotNo(chr);
		GF_ASSERT(no<3);
		pas_p.AnimeNo=pat.poke_b[no].patno;
		pas_p.Wait=pat.poke_b[no].wait;
		pas_p.Reverse=reverse;
	}

	PokeAnm_SetPokeAnime(pasp,ss,&pas_p,index);
}

//============================================================================================
/**
 *	�A�[�J�C�o�t�@�C�����o���p�w�b�_�f�[�^�������[�`���i�g���[�i�[�O���t�B�b�N�j
 *
 * @param[out]	ssa		�w�b�_�f�[�^���i�[����ϐ��̃|�C���^
 * @param[in]	trtype	��������g���[�i�[�^�C�v
 */
//============================================================================================
void	TrTypeGraArcDataGet(SOFT_SPRITE_ARC *ssa,u16 trtype)
{
	ssa->arc_no=ARC_TRF_GRA;
	ssa->index_chr=trtype*TR_GRA_SIZE;
	ssa->index_pal=trtype*TR_GRA_SIZE+TR_COL_OFS;

	//�g���[�i�[�O���t�B�b�N�́A�Ԃ��f�[�^���N���A
	ssa->strike_mons=0;
	ssa->form_no=0;
	ssa->personal_rnd=0;
}

//============================================================================================
/**
 *	PokemonParam�\���̂̃T�C�Y���擾
 */
//============================================================================================
u32		PokemonParamSizeGet(void)
{
	return (u32)sizeof(POKEMON_PARAM);
}

//============================================================================================
/**
 *	PokemonPasoParam�\���̂̃T�C�Y���擾
 */
//============================================================================================
u32		PokemonPasoParamSizeGet(void)
{
	return (u32)sizeof(POKEMON_PASO_PARAM);
}

//============================================================================================
/**
 *	�A���m�[���̃t�H�����i���o�[���Q�b�g
 *
 * @param[in]	pp	�|�P�����p�����[�^�\���̂̃|�C���^
 *
 * @retval	0-25:A-Z 26:! 27:?
 */
//============================================================================================
u8	PokeParaUnknownFormGet(POKEMON_PARAM *pp)
{
	return PokePasoParaUnknownFormGet((POKEMON_PASO_PARAM *)&pp->ppp);
}

//============================================================================================
/**
 *	�A���m�[���̃t�H�����i���o�[���Q�b�g
 *
 * @param[in]	ppp	�{�b�N�X�|�P�����p�����[�^�\���̂̃|�C���^
 *
 * @retval	0-25:A-Z 26:! 27:?
 */
//============================================================================================
u8	PokePasoParaUnknownFormGet(POKEMON_PASO_PARAM *ppp)
{
	return PokePasoParaGet(ppp,ID_PARA_form_no,NULL);
//	u32	annon_rnd=PokePasoParaGet(ppp,ID_PARA_personal_rnd,NULL);

//	return PokemonUnknownFormGet(annon_rnd);
}

//�c�r����莝������form_no�����o���������̂ŁA����������擾������@�͍폜
#if 0
//============================================================================================
/**
 *	�A���m�[���̃t�H�����i���o�[���Q�b�g
 *
 * @param[in]	annon_rnd	�擾���������
 *
 * @retval	0-25:A-Z 26:! 27:?
 */
//============================================================================================
u8	PokemonUnknownFormGet(u32 annon_rnd)
{
	return (((annon_rnd&0x03000000)>>18)|((annon_rnd&0x030000)>>12)|((annon_rnd&0x0300)>>6)|(annon_rnd&0x03))%28;
}

//============================================================================================
/**
 *	�A���m�[���̃t�H�����i���o�[������������擾
 *
 * @param[in]	form	�A���m�[���̃t�H�����i���o�[
 *
 * @retval	������
 */
//============================================================================================
u32	PokemonPasoUnknownFormRndGet(int form)
{
	return (((form&0x000000c0)<<18)|((form&0x00000030)<<12)|((form&0x0000000c)<<6)|(form&0x00000003));
}
#endif

//============================================================================================
/**
 *	POKEMON_PASO_PARAM�̃|�C���^���擾
 *
 * @param[in]	pp	�|�P�����p�����[�^�\���̂̃|�C���^
 *
 * @retval	ppp
 */
//============================================================================================
POKEMON_PASO_PARAM	*PPPPointerGet(POKEMON_PARAM *pp)
{
	return &pp->ppp;
}

//============================================================================================
/**
 *	�|�P�����̃��x���A�b�v�`�F�b�N������
 *
 * @param[in]	pp	�`�F�b�N����|�P�����\���̂̃|�C���^
 *
 * @retval	0:���x���A�b�v���Ȃ�
 *			1:���x���A�b�v�����i���̏ꍇlevel��+1����j
 */
//============================================================================================
u8	PokeLevelUpCheck(POKEMON_PARAM *pp)
{
	u16	monsno;
	u8	level;
	u32	exp;
	u32	grow_exp;
	int	para;

	monsno=PokeParaGet(pp,ID_PARA_monsno,NULL);
	level=PokeParaGet(pp,ID_PARA_level,NULL)+1;
	exp=PokeParaGet(pp,ID_PARA_exp,NULL);
	para=PokePersonalParaGet(monsno,ID_PER_grow);

	//�o���l������𒴂��Ă���ꍇ�͕␳����
	grow_exp=PokeGrowParaGet(para,100);
	if(exp>grow_exp){
		exp=grow_exp;
		PokeParaPut(pp,ID_PARA_exp,(u8 *)&exp);
	}
	//���x��101�ȏ�̓��x���A�b�v���Ȃ�
	if(level>100){
		return 0;
	}

	grow_exp=PokeGrowParaGet(para,level);
	if(exp>=grow_exp){
		PokeParaPut(pp,ID_PARA_level,(u8 *)&level);
		return 1;
	}
	return 0;
}

//============================================================================================
/**
 *	�i���`�F�b�N
 *
 *	@param[in]	pp			�`�F�b�N����|�P�����̍\���̂̃|�C���^
 *	@param[in]	type		�i�������ipoke_tool_def.h�ɒ�`�j
 *	@param[in]	itemno		�A�C�e���i���`�F�b�N���̎g�p�A�C�e���i�ꏊ�i���̏ꍇ�́Ashinka_place_mode�j
 *	@param[out]	shinka_cond	�i�������i�[���[�N�ւ̃|�C���^
 *
 *	@retval	0 �i������ 0�ȊO �i�������|�P�����i���o�[
 */
//============================================================================================
#define	SHINKA_COND_MAX	(7)	//�i��������MAX
u16	PokeShinkaCheck(POKEPARTY *ppt,POKEMON_PARAM *pp,u8 type,u16 itemno,int *shinka_cond)
{
	u16	monsno;
	u16	item;
	u8	level;
	int	i;
	u16	ret=0;
	u16	friend;
	u32	personal_rnd;
	u8	eqp;
	u8	beautiful;
	u16	rnd=0;
	POKEMON_SHINKA_TABLE	*pst;
	int	dummy;

	monsno=			PokeParaGet(pp,ID_PARA_monsno,		NULL);
	item=			PokeParaGet(pp,ID_PARA_item,		NULL);
	personal_rnd=	PokeParaGet(pp,ID_PARA_personal_rnd,NULL);
	beautiful=		PokeParaGet(pp,ID_PARA_beautiful,	NULL);
	rnd=(personal_rnd&0xffff0000)>>16;

	eqp=ItemParamGet(item,ITEM_PRM_EQUIP,HEAPID_BASE_SYSTEM);

	//�����Q���[�͐�ΐi��
	if(monsno!=MONSNO_YUNGERAA){
		//�A�C�e���Ői�����Ȃ��������ʂ͐i�����Ȃ�
		if((eqp==SOUBI_SINKASINAI)&&(type!=ITEM_SHINKA_CHECK)){
			return 0;
		}
	}

	if(shinka_cond==NULL){
		shinka_cond=&dummy;
	}

	pst=sys_AllocMemory(HEAPID_BASE_SYSTEM,sizeof(POKEMON_SHINKA_TABLE));
	PokeShinkaDataGet(monsno,pst);

	switch(type){
	case LEVELUP_SHINKA:
		level=PokeParaGet(pp,ID_PARA_level,NULL);
		friend=PokeParaGet(pp,ID_PARA_friend,NULL);
		for(i=0;i<SHINKA_COND_MAX;i++){
			switch(pst->psd[i].ShinkaCond){
			case SHINKA_FRIEND_HIGH:
				if(SHINKA_FRIEND<=friend){
					ret=pst->psd[i].ShinkaMons;
					shinka_cond[0]=SHINKA_FRIEND_HIGH;
				}
				break;
			case SHINKA_FRIEND_HIGH_NOON:
				if((GF_RTC_IsNightTime()==FALSE)&&
				   (SHINKA_FRIEND<=friend)){
					ret=pst->psd[i].ShinkaMons;
					shinka_cond[0]=SHINKA_FRIEND_HIGH_NOON;
				}
				break;
			case SHINKA_FRIEND_HIGH_NIGHT:
				if((GF_RTC_IsNightTime()==TRUE)&&
				   (SHINKA_FRIEND<=friend)){
					ret=pst->psd[i].ShinkaMons;
					shinka_cond[0]=SHINKA_FRIEND_HIGH_NIGHT;
				}
				break;
			case SHINKA_LEVELUP:
				if(pst->psd[i].ShinkaData<=level){
					ret=pst->psd[i].ShinkaMons;
					shinka_cond[0]=SHINKA_LEVELUP;
				}
				break;
			case SHINKA_SPECIAL_POW:
				if(pst->psd[i].ShinkaData<=level){
					if((PokeParaGet(pp,ID_PARA_pow,NULL))>(PokeParaGet(pp,ID_PARA_def,NULL))){
						ret=pst->psd[i].ShinkaMons;
						shinka_cond[0]=SHINKA_SPECIAL_POW;
					}
				}
				break;
			case SHINKA_SPECIAL_EVEN:
				if(pst->psd[i].ShinkaData<=level){
					if((PokeParaGet(pp,ID_PARA_pow,NULL))==(PokeParaGet(pp,ID_PARA_def,NULL))){
						ret=pst->psd[i].ShinkaMons;
						shinka_cond[0]=SHINKA_SPECIAL_EVEN;
					}
				}
				break;
			case SHINKA_SPECIAL_DEF:
				if(pst->psd[i].ShinkaData<=level){
					if((PokeParaGet(pp,ID_PARA_pow,NULL))<(PokeParaGet(pp,ID_PARA_def,NULL))){
						ret=pst->psd[i].ShinkaMons;
						shinka_cond[0]=SHINKA_SPECIAL_DEF;
					}
				}
				break;
			case SHINKA_SPECIAL_RND_EVEN:		//��������10�Ŋ������]�肪�T����
				if(pst->psd[i].ShinkaData<=level){
					if((rnd%10)<5){
						ret=pst->psd[i].ShinkaMons;
						shinka_cond[0]=SHINKA_SPECIAL_RND_EVEN;
					}
				}
				break;
			case SHINKA_SPECIAL_RND_ODD:		//��������10�Ŋ������]�肪�T�ȏ�
				if(pst->psd[i].ShinkaData<=level){
					if((rnd%10)>=5){
						ret=pst->psd[i].ShinkaMons;
						shinka_cond[0]=SHINKA_SPECIAL_RND_ODD;
					}
				}
				break;
			case SHINKA_SPECIAL_LEVELUP:		//�莝���ɋ󂫂�����΁A�i�����A
												//�J�����c��
				if(pst->psd[i].ShinkaData<=level){
					ret=pst->psd[i].ShinkaMons;
					shinka_cond[0]=SHINKA_SPECIAL_LEVELUP;
				}
				break;
			case SHINKA_SPECIAL_NUKENIN:		//�莝���ɋ󂫂������
				shinka_cond[0]=SHINKA_SPECIAL_NUKENIN;
				break;
			case SHINKA_SPECIAL_BEAUTIFUL:		//�������Ői��
				if(pst->psd[i].ShinkaData<=beautiful){
					ret=pst->psd[i].ShinkaMons;
					shinka_cond[0]=SHINKA_SPECIAL_BEAUTIFUL;
				}
				break;
			case SHINKA_SOUBI_NOON:
				if((GF_RTC_IsNightTime()==FALSE)&&
				   (pst->psd[i].ShinkaData==item)){
					ret=pst->psd[i].ShinkaMons;
					shinka_cond[0]=SHINKA_SOUBI_NOON;
				}
				break;
			case SHINKA_SOUBI_NIGHT:
				if((GF_RTC_IsNightTime()==TRUE)&&
				   (pst->psd[i].ShinkaData==item)){
					ret=pst->psd[i].ShinkaMons;
					shinka_cond[0]=SHINKA_SOUBI_NIGHT;
				}
				break;
			case SHINKA_WAZA:
				if(PokeParaWazaHaveCheck(pp,pst->psd[i].ShinkaData)==TRUE){
					ret=pst->psd[i].ShinkaMons;
					shinka_cond[0]=SHINKA_WAZA;
				}
				break;
			case SHINKA_POKEMON:
				if(ppt!=NULL){
					if(PokeParty_PokemonCheck(ppt,pst->psd[i].ShinkaData)==TRUE){
						ret=pst->psd[i].ShinkaMons;
						shinka_cond[0]=SHINKA_POKEMON;
					}
				}
				break;
			case SHINKA_MALE:
				if((PokeParaGet(pp,ID_PARA_sex,NULL)==PARA_MALE)&&
				   (pst->psd[i].ShinkaData<=level)){
					ret=pst->psd[i].ShinkaMons;
					shinka_cond[0]=SHINKA_MALE;
				}
				break;
			case SHINKA_FEMALE:
				if((PokeParaGet(pp,ID_PARA_sex,NULL)==PARA_FEMALE)&&
				   (pst->psd[i].ShinkaData<=level)){
					ret=pst->psd[i].ShinkaMons;
					shinka_cond[0]=SHINKA_FEMALE;
				}
				break;
			case SHINKA_PLACE_TENGANZAN:
				if(pst->psd[i].ShinkaCond==itemno){
					ret=pst->psd[i].ShinkaMons;
					shinka_cond[0]=SHINKA_PLACE_TENGANZAN;
				}
				break;
			case SHINKA_PLACE_KOKE:
				if(pst->psd[i].ShinkaCond==itemno){
					ret=pst->psd[i].ShinkaMons;
					shinka_cond[0]=SHINKA_PLACE_KOKE;
				}
				break;
			case SHINKA_PLACE_ICE:
				if(pst->psd[i].ShinkaCond==itemno){
					ret=pst->psd[i].ShinkaMons;
					shinka_cond[0]=SHINKA_PLACE_ICE;
				}
				break;
			}
			//�i������������������A������
			if(ret){
				break;
			}
		}
		break;
	case TUUSHIN_SHINKA:
		for(i=0;i<SHINKA_COND_MAX;i++){
			switch(pst->psd[i].ShinkaCond){
			case SHINKA_TUUSHIN:
				ret=pst->psd[i].ShinkaMons;
				shinka_cond[0]=SHINKA_TUUSHIN;
				break;
			case SHINKA_TUUSHIN_ITEM:
				if(pst->psd[i].ShinkaData==item){
					ret=pst->psd[i].ShinkaMons;
					shinka_cond[0]=SHINKA_TUUSHIN_ITEM;
				}
				break;
			}
			//�i������������������A������
			if(ret){
				break;
			}
		}
		break;
	case ITEM_SHINKA:
	case ITEM_SHINKA_CHECK:
		for(i=0;i<SHINKA_COND_MAX;i++){
			if((pst->psd[i].ShinkaCond==SHINKA_ITEM)&&
			   (pst->psd[i].ShinkaData==itemno)){
				ret=pst->psd[i].ShinkaMons;
				shinka_cond[0]=0;
				break;
			}
			if((pst->psd[i].ShinkaCond==SHINKA_ITEM_MALE)&&
			   (PokeParaGet(pp,ID_PARA_sex,NULL)==PARA_MALE)&&
			   (pst->psd[i].ShinkaData==itemno)){
				ret=pst->psd[i].ShinkaMons;
				shinka_cond[0]=0;
				break;
			}
			if((pst->psd[i].ShinkaCond==SHINKA_ITEM_FEMALE)&&
			   (PokeParaGet(pp,ID_PARA_sex,NULL)==PARA_FEMALE)&&
			   (pst->psd[i].ShinkaData==itemno)){
				ret=pst->psd[i].ShinkaMons;
				shinka_cond[0]=0;
				break;
			}
			//�i������������������A������
			if(ret){
				break;
			}
		}
		break;
	}
	sys_FreeMemoryEz(pst);
	return ret;
}

// =================================================================
/**
 * @brief   �n�����|�P�����J��No�̑匳�̎q����Ԃ��܂�(��O���Ⴀ��܂���j
 * @param   monsno	�|�P�����̊J��No
 * @retval  u16		�q���̊J��No�i�q���������ꍇ�͂��̂܂܈�����Ԃ��܂��j
 */
// =================================================================
u16 PokeSearchChild(const u16 monsno)
{
	FSFile		p_file;
	u16			result=0;

	GF_ASSERT_MSG((MONSNO_END+1)>monsno , "�|�P����NO��MAX�𒴂��Ă���");


	FS_InitFile(&p_file);

	FS_OpenFile(&p_file,"poketool/personal/pms.narc");			///< �匳�|�P�����e�[�u���I�[�v��

	FS_SeekFile(&p_file,monsno*2,FS_SEEK_SET);				///< MONSNOx2�����V�[�N
	FS_ReadFile(&p_file,&result,2);							///< �ǂݍ���

	FS_CloseFile(&p_file);

	return result;
}


//==============================================================================
/**
 * @brief   ���M�����[�V�����p�ɐi���|�P�������`�F�b�N����֐�
 *
 * @param   monsno	�J��NO
 *
 * @retval  u16		�i���|�P�����Ȃ���NO��Ԃ��A��Ȃ玩����NO���Ԃ�
 */
//==============================================================================
u16 PokeChildCheck( const u16 monsno )
{
	// ��|�P�������Ă���̂����A�����Ď툵�����Ă�����|�P�����𗅗�
	switch( monsno ){
	case MONSNO_SOONANSU:
	case MONSNO_MARIRU:
	case MONSNO_BARIYAADO:
	case MONSNO_USOKKII:	
	case MONSNO_KABIGON:		
	case MONSNO_MANTAIN:	
	case MONSNO_ROZERIA:		
	case MONSNO_RAKKII:	
	case MONSNO_TIRIIN:	
		return monsno;
		break;
	}
	
	// �ʏ�|�P�����̎�|�P�����擾����
	return PokeSearchChild(monsno);
}

//============================================================================================
/**
 *	�����X�^�[�i���o�[�ƃ��x������Z���Z�b�g����B
 *
 * @param[in]	pp	�Z�b�g����|�P�����f�[�^�\���̂̃|�C���^
 */
//============================================================================================
void	PokeWazaOboe(POKEMON_PARAM *pp)
{
	POKEMON_PASO_PARAM	*ppp=PPPPointerGet(pp);

	PokePasoWazaOboe(ppp);
}

//============================================================================================
/**
 *	�����X�^�[�i���o�[�ƃ��x������Z���Z�b�g����B
 *
 * @param[in]	ppp	�Z�b�g����|�P�����f�[�^�\���̂̃|�C���^
 */
//============================================================================================
void	PokePasoWazaOboe(POKEMON_PASO_PARAM *ppp)
{
	BOOL	flag;
	int	i;
	u16	monsno;
	u16	wazano;
	int	form_no;
	u16	ret;
	u8	level;
	u16	*wot=sys_AllocMemory(HEAPID_BASE_SYSTEM,LEVELUPWAZA_OBOE_MAX);

	flag=PokePasoParaFastModeOn(ppp);

	monsno=PokePasoParaGet(ppp,ID_PARA_monsno,0);
	form_no=PokePasoParaGet(ppp,ID_PARA_form_no,0);
	level=PokePasoLevelCalc(ppp);
	PokeFormNoWazaOboeDataGet(monsno,form_no,wot);

	i=0;
	while(wot[i]!=0xffff){
		if((wot[i]&0xfe00)<=(level<<9)){
			wazano=wot[i]&0x1ff;
			ret=PokePasoWazaSet(ppp,wazano);
			if(ret==NO_WAZA_SET){
				PokePasoWazaOboeOshidashi(ppp,wazano);
			}
		}
		else{
			break;
		}
		i++;
	}
	sys_FreeMemoryEz(wot);

	PokePasoParaFastModeOff(ppp,flag);
}

//============================================================================================
/**
 *	�����Ă���ꏊ�ɋZ��ǉ�����B�����Ă��Ȃ��ꍇ�͂��̎|��Ԃ��B
 *
 *	@param[in]	pp		�Z�b�g����|�P�����p�����[�^�\���̂̃|�C���^
 *	@param[in]	wazano	�Z�b�g����Z�i���o�[
 *
 *	@retvl	wazano			����I��
 *			SAME_WAZA_SET	���łɊo���Ă���Z�Ɠ����Z���o���悤�Ƃ���
 *			NO_WAZA_SET		�ꏊ���󂢂Ă��Ȃ�
 */
//============================================================================================
u16	PokeWazaSet(POKEMON_PARAM *pp,u16 wazano)
{
	POKEMON_PASO_PARAM	*ppp=PPPPointerGet(pp);

	return PokePasoWazaSet(ppp,wazano);
}

//============================================================================================
/**
 *	�����Ă���ꏊ�ɋZ��ǉ�����B�����Ă��Ȃ��ꍇ�͂��̎|��Ԃ��B
 *
 *	@param[in]	ppp		�Z�b�g����|�P�����p�����[�^�\���̂̃|�C���^
 *	@param[in]	wazano	�Z�b�g����Z�i���o�[
 *
 *	@retvl	wazano			����I��
 *			SAME_WAZA_SET	���łɊo���Ă���Z�Ɠ����Z���o���悤�Ƃ���
 *			NO_WAZA_SET		�ꏊ���󂢂Ă��Ȃ�
 */
//============================================================================================
u16	PokePasoWazaSet(POKEMON_PASO_PARAM *ppp,u16 wazano)
{
	int	i;
	u8	pp;
	u16	waza;
	u16	ret;
	BOOL	flag;

	ret=NO_WAZA_SET;

	flag=PokePasoParaFastModeOn(ppp);

	for(i=0;i<4;i++){
		if((waza=PokePasoParaGet(ppp,ID_PARA_waza1+i,NULL))==0){
			PokePasoWazaSetPos(ppp,wazano,i);
			ret=wazano;
			break;
		}
		else{
			//�����Z���o�����Ⴞ��
			if(waza==wazano){
				ret=SAME_WAZA_SET;
				break;
			}
		}
	}
	
	PokePasoParaFastModeOff(ppp,flag);

	return	ret;
}

//============================================================================================
/**
 *	�����o�����ɋZ���o����B
 *
 * @param[in]	pp		�Z�b�g����|�P�����p�����[�^�\���̂̃|�C���^
 * @param[in]	wazano	�o����Z
 */
//============================================================================================
void	PokeWazaOboeOshidashi(POKEMON_PARAM *pp,u16 wazano)
{
	POKEMON_PASO_PARAM	*ppp=PPPPointerGet(pp);

	PokePasoWazaOboeOshidashi(ppp,wazano);
}

//============================================================================================
/**
 *	�����o�����ɋZ���o����B
 *
 * @param[in]	ppp		�Z�b�g����|�P�����p�����[�^�\���̂̃|�C���^
 * @param[in]	wazano	�o����Z
 */
//============================================================================================
void	PokePasoWazaOboeOshidashi(POKEMON_PASO_PARAM *ppp,u16 wazano)
{
	int	i;
	u16	waza[4];
	u8	pp[4];
	u8	ppcnt[4];
	BOOL	flag;

	flag=PokePasoParaFastModeOn(ppp);

	for(i=0;i<3;i++){
		waza[i]=	PokePasoParaGet(ppp,ID_PARA_waza2+i,	NULL);
		pp[i]=		PokePasoParaGet(ppp,ID_PARA_pp2+i,		NULL);
		ppcnt[i]=	PokePasoParaGet(ppp,ID_PARA_pp_count2+i,NULL);
	}

	waza[3]=wazano;
	pp[3]=WT_WazaDataParaGet(wazano,ID_WTD_pp);
	ppcnt[3]=0;

	for(i=0;i<4;i++){
		PokePasoParaPut(ppp,ID_PARA_waza1+i,	(u8 *)&waza[i]);
		PokePasoParaPut(ppp,ID_PARA_pp1+i,		(u8 *)&pp[i]);
		PokePasoParaPut(ppp,ID_PARA_pp_count1+i,(u8 *)&ppcnt[i]);
	}

	PokePasoParaFastModeOff(ppp,flag);
}

//============================================================================================
/**
 *	�ꏊ���w�肵�ċZ���Z�b�g����B
 *
 * @param[in]	pp		�Z�b�g����|�P�����p�����[�^�\���̂̃|�C���^
 * @param[in]	wazano	�Z�b�g����Z�i���o�[
 * @param[in]	pos		�Z���Z�b�g����ꏊ
 */
//============================================================================================
void	PokeWazaSetPos(POKEMON_PARAM *pp,u16 wazano,u8 pos)
{
	PokePasoWazaSetPos(&pp->ppp,wazano,pos);
}

//============================================================================================
/**
 *	�ꏊ���w�肵�ċZ���Z�b�g����B
 *
 * @param[in]	ppp		�Z�b�g����|�P�����p�����[�^�\���̂̃|�C���^
 * @param[in]	wazano	�Z�b�g����Z�i���o�[
 * @param[in]	pos		�Z���Z�b�g����ꏊ
 */
//============================================================================================
void	PokePasoWazaSetPos(POKEMON_PASO_PARAM *ppp,u16 wazano,u8 pos)
{
	u8	pp;
	u8	pp_count;

	PokePasoParaPut(ppp,ID_PARA_waza1+pos,(u8 *)&wazano);
	pp_count=PokePasoParaGet(ppp,ID_PARA_pp_count1+pos,NULL);
	pp=WT_PPMaxGet(wazano,pp_count);
	PokePasoParaPut(ppp,ID_PARA_pp1+pos,(u8 *)&pp);
}


//============================================================================================
/**
 *	���x���A�b�v���Ɋo����Z���Z�b�g����B
 *
 * @param[in]		pp		�Z�b�g����\���̂̃|�C���^
 * @param[in/out]	cnt		�Z�o���e�[�u���̃J�E���^
 * @param[in/out]	wazano	�o�����Z�̊i�[���[�N
 *
 * @retval	�Z�b�g�����Z�i���o�[�iNO_WAZA_OBOE:�o���Ȃ����� NO_WAZA_SET:�Z�������ς��j
 */
//============================================================================================
u16	PokeWazaOboeCheck(POKEMON_PARAM *pp,int *cnt,u16 *wazano)
{
	u16	ret=NO_WAZA_OBOE;
	u16	monsno;
	int	form_no;
	u8	level;
	u16	*wot=sys_AllocMemory(HEAPID_BASE_SYSTEM,LEVELUPWAZA_OBOE_MAX);

	monsno=PokeParaGet(pp,ID_PARA_monsno,NULL);
	form_no=PokeParaGet(pp,ID_PARA_form_no,NULL);
	level=PokeParaGet(pp,ID_PARA_level,NULL);
	PokeFormNoWazaOboeDataGet(monsno,form_no,wot);

	if( wot[cnt[0]] == LEVELUPWAZA_OBOE_END ){
		sys_FreeMemoryEz(wot);
		return NO_WAZA_OBOE;
	}

	while( (wot[cnt[0]] & LEVELUPWAZA_LEVEL_MASK) != (level<<LEVELUPWAZA_LEVEL_SHIFT) ){
		cnt[0]++;
		if( wot[cnt[0]] == LEVELUPWAZA_OBOE_END ){
			sys_FreeMemoryEz(wot);
			return NO_WAZA_OBOE;
		}
	}
	if( (wot[cnt[0]] & LEVELUPWAZA_LEVEL_MASK) == (level<<LEVELUPWAZA_LEVEL_SHIFT) ){
		wazano[0] = wot[cnt[0]]&LEVELUPWAZA_WAZA_MASK;
		cnt[0]++;
		ret=PokeWazaSet(pp,wazano[0]);
	}

	sys_FreeMemoryEz(wot);

	return	ret;
}

//============================================================================================
/**
 *	�Z�̓���ւ�������
 *
 * @param[in]		pp			�Z�b�g����\���̂̃|�C���^
 * @param[in]		src_pos		����ւ����ʒu
 * @param[in]		dest_pos	����ւ���ʒu
 */
//============================================================================================
void	PokeParaWazaReplace(POKEMON_PARAM *pp,int src_pos,int dest_pos)
{
	PokePasoParaWazaReplace(&pp->ppp,src_pos,dest_pos);
}

//============================================================================================
/**
 *	�Z�̓���ւ�������
 *
 * @param[in]		pp			�Z�b�g����\���̂̃|�C���^
 * @param[in]		src_pos		����ւ����ʒu
 * @param[in]		dest_pos	����ւ���ʒu
 */
//============================================================================================
void	PokePasoParaWazaReplace(POKEMON_PASO_PARAM *ppp,int src_pos,int dest_pos)
{
	u16	waza_no[2];
	u8	pp[2];
	u8	pp_count[2];

	waza_no[0]=	PokePasoParaGet(ppp,ID_PARA_waza1+src_pos,		NULL);
	pp[0]=		PokePasoParaGet(ppp,ID_PARA_pp1+src_pos,		NULL);
	pp_count[0]=PokePasoParaGet(ppp,ID_PARA_pp_count1+src_pos,	NULL);
	waza_no[1]=	PokePasoParaGet(ppp,ID_PARA_waza1+dest_pos,		NULL);
	pp[1]=		PokePasoParaGet(ppp,ID_PARA_pp1+dest_pos,		NULL);
	pp_count[1]=PokePasoParaGet(ppp,ID_PARA_pp_count1+dest_pos,	NULL);

	PokePasoParaPut(ppp,ID_PARA_waza1+src_pos,		(u8 *)&waza_no[1]);
	PokePasoParaPut(ppp,ID_PARA_pp1+src_pos,		(u8 *)&pp[1]);
	PokePasoParaPut(ppp,ID_PARA_pp_count1+src_pos,	(u8 *)&pp_count[1]);
	PokePasoParaPut(ppp,ID_PARA_waza1+dest_pos,		(u8 *)&waza_no[0]);
	PokePasoParaPut(ppp,ID_PARA_pp1+dest_pos,		(u8 *)&pp[0]);
	PokePasoParaPut(ppp,ID_PARA_pp_count1+dest_pos,	(u8 *)&pp_count[0]);
}

//============================================================================================
/**
 * �w��ʒu�̋Z���N���A���āA�V�t�g����
 *
 * @param[in]	pp		�N���A����\���̂̃|�C���^
 * @param[in]	pos		�N���A�ʒu
 */
//============================================================================================
void	PokeParaWazaDelPos(POKEMON_PARAM *pp,u32 pos)
{
	u32	i;
	u16	waza_no;
	u8	pp_now;
	u8	pp_count;

	for(i=pos;i<3;i++){
		waza_no  = PokeParaGet(pp,ID_PARA_waza1+i+1,NULL);
		pp_now   = PokeParaGet(pp,ID_PARA_pp1+i+1,NULL);
		pp_count = PokeParaGet(pp,ID_PARA_pp_count1+i+1,NULL);
		
		PokeParaPut(pp,ID_PARA_waza1+i,(u8 *)&waza_no);
		PokeParaPut(pp,ID_PARA_pp1+i,(u8 *)&pp_now);
		PokeParaPut(pp,ID_PARA_pp_count1+i,(u8 *)&pp_count);
	}
	waza_no  = 0;
	pp_now   = 0;
	pp_count = 0;
	PokeParaPut(pp,ID_PARA_waza4,(u8 *)&waza_no);
	PokeParaPut(pp,ID_PARA_pp4,(u8 *)&pp_now);
	PokeParaPut(pp,ID_PARA_pp_count4,(u8 *)&pp_count);
}

//============================================================================================
/**
 * �Z�������Ă��邩�`�F�b�N
 *
 * @param[in]	pp		�`�F�b�N����\���̂̃|�C���^
 * @param[in]	waza_no	�`�F�b�N����Z�i���o�[
 *
 * @retval FALSE:�����Ă��Ȃ��@TRUE:�����Ă���
 */
//============================================================================================
BOOL	PokeParaWazaHaveCheck(POKEMON_PARAM *pp,u16 waza_no)
{
	int	i;

	for(i=0;i<WAZA_TEMOTI_MAX;i++){
		if(PokeParaGet(pp,ID_PARA_waza1+i,NULL)==waza_no){
			break;
		}
	}

	return (i!=WAZA_TEMOTI_MAX);
}

//============================================================================================
/**
 *	�{�b�N�X�̍\���̐錾����莝���̍\���̐錾�փf�[�^��
 *	�R�s�[���čČv�Z������
 *
 * @param[in]	ppp	�{�b�N�X�̍\���̂̃|�C���^
 * @param[in]	pp	�R�s�[����莝���̍\���̂̃|�C���^
 */
//============================================================================================
void	PokeReplace(POKEMON_PASO_PARAM *ppp,POKEMON_PARAM *pp)
{
	u32				i=0;
	MAIL_DATA		*mail_data;
//	CB_SAVE_DATA	*cb_core;
	CB_CORE			cb_core;

	pp->ppp=*ppp;

	//ppp��fast���[�h�Ȃ�Apcp��fast���[�h�ɂ���
	if(pp->ppp.ppp_fast_mode){
		pp->ppp.pp_fast_mode=1;
	}

//�R���f�B�V�����Z�b�g
	PokeParaPut(pp,ID_PARA_condition,(u8 *)&i);

//HP������
	PokeParaPut(pp,ID_PARA_hp,(u8 *)&i);
	PokeParaPut(pp,ID_PARA_hpmax,(u8 *)&i);

//���[���f�[�^
	mail_data=MailData_CreateWork(HEAPID_BASE_SYSTEM);
	PokeParaPut(pp,ID_PARA_mail_data,mail_data);
	sys_FreeMemoryEz(mail_data);

//�J�X�^���{�[��ID
	PokeParaPut(pp,ID_PARA_cb_id,(u8 *)&i);

//�J�X�^���{�[��
//	cb_core=CustomBall_AllocSaveData(HEAPID_BASE_SYSTEM);
//	PokeParaPut(pp,ID_PARA_cb_core,cb_core);
//	sys_FreeMemoryEz(cb_core);
	
	MI_CpuClearFast(&cb_core, sizeof(CB_CORE));
	PokeParaPut(pp,	ID_PARA_cb_core, (CB_CORE*)&cb_core);

	PokeParaCalc(pp);
}

//============================================================================================
/**
 *	�莝���|�P�����̍ő僌�x�����擾
 *
 * @param[in]	pp	�莝���|�P�����f�[�^�\����
 */
//============================================================================================
u8 GetStockPokeMaxLevel(POKEPARTY *ppt)
{
	u8				max, lv;
	int				i,poke_count;
	POKEMON_PARAM	*pp;

	poke_count=PokeParty_GetPokeCount(ppt);

	max=1;
	for(i=0;i<poke_count;i++){
		pp=PokeParty_GetMemberPointer(ppt,i);
		if((PokeParaGet(pp,ID_PARA_monsno,NULL))&&(PokeParaGet(pp,ID_PARA_tamago_flag,NULL)==0)){
			lv=PokeParaGet(pp,ID_PARA_level,NULL);
			if(lv>max){
				max=lv;
			}
		}
	}
	return max;
}

//============================================================================================
/**
 *	�S���}�Ӄi���o�[����V���I�E�}�Ӄi���o�[��Ԃ�
 *
 * @param[in]	pp	�莝���|�P�����f�[�^�\����
 *
 * @retval	�V���I�E�}�Ӄi���o�[
 */
//============================================================================================
u16		PokeParaZenkokuNo2ShinouNo(POKEMON_PARAM *pp)
{
	return PokePasoParaZenkokuNo2ShinouNo(&pp->ppp);
}

//============================================================================================
/**
 *	�S���}�Ӄi���o�[����V���I�E�}�Ӄi���o�[��Ԃ�
 *
 * @param[in]	ppp	�{�b�N�X�|�P�����f�[�^�\����
 *
 * @retval	�V���I�E�}�Ӄi���o�[
 */
//============================================================================================
u16		PokePasoParaZenkokuNo2ShinouNo(POKEMON_PASO_PARAM *ppp)
{
	return PokeZenkokuNo2ShinouNo(PokePasoParaGet(ppp,ID_PARA_monsno,NULL));
}

//============================================================================================
/**
 *	�S���}�Ӄi���o�[����V���I�E�}�Ӄi���o�[��Ԃ�
 *
 * @param[in]	mons_no	�S���}�Ӄi���o�[
 *
 * @retval	�V���I�E�}�Ӄi���o�[
 */
//============================================================================================
u16		PokeZenkokuNo2ShinouNo(u16 mons_no)
{
	u16	sinou_no;

	ArchiveDataLoadOfs(&sinou_no,ARC_POKE_ZUKAN,0,mons_no*2,2);

	return sinou_no;
}

//============================================================================================
/**
 *	�V���I�E�}�Ӄi���o�[����S���}�Ӄi���o�[��Ԃ�
 *
 * @param[in]	mons_no	�V���I�E�}�Ӄi���o�[
 *
 * @retval	�S���}�Ӄi���o�[
 */
//============================================================================================
u16		PokeShinouNo2ZenkokuNo(u16 mons_no)
{
	u16	zenkoku_no=0;

	if(mons_no<=SINOU_MAX){
		ArchiveDataLoadOfs(&zenkoku_no,ARC_SHIN_ZUKAN,0,mons_no*2,2);
	}

	return zenkoku_no;
}

//============================================================================================
/**
 *	POKEMON_PARAM�\���̂���POKEMON_PARAM�\���̂փR�s�[
 *
 * @param[in]	pp_src	�R�s�[��POKEMON_PARAM�\����
 * @param[in]	pp_dest	�R�s�[��POKEMON_PARAM�\����
 *
 * @retval	�S���}�Ӄi���o�[
 */
//============================================================================================
void	PokeCopyPPtoPP(POKEMON_PARAM *pp_src,POKEMON_PARAM *pp_dest)
{
	*pp_dest=*pp_src;

	return;
}

//============================================================================================
/**
 *	POKEMON_PASO_PARAM�\���̂���POKEMON_PASO_PARAM�\���̂փR�s�[
 *
 * @param[in]	ppp_src		�R�s�[��POKEMON_PASO_PARAM�\����
 * @param[in]	ppp_dest	�R�s�[��POKEMON_PASO_PARAM�\����
 *
 * @retval	�S���}�Ӄi���o�[
 */
//============================================================================================
void	PokeCopyPPPtoPPP(POKEMON_PASO_PARAM *ppp_src,POKEMON_PASO_PARAM *ppp_dest)
{
	*ppp_dest=*ppp_src;

	return;
}

//============================================================================================
/**
 *	POKEMON_PARAM�\���̂���POKEMON_PASO_PARAM�\���̂փR�s�[
 *
 * @param[in]	pp_src		�R�s�[��POKEMON_PARAM�\����
 * @param[in]	ppp_dest	�R�s�[��POKEMON_PASO_PARAM�\����
 *
 * @retval	�S���}�Ӄi���o�[
 */
//============================================================================================
void	PokeCopyPPtoPPP(POKEMON_PARAM *pp_src,POKEMON_PASO_PARAM *ppp_dest)
{
	*ppp_dest=pp_src->ppp;

	return;
}

//============================================================================================
/**
 *	�|�P�����̍D�݂̖����ǂ����`�F�b�N
 *
 * @param[in]	pp		POKEMON_PARAM�\����
 * @param[in]	taste	�`�F�b�N���閡
 *
 * @retval	-1:�����@0:���ʁ@1:�D��
 */
//============================================================================================
s8	PokeParaLikeTasteCheck(POKEMON_PARAM *pp,int taste)
{
	return PokePasoParaLikeTasteCheck(&pp->ppp,taste);
}

//============================================================================================
/**
 *	�|�P�����̍D�݂̖����ǂ����`�F�b�N
 *
 * @param[in]	ppp		POKEMON_PASO_PARAM�\����
 * @param[in]	taste	�`�F�b�N���閡
 *
 * @retval	-1:�����@0:���ʁ@1:�D��
 */
//============================================================================================
s8	PokePasoParaLikeTasteCheck(POKEMON_PASO_PARAM *ppp,int taste)
{
	return PokeLikeTasteCheck(PokePasoParaGet(ppp,ID_PARA_personal_rnd,NULL),taste);
}

//============================================================================================
/**
 *	�|�P�����̍D�݂̖����ǂ����`�F�b�N
 *
 * @param[in]	rnd		�|�P�����̌������i���i�𓱂��̂ɕK�v�j
 * @param[in]	taste	�`�F�b�N���閡
 *
 * @retval	-1:�����@0:���ʁ@1:�D��
 */
//============================================================================================
s8	PokeLikeTasteCheck(u32 rnd,int taste)
{
	u8	chr;

	chr=PokeSeikakuGetRnd(rnd);

	return CubeLikeTable[chr][taste];
}

//==============================================================================
/**
 * ���x���A�b�v�Ŋo����Z��S�ă��X�g�A�b�v
 *
 * @param   monsno		
 * @param   ksw->wazalist		
 *
 * @retval  none		
 */
//==============================================================================
int PokeOboeruWazaAllGet( int monsno, int form, u16 *wazalist )
{
	int i;
	u16	*wot=sys_AllocMemory(HEAPID_BASE_SYSTEM,LEVELUPWAZA_OBOE_MAX);
	
	PokeFormNoWazaOboeDataGet( monsno, form, wot );
//	PokeWazaOboeDataGet( monsno, wot );
	i = 0;
	while(wot[i] != LEVELUPWAZA_OBOE_END){
		wazalist[i] = wot[i] & LEVELUPWAZA_WAZA_MASK;
		i++;
	}
	sys_FreeMemoryEz(wot);

	return i;
}

//==============================================================================
/**
 *	�|�P�����Ƀ|�P���X������������
 *
 * @param	ppt		POKEPARTY�\���̂ւ̃|�C���^
 *
 * @retval  none		
 */
//==============================================================================
void	PokerusSetCheck(POKEPARTY *ppt)
{
	u16				rnd;
	u8				pokerus;
	POKEMON_PARAM	*pp;
	int				count;
	int				pos;

	count=PokeParty_GetPokeCount(ppt);
	rnd=gf_rand();

	if((rnd==16384)||
	   (rnd==32768)||
	   (rnd==49152)){
		do{
			pos=gf_rand()%count;
			pp=PokeParty_GetMemberPointer(ppt,pos);
			if((PokeParaGet(pp,ID_PARA_monsno,NULL))&&(PokeParaGet(pp,ID_PARA_tamago_flag,NULL)==0)){
				break;
			}
			else{
				pos=count;
			}
		}while(pos==count);
		if(PokerusedCheck(ppt,No2Bit(pos))==0){
			do{
				pokerus=gf_rand()&0xff;
			}while((pokerus&0x07)==0);
			if(pokerus&0xf0){
				pokerus&=0x07;
			}
			pokerus|=(pokerus<<4);
			pokerus&=0xf3;
			pokerus++;
			PokeParaPut(pp,ID_PARA_pokerus,(u8 *)&pokerus);
		}
	}
}

//============================================================================================
/**
 *	�|�P�������|�P���X�Ɋ������Ă��邩�`�F�b�N
 *
 * @param[in]	ppt			�������`�F�b�N����POKEPARTY�\���̂̃|�C���^
 * @param[in]	checkbit	0bit�ڂ�ON�FPP[0]���`�F�b�N
 *									:
 *									:
 *							5bit�ڂ�ON�FPP[6]���`�F�b�N
 *							0�̂Ƃ��́APP[0]�������`�F�b�N
 *
 * @retval	�������Ă���|�P�������r�b�g�ŕԂ�
 */
//============================================================================================
u8	PokerusCheck(POKEPARTY *ppt,u8 check_bit)
{
	int				pos=0,infection_bit=1;
	u8				infection=0;
	POKEMON_PARAM	*pp;

	if(check_bit){
		do{
			if(check_bit&1){
#ifdef PM_DEBUG
				{
					int	count;

					count=PokeParty_GetPokeCount(ppt);

					GF_ASSERT_MSG(count>pos,"POKEPARTY�ɓo�^����Ă��Ȃ��ʒu���Q�Ƃ��悤�Ƃ��Ă܂�\n");
				}
#endif
				pp=PokeParty_GetMemberPointer(ppt,pos);
				if(PokeParaGet(pp,ID_PARA_pokerus,NULL)&0x0f){
					infection|=infection_bit;
				}
			}
			pos++;
			infection_bit=infection_bit<<1;
			check_bit=check_bit>>1;
		}while(check_bit!=0);
	}
	else{
		pp=PokeParty_GetMemberPointer(ppt,pos);
		if(PokeParaGet(pp,ID_PARA_pokerus,NULL)&0x0f){
			infection++;
		}
	}
	return infection;
}

//============================================================================================
/**
 *	�|�P�������|�P���X�Ɋ������Ă��邩�`�F�b�N�i�ߋ��Ɋ������Ă������Ƃ����݁j
 *
 * @param[in]	ppt			�������`�F�b�N����POKEPARTY�\���̂̃|�C���^
 * @param[in]	checkbit	0bit�ڂ�ON�FPP[0]���`�F�b�N
 *									:
 *									:
 *							5bit�ڂ�ON�FPP[6]���`�F�b�N
 *							0�̂Ƃ��́APP[0]�������`�F�b�N
 *
 * @retval	�������Ă���|�P�������r�b�g�ŕԂ�
 */
//============================================================================================
u8	PokerusedCheck(POKEPARTY *ppt,u8 check_bit)
{
	int	pos=0;
	int	infection_bit=1;
	u8	infection=0;
	POKEMON_PARAM	*pp;

	if(check_bit){
		do{
			if(check_bit&1){
#ifdef PM_DEBUG
				{
					int	count;

					count=PokeParty_GetPokeCount(ppt);

					GF_ASSERT_MSG(count>pos,"POKEPARTY�ɓo�^����Ă��Ȃ��ʒu���Q�Ƃ��悤�Ƃ��Ă܂�\n");
				}
#endif
				pp=PokeParty_GetMemberPointer(ppt,pos);
				if(PokeParaGet(pp,ID_PARA_pokerus,NULL)){
					infection|=infection_bit;
				}
			}
			pos++;
			infection_bit=infection_bit<<1;
			check_bit=check_bit>>1;
		}while(check_bit!=0);
	}
	else{
		pp=PokeParty_GetMemberPointer(ppt,pos);
		if(PokeParaGet(pp,ID_PARA_pokerus,NULL)){
			infection++;
		}
	}
	return infection;
}

//============================================================================================
/**
 *	�|�P���X�̓����J�E���^�[���f�N�������g����
 *
 * @param[in]	ppt		�`�F�b�N����POKEPARTY�\���̂̃|�C���^
 * @param[in]	day		�o�ߓ���
 *
 * @retval	none
 */
//============================================================================================
void	PokerusCounterDec(POKEPARTY *ppt,s32 day)
{
	int	pos;
	int	count;
	u8	pokerus;
	POKEMON_PARAM	*pp;

	count=PokeParty_GetPokeCount(ppt);

	for(pos=0;pos<count;pos++){
		pp=PokeParty_GetMemberPointer(ppt,pos);
		if(PokeParaGet(pp,ID_PARA_monsno,NULL)){
			pokerus=PokeParaGet(pp,ID_PARA_pokerus,NULL);
			if(pokerus&0x0f){
				if(((pokerus&0x0f)<day)||(day>4)){
					pokerus&=0xf0;
				}
				else{
					pokerus-=day;
				}
				if(pokerus==0){
					pokerus=0x10;
				}
				PokeParaPut(pp,ID_PARA_pokerus,(u8 *)&pokerus);
			}
		}
	}
}

//============================================================================================
/**
 *	�|�P���X�̊����`�F�b�N���[�`��
 *
 * @param[in]	ppt	�������`�F�b�N����POKEPARTY�\���̂̃|�C���^
 */
//============================================================================================
void	PokerusCatchCheck(POKEPARTY *ppt)
{
	int	pos;
	int	count;
	u8	pokerus;
	POKEMON_PARAM	*pp;

	count=PokeParty_GetPokeCount(ppt);

	if(gf_rand()%3==0){
		for(pos=0;pos<count;pos++){
			pp=PokeParty_GetMemberPointer(ppt,pos);
			if(PokeParaGet(pp,ID_PARA_monsno,NULL)){
				pokerus=PokeParaGet(pp,ID_PARA_pokerus,NULL);
				if(pokerus&0x0f){
					if(pos!=0){
						pp=PokeParty_GetMemberPointer(ppt,pos-1);
						if((PokeParaGet(pp,ID_PARA_pokerus,NULL)&0xf0)==0){
							PokeParaPut(pp,ID_PARA_pokerus,(u8 *)&pokerus);
						}
					}
					if(pos<count-1){
						pp=PokeParty_GetMemberPointer(ppt,pos+1);
						if((PokeParaGet(pp,ID_PARA_pokerus,NULL)&0xf0)==0){
							PokeParaPut(pp,ID_PARA_pokerus,(u8 *)&pokerus);
							pos++;
						}
					}
				}
			}
		}
	}
}

//============================================================================================
/**
 *	�|�P���X�Ɋ������Ă��邩�`�F�b�N
 *
 * @param[in]	pp	�������`�F�b�N����POKEMON_PARAM�\���̂̃|�C���^
 *
 * @retval FALSE:�������Ă��Ȃ��@TRUE:�������Ă���
 */
//============================================================================================
BOOL	PokeParaPokerusCheck(POKEMON_PARAM *pp)
{
	return PokePasoParaPokerusCheck(&pp->ppp);
}

//============================================================================================
/**
 *	�|�P���X�Ɋ������Ă��邩�`�F�b�N
 *
 * @param[in]	ppp	�������`�F�b�N����POKEMON_PASO_PARAM�\���̂̃|�C���^
 *
 * @retval FALSE:�������Ă��Ȃ��@TRUE:�������Ă���
 */
//============================================================================================
BOOL	PokePasoParaPokerusCheck(POKEMON_PASO_PARAM *ppp)
{
	return ((PokePasoParaGet(ppp,ID_PARA_pokerus,NULL)&0x0f)!=0);
}

//============================================================================================
/**
 *	�ߋ��Ƀ|�P���X�Ɋ������Ă������`�F�b�N
 *
 * @param[in]	pp	�������`�F�b�N����POKEMON_PARAM�\���̂̃|�C���^
 *
 * @retval FALSE:�������Ă��Ȃ��@TRUE:�������Ă���
 */
//============================================================================================
BOOL	PokeParaPokerusedCheck(POKEMON_PARAM *pp)
{
	return PokePasoParaPokerusedCheck(&pp->ppp);
}

//============================================================================================
/**
 *	�ߋ��Ƀ|�P���X�Ɋ������Ă������`�F�b�N
 *
 * @param[in]	ppp	�������`�F�b�N����POKEMON_PASO_PARAM�\���̂̃|�C���^
 *
 * @retval FALSE:�������Ă��Ȃ��@TRUE:�������Ă���
 */
//============================================================================================
BOOL	PokePasoParaPokerusedCheck(POKEMON_PASO_PARAM *ppp)
{
	u8	pokerus;

	pokerus=PokePasoParaGet(ppp,ID_PARA_pokerus,NULL);
	
	//���A�������Ă���ꍇ�́AFALSE
	if(pokerus&0x0f){
		return FALSE;
	}

	return ((pokerus&0xf0)!=0);
}

//============================================================================================
/**
 *	��������𒲂ׂāA�A�E�X��form_no���Z�b�g
 *
 * @param[in]	pp	�Z�b�g����POKEMON_PARAM�\���̂̃|�C���^
 */
//============================================================================================
void	PokeParaAusuFormChange(POKEMON_PARAM *pp)
{
	PokePasoParaAusuFormChange(&pp->ppp);
}

//============================================================================================
/**
 *	��������𒲂ׂāA�A�E�X��form_no���Z�b�g
 *
 * @param[in]	ppp	�Z�b�g����POKEMON_PASO_PARAM�\���̂̃|�C���^
 */
//============================================================================================
void	PokePasoParaAusuFormChange(POKEMON_PASO_PARAM *ppp)
{
	int	monsno;
	int	speabino;
	int	item;
	int	form_no;

	monsno=PokePasoParaGet(ppp,ID_PARA_monsno,NULL);
	speabino=PokePasoParaGet(ppp,ID_PARA_speabino,NULL);
	item=PokePasoParaGet(ppp,ID_PARA_item,NULL);

	if((monsno==MONSNO_AUSU)&&(speabino==TOKUSYU_MARUTITAIPU)){
		form_no=AusuTypeGet(ItemParamGet(item,ITEM_PRM_EQUIP,HEAPID_BASE_SYSTEM));
		PokePasoParaPut(ppp,ID_PARA_form_no,&form_no);
	}
}

//============================================================================================
/**
 *	�������ʂ���A�E�X�̃^�C�v���擾
 *
 * @param[in]	item_param	�A�C�e���̑�������
 *
 * @retval	�^�C�v
 */
//============================================================================================
u8	AusuTypeGet(u16	item_param)
{
	u8	ret;

	switch(item_param){
	case SOUBI_AUSUHONOOUP:
		ret=FIRE_TYPE;
		break;
	case SOUBI_AUSUMIZUUP:
		ret=WATER_TYPE;
		break;
	case SOUBI_AUSUDENKIUP:
		ret=ELECTRIC_TYPE;
		break;
	case SOUBI_AUSUKUSAUP:
		ret=KUSA_TYPE;
		break;
	case SOUBI_AUSUKOORIUP:
		ret=KOORI_TYPE;
		break;
	case SOUBI_AUSUKAKUTOUUP:
		ret=BATTLE_TYPE;
		break;
	case SOUBI_AUSUDOKUBARIUP:
		ret=POISON_TYPE;
		break;
	case SOUBI_AUSUZIMENUP:
		ret=JIMEN_TYPE;
		break;
	case SOUBI_AUSUTORIUP:
		ret=HIKOU_TYPE;
		break;
	case SOUBI_AUSUESUPAAUP:
		ret=SP_TYPE;
		break;
	case SOUBI_AUSUMUSIIRYOKUUP:
		ret=MUSHI_TYPE;
		break;
	case SOUBI_AUSUIWAUP:
		ret=IWA_TYPE;
		break;
	case SOUBI_AUSUGOOSUTOUP:	
		ret=GHOST_TYPE;
		break;
	case SOUBI_AUSUDORAGONUP:	
		ret=DRAGON_TYPE;
		break;
	case SOUBI_AUSUAKUUP:	
		ret=AKU_TYPE;
		break;
	case SOUBI_AUSUHAGANEIRYOKUUP:	
		ret=METAL_TYPE;
		break;
	default:
		ret=NORMAL_TYPE;
		break;
	}
	return ret;
}

//============================================================================================
/**
 *	�Z�o���e�[�u���f�[�^���擾
 *
 * @param[in]	monsno		�擾����|�P�����i���o�[
 * @param[out]	wot		�擾�����Z�o���e�[�u���̊i�[��
 */
//============================================================================================
void	PokeWazaOboeDataGet(int monsno,u16 *wot)
{
	ArchiveDataLoad(wot,ARC_WOTBL,monsno);
}

//============================================================================================
/**
 *	�Z�o���e�[�u���f�[�^���擾
 *
 * @param[in]	monsno		�擾����|�P�����i���o�[
 * @param[in]	form_no		�擾����|�P�����̃t�H�����i���o�[
 * @param[out]	wot			�擾�����Z�o���e�[�u���̊i�[��
 */
//============================================================================================
void	PokeFormNoWazaOboeDataGet(int monsno,int form_no,u16 *wot)
{
	monsno=PokeOtherFormMonsNoGet(monsno,form_no);

	ArchiveDataLoad(wot,ARC_WOTBL,monsno);
}

//============================================================================================
/**
 *	�|�P���������Đ��i�؃��b�v���肠��j
 *
 * @param[in]	p_voice		�؃��b�v�̖����f�[�^�̓��������[�N
 * @param[in]	voice		Voice�p�^�[��
 * @param[in]	monsno		�����郂���X�^�[�i���o�[
 * @param[in]	pan			�p���f�[�^
 * @param[in]	vol			�{�����[���f�[�^
 * @param[in]	flag		�ւ񂵂�t���O
 * @param[in]	heapID		�q�[�vID
 */
//============================================================================================
void	PokeVoicePlaySet(PERAPVOICE *p_voice,int voice,u16 monsno,int pan,int vol,int flag,int heapID)
{
	if(monsno==MONSNO_PERAPPU){
		//�����Đ��p�^�[�����Z�n�̎��̓f�t�H���g�̖������Đ�����悤�ɂ���I
		if( Snd_PerapVoicePMVoiceTypeCheck( voice ) == FALSE ){
			Snd_PerapVoiceDefaultFlagSet( TRUE );		//default�̖������Đ�����t���OON
			Snd_PMVoicePlayEx(voice,monsno,pan,vol,heapID);
		}else{
			//�ւ񂵂�y���b�v�́Adefault�̖������Đ�
			if(flag){
				Snd_PerapVoiceDefaultFlagSet( TRUE );		//default�̖������Đ�����t���OON
			}
			Snd_PerapVoicePlay(p_voice,NULL,vol,pan);	//�^�������������Đ�
		}

	}
	else{
		Snd_PMVoicePlayEx(voice,monsno,pan,vol,heapID);
	}
}

//============================================================================================
/**
 *	�|�P�����ߊl�����i�[
 *
 * @param[in]	pp			�ߊl�����i�[����POKEMON_PARAM�\����
 * @param[in]	status		my_status�iIDNo�Ɛe���̎擾�ɕK�v�j
 * @param[in]	ball		�ߊl�{�[��
 * @param[in]	place		�ߊl�ꏊ�R�[�h
 * @param[in]	ground_id	�ߊl�ꏊ�A�g���r���[�g
 * @param[in]	heapID		�q�[�vID�i�e���i�[���̃o�b�t�@�����ɕK�v�j
 */
//============================================================================================
void	PokeParaGetInfoSet(POKEMON_PARAM *pp,MYSTATUS *status,int ball,int place,int ground_id,int heapID)
{
	int	data;

	PokePasoParaGetInfoSet(&pp->ppp,status,ball,place,ground_id,heapID);

	//�ߊl�����{�[�����q�[���{�[���Ȃ�΁AHP�S���A��Ԉُ���񕜂���
	if(ball==ITEM_HIIRUBOORU){
		data=PokeParaGet(pp,ID_PARA_hpmax,NULL);
		PokeParaPut(pp,ID_PARA_hp,&data);
		data=0;
		PokeParaPut(pp,ID_PARA_condition,&data);
	}
}

//============================================================================================
/**
 *	�|�P�����ߊl�����i�[
 *
 * @param[in]	ppp			�ߊl�����i�[����POKEMON_PASO_PARAM�\����
 * @param[in]	status		my_status�iIDNo�Ɛe���̎擾�ɕK�v�j
 * @param[in]	ball		�ߊl�{�[��
 * @param[in]	place		�ߊl�ꏊ�R�[�h
 * @param[in]	ground_id	�ߊl�ꏊ�A�g���r���[�g
 * @param[in]	heapID		�q�[�vID�i�e���i�[���̃o�b�t�@�����ɕK�v�j
 */
//============================================================================================
void	PokePasoParaGetInfoSet(POKEMON_PASO_PARAM *ppp,MYSTATUS *status,int ball,int place,int ground_id,int heapID)
{
//	RTCDate	rtc_d;
//	STRBUF	*str;

//	GF_RTC_GetDate(&rtc_d);

	//�ߊl���Ԃ��Z�b�g
//	PokePasoParaPut(ppp,ID_PARA_get_year,&rtc_d.year);
//	PokePasoParaPut(ppp,ID_PARA_get_month,&rtc_d.month);
//	PokePasoParaPut(ppp,ID_PARA_get_day,&rtc_d.day);

	//�ߊl�n����Z�b�g
//	PokePasoParaPut(ppp,ID_PARA_get_place,&place);

	//�ߊl���x�����Z�b�g
//	data=PokePasoParaGet(ppp,ID_PARA_level,NULL);
//	PokePasoParaPut(ppp,ID_PARA_get_level,&data);

	//IDNo���Z�b�g
//	data=MyStatus_GetID(status);
//	PokePasoParaPut(ppp,ID_PARA_id_no,&data);

	//�e�̐��ʂ��Z�b�g
//	data=MyStatus_GetMySex(status);
//	PokePasoParaPut(ppp,ID_PARA_oyasex,&data);

	//�e�����Z�b�g
//	str=MyStatus_CreateNameString(status,heapID);
//	PokePasoParaPut(ppp,ID_PARA_oyaname_buf,str);
//	STRBUF_Delete(str);

	//��̍��ڂ��ꊇ���Ċi�[����֐��ɒu������
	TrainerMemoSetPPP(ppp,status,TRMEMO_POKE_PLACESET,place,heapID);

	//�ߊl�J�Z�b�g�o�[�W�������Z�b�g
	PokePasoParaPut(ppp,ID_PARA_get_cassette,&CasetteVersion);
	//�ߊl�{�[�����Z�b�g
	PokePasoParaPut(ppp,ID_PARA_get_ball,&ball);

	//�ߊl�n�`�A�g���r���[�g���Z�b�g
	PokePasoParaPut(ppp,ID_PARA_get_ground_id,&ground_id);
}

//============================================================================================
/**
 *	�|�P�����z�������i�[
 *
 * @param[in]	pp			�z�������i�[����POKEMON_PARAM�\����
 * @param[in]	status		my_status�iIDNo�Ɛe���̎擾�ɕK�v�j
 * @param[in]	ball		�z���{�[��
 * @param[in]	place		�z���ꏊ�R�[�h
 * @param[in]	ground_id	�z���ꏊ�A�g���r���[�g
 * @param[in]	heapID		�q�[�vID�i�e���i�[���̃o�b�t�@�����ɕK�v�j
 */
//============================================================================================
void	PokeParaBirthInfoSet(POKEMON_PARAM *pp,MYSTATUS *status,int ball,int place,int ground_id,int heapID)
{
	PokePasoParaBirthInfoSet(&pp->ppp,status,ball,place,ground_id,heapID);
}

//============================================================================================
/**
 *	�|�P�����z�������i�[
 *
 * @param[in]	pp			�z�������i�[����POKEMON_PARAM�\����
 * @param[in]	status		my_status�iIDNo�Ɛe���̎擾�ɕK�v�j
 * @param[in]	ball		�z���{�[��
 * @param[in]	place		�z���ꏊ�R�[�h
 * @param[in]	ground_id	�z���ꏊ�A�g���r���[�g
 * @param[in]	heapID		�q�[�vID�i�e���i�[���̃o�b�t�@�����ɕK�v�j
 */
//============================================================================================
void	PokePasoParaBirthInfoSet(POKEMON_PASO_PARAM *ppp,MYSTATUS *status,int ball,int place,int ground_id,int heapID)
{
	int	data;
//	RTCDate	rtc_d;
//	STRBUF	*str;

	//�ߊl�����i�[
	PokePasoParaGetInfoSet(ppp,status,ball,place,ground_id,heapID);

//	GF_RTC_GetDate(&rtc_d);

	//�z�����Ԃ��Z�b�g
//	PokePasoParaPut(ppp,ID_PARA_birth_year,&rtc_d.year);
//	PokePasoParaPut(ppp,ID_PARA_birth_month,&rtc_d.month);
//	PokePasoParaPut(ppp,ID_PARA_birth_day,&rtc_d.day);

	//�z���n����Z�b�g
//	PokePasoParaPut(ppp,ID_PARA_birth_place,&place);
}

//============================================================================================
/**
 *	�쐫�|�P�����Ɏ�������A�C�e���̃Z�b�g
 *
 * @param[in]	pp			�A�C�e������������POKEMON_PARAM�\����
 * @param[in]	fight_type	�퓬�^�C�v
 * @param[in]	range		�m���e�[�u��ID�ipoke_tool.h�ɒ�`�j
 */
//============================================================================================
static const u16 ItemRangeTable[][2]={
	{45,95},		//ITEM_RANGE_NORMAL
	{20,80},		//ITEM_RANGE_HUKUGAN
};

void	PokeItemSet(POKEMON_PARAM *pp,u32 fight_type,int range)
{
	int	i;
	u32	rnd;
	u16	monsno;
	u16	formno;
	u8	spa;
	u16	item1,item2;

	if(fight_type&(FIGHT_TYPE_POKE_NO_HAVE_ITEM)){
		return;
	}

	rnd=gf_rand()%100;
	monsno=PokeParaGet(pp,ID_PARA_monsno,NULL);
	formno=PokeParaGet(pp,ID_PARA_form_no,NULL);
	item1=PokeFormNoPersonalParaGet(monsno,formno,ID_PER_item1);
	item2=PokeFormNoPersonalParaGet(monsno,formno,ID_PER_item2);

	//�A�C�e���f�[�^�ɗ��������i���o�[�������Ă���ꍇ�́A�K����������
	if((item1==item2)&&(item1!=0)){
		PokeParaPut(pp,ID_PARA_item,&item1);
		return;
	}
	if(rnd<ItemRangeTable[range][0]){
		return;
	}
	else if(rnd<ItemRangeTable[range][1]){
		PokeParaPut(pp,ID_PARA_item,&item1);
	}
	else{
		PokeParaPut(pp,ID_PARA_item,&item2);
	}
}

//============================================================================================
/**
 *	�|�P�����ɋZ�}�V�����g���邩�`�F�b�N
 *
 * @param[in]	pp			�`�F�b�N����POKEMON_PARAM�\����
 * @param[in]	machine_no	�`�F�b�N����Z�}�V���i���o�[
 *
 * @retval	FALSE:�g���Ȃ��@TRUE:�g����
 */
//============================================================================================
BOOL	PokeParaWazaMachineCheck(POKEMON_PARAM *pp,u8 machine_no)
{
	return	PokePasoParaWazaMachineCheck(&pp->ppp,machine_no);
}

//============================================================================================
/**
 *	�|�P�����ɋZ�}�V�����g���邩�`�F�b�N
 *
 * @param[in]	ppp			�`�F�b�N����POKEMON_PASO_PARAM�\����
 * @param[in]	machine_no	�`�F�b�N����Z�}�V���i���o�[
 *
 * @retval	FALSE:�g���Ȃ��@TRUE:�g����
 */
//============================================================================================
BOOL	PokePasoParaWazaMachineCheck(POKEMON_PASO_PARAM *ppp,u8 machine_no)
{
	u16	mons_no;
	int	form_no;

	mons_no=PokePasoParaGet(ppp,ID_PARA_monsno_egg,NULL);
	form_no=PokePasoParaGet(ppp,ID_PARA_form_no,NULL);

	return	PokeWazaMachineCheck(mons_no,form_no,machine_no);
}

//============================================================================================
/**
 *	�|�P�����ɋZ�}�V�����g���邩�`�F�b�N
 *
 * @param[in]	mons_no		�`�F�b�N����|�P�����i���o�[
 * @param[in]	form_no		�`�F�b�N����t�H�����i���o�[
 * @param[in]	machine_no	�`�F�b�N����Z�}�V���i���o�[
 *
 * @retval	FALSE:�g���Ȃ��@TRUE:�g����
 */
//============================================================================================
BOOL	PokeWazaMachineCheck(u16 mons_no,int form_no,u8 machine_no)
{
	u32	machine_bit;
	u8	perID;

	if(mons_no==MONSNO_TAMAGO){
		return FALSE;
	}

	if(machine_no<32){
		machine_bit=(1<<machine_no);
		perID=ID_PER_machine1;
	}
	else if(machine_no<64){
		machine_bit=(1<<(machine_no-32));
		perID=ID_PER_machine2;
	}
	else if(machine_no<96){
		machine_bit=(1<<(machine_no-64));
		perID=ID_PER_machine3;
	}
	else{
		machine_bit=(1<<(machine_no-96));
		perID=ID_PER_machine4;
	}

	return ((PokeFormNoPersonalParaGet(mons_no,form_no,perID)&machine_bit)!=0);
}

//============================================================================================
/**
 *	�|�P�����ɓ������Z�b�g
 *
 * @param[in]	pp		POKEMON_PARAM�\���̂̃|�C���^
 */
//============================================================================================
void	PokeParaSpeabiSet(POKEMON_PARAM *pp)
{
	PokePasoParaSpeabiSet(&pp->ppp);
}

//============================================================================================
/**
 *	�|�P�����ɓ������Z�b�g
 *
 * @param[in]	ppp		POKEMON_PASO_PARAM�\���̂̃|�C���^
 */
//============================================================================================
void	PokePasoParaSpeabiSet(POKEMON_PASO_PARAM *ppp)
{
	BOOL	fastMode;
	int		mons_no;
	int		speabi1,speabi2;
	u32		rnd;

	fastMode = PokePasoParaFastModeOn( ppp );

	mons_no=PokePasoParaGet(ppp,ID_PARA_monsno,NULL);
	rnd=PokePasoParaGet(ppp,ID_PARA_personal_rnd,NULL);

//����\�̓Z�b�g
	speabi1=PokePersonalParaGet(mons_no,ID_PER_speabi1);
	speabi2=PokePersonalParaGet(mons_no,ID_PER_speabi2);

	if(speabi2!=0){
		if(rnd&1){
			PokePasoParaPut(ppp,ID_PARA_speabino,(u8 *)&speabi2);
		}
		else{
			PokePasoParaPut(ppp,ID_PARA_speabino,(u8 *)&speabi1);
		}
	}
	else{
		PokePasoParaPut(ppp,ID_PARA_speabino,(u8 *)&speabi1);
	}

	PokePasoParaFastModeOff( ppp, fastMode );
}

//============================================================================================
/**
 *	������������������i���������L�[�ɂ��Ă�����̂�����̂ŁA��p�֐��ɂ���j
 *
 * @param[in]	pp				POKEMON_PARAM�\���̂̃|�C���^
 * @param[in]	personal_rnd	���������������
 */
//============================================================================================
void	PokeParaPersonalRndChange(POKEMON_PARAM *pp,u32 personal_rnd)
{
	POKEMON_PARAM		*pp_temp;
	POKEMON_PASO_PARAM1	*ppp1_src;
	POKEMON_PASO_PARAM2	*ppp2_src;
	POKEMON_PASO_PARAM3	*ppp3_src;
	POKEMON_PASO_PARAM4	*ppp4_src;
	POKEMON_PASO_PARAM1	*ppp1_dest;
	POKEMON_PASO_PARAM2	*ppp2_dest;
	POKEMON_PASO_PARAM3	*ppp3_dest;
	POKEMON_PASO_PARAM4	*ppp4_dest;

	pp_temp=PokemonParam_AllocWork(HEAPID_BASE_SYSTEM);

	PokeCopyPPtoPP(pp,pp_temp);

	ppp1_src=(POKEMON_PASO_PARAM1 *)PokeParaAdrsGet(&pp_temp->ppp,pp->ppp.personal_rnd,ID_POKEPARA1);
	ppp2_src=(POKEMON_PASO_PARAM2 *)PokeParaAdrsGet(&pp_temp->ppp,pp->ppp.personal_rnd,ID_POKEPARA2);
	ppp3_src=(POKEMON_PASO_PARAM3 *)PokeParaAdrsGet(&pp_temp->ppp,pp->ppp.personal_rnd,ID_POKEPARA3);
	ppp4_src=(POKEMON_PASO_PARAM4 *)PokeParaAdrsGet(&pp_temp->ppp,pp->ppp.personal_rnd,ID_POKEPARA4);
	ppp1_dest=(POKEMON_PASO_PARAM1 *)PokeParaAdrsGet(&pp->ppp,personal_rnd,ID_POKEPARA1);
	ppp2_dest=(POKEMON_PASO_PARAM2 *)PokeParaAdrsGet(&pp->ppp,personal_rnd,ID_POKEPARA2);
	ppp3_dest=(POKEMON_PASO_PARAM3 *)PokeParaAdrsGet(&pp->ppp,personal_rnd,ID_POKEPARA3);
	ppp4_dest=(POKEMON_PASO_PARAM4 *)PokeParaAdrsGet(&pp->ppp,personal_rnd,ID_POKEPARA4);

	PokeParaDecoded(&pp_temp->ppp.paradata,sizeof(POKEMON_PASO_PARAM1)*4,pp_temp->ppp.checksum);
	PokeParaDecoded(&pp->pcp,sizeof(POKEMON_CALC_PARAM),pp->ppp.personal_rnd);
	PokeParaDecoded(&pp->ppp.paradata,sizeof(POKEMON_PASO_PARAM1)*4,pp->ppp.checksum);

	pp->ppp.personal_rnd=personal_rnd;

	*ppp1_dest=*ppp1_src;
	*ppp2_dest=*ppp2_src;
	*ppp3_dest=*ppp3_src;
	*ppp4_dest=*ppp4_src;

	pp->ppp.checksum=PokeParaCheckSum(&pp->ppp.paradata,sizeof(POKEMON_PASO_PARAM1)*4);
	PokeParaCoded(&pp->ppp.paradata,sizeof(POKEMON_PASO_PARAM1)*4,pp->ppp.checksum);
	PokeParaCoded(&pp->pcp,sizeof(POKEMON_CALC_PARAM),pp->ppp.personal_rnd);

	sys_FreeMemoryEz(pp_temp);
}

//============================================================================================
/**
 *							�O�����J���Ȃ��֐��S
 */
//============================================================================================
//============================================================================================
/**
 *	�|�P�����p�[�\�i���\���̃f�[�^���擾
 *
 * @param[in]	mons_no	�擾�������|�P�����i���o�[
 * @param[out]	ppd		�擾�����p�[�\�i���f�[�^�̊i�[����w��
 */
//============================================================================================
static	void	PokePersonalDataGet(int mons_no,POKEMON_PERSONAL_DATA *ppd)
{
	ArchiveDataLoad(ppd,ARC_PERSONAL,mons_no);
}

//============================================================================================
/**
 *	�|�P�����p�[�\�i���\���̃f�[�^���擾
 *
 * @param[in]	mons_no	�擾�������|�P�����i���o�[
 * @param[in]	form_no	�擾�������|�P�����̃t�H�����i���o�[
 * @param[out]	ppd		�擾�����p�[�\�i���f�[�^�̊i�[����w��
 */
//============================================================================================
static	void	PokeFormNoPersonalDataGet(int mons_no,int form_no,POKEMON_PERSONAL_DATA *ppd)
{
	mons_no=PokeOtherFormMonsNoGet(mons_no,form_no);

	ArchiveDataLoad(ppd,ARC_PERSONAL,mons_no);
}

//============================================================================================
/**
 *	�i���e�[�u���\���̃f�[�^���擾
 *
 * @param[in]	mons_no	�擾�������|�P�����i���o�[
 * @param[out]	psd		�擾�����i���f�[�^�̊i�[����w��
 */
//============================================================================================
static	void	PokeShinkaDataGet(int mons_no,POKEMON_SHINKA_TABLE *pst)
{
	ArchiveDataLoad(pst,ARC_EVO,mons_no);
}


//============================================================================================
/**
 *	�Í�����
 *
 * @param[in]	data	�Í�������f�[�^�̃|�C���^
 * @param[in]	size	�Í�������f�[�^�̃T�C�Y
 * @param[in]	code	�Í����L�[�̏����l
 */
//============================================================================================
static	void	PokeParaCoded(void *data,u32 size,u32 code)
{
	int	i;
	u16	*data_p=(u16 *)data;

	//�Í��́A�����Í��L�[�Ń}�X�N
	for(i=0;i<size/2;i++){
		data_p[i]^=CodeRand(&code);
	}
}

//============================================================================================
/**
 *	��������
 *
 * @param[in]	data	��������f�[�^�̃|�C���^
 * @param[in]	size	��������f�[�^�̃T�C�Y
 * @param[in]	code	�Í����L�[�̏����l
 */
//============================================================================================
static	void	PokeParaDecoded(void *data,u32 size,u32 code)
{
	PokeParaCoded(data,size,code);
}

//============================================================================================
/**
 *	�����Í��L�[�������[�`��
 *
 * @param[in,out]	code	�Í��L�[�i�[���[�N�̃|�C���^
 *
 * @return	�Í��L�[�i�[���[�N�̏��2�o�C�g���Í��L�[�Ƃ��ĕԂ�
 */
//============================================================================================

static	u16 CodeRand(u32 *code)
{
    code[0] = code[0] *1103515245L + 24691;
    return (u16)(code[0] / 65536L) ;
}

//============================================================================================
/**
 *	�|�P�����p�����[�^�̃`�F�b�N�T���𐶐�
 *
 * @param[in]	data	�|�P�����p�����[�^�\���̂̃|�C���^
 * @param[in]	size	�`�F�b�N�T���𐶐�����f�[�^�̃T�C�Y
 *
 * @return	���������`�F�b�N�T��
 */
//============================================================================================
static	u16	PokeParaCheckSum(void *data,u32	size)
{
	int	i;
	u16	*data_p=(u16 *)data;
	u16	sum=0;

	for(i=0;i<size/2;i++){
		sum+=data_p[i];
	}

	return sum;
}

//============================================================================================
/**
 *	�{�b�N�X�|�P�����p�����[�^�\���̓��̃����o�̃A�h���X���擾
 *
 * @param[in]	ppp	�擾�������{�b�N�X�|�P�����p�����[�^�\���̂̃|�C���^
 * @param[in]	rnd	�\���̓���ւ��̃L�[
 * @param[in]	id	���o�����������o�̃C���f�b�N�X�ipoke_tool.h�ɒ�`�j
 *
 * @return	�擾�����A�h���X
 */
//============================================================================================
static	void	*PokeParaAdrsGet(POKEMON_PASO_PARAM *ppp,u32 rnd,u8 id)
{
	void	*ret;
	rnd=(rnd&0x0003e000)>>13;

	GF_ASSERT_MSG(rnd<=ID_POKEPARADATA62,"PokeParaAdrsGet:Index Over!");

	switch(rnd){
	case ID_POKEPARADATA11:
	case ID_POKEPARADATA51:
		{
			POKEMON_PARA_DATA11 *PPD11=(POKEMON_PARA_DATA11 *)&ppp->paradata;
			switch(id){
				case ID_POKEPARA1:
					ret=&PPD11->ppp1;
					break;
				case ID_POKEPARA2:
					ret=&PPD11->ppp2;
					break;
				case ID_POKEPARA3:
					ret=&PPD11->ppp3;
					break;
				case ID_POKEPARA4:
					ret=&PPD11->ppp4;
					break;
			}
			break;
		}
	case ID_POKEPARADATA12:
	case ID_POKEPARADATA52:
		{
			POKEMON_PARA_DATA12 *PPD12=(POKEMON_PARA_DATA12 *)&ppp->paradata;
			switch(id){
				case ID_POKEPARA1:
					ret=&PPD12->ppp1;
					break;
				case ID_POKEPARA2:
					ret=&PPD12->ppp2;
					break;
				case ID_POKEPARA3:
					ret=&PPD12->ppp3;
					break;
				case ID_POKEPARA4:
					ret=&PPD12->ppp4;
					break;
			}
			break;
		}
	case ID_POKEPARADATA13:
	case ID_POKEPARADATA53:
		{
			POKEMON_PARA_DATA13 *PPD13=(POKEMON_PARA_DATA13 *)&ppp->paradata;
			switch(id){
				case ID_POKEPARA1:
					ret=&PPD13->ppp1;
					break;
				case ID_POKEPARA2:
					ret=&PPD13->ppp2;
					break;
				case ID_POKEPARA3:
					ret=&PPD13->ppp3;
					break;
				case ID_POKEPARA4:
					ret=&PPD13->ppp4;
					break;
			}
			break;
		}
	case ID_POKEPARADATA14:
	case ID_POKEPARADATA54:
		{
			POKEMON_PARA_DATA14 *PPD14=(POKEMON_PARA_DATA14 *)&ppp->paradata;
			switch(id){
				case ID_POKEPARA1:
					ret=&PPD14->ppp1;
					break;
				case ID_POKEPARA2:
					ret=&PPD14->ppp2;
					break;
				case ID_POKEPARA3:
					ret=&PPD14->ppp3;
					break;
				case ID_POKEPARA4:
					ret=&PPD14->ppp4;
					break;
			}
			break;
		}
	case ID_POKEPARADATA15:
	case ID_POKEPARADATA55:
		{
			POKEMON_PARA_DATA15 *PPD15=(POKEMON_PARA_DATA15 *)&ppp->paradata;
			switch(id){
				case ID_POKEPARA1:
					ret=&PPD15->ppp1;
					break;
				case ID_POKEPARA2:
					ret=&PPD15->ppp2;
					break;
				case ID_POKEPARA3:
					ret=&PPD15->ppp3;
					break;
				case ID_POKEPARA4:
					ret=&PPD15->ppp4;
					break;
			}
			break;
		}
	case ID_POKEPARADATA16:
	case ID_POKEPARADATA56:
		{
			POKEMON_PARA_DATA16 *PPD16=(POKEMON_PARA_DATA16 *)&ppp->paradata;
			switch(id){
				case ID_POKEPARA1:
					ret=&PPD16->ppp1;
					break;
				case ID_POKEPARA2:
					ret=&PPD16->ppp2;
					break;
				case ID_POKEPARA3:
					ret=&PPD16->ppp3;
					break;
				case ID_POKEPARA4:
					ret=&PPD16->ppp4;
					break;
			}
			break;
		}
	case ID_POKEPARADATA21:
	case ID_POKEPARADATA61:
		{
			POKEMON_PARA_DATA21 *PPD21=(POKEMON_PARA_DATA21 *)&ppp->paradata;
			switch(id){
				case ID_POKEPARA1:
					ret=&PPD21->ppp1;
					break;
				case ID_POKEPARA2:
					ret=&PPD21->ppp2;
					break;
				case ID_POKEPARA3:
					ret=&PPD21->ppp3;
					break;
				case ID_POKEPARA4:
					ret=&PPD21->ppp4;
					break;
			}
			break;
		}
	case ID_POKEPARADATA22:
	case ID_POKEPARADATA62:
		{
			POKEMON_PARA_DATA22 *PPD22=(POKEMON_PARA_DATA22 *)&ppp->paradata;
			switch(id){
				case ID_POKEPARA1:
					ret=&PPD22->ppp1;
					break;
				case ID_POKEPARA2:
					ret=&PPD22->ppp2;
					break;
				case ID_POKEPARA3:
					ret=&PPD22->ppp3;
					break;
				case ID_POKEPARA4:
					ret=&PPD22->ppp4;
					break;
			}
			break;
		}
	case ID_POKEPARADATA23:
		{
			POKEMON_PARA_DATA23 *PPD23=(POKEMON_PARA_DATA23 *)&ppp->paradata;
			switch(id){
				case ID_POKEPARA1:
					ret=&PPD23->ppp1;
					break;
				case ID_POKEPARA2:
					ret=&PPD23->ppp2;
					break;
				case ID_POKEPARA3:
					ret=&PPD23->ppp3;
					break;
				case ID_POKEPARA4:
					ret=&PPD23->ppp4;
					break;
			}
			break;
		}
	case ID_POKEPARADATA24:
		{
			POKEMON_PARA_DATA24 *PPD24=(POKEMON_PARA_DATA24 *)&ppp->paradata;
			switch(id){
				case ID_POKEPARA1:
					ret=&PPD24->ppp1;
					break;
				case ID_POKEPARA2:
					ret=&PPD24->ppp2;
					break;
				case ID_POKEPARA3:
					ret=&PPD24->ppp3;
					break;
				case ID_POKEPARA4:
					ret=&PPD24->ppp4;
					break;
			}
			break;
		}
	case ID_POKEPARADATA25:
		{
			POKEMON_PARA_DATA25 *PPD25=(POKEMON_PARA_DATA25 *)&ppp->paradata;
			switch(id){
				case ID_POKEPARA1:
					ret=&PPD25->ppp1;
					break;
				case ID_POKEPARA2:
					ret=&PPD25->ppp2;
					break;
				case ID_POKEPARA3:
					ret=&PPD25->ppp3;
					break;
				case ID_POKEPARA4:
					ret=&PPD25->ppp4;
					break;
			}
			break;
		}
	case ID_POKEPARADATA26:
		{
			POKEMON_PARA_DATA26 *PPD26=(POKEMON_PARA_DATA26 *)&ppp->paradata;
			switch(id){
				case ID_POKEPARA1:
					ret=&PPD26->ppp1;
					break;
				case ID_POKEPARA2:
					ret=&PPD26->ppp2;
					break;
				case ID_POKEPARA3:
					ret=&PPD26->ppp3;
					break;
				case ID_POKEPARA4:
					ret=&PPD26->ppp4;
					break;
			}
			break;
		}
	case ID_POKEPARADATA31:
		{
			POKEMON_PARA_DATA31 *PPD31=(POKEMON_PARA_DATA31 *)&ppp->paradata;
			switch(id){
				case ID_POKEPARA1:
					ret=&PPD31->ppp1;
					break;
				case ID_POKEPARA2:
					ret=&PPD31->ppp2;
					break;
				case ID_POKEPARA3:
					ret=&PPD31->ppp3;
					break;
				case ID_POKEPARA4:
					ret=&PPD31->ppp4;
					break;
			}
			break;
		}
	case ID_POKEPARADATA32:
		{
			POKEMON_PARA_DATA32 *PPD32=(POKEMON_PARA_DATA32 *)&ppp->paradata;
			switch(id){
				case ID_POKEPARA1:
					ret=&PPD32->ppp1;
					break;
				case ID_POKEPARA2:
					ret=&PPD32->ppp2;
					break;
				case ID_POKEPARA3:
					ret=&PPD32->ppp3;
					break;
				case ID_POKEPARA4:
					ret=&PPD32->ppp4;
					break;
			}
			break;
		}
	case ID_POKEPARADATA33:
		{
			POKEMON_PARA_DATA33 *PPD33=(POKEMON_PARA_DATA33 *)&ppp->paradata;
			switch(id){
				case ID_POKEPARA1:
					ret=&PPD33->ppp1;
					break;
				case ID_POKEPARA2:
					ret=&PPD33->ppp2;
					break;
				case ID_POKEPARA3:
					ret=&PPD33->ppp3;
					break;
				case ID_POKEPARA4:
					ret=&PPD33->ppp4;
					break;
			}
			break;
		}
	case ID_POKEPARADATA34:
		{
			POKEMON_PARA_DATA34 *PPD34=(POKEMON_PARA_DATA34 *)&ppp->paradata;
			switch(id){
				case ID_POKEPARA1:
					ret=&PPD34->ppp1;
					break;
				case ID_POKEPARA2:
					ret=&PPD34->ppp2;
					break;
				case ID_POKEPARA3:
					ret=&PPD34->ppp3;
					break;
				case ID_POKEPARA4:
					ret=&PPD34->ppp4;
					break;
			}
			break;
		}
	case ID_POKEPARADATA35:
		{
			POKEMON_PARA_DATA35 *PPD35=(POKEMON_PARA_DATA35 *)&ppp->paradata;
			switch(id){
				case ID_POKEPARA1:
					ret=&PPD35->ppp1;
					break;
				case ID_POKEPARA2:
					ret=&PPD35->ppp2;
					break;
				case ID_POKEPARA3:
					ret=&PPD35->ppp3;
					break;
				case ID_POKEPARA4:
					ret=&PPD35->ppp4;
					break;
			}
			break;
		}
	case ID_POKEPARADATA36:
		{
			POKEMON_PARA_DATA36 *PPD36=(POKEMON_PARA_DATA36 *)&ppp->paradata;
			switch(id){
				case ID_POKEPARA1:
					ret=&PPD36->ppp1;
					break;
				case ID_POKEPARA2:
					ret=&PPD36->ppp2;
					break;
				case ID_POKEPARA3:
					ret=&PPD36->ppp3;
					break;
				case ID_POKEPARA4:
					ret=&PPD36->ppp4;
					break;
			}
			break;
		}
	case ID_POKEPARADATA41:
		{
			POKEMON_PARA_DATA41 *PPD41=(POKEMON_PARA_DATA41 *)&ppp->paradata;
			switch(id){
				case ID_POKEPARA1:
					ret=&PPD41->ppp1;
					break;
				case ID_POKEPARA2:
					ret=&PPD41->ppp2;
					break;
				case ID_POKEPARA3:
					ret=&PPD41->ppp3;
					break;
				case ID_POKEPARA4:
					ret=&PPD41->ppp4;
					break;
			}
			break;
		}
	case ID_POKEPARADATA42:
		{
			POKEMON_PARA_DATA42 *PPD42=(POKEMON_PARA_DATA42 *)&ppp->paradata;
			switch(id){
				case ID_POKEPARA1:
					ret=&PPD42->ppp1;
					break;
				case ID_POKEPARA2:
					ret=&PPD42->ppp2;
					break;
				case ID_POKEPARA3:
					ret=&PPD42->ppp3;
					break;
				case ID_POKEPARA4:
					ret=&PPD42->ppp4;
					break;
			}
			break;
		}
	case ID_POKEPARADATA43:
		{
			POKEMON_PARA_DATA43 *PPD43=(POKEMON_PARA_DATA43 *)&ppp->paradata;
			switch(id){
				case ID_POKEPARA1:
					ret=&PPD43->ppp1;
					break;
				case ID_POKEPARA2:
					ret=&PPD43->ppp2;
					break;
				case ID_POKEPARA3:
					ret=&PPD43->ppp3;
					break;
				case ID_POKEPARA4:
					ret=&PPD43->ppp4;
					break;
			}
			break;
		}
	case ID_POKEPARADATA44:
		{
			POKEMON_PARA_DATA44 *PPD44=(POKEMON_PARA_DATA44 *)&ppp->paradata;
			switch(id){
				case ID_POKEPARA1:
					ret=&PPD44->ppp1;
					break;
				case ID_POKEPARA2:
					ret=&PPD44->ppp2;
					break;
				case ID_POKEPARA3:
					ret=&PPD44->ppp3;
					break;
				case ID_POKEPARA4:
					ret=&PPD44->ppp4;
					break;
			}
			break;
		}
	case ID_POKEPARADATA45:
		{
			POKEMON_PARA_DATA45 *PPD45=(POKEMON_PARA_DATA45 *)&ppp->paradata;
			switch(id){
				case ID_POKEPARA1:
					ret=&PPD45->ppp1;
					break;
				case ID_POKEPARA2:
					ret=&PPD45->ppp2;
					break;
				case ID_POKEPARA3:
					ret=&PPD45->ppp3;
					break;
				case ID_POKEPARA4:
					ret=&PPD45->ppp4;
					break;
			}
			break;
		}
	case ID_POKEPARADATA46:
		{
			POKEMON_PARA_DATA46 *PPD46=(POKEMON_PARA_DATA46 *)&ppp->paradata;
			switch(id){
				case ID_POKEPARA1:
					ret=&PPD46->ppp1;
					break;
				case ID_POKEPARA2:
					ret=&PPD46->ppp2;
					break;
				case ID_POKEPARA3:
					ret=&PPD46->ppp3;
					break;
				case ID_POKEPARA4:
					ret=&PPD46->ppp4;
					break;
			}
			break;
		}
	}
	return	ret;
}

//--------------------------------------------------------------
/**
 * @brief	�ʃt�H�����̃����X�^�[�i���o�[�̎擾
 *
 * @param	mons_no	�擾���郂���X�^�[�i���o�[
 * @param	form_no	�擾����t�H�����i���o�[
 *
 * @retval	mons_no	
 */
//--------------------------------------------------------------
static	int	PokeOtherFormMonsNoGet(int mons_no,int form_no)
{
	//�t�H�����ɂ���āA�p�[�\�i�����ω�������̂��`�F�b�N
	switch(mons_no){
	case MONSNO_DEOKISISU:
		if((form_no)&&(form_no<=FORMNO_DEOKISISU_MAX)){
			mons_no=DEOKISISU_OTHER_FORM_PERSONAL+form_no;
		}
		break;
	case MONSNO_MINOMESU:
		if((form_no)&&(form_no<=FORMNO_MINOMUTTI_MAX)){
			mons_no=MINOMESU_OTHER_FORM_PERSONAL+form_no;
		}
		break;
	default:
		break;
	}

	return mons_no;
}

//============================================================================================
/**
 *	No��Bit�ɕϊ�(�R�P�܂Łj
 *
 * @param[in]	no		�ϊ�����i���o�[
 *
 * @retval	no=0:0x01 �c
 */
//============================================================================================
u32	No2Bit(int no)
{
	int	i;
	u32	ret=1;

	GF_ASSERT(no<32);

	for(i=0;i<no;i++){
		ret<<=1;
	}
	return ret;
}

//============================================================================================
/**
 *	Bit��No�ɕϊ�(�R�P�܂Łj
 *
 * @param[in]	bit		�ϊ�����i���o�[
 *
 * @retval	no=0x01:0�c
 */
//============================================================================================
int	Bit2No(u32 bit)
{
	int	i;
	u32	mask=1;

	for(i=0;i<32;i++){
		if(bit&mask){
			break;
		}
		mask<<=1;
	}
	return i;
}


//============================================================================================
/**
 *	�o�g���^���[�ɎQ���ł��Ȃ��|�P���������`�F�b�N�i�|�P�����ԍ�����j
 *
 * @param	mons	�|�P�����ԍ�
 *
 * @retval	"TRUE = �����ł�"
 * @retval	"FALSE = �Ⴂ�܂�"
 */
//============================================================================================
static const u16 BattleTowerExPoke[BTOWER_EXPOKE_NUM] = {
	MONSNO_MYUUTUU,
	MONSNO_MYUU,
	MONSNO_HOUOU,
	MONSNO_RUGIA,
	MONSNO_SEREBHI,
	MONSNO_KAIOOGA,
	MONSNO_GURAADON,
	MONSNO_REKKUUZA,
	MONSNO_ZIRAATI,
	MONSNO_DEOKISISU,
	MONSNO_IA,
	MONSNO_EA,
	MONSNO_KIMAIRAN,
	MONSNO_ERUFI,
	MONSNO_MANAFI,
	MONSNO_DAAKU,
	MONSNO_EURISU,
	MONSNO_AUSU
};

BOOL BattleTowerExPokeCheck_MonsNo( u16 mons )
{
	u32	i;

	for( i=0; i<NELEMS(BattleTowerExPoke); i++ ){
		if( mons == BattleTowerExPoke[i] ){
			return TRUE;
		}
	}
	return FALSE;
}

//�Q���s�\�ȃ|�P�����̃����X�^�[No��Ԃ�
u16 BattleTowerExPoke_MonsNoGet(u8 idx)
{
	if(idx >= NELEMS(BattleTowerExPoke)){
		idx = 0;
	}
	return BattleTowerExPoke[idx];
}

//============================================================================================
/**
 *	�o�g���^���[�ɎQ���ł��Ȃ��|�P���������`�F�b�N�iPOKEMON_PARAM����j
 *
 * @param	pp		POKEMON_PARAM
 *
 * @retval	"TRUE = �����ł�"
 * @retval	"FALSE = �Ⴂ�܂�"
 */
//============================================================================================
BOOL BattleTowerExPokeCheck_PokePara( POKEMON_PARAM * pp )
{
	u16 mons = (u16)PokeParaGet( pp, ID_PARA_monsno, NULL );

	return BattleTowerExPokeCheck_MonsNo( mons );
}

//============================================================================================
/**
 * @brief	�����̃|�P�������`�F�b�N
 * @param	pp		�Ώۃ|�P�����f�[�^
 * @param	my		�v���[���[�f�[�^
 * @retval	FALSE:���l�̃|�P�����@TRUE:�����̃|�P����
 */
//============================================================================================
BOOL	PokemonOyaCheckPP( POKEMON_PARAM* pp, MYSTATUS* my, int heapID )
{
#if 0
	u32		myID	= MyStatus_GetID( my );
	u32		oyaID	= PokeParaGet( pp, ID_PARA_id_no, NULL);
	u32		mysex	= MyStatus_GetMySex( my );
	u32		oyasex	= PokeParaGet( pp, ID_PARA_oyasex, NULL);
	STRBUF*	myname	= MyStatus_CreateNameString( my, heapID );
	STRBUF*	oyaname = STRBUF_Create( BUFLEN_PERSON_NAME, heapID );

	PokeParaGet( pp, ID_PARA_oyaname_buf, oyaname );

	if(( myID == oyaID )&&( mysex == oyasex )&&( STRBUF_Compare( myname, oyaname ) == 0 )){
		return TRUE;
	} else {
		return FALSE;
	}
#endif
	return PokemonOyaCheckPPP(&pp->ppp,my,heapID);
}

BOOL	PokemonOyaCheckPPP( POKEMON_PASO_PARAM* ppp, MYSTATUS* my, int heapID )
{
	u32		myID	= MyStatus_GetID( my );
	u32		oyaID	= PokePasoParaGet( ppp, ID_PARA_id_no, NULL);
	u32		mysex	= MyStatus_GetMySex( my );
	u32		oyasex	= PokePasoParaGet( ppp, ID_PARA_oyasex, NULL);
	STRBUF*	myname	= MyStatus_CreateNameString( my, heapID );
	STRBUF*	oyaname = STRBUF_Create( BUFLEN_PERSON_NAME, heapID );
	BOOL	result	= FALSE;

	PokePasoParaGet( ppp, ID_PARA_oyaname_buf, oyaname );

	if(( myID == oyaID )&&( mysex == oyasex )&&( STRBUF_Compare( myname, oyaname ) == 0 )){
		result = TRUE;
	}
	STRBUF_Delete( oyaname );
	STRBUF_Delete( myname );

	return result;
}

//============================================================================================
/**
 * @brief	�g���[�i�[�̔w��trtype���擾
 *
 * @param	trtype		�擾����trtype
 *
 * @retval	�ϊ�����trtype
 */
//============================================================================================
int	TrainerBTrTypeGet(int trtype)
{
	//�w�ʂ͂��ׂĂ�trtype�ɑΉ����Ă��Ȃ��̂ŁA�Ή����Ă�����̂����ϊ�
	switch(trtype){
	case TRTYPE_BOY:		//�j��l��
	case TRTYPE_GIRL:		//����l��
		//���̂܂܂�OK
		break;
	case TRTYPE_RIVAL:		//���C�o��
		trtype=TRTYPE_TRB_RIVAL;
		break;
	case TRTYPE_BTFIVE1:	//�ܐl�O
	case TRTYPE_BTFIVE2:	//�ܐl�O
	case TRTYPE_BTFIVE3:	//�ܐl�O
	case TRTYPE_BTFIVE4:	//�ܐl�O
	case TRTYPE_BTFIVE5:	//�ܐl�O
		trtype=TRTYPE_TRB_BTFIVE1+(trtype-TRTYPE_BTFIVE1);
		break;
	default:
		//���j�I���ΐ�ŁA�w�ʂ̂Ȃ�trtype������̂ŁA���ʂ����킹��
		if(TT_TrainerTypeSexGet(trtype)==PARA_FEMALE){
			trtype=TRTYPE_GIRL;		//����l��
		}
		else{
			trtype=TRTYPE_BOY;		//�j��l��
		}
		break;
	}

	return trtype;
}


//--------------------------------------------------------------
/**
 * @brief	�J�X�^���{�[���̃f�[�^������������
 *
 * @param	pp	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void PokePara_CustomBallDataInit( POKEMON_PARAM * pp )
{
	u8 cb_id;
	CB_CORE cb_core;
	
	cb_id = 0;
	
	MI_CpuClearFast(&cb_core, sizeof(CB_CORE));

	PokeParaPut(pp, ID_PARA_cb_id,   (u8*)&cb_id);
	PokeParaPut(pp,	ID_PARA_cb_core, (CB_CORE*)&cb_core);							
}



//------------------------------------------------------------------
/**
 * �SPP���t����
 *
 * @param   ppp		
 *
 */
//------------------------------------------------------------------
void PokePasoPara_RecoverPP( POKEMON_PASO_PARAM* ppp )
{
	BOOL fastMode;
	int i;

	fastMode = PokePasoParaFastModeOn( ppp );

	for(i=0; i<4; i++)
	{
		if( PokePasoParaGet( ppp, ID_PARA_waza1+i, NULL ) )
		{
			u8 pp_max = PokePasoParaGet( ppp, ID_PARA_pp_max1+i, NULL );
			PokePasoParaPut( ppp, ID_PARA_pp1+i, &pp_max );
		}
	}

	PokePasoParaFastModeOff( ppp, fastMode );
}



