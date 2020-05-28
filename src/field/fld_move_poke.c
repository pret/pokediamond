//============================================================================================
/**
 * @file	fld_move_poke.c
 * @bfief	フィールド移動ポケモン関連処理
 * @author	Nozomu Saito
 * @date	06.05.13
 */
//============================================================================================
#include "savedata/encount.h"
#include "common.h"
#include "fieldsys.h"
#include "move_pokemon_def.h"
#include "move_pokemon.h"

#include "debug_saito.h"

#include "fld_move_poke.h"

static void MovePokeLocation(ENC_SV_PTR inEncData);
static void JumpMovePokeAffterBattle(ENC_SV_PTR inEncData, const int inZoneID);
static MPD_PTR GetMovePokeDataByMondNo(ENC_SV_PTR inEncData, const int inMonsNo);

//-----------------------------------------------------------------------------
/**
 * 戦闘後の処理
 *
 * @param	
 *
 * @return	none
 */
//-----------------------------------------------------------------------------
void FLD_MP_SetAfferBattle(FIELDSYS_WORK * fsys, BATTLE_PARAM *inBattleParam)
{
	u16 hp;
	u8 cond;
	int monsno;
	
	ENC_SV_PTR data;
	MPD_PTR mpd;
	POKEPARTY *poke_party;
	POKEMON_PARAM *poke_param;
	
	//移動ポケモンと戦闘したかをチェック
	poke_party = inBattleParam->poke_party[POKEPARTY_ENEMY];
	poke_param = PokeParty_GetMemberPointer(poke_party, 0);

	data = EncDataSave_GetSaveDataPtr(fsys->savedata);
	monsno = PokeParaGet(poke_param, ID_PARA_monsno, NULL);
	mpd = GetMovePokeDataByMondNo(data, monsno);
	
	if(mpd != NULL){			//移動ポケモンとエンカウント
		hp = (u16)(PokeParaGet(poke_param,ID_PARA_hp, NULL));
		cond = (u8)(PokeParaGet(poke_param,ID_PARA_condition, NULL));
		//勝ってＨＰが0もしくは捕獲したか？
		if ( ((inBattleParam->win_lose_flag==FIGHT_WIN)&&(hp == 0)) ||
			 (inBattleParam->win_lose_flag==FIGHT_POKE_GET) ) {
			//エンカウントした移動ポケモンデータをクリア
			EncDataSave_ClearMovePokeData(&mpd);
		}else{
			//パラメータの反映
			EncDataSave_SetMovePokeDataParam(mpd, MP_PARAM_HP, hp);
			EncDataSave_SetMovePokeDataParam(mpd, MP_PARAM_COND, cond);
		}
		//3匹の移動ポケモンのジャンプ
		JumpMovePokeAffterBattle(data, fsys->location->zone_id);

	}else{			//通常ポケモンとエンカウント
		//30％の確率で、3匹の移動ポケモンのジャンプ
		if ( gf_p_rand(100)<30 ){
			JumpMovePokeAffterBattle(data, fsys->location->zone_id);
		}
	}
}

//-----------------------------------------------------------------------------
/**
 * 戦闘後の移動ポケモンジャンプ
 *
 * @param	
 *
 * @return	none
 */
//-----------------------------------------------------------------------------
static void JumpMovePokeAffterBattle(ENC_SV_PTR inEncData, const int inZoneID)
{
	int zone;
	u8 i;
	for(i=0;i<MOVE_POKE_MAX;i++){
		//移動中で、且つ、主人公と同じゾーンにいるか？
		if ( EncDataSave_IsMovePokeValid(inEncData, i) ){
			zone = MP_GetMovePokeZone(EncDataSave_GetMovePokeZoneIdx(inEncData, i));
			if (inZoneID == zone){
				//ジャンプ
				MP_JumpMovePokemon(inEncData, i);
			}
		}
	}
}

//-----------------------------------------------------------------------------
/**
 * モンスターナンバーから移動ポケモンデータを取得
 *
 * @param	inMonsNo	モンスターナンバー
 *
 * @return	MPD_PTR		移動ポケモンデータポインタ ない場合はNULLを返す
 *
*/ 
//-----------------------------------------------------------------------------
static MPD_PTR GetMovePokeDataByMondNo(ENC_SV_PTR inEncData, const int inMonsNo)
{
	u8 i;
	MPD_PTR mpd;
	for(i=0;i<MOVE_POKE_MAX;i++){
		if ( EncDataSave_IsMovePokeValid(inEncData, i) ){
			mpd = EncDataSave_GetMovePokeDataPtr(inEncData, i);
			if (inMonsNo == EncDataSave_GetMovePokeDataParam(mpd, MP_PARAM_MONSNO)){
				return mpd;
			}
		}
	}
	return NULL;
}
