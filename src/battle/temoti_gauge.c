//==============================================================================
/**
 * @file	temoti_gauge.c
 * @brief	手持ちゲージ
 * @author	matsuda
 * @date	2006.06.14(水)
 */
//==============================================================================
#include "common.h"
#include "graphic/batt_obj_def.h"
#include "system/arc_tool.h"
#include "battle/battle_id.h"
#include "battle/battle_tcb_pri.h"
#include "battle/fight_tool.h"
#include "temoti_gauge.h"
#include "battle_snd_def.h"


//==============================================================================
//	定数定義
//==============================================================================
///手持ちゲージのアニメシーケンス番号
enum{
	TGANM_BALL_ALIVE_ENEMY,		///<ポケモンがいる(生きている)：敵側
	TGANM_BALL_NG_ENEMY,		///<ポケモンがいる(ステータス異常)：敵側
	TGANM_BALL_DEAD_ENEMY,		///<ポケモンがいる(気絶)：敵側
	TGANM_BALL_ALIVE_MINE,		///<ポケモンがいる(生きている)：自機側
	TGANM_BALL_NG_MINE,			///<ポケモンがいる(ステータス異常)：自機側
	TGANM_BALL_DEAD_MINE,		///<ポケモンがいる(気絶)：自機側
	TGANM_BALL_NONE,			///<ポケモンがいない(自機、敵両方)
	TGANM_ARROW_ENEMY,			///<矢印(敵側)
	TGANM_ARROW_MINE,			///<矢印(自機側)
};

//--------------------------------------------------------------
//	矢印
//--------------------------------------------------------------
///矢印登場開始座標X(自機側)
#define ARROW_MINE_START_X			(256 + 96)
///矢印到着座標X(自機側)
#define ARROW_MINE_END_X			(256 - 32)
///矢印座標Y(自機側)
#define ARROW_MINE_Y				(128)

///矢印登場開始座標X(敵側)
#define ARROW_ENEMY_START_X			(-96)
///矢印到着座標X(敵側)
#define ARROW_ENEMY_END_X			(32)
///矢印座標Y(敵側)
#define ARROW_ENEMY_Y				(56)

///矢印IN速度(下位8ビット小数)
#define ARROW_IN_SPEED				(0x0e00)
///矢印OUT速度(下位8ビット小数)
#define ARROW_OUT_SPEED				(0x0400)

//--------------------------------------------------------------
//	ボール
//--------------------------------------------------------------
///ボール登場開始座標X(自機側)
#define BALL_MINE_START_X			(256 + 20)
///ボール到着座標X(自機側)
#define BALL_MINE_END_X				(256 - 128 + 20 + 14)
///ボール座標Y(自機側)
#define BALL_MINE_Y					(ARROW_MINE_Y - 6)

///ボール登場開始座標X(敵側)
#define BALL_ENEMY_START_X			(-20)
///ボール到着座標X(敵側)
#define BALL_ENEMY_END_X			(128 - 20 - 14)
///ボール座標Y(敵側)
#define BALL_ENEMY_Y				(ARROW_ENEMY_Y - 6)

///ボールIN速度(下位8ビット小数)
#define BALL_IN_SPEED				(ARROW_IN_SPEED)
///ボールOUT速度(下位8ビット小数)
#define BALL_OUT_SPEED				(0x0c00)

///エンカウントIN時、1個目のボールがIN開始するまでのウェイト
#define BALL_ENCOUNT_FAST_IN_WAIT	(5)
///エンカウントIN時、ボール一つ毎の動き始めるまでのウェイト
#define BALL_ENCOUNT_IN_WAIT		(3)
///ボール一つ毎のX座標配置間隔
#define BALL_SPACE_X				(16)
///ボールがエンカウントIN時、詰まった状態になる時のX座標配置間隔
#define BALL_OVER_SPACE_X				(15)
///ボールがエンカウントIN時、詰まった状態になる時のX座標オフセット座標
#define BALL_OVER_LEN				(6)

///ボール回転速度(自機側)
#define BALL_MINE_ROTATION		(-0x2800)
///ボール回転速度(敵側)
#define BALL_ENEMY_ROTATION		(-BALL_MINE_ROTATION)

///ボールのコロンの動作を始めるまでのウェイト
#define BALL_KORON_WAIT			(0)
///ボールのコロンの動作の時の移動速度(下位8ビット小数)
#define BALL_KORON_SPEED		(0x0600)
///コロン動作前の斜め向きで停止しているアニメのフレーム番号(自機側)
#define BALL_NANAME_ANM_FRAME_MINE	(1)
///コロン動作前の斜め向きで停止しているアニメのフレーム番号(敵側)
#define BALL_NANAME_ANM_FRAME_ENEMY	(1)

//--------------------------------------------------------------
//	半透明
//--------------------------------------------------------------
///半透明速度(下位8ビット小数)
#define ARROW_ALPHA_OUT_SP			(0x0100)

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///エンカウントアウトの時、カスタムボールのロードで動きがガクガクになるので、動き始めるまで
///少しウェイトを入れる(カスタムボールのロードが終わったら動き始めるぐらいにしている)
#define ARROW_SCROLL_OUT_START_WAIT		(4)
#define BALL_OUT_ENCOUNT_START_WAIT		(ARROW_SCROLL_OUT_START_WAIT)


//==============================================================================
//	構造体定義
//==============================================================================
///矢印ワーク
typedef struct{
	CATS_ACT_PTR cap;
	TCB_PTR tcb;
	ARROW_OUT_TYPE out_type;
	TEMOTI_SIDE side;
	BALL_POS_TYPE pos_type;
	s32 x;			///<X座標(下位8ビット小数)
	s16 alpha;		///<半透明αレジスタ値(下位8ビット小数)
	u8 seq;
	u8 start_wait;
}TG_ARROW_WORK;

///ボールワーク
typedef struct{
	CATS_ACT_PTR cap;
	TCB_PTR tcb;
	TEMOTI_SIDE side;
	BALL_POS_TYPE pos_type;
	BALL_OUT_TYPE out_type;
	s8 *in_count;
	s16 *arrow_alpha;		///<矢印が管理している半透明αレジスタ値へのポインタ
	s32 x;
	s32 end_x;
	s32 over_end_x;
	s16 wait;
	u16 se_id;
	u8 seq;
	u8 pos;
	u8 flip_anmseq;
	u8 start_wait;
}TG_BALL_WORK;

///手持ちゲージワーク
typedef struct _TEMOTIGAUGE_WORK{
	TG_ARROW_WORK	arrow;
	TG_BALL_WORK	ball[POKEMON_TEMOTI_MAX];
	s8 in_count;
}TEMOTIGAUGE_WORK;


//==============================================================================
//	データ
//==============================================================================
///手持ちゲージ矢印アクターヘッダ
static const TCATS_OBJECT_ADD_PARAM_S TemotiGaugeArrowObjParam = {
	0, 0, 0,		//x, y, z
	0, 10, 0,		//アニメ番号、優先順位、パレット番号
	NNS_G2D_VRAM_TYPE_2DMAIN,		//描画エリア
	{	//使用リソースIDテーブル
		CHARID_TEMOTI_GAUGE,	//キャラ
		PLTTID_TEMOTI_GAUGE,	//パレット
		CELLID_TEMOTI_GAUGE,	//セル
		CELLANMID_TEMOTI_GAUGE,	//セルアニメ
		CLACT_U_HEADER_DATA_NONE,		//マルチセル
		CLACT_U_HEADER_DATA_NONE,		//マルチセルアニメ
	},
	0,			//BGプライオリティ
	0,			//Vram転送フラグ
};

///手持ちゲージボールアクターヘッダ
static const TCATS_OBJECT_ADD_PARAM_S TemotiGaugeBallObjParam = {
	0, 0, 0,		//x, y, z
	0, 8, 0,		//アニメ番号、優先順位、パレット番号
	NNS_G2D_VRAM_TYPE_2DMAIN,		//描画エリア
	{	//使用リソースIDテーブル
		CHARID_TEMOTI_GAUGE,	//キャラ
		PLTTID_TEMOTI_GAUGE,	//パレット
		CELLID_TEMOTI_GAUGE,	//セル
		CELLANMID_TEMOTI_GAUGE,	//セルアニメ
		CLACT_U_HEADER_DATA_NONE,		//マルチセル
		CLACT_U_HEADER_DATA_NONE,		//マルチセルアニメ
	},
	0,			//BGプライオリティ
	0,			//Vram転送フラグ
};


//==============================================================================
//	データ
//==============================================================================
///自機側矢印位置Y
ALIGN4 static const u16 ArrowMinePosY[] = {
	ARROW_MINE_Y - 36,		//BALL_POS_HIGH
	ARROW_MINE_Y,			//BALL_POS_MIDDLE
	ARROW_MINE_Y,			//BALL_POS_LOW
};

///敵側矢印位置Y
ALIGN4 static const u16 ArrowEnemyPosY[] = {
	ARROW_ENEMY_Y - 36,		//BALL_POS_HIGH
	ARROW_ENEMY_Y,			//BALL_POS_MIDDLE
	ARROW_ENEMY_Y,			//BALL_POS_LOW
};

///自機側ボール位置Y
ALIGN4 static const u16 BallMinePosY[] = {
	BALL_MINE_Y - 36,		//BALL_POS_HIGH
	BALL_MINE_Y,			//BALL_POS_MIDDLE
	BALL_MINE_Y,			//BALL_POS_LOW
};

///敵側ボール位置Y
ALIGN4 static const u16 BallEnemyPosY[] = {
	BALL_ENEMY_Y - 36,		//BALL_POS_HIGH
	BALL_ENEMY_Y,			//BALL_POS_MIDDLE
	BALL_ENEMY_Y,			//BALL_POS_LOW
};


//==============================================================================
//	プロトタイプ宣言
//==============================================================================
static void TEMOTI_ArrowIn(TG_ARROW_WORK *arrow, TEMOTI_SIDE side, BALL_POS_TYPE pos_type,
	CATS_SYS_PTR csp, CATS_RES_PTR crp);
static void TEMOTI_ArrowOut(TG_ARROW_WORK *arrow, ARROW_OUT_TYPE out_type);
static void TEMOTI_BallIn(TG_BALL_WORK *ball, s8 *in_count, TEMOTI_SIDE side, 
	BALL_IN_TYPE ball_in_type, BALL_POS_TYPE pos_type,
	int pos, int anmseq, CATS_SYS_PTR csp, CATS_RES_PTR crp);
static void TEMOTI_BallOut(TG_BALL_WORK *ball, int pos, BALL_OUT_TYPE out_type, s16 *alpha);
static void ArrowTask_In(TCB_PTR tcb, void *work);
static void ArrowTask_Out(TCB_PTR tcb, void *work);
static void BallTask_EncountIn(TCB_PTR tcb, void *work);
static void BallTask_ChangeIn(TCB_PTR tcb, void *work);
static void BallTask_EncountOut(TCB_PTR tcb, void *work);
static void BallTask_ChangeOut(TCB_PTR tcb, void *work);
static int BallStatusAnimeSeqGet(int status, TEMOTI_SIDE side);
static int BallStatusFlipAnimeSeqGet(int anm_seq);
static TEMOTIGAUGE_PTR TEMOTI_SystemWorkAlloc(void);
static void TEMOTI_SystemWorkFree(TEMOTIGAUGE_PTR tb);



//--------------------------------------------------------------
/**
 * @brief   手持ちゲージのリソースをロードする
 *
 * @param   csp			
 * @param   crp			
 * @param   pfd			
 */
//--------------------------------------------------------------
void TEMOTI_ResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, PALETTE_FADE_PTR pfd)
{
	CATS_LoadResourcePlttWorkArc(pfd, FADE_MAIN_OBJ, csp, crp, 
		ARC_BATT_OBJ, GAUGE_M_BALL_NCLR, 0, 
		1, NNS_G2D_VRAM_TYPE_2DMAIN, PLTTID_TEMOTI_GAUGE);
	CATS_LoadResourceCharArc(csp, crp, ARC_BATT_OBJ, 
		GAUGE_M_BALL_NCGR_BIN, 1, NNS_G2D_VRAM_TYPE_2DMAIN, CHARID_TEMOTI_GAUGE);
	CATS_LoadResourceCellArc(csp, crp, ARC_BATT_OBJ, 
		GAUGE_M_BALL_NCER_BIN, 1, CELLID_TEMOTI_GAUGE);
	CATS_LoadResourceCellAnmArc(csp, crp, ARC_BATT_OBJ, 
		GAUGE_M_BALL_NANR_BIN, 1, CELLANMID_TEMOTI_GAUGE);
}

//--------------------------------------------------------------
/**
 * @brief   手持ちゲージのリソースを解放する
 *
 * @param   crp			
 */
//--------------------------------------------------------------
void TEMOTI_ResourceFree(CATS_RES_PTR crp)
{
	CATS_FreeResourceChar(crp, CHARID_TEMOTI_GAUGE);
	CATS_FreeResourcePltt(crp, PLTTID_TEMOTI_GAUGE);
	CATS_FreeResourceCell(crp, CELLID_TEMOTI_GAUGE);
	CATS_FreeResourceCellAnm(crp, CELLANMID_TEMOTI_GAUGE);
}

//--------------------------------------------------------------
/**
 * @brief   手持ちゲージワークをAllocする
 *
 * @retval  手持ちゲージワークへのポインタ
 */
//--------------------------------------------------------------
static TEMOTIGAUGE_PTR TEMOTI_SystemWorkAlloc(void)
{
	TEMOTIGAUGE_WORK *tg;
	
	tg = sys_AllocMemory(HEAPID_BATTLE, sizeof(TEMOTIGAUGE_WORK));
	MI_CpuClear8(tg, sizeof(TEMOTIGAUGE_WORK));
	return tg;
}

//--------------------------------------------------------------
/**
 * @brief   手持ちゲージワークをFreeする
 *
 * @param   tb		手持ちゲージワークへのポインタ
 */
//--------------------------------------------------------------
static void TEMOTI_SystemWorkFree(TEMOTIGAUGE_PTR tb)
{
	GF_ASSERT(tb->arrow.tcb == NULL);
	
	sys_FreeMemoryEz(tb);
}

//--------------------------------------------------------------
/**
 * @brief   手持ちゲージINエフェクトを起動する
 *
 * @param   status[]	ポケモンのステータス情報(POKEMON_TEMOTI_MAX分の配列)
 * @param   side		TEMOTI_MINE or TEMOTI_ENEMY
 *
 * @retval  手持ちゲージワークへのポインタ
 */
//--------------------------------------------------------------
TEMOTIGAUGE_PTR TEMOTI_InEffectSet(u8 status[], TEMOTI_SIDE side, BALL_IN_TYPE ball_in_type,
	BALL_POS_TYPE pos_type, CATS_SYS_PTR csp, CATS_RES_PTR crp)
{
	TEMOTIGAUGE_PTR tg;
	int i, anmseq;
	
	tg = TEMOTI_SystemWorkAlloc();
	TEMOTI_ArrowIn(&tg->arrow, side, pos_type, csp, crp);
	
	for(i = 0; i < POKEMON_TEMOTI_MAX; i++){
		anmseq = BallStatusAnimeSeqGet(status[i], side);
		TEMOTI_BallIn(&tg->ball[i], &tg->in_count, side, ball_in_type, pos_type,
			i, anmseq, csp, crp);
	}
	return tg;
}

//--------------------------------------------------------------
/**
 * @brief   手持ちゲージINエフェクトの終了確認
 *
 * @param   tg		手持ちゲージワークへのポインタ
 *
 * @retval  TRUE:終了、　FALSE:エフェクト中
 */
//--------------------------------------------------------------
BOOL TEMOTI_InEffectEndCheck(TEMOTIGAUGE_PTR tg)
{
	int i;
	
	if(tg->arrow.tcb == NULL){
		for(i = 0; i < POKEMON_TEMOTI_MAX; i++){
			if(tg->ball[i].tcb != NULL){
				break;
			}
		}
		if(i == POKEMON_TEMOTI_MAX){
			return TRUE;
		}
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   手持ちゲージOUTエフェクトを起動する
 *
 * @p
 * @param   status[]	ポケモンのステータス情報(POKEMON_TEMOTI_MAX分の配列)
 * @param   side		TEMOTI_MINE or TEMOTI_ENEMY
 *
 * @retval  手持ちゲージワークへのポインタ
 */
//--------------------------------------------------------------
void TEMOTI_OutEffectSet(TEMOTIGAUGE_PTR tg, 
	ARROW_OUT_TYPE arrow_out_type, BALL_OUT_TYPE ball_out_type)
{
	int i;
	
	GF_ASSERT(tg != NULL);
	
	TEMOTI_ArrowOut(&tg->arrow, arrow_out_type);
	for(i = 0; i < POKEMON_TEMOTI_MAX; i++){
		TEMOTI_BallOut(&tg->ball[i], i, ball_out_type, &tg->arrow.alpha);
	}
}

//--------------------------------------------------------------
/**
 * @brief   手持ちゲージINエフェクトの終了確認
 *
 * @param   tg		手持ちゲージワークへのポインタ
 *
 * @retval  TRUE:終了、　FALSE:エフェクト中
 */
//--------------------------------------------------------------
BOOL TEMOTI_OutEffectEndCheck(TEMOTIGAUGE_PTR tg)
{
	int i;
	
	if(tg->arrow.tcb == NULL){
		for(i = 0; i < POKEMON_TEMOTI_MAX; i++){
			if(tg->ball[i].tcb != NULL){
				break;
			}
		}
		if(i == POKEMON_TEMOTI_MAX){
			return TRUE;
		}
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   手持ちゲージのエフェクト解放処理
 *
 * @param   tg		手持ちゲージワークへのポインタ
 *
 * アクターの削除、手持ちゲージワーク自身の解放を行います
 */
//--------------------------------------------------------------
void TEMOTI_EffectFree(TEMOTIGAUGE_PTR tg)
{
	int i;
	
	CATS_ActorPointerDelete_S(tg->arrow.cap);
	for(i = 0; i < POKEMON_TEMOTI_MAX; i++){
		CATS_ActorPointerDelete_S(tg->ball[i].cap);
	}
	
	TEMOTI_SystemWorkFree(tg);
}


//==============================================================================
//
//	矢印登場
//
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   矢印登場エフェクトを起動する
 *
 * @param   arrow			矢印ワークへのポインタ
 * @param   side		TEMOTI_MINE or TEMOTI_ENEMY
 */
//--------------------------------------------------------------
static void TEMOTI_ArrowIn(TG_ARROW_WORK *arrow, TEMOTI_SIDE side, BALL_POS_TYPE pos_type,
	CATS_SYS_PTR csp, CATS_RES_PTR crp)
{
	GF_ASSERT(arrow->cap == NULL && arrow->tcb == NULL);
	
	MI_CpuClear8(arrow, sizeof(TG_ARROW_WORK));
	
	//アクター生成
	arrow->cap = CATS_ObjectAdd_S(csp, crp, &TemotiGaugeArrowObjParam);
	if(side == TEMOTI_MINE){
		CATS_ObjectPosSetCap(arrow->cap, ARROW_MINE_START_X, ArrowMinePosY[pos_type]);
		CLACT_AnmChg(arrow->cap->act, TGANM_ARROW_MINE);
	}
	else{
		CATS_ObjectPosSetCap(arrow->cap, ARROW_ENEMY_START_X, ArrowEnemyPosY[pos_type]);
		CLACT_AnmChg(arrow->cap->act, TGANM_ARROW_ENEMY);
	}
	CATS_ObjectUpdate(arrow->cap->act);

	//ワーク設定
	arrow->side = side;
	arrow->pos_type = pos_type;
	
	//タスク生成
	arrow->seq = 0;
	arrow->tcb = TCB_Add(ArrowTask_In, arrow, TCBPRI_TEMOTIGAUGE_ARROW);
	
	Snd_SePlay(BSE_TB_START);
}

//--------------------------------------------------------------
/**
 * @brief   矢印動作タスク：画面IN
 *
 * @param   tcb			TCBへのポインタ
 * @param   work		矢印ワークへのポインタ
 */
//--------------------------------------------------------------
static void ArrowTask_In(TCB_PTR tcb, void *work)
{
	TG_ARROW_WORK *arrow = work;
	
	switch(arrow->seq){
	case 0:	//ワーク初期化
		{
			s16 x, y;
			CATS_ObjectPosGetCap(arrow->cap, &x, &y);
			arrow->x = x << 8;
		}
		arrow->seq++;
		//break;
	case 1:
		if(arrow->side == TEMOTI_MINE){
			arrow->x -= ARROW_IN_SPEED;
			if(arrow->x <= ARROW_MINE_END_X << 8){
				arrow->x = ARROW_MINE_END_X << 8;
				arrow->seq++;
			}
			CATS_ObjectPosSetCap(arrow->cap, arrow->x >> 8, ArrowMinePosY[arrow->pos_type]);
		}
		else{
			arrow->x += ARROW_IN_SPEED;
			if(arrow->x >= ARROW_ENEMY_END_X << 8){
				arrow->x = ARROW_ENEMY_END_X << 8;
				arrow->seq++;
			}
			CATS_ObjectPosSetCap(arrow->cap, arrow->x >> 8, ArrowEnemyPosY[arrow->pos_type]);
		}
		break;
	default:
		TCB_Delete(tcb);
		arrow->tcb = NULL;
		return;
	}
}


//==============================================================================
//
//	矢印退場
//
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   矢印退場エフェクトを起動する
 *
 * @param   arrow			矢印ワークへのポインタ
 * @param   out_type		退場動作指定
 */
//--------------------------------------------------------------
static void TEMOTI_ArrowOut(TG_ARROW_WORK *arrow, ARROW_OUT_TYPE out_type)
{
	GF_ASSERT(arrow->cap != NULL && arrow->tcb == NULL);
	
	//タスク生成
	arrow->seq = 0;
	arrow->out_type = out_type;
	if(out_type == ARROW_OUT_TYPE_SCROLL){
		arrow->start_wait = ARROW_SCROLL_OUT_START_WAIT;
	}
	else{
		arrow->start_wait = 0;
	}
	arrow->tcb = TCB_Add(ArrowTask_Out, arrow, TCBPRI_TEMOTIGAUGE_ARROW);
}

//--------------------------------------------------------------
/**
 * @brief   矢印動作タスク：画面OUT
 *
 * @param   tcb			TCBへのポインタ
 * @param   work		矢印ワークへのポインタ
 */
//--------------------------------------------------------------
static void ArrowTask_Out(TCB_PTR tcb, void *work)
{
	TG_ARROW_WORK *arrow = work;
	
	switch(arrow->seq){
	case 0:	//ワーク初期化
		{
			s16 x, y;
			CATS_ObjectPosGetCap(arrow->cap, &x, &y);
			arrow->x = x << 8;
		}

		CATS_ObjectObjModeSetCap(arrow->cap, GX_OAM_MODE_XLU);	//半透明OBJモード

		//半透明レジスタ設定
		arrow->alpha = 16 << 8;
		G2_SetBlendAlpha(GX_BLEND_PLANEMASK_NONE, 
			GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG2 
			| GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BD,
			(arrow->alpha >> 8), 16 - (arrow->alpha >> 8));

		arrow->seq++;
		//break;
	case 1:
		if(arrow->start_wait > 0){
			arrow->start_wait--;
			break;
		}
		arrow->seq++;
		//break;
	case 2:
		if(arrow->out_type == ARROW_OUT_TYPE_SCROLL){
			if(arrow->side == TEMOTI_MINE){
				arrow->x -= ARROW_OUT_SPEED;
				CATS_ObjectPosSetCap(arrow->cap, arrow->x >> 8, ArrowMinePosY[arrow->pos_type]);
			}
			else{
				arrow->x += ARROW_OUT_SPEED;
				CATS_ObjectPosSetCap(arrow->cap, arrow->x >> 8, ArrowEnemyPosY[arrow->pos_type]);
			}
		}
		
		//半透明
		arrow->alpha -= ARROW_ALPHA_OUT_SP;
		if(arrow->alpha <= 0){
			arrow->alpha = 0;
			CATS_ObjectEnable(arrow->cap->act, CATS_ENABLE_FALSE);
			arrow->seq++;
		}
		G2_ChangeBlendAlpha(arrow->alpha >> 8, 16 - (arrow->alpha >> 8));
		break;
	default:
		BattleDefaultBlendSet();
		
		TCB_Delete(tcb);
		arrow->tcb = NULL;
		return;
	}
}


//==============================================================================
//
//	ボール登場
//
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   ボール登場エフェクトを起動する
 *
 * @param   arrow			矢印ワークへのポインタ
 * @param   in_count		ボール全てで共通で使用するカウンタワークへのポインタ
 * @param   side		TEMOTI_MINE or TEMOTI_ENEMY
 * @param   ball_in_type	ボール登場動作タイプ
 * @param   pos				何個目のボールか
 * @param   anmseq			アニメシーケンス番号
 */
//--------------------------------------------------------------
static void TEMOTI_BallIn(TG_BALL_WORK *ball, s8 *in_count, TEMOTI_SIDE side, 
	BALL_IN_TYPE ball_in_type, BALL_POS_TYPE pos_type,
	int pos, int anmseq, CATS_SYS_PTR csp, CATS_RES_PTR crp)
{
	GF_ASSERT(ball->cap == NULL && ball->tcb == NULL);
	
	MI_CpuClear8(ball, sizeof(TG_BALL_WORK));
	
	//アクター生成
	ball->cap = CATS_ObjectAdd_S(csp, crp, &TemotiGaugeBallObjParam);
	if(side == TEMOTI_MINE){
		CATS_ObjectPosSetCap(ball->cap, BALL_MINE_START_X, BallMinePosY[pos_type]);
	}
	else{
		CATS_ObjectPosSetCap(ball->cap, BALL_ENEMY_START_X, BallEnemyPosY[pos_type]);
	}
	CLACT_AnmChg(ball->cap->act, anmseq);
//	CATS_ObjectAffineSetCap(ball->cap, CLACT_AFFINE_NORMAL);
	CATS_ObjectUpdate(ball->cap->act);

	//ワーク設定
	ball->side = side;
	ball->pos = pos;
	ball->pos_type = pos_type;
	ball->flip_anmseq = BallStatusFlipAnimeSeqGet(anmseq);
	ball->in_count = in_count;
	ball->se_id = (anmseq == TGANM_BALL_NONE ? BSE_TB_KARA : BSE_TB_KON);
	
	if(side == TEMOTI_MINE){
		ball->end_x = BALL_MINE_END_X + pos * BALL_SPACE_X;
		ball->over_end_x = BALL_MINE_END_X + pos * BALL_OVER_SPACE_X - BALL_OVER_LEN;
	}
	else{
		ball->end_x = BALL_ENEMY_END_X - pos * BALL_SPACE_X;
		ball->over_end_x = BALL_ENEMY_END_X - pos * BALL_OVER_SPACE_X + BALL_OVER_LEN;
	}
	
	//タスク生成
	ball->seq = 0;
	if(ball_in_type == BALL_IN_TYPE_ENCOUNT){
		ball->wait = BALL_ENCOUNT_IN_WAIT * pos + BALL_ENCOUNT_FAST_IN_WAIT;
		ball->tcb = TCB_Add(BallTask_EncountIn, ball, TCBPRI_TEMOTIGAUGE_BALL);
	}
	else{
		ball->wait = 0;//BALL_ENCOUNT_IN_WAIT * pos;
		ball->tcb = TCB_Add(BallTask_ChangeIn, ball, TCBPRI_TEMOTIGAUGE_BALL);
	}
}

//--------------------------------------------------------------
/**
 * @brief   ボール動作タスク：エンカウント時の画面IN
 *
 * @param   tcb			TCBへのポインタ
 * @param   work		矢印ワークへのポインタ
 */
//--------------------------------------------------------------
static void BallTask_EncountIn(TCB_PTR tcb, void *work)
{
	TG_BALL_WORK *ball = work;
	
	switch(ball->seq){
	case 0:	//ワーク初期化
		{
			s16 x, y;
			CATS_ObjectPosGetCap(ball->cap, &x, &y);
			ball->x = x << 8;
		}
		ball->seq++;
		//break;
	case 1:
		if(ball->wait > 0){
			ball->wait--;
			break;
		}
		//break;
	case 2:
		if(ball->side == TEMOTI_MINE){
			ball->x -= BALL_IN_SPEED;
			if(ball->x <= ball->over_end_x << 8){
				ball->x = ball->over_end_x << 8;
				Snd_SePlay(ball->se_id);
				ball->seq++;
			}
			CATS_ObjectPosSetCap(ball->cap, ball->x >> 8, BallMinePosY[ball->pos_type]);
		}
		else{
			ball->x += BALL_IN_SPEED;
			if(ball->x >= ball->over_end_x << 8){
				ball->x = ball->over_end_x << 8;
				ball->seq++;
			}
			CATS_ObjectPosSetCap(ball->cap, ball->x >> 8, BallEnemyPosY[ball->pos_type]);
		}
		CATS_ObjectUpdate(ball->cap->act);
		break;
	case 3:
//		if(ball->side == TEMOTI_MINE){
//			CLACT_AnmFrameSet(ball->cap->act, BALL_NANAME_ANM_FRAME_MINE);
//		}
//		else{
//			CLACT_AnmFrameSet(ball->cap->act, BALL_NANAME_ANM_FRAME_ENEMY);
//		}
		
		(*(ball->in_count))++;
		ball->seq++;
		//break;
	case 4:
		if(*(ball->in_count) != POKEMON_TEMOTI_MAX){
			CATS_ObjectUpdate(ball->cap->act);
			break;
		}

		if(ball->side == TEMOTI_MINE){
			CLACT_AnmFrameSet(ball->cap->act, BALL_NANAME_ANM_FRAME_MINE);
		}
		else{
			CLACT_AnmFrameSet(ball->cap->act, BALL_NANAME_ANM_FRAME_ENEMY);
		}
		ball->wait = 0;
		ball->seq++;
		//break;
	case 5:
		ball->wait++;
		if(ball->wait < BALL_KORON_WAIT){
			break;
		}
		CLACT_AnmChg(ball->cap->act, ball->flip_anmseq);
		ball->wait = 0;
		ball->seq++;
		//break;
	case 6:
		if(ball->side == TEMOTI_MINE){
			ball->x += BALL_KORON_SPEED;
			if(ball->x >= ball->end_x << 8){
				ball->x = ball->end_x << 8;
				ball->seq++;
			}
			CATS_ObjectPosSetCap(ball->cap, ball->x >> 8, BallMinePosY[ball->pos_type]);
		}
		else{
			ball->x -= BALL_KORON_SPEED;
			if(ball->x <= ball->end_x << 8){
				ball->x = ball->end_x << 8;
				ball->seq++;
			}
			CATS_ObjectPosSetCap(ball->cap, ball->x >> 8, BallEnemyPosY[ball->pos_type]);
		}
		CATS_ObjectUpdate(ball->cap->act);
		break;
	default:
		//CLACT_AnmChg(ball->cap->act, anmseq);
		CLACT_AnmFrameSet(ball->cap->act, 0);
		
		TCB_Delete(tcb);
		ball->tcb = NULL;
		return;
	}
}

//--------------------------------------------------------------
/**
 * @brief   ボール動作タスク：入れ替え時の画面IN
 *
 * @param   tcb			TCBへのポインタ
 * @param   work		矢印ワークへのポインタ
 */
//--------------------------------------------------------------
static void BallTask_ChangeIn(TCB_PTR tcb, void *work)
{
	TG_BALL_WORK *ball = work;
	
	switch(ball->seq){
	case 0:	//ワーク初期化
		{
			s16 x, y;
			CATS_ObjectPosGetCap(ball->cap, &x, &y);
			ball->x = x << 8;
		}
		CLACT_AnmFrameSet(ball->cap->act, 0);
		ball->seq++;
		//break;
	case 1:
		if(ball->wait > 0){
			ball->wait--;
			break;
		}
		//break;
	case 2:
		if(ball->side == TEMOTI_MINE){
			ball->x -= BALL_IN_SPEED;
			if(ball->x <= ball->end_x << 8){
				ball->x = ball->end_x << 8;
				ball->seq++;
			}
			CATS_ObjectPosSetCap(ball->cap, ball->x >> 8, BallMinePosY[ball->pos_type]);
		}
		else{
			ball->x += BALL_IN_SPEED;
			if(ball->x >= ball->end_x << 8){
				ball->x = ball->end_x << 8;
				ball->seq++;
			}
			CATS_ObjectPosSetCap(ball->cap, ball->x >> 8, BallEnemyPosY[ball->pos_type]);
		}
		break;
	default:
		TCB_Delete(tcb);
		ball->tcb = NULL;
		return;
	}
}


//==============================================================================
//
//	ボール退場
//
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   ボール退場エフェクトを起動する
 *
 * @param   ball			矢印ワークへのポインタ
 * @param   pos				ボール手持ち位置
 * @param   out_type		退場動作指定
 * @param   alpha			矢印が管理している半透明レジスタ値へのポインタ
 */
//--------------------------------------------------------------
static void TEMOTI_BallOut(TG_BALL_WORK *ball, int pos, BALL_OUT_TYPE out_type, s16 *alpha)
{
	GF_ASSERT(ball->cap != NULL && ball->tcb == NULL);
	
	//タスク生成
	ball->seq = 0;
	if(out_type == BALL_OUT_TYPE_ENCOUNT){
		ball->arrow_alpha = alpha;
		ball->wait = BALL_ENCOUNT_IN_WAIT * pos;
		ball->start_wait = BALL_OUT_ENCOUNT_START_WAIT;
		ball->tcb = TCB_Add(BallTask_EncountOut, ball, TCBPRI_TEMOTIGAUGE_BALL);
	}
	else{
		ball->arrow_alpha = alpha;
		ball->wait = 0;
		ball->start_wait = 0;
		ball->tcb = TCB_Add(BallTask_ChangeOut, ball, TCBPRI_TEMOTIGAUGE_BALL);
	}
}

//--------------------------------------------------------------
/**
 * @brief   ボール動作タスク：画面OUT
 *
 * @param   tcb			TCBへのポインタ
 * @param   work		矢印ワークへのポインタ
 */
//--------------------------------------------------------------
static void BallTask_EncountOut(TCB_PTR tcb, void *work)
{
	TG_BALL_WORK *ball = work;
	
	if((*(ball->arrow_alpha)) == 0){
		ball->seq = 100;	//終了へ
	}
	
	switch(ball->seq){
	case 0:	//ワーク初期化
		{
			s16 x, y;
			CATS_ObjectPosGetCap(ball->cap, &x, &y);
			ball->x = x << 8;
		}
		CATS_ObjectObjModeSetCap(ball->cap, GX_OAM_MODE_XLU);	//半透明OBJモード
		ball->seq++;
		//break;
	case 1:
		if(ball->start_wait > 0){
			ball->start_wait--;
			break;
		}
		
		if(ball->wait > 0){
			ball->wait--;
			break;
		}
		//break;
	case 2:
		if(ball->side == TEMOTI_MINE){
			ball->x -= BALL_OUT_SPEED;
			CATS_ObjectPosSetCap(ball->cap, ball->x >> 8, BallMinePosY[ball->pos_type]);
		}
		else{
			ball->x += BALL_OUT_SPEED;
			CATS_ObjectPosSetCap(ball->cap, ball->x >> 8, BallEnemyPosY[ball->pos_type]);
		}
		
		if(ball->x < -16*0x100 || ball->x > ((256+16) << 8)){
			ball->seq++;
		}
		CATS_ObjectUpdate(ball->cap->act);
		break;
	case 100:
	default:
		CATS_ObjectEnable(ball->cap->act, CATS_ENABLE_FALSE);
		
		TCB_Delete(tcb);
		ball->tcb = NULL;
		return;
	}
}

//--------------------------------------------------------------
/**
 * @brief   ボール動作タスク：画面OUT(入れ替え時)
 *
 * @param   tcb			TCBへのポインタ
 * @param   work		矢印ワークへのポインタ
 */
//--------------------------------------------------------------
static void BallTask_ChangeOut(TCB_PTR tcb, void *work)
{
	TG_BALL_WORK *ball = work;
	
	if((*(ball->arrow_alpha)) == 0){
		ball->seq = 100;	//終了へ
	}
	
	switch(ball->seq){
	case 0:	//ワーク初期化
		CATS_ObjectObjModeSetCap(ball->cap, GX_OAM_MODE_XLU);	//半透明OBJモード
		ball->seq++;
		//break;
	case 1:		//半透明終了待ち
		break;
	case 100:
	default:
		CATS_ObjectEnable(ball->cap->act, CATS_ENABLE_FALSE);
		
		TCB_Delete(tcb);
		ball->tcb = NULL;
		return;
	}
}

//--------------------------------------------------------------
/**
 * @brief   ステータス情報から、ボールのアニメシーケンス番号を取得する
 * @param   status		ステータス情報
 * @retval  アニメシーケンス番号
 */
//--------------------------------------------------------------
static int BallStatusAnimeSeqGet(int status, TEMOTI_SIDE side)
{
	int anm_seq;
	
	switch(status){
	case COMSEL_STATUS_NONE:
	default:
		anm_seq = TGANM_BALL_NONE;
		break;
	case COMSEL_STATUS_ALIVE:
		anm_seq = side == TEMOTI_MINE ? TGANM_BALL_ALIVE_MINE : TGANM_BALL_ALIVE_ENEMY;
		break;
	case COMSEL_STATUS_DEAD:
		anm_seq = side == TEMOTI_MINE ? TGANM_BALL_DEAD_MINE : TGANM_BALL_DEAD_ENEMY;
		break;
	case COMSEL_STATUS_NG:
		anm_seq = side == TEMOTI_MINE ? TGANM_BALL_NG_MINE : TGANM_BALL_NG_ENEMY;
		break;
	}
	return anm_seq;
}

//--------------------------------------------------------------
/**
 * @brief   ボールのアニメシーケンスから、反対再生のアニメシーケンス番号を取得する
 * @param   anm_seq		アニメシーケンス
 * @retval  反対再生のアニメシーケンス
 */
//--------------------------------------------------------------
static int BallStatusFlipAnimeSeqGet(int anm_seq)
{
	switch(anm_seq){
	case TGANM_BALL_NONE:
	default:
		return anm_seq;
	
	case TGANM_BALL_ALIVE_MINE:
		return TGANM_BALL_ALIVE_ENEMY;
	case TGANM_BALL_ALIVE_ENEMY:
		return TGANM_BALL_ALIVE_MINE;
	
	case TGANM_BALL_DEAD_MINE:
		return TGANM_BALL_DEAD_ENEMY;
	case TGANM_BALL_DEAD_ENEMY:
		return TGANM_BALL_DEAD_MINE;
	
	case TGANM_BALL_NG_MINE:
		return TGANM_BALL_NG_ENEMY;
	case TGANM_BALL_NG_ENEMY:
		return TGANM_BALL_NG_MINE;
	}
}

