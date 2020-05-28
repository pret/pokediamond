//============================================================================================
/**
 * @file	plist_item.h
 * @brief	ポケモンリスト画面アイテム使用処理
 * @author	Hiroyuki Nakamura
 * @date	05.12.12
 */
//============================================================================================
#ifndef PLIST_ITEM_H
#define PLIST_ITEM_H
#undef GLOBAL
#ifdef PLIST_ITEM_H_GLOBAL
#define GLOBAL	/*	*/
#else
#define GLOBAL	extern
#endif





GLOBAL void PokeList_ItemUseMain( PLIST_WORK * wk );
GLOBAL int PokeList_ItemUseMsgWait( void * work );

GLOBAL BOOL PL_ALLDeathRcvItemCheck( u16 item );
GLOBAL int PokeList_AllDeathRcvMain( PLIST_WORK * wk );

GLOBAL int PokeList_LvUpWazaSetRetInit( PLIST_WORK * wk );

GLOBAL u8 PokeList_WazaOboeCheck( PLIST_WORK * wk, POKEMON_PARAM * pp );

GLOBAL int PokeList_WazaOboeInit( PLIST_WORK * wk );
GLOBAL int PokeList_WazaSetRetInit( PLIST_WORK * wk );
GLOBAL int PokeList_WazaSetRetSet( PLIST_WORK * wk );

GLOBAL void PokeList_WazaMenuInit( PLIST_WORK * wk, u8 type );
GLOBAL int PokeList_WazaMenuMain( PLIST_WORK * wk );


GLOBAL void PokeList_MailBoxAdd( PLIST_WORK * wk );



#undef GLOBAL
#endif
