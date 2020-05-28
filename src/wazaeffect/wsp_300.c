//==============================================================================
/**
 * @file	wsp_300.c
 * @brief	簡単な説明を書く
 * @author	goto
 * @date	2006.02.28
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

///< No 300-
typedef struct {

	TWE_TOOL_SYS		ts;		///< 技エフェクト汎用構造体
	TWE_POKE_SYS		poke;	///< ポケモン汎用構造体
	CATS_ACT_PTR		cap;
	
	WAZATOOL_CALCMOVE	cm;		///< 汎用ワーク
	WAZATOOL_CALCMOVE	cm_t;	///< 汎用ワーク
	WAZATOOL_CALCMOVE	cm_t2;	///< 汎用ワーク

	u8	loop;
	u8	wait;
	u8	eva;
	u8	evb;
	
	s16	height;
	
	
} TWE_325_SYS;

static void We325_TCB(TCB_PTR tcb, void* work)
{
	TWE_325_SYS* wk = (TWE_325_SYS*)work;
	
	switch(wk->ts.seq){
	case 0:
		if (wk->loop == 0){
			WazaTool_InitStraightSyncFx(&wk->cm,
										wk->poke.p.x, wk->poke.p.x + 48,
										wk->poke.p.y, wk->poke.p.y,
										3);
			WazaTool_InitStraightSyncFx(&wk->cm_t,
										wk->poke.p.x, wk->poke.p.x + 48,
										wk->poke.p.y + wk->height, wk->poke.p.y + wk->height,
										6);
			WazaTool_InitStraightSyncFx(&wk->cm_t2,
										wk->poke.p.x, wk->poke.p.x + 48,
										wk->poke.p.y + wk->height, wk->poke.p.y + wk->height,
										8);
		}
		else {
			WazaTool_InitStraightSyncFx(&wk->cm,
										wk->poke.p.x + 48, wk->poke.p.x,
										wk->poke.p.y, wk->poke.p.y,
										3);
			WazaTool_InitStraightSyncFx(&wk->cm_t,
										wk->poke.p.x + 48, wk->poke.p.x,
										wk->poke.p.y + wk->height, wk->poke.p.y + wk->height,
										6);
			WazaTool_InitStraightSyncFx(&wk->cm_t2,
										wk->poke.p.x + 48, wk->poke.p.x,
										wk->poke.p.y + wk->height, wk->poke.p.y + wk->height,
										9);
		}
		wk->loop++;
		wk->ts.seq++;
		break;
	
	case 1:
		{
			int check = 0;
			if (WazaTool_CalcAndReflectStraightFxCap(&wk->cm_t, wk->poke.cap) == FALSE){
				check++;
			}
			if (WazaTool_CalcAndReflectStraightFxSsp(&wk->cm,   wk->poke.ssp) == FALSE){
				check++;
			}
			if (WazaTool_CalcAndReflectStraightFxCap(&wk->cm_t2,wk->cap) == FALSE){
				check++;
			}
			
			if (check >= 3){
				if (wk->loop == 1){
					wk->ts.seq--;
				}
				else {
					wk->ts.seq++;
				}
			}
		}
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

void WestSp_WE_325(WE_SYS_PTR we_sys)
{
	TWE_325_SYS* wk = WET_ALLOC_MEMORY(we_sys, TWE_325_SYS);
	
	WT_ToolSysInit(we_sys, &wk->ts);

	wk->wait = 0;
	wk->eva  = 8;
	wk->evb	 = 8;
	
	WET_DefaultBlendSet(wk->ts.wsp, WET_DEFAULT_BLEND, WET_DEFAULT_BLEND);
	G2_ChangeBlendAlpha(wk->eva, wk->evb);
	
	wk->poke.ssp = WeSysSoftSpritePointerGet(wk->ts.wsp, WeSysATNoGet(wk->ts.wsp));
	wk->poke.p.x = SoftSpriteParaGet(wk->poke.ssp, SS_PARA_POS_X);
	wk->poke.p.y = SoftSpriteParaGet(wk->poke.ssp, SS_PARA_POS_Y);
	wk->poke.cap = WeSysPokeCapGet(wk->ts.wsp, 0);
	wk->cap = WeSysPokeCapGet(wk->ts.wsp, 1);
	wk->height = -SoftSpriteParaGet(wk->poke.ssp, SS_PARA_SHADOW_HEIGHT);
	{
		CATS_ACT_PTR cap;
		int pal_pos;
		int index_no = WeSysPalIDGet(wk->ts.wsp, WeSysATNoGet(wk->ts.wsp));
		int arcID	 = WeSysArcIDGet(wk->ts.wsp, WeSysATNoGet(wk->ts.wsp));

		cap = wk->poke.cap;
		
		CATS_ObjectBGPriSetCap(cap, BT_3DPriorityGet(wk->ts.wsp)+1);
		pal_pos = GetPlttProxyOffset(CLACT_PaletteProxyGet(cap->act), NNS_G2D_VRAM_TYPE_2DMAIN);
		PokeColorChange(WeSysPFDGet(wk->ts.wsp), arcID, index_no,
						WeSysHeapAreaGet(wk->ts.wsp), FADE_MAIN_OBJ, 0x20, pal_pos * 16, 196,196,196);
		CATS_ObjectObjModeSetCap(cap, GX_OAM_MODE_XLU);

		cap = wk->cap;
		CATS_ObjectBGPriSetCap(cap, BT_3DPriorityGet(wk->ts.wsp)+1);
		pal_pos = GetPlttProxyOffset(CLACT_PaletteProxyGet(cap->act), NNS_G2D_VRAM_TYPE_2DMAIN);
		PokeColorChange(WeSysPFDGet(wk->ts.wsp), arcID, index_no,
						WeSysHeapAreaGet(wk->ts.wsp), FADE_MAIN_OBJ, 0x20, pal_pos * 16, 196,196,196);
		CATS_ObjectObjModeSetCap(cap, GX_OAM_MODE_XLU);
	}
	
	WEEffect_TCB_AddPriSet(wk->ts.wsp, We325_TCB, wk);
}


/// 338
#define WE338_OAM_MAX	(8)
typedef struct {
	
	TWE_TOOL_SYS	ts;
	
	s16				wait;
	s16				time[WE338_OAM_MAX];
	CATS_ACT_PTR	cap[WE338_OAM_MAX];
	
	WAZATOOL_CALCMOVE	cm;		///< 汎用ワーク

} TWE_338_SYS;

static void We338_TCB(TCB_PTR tcb, void* work)
{
	TWE_338_SYS* wk = (TWE_338_SYS*)work;
	
	{
		int i;
		int check = 0;
		for (i = 0; i < WE338_OAM_MAX; i++){
			wk->time[i]++;
			if (wk->time[i] < 32){ continue; }
			
			EnableCheckAnime(wk->cap[i]);

			if (wk->time[i] >= 160){
				CATS_ObjectEnableCap(wk->cap[i], CATS_ENABLE_FALSE);
				check++;
			}
		}
		if (check == WE338_OAM_MAX){
			for (i = 0; i < WE338_OAM_MAX; i++){
				CATS_ActorPointerDelete_S(wk->cap[i]);
			}
			WEEffect_TCB_Delete(wk->ts.wsp, tcb);
			sys_FreeMemoryEz(wk);
			return;
		}
	}
	
	CATS_Draw(wk->ts.oam_crp);
}

void WestSp_CAT_WE_338(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap)
{
	TWE_338_SYS* wk = NULL;
	
	wk = WET_ALLOC_MEMORY(we_sys, TWE_338_SYS);
	
	wk->wait = 10;
	WT_ToolSysInit(we_sys, &wk->ts);
	
	{
		int i;

		///< OAM登録
		{
			s16 ofs1,ofs2;
			TCATS_OBJECT_ADD_PARAM_S coap;
			coap = WeSysCoapGet(wk->ts.wsp);
			wk->cap[0]  = cap;
			for (i = 1; i < WE338_OAM_MAX; i++){
				wk->cap[i]  = CATS_ObjectAdd_S(wk->ts.csp, wk->ts.oam_crp, &coap);
				
				if (i % 2){
					CATS_ObjectFlipSetCap(wk->cap[i], CLACT_FLIP_H);
				}
			}
		}

		///< 直線計算初期化
		{
			SOFT_SPRITE* ssp;
			s16 x1,x2,y1,y2;
			
			ssp = WeSysSoftSpritePointerGet(wk->ts.wsp, WeSysATNoGet(wk->ts.wsp));
			x1 = SoftSpriteParaGet(ssp, SS_PARA_POS_X);
			y1 = SoftSpriteParaGet(ssp, SS_PARA_POS_Y);
			ssp = WeSysSoftSpritePointerGet(wk->ts.wsp, WeSysDFNoGet(wk->ts.wsp));
			x2 = SoftSpriteParaGet(ssp, SS_PARA_POS_X);
			y2 = SoftSpriteParaGet(ssp, SS_PARA_POS_Y);
			
			WazaTool_InitStraightSyncFx(&wk->cm, x1, x2, y1, y2, (WE338_OAM_MAX+2) * 2);
		}

		///< 直線状の配置
		{
			BOOL res;
			int  cnt = 0;
			int  no  = 0;
			int skip = 0;
			if (WET_SideCheck(wk->ts.wsp, WeSysATNoGet(wk->ts.wsp)) == SIDE_ENEMY){
				skip = 1;
			}
			do {
				
				res = WazaTool_CalcStraightFx(&wk->cm);
				
				if (cnt % 2){
					if (skip == 0){						
						if (no < WE338_OAM_MAX){ 
							CATS_ObjectPosSetCap(wk->cap[no], wk->cm.x, wk->cm.y);
							no++;
						}
					}
					else {
						skip = 0;
					}
				}
				cnt++;
				
			} while(res == TRUE);
		}
	
		///< 表示時間計算
		{
			int pri  = BT_BGPriorityGet(wk->ts.wsp, WES_BF_EFFECT);
			int pri2 = BT_BGPriorityGet(wk->ts.wsp, WES_BF_BACKGROUND);
			
			for (i = 0; i < WE338_OAM_MAX; i++){
				wk->time[i] = (WE338_OAM_MAX - i) * 4;
				
				if (WES_ContestFlag_Get(wk->ts.wsp) == FALSE){
					if (WET_SideCheck(wk->ts.wsp, WeSysATNoGet(wk->ts.wsp)) == SIDE_MINE){
						if (i < 4){
							CATS_ObjectBGPriSetCap(wk->cap[i], pri2);
						}
						else {
							CATS_ObjectBGPriSetCap(wk->cap[i], pri);
						}
					}
					else {
						if (i >= 4){
							CATS_ObjectBGPriSetCap(wk->cap[i], pri2);
						}
						else {
							CATS_ObjectBGPriSetCap(wk->cap[i], pri);
						}
					}
					CATS_ObjectPriSetCap(wk->cap[i], WE338_OAM_MAX-i);
				}
				else {
					CATS_ObjectPriSetCap(wk->cap[i], i);
					CATS_ObjectBGPriSetCap(wk->cap[i], pri2);
				}
			}
		}
	}

	WEEffect_TCB_AddPriSet(wk->ts.wsp, We338_TCB, wk);
}





typedef struct {

	TWE_TOOL_SYS	ts;
	
	CATS_ACT_PTR	cap[3];
	
	int wait;
	
	f32 fx;
	f32 fy;
	u8	eva;
	u8	evb;
	s8	flip;
	
	PAL_SFS_PTR			ps[2];
	
} WSP_272_SYS;

#define W272_WAIT	(14)

static void W272_TCB(TCB_PTR tcb, void* work)
{
	WSP_272_SYS* wk = work;
	
	switch(wk->ts.seq){
	case 0:
		
		if (wk->wait > W272_WAIT){
			wk->fy -= 0.2f;
			wk->fx += 0.2f;
			
			if (wk->fy <= 0.2){
				wk->ts.seq++;
				CATS_ObjectEnableCap(wk->cap[0], CATS_ENABLE_FALSE);
			}
			else {
				CATS_ObjectScaleSetCap(wk->cap[0], wk->fx * wk->flip, wk->fy);
			}
		}
		else {
			wk->eva++;
			wk->evb--;
			G2_ChangeBlendAlpha(wk->eva, wk->evb);
			wk->wait++;
		}
		
		break;
	
	case 1:
		
		if (IsPaletteSoftFade(wk->ps[1]) == FALSE){
			int pal_pos;
			PaletteSoftFadeDelete(wk->ps[0]);
			PaletteSoftFadeDelete(wk->ps[1]);
			pal_pos = GetPlttProxyOffset(CLACT_PaletteProxyGet(wk->cap[2]->act), NNS_G2D_VRAM_TYPE_2DMAIN);
			wk->ps[1] = PaletteSoftFade(wk->ts.pfd, WeSysHeapAreaGet(wk->ts.wsp), FADE_MAIN_OBJ,
										pal_pos * 16, 16, 0, 1, 15, 0, 0xFFFFFF, TCBPRI_WE_SUPPORT);
			wk->ts.seq++;
		}
		break;
	
	case 2:
	default:	
		if (IsPaletteSoftFade(wk->ps[1]) == FALSE){

			CATS_ObjectUpdateCap(wk->cap[1]);
			PaletteSoftFadeDelete(wk->ps[1]);
			WEEffect_TCB_Delete(wk->ts.wsp, tcb);
			sys_FreeMemoryEz(wk);
			return;
		}
		break;
	}
	
	CATS_ObjectUpdateCap(wk->cap[0]);
	CATS_ObjectUpdateCap(wk->cap[1]);
	CATS_ObjectUpdateCap(wk->cap[2]);
	
	CATS_Draw(wk->ts.poke_crp);
}

void WSP_272(WE_SYS_PTR we_sys)
{
	WSP_272_SYS* wk;
	int client;
	s16 x,y;
	s16 ofs_x;
	s16 r_vec;
		
	
	wk = WET_ALLOC_MEMORY(we_sys, WSP_272_SYS);
	
	WT_ToolSysInit(we_sys, &wk->ts);
	
	wk->cap[0] = WeSysPokeCapGet(wk->ts.wsp, 0);
	wk->cap[1] = WeSysPokeCapGet(wk->ts.wsp, 1);
	wk->cap[2] = WeSysPokeCapGet(wk->ts.wsp, 2);
	wk->wait = 0;
	
	{
		ofs_x = -32;
		
		r_vec = WazaTool_VecChangeX(we_sys, WeSysATNoGet(we_sys));
		
		ofs_x *= r_vec;
		
		wk->fx = 1.0f;
		wk->fy = 1.0f;
		
		if (ContestFlipCheck(we_sys, WEDEF_DROP_E1) == TRUE){
			wk->flip = -1;
		}
		else {
			wk->flip = +1;
		}
		
		CATS_ObjectPosGetCap(wk->cap[1], &x, &y);
		
		CATS_ObjectPosSetCap(wk->cap[0], x + ofs_x, y);
		CATS_ObjectAffineSetCap(wk->cap[0], CLACT_AFFINE_DOUBLE);
//		CATS_ObjectObjModeSetCap(wk->cap[0], GX_OAM_MODE_XLU);
		CATS_ObjectScaleSetCap(wk->cap[0], wk->fx * wk->flip, wk->fy);
		
	}
	
	{
		int pal_pos;
		
		pal_pos = GetPlttProxyOffset(CLACT_PaletteProxyGet(wk->cap[0]->act), NNS_G2D_VRAM_TYPE_2DMAIN);
		wk->ps[0] = PaletteSoftFade(wk->ts.pfd, WeSysHeapAreaGet(we_sys), FADE_MAIN_OBJ,
									pal_pos * 16, 16, 0, 1, 0, 15, 0xFFFFFF, TCBPRI_WE_SUPPORT);
									
		pal_pos = GetPlttProxyOffset(CLACT_PaletteProxyGet(wk->cap[2]->act), NNS_G2D_VRAM_TYPE_2DMAIN);
		wk->ps[1] = PaletteSoftFade(wk->ts.pfd, WeSysHeapAreaGet(we_sys), FADE_MAIN_OBJ,
									pal_pos * 16, 16, 0, 1, 0, 15, 0xFFFFFF, TCBPRI_WE_SUPPORT);
	}

	{
		u8 height;
		u8 client_no;
		u8 client_type;
		SOFT_SPRITE* ssp;
		WT_POINT p;
		WT_POINT p2;
		
		client_no = WeSysATNoGet(wk->ts.wsp);
		client_type = WET_ClientTypeGet(wk->ts.wsp, client_no);
		
		WET_PokeDefaultPosGet_ClientType(client_type, WES_ContestFlag_Get(wk->ts.wsp), &p);
		
		CATS_ObjectPosGetCap(wk->cap[0], &p2.x, &p2.y);
		
		{
			int dir;
			
			if (WET_SideCheck(wk->ts.wsp, client_no) == SIDE_MINE){
				dir = PARA_BACK;
				CATS_ObjectBGPriSetCap(wk->cap[0], 1);
				CATS_ObjectPriSetCap(wk->cap[0], 0);				
			}
			else {
				CATS_ObjectBGPriSetCap(wk->cap[0], 2);
				CATS_ObjectPriSetCap(wk->cap[0], 0);
				dir = PARA_FRONT;
			}
			
			client_no = WeSysDFNoGet(wk->ts.wsp);
			height = PokeHeightGet(WeSysMonsNoGet(wk->ts.wsp, client_no), WeSysSexGet(wk->ts.wsp, client_no), dir,
								   WeSysFormNoGet(wk->ts.wsp, client_no), WeSysPersonalRndGet(wk->ts.wsp, client_no));
		}

		CATS_ObjectPosSetCap(wk->cap[0], p2.x, p.y + height);
	//	CATS_ObjectPosSetCap(wk->cap[0], p2.x, p2.y);
	}

	CATS_ObjectEnableCap(wk->cap[0], CATS_ENABLE_TRUE);
			
	wk->eva = 0;
	wk->evb = 15;
	WET_DefaultBlendSet(wk->ts.wsp, WET_DEFAULT_BLEND, WET_DEFAULT_BLEND);
	G2_ChangeBlendAlpha(wk->eva, wk->evb);
	
	{
		TCB_PTR tcb;
		
		tcb = WEEffect_TCB_AddPriSet(wk->ts.wsp, W272_TCB, wk);
		
		W272_TCB(tcb, wk);
	}
}


///< よこどり

typedef struct {

	TWE_TOOL_SYS		ts;
	TWE_POKE_SYS		poke;	///< ポケモン汎用構造体	
	WAZATOOL_CALCMOVE	cm;		///< 汎用ワーク	
	
	s16	vec;
	int rev;
	
	WT_POINT		p[2];	/// 0 = my 
	
	int wait;
	
	int cnt;
	int	point_x[3];
	int	point_y[3];
	int	point_pri[3];
	
} WSP_289_SYS;

static void W289_TCB(TCB_PTR tcb, void* work)
{
	WSP_289_SYS* wk = (WSP_289_SYS*)work;
	
	switch(wk->ts.seq){
	case 0:
		///< 初期化			
		WazaTool_InitStraightSyncFx(&wk->cm,
									wk->poke.p.x, wk->point_x[wk->cnt],
									wk->point_y[wk->cnt], wk->point_y[wk->cnt], 
									15);
		SoftSpriteParaSet(wk->poke.ssp, SS_PARA_POS_Z, wk->point_pri[wk->cnt]);
		SoftSpriteParaSet(wk->poke.ssp, SS_PARA_SHADOW_Y_REQ, 1);
		wk->ts.seq++;
		
	case 1:
		///< 移動
		if (WazaTool_CalcStraightFx(&wk->cm) == FALSE){
			wk->cnt++;
			if (wk->cnt > 2){
				wk->ts.seq++;
			}
			else {
				{
					WAZA_POKE_CHANGE_PARAM para;
					
					if (wk->rev == 0){
											
						WeSys_PokeChangeParamMake(wk->ts.wsp, &para, WE_HENSIN_YOKODORI);
						
						if (wk->cnt == 2){
						//	HenshinChrSet(&para, WeSysHeapAreaGet(wk->ts.wsp));
							HenshinChrPop(&para, WeSysHeapAreaGet(wk->ts.wsp));
						}
						else {
						//	HenshinChrSet(&para, WeSysHeapAreaGet(wk->ts.wsp));
							YokodoriChrSet(&para, WeSysHeapAreaGet(wk->ts.wsp));
						}
						
					}
				}
				wk->ts.seq = 0;
			}
			wk->poke.p.x = SoftSpriteParaGet(wk->poke.ssp, SS_PARA_POS_X);
		}
		SoftSpriteParaSet(wk->poke.ssp, SS_PARA_POS_X, wk->cm.x);
		SoftSpriteParaSet(wk->poke.ssp, SS_PARA_POS_Y, wk->cm.y);
		break;
	
	default:
		SoftSpriteParaSet(wk->poke.ssp, SS_PARA_SHADOW_Y_REQ, 0);
		WEEffect_TCB_Delete(wk->ts.wsp, tcb);
		sys_FreeMemoryEz(wk);
		break;
	}			
}

void WSP_289(WE_SYS_PTR we_sys)
{
	int height;
	WSP_289_SYS* wk;
	
	wk = WET_ALLOC_MEMORY(we_sys, WSP_289_SYS);
	
	WT_ToolSysInit(we_sys, &wk->ts);

	{
		int client_no = WeSysATNoGet(wk->ts.wsp);
		
		WET_PokeDefaultPosGet_ClientNo(wk->ts.wsp, WeSysATNoGet(wk->ts.wsp), &wk->p[0]);
		WET_PokeDefaultPosGet_ClientNo(wk->ts.wsp, WeSysDFNoGet(wk->ts.wsp), &wk->p[1]);

		if (WET_SideCheck(wk->ts.wsp, client_no) == SIDE_MINE){
			wk->vec = +1;
		}
		else {
			wk->vec = -1;
		}
	}
	
	{
		int s1 = WET_SideCheck(wk->ts.wsp, WeSysATNoGet(wk->ts.wsp));
		int s2 = WET_SideCheck(wk->ts.wsp, WeSysDFNoGet(wk->ts.wsp));
		
		if (s1 == s2){
			
			wk->rev = 1;
			
		}
		else {
		
			wk->rev = 0;
			
		}
	}
	
	wk->cnt = 0;
	
	
	{
		int num;
		
		WT_SSPointerGet(we_sys, WeSysGPWorkGet(we_sys, 0), &(wk->poke), &num);
	}
	height = SoftSpriteParaGet(wk->poke.ssp, SS_PARA_POS_Y) - wk->p[0].y;
	
	if (wk->vec > 0){
		wk->point_x[0] = 255 + 80;
		wk->point_x[1] = 0 - 80;
		wk->point_x[2] = wk->p[0].x;
		
		wk->point_y[0] = wk->p[0].y + height;
		wk->point_y[1] = wk->p[1].y + height;
		wk->point_y[2] = wk->p[0].y + height;
		
		wk->point_pri[0] = ENCOUNT_Z_TYPE_C + 10;
		wk->point_pri[1] = ENCOUNT_Z_TYPE_D - 10;
		wk->point_pri[2] = SoftSpriteParaGet(wk->poke.ssp, SS_PARA_POS_Z);
	}
	else {
		wk->point_x[0] = 0 - 80;
		wk->point_x[1] = 255 + 80;
		wk->point_x[2] = wk->p[0].x;
		
		wk->point_y[0] = wk->p[0].y + height;
		wk->point_y[1] = wk->p[1].y + height;
		wk->point_y[2] = wk->p[0].y + height;
		
		wk->point_pri[0] = ENCOUNT_Z_TYPE_D - 10;
		wk->point_pri[1] = ENCOUNT_Z_TYPE_C + 10;
		wk->point_pri[2] = SoftSpriteParaGet(wk->poke.ssp, SS_PARA_POS_Z);
	}
	
	
	WEEffect_TCB_AddPriSet(wk->ts.wsp, W289_TCB, wk);
}

#define YOFS_166	(2)
#define YOFS_MAX	((80 / YOFS_166) - 2)
#define DRAW_166	(2)
typedef struct {
	
	int n_pos;
	int win_y;
	int win_x;
	int view_y;
	int view_x;
	int rev;
	int alpha;
	SOFT_SPRITE*		ssp;
	
	TWE_TOOL_SYS		ts;
	TWE_POKE_SYS		poke;	///< ポケモン汎用構造体	
	
} W166;

static void SSP_Visible(SOFT_SPRITE* ssp, int x, int w, int y, int h)
{
	SoftSpriteVisibleSet(ssp, x, 80 - y, w, h);
}

static void W166_Tcb(TCB_PTR tcb, void* work)
{
	W166* wk = work;
	
	switch(wk->ts.seq){
	case 0:
		wk->view_x += 79;
		if (wk->view_x >= 80){
			wk->ts.seq++;
			wk->rev ^= 1;
			wk->view_x = 0;
		}
		else {
			if (wk->rev == 0){
				SSP_Visible(wk->ssp, 0, wk->view_x, (wk->n_pos + DRAW_166) * YOFS_166, DRAW_166);
			}
			else {
				SSP_Visible(wk->ssp, 80 - wk->view_x, wk->view_x, (wk->n_pos + DRAW_166) * YOFS_166, DRAW_166);
			}
		}
		//wk->ts.seq++;
		break;

	case 1:
		wk->win_y  -= (YOFS_166 / 2);
		wk->view_y += (YOFS_166 / 2);
		G2_SetWnd0Position(wk->win_x, wk->win_y, wk->win_x + 80, wk->view_y);
		wk->ts.seq++;
		break;

	case 2:
		wk->win_y  -= (YOFS_166 / 2);
		wk->view_y += (YOFS_166 / 2);
		G2_SetWnd0Position(wk->win_x, wk->win_y, wk->win_x + 80, wk->view_y);
		wk->n_pos++;
		if (wk->n_pos > YOFS_MAX){
			wk->ts.seq++;
		}
		else {
			wk->ts.seq = 0;
		}
		break;
	
	case 3:
		SoftSpriteParaSet(wk->ssp, SS_PARA_VISIBLE, 0);
		wk->ts.seq++;
		break;
	
	default:
		GX_SetVisibleWnd(GX_WNDMASK_NONE);
		G2_SetWnd0InsidePlane(GX_WND_PLANEMASK_NONE, FALSE);
		G2_SetWndOutsidePlane(GX_WND_PLANEMASK_NONE, FALSE);
		G2_SetWnd0Position(0, 0, 0, 0);
		WEEffect_TCB_Delete(wk->ts.wsp, tcb);
		SoftSpriteParaSet(wk->ssp, SS_PARA_ALPHA, wk->alpha);
		sys_FreeMemoryEz(wk);
		break;
	}
}

void WSP_166(WE_SYS_PTR we_sys)
{
	W166* wk;
	
	wk = WET_ALLOC_MEMORY(we_sys, W166);

	WT_ToolSysInit(we_sys, &wk->ts);
	
	
	wk->ssp = WeSysSoftSpritePointerGet(we_sys, WeSysDFNoGet(we_sys));
	wk->n_pos = 0;
	
	{
		int type;
		
		type = WET_ClientTypeGet(we_sys, WeSysDFNoGet(we_sys));
		
		switch(type){
		case CLIENT_TYPE_B:
		case CLIENT_TYPE_C:
			GF_BGL_PrioritySet( GF_BGL_FRAME2_M, (BT_3DPriorityGet(we_sys) - 1) );
			break;
		}
	}
	
	{
		s16 x, y;
		
		x  = SoftSpriteParaGet(wk->ssp, SS_PARA_POS_X);
		y  = SoftSpriteParaGet(wk->ssp, SS_PARA_POS_Y);
		y -= SoftSpriteParaGet(wk->ssp, SS_PARA_SHADOW_HEIGHT);
		wk->alpha = SoftSpriteParaGet(wk->ssp, SS_PARA_ALPHA);
		SoftSpriteParaSet(wk->ssp, SS_PARA_ALPHA, 8);
		wk->win_x = x - 40;
		wk->win_y = y + 40;
		wk->view_x = 0;
		wk->view_y = wk->win_y;
		wk->rev = 0;
			
		GX_SetVisibleWnd(GX_WNDMASK_W0);
		G2_SetWnd0InsidePlane(GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 |
							  GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 |
							  GX_WND_PLANEMASK_OBJ, TRUE);
		G2_SetWndOutsidePlane(GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 |
							  GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ, TRUE);
		
		G2_SetWnd0Position(wk->win_x, wk->win_y, wk->win_x + 80, wk->view_y);
	}

	WEEffect_TCB_AddPriSet(wk->ts.wsp, W166_Tcb, wk);
}

