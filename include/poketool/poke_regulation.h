//============================================================================================
/**
 * @file	poke_regulation.h
 * @brief	レギュレーション検査用プログラム
 * @author	k.ohno
 * @date	2006.5.25
 */
//============================================================================================
#ifndef __POKE_REGULATION_H__
#define __POKE_REGULATION_H__

#include "poketool/poke_tool.h"
#include "savedata/regulation.h"
#include "application/zukanlist/zkn_height_gram.h"

// PokeRegulationMatchPartialPokePartyとPokeRegulationMatchFullPokeParty の戻り値
enum{
    POKE_REG_OK,               // 正常
    POKE_REG_TOTAL_LV_FAILED,  // トータルのLVがオーバーしている
    POKE_REG_BOTH_POKE,        // 同じポケモンがいる
    POKE_REG_BOTH_ITEM,        // 同じアイテムがある
//--------------------------------------------------------
    POKE_REG_NUM_FAILED,       // 必要なポケモンの人数が満たされていない
    POKE_REG_ILLEGAL_POKE,     // 条件に合わないポケモンがいた
};

extern ZKN_HEIGHT_GRAM_PTR PokeRegulationInit(int heap_id );
// ポケモンがレギュレーションに適合しているかどうか調べたら、図鑑を破棄
extern void PokeRegulationEnd(ZKN_HEIGHT_GRAM_PTR pZKN);
// ポケモンがレギュレーションに適合しているかどうか調べる  
extern BOOL PokeRegulationCheckPokePara(const REGULATION* pReg, POKEMON_PARAM* pp, ZKN_HEIGHT_GRAM_PTR pZKN);
// ポケパーティがレギュレーションに完全適合しているかどうか調べる バトル最終チェック用
extern int PokeRegulationMatchFullPokeParty(const REGULATION* pReg, POKEPARTY * party,
                                            const ZKN_HEIGHT_GRAM_PTR pZKN, u8* sel);
// ポケパーティ中にレギュレーションに適合している
//  パーティーが組めるかどうか調べる 適応外のポケモンがいても大丈夫  受け付け用
extern int PokeRegulationMatchPartialPokeParty(const REGULATION* pReg, POKEPARTY * party,ZKN_HEIGHT_GRAM_PTR pZKN);

#endif// __POKE_REGULATION_H__
