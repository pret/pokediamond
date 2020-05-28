//============================================================================================
/**
 * @file	wordset.h
 * @brief	単語セットオブジェクト
 * @author	taya
 * @date	2005.09.28
 *
 */
//============================================================================================
#ifndef __WORDSET_H__
#define __WORDSET_H__

#include  "system\pm_str.h"
#include  "system\msgdata.h"
#include  "poketool\poke_tool.h"	// POKEMON_PASO_PARAM 参照等
#include  "field\field_common.h"	// FIELDSYS_WORK 参照
#include  "system\mystatus.h"		// MYSTATUS 参照
#include  "gflib\number_str.h"
#include  "system\savedata_def.h"
#include  "poketool\boxdata.h"
#include  "system\pms_word.h"
#include  "battle\battle_common.h"

enum {
	WORDSET_DEFAULT_SETNUM = 8,		// デフォルトバッファ数
	WORDSET_DEFAULT_BUFLEN = 32,	// デフォルトバッファ長（文字数）
};



typedef struct _WORDSET		WORDSET;


//------------------------------------------------------------------
/**
 * 
 *
 * @param   heapID		
 *
 * @retval  extern WORDSET*		
 */
//------------------------------------------------------------------
extern WORDSET*  WORDSET_Create( u32 heapID );


//------------------------------------------------------------------
/**
 * 
 *
 * @param   word_max		
 * @param   buflen		
 * @param   heapID		
 *
 * @retval  extern WORDSET*		
 */
//------------------------------------------------------------------
extern WORDSET* WORDSET_CreateEx( u32 word_max, u32 buflen, u32 heapID );


//------------------------------------------------------------------
/**
 * 
 *
 * @param   wordset		
 *
 * @retval  extern void		
 */
//------------------------------------------------------------------
extern void WORDSET_Delete( WORDSET* wordset );

//------------------------------------------------------------------
/**
 * 
 *
 * @param   wordset		
 * @param   dstbuf		
 * @param   srcbuf		
 *
 * @retval  extern void		
 */
//------------------------------------------------------------------
extern void WORDSET_ExpandStr( const WORDSET* wordset, STRBUF* dstbuf, const STRBUF* srcbuf );


//------------------------------------------------------------------
/**
 * 内部バッファを全て空文字列でクリアする
 *
 * @param   wordset		WORDSETポインタ
 */
//------------------------------------------------------------------
extern void WORDSET_ClearAllBuffer( WORDSET* wordset );


extern void WORDSET_RegisterPlayerName( WORDSET* wordset, u32 bufID, const MYSTATUS* status );
extern void WORDSET_RegisterRivalName( WORDSET* wordset,  u32 bufID, const SAVEDATA * savedata );
extern void WORDSET_RegisterSupportName( WORDSET* wordset, u32 bufID, const SAVEDATA * savedata );
extern void WORDSET_RegisterMonumentName( WORDSET* wordset, u32 bufID, const SAVEDATA * savedata );
extern void WORDSET_RegisterPokeMonsName( WORDSET* wordset, u32 bufID, POKEMON_PASO_PARAM* ppp );
extern void WORDSET_RegisterPokeNickName( WORDSET* wordset, u32 bufID, POKEMON_PASO_PARAM* ppp );
extern void WORDSET_RegisterPokeOyaName( WORDSET* wordset,  u32 bufID, POKEMON_PASO_PARAM* ppp );
extern void WORDSET_RegisterNumber( WORDSET* wordset, u32 bufID, s32 number, u32 keta, NUMBER_DISPTYPE dispType, NUMBER_CODETYPE codeType );
extern void WORDSET_RegisterWazaName( WORDSET* wordset, u32 bufID, u32 wazaID );
extern void WORDSET_RegisterRibbonName( WORDSET* wordset, u32 bufID, u32 ribbonID );
extern void WORDSET_RegisterTokuseiName( WORDSET* wordset, u32 bufID, u32 tokuseiID );
extern void WORDSET_RegisterSeikaku( WORDSET * wordset, u32 bufID, u32 seikakuID );
extern void WORDSET_RegisterItemName( WORDSET* wordset, u32 bufID, u32 itemID );
extern void WORDSET_RegisterItemPocketName( WORDSET* wordset, u32 bufID, u32 pocketID );
extern void WORDSET_RegisterItemPocketWithIcon( WORDSET* wordset, u32 bufID, u32 pocketID );
extern void WORDSET_RegisterPokeTypeName( WORDSET* wordset, u32 bufID, u32 typeID );
extern void WORDSET_RegisterPokeStatusName( WORDSET* wordset, u32 bufID, u32 statusID );
extern void WORDSET_RegisterBadConditionName( WORDSET* wordset, u32 bufID, u32 conditionID );
extern void WORDSET_RegisterSeedTasteName( WORDSET* wordset, u32 bufID, u32 tasteID );
extern void WORDSET_RegisterPlaceName( WORDSET* wordset, u32 bufID, u32 strID );
extern void WORDSET_RegisterPoketchAppName( WORDSET* wordset, u32 bufID, u32 strID );
extern void WORDSET_RegisterTrTypeName( WORDSET* wordset, u32 bufID, u32 strID );
extern void WORDSET_RegisterTrTypeNameBattle( WORDSET* wordset, u32 bufID, TRAINER_DATA *tr_data );
extern void WORDSET_RegisterTrainerName( WORDSET* wordset, u32 bufID, u32 strID );
extern void WORDSET_RegisterTrainerNameBattle( WORDSET* wordset, u32 bufID, TRAINER_DATA *tr_data );
extern void WORDSET_RegisterWord( WORDSET* wordset, u32 bufID, const STRBUF* word, u32 sex, BOOL single_flag, u32 lang );
extern void WORDSET_RegisterUGItemName( WORDSET* wordset, u32 bufID, u32 strID );
extern void WORDSET_RegisterUGTrapName( WORDSET* wordset, u32 bufID, u32 strID );
extern void WORDSET_RegisterJudgeName( WORDSET* wordset, u32 bufID, u32 strID );
extern void WORDSET_RegisterContestRank( WORDSET* wordset, u32 bufID, u32 strID );
extern void WORDSET_RegisterContestType( WORDSET* wordset, u32 bufID, u32 strID );
extern void WORDSET_RegisterSecretQuestion( WORDSET* wordset, u32 bufID, u32 strID );
extern void WORDSET_RegisterSecretAnswer( WORDSET* wordset, u32 bufID, u32 strID );
extern void WORDSET_RegisterUGGoodsName( WORDSET* wordset, u32 bufID, u32 strID );
extern void WORDSET_RegisterPokeMonsSex( WORDSET* wordset, u32 bufID, u8 sex);
extern void WORDSET_RegisterBoxTrayName( WORDSET* wordset, u32 bufID, const BOX_DATA* boxData, u32 trayNumber );
extern void WORDSET_RegisterGymName( WORDSET* wordset, u32 bufID, u32 strID );
extern void WORDSET_RegisterTimeType( WORDSET* wordset, u32 bufID, u32 strID );
extern void WORDSET_RegisterCountryName( WORDSET* wordset, u32 bufID, u32 strID );
extern void WORDSET_RegisterLocalPlaceName( WORDSET* wordset, u32 bufID, u32 countryID, u32 placeID );
extern void WORDSET_RegisterPMSWord( WORDSET* wordset, u32 bufID, PMS_WORD word );
extern void WORDSET_RegisterSealName( WORDSET* wordset, u32 bufID, u32 strID );
extern void WORDSET_RegisterPokeGetPlace( WORDSET* wordset, u32 bufID, u32 placeNumber );
extern void WORDSET_RegisterPorutoName( WORDSET* wordset, u32 bufID, u32 porutoID );
extern void WORDSET_RegisterAccessoryName( WORDSET* wordset, u32 bufID, u32 acID );
extern void WORDSET_RegisterImageClibBgName( WORDSET* wordset, u32 bufID, u32 bgID );
extern void WORDSET_RegisterGroupName(WORDSET * ws, SAVEDATA * sv, int gid, int bufID, int name_type);

#endif
