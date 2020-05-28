//============================================================================================
/**
 * @file	poketch_a06v.c
 * @bfief	ポケッチ（アプリNo06: 簡易ポケモンリスト）　描画
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include "common.h"
#include "system\lib_pack.h"
#include "poketool\pokeicon.h"
#include "itemtool\item.h"

#include "poketch_prv.h"
#include "poketch_view.h"
#include "poketch_a06.h"


//==============================================================
// consts
//==============================================================
#define CMD_STORE_MAX	(8)
#define USE_BG_FRAME	(GF_BGL_FRAME2_S)

#define ITEMICON_CHAR_POS	(0)
#define ITEMOCIN_CHAR_SIZE	(8)

#define POKEICON_CHAR_POS	(ITEMICON_CHAR_POS + ITEMOCIN_CHAR_SIZE)

#define POKEICON_CHAR_SIZE	(16)	// アニメさせないので
#define POKEICON_CHAR_BYTESIZE	(POKEICON_CHAR_SIZE*0x20)
#define POKEICON_CHAR_BUFSIZE	(POKEICON_CHAR_BYTESIZE+0x80)	// ヘッダも読み込みたい


#define ITEM_POKE_XDIFF		(28)
#define ITEM_POKE_YDIFF		(21)

enum {
	ANM_ITEM_NORMAL,
	ANM_ITEM_MAIL,
};

enum {
	PALPOS_COMMON = 0,
	PALPOS_SICKNESS_POKE,		// 状態異常のポケアイコン
	PALPOS_NORMAL_POKE,			// 普通のアイコンはここから４本使う
};


enum {
	CHARCODE_CLEAR = 0x0005,
	CHARCODE_FRAME_LT = 0x0001,
	CHARCODE_FRAME_TOP = 0x0002,
	CHARCODE_FRAME_RT = (CHARCODE_FRAME_LT | GX_SCRFMT_TEXT_HF_MASK),
	CHARCODE_FRAME_LEFT = 0x0006,
	CHARCODE_FRAME_RIGHT = (CHARCODE_FRAME_LEFT | GX_SCRFMT_TEXT_HF_MASK),
	CHARCODE_FRAME_LB = (CHARCODE_FRAME_LT | GX_SCRFMT_TEXT_VF_MASK),
	CHARCODE_FRAME_BOTTOM = (CHARCODE_FRAME_TOP | GX_SCRFMT_TEXT_VF_MASK),
	CHARCODE_FRAME_RB = (CHARCODE_FRAME_LT | GX_SCRFMT_TEXT_VF_MASK | GX_SCRFMT_TEXT_HF_MASK),

};

//==============================================================
// Work
//==============================================================

typedef struct {

	VIEWWORK*			vwk;
	const VIEWPARAM*	vpara;

	u8     seq;
	u8     timer;
	u8     iconNum;
	u8     count;

	u8     interval;
	u8     shake_min;

	int    vector;

}ICON_SHAKE_WORK;


struct _POKETCH_A06_VIEWWORK {
	const  VIEWPARAM*  vpara;
	GF_BGL_INI*        bgl;
	PACTSYS*           actsys;
	POKETCH_CMD_STORE  cmd_store[ CMD_STORE_HEADER_SIZE + CMD_STORE_MAX ];

	u32                free_charpos_top;
	u32                bmpwin_cnt;
	GF_BGL_BMPWIN      bmpwin[ TEMOTI_POKEMAX ];
	PACT*              act[ TEMOTI_POKEMAX ];
	PACT*              actItem[ TEMOTI_POKEMAX ];
	PACT_CLANM_PACK    clpackPoke;
	PACT_CLANM_PACK    clpackItem;

	TCB_PTR        tcb;
	ICON_SHAKE_WORK  taskwork;

	u8          act_charbuf[ POKEICON_CHAR_BUFSIZE ];
};



//====================================================
// bg map
//====================================================
#define USE_PALNO	(0)

enum {
	POKE_ICONPOS_XORG = 64,
	POKE_ICONPOS_YORG = 36,

	// ドット単位
	POKE_ICONPOS_1_X =  POKE_ICONPOS_XORG,
	POKE_ICONPOS_1_Y =  POKE_ICONPOS_YORG,
	POKE_ICONPOS_2_X =  POKE_ICONPOS_XORG+96,
	POKE_ICONPOS_2_Y =  POKE_ICONPOS_YORG,

	POKE_ICONPOS_3_X =  POKE_ICONPOS_XORG,
	POKE_ICONPOS_3_Y =  POKE_ICONPOS_YORG+48,
	POKE_ICONPOS_4_X =  POKE_ICONPOS_XORG+96,
	POKE_ICONPOS_4_Y =  POKE_ICONPOS_YORG+48,

	POKE_ICONPOS_5_X =  POKE_ICONPOS_XORG,
	POKE_ICONPOS_5_Y =  POKE_ICONPOS_YORG+96,
	POKE_ICONPOS_6_X =  POKE_ICONPOS_XORG+96,
	POKE_ICONPOS_6_Y =  POKE_ICONPOS_YORG+96,

	// 触って反応するエリアサイズ。アイコンサイズがまちまちなので、中心に近い位置のみに。
	POKE_ICON_TOUCHAREA_WIDTH = 16,		
	POKE_ICON_TOUCHAREA_HEIGHT = 16,

	// キャラ単位
	POKE_GAUGEWIN_1_X =  4,
	POKE_GAUGEWIN_1_Y =  8,
	POKE_GAUGEWIN_2_X = 16,
	POKE_GAUGEWIN_2_Y =  8,

	POKE_GAUGEWIN_3_X =  4,
	POKE_GAUGEWIN_3_Y = 14,
	POKE_GAUGEWIN_4_X = 16,
	POKE_GAUGEWIN_4_Y = 14,

	POKE_GAUGEWIN_5_X =  4,
	POKE_GAUGEWIN_5_Y = 20,
	POKE_GAUGEWIN_6_X = 16,
	POKE_GAUGEWIN_6_Y = 20,

	POKE_GAUGEWIN_WIDTH = 8,
	POKE_GAUGEWIN_HEIGHT = 1,
	POKE_GAUGEWIN_SIZE = POKE_GAUGEWIN_WIDTH*POKE_GAUGEWIN_HEIGHT,

	POKE_GAUGEWIN_DOT_WIDTH = POKE_GAUGEWIN_WIDTH*8,
	POKE_GAUGEWIN_DOT_UNIT = 2,
	POKE_GAUGEWIN_DOT_UNIT_MAX = POKE_GAUGEWIN_DOT_WIDTH / POKE_GAUGEWIN_DOT_UNIT,

};


//==============================================================
// アイコン表示位置テーブル
//==============================================================
static const struct {
	u16 x;
	u16 y;
}PokeIconPos[] = {
	{ POKE_ICONPOS_1_X, POKE_ICONPOS_1_Y },
	{ POKE_ICONPOS_2_X, POKE_ICONPOS_2_Y },
	{ POKE_ICONPOS_3_X, POKE_ICONPOS_3_Y },
	{ POKE_ICONPOS_4_X, POKE_ICONPOS_4_Y },
	{ POKE_ICONPOS_5_X, POKE_ICONPOS_5_Y },
	{ POKE_ICONPOS_6_X, POKE_ICONPOS_6_Y },
};

//==============================================================
// Prototype
//==============================================================
static void DeleteCommand(POKETCH_CMD_WORK* cwk);
static void CmdInit(TCB_PTR tcb, void *wk_ptr);
static void GaugeWinSetup( VIEWWORK* vwk, const VIEWPARAM* vpara, u32 charpos );
static void GaugeWinFrameScrnWritre( GF_BGL_BMPWIN* win, VIEWWORK* vwk );
static void GaugeWinCgxWrite( GF_BGL_BMPWIN* win, u32 hp_width );
static u32 CalcGaugeWinWidth( u32 hp, u32 hp_max );
static void ItemIconSetup( VIEWWORK* vwk, const VIEWPARAM* vpara );
static void PokeIconSetup( VIEWWORK* vwk, const VIEWPARAM* vpara );
static void PokeShakeTaskSetup(VIEWWORK* vwk );
static void PokeShakeTask(TCB_PTR tcb, void* wk_adrs);
static void DeleteAllPokeGraphics( VIEWWORK* wk );
static void CmdQuit(TCB_PTR tcb, void *wk_ptr);
static void CmdUpdate(TCB_PTR tcb, void *wk_ptr);




//------------------------------------------------------------------
/**
 * ワーク確保
 *
 * @param   wk_ptr		確保したワークアドレスを保存するポインタのアドレス
 *
 */
//------------------------------------------------------------------
BOOL Poketch_A06_SetViewWork( VIEWWORK** wk_ptr, const VIEWPARAM* vpara, GF_BGL_INI* bgl )
{
	VIEWWORK *wk = (VIEWWORK*)sys_AllocMemory( POKETCH_APP_VIEW_HEAPID, sizeof(VIEWWORK));

	if(wk != NULL)
	{
		int i;
		PoketchViewTool_CmdStoreInit( wk->cmd_store, CMD_STORE_MAX );
		wk->vpara = vpara;
		wk->bgl = PoketchView_GetAppBglWork();
		wk->actsys = PoketchGetActSys();
		wk->bmpwin_cnt = 0;
		wk->tcb = NULL;

		for(i=0; i<TEMOTI_POKEMAX; i++)
		{
			GF_BGL_BmpWinInit( &(wk->bmpwin[i]) );
			wk->act[i] = NULL;
			wk->actItem[i] = NULL;
		}

		PACT_TOOL_LoadCellDatas( &wk->clpackPoke, ARC_POKETCH_IMG,
			NARC_poketch_pokeicon_ncer,NARC_poketch_pokeicon_nanr, POKETCH_APP_VIEW_HEAPID );

		PACT_TOOL_LoadCellDatas( &wk->clpackItem, ARC_POKETCH_IMG,
			NARC_poketch_list_obj_lz_ncer,NARC_poketch_list_obj_lz_nanr, POKETCH_APP_VIEW_HEAPID );


		*wk_ptr = wk;
		return TRUE;
	}

	return FALSE;
}
//------------------------------------------------------------------
/**
 * ワーク削除
 *
 * @param   wk		確保したワークアドレス
 *
 */
//------------------------------------------------------------------
void Poketch_A06_DeleteViewWork( VIEWWORK* wk )
{
	if( wk != NULL )
	{
		DeleteAllPokeGraphics( wk );

		PACT_TOOL_UnloadCellDatas( &wk->clpackPoke );
		PACT_TOOL_UnloadCellDatas( &wk->clpackItem );

		if(wk->tcb)
		{
			TCB_Delete(wk->tcb);
		}
		sys_FreeMemoryEz( wk );
	}
}

//------------------------------------------------------------------
/**
 * @brief	コマンドテーブル
 */
//------------------------------------------------------------------
static const POKETCH_VIEW_CMD CmdTbl[] = {
	{ CMD_INIT,		CmdInit,	0 },
	{ CMD_QUIT,		CmdQuit,	0 },
	{ CMD_UPDATE,	CmdUpdate,	0 },
	{ 0, NULL, 0 },
};


//------------------------------------------------------------------
/**
 * 描画コマンドのセット
 *
 * @param   cmd		コマンド
 * @param   view_wk_adrs	ワーク領域アドレス
 *
 */
//------------------------------------------------------------------
void Poketch_A06_SetViewCommand(VIEWWORK* wk, u32 cmd)
{
	PoketchViewTool_SetCommand(CmdTbl, cmd, wk, wk->vpara, wk->cmd_store, POKETCH_GRAPHIC_TASKPRI, POKETCH_APP_VIEW_HEAPID);
}
//------------------------------------------------------------------
/**
 * 描画コマンドの終了待ち（単発）
 *
 * @param   cmd			コマンド
 *
 * @retval  BOOL		TRUEで終了
 */
//------------------------------------------------------------------
BOOL Poketch_A06_WaitViewCommand(VIEWWORK* wk, u32 cmd)
{
	return PoketchViewTool_WaitCommand(wk->cmd_store, cmd);
}
//------------------------------------------------------------------
/**
 * 描画コマンドの終了待ち（全部）
 *
 * @retval  BOOL		TRUEで終了
 */
//------------------------------------------------------------------
BOOL Poketch_A06_WaitViewCommandAll(VIEWWORK* wk)
{
	return PoketchViewTool_WaitCommandAll(wk->cmd_store);
}



//------------------------------------------------------------------
/**
 * コマンド削除
 *
 * @param   cwk		コマンドワーク
 *
 */
//------------------------------------------------------------------
static void DeleteCommand(POKETCH_CMD_WORK* cwk)
{
	VIEWWORK *wk = PoketchViewTool_GetViewWork(cwk);
	PoketchViewTool_DelCommand( wk->cmd_store, cwk );
}

//------------------------------------------------------------------
/**
 * コマンド：画面構築
 *
 * @param   tcb			TCBポインタ
 * @param   wk_ptr		ワークポインタ
 *
 */
//------------------------------------------------------------------
static void CmdInit(TCB_PTR tcb, void *wk_ptr)
{
	static const GF_BGL_BGCNT_HEADER header = {
		0, 0, 0x800, 0,		// scrX, scrY, scrbufSize, scrbufofs,
		GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
		GX_BG_SCRBASE_0x7000, GX_BG_CHARBASE_0x00000,
		GX_BG_EXTPLTT_01, 2, 0, 0, FALSE	// pal, pri, areaover, dmy, mosaic
	};

	GXSDispCnt dispcnt;
	VIEWWORK* vwk;
	u32  charpos;

	vwk = PoketchViewTool_GetViewWork( wk_ptr );

	GF_BGL_BGControlSet( vwk->bgl, USE_BG_FRAME, &header, GF_BGL_MODE_TEXT );

	charpos = ArcUtil_BgCharSet( ARC_POKETCH_IMG, NARC_poketch_list_lz_ncgr, vwk->bgl, USE_BG_FRAME, 0, 0, TRUE, HEAPID_POKETCH_APP );
	charpos /= 0x20;
	GF_BGL_ScrFill( vwk->bgl, USE_BG_FRAME, 0x0005, 0, 0, 32, 24, USE_PALNO );
	PoketchView_SetBaseColorPalette(USE_PALNO,0);

	vwk->free_charpos_top = charpos;
	GaugeWinSetup( vwk, vwk->vpara, charpos );
	GF_BGL_LoadScreenReq( vwk->bgl, USE_BG_FRAME );

	PoketchViewTool_TransSingleColorData( POKETCH_DEFAULTCOLOR_L2_POS, PALPOS_SICKNESS_POKE );
	PoketchViewTool_SetupPokeIconPalette( PALPOS_NORMAL_POKE );

	ItemIconSetup( vwk, vwk->vpara );
	PokeIconSetup( vwk, vwk->vpara );


	PokeShakeTaskSetup( vwk );

	dispcnt = GXS_GetDispCnt();
	GXS_SetVisiblePlane(dispcnt.visiblePlane | GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ);

	DeleteCommand( wk_ptr );

}

//------------------------------------------------------------------
/**
 * HPゲージ全描画
 *
 * @param   vwk		
 * @param   vpara		
 *
 */
//------------------------------------------------------------------
static void GaugeWinSetup( VIEWWORK* vwk, const VIEWPARAM* vpara, u32 charpos )
{
	static const struct {
		u16 x;
		u16 y;
	}winpos[] = {
		{ POKE_GAUGEWIN_1_X, POKE_GAUGEWIN_1_Y },
		{ POKE_GAUGEWIN_2_X, POKE_GAUGEWIN_2_Y },
		{ POKE_GAUGEWIN_3_X, POKE_GAUGEWIN_3_Y },
		{ POKE_GAUGEWIN_4_X, POKE_GAUGEWIN_4_Y },
		{ POKE_GAUGEWIN_5_X, POKE_GAUGEWIN_5_Y },
		{ POKE_GAUGEWIN_6_X, POKE_GAUGEWIN_6_Y },
	};
	int i;

	for(i=0; i<vpara->poke_count; i++)
	{
		GF_BGL_BmpWinInit( &(vwk->bmpwin[i]) );
		GF_BGL_BmpWinAdd( vwk->bgl, &(vwk->bmpwin[i]), USE_BG_FRAME, winpos[i].x, winpos[i].y,
			POKE_GAUGEWIN_WIDTH, POKE_GAUGEWIN_HEIGHT, USE_PALNO, charpos+i*POKE_GAUGEWIN_SIZE );

		GF_BGL_BmpWinMakeScrn( &(vwk->bmpwin[i]) );

		GaugeWinFrameScrnWritre( &(vwk->bmpwin[i]), vwk );

		GaugeWinCgxWrite( &(vwk->bmpwin[i]),
			CalcGaugeWinWidth(vpara->poke_param[i].hp,  vpara->poke_param[i].hp_max) );
	}

	vwk->bmpwin_cnt = vpara->poke_count;
}

//------------------------------------------------------------------
/**
 * HPゲージウィンドウの周囲にフレームスクリーン描画
 *
 * @param   win		
 * @param   hp_width		
 *
 */
//------------------------------------------------------------------
static void GaugeWinFrameScrnWritre( GF_BGL_BMPWIN* win, VIEWWORK* vwk )
{
	GF_BGL_ScrFill( vwk->bgl, USE_BG_FRAME, CHARCODE_FRAME_LT, win->posx-1, win->posy-1, 1, 1, USE_PALNO );
	GF_BGL_ScrFill( vwk->bgl, USE_BG_FRAME, CHARCODE_FRAME_TOP, win->posx, win->posy-1, win->sizx, 1, USE_PALNO );
	GF_BGL_ScrFill( vwk->bgl, USE_BG_FRAME, CHARCODE_FRAME_RT, win->posx+win->sizx, win->posy-1, 1, 1, USE_PALNO );

	GF_BGL_ScrFill( vwk->bgl, USE_BG_FRAME, CHARCODE_FRAME_LEFT, win->posx-1, win->posy, 1, win->sizy, USE_PALNO );
	GF_BGL_ScrFill( vwk->bgl, USE_BG_FRAME, CHARCODE_FRAME_RIGHT, win->posx+win->sizx, win->posy, 1, win->sizy, USE_PALNO );

	GF_BGL_ScrFill( vwk->bgl, USE_BG_FRAME, CHARCODE_FRAME_LB, win->posx-1, win->posy+win->sizy, 1, 1, USE_PALNO );
	GF_BGL_ScrFill( vwk->bgl, USE_BG_FRAME, CHARCODE_FRAME_BOTTOM, win->posx, win->posy+win->sizy, win->sizx, 1, USE_PALNO );
	GF_BGL_ScrFill( vwk->bgl, USE_BG_FRAME, CHARCODE_FRAME_RB, win->posx+win->sizx, win->posy+win->sizy, 1, 1, USE_PALNO );
}

//------------------------------------------------------------------
/**
 * HPゲージCGX描画
 *
 * @param   win		
 * @param   hp_width		
 *
 */
//------------------------------------------------------------------
static void GaugeWinCgxWrite( GF_BGL_BMPWIN* win, u32 hp_width )
{
	GF_BGL_BmpWinFill(win, POKETCH_DEFAULTCOLOR_L1_POS, 0, 0, POKE_GAUGEWIN_DOT_WIDTH, 8);

	if(hp_width)
	{
		GF_BGL_BmpWinFill(win, POKETCH_DEFAULTCOLOR_L2_POS, 0, 0, hp_width, 8);
	}

	GF_BGL_BmpWinCgxOn(win);
}
//------------------------------------------------------------------
/**
 * HPゲージ幅計算
 *
 * @param   hp		
 * @param   hp_max		
 *
 * @retval  u32		ゲージ幅（ドット）
 */
//------------------------------------------------------------------
static u32 CalcGaugeWinWidth( u32 hp, u32 hp_max )
{
	u32 ratio;

	if(hp==0){
		return 0;
	}
	if(hp==hp_max){
		return POKE_GAUGEWIN_DOT_WIDTH;
	}

	ratio = (((hp << FX32_SHIFT) / hp_max) * POKE_GAUGEWIN_DOT_UNIT_MAX) >> FX32_SHIFT;
	if( ratio == 0 ){
		ratio = 1;
	}else if( ratio == POKE_GAUGEWIN_DOT_UNIT_MAX ){
		ratio = POKE_GAUGEWIN_DOT_UNIT_MAX - 1;
	}

	return ratio * POKE_GAUGEWIN_DOT_UNIT;
}

//------------------------------------------------------------------
/**
 * アイテムアイコンセットアップ
 *
 * @param   vwk		
 *
 */
//------------------------------------------------------------------
static void ItemIconSetup( VIEWWORK* vwk, const VIEWPARAM* vpara )
{
	int i;

	PACT_ADD_PARAM   actparam;

	ArcUtil_ObjCharSet( ARC_POKETCH_IMG, NARC_poketch_list_obj_lz_ncgr,
		OBJTYPE_SUB, ITEMICON_CHAR_POS*0x20, 0, TRUE, HEAPID_POKETCH_APP );

	actparam.flip = PACT_FLIP_OFF;
	actparam.bgpri = BGPRI2;
	actparam.oampri = 0;
	actparam.affine_flag = FALSE;

	for(i=0; i<vpara->poke_count; i++)
	{
		if( vpara->poke_param[i].item != ITEM_DUMMY_ID )
		{
			actparam.anmseq = ItemMailCheck(vpara->poke_param[i].item)? ANM_ITEM_MAIL : ANM_ITEM_NORMAL;
			actparam.pos.x = FX32INT(PokeIconPos[i].x + ITEM_POKE_XDIFF);
			actparam.pos.y = FX32INT(PokeIconPos[i].y + ITEM_POKE_YDIFF);

			vwk->actItem[i] = PACT_Add( vwk->actsys, &actparam, &vwk->clpackItem );
		}
	}
}

//------------------------------------------------------------------
/**
 * ポケモンアイコンセットアップ
 *
 * @param   vwk		
 * @param   vpara		
 *
 */
//------------------------------------------------------------------
static void PokeIconSetup( VIEWWORK* vwk, const VIEWPARAM* vpara )
{
	ARCHANDLE* arcHandle;

	arcHandle = ArchiveDataHandleOpen( ARC_POKEICON, HEAPID_POKETCH_APP );
	if( arcHandle )
	{
		PACT_ADD_PARAM   actparam;
		NNSG2dCharacterData* charData;
		int i;

		actparam.anmseq = 0;
		actparam.flip = PACT_FLIP_OFF;
		actparam.bgpri = BGPRI2;
		actparam.oampri = 1;
		actparam.affine_flag = TRUE;

		for(i=0; i<vpara->poke_count; i++)
		{
			ArchiveDataLoadOfsByHandle( arcHandle, vpara->poke_param[i].imgArcIdx,
				 0, POKEICON_CHAR_BUFSIZE, vwk->act_charbuf );

			NNS_G2dGetUnpackedCharacterData( vwk->act_charbuf, &charData );
			DC_FlushRange( charData->pRawData, POKEICON_CHAR_BYTESIZE );
			GXS_LoadOBJ( charData->pRawData, POKEICON_CHAR_POS*0x20+POKEICON_CHAR_BYTESIZE*i, POKEICON_CHAR_BYTESIZE );

			actparam.pos.x = FX32INT(PokeIconPos[i].x);
			actparam.pos.y = FX32INT(PokeIconPos[i].y);

			vwk->act[i] = PACT_Add( vwk->actsys, &actparam, &vwk->clpackPoke );
			PACT_SetCharOffset( vwk->act[i], POKEICON_CHAR_POS+POKEICON_CHAR_SIZE*i );
			PACT_ChangeAnmSeq( vwk->act[i], POKEICON_ANM_OFF_L );

			if( vpara->poke_param[i].hp == 0 || vpara->poke_param[i].sick_flag )
			{
				PACT_SetPalOffset( vwk->act[i], PALPOS_SICKNESS_POKE );
			}
			else
			{
				u16 palIndex = PokeIconPalNumGet(vpara->poke_param[i].monsno,
						vpara->poke_param[i].form, vpara->poke_param[i].egg_flag);
				PACT_SetPalOffset(	vwk->act[i], PALPOS_NORMAL_POKE + palIndex );
			}
		}
		ArchiveDataHandleClose( arcHandle );
	}
}


//------------------------------------------------------------------
/**
 * ポケモンゆらしタスクセットアップ
 *
 * @param   vwk		
 *
 */
//------------------------------------------------------------------
static void PokeShakeTaskSetup(VIEWWORK* vwk )
{
	vwk->taskwork.seq = 0;
	vwk->taskwork.vwk = vwk;
	vwk->taskwork.vpara = vwk->vpara;

	vwk->tcb = TCB_Add(PokeShakeTask, &(vwk->taskwork), POKETCH_APP_TASKPRI);
}

//------------------------------------------------------------------
/**
 * ポケモンゆらしタスク
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void PokeShakeTask(TCB_PTR tcb, void* wk_adrs)
{
	enum {
		SHAKE_INTERVAL = 1,
		SHAKE_COUNT = 8,

		SHAKE_SICK_INTERVAL = 2,
		SHAKE_SICK_COUNT = 4,

		SHAKE_WIDTH = 2,
	};
	ICON_SHAKE_WORK* wk = wk_adrs;
	const VIEWPARAM* vpara = wk->vpara;
	VIEWWORK* vwk = wk->vwk;

	switch(wk->seq){
	case 0:
		if( vpara->tp_trg )
		{
			u32 iconNum = Poketch_A06_CheckTouchIconNum( vpara->tp_x, vpara->tp_y, vpara->poke_count );
			if(iconNum < vpara->poke_count)
			{
				if( vpara->poke_param[iconNum].hp && (vpara->poke_param[iconNum].egg_flag == FALSE) )
				{
					wk->timer = 0;
					wk->count = 0;
					wk->iconNum = iconNum;
					wk->vector = SHAKE_WIDTH;

					if( vpara->poke_param[iconNum].sick_flag == FALSE )
					{
						wk->interval = SHAKE_INTERVAL;
						wk->shake_min = SHAKE_COUNT;
					}
					else
					{
						wk->interval = SHAKE_SICK_INTERVAL;
						wk->shake_min = SHAKE_SICK_COUNT;
					}

					wk->seq = 1;
					PoketchVoicePlay( vpara->poke_param[iconNum].monsno );
				}
			}
		}
		break;

	case 1:
		if( wk->count == wk->shake_min )
		{
			if( ! (vpara->tp_cont && wk->iconNum == Poketch_A06_CheckTouchIconNum(vpara->tp_x, vpara->tp_y, vpara->poke_count)) )
			{
				PACT_SetPos( vwk->act[wk->iconNum],
					 (PokeIconPos[wk->iconNum].x<<FX32_SHIFT), (PokeIconPos[wk->iconNum].y <<FX32_SHIFT) );
				wk->seq = 0;
				break;
			}
		}

		if( wk->timer == 0 )
		{
			fx32 x, y;

			x = PokeIconPos[wk->iconNum].x << FX32_SHIFT;
			y = (PokeIconPos[wk->iconNum].y + wk->vector) << FX32_SHIFT;

			PACT_SetPos( vwk->act[wk->iconNum], x, y );

			if( wk->count < wk->shake_min )
			{
				wk->count++;
			}
			wk->vector *= -1;
			wk->timer = wk->interval;
		}
		else
		{
			wk->timer--;
		}
		break;
	}
}


//------------------------------------------------------------------
/**
 * 触ってるアイコンのナンバーを返す。触ってなければmaxと同じ値が返る
 *
 * @param   x		タッチパネルX
 * @param   y		タッチパネルY
 * @param   max		チェックする最大数
 *
 * @retval  u32		
 */
//------------------------------------------------------------------
u32 Poketch_A06_CheckTouchIconNum( u32 x, u32 y, u32 max )
{
	u32  i, top, bottom, left, right;
	for(i=0; i<max; i++)
	{
		// アイコンが上１キャラ開けて描かれている分を足しておく
		top = 8 + PokeIconPos[i].y - POKE_ICON_TOUCHAREA_HEIGHT;
		bottom = 8 + PokeIconPos[i].y + POKE_ICON_TOUCHAREA_HEIGHT;
		left = PokeIconPos[i].x - POKE_ICON_TOUCHAREA_WIDTH;
		right = PokeIconPos[i].x + POKE_ICON_TOUCHAREA_WIDTH;

		if( ((u32)( x - left) < (u32)(right - left))
		&	((u32)( y - top) < (u32)(bottom - top))
		){
			return i;
		}
	}
	return max;
}
//------------------------------------------------------------------
/**
 * ポケモンのアイコン、アイテムアイコン、HPゲージを全削除
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void DeleteAllPokeGraphics( VIEWWORK* wk )
{
	int i;
	for(i=0; i<TEMOTI_POKEMAX; i++)
	{
		if(wk->act[i] != NULL)
		{
			PACT_Del(wk->actsys, wk->act[i]);
			wk->act[i] = NULL;
		}
		if(wk->actItem[i] != NULL)
		{
			PACT_Del(wk->actsys, wk->actItem[i]);
			wk->actItem[i] = NULL;
		}
	}

	for(i=0; i<wk->bmpwin_cnt; i++)
	{
		GF_BGL_BmpWinDel( &(wk->bmpwin[i]) );
	}
	wk->bmpwin_cnt = 0;
}

//------------------------------------------------------------------
/**
 * コマンド：終了処理
 *
 * @param   tcb			TCBポインタ
 * @param   wk_ptr		ワークポインタ
 *
 */
//------------------------------------------------------------------
static void CmdQuit(TCB_PTR tcb, void *wk_ptr)
{
	VIEWWORK* vwk = PoketchViewTool_GetViewWork( wk_ptr );

	GF_BGL_BGControlExit( vwk->bgl, USE_BG_FRAME );
	DeleteCommand( wk_ptr );
}

//------------------------------------------------------------------
/**
 * コマンド：画面更新
 *
 * @param   tcb			TCBポインタ
 * @param   wk_ptr		ワークポインタ
 *
 */
//------------------------------------------------------------------
static void CmdUpdate(TCB_PTR tcb, void *wk_ptr)
{
	VIEWWORK* wk = PoketchViewTool_GetViewWork( wk_ptr );
	const VIEWPARAM* vpara = PoketchViewTool_GetViewParam( wk_ptr );

	DeleteAllPokeGraphics( wk );

	GF_BGL_ScrFill( wk->bgl, USE_BG_FRAME, 0x0005, 0, 0, 32, 24, USE_PALNO );

	ItemIconSetup( wk, vpara );
	PokeIconSetup( wk, vpara );
	GaugeWinSetup( wk, vpara, wk->free_charpos_top );

	GF_BGL_LoadScreenReq( wk->bgl, USE_BG_FRAME );

	PoketchSePlay( POKETCH_SE_LIST_UPDATE );

	DeleteCommand( wk_ptr );
}


