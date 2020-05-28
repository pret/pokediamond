/**
 *	@brief	ポルト　アクターシステム
 */

#include "common.h"
#include "field/field_matrix.h"
#include "field/field_place_name.h"
#include "system/procsys.h"
#include "system/arc_util.h"
#include "system/arc_tool.h"
#include "system/clact_util.h"
#include "system/clact_tool.h"
#include "system/render_oam.h"
#include "system/fontproc.h"
#include "system/pm_str.h"
#include "system/msgdata.h"
#include "system/bmp_list.h"
#include "system/pm_str.h"
#include "system/buflen.h"
#include "system/window.h"
#include "communication/communication.h"

#include "application/poru_tool.h"
#include "porusys.h"

#define PORUC_ACTRES_MAX	(3)

///プロトタイプ
void PoruCase_ActorInit(PORU_CASE_WORK *wk);
void PoruCase_ActorRelease(PORU_CASE_WORK *wk);
void PoruCase_ActorMain(PORU_CASE_WORK *wk);
void PoruCase_ActorTrans(PORU_CASE_WORK* wk);

void PoruCase_ActorInit(PORU_CASE_WORK *wk)
{
	initVramTransferManagerHeap(32,wk->heapID);

	//セルアクターシステム初期化
	wk->pActSys = CATS_AllocMemory(wk->heapID);
	wk->pActRes = CATS_ResourceCreate(wk->pActSys);

	{
		TCATS_OAM_INIT	coi = {
			0,128,		///< メイン	OAM管理領域・開始/終了
			0,32,		///< メイン	アフィン管理領域・開始/終了
			0,128,		///< サブ	OAM管理領域・開始/終了
			0,32,		///< サブ	アフィン管理領域・開始/終了
		};
		TCATS_CHAR_MANAGER_MAKE ccmm = {
			PORUC_ACTRES_MAX,	//ID制御数
			1024,	//メイン画面サイズ(byte単位)
			1024,	//サブ画面サイズ(byte単位)
			GX_OBJVRAMMODE_CHAR_1D_32K,	//メインOBJモード指定
			GX_OBJVRAMMODE_CHAR_1D_32K,	//サブOBJモード指定
		};

		CATS_SystemInit( wk->pActSys, &coi, &ccmm, 32 );
		CATS_ClactSetInit( wk->pActSys, wk->pActRes,PORUCASE_ACTMAX );

		//OAM初期化
		REND_OAM_UtilOamRamClear_Main(wk->heapID);
		REND_OAM_UtilOamRamClear_Sub(wk->heapID);
	}

	{
		TCATS_RESOURCE_FILE_LIST list = {
			"data/porucase_chr.resdat",		// キャラクタ
			"data/porucase_pal.resdat",		// パレット
			"data/porucase_cell.resdat",	// セル
			"data/porucase_canm.resdat",	// セルアニメ
			NULL,						// マルチセル
			NULL,						// マルチセルアニメ
			"data/porucase_celact.cldat"		// ヘッダー		
		};
		CATS_ResourceLoadBinary( wk->pActSys, wk->pActRes, &list );
	}

	///ポルトOAMマネージャ初期化
	wk->poruMan = PoruOam_SysInit(wk->heapID,1,1,PORUOAM_DRAW_MAIN,PORUOAM_CGXOFS_AUTO);

	//通信中なら通信アイコン復帰
	if(CommIsInitialize()){
		WirelessIconEasy();
	}

	GF_Disp_GX_VisibleControl(GX_PLANEMASK_OBJ,VISIBLE_ON);
	GF_Disp_GXS_VisibleControl(GX_PLANEMASK_OBJ,VISIBLE_ON);
}

void PoruCase_ActorRelease(PORU_CASE_WORK *wk)
{
	PoruOam_SysRelease(wk->poruMan);
	CATS_ResourceDestructor(wk->pActSys,wk->pActRes);
	CATS_FreeMemory(wk->pActSys);
	DellVramTransferManager();	
}

void PoruCase_ActorMain(PORU_CASE_WORK *wk)
{
	CATS_Draw(wk->pActRes);
	PoruOam_DrawMain(wk->poruMan);
}

void PoruCase_ActorTrans(PORU_CASE_WORK* wk)
{
	CATS_RenderOamTrans();
}

void NAct_CursorChg(PORU_CASE_WORK* wk,BOOL mode)
{
	if(mode == FALSE){
		CLACT_PaletteNoChg(wk->pAct[NACT_CURSOR],NACT_CUR_PALF);
		CLACT_SetAnmFlag(wk->pAct[NACT_UP],TRUE);
		CLACT_SetAnmFlag(wk->pAct[NACT_DOWN],TRUE);
	}else{
		CLACT_PaletteNoChg(wk->pAct[NACT_CURSOR],NACT_CUR_PALT);
		CLACT_SetAnmFlag(wk->pAct[NACT_UP],FALSE);
		CLACT_SetAnmFlag(wk->pAct[NACT_DOWN],FALSE);
	}
}
