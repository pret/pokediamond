//============================================================================================
/**
 * @file	plist_menu.h
 * @brief	ポケモンリスト画面メニュー関連
 * @author	Hiroyuki Nakamura
 * @date	05.10.18
 */
//============================================================================================
#ifndef PLIST_MENU_H
#define PLIST_MENU_H
#undef GLOBAL
#ifdef PLIST_MENU_H_GLOBAL
#define GLOBAL	/*	*/
#else
#define GLOBAL	extern
#endif


typedef void (*pPLMenuFunc)( PLIST_WORK * wk, int * seq );



GLOBAL u32 PokeListMenuParamGet( u8 id );

//--------------------------------------------------------------------------------------------
/**
 * メニュー破棄
 *
 * @param	wk		バッグ画面のワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
GLOBAL void PokeListMenuExit( PLIST_WORK * wk );

GLOBAL void PokeListRowCancel( PLIST_WORK * wk );
GLOBAL void PokeListMenuRowMoveInit( PLIST_WORK * wk );
GLOBAL BOOL PokeListMenu_NarabikaeMain( PLIST_WORK * wk );

GLOBAL int PokeList_ItemMenuItemGetEndWait( PLIST_WORK * wk );

GLOBAL int PokeList_BattleInWaitError( PLIST_WORK * wk );

GLOBAL int PokeList_MenuWazaError( PLIST_WORK * wk );

GLOBAL int PokeList_ItemGetEnd( PLIST_WORK * wk );


GLOBAL int PLIST_MenuKapselSet( PLIST_WORK * wk );

GLOBAL int PL_KapselGetYes( void * work );
GLOBAL int PL_KapselGetNo( void * work );


#undef GLOBAL
#endif	// PLIST_MENU_H
