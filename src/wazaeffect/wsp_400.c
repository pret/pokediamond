//==============================================================================
/**
 * @file	wsp_400.c
 * @brief	400番台の技エフェクト
 * @author	goto
 * @date	2006.03.09
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================

#include "common.h"				///< 必須
#include "system/lib_pack.h"	///< 必須
#include "west_sp.h"			///< 必須
#include "wsp.h"				///< xxx.cに対するxxx.hは必須

#include "wazatool.h"			///< 技エフェクト支援関数郡
#include "we_tool.h"			///< 

#include "ball_effect.h"
#include "system/arc_tool.h"	///< アーカイブ用
#include "system/arc_util.h"	///< アーカイブ用

#include "we_def.h"

///< 425
typedef struct {

	TWE_TOOL_SYS		ts;		///< 技エフェクト汎用構造体
	TWE_POKE_SYS		poke;	///< ポケモン汎用構造体
	
	WAZATOOL_CALCMOVE	cm;		///< 汎用ワーク
	
} TWE_425_SYS;

static void We425_TCB(TCB_PTR tcb, void* work)
{
	TWE_425_SYS* wk = (TWE_425_SYS*)work;
	
	switch(wk->ts.seq){
	case 0:
		break;
	
	default:
		///< 解放処理
		WEEffect_TCB_Delete(wk->ts.wsp, tcb);
		WET_SAFE_RELEASE(wk);
		return;
	}
}

void WestSp_WE_425(WE_SYS_PTR we_sys)
{
	TWE_425_SYS* wk = WET_ALLOC_MEMORY(we_sys, TWE_425_SYS);
	
	WT_ToolSysInit(we_sys, &wk->ts);
	
	WEEffect_TCB_AddPriSet(wk->ts.wsp, We425_TCB, wk);
}
