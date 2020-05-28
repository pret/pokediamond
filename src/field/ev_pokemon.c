//===========================================================================
/**
 * @file	ev_pokemon.c
 * @brief	イベントソース：ポケモン関連
 * @author	tamada GAME FREAK Inc.
 * @date	2005.12.18
 */
//===========================================================================
#include "common.h"

#include "fieldsys.h"
#include "poketool/pokeparty.h"
#include "poketool/poke_tool.h"
#include "poketool/poke_memo.h"
#include "savedata/zukanwork.h"
#include "savedata/get_poke.h"

#include "ev_pokemon.h"
#include "battle/battle_common.h"		//CONDITION_～
#include "sodateya.h"

#include "itemtool/itemsym.h"
//===========================================================================
//===========================================================================
#if 0
typedef void(* ITL_FUNC)(POKEMON_PARAM * poke, void *);
//------------------------------------------------------------------
/**
 * @brief	手持ち全部への操作を一括で行う
 * @param	party		手持ちポケモンへのポインタ
 * @param	func		操作関数へのポインタ
 * @param	work		ワークへのポインタ
 *
 * タマゴでもなく、気絶してもいないポケモンに対し操作関数を呼び出す。
 * 速度度外視。たぶんメモリ効率がよくなるはず。
 */
//------------------------------------------------------------------
void EvPoke_Itelator(POKEPARTY * party, ITL_FUNC func, void * work)
{
	int i, max;
	POKEMON_PARAM * pp;
	max = PokeParty_GetPokeCount(party);
	for (i = 0; i < max; i++) {
		pp = PokeParty_GetMemberPointer(party, i);
		if (PokeParaGet(poke, ID_PARA_tamago_flag, NULL) != 0) {
			continue;
		}
		if (PokeParaGet(poke, ID_PARA_hp, NULL) == 0) {
			continue;
		}
		func(pp, work);
	}
}
#endif
//------------------------------------------------------------------
/**
 * @brief	ポケモンが戦闘可能かどうかのチェック
 * @param	pp		対象ポケモンへのポインタ
 * @return	BOOL	TRUEのとき、戦闘可能
 *
 * 瀕死でもタマゴでもなければTRUEを返す
 */
//------------------------------------------------------------------
BOOL EvPoke_EnableBattle(POKEMON_PARAM * pp)
{
	if (PokeParaGet(pp, ID_PARA_hp, NULL) == 0) {
		return FALSE;
	}
	if (PokeParaGet(pp, ID_PARA_tamago_flag, NULL)) {
		return FALSE;
	}
	return TRUE;
}

//------------------------------------------------------------------
/**
 * @brief
 * @param	heapID
 * @param	sv
 * @param	monsno
 * @param	level
 * @param	itemno
 * @param	place_id
 * @param	ground_id
 * @retval	TRUE
 * @retval	FALSE
 */
//------------------------------------------------------------------
BOOL EvPoke_Add(int heapID, SAVEDATA * sv, u16 monsno, u8 level,
		u16 itemno, int place_id, int ground_id)
{
	BOOL result;
	POKEMON_PARAM *poke_param;
	u32 buf;
	POKEPARTY * party;
	MYSTATUS * my;

	my = SaveData_GetMyStatus(sv);
	party = SaveData_GetTemotiPokemon(sv);
	poke_param = PokemonParam_AllocWork(heapID);
	PokeParaInit(poke_param);
	PokeParaSet(poke_param, monsno, level, POW_RND, RND_NO_SET, 0, ID_NO_SET, 0);
	PokeParaGetInfoSet(poke_param, my, ITEM_MONSUTAABOORU, place_id, ground_id, heapID);
	buf = itemno;
	PokeParaPut(poke_param, ID_PARA_item, &buf);
	result = PokeParty_Add(party, poke_param);
	if (result) {
		SaveData_GetPokeRegister( sv, poke_param );
	}
	sys_FreeMemoryEz(poke_param);

	return result;
}

//------------------------------------------------------------------
/**
 * @brief	手持ちにタマゴを加える
 * @param	heapID
 * @param	sv
 * @param	monsno
 * @param	eventflg
 * @param	type      生まれた場所タイプ  placename.h参照
 * @param	index     生まれた場所index
 * @retval	TRUE
 * @retval	FALSE
 * 
 */
//------------------------------------------------------------------
BOOL EvPoke_AddTamago(int heapID, SAVEDATA * sv, u16 monsno, u8 eventflg, PLACENAME_TYPE type, int index)
{
    int number;
    BOOL result;
	MYSTATUS *my = SaveData_GetMyStatus( sv );
	POKEPARTY * temoti = SaveData_GetTemotiPokemon(sv);
	POKEMON_PARAM* poke_param = PokemonParam_AllocWork(HEAPID_EVENT);
	PokeParaInit(poke_param);
    number = PlaceName_IndexToParamNumber( type, index);
	PokemonTamagoSet_forEvent(poke_param, monsno, eventflg, my, TRMEMO_FUSHIGI_PLACESET, number);
	result = PokeParty_Add(temoti, poke_param);
	sys_FreeMemoryEz(poke_param);
	return result;
}

//------------------------------------------------------------------
/**
 * @brief	ポケモンにわざをセットする
 * @param	party		POKEPARTY構造体へのポインタ
 * @param	poke_pos	ポケモンの位置（０～６）
 * @param	waza_pos	わざをセットする場所（０～３）
 * @param	waza_no		わざの種類
 */
//------------------------------------------------------------------
void EvPoke_ChangeWaza(POKEPARTY * party, int poke_pos, int waza_pos, u16 waza_no)
{
	PokeWazaSetPos(PokeParty_GetMemberPointer(party, poke_pos), waza_no, waza_pos);
}

//------------------------------------------------------------------
/**
 * @brief	手持ちポケモンのわざチェック
 * @param	party		POKEPARTY構造体へのポインタ
 * @param	waza_no		わざの種類
 * @retval	0-5			持っているポケモンの位置
 * @retval	0xff		持っているポケモンがいない
 *
 * 手持ちポケモンに指定したわざを持っているものがいるかどうかを返す。
 */
//------------------------------------------------------------------
int EvPoke_CheckWaza(POKEPARTY * party, u16 waza_no)
{
	int i, max;
	POKEMON_PARAM * poke;

	max = PokeParty_GetPokeCount(party);

	for (i = 0; i<max; i++){
		poke = PokeParty_GetMemberPointer(party, i);

		//たまごチェック
		if( PokeParaGet( poke, ID_PARA_tamago_flag, NULL ) != 0 ){
			continue;
		}
		//ワザリストからチェック
		if( (PokeParaGet( poke, ID_PARA_waza1, NULL ) == waza_no)
				||(PokeParaGet( poke, ID_PARA_waza2, NULL ) == waza_no)
				||(PokeParaGet( poke, ID_PARA_waza3, NULL ) == waza_no)
				||(PokeParaGet( poke, ID_PARA_waza4, NULL ) == waza_no)
			){
			return i;		//持っているポケモンのリスト上の並びを返す
			break;
		}
	}
	return 0xff;
}

//------------------------------------------------------------------
/**
 * @brief	戦えるポケモンの数を数える
 * @param	party	POKEPARTYへのポインタ
 * @return	int		戦えるポケモンの数
 */
//------------------------------------------------------------------
int EvPoke_CountLivingPokemon(const POKEPARTY * party)
{
	int i, max, count;
	POKEMON_PARAM * pp;
	
	max = PokeParty_GetPokeCount(party);
	count = 0;
	for (i = 0; i < max; i++) {
		pp = PokeParty_GetMemberPointer(party, i);
		if (EvPoke_EnableBattle(pp)) {
			count ++;
		}
#if 0
		if (PokeParaGet(pp, ID_PARA_hp, NULL) == 0) {
			continue;
		}
		if (PokeParaGet(pp, ID_PARA_tamago_flag, NULL)) {
			continue;
		}
		count ++;
#endif
	}
	return count;
}

//------------------------------------------------------------------
/**
 * @brief	ポケパーティの中の戦えるポケモンを返す(先頭から調べて、始めに引っかかったやつを返す)
 * @param	party	POKEPARTYへのポインタ
 * @return	pp		ポケモンパラムポインタ
 */
//------------------------------------------------------------------
POKEMON_PARAM *EvPoke_GetLivingPokemonTop(const POKEPARTY * party)
{
	int i, max;
	POKEMON_PARAM * pp;
	
	max = PokeParty_GetPokeCount(party);
	for (i = 0; i < max; i++) {
		pp = PokeParty_GetMemberPointer(party, i);
		if (EvPoke_EnableBattle(pp)) {
			return pp;
		}
	}
	GF_ASSERT(0);
	return NULL;
}

//--------------------------------------------------------------
/**
 * @brief	先頭のポケモンへのポインタ取得
 * @param	party	POKEPARTYへのポインタ
 * @return	タマゴをのぞいた先頭のポケモンへのポインタ
 */
//--------------------------------------------------------------
POKEMON_PARAM * EvPoke_GetPokemonTop(const POKEPARTY * party)
{
	u16 i,max;
	POKEMON_PARAM * pp;

	max = PokeParty_GetPokeCount(party);
	for (i = 0; i < max; i++) {
		pp = PokeParty_GetMemberPointer(party, i);
		if (PokeParaGet(pp, ID_PARA_tamago_flag, NULL) == 0) {
			return pp;
		}
	}
	return NULL;
}


//------------------------------------------------------------------
/**
 * @brief	2vs2対戦が可能かどうかチェック
 * @param	party	POKEPARTYへのポインタ
 * @return	BOOL	TRUEのとき、2vs2対戦できる
 */
//------------------------------------------------------------------
BOOL EvPoke_Enable2vs2Battle(const POKEPARTY * party)
{
	if (EvPoke_CountLivingPokemon(party) >= 2) {
		return TRUE;
	} else {
		return FALSE;
	}
}

//===========================================================================
//===========================================================================
//------------------------------------------------------------------
/**
 * @brief	手持ちポケモン全部にシンオウチャンピオンリボンをセット
 * @param	party	POKEPARTYへのポインタ
 *
 * 殿堂入りの際に呼び出される
 */
//------------------------------------------------------------------
void EvPoke_SetChampionRibbon(POKEPARTY * party)
{
	int i,max;
	u8 flag = 1;
	POKEMON_PARAM * pp;
	max = PokeParty_GetPokeCount(party);
	for (i = 0; i < max; i++) {
		pp = PokeParty_GetMemberPointer(party, i);
		if (PokeParaGet(pp, ID_PARA_tamago_flag, NULL) == 0) {
			PokeParaPut(pp, ID_PARA_sinou_champ_ribbon, &flag);
		}
	}
}

//===========================================================================
//===========================================================================

//------------------------------------------------------------------
/**
 * @brief	毒ダメージチェック
 * @param	party		手持ちポケモンへのポインタ
 * @param	placeID		地域ID
 * @retval	FLD_POISON_DEAD			ポケモンが気絶した
 * @retval	FLD_POISON_DAMAGE		ポケモンがダメージを受けた
 * @retval	FLD_POISON_NODAMAGE		ポケモンはダメージを受けなかった
 */
//------------------------------------------------------------------
FLD_POISON_STAT EvPoke_PoisonDamage(POKEPARTY * party, u16 placeID)
{
	int poison_count = 0;
	int dead_count = 0;
	int i, max;
	POKEMON_PARAM * pp;
	max = PokeParty_GetPokeCount(party);
	for (i = 0; i < max; i++) {
		pp = PokeParty_GetMemberPointer(party, i);
		if (EvPoke_EnableBattle(pp)) {
			if (PokeParaGet(pp, ID_PARA_condition, NULL) & (CONDITION_DOKUDOKU|CONDITION_DOKU)) {
				u32 hp = PokeParaGet(pp, ID_PARA_hp, NULL);
				if (hp > 1) {
					hp --;
				}
				PokeParaPut(pp, ID_PARA_hp, &hp);
				if (hp == 1) {
					dead_count ++;
					FriendCalc( pp, FRIEND_DOKU_HINSHI, placeID);	// なつきど計算
				}
				poison_count ++;
			}
		}
	}

	if (dead_count) {
		return FLD_POISON_DEAD;
	} else if (poison_count) {
		return FLD_POISON_DAMAGE;
	} else {
		return FLD_POISON_NODAMAGE;
	}
}

//------------------------------------------------------------------
/**
 * @brief	毒による気絶認定
 * @param	pp			ポケモンへのポインタ
 * @retval	TRUE		毒で気絶した
 * @retval	FALSE		気絶していない
 *
 * 毒状態でかつHPが０のポケモンをどく気絶とみなす。
 * その際にコンディションをクリアする。
 */
//------------------------------------------------------------------
BOOL EvPoke_ApprovePoisonDead(POKEMON_PARAM * pp)
{
	if ((PokeParaGet(pp, ID_PARA_condition, NULL) & (CONDITION_DOKUDOKU|CONDITION_DOKU))
			&& PokeParaGet(pp, ID_PARA_hp, NULL) == 1){
		u32 cond = 0;
		PokeParaPut(pp, ID_PARA_condition, &cond);
		return TRUE;
	}
	return FALSE;
}





