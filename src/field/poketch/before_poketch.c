//============================================================================================
/**
 * @file	before_poketch.c
 * @bfief	ポケッチ取得以前画面
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include "common.h"
#include "tcb.h"
#include "system\arc_util.h"
#include "field\poketch.h"


#include "poketch_arc.h"



//------------------------------------------------------------------
/**
 * ポケッチ取得以前の画面構築
 *
 * @param   none		
 *
 */
//------------------------------------------------------------------
void BeforePoketchInit( GF_BGL_INI* bgl )
{
	static const GF_BGL_BGCNT_HEADER header = {
		0, 0, 0x800, 0,	// scrX, scrY, scrbufSize, scrbufofs,
		GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
		GX_BG_SCRBASE_0x6000, GX_BG_CHARBASE_0x00000,
		GX_BG_EXTPLTT_01, 0, 0, 0, FALSE	// pal, pri, areaover, dmy, mosaic
	};

	// 異様にデカいがポケッチの合計と同じにしておく
	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_POKETCH_APP,  0x18000 );

// BG 設定
	GXS_SetGraphicsMode(GX_BGMODE_0);

	GX_SetBankForSubBG(GX_VRAM_SUB_BG_32_H);
	GX_SetBankForSubOBJ(GX_VRAM_SUB_OBJ_16_I);
	GXS_SetOBJVRamModeChar( GX_OBJVRAMMODE_CHAR_1D_32K );

	GF_BGL_BGControlSet( bgl, GF_BGL_FRAME0_S, &header, GF_BGL_MODE_TEXT );


	ArcUtil_BgCharSet(ARC_POKETCH_IMG, NARC_poketch_before_lz_ncgr, bgl, GF_BGL_FRAME0_S,
		0, 0, TRUE, HEAPID_POKETCH_APP);
	ArcUtil_ScrnSet(ARC_POKETCH_IMG, NARC_poketch_before_lz_nscr, bgl, GF_BGL_FRAME0_S,
		0, 0, TRUE, HEAPID_POKETCH_APP);
	ArcUtil_PalSet(ARC_POKETCH_IMG, NARC_poketch_before_nclr, PALTYPE_SUB_BG,
		0, 0x20, HEAPID_POKETCH_APP);


	GXS_SetVisibleWnd(GX_WNDMASK_NONE);
	GXS_SetVisiblePlane(GX_PLANEMASK_BG0);
}

void BeforePoketchQuitReq( GF_BGL_INI* bgl )
{
	GF_BGL_BGControlExit( bgl, GF_BGL_FRAME0_S );
	sys_DeleteHeap( HEAPID_POKETCH_APP );
}

BOOL BeforePoketchQuitWait( GF_BGL_INI* bgl )
{
	return TRUE;
}
