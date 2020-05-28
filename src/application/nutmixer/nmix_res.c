/**
 *	@file	nmix_res.c
 *	@brief	ナッツミキサー　リソース管理
 *	@author	Miyuki Iwasawa
 *	@date	06.04.08
 */

#include "common.h"
#include "system/procsys.h"
#include "system/snd_tool.h"
#include "system/fontproc.h"
#include "system/pm_str.h"
#include "system/buflen.h"
#include "system/palanm.h"
#include "system/savedata.h"
#include "system/render_oam.h"
#include "itemtool/itemsym.h"
#include "itemtool/item.h"
#include "gflib/strbuf_family.h"

#include "application/nutmixer.h"
#include "nutmixer_sys.h"
#include "nmix_game.h"
#include "nmix_gameseq.h"

#include "nutmixer.naix"

#define __NMIX_RES_H_GLOBAL
#include "nmix_res.h"

//======================================================
//ゲームプロセス　コマンド内サブシーケンス群
//======================================================
static void nmixGame_BGLInit(GF_BGL_INI** bgl,int heapID);
static void nmixGame_BGLRelease(GF_BGL_INI** bgl);
static void nmixGame_ClactInit( NMIX_GAMEWORK* wk );
static void nmixGame_ClactDelete( NMIX_GAMEWORK* wk );
static void nmixGame_SwspInit( NMIX_GAMEWORK* wk );
static void nmixGame_SwspDelete( NMIX_GAMEWORK* wk );
static void nmixGame_OamRegInit( NMIX_GAMEWORK* wk );
static void nmixGame_OamRegDelete( NMIX_GAMEWORK* wk );
static void nmixGame_DefOamResLoad( NMIX_GAMEWORK* wk );
static void nmixGame_DefOamResRelease( NMIX_GAMEWORK* wk );
static void nmixGame_3DInit( NMIX_GAMEWORK* wk );
static void nmixGame_3DRelease( NMIX_GAMEWORK* wk );
static void nmix_CommonDataInit(NMIX_GAMEWORK* wk);
static void nmix_CommonDataRelease(NMIX_GAMEWORK* wk);

//======================================================
//ゲームプロセス　コマンド群
//======================================================
/**
 *	@brief	コマンド　リソース初期化
 */
void NMixGameCom_GameStartGraphicInit(NMIX_GAMEWORK* wk)
{
	// 管理システム初期化
	nmixGame_3DInit( wk );
	nmixGame_BGLInit(&(wk->bgl),wk->heapID);	
	nmixGame_OamRegInit( wk );
	nmixGame_ClactInit( wk );
	nmixGame_SwspInit( wk );


	nmixGame_DefOamResLoad( wk );	// デフォルトOAMリソース
	NMixGameDemo_SubWin_GraphicLoad( &wk->sub_win, wk->bgl, wk->heapID );
	NMixGameDemo_MainWin_GraphicLoad( &wk->main_win, wk->bgl, wk->heapID );
	NMixGameDemo_NabeGra_GraphicLoad( &wk->nabe_gra, wk->swsp_sys, wk->heapID );
	NMixGameDemo_CountDown_GraphicLoad( &wk->countdown, &wk->clact,
			wk->def_clact_res, wk->heapID, NMIX_GAME_DEF_OAM_RES_START, 0 );

	NMixGameDemo_CountDown_GraphicLoad( &wk->pen, &wk->clact,
			wk->def_clact_res, wk->heapID, NMIX_GAME_DEF_OAM_RES_START, 2 );
	NMixGameDemo_CountDown_GraphicLoad( &wk->end_mark, &wk->clact,
			wk->def_clact_res, wk->heapID, NMIX_GAME_DEF_OAM_RES_END, 0 );
	NMixGameDemo_OtherMark_GraphicLoad( &wk->other_mark, &wk->clact,
			wk->def_clact_res, wk->heapID );
	NMixGameDemo_SoopEffect_GraphicLoad( &wk->soop_effect, &wk->clact,
			wk->def_clact_res, wk->heapID );
	NMixGameDemo_Yazirusi_GraphicLoad( &wk->yazirusi, &wk->clact, wk->heapID );
	NMixGameDemo_HosiKiraKira_GraphicLoad( &wk->hosi_kira, &wk->clact,
			wk->def_clact_res, wk->heapID );



	// メッセージデータ
	nmix_CommonDataInit(wk);

	// 描画先を変更
	sys.disp3DSW = DISP_3D_TO_SUB;
	GF_Disp_DispSelect();
}

/**
 *	@brief	コマンド　リソース解放
 */
void NMixGameCom_GameStartGraphicRelease(NMIX_GAMEWORK* wk)
{

	NMixGameDemo_MainWin_GraphicRelease( &wk->main_win );
	NMixGameDemo_SubWin_GraphicRelease( &wk->sub_win );
	NMixGameDemo_NabeGra_GraphicRelease( &wk->nabe_gra );
	nmixGame_DefOamResRelease( wk );	// デフォルトOAMリソース
	NMixGameDemo_CountDown_GraphicRelease( &wk->countdown );
	NMixGameDemo_CountDown_GraphicRelease( &wk->end_mark );
	NMixGameDemo_CountDown_GraphicRelease( &wk->pen );
	NMixGameDemo_OtherMark_GraphicRelease( &wk->other_mark );
	NMixGameDemo_SoopEffect_GraphicRelease( &wk->soop_effect );
	NMixGameDemo_Yazirusi_GraphicRelease( &wk->yazirusi );
	NMixGameDemo_HosiKiraKira_GraphicRelease( &wk->hosi_kira );
	
	
	// 管理システム破棄
	nmixGame_BGLRelease(&(wk->bgl));	
	nmixGame_ClactDelete( wk );
	nmixGame_OamRegDelete( wk );
	nmixGame_SwspDelete( wk );
	nmixGame_3DRelease( wk );

	//メッセージデータ
	nmix_CommonDataRelease(wk);

	// 描画先を変更
	sys.disp3DSW = DISP_3D_TO_MAIN;
	GF_Disp_DispSelect();
}


/**
 *	@brief	コマンド　リソース初期化
 */
int NMixGameCom_ResInit(NMIX_GAMEWORK* wk,int* seq)
{
	// 各ワークの描画物読み込み
	NMixGameDemo_NutsIn_GraphicLoad( &wk->nuts_in, 
			&wk->game_comm_pack.get_ko_before_data, &wk->clact, 
			wk->def_clact_res, wk->heapID);

	return wk->main_seq + 1;
}

/**
 *	@brief	コマンド　リソース解放
 */
int NMixGameCom_ResRelease(NMIX_GAMEWORK* wk,int *seq)
{
	// 各ワークの描画物破棄
	NMixGameDemo_NutsIn_GraphicRelease( &wk->nuts_in, &wk->clact );

	
	return wk->main_seq + 1;
}

//----------------------------------------------------------------------------
/**
 *	@brief		グラフィック描画処理
 */
//-----------------------------------------------------------------------------
void NMixGame_Draw( NMIX_GAMEWORK* wk )
{
	//３Ｄ描画開始
	GF_G3X_Reset();

	NNS_G3dGePushMtx();
	{
		NNS_G3dGeFlushBuffer();

		// ソフトウェアスプライトの描画
		// カメラセットアップ
		NNS_G2dSetupSoftwareSpriteCamera();
		// ソフトウェアスプライト描画
		if( wk->swsp_sys ){
			SWSP_SysDraw( wk->swsp_sys );
		}
	}
	NNS_G3dGePopMtx(1);

	/* ジオメトリ＆レンダリングエンジン関連メモリのスワップ */
	GF_G3_RequestSwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_Z);

	// セルアクター描画
	if( wk->clact_draw ){
		if( wk->clact.cas ){
			CLACT_Draw( wk->clact.cas );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief		描画関係Vブランク処理
 */
//-----------------------------------------------------------------------------
void NMixGame_GraVBlank( NMIX_GAMEWORK* wk )
{
	// レンダラーOAM転送
	REND_OAMTrans();
	if( wk->bgl ){
		GF_BGL_VBlankFunc( wk->bgl );
	}
}





//-----------------------------------------------------------------------------
/**
 *		プライベート関数
 */
//-----------------------------------------------------------------------------

//======================================================
//ゲームプロセス　ローカルサブ関数群
//======================================================
/**
 *	@brief	ナッツミキサーVramBank設定
 */
static void nmixGame_VBankSet(void)
{
	GF_BGL_DISPVRAM vramSetTable = {
		GX_VRAM_BG_64_E,				// メイン2DエンジンのBG
		GX_VRAM_BGEXTPLTT_NONE,			// メイン2DエンジンのBG拡張パレット
		GX_VRAM_SUB_BG_48_HI,			// サブ2DエンジンのBG
		GX_VRAM_SUB_BGEXTPLTT_NONE,		// サブ2DエンジンのBG拡張パレット
		GX_VRAM_OBJ_128_A,				// メイン2DエンジンのOBJ
		GX_VRAM_OBJEXTPLTT_NONE,		// メイン2DエンジンのOBJ拡張パレット
		GX_VRAM_SUB_OBJ_NONE,			// サブ2DエンジンのOBJ
		GX_VRAM_SUB_OBJEXTPLTT_NONE,	// サブ2DエンジンのOBJ拡張パレット
		GX_VRAM_TEX_01_BC,				// テクスチャイメージスロット
		GX_VRAM_TEXPLTT_01_FG			// テクスチャパレットスロット
	};
	GF_Disp_SetBank( &vramSetTable );
}

/**
 *	@brief	BGLセット
 */
static void nmixGame_BGLInit(GF_BGL_INI** bgl,int heapID)
{
	int i = 0,frame;

	//VramBankセット
	nmixGame_VBankSet();

	//BGL初期化
	*bgl = GF_BGL_BglIniAlloc(heapID);
	
	{	//BG SYSTEM
		GF_BGL_SYS_HEADER BGsys_data = {
			GX_DISPMODE_GRAPHICS,GX_BGMODE_0,GX_BGMODE_0,GX_BG0_AS_3D
		};
		GF_BGL_InitBG(&BGsys_data);
	}

	// 3D面表示ON
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_BG0, VISIBLE_ON );
	GF_BGL_PrioritySet( GF_BGL_FRAME0_M, 2 );
	
	{
		GF_BGL_BGCNT_HEADER TextBgCntDat[] = {
			{	//MAIN BG1	テキスト背景面
				0,0,0x800,0,GF_BGL_SCRSIZ_256x256,GX_BG_COLORMODE_16,
				GX_BG_SCRBASE_0xf000,GX_BG_CHARBASE_0x08000,GX_BG_EXTPLTT_01,
				1,0,0,FALSE
			},
			{	//MAIN BG2	テキスト面
				0,0,0x800,0,GF_BGL_SCRSIZ_256x256,GX_BG_COLORMODE_16,
				GX_BG_SCRBASE_0xe800,GX_BG_CHARBASE_0x00000,GX_BG_EXTPLTT_01,
				0,0,0,FALSE
			},
			{	//SUB BG0	文字列面に使用
				0,0,0x800,0,GF_BGL_SCRSIZ_256x256,GX_BG_COLORMODE_16,
				GX_BG_SCRBASE_0xb000,GX_BG_CHARBASE_0x00000,GX_BG_EXTPLTT_01,
				0,0,0,FALSE
			},
			{	//SUB BG1	背景に使用
				0,0,0x800,0,GF_BGL_SCRSIZ_256x256,GX_BG_COLORMODE_16,
				GX_BG_SCRBASE_0xa800,GX_BG_CHARBASE_0x08000,GX_BG_EXTPLTT_01,
				1,0,0,FALSE
			},
		};
		for(i = 0;i < 4;i++){
			const u8 frame[4] = 
			{GF_BGL_FRAME1_M,GF_BGL_FRAME2_M,GF_BGL_FRAME0_S,GF_BGL_FRAME1_S};
			
			GF_BGL_BGControlSet(*bgl,frame[i],&(TextBgCntDat[i]),GF_BGL_MODE_TEXT);
			GF_BGL_ScrClear(*bgl,frame[i]);
			GF_BGL_ClearCharSet(frame[i],32,0,heapID);
		}
	}
}

/**
 *	@brief	BGL解放
 */
static void nmixGame_BGLRelease(GF_BGL_INI** bgl)
{
	GF_BGL_BGControlExit(*bgl,GF_BGL_FRAME1_S);
	GF_BGL_BGControlExit(*bgl,GF_BGL_FRAME0_S);
	GF_BGL_BGControlExit(*bgl,GF_BGL_FRAME2_M);
	GF_BGL_BGControlExit(*bgl,GF_BGL_FRAME1_M);
	sys_FreeMemoryEz(*bgl);
}


//----------------------------------------------------------------------------
/**
 *	@brief	セルアクター初期化
 *
 *	@param	wk	ワーク
 */
//-----------------------------------------------------------------------------
static void nmixGame_ClactInit( NMIX_GAMEWORK* wk )
{
	NMIXGAME_CLACT_Init( &wk->clact, NMIX_GAME_CLACT_WORK_MAX, NMIX_GAME_CLACT_RES_MAX, wk->heapID );
	
	// OBJON
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );
	GF_Disp_GXS_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );
}

//----------------------------------------------------------------------------
/**
 *	@brief	セルアクター破棄
 *
 *	@param	wk	ワーク
 */
//-----------------------------------------------------------------------------
static void nmixGame_ClactDelete( NMIX_GAMEWORK* wk )
{
	NMIXGAME_CLACT_Delete( &wk->clact );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ソフトウェアスプライト初期化
 *
 *	@param	wk	ワーク
 */
//-----------------------------------------------------------------------------
static void nmixGame_SwspInit( NMIX_GAMEWORK* wk )
{
	SWSP_SYSDATA swsp_sys_data = {
		NMIX_GAME_SWSP_WORK_MAX,
		NMIX_GAME_SWSP_CHAR_MAX,			
		NMIX_GAME_SWSP_PLTT_MAX,
		0
	};
	swsp_sys_data.heap = wk->heapID;

	wk->swsp_sys = SWSP_SysInit( &swsp_sys_data );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ソフトウェアスプライト破棄
 *
 *	@param	wk	ワーク
 */
//-----------------------------------------------------------------------------
static void nmixGame_SwspDelete( NMIX_GAMEWORK* wk )
{
	// ソフトウェアスプライト
	SWSP_SysDelete( wk->swsp_sys );
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAMのレジスタ初期化
 */
//-----------------------------------------------------------------------------
static void nmixGame_OamRegInit( NMIX_GAMEWORK* wk )
{
	// OAMマネージャーの初期化
	NNS_G2dInitOamManagerModule();

	// 共有OAMマネージャ作成
	// レンダラ用OAMマネージャ作成
	// ここで作成したOAMマネージャをみんなで共有する
	REND_OAMInit( 
			NMIX_OAM_OAM_MAIN_S, NMIX_OAM_OAM_MAIN_E,	// メイン画面NMIX_OAM管理領域
			NMIX_OAM_AFF_MAIN_S, NMIX_OAM_AFF_MAIN_E,			// メイン画面アフィン管理領域
			NMIX_OAM_OAM_SUB_S, NMIX_OAM_OAM_SUB_E,		// サブ画面NMIX_OAM管理領域
			NMIX_OAM_AFF_SUB_S, NMIX_OAM_AFF_SUB_E,		// サブ画面アフィン管理領域
			wk->heapID);
	
	// キャラクタマネージャー初期化
	{
		CHAR_MANAGER_MAKE cm = {
			NMIX_OAM_CHAR_ENTRY_NUM,
			NMIX_OAM_CHAR_VRAMTRANS_MAIN_SIZE,
			NMIX_OAM_CHAR_VRAMTRANS_SUB_SIZE,
		};
		cm.heap = wk->heapID;
		
		InitCharManagerReg(&cm, GX_OBJVRAMMODE_CHAR_1D_128K, GX_OBJVRAMMODE_CHAR_1D_32K );
	}
	// パレットマネージャー初期化
	InitPlttManager(NMIX_OAM_PLTT_ENTRY_NUM, wk->heapID);

	// 読み込み開始位置を初期化
	CharLoadStartAll();
	PlttLoadStartAll();
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAMのレジスタ管理データ破棄
 */
//-----------------------------------------------------------------------------
static void nmixGame_OamRegDelete( NMIX_GAMEWORK* wk )
{
	// レンダラー共有OAMマネージャ破棄
	REND_OAM_Delete();
	
	// キャラクタデータ破棄
	DeleteCharManager();
	// パレットデータ破棄
	DeletePlttManager();
}

//----------------------------------------------------------------------------
/**
 *	@brief	デフォルトOAMリソース読み込み
 */
//-----------------------------------------------------------------------------
static void nmixGame_DefOamResLoad( NMIX_GAMEWORK* wk )
{
	int i;
	static const u8 ClPlttTbl[ NMIX_GAME_DEF_OAM_RES_NUM ] = {
		NARC_nutmixer_cook_s_obj0_NCLR,
		NARC_nutmixer_cook_s_obj0_NCLR,
		NARC_nutmixer_cook_s_obj2_NCLR,
		NARC_nutmixer_cook_s_obj3_NCLR,
		NARC_nutmixer_cook_s_obj4_NCLR,
		NARC_nutmixer_cook_s_obj0_NCLR,
	};

	for( i=0; i<NMIX_GAME_DEF_OAM_RES_NUM; i++ ){
		if( (i > 0) && (ClPlttTbl[ i ] == NARC_nutmixer_cook_s_obj0_NCLR) ){		
			NMIXGAME_CLACT_ResLoadEasy_PlttCopy( &wk->clact,		// リソースインデックス0のパレットを皆共通で使用する
					&wk->def_clact_res[ i ], ARC_NUTMIXER_GRA,
					wk->def_clact_res[ 0 ].resobj[1],
					NARC_nutmixer_cook_s_obj0_NCGR + (3*i), 
					NARC_nutmixer_cook_s_obj0_NCER + (3*i), 
					NARC_nutmixer_cook_s_obj0_NANR + (3*i), 
					NMIX_GAME_DEF_OAM_CONTID + i, wk->heapID );

		}else{
			NMIXGAME_CLACT_ResLoadEasy( &wk->clact,
					&wk->def_clact_res[ i ], ARC_NUTMIXER_GRA,
					ClPlttTbl[ i ],
					NMIX_GAME_DEF_OAM_CL,
					NARC_nutmixer_cook_s_obj0_NCGR + (3*i), 
					NARC_nutmixer_cook_s_obj0_NCER + (3*i), 
					NARC_nutmixer_cook_s_obj0_NANR + (3*i), 
					NMIX_GAME_DEF_OAM_CONTID + i, wk->heapID );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	デフォルトOAMリソース破棄
 */
//-----------------------------------------------------------------------------
static void nmixGame_DefOamResRelease( NMIX_GAMEWORK* wk )
{
	int i;

	for( i=0; i<NMIX_GAME_DEF_OAM_RES_NUM; i++ ){
		NMIXGAME_CLACT_ResDeleteEasy( &wk->clact,
				&wk->def_clact_res[ i ] );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	３D初期化
 */
//-----------------------------------------------------------------------------
static void nmixGame_3DInit( NMIX_GAMEWORK* wk )
{
	// NitroSystem:３Ｄエンジンの初期化
	NNS_G3dInit();
	// マトリクススタックの初期化
    G3X_InitMtxStack();

	// 各種描画モードの設定(シェード＆アンチエイリアス＆半透明)
    G3X_SetShading(GX_SHADING_TOON);
    G3X_AntiAlias(TRUE);
	G3X_AlphaTest(FALSE, 0);	// アルファテスト　　オフ
	G3X_AlphaBlend(TRUE);		// アルファブレンド　オン

	// エッジマーキング
	G3X_EdgeMarking(FALSE);

	
	// クリアカラーの設定
    G3X_SetClearColor(GX_RGB(31, 31, 16),	// clear color
                      0,				// clear alpha
                      0x7fff,			// clear depth
                      63,				// clear polygon ID
                      FALSE				// fog
                      );

	// ジオメトリエンジン起動後必ず呼ばれなければならない
    G3_SwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_W);

	// ビューポートの設定
    G3_ViewPort(0, 0, 255, 191);

	// マネージャがテクスチャイメージスロットを指定スロット分管理できるようにして
	// デフォルトマネージャにする。
	NNS_GfdInitFrmTexVramManager(2, TRUE);
		
	// マネージャがパレットを32KB分管理できるようにして
	// デフォルトマネージャにする。
	NNS_GfdInitFrmPlttVramManager(0x8000, TRUE);
}

//----------------------------------------------------------------------------
/**
 *	@brief	３D破棄
 */
//-----------------------------------------------------------------------------
static void nmixGame_3DRelease( NMIX_GAMEWORK* wk )
{
	NNS_GfdResetFrmTexVramState();
	NNS_GfdResetFrmPlttVramState();
}

/**
 *	@brief	文字列データ作成	
 */
static void nmix_CommonDataInit(NMIX_GAMEWORK* wk)
{
	int i;
	
	//メッセージマネージャ初期化
	wk->msgDat.man = MSGMAN_Create(MSGMAN_TYPE_NORMAL,ARC_MSG,
		NARC_msg_porutogame1_dat,wk->heapID);
	
	wk->msgDat.wset = WORDSET_CreateEx( NMIX_GAME_WORD_SET_MAX, WORDSET_NMIXER_BUFLEN,wk->heapID);
	
	//デフォルト文字列取得
	wk->msgDat.tmp = STRBUF_Create(WORDSET_NMIXER_BUFLEN,wk->heapID);

	wk->msgDat.wait = MSGMAN_AllocString(wk->msgDat.man,mes_porutogame1_00_01);
	wk->msgDat.nuts_in = MSGMAN_AllocString(wk->msgDat.man,mes_porutogame1_01_01);
	wk->msgDat.tr_name = MSGMAN_AllocString(wk->msgDat.man,mes_porutogame1_02_01);

	wk->msgDat.casein = MSGMAN_AllocString(wk->msgDat.man,mes_porutogame1_05_01);
	wk->msgDat.replay = MSGMAN_AllocString(wk->msgDat.man,mes_porutogame1_05_02);
	wk->msgDat.exit = MSGMAN_AllocString(wk->msgDat.man,mes_porutogame1_05_03);
	wk->msgDat.bag_erabu = MSGMAN_AllocString(wk->msgDat.man,mes_porutogame1_05_04);
	wk->msgDat.poruto_ippai = MSGMAN_AllocString(wk->msgDat.man,mes_porutogame1_05_05);
	wk->msgDat.nuts_none = MSGMAN_AllocString(wk->msgDat.man,mes_porutogame1_05_06);

	wk->msgDat.end = MSGMAN_AllocString(wk->msgDat.man,mes_porutogame1_03_06);
	wk->msgDat.result = MSGMAN_AllocString(wk->msgDat.man,mes_porutogame1_04_01);

	for(i = 0;i < NMIX_STMSG_SPEED_NUM;i++){
		wk->msgDat.spd[i] = MSGMAN_AllocString(wk->msgDat.man,mes_porutogame1_03_01+i);
	}
	for(i = 0;i < NMIX_STMSG_RESULT_NUM;i++){
		wk->msgDat.res[i] = MSGMAN_AllocString(wk->msgDat.man,mes_porutogame1_04_02+i);
	}
}


/**
 *	@brief	文字列データ破棄
 */
static void nmix_CommonDataRelease(NMIX_GAMEWORK* wk)
{
	int i;
	
	STRBUF_Delete(wk->msgDat.result);	
	STRBUF_Delete(wk->msgDat.end);	
	
	STRBUF_Delete(wk->msgDat.exit);	
	STRBUF_Delete(wk->msgDat.replay);	
	STRBUF_Delete(wk->msgDat.casein);	
	
	STRBUF_Delete(wk->msgDat.tr_name);	
	STRBUF_Delete(wk->msgDat.nuts_in);	
	STRBUF_Delete(wk->msgDat.wait);	
	STRBUF_Delete(wk->msgDat.bag_erabu);
	STRBUF_Delete(wk->msgDat.poruto_ippai);
	STRBUF_Delete(wk->msgDat.nuts_none);
	
	for(i = 0;i < NMIX_STMSG_SPEED_NUM;i++){
		STRBUF_Delete(wk->msgDat.spd[i]);
	}
	for(i = 0;i < NMIX_STMSG_RESULT_NUM;i++){
		STRBUF_Delete(wk->msgDat.res[i]);
	}
	STRBUF_Delete(wk->msgDat.tmp);
	
	WORDSET_Delete(wk->msgDat.wset);
	MSGMAN_Delete(wk->msgDat.man);
}



