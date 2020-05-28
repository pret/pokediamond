//============================================================================================
/**
 * @file	worldtrade_status.c
 * @bfief	世界交換ポケモンステータス画面呼び出し・復帰
 * @author	Akito Mori
 * @date	06.05.10
 */
//============================================================================================
#include "common.h"
#include <dwc.h>
#include "libdpw/dpw_tr.h"
#include "system/procsys.h"
#include "system/arc_tool.h"
#include "system/arc_util.h"
#include "system/clact_tool.h"
#include "system/msgdata_util.h"
#include "system/wordset.h"
#include "msgdata/msg.naix"
#include "system/wipe.h"
#include "system/fontproc.h"
#include "system/lib_pack.h"
#include "system/lib_pack.h"
#include "system/fontoam.h"
#include "system/window.h"
#include "gflib/touchpanel.h"
#include "system/bmp_menu.h"
#include "system/snd_tool.h"
#include "gflib/strbuf_family.h"
#include "savedata/savedata.h"
#include "savedata/wifilist.h"
#include "savedata/worldtrade_data.h"
#include "savedata/zukanwork.h"
#include "savedata/sp_ribbon.h"
#include "poketool/pokeparty.h"
#include "poketool/boxdata.h"
#include "itemtool/itemsym.h"

#include "application/worldtrade.h"
#include "worldtrade_local.h"

#include "libdpw/dpw_tr.h"




//============================================================================================
//	プロトタイプ宣言
//============================================================================================
/*** 関数プロトタイプ ***/
//static void InitWork( WORLDTRADE_WORK *wk );
//static void FreeWork( WORLDTRADE_WORK *wk );



// ステータス画面で表示するフラグの列（ビットテーブルにすればいいのに…）
static const u8 StatusPageTable[]={
	PST_PAGE_INFO,			// 「ポケモンじょうほう」
	PST_PAGE_MEMO,			// 「トレーナーメモ」
	PST_PAGE_PARAM,			// 「ポケモンのうりょく」
	PST_PAGE_CONDITION,		// 「コンディション」
	PST_PAGE_B_SKILL,		// 「たたかうわざ」
	PST_PAGE_C_SKILL,		// 「コンテストわざ」
	PST_PAGE_RIBBON,		// 「きねんリボン」
	PST_PAGE_RET,			// 「もどる」
	PST_PAGE_MAX

};

//============================================================================================
//	プロセス関数
//============================================================================================

//==============================================================================
/**
 * $brief   世界交換入り口画面初期化
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//==============================================================================
int WorldTrade_Status_Init(WORLDTRADE_WORK *wk, int seq)
{
	// ワーク初期化
//	InitWork( wk );
	
	
	wk->statusParam.ppd  = WorldTrade_GetPokePtr(wk->param->myparty, wk->param->mybox, wk->BoxTrayNo, wk->BoxCursorPos);
	wk->statusParam.ppt  = PST_PP_TYPE_POKEPASO;
	wk->statusParam.max  = 1;
	wk->statusParam.pos  = 0;
	wk->statusParam.mode = PST_MODE_NO_WAZACHG;	// 技入れ替え禁止にする
	wk->statusParam.waza = 0;
	wk->statusParam.ev_contest = PokeStatus_ContestFlagGet(wk->param->savedata);
	wk->statusParam.zukan_mode = wk->param->zukanmode;
	wk->statusParam.cfg        = wk->param->config;
	wk->statusParam.ribbon     = SaveData_GetSpRibbon(wk->param->savedata);
	PokeStatus_PageSet( &wk->statusParam, StatusPageTable );
	PokeStatus_PlayerSet( &wk->statusParam, wk->param->mystatus );
	
	wk->proc = PROC_Create( &PokeStatusProcData, &wk->statusParam, HEAPID_WORLDTRADE );

	wk->subprocflag = 1;

	return SEQ_FADEIN;
}
//==============================================================================
/**
 * $brief   世界交換入り口画面メイン
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//==============================================================================
int WorldTrade_Status_Main(WORLDTRADE_WORK *wk, int seq)
{
	int ret=SEQ_MAIN;

		if( ProcMain( wk->proc ) ){

			PROC_Delete( wk->proc );

			WorldTrade_SubProcessChange( wk, WORLDTRADE_MYBOX, wk->sub_process_mode );
			
			ret = SEQ_FADEOUT;
		}

	return ret;
}


//==============================================================================
/**
 * $brief   世界交換入り口画面終了
 *
 * @param   wk		
 * @param   seq		
 *
 * @retval  int		
 */
//==============================================================================
int WorldTrade_Status_End(WORLDTRADE_WORK *wk, int seq)
{
//	FreeWork( wk );

	// ボックス画面に戻る
	WorldTrade_SubProcessUpdate( wk );

	return SEQ_INIT;
}
