/**
 *	@file	fld_btower.c
 *	@brief	�o�g���^���[�X�N���v�g�֘A�@FieldSub�T�u���[�`��
 *	@author	Miyuki Iwasawa
 *	@date	06.04.17
 */

#include "common.h"
#include "savedata/savedata_def.h"
#include "savedata/savedata.h"
#include "savedata/zukanwork.h"
#include "savedata/perapvoice.h"
#include "savedata/record.h"
#include "system/procsys.h"
#include "system/pm_str.h"
#include "poketool/poke_tool.h"
#include "poketool/monsno.h"
#include "application/p_status.h"
#include "application/pokelist.h"
#include "field/fieldsys.h"
#include "field/field_event.h"
#include "field/encount_set.h"
#include "field/ev_time.h"
#include "field/fieldobj_code.h"
#include "communication/comm_tool.h"
#include "communication/comm_system.h"
#include "communication/comm_def.h"

#include "gflib/strbuf_family.h"


#include "b_tower_scr_def.h"
#define __B_TOWER_FLD_H_GLOBAL
#include "b_tower_fld.h"
#include "b_tower_ev.h"

#include "savedata/b_tower_local.h"

#include "battle/attr_def.h"
//�����f�[�^���o����܂ŃC���N���[�h
#include "itemtool/itemsym.h"
#include "poketool/monsno.h"
#include "battle/wazano_def.h"
#include "battle/battle_common.h"
#include "battle/trtype_def.h"
#include "battle/b_tower_data.h"
#include "battle/trno_def.h"
#include "b_tower_fld.dat"

#include "msgdata\msg.naix"

//============================================================================================
/**
 *	�v���g�^�C�v�錾
 */
//============================================================================================
static void	BattleTowerTrainerDataMake(BATTLE_PARAM *bp,
			B_TOWER_PARTNER_DATA *tr_data,int cnt,int client_no,int heapID);
static BOOL BattleTowerPokemonSetAct(BTOWER_SCRWORK* wk,B_TOWER_TRAINER_ROM_DATA *trd,
		u16 tr_no,B_TOWER_POKEMON *pwd,u8 cnt,
		u16 *set_poke_no,u16 *set_item_no,B_TOWER_PAREPOKE_PARAM* poke,int heapID);
static	u8		BattleTowerPowRndGet(u16 tr_no);
static	void	*BattleTowerTrainerRomDataGet(u16 tr_no,int heapID);
static	void	BattleTowerPokemonRomDataGet(B_TOWER_POKEMON_ROM_DATA *prd,int index);

///�^���[�ɏo������g���[�i�[�^�C�v����OBJ�R�[�h
static const u16 btower_trtype2objcode[][2] = {
 {TRTYPE_BTFIVE1,SEVEN1},	///<�ܐl�O1
 {TRTYPE_BTFIVE2,SEVEN2},	///<�ܐl�O1
 {TRTYPE_BTFIVE3,SEVEN3},	///<�ܐl�O1
 {TRTYPE_BTFIVE4,SEVEN4},	///<�ܐl�O1
 {TRTYPE_BTFIVE5,SEVEN5},	///<�ܐl�O1
 {TRTYPE_TANPAN,	BOY2},	///<����p��������
 {TRTYPE_MINI,	GIRL1},	///<�~�j�X�J�[�g
 {TRTYPE_SCHOOLB,	BOY1},	///<���キ������
 {TRTYPE_SCHOOLG,	GIRL3},	///<���キ������
 {TRTYPE_PRINCE,	GORGGEOUSM},	///<���ڂ������
 {TRTYPE_PRINCESS,	GORGGEOUSW},	///<�����傤����
 {TRTYPE_CAMPB,	CAMPBOY},	///<�L�����v�{�[�C
 {TRTYPE_PICNICG,	PICNICGIRL},	///<�s�N�j�b�N�K�[��
 {TRTYPE_UKIWAB,	BABYBOY1},	///<������{�[�C
 {TRTYPE_UKIWAG,	BABYGIRL1},	///<������K�[��
 {TRTYPE_DAISUKIM,	MIDDLEMAN1},	///<���������N���u
 {TRTYPE_DAISUKIW,	MIDDLEWOMAN1},	///<���������N���u
 {TRTYPE_WAITER,	WAITER},	///<�E�G�[�^�[
 {TRTYPE_WAITRESS,	WAITRESS},	///<�E�G�[�g���X
 {TRTYPE_BREEDERM,	MAN1},	///<�|�P�����u���[�_�[
 {TRTYPE_BREEDERW,	WOMAN1},	///<�|�P�����u���[�_�[
 {TRTYPE_CAMERAMAN,	CAMERAMAN},	///<�J�����}��
 {TRTYPE_REPORTER,	REPORTER},	///<���|�[�^�[
 {TRTYPE_FARMER,	FARMER},	///<�ڂ����傤��������
 {TRTYPE_COWGIRL,	COWGIRL},	///<�J�E�K�[��
 {TRTYPE_CYCLINGM,	CYCLEM},	///<�T�C�N�����O��
 {TRTYPE_CYCLINGW,	CYCLEW},	///<�T�C�N�����O��
 {TRTYPE_KARATE,	FIGHTER},	///<����Ă���
 {TRTYPE_BATTLEG,	GIRL2},	///<�o�g���K�[��
 {TRTYPE_VETERAN,	OLDMAN1},	///<�x�e�����g���[�i�[
 {TRTYPE_MADAM,	LADY},	///<�}�_��
 {TRTYPE_ESPM,	MYSTERY},	///<�T�C�L�b�J�[
 {TRTYPE_ESPW,	MYSTERY},	///<�T�C�L�b�J�[
 {TRTYPE_RANGERM,	MAN3},	///<�|�P���������W���[
 {TRTYPE_RANGERW,	WOMAN3},	///<�|�P���������W���[
 {TRTYPE_ELITEM,	MAN3},	///<�G���[�g�g���[�i�[
 {TRTYPE_ELITEW,	WOMAN3},	///<�G���[�g�g���[�i�[
 {TRTYPE_COLDELITEM,	MAN5},	///<�G���[�g�g���[�i�[���i�����j
 {TRTYPE_COLDELITEW,	WOMAN5},	///<�G���[�g�g���[�i�[���i�����j
 {TRTYPE_DRAGON,	MAN3},	///<�h���S������
 {TRTYPE_MUSHI,	BOY3},	///<�ނ��Ƃ肵�傤�˂�
 {TRTYPE_SHINOBI,	BABYBOY1},	///<�ɂ񂶂Ⴒ����
 {TRTYPE_JOGGER,	SPORTSMAN},	///<�W���M���O��
 {TRTYPE_FISHING,	FISHING},	///<��т�
 {TRTYPE_SAILOR,	SEAMAN},	///<�ӂȂ̂�
 {TRTYPE_MOUNT,	MOUNT},	///<��܂��Ƃ�
 {TRTYPE_ISEKI,	EXPLORE},	///<�������}�j�A
 {TRTYPE_GUITARIST,	MAN2},	///<�M�^���X�g
 {TRTYPE_COLLECTOR,	BIGMAN},	///<�|�P�����R���N�^�[
 {TRTYPE_HEADS,	BADMAN},	///<�X�L���w�b�Y
 {TRTYPE_SCIENTIST,	ASSISTANTM},	///<���񂫂イ����
 {TRTYPE_GENTLE,	GENTLEMAN},	///<�W�F���g���}��
 {TRTYPE_WORKER,	WORKMAN},	///<�����傤����
 {TRTYPE_PIERROT,	CLOWN},	///<�s�G��
 {TRTYPE_POLICE,	POLICEMAN},	///<���܂�肳��
 {TRTYPE_GAMBLER,	GORGGEOUSM},	///<�M�����u���[
 {TRTYPE_BIRD,	WOMAN3},	///<�Ƃ����
 {TRTYPE_PARASOL,	AMBRELLA},	///<�p���\�����˂�����
 {TRTYPE_SISTER,	WOMAN2},	///<���ƂȂ̂��˂�����
 {TRTYPE_AROMA,	WOMAN1},	///<�A���}�Ȃ��˂�����
 {TRTYPE_IDOL,	IDOL},	///<�A�C�h��
 {TRTYPE_ARTIST,	ARTIST},	///<���������
 {TRTYPE_POKEGIRL,	PIKACHU},	///<�|�P������������
};
#define TRTYPE2OBJCODE_MAX	(NELEMS(btower_trtype2objcode))

/**
 *	@brief	�^���[�v���C�X�V�����_���V�[�h�擾 ���E���h�X�V���ɌĂ�
 */
static u16	btower_rand(BTOWER_SCRWORK* wk)
{
	wk->play_rnd_seed = BtlTower_PlayFixRand(wk->play_rnd_seed);

	OS_Printf("btower_rand = %d\n",wk->play_rnd_seed);
	return (wk->play_rnd_seed/65535);
}

/**
 *	@brief	�Q���ł��Ȃ��|�P���������^�O�W�J
 */
WORDSET* BtlTower_SetNgPokeName(SAVEDATA* sv,u16 pokenum,u16 sex,u8 flag,u8* num)
{
	u8	i;
	u16	mons;
	STRBUF *buf,*nbuf;
	ZUKAN_WORK* zukan;	
	WORDSET*	wset;
	MSGDATA_MANAGER* man;

	buf = STRBUF_Create( BUFLEN_POKEMON_NAME+BUFLEN_EOM_SIZE, HEAPID_FIELD );
	nbuf = STRBUF_Create( 2, HEAPID_FIELD );
	zukan = SaveData_GetZukanWork(sv);

	man = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_monsname_dat, HEAPID_FIELD );
	wset = WORDSET_CreateEx(BTOWER_EXPOKE_NUM+1,BUFLEN_POKEMON_NAME+BUFLEN_EOM_SIZE,HEAPID_FIELD);

	WORDSET_RegisterNumber( wset,0,pokenum,1,NUMBER_DISPTYPE_LEFT,NUMBER_CODETYPE_DEFAULT);

	for(i = 0;i < BTOWER_EXPOKE_NUM;i++){
		mons = BattleTowerExPoke_MonsNoGet(i);
		if(ZukanWork_GetPokeSeeFlag(zukan,mons)){
			MSGMAN_GetString(man,mons,buf);
			//�P��Z�b�g
			//�o�b�t�@ID
			//������
			//���ʃR�[�h
			//�P�^���iTRUE�ŒP���j
			//����R�[�h
			WORDSET_RegisterWord( wset,(*num)+1,buf,sex,flag,PM_LANG );
			(*num)++;
		}
	}

	MSGMAN_Delete(man);
	STRBUF_Delete( nbuf );
	STRBUF_Delete( buf );

	return wset;
}

/**
 *	@brief	�g���[�i�[�^�C�v����l��OBJ�R�[�h��Ԃ�
 */
u16 BtlTower_TrType2ObjCode(u8 tr_type)
{
	int i = 0;

	for(i = 0;i < TRTYPE2OBJCODE_MAX;i++){
		if(btower_trtype2objcode[i][0] == tr_type){
			return btower_trtype2objcode[i][1];
		}
	}
	return BOY1;	
}

#if 1
/**
 *	@brief	�V���O���_�u�� �g���[�i�[���I���ʎ擾
 *	
 * @param[in/out]	tr_data		��������B_TOWER_PARTNAER_DATA�\����
 * @param[in]		tr_no		�������ɂȂ�g���[�i�[ID
 * @param[in]		cnt			�g���[�i�[�Ɏ�������|�P�����̐�
 * @param[in]		heapID		�q�[�vID
 */
static void btltower_BtlPartnerSelectSD(B_TOWER_PARTNER_DATA* wk,const u8 round)
{
	int i;

	const B_TOWER_TRAINER *tr_src;
	const B_TOWER_POKEMON *poke_src;
	const B_TOWER_DMYENEMY	*poke_idx;

	MI_CpuClear8(wk,sizeof(B_TOWER_PARTNER_DATA));

	//�{����ROM/RAM�f�[�^������������Ă���
	tr_src = &(b_tower_trainer_data[round]);
	poke_src = b_tower_poke_data;
	poke_idx = &(b_tower_dmy_enemy[round]);

	//�g���[�i�[�f�[�^�R�s�[
	MI_CpuCopy8(tr_src,&wk->bt_trd,sizeof(B_TOWER_TRAINER));
	wk->bt_trd.dummy = poke_idx->obj_code;

	//�|�P�����f�[�^�R�s�[
	for(i = 0;i < 4;i++){
		MI_CpuCopy8(&(poke_src[poke_idx->pokeno[i]]),&(wk->btpwd[i]),sizeof(B_TOWER_POKEMON));
	}
}
#endif
/**
 *	@brief	Wifi �g���[�i�[���I
 */
void btltower_BtlPartnerSelectWifi(SAVEDATA* sv,B_TOWER_PARTNER_DATA* wk,
		const u8 round)
{
	int i;
	
	BTLTOWER_WIFI_DATA*	wifiSave;
	const B_TOWER_TRAINER *tr_src;
	const B_TOWER_POKEMON *poke_src;

	MI_CpuClear8(wk,sizeof(B_TOWER_PARTNER_DATA));
	
	wifiSave = SaveData_GetTowerWifiData(sv);

	if(!TowerWifiData_IsPlayerDataEnable(wifiSave)){
		//�f�[�^���Ȃ�(ROM���疳������I)
		btltower_BtlPartnerSelectSD(wk,round);
		return;
	}

	//�Z�[�u�f�[�^�����������
	TowerWifiData_GetBtlPlayerData(wifiSave,wk,round);
}

//-----------------------------------------------------------------------------
/**
 *	@brief	�o�g���^���[�p�|�P�����f�[�^����POKEMON_PARAM�𐶐�
 */
//-----------------------------------------------------------------------------
static void BtlTower_PokeParaMake(const B_TOWER_POKEMON* src,POKEMON_PARAM* dest)
{
	int i;
	u8	buf8,waza_pp;
	u16	buf16;
	u32	buf32;
	
	PokeParaInit(dest);

	//monsno,level,pow_rnd,idno
	PokeParaSetPowRnd(dest,src->mons_no,50,(src->power_rnd & 0x3FFFFFFF),src->personal_rnd);

	//form_no
	buf8 = src->form_no;
	PokeParaPut(dest,ID_PARA_form_no,&buf8);
	
	//�����A�C�e���ݒ�
	PokeParaPut(dest,ID_PARA_item,&src->item_no);
	
	//�Z�ݒ�
	for(i = 0;i < 4;i++){
		buf16 = src->waza[i];
		PokeParaPut(dest,ID_PARA_waza1+i,&buf16);
		buf8 = (src->pp_count >> (i*2))&0x03;
		PokeParaPut(dest,ID_PARA_pp_count1+i,&buf8);

		//pp�Đݒ�
		waza_pp = (u8)PokeParaGet(dest,ID_PARA_pp_max1+i,NULL);
		PokeParaPut(dest,ID_PARA_pp1+i,&waza_pp);
	}
	
	//ID�ݒ�
	buf32 = src->id_no;	
	PokeParaPut(dest,ID_PARA_id_no,&buf32);

	//�o���l�ݒ�
	buf8 = src->hp_exp;
	PokeParaPut(dest,ID_PARA_hp_exp,&buf8);
	buf8 = src->pow_exp;
	PokeParaPut(dest,ID_PARA_pow_exp,&buf8);
	buf8 = src->def_exp;
	PokeParaPut(dest,ID_PARA_def_exp,&buf8);
	buf8 = src->agi_exp;
	PokeParaPut(dest,ID_PARA_agi_exp,&buf8);
	buf8 = src->spepow_exp;
	PokeParaPut(dest,ID_PARA_spepow_exp,&buf8);
	buf8 = src->spedef_exp;
	PokeParaPut(dest,ID_PARA_spedef_exp,&buf8);

	//�����ݒ�
	PokeParaPut(dest,ID_PARA_speabino,&src->tokusei);
	
	//�Ȃ��ǐݒ�
	PokeParaPut(dest,ID_PARA_friend,&src->natuki);
	
	//NG�l�[���t���O���`�F�b�N
	if(src->ngname_f){
		//�f�t�H���g�l�[����W�J����
		MSGDATA_MANAGER* man;
		STRBUF* def_name;
	
		man = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_monsname_dat, HEAPID_FIELD );
		def_name = MSGMAN_AllocString(man,src->mons_no);
		
		PokeParaPut(dest,ID_PARA_nickname_buf,def_name);

		STRBUF_Delete(def_name);
		MSGMAN_Delete(man);
	}else{
		//�j�b�N�l�[��
		PokeParaPut(dest,ID_PARA_nickname,src->nickname);
	}
	
	//�J���g���[�R�[�h
	PokeParaPut(dest,ID_PARA_country_code,&src->country_code);
	//�p�����[�^�Čv�Z
	PokeParaCalc(dest);
}

/**
 * @brief	�o�g���^���[�@�v���C���[�h����FIGHT_TYPE��Ԃ�
 */
static u32 btower_GetFightType(u8 play_mode)
{
	switch(play_mode){
	case BTWR_MODE_SINGLE:
	case BTWR_MODE_WIFI:
		return FIGHT_TYPE_BATTLE_TOWER_1vs1;
	case BTWR_MODE_DOUBLE:
		return FIGHT_TYPE_BATTLE_TOWER_2vs2;
	case BTWR_MODE_MULTI:
		return FIGHT_TYPE_BATTLE_TOWER_AI_MULTI;	
	case BTWR_MODE_COMM_MULTI:
		return FIGHT_TYPE_BATTLE_TOWER_SIO_MULTI;
	}
	return FIGHT_TYPE_BATTLE_TOWER_1vs1;
}

/**
 *	@brief	�o�g���^���[�@�g���[�i�[�f�[�^����
 */
static void btower_TrainerDataMake(u8 play_mode,B_TOWER_TRAINER* src,TRAINER_DATA* dest)
{
	MI_CpuClear8(dest,sizeof(TRAINER_DATA));

	dest->tr_type = src->tr_type;	//�g���[�i�[�^�C�v
	dest->tr_gra = 0;//src->tr_type;	//�g���[�i�[�^�C�v
	dest->aibit = 0xFFFFFFFF;	//�ŋ�

	//�g���[�i�[��
	PM_strcpy(dest->name,src->name);
	
	//�����������b�Z�[�W
	MI_CpuCopy8(src->win_word,&dest->win_word,sizeof(PMS_DATA));
	MI_CpuCopy8(src->lose_word,&dest->lose_word,sizeof(PMS_DATA));
	
	switch(play_mode){
	case BTWR_MODE_SINGLE:
	case BTWR_MODE_WIFI:
		dest->fight_type = FIGHT_TYPE_1vs1;
		break;
	case BTWR_MODE_DOUBLE:
	case BTWR_MODE_MULTI:
	case BTWR_MODE_COMM_MULTI:
		dest->fight_type = FIGHT_TYPE_2vs2;
		break;	
	}
}

/**
 *	@brief	�g���[�i�[�ΐ�f�[�^����
 */
static void btltower_SetTrainerData(BTOWER_SCRWORK* wk,BATTLE_PARAM* bp,
		B_TOWER_PARTNER_DATA* tr,u8 tr_id,u8 tr_client,u8 poke_client)
{
	int i;
	POKEMON_PARAM *pp;
	
	//�g���[�i�[�f�[�^���Z�b�g
	btower_TrainerDataMake(wk->play_mode,&(tr->bt_trd),&(bp->trainer_data[tr_client]));
	
	//�g���[�i�[ID����
	bp->trainer_id[tr_client] = tr_id;//wk->tr_data[0].bt_trd.tr_type;
	
	//�ΐ푊��̃|�P�����f�[�^���Z�b�g
	pp = PokemonParam_AllocWork(wk->heapID);

	PokeParty_Init(bp->poke_party[poke_client],wk->member_num);
	for(i = 0;i < wk->member_num;i++){
		BtlTower_PokeParaMake(&(tr->btpwd[i]),pp);
		BattleParam_AddPokemon(bp,pp,poke_client);
	}
	sys_FreeMemoryEz(pp);
}

/**
 *	@brief	�o�g���^���[�p�@�o�g���p�����[�^����
 */
extern	void	BattleParam_TrainerDataMake(BATTLE_PARAM *bp);
BATTLE_PARAM* BtlTower_CreateBattleParam(BTOWER_SCRWORK* wk,FIELDSYS_WORK* fsys)
{
	int i;
	u8	val8;
	u32	val32;
	BATTLE_PARAM *bp;
	SAVEDATA* sv;
	POKEPARTY* party;
	POKEMON_PARAM *pp;

	bp = BattleParam_Create(wk->heapID,btower_GetFightType(wk->play_mode));
	
	sv = fsys->savedata;
	party = SaveData_GetTemotiPokemon(sv);
#if 0
	BattleParam_SetMyStatus(bp,SaveData_GetMyStatus(sv),POKEPARTY_MINE);
	MyItem_Copy(SaveData_GetMyItem(sv), bp->my_item);
	ZukanWork_Copy(SaveData_GetZukanWork(sv), bp->zw);
	BattleParam_SetPokeVoice(bp,SaveData_GetPerapVoice(sv), POKEPARTY_MINE);
	CONFIG_Copy(SaveData_GetConfig(sv), bp->config);
	
	//������f�[�^�͑傫������̂ŃR�s�[���Ȃ�
	bp->box = SaveData_GetBoxData(sv);
	bp->time_zone = EVTIME_GetTimeZone(fsys);
	bp->bag_cursor = fsys->bag_cursor;

	bp->record=SaveData_GetRecord(sv);
	bp->fnote_data = fsys->fnote;
	bp->friendlist = SaveData_GetFriendList( fsys->savedata );
	bp->zone_id = fsys->location->zone_id;
#else
	BattleParam_SetParamByGameDataCore(bp,fsys);
	bp->bg_id = BG_ID_ROOM_A;			//��{�w�i�w��
	bp->ground_id = GROUND_ID_FLOOR;	//��{�n�ʎw��
#endif
	//�|�P�����f�[�^�Z�b�g
	pp = PokemonParam_AllocWork(wk->heapID);
	
	//�I�񂾎莝���|�P�������Z�b�g
	val8 = 50;
	PokeParty_Init(bp->poke_party[POKEPARTY_MINE],wk->member_num);
	for(i = 0;i < wk->member_num;i++){
		PokeCopyPPtoPP(PokeParty_GetMemberPointer(party,wk->member[i]),pp);

		//���x������
		if(PokeParaGet(pp,ID_PARA_level,NULL) > val8){
			val32 = PokeLevelExpGet(PokeParaGet(pp,ID_PARA_monsno,NULL),val8);

			PokeParaPut(pp,ID_PARA_exp,&val32);
			PokeParaCalc(pp);
		}
		BattleParam_AddPokemon(bp,pp,POKEPARTY_MINE);
	}
	sys_FreeMemoryEz(pp);

	//�g���[�i�[�f�[�^�����i�������j
	BattleParam_TrainerDataMake(bp);

	//�g���[�i�[�f�[�^(enemy1)���Z�b�g
	BattleTowerTrainerDataMake(bp,&(wk->tr_data[0]),wk->member_num,CLIENT_NO_ENEMY,wk->heapID);
	
	switch(wk->play_mode){
	case BTWR_MODE_MULTI:
		//�y�A�f�[�^���Z�b�g
		BattleTowerTrainerDataMake(bp,&(wk->five_data[wk->partner]),wk->member_num,CLIENT_NO_MINE2,wk->heapID);
		//�������͋��ʏ����ŗ���Ă���
	case BTWR_MODE_COMM_MULTI:
		//�g���[�i�[�f�[�^(enemy2)���Z�b�g
		BattleTowerTrainerDataMake(bp,&(wk->tr_data[1]),wk->member_num,CLIENT_NO_ENEMY2,wk->heapID);
		break;
	default:
		break;
	}
	return bp;
}

//============================================================================
/**
 *	�ʐM�֘A�R�}���h
 */
//============================================================================

/**
 *	@brief	�o�g���^���[�@�����Ă����v���C���[�f�[�^���󂯎��
 */
u16 BTowerComm_RecvPlayerData(FIELDSYS_WORK* fsys,const u16* recv_buf)
{
	u16	ret = 0;
	BTOWER_SCRWORK* wk = fsys->btower_wk;

	wk->pare_sex = (u8)recv_buf[0];
	wk->pare_poke[0] = recv_buf[1];
	wk->pare_poke[1] = recv_buf[2];
	wk->pare_stage = recv_buf[3];

	wk->partner = 5+wk->pare_sex;

	OS_Printf("sio multi mem = %d,%d:%d,%d\n",wk->mem_poke[0],wk->mem_poke[1],wk->pare_poke[0],wk->pare_poke[1]);
	if(	wk->mem_poke[0] == wk->pare_poke[0] ||
		wk->mem_poke[0] == wk->pare_poke[1]){
		ret += 1;
	}
	if(	wk->mem_poke[1] == wk->pare_poke[0] ||
		wk->mem_poke[1] == wk->pare_poke[1]){
		ret += 2;
	}
	return ret;
}

/**
 *	@brief	�o�g���^���[�@�����Ă����g���[�i�[�f�[�^���󂯎��
 */
u16	BTowerComm_RecvTrainerData(FIELDSYS_WORK* fsys,const u16* recv_buf)
{
	int i;
	BTOWER_SCRWORK* wk = fsys->btower_wk;

	if(CommGetCurrentID() == COMM_PARENT_ID){
		return 0;	//�e�͑��M���邾���Ȃ̂Ŏ󂯎��Ȃ�
	}

	MI_CpuCopy8(recv_buf,wk->trainer,BTOWER_STOCK_TRAINER_MAX*2);
	OS_Printf("sio multi trainer01 = %d,%d:%d,%d\n",
			wk->trainer[0],wk->trainer[1],wk->trainer[2],wk->trainer[3]);
	OS_Printf("sio multi trainer02 = %d,%d:%d,%d\n",
			wk->trainer[4],wk->trainer[5],wk->trainer[6],wk->trainer[7]);
	OS_Printf("sio multi trainer03 = %d,%d:%d,%d\n",
			wk->trainer[8],wk->trainer[9],wk->trainer[10],wk->trainer[11]);
	OS_Printf("sio multi trainer04 = %d,%d\n",
			wk->trainer[12],wk->trainer[13]);
	return 1;
}

/**
 *	@brief	�o�g���^���[�@�����Ă������^�C�A���邩�ǂ����̌��ʂ��󂯎��
 *
 *	@retval	0	���^�C�A���Ȃ�
 *	@retval	1	���^�C�A����
 */
u16	BTowerComm_RecvRetireSelect(FIELDSYS_WORK* fsys,const u16* recv_buf)
{
	int i;
	BTOWER_SCRWORK* wk = fsys->btower_wk;

	OS_Printf("sio multi retire = %d,%d\n",wk->retire_f,recv_buf[0]);
	if(wk->retire_f || recv_buf[0]){
		return 1;
	}
	return 0;
}
	
/**
 *	@brief	�o�g���^���[�@���@���ʂƃ����X�^�[No�𑗐M
 */
void BTowerComm_SendPlayerData(BTOWER_SCRWORK* wk,SAVEDATA *sv)
{
	int i;
	POKEPARTY* party;
	POKEMON_PARAM *pp;
	MYSTATUS	*my = SaveData_GetMyStatus(sv);
	
	wk->send_buf[0] = MyStatus_GetMySex(my);
	party = SaveData_GetTemotiPokemon(sv);
	for(i = 0;i < 2;i++){
		wk->send_buf[1+i] =
			PokeParaGet(PokeParty_GetMemberPointer(party,wk->member[i]),
						ID_PARA_monsno,NULL);
	}
	wk->send_buf[3] = 
		TowerScoreData_SetStage(wk->scoreSave,BTWR_MODE_COMM_MULTI,BTWR_DATA_get);
}

/**
 *	@brief	�o�g���^���[�@�ʐM�}���`�@���I�����g���[�i�[No���q�@�ɑ��M
 */
void BTowerComm_SendTrainerData(BTOWER_SCRWORK* wk)
{
	MI_CpuCopy8(wk->trainer,wk->send_buf,BTOWER_STOCK_TRAINER_MAX*2);
}

/**
 *	@brief	�o�g���^���[�@�ʐM�}���`�@���^�C�A���邩�ǂ������݂��ɑ��M
 *
 *	@param	retire	TRUE�Ȃ烊�^�C�A
 */
void BTowerComm_SendRetireSelect(BTOWER_SCRWORK* wk,u16 retire)
{
	//�����̑I�����ʂ����[�N�ɕۑ�
	wk->retire_f = retire;
	wk->send_buf[0] = retire;
}

//============================================================================================
/**
 *	�o�g���^���[�g���[�i�[No�擾�i�����f�[�^�̂��߂̃g���[�i�[ID�擾�j
 *
 * @param[in]	stage		����
 * @param[in]	round		���l��
 * @param[in]	play_mode	�ΐ탂�[�h
 *
 * @retval	trainer_id
 */
//============================================================================================
static const u16 TrainerNoRangeTable[][2]={
	{  1-1,100-1},
	{ 81-1,120-1},
	{101-1,140-1},
	{121-1,160-1},
	{141-1,180-1},
	{161-1,200-1},
	{181-1,220-1},
	{201-1,300-1},
};

static const u16 TrainerNoRangeTable2[][2]={
	{101-1,120-1},
	{121-1,140-1},
	{141-1,160-1},
	{161-1,180-1},
	{181-1,200-1},
	{201-1,220-1},
	{221-1,240-1},
	{201-1,300-1},
};

#define	TOWER_MASTER_FIRST	(305)
#define	TOWER_MASTER_SECOND	(306)

/**
 *	@brief	�g���[�i�[�i���o�[���I
 */
u16	BattleTowerTrainerNoGet(BTOWER_SCRWORK* wk,u8 stage,u8 round,int play_mode)
{
	u16	no;

	//�^���[�^�C�N�[���̓V���O���̂�
	if(play_mode==BTWR_MODE_SINGLE){
		//�^���[�^�C�N�[��1���
		if((stage==2)&&(round==6)){
			return TOWER_MASTER_FIRST;
		}
		//�^���[�^�C�N�[��2���
		if((stage==6)&&(round==6)){
			return TOWER_MASTER_SECOND;
		}
	}

	if(stage<7){
		if(round==(7-1)){
			no=(TrainerNoRangeTable2[stage][1]-TrainerNoRangeTable2[stage][0])+1;
//			no=TrainerNoRangeTable2[stage][0]+(gf_rand()%no);
			no=TrainerNoRangeTable2[stage][0]+(btower_rand(wk)%no);
		}
		else{
			no=(TrainerNoRangeTable[stage][1]-TrainerNoRangeTable[stage][0])+1;
//			no=TrainerNoRangeTable[stage][0]+(gf_rand()%no);
			no=TrainerNoRangeTable[stage][0]+(btower_rand(wk)%no);
		}
	}
	else{
		no=(TrainerNoRangeTable[7][1]-TrainerNoRangeTable[7][0])+1;
//		no=TrainerNoRangeTable[7][0]+(gf_rand()%no);
		no=TrainerNoRangeTable[7][0]+(btower_rand(wk)%no);
	}
	return no;
}

//============================================================================================
/**
 *	�o�g���^���[�@rom�g���[�i�[�f�[�^�W�J
 *
 *	B_TOWER_TRAINER_ROM_DATA�^���������m�ۂ��ĕԂ��̂ŁA
 *	�Ăяo�����������I�ɉ�����邱��
 */
//============================================================================================
static B_TOWER_TRAINER_ROM_DATA* RomTrainerDataAlloc(B_TOWER_PARTNER_DATA *tr_data,u16 tr_no,int heapID)
{
	B_TOWER_TRAINER_ROM_DATA	*trd;
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_btdtrname_dat, heapID);
	STRBUF			*name;

	trd=BattleTowerTrainerRomDataGet(tr_no,heapID);

	//�g���[�i�[ID���Z�b�g
	tr_data->bt_trd.player_id=tr_no;

	//�g���[�i�[�o�����b�Z�[�W
	tr_data->bt_trd.appear_word[0] = 0xFFFF;
	tr_data->bt_trd.appear_word[1] = tr_no*3;
	//�g���[�i�[�f�[�^���Z�b�g
	tr_data->bt_trd.tr_type=trd->tr_type;
	name=MSGMAN_AllocString(man,tr_no);
	STRBUF_GetStringCode(name,&tr_data->bt_trd.name[0],BUFLEN_PERSON_NAME);
	STRBUF_Delete(name);

	MSGMAN_Delete(man);

	return trd;
}

//�����|�P��������̓����_���ł��Ă��邪�������[�v�h�~�̂��߁A
//������x�܂킵����A�|�P�����̕s��v�݂̂��`�F�b�N���āA
//�A�C�e�����Œ�Ŏ������邽�߂̃A�C�e���e�[�u��
static const u16 BattleTowerPokemonItem[]={
	ITEM_HIKARINOKONA,
	ITEM_RAMUNOMI,
	ITEM_TABENOKOSI,
	ITEM_SENSEINOTUME,
};
//============================================================================================
/**
 *	@brief	�o�g���^���[�̃|�P�����p�����[�^����
 *
 *	@param[in/out]	pwd	�|�P�����p�����[�^�̓W�J�ꏊ
 *	@param[in]		poke_no	�^���[rom�f�[�^�|�P�����i���o�[
 *	@param[in]		poke_id	�|�P�����ɃZ�b�g����id
 *	@param[in]		poke_rnd	�|�P�����ɃZ�b�g���������(0�������n���ꂽ��֐����Ő���)
 *	@param[in]		pow_rnd	�|�P�����ɃZ�b�g����pow_rnd�l
 *	@param[in]		mem_idx	�����o�[index�B��̖�or��̖�
 *	@param[in]		itemfix	TRUE�Ȃ�Œ�A�C�e���BFALSE�Ȃ�rom�f�[�^�̃A�C�e��
 *	@param[in]		heapID	�e���|�������������m�ۂ���q�[�vID
 *
 *	@return	personal_rnd:�������ꂽ�|�P�����̌������l
 *
 */
//============================================================================================
static u32 BattleTowerPokemonParamMake(BTOWER_SCRWORK* wk,B_TOWER_POKEMON* pwd,
		u16 poke_no,u32 poke_id,u32 poke_rnd,u8 pow_rnd,u8 mem_idx,BOOL itemfix,int heapID)
{
	int i;
	int	exp;
	u32	personal_rnd;
	u8	friend;
	B_TOWER_POKEMON_ROM_DATA	prd_s;
	
	MI_CpuClear8(pwd,sizeof(B_TOWER_POKEMON));
	
	//�����f�[�^���[�h
	BattleTowerPokemonRomDataGet(&prd_s,poke_no);
	
	//�����X�^�[�i���o�[
	pwd->mons_no=prd_s.mons_no;
	
	//��������
	if(itemfix){
		//50��ȏ�܂킵�Ă����t���O��TURE�Ȃ�A�����A�C�e���͌Œ�̂��̂���������
		pwd->item_no=BattleTowerPokemonItem[mem_idx];
	}else{
		//rom�f�[�^�ɓo�^���ꂽ�A�C�e������������
		pwd->item_no=prd_s.item_no;
	}

	//�Ȃ��x��255���f�t�H���g
	friend=255;
	for(i=0;i<WAZA_TEMOTI_MAX;i++){
		pwd->waza[i]=prd_s.waza[i];
		//�������������Ă���Ƃ��́A�Ȃ��x��0�ɂ���
		if(prd_s.waza[i]==WAZANO_YATUATARI){
			friend=0;
		}
	}

	//IDNo
	pwd->id_no=poke_id;

	if(poke_rnd == 0){
		//������
		do{
//			personal_rnd=(gf_rand()|gf_rand()<<16);
			personal_rnd=(btower_rand(wk)|btower_rand(wk)<<16);
		}while((prd_s.chr!=PokeSeikakuGetRnd(personal_rnd))&&(PokeRareGetPara(poke_id,personal_rnd)==TRUE));
		pwd->personal_rnd=personal_rnd;
	}else{
		pwd->personal_rnd = poke_rnd;	//0�łȂ���Έ����̒l���g�p
	}
	
		
	//�p���[����
	pwd->hp_rnd=pow_rnd;
	pwd->pow_rnd=pow_rnd;
	pwd->def_rnd=pow_rnd;
	pwd->agi_rnd=pow_rnd;
	pwd->spepow_rnd=pow_rnd;
	pwd->spedef_rnd=pow_rnd;

	//�w�͒l
	exp=0;
	for(i=0;i<6;i++){
		if(prd_s.exp_bit&No2Bit(i)){
			exp++;
		}
	}
	if((PARA_EXP_TOTAL_MAX/exp)>255){
		exp=255;
	}else{
		exp=PARA_EXP_TOTAL_MAX/exp;
	}
	for(i = 0;i < 6;i++){
		if(prd_s.exp_bit&No2Bit(i)){
			pwd->exp[i]=exp;
		}
	}

	//�Z�|�C���g
	pwd->pp_count=0;

	//���R�[�h
	pwd->country_code=CasetteLanguage;

	//����
	i=PokePersonalParaGet(pwd->mons_no,ID_PER_speabi2);
	if(i){
		if(pwd->personal_rnd&1){
			pwd->tokusei=i;
		}else{
			pwd->tokusei=PokePersonalParaGet(pwd->mons_no,ID_PER_speabi1);
		}
	}else{
		pwd->tokusei=PokePersonalParaGet(pwd->mons_no,ID_PER_speabi1);
	}

	//�Ȃ��x
	pwd->natuki=friend;

	//�j�b�N�l�[��
	MSGDAT_MonsNameGet(pwd->mons_no,heapID,&(pwd->nickname[0]));

	return personal_rnd;
}

//============================================================================================
/**
 *	�o�g���^���[�g���[�i�[�f�[�^�����i�����f�[�^��B_TOWER_PARTNER_DATA�\���̂ɓW�J�j
 *
 * @param[in/out]	tr_data		��������B_TOWER_PARTNAER_DATA�\����
 * @param[in]		tr_no		�������ɂȂ�g���[�i�[ID
 * @param[in]		cnt			�g���[�i�[�Ɏ�������|�P�����̐�
 * @param[in]		set_poke_no	�y�A��g��ł���g���[�i�[�̎����|�P�����iNULL���ƃ`�F�b�N�Ȃ��j
 * @param[in]		set_item_no	�y�A��g��ł���g���[�i�[�̎����|�P�����̑����A�C�e���iNULL���ƃ`�F�b�N�Ȃ��j
 * @param[in/out]	poke		���I���ꂽ�|�P�����̓�̂̃p�����[�^���i�[���ĕԂ��\���̌^�f�[�^�ւ̃|�C���^(NULL���ƃ`�F�b�N�Ȃ��j
 * @param[in]		heapID		�q�[�vID
 *
 * @retval	FALSE	���I���[�v��50��ȓ��ŏI�����
 * @retval	TRUE	���I���[�v��50��ȓ��ŏI���Ȃ�����
 */
//============================================================================================
BOOL	RomBattleTowerTrainerDataMake(BTOWER_SCRWORK* wk,B_TOWER_PARTNER_DATA *tr_data,u16 tr_no,int cnt,
							  u16 *set_poke_no,u16 *set_item_no,B_TOWER_PAREPOKE_PARAM* poke,int heapID)
{
	BOOL			ret = 0;
	B_TOWER_TRAINER_ROM_DATA	*trd;
	
	//�g���[�i�[�f�[�^�Z�b�g
	trd = RomTrainerDataAlloc(tr_data,tr_no,heapID);

	//�|�P�����f�[�^���Z�b�g
	ret = BattleTowerPokemonSetAct(wk,trd,tr_no,&tr_data->btpwd[0],cnt,set_poke_no,set_item_no,poke,heapID);
	
	sys_FreeMemoryEz(trd);
	return ret;
}

//============================================================================================
/**
 *	�o�g���^���[ �y�A�g���[�i�[�f�[�^�Đ���
 *	�i�Z�[�u���ꂽAI�}���`�p�[�g�i�[�̃f�[�^��B_TOWER_PARTNER_DATA�\���̂ɓW�J�j
 *
 * @param[in/out]	tr_data		��������B_TOWER_PARTNAER_DATA�\����
 * @param[in]		tr_no		�������ɂȂ�g���[�i�[ID
 * @param[in]		fixitem		TURE�Ȃ�Œ�A�C�e�����AFALSE�Ȃ�rom�A�C�e�����Z�b�g����
 * @param[in]		poke		�|�P�����f�[�^�Đ����ɕK�v�ȍ\���̌^�f�[�^�ւ̃|�C���^
 * @param[in]		heapID		�q�[�vID
 */
//============================================================================================
void RomBattleTowerPartnerDataMake(BTOWER_SCRWORK* wk,B_TOWER_PARTNER_DATA *tr_data,u16 tr_no,BOOL itemfix,
		const B_TOWER_PAREPOKE_PARAM* poke,int heapID)
{
	int	i;
	u8	pow_rnd = 0;
	B_TOWER_TRAINER_ROM_DATA	*trd;

	//�g���[�i�[�f�[�^�Z�b�g
	trd = RomTrainerDataAlloc(tr_data,tr_no,heapID);
	
	//�|�P�����f�[�^���Z�b�g
	pow_rnd=BattleTowerPowRndGet(tr_no);
	for(i = 0;i < BTOWER_STOCK_PAREPOKE_MAX;i++){
		BattleTowerPokemonParamMake(wk,&(tr_data->btpwd[i]),
			poke->poke_no[i],poke->poke_id,poke->poke_rnd[i],pow_rnd,i,itemfix,heapID);
	}
	sys_FreeMemoryEz(trd);
}


//============================================================================================
/**
 *	�o�g���^���[�̃|�P���������߂�
 *
 * @param[in]		trd			�g���[�i�[�f�[�^
 * @param[in]		tr_no		�g���[�i�[�i���o�[
 * @param[in/out]	pwd			B_TOWER_POKEMON�\����
 * @param[in]		cnt			�g���[�i�[�Ɏ�������|�P�����̐�
 * @param[in]		set_poke_no	�y�A��g��ł���g���[�i�[�̎����|�P�����iNULL���ƃ`�F�b�N�Ȃ��j
 * @param[in]		set_item_no	�y�A��g��ł���g���[�i�[�̎����|�P�����̑����A�C�e���iNULL���ƃ`�F�b�N�Ȃ��j
 * @param[in/out]	poke		���I���ꂽ�|�P�����̓�̂̃p�����[�^���i�[���ĕԂ��\���̌^�f�[�^�ւ̃|�C���^(NULL���ƃ`�F�b�N�Ȃ��j
 * @param[in]		heapID		�q�[�vID
 *
 * @retval	FALSE	���I���[�v��50��ȓ��ŏI�����
 * @retval	TRUE	���I���[�v��50��ȓ��ŏI���Ȃ�����
 */
//============================================================================================
static BOOL BattleTowerPokemonSetAct(BTOWER_SCRWORK* wk,B_TOWER_TRAINER_ROM_DATA *trd,
		u16 tr_no,B_TOWER_POKEMON *pwd,u8 cnt,
		u16 *set_poke_no,u16 *set_item_no,B_TOWER_PAREPOKE_PARAM* poke,int heapID)
{
	int	i,j;
	u8	pow_rnd;
	u8	poke_index;
	u32	id;
	int	set_index;
	int	set_index_no[4];
	u32	set_rnd_no[4];
	int	set_count;
	int	loop_count;
	BOOL	ret = 0;
	B_TOWER_POKEMON_ROM_DATA	prd_s;
	B_TOWER_POKEMON_ROM_DATA	prd_d;

	//�莝���|�P������MAX��4�̂܂�
	GF_ASSERT(cnt<=4);

	set_count=0;
	loop_count=0;
	while(set_count!=cnt){
//		poke_index = gf_rand()%trd->use_poke_cnt;
		poke_index = btower_rand(wk)%trd->use_poke_cnt;
		set_index=trd->use_poke_table[poke_index];
		BattleTowerPokemonRomDataGet(&prd_d,set_index);

		//�����X�^�[�i���o�[�̃`�F�b�N�i����̃|�P�����͎����Ȃ��j
		for(i=0;i<set_count;i++){
			BattleTowerPokemonRomDataGet(&prd_s,set_index_no[i]);
			if(prd_s.mons_no==prd_d.mons_no){
				break;
			}
		}
		if(i!=set_count){
			continue;
		}

		//�y�A��g��ł���g���[�i�[�̎����|�P�����Ƃ̃`�F�b�N
		if(set_poke_no!=NULL){
			//�����X�^�[�i���o�[�̃`�F�b�N�i����̃|�P�����͎����Ȃ��j
			for(i=0;i<cnt;i++){
				if(set_poke_no[i]==prd_d.mons_no){
					break;
				}
			}
			if(i!=cnt){
				continue;
			}
		}

		//50��܂킵�āA���܂�Ȃ��悤�Ȃ�A����A�C�e���`�F�b�N�͂��Ȃ�
		if(loop_count<50){
			//�����A�C�e���̃`�F�b�N�i����̃A�C�e���͎����Ȃ��j
			for(i=0;i<set_count;i++){
				BattleTowerPokemonRomDataGet(&prd_s,set_index_no[i]);
				if((prd_s.item_no)&&(prd_s.item_no==prd_d.item_no)){
					break;
				}
			}
			if(i!=set_count){
				loop_count++;
				continue;
			}
			//�y�A��g��ł���g���[�i�[�̎����|�P�����̑����A�C�e���Ƃ̃`�F�b�N
			if(set_item_no!=NULL){
				//�����A�C�e���̃`�F�b�N�i����̃A�C�e���͎����Ȃ��j
				for(i=0;i<cnt;i++){
					if((set_item_no[i]==prd_d.item_no) && (set_item_no[i]!=0)){
						break;
					}
				}
				if(i!=cnt){
					loop_count++;
					continue;
				}
			}
		}

		set_index_no[set_count]=set_index;
		set_count++;
	}

	pow_rnd=BattleTowerPowRndGet(tr_no);
//	id=(gf_rand()|(gf_rand()<<16));
	id=(btower_rand(wk)|(btower_rand(wk)<<16));

	if(loop_count >= 50){
		ret = TRUE;
	}
	for(i=0;i<set_count;i++){
		set_rnd_no[i] = BattleTowerPokemonParamMake(wk,&(pwd[i]),
			set_index_no[i],id,0,pow_rnd,i,ret,heapID);
	}
	if(poke == NULL){
		return ret;
	}
	//�|�C���^��NULL�łȂ���΁A���I���ꂽ�|�P�����̕K�v�ȃp�����[�^��Ԃ�
	poke->poke_id = id;
	for(i = 0;i< BTOWER_STOCK_PAREPOKE_MAX;i++){
		poke->poke_no[i] = set_index_no[i];
		poke->poke_rnd[i] = set_rnd_no[i];
	}
	return ret;
}

//---------------------------------------------------------------------------------------------
/**
 *	�o�g���^���[�g���[�i�[�̎����|�P�����̃p���[���������肷��
 *
 * @param	tr_no	�g���[�i�[�i���o�[
 *
 * @return	�p���[����
 *
 */
//---------------------------------------------------------------------------------------------
static	u8	BattleTowerPowRndGet(u16 tr_no)
{
	u8	pow_rnd;

	if(tr_no<100){
		pow_rnd=(0x1f/8)*1;
	}
	else if(tr_no<120){
		pow_rnd=(0x1f/8)*2;
	}
	else if(tr_no<140){
		pow_rnd=(0x1f/8)*3;
	}
	else if(tr_no<160){
		pow_rnd=(0x1f/8)*4;
	}
	else if(tr_no<180){
		pow_rnd=(0x1f/8)*5;
	}
	else if(tr_no<200){
		pow_rnd=(0x1f/8)*6;
	}
	else if(tr_no<220){
		pow_rnd=(0x1f/8)*7;
	}
	else{
		pow_rnd=0x1f;
	}
	return pow_rnd;
}

//---------------------------------------------------------------------------------------------
/**
 *	�o�g���^���[�g���[�i�[�����f�[�^�̓ǂݏo��
 *
 * @param[in]	tr_no	�g���[�i�[�i���o�[
 * @param[in]	heapID	�������m�ۂ��邽�߂̃q�[�vID
 *
 */
//---------------------------------------------------------------------------------------------
static	void	*BattleTowerTrainerRomDataGet(u16 tr_no,int heapID)
{
	return	ArchiveDataLoadMalloc(ARC_BTD_TR,tr_no,heapID);
}

//---------------------------------------------------------------------------------------------
/**
 *	�o�g���^���[�|�P���������f�[�^�̓ǂݏo��
 *
 * @param[in]	prd		�ǂݏo�����|�P�����f�[�^�̊i�[��
 * @param[in]	index	�ǂݏo���|�P�����f�[�^�̃C���f�b�N�X
 *
 */
//---------------------------------------------------------------------------------------------
static	void	BattleTowerPokemonRomDataGet(B_TOWER_POKEMON_ROM_DATA *prd,int index)
{
	ArchiveDataLoad(prd,ARC_BTD_PM,index);
}

//============================================================================================
/**
 *	�o�g���^���[�g���[�i�[�f�[�^����
 *
 * @param[in/out]	bp			��������BATTLE_PARAM�\����
 * @param[in]		tr_data		�������ɂȂ�g���[�i�[�f�[�^
 * @param[in]		cnt			�g���[�i�[�̎����|�P������
 * @param[in]		client_no	��������client_no
 * @param[in]		heapID		�q�[�vID�iPOKEMON_PARAM�̐����ɕK�v�j
 */
//============================================================================================
static void	BattleTowerTrainerDataMake(BATTLE_PARAM *bp,B_TOWER_PARTNER_DATA *tr_data,int cnt,int client_no,int heapID)
{
	int				i,j;
	PMS_DATA		*pd;
	POKEMON_PARAM	*pp;

	//�g���[�i�[ID���Z�b�g
	bp->trainer_id[client_no]=tr_data->bt_trd.player_id;

	//�g���[�i�[�f�[�^���Z�b�g
	bp->trainer_data[client_no].tr_type=tr_data->bt_trd.tr_type;
	PM_strcpy(&bp->trainer_data[client_no].name[0],&tr_data->bt_trd.name[0]);
	pd=(PMS_DATA *)&tr_data->bt_trd.win_word[0];
	bp->trainer_data[client_no].win_word=*pd;
	pd=(PMS_DATA *)&tr_data->bt_trd.lose_word[0];
	bp->trainer_data[client_no].lose_word=*pd;

	//�|�P�����f�[�^���Z�b�g
	pp=PokemonParam_AllocWork(heapID);
	for(i=0;i<cnt;i++){
		BtlTower_PokeParaMake(&tr_data->btpwd[i],pp);
		PokeParty_Add(bp->poke_party[client_no],pp);
	}

	sys_FreeMemoryEz(pp);
}

