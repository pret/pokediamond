//============================================================================================
/**
 * @file	demo_trade.c
 * @brief	ポケモン交換デモ（シーン０：これから送るポケモンがボールに入る）
 * @author	taya
 * @date	2006.04.12
 */
//============================================================================================
#include "demo_trade_common.h"
#include "demo_trade_3d.h"

#include "gflib\msg_print.h"
#include "gflib\calctool.h"
#include "system\window.h"
#include "system\font_arc.h"
#include "communication\wm_icon.h"



//======================================================================================================
// 動作させながら調整したいパラメータ群
//======================================================================================================


#ifdef		RUNTIME_ADJUST
#define	DECLARE_VALUE(type, name, value)	static type name = value
#else
#define	DECLARE_VALUE(type, name, value)	enum { name = value }
#endif



DECLARE_VALUE(fx32,	BALL_GRAVITY,		-0x780);	// 重力
DECLARE_VALUE(fx32,	BALL_START_SPEED,	0x2f60);	// 初期速度
DECLARE_VALUE(fx32,	BALL_REF_SPEED_MIN,	0xfa0);		// 反射後の速度がこれ以下なら停止
DECLARE_VALUE(fx32,	BALL_REF_RATIO,		0x2c);		// 反射係数
DECLARE_VALUE(fx32,	BALL_START_YOFS,	0xffff6800);// 初期Ｙ位置調整用
DECLARE_VALUE(fx32,	BALL_START_ZOFS,	0x37800);	// 初期Ｚ位置調整用

DECLARE_VALUE(fx32,	BALL_ROT_SPEED1,	0xb0);		//
DECLARE_VALUE(fx32,	BALL_ROT_SPEED2,	0x50);		//
DECLARE_VALUE(fx32, BALL_ROT_MOVE_RATIO,  0x05);
DECLARE_VALUE(fx32, BALL_ROT_DOWN_SPEED,  0x0e);

//----------------------------------------------
/**
 *	定数
 */ 
//----------------------------------------------
enum {
	POKE_DISP_X = 128,
	POKE_DISP_Y = 90,

	SPOTLIGHT_DISP_X = POKE_DISP_X,
	SPOTLIGHT_DISP_Y = POKE_DISP_Y + 10,

	EFFECT_DISP_X = POKE_DISP_X,
	EFFECT_DISP_Y = POKE_DISP_Y,

	BALL_DEFAULT_X = 0,
	BALL_DEFAULT_Y = (((192/2)-POKE_DISP_Y) + 30) << FX32_SHIFT,
	BALL_DEFAULT_Z = (60<<FX32_SHIFT),

	BALL_REF_Y = ((192/2)-SPOTLIGHT_DISP_Y) << FX32_SHIFT,

};


// アクターＩＤ
enum {
	ACTID_SPOTLIGHT,
	ACTID_EFFECT,
	ACTID_MAX,
};


// BGキャラ配置
enum {
	WIN_DISP_X = 2,
	WIN_DISP_Y = 19,
	WIN_WIDTH = 27,
	WIN_HEIGHT = 4,
	WIN_CHAR_SIZE = WIN_WIDTH*WIN_HEIGHT,

	CHARPOS_CLEAR = 0,
	CHARPOS_WIN = 1,
	CHARPOS_WIN_FRAME = CHARPOS_WIN + WIN_CHAR_SIZE,

	PAL_BG = 0,
	PAL_WIN,
	PAL_WIN_FRAME,
};




typedef struct {
	DEMO_TRADE_WORK*  mainWork;
	int seq;
	int timer;

	SOFT_SPRITE_MANAGER*	spriteManager;
	SOFT_SPRITE*			sprite;
	SOFT_SPRITE_ANIME		spriteAnim[SS_ANM_SEQ_MAX];

	CLACT_WORK_PTR			act[ACTID_MAX];
	DEMO_TRADE_CELLANIM		clpack;

	GF_BGL_INI*				bgl;
	GF_BGL_BMPWIN			win;

	STRBUF*					loadStrBuf;
	STRBUF*					expandStrBuf;

	DT3DMAN*				dt3dMan;
	DT3DOBJ*				objBall;

	TCB_PTR					flushTask;
	TCB_PTR					ballMoveTask;

}SCENE0_WORK;

//==============================================================
// Prototype
//==============================================================
static void main_tail_proc( SCENE0_WORK* wk );
static int subseq_setup( SCENE0_WORK* wk, int* seq );
static int subseq_spotlight( SCENE0_WORK* wk, int* seq );
static int subseq_message( SCENE0_WORK* wk, int* seq );
static int subseq_poke_flush( SCENE0_WORK* wk, int* seq );
static int subseq_wait( SCENE0_WORK* wk, int* seq );
static void setup_3d_graphics( SCENE0_WORK* wk );
static SOFT_SPRITE* create_sendpoke_sprite( SCENE0_WORK* wk );
static void setup_actors( SCENE0_WORK* wk);
static void cleanup_actors( SCENE0_WORK* wk );
static void start_3dframe_flush_task( SCENE0_WORK* wk, int start_evy, int end_evy, int wait );
static BOOL wait_3dframe_flush_task( SCENE0_WORK* wk );
static void delete_3dframe_flush_task( SCENE0_WORK* wk );
static void task_3dframe_flush(TCB_PTR tcb, void* wk_adrs );
static void start_ballmove_task( SCENE0_WORK* wk );
static BOOL wait_ballmove_task( SCENE0_WORK* wk );
static int get_ballmove_bound_count(SCENE0_WORK* wk );
static void delete_ballmove_task( SCENE0_WORK* wk );
static void ballmove_task( TCB_PTR tcb, void* wk_adrs );


//------------------------------------------------------------------
/**
 * シーン０ワーク構築
 *
 * @param   mainWork		
 *
 * @retval  void*		作成したシーン用ワークポインタ
 */
//------------------------------------------------------------------
void* DemoTrade_Scene0Init( DEMO_TRADE_WORK* mainWork )
{
	SCENE0_WORK* wk = sys_AllocMemory( HEAPID_DEMO_TRADE_SUB, sizeof(SCENE0_WORK) );
	if( wk )
	{
		int i;

		wk->mainWork = mainWork;
		wk->seq = 0;
		wk->bgl = DemoTrade_GetBgl(mainWork);

		wk->spriteManager = SoftSpriteInit( HEAPID_DEMO_TRADE_SUB );
		wk->sprite = NULL;

		wk->loadStrBuf = STRBUF_Create( 300, HEAPID_DEMO_TRADE_SUB );
		wk->expandStrBuf = STRBUF_Create( 300, HEAPID_DEMO_TRADE_SUB );

		wk->flushTask = NULL;
		wk->ballMoveTask = NULL;

	}
	return wk;
}
//------------------------------------------------------------------
/**
 * シーン０ワーク破棄
 *
 * @param   void*		シーン用ワークポインタ
 */
//------------------------------------------------------------------
void DemoTrade_Scene0Quit( void* wk_adrs )
{
	SCENE0_WORK* wk = wk_adrs;
	if( wk )
	{
		int i;

		delete_3dframe_flush_task( wk );
		delete_ballmove_task( wk );
		cleanup_actors( wk );

		STRBUF_Delete(wk->loadStrBuf);
		STRBUF_Delete(wk->expandStrBuf);

		DT3DMAN_Delete(wk->dt3dMan);

		GF_BGL_BGControlExit(wk->bgl, GF_BGL_FRAME1_M);
		GF_BGL_BGControlExit(wk->bgl, GF_BGL_FRAME2_M);
		GF_BGL_BGControlExit(wk->bgl, GF_BGL_FRAME2_S);
		GF_BGL_BmpWinDel( &(wk->win) );


		if( wk->sprite )
		{
			SoftSpriteDel( wk->sprite );
		}

		SoftSpriteEnd( wk->spriteManager );
		sys_FreeMemoryEz( wk );
	}
}
//------------------------------------------------------------------
/**
 * シーン０メイン
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  BOOL	TRUEでシーン終了
 */
//------------------------------------------------------------------
BOOL DemoTrade_Scene0Main( void* wk_adrs, int* seq )
{
	static int (* const subseq[])(SCENE0_WORK*, int*) = {
		subseq_setup,
		subseq_spotlight,
		subseq_message,
		subseq_poke_flush,
	};

	SCENE0_WORK* wk = wk_adrs;

	if( (*seq) < NELEMS(subseq) )
	{
		if( subseq[*seq](wk, &(wk->seq)) )
		{
			(*seq)++;
			wk->seq = 0;
		}

		main_tail_proc( wk );

		return FALSE;
	}
	return TRUE;
}
//------------------------------------------------------------------
/**
 * メインの最後に呼ばれる
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void main_tail_proc( SCENE0_WORK* wk )
{
	G3X_Reset();

#if 1
	NNS_G3dGePushMtx();
	{
		NNS_G3dGeFlushBuffer();

		// ソフトウェアスプライトの描画
		// カメラセットアップ
		NNS_G2dSetupSoftwareSpriteCamera();
		// ソフトウェアスプライト描画
		SoftSpriteTextureTrans( wk->spriteManager );
		SoftSpriteMain( wk->spriteManager );
	}
	NNS_G3dGePopMtx(1);
#endif

	DT3DMAN_Draw( wk->dt3dMan );

	/* ジオメトリ＆レンダリングエンジン関連メモリのスワップ */
	GF_G3_RequestSwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_Z);
//	G3_SwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_Z);
}



//------------------------------------------------------------------
/**
 * サブシーケンス：グラフィックセットアップ
 *
 * @param   mainWork
 *
 * @retval  int
 */
//------------------------------------------------------------------
static int subseq_setup( SCENE0_WORK* wk, int* seq )
{
	static const GF_BGL_DISPVRAM SetBankData = {
		GX_VRAM_BG_128_B,				// メイン2DエンジンのBG
		GX_VRAM_BGEXTPLTT_23_G,			// メイン2DエンジンのBG拡張パレット
		GX_VRAM_SUB_BG_128_C,			// サブ2DエンジンのBG
		GX_VRAM_SUB_BGEXTPLTT_32_H,		// サブ2DエンジンのBG拡張パレット
		GX_VRAM_OBJ_16_F,				// メイン2DエンジンのOBJ
		GX_VRAM_OBJEXTPLTT_NONE,		// メイン2DエンジンのOBJ拡張パレット
		GX_VRAM_SUB_OBJ_16_I,			// サブ2DエンジンのOBJ
		GX_VRAM_SUB_OBJEXTPLTT_NONE,	// サブ2DエンジンのOBJ拡張パレット
		GX_VRAM_TEX_0_A,				// テクスチャイメージスロット
		GX_VRAM_TEXPLTT_0123_E			// テクスチャパレットスロット
	};

	static const GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_3D,
	};

	static const GF_BGL_BGCNT_HEADER header1 = {
		0, 0, 0x800, 0,	// scrX, scrY, scrbufSize, scrbufofs,
		GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
		GX_BG_SCRBASE_0xf800, GX_BG_CHARBASE_0x00000,
		GX_BG_EXTPLTT_01, 0, 0, 0, FALSE	// pal, pri, areaover, dmy, mosaic
	};
	static const GF_BGL_BGCNT_HEADER header2 = {
		0, 0, 0, 0,	// scrX, scrY, scrbufSize, scrbufofs,
		GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
		GX_BG_SCRBASE_0xf000, GX_BG_CHARBASE_0x04000,
		GX_BG_EXTPLTT_01, 2, 0, 0, FALSE	// pal, pri, areaover, dmy, mosaic
	};



	GF_Disp_SetBank( &SetBankData );
	GX_SetDispSelect(GX_DISP_SELECT_SUB_MAIN);
	GF_BGL_InitBG( &BGsys_data );

	GF_BGL_BGControlSet( wk->bgl, GF_BGL_FRAME1_M, &header1, GF_BGL_MODE_TEXT );
	GF_BGL_BGControlSet( wk->bgl, GF_BGL_FRAME2_M, &header2, GF_BGL_MODE_TEXT );
	GF_BGL_BGControlSet( wk->bgl, GF_BGL_FRAME2_S, &header2, GF_BGL_MODE_TEXT );

	// ３Ｄ使用面の設定(表示＆プライオリティー)
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
    G2_SetBG0Priority(1);

	GF_BGL_CharFill( wk->bgl, GF_BGL_FRAME1_M, 0x00, 1, 0 );
	GF_BGL_ScrFill( wk->bgl, GF_BGL_FRAME1_M, 0x0000, 0, 0, 32, 32, 0 );

	TalkWinGraphicSet( wk->bgl, GF_BGL_FRAME1_M, CHARPOS_WIN_FRAME, PAL_WIN_FRAME,
		 DemoTrade_GetWinFrameType(wk->mainWork), HEAPID_DEMO_TRADE_SUB );
	GF_BGL_BmpWinAdd( wk->bgl, &(wk->win), GF_BGL_FRAME1_M, WIN_DISP_X, WIN_DISP_Y, WIN_WIDTH, WIN_HEIGHT, PAL_WIN, CHARPOS_WIN );
	GF_BGL_BmpWinDataFill( &(wk->win), 0x0f );

	ArcUtil_PalSet( ARC_FONT, NARC_font_talk_ncrl, PALTYPE_MAIN_BG, PAL_WIN*0x20, 0x20, HEAPID_DEMO_TRADE_SUB );


	ArcUtil_BgCharSet(ARC_DEMO_TRADE_GRA, NARC_demo_trade_dark_lz_ncgr, wk->bgl, GF_BGL_FRAME2_M, 0, 0, TRUE, HEAPID_DEMO_TRADE_SUB );
	ArcUtil_ScrnSet(ARC_DEMO_TRADE_GRA, NARC_demo_trade_dark_lz_nscr, wk->bgl, GF_BGL_FRAME2_M, 0, 0, TRUE, HEAPID_DEMO_TRADE_SUB );
	ArcUtil_PalSet(ARC_DEMO_TRADE_GRA, NARC_demo_trade_dark_nclr, PALTYPE_MAIN_BG, PAL_BG*0x20, 0x20, HEAPID_DEMO_TRADE_SUB);

	ArcUtil_BgCharSet(ARC_DEMO_TRADE_GRA, NARC_demo_trade_dark_lz_ncgr, wk->bgl, GF_BGL_FRAME2_S, 0, 0, TRUE, HEAPID_DEMO_TRADE_SUB );
	ArcUtil_ScrnSet(ARC_DEMO_TRADE_GRA, NARC_demo_trade_dark_lz_nscr, wk->bgl, GF_BGL_FRAME2_S, 0, 0, TRUE, HEAPID_DEMO_TRADE_SUB );
	ArcUtil_PalSet(ARC_DEMO_TRADE_GRA, NARC_demo_trade_dark_nclr, PALTYPE_SUB_BG, PAL_BG*0x20, 0x20, HEAPID_DEMO_TRADE_SUB);

	GF_BGL_LoadScreenReq( wk->bgl, GF_BGL_FRAME1_M );

	setup_3d_graphics(wk);
	wk->dt3dMan = DT3DMAN_Create(1, 0, 0, 0);
	wk->sprite = create_sendpoke_sprite(wk);
	wk->objBall = DT3D_AddObj( wk->dt3dMan, 0, ARC_DEMO_TRADE_GRA, NARC_demo_trade_trade_psel_nsbmd,
		BALL_DEFAULT_X, BALL_DEFAULT_Y+BALL_START_YOFS, BALL_DEFAULT_Z+BALL_START_ZOFS , FALSE );
	{
		VecFx16 rot = { 0x0000, 0xf000, 0x0000 };
		DT3D_SetObjRot( wk->objBall, &rot );
	}


	GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );
	GF_Disp_GXS_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );

	setup_actors(wk);

	G2_BlendNone();

	// Vramバンク設定によってアイコンを作り直す必要がある
	WirelessIconEasy();
	WirelessIconEasy_HoldLCD( TRUE, HEAPID_DEMO_TRADE_MAIN );


	WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN, WIPE_FADE_BLACK, 16, 1, HEAPID_DEMO_TRADE_SUB );

	return TRUE;
}
//------------------------------------------------------------------
/**
 * サブシーケンス：スポットライト表示
 *
 * @param   mainWork
 *
 * @retval  int
 */
//------------------------------------------------------------------
static int subseq_spotlight( SCENE0_WORK* wk, int* seq )
{
	switch( *seq ){
	case 0:
		if( WIPE_SYS_EndCheck() )
		{
			CLACT_AnmChg( wk->act[ACTID_SPOTLIGHT], ANM_SPOTLIGHT );
			CLACT_SetDrawFlag( wk->act[ACTID_SPOTLIGHT], TRUE );
			return TRUE;
		}
		break;
	}
	return FALSE;
}
//------------------------------------------------------------------
/**
 * サブシーケンス：メッセージ表示
 *
 * @param   mainWork
 *
 * @retval  int
 */
//------------------------------------------------------------------
static int subseq_message( SCENE0_WORK* wk, int* seq )
{
	switch( *seq ){
	case 0:
		wk->timer = 0;
		(*seq)++;
		break;

	case 1:
		if( ++(wk->timer) > 10 )
		{
			MSGDATA_MANAGER* mm = DemoTrade_GetMsgManager( wk->mainWork );
			WORDSET* wordset = DemoTrade_GetWordSet( wk->mainWork );
			int strID, nextSeq;

			if( DemoTrade_GetSeq(wk->mainWork) == DEMO_TRADE_SEQ_FULL )
			{
				strID = msg_start_00;
				nextSeq = 2;
			}
			else
			{
				strID = msg_send_only;
				nextSeq = 3;
			}

			MSGMAN_GetString( mm, strID, wk->loadStrBuf );
			WORDSET_ExpandStr( wordset, wk->expandStrBuf, wk->loadStrBuf );

			GF_STR_PrintSimple( &(wk->win), FONT_TALK, wk->expandStrBuf, 0, 0, MSG_NO_PUT, NULL );

			BmpTalkWinScreenSet( &(wk->win), CHARPOS_WIN_FRAME, PAL_WIN_FRAME );
			GF_BGL_BmpWinOn( &(wk->win) );

			wk->timer = 0;
			(*seq) = nextSeq;
		}
		break;

	case 2:
		if( ++(wk->timer) > 60 )
		{
			MSGDATA_MANAGER* mm = DemoTrade_GetMsgManager( wk->mainWork );
			WORDSET* wordset = DemoTrade_GetWordSet( wk->mainWork );

			MSGMAN_GetString( mm, msg_start_01, wk->loadStrBuf );
			WORDSET_ExpandStr( wordset, wk->expandStrBuf, wk->loadStrBuf );

			{
				const POKEMON_PASO_PARAM* ppp = DemoTrade_GetSendPokeParam(wk->mainWork);

				if( PokePasoParaGet((POKEMON_PASO_PARAM*)ppp, ID_PARA_tamago_flag, NULL) == FALSE)
				{
					SoftSpriteAnimeSet( wk->sprite, 1 );
					Snd_PMVoicePlay( DemoTrade_GetSendPokeNumber(wk->mainWork) );
				}
				GF_BGL_BmpWinDataFill( &(wk->win), 0x0f );
				GF_STR_PrintSimple( &(wk->win), FONT_TALK, wk->expandStrBuf, 0, 0, MSG_NO_PUT, NULL );
				GF_BGL_BmpWinCgxOn( &(wk->win) );
				wk->timer = 0;
				(*seq)++;
			}
		}
		break;

	case 3:
		if( ++(wk->timer) > 60 )
		{
			BmpTalkWinClear( &(wk->win), WINDOW_TRANS_ON );
			wk->timer = 0;
			(*seq)++;
		}
		break;

	case 4:
		if( ++(wk->timer) > 20 )
		{
			return TRUE;
		}
		break;

	}
	return FALSE;
}
//------------------------------------------------------------------
/**
 * サブシーケンス：ポケモン光って消える
 *
 * @param   mainWork
 *
 * @retval  int
 */
//------------------------------------------------------------------
static int subseq_poke_flush( SCENE0_WORK* wk, int* seq )
{
	switch( *seq ){
	case 0:
		Snd_SePlay( SE_POKE_TO_BALL );
		start_3dframe_flush_task( wk, 0, 16, 12 );
		(*seq)++;
		break;

	case 1:
		if( wait_3dframe_flush_task( wk ) )
		{
			SoftSpriteDel( wk->sprite );
			CLACT_AnmChg( wk->act[ACTID_EFFECT], ANM_EFFECT );
			CLACT_SetDrawFlag( wk->act[ACTID_EFFECT], TRUE );
			(*seq)++;
		}
		break;

	case 2:
		if( CLACT_AnmActiveCheck( wk->act[ACTID_EFFECT] ) == FALSE )
		{
			DT3D_SetObjDrawFlag( wk->objBall, TRUE );
			start_3dframe_flush_task( wk, 16, 0, 16 );
			start_ballmove_task( wk );
			(*seq)++;
		}
		break;

	case 3:
		if(	(get_ballmove_bound_count(wk) >= 2 )
		||	(wait_ballmove_task(wk) == TRUE)
		){
			WIPE_SYS_Start( WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, WIPE_FADE_BLACK, 24, 1, HEAPID_DEMO_TRADE_SUB );
			(*seq)++;
		}
		break;

	case 4:
#if 1
		if( WIPE_SYS_EndCheck() )
		{
			if( wait_ballmove_task(wk) )
			{
				return TRUE;
			}
		}
#endif
		#ifdef RUNTIME_ADJUST
		if(sys.cont & PAD_BUTTON_A){ DT_adjustValue32(&BALL_START_YOFS, 0x800, sys.repeat, "YOFS"); }
		if(sys.cont & PAD_BUTTON_B){ DT_adjustValue32(&BALL_GRAVITY, 0x10, sys.repeat, "Gravity"); }
		if(sys.cont & PAD_BUTTON_X){ DT_adjustValue32(&BALL_ROT_MOVE_RATIO, 0x1, sys.repeat, "Ball Move Ratio"); }
		if(sys.cont & PAD_BUTTON_Y){ DT_adjustValue32(&BALL_ROT_DOWN_SPEED, 0x1, sys.repeat, "rot down speed"); }
		if(sys.cont & PAD_BUTTON_L){ DT_adjustValue32(&BALL_ROT_SPEED1, 0x02, sys.repeat, "rot1"); }
		if(sys.cont & PAD_BUTTON_R){ DT_adjustValue32(&BALL_ROT_SPEED2, 0x02, sys.repeat, "rot2"); }
		#endif
		break;
	}

	return FALSE;
}




//==============================================================================================
//==============================================================================================

static void setup_3d_graphics( SCENE0_WORK* wk )
{
	NNSGfdTexKey	texKey;
	NNSGfdPlttKey	plttKey;

	// NitroSystem:３Ｄエンジンの初期化
	NNS_G3dInit();
	// マトリクススタックの初期化
    G3X_InitMtxStack();

	// 各種描画モードの設定(シェード＆アンチエイリアス＆半透明)
    G3X_SetShading(GX_SHADING_TOON);
    G3X_AntiAlias(TRUE);

	G3X_AlphaTest(FALSE, 0);	// アルファテスト　　オフ
	G3X_AlphaBlend(TRUE);		// アルファブレンド　オン

	// クリアカラーの設定
    G3X_SetClearColor(GX_RGB(0, 0, 0),	// clear color
                      0,				// clear alpha
                      0x7fff,			// clear depth
                      63,				// clear polygon ID
                      FALSE				// fog
                      );

	// ジオメトリエンジン起動後必ず呼ばれなければならない
    G3_SwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_W);

	// ビューポートの設定
    G3_ViewPort(0, 0, 255, 191);

    NNS_GfdInitFrmTexVramManager(1, TRUE);
    NNS_GfdInitFrmPlttVramManager(0x4000, TRUE);

	texKey = NNS_GfdAllocTexVram(0x4000, FALSE, 0);
	plttKey = NNS_GfdAllocPlttVram(0x80, FALSE, NNS_GFD_ALLOC_FROM_LOW);

	SoftSpriteTextureTransParamSet( 
			wk->spriteManager,
			NNS_GfdGetTexKeyAddr(texKey),
			NNS_GfdGetTexKeySize(texKey) );

	SoftSpritePaletteTransParamSet( 
			wk->spriteManager,
			NNS_GfdGetPlttKeyAddr(plttKey),
			NNS_GfdGetPlttKeySize(plttKey) );


}
//------------------------------------------------------------------
/**
 * これから送るポケモンのソフトスプライトを生成
 *
 * @param   wk		
 *
 * @retval  SOFTSPRITE*		
 */
//------------------------------------------------------------------
static SOFT_SPRITE* create_sendpoke_sprite( SCENE0_WORK* wk )
{
	SOFT_SPRITE_ARC  arc;
	POKEMON_PASO_PARAM* ppp;
	int ypos;

	ppp = (POKEMON_PASO_PARAM*)DemoTrade_GetSendPokeParam(wk->mainWork);

	PokeGraArcDataGetPPP( &arc, ppp, PARA_FRONT );
	PokeAnmDataSet( wk->spriteAnim, DemoTrade_GetSendPokeNumber(wk->mainWork) );

	ypos = (SPOTLIGHT_DISP_Y - 20) + PokePasoParaHeightGet(ppp, PARA_FRONT);

	return SoftSpriteAdd( wk->spriteManager, &arc, POKE_DISP_X, ypos, 0, 0, wk->spriteAnim, NULL );
}


//==============================================================================================
//==============================================================================================

static void setup_actors( SCENE0_WORK* wk)
{
	NNSG2dImagePaletteProxy	palProxy;
	NNSG2dImageProxy		imgProxy;
	CLACT_HEADER			header;

	DemoTrade_LoadCellAnimDatas( &wk->clpack, ARC_DEMO_TRADE_GRA, NARC_demo_trade_trade01_lz_ncer, NARC_demo_trade_trade01_lz_nanr );

	NNS_G2dInitImagePaletteProxy(&palProxy);
	NNS_G2dInitImageProxy(&imgProxy);

	ArcUtil_CharSysLoad(ARC_DEMO_TRADE_GRA, NARC_demo_trade_trade_obj01_lz_ncgr, TRUE, CHAR_MAP_1D, 0,
					NNS_G2D_VRAM_TYPE_2DMAIN, 0, HEAPID_DEMO_TRADE_SUB, &imgProxy );

	ArcUtil_PalSysLoad( ARC_DEMO_TRADE_GRA, NARC_demo_trade_trade_obj01_nclr, NNS_G2D_VRAM_TYPE_2DMAIN, 0,
					HEAPID_DEMO_TRADE_SUB, &palProxy );

	DemoTrade_SetActHeader( &header, &wk->clpack, &imgProxy, &palProxy, 2 );

	wk->act[ACTID_SPOTLIGHT] = DemoTrade_AddActor(wk->mainWork, &header, SPOTLIGHT_DISP_X, SPOTLIGHT_DISP_Y, 0, NNS_G2D_VRAM_TYPE_2DMAIN );
	wk->act[ACTID_EFFECT] = DemoTrade_AddActor(wk->mainWork, &header, EFFECT_DISP_X, EFFECT_DISP_Y, 0, NNS_G2D_VRAM_TYPE_2DMAIN );
	CLACT_BGPriorityChg( wk->act[ACTID_EFFECT], 1 );
	CLACT_SetDrawFlag( wk->act[ACTID_SPOTLIGHT], FALSE );
	CLACT_SetDrawFlag( wk->act[ACTID_EFFECT], FALSE );
}

static void cleanup_actors( SCENE0_WORK* wk )
{
	int i;

	for(i=0; i<ACTID_MAX; i++)
	{
		if( wk->act[i] )
		{
			CLACT_Delete(wk->act[i]);
		}
	}
	DemoTrade_UnloadCellAnimDatas( &wk->clpack );
}


//==============================================================================================
//==============================================================================================
typedef struct {
	SCENE0_WORK*   parent;
	fx32  val;
	fx32  end_val;
	fx32  add_val;
	int   timer;
}POKE_FLUSH_WORK;

//------------------------------------------------------------------
/**
 * 3D面の輝度変更タスク開始
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void start_3dframe_flush_task( SCENE0_WORK* wk, int start_evy, int end_evy, int wait )
{
	POKE_FLUSH_WORK* twk = sys_AllocMemory( HEAPID_DEMO_TRADE_SUB, sizeof(POKE_FLUSH_WORK) );

	if( twk )
	{
		twk->parent = wk;
		twk->val = start_evy << FX32_SHIFT;
		twk->end_val = end_evy << FX32_SHIFT;
		twk->add_val = (twk->end_val - twk->val) / wait;
		twk->timer = wait;
		wk->flushTask = VIntrTCB_Add( task_3dframe_flush, twk, VINTR_TASKPRI_DEFAULT );
		G2_SetBlendBrightness( GX_BLEND_PLANEMASK_BG0, start_evy );
	}
}

static BOOL wait_3dframe_flush_task( SCENE0_WORK* wk )
{
	return wk->flushTask == NULL;
}

static void delete_3dframe_flush_task( SCENE0_WORK* wk )
{
	if( wk->flushTask )
	{
		DemoTrade_IRQ_FreeReq( TCB_GetWork(wk->flushTask) );
		TCB_Delete(wk->flushTask);
		wk->flushTask = NULL;
	}
}


static void task_3dframe_flush(TCB_PTR tcb, void* wk_adrs )
{
	POKE_FLUSH_WORK* twk = wk_adrs;
	int bright;

	if( --(twk->timer) > 0 )
	{
		twk->val += twk->add_val;
		bright = twk->val >> FX32_SHIFT;
		G2_SetBlendBrightness( GX_BLEND_PLANEMASK_BG0, bright );
	}
	else
	{
		bright = twk->end_val >> FX32_SHIFT;
		G2_SetBlendBrightness( GX_BLEND_PLANEMASK_BG0, bright );
		delete_3dframe_flush_task(twk->parent);
	}
}

//==============================================================================================
//==============================================================================================

typedef struct {
	SCENE0_WORK*   parent;
	DT3DOBJ*  obj;
	VecFx32   pos;
	VecFx16   rot;
	fx32      speed;
	int       boundCount;
	BOOL      boundStopFlag;
	int       timer;
	fx16      rotVal;
}BALLMOVE_WORK;


static void start_ballmove_task( SCENE0_WORK* wk )
{
	BALLMOVE_WORK*  twk = sys_AllocMemory( HEAPID_DEMO_TRADE_SUB, sizeof(BALLMOVE_WORK) );
	if( twk )
	{
		twk->parent = wk;
		twk->obj = wk->objBall;
		DT3D_GetObjPos( twk->obj, &(twk->pos) );
		DT3D_GetObjRot( twk->obj, &(twk->rot) );
		twk->speed = BALL_START_SPEED;
		twk->boundCount = 0;
		twk->rotVal = 0;
		twk->boundStopFlag = FALSE;
		twk->timer = 0;

		wk->ballMoveTask = TCB_Add(ballmove_task, twk, TASKPRI_DEFAULT);
	}
}
static BOOL wait_ballmove_task( SCENE0_WORK* wk )
{
	return (wk->ballMoveTask == NULL);
}

static int get_ballmove_bound_count(SCENE0_WORK* wk )
{
	if( wk->ballMoveTask )
	{
		BALLMOVE_WORK* twk = TCB_GetWork( wk->ballMoveTask );
		return twk->boundCount;
	}
	return 0;
}

static void delete_ballmove_task( SCENE0_WORK* wk )
{
	if( wk->ballMoveTask )
	{
		sys_FreeMemoryEz( TCB_GetWork(wk->ballMoveTask) );
		TCB_Delete( wk->ballMoveTask );
		wk->ballMoveTask = NULL;
	}
}

static void ballmove_task( TCB_PTR tcb, void* wk_adrs )
{
	BALLMOVE_WORK* wk = wk_adrs;
	BOOL endFlag = FALSE;


	if( wk->boundStopFlag == FALSE )
	{
		wk->pos.y += wk->speed;

		if( wk->speed >= 0 )
		{
			wk->speed += BALL_GRAVITY;
		}
		else
		{
			wk->speed += BALL_GRAVITY;

			if( wk->pos.y <= BALL_REF_Y )
			{
				wk->pos.y = BALL_REF_Y;
				wk->speed = - ((wk->speed * BALL_REF_RATIO)/100);
				if( wk->speed < BALL_REF_SPEED_MIN )
				{
					wk->boundStopFlag = TRUE;
				}
				Snd_SePlay(SE_BALL_REFRECT);
				wk->boundCount++;
				switch(wk->boundCount){
				case 1: wk->rotVal = BALL_ROT_SPEED1; break;
				case 3: wk->rotVal += BALL_ROT_SPEED2; break;
				}
			}
		}
	}

	wk->rot.x += wk->rotVal;
	wk->rot.z -= wk->rotVal;
	DT3D_SetObjRot( wk->obj, &(wk->rot) );

	wk->pos.x += (wk->rotVal * BALL_ROT_MOVE_RATIO);
	wk->pos.z += (wk->rotVal * BALL_ROT_MOVE_RATIO);
	DT3D_SetObjPos( wk->obj, &(wk->pos) );

	if( wk->boundStopFlag )
	{
		wk->rotVal -= BALL_ROT_DOWN_SPEED;
		if(++(wk->timer) > 30)
		{
			delete_ballmove_task( wk->parent );
		}
	}
}
/*
DECLARE_VALUE(fx32,	BALL_GRAVITY,		0x780);
DECLARE_VALUE(fx32,	BALL_START_SPEED,	0x900);
DECLARE_VALUE(fx32,	BALL_SPEED_MIN,		0xa00);
DECLARE_VALUE(fx32,	BALL_REF_RATIO,		0x2c);
DECLARE_VALUE(fx32,	BALL_START_YOFS,	0x8000);
}
*/
