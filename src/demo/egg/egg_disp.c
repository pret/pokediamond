//==============================================================================
/**
 * @file	egg_disp.c
 * @brief	画面周りのシステム
 * @author	goto
 * @date	2006.05.20(土)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================
#include "common.h"
#include "poketool/poke_tool.h"
#include "system/procsys.h"
#include "system/snd_tool.h"
#include "include/system/lib_pack.h"
#include "include/system/brightness.h"
#include "include/system/heapdefine.h"
#include "include/system/touch_subwindow.h"

#include "system/bmp_menu.h"
#include "include/system/fontproc.h"
#include "include/system/msgdata.h"
#include "include/system/arc_util.h"
#include "include/system/window.h"
#include "include/system/wordset.h"

#include "msgdata/msg.naix"

#include "demo/egg/data/egg_data_def.h"
#include "demo/egg/data/particle/egg_demo_setup.h"
#include "src/field/poketch/poketch_arc.h"

#include "battle/battle_common.h"
#include "wazaeffect/wazatool.h"

#include "system/wipe.h"

#include "demo/egg/egg.h"

extern void EggDisp_SystemInit(void);
extern void EggDisp_DefaultBlendSet(void);
extern GF_G3DMAN* EggDisp_3D_Init(void);
extern void EggDisp_3DSetUp(void);
extern void EggDisp_3DVramInit(void);


// =============================================================================
//
//
//	□ 描画システム関連
//
//
// =============================================================================
//--------------------------------------------------------------
/**
 * @brief	システム初期化
 *
 * @param	none	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void EggDisp_SystemInit(void)
{
	GF_Disp_GX_VisibleControlInit();
	GF_Disp_GXS_VisibleControlInit();
	GX_SetVisiblePlane(0);
	GXS_SetVisiblePlane(0);	
}


//--------------------------------------------------------------
/**
 * @brief	基本α設定
 *
 * @param	none	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void EggDisp_DefaultBlendSet(void)
{
	G2_SetBlendAlpha(GX_BLEND_PLANEMASK_NONE,
					 GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG3, 11, 7);
	G2S_SetBlendAlpha(GX_BLEND_PLANEMASK_NONE,
					  GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG2 |
					  GX_BLEND_PLANEMASK_BG3, 7, 8);
}


//--------------------------------------------------------------
/**
 * @brief	3D初期化
 *
 * @param	none	
 *
 * @retval	GF_G3DMAN*	
 *
 */
//--------------------------------------------------------------
GF_G3DMAN* EggDisp_3D_Init(void)
{
	GF_G3DMAN *g3Dman;
	
	g3Dman = GF_G3DMAN_Init(HEAPID_EGG_DEMO,
							GF_G3DMAN_LNK,
							GF_G3DTEX_256K, 
							GF_G3DMAN_LNK,
							GF_G3DPLT_32K,
							EggDisp_3DSetUp);
	
	return g3Dman;	
}


//--------------------------------------------------------------
/**
 * @brief	3Dセットアップ
 *
 * @param	none	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void EggDisp_3DSetUp(void)
{
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
    G2_SetBG0Priority(1);

    G3X_SetShading( GX_SHADING_TOON );
    G3X_AntiAlias( TRUE );
	G3X_AlphaTest( FALSE, 0 );
	G3X_AlphaBlend( TRUE );
	G3X_EdgeMarking( FALSE );
	G3X_SetFog( FALSE, GX_FOGBLEND_COLOR_ALPHA, GX_FOGSLOPE_0x8000, 0 );

    G3X_SetClearColor(GX_RGB(0,0,0),0,0x7fff,63,FALSE);	//color,alpha,depth,polygonID,fog

    G3_ViewPort(0, 0, 255, 191);
}


//--------------------------------------------------------------
/**
 * @brief	3DVram初期化
 *
 * @param	none	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void EggDisp_3DVramInit(void)
{
	NNSGfdTexKey tex_key;
	NNSGfdPlttKey pltt_key;
	u32 tex_addrs, pltt_addrs;
	
	tex_key		= NNS_GfdAllocTexVram(0x2000 * CLIENT_MAX, 0, 0);
	pltt_key	= NNS_GfdAllocPlttVram(0x20 * CLIENT_MAX, 0, 0);
	
	GF_ASSERT(tex_key != NNS_GFD_ALLOC_ERROR_TEXKEY);
	GF_ASSERT(pltt_key != NNS_GFD_ALLOC_ERROR_PLTTKEY);
	
	tex_addrs	= NNS_GfdGetTexKeyAddr(tex_key);
	pltt_addrs	= NNS_GfdGetPlttKeyAddr(pltt_key);
	
	OS_TPrintf("ポケモン用に確保した テクスチャVramの先頭アドレス＝%d\n", tex_addrs);
	OS_TPrintf("ポケモン用に確保した 　パレットVramの先頭アドレス＝%d\n", pltt_addrs);

	Particle_SystemWorkInit();		
}


//--------------------------------------------------------------
/**
 * @brief	VramBank設定
 *
 * @param	bgl	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void EggDisp_VramBankSet(GF_BGL_INI* bgl)
{
	GF_Disp_GX_VisibleControlInit();	
	
	//VRAM設定
	{
		GF_BGL_DISPVRAM vramSetTable = {
			GX_VRAM_BG_128_A,				// メイン2DエンジンのBG
			GX_VRAM_BGEXTPLTT_NONE,			// メイン2DエンジンのBG拡張パレット
			GX_VRAM_SUB_BG_32_H,			// サブ2DエンジンのBG
			GX_VRAM_SUB_BGEXTPLTT_NONE,		// サブ2DエンジンのBG拡張パレット
			GX_VRAM_OBJ_64_E,				// メイン2DエンジンのOBJ
			GX_VRAM_OBJEXTPLTT_NONE,		// メイン2DエンジンのOBJ拡張パレット
			GX_VRAM_SUB_OBJ_16_I,			// サブ2DエンジンのOBJ
			GX_VRAM_SUB_OBJEXTPLTT_NONE,	// サブ2DエンジンのOBJ拡張パレット
			GX_VRAM_TEX_01_BC,				// テクスチャイメージスロット
			GX_VRAM_TEXPLTT_01_FG			// テクスチャパレットスロット
		};
		GF_Disp_SetBank( &vramSetTable );

		//VRAMクリア
		MI_CpuClear32((void*)HW_BG_VRAM, HW_BG_VRAM_SIZE);
		MI_CpuClear32((void*)HW_DB_BG_VRAM, HW_DB_BG_VRAM_SIZE);
		MI_CpuClear32((void*)HW_OBJ_VRAM, HW_OBJ_VRAM_SIZE);
		MI_CpuClear32((void*)HW_DB_OBJ_VRAM, HW_DB_OBJ_VRAM_SIZE);
	}

	// BG SYSTEM
	{
		GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_3D,
		};
		GF_BGL_InitBG( &BGsys_data );
	}

	//メイン画面フレーム設定
	{
		GF_BGL_BGCNT_HEADER TextBgCntDat[] = {
			///<FRAME1_M
			{
				0, 0, 0x0800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
				GX_BG_SCRBASE_0x0000, GX_BG_CHARBASE_0x04000, GX_BG_EXTPLTT_01,
				0, 0, 0, FALSE
			},
			///<FRAME2_M
			{
				0, 0, 0x2000, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
				GX_BG_SCRBASE_0x1000, GX_BG_CHARBASE_0x0c000, GX_BG_EXTPLTT_01,
				1, 0, 0, FALSE
			},
			///<FRAME3_M
			{
				0, 0, 0x1000, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
				GX_BG_SCRBASE_0x3000, GX_BG_CHARBASE_0x10000, GX_BG_EXTPLTT_01,
				2, 0, 0, FALSE
			},
		};
		GF_BGL_BGControlSet(bgl, GF_BGL_FRAME1_M, &TextBgCntDat[0], GF_BGL_MODE_TEXT );
		GF_BGL_BGControlSet(bgl, GF_BGL_FRAME2_M, &TextBgCntDat[1], GF_BGL_MODE_TEXT );
		GF_BGL_BGControlSet(bgl, GF_BGL_FRAME3_M, &TextBgCntDat[2], GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear(bgl, GF_BGL_FRAME1_M );
		GF_BGL_ScrClear(bgl, GF_BGL_FRAME2_M );
		GF_BGL_ScrClear(bgl, GF_BGL_FRAME3_M );

		G2_SetBG0Priority(BATTLE_3DBG_PRIORITY);
		GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG0, VISIBLE_ON);
	}
	
	GF_Disp_DispOn();
	GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);
	
	///< サブ画面フレーム設定
	{
		GF_BGL_BGCNT_HEADER TextBgCntDat[] = {
			{	///< BG
				0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
				GX_BG_SCRBASE_0x6800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
				0, 0, 0, FALSE
			},
		};
		GF_BGL_BGControlSet(bgl, GF_BGL_FRAME0_S, &TextBgCntDat[0], GF_BGL_MODE_TEXT);
		GF_BGL_ScrClear(bgl, GF_BGL_FRAME0_S);
	}
}

//--------------------------------------------------------------
/**
 * @brief	VBlank関数
 *
 * @param	work	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void EggDisp_VBlank(void* work)
{
	EGG_MAIN_WORK* emwk = (EGG_MAIN_WORK*)work;
	
	SoftSpriteTextureTrans(emwk->sys.ssm_p);

	DoVramTransferManager();					///< Vram転送マネージャー実行
	CATS_RenderOamTrans();
	PaletteFadeTrans(emwk->sys.pfd);
	
	GF_BGL_VBlankFunc(emwk->sys.bgl);
	
	OS_SetIrqCheckFlag(OS_IE_V_BLANK);
}


//--------------------------------------------------------------
/**
 * @brief	パーティクルメイン
 *
 * @param	none	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void EggDisp_ParticleMain(void)
{
	int draw_num;
	const MtxFx43 *camera_ptr;

	GF_G3X_Reset();

	draw_num = Particle_DrawAll();

	if(draw_num > 0){
		GF_G3X_Reset();
		NNS_G2dSetupSoftwareSpriteCamera();
	}

	Particle_CalcAll();
	GF_G3_RequestSwapBuffers(GX_SORTMODE_MANUAL, GX_BUFFERMODE_Z);
}


//--------------------------------------------------------------
/**
 * @brief	ワイプフェードイン
 *
 * @param	none	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void EggDisp_WipeFadeIn(void)
{
	WIPE_SYS_Start(WIPE_PATTERN_WMS,
				   WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN,
				   WIPE_FADE_BLACK, WIPE_DEF_DIV, WIPE_DEF_SYNC, HEAPID_EGG_DEMO);
}

//--------------------------------------------------------------
/**
 * @brief	ワイプフェードアウト
 *
 * @param	none	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void EggDisp_WipeFadeOut(void)
{
	WIPE_SYS_Start(WIPE_PATTERN_WMS,
			   	   WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, 
			   	   WIPE_FADE_BLACK, WIPE_DEF_DIV, WIPE_DEF_SYNC, HEAPID_EGG_DEMO);
}









// =============================================================================
//
//
//	□ 描画ツール関係
//
//
// =============================================================================
//--------------------------------------------------------------
/**
 * @brief	BMP win 登録
 *
 * @param	bgl	
 * @param	pfd	
 * @param	wintype	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void EggDisp_BMP_WindowResLoad(GF_BGL_INI* bgl, PALETTE_FADE_PTR pfd, int wintype)
{
	int heap_id = HEAPID_EGG_DEMO;
	
	TalkWinGraphicSet(bgl,
					  GF_BGL_FRAME1_M,
					  EGG_DEMO_TALK_CHAR_OFS,
					  EDPAL_BACK,
					  wintype,
					 // TalkWinCgxArcGet(wintype),
					  heap_id);
					  
	PaletteWorkSet_Arc(pfd,
					   ARC_WINFRAME,
					   TalkWinPalArcGet(wintype),
					   heap_id,
					   FADE_MAIN_BG,
					   0x20,
					   EDPAL_FRAME * 16);

	MenuWinGraphicSet(bgl,
					  GF_BGL_FRAME1_M,
					  EGG_DEMO_MENU_CHAR_OFS,
					  EDPAL_MENU,
					  0,
					  heap_id);
					  
	PaletteWorkSet_Arc(pfd,
					   ARC_WINFRAME,
					   MenuWinPalArcGet(),
					   heap_id,
					   FADE_MAIN_BG,
					   0x20,
					   EDPAL_MENU * 16);

	///< フォント
	PaletteWorkSet_Arc(pfd,
					   ARC_FONT,
					   NARC_font_talk_ncrl, 
					   heap_id,
					   FADE_MAIN_BG,
					   0x20,
					   EDPAL_FONT * 16);
}

//--------------------------------------------------------------
/**
 * @brief	BMP win追加
 *
 * @param	bgl	
 * @param	win	
 * @param	frm	
 * @param	x	
 * @param	y	
 * @param	sx	
 * @param	sy	
 * @param	ofs	
 * @param	pal	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void EggDisp_BMP_WindowAdd(GF_BGL_INI* bgl, GF_BGL_BMPWIN* win, int frm, int x, int y, int sx, int sy, int ofs, int pal)
{
	GF_BGL_BmpWinInit(win);
	GF_BGL_BmpWinAdd(bgl, win, frm,
					 x, y, sx, sy, pal, ofs);
					 
	BmpTalkWinWrite(win, WINDOW_TRANS_OFF, EGG_DEMO_TALK_CHAR_OFS, EDPAL_FRAME);

	GF_BGL_BmpWinDataFill(win, FBMP_COL_WHITE);
	GF_BGL_BmpWinOn(win);	
}


//--------------------------------------------------------------
/**
 * @brief	BMP win メッセージ登録
 *
 * @param	win	
 * @param	mes_id	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
int EggDisp_BMP_MessageSet(GF_BGL_BMPWIN * win, int mes_id, POKEMON_PARAM* pp, int speed)
{
	int index;
	
	STRBUF*		str;	///< 元データ
	STRBUF*		tmp;	///< 
	WORDSET*	wset;
	POKEMON_PASO_PARAM* ppp;
	
	MSGDATA_MANAGER *man;
	
	GF_BGL_BmpWinDataFill(win, FBMP_COL_WHITE);
	
	///< 初期化
	man  = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG,
						 NARC_msg_egg_demo_dat, HEAPID_EGG_DEMO);
	wset = WORDSET_Create(HEAPID_EGG_DEMO);
	
	str = MSGMAN_AllocString(man, mes_id);
	tmp = STRBUF_Create(255, HEAPID_EGG_DEMO);
	
	ppp = PPPPointerGet(pp);
	
	WORDSET_RegisterPokeMonsName(wset, 0, ppp);
	WORDSET_ExpandStr(wset, tmp, str);
	
	index = GF_STR_PrintSimple(win, FONT_TALK, tmp, 0, 0, speed, NULL);
	
	///< 解放
	MSGMAN_Delete(man);
	STRBUF_Delete(tmp);
	STRBUF_Delete(str);
	WORDSET_Delete(wset);
	
	return index;
}

//--------------------------------------------------------------
/**
 * @brief	はい・いいえ
 *
 * @param	emwk	
 * @param	bgl	
 * @param	win	
 * @param	frm	
 * @param	x	
 * @param	y	
 * @param	sx	
 * @param	sy	
 * @param	ofs	
 * @param	pal	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void EggDisp_SelWindowAdd(EGG_MAIN_WORK* emwk, GF_BGL_INI* bgl, GF_BGL_BMPWIN* win, int frm, int x, int y, int sx, int sy, int ofs, int pal)
{
	BMPMENU_HEADER	mh;
	
	GF_BGL_BmpWinInit(win);
	GF_BGL_BmpWinAdd(bgl, win, frm, x, y, sx, sy, pal, ofs);
	
	emwk->sys.bml = BMP_MENULIST_Create(2, HEAPID_EGG_DEMO);
	
	{
		int i;
		STRBUF* str;
		MSGDATA_MANAGER* man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_egg_demo_dat, HEAPID_EGG_DEMO);
		
		for (i = 0; i < 2; i++){
			str = MSGMAN_AllocString(man, 2 + i);
			
			BMP_MENULIST_AddString(emwk->sys.bml, str, i);
			
			STRBUF_Delete(str);			
		}
		MSGMAN_Delete(man);
	}
	
	mh.menu		= emwk->sys.bml;
	mh.font		= FONT_SYSTEM;
	mh.win 		= win;
	mh.x_max	= 1;
	mh.y_max	= 2;
	mh.line_spc = 0;
	mh.c_disp_f = 0;
	mh.loop_f	= 1;

	BmpMenuWinWrite(win, WINDOW_TRANS_OFF, EGG_DEMO_MENU_CHAR_OFS, EDPAL_MENU);
	emwk->sys.bmw = BmpMenuAddEx(&mh, 8, 0, 0, HEAPID_EGG_DEMO, PAD_BUTTON_CANCEL);
}


//--------------------------------------------------------------
/**
 * @brief	はい・いいえ破棄
 *
 * @param	emwk	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void EggDisp_SelWindowDel(EGG_MAIN_WORK* emwk)
{
	BmpMenuWinClear(&emwk->sys.win[ 1 ], WINDOW_TRANS_OFF );
	GF_BGL_BmpWinOff(&emwk->sys.win[ 1 ]);
	GF_BGL_BmpWinDel(&emwk->sys.win[ 1 ]);
	BmpMenuExit(emwk->sys.bmw, NULL);
	BMP_MENULIST_Delete(emwk->sys.bml);
}

//--------------------------------------------------------------
/**
 * @brief	BMP win 破棄
 *
 * @param	win	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void EggDisp_BMP_WindowDel(GF_BGL_BMPWIN* win)
{
	GF_BGL_BmpWinOff(win);
	GF_BGL_BmpWinDel(win);
}


//--------------------------------------------------------------
/**
 * @brief	上画面背景のロード
 *
 * @param	bgl	
 * @param	pfd	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void EggDisp_BG_ResourceLoad(GF_BGL_INI* bgl, PALETTE_FADE_PTR pfd)
{
	int arc_index = ARC_EGGDEMO_GRA;
	int chr_index = EGG_DATA_EGG_BG01_NCGR_BIN;
	int scr_index = EGG_DATA_EGG_BG01_NSCR_BIN;
	int pal_index = EGG_DATA_EGG_BG01_NCLR;
	int frame	  = GF_BGL_FRAME3_M;
	int heap_id	  = HEAPID_EGG_DEMO;
	
	ArcUtil_BgCharSet(arc_index, chr_index,
					  bgl, frame, 0, 0, 1, heap_id);
					  
	ArcUtil_ScrnSet(arc_index, scr_index,
					bgl, frame, 0, 0, 1, heap_id);
					
	PaletteWorkSet_Arc(pfd, arc_index, pal_index,
					   heap_id, FADE_MAIN_BG, 0x20 * 2, EDPAL_BG);
}


//--------------------------------------------------------------
/**
 * @brief	サブ画面背景
 *
 * @param	bgl	
 * @param	pfd	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void EggDisp_SubBG_ResourceLoad(GF_BGL_INI* bgl, PALETTE_FADE_PTR pfd)
{
	int arc_index = ARC_POKETCH_IMG;
	int chr_index = NARC_poketch_before_lz_ncgr;
	int scr_index = NARC_poketch_before_lz_nscr;
	int pal_index = NARC_poketch_before_nclr;
	int frame	  = GF_BGL_FRAME0_S;
	int heap_id	  = HEAPID_EGG_DEMO;
	
	ArcUtil_BgCharSet(arc_index, chr_index,
					  bgl, frame, 0, 0, 1, heap_id);
					  
	ArcUtil_ScrnSet(arc_index, scr_index,
					bgl, frame, 0, 0, 1, heap_id);
					
	PaletteWorkSet_Arc(pfd, arc_index, pal_index,
					   heap_id, FADE_SUB_BG, 0x20 * 1, EDPAL_SUB_BG);
}







// =============================================================================
//
//
//	□ パーティクル
//
//
// =============================================================================
static u32 sAllocTex(u32 size, BOOL is4x4comp);
static u32 sAllocTexPalette(u32 size, BOOL is4pltt);
static PTC_PTR EggParticle_SystemSet(int heap_id);
static PTC_PTR EggParticle_PtcInit(int heap_id, int arc_id, int data_no);
//static void EggParticle_PtcExit(PTC_PTR ptc);
static void EggParticle_CallBack(EMIT_PTR emit);
//--------------------------------------------------------------
/**
 * @brief	領域確保
 *
 * @param	size	
 * @param	is4x4comp	
 *
 * @retval	static u32	
 *
 */
//--------------------------------------------------------------
static u32 sAllocTex(u32 size, BOOL is4x4comp)
{
	NNSGfdTexKey key;
	u32 address;
	
	key = NNS_GfdAllocTexVram(size, is4x4comp, 0);
	Particle_LnkTexKeySet(key);		//リンクドリストを使用しているのでキー情報をセット
	
	address = NNS_GfdGetTexKeyAddr(key);
	OS_Printf("テクスチャVramアドレス＝%#x\n", address);
	return address;
}


//--------------------------------------------------------------
/**
 * @brief	領域確保
 *
 * @param	size	
 * @param	is4pltt	
 *
 * @retval	static u32	
 *
 */
//--------------------------------------------------------------
static u32 sAllocTexPalette(u32 size, BOOL is4pltt)
{
	NNSGfdPlttKey key;
	u32 address;
	
	key = NNS_GfdAllocPlttVram(size, is4pltt, 0);
	Particle_PlttLnkTexKeySet(key);	//リンクドリストを使用しているのでキー情報をセット
	
	address = NNS_GfdGetPlttKeyAddr(key);
	OS_Printf("パレットVramアドレス＝%#x\n", address);
	return address;
}


//--------------------------------------------------------------
/**
 * @brief	システムセット
 *
 * @param	heap_id	
 *
 * @retval	static PTC_PTR	
 *
 */
//--------------------------------------------------------------
static PTC_PTR EggParticle_SystemSet(int heap_id)
{
	PTC_PTR ptc;
	void *heap;
	GF_CAMERA_PTR camera_ptr;
	
	heap = sys_AllocMemory(heap_id, PARTICLE_LIB_HEAP_SIZE);
	ptc = Particle_SystemCreate(sAllocTex, sAllocTexPalette, heap, PARTICLE_LIB_HEAP_SIZE, 
		TRUE, heap_id);
	camera_ptr = Particle_GetCameraPtr(ptc);
	if(camera_ptr != NULL){
		GFC_SetCameraClip(EGG_DEMO_NEAR, EGG_DEMO_FAR, camera_ptr);
	}
	return ptc;
}


//--------------------------------------------------------------
/**
 * @brief	PTC初期化
 *
 * @param	heap_id	
 * @param	arc_id	
 * @param	data_no	
 *
 * @retval	static PTC_PTR	
 *
 */
//--------------------------------------------------------------
static PTC_PTR EggParticle_PtcInit(int heap_id, int arc_id, int data_no)
{
	PTC_PTR ptc;
	void *resource;
	
	ptc = EggParticle_SystemSet(heap_id);
	resource = Particle_ArcResourceLoad(arc_id, data_no, heap_id);
	Particle_ResourceSet(ptc, resource, PTC_AUTOTEX_LNK | PTC_AUTOPLTT_LNK, TRUE);
	
	return ptc;
}


//--------------------------------------------------------------
/**
 * @brief	PTC終了
 *
 * @param	ptc	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void EggParticle_PtcExit(PTC_PTR ptc)
{
	void *heap;

	heap = Particle_HeapPtrGet(ptc);
	Particle_SystemExit(ptc);
	sys_FreeMemoryEz(heap);
}


//--------------------------------------------------------------
/**
 * @brief	コールバック
 *
 * @param	emit	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void EggParticle_CallBack(EMIT_PTR emit)
{
	VecFx32 pos = { 0, 0, 0 };
	
	SPL_SetEmitterPosition(emit, &pos);
}


//--------------------------------------------------------------
/**
 * @brief	パーティクルシステム初期化
 *
 * @param	param	
 *
 * @retval	EGG_PARTICLE_SYS*	
 *
 */
//--------------------------------------------------------------
EGG_PARTICLE_SYS* EggParticle_Init(EGG_PARTICLE_PARAM* param)
{
	int i;
	int ball_id;
	int spa_max;
	int set_id;
	EGG_PARTICLE_SYS* wk;
	
	wk = sys_AllocMemory(param->heap_id, sizeof(EGG_PARTICLE_SYS));
	
	GF_ASSERT(wk != NULL);
	
	wk->param = *param;
	
	wk->ptc = EggParticle_PtcInit(wk->param.heap_id, ARC_EGGDEMO_PARTICLE, wk->param.spa_id);
	
//	Particle_CreateEmitterCallback(wk->ptc, wk->param.spr_id, EggParticle_CallBack, wk);

	Particle_CameraTypeSet(wk->ptc, GF_CAMERA_ORTHO);
	
	return wk;	
}

//--------------------------------------------------------------
/**
 * @brief	SPA登録
 *
 * @param	eps	
 * @param	no	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void EggParticle_SprSet(EGG_PARTICLE_SYS* eps, int no)
{
	int i;
	int ball_id;
	int spa_max;
	int set_id;
	
	EGG_PARTICLE_SYS* wk = eps;
	
	Particle_CreateEmitterCallback(wk->ptc, no, EggParticle_CallBack, wk);

	Particle_CameraTypeSet(wk->ptc, GF_CAMERA_ORTHO);
}

//--------------------------------------------------------------
/**
 * @brief	メイン
 *
 * @param	eps	
 *
 * @retval	BOOL	
 *
 */
//--------------------------------------------------------------
BOOL EggParticle_Main(EGG_PARTICLE_SYS* eps)
{
	EGG_PARTICLE_SYS* wk = eps;
	
	if (Particle_GetEmitterNum(wk->ptc) == 0){
	//	EggParticle_PtcExit(wk->ptc);
		return FALSE;
	}
	
	return TRUE;
}


//--------------------------------------------------------------
/**
 * @brief	終了
 *
 * @param	eps	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void EggParticle_End(EGG_PARTICLE_SYS* eps)
{
	sys_FreeMemoryEz(eps);
}




// =============================================================================
//
//
//	□ ＯＡＭ関連
//
//
// =============================================================================
//--------------------------------------------------------------
/**
 * @brief	孵化デモリソース読み込み
 *
 * @param	emwk	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void EggOAM_ResourceLoad(EGG_MAIN_WORK* emwk)
{
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	PALETTE_FADE_PTR pfd;
	
	int egg_id[][4] = {
		{
			EGG_DATA_EGG_NORMAL_NCGR_BIN,
			EGG_DATA_EGG_NORMAL_NCLR,
			EGG_DATA_EGG_NORMAL_NCER_BIN,
			EGG_DATA_EGG_NORMAL_NANR_BIN,
		},
		{
			EGG_DATA_EGG_NORMAL_NCGR_BIN,
			EGG_DATA_EGG_NORMAL_NCLR,
			EGG_DATA_EGG_NORMAL_NCER_BIN,
			EGG_DATA_EGG_NORMAL_NANR_BIN,
		}
	};
	
	int arc  = ARC_EGGDEMO_GRA;
	int vram = NNS_G2D_VRAM_TYPE_2DMAIN;
	int egg_type = 0;
	
	csp = emwk->sys.csp;
	crp = emwk->sys.crp;
	pfd = emwk->sys.pfd;
	
	///< タマゴ
	CATS_LoadResourceCharArc(csp, crp, arc, egg_id[egg_type][0], TRUE, vram, EDID_EGG_NCGR);
	CATS_LoadResourcePlttWorkArc(pfd, FADE_MAIN_OBJ, csp, crp, arc, egg_id[egg_type][1], FALSE, 1, vram, EDID_EGG_NCLR);
	CATS_LoadResourceCellArc(csp, crp, arc, egg_id[egg_type][2], TRUE, EDID_EGG_NCER);
	CATS_LoadResourceCellAnmArc(csp, crp, arc, egg_id[egg_type][3], TRUE, EDID_EGG_NANR);	
	
	///< wnd
	CATS_LoadResourceCharArc(csp, crp, arc, EGG_DATA_MASK_NCGR_BIN, TRUE, vram, EDID_WND_NCGR);
	CATS_LoadResourcePlttWorkArc(pfd, FADE_MAIN_OBJ, csp, crp, arc, EGG_DATA_MASK_NCLR, FALSE, 1, vram, EDID_WND_NCLR);
	CATS_LoadResourceCellArc(csp, crp, arc, EGG_DATA_MASK_NCER_BIN, TRUE, EDID_WND_NCER);
	CATS_LoadResourceCellAnmArc(csp, crp, arc, EGG_DATA_MASK_NANR_BIN, TRUE, EDID_WND_NANR);	
}


//--------------------------------------------------------------
/**
 * @brief	OAM追加
 *
 * @param	emwk	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void EggOAM_Add(EGG_MAIN_WORK* emwk)
{
	TCATS_OBJECT_ADD_PARAM_S coap;
	
	coap.x		= 128;
	coap.y		= 120;
	coap.z		= 0;		
	coap.anm	= 0;
	coap.pri	= 0;
	coap.pal	= 0;
	coap.d_area = CATS_D_AREA_MAIN;
	coap.bg_pri = 2;
	coap.vram_trans = 0;
	
	coap.id[0]	= EDID_EGG_NCGR;
	coap.id[1]	= EDID_EGG_NCLR;
	coap.id[2]	= EDID_EGG_NCER;
	coap.id[3]	= EDID_EGG_NANR;
	coap.id[4]	= CLACT_U_HEADER_DATA_NONE;
	coap.id[5]	= CLACT_U_HEADER_DATA_NONE;

	emwk->egg = CATS_ObjectAdd_S(emwk->sys.csp, emwk->sys.crp, &coap);
	CATS_ObjectUpdateCap(emwk->egg);
	CATS_ObjectAffineSetCap(emwk->egg, CLACT_AFFINE_DOUBLE);
	
	coap.x		= 0;
	coap.y		= 0 - (2 * 8);
	coap.bg_pri = 0;
	coap.id[0]	= EDID_WND_NCGR;
	coap.id[1]	= EDID_WND_NCLR;
	coap.id[2]	= EDID_WND_NCER;
	coap.id[3]	= EDID_WND_NANR;
	emwk->wnd_t = CATS_ObjectAdd_S(emwk->sys.csp, emwk->sys.crp, &coap);
	CATS_ObjectUpdateCap(emwk->wnd_t);
	
	coap.y		= 192 - (6 * 8);
	emwk->wnd_b = CATS_ObjectAdd_S(emwk->sys.csp, emwk->sys.crp, &coap);
	CATS_ObjectUpdateCap(emwk->wnd_b);
}


//--------------------------------------------------------------
/**
 * @brief	デモ中の動き
 *
 * @param	emwk	
 *
 * @retval	static BOOL	
 *
 */
static const s16 EO_demo_move_x[][ 10 ] = {
	{ -1, +1, +1, -1, -1, +1, +1, -1, 0xFF, 0xFF },
	{ -2, +2, +2, -2, -2, +2, +2, -2, 0xFF, 0xFF },
	{ -3, +3, +3, -3, -3, +3, 0xFF, 0xFF },
	{ -3, +3, +3, -3, -3, +3, 0xFF, 0xFF },
};
static const s16 EO_demo_move_y[][ 10 ] = {
	{ 0, 0xFF },
	{ 0, 0, +1, +1,  0, -1, -1, 0,0,0xFF },
	{ 0, 0, +1, +1, +1, -1, -1,-1,0,0 },
	{ 0, 0, +1, +1, +1, -1, -1,-1,0,0 },
//	{ 0, 0, +1, +1, +1, +1, +1, 0, 0xFF },
};
static const f32 EO_demo_sc_x[][ 10 ] = {
	{ 1.0f, 0.0f },
	{ 1.0f, 1.0f, 1.1f, 1.1f, 1.1f, 1.1f, 1.1f, 1.0f, 1.0f, 0.0f },
	{ 1.0f, 1.1f, 1.1f, 1.2f, 1.2f, 1.2f, 1.1f, 1.1f, 1.0f, 0.0f },
	{ 1.0f, 1.1f, 1.1f, 1.2f, 1.2f, 1.2f, 1.1f, 1.1f, 1.0f, 0.0f },
//	{ 1.0f, 1.1f, 1.1f, 1.2f, 1.2f, 1.2f, 1.2f, 0.0f },
};
static const f32 EO_demo_sc_y[][ 10 ] = {
	{ 1.0f, 0.0f },
	{ 1.0f, 1.0f, 0.9f, 0.9f, 0.9f, 0.9f, 0.9f, 1.0f, 1.0f, 0.0f },
	{ 1.0f, 1.0f, 0.9f, 0.8f, 0.7f, 0.7f, 0.8f, 0.9f, 1.0f, 1.0f },
	{ 1.0f, 1.0f, 0.9f, 0.8f, 0.7f, 0.7f, 0.8f, 0.9f, 1.0f, 1.0f },
//	{ 1.0f, 1.0f, 0.9f, 0.8f, 0.7f, 0.7f, 0.6f, 0.0f },
};
//--------------------------------------------------------------
BOOL EggOam_DemoMove(EGG_MAIN_WORK* emwk, int count)
{
	EGG_DEMO_CAT_WORK* wk;
	
	wk = &emwk->demo;
	
	switch(wk->seq){
	case 0:
		if (wk->cnt >= 10){
			wk->seq++;
			wk->cnt = 0;
		}
		else {
			s16 x;
			s16 y;
			f32 cx;
			f32 cy;
			int check = 0;
			
			x  = EO_demo_move_x[ count ][ wk->cnt ];
		    y  = EO_demo_move_y[ count ][ wk->cnt ];
			cx = EO_demo_sc_x[ count ][ wk->cnt ];
			cy = EO_demo_sc_y[ count ][ wk->cnt ];
			
			if (x == 0xFF){
				x = 0;
				check++;
			}
			if (y == 0xFF){
				y = 0;
				check++;
			}
			CATS_ObjectPosMoveCap(emwk->egg, x, y);
			
			if (cx != 0.0f){
				CATS_ObjectScaleSetCap(emwk->egg, cx, cy);
			}
			else {
				check++;
			}
			if (check != 3){
				wk->cnt++;
				break;
			}
			else {
				wk->seq++;
			}
		}
		
	default:
		wk->seq = 0;
		wk->cnt = 0;
		return FALSE;
	}
	
	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief	デモ中の動き
 *
 * @param	emwk	
 * @param	count	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
int	EggOam_DemoMoveEx(EGG_MAIN_WORK* emwk, int count)
{
	if (EggOam_DemoMove(emwk, count) == FALSE){
		
		return EGG_DEMO_MOVE_END;
	}
	
	if (count == EGG_MOVE_SHAKE_5){
		if (emwk->demo.cnt == 6){
			
			return EGG_DEMO_MOVE_PARTICLE;
			
		}
	}
	else {
		if (emwk->demo.cnt == 6){
			
			return EGG_DEMO_MOVE_PARTICLE;
			
		}
	}
	
	return EGG_DEMO_MOVE_MAIN;
		
}

//--------------------------------------------------------------
/**
 * @brief	孵化デモＯＡＭ削除
 *
 * @param	emwk	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void EggOAM_Delete(EGG_MAIN_WORK* emwk)
{
	CATS_ActorPointerDelete_S(emwk->egg);	
	CATS_ActorPointerDelete_S(emwk->wnd_t);	
	CATS_ActorPointerDelete_S(emwk->wnd_b);	
}


//--------------------------------------------------------------
/**
 * @brief	システム初期化
 *
 * @param	sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void EggOAM_CatsInit(COMMON_SYS_WORK* sys)
{
	sys->csp = CATS_AllocMemory(HEAPID_EGG_DEMO);
	{
		const TCATS_OAM_INIT ED_OamInit = {
			0, 128, 0, 32,
			0, 128, 0, 32,
		};
		const TCATS_CHAR_MANAGER_MAKE ED_Ccmm = {
			48 + 48,			///< ID管理 main + sub
			1024 * 0x40,		///< 64k
			 512 * 0x20,		///< 32k
			GX_OBJVRAMMODE_CHAR_1D_64K,
			GX_OBJVRAMMODE_CHAR_1D_32K
		};
		CATS_SystemInit(sys->csp, &ED_OamInit, &ED_Ccmm, 16 + 16);
	}
	
	{
		BOOL active;
		const TCATS_RESOURCE_NUM_LIST ED_ResourceList = {
			48 + 48,	///< キャラ登録数 	main + sub
			16 + 16,	///< パレット登録数	main + sub
			64,			///< セル
			64,			///< セルアニメ
			16,			///< マルチセル
			16,			///< マルチセルアニメ
		};
		
		sys->crp = CATS_ResourceCreate(sys->csp);
		active   = CATS_ClactSetInit(sys->csp, sys->crp, 255);
		GF_ASSERT(active);
		
		active	  = CATS_ResourceManagerInit(sys->csp, sys->crp, &ED_ResourceList);
		GF_ASSERT(active);
	}
}


//--------------------------------------------------------------
/**
 * @brief	システム削除
 *
 * @param	sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void EggOAM_CatsDelete(COMMON_SYS_WORK* sys)
{
	CATS_ResourceDestructor_S(sys->csp, sys->crp);
	CATS_FreeMemory(sys->csp);
}



// =============================================================================
//
//
//	□ ソフトスプライト
//
//
// =============================================================================
//--------------------------------------------------------------
/**
 * @brief	ポケモン登録
 *
 * @param	emwk	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void EggPoke_Add(EGG_MAIN_WORK* emwk)
{
	SOFT_SPRITE_ARC ssa;
	SOFT_SPRITE_ANIME	ssanm[SS_ANM_SEQ_MAX];
	POKEMON_PARAM*	pp;
	int monsno;	
	int height;
	
	pp = emwk->epwk->param.pp;
	
	
	monsno  = PokeParaGet(pp, ID_PARA_monsno, NULL);
	height	= PokeParaHeightGet(pp, PARA_FRONT);
	
	///< タマゴをタマゴじゃなくするために
	{
		int para = 0;

		PokeParaPut(pp, ID_PARA_tamago_flag, &para);
	}
	
	PokeGraArcDataGetPP(&ssa, pp, PARA_FRONT);
	PokeAnmDataSet(&ssanm[0], monsno);

	emwk->ssp_poke = SoftSpriteAdd(emwk->sys.ssm_p, &ssa,
							 	   128, 96 + height, 0,
							 	   0, &ssanm[0], NULL);
}


//--------------------------------------------------------------
/**
 * @brief	アニメ設定
 *
 * @param	emwk	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void EggPoke_Anm(EGG_MAIN_WORK* emwk)
{
	int monsno;
	int chr;
	
	monsno = PokeParaGet(emwk->epwk->param.pp, ID_PARA_monsno, NULL);
	chr	   = PokeSeikakuGet(emwk->epwk->param.pp);
	
	SoftSpriteAnimeSet(emwk->ssp_poke, 1);
	PokePrgAnmDataSet(emwk->sys.pas,
					  emwk->ssp_poke, monsno, PARA_FRONT, chr, PARA_HFLIP_OFF, 0);
}


//--------------------------------------------------------------
/**
 * @brief	ポケモン削除
 *
 * @param	emwk	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void EggPoke_Del(EGG_MAIN_WORK* emwk)
{
	SoftSpriteDel(emwk->ssp_poke);
}


//--------------------------------------------------------------
/**
 * @brief	ポケモン非表示
 *
 * @param	emwk	
 * @param	flag	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void EggPoke_Vanish(EGG_MAIN_WORK* emwk, int flag)
{
	SoftSpriteParaSet(emwk->ssp_poke, SS_PARA_VANISH, flag);
}

