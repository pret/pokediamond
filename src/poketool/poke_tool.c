
//============================================================================================
/**
 * @file	poke_tool.c
 * @bfief	ポケモンパラメータツール群
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

//更新があったら、MAKEがかかるようにするためにINCLUDE
#include	"pokezukan.naix"
#include	"pokegra/pokegra.naix"
#include	"pokegra/otherpoke.naix"
#include	"pokegra/height_o.naix"
#include	"pokeanm/pokeanm.naix"
#include	"trgra/trbgra.naix"
#include	"trgra/trfgra.naix"

//============================================================================================
/**
 * 定数宣言
 */
//============================================================================================

#define	POKE_GRA_SIZE	(6)		///<ポケモン１体につき、存在するグラフィックファイルの数
#define	POKE_COL_OFS	(4)		///<グラフィックアーカイブファイル内のパレットデータまでのオフセット

#define	TR_GRA_SIZE		(2)		///<トレーナー１体につき、存在するグラフィックファイルの数
#define	TR_COL_OFS		(1)		///<トレーナー１体につき、存在するグラフィックファイルの数

#define	POKE_HEIGHT_SIZE	(4)	///<ポケモン１体につき、存在する高さ情報ファイルの数

#define	DEOKISISU_OTHER_FORM_PERSONAL	(496-1)	//デオキシスの別フォルムパーソナルの開始ナンバー
#define	MINOMESU_OTHER_FORM_PERSONAL	(499-1)	//ミノメスの別フォルムパーソナルの開始ナンバー

//============================================================================================
/**
 * プロトタイプ宣言
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
 *	ポケモンパラメータ構造体を初期化する
 *
 * @param[in]	pp	初期化するポケモンパラメータ構造体のポインタ
 */
//============================================================================================
void	PokeParaInit(POKEMON_PARAM *pp)
{
	MI_CpuClearFast(pp,sizeof(POKEMON_PARAM));
//パラメータを暗号化
	PokeParaCoded(&pp->ppp.paradata,sizeof(POKEMON_PASO_PARAM1)*4,pp->ppp.checksum);
	PokeParaCoded(&pp->pcp,sizeof(POKEMON_CALC_PARAM),pp->ppp.personal_rnd);
}

//============================================================================================
/**
 *	ボックスポケモンパラメータ構造体を初期化する
 *
 * @param[in]	ppp	初期化するボックスポケモンパラメータ構造体のポインタ
 */
//============================================================================================
void	PokePasoParaInit(POKEMON_PASO_PARAM *ppp)
{
	MI_CpuClearFast(ppp,sizeof(POKEMON_PASO_PARAM));
//個性乱数セットしたところで暗号化
	PokeParaCoded(ppp->paradata,sizeof(POKEMON_PASO_PARAM1)*4,ppp->checksum);
}

//============================================================================================
/**
 *	POKEMON_PARAM構造体のサイズを返す
 *
 * @retval	POKEMON_PARAM構造体のサイズ
 */
//============================================================================================
int		PokemonParam_GetWorkSize(void)
{
	return sizeof(POKEMON_PARAM);
}

//============================================================================================
/**
 *	POKEMON_PARAM構造体のワークを確保、初期化してポインタを返す
 *
 *	@param[in]	heapID	メモリを確保するヒープID
 *
 * @retval	POKEMON_PARAM構造体へのポインタ
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
 *	ポケモンパラメータ構造体へのアクセスを高速化モードへ
 *
 * @param[in]	pp	ポケモンパラメータ構造体へのポインタ
 *
 * @retval	FALSE:すでに高速化モードになっている　TRUE:高速化モードへ移行
 */
//============================================================================================
BOOL	PokeParaFastModeOn(POKEMON_PARAM *pp)
{
	BOOL	ret;

	ret=FALSE;

	if(pp->ppp.pp_fast_mode==0){
		ret=TRUE;
		GF_ASSERT_MSG(pp->ppp.ppp_fast_mode==0,"pppが高速化モードになっています\n");
		pp->ppp.pp_fast_mode=1;
		pp->ppp.ppp_fast_mode=1;
		PokeParaDecoded(&pp->pcp,sizeof(POKEMON_CALC_PARAM),pp->ppp.personal_rnd);
		PokeParaDecoded(&pp->ppp.paradata,sizeof(POKEMON_PASO_PARAM1)*4,pp->ppp.checksum);
	}

	return ret;
}

//============================================================================================
/**
 *	ポケモンパラメータ構造体へのアクセスを通常モードへ
 *
 * @param[in]	pp	ポケモンパラメータ構造体へのポインタ
 * @param[in]	flag	モード移行可能か判断するためのフラグ（FALSE:移行不可、TRUE:移行する）
 *
 * @retval	FALSE:すでに通常モードになっている　TRUE:通常モードへ移行
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
 *	ボックスポケモンパラメータ構造体へのアクセスを高速化モードへ
 *
 * @param[in]	ppp	ボックスポケモンパラメータ構造体へのポインタ
 *
 * @retval	FALSE:すでに高速化モードになっている　TRUE:高速化モードへ移行
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
 *	ボックスポケモンパラメータ構造体へのアクセスを通常モードへ
 *
 * @param[in]	ppp		ボックスポケモンパラメータ構造体へのポインタ
 * @param[in]	flag	モード移行可能か判断するためのフラグ（FALSE:移行不可、TRUE:移行する）
 *
 * @retval	FALSE:すでに通常モードになっている　TRUE:通常モードへ移行
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
 *	ポケモンパラメータ構造体にポケモンパラメータを生成
 *
 * @param[in]	pp		パラメータを生成するポケモンパラメータ構造体のポインタ
 * @param[in]	mons_no	パラメータを生成するポケモンナンバー
 * @param[in]	level	生成するレベル
 * @param[in]	pow		POW_RND以外:セットするパワー乱数　POW_RND:パワー乱数をランダムでセット
 * @param[in]	rndflag	個性乱数セットフラグ（RND_NO_SET:個性乱数をランダムでセット RND_SET:引数rndの値をセット
 * @param[in]	rnd		rndflagがRND_SETの時にセットされる値
 * @param[in]	idflag	IDNoセットフラグ（ID_NO_SET:プレイヤーのIDをセット ID_SET:引数idの値をセット
 *										　ID_NO_RARE:個性乱数との組み合わせでレアポケモンにならないように値を調整してセット）
 * @param[in]	id		idflagがID_SETの時にセットされる値
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

//個性乱数がきまったら、PCPを再暗号化
	PokeParaCoded(&pp->pcp,sizeof(POKEMON_CALC_PARAM),0);
	PokeParaCoded(&pp->pcp,sizeof(POKEMON_CALC_PARAM),pp->ppp.personal_rnd);

//レベルセット
	PokeParaPut(pp,ID_PARA_level,(u8 *)&level);

//メールデータ
	mail_data=MailData_CreateWork(HEAPID_BASE_SYSTEM);
	PokeParaPut(pp,ID_PARA_mail_data,mail_data);
	sys_FreeMemoryEz(mail_data);

//カスタムボールID
	i=0;
	PokeParaPut(pp,ID_PARA_cb_id,(u8 *)&i);

//カスタムボール
//	cb_core=CustomBall_AllocSaveData(HEAPID_BASE_SYSTEM);
//	PokeParaPut(pp,ID_PARA_cb_core,cb_core);
//	sys_FreeMemoryEz(cb_core);
	
	MI_CpuClearFast(&cb_core, sizeof(CB_CORE));
	PokeParaPut(pp,	ID_PARA_cb_core, (CB_CORE*)&cb_core);							

	PokeParaCalc(pp);
}

//============================================================================================
/**
 *	ボックスポケモンパラメータ構造体にポケモンパラメータを生成
 *
 * @param[in]	ppp		パラメータを生成するボックスポケモンパラメータ構造体のポインタ
 * @param[in]	mons_no	パラメータを生成するポケモンナンバー
 * @param[in]	level	生成するレベル
 * @param[in]	pow		POW_RND以外:セットするパワー乱数　POW_RND:パワー乱数をランダムでセット
 * @param[in]	rndflag	個性乱数セットフラグ（RND_NO_SET:個性乱数をランダムでセット RND_SET:引数rndの値をセット
 * @param[in]	rnd		rndflagがRND_SETの時にセットされる値
 * @param[in]	idflag	IDNoセットフラグ（ID_NO_SET:プレイヤーのIDをセット ID_SET:引数idの値をセット
 *										　ID_NO_RARE:個性乱数との組み合わせでレアポケモンにならないように値を調整してセット）
 * @param[in]	id		idflagがID_SETの時にセットされる値
 */
//============================================================================================
void	PokePasoParaSet(POKEMON_PASO_PARAM *ppp,int mons_no,int level,int pow,int rndflag,u32 rnd,int idflag,u32 id)
{
	u16	sum;
	u32	i,j;
	BOOL	flag;

	PokePasoParaInit(ppp);

	flag=PokePasoParaFastModeOn(ppp);

//個性乱数セット
	if(!rndflag){
		rnd=(gf_rand()|(gf_rand()<<16));
	}
	PokePasoParaPut(ppp,ID_PARA_personal_rnd,(u8 *)&rnd);

//IDナンバーセット
	if(idflag==ID_NO_RARE){
		do{
			id=(gf_rand()|(gf_rand()<<16));
		}while((((id&0xffff0000)>>16)^(id&0xffff)^((rnd&0xffff0000)>>16)^(rnd&0xffff))<8);
	}
	else if(idflag!=ID_SET){
		id=0;
	}
	PokePasoParaPut(ppp,ID_PARA_id_no,(u8 *)&id);
	
//国コード
	PokePasoParaPut(ppp,ID_PARA_country_code,(u8 *)&CasetteLanguage);

//ポケモンナンバーセット
	PokePasoParaPut(ppp,ID_PARA_monsno,(u8 *)&mons_no);

//ニックネームセット
//	MSGDAT_MonsNameGet(mons_no,HEAPID_BASE_SYSTEM,buf);
//	PokePasoParaPut(ppp,ID_PARA_nickname,(u8 *)&buf);
	PokePasoParaPut(ppp,ID_PARA_default_name,NULL);

//経験値セット
	i=PokeLevelExpGet(mons_no,level);
	PokePasoParaPut(ppp,ID_PARA_exp,(u8 *)&i);

//友好値セット
	i=PokePersonalParaGet(mons_no,ID_PER_friend);
	PokePasoParaPut(ppp,ID_PARA_friend,(u8 *)&i);

//捕獲データセット
	PokePasoParaPut(ppp,ID_PARA_get_level,(u8 *)&level);
	PokePasoParaPut(ppp,ID_PARA_get_cassette,(u8 *)&CasetteVersion);
	i=ITEM_MONSUTAABOORU;	//デフォルトはモンスターボールにしておく	
	PokePasoParaPut(ppp,ID_PARA_get_ball,(u8 *)&i);

//パワー乱数セット
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

//特殊能力セット
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

//性別セット
	i=PokePasoSexGet(ppp);
	PokePasoParaPut(ppp,ID_PARA_sex,(u8 *)&i);

//技セット
	PokePasoWazaOboe(ppp);

	PokePasoParaFastModeOff(ppp,flag);
}

//============================================================================================
/**
 *	PokeParaSetChr(ポケモンのパラメータをセットする。性格もきめうちで）
 *
 *	@param[in]	PP			パラメータをセットする構造体のポインタ
 *	@param[in]	pokeno		ポケモンナンバー
 *	@param[in]	pokelevel	ポケモンのレベル
 *	@param[in]	pow			セットするパワー乱数(POW_RNDの時は乱数でセット）
 *	@param[in]	chr			セットする性格（０～２４）
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
 *	PokeParaSetSexChr(ポケモンのパラメータをセットする。性別、性格もきめうちで）
 *	（エンカウントのポケモンを生成するのには使わないでください。個性乱数が偏ります）
 *
 *	@param[in]	PP			パラメータをセットする構造体のポインタ
 *	@param[in]	pokeno		ポケモンナンバー
 *	@param[in]	pokelevel	ポケモンのレベル
 *	@param[in]	pow			セットするパワー乱数(POW_RNDの時は乱数でセット）
 *	@param[in]	chr			セットする性格（０～２４）
 *	@param[in]	annon		アンノーンの形状も（0:関係無し）
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
 *	PokeParaSetPowRnd(ポケモンのパラメータをセットする。パワー乱数をu32で受け取って代入）
 *
 *	@param[in]	PP			パラメータをセットする構造体のポインタ
 *	@param[in]	pokeno		ポケモンナンバー
 *	@param[in]	pokelevel	ポケモンのレベル
 *	@param[in]	pow			セットするパワー乱数
 *	@param[in]	rnd			セットする個性乱数
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
 *	PokeParaSetPowRndBuf(ポケモンのパラメータをセットする。パワー乱数をu8 *で受け取って代入）
 *
 *	@param[in]	PP			パラメータをセットする構造体のポインタ
 *	@param[in]	pokeno		ポケモンナンバー
 *	@param[in]	pokelevel	ポケモンのレベル
 *	@param[in]	pow			セットするパワー乱数
 *	@param[in]	id			セットするIDナンバー
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
 *	PokeParaSetParaExp(ポケモンのパラメータをセットする。努力値もセットする）
 *
 *	@param[in]	pp			パラメータをセットする構造体のポインタ
 *	@param[in]	pokeno		ポケモンナンバー
 *	@param[in]	pokelevel	ポケモンのレベル
 *	@param[in]	pow			セットするパワー乱数
 *	@param[in]	expbit		セットする努力値のビット(0bit:hp_exp 1bit:pow_exp 2bit:def_exp...）
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
 *	バトル施設用のPokeParaSet
 *
 *	@param	pp			パラメータをセットする構造体のポインタ
 *	@param	pokeno		ポケモンナンバー
 *	@param	pokelevel	ポケモンのレベル
 *	@param	chr			セットする性格
 *	@param	pow			セットするパワー乱数
 *	@param	expbit		セットする努力値のビット(0bit:hp_exp 1bit:pow_exp 2bit:def_exp...）
 *	@param	id			セットするID
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
 *	ポケモンパラメータ計算ルーチン
 *
 * @param[in]	pp	計算するポケモンパラメータ構造体のポインタ
 */
//============================================================================================
void	PokeParaCalc(POKEMON_PARAM *pp)
{
	int		level;
	BOOL	flag;

	flag=PokeParaFastModeOn(pp);

//レベルセット
	level=PokeParaLevelCalc(pp);
	PokeParaPut(pp,ID_PARA_level,(u8 *)&level);

	PokeParaCalcLevelUp(pp);

	PokeParaFastModeOff(pp,flag);
}

//============================================================================================
/**
 *	ポケモンパラメータ計算ルーチン（レベルアップ時専用）
 *
 * @param[in]	pp	計算するポケモンパラメータ構造体のポインタ
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

//一応残しておく
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
 *	ポケモンパラメータ構造体から任意で値を取得（暗号／復号／チェックサムチェックあり）
 *
 * @param[in]	pp	取得するポケモンパラメータ構造体のポインタ
 * @param[in]	id	取得したいデータのインデックス（poke_tool.hに定義）
 * @param[out]	buf	取得したいデータが配列の時に格納先のアドレスを指定
 *
 * @return		取得したデータ
 */
//============================================================================================
u32	PokeParaGet(POKEMON_PARAM *pp,int id,void *buf)
{
	u32	ret;
	u16	sum;

//アサートを出すために呼び分けていた時のなごり
//	GF_ASSERT_MSG(pp->ppp.pp_fast_mode==0,"高速化モードのままになってます\n");

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

//アサートを出すために呼び分けていたけど、PokeParaGetに統合
#if 0
//============================================================================================
/**
 *	ポケモンパラメータ構造体から任意で値を取得（高速化モード）
 *
 * @param[in]	pp	取得するポケモンパラメータ構造体のポインタ
 * @param[in]	id	取得したいデータのインデックス（poke_tool.hに定義）
 * @param[out]	buf	取得したいデータが配列の時に格納先のアドレスを指定
 *
 * @return		取得したデータ
 */
//============================================================================================
u32	PokeParaGetFast(POKEMON_PARAM *pp,int id,void *buf)
{
	GF_ASSERT_MSG(pp->ppp.pp_fast_mode==1,"高速化モードではないのに呼ばれています\n");

	return PokeParaGetAct(pp,id,buf);
}
#endif

//============================================================================================
/**
 *	ポケモンパラメータ構造体から任意で値を取得
 *
 * @param[in]	pp	取得するポケモンパラメータ構造体のポインタ
 * @param[in]	id	取得したいデータのインデックス（poke_tool.hに定義）
 * @param[out]	buf	取得したいデータが配列の時に格納先のアドレスを指定
 *
 * @return		取得したデータ
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
 *	ボックスポケモンパラメータ構造体から任意で値を取得（暗号／復号／チェックサムチェックあり）
 *
 * @param[in]	pp	取得するボックスポケモンパラメータ構造体のポインタ
 * @param[in]	id	取得したいデータのインデックス（poke_tool.hに定義）
 * @param[out]	buf	取得したいデータが配列の時に格納先のアドレスを指定
 *
 * @return		取得したデータ
 */
//============================================================================================
u32	PokePasoParaGet(POKEMON_PASO_PARAM *ppp,int id,void *buf)
{
	u16	sum;
	u32	ret;

//アサートを出すために呼び分けていた時のなごり
//	GF_ASSERT_MSG(ppp->ppp_fast_mode==0,"高速化モードのままになってます\n");

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

//アサートを出すために呼び分けていたけど、PokePasoParaGetに統合
#if 0
//============================================================================================
/**
 *	ボックスポケモンパラメータ構造体から任意で値を取得（高速化モード）
 *
 * @param[in]	pp	取得するボックスポケモンパラメータ構造体のポインタ
 * @param[in]	id	取得したいデータのインデックス（poke_tool.hに定義）
 * @param[out]	buf	取得したいデータが配列の時に格納先のアドレスを指定
 *
 * @return		取得したデータ
 */
//============================================================================================
u32	PokePasoParaGetFast(POKEMON_PASO_PARAM *ppp,int id,void *buf)
{
	GF_ASSERT_MSG(ppp->ppp_fast_mode==1,"高速化モードではないのに呼ばれています\n");

	return PokePasoParaGetAct(ppp,id,buf);
}
#endif

//============================================================================================
/**
 *	ボックスポケモンパラメータ構造体から任意で値を取得
 *
 * @param[in]	pp	取得するボックスポケモンパラメータ構造体のポインタ
 * @param[in]	id	取得したいデータのインデックス（poke_tool.hに定義）
 * @param[out]	buf	取得したいデータが配列の時に格納先のアドレスを指定
 *
 * @return		取得したデータ
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
		case ID_PARA_sinou_champ_ribbon:				//シンオウチャンプリボン
		case ID_PARA_sinou_battle_tower_ttwin_first:	//シンオウバトルタワータワータイクーン勝利1回目
		case ID_PARA_sinou_battle_tower_ttwin_second:	//シンオウバトルタワータワータイクーン勝利2回目
		case ID_PARA_sinou_battle_tower_2vs2_win50:		//シンオウバトルタワータワーダブル50連勝
		case ID_PARA_sinou_battle_tower_aimulti_win50:	//シンオウバトルタワータワーAIマルチ50連勝
		case ID_PARA_sinou_battle_tower_siomulti_win50:	//シンオウバトルタワータワー通信マルチ50連勝
		case ID_PARA_sinou_battle_tower_wifi_rank5:		//シンオウバトルタワーWifiランク５入り
		case ID_PARA_sinou_syakki_ribbon:				//シンオウしゃっきリボン
		case ID_PARA_sinou_dokki_ribbon:				//シンオウどっきリボン
		case ID_PARA_sinou_syonbo_ribbon:				//シンオウしょんぼリボン
		case ID_PARA_sinou_ukka_ribbon:					//シンオウうっかリボン
		case ID_PARA_sinou_sukki_ribbon:				//シンオウすっきリボン
		case ID_PARA_sinou_gussu_ribbon:				//シンオウぐっすリボン
		case ID_PARA_sinou_nikko_ribbon:				//シンオウにっこリボン
		case ID_PARA_sinou_gorgeous_ribbon:				//シンオウゴージャスリボン
		case ID_PARA_sinou_royal_ribbon:				//シンオウロイヤルリボン
		case ID_PARA_sinou_gorgeousroyal_ribbon:		//シンオウゴージャスロイヤルリボン
		case ID_PARA_sinou_ashiato_ribbon:				//シンオウあしあとリボン
		case ID_PARA_sinou_record_ribbon:				//シンオウレコードリボン
		case ID_PARA_sinou_history_ribbon:				//シンオウヒストリーリボン
		case ID_PARA_sinou_legend_ribbon:				//シンオウレジェンドリボン
		case ID_PARA_sinou_red_ribbon:					//シンオウレッドリボン
		case ID_PARA_sinou_green_ribbon:				//シンオウグリーンリボン
		case ID_PARA_sinou_blue_ribbon:					//シンオウブルーリボン
		case ID_PARA_sinou_festival_ribbon:				//シンオウフェスティバルリボン
		case ID_PARA_sinou_carnival_ribbon:				//シンオウカーニバルリボン
		case ID_PARA_sinou_classic_ribbon:				//シンオウクラシックリボン
		case ID_PARA_sinou_premiere_ribbon:				//シンオウプレミアリボン
		case ID_PARA_sinou_amari_ribbon:				//あまり
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

		case ID_PARA_get_year:							//捕まえた年
			ret=ppp4->get_year;							//捕まえた年
			break;
		case ID_PARA_get_month:							//捕まえた月
			ret=ppp4->get_month;							//捕まえた月
			break;
		case ID_PARA_get_day:							//捕まえた日
			ret=ppp4->get_day;							//捕まえた日
			break;
		case ID_PARA_birth_year:						//生まれた年
			ret=ppp4->birth_year;						//生まれた年
			break;
		case ID_PARA_birth_month:						//生まれた月
			ret=ppp4->birth_month;						//生まれた月
			break;
		case ID_PARA_birth_day:							//生まれた日
			ret=ppp4->birth_day;							//生まれた日
			break;
		case ID_PARA_get_place:							//捕まえた場所
			ret=ppp4->get_place;							//捕まえた場所
			break;
		case ID_PARA_birth_place:						//生まれた場所
			ret=ppp4->birth_place;						//生まれた場所
			break;
		case ID_PARA_pokerus:							//ポケルス
			ret=ppp4->pokerus;							//ポケルス
			break;
		case ID_PARA_get_ball:							//捕まえたボール
			ret=ppp4->get_ball;							//捕まえたボール
			break;
		case ID_PARA_get_level:							//捕まえたレベル
			ret=ppp4->get_level;							//捕まえたレベル
			break;
		case ID_PARA_oyasex:							//親の性別
			ret=ppp4->oyasex;							//親の性別
			break;
		case ID_PARA_get_ground_id:						//捕まえた場所の地形アトリビュート（ミノッチ用）
			ret=ppp4->get_ground_id;						//捕まえた場所の地形アトリビュート（ミノッチ用）
			break;
		case ID_PARA_dummy_p4_1:						//あまり
			ret=ppp4->dummy_p4_1;						//あまり
			break;

		case ID_PARA_power_rnd:
			ret=(ppp2->hp_rnd		<< 0)|
				(ppp2->pow_rnd		<< 5)|
				(ppp2->def_rnd		<<10)|
				(ppp2->agi_rnd		<<15)|
				(ppp2->spepow_rnd	<<20)|
				(ppp2->spedef_rnd	<<25);
			break;
		//モンスターナンバーがニドランの時にnickname_flagが立っているかチェック
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
		case ID_PARA_default_name:						//ポケモンのデフォルト名
			MSGDAT_MonsNameGet(ppp1->monsno,HEAPID_BASE_SYSTEM,buf);
			break;
	}

	return	ret;
}

//============================================================================================
/**
 *	ポケモンパラメータ構造体に任意で値を格納（暗号／復号／チェックサムチェックあり）
 *
 * @param[in]	pp	格納したいポケモンパラメータ構造体のポインタ
 * @param[in]	id	格納したいデータのインデックス（poke_tool.hに定義）
 * @param[in]	buf	格納したいデータのポインタ
 */
//============================================================================================
void	PokeParaPut(POKEMON_PARAM *pp,int id,const void *buf)
{
	u16	sum;

//アサートを出すために呼び分けていた時のなごり
//	GF_ASSERT_MSG(pp->ppp.pp_fast_mode==0,"高速化モードのままになってます\n");

	if(pp->ppp.pp_fast_mode==0){
		PokeParaDecoded(&pp->pcp,sizeof(POKEMON_CALC_PARAM),pp->ppp.personal_rnd);
		PokeParaDecoded(&pp->ppp.paradata,sizeof(POKEMON_PASO_PARAM1)*4,pp->ppp.checksum);
		sum=PokeParaCheckSum(&pp->ppp.paradata,sizeof(POKEMON_PASO_PARAM1)*4);
		//不正なデータの時は書き込みをしない
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

//アサートを出すために呼び分けていたけど、PokeParaPutに統合
#if 0
//============================================================================================
/**
 *	ポケモンパラメータ構造体に任意で値を格納（高速化モード）
 *
 * @param[in]	pp	格納したいポケモンパラメータ構造体のポインタ
 * @param[in]	id	格納したいデータのインデックス（poke_tool.hに定義）
 * @param[in]	buf	格納したいデータのポインタ
 */
//============================================================================================
void	PokeParaPutFast(POKEMON_PARAM *pp,int id,const void *buf)
{
	u16	sum;

	GF_ASSERT_MSG(pp->ppp.pp_fast_mode==1,"高速化モードではないのに呼ばれています\n");

	PokeParaPutAct(pp,id,buf);
}
#endif

//============================================================================================
/**
 *	ポケモンパラメータ構造体に任意で値を格納
 *
 * @param[in]	pp	格納したいポケモンパラメータ構造体のポインタ
 * @param[in]	id	格納したいデータのインデックス（poke_tool.hに定義）
 * @param[in]	buf	格納したいデータのポインタ
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
 *	ボックスポケモンパラメータ構造体に任意で値を格納（暗号／復号／チェックサムチェックあり）
 *
 * @param[in]	ppp	格納したいボックスポケモンパラメータ構造体のポインタ
 * @param[in]	id	格納したいデータのインデックス（poke_tool.hに定義）
 * @param[in]	buf	格納したいデータのポインタ
 */
//============================================================================================
void	PokePasoParaPut(POKEMON_PASO_PARAM *ppp,int id,const void *buf)
{
	u16	sum;

//アサートを出すために呼び分けていた時のなごり
//	GF_ASSERT_MSG(ppp->ppp_fast_mode==0,"高速化モードのままになってます\n");

	if(ppp->ppp_fast_mode==0){
		PokeParaDecoded(ppp->paradata,sizeof(POKEMON_PASO_PARAM1)*4,ppp->checksum);
		sum=PokeParaCheckSum(ppp->paradata,sizeof(POKEMON_PASO_PARAM1)*4);
		//不正なデータの時は書き込みをしない
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

//アサートを出すために呼び分けていたけど、PokePasoParaPutに統合
#if 0
//============================================================================================
/**
 *	ボックスポケモンパラメータ構造体に任意で値を格納（高速化モード）
 *
 * @param[in]	ppp	格納したいボックスポケモンパラメータ構造体のポインタ
 * @param[in]	id	格納したいデータのインデックス（poke_tool.hに定義）
 * @param[in]	buf	格納したいデータのポインタ
 */
//============================================================================================
void	PokePasoParaPutFast(POKEMON_PASO_PARAM *ppp,int id,const void *buf)
{
	u16	sum;

	GF_ASSERT_MSG(ppp->ppp_fast_mode==1,"高速化モードではないのに呼ばれています\n");

	PokePasoParaPutAct(ppp,id,buf);
}
#endif

//============================================================================================
/**
 *	ボックスポケモンパラメータ構造体に任意で値を格納
 *
 * @param[in]	ppp	格納したいボックスポケモンパラメータ構造体のポインタ
 * @param[in]	id	格納したいデータのインデックス（poke_tool.hに定義）
 * @param[in]	buf	格納したいデータのポインタ
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
			GF_ASSERT_MSG((0),"fast_modeへ不正な書き込み\n");
			ppp->pp_fast_mode=buf8[0];
			break;
		case ID_PARA_ppp_fast_mode:
			GF_ASSERT_MSG((0),"fast_modeへ不正な書き込み\n");
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
		case ID_PARA_sinou_champ_ribbon:				//シンオウチャンプリボン
		case ID_PARA_sinou_battle_tower_ttwin_first:	//シンオウバトルタワータワータイクーン勝利1回目
		case ID_PARA_sinou_battle_tower_ttwin_second:	//シンオウバトルタワータワータイクーン勝利2回目
		case ID_PARA_sinou_battle_tower_2vs2_win50:		//シンオウバトルタワータワーダブル50連勝
		case ID_PARA_sinou_battle_tower_aimulti_win50:	//シンオウバトルタワータワーAIマルチ50連勝
		case ID_PARA_sinou_battle_tower_siomulti_win50:	//シンオウバトルタワータワー通信マルチ50連勝
		case ID_PARA_sinou_battle_tower_wifi_rank5:		//シンオウバトルタワーWifiランク５入り
		case ID_PARA_sinou_syakki_ribbon:				//シンオウしゃっきリボン
		case ID_PARA_sinou_dokki_ribbon:				//シンオウどっきリボン
		case ID_PARA_sinou_syonbo_ribbon:				//シンオウしょんぼリボン
		case ID_PARA_sinou_ukka_ribbon:					//シンオウうっかリボン
		case ID_PARA_sinou_sukki_ribbon:				//シンオウすっきリボン
		case ID_PARA_sinou_gussu_ribbon:				//シンオウぐっすリボン
		case ID_PARA_sinou_nikko_ribbon:				//シンオウにっこリボン
		case ID_PARA_sinou_gorgeous_ribbon:				//シンオウゴージャスリボン
		case ID_PARA_sinou_royal_ribbon:				//シンオウロイヤルリボン
		case ID_PARA_sinou_gorgeousroyal_ribbon:		//シンオウゴージャスロイヤルリボン
		case ID_PARA_sinou_ashiato_ribbon:				//シンオウあしあとリボン
		case ID_PARA_sinou_record_ribbon:				//シンオウレコードリボン
		case ID_PARA_sinou_history_ribbon:				//シンオウヒストリーリボン
		case ID_PARA_sinou_legend_ribbon:				//シンオウレジェンドリボン
		case ID_PARA_sinou_red_ribbon:					//シンオウレッドリボン
		case ID_PARA_sinou_green_ribbon:				//シンオウグリーンリボン
		case ID_PARA_sinou_blue_ribbon:					//シンオウブルーリボン
		case ID_PARA_sinou_festival_ribbon:				//シンオウフェスティバルリボン
		case ID_PARA_sinou_carnival_ribbon:				//シンオウカーニバルリボン
		case ID_PARA_sinou_classic_ribbon:				//シンオウクラシックリボン
		case ID_PARA_sinou_premiere_ribbon:				//シンオウプレミアリボン
		case ID_PARA_sinou_amari_ribbon:				//あまり
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
			OS_Printf("不正な書き込み\n");
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

				//デフォルト名と比較して、デフォルト名だったら、ニックネームフラグを落とす
				//海外版からきたポケモンは、ニックネームの変更が不可なので、国コードを見る必要はなし
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

				//デフォルト名と比較して、デフォルト名だったら、ニックネームフラグを落とす
				//海外版からきたポケモンは、ニックネームの変更が不可なので、国コードを見る必要はなし
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

		case ID_PARA_get_year:							//捕まえた年
			ppp4->get_year=buf8[0];						//捕まえた年
			break;
		case ID_PARA_get_month:							//捕まえた月
			ppp4->get_month=buf8[0];					//捕まえた月
			break;
		case ID_PARA_get_day:							//捕まえた日
			ppp4->get_day=buf8[0];						//捕まえた日
			break;
		case ID_PARA_birth_year:						//生まれた年
			ppp4->birth_year=buf8[0];					//生まれた年
			break;
		case ID_PARA_birth_month:						//生まれた月
			ppp4->birth_month=buf8[0];					//生まれた月
			break;
		case ID_PARA_birth_day:							//生まれた日
			ppp4->birth_day=buf8[0];					//生まれた日
			break;
		case ID_PARA_get_place:							//捕まえた場所
			ppp4->get_place=buf16[0];					//捕まえた場所
			break;
		case ID_PARA_birth_place:						//生まれた場所
			ppp4->birth_place=buf16[0];					//生まれた場所
			break;
		case ID_PARA_pokerus:							//ポケルス
			ppp4->pokerus=buf8[0];						//ポケルス
			break;
		case ID_PARA_get_ball:							//捕まえたボール
			ppp4->get_ball=buf8[0];						//捕まえたボール
			break;
		case ID_PARA_get_level:							//捕まえたレベル
			ppp4->get_level=buf8[0];					//捕まえたレベル
			break;
		case ID_PARA_oyasex:							//親の性別
			ppp4->oyasex=buf8[0];						//親の性別
			break;
		case ID_PARA_get_ground_id:						//捕まえた場所の地形アトリビュート（ミノッチ用）
			ppp4->get_ground_id=buf8[0];				//捕まえた場所の地形アトリビュート（ミノッチ用）
			break;
		case ID_PARA_dummy_p4_1:						//あまり
			ppp4->dummy_p4_1=buf16[0];					//あまり
			break;

		case ID_PARA_power_rnd:
			ppp2->hp_rnd	=(buf32[0]>> 0)&0x0000001f;
			ppp2->pow_rnd	=(buf32[0]>> 5)&0x0000001f;
			ppp2->def_rnd	=(buf32[0]>>10)&0x0000001f;
			ppp2->agi_rnd	=(buf32[0]>>15)&0x0000001f;
			ppp2->spepow_rnd=(buf32[0]>>20)&0x0000001f;
			ppp2->spedef_rnd=(buf32[0]>>25)&0x0000001f;
			break;
		//モンスターナンバーがニドランの時にnickname_flagが立っているかチェック
		case ID_PARA_nidoran_nickname:
		case ID_PARA_type1:
		case ID_PARA_type2:
			OS_Printf("不正な書き込み\n");
			break;
		case ID_PARA_default_name:						//ポケモンのデフォルト名
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
 *	ポケモンパラメータ構造体に任意で値を加算（暗号／復号／チェックサムチェックあり）
 *
 * @param[in]	pp		加算したいポケモンパラメータ構造体のポインタ
 * @param[in]	id		加算したいデータのインデックス（poke_tool.hに定義）
 * @param[in]	value	加算したいデータのポインタ
 */
//============================================================================================
void	PokeParaAdd(POKEMON_PARAM *pp,int id,int value)
{
	u16	sum;

//アサートを出すために呼び分けていた時のなごり
//	GF_ASSERT_MSG(pp->ppp.pp_fast_mode==0,"高速化モードのままになってます\n");

	if(pp->ppp.pp_fast_mode==0){
		PokeParaDecoded(&pp->pcp,sizeof(POKEMON_CALC_PARAM),pp->ppp.personal_rnd);
		PokeParaDecoded(&pp->ppp.paradata,sizeof(POKEMON_PASO_PARAM1)*4,pp->ppp.checksum);
		sum=PokeParaCheckSum(&pp->ppp.paradata,sizeof(POKEMON_PASO_PARAM1)*4);
		//不正なデータの時は書き込みをしない
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

//アサートを出すために呼び分けていたけど、PokeParaAddに統合
#if 0
//============================================================================================
/**
 *	ポケモンパラメータ構造体に任意で値を加算（高速化モード）
 *
 * @param[in]	pp		加算したいポケモンパラメータ構造体のポインタ
 * @param[in]	id		加算したいデータのインデックス（poke_tool.hに定義）
 * @param[in]	value	加算したいデータのポインタ
 */
//============================================================================================
void	PokeParaAddFast(POKEMON_PARAM *pp,int id,int value)
{
	u16	sum;

	GF_ASSERT_MSG(pp->ppp.pp_fast_mode==1,"高速化モードではないのに呼ばれています\n");

	PokeParaAddAct(pp,id,value);
}
#endif

//============================================================================================
/**
 *	ポケモンパラメータ構造体に任意で値を加算
 *
 * @param[in]	pp		加算したいポケモンパラメータ構造体のポインタ
 * @param[in]	id		加算したいデータのインデックス（poke_tool.hに定義）
 * @param[in]	value	加算したいデータのポインタ
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
			GF_ASSERT_MSG((0),"Addできないパラメータです\n");
			break;
		default:
			PokePasoParaAddAct((POKEMON_PASO_PARAM *)&pp->ppp,id,value);
			break;
	}
}

//============================================================================================
/**
 *	ボックスポケモンパラメータ構造体に任意で値を加算（暗号／復号／チェックサムチェックあり）
 *
 * @param[in]	ppp		加算したいボックスポケモンパラメータ構造体のポインタ
 * @param[in]	id		加算したいデータのインデックス（poke_tool.hに定義）
 * @param[in]	value	加算したいデータのポインタ
 */
//============================================================================================
void	PokePasoParaAdd(POKEMON_PASO_PARAM *ppp,int id,int value)
{
	u16	sum;

//アサートを出すために呼び分けていた時のなごり
//	GF_ASSERT_MSG(ppp->ppp_fast_mode==0,"高速化モードのままになってます\n");

	if(ppp->ppp_fast_mode==0){
		PokeParaDecoded(ppp->paradata,sizeof(POKEMON_PASO_PARAM1)*4,ppp->checksum);
		sum=PokeParaCheckSum(ppp->paradata,sizeof(POKEMON_PASO_PARAM1)*4);
		//不正なデータの時は書き込みをしない
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

//アサートを出すために呼び分けていたけど、PokePasoParaAddに統合
#if 0
//============================================================================================
/**
 *	ボックスポケモンパラメータ構造体に任意で値を加算（高速化モード）
 *
 * @param[in]	ppp		加算したいボックスポケモンパラメータ構造体のポインタ
 * @param[in]	id		加算したいデータのインデックス（poke_tool.hに定義）
 * @param[in]	value	加算したいデータのポインタ
 */
//============================================================================================
void	PokePasoParaAddFast(POKEMON_PASO_PARAM *ppp,int id,int value)
{
	u16	sum;

	GF_ASSERT_MSG(ppp->ppp_fast_mode==1,"高速化モードではないのに呼ばれています\n");

	PokePasoParaAddAct(ppp,id,value);
}
#endif

//============================================================================================
/**
 *	ボックスポケモンパラメータ構造体に任意で値を加算
 *
 * @param[in]	ppp		加算したいボックスポケモンパラメータ構造体のポインタ
 * @param[in]	id		加算したいデータのインデックス（poke_tool.hに定義）
 * @param[in]	value	加算したいデータのポインタ
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
			OS_Printf("不正な足しこみ\n");
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
		case ID_PARA_sinou_champ_ribbon:				//シンオウチャンプリボン
		case ID_PARA_sinou_battle_tower_ttwin_first:	//シンオウバトルタワータワータイクーン勝利1回目
		case ID_PARA_sinou_battle_tower_ttwin_second:	//シンオウバトルタワータワータイクーン勝利2回目
		case ID_PARA_sinou_battle_tower_2vs2_win50:		//シンオウバトルタワータワーダブル50連勝
		case ID_PARA_sinou_battle_tower_aimulti_win50:	//シンオウバトルタワータワーAIマルチ50連勝
		case ID_PARA_sinou_battle_tower_siomulti_win50:	//シンオウバトルタワータワー通信マルチ50連勝
		case ID_PARA_sinou_battle_tower_wifi_rank5:		//シンオウバトルタワーWifiランク５入り
		case ID_PARA_sinou_syakki_ribbon:				//シンオウしゃっきリボン
		case ID_PARA_sinou_dokki_ribbon:				//シンオウどっきリボン
		case ID_PARA_sinou_syonbo_ribbon:				//シンオウしょんぼリボン
		case ID_PARA_sinou_ukka_ribbon:					//シンオウうっかリボン
		case ID_PARA_sinou_sukki_ribbon:				//シンオウすっきリボン
		case ID_PARA_sinou_gussu_ribbon:				//シンオウぐっすリボン
		case ID_PARA_sinou_nikko_ribbon:				//シンオウにっこリボン
		case ID_PARA_sinou_gorgeous_ribbon:				//シンオウゴージャスリボン
		case ID_PARA_sinou_royal_ribbon:				//シンオウロイヤルリボン
		case ID_PARA_sinou_gorgeousroyal_ribbon:		//シンオウゴージャスロイヤルリボン
		case ID_PARA_sinou_ashiato_ribbon:				//シンオウあしあとリボン
		case ID_PARA_sinou_record_ribbon:				//シンオウレコードリボン
		case ID_PARA_sinou_history_ribbon:				//シンオウヒストリーリボン
		case ID_PARA_sinou_legend_ribbon:				//シンオウレジェンドリボン
		case ID_PARA_sinou_red_ribbon:					//シンオウレッドリボン
		case ID_PARA_sinou_green_ribbon:				//シンオウグリーンリボン
		case ID_PARA_sinou_blue_ribbon:					//シンオウブルーリボン
		case ID_PARA_sinou_festival_ribbon:				//シンオウフェスティバルリボン
		case ID_PARA_sinou_carnival_ribbon:				//シンオウカーニバルリボン
		case ID_PARA_sinou_classic_ribbon:				//シンオウクラシックリボン
		case ID_PARA_sinou_premiere_ribbon:				//シンオウプレミアリボン
		case ID_PARA_sinou_amari_ribbon:				//あまり
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
		case ID_PARA_get_year:							//捕まえた年
		case ID_PARA_get_month:							//捕まえた月
		case ID_PARA_get_day:							//捕まえた日
		case ID_PARA_birth_year:						//生まれた年
		case ID_PARA_birth_month:						//生まれた月
		case ID_PARA_birth_day:							//生まれた日
		case ID_PARA_get_place:							//捕まえた場所
		case ID_PARA_birth_place:						//生まれた場所
		case ID_PARA_pokerus:							//ポケルス
		case ID_PARA_get_ball:							//捕まえたボール
		case ID_PARA_get_level:							//捕まえたレベル
		case ID_PARA_oyasex:							//親の性別
		case ID_PARA_get_ground_id:						//捕まえた場所の地形アトリビュート（ミノッチ用）
		case ID_PARA_dummy_p4_1:						//あまり
		case ID_PARA_power_rnd:
		case ID_PARA_nidoran_nickname:
		case ID_PARA_type1:
		case ID_PARA_type2:
		case ID_PARA_default_name:						//ポケモンのデフォルト名
		default:
			GF_ASSERT_MSG((0),"不正な加算\n");
			break;
	}
}

//==============================================================================
/**
 * パーソナルデータオープン
 *
 * この関数でオープンしたデータをPokePersonalPara_Getで取得します
 * PokePersonalPara_Closeで解放
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
 * パーソナルデータ取得
 *
 * PokePersonalPara_Openで関数で準備してからデータを取得します
 * PokePersonalPara_Closeで解放
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
	case ID_PER_basic_hp:		//基本ＨＰ
		ret=ppd->basic_hp;
		break;
	case ID_PER_basic_pow:		//基本攻撃力
		ret=ppd->basic_pow;
		break;
	case ID_PER_basic_def:		//基本防御力
		ret=ppd->basic_def;
		break;
	case ID_PER_basic_agi:		//基本素早さ
		ret=ppd->basic_agi;
		break;
	case ID_PER_basic_spepow:	//基本特殊攻撃力
		ret=ppd->basic_spepow;
		break;
	case ID_PER_basic_spedef:	//基本特殊防御力
		ret=ppd->basic_spedef;
		break;
	case ID_PER_type1:			//属性１
		ret=ppd->type1;
		break;
	case ID_PER_type2:			//属性２
		ret=ppd->type2;
		break;
	case ID_PER_get_rate:		//捕獲率
		ret=ppd->get_rate;
		break;
	case ID_PER_give_exp:		//贈与経験値
		ret=ppd->give_exp;
		break;
	case ID_PER_pains_hp:		//贈与努力値ＨＰ
		ret=ppd->pains_hp;
		break;
	case ID_PER_pains_pow:		//贈与努力値攻撃力
		ret=ppd->pains_pow;
		break;
	case ID_PER_pains_def:		//贈与努力値防御力
		ret=ppd->pains_def;
		break;
	case ID_PER_pains_agi:		//贈与努力値素早さ
		ret=ppd->pains_agi;
		break;
	case ID_PER_pains_spepow:	//贈与努力値特殊攻撃力
		ret=ppd->pains_spepow;
		break;
	case ID_PER_pains_spedef:	//贈与努力値特殊防御力
		ret=ppd->pains_spedef;
		break;
	case ID_PER_item1:			//アイテム１
		ret=ppd->item1;
		break;
	case ID_PER_item2:			//アイテム２
		ret=ppd->item2;
		break;
	case ID_PER_sex:			//性別ベクトル
		ret=ppd->sex;
		break;
	case ID_PER_egg_birth:		//タマゴの孵化歩数
		ret=ppd->egg_birth;
		break;
	case ID_PER_friend:			//なつき度初期値
		ret=ppd->friend;
		break;
	case ID_PER_grow:			//成長曲線識別
		ret=ppd->grow;
		break;
	case ID_PER_egg_group1:		//こづくりグループ1
		ret=ppd->egg_group1;
		break;
	case ID_PER_egg_group2:		//こづくりグループ2
		ret=ppd->egg_group2;
		break;
	case ID_PER_speabi1:		//特殊能力１
		ret=ppd->speabi1;
		break;
	case ID_PER_speabi2:		//特殊能力２
		ret=ppd->speabi2;
		break;
	case ID_PER_escape:			//逃げる率
		ret=ppd->escape;
		break;
	case ID_PER_color:			//色（図鑑で使用）
		ret=ppd->color;
		break;
	case ID_PER_reverse:		//反転フラグ
		ret=ppd->reverse;
		break;
	case ID_PER_machine1:		//技マシンフラグ１
		ret=ppd->machine1;
		break;
	case ID_PER_machine2:		//技マシンフラグ２
		ret=ppd->machine2;
		break;
	case ID_PER_machine3:		//技マシンフラグ３
		ret=ppd->machine3;
		break;
	case ID_PER_machine4:		//技マシンフラグ４
		ret=ppd->machine4;
		break;
	}
	return ret;
}

//==============================================================================
/**
 * パーソナルデータ解放
 *
 * PokePersonalPara_Openで確保したメモリを解放します
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
 *	ポケモンパーソナル構造体データから任意でデータを取得
 *  （一発でデータを取り出したいときに使用してください、
 *    パーソナルデータをたくさん取り出したいときはOpen,Get,Closeした方が軽いです）
 *  
 * @param[in]	pp		取得したいPOKEMON_PARAM構造体
 * @param[in]	para	取得したデータのインデックス（poke_tool.hに定義）
 *
 * @return	取得したデータ
 */
//============================================================================================
u32	PokeParaPersonalParaGet(POKEMON_PARAM *pp,int para)
{
	return PokePasoParaPersonalParaGet(&pp->ppp,para);
}

//============================================================================================
/**
 *	ポケモンパーソナル構造体データから任意でデータを取得
 *  （一発でデータを取り出したいときに使用してください、
 *    パーソナルデータをたくさん取り出したいときはOpen,Get,Closeした方が軽いです）
 *  
 * @param[in]	ppp		取得したいPOKEMON_PASO_PARAM構造体
 * @param[in]	para	取得したデータのインデックス（poke_tool.hに定義）
 *
 * @return	取得したデータ
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
 *	ポケモンパーソナル構造体データから任意でデータを取得
 *  （一発でデータを取り出したいときに使用してください、
 *    パーソナルデータをたくさん取り出したいときはOpen,Get,Closeした方が軽いです）
 *  
 * @param[in]	mons_no	取得したいポケモンナンバー
 * @param[in]	form_no	取得したいポケモンのフォルムナンバー
 * @param[in]	para	取得したデータのインデックス（poke_tool.hに定義）
 *
 * @return	取得したデータ
 */
//============================================================================================
u32	PokeFormNoPersonalParaGet(int mons_no,int form_no,int para)
{
	u32	ret;
	POKEMON_PERSONAL_DATA *ppd;

	mons_no=PokeOtherFormMonsNoGet(mons_no,form_no);

	// パーソナルデータAlloc・読み込み
	ppd = PokePersonalPara_Open( mons_no, HEAPID_BASE_SYSTEM );

	// 値取得
	ret = PokePersonalPara_Get( ppd, para );

	// データ解放
	PokePersonalPara_Close( ppd );

	return ret;
}

//============================================================================================
/**
 *	ポケモンパーソナル構造体データから任意でデータを取得
 *  （一発でデータを取り出したいときに使用してください、
 *    パーソナルデータをたくさん取り出したいときはOpen,Get,Closeした方が軽いです）
 *  
 * @param[in]	mons_no	取得したいポケモンナンバー
 * @param[in]	para	取得したデータのインデックス（poke_tool.hに定義）
 *
 * @return	取得したデータ
 */
//============================================================================================
u32	PokePersonalParaGet(int mons_no,int para)
{
	u32	ret;
	POKEMON_PERSONAL_DATA *ppd;

	// パーソナルデータAlloc・読み込み
	ppd = PokePersonalPara_Open( mons_no, HEAPID_BASE_SYSTEM );

	// 値取得
	ret = PokePersonalPara_Get( ppd, para );

	// データ解放
	PokePersonalPara_Close( ppd );

	return ret;
}

//============================================================================================
/**
 *	ポケモンパラメータ構造体から次のレベルまでの経験値を％で取得
 *
 * @param[in]	pp	ポケモンパラメータ構造体のポインタ
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
 *	ポケモンパラメータ構造体から次のレベルまでの経験値を取得
 *
 * @param[in]	pp	ポケモンパラメータ構造体のポインタ
 */
//============================================================================================
u32		PokeParaNextLevelExpGet(POKEMON_PARAM *pp)
{
	return PokePasoParaNextLevelExpGet(&pp->ppp);
}

//============================================================================================
/**
 *	ポケモンパラメータ構造体から次のレベルまでの経験値を取得
 *
 * @param[in]	pp	ポケモンパラメータ構造体のポインタ
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
 *	ポケモンパラメータ構造体から経験値データを取得
 *
 * @param[in]	pp	ポケモンパラメータ構造体のポインタ
 */
//============================================================================================
u32	PokeParaLevelExpGet(POKEMON_PARAM *pp)
{
	return PokeLevelExpGet(PokeParaGet(pp,ID_PARA_monsno,NULL),PokeParaGet(pp,ID_PARA_level,NULL));
}

//============================================================================================
/**
 *	ポケモンナンバーとレベルから経験値データを取得
 *
 * @param[in]	mons_no		取得するモンスターナンバー
 * @param[in]	level		取得するレベル
 */
//============================================================================================
u32	PokeLevelExpGet(int	mons_no,int level)
{
	return	PokeGrowParaGet(PokePersonalParaGet(mons_no,ID_PER_grow),level);
}

//============================================================================================
/**
 *	ポケモン成長テーブルデータを取得
 *
 * @param[in]	para		取得する成長テーブルのインデックス（0～7）
 * @param[out]	grow_tbl	取得した成長テーブルの格納先
 */
//============================================================================================
void	PokeGrowDataGet(int para,u32 *grow_tbl)
{
	GF_ASSERT_MSG(para<8,"PokeGrowDataGet:TableIndexOver!");
	ArchiveDataLoad(grow_tbl,ARC_GROW_TBL,para);
}

//============================================================================================
/**
 *	ポケモン成長テーブルデータから任意で経験値データを取得
 *
 * @param[in]	para		取得する成長テーブルのインデックス（0～7）
 * @param[in]	level		取得する成長テーブルのレベル（0～100）
 *
 * @return	取得した経験値データ
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
 *	ポケモンデータからポケモンのレベルを取得
 *
 * @param[in]	pp	取得したいポケモンパラメータ構造体のポインタ
 *
 * @return	取得したレベル
 */
//============================================================================================
u32	PokeParaLevelCalc(POKEMON_PARAM *pp)
{
	return PokePasoLevelCalc(&pp->ppp);
}
//============================================================================================
/**
 *	ボックスポケモンデータからポケモンのレベルを取得
 *
 * @param[in]	ppp	取得したいボックスポケモンパラメータ構造体のポインタ
 *
 * @return	取得したレベル
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
 *	ポケモンナンバー、経験値からポケモンのレベルを計算
 *	（内部でパーソナルデータをロードする）
 *
 * @param[in]	mons_no	取得したいポケモンナンバー
 * @param[in]	exp		取得したいポケモンの経験値
 *
 * @return	取得したレベル
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
 *	ポケモンナンバー、経験値からポケモンのレベルを計算
 *	（ロード済みパーソナルデータを利用する）
 *
 * @param[in]	personalData	ポケモンパーソナルデータ
 * @param[in]	mons_no			ポケモンナンバー
 * @param[in]	exp				経験値
 *
 * @return	取得したレベル
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
 *	ポケモンの性格を取得（引数がPOKEMON_PARAM)
 *
 * @param[in]	pp	取得したいポケモンパラメータ構造体のポインタ
 *
 * @return	取得した性格
 */
//============================================================================================
u8	PokeSeikakuGet(POKEMON_PARAM *pp)
{
	return	PokePasoSeikakuGet(&pp->ppp);
}

//============================================================================================
/**
 *	ポケモンの性格を取得（引数がPOKEMON_PASO_PARAM)
 *
 * @param[in]	ppp	取得したいポケモンパラメータ構造体のポインタ
 *
 * @return	取得した性格
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
 *	ポケモンの性格を取得
 *
 *	性格は、個性乱数を25で割った余りから算出される
 *
 * @param[in]	rnd	取得したい個性乱数
 *
 * @return	取得した性格
 */
//============================================================================================
u8	PokeSeikakuGetRnd(u32 rnd)
{
	return(u8)(rnd%25);
}

//============================================================================================
/**
 *	性格によるパラメータ変化値テーブル
 */
//============================================================================================
static	const	s8	SeikakuAbiTbl[][5]={
//		pow	def	agi	spepow	spedef
	{	 0,	 0,	 0,	 0,		 0},		//がんばりや
	{	 1,	-1,	 0,	 0,		 0},		//さみしがり
	{	 1,	 0,	-1,	 0,		 0},		//ゆうかん
	{	 1,	 0,	 0,	-1,		 0},		//いじっぱり
	{	 1,	 0,	 0,	 0,		-1},		//やんちゃ
	{	-1,	 1,	 0,	 0,		 0},		//ずぶとい
	{	 0,	 0,	 0,	 0,		 0},		//すなお
	{	 0,	 1,	-1,	 0,		 0},		//のんき
	{	 0,	 1,	 0,	-1,		 0},		//わんぱく
	{	 0,	 1,	 0,	 0,		-1},		//のうてんき
	{	-1,	 0,	 1,	 0,		 0},		//おくびょう
	{	 0,	-1,	 1,	 0,		 0},		//せっかち
	{	 0,	 0,	 0,	 0,		 0},		//まじめ
	{	 0,	 0,	 1,	-1,		 0},		//ようき
	{	 0,	 0,	 1,	 0,		-1},		//むじゃき
	{	-1,	 0,	 0,	 1,		 0},		//ひかえめ
	{	 0,	-1,	 0,	 1,		 0},		//おっとり
	{	 0,	 0,	-1,	 1,		 0},		//れいせい
	{	 0,	 0,	 0,	 0,		 0},		//てれや
	{	 0,	 0,	 0,	 1,		-1},		//うっかりや
	{	-1,	 0,	 0,	 0,		 1},		//おだやか
	{	 0,	-1,	 0,	 0,		 1},		//おとなしい
	{	 0,	 0,	-1,	 0,		 1},		//なまいき
	{	 0,	 0,	 0,	-1,		 1},		//しんちょう
	{	 0,	 0,	 0,	 0,		 0},		//きまぐれ
};

//============================================================================================
/**
 *	性格によるパラメータ変化計算ルーチン
 *
 * @param[in]	chr		計算する性格
 * @param[in]	para	計算するパラメータ値
 * @param[in]	cond	取り出すパラメータ変化値テーブルのインデックス（poke_tool.hに定義）
 *
 * @return	計算結果
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
 *	性格によるパラメータ変化テーブル値取得
 *
 * @param[in]	chr		取得する性格
 * @param[in]	cond	取得するパラメータ変化値テーブルのインデックス（poke_tool.hに定義）
 *
 * @return	変化テーブル値
 */
//============================================================================================
s8	PokeChrAbiTableGet(u8 chr,u8 cond)
{
	return SeikakuAbiTbl[chr][cond-1];
}

//============================================================================================
/**
 *	なつき度計算テーブル
 */
//============================================================================================
static	const	s8	FriendParaTbl[][3]={
	{  5,  3,  2},		//レベルアップ
	{  5,  3,  2},		//努力値アップアイテム（タウリン等）使用
	{  1,  1,  0},		//攻撃補助アイテム（スピーダー等）使用
	{  3,  2,  1},		//ボス戦に参加（ジムリーダー、四天王、チャンプ）
	{  1,  1,  0},		//技マシン使用
	{  1,  1,  1},		//連れ歩き
	{ -1, -1, -1},		//瀕死
	{ -5, -5,-10},		//どくの連れ歩きによる瀕死
	{ -5, -5,-10},		//レベル３０差以上の瀕死
	{  3,  2,  1},		//コンテストで優勝
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
 *	なつき度計算
 *
 * @param[in]	pp		なつき度を計算するポケモン構造体のポインタ
 * @param[in]	id		なつき度計算するポケモンに行った行動IDナンバー（poke_tool.hに定義）
 * @param[in]	placeID	現在地ID
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

	//連れ歩きのなつき度計算の確率は1/2
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
 *	ポケモンパラメータからポケモンの性別を取得
 *
 * @param[in]	pp		ポケモンパラメータ構造体
 *
 * @retval	PARA_MALE:♂　PARA_FEMALE:♀　PARA_UNK:性別不明
 */
//============================================================================================
u8	PokeSexGet(POKEMON_PARAM *pp)
{
	return(PokePasoSexGet((POKEMON_PASO_PARAM *)&pp->ppp));
}
//============================================================================================
/**
 *	ボックスポケモンパラメータからポケモンの性別を取得
 *
 * @param[in]	pp		ポケモンパラメータ構造体
 *
 * @retval	PARA_MALE:♂　PARA_FEMALE:♀　PARA_UNK:性別不明
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
 *	ポケモンの性別を取得（内部でパーソナルデータをロードする）
 *
 * @param[in]	monsno	性別を取得するポケモンナンバー
 * @param[in]	rnd		性別を取得するポケモンの個性乱数
 *
 * @retval	PARA_MALE:♂　PARA_FEMALE:♀　PARA_UNK:性別不明
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
 *	ポケモンの性別を取得（ロード済みパーソナルデータを利用する）
 *
 * @param[in]	personalData	パーソナルデータへのポインタ
 * @param[in]	monsno			性別を取得するポケモンナンバー
 * @param[in]	rnd				性別を取得するポケモンの個性乱数
 *
 * @retval	PARA_MALE:♂　PARA_FEMALE:♀　PARA_UNK:性別不明
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
 *	ポケモンがレアかどうか取得
 *
 * @param[in]	pp		ポケモンパラメータ構造体
 *
 * @retval	TRUE:レア　FALSE:レアじゃない
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
 * @brief   ＩＤと個性乱数からレアかどうかを判定する
 *
 * @param   id		ID
 * @param   rnd		個性乱数
 *
 * @retval  u8		0:レアじゃない	0以外:レア
 */
//==============================================================================
u8		PokeRareGetPara(u32 id,u32 rnd)
{
	return((((id&0xffff0000)>>16)^(id&0xffff)^((rnd&0xffff0000)>>16)^(rnd&0xffff))<8);
}

//============================================================================================
/**
 *	ポケモンの個性乱数をレアにする値を取得
 *
 * @param[in]	id		値を導くトレーナーのID
 *
 * @retval	個性乱数
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
 *	アーカイバファイル取り出し用ヘッダデータ生成ルーチン（ポケモングラフィック）
 *
 *	PokemonParam構造体からポケモン、雌雄、色を取り出して生成
 *
 * @param[out]	ssa		ヘッダデータを格納する変数のポインタ
 * @param[in]	pp		PokemonParam構造体のポインタ
 * @param[in]	dir		生成するポケモンの向き（PARA_FRONT:正面　PARA_BACK:背面）
 */
//============================================================================================
void	PokeGraArcDataGetPP(SOFT_SPRITE_ARC *ssa,POKEMON_PARAM *pp,u8 dir)
{
	PokeGraArcDataGetPPP(ssa,&pp->ppp,dir);
}

//============================================================================================
/**
 *	アーカイバファイル取り出し用ヘッダデータ生成ルーチン（ポケモングラフィック）
 *
 *	PokemonPasoParam構造体からポケモン、雌雄、色を取り出して生成
 *
 * @param[out]	ssa		ヘッダデータを格納する変数のポインタ
 * @param[in]	ppp		PokemonPasoParam構造体のポインタ
 * @param[in]	dir		生成するポケモンの向き（PARA_FRONT:正面　PARA_BACK:背面）
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
 *	アーカイバファイル取り出し用ヘッダデータ生成ルーチン（ポケモングラフィック）
 *
 * @param[out]	ssa		ヘッダデータを格納する変数のポインタ
 * @param[in]	mons_no	生成するポケモンナンバー
 * @param[in]	sex		生成するポケモンの雌雄（PARA_MALE:♂　PARA_FEMALE:♀　PARA_UNK:Unknown）
 * @param[in]	dir		生成するポケモンの向き（PARA_FRONT:正面　PARA_BACK:背面）
 * @param[in]	col		生成するポケモンの色（PARA_NORMAL:ノーマル　PARA_RARE:レア）
 * @param[in]	form_no	生成するためのフォルムナンバー（ミノムッチ、ミノメスなど）
 * @param[in]	rnd		生成するための個性乱数（アンノーン、パッチールなど）
 */
//============================================================================================
void	PokeGraArcDataGet(SOFT_SPRITE_ARC *ssa,u16 mons_no,u8 sex,u8 dir,u8 col,u8 form_no,u32 rnd)
{
	//ぶち情報を初期化
	ssa->strike_mons=0;
	ssa->form_no=0;
	ssa->personal_rnd=0;

	switch(mons_no){
	//ミノムッチ
	case MONSNO_MINOMUTTI:
		//値が不正なら、0にする
		if(form_no>FORMNO_MINOMUTTI_MAX){
			form_no=0;
		}
		ssa->arc_no=ARC_OTHER_POKE;
		ssa->index_chr=NARC_otherpoke_pmdp_455_back_kusa_NCBR+(dir/2)+form_no*2;
		ssa->index_pal=NARC_otherpoke_pmdp_455_n_kusa_NCLR+col+form_no*2;
		break;
	//ミノメス
	case MONSNO_MINOMESU:
		//値が不正なら、0にする
		if(form_no>FORMNO_MINOMUTTI_MAX){
			form_no=0;
		}
		ssa->arc_no=ARC_OTHER_POKE;
		ssa->index_chr=NARC_otherpoke_pmdp_457_back_kusa_NCBR+(dir/2)+form_no*2;
		ssa->index_pal=NARC_otherpoke_pmdp_457_n_kusa_NCLR+col+form_no*2;
		break;
	//シーウシ
	case MONSNO_SIIUSI:
		//値が不正なら、0にする
		if(form_no>FORMNO_SII_MAX){
			form_no=0;
		}
		ssa->arc_no=ARC_OTHER_POKE;
		ssa->index_chr=NARC_otherpoke_pmdp_458_back_west_NCBR+dir+form_no;
		ssa->index_pal=NARC_otherpoke_pmdp_458_n_west_NCLR+col+form_no*2;
		break;
	//シードルゴ
	case MONSNO_SIIDORUGO:
		//値が不正なら、0にする
		if(form_no>FORMNO_SII_MAX){
			form_no=0;
		}
		ssa->arc_no=ARC_OTHER_POKE;
		ssa->index_chr=NARC_otherpoke_pmdp_459_back_west_NCBR+dir+form_no;
		ssa->index_pal=NARC_otherpoke_pmdp_459_n_west_NCLR+col+form_no*2;
		break;
	//チェリシュ
	case MONSNO_THERISYU:
		//値が不正なら、0にする
		if(form_no>FORMNO_THERISYU_MAX){
			form_no=0;
		}
		ssa->arc_no=ARC_OTHER_POKE;
		ssa->index_chr=NARC_otherpoke_pmdp_483_back_normal_NCBR+dir+form_no;
		ssa->index_pal=NARC_otherpoke_pmdp_483_n_normal_NCLR+(col*2)+form_no;
		break;
	//アウス
	case MONSNO_AUSU:
		//値が不正なら、0にする
		if(form_no>POKE_WAZA_TYPE_MAX){
			form_no=0;
		}
		ssa->arc_no=ARC_OTHER_POKE;
		ssa->index_chr=NARC_otherpoke_pmdp_518_back_normal_NCBR+(dir/2)+form_no*2;
		ssa->index_pal=NARC_otherpoke_pmdp_518_n_normal_NCLR+col+form_no*2;
		break;
	//ポワルン
	case MONSNO_POWARUN:
		//値が不正なら、0にする
		if(form_no>FORMNO_POWARUN_MAX){
			form_no=0;
		}
		ssa->arc_no=ARC_OTHER_POKE;
		ssa->index_chr=NARC_otherpoke_pmdp_351_back_normal_NCBR+(dir*2)+form_no;
		ssa->index_pal=NARC_otherpoke_pmdp_351_n_normal_NCLR+(col*4)+form_no;
		break;
	//デオキシス
	case MONSNO_DEOKISISU:
		//値が不正なら、0にする
		if(form_no>FORMNO_DEOKISISU_MAX){
			form_no=0;
		}
		ssa->arc_no=ARC_OTHER_POKE;
		ssa->index_chr=NARC_otherpoke_pmdp_386_back_n_NCBR+(dir/2)+form_no*2;
		ssa->index_pal=NARC_otherpoke_pmdp_386_n_NCLR+col;
		break;
	//アンノーン
	case MONSNO_ANNOON:
		//値が不正なら、0にする
		if(form_no>=UNK_END){
			form_no=0;
		}
		ssa->arc_no=ARC_OTHER_POKE;
//		ssa->index_chr=NARC_otherpoke_pmdp_una_back_o_NCBR+(dir/2)+PokemonUnknownFormGet(rnd)*2;
		ssa->index_chr=NARC_otherpoke_pmdp_una_back_o_NCBR+(dir/2)+form_no*2;
		ssa->index_pal=NARC_otherpoke_pmdp_201_n_NCLR+col;
		break;
	//タマゴ
	case MONSNO_TAMAGO:
		//値が不正なら、0にする
		if(form_no>1){
			form_no=0;
		}
		ssa->arc_no=ARC_OTHER_POKE;
		ssa->index_chr=NARC_otherpoke_pmdp_egg_normal_NCBR+form_no;
		ssa->index_pal=NARC_otherpoke_pmdp_egg_normal_NCLR+form_no;
		break;
	//ダメタマゴ
	case MONSNO_DAMETAMAGO:
		ssa->arc_no=ARC_OTHER_POKE;
		ssa->index_chr=NARC_otherpoke_pmdp_egg_normal_NCBR;
		ssa->index_pal=NARC_otherpoke_pmdp_egg_normal_NCLR;
		break;
	default:
		ssa->arc_no=ARC_POKE_GRA;
		ssa->index_chr=mons_no*POKE_GRA_SIZE+dir+(sex!=PARA_FEMALE?1:0);
		ssa->index_pal=mons_no*POKE_GRA_SIZE+POKE_COL_OFS+col;
		//パッチールの時は、ぶちデータを格納
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
 *	ポケモン高さ情報取得
 *
 * @param[in]	pp		取得するポケモンの構造体データへのポインタ
 * @param[in]	dir		取得するポケモンの向き（PARA_FRONT:正面　PARA_BACK:背面）
 */
//============================================================================================
u8	PokeParaHeightGet(POKEMON_PARAM *pp,u8 dir)
{
	return PokePasoParaHeightGet(&pp->ppp,dir);
}

//============================================================================================
/**
 *	ポケモン高さ情報取得
 *
 * @param[in]	ppp		取得するポケモンの構造体データへのポインタ
 * @param[in]	dir		取得するポケモンの向き（PARA_FRONT:正面　PARA_BACK:背面）
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
 *	ポケモン高さ情報取得
 *
 * @param[in]	mons_no	取得するポケモンナンバー
 * @param[in]	sex		取得するポケモンの性別（PARA_MALE:オス　PARA_FEMALE:メス　PARA_UNKNOWN：性別なし）
 * @param[in]	dir		取得するポケモンの向き（PARA_FRONT:正面　PARA_BACK:背面）
 * @param[in]	form_no	取得するポケモンのフォルムナンバー
 * @param[in]	rnd		取得するポケモンの個性乱数
 */
//============================================================================================
u8	PokeHeightGet(u16 mons_no,u8 sex,u8 dir,u8 form_no,u32 rnd)
{
	int	arcID;
	int	index;
	u8	height;

	switch(mons_no){
	//ミノムッチ
	case MONSNO_MINOMUTTI:
		//値が不正なら、0にする
		if(form_no>FORMNO_MINOMUTTI_MAX){
			form_no=0;
		}
		arcID=ARC_OTHER_HEIGHT;
		index=NARC_height_o_pmdp_455_back_kusa_bin+(dir/2)+form_no*2;
		break;
	//ミノメス
	case MONSNO_MINOMESU:
		//値が不正なら、0にする
		if(form_no>FORMNO_MINOMUTTI_MAX){
			form_no=0;
		}
		arcID=ARC_OTHER_HEIGHT;
		index=NARC_height_o_pmdp_457_back_kusa_bin+(dir/2)+form_no*2;
		break;
	//シーウシ
	case MONSNO_SIIUSI:
		//値が不正なら、0にする
		if(form_no>FORMNO_SII_MAX){
			form_no=0;
		}
		arcID=ARC_OTHER_HEIGHT;
		index=NARC_height_o_pmdp_458_back_west_bin+dir+form_no;
		break;
	//シードルゴ
	case MONSNO_SIIDORUGO:
		//値が不正なら、0にする
		if(form_no>FORMNO_SII_MAX){
			form_no=0;
		}
		arcID=ARC_OTHER_HEIGHT;
		index=NARC_height_o_pmdp_459_back_west_bin+dir+form_no;
		break;
	//チェリシュ
	case MONSNO_THERISYU:
		//値が不正なら、0にする
		if(form_no>FORMNO_THERISYU_MAX){
			form_no=0;
		}
		arcID=ARC_OTHER_HEIGHT;
		index=NARC_height_o_pmdp_483_back_normal_bin+dir+form_no;
		break;
	//アウス
	case MONSNO_AUSU:
		//値が不正なら、0にする
		if(form_no>POKE_WAZA_TYPE_MAX){
			form_no=0;
		}
		arcID=ARC_OTHER_HEIGHT;
		index=NARC_height_o_pmdp_518_back_normal_bin+(dir/2)+form_no*2;
		break;
	//ポワルン
	case MONSNO_POWARUN:
		//値が不正なら、0にする
		if(form_no>FORMNO_POWARUN_MAX){
			form_no=0;
		}
		arcID=ARC_OTHER_HEIGHT;
		index=NARC_height_o_pmdp_351_back_normal_bin+dir*2+form_no;
		break;
	//デオキシス
	case MONSNO_DEOKISISU:
		//値が不正なら、0にする
		if(form_no>FORMNO_DEOKISISU_MAX){
			form_no=0;
		}
		arcID=ARC_OTHER_HEIGHT;
		index=NARC_height_o_pmdp_386_back_n_bin+(dir/2)+form_no*2;
		break;
	//アンノーン
	case MONSNO_ANNOON:
		//値が不正なら、0にする
		if(form_no>=UNK_END){
			form_no=0;
		}
		arcID=ARC_OTHER_HEIGHT;
//		index=NARC_height_o_pmdp_una_back_o_bin+(dir/2)+PokemonUnknownFormGet(rnd)*2;
		index=NARC_height_o_pmdp_una_back_o_bin+(dir/2)+form_no*2;
		break;
	//タマゴ
	case MONSNO_TAMAGO:
		//値が不正なら、0にする
		if(form_no>1){
			form_no=0;
		}
		arcID=ARC_OTHER_HEIGHT;
		index=NARC_height_o_pmdp_egg_normal_bin+form_no;
		break;
	//ダメタマゴ
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
 *	アーカイバファイル取り出し用ヘッダデータ生成ルーチン（トレーナーグラフィック）
 *
 * @param[out]	ssa		ヘッダデータを格納する変数のポインタ
 * @param[in]	trtype	生成するトレーナー種別
 * @param[in]	dir		生成するトレーナーの向き（PARA_FRONT:正面　PARA_BACK:背面）
 * @param[in]	sex		生成するトレーナーの性別
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

	//トレーナーグラフィックは、形態変化データをクリア
	ssa->strike_mons=0;
	ssa->form_no=0;
	ssa->personal_rnd=0;
}

//============================================================================================
/**
 *	ポケモンのアニメーションデータをセット
 *
 * @param[out]	ssanm	アニメーションデータを格納する変数のポインタ
 * @param[in]	monsno	セットするポケモンナンバー
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
 *	ポケモンのアニメーションデータをセット（プログラムアニメ）
 *
 * @param[in]	pasp	アニメーションシステムワークのポインタ
 * @param[in]	ss		アニメーションデータをセットするSoftSpriteのポインタ
 * @param[in]	monsno	セットするポケモンナンバー
 * @param[in]	dir		セットする向き
 * @param[in]	chr		ポケモンの性格（背面のアニメーションを決定するのに必要）
 * @param[in]	reverse	HFLIPするかどうか？(PARA_HFLIP_OFF:HFLIPなし　PARA_HFLIP_ON:HFLIPあり）
 * @param[in]	index	セットするシステムワークのインデックス
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
 *	アーカイバファイル取り出し用ヘッダデータ生成ルーチン（トレーナーグラフィック）
 *
 * @param[out]	ssa		ヘッダデータを格納する変数のポインタ
 * @param[in]	trtype	生成するトレーナータイプ
 */
//============================================================================================
void	TrTypeGraArcDataGet(SOFT_SPRITE_ARC *ssa,u16 trtype)
{
	ssa->arc_no=ARC_TRF_GRA;
	ssa->index_chr=trtype*TR_GRA_SIZE;
	ssa->index_pal=trtype*TR_GRA_SIZE+TR_COL_OFS;

	//トレーナーグラフィックは、ぶちデータをクリア
	ssa->strike_mons=0;
	ssa->form_no=0;
	ssa->personal_rnd=0;
}

//============================================================================================
/**
 *	PokemonParam構造体のサイズを取得
 */
//============================================================================================
u32		PokemonParamSizeGet(void)
{
	return (u32)sizeof(POKEMON_PARAM);
}

//============================================================================================
/**
 *	PokemonPasoParam構造体のサイズを取得
 */
//============================================================================================
u32		PokemonPasoParamSizeGet(void)
{
	return (u32)sizeof(POKEMON_PASO_PARAM);
}

//============================================================================================
/**
 *	アンノーンのフォルムナンバーをゲット
 *
 * @param[in]	pp	ポケモンパラメータ構造体のポインタ
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
 *	アンノーンのフォルムナンバーをゲット
 *
 * @param[in]	ppp	ボックスポケモンパラメータ構造体のポインタ
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

//ＤＳから手持ち情報にform_noメンバが増えたので、個性乱数から取得する方法は削除
#if 0
//============================================================================================
/**
 *	アンノーンのフォルムナンバーをゲット
 *
 * @param[in]	annon_rnd	取得する個性乱数
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
 *	アンノーンのフォルムナンバーから個性乱数を取得
 *
 * @param[in]	form	アンノーンのフォルムナンバー
 *
 * @retval	個性乱数
 */
//============================================================================================
u32	PokemonPasoUnknownFormRndGet(int form)
{
	return (((form&0x000000c0)<<18)|((form&0x00000030)<<12)|((form&0x0000000c)<<6)|(form&0x00000003));
}
#endif

//============================================================================================
/**
 *	POKEMON_PASO_PARAMのポインタを取得
 *
 * @param[in]	pp	ポケモンパラメータ構造体のポインタ
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
 *	ポケモンのレベルアップチェックをする
 *
 * @param[in]	pp	チェックするポケモン構造体のポインタ
 *
 * @retval	0:レベルアップしない
 *			1:レベルアップした（その場合levelに+1する）
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

	//経験値が上限を超えている場合は補正する
	grow_exp=PokeGrowParaGet(para,100);
	if(exp>grow_exp){
		exp=grow_exp;
		PokeParaPut(pp,ID_PARA_exp,(u8 *)&exp);
	}
	//レベル101以上はレベルアップしない
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
 *	進化チェック
 *
 *	@param[in]	pp			チェックするポケモンの構造体のポインタ
 *	@param[in]	type		進化条件（poke_tool_def.hに定義）
 *	@param[in]	itemno		アイテム進化チェック時の使用アイテム（場所進化の場合は、shinka_place_mode）
 *	@param[out]	shinka_cond	進化条件格納ワークへのポインタ
 *
 *	@retval	0 進化せず 0以外 進化したポケモンナンバー
 */
//============================================================================================
#define	SHINKA_COND_MAX	(7)	//進化条件のMAX
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

	//ユンゲラーは絶対進化
	if(monsno!=MONSNO_YUNGERAA){
		//アイテムで進化しない装備効果は進化しない
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
			case SHINKA_SPECIAL_RND_EVEN:		//個性乱数を10で割った余りが５未満
				if(pst->psd[i].ShinkaData<=level){
					if((rnd%10)<5){
						ret=pst->psd[i].ShinkaMons;
						shinka_cond[0]=SHINKA_SPECIAL_RND_EVEN;
					}
				}
				break;
			case SHINKA_SPECIAL_RND_ODD:		//個性乱数を10で割った余りが５以上
				if(pst->psd[i].ShinkaData<=level){
					if((rnd%10)>=5){
						ret=pst->psd[i].ShinkaMons;
						shinka_cond[0]=SHINKA_SPECIAL_RND_ODD;
					}
				}
				break;
			case SHINKA_SPECIAL_LEVELUP:		//手持ちに空きがあれば、進化しつつ、
												//カラを残す
				if(pst->psd[i].ShinkaData<=level){
					ret=pst->psd[i].ShinkaMons;
					shinka_cond[0]=SHINKA_SPECIAL_LEVELUP;
				}
				break;
			case SHINKA_SPECIAL_NUKENIN:		//手持ちに空きがあれば
				shinka_cond[0]=SHINKA_SPECIAL_NUKENIN;
				break;
			case SHINKA_SPECIAL_BEAUTIFUL:		//美しさで進化
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
			//進化条件が見つかったら、抜ける
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
			//進化条件が見つかったら、抜ける
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
			//進化条件が見つかったら、抜ける
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
 * @brief   渡したポケモン開発Noの大元の子供を返します(一つ前じゃありません）
 * @param   monsno	ポケモンの開発No
 * @retval  u16		子供の開発No（子供が無い場合はそのまま引数を返します）
 */
// =================================================================
u16 PokeSearchChild(const u16 monsno)
{
	FSFile		p_file;
	u16			result=0;

	GF_ASSERT_MSG((MONSNO_END+1)>monsno , "ポケモンNOのMAXを超えている");


	FS_InitFile(&p_file);

	FS_OpenFile(&p_file,"poketool/personal/pms.narc");			///< 大元ポケモンテーブルオープン

	FS_SeekFile(&p_file,monsno*2,FS_SEEK_SET);				///< MONSNOx2分をシーク
	FS_ReadFile(&p_file,&result,2);							///< 読み込み

	FS_CloseFile(&p_file);

	return result;
}


//==============================================================================
/**
 * @brief   レギュレーション用に進化ポケモンをチェックする関数
 *
 * @param   monsno	開発NO
 *
 * @retval  u16		進化ポケモンなら種のNOを返す、種なら自分のNOが返る
 */
//==============================================================================
u16 PokeChildCheck( const u16 monsno )
{
	// 種ポケを持っているのだが、あえて種扱いしてあげるポケモンを羅列
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
	
	// 通常ポケモンの種ポケモン取得処理
	return PokeSearchChild(monsno);
}

//============================================================================================
/**
 *	モンスターナンバーとレベルから技をセットする。
 *
 * @param[in]	pp	セットするポケモンデータ構造体のポインタ
 */
//============================================================================================
void	PokeWazaOboe(POKEMON_PARAM *pp)
{
	POKEMON_PASO_PARAM	*ppp=PPPPointerGet(pp);

	PokePasoWazaOboe(ppp);
}

//============================================================================================
/**
 *	モンスターナンバーとレベルから技をセットする。
 *
 * @param[in]	ppp	セットするポケモンデータ構造体のポインタ
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
 *	あいている場所に技を追加する。あいていない場合はその旨を返す。
 *
 *	@param[in]	pp		セットするポケモンパラメータ構造体のポインタ
 *	@param[in]	wazano	セットする技ナンバー
 *
 *	@retvl	wazano			正常終了
 *			SAME_WAZA_SET	すでに覚えている技と同じ技を覚えようとした
 *			NO_WAZA_SET		場所が空いていない
 */
//============================================================================================
u16	PokeWazaSet(POKEMON_PARAM *pp,u16 wazano)
{
	POKEMON_PASO_PARAM	*ppp=PPPPointerGet(pp);

	return PokePasoWazaSet(ppp,wazano);
}

//============================================================================================
/**
 *	あいている場所に技を追加する。あいていない場合はその旨を返す。
 *
 *	@param[in]	ppp		セットするポケモンパラメータ構造体のポインタ
 *	@param[in]	wazano	セットする技ナンバー
 *
 *	@retvl	wazano			正常終了
 *			SAME_WAZA_SET	すでに覚えている技と同じ技を覚えようとした
 *			NO_WAZA_SET		場所が空いていない
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
			//同じ技を覚えちゃだめ
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
 *	押し出し式に技を覚える。
 *
 * @param[in]	pp		セットするポケモンパラメータ構造体のポインタ
 * @param[in]	wazano	覚える技
 */
//============================================================================================
void	PokeWazaOboeOshidashi(POKEMON_PARAM *pp,u16 wazano)
{
	POKEMON_PASO_PARAM	*ppp=PPPPointerGet(pp);

	PokePasoWazaOboeOshidashi(ppp,wazano);
}

//============================================================================================
/**
 *	押し出し式に技を覚える。
 *
 * @param[in]	ppp		セットするポケモンパラメータ構造体のポインタ
 * @param[in]	wazano	覚える技
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
 *	場所を指定して技をセットする。
 *
 * @param[in]	pp		セットするポケモンパラメータ構造体のポインタ
 * @param[in]	wazano	セットする技ナンバー
 * @param[in]	pos		技をセットする場所
 */
//============================================================================================
void	PokeWazaSetPos(POKEMON_PARAM *pp,u16 wazano,u8 pos)
{
	PokePasoWazaSetPos(&pp->ppp,wazano,pos);
}

//============================================================================================
/**
 *	場所を指定して技をセットする。
 *
 * @param[in]	ppp		セットするポケモンパラメータ構造体のポインタ
 * @param[in]	wazano	セットする技ナンバー
 * @param[in]	pos		技をセットする場所
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
 *	レベルアップ時に覚える技をセットする。
 *
 * @param[in]		pp		セットする構造体のポインタ
 * @param[in/out]	cnt		技覚えテーブルのカウンタ
 * @param[in/out]	wazano	覚えた技の格納ワーク
 *
 * @retval	セットした技ナンバー（NO_WAZA_OBOE:覚えなかった NO_WAZA_SET:技がいっぱい）
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
 *	技の入れ替えをする
 *
 * @param[in]		pp			セットする構造体のポインタ
 * @param[in]		src_pos		入れ替え元位置
 * @param[in]		dest_pos	入れ替え先位置
 */
//============================================================================================
void	PokeParaWazaReplace(POKEMON_PARAM *pp,int src_pos,int dest_pos)
{
	PokePasoParaWazaReplace(&pp->ppp,src_pos,dest_pos);
}

//============================================================================================
/**
 *	技の入れ替えをする
 *
 * @param[in]		pp			セットする構造体のポインタ
 * @param[in]		src_pos		入れ替え元位置
 * @param[in]		dest_pos	入れ替え先位置
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
 * 指定位置の技をクリアして、シフトする
 *
 * @param[in]	pp		クリアする構造体のポインタ
 * @param[in]	pos		クリア位置
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
 * 技を持っているかチェック
 *
 * @param[in]	pp		チェックする構造体のポインタ
 * @param[in]	waza_no	チェックする技ナンバー
 *
 * @retval FALSE:もっていない　TRUE:もっている
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
 *	ボックスの構造体宣言から手持ちの構造体宣言へデータを
 *	コピーして再計算をする
 *
 * @param[in]	ppp	ボックスの構造体のポインタ
 * @param[in]	pp	コピーする手持ちの構造体のポインタ
 */
//============================================================================================
void	PokeReplace(POKEMON_PASO_PARAM *ppp,POKEMON_PARAM *pp)
{
	u32				i=0;
	MAIL_DATA		*mail_data;
//	CB_SAVE_DATA	*cb_core;
	CB_CORE			cb_core;

	pp->ppp=*ppp;

	//pppがfastモードなら、pcpもfastモードにする
	if(pp->ppp.ppp_fast_mode){
		pp->ppp.pp_fast_mode=1;
	}

//コンディションセット
	PokeParaPut(pp,ID_PARA_condition,(u8 *)&i);

//HP初期化
	PokeParaPut(pp,ID_PARA_hp,(u8 *)&i);
	PokeParaPut(pp,ID_PARA_hpmax,(u8 *)&i);

//メールデータ
	mail_data=MailData_CreateWork(HEAPID_BASE_SYSTEM);
	PokeParaPut(pp,ID_PARA_mail_data,mail_data);
	sys_FreeMemoryEz(mail_data);

//カスタムボールID
	PokeParaPut(pp,ID_PARA_cb_id,(u8 *)&i);

//カスタムボール
//	cb_core=CustomBall_AllocSaveData(HEAPID_BASE_SYSTEM);
//	PokeParaPut(pp,ID_PARA_cb_core,cb_core);
//	sys_FreeMemoryEz(cb_core);
	
	MI_CpuClearFast(&cb_core, sizeof(CB_CORE));
	PokeParaPut(pp,	ID_PARA_cb_core, (CB_CORE*)&cb_core);

	PokeParaCalc(pp);
}

//============================================================================================
/**
 *	手持ちポケモンの最大レベルを取得
 *
 * @param[in]	pp	手持ちポケモンデータ構造体
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
 *	全国図鑑ナンバーからシンオウ図鑑ナンバーを返す
 *
 * @param[in]	pp	手持ちポケモンデータ構造体
 *
 * @retval	シンオウ図鑑ナンバー
 */
//============================================================================================
u16		PokeParaZenkokuNo2ShinouNo(POKEMON_PARAM *pp)
{
	return PokePasoParaZenkokuNo2ShinouNo(&pp->ppp);
}

//============================================================================================
/**
 *	全国図鑑ナンバーからシンオウ図鑑ナンバーを返す
 *
 * @param[in]	ppp	ボックスポケモンデータ構造体
 *
 * @retval	シンオウ図鑑ナンバー
 */
//============================================================================================
u16		PokePasoParaZenkokuNo2ShinouNo(POKEMON_PASO_PARAM *ppp)
{
	return PokeZenkokuNo2ShinouNo(PokePasoParaGet(ppp,ID_PARA_monsno,NULL));
}

//============================================================================================
/**
 *	全国図鑑ナンバーからシンオウ図鑑ナンバーを返す
 *
 * @param[in]	mons_no	全国図鑑ナンバー
 *
 * @retval	シンオウ図鑑ナンバー
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
 *	シンオウ図鑑ナンバーから全国図鑑ナンバーを返す
 *
 * @param[in]	mons_no	シンオウ図鑑ナンバー
 *
 * @retval	全国図鑑ナンバー
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
 *	POKEMON_PARAM構造体からPOKEMON_PARAM構造体へコピー
 *
 * @param[in]	pp_src	コピー元POKEMON_PARAM構造体
 * @param[in]	pp_dest	コピー先POKEMON_PARAM構造体
 *
 * @retval	全国図鑑ナンバー
 */
//============================================================================================
void	PokeCopyPPtoPP(POKEMON_PARAM *pp_src,POKEMON_PARAM *pp_dest)
{
	*pp_dest=*pp_src;

	return;
}

//============================================================================================
/**
 *	POKEMON_PASO_PARAM構造体からPOKEMON_PASO_PARAM構造体へコピー
 *
 * @param[in]	ppp_src		コピー元POKEMON_PASO_PARAM構造体
 * @param[in]	ppp_dest	コピー先POKEMON_PASO_PARAM構造体
 *
 * @retval	全国図鑑ナンバー
 */
//============================================================================================
void	PokeCopyPPPtoPPP(POKEMON_PASO_PARAM *ppp_src,POKEMON_PASO_PARAM *ppp_dest)
{
	*ppp_dest=*ppp_src;

	return;
}

//============================================================================================
/**
 *	POKEMON_PARAM構造体からPOKEMON_PASO_PARAM構造体へコピー
 *
 * @param[in]	pp_src		コピー元POKEMON_PARAM構造体
 * @param[in]	ppp_dest	コピー先POKEMON_PASO_PARAM構造体
 *
 * @retval	全国図鑑ナンバー
 */
//============================================================================================
void	PokeCopyPPtoPPP(POKEMON_PARAM *pp_src,POKEMON_PASO_PARAM *ppp_dest)
{
	*ppp_dest=pp_src->ppp;

	return;
}

//============================================================================================
/**
 *	ポケモンの好みの味かどうかチェック
 *
 * @param[in]	pp		POKEMON_PARAM構造体
 * @param[in]	taste	チェックする味
 *
 * @retval	-1:嫌い　0:普通　1:好き
 */
//============================================================================================
s8	PokeParaLikeTasteCheck(POKEMON_PARAM *pp,int taste)
{
	return PokePasoParaLikeTasteCheck(&pp->ppp,taste);
}

//============================================================================================
/**
 *	ポケモンの好みの味かどうかチェック
 *
 * @param[in]	ppp		POKEMON_PASO_PARAM構造体
 * @param[in]	taste	チェックする味
 *
 * @retval	-1:嫌い　0:普通　1:好き
 */
//============================================================================================
s8	PokePasoParaLikeTasteCheck(POKEMON_PASO_PARAM *ppp,int taste)
{
	return PokeLikeTasteCheck(PokePasoParaGet(ppp,ID_PARA_personal_rnd,NULL),taste);
}

//============================================================================================
/**
 *	ポケモンの好みの味かどうかチェック
 *
 * @param[in]	rnd		ポケモンの個性乱数（性格を導くのに必要）
 * @param[in]	taste	チェックする味
 *
 * @retval	-1:嫌い　0:普通　1:好き
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
 * レベルアップで覚える技を全てリストアップ
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
 *	ポケモンにポケルスを感染させる
 *
 * @param	ppt		POKEPARTY構造体へのポインタ
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
 *	ポケモンがポケルスに感染しているかチェック
 *
 * @param[in]	ppt			感染をチェックするPOKEPARTY構造体のポインタ
 * @param[in]	checkbit	0bit目をON：PP[0]をチェック
 *									:
 *									:
 *							5bit目をON：PP[6]をチェック
 *							0のときは、PP[0]だけをチェック
 *
 * @retval	感染しているポケモンをビットで返す
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

					GF_ASSERT_MSG(count>pos,"POKEPARTYに登録されていない位置を参照しようとしてます\n");
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
 *	ポケモンがポケルスに感染しているかチェック（過去に感染していたことも込み）
 *
 * @param[in]	ppt			感染をチェックするPOKEPARTY構造体のポインタ
 * @param[in]	checkbit	0bit目をON：PP[0]をチェック
 *									:
 *									:
 *							5bit目をON：PP[6]をチェック
 *							0のときは、PP[0]だけをチェック
 *
 * @retval	感染しているポケモンをビットで返す
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

					GF_ASSERT_MSG(count>pos,"POKEPARTYに登録されていない位置を参照しようとしてます\n");
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
 *	ポケルスの日数カウンターをデクリメントする
 *
 * @param[in]	ppt		チェックするPOKEPARTY構造体のポインタ
 * @param[in]	day		経過日数
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
 *	ポケルスの感染チェックルーチン
 *
 * @param[in]	ppt	感染をチェックするPOKEPARTY構造体のポインタ
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
 *	ポケルスに感染しているかチェック
 *
 * @param[in]	pp	感染をチェックするPOKEMON_PARAM構造体のポインタ
 *
 * @retval FALSE:感染していない　TRUE:感染している
 */
//============================================================================================
BOOL	PokeParaPokerusCheck(POKEMON_PARAM *pp)
{
	return PokePasoParaPokerusCheck(&pp->ppp);
}

//============================================================================================
/**
 *	ポケルスに感染しているかチェック
 *
 * @param[in]	ppp	感染をチェックするPOKEMON_PASO_PARAM構造体のポインタ
 *
 * @retval FALSE:感染していない　TRUE:感染している
 */
//============================================================================================
BOOL	PokePasoParaPokerusCheck(POKEMON_PASO_PARAM *ppp)
{
	return ((PokePasoParaGet(ppp,ID_PARA_pokerus,NULL)&0x0f)!=0);
}

//============================================================================================
/**
 *	過去にポケルスに感染していたかチェック
 *
 * @param[in]	pp	感染をチェックするPOKEMON_PARAM構造体のポインタ
 *
 * @retval FALSE:感染していない　TRUE:感染していた
 */
//============================================================================================
BOOL	PokeParaPokerusedCheck(POKEMON_PARAM *pp)
{
	return PokePasoParaPokerusedCheck(&pp->ppp);
}

//============================================================================================
/**
 *	過去にポケルスに感染していたかチェック
 *
 * @param[in]	ppp	感染をチェックするPOKEMON_PASO_PARAM構造体のポインタ
 *
 * @retval FALSE:感染していない　TRUE:感染していた
 */
//============================================================================================
BOOL	PokePasoParaPokerusedCheck(POKEMON_PASO_PARAM *ppp)
{
	u8	pokerus;

	pokerus=PokePasoParaGet(ppp,ID_PARA_pokerus,NULL);
	
	//今、かかっている場合は、FALSE
	if(pokerus&0x0f){
		return FALSE;
	}

	return ((pokerus&0xf0)!=0);
}

//============================================================================================
/**
 *	装備道具を調べて、アウスのform_noをセット
 *
 * @param[in]	pp	セットするPOKEMON_PARAM構造体のポインタ
 */
//============================================================================================
void	PokeParaAusuFormChange(POKEMON_PARAM *pp)
{
	PokePasoParaAusuFormChange(&pp->ppp);
}

//============================================================================================
/**
 *	装備道具を調べて、アウスのform_noをセット
 *
 * @param[in]	ppp	セットするPOKEMON_PASO_PARAM構造体のポインタ
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
 *	装備効果からアウスのタイプを取得
 *
 * @param[in]	item_param	アイテムの装備効果
 *
 * @retval	タイプ
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
 *	技覚えテーブルデータを取得
 *
 * @param[in]	monsno		取得するポケモンナンバー
 * @param[out]	wot		取得した技覚えテーブルの格納先
 */
//============================================================================================
void	PokeWazaOboeDataGet(int monsno,u16 *wot)
{
	ArchiveDataLoad(wot,ARC_WOTBL,monsno);
}

//============================================================================================
/**
 *	技覚えテーブルデータを取得
 *
 * @param[in]	monsno		取得するポケモンナンバー
 * @param[in]	form_no		取得するポケモンのフォルムナンバー
 * @param[out]	wot			取得した技覚えテーブルの格納先
 */
//============================================================================================
void	PokeFormNoWazaOboeDataGet(int monsno,int form_no,u16 *wot)
{
	monsno=PokeOtherFormMonsNoGet(monsno,form_no);

	ArchiveDataLoad(wot,ARC_WOTBL,monsno);
}

//============================================================================================
/**
 *	ポケモン鳴き声再生（ぺラップ判定あり）
 *
 * @param[in]	p_voice		ぺラップの鳴き声データの入ったワーク
 * @param[in]	voice		Voiceパターン
 * @param[in]	monsno		鳴かせるモンスターナンバー
 * @param[in]	pan			パンデータ
 * @param[in]	vol			ボリュームデータ
 * @param[in]	flag		へんしんフラグ
 * @param[in]	heapID		ヒープID
 */
//============================================================================================
void	PokeVoicePlaySet(PERAPVOICE *p_voice,int voice,u16 monsno,int pan,int vol,int flag,int heapID)
{
	if(monsno==MONSNO_PERAPPU){
		//鳴き声再生パターンが技系の時はデフォルトの鳴き声を再生するようにする！
		if( Snd_PerapVoicePMVoiceTypeCheck( voice ) == FALSE ){
			Snd_PerapVoiceDefaultFlagSet( TRUE );		//defaultの鳴き声を再生するフラグON
			Snd_PMVoicePlayEx(voice,monsno,pan,vol,heapID);
		}else{
			//へんしんペラップは、defaultの鳴き声を再生
			if(flag){
				Snd_PerapVoiceDefaultFlagSet( TRUE );		//defaultの鳴き声を再生するフラグON
			}
			Snd_PerapVoicePlay(p_voice,NULL,vol,pan);	//録音した鳴き声を再生
		}

	}
	else{
		Snd_PMVoicePlayEx(voice,monsno,pan,vol,heapID);
	}
}

//============================================================================================
/**
 *	ポケモン捕獲情報を格納
 *
 * @param[in]	pp			捕獲情報を格納するPOKEMON_PARAM構造体
 * @param[in]	status		my_status（IDNoと親名の取得に必要）
 * @param[in]	ball		捕獲ボール
 * @param[in]	place		捕獲場所コード
 * @param[in]	ground_id	捕獲場所アトリビュート
 * @param[in]	heapID		ヒープID（親名格納時のバッファ生成に必要）
 */
//============================================================================================
void	PokeParaGetInfoSet(POKEMON_PARAM *pp,MYSTATUS *status,int ball,int place,int ground_id,int heapID)
{
	int	data;

	PokePasoParaGetInfoSet(&pp->ppp,status,ball,place,ground_id,heapID);

	//捕獲したボールがヒールボールならば、HP全快、状態異常も回復する
	if(ball==ITEM_HIIRUBOORU){
		data=PokeParaGet(pp,ID_PARA_hpmax,NULL);
		PokeParaPut(pp,ID_PARA_hp,&data);
		data=0;
		PokeParaPut(pp,ID_PARA_condition,&data);
	}
}

//============================================================================================
/**
 *	ポケモン捕獲情報を格納
 *
 * @param[in]	ppp			捕獲情報を格納するPOKEMON_PASO_PARAM構造体
 * @param[in]	status		my_status（IDNoと親名の取得に必要）
 * @param[in]	ball		捕獲ボール
 * @param[in]	place		捕獲場所コード
 * @param[in]	ground_id	捕獲場所アトリビュート
 * @param[in]	heapID		ヒープID（親名格納時のバッファ生成に必要）
 */
//============================================================================================
void	PokePasoParaGetInfoSet(POKEMON_PASO_PARAM *ppp,MYSTATUS *status,int ball,int place,int ground_id,int heapID)
{
//	RTCDate	rtc_d;
//	STRBUF	*str;

//	GF_RTC_GetDate(&rtc_d);

	//捕獲時間をセット
//	PokePasoParaPut(ppp,ID_PARA_get_year,&rtc_d.year);
//	PokePasoParaPut(ppp,ID_PARA_get_month,&rtc_d.month);
//	PokePasoParaPut(ppp,ID_PARA_get_day,&rtc_d.day);

	//捕獲地域をセット
//	PokePasoParaPut(ppp,ID_PARA_get_place,&place);

	//捕獲レベルをセット
//	data=PokePasoParaGet(ppp,ID_PARA_level,NULL);
//	PokePasoParaPut(ppp,ID_PARA_get_level,&data);

	//IDNoをセット
//	data=MyStatus_GetID(status);
//	PokePasoParaPut(ppp,ID_PARA_id_no,&data);

	//親の性別をセット
//	data=MyStatus_GetMySex(status);
//	PokePasoParaPut(ppp,ID_PARA_oyasex,&data);

	//親名をセット
//	str=MyStatus_CreateNameString(status,heapID);
//	PokePasoParaPut(ppp,ID_PARA_oyaname_buf,str);
//	STRBUF_Delete(str);

	//上の項目を一括して格納する関数に置き換え
	TrainerMemoSetPPP(ppp,status,TRMEMO_POKE_PLACESET,place,heapID);

	//捕獲カセットバージョンをセット
	PokePasoParaPut(ppp,ID_PARA_get_cassette,&CasetteVersion);
	//捕獲ボールをセット
	PokePasoParaPut(ppp,ID_PARA_get_ball,&ball);

	//捕獲地形アトリビュートをセット
	PokePasoParaPut(ppp,ID_PARA_get_ground_id,&ground_id);
}

//============================================================================================
/**
 *	ポケモン孵化情報を格納
 *
 * @param[in]	pp			孵化情報を格納するPOKEMON_PARAM構造体
 * @param[in]	status		my_status（IDNoと親名の取得に必要）
 * @param[in]	ball		孵化ボール
 * @param[in]	place		孵化場所コード
 * @param[in]	ground_id	孵化場所アトリビュート
 * @param[in]	heapID		ヒープID（親名格納時のバッファ生成に必要）
 */
//============================================================================================
void	PokeParaBirthInfoSet(POKEMON_PARAM *pp,MYSTATUS *status,int ball,int place,int ground_id,int heapID)
{
	PokePasoParaBirthInfoSet(&pp->ppp,status,ball,place,ground_id,heapID);
}

//============================================================================================
/**
 *	ポケモン孵化情報を格納
 *
 * @param[in]	pp			孵化情報を格納するPOKEMON_PARAM構造体
 * @param[in]	status		my_status（IDNoと親名の取得に必要）
 * @param[in]	ball		孵化ボール
 * @param[in]	place		孵化場所コード
 * @param[in]	ground_id	孵化場所アトリビュート
 * @param[in]	heapID		ヒープID（親名格納時のバッファ生成に必要）
 */
//============================================================================================
void	PokePasoParaBirthInfoSet(POKEMON_PASO_PARAM *ppp,MYSTATUS *status,int ball,int place,int ground_id,int heapID)
{
	int	data;
//	RTCDate	rtc_d;
//	STRBUF	*str;

	//捕獲情報を格納
	PokePasoParaGetInfoSet(ppp,status,ball,place,ground_id,heapID);

//	GF_RTC_GetDate(&rtc_d);

	//孵化時間をセット
//	PokePasoParaPut(ppp,ID_PARA_birth_year,&rtc_d.year);
//	PokePasoParaPut(ppp,ID_PARA_birth_month,&rtc_d.month);
//	PokePasoParaPut(ppp,ID_PARA_birth_day,&rtc_d.day);

	//孵化地域をセット
//	PokePasoParaPut(ppp,ID_PARA_birth_place,&place);
}

//============================================================================================
/**
 *	野性ポケモンに持たせるアイテムのセット
 *
 * @param[in]	pp			アイテムを持たせるPOKEMON_PARAM構造体
 * @param[in]	fight_type	戦闘タイプ
 * @param[in]	range		確率テーブルID（poke_tool.hに定義）
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

	//アイテムデータに両方同じナンバーが入っている場合は、必ず持たせる
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
 *	ポケモンに技マシンが使えるかチェック
 *
 * @param[in]	pp			チェックするPOKEMON_PARAM構造体
 * @param[in]	machine_no	チェックする技マシンナンバー
 *
 * @retval	FALSE:使えない　TRUE:使える
 */
//============================================================================================
BOOL	PokeParaWazaMachineCheck(POKEMON_PARAM *pp,u8 machine_no)
{
	return	PokePasoParaWazaMachineCheck(&pp->ppp,machine_no);
}

//============================================================================================
/**
 *	ポケモンに技マシンが使えるかチェック
 *
 * @param[in]	ppp			チェックするPOKEMON_PASO_PARAM構造体
 * @param[in]	machine_no	チェックする技マシンナンバー
 *
 * @retval	FALSE:使えない　TRUE:使える
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
 *	ポケモンに技マシンが使えるかチェック
 *
 * @param[in]	mons_no		チェックするポケモンナンバー
 * @param[in]	form_no		チェックするフォルムナンバー
 * @param[in]	machine_no	チェックする技マシンナンバー
 *
 * @retval	FALSE:使えない　TRUE:使える
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
 *	ポケモンに特性をセット
 *
 * @param[in]	pp		POKEMON_PARAM構造体のポインタ
 */
//============================================================================================
void	PokeParaSpeabiSet(POKEMON_PARAM *pp)
{
	PokePasoParaSpeabiSet(&pp->ppp);
}

//============================================================================================
/**
 *	ポケモンに特性をセット
 *
 * @param[in]	ppp		POKEMON_PASO_PARAM構造体のポインタ
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

//特殊能力セット
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
 *	個性乱数を書き換える（個性乱数をキーにしているものがあるので、専用関数にする）
 *
 * @param[in]	pp				POKEMON_PARAM構造体のポインタ
 * @param[in]	personal_rnd	書き換える個性乱数
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
 *							外部公開しない関数郡
 */
//============================================================================================
//============================================================================================
/**
 *	ポケモンパーソナル構造体データを取得
 *
 * @param[in]	mons_no	取得したいポケモンナンバー
 * @param[out]	ppd		取得したパーソナルデータの格納先を指定
 */
//============================================================================================
static	void	PokePersonalDataGet(int mons_no,POKEMON_PERSONAL_DATA *ppd)
{
	ArchiveDataLoad(ppd,ARC_PERSONAL,mons_no);
}

//============================================================================================
/**
 *	ポケモンパーソナル構造体データを取得
 *
 * @param[in]	mons_no	取得したいポケモンナンバー
 * @param[in]	form_no	取得したいポケモンのフォルムナンバー
 * @param[out]	ppd		取得したパーソナルデータの格納先を指定
 */
//============================================================================================
static	void	PokeFormNoPersonalDataGet(int mons_no,int form_no,POKEMON_PERSONAL_DATA *ppd)
{
	mons_no=PokeOtherFormMonsNoGet(mons_no,form_no);

	ArchiveDataLoad(ppd,ARC_PERSONAL,mons_no);
}

//============================================================================================
/**
 *	進化テーブル構造体データを取得
 *
 * @param[in]	mons_no	取得したいポケモンナンバー
 * @param[out]	psd		取得した進化データの格納先を指定
 */
//============================================================================================
static	void	PokeShinkaDataGet(int mons_no,POKEMON_SHINKA_TABLE *pst)
{
	ArchiveDataLoad(pst,ARC_EVO,mons_no);
}


//============================================================================================
/**
 *	暗号処理
 *
 * @param[in]	data	暗号化するデータのポインタ
 * @param[in]	size	暗号化するデータのサイズ
 * @param[in]	code	暗号化キーの初期値
 */
//============================================================================================
static	void	PokeParaCoded(void *data,u32 size,u32 code)
{
	int	i;
	u16	*data_p=(u16 *)data;

	//暗号は、乱数暗号キーでマスク
	for(i=0;i<size/2;i++){
		data_p[i]^=CodeRand(&code);
	}
}

//============================================================================================
/**
 *	復号処理
 *
 * @param[in]	data	復号するデータのポインタ
 * @param[in]	size	復号するデータのサイズ
 * @param[in]	code	暗号化キーの初期値
 */
//============================================================================================
static	void	PokeParaDecoded(void *data,u32 size,u32 code)
{
	PokeParaCoded(data,size,code);
}

//============================================================================================
/**
 *	乱数暗号キー生成ルーチン
 *
 * @param[in,out]	code	暗号キー格納ワークのポインタ
 *
 * @return	暗号キー格納ワークの上位2バイトを暗号キーとして返す
 */
//============================================================================================

static	u16 CodeRand(u32 *code)
{
    code[0] = code[0] *1103515245L + 24691;
    return (u16)(code[0] / 65536L) ;
}

//============================================================================================
/**
 *	ポケモンパラメータのチェックサムを生成
 *
 * @param[in]	data	ポケモンパラメータ構造体のポインタ
 * @param[in]	size	チェックサムを生成するデータのサイズ
 *
 * @return	生成したチェックサム
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
 *	ボックスポケモンパラメータ構造体内のメンバのアドレスを取得
 *
 * @param[in]	ppp	取得したいボックスポケモンパラメータ構造体のポインタ
 * @param[in]	rnd	構造体入れ替えのキー
 * @param[in]	id	取り出したいメンバのインデックス（poke_tool.hに定義）
 *
 * @return	取得したアドレス
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
 * @brief	別フォルムのモンスターナンバーの取得
 *
 * @param	mons_no	取得するモンスターナンバー
 * @param	form_no	取得するフォルムナンバー
 *
 * @retval	mons_no	
 */
//--------------------------------------------------------------
static	int	PokeOtherFormMonsNoGet(int mons_no,int form_no)
{
	//フォルムによって、パーソナルが変化するものをチェック
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
 *	NoをBitに変換(３１まで）
 *
 * @param[in]	no		変換するナンバー
 *
 * @retval	no=0:0x01 …
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
 *	BitをNoに変換(３１まで）
 *
 * @param[in]	bit		変換するナンバー
 *
 * @retval	no=0x01:0…
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
 *	バトルタワーに参加できないポケモンかをチェック（ポケモン番号から）
 *
 * @param	mons	ポケモン番号
 *
 * @retval	"TRUE = そうです"
 * @retval	"FALSE = 違います"
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

//参加不可能なポケモンのモンスターNoを返す
u16 BattleTowerExPoke_MonsNoGet(u8 idx)
{
	if(idx >= NELEMS(BattleTowerExPoke)){
		idx = 0;
	}
	return BattleTowerExPoke[idx];
}

//============================================================================================
/**
 *	バトルタワーに参加できないポケモンかをチェック（POKEMON_PARAMから）
 *
 * @param	pp		POKEMON_PARAM
 *
 * @retval	"TRUE = そうです"
 * @retval	"FALSE = 違います"
 */
//============================================================================================
BOOL BattleTowerExPokeCheck_PokePara( POKEMON_PARAM * pp )
{
	u16 mons = (u16)PokeParaGet( pp, ID_PARA_monsno, NULL );

	return BattleTowerExPokeCheck_MonsNo( mons );
}

//============================================================================================
/**
 * @brief	自分のポケモンかチェック
 * @param	pp		対象ポケモンデータ
 * @param	my		プレーヤーデータ
 * @retval	FALSE:他人のポケモン　TRUE:自分のポケモン
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
 * @brief	トレーナーの背面trtypeを取得
 *
 * @param	trtype		取得するtrtype
 *
 * @retval	変換したtrtype
 */
//============================================================================================
int	TrainerBTrTypeGet(int trtype)
{
	//背面はすべてのtrtypeに対応していないので、対応しているものだけ変換
	switch(trtype){
	case TRTYPE_BOY:		//男主人公
	case TRTYPE_GIRL:		//女主人公
		//そのままでOK
		break;
	case TRTYPE_RIVAL:		//ライバル
		trtype=TRTYPE_TRB_RIVAL;
		break;
	case TRTYPE_BTFIVE1:	//五人衆
	case TRTYPE_BTFIVE2:	//五人衆
	case TRTYPE_BTFIVE3:	//五人衆
	case TRTYPE_BTFIVE4:	//五人衆
	case TRTYPE_BTFIVE5:	//五人衆
		trtype=TRTYPE_TRB_BTFIVE1+(trtype-TRTYPE_BTFIVE1);
		break;
	default:
		//ユニオン対戦で、背面のないtrtypeが来るので、性別をあわせる
		if(TT_TrainerTypeSexGet(trtype)==PARA_FEMALE){
			trtype=TRTYPE_GIRL;		//女主人公
		}
		else{
			trtype=TRTYPE_BOY;		//男主人公
		}
		break;
	}

	return trtype;
}


//--------------------------------------------------------------
/**
 * @brief	カスタムボールのデータを初期化する
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
 * 全PPをフル回復
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



