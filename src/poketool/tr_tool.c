
//============================================================================================
/**
 * @file	tr_tool.c
 * @bfief	トレーナーデータツール郡
 * @author	HisashiSogabe
 * @date	05.12.14
 */
//============================================================================================

#include	"common.h"

#include	"battle/battle_common.h"
#include	"battle/trtype_def.h"
#include	"battle/trtype_sex.h"
#include	"poketool/poke_tool.h"
#include	"poketool/pokeparty.h"
#include	"poketool/tr_tool.h"
#include	"system/arc_tool.h"
#include	"system/msgdata.h"
#include	"system/pm_str.h"
#include	"gflib/strbuf_family.h"
#include	"savedata/misc.h"

#include	"msgdata/msg.naix"

//MAKEの依存関係に含めるためにINCLUDE
#include	"trmsg/trtbl.naix"

//============================================================================================
/**
 * 定数宣言
 */
//============================================================================================

//============================================================================================
/**
 * プロトタイプ宣言
 */
//============================================================================================

void	TT_EncountTrainerDataMake(BATTLE_PARAM *bp,const SAVEDATA * sv,int heapID);
u32		TT_TrainerDataParaGet(int tr_id,int id);
BOOL	TT_TrainerMessageCheck(int tr_id,int kindID,int heapID);
void	TT_TrainerMessageGet(int tr_id,int msgID,STRBUF *msg,int heapID);

void	TT_TrainerDataGet(int tr_id,TRAINER_DATA *td);
void	TT_TrainerPokeDataGet(int tr_id,void *tpd);

u8		TT_TrainerTypeSexGet(int trtype);

static	void	TT_EncountTrainerPokeDataMake(BATTLE_PARAM *bp,int num,int heapID);

//============================================================================================
/**
 *	エンカウントトレーナーデータを生成する
 *
 * @param[in/out]	bp		戦闘システムに引き渡す構造体のポインタ
 * @param[in]		sv		セーブデータ構造体（ライバルの名前を取り出すのに必要）
 * @param[in]		heapID	メモリ確保するためのヒープID
 */
//============================================================================================
void	TT_EncountTrainerDataMake(BATTLE_PARAM *bp,const SAVEDATA * sv,int heapID)
{
	TRAINER_DATA	td;
	int				num;
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_trname_dat, heapID);
	STRBUF			*name;
	const STRCODE * rivalname = MISC_GetRivalName(SaveData_GetMiscReadOnly(sv));

	for(num=0;num<CLIENT_MAX;num++){
		if(bp->trainer_id[num]){
			TT_TrainerDataGet(bp->trainer_id[num],&td);
			bp->trainer_data[num]=td;
			if(td.tr_type==TRTYPE_RIVAL){
				PM_strcpy(&bp->trainer_data[num].name[0],rivalname);			
			}
			else{
				name=MSGMAN_AllocString(man,bp->trainer_id[num]);
				STRBUF_GetStringCode(name,&bp->trainer_data[num].name[0],BUFLEN_PERSON_NAME);
				STRBUF_Delete(name);
			}
			TT_EncountTrainerPokeDataMake(bp,num,heapID);
		}
	}

	bp->fight_type|=td.fight_type;

	MSGMAN_Delete(man);
}

//============================================================================================
/**
 *	トレーナーデータを取得する
 *
 * @param[in]	waza_no		取得したい技ナンバー
 * @param[in]	id			取得したい値の種類
 *
 *	@retval	計算結果のダメージ量
 */
//============================================================================================
u32	TT_TrainerDataParaGet(int tr_id,int id)
{
	u32	ret;
	TRAINER_DATA td;

	TT_TrainerDataGet(tr_id,&td);

	switch(id){
	case ID_TD_data_type:		//データタイプ
		ret=td.data_type;
		break;
	case ID_TD_tr_type:			//トレーナー分類
		ret=td.tr_type;
		break;
	case ID_TD_tr_gra:			//トレーナーグラフィック
		ret=td.tr_gra;
		break;
	case ID_TD_poke_count:		//所持ポケモン数
		ret=td.poke_count;
		break;
	case ID_TD_use_item1:		//使用道具1
	case ID_TD_use_item2:		//使用道具2
	case ID_TD_use_item3:		//使用道具3
	case ID_TD_use_item4:		//使用道具4
		ret=td.use_item[id-ID_TD_use_item1];
		break;
	case ID_TD_aibit:			//AIパターン
		ret=td.aibit;
		break;
	case ID_TD_fight_type:		//戦闘タイプ（1vs1or2vs2）
		ret=td.fight_type;
		break;
	}
	return ret;
}

//============================================================================================
/**
 *	トレーナーメッセージデータが存在するかチェック
 *
 * @param[in]	tr_id		チェックしたいトレーナーID
 * @param[in]	kindID		チェックしたいメッセージの種類
 * @param[in]	heapID		テンポラリ領域の生成先ヒープID
 *
 * @retval	TRUE:存在する　FALSE:存在しない
 */
//============================================================================================
BOOL	TT_TrainerMessageCheck(int tr_id,int kindID,int heapID)
{
	ARCHANDLE	*handle;
	int	size;
	u16	ofs;
	u16	data[2];
	BOOL		ret;

	ret=FALSE;

	size=ArchiveDataSizeGet(ARC_TRTBL,0);
	ArchiveDataLoadOfs(&ofs,ARC_TRTBL_OFS,0,tr_id*2,2);
	handle=ArchiveDataHandleOpen(ARC_TRTBL,heapID);

	while(ofs!=size){
		ArchiveDataLoadOfsByHandle(handle,0,ofs,4,&data[0]);
		if((data[0]==tr_id)&&(data[1]==kindID)){
			ret=TRUE;
			break;
		}
		if(data[0]!=tr_id){
			break;
		}
		ofs+=4;
	}
	ArchiveDataHandleClose(handle);

	return ret;
}

//============================================================================================
/**
 *	トレーナーメッセージデータを取得
 *
 * @param[in]	tr_id		取得したいトレーナーID
 * @param[in]	kindID		取得したいメッセージの種類
 * @param[out]	msg			取得したメッセージの格納先へのポインタ
 * @param[in]	heapID		テンポラリ領域の生成先ヒープID
 */
//============================================================================================
void	TT_TrainerMessageGet(int tr_id,int kindID,STRBUF *msg,int heapID)
{
	ARCHANDLE	*handle;
	int	size;
	u16	ofs;
	u16	data[2];

	size=ArchiveDataSizeGet(ARC_TRTBL,0);
	ArchiveDataLoadOfs(&ofs,ARC_TRTBL_OFS,0,tr_id*2,2);
	handle=ArchiveDataHandleOpen(ARC_TRTBL,heapID);

	while(ofs!=size){
		ArchiveDataLoadOfsByHandle(handle,0,ofs,4,&data[0]);
		if((data[0]==tr_id)&&(data[1]==kindID)){
			MSGDAT_GetStrDirect(ARC_MSG,NARC_msg_trmsg_dat,ofs/4,heapID,msg);
			break;
		}
		ofs+=4;
	}
	ArchiveDataHandleClose(handle);

//	GF_ASSERT_MSG(ofs!=size,"TrainerMessage Not Found");
	//メッセージが見つからなかったら、STRBUFをクリアして返す
	if(ofs==size){
		OS_TPrintf("TrainerMessage Not Found");
		STRBUF_Clear(msg);
	}
}

//============================================================================================
/**
 *	トレーナー構造体データを取得
 *
 * @param[in]	tr_id		取得したいトレーナーID
 * @param[in]	td			取得したトレーナーデータの格納先を指定
 */
//============================================================================================
void	TT_TrainerDataGet(int tr_id,TRAINER_DATA *td)
{
	ArchiveDataLoad(td,ARC_TRDATA,tr_id);
}

//============================================================================================
/**
 *	トレーナー持ちポケモン構造体データを取得
 *
 * @param[in]	tr_id		取得したいトレーナーID
 * @param[in]	td			取得したトレーナー持ちポケモンデータの格納先を指定
 */
//============================================================================================
void	TT_TrainerPokeDataGet(int tr_id,void *tpd)
{
	ArchiveDataLoad(tpd,ARC_TRPOKE,tr_id);
}

//============================================================================================
/**
 *	トレーナータイプから性別を取得する
 *
 * @param[in]	trtype		取得したいトレーナータイプ
 */
//============================================================================================
u8	TT_TrainerTypeSexGet(int trtype)
{
	return TrTypeSexTable[trtype];
}

//============================================================================================
/**
 *							外部公開しない関数郡
 */
//============================================================================================
//============================================================================================
/**
 *	エンカウントトレーナー持ちポケモンデータを生成する
 *
 * @param[in/out]	bp		戦闘システムに引き渡す構造体のポインタ
 * @param[in]		num		何番目のトレーナーID？（タッグの時のため）
 * @param[in]		heapID	メモリ確保するためのヒープID
 */
//============================================================================================
static	void	TT_EncountTrainerPokeDataMake(BATTLE_PARAM *bp,int num,int heapID)
{
	void			*buf;
	int				i,j;
	u32				rnd_tmp,rnd;
	u32				seed_tmp;
	u8				pow;
	POKEMON_PARAM	*pp;

	//現在の乱数の種を退避
	seed_tmp=gf_get_seed();

	PokeParty_Init(bp->poke_party[num],POKEMON_TEMOTI_MAX);

	buf=sys_AllocMemory(heapID,sizeof(POKEDATA_TYPE_MULTI)*POKEMON_TEMOTI_MAX);
	pp=PokemonParam_AllocWork(heapID);

	TT_TrainerPokeDataGet(bp->trainer_id[num],buf);

	if(TT_TrainerTypeSexGet(bp->trainer_data[num].tr_type)==PARA_FEMALE){
		rnd_tmp=120;
	}
	else{
		rnd_tmp=136;
	}

	switch(bp->trainer_data[num].data_type){
	case DATATYPE_NORMAL:
		{
			POKEDATA_TYPE_NORMAL	*ptn;

			ptn=(POKEDATA_TYPE_NORMAL *)buf;
			for(i=0;i<bp->trainer_data[num].poke_count;i++){
				//持ちポケモンデータのパラメータを使用して、ポケモンの個性乱数を生成
				rnd=ptn[i].pow+ptn[i].level+ptn[i].monsno+bp->trainer_id[num];
				gf_srand(rnd);
				for(j=0;j<bp->trainer_data[num].tr_type;j++){
					rnd=gf_rand();
				}
				rnd=(rnd<<8)+rnd_tmp;
				pow=ptn[i].pow*31/255;
				PokeParaSet(pp,ptn[i].monsno,ptn[i].level,pow,RND_SET,rnd,ID_NO_RARE,0);
				PokeParty_Add(bp->poke_party[num],pp);
			}
		}
		break;
	case DATATYPE_WAZA:
		{
			POKEDATA_TYPE_WAZA	*ptw;

			ptw=(POKEDATA_TYPE_WAZA *)buf;
			for(i=0;i<bp->trainer_data[num].poke_count;i++){
				//持ちポケモンデータのパラメータを使用して、ポケモンの個性乱数を生成
				rnd=ptw[i].pow+ptw[i].level+ptw[i].monsno+bp->trainer_id[num];
				gf_srand(rnd);
				for(j=0;j<bp->trainer_data[num].tr_type;j++){
					rnd=gf_rand();
				}
				rnd=(rnd<<8)+rnd_tmp;
				pow=ptw[i].pow*31/255;
				PokeParaSet(pp,ptw[i].monsno,ptw[i].level,pow,RND_SET,rnd,ID_NO_RARE,0);
				for(j=0;j<4;j++){
					PokeWazaSetPos(pp,ptw[i].waza[j],j);
				}
				PokeParty_Add(bp->poke_party[num],pp);
			}
		}
		break;
	case DATATYPE_ITEM:
		{
			POKEDATA_TYPE_ITEM	*pti;

			pti=(POKEDATA_TYPE_ITEM *)buf;
			for(i=0;i<bp->trainer_data[num].poke_count;i++){
				//持ちポケモンデータのパラメータを使用して、ポケモンの個性乱数を生成
				rnd=pti[i].pow+pti[i].level+pti[i].monsno+bp->trainer_id[num];
				gf_srand(rnd);
				for(j=0;j<bp->trainer_data[num].tr_type;j++){
					rnd=gf_rand();
				}
				rnd=(rnd<<8)+rnd_tmp;
				pow=pti[i].pow*31/255;
				PokeParaSet(pp,pti[i].monsno,pti[i].level,pow,RND_SET,rnd,ID_NO_RARE,0);
				PokeParaPut(pp,ID_PARA_item,(u8 *)&pti[i].itemno);
				PokeParty_Add(bp->poke_party[num],pp);
			}
		}
		break;
	case DATATYPE_MULTI:
		{
			POKEDATA_TYPE_MULTI	*ptm;

			ptm=(POKEDATA_TYPE_MULTI *)buf;
			for(i=0;i<bp->trainer_data[num].poke_count;i++){
				//持ちポケモンデータのパラメータを使用して、ポケモンの個性乱数を生成
				rnd=ptm[i].pow+ptm[i].level+ptm[i].monsno+bp->trainer_id[num];
				gf_srand(rnd);
				for(j=0;j<bp->trainer_data[num].tr_type;j++){
					rnd=gf_rand();
				}
				rnd=(rnd<<8)+rnd_tmp;
				pow=ptm[i].pow*31/255;
				PokeParaSet(pp,ptm[i].monsno,ptm[i].level,pow,RND_SET,rnd,ID_NO_RARE,0);
				PokeParaPut(pp,ID_PARA_item,(u8 *)&ptm[i].itemno);
				for(j=0;j<4;j++){
					PokeWazaSetPos(pp,ptm[i].waza[j],j);
				}
				PokeParty_Add(bp->poke_party[num],pp);
			}
		}
		break;
	}
	sys_FreeMemoryEz(buf);
	sys_FreeMemoryEz(pp);

	//退避していた乱数の種を戻す
	gf_srand(seed_tmp);
}
			
