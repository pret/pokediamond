//==============================================================================
/**
 * @file	ball_effect.c
 * @brief	ボールエフェクト
 * @author	goto
 * @date	2005.10.24(月)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================

#include "common.h"
#include "system/lib_pack.h"
#include "system/fontproc.h"
#include "system/pm_str.h"

#include "str_tool.h"
#include "wazaeffect/we_mana.h"
#include "system/snd_tool.h"
#include "system/msgdata.h"

#include "spl.h"
#include "include/battle/battle_tcb_pri.h"
//#include "effectdata/we_list.h"

#include "we_tool.h"
#include "we_def.h"
#include "we_sys.h"

#include "ball_effect.h"
#include "battle_particle.h"

#include "d_tool.h"

#include "wazatool.h"

#include "contest/visual_ex.h"

#include "savedata/custom_ball.h"
#include "include/application/cb_sys.h"

#include "ball_effect_tool.h"

#define BE_START_NO (0)						///< 派手目のｴﾌｪｸﾄ

static int ball_eff_loop_cnt = BE_START_NO;

//#define BE_FREE_MOVE

#define BMT_START_POS_OFS_X	(+10)
#define BMT_START_POS_OFS_Y		(32)
#define BMT_START_POS_OFS_E_Y	(38)

/*
#define ITEM_MASUTAABOORU		( 1 )		// マスターボール
#define ITEM_HAIPAABOORU		( 2 )		// ハイパーボール
#define ITEM_SUUPAABOORU		( 3 )		// スーパーボール
#define ITEM_MONSUTAABOORU		( 4 )		// モンスターボール
#define ITEM_SAFARIBOORU		( 5 )		// サファリボール
#define ITEM_NETTOBOORU		( 6 )		// ネットボール
#define ITEM_DAIBUBOORU		( 7 )		// ダイブボール
#define ITEM_NESUTOBOORU		( 8 )		// ネストボール
#define ITEM_RIPIITOBOORU		( 9 )		// リピートボール
#define ITEM_TAIMAABOORU		( 10 )		// タイマーボール
#define ITEM_GOOZYASUBOORU		( 11 )		// ゴージャスボール
#define ITEM_PUREMIABOORU		( 12 )		// プレミアボール
#define ITEM_DAAKUBOORU		( 13 )		// ダークボール
#define ITEM_HIIRUBOORU		( 14 )		// ヒールボール
#define ITEM_KUIKKUBOORU		( 15 )		// クイックボール
#define ITEM_PURESYASUBOORU		( 16 )		// プレシャスボール
*/

///< OAMデータ
/// ---- キャラファイル連番 -----
#if 0
00	モンスターボール
01	マスターボール
02	ハイパーボール
03	スーパーボール
04	サファリボール
05	ネットボール
06	ダイブボール	
07	ネストボール
08	リピートボール	
09	タイマーボール
10	ゴージャスボール
11	プレミアボール
12	【新】クイックボール（青黄
13	【新】ヒールボール（ピンク
14	【新】ダークボール（黒緑
15	【新】プレシアスボール（赤
#endif
/// ------------------------------------
static const int MonsterBall_GRA_Table[][4] = {
	{ BATT_BALL_01_NCGR_BIN, BATT_BALL_01_NCLR, BATT_BALL_01_NCER_BIN, BATT_BALL_01_NANR_BIN, },	///< マスター	ボール
	{ BATT_BALL_02_NCGR_BIN, BATT_BALL_02_NCLR, BATT_BALL_02_NCER_BIN, BATT_BALL_02_NANR_BIN, },	///< ハイパー	ボール
	{ BATT_BALL_03_NCGR_BIN, BATT_BALL_03_NCLR, BATT_BALL_03_NCER_BIN, BATT_BALL_03_NANR_BIN, },	///< スーパー	ボール
	{ BATT_BALL_00_NCGR_BIN, BATT_BALL_00_NCLR, BATT_BALL_00_NCER_BIN, BATT_BALL_00_NANR_BIN, },	///< モンスター	ボール
	{ BATT_BALL_04_NCGR_BIN, BATT_BALL_04_NCLR, BATT_BALL_04_NCER_BIN, BATT_BALL_04_NANR_BIN, },	///< サファリ	ボール
	{ BATT_BALL_05_NCGR_BIN, BATT_BALL_05_NCLR, BATT_BALL_05_NCER_BIN, BATT_BALL_05_NANR_BIN, },	///< ネット		ボール
	{ BATT_BALL_06_NCGR_BIN, BATT_BALL_06_NCLR, BATT_BALL_06_NCER_BIN, BATT_BALL_06_NANR_BIN, },	///< ダイブ		ボール
	{ BATT_BALL_07_NCGR_BIN, BATT_BALL_07_NCLR, BATT_BALL_07_NCER_BIN, BATT_BALL_07_NANR_BIN, },	///< ネスト		ボール
	{ BATT_BALL_08_NCGR_BIN, BATT_BALL_08_NCLR, BATT_BALL_08_NCER_BIN, BATT_BALL_08_NANR_BIN, },	///< リピート	ボール
	{ BATT_BALL_09_NCGR_BIN, BATT_BALL_09_NCLR, BATT_BALL_09_NCER_BIN, BATT_BALL_09_NANR_BIN, },	///< タイマー	ボール
	{ BATT_BALL_10_NCGR_BIN, BATT_BALL_10_NCLR, BATT_BALL_10_NCER_BIN, BATT_BALL_10_NANR_BIN, },	///< ゴージャス	ボール
	{ BATT_BALL_11_NCGR_BIN, BATT_BALL_11_NCLR, BATT_BALL_11_NCER_BIN, BATT_BALL_11_NANR_BIN, },	///< プレミア	ボール
	{ BATT_BALL_13_NCGR_BIN, BATT_BALL_13_NCLR, BATT_BALL_13_NCER_BIN, BATT_BALL_13_NANR_BIN, },	///< ダーク		ボール
	{ BATT_BALL_14_NCGR_BIN, BATT_BALL_14_NCLR, BATT_BALL_14_NCER_BIN, BATT_BALL_14_NANR_BIN, },	///< ヒール		ボール
	{ BATT_BALL_12_NCGR_BIN, BATT_BALL_12_NCLR, BATT_BALL_12_NCER_BIN, BATT_BALL_12_NANR_BIN, },	///< クイック	ボール
	{ BATT_BALL_15_NCGR_BIN, BATT_BALL_15_NCLR, BATT_BALL_15_NCER_BIN, BATT_BALL_15_NANR_BIN, },	///< プレシャス	ボール
	{ BATT_BALL_16_NCGR_BIN, BATT_BALL_16_NCLR, BATT_BALL_16_NCER_BIN, BATT_BALL_16_NANR_BIN, },	///< パーク		ボール
	{ BATT_BALL_18_NCGR_BIN, BATT_BALL_18_NCLR, BATT_BALL_18_NCER_BIN, BATT_BALL_18_NANR_BIN, },	///< どろ		ボール
	{ BATT_BALL_17_NCGR_BIN, BATT_BALL_17_NCLR, BATT_BALL_17_NCER_BIN, BATT_BALL_17_NANR_BIN, },	///< エサ		ボール
	{ BATT_BALL_17_NCGR_BIN, BATT_BALL_17_NCLR, BATT_BALL_17_NCER_BIN, BATT_BALL_17_NANR_BIN, },	///< もどす
};

///< 登場パーティクル
static const int MonsterBall_SPA_Table[][2] = {
	{ SPA_P_BALL_01, P_BALL_01_SPAMAX },	///< マスター	ボール
	{ SPA_P_BALL_02, P_BALL_02_SPAMAX },	///< ハイパー	ボール
	{ SPA_P_BALL_03, P_BALL_03_SPAMAX },	///< スーパー	ボール
	{ SPA_P_BALL_04, P_BALL_04_SPAMAX },	///< モンスター	ボール
	{ SPA_P_BALL_05, P_BALL_05_SPAMAX },	///< サファリ	ボール
	{ SPA_P_BALL_06, P_BALL_06_SPAMAX },	///< ネット		ボール
	{ SPA_P_BALL_07, P_BALL_07_SPAMAX },	///< ダイブ		ボール
	{ SPA_P_BALL_08, P_BALL_08_SPAMAX },	///< ネスト		ボール
	{ SPA_P_BALL_09, P_BALL_09_SPAMAX },	///< リピート	ボール
	{ SPA_P_BALL_10, P_BALL_10_SPAMAX },	///< タイマー	ボール
	{ SPA_P_BALL_11, P_BALL_11_SPAMAX },	///< ゴージャス	ボール
	{ SPA_P_BALL_12, P_BALL_12_SPAMAX },	///< プレミア	ボール
	{ SPA_P_BALL_13, P_BALL_13_SPAMAX },	///< ダーク		ボール
	{ SPA_P_BALL_14, P_BALL_14_SPAMAX },	///< ヒール		ボール
	{ SPA_P_BALL_15, P_BALL_15_SPAMAX },	///< クイック	ボール
	{ SPA_P_BALL_16, P_BALL_16_SPAMAX },	///< プレシャス	ボール
	{ SPA_P_BALL_17, P_BALL_17_SPAMAX },	///< パーク		ボール
	{ SPA_P_BALL_01, P_BALL_01_SPAMAX },	///< どろ		ボール
	{ SPA_P_BALL_01, P_BALL_01_SPAMAX },	///< エサ		ボール
	{ SPA_P_BACK,	 P_BACK_SPAMAX	  },	///< もどす
};

///< 捕獲パーティクル
static const int MonsterBall_Get_SPA_Table[][3] = {
	{ SPA_P_GET_01,	 P_GET_01_BALL_STAR1, P_GET_01_SPAMAX },	///< マスター	ボール
	{ SPA_P_GET_02,	 P_GET_02_BALL_STAR1, P_GET_02_SPAMAX },	///< ハイパー	ボール
	{ SPA_P_GET_03,	 P_GET_03_BALL_STAR1, P_GET_03_SPAMAX },	///< スーパー	ボール
	{ SPA_P_GET_04,	 P_GET_04_BALL_STAR1, P_GET_04_SPAMAX },	///< モンスター	ボール
	{ SPA_P_GET_05,	 P_GET_05_BALL_STAR1, P_GET_05_SPAMAX },	///< サファリ	ボール
	{ SPA_P_GET_06,	 P_GET_06_BALL_STAR1, P_GET_06_SPAMAX },	///< ネット		ボール
	{ SPA_P_GET_07,	 P_GET_07_BALL_STAR1, P_GET_07_SPAMAX },	///< ダイブ		ボール
	{ SPA_P_GET_08,	 P_GET_08_BALL_STAR1, P_GET_08_SPAMAX },	///< ネスト		ボール
	{ SPA_P_GET_09,	 P_GET_09_BALL_STAR1, P_GET_09_SPAMAX },	///< リピート	ボール
	{ SPA_P_GET_10,	 P_GET_10_BALL_STAR1, P_GET_10_SPAMAX },	///< タイマー	ボール
	{ SPA_P_GET_11,	 P_GET_11_BALL_STAR1, P_GET_11_SPAMAX },	///< ゴージャス	ボール
	{ SPA_P_GET_12,	 P_GET_12_BALL_STAR1, P_GET_12_SPAMAX },	///< プレミア	ボール
	{ SPA_P_GET_13,	 P_GET_13_BALL_STAR1, P_GET_13_SPAMAX },	///< ダーク		ボール
	{ SPA_P_GET_14,	 P_GET_14_BALL_STAR1, P_GET_14_SPAMAX },	///< ヒール		ボール
	{ SPA_P_GET_15,	 P_GET_15_BALL_STAR1, P_GET_15_SPAMAX },	///< クイック	ボール
	{ SPA_P_GET_16,	 P_GET_16_BALL_STAR1, P_GET_16_SPAMAX },	///< プレシャス	ボール
	{ SPA_P_GET_17,	 P_GET_17_BALL_STAR1, P_GET_17_SPAMAX },	///< パーク		ボール
	{ SPA_P_GET_01,	 P_GET_01_BALL_STAR1, P_GET_01_SPAMAX },	///< どろ		ボール
	{ SPA_P_GET_01,	 P_GET_01_BALL_STAR1, P_GET_01_SPAMAX },	///< エサ		ボール
	{ SPA_P_BACK,	 0xFF,				  P_BACK_SPAMAX	  },	///< もどす
};

#define BE_MONSTER_BALL_SPA_TBL_MAX		(sizeof(MonsterBall_SPA_Table))


//--------------------------------------------------------------
/**
 * @brief	ボールＩＤの取得
 *
 * @param	no	
 *
 * @retval	static int	
 *
 */
//--------------------------------------------------------------
static int DP_BallEffectID_Get(int no)
{
	int id;
	
	if (no < ITEM_MASUTAABOORU
	||	no > BALL_EFF_DP_END){			///< マスターボールより値が小さい DPボールより値が大きい
		id = ITEM_MONSUTAABOORU;
		
//		OS_Printf(">> BallID = %2d → %2d\n ･･･ 範囲外のボール値モンスターボールに補正\n", no, id);
	}
	else if (no >= BALL_EFF_EX_DP){		///< DP専用のボールＩＤ定義以上
		id = no - BALL_EFF_EX_DP;
		
//		OS_Printf(">> BallID = %2d → %2d\n ･･･ DP専用のボール値なので補正\n", no, id);
	}
	else {								///< その他 = 正常
		id = no;
		
//		OS_Printf(">> BallID = %2d → %2d\n ･･･ 正常なボール値\n", no, id);
	}

	return id - ITEM_MASUTAABOORU;
}

static BOOL MonsterBall_RollFlagGet(int type)
{
	int i;
	BOOL is_roll;
	
	int check[] = {
		EBMT_THROW_C,
		EBMT_THROW_R,
		EBMT_THROW_L,
		EBMT_THROW_E0,
		EBMT_THROW_E1,
		EBMT_THROW_E2,
		EBMT_THROW_E0_STONE,
		EBMT_THROW_E0_FOOD,
		EBMT_CAPTURE_BB,
		EBMT_CAPTURE_B,
		EBMT_CAPTURE_D,
	};
	
	is_roll = FALSE;
	
	for (i = 0; i < NELEMS(check); i++){
		
		if (check[i] != type){ continue; }
		
		is_roll = TRUE;
		break;
	}
	
	return is_roll;
}

static BOOL MonsterBall_FadeFlagGet(int type)
{
	int i;
	BOOL is_fade;
	
	int check[] = {
		EBMT_THROW_C,
		EBMT_THROW_R,
		EBMT_THROW_L,
		EBMT_THROW_E0,
		EBMT_THROW_E1,
		EBMT_THROW_E2,
	};
	
	is_fade = FALSE;
	
	for (i = 0; i < NELEMS(check); i++){
		
		if (check[i] != type){ continue; }
		
		is_fade = TRUE;
		break;
	}
	
	return is_fade;
}

static BOOL MonsterBall_AnimeFlagGet(int type)
{
	int i;
	BOOL is_anime;
	
	int check[] = {
		EBMT_STAY_B,
		EBMT_STAY_D,
		EBMT_STAY_BB,
	};
	
	is_anime = TRUE;
	
	for (i = 0; i < NELEMS(check); i++){
		
		if (check[i] != type){ continue; }
		
		is_anime = FALSE;
		break;
	}
	
	return is_anime;
}


static int MonsterBall_SPA_Get(int no)
{	
	int id;
	
	id = DP_BallEffectID_Get(no);
	
	return MonsterBall_SPA_Table[ id ][ 0 ];
}

static int MonsterBall_SPA_Max_Get(int no)
{
	int id;
	
	id = DP_BallEffectID_Get(no);
	
	return MonsterBall_SPA_Table[ id ][ 1 ];
}

static int MonsterBall_Get_SPA_Get(int no)
{
	int id;
	
	id = DP_BallEffectID_Get(no);
	
	return MonsterBall_Get_SPA_Table[ id ][ 0 ];
}

static int MonsterBall_Get_SPA_Max_Get(int no)
{
	int id;
	
	id = DP_BallEffectID_Get(no);
	
	return MonsterBall_Get_SPA_Table[ id ][ 2 ];
}

static int MonsterBall_Get_SPA_Star_Get(int no)
{
	int id;
	
	id = DP_BallEffectID_Get(no);
	
	return MonsterBall_Get_SPA_Table[ id ][ 1 ];
}

///< 0 = char 1 = pltt 2 = ncer 3 = ncnr
static int MonsterBall_Get_GRA_Get(int ball_id, int type)
{
	int id;
	
	id = DP_BallEffectID_Get(ball_id);
	
#if 0
	int id;
	
	id = ball_id - 1;	///< 1 ori → 0 ori
	
	if (id < 0){
		OS_Printf(" DPで定義されていないボールIDです \n");
		id = 3;
	}
	if (id >= 18){
		OS_Printf(" DPで定義されていないボールIDです \n");
		id = 3;
	}
#endif
	
	return MonsterBall_GRA_Table[ id ][ type ];
}

typedef struct {

	int 		ptc_id;
	int			wait;
	int			client_type;
	
	BOOL*		active;
		
	PTC_PTR		ptc;
	CB_SEAL*	seal;
	pEmitFunc	call_back;
	
} BE_TIMER_SYS;


// -----------------------------------------
//
//	■ボールエフェクト用構造体
//
// -----------------------------------------
typedef struct _TBALL_EFFECT_SYS {
	
	int			heap_area;			///< ヒープエリア
	
	TBALL_CUSTOM_PARAM	bcp;		///< ボールカスタマイズパラメータ
	
	int			ptc_num;			///< 動いているptcの数
	PTC_PTR		ptc[9];				///< パーティクルのポインタ
	CB_SEAL*	seal[9];			///< 加工用
	BOOL		ptc_active[9];		///< 
	
	EMIT_PTR	emit;				///< エミッターのポインタ
	
	TCB_PTR		tcb;				///< TCB のポインタ
	
	BOOL		active;				///< 生存チェック
	
	ARCHANDLE*	arc_h;				///< アーカイブハンドル
	int			load_seq;
	
	/// ----------
	int			eff_type;			///< effectタイプ
	int			get_ball;			///< 捕獲ボール
	int			cb_id;				///< カスタマイズID
	CB_CORE		core;				///< 編集コアデータ

} TBALL_EFFECT_SYS;

static PTC_PTR	d_ptc = NULL;
// =============================================================================
//
//
//	■プロトタイプ
//
//
// =============================================================================
static void BallEffect_MainTCB(TCB_PTR tcb, void* work);
static void BallEffect_ParticleSet(BES_PTR bes, pEmitFunc callback);
static void BallEffect_CallBack(EMIT_PTR emit);
static void BallEffect_CallBack_Custom(EMIT_PTR emit);

static void CBTool_InitVelocityGet(fx16* i_velo, fx16 n_velo, int n_per, f32 m_per);
static void CBTool_InitPosRandGet(f32* p, u16 rnd, f32 param);
static s8 CBTool_SignGet(void);


// =============================================================================
//
//
//	■外部参照関数郡
//
//
// =============================================================================
//--------------------------------------------------------------
/**
 * @brief	パラメーター無し初期化
 *
 * @param	heap_area			ヒープID
 *
 * @retval	BES_PTR	
 *
 */
//--------------------------------------------------------------
BES_PTR BallEffect_InitEz(int heap_area)
{
	TBALL_EFFECT_SYS* bes = NULL;
	
	bes = sys_AllocMemory(heap_area, sizeof(TBALL_EFFECT_SYS));
	
	if (bes == NULL){
		GF_ASSERT(0);
		return NULL;
	}
	
	bes->heap_area = heap_area;
	bes->active	   = FALSE;
	
	return bes;
}


//--------------------------------------------------------------
/**
 * @brief	パラメーターありエフェクトの初期化
 *
 * @param	heap_area	
 * @param	bip	
 *
 * @retval	BES_PTR	
 *
 */
//--------------------------------------------------------------
BES_PTR BallEffect_Init(int heap_area, const TBALL_CUSTOM_PARAM* bcp)
{
	TBALL_EFFECT_SYS* bes = NULL;
	
//	DefaultBlendSet();
	
	bes = BallEffect_InitEz(heap_area);
	
	BallEffect_ParamSet(bes, bcp);
	
	{
		int i;
		
		bes->ptc_num = 0;
		
		for (i = 0; i < 9; i++){
			bes->ptc[i] = NULL;
			bes->seal[i] = NULL;
			bes->ptc_active[i] = FALSE;
		}
	}
		

	return bes;
}


//--------------------------------------------------------------
/**
 * @brief	エフェクトのパラメーター設定
 *
 * @param	bes	
 * @param	bip	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void BallEffect_ParamSet(BES_PTR bes, const TBALL_CUSTOM_PARAM* bcp)
{
	bes->bcp = *bcp;

#ifdef	PM_DEBUG	
//	Debug_CB_Set(bes->bcp.pp);
#endif
	
	bes->cb_id = PokeParaGet(bes->bcp.pp, ID_PARA_cb_id, NULL);
	
	GF_ASSERT(bes->cb_id < CB_DEF_CORE_MAX + 1);
		
	if (bes->cb_id == 0){		///< カスタムボールIDが指定されてない

		bes->eff_type = BE_EFF_MONSTAR_BALL;
		
		if (bes->bcp.ball_id != 0){
			bes->get_ball = bes->bcp.ball_id;
		}
		else {
			bes->get_ball = PokeParaGet(bes->bcp.pp, ID_PARA_get_ball, NULL);
		}
		
	}
	else {						///< カスタムボールIDが指定されている

		bes->eff_type = BE_EFF_CUSTOM_BALL;
		PokeParaGet(bes->bcp.pp, ID_PARA_cb_core, &bes->core);
	}
}


//--------------------------------------------------------------
/**
 * @brief	リソース読み込み専用TCB
 *
 * @param	tcb	
 * @param	work	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void BE_ResLoadTCB(TCB_PTR tcb, void* work)
{
	BES_PTR bes = work;
	int i;
	int	id;
	int	pt_id;	
	int spa_id;
	CB_SEAL* seal;
		
	switch(bes->load_seq){
	case 0:
		///< 前半４個を読み込む
		bes->arc_h = ArchiveDataHandleOpen( ARC_BALL_PARTICLE, bes->heap_area );
		for (i = 0; i < 2; i++){
			seal = CB_SaveData_SealDataGet(&bes->core, i);
			
			if (seal == NULL){ continue; }

			id = CB_SaveData_SealIDGet(seal);

			if (id == 0){ continue; }
			if (id >= CB_DEF_ITEM_DATA_NUM){ continue; }
						
			pt_id = Seal_EffectGet(id);
			
			bes->seal[bes->ptc_num] = seal;
			
			GF_ASSERT(bes->ptc[bes->ptc_num] == NULL);
			
			bes->ptc[bes->ptc_num]	= Wp_InitEx_CBAH(bes->arc_h, bes->heap_area, pt_id, FALSE);
			
			GF_ASSERT(bes->ptc[bes->ptc_num] != NULL);
			
			bes->ptc_num++;
		}
		bes->load_seq++;
		break;
		
	case 1:
		///< 前半４個を読み込む
		for (i = 2; i < 4; i++){
			seal = CB_SaveData_SealDataGet(&bes->core, i);
			
			if (seal == NULL){ continue; }

			id = CB_SaveData_SealIDGet(seal);

			if (id == 0){ continue; }
			if (id >= CB_DEF_ITEM_DATA_NUM){ continue; }
						
			pt_id = Seal_EffectGet(id);
			
			bes->seal[bes->ptc_num] = seal;
			
			GF_ASSERT(bes->ptc[bes->ptc_num] == NULL);
			
			bes->ptc[bes->ptc_num]	= Wp_InitEx_CBAH(bes->arc_h, bes->heap_area, pt_id, FALSE);
			
			GF_ASSERT(bes->ptc[bes->ptc_num] != NULL);
			
			bes->ptc_num++;
		}
		bes->load_seq++;
		break;
		
	case 2:
		///< 前半４個を読み込む
		for (i = 4; i < 6; i++){
			seal = CB_SaveData_SealDataGet(&bes->core, i);
			
			if (seal == NULL){ continue; }

			id = CB_SaveData_SealIDGet(seal);

			if (id == 0){ continue; }
			if (id >= CB_DEF_ITEM_DATA_NUM){ continue; }
						
			pt_id = Seal_EffectGet(id);
			
			bes->seal[bes->ptc_num] = seal;
			
			GF_ASSERT(bes->ptc[bes->ptc_num] == NULL);
			
			bes->ptc[bes->ptc_num]	= Wp_InitEx_CBAH(bes->arc_h, bes->heap_area, pt_id, FALSE);
			
			GF_ASSERT(bes->ptc[bes->ptc_num] != NULL);
			
			bes->ptc_num++;
		}
		bes->load_seq++;
		break;
		
	case 3:
		///< 後半４個を読み込む
		for (i = 6; i < CB_DEF_SEAL_MAX; i++){
			seal = CB_SaveData_SealDataGet(&bes->core, i);
			
			if (seal == NULL){ continue; }

			id = CB_SaveData_SealIDGet(seal);

			if (id == 0){ continue; }
			if (id >= CB_DEF_ITEM_DATA_NUM){ continue; }
						
			pt_id = Seal_EffectGet(id);
			
			bes->seal[bes->ptc_num] = seal;
			
			GF_ASSERT(bes->ptc[bes->ptc_num] == NULL);
			
			bes->ptc[bes->ptc_num]	= Wp_InitEx_CBAH(bes->arc_h, bes->heap_area, pt_id, FALSE);
			
			GF_ASSERT(bes->ptc[bes->ptc_num] != NULL);
			
			bes->ptc_num++;
		}
		bes->load_seq = LOAD_SEQ_END;
		ArchiveDataHandleClose( bes->arc_h );
		TCB_Delete(tcb);
		break;
	default:
		break;
	}
}

//--------------------------------------------------------------
/**
 * @brief	リソースの読み込み
 *
 * @param	bes	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void BallEffect_ResourceLoad(BES_PTR bes)
{
	int i;
	int	id;
	int	pt_id;	
	int spa_id;
	CB_SEAL* seal;

	if (bes->eff_type == BE_EFF_MONSTAR_BALL){
		
		///< 通常のモンスターボール
		spa_id = MonsterBall_SPA_Get(bes->get_ball);
		bes->ptc_num = 1;
		bes->ptc[0] = Wp_InitEx(bes->heap_area, ARC_BALL_PARTICLE, spa_id, FALSE);	
	}
	else {
		
		///< カスタムボール
		bes->ptc_num = 0;
		
	#ifdef LOAD_SEQ_SEP
	
		///< 分割タスク
		bes->load_seq = 0;
		{
			TCB_PTR tcb;
			
			tcb = TCB_Add(BE_ResLoadTCB, bes, TCBPRI_BALL_EFFECT);
			
			BE_ResLoadTCB(tcb, bes);
		}
	
	#else
		bes->load_seq = LOAD_SEQ_END;
		
		bes->arc_h = ArchiveDataHandleOpen( ARC_BALL_PARTICLE, bes->heap_area );

		for (i = 0; i < CB_DEF_SEAL_MAX; i++){
			seal = CB_SaveData_SealDataGet(&bes->core, i);
			
			if (seal == NULL){ continue; }

			id = CB_SaveData_SealIDGet(seal);

			if (id == 0){ continue; }
			if (id >= CB_DEF_ITEM_DATA_NUM){ continue; }
						
			pt_id = Seal_EffectGet(id);
			
			bes->seal[bes->ptc_num] = seal;
			
			GF_ASSERT(bes->ptc[bes->ptc_num] == NULL);
			
			bes->ptc[bes->ptc_num]	= Wp_InitEx_CBAH(bes->arc_h, bes->heap_area, pt_id, FALSE);
			
			GF_ASSERT(bes->ptc[bes->ptc_num] != NULL);
			
			bes->ptc_num++;
		}
		
		ArchiveDataHandleClose( bes->arc_h );
		
	#endif
	}
}


//--------------------------------------------------------------
/**
 * @brief	分割読み込み終了チェック
 *
 * @param	bes	
 *
 * @retval	BOOL	
 *
 */
//--------------------------------------------------------------
BOOL BallEffect_IsLoadEnd(BES_PTR bes)
{
#ifdef LOAD_SEQ_SEP
	
	return TRUE;
	
#else
	
	if (bes->load_seq == LOAD_SEQ_END){
		
		return TRUE;
		
	}
	
	return FALSE

#endif
}

//--------------------------------------------------------------
/**
 * @brief	ボール登録
 *
 * @param	bes	
 * @param	callback	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void BallEffect_Executed(BES_PTR bes, pEmitFunc callback)
{
	bes->active = TRUE;
	
	DefaultBlendSet();
	
	BallEffect_ParticleSet(bes, callback);
	
	bes->tcb = TCB_Add(BallEffect_MainTCB, bes, TCBPRI_BALL_EFFECT);
}


//--------------------------------------------------------------
/**
 * @brief	
 *
 * @param	bes	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void BallEffect_ExecutedEz(BES_PTR bes)
{
	BallEffect_Executed(bes, BallEffect_CallBack);
}

//--------------------------------------------------------------
/**
 * @brief	終了チェック
 *
 * @param	bes	
 *
 * @retval	BOOL	
 *
 */
//--------------------------------------------------------------
BOOL BallEffect_EndCheck(BES_PTR bes)
{
	return bes->active;
}


//--------------------------------------------------------------
/**
 * @brief	メインタスク
 *
 * @param	tcb	
 * @param	work	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void BallEffect_MainTCB(TCB_PTR tcb, void* work)
{
	int i;
	BOOL bFlag;
	BES_PTR wk = (BES_PTR)work;
		
	bFlag = FALSE;
	
	GF_ASSERT(wk->ptc_num <= 9);
	
	for (i = 0; i < wk->ptc_num; i++){

		if (wk->ptc[i] == NULL){ continue; }
		
		if (Particle_GetEmitterNum(wk->ptc[i]) == 0
		&&	wk->ptc_active[i] != FALSE){
			Wp_Exit(wk->ptc[i]);
			wk->ptc[i] = NULL;
			wk->ptc_active[i] = FALSE;
			continue;
		}
		bFlag = TRUE;
	}

	if (bFlag == FALSE){
		wk->active = FALSE;
		TCB_Delete(tcb);
	}
}


//--------------------------------------------------------------
/**
 * @brief	ボール用メモリ解放
 *
 * @param	bes	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void BallEffect_FreeMemory(BES_PTR bes)
{
	sys_FreeMemoryEz(bes); ///< BES_PTR
}



// =============================================================================
//
//
//	■内部参照関数郡
//
//
// =============================================================================
static void BallEffect_TimerTCB(TCB_PTR tcb, void* work)
{
	BE_TIMER_SYS* wk = (BE_TIMER_SYS*)work;
	
	if (wk->wait == 0){
		*(wk->active) = TRUE;
		Particle_CreateEmitterCallback(wk->ptc, 0, wk->call_back, wk);
		Particle_CameraTypeSet(wk->ptc, GF_CAMERA_ORTHO);
		TCB_Delete(tcb);
		sys_FreeMemoryEz(wk);
	}
	else {
		wk->wait--;
	}
}

//--------------------------------------------------------------
/**
 * @brief	エフェクトの登録
 *
 * @param	bes	
 * @param	callback	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void BallEffect_ParticleSet(BES_PTR bes, pEmitFunc callback)
{
	int i,j;
	int spa_id;
	int spa_max;
	
	if (bes->eff_type == BE_EFF_MONSTAR_BALL){
		
		spa_max	= MonsterBall_SPA_Max_Get( bes->get_ball );
		
		for (i = 0; i < spa_max; i++){
			Particle_CreateEmitterCallback(bes->ptc[0], i, callback, bes);
		}
		bes->ptc_active[0] = TRUE;
		Particle_CameraTypeSet(bes->ptc[0], GF_CAMERA_ORTHO);
	}
	else {
		for (i = 0; i < bes->ptc_num; i++){

			BE_TIMER_SYS* wk = sys_AllocMemory(bes->heap_area, sizeof(BE_TIMER_SYS));
			
			GF_ASSERT(wk != NULL);
			
			wk->ptc_id = i;
			wk->client_type = bes->bcp.client_type;
			wk->call_back = BallEffect_CallBack_Custom;
			
			bes->ptc_active[i] = FALSE;
			wk->active = &bes->ptc_active[i];
			
			wk->ptc  = bes->ptc[i];
			wk->seal = bes->seal[i];
			
			GF_ASSERT(wk->seal != NULL);
			
			wk->wait = BET_Seal_RangeWaitGet(wk->seal);
			
			TCB_Add(BallEffect_TimerTCB, wk, 1001);
		}	
	}
}

extern void DebugParticle_EmitMove(PTC_PTR ptc, EMIT_PTR emit, const VecFx32 *vec);


//--------------------------------------------------------------
/**
 * @brief	エミッタの座標設定
 *
 * @param	client_type	
 * @param	pos	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void BallEffect_EmitPosOfsGet(int client_type, VecFx32* pos)
{		
	WET_PokeParticlePosGet_CT(client_type, pos, FALSE, GF_CAMERA_ORTHO);
	
	///< 座標補正
	{
		int x;
		int y;
		s16 ox;
		s16 oy;
		VecFx32 ofs;
		
		switch(client_type){
		case CLIENT_TYPE_AA:
			ox = 0;
			oy = -16;
			break;
		case CLIENT_TYPE_BB:
			ox = -15;
			oy = -25;
			break;
		case CLIENT_TYPE_A:
			ox = -8;
			oy = -12;
			break;
		case CLIENT_TYPE_B:
			ox = -14;		///< -なら右へ（なぜか最後にひいてるから）
			oy = -25;
			break;
		case CLIENT_TYPE_C:
			ox = -8;
			oy = -12;
			break;
		case CLIENT_TYPE_D:
		default:
			ox = -16;
			oy = -29;
			break;
		}
	
		x = PT_LCD_DOT * (BMT_START_POS_OFS_X + ox);
		y = PT_LCD_DOT * (BMT_START_POS_OFS_Y + oy);
		VEC_Set(&ofs, x, y, 0);
		pos->x -= ofs.x;
		pos->y -= ofs.y;
	}
}

//--------------------------------------------------------------
/**
 * @brief	コールバック関数･･･パラメータの反映など
 *
 * @param	emit	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void BallEffect_CallBack(EMIT_PTR emit)
{
	int client_type;
	BES_PTR bes;
	
	bes = Particle_GetTempPtr();
	
	client_type = bes->bcp.client_type;
	
	{
		VecFx32 pos;
		
		BallEffect_EmitPosOfsGet(client_type, &pos);
		
		SPL_SetEmitterPosition(emit, &pos);
	}
}
#define BE_CUSTOM_Y_OFS		(+30)
#define BE_CUSTOM_A_TYPE	(2)
static void BallEffect_CallBack_Custom(EMIT_PTR emit)
{
	VecFx32 pos;
	int client_type;
	BES_PTR bes;
	BE_TIMER_SYS* wk;
	
	wk  = Particle_GetTempPtr();
	
	client_type = wk->client_type;
	
	{		
		BallEffect_EmitPosOfsGet(client_type, &pos);
	}
	{
		///< オフセット
		u8  id;
		u8	x, y;
		s16 ox, oy;
		int px, py;
		VecFx32 ofs;
		
		id = CB_SaveData_SealIDGet(wk->seal);
		
		if (Seal_TypeGet(id) == CB_SEAL_TYPE_B){
			
			x = CB_SaveData_SealPXGet(wk->seal);
			y = CB_SaveData_SealPYGet(wk->seal);
			
			ox = (x - SEAL_DEF_POS_X);
			oy = (SEAL_DEF_POS_Y - y + BE_CUSTOM_Y_OFS);
			
			px = ox * PT_LCD_DOT;
			py = oy * PT_LCD_DOT;
			
			VEC_Set(&ofs, px, py, 0);
		
			pos.x += ofs.x;
			pos.y += ofs.y;
			pos.z += ofs.z;
		}
		else {
			
			x = CB_SaveData_SealPXGet(wk->seal);
			y = CB_SaveData_SealPYGet(wk->seal);
			
			ox = (x - SEAL_DEF_POS_X);
			oy = (SEAL_DEF_POS_Y - y + BE_CUSTOM_Y_OFS);
			
			px = ox * PT_LCD_DOT;
			py = oy * PT_LCD_DOT;
			
			VEC_Set(&ofs, px, py, 0);
		
			pos.x += ofs.x;
			pos.y += ofs.y;
			pos.z += ofs.z;
		}
	}
		
	SPL_SetEmitterPosition(emit, &pos);
}

// -----------------------------------------
//
//	コールバックの補助関数
//
// -----------------------------------------
static void CBTool_InitVelocityGet(fx16* i_velo, fx16 n_velo, int n_per, f32 m_per)
{
	f32 per;
	f32 temp;
	
	per = (f32)(n_per / m_per);
	
	temp = FX_FX16_TO_F32(n_velo);
	temp *= per;
	
	*i_velo = FX_F32_TO_FX16(temp);
}


//--------------------------------------------------------------
/**
 * @brief	座標設定関数
 *
 * @param	p	
 * @param	rnd	
 * @param	param	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void CBTool_InitPosRandGet(f32* p, u16 rnd, f32 param)
{
	u16 rand;
	f32 pos;
	
	rand = gf_rand();
	rand %= rnd;
	rand++;
	
	pos = rand;
	pos /= param;
	
	*p = pos;	
}


//--------------------------------------------------------------
/**
 * @brief	符号設定関数
 *
 * @param	none	
 *
 * @retval	s8	
 *
 */
//--------------------------------------------------------------
static s8 CBTool_SignGet(void)
{
	u16 rand;
	
	rand = gf_rand();
	
	if (rand % 2){
		return +1;
	}
	else {
		return -1;
	}
}




// =============================================================================
//
//
//	■inline関数
//
//
// =============================================================================
//--------------------------------------------------------------
/**
 * @brief	int型の加減算
 *
 * @param	param	
 * @param	data	
 * @param	min	
 * @param	max	
 *
 * @retval	none
 *
 */
//--------------------------------------------------------------
static inline void BE_IntParamSet_inline(int* param, s16 data, int min, int max)
{
	if (data > 0){
		*param += data;
		*param %= max;
	}
	else if (data < 0){
		if (*param + data < min){
			*param = max + data;
		}
		else {
			*param += data;
		}
	}
}


//--------------------------------------------------------------
/**
 * @brief	fx32型の加減算
 *
 * @param	param	
 * @param	data	
 * @param	min	
 * @param	max	
 *
 * @retval	none
 *
 */
//--------------------------------------------------------------
static inline void BE_Fx32ParamSet_inline(fx32* param, fx32 data, fx32 min, fx32 max)
{
	if (data > 0){
		if (*param + data < max){
			*param += data;
		}
		else {
			*param = (*param + data) - max;
		}
	}
	else if (data < 0){
		if (*param + data < min){
			*param = max + data;
		}
		else {
			*param += data;
		}
	}
}






// =============================================================================
//
//
//	■簡単Ver
//
//
// =============================================================================
typedef struct _TSP_BALL_SYS {
	
	TSP_BALL_PARAM	param;
	
	EMIT_PTR		emit;
	PTC_PTR			ptc;
	
	int				spa_max;
	int				ball_id;
	
} TSP_BALL_SYS;

static void SP_Ball_CallBack(EMIT_PTR emit)
{
	SPB_PTR wk = Particle_GetTempPtr();
	
	{
		VecFx32 pos;
		int px, py;
		s16 ox, oy;
	
		ox = (wk->param.x - SEAL_DEF_POS_X + 61);
		oy = (SEAL_DEF_POS_Y - wk->param.y + BE_CUSTOM_Y_OFS);
		
		px = ox * PT_LCD_DOT;
		py = oy * PT_LCD_DOT;
		
		VEC_Set(&pos, px, py, 0);
		
		SPL_SetEmitterPosition(emit, &pos);
	}
}

SPB_PTR	SPB_Init(TSP_BALL_PARAM* param)
{
	SPB_PTR wk;
	
	wk = sys_AllocMemory(param->heap_id, sizeof(TSP_BALL_SYS));
	
	GF_ASSERT(wk != NULL);
	
	wk->param = *param;
	
	if (wk->param.close_only){
		wk->ball_id = MonsterBall_Get_SPA_Get(BALL_EFF_BACK);
		wk->spa_max = MonsterBall_Get_SPA_Max_Get(BALL_EFF_BACK);
	}
	else {
		wk->ball_id = MonsterBall_Get_SPA_Get(wk->param.ball_id);
		wk->spa_max = MonsterBall_Get_SPA_Max_Get(wk->param.ball_id);
	}
	
	wk->ptc	= Wp_InitEx(wk->param.heap_id, ARC_BALL_PARTICLE, wk->ball_id, FALSE);
	
	return wk;
}

void SPB_Load(SPB_PTR spb)
{
	int i;
	int set_id;
	
	SPB_PTR wk = spb;

	if (wk->param.set_id == ALL_DATA_SET){
		
		if (wk->param.close_only){
		
			for (i = 0; i < wk->spa_max; i++){
				
				Particle_CreateEmitterCallback(wk->ptc, i, SP_Ball_CallBack, wk);
				
			}
			
		}
		else {
				
			for (i = 0; i < wk->spa_max; i++){
				
				///< 星はこの時点で出さない
				if (i == MonsterBall_Get_SPA_Star_Get(wk->param.ball_id)){ continue; }
				
				Particle_CreateEmitterCallback(wk->ptc, i, SP_Ball_CallBack, wk);
			}
		}
				
	}
	else {
		
		set_id = wk->param.set_id;
		
		Particle_CreateEmitterCallback(wk->ptc, set_id, SP_Ball_CallBack, wk);
		
	}
	
	Particle_CameraTypeSet(wk->ptc, GF_CAMERA_ORTHO);	
}

BOOL SPB_Main(SPB_PTR spb)
{
	SPB_PTR wk = spb;
	
	if (Particle_GetEmitterNum(wk->ptc) == 0){
		Wp_Exit(wk->ptc);
		return FALSE;
	}
	
	return TRUE;
}

void SPB_End(SPB_PTR spb)
{
	sys_FreeMemoryEz(spb);
}

















#include "wazatool.h"
// =============================================================================
//
//
//	■
//
//
// =============================================================================
typedef struct {
	
	s16 sx;
	s16 sy;
	s16 ex;
	s16 ey;
	
	int time;
	int time_stop;
	int height;
	
} TBALL_THROW_PARAM;

typedef struct _TBALL_MOVE_SYS {
	
	// -----
	
	int scene;			///< 状況より上の部分でシーンを管理する
	int scene_seq;		///< シーンの中のシーケンスを管理
	
	// -----
	
	int seq;
	int	cnt;
	int flg;
	int	state;			///< ボールの動作動作を取得する
	
	int roll_num;		///< 転がっている回数 1回目 = 0
	
	BOOL active;
	
	u8	eva;
	u8	evb;
	s8	vec_r;
	
	BOOL anime_flag;	///< アニメフラグ
	BOOL open;
	
	CATS_RES_PTR	crp;
	CATS_ACT_PTR	cap;
	
	WAZATOOL_CALCMOVE_ONE	cmo;
	WAZATOOL_CALCMOVE		cm[2];
	TBALL_MOVE_DATA			bmd;
	
	TBALL_THROW_PARAM	tp;
	
	TCB_PTR	tcb;
	
	SPB_PTR	spb;
	
	PAL_SFS_PTR	psp;
	
	OAM_DROP_SYS* ods;
	
	int ex_wait;
} TBALL_MOVE_SYS;

#define BT_OBJ_NUM	(10)
#define BT_RES_NUM	(10)

// -----------------------------------------
//
//	ツール関連
//
// -----------------------------------------
static void BMT_ClactInit(BMS_PTR bms);
static void BMT_ClactAdd(BMS_PTR bms);
static void BMT_BallParaSet(BMS_PTR bms);
static void BMT_StartPosSet(BMS_PTR bms, s16* x, s16* y);

// -----------------------------------------
//
//	TCB関連
//
// -----------------------------------------
static BOOL BM_Throw(BMS_PTR bms);
static BOOL BM_Failure(BMS_PTR bms);
static BOOL BM_Shake(BMS_PTR bms);
static BOOL BM_Capture(BMS_PTR bms);
static BOOL BM_Free(BMS_PTR bms);
static BOOL BM_Close(BMS_PTR bms);

static BOOL (* const BM_TcbTable[])(BMS_PTR wk) = {
	BM_Throw,
	BM_Failure,
	BM_Shake,
	BM_Capture,
	BM_Free,
	BM_Close,
};

static BOOL Scene_Capture_01(BMS_PTR bms)
{
	BOOL active;
	
	if (bms->scene_seq == 0){
		bms->scene_seq++;
		BM_CaptureStateSet(bms, EBMS_THROW);
	}		
	
	active = BM_IsCaptureStateEnd(bms, EBMS_THROW_END);
	
	if (active == TRUE){
		return FALSE;
	}
	
	return TRUE;
}

static BOOL Scene_Capture_01_A(BMS_PTR bms)
{
	BOOL active;
	
	if (bms->scene_seq == 0){
		bms->scene_seq++;
		BM_CaptureStateSet(bms, EBMS_OPEN);
	}		
	
	active = BM_IsCaptureStateEnd(bms, EBMS_OPEN_END);
	
	if (active == TRUE){
		return FALSE;
	}
	
	return TRUE;
}

static BOOL Scene_Capture_01_B(BMS_PTR bms)
{
	BOOL active;
	
	if (bms->scene_seq == 0){
		bms->scene_seq++;
		BM_CaptureStateSet(bms, EBMS_SHED);
	}		
	
	active = BM_IsCaptureStateEnd(bms, EBMS_SHED_END);
	
	if (active == TRUE){
		return FALSE;
	}
	
	return TRUE;
}

static BOOL Scene_Capture_02(BMS_PTR bms)
{
	BOOL active;
	
	if (bms->scene_seq == 0){
		bms->scene_seq++;
		BM_CaptureStateSet(bms, EBMS_CLOSE);
	}
	
	active = BM_IsCaptureStateEnd(bms, EBMS_BOUNCE_END);
	
	if (active == TRUE){
		return FALSE;
	}
	
	return TRUE;
}

static BOOL Scene_Capture_03(BMS_PTR bms)
{
	BOOL active;
	
	if (bms->scene_seq == 0){
		bms->scene_seq++;
		BM_CaptureStateSet(bms, EBMS_STOP);
	}
	
	active = BM_IsCaptureStateEnd(bms, EBMS_ROLL_END);
	
	if (active == TRUE){
		return FALSE;
	}
	
	return TRUE;
}

static BOOL Scene_Capture_04(BMS_PTR bms)
{
	BOOL active;
	
	if (bms->scene_seq == 0){
		bms->scene_seq++;
		BM_CaptureStateSet(bms, EBMS_FAILURE);
	}
	
	active = BM_IsCaptureStateEnd(bms, EBMS_END);
	
	if (active == TRUE){
		return FALSE;
	}
	
	return TRUE;
}

static BOOL Scene_Capture_05(BMS_PTR bms)
{
	BOOL active;
	
	if (bms->scene_seq == 0){
		bms->scene_seq++;
		BM_CaptureStateSet(bms, EBMS_SUCCESS_1);
	}
	
	active = BM_IsCaptureStateEnd(bms, EBMS_SUCCESS_1_END);
	
	if (active == TRUE){
		return FALSE;
	}
	
	return TRUE;
}

static BOOL Scene_Capture_05_A(BMS_PTR bms)
{
	BOOL active;
	
	if (bms->scene_seq == 0){
		bms->scene_seq++;
		BM_CaptureStateSet(bms, EBMS_SUCCESS_2);
	}
	
	active = BM_IsCaptureStateEnd(bms, EBMS_END);
	
	if (active == TRUE){
		return FALSE;
	}
	
	return TRUE;
}

static BOOL (* const BM_SceneTable[])(BMS_PTR wk) = {
	Scene_Capture_01,
	Scene_Capture_01_A,
	Scene_Capture_01_B,
	Scene_Capture_02,
	Scene_Capture_03,
	Scene_Capture_04,
	Scene_Capture_05,
	Scene_Capture_05_A
};

void BM_SceneSet(BMS_PTR bms, int scene)
{
	bms->scene = scene;
	bms->scene_seq = 0;
}

BOOL BM_SceneStateGet(BMS_PTR bms, int scene)
{
	BOOL active;
	
	active = BM_SceneTable[ bms->scene ](bms);
	
	return active;	
}


static void Capture_StateChange(BMS_PTR bms, int state)
{
	bms->state	= state;
	bms->seq	= 0;
	bms->cnt	= 0;
	bms->flg	= 0;
}

// ------------------
//
//	コントロールを外で行なうため
//
// ------------------
//#define BM_CAPTURE_AUTO_CONTROL

///< 開始
static BOOL Capture_Start(BMS_PTR bms)
{
	
#ifdef BM_CAPTURE_AUTO_CONTROL
	Capture_StateChange(bms, EBMS_THROW);
#endif

	return TRUE;
}

///< 投げる
static BOOL Capture_Throw(BMS_PTR bms)
{
	BOOL active;
	
	active = BM_Throw(bms);
	
	if (active == FALSE){
		Capture_StateChange(bms, EBMS_THROW_END);
	}
	
	return TRUE;
}

///< 投げ終わり
static BOOL Capture_Throw_End(BMS_PTR bms)
{	
	Capture_StateChange(bms, EBMS_OPEN);
	
	return TRUE;
}

///< 開く
static BOOL Capture_Open(BMS_PTR bms)
{	

	switch(bms->seq){
	case 0:
		CATS_ObjectAnimeSeqSetCap(bms->cap, EBM_ANM_OPEN);
		{
			TSP_BALL_PARAM para;
			
			para.ball_id = bms->bmd.ball_id;
			para.heap_id = bms->bmd.heap_id;
			para.set_id	 = ALL_DATA_SET;
			para.close_only = 0;
			CATS_ObjectPosGetCap(bms->cap, &para.x, &para.y);
			bms->ods = OAM_DropAll_Init(bms->bmd.bw, bms->bmd.heap_id);	///< OAM DROP
			bms->spb = SPB_Init(&para);
		}	
		bms->seq++;
		break;
	
	case 1:
		{
			int frame = CATS_ObjectAnimeFrameGetCap(bms->cap);
			
			if (frame >= 2){
				bms->anime_flag = FALSE;
				bms->seq++;
			}
		}		
		break;
	
	case 2:
		SPB_Load(bms->spb);	
		OAM_DropAll_End(bms->ods);										///< OAM DROP
		bms->seq++;
		break;
		
	case 3:	
		{
			if (SPB_Main(bms->spb) == FALSE){
				CATS_ObjectAnimeFrameSetCap(bms->cap, 0);
				SPB_End(bms->spb);
				bms->seq++;
			}
		}
		break;
	
	default:
		Capture_StateChange(bms, EBMS_OPEN_END);
		break;
	}
	
	return TRUE;
}
static BOOL Capture_Open_End(BMS_PTR bms)
{	
#ifdef BM_CAPTURE_AUTO_CONTROL
	Capture_StateChange(bms, EBMS_CLOSE);
#endif
	return TRUE;
}


///< 弾き
static BOOL Capture_Shed(BMS_PTR bms)
{
	BOOL active;
	
	switch(bms->cnt){
	case 0:
		CATS_ObjectPosGetCap(bms->cap, &bms->tp.sx, &bms->tp.sy);
		bms->tp.ex	   = 60;
		bms->tp.ey	   = 180;
		bms->tp.time   = 10;
		bms->tp.height = 12;
		bms->cnt++;
		break;
	default:
		{
			active = BM_Throw(bms);
	
			if (active == FALSE){
				Capture_StateChange(bms, EBMS_SHED_END);
			}
		}
		break;
	}
	
	return TRUE;
}

///< 弾き
static BOOL Capture_Shed_End(BMS_PTR bms)
{	
//	Capture_StateChange(bms, EBMS_OPEN);
	
	return TRUE;
}

///< 閉じる
static BOOL Capture_Close(BMS_PTR bms)
{	
	Capture_StateChange(bms, EBMS_CLOSE_END);

	return TRUE;
}

static BOOL Capture_Close_End(BMS_PTR bms)
{
	Capture_StateChange(bms, EBMS_FLASH);

	return TRUE;
}


static BOOL Capture_Flash(BMS_PTR bms)
{	
	switch(bms->seq){
	case 0:
		///< 光る
		{
			int pal_ofs;
			
			pal_ofs = CATS_ObjectPaletteOffsetGetCap(bms->cap);
			
			PaletteFadeReq(bms->bmd.pfd, PF_BIT_MAIN_OBJ, 1 << pal_ofs, BM_FADE_FLASH_SPD, 0, BM_FADE_FLASH_PARA, BM_FADE_FLASH);
			
			bms->seq++;
		}
		break;
	
	case 1:
		///< 光り終わりまち
		if (PaletteFadeCheck(bms->bmd.pfd) != 0){ break; }
		
		{
			int pal_ofs;
			
			pal_ofs = CATS_ObjectPaletteOffsetGetCap(bms->cap);
			
			PaletteFadeReq(bms->bmd.pfd, PF_BIT_MAIN_OBJ, 1 << pal_ofs, BM_FADE_FLASH_SPD, BM_FADE_FLASH_PARA, 0, BM_FADE_FLASH);
		}
		
		bms->seq++;
		break;
	
	default:
		if (PaletteFadeCheck(bms->bmd.pfd) != 0){ break; }
		
		Capture_StateChange(bms, EBMS_FLASH_END);
		break;
	}
		
	return TRUE;
}
static BOOL Capture_Flash_End(BMS_PTR bms)
{	
	Capture_StateChange(bms, EBMS_FALL);
	
	return TRUE;
}

static BOOL Capture_Fall(BMS_PTR bms)
{	
	switch(bms->seq){
	case 0:
		if ((++bms->cnt) < BM_FALL_WAIT ){ break; }
		
		{
			s16 x, y;
			
			CATS_ObjectPosGetCap(bms->cap, &x, &y);
			
			WazaTool_InitStraightSyncFx(&bms->cm[0],
										 x, x, y, y + 32, 32 / 3);
			bms->seq++;
		}
		break;
	
	case 1:
	
		if (WazaTool_CalcAndReflectStraightFxCap(&bms->cm[0], bms->cap) == FALSE){
			bms->seq++;
			///< いきなりいく
			Capture_StateChange(bms, EBMS_BOUNCE);
		}
	
		break;
	
	default:
		break;
	}	
	
	return TRUE;
}

static BOOL Capture_Fall_End(BMS_PTR bms)
{
#ifdef BM_CAPTURE_AUTO_CONTROL
	Capture_StateChange(bms, EBMS_BOUNCE);	
#endif
	return TRUE;
}
#if 0
static const s16 BoundTable[][3] = {
	{ 0, -7, 1 },{ 1, -5, 0 },{ 0, -3, 0 },{ 1, -2, 0 },{ 0, -1, 0 },
	{ 1, +1, 0 },{ 0, +2, 0 },{ 1, +3, 0 },{ 0, +5, 0 },{ 1, +7, 1 },
	
	{ 0, -5, 1 },{ 0, -3, 0 },{ 1, -2, 0 },{ 0, -1, 0 },
	{ 0, +1, 0 },{ 1, +2, 0 },{ 0, +3, 0 },{ 0, +5, 1 },
	
	{ 0, -3, 1 },{ 0, -2, 0 },{ 0, -1, 0 },{ 1, -1, 0 },
	{ 0, +1, 0 },{ 0, +1, 0 },{ 0, +2, 0 },{ 1, +3, 1 },
	
	{ 0, -2, 1 },{ 0, -1, 0 },
	{ 0, +1, 0 },{ 0, +2, 1 },
	
	{ 0xFF, 0xFF, 0 },
};

static const int BounceSE[][2] = {
	{  1, SEQ_SE_DP_KON,  },
	{ 10, SEQ_SE_DP_KON,  },
	{ 18, SEQ_SE_DP_KON2, },
	{ 26, SEQ_SE_DP_KON3, },
	{ 30, SEQ_SE_DP_KON4, },
};

#else
static const s16 BoundTable[][3] = {
	{ 0, -7, 1 },{ 1, -5, 0 },{ 0, -3, 0 },{ 1, -2, 0 },
	{ 1, +2, 0 },{ 1, +3, 0 },{ 0, +5, 0 },{ 1, +7, 1 },
	
	{ 0, -5, 1 },{ 0, -3, 0 },{ 1, -2, 0 },
	{ 1, +2, 0 },{ 0, +3, 0 },{ 0, +5, 1 },
	
	{ 0, -2, 0 },{ 1, -1, 0 },
	{ 0, +1, 0 },{ 0, +2, 0 },
	
	{ 0, -2, 1 },
	{ 0, +2, 1 },
	
	{ 0xFF, 0xFF, 0 },
};

static const int BounceSE[][2] = {
	{  1, SEQ_SE_DP_KON,  },
	{  8, SEQ_SE_DP_KON,  },
	{ 14, SEQ_SE_DP_KON2, },
	{ 18, SEQ_SE_DP_KON3, },
	{ 20, SEQ_SE_DP_KON4, },
};
#endif

static BOOL Capture_Bounce(BMS_PTR bms)
{
	switch(bms->seq){
	case 0:
		CATS_ObjectAnimeSeqSetCap(bms->cap, EBM_ANM_OPEN);
		CATS_ObjectAnimeFrameSetCap(bms->cap, 0);
		bms->seq++;
		
	case 1:
		{
			s16 x, y;
			int anm;
			
			//x = BoundTable[ bms->cnt ][ 0 ] * bms->vec_r;
			x = 0;
			y = BoundTable[ bms->cnt ][ 1 ];
			
			anm = BoundTable[ bms->cnt ][ 2 ];
			CATS_ObjectAnimeFrameSetCap(bms->cap, anm);
			
			bms->cnt++;
			
			{
				int i;
				
				for (i = 0; i < 5; i++){
					if (BounceSE[ i ][ 0 ] == bms->cnt){
						Snd_SePlayPan(BounceSE[ i ][ 1 ], WAZA_SE_PAN_R);
					}
				}
			}
			
			if (bms->cnt > BM_BOUNCE_WAIT
			||	x == 0xFF
			||	y == 0xFF){
				bms->seq++;
			}
			else {
				CATS_ObjectPosMoveCap(bms->cap, x, y);
			}
		}	
		break;
	
	default:
		Capture_StateChange(bms, EBMS_BOUNCE_END);
		break;
	}
		
	return TRUE;
}

static BOOL Capture_Bounce_End(BMS_PTR bms)
{
#ifdef BM_CAPTURE_AUTO_CONTROL
	Capture_StateChange(bms, EBMS_STOP);
#endif
	return TRUE;
}

static BOOL Capture_Stop(BMS_PTR bms)
{
	
	bms->cnt++;
	if (bms->cnt >= BM_STOP_WAIT){
		bms->seq++;
		bms->cnt = 0;
		Capture_StateChange(bms, EBMS_STOP_END);
	}
	return TRUE;
}

static BOOL Capture_Stop_End(BMS_PTR bms)
{	
	Capture_StateChange(bms, EBMS_ROLL);
	return TRUE;
}

static const s16 RollTable[][12] = {
//	{ -3, -2, +2, +3, 0, +3, +2, -2, -3, 0xFF },
//	{ -2, -2, +2, +2, 0, +2, +2, -2, -2, 0xFF },
	{ -2, -0, +2, +2, +0, -2, 0xFF, 0xFF, 0xFF },
	{ -1, -0, +1, +1, +0, -1, 0xFF, 0xFF, 0xFF },
	{ -1, +0, +1, +1, +0, -1, 0, 0, 0, 0, 0, 0xFF },
};


static BOOL Capture_Roll(BMS_PTR bms)
{
	switch(bms->seq){
	case 0:
		GF_ASSERT(bms->roll_num < BM_ROLL_NUM);
		bms->seq++;
	
	case 1:
		{
			s16 x;
			x = RollTable[ bms->roll_num ][ bms->cnt ];// * bms->vec_r;
			bms->cnt++;
			
			if (bms->cnt > BM_ROLL_WAIT
			||	x == 0xFF){
				bms->seq++;
				bms->roll_num++;
				CATS_ObjectRotationSetCap(bms->cap, 0);
				Capture_StateChange(bms, EBMS_ROLL_END);
				return TRUE;
			}
			else {
				if (bms->cnt == 5){
					Snd_SePlayPan(SEQ_SE_DP_BOWA, WAZA_SE_PAN_R);
				}
				CATS_ObjectPosMoveCap(bms->cap, x, 0);
				CATS_ObjectRotationAddCap(bms->cap, BM_ROLL_RAD(x));
			}
		}		
		break;
		
	default:
	//	Capture_StateChange(bms, EBMS_ROLL_END);
		break;
	}	
	return TRUE;
}

static BOOL Capture_Roll_End(BMS_PTR bms)
{
#ifdef BM_CAPTURE_AUTO_CONTROL
	Capture_StateChange(bms, EBMS_SUCCESS_1);
#endif
	return TRUE;
}

static BOOL Capture_Failure(BMS_PTR bms)
{
	Capture_StateChange(bms, EBMS_FAILURE_END);
	
	return TRUE;
}
static BOOL Capture_Failure_End(BMS_PTR bms)
{
	Capture_StateChange(bms, EBMS_END);
	
	return TRUE;
}

static BOOL Capture_Success_1(BMS_PTR bms)
{	
	switch(bms->seq){
	case 0:
		///< 暗く
		{
			int pal_ofs;
			
			pal_ofs = CATS_ObjectPaletteOffsetGetCap(bms->cap);
			
			PaletteFadeReq(bms->bmd.pfd, PF_BIT_MAIN_OBJ, 1 << pal_ofs, BM_FADE_DARK_SPD, 0, BM_FADE_DARK_PARA, BM_FADE_DARK);
			
			bms->seq++;
		}
		break;
		
	case 1:
		if (PaletteFadeCheck(bms->bmd.pfd) != 0){ break; }
		{
			TSP_BALL_PARAM para;
			
			para.ball_id = bms->bmd.ball_id;			
			para.heap_id = bms->bmd.heap_id;
			para.set_id	 = MonsterBall_Get_SPA_Star_Get(para.ball_id);
			para.close_only = 0;
			CATS_ObjectPosGetCap(bms->cap, &para.x, &para.y);
			
			bms->spb = SPB_Init(&para);
		}			
		bms->seq++;
		break;
		
	case 2:
		SPB_Load(bms->spb);
		bms->seq++;
		break;
		
	case 3:
		{
			if (SPB_Main(bms->spb) == FALSE){
				CATS_ObjectAnimeFrameSetCap(bms->cap, 0);
				SPB_End(bms->spb);
				bms->seq++;
			}
		}
		break;
	default:
		if (PaletteFadeCheck(bms->bmd.pfd) != 0){ break; }
		
		Capture_StateChange(bms, EBMS_SUCCESS_1_END);
		break;
	}	
	
	return TRUE;
}

static BOOL Capture_Success_1_End(BMS_PTR bms)
{
//	Capture_StateChange(bms, EBMS_SUCCESS_2);
	
	return TRUE;
}

static BOOL Capture_Success_2(BMS_PTR bms)
{	
	switch(bms->seq){
	case 0:
		{
			int pal_ofs;
			
			pal_ofs = CATS_ObjectPaletteOffsetGetCap(bms->cap);
			
			PaletteFadeReq(bms->bmd.pfd, PF_BIT_MAIN_OBJ, 1 << pal_ofs, BM_FADE_DARK_SPD, BM_FADE_DARK_PARA, 0, BM_FADE_DARK);
		}
		
		bms->seq++;
		break;
	
	case 1:
		if (PaletteFadeCheck(bms->bmd.pfd) != 0){ break; }
				
		bms->seq++;
		break;
	
	default:		
		Capture_StateChange(bms, EBMS_SUCCESS_2_END);
		break;
	}	
	
	return TRUE;
}

static BOOL Capture_Success_2_End(BMS_PTR bms)
{
	Capture_StateChange(bms, EBMS_SUCCESS_3);
	
	return TRUE;
}

static BOOL Capture_Success_3(BMS_PTR bms)
{	
	switch(bms->seq){
	case 0:
		CATS_ObjectObjModeSetCap(bms->cap, GX_OAM_MODE_XLU);
		
		bms->seq++;
	
	case 1:
	
		if (bms->eva > 0){
			bms->eva--;
			bms->evb++;			
		}
		else {
			bms->eva =  0;
			bms->evb = 15;
			CATS_ObjectEnableCap(bms->cap, CATS_ENABLE_FALSE);
			bms->seq++;
		}
		G2_ChangeBlendAlpha(bms->eva, bms->evb);	
		break;
	
	default:		
		Capture_StateChange(bms, EBMS_SUCCESS_3_END);
		break;
	}	
	
	return TRUE;
}

static BOOL Capture_Success_3_End(BMS_PTR bms)
{
	Capture_StateChange(bms, EBMS_END);
	
	return TRUE;
}

static BOOL Capture_End(BMS_PTR bms)
{
	return FALSE;
}


static BOOL (* const Capture_TcbTable[])(BMS_PTR wk) = {
	Capture_Start,
	Capture_Throw,
	Capture_Throw_End,
	Capture_Open,
	Capture_Open_End,
	Capture_Shed,
	Capture_Shed_End,
	Capture_Close,
	Capture_Close_End,
	Capture_Flash,
	Capture_Flash_End,
	Capture_Fall,
	Capture_Fall_End,
	Capture_Bounce,
	Capture_Bounce_End,
	Capture_Stop,
	Capture_Stop_End,
	Capture_Roll,
	Capture_Roll_End,
	Capture_Failure,
	Capture_Failure_End,
	Capture_Success_1,
	Capture_Success_1_End,
	Capture_Success_2,
	Capture_Success_2_End,
	Capture_Success_3,
	Capture_Success_3_End,
	Capture_End,
};

///< 捕獲
static BOOL BM_Capture(BMS_PTR bms)
{
	BOOL active;
	
	active = Capture_TcbTable[ bms->state ](bms);
	
	return active;
}


///< 投げる
static BOOL BM_Throw(BMS_PTR bms)
{
	switch(bms->seq){
	case 0:
		WazaTool_InitCurveYFx(&bms->cm[0],
							  &bms->cm[1], 
							  bms->tp.sx, bms->tp.ex,
							  bms->tp.sy, bms->tp.ey,
							  bms->tp.time, bms->tp.height * FX32_ONE);
		bms->tp.time_stop = 0;
		bms->seq++;
		bms->psp = NULL;
		
		{
			int num;
			
		//	if (bms->bmd.type > EBMT_STAY_D){
			if (MonsterBall_RollFlagGet(bms->bmd.type) == TRUE){
				num = (gf_rand() % 20) + 10;
			
				CATS_ObjectRotationAddCap(bms->cap, 0x2000*num);
			}
		}
		break;

	case 1:
	//	if (bms->bmd.type > EBMT_STAY_D){
		if (MonsterBall_RollFlagGet(bms->bmd.type) == TRUE){
			CATS_ObjectRotationAddCap(bms->cap, 0x2000);
			
			if (bms->tp.time_stop > ((bms->tp.time / 2) + 10)){
				CATS_ObjectRotationAddCap(bms->cap, 0x2000);
			}
			
			if (MonsterBall_FadeFlagGet(bms->bmd.type) == TRUE){
				if (bms->tp.time_stop == ((bms->tp.time / 2) + 10)){
					int pal_ofs;
				
					pal_ofs = CATS_ObjectPaletteOffsetGetCap(bms->cap);
					
					bms->psp = PaletteSoftFade(bms->bmd.pfd, bms->bmd.heap_id, FADE_MAIN_OBJ, pal_ofs * 16, 16, -2, 2, 0, 14, 0xFFFF, 1002);
				}
			}
		}
		bms->tp.time_stop++;
		
		///< 空中停止
		if (bms->bmd.type >= EBMT_THROW_C
		&&	bms->bmd.type <= EBMT_THROW_L){
			if (bms->tp.time_stop >  (bms->tp.time / 2)
			&& (bms->tp.time_stop < ((bms->tp.time / 2) + BM_STOP_TIME))){ break; }
		}
			
		if (WazaTool_CalcAndReflectCurveFxCap(&bms->cm[0], &bms->cm[1], bms->cap) == FALSE){
			BM_BallRadSet(bms, 0);
			bms->seq++;
		}
		break;

	case 2:
	//	if (bms->bmd.type > EBMT_STAY_D
		if (MonsterBall_FadeFlagGet(bms->bmd.type) == TRUE
		&&	bms->psp != NULL){
			if (IsPaletteSoftFade(bms->psp) == TRUE){ break; }
		
			PaletteSoftFadeDelete(bms->psp);
			bms->open = TRUE;					///< 開くフラグ　ON
			
			return FALSE;
		}
		else {
			if (bms->bmd.type >= EBMT_CAPTURE_BB){
				bms->open = TRUE;				///< 開くフラグ　ON
				
				return FALSE;
			}
			
			if (bms->bmd.ball_id == BALL_EFF_STONE){
				Snd_SePlayPan(SEQ_SE_DP_W202B, WAZA_SE_PAN_R);
			}			
			bms->seq++;
		}
		break;
		
	case 3:
		CATS_ObjectAnimeSeqSetCap(bms->cap, 1);
		BM_BallAnimeFlagSet(bms, TRUE);
		bms->tp.time_stop = 0;
		bms->seq++;
		break;
		
	default:
		if (bms->tp.time_stop == BM_OPEN_WAIT){
			{
				int pal_ofs;
				
				if (bms->bmd.type != EBMT_THROW_E0_STONE
				&&	bms->bmd.type != EBMT_THROW_E0_FOOD){
				
					pal_ofs = CATS_ObjectPaletteOffsetGetCap(bms->cap);
					bms->psp = PaletteSoftFade(bms->bmd.pfd, bms->bmd.heap_id, FADE_MAIN_OBJ, pal_ofs * 16, 16, -2, 2, 0, 14, 0xFFFF, 1002);
					
				}
			}
			bms->open = TRUE;						///< 開くフラグ　ON	
		}
		if ((++bms->tp.time_stop) <= BM_OPEN_WAIT_2){ break; }

		if (bms->bmd.type != EBMT_THROW_E0_STONE
		&&	bms->bmd.type != EBMT_THROW_E0_FOOD){
			if (IsPaletteSoftFade(bms->psp) == TRUE){ break; }
			
			PaletteSoftFadeDelete(bms->psp);
		}
		
		return FALSE;
	}
	return TRUE;
}


static BOOL BM_Failure(BMS_PTR bms)
{
	switch(bms->seq){
	case 0:
		WazaTool_InitCurveYFx(&bms->cm[0],
							  &bms->cm[1], 
							  bms->tp.sx, bms->tp.ex,
							  bms->tp.sy, bms->tp.ey,
							  bms->tp.time, bms->tp.height * FX32_ONE);
		bms->tp.time_stop = 0;
		bms->seq++;
		bms->psp = NULL;
		
		{
			int num;
			
		//	if (bms->bmd.type > EBMT_STAY_D){
			if (MonsterBall_RollFlagGet(bms->bmd.type) == TRUE){
				num = (gf_rand() % 20) + 10;
			
				CATS_ObjectRotationAddCap(bms->cap, 0x2000*num);
			}
		}
		break;

	case 1:
	//	if (bms->bmd.type > EBMT_STAY_D){
		if (MonsterBall_RollFlagGet(bms->bmd.type) == TRUE){
			CATS_ObjectRotationAddCap(bms->cap, 0x2000);
			
			if (bms->tp.time_stop > ((bms->tp.time / 2) + 10)){
				CATS_ObjectRotationAddCap(bms->cap, 0x2000);
			}
			
			if (MonsterBall_FadeFlagGet(bms->bmd.type) == TRUE){
				if (bms->tp.time_stop == ((bms->tp.time / 2) + 10)){
					int pal_ofs;
				
					pal_ofs = CATS_ObjectPaletteOffsetGetCap(bms->cap);
					
					bms->psp = PaletteSoftFade(bms->bmd.pfd, bms->bmd.heap_id, FADE_MAIN_OBJ, pal_ofs * 16, 16, -2, 2, 0, 14, 0xFFFF, 1002);
				}
			}
		}
		bms->tp.time_stop++;
		
		///< 空中停止
		if (bms->bmd.type >= EBMT_THROW_C
		&&	bms->bmd.type <= EBMT_THROW_L){
			if (bms->tp.time_stop >  (bms->tp.time / 2)
			&& (bms->tp.time_stop < ((bms->tp.time / 2) + BM_STOP_TIME))){ break; }
		}
			
		if (WazaTool_CalcAndReflectCurveFxCap(&bms->cm[0], &bms->cm[1], bms->cap) == FALSE){
			BM_BallRadSet(bms, 0);
			bms->seq++;
		}
		break;

	case 2:
	//	if (bms->bmd.type > EBMT_STAY_D
		if (MonsterBall_FadeFlagGet(bms->bmd.type) == TRUE
		&&	bms->psp != NULL){
			if (IsPaletteSoftFade(bms->psp) == TRUE){ break; }
		
			PaletteSoftFadeDelete(bms->psp);
			bms->open = TRUE;					///< 開くフラグ　ON
			
			return FALSE;
		}
		else {
			if (bms->bmd.type >= EBMT_CAPTURE_BB){
				bms->open = TRUE;				///< 開くフラグ　ON
				
				return FALSE;
			}
			bms->seq++;
		}
		break;
		
	case 3:
		CATS_ObjectAnimeSeqSetCap(bms->cap, 1);
		BM_BallAnimeFlagSet(bms, FALSE);
		bms->tp.time_stop = 0;
		bms->seq++;
		break;
		
	default:
		if (bms->tp.time_stop == BM_OPEN_WAIT){
			CATS_ObjectAnimeFrameSetCap(bms->cap, 2);		///< 縮むのを飛ばす
			{
				int pal_ofs;
			
				pal_ofs = CATS_ObjectPaletteOffsetGetCap(bms->cap);
				bms->psp = PaletteSoftFade(bms->bmd.pfd, bms->bmd.heap_id, FADE_MAIN_OBJ, pal_ofs * 16, 16, -2, 2, 0, 14, 0xFFFF, 1002);
			}
			bms->open = TRUE;						///< 開くフラグ　ON	
		}
		if ((++bms->tp.time_stop) <= BM_OPEN_WAIT_2){ break; }
		
		if (IsPaletteSoftFade(bms->psp) == TRUE){ break; }
		
		PaletteSoftFadeDelete(bms->psp);
		
		return FALSE;
	}
	return TRUE;
}

///< 閉じる
static const int close_anime_tbl[][2] = {
	{ 0, 2 },	///< 0コマ目 5フレ
	{ 2, 2 },	///< 1コマ目 5フレ
	{ 2, 6 },	///< 2コマ目 8フレ
	{ 1, 6 },	///< 1コマ目 8フレ
	{ 0, 6 },	///< 0コマ目 8フレ
};
static BOOL BM_Close(BMS_PTR bms)
{
	switch(bms->seq){
	case 0:
		BM_BallAnimeFlagSet(bms, FALSE);
		CATS_ObjectAnimeSeqSetCap(bms->cap, 1);
		bms->tp.time_stop++;
		if (bms->tp.time_stop >= close_anime_tbl[0][1]){
			CATS_ObjectAnimeFrameSetCap(bms->cap, close_anime_tbl[0][0]);
			bms->tp.time_stop = 0;
			bms->seq++;
		}
		break;
		
	case 1:
		bms->tp.time_stop++;
		if (bms->tp.time_stop >= close_anime_tbl[1][1]){
			CATS_ObjectAnimeFrameSetCap(bms->cap, close_anime_tbl[1][0]);
			bms->tp.time_stop = 0;
			bms->seq++;
		}
		break;
	
	case 2:
		{
			TSP_BALL_PARAM para;
			
			para.ball_id = bms->bmd.ball_id;
			para.heap_id = bms->bmd.heap_id;
			para.set_id	 = ALL_DATA_SET;
			para.close_only = 1;
			CATS_ObjectPosGetCap(bms->cap, &para.x, &para.y);
			
			bms->spb = SPB_Init(&para);
		}		
		bms->seq++;
		break;
	
	case 3:
		SPB_Load(bms->spb);
		bms->seq++;
		break;
		
	case 4:
		bms->tp.time_stop++;
		if (bms->tp.time_stop >= close_anime_tbl[2][1]){
			CATS_ObjectAnimeFrameSetCap(bms->cap, close_anime_tbl[2][0]);
			bms->tp.time_stop = 0;
			bms->seq++;
		}
		break;
		
	case 5:
		bms->tp.time_stop++;
		if (bms->tp.time_stop >= close_anime_tbl[3][1]){
			CATS_ObjectAnimeFrameSetCap(bms->cap, close_anime_tbl[3][0]);
			bms->tp.time_stop = 0;
			bms->seq++;
		}
		break;
		
	case 6:
		bms->tp.time_stop++;
		if (bms->tp.time_stop >= close_anime_tbl[4][1]){
			CATS_ObjectAnimeFrameSetCap(bms->cap, close_anime_tbl[4][0]);
			bms->tp.time_stop = 0;
			bms->seq++;
		}
		break;
	
	case 7:
		if (SPB_Main(bms->spb) == FALSE){
			SPB_End(bms->spb);
			bms->seq++;
		}
		break;
	
	default:
		return FALSE;
		break;
	}
	
	return TRUE;
}

//
//	初期化0度から、360度回転をする
//	着地角度から、右か左に20度まで転がる
//
//
//
#define BM_ROTATION_NUM		(1)
#define BM_ROTATION_FRAME	(10)
#define BM_ROTATION_RAD		(45)
static BOOL BM_Shake(BMS_PTR bms)
{
	switch(bms->seq){
	case 0:
		{
			if (bms->flg == 0){
				WazaTool_InitMoveOneSync(&bms->cmo, -FX_GET_ROTA_NUM(BM_ROTATION_RAD), +FX_GET_ROTA_NUM(BM_ROTATION_RAD), BM_ROTATION_FRAME);
			}
			else {
				WazaTool_InitMoveOneSync(&bms->cmo, +FX_GET_ROTA_NUM(BM_ROTATION_RAD), -FX_GET_ROTA_NUM(BM_ROTATION_RAD), BM_ROTATION_FRAME);
			}
			bms->flg ^= 1;
		}
		bms->seq++;
		break;

	case 1:
		CATS_ObjectRotationSetCap(bms->cap, bms->cmo.num);
		if (WazaTool_CalcMoveOne(&bms->cmo) == FALSE){
			if (bms->cnt >= BM_ROTATION_NUM){
				bms->seq++;
			}
			else {
				bms->cnt++;
				bms->seq--;
			}
		}
		break;

	default:
		bms->tp.time_stop = 0;
		return FALSE;
		break;
	}
	return TRUE;
}


static BOOL BM_Free(BMS_PTR bms)
{
	///< 特に何もしない
	
	if (bms->seq == 0xFF){
		return FALSE;
	}
	
	if (bms->cap != NULL){
		s16 x, y;
		
		CATS_ObjectPosGetCap(bms->cap, &x, &y);
		bms->tp.sx = x;
		bms->tp.sy = y;
	}
		
	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief	ボール移動メインTCB
 *
 * @param	tcb	
 * @param	work	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void BM_TcbMain(TCB_PTR tcb, void* work)
{
	BOOL state;
	
	BMS_PTR wk = (BMS_PTR)work;
	
	if (wk->active == FALSE){ return; }
	
	if (wk->ex_wait > 0){	//外部指定ウェイト
		wk->ex_wait--;
		CATS_Draw(wk->crp);
		return;
	}
	
	state = BM_TcbTable[ wk->bmd.mode ]( wk );
	
	if (state == FALSE){
		wk->active = FALSE;
	}
	
	if (wk->anime_flag == TRUE){
		CATS_ObjectUpdateCap(wk->cap);
	}
	CATS_Draw(wk->crp);
}


//--------------------------------------------------------------
/**
 * @brief	ボール移動初期化
 *
 * @param	bmd	
 *
 * @retval	BMS_PTR	
 *
 */
//--------------------------------------------------------------
BMS_PTR BM_Init(TBALL_MOVE_DATA* bmd)
{
	BMS_PTR wk = NULL;
	
	wk = sys_AllocMemory(bmd->heap_id, sizeof(TBALL_MOVE_SYS));
	MI_CpuClear8(wk, sizeof(TBALL_MOVE_SYS));
	
	GF_ASSERT(wk != NULL);
	
	wk->bmd = (*bmd);
	wk->seq = 0;
	wk->flg = 0;
	wk->cnt = 0;
	wk->state = 0;
	wk->roll_num = 0;
	wk->scene = EBM_DEMO_SCENE_THROW;
	wk->scene_seq = 0;
	wk->crp	= CATS_ResourceCreate(wk->bmd.csp);
	wk->ex_wait = 0;
	
	wk->anime_flag = MonsterBall_AnimeFlagGet(wk->bmd.type);
	
	wk->tp.time_stop = 0;

	wk->eva = 16;
	wk->evb =  0;
	DefaultBlendSet();
	
	{
		int temp;
		
		temp = gf_rand() % 2;
		
		if (temp){
			wk->vec_r = +1;
		}
		else {
			wk->vec_r = -1;
		}
	}
	
	BMT_ClactInit(wk);
	
	BMT_ClactAdd(wk);
	
	BMT_BallParaSet(wk);
	
	wk->active = TRUE;
	wk->open   = FALSE;
	
	wk->tcb = TCB_Add(BM_TcbMain, wk, TCBPRI_BALL_EFFECT);

	return wk;
}


//--------------------------------------------------------------
/**
 * @brief	ボール移動終了チェック
 *
 * @param	bms	
 *
 * @retval	BOOL	
 *
 */
//--------------------------------------------------------------
BOOL BM_EndCheck(BMS_PTR bms)
{
	GF_ASSERT(bms != NULL);
	
	return bms->active ? TRUE : FALSE;
}

BOOL BM_IsOpen(BMS_PTR bms)
{
	GF_ASSERT(bms != NULL);
	
	return bms->open ? TRUE : FALSE;
}

//--------------------------------------------------------------
/**
 * @brief	ボールの捕獲デモ状況
 *
 * @param	bms	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
int	BM_CaptureStateGet(BMS_PTR bms)
{
	return bms->state;
}


//--------------------------------------------------------------
/**
 * @brief	ボール捕獲デモ状況コントロール
 *
 * @param	bms	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void BM_CaptureStateSet(BMS_PTR bms, int state)
{
	bms->state = state;
}


//--------------------------------------------------------------
/**
 * @brief	ボール捕獲デモ状況チェック
 *
 * @param	bms	
 * @param	state	
 *
 * @retval	BOOL	
 *
 */
//--------------------------------------------------------------
BOOL BM_IsCaptureStateEnd(BMS_PTR bms, int state)
{
	return (bms->state == state) ? TRUE : FALSE;
}


//--------------------------------------------------------------
/**
 * @brief	ボール移動終了
 *
 * @param	bms	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void BM_Delete(BMS_PTR bms)
{
	int heap = bms->bmd.heap_id;
	
	GF_ASSERT(bms != NULL);
	
	CATS_ResourceDestructor_S(bms->bmd.csp, bms->crp);
	CATS_ActorPointerDelete_S(bms->cap); 
	
	TCB_Delete(bms->tcb);
	
	sys_FreeMemoryEz(bms);
}


//--------------------------------------------------------------
/**
 * @brief	モード切替
 *
 * @param	bms	
 * @param	mode	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void BM_ModeChange(BMS_PTR bms, int mode)
{
	bms->bmd.mode	= mode;
	bms->seq		= 0;
	bms->cnt		= 0;	
	bms->flg		= 0;
	bms->active		= TRUE;

	CATS_ObjectPosGetCap(bms->cap, &bms->tp.sx, &bms->tp.sy);
}


//--------------------------------------------------------------
/**
 * @brief	モード取得
 *
 * @param	bms	
 *
 * @retval	int	
 *
 */
//--------------------------------------------------------------
int BM_ModeGet(BMS_PTR bms)
{
	GF_ASSERT(bms != NULL);
	
	return bms->bmd.mode;
}

// -----------------------------------------
//
//	ツール
//
// -----------------------------------------
static void BMT_BallParaSet(BMS_PTR bms)
{
	CATS_ObjectPosGetCap(bms->cap, &bms->tp.sx, &bms->tp.sy);

	switch(bms->bmd.type){
	case EBMT_STAY_AA:
	case EBMT_STAY_BB:
	case EBMT_STAY_A:
	case EBMT_STAY_B:
	case EBMT_STAY_C:
	case EBMT_STAY_D:
		CATS_ObjectPosGetCap(bms->cap, &bms->tp.ex, &bms->tp.ey);
		bms->tp.height	= 0;
		break;

	case EBMT_THROW_C:
		WazaEffPosGet_Type(0, 0, &bms->tp.ex, &bms->tp.ey);
		bms->tp.height	= 48;
		bms->tp.ey		+= 32;
		break;
		
	case EBMT_THROW_R:
		CATS_ObjectPosGetCap(bms->cap, &bms->tp.sx, &bms->tp.sy);
		WazaEffPosGet_Type(1, 4, &bms->tp.ex, &bms->tp.ey);
		bms->tp.height	= 48;
		bms->tp.ey		+= 32;
		break;
		
	case EBMT_THROW_L:
		WazaEffPosGet_Type(1, 2, &bms->tp.ex, &bms->tp.ey);
		bms->tp.height	= 48;
		bms->tp.ey		+= 32;
		break;

	case EBMT_THROW_E0:
		WazaEffPosGet_Type(0, 1, &bms->tp.ex, &bms->tp.ey);
		bms->tp.height	= 48;
		bms->tp.ey		+= 32;
		break;
		
	case EBMT_THROW_E1:
		WazaEffPosGet_Type(1, 3, &bms->tp.ex, &bms->tp.ey);
		bms->tp.height	 = 48;
		bms->tp.ey		+= 32;
		break;
		
	case EBMT_THROW_E2:
		WazaEffPosGet_Type(1, 5, &bms->tp.ex, &bms->tp.ey);
		bms->tp.height	 = 48;
		bms->tp.ey		+= 32;
		break;

	case EBMT_THROW_E0_STONE:
		WazaEffPosGet_Type(0, 1, &bms->tp.ex, &bms->tp.ey);
		bms->tp.height	= 16;
		bms->tp.ey		+=16;	
		bms->tp.time	= 12;
		return;

	case EBMT_THROW_E0_FOOD:
		WazaEffPosGet_Type(0, 1, &bms->tp.ex, &bms->tp.ey);
		bms->tp.height	= 32;
		bms->tp.ex		-=20;
		bms->tp.ey		+=38;	
		bms->tp.time	= 16;
		return;

	case EBMT_VISUAL:
		bms->tp.ex = VISUAL_ARRIVAL_X;
		bms->tp.ey = VISUAL_ARRIVAL_Y;
		bms->tp.height	= 32;
		bms->tp.ey		+= 32;
		break;
	
	case EBMT_CAPTURE_BB:
		///< 捕獲用
		WazaEffPosGet_Type(0, 1, &bms->tp.ex, &bms->tp.ey);
		bms->tp.height  = 64;
		bms->tp.ey	   +=  8;	
		bms->tp.time	= 16;
		return;
		
	case EBMT_CAPTURE_B:
		///< 捕獲用
		WazaEffPosGet_Type(1, 3, &bms->tp.ex, &bms->tp.ey);
		bms->tp.height  = 64;
		bms->tp.ey	   +=  8;	
		bms->tp.time	= 16;
		return;
		
	case EBMT_CAPTURE_D:
		///< 捕獲用
		WazaEffPosGet_Type(1, 5, &bms->tp.ex, &bms->tp.ey);
		bms->tp.height  = 64;
		bms->tp.ey	   +=  8;	
		bms->tp.time	= 16;
		return;
		
	default:
		break;
	}
	bms->tp.time	= 20;
}


static void BMT_StartPosSet(BMS_PTR bms, s16* x, s16* y)
{
	switch(bms->bmd.type){
	case EBMT_STAY_AA:
		WazaEffPosGet_Type(0, 0, x, y);
		(*y) += BMT_START_POS_OFS_Y;
		break;
	case EBMT_STAY_BB:
		WazaEffPosGet_Type(0, 1, x, y);
		(*y) += BMT_START_POS_OFS_E_Y;
		break;
	case EBMT_STAY_A:
		WazaEffPosGet_Type(1, 2, x, y);
		(*y) += BMT_START_POS_OFS_Y;
		break;
	case EBMT_STAY_C:
		WazaEffPosGet_Type(1, 4, x, y);
		(*y) += BMT_START_POS_OFS_Y;
		break;
		
	case EBMT_STAY_B:
		WazaEffPosGet_Type(1, 3, x, y);
		(*y) += BMT_START_POS_OFS_E_Y;
		break;
		
	case EBMT_STAY_D:
		WazaEffPosGet_Type(1, 5, x, y);
		(*y) += BMT_START_POS_OFS_E_Y;
		break;

	case EBMT_THROW_C:
		*x = 10;
		*y = 100;
		break;
		
	case EBMT_THROW_R:
		*x = 10;
		*y = 100;
		break;
		
	case EBMT_THROW_L:
		*x = 10;
		*y = 100;
		break;

	case EBMT_THROW_E0:
		WazaEffPosGet_Type(0, 0, x, y);
		break;
		
	case EBMT_THROW_E1:
		WazaEffPosGet_Type(0, 0, x, y);
		break;
		
	case EBMT_THROW_E2:
		WazaEffPosGet_Type(0, 0, x, y);
		break;
	
	case EBMT_THROW_E0_STONE:
		WazaEffPosGet_Type(0, 0, x, y);
		break;
		
	case EBMT_THROW_E0_FOOD:
		WazaEffPosGet_Type(0, 0, x, y);
		break;

	case EBMT_VISUAL:
		*x = VISUAL_TRAINER_ARRIVAL_X;
		*y = VISUAL_TRAINER_ARRIVAL_Y;
		break;
	
	case EBMT_CAPTURE_BB:
	case EBMT_CAPTURE_B:
	case EBMT_CAPTURE_D:
		///< 捕獲用
		*x = -30;
		*y = 160;
		break;
	
	default:
		break;
	}
}

static void BMT_ClactInit(BMS_PTR bms)
{
	int ncgr;
	int nclr;
	int ncer;
	int nanr;
	
	CATS_ClactSetInit(bms->bmd.csp, bms->crp, BT_OBJ_NUM);
	
	if (bms->bmd.surface == 0){
		CLACT_U_SetSubSurfaceMatrix(CATS_EasyRenderGet(bms->bmd.csp), 0, BATTLE_SUB_ACTOR_DISTANCE);
	}
	
	{
		int i;
		TCATS_RESOURCE_NUM_LIST crnl;
		
		for (i = 0; i < CLACT_U_RES_MAX; i++){
			crnl.res_num[i] = BT_RES_NUM;
		}
		crnl.res_num[4] = 0;
		crnl.res_num[5] = 0;
		
		CATS_ResourceManagerInit(bms->bmd.csp, bms->crp, &crnl);
	}
	
	ncgr = MonsterBall_Get_GRA_Get(bms->bmd.ball_id, 0);
	nclr = MonsterBall_Get_GRA_Get(bms->bmd.ball_id, 1);
	ncer = MonsterBall_Get_GRA_Get(bms->bmd.ball_id, 2);
	nanr = MonsterBall_Get_GRA_Get(bms->bmd.ball_id, 3);
	
	///< 読み込み
	CATS_LoadResourceCharArc(bms->bmd.csp, bms->crp,
							 ARC_BATT_OBJ, ncgr, 1, NNS_G2D_VRAM_TYPE_2DMAIN, bms->bmd.id + BALL_ARC_ID_BASE);

	CATS_LoadResourcePlttWorkArc(bms->bmd.pfd, FADE_MAIN_OBJ,
								 bms->bmd.csp, bms->crp,
							 	 ARC_BATT_OBJ, nclr, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 1, bms->bmd.id + BALL_ARC_ID_BASE);

	CATS_LoadResourceCellArc(bms->bmd.csp, bms->crp, ARC_BATT_OBJ, ncer, 1, bms->bmd.id + BALL_ARC_ID_BASE);

	CATS_LoadResourceCellAnmArc(bms->bmd.csp, bms->crp, ARC_BATT_OBJ, nanr, 1, bms->bmd.id + BALL_ARC_ID_BASE);
}

static void BMT_ClactAdd(BMS_PTR bms)
{
	int i;
	TCATS_OBJECT_ADD_PARAM_S coap;
	int defence_client;

	BMT_StartPosSet(bms, &coap.x, &coap.y);
	
	coap.z		= 0;		
	coap.anm	= 0;
	coap.pri	= 0;
	coap.pal	= 0;
	coap.d_area = CATS_D_AREA_MAIN;
	coap.bg_pri = bms->bmd.bg_pri;
	coap.vram_trans = 0;
	
	for (i = 0; i < CLACT_U_RES_MAX; i++){
		coap.id[i] = bms->bmd.id + BALL_ARC_ID_BASE;
	}

	bms->cap = CATS_ObjectAdd_S(bms->bmd.csp, bms->crp, &coap);
	CATS_ObjectEnableCap(bms->cap, CATS_ENABLE_TRUE);
	
	CATS_ObjectAffineSetCap(bms->cap, CLACT_AFFINE_DOUBLE);
	
	CATS_ObjectAnimeFrameSetCap(bms->cap, 0);
	CATS_ObjectAnimeSeqSetCap(bms->cap, 0);
	
	CATS_ObjectUpdateCap(bms->cap);
	
	DefaultBlendSet();
}


// =============================================================================
//
//
//	■操作関数
//
//
// =============================================================================
///< 表示・非表示切り替え
void BM_BallEnable(BMS_PTR bms, int flag)
{
	CATS_ObjectEnableCap(bms->cap, flag);
}

///< 座標取得
void BM_BallPosGet(BMS_PTR bms, s16* x, s16* y)
{
	CATS_ObjectPosGetCap(bms->cap, x, y);
}

///< 座標設定
void BM_BallPosSet(BMS_PTR bms, s16 x, s16 y)
{
	CATS_ObjectPosSetCap(bms->cap, x, y);
}

///< 角度取得
void BM_BallRadGet(BMS_PTR bms, u16* rot)
{
	*rot = CATS_ObjectRotationGetCap(bms->cap);
}

///< 角度設定
void BM_BallRadSet(BMS_PTR bms, u16 rot)
{
	CATS_ObjectRotationSetCap(bms->cap, rot);
}

///< 自由操作を終わらせる
void BM_BallFreeEnd(BMS_PTR bms)
{
	bms->seq = 0xFF;	
}

///< アニメフラグ設定
void BM_BallAnimeFlagSet(BMS_PTR bms, BOOL flag)
{
	bms->anime_flag = flag;
}

///< プライオリティ
void BM_BallSoftPriSet(BMS_PTR bms, int pri)
{
	CATS_ObjectPriSetCap(bms->cap, pri);
}

///< プライオリティ
void BM_BallBgPriSet(BMS_PTR bms, int pri)
{
	CATS_ObjectBGPriSetCap(bms->cap, pri);	
}

///< 外部指定ウェイト
void BM_BallWaitSet(BMS_PTR bms, int wait)
{
	bms->ex_wait = wait;
}
