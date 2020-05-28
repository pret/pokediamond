//==============================================================================
/**
 * @file	wsp_steff.c
 * @brief	ステータスエフェクト用
 * @author	goto
 * @date	2006.03.15
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

///< 個別設定パラメータ 汎用ワークからの取り出しとそうでないものがある。
typedef struct {

	int arc_id;			///< アークNo			固定
	int data_no;		///< グラフィックNo = up/down/recover
	int type;			///< 能力タイプ
	
	s16	speed_x;
	s16	speed_y;
	
	s16	ofs_x;
	s16	ofs_y;
	u16 ev1;
	u16 ev2;

} STEFF_PARAM;

///< システム
typedef struct {

	STEFF_PARAM		param;
	TWE_TOOL_SYS	ts;

	CATS_ACT_PTR	cap_n;
	CATS_ACT_PTR	cap_w;
	CATS_ACT_PTR	cap_m;

	u8	wait;

} STEFF_SYS;

#define STEFF_FADE_WAIT				(20)
#define STEFF_WIN_OUT_SIDE_PLANE	(GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | \
									 GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ)

static const int StatusEffect_DataTable[][4] = {
	{
		STATE_UP_NCGR_BIN,
		STATE_UP_NCLR,
		STATE_UP_NSCR_BIN,
		STATE_UP_NSCR_BIN,
	},
	{
		STATE_DOWN_NCGR_BIN,
		STATE_DOWN_NCLR,
		STATE_DOWN_NSCR_BIN,
		STATE_DOWN_NSCR_BIN,
	},
	{
		STATE_HEAL_NCGR_BIN,
		STATE_HEAL_NCLR,
		STATE_HEAL_NSCR_BIN,
		STATE_HEAL_NSCR_BIN,
	},
	{
		STATE_METAL_NCGR_BIN,
		STATE_METAL_NCLR,
		STATE_METAL_NSCR_BIN,
		STATE_METAL_NSCR_BIN,
	},	
};

static void StatusEffect_ScrollSet(STEFF_PARAM* wk, s16 x, s16 y)
{
	wk->speed_x = x;
	wk->speed_y = y;
}

static void StatusEffect_AlphaSet(STEFF_PARAM* wk, u16 ev1, u16 ev2)
{
	wk->ev1 = ev1;
	wk->ev2 = ev2;
}

static void StatusEffect_DataSet(STEFF_SYS* wk, int frm)
{
	int heap;
	int pri;
	
	heap = WeSysHeapAreaGet(wk->ts.wsp);
	pri  = BT_BGPriorityGet(wk->ts.wsp, WES_BF_3DFRAME);
	
	GF_BGL_PrioritySet(frm, pri);
	
	ArcUtil_BgCharSet(wk->param.arc_id,
					  StatusEffect_DataTable[ wk->param.data_no ][0],
					  wk->ts.bgl,
					  frm, 0, 0, 1, heap);

	PaletteWorkSet_Arc(wk->ts.pfd,
					   wk->param.arc_id, StatusEffect_DataTable[ wk->param.data_no ][1],
					   heap, FADE_MAIN_BG, 0x20, WEDEF_BG_POKE_COL_POS);

	GF_BGL_ScrClear(wk->ts.bgl, frm);

	ArcUtil_ScrnSet(wk->param.arc_id,
					StatusEffect_DataTable[ wk->param.data_no ][ 2 ],
					wk->ts.bgl,
					frm, 0, 0, 1, heap);
}

///< TCB
static void StatusEffect_TCB(TCB_PTR tcb, void* work)
{
	STEFF_SYS* wk = (STEFF_SYS*)work;
	
	switch(wk->ts.seq){
	case 0:
		StatusEffect_DataSet(wk, BATTLE_FRAME_EFFECT);
		#if 0
		G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG2,
						 GX_BLEND_PLANEMASK_BD  | GX_BLEND_PLANEMASK_OBJ |
						 GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG3,
						 wk->param.ev1, wk->param.ev2);
		#endif
		wk->ts.seq++;
		break;
	
	case 1:
		G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG2,
						 GX_BLEND_PLANEMASK_BD  | GX_BLEND_PLANEMASK_OBJ |
						 GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG3,
						 wk->param.ev1, wk->param.ev2);
		wk->ts.seq++;
		break;
		
	case 2:
		if (wk->wait > STEFF_FADE_WAIT){
			wk->ts.seq++;
		}
		else {
			wk->wait++;
		}
		break;
		
	case 3:
		if (wk->param.ev1 > 0){
			wk->param.ev1--;
		}
		if (wk->param.ev2 < 16){
			wk->param.ev2++;
		}
		if (wk->param.ev1 == 0
		&&	wk->param.ev2 == 16){
			GF_BGL_ScrClear(wk->ts.bgl, BATTLE_FRAME_EFFECT);
			CATS_ObjectEnableCap(wk->cap_n, CATS_ENABLE_FALSE);
			CATS_ObjectEnableCap(wk->cap_w, CATS_ENABLE_FALSE);
			CATS_ObjectEnableCap(wk->cap_m, CATS_ENABLE_FALSE);
			wk->ts.seq++;
		}
		G2_ChangeBlendAlpha(wk->param.ev1, wk->param.ev2);		
		break;
		
	default:
		G2_SetWndOutsidePlane(WE_MASK_ALL, FALSE);
		G2_SetWndOBJInsidePlane(WE_MASK_ALL, FALSE);
		GF_BGL_ScrollSet(wk->ts.bgl, BATTLE_FRAME_EFFECT, GF_BGL_SCROLL_X_SET, 0);
		GF_BGL_ScrollSet(wk->ts.bgl, BATTLE_FRAME_EFFECT, GF_BGL_SCROLL_Y_SET, 0);
		GX_SetVisibleWnd(GX_WNDMASK_NONE);
		WEEffect_TCB_Delete(wk->ts.wsp, tcb);
		WET_SAFE_RELEASE(wk);
		return;
	}

	wk->param.ofs_x += wk->param.speed_x;
	wk->param.ofs_y += wk->param.speed_y;

	GF_BGL_ScrollSet(wk->ts.bgl, BATTLE_FRAME_EFFECT, GF_BGL_SCROLL_X_SET, wk->param.ofs_x);
	GF_BGL_ScrollSet(wk->ts.bgl, BATTLE_FRAME_EFFECT, GF_BGL_SCROLL_Y_SET, wk->param.ofs_y);

	CATS_ObjectUpdateCap(wk->cap_n);
	CATS_ObjectUpdateCap(wk->cap_w);
	CATS_ObjectUpdateCap(wk->cap_m);
	CATS_Draw(wk->ts.poke_crp);
}


///< 汎用ワークからの値取り出し
static void StatusEffect_Param_SetUp(WE_SYS_PTR wsp, STEFF_PARAM* param)
{
	(*param).arc_id		= WE_HAIKEI_ARC;
	(*param).data_no	= WeSysGPWorkGet(wsp, 0);
	(*param).type	  	= WeSysGPWorkGet(wsp, 1);
}


///< 初期化
static void StatusEffect_BG_SetUp(WE_SYS_PTR wsp, STEFF_PARAM* param)
{
	STEFF_SYS* wk = WET_ALLOC_MEMORY(wsp, STEFF_SYS);
	
	WT_ToolSysInit(wsp, &wk->ts);
	
	wk->param = (*param);
	
	wk->cap_n = WeSysPokeCapGet(wk->ts.wsp, 0);		///< ノーマル　OBJ
	wk->cap_w = WeSysPokeCapGet(wk->ts.wsp, 1);		///< ウィンドウOBJ
	wk->cap_m = WeSysPokeCapGet(wk->ts.wsp, 2);		///< 相方OBJ
	
	{
		int pri;
		
		pri = BT_BGPriorityGet(wk->ts.wsp, WES_BF_BACKGROUND);
		pri = 2;
		
		CATS_ObjectBGPriSetCap(wk->cap_n, pri);
		CATS_ObjectBGPriSetCap(wk->cap_w, pri);
		
		{
			int type;
			int client;
			
			if (wk->param.type == 0){
				client = WeSysATNoGet(wsp);
			}
			else {
				client = WeSysDFNoGet(wsp);
			}
			
			type = WET_ClientTypeGet(wsp, client);	
			
			if (WES_ContestFlag_Get(wsp) == TRUE){
				CATS_ObjectEnableCap(wk->cap_m, CATS_ENABLE_FALSE);
				pri = BT_BGPriorityGet(wk->ts.wsp, WES_BF_BACKGROUND);
				CATS_ObjectBGPriSetCap(wk->cap_n, pri);
				CATS_ObjectBGPriSetCap(wk->cap_w, pri);
			}
			else {
				if (type == CLIENT_TYPE_AA
				||	type == CLIENT_TYPE_BB){
					CATS_ObjectEnableCap(wk->cap_m, CATS_ENABLE_FALSE);
				}
				else if (type == CLIENT_TYPE_C
					 ||	 type == CLIENT_TYPE_B){
					if (wk->param.type == 0){
						CATS_ObjectBGPriSetCap(wk->cap_m, pri + 1);
					}
					else {
						CATS_ObjectBGPriSetCap(wk->cap_m, pri + 1);
					}
				}
				else {
					if (wk->param.type == 0){
						CATS_ObjectBGPriSetCap(wk->cap_m, pri - 1);
					}
					else {
						CATS_ObjectBGPriSetCap(wk->cap_m, pri - 1);
					}
				}
			}
		}
	}

	///< ブレンド設定
	{
		G2_SetWndOBJInsidePlane(GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_OBJ | GX_WND_PLANEMASK_BG2,	TRUE);
		G2_SetWndOutsidePlane(STEFF_WIN_OUT_SIDE_PLANE,	TRUE);
		GX_SetVisibleWnd(GX_WNDMASK_OW);

		CATS_ObjectObjModeSetCap(wk->cap_w, GX_OAM_MODE_OBJWND);
	}
	
	wk->param.ofs_x = 0;
	wk->param.ofs_y = 0;

	WEEffect_TCB_AddPriSet(wk->ts.wsp, StatusEffect_TCB, wk);
}

#define STEFF_SCR_SPEED_X	(3)
#define STEFF_SCR_SPEED_Y	(3)
#define STEFF_SCR_EV1		(12)
#define STEFF_SCR_EV2		(4)
//--------------------------------------------------------------
/**
 * @brief	上昇エフェクト
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void StatusEffect_Up(WE_SYS_PTR we_sys)
{
	STEFF_PARAM p;
	
	StatusEffect_Param_SetUp(we_sys, &p);

	StatusEffect_ScrollSet(&p, 0, +STEFF_SCR_SPEED_X);
	StatusEffect_AlphaSet(&p, STEFF_SCR_EV1, STEFF_SCR_EV2);

	StatusEffect_BG_SetUp(we_sys, &p);
}


//--------------------------------------------------------------
/**
 * @brief	下降エフェクト
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void StatusEffect_Down(WE_SYS_PTR we_sys)
{
	STEFF_PARAM p;
	
	StatusEffect_Param_SetUp(we_sys, &p);
	
	StatusEffect_ScrollSet(&p, 0, -STEFF_SCR_SPEED_Y);
	StatusEffect_AlphaSet(&p, STEFF_SCR_EV1, STEFF_SCR_EV2);
	
	StatusEffect_BG_SetUp(we_sys, &p);
}


//--------------------------------------------------------------
/**
 * @brief	回復エフェクト
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void StatusEffect_Recover(WE_SYS_PTR we_sys)
{
	STEFF_PARAM p;
	
	StatusEffect_Param_SetUp(we_sys, &p);
	
	StatusEffect_ScrollSet(&p, 0, +STEFF_SCR_SPEED_Y);
	StatusEffect_AlphaSet(&p, STEFF_SCR_EV1, STEFF_SCR_EV2);
	
	StatusEffect_BG_SetUp(we_sys, &p);
}

//--------------------------------------------------------------
/**
 * @brief	メタルエフェクト
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void StatusEffect_Metal(WE_SYS_PTR we_sys)
{
	STEFF_PARAM p;
	s16 speed = STEFF_SCR_SPEED_Y + 3;
	
	StatusEffect_Param_SetUp(we_sys, &p);
	
	StatusEffect_ScrollSet(&p, 0, -speed);
	StatusEffect_AlphaSet(&p, STEFF_SCR_EV1, STEFF_SCR_EV2);
	
	StatusEffect_BG_SetUp(we_sys, &p);
}
