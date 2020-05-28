//============================================================================================
/**
 * @file	boxmenu.h
 * @brief	ボックスメニューデータ処理
 * @author	taya
 * @date	2005.09.27
 */
//============================================================================================
#ifndef __BOXMENU_H__
#define __BOXMENU_H__

#include "box_common.h"

//-----------------------------------------------------------------
/**
 *  BoxMenu_Ctrl の戻り値。Ａで選択されれば、その項目のＩＤが返る
 */
//-----------------------------------------------------------------
enum {
	BOXMENU_CTRL_CANCEL = -1,	///< Ｂボタンでキャンセルされた
	BOXMENU_CTRL_MOVE = -2,		///< カーソルが動いた
	BOXMENU_CTRL_LOOP = -3,		///< 何も無い
};

//-----------------------------------------------------------------
/**
 *  メニュータイプ
 */
//-----------------------------------------------------------------
enum {
	BOXMENU_TYPE_YESNO,
	BOXMENU_TYPE_POKE,
	BOXMENU_TYPE_TRAY,
	BOXMENU_TYPE_WALLPAPER,
	BOXMENU_TYPE_MARKING,
};

extern void BoxMenu_SetYesNoMenu( BOXAPP_VPARAM* vpara, u32 pos );
extern void BoxMenu_SetPokeMenu( BOXAPP_VPARAM* vpara );
extern void BoxMenu_SetItemMenu( BOXAPP_VPARAM* vpara );
extern void BoxMenu_SetTrayMenu( BOXAPP_VPARAM* vpara );
extern void BoxMenu_SetWallPaperCategoryMenu( BOXAPP_VPARAM* vpara, BOX_MENU_ID defaultCategory );
extern void BoxMenu_SetWallPaperTypeMenu( BOXAPP_VPARAM* vpara, BOX_MENU_ID  category );
extern void BoxMenu_SetMarkingMenu( BOXAPP_VPARAM* vpara );
extern void BoxMenu_ReverseMarkingState( BOXAPP_VPARAM* vpara, u32 pos );

//------------------------------------------------------------------
/**
 * キーチェック＆メニュー状態コントロール
 *
 * @param   vpara		
 *
 * @retval  int		
s */
//------------------------------------------------------------------
extern int BoxMenu_Ctrl( BOXAPP_VPARAM* vpara );

//------------------------------------------------------------------
/**
 * 選択中メニューＩＤを返す
 *
 * @param   vpara		
 *
 * @retval  BOX_MENU_ID		
 */
//------------------------------------------------------------------
extern BOX_MENU_ID BoxMenu_GetSelectMenuID( BOXAPP_VPARAM* vpara );

//------------------------------------------------------------------
/**
 * 先頭のメニューＩＤを返す
 *
 * @param   vpara		
 *
 * @retval  BOX_MENU_ID		
 */
//------------------------------------------------------------------
extern BOX_MENU_ID BoxMenu_GetFirstMenuID( BOXAPP_VPARAM* vpara );

#endif
