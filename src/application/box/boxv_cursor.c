//============================================================================================
/**
 * @file	boxv_cursor.c
 * @brief	ボックス操作画面　描画下請け（トレイ関連）
 * @author	taya
 * @date	2005.09.09
 */
//============================================================================================
#include  "common.h"
#include  "system\arc_util.h"
#include  "system\clact_util.h"

#include  "box_arc.h"
#include  "box_view.h"
#include  "box_common.h"

//==============================================================
// consts
//==============================================================
enum {
	// 移動可能な範囲。超えたら逆から出てくる
	CURSOR_VISIBLE_X_MIN = 70,
	CURSOR_VISIBLE_X_MAX = 256 + 16,
	CURSOR_VISIBLE_Y_MIN = -24,			// 掴んでいるアイコンも完全に隠れるくらい
	CURSOR_VISIBLE_Y_MAX = 192 + 16,

	CURSOR_VISIBLE_X_MAX_FX32 = CURSOR_VISIBLE_X_MAX << FX32_SHIFT,
	CURSOR_VISIBLE_X_MIN_FX32 = CURSOR_VISIBLE_X_MIN << FX32_SHIFT,
	CURSOR_VISIBLE_Y_MAX_FX32 = CURSOR_VISIBLE_Y_MAX << FX32_SHIFT,
	CURSOR_VISIBLE_Y_MIN_FX32 = CURSOR_VISIBLE_Y_MIN << FX32_SHIFT,

	// 移動フレーム数
	CURSOR_MOVE_TIME = BOX_TIMER(3),		//< 通常時
	CURSOR_LOOP_MOVE_TIME = BOX_TIMER(6),	//< クルッと回って反対側から出てくる時

	// つかみ動作フレーム数
	CURSOR_CATCHMOVE_DOWN_TIME = BOX_TIMER(3),	// 下がるとき
	CURSOR_CATCHMOVE_UP_TIME = BOX_TIMER(3),	// 上がるとき
	CURSOR_CATCHMOVE_DIPTH = -(CURSOR_ICON_YDIFF - CURSOR_CATCHICON_YDIFF),		// 上下する深さ（ドット）


	// 入れ替え動作フレーム数
	CURSOR_SWAPMOVE_TIME = BOX_TIMER(6),
	CURSOR_SWAPMOVE_WIDTH = 12,	// 横にブワッと広がる幅（ドット）

	// ボタン押し動作
	PUSHMOVE_START_TIME = BOX_TIMER(2),
	PUSHMOVE_DOWN_TIME = BOX_TIMER(1),
	PUSHMOVE_RETURN_TIME = BOX_TIMER(2),
	PUSHMOVE_UP_RANGE = -2,
	PUSHMOVE_DOWN_RANGE = 6,
	PUSHMOVE_RETURN_RANGE = -(PUSHMOVE_UP_RANGE+PUSHMOVE_DOWN_RANGE),

	MOVE_SEQ_END = 255,

	CURSOR_SHADOW_DIFF = 24,

	// 矢印アクター表示位置
	ARROW_L_XPOS = 108,
	ARROW_R_XPOS = 236,
	ARROW_COMPAREMODE_OFS = -44,

	ARROW_YPOS = 20,
};

enum {
	ANM_NORMAL,
	ANM_PAR,
	ANM_GOO,
	ANM_PUSH_START,
	ANM_PUSH_END,

	ANM_SHADOW,
	ANM_ARROW_L_STOP,
	ANM_ARROW_R_STOP,
	ANM_ARROW_L_MOVE,
	ANM_ARROW_R_MOVE,
};

//==============================================================
// Prototype
//==============================================================
static void SetupCatchPokeObj( CURSOR_VIEW_WORK* wk );
static void CheckReverseMove( const CURSOR_VIEW_WORK* wk, BOOL* xflg, BOOL* yflg );
static void CursorMoveTask( TCB_PTR tcb, void* wk_adrs );
static void CursorCatchMoveTask( TCB_PTR tcb, void* wk_adrs );
static void CursorPutMoveTask(TCB_PTR tcb, void* wk_adrs );
static void SwapIconTaskAdd( CURSOR_VIEW_WORK* wk, CLACT_WORK_PTR act, fx32 end_y, s32 sindir, u32 nextpri );
static BOOL SwapIconMoveTaskEndCheck( CURSOR_VIEW_WORK* wk );
static void SwapIconWorkDeleteReserve( void* wk_adrs );
static void SwapIconMoveTask( TCB_PTR tcb, void* wk_adrs );
static void ButtonPushActionTask( TCB_PTR tcb, void* wk_adrs );
static void ButtonReleaseActionTask( TCB_PTR tcb, void* wk_adrs );
static void ItemCatchTask( TCB_PTR tcb, void* wk_adrs );
static void ItemSetTask( TCB_PTR tcb, void* wk_adrs );
static void ItemSwapTask( TCB_PTR tcb, void* wk_adrs );
static void GetCursorPosByVparam( s32* x, s32* y, u8* area, CURSOR_VIEW_WORK* wk );
static void CursorPosSet( CURSOR_VIEW_WORK* wk, VecFx32* vec );
static void PointIconDataToCatchIconData( CURSOR_VIEW_WORK* wk );
static void CatchIconDataEnable( CURSOR_VIEW_WORK* wk );
static void CatchIconDataPut( CURSOR_VIEW_WORK* wk );
static void CatchIconDataSwap( CURSOR_VIEW_WORK* wk );
static void CatchIconDataDisable( CURSOR_VIEW_WORK* wk );
static void CatchIconDataDelete( CURSOR_VIEW_WORK* wk );
static CLACT_WORK_PTR GetPointIconActor( CURSOR_VIEW_WORK* wk );


//------------------------------------------------------------------
/**
 * 初期化
 *
 * @param   wk		
 * @param   vwk		
 * @param   vpara		
 * @param   actsys		
 *
 * @retval  BOOL		TRUEで成功
 */
//------------------------------------------------------------------
BOOL BoxAppView_CursorInit( CURSOR_VIEW_WORK* wk, BOXAPP_VIEW_WORK* vwk, const BOXAPP_VPARAM* vpara, CLACT_SET_PTR actsys )
{
	wk->vwk = vwk;
	wk->vpara = vpara;
	wk->actsys = actsys;
	wk->trayWork = BoxAppView_GetTrayViewWork( vwk );
	wk->partyWork = BoxAppView_GetPartyViewWork ( vwk );
	wk->iconSys = BoxAppView_GetIconSysWork( vwk );

	wk->area = BoxAppVPara_GetCursorArea( vpara );
	wk->tray_xpos = BoxAppVPara_GetCursorTrayPosX( vpara );
	wk->tray_ypos = BoxAppVPara_GetCursorTrayPosY( vpara );
	wk->party_pos = BoxAppVPara_GetCursorPartyPos( vpara );


	wk->act = NULL;
	wk->shadow_act = NULL;
	wk->arrow_act_L = NULL;
	wk->arrow_act_R = NULL;
	wk->catch_icon_count = 0;
	wk->shadow_syncro_flag = TRUE;

	wk->cellBuf = ArcUtil_CellBankDataGet(ARC_BOX_GRA, NARC_box_m_hand_lz_ncer, TRUE, &(wk->cellBank), HEAPID_BOX_VIEW);
	wk->anmBuf = ArcUtil_AnimBankDataGet(ARC_BOX_GRA, NARC_box_m_hand_lz_nanr, TRUE, &(wk->anmBank), HEAPID_BOX_VIEW);

	if( wk->cellBuf == NULL || wk->anmBuf == NULL ){
		return FALSE;
	}

	return TRUE;
}

//--------------------------------------------------------------------------------------
/**
 * ＯＢＪセットアップ処理
 *
 * @param   wk		ワークポインタ
 *
 */
//--------------------------------------------------------------------------------------
void BoxAppView_CursorActSet( CURSOR_VIEW_WORK* wk )
{
	CLACT_HEADER  header;
	u32 area, mode;

	NNS_G2dInitImageProxy( &(wk->imgProxy) );
	ArcUtil_CharSysLoad( ARC_BOX_GRA, NARC_box_m_hand_lz_ncgr, TRUE, CHAR_MAP_1D, 0,
					NNS_G2D_VRAM_TYPE_2DMAIN, OBJCHAR_CURSOR_POS*0x20, HEAPID_BOX_VIEW, &(wk->imgProxy) );

	BoxAppView_SetActHeader( &header, &(wk->imgProxy), BoxAppView_GetObjPlttProxy( wk->vwk ), wk->cellBank, wk->anmBank,
					((wk->area == CURSOR_AREA_PARTY)? BGPRI_PARTY_ICON : BGPRI_TRAY_ICON ));
	GetCursorPosByVparam( &wk->xpos, &wk->ypos, &wk->area, wk );
	wk->act = BoxAppView_AddActor( wk->actsys, &header, wk->xpos, wk->ypos, ACTPRI_CURSOR, NNS_G2D_VRAM_TYPE_2DMAIN );
	wk->shadow_act = BoxAppView_AddActor( wk->actsys, &header, wk->xpos, wk->ypos+CURSOR_SHADOW_DIFF,
			ACTPRI_CURSOR_SHADOW, NNS_G2D_VRAM_TYPE_2DMAIN );


	area = BoxAppVPara_GetCursorArea( wk->vpara );
	mode = BoxAppVPara_GetBoxMode( wk->vpara );

	{
		int Lpos, Rpos;

		if( mode != BOX_MODE_COMPARE )
		{
			Lpos = ARROW_L_XPOS;
			Rpos = ARROW_R_XPOS;
		}
		else
		{
			Lpos = ARROW_L_XPOS + ARROW_COMPAREMODE_OFS;
			Rpos = ARROW_R_XPOS + ARROW_COMPAREMODE_OFS;
		}

		header.priority = BGPRI_TRAY_ICON;

		wk->arrow_act_L = BoxAppView_AddActor( wk->actsys, &header, Lpos, ARROW_YPOS,
								ACTPRI_ARROW, NNS_G2D_VRAM_TYPE_2DMAIN );

		wk->arrow_act_R = BoxAppView_AddActor( wk->actsys, &header, Rpos, ARROW_YPOS,
								ACTPRI_ARROW, NNS_G2D_VRAM_TYPE_2DMAIN );
	}

	CLACT_AnmChg( wk->shadow_act, ANM_SHADOW );
	CLACT_BGPriorityChg( wk->shadow_act, BGPRI_TRAY_ICON );


	area = BoxAppVPara_GetCursorArea( wk->vpara );
	if( area != CURSOR_AREA_TRAY_TAB )
	{
		CLACT_AnmChg( wk->arrow_act_L, ANM_ARROW_L_STOP );
		CLACT_AnmChg( wk->arrow_act_R, ANM_ARROW_R_STOP );
	}
	else
	{
		CLACT_AnmChg( wk->arrow_act_L, ANM_ARROW_L_MOVE );
		CLACT_AnmChg( wk->arrow_act_R, ANM_ARROW_R_MOVE );
	}

	if( area != CURSOR_AREA_TRAY )
	{
		CLACT_SetDrawFlag( wk->shadow_act, FALSE );
	}

	// 画面復帰時、掴んでいるアイコンがあればそれに合わせた初期化が必要になる
	if( mode != BOX_MODE_ITEM )
	{
		if( BoxAppVPara_GetCursorCatchPokeFlag( wk->vpara ) == CURSOR_CATCH_NONE )
		{
			CLACT_AnmChg( wk->act, ANM_NORMAL );
			BoxAppView_IconWorkInit( wk->iconSys, wk->catch_icon, BOX_MAX_POS );
			wk->catchicon_syncro_flag = FALSE;
		}
		else
		{
			CLACT_AnmChg( wk->act, ANM_GOO );
			SetupCatchPokeObj( wk );
			wk->catchicon_syncro_flag = TRUE;
		}
		wk->itemicon_syncro_flag = FALSE;
	}
	else
	{
		if(BoxAppVPara_GetCatchItemNumber(wk->vpara) == ITEM_DUMMY_ID)
		{
			CLACT_AnmChg( wk->act, ANM_NORMAL );
			wk->itemicon_syncro_flag = FALSE;
		}
		else
		{
			CLACT_AnmChg( wk->act, ANM_GOO );
			wk->itemicon_syncro_flag = TRUE;
		}
		BoxAppView_IconWorkInit( wk->iconSys, wk->catch_icon, BOX_MAX_POS );
		wk->catchicon_syncro_flag = FALSE;
	}
	wk->itemIconWork = BoxAppView_GetItemIconWork(wk->vwk);



	// 慣れてる人モードだったら色を変えておく
	BoxAppView_CursorExpertModeChange( wk );
}
//---------------------------------------------------------------
/**
 * 掴んでいるポケモンデータを参照してアイコンを作成
 *
 * @param   wk		ワークポインタ
 *
 */
//---------------------------------------------------------------
static void SetupCatchPokeObj( CURSOR_VIEW_WORK* wk )
{
	// 現状、複数選択のまま画面復帰処理を行う可能性は考慮していない。
	VecFx32 vec;
	s32 x, y;

	vec = *CLACT_GetMatrix( wk->act );
	x = (vec.x >> FX32_SHIFT) - CURSOR_CATCHICON_XDIFF;
	y = (vec.y >> FX32_SHIFT) - CURSOR_CATCHICON_YDIFF;

	BoxAppView_IconWorkInit( wk->iconSys, wk->catch_icon, 1 );

	BoxAppView_IconAdd( wk->iconSys, BoxAppVPara_GetStatusPokePara(wk->vpara), x, y,  
			CLACT_BGPriorityGet( wk->act ), ACTPRI_CATCH_ICON, OBJCHAR_MOVING_SINGLE_ICON_POS,
			wk->catch_icon );

	wk->iconOfs[0].x = (CURSOR_CATCHICON_XDIFF * FX32_ONE);
	wk->iconOfs[0].y = (CURSOR_CATCHICON_YDIFF * FX32_ONE);


	wk->catch_icon_count = 1;
	wk->catchicon_syncro_flag = TRUE;
}


//------------------------------------------------------------------
/**
 * 終了
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
void BoxAppView_CursorQuit( CURSOR_VIEW_WORK* wk )
{
	if( wk->cellBuf ){
		sys_FreeMemoryEz( wk->cellBuf );
		wk->cellBuf = NULL;
	}
	if( wk->anmBuf ){
		sys_FreeMemoryEz( wk->anmBuf );
		wk->anmBuf = NULL;
	}
	if( wk->act != NULL )
	{
		CLACT_Delete( wk->act );
		wk->act = NULL;
	}
	if( wk->shadow_act != NULL )
	{
		CLACT_Delete( wk->shadow_act );
		wk->shadow_act = NULL;
	}
	if( wk->arrow_act_L != NULL )
	{
		CLACT_Delete( wk->arrow_act_L );
		wk->arrow_act_L = NULL;
	}
	if( wk->arrow_act_R != NULL )
	{
		CLACT_Delete( wk->arrow_act_R );
		wk->arrow_act_R = NULL;
	}
}

//------------------------------------------------------------------
/**
 * 画面をくるっと回って逆から出てくる動作にするかチェック
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void CheckReverseMove( const CURSOR_VIEW_WORK* wk, BOOL* xflg, BOOL* yflg )
{
	*xflg = *yflg = FALSE;

	switch( wk->area ){
	case CURSOR_AREA_TRAY:
		if( wk->next_area == CURSOR_AREA_TRAY )
		{
			u32 next_xpos = BoxAppVPara_GetCursorTrayPosX( wk->vpara );
			if(	(wk->tray_xpos == 0) && (next_xpos == TRAY_XPOS_MAX)
			||	(wk->tray_xpos == TRAY_XPOS_MAX) && (next_xpos == 0)
			){
				*xflg = TRUE;
			}
		}
		break;
	case CURSOR_AREA_TRAY_TAB:
		if(	(wk->next_area == CURSOR_AREA_EXIT_BUTTON)
		||	(wk->next_area == CURSOR_AREA_PARTY_BUTTON)
		){
			*yflg = TRUE;
		}
		break;

	case CURSOR_AREA_EXIT_BUTTON:
	case CURSOR_AREA_PARTY_BUTTON:
		if( wk->next_area == CURSOR_AREA_TRAY_TAB )
		{
			*yflg = TRUE;
		}
		break;
	}
}
//------------------------------------------------------------------
/**
 * 移動処理スタート
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
void BoxAppView_CursorMoveStart( CURSOR_VIEW_WORK* wk )
{
	BOOL x_revflg, y_revflg;
	s32  end_x, end_y;
	s32  vec_x, vec_y;
	s32  time;

	GetCursorPosByVparam( &(wk->next_xpos), &(wk->next_ypos), &(wk->next_area), wk );
	CheckReverseMove( wk, &x_revflg, &y_revflg );

	if( wk->next_area != CURSOR_AREA_TRAY )
	{
		CLACT_SetDrawFlag( wk->shadow_act, FALSE );
	}

	wk->move_x = wk->xpos << FX32_SHIFT;
	wk->move_y = wk->ypos << FX32_SHIFT;
	end_x = wk->next_xpos << FX32_SHIFT;
	end_y = wk->next_ypos << FX32_SHIFT;


	if( x_revflg == FALSE )
	{
		vec_x = end_x - wk->move_x;
	}
	else
	{
		if( end_x > wk->move_x )
		{
			vec_x = -((CURSOR_VISIBLE_X_MAX - wk->next_xpos) + (wk->xpos - CURSOR_VISIBLE_X_MIN));
		}
		else
		{
			vec_x = (CURSOR_VISIBLE_X_MAX - wk->xpos) + (wk->next_xpos - CURSOR_VISIBLE_X_MIN);
		}
		vec_x <<= FX32_SHIFT;
	}

	if( y_revflg == FALSE )
	{
		vec_y = end_y - wk->move_y;
	}
	else
	{
		if( end_y > wk->move_y )
		{
			vec_y = -((CURSOR_VISIBLE_Y_MAX - wk->next_ypos) + (wk->ypos - CURSOR_VISIBLE_Y_MIN));
		}
		else
		{
			vec_y = (CURSOR_VISIBLE_Y_MAX - wk->ypos) + (wk->next_ypos - CURSOR_VISIBLE_Y_MIN);
		}
		vec_y <<= FX32_SHIFT;
		
	}

	if( x_revflg || y_revflg ){
		time = CURSOR_LOOP_MOVE_TIME;
	}else{
		time = CURSOR_MOVE_TIME;
	}

	wk->add_x = vec_x / time;
	wk->add_y = vec_y / time;
	wk->move_timer = time;

	BoxAppView_VTaskAdd( CursorMoveTask, wk, TASKPRI_V_SUB );
}
//------------------------------------------------------------------
/**
 * 移動処理終了待ち
 *
 * @param   wk		ワークポインタ	
 *
 * @retval  BOOL	TRUEで終了
 */
//------------------------------------------------------------------
BOOL BoxAppView_CursorMoveWait( CURSOR_VIEW_WORK* wk )
{
	return wk->move_timer == 0;
}
//------------------------------------------------------------------
/**
 * 移動処理タスク
 *
 * @param   tcb			
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CursorMoveTask( TCB_PTR tcb, void* wk_adrs )
{
	CURSOR_VIEW_WORK* wk = (CURSOR_VIEW_WORK*)wk_adrs;

	VecFx32  vec;
	vec.z = 0;

	if( wk->move_timer )
	{
		wk->move_x += wk->add_x;
		if( wk->add_x > 0 && wk->move_x > CURSOR_VISIBLE_X_MAX_FX32)
		{
			wk->move_x = CURSOR_VISIBLE_X_MIN_FX32 + (CURSOR_VISIBLE_X_MAX_FX32 - wk->move_x);
		}
		if( wk->add_x < 0 && wk->move_x < CURSOR_VISIBLE_X_MIN_FX32)
		{
			wk->move_x = CURSOR_VISIBLE_X_MAX_FX32 - (CURSOR_VISIBLE_X_MIN_FX32 - wk->move_x);
		}

		wk->move_y += wk->add_y;
		if( wk->add_y > 0 && wk->move_y > CURSOR_VISIBLE_Y_MAX_FX32)
		{
			wk->move_y = CURSOR_VISIBLE_Y_MIN_FX32 + (CURSOR_VISIBLE_Y_MAX_FX32 - wk->move_y);
		}
		if( wk->add_y < 0 && wk->move_y < CURSOR_VISIBLE_Y_MIN_FX32)
		{
			wk->move_y = CURSOR_VISIBLE_Y_MAX_FX32 - (CURSOR_VISIBLE_Y_MIN_FX32 - wk->move_y);
		}

		vec.x = wk->move_x;
		vec.y = wk->move_y;
		vec.z = 0;
		CursorPosSet( wk, &vec );

		wk->move_timer--;
		return;
	}

	vec.x = wk->next_xpos << FX32_SHIFT;
	vec.y = wk->next_ypos << FX32_SHIFT;
	vec.z = 0;
	CursorPosSet( wk, &vec );

	wk->xpos = wk->next_xpos;
	wk->ypos = wk->next_ypos;
	wk->area = wk->next_area;
	wk->tray_xpos = BoxAppVPara_GetCursorTrayPosX( wk->vpara );
	wk->tray_ypos = BoxAppVPara_GetCursorTrayPosY( wk->vpara );
	wk->party_pos = BoxAppVPara_GetCursorPartyPos( wk->vpara );


	if( wk->next_area == CURSOR_AREA_TRAY )
	{
		CLACT_SetDrawFlag( wk->shadow_act, TRUE );
	}

	if( wk->next_area != CURSOR_AREA_TRAY_TAB )
	{
		CLACT_AnmChg( wk->arrow_act_L, ANM_ARROW_L_STOP );
		CLACT_AnmChg( wk->arrow_act_R, ANM_ARROW_R_STOP );
	}
	else
	{
		CLACT_AnmChg( wk->arrow_act_L, ANM_ARROW_L_MOVE );
		CLACT_AnmChg( wk->arrow_act_R, ANM_ARROW_R_MOVE );
	}

	TCB_Delete(tcb);
}
//------------------------------------------------------------------
/**
 * ポケモンアイコンをつかむ動作スタート
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
void BoxAppView_CursorCatchStart( CURSOR_VIEW_WORK* wk )
{
	CLACT_AnmChg( wk->act, ANM_PAR );

	wk->add_y = (CURSOR_CATCHMOVE_DIPTH << FX32_SHIFT) / CURSOR_CATCHMOVE_DOWN_TIME;
	wk->next_ypos = (wk->ypos + CURSOR_CATCHMOVE_DIPTH);
	wk->move_timer = CURSOR_CATCHMOVE_DOWN_TIME;
	wk->move_seq = 0;

	PointIconDataToCatchIconData( wk );

	BoxAppView_VTaskAdd( CursorCatchMoveTask, wk, TASKPRI_V_SUB );
}
//------------------------------------------------------------------
/**
 * ポケモンアイコンをつかむ動作終了待ち
 *
 * @param   wk		
 *
 * @retval  BOOL	TRUEで終了
 */
//------------------------------------------------------------------
BOOL BoxAppView_CursorCatchWait( CURSOR_VIEW_WORK* wk )
{
	return wk->move_seq == MOVE_SEQ_END;
}
//------------------------------------------------------------------
/**
 * ポケモンアイコンをつかむ動作タスク
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CursorCatchMoveTask( TCB_PTR tcb, void* wk_adrs )
{
	CURSOR_VIEW_WORK* wk = (CURSOR_VIEW_WORK*)wk_adrs;

	VecFx32  vec = *(CLACT_GetMatrix( wk->act ));

	switch( wk->move_seq ){
	case 0:
		wk->shadow_syncro_flag = FALSE;
		if( wk->move_timer )
		{
			vec.y += wk->add_y;
			CursorPosSet( wk, &vec );
			wk->move_timer--;
			break;
		}
		vec.y = wk->next_ypos << FX32_SHIFT;
		CursorPosSet( wk, &vec );
		CLACT_AnmChg( wk->act, ANM_GOO );

		CatchIconDataEnable( wk );

		wk->move_timer = CURSOR_CATCHMOVE_UP_TIME;
		wk->move_seq++;
		/* fallthru */
	case 1:
		if( wk->move_timer )
		{
			vec.y -= wk->add_y;
			CursorPosSet( wk, &vec );
			wk->move_timer--;
			break;
		}
		vec.y = wk->ypos << FX32_SHIFT;
		CursorPosSet( wk, &vec );
		wk->move_seq = MOVE_SEQ_END;
		wk->shadow_syncro_flag = TRUE;
		TCB_Delete( tcb );
	}
}
//------------------------------------------------------------------
/**
 * ポケモンアイコンを置く動作スタート
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
void BoxAppView_CursorPutStart( CURSOR_VIEW_WORK* wk )
{
	wk->add_y = (CURSOR_CATCHMOVE_DIPTH << FX32_SHIFT) / CURSOR_CATCHMOVE_DOWN_TIME;
	wk->next_ypos = (wk->ypos + CURSOR_CATCHMOVE_DIPTH);
	wk->move_timer = CURSOR_CATCHMOVE_DOWN_TIME;
	wk->move_seq = 0;

	BoxAppView_VTaskAdd( CursorPutMoveTask, wk, TASKPRI_V_SUB );
}
//------------------------------------------------------------------
/**
 * ポケモンアイコンを置く動作終了待ち
 *
 * @param   wk		
 *
 * @retval  BOOL	TRUEで終了
 */
//------------------------------------------------------------------
BOOL BoxAppView_CursorPutWait( CURSOR_VIEW_WORK* wk )
{
	if( wk->move_seq == MOVE_SEQ_END )
	{
		CatchIconDataPut( wk );
		BoxAppView_IconWorkInit( wk->iconSys, wk->catch_icon, wk->catch_icon_count );
		wk->catch_icon_count = 0;
		return TRUE;
	}
	return FALSE;
}
//------------------------------------------------------------------
/**
 * ポケモンアイコンを置く動作タスク
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CursorPutMoveTask(TCB_PTR tcb, void* wk_adrs )
{
	CURSOR_VIEW_WORK* wk = (CURSOR_VIEW_WORK*)wk_adrs;

	VecFx32  vec = *(CLACT_GetMatrix( wk->act ));

	switch( wk->move_seq ){
	case 0:
		wk->shadow_syncro_flag = FALSE;
		if( wk->move_timer )
		{
			vec.y += wk->add_y;
			CursorPosSet( wk, &vec );
			wk->move_timer--;
			break;
		}
		vec.y = wk->next_ypos << FX32_SHIFT;
		CursorPosSet( wk, &vec );
		CLACT_AnmChg( wk->act, ANM_PAR );

		CatchIconDataDisable( wk );

		wk->move_timer = CURSOR_CATCHMOVE_UP_TIME;
		wk->move_seq++;
		/* fallthru */
	case 1:
		if( wk->move_timer )
		{
			vec.y -= wk->add_y;
			CursorPosSet( wk, &vec );
			wk->move_timer--;
			break;
		}
		vec.y = wk->ypos << FX32_SHIFT;
		CursorPosSet( wk, &vec );
		CLACT_AnmChg( wk->act, ANM_NORMAL );
		wk->move_seq = MOVE_SEQ_END;
		wk->shadow_syncro_flag = TRUE;
		TCB_Delete(tcb);
	}
}

//------------------------------------------------------------------
/**
 * ポケモンアイコンを入れ替える動作スタート
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
void BoxAppView_CursorIconSwapStart( CURSOR_VIEW_WORK* wk )
{
	VecFx32  vec;
	CLACT_WORK_PTR  act;

	CLACT_AnmChg( wk->act, ANM_PAR );

	wk->move_taskflag = FALSE;

	act = GetPointIconActor( wk );
	vec = *(CLACT_GetMatrix( act ));
	SwapIconTaskAdd( wk, wk->catch_icon->act, vec.y, 1, CLACT_DrawPriorityGet(act) );

	vec = *(CLACT_GetMatrix( wk->catch_icon->act ));
	SwapIconTaskAdd( wk, act, vec.y, -1, CLACT_DrawPriorityGet(wk->catch_icon->act) );

	wk->move_seq = 0;
}
//------------------------------------------------------------------
/**
 * ポケモンアイコンを入れ替える動作終了待ち
 *
 * @param   wk		
 *
 * @retval  BOOL	TRUEで終了
 */
//------------------------------------------------------------------
BOOL BoxAppView_CursorIconSwapWait( CURSOR_VIEW_WORK* wk )
{
	if( SwapIconMoveTaskEndCheck( wk ) )
	{
		CLACT_AnmChg( wk->act, ANM_GOO );
		CatchIconDataSwap( wk );
		return TRUE;
	}
	return FALSE;
}

//-----------------------------------------------
/**
 *  アイコン入れ替え動作タスク用ワーク
 */
//-----------------------------------------------
typedef struct {
	CLACT_WORK_PTR	act;
	u16			timer;
	u16			half_time;
	u32			nextpri;
	fx32		ypos;
	fx32		end_ypos;
	fx32		org_xpos;
	fx32		sinpos;
	fx32		posadd;
	fx32		sinadd;
	fx32		sinval;

	CURSOR_VIEW_WORK* wk;

}ICON_SWAPMOVE_TASKWORK;

//------------------------------------------------------------------
/**
 * アイコン入れ替え動作タスクセット
 *
 * @param   wk			ワークポインタ
 * @param   act			アクターポインタ
 * @param   end_y		移動先Ｙ座標
 * @param   sindir		横移動方向（1 or -1）
 * @param   nextpri		移動後のプライオリティ
 *
 */
//------------------------------------------------------------------
static void SwapIconTaskAdd( CURSOR_VIEW_WORK* wk, CLACT_WORK_PTR act, fx32 end_y, s32 sindir, u32 nextpri )
{
	ICON_SWAPMOVE_TASKWORK* taskwk = sys_AllocMemory( HEAPID_BOX_VIEW, sizeof(ICON_SWAPMOVE_TASKWORK) );

	if( taskwk )
	{
		VecFx32  vec;

		vec = *CLACT_GetMatrix(act);

		taskwk->act = act;
		taskwk->timer = CURSOR_SWAPMOVE_TIME;
		taskwk->half_time = CURSOR_SWAPMOVE_TIME / 2;
		taskwk->nextpri = nextpri;
		taskwk->ypos = vec.y;
		taskwk->org_xpos = vec.x;
		taskwk->end_ypos = end_y;
		taskwk->sinpos = 0;
		taskwk->sinval = sindir * CURSOR_SWAPMOVE_WIDTH;

		taskwk->posadd = (taskwk->end_ypos - taskwk->ypos) / CURSOR_SWAPMOVE_TIME;
		taskwk->sinadd = (180 << FX32_SHIFT) / CURSOR_SWAPMOVE_TIME;

		taskwk->wk = wk;
		if( BoxAppView_VTaskAdd( SwapIconMoveTask, taskwk, TASKPRI_V_SUB ) )
		{
			wk->move_taskflag = TRUE;
			return;
		}
		else
		{
			sys_FreeMemoryEz( taskwk );
		}
	}
}
//------------------------------------------------------------------
/**
 * アイコン入れ替え動作タスクの終了待ち
 *
 * @param   wk			ワークポインタ
 *
 * @retval  BOOL		TRUEで終了
 */
//------------------------------------------------------------------
static BOOL SwapIconMoveTaskEndCheck( CURSOR_VIEW_WORK* wk )
{
	return wk->move_taskflag == FALSE;
}
//------------------------------------------------------------------
/**
 * アイコン入れ替え動作タスク終了（タスク本体からのみ呼ばれる）
 *
 * @param   wk			ワークポインタ
 * @param   tcb			TCBポインタ
 * @param   wk_adrs		TCBワークアドレス
 *
 */
//------------------------------------------------------------------
static void SwapIconWorkDeleteReserve( void* wk_adrs )
{
	CURSOR_VIEW_WORK* wk = wk_adrs;
	wk->move_taskflag = FALSE;
}
//------------------------------------------------------------------
/**
 * アイコン入れ替え動作タスク本体
 *
 * @param   tcb			
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void SwapIconMoveTask( TCB_PTR tcb, void* wk_adrs )
{
	ICON_SWAPMOVE_TASKWORK* wk = (ICON_SWAPMOVE_TASKWORK*)wk_adrs;
	VecFx32  vec;

	vec = *CLACT_GetMatrix( wk->act );

	if( wk->timer )
	{
		fx32 sin;

		wk->timer--;
		if( wk->timer == wk->half_time )
		{
			BoxAppView_ChangeDrawPriority( wk->act, wk->nextpri );
		}
		wk->ypos += wk->posadd;
		vec.y = wk->ypos;

		wk->sinpos += wk->sinadd;
		sin = wk->sinval * Sin360( wk->sinpos >> FX32_SHIFT );
		vec.x = wk->org_xpos + sin;
		CLACT_SetMatrix( wk->act, &vec );
	}
	else
	{
		vec.x = wk->org_xpos;
		vec.y = wk->end_ypos;
		CLACT_SetMatrix( wk->act, &vec );
//		SwapIconTaskDel( wk->wk, tcb, wk_adrs );
		BoxAppView_IrqMemoryFreeReq( wk_adrs, SwapIconWorkDeleteReserve, wk->wk );
		TCB_Delete( tcb );
	}
}
//------------------------------------------------------------------
/**
 * ボタンを押す動作開始
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
void BoxAppView_CursorButtonPushActionStart( CURSOR_VIEW_WORK* wk )
{
	VecFx32  vec;

	if( wk->catchicon_syncro_flag == FALSE && wk->itemicon_syncro_flag == FALSE)
	{
		CLACT_AnmChg( wk->act, ANM_PUSH_START);
	}

	vec = *CLACT_GetMatrix( wk->act );
	vec.y += (PUSHMOVE_UP_RANGE * FX32_ONE);
	CursorPosSet( wk, &vec );

	wk->move_seq = 0;
	wk->move_timer = 0;

	if( BoxAppView_VTaskAdd( ButtonPushActionTask, wk, TASKPRI_V_SUB ) )
	{
		wk->move_taskflag = TRUE;
	}

}
//------------------------------------------------------------------
/**
 * ボタンを押す動作終了待ち
 *
 * @param   wk		ワークポインタ
 *
 * @retval  BOOL	TRUEで終了
 */
//------------------------------------------------------------------
BOOL BoxAppView_CursorButtonPushActionWait( CURSOR_VIEW_WORK* wk )
{
	return wk->move_taskflag == FALSE;
}
//------------------------------------------------------------------
/**
 * ボタンを押す動作タスク
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void ButtonPushActionTask( TCB_PTR tcb, void* wk_adrs )
{
	CURSOR_VIEW_WORK* wk = (CURSOR_VIEW_WORK*)wk_adrs;

	switch( wk->move_seq ){
	case 0:
		if( ++(wk->move_timer) >= PUSHMOVE_START_TIME )
		{
			VecFx32 vec = *CLACT_GetMatrix( wk->act );
			wk->next_ypos = (vec.y >> FX32_SHIFT) + PUSHMOVE_DOWN_RANGE;
			wk->add_y = ( PUSHMOVE_DOWN_RANGE * FX32_ONE ) / PUSHMOVE_DOWN_TIME;
			wk->move_timer = PUSHMOVE_DOWN_TIME;

			if( wk->catchicon_syncro_flag == FALSE && wk->itemicon_syncro_flag == FALSE)
			{
				CLACT_AnmChg( wk->act, ANM_PUSH_END );
			}

			wk->move_seq++;
		}
		break;

	case 1:
		{
			VecFx32 vec = *CLACT_GetMatrix( wk->act );
			if( wk->move_timer )
			{
				vec.y += wk->add_y;
				CursorPosSet( wk, &vec );
				wk->move_timer--;
			}
			else
			{
				vec.y = wk->next_ypos << FX32_SHIFT;
				CursorPosSet( wk, &vec );
				wk->move_taskflag = FALSE;
				TCB_Delete(tcb);
			}
		}
		break;
	}
}
//------------------------------------------------------------------
/**
 * ボタンを離す動作開始
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
void BoxAppView_CursorButtonReleaseActionStart( CURSOR_VIEW_WORK* wk )
{
	VecFx32 vec = *CLACT_GetMatrix( wk->act );
	wk->next_ypos = (vec.y >> FX32_SHIFT) + PUSHMOVE_RETURN_RANGE;
	wk->add_y = ( PUSHMOVE_RETURN_RANGE * FX32_ONE ) / PUSHMOVE_RETURN_TIME;
	wk->move_timer = PUSHMOVE_RETURN_TIME;
	wk->move_seq = 0;

	if( BoxAppView_VTaskAdd( ButtonReleaseActionTask, wk, TASKPRI_V_SUB ) )
	{
		wk->move_taskflag = TRUE;
	}

}
//------------------------------------------------------------------
/**
 * ボタンを離す動作終了待ち
 *
 * @param   wk			ワークポインタ
 *
 * @retval  BOOL		TRUEで終了
 */
//------------------------------------------------------------------
BOOL BoxAppView_CursorButtonReleaseActionWait( CURSOR_VIEW_WORK* wk )
{
	if( wk->move_taskflag == FALSE )
	{
		if( wk->catchicon_syncro_flag == FALSE 
		&&	wk->itemicon_syncro_flag == FALSE
		){
			if( CLACT_AnmGet( wk->act ) != ANM_NORMAL )
			{
				CLACT_AnmChg( wk->act, ANM_NORMAL );
			}
		}
		return TRUE;
	}
	return FALSE;
}
//------------------------------------------------------------------
/**
 * ボタンを離す動作タスク
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void ButtonReleaseActionTask( TCB_PTR tcb, void* wk_adrs )
{
	CURSOR_VIEW_WORK* wk;
	VecFx32 vec;

	wk = (CURSOR_VIEW_WORK*)wk_adrs;
	vec = *CLACT_GetMatrix( wk->act );

	if( wk->move_timer )
	{
		vec.y += wk->add_y;
		CursorPosSet( wk, &vec );
		wk->move_timer--;
	}
	else
	{
		vec.y = wk->next_ypos << FX32_SHIFT;
		CursorPosSet( wk, &vec );
		wk->move_taskflag = FALSE;
		TCB_Delete( tcb );
	}
}

//------------------------------------------------------------------
/**
 * つかんでいるアイコンをボックスに預ける
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
void BoxAppView_CursorCatchIconAzukeru( CURSOR_VIEW_WORK* wk )
{
	// 現在表示中のトレイに預ける場合はアイコン表示を更新
	if( wk->vpara->azukeruTrayNumber == BoxAppVPara_GetTrayBoxNumber( wk->vpara ) )
	{
		BoxAppView_TrayUpdateIcon( wk->trayWork );
	}
	CatchIconDataDelete( wk );
	CLACT_AnmChg( wk->act, ANM_NORMAL );
}

//------------------------------------------------------------------
/**
 * つかんでいるアイコンを逃がす動作スタート
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
void BoxAppView_CursorCatchIconReleaseStart( CURSOR_VIEW_WORK* wk )
{
	CLACT_AnmChg( wk->act, ANM_PAR );

	BoxAppView_IconAnmStart( wk->iconSys, wk->catch_icon, ICON_ANM_RELEASE );
	wk->move_seq = 0;
}
//------------------------------------------------------------------
/**
 * つかんでいるアイコンを逃がす動作の終了待ち
 *
 * @param   wk			ワークポインタ
 *
 * @retval  BOOL		TRUEで終了
 */
//------------------------------------------------------------------
BOOL BoxAppView_CursorCatchIconReleaseWait( CURSOR_VIEW_WORK* wk )
{
	const BOXAPP_WORK* mainWk = BoxAppView_GetMainWork( wk->vwk );

	switch( wk->move_seq ){
	case 0:
		if( BoxAppView_IconAnmWait(wk->iconSys, wk->catch_icon) )
		{
			wk->move_seq++;
		}
		break;
	case 1:
		if( BoxApp_ReleaseWazaCheckDone( mainWk ) )
		{
			if( BoxApp_ReleaseWazaCheckOK( mainWk ) )
			{
				CLACT_AnmChg( wk->act, ANM_NORMAL );
				CatchIconDataDelete( wk );
				return TRUE;
			}
			else
			{
				BoxAppView_IconAnmStart( wk->iconSys, wk->catch_icon, ICON_ANM_COMEBACK );
				wk->move_seq++;
			}
		}
		break;
	case 2:
		if( BoxAppView_IconAnmWait(wk->iconSys, wk->catch_icon) )
		{
			CLACT_AnmChg( wk->act, ANM_GOO );
			return TRUE;
		}
		break;
	}
	return FALSE;
}

//------------------------------------------------------------------
/**
 * アクターのBGﾌﾟﾗｲｵﾘﾃｨを手持ちトレイモードに
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
void BoxAppView_CursorPriPartyMode( CURSOR_VIEW_WORK* wk )
{
	CLACT_BGPriorityChg( wk->act, BGPRI_PARTY_ICON );
	if( wk->catchicon_syncro_flag )
	{
		CLACT_BGPriorityChg( wk->catch_icon->act, BGPRI_PARTY_ICON );
	}
	if( wk->itemicon_syncro_flag )
	{
		BoxAppView_ItemIcon_ChangePriorityCaughtIcon( wk->itemIconWork, BGPRI_PARTY_ICON );
	}

}
//------------------------------------------------------------------
/**
 * アクターのBGﾌﾟﾗｲｵﾘﾃｨを通常モードに
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
void BoxAppView_CursorPriNormalMode( CURSOR_VIEW_WORK* wk )
{
	CLACT_BGPriorityChg( wk->act, BGPRI_TRAY_ICON );
	if( wk->catchicon_syncro_flag )
	{
		CLACT_BGPriorityChg( wk->catch_icon->act, BGPRI_TRAY_ICON );
	}
	if( wk->itemicon_syncro_flag )
	{
		BoxAppView_ItemIcon_ChangePriorityCaughtIcon( wk->itemIconWork, BGPRI_TRAY_ICON );
	}
}

//------------------------------------------------------------------
/**
 * ステータス表示中ポケモンアイコンのマーキング用ステータスを更新
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
void BoxAppView_CursorIconMarkUpdate( CURSOR_VIEW_WORK* wk )
{
	if( wk->catchicon_syncro_flag )
	{
		u32 markBit = BoxAppVPara_GetStatusPokeMarkBit( wk->vpara );
		BoxAppView_IconMarkBitSet( wk->iconSys, wk->catch_icon, markBit );
	}
}

//------------------------------------------------------------------
/**
 * アイコンを絞り込みモード表示に対応
 *
 * @param   wk		ワークポインタ
 */
//------------------------------------------------------------------
void BoxAppView_CursorCatchIconLimitModeSet( CURSOR_VIEW_WORK* wk )
{
	u32 limitBit = BoxAppVPara_GetLimitModeBitFlag( wk->vpara );

	if( wk->catch_icon->act != NULL )
	{
		BoxAppView_IconLimitModeSet( wk->iconSys, wk->catch_icon, limitBit );
	}
}
//------------------------------------------------------------------
/**
 * アイコンのアイテム情報を更新
 *
 * @param   wk			ワークポインタ
 * @param   itemNumber	アイテムナンバー
 *
 */
//------------------------------------------------------------------
void BoxAppView_CursorCatchIconUpdateItem( CURSOR_VIEW_WORK* wk, u32 itemNumber )
{
	if( wk->catch_icon->act != NULL )
	{
		BoxAppView_IconItemNumberSet( wk->iconSys, wk->catch_icon, itemNumber );
		BoxAppView_IconLimitModeSet( wk->iconSys, wk->catch_icon, BoxAppVPara_GetLimitModeBitFlag(wk->vpara) );
	}
}


//------------------------------------------------------------------
/**
 * 慣れてる人モードのオンオフに応じてカーソル色変更
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
void BoxAppView_CursorExpertModeChange( CURSOR_VIEW_WORK* wk )
{
	if( BoxAppVPara_GetExpertModeFlag(wk->vpara) )
	{
		CLACT_PaletteNoChg( wk->act, OBJPAL_CURSOR_EXPERTMODE );
	}
	else
	{
		CLACT_PaletteNoChg( wk->act, OBJPAL_CURSOR );
	}
}


//------------------------------------------------------------------
/**
 * アイコンの範囲選択処理開始
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
void BoxAppView_CursorAleaSelectStart( CURSOR_VIEW_WORK* wk )
{
	CLACT_AnmChg( wk->act, ANM_PAR );
}
//------------------------------------------------------------------
/**
 * カーソルアクター位置を返す
 *
 * @param   wk		
 * @param   mtx		
 *
 */
//------------------------------------------------------------------
void BoxAppView_CursorGetMatrix( CURSOR_VIEW_WORK* wk, VecFx32* mtx )
{
	*mtx = *(CLACT_GetMatrix(wk->act));
}


/*====================================================================================================*/
/* アイテムアイコン処理関連                                                                           */
/*====================================================================================================*/


//------------------------------------------------------------------
/**
 * アイテムをつかむ動作開始
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
void BoxAppView_CursorItemCatchStart( CURSOR_VIEW_WORK* wk )
{
	wk->move_seq = 0;

	if( TCB_Add( ItemCatchTask, wk, TASKPRI_VIEW_COMMAND_SUB ) )
	{
		wk->itemicon_syncro_flag = TRUE;
		wk->move_taskflag = TRUE;
	}
}
//------------------------------------------------------------------
/**
 * アイテムをつかむ動作終了待ち
 *
 * @param   wk		ワークポインタ
 *
 * @retval  BOOL	TRUEで終了
 */
//------------------------------------------------------------------
BOOL BoxAppView_CursorItemCatchWait( CURSOR_VIEW_WORK* wk )
{
	return (wk->move_taskflag == FALSE);
}
//------------------------------------------------------------------
/**
 * アイテムをつかむ動作の実行タスク
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void ItemCatchTask( TCB_PTR tcb, void* wk_adrs )
{
	CURSOR_VIEW_WORK* wk = wk_adrs;

	switch(wk->move_seq){
	case 0:
		CLACT_AnmChg( wk->act, ANM_PAR );
		BoxAppView_ItemIcon_StartCatch( wk->itemIconWork );
		wk->move_seq++;
		break;
	case 1:
		if( BoxAppView_ItemIcon_WaitCatch( wk->itemIconWork ) )
		{
			CLACT_AnmChg( wk->act, ANM_GOO );
			wk->move_taskflag = FALSE;
			TCB_Delete(tcb);
		}
	}
}


//------------------------------------------------------------------
/**
 * アイテムを持たせる動作開始
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
void BoxAppView_CursorItemSetStart( CURSOR_VIEW_WORK* wk )
{
	wk->move_seq = 0;

	if( TCB_Add( ItemSetTask, wk, TASKPRI_VIEW_COMMAND_SUB ) )
	{
		wk->itemicon_syncro_flag = FALSE;
		wk->move_taskflag = TRUE;
	}
}
//------------------------------------------------------------------
/**
 * アイテムを持たせる動作終了待ち
 *
 * @param   wk		ワークポインタ
 *
 * @retval  BOOL	TRUEで終了
 */
//------------------------------------------------------------------
BOOL BoxAppView_CursorItemSetWait( CURSOR_VIEW_WORK* wk )
{
	return (wk->move_taskflag == FALSE);
}
//------------------------------------------------------------------
/**
 * アイテムを持たせる動作の実行タスク
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void ItemSetTask( TCB_PTR tcb, void* wk_adrs )
{
	CURSOR_VIEW_WORK* wk = wk_adrs;

	switch(wk->move_seq){
	case 0:
		CLACT_AnmChg( wk->act, ANM_PAR );
		BoxAppView_ItemIcon_StartSet( wk->itemIconWork );
		wk->move_seq++;
		break;
	case 1:
		if( BoxAppView_ItemIcon_WaitSet( wk->itemIconWork ) )
		{
			CLACT_AnmChg( wk->act, ANM_NORMAL );
			wk->move_taskflag = FALSE;
			TCB_Delete(tcb);
		}
	}
}


//------------------------------------------------------------------
/**
 * アイテムをとりかえる動作開始
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
void BoxAppView_CursorItemSwapStart( CURSOR_VIEW_WORK* wk )
{
	wk->move_seq = 0;

	if( TCB_Add( ItemSwapTask, wk, TASKPRI_VIEW_COMMAND_SUB ) )
	{
		wk->move_taskflag = TRUE;
	}
}
//------------------------------------------------------------------
/**
 * アイテムをとりかえる動作の終了待ち
 *
 * @param   wk		ワークポインタ
 *
 * @retval  BOOL	TRUEで終了
 */
//------------------------------------------------------------------
BOOL BoxAppView_CursorItemSwapWait( CURSOR_VIEW_WORK* wk )
{
	return (wk->move_taskflag == FALSE);
}
//------------------------------------------------------------------
/**
 * アイテムをとりかえる動作の実行タスク
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void ItemSwapTask( TCB_PTR tcb, void* wk_adrs )
{
	CURSOR_VIEW_WORK* wk = wk_adrs;

	switch(wk->move_seq){
	case 0:
		CLACT_AnmChg( wk->act, ANM_PAR );
		BoxAppView_ItemIcon_StartSwap( wk->itemIconWork );
		wk->move_seq++;
		break;
	case 1:
		if( BoxAppView_ItemIcon_WaitSwap( wk->itemIconWork ) )
		{
			CLACT_AnmChg( wk->act, ANM_GOO );
			wk->move_taskflag = FALSE;
			TCB_Delete(tcb);
		}
	}
}
//------------------------------------------------------------------
/**
 * アイテムをバッグに戻す処理前にカーソル状態変更しておく
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
void BoxAppView_CursorItemReleaseStart( CURSOR_VIEW_WORK* wk )
{
	if( wk->itemicon_syncro_flag )
	{
		CLACT_AnmChg( wk->act, ANM_PAR );
	}
}
//------------------------------------------------------------------
/**
 * アイテムをバッグに戻す処理が終了した後の処理
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
void BoxAppView_CursorItemReleaseEnd( CURSOR_VIEW_WORK* wk )
{
	if( wk->itemicon_syncro_flag )
	{
		CLACT_AnmChg( wk->act, ANM_NORMAL );
		wk->itemicon_syncro_flag = FALSE;
	}
}







/*====================================================================================================*/
/* ここから下はローカル                                                                               */
/*====================================================================================================*/


//------------------------------------------------------------------
/**
 * カーソルアクターの移動先座標取得
 *
 * @param   wk		
 * @param   vpara		
 *
 */
//------------------------------------------------------------------
static void GetCursorPosByVparam( s32* x, s32* y, u8* area, CURSOR_VIEW_WORK* wk )
{
	const BOXAPP_VPARAM* vpara = wk->vpara;

	*area = BoxAppVPara_GetCursorArea( vpara );
	switch( *area ){
	case CURSOR_AREA_TRAY:
		*x = ICON_TRAY_XORG + BoxAppView_GetTrayScrollOfs(wk->vwk) + BoxAppVPara_GetCursorTrayPosX(vpara) * ICON_TRAY_XSPC + CURSOR_ICON_XDIFF;
		*y = ICON_TRAY_YORG + BoxAppVPara_GetCursorTrayPosY(vpara) * ICON_TRAY_YSPC + CURSOR_ICON_YDIFF;
		break;

	case CURSOR_AREA_PARTY:
		{
			u32 pos = BoxAppVPara_GetCursorPartyPos( vpara );

			BoxAppView_PartyGetIconDispPos( BoxAppView_GetPartyViewWork(wk->vwk), pos, x, y );
			(*x) += CURSOR_ICON_XDIFF;
			(*y) += CURSOR_ICON_YDIFF;
		}
		break;

	case CURSOR_AREA_TRAY_TAB:
		*x = CURSOR_TRAYTAB_XPOS + BoxAppView_GetTrayScrollOfs(wk->vwk);
		*y = CURSOR_TRAYTAB_YPOS;
		break;

	case CURSOR_AREA_PARTY_BUTTON:
		*x = CURSOR_PARTYBUTTON_XPOS + BoxAppView_GetTrayScrollOfs(wk->vwk);
		*y = CURSOR_PARTYBUTTON_YPOS;
		break;

	case CURSOR_AREA_EXIT_BUTTON:
		*x = CURSOR_CLOSEBUTTON_XPOS + BoxAppView_GetTrayScrollOfs(wk->vwk);
		*y = CURSOR_CLOSEBUTTON_YPOS;
		break;

	}
}
//------------------------------------------------------------------
/**
 * カーソルアクターの座標セット（つかんでるアイコンがあれば同期させる）
 *
 * @param   wk		
 * @param   vec		
 *
 */
//------------------------------------------------------------------
static void CursorPosSet( CURSOR_VIEW_WORK* wk, VecFx32* vec )
{
	CLACT_SetMatrix( wk->act, vec );

	if( wk->catchicon_syncro_flag )
	{
		VecFx32  icon_vec;
		int i;

		icon_vec.z = 0;
		for(i=0; i<wk->catch_icon_count; i++)
		{
			icon_vec.x = vec->x + wk->iconOfs[i].x;
			icon_vec.y = vec->y - wk->iconOfs[i].y;
			CLACT_SetMatrix( wk->catch_icon[i].act, &icon_vec );
		}
	}

	if( wk->itemicon_syncro_flag )
	{
		BoxAppView_ItemIcon_MoveCaughtIcon( wk->itemIconWork, vec );
	}

	if( wk->shadow_syncro_flag)
	{
		VecFx32  shadow_vec = *vec;
		shadow_vec.y += (CURSOR_SHADOW_DIFF << FX32_SHIFT);
		CLACT_SetMatrix( wk->shadow_act, &shadow_vec );
	}
}
//------------------------------------------------------------------
/**
 * 今いる場所のアイコンデータを掴んでいるアイコン用ワークに移動
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void PointIconDataToCatchIconData( CURSOR_VIEW_WORK* wk )
{
	if( BoxAppVPara_GetCursorArea( wk->vpara ) == CURSOR_AREA_TRAY )
	{
		// 単体つかみ
		if( BoxAppVPara_CheckAreaSelectSinglePoke( wk->vpara ) )
		{
			u32 pos = BoxAppVPara_GetCursorTrayPos( wk->vpara );
			BoxAppView_TrayMoveIconData( wk->trayWork, pos, OBJCHAR_MOVING_SINGLE_ICON_POS, wk->catch_icon );
			wk->catch_icon_count = 1;
			wk->iconOfs[0].x = (CURSOR_CATCHICON_XDIFF * FX32_ONE);
			wk->iconOfs[0].y = (CURSOR_CATCHICON_YDIFF * FX32_ONE);
		}
		// 範囲選択つかみ
		else
		{
			u32 pos, x, y, l, r, t, b, cursor_x, cursor_y;

			BoxAppVPara_GetAreaSelectParam( wk->vpara, &l, &r, &t, &b );

			cursor_x = BoxAppVPara_GetCursorTrayPosX( wk->vpara );
			cursor_y = BoxAppVPara_GetCursorTrayPosY( wk->vpara );
			pos = 0;
			for(y=t; y<=b; y++)
			{
				for(x=l; x<=r; x++)
				{
					BoxAppView_TrayMoveIconData(wk->trayWork, y*BOX_MAX_COLUMN+x, 
						OBJCHAR_AREASELECT_ICON_POS+pos*OBJCHAR_POKEICON_SIZE, &wk->catch_icon[pos]);

					if( wk->catch_icon[pos].act != NULL )
					{
						wk->iconOfs[pos].x = (CURSOR_CATCHICON_XDIFF + (x-cursor_x)*ICON_TRAY_XSPC) * FX32_ONE;
						wk->iconOfs[pos].y = (CURSOR_CATCHICON_YDIFF - (y-cursor_y)*ICON_TRAY_YSPC) * FX32_ONE;
						pos++;
					}
				}
			}
			wk->catch_icon_count = pos;
		}
	}
	else
	{
		u32 pos = BoxAppVPara_GetCursorPartyPos( wk->vpara );
		BoxAppView_PartyMoveIconData( wk->partyWork, pos, OBJCHAR_MOVING_SINGLE_ICON_POS, wk->catch_icon );
		wk->catch_icon_count = 1;
		wk->iconOfs[0].x = (CURSOR_CATCHICON_XDIFF * FX32_ONE);
		wk->iconOfs[0].y = (CURSOR_CATCHICON_YDIFF * FX32_ONE);

	}

//	CLACT_BGPriorityChg( wk->catch_icon->act, CLACT_BGPriorityGet(wk->act) );
}
//------------------------------------------------------------------
/**
 * 掴んでいるアイコンプライオリティを調整＆カーソルに追随させる
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void CatchIconDataEnable( CURSOR_VIEW_WORK* wk )
{
	int i;

	for(i=0; i<wk->catch_icon_count;i ++)
	{
		BoxAppView_ChangeDrawPriority( wk->catch_icon[i].act, ACTPRI_CATCH_ICON );
	}
	wk->catchicon_syncro_flag = TRUE;
}
//------------------------------------------------------------------
/**
 * つかんでいるアイコンデータを今いる場所用のワークに移動させる
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void CatchIconDataPut( CURSOR_VIEW_WORK* wk )
{
	if( BoxAppVPara_GetCursorArea( wk->vpara ) == CURSOR_AREA_TRAY )
	{
		// 単体つかみ
		if( BoxAppVPara_CheckAreaSelectSinglePoke( wk->vpara ) )
		{
			u32 pos = BoxAppVPara_GetCursorTrayPos( wk->vpara );
			BoxAppView_TrayPutIconData( wk->trayWork, pos, wk->catch_icon );
		}
		// 範囲選択つかみ
		else
		{
			int i, top_pos, put_pos;

			top_pos = BoxAppVPara_GetAreaSelectCursorTopPos(wk->vpara);
			for(i=0; i<wk->catch_icon_count; i++)
			{
				put_pos = top_pos + BoxAppVPara_GetAreaSelectIconOfsPos(wk->vpara, i);
				BoxAppView_TrayPutIconData( wk->trayWork, put_pos, &wk->catch_icon[i] );
			}
		}

	}
	else
	{
		u32 pos = BoxAppVPara_GetCursorPartyPos( wk->vpara );
		BoxAppView_PartyAddIconData( wk->partyWork, pos, wk->catch_icon );
	}
}

//------------------------------------------------------------------
/**
 * つかんでいるアイコンデータと今いる場所のアイコンデータを入れ替える
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void CatchIconDataSwap( CURSOR_VIEW_WORK* wk )
{
	// どちらも wk->catch_icon[1] を入れ替え用テンポラリとして使用。
	// 入れ替えは単体同士でしか発生しないのでこれで大丈夫なはず。
	if( BoxAppVPara_GetCursorArea( wk->vpara ) == CURSOR_AREA_TRAY )
	{
		u32 pos = BoxAppVPara_GetCursorTrayPos( wk->vpara );

		// アイコンキャラデータ入れ替え時のパシり対策。元のキャラ位置とは全く違う場所を一時的に参照させておく
		{
			BOX_ICON_WORK* trayIcon = BoxAppView_TrayGetIconData( wk->trayWork, pos );
			BoxAppView_Icon_ResetImageBank( wk->iconSys, wk->catch_icon, OBJCHAR_FIX_END );
			BoxAppView_Icon_ResetImageBank( wk->iconSys, trayIcon, OBJCHAR_FIX_END+OBJCHAR_POKEICON_SIZE);
			OS_WaitVBlankIntr();
		}

		BoxAppView_TrayMoveIconData( wk->trayWork, pos, OBJCHAR_MOVING_SINGLE_ICON_POS, &wk->catch_icon[1] );
		BoxAppView_TrayPutIconData( wk->trayWork, pos, wk->catch_icon );
		BoxAppView_IconWorkCopy(&(wk->catch_icon[1]), &(wk->catch_icon[0]), 1);
//		wk->catch_icon[0] = wk->catch_icon[1];
	}
	else
	{
		u32 pos = BoxAppVPara_GetCursorPartyPos( wk->vpara );

		// アイコンキャラデータ入れ替え時のパシり対策。元のキャラ位置とは全く違う場所を一時的に参照させておく
		{
			BOX_ICON_WORK* partyIcon = BoxAppView_PartyGetIconData( wk->partyWork, pos );
			BoxAppView_Icon_ResetImageBank( wk->iconSys, wk->catch_icon, OBJCHAR_FIX_END );
			BoxAppView_Icon_ResetImageBank( wk->iconSys, partyIcon, OBJCHAR_FIX_END+OBJCHAR_POKEICON_SIZE);
			OS_WaitVBlankIntr();
		}

		BoxAppView_PartyMoveIconData( wk->partyWork, pos, OBJCHAR_MOVING_SINGLE_ICON_POS, &wk->catch_icon[1] );
		BoxAppView_PartySetIconData( wk->partyWork, pos, wk->catch_icon );
		BoxAppView_IconWorkCopy(&(wk->catch_icon[1]), &(wk->catch_icon[0]), 1);

	}
//	CLACT_DrawPriorityChg( wk->catch_icon->act, ACTPRI_CATCH_ICON );
}

//------------------------------------------------------------------
/**
 * 掴んでいるアイコンデータを切り離す
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void CatchIconDataDisable( CURSOR_VIEW_WORK* wk )
{
	wk->catchicon_syncro_flag = FALSE;
}

//------------------------------------------------------------------
/**
 * 掴んでいるアイコンデータを削除
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void CatchIconDataDelete( CURSOR_VIEW_WORK* wk )
{
	BoxAppView_IconWorkQuit( wk->iconSys, wk->catch_icon, 1 );
	wk->catchicon_syncro_flag = FALSE;
	wk->catch_icon_count = 0;
}

//------------------------------------------------------------------
/**
 * ポイントしているアイコンのアクターポインタを返す
 *
 * @param   wk		
 *
 * @retval  CLACT_WORK_PTR		
 */
//------------------------------------------------------------------
static CLACT_WORK_PTR GetPointIconActor( CURSOR_VIEW_WORK* wk )
{
	BOX_ICON_WORK* icon;
	u32 pos;

	if( BoxAppVPara_GetCursorArea( wk->vpara ) == CURSOR_AREA_TRAY )
	{
		pos = BoxAppVPara_GetCursorTrayPos( wk->vpara );
		icon = BoxAppView_TrayGetIconData( wk->trayWork, pos );
		return icon->act;
	}
	else
	{
		pos = BoxAppVPara_GetCursorPartyPos( wk->vpara );
		icon = BoxAppView_PartyGetIconData( wk->partyWork, pos );
		return icon->act;
	}
}