//============================================================================================
/**
 * @file	boxv_cursor.c
 * @brief	�{�b�N�X�����ʁ@�`�扺�����i�g���C�֘A�j
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
	// �ړ��\�Ȕ͈́B��������t����o�Ă���
	CURSOR_VISIBLE_X_MIN = 70,
	CURSOR_VISIBLE_X_MAX = 256 + 16,
	CURSOR_VISIBLE_Y_MIN = -24,			// �͂�ł���A�C�R�������S�ɉB��邭�炢
	CURSOR_VISIBLE_Y_MAX = 192 + 16,

	CURSOR_VISIBLE_X_MAX_FX32 = CURSOR_VISIBLE_X_MAX << FX32_SHIFT,
	CURSOR_VISIBLE_X_MIN_FX32 = CURSOR_VISIBLE_X_MIN << FX32_SHIFT,
	CURSOR_VISIBLE_Y_MAX_FX32 = CURSOR_VISIBLE_Y_MAX << FX32_SHIFT,
	CURSOR_VISIBLE_Y_MIN_FX32 = CURSOR_VISIBLE_Y_MIN << FX32_SHIFT,

	// �ړ��t���[����
	CURSOR_MOVE_TIME = BOX_TIMER(3),		//< �ʏ펞
	CURSOR_LOOP_MOVE_TIME = BOX_TIMER(6),	//< �N���b�Ɖ���Ĕ��Α�����o�Ă��鎞

	// ���ݓ���t���[����
	CURSOR_CATCHMOVE_DOWN_TIME = BOX_TIMER(3),	// ������Ƃ�
	CURSOR_CATCHMOVE_UP_TIME = BOX_TIMER(3),	// �オ��Ƃ�
	CURSOR_CATCHMOVE_DIPTH = -(CURSOR_ICON_YDIFF - CURSOR_CATCHICON_YDIFF),		// �㉺����[���i�h�b�g�j


	// ����ւ�����t���[����
	CURSOR_SWAPMOVE_TIME = BOX_TIMER(6),
	CURSOR_SWAPMOVE_WIDTH = 12,	// ���Ƀu���b�ƍL���镝�i�h�b�g�j

	// �{�^����������
	PUSHMOVE_START_TIME = BOX_TIMER(2),
	PUSHMOVE_DOWN_TIME = BOX_TIMER(1),
	PUSHMOVE_RETURN_TIME = BOX_TIMER(2),
	PUSHMOVE_UP_RANGE = -2,
	PUSHMOVE_DOWN_RANGE = 6,
	PUSHMOVE_RETURN_RANGE = -(PUSHMOVE_UP_RANGE+PUSHMOVE_DOWN_RANGE),

	MOVE_SEQ_END = 255,

	CURSOR_SHADOW_DIFF = 24,

	// ���A�N�^�[�\���ʒu
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
 * ������
 *
 * @param   wk		
 * @param   vwk		
 * @param   vpara		
 * @param   actsys		
 *
 * @retval  BOOL		TRUE�Ő���
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
 * �n�a�i�Z�b�g�A�b�v����
 *
 * @param   wk		���[�N�|�C���^
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

	// ��ʕ��A���A�͂�ł���A�C�R��������΂���ɍ��킹�����������K�v�ɂȂ�
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



	// ����Ă�l���[�h��������F��ς��Ă���
	BoxAppView_CursorExpertModeChange( wk );
}
//---------------------------------------------------------------
/**
 * �͂�ł���|�P�����f�[�^���Q�Ƃ��ăA�C�R�����쐬
 *
 * @param   wk		���[�N�|�C���^
 *
 */
//---------------------------------------------------------------
static void SetupCatchPokeObj( CURSOR_VIEW_WORK* wk )
{
	// ����A�����I���̂܂܉�ʕ��A�������s���\���͍l�����Ă��Ȃ��B
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
 * �I��
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
 * ��ʂ�������Ɖ���ċt����o�Ă��铮��ɂ��邩�`�F�b�N
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
 * �ړ������X�^�[�g
 *
 * @param   wk		���[�N�|�C���^
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
 * �ړ������I���҂�
 *
 * @param   wk		���[�N�|�C���^	
 *
 * @retval  BOOL	TRUE�ŏI��
 */
//------------------------------------------------------------------
BOOL BoxAppView_CursorMoveWait( CURSOR_VIEW_WORK* wk )
{
	return wk->move_timer == 0;
}
//------------------------------------------------------------------
/**
 * �ړ������^�X�N
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
 * �|�P�����A�C�R�������ޓ���X�^�[�g
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
 * �|�P�����A�C�R�������ޓ���I���҂�
 *
 * @param   wk		
 *
 * @retval  BOOL	TRUE�ŏI��
 */
//------------------------------------------------------------------
BOOL BoxAppView_CursorCatchWait( CURSOR_VIEW_WORK* wk )
{
	return wk->move_seq == MOVE_SEQ_END;
}
//------------------------------------------------------------------
/**
 * �|�P�����A�C�R�������ޓ���^�X�N
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
 * �|�P�����A�C�R����u������X�^�[�g
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
 * �|�P�����A�C�R����u������I���҂�
 *
 * @param   wk		
 *
 * @retval  BOOL	TRUE�ŏI��
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
 * �|�P�����A�C�R����u������^�X�N
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
 * �|�P�����A�C�R�������ւ��铮��X�^�[�g
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
 * �|�P�����A�C�R�������ւ��铮��I���҂�
 *
 * @param   wk		
 *
 * @retval  BOOL	TRUE�ŏI��
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
 *  �A�C�R������ւ�����^�X�N�p���[�N
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
 * �A�C�R������ւ�����^�X�N�Z�b�g
 *
 * @param   wk			���[�N�|�C���^
 * @param   act			�A�N�^�[�|�C���^
 * @param   end_y		�ړ���x���W
 * @param   sindir		���ړ������i1 or -1�j
 * @param   nextpri		�ړ���̃v���C�I���e�B
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
 * �A�C�R������ւ�����^�X�N�̏I���҂�
 *
 * @param   wk			���[�N�|�C���^
 *
 * @retval  BOOL		TRUE�ŏI��
 */
//------------------------------------------------------------------
static BOOL SwapIconMoveTaskEndCheck( CURSOR_VIEW_WORK* wk )
{
	return wk->move_taskflag == FALSE;
}
//------------------------------------------------------------------
/**
 * �A�C�R������ւ�����^�X�N�I���i�^�X�N�{�̂���̂݌Ă΂��j
 *
 * @param   wk			���[�N�|�C���^
 * @param   tcb			TCB�|�C���^
 * @param   wk_adrs		TCB���[�N�A�h���X
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
 * �A�C�R������ւ�����^�X�N�{��
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
 * �{�^������������J�n
 *
 * @param   wk		���[�N�|�C���^
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
 * �{�^������������I���҂�
 *
 * @param   wk		���[�N�|�C���^
 *
 * @retval  BOOL	TRUE�ŏI��
 */
//------------------------------------------------------------------
BOOL BoxAppView_CursorButtonPushActionWait( CURSOR_VIEW_WORK* wk )
{
	return wk->move_taskflag == FALSE;
}
//------------------------------------------------------------------
/**
 * �{�^������������^�X�N
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
 * �{�^���𗣂�����J�n
 *
 * @param   wk		���[�N�|�C���^
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
 * �{�^���𗣂�����I���҂�
 *
 * @param   wk			���[�N�|�C���^
 *
 * @retval  BOOL		TRUE�ŏI��
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
 * �{�^���𗣂�����^�X�N
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
 * ����ł���A�C�R�����{�b�N�X�ɗa����
 *
 * @param   wk		���[�N�|�C���^
 *
 */
//------------------------------------------------------------------
void BoxAppView_CursorCatchIconAzukeru( CURSOR_VIEW_WORK* wk )
{
	// ���ݕ\�����̃g���C�ɗa����ꍇ�̓A�C�R���\�����X�V
	if( wk->vpara->azukeruTrayNumber == BoxAppVPara_GetTrayBoxNumber( wk->vpara ) )
	{
		BoxAppView_TrayUpdateIcon( wk->trayWork );
	}
	CatchIconDataDelete( wk );
	CLACT_AnmChg( wk->act, ANM_NORMAL );
}

//------------------------------------------------------------------
/**
 * ����ł���A�C�R���𓦂�������X�^�[�g
 *
 * @param   wk		���[�N�|�C���^
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
 * ����ł���A�C�R���𓦂�������̏I���҂�
 *
 * @param   wk			���[�N�|�C���^
 *
 * @retval  BOOL		TRUE�ŏI��
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
 * �A�N�^�[��BG��ײ��è���莝���g���C���[�h��
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
 * �A�N�^�[��BG��ײ��è��ʏ탂�[�h��
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
 * �X�e�[�^�X�\�����|�P�����A�C�R���̃}�[�L���O�p�X�e�[�^�X���X�V
 *
 * @param   wk		���[�N�|�C���^
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
 * �A�C�R�����i�荞�݃��[�h�\���ɑΉ�
 *
 * @param   wk		���[�N�|�C���^
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
 * �A�C�R���̃A�C�e�������X�V
 *
 * @param   wk			���[�N�|�C���^
 * @param   itemNumber	�A�C�e���i���o�[
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
 * ����Ă�l���[�h�̃I���I�t�ɉ����ăJ�[�\���F�ύX
 *
 * @param   wk		���[�N�|�C���^
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
 * �A�C�R���͈̔͑I�������J�n
 *
 * @param   wk		���[�N�|�C���^
 *
 */
//------------------------------------------------------------------
void BoxAppView_CursorAleaSelectStart( CURSOR_VIEW_WORK* wk )
{
	CLACT_AnmChg( wk->act, ANM_PAR );
}
//------------------------------------------------------------------
/**
 * �J�[�\���A�N�^�[�ʒu��Ԃ�
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
/* �A�C�e���A�C�R�������֘A                                                                           */
/*====================================================================================================*/


//------------------------------------------------------------------
/**
 * �A�C�e�������ޓ���J�n
 *
 * @param   wk		���[�N�|�C���^
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
 * �A�C�e�������ޓ���I���҂�
 *
 * @param   wk		���[�N�|�C���^
 *
 * @retval  BOOL	TRUE�ŏI��
 */
//------------------------------------------------------------------
BOOL BoxAppView_CursorItemCatchWait( CURSOR_VIEW_WORK* wk )
{
	return (wk->move_taskflag == FALSE);
}
//------------------------------------------------------------------
/**
 * �A�C�e�������ޓ���̎��s�^�X�N
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
 * �A�C�e�����������铮��J�n
 *
 * @param   wk		���[�N�|�C���^
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
 * �A�C�e�����������铮��I���҂�
 *
 * @param   wk		���[�N�|�C���^
 *
 * @retval  BOOL	TRUE�ŏI��
 */
//------------------------------------------------------------------
BOOL BoxAppView_CursorItemSetWait( CURSOR_VIEW_WORK* wk )
{
	return (wk->move_taskflag == FALSE);
}
//------------------------------------------------------------------
/**
 * �A�C�e�����������铮��̎��s�^�X�N
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
 * �A�C�e�����Ƃ肩���铮��J�n
 *
 * @param   wk		���[�N�|�C���^
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
 * �A�C�e�����Ƃ肩���铮��̏I���҂�
 *
 * @param   wk		���[�N�|�C���^
 *
 * @retval  BOOL	TRUE�ŏI��
 */
//------------------------------------------------------------------
BOOL BoxAppView_CursorItemSwapWait( CURSOR_VIEW_WORK* wk )
{
	return (wk->move_taskflag == FALSE);
}
//------------------------------------------------------------------
/**
 * �A�C�e�����Ƃ肩���铮��̎��s�^�X�N
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
 * �A�C�e�����o�b�O�ɖ߂������O�ɃJ�[�\����ԕύX���Ă���
 *
 * @param   wk		���[�N�|�C���^
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
 * �A�C�e�����o�b�O�ɖ߂��������I��������̏���
 *
 * @param   wk		���[�N�|�C���^
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
/* �������牺�̓��[�J��                                                                               */
/*====================================================================================================*/


//------------------------------------------------------------------
/**
 * �J�[�\���A�N�^�[�̈ړ�����W�擾
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
 * �J�[�\���A�N�^�[�̍��W�Z�b�g�i����ł�A�C�R��������Γ���������j
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
 * ������ꏊ�̃A�C�R���f�[�^��͂�ł���A�C�R���p���[�N�Ɉړ�
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void PointIconDataToCatchIconData( CURSOR_VIEW_WORK* wk )
{
	if( BoxAppVPara_GetCursorArea( wk->vpara ) == CURSOR_AREA_TRAY )
	{
		// �P�̂���
		if( BoxAppVPara_CheckAreaSelectSinglePoke( wk->vpara ) )
		{
			u32 pos = BoxAppVPara_GetCursorTrayPos( wk->vpara );
			BoxAppView_TrayMoveIconData( wk->trayWork, pos, OBJCHAR_MOVING_SINGLE_ICON_POS, wk->catch_icon );
			wk->catch_icon_count = 1;
			wk->iconOfs[0].x = (CURSOR_CATCHICON_XDIFF * FX32_ONE);
			wk->iconOfs[0].y = (CURSOR_CATCHICON_YDIFF * FX32_ONE);
		}
		// �͈͑I������
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
 * �͂�ł���A�C�R���v���C�I���e�B�𒲐����J�[�\���ɒǐ�������
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
 * ����ł���A�C�R���f�[�^��������ꏊ�p�̃��[�N�Ɉړ�������
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void CatchIconDataPut( CURSOR_VIEW_WORK* wk )
{
	if( BoxAppVPara_GetCursorArea( wk->vpara ) == CURSOR_AREA_TRAY )
	{
		// �P�̂���
		if( BoxAppVPara_CheckAreaSelectSinglePoke( wk->vpara ) )
		{
			u32 pos = BoxAppVPara_GetCursorTrayPos( wk->vpara );
			BoxAppView_TrayPutIconData( wk->trayWork, pos, wk->catch_icon );
		}
		// �͈͑I������
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
 * ����ł���A�C�R���f�[�^�ƍ�����ꏊ�̃A�C�R���f�[�^�����ւ���
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void CatchIconDataSwap( CURSOR_VIEW_WORK* wk )
{
	// �ǂ���� wk->catch_icon[1] �����ւ��p�e���|�����Ƃ��Ďg�p�B
	// ����ւ��͒P�̓��m�ł����������Ȃ��̂ł���ő��v�Ȃ͂��B
	if( BoxAppVPara_GetCursorArea( wk->vpara ) == CURSOR_AREA_TRAY )
	{
		u32 pos = BoxAppVPara_GetCursorTrayPos( wk->vpara );

		// �A�C�R���L�����f�[�^����ւ����̃p�V��΍�B���̃L�����ʒu�Ƃ͑S���Ⴄ�ꏊ���ꎞ�I�ɎQ�Ƃ����Ă���
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

		// �A�C�R���L�����f�[�^����ւ����̃p�V��΍�B���̃L�����ʒu�Ƃ͑S���Ⴄ�ꏊ���ꎞ�I�ɎQ�Ƃ����Ă���
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
 * �͂�ł���A�C�R���f�[�^��؂藣��
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
 * �͂�ł���A�C�R���f�[�^���폜
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
 * �|�C���g���Ă���A�C�R���̃A�N�^�[�|�C���^��Ԃ�
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