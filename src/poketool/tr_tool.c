
//============================================================================================
/**
 * @file	tr_tool.c
 * @bfief	�g���[�i�[�f�[�^�c�[���S
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

//MAKE�̈ˑ��֌W�Ɋ܂߂邽�߂�INCLUDE
#include	"trmsg/trtbl.naix"

//============================================================================================
/**
 * �萔�錾
 */
//============================================================================================

//============================================================================================
/**
 * �v���g�^�C�v�錾
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
 *	�G���J�E���g�g���[�i�[�f�[�^�𐶐�����
 *
 * @param[in/out]	bp		�퓬�V�X�e���Ɉ����n���\���̂̃|�C���^
 * @param[in]		sv		�Z�[�u�f�[�^�\���́i���C�o���̖��O�����o���̂ɕK�v�j
 * @param[in]		heapID	�������m�ۂ��邽�߂̃q�[�vID
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
 *	�g���[�i�[�f�[�^���擾����
 *
 * @param[in]	waza_no		�擾�������Z�i���o�[
 * @param[in]	id			�擾�������l�̎��
 *
 *	@retval	�v�Z���ʂ̃_���[�W��
 */
//============================================================================================
u32	TT_TrainerDataParaGet(int tr_id,int id)
{
	u32	ret;
	TRAINER_DATA td;

	TT_TrainerDataGet(tr_id,&td);

	switch(id){
	case ID_TD_data_type:		//�f�[�^�^�C�v
		ret=td.data_type;
		break;
	case ID_TD_tr_type:			//�g���[�i�[����
		ret=td.tr_type;
		break;
	case ID_TD_tr_gra:			//�g���[�i�[�O���t�B�b�N
		ret=td.tr_gra;
		break;
	case ID_TD_poke_count:		//�����|�P������
		ret=td.poke_count;
		break;
	case ID_TD_use_item1:		//�g�p����1
	case ID_TD_use_item2:		//�g�p����2
	case ID_TD_use_item3:		//�g�p����3
	case ID_TD_use_item4:		//�g�p����4
		ret=td.use_item[id-ID_TD_use_item1];
		break;
	case ID_TD_aibit:			//AI�p�^�[��
		ret=td.aibit;
		break;
	case ID_TD_fight_type:		//�퓬�^�C�v�i1vs1or2vs2�j
		ret=td.fight_type;
		break;
	}
	return ret;
}

//============================================================================================
/**
 *	�g���[�i�[���b�Z�[�W�f�[�^�����݂��邩�`�F�b�N
 *
 * @param[in]	tr_id		�`�F�b�N�������g���[�i�[ID
 * @param[in]	kindID		�`�F�b�N���������b�Z�[�W�̎��
 * @param[in]	heapID		�e���|�����̈�̐�����q�[�vID
 *
 * @retval	TRUE:���݂���@FALSE:���݂��Ȃ�
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
 *	�g���[�i�[���b�Z�[�W�f�[�^���擾
 *
 * @param[in]	tr_id		�擾�������g���[�i�[ID
 * @param[in]	kindID		�擾���������b�Z�[�W�̎��
 * @param[out]	msg			�擾�������b�Z�[�W�̊i�[��ւ̃|�C���^
 * @param[in]	heapID		�e���|�����̈�̐�����q�[�vID
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
	//���b�Z�[�W��������Ȃ�������ASTRBUF���N���A���ĕԂ�
	if(ofs==size){
		OS_TPrintf("TrainerMessage Not Found");
		STRBUF_Clear(msg);
	}
}

//============================================================================================
/**
 *	�g���[�i�[�\���̃f�[�^���擾
 *
 * @param[in]	tr_id		�擾�������g���[�i�[ID
 * @param[in]	td			�擾�����g���[�i�[�f�[�^�̊i�[����w��
 */
//============================================================================================
void	TT_TrainerDataGet(int tr_id,TRAINER_DATA *td)
{
	ArchiveDataLoad(td,ARC_TRDATA,tr_id);
}

//============================================================================================
/**
 *	�g���[�i�[�����|�P�����\���̃f�[�^���擾
 *
 * @param[in]	tr_id		�擾�������g���[�i�[ID
 * @param[in]	td			�擾�����g���[�i�[�����|�P�����f�[�^�̊i�[����w��
 */
//============================================================================================
void	TT_TrainerPokeDataGet(int tr_id,void *tpd)
{
	ArchiveDataLoad(tpd,ARC_TRPOKE,tr_id);
}

//============================================================================================
/**
 *	�g���[�i�[�^�C�v���琫�ʂ��擾����
 *
 * @param[in]	trtype		�擾�������g���[�i�[�^�C�v
 */
//============================================================================================
u8	TT_TrainerTypeSexGet(int trtype)
{
	return TrTypeSexTable[trtype];
}

//============================================================================================
/**
 *							�O�����J���Ȃ��֐��S
 */
//============================================================================================
//============================================================================================
/**
 *	�G���J�E���g�g���[�i�[�����|�P�����f�[�^�𐶐�����
 *
 * @param[in/out]	bp		�퓬�V�X�e���Ɉ����n���\���̂̃|�C���^
 * @param[in]		num		���Ԗڂ̃g���[�i�[ID�H�i�^�b�O�̎��̂��߁j
 * @param[in]		heapID	�������m�ۂ��邽�߂̃q�[�vID
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

	//���݂̗����̎��ޔ�
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
				//�����|�P�����f�[�^�̃p�����[�^���g�p���āA�|�P�����̌������𐶐�
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
				//�����|�P�����f�[�^�̃p�����[�^���g�p���āA�|�P�����̌������𐶐�
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
				//�����|�P�����f�[�^�̃p�����[�^���g�p���āA�|�P�����̌������𐶐�
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
				//�����|�P�����f�[�^�̃p�����[�^���g�p���āA�|�P�����̌������𐶐�
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

	//�ޔ����Ă��������̎��߂�
	gf_srand(seed_tmp);
}
			
