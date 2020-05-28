//==============================================================================
/**
 * @file	wsp_goto.c
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

// =============================================================================
//
//	□ 検索用
//
//		[ __WE_070__ ]	かいりき
//		[ __WE_074__ ]	せいちょう
//		[ __WE_081__ ]	くものいと
//		[ __WE_096__ ]	ヨガのポーズ
//		[ __WE_100__ ]	テレポート
//		[ __WE_104__ ]	かげぶんしん
//		[ __WE_106__ ]	かたくなる
//		[ __WE_107__ ]	ちいさくなる
//		[ __WE_148__ ]	フラッシュ
//		[ __WE_150__ ]	はねる
//		[ __WE_271__ ]	トリック
//		[ __WE_339__ ]	ビルドアップ
//		[ __WE_089__ ]	じしん
//		[ __WE_171__ ]	あくむ
//		[ __WE_175__ ]	じたばた
//		[ __WE_222__ ]	マグニチュード
//		[ __WE_316__ ]	かぎわける
//		[ __WE_333__ ]	つららばり
//		[ __WE_057__ ]	なみのり
//
//
// =============================================================================

// -----------------------------------------
//
//
//		[ __WE_081__ ]	くものいと
//
//
// -----------------------------------------
#define WE081_EVA		(15)
#define WE081_EVB		(0)
#define WE081_EVAM		(0)
#define WE081_EVBM		(15)
#define WE081_EFF_TIME	(45)
#define WE081_WAIT		(10)
#define WE081_DEF_POS	(32)

// -----------------------------------------
//
//	構造体
//
// -----------------------------------------
typedef struct {
	
	u8	seq;
	u8	cnt[3];
	u8	wait;

	u8	eva;
	u8	evb;

	WE_SYS_PTR	 wsp;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	CATS_ACT_PTR cap[3];

	WAZATOOL_CALCMOVE cm;
	
} TWE_081_SYS;

// -----------------------------------------
//
//	タイムテーブル
//
// -----------------------------------------
static const u8 we081_wait[][2] = {
	{  8, 2, },
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
static void We081_TCB(TCB_PTR tcb, void* work)
{
	int i;
	TWE_081_SYS* wk = (TWE_081_SYS*)work;

	switch(wk->seq){
	case 0:	
		///< ブリンクしながら表示
		wk->wait++;
		for (i = 0; i < WeSysGPWorkGet(wk->wsp,0); i++){
			{
				s16 x,y;
				CATS_ObjectPosGetCap(wk->cap[i], &x, &y);
			}
			if (wk->wait >= we081_wait[i][0]){
				wk->cnt[i]++;
				if (wk->cnt[i] >= we081_wait[i][1]){
					wk->cnt[i] = 0;
					if (CATS_ObjectEnableGetCap(wk->cap[i]) == CATS_ENABLE_TRUE){
						CATS_ObjectEnableCap(wk->cap[i], CATS_ENABLE_FALSE);
					}
					else {
						CATS_ObjectEnableCap(wk->cap[i], CATS_ENABLE_TRUE);
					}
				}
			}
			else {
				CATS_ObjectEnableCap(wk->cap[i], CATS_ENABLE_FALSE);
			}
		}
		if (wk->wait >= WE081_EFF_TIME){
			for (i = 0; i < WeSysGPWorkGet(wk->wsp, 0); i++){
				CATS_ObjectEnableCap(wk->cap[i], CATS_ENABLE_TRUE);
			}
			wk->wait = 0;	// 締め付け待ちに使う
			wk->seq++;
		}
		break;
	
	case 1:
		///< 締め付け
		WazaTool_InitScaleRateEx(&wk->cm,
								 100, 60, 100,100, 100, 10);
		wk->seq++;
		break;
	
	case 2:
		///< 締め付け
		if (WazaTool_CalcScaleRateEx(&wk->cm) == TRUE){
			for (i = 0; i < WeSysGPWorkGet(wk->wsp, 0); i++){
				f32 x, y;
				WazaTool_CalcScaleRateToClactScale(&wk->cm, &x, &y);
				CATS_ObjectScaleSetCap(wk->cap[i], x, y);
			}
		}
		else {
			if (++wk->wait >= WE081_EFF_TIME){
				wk->seq++;
			}
		}		
		break;
		
	case 3:
		///< フェード
		if (wk->eva > WE081_EVAM){ wk->eva--; }
		if (wk->evb < WE081_EVBM){ wk->evb++; }
		
		if (wk->eva == WE081_EVAM
		&&	wk->evb == WE081_EVBM){
			wk->seq++;
		}
		G2_ChangeBlendAlpha(wk->eva, wk->evb);
		break;

	default:
		for (i = 0; i < WeSysGPWorkGet(wk->wsp, 0); i++){
			CATS_ActorPointerDelete_S(wk->cap[i]);
		}
		WEEffect_TCB_Delete(wk->wsp, tcb);
		sys_FreeMemoryEz(wk);
		return;
	}

	for (i = 0; i < WeSysGPWorkGet(wk->wsp, 0); i++){
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
void WestSp_CAT_WE_081(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap)
{
	int i;	
	TWE_081_SYS* wk;
	TCATS_OBJECT_ADD_PARAM_S coap;
	
	wk = sys_AllocMemory(WeSysHeapAreaGet(we_sys), sizeof(TWE_081_SYS));
	
	GF_ASSERT(wk != NULL);
	
	wk->wait = 0;
	wk->seq = 0;
	wk->csp = csp;
	wk->crp = crp;

	wk->wsp = we_sys;
	coap    = WeSysCoapGet(we_sys);
	
	WET_DefaultBlendSet(wk->wsp, WET_DEFAULT_BLEND, WET_DEFAULT_BLEND);
	
	wk->eva = WE081_EVA;
	wk->evb = WE081_EVB;
	G2_ChangeBlendAlpha(wk->eva, wk->evb);

	wk->cap[0] = cap;
	{	
		WT_POINT p;
		int side = WET_SideCheck(we_sys, WeSysDFNoGet(we_sys));
		
		if (side == SIDE_MINE){
			WET_PokeDefaultPosGet_ClientType(CLIENT_TYPE_AA, WES_ContestFlag_Get(we_sys), &p);
		}
		else {
			WET_PokeDefaultPosGet_ClientType(CLIENT_TYPE_BB, WES_ContestFlag_Get(we_sys), &p);
		}
			
	
		for (i = 1; i < WeSysGPWorkGet(wk->wsp,0); i++){
			wk->cap[i] = CATS_ObjectAdd_S(wk->csp, wk->crp, &coap);
			
			CATS_ObjectPosSetCap(wk->cap[i], p.x, p.y);
		}
		CATS_ObjectPosSetCap(wk->cap[0], p.x, p.y);
	}
	
	for (i = 0; i < WeSysGPWorkGet(wk->wsp,0); i++){
		wk->cnt[i] = 0;
		CATS_ObjectAffineSetCap(wk->cap[i], CLACT_AFFINE_DOUBLE);
		CATS_ObjectPosMoveCap(wk->cap[i], 0, WE081_DEF_POS - (i*4));
		CATS_ObjectObjModeSetCap(wk->cap[i], GX_OAM_MODE_XLU);
	}

	WEEffect_TCB_Add(we_sys, We081_TCB, wk, 0x1000);
}





// -----------------------------------------
//
//
//		[ __WE_070__ ]	かいりき
//
//
// -----------------------------------------

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
	
	WE_SYS_PTR		wsp;
	SOFT_SPRITE*	ssp;
	
	WAZATOOL_CALCMOVE cm;
	WAZATOOL_CALCMOVE shake;
	
} TWE_070_SYS;

#define WE070_FADE_CNT		(3)
#define WE070_SS_FADE_WAIT	(0)
#define WE070_SS_FADE_COL	(0x1F)
#define WE070_END_EVY		(10)

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
static void We070_TCB(TCB_PTR tcb, void* work)
{
	TWE_070_SYS* wk = (TWE_070_SYS*)work;
	
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
		///< 赤フェード
		SoftSpritePalFadeSet(wk->ssp, 0, WE070_END_EVY, WE070_SS_FADE_WAIT, WE070_SS_FADE_COL);
		wk->seq++;
		break;
	case 2:
		///< フェードif (PaletteFadeCheck(wk->pfd) == 0
		if (SoftSpritePalFadeExist(wk->ssp) == FALSE){
			SoftSpritePalFadeSet(wk->ssp, WE070_END_EVY, 0, WE070_SS_FADE_WAIT, WE070_SS_FADE_COL);
			wk->seq++;
		}
		break;
		
	case 3:
		///< フェード
		if (SoftSpritePalFadeExist(wk->ssp) == FALSE){
			wk->fade_cnt++;
			if (wk->fade_cnt >= WE070_FADE_CNT){
				WazaTool_InitScaleRate(&wk->cm,
							   		   WeSysGPWorkGet(wk->wsp, 0),
							   		   100,
							   		   WeSysGPWorkGet(wk->wsp, 1),
							   		   WeSysGPWorkGet(wk->wsp, 3));
				wk->seq++;
			}
			else {
				wk->seq = 1;
			}
		}
		break;
	
	case 4:
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
	case 5:
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
void WestSp_WE_070(WE_SYS_PTR we_sys)
{
	TWE_070_SYS* wk;
	
	wk = sys_AllocMemory(WeSysHeapAreaGet(we_sys), sizeof(TWE_070_SYS));
	
	wk->fade_cnt = 0;
	wk->seq = 0;
	wk->wsp = we_sys;
	wk->ssp = WeSysSoftSpritePointerGet( wk->wsp, WeSysATNoGet(wk->wsp) );
	
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
						   
	
	WEEffect_TCB_AddPriSet(wk->wsp, We070_TCB, wk);
}


// -----------------------------------------
//
//
//		[ __WE_339__ ]	ビルドアップ
//
//
// -----------------------------------------

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
	
	WE_SYS_PTR		wsp;
	SOFT_SPRITE*	ssp;
	
	WAZATOOL_CALCMOVE cm;
	WAZATOOL_CALCMOVE shake;
	
} TWE_339_SYS;


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
static void We339_TCB(TCB_PTR tcb, void* work)
{
	TWE_339_SYS* wk = (TWE_339_SYS*)work;
	
	switch(wk->seq){
	case 0:
		///< 横縮み
		if (WazaTool_CalcScaleRateEx(&wk->cm) == TRUE){
			SoftSpriteParaSet(wk->ssp, SS_PARA_AFF_X, wk->cm.x);
			SoftSpriteParaSet(wk->ssp, SS_PARA_AFF_Y, wk->cm.y);
			{
				s16 ofs_y = WazaTool_CalcScaleRateToYPosFX(wk->dy, wk->poke_h, wk->cm.work[4]);
				SoftSpriteParaSet(wk->ssp, SS_PARA_POS_Y, wk->dy + ofs_y);
			}
		}
		else {
			WazaTool_InitScaleRateEx(&wk->cm, 150, 50, 50, 150, 100, 10);
			wk->seq++;
		}		
		break;
	case 1:
		///< 縦縮み
		if (WazaTool_CalcScaleRateEx(&wk->cm) == TRUE){
			SoftSpriteParaSet(wk->ssp, SS_PARA_AFF_X, wk->cm.x);
			SoftSpriteParaSet(wk->ssp, SS_PARA_AFF_Y, wk->cm.y);
			{
				s16 ofs_y = WazaTool_CalcScaleRateToYPosFX(wk->dy, wk->poke_h, wk->cm.work[4]);
				SoftSpriteParaSet(wk->ssp, SS_PARA_POS_Y, wk->dy + ofs_y);
			}
		}
		else {
			WazaTool_InitScaleRateEx(&wk->cm, 50, 100, 150, 100, 100, 5);
			wk->seq++;
		}
		break;
	case 2:
		///< 戻り
		if (WazaTool_CalcScaleRateEx(&wk->cm) == TRUE){
			SoftSpriteParaSet(wk->ssp, SS_PARA_AFF_X, wk->cm.x);
			SoftSpriteParaSet(wk->ssp, SS_PARA_AFF_Y, wk->cm.y);
			{
				s16 ofs_y = WazaTool_CalcScaleRateToYPosFX(wk->dy, wk->poke_h, wk->cm.work[4]);	
				SoftSpriteParaSet(wk->ssp, SS_PARA_POS_Y, wk->dy + ofs_y);
			}
		}
		else {
			WazaTool_InitScaleRateEx(&wk->cm, 100, 150, 100, 150, 100, 5);
			wk->seq++;
		}
		break;
	case 3:
		///< ぼよん
		if (WazaTool_CalcScaleRateEx(&wk->cm) == TRUE){
			SoftSpriteParaSet(wk->ssp, SS_PARA_AFF_X, wk->cm.x);
			SoftSpriteParaSet(wk->ssp, SS_PARA_AFF_Y, wk->cm.y);
			{
				s16 ofs_y = WazaTool_CalcScaleRateToYPosFX(wk->dy, wk->poke_h, wk->cm.work[4]);
				SoftSpriteParaSet(wk->ssp, SS_PARA_POS_Y, wk->dy + ofs_y);
			}
		}
		else {
			WazaTool_InitScaleRateEx(&wk->cm, 150, 100, 150, 100, 100, 5);
			wk->seq++;
		}
		break;
	case 4:
		///< 戻り
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
void WestSp_WE_339(WE_SYS_PTR we_sys)
{
	TWE_339_SYS* wk;
	
	wk = sys_AllocMemory(WeSysHeapAreaGet(we_sys), sizeof(TWE_339_SYS));
	
	wk->seq = 0;
	wk->wsp = we_sys;
	wk->ssp = WeSysSoftSpritePointerGet( wk->wsp, WeSysATNoGet(wk->wsp) );
	
	wk->dy  = SoftSpriteParaGet(wk->ssp, SS_PARA_POS_Y);
	wk->poke_h = WeSysPokeOfsGet(wk->wsp, WeSysATNoGet(wk->wsp));

	///< 拡縮
	WazaTool_InitScaleRateEx(&wk->cm, 100, 150, 100, 50, 100, 10);	
	WEEffect_TCB_AddPriSet(wk->wsp, We339_TCB, wk);
}


// -----------------------------------------
//
//
//		[ __WE_104__ ]	かげぶんしん
//
//		■ □ 本体 □ ■
//		１ ３　　　２ ０
//
// -----------------------------------------
#define WE104_OAM_MAX	(4)
#define WE104_RANGE		(32)
#define WE104_WAIT_1	(7)
#define WE104_WAIT_2	(10)
#define WE104_OBJ_PRI_1	(10)
#define WE104_OBJ_PRI_2	(20)
#define WE104_EVA		(8)
#define WE104_EVB		(6)
#define WE104_EVM		(15)
#define WE104_LOOP		(9)


// -----------------------------------------
//
//	構造体
//
// -----------------------------------------
typedef struct {
	
	u8	loop;
	u8	seq;
	u16	wait;
	u8	eva;
	u8	evb;
	u16 dmy;
	
	s16 poke_x;
	s16 poke_y;
	
	WE_SYS_PTR		wsp;
	SOFT_SPRITE*	ssp;
	
	CATS_RES_PTR	  crp;
	CATS_ACT_PTR	  cap[ WE104_OAM_MAX ];
	WAZATOOL_CALCMOVE cm[ WE104_OAM_MAX ];
	
} TWE_104_SYS;

// -----------------------------------------
//
//	移動座標テーブル
//
// -----------------------------------------
static const s16 we_104_pos[][3] = {
	{  0, WE104_RANGE, WE104_WAIT_1 },
	{  0, WE104_RANGE, WE104_WAIT_2 },
	{ WE104_RANGE,  0, WE104_WAIT_1 },
	{ WE104_RANGE,  0, WE104_WAIT_2 },
};


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
static void We104_TCB(TCB_PTR tcb, void* work)
{
	int i;
	u8	res;
	TWE_104_SYS* wk = (TWE_104_SYS*)work;
	
	switch(wk->seq){
	case 0:
		///< 初期化処理
		{
			int no   = (wk->loop % 2) * 2;
			int wait = (wk->loop + 1) / 2;

			WazaTool_InitStraightSyncFx(&wk->cm[0],
										wk->poke_x + we_104_pos[no][0], 
										wk->poke_x + we_104_pos[no][1],
										wk->poke_y,
										wk->poke_y,
										we_104_pos[no][2] - wait);
									  
			WazaTool_InitStraightSyncFx(&wk->cm[1],
										wk->poke_x - we_104_pos[no][0],
										wk->poke_x - we_104_pos[no][1],
										wk->poke_y,
										wk->poke_y,
										we_104_pos[no][2] - wait);
			
			WazaTool_InitStraightSyncFx(&wk->cm[2],
										wk->poke_x + we_104_pos[no + 1][0],
										wk->poke_x + we_104_pos[no + 1][1],
										wk->poke_y,
										wk->poke_y,
										we_104_pos[no + 1][2] - wait);
									  
			WazaTool_InitStraightSyncFx(&wk->cm[3],
									 	wk->poke_x - we_104_pos[no + 1][0],
									 	wk->poke_x - we_104_pos[no + 1][1],
									 	wk->poke_y,
									 	wk->poke_y,
									 	we_104_pos[no + 1][2] - wait);
		}
		wk->loop++;
		wk->seq++;

	case 1:
		///< 移動処理
		res = 0;
		for (i = 0; i < WE104_OAM_MAX; i++){
			if (WazaTool_CalcStraightFx(&wk->cm[i]) == FALSE){
				res++;
			}
			else {
				CATS_ObjectPosSetCap(wk->cap[i], wk->cm[i].x, wk->cm[i].y);
			}
			CATS_ObjectUpdateCap(wk->cap[i]);
		}

		if (res == WE104_OAM_MAX){
			if (wk->loop == WE104_LOOP){
				wk->seq++;
			}
			else {
				wk->seq = 0;
			}
		}	
		break;
		
	case 2:
		///< 分身フェードアウト
		if (wk->eva > 0){ wk->eva--; }
		if (wk->evb < WE104_EVM){ wk->evb++; }
		
		if (wk->eva == 0
		&&	wk->evb == WE104_EVM){
			wk->seq++;
		}
		G2_ChangeBlendAlpha(wk->eva, wk->evb);
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
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WestSp_WE_104(WE_SYS_PTR we_sys)
{
	TWE_104_SYS* wk;
	
	wk = sys_AllocMemory(WeSysHeapAreaGet(we_sys), sizeof(TWE_104_SYS));
	
	wk->seq		= 0;
	wk->loop	= 0;
	wk->wsp		= we_sys;
	wk->ssp		= WeSysSoftSpritePointerGet( wk->wsp, WeSysATNoGet(wk->wsp) );
	wk->poke_x	= SoftSpriteParaGet(wk->ssp, SS_PARA_POS_X);
	wk->poke_y	= SoftSpriteParaGet(wk->ssp, SS_PARA_POS_Y);
	wk->poke_y	-= SoftSpriteParaGet(wk->ssp, SS_PARA_SHADOW_HEIGHT);
	wk->crp		= WeSysPokeCrpGet(wk->wsp);
	
	wk->eva		= WE104_EVA;
	wk->evb		= WE104_EVB;
	
	
	WET_DefaultBlendSet(wk->wsp, WET_DEFAULT_BLEND, WET_DEFAULT_BLEND);
	G2_ChangeBlendAlpha(wk->eva, wk->evb);
	
	{
		int i;
		u16 pal_pos;
		int index_no = WeSysPalIDGet(wk->wsp, WeSysATNoGet(wk->wsp));
		int bg_pri   = BT_3DPriorityGet(wk->wsp);
		int arcID	 = WeSysArcIDGet(wk->wsp, WeSysATNoGet(wk->wsp));
		
		for (i = 0; i < WE104_OAM_MAX; i++){
			wk->cap[i] = WeSysPokeCapGet(wk->wsp, i);
			CATS_ObjectObjModeSetCap(wk->cap[i], GX_OAM_MODE_XLU);
		}
		
		if (WET_SideCheck(wk->wsp, WeSysATNoGet(wk->wsp)) == SIDE_MINE){
			CATS_ObjectPriSetCap(wk->cap[0], WE104_OBJ_PRI_1);
			CATS_ObjectPriSetCap(wk->cap[1], WE104_OBJ_PRI_1);
			CATS_ObjectPriSetCap(wk->cap[2], WE104_OBJ_PRI_2);
			CATS_ObjectPriSetCap(wk->cap[3], WE104_OBJ_PRI_2);
			CATS_ObjectBGPriSetCap(wk->cap[0], bg_pri);
			CATS_ObjectBGPriSetCap(wk->cap[1], bg_pri);
			CATS_ObjectBGPriSetCap(wk->cap[2], bg_pri);
			CATS_ObjectBGPriSetCap(wk->cap[3], bg_pri);
			
			pal_pos = GetPlttProxyOffset(CLACT_PaletteProxyGet(wk->cap[0]->act), NNS_G2D_VRAM_TYPE_2DMAIN);
			PokeColorChange(WeSysPFDGet(wk->wsp), arcID, index_no,
							WeSysHeapAreaGet(we_sys), FADE_MAIN_OBJ,
							0x20, pal_pos * 16, 128,128,128);

			pal_pos = GetPlttProxyOffset(CLACT_PaletteProxyGet(wk->cap[2]->act), NNS_G2D_VRAM_TYPE_2DMAIN);
			PokeColorChange(WeSysPFDGet(wk->wsp), arcID,	index_no,
							WeSysHeapAreaGet(we_sys), FADE_MAIN_OBJ,
							0x20, pal_pos * 16,	196,196,196);
		}
		else {
			CATS_ObjectPriSetCap(wk->cap[0], WE104_OBJ_PRI_2);
			CATS_ObjectPriSetCap(wk->cap[1], WE104_OBJ_PRI_2);
			CATS_ObjectPriSetCap(wk->cap[2], WE104_OBJ_PRI_1);
			CATS_ObjectPriSetCap(wk->cap[3], WE104_OBJ_PRI_1);
			CATS_ObjectBGPriSetCap(wk->cap[0], bg_pri + 1);
			CATS_ObjectBGPriSetCap(wk->cap[1], bg_pri + 1);
			CATS_ObjectBGPriSetCap(wk->cap[2], bg_pri + 1);
			CATS_ObjectBGPriSetCap(wk->cap[3], bg_pri + 1);
			CATS_ObjectBGPriSetCap(wk->cap[0], bg_pri);
			CATS_ObjectBGPriSetCap(wk->cap[1], bg_pri);
			CATS_ObjectBGPriSetCap(wk->cap[2], bg_pri);
			CATS_ObjectBGPriSetCap(wk->cap[3], bg_pri);
						
			pal_pos = GetPlttProxyOffset(CLACT_PaletteProxyGet(wk->cap[0]->act), NNS_G2D_VRAM_TYPE_2DMAIN);
			PokeColorChange(WeSysPFDGet(wk->wsp), arcID,	index_no,
							WeSysHeapAreaGet(we_sys), FADE_MAIN_OBJ,
							0x20, pal_pos * 16,	196,196,196);

			pal_pos = GetPlttProxyOffset(CLACT_PaletteProxyGet(wk->cap[2]->act), NNS_G2D_VRAM_TYPE_2DMAIN);
			PokeColorChange(WeSysPFDGet(wk->wsp), arcID,	index_no,
							WeSysHeapAreaGet(we_sys), FADE_MAIN_OBJ,
							0x20, pal_pos * 16,	128,128,128);
		}
	}

	WEEffect_TCB_AddPriSet(wk->wsp, We104_TCB, wk);
}




// -----------------------------------------
//
//
//		[ __WE_074__ ]	
//
//
// -----------------------------------------
typedef struct {
	
	u8	seq;
	u8	cnt;
	
	u8	step;

	WE_SYS_PTR		wsp;
	SOFT_SPRITE*	ssp;
	WAZATOOL_CALCMOVE cm;
	
} TWE_074_SYS;

#define WE074_CNT_MAX		(4)
#define WE074_END_EVY		(6)
#define WE074_SS_FADE_WAIT	(0)
#define WE074_SS_FADE_COL	(0x7FFF)

static const u8 w074_step_data[][3] = {
	{ 100, 115, 6 },
	{ 115, 100, 6 },
};

static void We074_TCB(TCB_PTR tcb, void* work)
{
	TWE_074_SYS* wk = (TWE_074_SYS*)work;
	
	switch(wk->seq){
	case 0:
		///< 拡縮パラメーター設定
		WazaTool_InitScaleRate(&wk->cm,
							   w074_step_data[wk->step][0],
							   100,
							   w074_step_data[wk->step][1],
							   w074_step_data[wk->step][2]);

		if (wk->step == 0){
			SoftSpritePalFadeSet(wk->ssp, 0, WE074_END_EVY, WE074_SS_FADE_WAIT, WE074_SS_FADE_COL);
		}
		else {
			SoftSpritePalFadeSet(wk->ssp, WE074_END_EVY, 0, WE074_SS_FADE_WAIT, WE074_SS_FADE_COL);
		}

		wk->step ^= 1;
		wk->cnt++;
		wk->seq++;
		break;

	case 1:
		///< 拡縮
		if (WazaTool_CalcScaleRate(&wk->cm) == FALSE
		&&	SoftSpritePalFadeExist(wk->ssp) == FALSE){
			if (wk->cnt < WE074_CNT_MAX){
				wk->seq--;
			}
			else {
				wk->seq++;
			}
		}
		SoftSpriteParaSet(wk->ssp, SS_PARA_AFF_X, wk->cm.x);
		SoftSpriteParaSet(wk->ssp, SS_PARA_AFF_Y, wk->cm.y);
		break;

	default:
		///< 終了
		WEEffect_TCB_Delete(wk->wsp, tcb);
		sys_FreeMemoryEz(wk);		
		break;
	}
}

void WestSp_WE_074(WE_SYS_PTR we_sys)
{
	TWE_074_SYS* wk;
	
	wk = WET_ALLOC_MEMORY(we_sys, TWE_074_SYS);
	
	wk->seq		= 0;
	wk->step	= 0;
	wk->cnt		= 0;
	wk->wsp		= we_sys;
	wk->ssp		= WeSysSoftSpritePointerGet( wk->wsp, WeSysATNoGet(wk->wsp) );
	
	WEEffect_TCB_AddPriSet(wk->wsp, We074_TCB, wk);		
}

// -----------------------------------------
//
//
//		[ __WE_096__ ]	ヨガのポーズ
//
//
// -----------------------------------------
typedef struct {
	
	u8	seq;
	u8	cnt;
	
	s16 dy;
	s16 poke_h;

	WE_SYS_PTR		wsp;
	SOFT_SPRITE*	ssp;
	WAZATOOL_CALCMOVE cm;
	
} TWE_096_SYS;

#define WE096_CNT_MAX	(3)

#define WE096_SSX1		(100)
#define WE096_SEX1		(150)
#define WE096_SSY1		(100)
#define WE096_SEY1		(50)
#define WE096_SSX2		(WE096_SEX1)
#define WE096_SEX2		(50)
#define WE096_SSY2		(WE096_SEY1)
#define WE096_SEY2		(150)
#define WE096_SSX3		(WE096_SEX2)
#define WE096_SEX3		(100)
#define WE096_SSY3		(WE096_SEY2)
#define WE096_SEY3		(100)
#define WE096_SWAIT		(8)

static const u8 w096_step_data[][5] = {
	{ WE096_SSX1, WE096_SEX1, WE096_SSY1, WE096_SEY1, WE096_SWAIT },
	{ WE096_SSX2, WE096_SEX2, WE096_SSY2, WE096_SEY2, WE096_SWAIT },
	{ WE096_SSX3, WE096_SEX3, WE096_SSY3, WE096_SEY3, WE096_SWAIT },
};

static void We096_TCB(TCB_PTR tcb, void* work)
{
	TWE_096_SYS* wk = (TWE_096_SYS*)work;
	
	switch(wk->seq){
	case 0:
		///< 拡縮パラメーター設定
		WazaTool_InitScaleRateEx(&wk->cm,
								 w096_step_data[wk->cnt][0],
								 w096_step_data[wk->cnt][1],
								 w096_step_data[wk->cnt][2],
								 w096_step_data[wk->cnt][3], 100,
								 w096_step_data[wk->cnt][4]);
		wk->cnt++;
		wk->seq++;
		break;

	case 1:
		///< 拡縮
		if (WazaTool_CalcScaleRateEx(&wk->cm) == FALSE){
			if (wk->cnt < WE096_CNT_MAX){
				wk->seq--;
			}
			else {
				wk->seq++;
			}
		}
		SoftSpriteParaSet(wk->ssp, SS_PARA_AFF_X, wk->cm.x);
		SoftSpriteParaSet(wk->ssp, SS_PARA_AFF_Y, wk->cm.y);
		{
			s16 ofs_y = WazaTool_CalcScaleRateToYPosFX(wk->dy, wk->poke_h, wk->cm.work[4]);
			SoftSpriteParaSet(wk->ssp, SS_PARA_POS_Y, wk->dy + ofs_y);
		}
		break;

	default:
		///< 終了
		WEEffect_TCB_Delete(wk->wsp, tcb);
		sys_FreeMemoryEz(wk);		
		break;
	}
}

void WestSp_WE_096(WE_SYS_PTR we_sys)
{
	TWE_096_SYS* wk;
	
	wk = WET_ALLOC_MEMORY(we_sys, TWE_096_SYS);
	
	wk->seq		= 0;
	wk->cnt		= 0;
	wk->wsp		= we_sys;
	wk->ssp		= WeSysSoftSpritePointerGet( wk->wsp, WeSysATNoGet(wk->wsp) );
	wk->dy		= SoftSpriteParaGet(wk->ssp, SS_PARA_POS_Y);
	wk->poke_h	= WeSysPokeOfsGet(wk->wsp, WeSysATNoGet(wk->wsp));
	
	WEEffect_TCB_AddPriSet(wk->wsp, We096_TCB, wk);		
}

// -----------------------------------------
//
//
//		[ __WE_100__ ]	テレポート
//
//
// -----------------------------------------
typedef struct {
	
	u8	seq;
	u8	cnt;
	
	s16 dy;
	s16 base_y;
	s16 poke_h;

	WE_SYS_PTR		wsp;
	SOFT_SPRITE*	ssp;
	WAZATOOL_CALCMOVE cm;
	
} TWE_100_SYS;

#define WE100_CNT_MAX	(2)

#define WE100_SSX1		(100)			///< 伸びる
#define WE100_SEX1		(10)
#define WE100_SSY1		(100)
#define WE100_SEY1		(180)

#define WE100_SSX2		(WE100_SEX1)	///< 一気に縮む
#define WE100_SEX2		(10)
#define WE100_SSY2		(WE100_SEY1)
#define WE100_SEY2		(0)

#define WE100_SWAIT_1	(10)			///< wait
#define WE100_SWAIT_2	(5)

#define WE100_SXO		(0)				///< 上に浮く
#define WE100_SYO		(0)
#define WE100_SYW		(5)				///< wait

static const u8 w100_step_data[][5] = {
	{ WE100_SSX1, WE100_SEX1, WE100_SSY1, WE100_SEY1, WE100_SWAIT_1 },
	{ WE100_SSX2, WE100_SEX2, WE100_SSY2, WE100_SEY2, WE100_SWAIT_2 },
};
/*
static int DZ = -0x280;
static void AAA_AAA(TCB_PTR tcb, void* work)
{
	SOFT_SPRITE* ssp = (SOFT_SPRITE*)work;
	
	if (sys.cont & PAD_BUTTON_A){
		DZ++;
	}
	if (sys.cont & PAD_BUTTON_B){
		DZ--;
	}
	SoftSpriteParaSet(ssp, SS_PARA_POS_Z, DZ);
	OS_Printf("\n■ z = %d\n",DZ);
}
*/
static void We100_TCB(TCB_PTR tcb, void* work)
{
	TWE_100_SYS* wk = (TWE_100_SYS*)work;
	
	switch(wk->seq){
	case 0:
		///< 拡縮パラメーター設定
		WazaTool_InitScaleRateEx(&wk->cm,
								 w100_step_data[wk->cnt][0], w100_step_data[wk->cnt][1],
								 w100_step_data[wk->cnt][2], w100_step_data[wk->cnt][3], 100,
								 w100_step_data[wk->cnt][4]);
		wk->cnt++;
		wk->seq++;
		break;

	case 1:
		///< 拡縮
		if (WazaTool_CalcScaleRateEx(&wk->cm) == FALSE){
			wk->seq++;
		}
		SoftSpriteParaSet(wk->ssp, SS_PARA_AFF_X, wk->cm.x);
		SoftSpriteParaSet(wk->ssp, SS_PARA_AFF_Y, wk->cm.y);
		WazaTool_PokeOffsetSet(wk->ssp, wk->dy, wk->poke_h, wk->cm.work[4], WAZAEFF_OFS_MODE_BOTTOM);
		break;
	
	case 2:
		///< 上移動設定
		WazaTool_InitStraightSyncFx(&wk->cm,
									0, WE100_SYO,
									SoftSpriteParaGet(wk->ssp, SS_PARA_POS_Y), WE100_SYO,
									WE100_SYW);
		wk->seq++;
		break;
	
	case 3:
		///< 上移動
		if (WazaTool_CalcStraightFx(&wk->cm) == FALSE){
			wk->seq++;
		}
		SoftSpriteParaSet(wk->ssp, SS_PARA_POS_Y, wk->cm.y);
		break;
	
	case 4:
		///< 拡縮パラメーター設定
		WazaTool_InitScaleRateEx(&wk->cm,
								 w100_step_data[wk->cnt][0], w100_step_data[wk->cnt][1],
								 w100_step_data[wk->cnt][2], w100_step_data[wk->cnt][3], 100,
								 w100_step_data[wk->cnt][4]);
		wk->dy = SoftSpriteParaGet(wk->ssp, SS_PARA_POS_Y);
		wk->seq++;
		break;
	
	case 5:
		///< 拡縮
		if (WazaTool_CalcScaleRateEx(&wk->cm) == FALSE){
			wk->seq++;
		}
		SoftSpriteParaSet(wk->ssp, SS_PARA_AFF_X, wk->cm.x);
		SoftSpriteParaSet(wk->ssp, SS_PARA_AFF_Y, wk->cm.y);
		WazaTool_PokeOffsetSet(wk->ssp, wk->dy, wk->poke_h, wk->cm.work[4], WAZAEFF_OFS_MODE_TOP);
		break;

	default:
		///< 終了
		SoftSpriteParaSet(wk->ssp, SS_PARA_POS_Y, wk->base_y);
		SoftSpriteParaSet(wk->ssp, SS_PARA_VANISH, 1);
		SoftSpriteParaSet(wk->ssp, SS_PARA_AFF_X, 0x100);
		SoftSpriteParaSet(wk->ssp, SS_PARA_AFF_Y, 0x100);
		WEEffect_TCB_Delete(wk->wsp, tcb);
		sys_FreeMemoryEz(wk);		
		break;
	}
}

void WestSp_WE_100(WE_SYS_PTR we_sys)
{
	TWE_100_SYS* wk;
	
	wk = WET_ALLOC_MEMORY(we_sys, TWE_100_SYS);
	
	wk->seq		= 0;
	wk->cnt		= 0;
	wk->wsp		= we_sys;
	wk->ssp		= WeSysSoftSpritePointerGet( wk->wsp, WeSysATNoGet(wk->wsp) );
	wk->dy		= SoftSpriteParaGet(wk->ssp, SS_PARA_POS_Y);
	wk->base_y  = wk->dy;
	wk->poke_h	= WeSysPokeOfsGet(wk->wsp, WeSysATNoGet(wk->wsp));
	
	WEEffect_TCB_AddPriSet(wk->wsp, We100_TCB, wk);		
}


// -----------------------------------------
//
//
//		[ __WE_148__ ]	
//
//
// -----------------------------------------
typedef struct {
	
	u8	seq;
	u8	wait;

	PALETTE_FADE_PTR	pfd;
	WE_SYS_PTR			wsp;
	PAL_SFS_PTR			psp;
	SOFT_SPRITE*		ssp;
	
} TWE_148_SYS;

#define WE148_FADE_PAL		(0x1FF)
#define WE148_FADE_WAIT		(-2)
#define WE148_FADE_COL		(0x7FFF)
#define WE148_SS_FADE_WAIT	(0)
#define WE148_SS_FADE_COL	(0x0000)

#define WE148_WAIT		(5)


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
static void We148_TCB(TCB_PTR tcb, void* work)
{
	TWE_148_SYS* wk = (TWE_148_SYS*)work;
#if 0
	///< ソフトフェード実験
	switch(wk->seq){
	case 0:
		wk->psp = PaletteSoftFade(wk->pfd, 
								  WeSysHeapAreaGet(wk->wsp),
								  FADE_MAIN_BG, 0, 8 * 16, 0, 1, 0, 16, 0x7FFF, 0x1000);
		wk->seq++;
		break;
	
	case 1:
		if (IsPaletteSoftFade(wk->psp) == FALSE){
			PaletteSoftFadeDelete(wk->psp);
			wk->seq++;
		}
		break;
	
	case 2:
		wk->psp = PaletteSoftFade(wk->pfd, 
								  WeSysHeapAreaGet(wk->wsp),
								  FADE_MAIN_BG, 0, 8 * 16, 2, 1, 16, 0, 0x7FFF, 0x1000);
		wk->seq++;
		break;
	
	case 3:
		if (IsPaletteSoftFade(wk->psp) == FALSE){
			PaletteSoftFadeDelete(wk->psp);
			wk->seq++;
		}
		break;
		
	default:
		WEEffect_TCB_Delete(wk->wsp, tcb);
		sys_FreeMemoryEz(wk);
		break;
	}
#endif
#if 1
	switch(wk->seq){
	case 0:
		///< 背景白く
		PaletteFadeReq(wk->pfd, PF_BIT_MAIN_BG, BT_HaikeiFadeBit(wk->wsp), WE148_FADE_WAIT, 0, 16, WE148_FADE_COL);
		SoftSpritePalFadeSet(wk->ssp, 0, 16, WE148_SS_FADE_WAIT, WE148_SS_FADE_COL);
		wk->seq++;
		break;
	
	case 1:
		///< フェード待ち
		if (PaletteFadeCheck(wk->pfd) == 0
		&&	SoftSpritePalFadeExist(wk->ssp) == FALSE){
			wk->seq++;
		}		
		break;
	
	case 2:
		///< 待ち
		if ((++wk->wait) > WE148_WAIT){
			wk->seq++;
		}
		break;
	
	case 3:
		///< 復帰
		PaletteFadeReq(wk->pfd, PF_BIT_MAIN_BG, BT_HaikeiFadeBit(wk->wsp), WE148_FADE_WAIT, 16, 0, WE148_FADE_COL);
		SoftSpritePalFadeSet(wk->ssp, 16, 0, WE148_SS_FADE_WAIT, WE148_SS_FADE_COL);
		wk->seq++;
		break;
	
	case 4:
		///< フェード待ち
		if (PaletteFadeCheck(wk->pfd) == 0
		&&	SoftSpritePalFadeExist(wk->ssp) == FALSE){
			wk->seq++;
		}
		break;		

	default:
		WEEffect_TCB_Delete(wk->wsp, tcb);
		sys_FreeMemoryEz(wk);
		break;
	}
#endif
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
void WestSp_WE_148(WE_SYS_PTR we_sys)
{
	TWE_148_SYS* wk;
	
	wk = WET_ALLOC_MEMORY(we_sys, TWE_148_SYS);
	
	wk->wsp		= we_sys;
	wk->pfd		= WeSysPFDGet(wk->wsp);
	wk->ssp		= WeSysSoftSpritePointerGet(wk->wsp, WeSysATNoGet(wk->wsp));
	
	WEEffect_TCB_AddPriSet(wk->wsp, We148_TCB, wk);		
}


// -----------------------------------------
//
//
//		[ __WE_150__ ]	はねる
//
//
// -----------------------------------------
typedef struct {
	
	u8	seq;
	u8	cnt;
	u8	loop;
	
	s16 dy;
	s16 poke_h;

	WE_SYS_PTR		wsp;
	SOFT_SPRITE*	ssp;
	WAZATOOL_CALCMOVE cm;
	WAZATOOL_CALCMOVE cm_ud;
	
} TWE_150_SYS;

#define WE150_CNT_MAX	(2)

#define WE150_SSX1		(100)			///< 伸びる
#define WE150_SEX1		(120)
#define WE150_SSY1		(100)
#define WE150_SEY1		(80)
#define WE150_SSX2		(WE150_SEX1)	///< 
#define WE150_SEX2		(100)
#define WE150_SSY2		(WE150_SEY1)
#define WE150_SEY2		(120)
#define WE150_SSX3		(WE150_SEX2)	///< 
#define WE150_SEX3		(100)
#define WE150_SSY3		(WE150_SEY2)
#define WE150_SEY3		(100)

#define WE150_SWAIT_1	(5)

#define WE150_STEP_CNT	(3)
#define WE150_LOOP_CNT	(3)

static const u8 w150_step_data[][5] = {
	{ WE150_SSX1, WE150_SEX1, WE150_SSY1, WE150_SEY1, WE150_SWAIT_1 },
	{ WE150_SSX2, WE150_SEX2, WE150_SSY2, WE150_SEY2, WE150_SWAIT_1 },
	{ WE150_SSX3, WE150_SEX3, WE150_SSY3, WE150_SEY3, WE150_SWAIT_1 },
};

#define WE150_SOX1		(0)
#define WE150_SOY1		(16)
#define WE150_SOX2		(0)
#define WE150_SOY2		(0)
#define WE150_SOX3		(0)
#define WE150_SOY3		(0)
#define WE150_SOWAIT_1	(WE150_SWAIT_1)

static const u8 w150_ud_data[][3] = {
	{ 		   0, WE150_SOY1, WE150_SOWAIT_1 },
	{ WE150_SOY1, WE150_SOY2, WE150_SOWAIT_1 },
	{ WE150_SOY2, WE150_SOY3, WE150_SOWAIT_1 },
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
static void We150_TCB(TCB_PTR tcb, void* work)
{
	TWE_150_SYS* wk = (TWE_150_SYS*)work;
	
	switch(wk->seq){
	case 0:
		///< 拡縮パラメーター設定
		WazaTool_InitScaleRateEx(&wk->cm,
								 w150_step_data[wk->cnt][0], w150_step_data[wk->cnt][1],
								 w150_step_data[wk->cnt][2], w150_step_data[wk->cnt][3], 100,
								 w150_step_data[wk->cnt][4]);
		WazaTool_InitStraightSyncFx(&wk->cm_ud,
								  	0,0,
								  	wk->dy + w150_ud_data[wk->cnt][0],
								  	wk->dy + w150_ud_data[wk->cnt][1],
								  	w150_ud_data[wk->cnt][2]);								  
		wk->cnt++;
		wk->seq++;
		break;

	case 1:
		///< 拡縮
		{
			int res = 0;
			if (WazaTool_CalcScaleRateEx(&wk->cm) == FALSE){
				res++;
			}
			if (WazaTool_CalcStraightFx(&wk->cm_ud) == FALSE){
				res++;
			}
			
			if (res >= 2){
				if (wk->cnt >= WE150_STEP_CNT){
					wk->loop++;
					wk->cnt = 0;
					
					if (wk->loop >= WE150_LOOP_CNT){
						wk->seq++;
					}
				}
				else {
					wk->seq = 0;
				}
			}
			SoftSpriteParaSet(wk->ssp, SS_PARA_AFF_X, wk->cm.x);
			SoftSpriteParaSet(wk->ssp, SS_PARA_AFF_Y, wk->cm.y);
			WazaTool_PokeOffsetSet(wk->ssp, wk->cm_ud.y, wk->poke_h, wk->cm.work[4], WAZAEFF_OFS_MODE_BOTTOM);
		}
		break;

	default:
		///< 終了
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
void WestSp_WE_150(WE_SYS_PTR we_sys)
{
	TWE_150_SYS* wk;
	
	wk = WET_ALLOC_MEMORY(we_sys, TWE_150_SYS);
	
	wk->seq		= 0;
	wk->cnt		= 0;
	wk->wsp		= we_sys;
	wk->ssp		= WeSysSoftSpritePointerGet( wk->wsp, WeSysATNoGet(wk->wsp) );
	wk->dy		= SoftSpriteParaGet(wk->ssp, SS_PARA_POS_Y);
	wk->poke_h	= WeSysPokeOfsGet(wk->wsp, WeSysATNoGet(wk->wsp));
	
	WEEffect_TCB_AddPriSet(wk->wsp, We150_TCB, wk);		
}


// -----------------------------------------
//
//
//		[ __WE_106__ ]	
//
//
// -----------------------------------------
typedef struct {

	u8	seq;
	u8	wait;
	
	WE_SYS_PTR		wsp;
	
	CATS_RES_PTR	crp;
	CATS_ACT_PTR	cap;
	CATS_ACT_PTR	cap_ow;
	
} TWE_106_SYS;

#define WE106_START_WAIT	(10)
#define WE106_WIN_OUT_SIDE_PLANE	(GX_WND_PLANEMASK_BG0 | GX_WND_PLANEMASK_BG1 | \
									 GX_WND_PLANEMASK_BG2 | GX_WND_PLANEMASK_BG3 | GX_WND_PLANEMASK_OBJ)

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
static void We106_TCB(TCB_PTR tcb, void* work)
{
	TWE_106_SYS* wk = (TWE_106_SYS*)work;
	
	switch(wk->seq){
	case 0:
		///< 待ち
		if ((++wk->wait) >= WE106_START_WAIT){
			wk->wait = 0;
			wk->seq++;
		}
		break;
	
	case 1:
		///< 表示
		CATS_ObjectEnableCap(wk->cap,	 CATS_ENABLE_TRUE);
		CATS_ObjectEnableCap(wk->cap_ow, CATS_ENABLE_TRUE);
		CATS_ObjectObjModeSetCap(wk->cap_ow, GX_OAM_MODE_OBJWND);
		wk->seq++;
		break;
	
	case 2:
		///< 流れ
		if ((++wk->wait) >= WE106_START_WAIT){
			G2_SetWndOutsidePlane(WE_MASK_ALL, FALSE);
			G2_SetWndOBJInsidePlane(WE_MASK_ALL, FALSE);
			CATS_ObjectEnableCap(wk->cap,	 CATS_ENABLE_FALSE);
			CATS_ObjectEnableCap(wk->cap_ow, CATS_ENABLE_FALSE);
			wk->wait = 0;
			wk->seq++;
		}
		break;
	
	default:
		///< 終了
		GX_SetVisibleWnd(GX_WNDMASK_NONE);
		WEEffect_TCB_Delete(wk->wsp, tcb);
		sys_FreeMemoryEz(wk);		
		return;
	}

	CATS_ObjectUpdateCap(wk->cap);
	CATS_ObjectUpdateCap(wk->cap_ow);
	CATS_Draw(wk->crp);
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
void WestSp_WE_106(WE_SYS_PTR we_sys)
{
	TWE_106_SYS* wk;
	
	wk = WET_ALLOC_MEMORY(we_sys, TWE_106_SYS);
	
	wk->wsp		= we_sys;
	wk->crp		= WeSysPokeCrpGet(wk->wsp);
	wk->cap		= WeSysPokeCapGet(wk->wsp, 0);
	wk->cap_ow	= WeSysPokeCapGet(wk->wsp, 1);
	
	GX_SetVisibleWnd(GX_WNDMASK_OW);
	G2_SetWndOutsidePlane(WE106_WIN_OUT_SIDE_PLANE,	FALSE);
	G2_SetWndOBJInsidePlane(GX_WND_PLANEMASK_BG1 | GX_WND_PLANEMASK_OBJ,	FALSE);

	{
		int pal_pos;
		int index_no = WeSysPalIDGet(wk->wsp, WeSysATNoGet(wk->wsp));
		int arcID	 = WeSysArcIDGet(wk->wsp, WeSysATNoGet(wk->wsp));

		pal_pos = GetPlttProxyOffset(CLACT_PaletteProxyGet(wk->cap->act), NNS_G2D_VRAM_TYPE_2DMAIN);
		PokeColorChange(WeSysPFDGet(wk->wsp), arcID, index_no,
						WeSysHeapAreaGet(we_sys), FADE_MAIN_OBJ,
						0x20, pal_pos * 16, 256,256,256);
	}

	CATS_ObjectEnableCap(wk->cap,	 CATS_ENABLE_FALSE);
	CATS_ObjectEnableCap(wk->cap_ow, CATS_ENABLE_FALSE);
	
	WEEffect_TCB_AddPriSet(wk->wsp, We106_TCB, wk);	
}


// -----------------------------------------
//
//
//		[ __WE_107__ ]	
//
//
// -----------------------------------------
#define WE107_CAP_MAX	(3)
#define WE107_STEP		(3)

typedef struct {
	
	u8	seq;
	u8	wait;
	
	CATS_ACT_PTR cap;
	WAZATOOL_CALCMOVE cm;
	
} TWE_107_OAM;

typedef struct {
	u8	seq;
	u8	step;
	s16	dy;
	int poke_h;
	s8	flip;
	SOFT_SPRITE*	ssp;
	
	WE_SYS_PTR		wsp;
	CATS_RES_PTR	crp;

	TWE_107_OAM		oam[ WE107_CAP_MAX ];
	
} TWE_107_SYS;

static const u8 we_107_wait[] = {
	2, 7, 13, 18
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
static void We107_TCB(TCB_PTR tcb, void* work)
{
	int i;
	int ret;
	TWE_107_SYS* wk = (TWE_107_SYS*)work;
	
	switch(wk->seq){
	case 0:
		///< 
		SoftSpriteParaSet(wk->ssp, SS_PARA_VISIBLE, 1);
		wk->seq++;
		break;
	case 1:
		///< メイン
		ret = 0;
		for (i = 0; i < WE107_CAP_MAX; i++){
			switch(wk->oam[i].seq){
			case 0:
				///< 初期化
				if ((++wk->oam[i].wait) >= we_107_wait[i]){
					WazaTool_InitScaleRateEx(&wk->oam[i].cm, 100, 5, 100, 5, 100, 5);
					wk->oam[i].seq++;
				}
				break;

			case 1:
				///< 縮小
				if (WazaTool_CalcScaleRateEx(&wk->oam[i].cm) == FALSE){
					wk->oam[i].seq++;
				}
				else {
					f32 x, y;
					WazaTool_CalcScaleRateToClactScale(&wk->oam[i].cm, &x, &y);
					CATS_ObjectScaleSetCap(wk->oam[i].cap, x * wk->flip, y);					
					WazaTool_PokeOffsetSetOAM(wk->oam[i].cap,
											  wk->dy, wk->poke_h,
											  wk->oam[i].cm.work[4], WAZAEFF_OFS_MODE_BOTTOM);
				}
				break;

			default:
				ret++;
				break;
			}
			CATS_ObjectUpdateCap(wk->oam[i].cap);
		}
		if (ret >= WE107_CAP_MAX){
			wk->step++;
			if (wk->step < WE107_STEP){
				for (i = 0; i < WE107_CAP_MAX; i++){
					{
						s16 x;
						s16 y;
						CATS_ObjectPosGetCap(wk->oam[i].cap, &x, &y);
						CATS_ObjectPosSetCap(wk->oam[i].cap, x, wk->dy);
						CATS_ObjectScaleSetCap(wk->oam[i].cap, 1.0f * wk->flip, 1.0f);
					}
					wk->oam[i].seq = 0;
					wk->oam[i].wait = 0;
				}
				wk->seq--;
			}
			else {
				wk->seq++;
			}
		}
		break;
	
	case 2:
		///< 拡大初期化
		for (i = 0; i < WE107_CAP_MAX; i++){
			CATS_ObjectObjModeSetCap(wk->oam[i].cap, GX_OAM_MODE_NORMAL);
			WazaTool_InitScaleRateEx(&wk->oam[i].cm, 5, 100, 5, 100, 100, 5);
		}
		wk->seq++;
		break;
	
	case 3:
		///< 拡大
		ret = 0;
		for (i = 0; i < WE107_CAP_MAX; i++){
			if (WazaTool_CalcScaleRateEx(&wk->oam[i].cm) == FALSE){
				ret++;
			}
			else {
				f32 x, y;
				WazaTool_CalcScaleRateToClactScale(&wk->oam[i].cm, &x, &y);
				CATS_ObjectScaleSetCap(wk->oam[i].cap, x * wk->flip, y);					
				WazaTool_PokeOffsetSetOAM(wk->oam[i].cap,
										  wk->dy, wk->poke_h,
										  wk->oam[i].cm.work[4], WAZAEFF_OFS_MODE_BOTTOM);
			}
		}
		if (ret >= WE107_CAP_MAX){
			wk->seq++;
		}
		break;
	
	default:
		///< 終了
		SoftSpriteParaSet(wk->ssp, SS_PARA_VISIBLE, 0);
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
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WestSp_WE_107(WE_SYS_PTR we_sys)
{
	TWE_107_SYS* wk;
	
	wk = WET_ALLOC_MEMORY(we_sys, TWE_107_SYS);
	
	wk->seq		= 0;
	wk->step	= 0;
	wk->wsp		= we_sys;
	wk->crp		= WeSysPokeCrpGet(wk->wsp);

	wk->ssp		= WeSysSoftSpritePointerGet(wk->wsp, WeSysATNoGet(wk->wsp));
	wk->dy		= SoftSpriteParaGet(wk->ssp, SS_PARA_POS_Y);
	wk->dy		-= SoftSpriteParaGet(wk->ssp, SS_PARA_SHADOW_HEIGHT);
	wk->poke_h	= WeSysPokeOfsGet(wk->wsp, WeSysATNoGet(wk->wsp));
	
	WET_DefaultBlendSet(wk->wsp, WET_DEFAULT_BLEND, WET_DEFAULT_BLEND);
	G2_ChangeBlendAlpha(12,6);

	{
		int i;
		
		for (i = 0; i < WE107_CAP_MAX; i++){
			wk->oam[i].seq	= 0;
			wk->oam[i].wait = 0;
			wk->oam[i].cap	= WeSysPokeCapGet(wk->wsp, i);
			CATS_ObjectAffineSetCap(wk->oam[i].cap, CLACT_AFFINE_DOUBLE);
			CATS_ObjectObjModeSetCap(wk->oam[i].cap, GX_OAM_MODE_XLU);
			CATS_ObjectPriSetCap(wk->oam[i].cap, i + 1);
		}
	}
	
	if (ContestFlipCheck(we_sys, WEDEF_DROP_M1) == TRUE){
		wk->flip = -1;
	}
	else {
		wk->flip = +1;
	}
	
	{
		int i;
		for (i = 0; i < WE107_CAP_MAX; i++){
			CATS_ObjectScaleSetCap(wk->oam[i].cap, 1.0f * wk->flip, 1.0f);
		}
	}
	
	WEEffect_TCB_AddPriSet(wk->wsp, We107_TCB, wk);
}


// -----------------------------------------
//
//
//		[ __WE_089__ ]	
//
//
// -----------------------------------------
typedef struct {
	SOFT_SPRITE* ssp;
	CATS_ACT_PTR cap;
	s16	def_x;	
	s16	def_y;	
} TWE_089_POKE;

typedef struct {
	u8	seq;
	u8	step;
	u8	fade;
	u8	wait;
	
	int num;

//	TWE_089_POKE	poke[4];
	GF_BGL_INI*		bgl;
	
	WE_SYS_PTR		wsp;
	CATS_RES_PTR	crp;
	
	TWE_POKE_SYS	poke[ WE_POKE_DATA_MAX ];
	TWE_POKE_SYS	poke2[ WE_POKE_DATA_MAX ];
	
	WAZATOOL_CALCMOVE shake;
	
} TWE_089_SYS;

static const s16 we089_shake[] = { 12, 10, 8, 6, 4, 2, 1, 0 };

#define WE089_STEP_NUM	(NELEMS(we089_shake))
#define WE089_COL_BLACK	(WEDEF_COLOR_BLACK)
#define WE089_COL_WHITE	(WEDEF_COLOR_WHITE)


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
static void We089_TCB(TCB_PTR tcb, void* work)
{
	int i;
	TWE_089_SYS* wk = (TWE_089_SYS*)work;
	
	switch(wk->seq){
	case 0:			
		PaletteFadeReq(WeSysPFDGet(wk->wsp), PF_BIT_MAIN_BG, BT_HaikeiFadeBit(wk->wsp), 1, 0, 10, WEDEF_COLOR_BLACK);
		wk->seq++;
		break;
		
	case 1:
		if (PaletteFadeCheck(WeSysPFDGet(wk->wsp)) != 0){ break; }
		wk->seq++;
		
	case 2:
		///< ゆれ幅初期化
		WazaTool_InitShake(&wk->shake, we089_shake[wk->step], 0, 0, 5);
		
		if (wk->fade == 0){
			ColorConceChangePfd(WeSysPFDGet(wk->wsp), FADE_MAIN_BG, WEDEF_BACKGROUND_PAL, 10, WEDEF_COLOR_BLACK);
		}
		else {
			ColorConceChangePfd(WeSysPFDGet(wk->wsp), FADE_MAIN_BG, WEDEF_BACKGROUND_PAL, 10, WEDEF_COLOR_WHITE);
		}
		wk->wait = 3;
		wk->fade ^= 1;
		wk->step++;
		wk->seq++;

	case 3:
		///< ゆれ
		if (WazaTool_CalcShake(&wk->shake) == FALSE){
			if (wk->step >= WE089_STEP_NUM){
				wk->seq++;
			}
			else {
				wk->seq--;
			}
		}
		if (wk->wait > 0){
			wk->wait--;
			if (wk->wait == 0){
				ColorConceChangePfd(WeSysPFDGet(wk->wsp), FADE_MAIN_BG, WEDEF_BACKGROUND_PAL, 0, 0);
			}
		}
		for (i = 0; i < 4; i++){
			if (wk->poke[i].ssp == NULL){ continue; }

			SoftSpriteParaSet(wk->poke[i].ssp, SS_PARA_POS_X, wk->poke[i].base_p.x + wk->shake.x);
		//	CATS_ObjectPosSetCap(wk->poke2[i].cap, wk->poke[i].base_p.x - wk->shake.x, wk->poke[i].base_p.y);
		//	CATS_ObjectUpdateCap(wk->poke2[i].cap);
		}
	//	CATS_Draw(wk->crp);
		GF_BGL_ScrollSet(wk->bgl, BATTLE_FRAME_BACKGROUND, GF_BGL_SCROLL_X_SET, wk->shake.x);
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
void WestSp_WE_089(WE_SYS_PTR we_sys)
{
	int i;
	TWE_089_SYS* wk;
	
	wk = WET_ALLOC_MEMORY(we_sys, TWE_089_SYS);

	wk->seq		= 0;
	wk->step	= 0;
	wk->wsp		= we_sys;
	wk->crp		= WeSysPokeCrpGet(wk->wsp);
	wk->bgl		= WeSysBGLPointerGet(wk->wsp);

	{
		int mode1;
		int mode2;
		
		if (IsWeSysBattleMode2vs2(wk->wsp) == TRUE){
			mode1 = WE_TOOL_STAGE;//(WE_TOOL_M1 | WE_TOOL_M2 | WE_TOOL_E1 | WE_TOOL_E2);
			mode2 = (WE_TOOL_C0 | WE_TOOL_C1 | WE_TOOL_C2 | WE_TOOL_C3);
		}
		else {
			mode1 = (WE_TOOL_M1 | WE_TOOL_E1);
			mode2 = (WE_TOOL_C0 | WE_TOOL_C1);
		}
		
		WT_SSPointerGet(we_sys, mode1, &(wk->poke[0]), &wk->num);
	//	WT_CAPointerGet(we_sys, mode2, &(wk->poke2[0]), &wk->num);
	}
	for (i = 0; i < wk->num; i++){
		wk->poke[i].base_p.x = SoftSpriteParaGet(wk->poke[i].ssp, SS_PARA_POS_X);
		wk->poke[i].base_p.y = SoftSpriteParaGet(wk->poke[i].ssp, SS_PARA_POS_Y);
	//	CATS_ObjectEnableCap(wk->poke2[i].cap, CATS_ENABLE_FALSE);
	}
/*
	for (i = 0; i < 4; i++){
		wk->poke[i].ssp	= WeSysSoftSpritePointerGet(wk->wsp, i);
		wk->poke[i].cap	= WeSysPokeCapGet(wk->wsp, i);
		CATS_ObjectEnableCap(wk->poke[i].cap, CATS_ENABLE_FALSE);
		
		if (wk->poke[i].ssp == NULL){ continue; }

		CATS_ObjectEnableCap(wk->poke[i].cap, CATS_ENABLE_TRUE);
		wk->poke[i].def_x = SoftSpriteParaGet(wk->poke[i].ssp, SS_PARA_POS_X);
		wk->poke[i].def_y = SoftSpriteParaGet(wk->poke[i].ssp, SS_PARA_POS_Y);
		OS_Printf("pos = %d, %d\n",wk->poke[i].def_x,wk->poke[i].def_y);
	}
*/
	WEEffect_TCB_AddPriSet(wk->wsp, We089_TCB, wk);
}


// -----------------------------------------
//
//
//		[ __WE_171__ ]	
//
//
// -----------------------------------------
typedef struct {
	u8	seq;
	u8	step;
	u8	fade;
	u8	wait;
	
	WT_POINT		pos;

	GF_BGL_INI*		bgl;
	
	WE_SYS_PTR		wsp;
	CATS_RES_PTR	crp;
	SOFT_SPRITE*	ssp;
	CATS_ACT_PTR	cap;
	
	WAZATOOL_CALCMOVE shake;
	WAZATOOL_CALCMOVE cm;
	
	WAZATOOL_ALPHA_FADE af;
	
} TWE_171_SYS;


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
static void We171_TCB(TCB_PTR tcb, void* work)
{
	TWE_171_SYS* wk = (TWE_171_SYS*)work;
	
	switch(wk->seq){
	case 0:
		///< 実行
		if (WazaTool_CalcStraightFx(&wk->cm) == FALSE){
			wk->seq++;
		}
		WazaTool_CalcShake(&wk->shake);
		WazaTool_EndCheckAlphaFade(&wk->af);
		
	//	SoftSpriteParaSet(wk->ssp, SS_PARA_POS_X, wk->pos.x + wk->shake.x);
		CATS_ObjectPosSetCap(wk->cap, wk->cm.x, wk->cm.y);
		CATS_ObjectUpdateCap(wk->cap);
		CATS_Draw(wk->crp);
		break;
		
	default:
		///< 終了処理
		WEEffect_TCB_Delete(wk->wsp, tcb);
		sys_FreeMemoryEz(wk);
		break;
	}
}

#define WE171_OFS_X		(-20)
#define WE171_OFS_Y		(+20)
#define WE171_SYNC		(20)
#define WE171_FADE_SYNC	(WE171_SYNC - 5)
void WestSp_WE_171(WE_SYS_PTR we_sys)
{
	TWE_171_SYS* wk;
	
	int client_no;
	
	wk = WET_ALLOC_MEMORY(we_sys, TWE_171_SYS);	

	wk->seq		= 0;
	wk->step	= 0;
	wk->wsp		= we_sys;
	wk->crp		= WeSysPokeCrpGet(wk->wsp);
	wk->bgl		= WeSysBGLPointerGet(wk->wsp);
	wk->cap		= WeSysPokeCapGet(wk->wsp, 0);

	if (WeSysGPWorkGet(we_sys, 0) == 0){
		client_no = WeSysDFNoGet(wk->wsp);
	}
	else {
		client_no = WeSysATNoGet(wk->wsp);
	}
	
	wk->ssp		= WeSysSoftSpritePointerGet(wk->wsp, client_no);

	WT_SSP_PointGet(wk->ssp, &wk->pos);
	wk->pos.y -= SoftSpriteParaGet(wk->ssp, SS_PARA_SHADOW_HEIGHT);
	
	{
		int vecx = WazaTool_VecChangeX( wk->wsp, client_no );
		int vecy = WazaTool_VecChangeY( wk->wsp, client_no );
		
		WazaTool_InitStraightSyncFx(&wk->cm,
									wk->pos.x, wk->pos.x + (WE171_OFS_X * vecx),
									wk->pos.y, wk->pos.y + (WE171_OFS_Y * vecy),
									WE171_SYNC);
	//	WazaTool_InitShake(&wk->shake, 2, 0, 0, WE171_SYNC);		
	}
	
	WET_BGSelectBlendSet(wk->wsp, 
						( 1 << BT_BGL_BGNoGet(we_sys, WES_BF_BACKGROUND) ) | GX_BLEND_PLANEMASK_BD |
						( 1 << BT_BGL_BGNoGet(we_sys, WES_BF_EFFECT) ) | GX_WND_PLANEMASK_BG0,
						WET_DEFAULT_BLEND, WET_DEFAULT_BLEND);
	WazaTool_StartAlphaFade(&wk->af, 31, 0, 0, 31, WE171_FADE_SYNC);
	
	CATS_ObjectObjModeSetCap(wk->cap, GX_OAM_MODE_XLU);
	
	WEEffect_TCB_AddPriSet(wk->wsp, We171_TCB, wk);
}


// -----------------------------------------
//
//
//		[ __WE_175__ ]	
//
//
// -----------------------------------------
typedef struct {
	
	TWE_TOOL_SYS			ts;
	TWE_SHAKE_TOOL			st;
	
	SOFT_SPRITE*			ssp[2];
	
	s16						shake_x;
	s16						shake_y;
	s16						shake_wait;
	s16						shake_num;
	
	WAZATOOL_CALCMOVE		shake;
	WAZATOOL_CALCMOVE_ONE	cm;
	
} TWE_175_SYS;

#define WE175_STEP_NUM	(5)
#define WE175_RAD_CY	(100)

static const int we175_rad[][2] = {
	{ FX_GET_ROTA_NUM(20),  3 },
	{ FX_GET_ROTA_NUM(15),  3 },
	{ FX_GET_ROTA_NUM(10),  2 },
	{ FX_GET_ROTA_NUM(5),   2 },
	{ FX_GET_ROTA_NUM(0),   1 },
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
static void We175_1_TCB(TCB_PTR tcb, void* work)
{
	TWE_175_SYS* wk = (TWE_175_SYS*)work;
	
	switch(wk->ts.seq){
	case 0:
		///< 回転初期化
		{
			int sr;
			int er;
			if (wk->ts.cnt == 0){
				sr = -we175_rad[ wk->ts.step ][ 0 ];
				er = +we175_rad[ wk->ts.step ][ 0 ];
			}
			else {
				sr = +we175_rad[ wk->ts.step ][ 0 ];
				er = -we175_rad[ wk->ts.step ][ 0 ];
			}
			WazaTool_InitMoveOneSync(&wk->cm, sr, er,
									 we175_rad[ wk->ts.step ][ 1 ]);
			if (wk->ts.cnt == 1){
				wk->ts.step++;
			}
			wk->ts.cnt ^= 1;
		}
		wk->ts.seq++;
		
	case 1:
		///< 回転
		if (WazaTool_CalcMoveOne(&wk->cm) == TRUE){
			SoftSpriteParaSet(wk->ssp[0], SS_PARA_ROT_Z, (u16)wk->cm.num);
		}
		else {
			if (wk->ts.step >= WE175_STEP_NUM){
				wk->ts.seq++;
			}
			else {
				wk->ts.seq--;
			}
		}
		break;
		
	default:
		///< 終了
		SoftSpriteParaSet(wk->ssp[0], SS_PARA_ROT_Z, 0);
		
		WEEffect_TCB_Delete(wk->ts.wsp, tcb);
		sys_FreeMemoryEz(wk);
		break;
	}
}

static void We175_2_TCB(TCB_PTR tcb, void* work)
{
	TWE_175_SYS* wk = (TWE_175_SYS*)work;
	
	switch(wk->ts.seq){
	case 0:
		///< ブレ初期化
		WazaTool_InitShake(&wk->shake, wk->st.x, wk->st.y, wk->st.w, wk->st.n);
		wk->ts.seq++;
		break;
	
	case 1:
		///< ブレ
		{
			WT_POINT p;
			
			WT_SSP_PointGet(wk->ssp[1], &p);
			
			if (WazaTool_CalcAndReflectShakeSsp(&wk->shake, p.x, p.y, wk->ssp[1]) == FALSE){
				wk->ts.seq++;
			}
		}
		break;
		
	default:
		///< 終了
		WEEffect_TCB_Delete(wk->ts.wsp, tcb);
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
void WestSp_WE_175(WE_SYS_PTR we_sys)
{
	TWE_175_SYS* wk;
	int sep = 0;
	
	wk = WET_ALLOC_MEMORY(we_sys, TWE_175_SYS);
	
	WT_ToolSysInit(we_sys, &wk->ts);
	
	wk->ssp[0] = WeSysSoftSpritePointerGet(wk->ts.wsp, WeSysATNoGet(wk->ts.wsp));
	wk->ssp[1] = WeSysSoftSpritePointerGet(wk->ts.wsp, WeSysDFNoGet(wk->ts.wsp));

	SoftSpriteParaSet(wk->ssp[0], SS_PARA_ROT_CY, WE175_RAD_CY);
	
	sep = WeSysGPWorkGet(we_sys, 0);
	
	wk->st.x = WeSysGPWorkGet(we_sys, 1);
	wk->st.y = WeSysGPWorkGet(we_sys, 2);
	wk->st.w = WeSysGPWorkGet(we_sys, 3);
	wk->st.n = WeSysGPWorkGet(we_sys, 4);
	wk->st.mode = WeSysGPWorkGet(we_sys, 5);
	
	if (sep == 0){
		WEEffect_TCB_AddPriSet(wk->ts.wsp, We175_1_TCB, wk);
	}
	else {
		WEEffect_TCB_AddPriSet(wk->ts.wsp, We175_2_TCB, wk);
	}
}



// -----------------------------------------
//
//
//		[ __WE_222__ ]	
//
//
// -----------------------------------------
typedef struct {	

	TWE_TOOL_SYS		ts;
	TWE_SHAKE_TOOL		st;

	WT_POINT			p[4];
	SOFT_SPRITE*		ssp[4];
	
	int					pow;

	WAZATOOL_CALCMOVE	cm;
	
} TWE_222_SYS;


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
static void We222_TCB(TCB_PTR tcb, void* work)
{
	int i;
	TWE_222_SYS* wk = (TWE_222_SYS*)work;
	
	switch(wk->ts.seq){
	case 0:
		///< ゆれ幅指定
		WazaTool_InitShake(&wk->cm, 2 + wk->pow, wk->pow, 0, 10);
		wk->ts.seq++;
		break;
		
	case 1:
		///< ゆれ
		if (WazaTool_CalcShake(&wk->cm) == FALSE){
			wk->ts.seq++;
		}
		else {
			for (i = 0; i < 4; i++){
				if (wk->ssp[i] == NULL){ continue; }
				
				SoftSpriteParaSet(wk->ssp[i], SS_PARA_POS_X, wk->p[i].x + wk->cm.x);
			}
			GF_BGL_ScrollSet(wk->ts.bgl, BATTLE_FRAME_BACKGROUND, GF_BGL_SCROLL_X_SET, wk->cm.x);
			GF_BGL_ScrollSet(wk->ts.bgl, BATTLE_FRAME_BACKGROUND, GF_BGL_SCROLL_Y_SET, wk->cm.y);
		}
		break;
		
	default:
		WEEffect_TCB_Delete(wk->ts.wsp, tcb);
		sys_FreeMemoryEz(wk);
		break;
	}
}

void WestSp_WE_222(WE_SYS_PTR we_sys)
{
	TWE_222_SYS* wk = WET_ALLOC_MEMORY(we_sys, TWE_222_SYS);
	
	int i;

	WT_ToolSysInit(we_sys, &wk->ts);
	
	{
		int p = WazaEffParaGet(wk->ts.wsp, WE_PARA_POW);
		
		switch(p){
		case 150:
			wk->pow = 6;
			break;
		case 110:
			wk->pow = 5;
			break;
		case 90:
			wk->pow = 4;
			break;
		case 70:
			wk->pow = 3;
			break;
		case 50:
			wk->pow = 2;
			break;
		case 30:
			wk->pow = 1;
			break;
		default:
			wk->pow = 0;
			break;
		};
	}

	for (i = 0; i < 4; i++){
		wk->ssp[i]	= WeSysSoftSpritePointerGet(wk->ts.wsp, i);
		
		if (wk->ssp[i] == NULL){ continue; }
		
		WT_SSP_PointGet(wk->ssp[i], &wk->p[i]);
	}

	WEEffect_TCB_AddPriSet(wk->ts.wsp, We222_TCB, wk);
}


// -----------------------------------------
//
//
//		[ __WE_316__ ]	
//
//
// -----------------------------------------
typedef struct {	

	TWE_TOOL_SYS		ts;
	TWE_SHAKE_TOOL		st;

	WT_POINT			p[2];
	SOFT_SPRITE*		ssp[2];
	
	CATS_ACT_PTR		cap[2];

	WAZATOOL_CALCMOVE	cm[2];
	
} TWE_316_SYS;


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
static void We316_TCB(TCB_PTR tcb, void* work)
{
	int i;
	TWE_316_SYS* wk = (TWE_316_SYS*)work;
	
	switch(wk->ts.seq){
	case 0:
		///< ゆれ幅指定
		WazaTool_InitShake(&wk->cm[0], 20, 0, 0, 10);
		WazaTool_InitShake(&wk->cm[1], 2, 0, 0, 10);
		wk->ts.seq++;
		break;
		
	case 1:
		///< ゆれ
		if (WazaTool_CalcShake(&wk->cm[0]) == FALSE){
			wk->ts.seq++;
		}
		else {
			CATS_ObjectPosSetCap(wk->cap[0], +wk->p[1].x + wk->cm[0].x, wk->p[1].y + wk->cm[0].y);
			CATS_ObjectPosSetCap(wk->cap[1], -wk->p[1].x + wk->cm[0].x, wk->p[1].y + wk->cm[0].y);
			CATS_ObjectUpdateCap(wk->cap[0]);
			CATS_ObjectUpdateCap(wk->cap[1]);
		}
		

		CATS_Draw(wk->ts.poke_crp);
		break;
		
	default:
		WEEffect_TCB_Delete(wk->ts.wsp, tcb);
		sys_FreeMemoryEz(wk);
		break;
	}
}

void WestSp_WE_316(WE_SYS_PTR we_sys)
{
	TWE_316_SYS* wk = WET_ALLOC_MEMORY(we_sys, TWE_316_SYS);
	
	int i;

	WT_ToolSysInit(we_sys, &wk->ts);
	
	wk->cap[0] = WeSysPokeCapGet(wk->ts.wsp, 0);
	wk->cap[1] = WeSysPokeCapGet(wk->ts.wsp, 1);
	
	wk->ssp[0] = WeSysSoftSpritePointerGet(wk->ts.wsp, WeSysATNoGet(wk->ts.wsp));
	wk->ssp[1] = WeSysSoftSpritePointerGet(wk->ts.wsp, WeSysDFNoGet(wk->ts.wsp));
	WT_SSP_PointGet(wk->ssp[0], &wk->p[0]);
	WT_SSP_PointGet(wk->ssp[1], &wk->p[1]);

	WEEffect_TCB_AddPriSet(wk->ts.wsp, We316_TCB, wk);
}



// -----------------------------------------
//
//
//		[ __WE_333__ ]	つららばり
//
//
// -----------------------------------------

// -----------------------------------------
//
//	構造体
//
// -----------------------------------------
typedef struct {
	
	int num;
	int time;
	int height;
	WT_POINT			ofs;

	TWE_TOOL_SYS		ts;
	TWE_SHAKE_TOOL		st;
	
	CATS_ACT_PTR		cap;
	
	TWE_POKE_SYS		poke[ WE_POKE_DATA_MAX ];

	WAZATOOL_CALCMOVE	cm[2];
	WAZATOOL_CALCMOVE_ONE	rd;
	
} TWE_333_SYS;

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
static void We333_TCB(TCB_PTR tcb, void* work)
{
	int i;
	TWE_333_SYS* wk = (TWE_333_SYS*)work;
	
	if (WazaTool_CalcAndReflectCurveFxCap(&wk->cm[0], &wk->cm[1], wk->cap) == FALSE){
		CATS_ActorPointerDelete_S(wk->cap);
		WEEffect_TCB_Delete(wk->ts.wsp, tcb);
		WET_SAFE_RELEASE(wk);
		return;
	}
	
	if (WazaTool_CalcMoveOne(&wk->rd) == TRUE){
		CATS_ObjectRotationSetCap(wk->cap, wk->rd.num);
	}
	CATS_ObjectUpdateCap(wk->cap);
	CATS_Draw(wk->ts.oam_crp);
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
void WestSp_CAT_WE_333(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap)
{
	int i;
	int r_vec;
	TWE_333_SYS* wk;
	
	wk = WET_ALLOC_MEMORY(we_sys, TWE_333_SYS);

	WT_ToolSysInit(we_sys, &wk->ts);
	
	wk->ofs.x	= WeSysGPWorkGet(we_sys, 0);
	wk->ofs.y	= WeSysGPWorkGet(we_sys, 1);
	wk->time	= WeSysGPWorkGet(we_sys, 2);
	wk->height	= WeSysGPWorkGet(we_sys, 3);
	
	r_vec = WazaTool_VecChangeX(we_sys, WeSysATNoGet(we_sys));

	wk->cap		= cap;
	
	CATS_ObjectAffineSetCap(wk->cap, CLACT_AFFINE_DOUBLE);
	
	wk->poke[ 0 ].ssp = WeSysSoftSpritePointerGet(we_sys, WeSysATNoGet(we_sys));
	wk->poke[ 1 ].ssp = WeSysSoftSpritePointerGet(we_sys, WeSysDFNoGet(we_sys));
	WT_SSP_PointGet(wk->poke[ 0 ].ssp, &wk->poke[ 0 ].p);
	WT_SSP_PointGet(wk->poke[ 1 ].ssp, &wk->poke[ 1 ].p);
	
	WazaTool_InitCurveYFx(&wk->cm[0],
						  &wk->cm[1], 
						  wk->poke[ 0 ].p.x,
						  wk->poke[ 1 ].p.x + (wk->ofs.x * r_vec),
						  wk->poke[ 0 ].p.y,
						  wk->poke[ 1 ].p.y + (wk->ofs.y * r_vec),
						  wk->time, wk->height * FX32_ONE);

	if (WeSysClientTypeGet(we_sys, WeSysATNoGet(we_sys)) == CLIENT_TYPE_C
	&&	WeSysClientTypeGet(we_sys, WeSysDFNoGet(we_sys)) == CLIENT_TYPE_A){
		r_vec *= -1;
	}
	
	if (WeSysClientTypeGet(we_sys, WeSysATNoGet(we_sys)) == CLIENT_TYPE_D
	&&	WeSysClientTypeGet(we_sys, WeSysDFNoGet(we_sys)) == CLIENT_TYPE_B){
		r_vec *= -1;
	}
	
	///< 1度実行
	if (r_vec > 0){
		WazaTool_InitMoveOneSync(&wk->rd, FX_GET_ROTA_NUM(20) * r_vec, FX_GET_ROTA_NUM(130) * r_vec, 10);
	}
	else {
		WazaTool_InitMoveOneSync(&wk->rd, FX_GET_ROTA_NUM(90) * r_vec, FX_GET_ROTA_NUM(130) * r_vec, 10);
	}
	
	CATS_ObjectRotationSetCap(wk->cap, wk->rd.num);
	WazaTool_CalcAndReflectCurveFxCap(&wk->cm[0], &wk->cm[1], wk->cap);
	CATS_ObjectUpdateCap(wk->cap);

	WEEffect_TCB_AddPriSet(wk->ts.wsp, We333_TCB, wk);
}

// -----------------------------------------
//
//
//		[ __WE_057__ ]	なみのり
//
//
// -----------------------------------------
typedef struct {
	
	int num;
	int time;
	int height;
	u8	eva;
	u8	evb;
	
	u8	eva_s;
	u8	evb_s;
	u8	eva_m;
	u8	evb_m;
	s16 scale;
	WT_POINT			def;

	TWE_TOOL_SYS		ts;
	TWE_SHAKE_TOOL		st;
	
	CATS_ACT_PTR		cap;
	CATS_ACT_PTR		cap_temp[2];
	
	TWE_POKE_SYS		poke[ WE_POKE_DATA_MAX ];

	WAZATOOL_CALCMOVE		cm;
	WAZATOOL_CALCMOVE_ONE	rd;
	
} TWE_057_SYS;

#define WE057_OAM_HEIGHT	(16)
#define WE057_EVA			(0)
#define WE057_EVB			(31)
#define WE057_EVAM			(31)
#define WE057_EVBM			(4)
#define WE057_WAIT			(4)

static void We057_TCB(TCB_PTR tcb, void* work)
{
	TWE_057_SYS* wk = (TWE_057_SYS*)work;
	
	switch(wk->ts.seq){
	case 0:
		WazaTool_InitScaleRateEx(&wk->cm, 100 * wk->scale, 60 * wk->scale, 5, 150, 100, 12);
		wk->ts.seq++;
		break;
	case 1:
		if (WazaTool_CalcScaleRateEx(&wk->cm) == FALSE){
			WazaTool_InitScaleRateEx(&wk->cm, 60 * wk->scale, 150 * wk->scale, 150, 10, 100, 12);
			wk->ts.seq++;
		}
		else {		
			f32 x, y;
			s16 ypos;
			WazaTool_CalcScaleRateToClactScale(&wk->cm, &x, &y);
			CATS_ObjectScaleSetCap(wk->cap, x, y);
			ypos = WazaTool_CalcScaleRateToYPosFX(wk->def.y, WE057_OAM_HEIGHT, wk->cm.work[4]);
			CATS_ObjectPosSetCap(wk->cap, wk->def.x, wk->def.y + ypos);
			
			if (wk->eva < wk->eva_m){ wk->eva++; }
			if (wk->evb > wk->evb_m){ wk->evb--; }
			G2_ChangeBlendAlpha(wk->eva, wk->evb);
		}
		break;
	case 2:
		if (++wk->time >= WE057_WAIT){
			wk->ts.seq++;
		}
		break;
	case 3:
		if (WazaTool_CalcScaleRateEx(&wk->cm) == FALSE){
			wk->ts.seq++;
		}
		else {		
			f32 x, y;
			s16 ypos;
			WazaTool_CalcScaleRateToClactScale(&wk->cm, &x, &y);
			CATS_ObjectScaleSetCap(wk->cap, x, y);
			ypos = WazaTool_CalcScaleRateToYPosFX(wk->def.y, WE057_OAM_HEIGHT, wk->cm.work[4]);
			CATS_ObjectPosSetCap(wk->cap, wk->def.x, wk->def.y + ypos);
			
			if (wk->eva > wk->eva_s){ wk->eva--; }
			if (wk->evb < wk->evb_s){ wk->evb++; }
			G2_ChangeBlendAlpha(wk->eva, wk->evb);
		}
		break;

	default:
		CATS_ActorPointerDelete_S(wk->cap_temp[0]);
		CATS_ActorPointerDelete_S(wk->cap_temp[1]);
		WEEffect_TCB_Delete(wk->ts.wsp, tcb);
		WET_SAFE_RELEASE(wk);
		return;
	}
	
	CATS_ObjectUpdateCap(wk->cap);
	CATS_Draw(wk->ts.oam_crp);
}

void WestSp_WE_057(WE_SYS_PTR we_sys)
{
	TWE_057_SYS* wk = WET_ALLOC_MEMORY(we_sys, TWE_057_SYS);

	WT_ToolSysInit(we_sys, &wk->ts);
	
	wk->cap_temp[0] = WeSysOamCapGet(we_sys, 0);
	wk->cap_temp[1] = WeSysOamCapGet(we_sys, 1);
	
	WET_DefaultBlendSet(wk->ts.wsp, WET_DEFAULT_BLEND, WET_DEFAULT_BLEND);

	if (WeSysGPWorkGet(we_sys, 0) == 0){
		wk->eva = WE057_EVA;
		wk->evb = WE057_EVB;
		wk->eva_s = WE057_EVA;
		wk->evb_s = WE057_EVB;
		wk->eva_m = WE057_EVAM;
		wk->evb_m = WE057_EVBM;
	}
	else {
		wk->eva = WE057_EVA;
		wk->evb = WE057_EVB;
		wk->eva_s = WE057_EVA;
		wk->evb_s = WE057_EVB;
		wk->eva_m = WE057_EVAM;
		wk->evb_m = WE057_EVBM;
	}
	
	
	if (WES_ContestFlag_Get(we_sys) == TRUE){
		wk->cap = wk->cap_temp[0];
		CATS_ObjectEnableCap(wk->cap_temp[1], CATS_ENABLE_FALSE);
		CATS_ObjectAnimeSeqSetCap(wk->cap, 0);
		wk->def.x = 255 - 76;
		wk->def.y = 120;
		CATS_ObjectBGPriSetCap(wk->cap, BT_3DPriorityGet(we_sys) + 1);	
		wk->scale = -1;
	}
	else {
		if (WET_SideCheck(we_sys, WeSysATNoGet(we_sys)) == SIDE_ENEMY){
			wk->cap = wk->cap_temp[1];
			CATS_ObjectEnableCap(wk->cap_temp[0], CATS_ENABLE_FALSE);
			CATS_ObjectAnimeSeqSetCap(wk->cap, 1);
			wk->def.x = 144;
			wk->def.y = 64;
		}
		else {
			wk->cap = wk->cap_temp[0];
			CATS_ObjectEnableCap(wk->cap_temp[1], CATS_ENABLE_FALSE);
			CATS_ObjectAnimeSeqSetCap(wk->cap, 0);
			wk->def.x = 76;
			wk->def.y = 120;
			CATS_ObjectBGPriSetCap(wk->cap, BT_3DPriorityGet(we_sys) + 1);
		}
		wk->scale = +1;
	}
	CATS_ObjectPosSetCap(wk->cap, wk->def.x, wk->def.y);
	CATS_ObjectAffineSetCap(wk->cap, CLACT_AFFINE_DOUBLE);
	CATS_ObjectObjModeSetCap(wk->cap, GX_OAM_MODE_XLU);

	{
		f32 x, y;
		s16 ypos;
		WazaTool_InitScaleRateEx(&wk->cm, 100 * wk->scale, 100 * wk->scale, 100, 5, 100, 1);
		WazaTool_CalcScaleRateEx(&wk->cm);
	
		WazaTool_CalcScaleRateToClactScale(&wk->cm, &x, &y);
		CATS_ObjectScaleSetCap(wk->cap, x, y);
		ypos = WazaTool_CalcScaleRateToYPosFX(wk->def.y, WE057_OAM_HEIGHT, wk->cm.work[4]);
		CATS_ObjectPosSetCap(wk->cap, wk->def.x, wk->def.y + ypos);
	}
	
	WEEffect_TCB_AddPriSet(wk->ts.wsp, We057_TCB, wk);
}

/// 253
typedef struct {

	int num;
	int cnt;
	int	wait;
	
	s16	ofs_x;		///< 移動幅
	
	TWE_POKE_SYS	pp;

	TWE_TOOL_SYS	ts;
	
	WAZATOOL_CALCMOVE cm;
	
	WE_SYS_PTR		wsp;
	
} TWE_253_SYS;

static void We253_TCB(TCB_PTR tcb, void* work)
{
	TWE_253_SYS* wk = (TWE_253_SYS*)work;
	
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

void WestSp_WE_253(WE_SYS_PTR we_sys)
{
	int r_vec;
	TWE_253_SYS* wk = WET_ALLOC_MEMORY(we_sys, TWE_253_SYS);

	wk->wsp   = we_sys;
	wk->wait  = WeSysGPWorkGet(we_sys, 0);
	wk->ofs_x = WeSysGPWorkGet(we_sys, 1);

	WT_ToolSysInit(we_sys, &wk->ts);
	
	wk->pp.ssp = WeSysSoftSpritePointerGet(we_sys, WeSysDFNoGet(we_sys));
	WT_SSP_PointGet(wk->pp.ssp, &wk->pp.p);
	
	r_vec = WazaTool_VecChangeX(we_sys, WeSysDFNoGet(we_sys));
	if (r_vec < 0){
		wk->ofs_x *= +1;
	}
	else {
		wk->ofs_x *= -1;
	}
	WEEffect_TCB_AddPriSet(wk->wsp, We253_TCB, wk);
}










// -----------------------------------------
//
//
//		[ __WE_271__ ]	トリック
//
//
// -----------------------------------------
#define WE271_EVP		(16)				///< 変化α
#define WE271_EVP2		(2)					///< 変化α
#define WE271_EVA		(16)				///< α定数
#define WE271_EVB		(0)
#define WE271_EVAM		(0)
#define WE271_EVBM		(16)
#define WE271_OFS		(16)				///< オフセット
#define WE271_CUP_1_X	(100)				///< カップ表示位置
#define WE271_CUP_1_Y	(40 - WE271_OFS + 20)
#define WE271_CUP_2_X	(180)
#define WE271_CUP_2_Y	(25  - WE271_OFS + 20)
#define WE271_WAIT		(15)				///< ウェイト
#define WE271_WAIT3		(10)
#define WE271_WAIT4		(12)
#define WE271_ROTA_WAIT	(15)

#define WE271_BASE_CUP	(1)					///< フラグ
#define WE271_SUB_CUP	(0)

#define WE271_CUP_FI_LINE	(WE271_CUP_1_Y + 60)
#define WE271_CUP_STOP		(WE271_CUP_FI_LINE)// + 20)

// -----------------------------------------
//
//	構造体
//
// -----------------------------------------
typedef struct {
	CATS_ACT_PTR		cap;	///< OAM
	WAZATOOL_CALCMOVE	cv[2];	///< カーブ計算用	
} TWE_271_CUP;

typedef struct {
	
	u8	seq;
	u8	wait;

	int	eva;
	int	evb;
	
	u8	loop;

	WE_SYS_PTR	 wsp;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	
	
	SOFT_SPRITE*	ssp;
	s16				dy;
	int				poke_h;
	
	u16		angle;
	fx32	range;
	TWE_271_CUP		cup[2];
	
	s16				mx;
	s16				my;

	WAZATOOL_CALCMOVE cm;
	
} TWE_271_SYS;

enum {
	eW271_STEP_0,
	eW271_STEP_1,
	eW271_STEP_2,
	eW271_STEP_END,
};

enum {
	eW271_SEQ_AFF_INIT = 0,
	eW271_SEQ_AFF_MAIN,
	eW271_SEQ_WAIT,
	eW271_SEQ_FALL_INIT,
	eW271_SEQ_FALL_MAIN,
	eW271_SEQ_ROTA_INIT,
	eW271_SEQ_ROTA_SET,
	eW271_SEQ_ROTA_MAIN,
	eW271_SEQ_FADE_OUT,
};

static const u8 w271_step_data[][5] = {
	{ 100, 100, 100,  70, 8 },
	{ 100, 100,  70, 120, 3 },
	{ 100, 100, 120, 100, 3 },
};

//--------------------------------------------------------------
/**
 * @brief	回転初期化関数
 *
 * @param	p_wtc	
 * @param	dir	
 * @param	base	
 * @param	angle	
 * @param	range	
 * @param	sync	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WE271_RotaInit(WAZATOOL_CALCMOVE* p_wtc, s8 dir, u8 base, u16 angle, fx32 range, u16 sync)
{
	u16  angle_01, angle_02;

	if (dir < 0 && base == 1
	||	dir > 0 && base == 0){
		angle_01 = angle + FX_GET_ROTA_NUM(180);
		angle_02 = angle;
	}
	else {
		angle_01 = angle;
		angle_02 = angle + FX_GET_ROTA_NUM(180);
	}
	WazaTool_InitRotaFx(p_wtc,
						angle_01, angle_02,
						angle_01, angle_02,
						range * dir,
						range * dir,
						sync);	
}

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
#define CUP_WIDE	(40)
//--------------------------------------------------------------
static void We271_TCB(TCB_PTR tcb, void* work)
{
	int i;
	TWE_271_SYS* wk = (TWE_271_SYS*)work;

	switch(wk->seq){
	case eW271_SEQ_AFF_INIT:
		///< 縮む
		WazaTool_InitScaleRateEx(&wk->cm,
								 w271_step_data[wk->loop][0],
								 w271_step_data[wk->loop][1],
								 w271_step_data[wk->loop][2],
								 w271_step_data[wk->loop][3], 100,
								 w271_step_data[wk->loop][4]);
		wk->loop++;
		wk->seq++;
		break;
		
	case eW271_SEQ_AFF_MAIN:
		///< 縮み待ち
		if (WazaTool_CalcScaleRateEx(&wk->cm) == TRUE){
			SoftSpriteParaSet(wk->ssp, SS_PARA_AFF_X, wk->cm.x);
			SoftSpriteParaSet(wk->ssp, SS_PARA_AFF_Y, wk->cm.y);
			{
				s16 ofs_y = WazaTool_CalcScaleRateToYPosFX(wk->dy, wk->poke_h, wk->cm.work[4]);
				SoftSpriteParaSet(wk->ssp, SS_PARA_POS_Y, wk->dy + ofs_y);
			}
		}
		else {
			if (wk->loop >= eW271_STEP_END){
				wk->seq++;
			}
			else {
				wk->seq--;
			}
		}
		break;
	
	case eW271_SEQ_WAIT:
		///< wait
		if ((++wk->wait) >= WE271_WAIT){
			wk->wait = 0;
			wk->loop = 0;
			wk->seq++;
		}
		break;
		
	case eW271_SEQ_FALL_INIT:
		///< 落下予備
		{
			s16 x, y;
			CATS_ObjectPosGetCap(wk->cup[0].cap, &x, &y);
			
			if (y <= WE271_CUP_FI_LINE){
				CATS_ObjectPosMoveCap(wk->cup[0].cap, 0, 2);
				CATS_ObjectPosMoveCap(wk->cup[1].cap, 0, 2);
			}
			else {
				wk->seq++;
			}
		}
		break;
	
	case eW271_SEQ_FALL_MAIN:
		///< カップ落下 + フェード
		{
			s16 x, y;
			CATS_ObjectPosGetCap(wk->cup[0].cap, &x, &y);
			
			if (y <= WE271_CUP_STOP){
				CATS_ObjectPosMoveCap(wk->cup[0].cap, 0, 2);
				CATS_ObjectPosMoveCap(wk->cup[1].cap, 0, 2);
			}
			else {
				G2_ChangeBlendAlpha(WE271_EVA, WE271_EVB);
				wk->seq++;
			}
		}
		wk->wait++;

		WazaTool_ParamCalc(&wk->eva, WE271_EVA, +WE271_EVP);
		WazaTool_ParamCalc(&wk->evb, WE271_EVB, -WE271_EVP);
		G2_ChangeBlendAlpha(wk->eva, wk->evb);
		
		if (wk->wait == WE271_WAIT3){
			CATS_ObjectPosMoveCap(wk->cup[0].cap, 0, WE271_OFS);
		}
		if (wk->wait == WE271_WAIT4){
			CATS_ObjectPosMoveCap(wk->cup[1].cap, 0, WE271_OFS);
		}

		break;

	case eW271_SEQ_ROTA_INIT:
		if ((++wk->wait) < WE271_WAIT){ break; }
		wk->wait = 0;
		{
			s16 x1, y1, x2, y2;
			
			CATS_ObjectPosGetCap(wk->cup[0].cap, &x1, &y1);
			CATS_ObjectPosGetCap(wk->cup[1].cap, &x2, &y2);
			
			WazaTool_MiddlePointGet(x1, y1, x2, y2, &wk->mx, &wk->my);
			WazaTool_RangeGetFx(x1, y1, wk->mx, wk->my, &wk->range);
			WazaTool_PointToPointAngleGet(x1, y1, wk->mx, wk->my, &wk->angle);

			wk->range = (CUP_WIDE * FX32_ONE);
		}
		wk->seq++;
		break;
	
	case eW271_SEQ_ROTA_SET:
		{
			s16 x1, y1, x2, y2;
			s8 direc[][2] = { { +1, -1 },{ -1, +1 },{ +1, -1 },{ +1, -1 }, { +1, -1 }, };
			
			CATS_ObjectPosGetCap(wk->cup[0].cap, &x1, &y1);
			CATS_ObjectPosGetCap(wk->cup[1].cap, &x2, &y2);

			WazaTool_InitCurveYFx(&wk->cup[0].cv[0],
								  &wk->cup[0].cv[1], 
								  x1,
								  x2,
								  y1,
								  y2,
								  10, wk->range * direc[wk->loop][0]);
			WazaTool_InitCurveYFx(&wk->cup[1].cv[0],
								  &wk->cup[1].cv[1], 
								  x2,
								  x1,
								  y2,
								  y1,
								  10, wk->range * direc[wk->loop][1]);
		}
		wk->loop++;
		wk->seq++;
		break;
	
	case eW271_SEQ_ROTA_MAIN:
		{
			u8 ret = 0;
			
			if (WazaTool_CalcAndReflectCurveFxCap(&wk->cup[0].cv[0], &wk->cup[0].cv[1], wk->cup[0].cap) == FALSE){
				ret++;
			}
			if (WazaTool_CalcAndReflectCurveFxCap(&wk->cup[1].cv[0], &wk->cup[1].cv[1], wk->cup[1].cap) == FALSE){
				ret++;
			}
			if (ret == 2){
				if (wk->loop == 5){
					wk->seq++;
				}
				else {
					wk->seq--;
				}
			}
		}
		break;

	case eW271_SEQ_FADE_OUT:
		///< フェード
		{
			int ret = 0;

			if (WazaTool_ParamCalc(&wk->eva, WE271_EVAM, -WE271_EVP2) == TRUE){
				ret++;
			}
				
			if (WazaTool_ParamCalc(&wk->evb, WE271_EVBM, +WE271_EVP2) == TRUE){
				ret++;
			}
			G2_ChangeBlendAlpha(wk->eva, wk->evb);
			
			if (ret == 2){
				wk->seq++;
			}
		}
		break;

	default:
		for (i = 0; i < WeSysGPWorkGet(wk->wsp, 0); i++){
			CATS_ActorPointerDelete_S(wk->cup[i].cap);
		}
		WEEffect_TCB_Delete(wk->wsp, tcb);
		sys_FreeMemoryEz(wk);
		return;
	}
	
	{
		s16 x, y;
		
		for (i = 0; i < WeSysGPWorkGet(wk->wsp, 0); i++){
			
			CATS_ObjectPosGetCap(wk->cup[i].cap, &x, &y);
			
			if (y < 80){
				CATS_ObjectBGPriSetCap(wk->cup[i].cap, BT_3DPriorityGet(wk->wsp));
			}
			else {
				if (x > 128){
					CATS_ObjectBGPriSetCap(wk->cup[i].cap, BT_3DPriorityGet(wk->wsp));
				}
				else {
					CATS_ObjectBGPriSetCap(wk->cup[i].cap, BT_3DPriorityGet(wk->wsp) + 1);
				}
			}
		}
	}
	
	if (wk->seq < eW271_SEQ_FALL_MAIN){
		return;
	}

	for (i = 0; i < WeSysGPWorkGet(wk->wsp, 0); i++){
		CATS_ObjectUpdateCap(wk->cup[i].cap);
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
void WestSp_CAT_WE_271(WE_SYS_PTR we_sys, CATS_SYS_PTR csp, CATS_RES_PTR crp, CATS_ACT_PTR cap)
{
	int i;
	TWE_271_SYS* wk;
	TCATS_OBJECT_ADD_PARAM_S coap;
	
	wk = WET_ALLOC_MEMORY(we_sys, TWE_271_SYS);
	
	wk->seq		= 0;
	wk->wait	= 0;
	wk->wsp		= we_sys;
	wk->crp		= crp;
	wk->csp		= csp;
	
	wk->eva		= WE271_EVAM;
	wk->evb		= WE271_EVBM;
	
	wk->ssp		= WeSysSoftSpritePointerGet( wk->wsp, WeSysATNoGet(wk->wsp) );
	wk->dy		= SoftSpriteParaGet(wk->ssp, SS_PARA_POS_Y);
	wk->poke_h	= WeSysPokeOfsGet(wk->wsp, WeSysATNoGet(wk->wsp));
	
	WET_BGSelectBlendSet(wk->wsp, 
						( 1 << BT_BGL_BGNoGet(we_sys, WES_BF_BACKGROUND) ) |
						( 1 << BT_BGL_BGNoGet(we_sys, WES_BF_EFFECT) ) | GX_WND_PLANEMASK_BG0,
						WET_DEFAULT_BLEND, WET_DEFAULT_BLEND);
	G2_ChangeBlendAlpha(wk->eva, wk->evb);
	
	coap    	= WeSysCoapGet(we_sys);
	wk->cup[0].cap	= cap;
	{	
		for (i = 1; i < WeSysGPWorkGet(wk->wsp,0); i++){
			wk->cup[i].cap = CATS_ObjectAdd_S(wk->csp, wk->crp, &coap);
		}
	}
	
	for (i = 0; i < WeSysGPWorkGet(wk->wsp,0); i++){
		CATS_ObjectObjModeSetCap(wk->cup[i].cap, GX_OAM_MODE_XLU);
		CATS_ObjectBGPriSetCap(wk->cup[i].cap, BT_3DPriorityGet(wk->wsp) + 1);
	}
	
	if (WES_ContestFlag_Get(we_sys) == TRUE){
		CATS_ObjectPosSetCap(wk->cup[0].cap, WE271_CUP_2_X - 20, WE271_CUP_1_Y);
		CATS_ObjectPosSetCap(wk->cup[1].cap, WE271_CUP_1_X - 20, WE271_CUP_2_Y);
	}
	else {
		CATS_ObjectPosSetCap(wk->cup[0].cap, WE271_CUP_1_X, WE271_CUP_1_Y);
		CATS_ObjectPosSetCap(wk->cup[1].cap, WE271_CUP_2_X, WE271_CUP_2_Y);
	}
	
	WEEffect_TCB_AddPriSet(wk->wsp, We271_TCB, wk);
}

