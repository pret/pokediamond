//============================================================================================
/**
 * @file	boxv_party.c
 * @brief	ボックス操作画面　描画下請け（手持ちトレイ）
 * @author	taya
 * @date	2005.10.19
 */
//============================================================================================
#include  "common.h"
#include  "system\arc_util.h"
#include  "system\clact_util.h"
#include  "poketool\pokeparty.h"

#include  "box_arc.h"

#include  "box_view.h"
#include  "box_common.h"

//==============================================================
// consts
//==============================================================
enum {
	PTRAY_SCRN_WIDTH = 15,
	PTRAY_SCRN_HEIGHT = 26,

	PTRAY_WRITE_XPOS_NORMAL = 14,
	PTRAY_WRITE_XPOS_COMPARE = 9,

	LCD_SCRN_HEIGHT = 24,

	PTRAY_SCRN_OUTSIZE = PTRAY_SCRN_HEIGHT-LCD_SCRN_HEIGHT,	// 画面外に出る部分

	// スクロール速度（キャラ単位）
	TRAY_SCROLL_SPEED = BOX_EFF_SPEED(2),

	ICON_SCROLL_OFS = PTRAY_SCRN_HEIGHT * 8,
	ICON_DISP_BORDER_YPOS = (192+16) << FX32_SHIFT,


	ICON_CLOSEUP_MOVE_TIME = BOX_TIMER(4),

	LASTICON_CLSEUP_MOVE_TIME = BOX_TIMER(4),
//	ICON_CLOSEUP_
};

//==============================================================
// アイコン表示位置テーブル
//==============================================================
static const struct {
	u16 x;
	u16 y;
}IconPosTbl[] = {
	{ PARTYICON_1ST_XPOS, PARTYICON_1ST_YPOS },
	{ PARTYICON_2ND_XPOS, PARTYICON_2ND_YPOS },
	{ PARTYICON_3RD_XPOS, PARTYICON_3RD_YPOS },
	{ PARTYICON_4TH_XPOS, PARTYICON_4TH_YPOS },
	{ PARTYICON_5TH_XPOS, PARTYICON_5TH_YPOS },
	{ PARTYICON_6TH_XPOS, PARTYICON_6TH_YPOS },
};

//==============================================================
// Prototype
//==============================================================
static void TrayOpenTask( TCB_PTR tcb, void* wk_adrs );
static void TrayCloseTask( TCB_PTR tcb, void* wk_adrs );
static void IconCloseupTask(TCB_PTR tcb, void* wk_adrs);
static void LastIconCloseupTask( TCB_PTR tcb, void* wk_adrs );
static void TrayScrnWrite( PARTY_VIEW_WORK* wk, u32 pos );
static void SetupCloseupMovePos( PARTY_VIEW_WORK* wk, VecFx32* vec );
static void IconMoveScroll( PARTY_VIEW_WORK* wk, fx32 val );
static void IconAllSet( PARTY_VIEW_WORK* wk, BOOL disp_flag);
static void IconAllDelete( PARTY_VIEW_WORK* wk );


//==============================================================================================================
// メインモジュールから呼ばれる初期化・終了関連
//==============================================================================================================

//------------------------------------------------------------------
/**
 * 初期化処理
 *
 * @param   wk			ワークポインタ
 * @param   vwk			
 * @param   vpara		
 * @param   actsys		
 *
 * @retval  BOOL		
 */
//------------------------------------------------------------------
BOOL BoxAppView_PartyInit( PARTY_VIEW_WORK* wk, BOXAPP_VIEW_WORK* vwk, const BOXAPP_VPARAM* vpara, GF_BGL_INI* bgl, CLACT_SET_PTR actsys )
{
	wk->vwk = vwk;
	wk->vpara = vpara;
	wk->actsys = actsys;
	wk->bgl = bgl;
	wk->iconsys = BoxAppView_GetIconSysWork( vwk );
	wk->trayWork = BoxAppView_GetTrayViewWork( vwk );

	if( BoxAppVPara_GetBoxMode(vpara)!=BOX_MODE_COMPARE )
	{
		wk->scrnWriteXpos = PTRAY_WRITE_XPOS_NORMAL;
		wk->iconXofs = 0;
	}
	else
	{
		wk->scrnWriteXpos = PTRAY_WRITE_XPOS_COMPARE;
		wk->iconXofs = (PTRAY_WRITE_XPOS_COMPARE - PTRAY_WRITE_XPOS_NORMAL) * 8;
	}

	wk->tray_viewpos = 0;
	wk->tray_taskflag = FALSE;

	BoxAppView_IconWorkInit( wk->iconsys, wk->icon, TEMOTI_POKEMAX );

	wk->icon_move_work = sys_AllocMemory( HEAPID_BOX_VIEW, sizeof(VecFx32)*TEMOTI_POKEMAX*ICON_CLOSEUP_MOVE_TIME );
	wk->scrnBuf = ArcUtil_ScrnDataGet( ARC_BOX_GRA, NARC_box_bg1_party_lz_nscr, TRUE, &(wk->scrnData), HEAPID_BOX_VIEW );

	if(	(wk->scrnBuf == NULL)
	||	(wk->icon_move_work == NULL)
	){
		return FALSE;
	}

	SetupCloseupMovePos( wk, wk->icon_move_work );

	return TRUE;
}
//------------------------------------------------------------------
/**
 * 終了処理
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
void BoxAppView_PartyQuit( PARTY_VIEW_WORK* wk )
{
	if( wk->scrnBuf )
	{
		sys_FreeMemoryEz( wk->scrnBuf );
	}
	if( wk->icon_move_work != NULL )
	{
		sys_FreeMemoryEz( wk->icon_move_work );
	}
	IconAllDelete( wk );
}

//==============================================================================================================
// メインモジュールから呼ばれるコマンド処理関数群
//==============================================================================================================


//------------------------------------------------------------------
/**
 * 手持ちトレイ全描画
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
void BoxAppView_PartyDisp( PARTY_VIEW_WORK* wk )
{
	wk->tray_viewpos = 0;
	TrayScrnWrite( wk, wk->tray_viewpos );
	IconAllSet( wk, TRUE );
	GF_BGL_LoadScreenReq( wk->bgl, FRM_MAIN_STATUS );
}
//------------------------------------------------------------------
/**
 * 手持ちトレイ開くアクション開始
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
void BoxAppView_PartyOpenStart( PARTY_VIEW_WORK* wk )
{
	IconAllSet( wk, FALSE );

	wk->tray_viewpos = PTRAY_SCRN_HEIGHT;
	wk->tray_taskflag = (BoxAppView_VTaskAdd( TrayOpenTask, wk, TASKPRI_V_SUB ) != NULL);
}
//------------------------------------------------------------------
/**
 * 手持ちトレイ開くアクション終了待ち
 *
 * @param   wk		ワークポインタ
 *
 * @retval  BOOL		TRUEで終了
 */
//------------------------------------------------------------------
BOOL BoxAppView_PartyOpenWait( PARTY_VIEW_WORK* wk )
{
	return wk->tray_taskflag == FALSE;
}
//------------------------------------------------------------------
/**
 * 手持ちトレイ開くアクションのタスク
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void TrayOpenTask( TCB_PTR tcb, void* wk_adrs )
{
	PARTY_VIEW_WORK* wk = (PARTY_VIEW_WORK*)wk_adrs;
	fx32  icon_move_len;

	if( wk->tray_viewpos > TRAY_SCROLL_SPEED )
	{
		icon_move_len = -((TRAY_SCROLL_SPEED * 8) << FX32_SHIFT);
		wk->tray_viewpos -= TRAY_SCROLL_SPEED;
	}
	else
	{
		icon_move_len = -((wk->tray_viewpos * 8) << FX32_SHIFT);
		wk->tray_viewpos = 0;
	}

	TrayScrnWrite( wk, wk->tray_viewpos );
	GF_BGL_LoadScreenReq( wk->bgl, FRM_MAIN_STATUS );

	IconMoveScroll( wk, icon_move_len );

	if( wk->tray_viewpos == 0 )
	{
		wk->tray_taskflag = FALSE;
		TCB_Delete(tcb);
	}
}
//------------------------------------------------------------------
/**
 * 手持ちトレイ閉じるアクション開始
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
void BoxAppView_PartyCloseStart( PARTY_VIEW_WORK* wk )
{
	wk->tray_taskflag = (BoxAppView_VTaskAdd( TrayCloseTask, wk, TASKPRI_V_SUB ) != NULL);
}
//------------------------------------------------------------------
/**
 * 手持ちトレイ閉じるアクション終了待ち
 *
 * @param   wk		ワークポインタ
 *
 * @retval  BOOL		TRUEで終了
 */
//------------------------------------------------------------------
BOOL BoxAppView_PartyCloseWait( PARTY_VIEW_WORK* wk )
{
	if( wk->tray_taskflag == FALSE )
	{
		IconAllDelete( wk );
		return TRUE;
	}
	return FALSE;
}
//------------------------------------------------------------------
/**
 * 手持ちトレイ閉じるアクションのタスク
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void TrayCloseTask( TCB_PTR tcb, void* wk_adrs )
{
	PARTY_VIEW_WORK* wk = (PARTY_VIEW_WORK*)wk_adrs;
	fx32  icon_move_len;

	if( wk->tray_viewpos < (PTRAY_SCRN_HEIGHT-TRAY_SCROLL_SPEED) )
	{
		icon_move_len = ((TRAY_SCROLL_SPEED * 8) << FX32_SHIFT);
		wk->tray_viewpos += TRAY_SCROLL_SPEED;
	}
	else
	{
		icon_move_len = ((PTRAY_SCRN_HEIGHT - wk->tray_viewpos) * 8) << FX32_SHIFT;
		wk->tray_viewpos = PTRAY_SCRN_HEIGHT;
	}

	if( wk->tray_viewpos > PTRAY_SCRN_OUTSIZE )
	{
		u32  ypos, clear_len;

		clear_len = (u32)((icon_move_len) >> FX32_SHIFT) / 8;
		ypos = wk->tray_viewpos - PTRAY_SCRN_OUTSIZE - clear_len;

		GF_BGL_ScrFill( wk->bgl, FRM_MAIN_STATUS, 0x0000, wk->scrnWriteXpos, ypos, PTRAY_SCRN_WIDTH, clear_len, GF_BGL_SCRWRT_PALIN );
	}
//	GF_BGL_ScrFill( GF_BGL_INI * ini, u8 frmnum, u16 dat, u8 px, u8 py, u8 sx, u8 sy, u8 mode )
	TrayScrnWrite( wk, wk->tray_viewpos );
	GF_BGL_LoadScreenReq( wk->bgl, FRM_MAIN_STATUS );

	IconMoveScroll( wk, icon_move_len );

	if( wk->tray_viewpos == PTRAY_SCRN_HEIGHT )
	{
		wk->tray_taskflag = FALSE;
		TCB_Delete(tcb);
	}
}

//------------------------------------------------------------------
/**
 * 手持ちトレイアイコンの空き詰め動作開始
 * ※最後尾以外のポケモンを「つかむ」で持って行かれた時に使用
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
void BoxAppView_PartyIconCloseupStart( PARTY_VIEW_WORK* wk )
{
	int pokecnt = PokeParty_GetPokeCount( wk->vpara->partyData );

	if( wk->icon_closeup_poke_pos < pokecnt )
	{
		int  i, move_icon_cnt;

		move_icon_cnt = pokecnt - wk->icon_closeup_poke_pos;

		for(i=wk->icon_closeup_poke_pos; i<(TEMOTI_POKEMAX-1); i++)
		{
			BoxAppView_IconWorkCopy( &(wk->icon[i+1]), &(wk->icon[i]), 1 );
			BoxAppView_IconWorkInit( wk->iconsys,  &(wk->icon[i+1]), 1 );
			if( wk->icon[i].act != NULL )
			{
				BoxAppView_Icon_ResetImageBank( wk->iconsys, &(wk->icon[i]), OBJCHAR_PARTY_ICON_POS+OBJCHAR_TRAYICON_SIZE*i );
			}
		}
		wk->icon_closeup_poke_cnt = move_icon_cnt;
		wk->icon_closeup_time = 0;

		wk->tray_taskflag = (BoxAppView_VTaskAdd( IconCloseupTask, wk, TASKPRI_V_SUB ) != NULL);
	}
	else
	{
		wk->tray_taskflag = FALSE;
	}
}
//------------------------------------------------------------------
/**
 * 手持ちトレイアイコンの空き詰め動作タスク
 * ※最後尾以外のポケモンを「つかむ」で持って行かれた時に使用
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void IconCloseupTask(TCB_PTR tcb, void* wk_adrs)
{
	PARTY_VIEW_WORK* wk;
	VecFx32* vec;
	int p, i, cnt;


	wk = (PARTY_VIEW_WORK*)wk_adrs;
	p = wk->icon_closeup_poke_pos;
	cnt = wk->icon_closeup_poke_cnt;

	vec = ((VecFx32*)(wk->icon_move_work)) + ((p*ICON_CLOSEUP_MOVE_TIME) + wk->icon_closeup_time);
	for(i=0; i<cnt; i++)
	{
		if( wk->icon[p].act != NULL )
		{
			CLACT_SetMatrix( wk->icon[p].act, vec );
		}
		p++;
		vec += ICON_CLOSEUP_MOVE_TIME;
	}


	if( ++(wk->icon_closeup_time) >= ICON_CLOSEUP_MOVE_TIME )
	{
		wk->tray_taskflag = FALSE;
		TCB_Delete(tcb);
	}
}
//------------------------------------------------------------------
/**
 * 手持ちトレイアイコンの空き詰め動作終了待ち
 * ※最後尾以外のポケモンを「つかむ」で持って行かれた時に使用
 *
 * @param   wk			ワークポインタ
 *
 * @retval  BOOL		TRUEで終了
 */
//------------------------------------------------------------------
BOOL BoxAppView_PartyIconCloseupWait( PARTY_VIEW_WORK* wk )
{
	return (wk->tray_taskflag == FALSE);
}


//------------------------------------------------------------------
/**
 * 手持ちトレイ最後尾に置かれたアイコンの空き詰め動作開始
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
void BoxAppView_PartyLastIconCloseupStart( PARTY_VIEW_WORK* wk )
{
	u32  prim_pos = PokeParty_GetPokeCount( wk->vpara->partyData ) - 1;

	if( wk->icon_closeup_poke_pos > prim_pos )
	{
		VecFx32  vec;

		vec = *CLACT_GetMatrix( wk->icon[prim_pos].act );
		wk->icon_add_x = (((IconPosTbl[prim_pos].x + wk->iconXofs) << FX32_SHIFT) - vec.x) / LASTICON_CLSEUP_MOVE_TIME;
		wk->icon_add_y = ((IconPosTbl[prim_pos].y << FX32_SHIFT) - vec.y) / LASTICON_CLSEUP_MOVE_TIME;
		wk->icon_closeup_time = 0;

		wk->icon_closeup_poke_pos = prim_pos;
		wk->tray_taskflag = (BoxAppView_VTaskAdd( LastIconCloseupTask, wk, TASKPRI_V_SUB ) != NULL);
	}
	else
	{
		wk->tray_taskflag = FALSE;
	}
}
//------------------------------------------------------------------
/**
 * 手持ちトレイ最後尾に置かれたアイコンの空き詰め動作開始
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
BOOL BoxAppView_PartyLastIconCloseupWait( PARTY_VIEW_WORK* wk )
{
	return (wk->tray_taskflag == FALSE);
}
//------------------------------------------------------------------
/**
 * 手持ちトレイ最後尾に置かれたアイコンの空き詰め動作タスク
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void LastIconCloseupTask( TCB_PTR tcb, void* wk_adrs )
{
	PARTY_VIEW_WORK* wk;
	VecFx32 vec;
	BOOL  endflag;

	wk = (PARTY_VIEW_WORK*)wk_adrs;
	vec = *CLACT_GetMatrix( wk->icon[wk->icon_closeup_poke_pos].act );

	if( ++(wk->icon_closeup_time) >= ICON_CLOSEUP_MOVE_TIME )
	{
		vec.x = (IconPosTbl[wk->icon_closeup_poke_pos].x + wk->iconXofs) << FX32_SHIFT;
		vec.y = IconPosTbl[wk->icon_closeup_poke_pos].y << FX32_SHIFT;
		endflag = TRUE;
	}
	else
	{
		vec.x += wk->icon_add_x;
		vec.y += wk->icon_add_y;
		endflag = FALSE;
	}

	CLACT_SetMatrix( wk->icon[wk->icon_closeup_poke_pos].act, &vec );

	if( endflag )
	{
		wk->tray_taskflag = FALSE;
		TCB_Delete(tcb);
	}
}

//------------------------------------------------------------------
/**
 * 指しているアイコンデータをボックスに預ける
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
void BoxAppView_PartyPointIconAzuke( PARTY_VIEW_WORK* wk )
{
	u32 pos;

	// 現在表示中のトレイに預ける場合はアイコン表示を更新
	if( wk->vpara->azukeruTrayNumber == BoxAppVPara_GetTrayBoxNumber( wk->vpara ) )
	{
		BoxAppView_TrayUpdateIcon( wk->trayWork );
	}

	// 指しているアイコンはただ消すだけ
	pos = BoxAppVPara_GetCursorPartyPos( wk->vpara );
	BoxAppView_IconWorkQuit( wk->iconsys, &wk->icon[pos], 1 );

	// 空き詰め動作用パラメータとして保持
	wk->icon_closeup_poke_pos = pos;
}


//------------------------------------------------------------------------------
/**
 * 指定位置のアイコン逃がす処理開始
 *
 * @param   wk			トレイ描画ワーク
 * @param   pos			アイコン位置
 *
 */
//------------------------------------------------------------------------------
void BoxAppView_PartyIconReleaseStart( PARTY_VIEW_WORK* wk, u32 pos )
{
	wk->mvseq = 0;
	wk->icon_closeup_poke_pos = pos;
	BoxAppView_IconAnmStart( wk->iconsys, &(wk->icon[pos]), ICON_ANM_RELEASE );

}
//------------------------------------------------------------------------------
/**
 * 指定位置のアイコン逃がす処理終了待ち
 *
 * @param   wk		ワークポインタ
 *
 * @retval  BOOL	TRUEで終了
 */
//------------------------------------------------------------------------------
BOOL BoxAppView_PartyIconReleaseWait( PARTY_VIEW_WORK* wk )
{
	BOX_ICON_WORK*  icon = &(wk->icon[wk->icon_closeup_poke_pos]);

	switch( wk->mvseq ){
	case 0:
		if( BoxAppView_IconAnmWait( wk->iconsys, icon ) )
		{
			const BOXAPP_WORK* mainWk = BoxAppView_GetMainWork( wk->vwk );

			if( BoxApp_ReleaseWazaCheckDone( mainWk ) )
			{
				if( BoxApp_ReleaseWazaCheckOK( mainWk ) )
				{
					BoxAppView_IconWorkQuit( wk->iconsys, icon, 1 );
					return TRUE;
				}
				else
				{
					BoxAppView_IconAnmStart( wk->iconsys, icon, ICON_ANM_COMEBACK );
					wk->mvseq++;
				}
			}
		}
		break;

	case 1:
		if( BoxAppView_IconAnmWait( wk->iconsys, icon ) )
		{
			return TRUE;
		}
		break;
	}
	return FALSE;
}


//------------------------------------------------------------------
/**
 * アイコンを絞り込みモード表示に対応
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
void BoxAppView_PartyIconLimitModeSet( PARTY_VIEW_WORK* wk )
{
	if( BoxAppVPara_GetCursorArea(wk->vpara) == CURSOR_AREA_PARTY )
	{
		u32 limitBit;
		int i;

		limitBit = BoxAppVPara_GetLimitModeBitFlag( wk->vpara );

		for(i=0; i<TEMOTI_POKEMAX; i++)
		{
			if( wk->icon[i].act != NULL )
			{
				BoxAppView_IconLimitModeSet( wk->iconsys, &(wk->icon[i]), limitBit );
			}
		}
	}
}
//------------------------------------------------------------------
/**
 * アイコンのアイテム情報を更新
 *
 * @param   wk			ワークポインタ
 * @param   pos			アイコン位置
 * @param   itemNumber	アイテムナンバー
 */
//------------------------------------------------------------------
void BoxAppView_PartyIconUpdateItem( PARTY_VIEW_WORK* wk, u32 pos, u32 itemNumber )
{
	if( wk->icon[pos].act != NULL )
	{
		BoxAppView_IconItemNumberSet( wk->iconsys, &wk->icon[pos], itemNumber );
		BoxAppView_IconLimitModeSet( wk->iconsys, &wk->icon[pos], BoxAppVPara_GetLimitModeBitFlag(wk->vpara) );
	}

}


//------------------------------------------------------------------
/**
 * ポイントしているアイコンマーキングビットフラグ（内部ステータス）を書き換え
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
void BoxAppView_PartyIconMarkUpdate( PARTY_VIEW_WORK* wk )
{
	u32 pos, markBit;

	pos = BoxAppVPara_GetCursorPartyPos( wk->vpara );
	markBit = BoxAppVPara_GetStatusPokeMarkBit( wk->vpara );

	if( wk->icon[pos].act != NULL )
	{
		BoxAppView_IconMarkBitSet( wk->iconsys, &(wk->icon[pos]), markBit );
	}
}


//==============================================================================================================
// 他下請けモジュールから呼ばれる関数群
//==============================================================================================================

//------------------------------------------------------------------
/**
 * 手持ちトレイ内の指定位置アイコンデータをバッファに引き渡す
 *
 * @param   wk		ワークポインタ
 * @param   pos		トレイ内の位置
 * @param   charpos	キャラデータ転送先（領域先頭からのキャラ単位オフセット）
 * @param   dst		アイコンデータ移動先
 *
 */
//------------------------------------------------------------------
void BoxAppView_PartyMoveIconData( PARTY_VIEW_WORK* wk, u32 pos, u32 charpos, BOX_ICON_WORK* dst )
{
	BoxAppView_IconWorkCopy( &wk->icon[pos], dst, 1 );
	BoxAppView_Icon_ResetImageBank( wk->iconsys, dst, charpos );
	BoxAppView_IconWorkInit( wk->iconsys, &wk->icon[pos], 1 );

	// 空き詰め動作用パラメータとして保持
	wk->icon_closeup_poke_pos = pos;
}
//------------------------------------------------------------------
/**
 * アイコンデータを空いている最後尾のバッファに受け取る
 *
 * @param   wk			
 * @param   cursor_pos	
 * @param   dst			
 *
 */
//------------------------------------------------------------------
void BoxAppView_PartyAddIconData( PARTY_VIEW_WORK* wk, u32 cursor_pos, const BOX_ICON_WORK* srcIcon )
{
	u32 iconpos;
	u32 charpos;
	BOX_ICON_WORK* dstIcon;


	// 本来のアイコン位置
	iconpos = PokeParty_GetPokeCount( wk->vpara->partyData ) - 1;

	charpos = OBJCHAR_PARTY_ICON_POS+OBJCHAR_TRAYICON_SIZE*iconpos;
	dstIcon = &wk->icon[iconpos];
	BoxAppView_IconWorkCopy( srcIcon, dstIcon, 1 );
	BoxAppView_Icon_ResetImageBank( wk->iconsys, dstIcon, charpos );
	CLACT_BGPriorityChg( dstIcon->act, BGPRI_PARTY_ICON );
	BoxAppView_ChangeDrawPriority( dstIcon->act, ACTPRI_PARTY_ICON_MIN+iconpos );

	// カーソル位置は空き詰め動作用パラメータとして保持
	wk->icon_closeup_poke_pos = cursor_pos;
}
//------------------------------------------------------------------
/**
 * アイコンデータを指定位置のバッファに受け取る
 *
 * @param   wk			
 * @param   cursor_pos	
 * @param   dst			
 *
 */
//------------------------------------------------------------------
void BoxAppView_PartySetIconData( PARTY_VIEW_WORK* wk, u32 cursor_pos, const BOX_ICON_WORK* srcIcon )
{
	u32 iconpos;
	u32 charpos;
	BOX_ICON_WORK* dstIcon;

	// 本来のアイコン位置
	iconpos = cursor_pos;

	charpos = OBJCHAR_PARTY_ICON_POS+OBJCHAR_TRAYICON_SIZE*iconpos;
	dstIcon = &wk->icon[iconpos];
	BoxAppView_IconWorkCopy( srcIcon, dstIcon, 1 );
	BoxAppView_Icon_ResetImageBank( wk->iconsys, dstIcon, charpos );
	CLACT_BGPriorityChg( dstIcon->act, BGPRI_PARTY_ICON );
	BoxAppView_ChangeDrawPriority( dstIcon->act, ACTPRI_PARTY_ICON_MIN+iconpos );

	// カーソル位置は空き詰め動作用パラメータとして保持
	wk->icon_closeup_poke_pos = cursor_pos;
}
//------------------------------------------------------------------
/**
 * アイコンデータポインタを返す
 *
 * @param   wk		ワークポインタ
 * @param   pos		位置指定
 *
 * @retval  BOX_ICON_WORK*  アイコンデータポインタ
 */
//------------------------------------------------------------------
BOX_ICON_WORK* BoxAppView_PartyGetIconData( PARTY_VIEW_WORK* wk, u32 pos )
{
	GF_ASSERT(pos < TEMOTI_POKEMAX);
	return &wk->icon[pos];
}

//------------------------------------------------------------------
/**
 * 手持ちトレイアイコンの表示位置（トレイが完全にオープンした状態での）を取得
 *
 * @param   wk			[in]  ワークポインタ
 * @param   pos			[in]  何体目の表示位置か
 * @param   x			[out] Ｘ座標を受け取る変数へのポインタ
 * @param   y			[out] Ｙ座標を受け取る変数へのポインタ
 *
 */
//------------------------------------------------------------------
void BoxAppView_PartyGetIconDispPos( PARTY_VIEW_WORK* wk, u32 pos, s32* x, s32* y )
{
	if( pos == CURSOR_PARTYTRAY_CLOSEBUTTON_POS )
	{
		*x = PARTYTRAY_CLOSEBUTTON_XPOS + wk->iconXofs;
		*y = PARTYTRAY_CLOSEBUTTON_YPOS;
	}
	else
	{
		*x = IconPosTbl[pos].x + wk->iconXofs;
		*y = IconPosTbl[pos].y;
	}
}



//==============================================================================================================
// ローカル関数群
//==============================================================================================================

//------------------------------------------------------------------
/**
 * トレイスクリーン描画
 *
 * @param   wk		ワークポインタ
 * @param   pos		描画段階
 *
 */
//------------------------------------------------------------------
static void TrayScrnWrite( PARTY_VIEW_WORK* wk, u32 pos )
{
	u32 ofs, len, writepos;

	if( pos <= PTRAY_SCRN_OUTSIZE )
	{
		ofs = ((PTRAY_SCRN_OUTSIZE - pos) * PTRAY_SCRN_WIDTH)*2;
		len = LCD_SCRN_HEIGHT;
		writepos = 0;
	}
	else
	{
		if( pos >= PTRAY_SCRN_HEIGHT )
		{
			return;
		}
		ofs = 0;
		len = PTRAY_SCRN_HEIGHT - pos;
		writepos = LCD_SCRN_HEIGHT - len;
	}

	GF_BGL_ScrWrite( wk->bgl, FRM_MAIN_STATUS, ((u8*)wk->scrnData->rawData) + ofs, 
		wk->scrnWriteXpos, writepos, PTRAY_SCRN_WIDTH, len );

}
//------------------------------------------------------------------
/**
 * 手持ちトレイアイコンの空き詰め動作テーブル作成
 *
 * @param   vec				動作テーブル作成先
 *
 */
//------------------------------------------------------------------
static void SetupCloseupMovePos( PARTY_VIEW_WORK* wk, VecFx32* vec )
{
	fx32  xadd, yadd;
	u32 i, f, p;

	p = 0;

	for(i=0; i<(TEMOTI_POKEMAX-1); i++)
	{
		xadd = ((IconPosTbl[i].x - IconPosTbl[i+1].x) * FX32_ONE) / ICON_CLOSEUP_MOVE_TIME;
		yadd = ((IconPosTbl[i].y - IconPosTbl[i+1].y) * FX32_ONE) / ICON_CLOSEUP_MOVE_TIME;
		for(f=0; f<(ICON_CLOSEUP_MOVE_TIME-1); f++)
		{
			vec[f].x = ((IconPosTbl[i+1].x + wk->iconXofs) * FX32_ONE) + (xadd * (f+1));
			vec[f].y = (IconPosTbl[i+1].y * FX32_ONE) + (yadd * (f+1));
			vec[f].z = 0;
		}
		vec[f].x = ((IconPosTbl[i].x + wk->iconXofs) * FX32_ONE);
		vec[f].y = (IconPosTbl[i].y * FX32_ONE);
		vec[f].z = 0;

		vec += ICON_CLOSEUP_MOVE_TIME;
	}
}
//------------------------------------------------------------------
/**
 * トレイ上のアイコン全スクロール（開く・閉じるアクション用）
 *
 * @param   wk		ワークポインタ
 * @param   val		スクロール量
 *
 */
//------------------------------------------------------------------
static void IconMoveScroll( PARTY_VIEW_WORK* wk, fx32 val )
{
	VecFx32  vec;
	int i;

	for(i=0; i<TEMOTI_POKEMAX; i++)
	{
		if( wk->icon[i].act != NULL )
		{
			vec = *CLACT_GetMatrix( wk->icon[i].act );
			vec.y += val;
			CLACT_SetMatrix( wk->icon[i].act, &vec );

			if( val < 0 )
			{
				if( vec.y < ICON_DISP_BORDER_YPOS )
				{
					CLACT_SetDrawFlag( wk->icon[i].act, TRUE );
				}
			}
			else
			{
				if( vec.y >= ICON_DISP_BORDER_YPOS )
				{
					CLACT_SetDrawFlag( wk->icon[i].act, FALSE );
//					BoxAppView_IconWorkQuit( wk->iconsys, &(wk->icon[i]), 1 );
				}
			}
		}
		else
		{
			break;
		}
	}
}
//------------------------------------------------------------------
/**
 * 手持ちポケアイコン全部作成
 *
 * @param   wk			ワークポインタ
 * @param   disp_flag	画面内に存在するか？（しなければ画面下に作成、Vanishする）
 *
 */
//------------------------------------------------------------------
static void IconAllSet( PARTY_VIEW_WORK* wk, BOOL disp_flag)
{
	POKEMON_PARAM* pp;
	int i, max, yofs;

	yofs = (disp_flag)? 0 : ICON_SCROLL_OFS;
	max = PokeParty_GetPokeCount( wk->vpara->partyData );

	for(i=0; i<max; i++)
	{
		pp = PokeParty_GetMemberPointer( wk->vpara->partyData, i );
		BoxAppView_IconAdd(	wk->iconsys, (POKEMON_PASO_PARAM*)pp,
							IconPosTbl[i].x+wk->iconXofs, IconPosTbl[i].y+yofs,
							BGPRI_PARTY_ICON, ACTPRI_PARTY_ICON_MIN + i, 
							OBJCHAR_PARTY_ICON_POS+OBJCHAR_TRAYICON_SIZE*i, &wk->icon[i] );
		CLACT_SetDrawFlag( wk->icon[i].act, disp_flag );
	}
}

//------------------------------------------------------------------
/**
 * 手持ちポケモンアイコン全削除
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
static void IconAllDelete( PARTY_VIEW_WORK* wk )
{
	int i, max;
	max = PokeParty_GetPokeCount( wk->vpara->partyData );

	for(i=0; i<max; i++)
	{
		if( wk->icon[i].act )
		{
			BoxAppView_IconWorkQuit( wk->iconsys, &(wk->icon[i]), 1 );
		}
	}

}
