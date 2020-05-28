//==============================================================================
/**
 * @file	wsp_sample.c
 * @brief	サポートサンプル
 * @author	goto
 * @date	2005.07.14(木)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================

// -----------------------------------------
//
//	include
//
// -----------------------------------------
#include "common.h"				///< 必須
#include "system/lib_pack.h"	///< 必須
#include "we_def.h"
#include "west_sp.h"			///< 必須
#include "wsp_sample.h"			///< xxx.cに対するxxx.hは必須

#include "wazatool.h"			///< 技エフェクト支援関数郡
#include "we_tool.h"			///< 

#include "ball_effect.h"
#include "system/arc_tool.h"				///< アーカイブ用
#include "system/arc_util.h"				///< アーカイブ用

// -----------------------------------------
//
//	■検索用
//
//		[ NORMAL_SAMPLE ]			関数呼び出し
//		[ EFFECT_TCB_ADD_SAMPLE ]	エフェクト用TCB登録
//		[ SOUND_TCB_ADD_SAMLE ]		サウンド用TCB登録
//		[ TCB_ADD_SAMPLE ]			従来のTCB登録
//
// -----------------------------------------



// =============================================================================
//
//
//	■[ NORMAL_SAMPLE ]		関数呼び出し方法
//
//
// =============================================================================
//--------------------------------------------------------------
/**
 * @brief	サンプル関数
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
typedef struct {
	BES_PTR bes;
} TSAMPLE;
void WestSp_Sample(WE_SYS_PTR we_sys)
{
	///< 単なる関数呼び出しです。
}






// =============================================================================
//
//
//	■[ EFFECT_TCB_ADD_SAMPLE ] エフェクトTCB登録方法
//
//
// =============================================================================
typedef struct {
	
	u8	seq;
	
	WE_SYS_PTR	ws;			///< ユーザーが用意するワークに必須のメンバ
	
} TEFFECT_TCB_SAMPLE;

// -------------------------------------------------------------
/*
 *	登録するTCB
 */
// -------------------------------------------------------------
static void Sample_EffectTCB(TCB_PTR tcb, void* work)
{
	TEFFECT_TCB_SAMPLE* wk = (TEFFECT_TCB_SAMPLE*)work;
	
	switch(wk->seq){
	case 0:
		///< とりあえず

		wk->seq++;
		break;

	case 1:
		///< 開放処理
		
		///< エフェクト用のTCBは、この関数を呼び出すことで破棄
		///< でないと、管理されているエフェクト管理数が減らない
		WEEffect_TCB_Delete(wk->ws, tcb);
		sys_FreeMemoryEz(wk);
		break;
	}
}

//--------------------------------------------------------------
/**
 * @brief	エフェクト用のTCB作成サンプル
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WestSp_SampleEffectTCB(WE_SYS_PTR we_sys)
{
	TEFFECT_TCB_SAMPLE* wk;
	
	wk = sys_AllocMemory(HEAPID_BATTLE, sizeof(TEFFECT_TCB_SAMPLE));
	
	wk->seq = 0;
	wk->ws	= we_sys;
	
	WEEffect_TCB_Add(wk->ws, Sample_EffectTCB, wk, 0x1000);
}





// =============================================================================
//
//
//	■[ SOUND_TCB_ADD_SAMPLE ] サウンドTCB登録方法
//
//
// =============================================================================
typedef struct {
	
	u8	seq;
	
	WE_SYS_PTR	ws;			///< ユーザーが用意するワークに必須のメンバ
	
} TSOUND_TCB_SAMPLE;

// -------------------------------------------------------------
/*
 *	登録するTCB
 */
// -------------------------------------------------------------
static void Sample_SoundTCB(TCB_PTR tcb, void* work)
{
	TSOUND_TCB_SAMPLE* wk = (TSOUND_TCB_SAMPLE*)work;
	
	switch(wk->seq){
	case 0:
		///< とりあえず

		wk->seq++;
		break;
	case 1:
		///< 開放処理
		
		///< サウンド用のTCBは、この関数を呼び出すことで破棄
		///< でないと、管理されているサウンド管理数が減らない
		WESound_TCB_Delete(wk->ws, tcb);
		sys_FreeMemoryEz(wk);
		break;
	}
}

//--------------------------------------------------------------
/**
 * @brief	サウンド用のTCB作成サンプル
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WestSp_SampleSoundTCB(WE_SYS_PTR we_sys)
{
	TSOUND_TCB_SAMPLE* wk;
	
	wk = sys_AllocMemory(HEAPID_BATTLE, sizeof(TSOUND_TCB_SAMPLE));
	
	wk->seq = 0;
	wk->ws	= we_sys;

	WESound_TCB_Add(wk->ws, Sample_SoundTCB, wk, 0x1000);
}



// =============================================================================
//
//
//	■[ TCB_ADD_SAMPLE ] 通常TCB登録方法
//
//
// =============================================================================
typedef struct {
	
	u8	seq;
	
	///< 通常のTCBは、WE-SYSに依存しないので受け取らなくても良い
	WE_SYS_PTR	ws;
	
} TTCB_SAMPLE;

// -------------------------------------------------------------
/*
 *	登録するTCB
 */
// -------------------------------------------------------------
static void Sample_TCB(TCB_PTR tcb, void* work)
{
	TTCB_SAMPLE* wk = (TTCB_SAMPLE*)work;
	
	switch(wk->seq){
	case 0:
		///< とりあえず

		wk->seq++;
		break;
	case 1:
		///< 破棄
		
		///< 従来のTCB開放処理でよい
		TCB_Delete(tcb);
		sys_FreeMemoryEz(wk);
		break;
	}
}

//--------------------------------------------------------------
/**
 * @brief	通常のTCB作成サンプル
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WestSp_SampleTCB(WE_SYS_PTR we_sys)
{
	TTCB_SAMPLE* wk;
	
	wk = sys_AllocMemory(HEAPID_BATTLE, sizeof(TTCB_SAMPLE));
	
	wk->seq = 0;
	
	///< 使わないので、メンバ自体も不要 無いと警告出るけど･･･
	wk->ws = we_sys;
	
	///< 従来のTCB登録方法で行う
	TCB_Add(Sample_TCB, wk, 0x1000);
}


// =============================================================================
//
//
//	■[ TCB_ADD_SAMPLE ] 通常TCB登録方法
//
//
#define TOM		(100)
// =============================================================================
typedef struct {
	
	u8	seq;
	
	///< 通常のTCBは、WE-SYSに依存しないので受け取らなくても良い
	WE_SYS_PTR	ws;
	
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	
	CATS_ACT_PTR cap;
	
	CATS_ACT_PTR caps[TOM];
	
	CLACT_WORK_PTR act[10];
	
} TTCB_CAT_SAMPLE;

// -------------------------------------------------------------
/*
 *	登録するTCB
 */
static int err_flag = 0;
// -------------------------------------------------------------
static void Sample_CAT_TCB(TCB_PTR tcb, void* work)
{
	TTCB_CAT_SAMPLE* wk = (TTCB_CAT_SAMPLE*)work;
	
	switch(wk->seq){
	case 0:
		CATS_ObjectUpdate(wk->caps[0]->act);
		CATS_ObjectUpdate(wk->caps[1]->act);
		CATS_ObjectUpdate(wk->caps[2]->act);
		
		CATS_ObjectPosMove(wk->caps[0]->act, 1, 0);
		CATS_ObjectPosMove(wk->caps[1]->act, -1, 0);
		CATS_ObjectPosMove(wk->caps[2]->act, 1, 1);
			
		CATS_Draw(wk->crp);
		break;
	case 1:
		{
			WE_SYS_PTR wsp = wk->ws;
			CATS_ActorPointerDelete_S(wk->cap);
			sys_FreeMemoryEz(wk);
			WEEffect_TCB_Delete(wsp, tcb);
		}
		break;
	}
}

//--------------------------------------------------------------
/**
 * @brief	通常のTCB作成サンプル
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WestSp_CAT_SampleTCB(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap)
{
	TTCB_CAT_SAMPLE* wk;
	TCATS_OBJECT_ADD_PARAM_S coap;
	
	wk = sys_AllocMemory(HEAPID_BATTLE, sizeof(TTCB_CAT_SAMPLE));
	
	GF_ASSERT(wk != NULL);
	
	wk->seq = 0;
	wk->csp = csp;
	wk->crp = crp;
	wk->cap = cap;

	wk->ws = we_sys;
	coap   = WeSysCoapGet(we_sys);

	wk->caps[0] = cap;
	{
		int i;
		
		for (i = 1; i < 3; i++){
			wk->caps[i] = CATS_ObjectAdd_S(wk->csp, wk->crp, &coap);
		}
	}

	WEEffect_TCB_Add(we_sys, Sample_CAT_TCB, wk, 0x1000);
}


