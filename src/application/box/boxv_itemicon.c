//============================================================================================
/**
 * @file	boxv_itemicon.c
 * @brief	ボックス操作画面　描画下請け（アイテムアイコン関連）
 * @author	taya
 * @date	2006.03.23
 */
//============================================================================================
#include  "common.h"
#include  "gflib\calctool.h"
#include  "gflib\strbuf.h"
#include  "system\fontproc.h"
#include  "system\arc_util.h"
#include  "system\clact_util.h"
#include  "system\render_oam.h"
#include  "system\brightness.h"

#include  "box_arc.h"
#include  "box_view.h"
#include  "box_common.h"


enum {
	ICON_POKE_DIFF_X = 10,
	ICON_POKE_DIFF_Y = 8,

	ICON_CURSOR_DIFF_X = 0,
	ICON_CURSOR_DIFF_Y = 8,
};


enum {
	ITEMICON_ACTOR_MAX = 3,		// 出てくるヤツ、消えるヤツ、捕まれるヤツで３個あればよい
	ITEMICON_INDEX_NULL = -1,
};

enum {
	ITEMICON_STATE_FREE,
	ITEMICON_STATE_APPEAR,
	ITEMICON_STATE_DISAPPEAR,
	ITEMICON_STATE_CAUGHT,
};


//--------------------------------------------------------------
/**
 *  アイコングラフィック転送位置テーブル
 */
//--------------------------------------------------------------
static const struct {
	u32   cgx;
	u32   pal;
}IconGraphicTransPosTable[] = {
	{ OBJCHAR_ITEMICON_1_POS*0x20,	OBJPAL_ITEMICON1 },
	{ OBJCHAR_ITEMICON_2_POS*0x20,	OBJPAL_ITEMICON2 },
	{ OBJCHAR_ITEMICON_3_POS*0x20,	OBJPAL_ITEMICON3 },
};

//--------------------------------------------------------------
/**
 *
 */
//--------------------------------------------------------------
struct _ITEMICON_VIEW_WORK {
	BOOL					enableFlag;

	BOXAPP_VIEW_WORK*		vwk;
	const BOXAPP_VPARAM*	vpara;
	GF_BGL_INI*             bgl;
	CLACT_SET_PTR           actsys;
	BOX_ICON_SYS*           iconsys;
	CURSOR_VIEW_WORK*       cursorWork;

	CLACT_WORK_PTR          actor[ITEMICON_ACTOR_MAX];
	int                     actor_state[ITEMICON_ACTOR_MAX];

	int                     task_cnt;
	int                     restore_actID;
};





//==============================================================
// Prototype
//==============================================================
static void SetupIconActors( ITEMICON_VIEW_WORK* wk );
static void CleanupIconActors( ITEMICON_VIEW_WORK* wk );
static int ReserveIcon( ITEMICON_VIEW_WORK* wk, int next_state );
static int SearchIcon( ITEMICON_VIEW_WORK* wk, int state );
static void ChangeStateIcon( ITEMICON_VIEW_WORK* wk, int id, int next_state );
static void StartDisp_Appear( ITEMICON_VIEW_WORK* wk );
static void StartDisp_Caught( ITEMICON_VIEW_WORK* wk );
static void GetAppearIconPosAndPriority( ITEMICON_VIEW_WORK* wk, VecFx32* pos, u32* pri );
static void SetupAppearIconActor( ITEMICON_VIEW_WORK* wk, int actID, int itemNo );
static void SetupIconMoveTask( ITEMICON_VIEW_WORK* wk, int actID, const VecFx32* nextPos, int nextPriority, int frames  );
static void ItemIconMoveTask( TCB_PTR tcb, void* wk_adrs );











//------------------------------------------------------------------
/**
 * 
 *
 * @param   wk_ptr_adrs		
 * @param   vwk		
 * @param   vpara		
 * @param   bgl		
 * @param   actsys		
 *
 * @retval  BOOL		
 */
//------------------------------------------------------------------
BOOL BoxAppView_ItemIconInit( ITEMICON_VIEW_WORK** wk_ptr_adrs, BOXAPP_VIEW_WORK* vwk, const BOXAPP_VPARAM* vpara, GF_BGL_INI* bgl, CLACT_SET_PTR actsys )
{
	ITEMICON_VIEW_WORK*  wk = sys_AllocMemory(HEAPID_BOX_VIEW, sizeof(ITEMICON_VIEW_WORK));

	if( wk )
	{
		wk->vwk = vwk;
		wk->vpara = vpara;
		wk->bgl = bgl;
		wk->actsys = actsys;
		wk->iconsys = BoxAppView_GetIconSysWork( vwk );
		wk->cursorWork = BoxAppView_GetCursorWork( vwk );
		wk->task_cnt = 0;

		wk->enableFlag = (BoxAppVPara_GetBoxMode(vpara) == BOX_MODE_ITEM);

		SetupIconActors( wk );

		*wk_ptr_adrs = wk;
		return TRUE;
	}

	return FALSE;
}
//------------------------------------------------------------------
/**
 * 
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
void BoxAppView_ItemIconQuit( ITEMICON_VIEW_WORK* wk )
{
	CleanupIconActors( wk );
	sys_FreeMemoryEz( wk );
}



static void SetupIconActors( ITEMICON_VIEW_WORK* wk )
{
	if( wk->enableFlag )
	{
		enum {
			TMP_ITEMNO = ITEM_MASUTAABOORU,
		};

		CLACT_HEADER  header;
		NNSG2dImageProxy  proxy;
		NNSG2dCharacterData*  charData;
		void * loadBuf;
		int i;

		BoxAppView_SetActHeader( &header, &proxy, BoxAppView_GetObjPlttProxy( wk->vwk ),
				wk->iconsys->item_cellBank, wk->iconsys->item_anmBank, 0 );

		loadBuf = ArcUtil_CharDataGet( ARC_ITEMICON, GetItemIndex(TMP_ITEMNO,ITEM_GET_ICON_CGX), FALSE, &charData, HEAPID_BOX_VIEW );
		if( loadBuf )
		{
			int i;

			charData->mapingType = GX_GetOBJVRamModeChar();

			for(i=0; i<ITEMICON_ACTOR_MAX; i++)
			{
				NNS_G2dInitImageProxy( &proxy );
				NNS_G2dLoadImage1DMapping( charData, IconGraphicTransPosTable[i].cgx, NNS_G2D_VRAM_TYPE_2DMAIN, &proxy );

				wk->actor[i] = BoxAppView_AddActor( wk->actsys, &header, 0, 0, 0, NNS_G2D_VRAM_TYPE_2DMAIN );
				CLACT_PaletteNoChg( wk->actor[i], IconGraphicTransPosTable[i].pal );
				CLACT_SetDrawFlag( wk->actor[i], FALSE );
				CLACT_SetAffineParam( wk->actor[i], CLACT_AFFINE_NORMAL );

				wk->actor_state[i] = ITEMICON_STATE_FREE;
			}

			sys_FreeMemoryEz(loadBuf);
		}
	}
	else
	{
		int i;
		for(i=0; i<ITEMICON_ACTOR_MAX; i++)
		{
			wk->actor[i] = NULL;
			wk->actor_state[i] = ITEMICON_STATE_FREE;
		}
	}
}
//------------------------------------------------------------------
/**
 * 
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void CleanupIconActors( ITEMICON_VIEW_WORK* wk )
{
	int i;

	for(i=0; i<ITEMICON_ACTOR_MAX; i++)
	{
		if( wk->actor[i] )
		{
			CLACT_Delete( wk->actor[i] );
		}
	}
}


//======================================================================================================
// 
//======================================================================================================

//------------------------------------------------------------------
/**
 * 使われていないアイコンを探してインデックスを返す
 *
 * @param   wk		
 * @param   next_state		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int ReserveIcon( ITEMICON_VIEW_WORK* wk, int next_state )
{
	int i;

	for(i=0; i<ITEMICON_ACTOR_MAX; i++)
	{
		if( wk->actor_state[i] == ITEMICON_STATE_FREE )
		{
			wk->actor_state[i] = next_state;
			return i;
		}
	}
	return -1;
}
//------------------------------------------------------------------
/**
 * 指定された状態にあるアイコンのインデックスを返す
 *
 * @param   wk		
 * @param   state		
 *
 * @retval  int		
 */
//------------------------------------------------------------------
static int SearchIcon( ITEMICON_VIEW_WORK* wk, int state )
{
	int i;
	for(i=0; i<ITEMICON_ACTOR_MAX; i++)
	{
		if( wk->actor_state[i] == state )
		{
			return i;
		}
	}
	return -1;
}
//------------------------------------------------------------------
/**
 * 特定インデックスのアイコンの状態を変更する
 *
 * @param   wk		
 * @param   id		
 * @param   next_state		
 *
 */
//------------------------------------------------------------------
static void ChangeStateIcon( ITEMICON_VIEW_WORK* wk, int id, int next_state )
{
	wk->actor_state[id] = next_state;
}



//======================================================================================================
//======================================================================================================


//------------------------------------------------------------------
/**
 * 
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
void BoxAppView_ItemIcon_StartDisp( ITEMICON_VIEW_WORK* wk )
{
	if( wk->enableFlag == FALSE )
	{
		return;
	}

	StartDisp_Appear( wk );
	StartDisp_Caught( wk );
}

static void StartDisp_Appear( ITEMICON_VIEW_WORK* wk )
{
	u32 itemNo = BoxAppVPara_GetStatusPokeItemNumber( wk->vpara );

	if( itemNo != ITEM_DUMMY_ID )
	{
		int  actID = ReserveIcon( wk, ITEMICON_STATE_APPEAR );

		SetupAppearIconActor( wk, actID, itemNo );
		CLACT_AnmChg( wk->actor[actID], ITEMICON_ANM_APPEARED );
		CLACT_SetDrawFlag( wk->actor[actID], TRUE );
	}
}

static void StartDisp_Caught( ITEMICON_VIEW_WORK* wk )
{
	u32 itemNo = BoxAppVPara_GetCatchItemNumber( wk->vpara );

	if( itemNo != ITEM_DUMMY_ID )
	{
		VecFx32  mtx;
		u32 bgpri;
		int  actID = ReserveIcon( wk, ITEMICON_STATE_CAUGHT );

		BoxAppView_CursorGetMatrix( wk->cursorWork, &mtx );
		mtx.x += (ICON_CURSOR_DIFF_X << FX32_SHIFT);
		mtx.y += (ICON_CURSOR_DIFF_Y << FX32_SHIFT);
		if( BoxAppVPara_GetCursorArea(wk->vpara) == CURSOR_AREA_PARTY )
		{
			bgpri = BGPRI_PARTY_ICON;
		}
		else
		{
			bgpri = BGPRI_TRAY_ICON;
		}

		ArcUtil_PalSet( ARC_ITEMICON, GetItemIndex(itemNo,ITEM_GET_ICON_PAL), PALTYPE_MAIN_OBJ, 
				IconGraphicTransPosTable[actID].pal*0x20, 0x20, HEAPID_BOX_VIEW );

		CLACT_BGPriorityChg( wk->actor[actID], bgpri );
		BoxAppView_ChangeDrawPriority( wk->actor[actID], ACTPRI_CATCH_ICON );
		CLACT_SetMatrix( wk->actor[actID], &mtx );
		CLACT_AnmChg( wk->actor[actID], ITEMICON_ANM_CAUGHT );
		CLACT_SetDrawFlag( wk->actor[actID], TRUE );
	}
}

//------------------------------------------------------------------
/**
 * ポケモンの所有アイテムアイコンを表示する位置を計算（カーソル位置依存）
 *
 * @param   wk		
 * @param   pos		
 * @param   pri		
 *
 */
//------------------------------------------------------------------
static void GetAppearIconPosAndPriority( ITEMICON_VIEW_WORK* wk, VecFx32* pos, u32* pri )
{
	pos->z = 0;
	if( BoxAppVPara_GetCursorArea(wk->vpara) == CURSOR_AREA_PARTY )
	{
		s32 x, y;
		BoxAppView_PartyGetIconDispPos( BoxAppView_GetPartyViewWork(wk->vwk), 
						BoxAppVPara_GetCursorPartyPos(wk->vpara), &x, &y );
		pos->x = (x + ICON_POKE_DIFF_X) << FX32_SHIFT;
		pos->y = (y + ICON_POKE_DIFF_Y) << FX32_SHIFT;
		*pri = BGPRI_PARTY_ICON;
	}
	else
	{
		pos->x = ICON_TRAY_XORG + BoxAppView_GetTrayScrollOfs(wk->vwk) + BoxAppVPara_GetCursorTrayPosX(wk->vpara) * ICON_TRAY_XSPC + ICON_POKE_DIFF_X;
		pos->y = ICON_TRAY_YORG + BoxAppVPara_GetCursorTrayPosY(wk->vpara) * ICON_TRAY_YSPC + ICON_POKE_DIFF_Y;
		pos->x <<= FX32_SHIFT;
		pos->y <<= FX32_SHIFT;
		*pri = BGPRI_TRAY_ICON;
	}
}

static void SetupAppearIconActor( ITEMICON_VIEW_WORK* wk, int actID, int itemNo )
{
	if( actID >= 0 )
	{
		VecFx32  mtx;
		u32      bgpri;

		GetAppearIconPosAndPriority( wk, &mtx, &bgpri );

		ArcUtil_ObjCharSet( ARC_ITEMICON, GetItemIndex(itemNo,ITEM_GET_ICON_CGX), OBJTYPE_MAIN,
				IconGraphicTransPosTable[actID].cgx, 0, FALSE, HEAPID_BOX_VIEW );

		ArcUtil_PalSet( ARC_ITEMICON, GetItemIndex(itemNo,ITEM_GET_ICON_PAL), PALTYPE_MAIN_OBJ, 
				IconGraphicTransPosTable[actID].pal*0x20, 0x20, HEAPID_BOX_VIEW );

		CLACT_BGPriorityChg( wk->actor[actID], bgpri );
		BoxAppView_ChangeDrawPriority( wk->actor[actID], ACTPRI_ITEM_ICON );
		CLACT_SetMatrix( wk->actor[actID], &mtx );
	}
}


//======================================================================================================
//======================================================================================================


//------------------------------------------------------------------
/**
 * カーソル動作に合わせてアイコンの表示・消去を開始
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
void BoxAppView_ItemIcon_StartAppear( ITEMICON_VIEW_WORK* wk )
{
	if( wk->enableFlag )
	{
		int actID, itemNo;

		actID = SearchIcon( wk, ITEMICON_STATE_APPEAR );
		if( actID >= 0 )
		{
			ChangeStateIcon( wk, actID, ITEMICON_STATE_DISAPPEAR );
			CLACT_AnmChg( wk->actor[actID], ITEMICON_ANM_DISAPPEAR );
		}

		itemNo = BoxAppVPara_GetStatusPokeItemNumber( wk->vpara );
		if( itemNo != ITEM_DUMMY_ID )
		{
			actID = ReserveIcon( wk, ITEMICON_STATE_APPEAR );
			if( actID >= 0 )
			{
				SetupAppearIconActor( wk, actID, itemNo );
				CLACT_AnmChg( wk->actor[actID], ITEMICON_ANM_APPEAR );
				CLACT_SetDrawFlag( wk->actor[actID], TRUE );
			}
		}
	}
}
//------------------------------------------------------------------
/**
 * カーソル動作に合わせてアイコンの表示・消去の終了待ち
 *
 * @param   wk		ワークポインタ
 *
 * @retval  BOOL	TRUEで終了
 */
//------------------------------------------------------------------
BOOL BoxAppView_ItemIcon_WaitAppear( ITEMICON_VIEW_WORK* wk )
{
	if( wk->enableFlag == FALSE)
	{
		return TRUE;
	}
	else
	{
		int actID = SearchIcon( wk, ITEMICON_STATE_APPEAR );
		if( actID >= 0 )
		{
			if( CLACT_AnmActiveCheck( wk->actor[actID] ) )
			{
				return FALSE;
			}
		}
		actID = SearchIcon( wk, ITEMICON_STATE_DISAPPEAR );
		if( actID >= 0 )
		{
			if( CLACT_AnmActiveCheck( wk->actor[actID] ) )
			{
				return FALSE;
			}
			ChangeStateIcon( wk, actID, ITEMICON_STATE_FREE );
		}
		return TRUE;
	}
}


//======================================================================================================
//======================================================================================================

//------------------------------------------------------
/**
 *	アイコン移動処理関連定数
 */
//------------------------------------------------------
enum {
	ITEMICON_MOVE_FRAMES = BOX_TIMER(6),
};

//------------------------------------------------------
/**
 *	アイコン移動処理タスク用ワーク
 */
//------------------------------------------------------
typedef struct {
	ITEMICON_VIEW_WORK* parent;
	CLACT_WORK_PTR      actor;
	VecFx32   pos;
	VecFx32   nextPos;
	fx32   xac;
	fx32   yac;
	int    nextPriority;
	int    timer;
	int    seq;
}ITEMICON_MOVE_WORK;


//------------------------------------------------------------------
/**
 * アイコン移動処理開始
 *
 * @param   wk		
 * @param   actID		
 * @param   nextPos		
 * @param   frames		
 *
 */
//------------------------------------------------------------------
static void SetupIconMoveTask( ITEMICON_VIEW_WORK* wk, int actID, const VecFx32* nextPos, int nextPriority, int frames  )
{
	ITEMICON_MOVE_WORK*  mwk = sys_AllocMemory( HEAPID_BOX_VIEW, sizeof(ITEMICON_MOVE_WORK) );
	if( mwk )
	{
		mwk->parent = wk;
		mwk->actor = wk->actor[actID];

		mwk->pos = *(CLACT_GetMatrix(mwk->actor));
		mwk->nextPos = *nextPos;
		mwk->xac = (mwk->nextPos.x - mwk->pos.x) / frames;
		mwk->yac = (mwk->nextPos.y - mwk->pos.y) / frames;
		mwk->timer = frames;
		mwk->nextPriority = nextPriority;
		mwk->seq = 0;

		if( BoxAppView_VTaskAdd(ItemIconMoveTask, mwk, TASKPRI_V_SUB) )
		{
			wk->task_cnt++;
		}
		else
		{
			sys_FreeMemoryEz(mwk);
		}
	}
}
//------------------------------------------------------------------
/**
 * アイコン始動処理実行タスク
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void ItemIconMoveTask( TCB_PTR tcb, void* wk_adrs )
{
	ITEMICON_MOVE_WORK* mwk = wk_adrs;

	switch( mwk->seq ){
	case 0:
		if( mwk->timer )
		{
			mwk->pos.x += mwk->xac;
			mwk->pos.y += mwk->yac;
			CLACT_SetMatrix( mwk->actor, &mwk->pos );
			mwk->timer--;
		}
		else
		{
			CLACT_SetMatrix( mwk->actor, &mwk->nextPos );
			mwk->seq++;
		}
		break;

	case 1:
		if( CLACT_AnmActiveCheck(mwk->actor) == FALSE )
		{
			BoxAppView_ChangeDrawPriority(mwk->actor, mwk->nextPriority);
			mwk->parent->task_cnt--;
			TCB_Delete( tcb );
			BoxAppView_IrqMemoryFreeReq( mwk, NULL, NULL );
		}
		break;
	}
}


//======================================================================================================
//======================================================================================================


//------------------------------------------------------------------
/**
 * ポケモンにくっついてるアイコンがカーソルにつかまれる動作開始
 *
 * @param   wk		
 *
 * @retval  BOOL		
 */
//------------------------------------------------------------------
void BoxAppView_ItemIcon_StartCatch( ITEMICON_VIEW_WORK* wk )
{
	if( wk->enableFlag )
	{
		int actID = SearchIcon( wk, ITEMICON_STATE_APPEAR );
		if( actID >= 0 )
		{
			VecFx32  mtx;

			BoxAppView_CursorGetMatrix( wk->cursorWork, &mtx );
			mtx.x += (ICON_CURSOR_DIFF_X << FX32_SHIFT);
			mtx.y += (ICON_CURSOR_DIFF_Y << FX32_SHIFT);

			ChangeStateIcon( wk, actID, ITEMICON_STATE_CAUGHT );
			CLACT_AnmChg( wk->actor[actID], ITEMICON_ANM_CATCH );
			SetupIconMoveTask( wk, actID, &mtx, ACTPRI_CATCH_ICON, ITEMICON_MOVE_FRAMES );
		}
	}
}
//------------------------------------------------------------------
/**
 * カーソルにつかまれる動作終了待ち
 *
 * @param   wk		
 *
 * @retval  BOOL		
 */
//------------------------------------------------------------------
BOOL BoxAppView_ItemIcon_WaitCatch( ITEMICON_VIEW_WORK* wk )
{
	return (wk->task_cnt == 0);
}

//------------------------------------------------------------------
/**
 * ポケモンにくっついてるアイコンが消える動作開始
 *
 * @param   wk		
 *
 * @retval  BOOL		
 */
//------------------------------------------------------------------
void BoxAppView_ItemIcon_StartDisappear( ITEMICON_VIEW_WORK* wk )
{
	if( wk->enableFlag )
	{
		int actID = SearchIcon( wk, ITEMICON_STATE_APPEAR );
		if( actID >= 0 )
		{
			ChangeStateIcon( wk, actID, ITEMICON_STATE_DISAPPEAR );
			CLACT_AnmChg( wk->actor[actID], ITEMICON_ANM_DISAPPEAR );
		}
	}
}
//------------------------------------------------------------------
/**
 * アイコンが消える動作終了待ち
 *
 * @param   wk		
 *
 * @retval  BOOL		
 */
//------------------------------------------------------------------
BOOL BoxAppView_ItemIcon_WaitDisappear( ITEMICON_VIEW_WORK* wk )
{
	if( wk->enableFlag )
	{
		int actID = SearchIcon( wk, ITEMICON_STATE_DISAPPEAR );
		if( actID >= 0 )
		{
			if( CLACT_AnmActiveCheck(wk->actor[actID]) )
			{
				return FALSE;
			}
			ChangeStateIcon( wk, actID, ITEMICON_STATE_FREE );
		}
	}

	return TRUE;
}




//------------------------------------------------------------------
/**
 * つかまれているアイコンがポケモンにセットされる動作開始
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
void BoxAppView_ItemIcon_StartSet( ITEMICON_VIEW_WORK* wk )
{
	if( wk->enableFlag )
	{
		int actID = SearchIcon( wk, ITEMICON_STATE_CAUGHT );
		if( actID >= 0 )
		{
			VecFx32  mtx;
			u32      pri;

			GetAppearIconPosAndPriority( wk, &mtx, &pri );

			ChangeStateIcon( wk, actID, ITEMICON_STATE_APPEAR );
			CLACT_AnmChg( wk->actor[actID], ITEMICON_ANM_SET );
			SetupIconMoveTask( wk, actID, &mtx, ACTPRI_ITEM_ICON, ITEMICON_MOVE_FRAMES );
		}
	}
}
//------------------------------------------------------------------
/**
 * つかまれているアイコンがポケモンにセットされる動作の終了待ち
 *
 * @param   wk		ワークポインタ
 *
 * @retval  BOOL	TRUEで終了
 */
//------------------------------------------------------------------
BOOL BoxAppView_ItemIcon_WaitSet( ITEMICON_VIEW_WORK* wk )
{
	return (wk->task_cnt == 0);
}



//------------------------------------------------------------------
/**
 * つかまれてるアイコンとポケモンにくっついてるアイコンの入れ替え動作開始
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
void BoxAppView_ItemIcon_StartSwap( ITEMICON_VIEW_WORK* wk )
{
	if( wk->enableFlag )
	{
		int caughtActID = SearchIcon( wk, ITEMICON_STATE_CAUGHT );
		int pointActID  = SearchIcon( wk, ITEMICON_STATE_APPEAR );

		if( caughtActID >= 0 && pointActID >= 0 )
		{
			VecFx32  mtx;
			u32      pri;

			GetAppearIconPosAndPriority( wk, &mtx, &pri );
			ChangeStateIcon( wk, caughtActID, ITEMICON_STATE_APPEAR );
			CLACT_AnmChg( wk->actor[caughtActID], ITEMICON_ANM_SET );
			SetupIconMoveTask( wk, caughtActID, &mtx, ACTPRI_ITEM_ICON, ITEMICON_MOVE_FRAMES );


			BoxAppView_CursorGetMatrix( wk->cursorWork, &mtx );
			mtx.x += (ICON_CURSOR_DIFF_X << FX32_SHIFT);
			mtx.y += (ICON_CURSOR_DIFF_Y << FX32_SHIFT);
			ChangeStateIcon( wk, pointActID, ITEMICON_STATE_CAUGHT );
			CLACT_AnmChg( wk->actor[pointActID], ITEMICON_ANM_CATCH );
			SetupIconMoveTask( wk, pointActID, &mtx, ACTPRI_CATCH_ICON, ITEMICON_MOVE_FRAMES );
		}
	}
}
//------------------------------------------------------------------
/**
 * つかまれてるアイコンとポケモンにくっついてるアイコンの入れ替え動作終了待ち
 *
 * @param   wk		ワークポインタ
 *
 * @retval  BOOL	TRUEで終了
 */
//------------------------------------------------------------------
BOOL BoxAppView_ItemIcon_WaitSwap( ITEMICON_VIEW_WORK* wk )
{
	return ( wk->task_cnt == 0 );
}


//------------------------------------------------------------------
/**
 * つかまれてるアイコンか、ポケモンにくっついてるアイコンをバッグにしまう動作
 *（つかまれてるの優先）
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
void BoxAppView_ItemIcon_StartRestore( ITEMICON_VIEW_WORK* wk )
{
	if( wk->enableFlag )
	{
		int actID = SearchIcon( wk, ITEMICON_STATE_CAUGHT );

		if( actID >= 0 )
		{
			CLACT_AnmChg( wk->actor[actID], ITEMICON_ANM_CAUGHT_RESTORE );
			wk->restore_actID = actID;
			return;
		}

		actID = SearchIcon( wk, ITEMICON_STATE_APPEAR );
		if( actID >= 0 )
		{
			CLACT_AnmChg( wk->actor[actID], ITEMICON_ANM_DISAPPEAR );
			wk->restore_actID = actID;
			return;
		}

		wk->restore_actID = ITEMICON_INDEX_NULL;
	}
}
//------------------------------------------------------------------
/**
 * アイコンをバッグにしまう動作の終了待ち
 *
 * @param   wk		ワークポインタ
 *
 * @retval  BOOL	TRUEで終了
 */
//------------------------------------------------------------------
BOOL BoxAppView_ItemIcon_WaitRestore( ITEMICON_VIEW_WORK* wk )
{
	if( wk->enableFlag )
	{
		if( wk->restore_actID != ITEMICON_INDEX_NULL )
		{
			if( CLACT_AnmActiveCheck( wk->actor[wk->restore_actID] ) )
			{
				return FALSE;
			}
			ChangeStateIcon( wk, wk->restore_actID, ITEMICON_STATE_FREE );
			wk->restore_actID = ITEMICON_INDEX_NULL;
		}
	}
	return TRUE;
}


//======================================================================================================
//======================================================================================================


//------------------------------------------------------------------
/**
 * カーソル移動に合わせて描画位置更新
 *
 * @param   wk		ワークポインタ
 * @param   mtx		カーソルの位置
 *
 */
//------------------------------------------------------------------
void BoxAppView_ItemIcon_MoveCaughtIcon( ITEMICON_VIEW_WORK* wk, const VecFx32* cursorPos )
{
	if( wk->enableFlag )
	{
		int actID = SearchIcon( wk, ITEMICON_STATE_CAUGHT );
		if( actID >= 0 )
		{
			VecFx32 pos = *cursorPos;
			pos.x += (ICON_CURSOR_DIFF_X << FX32_SHIFT);
			pos.y += (ICON_CURSOR_DIFF_Y << FX32_SHIFT);
			CLACT_SetMatrix( wk->actor[actID], &pos );
		}
	}
}
//------------------------------------------------------------------
/**
 * カーソルにつかまれているアイコンのBGプライオリティ変更
 *
 * @param   wk		ワークポインタ
 * @param   pri		BGプライオリティ
 *
 */
//------------------------------------------------------------------
void BoxAppView_ItemIcon_ChangePriorityCaughtIcon( ITEMICON_VIEW_WORK* wk, u32 pri )
{
	if( wk->enableFlag )
	{
		int actID = SearchIcon( wk, ITEMICON_STATE_CAUGHT );
		if( actID >= 0 )
		{
			CLACT_BGPriorityChg( wk->actor[actID], pri );
		}
	}
}
