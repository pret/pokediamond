//==============================================================================
/**
 * @file	wsp_tool.c
 * @brief	技サポート関数郡
 * @author	goto
 * @date	2005.12.16(金)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================

#include "common.h"				///< 必須
#include "system/lib_pack.h"	///< 必須
#include "west_sp.h"			///< 必須
#include "wsp.h"				///< wsp.h

#include "wazatool.h"			///< 技エフェクト支援関数郡
#include "we_tool.h"			///< 

#include "ball_effect.h"
#include "system/arc_tool.h"	///< アーカイブ用
#include "system/arc_util.h"	///< アーカイブ用

#include "we_def.h"

//#include "system/spl.h"

static void SoftSpriteDefaultScaleSet(SOFT_SPRITE* ssp)
{
	SoftSpriteParaSet( ssp, SS_PARA_AFF_X, AFF_APPEAR_X_B );
	SoftSpriteParaSet( ssp, SS_PARA_AFF_Y, AFF_APPEAR_Y_B);
}

// -----------------------------------------
//
//
//		[ __WE_T01__ ]	
//
//
// -----------------------------------------
// ゆらシステム構造体
typedef struct {
	
	int num;	

	TWE_TOOL_SYS		ts;
	TWE_SHAKE_TOOL		st;
	
	TWE_POKE_SYS		poke[ WE_POKE_DATA_MAX ];

	WAZATOOL_CALCMOVE	cm;
	
} TWE_T01_SYS;

//--------------------------------------------------------------
/**
 * @brief	動作TCB
 *
 * @param	tcb	
 * @param	work	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WeT01_TCB(TCB_PTR tcb, void* work)
{
	int i;
	TWE_T01_SYS* wk = (TWE_T01_SYS*)work;

	switch(wk->ts.seq){
	case 0:
		///< ゆれ幅指定
		WazaTool_InitShake(&wk->cm, wk->st.x, wk->st.y, wk->st.w, wk->st.n);
		wk->ts.seq++;
		break;
		
	case 1:
		///< ゆれ
		if (WazaTool_CalcShake(&wk->cm) == FALSE){
			wk->ts.seq++;
		}
		else {
			if (IsBitCheck(wk->st.mode, WE_TOOL_SSP) == TRUE){
				for (i = 0; i < wk->num; i++){
					if (wk->poke[i].ssp == NULL){ continue; }
					
					SoftSpriteParaSet(wk->poke[i].ssp, SS_PARA_POS_X, wk->poke[i].p.x + wk->cm.x);
					SoftSpriteParaSet(wk->poke[i].ssp, SS_PARA_POS_Y, wk->poke[i].p.y + wk->cm.y);
				}
			}
			else if (IsBitCheck(wk->st.mode, WE_TOOL_CAP) == TRUE){
				for (i = 0; i < wk->num; i++){
					if (wk->poke[i].cap == NULL){ continue; }
					
					CATS_ObjectPosSetCap(wk->poke[i].cap, wk->poke[i].p.x + wk->cm.x, wk->poke[i].p.y + wk->cm.y);
					CATS_ObjectUpdateCap(wk->poke[i].cap);
				}
				CATS_Draw(wk->ts.poke_crp);
			}

			if (IsBitCheck(wk->st.mode, WE_TOOL_BG) == TRUE){
				GF_BGL_ScrollSet(wk->ts.bgl, BATTLE_FRAME_BACKGROUND, GF_BGL_SCROLL_X_SET, wk->cm.x);
			}
		}
		break;
		
	default:
		WEEffect_TCB_Delete(wk->ts.wsp, tcb);
		sys_FreeMemoryEz(wk);
		break;
	}
}

void WestSp_WE_T01(WE_SYS_PTR we_sys)
{
	TWE_T01_SYS* wk = WET_ALLOC_MEMORY(we_sys, TWE_T01_SYS);
	
	int i;

	WT_ToolSysInit(we_sys, &wk->ts);
	
	wk->st.x	= WeSysGPWorkGet(we_sys, 0);
	wk->st.y	= WeSysGPWorkGet(we_sys, 1);
	wk->st.w	= WeSysGPWorkGet(we_sys, 2);
	wk->st.n	= WeSysGPWorkGet(we_sys, 3);
	wk->st.mode = WeSysGPWorkGet(we_sys, 4);
	
	if (IsBitCheck(wk->st.mode, WE_TOOL_SSP) == TRUE){
		WT_SSPointerGet(we_sys, wk->st.mode, &(wk->poke[0]), &wk->num);
	}
	else if (IsBitCheck(wk->st.mode, WE_TOOL_CAP) == TRUE){
		WT_CAPointerGet(we_sys, wk->st.mode, &(wk->poke[0]), &wk->num);
	}
	WEEffect_TCB_AddPriSet(wk->ts.wsp, WeT01_TCB, wk);
}

// -----------------------------------------
//
//
//		[ __WE_T02__ ]	
//
//
// -----------------------------------------
// 背景うごかしシステム構造体 ※波乗り専用になりそうだ。
typedef struct {
	int rev;
	int fade_flag;
	u16	bld_def;
	s16 pos_x;
	s16 pos_y;
	s16 spd_x;
	s16 spd_y;
	
	u16 timer;
	u16	timer_wait;
	
	u16 ev1;
	u16 ev2;

	TWE_TOOL_SYS		ts;
	TWE_SHAKE_TOOL		st;
	
	TWE_POKE_SYS		poke[ WE_POKE_DATA_MAX ];

	WAZATOOL_CALCMOVE	cm;
	
} TWE_T02_SYS;

#define WET02_STOP_Y_1		(512)
#define WET02_STOP_Y_2		(-412)
#define WET02_START_Y_OFS	(128)

//--------------------------------------------------------------
/**
 * @brief	動作TCB
 *
 * @param	tcb	
 * @param	work	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WeT02_TCB(TCB_PTR tcb, void* work)
{
	TWE_T02_SYS* wk = (TWE_T02_SYS*)work;

	switch(wk->ts.seq){
	case 0:
		G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG2,
						 GX_BLEND_PLANEMASK_BD  | GX_BLEND_PLANEMASK_OBJ |
						 GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG3,
						 wk->ev1, wk->ev2);
		GF_BGL_VisibleSet(BATTLE_FRAME_EFFECT, VISIBLE_ON);
		wk->ts.seq++;
		
	case 1:
		{
			int ev_sw = 0;
			if (wk->ev1 < wk->bld_def - 2){
				wk->ev1 += 2;
			}
			else {
				ev_sw++;
			}
			if (wk->ev2 > 7 + 2){//wk->bld_def + 2){
				wk->ev2 -= 2;
			}
			else {
				ev_sw++;
			}
			if (ev_sw == 2){
				wk->ev1 = wk->bld_def;
				wk->ev2 = 7;//wk->bld_def;
				wk->ts.seq++;
			}
			G2_ChangeBlendAlpha(wk->ev1, wk->ev2);
		}
		break;
	case 2:
		if (wk->fade_flag){
			wk->ts.seq++;
		}
		break;
	case 3:
		{
			int ev_sw = 0;
			if (wk->ev1 > 2){
				wk->ev1 -= 2;
			}
			else {
				ev_sw++;
			}
			if (wk->ev2 < 31-2){
				wk->ev2 += 2;
			}
			else {
				ev_sw++;
			}
			if (ev_sw == 2){
				wk->ev1 = 0;
				wk->ev2 = 31;
				wk->ts.seq++;
			}
			G2_ChangeBlendAlpha(wk->ev1, wk->ev2);
		}
		break;
	default:
		GF_BGL_VisibleSet(BATTLE_FRAME_EFFECT, VISIBLE_OFF);
		WEEffect_TCB_Delete(wk->ts.wsp, tcb);
		sys_FreeMemoryEz(wk);
		return;
	}

	if ((wk->spd_y > 0 && wk->pos_y >= WET02_STOP_Y_1)
	||  (wk->spd_y < 0 && wk->pos_y <= WET02_STOP_Y_2)){
		wk->fade_flag = 1;
	}

	wk->pos_x += wk->spd_x;
	wk->pos_y += wk->spd_y;
	
	if (wk->timer < wk->timer_wait){
		if (wk->spd_y < 0){
			wk->spd_y++;
		}
		else {
			wk->spd_y = 0;
		}
		if (wk->spd_x < 0){
			wk->spd_x++;
		}
		else {
			wk->spd_x = 0;
		}
		wk->timer_wait = 0;
	}
	else {
		wk->timer_wait++;
	}
		
	GF_BGL_ScrollSet(wk->ts.bgl, BATTLE_FRAME_EFFECT, GF_BGL_SCROLL_X_SET, wk->pos_x);
	GF_BGL_ScrollSet(wk->ts.bgl, BATTLE_FRAME_EFFECT, GF_BGL_SCROLL_Y_SET, wk->pos_y);
}


//--------------------------------------------------------------
/**
 * @brief	呼び出し関数
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WestSp_WE_T02(WE_SYS_PTR we_sys)
{
	TWE_T02_SYS* wk = WET_ALLOC_MEMORY(we_sys, TWE_T02_SYS);
	
	int i;

	WT_ToolSysInit(we_sys, &wk->ts);
	
	wk->pos_x	= WeSysGPWorkGet(we_sys, 1);
	wk->pos_y	= WeSysGPWorkGet(we_sys, 2);
	wk->spd_x	= WeSysGPWorkGet(we_sys, 3);
	wk->spd_y	= WeSysGPWorkGet(we_sys, 4);
	wk->rev		= WeSysGPWorkGet(we_sys, 5);
	wk->bld_def	= WeSysGPWorkGet(we_sys, 6);
	wk->timer	= WeSysGPWorkGet(we_sys, 7);
	wk->timer_wait = 0;
	
	if (wk->rev != 0
	&&	WET_SideCheck(we_sys, WeSysATNoGet(we_sys)) == SIDE_ENEMY){
		wk->pos_x	*= -1;
		wk->pos_y	*= -1;
		wk->spd_x	*= -1;
		wk->spd_y	*= -1;
		wk->pos_y -= ((WET02_START_Y_OFS / 3) * 2);
	}
	else {
		wk->pos_y += ((WET02_START_Y_OFS / 3) * 2);
	}
	
	if (WES_ContestFlag_Get(we_sys) == TRUE){
		wk->spd_x	*= -1;
	}
	
	wk->ev1 = 0;
	wk->ev2	= 31;
	wk->fade_flag = 0;
	
	GF_BGL_VisibleSet(BATTLE_FRAME_EFFECT, VISIBLE_OFF);
	{
		int arc = WeSysGPWorkGet(we_sys, 0);
		ArcUtil_BgCharSet(WE_HAIKEI_ARC,
						  WeSysHaikeiDataIDGet(arc, 0),
						  wk->ts.bgl,
						  BATTLE_FRAME_EFFECT, 0, 0, 1, WeSysHeapAreaGet(we_sys));

		PaletteWorkSet_Arc(wk->ts.pfd,
						   WE_HAIKEI_ARC,
						   WeSysHaikeiDataIDGet(arc, 1),
						   WeSysHeapAreaGet(we_sys), FADE_MAIN_BG, 0x20, WEDEF_BG_DATA_COL_POS);
						   
		GF_BGL_ScrClear(wk->ts.bgl, BATTLE_FRAME_EFFECT);
		
		{
			int idx = 2;
			
			if (WES_ContestFlag_Get(we_sys) == TRUE){
				idx = 4;
			}
			else if (WET_SideCheck(we_sys, WeSysATNoGet(we_sys)) == SIDE_ENEMY){
				idx = 3;
			}
			ArcUtil_ScrnSet(WE_HAIKEI_ARC,
							WeSysHaikeiDataIDGet(arc, idx),
							wk->ts.bgl,
							BATTLE_FRAME_EFFECT, 0, 0, 1, WeSysHeapAreaGet(we_sys));
		}
	}
	GF_BGL_ScrollSet(wk->ts.bgl, BATTLE_FRAME_EFFECT, GF_BGL_SCROLL_X_SET, wk->pos_x);
	GF_BGL_ScrollSet(wk->ts.bgl, BATTLE_FRAME_EFFECT, GF_BGL_SCROLL_Y_SET, wk->pos_y);
	
	WEEffect_TCB_AddPriSet(wk->ts.wsp, WeT02_TCB, wk);
}

// -----------------------------------------
//
//
//		[ __WE_T22__ ]	
//
//
// -----------------------------------------
// 背景うごかしシステム構造体 ※波乗り専用になりそうだ。
typedef struct {
	int rev;
	int fade_flag;
	u16	bld_def;
	s16 pos_x;
	s16 pos_y;
	s16 spd_x;
	s16 spd_y;
	
	u16 timer;
	u16	timer_wait;
	
	u16 ev1;
	u16 ev2;

	TWE_TOOL_SYS		ts;
	TWE_SHAKE_TOOL		st;
	
	TWE_POKE_SYS		poke[ WE_POKE_DATA_MAX ];

	WAZATOOL_CALCMOVE	cm;
	
} TWE_T22_SYS;

#define WET22_STOP_Y_1		(512)
#define WET22_STOP_Y_2		(-412)
#define WET22_START_Y_OFS	(128)

//--------------------------------------------------------------
/**
 * @brief	動作TCB
 *
 * @param	tcb	
 * @param	work	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WeT22_TCB(TCB_PTR tcb, void* work)
{
	TWE_T22_SYS* wk = (TWE_T22_SYS*)work;

	switch(wk->ts.seq){
	case 0:
		G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG2,
						 GX_BLEND_PLANEMASK_BD  | GX_BLEND_PLANEMASK_OBJ |
						 GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG3,
						 wk->ev1, wk->ev2);
		GF_BGL_VisibleSet(BATTLE_FRAME_EFFECT, VISIBLE_ON);
		wk->ts.seq++;
		
	case 1:
		{
			int ev_sw = 0;
			if (wk->ev1 < 16){
				wk->ev1 += 2;
			}
			else {
				ev_sw++;
			}
			if (wk->ev2 > 4){
				wk->ev2 -= 2;
			}
			else {
				ev_sw++;
			}
			if (ev_sw == 2){
				wk->ev1 =16;
				wk->ev2 = 4;
				wk->ts.seq++;
			}
			G2_ChangeBlendAlpha(wk->ev1, wk->ev2);
		}
		break;
	case 2:
		if (wk->fade_flag){
			wk->ts.seq++;
		}
		break;
	case 3:
		{
			int ev_sw = 0;
			if (wk->ev1 > 2){
				wk->ev1 -= 2;
			}
			else {
				ev_sw++;
			}
			if (wk->ev2 < 16){
				wk->ev2 += 2;
			}
			else {
				ev_sw++;
			}
			if (ev_sw == 2){
				wk->ev1 = 0;
				wk->ev2 = 31;
				wk->ts.seq++;
			}
			G2_ChangeBlendAlpha(wk->ev1, wk->ev2);
		}
		break;
	default:
		GF_BGL_VisibleSet(BATTLE_FRAME_EFFECT, VISIBLE_OFF);
		WEEffect_TCB_Delete(wk->ts.wsp, tcb);
		sys_FreeMemoryEz(wk);
		return;
	}

	if ((wk->spd_y > 0 && wk->pos_y >= WET22_STOP_Y_1)
	||  (wk->spd_y < 0 && wk->pos_y <= WET22_STOP_Y_2)){
		wk->fade_flag = 1;
	}

	wk->pos_x += wk->spd_x;
	wk->pos_y += wk->spd_y;
	
	if (wk->timer < wk->timer_wait){
		if (wk->spd_y < 0){
			wk->spd_y++;
		}
		else {
			wk->spd_y = 0;
		}
		if (wk->spd_x < 0){
			wk->spd_x++;
		}
		else {
			wk->spd_x = 0;
		}
		wk->timer_wait = 0;
	}
	else {
		wk->timer_wait++;
	}
		
	GF_BGL_ScrollSet(wk->ts.bgl, BATTLE_FRAME_EFFECT, GF_BGL_SCROLL_X_SET, wk->pos_x);
	GF_BGL_ScrollSet(wk->ts.bgl, BATTLE_FRAME_EFFECT, GF_BGL_SCROLL_Y_SET, wk->pos_y);
}


//--------------------------------------------------------------
/**
 * @brief	呼び出し関数
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WestSp_WE_T22(WE_SYS_PTR we_sys)
{
	TWE_T22_SYS* wk = WET_ALLOC_MEMORY(we_sys, TWE_T22_SYS);
	
	int i;

	WT_ToolSysInit(we_sys, &wk->ts);
	
	wk->pos_x	= WeSysGPWorkGet(we_sys, 1);
	wk->pos_y	= WeSysGPWorkGet(we_sys, 2);
	wk->spd_x	= WeSysGPWorkGet(we_sys, 3);
	wk->spd_y	= WeSysGPWorkGet(we_sys, 4);
	wk->rev		= WeSysGPWorkGet(we_sys, 5);
	wk->bld_def	= WeSysGPWorkGet(we_sys, 6);
	wk->timer	= WeSysGPWorkGet(we_sys, 7);
	wk->timer_wait = 0;
	
	if (wk->rev != 0
	&&	WET_SideCheck(we_sys, WeSysATNoGet(we_sys)) == SIDE_ENEMY){
		wk->pos_x	*= -1;
		wk->pos_y	*= -1;
		wk->spd_x	*= -1;
		wk->spd_y	*= -1;
		wk->pos_y -= ((WET22_START_Y_OFS / 3) * 2);
	}
	else {
		wk->pos_y += ((WET22_START_Y_OFS / 3) * 2);
	}
	
	if (WES_ContestFlag_Get(we_sys) == TRUE){
		wk->spd_x	*= -1;
	}

	wk->ev1 =  4;	///< 0
	wk->ev2	= 16;	///< 31
	wk->ev1 =  0;
	wk->ev2	= 16;
	wk->fade_flag = 0;
	
	GF_BGL_VisibleSet(BATTLE_FRAME_EFFECT, VISIBLE_OFF);
	{
		int arc = WeSysGPWorkGet(we_sys, 0);
		ArcUtil_BgCharSet(WE_HAIKEI_ARC,
						  WeSysHaikeiDataIDGet(arc, 0),
						  wk->ts.bgl,
						  BATTLE_FRAME_EFFECT, 0, 0, 1, WeSysHeapAreaGet(we_sys));

		PaletteWorkSet_Arc(wk->ts.pfd,
						   WE_HAIKEI_ARC,
						   WeSysHaikeiDataIDGet(arc, 1),
						   WeSysHeapAreaGet(we_sys), FADE_MAIN_BG, 0x20, WEDEF_BG_DATA_COL_POS);
						   
		GF_BGL_ScrClear(wk->ts.bgl, BATTLE_FRAME_EFFECT);
		
		{
			int idx = 2;
			
			if (WES_ContestFlag_Get(we_sys) == TRUE){
				idx = 4;
			}
			else if (WET_SideCheck(we_sys, WeSysATNoGet(we_sys)) == SIDE_ENEMY){
				idx = 3;
			}
			ArcUtil_ScrnSet(WE_HAIKEI_ARC,
							WeSysHaikeiDataIDGet(arc, idx),
							wk->ts.bgl,
							BATTLE_FRAME_EFFECT, 0, 0, 1, WeSysHeapAreaGet(we_sys));
		}
	}
	GF_BGL_ScrollSet(wk->ts.bgl, BATTLE_FRAME_EFFECT, GF_BGL_SCROLL_X_SET, wk->pos_x);
	GF_BGL_ScrollSet(wk->ts.bgl, BATTLE_FRAME_EFFECT, GF_BGL_SCROLL_Y_SET, wk->pos_y);
	
	WEEffect_TCB_AddPriSet(wk->ts.wsp, WeT22_TCB, wk);
}

//-----------------------------------------------------------------------------
/**
 *		つつく時のポケモン回転タスク
 */
//-----------------------------------------------------------------------------
//シーケンス
enum{
	WAZATOOL_POKE_ROTA00_MAIN = 0,
	WAZATOOL_POKE_ROTA00_REMOVE,
	WAZATOOL_POKE_ROTA00_END,
};
// ワーク
typedef struct{
	u8	seq;
	WE_SYS_PTR	ws;			///< ユーザーが用意するワークに必須のメンバ
	
	// ソフトスプライトデータ
	SOFT_SPRITE* ss;

	// 回転計算用ワーク
	WAZATOOL_CALCMOVE_ONE	calc_rota;
	s32	start;	// 開始回転角度
	int sync;	// 保存
	
	s16	cx;
	s16	cy;

} TEFFECT_TCB_POKE_ROTA00;

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ポケモンを少し回転させる
 *
 *	@param	tcb		tcbワーク
 *	@param	work	ワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void EffectTCB_PokeRota00(TCB_PTR tcb, void* work)
{
	TEFFECT_TCB_POKE_ROTA00* wk = work;

	switch( wk->seq ){
	case WAZATOOL_POKE_ROTA00_MAIN:
	case WAZATOOL_POKE_ROTA00_REMOVE:
		if( WazaTool_CalcMoveOne( &wk->calc_rota ) == TRUE ){
			
			// ポケモンの回転パラメータ設定
			// オーバーしている可能性もあるのでu16でキャストして渡す
			SoftSpriteParaSet( wk->ss, SS_PARA_ROT_Z, (u16)wk->calc_rota.num );
		}else{
			
			// 元に戻すタスク
			WazaTool_InitMoveOneSync( &wk->calc_rota, wk->calc_rota.num, wk->start, wk->sync );
			wk->seq++;
		}
		break;

	case WAZATOOL_POKE_ROTA00_END:
		// 回転座標を設定
		SoftSpriteParaSet( wk->ss, SS_PARA_ROT_CX, 0 );
		SoftSpriteParaSet( wk->ss, SS_PARA_ROT_CY, 0 );

		// 回転角初期化
		SoftSpriteParaSet( wk->ss, SS_PARA_ROT_Z, 0 );

		// このTCBを破棄
		WEEffect_TCB_Delete(wk->ws, tcb);
		sys_FreeMemoryEz(wk);
		break;
	}
}

//--------------------------------------------------------------
/**
 * @brief	ポケモンがちょっと回転するエフェクトタスク生成
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 * つつくで使用しています。
 *
 * we_sys内の引数を使用します。
 * wk[0]	開始角度	(0～65535)	65535で360度
 * wk[1]	終了角度	(0～65535)	65535で360度
 * wk[2]	シンク数	(マイナス不可能)
 * 
 */
//--------------------------------------------------------------
void WestSp_EffectTCBPokeRota00(WE_SYS_PTR we_sys)
{
	TEFFECT_TCB_POKE_ROTA00* wk;
	int r_vec;	// 回転方向単位ベクトル
	int type;
	int clno;
	
	wk = sys_AllocMemory(WeSysHeapAreaGet(we_sys), sizeof(TEFFECT_TCB_POKE_ROTA00));
	
	wk->seq = 0;
	wk->ws	= we_sys;

	wk->sync	= WeSysGPWorkGet(we_sys, 2);	// シンク数
	wk->start	= WeSysGPWorkGet(we_sys, 0);	// 開始回転角

	type = WeSysGPWorkGet(we_sys, 3);	///< 対象
	
	{
		if (type == 0
		||	type == 2){
			clno = WeSysDFNoGet(wk->ws);
		}
		else {
			clno = WeSysATNoGet(wk->ws);
		}
	}

	// 回転データの初期化を行う
	//	パラメータを使用する
	WazaTool_InitMoveOneSync( &wk->calc_rota,
			wk->start,
			WeSysGPWorkGet(we_sys, 1),
			wk->sync );
	
	// 回転方向設定
	// 回転方向ベクトル取得
	r_vec = WazaTool_VecChangeX( we_sys, clno );

	// 回転方向ベクトルを掛ける
	wk->calc_rota.work[1] *= r_vec;
	
	if (type == 2){
		r_vec *= -1;
	}

	// スプライトデータ取得
	wk->ss = WeSysSoftSpritePointerGet( wk->ws, clno );

	if (WeSysGPWorkGet(we_sys, 3) == 1){
		wk->cx		= WeSysGPWorkGet(we_sys, 4);	// 開始回転角
		wk->cy		= WeSysGPWorkGet(we_sys, 5);	// 開始回転角
	}
	else {
		wk->cx		= (SOFT_SPRITE_SIZE_X / 2) * r_vec;
		wk->cy		= (SOFT_SPRITE_SIZE_Y / 2);
	}

	// 回転座標を設定
	SoftSpriteParaSet( wk->ss, SS_PARA_ROT_CX, wk->cx );
	SoftSpriteParaSet( wk->ss, SS_PARA_ROT_CY, wk->cy );

	WEEffect_TCB_AddPriSet(wk->ws, EffectTCB_PokeRota00, wk);
}


//-------------------------------------
//	
//	じごくぐるま
//	(くるくる回転させる)
//	
//=====================================
typedef struct{
	WE_SYS_PTR	we_sys;

	WAZATOOL_CALCMOVE wtc;
	SOFT_SPRITE*	ssp;
	s16	x;
	s16 y;
} TWE_066_SYS;


//----------------------------------------------------------------------------
/**
 *	@brief	じごくぐるまTCB
 *
 *	@param	tcb
 *	@param	work
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void We066_TCB(TCB_PTR tcb, void* work)
{
	TWE_066_SYS* wk = work;

	// 動作が完全に終わるまで待って終了
	// 動作部
	if( WazaTool_CalcAndReflectRotaFxSsp( &wk->wtc, wk->x, wk->y, wk->ssp ) == FALSE ){

		// 元座標を設定
		SoftSpriteParaSet( wk->ssp, SS_PARA_POS_X, wk->x );
		SoftSpriteParaSet( wk->ssp, SS_PARA_POS_Y, wk->y + (WAZATOOL_DEF_ROTA_W_Y >> FX32_SHIFT) );

		// 回転角初期化
		SoftSpriteParaSet( wk->ssp, SS_PARA_ROT_Z, 0 );

		// 終了
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		sys_FreeMemoryEz(wk);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	じごくぐるま	
 *
 *	@param	we_sys	技エフェクトシステムワーク
 *
 *	@return	none
 *
 * we_sys.work[0]	回転数
 * we_sys.work[1]	１回転シンク数
 * we_sys.work[2]	対象ポケモン	（単体）
 *
 */
//-----------------------------------------------------------------------------
void WestSp_WE_066( WE_SYS_PTR we_sys )
{
	TWE_066_SYS* wk;
	
	wk = sys_AllocMemory(WeSysHeapAreaGet(we_sys), sizeof(TWE_066_SYS));

	wk->we_sys	= we_sys;
	
	// ポケモン　動作データ作成
	WazaTool_MakeDefRota(
			&wk->wtc,
			WeSysGPWorkGet(we_sys, 0),
			WeSysGPWorkGet(we_sys, 1) );

	// ポケモンスプライトデータ取得
	switch( WeSysGPWorkGet(we_sys, 2) ){
	case WE_TOOL_M1:
		wk->ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysATNoGet(we_sys) );
		// 回転方向を設定
		// 攻撃側の回転方向 逆ベクトルにする
		wk->wtc.work[2] *= -1;
		break;

	case WE_TOOL_M2:
		wk->ssp = WeSysSoftSpritePointerGet(wk->we_sys, WET_AllySideClientNoGet(wk->we_sys, WeSysATNoGet(wk->we_sys)));

		// 回転方向を設定
		// 攻撃側の回転方向 逆ベクトルにする
		wk->wtc.work[2] *= -1;
		break;
	
	case WE_TOOL_E1:
		wk->ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysDFNoGet(we_sys) );
		break;

	case WE_TOOL_E2:
		wk->ssp = WeSysSoftSpritePointerGet(wk->we_sys, WET_AllySideClientNoGet(wk->we_sys, WeSysDFNoGet(wk->we_sys)));
		break;

	default:
		GF_ASSERT_MSG( 0, "複数のポケモンを指定することが出来ません。" );
		break;
	}

	wk->x = SoftSpriteParaGet( wk->ssp, SS_PARA_POS_X );
	wk->y = SoftSpriteParaGet( wk->ssp, SS_PARA_POS_Y );
	// 座標を回転のY幅分上に補正
	wk->y -= WAZATOOL_DEF_ROTA_W_Y >> FX32_SHIFT;


	WEEffect_TCB_AddPriSet(wk->we_sys, We066_TCB, wk);
}


//-------------------------------------
//	
//	いばる
//		などで使用する
//		キレマークの表示
//	
//=====================================
// きれまーく
enum{
	WE207_KIRESYS_MOVE,
	WE207_KIRESYS_END,
};
enum{
	WE207_KIRE_START,
	WE207_KIRE_1DRAW,
	WE207_KIRE_WAIT,
	WE207_KIRE_2DRAW,
	WE207_KIRE_END
};

#define WE207_SCALE_CAP_S		( 10 )
#define WE207_SCALE_CAP_D		( 10 )
#define WE207_SCALE_CAP_E		( 14 )
#define WE207_SCALE_CAP_SYNC	( 4 )
#define WE207_SCALERET_CAP_S		( 14 )
#define WE207_SCALERET_CAP_D		( 10 )
#define WE207_SCALERET_CAP_E		( 12 )
#define WE207_SCALERET_CAP_SYNC		( 2 )

#define WE207_CAP_OFS_X		( 24 )
#define WE207_CAP_OFS_Y		( 16 )
#define WE207_CAP_OFS_Y2	( 24 )

#define WE207_SCALE_CAP_WAIT	( 4 )

typedef struct {
	WE_SYS_PTR	we_sys;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	int seq;
	int wait;
	
	// きれまーく
	CATS_ACT_PTR cap;
	WAZATOOL_CALCMOVE cap_scale;
	int cap_vec_x;
	int cap_scale_flg;
	int cap_wait;
	int cap_seq;
	s16 df_x;
	s16 df_y;

} TWE207_SYS_SUB;

static void We207_InitCapObj(  TWE207_SYS_SUB* wk, s16 x, s16 y  )
{
	CATS_ObjectEnableCap( wk->cap, TRUE );
	CATS_ObjectPosSetCap( wk->cap, x, y );
	wk->cap_scale_flg = 0;
		
	WazaTool_InitScaleRate(
			&wk->cap_scale,
			WE207_SCALE_CAP_S,
			WE207_SCALE_CAP_D,
			WE207_SCALE_CAP_E,
			WE207_SCALE_CAP_SYNC
			);
}

static BOOL We207_MoveCapObj( TWE207_SYS_SUB* wk )
{
	if( WazaTool_CalcAndReflectScaleRateCap( &wk->cap_scale, wk->cap ) == FALSE ){
		
		if( wk->cap_scale_flg ){
			CATS_ObjectEnableCap( wk->cap, FALSE );
			return TRUE;
		}else{
			wk->cap_scale_flg = 1;

			WazaTool_InitScaleRate(
					&wk->cap_scale,
					WE207_SCALERET_CAP_S,
					WE207_SCALERET_CAP_D,
					WE207_SCALERET_CAP_E,
					WE207_SCALERET_CAP_SYNC
					);

		}
	}

	return FALSE;
}

static BOOL We207_CapMove( TWE207_SYS_SUB* wk )
{
	BOOL ret = FALSE;
	
	switch( wk->cap_seq ){
	case WE207_KIRE_START:
		We207_InitCapObj( wk, wk->df_x + (WE207_CAP_OFS_X * wk->cap_vec_x), wk->df_y - WE207_CAP_OFS_Y );
		wk->cap_seq++;
		break;

	case WE207_KIRE_1DRAW:
		if( We207_MoveCapObj( wk ) ){
			wk->cap_seq++;
		}
		break;

	case WE207_KIRE_WAIT:
		wk->cap_wait --;
		if( wk->cap_wait < 0 ){
			wk->cap_seq++;
			We207_InitCapObj( wk, wk->df_x - (WE207_CAP_OFS_X * wk->cap_vec_x), wk->df_y - WE207_CAP_OFS_Y2 );
		}
		break;
		
	case WE207_KIRE_2DRAW:
		if( We207_MoveCapObj( wk ) ){
			wk->cap_seq++;
		}
		break;

	case WE207_KIRE_END:
		ret = TRUE;
		break;
	}

	return ret;
}

static void We207_TCB_SUB( TCB_PTR tcb, void* work )
{
	TWE207_SYS_SUB* wk = work;
	
	switch( wk->seq ){
	case WE207_KIRESYS_MOVE:
		if( We207_CapMove( wk ) ){
			wk->seq++;
		}
		break;

	case WE207_KIRESYS_END:
		CATS_ActorPointerDelete_S(wk->cap);
		// 終了
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		sys_FreeMemoryEz(wk);
		return;
	}

	// OAM描画
	CATS_Draw(wk->crp);	
}

//----------------------------------------------------------------------------
/**
 * @brief	キレマーク用タスク登録
 *
 *	@param	we_sys	技エフェクトシステムワーク
 *	@param	csp		セルアクターツールシステム
 *	@param	crp		セルアクターリソースシステム
 *	@param	cap		セルアクターツールオブジェ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WestSp_CAT_WE_207_SUB(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap)
{
	TWE207_SYS_SUB* wk;
	SOFT_SPRITE* df_ssp;

	wk = WET_ALLOC_MEMORY(we_sys, TWE207_SYS_SUB);
	wk->we_sys	= we_sys;
	wk->csp		= csp;
	wk->crp		= crp;

	// きれまーく
	wk->cap = cap;
	CATS_ObjectPriSetCap( wk->cap, WAZAEFF_ACT_SOFTPRI );
	CATS_ObjectBGPriSetCap( wk->cap, WAZAEFF_ACT_BGPRI );
	CATS_ObjectAffineSetCap( wk->cap, CLACT_AFFINE_DOUBLE );
	CATS_ObjectEnableCap( wk->cap, FALSE );
	wk->cap_wait = WE207_SCALE_CAP_WAIT;
	wk->cap_vec_x = WazaTool_VecChangeX( wk->we_sys, WeSysATNoGet(wk->we_sys) );
	

	df_ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysDFNoGet(we_sys) );
	wk->df_x = SoftSpriteParaGet( df_ssp, SS_PARA_POS_X );
	wk->df_y = SoftSpriteParaGet( df_ssp, SS_PARA_POS_Y );

	WEEffect_TCB_AddPriSet(wk->we_sys, We207_TCB_SUB, wk);
}



//-------------------------------------
//	
//	背景パレットフェード関数
//	
//=====================================
typedef struct {
	WE_SYS_PTR we_sys;
	PALETTE_FADE_PTR pfd;
} TWEBG_PAL_FADE;

#define TWEBG_BG_PAL_BIT	( WEDEF_BACKGROUND_PAL )
#define TWEBG_EF1_PAL_BIT	( 1 << BATTLE_PAL_EFF_0 )
#define TWEBG_EF2_PAL_BIT	( 1 << BATTLE_PAL_EFF_1 )

static void WeBGPalFade_TCB( TCB_PTR tcb, void* work )
{
	TWEBG_PAL_FADE* wk = work;
	
	if (PaletteFadeCheck(wk->pfd) == 0){
		sys_FreeMemoryEz(wk);
		WEEffect_TCB_Delete(wk->we_sys, tcb);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	背景パレットフェード設定
 *
 *	@param	we_sys		技エフェクトシステム
 *
 *	@return	none
 *
 * we_sys.work[0]	0=背景 1=エフェクト1(pokemon)  2=エフェクト2(other)
 * we_sys.work[1]	wait	計算待ち時間
 * we_sys.work[2]	start	初期濃度
 * we_sys.work[3]	end		最終濃度
 * we_sys.work[4]	color	変更後の色
 *
 */
//-----------------------------------------------------------------------------
void WestSp_WE_HaikeiPalFade(WE_SYS_PTR we_sys)
{
	TWEBG_PAL_FADE* wk;
	u16 fade_bit;

	wk = WET_ALLOC_MEMORY(we_sys, TWEBG_PAL_FADE);
	wk->we_sys	= we_sys;
	wk->pfd		= WeSysPFDGet(wk->we_sys);
	
	// ふぇーどビット取得
	switch( WeSysGPWorkGet(we_sys, 0) ){
	case 0:
		fade_bit = BT_HaikeiFadeBit(we_sys);
		//	fade_bit = TWEBG_BG_PAL_BIT;
		break;
		
	case 1:
		fade_bit = TWEBG_EF1_PAL_BIT;
		break;
	
	case 2:
		fade_bit = TWEBG_EF2_PAL_BIT;
		break;

	default:
		GF_ASSERT_MSG( 0, "color=0,1,2" );
		break;
	}
	
	PaletteFadeReq(wk->pfd, PF_BIT_MAIN_BG, fade_bit,
			WeSysGPWorkGet(we_sys, 1),
			WeSysGPWorkGet(we_sys, 2),
			WeSysGPWorkGet(we_sys, 3),
			WeSysGPWorkGet(we_sys, 4)
			);
	
	WEEffect_TCB_AddPriSet(wk->we_sys, WeBGPalFade_TCB, wk);
}

// SOFT_SPRITE パレットフェード点滅
enum{
	TWE_SSP_POKE_PAL_FADEOUT_INIT,
	TWE_SSP_POKE_PAL_FADEOUT_MOVE,
	TWE_SSP_POKE_PAL_FADE_WAIT,
	TWE_SSP_POKE_PAL_FADEIN_INIT,
	TWE_SSP_POKE_PAL_FADEIN_MOVE,
	TWE_SSP_POKE_PAL_FADE_END,
};
typedef struct {
	WE_SYS_PTR we_sys;
	SOFT_SPRITE* ssp;
	int seq;
	int count;
	int fade_wait;
	int rgb;
	int evy_max;
	
	int wait;
} TWE326_SSP_POKE_PAL_FADE;

static void WeSSPPokePalFade_TCB( TCB_PTR tcb, void* work )
{
	TWE326_SSP_POKE_PAL_FADE* wk = work;

	switch( wk->seq ){
	case TWE_SSP_POKE_PAL_FADEOUT_INIT:
		SoftSpritePalFadeSet( wk->ssp, 0, wk->evy_max, wk->fade_wait, wk->rgb );
		wk->seq++;
		break;
		
	case TWE_SSP_POKE_PAL_FADEOUT_MOVE:
		if( SoftSpritePalFadeExist( wk->ssp ) == FALSE ){
			wk->seq++;
		}
		break;
	
	case TWE_SSP_POKE_PAL_FADE_WAIT:
		if (wk->wait == 0){
			wk->seq++;
		}
		else {
			wk->wait--;
			break;
		}
		
	case TWE_SSP_POKE_PAL_FADEIN_INIT:
		SoftSpritePalFadeSet( wk->ssp, wk->evy_max, 0, wk->fade_wait, wk->rgb );
		wk->seq++;
		break;
		
	case TWE_SSP_POKE_PAL_FADEIN_MOVE:
		if( SoftSpritePalFadeExist( wk->ssp ) == FALSE ){
			wk->count --;
			if( wk->count <= 0 ){
				// 終了
				wk->seq++;
			}else{
				wk->seq = TWE_SSP_POKE_PAL_FADEOUT_INIT;
			}
		}
		break;
		
	case TWE_SSP_POKE_PAL_FADE_END:
		sys_FreeMemoryEz(wk);
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		return;
	}

}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	ソフトウェアスプライト　ポケモン　パレットフェード点滅
 *
 *	@param	we_sys		技エフェクトシステム
 *
 *	@return	none
 *
 * we_sys.work[0]			対象ポケモン WE_TOOL_M1 ... (1つしか指定できません)
 * we_sys.work[1]	wait	計算待ち時間
 * we_sys.work[2]	num		点滅数
 * we_sys.work[3]	color	変更後の色
 * we_sys.work[4]	evy_max	最大のフェード色割合(16段階)
 *
 * 開始色割合は0です 
 */
//-----------------------------------------------------------------------------
void WestSp_WE_SSPPokePalFade(WE_SYS_PTR we_sys)
{
	TWE326_SSP_POKE_PAL_FADE* wk;
	int no;

	wk = WET_ALLOC_MEMORY(we_sys, TWE326_SSP_POKE_PAL_FADE);
	wk->we_sys	= we_sys;
	wk->ssp		= NULL;

	// ポケモンスプライトデータ取得
	switch( WeSysGPWorkGet(we_sys, 0) ){
	case WE_TOOL_M1:
		wk->ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysATNoGet(we_sys) );
		break;

	case WE_TOOL_M2:
		if (IsWeSysBattleMode2vs2(we_sys) == TRUE){
			wk->ssp = WeSysSoftSpritePointerGet(wk->we_sys, WET_AllySideClientNoGet(wk->we_sys, WeSysATNoGet(wk->we_sys)));
		}
		break;
	
	case WE_TOOL_E1:
		wk->ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysDFNoGet(we_sys) );
		break;

	case WE_TOOL_E2:
		if (IsWeSysBattleMode2vs2(we_sys) == TRUE){
			wk->ssp = WeSysSoftSpritePointerGet(wk->we_sys, WET_AllySideClientNoGet(wk->we_sys, WeSysDFNoGet(wk->we_sys)));
		}
		break;
		
	case WE_TOOL_A:
		{
			int i;
			int type;
			no = 0xFF;
			for (i = 0; i < 4; i++){
				type = WeSysClientTypeGet(we_sys, i);
				
				if (type == CLIENT_TYPE_AA || type == CLIENT_TYPE_A){
					no = i;
					break;
				}
			}
			if (no == 0xFF){
				no = 0;
			}
			wk->ssp = WeSysSoftSpritePointerGet( wk->we_sys, no );
		}	
		break;
		
	case WE_TOOL_C:
		{
			int i;
			int type;
			no = 0xFF;
			for (i = 0; i < 4; i++){
				type = WeSysClientTypeGet(we_sys, i);
				
				if (type == CLIENT_TYPE_C){
					no = i;
					break;
				}
			}
			if (no == 0xFF){
				no = 0;
			}
			wk->ssp = WeSysSoftSpritePointerGet( wk->we_sys, no );
		}
		break;
		
	case WE_TOOL_B:
		{
			int i;
			int type;
			no = 0xFF;
			for (i = 0; i < 4; i++){
				type = WeSysClientTypeGet(we_sys, i);
				
				if (type == CLIENT_TYPE_BB || type == CLIENT_TYPE_B){
					no = i;
					break;
				}
			}
			if (no == 0xFF){
				no = 0;
			}
			wk->ssp = WeSysSoftSpritePointerGet( wk->we_sys, no );
		}	
		break;
		
	case WE_TOOL_D:
		{
			int i;
			int type;
			no = 0xFF;
			for (i = 0; i < 4; i++){
				type = WeSysClientTypeGet(we_sys, i);
				
				if (type == CLIENT_TYPE_D){
					no = i;
					break;
				}
			}
			if (no == 0xFF){
				no = 0;
			}
			wk->ssp = WeSysSoftSpritePointerGet( wk->we_sys, no );
		}	
		break;

	default:
		GF_ASSERT_MSG( 0, "複数のポケモンを指定することが出来ません。" );
		break;
	}
	
	if (wk->ssp == NULL){
		sys_FreeMemoryEz(wk);
		return;
	}

	wk->fade_wait	= WeSysGPWorkGet(we_sys, 1);
	wk->count		= WeSysGPWorkGet(we_sys, 2);
	wk->rgb			= WeSysGPWorkGet(we_sys, 3);
	wk->evy_max		= WeSysGPWorkGet(we_sys, 4);
	wk->wait		= WeSysGPWorkGet(we_sys, 5);

	WEEffect_TCB_AddPriSet(wk->we_sys, WeSSPPokePalFade_TCB, wk);
}



//-------------------------------------
//	
// POKE_OAMを半透明にして拡大して縮小
//	
//=====================================
enum{
	WE326_POKE_OAM_SCALEUP_INIT,
	WE326_POKE_OAM_SCALEUP,
	WE326_POKE_OAM_SCALEDOWN_INIT,
	WE326_POKE_OAM_SCALEDOWN,
	WE326_POKE_OAM_SCALEEND,
};

#define WE326_POKE_OAM_DOWN_OFS	( 40 )
typedef struct {
	WE_SYS_PTR we_sys;
	CATS_RES_PTR crp;
	int seq;

	s16 dy;			// 今のポジション
	s16 poke_h;		// ポケモンの高さ

	// ポケモン
	CATS_ACT_PTR		cap;
	WAZATOOL_CALCMOVE	cap_scale;

	int poke_alpha;
	int scale_s;
	int scale_e;
	int scale_d;
	int scale_num;		// 伸びて縮むを１とした回数
	int scale_sync;		// 伸びて縮むに１回のしんく数

	BOOL scale_ret;		// 拡縮X反転
} TWE326_POKE_OAM_SCALE_UPDOWN;

static void WeCAPPokeScaleUpDownTCB( TCB_PTR tcb, void* work )
{
	TWE326_POKE_OAM_SCALE_UPDOWN* wk = work;
	f32 s_x, s_y;
	BOOL check;

	switch( wk->seq ){
	case WE326_POKE_OAM_SCALEUP_INIT:
		WazaTool_InitScaleRate(
				&wk->cap_scale,
				wk->scale_s,
				wk->scale_d,
				wk->scale_e,
				wk->scale_sync >> 16
				);
		// 拡縮値を設定
		WazaTool_CalcScaleRateToClactScale( &wk->cap_scale, &s_x, &s_y );
		if( wk->scale_ret == TRUE ){
			s_x = -s_x;
		}
		CATS_ObjectScaleSetCap( wk->cap, s_x, s_y );
		wk->seq++;
		break;
		
	case WE326_POKE_OAM_SCALEUP:
		check = WazaTool_CalcScaleRate( &wk->cap_scale );
		WazaTool_CalcScaleRateToClactScale( &wk->cap_scale, &s_x, &s_y );
		if( wk->scale_ret == TRUE ){
			s_x = -s_x;
		}
		CATS_ObjectScaleSetCap( wk->cap, s_x, s_y );
		
		// 拡縮値を設定
		if( check ){

			WazaTool_PokeOffsetSetOAM(
					wk->cap,
					wk->dy, wk->poke_h,
					wk->cap_scale.work[4], WAZAEFF_OFS_MODE_BOTTOM);

		}else{
			wk->seq++;
		}
		break;
		
	case WE326_POKE_OAM_SCALEDOWN_INIT:
		WazaTool_InitScaleRate(
				&wk->cap_scale,
				wk->scale_e,
				wk->scale_d,
				wk->scale_s,
				wk->scale_sync & 0xffff
				);
		wk->seq++;
		break;
		
	case WE326_POKE_OAM_SCALEDOWN:
		check = WazaTool_CalcScaleRate( &wk->cap_scale );
		WazaTool_CalcScaleRateToClactScale( &wk->cap_scale, &s_x, &s_y );
		if( wk->scale_ret == TRUE ){
			s_x = -s_x;
		}
		CATS_ObjectScaleSetCap( wk->cap, s_x, s_y );
		
		// 拡縮値を設定
		if( check ){
			WazaTool_PokeOffsetSetOAM(
					wk->cap,
					wk->dy, wk->poke_h,
					wk->cap_scale.work[4], WAZAEFF_OFS_MODE_BOTTOM);
		}else{
			wk->scale_num --;
			if( wk->scale_num <= 0 ){
				// 終了
				wk->seq++;
			}else{
				wk->seq = WE326_POKE_OAM_SCALEUP_INIT;
			}
		}
		break;
		
	case WE326_POKE_OAM_SCALEEND:
		sys_FreeMemoryEz(wk);
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		return;
	}

	// 残像OAM描画
	CATS_Draw(wk->crp);	
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	POKE_OAM を半透明状態で伸び縮みさせる	
 *
 *	@param	we_sys		技エフェクトシステム
 *
 *	@return	none
 *
 * we_sys.work[0]	at or df	0=攻撃側	1=防御側
 * we_sys.work[1]	alpha		ポケモンのα値
 * we_sys.work[2]	scale_s		開始スケール
 * we_sys.work[3]	scale_e		終了スケール
 * we_sys.work[4]	scale_d		100%の時のスケール
 * we_sys.work[5]	scale_num	スケール数	伸びて縮むを１とした回数
 * we_sys.work[6]	scale_sync	シンク数	伸びるシンク数 上位16bit	縮むシンク数 下位16bit
 * we_sys.work[7]	cap_no		ポケモンのcapの番号
 *
 * ポケモンCAPのwe_sys.work[7] 番目にポケモンの絵を入れておいてください
 */
//-----------------------------------------------------------------------------
void WestSp_WE_CAPPokeScaleUpDown(WE_SYS_PTR we_sys)
{
	TWE326_POKE_OAM_SCALE_UPDOWN* wk;
	SOFT_SPRITE* ssp;
	int at_df;

	wk = WET_ALLOC_MEMORY(we_sys, TWE326_POKE_OAM_SCALE_UPDOWN);
	wk->we_sys	= we_sys;
	wk->crp		= WeSysPokeCrpGet(wk->we_sys);

	// ポケモンの高さ取得
	if( WeSysGPWorkGet(we_sys, 0) == 0 ){
		ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysATNoGet(we_sys) );

		wk->poke_h	= WeSysPokeOfsGet(wk->we_sys, WeSysATNoGet(wk->we_sys));
	}else{
		ssp = WeSysSoftSpritePointerGet( wk->we_sys, WeSysDFNoGet(wk->we_sys) );
		wk->poke_h	= WeSysPokeOfsGet(wk->we_sys, WeSysDFNoGet(wk->we_sys));
	}
	wk->dy = SoftSpriteParaGet( ssp, SS_PARA_POS_Y );
	wk->dy -= SoftSpriteParaGet( ssp, SS_PARA_SHADOW_HEIGHT );
	
	wk->poke_alpha	= WeSysGPWorkGet(we_sys, 1);
	wk->scale_s		= WeSysGPWorkGet(we_sys, 2);
	wk->scale_e		= WeSysGPWorkGet(we_sys, 3);
	wk->scale_d		= WeSysGPWorkGet(we_sys, 4);
	wk->scale_num	= WeSysGPWorkGet(we_sys, 5);
	wk->scale_sync	= WeSysGPWorkGet(we_sys, 6);

	wk->cap = WeSysPokeCapGet(wk->we_sys, WeSysGPWorkGet(we_sys, 7));
	CATS_ObjectPriSetCap( wk->cap, WAZAEFF_ACT_SOFTPRI );
	CATS_ObjectBGPriSetCap( wk->cap, WAZAEFF_ACT_BGPRI );
	CATS_ObjectObjModeSetCap(wk->cap, GX_OAM_MODE_XLU);
	CATS_ObjectAffineSetCap( wk->cap, CLACT_AFFINE_DOUBLE );

	WET_DefaultBlendSet( wk->we_sys, wk->poke_alpha, 16 - wk->poke_alpha );

	WEEffect_TCB_AddPriSet(wk->we_sys, WeCAPPokeScaleUpDownTCB, wk);


	// 拡縮方向を見る
	at_df = WeSysGPWorkGet(we_sys, 0);
	if( at_df == 0 ){
		at_df = WEDEF_DROP_M1;
	}else{
		at_df = WEDEF_DROP_E1;
	}
	if( ContestFlipCheck( wk->we_sys, at_df ) == TRUE ){
		wk->scale_ret = TRUE;
	}
}


//-------------------------------------
//	
//	SSPの拡大縮小
//	
//=====================================
enum{
	WE_POKE_SSP_SCALEUP_INIT,
	WE_POKE_SSP_SCALEUP,
	WE_POKE_SSP_WAIT,
	WE_POKE_SSP_SCALEDOWN_INIT,
	WE_POKE_SSP_SCALEDOWN,
	WE_POKE_SSP_SCALEEND,
};

typedef struct {
	WE_SYS_PTR we_sys;
	int seq;

	s16 dy;			// 今のポジション
	s16 poke_h;		// ポケモンの高さ

	// ポケモン
	SOFT_SPRITE*	ssp;
	WAZATOOL_CALCMOVE	ssp_scale;

	int scale_sx;
	int scale_ex;
	int scale_sy;
	int scale_ey;
	int scale_d;
	int scale_num;		// 伸びて縮むを１とした回数
	int scale_sync;		// 伸びて縮むに１回のしんく数

	int wait;
} TWE_POKE_SSP_SCALE_UPDOWN;

static void WeSSPPokeScaleUpDownTCB( TCB_PTR tcb, void* work )
{
	TWE_POKE_SSP_SCALE_UPDOWN* wk = work;

	switch( wk->seq ){
	case WE_POKE_SSP_SCALEUP_INIT:
		WazaTool_InitScaleRateEx(
				&wk->ssp_scale,
				wk->scale_sx,
				wk->scale_ex,
				wk->scale_sy,
				wk->scale_ey,
				wk->scale_d,
				wk->scale_sync >> 16
				);
		// 拡縮値を設定
		WazaTool_CalcAndReflectScaleRateSsp( &wk->ssp_scale, wk->ssp );
		wk->seq++;
		break;
		
	case WE_POKE_SSP_SCALEUP:
		// 拡縮値を設定
		if( WazaTool_CalcAndReflectScaleRateExSsp( &wk->ssp_scale, wk->ssp ) ){
			WazaTool_PokeOffsetSet(
					wk->ssp,
					wk->dy, wk->poke_h,
					wk->ssp_scale.work[4], WAZAEFF_OFS_MODE_BOTTOM);//*/
			
		}else{
			wk->seq++;
		}
		break;
		
	case WE_POKE_SSP_WAIT:
	
		if (wk->wait == 0){
			wk->seq++;
		}
		else {
			wk->wait--;
			break;
		}
		
	case WE_POKE_SSP_SCALEDOWN_INIT:
		WazaTool_InitScaleRateEx(
				&wk->ssp_scale,
				wk->scale_ex,
				wk->scale_sx,
				wk->scale_ey,
				wk->scale_sy,
				wk->scale_d,
				wk->scale_sync & 0xffff
				);
		WazaTool_CalcAndReflectScaleRateExSsp( &wk->ssp_scale, wk->ssp );
		wk->seq++;
		break;
		
	case WE_POKE_SSP_SCALEDOWN:
		// 拡縮値を設定
		if( WazaTool_CalcAndReflectScaleRateExSsp( &wk->ssp_scale, wk->ssp ) ){
			WazaTool_PokeOffsetSet(
					wk->ssp,
					wk->dy, wk->poke_h,
					wk->ssp_scale.work[4], WAZAEFF_OFS_MODE_BOTTOM);//*/
		}else{
			wk->scale_num --;
			if( wk->scale_num <= 0 ){
				// 終了
				wk->seq++;
			}else{
				wk->seq = WE_POKE_SSP_SCALEUP_INIT;
			}
		}
		break;
		
	case WE_POKE_SSP_SCALEEND:
		SoftSpriteDefaultScaleSet(wk->ssp);
		sys_FreeMemoryEz(wk);
		WEEffect_TCB_Delete(wk->we_sys, tcb);
		return;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	POKE_SSP を伸び縮みさせる	
 *
 *	@param	we_sys		技エフェクトシステム
 *
 *	@return	none
 *
 * we_sys.work[0]	対象ポケモン	（複数選択不可能）
 * we_sys.work[1]	scale_sx	開始スケール
 * we_sys.work[2]	scale_ex	終了スケール
 * we_sys.work[3]	scale_sy	開始スケール
 * we_sys.work[4]	scale_ey	終了スケール
 * we_sys.work[5]	scale_d		100%の時のスケール
 * we_sys.work[6]	scale_num	スケール数	伸びて縮むを１とした回数　上位16ビット ウェイト　下位16ビット スケール数
 
 * we_sys.work[7]	scale_sync	シンク数	伸びるシンク数 上位16bit	縮むシンク数 下位16bit
 *
 */
//-----------------------------------------------------------------------------
void WestSp_WE_SSPPokeScaleUpDown(WE_SYS_PTR we_sys)
{
	TWE_POKE_SSP_SCALE_UPDOWN* wk;
	TWE_POKE_SYS pp[ 4 ];
	TCB_PTR tcb;
	int num;
	int no;

	wk = WET_ALLOC_MEMORY(we_sys, TWE_POKE_SSP_SCALE_UPDOWN);
	wk->we_sys	= we_sys;

	// ポケモンの高さ取得
	switch( WeSysGPWorkGet(we_sys, 0) ){
	case WE_TOOL_M1 | WE_TOOL_SSP:
	case WE_TOOL_M2 | WE_TOOL_SSP:
		wk->poke_h	= WeSysPokeOfsGet(wk->we_sys, WeSysATNoGet(wk->we_sys));
		WT_SSPointerGet( wk->we_sys, WeSysGPWorkGet(we_sys, 0), pp, &num );
		wk->ssp = pp[0].ssp;
		break;
		
	case WE_TOOL_E1 | WE_TOOL_SSP:
	case WE_TOOL_E2 | WE_TOOL_SSP:
		wk->poke_h	= WeSysPokeOfsGet(wk->we_sys, WeSysDFNoGet(wk->we_sys));
		WT_SSPointerGet( wk->we_sys, WeSysGPWorkGet(we_sys, 0), pp, &num );
		wk->ssp = pp[0].ssp;
		break;
	
	case WE_TOOL_A:
		{
			int i;
			int type;
			no = 0xFF;
			for (i = 0; i < 4; i++){
				type = WeSysClientTypeGet(we_sys, i);
				
				if (type == CLIENT_TYPE_AA || type == CLIENT_TYPE_A){
					no = i;
					break;
				}
			}
			if (no == 0xFF){
				no = 0;
			}
			wk->ssp = WeSysSoftSpritePointerGet( wk->we_sys, no );
		}	
		break;
		
	case WE_TOOL_C:
		{
			int i;
			int type;
			no = 0xFF;
			for (i = 0; i < 4; i++){
				type = WeSysClientTypeGet(we_sys, i);
				
				if (type == CLIENT_TYPE_C){
					no = i;
					break;
				}
			}
			if (no == 0xFF){
				no = 0;
			}
			wk->ssp = WeSysSoftSpritePointerGet( wk->we_sys, no );
		}
		break;
		
	case WE_TOOL_B:
		{
			int i;
			int type;
			no = 0xFF;
			for (i = 0; i < 4; i++){
				type = WeSysClientTypeGet(we_sys, i);
				
				if (type == CLIENT_TYPE_BB || type == CLIENT_TYPE_B){
					no = i;
					break;
				}
			}
			if (no == 0xFF){
				no = 0;
			}
			wk->ssp = WeSysSoftSpritePointerGet( wk->we_sys, no );
		}	
		break;
		
	case WE_TOOL_D:
		{
			int i;
			int type;
			no = 0xFF;
			for (i = 0; i < 4; i++){
				type = WeSysClientTypeGet(we_sys, i);
				
				if (type == CLIENT_TYPE_D){
					no = i;
					break;
				}
			}
			if (no == 0xFF){
				no = 0;
			}
			wk->ssp = WeSysSoftSpritePointerGet( wk->we_sys, no );
		}	
		break;
	}

	// ポケモン取得
	if (wk->ssp == NULL){
		sys_FreeMemoryEz(wk);
		return;		
	}
	wk->dy = SoftSpriteParaGet( wk->ssp, SS_PARA_POS_Y );
	wk->poke_h = SoftSpriteParaGet( wk->ssp, SS_PARA_SHADOW_HEIGHT );
	wk->poke_h += 16;
	
	wk->scale_sx	= WeSysGPWorkGet(we_sys, 1);
	wk->scale_ex	= WeSysGPWorkGet(we_sys, 2);
	wk->scale_sy	= WeSysGPWorkGet(we_sys, 3);
	wk->scale_ey	= WeSysGPWorkGet(we_sys, 4);
	wk->scale_d		= WeSysGPWorkGet(we_sys, 5);
	wk->scale_num	= WeSysGPWorkGet(we_sys, 6);
	wk->scale_sync	= WeSysGPWorkGet(we_sys, 7);

	///< ワークが足りないので、上位16ビットをウェイトに変更
	wk->scale_num	= WeSysGPWorkGet(we_sys, 6) & 0xffff;
	wk->wait		= WeSysGPWorkGet(we_sys, 6) >> 16;

	tcb = WEEffect_TCB_AddPriSet(wk->we_sys, WeSSPPokeScaleUpDownTCB, wk);
	
	WeSSPPokeScaleUpDownTCB(tcb, wk);
}



//-------------------------------------
//	
//	アルファフェード処理
//	
//=====================================
typedef struct {
	WE_SYS_PTR we_sys;
	CATS_RES_PTR crp;

	WAZATOOL_ALPHA_FADE alpha;
} TWE_BG_NORMALALPHA_FADE_SYS;

static void WeCapNormalAlphaTCB( TCB_PTR tcb, void* work )
{
	TWE_BG_NORMALALPHA_FADE_SYS* wk = work;

	if( WazaTool_EndCheckAlphaFade( &wk->alpha ) ){
		sys_FreeMemoryEz(wk);
		WEEffect_TCB_Delete(wk->we_sys, tcb);
	}else{

		// 残像OAM描画
		CATS_Draw(wk->crp);	
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	αフェード
 *
 *	@param	we_sys		技エフェクトシステム
 *
 *	@return	none
 *
 *	we_sys.work[0]	対象capポケモン	0bit = 0 1bit = 1
 *	we_sys.work[1]	対象１開始α値	0～31
 *	we_sys.work[2]	対象１終了α値	0～31
 *	we_sys.work[3]	対象２開始α値	0～31
 *	we_sys.work[4]	対象２終了α値	0～31
 *	we_sys.work[5]	シンク数
 */
//-----------------------------------------------------------------------------
void WestSp_WE_CAP_NormalAlphaFade(WE_SYS_PTR we_sys)
{
	TWE_BG_NORMALALPHA_FADE_SYS* wk;
	int cap_bit;
	int i;
	CATS_ACT_PTR cap;
	int alpha1_s;
	int alpha2_s;
	

	wk = WET_ALLOC_MEMORY(we_sys, TWE_BG_NORMALALPHA_FADE_SYS);
	wk->we_sys	= we_sys;
	wk->crp		= WeSysPokeCrpGet(wk->we_sys);
	
	cap_bit = WeSysGPWorkGet( we_sys, 0 );
	
	// OAM設定
	for( i=0; i<4; i++ ){
		if( cap_bit & (1 << i) ){
			cap  = WeSysPokeCapGet(wk->we_sys, i);
			CATS_ObjectObjModeSetCap( cap, GX_OAM_MODE_XLU );
		}
	}
	
	alpha1_s = WeSysGPWorkGet( we_sys, 1 );
	alpha2_s = WeSysGPWorkGet( we_sys, 3 );
	
	WET_DefaultBlendSet( wk->we_sys, alpha1_s, alpha2_s );
	WazaTool_StartAlphaFade(
			&wk->alpha,
			alpha1_s,
			WeSysGPWorkGet( we_sys, 2 ),
			alpha2_s,
			WeSysGPWorkGet( we_sys, 4 ),
			WeSysGPWorkGet( we_sys, 5 )
			);
		
	WEEffect_TCB_AddPriSet(wk->we_sys, WeCapNormalAlphaTCB, wk);
}


//-------------------------------------
//	
//	ポケモンのバニッシュ
//	
//=====================================
//----------------------------------------------------------------------------
/**
 *
 *	@brief	ポケモンのバニッシュ設定
 *
 *	@param	we_sys	技エフェクトシステム
 *
 *	@return	none
 *
 * we_sys.work[0]	対象ポケモン　複数可
 * we_sys.work[1]	0表示	1非表示
 *
 */
//-----------------------------------------------------------------------------
void WestSp_WE_SSP_PokeVanish(WE_SYS_PTR we_sys)
{
	TWE_POKE_SYS pp;
	int num;
	int i;
	int flag = WeSysGPWorkGet( we_sys, 1 );
	
	WT_SSPointerGet( 
			we_sys,
			WeSysGPWorkGet( we_sys, 0 ),
			&pp,
			&num
			);

	for( i=0; i<num; i++ ){
		
		if (BT_WazaKoukaCheck( we_sys, pp.client_no ) == TRUE		///< エフェクトで消えてるのに
		&&	flag == 0){ continue; }									///< 出そうとしてる時　とばす
		
		SoftSpriteParaSet( pp.ssp, SS_PARA_VANISH,  flag );
	}
}



/// ブリンク
typedef struct {
	
	int num;
	int cnt;
	int	wait;
	
	TWE_POKE_SYS	pp;

	TWE_TOOL_SYS	ts;
	
	WE_SYS_PTR		wsp;
	
} TWE_T03_SYS;

static void WeT03_TCB(TCB_PTR tcb, void* work)
{
	TWE_T03_SYS* wk = (TWE_T03_SYS*)work;
	
	if (wk->cnt >= wk->wait){
		
		if (wk->num == 0){
			SoftSpriteParaSet(wk->pp.ssp, SS_PARA_VANISH, 0);
			sys_FreeMemoryEz(wk);
			WEEffect_TCB_Delete(wk->wsp, tcb);
		}
		else {
			int flag;
			flag = SoftSpriteParaGet(wk->pp.ssp, SS_PARA_VANISH);
			SoftSpriteParaSet(wk->pp.ssp, SS_PARA_VANISH, flag ^ 1);
			wk->num--;
			wk->cnt = 0;
		}				
	}
	else {
		wk->cnt++;
	}
}

void WestSp_WE_T03(WE_SYS_PTR we_sys)
{
	TWE_T03_SYS* wk = WET_ALLOC_MEMORY(we_sys, TWE_T03_SYS);

	wk->wsp  = we_sys;
	wk->num  = WeSysGPWorkGet(we_sys, 0) * 2;
	wk->wait = WeSysGPWorkGet(we_sys, 1);

	WT_ToolSysInit(we_sys, &wk->ts);
	
	wk->pp.ssp = WeSysSoftSpritePointerGet(we_sys, WeSysATNoGet(we_sys));
		
	WEEffect_TCB_AddPriSet(wk->wsp, WeT03_TCB, wk);
}


/// 背後攻撃
typedef struct {

	int num;
	int cnt;
	int	wait;
	
	s16	ofs_x;		///< 移動幅
	
	TWE_POKE_SYS	pp;

	TWE_TOOL_SYS	ts;
	
	WAZATOOL_CALCMOVE cm;
	
	WE_SYS_PTR		wsp;
	
} TWE_T04_SYS;

static void WeT04_TCB(TCB_PTR tcb, void* work)
{
	TWE_T04_SYS* wk = (TWE_T04_SYS*)work;
	
	switch(wk->ts.seq){
	case 0:
		WazaTool_InitStraightSyncFx(&wk->cm, 
									wk->pp.p.x, wk->pp.p.x + wk->ofs_x,
									wk->pp.p.y, wk->pp.p.y, 
									wk->wait);
		wk->ts.seq++;
		break;
	case 1:
		if (WazaTool_CalcStraightFx(&wk->cm) == FALSE){
			wk->ts.seq++;
		}
		SoftSpriteParaSet(wk->pp.ssp, SS_PARA_POS_X, wk->cm.x);
		break;
	default:
		WEEffect_TCB_Delete(wk->wsp, tcb);
		sys_FreeMemoryEz(wk);
		break;
	}
}

void WestSp_WE_T04(WE_SYS_PTR we_sys)
{
	int r_vec;
	int type;
	int client;
	TWE_T04_SYS* wk = WET_ALLOC_MEMORY(we_sys, TWE_T04_SYS);

	wk->wsp   = we_sys;
	wk->wait  = WeSysGPWorkGet(we_sys, 0);
	wk->ofs_x = WeSysGPWorkGet(we_sys, 1);
	type = WeSysGPWorkGet(we_sys, 2);
	
	client = 0xFF;
	switch(type){
	case WE_TOOL_M1 | WE_TOOL_SSP:
		client = WeSysATNoGet(we_sys);
		break;
	case WE_TOOL_M2 | WE_TOOL_SSP:
		if (IsWeSysBattleMode2vs2(we_sys) == TRUE){
			client = WET_AllySideClientNoGet(we_sys, WeSysATNoGet(we_sys));
		}
		break;
	case WE_TOOL_E1 | WE_TOOL_SSP:
		client = WeSysDFNoGet(we_sys);
		break;
	case WE_TOOL_E2 | WE_TOOL_SSP:
		if (IsWeSysBattleMode2vs2(we_sys) == TRUE){
			client = WET_AllySideClientNoGet(we_sys, WeSysDFNoGet(we_sys));
		}
		break;
	default:
		GF_ASSERT(0);
		break;
	}
	
	if (client == 0xFF){
		sys_FreeMemoryEz(wk);
		return;
	}

	WT_ToolSysInit(we_sys, &wk->ts);
	
	wk->pp.ssp = WeSysSoftSpritePointerGet(we_sys, client);
	WT_SSP_PointGet(wk->pp.ssp, &wk->pp.p);
	
	r_vec = WazaTool_VecChangeX(we_sys, client);
	if (r_vec > 0){
		wk->ofs_x *= +1;
	}
	else {
		wk->ofs_x *= -1;
	}
		
	WEEffect_TCB_AddPriSet(wk->wsp, WeT04_TCB, wk);
}

/// 元の位置にもどる
typedef struct {

	int num;
	int cnt;
	int	wait;
	
	TWE_POKE_SYS	pp;
	TWE_TOOL_SYS	ts;
	
	WAZATOOL_CALCMOVE cm;
	
	WE_SYS_PTR		wsp;
	
	s16	ofs_x;		///< 移動幅
	
} TWE_T05_SYS;

static void WeT05_TCB(TCB_PTR tcb, void* work)
{
	TWE_T05_SYS* wk = (TWE_T05_SYS*)work;
	
	switch(wk->ts.seq){
	case 0:
		if (wk->pp.ssp == NULL){
			wk->ts.seq = 0xff;
			break;
		}
		WazaTool_InitStraightSyncFx(&wk->cm, 
									wk->pp.p.x, wk->pp.p.x + wk->ofs_x,
									wk->pp.p.y, wk->pp.p.y, 
									wk->wait);
		wk->ts.seq++;

	case 1:
		if (WazaTool_CalcStraightFx(&wk->cm) == FALSE){
			wk->ts.seq++;
		}
		SoftSpriteParaSet(wk->pp.ssp, SS_PARA_POS_X, wk->cm.x);
		break;
	default:
		WEEffect_TCB_Delete(wk->wsp, tcb);
		sys_FreeMemoryEz(wk);
		break;
	}
}

void WestSp_WE_T05(WE_SYS_PTR we_sys)
{
	int r_vec;
	int type;
	int client;
	TWE_T05_SYS* wk = WET_ALLOC_MEMORY(we_sys, TWE_T05_SYS);

	wk->wsp   = we_sys;
	wk->wait  = WeSysGPWorkGet(we_sys, 0);
	wk->ofs_x = WeSysGPWorkGet(we_sys, 1);
	type = WeSysGPWorkGet(we_sys, 2);

	WT_ToolSysInit(we_sys, &wk->ts);
	
	client = 0xFF;
	switch(type){
	case WE_TOOL_M1 | WE_TOOL_SSP:
		client = WeSysATNoGet(we_sys);
		break;
	case WE_TOOL_M2 | WE_TOOL_SSP:
		if (IsWeSysBattleMode2vs2(we_sys) == TRUE){
			client = WET_AllySideClientNoGet(we_sys, WeSysATNoGet(we_sys));
		}
		break;
	case WE_TOOL_E1 | WE_TOOL_SSP:
		client = WeSysDFNoGet(we_sys);
		break;
	case WE_TOOL_E2 | WE_TOOL_SSP:
		if (IsWeSysBattleMode2vs2(we_sys) == TRUE){
			client = WET_AllySideClientNoGet(we_sys, WeSysDFNoGet(we_sys));
		}
		break;
	default:
		GF_ASSERT(0);
		break;
	}
	
	if (client == 0xFF){
		sys_FreeMemoryEz(wk);
		return;
	}

	wk->pp.ssp = WeSysSoftSpritePointerGet(we_sys, client);
	WT_SSP_PointGet(wk->pp.ssp, &wk->pp.p);
	
	r_vec = WazaTool_VecChangeX(we_sys, client);
	if (r_vec > 0){
		wk->ofs_x *= +1;
	}
	else {
		wk->ofs_x *= -1;
	}
		
	if (WES_ContestFlag_Get(we_sys) == TRUE){
	//	wk->ofs_x *= -1;
	}

	{
		TCB_PTR tcb;
		
		tcb = WEEffect_TCB_AddPriSet(wk->wsp, WeT05_TCB, wk);
		
		WeT05_TCB(tcb, wk);
	}
}


// びよよん
// -----------------------------------------
//
//	構造体
//
// -----------------------------------------
typedef struct {
	
	u8	seq;
	u8	wait;
	s16	dy;
	int poke_h;
	
	u8	fade_cnt;
	
	u8	keep_cnt;
	u8	keep_wait;
	
	WE_SYS_PTR		wsp;
	SOFT_SPRITE*	ssp;
	
	WAZATOOL_CALCMOVE cm;
	WAZATOOL_CALCMOVE shake;
	
} TWE_T06_SYS;

#define WET06_FADE_CNT		(3)
#define WET06_SS_FADE_WAIT	(0)
#define WET06_SS_FADE_COL	(0x1F)
#define WET06_END_EVY		(10)

//--------------------------------------------------------------
/**
 * @brief	動作関数
 *
 * @param	tcb	
 * @param	work	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WeT06_TCB(TCB_PTR tcb, void* work)
{
	TWE_T06_SYS* wk = (TWE_T06_SYS*)work;
	
	switch(wk->seq){
	case 0:
		///< 縮み
		if (WazaTool_CalcScaleRate(&wk->cm) == TRUE){
			WazaTool_CalcShake(&wk->shake);
			SoftSpriteParaSet(wk->ssp, SS_PARA_AFF_X, wk->cm.x);
			SoftSpriteParaSet(wk->ssp, SS_PARA_AFF_Y, wk->cm.y);
			SoftSpriteParaCalc(wk->ssp, SS_PARA_POS_X, wk->shake.x);
			{
				s16 ofs_y = WazaTool_CalcScaleRateToYPosFX(wk->dy, wk->poke_h, wk->cm.work[4]);
				SoftSpriteParaSet(wk->ssp, SS_PARA_POS_Y, wk->dy + ofs_y);
			}
		}
		else {
			wk->seq++;
		}		
		break;
	case 1:
		if ((++wk->keep_cnt) > wk->keep_wait){
			WazaTool_InitScaleRate(&wk->cm,
						   		   WeSysGPWorkGet(wk->wsp, 0),
						   		   100,
						   		   WeSysGPWorkGet(wk->wsp, 1),
						   		   WeSysGPWorkGet(wk->wsp, 3));
			wk->seq++;
		}
		break;

	case 2:
		///< びよよーーーん
		if (WazaTool_CalcScaleRate(&wk->cm) == TRUE){
			SoftSpriteParaSet(wk->ssp, SS_PARA_AFF_X, wk->cm.x);
			SoftSpriteParaSet(wk->ssp, SS_PARA_AFF_Y, wk->cm.y);
			{
				s16 ofs_y = WazaTool_CalcScaleRateToYPosFX(wk->dy, wk->poke_h, wk->cm.work[4]);
				SoftSpriteParaSet(wk->ssp, SS_PARA_POS_Y, wk->dy + ofs_y);
			}
		}
		else {
			wk->seq++;
		}
		break;
	case 3:
		///< もどる
		if (WazaTool_CalcScaleRate(&wk->cm) == TRUE){
			SoftSpriteParaSet(wk->ssp, SS_PARA_AFF_X, wk->cm.x);
			SoftSpriteParaSet(wk->ssp, SS_PARA_AFF_Y, wk->cm.y);
			{
				s16 ofs_y = WazaTool_CalcScaleRateToYPosFX(wk->dy, wk->poke_h, wk->cm.work[4]);
				SoftSpriteParaSet(wk->ssp, SS_PARA_POS_Y, wk->dy + ofs_y);
			}
		}
		else {
			SoftSpriteParaSet(wk->ssp, SS_PARA_AFF_X, 0x0100);
			SoftSpriteParaSet(wk->ssp, SS_PARA_AFF_Y, 0x0100);
			SoftSpriteParaSet(wk->ssp, SS_PARA_POS_Y, wk->dy);
			wk->seq++;
		}
		break;
	default:
		WEEffect_TCB_Delete(wk->wsp, tcb);
		sys_FreeMemoryEz(wk);
		break;
	}
}


//--------------------------------------------------------------
/**
 * @brief	呼び出し関数
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WestSp_WE_T06(WE_SYS_PTR we_sys)
{
	TWE_T06_SYS* wk;
	
	wk = sys_AllocMemory(WeSysHeapAreaGet(we_sys), sizeof(TWE_T06_SYS));
	
	wk->fade_cnt = 0;
	wk->seq = 0;
	wk->wsp = we_sys;
	wk->ssp = WeSysSoftSpritePointerGet( wk->wsp, WeSysATNoGet(wk->wsp) );
	
	wk->keep_cnt  = 0;
	wk->keep_wait = WeSysGPWorkGet(we_sys, 4);
	
	wk->dy  = SoftSpriteParaGet(wk->ssp, SS_PARA_POS_Y);
	
	wk->poke_h = WeSysPokeOfsGet(wk->wsp, WeSysATNoGet(wk->wsp));
	
	///< 拡縮
	WazaTool_InitScaleRate(&wk->cm,
						   100,
						   100,
						   WeSysGPWorkGet(we_sys, 0),
						   WeSysGPWorkGet(we_sys, 2));
	///< 揺らし
	WazaTool_InitShake(&wk->shake, 2,0,0,10);
						   
	
	WEEffect_TCB_AddPriSet(wk->wsp, WeT06_TCB, wk);
}


// びよよん
// -----------------------------------------
//
//	構造体
//
// -----------------------------------------
typedef struct {
	
	u8	seq;
	u8	wait;
	s16	dy;
	int poke_h;
	
	u8	fade_cnt;
	
	u8	keep_cnt;
	u8	keep_wait;
	
	int param_3;
	int param_4;
	int param_5;
	
	WE_SYS_PTR		wsp;
	SOFT_SPRITE*	ssp;
	
	WAZATOOL_CALCMOVE cm;
	WAZATOOL_CALCMOVE shake;
	
} TWE_T07_SYS;

#define WET07_FADE_CNT		(3)
#define WET07_SS_FADE_WAIT	(0)
#define WET07_SS_FADE_COL	(0x1F)
#define WET07_END_EVY		(10)

//--------------------------------------------------------------
/**
 * @brief	動作関数
 *
 * @param	tcb	
 * @param	work	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WeT07_TCB(TCB_PTR tcb, void* work)
{
	TWE_T07_SYS* wk = (TWE_T07_SYS*)work;
	
	switch(wk->seq){
	case 0:
		///< 縮み
		if (WazaTool_CalcScaleRateEx(&wk->cm) == TRUE){
			WazaTool_CalcShake(&wk->shake);
			SoftSpriteParaSet(wk->ssp, SS_PARA_AFF_X, wk->cm.x);
			SoftSpriteParaSet(wk->ssp, SS_PARA_AFF_Y, wk->cm.y);
			SoftSpriteParaCalc(wk->ssp, SS_PARA_POS_X, wk->shake.x);
			{
				s16 ofs_y = WazaTool_CalcScaleRateToYPosFX(wk->dy, wk->poke_h, wk->cm.work[4]);
				SoftSpriteParaSet(wk->ssp, SS_PARA_POS_Y, wk->dy + ofs_y);
			}
		}
		else {
			wk->seq++;
//			WEEffect_TCB_Delete(wk->wsp, tcb);
//			sys_FreeMemoryEz(wk);
		}		
		break;
	case 1:
		if ((++wk->keep_cnt) > wk->keep_wait){
			{
				s16 sx, sy;
				s16 ex, ey;
				sx = wk->param_3 >> 16;
				ex = wk->param_3 & 0x00FF;
				sy = wk->param_4 >> 16;
				ey = wk->param_4 & 0x00FF;
				WazaTool_InitScaleRateEx(&wk->cm,
										sx,ex,
										sy,ey,100,
										wk->param_5);
			}
			wk->seq++;
		}
		break;

	case 2:
		///< びよよーーーん
		if (WazaTool_CalcScaleRateEx(&wk->cm) == TRUE){
			SoftSpriteParaSet(wk->ssp, SS_PARA_AFF_X, wk->cm.x);
			SoftSpriteParaSet(wk->ssp, SS_PARA_AFF_Y, wk->cm.y);
			{
				s16 ofs_y = WazaTool_CalcScaleRateToYPosFX(wk->dy, wk->poke_h, wk->cm.work[4]);
				SoftSpriteParaSet(wk->ssp, SS_PARA_POS_Y, wk->dy + ofs_y);
			}
		}
		else {
			wk->seq++;
		}
		break;
	case 3:
		///< もどる
		if (WazaTool_CalcScaleRateEx(&wk->cm) == TRUE){
			SoftSpriteParaSet(wk->ssp, SS_PARA_AFF_X, wk->cm.x);
			SoftSpriteParaSet(wk->ssp, SS_PARA_AFF_Y, wk->cm.y);
			{
				s16 ofs_y = WazaTool_CalcScaleRateToYPosFX(wk->dy, wk->poke_h, wk->cm.work[4]);
				SoftSpriteParaSet(wk->ssp, SS_PARA_POS_Y, wk->dy + ofs_y);
			}
		}
		else {
			SoftSpriteParaSet(wk->ssp, SS_PARA_AFF_X, 0x0100);
			SoftSpriteParaSet(wk->ssp, SS_PARA_AFF_Y, 0x0100);
			SoftSpriteParaSet(wk->ssp, SS_PARA_POS_Y, wk->dy);
			wk->seq++;
		}
		break;
	default:
		WEEffect_TCB_Delete(wk->wsp, tcb);
		sys_FreeMemoryEz(wk);
		break;
	}
}


//--------------------------------------------------------------
/**
 * @brief	呼び出し関数
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WestSp_WE_T07(WE_SYS_PTR we_sys)
{
	TWE_T07_SYS* wk;
	
	wk = sys_AllocMemory(WeSysHeapAreaGet(we_sys), sizeof(TWE_T07_SYS));
	
	wk->fade_cnt = 0;
	wk->seq = 0;
	wk->wsp = we_sys;
	wk->ssp = WeSysSoftSpritePointerGet( wk->wsp, WeSysATNoGet(wk->wsp) );
	
	wk->keep_cnt  = 0;
	wk->keep_wait = WeSysGPWorkGet(we_sys, 6);
	
	wk->param_3 = WeSysGPWorkGet(wk->wsp, 3);
	wk->param_4 = WeSysGPWorkGet(wk->wsp, 4);
	wk->param_5 = WeSysGPWorkGet(wk->wsp, 5);
	
	WazaEffPosGet_ClientType(we_sys, WeSysATNoGet(wk->wsp), NULL, &wk->dy);
	
	wk->poke_h = WeSysPokeOfsGet(wk->wsp, WeSysATNoGet(wk->wsp));
	
	wk->dy += wk->poke_h;
	
	///< 拡縮
	{
		s16 sx, sy;
		s16 ex, ey;
		s16 ofs_y;
		sx = WeSysGPWorkGet(we_sys, 0) >> 16;
		ex = WeSysGPWorkGet(we_sys, 0) & 0x00FF;
		sy = WeSysGPWorkGet(we_sys, 1) >> 16;
		ey = WeSysGPWorkGet(we_sys, 1) & 0x00FF;
		WazaTool_InitScaleRateEx(&wk->cm,
								sx,ex,
								sy,ey,100,
								WeSysGPWorkGet(we_sys, 2));
	}
	///< 揺らし
	WazaTool_InitShake(&wk->shake, 2,0,0,10);
						   
	
	WEEffect_TCB_AddPriSet(wk->wsp, WeT07_TCB, wk);
}

// =============================================================================
//
//
//	■オーラ
//
//
// =============================================================================
typedef struct {

	int type;
	
	TWE_TOOL_SYS	ts;
	
	CATS_ACT_PTR	poke_cap;
	CATS_ACT_PTR	obj_win_cap;
	
} TWE_T08_SYS;

static void WeT08_TCB(TCB_PTR tcb, void* work)
{
	TWE_T08_SYS* wk = (TWE_T08_SYS*)work;

	switch(wk->ts.seq){
	default:
		GX_SetVisibleWnd(GX_WNDMASK_NONE);
		WeSysBaseBGReset(wk->ts.wsp, BATTLE_FRAME_EFFECT);
		WEEffect_TCB_Delete(wk->ts.wsp, tcb);
		sys_FreeMemoryEz(wk);
		return;
	}

	CATS_ObjectUpdateCap(wk->obj_win_cap);
//	CATS_ObjectUpdateCap(wk->poke_cap);
	
	CATS_Draw(wk->ts.poke_crp);
}
#define WET08_AURA_OUTSIDE_PLANE (GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ)
#define WET08_AURA_INSIDE_PLANE  (GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 |	GX_WND_PLANEMASK_BG2)
void WestSp_WE_T08(WE_SYS_PTR we_sys)
{
	int type;
	TWE_T08_SYS* wk = NULL;
	
	wk = WET_ALLOC_MEMORY(we_sys, TWE_T08_SYS);

	type = WeSysGPWorkGet(we_sys, 0);

	WT_ToolSysInit(we_sys, &wk->ts);

	WeSysBaseBGSet(wk->ts.wsp, BATTLE_FRAME_EFFECT);

	///< ウィンドウOBJ
	wk->obj_win_cap = WeSysPokeCapGet(wk->ts.wsp, 0);
	CATS_ObjectObjModeSetCap(wk->obj_win_cap, GX_OAM_MODE_OBJWND);
	CATS_ObjectAffineSetCap(wk->obj_win_cap, CLACT_AFFINE_DOUBLE);
	CATS_ObjectScaleSetCap(wk->obj_win_cap, 1.2f, 1.2f);
	GX_SetVisibleWnd(GX_WNDMASK_OW);
	G2_SetWndOutsidePlane(WET08_AURA_OUTSIDE_PLANE,	FALSE);
	G2_SetWndOBJInsidePlane(WET08_AURA_INSIDE_PLANE, FALSE);
	
	///< 半透明OBJ
//	wk->poke_cap = WeSysPokeCapGet(wk->ts.wsp, 1);
	
	WEEffect_TCB_AddPriSet(wk->ts.wsp, WeT08_TCB, wk);
}

/// 元の位置にもどる
typedef struct {

	int num;
	int cnt;
	int	wait;
	
	TWE_POKE_SYS	pp;
	TWE_TOOL_SYS	ts;
	
	WAZATOOL_CALCMOVE cm;
	
	WE_SYS_PTR		wsp;
	
	s16	ofs_x;		///< 移動幅
	s16	ofs_y;		///< 移動幅
	
} TWE_T10_SYS;

static void WeT10_TCB(TCB_PTR tcb, void* work)
{
	TWE_T10_SYS* wk = (TWE_T10_SYS*)work;
	
	switch(wk->ts.seq){
	case 0:
		WazaTool_InitStraightSyncFx(&wk->cm, 
									wk->pp.p.x, wk->pp.p.x + wk->ofs_x,
									wk->pp.p.y, wk->pp.p.y + wk->ofs_y, 
									wk->wait);
		wk->ts.seq++;

	case 1:
		if (WazaTool_CalcStraightFx(&wk->cm) == FALSE){
			wk->ts.seq++;
		}
		SoftSpriteParaSet(wk->pp.ssp, SS_PARA_POS_X, wk->cm.x);
		SoftSpriteParaSet(wk->pp.ssp, SS_PARA_POS_Y, wk->cm.y);
		break;
	default:
		WEEffect_TCB_Delete(wk->wsp, tcb);
		sys_FreeMemoryEz(wk);
		break;
	}
}

void WestSp_WE_T10(WE_SYS_PTR we_sys)
{
	int r_vec;
	int type;
	int client;
	TWE_T10_SYS* wk = WET_ALLOC_MEMORY(we_sys, TWE_T10_SYS);

	wk->wsp   = we_sys;
	wk->wait  = WeSysGPWorkGet(we_sys, 0);
	wk->ofs_x = WeSysGPWorkGet(we_sys, 1);
	wk->ofs_y = WeSysGPWorkGet(we_sys, 2);
	type = WeSysGPWorkGet(we_sys, 3);

	WT_ToolSysInit(we_sys, &wk->ts);
	
	client = 0xFF;
	switch(type){
	case WE_TOOL_M1 | WE_TOOL_SSP:
		client = WeSysATNoGet(we_sys);
		break;
	case WE_TOOL_M2 | WE_TOOL_SSP:
		if (IsWeSysBattleMode2vs2(we_sys) == TRUE){
			client = WET_AllySideClientNoGet(we_sys, WeSysATNoGet(we_sys));
		}
		break;
	case WE_TOOL_E1 | WE_TOOL_SSP:
		client = WeSysDFNoGet(we_sys);
		break;
	case WE_TOOL_E2 | WE_TOOL_SSP:
		if (IsWeSysBattleMode2vs2(we_sys) == TRUE){
			client = WET_AllySideClientNoGet(we_sys, WeSysDFNoGet(we_sys));
		}
		break;
	default:
		GF_ASSERT(0);
		break;
	}

	if (client == 0xFF){
		sys_FreeMemoryEz(wk);
		return;
	}
	
	wk->pp.ssp = WeSysSoftSpritePointerGet(we_sys, client);
	if (wk->pp.ssp == NULL){
		sys_FreeMemoryEz(wk);
		return;
	}	
	WT_SSP_PointGet(wk->pp.ssp, &wk->pp.p);
	
	r_vec = WazaTool_VecChangeX(we_sys, client);
	if (r_vec > 0){
		wk->ofs_x *= +1;
		wk->ofs_y *= +1;
	}
	else {
		wk->ofs_x *= -1;
		wk->ofs_y *= -1;
	}
	
	if (WES_ContestFlag_Get(we_sys) == TRUE){
		wk->ofs_y *= -1;
	}

	{
		TCB_PTR tcb;
		
		tcb = WEEffect_TCB_AddPriSet(wk->wsp, WeT10_TCB, wk);
		
		WeT10_TCB(tcb, wk);
	}
}




//--------------------------------------------------------------
/**
 *
 * @brief	回転	
 *
 */
//--------------------------------------------------------------
typedef struct {

	TWE_TOOL_SYS		ts;		///< 技エフェクト汎用構造体
	TWE_POKE_SYS		poke;	///< ポケモン汎用構造体	
	WAZATOOL_CALCMOVE	cm;		///< 汎用ワーク	
	
} TWE_KAITEN;

static void WeKaiten_TCB(TCB_PTR tcb, void* work)
{
	int ret;
	
	TWE_KAITEN* wk = (TWE_KAITEN*)work;
	
	ret = WazaTool_CalcAndReflectRotaFxSsp(&wk->cm, wk->poke.p.x, wk->poke.p.y, wk->poke.ssp);
	
	if (ret == FALSE){
		SoftSpriteParaSet(wk->poke.ssp, SS_PARA_POS_X, wk->poke.p.x);
		SoftSpriteParaSet(wk->poke.ssp, SS_PARA_POS_Y, wk->poke.p.y + (WAZATOOL_DEF_ROTA_W_Y >> FX32_SHIFT));
		WEEffect_TCB_Delete(wk->ts.wsp, tcb);
		sys_FreeMemoryEz(wk);
	}
}

void WestSp_WE_Kaiten(WE_SYS_PTR we_sys)
{
	int num;
	
	TWE_KAITEN* wk = WET_ALLOC_MEMORY(we_sys, TWE_KAITEN);

	WT_ToolSysInit(we_sys, &wk->ts);
	
	WT_SSPointerGet(we_sys, WeSysGPWorkGet(we_sys, 0), &(wk->poke), &num);
	
	wk->poke.p.y -= WAZATOOL_DEF_ROTA_W_Y >> FX32_SHIFT;

	WazaTool_MakeDefRota(&wk->cm, WeSysGPWorkGet(we_sys, 1), WeSysGPWorkGet(we_sys, 2));
	{
		wk->cm.work[2] /= 2;
		wk->cm.work[4] /= 2;
	}
	
	WEEffect_TCB_AddPriSet(wk->ts.wsp, WeKaiten_TCB, wk);
}


///< 画面外まで移動
typedef struct {

	TWE_TOOL_SYS		ts;		///< 技エフェクト汎用構造体
	TWE_POKE_SYS		poke;	///< ポケモン汎用構造体	
	WAZATOOL_CALCMOVE	cm;		///< 汎用ワーク	

	WT_POINT			p;		///< 座標	
	WT_POINT			op;		///< 画面外座標	

} TWE_OUT_SYS;

#define WIN_OSX	(0-80)
#define WIN_OSY	(0-80)
#define WIN_OEX	(256+80)
#define WIN_OEY	(196+80)

static void WeDispOut_TCB(TCB_PTR tcb, void* work)
{
	TWE_OUT_SYS* wk = (TWE_OUT_SYS*)work;

	switch(wk->ts.seq){
	case 0:			
		if (WazaTool_CalcStraightFx(&wk->cm) == FALSE){
			wk->ts.seq++;
		}
		SoftSpriteParaSet(wk->poke.ssp, SS_PARA_POS_X, wk->cm.x);
		SoftSpriteParaSet(wk->poke.ssp, SS_PARA_POS_Y, wk->cm.y);
		break;

	default:
		WEEffect_TCB_Delete(wk->ts.wsp, tcb);
		sys_FreeMemoryEz(wk);
		break;
	}
}

void WestSp_WE_DispOut(WE_SYS_PTR we_sys)
{
	WT_POINT p;
	int mode;
	int client;
	int num;
	int wait;

	TWE_OUT_SYS* wk = WET_ALLOC_MEMORY(we_sys, TWE_OUT_SYS);

	WT_ToolSysInit(we_sys, &wk->ts);

	mode = WeSysGPWorkGet(we_sys, 0);
	wait = WeSysGPWorkGet(we_sys, 1);
	
	///< 対象取得
	switch(mode){
	case WE_TOOL_M1:
		client = WeSysATNoGet(we_sys);
		break;
	case WE_TOOL_M2:
		client = WET_AllySideClientNoGet(we_sys, WeSysATNoGet(we_sys));
		break;
	case WE_TOOL_E1:
		client = WeSysDFNoGet(we_sys);
		break;
	case WE_TOOL_E2:
		client = WET_AllySideClientNoGet(we_sys, WeSysDFNoGet(we_sys));
		break;
	default:
		GF_ASSERT(0);
		break;
	}
	
	WET_PokeDefaultPosGet_ClientNo(we_sys, client, &wk->p);

	///< SSP取得
	WT_SSPointerGet(we_sys, mode, &(wk->poke), &num);	
	
	wk->op.x = 0;
	wk->op.y = 0;
	
	///< 方向設定
	if (WET_SideCheck(wk->ts.wsp, client) == SIDE_MINE){
		wk->op.x = WIN_OSX;
	}
	else {
		wk->op.x = WIN_OEX;
	}

	WazaTool_InitStraightSyncFx(&wk->cm,
								wk->poke.p.x, wk->op.x,
								wk->poke.p.y, wk->poke.p.y, 
								wait);

	WEEffect_TCB_AddPriSet(wk->ts.wsp, WeDispOut_TCB, wk);
}

///< 画面内外操作
void WestSp_WE_DispMove(WE_SYS_PTR we_sys)
{
	WT_POINT p;
	int mode;
	int client;
	int num;
	int wait;
	int target;

	TWE_OUT_SYS* wk = WET_ALLOC_MEMORY(we_sys, TWE_OUT_SYS);

	WT_ToolSysInit(we_sys, &wk->ts);

	mode	= WeSysGPWorkGet(we_sys, 0);
	target	= WeSysGPWorkGet(we_sys, 1);
	wait	= WeSysGPWorkGet(we_sys, 2);
	
	///< 対象取得
	switch(target){
	case WE_TOOL_M1:
		client = WeSysATNoGet(we_sys);
		break;
	case WE_TOOL_M2:
		client = WET_AllySideClientNoGet(we_sys, WeSysATNoGet(we_sys));
		break;
	case WE_TOOL_E1:
		client = WeSysDFNoGet(we_sys);
		break;
	case WE_TOOL_E2:
		client = WET_AllySideClientNoGet(we_sys, WeSysDFNoGet(we_sys));
		break;
	default:
		GF_ASSERT(0);
		break;
	}
	
	WET_PokeDefaultPosGet_ClientNo(we_sys, client, &wk->p);

	///< SSP取得
	WT_SSPointerGet(we_sys, target, &(wk->poke), &num);	
	
	wk->op.x = 0;
	wk->op.y = 0;
	
	///< 方向設定
	if (WET_SideCheck(wk->ts.wsp, client) == SIDE_MINE){
		wk->op.x = WIN_OSX;
	}
	else {
		wk->op.x = WIN_OEX;
	}
	
	if (mode == 0){
		WazaTool_InitStraightSyncFx(&wk->cm,
									wk->poke.p.x, wk->op.x,
									wk->poke.p.y, wk->poke.p.y, 
									wait);
	}
	else {
		
		s16 px;
		
		px = GetWazaEffPos(we_sys, client, PM_X);
		
		WazaTool_InitStraightSyncFx(&wk->cm,
									wk->op.x, px,
									wk->poke.p.y, wk->poke.p.y, 
									wait);		
		
	}

	WEEffect_TCB_AddPriSet(wk->ts.wsp, WeDispOut_TCB, wk);	
}


///< 基本位置に表示
void WestSp_WE_DispDef(WE_SYS_PTR we_sys)
{
	int mode;
	int client;
	int num;
	WT_POINT p;
	TWE_POKE_SYS poke;

	mode = WeSysGPWorkGet(we_sys, 0);
	
	///< 対象取得
	switch(mode){
	case WE_TOOL_M1:
		client = WeSysATNoGet(we_sys);
		break;
	case WE_TOOL_M2:
		client = WET_AllySideClientNoGet(we_sys, WeSysATNoGet(we_sys));
		break;
	case WE_TOOL_E1:
		client = WeSysDFNoGet(we_sys);
		break;
	case WE_TOOL_E2:
		client = WET_AllySideClientNoGet(we_sys, WeSysDFNoGet(we_sys));
		break;
	default:
		GF_ASSERT(0);
		break;
	}


	WET_PokeDefaultPosGet_ClientNo(we_sys, client, &p);

	///< SSP取得
	WT_SSPointerGet(we_sys, mode, &poke, &num);

	{	
		s16 height = WeSysPokeOfsGet(we_sys, client);

		SoftSpriteParaSet(poke.ssp, SS_PARA_POS_X, p.x);
		SoftSpriteParaSet(poke.ssp, SS_PARA_POS_Y, p.y + height);
	}
}

/*
 * we_sys.work[0]			対象ポケモン WE_TOOL_M1 ... (1つしか指定できません)
 * we_sys.work[1]	wait	計算待ち時間
 * we_sys.work[2]	num		点滅数
 * we_sys.work[3]	color	変更後の色
 * we_sys.work[4]	evy_max	最大のフェード色割合(16段階)
*/

typedef struct {

	TWE_TOOL_SYS		ts;		///< 技エフェクト汎用構造体
	TWE_POKE_SYS		poke;	///< ポケモン汎用構造体	
	PAL_SFS_PTR			ps;
	
} TWE_OAM_FADE;

static void OamPalFade_TCB(TCB_PTR tcb, void* work)
{
	TWE_OAM_FADE* wk = (TWE_OAM_FADE*)work;
	
	
	if (IsPaletteSoftFade(wk->ps) == FALSE){
		PaletteSoftFadeDelete(wk->ps);
		WEEffect_TCB_Delete(wk->ts.wsp, tcb);
		sys_FreeMemoryEz(wk);
	}
}

void WestSp_WE_OAM_PalFade(WE_SYS_PTR we_sys)
{
	int num;

	TWE_OAM_FADE* wk = WET_ALLOC_MEMORY(we_sys, TWE_OAM_FADE);
	
	WT_ToolSysInit(we_sys, &wk->ts);
	
	{
		int pal_pos;
		int mode	= WeSysGPWorkGet(we_sys, 0);
		int wait	= WeSysGPWorkGet(we_sys, 1);
		int param	= WeSysGPWorkGet(we_sys, 2);
		int start	= WeSysGPWorkGet(we_sys, 3);
		int end		= WeSysGPWorkGet(we_sys, 4);
		int col		= WeSysGPWorkGet(we_sys, 5);
		WT_CAPointerGet(we_sys, mode, &(wk->poke), &num);
		
		pal_pos = GetPlttProxyOffset(CLACT_PaletteProxyGet(wk->poke.cap->act), NNS_G2D_VRAM_TYPE_2DMAIN);

		wk->ps = PaletteSoftFade(wk->ts.pfd, WeSysHeapAreaGet(we_sys), FADE_MAIN_OBJ,
								 pal_pos * 16, 16, wait, param, start, end, col, TCBPRI_WE_SUPPORT);
	}
	
	WEEffect_TCB_AddPriSet(wk->ts.wsp, OamPalFade_TCB, wk);
}



///< 可変表示しすてむ

typedef struct {

	TWE_TOOL_SYS		ts;		///< 技エフェクト汎用構造体
	TWE_POKE_SYS		poke;	///< ポケモン汎用構造体	
	
	int 				ofs_x;	///< GP からもらう
	int 				ofs_y;
	int					siz_x;
	int					siz_y;
	s16					ch_x;
	s16					ch_y;
	int					wait;
	int					type;

	int					count;	///< GP からもらわない
	
	int pos_y;
	int height;
	
} TWE_VS;

static void VS_TCB(TCB_PTR tcb, void* work)
{
	TWE_VS* wk = (TWE_VS*)work;
	
	switch(wk->ts.seq){
	case 0:
		{
			if ((++wk->count) < wk->wait){ return; }
			
			wk->count = 0;
					
			if (wk->type == 0){
				if(wk->height < 0){
					wk->height = 0;
				}
				if(wk->height == 0){
					wk->ts.seq++;
				}
			}
			else {
				if(wk->height > SOFT_SPRITE_SIZE_Y){
					wk->height = SOFT_SPRITE_SIZE_Y;
				}
				if(wk->height == SOFT_SPRITE_SIZE_Y){
					wk->ts.seq++;
				}
			}
			SoftSpriteParaSet(wk->poke.ssp, SS_PARA_OFS_SIZE_Y, wk->height);
			SoftSpriteParaSet(wk->poke.ssp, SS_PARA_POS_Y,		wk->pos_y);

			wk->pos_y  -= wk->ch_y;
			wk->height += wk->ch_y;
		}
		break;
	default:
		SoftSpriteDefaultScaleSet(wk->poke.ssp);
		WEEffect_TCB_Delete(wk->ts.wsp, tcb);
		sys_FreeMemoryEz(wk);
		break;
	}
}

void WestSp_WE_VisibleSet(WE_SYS_PTR we_sys)
{
	TWE_VS* wk = WET_ALLOC_MEMORY(we_sys, TWE_VS);
	
	WT_ToolSysInit(we_sys, &wk->ts);
	
	{
		int mode = WeSysGPWorkGet(we_sys, 0);
		int num;
		int client;
	
		WT_SSPointerGet(we_sys, mode, &(wk->poke), &num);
		
		switch(mode){
		case WE_TOOL_M1:
			client = WeSysATNoGet(we_sys);
			break;
		case WE_TOOL_M2:
			client = WET_AllySideClientNoGet(we_sys, WeSysATNoGet(we_sys));
			break;
		case WE_TOOL_E1:
			client = WeSysDFNoGet(we_sys);
			break;
		case WE_TOOL_E2:
			client = WET_AllySideClientNoGet(we_sys, WeSysDFNoGet(we_sys));
			break;
		default:
			GF_ASSERT(0);
			break;
		}
		
		wk->type = WeSysGPWorkGet(we_sys, 1);
		if (wk->type == 0){
			wk->pos_y = SoftSpriteParaGet(wk->poke.ssp, SS_PARA_POS_Y);
			wk->height= SOFT_SPRITE_SIZE_Y - SoftSpriteParaGet(wk->poke.ssp, SS_PARA_OFS_SIZE_Y);
			wk->ch_x  = WeSysGPWorkGet(we_sys, 2);
			wk->ch_y  = WeSysGPWorkGet(we_sys, 3);
			wk->ch_y *= -1;
		}
		else {
			wk->pos_y = SoftSpriteParaGet(wk->poke.ssp, SS_PARA_POS_Y);
			wk->height= SoftSpriteParaGet(wk->poke.ssp, SS_PARA_OFS_SIZE_Y);
			wk->ch_x  = WeSysGPWorkGet(we_sys, 2);
			wk->ch_y  = WeSysGPWorkGet(we_sys, 3);
		}
		wk->ofs_x = 0;
		wk->ofs_y = 0;
		wk->siz_x = SOFT_SPRITE_SIZE_X;
		wk->siz_y = SOFT_SPRITE_SIZE_Y - WeSysPokeOfsGet(we_sys, client);
		wk->wait  = WeSysGPWorkGet(we_sys, 4);
		wk->count = 0;

		SoftSpriteVisibleSet(wk->poke.ssp, wk->ofs_x, wk->ofs_y, wk->siz_x, wk->siz_y);
	}

	WEEffect_TCB_AddPriSet(wk->ts.wsp, VS_TCB, wk);
}

// -----------------------------------------
//
//	□矩形範囲可視
//
// -----------------------------------------
typedef struct {

	TWE_TOOL_SYS	ts;
	
	s16				my;
	int				wait;
	int				cnt;
	
	///< ポケモン操作用
	TWE_POKE_SYS	poke;
	int				height;
	int				height_buf;
	int				pos_y;
	int				pos_y_buf;
	
	int				type;
	
} TRECT_VIEW;


static int ClientNo_Get(WE_SYS_PTR we_sys, int mode);
static int ClientNo_Get(WE_SYS_PTR we_sys, int mode)
{	
	int client = 0;

	switch(mode){
	case WE_TOOL_M1:
		client = WeSysATNoGet(we_sys);
		break;
	case WE_TOOL_M2:
		client = WET_AllySideClientNoGet(we_sys, WeSysATNoGet(we_sys));
		break;
	case WE_TOOL_E1:
		client = WeSysDFNoGet(we_sys);
		break;
	case WE_TOOL_E2:
		client = WET_AllySideClientNoGet(we_sys, WeSysDFNoGet(we_sys));
		break;
	default:
		GF_ASSERT(0);
		break;
	}
	
	return client;
}


static void RectViewUp_TCB(TCB_PTR tcb, void* work)
{
	TRECT_VIEW* wk = (TRECT_VIEW*)work;
	
	switch(wk->ts.seq){
	case 0:
		if ((++wk->cnt) < wk->wait){ break; }
		wk->cnt = 0;
		
		wk->pos_y += wk->my;
		SoftSpriteParaSet(wk->poke.ssp, SS_PARA_POS_Y, wk->pos_y);
		
		wk->height -= wk->my;
		if(wk->height > wk->height_buf){
			wk->height = wk->height_buf;
			wk->ts.seq++;
		}
		SoftSpriteParaSet(wk->poke.ssp, SS_PARA_OFS_SIZE_Y, wk->height);	
		break;
	case 1:
		SoftSpriteParaSet(wk->poke.ssp, SS_PARA_VISIBLE, 0);
		SoftSpriteParaSet(wk->poke.ssp, SS_PARA_POS_Y, wk->pos_y_buf);
		SoftSpriteParaSet(wk->poke.ssp, SS_PARA_OFS_SIZE_Y, wk->height_buf);
		SoftSpriteDefaultScaleSet(wk->poke.ssp);
		WEEffect_TCB_Delete(wk->ts.wsp, tcb);
		sys_FreeMemoryEz(wk);
		break;
	}
}

static void RectViewDown_TCB(TCB_PTR tcb, void* work)
{
	TRECT_VIEW* wk = (TRECT_VIEW*)work;	

	switch(wk->ts.seq){
	case 0:
		if ((++wk->cnt) < wk->wait){ break; }
		wk->cnt = 0;
		
		wk->pos_y += wk->my;
		SoftSpriteParaSet(wk->poke.ssp, SS_PARA_POS_Y, wk->pos_y);
		
		wk->height -= wk->my;
		if(wk->height < 0){
			wk->height = 0;
			wk->ts.seq++;
		}
		SoftSpriteParaSet(wk->poke.ssp, SS_PARA_OFS_SIZE_Y, wk->height);
		break;
	case 1:
		SoftSpriteParaSet(wk->poke.ssp, SS_PARA_VISIBLE, 0);
		SoftSpriteParaSet(wk->poke.ssp, SS_PARA_POS_Y, wk->pos_y_buf);
		SoftSpriteParaSet(wk->poke.ssp, SS_PARA_OFS_SIZE_Y, wk->height_buf);
		SoftSpriteDefaultScaleSet(wk->poke.ssp);
		WEEffect_TCB_Delete(wk->ts.wsp, tcb);
		sys_FreeMemoryEz(wk);
		break;
	}
}

static void RectViewPaint_TCB(TCB_PTR tcb, void* work)
{
	TRECT_VIEW* wk = (TRECT_VIEW*)work;	

	switch(wk->ts.seq){
	case 0:
		if ((++wk->cnt) < wk->wait){ break; }
		wk->cnt = 0;
	
		wk->height -= wk->my;
		wk->height_buf += wk->my;
		if(wk->height < 0){
			wk->height = 0;
			wk->ts.seq++;
		}
		
		SoftSpriteVisibleSet(wk->poke.ssp, 0, wk->height, SOFT_SPRITE_SIZE_X, wk->height_buf);
		break;
		
	case 1:
		SoftSpriteParaSet(wk->poke.ssp, SS_PARA_VISIBLE, 0);
		SoftSpriteDefaultScaleSet(wk->poke.ssp);
		WEEffect_TCB_Delete(wk->ts.wsp, tcb);
		sys_FreeMemoryEz(wk);
		break;
	}
}

void WSP_RectView(WE_SYS_PTR we_sys)
{
	TRECT_VIEW* wk;
	int client;
	
	wk = WET_ALLOC_MEMORY(we_sys, TRECT_VIEW);
	
	WT_ToolSysInit(we_sys, &wk->ts);
	
//	wk->my = WeSysGPWorkGet(we_sys, 2);		///< x
	wk->my = WeSysGPWorkGet(we_sys, 3);		///< y
	wk->wait = WeSysGPWorkGet(we_sys, 4);	///< wait
	
	
	///< ポケモンデータを設定する
	{
		int mode = WeSysGPWorkGet(we_sys, 0);
		int num;
		
		WT_SSPointerGet(we_sys, mode, &(wk->poke), &num);
		
		client = ClientNo_Get(we_sys, mode);
	}
	
	if (WeSysGPWorkGet(we_sys, 5) != 0){
		wk->height = WeSysPokeOfsGet(we_sys, client);
		wk->height = SOFT_SPRITE_SIZE_Y - wk->height;
		wk->height_buf = 0;
		
		SoftSpriteVisibleSet(wk->poke.ssp, 0, wk->height, SOFT_SPRITE_SIZE_X, wk->height_buf);
		
		WEEffect_TCB_AddPriSet(wk->ts.wsp, RectViewPaint_TCB, wk);
		return;
	}
	
	wk->pos_y  = SoftSpriteParaGet(wk->poke.ssp, SS_PARA_POS_Y);
	wk->pos_y_buf = wk->pos_y;
	
	wk->height = WeSysPokeOfsGet(we_sys, client);
	wk->height = SOFT_SPRITE_SIZE_Y - wk->height;
	wk->height_buf = wk->height;
	
	if (wk->my > 0){
		SoftSpriteVisibleSet(wk->poke.ssp, 0, 0, SOFT_SPRITE_SIZE_X, wk->height);
		WEEffect_TCB_AddPriSet(wk->ts.wsp, RectViewDown_TCB, wk);
	}
	else {
		wk->height = 0;
		wk->pos_y  += wk->height_buf;
		SoftSpriteParaSet(wk->poke.ssp, SS_PARA_POS_Y, wk->pos_y);
		SoftSpriteVisibleSet(wk->poke.ssp, 0, 0, SOFT_SPRITE_SIZE_X, wk->height);
		WEEffect_TCB_AddPriSet(wk->ts.wsp, RectViewUp_TCB, wk);
	}
}


// -----------------------------------------
//
//
//		[ __WE_BgShake__ ]	
//
//
// -----------------------------------------
typedef struct {
	SOFT_SPRITE* ssp;
	CATS_ACT_PTR cap;
	s16	def_x;	
	s16	def_y;	
} TWE_BgShake_POKE;

typedef struct {
	u8	seq;
	u8	step;
	u8	fade;
	u8	wait;
	
	int shake_pow_x;
	int shake_pow_y;
	int shake_sync;
	int shake_num;
	int num;
	int num_max;
	int frame;
	
	int old_x;
	int old_y;

	GF_BGL_INI*		bgl;
	WE_SYS_PTR		wsp;
	CATS_RES_PTR	crp;
	
	TWE_POKE_SYS	poke[ WE_POKE_DATA_MAX ];
	TWE_POKE_SYS	poke2[ WE_POKE_DATA_MAX ];
	
	WAZATOOL_CALCMOVE shake;
	
} TWE_BgShake_SYS;

static const s16 weBgShake_shake[] = { 12, 10, 8, 6, 4, 2, 1, 0 };

#define WEBgShake_STEP_NUM	(NELEMS(weBgShake_shake))
#define WEBgShake_COL_BLACK	(WEDEF_COLOR_BLACK)
#define WEBgShake_COL_WHITE	(WEDEF_COLOR_WHITE)


//--------------------------------------------------------------
/**
 * @brief	動作TCB
 *
 * @param	tcb	
 * @param	work	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WeBgShake_TCB(TCB_PTR tcb, void* work)
{
	int i;
	TWE_BgShake_SYS* wk = (TWE_BgShake_SYS*)work;
	
	switch(wk->seq){
	case 0:
		///< ゆれ幅初期化
		WazaTool_InitShake(&wk->shake, wk->shake_pow_x, wk->shake_pow_y, wk->shake_sync, wk->shake_num);
		wk->seq++;

	case 1:
		///< ゆれ
		{
			if (WazaTool_CalcShake(&wk->shake) == FALSE){
				if (wk->step >= wk->num_max){
					wk->seq++;
				}
				else {
					wk->seq--;
				}
				if (wk->old_x != 0){
					GF_BGL_ScrollSet(wk->bgl, wk->frame, GF_BGL_SCROLL_X_SET, 0);
				}
				if (wk->old_y != 0){
					GF_BGL_ScrollSet(wk->bgl, wk->frame, GF_BGL_SCROLL_Y_SET, 0);
				}
				wk->step++;
			}
			else {
				if (wk->shake.x != 0){
					wk->old_x = 1;
					GF_BGL_ScrollSet(wk->bgl, wk->frame, GF_BGL_SCROLL_X_SET, wk->shake.x);
				}
				if (wk->shake.y != 0){
					wk->old_y = 1;
					GF_BGL_ScrollSet(wk->bgl, wk->frame, GF_BGL_SCROLL_Y_SET, wk->shake.y);
				}
			}
		}
		break;
	
	default:
		///< 終了処理
		WEEffect_TCB_Delete(wk->wsp, tcb);
		sys_FreeMemoryEz(wk);
		break;
	}
}

//--------------------------------------------------------------
/**
 * @brief	呼び出し関数
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WestSp_WE_BgShake(WE_SYS_PTR we_sys)
{
	int i;
	TWE_BgShake_SYS* wk;
	
	wk = WET_ALLOC_MEMORY(we_sys, TWE_BgShake_SYS);

	wk->seq		= 0;
	wk->step	= 0;
	wk->wsp		= we_sys;
	wk->crp		= WeSysPokeCrpGet(wk->wsp);
	wk->bgl		= WeSysBGLPointerGet(wk->wsp);
	
	
	wk->shake_pow_x = WeSysGPWorkGet(we_sys, 0);
	wk->shake_pow_y = WeSysGPWorkGet(we_sys, 1);
	wk->shake_sync  = WeSysGPWorkGet(we_sys, 2);
	wk->shake_num   = WeSysGPWorkGet(we_sys, 3);
	wk->num_max     = WeSysGPWorkGet(we_sys, 4);
	if (WeSysGPWorkGet(we_sys, 5) == 0){
		wk->frame = BATTLE_FRAME_BACKGROUND;
	}
	else {
		wk->frame = BATTLE_FRAME_EFFECT;
	}

	WEEffect_TCB_AddPriSet(wk->wsp, WeBgShake_TCB, wk);
}


typedef struct {

	TWE_TOOL_SYS	ts;
	
	CATS_ACT_PTR	cap;
	
	s16				add;
	
	int				h;
	int				v;
	int				end;
	
	
} WSP_MOSAIC;

static void Mosaic_TCB(TCB_PTR tcb, void* work)
{
	WSP_MOSAIC* wk = work;
	
	if (wk->h == wk->end
	||	wk->v == wk->end){
		WEEffect_TCB_Delete(wk->ts.wsp, tcb);
		sys_FreeMemoryEz(wk);
		return;	
	}
	
	if (wk->add < 0){
		
		if (wk->h + wk->add  > 0){
			wk->h += wk->add;
			wk->v += wk->add;
		}
		else {
			wk->h = wk->end;
			wk->v = wk->end;
		}
	}
	else {
		if (wk->h + wk->add  < 15){
			wk->h += wk->add;
			wk->v += wk->add;
		}
		else {
			wk->h = wk->end;
			wk->v = wk->end;
		}
	}
	
	CATS_ObjectUpdateCap(wk->cap);
	
	G2_SetOBJMosaicSize(wk->h, wk->v);
	
	CATS_Draw(wk->ts.poke_crp);
}

void WSP_Mosaic(WE_SYS_PTR we_sys)
{

	WSP_MOSAIC* wk;
	int client;
	
	wk = WET_ALLOC_MEMORY(we_sys, WSP_MOSAIC);
	
	WT_ToolSysInit(we_sys, &wk->ts);
	
	wk->add = WeSysGPWorkGet(wk->ts.wsp, 1);
	wk->h	= WeSysGPWorkGet(wk->ts.wsp, 2);
	wk->v	= WeSysGPWorkGet(wk->ts.wsp, 3);
	
	wk->cap = WeSysPokeCapGet(wk->ts.wsp, WeSysGPWorkGet(wk->ts.wsp, 0));
	CATS_ObjectEnableCap(wk->cap, CATS_ENABLE_TRUE);
	
	if (wk->add < 0){
		wk->end = 0;
	}
	else {
		wk->end = 15;
	}
	
	CATS_ObjectMosaicSet(wk->cap, TRUE);
	
	{
		TCB_PTR tcb;
		
		tcb = WEEffect_TCB_AddPriSet(wk->ts.wsp, Mosaic_TCB, wk);
	
		Mosaic_TCB(tcb, wk);
	}
}


//--------------------------------------------------------------
/**
 * @brief	エミッターを移動させる
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
typedef struct {
	
	int				emit_id;					///< どのエミッタか
	s16				wait;						///< 何フレ後に開始するか
	s16				time;						///< どの期間かけて移動するか
	int				height;						///< 高さ
	WT_POINT		ofs;						///< ある程度のブレ幅
	
	int				target;
	
	int				s_client;
	int				e_client;
	
	int				loop_cnt;					///< 
	int				dmy_loop;					///< から回し回数
	int				stop_loop;					///< 回さなくなる位置
	
	int				wait_now;
	int				rad;
	int 			curv;
	
	PTC_PTR			ptc;						///< ptc
	EMIT_PTR		emit;						///< 動作するTCB
	
	TWE_TOOL_SYS	ts;
	
	TWE_POKE_SYS	poke[ WE_POKE_DATA_MAX ];	///< poke
	
	///< 計算用
	WAZATOOL_CALCMOVE		cm[2];
	WAZATOOL_CALCMOVE_ONE	rd;
	
	
} EMIT_MOVE_SYS;

///< 引数取り出し
static void EmitMove_Init(WE_SYS_PTR we_sys, EMIT_MOVE_SYS* wk)
{
	wk->emit_id = WeSysGPWorkGet(we_sys, 0);
	wk->ofs.x	= WeSysGPWorkGet(we_sys, 1);
	wk->ofs.y	= WeSysGPWorkGet(we_sys, 2);
	wk->wait	= WeSysGPWorkGet(we_sys, 3);
	wk->time	= WeSysGPWorkGet(we_sys, 4);
	wk->height	= WeSysGPWorkGet(we_sys, 5);
	wk->target	= WeSysGPWorkGet(we_sys, 6);
	wk->curv	= WeSysGPWorkGet(we_sys, 8);
	
	{
		int para = WeSysGPWorkGet(we_sys, 7);
		
		wk->loop_cnt  = 0;
		wk->dmy_loop  = (para & 0xFFFF0000) >> 16;
		wk->stop_loop = (para & 0x0000FFFF);
		
		if (wk->dmy_loop == 0){
			wk->dmy_loop = 0;
		}
		if (wk->stop_loop == 0){
			wk->stop_loop = 0xFF;
		}
	}
	
	wk->emit	= WeSysEMITPointerGet(we_sys, wk->emit_id);
	wk->ptc		= WeSysPTCPointerGet(we_sys);
	
	if (wk->target == 0){
		wk->s_client = WeSysATNoGet(we_sys);
		wk->e_client = WeSysDFNoGet(we_sys);
	}
	else if (wk->target == 1){
		wk->s_client = WeSysDFNoGet(we_sys);
		wk->e_client = WeSysATNoGet(we_sys);
	}
	else {
		GF_ASSERT("emitter move = target none\n");
	}
	
	if (wk->emit == NULL){
		GF_ASSERT(0);
	}
}

// -----------------------------------------
//
//	パーティクルの寿命を待つ
//
//	リンクリストの末端に最後のパーティクルが存在するをことを期待している･･･。
//	コレで良いのか不明。
//
// -----------------------------------------
static BOOL Is_ParticleActive(EMIT_PTR emit)
{
	BOOL active;
	
	active = FALSE;
	{
		SPLParticle* spl;
		int age;
		int life;
		
		spl = SPL_GetHeadParticle(emit);			///< 先頭のパーティクルを取得
		
		while(spl != NULL){
			
			age  = SPL_GetParticleAge(spl);			///< 年齢取得
			life = SPL_GetParticleLife(spl);		///< 寿命取得
			spl  = SPL_GetNextParticle(spl);		///< 次のパーティクル取得
		}
		
		if (age != life){							///< 最後の生存パーティクルの状態を取得
			active = TRUE;
		}
	}
	
	return active;	
}

static void WSP_Straight_TCB(TCB_PTR tcb, void* work)
{
	EMIT_MOVE_SYS* wk = work;
	BOOL active;
	
	active = Is_ParticleActive(wk->emit);
	
	if (wk->wait_now < wk->wait){
		wk->wait_now++;
		return;
	}
	
	if (WazaTool_CalcStraightFx(&wk->cm[0]) == FALSE && active == FALSE){
		Particle_EmitterDelete(wk->ptc, wk->emit);
		WEEffect_TCB_Delete(wk->ts.wsp, tcb);
		WET_SAFE_RELEASE(wk);
		return;
	}
	else {
		if ((wk->dmy_loop  > wk->loop_cnt
		||	wk->stop_loop < wk->loop_cnt)
		&&	wk->stop_loop != 255){
			return;
		}
		
		SPL_SetEmitterPositionX(wk->emit, wk->cm[0].x * PT_LCD_DOT);
		SPL_SetEmitterPositionY(wk->emit, wk->cm[0].y * PT_LCD_DOT);
		
		if (wk->curv){
			wk->rad += (360 / (wk->time));
			SPL_SetEmitterPositionY(wk->emit, (wk->cm[0].y * PT_LCD_DOT) + Sin360R(wk->rad));
		}
	}
}

///< 直線移動
void WSP_Emitter_Straight(WE_SYS_PTR we_sys)
{
	int r_vec;
	VecFx32 p1;
	VecFx32 p2;
	EMIT_MOVE_SYS* wk;
	
	wk = WET_ALLOC_MEMORY(we_sys, EMIT_MOVE_SYS);
	
	WT_ToolSysInit(we_sys, &wk->ts);
	
	EmitMove_Init(we_sys, wk);
	
	r_vec = WazaTool_VecChangeX(we_sys, WeSysATNoGet(we_sys));
#if 0
	wk->poke[ 0 ].ssp = WeSysSoftSpritePointerGet(we_sys, wk->s_client);
	wk->poke[ 1 ].ssp = WeSysSoftSpritePointerGet(we_sys, wk->e_client);
	WT_SSP_PointGet(wk->poke[ 0 ].ssp, &wk->poke[ 0 ].p);
	WT_SSP_PointGet(wk->poke[ 1 ].ssp, &wk->poke[ 1 ].p);
#endif	
	WET_PokeParticlePosGet(we_sys, wk->s_client, &p1);
	WET_PokeParticlePosGet(we_sys, wk->e_client, &p2);
	
	WazaTool_InitStraightSyncFx(
						  &wk->cm[0], 
						  (p1.x / PT_LCD_DOT),
						  (p2.x / PT_LCD_DOT) + (wk->ofs.x * r_vec),
						  (p1.y / PT_LCD_DOT),
						  (p2.y / PT_LCD_DOT) + (wk->ofs.y * r_vec),
						  wk->time);

	if (r_vec > 0){
		WazaTool_InitMoveOneSync(&wk->rd, FX_GET_ROTA_NUM(20) * r_vec, FX_GET_ROTA_NUM(130) * r_vec, 10);
	}
	else {
		WazaTool_InitMoveOneSync(&wk->rd, FX_GET_ROTA_NUM(90) * r_vec, FX_GET_ROTA_NUM(130) * r_vec, 10);
	}
	
	
	{
		int i;
		
		for (i = 0; i < wk->dmy_loop; i++){
			WazaTool_CalcStraightFx(&wk->cm[0]);
		}
		if (wk->stop_loop != 0xFF){
			wk->loop_cnt = wk->stop_loop + 1;
		}
		
		SPL_SetEmitterPositionX(wk->emit, wk->cm[0].x * PT_LCD_DOT);
		SPL_SetEmitterPositionY(wk->emit, wk->cm[0].y * PT_LCD_DOT);
	}

	WEEffect_TCB_AddPriSet(wk->ts.wsp, WSP_Straight_TCB, wk);
}

///< 上下
void WSP_Emitter_SimpleUD(WE_SYS_PTR we_sys)
{
	VecFx32 p1;
	VecFx32 p2;
	int mode;
	EMIT_MOVE_SYS* wk;
	
	wk = WET_ALLOC_MEMORY(we_sys, EMIT_MOVE_SYS);
	WT_ToolSysInit(we_sys, &wk->ts);
	
	wk->emit_id = WeSysGPWorkGet(we_sys, 0);
	wk->target	= WeSysGPWorkGet(we_sys, 1);
	mode		= WeSysGPWorkGet(we_sys, 2);
	wk->time	= WeSysGPWorkGet(we_sys, 3);
	wk->wait	= WeSysGPWorkGet(we_sys, 4);
	wk->wait_now = 0;
	{
		int para = WeSysGPWorkGet(we_sys, 5);
		
		wk->loop_cnt  = 0;
		wk->dmy_loop  = (para & 0xFFFF0000) >> 16;
		wk->stop_loop = (para & 0x0000FFFF);
		
		if (wk->dmy_loop == 0){
			wk->dmy_loop = 0;
		}
		if (wk->stop_loop == 0){
			wk->stop_loop = 0xFF;
		}		
		
	}
	
	wk->emit	= WeSysEMITPointerGet(we_sys, wk->emit_id);
	wk->ptc		= WeSysPTCPointerGet(we_sys);
	
	if (wk->target == 0){
		wk->s_client = WeSysATNoGet(we_sys);
		wk->e_client = WeSysATNoGet(we_sys);
	}
	else {
		wk->s_client = WeSysDFNoGet(we_sys);
		wk->e_client = WeSysDFNoGet(we_sys);
	}
	
	if (wk->emit == NULL){
		GF_ASSERT(0);
	}
	
	WET_PokeParticlePosGet(we_sys, wk->s_client, &p1);
	WET_PokeParticlePosGet(we_sys, wk->e_client, &p2);
	if (mode == 0){
		WET_PokeParticleDispOutTopGet(&p1);
		p1.x = p2.x;
	}
	else {
		WET_PokeParticleDispOutTopGet(&p2);
		p2.x = p1.x;
	}
	
	
	WazaTool_InitStraightSyncFx(
						  &wk->cm[0], 
						  (p1.x / PT_LCD_DOT),
						  (p2.x / PT_LCD_DOT),
						  (p1.y / PT_LCD_DOT),
						  (p2.y / PT_LCD_DOT),
						  wk->time);
	{
		int i;
		
		for (i = 0; i < wk->dmy_loop; i++){
			WazaTool_CalcStraightFx(&wk->cm[0]);
		}
		if (wk->stop_loop != 0xFF){
			wk->loop_cnt = wk->stop_loop + 1;
		}
		SPL_SetEmitterPositionX(wk->emit, wk->cm[0].x * PT_LCD_DOT);
		SPL_SetEmitterPositionY(wk->emit, (wk->cm[0].y * PT_LCD_DOT));
	}
	
	WEEffect_TCB_AddPriSet(wk->ts.wsp, WSP_Straight_TCB, wk);	
}


static void WSP_Parabolic_TCB(TCB_PTR tcb, void* work)
{
	EMIT_MOVE_SYS* wk = work;
	BOOL active;
	
	active = Is_ParticleActive(wk->emit);
	
	if (WazaTool_CalcCurveFx(&wk->cm[0], &wk->cm[1]) == FALSE && active == FALSE){
		Particle_EmitterDelete(wk->ptc, wk->emit);
		WEEffect_TCB_Delete(wk->ts.wsp, tcb);
		WET_SAFE_RELEASE(wk);
		return;
	}
	else {
		SPL_SetEmitterPositionX(wk->emit, wk->cm[0].x * PT_LCD_DOT);
		SPL_SetEmitterPositionY(wk->emit, wk->cm[0].y * PT_LCD_DOT);
	}
}

///< 放物線移動
void WSP_Emitter_Parabolic(WE_SYS_PTR we_sys)
{
	int r_vec;
	VecFx32 p1;
	VecFx32 p2;
	EMIT_MOVE_SYS* wk;
	
	wk = WET_ALLOC_MEMORY(we_sys, EMIT_MOVE_SYS);
	
	WT_ToolSysInit(we_sys, &wk->ts);
	
	EmitMove_Init(we_sys, wk);
	
	r_vec = WazaTool_VecChangeX(we_sys, WeSysATNoGet(we_sys));
#if 0	
	wk->poke[ 0 ].ssp = WeSysSoftSpritePointerGet(we_sys, wk->s_client);
	wk->poke[ 1 ].ssp = WeSysSoftSpritePointerGet(we_sys, wk->e_client);
	WT_SSP_PointGet(wk->poke[ 0 ].ssp, &wk->poke[ 0 ].p);
	WT_SSP_PointGet(wk->poke[ 1 ].ssp, &wk->poke[ 1 ].p);
#endif	
	WET_PokeParticlePosGet(we_sys, wk->s_client, &p1);
	WET_PokeParticlePosGet(we_sys, wk->e_client, &p2);
	
	/// --- 放物線
	WazaTool_InitCurveYFx(&wk->cm[0],
						  &wk->cm[1], 
						  (p1.x / PT_LCD_DOT),
						  (p2.x / PT_LCD_DOT) + (wk->ofs.x * r_vec),
						  (p1.y / PT_LCD_DOT),
						  (p2.y / PT_LCD_DOT) + (wk->ofs.y * r_vec),
						  wk->time, (wk->height * -FX32_ONE));
						  
	if (r_vec > 0){
		WazaTool_InitMoveOneSync(&wk->rd, FX_GET_ROTA_NUM(20) * r_vec, FX_GET_ROTA_NUM(130) * r_vec, 10);
	}
	else {
		WazaTool_InitMoveOneSync(&wk->rd, FX_GET_ROTA_NUM(90) * r_vec, FX_GET_ROTA_NUM(130) * r_vec, 10);
	}
	
	{
		int i;
		
		for (i = 0; i < wk->dmy_loop; i++){
			WazaTool_CalcCurveFx(&wk->cm[0], &wk->cm[1]);
		}
		if (wk->stop_loop != 0xFF){
			wk->loop_cnt = wk->stop_loop + 1;
		}
		
		SPL_SetEmitterPositionX(wk->emit, wk->cm[0].x * PT_LCD_DOT);
		SPL_SetEmitterPositionY(wk->emit, wk->cm[0].y * PT_LCD_DOT);
	}
	
	WEEffect_TCB_AddPriSet(wk->ts.wsp, WSP_Parabolic_TCB, wk);
}

typedef struct {
	
	int				emit_id;					///< どのエミッタか	
	int				s_rad_x;					///< 開始角
	int				s_rad_y;
	int				e_rad_x;					///< 終了角
	int				e_rad_y;
	int				r_x;						///< 半径
	int				r_y;
	int				wait;
	int				target;
	
	int				s_client;
	
	int				loop_cnt;					///< 
	int				dmy_loop;					///< から回し回数
	int				stop_loop;					///< 回さなくなる位置
	
	PTC_PTR			ptc;						///< ptc
	EMIT_PTR		emit;						///< 動作するTCB
	
	TWE_TOOL_SYS	ts;
	
	WAZATOOL_CALCMOVE wtc;
	VecFx32 def_ofs;
	VecFx32 pos;
	
} EMIT_MOVE_SYS_2;

///< 回転
static void WSP_Rotation_TCB(TCB_PTR tcb, void* work)
{
	EMIT_MOVE_SYS_2* wk = work;
	
	BOOL active;
	
	active = Is_ParticleActive(wk->emit);
	
	if( WazaTool_CalcRotaFx(&wk->wtc) == FALSE && active == FALSE){
		Particle_EmitterDelete(wk->ptc, wk->emit);
		WEEffect_TCB_Delete(wk->ts.wsp, tcb);
		sys_FreeMemoryEz(wk);
	}
	else {
		VecFx32 ofs;
		ofs.x = wk->pos.x + (wk->wtc.x * PT_LCD_DOT);
		ofs.y = wk->pos.y + (wk->wtc.y * PT_LCD_DOT);
		SPL_SetEmitterPositionX(wk->emit, ofs.x);
		SPL_SetEmitterPositionY(wk->emit, ofs.y);
	}
}

///< 回転移動
void WSP_Emitter_Rotation(WE_SYS_PTR we_sys)
{
	EMIT_MOVE_SYS_2* wk;
	
	wk = WET_ALLOC_MEMORY(we_sys, EMIT_MOVE_SYS_2);
	
	WT_ToolSysInit(we_sys, &wk->ts);
	
	wk->emit_id = WeSysGPWorkGet(we_sys, 0);
	wk->s_rad_x = WeSysGPWorkGet(we_sys, 1);
	wk->e_rad_x = WeSysGPWorkGet(we_sys, 2);
	wk->s_rad_y = WeSysGPWorkGet(we_sys, 3);
	wk->e_rad_y = WeSysGPWorkGet(we_sys, 4);
	wk->r_x		= WeSysGPWorkGet(we_sys, 5);
	wk->r_y		= WeSysGPWorkGet(we_sys, 6);
	wk->wait	= WeSysGPWorkGet(we_sys, 7);
	wk->target	= WeSysGPWorkGet(we_sys, 8);
	
	if (wk->target == 0){
		wk->s_client = WeSysATNoGet(we_sys);
	}
	else {
		wk->s_client = WeSysDFNoGet(we_sys);
	}
	
	WET_PokeParticlePosGet(we_sys, wk->s_client, &wk->pos);
	
	wk->emit	= WeSysEMITPointerGet(we_sys, wk->emit_id);
	wk->ptc		= WeSysPTCPointerNoGet(we_sys, WeSysGPWorkGet(we_sys, 9));


	WazaTool_InitRotaFx(&wk->wtc,
			FX_GET_ROTA_NUM(wk->s_rad_x), FX_GET_ROTA_NUM(wk->e_rad_x),
			FX_GET_ROTA_NUM(wk->s_rad_y), FX_GET_ROTA_NUM(wk->e_rad_y),
			wk->r_x * FX32_ONE,
			wk->r_y * FX32_ONE,
			wk->wait);
	
	{
		VecFx32 ofs;
		
		WazaTool_CalcRotaFx(&wk->wtc);
		
		ofs.x = wk->pos.x + (wk->wtc.x * PT_LCD_DOT);
		ofs.y = wk->pos.y + (wk->wtc.y * PT_LCD_DOT);
		SPL_SetEmitterPositionX(wk->emit, ofs.x);
		SPL_SetEmitterPositionY(wk->emit, ofs.y);
	}
	
	WEEffect_TCB_AddPriSet(wk->ts.wsp, WSP_Rotation_TCB, wk);
}

typedef struct {
		
	TWE_TOOL_SYS	ts;
	
	CATS_ACT_PTR	cap;

} TWE_FREE; 

static void Free_TCB(TCB_PTR tcb, void* work)
{
	BOOL is_anime;
	
	TWE_FREE* wk = (TWE_FREE*)work;
	
	is_anime = TRUE;
	
	is_anime = CATS_ObjectAnimeActiveCheckCap(wk->cap);
	
	if (is_anime == FALSE){
		CATS_ActorPointerDelete_S(wk->cap);
		WEEffect_TCB_Delete(wk->ts.wsp, tcb);
		sys_FreeMemoryEz(wk);
		return;
	}
	
	CATS_ObjectUpdateCap(wk->cap);
	
	CATS_Draw(wk->ts.oam_crp);
}

void WestSp_Free(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap)
{
	TWE_FREE* wk = NULL;
	
	wk = WET_ALLOC_MEMORY(we_sys, TWE_FREE);
	
	WT_ToolSysInit(we_sys, &wk->ts);
	
	wk->cap = cap;
	
	{
		s16 x;
		s16 y;
		
		x = WeSysGPWorkGet(we_sys, 0);
		y = WeSysGPWorkGet(we_sys, 1);
		
		CATS_ObjectPosMoveCap(cap, x, y);
	}
	
	WEEffect_TCB_AddPriSet(wk->ts.wsp, Free_TCB, wk);
}

typedef struct {
		
	TWE_TOOL_SYS	ts;
	
	CATS_ACT_PTR	cap;
	
	WAZATOOL_CALCMOVE_ONE cmo;
	
	int cnt;
	
} TWE_266;

static const s16 we_266_x[] = { +5,+5,+5,+5, +4,+4,+4, +3,+3,+3, 0,
								-3,-3,-3, -4,-4,-4, -5,-5,-5,-5,-5,-5,-5,-5, -4,-4,-4, -3,-3,-3, 0,
								+3,+3,+3, +4,+4,+4, +5,+5,+5,+5, 0xFF };
static void We266_TCB(TCB_PTR tcb, void* work)
{
	TWE_266* wk = work;
	
	switch(wk->ts.seq){
	case 0:
		{
			s16 pos = we_266_x[wk->cnt];
			wk->cnt++;
			if (pos != 0xFF){
				int pri;
				int set_pri;
				
				if (pos == 0){
					
					pri = CATS_ObjectBGPriGetCap(wk->cap);
					
					if (pri == BT_3DPriorityGet(wk->ts.wsp)){
						set_pri = BT_BGPriorityGet(wk->ts.wsp, WES_BF_BACKGROUND);
						CATS_ObjectBGPriSetCap(wk->cap, set_pri);
					}
					else {
						set_pri = BT_3DPriorityGet(wk->ts.wsp);
						CATS_ObjectBGPriSetCap(wk->cap, set_pri);
					}
					
				}
				CATS_ObjectPosMoveCap(wk->cap, pos, 0);
			}
			else {
				CATS_ObjectAffineSetCap(wk->cap, CLACT_AFFINE_DOUBLE);
				WazaTool_InitMoveOneSync(&wk->cmo, 0, +FX_GET_ROTA_NUM(45), 8);
				CATS_ObjectAffinePosSetCap(wk->cap, -8, 16);
				wk->cnt = 0;
				wk->ts.seq++;
			}
		}
		break;
	
	case 1:
		{
			if (WazaTool_CalcMoveOne(&wk->cmo) == TRUE){
				CATS_ObjectRotationSetCap(wk->cap, wk->cmo.num);
			}
			else {
				if (wk->cnt > 3){
					wk->ts.seq++;
				}
				else {
					wk->cnt++;
					switch(wk->cnt){
					case 1:
						WazaTool_InitMoveOneSync(&wk->cmo, +FX_GET_ROTA_NUM(45), -FX_GET_ROTA_NUM(45), 8);
						break;
					case 2:
						WazaTool_InitMoveOneSync(&wk->cmo, -FX_GET_ROTA_NUM(45), +FX_GET_ROTA_NUM(45), 8);
						break;
					case 3:
						WazaTool_InitMoveOneSync(&wk->cmo, +FX_GET_ROTA_NUM(45), 0, 8);
						break;
					}
				}
			}
		}
		break;
		
	default:
		CATS_ActorPointerDelete_S(wk->cap);
		WEEffect_TCB_Delete(wk->ts.wsp, tcb);
		sys_FreeMemoryEz(wk);
		return;
	}
	
	CATS_ObjectUpdateCap(wk->cap);
	
	CATS_Draw(wk->ts.oam_crp);
}

void WestSp_266(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap)
{
	TWE_266* wk = NULL;
	
	wk = WET_ALLOC_MEMORY(we_sys, TWE_266);
	
	WT_ToolSysInit(we_sys, &wk->ts);
	
	wk->cap = cap;
	wk->cnt = 0;
	
	{
		int client = WeSysDFNoGet(we_sys);
		s16 x = GetWazaEffPos(we_sys, client, PM_X);
		s16 y = GetWazaEffPos(we_sys, client, PM_Y);
		
		CATS_ObjectPosSetCap(wk->cap, x, y);
	}
	
	if (WET_SideCheck(we_sys, WeSysATNoGet(we_sys)) == SIDE_ENEMY){
		CATS_ObjectAnimeSeqSetCap(wk->cap, 1);
	}
	else {
		CATS_ObjectAnimeSeqSetCap(wk->cap, 0);
	}
	

	CATS_ObjectBGPriSetCap(wk->cap, BT_3DPriorityGet(wk->ts.wsp));
	CATS_ObjectPosMoveCap(wk->cap, 0, +12);
	#if 0
	{
		s16 x;
		s16 y;
		
		x = WeSysGPWorkGet(we_sys, 0);
		y = WeSysGPWorkGet(we_sys, 1);
		
		
	}
	#endif
	
	WEEffect_TCB_AddPriSet(wk->ts.wsp, We266_TCB, wk);
}

typedef struct {
		
	TWE_TOOL_SYS	ts;
	
	CATS_ACT_PTR	cap;
	
	WAZATOOL_CALCMOVE_ONE cmo;
	
} TWE_090;


static void We090_TCB(TCB_PTR tcb, void* work)
{
	TWE_090* wk = work;
	BOOL is_anime;
	
	is_anime = CATS_ObjectAnimeActiveCheckCap(wk->cap);
	
	if (is_anime == FALSE){
		CATS_ActorPointerDelete_S(wk->cap);
		WEEffect_TCB_Delete(wk->ts.wsp, tcb);
		sys_FreeMemoryEz(wk);
		return;
	}
	
	CATS_ObjectUpdateCap(wk->cap);
	
	CATS_Draw(wk->ts.oam_crp);	
}

void WestSp_090(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap)
{
	TWE_090* wk;
	
	wk = WET_ALLOC_MEMORY(we_sys, TWE_266);
	
	WT_ToolSysInit(we_sys, &wk->ts);
	
	wk->cap = cap;
	
	{
		int anime = 0;
		int client = WeSysDFNoGet(we_sys);
		s16 x = GetWazaEffPos(we_sys, client, PM_X);
		s16 y = GetWazaEffPos(we_sys, client, PM_Y);
		
		if (WES_ContestFlag_Get(we_sys) == TRUE){
			
			x = 72;
			y = 32;
			anime = 0;
			
		}
		else {	
			if (WET_SideCheck(wk->ts.wsp, client) == SIDE_MINE){
				y = 190 - 32 - 32;
				anime = 1;
			}
			else {
				y =   0 + 32;
				anime = 0;
			}
		}
		CATS_ObjectPosSetCap(wk->cap, x, y);
		CATS_ObjectAnimeSeqSetCap(wk->cap, anime);
	}
	
	CATS_ObjectBGPriSetCap(wk->cap, BT_BGPriorityGet(wk->ts.wsp, WES_BF_BACKGROUND));
	
	WEEffect_TCB_AddPriSet(wk->ts.wsp, We090_TCB, wk);
}

///< item
typedef struct {
		
	TWE_TOOL_SYS		ts;
	
	CATS_ACT_PTR		cap;
	
	u8	eva;
	u8	evb;
	
	WAZATOOL_CALCMOVE	cm[2];
	
} TWE_ITEM;

static void Item_TCB(TCB_PTR tcb, void* work)
{
	TWE_ITEM* wk = work;
	BOOL is_anime;
	
	
	
	switch(wk->ts.seq){
	case 0:
		WazaTool_InitCurveYFx(&wk->cm[0],
							  &wk->cm[1], 
							  -30, 128 - 16,
							  160, 80 + 32,
							  21, 64 * FX32_ONE);
		wk->ts.seq++;
		break;
		
	case 1:
		if (WazaTool_CalcAndReflectCurveFxCap(&wk->cm[0], &wk->cm[1], wk->cap) == FALSE){
			wk->ts.seq++;
		}
		break;
		
	case 2:
		{
			BOOL is_anime = CATS_ObjectAnimeActiveCheckCap(wk->cap);
			
			if (is_anime == FALSE){
				
				CATS_ObjectObjModeSetCap(wk->cap, GX_OAM_MODE_XLU);
				wk->eva = 16;
				wk->evb =  0;
				WET_DefaultBlendSet(wk->ts.wsp, wk->eva, wk->evb);
				
				wk->ts.seq++;
			}
		}
		break;
		
	case 3:
	
		if (wk->eva >  0){ wk->eva--; }
		if (wk->evb < 16){ wk->evb++; }
		
		G2_ChangeBlendAlpha(wk->eva, wk->evb);
		
		if (wk->eva == 0){
			wk->ts.seq++;
		}
	
		break;
		
	default:
		CATS_ActorPointerDelete_S(wk->cap);
		WEEffect_TCB_Delete(wk->ts.wsp, tcb);
		sys_FreeMemoryEz(wk);
		return;
	}
	
	CATS_ObjectUpdateCap(wk->cap);
	
	CATS_Draw(wk->ts.oam_crp);
}

void WestSp_Item(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap)
{
	TWE_ITEM* wk;
	
	wk = WET_ALLOC_MEMORY(we_sys, TWE_ITEM);
	
	WT_ToolSysInit(we_sys, &wk->ts);
	
	wk->cap = cap;
	
	CATS_ObjectPosSetCap(wk->cap, -30, 160);
	
	CATS_ObjectBGPriSetCap(wk->cap, BT_BGPriorityGet(wk->ts.wsp, WES_BF_BACKGROUND));

	WEEffect_TCB_AddPriSet(wk->ts.wsp, Item_TCB, wk);
}


//--------------------------------------------------------------
/**
 * @brief	カラー変更
 *
 * @param	wsp	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WSP_PalColChange(WE_SYS_PTR wsp)
{
	int no = WeSysGPWorkGet(wsp, 0);
	
	if (no != 0){
		WeTool_PalGrayScale(wsp);
	}
	else {
		WeTool_PalNormal(wsp);
	}
}



//--------------------------------------------------------------
/**
 * @brief	OAM表示
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
typedef struct {
	
	TWE_TOOL_SYS	ts;
	
	CATS_ACT_PTR	cap;
	
	int cap_id;
	int	wait;
	int bg_type;
	int soft_pri;
	int call_back;
	int target;
	
	int cnt;
	
	int gene_cnt;
	
} WE_POV;

static void PokeOamView_464(WE_POV* wk)
{
	switch(wk->ts.seq){
	case 0:
		if (wk->target == 0){
			GX_SetVisibleWnd(GX_WNDMASK_W0);
			G2_SetWnd0InsidePlane(GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 |
								  GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3, TRUE);
			G2_SetWndOutsidePlane(GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 |
								  GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 |
								  GX_WND_PLANEMASK_OBJ, TRUE);
			G2_SetWnd0Position(0, 160, 128, 192);
			wk->gene_cnt = 35 + (gf_rand() % 5);
		}
		else {
			GX_SetVisibleWnd(GX_WNDMASK_W0);
			G2_SetWnd0InsidePlane(GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 |
								  GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3, TRUE);
			G2_SetWndOutsidePlane(GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 |
								  GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 |
								  GX_WND_PLANEMASK_OBJ, TRUE);
			G2_SetWnd0Position(128, 96 - 10, 256, 192);
			wk->gene_cnt = 35 + (gf_rand() % 5);
		}
		break;
		
	case 5:
	case 6:
		if (gf_rand() % 2){
			if (wk->cnt == 0){
				wk->cnt++;
				CATS_ObjectPosMoveCap(wk->cap, 0, +4);
			}
		}
		break;
	case 7:
		if (wk->cnt != 1){
			wk->cnt++;
			CATS_ObjectPosMoveCap(wk->cap, 0, +4);
		}
		break;
	
	case 10:
	case 11:
		if (gf_rand() % 2){
			if (wk->cnt == 1){
				wk->cnt++;
				CATS_ObjectPosMoveCap(wk->cap, 0, +4);
			}
		}
		break;
	case 12:
		if (wk->cnt != 2){
			wk->cnt++;
			CATS_ObjectPosMoveCap(wk->cap, 0, +4);
		}
		break;
		
	case 15:
	case 16:
		if (gf_rand() % 2){
			if (wk->cnt == 2){
				wk->cnt++;
				CATS_ObjectPosMoveCap(wk->cap, 0, +4);
			}
		}
		break;
	case 17:
		if (wk->cnt != 3){
			wk->cnt++;
			CATS_ObjectPosMoveCap(wk->cap, 0, +4);
		}
		break;

	case 22:
	case 23:
		if (gf_rand() % 2){
			if (wk->cnt == 3){
				wk->cnt++;
				CATS_ObjectPosMoveCap(wk->cap, 0, +8);
			}
		}
		break;
	case 24:
		if (wk->cnt != 4){
			wk->cnt++;
			CATS_ObjectPosMoveCap(wk->cap, 0, +8);
		}
		break;
				
	default:
		if (wk->ts.seq > wk->gene_cnt){
			if (wk->cnt < 20){
				CATS_ObjectPosMoveCap(wk->cap, 0, +4);
				{
					s16 x, y;
					
					CATS_ObjectPosGetCap(wk->cap, &x, &y);
					
					if (y > 130){
						CATS_ObjectEnableCap(wk->cap, CATS_ENABLE_FALSE);
					}					
				}
				wk->cnt++;
			}
			else {
				CATS_ObjectEnableCap(wk->cap, CATS_ENABLE_FALSE);
			}
		}
		break;
	}
}

static void PokeOamView_TCB(TCB_PTR tcb, void* work)
{
	WE_POV* wk = work;
	
	
	if (wk->call_back != 0){
		PokeOamView_464(wk);
	}
	
	wk->ts.seq++;
	
	if (wk->ts.seq >= wk->wait){
		
		GX_SetVisibleWnd(GX_WNDMASK_NONE);
		G2_SetWnd0InsidePlane(GX_WND_PLANEMASK_NONE, FALSE);
		G2_SetWndOutsidePlane(GX_WND_PLANEMASK_NONE, FALSE);
		G2_SetWnd0Position(0, 0, 0, 0);
		CATS_ObjectEnableCap(wk->cap, CATS_ENABLE_FALSE);
		CATS_Draw(wk->ts.poke_crp);	
		WEEffect_TCB_Delete(wk->ts.wsp, tcb);
		sys_FreeMemoryEz(wk);
		return;
	}

	CATS_ObjectUpdateCap(wk->cap);
	CATS_Draw(wk->ts.poke_crp);	
}

void WSP_PokeOAM_View(WE_SYS_PTR we_sys)
{
	WE_POV* wk;
	
	wk = WET_ALLOC_MEMORY(we_sys, WE_POV);
	
	WT_ToolSysInit(we_sys, &wk->ts);

	wk->cap_id	 = WeSysGPWorkGet(we_sys, 0);
	wk->wait  	 = WeSysGPWorkGet(we_sys, 1);
	wk->bg_type	 = WeSysGPWorkGet(we_sys, 2);
	wk->soft_pri = WeSysGPWorkGet(we_sys, 3);
	wk->call_back= WeSysGPWorkGet(we_sys, 5);
	wk->target	 = WeSysGPWorkGet(we_sys, 6);	///< 0 = MINE
	
	wk->cap	= WeSysPokeCapGet(wk->ts.wsp, wk->cap_id);
	wk->cnt = 0;
	
	{
		int bg_pri;
		
		if (wk->bg_type != WT_BF_NONE){
			
			bg_pri = BT_BGPriorityGet(we_sys, wk->bg_type);
			
			CATS_ObjectBGPriSetCap(wk->cap, bg_pri);
		}
		
		if (wk->soft_pri != WT_BF_NONE){
			CATS_ObjectPriSetCap(wk->cap, wk->soft_pri);
		}
	}
	
	if (IsWeSysBattleMode2vs2(we_sys) != TRUE){
		if (WeSysGPWorkGet(we_sys, 4) == WEDEF_DROP_M2
		||	WeSysGPWorkGet(we_sys, 4) == WEDEF_DROP_E2){
			CATS_ObjectEnableCap(wk->cap, CATS_ENABLE_FALSE);		
			sys_FreeMemoryEz(wk);
			return;
		}
	}
	
	{
		int para = WeSysGPWorkGet(we_sys, 4);
		int at   = WeSysATNoGet(we_sys);
		int df   = WeSysDFNoGet(we_sys);
		int att, dft;
		if (wk->soft_pri != WT_BF_NONE){
			
			att = WET_ClientTypeGet(we_sys, at);
			dft = WET_ClientTypeGet(we_sys, df);
			
			switch(para){
			case WEDEF_DROP_M1:
				switch(att){
				case CLIENT_TYPE_A:
					CATS_ObjectPriSetCap(wk->cap, 20);
					break;
				case CLIENT_TYPE_B:
					CATS_ObjectPriSetCap(wk->cap, 10);
					break;
				case CLIENT_TYPE_C:
					CATS_ObjectPriSetCap(wk->cap, 10);
					break;
				case CLIENT_TYPE_D:
					CATS_ObjectPriSetCap(wk->cap, 20);
					break;
				}
				break;
				
			case WEDEF_DROP_M2:
				switch(att){
				case CLIENT_TYPE_A:
					CATS_ObjectPriSetCap(wk->cap, 10);
					break;
				case CLIENT_TYPE_B:
					CATS_ObjectPriSetCap(wk->cap, 20);
					break;
				case CLIENT_TYPE_C:
					CATS_ObjectPriSetCap(wk->cap, 20);
					break;
				case CLIENT_TYPE_D:
					CATS_ObjectPriSetCap(wk->cap, 10);
					break;
				}
				break;
				
			case WEDEF_DROP_E1:
				switch(dft){
				case CLIENT_TYPE_A:
					CATS_ObjectPriSetCap(wk->cap, 20);
					break;
				case CLIENT_TYPE_B:
					CATS_ObjectPriSetCap(wk->cap, 10);
					break;
				case CLIENT_TYPE_C:
					CATS_ObjectPriSetCap(wk->cap, 10);
					break;
				case CLIENT_TYPE_D:
					CATS_ObjectPriSetCap(wk->cap, 20);
					break;
				}
				break;
				
			case WEDEF_DROP_E2:
				switch(dft){
				case CLIENT_TYPE_A:
					CATS_ObjectPriSetCap(wk->cap, 10);
					break;
				case CLIENT_TYPE_B:
					CATS_ObjectPriSetCap(wk->cap, 20);
					break;
				case CLIENT_TYPE_C:
					CATS_ObjectPriSetCap(wk->cap, 20);
					break;
				case CLIENT_TYPE_D:
					CATS_ObjectPriSetCap(wk->cap, 10);
					break;
				}
				break;
			}
		}
	}

	WEEffect_TCB_AddPriSet(wk->ts.wsp, PokeOamView_TCB, wk);	
}

//--------------------------------------------------------------
/**
 * @brief	場のポケモンをOAMに落とす
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
typedef struct {
	
	TWE_TOOL_SYS	ts;
	
	CATS_ACT_PTR	cap[ 4 ];
	
	int wait;
	int num;
	
} PAD;

static void PAD_Tcb(TCB_PTR tcb, void* work)
{
	int i;
	PAD* wk = (PAD*)work;
	
	if (wk->wait == 0){
		
		WEEffect_TCB_Delete(wk->ts.wsp, tcb);
		sys_FreeMemoryEz(wk);
		
		return;
	}
	
	wk->wait--;
	
	for (i = 0; i < 4; i++){
		
		if (wk->cap[ i ] == NULL){ continue; }
		
		CATS_ObjectUpdateCap(wk->cap[ i ]);
	}
	CATS_Draw(wk->ts.poke_crp);	
}

void WSP_AllPokeDrop(WE_SYS_PTR we_sys)
{
	PAD* wk;
	
	wk = WET_ALLOC_MEMORY(we_sys, PAD);
	
	WT_ToolSysInit(we_sys, &wk->ts);
	
	if (WeSysGPWorkGet(we_sys, 0) == 0){
		wk->wait = PARTICLE_VBLANK_LOAD_WAIT + 1;
	}
	else {
		wk->wait = WeSysGPWorkGet(we_sys, 0);
	}
	
	{
		int i;
		static int pri_table[ 4 ] = { 
			20, 10, 10, 20,
		};
		
		for (i = 0; i < 4; i++){
			
			wk->cap[ i ] = WeSysPokeCapGet(wk->ts.wsp, i);
			
			if (wk->cap[ i ] != NULL){				
				CATS_ObjectPriSetCap(wk->cap[i], pri_table[i]);				
			}
		}
	}
	
	{
		TCB_PTR tcb = WEEffect_TCB_AddPriSet(wk->ts.wsp, PAD_Tcb, wk);
		
		PAD_Tcb(tcb, wk);
	}		
}


//--------------------------------------------------------------
/**
 * @brief	ラスタースクロール
 *
 * @param	tcb	
 * @param	work	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
typedef struct {
	
	int lst_wait;
	int lst_wait_max;
	
	TWE_TOOL_SYS	ts;
	
	WAZATOOL_SCRLASTER_PTR	lst;	// laster
	
} TWE_LASTER_SYS;

#define WELASTER_ROTA_ADD		(FX_GET_ROTA_NUM(1))
#define WELASTER_ROTA_WIDTH		(32*FX32_ONE)
#define WELASTER_SCR_SP_OFS		(2)
#define WELASTER_SCR_SP			(WELASTER_SCR_SP_OFS*100)

static void WeLASTER_TCB(TCB_PTR tcb, void* work)
{
	TWE_LASTER_SYS* wk = (TWE_LASTER_SYS*)work;
	
	switch(wk->ts.seq){
	case 0:
		// ラスター
		wk->lst_wait = 0;
		wk->lst = WazaTool_InitScrLaster( 
				0,
				160,
				WELASTER_ROTA_ADD,
				WELASTER_ROTA_WIDTH,
				WELASTER_SCR_SP,
				BT_BGL_BGNoGet(wk->ts.wsp, WES_BF_BACKGROUND),
				0,
				WazaTool_GetLasterBuffMatrixData(0, 0),
				WeSysHeapAreaGet(wk->ts.wsp));

		wk->ts.seq++;
		break;
		
	case 1:
		wk->lst_wait++;
		
		if (wk->lst_wait < wk->lst_wait_max){ break; }

		WazaTool_DeleteScrLaster(wk->lst);
		wk->ts.seq++;

	default:
		WEEffect_TCB_Delete(wk->ts.wsp, tcb);
		sys_FreeMemoryEz(wk);
		return;
	}
}

void WestSp_WE_Laster(WE_SYS_PTR we_sys)
{
	TWE_LASTER_SYS* wk = NULL;
	
	wk = WET_ALLOC_MEMORY(we_sys, TWE_LASTER_SYS);
	
	WT_ToolSysInit(we_sys, &wk->ts);
	
	wk->lst_wait_max = WeSysGPWorkGet(we_sys, 0);
		
	WEEffect_TCB_AddPriSet(wk->ts.wsp, WeLASTER_TCB, wk);
}
