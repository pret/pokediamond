//==============================================================================================
/**
 * @file	tr_test.c
 * @brief	トレーナーグラフィックチェック
 * @author	sogabe
 * @date	2006.03.29
 */
//==============================================================================================

#ifdef PM_DEBUG

#include "common.h"
#include "system/fontproc.h"
#include "system/pm_str.h"
#include "system/msgdata.h"						//MSGDATA_MANAGER
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/softsprite.h"
#include "tr_test.h"

#include "msgdata/msg.naix"						//NARC_msg_??_dat
#include "battle/graphic/batt_bg_def.h"
#include "battle/battle_common.h"
#include "battle/trtype_def.h"
#include "poketool/poke_tool.h"
#include "system/snd_tool.h"
#include "system/wordset.h"

#include "system/main.h"
#include "demo/title.h"
#include "msgdata/msg_poke_test.h"

//==============================================================================================
//
//	msgデータ
//
//==============================================================================================

//==============================================================================================
//
//	構造体
//
//==============================================================================================

typedef struct{
	BOOL end_flag;
	GF_BGL_INI			*bgl;
	GF_BGL_BMPWIN		*win;
	SOFT_SPRITE_MANAGER	*ssm;
	SOFT_SPRITE			*ss[2];
	int					seq_no;
	int					tr_type;
}TR_GRA_TEST;

//==============================================================================================
//
//	プロトタイプ宣言
//
//==============================================================================================

static	void	TrGraInit(TR_GRA_TEST *tgt);
static	void	TrGraTestBGCreate(TR_GRA_TEST *tgt,GF_BGL_INI *bgl);
static	void	TrGraTestDebugPrint(TR_GRA_TEST *tgt);
static	void	TrGraTestVBlank(void *work);
static	void	Init3DStuff_(void);
static	void	TrGraTestMSG_Print(TR_GRA_TEST *tgt);


//==================================================================================================
//
//	データ
//
//==================================================================================================

//==================================================================================================
//
//	関数
//
//==================================================================================================

static	void	TrGraInit(TR_GRA_TEST *tgt)
{
	SOFT_SPRITE_ARC	ssa;

	MI_CpuClearFast(tgt,sizeof(TR_GRA_TEST));

	tgt->end_flag = FALSE;
	tgt->bgl=GF_BGL_BglIniAlloc(HEAPID_BATTLE);
	tgt->win=GF_BGL_BmpWinAllocGet(HEAPID_BATTLE,1);

	TrGraTestBGCreate(tgt,tgt->bgl);

	tgt->ssm=SoftSpriteInit(HEAPID_BATTLE);

	tgt->tr_type=TRTYPE_BOY;

	TrTypeGraArcDataGet(&ssa,tgt->tr_type);
	tgt->ss[0]=SoftSpriteAdd(tgt->ssm,&ssa,APPEAR_X_TYPE_BB,APPEAR_Y_TYPE_BB,APPEAR_Z_TYPE_BB,1,NULL,NULL);

	GF_BGL_BmpWinAdd(tgt->bgl,tgt->win,GF_BGL_FRAME1_M,0x02,0x13,28,4,0x0a,0x0d);

	TrGraTestMSG_Print(tgt);
	Snd_Stop();
}

//============================================================================================
/**
 *	戦闘背景画面初期化＆画面生成
 */
//============================================================================================
static	void	TrGraTestBGCreate(TR_GRA_TEST *tgt,GF_BGL_INI *bgl)
{
	Init3DStuff_();

	//カメラの共通設定を行います。
    {
        // 単位行列と等価
        VecFx32 Eye = { 0, 0, 0 };                  // Eye position
        VecFx32 vUp = { 0, FX32_ONE, 0 };           // Up
        VecFx32 at = { 0, 0, -FX32_ONE };           // Viewpoint

        // Matrix mode is changed to GX_MTXMODE_POSITION_VECTOR internally,
        // and the camera matrix is loaded to the current matrix.
        G3_LookAt(&Eye, &vUp, &at, NULL);
    }
    // 描画の際に有効となる、属性を設定します。
    // 不必要な、属性を無効設定することによって、パフォーマンスが向上します。
    NNS_G2dSetSpriteAttrEnable(
        NNS_G2D_SPRITEATTR_ALPHA |
        NNS_G2D_SPRITEATTR_UV    |
        NNS_G2D_SPRITEATTR_TEXTUE|
        NNS_G2D_SPRITEATTR_ROTXY |
        NNS_G2D_SPRITEATTR_ROTO
    );

	GF_Disp_GX_VisibleControlInit();

	//VRAM設定
	{
		GF_BGL_DISPVRAM vramSetTable = {
			GX_VRAM_BG_128_C,				// メイン2DエンジンのBG
			GX_VRAM_BGEXTPLTT_NONE,			// メイン2DエンジンのBG拡張パレット
			GX_VRAM_SUB_BG_32_H,			// サブ2DエンジンのBG
			GX_VRAM_SUB_BGEXTPLTT_NONE,		// サブ2DエンジンのBG拡張パレット
			GX_VRAM_OBJ_64_E,				// メイン2DエンジンのOBJ
			GX_VRAM_OBJEXTPLTT_NONE,		// メイン2DエンジンのOBJ拡張パレット
			GX_VRAM_SUB_OBJ_16_I,			// サブ2DエンジンのOBJ
			GX_VRAM_SUB_OBJEXTPLTT_NONE,	// サブ2DエンジンのOBJ拡張パレット
			GX_VRAM_TEX_01_AB,				// テクスチャイメージスロット
			GX_VRAM_TEXPLTT_01_FG			// テクスチャパレットスロット
		};
		GF_Disp_SetBank( &vramSetTable );
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
				0, 0, 0x2000, 0, GF_BGL_SCRSIZ_512x512, GX_BG_COLORMODE_16,
				GX_BG_SCRBASE_0x1000, GX_BG_CHARBASE_0x0c000, GX_BG_EXTPLTT_01,
				1, 0, 0, FALSE
			},
			///<FRAME3_M
			{
				0, 0, 0x1000, 0, GF_BGL_SCRSIZ_512x256, GX_BG_COLORMODE_256,
				GX_BG_SCRBASE_0x3000, GX_BG_CHARBASE_0x10000, GX_BG_EXTPLTT_01,
				3, 0, 0, FALSE
			},
		};
		GF_BGL_BGControlSet(bgl, GF_BGL_FRAME1_M, &TextBgCntDat[0], GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear(bgl, GF_BGL_FRAME1_M );
		GF_BGL_BGControlSet(bgl, GF_BGL_FRAME2_M, &TextBgCntDat[1], GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear(bgl, GF_BGL_FRAME2_M );
		GF_BGL_BGControlSet(bgl, GF_BGL_FRAME3_M, &TextBgCntDat[2], GF_BGL_MODE_TEXT );
		GF_BGL_ScrClear(bgl, GF_BGL_FRAME3_M );

		G2_SetBG0Priority(0x01);
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
	}
	//サブ画面フレーム設定
	{
	}

	//背景グラフィックデータロード
	{
		ArcUtil_BgCharSet(ARC_BATT_BG,BATTLE_WBG0A_NCGR_BIN,bgl,GF_BGL_FRAME1_M,0,0,1,HEAPID_BATTLE);
		ArcUtil_ScrnSet(ARC_BATT_BG,BATTLE_WBG0A_NSCR_BIN,bgl,GF_BGL_FRAME1_M,0,0,1,HEAPID_BATTLE);
		ArcUtil_BgCharSet(ARC_BATT_BG,BATTLE_BG00_NCGR_BIN,bgl,GF_BGL_FRAME3_M,0,0,1,HEAPID_BATTLE);
		ArcUtil_PalSet(ARC_BATT_BG,BATT_BG00_D_NCLR,PALTYPE_MAIN_BG,0,0,HEAPID_BATTLE);
		ArcUtil_ScrnSet(ARC_BATT_BG,BATTLE_BG00_NSCR_BIN,bgl,GF_BGL_FRAME3_M,0,0,1,HEAPID_BATTLE);
	}

	GF_Disp_DispOn();

	sys_VBlankFuncChange(TrGraTestVBlank,tgt);
}

//============================================================================================
/**
 *	メインループタスク
 */
//============================================================================================
static	void	TrGraTestMain(TR_GRA_TEST * tgt)
{
	if(sys.repeat & PAD_KEY_LEFT){
		if(tgt->tr_type==0){
			tgt->tr_type=TRTYPE_MAX;
		}
		else{
			tgt->tr_type--;
		}
	}
	else if(sys.repeat & PAD_KEY_RIGHT){
		if(tgt->tr_type==TRTYPE_MAX){
			tgt->tr_type=0;
		}
		else{
			tgt->tr_type++;
		}
	}
	if(sys.repeat & PAD_BUTTON_L){
		if(tgt->tr_type-10<0){
			tgt->tr_type=TRTYPE_MAX+(tgt->tr_type-10);
		}
		else{
			tgt->tr_type-=10;
		}
	}
	else if(sys.repeat & PAD_BUTTON_R){
		if(tgt->tr_type+10>TRTYPE_MAX){
			tgt->tr_type=tgt->tr_type+10-TRTYPE_MAX;
		}
		else{
			tgt->tr_type+=10;
		}
	}
	if(sys.repeat){
		TrGraTestDebugPrint(tgt);
	}
	if(sys.trg & PAD_BUTTON_SELECT){
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_OFF );
		GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG1, VISIBLE_OFF );
		GF_BGL_BGControlExit(tgt->bgl, GF_BGL_FRAME1_M );
		GF_BGL_BGControlExit(tgt->bgl, GF_BGL_FRAME2_M );
		GF_BGL_BGControlExit(tgt->bgl, GF_BGL_FRAME3_M );
		GF_BGL_BmpWinFree(tgt->win,1);
		SoftSpriteEnd(tgt->ssm);
		sys_FreeMemoryEz(tgt->bgl);
		tgt->end_flag = TRUE;
		return;
	}

	SoftSpriteMain(tgt->ssm);
	G3_SwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_Z);
}

//============================================================================================
/**
 *	メインループタスク
 */
//============================================================================================
static	void	TrGraTestDebugPrint(TR_GRA_TEST *tgt)
{
	int				height;
	SOFT_SPRITE_ARC	*ssa;

	ssa=SoftSpriteArcPointerGet(tgt->ssm,0);
	TrTypeGraArcDataGet(ssa,tgt->tr_type);

	TrGraTestMSG_Print(tgt);

	SoftSpriteRecover(tgt->ssm);
}

//==============================================================================================
//
//	タイトルデバックメニューから呼ばれるように追加
//
//==============================================================================================
//--------------------------------------------------------------
//--------------------------------------------------------------
static PROC_RESULT TrGraTestProc_Init(PROC * proc, int * seq)
{
	TR_GRA_TEST	*tgt;
	sys_CreateHeap(HEAPID_BASE_APP,HEAPID_BATTLE,BATTLE_ALLOC_SIZE);
	tgt=PROC_AllocWork(proc,sizeof(TR_GRA_TEST),HEAPID_BATTLE);
	TrGraInit(tgt);
	return PROC_RES_FINISH;
}

//--------------------------------------------------------------
//--------------------------------------------------------------
static PROC_RESULT TrGraTestProc_Main(PROC * proc, int * seq)
{
	TR_GRA_TEST * tgt = PROC_GetWork(proc);
	TrGraTestMain(tgt);
	if (tgt->end_flag) {
		return PROC_RES_FINISH;
	} else {
		return PROC_RES_CONTINUE;
	}
}

//--------------------------------------------------------------
//--------------------------------------------------------------
static PROC_RESULT TrGraTestProc_End(PROC * proc, int * seq)
{
	PROC_FreeWork(proc);
	sys_DeleteHeap(HEAPID_BATTLE);
	Main_SetNextProc(NO_OVERLAY_ID, &TitleProcData);
	//sys_MainProcChange( TitleMainProc );				//復帰先
	//ソフトリセット
	//詳細はソース先頭の「サウンドテストの例外処理について」を参照して下さい
	//OS_InitReset();
	OS_ResetSystem(0);									//ソフトリセット
	return PROC_RES_FINISH;
}

//--------------------------------------------------------------
//--------------------------------------------------------------
const PROC_DATA TrGraTestProcData = {
	TrGraTestProc_Init,
	TrGraTestProc_Main,
	TrGraTestProc_End,
	NO_OVERLAY_ID
};

//--------------------------------------------------------------
/**
 * @brief	VBLANK関数
 *
 * @param	work	VBLankには引数が必要なので定義してあるが実際にはNULLが入っているので、アクセスは禁止！
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static	void	TrGraTestVBlank(void *work)
{
	TR_GRA_TEST	*tgt=(TR_GRA_TEST *)work;

	SoftSpriteTextureTrans(tgt->ssm);
	OS_SetIrqCheckFlag( OS_IE_V_BLANK);
}

//--------------------------------------------------------------
/**
 * @brief	3D初期化
 *
 * @retval	none	
 */
//--------------------------------------------------------------
static void Init3DStuff_(void)
{
    G3X_Init();                                            // initialize the 3D graphics states
    G3X_InitMtxStack();                                    // initialize the matrix stack

    G2_SetBG0Priority(1);

    G3X_SetShading(GX_SHADING_TOON);
    G3X_AntiAlias(TRUE);
    G3X_AlphaBlend(TRUE);

    // 3D 面は特殊効果OFFでも他のBG面とαブレンディングが行われますが、
    // そのためにはαブレンディング対象面の指定を行う必要があります。
    // SDK には対象面のみを設定する API が存在しないので、代わりに G2_SetBlendAlpha を使います。
    // この場合 G2_SetBlendAlpha の後ろ2つの引数は無視されます。
    G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG0, GX_BLEND_PLANEMASK_BD, 0, 0);

    // clear color
    G3X_SetClearColor(GX_RGB(0, 0, 0), 0, 0x7fff, 0, FALSE );

    G3_SwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_Z);
}

//--------------------------------------------------------------
//	メッセージ表示位置定義
//--------------------------------------------------------------
#define	TR_NUM_X	(0)		//モンスターナンバー表示X位置
#define	TR_NUM_Y	(8)		//モンスターナンバー表示Y位置
#define	TR_TYPE_X	(32)	//トレーナータイプ名表示X位置
#define	TR_TYPE_Y	(8)	//トレーナータイプ名表示Y位置


//--------------------------------------------------------------
/**
 * @brief	メッセージ表示
 *
 * @retval	none	
 */
//--------------------------------------------------------------
static	void	TrGraTestMSG_Print(TR_GRA_TEST *tgt)
{
	MSGDATA_MANAGER		*msg_m;
	STRBUF				*msg_buf;

	GF_BGL_BmpWinDataFill(tgt->win,0xff);

	msg_buf=STRBUF_Create(0x100,HEAPID_BATTLE);

	//ナンバー
	STRBUF_SetNumber( msg_buf, tgt->tr_type, 3, NUMBER_DISPTYPE_ZERO,NUMBER_CODETYPE_DEFAULT);
	GF_STR_PrintSimple(tgt->win,FONT_SYSTEM,msg_buf,TR_NUM_X,TR_NUM_Y,0,NULL);

	//トレーナータイプ名
	msg_m=MSGMAN_Create(MSGMAN_TYPE_DIRECT,ARC_MSG,NARC_msg_trtype_dat,HEAPID_BATTLE);
	MSGMAN_GetString(msg_m,tgt->tr_type,msg_buf);
	MSGMAN_Delete(msg_m);
	GF_STR_PrintSimple(tgt->win,FONT_SYSTEM,msg_buf,TR_TYPE_X,TR_TYPE_Y,0,NULL);

	sys_FreeMemoryEz(msg_buf);
}

#endif PM_DEBUG
