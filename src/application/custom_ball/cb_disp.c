//==============================================================================
/**
 * @file	cb_disp.c
 * @brief	主に描画関連の関数をおいとく
 * @author	goto
 * @date	2006.04.25(火)
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
#include "include/gflib/strbuf.h"
#include "include/gflib/msg_print.h"

#include "include/system/fontproc.h"
#include "include/system/msgdata.h"
#include "include/system/arc_util.h"
#include "include/system/window.h"

#include "include/poketool/pokeicon.h"

#include "field/field_common.h"
#include "field/field_event.h"
#include "field/fieldsys.h"
#include "field/ev_mapchange.h"


#include "system/bmp_menu.h"
#include "system/palanm.h"
#include "system/clact_tool.h"

#include "include/application/cb_sys.h"
#include "battle/battle_common.h"
#include "system/wipe.h"

#include "battle/graphic/batt_bg_def.h"

#include "data/cb_data_def.h"
#include "wazaeffect/wazatool.h"

#include "cb_snd_def.h"


extern void CB_BMP_SelectWinAdd(GF_BGL_INI* bgl, GF_BGL_BMPWIN* win, int frm, CB_MAIN_WORK* cbmw, int no);
extern void CB_BMP_SelectWinDel(CB_MAIN_WORK* cbmw);
extern void CB_SelectThisPosGet(int pos, s16* x, s16* y);
extern void CB_Tool_PokeIcon_Load(CB_MAIN_WORK* cbmw);
extern void CB_Tool_PokeIcon_Add(CB_MAIN_WORK* cbmw);
extern void CB_Tool_PokeIcon_CheckPosSetup(CB_MAIN_WORK* cbmw);
extern void CB_Tool_PokeIcon_Update(CB_MAIN_WORK* cbmw);
extern void CB_Tool_PokeIcon_Del(CB_MAIN_WORK* cbmw);
extern void CB_Tool_MarkObj_SetUp(CB_MAIN_WORK* cbmw);
extern void CB_Tool_CatsInit(CB_SYS* sys);
extern void CB_Tool_CatsDelete(CB_SYS* sys);
extern void SubObj_ResLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, PALETTE_FADE_PTR pfd, int chr_id, int pal_id, int cel_id, int cla_id, int vram, int pal_tg, int palnum);
extern void CB_Tool_SubSelect_ObjAdd(CB_MAIN_WORK* cbmw);
extern void SubSelect_ObjRefrect(CB_MAIN_WORK* cbmw);
extern void CB_Tool_CoreDataChange(CB_MAIN_WORK* cbmw, int from, int to);
extern void SubSelect_ObjUpdate(CB_MAIN_WORK* cbmw);
extern void SubSelect_ObjDelete(CB_MAIN_WORK* cbmw);
extern void CB_BMP_WindowResLoad(GF_BGL_INI* bgl, PALETTE_FADE_PTR pfd, int wintype);
extern void CB_BMP_WindowResLoad_Sub(GF_BGL_INI* bgl, PALETTE_FADE_PTR pfd, int wintype);
extern void CB_BMP_InfoMessageSet(GF_BGL_BMPWIN * win, int mes_id);
extern void CB_BMP_WindowAdd(GF_BGL_INI* bgl, GF_BGL_BMPWIN* win, int frm, int x, int y, int sx, int sy, int ofs);
extern void CB_BMP_WindowAddSimple(GF_BGL_INI* bgl, GF_BGL_BMPWIN* win, int frm, int x, int y, int sx, int sy, int ofs);
extern void CB_BMP_SealNumWinAdd(CB_MAIN_WORK* cbmw);
extern void CB_BMP_SealNumWinDel(CB_MAIN_WORK* cbmw);
extern void CB_BMP_SealNameSet(GF_BGL_BMPWIN * win, int id);
extern void CB_DispOn(void);
extern void CB_WipeFadeIn(void);
extern void CB_WipeFadeOut(void);
extern void CB_Select_TopResLoad(CB_MAIN_WORK* cbmw);
extern void CB_Select_BottomResLoad(CB_MAIN_WORK* cbmw);
extern void CB_Edit_BottomResLoad(CB_MAIN_WORK* cbmw);
extern void CB_Tool_SealBTN_ResLoad(CB_MAIN_WORK* cbmw);
extern void CB_Tool_BTN_ResLoad(CB_MAIN_WORK* cbmw);
extern void CB_Tool_BTN_Add(CB_MAIN_WORK* cbmw);
extern void CB_Tool_BTN_Update(CB_MAIN_WORK* cbmw);
extern void CB_Tool_BTN_Delete(CB_MAIN_WORK* cbmw);


static void HitRectSet(RECT_HIT_TBL* tbl, CATS_ACT_PTR cap, int w, int h)
{
	s16 x,y;
	
	CATS_ObjectPosGetCap(cap, &x, &y);
	
	tbl->rect.top		= y - h;
	tbl->rect.bottom	= y + h;
	tbl->rect.left		= x - w;
	tbl->rect.right		= x + w;
}


// =============================================================================
//
//
//	■フォントOAM
//
//
// =============================================================================
#define	PRINT_COL_BLACK		(GF_PRINTCOLOR_MAKE(15, 13, 2))		// フォントカラー：白
#define	PRINT_COL_NUM		(GF_PRINTCOLOR_MAKE( 1,  2, 0))		// フォントカラー：黒
#define PRINT_NUM_CLEAR		(0x00)
#define PRINT_NUM_CLEAR_2	(0xEE)

void FontOam_SysInit(CB_MAIN_WORK* cbmw)
{
	cbmw->sys.fontoam_sys = FONTOAM_SysInit(CB_ENUM_FONT_OAM_MAX, HEAPID_CUSTOM_BALL);
	
	FontProc_LoadFont(FONT_BUTTON, HEAPID_CUSTOM_BALL);
}

void FontOam_SysDelete(CB_MAIN_WORK* cbmw)
{
	FontProc_UnloadFont(FONT_BUTTON);
	
	FONTOAM_Delete(cbmw->sys.font_obj[ 0 ]);
	CharVramAreaFree(&cbmw->sys.font_vram[ 0 ]);
	
	FONTOAM_Delete(cbmw->sys.font_obj[ 1 ]);
	CharVramAreaFree(&cbmw->sys.font_vram[ 1 ]);
	
	FONTOAM_SysDelete(cbmw->sys.fontoam_sys);			
}

void FontOam_ResourceLoad(CB_MAIN_WORK* cbmw)
{
	CATS_LoadResourcePlttWorkArc(cbmw->sys.pfd, FADE_SUB_OBJ,
								 cbmw->sys.csp, cbmw->sys.crp,
								 ARC_FONT, NARC_font_talk_ncrl, FALSE,
								 1, NNS_G2D_VRAM_TYPE_2DSUB, CB_ENUM_FONT_OMA_BTN_PLTT_ID);	
}

void FontOam_Add(CB_MAIN_WORK* cbmw)
{
	FontOam_ResourceLoad(cbmw);
	FontOam_Create(cbmw, CB_ENUM_WIN_B_BTN_1,  78, 165, 0);
	FontOam_Create(cbmw, CB_ENUM_WIN_B_BTN_2, 172, 165, 0);
}

void FontOam_Enable(CB_MAIN_WORK* cbmw, BOOL flag)
{
	FONTOAM_SetDrawFlag(cbmw->sys.font_obj[ 0 ], flag);
	FONTOAM_SetDrawFlag(cbmw->sys.font_obj[ 1 ], flag);
}

void FontOam_Create(CB_MAIN_WORK* cbmw, int no, int x, int y, int pal_offset)
{
	FONTOAM_INIT	finit;
	STRBUF*			str;
	int				pal_id;
	int				vram_size;
	MSGDATA_MANAGER*		man;
	GF_BGL_BMPWIN 			bmpwin;
	
	
	
	man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, CB_DEF_MSG_ARC, HEAPID_CUSTOM_BALL);
	str	= MSGMAN_AllocString(man, msg_menu_00_06 + no);
		
	///< BMP
	{
		///< FONT_BUTTON は 2dotでかい
		GF_BGL_BmpWinInit(&bmpwin);
		GF_BGL_BmpWinObjAdd(cbmw->sys.bgl, &bmpwin, 10, 2, 0, 0);
		GF_STR_PrintColor(&bmpwin, FONT_BUTTON, str, 0, 0,
						  MSG_NO_PUT, PRINT_COL_BLACK, NULL);
	}

	pal_id = CB_ENUM_FONT_OMA_BTN_PLTT_ID;

	vram_size = FONTOAM_NeedCharSize(&bmpwin, NNS_G2D_VRAM_TYPE_2DSUB, HEAPID_CUSTOM_BALL);
	CharVramAreaAlloc(vram_size, CHARM_CONT_AREACONT, NNS_G2D_VRAM_TYPE_2DSUB, &cbmw->sys.font_vram[ no ]);

	finit.fontoam_sys	= cbmw->sys.fontoam_sys;
	finit.bmp			= &bmpwin;
	finit.clact_set		= CATS_GetClactSetPtr(cbmw->sys.crp);
	finit.pltt			= CATS_PlttProxy(cbmw->sys.crp, pal_id);
	finit.parent		= NULL;
	finit.char_ofs		= cbmw->sys.font_vram[ no ].alloc_ofs;
	finit.x				= x;
	finit.y				= y + 192;
	finit.bg_pri		= CB_ENUM_BG_PRI_B_OBJ2;
	finit.soft_pri		= 40;
	finit.draw_area		= NNS_G2D_VRAM_TYPE_2DSUB;
	finit.heap			= HEAPID_CUSTOM_BALL;
	
	cbmw->sys.font_obj[ no ] = FONTOAM_Init(&finit);
	FONTOAM_SetPaletteOffsetAddTransPlttNo(cbmw->sys.font_obj[ no ], pal_offset);
//	FONTOAM_SetMat(cbmw->sys.font_obj[ no ], x, y + );

	STRBUF_Delete(str);
	MSGMAN_Delete(man);
	GF_BGL_BmpWinDel(&bmpwin);
}

// =============================================================================
//
//
//	■ページデータ
//
//
// =============================================================================
///< ページ登録
void PageData_Create(CB_MAIN_WORK* cbmw, int page_no)
{
	int i;
	int no;
	int add;
	int add_start;
	BOOL have;
	int  num;
	
	no = 0;
	add = 0;
	add_start  = page_no;
	add_start *= CB_DEF_PAGE_ITEMS;
	
	for (i = 0; i < CB_DEF_PAGE_ITEMS; i++){						///< ページデータ初期化
		cbmw->page.item[ i ] = 0;
	}
	
	///< セーブデータにある、もしくはバックアップデータが所有している場合
	
	for (i = 0; i < CB_DEF_ITEM_DATA_NUM; i++){
//		if (CB_Tool_IsSeal(cbmw->cb_pw->save_data, i) == TRUE){		///< 1枚でも所持していたらページに登録
		
		have = CB_Tool_IsSealCore(&cbmw->backup_edit, i);
		num  = cbmw->backup_item[ i ];
		
		if (num != 0 || have == TRUE){
			add++;
			
			if (add <= add_start){ continue; }						///< ページ開始位置を越え無ければ登録できない
			
			cbmw->page.item[ no ] = (i + 1);						///< 1オリジンなので + 1	
			no++;
			
			if (no >= CB_DEF_PAGE_ITEMS){ break; }
		}
		
	}
}

///< OBJ登録
void PageData_ResourceLoad(CB_MAIN_WORK* cbmw)
{
	int i;
	int char_id;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	PALETTE_FADE_PTR pfd;

	csp = cbmw->sys.csp;
	crp = cbmw->sys.crp;
	pfd = cbmw->sys.pfd;
	
	for (i = 0; i < CB_DEF_PAGE_ITEMS; i++){	
		char_id = Seal_CharArcGet(cbmw->page.item[i]);
		
		CATS_LoadResourceCharArc(csp, crp,
								 ARC_CUSTOM_BALL_GRA, char_id, TRUE,
								 NNS_G2D_VRAM_TYPE_2DSUB,
								 CB_DEF_ARC_ID_BTN_GET(i));
	}
								 
	CATS_LoadResourcePlttWorkArc(pfd, FADE_SUB_OBJ,
								 csp, crp,
								 ARC_CUSTOM_BALL_GRA, CB_SEAL_NCLR, FALSE,
								 1, NNS_G2D_VRAM_TYPE_2DSUB, CB_ENUM_BTN_PLTT_ID + CB_LI_SEAL_NCLR);

	CATS_LoadResourceCellArc(csp, crp,
							 ARC_CUSTOM_BALL_GRA, CB_LI_SEAL_01_NCER_BIN, TRUE,
							 CB_ENUM_BTN_CELL_ID + CB_LI_SEAL_01_NCER_BIN);

	CATS_LoadResourceCellAnmArc(csp, crp,
								ARC_CUSTOM_BALL_GRA, CB_LI_SEAL_01_NANR_BIN, TRUE,
								CB_ENUM_BTN_CELLANM_ID + CB_LI_SEAL_01_NANR_BIN);
}

void PageData_Add(CB_MAIN_WORK* cbmw)
{
	int i;
	TUSUALLY_BTN* btn;
	TCATS_OBJECT_ADD_PARAM_S coap;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	PALETTE_FADE_PTR pfd;

	csp = cbmw->sys.csp;
	crp = cbmw->sys.crp;
	pfd = cbmw->sys.pfd;	
	btn = &cbmw->button_obj;
	
	coap.x		= 0;
	coap.y		= 0;
	coap.z		= 0;		
	coap.anm	= 0;
	coap.pri	= CB_ENUM_OAM_BTN_PRI;
	coap.d_area = CATS_D_AREA_SUB;
	coap.bg_pri = CB_ENUM_BG_PRI_B_OBJ;
	coap.vram_trans = 0;
	coap.id[4]	= CLACT_U_HEADER_DATA_NONE;
	coap.id[5]	= CLACT_U_HEADER_DATA_NONE;

	///< シール
	coap.pal	= 0;
	coap.id[1]	= CB_ENUM_BTN_PLTT_ID + CB_LI_SEAL_NCLR;
	coap.id[2]	= CB_ENUM_BTN_CELL_ID + CB_LI_SEAL_01_NCER_BIN;
	coap.id[3]	= CB_ENUM_BTN_CELLANM_ID + CB_LI_SEAL_01_NANR_BIN;
	for (i = 0; i < CB_DEF_PAGE_ITEMS; i++){
		coap.id[0]	= CB_DEF_ARC_ID_BTN_GET(i);
		btn->cap[i] = CATS_ObjectAdd_S(csp, crp, &coap);
	}
	{
	#ifdef SEAL_SBS
		///< 横並び
		const s16 pos[][2] = {
			{ 19, 23 },{ 75, 23 },
			{ 19, 47 },{ 75, 47 },
			{ 19, 71 },{ 75, 71 },
			{ 19, 95 },{ 75, 95 },
		};
	#else
		///< 縦並び
		const s16 pos[][2] = {
			{ 19, 23 },{ 19, 47 },	
			{ 19, 71 },{ 19, 95 },	
			{ 75, 23 },{ 75, 47 },
			{ 75, 71 },{ 75, 95 },
		};
	#endif
		for (i = 0; i < CB_DEF_PAGE_ITEMS; i++){
			CATS_ObjectPosSetCap(cbmw->button_obj.cap[i], pos[i][0], pos[i][1]-1);
			CATS_ObjectUpdateCap(cbmw->button_obj.cap[i]);
			CATS_ObjectAnimeFrameSetCap(cbmw->button_obj.cap[i], 0);
		}
	}
}

void PageData_Del(CB_MAIN_WORK* cbmw)
{
	int i;
	
	for (i = 0; i < CB_DEF_PAGE_ITEMS; i++){	
		CATS_FreeResourceChar(cbmw->sys.crp, CB_DEF_ARC_ID_BTN_GET(i));
		CATS_ActorPointerDelete_S(cbmw->button_obj.cap[i]);	
	}
}

// =============================================================================
//
//
//	■
//
//
// =============================================================================

typedef struct {
	
	WAZATOOL_CALCMOVE	cm[ CB_DEF_SEAL_MAX + 1 ];
	
	CATS_ACT_PTR	cap[ CB_DEF_SEAL_MAX ];
	GF_BGL_INI*		bgl;
	
	int seq;
	
	BOOL*			active;
	
} TCB_VIEW_SCROLL;

static void CB_View_Scroll_TCB(TCB_PTR tcb, void* work)
{
	TCB_VIEW_SCROLL* wk = (TCB_VIEW_SCROLL*)work;
	
	BOOL bCheck = FALSE;
	{
		int i;
		
		for (i = 0; i < CB_DEF_SEAL_MAX; i++){
			
			if (wk->cap[ i ] == NULL){ continue; }
	
			if (WazaTool_CalcAndReflectStraightFxCap(&wk->cm[i], wk->cap[i]) == TRUE){
				bCheck = TRUE;				
			}			
		}
		
		if (WazaTool_CalcStraightFx(&wk->cm[ CB_DEF_SEAL_MAX ]) == TRUE){
			bCheck = TRUE;				
			GF_BGL_ScrollSet(wk->bgl, CB_DEF_BALL_SUB_BG_FRM, GF_BGL_SCROLL_X_SET, wk->cm[ CB_DEF_SEAL_MAX ].x);
			GF_BGL_ScrollSet(wk->bgl, CB_DEF_BALL_SUB_BG_FRM, GF_BGL_SCROLL_Y_SET, wk->cm[ CB_DEF_SEAL_MAX ].y);
		}
	}
	
	if (bCheck == FALSE){
		*(wk->active) = FALSE;
		sys_FreeMemoryEz(wk);
		TCB_Delete(tcb);
	}
}

void CB_View_Scroll(CB_MAIN_WORK* cbmw, s8 r_vec, int wait)
{
	TCB_VIEW_SCROLL* wk;
	
	wk = sys_AllocMemory(HEAPID_CUSTOM_BALL, sizeof(TCB_VIEW_SCROLL));
	
	wk->bgl	  = cbmw->sys.bgl;
	
	{
		int i;
		s16 x, y;
		
		for (i = 0; i < CB_DEF_SEAL_MAX; i++){
			
			if (cbmw->seal[i].pop == FALSE){
				wk->cap[i] = NULL;
				continue;
			}
			
			wk->cap[i] = cbmw->seal[i].cap;
			
			CATS_ObjectPosGetCap(wk->cap[i], &x, &y);
			
			WazaTool_InitStraightSyncFx(&wk->cm[i],
										x, x + (CB_DEF_SEAL_OFS_X * r_vec),
										y, y + (CB_DEF_SEAL_OFS_Y * r_vec),
										wait);

			WazaTool_CalcAndReflectStraightFxCap(&wk->cm[i], wk->cap[i]);
			WazaTool_CalcAndReflectStraightFxCap(&wk->cm[i], wk->cap[i]);
		}
	}
	
	{
		int x = GF_BGL_ScrollGetX(wk->bgl, CB_DEF_BALL_SUB_BG_FRM);
		int y = GF_BGL_ScrollGetY(wk->bgl, CB_DEF_BALL_SUB_BG_FRM);
		
		WazaTool_InitStraightSyncFx(&wk->cm[ CB_DEF_SEAL_MAX ],
									x, x + ((CB_DEF_SEAL_OFS_X * r_vec) * -1),
									y, y + ((CB_DEF_SEAL_OFS_Y * r_vec) * -1),
									wait);
	}
	
	wk->active = &cbmw->sys.sub_tcb_active;
	*(wk->active) = TRUE;
	
	TCB_Add(CB_View_Scroll_TCB, wk, 0x1000);
}


// =============================================================================
//
//
//	■パーティクル
//
//
// =============================================================================
// particle

GF_G3DMAN * CB_3D_Init(void)
{
	GF_G3DMAN *g3Dman;
	
	g3Dman = GF_G3DMAN_Init(HEAPID_CUSTOM_BALL, GF_G3DMAN_LNK, GF_G3DTEX_256K, 
		GF_G3DMAN_LNK, GF_G3DPLT_32K, CBSimpleSetUp);
	return g3Dman;
}

void CBSimpleSetUp(void)
{
	// ３Ｄ使用面の設定(表示＆プライオリティー)
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
    G2_SetBG0Priority(1);

	// 各種描画モードの設定(シェード＆アンチエイリアス＆半透明)
    G3X_SetShading( GX_SHADING_TOON );
    G3X_AntiAlias( TRUE );
	G3X_AlphaTest( FALSE, 0 );	// アルファテスト　　オフ
	G3X_AlphaBlend( TRUE );		// アルファブレンド　オン
	G3X_EdgeMarking( FALSE );
	G3X_SetFog( FALSE, GX_FOGBLEND_COLOR_ALPHA, GX_FOGSLOPE_0x8000, 0 );

	// クリアカラーの設定
    G3X_SetClearColor(GX_RGB(0,0,0),0,0x7fff,63,FALSE);	//color,alpha,depth,polygonID,fog

	// ビューポートの設定
    G3_ViewPort(0, 0, 255, 191);
}

void CB_Particle_Init(void)
{
#if 0
	NNS_GfdInitFrmTexVramManager(2, TRUE);
	NNS_GfdInitFrmPlttVramManager(0x8000, TRUE);

	///< pokemon
	NNS_GfdAllocFrmTexVram(0x4000, 0, 0);
	NNS_GfdAllocFrmPlttVram(0x20 * 4, 0, NNS_GFD_ALLOC_FROM_LOW);
#else
	NNSGfdTexKey tex_key;
	NNSGfdPlttKey pltt_key;
	u32 tex_addrs, pltt_addrs;
	
	//ポケモンで使用する分を確保
	tex_key = NNS_GfdAllocTexVram(0x2000 * CLIENT_MAX, 0, 0);
	pltt_key = NNS_GfdAllocPlttVram(0x20 * CLIENT_MAX, 0, 0);
	
	GF_ASSERT(tex_key != NNS_GFD_ALLOC_ERROR_TEXKEY);
	GF_ASSERT(pltt_key != NNS_GFD_ALLOC_ERROR_PLTTKEY);
	tex_addrs = NNS_GfdGetTexKeyAddr(tex_key);
	pltt_addrs = NNS_GfdGetPlttKeyAddr(pltt_key);
	OS_TPrintf("ポケモン用に確保したテクスチャVramの先頭アドレス＝%d\n", tex_addrs);
	OS_TPrintf("ポケモン用に確保したパレットVramの先頭アドレス＝%d\n", pltt_addrs);
#endif
	Particle_SystemWorkInit();	
}

void CB_Particle_Main(void)
{
	int draw_num;
	const MtxFx43 *camera_ptr;

	GF_G3X_Reset();

	draw_num = Particle_DrawAll();	//パーティクル描画

	if(draw_num > 0){
		GF_G3X_Reset();
		NNS_G2dSetupSoftwareSpriteCamera();
	}

	Particle_CalcAll();	//パーティクル計算
	GF_G3_RequestSwapBuffers(GX_SORTMODE_MANUAL, GX_BUFFERMODE_Z);
}


// =============================================================================
//
//
//	■BG/BMP関連
//
//
// =============================================================================
void CB_BMP_SelectWinAdd(GF_BGL_INI* bgl, GF_BGL_BMPWIN* win, int frm, CB_MAIN_WORK* cbmw, int no)
{
	BMPMENU_HEADER	mh;
	int state;
	int x, y, sx, sy, ofs, list;
	int menu[ 4 ];
	
	state = CB_Tool_BallStatusCheck(cbmw, no);
	ofs = CB_DEF_WIN_T_MENU_SIZE_END;
	x   = CB_DEF_WIN_T_MENU_X;
	sx	= CB_DEF_WIN_T_MENU_SX;
	
	switch(state){
	case CB_ENUM_BALL_STATE_FREE:
		y	= CB_DEF_WIN_T_MENU_Y_1;
		sy	= CB_DEF_WIN_T_MENU_SY_1;
		menu[ 0 ] = 0;
		menu[ 1 ] = 4;
		menu[ 2 ] = 1;
		break;
	case CB_ENUM_BALL_STATE_CUSTOM:
		y	= CB_DEF_WIN_T_MENU_Y_2;
		sy	= CB_DEF_WIN_T_MENU_SY_2;
		menu[ 0 ] = 2;
		menu[ 1 ] = 0;
		menu[ 2 ] = 4;
		menu[ 3 ] = 1;
		break;
	case CB_ENUM_BALL_STATE_CUSTOM_SET:
		y	= CB_DEF_WIN_T_MENU_Y_2;
		sy	= CB_DEF_WIN_T_MENU_SY_2;
		menu[ 0 ] = 3;
		menu[ 1 ] = 0;
		menu[ 2 ] = 4;
		menu[ 3 ] = 1;
		break;
	case CB_ENUM_BALL_STATE_FREE_SET:
		y	= CB_DEF_WIN_T_MENU_Y_2;
		sy	= CB_DEF_WIN_T_MENU_SY_2;
		menu[ 0 ] = 2;
		menu[ 1 ] = 0;
		menu[ 2 ] = 4;
		menu[ 3 ] = 1;
		break;
	}
	list = (sy / 2);

	GF_BGL_BmpWinInit(win);
	GF_BGL_BmpWinAdd(bgl, win, frm,
					 x, y, sx, sy, CB_ENUM_PAL_FONT, ofs);
					 
	cbmw->sys.bml = BMP_MENULIST_Create(list, HEAPID_CUSTOM_BALL);
	
	{
		int i;
		STRBUF* str;
		MSGDATA_MANAGER* man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, CB_DEF_MSG_ARC, HEAPID_CUSTOM_BALL);
		for (i = 0; i < list; i++){
			str = MSGMAN_AllocString(man, CB_ParamTable[ menu[i] ].msg_id);
			
			BMP_MENULIST_AddString(cbmw->sys.bml, str, CB_ParamTable[ menu[i] ].param);
			
			STRBUF_Delete(str);
		}
		MSGMAN_Delete(man);
	}
	
	mh.menu		= cbmw->sys.bml;
	mh.font		= FONT_SYSTEM;
	mh.win 		= win;
	mh.x_max	= 1;
	mh.y_max	= list;
	mh.line_spc = 0;
	mh.c_disp_f = 0;
	mh.loop_f	= 1;

	BmpMenuWinWrite(win, WINDOW_TRANS_OFF, CB_DEF_WIN_T_MENU_CHAR_OFS, CB_ENUM_PAL_MENU);
	cbmw->sys.bmw = BmpMenuAddEx(&mh, 8, 0, 0, HEAPID_CUSTOM_BALL, PAD_BUTTON_CANCEL);
//	GF_BGL_BmpWinDataFill(win, FBMP_COL_WHITE);
//	GF_BGL_BmpWinOn(win);
}


void CB_BMP_SelectWinDel(CB_MAIN_WORK* cbmw)
{
	BmpMenuExit(cbmw->sys.bmw, NULL);
	BMP_MENULIST_Delete(cbmw->sys.bml);
}






// =============================================================================
//
//
//	■OBJなどのアイコン
//
//
// =============================================================================
void CB_SelectThisPosGet(int pos, s16* x, s16* y)
{
	int ofs;
	ofs = (pos % 4);
	*x = 32 + 8 + (ofs * 56);
	ofs = (pos >> 2);
	*y = 27 + (ofs * 53);
}

void CB_Tool_PokeIcon_Load(CB_MAIN_WORK* cbmw)
{
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	PALETTE_FADE_PTR pfd;

	csp = cbmw->sys.csp;
	crp = cbmw->sys.crp;
	pfd = cbmw->sys.pfd;

	//パレット
	CATS_LoadResourcePlttWorkArc(pfd, FADE_MAIN_OBJ, csp, crp,
		ARC_POKEICON, PokeIconPalArcIndexGet(), 0, POKEICON_PAL_MAX, NNS_G2D_VRAM_TYPE_2DMAIN, CB_ENUM_ICON_PLTT_ID);
	//セル
	{
		int arc = PokeIcon64kCellArcIndexGet();
		CATS_LoadResourceCellArc(csp, crp, ARC_POKEICON, arc, 0, CB_ENUM_ICON_CELL_ID);
	}
	//セルアニメ
	{
		int arc = PokeIcon64kCellAnmArcIndexGet();
		CATS_LoadResourceCellAnmArc(csp, crp, ARC_POKEICON, arc, 0, CB_ENUM_ICON_CELLANM_ID);
	}
}

void CB_Tool_PokeIcon_Add(CB_MAIN_WORK* cbmw)
{
	int i;
	int egg;
	int monsno;
	int palno;
	int form;
	POKEMON_PARAM* pp;
	TCATS_OBJECT_ADD_PARAM_S coap;
	
	for (i = 0; i < cbmw->cb_pw->poke_cnt; i++){
		pp = cbmw->cb_pw->poke_para[i];
		
		CATS_LoadResourceCharArcModeAdjustAreaCont(cbmw->sys.csp, cbmw->sys.crp,
								 ARC_POKEICON, PokeIconCgxArcIndexGetByPP(pp), 0,
								 NNS_G2D_VRAM_TYPE_2DMAIN, CB_DEF_ARC_ID_POKE_ICON_GET(i));
	
		coap.x		= 0;
		coap.y		= 0;
		coap.z		= 0;		
		coap.anm	= 0;
		coap.pri	= CB_ENUM_OAM_PRI_ICON;
		coap.pal	= 0;
		coap.d_area = CATS_D_AREA_MAIN;
		coap.bg_pri = CB_ENUM_BG_PRI_T_OBJ;
		coap.vram_trans = 0;

		coap.id[0] = CB_DEF_ARC_ID_POKE_ICON_GET(i);
		coap.id[1] = CB_ENUM_ICON_PLTT_ID;
		coap.id[2] = CB_ENUM_ICON_CELL_ID;
		coap.id[3] = CB_ENUM_ICON_CELLANM_ID;
		coap.id[4] = CLACT_U_HEADER_DATA_NONE;
		coap.id[5] = CLACT_U_HEADER_DATA_NONE;
		
		cbmw->icon[ i ] = CATS_ObjectAdd_S(cbmw->sys.csp, cbmw->sys.crp, &coap);

		monsno = PokeParaGet(pp, ID_PARA_monsno, NULL);
		egg	   = PokeParaGet(pp, ID_PARA_tamago_flag, NULL);
		form   = PokeParaGet(pp, ID_PARA_form_no, NULL);
		palno  = PokeIconPalNumGet(monsno, form, egg);
		CLACT_PaletteOffsetChgAddTransPlttNo(cbmw->icon[ i ]->act, palno);
		CATS_ObjectAnimeSeqSetCap(cbmw->icon[ i ], POKEICON_ANM_HPMAX);
	}
}


void CB_Tool_PokeIcon_CheckPosSetup(CB_MAIN_WORK* cbmw)
{
	int i;
	int has_no;
	s16 x, y;
	for (i = 0; i < cbmw->cb_pw->poke_cnt; i++){
		CATS_ObjectEnableCap(cbmw->icon[ i ], CATS_ENABLE_FALSE);
	}
	for (i = 0; i < CB_DEF_CORE_MAX; i++){
		has_no = cbmw->cb_edit_data[ i ].poke_idx;
		if (has_no != CB_DEF_POKE_NOT_INDEX){
			CB_SelectThisPosGet(i, &x, &y);
			CATS_ObjectPosSetCap(cbmw->icon[ has_no ], x + CB_DEF_ICON_OFS_X, y + CB_DEF_ICON_OFS_Y);
			CATS_ObjectEnableCap(cbmw->icon[ has_no ], CATS_ENABLE_TRUE);
		}
	}
}


void CB_Tool_PokeIcon_Update(CB_MAIN_WORK* cbmw)
{
	int i;
	for (i = 0; i < cbmw->cb_pw->poke_cnt; i++){
		CATS_ObjectUpdateCap(cbmw->icon[ i ]);	
	}
}

void CB_Tool_PokeIcon_Del(CB_MAIN_WORK* cbmw)
{
	int i;
	int monsno;
	
	for (i = 0; i < cbmw->cb_pw->poke_cnt; i++){
		CATS_ActorPointerDelete_S(cbmw->icon[ i ]);
	}
}

void CB_Tool_MarkObj_SetUp(CB_MAIN_WORK* cbmw)
{
	int i;
	int no;
	int clear = 0;
	
	CB_CORE* core;
	
	///< ボールが編集済みかどうか
	for (i = 0; i < CB_DEF_CORE_MAX; i++){
		core = cbmw->cb_edit_data[i].core;
		cbmw->mo[ i ].edit_flag = CB_Tool_IsEdit(core);
		cbmw->mo[ i ].poke_idx  = cbmw->cb_edit_data[ i ].poke_idx;
		
		///< 編集してないけど、ポケモンについてる場合はずす	
		if (cbmw->mo[ i ].edit_flag == CB_DEF_EDIT_OFF
		&&	cbmw->mo[ i ].poke_idx  != CB_DEF_POKE_NOT_INDEX){
			OS_Printf("消す　ID = %d\n", i);
			OS_Printf("poke idx = %3d\n", cbmw->mo[ i ].poke_idx);
			
			CB_Tool_CoreDataRemove(cbmw, i);
		}
	}
}

void CB_Tool_CatsInit(CB_SYS* sys)
{
	sys->csp = CATS_AllocMemory(HEAPID_CUSTOM_BALL);
	{
		const TCATS_OAM_INIT CB_OamInit = {
			0, 128, 0, 32,
			0, 128, 0, 32,
		};
		const TCATS_CHAR_MANAGER_MAKE CB_Ccmm = {
			48 + 48,			///< ID管理 main + sub
			1024 * 0x40,		///< 64k
			 512 * 0x20,		///< 32k
			GX_OBJVRAMMODE_CHAR_1D_64K,
			GX_OBJVRAMMODE_CHAR_1D_32K
		};
		CATS_SystemInit(sys->csp, &CB_OamInit, &CB_Ccmm, 16 + 16);
	}
	
	{
		BOOL active;
		const TCATS_RESOURCE_NUM_LIST CB_ResourceList = {
			48 + 48,	///< キャラ登録数 	main + sub
			16 + 16,	///< パレット登録数	main + sub
			64,			///< セル
			64,			///< セルアニメ
			16,			///< マルチセル
			16,			///< マルチセルアニメ
		};
		
		sys->crp = CATS_ResourceCreate(sys->csp);
		active   = CATS_ClactSetInit(sys->csp, sys->crp, CB_DEF_OBJ_MAX);
		GF_ASSERT(active);
		
		active	  = CATS_ResourceManagerInit(sys->csp, sys->crp, &CB_ResourceList);
		GF_ASSERT(active);
	}
}

void CB_Tool_CatsDelete(CB_SYS* sys)
{
	CATS_ResourceDestructor_S(sys->csp, sys->crp);
	CATS_FreeMemory(sys->csp);
}

void Piko_ResLoad(CB_MAIN_WORK* cbmw)
{
	CATS_LoadResourceCharArc(cbmw->sys.csp, cbmw->sys.crp,
							 ARC_CUSTOM_BALL_GRA, CB_ANIMEC_01_NCGR_BIN, TRUE,
							 CATS_D_AREA_SUB,
							 CB_ENUM_PIKO_CHAR_ID);

	CATS_LoadResourceCellArc(cbmw->sys.csp, cbmw->sys.crp,
							 ARC_CUSTOM_BALL_GRA, CB_ANIMEC_01_NCER_BIN, TRUE,
							 CB_ENUM_PIKO_CELL_ID);

	CATS_LoadResourceCellAnmArc(cbmw->sys.csp, cbmw->sys.crp,
								ARC_CUSTOM_BALL_GRA, CB_ANIMEC_01_NANR_BIN, TRUE,
								CB_ENUM_PIKO_CELLANM_ID);	
}

#define PIKO_USE

void Piko_Add(CB_MAIN_WORK* cbmw)
{
#ifdef PIKO_USE
	int i;
	
	TCATS_OBJECT_ADD_PARAM_S coap;
	/*
	int pos[][ 3 ] = {
		{ 132,  12, CLACT_FLIP_H },
		{ 132, 132, CLACT_FLIP_HV },
		{ 244,  12, CLACT_FLIP_NONE },
		{ 244, 132, CLACT_FLIP_V },
	};
	*/
	int pos[][ 3 ] = {
		{ 136,  16, CLACT_FLIP_H },
		{ 136, 128, CLACT_FLIP_HV },
		{ 240,  16, CLACT_FLIP_NONE },
		{ 240, 128, CLACT_FLIP_V },
	};
	for (i = 0; i < 4; i++){
		coap.x		= pos[i][0];
		coap.y		= pos[i][1];
		coap.z		= 0;		
		coap.anm	= 0;
		coap.pri	= CB_ENUM_OAM_PRI_BALL;
		coap.pal	= CB_DEF_CUR_BTN_PAL_NO;
		coap.d_area = CATS_D_AREA_SUB;
		coap.bg_pri = CB_ENUM_BG_PRI_B_OBJ;
		coap.vram_trans = 0;
		
		coap.id[0]	= CB_ENUM_PIKO_CHAR_ID;
		coap.id[1]	= CB_ENUM_BTN_PLTT_ID + CB_BUTTON_NCLR;
		coap.id[2]	= CB_ENUM_PIKO_CELL_ID;
		coap.id[3]	= CB_ENUM_PIKO_CELLANM_ID;
		coap.id[4]	= CLACT_U_HEADER_DATA_NONE;
		coap.id[5]	= CLACT_U_HEADER_DATA_NONE;
		
		cbmw->piko[i] = CATS_ObjectAdd_S(cbmw->sys.csp, cbmw->sys.crp, &coap);
		
		CATS_ObjectFlipSetCap(cbmw->piko[i], pos[i][2]);
	}
#endif
}

void Piko_Update(CB_MAIN_WORK* cbmw)
{
#ifdef PIKO_USE
	int i;
	
	if (cbmw->sys.main_tp_active == FALSE){ return; }
	
	for (i = 0; i < 4; i++){
		CATS_ObjectUpdateCap(cbmw->piko[i]);
	}
#endif
}

void Piko_Enable(CB_MAIN_WORK* cbmw, int flag)
{
#ifdef PIKO_USE
	int i;
	for (i = 0; i < 4; i++){
		CATS_ObjectEnableCap(cbmw->piko[i], flag);
	}
#endif
}

void Piko_Delete(CB_MAIN_WORK* cbmw)
{
#ifdef PIKO_USE
	int i;
	for (i = 0; i < 4; i++){
		CATS_ActorPointerDelete_S(cbmw->piko[i]);
	}
#endif
}

void SubObj_ResLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, PALETTE_FADE_PTR pfd, int chr_id, int pal_id, int cel_id, int cla_id, int vram, int pal_tg, int palnum)
{
	CATS_LoadResourceCharArc(csp, crp,
							 ARC_CUSTOM_BALL_GRA, chr_id, TRUE,
							 vram,
							 CB_DEF_ARC_ID_GET( chr_id ));

	CATS_LoadResourcePlttWorkArc(pfd, pal_tg,
								 csp, crp,
								 ARC_CUSTOM_BALL_GRA, pal_id, FALSE,
								 palnum, vram, CB_DEF_ARC_ID_GET( pal_id ));
	CATS_LoadResourceCellArc(csp, crp,
							 ARC_CUSTOM_BALL_GRA, cel_id, TRUE,
							 CB_DEF_ARC_ID_GET( cel_id ));

	CATS_LoadResourceCellAnmArc(csp, crp,
								ARC_CUSTOM_BALL_GRA, cla_id, TRUE,
								CB_DEF_ARC_ID_GET( cla_id ));	
}


void CB_Tool_SubSelect_ObjAdd(CB_MAIN_WORK* cbmw)
{
	SubObj_ResLoad(cbmw->sys.csp, cbmw->sys.crp, cbmw->sys.pfd,
				   CB_BALL_OBJ_NCGR_BIN, CB_BALL_OBJ_NCLR,
				   CB_BALL_OBJ_NCER_BIN, CB_BALL_OBJ_NANR_BIN,
				   NNS_G2D_VRAM_TYPE_2DMAIN, FADE_MAIN_OBJ, 1);
				   
	SubObj_ResLoad(cbmw->sys.csp, cbmw->sys.crp, cbmw->sys.pfd,
				   CB_CUR_OBJ_NCGR_BIN, CB_CUR_OBJ_NCLR,
				   CB_CUR_OBJ_NCER_BIN, CB_CUR_OBJ_NANR_BIN,
				   NNS_G2D_VRAM_TYPE_2DMAIN, FADE_MAIN_OBJ, 1);
	{
		int i;
		
		TCATS_OBJECT_ADD_PARAM_S coap;
		
		for (i = 0; i < CB_DEF_CORE_MAX; i++){
			coap.x		= 0;
			coap.y		= 0;
			coap.z		= 0;		
			coap.anm	= cbmw->mo[ i ].edit_flag;
			coap.pri	= CB_ENUM_OAM_PRI_BALL - i;
			coap.pal	= 0;
			coap.d_area = CATS_D_AREA_MAIN;
			coap.bg_pri = CB_ENUM_BG_PRI_T_OBJ;
			coap.vram_trans = 0;
			
			coap.id[0]	= CB_DEF_ARC_ID_GET( CB_BALL_OBJ_NCGR_BIN );
			coap.id[1]	= CB_DEF_ARC_ID_GET( CB_BALL_OBJ_NCLR );
			coap.id[2]	= CB_DEF_ARC_ID_GET( CB_BALL_OBJ_NCER_BIN );
			coap.id[3]	= CB_DEF_ARC_ID_GET( CB_BALL_OBJ_NANR_BIN );
			coap.id[4]	= CLACT_U_HEADER_DATA_NONE;
			coap.id[5]	= CLACT_U_HEADER_DATA_NONE;
			
			cbmw->mo[ i ].cap = CATS_ObjectAdd_S(cbmw->sys.csp, cbmw->sys.crp, &coap);
			{
				s16 x, y;
				CB_SelectThisPosGet(i, &x, &y);
				CATS_ObjectPosSetCap(cbmw->mo[ i ].cap, x, y);
			//	CATS_ObjectObjModeSetCap(cbmw->mo[ i ].cap, GX_OAM_MODE_XLU);
			}
		}
		coap.x		= 0;
		coap.y		= 0;
		coap.z		= 0;		
		coap.anm	= 0;
		coap.pri	= CB_ENUM_OAM_PRI_CUR_1;
		coap.pal	= 0;
		coap.d_area = CATS_D_AREA_MAIN;
		coap.bg_pri = CB_ENUM_BG_PRI_T_OBJ;
		coap.vram_trans = 0;
		
		coap.id[0]	= CB_DEF_ARC_ID_GET( CB_CUR_OBJ_NCGR_BIN );
		coap.id[1]	= CB_DEF_ARC_ID_GET( CB_CUR_OBJ_NCLR );
		coap.id[2]	= CB_DEF_ARC_ID_GET( CB_CUR_OBJ_NCER_BIN );
		coap.id[3]	= CB_DEF_ARC_ID_GET( CB_CUR_OBJ_NANR_BIN );
		coap.id[4]	= CLACT_U_HEADER_DATA_NONE;
		coap.id[5]	= CLACT_U_HEADER_DATA_NONE;

		cbmw->cap_cur[0] = CATS_ObjectAdd_S(cbmw->sys.csp, cbmw->sys.crp, &coap);
		cbmw->cap_cur[1] = CATS_ObjectAdd_S(cbmw->sys.csp, cbmw->sys.crp, &coap);
		{
			s16 x, y;
			CB_SelectThisPosGet(cbmw->select[0], &x, &y);
			CATS_ObjectPosSetCap(cbmw->cap_cur[0], x, y);
			CATS_ObjectPosSetCap(cbmw->cap_cur[1], x, y);
			CATS_ObjectPriSetCap(cbmw->cap_cur[1], CB_ENUM_OAM_PRI_CUR_2);
			CATS_ObjectAnimeSeqSetCap(cbmw->cap_cur[0], 0);
			CATS_ObjectAnimeSeqSetCap(cbmw->cap_cur[1], 0);
		}
	}
}

void SubSelect_ObjRefrect(CB_MAIN_WORK* cbmw)
{
	int i;
	
	CB_Tool_MarkObj_SetUp(cbmw);
	CB_Tool_PokeIcon_CheckPosSetup(cbmw);
	
	for (i = 0; i < CB_DEF_CORE_MAX; i++){
		CATS_ObjectAnimeSeqSetCap(cbmw->mo[i].cap, cbmw->mo[i].edit_flag);
	}
}

void CB_Tool_CoreDataChange(CB_MAIN_WORK* cbmw, int from, int to)
{
	int poke_idx;
	int poke_from;
	int poke_to;
	int set_to;
	int set_from;
	CB_CORE temp;
	
	///< ポケパラ操作
	poke_from = cbmw->cb_edit_data[ from ].poke_idx;
	poke_to	  = cbmw->cb_edit_data[ to ].poke_idx;
	
	OS_Printf("poke_from %d\n", poke_from);
	OS_Printf("poke_to   %d\n", poke_to);
	OS_Printf("from %d\n", from);
	OS_Printf("to   %d\n", to);
	
	if (poke_from != CB_DEF_POKE_NOT_INDEX){
		set_to = to + 1;
		PokeParaPut(cbmw->cb_pw->poke_para[ poke_from ], ID_PARA_cb_id, (u8*)&set_to);
		OS_Printf("poke_from 書き換え\n");
	}
	if (poke_to != CB_DEF_POKE_NOT_INDEX){
		set_from = from + 1;
		PokeParaPut(cbmw->cb_pw->poke_para[ poke_to ], ID_PARA_cb_id, (u8*)&set_from);
		OS_Printf("poke_to 書き換え\n");
	}
	poke_idx = cbmw->cb_edit_data[ from ].poke_idx;
	cbmw->cb_edit_data[ from ].poke_idx = cbmw->cb_edit_data[ to ].poke_idx;
	cbmw->cb_edit_data[ to ].poke_idx = poke_idx;
	
	///< コアデータ入れ替え
	CB_Tool_CoreData_Copy(cbmw->cb_edit_data[from].core, &temp);
	CB_Tool_CoreData_Copy(cbmw->cb_edit_data[to].core, cbmw->cb_edit_data[from].core);
	CB_Tool_CoreData_Copy(&temp, cbmw->cb_edit_data[to].core);
	
	SubSelect_ObjRefrect(cbmw);
}

void SubSelect_ObjUpdate(CB_MAIN_WORK* cbmw)
{
	int i;
	
	for (i = 0; i < CB_DEF_CORE_MAX; i++){
		CATS_ObjectUpdateCap(cbmw->mo[ i ].cap);
	}
	CATS_ObjectUpdateCap(cbmw->cap_cur[0]);
	CATS_ObjectUpdateCap(cbmw->cap_cur[1]);
}

void SubSelect_ObjDelete(CB_MAIN_WORK* cbmw)
{
	int i;
	
	for (i = 0; i < CB_DEF_CORE_MAX; i++){
		CATS_ActorPointerDelete_S(cbmw->mo[ i ].cap);
	}
	CATS_ActorPointerDelete_S(cbmw->cap_cur[0]);
	CATS_ActorPointerDelete_S(cbmw->cap_cur[1]);
}

///< メイン画面　ウィンドウリソース読み込み
void CB_BMP_WindowResLoad(GF_BGL_INI* bgl, PALETTE_FADE_PTR pfd, int wintype)
{
//	TalkWinGraphicSet(bgl, CB_DEF_STRING_BG_FRM, CB_DEF_WIN_T_TALK_CHAR_OFS,
//					  CB_ENUM_PAL_BACK, TalkWinCgxArcGet(wintype), HEAPID_CUSTOM_BALL);
	TalkWinGraphicSet(bgl, CB_DEF_STRING_BG_FRM, CB_DEF_WIN_T_TALK_CHAR_OFS,
					  CB_ENUM_PAL_BACK, wintype, HEAPID_CUSTOM_BALL);
	PaletteWorkSet_Arc(pfd, ARC_WINFRAME, TalkWinPalArcGet(wintype),
					   HEAPID_CUSTOM_BALL, FADE_MAIN_BG, 0x20, CB_ENUM_PAL_FRAME * 16);

	MenuWinGraphicSet(bgl, CB_DEF_STRING_BG_FRM, CB_DEF_WIN_T_MENU_CHAR_OFS, CB_ENUM_PAL_MENU, 0, HEAPID_CUSTOM_BALL);
	PaletteWorkSet_Arc(pfd, ARC_WINFRAME, MenuWinPalArcGet(),
					   HEAPID_CUSTOM_BALL, FADE_MAIN_BG, 0x20, CB_ENUM_PAL_MENU * 16);

	///< フォント
	PaletteWorkSet_Arc(pfd, ARC_FONT, NARC_font_talk_ncrl, 
					   HEAPID_CUSTOM_BALL, FADE_MAIN_BG, 0x20, CB_ENUM_PAL_FONT * 16);
}

///< サブ画面　ウィンドウリソース読み込み
void CB_BMP_WindowResLoad_Sub(GF_BGL_INI* bgl, PALETTE_FADE_PTR pfd, int wintype)
{
//	TalkWinGraphicSet(bgl, CB_DEF_STRING_SUB_BG_FRM, CB_DEF_WIN_T_TALK_CHAR_OFS,
//					  CB_ENUM_PAL_BACK, TalkWinCgxArcGet(wintype), HEAPID_CUSTOM_BALL);
	TalkWinGraphicSet(bgl, CB_DEF_STRING_SUB_BG_FRM, CB_DEF_WIN_T_TALK_CHAR_OFS,
					  CB_ENUM_PAL_BACK, wintype, HEAPID_CUSTOM_BALL);
	PaletteWorkSet_Arc(pfd, ARC_WINFRAME, TalkWinPalArcGet(wintype),
					   HEAPID_CUSTOM_BALL, FADE_SUB_BG, 0x20, CB_ENUM_PAL_FRAME * 16);

	MenuWinGraphicSet(bgl, CB_DEF_STRING_SUB_BG_FRM, CB_DEF_WIN_T_MENU_CHAR_OFS, CB_ENUM_PAL_MENU, 0, HEAPID_CUSTOM_BALL);
	PaletteWorkSet_Arc(pfd, ARC_WINFRAME, MenuWinPalArcGet(),
					   HEAPID_CUSTOM_BALL, FADE_SUB_BG, 0x20, CB_ENUM_PAL_MENU * 16);

	///< フォント
	PaletteWorkSet_Arc(pfd, ARC_FONT, NARC_font_talk_ncrl, 
					   HEAPID_CUSTOM_BALL, FADE_SUB_BG, 0x20, CB_ENUM_PAL_FONT * 16);

	PaletteWorkSet_Arc(pfd, ARC_FONT, NARC_font_talk_ncrl, 
					   HEAPID_CUSTOM_BALL, FADE_SUB_BG, 0x20, CB_ENUM_PAL_LIST_BG * 16);

	PaletteWorkSet_Arc(pfd, ARC_CUSTOM_BALL_GRA, CB_FONT_NCLR, 
					   HEAPID_CUSTOM_BALL, FADE_SUB_BG, 0x20, CB_ENUM_PAL_NUM * 16);
}

void CB_BMP_InfoMessageSet(GF_BGL_BMPWIN * win, int mes_id)
{
	MSGDATA_MANAGER* man;
	STRBUF* str;
	
	if (mes_id == CB_MSG_ID_CLEAR){ 
		GF_BGL_BmpWinDataFill(win, FBMP_COL_WHITE);
		GF_BGL_BmpWinOn(win);
		return;
	}

	man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, CB_DEF_MSG_ARC, HEAPID_CUSTOM_BALL);
	str	= MSGMAN_AllocString(man, mes_id);
	
	GF_BGL_BmpWinDataFill(win, FBMP_COL_WHITE);
	GF_STR_PrintSimple(win, FONT_SYSTEM, str, 0, 0, 0, NULL);
	GF_BGL_BmpWinOn(win);

	STRBUF_Delete(str);
	MSGMAN_Delete(man);	
}

void CB_BMP_WindowAdd(GF_BGL_INI* bgl, GF_BGL_BMPWIN* win, int frm, int x, int y, int sx, int sy, int ofs)
{
	GF_BGL_BmpWinInit(win);
	GF_BGL_BmpWinAdd(bgl, win, frm,
					 x, y, sx, sy, CB_ENUM_PAL_FONT, ofs);
	BmpTalkWinWrite(win, WINDOW_TRANS_OFF, CB_DEF_WIN_T_TALK_CHAR_OFS, CB_ENUM_PAL_FRAME);
	GF_BGL_BmpWinDataFill(win, FBMP_COL_WHITE);
	GF_BGL_BmpWinOn(win);
}

void CB_BMP_WindowAddSimple(GF_BGL_INI* bgl, GF_BGL_BMPWIN* win, int frm, int x, int y, int sx, int sy, int ofs)
{
	GF_BGL_BmpWinInit(win);
	GF_BGL_BmpWinAdd(bgl, win, frm,
					 x, y, sx, sy, CB_ENUM_PAL_FONT, ofs);
	GF_BGL_BmpWinDataFill(win, FBMP_COL_WHITE);
	GF_BGL_BmpWinOn(win);
}

static void CB_BMP_WindowAddSimpleEx(GF_BGL_INI* bgl, GF_BGL_BMPWIN* win, int frm, int x, int y, int sx, int sy, int ofs, int pal)
{
	GF_BGL_BmpWinInit(win);
	GF_BGL_BmpWinAdd(bgl, win, frm,
					 x, y, sx, sy, pal, ofs);
	GF_BGL_BmpWinDataFill(win, FBMP_COL_WHITE);
	GF_BGL_BmpWinOn(win);
}

void CB_BMP_SealNumWinAdd(CB_MAIN_WORK* cbmw)
{
	CB_BMP_WindowAddSimpleEx(cbmw->sys.bgl, &cbmw->sys.win[ CB_ENUM_WIN_B_LIST_1 ], CB_DEF_LIST_SUB_BG_FRM,
					 CB_DEF_WIN_B_LIST_1_X,  CB_DEF_WIN_B_LIST_1_Y,
					 CB_DEF_WIN_B_LIST_1_SX, CB_DEF_WIN_B_LIST_1_SY, CB_DEF_WIN_B_MAIN_SIZE_END, CB_ENUM_PAL_NUM);

	CB_BMP_WindowAddSimpleEx(cbmw->sys.bgl, &cbmw->sys.win[ CB_ENUM_WIN_B_LIST_2 ], CB_DEF_LIST_SUB_BG_FRM,
					 CB_DEF_WIN_B_LIST_2_X,  CB_DEF_WIN_B_LIST_2_Y,
					 CB_DEF_WIN_B_LIST_2_SX, CB_DEF_WIN_B_LIST_2_SY, CB_DEF_WIN_B_LIST_1_SIZE_END, CB_ENUM_PAL_NUM);

	CB_BMP_WindowAddSimpleEx(cbmw->sys.bgl, &cbmw->sys.win[ CB_ENUM_WIN_B_LIST_3 ], CB_DEF_LIST_SUB_BG_FRM,
					 CB_DEF_WIN_B_LIST_3_X,  CB_DEF_WIN_B_LIST_3_Y,
					 CB_DEF_WIN_B_LIST_3_SX, CB_DEF_WIN_B_LIST_3_SY, CB_DEF_WIN_B_LIST_2_SIZE_END, CB_ENUM_PAL_NUM);

	CB_BMP_WindowAddSimpleEx(cbmw->sys.bgl, &cbmw->sys.win[ CB_ENUM_WIN_B_LIST_4 ], CB_DEF_LIST_SUB_BG_FRM,
					 CB_DEF_WIN_B_LIST_4_X,  CB_DEF_WIN_B_LIST_4_Y,
					 CB_DEF_WIN_B_LIST_4_SX, CB_DEF_WIN_B_LIST_4_SY, CB_DEF_WIN_B_LIST_3_SIZE_END, CB_ENUM_PAL_NUM);

	CB_BMP_WindowAddSimpleEx(cbmw->sys.bgl, &cbmw->sys.win[ CB_ENUM_WIN_B_LIST_5 ], CB_DEF_LIST_SUB_BG_FRM,
					 CB_DEF_WIN_B_LIST_5_X,  CB_DEF_WIN_B_LIST_5_Y,
					 CB_DEF_WIN_B_LIST_5_SX, CB_DEF_WIN_B_LIST_5_SY, CB_DEF_WIN_B_LIST_4_SIZE_END, CB_ENUM_PAL_NUM);
					 
	CB_BMP_WindowAddSimpleEx(cbmw->sys.bgl, &cbmw->sys.win[ CB_ENUM_WIN_B_LIST_6 ], CB_DEF_LIST_SUB_BG_FRM,
					 CB_DEF_WIN_B_LIST_6_X,  CB_DEF_WIN_B_LIST_6_Y,
					 CB_DEF_WIN_B_LIST_6_SX, CB_DEF_WIN_B_LIST_6_SY, CB_DEF_WIN_B_LIST_5_SIZE_END, CB_ENUM_PAL_NUM);
					 
	CB_BMP_WindowAddSimpleEx(cbmw->sys.bgl, &cbmw->sys.win[ CB_ENUM_WIN_B_LIST_7 ], CB_DEF_LIST_SUB_BG_FRM,
					 CB_DEF_WIN_B_LIST_7_X,  CB_DEF_WIN_B_LIST_7_Y,
					 CB_DEF_WIN_B_LIST_7_SX, CB_DEF_WIN_B_LIST_7_SY, CB_DEF_WIN_B_LIST_6_SIZE_END, CB_ENUM_PAL_NUM);
					 
	CB_BMP_WindowAddSimpleEx(cbmw->sys.bgl, &cbmw->sys.win[ CB_ENUM_WIN_B_LIST_8 ], CB_DEF_LIST_SUB_BG_FRM,
					 CB_DEF_WIN_B_LIST_8_X,  CB_DEF_WIN_B_LIST_8_Y,
					 CB_DEF_WIN_B_LIST_8_SX, CB_DEF_WIN_B_LIST_8_SY, CB_DEF_WIN_B_LIST_7_SIZE_END, CB_ENUM_PAL_NUM);
}

void CB_BMP_SealNumWinPrint(CB_MAIN_WORK* cbmw)
{
	int i;
	int id;
	int seal_no;
	int num;

	STRBUF* str_dest;
	GF_BGL_BMPWIN * win;
	
	for (i = CB_ENUM_WIN_B_LIST_1; i < CB_ENUM_WIN_MAX; i++){
		
		win = &cbmw->sys.win[i];
		
		id = i - CB_ENUM_WIN_B_LIST_1;
		
		seal_no = cbmw->page.item[ id ];		
				
		if (seal_no == 0){
			GF_BGL_BmpWinDataFill(win, PRINT_NUM_CLEAR_2);
			GF_BGL_BmpWinOn(win);
			continue;
		}
		
		GF_BGL_BmpWinDataFill(win, PRINT_NUM_CLEAR);
		
		str_dest = STRBUF_Create(100, HEAPID_CUSTOM_BALL);
		
		num = CB_SaveData_ItemNumGet_CBO(cbmw->cb_item_data, seal_no - 1);
			
		STRBUF_SetNumber(str_dest, num, 3, NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT);
				
//		GF_STR_PrintSimple(win, FONT_SYSTEM, str_dest, 0, 0, 0, NULL);
		GF_STR_PrintColor(win, FONT_SYSTEM, str_dest, SEAL_NUM_PRINT_X, SEAL_NUM_PRINT_Y,
						  MSG_NO_PUT, PRINT_COL_NUM, NULL);
		GF_BGL_BmpWinOn(win);
		
		STRBUF_Delete(str_dest);
	}
}

void CB_BMP_SealNumWinPrint_No(CB_MAIN_WORK* cbmw, int no)
{
	int i;
	int id;
	int seal_no;
	int num;

	STRBUF* str_dest;
	GF_BGL_BMPWIN * win;

	win = &cbmw->sys.win[no + CB_ENUM_WIN_B_LIST_1];
	
	id = no;
	
	seal_no = cbmw->page.item[ id ];
	
	if (seal_no == 0){
		GF_BGL_BmpWinDataFill(win, PRINT_NUM_CLEAR_2);
		GF_BGL_BmpWinOn(win);
		return;
	}
	GF_BGL_BmpWinDataFill(win, PRINT_NUM_CLEAR);
	
	str_dest = STRBUF_Create(100, HEAPID_CUSTOM_BALL);
	
	num = CB_SaveData_ItemNumGet_CBO(cbmw->cb_item_data, seal_no - 1);
		
	STRBUF_SetNumber(str_dest, num, 3, NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT);
			
//	GF_STR_PrintSimple(win, FONT_SYSTEM, str_dest, 0, 0, 0, NULL);
	GF_STR_PrintColor(win, FONT_SYSTEM, str_dest, SEAL_NUM_PRINT_X, SEAL_NUM_PRINT_Y,
					  MSG_NO_PUT, PRINT_COL_NUM, NULL);

	GF_BGL_BmpWinOn(win);
	
	STRBUF_Delete(str_dest);
}

void CB_BMP_SealNumWinDel(CB_MAIN_WORK* cbmw)
{
	int i;
	
	for (i = CB_ENUM_WIN_B_LIST_1; i < CB_ENUM_WIN_MAX; i++){
		GF_BGL_BmpWinOff(&cbmw->sys.win[ i ]);
		GF_BGL_BmpWinDel(&cbmw->sys.win[ i ]);
	}
}

void CB_BMP_SealNameSet(GF_BGL_BMPWIN * win, int id)
{
	MSGDATA_MANAGER* man;
	STRBUF* str;
	
	if (id == CB_MSG_ID_CLEAR){ 
		GF_BGL_BmpWinDataFill(win, FBMP_COL_WHITE);
		GF_BGL_BmpWinOn(win);
		return;
	}

	man = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, CB_SEAL_MSG_ARC, HEAPID_CUSTOM_BALL);
	str	= MSGMAN_AllocString(man, id);
	
	GF_BGL_BmpWinDataFill(win, FBMP_COL_WHITE);
	GF_STR_PrintSimple(win, FONT_SYSTEM, str, 0, 0, 0, NULL);
	GF_BGL_BmpWinOn(win);

	STRBUF_Delete(str);
	MSGMAN_Delete(man);	
}

void CB_DispOn(void)
{
	GF_Disp_DispOn();
	GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);
	GF_Disp_GXS_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);
}

void CB_WipeFadeIn(void)
{
	WIPE_SYS_Start(WIPE_PATTERN_WMS,
				   WIPE_TYPE_FADEIN, WIPE_TYPE_FADEIN,
				   WIPE_FADE_BLACK, WIPE_DEF_DIV, WIPE_DEF_SYNC, HEAPID_CUSTOM_BALL);
}

void CB_WipeFadeOut(void)
{
	WIPE_SYS_Start(WIPE_PATTERN_WMS,
			   	   WIPE_TYPE_FADEOUT, WIPE_TYPE_FADEOUT, 
			   	   WIPE_FADE_BLACK, WIPE_DEF_DIV, WIPE_DEF_SYNC, HEAPID_CUSTOM_BALL);
}

void CB_Select_TopResLoad(CB_MAIN_WORK* cbmw)
{
	int arc_index = ARC_CUSTOM_BALL_GRA;
	int chr_index = CB_BG_T_01_NCGR_BIN;
	int scr_index = CB_BG_T_01_NSCR_BIN;
	int pal_index = CB_BG_T_01_NCLR;
	int frame	  = CB_DEF_SINGLE_BG_FRM;
	
	ArcUtil_BgCharSet(arc_index, chr_index,
					  cbmw->sys.bgl, frame, 0, 0, 1, HEAPID_CUSTOM_BALL);
	ArcUtil_ScrnSet(arc_index, scr_index,
					cbmw->sys.bgl, frame, 0, 0, 1, HEAPID_CUSTOM_BALL);
	PaletteWorkSet_Arc(cbmw->sys.pfd,
					   arc_index, pal_index,
					   HEAPID_CUSTOM_BALL, FADE_MAIN_BG, 0x20 * 2, CB_ENUM_PAL_SEL_BG);

	arc_index = ARC_CUSTOM_BALL_GRA;
	chr_index = CB_BG_T_02_NCGR_BIN;
	scr_index = CB_BG_T_02_NSCR_BIN;
	frame	  = CB_DEF_FIELD_BG_FRM;
	
	ArcUtil_BgCharSet(arc_index, chr_index,
					  cbmw->sys.bgl, frame, 0, 0, 1, HEAPID_CUSTOM_BALL);
	ArcUtil_ScrnSet(arc_index, scr_index,
					cbmw->sys.bgl, frame, 0, 0, 1, HEAPID_CUSTOM_BALL);
}


void CB_Select_BottomResLoad(CB_MAIN_WORK* cbmw)
{
	int arc_index = ARC_CUSTOM_BALL_GRA;
	int chr_index = CB_BG_B_01_NCGR_BIN;
	int scr_index = CB_BG_B_02_NSCR_BIN;
	int pal_index = CB_BG_B_01_NCLR;
	int frame	  = CB_DEF_BALL_SUB_BG_FRM;
	
	ArcUtil_BgCharSet(arc_index, chr_index,
					  cbmw->sys.bgl, frame, 0, 0, 1, HEAPID_CUSTOM_BALL);
	ArcUtil_ScrnSet(arc_index, scr_index,
					cbmw->sys.bgl, frame, 0, 0, 1, HEAPID_CUSTOM_BALL);
	PaletteWorkSet_Arc(cbmw->sys.pfd,
					   arc_index, pal_index,
					   HEAPID_CUSTOM_BALL, FADE_SUB_BG, 0x20 * 2, CB_ENUM_PAL_SEL_BG);
}

void CB_Edit_BottomResLoad(CB_MAIN_WORK* cbmw)
{
	int arc_index = ARC_CUSTOM_BALL_GRA;
	int chr_index = CB_BG_B_01_NCGR_BIN;
	int scr_index = CB_BG_B_01_NSCR_BIN;
	int pal_index = CB_BG_B_01_NCLR;
	int frame	  = CB_DEF_EDIT_SUB_BG_FRM;
	
	ArcUtil_BgCharSet(arc_index, chr_index,
					  cbmw->sys.bgl, frame, 0, 0, 1, HEAPID_CUSTOM_BALL);
	ArcUtil_ScrnSet(arc_index, scr_index,
					cbmw->sys.bgl, frame, 0, 0, 1, HEAPID_CUSTOM_BALL);
	PaletteWorkSet_Arc(cbmw->sys.pfd,
					   arc_index, pal_index,
					   HEAPID_CUSTOM_BALL, FADE_SUB_BG, 0x20 * 2, CB_ENUM_PAL_SEL_BG);
}

///< 
void CB_Tool_SealBTN_ResLoad(CB_MAIN_WORK* cbmw)
{
	int i;
	int char_id;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	PALETTE_FADE_PTR pfd;

	csp = cbmw->sys.csp;
	crp = cbmw->sys.crp;
	pfd = cbmw->sys.pfd;
	
	for (i = 0; i < CB_DEF_PAGE_ITEMS; i++){	
		char_id = Seal_Li_CharArcGet(1 + i);
		CATS_LoadResourceCharArc(csp, crp,
								 ARC_CUSTOM_BALL_GRA, char_id, TRUE,
								 NNS_G2D_VRAM_TYPE_2DSUB,
								 CB_DEF_ARC_ID_BTN_GET(i));

	}								 
	CATS_LoadResourcePlttWorkArc(pfd, FADE_SUB_OBJ,
								 csp, crp,
								 ARC_CUSTOM_BALL_GRA, CB_SEAL_NCLR, FALSE,
								 1, NNS_G2D_VRAM_TYPE_2DSUB, CB_ENUM_BTN_PLTT_ID + CB_LI_SEAL_NCLR);

	CATS_LoadResourceCellArc(csp, crp,
							 ARC_CUSTOM_BALL_GRA, CB_LI_SEAL_01_NCER_BIN, TRUE,
							 CB_ENUM_BTN_CELL_ID + CB_LI_SEAL_01_NCER_BIN);

	CATS_LoadResourceCellAnmArc(csp, crp,
								ARC_CUSTOM_BALL_GRA, CB_LI_SEAL_01_NANR_BIN, TRUE,
								CB_ENUM_BTN_CELLANM_ID + CB_LI_SEAL_01_NANR_BIN);	
}

void CB_Tool_BTN_ResLoad(CB_MAIN_WORK* cbmw)
{
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	PALETTE_FADE_PTR pfd;

	csp = cbmw->sys.csp;
	crp = cbmw->sys.crp;
	pfd = cbmw->sys.pfd;
	
	///< シールボタン
//	CB_Tool_SealBTN_ResLoad(cbmw);

	///< ボタン用パレット
	CATS_LoadResourcePlttWorkArc(pfd, FADE_SUB_OBJ, csp, crp,
								 ARC_CUSTOM_BALL_GRA, CB_BUTTON_NCLR, FALSE,
								 CB_DEF_BTN_PAL_NUM, NNS_G2D_VRAM_TYPE_2DSUB,
								 CB_ENUM_BTN_PLTT_ID + CB_BUTTON_NCLR);	
	///< ↑押しボタン
	CATS_LoadResourceCharArc(csp, crp,
							 ARC_CUSTOM_BALL_GRA, CB_BUTTON_SC01_NCGR_BIN, TRUE,
							 NNS_G2D_VRAM_TYPE_2DSUB,
							 CB_ENUM_BTN_CHAR_ID + CB_BUTTON_SC01_NCGR_BIN);

	CATS_LoadResourceCellArc(csp, crp,
							 ARC_CUSTOM_BALL_GRA, CB_BUTTON_SC01_NCER_BIN, TRUE,
							 CB_ENUM_BTN_CELL_ID + CB_BUTTON_SC01_NCER_BIN);

	CATS_LoadResourceCellAnmArc(csp, crp,
								ARC_CUSTOM_BALL_GRA, CB_BUTTON_SC01_NANR_BIN, TRUE,
								CB_ENUM_BTN_CELLANM_ID + CB_BUTTON_SC01_NANR_BIN);
	
	///< ↓押しボタン
	CATS_LoadResourceCharArc(csp, crp,
							 ARC_CUSTOM_BALL_GRA, CB_BUTTON_SC02_NCGR_BIN, TRUE,
							 NNS_G2D_VRAM_TYPE_2DSUB,
							 CB_ENUM_BTN_CHAR_ID + CB_BUTTON_SC02_NCGR_BIN);

	CATS_LoadResourceCellArc(csp, crp,
							 ARC_CUSTOM_BALL_GRA, CB_BUTTON_SC02_NCER_BIN, TRUE,
							 CB_ENUM_BTN_CELL_ID + CB_BUTTON_SC02_NCER_BIN);

	CATS_LoadResourceCellAnmArc(csp, crp,
								ARC_CUSTOM_BALL_GRA, CB_BUTTON_SC02_NANR_BIN, TRUE,
								CB_ENUM_BTN_CELLANM_ID + CB_BUTTON_SC02_NANR_BIN);

	///< 下のボタン
	CATS_LoadResourceCharArc(csp, crp,
							 ARC_CUSTOM_BALL_GRA, CB_BUTTON_01_NCGR_BIN, TRUE,
							 NNS_G2D_VRAM_TYPE_2DSUB,
							 CB_ENUM_BTN_CHAR_ID + CB_BUTTON_01_NCGR_BIN);

	CATS_LoadResourceCellArc(csp, crp,
							 ARC_CUSTOM_BALL_GRA, CB_BUTTON_01_NCER_BIN, TRUE,
							 CB_ENUM_BTN_CELL_ID + CB_BUTTON_01_NCER_BIN);

	CATS_LoadResourceCellAnmArc(csp, crp,
								ARC_CUSTOM_BALL_GRA, CB_BUTTON_01_NANR_BIN, TRUE,
								CB_ENUM_BTN_CELLANM_ID + CB_BUTTON_01_NANR_BIN);

	CATS_LoadResourceCharArc(csp, crp,
							 ARC_CUSTOM_BALL_GRA, CB_BUTTON_KAKU01_NCGR_BIN, TRUE,
							 NNS_G2D_VRAM_TYPE_2DSUB,
							 CB_ENUM_BTN_EYE_CHAR_ID + CB_BUTTON_KAKU01_NCGR_BIN);

	CATS_LoadResourceCellArc(csp, crp,
							 ARC_CUSTOM_BALL_GRA, CB_BUTTON_KAKU01_NCER_BIN, TRUE,
							 CB_ENUM_BTN_CELL_ID + CB_BUTTON_KAKU01_NCER_BIN);

	CATS_LoadResourceCellAnmArc(csp, crp,
								ARC_CUSTOM_BALL_GRA, CB_BUTTON_KAKU01_NANR_BIN, TRUE,
								CB_ENUM_BTN_CELLANM_ID + CB_BUTTON_KAKU01_NANR_BIN);
}

void CB_Tool_BTN_Add(CB_MAIN_WORK* cbmw)
{
	int i;
	TUSUALLY_BTN* btn;
	TCATS_OBJECT_ADD_PARAM_S coap;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	PALETTE_FADE_PTR pfd;

	csp = cbmw->sys.csp;
	crp = cbmw->sys.crp;
	pfd = cbmw->sys.pfd;	
	btn = &cbmw->button_obj;
	
	coap.x		= 0;
	coap.y		= 0;
	coap.z		= 0;		
	coap.anm	= 0;
	coap.pri	= CB_ENUM_OAM_BTN_PRI;
	coap.d_area = CATS_D_AREA_SUB;
	coap.bg_pri = CB_ENUM_BG_PRI_B_OBJ;
	coap.vram_trans = 0;
	coap.id[4]	= CLACT_U_HEADER_DATA_NONE;
	coap.id[5]	= CLACT_U_HEADER_DATA_NONE;
#if 0
	///< シール
	coap.pal	= 0;
	coap.id[1]	= CB_ENUM_BTN_PLTT_ID + CB_LI_SEAL_NCLR;
	coap.id[2]	= CB_ENUM_BTN_CELL_ID + CB_LI_SEAL_01_NCER_BIN;
	coap.id[3]	= CB_ENUM_BTN_CELLANM_ID + CB_LI_SEAL_01_NANR_BIN;
	for (i = 0; i < CB_DEF_PAGE_ITEMS; i++){
		coap.id[0]	= CB_DEF_ARC_ID_BTN_GET(i);
		btn->cap[i] = CATS_ObjectAdd_S(csp, crp, &coap);
	}
#endif
	i = CB_DEF_PAGE_ITEMS;
	///< 上下ボタン
	coap.pal	= CB_DEF_UD_BTN_PAL_NO;
	coap.id[0]	= CB_ENUM_BTN_CHAR_ID + CB_BUTTON_SC01_NCGR_BIN;
	coap.id[1]	= CB_ENUM_BTN_PLTT_ID + CB_BUTTON_NCLR;
	coap.id[2]	= CB_ENUM_BTN_CELL_ID + CB_BUTTON_SC01_NCER_BIN;
	coap.id[3]	= CB_ENUM_BTN_CELLANM_ID + CB_BUTTON_SC01_NANR_BIN;
	btn->cap[i++] = CATS_ObjectAdd_S(csp, crp, &coap);
	
	coap.id[0]	= CB_ENUM_BTN_CHAR_ID + CB_BUTTON_SC02_NCGR_BIN;
	coap.id[1]	= CB_ENUM_BTN_PLTT_ID + CB_BUTTON_NCLR;
	coap.id[2]	= CB_ENUM_BTN_CELL_ID + CB_BUTTON_SC02_NCER_BIN;
	coap.id[3]	= CB_ENUM_BTN_CELLANM_ID + CB_BUTTON_SC02_NANR_BIN;
	btn->cap[i++] = CATS_ObjectAdd_S(csp, crp, &coap);

	///< 確認
	coap.bg_pri = CB_ENUM_BG_PRI_B_OBJ2;
	coap.pal	= CB_DEF_EYE_BTN_PAL_NO;
	coap.id[0]	= CB_ENUM_BTN_EYE_CHAR_ID + CB_BUTTON_KAKU01_NCGR_BIN;
	coap.id[1]	= CB_ENUM_BTN_PLTT_ID + CB_BUTTON_NCLR;
	coap.id[2]	= CB_ENUM_BTN_CELL_ID + CB_BUTTON_KAKU01_NCER_BIN;
	coap.id[3]	= CB_ENUM_BTN_CELLANM_ID + CB_BUTTON_KAKU01_NANR_BIN;	
	btn->cap[i++] = CATS_ObjectAdd_S(csp, crp, &coap);
	
	coap.bg_pri = CB_ENUM_BG_PRI_B_OBJ2;
	coap.pal	= CB_DEF_BTN_PAL_NO;
	coap.id[0]	= CB_ENUM_BTN_CHAR_ID + CB_BUTTON_01_NCGR_BIN;
	coap.id[1]	= CB_ENUM_BTN_PLTT_ID + CB_BUTTON_NCLR;
	coap.id[2]	= CB_ENUM_BTN_CELL_ID + CB_BUTTON_01_NCER_BIN;
	coap.id[3]	= CB_ENUM_BTN_CELLANM_ID + CB_BUTTON_01_NANR_BIN;	
	btn->cap[i++] = CATS_ObjectAdd_S(csp, crp, &coap);
	btn->cap[i++] = CATS_ObjectAdd_S(csp, crp, &coap);
	
	{
		const s16 pos[][2] = {
			{ 20, 23 },{ 20, 47 },	
			{ 20, 71 },{ 20, 95 },	
			{ 76, 23 },{ 76, 47 },
			{ 76, 71 },{ 76, 95 },
			
			{ 27, 124 },{ 67, 124 },
			
			{ 32, 168+3 },{ 112-8, 168+3 },{ 196-4, 168+3 },
		};
		const s16 hit[][2] = {
			{ 0xFF, 0xFF },{ 0xFF, 0xFF },
			{ 0xFF, 0xFF },{ 0xFF, 0xFF },
			{ 0xFF, 0xFF },{ 0xFF, 0xFF },
			{ 0xFF, 0xFF },{ 0xFF, 0xFF },
			
			{ 13, 10 },{ 13, 10 },
			{ 16, 12 },{ 28, 12 },{ 28, 12 },
		};
		for (i = CB_ENUM_BHIT_UP; i < CB_ENUM_BTN_NUM; i++){
			CATS_ObjectPosSetCap(cbmw->button_obj.cap[i], pos[i][0], pos[i][1]);
			CATS_ObjectUpdateCap(cbmw->button_obj.cap[i]);
			CATS_ObjectAnimeFrameSetCap(cbmw->button_obj.cap[i], 0);
			
			HitRectSet(&cbmw->sys.hit_tbl[i], cbmw->button_obj.cap[i], hit[i][0], hit[i][1]);
		}
	}
}

void CB_Tool_BTN_Enable(CB_MAIN_WORK* cbmw, int flag)
{
	int i;
	
	for (i = 0; i < CB_ENUM_BTN_NUM; i++){
		CATS_ObjectEnableCap(cbmw->button_obj.cap[i], flag);
	}
}

void CB_Tool_BTN_Update(CB_MAIN_WORK* cbmw)
{
	int i;
	
	for (i = 0; i < CB_ENUM_BTN_NUM; i++){
//		CATS_ObjectUpdateCap(cbmw->button_obj.cap[i]);
	}
}

void CB_Tool_BTN_Delete(CB_MAIN_WORK* cbmw)
{
	int i;
	
	for (i = CB_ENUM_BHIT_UP; i < CB_ENUM_BTN_NUM; i++){
		CATS_ActorPointerDelete_S(cbmw->button_obj.cap[i]);
	}
}





