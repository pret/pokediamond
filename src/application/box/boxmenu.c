//============================================================================================
/**
 * @file	boxmenu.c
 * @brief	ボックスメニューデータ処理
 * @author	taya
 * @date	2005.09.27
 */
//============================================================================================
#include  "common.h"
#include  "application\box.h"
#include  "boxmenu.h"
#include  "box_common.h"


//==============================================================
// Prototype
//==============================================================
static void InitWork( BOXAPP_MENU* menu );
static void AddMenu( BOXAPP_MENU* menu, BOX_MENU_ID id );



//==============================================================================================================
// メニュー状態セット関数
//==============================================================================================================

//------------------------------------------------------------------
/**
 * 「はい」「いいえ」メニュー状態セット
 *
 * @param   vpara		描画パラメータポインタ
 * @param   pos			初期カーソル位置
 *
 */
//------------------------------------------------------------------
void BoxMenu_SetYesNoMenu( BOXAPP_VPARAM* vpara, u32 pos )
{
	BOXAPP_MENU* menu = &(vpara->menu);

	InitWork( menu );
	AddMenu( menu, BOXMENU_YES );
	AddMenu( menu, BOXMENU_NO );
	menu->pos = pos;
	menu->type = BOXMENU_TYPE_YESNO;
}

//------------------------------------------------------------------
/**
 * ポケモンメニュー状態セット
 *
 * @param   vpara		描画パラメータポインタ
 *
 */
//------------------------------------------------------------------
void BoxMenu_SetPokeMenu( BOXAPP_VPARAM* vpara )
{
	BOXAPP_MENU* menu = &(vpara->menu);

	InitWork( menu );

	menu->type = BOXMENU_TYPE_POKE;

	switch( BoxAppVPara_GetBoxMode(vpara) ){
	case BOX_MODE_SEIRI:
	default:
		if( BoxAppVPara_GetCursorCatchPokeFlag(vpara) == CURSOR_CATCH_SINGLE ){
			AddMenu(menu, BoxAppVPara_GetCursorPointPokeFlag(vpara)? BOXMENU_POKE_IREKAERU : BOXMENU_POKE_OKU);
		}else{
			AddMenu(menu, BOXMENU_POKE_TUKAMU);
		}

		AddMenu( menu, BOXMENU_POKE_YOUSU );

		{
			const BOXAPP_STATUS_POKE*  stpoke = BoxAppVpara_GetStatusPokeData(vpara);
			if( stpoke->tamago_flag == FALSE )
			{
				AddMenu( menu, BOXMENU_POKE_MOTIMONO );
			}
		}

		AddMenu( menu, (BoxAppVPara_GetCursorArea( vpara ) == CURSOR_AREA_TRAY)?
				BOXMENU_POKE_TURETEIKU : BOXMENU_POKE_AZUKERU );

		AddMenu( menu, BOXMENU_POKE_MARKING );
		AddMenu( menu, BOXMENU_POKE_NIGASU );
		AddMenu( menu, BOXMENU_POKEMENU_QUIT );
		break;

	case BOX_MODE_AZUKERU:
		AddMenu( menu, BOXMENU_POKE_AZUKERU );
		AddMenu( menu, BOXMENU_POKE_YOUSU );
		AddMenu( menu, BOXMENU_POKE_MARKING );
		AddMenu( menu, BOXMENU_POKE_NIGASU );
		AddMenu( menu, BOXMENU_POKEMENU_QUIT );
		break;

	case BOX_MODE_TURETEIKU:
		AddMenu( menu, BOXMENU_POKE_TURETEIKU );
		AddMenu( menu, BOXMENU_POKE_YOUSU );
		AddMenu( menu, BOXMENU_POKE_MARKING );
		AddMenu( menu, BOXMENU_POKE_NIGASU );
		AddMenu( menu, BOXMENU_POKEMENU_QUIT );
		break;

	case BOX_MODE_COMPARE:
		AddMenu( menu, (BoxAppVPara_GetCompareUpdateSide(vpara) == BOXAPP_COMPARE_SIDE_LEFT)? 
				BOXMENU_COMPARE_HOLD_LEFT : BOXMENU_COMPARE_HOLD_RIGHT );

		AddMenu( menu, (BoxAppVPara_GetCursorArea( vpara ) == CURSOR_AREA_TRAY)?
				BOXMENU_POKE_TURETEIKU : BOXMENU_POKE_AZUKERU );

		AddMenu( menu, BOXMENU_POKE_MARKING );
		AddMenu( menu, BOXMENU_POKEMENU_QUIT );
	}
	//BoxAppVPara_GetBoxMode
}
//------------------------------------------------------------------
/**
 * アイテムせいりメニュー状態セット
 *
 * @param   vpara		描画パラメータポインタ
 *
 */
//------------------------------------------------------------------
void BoxMenu_SetItemMenu( BOXAPP_VPARAM* vpara )
{
	BOXAPP_MENU* menu;
	u32 catch_item, point_item;

	menu = &(vpara->menu);
	catch_item = BoxAppVPara_GetCatchItemNumber(vpara);
	point_item = BoxAppVPara_GetStatusPokeItemNumber(vpara);

	InitWork( menu );
	menu->type = BOXMENU_TYPE_POKE;

	if( catch_item != ITEM_DUMMY_ID )
	{
		if( point_item != ITEM_DUMMY_ID )
		{
			AddMenu( menu, BOXMENU_ITEM_SWAP );
		}
		else
		{
			AddMenu( menu, BOXMENU_ITEM_SET );
		}
		AddMenu( menu, BOXMENU_ITEM_TO_BAG );
		AddMenu( menu, BOXMENU_ITEM_INFO );
	}
	else
	{
		if( point_item != ITEM_DUMMY_ID )
		{
			AddMenu( menu, BOXMENU_ITEM_WITHDRAW );
			AddMenu( menu, BOXMENU_ITEM_TO_BAG );
			AddMenu( menu, BOXMENU_ITEM_INFO );
		}
		else
		{
			AddMenu( menu, BOXMENU_ITEM_SET );
		}
	}
	AddMenu( menu, BOXMENU_ITEM_QUIT );

}
//------------------------------------------------------------------
/**
 * トレーメニュー状態セット
 *
 * @param   vpara		描画パラメータポインタ
 *
 */
//------------------------------------------------------------------
void BoxMenu_SetTrayMenu( BOXAPP_VPARAM* vpara )
{
	BOXAPP_MENU* menu = &(vpara->menu);
	const BOX_DATA* boxData = BoxAppVPara_GetBoxData(vpara);

	InitWork( menu );

	AddMenu( menu, BOXMENU_TRAY_JUMP );

	if( BoxAppVPara_GetBoxMode(vpara) != BOX_MODE_COMPARE )
	{
		AddMenu( menu, BOXMENU_TRAY_WALLPAPER );
		AddMenu( menu, BOXMENU_TRAY_NAME );
	}

	AddMenu( menu, BOXMENU_TRAYMENU_QUIT );

	menu->type = BOXMENU_TYPE_TRAY;
}

//------------------------------------------------------------------
/**
 * 壁紙カテゴリメニュー状態セット
 *
 * @param   vpara			描画パラメータポインタ
 * @param	defaultCategory	初期カーソル位置
 *
 */
//------------------------------------------------------------------
void BoxMenu_SetWallPaperCategoryMenu( BOXAPP_VPARAM* vpara, BOX_MENU_ID defaultCategory )
{
	BOXAPP_MENU* menu = &(vpara->menu);
	const BOX_DATA* boxData = BoxAppVPara_GetBoxData(vpara);
	u32  ex_count;

	InitWork( menu );

	AddMenu( menu, BOXMENU_WP_CATEGORY1 );
	AddMenu( menu, BOXMENU_WP_CATEGORY2 );
	AddMenu( menu, BOXMENU_WP_CATEGORY3 );
	AddMenu( menu, BOXMENU_WP_CATEGORY4 );

	ex_count = BOXDAT_GetDaiukiKabegamiCount(boxData);
	if( ex_count > 0 )
	{
		AddMenu( menu, BOXMENU_WP_CATEGORY_EX1 );
	}
	if( ex_count > 4 )
	{
		AddMenu( menu, BOXMENU_WP_CATEGORY_EX2 );
	}

	menu->type = BOXMENU_TYPE_WALLPAPER;

	if( defaultCategory >= BOXMENU_WP_CATEGORY1 && defaultCategory <= BOXMENU_WP_CATEGORY_EX2 )
	{
		menu->pos = defaultCategory - BOXMENU_WP_CATEGORY1;
	}
	else
	{
		GF_ASSERT(0);
	}

}

//------------------------------------------------------------------
/**
 * 壁紙タイプメニューセット
 *
 * @param   vpara			描画パラメータポインタ
 * @param   category		壁紙カテゴリ（メニューID）
 *
 */
//------------------------------------------------------------------
void BoxMenu_SetWallPaperTypeMenu( BOXAPP_VPARAM* vpara, BOX_MENU_ID  category )
{
	enum {
		WP_TYPE_MAX = 4,
	};

	static const u16 id_tbl[][WP_TYPE_MAX] = {
		{ BOXMENU_WP_NAME1_1, BOXMENU_WP_NAME1_2, BOXMENU_WP_NAME1_3, BOXMENU_WP_NAME1_4 },
		{ BOXMENU_WP_NAME2_1, BOXMENU_WP_NAME2_2, BOXMENU_WP_NAME2_3, BOXMENU_WP_NAME2_4 },
		{ BOXMENU_WP_NAME3_1, BOXMENU_WP_NAME3_2, BOXMENU_WP_NAME3_3, BOXMENU_WP_NAME3_4 },
		{ BOXMENU_WP_NAME4_1, BOXMENU_WP_NAME4_2, BOXMENU_WP_NAME4_3, BOXMENU_WP_NAME4_4 },
	};
	BOXAPP_MENU* menu = &(vpara->menu);
	const BOX_DATA* boxData = BoxAppVPara_GetBoxData(vpara);
	int i;

	InitWork( menu );

	// 通常壁紙
	if( category >= BOXMENU_WP_CATEGORY1 && category <= BOXMENU_WP_CATEGORY4 )
	{
		category -= BOXMENU_WP_CATEGORY1;
		for(i = 0; i < WP_TYPE_MAX; i++)
		{
			AddMenu( menu, id_tbl[category][i] );
		}
	}
	// だいすきクラブ壁紙
	else
	{
		int skip = 0;
		int add_cnt = 0;

		if( category == BOXMENU_WP_CATEGORY_EX2 ){ skip = WP_TYPE_MAX; }
		for(i=0; i<BOX_EX_WALLPAPER_MAX; i++)
		{
			if(BOXDAT_GetDaisukiKabegamiFlag(boxData, i))
			{
				if(skip)
				{
					skip--;
				}
				else
				{
					AddMenu( menu, BOXMENU_WP_NAME_EX_1+i );
					if(++add_cnt >= WP_TYPE_MAX)
					{
						break;
					}
				}
			}
		}
	}

	menu->type = BOXMENU_TYPE_WALLPAPER;

}

//------------------------------------------------------------------
/**
 * マーキングメニューセット
 *
 * @param   vpara			描画パラメータポインタ
 *
 */
//------------------------------------------------------------------
void BoxMenu_SetMarkingMenu( BOXAPP_VPARAM* vpara )
{
	BOXAPP_MENU* menu = &(vpara->menu);

	InitWork( menu );
	menu->type = BOXMENU_TYPE_MARKING;
	menu->mark = vpara->statusPoke.mark;

	AddMenu( menu, BOXMENU_MARK1 );
	AddMenu( menu, BOXMENU_MARK2 );
	AddMenu( menu, BOXMENU_MARK3 );
	AddMenu( menu, BOXMENU_MARK4 );
	AddMenu( menu, BOXMENU_MARK5 );
	AddMenu( menu, BOXMENU_MARK6 );

	AddMenu( menu, BOXMENU_MARKING_DECIDE );
	AddMenu( menu, BOXMENU_MARKING_CANCEL );

}

//------------------------------------------------------------------
/**
 * マーキング状態フラグの特定位置を反転させる
 *
 * @param   vpara		描画パラメータポインタ
 * @param   pos			反転位置
 *
 */
//------------------------------------------------------------------
void BoxMenu_ReverseMarkingState( BOXAPP_VPARAM* vpara, u32 pos )
{
	BOXAPP_MENU* menu = &(vpara->menu);

	menu->mark ^= (1 << pos);
}

//==============================================================================================================
//==============================================================================================================

//------------------------------------------------------------------
/**
 * ワーク初期化
 *
 * @param   menu		
 *
 */
//------------------------------------------------------------------
static void InitWork( BOXAPP_MENU* menu )
{
	menu->cnt = 0;
	menu->pos = 0;
}
//------------------------------------------------------------------
/**
 * 項目追加
 *
 * @param   menu		
 *
 */
//------------------------------------------------------------------
static void AddMenu( BOXAPP_MENU* menu, BOX_MENU_ID id )
{
	if( menu->cnt < BOXAPP_MENU_ELEMS_MAX )
	{
		menu->id[ menu->cnt++ ] = id;
	}
}

//==============================================================================================================
//==============================================================================================================

//------------------------------------------------------------------
/**
 * 項目選択チェック
 *
 * @param   vpara		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
int BoxMenu_Ctrl( BOXAPP_VPARAM* vpara )
{
	enum {
		LOOP_MIN_ELEMS = 3,		///< カーソルループする最低項目数
	};

	BOXAPP_MENU* menu = &(vpara->menu);

	if( sys.trg & PAD_KEY_UP )
	{
		if( menu->pos )
		{
			menu->pos--;
			return BOXMENU_CTRL_MOVE;
		}
		else if ( menu->cnt >= LOOP_MIN_ELEMS )
		{
			menu->pos = menu->cnt - 1;
			return BOXMENU_CTRL_MOVE;
		}
	}
	if( sys.trg & PAD_KEY_DOWN )
	{
		if( menu->pos < (menu->cnt-1) )
		{
			menu->pos++;
			return BOXMENU_CTRL_MOVE;
		}
		else if ( menu->cnt >= LOOP_MIN_ELEMS )
		{
			menu->pos = 0;
			return BOXMENU_CTRL_MOVE;
		}
	}

	if( sys.trg & PAD_BUTTON_B )
	{
		Snd_SePlay( SOUND_CANCEL );
		return BOXMENU_CTRL_CANCEL;
	}

	if( sys.trg & PAD_BUTTON_A )
	{
		Snd_SePlay( SOUND_DECIDE );
		return menu->id[ menu->pos ];
	}

	return BOXMENU_CTRL_LOOP;

}

//------------------------------------------------------------------
/**
 * 選択中メニューＩＤを返す
 *
 * @param   vpara		
 *
 * @retval  BOX_MENU_ID		
 */
//------------------------------------------------------------------
BOX_MENU_ID BoxMenu_GetSelectMenuID( BOXAPP_VPARAM* vpara )
{
	BOXAPP_MENU* menu = &(vpara->menu);
	return menu->id[ menu->pos ];
}

//------------------------------------------------------------------
/**
 * 先頭のメニューＩＤを返す
 *
 * @param   vpara		
 *
 * @retval  BOX_MENU_ID		
 */
//------------------------------------------------------------------
BOX_MENU_ID BoxMenu_GetFirstMenuID( BOXAPP_VPARAM* vpara )
{
	BOXAPP_MENU* menu = &(vpara->menu);
	return menu->id[ 0 ];
}
