//============================================================================================
/**
 * @file	plist_menu.c
 * @brief	ポケモンリスト画面メニュー関連
 * @author	Hiroyuki Nakamura
 * @date	05.10.18
 */
//============================================================================================
#include "common.h"
#include "system/procsys.h"
#include "system/bmp_menu.h"
#include "system/fontproc.h"
#include "system/msgdata.h"
#include "system/wordset.h"
#include "system/numfont.h"
#include "system/clact_tool.h"
#include "system/window.h"
#include "system/brightness.h"
#include "msgdata/msg_pokelist.h"
#include "poketool/poke_tool.h"
#include "poketool/pokeparty.h"
#include "poketool/monsno.h"
#include "poketool/poke_regulation.h"
#include "itemtool/item.h"
#include "itemtool/myitem.h"
#include "application/app_tool.h"
#include "application/mailtool.h"
#include "field/field_skill.h"

#define	PLIST_MENU_H_GLOBAL
#include "application/pokelist.h"
#include "plist_sys.h"
#include "plist_bmp.h"
#include "plist_obj.h"
#include "plist_menu.h"
#include "plist_snd_def.h"



static void Menu_RowSelectInit( PLIST_WORK * wk, int * seq );
static void Menu_ChgSelect( PLIST_WORK * wk, int * seq );
static void Menu_Status( PLIST_WORK * wk, int * seq );
static void Menu_Skill( PLIST_WORK * wk, int * seq );

//static void Menu_NarabikaeMain( void * work );
static void Menu_NarabikaeScreenWrite( PLIST_WORK * wk, u8 pos );
static void Menu_NarabikaeObjMove( PLIST_WORK * wk, u8 pos, u8 mv );
static void Menu_NarabikaeChg( PLIST_WORK * wk );
static void PLM_NarabikaeScrnRemake( PLIST_WORK * wk, u8 pos );

static void Menu_Iaigiri( PLIST_WORK * wk, int * seq );
static void Menu_Iwakudaki( PLIST_WORK * wk, int * seq );
static void Menu_Kairiki( PLIST_WORK * wk, int * seq );
static void Menu_Naminori( PLIST_WORK * wk, int * seq );
static void Menu_Kiribarai( PLIST_WORK * wk, int * seq );
static void Menu_RockClimb( PLIST_WORK * wk, int * seq );
static void Menu_Sorawotobu( PLIST_WORK * wk, int * seq );
static void Menu_Takinobori( PLIST_WORK * wk, int * seq );
static void Menu_Flash( PLIST_WORK * wk, int * seq );
static void Menu_Teleport( PLIST_WORK * wk, int * seq );
static void Menu_Anawohoru( PLIST_WORK * wk, int * seq );
static void Menu_Amaikaori( PLIST_WORK * wk, int * seq );
static void Menu_Osyaberi( PLIST_WORK * wk, int * seq );
static void Menu_MilkNomi( PLIST_WORK * wk, int * seq );
static void Menu_TamagoUmi( PLIST_WORK * wk, int * seq );

static int Menu_MilkNomiInit( PLIST_WORK * wk );

static void Menu_KapselSet( PLIST_WORK * wk, int * seq );

static void Menu_ItemMenuInit( PLIST_WORK * wk, int * seq );
static void Menu_ItemMenuItemSet( PLIST_WORK * wk, int *seq );
static void Menu_ItemMenuItemGet( PLIST_WORK * wk, int * seq );
static void Menu_MailMenuInit( PLIST_WORK * wk, int * seq );
static void Menu_MailMenuMailRead( PLIST_WORK * wk, int * seq );
static void Menu_MailMenuMailGet( PLIST_WORK * wk, int * seq );
static int PL_MailGetPCYes( void * work );
static int PL_MailGetPCNo( void * work );
static int PL_MailGetBagYes( void * work );
static int PL_MailGetBagNo( void * work );
static void Menu_ContestIn( PLIST_WORK * wk, int * seq );
static void Menu_BattleIn( PLIST_WORK * wk, int * seq );
static void Menu_BattleOut( PLIST_WORK * wk, int * seq );

static void Menu_Azukeru( PLIST_WORK * wk, int * seq );


static const u32 MenuParamTbl[] = {
	(const u32)Menu_RowSelectInit,		// ならびかえ
	(const u32)Menu_Status,				// つよさをみる
	(const u32)Menu_ItemMenuInit,		// もちもの
	(const u32)Menu_ItemMenuItemSet,	// もちものメニュー：もたせる
	(const u32)Menu_ItemMenuItemGet,	// もちものメニュー：あずかる
	(const u32)Menu_MailMenuInit,		// メール
	(const u32)Menu_MailMenuMailRead,	// メールを　よむ
	(const u32)Menu_MailMenuMailGet,	// メールを　とる
	(const u32)Menu_Azukeru,			// あずける
	BMPMENU_CANCEL,						// やめる
//	(const u32)Menu_ChgSelect,			// いれかえる
	BMPMENU_CANCEL,						// いれかえる
	(const u32)Menu_BattleIn,			// さんかする（戦闘参加選択）
	(const u32)Menu_BattleOut,			// さんかしない
	(const u32)Menu_ContestIn,			// さんかする（コンテスト参加）
	(const u32)Menu_KapselSet,			// セットする

	(const u32)Menu_Iaigiri,			// 技：いあいぎり
	(const u32)Menu_Sorawotobu,			// 技：そらをとぶ
	(const u32)Menu_Naminori,			// 技：なみのり
	(const u32)Menu_Kairiki,			// 技：かいりき
	(const u32)Menu_Kiribarai,			// 技：きりばらい
	(const u32)Menu_Iwakudaki,			// 技：いわくだき
	(const u32)Menu_Takinobori,			// 技：たきのぼり
	(const u32)Menu_RockClimb,			// 技：ロッククライム

	(const u32)Menu_Flash,				// 技：フラッシュ
	(const u32)Menu_Teleport,			// 技：テレポート
	(const u32)Menu_Anawohoru,			// 技：あなをほる
	(const u32)Menu_Amaikaori,			// 技：あまいかおり
	(const u32)Menu_Osyaberi,			// 技：おしゃべり

	(const u32)Menu_MilkNomi,			// 技：ミルクのみ
	(const u32)Menu_TamagoUmi,			// 技：タマゴうみ

	BMPMENU_CANCEL
};


u32 PokeListMenuParamGet( u8 id )
{
	return MenuParamTbl[id];
}


//--------------------------------------------------------------------------------------------
/**
 * メニュー破棄
 *
 * @param	wk		バッグ画面のワーク
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void PokeListMenuExit( PLIST_WORK * wk )
{
	BmpMenuWinClear( &wk->add_win[ADD_WIN_MENU], WINDOW_TRANS_OFF );
	GF_BGL_BmpWinOffVReq( &wk->add_win[ADD_WIN_MENU] );
	BmpMenuExit( wk->mw, NULL );
	BMP_MENULIST_Delete( wk->md );
	GF_BGL_BmpWinDel( &wk->add_win[ADD_WIN_MENU] );
}


//============================================================================================
//	もちもの
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * メニュー「もちもの」
 *
 * @param
 *
 * @return
 */
//--------------------------------------------------------------------------------------------
static void Menu_ItemMenuInit( PLIST_WORK * wk, int * seq )
{
	BMPMENU_HEADER	mh;

	PokeListMenuExit( wk );

	PokeListMiddleMsgPut( wk, mes_pokelist_03_02, 0 );

	wk->md = BMP_MENULIST_Create( 3, HEAPID_POKELIST );
	BMP_MENULIST_AddString(
		wk->md, wk->menu_str[MENU_ITEM_S], PokeListMenuParamGet(MENU_ITEM_S) );
	BMP_MENULIST_AddString(
		wk->md, wk->menu_str[MENU_ITEM_G], PokeListMenuParamGet(MENU_ITEM_G) );
	BMP_MENULIST_AddString(
		wk->md, wk->menu_str[MENU_CANCEL], PokeListMenuParamGet(MENU_CANCEL) );

	mh.menu  = wk->md;
	mh.win   = &wk->win[WIN_ITEM_MENU];
	mh.font  = FONT_SYSTEM;
	mh.x_max = 1;
	mh.y_max = 3;
	mh.line_spc = 0;
	mh.c_disp_f = 0;
	mh.loop_f = 0;

	BmpMenuWinWrite( &wk->win[WIN_ITEM_MENU], WINDOW_TRANS_OFF, PL_MENU_WIN_CGX, PAL_MENU_WIN );
	wk->mw = BmpMenuAddEx( &mh, 8, 0, 0, HEAPID_POKELIST, PAD_BUTTON_CANCEL );

	*seq = SEQ_ITEM_MENU;
}

//--------------------------------------------------------------------------------------------
/**
 * メニュー「もたせる」
 *
 * @param
 *
 * @return
 */
//--------------------------------------------------------------------------------------------
static void Menu_ItemMenuItemSet( PLIST_WORK * wk, int * seq )
{
	BmpMenuExit( wk->mw, NULL );
	BMP_MENULIST_Delete( wk->md );

	wk->dat->ret_mode = PL_RET_ITEMSET;

	*seq = SEQ_OUT_SET;
}


//--------------------------------------------------------------------------------------------
/**
 * メニュー「あずかる」
 *
 * @param
 *
 * @return
 */
//--------------------------------------------------------------------------------------------
static void Menu_ItemMenuItemGet( PLIST_WORK * wk, int * seq )
{
	POKEMON_PARAM * pp;

	BmpMenuWinClear( &wk->win[WIN_ITEM_MENU], WINDOW_TRANS_OFF );
	BmpMenuExit( wk->mw, NULL );
	BMP_MENULIST_Delete( wk->md );

	if( wk->panel[wk->pos].item == 0 ){
		pp = PokeParty_GetMemberPointer( wk->dat->pp, wk->pos );
		MSGMAN_GetString( wk->msg_man, mes_pokelist_04_29, wk->str_buf );
		WORDSET_RegisterPokeNickName( wk->wset, 0, PPPPointerGet(pp) );
		WORDSET_ExpandStr( wk->wset, wk->msg_buf, wk->str_buf );
	}else if(MyItem_AddItem(wk->dat->myitem,wk->panel[wk->pos].item,1,HEAPID_POKELIST)==TRUE){
		u32	item;

		pp = PokeParty_GetMemberPointer( wk->dat->pp, wk->pos );
		item = 0;
		PokeParaPut( pp, ID_PARA_item, &item );
		PokeParaAusuFormChange( pp );

		MSGMAN_GetString( wk->msg_man, mes_pokelist_04_30, wk->str_buf );
		WORDSET_RegisterPokeNickName( wk->wset, 0, PPPPointerGet(pp) );
		WORDSET_RegisterItemName( wk->wset, 1, wk->panel[wk->pos].item );
		WORDSET_ExpandStr( wk->wset, wk->msg_buf, wk->str_buf );
		wk->panel[wk->pos].item = 0;
		PokeList_ItemIconChg( wk, wk->pos, wk->panel[wk->pos].item );
	}else{
		MSGMAN_GetString( wk->msg_man, mes_pokelist_04_31, wk->msg_buf );
	}

	BmpTalkWinWrite( &wk->win[WIN_L_MSG], WINDOW_TRANS_OFF, PL_TALK_WIN_CGX, PAL_TALK_WIN );
	GF_BGL_BmpWinDataFill( &wk->win[WIN_L_MSG], FBMP_COL_WHITE );
	PokeList_TalkMsgStart( wk );
	*seq = SEQ_ITEM_MENU_GET;
}

int PokeList_ItemMenuItemGetEndWait( PLIST_WORK * wk )
{
	if( GF_MSG_PrintEndCheck( wk->msg_index ) == 0 ){
		if( sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL) ){
			BmpTalkWinClear( &wk->win[WIN_L_MSG], WINDOW_TRANS_OFF );
			PokeListSmallMsgPut( wk, mes_pokelist_02_01, 1 );
			CATS_ObjectPaletteSet( wk->act_work[PLIST_ACT_CURSOR1], 0 );
			return SEQ_MAIN;
		}
	}
	return SEQ_ITEM_MENU_GET;
}


//============================================================================================
//	メール
//============================================================================================

//--------------------------------------------------------------------------------------------
/**
 * メニュー「メール」
 *
 * @param
 *
 * @return
 */
//--------------------------------------------------------------------------------------------
static void Menu_MailMenuInit( PLIST_WORK * wk, int * seq )
{
	BMPMENU_HEADER	mh;

	PokeListMenuExit( wk );

	PokeListMiddleMsgPut( wk, mes_pokelist_03_03, 0 );

	wk->md = BMP_MENULIST_Create( 3, HEAPID_POKELIST );
	BMP_MENULIST_AddString(
		wk->md, wk->menu_str[MENU_MAIL_R], PokeListMenuParamGet(MENU_MAIL_R) );
	BMP_MENULIST_AddString(
		wk->md, wk->menu_str[MENU_MAIL_G], PokeListMenuParamGet(MENU_MAIL_G) );
	BMP_MENULIST_AddString(
		wk->md, wk->menu_str[MENU_CANCEL], PokeListMenuParamGet(MENU_CANCEL) );

	mh.menu  = wk->md;
	mh.win   = &wk->win[WIN_ITEM_MENU];
	mh.font  = FONT_SYSTEM;
	mh.x_max = 1;
	mh.y_max = 3;
	mh.line_spc = 0;
	mh.c_disp_f = 0;
	mh.loop_f = 0;

	BmpMenuWinWrite( &wk->win[WIN_ITEM_MENU], WINDOW_TRANS_OFF, PL_MENU_WIN_CGX, PAL_MENU_WIN );
	wk->mw = BmpMenuAddEx( &mh, 8, 0, 0, HEAPID_POKELIST, PAD_BUTTON_CANCEL );

	*seq = SEQ_ITEM_MENU;
}

//--------------------------------------------------------------------------------------------
/**
 * メニュー「メールを　よむ」
 *
 * @param
 *
 * @return
 */
//--------------------------------------------------------------------------------------------
static void Menu_MailMenuMailRead( PLIST_WORK * wk, int * seq )
{
	BmpMenuExit( wk->mw, NULL );
	BMP_MENULIST_Delete( wk->md );

	wk->dat->ret_mode = PL_RET_MAILREAD;

	*seq = SEQ_OUT_SET;
}

//--------------------------------------------------------------------------------------------
/**
 * メニュー「メールを　とる」
 *
 * @param
 *
 * @return
 */
//--------------------------------------------------------------------------------------------
static void Menu_MailMenuMailGet( PLIST_WORK * wk, int * seq )
{
	BmpMenuWinClear( &wk->win[WIN_ITEM_MENU], WINDOW_TRANS_OFF );
	BmpMenuExit( wk->mw, NULL );
	BMP_MENULIST_Delete( wk->md );

	PokeListLargeMsgPut( wk, mes_pokelist_04_01, 1 );
	wk->yesno.yes = PL_MailGetPCYes;
	wk->yesno.no  = PL_MailGetPCNo;
	wk->next_seq = SEQ_YESNO_INIT;
	*seq = SEQ_MSG_WAIT;
}

static int PL_MailGetPCYes( void * work )
{
	PLIST_WORK * wk = work;
	POKEMON_PARAM * pp;

	wk = work;
	pp = PokeParty_GetMemberPointer( wk->dat->pp, wk->pos );

	if( MailSys_MoveMailPoke2Paso(wk->dat->mailblock,pp,HEAPID_POKELIST) != MAILDATA_NULLID ){
		wk->panel[wk->pos].item = 0;
		PokeList_ItemIconChg( wk, wk->pos, wk->panel[wk->pos].item );
		PokeListLargeMsgPut( wk, mes_pokelist_04_02, 0 );
	}else{
		PokeListLargeMsgPut( wk, mes_pokelist_04_04, 0 );
	}
	wk->next_seq = SEQ_ITEMGET_END;
	return SEQ_MSG_WAIT;
}

static int PL_MailGetPCNo( void * work )
{
	PLIST_WORK * wk = work;

	PokeListLargeMsgPut( wk, mes_pokelist_04_03, 0 );
	wk->yesno.yes = PL_MailGetBagYes;
	wk->yesno.no  = PL_MailGetBagNo;
	wk->next_seq = SEQ_YESNO_INIT;
	return SEQ_MSG_WAIT;
}

static int PL_MailGetBagYes( void * work )
{
	PLIST_WORK * wk = work;

	if( MyItem_AddItem( wk->dat->myitem, wk->panel[wk->pos].item, 1, HEAPID_POKELIST ) == TRUE ){
		POKEMON_PARAM * pp;
		u32	item;

		pp = PokeParty_GetMemberPointer( wk->dat->pp, wk->pos );
		item = 0;
		PokeParaPut( pp, ID_PARA_item, &item );
		PokeParaAusuFormChange( pp );

		wk->panel[wk->pos].item = 0;
		PokeList_ItemIconChg( wk, wk->pos, wk->panel[wk->pos].item );
		PokeListLargeMsgPut( wk, mes_pokelist_04_05, 0 );
	}else{
		PokeListLargeMsgPut( wk, mes_pokelist_04_31, 0 );
	}
	wk->next_seq = SEQ_ITEMGET_END;
	return SEQ_MSG_WAIT;
}

static int PL_MailGetBagNo( void * work )
{
	PLIST_WORK * wk = work;

	BmpTalkWinClear( &wk->win[WIN_L_MSG], WINDOW_TRANS_OFF );
	PokeListSmallMsgPut( wk, mes_pokelist_02_01, 1 );
	CATS_ObjectPaletteSet( wk->act_work[PLIST_ACT_CURSOR1], 0 );
	return SEQ_MAIN;
}

int PokeList_ItemGetEnd( PLIST_WORK * wk )
{
	if( sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL) ){
		BmpTalkWinClear( &wk->win[WIN_L_MSG], WINDOW_TRANS_OFF );
		PokeListSmallMsgPut( wk, mes_pokelist_02_01, 1 );
		CATS_ObjectPaletteSet( wk->act_work[PLIST_ACT_CURSOR1], 0 );
		return SEQ_MAIN;
	}
	return SEQ_ITEMGET_END;
}





//--------------------------------------------------------------------------------------------
/**
 * あずける
 *
 */
//--------------------------------------------------------------------------------------------
static void Menu_Azukeru( PLIST_WORK * wk, int * seq )
{
	// カプセルを持っていない
	if( wk->panel[wk->pos].cb == 0 ){
		BmpMenuExit( wk->mw, NULL );
		BMP_MENULIST_Delete( wk->md );
		wk->dat->ret_mode = PL_RET_NORMAL;
		*seq = SEQ_OUT_SET;
		return;
	}

	PokeListMenuExit( wk );

	PokeListLargeMsgPut( wk, mes_pokelist_08_11, 1 );
	wk->yesno.yes = PL_KapselGetYes;
	wk->yesno.no  = PL_KapselGetNo;
	wk->next_seq = SEQ_YESNO_INIT;
	*seq = SEQ_MSG_WAIT;
}

int PL_KapselGetYes( void * work )
{
	PLIST_WORK * wk;
	POKEMON_PARAM * pp;
//	int	cb;

	wk = work;
	pp = PokeParty_GetMemberPointer( wk->dat->pp, wk->pos );
//	cb = 0;

	// カプセルを外す
	PokePara_CustomBallDataInit( pp );
//	PokeParaPut( pp, ID_PARA_cb_id, (u8 *)&cb );
//	PokeParaPut( pp, ID_PARA_cb_core, (u8 *)&cb );

	wk->dat->ret_mode = PL_RET_NORMAL;
	return SEQ_OUT_SET;
}

int PL_KapselGetNo( void * work )
{
	PLIST_WORK * wk = work;

	BmpTalkWinClear( &wk->win[WIN_L_MSG], WINDOW_TRANS_OFF );
	PokeListSmallMsgPut( wk, mes_pokelist_02_01, 1 );
	CATS_ObjectPaletteSet( wk->act_work[PLIST_ACT_CURSOR1], 0 );
	return SEQ_MAIN;
}


//--------------------------------------------------------------------------------------------
/**
 * ならびかえ
 *
 */
//--------------------------------------------------------------------------------------------
static void Menu_RowSelectInit( PLIST_WORK * wk, int * seq )
{
	s16	x, y;

	wk->chg_flg = 1;
	wk->chg_pos = wk->pos;

	// ダミーカーソル表示
	CATS_ObjectPaletteSet( wk->act_work[PLIST_ACT_CURSOR1], 0 );
	CATS_ObjectPosGet( wk->act_work[PLIST_ACT_CURSOR1], &x, &y );
	CATS_ObjectPosSet( wk->act_work[PLIST_ACT_CURSOR2], x, y );
	CLACT_AnmChg(
		wk->act_work[PLIST_ACT_CURSOR2],
		PokeListSelCursorCheck( wk->dat->type, wk->chg_pos )+2 );
	CLACT_SetDrawFlag( wk->act_work[PLIST_ACT_CURSOR2], 1 );

	// プレートカラーチェンジ
	PokeListPanelPaletteSet( wk, wk->chg_pos );

	// メッセージ非表示
	BmpTalkWinClear( &wk->win[WIN_M_MSG], WINDOW_TRANS_OFF );
	// メニュー削除
	PokeListMenuExit( wk );

	// メッセージ表示
	PokeListSmallMsgPut( wk, mes_pokelist_02_02, 1 );

	*seq = SEQ_ROW_SEL;
}

void PokeListRowCancel( PLIST_WORK * wk )
{
	wk->chg_flg = 0;
	CLACT_SetDrawFlag( wk->act_work[PLIST_ACT_CURSOR2], 0 );
	if( wk->pos < PL_SEL_POS_ENTER ){
		PokeListPanelPaletteSet( wk, wk->pos );
	}
	PokeListPanelPaletteSet( wk, wk->chg_pos );
	PokeListSmallMsgPut( wk, mes_pokelist_02_01, 1 );
}

void PokeListMenuRowMoveInit( PLIST_WORK * wk )
{
	u16 * plate_bg;
	u16 * str_bg;
	s8	px1, py1, px2, py2;
	u16	i;

	wk->chg_wk.pos[0] = wk->pos;
	wk->chg_wk.pos[1] = wk->chg_pos;
	wk->chg_wk.flg    = 1;
	wk->chg_wk.cnt    = 0;
	wk->chg_wk.seq    = 0;

	if( wk->chg_wk.pos[0] & 1 ){
		wk->chg_wk.mv[0] = 1;
	}else{
		wk->chg_wk.mv[0] = 0;
	}
	if( wk->chg_wk.pos[1] & 1 ){
		wk->chg_wk.mv[1] = 1;
	}else{
		wk->chg_wk.mv[1] = 0;
	}

	// スクリーンコピー
	plate_bg = (u16 *)GF_BGL_ScreenAdrsGet( wk->bgl, GF_BGL_FRAME2_M );
	str_bg   = (u16 *)GF_BGL_ScreenAdrsGet( wk->bgl, GF_BGL_FRAME1_M );

	px1 = wk->panel[ wk->chg_wk.pos[0] ].plate_px;
	py1 = wk->panel[ wk->chg_wk.pos[0] ].plate_py;
	px2 = wk->panel[ wk->chg_wk.pos[1] ].plate_px;
	py2 = wk->panel[ wk->chg_wk.pos[1] ].plate_py;

	for( i=0; i<PL_PANEL_SY; i++ ){
		// 1
		memcpy(
			&wk->chg_wk.plate_bg[0][ i*PL_PANEL_SX ],
			&plate_bg[ px1 + (py1+i)*32 ],
			PL_PANEL_SX*2 );
		memcpy(
			&wk->chg_wk.str_bg[0][ i*PL_PANEL_SX ],
			&str_bg[ px1 + (py1+i)*32 ],
			PL_PANEL_SX*2 );
		// 2
		memcpy(
			&wk->chg_wk.plate_bg[1][ i*PL_PANEL_SX ],
			&plate_bg[ px2 + (py2+i)*32 ],
			PL_PANEL_SX*2 );
		memcpy(
			&wk->chg_wk.str_bg[1][ i*PL_PANEL_SX ],
			&str_bg[ px2 + (py2+i)*32 ],
			PL_PANEL_SX*2 );
	}

	// カーソル非表示
	CLACT_SetDrawFlag( wk->act_work[PLIST_ACT_CURSOR1], 0 );
	CLACT_SetDrawFlag( wk->act_work[PLIST_ACT_CURSOR2], 0 );

//	wk->vblank_func = Menu_NarabikaeMain;
}

BOOL PokeListMenu_NarabikaeMain( PLIST_WORK * wk )
{
	MENU_NARABIKAE_WORK * nwk = &wk->chg_wk;

	switch( nwk->seq ){
	case 0:
		Snd_SePlay( PLIST_SE_MV_OUT );
		nwk->seq = 1;
		break;

	case 1:		// 移動
		nwk->cnt+=1;

		Menu_NarabikaeScreenWrite( wk, 0 );
		Menu_NarabikaeScreenWrite( wk, 1 );

		Menu_NarabikaeObjMove( wk, 0, nwk->mv[0] );
		Menu_NarabikaeObjMove( wk, 1, nwk->mv[1] );

		GF_BGL_LoadScreenV_Req( wk->bgl, GF_BGL_FRAME2_M );
		GF_BGL_LoadScreenV_Req( wk->bgl, GF_BGL_FRAME1_M );

		if( nwk->cnt == 16 ){
			nwk->seq = 2;
		}
		break;

	case 2:		// いれかえ
		Menu_NarabikaeChg( wk );
		Snd_SePlay( PLIST_SE_MV_IN );
		nwk->seq = 3;
		break;

	case 3:		// 移動
		nwk->cnt-=1;

		Menu_NarabikaeScreenWrite( wk, 0 );
		Menu_NarabikaeScreenWrite( wk, 1 );

		Menu_NarabikaeObjMove( wk, 0, nwk->mv[0]^1 );
		Menu_NarabikaeObjMove( wk, 1, nwk->mv[1]^1 );

		GF_BGL_LoadScreenV_Req( wk->bgl, GF_BGL_FRAME2_M );
		GF_BGL_LoadScreenV_Req( wk->bgl, GF_BGL_FRAME1_M );

		if( nwk->cnt == 0 ){
			nwk->seq = 4;
		}
		break;

	case 4:		// 復帰・終了
		PokeParty_ExchangePosition( wk->dat->pp, nwk->pos[0], nwk->pos[1] );
		CLACT_SetDrawFlag( wk->act_work[PLIST_ACT_CURSOR1], 1 );
		nwk->flg = 0;
		wk->chg_flg = 0;
		PokeListPanelPaletteSet( wk, wk->pos );
		PokeListPanelPaletteSet( wk, wk->chg_pos );
		PokeListSmallMsgPut( wk, mes_pokelist_02_01, 0 );
		return TRUE;
	}

	return FALSE;
}

static void Menu_NarabikaeScreenWrite( PLIST_WORK * wk, u8 pos )
{
	MENU_NARABIKAE_WORK * nwk;
	s8	px, py;
	u8	i;

	nwk = &wk->chg_wk;

	px = wk->panel[ nwk->pos[pos] ].plate_px;
	py = wk->panel[ nwk->pos[pos] ].plate_py;

	GF_BGL_ScrFill(
		wk->bgl, GF_BGL_FRAME2_M, 0, px, py, PL_PANEL_SX, PL_PANEL_SY, GF_BGL_SCRWRT_PALNL );
	GF_BGL_ScrFill(
		wk->bgl, GF_BGL_FRAME1_M, 0, px, py, PL_PANEL_SX, PL_PANEL_SY, GF_BGL_SCRWRT_PALNL );

	if( nwk->mv[pos] == 0 ){
		GF_BGL_ScrWriteExpand(
			wk->bgl, GF_BGL_FRAME2_M, px, py, 16-nwk->cnt, PL_PANEL_SY,
			&nwk->plate_bg[pos], nwk->cnt, 0, PL_PANEL_SX, PL_PANEL_SY );
		GF_BGL_ScrWriteExpand(
			wk->bgl, GF_BGL_FRAME1_M, px, py, 16-nwk->cnt, PL_PANEL_SY,
			&nwk->str_bg[pos], nwk->cnt, 0, PL_PANEL_SX, PL_PANEL_SY );
	}else{
		GF_BGL_ScrWriteExpand(
			wk->bgl, GF_BGL_FRAME2_M, px+nwk->cnt, py, 16-nwk->cnt, PL_PANEL_SY,
			&nwk->plate_bg[pos], 0, 0, PL_PANEL_SX, PL_PANEL_SY );
		GF_BGL_ScrWriteExpand(
			wk->bgl, GF_BGL_FRAME1_M, px+nwk->cnt, py, 16-nwk->cnt, PL_PANEL_SY,
			&nwk->str_bg[pos], 0, 0, PL_PANEL_SX, PL_PANEL_SY );
	}
}

static void Menu_NarabikaeObjMove( PLIST_WORK * wk, u8 pos, u8 mv )
{
	MENU_NARABIKAE_WORK * nwk;
	s16	x, y;

	nwk = &wk->chg_wk;

	CATS_ObjectPosGet( wk->act_work[PLIST_ACT_BALL1+nwk->pos[pos]], &x, &y );

	if( mv == 0 ){
		wk->panel[nwk->pos[pos]].mons_px -= 8;
		wk->panel[nwk->pos[pos]].st_px -= 8;
		wk->panel[nwk->pos[pos]].item_px -= 8;
		x -= 8;
	}else{
		wk->panel[nwk->pos[pos]].mons_px += 8;
		wk->panel[nwk->pos[pos]].st_px += 8;
		wk->panel[nwk->pos[pos]].item_px += 8;
		x += 8;
	}

	CATS_ObjectPosSet(
		wk->panel[nwk->pos[pos]].icon_cwp,
		wk->panel[nwk->pos[pos]].mons_px,
		wk->panel[nwk->pos[pos]].mons_py );

	CATS_ObjectPosSet(
		wk->act_work[PLIST_ACT_ST1+nwk->pos[pos]],
		wk->panel[nwk->pos[pos]].st_px,
		wk->panel[nwk->pos[pos]].st_py );

	CATS_ObjectPosSet(
		wk->act_work[PLIST_ACT_ITEM1+nwk->pos[pos]],
		wk->panel[nwk->pos[pos]].item_px,
		wk->panel[nwk->pos[pos]].item_py );

	CATS_ObjectPosSet(
		wk->act_work[PLIST_ACT_CB1+nwk->pos[pos]],
		wk->panel[nwk->pos[pos]].item_px+8,
		wk->panel[nwk->pos[pos]].item_py );

	CATS_ObjectPosSet( wk->act_work[PLIST_ACT_BALL1+nwk->pos[pos]], x, y );
}

static void Menu_NarabikaeChg( PLIST_WORK * wk )
{
	PL_PANEL_DATA * cpy;

	MENU_NARABIKAE_WORK * nwk;
	CATS_ACT_PTR	cap;
	s16	pos;

	nwk = &wk->chg_wk;

	// データいれかえ
	cpy = sys_AllocMemory( HEAPID_POKELIST, sizeof(PL_PANEL_DATA) );
	*cpy = wk->panel[ nwk->pos[0] ];
	wk->panel[ nwk->pos[0] ] = wk->panel[ nwk->pos[1] ];
	wk->panel[ nwk->pos[1] ] = *cpy;
	sys_FreeMemory( HEAPID_POKELIST, cpy );

	// プレートとアイコンの座標は戻す
	pos = wk->panel[ nwk->pos[0] ].mons_px;
	wk->panel[ nwk->pos[0] ].mons_px = wk->panel[ nwk->pos[1] ].mons_px;
	wk->panel[ nwk->pos[1] ].mons_px = pos;
	pos = wk->panel[ nwk->pos[0] ].mons_py;
	wk->panel[ nwk->pos[0] ].mons_py = wk->panel[ nwk->pos[1] ].mons_py;
	wk->panel[ nwk->pos[1] ].mons_py = pos;

	pos = wk->panel[ nwk->pos[0] ].st_px;
	wk->panel[ nwk->pos[0] ].st_px = wk->panel[ nwk->pos[1] ].st_px;
	wk->panel[ nwk->pos[1] ].st_px = pos;
	pos = wk->panel[ nwk->pos[0] ].st_py;
	wk->panel[ nwk->pos[0] ].st_py = wk->panel[ nwk->pos[1] ].st_py;
	wk->panel[ nwk->pos[1] ].st_py = pos;

	pos = wk->panel[ nwk->pos[0] ].item_px;
	wk->panel[ nwk->pos[0] ].item_px = wk->panel[ nwk->pos[1] ].item_px;
	wk->panel[ nwk->pos[1] ].item_px = pos;
	pos = wk->panel[ nwk->pos[0] ].item_py;
	wk->panel[ nwk->pos[0] ].item_py = wk->panel[ nwk->pos[1] ].item_py;
	wk->panel[ nwk->pos[1] ].item_py = pos;

	pos = wk->panel[ nwk->pos[0] ].plate_px;
	wk->panel[ nwk->pos[0] ].plate_px = wk->panel[ nwk->pos[1] ].plate_px;
	wk->panel[ nwk->pos[1] ].plate_px = pos;
	pos = wk->panel[ nwk->pos[0] ].plate_py;
	wk->panel[ nwk->pos[0] ].plate_py = wk->panel[ nwk->pos[1] ].plate_py;
	wk->panel[ nwk->pos[1] ].plate_py = pos;

	// パラメータ書き換え
	PokeListParamPut( wk, nwk->pos[0] );
	PokeListParamPut( wk, nwk->pos[1] );
	PokeListParamBmpWinOff( wk, nwk->pos[0] );
	PokeListParamBmpWinOff( wk, nwk->pos[1] );
//	PokeListParamBmpCgxOn( wk, nwk->pos[0] );
//	PokeListParamBmpCgxOn( wk, nwk->pos[1] );

	PLM_NarabikaeScrnRemake( wk, 0 );
	PLM_NarabikaeScrnRemake( wk, 1 );

	PokeList_StatusIconChg( wk, nwk->pos[0], wk->panel[nwk->pos[0]].st );	// 状態異常アイコン
	PokeList_StatusIconChg( wk, nwk->pos[1], wk->panel[nwk->pos[1]].st );	// 状態異常アイコン

	PokeList_ItemIconChg( wk, nwk->pos[0], wk->panel[nwk->pos[0]].item );	// アイテムアイコン
	PokeList_ItemIconChg( wk, nwk->pos[1], wk->panel[nwk->pos[1]].item );	// アイテムアイコン

	PokeList_CustomIconChg( wk, nwk->pos[0] );
	PokeList_CustomIconChg( wk, nwk->pos[1] );
}

static void PLM_NarabikaeScrnRemake( PLIST_WORK * wk, u8 pos )
{
	MENU_NARABIKAE_WORK * nwk;
	const u16 * scrn;
	u16 * buf;
	u16	pal;
	u16	i;

	nwk  = &wk->chg_wk;
	buf  = nwk->plate_bg[pos];
	scrn = PokeList_HPGageCharGet( wk );

	if( wk->panel[ nwk->pos[pos] ].egg == 1 ){
		for( i=0; i<PL_PANEL_HPGAGE_SX; i++ ){
			pal = buf[PL_PANEL_HPGAGE_PY*16+PL_PANEL_HPGAGE_PX+i] & 0xf000;
			buf[PL_PANEL_HPGAGE_PY*16+PL_PANEL_HPGAGE_PX+i] = pal | PL_PANEL_HPGAGE_CLEAR_CHR;
		}
	}else{
		for( i=0; i<PL_PANEL_HPGAGE_SX; i++ ){
			pal = buf[PL_PANEL_HPGAGE_PY*16+PL_PANEL_HPGAGE_PX+i] & 0xf000;
			buf[PL_PANEL_HPGAGE_PY*16+PL_PANEL_HPGAGE_PX+i] = pal | (scrn[i]&0xfff);
		}
	}
}




//--------------------------------------------------------------------------------------------
/**
 * さんかする（戦闘参加選択）
 *
 */
//--------------------------------------------------------------------------------------------
static void Menu_BattleIn( PLIST_WORK * wk, int * seq )
{
	u8	i;

	BmpTalkWinClear( &wk->win[WIN_M_MSG], WINDOW_TRANS_OFF );
	PokeListMenuExit( wk );

	for( i=0; i<wk->dat->in_max; i++ ){
		if( wk->dat->in_num[i] != 0 ){ continue; }

		wk->dat->in_num[i] = wk->pos+1;

		PokeList_PanelBattleInCommPut( wk, wk->pos );
		PokeListSmallMsgPut( wk, mes_pokelist_02_06, 1 );

		CATS_ObjectPaletteSet( wk->act_work[PLIST_ACT_CURSOR1], 0 );
		if( i == wk->dat->in_max-1 ){
			PokeList_CursorMoveAuto( wk, PL_SEL_POS_ENTER );
		}
		*seq = SEQ_MAIN;
		return;
	}

	switch( wk->dat->in_max ){
	case 1:
		PokeListLargeMsgPut( wk, mes_pokelist_04_61_03, 1 );
		break;
	case 2:
		PokeListLargeMsgPut( wk, mes_pokelist_04_40, 1 );
		break;
	case 3:
		PokeListLargeMsgPut( wk, mes_pokelist_04_62, 1 );
		break;
	case 4:
		PokeListLargeMsgPut( wk, mes_pokelist_04_63, 1 );
		break;
	case 5:
		PokeListLargeMsgPut( wk, mes_pokelist_04_63_01, 1 );
		break;
	}
	wk->next_seq = SEQ_BTLIN_ERR;
	*seq = SEQ_MSG_WAIT;
}

int PokeList_BattleInWaitError( PLIST_WORK * wk )
{
	if( sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL) ){
		BmpTalkWinClear( &wk->win[WIN_L_MSG], WINDOW_TRANS_OFF );
		PokeListSmallMsgPut( wk, mes_pokelist_02_06, 1 );
		CATS_ObjectPaletteSet( wk->act_work[PLIST_ACT_CURSOR1], 0 );
		return SEQ_MAIN;
	}
	return SEQ_BTLIN_ERR;
}


//--------------------------------------------------------------------------------------------
/**
 * さんかしない
 *
 */
//--------------------------------------------------------------------------------------------
static void Menu_BattleOut( PLIST_WORK * wk, int * seq )
{
	u8	i;

	for( i=0; i<wk->dat->in_max; i++ ){
		if( wk->dat->in_num[i] == wk->pos+1 ){
			wk->dat->in_num[i] = 0;
			for( i=i; i<wk->dat->in_max-1; i++ ){
				wk->dat->in_num[i] = wk->dat->in_num[i+1];
				wk->dat->in_num[i+1] = 0;
			}
			break;
		}
	}

	for( i=0; i<6; i++ ){
		if( wk->panel[i].flg == 0 ){ continue; }
		PokeList_PanelBattleInCommPut( wk, i );
	}

	BmpTalkWinClear( &wk->win[WIN_M_MSG], WINDOW_TRANS_OFF );
	PokeListMenuExit( wk );
	PokeListSmallMsgPut( wk, mes_pokelist_02_01, 1 );
	CATS_ObjectPaletteSet( wk->act_work[PLIST_ACT_CURSOR1], 0 );
	*seq = SEQ_MAIN;
}



//--------------------------------------------------------------------------------------------
/**
 * さんかする（コンテスト参加）
 *
 */
//--------------------------------------------------------------------------------------------
static void Menu_ContestIn( PLIST_WORK * wk, int * seq )
{
	wk->dat->ret_mode = PL_RET_NORMAL;

	BmpMenuExit( wk->mw, NULL );
	BMP_MENULIST_Delete( wk->md );

	*seq = SEQ_OUT_SET;
}



//--------------------------------------------------------------------------------------------
/**
 * いれかえ
 *
 */
//--------------------------------------------------------------------------------------------
#if 0
static void Menu_ChgError( void * work );
static void ChgErrorMsgMake( PLIST_WORK * wk, u32 id );

static void Menu_ChgSelect( PLIST_WORK * wk, int * seq )
{
	// 先頭
	if( wk->pos == 0 ){
		PokeListMenuExit( wk );
		BmpTalkWinClear( &wk->win[WIN_M_MSG], WINDOW_TRANS_OFF );
		ChgErrorMsgMake( wk, mes_pokelist_04_54 );
		PokeListLargeMsgPut( wk, PL_MSG_COMP_EXPAND, 1 );
		*seq = SEQ_FUNC_WAIT;
		wk->vblank_func = Menu_ChgError;
		return;
	}
	// HP=0
	if( wk->panel[wk->pos].hp == 0 ){
		PokeListMenuExit( wk );
		BmpTalkWinClear( &wk->win[WIN_M_MSG], WINDOW_TRANS_OFF );
		ChgErrorMsgMake( wk, mes_pokelist_04_55 );
		PokeListLargeMsgPut( wk, PL_MSG_COMP_EXPAND, 1 );
		*seq = SEQ_FUNC_WAIT;
		wk->vblank_func = Menu_ChgError;
		return;
	}
/*
	// 技効果
	if( wk->dat->chg_waza != 0 ){
		PokeListMenuExit( wk );
		BmpTalkWinClear( &wk->win[WIN_M_MSG], WINDOW_TRANS_OFF );
		ChgErrorMsgMake( wk, mes_pokelist_04_55 );
		PokeListLargeMsgPut( wk, PL_MSG_COMP_EXPAND, 1 );
		*seq = SEQ_FUNC_WAIT;
		wk->vblank_func = Menu_ChgError;
		return;
	}
*/
	wk->dat->ret_mode = PL_RET_CHANGE;

	BmpMenuExit( wk->mw, NULL );
	BMP_MENULIST_Delete( wk->md );

	*seq = SEQ_OUT_SET;
}

static void ChgErrorMsgMake( PLIST_WORK * wk, u32 id )
{
	POKEMON_PARAM * pp;
	STRBUF * str;

	pp  = PokeParty_GetMemberPointer( wk->dat->pp, wk->pos );
	str = MSGMAN_AllocString( wk->msg_man, id );
	WORDSET_RegisterPokeNickName( wk->wset, 0, PPPPointerGet(pp) );
	WORDSET_ExpandStr( wk->wset, wk->msg_buf, str );
	STRBUF_Delete( str );
}

static void Menu_ChgError( void * work )
{
	PLIST_WORK * wk = (PLIST_WORK *)work;

	if( GF_MSG_PrintEndCheck( wk->msg_index ) != 0 ){ return; }

	if( sys.trg & ( PAD_BUTTON_A|PAD_BUTTON_B ) ){
		BmpTalkWinClear( &wk->win[WIN_L_MSG], WINDOW_TRANS_OFF );
		PokeListSmallMsgPut( wk, mes_pokelist_02_01, 1 );
		wk->vblank_func = NULL;
	}
}

#endif


//--------------------------------------------------------------------------------------------
/**
 * ステータス
 *
 */
//--------------------------------------------------------------------------------------------
static void Menu_Status( PLIST_WORK * wk, int * seq )
{
	wk->dat->ret_mode = PL_RET_STATUS;

	BmpMenuExit( wk->mw, NULL );
	BMP_MENULIST_Delete( wk->md );

	*seq = SEQ_OUT_SET;
}


//--------------------------------------------------------------------------------------------
/**
 * セットする
 *
 */
//--------------------------------------------------------------------------------------------
static void Menu_KapselSet( PLIST_WORK * wk, int * seq )
{
//	POKEMON_PARAM * pp;

	PokeListMenuExit( wk );
	BmpTalkWinClear( &wk->win[WIN_M_MSG], WINDOW_TRANS_OFF );
/*
	pp = PokeParty_GetMemberPointer( wk->dat->pp, wk->pos );

	if( PokeParaGet( pp, ID_PARA_cb_id, NULL ) == 0 ){
		MSGMAN_GetString( wk->msg_man, mes_pokelist_04_66, wk->msg_buf );
		CLACT_SetDrawFlag( wk->act_work[PLIST_ACT_CB1+wk->pos], 1 );
	}else{
		MSGMAN_GetString( wk->msg_man, mes_pokelist_04_67, wk->msg_buf );
		wk->pos = PL_SEL_POS_EXIT;
	}

	PokeListLargeMsgPut( wk, PL_MSG_COMP_EXPAND, 1 );
	wk->dat->ret_mode = PL_RET_NORMAL;
	wk->next_seq = SEQ_ENDTRG_WAIT;
	*seq = SEQ_MSG_WAIT;
*/
	*seq = PLIST_MenuKapselSet( wk );
}

int PLIST_MenuKapselSet( PLIST_WORK * wk )
{
	POKEMON_PARAM * pp = PokeParty_GetMemberPointer( wk->dat->pp, wk->pos );

	if( PokeParaGet( pp, ID_PARA_cb_id, NULL ) == 0 ){
		MSGMAN_GetString( wk->msg_man, mes_pokelist_04_66, wk->msg_buf );
		CLACT_SetDrawFlag( wk->act_work[PLIST_ACT_CB1+wk->pos], 1 );
	}else{
		MSGMAN_GetString( wk->msg_man, mes_pokelist_04_67, wk->msg_buf );
		wk->pos = PL_SEL_POS_EXIT;
	}

	PokeListLargeMsgPut( wk, PL_MSG_COMP_EXPAND, 1 );
	wk->dat->ret_mode = PL_RET_NORMAL;
	wk->next_seq = SEQ_ENDTRG_WAIT;
	return SEQ_MSG_WAIT;
}


//--------------------------------------------------------------------------------------------
/**
 * 技
 *
 */
//--------------------------------------------------------------------------------------------
static void Menu_Skill( PLIST_WORK * wk, int * seq )
{
	SKILLCHECK_FUNC	check;
	u32	ret;
	u32	msg;

	check = (SKILLCHECK_FUNC)FieldSkill_FuncGet(
					FIELDSKILL_PRM_CHECKFUNC, wk->dat->ret_mode-PL_RET_IAIGIRI );

	if( check != NULL ){
		ret = check( wk->dat->scwk );
	}else{
		ret = FIELDSKILL_USE_FALSE;
	}

	switch( ret ){
	case FIELDSKILL_USE_TRUE:
		BmpMenuExit( wk->mw, NULL );
		BMP_MENULIST_Delete( wk->md );
		*seq = SEQ_OUT_SET;
		return;

	case FIELDSKILL_USE_FALSE:
		msg = mes_pokelist_04_44;
		break;

	case FIELDSKILL_NO_BADGE:
		msg = mes_pokelist_04_26;
		break;

	case FIELDSKILL_COMPANION:
		msg = mes_pokelist_09_01;
		break;

	case FIELDSKILL_PLAYER_SWIM:
		msg = mes_pokelist_04_42;
		break;
	}

	BmpTalkWinClear( &wk->win[WIN_M_MSG], WINDOW_TRANS_OFF );
	PokeListMenuExit( wk );
	PokeListLargeMsgPut( wk, msg, 1 );
	wk->next_seq = SEQ_MENUWAZA_ERR;
	*seq = SEQ_MSG_WAIT;
}

static void Menu_Iaigiri( PLIST_WORK * wk, int * seq )
{
	wk->dat->ret_mode = PL_RET_IAIGIRI;
	Menu_Skill( wk, seq );
}
static void Menu_Iwakudaki( PLIST_WORK * wk, int * seq )
{
	wk->dat->ret_mode = PL_RET_IWAKUDAKI;
	Menu_Skill( wk, seq );
}
static void Menu_Kairiki( PLIST_WORK * wk, int * seq )
{
	wk->dat->ret_mode = PL_RET_KAIRIKI;
	Menu_Skill( wk, seq );
}
static void Menu_Naminori( PLIST_WORK * wk, int * seq )
{
	wk->dat->ret_mode = PL_RET_NAMINORI;
	Menu_Skill( wk, seq );
}
static void Menu_Kiribarai( PLIST_WORK * wk, int * seq )
{
	wk->dat->ret_mode = PL_RET_KIRIBARAI;
	Menu_Skill( wk, seq );
}
static void Menu_RockClimb( PLIST_WORK * wk, int * seq )
{
	wk->dat->ret_mode = PL_RET_ROCKCLIMB;
	Menu_Skill( wk, seq );
}
static void Menu_Sorawotobu( PLIST_WORK * wk, int * seq )
{
	wk->dat->ret_mode = PL_RET_SORAWOTOBU;
	Menu_Skill( wk, seq );
}
static void Menu_Takinobori( PLIST_WORK * wk, int * seq )
{
	wk->dat->ret_mode = PL_RET_TAKINOBORI;
	Menu_Skill( wk, seq );
}
static void Menu_Flash( PLIST_WORK * wk, int * seq )
{
	wk->dat->ret_mode = PL_RET_FLASH;
	Menu_Skill( wk, seq );
}
static void Menu_Teleport( PLIST_WORK * wk, int * seq )
{
	wk->dat->ret_mode = PL_RET_TELEPORT;
	Menu_Skill( wk, seq );
}
static void Menu_Anawohoru( PLIST_WORK * wk, int * seq )
{
	wk->dat->ret_mode = PL_RET_ANAWOHORU;
	Menu_Skill( wk, seq );
}
static void Menu_Amaikaori( PLIST_WORK * wk, int * seq )
{
	wk->dat->ret_mode = PL_RET_AMAIKAORI;
	Menu_Skill( wk, seq );
}
static void Menu_Osyaberi( PLIST_WORK * wk, int * seq )
{
	wk->dat->ret_mode = PL_RET_OSYABERI;
	Menu_Skill( wk, seq );
}

//--------------------------------------------------------------------------------------------
/**
 * ミルクのみ（タマゴうみ）
 *
 * @param	wk
 * @param	seq
 *
 * @return	none
 *
 *	tmp[0] : 回復量
 *	tmp[1] : シーケンス
 *	tmp[2] : 実際の回復量
 *	tmp[3] : ポケモンリスト内の技番号
 */
//--------------------------------------------------------------------------------------------
static void Menu_MilkNomi( PLIST_WORK * wk, int * seq )
{
	*seq = Menu_MilkNomiInit( wk );
	if( *seq == SEQ_MILKNOMI ){
		wk->tmp[3] = PL_RET_MILKNOMI - PL_RET_IAIGIRI;
	}
}

static void Menu_TamagoUmi( PLIST_WORK * wk, int * seq )
{
	*seq = Menu_MilkNomiInit( wk );
	if( *seq == SEQ_MILKNOMI ){
		wk->tmp[3] = PL_RET_TAMAGOUMI - PL_RET_IAIGIRI;
	}
}

static int Menu_MilkNomiInit( PLIST_WORK * wk )
{
	BmpTalkWinClear( &wk->win[WIN_M_MSG], WINDOW_TRANS_OFF );
	PokeListMenuExit( wk );

	wk->tmp[0] = wk->panel[wk->pos].mhp / 5;	// 回復量
	// HPが1/5以下
	if( wk->panel[wk->pos].hp <= wk->tmp[0] ){
		PokeListLargeMsgPut( wk, mes_pokelist_04_71, 1 );
		wk->next_seq = SEQ_MENUWAZA_ERR;
		return SEQ_MSG_WAIT;
	}else{

		s16	x, y;

		wk->chg_flg = 1;
		wk->chg_pos = wk->pos;

		// ダミーカーソル表示
		CATS_ObjectPaletteSet( wk->act_work[PLIST_ACT_CURSOR1], 0 );
		CATS_ObjectPosGet( wk->act_work[PLIST_ACT_CURSOR1], &x, &y );
		CATS_ObjectPosSet( wk->act_work[PLIST_ACT_CURSOR2], x, y );
		CLACT_AnmChg(
			wk->act_work[PLIST_ACT_CURSOR2],
			PokeListSelCursorCheck( wk->dat->type, wk->chg_pos )+2 );
		CLACT_SetDrawFlag( wk->act_work[PLIST_ACT_CURSOR2], 1 );

		// プレートカラーチェンジ
		PokeListPanelPaletteSet( wk, wk->chg_pos );

		PokeListSmallMsgPut( wk, mes_pokelist_02_08, 1 );

		wk->tmp[1] = 0;
		return SEQ_MILKNOMI;
	}
}




int PokeList_MenuWazaError( PLIST_WORK * wk )
{
	if( sys.trg & (PAD_BUTTON_DECIDE|PAD_BUTTON_CANCEL) ){
		BmpTalkWinClear( &wk->win[WIN_L_MSG], WINDOW_TRANS_OFF );
		PokeListSmallMsgPut( wk, mes_pokelist_02_01, 1 );
		CATS_ObjectPaletteSet( wk->act_work[PLIST_ACT_CURSOR1], 0 );
		return SEQ_MAIN;
	}
	return SEQ_MENUWAZA_ERR;
}
