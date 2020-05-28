//==============================================================================
/**
 * @file	wsp_100.c
 * @brief	簡単な説明を書く
 * @author	goto
 * @date	2006.02.23
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


///< No100 ～

// -----------------------------------------
//
//	□ 102 ものまね
//
// -----------------------------------------
typedef struct {

	TWE_TOOL_SYS		ts;		///< 技エフェクト汎用構造体
	TWE_POKE_SYS		poke;	///< ポケモン汎用構造体
	TWE_POKE_SYS		poke2[2];	///< ポケモン汎用構造体
	
	s16					dy;
	s16					poke_h;
	s16					base_y;
	
	WAZATOOL_CALCMOVE	cm;		///< 汎用ワーク
	
} TWE_102_SYS;

static void We102_TCB(TCB_PTR tcb, void* work)
{
	TWE_102_SYS* wk = (TWE_102_SYS*)work;
	
	switch(wk->ts.seq){
	case 0:
		if (WazaTool_CalcScaleRateEx(&wk->cm) == FALSE){
			CATS_ObjectEnableCap(wk->poke.cap, CATS_ENABLE_FALSE);
			CATS_ObjectEnableCap(wk->poke2[0].cap, CATS_ENABLE_FALSE);
			CATS_ObjectEnableCap(wk->poke2[0].cap, CATS_ENABLE_FALSE);
			
			WEEffect_TCB_Delete(wk->ts.wsp, tcb);
			WET_SAFE_RELEASE(wk);
			
			return;
		}
		{
			f32 x, y;
			
			WazaTool_CalcScaleRateToClactScale(&wk->cm, &x, &y);
			CATS_ObjectScaleSetCap(wk->poke.cap, x, y);
			
			WazaTool_PokeOffsetSetOAM(wk->poke.cap, wk->dy, wk->poke_h, wk->cm.work[4], WAZAEFF_OFS_MODE_BOTTOM);
		}
		break;
	
	default:
		///< 解放処理
		return;
	}

	CATS_ObjectUpdateCap(wk->poke.cap);
	CATS_ObjectUpdateCap(wk->poke2[0].cap);
	CATS_ObjectUpdateCap(wk->poke2[1].cap);
	CATS_Draw(wk->ts.poke_crp);
}

void WestSp_WE_102(WE_SYS_PTR we_sys)
{
	TWE_102_SYS* wk = WET_ALLOC_MEMORY(we_sys, TWE_102_SYS);
	
	WT_ToolSysInit(we_sys, &wk->ts);
	
	wk->poke.ssp = WeSysSoftSpritePointerGet(wk->ts.wsp, WeSysDFNoGet(wk->ts.wsp));
	wk->dy		 = SoftSpriteParaGet(wk->poke.ssp, SS_PARA_POS_Y);
	wk->base_y   = wk->dy;
	wk->poke_h	 = WeSysPokeOfsGet(wk->ts.wsp, WeSysDFNoGet(wk->ts.wsp));
	
	wk->poke.cap 	 = WeSysPokeCapGet(we_sys, 0);
	wk->poke2[0].cap = WeSysPokeCapGet(we_sys, 1);
	wk->poke2[1].cap = WeSysPokeCapGet(we_sys, 2);
	
	CATS_ObjectAffineSetCap(wk->poke.cap, CLACT_AFFINE_DOUBLE);
	CATS_ObjectBGPriSetCap(wk->poke.cap, 	 BT_3DPriorityGet(we_sys));
	CATS_ObjectBGPriSetCap(wk->poke2[0].cap, BT_3DPriorityGet(we_sys));
	CATS_ObjectBGPriSetCap(wk->poke2[1].cap, BT_3DPriorityGet(we_sys));
	
	{
		int type;
		
		type = WeSysClientTypeGet(wk->ts.wsp, WeSysDFNoGet(wk->ts.wsp));
				
		if (type == CLIENT_TYPE_B
		||	type == CLIENT_TYPE_C){
			CATS_ObjectPriSetCap(wk->poke.cap, 30);
			CATS_ObjectPriSetCap(wk->poke2[0].cap, 50);
			CATS_ObjectPriSetCap(wk->poke2[1].cap, 70);
		}
		else {
			CATS_ObjectPriSetCap(wk->poke.cap, 60);
			CATS_ObjectPriSetCap(wk->poke2[0].cap, 70);
			CATS_ObjectPriSetCap(wk->poke2[1].cap, 50);
		}
	}
	
	WazaTool_InitScaleRateEx(&wk->cm, 100, 20, 100, 20, 100, 10);
	
	WEEffect_TCB_AddPriSet(wk->ts.wsp, We102_TCB, wk);
}

#if 0
// -----------------------------------------
//
//	□ 102 ものまね
//
// -----------------------------------------
typedef struct {

	TWE_TOOL_SYS		ts;		///< 技エフェクト汎用構造体
	TWE_POKE_SYS		poke;	///< ポケモン汎用構造体
	
	s16					dy;
	s16					poke_h;
	s16					base_y;
	
	WAZATOOL_CALCMOVE	cm;		///< 汎用ワーク
	
} TWE_102_SYS;

static void We102_TCB(TCB_PTR tcb, void* work)
{
	TWE_102_SYS* wk = (TWE_102_SYS*)work;
	
	switch(wk->ts.seq){
	case 0:
		if (WazaTool_CalcScaleRateEx(&wk->cm) == FALSE){
			wk->ts.seq++;
		}
		SoftSpriteParaSet(wk->poke.ssp, SS_PARA_AFF_X, wk->cm.x);
		SoftSpriteParaSet(wk->poke.ssp, SS_PARA_AFF_Y, wk->cm.y);
		WazaTool_PokeOffsetSet(wk->poke.ssp, wk->dy, wk->poke_h, wk->cm.work[4], WAZAEFF_OFS_MODE_BOTTOM);
		break;
	
	case 1:
		SoftSpriteParaSet(wk->poke.ssp, SS_PARA_AFF_X, 0x100);
		SoftSpriteParaSet(wk->poke.ssp, SS_PARA_AFF_Y, 0x100);
		SoftSpriteParaSet(wk->poke.ssp, SS_PARA_POS_Y, wk->base_y);
		wk->ts.seq++;
		break;
	
	default:
		///< 解放処理
		WEEffect_TCB_Delete(wk->ts.wsp, tcb);
		WET_SAFE_RELEASE(wk);
		return;
	}

	CATS_ObjectUpdateCap(wk->poke.cap);
	CATS_Draw(wk->ts.poke_crp);
}

void WestSp_WE_102(WE_SYS_PTR we_sys)
{
	TWE_102_SYS* wk = WET_ALLOC_MEMORY(we_sys, TWE_102_SYS);
	
	WT_ToolSysInit(we_sys, &wk->ts);
	
	wk->poke.ssp = WeSysSoftSpritePointerGet(wk->ts.wsp, WeSysDFNoGet(wk->ts.wsp));
	wk->dy		 = SoftSpriteParaGet(wk->poke.ssp, SS_PARA_POS_Y);
	wk->base_y   = wk->dy;
	wk->poke_h	 = WeSysPokeOfsGet(wk->ts.wsp, WeSysDFNoGet(wk->ts.wsp));
	wk->poke.cap = WeSysPokeCapGet(we_sys, 0);
	CATS_ObjectBGPriSetCap(wk->poke.cap, BT_3DPriorityGet(we_sys)+1);
	
	WazaTool_InitScaleRateEx(&wk->cm, 100, 20, 100, 20, 100, 10);
	
	WEEffect_TCB_AddPriSet(wk->ts.wsp, We102_TCB, wk);
}
#endif









/* -------------------------------------------------------------
□□□□□□□□ テンプレート □□□□□□□□□□□□□□□□□

typedef struct {

	TWE_TOOL_SYS		ts;		///< 技エフェクト汎用構造体
	TWE_POKE_SYS		poke;	///< ポケモン汎用構造体
	
	WAZATOOL_CALCMOVE	cm;		///< 汎用ワーク
	
} TWE_102_SYS;

static void We102_TCB(TCB_PTR tcb, void* work)
{
	TWE_102_SYS* wk = (TWE_102_SYS*)work;
	
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

void WestSp_WE_102(WE_SYS_PTR we_sys)
{
	TWE_102_SYS* wk = WET_ALLOC_MEMORY(we_sys, TWE_102_SYS);
	
	WT_ToolSysInit(we_sys, &wk->ts);
	
	WEEffect_TCB_AddPriSet(wk->ts.wsp, We102_TCB, wk);
}

 -------------------------------------------------------------- */