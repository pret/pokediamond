//============================================================================================
/**
 * @file	boxv_status.c
 * @brief	ボックス操作画面　描画下請け（ポケモンステータス面）
 * @author	taya
 * @date	2005.09.24
 */
//============================================================================================
#include  "common.h"
#include  "system\arc_util.h"
#include  "system\fontproc.h"
#include  "battle\wazatype_icon.h"

#include  "box_arc.h"
#include  "box_view.h"
#include  "box_common.h"


extern u32 WazaTypeIcon_CgrIDGet(int waza_type);
extern u32 WazaTypeIcon_PlttIDGet(void);
extern u32 WazaTypeIcon_CellIDGet(void);
extern u32 WazaTypeIcon_CellAnmIDGet(void);
extern u8 WazaTypeIcon_PlttOffsetGet(int waza_type);
extern u32 WazaTypeIcon_ArcIDGet(void);

//------------------------------------------------------------
/**
 *  consts
 */
//------------------------------------------------------------

/// ウィンドウタイプ
enum {
	WIN_KIND,		///< ポケモン種類名
	WIN_NUMBER,		///< 図鑑No
	WIN_NICKNAME,	///< ニックネーム（レベル・性別共通）
	WIN_INFO,		///< 追加情報

	WIN_MAX,
};

/// ウィンドウパラメータ（キャラサイズ系）
enum {
	WIN_KIND_CHAROFS = 32*9,
	WIN_KIND_X = 0,
	WIN_KIND_Y = 1,
	WIN_KIND_WIDTH = 10,
	WIN_KIND_HEIGHT = 2,
	WIN_KIND_SIZE = WIN_KIND_WIDTH * WIN_KIND_HEIGHT,

	WIN_NUMBER_CHAROFS = WIN_KIND_CHAROFS + WIN_KIND_SIZE,
	WIN_NUMBER_X = 5,
	WIN_NUMBER_Y = 3,
	WIN_NUMBER_WIDTH = 5,
	WIN_NUMBER_HEIGHT = 1,
	WIN_NUMBER_SIZE = WIN_NUMBER_WIDTH * WIN_NUMBER_HEIGHT,

	WIN_NICKNAME_CHAROFS = WIN_NUMBER_CHAROFS + WIN_NUMBER_SIZE,
	WIN_NICKNAME_X = 0,
	WIN_NICKNAME_Y = 16,
	WIN_NICKNAME_WIDTH = 10,
	WIN_NICKNAME_HEIGHT = 3,
	WIN_NICKNAME_SIZE = WIN_NICKNAME_WIDTH * WIN_NICKNAME_HEIGHT,

	WIN_INFO_CHAROFS = WIN_NICKNAME_CHAROFS + WIN_NICKNAME_SIZE,
	WIN_INFO_X = 1,
	WIN_INFO_Y = 21,
	WIN_INFO_WIDTH = 12,
	WIN_INFO_HEIGHT = 4,		// 内部バッファはスクロール領域分も作成しておく
	WIN_INFO_DISP_HEIGHT = 2,	// 実際表示するのはこんだけ
	WIN_INFO_SIZE = WIN_INFO_WIDTH * WIN_INFO_HEIGHT,

};

/// ウィンドウパラメータ（パレットデータ系）
enum {
	WIN_KIND_PALNUMBER = PAL_MAIN_STATUS2,
	WIN_KIND_PAL_GROUND = 0x0f,
	WIN_KIND_PAL_LETTER = 0x09,
	WIN_KIND_PAL_SHADOW = 0x06,

	WIN_NUMBER_PALNUMBER = PAL_MAIN_STATUS2,
	WIN_NUMBER_PAL_GROUND = 0x0f,
	WIN_NUMBER_PAL_LETTER = 0x09,
	WIN_NUMBER_PAL_SHADOW = 0x06,

	WIN_NICKNAME_PALNUMBER = PAL_MAIN_STATUS4,
	WIN_NICKNAME_PAL_GROUND = 0x0f,
	WIN_NICKNAME_PAL_LETTER = 0x01,
	WIN_NICKNAME_PAL_SHADOW = 0x02,

	WIN_SEX_PALNUMBER = PAL_MAIN_STATUS4,
	WIN_SEX_PAL_GROUND = 0x0f,
	WIN_MALE_PAL_LETTER = 0x07,
	WIN_MALE_PAL_SHADOW = 0x08,
	WIN_FEMALE_PAL_LETTER = 0x03,
	WIN_FEMALE_PAL_SHADOW = 0x04,


	WIN_INFO_PALNUMBER = PAL_MAIN_STATUS2,
	WIN_INFO_PAL_GROUND = 0x00,
	WIN_INFO_PAL_LETTER = 0x09,
	WIN_INFO_PAL_SHADOW = 0x06,

};

/// 描画レイアウト
enum {
	POKENAME_WRITE_X = 2,
	POKENAME_WRITE_Y = 0,

	POKENO_WRITE_X = 0,
	POKENO_WRITE_Y = 0,

	NICKNAME_WRITE_X = 2,
	NICKNAME_WRITE_Y = 0,

	SEX_WRITE_X = 70,
	SEX_WRITE_Y = 0,

	LV_WRITE_X = 0,
	LV_WRITE_Y = 16,

	INFO_WRITE_X = 0,
	INFO_WRITE_Y = 2,

	POKEIMAGE_WRITE_X = 44,
	POKEIMAGE_WRITE_Y = 84,

	POKEMARK_WRITE_X = 4,
	POKEMARK_WRITE_Y = 19,

	INFOBACK_OBJ_X = 56,
	INFOBACK_OBJ_Y = 176,

	TYPEICON_OBJ_XSPC = 36,
	TYPEICON_OBJ_YSPC = 16,
	TYPEICON_OBJ_X = 24,
	TYPEICON_OBJ_Y = INFOBACK_OBJ_Y,

	TYPEICON_ACTOR_MAX = 2,

};

/// キャラ配置
enum {
	CHARPOS_MARK_ON = 0x98,
	CHARPOS_MARK_OFF = 0x84,
};

//==============================================================
// タスク制御ワーク
//==============================================================
typedef struct {
	u16					seq;
	u16					subseq;
	u16					timer;
	u16					scroll;
	STATUS_VIEW_WORK*	wk;
}INFOWIN_TASK_WORK;

//==============================================================
// Prototype
//==============================================================
static void ActorSetup( STATUS_VIEW_WORK* wk );
static void TaskSetup( STATUS_VIEW_WORK* wk );
static void TaskDelete( STATUS_VIEW_WORK* wk );
static void InfoWinControlTaskReset( STATUS_VIEW_WORK* wk );
static void InfoWinControlTaskPause( STATUS_VIEW_WORK* wk );
static void InfoWinControlTask(TCB_PTR tcb, void* wk_adrs );
static void TypeIconScroll( STATUS_VIEW_WORK* wk, fx32 vector );
static void TypeIconDispOff( STATUS_VIEW_WORK* wk );
static void InfoWinCharSetup( INFOWIN_TASK_WORK* taskwk );
static void InfoWinCharSetupSub( GF_BGL_BMPWIN* win, STATUS_VIEW_WORK* wk, u32 subseq, u32 vpos );
static void StatusPrintCore( STATUS_VIEW_WORK* wk );
static void MarkingScreenSet( STATUS_VIEW_WORK* wk, u8 mark );



//------------------------------------------------------------------
/**
 * 初期化処理
 *
 * @param   wk			ワークポインタ
 * @param   vwk			描画ワーク
 * @param   vpara		描画パラメータ
 * @param   bgl			BGLシステムワーク
 * @param   actsys		アクターシステムワーク
 *
 * @retval  BOOL		TRUEで成功
 */
//------------------------------------------------------------------
BOOL BoxAppView_StatusInit( STATUS_VIEW_WORK* wk, BOXAPP_VIEW_WORK* vwk, const BOXAPP_VPARAM* vpara, GF_BGL_INI* bgl, CLACT_SET_PTR actsys, const MSGDATA_MANAGER* msgman )
{
	int i;

	if( BoxAppVPara_GetBoxMode(vpara) == BOX_MODE_COMPARE )
	{
		wk->enableFlag = FALSE;
		return TRUE;
	}

	wk->vwk = vwk;
	wk->bgl = bgl;
	wk->vpara = vpara;
	wk->actsys = actsys;
	wk->bmpwin = NULL;
	wk->task = NULL;

	wk->sprite = NULL;
	wk->spriteMan = BoxAppView_GetSpriteManager( vwk );

	wk->numfontNo = NUMFONT_Create(WIN_NUMBER_PAL_LETTER, WIN_NUMBER_PAL_SHADOW, WIN_NUMBER_PAL_GROUND, HEAPID_BOX_VIEW );
	wk->numfontLv = NUMFONT_Create(WIN_NICKNAME_PAL_LETTER, WIN_NICKNAME_PAL_SHADOW, WIN_NICKNAME_PAL_GROUND, HEAPID_BOX_VIEW );

	wk->infobackCellBuf = ArcUtil_CellBankDataGet(ARC_BOX_GRA, NARC_box_info_back_lz_ncer, TRUE, &(wk->infobackCellData), HEAPID_BOX_VIEW);
	wk->infobackAct = NULL;

	wk->strMale = MSGMAN_AllocString( msgman, msg_boxmes_01_22 );
	wk->strFemale = MSGMAN_AllocString( msgman, msg_boxmes_01_23 );

	wk->typeIconCellBuf = ArcUtil_CellBankDataGet(WazaTypeIcon_ArcIDGet(), WazaTypeIcon_CellIDGet(), TRUE, &(wk->typeIconCellData), HEAPID_BOX_VIEW);
	for(i=0; i<TYPEICON_ACTOR_MAX; i++)
	{
		wk->typeIconAct[i] = NULL;
	}

	wk->enableFlag = TRUE;

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
void BoxAppView_StatusQuit( STATUS_VIEW_WORK* wk )
{
	int i;

	if( wk->enableFlag == FALSE )
	{
		return;
	}

	if( wk->bmpwin )
	{
		for(i = 0; i < WIN_MAX; i++)
		{
			GF_BGL_BmpWinDel( &wk->bmpwin[i] );
		}
		sys_FreeMemoryEz( wk->bmpwin );
		wk->bmpwin = NULL;
	}

	if( wk->numfontNo ){
		NUMFONT_Delete( wk->numfontNo );
	}
	if( wk->numfontLv ){
		NUMFONT_Delete( wk->numfontLv );
	}
	if( wk->strMale )
	{
		STRBUF_Delete(wk->strMale);
	}
	if( wk->strFemale )
	{
		STRBUF_Delete(wk->strFemale);
	}


	if( wk->sprite )
	{
		SoftSpriteDel( wk->sprite );
		wk->sprite = NULL;
	}

	if( wk->infobackCellBuf )
	{
		sys_FreeMemoryEz( wk->infobackCellBuf );
	}

	if( wk->infobackAct )
	{
		CLACT_Delete( wk->infobackAct );
	}

	if( wk->typeIconCellBuf )
	{
		sys_FreeMemoryEz( wk->typeIconCellBuf );
	}

	for(i=0; i<TYPEICON_ACTOR_MAX; i++)
	{
		if(wk->typeIconAct[i] != NULL)
		{
			CLACT_Delete(wk->typeIconAct[i]);
		}
	}

	TaskDelete( wk );
}
void BoxAppView_StatusVBlank( STATUS_VIEW_WORK* wk )
{
	if( wk->enableFlag )
	{
		SoftSpriteTextureTrans(wk->spriteMan);
	}
}

//------------------------------------------------------------------
/**
 * スプライト表示の前準備を開始
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
void BoxAppView_Status_StartSoftSpritePreparation( STATUS_VIEW_WORK* wk )
{
	// スプライト作成１回目だけパシるので、最初に作って消しておく
	SOFT_SPRITE_ARC  spriteArc;
	PokeGraArcDataGet( &spriteArc, 1, 0, 0, 0, 0, 0 );
	wk->sprite = SoftSpriteAdd( wk->spriteMan, &spriteArc, POKEIMAGE_WRITE_X, POKEIMAGE_WRITE_Y, 0, 0, NULL, NULL );
}
//------------------------------------------------------------------
/**
 * スプライト表示の前準備終了待ち
 *
 * @param   wk		
 *
 * @retval  BOOL		
 */
//------------------------------------------------------------------
BOOL BoxAppView_Status_WaitSoftSpritePreparation( STATUS_VIEW_WORK* wk )
{
	if( wk->sprite )
	{
		SoftSpriteDel( wk->sprite );
		wk->sprite = NULL;
		return FALSE;
	}
	return TRUE;
}


//------------------------------------------------------------------
/**
 * ステータス表示用BGセットアップ
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
void BoxAppView_StatusSetup( STATUS_VIEW_WORK* wk )
{
	static const BMPWIN_DAT  windat[] = {
		{
			FRM_MAIN_STATUS,
			WIN_KIND_X, WIN_KIND_Y, WIN_KIND_WIDTH, WIN_KIND_HEIGHT,
			WIN_KIND_PALNUMBER, WIN_KIND_CHAROFS
		},{
			FRM_MAIN_STATUS,
			WIN_NUMBER_X, WIN_NUMBER_Y, WIN_NUMBER_WIDTH, WIN_NUMBER_HEIGHT,
			WIN_KIND_PALNUMBER, WIN_NUMBER_CHAROFS
		},{
			FRM_MAIN_STATUS,
			WIN_NICKNAME_X, WIN_NICKNAME_Y, WIN_NICKNAME_WIDTH, WIN_NICKNAME_HEIGHT,
			WIN_NICKNAME_PALNUMBER, WIN_NICKNAME_CHAROFS
		},{
			FRM_MAIN_STATUS,
			WIN_INFO_X, WIN_INFO_Y, WIN_INFO_WIDTH, WIN_INFO_HEIGHT,
			WIN_KIND_PALNUMBER, WIN_INFO_CHAROFS
		}
	};
	extern void GF_BGL_BmpWinMakeScrnLimited( GF_BGL_BMPWIN* win, u32 width, u32 height );


	if( wk->enableFlag == FALSE )
	{
		return;
	}

	wk->bmpwin = GF_BGL_BmpWinAllocGet( HEAPID_BOX_VIEW, WIN_MAX );
	if( wk->bmpwin )
	{
		int i;

		for(i = 0; i < WIN_MAX; i++)
		{
			GF_BGL_BmpWinAddEx( wk->bgl, &wk->bmpwin[i], &windat[i] );
			if( i != WIN_INFO )
			{
				GF_BGL_BmpWinMakeScrn( &wk->bmpwin[i] );
			}
			else
			{
				GF_BGL_BmpWinMakeScrnLimited( &wk->bmpwin[i], WIN_INFO_WIDTH, WIN_INFO_DISP_HEIGHT );
			}
		}
		GF_BGL_LoadScreenReq( wk->bgl, FRM_MAIN_STATUS );
	}

	ActorSetup( wk );
	TaskSetup( wk );
}
//------------------------------------------------------------------
/**
 * アクターのセットアップ
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
static void ActorSetup( STATUS_VIEW_WORK* wk )
{
	NNSG2dImageProxy  proxy;
	CLACT_HEADER      header;

	u32  iconArcIdx, iconArcCgrDatIdx, i;


	/* ポケモンタイプアイコン作成 */
	iconArcIdx = WazaTypeIcon_ArcIDGet();
	iconArcCgrDatIdx = WazaTypeIcon_CgrIDGet(2);

	ArcUtil_PalSet( iconArcIdx, WazaTypeIcon_PlttIDGet(), PALTYPE_MAIN_OBJ, OBJPAL_TYPE*0x20,
		0x20*3, HEAPID_BOX_VIEW );

	for(i=0; i<TYPEICON_ACTOR_MAX; i++)
	{
		NNS_G2dInitImageProxy( &proxy );
		ArcUtil_CharSysLoadSyncroMappingMode( iconArcIdx, iconArcCgrDatIdx, TRUE, CHAR_MAP_1D, 0,
						NNS_G2D_VRAM_TYPE_2DMAIN, (OBJCHAR_POKETYPE_POS+(OBJCHAR_POKETYPE_HALF_SIZE*i))*0x20,
						HEAPID_BOX_VIEW, &proxy );
		BoxAppView_SetActHeader( &header, &proxy, BoxAppView_GetObjPlttProxy( wk->vwk ),
			wk->typeIconCellData, NULL, BGPRI_TYPE_ICON );

		wk->typeIconAct[i] = BoxAppView_AddActor( wk->actsys, &header, TYPEICON_OBJ_X+TYPEICON_OBJ_XSPC*i, TYPEICON_OBJ_Y,
						ACTPRI_TYPE_ICON, NNS_G2D_VRAM_TYPE_2DMAIN );
		GF_ASSERT(wk->typeIconAct[i]!=NULL);


		CLACT_SetDrawFlag( wk->typeIconAct[i], FALSE );
	}

	/*
		ここで作成されているＯＢＪは、アイテム名／ポケモンタイプ名等を
		切り替え表示するウィンドウの背景として使用。ウィンドウ自体は背景色を抜き色で描く。
	*/
	NNS_G2dInitImageProxy( &proxy );
	ArcUtil_CharSysLoad( ARC_BOX_GRA, NARC_box_info_back_lz_ncgr, TRUE, CHAR_MAP_1D, 0,
					NNS_G2D_VRAM_TYPE_2DMAIN, OBJCHAR_INFOBACK_POS*0x20, HEAPID_BOX_VIEW, &proxy );

	BoxAppView_SetActHeader( &header, &proxy, BoxAppView_GetObjPlttProxy( wk->vwk ),
		wk->infobackCellData, NULL, BGPRI_INFO_BACK );

	wk->infobackAct = BoxAppView_AddActor( wk->actsys, &header, INFOBACK_OBJ_X, INFOBACK_OBJ_Y, ACTPRI_INFO_BACK,
		NNS_G2D_VRAM_TYPE_2DMAIN );

}

//======================================================================================================
// ステータス表示ポケモンの追加情報表示ウィンドウ表示制御タスク
//======================================================================================================

enum {
	TSEQ_IDLE,
	TSEQ_SETUP,
	TSEQ_WAIT,
	TSEQ_SCROLL,
	TSEQ_PAUSE,
};

enum {
	TSUBSEQ_ITEM,
	TSUBSEQ_TYPE,
	TSUBSEQ_CHARACTER,
	TSUBSEQ_ABILITY,

	TSUBSEQ_END,
};

enum {
	STATUS_SCROLL_WAIT = 80,
	STATUS_SCROLL_SPEED = 4,
	STATUS_SCROLL_MAX = 16,
};


//------------------------------------------------------------------
/**
 * タスクのセットアップ
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
static void TaskSetup( STATUS_VIEW_WORK* wk )
{
	if( wk->task == NULL )
	{
		INFOWIN_TASK_WORK* taskwk = sys_AllocMemory( HEAPID_BOX_VIEW, sizeof(INFOWIN_TASK_WORK) );
		if( taskwk )
		{
			const BOXAPP_STATUS_POKE* poke = BoxAppVpara_GetStatusPokeData( wk->vpara );
			taskwk->seq = (poke->tamago_flag)? TSEQ_PAUSE : TSEQ_IDLE;
			taskwk->wk = wk;
			wk->task = TCB_Add( InfoWinControlTask, taskwk, TASKPRI_VIEW_COMMAND );
		}
		else
		{
			GF_ASSERT(0);
		}
	}
}
//------------------------------------------------------------------
/**
 * タスクの削除
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
static void TaskDelete( STATUS_VIEW_WORK* wk )
{
	if( wk->task )
	{
		sys_FreeMemoryEz( TCB_GetWork( wk->task ) );
		TCB_Delete( wk->task );
		wk->task = NULL;
	}
}
static void InfoWinControlTaskReset( STATUS_VIEW_WORK* wk )
{
	INFOWIN_TASK_WORK* taskwk = TCB_GetWork( wk->task );
	if(taskwk)
	{
		const BOXAPP_STATUS_POKE* poke = BoxAppVpara_GetStatusPokeData( wk->vpara );
		taskwk->seq = (poke->tamago_flag)? TSEQ_PAUSE : TSEQ_IDLE;
		TypeIconDispOff( wk );
	}
}
static void InfoWinControlTaskPause( STATUS_VIEW_WORK* wk )
{
	INFOWIN_TASK_WORK* taskwk = TCB_GetWork( wk->task );
	if(taskwk)
	{
		taskwk->seq = TSEQ_PAUSE;
		TypeIconDispOff( wk );
	}
}

static void InfoWinControlTask(TCB_PTR tcb, void* wk_adrs )
{
	INFOWIN_TASK_WORK* taskwk = (INFOWIN_TASK_WORK*)wk_adrs;
	STATUS_VIEW_WORK* wk = taskwk->wk;

	switch(taskwk->seq){
	case TSEQ_IDLE:
		if(BoxAppVPara_GetCursorStatusEnableFlag(wk->vpara) == FALSE){ break; }
		taskwk->subseq = TSUBSEQ_ITEM;
		taskwk->seq = TSEQ_SETUP;
		/* fallthru */
	case TSEQ_SETUP:
		InfoWinCharSetupSub( &wk->bmpwin[WIN_INFO], wk, taskwk->subseq, 0 );
		GF_BGL_BmpWinCgxOn( &wk->bmpwin[WIN_INFO] );
		taskwk->timer = 0;
		taskwk->seq = TSEQ_WAIT;
		break;
	case TSEQ_WAIT:
		if(++(taskwk->timer) > STATUS_SCROLL_WAIT )
		{
			InfoWinCharSetup( taskwk );
			taskwk->timer = 0;
			taskwk->scroll = 0;
			taskwk->seq = TSEQ_SCROLL;
		}
		break;
	case TSEQ_SCROLL:
		taskwk->scroll += STATUS_SCROLL_SPEED;
		TypeIconScroll( wk, STATUS_SCROLL_SPEED << FX32_SHIFT );
		GF_BGL_BmpWinShift( &wk->bmpwin[WIN_INFO], GF_BGL_BMPWIN_SHIFT_U, STATUS_SCROLL_SPEED, 0x00 );
		GF_BGL_BmpWinCgxOn( &wk->bmpwin[WIN_INFO] );
		if( taskwk->scroll >= STATUS_SCROLL_MAX )
		{
			if( taskwk->subseq == TSUBSEQ_TYPE )
			{
				TypeIconDispOff( wk );
			}
			if( ++(taskwk->subseq) >= TSUBSEQ_END )
			{
				taskwk->subseq = 0;
			}
			taskwk->scroll = 0;
			taskwk->timer = 0;
			taskwk->seq = TSEQ_WAIT;
		}
		break;
	case TSEQ_PAUSE:
		break;
	}
}

//------------------------------------------------------------------
/**
 * タイプアイコンスクロール
 *
 * @param   wk		
 * @param   vector		
 *
 */
//------------------------------------------------------------------
static void TypeIconScroll( STATUS_VIEW_WORK* wk, fx32 vector )
{
	int i;
	VecFx32 vec;
	for(i=0; i<TYPEICON_ACTOR_MAX; i++)
	{
		vec = *CLACT_GetMatrix(wk->typeIconAct[i]);
		vec.y -= vector;
		CLACT_SetMatrix(wk->typeIconAct[i], &vec);
		if( i==0 && CLACT_GetDrawFlag( wk->typeIconAct[i] ) )
		{
			u32 x , y;

			x = vec.x >> FX32_SHIFT;
			y = vec.y >> FX32_SHIFT;
		}
	}
}
static void TypeIconDispOff( STATUS_VIEW_WORK* wk )
{
	int i;
	for(i=0; i<TYPEICON_ACTOR_MAX; i++)
	{
		CLACT_SetDrawFlag(wk->typeIconAct[i], FALSE);
	}
}

//------------------------------------------------------------------
/**
 * 内部バッファに転送用データ作成
 *
 * @param   taskwk			
 * @param   next_flag		
 *
 */
//------------------------------------------------------------------
static void InfoWinCharSetup( INFOWIN_TASK_WORK* taskwk )
{
	u32 next_subseq;
	GF_BGL_BMPWIN* win;

	win = &(taskwk->wk->bmpwin[WIN_INFO]);

	GF_BGL_BmpWinDataFill( win, WIN_INFO_PAL_GROUND );
	InfoWinCharSetupSub( win, taskwk->wk, taskwk->subseq, 0 );

	next_subseq = taskwk->subseq + 1;
	if( next_subseq >= TSUBSEQ_END ){ next_subseq = 0; }
	InfoWinCharSetupSub( win, taskwk->wk, next_subseq, 1 );
}

static void InfoWinCharSetupSub( GF_BGL_BMPWIN* win, STATUS_VIEW_WORK* wk, u32 subseq, u32 vpos )
{
	const STRBUF* str;
	u32 print_ypos;

	print_ypos = (vpos * 16) + INFO_WRITE_Y;
	switch( subseq ){
	case TSUBSEQ_ITEM:
		str = wk->vpara->statusPoke.itemname;
		break;

	case TSUBSEQ_CHARACTER:
		str = wk->vpara->statusPoke.character;
		break;

	case TSUBSEQ_ABILITY:
		str = wk->vpara->statusPoke.ability;
		break;

	case TSUBSEQ_TYPE:
		{
			VecFx32 vec;

			u32 arcid, datid;

			arcid = WazaTypeIcon_ArcIDGet();
			datid = WazaTypeIcon_CgrIDGet(wk->vpara->statusPoke.type1);

			ArcUtil_ObjCharSet( WazaTypeIcon_ArcIDGet(), WazaTypeIcon_CgrIDGet(wk->vpara->statusPoke.type1),
				OBJTYPE_MAIN, OBJCHAR_POKETYPE_POS*0x20, 0, WAZATYPEICON_COMP_CHAR, HEAPID_BOX_VIEW );

			vec = *CLACT_GetMatrix( wk->typeIconAct[0] );
			vec.y = (TYPEICON_OBJ_Y+(TYPEICON_OBJ_YSPC*vpos)) << FX32_SHIFT;
			CLACT_SetMatrix( wk->typeIconAct[0], &vec );
			CLACT_PaletteNoChg( wk->typeIconAct[0],
				OBJPAL_TYPE+WazaTypeIcon_PlttOffsetGet(wk->vpara->statusPoke.type1) );
			CLACT_SetDrawFlag( wk->typeIconAct[0], TRUE );


			// type1, type2 に同じ値が入ってきたら純タイプなので、２番目は表示しない
			if( wk->vpara->statusPoke.type1 != wk->vpara->statusPoke.type2 )
			{
				ArcUtil_ObjCharSet( WazaTypeIcon_ArcIDGet(), WazaTypeIcon_CgrIDGet(wk->vpara->statusPoke.type2),
					OBJTYPE_MAIN, (OBJCHAR_POKETYPE_POS+OBJCHAR_POKETYPE_HALF_SIZE)*0x20, 0, WAZATYPEICON_COMP_CHAR, HEAPID_BOX_VIEW );
				vec.x += (TYPEICON_OBJ_XSPC << FX32_SHIFT);
				CLACT_SetMatrix( wk->typeIconAct[1], &vec );
				CLACT_PaletteNoChg( wk->typeIconAct[1],
					OBJPAL_TYPE+WazaTypeIcon_PlttOffsetGet(wk->vpara->statusPoke.type2) );
				CLACT_SetDrawFlag( wk->typeIconAct[1], TRUE );
			}
			else
			{
				CLACT_SetDrawFlag( wk->typeIconAct[1], FALSE );
			}
		}
		return;

	default:
		return;
	}


	GF_STR_PrintColor( win, FONT_SYSTEM, str, INFO_WRITE_X, print_ypos, MSG_NO_PUT, 
					GF_PRINTCOLOR_MAKE(WIN_INFO_PAL_LETTER,WIN_INFO_PAL_SHADOW,WIN_INFO_PAL_GROUND), NULL );

}


//------------------------------------------------------------------
/**
 * ステータス表示初回（エフェクトなし）
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
void BoxAppView_StatusUpdate( STATUS_VIEW_WORK* wk )
{
	if( wk->enableFlag == FALSE )
	{
		return;
	}

	GF_BGL_BmpWinDataFill( &wk->bmpwin[WIN_KIND], WIN_KIND_PAL_GROUND );
	GF_BGL_BmpWinDataFill( &wk->bmpwin[WIN_NUMBER], WIN_NUMBER_PAL_GROUND );
	GF_BGL_BmpWinDataFill( &wk->bmpwin[WIN_NICKNAME], WIN_NICKNAME_PAL_GROUND );
	GF_BGL_BmpWinDataFill( &wk->bmpwin[WIN_INFO], WIN_INFO_PAL_GROUND );

	if( BoxAppVPara_GetCursorStatusEnableFlag( wk->vpara ) )
	{
		StatusPrintCore( wk );
	}

	GF_BGL_BmpWinCgxOn( &wk->bmpwin[WIN_KIND] );
	GF_BGL_BmpWinCgxOn( &wk->bmpwin[WIN_NUMBER] );
	GF_BGL_BmpWinCgxOn( &wk->bmpwin[WIN_NICKNAME] );
	GF_BGL_BmpWinCgxOn( &wk->bmpwin[WIN_INFO] );
}
//------------------------------------------------------------------
/**
 * ステータス表示更新開始
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
void BoxAppView_StatusUpdateStart( STATUS_VIEW_WORK* wk )
{
	if( wk->enableFlag == FALSE )
	{
		return;
	}

	GF_BGL_BmpWinDataFill( &wk->bmpwin[WIN_KIND], WIN_KIND_PAL_GROUND );
	GF_BGL_BmpWinDataFill( &wk->bmpwin[WIN_NUMBER], WIN_NUMBER_PAL_GROUND );
	GF_BGL_BmpWinDataFill( &wk->bmpwin[WIN_NICKNAME], WIN_NICKNAME_PAL_GROUND );
	GF_BGL_BmpWinDataFill( &wk->bmpwin[WIN_INFO], WIN_INFO_PAL_GROUND );

	if( wk->sprite )
	{
		SoftSpriteDel( wk->sprite );
		wk->sprite = NULL;
	}

	if( BoxAppVPara_GetCursorStatusEnableFlag( wk->vpara ) )
	{
		StatusPrintCore( wk );
	}
	else
	{
		MarkingScreenSet( wk, 0 );
	}

	GF_BGL_BmpWinCgxOn( &wk->bmpwin[WIN_KIND] );
	GF_BGL_BmpWinCgxOn( &wk->bmpwin[WIN_NUMBER] );
	GF_BGL_BmpWinCgxOn( &wk->bmpwin[WIN_NICKNAME] );
	GF_BGL_BmpWinCgxOn( &wk->bmpwin[WIN_INFO] );

	InfoWinControlTaskReset( wk );
}

//------------------------------------------------------------------
/**
 * ステータス表示部をクリア（何も表示しない状態）
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
void BoxAppView_StatusUpdateClear( STATUS_VIEW_WORK* wk )
{
	if( wk->enableFlag == FALSE )
	{
		return;
	}

	GF_BGL_BmpWinDataFill( &wk->bmpwin[WIN_KIND], WIN_KIND_PAL_GROUND );
	GF_BGL_BmpWinDataFill( &wk->bmpwin[WIN_NUMBER], WIN_NUMBER_PAL_GROUND );
	GF_BGL_BmpWinDataFill( &wk->bmpwin[WIN_NICKNAME], WIN_NICKNAME_PAL_GROUND );
	GF_BGL_BmpWinDataFill( &wk->bmpwin[WIN_INFO], WIN_INFO_PAL_GROUND );

	if( wk->sprite )
	{
		SoftSpriteDel( wk->sprite );
		wk->sprite = NULL;
	}
	MarkingScreenSet( wk, 0 );

	GF_BGL_BmpWinCgxOn( &wk->bmpwin[WIN_KIND] );
	GF_BGL_BmpWinCgxOn( &wk->bmpwin[WIN_NUMBER] );
	GF_BGL_BmpWinCgxOn( &wk->bmpwin[WIN_NICKNAME] );
	GF_BGL_BmpWinCgxOn( &wk->bmpwin[WIN_INFO] );

	InfoWinControlTaskPause( wk );
}


static void StatusPrintCore( STATUS_VIEW_WORK* wk )
{
	SOFT_SPRITE_ARC  spriteArc;
	const BOXAPP_STATUS_POKE* poke;
	poke = BoxAppVpara_GetStatusPokeData( wk->vpara );


	GF_STR_PrintColor( 
			&wk->bmpwin[WIN_KIND], FONT_SYSTEM, poke->monsname,
			POKENAME_WRITE_X, POKENAME_WRITE_Y, MSG_NO_PUT,
			GF_PRINTCOLOR_MAKE(WIN_KIND_PAL_LETTER, WIN_KIND_PAL_SHADOW, WIN_KIND_PAL_GROUND), NULL);

	GF_STR_PrintColor( 
			&wk->bmpwin[WIN_NICKNAME], FONT_SYSTEM, poke->nickname,
			NICKNAME_WRITE_X, NICKNAME_WRITE_Y, MSG_NO_PUT,
			GF_PRINTCOLOR_MAKE(WIN_NICKNAME_PAL_LETTER, WIN_NICKNAME_PAL_SHADOW, WIN_NICKNAME_PAL_GROUND), NULL);

	GF_STR_PrintColor( 
			&wk->bmpwin[WIN_NICKNAME], FONT_SYSTEM, poke->nickname,
			NICKNAME_WRITE_X, NICKNAME_WRITE_Y, MSG_NO_PUT,
			GF_PRINTCOLOR_MAKE(WIN_NICKNAME_PAL_LETTER, WIN_NICKNAME_PAL_SHADOW, WIN_NICKNAME_PAL_GROUND), NULL);

	switch( poke->sex ){
	case PARA_MALE:	
		GF_STR_PrintColor( 
				&wk->bmpwin[WIN_NICKNAME], FONT_SYSTEM, wk->strMale,
				SEX_WRITE_X, SEX_WRITE_Y, MSG_NO_PUT,
				GF_PRINTCOLOR_MAKE(WIN_MALE_PAL_LETTER, WIN_MALE_PAL_SHADOW, WIN_SEX_PAL_GROUND), NULL);
		break;
	case PARA_FEMALE:
		GF_STR_PrintColor( 
				&wk->bmpwin[WIN_NICKNAME], FONT_SYSTEM, wk->strFemale,
				SEX_WRITE_X, SEX_WRITE_Y, MSG_NO_PUT,
				GF_PRINTCOLOR_MAKE(WIN_FEMALE_PAL_LETTER, WIN_FEMALE_PAL_SHADOW, WIN_SEX_PAL_GROUND), NULL);
		break;
	}

	/* とりあえずアイテム名だけ表示で */
	if( poke->tamago_flag == FALSE )
	{
		GF_STR_PrintColor( 
				&wk->bmpwin[WIN_INFO], FONT_SYSTEM, poke->itemname,
				INFO_WRITE_X, INFO_WRITE_Y, MSG_NO_PUT,
				GF_PRINTCOLOR_MAKE(WIN_INFO_PAL_LETTER, WIN_INFO_PAL_SHADOW, WIN_INFO_PAL_GROUND), NULL);

		// 全国図鑑未入手かつ全国図鑑にしか表示されないポケを持っていると
		// ナンバーが0になる（この場合、ナンバーを表示しない）
		if( poke->zukan_no )
		{
			NUMFONT_WriteSet( wk->numfontNo, NUMFONT_MARK_NO, poke->zukan_no, 3, NUMFONT_MODE_ZERO, 
					&(wk->bmpwin[WIN_NUMBER]), POKENO_WRITE_X, POKENO_WRITE_Y );
		}

		NUMFONT_WriteSet( wk->numfontLv, NUMFONT_MARK_LV, poke->level, 3, NUMFONT_MODE_SPACE, 
				&(wk->bmpwin[WIN_NICKNAME]), LV_WRITE_X, LV_WRITE_Y );
	}

	PokeGraArcDataGetPPP( &spriteArc, poke->poke_data, PARA_FRONT );
	wk->sprite = SoftSpriteAdd( wk->spriteMan, &spriteArc, POKEIMAGE_WRITE_X, POKEIMAGE_WRITE_Y, 0, 0, NULL, NULL );

	MarkingScreenSet( wk, poke->mark );
}

//------------------------------------------------------------------
/**
 * ステータス表示更新終了待ち
 *
 * @param   wk		ワークポインタ
 *
 * @retval  BOOL	TRUEで終了
 */
//------------------------------------------------------------------
BOOL BoxAppView_StatusUpdateWait( STATUS_VIEW_WORK* wk )
{
	if( wk->enableFlag == FALSE )
	{
		return TRUE;
	}

	// とりあえず１フレームで終わらせてるので
	return TRUE;
}


//------------------------------------------------------------------
/**
 * マーキング表示のみ更新
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
void BoxAppView_StatusMarkUpdate( STATUS_VIEW_WORK* wk )
{
	if( wk->enableFlag == FALSE )
	{
		return;
	}

	if( BoxAppVPara_GetCursorStatusEnableFlag( wk->vpara ) )
	{
		const BOXAPP_STATUS_POKE* poke;
		poke = BoxAppVpara_GetStatusPokeData( wk->vpara );

		MarkingScreenSet( wk, poke->mark );
	}
}

//------------------------------------------------------------------
/**
 * マーキング表示スクリーン更新
 *
 * @param   wk			ワークポインタ
 * @param   mark		マーキング状態
 *
 */
//------------------------------------------------------------------
static void MarkingScreenSet( STATUS_VIEW_WORK* wk, u8 mark )
{
	u16* scrn;
	u32 scrn_ofs;
	int i;

	scrn_ofs = (POKEMARK_WRITE_Y*32)+POKEMARK_WRITE_X;
	scrn = GF_BGL_ScreenAdrsGet( wk->bgl, FRM_MAIN_STATUS );
	scrn += scrn_ofs;
	for(i=0; i<BOX_MARK_MAX; i++)
	{
		if( mark & (1<<i) )
		{
			scrn[i] = (PAL_MAIN_STATUS3<<12) | (CHARPOS_MARK_ON+i);
		}
		else
		{
			scrn[i] = (PAL_MAIN_STATUS3<<12) | (CHARPOS_MARK_OFF+i);
		}
	}

	GF_BGL_LoadScreen( wk->bgl, FRM_MAIN_STATUS, scrn, BOX_MARK_MAX*sizeof(u16), scrn_ofs );
}

//------------------------------------------------------------------
/**
 * アイテム名表示のみ更新
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
void BoxAppView_StatusUpdateItemInfo( STATUS_VIEW_WORK* wk )
{
	const BOXAPP_STATUS_POKE* poke;

	if( wk->enableFlag == FALSE )
	{
		return;
	}

	poke = BoxAppVpara_GetStatusPokeData( wk->vpara );

	GF_BGL_BmpWinDataFill( &wk->bmpwin[WIN_INFO], WIN_INFO_PAL_GROUND );

	if( poke->tamago_flag == FALSE )
	{
		GF_STR_PrintColor( 
				&wk->bmpwin[WIN_INFO], FONT_SYSTEM, poke->itemname,
				INFO_WRITE_X, INFO_WRITE_Y, MSG_NO_PUT,
				GF_PRINTCOLOR_MAKE(WIN_INFO_PAL_LETTER, WIN_INFO_PAL_SHADOW, WIN_INFO_PAL_GROUND), NULL);
	}
	InfoWinControlTaskReset( wk );
}




