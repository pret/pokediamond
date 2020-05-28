//==============================================================================
/**
 * @file	wsp_goto2.c
 * @brief	簡単な説明を書く
 * @author	goto
 * @date	2005.11.30(水)
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

// -----------------------------------------
//
//
//		[ __WE_269__ ]	
//
//
// -----------------------------------------
#define WE269_EVA		(15)
#define WE269_EVB		(0)
#define WE269_EVAM		(0)
#define WE269_EVBM		(15)
#define WE269_EFF_TIME	(45)
#define WE269_WAIT		(10)
#define WE269_DEF_POS	(32)

// -----------------------------------------
//
//	構造体
//
// -----------------------------------------
typedef struct {
	
	u8	seq;
	u8	cnt[3];
	u8	wait;
	u8	cap_num;

	u8	eva;
	u8	evb;

	WE_SYS_PTR	 wsp;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	CATS_ACT_PTR cap[3];

	WAZATOOL_CALCMOVE cm;
	
} TWE_269_SYS;

// -----------------------------------------
//
//	タイムテーブル
//
// -----------------------------------------
static const u8 we269_wait[][2] = {
	{ 20, 2, },
	{ 13, 1, },
	{ 18, 3, },
};


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
static void We269_TCB(TCB_PTR tcb, void* work)
{
	int i;
	TWE_269_SYS* wk = (TWE_269_SYS*)work;

	switch(wk->seq){
	case 0:	
		///< ブリンクしながら表示
		///< フェード
		if (wk->eva < WE269_EVA){ wk->eva++; }
		if (wk->evb > WE269_EVB){ wk->evb--; }
		G2_ChangeBlendAlpha(wk->eva, wk->evb);
		
		wk->wait++;
		for (i = 0; i < wk->cap_num; i++){
			{
				s16 x,y;
				CATS_ObjectPosGetCap(wk->cap[i], &x, &y);
			}
			if (wk->wait >= we269_wait[i][0]){
				wk->cnt[i]++;
				if (wk->cnt[i] >= we269_wait[i][1]){
					wk->cnt[i] = 0;
				}
			}
		}
		if (wk->wait >= WE269_EFF_TIME){
			wk->seq++;
		}
		break;
		
	case 1:
		///< フェード
		if (wk->eva > WE269_EVAM){ wk->eva--; }
		if (wk->evb < WE269_EVBM){ wk->evb++; }
		
		if (wk->eva == WE269_EVAM
		&&	wk->evb == WE269_EVBM){
			wk->seq++;
		}
		G2_ChangeBlendAlpha(wk->eva, wk->evb);
		break;

	default:
		for (i = 0; i < wk->cap_num; i++){
			CATS_ActorPointerDelete_S(wk->cap[i]);
		}
		WEEffect_TCB_Delete(wk->wsp, tcb);
		sys_FreeMemoryEz(wk);
		return;
	}

	for (i = 0; i < wk->cap_num; i++){
		CATS_ObjectUpdate(wk->cap[i]->act);
	}
	CATS_Draw(wk->crp);
}


//--------------------------------------------------------------
/**
 * @brief	呼び出し関数
 *
 * @param	we_sys	
 * @param	csp	
 * @param	crp	
 * @param	cap	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WestSp_CAT_WE_269(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap)
{
	int i;	
	TWE_269_SYS* wk;
	TCATS_OBJECT_ADD_PARAM_S coap;
	
	wk = sys_AllocMemory(WeSysHeapAreaGet(we_sys), sizeof(TWE_269_SYS));
	
	GF_ASSERT(wk != NULL);
	
	wk->wait = 0;
	wk->seq = 0;
	wk->csp = csp;
	wk->crp = crp;

	wk->wsp = we_sys;
	coap    = WeSysCoapGet(we_sys);
	
	WET_DefaultBlendSet(wk->wsp, WET_DEFAULT_BLEND, WET_DEFAULT_BLEND);
	
	wk->cap_num = WeSysGPWorkGet(wk->wsp,0);
	wk->eva = WE269_EVAM;
	wk->evb = WE269_EVBM;
	G2_ChangeBlendAlpha(wk->eva, wk->evb);

	wk->cap[0] = cap;
	{	
		for (i = 1; i < wk->cap_num; i++){
			wk->cap[i] = CATS_ObjectAdd_S(wk->csp, wk->crp, &coap);
		}
	}
	
	if (WET_SideCheck(we_sys, WeSysDFNoGet(we_sys)) == SIDE_MINE){
		
		if (WET_SideCheck(we_sys, WeSysDFNoGet(we_sys)) == SIDE_MINE
		&&	WET_SideCheck(we_sys, WeSysATNoGet(we_sys)) == SIDE_MINE){	
			CATS_ObjectAnimeSeqSetCap(wk->cap[0], 0);
		}
		else {
			CATS_ObjectAnimeSeqSetCap(wk->cap[0], 1);
		}
		CATS_ObjectPosSetCap(wk->cap[0], 128, 80);
	}
	else {
		if (WET_SideCheck(we_sys, WeSysDFNoGet(we_sys)) == SIDE_ENEMY
		&&	WET_SideCheck(we_sys, WeSysATNoGet(we_sys)) == SIDE_ENEMY){	
			CATS_ObjectAnimeSeqSetCap(wk->cap[0], 1);
		}
		else {
			CATS_ObjectAnimeSeqSetCap(wk->cap[0], 0);
		}
		CATS_ObjectPosSetCap(wk->cap[0], 128, 80);
	}
	
	for (i = 0; i < wk->cap_num; i++){
		wk->cnt[i] = 0;
		CATS_ObjectAffineSetCap(wk->cap[i], CLACT_AFFINE_DOUBLE);
		CATS_ObjectObjModeSetCap(wk->cap[i], GX_OAM_MODE_XLU);
		
		if (WES_ContestFlag_Get(wk->wsp) == TRUE){
			CATS_ObjectScaleSetCap(wk->cap[i], -1.0f, 1.0f);
		}	
	}

	WEEffect_TCB_Add(we_sys, We269_TCB, wk, TCBPRI_WE_SUPPORT);
}








// -----------------------------------------
//
//
//		[ __WE_270__ ]	くものいと
//
//
// -----------------------------------------
#define WE270_EVA		(15)
#define WE270_EVB		(0)
#define WE270_EVAM		(0)
#define WE270_EVBM		(15)
#define WE270_EFF_TIME	(45)
#define WE270_WAIT		(10)
#define WE270_DEF_POS	(32)

#define WE270_X1		(80)
#define WE270_X2		(180)
#define WE270_Y1		(50)
#define WE270_Y2		(75)
#define WE270_Y3		(100)

static const WT_POINT pos_tbl_270[] = {
	{ WE270_X1, WE270_Y1 },
	{ WE270_X2, WE270_Y1 },
	{ WE270_X1, WE270_Y3 },
	{ WE270_X2, WE270_Y3 },
	{ WE270_X1, WE270_Y2 },
	{ WE270_X2, WE270_Y2 },
};

#define WE270_CX	(128)
#define WE270_CY	(80)
#define WE270_SYNC	(5)

static const WT_POINT move_pos_tbl_270[][2] = {
	{ { WE270_CX-8, WE270_CY },{ WE270_CX+8, WE270_CY }, },
	{ { WE270_CX-8, WE270_CY },{ WE270_CX+8, WE270_CY }, },
	{ { WE270_CX-8, WE270_CY },{ WE270_CX+8, WE270_CY }, },
	{ { WE270_CX-40, WE270_CY },{ WE270_CX+40, WE270_CY }, }
};

static const u8 move_sync_tbl_270[] = {
	WE270_SYNC,
	WE270_SYNC,
	WE270_SYNC,
	WE270_SYNC-2,
};

// -----------------------------------------
//
//	構造体
//
// -----------------------------------------
typedef struct {
	
	u8	seq;
	u8	cnt[6];
	u8	wait;
	u8	cap_num;

	u8	eva;
	u8	evb;

	WE_SYS_PTR	 wsp;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	CATS_ACT_PTR cap[6];
	
	int loop;
	CATS_ACT_PTR cap1;
	CATS_ACT_PTR cap2;

	WAZATOOL_CALCMOVE cm1;
	WAZATOOL_CALCMOVE cm2;
	
} TWE_270_SYS;

// -----------------------------------------
//
//	タイムテーブル
//
// -----------------------------------------
static const u8 we270_wait[][2] = {
	{ 20, 2, },
	{ 13, 1, },
	{ 18, 3, },
};


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
static void We270_TCB(TCB_PTR tcb, void* work)
{
	int i;
	int anm_stop = 0;
	TWE_270_SYS* wk = (TWE_270_SYS*)work;

	switch(wk->seq){
	case 0:	
		///< ブリンクしながら表示
		///< フェード
		if (wk->eva < WE270_EVA){ wk->eva++; }
		if (wk->evb > WE270_EVB){ wk->evb--; }
		
		if (wk->eva == WE270_EVA
		&&	wk->evb == WE270_EVB){
			wk->seq++;
		}
		G2_ChangeBlendAlpha(wk->eva, wk->evb);		
		break;
	
	case 1:
		///
		switch(wk->loop){
		case 0:
			wk->cap1 = wk->cap[0];
			wk->cap2 = wk->cap[3];
			CATS_ObjectEnableCap(wk->cap1, CATS_ENABLE_TRUE);
			CATS_ObjectEnableCap(wk->cap2, CATS_ENABLE_TRUE);
			break;
		case 1:
			wk->cap1 = wk->cap[1];
			wk->cap2 = wk->cap[2];
			CATS_ObjectEnableCap(wk->cap1, CATS_ENABLE_TRUE);
			CATS_ObjectEnableCap(wk->cap2, CATS_ENABLE_TRUE);
			break;
		case 2:
		case 3:
			wk->cap1 = wk->cap[4];
			wk->cap2 = wk->cap[5];
			CATS_ObjectEnableCap(wk->cap1, CATS_ENABLE_TRUE);
			CATS_ObjectEnableCap(wk->cap2, CATS_ENABLE_TRUE);
			break;
		}
		{
			s16 sx, sy;
			CATS_ObjectPosGetCap(wk->cap1, &sx, &sy);
			WazaTool_InitStraightSyncFx(&wk->cm1, sx, move_pos_tbl_270[wk->loop][0].x,
												  sy, move_pos_tbl_270[wk->loop][0].y, move_sync_tbl_270[wk->loop]);
			
			CATS_ObjectPosGetCap(wk->cap2, &sx, &sy);
			WazaTool_InitStraightSyncFx(&wk->cm2, sx, move_pos_tbl_270[wk->loop][1].x,
												  sy, move_pos_tbl_270[wk->loop][1].y, move_sync_tbl_270[wk->loop]);
		}
		wk->loop++;
		wk->seq++;
		break;
	
	case 2:
		///
		{
			int  check = 0;
			BOOL active;
			
			active = WazaTool_CalcAndReflectStraightFxCap(&wk->cm1, wk->cap1);
			if (active == FALSE){
				check++;
			}				
			active = WazaTool_CalcAndReflectStraightFxCap(&wk->cm2, wk->cap2);
			if (active == FALSE){
				check++;
			}
			
			if (check >= 2){
				if (wk->loop <= 3){
					CATS_ObjectEnableCap(wk->cap1, CATS_ENABLE_FALSE);
					CATS_ObjectEnableCap(wk->cap2, CATS_ENABLE_FALSE);
					wk->seq--;
				}
				else {
					wk->seq++;
				}
			}
		}
		break;
		
	case 3:
		///< フェード
		if (wk->eva > WE270_EVAM){ wk->eva--; }
		if (wk->evb < WE270_EVBM){ wk->evb++; }
		
		if (wk->evb >= (WE270_EVBM / 2)){
			anm_stop = 1;
		}
		
		if (wk->eva == WE270_EVAM
		&&	wk->evb == WE270_EVBM){
			wk->seq++;
		}
		G2_ChangeBlendAlpha(wk->eva, wk->evb);
		break;

	default:
		for (i = 0; i < wk->cap_num; i++){
			CATS_ActorPointerDelete_S(wk->cap[i]);
		}
		WEEffect_TCB_Delete(wk->wsp, tcb);
		sys_FreeMemoryEz(wk);
		return;
	}

	if (wk->seq < 3 && anm_stop == 0){
		for (i = 0; i < wk->cap_num; i++){
			CATS_ObjectUpdate(wk->cap[i]->act);
		}
	}
	CATS_Draw(wk->crp);
}


//--------------------------------------------------------------
/**
 * @brief	呼び出し関数
 *
 * @param	we_sys	
 * @param	csp	
 * @param	crp	
 * @param	cap	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WestSp_CAT_WE_270(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap)
{
	int i;	
	TWE_270_SYS* wk;
	TCATS_OBJECT_ADD_PARAM_S coap;
	
	wk = sys_AllocMemory(WeSysHeapAreaGet(we_sys), sizeof(TWE_270_SYS));
	
	GF_ASSERT(wk != NULL);
	
	wk->wait = 0;
	wk->seq = 0;
	wk->csp = csp;
	wk->crp = crp;
	wk->loop = 0;

	wk->wsp = we_sys;
	coap    = WeSysCoapGet(we_sys);
	
	WET_DefaultBlendSet(wk->wsp, WET_DEFAULT_BLEND, WET_DEFAULT_BLEND);
	
	wk->eva = WE270_EVAM;
	wk->evb = WE270_EVBM;
	G2_ChangeBlendAlpha(wk->eva, wk->evb);
	
	wk->cap_num = WeSysGPWorkGet(wk->wsp,0);
	wk->cap[0] = cap;
	{	
		for (i = 1; i < wk->cap_num; i++){
			wk->cap[i] = CATS_ObjectAdd_S(wk->csp, wk->crp, &coap);
		}
	}

	CATS_ObjectAnimeSeqSetCap(wk->cap[0], 0);	/// 1
	CATS_ObjectAnimeSeqSetCap(wk->cap[1], 0);
	CATS_ObjectAnimeSeqSetCap(wk->cap[2], 1);	/// 2
	CATS_ObjectAnimeSeqSetCap(wk->cap[3], 1);
	CATS_ObjectAnimeSeqSetCap(wk->cap[4], 2);	/// 3
	CATS_ObjectAnimeSeqSetCap(wk->cap[5], 3);
	
	CATS_ObjectFlipSetCap(wk->cap[0], CLACT_FLIP_H);	/// 2
	CATS_ObjectFlipSetCap(wk->cap[3], CLACT_FLIP_H);	/// 2
	
	for (i = 0; i < wk->cap_num; i++){
		CATS_ObjectAutoAnimeSetCap(wk->cap[i], CATS_ANM_AUTO_ON);
		CATS_ObjectPosSetCap(wk->cap[i], pos_tbl_270[i].x, pos_tbl_270[i].y);
		CATS_ObjectObjModeSetCap(wk->cap[i], GX_OAM_MODE_XLU);
	}
	
	CATS_ObjectEnableCap(wk->cap[1], CATS_ENABLE_FALSE);
	CATS_ObjectEnableCap(wk->cap[2], CATS_ENABLE_FALSE);
	CATS_ObjectEnableCap(wk->cap[4], CATS_ENABLE_FALSE);
	CATS_ObjectEnableCap(wk->cap[5], CATS_ENABLE_FALSE);

	WEEffect_TCB_Add(we_sys, We270_TCB, wk, TCBPRI_WE_SUPPORT);
}



// -----------------------------------------
//
//
//		[ __WE_274__ ]	くものいと
//
//
// -----------------------------------------
#define WE274_EVA		(15)
#define WE274_EVB		(0)
#define WE274_EVAM		(0)
#define WE274_EVBM		(15)
#define WE274_EFF_TIME	(45)
#define WE274_WAIT		(10)
#define WE274_DEF_POS	(32)

// -----------------------------------------
//
//	構造体
//
// -----------------------------------------
typedef struct {

	WE_SYS_PTR	 wsp;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;

	u8			 seq;
	u8			 wait;
	u8			 cnt;
	u8			 point;
	CATS_ACT_PTR cap;
	
	WAZATOOL_CALCMOVE cm;
	
	f32			 sc;
	
	int*		 check;
	
} TWE_CAT_HAND;

typedef struct {
	
	u8	seq;
	u8	wait;
	u8	cap_num;

	u8	eva;
	u8	evb;

	WE_SYS_PTR	 wsp;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	
	TWE_CAT_HAND ch[20];
	int			 check[20];
	
} TWE_274_SYS;

static const WT_POINT point_tbl_270[] = {
	{   0,  0 },
	{ 128,  0 },
	{ 256,  0 },
	{   0,170 },
	{ 128,170 },
	{ 256,170 },
};

enum {
	E274_CNT_WAIT = 1,
	E274_MOV,
	E274_MOV_WAIT,
};

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
static void We274_CH_TCB(TCB_PTR tcb, void* work)
{
	TWE_CAT_HAND* wk = (TWE_CAT_HAND*)work;
	
	switch(wk->seq){
	case 0:
		///< 一定期間待つ
		if ((--wk->cnt) <= 10){
			wk->seq++;
		}
		break;
	case 1:
		///< 拡大開始待ち
		if ((++wk->wait) >= 3){
			CATS_ObjectEnableCap(wk->cap, CATS_ENABLE_TRUE);
			wk->wait = 0;
			wk->seq++;
		}
		break;
	
	case 2:
		///< 拡大
		if ((++wk->wait) <= 3){
			wk->sc += 0.1f;
			CATS_ObjectScaleSetCap(wk->cap, wk->sc, wk->sc);
		}
		else {
			wk->wait = 0;
			wk->seq++;
		}
		break;

	case 3:
		///< 縮小
		if ((++wk->wait) <= 3){
			wk->sc -= 0.1f;
			CATS_ObjectScaleSetCap(wk->cap, wk->sc, wk->sc);
		}
		else {
			wk->wait = 0;
			wk->seq++;
		}
		break;
	case 4:
		///< フラグ落とし待ち
		if ((--wk->cnt) <= 10){
			*(wk->check) = E274_CNT_WAIT;
			wk->wait = 0;
			wk->seq++;
		}
		break;
	case 5:
		///< フラグ操作待ち
		if ((++wk->wait) > 30){
			wk->wait = 0;
			wk->seq++;
			break;
		}
		if ((*wk->check) == E274_MOV){
			wk->seq++;
		}
		break;
	case 6:
		///< 直線移動初期化
		{
			WT_POINT p;
			int sync;
			
			sync = 10 + (gf_rand() % 10);
			
			CATS_ObjectPosGetCap(wk->cap, &p.x, &p.y);
			WazaTool_InitStraightSyncFx(&wk->cm,
										p.x, point_tbl_270[wk->point].x,
										p.y, point_tbl_270[wk->point].y, sync);
			wk->seq++;
		}
		break;
	case 7:
		///< 移動
		{
			BOOL active;
			
			active = WazaTool_CalcAndReflectStraightFxCap(&wk->cm, wk->cap);
			
			if (active == FALSE){
				CATS_ObjectEnableCap(wk->cap, CATS_ENABLE_FALSE);
				wk->seq++;
			}
			else {
				break;
			}
		}
	default:
		*(wk->check) = E274_MOV_WAIT;
		WEEffect_TCB_Delete(wk->wsp, tcb);
		break;
	}
	
	CATS_ObjectUpdateCap(wk->cap);
}

static void We274_TCB(TCB_PTR tcb, void* work)
{
	int i;
	TWE_274_SYS* wk = (TWE_274_SYS*)work;
	
	switch(wk->seq){
	case 0:
		///< 出現待ち
		{
			BOOL check = TRUE;
			for (i = 0; i < wk->cap_num; i++){
				if (wk->check[i] != E274_CNT_WAIT){
					check = FALSE;
					break;
				}
			}
			if (check == TRUE){
				wk->seq++;
			}
		}
		break;
	case 1:
		///< 移動開始フラグセット
		for (i = 0; i < wk->cap_num; i++){
			wk->check[i] = E274_MOV;
		}
		wk->seq++;	
		break;
	
	case 2:
		///< 移動待ち
		{
			BOOL check = TRUE;
			for (i = 0; i < wk->cap_num; i++){
				if (wk->check[i] != E274_MOV_WAIT){
					check = FALSE;
					break;
				}
			}
			if (check == TRUE){
				wk->seq++;
			}
		}
		break;
	case 3:
		///< 終了
		for (i = 0; i < wk->cap_num; i++){
			CATS_ActorPointerDelete_S(wk->ch[i].cap);
		}
		wk->seq++;
		break;
	default:
		WEEffect_TCB_Delete(wk->wsp, tcb);
		sys_FreeMemoryEz(wk);
		return;
	}
	
	CATS_Draw(wk->crp);
}


//--------------------------------------------------------------
/**
 * @brief	呼び出し関数
 *
 * @param	we_sys	
 * @param	csp	
 * @param	crp	
 * @param	cap	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
#define W270_DISP_HSP		(30)
#define W270_DISP_WSP		(40)
#define W270_DISP_HEIGHT	(160 - (W270_DISP_HSP*2))
#define W270_DISP_HF		(W270_DISP_HEIGHT/2)
#define W270_DISP_WIDTH		(240 - (W270_DISP_WSP*2))
#define W270_DISP_WF		(W270_DISP_WIDTH/3)
static const s16 rand_rect[][4] = {
	{ W270_DISP_HSP, 			  W270_DISP_WSP, 							W270_DISP_HF, W270_DISP_WF },
	{ W270_DISP_HSP, 			  W270_DISP_WSP+W270_DISP_WF, 				W270_DISP_HF, W270_DISP_WF },
	{ W270_DISP_HSP, 			  W270_DISP_WSP+W270_DISP_WF+W270_DISP_WF,	W270_DISP_HF, W270_DISP_WF },
	{ W270_DISP_HSP+W270_DISP_HF, W270_DISP_WSP,							W270_DISP_HF, W270_DISP_WF },
	{ W270_DISP_HSP+W270_DISP_HF, W270_DISP_WSP+W270_DISP_WF,				W270_DISP_HF, W270_DISP_WF },
	{ W270_DISP_HSP+W270_DISP_HF, W270_DISP_WSP+W270_DISP_WF+W270_DISP_WF,	W270_DISP_HF, W270_DISP_WF },
};
void WestSp_CAT_WE_274(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap)
{
	int cnt;
	int i;	
	TWE_274_SYS* wk;
	TCATS_OBJECT_ADD_PARAM_S coap;
	
	wk = sys_AllocMemory(WeSysHeapAreaGet(we_sys), sizeof(TWE_274_SYS));
	
	GF_ASSERT(wk != NULL);

	wk->wait = 0;
	wk->seq = 0;
	wk->csp = csp;
	wk->crp = crp;

	wk->wsp = we_sys;
	coap    = WeSysCoapGet(we_sys);
	
	WET_DefaultBlendSet(wk->wsp, WET_DEFAULT_BLEND, WET_DEFAULT_BLEND);
	
	wk->cap_num = WeSysGPWorkGet(wk->wsp,0);
	OS_Printf("num = %2d\n",wk->cap_num);
	wk->cap_num = 12;

	{
		s16 x,y;
		CATS_ACT_PTR cap_tmp;
		
		wk->ch[0].cap = cap;
		cnt = 0;
		for (i = 0; i < wk->cap_num; i++){

			if (i != 0){
				wk->ch[i].cap = CATS_ObjectAdd_S(wk->csp, wk->crp, &coap);
			}
			cap_tmp = wk->ch[i].cap;	
			
			wk->ch[i].seq = 0;
			wk->ch[i].wait= 0;
			wk->ch[i].cnt = 10 + (gf_rand() % 10) + i;
			wk->ch[i].point = (gf_rand() % 6);
			wk->ch[i].sc  = 1.0f;
			wk->ch[i].wsp = wk->wsp;
			wk->ch[i].csp = wk->csp;
			wk->ch[i].crp = wk->crp;
			wk->ch[i].check = &wk->check[i];
			x = rand_rect[cnt][1] + (gf_rand() % rand_rect[cnt][3]);
			y = rand_rect[cnt][0] + (gf_rand() % rand_rect[cnt][2]);
			
			CATS_ObjectPosSetCap(cap_tmp, x, y);
			CATS_ObjectAffineSetCap(cap_tmp, CLACT_AFFINE_DOUBLE);
			CATS_ObjectScaleSetCap(cap_tmp, wk->ch[i].sc, wk->ch[i].sc);
			CATS_ObjectEnableCap(cap_tmp, CATS_ENABLE_FALSE);
			
			WEEffect_TCB_Add(we_sys, We274_CH_TCB, &wk->ch[i], TCBPRI_WE_SUPPORT - 1);
			
			cnt++;
			cnt %= 6;
		}		
	}
	
	WEEffect_TCB_Add(we_sys, We274_TCB, wk, TCBPRI_WE_SUPPORT + 1);
}


// =============================================================================
//
//
//	■293
//
//
// =============================================================================
typedef struct {
	
	int lst_wait;
	
	TWE_TOOL_SYS	ts;
	
	CATS_ACT_PTR	obj_win_cap;	// obj-window
	CATS_ACT_PTR	poke_cap;		// pokemon

	WAZATOOL_SCRLASTER_PTR	lst;	// laster
	
	WAZATOOL_ALPHA_FADE alpha;		// alpha
	
} TWE_293_SYS;

#define WE293_ROTA_ADD		(FX_GET_ROTA_NUM(2))
#define WE293_ROTA_WIDTH	(12*FX32_ONE)
#define WE293_SCR_SP_OFS	(2)
#define WE293_SCR_SP		(WE293_SCR_SP_OFS*100)

#define WE293_EVA_S			(16)
#define WE293_EVA_E			(2)
#define WE293_EVB_S			(2)
#define WE293_EVB_E			(16)
#define WE293_EV_FRAME		(16)
#define WE293_LST_WAIT		(120)

static void We293_TCB(TCB_PTR tcb, void* work)
{
	TWE_293_SYS* wk = (TWE_293_SYS*)work;
	
	switch(wk->ts.seq){
	case 0:
		{
			SOFT_SPRITE* ssp;
			ssp = WeSysSoftSpritePointerGet(wk->ts.wsp, WeSysATNoGet(wk->ts.wsp));
			SoftSpriteParaSet(ssp, SS_PARA_VANISH, 1);
		}
		wk->ts.seq++;
		break;
	case 1:
		// ラスター
		if (WazaTool_EndCheckAlphaFade(&wk->alpha) == FALSE){ break; }
		
		wk->lst_wait = 0;
		wk->lst = WazaTool_InitScrLaster( 
				0,
				160,
				WE293_ROTA_ADD,
				WE293_ROTA_WIDTH,
				WE293_SCR_SP,
				BT_BGL_BGNoGet(wk->ts.wsp, WES_BF_EFFECT),
				0,
				WazaTool_GetLasterBuffMatrixData(0, 0),
				WeSysHeapAreaGet(wk->ts.wsp));

		wk->ts.seq++;
		break;
		
	case 2:
		wk->lst_wait++;
		
		#if 0	///< 有効だと、移動できる
		
			if (sys.cont & PAD_BUTTON_A){
				s16 x,y;
				int mv_ofs = 2;
				
				wk->lst_wait--;
								
				CATS_ObjectPosGetCap(wk->obj_win_cap, &x, &y);
				
				if (sys.cont & PAD_KEY_UP){
					y-=mv_ofs;
				}
				if (sys.cont & PAD_KEY_DOWN){
					y+=mv_ofs;
				}
				if (sys.cont & PAD_KEY_RIGHT){
					x+=mv_ofs;
				}
				if (sys.cont & PAD_KEY_LEFT){
					x-=mv_ofs;
				}
				CATS_ObjectPosSetCap(wk->obj_win_cap, x, y);
				CATS_ObjectPosSetCap(wk->poke_cap, x, y);
				
			}
		
		#endif
		
		if (wk->lst_wait < WE293_LST_WAIT){ break; }

		WazaTool_DeleteScrLaster(wk->lst);

		WazaTool_StartAlphaFade(&wk->alpha,
						WE293_EVA_E, WE293_EVA_S,
						WE293_EVB_E, WE293_EVB_S, WE293_EV_FRAME);
		wk->ts.seq++;
		break;
	
	case 3:
		if (WazaTool_EndCheckAlphaFade(&wk->alpha) == FALSE){ break; }
		
		{
			SOFT_SPRITE* ssp;
			ssp = WeSysSoftSpritePointerGet(wk->ts.wsp, WeSysATNoGet(wk->ts.wsp));
			SoftSpriteParaSet(ssp, SS_PARA_VANISH, 0);
		}
		wk->ts.seq++;
		break;

	default:
		GX_SetVisibleWnd(GX_WNDMASK_NONE);
		WeSysBaseBGReset(wk->ts.wsp, BATTLE_FRAME_EFFECT);
		WEEffect_TCB_Delete(wk->ts.wsp, tcb);
		sys_FreeMemoryEz(wk);
		return;
	}
	
	CATS_ObjectUpdateCap(wk->poke_cap);
	CATS_ObjectUpdateCap(wk->obj_win_cap);
	
	CATS_Draw(wk->ts.poke_crp);
}

void WestSp_WE_293(WE_SYS_PTR we_sys)
{
	TWE_293_SYS* wk = NULL;
	
	wk = WET_ALLOC_MEMORY(we_sys, TWE_293_SYS);
	
	WT_ToolSysInit(we_sys, &wk->ts);

	///< ウィンドウOBJ
	wk->obj_win_cap = WeSysPokeCapGet(wk->ts.wsp, 0);
	CATS_ObjectObjModeSetCap(wk->obj_win_cap, GX_OAM_MODE_OBJWND);
	GX_SetVisibleWnd(GX_WNDMASK_OW);
	G2_SetWndOutsidePlane(GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 |
						  GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ,	FALSE);
	G2_SetWndOBJInsidePlane(GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_BG2 |
							GX_WND_PLANEMASK_OBJ, FALSE);
	
	///< 半透明OBJ
	wk->poke_cap = WeSysPokeCapGet(wk->ts.wsp, 1);
	CATS_ObjectObjModeSetCap(wk->poke_cap, GX_OAM_MODE_XLU);
	WazaTool_StartAlphaFade(&wk->alpha,
							WE293_EVA_S, WE293_EVA_E,
							WE293_EVB_S, WE293_EVB_E, WE293_EV_FRAME);

	WeSysBaseBGSet(wk->ts.wsp, BATTLE_FRAME_EFFECT);
	GF_BGL_VisibleSet(BATTLE_FRAME_EFFECT, VISIBLE_ON);
	
	WEEffect_TCB_AddPriSet(wk->ts.wsp, We293_TCB, wk);
}

// =============================================================================
//
//
//	■232　アイアンクロー
//
//
// =============================================================================
typedef struct {
	
	TWE_TOOL_SYS	ts;
	
	s16				wait;
	s16				time[4];
	CATS_ACT_PTR	cap[4];

} TWE_232_SYS;

void EnableCheckAnime(CATS_ACT_PTR cap)
{
	if (CATS_ObjectEnableGetCap(cap) == CATS_ENABLE_TRUE){		
		CATS_ObjectUpdateCap(cap);
	}
}

static void We232_TCB(TCB_PTR tcb, void* work)
{
	TWE_232_SYS* wk = (TWE_232_SYS*)work;
	
	if (wk->wait <= 0){
		EnableCheckAnime(wk->cap[2]);
		EnableCheckAnime(wk->cap[3]);
	}
	else {
		wk->wait--;
	}
	EnableCheckAnime(wk->cap[0]);
	EnableCheckAnime(wk->cap[1]);
	
	{
		int i;
		int check = 0;
		for (i = 0; i < 4; i++){
			wk->time[i]++;
			if (wk->time[i] >= 40){
				CATS_ObjectEnableCap(wk->cap[i], CATS_ENABLE_FALSE);
				check++;
			}
		}
		if (check == 4){
			for (i = 0; i < 4; i++){
				CATS_ActorPointerDelete_S(wk->cap[i]);
			}
			WEEffect_TCB_Delete(wk->ts.wsp, tcb);
			sys_FreeMemoryEz(wk);
			return;
		}
	}
	
	CATS_Draw(wk->ts.oam_crp);
}

void WestSp_CAT_WE_232(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap)
{
	TWE_232_SYS* wk = NULL;
	
	wk = WET_ALLOC_MEMORY(we_sys, TWE_232_SYS);
	
	wk->wait = 10;
	WT_ToolSysInit(we_sys, &wk->ts);
	
	{
		int i;
		TCATS_OBJECT_ADD_PARAM_S coap;
		coap = WeSysCoapGet(wk->ts.wsp);
		wk->cap[0]  = cap;
		wk->time[0] = 0;
		for (i = 1; i < 4; i++){
			wk->time[i] = 0;
			wk->cap[i]  = CATS_ObjectAdd_S(wk->ts.csp, wk->ts.oam_crp, &coap);
		}
		
		CATS_ObjectFlipSetCap(wk->cap[0], CLACT_FLIP_H);	///< 反転設定
		CATS_ObjectFlipSetCap(wk->cap[1], CLACT_FLIP_H);
		
		{
			WT_POINT p;
			
			
		}
		
		CATS_ObjectPosMoveCap(wk->cap[0], -32, 0);		///< 座標設定
		CATS_ObjectPosMoveCap(wk->cap[1], -32, +32);
		CATS_ObjectPosMoveCap(wk->cap[2], +32, 0);
		CATS_ObjectPosMoveCap(wk->cap[3], +32, +32);
	}

	WEEffect_TCB_AddPriSet(wk->ts.wsp, We232_TCB, wk);
}


// =============================================================================
//
//
//	■ねをはる
//
//
// =============================================================================
typedef struct {
	
	TWE_TOOL_SYS	ts;
	
	int pal_ofs;
	
	s16				wait;
	s16				time[4];
	CATS_ACT_PTR	cap[4];
	PAL_SFS_PTR		psp[ 6 ];
	
	int eva;
	int evb;

} TWE_275_SYS;

static void We275_TCB(TCB_PTR tcb, void* work)
{
	TWE_275_SYS* wk = (TWE_275_SYS*)work;
	
	{
		int i;
		int check = 0;
		for (i = 0; i < 4; i++){
			wk->time[i]++;
			if (wk->time[i] < 20){ continue; }
			
			EnableCheckAnime(wk->cap[i]);
			
			if (wk->time[0] == 110){
				WET_DefaultBlendSet(wk->ts.wsp, WET_DEFAULT_BLEND, WET_DEFAULT_BLEND);
				CATS_ObjectObjModeSetCap(wk->cap[0], GX_OAM_MODE_XLU);
				CATS_ObjectObjModeSetCap(wk->cap[1], GX_OAM_MODE_XLU);
				CATS_ObjectObjModeSetCap(wk->cap[2], GX_OAM_MODE_XLU);
				CATS_ObjectObjModeSetCap(wk->cap[3], GX_OAM_MODE_XLU);
				wk->eva = 15;
				wk->evb = 0;
			//	CATS_ObjectEnableCap(wk->cap[i], CATS_ENABLE_FALSE);
			//	check++;
			}
			/*
			if (wk->time[0] >= 160){
				if (wk->eva >  0){ wk->eva--; }
				if (wk->evb < 15){ wk->evb++; }
				G2_ChangeBlendAlpha(wk->eva, wk->evb);
				
				if (wk->eva == 0
				&&	wk->evb == 15){
					check = 4;
				}
			}
			*/
		}
		if (wk->time[0] == 40 + 10){
			wk->psp[0] = PaletteSoftFade(wk->ts.pfd, WeSysHeapAreaGet(wk->ts.wsp), FADE_MAIN_OBJ, wk->pal_ofs * 16, 16, -2, 2, 0, 14, 0xFFFF, 1002);
		}
		
		if (wk->time[0] == 50 + 10){
			wk->psp[1] = PaletteSoftFade(wk->ts.pfd, WeSysHeapAreaGet(wk->ts.wsp), FADE_MAIN_OBJ, wk->pal_ofs * 16, 16, -2, 2, 14, 0, 0xFFFF, 1002);
		}
		
		if (wk->time[0] == 60 + 10){
			wk->psp[2] = PaletteSoftFade(wk->ts.pfd, WeSysHeapAreaGet(wk->ts.wsp), FADE_MAIN_OBJ, wk->pal_ofs * 16, 16, -2, 2, 0, 14, 0xFFFF, 1002);
		}
		
		if (wk->time[0] == 70 + 10){
			wk->psp[3] = PaletteSoftFade(wk->ts.pfd, WeSysHeapAreaGet(wk->ts.wsp), FADE_MAIN_OBJ, wk->pal_ofs * 16, 16, -2, 2, 14, 0, 0xFFFF, 1002);
		}
		
		if (wk->time[0] == 80 + 10){
			wk->psp[4] = PaletteSoftFade(wk->ts.pfd, WeSysHeapAreaGet(wk->ts.wsp), FADE_MAIN_OBJ, wk->pal_ofs * 16, 16, -2, 2, 0, 14, 0xFFFF, 1002);
		}
		
		if (wk->time[0] == 90 + 10){
			wk->psp[5] = PaletteSoftFade(wk->ts.pfd, WeSysHeapAreaGet(wk->ts.wsp), FADE_MAIN_OBJ, wk->pal_ofs * 16, 16, -2, 2, 14, 0, 0xFFFF, 1002);
		}
		
		if (wk->time[0] == 110){
			WET_DefaultBlendSet(wk->ts.wsp, WET_DEFAULT_BLEND, WET_DEFAULT_BLEND);
			CATS_ObjectObjModeSetCap(wk->cap[0], GX_OAM_MODE_XLU);
			CATS_ObjectObjModeSetCap(wk->cap[1], GX_OAM_MODE_XLU);
			CATS_ObjectObjModeSetCap(wk->cap[2], GX_OAM_MODE_XLU);
			CATS_ObjectObjModeSetCap(wk->cap[3], GX_OAM_MODE_XLU);
			wk->eva = 15;
			wk->evb = 0;
		//	CATS_ObjectEnableCap(wk->cap[i], CATS_ENABLE_FALSE);
		//	check++;
		}
		if (wk->time[0] >= 110){
			if (wk->eva >  0){ wk->eva--; }
			if (wk->evb < 15){ wk->evb++; }
			G2_ChangeBlendAlpha(wk->eva, wk->evb);
			
			if (wk->eva == 0
			&&	wk->evb == 15){
				check = 4;
			}
		}
		if (check == 4){
			for (i = 0; i < 4; i++){
				CATS_ActorPointerDelete_S(wk->cap[ i ]);
			}
			for (i = 0; i < 6; i++){
				PaletteSoftFadeDelete(wk->psp[ i ]);
			}
			WEEffect_TCB_Delete(wk->ts.wsp, tcb);
			sys_FreeMemoryEz(wk);
			return;
		}
	}
	
	CATS_Draw(wk->ts.oam_crp);
}

void WestSp_CAT_WE_275(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap)
{
	TWE_275_SYS* wk = NULL;
	
	wk = WET_ALLOC_MEMORY(we_sys, TWE_275_SYS);
	
	wk->wait = 10;
	WT_ToolSysInit(we_sys, &wk->ts);
	
	{
		int i;
		s16 ofs1,ofs2;
		TCATS_OBJECT_ADD_PARAM_S coap;
		coap = WeSysCoapGet(wk->ts.wsp);
		wk->cap[0]  = cap;
		wk->time[0] = 0;
		for (i = 1; i < 4; i++){
			wk->time[i] = (gf_rand() % 4) + (i * 5);
			wk->cap[i]  = CATS_ObjectAdd_S(wk->ts.csp, wk->ts.oam_crp, &coap);
		}
		
		CATS_ObjectFlipSetCap(wk->cap[1], CLACT_FLIP_H);	///< 反転設定
		CATS_ObjectFlipSetCap(wk->cap[2], CLACT_FLIP_H);
		
		{
			s16 px;
			s16 py;
			int client_no;
			SOFT_SPRITE* ssp;
			
			client_no = WeSysATNoGet(we_sys);
			
			ssp = WeSysSoftSpritePointerGet(we_sys, client_no);
			
			px = SoftSpriteParaGet(ssp, SS_PARA_POS_X);
			py = SoftSpriteParaGet(ssp, SS_PARA_POS_Y);
			py += SoftSpriteParaGet(ssp, SS_PARA_SHADOW_HEIGHT);
			
			///< 座標固定Ver
			if (WET_SideCheck(we_sys, WeSysATNoGet(we_sys)) == SIDE_MINE){
				py = 140;
			}
			else {
				py = 84;
			}
			
			for (i = 0; i < 4; i++){
				CATS_ObjectPosSetCap(wk->cap[i], px, py);
			}
		}
		
		if (WET_SideCheck(we_sys, WeSysATNoGet(we_sys)) == SIDE_MINE){
			ofs2 = 24;
			ofs1 = 16;
			CATS_ObjectPriSetCap(wk->cap[0], 10);
			CATS_ObjectPriSetCap(wk->cap[2], 10);
			CATS_ObjectPriSetCap(wk->cap[1], 18);
			CATS_ObjectPriSetCap(wk->cap[3], 18);
		}
		else {
			ofs2 = 0;//40 - 8 - 6 - 12;
			ofs1 = 8;//32 - 8 - 6;
			CATS_ObjectPriSetCap(wk->cap[0], 18);
			CATS_ObjectPriSetCap(wk->cap[2], 18);
			CATS_ObjectPriSetCap(wk->cap[1], 10);
			CATS_ObjectPriSetCap(wk->cap[3], 10);
		}
		ofs1 = 4;
		ofs2 = 0;
		CATS_ObjectPosMoveCap(wk->cap[0], -32, +ofs2);		///< 座標設定
		CATS_ObjectPosMoveCap(wk->cap[3], -40, +ofs1);
		CATS_ObjectPosMoveCap(wk->cap[2], +32, +ofs2);
		CATS_ObjectPosMoveCap(wk->cap[1], +40, +ofs1);
	}
	
	{
		wk->pal_ofs = CATS_ObjectPaletteOffsetGetCap(wk->cap[0]);			
	//	bms->psp = PaletteSoftFade(bms->bmd.pfd, bms->bmd.heap_id, FADE_MAIN_OBJ, pal_ofs * 16, 16, -2, 2, 0, 14, 0xFFFF, 1002);
	}

	WEEffect_TCB_AddPriSet(wk->ts.wsp, We275_TCB, wk);
}


