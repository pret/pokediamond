/**
 *	@file	fld_btower.c
 *	@brief	バトルタワースクリプト関連　FieldSubサブルーチン
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
//正式データが出来るまでインクルード
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
 *	プロトタイプ宣言
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

///タワーに出現するトレーナータイプ←→OBJコード
static const u16 btower_trtype2objcode[][2] = {
 {TRTYPE_BTFIVE1,SEVEN1},	///<五人衆1
 {TRTYPE_BTFIVE2,SEVEN2},	///<五人衆1
 {TRTYPE_BTFIVE3,SEVEN3},	///<五人衆1
 {TRTYPE_BTFIVE4,SEVEN4},	///<五人衆1
 {TRTYPE_BTFIVE5,SEVEN5},	///<五人衆1
 {TRTYPE_TANPAN,	BOY2},	///<たんパンこぞう
 {TRTYPE_MINI,	GIRL1},	///<ミニスカート
 {TRTYPE_SCHOOLB,	BOY1},	///<じゅくがえり
 {TRTYPE_SCHOOLG,	GIRL3},	///<じゅくがえり
 {TRTYPE_PRINCE,	GORGGEOUSM},	///<おぼっちゃま
 {TRTYPE_PRINCESS,	GORGGEOUSW},	///<おじょうさま
 {TRTYPE_CAMPB,	CAMPBOY},	///<キャンプボーイ
 {TRTYPE_PICNICG,	PICNICGIRL},	///<ピクニックガール
 {TRTYPE_UKIWAB,	BABYBOY1},	///<うきわボーイ
 {TRTYPE_UKIWAG,	BABYGIRL1},	///<うきわガール
 {TRTYPE_DAISUKIM,	MIDDLEMAN1},	///<だいすきクラブ
 {TRTYPE_DAISUKIW,	MIDDLEWOMAN1},	///<だいすきクラブ
 {TRTYPE_WAITER,	WAITER},	///<ウエーター
 {TRTYPE_WAITRESS,	WAITRESS},	///<ウエートレス
 {TRTYPE_BREEDERM,	MAN1},	///<ポケモンブリーダー
 {TRTYPE_BREEDERW,	WOMAN1},	///<ポケモンブリーダー
 {TRTYPE_CAMERAMAN,	CAMERAMAN},	///<カメラマン
 {TRTYPE_REPORTER,	REPORTER},	///<レポーター
 {TRTYPE_FARMER,	FARMER},	///<ぼくじょうおじさん
 {TRTYPE_COWGIRL,	COWGIRL},	///<カウガール
 {TRTYPE_CYCLINGM,	CYCLEM},	///<サイクリング♂
 {TRTYPE_CYCLINGW,	CYCLEW},	///<サイクリング♀
 {TRTYPE_KARATE,	FIGHTER},	///<からておう
 {TRTYPE_BATTLEG,	GIRL2},	///<バトルガール
 {TRTYPE_VETERAN,	OLDMAN1},	///<ベテラントレーナー
 {TRTYPE_MADAM,	LADY},	///<マダム
 {TRTYPE_ESPM,	MYSTERY},	///<サイキッカー
 {TRTYPE_ESPW,	MYSTERY},	///<サイキッカー
 {TRTYPE_RANGERM,	MAN3},	///<ポケモンレンジャー
 {TRTYPE_RANGERW,	WOMAN3},	///<ポケモンレンジャー
 {TRTYPE_ELITEM,	MAN3},	///<エリートトレーナー
 {TRTYPE_ELITEW,	WOMAN3},	///<エリートトレーナー
 {TRTYPE_COLDELITEM,	MAN5},	///<エリートトレーナー♂（厚着）
 {TRTYPE_COLDELITEW,	WOMAN5},	///<エリートトレーナー♀（厚着）
 {TRTYPE_DRAGON,	MAN3},	///<ドラゴンつかい
 {TRTYPE_MUSHI,	BOY3},	///<むしとりしょうねん
 {TRTYPE_SHINOBI,	BABYBOY1},	///<にんじゃごっこ
 {TRTYPE_JOGGER,	SPORTSMAN},	///<ジョギング♂
 {TRTYPE_FISHING,	FISHING},	///<つりびと
 {TRTYPE_SAILOR,	SEAMAN},	///<ふなのり
 {TRTYPE_MOUNT,	MOUNT},	///<やまおとこ
 {TRTYPE_ISEKI,	EXPLORE},	///<いせきマニア
 {TRTYPE_GUITARIST,	MAN2},	///<ギタリスト
 {TRTYPE_COLLECTOR,	BIGMAN},	///<ポケモンコレクター
 {TRTYPE_HEADS,	BADMAN},	///<スキンヘッズ
 {TRTYPE_SCIENTIST,	ASSISTANTM},	///<けんきゅういん♂
 {TRTYPE_GENTLE,	GENTLEMAN},	///<ジェントルマン
 {TRTYPE_WORKER,	WORKMAN},	///<さぎょういん
 {TRTYPE_PIERROT,	CLOWN},	///<ピエロ
 {TRTYPE_POLICE,	POLICEMAN},	///<おまわりさん
 {TRTYPE_GAMBLER,	GORGGEOUSM},	///<ギャンブラー
 {TRTYPE_BIRD,	WOMAN3},	///<とりつかい
 {TRTYPE_PARASOL,	AMBRELLA},	///<パラソルおねえさん
 {TRTYPE_SISTER,	WOMAN2},	///<おとなのおねえさん
 {TRTYPE_AROMA,	WOMAN1},	///<アロマなおねえさん
 {TRTYPE_IDOL,	IDOL},	///<アイドル
 {TRTYPE_ARTIST,	ARTIST},	///<げいじゅつか
 {TRTYPE_POKEGIRL,	PIKACHU},	///<ポケモンごっこ♀
};
#define TRTYPE2OBJCODE_MAX	(NELEMS(btower_trtype2objcode))

/**
 *	@brief	タワープレイ更新ランダムシード取得 ラウンド更新時に呼ぶ
 */
static u16	btower_rand(BTOWER_SCRWORK* wk)
{
	wk->play_rnd_seed = BtlTower_PlayFixRand(wk->play_rnd_seed);

	OS_Printf("btower_rand = %d\n",wk->play_rnd_seed);
	return (wk->play_rnd_seed/65535);
}

/**
 *	@brief	参加できないポケモン名をタグ展開
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
			//単語セット
			//バッファID
			//文字列
			//性別コード
			//単／複（TRUEで単数）
			//言語コード
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
 *	@brief	トレーナータイプから人物OBJコードを返す
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
 *	@brief	シングルダブル トレーナー抽選結果取得
 *	
 * @param[in/out]	tr_data		生成するB_TOWER_PARTNAER_DATA構造体
 * @param[in]		tr_no		生成元になるトレーナーID
 * @param[in]		cnt			トレーナーに持たせるポケモンの数
 * @param[in]		heapID		ヒープID
 */
static void btltower_BtlPartnerSelectSD(B_TOWER_PARTNER_DATA* wk,const u8 round)
{
	int i;

	const B_TOWER_TRAINER *tr_src;
	const B_TOWER_POKEMON *poke_src;
	const B_TOWER_DMYENEMY	*poke_idx;

	MI_CpuClear8(wk,sizeof(B_TOWER_PARTNER_DATA));

	//本当はROM/RAMデータから引っ張ってくる
	tr_src = &(b_tower_trainer_data[round]);
	poke_src = b_tower_poke_data;
	poke_idx = &(b_tower_dmy_enemy[round]);

	//トレーナーデータコピー
	MI_CpuCopy8(tr_src,&wk->bt_trd,sizeof(B_TOWER_TRAINER));
	wk->bt_trd.dummy = poke_idx->obj_code;

	//ポケモンデータコピー
	for(i = 0;i < 4;i++){
		MI_CpuCopy8(&(poke_src[poke_idx->pokeno[i]]),&(wk->btpwd[i]),sizeof(B_TOWER_POKEMON));
	}
}
#endif
/**
 *	@brief	Wifi トレーナー抽選
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
		//データがない(ROMから無理矢理抽選)
		btltower_BtlPartnerSelectSD(wk,round);
		return;
	}

	//セーブデータから引っ張る
	TowerWifiData_GetBtlPlayerData(wifiSave,wk,round);
}

//-----------------------------------------------------------------------------
/**
 *	@brief	バトルタワー用ポケモンデータからPOKEMON_PARAMを生成
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
	
	//装備アイテム設定
	PokeParaPut(dest,ID_PARA_item,&src->item_no);
	
	//技設定
	for(i = 0;i < 4;i++){
		buf16 = src->waza[i];
		PokeParaPut(dest,ID_PARA_waza1+i,&buf16);
		buf8 = (src->pp_count >> (i*2))&0x03;
		PokeParaPut(dest,ID_PARA_pp_count1+i,&buf8);

		//pp再設定
		waza_pp = (u8)PokeParaGet(dest,ID_PARA_pp_max1+i,NULL);
		PokeParaPut(dest,ID_PARA_pp1+i,&waza_pp);
	}
	
	//ID設定
	buf32 = src->id_no;	
	PokeParaPut(dest,ID_PARA_id_no,&buf32);

	//経験値設定
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

	//特性設定
	PokeParaPut(dest,ID_PARA_speabino,&src->tokusei);
	
	//なつきど設定
	PokeParaPut(dest,ID_PARA_friend,&src->natuki);
	
	//NGネームフラグをチェック
	if(src->ngname_f){
		//デフォルトネームを展開する
		MSGDATA_MANAGER* man;
		STRBUF* def_name;
	
		man = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_monsname_dat, HEAPID_FIELD );
		def_name = MSGMAN_AllocString(man,src->mons_no);
		
		PokeParaPut(dest,ID_PARA_nickname_buf,def_name);

		STRBUF_Delete(def_name);
		MSGMAN_Delete(man);
	}else{
		//ニックネーム
		PokeParaPut(dest,ID_PARA_nickname,src->nickname);
	}
	
	//カントリーコード
	PokeParaPut(dest,ID_PARA_country_code,&src->country_code);
	//パラメータ再計算
	PokeParaCalc(dest);
}

/**
 * @brief	バトルタワー　プレイモードからFIGHT_TYPEを返す
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
 *	@brief	バトルタワー　トレーナーデータ生成
 */
static void btower_TrainerDataMake(u8 play_mode,B_TOWER_TRAINER* src,TRAINER_DATA* dest)
{
	MI_CpuClear8(dest,sizeof(TRAINER_DATA));

	dest->tr_type = src->tr_type;	//トレーナータイプ
	dest->tr_gra = 0;//src->tr_type;	//トレーナータイプ
	dest->aibit = 0xFFFFFFFF;	//最強

	//トレーナー名
	PM_strcpy(dest->name,src->name);
	
	//勝ち負けメッセージ
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
 *	@brief	トレーナー対戦データ生成
 */
static void btltower_SetTrainerData(BTOWER_SCRWORK* wk,BATTLE_PARAM* bp,
		B_TOWER_PARTNER_DATA* tr,u8 tr_id,u8 tr_client,u8 poke_client)
{
	int i;
	POKEMON_PARAM *pp;
	
	//トレーナーデータをセット
	btower_TrainerDataMake(wk->play_mode,&(tr->bt_trd),&(bp->trainer_data[tr_client]));
	
	//トレーナーID入力
	bp->trainer_id[tr_client] = tr_id;//wk->tr_data[0].bt_trd.tr_type;
	
	//対戦相手のポケモンデータをセット
	pp = PokemonParam_AllocWork(wk->heapID);

	PokeParty_Init(bp->poke_party[poke_client],wk->member_num);
	for(i = 0;i < wk->member_num;i++){
		BtlTower_PokeParaMake(&(tr->btpwd[i]),pp);
		BattleParam_AddPokemon(bp,pp,poke_client);
	}
	sys_FreeMemoryEz(pp);
}

/**
 *	@brief	バトルタワー用　バトルパラメータ生成
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
	
	//ずかんデータは大きすぎるのでコピーしない
	bp->box = SaveData_GetBoxData(sv);
	bp->time_zone = EVTIME_GetTimeZone(fsys);
	bp->bag_cursor = fsys->bag_cursor;

	bp->record=SaveData_GetRecord(sv);
	bp->fnote_data = fsys->fnote;
	bp->friendlist = SaveData_GetFriendList( fsys->savedata );
	bp->zone_id = fsys->location->zone_id;
#else
	BattleParam_SetParamByGameDataCore(bp,fsys);
	bp->bg_id = BG_ID_ROOM_A;			//基本背景指定
	bp->ground_id = GROUND_ID_FLOOR;	//基本地面指定
#endif
	//ポケモンデータセット
	pp = PokemonParam_AllocWork(wk->heapID);
	
	//選んだ手持ちポケモンをセット
	val8 = 50;
	PokeParty_Init(bp->poke_party[POKEPARTY_MINE],wk->member_num);
	for(i = 0;i < wk->member_num;i++){
		PokeCopyPPtoPP(PokeParty_GetMemberPointer(party,wk->member[i]),pp);

		//レベル調整
		if(PokeParaGet(pp,ID_PARA_level,NULL) > val8){
			val32 = PokeLevelExpGet(PokeParaGet(pp,ID_PARA_monsno,NULL),val8);

			PokeParaPut(pp,ID_PARA_exp,&val32);
			PokeParaCalc(pp);
		}
		BattleParam_AddPokemon(bp,pp,POKEPARTY_MINE);
	}
	sys_FreeMemoryEz(pp);

	//トレーナーデータ生成（自分側）
	BattleParam_TrainerDataMake(bp);

	//トレーナーデータ(enemy1)をセット
	BattleTowerTrainerDataMake(bp,&(wk->tr_data[0]),wk->member_num,CLIENT_NO_ENEMY,wk->heapID);
	
	switch(wk->play_mode){
	case BTWR_MODE_MULTI:
		//ペアデータをセット
		BattleTowerTrainerDataMake(bp,&(wk->five_data[wk->partner]),wk->member_num,CLIENT_NO_MINE2,wk->heapID);
		//↓ここは共通処理で流れていい
	case BTWR_MODE_COMM_MULTI:
		//トレーナーデータ(enemy2)をセット
		BattleTowerTrainerDataMake(bp,&(wk->tr_data[1]),wk->member_num,CLIENT_NO_ENEMY2,wk->heapID);
		break;
	default:
		break;
	}
	return bp;
}

//============================================================================
/**
 *	通信関連コマンド
 */
//============================================================================

/**
 *	@brief	バトルタワー　送られてきたプレイヤーデータを受け取る
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
 *	@brief	バトルタワー　送られてきたトレーナーデータを受け取る
 */
u16	BTowerComm_RecvTrainerData(FIELDSYS_WORK* fsys,const u16* recv_buf)
{
	int i;
	BTOWER_SCRWORK* wk = fsys->btower_wk;

	if(CommGetCurrentID() == COMM_PARENT_ID){
		return 0;	//親は送信するだけなので受け取らない
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
 *	@brief	バトルタワー　送られてきたリタイアするかどうかの結果を受け取る
 *
 *	@retval	0	リタイアしない
 *	@retval	1	リタイアする
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
 *	@brief	バトルタワー　自機性別とモンスターNoを送信
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
 *	@brief	バトルタワー　通信マルチ　抽選したトレーナーNoを子機に送信
 */
void BTowerComm_SendTrainerData(BTOWER_SCRWORK* wk)
{
	MI_CpuCopy8(wk->trainer,wk->send_buf,BTOWER_STOCK_TRAINER_MAX*2);
}

/**
 *	@brief	バトルタワー　通信マルチ　リタイアするかどうかを互いに送信
 *
 *	@param	retire	TRUEならリタイア
 */
void BTowerComm_SendRetireSelect(BTOWER_SCRWORK* wk,u16 retire)
{
	//自分の選択結果をワークに保存
	wk->retire_f = retire;
	wk->send_buf[0] = retire;
}

//============================================================================================
/**
 *	バトルタワートレーナーNo取得（ロムデータのためのトレーナーID取得）
 *
 * @param[in]	stage		周回数
 * @param[in]	round		何人目
 * @param[in]	play_mode	対戦モード
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
 *	@brief	トレーナーナンバー抽選
 */
u16	BattleTowerTrainerNoGet(BTOWER_SCRWORK* wk,u8 stage,u8 round,int play_mode)
{
	u16	no;

	//タワータイクーンはシングルのみ
	if(play_mode==BTWR_MODE_SINGLE){
		//タワータイクーン1回目
		if((stage==2)&&(round==6)){
			return TOWER_MASTER_FIRST;
		}
		//タワータイクーン2回目
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
 *	バトルタワー　romトレーナーデータ展開
 *
 *	B_TOWER_TRAINER_ROM_DATA型をメモリ確保して返すので、
 *	呼び出し側が明示的に解放すること
 */
//============================================================================================
static B_TOWER_TRAINER_ROM_DATA* RomTrainerDataAlloc(B_TOWER_PARTNER_DATA *tr_data,u16 tr_no,int heapID)
{
	B_TOWER_TRAINER_ROM_DATA	*trd;
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_btdtrname_dat, heapID);
	STRBUF			*name;

	trd=BattleTowerTrainerRomDataGet(tr_no,heapID);

	//トレーナーIDをセット
	tr_data->bt_trd.player_id=tr_no;

	//トレーナー出現メッセージ
	tr_data->bt_trd.appear_word[0] = 0xFFFF;
	tr_data->bt_trd.appear_word[1] = tr_no*3;
	//トレーナーデータをセット
	tr_data->bt_trd.tr_type=trd->tr_type;
	name=MSGMAN_AllocString(man,tr_no);
	STRBUF_GetStringCode(name,&tr_data->bt_trd.name[0],BUFLEN_PERSON_NAME);
	STRBUF_Delete(name);

	MSGMAN_Delete(man);

	return trd;
}

//持ちポケモン決定はランダムでしているが無限ループ防止のため、
//ある程度まわしたら、ポケモンの不一致のみをチェックして、
//アイテムを固定で持たせるためのアイテムテーブル
static const u16 BattleTowerPokemonItem[]={
	ITEM_HIKARINOKONA,
	ITEM_RAMUNOMI,
	ITEM_TABENOKOSI,
	ITEM_SENSEINOTUME,
};
//============================================================================================
/**
 *	@brief	バトルタワーのポケモンパラメータ生成
 *
 *	@param[in/out]	pwd	ポケモンパラメータの展開場所
 *	@param[in]		poke_no	タワーromデータポケモンナンバー
 *	@param[in]		poke_id	ポケモンにセットするid
 *	@param[in]		poke_rnd	ポケモンにセットする個性乱数(0が引き渡されたら関数内で生成)
 *	@param[in]		pow_rnd	ポケモンにセットするpow_rnd値
 *	@param[in]		mem_idx	メンバーindex。一体目or二体目
 *	@param[in]		itemfix	TRUEなら固定アイテム。FALSEならromデータのアイテム
 *	@param[in]		heapID	テンポラリメモリを確保するヒープID
 *
 *	@return	personal_rnd:生成されたポケモンの個性乱数値
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
	
	//ロムデータロード
	BattleTowerPokemonRomDataGet(&prd_s,poke_no);
	
	//モンスターナンバー
	pwd->mons_no=prd_s.mons_no;
	
	//装備道具
	if(itemfix){
		//50回以上まわしていたフラグがTUREなら、装備アイテムは固定のものを持たせる
		pwd->item_no=BattleTowerPokemonItem[mem_idx];
	}else{
		//romデータに登録されたアイテムを持たせる
		pwd->item_no=prd_s.item_no;
	}

	//なつき度は255がデフォルト
	friend=255;
	for(i=0;i<WAZA_TEMOTI_MAX;i++){
		pwd->waza[i]=prd_s.waza[i];
		//やつあたりを持っているときは、なつき度を0にする
		if(prd_s.waza[i]==WAZANO_YATUATARI){
			friend=0;
		}
	}

	//IDNo
	pwd->id_no=poke_id;

	if(poke_rnd == 0){
		//個性乱数
		do{
//			personal_rnd=(gf_rand()|gf_rand()<<16);
			personal_rnd=(btower_rand(wk)|btower_rand(wk)<<16);
		}while((prd_s.chr!=PokeSeikakuGetRnd(personal_rnd))&&(PokeRareGetPara(poke_id,personal_rnd)==TRUE));
		pwd->personal_rnd=personal_rnd;
	}else{
		pwd->personal_rnd = poke_rnd;	//0でなければ引数の値を使用
	}
	
		
	//パワー乱数
	pwd->hp_rnd=pow_rnd;
	pwd->pow_rnd=pow_rnd;
	pwd->def_rnd=pow_rnd;
	pwd->agi_rnd=pow_rnd;
	pwd->spepow_rnd=pow_rnd;
	pwd->spedef_rnd=pow_rnd;

	//努力値
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

	//技ポイント
	pwd->pp_count=0;

	//国コード
	pwd->country_code=CasetteLanguage;

	//特性
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

	//なつき度
	pwd->natuki=friend;

	//ニックネーム
	MSGDAT_MonsNameGet(pwd->mons_no,heapID,&(pwd->nickname[0]));

	return personal_rnd;
}

//============================================================================================
/**
 *	バトルタワートレーナーデータ生成（ロムデータをB_TOWER_PARTNER_DATA構造体に展開）
 *
 * @param[in/out]	tr_data		生成するB_TOWER_PARTNAER_DATA構造体
 * @param[in]		tr_no		生成元になるトレーナーID
 * @param[in]		cnt			トレーナーに持たせるポケモンの数
 * @param[in]		set_poke_no	ペアを組んでいるトレーナーの持ちポケモン（NULLだとチェックなし）
 * @param[in]		set_item_no	ペアを組んでいるトレーナーの持ちポケモンの装備アイテム（NULLだとチェックなし）
 * @param[in/out]	poke		抽選されたポケモンの二体のパラメータを格納して返す構造体型データへのポインタ(NULLだとチェックなし）
 * @param[in]		heapID		ヒープID
 *
 * @retval	FALSE	抽選ループが50回以内で終わった
 * @retval	TRUE	抽選ループが50回以内で終わらなかった
 */
//============================================================================================
BOOL	RomBattleTowerTrainerDataMake(BTOWER_SCRWORK* wk,B_TOWER_PARTNER_DATA *tr_data,u16 tr_no,int cnt,
							  u16 *set_poke_no,u16 *set_item_no,B_TOWER_PAREPOKE_PARAM* poke,int heapID)
{
	BOOL			ret = 0;
	B_TOWER_TRAINER_ROM_DATA	*trd;
	
	//トレーナーデータセット
	trd = RomTrainerDataAlloc(tr_data,tr_no,heapID);

	//ポケモンデータをセット
	ret = BattleTowerPokemonSetAct(wk,trd,tr_no,&tr_data->btpwd[0],cnt,set_poke_no,set_item_no,poke,heapID);
	
	sys_FreeMemoryEz(trd);
	return ret;
}

//============================================================================================
/**
 *	バトルタワー ペアトレーナーデータ再生成
 *	（セーブされたAIマルチパートナーのデータをB_TOWER_PARTNER_DATA構造体に展開）
 *
 * @param[in/out]	tr_data		生成するB_TOWER_PARTNAER_DATA構造体
 * @param[in]		tr_no		生成元になるトレーナーID
 * @param[in]		fixitem		TUREなら固定アイテムを、FALSEならromアイテムをセットする
 * @param[in]		poke		ポケモンデータ再生成に必要な構造体型データへのポインタ
 * @param[in]		heapID		ヒープID
 */
//============================================================================================
void RomBattleTowerPartnerDataMake(BTOWER_SCRWORK* wk,B_TOWER_PARTNER_DATA *tr_data,u16 tr_no,BOOL itemfix,
		const B_TOWER_PAREPOKE_PARAM* poke,int heapID)
{
	int	i;
	u8	pow_rnd = 0;
	B_TOWER_TRAINER_ROM_DATA	*trd;

	//トレーナーデータセット
	trd = RomTrainerDataAlloc(tr_data,tr_no,heapID);
	
	//ポケモンデータをセット
	pow_rnd=BattleTowerPowRndGet(tr_no);
	for(i = 0;i < BTOWER_STOCK_PAREPOKE_MAX;i++){
		BattleTowerPokemonParamMake(wk,&(tr_data->btpwd[i]),
			poke->poke_no[i],poke->poke_id,poke->poke_rnd[i],pow_rnd,i,itemfix,heapID);
	}
	sys_FreeMemoryEz(trd);
}


//============================================================================================
/**
 *	バトルタワーのポケモンを決める
 *
 * @param[in]		trd			トレーナーデータ
 * @param[in]		tr_no		トレーナーナンバー
 * @param[in/out]	pwd			B_TOWER_POKEMON構造体
 * @param[in]		cnt			トレーナーに持たせるポケモンの数
 * @param[in]		set_poke_no	ペアを組んでいるトレーナーの持ちポケモン（NULLだとチェックなし）
 * @param[in]		set_item_no	ペアを組んでいるトレーナーの持ちポケモンの装備アイテム（NULLだとチェックなし）
 * @param[in/out]	poke		抽選されたポケモンの二体のパラメータを格納して返す構造体型データへのポインタ(NULLだとチェックなし）
 * @param[in]		heapID		ヒープID
 *
 * @retval	FALSE	抽選ループが50回以内で終わった
 * @retval	TRUE	抽選ループが50回以内で終わらなかった
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

	//手持ちポケモンのMAXは4体まで
	GF_ASSERT(cnt<=4);

	set_count=0;
	loop_count=0;
	while(set_count!=cnt){
//		poke_index = gf_rand()%trd->use_poke_cnt;
		poke_index = btower_rand(wk)%trd->use_poke_cnt;
		set_index=trd->use_poke_table[poke_index];
		BattleTowerPokemonRomDataGet(&prd_d,set_index);

		//モンスターナンバーのチェック（同一のポケモンは持たない）
		for(i=0;i<set_count;i++){
			BattleTowerPokemonRomDataGet(&prd_s,set_index_no[i]);
			if(prd_s.mons_no==prd_d.mons_no){
				break;
			}
		}
		if(i!=set_count){
			continue;
		}

		//ペアを組んでいるトレーナーの持ちポケモンとのチェック
		if(set_poke_no!=NULL){
			//モンスターナンバーのチェック（同一のポケモンは持たない）
			for(i=0;i<cnt;i++){
				if(set_poke_no[i]==prd_d.mons_no){
					break;
				}
			}
			if(i!=cnt){
				continue;
			}
		}

		//50回まわして、決まらないようなら、同一アイテムチェックはしない
		if(loop_count<50){
			//装備アイテムのチェック（同一のアイテムは持たない）
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
			//ペアを組んでいるトレーナーの持ちポケモンの装備アイテムとのチェック
			if(set_item_no!=NULL){
				//装備アイテムのチェック（同一のアイテムは持たない）
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
	//ポインタがNULLでなければ、抽選されたポケモンの必要なパラメータを返す
	poke->poke_id = id;
	for(i = 0;i< BTOWER_STOCK_PAREPOKE_MAX;i++){
		poke->poke_no[i] = set_index_no[i];
		poke->poke_rnd[i] = set_rnd_no[i];
	}
	return ret;
}

//---------------------------------------------------------------------------------------------
/**
 *	バトルタワートレーナーの持ちポケモンのパワー乱数を決定する
 *
 * @param	tr_no	トレーナーナンバー
 *
 * @return	パワー乱数
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
 *	バトルタワートレーナーロムデータの読み出し
 *
 * @param[in]	tr_no	トレーナーナンバー
 * @param[in]	heapID	メモリ確保するためのヒープID
 *
 */
//---------------------------------------------------------------------------------------------
static	void	*BattleTowerTrainerRomDataGet(u16 tr_no,int heapID)
{
	return	ArchiveDataLoadMalloc(ARC_BTD_TR,tr_no,heapID);
}

//---------------------------------------------------------------------------------------------
/**
 *	バトルタワーポケモンロムデータの読み出し
 *
 * @param[in]	prd		読み出したポケモンデータの格納先
 * @param[in]	index	読み出すポケモンデータのインデックス
 *
 */
//---------------------------------------------------------------------------------------------
static	void	BattleTowerPokemonRomDataGet(B_TOWER_POKEMON_ROM_DATA *prd,int index)
{
	ArchiveDataLoad(prd,ARC_BTD_PM,index);
}

//============================================================================================
/**
 *	バトルタワートレーナーデータ生成
 *
 * @param[in/out]	bp			生成するBATTLE_PARAM構造体
 * @param[in]		tr_data		生成元になるトレーナーデータ
 * @param[in]		cnt			トレーナーの持ちポケモン数
 * @param[in]		client_no	生成するclient_no
 * @param[in]		heapID		ヒープID（POKEMON_PARAMの生成に必要）
 */
//============================================================================================
static void	BattleTowerTrainerDataMake(BATTLE_PARAM *bp,B_TOWER_PARTNER_DATA *tr_data,int cnt,int client_no,int heapID)
{
	int				i,j;
	PMS_DATA		*pd;
	POKEMON_PARAM	*pp;

	//トレーナーIDをセット
	bp->trainer_id[client_no]=tr_data->bt_trd.player_id;

	//トレーナーデータをセット
	bp->trainer_data[client_no].tr_type=tr_data->bt_trd.tr_type;
	PM_strcpy(&bp->trainer_data[client_no].name[0],&tr_data->bt_trd.name[0]);
	pd=(PMS_DATA *)&tr_data->bt_trd.win_word[0];
	bp->trainer_data[client_no].win_word=*pd;
	pd=(PMS_DATA *)&tr_data->bt_trd.lose_word[0];
	bp->trainer_data[client_no].lose_word=*pd;

	//ポケモンデータをセット
	pp=PokemonParam_AllocWork(heapID);
	for(i=0;i<cnt;i++){
		BtlTower_PokeParaMake(&tr_data->btpwd[i],pp);
		PokeParty_Add(bp->poke_party[client_no],pp);
	}

	sys_FreeMemoryEz(pp);
}

