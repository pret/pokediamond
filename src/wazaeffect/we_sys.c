//==============================================================================
/**
 * @file	we_sys.c
 * @brief	技エフェクト用のシステム
 * @author	goto
 * @date	2005.06.22(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 *
 */
//==============================================================================
#include "common.h"
#include "system/lib_pack.h"
#include "system/snd_tool.h"

#include "system/arc_tool.h"

#include "wazatool.h"

#include "we_sys.h"							///< 技エフェクト用のシステム.h

#include "west_sp.h"						///< 技エフェクト用サポート.h

#include "battle_particle.h"				///< パーティクル用
#include "wp_tbl.h"							///< パーティクル用

#include "battle/battle_tcb_pri.h"			///< TCB pri
#include "battle/battle_id.h"				///< アーカイブデータ
#include "battle/fight_tool.h"				///< 

#include "include/battle/attr_def.h"		///< 
#include "include/battle/wazano_def.h"		///< 
#include "include/battle/battle_server.h"	///< 
#include "include/poketool/poke_tool.h"		///< 

#include "battle/graphic/batt_bg_def.h"		///< アーカイブデータ
#include "battle/graphic/batt_obj_def.h"		///< アーカイブデータ
#include "system/arc_tool.h"				///< アーカイブ用
#include "system/arc_util.h"				///< アーカイブ用

#include "system/brightness.h"				///< 輝度変更
#include "system/gra_tool.h"

#include "we_tool.h"
#include "we_def.h"

#include "contest/contest.h"

#include "battle/bc_common.h"

/*
///背景のフェードbit(技エフェクト用)
#define ACTIN_HAIKEI_FADE_BIT		(0x0007)
///技エフェクトBG用パレットのフェードbit
#define ACTIN_WAZAEFF_FADE_BIT		(0x0300)
///背景のフェードbit＋技エフェクトBG用パレット(技エフェクト用)
#define ACTIN_EFFBG_ALL_FADE_BIT	(ACTIN_HAIKEI_FADE_BIT | ACTIN_WAZAEFF_FADE_BIT)
*/

#define WES_OFS_ID(n)		((n) * 5000)

#define WES_HAIKEI_S_EV1	(0)
#define WES_HAIKEI_S_EV2	(31)
#define WES_HAIKEI_E_EV1	(31)
#define WES_HAIKEI_E_EV2	(0)
#define WES_HAIKEI_FO_WAIT	(0)
#define WES_HAIKEI_FI_WAIT	(WES_HAIKEI_FO_WAIT)
#define WES_HAIKEI_PAL		(0x00FF)

#define PO_ARC_ID			(ARC_BATT_OBJ)		///< ポケモン画像のアークID
#define FREE_TIME			(2)

#ifdef PM_DEBUG

//#define WE_SYS_DEBUG_ALLOC_SIZE_ON

u64 g_nWazaEffectHeapState = 0;
int	g_nDebugCameraType	   = 0;

#endif

// ----------------------------------------
//
//	■ 戦闘で扱われる構造体
//		[ BTL_SYS_PTR ]
//		とりあえず、適当なメンバを入れてある
//
// ----------------------------------------
typedef struct _TBTL_SYS {
	
	u8	command_code;						///< 命令コードインデックス
	u8	mode;								///< 戦闘・コンテスト・コンクール？
	u16	waza_no;							///< エフェクトを出す技ナンバー
	
	s32 waza_eff_damage;					///< 技で受けるダメージ(回復の時は[ + ])
	u16	waza_eff_power;						///< 出ている技の威力
	u16	waza_eff_natuki;					///< なつき度
	u32	waza_eff_weather;					///< 天候
	u16 waza_eff_cnt;						///< 技エフェクトのカウンタ(空を飛ぶとか)
	u16	waza_eff_ground_id;					///< 技エフェクトの地形データ
	
	u16	at_client_no;						///< 攻撃側のクライアント番号(自分)
	u16	df_client_no;						///< 防御側のクライアント番号(対象)
	
	int	this_ptc_no;						///< 登録した時点のptcno;
	
	PTC_PTR		ptc[PARTICLE_GLOBAL_MAX];	///< パーティクルシステム
	EMIT_PTR	emit[PARTICLE_EMIT_MAX];	///< エミッターの数
	
	CATS_SYS_PTR	csp;					///< セルアクター管理
	EXCHR_PARAM*	excp[CLIENT_MAX];		///< 展開されたポケモンデータ格納構造体のポインタ
	u8				client_type[CLIENT_MAX];///< クライアントタイプ
	SOFT_SPRITE*	ss[CLIENT_MAX];			///< ソフトスプライト
	u32				fight_type;				///< ファイトタイプ
	u16				mons_no[CLIENT_MAX];	///< ポケモンNO
	u8				sex[CLIENT_MAX];		///< ポケモン性別
	u8				rare[CLIENT_MAX];		///< レアフラグ
	u8				form_no[CLIENT_MAX];	///< ポケモンフォルムNo
	u32				personal_rnd[CLIENT_MAX];	///<ポケモン個性乱数
	u32				waza_kouka[CLIENT_MAX];		///< 技効果フラグ
	
	PERAPVOICE*		perap_voice;			///< ペラップ
	u8*				bg_area;				///< バトルの背景
	u16*			pal_area;				///< パレット

	int				henshin_flag;			///< へんしんフラグ（32bitもいらないけど、4バイト境界補正）

} TBTL_SYS;

// ----------------------------------------
//
//	■ ループ用構造体
//		現在のシーケンス位置以外にも
//		繰り返した回数が必要なので構造体
//
// ----------------------------------------
typedef struct _TLOOP_SYS {
	
	u32* seq_adrs;							///< 現在のシーケンス位置
	u8	 n_cnt;								///< 現在のカウンタ
	u8	 e_cnt;								///< 繰り返し回数
	BOOL active;							///< 使用されているか
	
} TLOOP_SYS;

typedef struct {
	
	WE_SYS_PTR		wsp;
	
	CATS_RES_PTR	crp;
	CATS_ACT_PTR	cap;
	
	BOOL			flag;
	
} PT_DROP_SYS;

// ----------------------------------------
//
//	■ 技エフェクトシステム管理構造体
//		[ WE_SYS_PTR ]
//		直接のメンバ参照防止の方向で
//		TWE_SYS_PTR が他のユーザーが扱う型
//
// ----------------------------------------
typedef struct _TWE_SYS {
	
	int	 heap_area;								///< ヒープエリア
	int	 eff_arc_id;

	BOOL contest_active;						///< コンテストとして動作中か？ TRUE = 動作中
	BOOL active;								///< システムが動作可能か？	TRUE = 動作中
	BOOL waza_eff_active;						///< エフェクトが動作中か？ TRUE = 実行中

	void* arc_data_adrs;						///< アーカイブから取得されるポインタ
	u32*  waza_eff_seq_adrs;					///< 現在のシーケンス位置 (4byte単位で移動 = u32)
	u32*  waza_eff_seq_adrs_j[ WE_JUMP_MAX ];	///< 現在のシーケンス位置 (ジャンプ用)
	TLOOP_SYS loop[ WE_LOOP_MAX ];				///< 現在のシーケンス位置 (ループ用構造体)
	PT_DROP_SYS pds[ 2 ];   

	u8	 camera_mode[PARTICLE_GLOBAL_MAX];
	u8	 camera_flag[PARTICLE_GLOBAL_MAX];
	s8	waza_se_pan;							///< SE命令で設定されるPanの値	
	u8	waza_eff_wait;							///< 命令で設定されるウェイトを入れる
	
	// 管理などに使う
	u16 waza_eff_num;							///< 現在登録されている、OBJやTCBの総数
	u16	waza_se_num;							///< 現在登録されている、SEの総数
	
	s32	waza_eff_gp_wk[ WE_GENE_WK_MAX ];		///< 技エフェクトで利用できるテンポラリ

	pWeFunc waza_eff_exe;						///< 現在実行中のシーケンス
	
	// 戦闘用のワーク
	BTL_SYS_PTR btl_sys;						///< 戦闘からもらうパラメータ格納構造体
	GF_BGL_INI* bgl;							///< BGL
	PALETTE_FADE_PTR pfd;						///< PFD
	
	CATS_RES_PTR	crp[ WE_CRP_MAX ];			///< リソース管理
	CATS_ACT_PTR	cap[ WE_CAP_MAX ];			///< OAMのCAP
	TCATS_OBJECT_ADD_PARAM_S coap;				///< 設定保存
	
	// ポケモンドロップ用
	CATS_RES_PTR	poke_crp;					///< ポケモンOAMドロップのCRP
	CATS_ACT_PTR	poke_cap[ WE_POKE_CAP_MAX ];///< ポケモンOAMドロップのCAP
	BOOL			poke_cap_use[ WE_POKE_CAP_MAX ];
	AMO_SYS_PTR		poke_amos[WE_POKE_CAP_MAX ];///< ポケモンOAM追尾SYS
	AMB_SYS_PTR		poke_ambs;					///< ポケモンBG追尾SYS
	
	// チェック用など
	u8	haikei_chg_flag;						///< 背景切り替えフラグ
	u8	se_end_timer;							///< SEの終了待ちを強制的に決めるためのカウンタ
	u8	free_time;								///< 遊び時間
	u8	sub1;

	// 背景用
	HC_SUB_PTR		hc_sub_ptr;					///< 背景サブシステム
	TWES_HAIKEI_ARC haikei_data;				///< 背景データ
	
	int				haikei_fade_bit;
	u8				bg_pri[ 4 ];
	
} TWE_SYS;


// -----------------------------------------
//
//	■ サウンド用の汎用構造体
//		[ SE_SYS_PTR ]
//
// -----------------------------------------
typedef struct _TSE_SYS {

	u8	mode;				///< コントロールモード
	
	u8	seq;				///< シーケンス管理
	u8	gene_seq;			///< 汎用シーケンス
	u8	wait;				///< ウェイト
	u8	gene_wait;			///< 汎用ウェイト
	
	int	s_pan;				///< 開始位置のパン
	int	e_pan;				///< 終了位置のパン
	int	a_pan;				///< 加算するパンの値
	int	n_pan;				///< 現在のパン
	
	u8	repeat;				///< 繰り返し回数

	u16 se_no;				///< SEの番号
	
	u32	wk[ WE_SE_WK_MAX ];	///< 汎用ワーク
	
	WE_SYS_PTR we_sys;		///< WE-SYSのワーク
	
} TSE_SYS;


// -----------------------------------------
//
//	■背景切り替え用の汎用構造体
//		[ HC_SYS_PTR ]
//
// -----------------------------------------
typedef struct _THC_SYS {
	
	int	sub_seq;
	
	u8	mode;
	u8	seq;
	u8	gene_seq;
	u8	wait;

	u8	gene_wait;
	u8	ev1;
	u8	ev2;
	u8	ev1_e;
	u8	ev2_e;
	u8	fade_type;			///< 白か黒か デフォルト黒
	
	int bg_id;				///< 書き換えBG番号
	int ch_mode;			///< 切り替えモード
	int ch_sbit;			///< 切り替え特殊Bit
	
	int gp_wk[ WE_GENE_WK_MAX ];	///< GP_Workのコピー

	u16	move_flag:1;		///< 移動フラグ
	u16 laster_flag:1;		///< ラスターフラグ
	u16	dmy_flag:14;
	
	WE_SYS_PTR	we_sys;		///< WE_SYSのワーク
	
} THC_SYS;

typedef struct {

	WAZATOOL_SCRLASTER_PTR	ptr;
	s16						x;
	s16						y;
	u8						start;
	u8						end;	
	
} HC_LASTER;


#define HC_LASTER_VOFS	(8)
#define HC_LASTER_MAX	((WAZATOOL_DEFLASTER_BUFF_SIZE - 64) / HC_LASTER_VOFS)

typedef struct {
	
	s16 start;
	s16 end;
	
	s16	speed;
	s16 ofs;
	int init;
	
} HC_LASTER_DATA;

typedef struct {
	
	HC_LASTER_DATA lst[ HC_LASTER_MAX ];

	WAZATOOL_DEFLASTER_PTR	dlp;
	
} HC_LASTER_SYS;

static void HaikeiSubSystem_LasterScroll(TCB_PTR tcb, void* work);
static const s16 speed_tbl[] = {
	32, 28, 24, 20, 16, 12,  8,  4, 
	 4,  8, 12, 16, 20, 24, 28, 32,
};

// -----------------------------------------
//
//	■背景切り替え用の動作汎用構造体
//		[ HC_SUB_PTR ]
//
// -----------------------------------------
typedef struct _HC_SUB_SYS {
	
	GF_BGL_INI* bgl;
	
	s16		pos_x;
	s16		pos_y;
	s16		speed_x;
	s16		speed_y;
	int		frm1;
	int		frm2;

	BOOL	active;
	BOOL	destroy;
	
	HC_LASTER_SYS* hls;

} HC_SUB_SYS;


// -----------------------------------------
//
//	■ポケモン追尾用の構造体
//
// -----------------------------------------
typedef struct _TAUTO_MOVE_SYS {
	
	u8 wait;				///< wait
	u8 frame;				///< 更新
	SOFT_SPRITE* ssp;		///< ソフトスプライト
	TCB_PTR		 am_tcb;	///< TCB_PTR
	
} TAUTO_MOVE_SYS;

///< OAM
typedef struct _TAMO_SYS {

	CATS_ACT_PTR	cap;	
	TAUTO_MOVE_SYS	ams;
	
} TAMO_SYS;

///< BG
typedef struct _TAMB_SYS {
	
	GF_BGL_INI*		bgl;
	TAUTO_MOVE_SYS	ams;
	
} TAMB_SYS;

// ============================================================================
//
//
//	■専用デバッグ関数
//
//
// ============================================================================


// =============================================================================
//
//
//	■プロトタイプ
//
//
// =============================================================================
static void WazaEffectWait(WE_SYS_PTR we_sys);
static void WazaEffectExecuted(WE_SYS_PTR we_sys);
static TCB_PTR WazaEffectTCB_Add(u8 mode, WE_SYS_PTR we_sys, TCB_FUNC func, void* work, u32 pri);
static void WazaEffectTCB_Delete(u8 mode, WE_SYS_PTR we_sys, TCB_PTR tcb);

//--------------------------------------------------------------
/**
 * @brief	技エフェクトの実行待ち
 *
 * @param	we_sys	WE-SYSの初期化
 *
 * @retval	none	
 *
 *		WEST_WAIT_ACT
 */
//--------------------------------------------------------------
static void WazaEffectWait(WE_SYS_PTR we_sys)
{
	if (we_sys->waza_eff_wait == 0) {				///< waitが設定されているなら待ち
		we_sys->waza_eff_wait == 0;					///< 念のため
		we_sys->waza_eff_exe = WazaEffectExecuted;	///< 実行関数に遷移する
	}
	else {
		we_sys->waza_eff_wait--;					///< waitデクリメント
	}
}


//--------------------------------------------------------------
/**
 * @brief	技エフェクトの実行 [ 実際にコマンドを行う場所 ]
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 *		WazaEffectAct
 */
//--------------------------------------------------------------
static void WazaEffectExecuted(WE_SYS_PTR we_sys)
{
	pWeFunc func;
	
	do {
		///< 実行関数
		func = WazaEffectCommandGet(*(we_sys->waza_eff_seq_adrs));
		func(we_sys);
		
	} while (we_sys->waza_eff_wait == 0			///< 技ウェイト = 0
		 &&  we_sys->waza_eff_active == TRUE);	///< エフェクトがアクティブ
}


//--------------------------------------------------------------
/**
 * @brief	WE-SYS専用TCBの作成
 *
 * @param	mode		EFFECT / SOUND
 * @param	we_sys	
 * @param	TCB_FUNC	
 * @param	work	
 * @param	pri	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static TCB_PTR WazaEffectTCB_Add(u8 mode, WE_SYS_PTR we_sys, TCB_FUNC func, void* work, u32 pri)
{
	TCB_PTR tcb;
	
	switch(mode){
	case ENUM_WETCB_EFFECT:
		we_sys->waza_eff_num++;
		break;
	case ENUM_WETCB_SOUND:
		we_sys->waza_se_num++;
		break;
	default:
		GF_ASSERT(0);
		break;
	}
	
	tcb = TCB_Add(func, work, pri);
	
	return tcb;
}


//--------------------------------------------------------------
/**
 * @brief	WE-SYS専用TCBの破棄
 *
 * @param	mode	
 * @param	we_sys	
 * @param	tcb	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WazaEffectTCB_Delete(u8 mode, WE_SYS_PTR we_sys, TCB_PTR tcb)
{
	switch(mode){
	case ENUM_WETCB_EFFECT:
		we_sys->waza_eff_num--;
		break;
	case ENUM_WETCB_SOUND:
		we_sys->waza_se_num--;
		break;
	default:
		GF_ASSERT(0);
		break;
	}
	
	TCB_Delete(tcb);
}









// =============================================================================
//
//
//	■外部参照関数
//
//
// =============================================================================
//--------------------------------------------------------------
/**
 * @brief   WE_SYS の初期化
 *
 * @param 	heap_area	ヒープエリア
 *
 * @retval	WE_SYS_PTR	NULLが戻る時は初期化失敗
 *
 */
//--------------------------------------------------------------
WE_SYS_PTR WES_Create(int heap_area)
{
	int i;

	WE_SYS_PTR we_sys = NULL;
	
	///< メインシステムの初期化
	we_sys = sys_AllocMemory(heap_area, sizeof(TWE_SYS));
	
	if (we_sys == NULL){
		GF_ASSERT(we_sys != NULL);
		return NULL;
	}
	memset(we_sys, 0, sizeof(TWE_SYS));
	
	///< HEAPIDをメモリ確保と同時に設定
	we_sys->heap_area = heap_area;
	
	///< 戦闘として動作
	we_sys->contest_active = FALSE;

	
	///< 戦闘システムの初期化
	we_sys->btl_sys = sys_AllocMemory(we_sys->heap_area, sizeof(TBTL_SYS));
	
	if (we_sys->btl_sys == NULL){
		GF_ASSERT(we_sys->btl_sys != NULL);
		return NULL;
	}
	memset(we_sys->btl_sys, 0, sizeof(TBTL_SYS));	
	
	we_sys->active = FALSE;						///< 準備中なのでFALSE

	we_sys->waza_eff_seq_adrs = NULL;			///< システムワークの初期化など
	
	for (i = 0; i < WE_CRP_MAX; i++){			///< CLACT用ワークの初期化
		we_sys->crp[i] = NULL;
	}
	
	for (i = 0; i < WE_POKE_CAP_MAX; i++){		///< ポケモン自動追尾の初期化
		we_sys->poke_amos[i] = NULL;	
	}
	we_sys->poke_ambs = NULL;
	

	we_sys->active = TRUE;						///< 準備完了なのでTRUE
	
	return we_sys;
}


//--------------------------------------------------------------
/**
 * @brief	コンテスト用フラグセット
 *
 * @param	we_sys	
 * @param	flag				TRUE = コンテスト FALSE = それ以外
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WES_ContestFlag_Set(WE_SYS_PTR we_sys, BOOL flag)
{
	GF_ASSERT(we_sys != NULL);
	
	we_sys->contest_active  = flag;
}


//--------------------------------------------------------------
/**
 * @brief	コンテスト用フラグチェック
 *
 * @param	we_sys	
 *
 * @retval	BOOL				TRUE = コンテスト
 *
 */
//--------------------------------------------------------------
BOOL WES_ContestFlag_Get(WE_SYS_PTR we_sys)
{
	GF_ASSERT(we_sys != NULL);
	
	return we_sys->contest_active;
}


//--------------------------------------------------------------
/**
 * @brief	
 *
 * @param	we_sys	
 *
 * @retval	int	
 *
 */
//--------------------------------------------------------------
int WeSysHeapAreaGet(WE_SYS_PTR we_sys)
{
	GF_ASSERT(we_sys != NULL);
	
	return we_sys->heap_area;
}

//--------------------------------------------------------------
/**
 * @brief	WE_SYS の破棄
 *
 * @param	we_sys	WE_SYS用のワーク
 *
 * @retval	BOOL	TRUE = 成功
 *
 */
//--------------------------------------------------------------
BOOL WES_Delete(WE_SYS_PTR we_sys)
{
	// システムの動作チェック
	if (IsWES(we_sys) == FALSE){
		return FALSE;
	}
	
	sys_FreeMemoryEz(we_sys->btl_sys);
	sys_FreeMemoryEz(we_sys);
		
	return TRUE;
}


//--------------------------------------------------------------
/**
 * @brief	技エフェクトのコール
 *
 * @param	we_sys	WE_SYS用のワーク
 * @param	btl_sys	戦闘用のワークエリア
 * @param	waza_no	技番号
 *
 * @retval	BOOL	TURE = 成功
 *
 *	技番号から、対応する技の先頭アドレスをwaza_eff_seq_adrsに入れる
 *	
 *
 */
//--------------------------------------------------------------
BOOL WES_Call(WE_SYS_PTR we_sys, WAZA_EFFECT_PARAM* btl_sys, u16 waza_no)
{
	return WES_Call_Ex(we_sys, btl_sys, waza_no, NULL);
}


//--------------------------------------------------------------
/**
 * @brief	
 *
 * @param	we_sys	
 * @param	btl_sys	
 * @param	waza_no	
 * @param	bgl	
 *
 * @retval	BOOL	
 *
 */
//--------------------------------------------------------------
BOOL WES_Call_Ex(WE_SYS_PTR we_sys, WAZA_EFFECT_PARAM* btl_sys, u16 waza_no,
				 WES_CALL_BTL_EX_PARAM* wcbep)
{
	int i;
	
	int set_waza_no;
	
	set_waza_no = waza_no;
	
//	OS_Printf("コールNo = %d\n", waza_no);
//	OS_Printf("アークID = %d\n", wcbep->eff_arc_id);

#ifdef PM_DEBUG

	g_nWazaEffectHeapState = sys_GetHeapState( we_sys->heap_area );

#endif

	// ----- エフェクト用の基本のブレンド -----
	DefaultBlendSet();
	
	// ----- システムの動作チェック -----
	if (IsWES(we_sys) == FALSE){
		return FALSE;
	}

	// ----- カメラモードの初期化 -----
	for (i = 0; i < PARTICLE_GLOBAL_MAX; i++){
		we_sys->camera_mode[i] = WE_CAMERA_TYPE_ORTHO;
		we_sys->camera_flag[i] = 0;
	}

	
	// ----- WE-SYS側の初期化 -----
	for (i = 0; i < WE_GENE_WK_MAX; i++){		///< 汎用ワーク初期化
		we_sys->waza_eff_gp_wk[i] = 0;
	}
	
	for (i = 0; i < WE_LOOP_MAX; i++){			///< ループ用ワーク初期化
		we_sys->loop[i].active  = FALSE;
		we_sys->loop[i].seq_adrs = NULL;
		we_sys->loop[i].n_cnt	= 0;
		we_sys->loop[i].e_cnt	= 0;
	}
	
	// ----- 戦闘ワークの受け渡し -----
	we_sys->btl_sys->command_code		= btl_sys->command_code;
	we_sys->btl_sys->mode				= btl_sys->mode;
	we_sys->btl_sys->waza_no			= btl_sys->waza_no;			///< 技番号 = waza_noと同じ

	we_sys->btl_sys->waza_eff_damage	= btl_sys->waza_eff_damage;	
	we_sys->btl_sys->waza_eff_power		= btl_sys->waza_eff_power;
	we_sys->btl_sys->waza_eff_natuki	= btl_sys->waza_eff_natuki;
	we_sys->btl_sys->waza_eff_weather	= btl_sys->waza_eff_weather;
	we_sys->btl_sys->waza_eff_cnt		= btl_sys->waza_eff_cnt;
	we_sys->btl_sys->waza_eff_ground_id	= btl_sys->ground_id;
	we_sys->btl_sys->at_client_no		= btl_sys->at_client_no;
	we_sys->btl_sys->df_client_no		= btl_sys->df_client_no;
	we_sys->btl_sys->henshin_flag		= btl_sys->henshin_flag;
#if 1
//	OS_Printf("□-----↓↓↓サーバーからもらうデータ↓↓↓-----□\n");
//	OS_Printf("waza_eff_damage	= %3d\n", btl_sys->waza_eff_damage);
//	OS_Printf("waza_eff_power	= %3d\n", btl_sys->waza_eff_power);
//	OS_Printf("waza_eff_natuki	= %3d\n", btl_sys->waza_eff_natuki);
//	OS_Printf("waza_eff_weather	= %3d\n", btl_sys->waza_eff_weather);
//	OS_Printf("waza_eff_cnt		= %3d\n", btl_sys->waza_eff_cnt);
//	OS_Printf("ground_id		= %3d\n", btl_sys->ground_id);
//	OS_Printf("at_client_no		= %3d\n", btl_sys->at_client_no);
//	OS_Printf("df_client_no		= %3d\n", btl_sys->df_client_no);
//	OS_Printf("□-----↑↑↑サーバーからもらうデータ↑↑↑-----□\n");
//	we_sys->btl_sys->waza_eff_cnt = 0;
#endif
	we_sys->btl_sys->csp				= wcbep->csp;
	GF_ASSERT(wcbep->csp != NULL);
	we_sys->bgl							= wcbep->bgl;
	we_sys->pfd							= wcbep->pfd;
	we_sys->btl_sys->fight_type			= wcbep->fight_type;
	
	for (i = 0; i < CLIENT_MAX; i++){
		we_sys->btl_sys->excp[i]		= wcbep->excp[i];
		we_sys->btl_sys->client_type[i] = wcbep->client_type[i];
		we_sys->btl_sys->ss[i] 		 	= wcbep->ss[i];
		we_sys->btl_sys->mons_no[i]		= wcbep->mons_no[i];
		we_sys->btl_sys->sex[i]			= wcbep->sex[i];
		we_sys->btl_sys->rare[i]		= wcbep->rare[i];
		we_sys->btl_sys->form_no[i]		= wcbep->form_no[i];
		we_sys->btl_sys->personal_rnd[i]= wcbep->personal_rnd[i];
		we_sys->btl_sys->waza_kouka[i]	= wcbep->waza_kouka[i];
	}
	
	we_sys->haikei_data					= wcbep->haikei_data;
	we_sys->btl_sys->perap_voice		= wcbep->perap_voice;
	we_sys->btl_sys->pal_area			= wcbep->pal_area;			///< パレット
	we_sys->btl_sys->bg_area			= wcbep->bg_area;			///< バトルの背景

	
	// ----- アーカイブからの取得 -----
	if (set_waza_no == WAZANO_HIMITUNOTIKARA){
		
		int HimitunoTikara_WazaTbl[] = {
			WAZANO_DOROKAKE,				///< 砂利(砂浜)		どろかけ
			WAZANO_DOROKAKE,				///< 砂利(砂浜)		どろかけ
			WAZANO_NIIDORUAAMU,				///< 芝生(水たまり)	ニードルアーム
			WAZANO_NIIDORUAAMU,				///< 芝生(水たまり)	ニードルアーム
			WAZANO_IWAOTOSI,				///< 岩肌(洞窟)		いわおとし
			WAZANO_IWAOTOSI,				///< 岩肌(洞窟)		いわおとし
			WAZANO_YUKINADARE,				///< 雪原			ゆきなだれ
			WAZANO_MIZUNOHADOU,				///< 水上			みずのはどう
			WAZANO_KOORINOTUBUTE,			///< 氷上			こおりつぶて
			WAZANO_NOSIKAKARI,				///< 床				のしかかり
			WAZANO_MADDOSYOTTO,				///< 沼地			マッドショット
			WAZANO_KAZEOKOSI,				///< 吊橋			かぜおこし
			WAZANO_NOSIKAKARI,				///< 以外			のしかかり
		};
		
		if (we_sys->btl_sys->waza_eff_ground_id >= GROUND_ID_ALL){
			set_waza_no = WAZANO_TORAIATAKKU;
		}
		else {
			set_waza_no = HimitunoTikara_WazaTbl[ we_sys->btl_sys->waza_eff_ground_id ];
		}		
	//	OS_Printf("[ 技 ]:ひみつのちから なので すりかえますよ。\n地形 = %2d\n技NO = %3d\n",we_sys->btl_sys->waza_eff_ground_id, set_waza_no);
	}
	
	if (set_waza_no == 0
	||	set_waza_no >  WAZANO_MAX){
		set_waza_no = WAZANO_HATAKU;
	}
#if 0
	if (wcbep->eff_arc_id == ARC_WAZA_EFF
	&&	WES_ContestFlag_Get(we_sys) == FALSE){
		GF_Disp_GXS_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_OFF);
	}
#endif
	we_sys->eff_arc_id	  = wcbep->eff_arc_id;
	we_sys->arc_data_adrs = ArchiveDataLoadMalloc(we_sys->eff_arc_id, set_waza_no, we_sys->heap_area );
	
	if (we_sys->arc_data_adrs == NULL){
		GF_ASSERT(we_sys->arc_data_adrs != NULL);
		return FALSE;
	}
	we_sys->waza_eff_seq_adrs = (u32*)we_sys->arc_data_adrs;

	// ----- BGプライオリティの保存
	we_sys->bg_pri[ 0 ] = GF_BGL_PriorityGet(we_sys->bgl, GF_BGL_FRAME0_M);
	we_sys->bg_pri[ 1 ] = GF_BGL_PriorityGet(we_sys->bgl, GF_BGL_FRAME1_M);
	we_sys->bg_pri[ 2 ] = GF_BGL_PriorityGet(we_sys->bgl, GF_BGL_FRAME2_M);
	we_sys->bg_pri[ 3 ] = GF_BGL_PriorityGet(we_sys->bgl, GF_BGL_FRAME3_M);
	
	// ----- OAMのCAP初期化 -----
	for (i = 0; i < WE_CAP_MAX; i++){
		we_sys->cap[i] = NULL;
	}

	for (i = 0; i < WE_POKE_CAP_MAX; i++){
		we_sys->poke_cap[i] = NULL;
		we_sys->poke_cap_use[i] = FALSE;
	}
	
	// ----- サブシステム -----
	we_sys->hc_sub_ptr = NULL;
	

	// ----- 実行関数の登録 -----
	we_sys->waza_eff_exe = WazaEffectExecuted;	///< 実行関数のアドレス

	we_sys->waza_eff_wait = 0;					///< エフェクト用ウェイト
	
	if (WES_ContestFlag_Get(we_sys) == TRUE){
		we_sys->haikei_fade_bit = ACTIN_HAIKEI_FADE_BIT;
	}
	else {
		we_sys->haikei_fade_bit = WES_HAIKEI_PAL;
	}
	
	we_sys->waza_eff_active = TRUE;				///< 技エフェクトの動作ON

	return TRUE;
}	

//--------------------------------------------------------------
/**
 * @brief	技エフェクトの実行
 *
 * @param	we_sys	WE_SYS のワーク
 *
 * @retval	BOOL	TRUE = 正常		FALSE = 異常
 *
 */
//--------------------------------------------------------------
BOOL WES_Executed(WE_SYS_PTR we_sys)
{
	// システムの動作状況チェック
	if (IsWES(we_sys) == FALSE){
		return FALSE;
	}
		
	we_sys->waza_eff_exe(we_sys);

	return TRUE;
}


//--------------------------------------------------------------
/**
 * @brief	技エフェクトの終了チェック
 *
 * @param	we_sys	
 *
 * @retval	BOOL	TRUE = 動作中	FALSE = 異常
 *
 */
//--------------------------------------------------------------
BOOL IsWES_Executed(WE_SYS_PTR we_sys)
{
	return (we_sys->waza_eff_active == TRUE) ? TRUE : FALSE;
}


//--------------------------------------------------------------
/**
 * @brief	エフェクトの初期化
 *
 * @param	we_sys	
 *
 * @retval	BOOL	TRUE = 正常		FALSE = 異常
 *
 */
//--------------------------------------------------------------
BOOL WES_Reset(WE_SYS_PTR we_sys)
{
	if (we_sys->arc_data_adrs == NULL){
		GF_ASSERT(we_sys->arc_data_adrs);
		return FALSE;
	}

	sys_FreeMemoryEz(we_sys->arc_data_adrs);
#if 0
#ifdef PM_DEBUG
	{
		u64 now_state;
		
		now_state = sys_GetHeapState( we_sys->heap_area );
		
#ifdef WE_SYS_DEBUG_ALLOC_SIZE_ON

		{		
			int cnt[2];
			cnt[0] = (now_state >> 32);
			cnt[1] = (g_nWazaEffectHeapState >> 32);
			OS_Printf("now cnt = %ld \n", cnt[0]);
			OS_Printf("old cnt = %ld \n", cnt[1]);
			OS_Printf("now siz = %ld \n", (now_state & 0x00000000FFFFFFFF));
			OS_Printf("old siz = %ld \n", (g_nWazaEffectHeapState & 0x00000000FFFFFFFF));
		}
#endif

		GF_ASSERT((g_nWazaEffectHeapState == now_state) && "不一致");
	}
#endif
#endif	
	return TRUE;
}


//--------------------------------------------------------------
/**
 * @brief	WE_SYSが動作中か？
 *
 * @param	we_sys	WE_SYSワーク
 *
 * @retval	BOOL	TRUE = 動作中 FALSE = 未動作、またはワークがNULL
 *
 */
//--------------------------------------------------------------
BOOL IsWES(WE_SYS_PTR we_sys)
{
	if (we_sys == NULL){
		return FALSE;
	}
	
	return (we_sys->active == TRUE) ? TRUE : FALSE;
}


//--------------------------------------------------------------
/**
 * @brief	WE-SYS用 エフェクトTCB作成
 *
 * @param	we_sys	
 * @param	func	
 * @param	work	
 * @param	pri	
 *
 * @retval	TCB_PTR	
 *
 */
//--------------------------------------------------------------
TCB_PTR WEEffect_TCB_Add(WE_SYS_PTR we_sys, TCB_FUNC func, void* work, u32 pri)
{
	TCB_PTR tcb;
	
	tcb = WazaEffectTCB_Add(ENUM_WETCB_EFFECT, we_sys, func, work, pri);
	
	return tcb;
}

TCB_PTR WEEffect_TCB_AddPriSet(WE_SYS_PTR we_sys, TCB_FUNC func, void* work)
{
	TCB_PTR tcb;
	
	tcb = WazaEffectTCB_Add(ENUM_WETCB_EFFECT, we_sys, func, work, TCBPRI_WE_SUPPORT);
	
	return tcb;
}


//--------------------------------------------------------------
/**
 * @brief	WE-SYS用 サウンドTCB作成
 *
 * @param	we_sys	
 * @param	func	
 * @param	work	
 * @param	pri	
 *
 * @retval	TCB_PTR	
 *
 */
//--------------------------------------------------------------
TCB_PTR WESound_TCB_Add(WE_SYS_PTR we_sys, TCB_FUNC func, void* work, u32 pri)
{
	TCB_PTR tcb;

	tcb = WazaEffectTCB_Add(ENUM_WETCB_SOUND, we_sys, func, work, pri);

	return tcb;
}

TCB_PTR WESound_TCB_AddPriSet(WE_SYS_PTR we_sys, TCB_FUNC func, void* work)
{
	TCB_PTR tcb;

	tcb = WazaEffectTCB_Add(ENUM_WETCB_SOUND, we_sys, func, work, TCBPRI_SE_CONTROL);

	return tcb;
}

//--------------------------------------------------------------
/**
 * @brief	WE-SYS用 エフェクト用TCB破棄
 *
 * @param	we_sys	
 * @param	tcb	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WEEffect_TCB_Delete(WE_SYS_PTR we_sys, TCB_PTR tcb)
{
	WazaEffectTCB_Delete(ENUM_WETCB_EFFECT, we_sys, tcb);
}


//--------------------------------------------------------------
/**
 * @brief	WE-SYS用 サウンドTCB破棄
 *
 * @param	we_sys	
 * @param	tcb	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WESound_TCB_Delete(WE_SYS_PTR we_sys, TCB_PTR tcb)
{
	WazaEffectTCB_Delete(ENUM_WETCB_SOUND, we_sys, tcb);
}





// =============================================================================
//
//
//	■戦闘用パラメーター引渡し関数
//
//
// =============================================================================
//--------------------------------------------------------------
/**
 * @brief	アタック側クライアント番号取得
 *
 * @param	we_sys	
 *
 * @retval	u16			アタック側クライアント番号取得
 *
 */
//--------------------------------------------------------------
u16 WeSysATNoGet(WE_SYS_PTR we_sys)
{
	return we_sys->btl_sys->at_client_no;
}


//--------------------------------------------------------------
/**
 * @brief	ディフェンス側クライアント番号取得
 *
 * @param	we_sys	
 *
 * @retval	u16			ディフェンス側クライアント番号取得
 *
 */
//--------------------------------------------------------------
u16 WeSysDFNoGet(WE_SYS_PTR we_sys)
{
	return we_sys->btl_sys->df_client_no;
}


//--------------------------------------------------------------
/**
 * @brief	PTCポインタ取得関数
 *
 * @param	we_sys	
 *
 * @retval	PTC_PTR		PTCポインタ取得関数
 *
 */
//--------------------------------------------------------------
PTC_PTR WeSysPTCPointerGet(WE_SYS_PTR we_sys)
{
	return we_sys->btl_sys->ptc[we_sys->btl_sys->this_ptc_no];
}

PTC_PTR WeSysPTCPointerNoGet(WE_SYS_PTR we_sys, int no)
{
	return we_sys->btl_sys->ptc[no];
}

//--------------------------------------------------------------
/**
 * @brief	エミッターのポインタ取得
 *
 * @param	we_sys	
 * @param	no	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
EMIT_PTR WeSysEMITPointerGet(WE_SYS_PTR we_sys, int no)
{
	EMIT_PTR emit;
	
	emit = we_sys->btl_sys->emit[no];
	
	return emit;
}


//--------------------------------------------------------------
/**
 * @brief	BGLのポインタ取得関数
 *
 * @param	we_sys	
 *
 * @retval	BGL_INI*	
 *
 */
//--------------------------------------------------------------
GF_BGL_INI* WeSysBGLPointerGet(WE_SYS_PTR we_sys)
{
	return we_sys->bgl;
}


//--------------------------------------------------------------
/**
 * @brief	汎用ワークの値を取得
 *
 * @param	we_sys	
 * @param	no	
 *
 * @retval	s32	
 *
 */
//--------------------------------------------------------------
s32 WeSysGPWorkGet(WE_SYS_PTR we_sys, int no)
{
	GF_ASSERT(no < WE_GENE_WK_MAX);
	
	return we_sys->waza_eff_gp_wk[no];
}


//--------------------------------------------------------------
/**
 * @brief	OAMのCAPを取得
 *
 * @param	we_sys	
 * @param	no	
 *
 * @retval	CATS_ACT_PTR	
 *
 */
//--------------------------------------------------------------
CATS_ACT_PTR WeSysOamCapGet(WE_SYS_PTR we_sys, int no)
{
	GF_ASSERT( no < WE_CAP_MAX );
	GF_ASSERT(we_sys != NULL);
	GF_ASSERT(we_sys->cap[ no ] != NULL);

	return we_sys->cap[ no ];
}


//--------------------------------------------------------------
/**
 * @brief	ポケモンのCAPを取得する
 *
 * @param	we_sys			
 * @param	no					番号
 *
 * @retval	CATS_ACT_PTR	
 *
 */
//--------------------------------------------------------------
CATS_ACT_PTR WeSysPokeCapGet(WE_SYS_PTR we_sys, int no)
{
	GF_ASSERT( no < WE_POKE_CAP_MAX );
	GF_ASSERT(we_sys != NULL);
	GF_ASSERT(we_sys->poke_cap[ no ] != NULL);

	return we_sys->poke_cap[ no ];
}


//--------------------------------------------------------------
/**
 * @brief	ポケモンのCRPを取得する
 *
 * @param	we_sys	
 *
 * @retval	CATS_RES_PTR	
 *
 */
//--------------------------------------------------------------
CATS_RES_PTR WeSysPokeCrpGet(WE_SYS_PTR we_sys)
{
	GF_ASSERT(we_sys != NULL);

	return we_sys->poke_crp;
}


//--------------------------------------------------------------
/**
 * @brief	CRPを取得する 0だけ
 *
 * @param	we_sys	
 *
 * @retval	CATS_RES_PTR	
 *
 */
//--------------------------------------------------------------
CATS_RES_PTR WeSysCrpGet(WE_SYS_PTR we_sys)
{
	return we_sys->crp[0];
}


//--------------------------------------------------------------
/**
 * @brief	CSPの取得
 *
 * @param	we_sys	
 *
 * @retval	CATS_SYS_PTR	
 *
 */
//--------------------------------------------------------------
CATS_SYS_PTR WeSysCspGet(WE_SYS_PTR we_sys)
{
	return we_sys->btl_sys->csp;
}

// =============================================================================
//
//
//
//	■サウンドコントロール関連	[ _SOUND_CONTROL_ ]
//
//
//
// =============================================================================
static SE_SYS_PTR SeControlInit(WE_SYS_PTR we_sys);
static void	SeControlStart(WE_SYS_PTR we_sys, SE_SYS_PTR ss);

static void SeControl_MainTCB(TCB_PTR tcb, void* work);

static BOOL	SeControl_None(SE_SYS_PTR ss);

static BOOL SeControl_PanFlow(SE_SYS_PTR ss);
static BOOL SeControl_PanFlowFix(SE_SYS_PTR ss);
static BOOL SeControl_PanFlowAF(SE_SYS_PTR ss);

static BOOL SeControl_Repeat(SE_SYS_PTR ss);
static BOOL SeControl_WaitPlay(SE_SYS_PTR ss);

// -----------------------------------------
//
//
//	■サウンド用のTCBリスト
//
//
// -----------------------------------------
static BOOL (* const SeControlTCB[])(SE_SYS_PTR ss) = {

	SeControl_None,			// 動作なし
	SeControl_PanFlow,		// パンの変更
	SeControl_PanFlowFix,	// PanFlowと内部は同じ動き
	SeControl_PanFlowAF,	// PanFlowと内部は同じ動き
	
	SeControl_Repeat,		// リピート
	SeControl_WaitPlay,		// wait分待ってから再生
};


//--------------------------------------------------------------
/**
 * @brief	サウンドコントロールの初期化
 *
 * @param	we_sys
 *
 * @retval	static SE_SYS_PTR	
 *
 */
//--------------------------------------------------------------
static SE_SYS_PTR SeControlInit(WE_SYS_PTR we_sys)
{
	SE_SYS_PTR ss = NULL;
	
	ss = sys_AllocMemory(we_sys->heap_area, sizeof(TSE_SYS));
	
	if (ss == NULL){
		GF_ASSERT(0 && "SeControlの初期化失敗");
		return NULL;
	}
	memset(ss, 0, sizeof(TSE_SYS));
	
	we_sys->waza_se_num++;
	
	return ss;
}


//--------------------------------------------------------------
/**
 * @brief	サウンドコントロールTCB作成
 *
 * @param	ss	
 *
 * @retval	static	
 *
 */
//--------------------------------------------------------------
static void	SeControlStart(WE_SYS_PTR we_sys, SE_SYS_PTR ss)
{
	ss->we_sys = we_sys;
	
	TCB_Add(SeControl_MainTCB, ss, TCBPRI_SE_CONTROL);
}


//--------------------------------------------------------------
/**
 * @brief	SEコントロールの分岐TCB
 *
 * @param	tcb	
 * @param	work	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void SeControl_MainTCB(TCB_PTR tcb, void* work)
{
	BOOL active;
	SE_SYS_PTR ss = (SE_SYS_PTR)work;
	
	active = SeControlTCB[ss->mode](ss);
	
	if (active == FALSE){
		if (ss->we_sys->waza_se_num != 0){
			ss->we_sys->waza_se_num--;
		}
		sys_FreeMemoryEz(ss);
		TCB_Delete(tcb);
	}
}


//--------------------------------------------------------------
/**
 * @brief	SEコントロール ダミー
 *
 * @param	ss	
 *
 * @retval	static	
 *
 */
//--------------------------------------------------------------
static BOOL	SeControl_None(SE_SYS_PTR ss)
{
	return FALSE;
}


//--------------------------------------------------------------
/**
 * @brief	SEコントロール PanFlow
 *
 * @param	ss	
 *
 * @retval	static	
 *
 */
//--------------------------------------------------------------
static BOOL	SeControl_PanFlow(SE_SYS_PTR ss)
{
	BOOL active;
	s8	now_pan;
	
	if (ss->gene_wait++ < ss->wait){
		return TRUE;
	}
	
	active = TRUE;
	ss->gene_wait = 0;

	//ss->n_pan = ss->s_pan;
	ss->n_pan += ss->a_pan;
	
	if (ss->a_pan == 0){
		active = FALSE;	
	}
	else if (ss->s_pan < ss->e_pan){
		if (ss->n_pan >= ss->e_pan){
			active = FALSE;
		}
	}
	else {
		if (ss->n_pan <= ss->e_pan){
			active = FALSE;
		}
	}
	
	Snd_SePanSetAll(ss->n_pan);
	
//	OS_Printf("現在のパンの設定 ･･･ %4d\n", ss->n_pan);
	
	if (Snd_SePlayCheck(ss->se_no) == FALSE){
		if (active == TRUE){
//			OS_Printf("パンの移動が終わってないが、ＳＥがなり終わっているのでＴＣＢを終了\n");
		}		
		return FALSE;
	}
	
	return active;
}


//--------------------------------------------------------------
/**
 * @brief	SEコントロール PanFlowFix
 *
 * @param	ss	
 *
 * @retval	static	
 *
 */
//--------------------------------------------------------------
static BOOL	SeControl_PanFlowFix(SE_SYS_PTR ss)
{
	return SeControl_PanFlow(ss);
}


//--------------------------------------------------------------
/**
 * @brief	SEコントロール PanFlowAF
 *
 * @param	ss	
 *
 * @retval	static	
 *
 */
//--------------------------------------------------------------
static BOOL	SeControl_PanFlowAF(SE_SYS_PTR ss)
{
	return SeControl_PanFlow(ss);
}


//--------------------------------------------------------------
/**
 * @brief	SEコントロール Repeat
 *
 * @param	ss	
 *
 * @retval	static int	
 *
 */
//--------------------------------------------------------------
static BOOL SeControl_Repeat(SE_SYS_PTR ss)
{
	BOOL active;
	
	if (ss->gene_wait++ < ss->wait){
		return TRUE;
	}
	
	active = TRUE;
	ss->gene_wait = 0;

	ss->repeat--;

	Snd_SePlay(ss->se_no);
	Snd_SePanSet(ss->se_no, 0xffff, ss->n_pan);
	
	if (ss->repeat == 0){
		active = FALSE;
	}
	
	return active;
}


//--------------------------------------------------------------
/**
 * @brief	wait分待ってからSEを再生する
 *
 * @param	ss	
 *
 * @retval	static BOOL	
 *
 */
//--------------------------------------------------------------
static BOOL SeControl_WaitPlay(SE_SYS_PTR ss)
{
	BOOL active;
	
	active = TRUE;
	
	if ((ss->wait--) == 0){
		
		Snd_SePlay(ss->se_no);
		Snd_SePanSet(ss->se_no, 0xffff, ss->n_pan);
	
		active = FALSE;
	}

	return active;
}












// =============================================================================
//
//
//
//	■コマンド	[ _COMMAND_ ]
//
//
//
// =============================================================================
// =============================================================================
//
//
//	■プロトタイプ宣言
//
//
// =============================================================================
static void WEST_WAIT(WE_SYS_PTR we_sys);
static void WEST_WAIT_FLAG(WE_SYS_PTR we_sys);
static void WEST_LOOP_LABEL(WE_SYS_PTR we_sys);
static void WEST_LOOP(WE_SYS_PTR we_sys);
static void WEST_SEQEND(WE_SYS_PTR we_sys);
static void WEST_SE(WE_SYS_PTR we_sys);
static void WEST_POKEBG(WE_SYS_PTR we_sys);
static void WEST_POKEBG_RESET(WE_SYS_PTR we_sys);
static void WEST_BLDALPHA_SET(WE_SYS_PTR we_sys);
static void WEST_BLDALPHA_RESET(WE_SYS_PTR we_sys);
static void WEST_SEQ_CALL(WE_SYS_PTR we_sys);
static void WEST_END_CALL(WE_SYS_PTR we_sys);
static void WEST_WORK_SET(WE_SYS_PTR we_sys);
static void WEST_WORK_CLEAR(WE_SYS_PTR we_sys);
static void WEST_HENSIN_ON(WE_SYS_PTR we_sys);
static void WEST_HENSIN_ON_RC(WE_SYS_PTR we_sys);
static void WEST_TURN_CHK(WE_SYS_PTR we_sys);
static void WEST_TURN_JP(WE_SYS_PTR we_sys);
static void WEST_SEQ_JP(WE_SYS_PTR we_sys);
static void WEST_HAIKEI_CHG(WE_SYS_PTR we_sys);
static void WEST_HAIKEI_PARA_CHG(WE_SYS_PTR we_sys);
static void WEST_HAIKEI_RECOVER(WE_SYS_PTR we_sys);
static void WEST_HAIKEI_HALF_WAIT(WE_SYS_PTR we_sys);
static void WEST_HAIKEI_CHG_WAIT(WE_SYS_PTR we_sys);
static void WEST_HAIKEI_SET(WE_SYS_PTR we_sys);
static void WEST_SEPLAY_PAN(WE_SYS_PTR we_sys);
static void WEST_SEPAN(WE_SYS_PTR we_sys);
static void WEST_SEPAN_FLOW(WE_SYS_PTR we_sys);
static void WEST_SE_REPEAT(WE_SYS_PTR we_sys);
static void WEST_SE_WAITPLAY(WE_SYS_PTR we_sys);
static void WEST_BLDCNT_SET(WE_SYS_PTR we_sys);
static void WEST_SE_TASK(WE_SYS_PTR we_sys);
static void WEST_SEWAIT_FLAG(WE_SYS_PTR we_sys);
static void WEST_WORKCHK_JP(WE_SYS_PTR we_sys);
static void WEST_POKEBG_DROP(WE_SYS_PTR we_sys);
static void WEST_POKEOAM_RES_INIT(WE_SYS_PTR we_sys);
static void WEST_POKEOAM_RES_LOAD(WE_SYS_PTR we_sys);
static void WEST_POKEOAM_DROP(WE_SYS_PTR we_sys);
static void WEST_POKEOAM_RES_FREE(WE_SYS_PTR we_sys);
static void WEST_POKEOAM_DROP_RESET(WE_SYS_PTR we_sys);
static void WEST_POKEOAM_AUTO_STOP(WE_SYS_PTR we_sys);
static void WEST_CAMERA_CHG(WE_SYS_PTR we_sys);
static void WEST_CAMERA_REVERCE(WE_SYS_PTR we_sys);
static void WEST_POKEBG_DROP_RESET(WE_SYS_PTR we_sys);
static void WEST_CONTEST_CHK_JP(WE_SYS_PTR we_sys);
static void WEST_HAIKEI_CHKCHG(WE_SYS_PTR we_sys);
static void WEST_SEPAN_FLOWFIX(WE_SYS_PTR we_sys);
static void WEST_SEPAN_FLOW_AF(WE_SYS_PTR we_sys);
static void WEST_BGPRI_GAPSET(WE_SYS_PTR we_sys);
static void WEST_BGPRI_GAPSET2(WE_SYS_PTR we_sys);
static void WEST_BGPRI_GAPSET3(WE_SYS_PTR we_sys);
static void WEST_POKE_BANISH_ON(WE_SYS_PTR we_sys);
static void WEST_POKE_BANISH_OFF(WE_SYS_PTR we_sys);
static void WEST_PARTY_ATTACK_BGOFF(WE_SYS_PTR we_sys);
static void WEST_PARTY_ATTACK_BGEND(WE_SYS_PTR we_sys);
static void WEST_SE_STOP(WE_SYS_PTR we_sys);
static void WEST_SIDE_JP(WE_SYS_PTR we_sys);
static void WEST_TENKI_JP(WE_SYS_PTR we_sys);
static void WEST_CONTEST_JP(WE_SYS_PTR we_sys);
static void WEST_PTAT_JP(WE_SYS_PTR we_sys);
static void WEST_VOICE_PLAY(WE_SYS_PTR we_sys);
static void WEST_VOICE_WAIT_STOP(WE_SYS_PTR we_sys);

/// 新規コマンド
static void WEST_FUNC_CALL(WE_SYS_PTR we_sys);
static void WEST_ADD_PARTICLE(WE_SYS_PTR we_sys);
static void WEST_ADD_PARTICLE_EMIT_SET(WE_SYS_PTR we_sys);
static void WEST_ADD_PARTICLE_SEP(WE_SYS_PTR we_sys);
static void WEST_ADD_PARTICLE_PTAT(WE_SYS_PTR we_sys);
static void WEST_WAIT_PARTICLE(WE_SYS_PTR we_sys);
static void WEST_LOAD_PARTICLE(WE_SYS_PTR we_sys);
static void WEST_LOAD_PARTICLE_EX(WE_SYS_PTR we_sys);
static void WEST_EXIT_PARTICLE(WE_SYS_PTR we_sys);
static void WEST_EX_DATA(WE_SYS_PTR we_sys);
static void WEST_OLDACT_FUNC_CALL(WE_SYS_PTR we_sys);

/// CLACT 関連コマンド
static void WEST_CATS_RES_INIT(WE_SYS_PTR we_sys);
static void WEST_CATS_CHAR_RES_LOAD(WE_SYS_PTR we_sys);
static void WEST_CATS_PLTT_RES_LOAD(WE_SYS_PTR we_sys);
static void WEST_CATS_CELL_RES_LOAD(WE_SYS_PTR we_sys);
static void WEST_CATS_CELL_ANM_RES_LOAD(WE_SYS_PTR we_sys);
static void WEST_CATS_ACT_ADD(WE_SYS_PTR we_sys);
static void WEST_CATS_ACT_ADD_EZ(WE_SYS_PTR we_sys);
static void WEST_CATS_RES_FREE(WE_SYS_PTR we_sys);
static void WEST_POKE_OAM_ENABLE(WE_SYS_PTR we_sys);

static void WEST_PT_DROP(WE_SYS_PTR we_sys);
static void WEST_PT_DROP_RESET(WE_SYS_PTR we_sys);


/// デバッグ
static void WEST_KEY_WAIT(WE_SYS_PTR we_sys);

/// インライン関数
static inline TAP  AdrsParamGetEx(u32* adrs, u8 s_byte, u8 byte);	///< データ取得
static inline TAP  AdrsParamGet(u32* adrs, u8 byte);					///< データ取得
static inline TAP  SeqAdrsGet(u32* adrs);							///< データ取得


















// =============================================================================
//
//
//	■テーブル	[ _COMMAND_TABLE_ ]
//
//
// =============================================================================
static const pWeFunc WazaEffectCmdList[] = {
	WEST_WAIT,
	WEST_WAIT_FLAG,
	WEST_LOOP_LABEL,
	WEST_LOOP,
	WEST_SEQEND,
	WEST_SE,
	WEST_POKEBG,
	WEST_POKEBG_RESET,
	WEST_BLDALPHA_SET,
	WEST_BLDALPHA_RESET,
	WEST_SEQ_CALL,
	WEST_END_CALL,
	WEST_WORK_SET,
	WEST_TURN_CHK,
	WEST_TURN_JP,
	WEST_SEQ_JP,
	WEST_HAIKEI_CHG,
	WEST_HAIKEI_PARA_CHG,
	WEST_HAIKEI_RECOVER,
	WEST_HAIKEI_HALF_WAIT,
	WEST_HAIKEI_CHG_WAIT,
	WEST_HAIKEI_SET,
	WEST_SEPLAY_PAN,
	WEST_SEPAN,
	WEST_SEPAN_FLOW,
	WEST_SE_REPEAT,
	WEST_SE_WAITPLAY,
	WEST_BLDCNT_SET,
	WEST_SE_TASK,
	WEST_SEWAIT_FLAG,
	WEST_WORKCHK_JP,
	WEST_POKEBG_DROP,
	WEST_POKEBG_DROP_RESET,
	WEST_CONTEST_CHK_JP,
	WEST_HAIKEI_CHKCHG,
	WEST_SEPAN_FLOWFIX,
	WEST_SEPAN_FLOW_AF,
	WEST_BGPRI_GAPSET,
	WEST_BGPRI_GAPSET2,
	WEST_BGPRI_GAPSET3,
	WEST_POKE_BANISH_ON,
	WEST_POKE_BANISH_OFF,
	WEST_PARTY_ATTACK_BGOFF,
	WEST_PARTY_ATTACK_BGEND,
	WEST_SE_STOP,
	
	// 新規登録
	WEST_FUNC_CALL,				///< 指定された関数を呼び出す
	WEST_ADD_PARTICLE,			///< パーティクルを登録する
	WEST_ADD_PARTICLE_EMIT_SET,	///< パーティクルエミッタ指定バージョン
	WEST_ADD_PARTICLE_SEP,		///< パーティクルエミッタ指定 分岐
	WEST_ADD_PARTICLE_PTAT,		///< パーティクルエミッタ指定 分岐
	WEST_WAIT_PARTICLE,			///< パーティクルの終了待ち
	WEST_LOAD_PARTICLE,			///< パーティクルのリソース読み込み
	WEST_LOAD_PARTICLE_EX,		///< パーティクルのリソース読み込み
	WEST_EXIT_PARTICLE,			///< パーティクルのリソース解放
	WEST_OLDACT_FUNC_CALL,		///< 旧技エフェクト互換用アクター生成関数呼び出し
	WEST_EX_DATA,				///< データ列定義
	WEST_POKEOAM_RES_INIT,		///< ポケモンをOAMに落とすためのリソース作成
	WEST_POKEOAM_RES_LOAD,		///< ポケモンをOAMに落とすためのリソース作成
	WEST_POKEOAM_DROP,			///< ポケモンをOAMに落とす
	WEST_POKEOAM_RES_FREE,		///< ポケモンをOAMに落とすために使用したリソース解放
	WEST_POKEOAM_DROP_RESET,	///< ポケモンのOAM解放
	WEST_POKEOAM_AUTO_STOP,		///< ポケモンをOAMの自動追尾の停止
	WEST_CAMERA_CHG,			///< カメラのモード設定
	WEST_CAMERA_REVERCE,		///< カメラ反転
	WEST_SIDE_JP,				///< サイドの位置でジャンプする
	WEST_VOICE_PLAY,			///< 鳴き声 再生
	WEST_VOICE_WAIT_STOP,		///< 鳴き声 待ち＋停止
	WEST_WORK_CLEAR,			///< ワーク初期化
	WEST_HENSIN_ON,				///< 変身
	WEST_HENSIN_ON_RC,			///< 変身もどし
	WEST_TENKI_JP,				///< 天気ジャンプ
	WEST_CONTEST_JP,			///< コンテストジャンプ
	WEST_PTAT_JP,				///< パーティアタック

	WEST_CATS_RES_INIT,			///< リソース初期化
	WEST_CATS_CHAR_RES_LOAD,	///< リソース読み込み
	WEST_CATS_PLTT_RES_LOAD,	///< リソース読み込み
	WEST_CATS_CELL_RES_LOAD,	///< リソース読み込み
	WEST_CATS_CELL_ANM_RES_LOAD,///< リソース読み込み
	WEST_CATS_ACT_ADD,			///< OBJ登録
	WEST_CATS_ACT_ADD_EZ,		///< OBJ登録
	WEST_CATS_RES_FREE,			///< リソース解放
	WEST_POKE_OAM_ENABLE,
	WEST_PT_DROP,
	WEST_PT_DROP_RESET,
	
	// ----- デバッグ用はココから定義 -----
	WEST_KEY_WAIT,			///< デバッグ
};

#define EFFECT_CMD_MAX	(NELEMS(WazaEffectCmdList))








// =============================================================================
//
//
//	■インライン関数・マクロ	[ _INLINE_MACRO_ ]
//
//
// =============================================================================
//--------------------------------------------------------------
/**
 * @brief	基本ブレンド設定を行なう
 *
 * @param	none	
 *
 * @retval	static inline void	
 *
 */
#define BATTLE_DEFAULT_BLEND_PLANE_1	(GX_BLEND_PLANEMASK_NONE)
#define BATTLE_DEFAULT_BLEND_PLANE_2	(GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG2 |	\
										 GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BD)
#define BATTLE_DEFAULT_BLEND_EV_1		(8)
#define BATTLE_DEFAULT_BLEND_EV_2		(8)
//--------------------------------------------------------------
void DefaultBlendSet(void)
{	
	G2_SetBlendAlpha(BATTLE_DEFAULT_BLEND_PLANE_1,
					  BATTLE_DEFAULT_BLEND_PLANE_2,
					  BATTLE_DEFAULT_BLEND_EV_1,
					  BATTLE_DEFAULT_BLEND_EV_2);
}

//--------------------------------------------------------------
/**
 * @brief	指定バイト数データを取得
 *
 * @param	adrs	取得する対象アドレス
 * @param	s_byte	開始するバイト位置
 * @param	byte	取得するバイト数
 *
 * @retval	TAP	値
 *
 */
//--------------------------------------------------------------
static inline TAP AdrsParamGetEx(u32* adrs, u8 s_byte, u8 byte)
{
	TAP val = adrs[s_byte];
	
	if (byte != 1){
		GF_ASSERT(0);
#ifdef WE_SYS_INF_OS_PRINT
//		OS_Printf("AdrsParamGetEx --- byte != 1 err!\n");
#endif
	}
	
	return val;
	
#if 0
	///< u8 指定バイトだけ取得するためのもの
	///< 現在は、4byte固定なので特に必要なし
	int i;
	TAP val;
	
	// 型より指定byteが大きい場合エラー
	if (byte > sizeof(TAP)){
		OS_Printf("byte size over\n");
	}

	val = adrs[s_byte];
	
	for (i = s_byte + 1; i < s_byte + byte; i++){
		val += (adrs[i] << (i * 8));
	}
	
	return val;
#endif
}


//--------------------------------------------------------------
/**
 * @brief	指定バイト数データを取得
 *
 * @param	adrs	取得する対象アドレス
 * @param	byte	取得するバイト数
 *
 * @retval	TAP		値
 *
 */
//--------------------------------------------------------------
static inline TAP AdrsParamGet(u32* adrs, u8 byte)
{
	TAP val;

	val = AdrsParamGetEx(adrs, 0, byte);

	return val;
}


//--------------------------------------------------------------
/**
 * @brief	シーケンスアドレスを取得
 *
 * @param	adrs	取得する対象アドレス
 *
 * @retval	TAP		値
 *
 */
//--------------------------------------------------------------
static inline TAP SeqAdrsGet(u32* adrs)
{
	return AdrsParamGet(adrs, 1);
}


// ----------------------------------------
//
//	指定サイズ分アドレスを進めるマクロ
//		進めるアドレスの型に依存する
//
// -----------------------------------------
#define ADRS_CMD(n, m)			((n) += (m))


// -----------------------------------------
//
//	型サイズ分アドレスを進めるマクロ
//		最小単位でアドレスが進む
//		ADRS_CMD を利用するので型に依存する
//
// -----------------------------------------
#define ADRS_SHIFT(n)			(ADRS_CMD(n, 1))





// =============================================================================
//
//
//	■内部参照	[ _COMMAND_LIST_ ]
//
//	検索用コマンドラベル
//
//		[ _DEBUG_TOOL_ ]			デバッグ・コマンド系			
//		[ _COMMAND_TOOL_ ]			ツール関連
//		[ _COMMAND_PARTICLE_ ]		パーティクル関連
//		[ _COMMAND_JUMP_ ]			ジャンプ関連
//		[ _COMMAND_POKEMON_ ]		ポケモン関連
//		[ _COMMAND_BG_ ]			BG操作関連
//		[ _COMMAND_SOUND_ ]			サウンド関連
//		[ _COMMAND_REG_ ]			レジスタ操作関連
//		[ _COMMAND_CLACT_ ]			アクター操作関連
//
//
// =============================================================================
// =========================================
//
//	■デバッグ・コマンド系
//		[ _DEBUG_TOOL_ ]
//
// =========================================
static void WEST_KEY_WAIT(WE_SYS_PTR we_sys)
{
	we_sys->waza_eff_wait = 1;
	
//	OS_Printf("we_sys内でKEY_WAITが実行されています。\n[ L ] + [ START ]で抜けます。\n");
	
	if(sys.cont & PAD_BUTTON_L){					///< エフェクト0まで待つ
		if(sys.cont & PAD_BUTTON_R){
			if (sys.trg & PAD_BUTTON_X){
				ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
				we_sys->waza_eff_wait = 0;	
			}
		}
	}
}


//--------------------------------------------------------------
/**
 * @brief	ウェイトを設定して、WazaEffWait へ遷移
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_WAIT(WE_SYS_PTR we_sys)
{
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	we_sys->waza_eff_wait = (u8)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	we_sys->waza_eff_exe = WazaEffectWait;
}


//--------------------------------------------------------------
/**
 * @brief	エフェクトが終了するまで、ウェイトを設定する
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_WAIT_FLAG(WE_SYS_PTR we_sys)
{
	if (we_sys->waza_eff_num == 0){					///< エフェクト0まで待つ
		ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
		we_sys->waza_eff_wait = 0;	
	}
	else {											///< エフェクトが存在するなら
		we_sys->waza_eff_wait = 1;					///< 常に1入れておくことでスキップできる
	}
}


//--------------------------------------------------------------
/**
 * @brief	ワークに値をセットする
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_WORK_SET(WE_SYS_PTR we_sys)
{
	u32	index;
	u32 param;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	index = (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	param = (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	if (index < WE_GENE_WK_MAX){
		we_sys->waza_eff_gp_wk[index] = param;
		return;
	}
}


//--------------------------------------------------------------
/**
 * @brief	ワーク初期化
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_WORK_CLEAR(WE_SYS_PTR we_sys)
{
	int i;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	for (i = 0; i < WE_GENE_WK_MAX; i++){
		we_sys->waza_eff_gp_wk[i] = 0;
	}
}

int WazaEffParaGet(WE_SYS_PTR we_sys, int para_id)
{
	int dat = 0;
	
	switch(para_id){
	case WE_PARA_DAMAGE:
		dat = we_sys->btl_sys->waza_eff_damage;
		break;
	case WE_PARA_POW:
		dat = we_sys->btl_sys->waza_eff_power;
		break;
	case WE_PARA_NATUKI:
		dat = we_sys->btl_sys->waza_eff_natuki;
		break;
	case WE_PARA_WEATHER:
		dat = we_sys->btl_sys->waza_eff_weather;
		break;
	case WE_PARA_TURN:
		dat = we_sys->btl_sys->waza_eff_cnt;
		break;
	case WE_PARA_GROUND_ID:
		dat = we_sys->btl_sys->waza_eff_ground_id;
		break;
	default:
		dat = 0;
		break;
	}
	
	return dat;
}
void WeSys_PokeChangeParamMake(WE_SYS_PTR we_sys, WAZA_POKE_CHANGE_PARAM* para, int type)
{
	int i;
	
	for (i = 0; i < CLIENT_MAX; i++){
		para->excp[ i ] 		= we_sys->btl_sys->excp[ i ];
		para->ss[ i ]			= we_sys->btl_sys->ss[ i ];
		para->mons_no[ i ]		= we_sys->btl_sys->mons_no[ i ];
		para->sex[ i ]			= we_sys->btl_sys->sex[ i ];
		para->rare[ i ]			= we_sys->btl_sys->rare[ i ];
		para->form_no[ i ]		= we_sys->btl_sys->form_no[ i ];
		para->personal_rnd[ i ]	= we_sys->btl_sys->personal_rnd[ i ];
		para->client_type[ i ]	= we_sys->btl_sys->client_type[ i ];
	}
	
	switch(type){
	case WE_HENSIN_DF:
		para->at_client_no = we_sys->btl_sys->at_client_no;
		para->df_client_no = we_sys->btl_sys->df_client_no;
		break;
		
	case WE_HENSIN_AT:
		para->at_client_no = we_sys->btl_sys->at_client_no;
		para->df_client_no = we_sys->btl_sys->at_client_no;
		break;
		
	case WE_HENSIN_MIGAWARI:
		para->at_client_no = we_sys->btl_sys->at_client_no;
		para->df_client_no = we_sys->btl_sys->at_client_no;
		break;
			
	case WE_HENSIN_YOKODORI:
		para->at_client_no = we_sys->btl_sys->at_client_no;
		para->df_client_no = we_sys->btl_sys->at_client_no;
		break;
		
	default:
		OS_Printf("変身方法が未設定\n");
		GF_ASSERT(0);
		break;
	}
}

//--------------------------------------------------------------
/**
 * @brief	
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_HENSIN_ON(WE_SYS_PTR we_sys)
{
	int type;
	
	WAZA_POKE_CHANGE_PARAM para;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	type = (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	WeSys_PokeChangeParamMake(we_sys, &para, type);
	
	if (type == WE_HENSIN_MIGAWARI){
		MigawariChrSet(&para, we_sys->heap_area);
	}
	else if (type == WE_HENSIN_YOKODORI){
		YokodoriChrSet(&para, we_sys->heap_area);
	}
	else {
		HenshinChrSet(&para, we_sys->heap_area);
	}
}


//--------------------------------------------------------------
/**
 * @brief	
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_HENSIN_ON_RC(WE_SYS_PTR we_sys)
{
	int type;
	
	WAZA_POKE_CHANGE_PARAM para;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	type = (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	WeSys_PokeChangeParamMake(we_sys, &para, type);
	
	HenshinChrPop(&para, we_sys->heap_area);
}


//--------------------------------------------------------------
/**
 * @brief	ループラベル
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_LOOP_LABEL(WE_SYS_PTR we_sys)
{
	int i;

	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	///< ループラベルの位置を作成
	for (i = 0; i < WE_LOOP_MAX; i++){
		if (we_sys->loop[i].active == TRUE){ continue; }
		
		we_sys->loop[i].active = TRUE;
		we_sys->loop[i].n_cnt  = 0;
		we_sys->loop[i].e_cnt  = (u8)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
		ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
		
		we_sys->loop[i].seq_adrs = we_sys->waza_eff_seq_adrs;
		return;
	}
}


//--------------------------------------------------------------
/**
 * @brief	ループ
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_LOOP(WE_SYS_PTR we_sys)
{
	int i;

	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	for (i = WE_LOOP_MAX - 1; i >= 0; i--){
		if (we_sys->loop[i].active == FALSE){ continue; }

		we_sys->loop[i].n_cnt++;
		
		if (we_sys->loop[i].n_cnt == we_sys->loop[i].e_cnt){	///< 指定回数ループした
			we_sys->loop[i].active = FALSE;
		}
		else {													///< ループ回数が残っている
			we_sys->waza_eff_seq_adrs = we_sys->loop[i].seq_adrs;
		}
		return;
	}
}


//--------------------------------------------------------------
/**
 * @brief	コマンド終了
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_SEQEND(WE_SYS_PTR we_sys)
{
	int i;
	int em_num = 0;
	
	if (we_sys->free_time < 1){
		we_sys->waza_eff_wait = 1;
		we_sys->free_time++;
		return;
	}
	
	for (i = 0; i < PARTICLE_GLOBAL_MAX; i++){
		if (we_sys->btl_sys->ptc[i]){
			em_num += Particle_GetEmitterNum(we_sys->btl_sys->ptc[i]);
		}
	}

	// -------------------------------------
	//
	//	エフェクトなどの終了チェック
	//
	// -------------------------------------
	if (em_num != 0										///< エミッターの数が0じゃない
	||	we_sys->waza_eff_num != 0						///< 何かエフェクトが出ている
	||	we_sys->waza_se_num  != 0						///< SEが再生されている
	){
		we_sys->waza_eff_wait = 1;						///< wait = 1
		we_sys->se_end_timer  = 0;						///< timer = 0
		return;
	}

	// -------------------------------------
	//
	//	SEの再生チェック
	//
	// -------------------------------------
	if (Snd_SePlayCheckAll()){							///< SEが再生されていた場合
		we_sys->se_end_timer++;

		if (we_sys->se_end_timer > WE_SE_END_TIMER){	///< 終了3秒は待つ
			// エフェクト関連SEをとめる
			;
			;
			we_sys->se_end_timer = 0;
			we_sys->waza_eff_wait = 0;
		}
		else {
			we_sys->waza_eff_wait = 1;
			return;
		}
	}
	we_sys->se_end_timer = 0;
	we_sys->free_time = 0;
	
	// -------------------------------------
	//
	//	システム部分クリア
	//
	// -------------------------------------
	for (i = 0; i < WE_JUMP_MAX; i++){					///< jump先アドレス初期化
		we_sys->waza_eff_seq_adrs_j[i] = NULL;
	}
	
	for (i = 0; i < WE_LOOP_MAX; i++){					///< loop先アドレス初期化など
		we_sys->loop[i].seq_adrs = NULL;
		we_sys->loop[i].n_cnt 	 = 0;
		we_sys->loop[i].e_cnt	 = 0;
		we_sys->loop[i].active	 = FALSE;
	}
	
	for (i = 0; i < WE_CRP_MAX; i++){					///< CLACT用ワークの初期化
		if (we_sys->crp[i] != NULL){
			CATS_ResourceDestructor_S(we_sys->btl_sys->csp, we_sys->crp[i]);
		}
		we_sys->crp[i] = NULL;
	}
	
	for (i = 0; i < WEDEF_AUTO_MOVE_MAX; i++){			///< 自動追尾ワークの初期化
		WeSysAutoMoveStop(we_sys, i);
	}
	
	for (i = 0; i < PARTICLE_GLOBAL_MAX; i++){
		if (we_sys->btl_sys->ptc[i]){							///< パーティクルのシステム終了
			Wp_Exit(we_sys->btl_sys->ptc[i]);
			we_sys->btl_sys->ptc[i] = NULL;
		}
	}
	
	if (we_sys->hc_sub_ptr != NULL){					///< サブシステム停止
		we_sys->hc_sub_ptr = NULL;
	}
	
	if (WES_ContestFlag_Get(we_sys) == FALSE){
		BattleDefaultBlendSet();
		// キャラクタデータクリア
		GF_BGL_ClearCharSet( BT_BGL_FrameGet(we_sys, WES_BF_EFFECT), 0x4000, 0, WeSysHeapAreaGet(we_sys) );
		GF_BGL_ScrClear( WeSysBGLPointerGet(we_sys) ,BT_BGL_FrameGet(we_sys, WES_BF_EFFECT) );
		GF_BGL_VisibleSet(BATTLE_FRAME_EFFECT, VISIBLE_ON);
	}
	else {
		ActinExTool_DefaultBlendSet();
	}
	
	GF_BGL_PrioritySet(GF_BGL_FRAME0_M, we_sys->bg_pri[ 0 ]);
	GF_BGL_PrioritySet(GF_BGL_FRAME1_M, we_sys->bg_pri[ 1 ]);
	GF_BGL_PrioritySet(GF_BGL_FRAME2_M, we_sys->bg_pri[ 2 ]);
	GF_BGL_PrioritySet(GF_BGL_FRAME3_M, we_sys->bg_pri[ 3 ]);

	GF_BGL_ScrollSet(we_sys->bgl, BATTLE_FRAME_EFFECT,		GF_BGL_SCROLL_X_SET, 0);
	GF_BGL_ScrollSet(we_sys->bgl, BATTLE_FRAME_EFFECT,		GF_BGL_SCROLL_Y_SET, 0);
	GF_BGL_ScrollSet(we_sys->bgl, BATTLE_FRAME_BACKGROUND,	GF_BGL_SCROLL_X_SET, 0);
	GF_BGL_ScrollSet(we_sys->bgl, BATTLE_FRAME_BACKGROUND,	GF_BGL_SCROLL_Y_SET, 0);
	
//	GF_Disp_GXS_VisibleControl(GX_PLANEMASK_OBJ, VISIBLE_ON);

	we_sys->waza_eff_active = FALSE;					///< システムの停止	
}



// =========================================
//
//	■パーティクル系
//		[ _COMMAND_PARTICLE_ ]
//
// =========================================
//--------------------------------------------------------------
/**
 * @brief	パーティクルの登録
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_ADD_PARTICLE(WE_SYS_PTR we_sys)
{

	u32	index;
	u32 cb_no;
	u32	no;

	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
		
	no = (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	index = (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);	///< パーティクル番号
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	cb_no = (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);	///< コールバック関数の番号
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	we_sys->btl_sys->this_ptc_no = no;

	if (we_sys->camera_flag[no] != 0){
		VecFx32 cv;
		Particle_GetVup(we_sys->btl_sys->ptc[no], &cv);
		cv.y *= -1;
		Particle_SetVup(we_sys->btl_sys->ptc[no], &cv);
	}
	
	Particle_CameraTypeSet(we_sys->btl_sys->ptc[no], we_sys->camera_mode[no]);

	we_sys->btl_sys->emit[0] = Wp_EmitterCreate(we_sys->btl_sys->ptc[no], index, cb_no, we_sys);
}

static void WEST_ADD_PARTICLE_EMIT_SET(WE_SYS_PTR we_sys)
{

	u32	index;
	u32 cb_no;
	u32	no;
	u32	emit_no;

	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
		
	no = (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
		
	emit_no = (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	index = (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);	///< パーティクル番号
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	cb_no = (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);	///< コールバック関数の番号
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	we_sys->btl_sys->this_ptc_no = no;
	
	if (we_sys->camera_flag[no] != 0){
		VecFx32 cv;
		Particle_GetVup(we_sys->btl_sys->ptc[no], &cv);
		cv.y *= -1;
		Particle_SetVup(we_sys->btl_sys->ptc[no], &cv);
	}
	
	Particle_CameraTypeSet(we_sys->btl_sys->ptc[no], we_sys->camera_mode[no]);

	we_sys->btl_sys->emit[emit_no] = Wp_EmitterCreate(we_sys->btl_sys->ptc[no], index, cb_no, we_sys);
}

static int ParticleSepIndexGet(WE_SYS_PTR we_sys)
{
	int index;
	int	at, df;
	int	at_no, df_no;
	
	int	 index_tbl[][ 6 ] = {
		///	aa	bb		a	b		c	d
		{ 0xFF,    1, 0xFF, 0xFF, 0xFF, 0xFF },	// aa
		{    4, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF },	// bb
		{ 0xFF, 0xFF, 0xFF,    3, 0xFF,    1 },	// a
		{ 0xFF, 0xFF,    6, 0xFF,    4, 0xFF },	// b
		{ 0xFF, 0xFF, 0xFF,    1, 0xFF,    2 },	// c
		{ 0xFF, 0xFF,    4, 0xFF,    5, 0xFF },	// d
	};
	
	at_no = WeSysATNoGet(we_sys);
	df_no = WeSysDFNoGet(we_sys);
	
	at = WET_ClientTypeGet(we_sys, at_no);
	df = WET_ClientTypeGet(we_sys, df_no);
	
	index = index_tbl[ at ][ df ];
	
	GF_ASSERT(index != 0xFF);

	return index - 1;
}

static int ParticlePtAtIndexGet(WE_SYS_PTR we_sys)
{
	int index;
	int	at, df;
	int	at_no, df_no;
	
	int	 index_tbl[][ 6 ] = {
		///	aa	bb		a	b		c	d
		{ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF },	// aa
		{ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF },	// bb
		{ 0xFF, 0xFF, 0xFF, 0xFF,    0, 0xFF },	// a
		{ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,    1 },	// b
		{ 0xFF, 0xFF,    1, 0xFF, 0xFF, 0xFF },	// c
		{ 0xFF, 0xFF, 0xFF,    0, 0xFF, 0xFF },	// d
	};
	
	at_no = WeSysATNoGet(we_sys);
	df_no = WeSysDFNoGet(we_sys);
	
	at = WET_ClientTypeGet(we_sys, at_no);
	df = WET_ClientTypeGet(we_sys, df_no);
	
	index = index_tbl[ at ][ df ];
	
	GF_ASSERT(index != 0xFF);

	return index;
}

static void WEST_ADD_PARTICLE_SEP(WE_SYS_PTR we_sys)
{
	int i;
	u32	index[ 6 ];
	u32 cb_no;
	u32	no;
	u32	set_index;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
		
	no = (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	for (i = 0; i < 6; i++){
		index[ i ] = (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);	///< パーティクル番号
		ADRS_SHIFT(we_sys->waza_eff_seq_adrs);		
	}

	cb_no = (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);	///< コールバック関数の番号
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	we_sys->btl_sys->this_ptc_no = no;

	if (we_sys->camera_flag[no] != 0){
		VecFx32 cv;
		Particle_GetVup(we_sys->btl_sys->ptc[no], &cv);
		cv.y *= -1;
		Particle_SetVup(we_sys->btl_sys->ptc[no], &cv);
	}
	
	{
		int id;
		
		id = ParticleSepIndexGet(we_sys);
		
		set_index = index[ id ];
	}
	
	Particle_CameraTypeSet(we_sys->btl_sys->ptc[no], we_sys->camera_mode[no]);

	we_sys->btl_sys->emit[0] = Wp_EmitterCreate(we_sys->btl_sys->ptc[no], set_index, cb_no, we_sys);
}


static void WEST_ADD_PARTICLE_PTAT(WE_SYS_PTR we_sys)
{
	int i;
	u32	index[ 4 ];
	u32 cb_no;
	u32	no;
	u32	set_index;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
		
	no = (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	for (i = 0; i < 4; i++){
		index[ i ] = (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);	///< パーティクル番号
		ADRS_SHIFT(we_sys->waza_eff_seq_adrs);		
	}

	cb_no = (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);				///< コールバック関数の番号
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	we_sys->btl_sys->this_ptc_no = no;

	if (we_sys->camera_flag[no] != 0){
		VecFx32 cv;
		Particle_GetVup(we_sys->btl_sys->ptc[no], &cv);
		cv.y *= -1;
		Particle_SetVup(we_sys->btl_sys->ptc[no], &cv);
	}
	
	{
		int id;
		
		id = ParticlePtAtIndexGet(we_sys);
		
		set_index = index[ id ];
	}
	
	Particle_CameraTypeSet(we_sys->btl_sys->ptc[no], we_sys->camera_mode[no]);

	we_sys->btl_sys->emit[0] = Wp_EmitterCreate(we_sys->btl_sys->ptc[no], set_index, cb_no, we_sys);
}


//--------------------------------------------------------------
/**
 * @brief	パーティクルの終了待ち
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_WAIT_PARTICLE(WE_SYS_PTR we_sys)
{
	int i;
	int em_num;
	
	em_num = 0;
	
	for (i = 0; i < PARTICLE_GLOBAL_MAX; i++){
		
		if (we_sys->btl_sys->ptc[i] == NULL){ continue; }
		
		em_num += Particle_GetEmitterNum(we_sys->btl_sys->ptc[i]);	///< エミッタ数の取得
	}
	
	if (em_num == 0){											///< エミッタ数 = 0なら終了してる
		ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
		we_sys->waza_eff_wait = 0;	
	}
	else {
		we_sys->waza_eff_wait = 1;
	}
}


//--------------------------------------------------------------
/**
 * @brief	パーティクルのリソースの読み込み
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_LOAD_PARTICLE(WE_SYS_PTR we_sys)
{
	u32 index;
	u32	no;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	no = (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	
	GF_ASSERT(we_sys->btl_sys->ptc[no] == NULL);
	
	
	index = (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

#ifdef PARTICLE_VBLANK_LOAD
//	OS_Printf(">> パーティクルをVBlankでロードします。\n");
	we_sys->btl_sys->ptc[no] = Wp_Init(we_sys->heap_area, index, FALSE);
	
	we_sys->waza_eff_wait = PARTICLE_VBLANK_LOAD_WAIT;	
	we_sys->waza_eff_exe  = WazaEffectWait;
#else
	we_sys->btl_sys->ptc[no] = Wp_Init(we_sys->heap_area, index, TRUE);
#endif
}

static void WEST_LOAD_PARTICLE_EX(WE_SYS_PTR we_sys)
{
	u32 index;
	u32 arc_no;
	u32	no;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	no = (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	arc_no = (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	arc_no = ARC_SAMPLE_PARTICLE;
	
	
	GF_ASSERT(we_sys->btl_sys->ptc[no] == NULL);
	
	
	index = (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
#ifdef PARTICLE_VBLANK_LOAD
//	OS_Printf(">> パーティクルをVBlankでロードします。\n");
	we_sys->btl_sys->ptc[no] = Wp_InitEx(we_sys->heap_area, arc_no, index, FALSE);
	
	we_sys->waza_eff_wait = PARTICLE_VBLANK_LOAD_WAIT;	
	we_sys->waza_eff_exe  = WazaEffectWait;
#else
	we_sys->btl_sys->ptc[no] = Wp_InitEx(we_sys->heap_area, arc_no, index, TRUE);
#endif
}

//--------------------------------------------------------------
/**
 * @brief	パーティクルのリソースの解放
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_EXIT_PARTICLE(WE_SYS_PTR we_sys)
{
	u32	no;
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
		
	no = (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	Wp_Exit(we_sys->btl_sys->ptc[no]);
	we_sys->btl_sys->ptc[no] = NULL;
}



// =========================================
//
//	■ジャンプ系
//		[ _COMMAND_JUMP_ ]
//
// =========================================
//--------------------------------------------------------------
/**
 * @brief	関数ジャンプ
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_SEQ_CALL(WE_SYS_PTR we_sys)
{
	int i;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	for (i = 0; i < WE_JUMP_MAX; i++){
		// 先頭から順に開いている場所を探す
		if (we_sys->waza_eff_seq_adrs_j[i] != NULL){ continue; }
		
		we_sys->waza_eff_seq_adrs_j[i] = we_sys->waza_eff_seq_adrs + 1;
		
		we_sys->waza_eff_seq_adrs += (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);		
		

		return;
	}	
}


//--------------------------------------------------------------
/**
 * @brief	関数ジャンプからもどる
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_END_CALL(WE_SYS_PTR we_sys)
{
	int i;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	for (i = WE_JUMP_MAX - 1; i >= 0; i--){
		if (we_sys->waza_eff_seq_adrs_j[i] == NULL){ continue; }
		
		we_sys->waza_eff_seq_adrs = we_sys->waza_eff_seq_adrs_j[i];	

		we_sys->waza_eff_seq_adrs_j[i] = NULL;

		return;
	}
}



//--------------------------------------------------------------
/**
 * @brief	指定したワーク番号と同じ値ならばジャンプ
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_WORKCHK_JP(WE_SYS_PTR we_sys)
{
	u32 index;
	u32 param;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	index = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	param = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	if (param == we_sys->waza_eff_gp_wk[index]){
		we_sys->waza_eff_seq_adrs = (u32*)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	}
	else {
		ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	}
}


//--------------------------------------------------------------
/**
 * @brief	コンテストの場合は指定アドレスに飛ぶ
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_CONTEST_CHK_JP(WE_SYS_PTR we_sys)
{
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	if (WeSysModeGet(we_sys->btl_sys)){
		we_sys->waza_eff_seq_adrs = (u32*)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	}
	else {
		ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	}	
}


//--------------------------------------------------------------
/**
 * @brief	指定された関数を呼び出すコマンド
 *			アドレスから参照する引数
 *			呼び出す関数のアドレス
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_FUNC_CALL(WE_SYS_PTR we_sys)
{
	int i;
	u32 id;
	u32 cnt;
	pWeFunc func;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	id = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	func = WazaEffectSupportFuncGet(id);
	
	cnt  = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	for (i = 0; i < cnt; i++){
		we_sys->waza_eff_gp_wk[i] = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
		ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	}
	for (; i < WE_GENE_WK_MAX; i++){
		we_sys->waza_eff_gp_wk[i] = 0;
	}

	func(we_sys);
}


//--------------------------------------------------------------
/**
 * @brief	ターン数に応じて、シーケンスの切り替えを行う
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_TURN_CHK(WE_SYS_PTR we_sys)
{
	int turn;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	if (we_sys->btl_sys->waza_eff_cnt & 1){
		ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	}
	
	we_sys->waza_eff_seq_adrs += (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);	
}


//--------------------------------------------------------------
/**
 * @brief	サイドでシーケンス切り替え
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_SIDE_JP(WE_SYS_PTR we_sys)
{
	int type;
	int side;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	
	type = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	if (type == 0){
		side = WET_SideCheck(we_sys, we_sys->btl_sys->at_client_no);
	}
	else {
		side = WET_SideCheck(we_sys, we_sys->btl_sys->df_client_no);
	}
	
	if (side == SIDE_ENEMY){
		ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	}

	we_sys->waza_eff_seq_adrs += (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
}


//--------------------------------------------------------------
/**
 * @brief	天気で切り替え
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_TENKI_JP(WE_SYS_PTR we_sys)
{
	int tenki;
	int tenki_tbl[] = {	///< tenki入れる
		FIELD_CONDITION_AME_ALL,
		FIELD_CONDITION_SUNAARASHI_ALL,
		FIELD_CONDITION_HARE_ALL,
		FIELD_CONDITION_ARARE_ALL,
	};
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	tenki = we_sys->btl_sys->waza_eff_weather;

	if (tenki != 0){
		ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
		{
			int i;
			for (i = 0; i < NELEMS(tenki_tbl); i++){
				
				if (tenki & tenki_tbl[i]){
					break;
				}
				else {
					ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
				}
				
				#if 0
				if (tenki != tenki_tbl[ i ]){
					ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
				}
				else {
					break;
				}
				#endif
			}
		}	
	}
	
	we_sys->waza_eff_seq_adrs += (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
}



//--------------------------------------------------------------
/**
 * @brief	コンテスト専用
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_CONTEST_JP(WE_SYS_PTR we_sys)
{
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	if (WES_ContestFlag_Get(we_sys) == TRUE){
		we_sys->waza_eff_seq_adrs += (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	}
	else {
		ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	}
}


//--------------------------------------------------------------
/**
 * @brief	パーティーアタック
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_PTAT_JP(WE_SYS_PTR we_sys)
{
	int at_side;
	int df_side;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	at_side = WET_SideCheck(we_sys, we_sys->btl_sys->at_client_no);
	df_side = WET_SideCheck(we_sys, we_sys->btl_sys->df_client_no);
	
	if (at_side == df_side){
		we_sys->waza_eff_seq_adrs += (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	}
	else {
		ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	}
}


//--------------------------------------------------------------
/**
 * @brief	指定ターンと同じならば、シーケンス切り替えを行う
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_TURN_JP(WE_SYS_PTR we_sys)
{
	int cnt;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	cnt = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
		
	if (cnt == we_sys->btl_sys->waza_eff_cnt){
		we_sys->waza_eff_seq_adrs += (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);		
	}
	else {
		ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	}	
}


//--------------------------------------------------------------
/**
 * @brief	指定アドレスにジャンプする
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_SEQ_JP(WE_SYS_PTR we_sys)
{
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	we_sys->waza_eff_seq_adrs += (u32)SeqAdrsGet(we_sys->waza_eff_seq_adrs);		
}



// =========================================
//
//	■ポケモン関連
//		[ _COMMAND_POKEMON_ ]
//
// =========================================

static int WEST_Tool_DropPokeClientNoGet(WE_SYS_PTR we_sys, int flag);

//--------------------------------------------------------------
/**
 * @brief	操作フラグから、クライアント番号を取得する
 *
 * @param	we_sys	
 * @param	flag	
 *
 * @retval	static int	
 *
 */
//--------------------------------------------------------------
static int WEST_Tool_DropPokeClientNoGet(WE_SYS_PTR we_sys, int flag)
{
	int no;
	
	switch(flag){
	case WEDEF_DROP_M1:
		no = we_sys->btl_sys->at_client_no;
		break;

	case WEDEF_DROP_E1:
		no = we_sys->btl_sys->df_client_no;
		break;

	case WEDEF_DROP_M2:
		no = WET_AllySideClientNoGet(we_sys, we_sys->btl_sys->at_client_no);
		break;

	case WEDEF_DROP_E2:
		no = WET_AllySideClientNoGet(we_sys, we_sys->btl_sys->df_client_no);
		break;
	
	case WEDEF_DROP_A:
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
		}
		break;
	case WEDEF_DROP_B:
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
		}
		break;
	case WEDEF_DROP_C:
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
		}
		break;
	case WEDEF_DROP_D:
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
		}
		break;
	}
	
	return no;
}



//--------------------------------------------------------------
/**
 * @brief	OAMが自動でソフトスプライトを追尾するTCB
 *
 * @param	tcb	
 * @param	work	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_Tool_AutoMoveOAM_TCB(TCB_PTR tcb, void* work)
{
	AMO_SYS_PTR wk = (AMO_SYS_PTR)work;
	
	s16 px;
	s16 py;
	
	if (wk->ams.frame != 0){
		wk->ams.wait++;
		if (wk->ams.wait != wk->ams.frame){ return; }
		wk->ams.wait = 0;
	}

	px = SoftSpriteParaGet(wk->ams.ssp, SS_PARA_POS_X);
	py = SoftSpriteParaGet(wk->ams.ssp, SS_PARA_POS_Y);
	py -= SoftSpriteParaGet(wk->ams.ssp, SS_PARA_SHADOW_HEIGHT);
	
	CATS_ObjectPosSetCap(wk->cap, px, py);	
}


//--------------------------------------------------------------
/**
 * @brief	BGが自動でソフトスプライトを追尾するTCB
 *
 * @param	tcb	
 * @param	work	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_Tool_AutoMoveBG_TCB(TCB_PTR tcb, void* work)
{
	AMB_SYS_PTR wk = (AMB_SYS_PTR)work;
	
	s16 px;
	s16 py;
	
	if (wk->ams.frame != 0){
		wk->ams.wait++;
		if (wk->ams.wait != wk->ams.frame){ return; }
		wk->ams.wait = 0;
	}

	px = SoftSpriteParaGet(wk->ams.ssp, SS_PARA_POS_X);
	py = SoftSpriteParaGet(wk->ams.ssp, SS_PARA_POS_Y);
	py -= SoftSpriteParaGet(wk->ams.ssp, SS_PARA_SHADOW_HEIGHT);
	
	GF_BGL_ScrollSet(wk->bgl, BATTLE_FRAME_EFFECT, GF_BGL_SCROLL_X_SET, -(px-40));
	GF_BGL_ScrollSet(wk->bgl, BATTLE_FRAME_EFFECT, GF_BGL_SCROLL_Y_SET, -(py-40));
}


//--------------------------------------------------------------
/**
 * @brief	自動追尾の終了
 *
 * @param	we_sys	
 * @param	stop_tr	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WeSysAutoMoveStop(WE_SYS_PTR we_sys, int stop_tr)
{
	if (stop_tr == WEDEF_AM_STOP_BG){
		if (we_sys->poke_ambs != NULL){
			TCB_Delete(we_sys->poke_ambs->ams.am_tcb);
			sys_FreeMemoryEz(we_sys->poke_ambs);
			we_sys->poke_ambs = NULL;
		}
	}
	else {
		if (we_sys->poke_amos[ stop_tr ] != NULL){
			TCB_Delete(we_sys->poke_amos[ stop_tr ]->ams.am_tcb);
			sys_FreeMemoryEz(we_sys->poke_amos[ stop_tr ]);
			we_sys->poke_amos[ stop_tr ] = NULL;
		}
	}
}

static void WEST_POKEBG(WE_SYS_PTR we_sys)
{
}
static void WEST_POKEBG_RESET(WE_SYS_PTR we_sys)
{
}


//--------------------------------------------------------------
/**
 * @brief	ポケモンをBGに落とす
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 *	flag =	0 攻撃ポケモンをBGへ
 *			1 対象ポケモンをBGへ
 *			2 攻撃ポケモンの相方をBGへ
 *			3 対象ポケモンの相方をBGへ
 *
 *	auto_move = 0 移動結果をBGに反映しない
 *				1 移動結果をBGに反映する
 */
//--------------------------------------------------------------
static void WEST_POKEBG_DROP(WE_SYS_PTR we_sys)
{	
	void* oam_temp = NULL;
	int flag;
	int auto_move;
	int client_no;
	int arcID;
	int index_pal;
	int index_screen;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	flag = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	auto_move = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	client_no = WEST_Tool_DropPokeClientNoGet(we_sys, flag);
	arcID	  = we_sys->btl_sys->excp[client_no]->arcID;
	index_pal = we_sys->btl_sys->excp[client_no]->pal_index;
	oam_temp  = we_sys->btl_sys->excp[client_no]->exchr_buffer;
	
	if (WES_ContestFlag_Get(we_sys) == TRUE
	&&	ContestPokeFlipCheck(WeSysMonsNoGet(we_sys, client_no)) == TRUE){
		index_screen = PB_F_512_SCREEN_ID;		///< 反転
	}
	else {
		index_screen = PB_N_512_SCREEN_ID;		///< 通常
	}

	{
		u8* adrs = GF_BGL_CgxGet(BATTLE_FRAME_EFFECT);
		
		MI_CpuFill8(adrs, 0, 10 * 10 * 2 * 0x20);
	}

//	GF_BGL_ScrClear(we_sys->bgl, BATTLE_FRAME_EFFECT);
//	GF_BGL_ScrClearCode( we_sys->bgl, BATTLE_FRAME_EFFECT, 64 );

	GF_BGL_VisibleSet(BATTLE_FRAME_EFFECT, VISIBLE_OFF);

	GF_BGL_LoadCharacter(we_sys->bgl, BATTLE_FRAME_EFFECT, oam_temp,  POKE_TEX_SIZE, 0);
	
	PaletteWorkSet_Arc(we_sys->pfd,
					   arcID, index_pal,
					   we_sys->heap_area, FADE_MAIN_BG, 0, WEDEF_BG_POKE_COL_POS);

	ArcUtil_ScrnSet(ARC_BATT_BG,
					index_screen,
					we_sys->bgl,
					BATTLE_FRAME_EFFECT,0,0,0,we_sys->heap_area);
	
	///< 自動追尾TCB設定
	if (auto_move == WEDEF_POKE_AUTO_ON){
		TCB_PTR tcb;
		
		we_sys->poke_ambs = sys_AllocMemory(we_sys->heap_area, sizeof(TAMO_SYS));
		we_sys->poke_ambs->bgl		 = we_sys->bgl;
		we_sys->poke_ambs->ams.ssp   = WeSysSoftSpritePointerGet(we_sys, client_no);
		we_sys->poke_ambs->ams.wait  = 0;
		we_sys->poke_ambs->ams.frame = 0;
		
		tcb = TCB_Add(WEST_Tool_AutoMoveBG_TCB, we_sys->poke_ambs, 0x1001);
		
		we_sys->poke_ambs->ams.am_tcb = tcb;
	}
	
	///< 座標をポケモンにあわせる
	{
		s16 px;
		s16 py;

		px = SoftSpriteParaGet(WeSysSoftSpritePointerGet(we_sys, client_no), SS_PARA_POS_X);
		py = SoftSpriteParaGet(WeSysSoftSpritePointerGet(we_sys, client_no), SS_PARA_POS_Y);
		py -= SoftSpriteParaGet(WeSysSoftSpritePointerGet(we_sys, client_no), SS_PARA_SHADOW_HEIGHT);
		
		GF_BGL_ScrollSet(we_sys->bgl, BATTLE_FRAME_EFFECT, GF_BGL_SCROLL_X_SET, -(px-40));
		GF_BGL_ScrollSet(we_sys->bgl, BATTLE_FRAME_EFFECT, GF_BGL_SCROLL_Y_SET, -(py-40));
	}

	GF_BGL_VisibleSet(BATTLE_FRAME_EFFECT, VISIBLE_ON);
	GF_BGL_PrioritySet(BATTLE_FRAME_EFFECT, BT_3DPriorityGet(we_sys));
}


//--------------------------------------------------------------
/**
 * @brief	ポケモンのBG落としをリセット
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_POKEBG_DROP_RESET(WE_SYS_PTR we_sys)
{
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	{
		u8* adrs = GF_BGL_CgxGet(BATTLE_FRAME_EFFECT);
		
		MI_CpuFill8(adrs, 0, 10 * 10 * 2 * 0x20);
	}	
//	GF_BGL_ScrClearCode(we_sys->bgl, BATTLE_FRAME_EFFECT, 0x64);
//	GF_BGL_ScrClear(we_sys->bgl, BATTLE_FRAME_EFFECT);

	WeSysAutoMoveStop(we_sys, WEDEF_AM_STOP_BG);
}


//--------------------------------------------------------------
/**
 * @brief	ポケモンのOAMリソース初期化
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_POKEOAM_RES_INIT(WE_SYS_PTR we_sys)
{
	///< リソースの作成
	int obj_num = WE_POKE_CAP_MAX;
	TCATS_RESOURCE_NUM_LIST crnl = {
						WE_POKE_CAP_MAX,
						WE_POKE_CAP_MAX,
						WE_POKE_CAP_MAX,
						WE_POKE_CAP_MAX, 0, 0 };
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	we_sys->poke_crp = CATS_ResourceCreate(we_sys->btl_sys->csp);
	
	CATS_ClactSetInit(we_sys->btl_sys->csp, we_sys->poke_crp, obj_num);
	CLACT_U_SetSubSurfaceMatrix(CATS_EasyRenderGet(we_sys->btl_sys->csp), 0, BATTLE_SUB_ACTOR_DISTANCE);
	
	CATS_ResourceManagerInit(we_sys->btl_sys->csp, we_sys->poke_crp, &crnl);
}


//--------------------------------------------------------------
/**
 * @brief	ポケモンOAMリソースロード
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_POKEOAM_RES_LOAD(WE_SYS_PTR we_sys)
{
	int res_id[6];
	int use_no;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	use_no = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	res_id[0] = CHARID_POKE_OAM_0 + use_no + WES_OFS_ID(we_sys->btl_sys->at_client_no);
	res_id[1] = PLTTID_POKE_OAM_0 + use_no + WES_OFS_ID(we_sys->btl_sys->at_client_no);
	res_id[2] = CELLID_POKE_OAM_0 + use_no + WES_OFS_ID(we_sys->btl_sys->at_client_no);
	res_id[3] = CELLANMID_POKE_OAM_0 + use_no + WES_OFS_ID(we_sys->btl_sys->at_client_no);
	res_id[4] = 0;
	res_id[5] = 0;

	///< 転送
	CATS_LoadResourceCharArc(we_sys->btl_sys->csp, we_sys->poke_crp,
							 PO_ARC_ID, PO_CHAR_ID, 0,
							 NNS_G2D_VRAM_TYPE_2DMAIN, res_id[0]);

	CATS_LoadResourcePlttWorkArc(we_sys->pfd, FADE_MAIN_OBJ,
								 we_sys->btl_sys->csp, we_sys->poke_crp,
								 PO_ARC_ID, PO_PLTT_ID, 0,
								 NNS_G2D_VRAM_TYPE_2DMAIN, 1, res_id[1]);

	CATS_LoadResourceCellArc(we_sys->btl_sys->csp, we_sys->poke_crp,
							 PO_ARC_ID, PO_CELL_ID, 0, res_id[2]);

	CATS_LoadResourceCellAnmArc(we_sys->btl_sys->csp, we_sys->poke_crp,
							 	PO_ARC_ID,	PO_CELLANM_ID, 0, res_id[3]);
}


//--------------------------------------------------------------
/**
 * @brief	ポケモンのOAMドロップ
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_POKEOAM_DROP(WE_SYS_PTR we_sys)
{	
	u8* oam_temp = NULL;
	CATS_ACT_PTR cap = NULL;
	int res_id[6];

	int flag;
	int auto_move;
	int cap_id;
	int use_no;
	int client_no;
	int arcID;
	int index_pal;

	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	flag = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	auto_move = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	cap_id = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	use_no = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	res_id[0] = CHARID_POKE_OAM_0 + use_no + WES_OFS_ID(we_sys->btl_sys->at_client_no);
	res_id[1] = PLTTID_POKE_OAM_0 + use_no + WES_OFS_ID(we_sys->btl_sys->at_client_no);
	res_id[2] = CELLID_POKE_OAM_0 + use_no + WES_OFS_ID(we_sys->btl_sys->at_client_no);
	res_id[3] = CELLANMID_POKE_OAM_0 + use_no + WES_OFS_ID(we_sys->btl_sys->at_client_no);
	res_id[4] = 0;
	res_id[5] = 0;
	
	/// クライアントNoの取得
	client_no = WEST_Tool_DropPokeClientNoGet(we_sys, flag);
	
	arcID	  = we_sys->btl_sys->excp[client_no]->arcID;
	index_pal = we_sys->btl_sys->excp[client_no]->pal_index;
	oam_temp  = we_sys->btl_sys->excp[client_no]->exchr_buffer;
	{
		///< OAM登録
		TCATS_OBJECT_ADD_PARAM_S coap;
		SOFT_SPRITE* ssp = WeSysSoftSpritePointerGet(we_sys, client_no);
		int defence_client;
		int i;
		s16 px;
		s16 py;
		
		if (ssp != NULL){
			px = SoftSpriteParaGet(ssp, SS_PARA_POS_X);
			py = SoftSpriteParaGet(ssp, SS_PARA_POS_Y);
			py -= SoftSpriteParaGet(ssp, SS_PARA_SHADOW_HEIGHT);
			
		}

		
		coap.x		= px;
		coap.y		= py;
		coap.z		= 0;		
		coap.anm	= 0;
		coap.pri	= WAZAEFF_ACT_SOFTPRI;
		coap.pal	= 0;
		coap.d_area = CATS_D_AREA_MAIN;
		coap.bg_pri = WAZAEFF_ACT_BGPRI;
		coap.vram_trans = 0;
		
		for (i = 0; i < 6; i++){
			coap.id[i] = res_id[i];
		}
		
		cap = CATS_ObjectAdd_S(we_sys->btl_sys->csp, we_sys->poke_crp, &coap);
		
		if (ssp == NULL){
			CATS_ObjectEnableCap(cap, CATS_ENABLE_FALSE);
		}
		else {
			int vf = SoftSpriteParaGet(ssp, SS_PARA_VANISH);
			
			if (vf == 1){
				CATS_ObjectEnableCap(cap, CATS_ENABLE_FALSE);
			}			
		}
		
		if (WES_ContestFlag_Get(we_sys) == TRUE
		&&	ContestPokeFlipCheck(WeSysMonsNoGet(we_sys, client_no)) == TRUE){
			CATS_ObjectFlipSetCap(cap, CLACT_FLIP_H);
		}
	}
	
	if (WeSysSoftSpritePointerGet(we_sys, client_no) != NULL)
	{
		///< ダミーキャラに正式キャラを転送しなおし
		NNSG2dImageProxy * image;
		
		image = CLACT_ImageProxyGet(cap->act);
				
		AddVramTransferManager(
			NNS_GFD_DST_2D_OBJ_CHAR_MAIN,
			image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN],
			oam_temp,
			POKE_TEX_SIZE);
	}
	
	if (WeSysSoftSpritePointerGet(we_sys, client_no) != NULL)
	{
		///< ダミーパレットに正式なパレットを転送しなおし
		NNSG2dImagePaletteProxy* palette;
		int pal_no;
		
		palette = CLACT_PaletteProxyGet(cap->act);
		
		pal_no = GetPlttProxyOffset(palette, NNS_G2D_VRAM_TYPE_2DMAIN);
		
		PaletteWorkSet_Arc(we_sys->pfd, arcID, index_pal, we_sys->heap_area,
						   FADE_MAIN_OBJ, 0x20, pal_no*16);
	}
		
	GF_ASSERT(we_sys->poke_cap[ cap_id ] == NULL);
	
	we_sys->poke_cap[ cap_id ] = cap;
	we_sys->poke_cap_use[ cap_id ] = TRUE;
	
	///< 自動追尾TCB設定
	if (auto_move == WEDEF_POKE_AUTO_ON){		
		TCB_PTR tcb;
		
		if (WeSysSoftSpritePointerGet(we_sys, client_no) == NULL){ return; }
		
		we_sys->poke_amos[ cap_id ] = sys_AllocMemory(we_sys->heap_area, sizeof(TAMO_SYS));
		we_sys->poke_amos[ cap_id ]->cap	   = cap;
		we_sys->poke_amos[ cap_id ]->ams.ssp   = WeSysSoftSpritePointerGet(we_sys, client_no);
		we_sys->poke_amos[ cap_id ]->ams.wait  = 0;
		we_sys->poke_amos[ cap_id ]->ams.frame = 0;
		
		tcb = TCB_Add(WEST_Tool_AutoMoveOAM_TCB, we_sys->poke_amos[ cap_id ], 0x1001);
		
		we_sys->poke_amos[ cap_id ]->ams.am_tcb = tcb;
	}
}

//--------------------------------------------------------------
/**
 * @brief	ポケモンOAMドロップ用リソース削除
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_POKEOAM_RES_FREE(WE_SYS_PTR we_sys)
{
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	if (we_sys->poke_crp != NULL){
		CATS_ResourceDestructor_S(we_sys->btl_sys->csp, we_sys->poke_crp);
	}
	we_sys->poke_crp = NULL;
}


//--------------------------------------------------------------
/**
 * @brief	ポケモンOAMの解放
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_POKEOAM_DROP_RESET(WE_SYS_PTR we_sys)
{
	int cap_id;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	cap_id = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	if (we_sys->poke_cap[cap_id] != NULL){
		CATS_ActorPointerDelete_S(we_sys->poke_cap[cap_id]);
	}
	we_sys->poke_cap_use[ cap_id ] = FALSE;
	we_sys->poke_cap[cap_id] = NULL;
}


static void PDS_Tcb(TCB_PTR tcb, void* work)
{
	PT_DROP_SYS* wk = work;
	
	if (wk->flag == FALSE){
		TCB_Delete(tcb);
		return;
	}
	
	if (wk->wsp->poke_crp != NULL){
		CATS_Draw(wk->crp);	
	}
}

static void WEST_PT_DROP(WE_SYS_PTR we_sys)
{	
	int type;
	int no;
	int cap_no;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	type = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	no = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	cap_no = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	we_sys->pds[no].wsp  = we_sys;
	we_sys->pds[no].crp  = we_sys->poke_crp;
	we_sys->pds[no].cap  = we_sys->poke_cap[ cap_no ];
	we_sys->pds[no].flag = TRUE;
	
	CATS_ObjectEnableCap(we_sys->pds[no].cap, CATS_ENABLE_FALSE);
	
	if (IsWeSysBattleMode2vs2(we_sys) == TRUE)
	{
		int at, df;
		
		at = WET_ClientTypeGet(we_sys, WeSysATNoGet(we_sys));
		df = WET_ClientTypeGet(we_sys, WeSysDFNoGet(we_sys));
		
		{
			int vf;
			int client_no;
			SOFT_SPRITE* ssp;
			
			client_no = WEST_Tool_DropPokeClientNoGet(we_sys, type);
			ssp = WeSysSoftSpritePointerGet(we_sys, client_no);
			
			if (ssp != NULL){
				vf = SoftSpriteParaGet(ssp, SS_PARA_VANISH);
			}
			else {
				vf = 0;
			}
			
			if (vf == 1){
				CATS_ObjectEnableCap(we_sys->pds[no].cap, CATS_ENABLE_FALSE);
			}
			else {
				CATS_ObjectEnableCap(we_sys->pds[no].cap, CATS_ENABLE_TRUE);
			}
		}
	
		switch(type){
		case WEDEF_DROP_M1:			
			if (at == CLIENT_TYPE_B
			||	at == CLIENT_TYPE_C){
			//	CATS_ObjectPriSetCap(we_sys->pds[no].cap, 0);
				CATS_ObjectPriSetCap(we_sys->pds[no].cap, 1);
			}
			else {
				CATS_ObjectEnableCap(we_sys->pds[no].cap, CATS_ENABLE_FALSE);
				CATS_ObjectPriSetCap(we_sys->pds[no].cap, 255);
			}
			#if 0
			switch(df){
			case CLIENT_TYPE_A:
				CATS_ObjectPriSetCap(we_sys->pds[no].cap, 255);
				break;
			case CLIENT_TYPE_B:
				CATS_ObjectPriSetCap(we_sys->pds[no].cap, 255);
				break;
			case CLIENT_TYPE_C:
				CATS_ObjectPriSetCap(we_sys->pds[no].cap, 255);
				break;
			case CLIENT_TYPE_D:
				CATS_ObjectPriSetCap(we_sys->pds[no].cap, 255);
				break;
			}
			#endif
			break;
		case WEDEF_DROP_M2:
			if (at == CLIENT_TYPE_D
			||	at == CLIENT_TYPE_A){
			//	CATS_ObjectPriSetCap(we_sys->pds[no].cap, 0);
				CATS_ObjectPriSetCap(we_sys->pds[no].cap, 1);
			}
			else {
				CATS_ObjectEnableCap(we_sys->pds[no].cap, CATS_ENABLE_FALSE);
				CATS_ObjectPriSetCap(we_sys->pds[no].cap, 255);
			}
			#if 0
			switch(df){
			case CLIENT_TYPE_A:
				CATS_ObjectPriSetCap(we_sys->pds[no].cap, 0);
				break;
			case CLIENT_TYPE_B:
				CATS_ObjectPriSetCap(we_sys->pds[no].cap, 0);
				break;
			case CLIENT_TYPE_C:
				CATS_ObjectPriSetCap(we_sys->pds[no].cap, 0);
				break;
			case CLIENT_TYPE_D:
				CATS_ObjectPriSetCap(we_sys->pds[no].cap, 0);
				break;
			}
			#endif
			break;
		case WEDEF_DROP_E1:
			switch(df){
			case CLIENT_TYPE_A:
				CATS_ObjectPriSetCap(we_sys->pds[no].cap, 255);
				break;
			case CLIENT_TYPE_B:
			//	CATS_ObjectPriSetCap(we_sys->pds[no].cap, 0);
				CATS_ObjectPriSetCap(we_sys->pds[no].cap, 1);
				break;
			case CLIENT_TYPE_C:
			//	CATS_ObjectPriSetCap(we_sys->pds[no].cap, 0);
				CATS_ObjectPriSetCap(we_sys->pds[no].cap, 1);
				break;
			case CLIENT_TYPE_D:
				CATS_ObjectPriSetCap(we_sys->pds[no].cap, 255);
				break;
			}
			break;
		case WEDEF_DROP_E2:
			switch(df){
			case CLIENT_TYPE_A:
			//	CATS_ObjectPriSetCap(we_sys->pds[no].cap, 0);
				CATS_ObjectPriSetCap(we_sys->pds[no].cap, 1);
				break;
			case CLIENT_TYPE_B:
				CATS_ObjectPriSetCap(we_sys->pds[no].cap, 255);
				break;
			case CLIENT_TYPE_C:
				CATS_ObjectPriSetCap(we_sys->pds[no].cap, 255);
				break;
			case CLIENT_TYPE_D:
			//	CATS_ObjectPriSetCap(we_sys->pds[no].cap, 0);
				CATS_ObjectPriSetCap(we_sys->pds[no].cap, 1);
				break;
			}
			break;
		}
		TCB_Add(PDS_Tcb, &we_sys->pds[no], 0x1000);
	}	
}

static void WEST_PT_DROP_RESET(WE_SYS_PTR we_sys)
{
	int no;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	no = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	we_sys->pds[no].flag = FALSE;
}



//--------------------------------------------------------------
/**
 * @brief	ポケモンOAMの自動追尾停止
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_POKEOAM_AUTO_STOP(WE_SYS_PTR we_sys)
{
	int cap_id;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	cap_id = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	WeSysAutoMoveStop(we_sys, cap_id);
}


//--------------------------------------------------------------
/**
 * @brief	カメラのモード指定
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_CAMERA_CHG(WE_SYS_PTR we_sys)
{
	int no;
	int mode;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	no = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);	
	
	mode = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);	
	
	we_sys->camera_mode[no] = mode;
}


//--------------------------------------------------------------
/**
 * @brief	カメラ反転
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WEST_CAMERA_REVERCE(WE_SYS_PTR we_sys)
{
	int no;
	int flag;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	no = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);	
	
	flag = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);	
	
	we_sys->camera_flag[no] = flag;
}


static void WEST_POKE_BANISH_ON(WE_SYS_PTR we_sys)
{
}
static void WEST_POKE_BANISH_OFF(WE_SYS_PTR we_sys)
{
}

// =========================================
//
//	■背景関連
//		[ _COMMAND_BG_ ]
//
// =========================================

// -----------------------------------------
//
//	■背景切り替えモード
//
// -----------------------------------------
enum ETCB_HAIKEI_MODE {
	
	ENUM_HMODE_NONE = 0,					///< 何も発生していない
	ENUM_HMODE_CHG,							///< 背景切り替え
	ENUM_HMODE_HALF,						///< フェードの中間

};

static BOOL HaikeiChange_ParamRev(HC_SYS_PTR hcs, WE_SYS_PTR we_sys, int gp_index);


static void HaikeiChange_DataSet(HC_SYS_PTR wk, WE_SYS_PTR we_sys, int frm, int id);
static int	HaikeiChange_BitCheck(int mode, int flag);
static int	HaikeiChange_BitReset(int* mode, int flag);

static void HaikeiSubSystemFirstCall(HC_SYS_PTR wk);

///< 切り替え関数
static BOOL HaikeiChange_Blend(TCB_PTR tcb, HC_SYS_PTR wk);
static BOOL HaikeiChange_Fade(TCB_PTR tcb, HC_SYS_PTR wk);
static BOOL HaikeiChange_None(TCB_PTR tcb, HC_SYS_PTR wk);

///< 復帰関数
static BOOL HaikeiRecover_Blend(TCB_PTR tcb, HC_SYS_PTR wk);
static BOOL HaikeiRecover_Fade(TCB_PTR tcb, HC_SYS_PTR wk);
static BOOL HaikeiRecover_None(TCB_PTR tcb, HC_SYS_PTR wk);

static BOOL (* const HaikeiChange_Table[])(TCB_PTR tcb, HC_SYS_PTR wk) = {
	HaikeiChange_Blend,
	HaikeiChange_Fade,
	HaikeiChange_None,

	HaikeiRecover_Blend,
	HaikeiRecover_Fade,
	HaikeiRecover_None,
};

///< サブ関数
static BOOL HaikeiSubSystem_None(HC_SYS_PTR wk);
static BOOL HaikeiSubSystem_Move(HC_SYS_PTR wk);
static BOOL HaikeiSubSystem_Stop(HC_SYS_PTR wk);
static BOOL HaikeiSubSystem_Exit(HC_SYS_PTR wk);
static BOOL HaikeiSubSystem_LasterScroll_Init(HC_SYS_PTR wk);
static BOOL HaikeiSubSystem_LasterScroll_Stop(HC_SYS_PTR wk);

static BOOL HaikeiSubSystem_Drop(HC_SYS_PTR wk);
static BOOL HaikeiSubSystem_Recover(HC_SYS_PTR wk);

static BOOL (* const HaikeiChange_SubTable[])(HC_SYS_PTR wk) = {
	HaikeiSubSystem_None,
	HaikeiSubSystem_Move,
	HaikeiSubSystem_Stop,
	HaikeiSubSystem_Exit,
	HaikeiSubSystem_None,
	HaikeiSubSystem_LasterScroll_Init,
	HaikeiSubSystem_LasterScroll_Stop,
};


//--------------------------------------------------------------
/**
 * @brief	背景パラメーター反転チェック
 *
 * @param	we_sys	
 * @param	gp_index	
 *
 * @retval	static BOOL	
 *
 */
//--------------------------------------------------------------
static BOOL HaikeiChange_ParamRev(HC_SYS_PTR hcs, WE_SYS_PTR we_sys, int gp_index)
{
	int at_side;
	int df_side;
	
	at_side = WET_SideCheck(we_sys, we_sys->btl_sys->at_client_no);
	df_side = WET_SideCheck(we_sys, we_sys->btl_sys->df_client_no);

	if (hcs->gp_wk[ gp_index ] == 2){			///< 場によって反転
		
		if (at_side == df_side){
			
			if (df_side == SIDE_MINE){
				
				return FALSE;
				
			}
			else {
				
				return TRUE;
				
			}
			
		}
		else if (df_side == SIDE_MINE){
			
			return TRUE;
			
		}
		
	}
	else if (hcs->gp_wk[ gp_index ] != 0){			///< 場によって反転
		
		if (df_side == SIDE_MINE){
			
			return TRUE;
			
		}
		
	}
	return FALSE;
}


//--------------------------------------------------------------
/**
 * @brief	背景切り替えデータ設定
 *
 * @param	we_sys	
 * @param	frm	
 * @param	id	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void HaikeiChange_DataSet(HC_SYS_PTR hcs, WE_SYS_PTR we_sys, int frm, int id)
{
//	OS_Printf("指定背景データ　= %3d\n",id);
	
	ArcUtil_BgCharSet(WE_HAIKEI_ARC,
					  WeSysHaikeiDataIDGet( id, 0 ),
					  we_sys->bgl,
					  frm, 0, 0, 1, we_sys->heap_area);

	PaletteWorkSet_Arc(we_sys->pfd,
					   WE_HAIKEI_ARC, WeSysHaikeiDataIDGet( id, 1),
					   we_sys->heap_area, FADE_MAIN_BG, 0x20, WEDEF_BG_DATA_COL_POS);
					   
	GF_BGL_ScrClear(we_sys->bgl, frm);
	
	{
		int idx = 2;
		
		if (WES_ContestFlag_Get(we_sys) == TRUE){
			idx = 4;
		}
		else if (HaikeiChange_ParamRev(hcs, we_sys, WEDEF_GP_INDEX_SCREEN_R) == TRUE){
			idx = 3;
		}
		
		ArcUtil_ScrnSet(WE_HAIKEI_ARC,
						WeSysHaikeiDataIDGet( id, idx ),
						we_sys->bgl,
						frm, 0, 0, 1, we_sys->heap_area);
	}
}


//--------------------------------------------------------------
/**
 * @brief	背景切り替えBitチェック
 *
 * @param	mode	モード
 * @param	flag	
 *
 * @retval	static int	
 *
 */
//--------------------------------------------------------------
static int HaikeiChange_BitCheck(int mode, int flag)
{
	int bit;
	int no;

	if (((mode<<WEDEF_HAIKEI_SHIFT) & flag) == flag){
		bit = 1;
	}
	else {
		bit = 0;
	}

	return bit;
}


//--------------------------------------------------------------
/**
 * @brief	背景切り替えBitを落とす
 *
 * @param	mode	
 * @param	flag	
 *
 * @retval	static	
 *
 */
//--------------------------------------------------------------
static int	HaikeiChange_BitReset(int* mode, int flag)
{
	int bit;
	int no;
	
	no   = WEDEF_BIT_SHIFT(flag) >> WEDEF_HAIKEI_SHIFT;
	bit  = ((*mode) &= 0xffffffff ^ (1 << no));

	return bit;
}


//--------------------------------------------------------------
/**
 * @brief	背景切り替え後のサブシステム実行
 *
 * @param	wk	
 *
 * @retval	none	
 *
 *		□フェードアウト後に呼ばれるサブコール
 *
 */
//--------------------------------------------------------------
static void HaikeiSubSystemFirstCall(HC_SYS_PTR wk)
{
	int i;
	int id;
	int call_id;
	
	const u32 first_call_no[] = {		///< 初回起動するモードID
		WEDEF_HAIKEI_SBIT_MOVE,
		WEDEF_HAIKEI_SBIT_STOP,
		WEDEF_HAIKEI_SBIT_LASTER,
		WEDEF_HAIKEI_SBIT_LASTER_STOP,
	};
	
	for (i = 0; i < NELEMS(first_call_no); i++){
		
		if (HaikeiChange_BitCheck(wk->ch_sbit, first_call_no[i]) == 0){ continue; }

		id		= 0;
		call_id = WEDEF_HAIKEI_SBIT_SHIFT(first_call_no[i]);
		
		call_id = first_call_no[i] >> WEDEF_HAIKEI_SHIFT;
		while (call_id >= 2){
			call_id /= 2;
			id++;						
		};
		
		HaikeiChange_SubTable[id](wk);
	}
}


//--------------------------------------------------------------
/**
 * @brief	背景切り替え用初期化済みポインタの取得
 *
 * @param	we_sys	
 *
 * @retval	HC_SYS_PTR	
 *
 */
//--------------------------------------------------------------
static HC_SYS_PTR HaikeiControlInit(WE_SYS_PTR we_sys)
{
	HC_SYS_PTR hcs = NULL;
	
	hcs = sys_AllocMemory(we_sys->heap_area, sizeof(THC_SYS));
	
	if (hcs == NULL){
		GF_ASSERT(0 && "HaikeiControlの初期化失敗");
		return NULL;
	}
	memset(hcs, 0, sizeof(THC_SYS));
	
	hcs->sub_seq = 0;
	hcs->seq     = 0;
	hcs->we_sys  = we_sys;
	
	hcs->ev1	 = WES_HAIKEI_S_EV1;
	hcs->ev2	 = WES_HAIKEI_S_EV2;
	hcs->ev1_e	 = WES_HAIKEI_E_EV1 - 2;
	hcs->ev2_e	 = WES_HAIKEI_E_EV2 + 2;
	
	///< 半透明停止モード
	if (WeSysGPWorkGet(we_sys, WEDEF_GP_INDEX_FADE_VALUE) == 1){
		hcs->ev1	= 0;
		hcs->ev2	= 31;
		hcs->ev1_e	= 15;
		hcs->ev2_e	= 7;
	}
	if (WeSysGPWorkGet(we_sys, WEDEF_GP_INDEX_FADE_VALUE) == 2){
		hcs->ev1	= 7;
		hcs->ev2	= 15;
		hcs->ev1_e	= 31 - 2;
		hcs->ev2_e	= 0  + 2;
	}
	
	{
		int i;
		
		for (i = 0; i < WE_GENE_WK_MAX; i++){
			hcs->gp_wk[ i ] = we_sys->waza_eff_gp_wk[ i ];
		}
	}
	
	we_sys->haikei_chg_flag = ENUM_HMODE_CHG;
	
	return hcs;
}


//--------------------------------------------------------------
/**
 * @brief	[ 背景切り替え ] αブレンド
 *
 * @param	tcb	
 * @param	wk	
 *
 * @retval	static BOOL	
 *
 */
//--------------------------------------------------------------
static BOOL HaikeiChange_Blend(TCB_PTR tcb, HC_SYS_PTR wk)
{
	switch(wk->seq){
	case 0:
		///< エフェクト面に背景と同じBGを展開
		WeSysBaseBGSet(wk->we_sys, BATTLE_FRAME_EFFECT);
		{
			int pri1 = BT_BGPriorityGet(wk->we_sys, WES_BF_BACKGROUND);
			int pri2 = BT_BGPriorityGet(wk->we_sys, WES_BF_EFFECT);

			GF_BGL_PrioritySet(BATTLE_FRAME_BACKGROUND,	pri1);
			GF_BGL_PrioritySet(BATTLE_FRAME_EFFECT,		pri1);
		}
		GF_BGL_VisibleSet(BATTLE_FRAME_EFFECT, VISIBLE_ON);

		wk->seq++;
		break;

	case 1:
		///< α値の初期化
		{

			GF_BGL_BGControlReset(wk->we_sys->bgl, BATTLE_FRAME_BACKGROUND, BGL_RESET_CHRBASE, GX_BG_CHARBASE_0x0c000);
			if (WES_ContestFlag_Get(wk->we_sys) != TRUE){
				GF_BGL_BGControlReset(wk->we_sys->bgl, BATTLE_FRAME_BACKGROUND, BGL_RESET_COLOR, GX_BG_COLORMODE_16);
			}
			HaikeiChange_DataSet(wk, wk->we_sys, BATTLE_FRAME_BACKGROUND, wk->bg_id);		
		
			G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG2, GX_BLEND_PLANEMASK_BG3, wk->ev2, wk->ev1);

			HaikeiSubSystemFirstCall(wk);			
		}
		wk->seq++;
		
	case 2:
		///< αフェード
		{
			int ev_sw = 0;
			if (wk->ev1 < wk->ev1_e){
				wk->ev1 += 2;
			}
			else {
				ev_sw++;
			}
			if (wk->ev2 > wk->ev2_e){
				wk->ev2 -= 2;
			}
			else {
				ev_sw++;
			}
			if (ev_sw == 2){
				wk->ev1 = wk->ev1_e;
				wk->ev2 = wk->ev2_e;
				wk->seq++;
			}
			G2_ChangeBlendAlpha(wk->ev2, wk->ev1);
			
			if (wk->seq != 2){
				return FALSE;
			}
		}
		break;

	default:
		return FALSE;
	}
	return TRUE;
}


static BOOL HaikeiRecover_Blend(TCB_PTR tcb, HC_SYS_PTR wk)
{
	switch(wk->seq){
	case 0:
		///< 背景BGをエフェクト面に展開
	//	WeSysBaseBGSet(wk->we_sys, BATTLE_FRAME_EFFECT);
		GF_BGL_VisibleSet(BATTLE_FRAME_EFFECT, VISIBLE_ON);
		wk->seq++;

	case 1:
		///< α値の初期化
		{
			int pri1 = BT_BGPriorityGet(wk->we_sys, WES_BF_BACKGROUND);
			int pri2 = BT_BGPriorityGet(wk->we_sys, WES_BF_EFFECT);

			GF_BGL_PrioritySet(BATTLE_FRAME_BACKGROUND,	pri1);
			GF_BGL_PrioritySet(BATTLE_FRAME_EFFECT,		pri1);

			G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG2, GX_BLEND_PLANEMASK_BG3, wk->ev1, wk->ev2);

			HaikeiSubSystemFirstCall(wk);			
		}
		wk->seq++;

	case 2:
		///< αフェード
		{
			int ev_sw = 0;
			if (wk->ev1 < wk->ev1_e){
				wk->ev1 += 2;
			}
			else {
				ev_sw++;
			}
			if (wk->ev2 > wk->ev2_e){
				wk->ev2 -= 2;
			}
			else {
				ev_sw++;
			}
			if (ev_sw == 2){
				wk->ev1 = wk->ev1_e + 2;
				wk->ev2 = wk->ev2_e - 2;
				wk->seq++;
			}
			G2_ChangeBlendAlpha(wk->ev1, wk->ev2);
		}
		break;
	
	case 3:
		///< エフェクト面に背景を残しつつ、背景を復帰させる
		if (wk->move_flag == 1){
			BT_HaikeiSubSystemStop(wk->we_sys);						///< 背景サブシステム停止
		}
		if (wk->laster_flag == 1){
			BT_HaikeiSubSystemStop(wk->we_sys);						///< 背景サブシステム停止
		}
		
		GF_BGL_ScrollSet(wk->we_sys->bgl, BATTLE_FRAME_BACKGROUND,	GF_BGL_SCROLL_X_SET, 0);
		GF_BGL_ScrollSet(wk->we_sys->bgl, BATTLE_FRAME_BACKGROUND,	GF_BGL_SCROLL_Y_SET, 0);

		GF_BGL_BGControlReset(wk->we_sys->bgl, BATTLE_FRAME_BACKGROUND, BGL_RESET_CHRBASE,	GX_BG_CHARBASE_0x10000);
		if (WES_ContestFlag_Get(wk->we_sys) == FALSE){
			GF_BGL_BGControlReset(wk->we_sys->bgl, BATTLE_FRAME_BACKGROUND, BGL_RESET_COLOR,	GX_BG_COLORMODE_256);

			WeSys_BattleBGDraw(wk->we_sys, BATTLE_FRAME_BACKGROUND);
			WeSys_BattlePaletteTrans(wk->we_sys);
		}
		else {
					
			ArcUtil_BgCharSet(wk->we_sys->haikei_data.arc_index,
							  wk->we_sys->haikei_data.chr_id,
							  wk->we_sys->bgl,
							  BATTLE_FRAME_BACKGROUND,0,0,1,wk->we_sys->heap_area);
							  
			PaletteWorkSet_Arc(wk->we_sys->pfd,
							   wk->we_sys->haikei_data.arc_index,
							   wk->we_sys->haikei_data.pal_id,
							   wk->we_sys->heap_area, FADE_MAIN_BG,
							   wk->we_sys->haikei_data.pal_num * 0x20,
							   wk->we_sys->haikei_data.pal_start);

		}
		ArcUtil_ScrnSet(wk->we_sys->haikei_data.arc_index,
						wk->we_sys->haikei_data.scr_id,
						wk->we_sys->bgl,
						BATTLE_FRAME_BACKGROUND, 0, 0, 1, wk->we_sys->heap_area);
		wk->seq++;
		break;
	
	case 4:
		///< エフェクト面をリセットする
		if (WES_ContestFlag_Get(wk->we_sys) == FALSE){
			BattleDefaultBlendSet();
		}
		else {
			ActinExTool_DefaultBlendSet();
		}
		WeSysBaseBGReset(wk->we_sys, BATTLE_FRAME_EFFECT);
		wk->seq++;
		break;

	default:
		return FALSE;
	}

	return TRUE;
}


//--------------------------------------------------------------
/**
 * @brief	[ 背景切り替え ] フェードする
 *
 * @param	tcb	
 * @param	wk	
 *
 * @retval	static BOOL	
 *
 */
//--------------------------------------------------------------
static BOOL HaikeiChange_Fade(TCB_PTR tcb, HC_SYS_PTR wk)
{
	switch(wk->seq){
		
	case 0:
		///< フェード開始
		if (wk->fade_type == 0){
			PaletteFadeReq(wk->we_sys->pfd, PF_BIT_MAIN_BG, wk->we_sys->haikei_fade_bit, WES_HAIKEI_FO_WAIT, 0, 16, 0);
			ColorConceChangePfd(wk->we_sys->pfd, FADE_MAIN_BG, 0x200, 16, 0);
		}
		else {
			PaletteFadeReq(wk->we_sys->pfd, PF_BIT_MAIN_BG, wk->we_sys->haikei_fade_bit, WES_HAIKEI_FO_WAIT, 0, 16, 0xFFFF);
			ColorConceChangePfd(wk->we_sys->pfd, FADE_MAIN_BG, 0x200, 16, 0xFFFF);
		}
		wk->seq++;
	
	case 1:
		///< フェード終了 モード切替
		if (PaletteFadeCheck(wk->we_sys->pfd) != 0){ break; }
		
		GF_BGL_BGControlReset(wk->we_sys->bgl, BATTLE_FRAME_BACKGROUND, BGL_RESET_COLOR, GX_BG_COLORMODE_16);
		HaikeiChange_DataSet(wk, wk->we_sys, BATTLE_FRAME_BACKGROUND, wk->bg_id);

		if (wk->fade_type == 0){
			PaletteFadeReq(wk->we_sys->pfd, PF_BIT_MAIN_BG, (1 << BATTLE_PAL_EFF_1), WES_HAIKEI_FI_WAIT, 16, 0, 0);
		}
		else {
			PaletteFadeReq(wk->we_sys->pfd, PF_BIT_MAIN_BG, (1 << BATTLE_PAL_EFF_1), WES_HAIKEI_FI_WAIT, 16, 0, 0xFFFF);
		}
	
		HaikeiSubSystemFirstCall(wk);
		wk->we_sys->haikei_chg_flag = ENUM_HMODE_HALF;

		wk->seq++;
		break;
	
	default:
		if (PaletteFadeCheck(wk->we_sys->pfd) != 0){ break; }
		
		return FALSE;		
	}
	
	return TRUE;
}


//--------------------------------------------------------------
/**
 * @brief	[ 背景復帰 ] フェード
 *
 * @param	tcb	
 * @param	wk	
 *
 * @retval	static BOOL	
 *
 */
//--------------------------------------------------------------
static BOOL HaikeiRecover_Fade(TCB_PTR tcb, HC_SYS_PTR wk)
{
	switch(wk->seq){
	case 0:
		///< 起動
		HaikeiSubSystemFirstCall(wk);
		wk->seq++;
	
	case 1:
		///< フェード開始
		if (wk->fade_type == 0){
			PaletteFadeReq(wk->we_sys->pfd, PF_BIT_MAIN_BG, (1 << BATTLE_PAL_EFF_1), WES_HAIKEI_FO_WAIT,  0, 16, 0);
			ColorConceChangePfd(wk->we_sys->pfd, FADE_MAIN_BG, wk->we_sys->haikei_fade_bit, 16, 0);
		}
		else {
			PaletteFadeReq(wk->we_sys->pfd, PF_BIT_MAIN_BG, (1 << BATTLE_PAL_EFF_1), WES_HAIKEI_FO_WAIT,  0, 16, 0xFFFF);
			ColorConceChangePfd(wk->we_sys->pfd, FADE_MAIN_BG, wk->we_sys->haikei_fade_bit, 16, 0xFFFF);
		}
		wk->seq++;
		
	case 2:
		if (PaletteFadeCheck(wk->we_sys->pfd) != 0){ break; }

		if (wk->move_flag == 1){
			BT_HaikeiSubSystemStop(wk->we_sys);						///< 背景サブシステム停止
		}
		if (wk->laster_flag == 1){
			BT_HaikeiSubSystemStop(wk->we_sys);						///< 背景サブシステム停止
		}
		
		GF_BGL_VisibleSet(BATTLE_FRAME_BACKGROUND, VISIBLE_OFF);	///< カラーモードの変更のためBGをOFF
	
		if (WES_ContestFlag_Get(wk->we_sys) == FALSE){
			GF_BGL_BGControlReset(wk->we_sys->bgl, BATTLE_FRAME_BACKGROUND, BGL_RESET_COLOR, GX_BG_COLORMODE_256);
				
			WeSys_BattleBGDraw(wk->we_sys, BATTLE_FRAME_BACKGROUND);
			WeSys_BattlePaletteTrans(wk->we_sys);
		}
		else {	
			ArcUtil_BgCharSet(wk->we_sys->haikei_data.arc_index,
							  wk->we_sys->haikei_data.chr_id,
							  wk->we_sys->bgl,
							  BATTLE_FRAME_BACKGROUND,0,0,1,wk->we_sys->heap_area);

			PaletteWorkSet_Arc(wk->we_sys->pfd,
							   wk->we_sys->haikei_data.arc_index,
							   wk->we_sys->haikei_data.pal_id,
							   wk->we_sys->heap_area, FADE_MAIN_BG,
							   wk->we_sys->haikei_data.pal_num * 0x20,
							   wk->we_sys->haikei_data.pal_start);
		}
		
		ArcUtil_ScrnSet(wk->we_sys->haikei_data.arc_index,
						wk->we_sys->haikei_data.scr_id,
						wk->we_sys->bgl,
						BATTLE_FRAME_BACKGROUND, 0, 0, 1, wk->we_sys->heap_area);
		
		GF_BGL_VisibleSet(BATTLE_FRAME_BACKGROUND, VISIBLE_ON);		///< すべて展開後にBGをON
		wk->seq++;

	case 3:
		GF_BGL_ScrollSet(wk->we_sys->bgl, BATTLE_FRAME_BACKGROUND,	GF_BGL_SCROLL_X_SET, 0);
		GF_BGL_ScrollSet(wk->we_sys->bgl, BATTLE_FRAME_BACKGROUND,	GF_BGL_SCROLL_Y_SET, 0);
		if (wk->fade_type == 0){
			PaletteFadeReq(wk->we_sys->pfd, PF_BIT_MAIN_BG, wk->we_sys->haikei_fade_bit, WES_HAIKEI_FI_WAIT, 16, 0, 0);
		//	ColorConceChangePfd(wk->we_sys->pfd, FADE_MAIN_BG, WES_HAIKEI_PAL, 16, 0);
		}
		else {
			PaletteFadeReq(wk->we_sys->pfd, PF_BIT_MAIN_BG, wk->we_sys->haikei_fade_bit, WES_HAIKEI_FI_WAIT, 16, 0, 0xFFFF);
		//	ColorConceChangePfd(wk->we_sys->pfd, FADE_MAIN_BG, WES_HAIKEI_PAL, 16, 0xFFFF);
		}
		wk->seq++;
	
	default:
		if (PaletteFadeCheck(wk->we_sys->pfd) != 0){ break; }

		wk->we_sys->haikei_chg_flag = ENUM_HMODE_HALF;
		wk->seq++;
		return FALSE;
	}
	return TRUE;
}


static BOOL HaikeiChange_None(TCB_PTR tcb, HC_SYS_PTR wk)
{
	HaikeiSubSystemFirstCall(wk);

	return FALSE;
}

static BOOL HaikeiRecover_None(TCB_PTR tcb, HC_SYS_PTR wk)
{
	HaikeiSubSystemFirstCall(wk);
	
	if (wk->move_flag == 1){
		BT_HaikeiSubSystemStop(wk->we_sys);						///< 背景サブシステム停止
	}

	return FALSE;
}

// =============================================================================
//
//
//	■背景切り替えサブシステム
//
//
// =============================================================================
//--------------------------------------------------------------
/**
 * @brief	スクロールTCB
 *
 * @param	tcb	
 * @param	work	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void HaikeiSubSysmte_Scroll(TCB_PTR tcb, void* work)
{
	HC_SUB_PTR wk = (HC_SUB_PTR)work;
	
	if (wk->destroy == TRUE){
		sys_FreeMemoryEz(wk);
		TCB_Delete(tcb);
		return;
	}

	wk->pos_x += wk->speed_x;
	wk->pos_y += wk->speed_y;
	
	if (wk->speed_x != 0){
		GF_BGL_ScrollSet(wk->bgl, wk->frm1, GF_BGL_SCROLL_X_SET, wk->pos_x);
	}
	
	if (wk->speed_y != 0){
		GF_BGL_ScrollSet(wk->bgl, wk->frm1, GF_BGL_SCROLL_Y_SET, wk->pos_y);	
	}
}


//--------------------------------------------------------------
/**
 * @brief	サブシステム停止
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void BT_HaikeiSubSystemStop(WE_SYS_PTR we_sys)
{
	GF_ASSERT(we_sys);

	if (we_sys->hc_sub_ptr == NULL){ return; }
	
	we_sys->hc_sub_ptr->destroy = TRUE;
}


//--------------------------------------------------------------
/**
 * @brief	サブシステムフレーム切り替え
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void BT_HaikeiSubSystemFrameChange(WE_SYS_PTR we_sys)
{
	int frm;

//	GF_ASSERT(we_sys);
//	GF_ASSERT(we_sys->hc_sub_ptr);
	
	frm = we_sys->hc_sub_ptr->frm1;
	we_sys->hc_sub_ptr->frm1 = we_sys->hc_sub_ptr->frm2;
	we_sys->hc_sub_ptr->frm2 = frm;
}


//--------------------------------------------------------------
/**
 * @brief	背景フェードビット取得
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
int	BT_HaikeiFadeBit(WE_SYS_PTR we_sys)
{
	return we_sys->haikei_fade_bit;
}


//--------------------------------------------------------------
/**
 * @brief	背景切り替えサブシステム
 *
 * @param	wk	
 *
 * @retval	static BOOL	
 *
 */
//--------------------------------------------------------------
static BOOL HaikeiSubSystem_None(HC_SYS_PTR wk)
{
	return FALSE;
}


//--------------------------------------------------------------
/**
 * @brief	背景切り替えサブシステム [ 背景スクロール ]
 *
 * @param	wk	
 *
 * @retval	static BOOL	
 *
 */
//--------------------------------------------------------------
static BOOL HaikeiSubSystem_Move(HC_SYS_PTR wk)
{
	int i;
	HC_SUB_PTR hs;
	
	hs = sys_AllocMemory(wk->we_sys->heap_area, sizeof(HC_SUB_SYS));
	
	hs->bgl		= wk->we_sys->bgl;

	hs->pos_x	= wk->we_sys->waza_eff_gp_wk[ WEDEF_GP_INDEX_BGPOS_X ];
	hs->pos_y	= wk->we_sys->waza_eff_gp_wk[ WEDEF_GP_INDEX_BGPOS_Y ];
	hs->speed_x	= wk->we_sys->waza_eff_gp_wk[ WEDEF_GP_INDEX_SPEED_X ];
	hs->speed_y	= wk->we_sys->waza_eff_gp_wk[ WEDEF_GP_INDEX_SPEED_Y ];
	hs->frm1	= BATTLE_FRAME_BACKGROUND;//BATTLE_FRAME_EFFECT;
	hs->frm2	= BATTLE_FRAME_BACKGROUND;
	
	if (HaikeiChange_ParamRev(wk, wk->we_sys, WEDEF_GP_INDEX_SPEED_R) == TRUE){
		hs->speed_x *= -1;
		hs->speed_y *= -1;
		hs->pos_x	*= -1;
		hs->pos_y	*= -1;
	}
	
	hs->active  = TRUE;
	hs->destroy = FALSE;
	
	wk->we_sys->hc_sub_ptr = hs;
	
	wk->move_flag = 1;
	
	TCB_Add(HaikeiSubSysmte_Scroll, hs, 0x1001);
	
	return FALSE;
}

static BOOL HaikeiSubSystem_LasterScroll_Init(HC_SYS_PTR wk)
{
	int i, j;
	WE_SYS_PTR wsp;
	HC_SUB_PTR hs;
	
	wsp = wk->we_sys;
	
	hs = sys_AllocMemory(wk->we_sys->heap_area, sizeof(HC_SUB_SYS));
	hs->hls = sys_AllocMemory(wsp->heap_area, sizeof(HC_LASTER_SYS));
	
	wsp->hc_sub_ptr = hs;
	
	wk->laster_flag = 1;
	hs->destroy = FALSE;

	hs->hls->dlp = WazaTool_InitDefLaster(WazaTool_GetLasterBGDestAddr(BT_BGL_BGNoGet(wsp, WES_BF_BACKGROUND)),
										  WazaTool_GetLasterBuffMatrixData(0, 0),
										  wsp->heap_area);
	for (i = 0; i < HC_LASTER_MAX; i++){
		hs->hls->lst[i].start	 = (i * HC_LASTER_VOFS);
		hs->hls->lst[i].end		 = (hs->hls->lst[i].start + HC_LASTER_VOFS);
		hs->hls->lst[i].speed	 = speed_tbl[i];
		hs->hls->lst[i].ofs		 = 0;
		hs->hls->lst[i].init	 = WazaTool_GetLasterBuffMatrixData(0, 0);
		
		if (HaikeiChange_ParamRev(wk, wk->we_sys, WEDEF_GP_INDEX_SPEED_R) == TRUE){
			hs->hls->lst[i].speed	 *= -1;
		}
	}
	
	TCB_Add(HaikeiSubSystem_LasterScroll, hs, 0x1000);	
	
	return FALSE;
}


static BOOL HaikeiSubSystem_LasterScroll_Stop(HC_SYS_PTR wk)
{
	WE_SYS_PTR wsp;
	HC_SUB_PTR hs;
	
	wsp = wk->we_sys;
	hs	= wk->we_sys->hc_sub_ptr;
	
	wk->laster_flag = 1;
	
	return FALSE;
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
static void HaikeiSubSystem_LasterScroll(TCB_PTR tcb, void* work)
{
	int	 i, j;
	u32* buff;
	HC_LASTER_SYS* wk = (HC_LASTER_SYS*)(((HC_SUB_PTR)work)->hls);
	HC_SUB_PTR hs = (HC_SUB_PTR)work;
	
	if (hs->destroy == TRUE){
		WazaTool_DeleteDefLaster(hs->hls->dlp);
		sys_FreeMemoryEz(hs->hls);
		sys_FreeMemoryEz(hs);
		TCB_Delete(tcb);
		return;
	}
	
	buff = WazaTool_GetDefLasterWriteBuff(wk->dlp);

	for (i = 0; i < HC_LASTER_MAX; i++){
		
		wk->lst[i].ofs += wk->lst[i].speed;
		
		for (j = wk->lst[i].start; j < wk->lst[i].end; j++){
			s16 now_x, now_y;
			
			now_x = wk->lst[i].init & 0xffff;
			now_y = wk->lst[i].init >> 16;

			buff[j] = WazaTool_GetLasterBuffMatrixData(now_x + wk->lst[i].ofs, now_y);
		}	
	}
}


//--------------------------------------------------------------
/**
 * @brief	基本背景をエフェクト面に描画
 *
 * @param	wsp	
 * @param	frm	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WeSysBaseBGSet(WE_SYS_PTR wsp, int frm)
{
	int pri = BT_BGPriorityGet(wsp, WES_BF_BACKGROUND);

	GF_BGL_PrioritySet(frm,	pri);
	GF_BGL_VisibleSet(frm, VISIBLE_OFF);

	if (WES_ContestFlag_Get(wsp) == TRUE){
		GF_BGL_BGControlReset(wsp->bgl, frm, BGL_RESET_CHRBASE, GX_BG_CHARBASE_0x10000);
	}
	else {
		GF_BGL_BGControlReset(wsp->bgl, frm, BGL_RESET_COLOR,	GX_BG_COLORMODE_256);
		GF_BGL_BGControlReset(wsp->bgl, frm, BGL_RESET_CHRBASE, GX_BG_CHARBASE_0x10000);
	}
	
	GF_BGL_ScrClear(wsp->bgl, frm);	

	if (WES_ContestFlag_Get(wsp) == TRUE){
		ArcUtil_BgCharSet(wsp->haikei_data.arc_index,
						  wsp->haikei_data.chr_id,
						  wsp->bgl,frm,0,0,1,wsp->heap_area);
	}
	else {
		WeSys_BattleBGDraw(wsp, frm);
	}
	
	ArcUtil_ScrnSet(wsp->haikei_data.arc_index,
					wsp->haikei_data.scr_id,
					wsp->bgl,frm,0,0,1,wsp->heap_area);
//	GF_BGL_VisibleSet(frm, VISIBLE_ON);
}

void WeSysBaseBGReset(WE_SYS_PTR wsp, int frm)
{
	int pri = BT_BGPriorityGet(wsp, WES_BF_EFFECT);

	GF_BGL_PrioritySet(frm,	pri);

	if (WES_ContestFlag_Get(wsp) == TRUE){
		GF_BGL_BGControlReset(wsp->bgl, frm, BGL_RESET_CHRBASE, GX_BG_CHARBASE_0x0c000);
	}
	else {
		GF_BGL_BGControlReset(wsp->bgl, frm, BGL_RESET_COLOR,	GX_BG_COLORMODE_16);
		GF_BGL_BGControlReset(wsp->bgl, frm, BGL_RESET_CHRBASE, GX_BG_CHARBASE_0x0c000);
	}
	GF_BGL_ScrClear(wsp->bgl, frm);
}

//--------------------------------------------------------------
/**
 * @brief	背景切り替えサブシステム [ 256→16モード変換 ]
 *
 * @param	wk	
 *
 * @retval	static BOOL	
 *
 */
//--------------------------------------------------------------
static BOOL HaikeiSubSystem_Drop(HC_SYS_PTR wk)
{	
	GF_BGL_BGControlReset(wk->we_sys->bgl, BATTLE_FRAME_BACKGROUND, BGL_RESET_COLOR,	GX_BG_COLORMODE_16);
	
	HaikeiChange_DataSet(wk, wk->we_sys, BATTLE_FRAME_BACKGROUND, wk->bg_id);

	///< 背景スクロールフラグが立っている場合、BG入れ替えじに背景スクロール面を入れ替える	
	if (wk->move_flag == 1){
		BT_HaikeiSubSystemFrameChange(wk->we_sys);
	}
	
	///< ラスターフラグがたっている場合、BG入れ替え時にラスター処理面を入れ替える
	if (wk->laster_flag == 1){
		if (wk->we_sys->hc_sub_ptr->hls->dlp != NULL){
			int now_addr = WazaTool_GetDefLasterTransAddr(wk->we_sys->hc_sub_ptr->hls->dlp);
			int bg_addr  = WazaTool_GetLasterBGDestAddr(BT_BGL_BGNoGet(wk->we_sys, WES_BF_BACKGROUND));
			int eff_addr = WazaTool_GetLasterBGDestAddr(BT_BGL_BGNoGet(wk->we_sys, WES_BF_EFFECT));
			if (now_addr == bg_addr){
				WazaTool_SetDefLasterTransAddr(wk->we_sys->hc_sub_ptr->hls->dlp, eff_addr);
			}
			else {
				WazaTool_SetDefLasterTransAddr(wk->we_sys->hc_sub_ptr->hls->dlp, bg_addr);
			}
		}
	}
	
	GF_BGL_ScrClear(wk->we_sys->bgl, BATTLE_FRAME_EFFECT);
	GF_BGL_VisibleSet(BATTLE_FRAME_EFFECT, VISIBLE_ON);
	
	return FALSE;
}


//--------------------------------------------------------------
/**
 * @brief	背景切り替えサブシステム [ 16→256モード変換 ]
 *
 * @param	wk	
 *
 * @retval	static BOOL	
 *
 */
//--------------------------------------------------------------
static BOOL HaikeiSubSystem_Recover(HC_SYS_PTR wk)
{
	switch(wk->sub_seq){
	case 0:
		///< 優先度切り替え+復帰データ書き込み
		{
			int pri1 = BT_BGPriorityGet(wk->we_sys, WES_BF_BACKGROUND);
			int pri2 = BT_3DPriorityGet(wk->we_sys);

			GF_BGL_PrioritySet(BATTLE_FRAME_EFFECT,		pri1);
			GF_BGL_PrioritySet(BATTLE_FRAME_BACKGROUND, pri2+1);
			
			///< 背景スクロールフラグが立っている場合、BG入れ替えじに背景スクロール面を入れ替える				
			if (wk->move_flag == 1){
				BT_HaikeiSubSystemFrameChange(wk->we_sys);
			}

			///< ラスターフラグがたっている場合、BG入れ替え時にラスター処理面を入れ替える
			if (wk->laster_flag == 1){
				if (wk->we_sys->hc_sub_ptr->hls->dlp != NULL){
					int now_addr = WazaTool_GetDefLasterTransAddr(wk->we_sys->hc_sub_ptr->hls->dlp);
					int bg_addr  = WazaTool_GetLasterBGDestAddr(BT_BGL_BGNoGet(wk->we_sys, WES_BF_BACKGROUND));
					int eff_addr = WazaTool_GetLasterBGDestAddr(BT_BGL_BGNoGet(wk->we_sys, WES_BF_EFFECT));
					if (now_addr == bg_addr){
						WazaTool_SetDefLasterTransAddr(wk->we_sys->hc_sub_ptr->hls->dlp, eff_addr);
					}
					else {
						WazaTool_SetDefLasterTransAddr(wk->we_sys->hc_sub_ptr->hls->dlp, bg_addr);
					}
				}
			}
		}
		wk->sub_seq++;
		break;
	
	case 1:
		///< 優先度変更
		if (wk->move_flag != 1){	
			GF_BGL_ScrollSet(wk->we_sys->bgl, BATTLE_FRAME_BACKGROUND,	GF_BGL_SCROLL_X_SET, 0);
			GF_BGL_ScrollSet(wk->we_sys->bgl, BATTLE_FRAME_BACKGROUND,	GF_BGL_SCROLL_Y_SET, 0);
		}
	
		GF_BGL_ScrollSet(wk->we_sys->bgl, BATTLE_FRAME_EFFECT,		GF_BGL_SCROLL_X_SET, 0);
		GF_BGL_ScrollSet(wk->we_sys->bgl, BATTLE_FRAME_EFFECT,		GF_BGL_SCROLL_Y_SET, 0);

		HaikeiChange_DataSet(wk, wk->we_sys, BATTLE_FRAME_EFFECT, wk->bg_id);

		wk->sub_seq++;			
		break;
	
	case 2:
		///< 優先度切り替え+元データ書き込み
		{
			int pri1 = BT_BGPriorityGet(wk->we_sys, WES_BF_BACKGROUND);
			
			GF_BGL_PrioritySet(BATTLE_FRAME_EFFECT,		pri1);
			GF_BGL_PrioritySet(BATTLE_FRAME_BACKGROUND, pri1);
			
			if (WES_ContestFlag_Get(wk->we_sys) == TRUE){
				ArcUtil_BgCharSet(wk->we_sys->haikei_data.arc_index,
								  wk->we_sys->haikei_data.chr_id,
					 			  wk->we_sys->bgl,
								  BATTLE_FRAME_BACKGROUND,0,0,1,wk->we_sys->heap_area);

				PaletteWorkSet_Arc(wk->we_sys->pfd,
								   wk->we_sys->haikei_data.arc_index,
								   wk->we_sys->haikei_data.pal_id,
								   wk->we_sys->heap_area, FADE_MAIN_BG,
								   wk->we_sys->haikei_data.pal_num * 0x20,
								   wk->we_sys->haikei_data.pal_start);
			}
			else {
				GF_BGL_BGControlReset(wk->we_sys->bgl, BATTLE_FRAME_BACKGROUND, BGL_RESET_COLOR, GX_BG_COLORMODE_256);
				WeSys_BattleBGDraw(wk->we_sys, BATTLE_FRAME_BACKGROUND);
				WeSys_BattlePaletteTrans(wk->we_sys);
			}

			ArcUtil_ScrnSet(wk->we_sys->haikei_data.arc_index,
							wk->we_sys->haikei_data.scr_id,
							wk->we_sys->bgl,
							BATTLE_FRAME_BACKGROUND, 0, 0, 1, wk->we_sys->heap_area);
		}
		wk->sub_seq++;
		break;
	
	default:
		wk->sub_seq = 0;
		return FALSE;
	}					

	return TRUE;
}


//--------------------------------------------------------------
/**
 * @brief	背景切り替えサブシステム [ 背景の停止 ]
 *
 * @param	wk	
 *
 * @retval	static BOOL	
 *
 */
//--------------------------------------------------------------
static BOOL HaikeiSubSystem_Stop(HC_SYS_PTR wk)
{
	wk->move_flag = 1;
	
	return FALSE;
}


//--------------------------------------------------------------
/**
 * @brief	背景切り替えサブシステム [ サブシステムの停止 ] 
 *
 * @param	wk	
 *
 * @retval	static BOOL	
 *
 */
//--------------------------------------------------------------
static BOOL HaikeiSubSystem_Exit(HC_SYS_PTR wk)
{
	BT_HaikeiSubSystemStop(wk->we_sys);
	
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief	背景切り替え用のTCB
 *
 * @param	tcb	
 * @param	work	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void HaikeiChange_TCB(TCB_PTR tcb, void* work)
{
	HC_SYS_PTR wk = (HC_SYS_PTR)work;
	BOOL active;
	
	active = HaikeiChange_Table[ wk->ch_mode ](tcb, wk);
	
	if (active == FALSE){		
		wk->we_sys->haikei_chg_flag = ENUM_HMODE_NONE;
		
		sys_FreeMemoryEz(wk);
		TCB_Delete(tcb);
	}
}


//--------------------------------------------------------------
/**
 * @brief	背景切り替え
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_HAIKEI_CHG(WE_SYS_PTR we_sys)
{
	HC_SYS_PTR wk;
	int temp;
	
	wk = HaikeiControlInit(we_sys);
	
	wk->fade_type = WeSysGPWorkGet(we_sys, WEDEF_GP_INDEX_FADE_TYPE);

	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	wk->bg_id = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	temp = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	wk->ch_mode = (temp & 0x0000FFFF);
	wk->ch_sbit = (temp & 0xFFFF0000) >> WEDEF_HAIKEI_SHIFT;
	
	TCB_Add(HaikeiChange_TCB, wk, TCBPRI_HAIKEI_CHANGE);
}


//--------------------------------------------------------------
/**
 * @brief	背景パラメーター変更
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_HAIKEI_PARA_CHG(WE_SYS_PTR we_sys)
{
	int id;
	s16	param;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	id = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	param = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	switch(id){
	case WEDEF_GP_INDEX_SPEED_X:
		we_sys->hc_sub_ptr->speed_x = param;
		break;
	case WEDEF_GP_INDEX_SPEED_Y:
		we_sys->hc_sub_ptr->speed_y = param;
		break;
	case WEDEF_GP_INDEX_BGPOS_X:
		we_sys->hc_sub_ptr->pos_x = param;
		break;
	case WEDEF_GP_INDEX_BGPOS_Y:
		we_sys->hc_sub_ptr->pos_x = param;
		break;
	default:
		break;
	}
}


//--------------------------------------------------------------
/**
 * @brief	背景復帰
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_HAIKEI_RECOVER(WE_SYS_PTR we_sys)
{
	HC_SYS_PTR wk;
	int temp;
	
	wk = HaikeiControlInit(we_sys);
	
	wk->fade_type = WeSysGPWorkGet(we_sys, WEDEF_GP_INDEX_FADE_TYPE);

	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	wk->bg_id = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	temp = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	wk->ch_mode = (temp & 0x0000FFFF) + WEDEF_HAIKEI_MODE_END;
	wk->ch_sbit = (temp & 0xFFFF0000) >> WEDEF_HAIKEI_SHIFT;
	
	TCB_Add(HaikeiChange_TCB, wk, TCBPRI_HAIKEI_CHANGE);
}


//--------------------------------------------------------------
/**
 * @brief	背景切り替え中間待ち
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_HAIKEI_HALF_WAIT(WE_SYS_PTR we_sys)
{
	if (we_sys->haikei_chg_flag == ENUM_HMODE_HALF){
		ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
		we_sys->waza_eff_wait = 0;	
//		OS_Printf("背景切り替え待ち終了です\n");
	}
	else {
		we_sys->waza_eff_wait = 1;
//		OS_Printf("背景切り替え待ちです\n");
	}
}


//--------------------------------------------------------------
/**
 * @brief	背景切り替え待ち
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_HAIKEI_CHG_WAIT(WE_SYS_PTR we_sys)
{
	if (we_sys->haikei_chg_flag == ENUM_HMODE_NONE){
		ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
		we_sys->waza_eff_wait = 0;
	}
	else {
		we_sys->waza_eff_wait = 1;
	}
}


//--------------------------------------------------------------
/**
 * @brief	背景の瞬間切り替え
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_HAIKEI_SET(WE_SYS_PTR we_sys)
{
	int bg_id;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	bg_id = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	ArcUtil_BgCharSet(WE_HAIKEI_ARC,
					  WeSysHaikeiDataIDGet( bg_id, 0),
					  we_sys->bgl,
					  GF_BGL_FRAME3_M,0,0,1,we_sys->heap_area);
	
	ArcUtil_PalSet(WE_HAIKEI_ARC,
				   WeSysHaikeiDataIDGet( bg_id, 1),
				   PALTYPE_MAIN_BG,0,0,we_sys->heap_area);
	
	ArcUtil_ScrnSet(WE_HAIKEI_ARC,
					WeSysHaikeiDataIDGet( bg_id, 2),
					we_sys->bgl,
					GF_BGL_FRAME3_M,0,0,1,we_sys->heap_area);
}


//--------------------------------------------------------------
/**
 * @brief	シーンごとの背景設定
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_HAIKEI_CHKCHG(WE_SYS_PTR we_sys)
{
	HC_SYS_PTR wk;
	int bg1, bg2, bg3;
	
	wk = HaikeiControlInit(we_sys);

	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	bg1 = SeqAdrsGet(we_sys->waza_eff_seq_adrs);	///< 自分
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	bg2 = SeqAdrsGet(we_sys->waza_eff_seq_adrs);	///< 敵
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	bg3 = SeqAdrsGet(we_sys->waza_eff_seq_adrs);	///< コンテスト
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	if (WES_ContestFlag_Get(we_sys) == TRUE){
		wk->bg_id = bg3;
	}
	else {
		if (WET_SideCheck(we_sys, we_sys->btl_sys->df_client_no) == SIDE_MINE){
			wk->bg_id = bg2;
		}
		else {
			wk->bg_id = bg1;
		}
	}
	
	TCB_Add(HaikeiChange_TCB, wk, TCBPRI_HAIKEI_CHANGE);
}

/// とりあえずいらない。
static void WEST_BGPRI_GAPSET(WE_SYS_PTR we_sys)
{
}
static void WEST_BGPRI_GAPSET2(WE_SYS_PTR we_sys)
{
}
static void WEST_BGPRI_GAPSET3(WE_SYS_PTR we_sys)
{
}
static void WEST_PARTY_ATTACK_BGOFF(WE_SYS_PTR we_sys)
{
}
static void WEST_PARTY_ATTACK_BGEND(WE_SYS_PTR we_sys)
{
}

// =========================================
//
//	■サウンド関連
//		[ _COMMAND_SOUND_ ]
//
// =========================================
//--------------------------------------------------------------
/**
 * @brief	SEを再生
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_SE(WE_SYS_PTR we_sys)
{
	u16 se_no;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	se_no = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	Snd_SePlay(se_no);
}


//--------------------------------------------------------------
/**
 * @brief	SEの停止
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_SE_STOP(WE_SYS_PTR we_sys)
{
	u16 se_no;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	se_no = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	Snd_SeStopBySeqNo(se_no, 0);
}


//--------------------------------------------------------------
/**
 * @brief	パンを設定してSEを鳴らす
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_SEPLAY_PAN(WE_SYS_PTR we_sys)
{
	u16 se_no;
	int	pan;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	se_no = (u16)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	pan   = (int)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	pan = WeSysSePanGet(we_sys, pan);
	
	Snd_SePlay(se_no);
	Snd_SePanSet(se_no, 0xffff, pan);	
}


//--------------------------------------------------------------
/**
 * @brief	パンの設定
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_SEPAN(WE_SYS_PTR we_sys)
{
	int pan;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	pan = (int)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	pan = WeSysSePanGet(we_sys, pan);

	Snd_SePanSetAll(pan);
}


//--------------------------------------------------------------
/**
 * @brief	一定間隔でパンを変更する
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_SEPAN_FLOW(WE_SYS_PTR we_sys)
{
	SE_SYS_PTR ss = NULL;

	ss = SeControlInit(we_sys);
	
	memset(ss, 0, sizeof(TSE_SYS));
	ss->mode = ENUM_SEC_PAN_FLOW;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	ss->se_no = (u16)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	ss->s_pan = (int)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	ss->e_pan = (int)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	ss->a_pan = (int)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	ss->wait  = (u8)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	ss->s_pan = WeSysSePanGet(we_sys, ss->s_pan);
	ss->e_pan = WeSysSePanGet(we_sys, ss->e_pan);

	ss->a_pan = WeSysSePanAddGet(ss->s_pan, ss->e_pan, ss->a_pan);
//	OS_Printf("開始パン = %4d\n", ss->s_pan);
//	OS_Printf("終了パン = %4d\n", ss->e_pan);
//	OS_Printf("加算パン = %4d\n", ss->a_pan);
	Snd_SePlay(ss->se_no);
	Snd_SePanSet(ss->se_no, 0xffff, ss->s_pan);
	
	SeControlStart(we_sys, ss);
}


//--------------------------------------------------------------
/**
 * @brief	一定間隔でパンを変更する(敵味方の位置関係なし)
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_SEPAN_FLOWFIX(WE_SYS_PTR we_sys)
{
	SE_SYS_PTR ss = NULL;
	
	ss = SeControlInit(we_sys);
	
	memset(ss, 0, sizeof(TSE_SYS));
	ss->mode = ENUM_SEC_PAN_FLOW_FIX;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	ss->se_no = (u16)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	ss->s_pan = (s8)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	ss->e_pan = (s8)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	ss->a_pan = (s8)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	ss->wait  = (u8)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	Snd_SePlay(ss->se_no);
	Snd_SePanSet(ss->se_no, 0xffff, ss->s_pan);
	
	SeControlStart(we_sys, ss);
}


//--------------------------------------------------------------
/**
 * @brief	パンの値を一定間隔で変更していく
 *			パーティのことは考慮しない
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_SEPAN_FLOW_AF(WE_SYS_PTR we_sys)
{
	SE_SYS_PTR ss = NULL;
	
	ss = SeControlInit(we_sys);
	
	memset(ss, 0, sizeof(TSE_SYS));
	ss->mode = ENUM_SEC_PAN_FLOW;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	ss->se_no = (u16)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	ss->s_pan = (s8)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	ss->e_pan = (s8)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	ss->a_pan = (s8)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	ss->wait  = (u8)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	ss->s_pan = WeSysSePanGet(we_sys, ss->s_pan);
	ss->e_pan = WeSysSePanGet(we_sys, ss->e_pan);
	ss->a_pan = WeSysSePanGet(we_sys, ss->a_pan);

	Snd_SePlay(ss->se_no);
	Snd_SePanSet(ss->se_no, 0xffff, ss->s_pan);
	
	SeControlStart(we_sys, ss);
}


//--------------------------------------------------------------
/**
 * @brief	指定回数リピートする
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_SE_REPEAT(WE_SYS_PTR we_sys)
{
	SE_SYS_PTR ss = NULL;
	
	ss = SeControlInit(we_sys);
	
	memset(ss, 0, sizeof(TSE_SYS));
	ss->mode = ENUM_SEC_REPEAT;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	ss->se_no = (u16)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	ss->n_pan = (s8)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	ss->wait = (u8)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	ss->repeat = (u8)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	ss->gene_wait = ss->wait;
	
	ss->n_pan = WeSysSePanGet(we_sys, ss->n_pan);
	
	SeControlStart(we_sys, ss);
}


//--------------------------------------------------------------
/**
 * @brief	wait時間待ってから再生する
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_SE_WAITPLAY(WE_SYS_PTR we_sys)
{
	SE_SYS_PTR ss = NULL;
	
	ss = SeControlInit(we_sys);
	
	memset(ss, 0, sizeof(TSE_SYS));
	ss->mode = ENUM_SEC_WAIT_PLAY;

	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	ss->se_no = (u16)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	ss->n_pan = (s8)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	ss->wait  = (u8)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	ss->n_pan = WeSysSePanGet(we_sys, ss->n_pan);

	SeControlStart(we_sys, ss);
}


//--------------------------------------------------------------
/**
 * @brief	SE用のTCBを作成する
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_SE_TASK(WE_SYS_PTR we_sys)
{
}


//--------------------------------------------------------------
/**
 * @brief	なり終わるまでwait
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_SEWAIT_FLAG(WE_SYS_PTR we_sys)
{
	if (we_sys->waza_se_num){
		we_sys->waza_eff_wait = 1;
		we_sys->se_end_timer = 0;
		return;
	}

	if (Snd_SePlayCheckAll()){							///< SEが再生されていた場合
		we_sys->se_end_timer++;

		if (we_sys->se_end_timer > WE_SE_END_TIMER){	///< 終了3秒は待つ
			// エフェクト関連SEをとめる
			;
			;
			we_sys->se_end_timer = 0;
		}
		else {
			we_sys->waza_eff_wait = 1;
			return;
		}
	}
	else {
		we_sys->waza_eff_wait = 0;
		we_sys->se_end_timer = 0;
		ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	}
}


// =========================================
//
//	■レジスタ操作系
//		[ _COMMAND_REG_ ]
//
// =========================================
//--------------------------------------------------------------
/**
 * @brief	αブレンドを行なう
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_BLDALPHA_SET(WE_SYS_PTR we_sys)
{
	u16 eva;
	u16 evb;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	eva = (u16)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	evb = (u16)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	G2S_SetBlendAlpha(ENUM_WES_BLD_PLANE_1,
					  ENUM_WES_BLD_PLANE_2, eva, evb);
}


//--------------------------------------------------------------
/**
 * @brief	αブレンド初期化
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_BLDALPHA_RESET(WE_SYS_PTR we_sys)
{
	DefaultBlendSet();
}


static void WEST_BLDCNT_SET(WE_SYS_PTR we_sys)
{
}

// =============================================================================
//
//
//	■アクター関連
//		[ _COMMAND_CLACT_ ]
//
//
// =============================================================================
//--------------------------------------------------------------
/**
 * @brief	リソースシステムの初期化
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_CATS_RES_INIT(WE_SYS_PTR we_sys)
{
	int i;
	int res_no;
	int obj_num;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	res_no = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	obj_num = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	GF_ASSERT(we_sys->crp[res_no] == NULL);
	
	we_sys->crp[res_no] = CATS_ResourceCreate(we_sys->btl_sys->csp);
	
	GF_ASSERT(we_sys->crp[res_no] != NULL);
	
	///< 初期化
	CATS_ClactSetInit(we_sys->btl_sys->csp, we_sys->crp[res_no], obj_num);
	CLACT_U_SetSubSurfaceMatrix(CATS_EasyRenderGet(we_sys->btl_sys->csp), 0, BATTLE_SUB_ACTOR_DISTANCE);
	
	{
		TCATS_RESOURCE_NUM_LIST crnl;
		
		for (i = 0; i < CLACT_U_RES_MAX; i++){
			crnl.res_num[i] = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
			ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
		}
		CATS_ResourceManagerInit(we_sys->btl_sys->csp, we_sys->crp[res_no], &crnl);
	}
}


//--------------------------------------------------------------
/**
 * @brief	キャラリソース読み込み
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_CATS_CHAR_RES_LOAD(WE_SYS_PTR we_sys)
{
	int res_no;
	int	arc_id;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	res_no = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	arc_id = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	CATS_LoadResourceCharArc(we_sys->btl_sys->csp, we_sys->crp[res_no],
							 ARC_WER_CHAR, arc_id, TRUE, NNS_G2D_VRAM_TYPE_2DMAIN, arc_id + EFF_ARC_ID_BASE);
}


//--------------------------------------------------------------
/**
 * @brief	パレットリソース読み込み
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_CATS_PLTT_RES_LOAD(WE_SYS_PTR we_sys)
{
	int res_no;
	int	arc_id;
	int pal_num;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	res_no = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	arc_id = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	pal_num = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);	

	CATS_LoadResourcePlttWorkArc(we_sys->pfd, FADE_MAIN_OBJ,
								 we_sys->btl_sys->csp, we_sys->crp[res_no],
							 	 ARC_WER_PLTT, arc_id, 0, NNS_G2D_VRAM_TYPE_2DMAIN, pal_num, arc_id + EFF_ARC_ID_BASE);	
}


//--------------------------------------------------------------
/**
 * @brief	セルリソース読み込み
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_CATS_CELL_RES_LOAD(WE_SYS_PTR we_sys)
{
	int res_no;
	int	arc_id;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	res_no = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	arc_id = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	CATS_LoadResourceCellArc(we_sys->btl_sys->csp, we_sys->crp[res_no],
							 ARC_WER_CELL, arc_id, TRUE, arc_id + EFF_ARC_ID_BASE);	
}


//--------------------------------------------------------------
/**
 * @brief	セルアニメリソース読み込み
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_CATS_CELL_ANM_RES_LOAD(WE_SYS_PTR we_sys)
{
	int res_no;
	int	arc_id;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	res_no = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	arc_id = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	CATS_LoadResourceCellAnmArc(we_sys->btl_sys->csp, we_sys->crp[res_no],
							 ARC_WER_CELLANM, arc_id, TRUE, arc_id + EFF_ARC_ID_BASE);		
}


//--------------------------------------------------------------
/**
 * @brief	アクター登録
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_CATS_ACT_ADD(WE_SYS_PTR we_sys)
{
	int i;
	int func_id;
	int res_no;
	int cnt;
	CATS_ACT_PTR cap;
	pWeClactFunc func;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	res_no = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	func_id = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	{
		TCATS_OBJECT_ADD_PARAM_S coap;
		int defence_client;
		
		defence_client = WeSysDFNoGet(we_sys);
		
		coap.x		= GetWazaEffPos(we_sys, defence_client, PM_X);
		coap.y		= GetWazaEffPos(we_sys, defence_client, PM_Y);
		coap.z		= 0;		
		coap.anm	= 0;
		coap.pri	= WAZAEFF_ACT_SOFTPRI;
		coap.pal	= 0;
		coap.d_area = CATS_D_AREA_MAIN;
		coap.bg_pri = WAZAEFF_ACT_BGPRI;
		coap.vram_trans = 0;
		
		for (i = 0; i < CLACT_U_RES_MAX; i++){
			coap.id[i] = SeqAdrsGet(we_sys->waza_eff_seq_adrs) + EFF_ARC_ID_BASE;
			ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
		}
		
		we_sys->coap = coap;
		
		cap  = CATS_ObjectAdd_S(we_sys->btl_sys->csp, we_sys->crp[res_no], &coap);
	}
	
	cnt = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	for (i = 0; i < cnt; i++){
		we_sys->waza_eff_gp_wk[i] = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
		ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	}
	for (; i < WE_GENE_WK_MAX; i++){
		we_sys->waza_eff_gp_wk[i] = 0;
	}
	
	func = WazaEffectSupportFuncGet_CATS(func_id);
	
	func(we_sys, we_sys->btl_sys->csp, we_sys->crp[res_no], cap);
}


//--------------------------------------------------------------
/**
 * @brief	アクターの登録のみ行なう
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_CATS_ACT_ADD_EZ(WE_SYS_PTR we_sys)
{
	int i;
	int res_no;
	int cap_id;
	CATS_ACT_PTR cap;
	pWeClactFunc func;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	res_no = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	cap_id = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	{
		TCATS_OBJECT_ADD_PARAM_S coap;
		int defence_client;
		
		defence_client = WeSysDFNoGet(we_sys);
		
		coap.x		= GetWazaEffPos(we_sys, defence_client, PM_X);
		coap.y		= GetWazaEffPos(we_sys, defence_client, PM_Y);
		coap.z		= 0;		
		coap.anm	= 0;
		coap.pri	= WAZAEFF_ACT_SOFTPRI;
		coap.pal	= 0;
		coap.d_area = CATS_D_AREA_MAIN;
		coap.bg_pri = WAZAEFF_ACT_BGPRI;
		coap.vram_trans = 0;
		
		for (i = 0; i < CLACT_U_RES_MAX; i++){
			coap.id[i] = SeqAdrsGet(we_sys->waza_eff_seq_adrs) + EFF_ARC_ID_BASE;
			ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
		}
		
		we_sys->coap = coap;
		
		cap  = CATS_ObjectAdd_S(we_sys->btl_sys->csp, we_sys->crp[res_no], &coap);
		
		GF_ASSERT(we_sys->cap[ cap_id ] == NULL);
		
		we_sys->cap[ cap_id ] = cap;
	}
}


//--------------------------------------------------------------
/**
 * @brief	リソース破棄
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_CATS_RES_FREE(WE_SYS_PTR we_sys)
{
	int res_no;

	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	res_no = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	if (we_sys->crp[res_no] != NULL){
		CATS_ResourceDestructor_S(we_sys->btl_sys->csp, we_sys->crp[res_no]);
	}
	we_sys->crp[res_no] = NULL;
}

static void WEST_POKE_OAM_ENABLE(WE_SYS_PTR we_sys)
{
	int no;
	int flag;

	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	no = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);	
	
	flag = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	CATS_ObjectEnableCap(we_sys->poke_cap[no], flag);
}

//--------------------------------------------------------------
/**
 * @brief	データ列定義
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 * WeSysExDataGet関数を使用して定義しているデータを取得します。
 * CソースWeSysExDataGet関数を使用し、値取得、アドレス移動をするのでwe_sys.cのシステム上から
 * ここを通過する事はエラー処理になります。
 *
 * 例)
 * 	FUNC_CALL	WEST_SP_TEST_1, 0, 0
 * 	EX_DATA		3, 100, 200, 150
 * のようにした場合、FUNC_CALLで呼び出された関数の中でWeSysExDataGet関数で下のEX_DATA分のデータを
 * 取得しアドレスを進める必要があります。もし取得しなかった場合、we_sys.cから呼ばれる事になり、
 * エラー処理扱いとなります。
 */
//--------------------------------------------------------------
static void WEST_EX_DATA(WE_SYS_PTR we_sys)
{
	GF_ASSERT((0)&&"EX_DATAが実行されました");
}

//--------------------------------------------------------------
/**
 * @brief	鳴き声再生
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_VOICE_PLAY(WE_SYS_PTR we_sys)
{
	int type;
	s16 pan;
	int vol;
	int mons_no;

	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	type = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	pan = (s16)SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	pan = WeSysSePanGet(we_sys, pan);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	vol = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	mons_no = we_sys->btl_sys->mons_no[ we_sys->btl_sys->at_client_no ];
//	OS_Printf("mons_no = %d we_sys\n", mons_no);

	PokeVoicePlaySet(we_sys->btl_sys->perap_voice, type, mons_no, pan, vol, we_sys->btl_sys->henshin_flag, we_sys->heap_area);

//	Snd_PMVoicePlayEx( type, mons_no, pan, vol, we_sys->heap_area);

}

//--------------------------------------------------------------
/**
 * @brief	鳴き声待ち＋停止
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_VOICE_WAIT_STOP(WE_SYS_PTR we_sys)
{
	int frame;
		
	if( Snd_PMVoicePlayCheck() == 0 ){	//再生終了していたら
		ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
		frame = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
		ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
		
		we_sys->waza_eff_wait = 0;
		Snd_PMVoiceStop( frame );
	}
	else {
		we_sys->waza_eff_wait = 1;
	}
}

//--------------------------------------------------------------
/**
 * @brief	指定された関数を呼び出すコマンド
 *			アドレスから参照する引数
 *			呼び出す関数のアドレス
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void WEST_OLDACT_FUNC_CALL(WE_SYS_PTR we_sys)
{
#if 0
	int i;
	u32 id;
	u32 ah_no;
	u32 cnt, soft_pri;
	pWeOldActFunc func;
	CLACT_WORK_PTR act;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	id = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	ah_no = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	soft_pri = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	func = WazaEffectSupportFuncGet_OLDACT(id);

	cnt  = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	for (i = 0; i < cnt; i++){
		we_sys->waza_eff_gp_wk[i] = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
		ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	}

#if 0	//アクター変更のため、とりあえずFIX
	//アクター生成
	{
		TCAT_ADD_DATA cad = {
			0,								//アクターヘッダーの中の登録OBJの番号 0から
			128,128,						//x, y
			0, WAZAEFF_ACT_SOFTPRI, 0,		//anm, soft_pri, pal
			NNS_G2D_VRAM_TYPE_2DMAIN,		//d_area
		};
		int defence_client;
		
		defence_client = WeSysDFNoGet(we_sys);

		cad.x = GetWazaEffPos(we_sys, defence_client, PM_X);
		cad.y = GetWazaEffPos(we_sys, defence_client, PM_Y);
		cad.pri = soft_pri;
		
		//↓↓↓↓設定する必要あり↓↓↓↓
		//cad.no = 0;
		//cal.palno = 0;
		
		act = CAT_Clact_Add(we_sys->cat_sys[ah_no], &cad);
	}
#endif

	func(we_sys, we_sys->btl_sys->csp, we_sys->crp[ah_no], act);
#endif
}


// =============================================================================
//
//
//	■外部参照
//
//
// =============================================================================
//--------------------------------------------------------------
/**
 * @brief	テーブルからコマンドを取得する
 *
 * @param	id		コマンド番号
 *
 * @retval	pWeFunc	コマンド関数
 *
 */
//--------------------------------------------------------------
pWeFunc WazaEffectCommandGet(u32 id)
{
	if (id > EFFECT_CMD_MAX){
		return NULL;
	}
	
	return WazaEffectCmdList[id];
}


//--------------------------------------------------------------
/**
 * @brief	モードチェックする(戦闘・コンテスト・コンクール)
 *
 * @param	btl_sys	
 *
 * @retval	BOOL	
 *
 *
 */
//--------------------------------------------------------------
int WeSysModeGet(BTL_SYS_PTR btl_sys)
{
	return btl_sys->mode;
}


//--------------------------------------------------------------
/**
 * @brief	パンの状態を取得する
 *
 * @param	we_sys	
 * @param	pan	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
s8	WeSysSePanGet(WE_SYS_PTR we_sys, s8 pan)
{
	int pan_fix;
	
	pan_fix = pan;
	
	{
		int at = WeSysATNoGet(we_sys);
		int df = WeSysDFNoGet(we_sys);
		int at_side = WET_SideCheck(we_sys, at);
		int df_side = WET_SideCheck(we_sys, df);
	#if 1
			
		if (WET_SideCheck(we_sys, at) == SIDE_MINE
		&&	WET_SideCheck(we_sys, df) == SIDE_ENEMY){
			
			///< A to B
			
		}
		else if (WET_SideCheck(we_sys, at) == SIDE_ENEMY
			 &&	 WET_SideCheck(we_sys, df) == SIDE_MINE){
			
			pan_fix *= -1;
			
		}
		else if (WET_SideCheck(we_sys, at) == SIDE_MINE
			 &&	 WET_SideCheck(we_sys, df) == SIDE_MINE){
			
			if (pan_fix > 0){
				pan_fix *= -1;
			}
			
		}
		else if (WET_SideCheck(we_sys, at) == SIDE_ENEMY
			 &&	 WET_SideCheck(we_sys, df) == SIDE_ENEMY){
			
			if (pan_fix < 0){
				pan_fix *= -1;
			}
			
		}
	#else
		if (WET_SideCheck(we_sys, at) == SIDE_MINE
		&&	WET_SideCheck(we_sys, df) == SIDE_ENEMY){
			
			if (pan < 0){
				pan_fix *= -1;
			}
			
		}
		else if (WET_SideCheck(we_sys, at) == SIDE_ENEMY
			 &&	 WET_SideCheck(we_sys, df) == SIDE_MINE){
			
			if (pan > 0){
				pan_fix *= -1;
			}			
			
		}
		else {
				
			if (pan > 0){
				pan_fix *= -1;
			}
		}
	#endif
	}
	
	if (WES_ContestFlag_Get(we_sys) == TRUE){
		pan_fix *= -1;
	}
	
//	OS_Printf("pan [ s = %4d ] | [ e = %4d ]\n", pan, pan_fix);
	
	return pan_fix;
}


//--------------------------------------------------------------
/**
 * @brief	パンの状態を取得する　攻撃用
 *
 * @param	we_sys	
 * @param	pan	
 *
 * @retval	s8	
 *
 */
//--------------------------------------------------------------
s8 WeSysSePanAttackGet(WE_SYS_PTR we_sys, s8 pan)
{
	int pan_fix;
	
	pan_fix = pan;
	
	{
		int at = WeSysATNoGet(we_sys);
		int df = WeSysDFNoGet(we_sys);
		int at_side = WET_SideCheck(we_sys, at);
		int df_side = WET_SideCheck(we_sys, df);
			
		if (WET_SideCheck(we_sys, at) == SIDE_MINE
		&&	WET_SideCheck(we_sys, df) == SIDE_ENEMY){
			
			
		}
		else if (WET_SideCheck(we_sys, at) == SIDE_ENEMY
			 &&	 WET_SideCheck(we_sys, df) == SIDE_MINE){
			
			pan_fix *= -1;
			
		}
		else if (WET_SideCheck(we_sys, at) == SIDE_MINE
			 &&	 WET_SideCheck(we_sys, df) == SIDE_MINE){			
		}
		else if (WET_SideCheck(we_sys, at) == SIDE_ENEMY
			 &&	 WET_SideCheck(we_sys, df) == SIDE_ENEMY){
			
			pan_fix *= -1;
			
		}
	}
	
	if (WES_ContestFlag_Get(we_sys) == TRUE){
		pan_fix *= -1;
	}
		
//	OS_Printf("まえのパンの設定 ･･･ %4d\n", pan);
//	OS_Printf("現在のパンの設定 ･･･ %4d\n", pan_fix);
	
	return pan_fix;
}


//--------------------------------------------------------------
/**
 * @brief	開始～終点により、パンの加算値を決める
 *
 * @param	we_sys	
 * @param	pan	
 *
 * @retval	s8	
 *
 */
//--------------------------------------------------------------
s8 WeSysSePanAddGet(s8 s_pan, s8 e_pan,  s8 a_pan)
{
	s8 pan;
	
	if (s_pan < e_pan){
		pan = +abs(a_pan);
	}
	else if (s_pan > e_pan){
		pan = -abs(a_pan);
	}
	else {
		pan = 0;
	}
	
	return pan;
}

//--------------------------------------------------------------
/**
 * @brief   EX_DATAで定義しているデータ列を取得
 *
 * @param   we_sys		
 * @param   data[]		取得データ代入先(numで指定した分必要)
 * @param   num			取得データ数(EX_DATAに指定した数と一致している必要があります)
 *
 * @retval  TRUE:成功、FALSE:失敗
 */
//--------------------------------------------------------------
BOOL WeSysExDataGet(WE_SYS_PTR we_sys, int data[], int num)
{
	int cnt, i;
	
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	
	cnt = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
	ADRS_SHIFT(we_sys->waza_eff_seq_adrs);

	if(cnt != num){
		GF_ASSERT(cnt == num);
		return FALSE;
	}
	
	for(i = 0; i < num; i++){
		data[i] = SeqAdrsGet(we_sys->waza_eff_seq_adrs);
		ADRS_SHIFT(we_sys->waza_eff_seq_adrs);
	}
	return TRUE;
}


//--------------------------------------------------------------
/**
 * @brief	直前で設定されていた登録パラメーターの取得
 *
 * @param	we_sys	
 *
 * @retval	TCATS_OBJECT_ADD_PARAM_S	
 *
 */
//--------------------------------------------------------------
TCATS_OBJECT_ADD_PARAM_S WeSysCoapGet(WE_SYS_PTR we_sys)
{
	return we_sys->coap;
}


//--------------------------------------------------------------
/**
 * @brief	クライアントのタイプを取得する
 *
 * @param	we_sys
 * @param	no			クライアント番号
 *
 * @retval	int
 *
 */
//--------------------------------------------------------------
int WeSysClientTypeGet(WE_SYS_PTR we_sys, int no)
{
	return we_sys->btl_sys->client_type[no];
}



//--------------------------------------------------------------
/**
 * @brief	性別
 *
 * @param	we_sys	
 * @param	no	
 *
 * @retval	int	
 *
 */
//--------------------------------------------------------------
int WeSysSexGet(WE_SYS_PTR we_sys, int no)
{
	return we_sys->btl_sys->sex[no];	
}


//--------------------------------------------------------------
/**
 * @brief	モンスター番号
 *
 * @param	we_sys	
 * @param	no	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
int	WeSysMonsNoGet(WE_SYS_PTR we_sys, int no)
{
	return we_sys->btl_sys->mons_no[no];	
}

//--------------------------------------------------------------
/**
 * @brief	フォルムNo
 *
 * @param	we_sys	
 * @param	no	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
int	WeSysFormNoGet(WE_SYS_PTR we_sys, int no)
{
	return we_sys->btl_sys->form_no[no];	
}

//--------------------------------------------------------------
/**
 * @brief	個性乱数
 *
 * @param	we_sys	
 * @param	no	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
int	WeSysPersonalRndGet(WE_SYS_PTR we_sys, int no)
{
	return we_sys->btl_sys->personal_rnd[no];	
}

//--------------------------------------------------------------
/**
 * @brief	ソフトスプライトのポインタ取得
 *
 * @param	we_sys	
 * @param	no			クライアント番号
 *
 * @retval	SOFT_SPRITE*	
 *
 */
//--------------------------------------------------------------
SOFT_SPRITE* WeSysSoftSpritePointerGet(WE_SYS_PTR we_sys, int no)
{
	if (we_sys->btl_sys->ss[no] == NULL){
		return NULL;
	}
	
	if(SoftSpriteExistCheck(we_sys->btl_sys->ss[no])){
		return we_sys->btl_sys->ss[no];
	}
	else{
		return NULL;
	}
}


//--------------------------------------------------------------
/**
 * @brief	PFD
 *
 * @param	we_sys	
 *
 * @retval	PALETTE_FADE_PTR	
 *
 */
//--------------------------------------------------------------
PALETTE_FADE_PTR WeSysPFDGet(WE_SYS_PTR we_sys)
{
	return we_sys->pfd;
}


//--------------------------------------------------------------
/**
 * @brief	パレットIDの取得
 *
 * @param	we_sys	
 * @param	client_no	
 *
 * @retval	int	
 *
 */
//--------------------------------------------------------------
int WeSysPalIDGet(WE_SYS_PTR we_sys, int client_no)
{
	return we_sys->btl_sys->excp[client_no]->pal_index;
}

int WeSysArcIDGet(WE_SYS_PTR we_sys, int client_no)
{
	return we_sys->btl_sys->excp[client_no]->arcID;
}

//--------------------------------------------------------------
/**
 * @brief	ポケモンのオフセット取得
 *
 * @param	we_sys	
 * @param	client_no	
 *
 * @retval	int	
 *
 */
//--------------------------------------------------------------
int WeSysPokeOfsGet(WE_SYS_PTR we_sys, int client_no)
{
	return we_sys->btl_sys->excp[client_no]->height;
}


//--------------------------------------------------------------
/**
 * @brief	2対2か調べる
 *
 * @param	we_sys	
 *
 * @retval	BOOL			TRUE = 2vs2
 *
 */
//--------------------------------------------------------------
BOOL IsWeSysBattleMode2vs2(WE_SYS_PTR we_sys)
{
	u32 bit;
	
	bit = (we_sys->btl_sys->fight_type & FIGHT_TYPE_2vs2);

	return (bit != 0) ? TRUE : FALSE;
}

BOOL BT_WazaKoukaCheck(WE_SYS_PTR we_sys, int client_no)
{
	int para;
	
	para = we_sys->btl_sys->waza_kouka[ client_no ] & WAZAKOUKA_KIE;
	
	return (para != 0) ? TRUE : FALSE;
}

//--------------------------------------------------------------
/**
 * @brief	カメラのモードを取得
 *
 * @param	we_sys	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
int	WeSysCameraTypeGet(int no, WE_SYS_PTR we_sys)
{
	return we_sys->camera_mode[no];
}

//--------------------------------------------------------------
/**
 * @brief	3D面のプライオリティ取得
 *
 * @param	we_sys	
 *
 * @retval	int	
 *
 */
//--------------------------------------------------------------
int BT_3DPriorityGet(WE_SYS_PTR we_sys)
{
	int pri;
	
	if (WES_ContestFlag_Get(we_sys) == TRUE){
		pri = ACTIN_3DBG_PRIORITY;
	}
	else {
		pri = BATTLE_3DBG_PRIORITY;
	}
	
	return pri;
}


//--------------------------------------------------------------
/**
 * @brief	BGのフレームを取得する
 *
 * @param	we_sys	
 * @param	type	
 *
 * @retval	int	
 *
 */
//--------------------------------------------------------------
int BT_BGL_FrameGet(WE_SYS_PTR we_sys, int type)
{
	int frame;
	int frm[][3] = {
		{
			BATTLE_FRAME_WINDOW,
			BATTLE_FRAME_EFFECT,
			BATTLE_FRAME_BACKGROUND
		},
		{
			ACTIN_FRAME_WINDOW,
			ACTIN_FRAME_EFFECT,
			ACTIN_FRAME_BACKGROUND
		},
	};
	
	if (WES_ContestFlag_Get(we_sys) == TRUE){
		frame = frm[ 1 ][ type ];
	}
	else {
		
		frame = frm[ 0 ][ type ];
	}

	return frame;
}


//--------------------------------------------------------------
/**
 * @brief	BGNO取得
 *
 * @param	we_sys	
 * @param	type	
 *
 * @retval	int	
 *
 */
//--------------------------------------------------------------
int BT_BGL_BGNoGet(WE_SYS_PTR we_sys, int type)
{
	int bgno;
	int no[][3] = {
		{
			BATTLE_BGNO_WINDOW,
			BATTLE_BGNO_EFFECT,
			BATTLE_BGNO_BACKGROUND
		},
		{
			ACTIN_BGNO_WINDOW,
			ACTIN_BGNO_EFFECT,
			ACTIN_BGNO_BACKGROUND
		},
	};
	
	if (WES_ContestFlag_Get(we_sys) == TRUE){
		bgno = no[ 1 ][ type ];
	}
	else {
		
		bgno = no[ 0 ][ type ];
	}
	
	return bgno;
}


//--------------------------------------------------------------
/**
 * @brief	BGプライオリティ取得
 *
 * @param	we_sys	
 * @param	type	
 *
 * @retval	int	
 *
 */
//--------------------------------------------------------------
int BT_BGPriorityGet(WE_SYS_PTR we_sys, int type)
{
	int pri;
	
	switch(type){
	case WES_BF_WINDOW:
		if (WES_ContestFlag_Get(we_sys) == TRUE){
			pri = ACTIN_BGPRI_WINDOW;
		}
		else {
			pri = BATTLE_BGPRI_WINDOW;
		}
		break;
		
	case WES_BF_EFFECT:
		if (WES_ContestFlag_Get(we_sys) == TRUE){
			pri = ACTIN_BGPRI_EFFECT;
		}
		else {
			pri = BATTLE_BGPRI_EFFECT;
		}
		break;
		
	case WES_BF_BACKGROUND:
		if (WES_ContestFlag_Get(we_sys) == TRUE){
			pri = ACTIN_BGPRI_BACKGROUND;
		}
		else {
			pri = BATTLE_BGPRI_BACKGROUND;
		}
		break;
		
	case WES_BF_3DFRAME:
		return BT_3DPriorityGet(we_sys);
	//	return BATTLE_3DBG_PRIORITY;
		break;
	}
	
	return pri;
}


//--------------------------------------------------------------
/**
 * @brief	カメラモードの設定
 *
 * @param	we_sys	
 * @param	mode	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WE_SYS_CameraModeSet(WE_SYS_PTR we_sys, int mode)
{
#ifdef PM_DEBUG
	g_nDebugCameraType = mode;
#endif
}

//--------------------------------------------------------------
/**
 * @brief	BG書き換え
 *
 * @param	wsp	
 * @param	frame	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WeSys_BattleBGDraw(WE_SYS_PTR wsp, int frame)
{
	GF_BGL_LoadCharacter(wsp->bgl, frame, wsp->btl_sys->bg_area, 0x10000, 0);
}

//--------------------------------------------------------------
/**
 * @brief	パレット
 *
 * @param	wsp	
 * @param	frame	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void WeSys_BattlePaletteTrans(WE_SYS_PTR wsp)
{
	PaletteWorkSet(wsp->pfd, wsp->btl_sys->pal_area, FADE_MAIN_BG, 0, 0x200);
}


//--------------------------------------------------------------
/**
 * @brief	フリップチェック
 *
 * @param	we_sys	
 * @param	flag	
 *
 * @retval	1BOOL	
 *
 */
//--------------------------------------------------------------
BOOL ContestFlipCheck(WE_SYS_PTR we_sys, int flag)
{
	int client_no;
	
	client_no = WEST_Tool_DropPokeClientNoGet(we_sys, flag);
	
	
	if (WES_ContestFlag_Get(we_sys) == TRUE
	&&	ContestPokeFlipCheck(WeSysMonsNoGet(we_sys, client_no)) == TRUE){
		
		return TRUE;
		
	}

	return FALSE;
}


// -----------------------------------------
//
//	■背景のデータテーブル
//
// -----------------------------------------
#if 0
static const int WE_HaikeiData_Table[][ 5 ] = {
	{
		EFFECT_BG01_NCGR_BIN,
		EFFECT_BG01_NCLR,
		EFFECT_BG01_NSCR_BIN,
		EFFECT_BG01_NSCR_BIN,		
		EFFECT_BG01_NSCR_BIN,		
	},
	{	
		EFFECT_057_NCGR_BIN,
		EFFECT_057_NCLR,
		EFFECT_057A_NSCR_BIN,
		EFFECT_057B_NSCR_BIN,	
		EFFECT_057B_NSCR_BIN,	
	},
	{
		EFFECT_059_NCGR_BIN,
		EFFECT_059_NCLR,
		EFFECT_059A_NSCR_BIN,
		EFFECT_059B_NSCR_BIN,
		EFFECT_059B_NSCR_BIN,
	},
	{
		BG_069_EARTH_NCGR_BIN,
		BG_069_EARTH_NCLR,
		BG_069_EARTH_NSCR_BIN,
		BG_069_EARTH_NSCR_BIN,
		BG_069_EARTH_NSCR_BIN,
	},
	{
		BG_094_PSYCHO1_NCGR_BIN,
		BG_094_PSYCHO_NCLR,
		BG_094_PSYCHO_NSCR_BIN,
		BG_094_PSYCHO_NSCR_BIN,
		BG_094_PSYCHO_NSCR_BIN,
	},
	{
		BG_090_JIWARE_NCGR_BIN,
		BG_090_JIWARE_NCLR,
		BG_090_JIWARE1_NSCR_BIN,
		BG_090_JIWARE2_NSCR_BIN,
		BG_090_JIWARE2_NSCR_BIN,
	},
	{
		BG_236_MOON_NCGR_BIN,
		BG_236_MOON_NCLR,
		BG_236_MOON_NSCR_BIN,
		BG_236_MOON_NSCR_BIN,
		BG_236_MOON_NSCR_BIN,
	},
	{
		BG_327_BLUESKY_NCGR_BIN,
		BG_327_BLUESKY_NCLR,
		BG_327_BLUESKY_NSCR_BIN,
		BG_327_BLUESKY_NSCR_BIN,
		BG_327_BLUESKY_NSCR_BIN,
	},
	{
		BG_322_COSMOS_NCGR_BIN,
		BG_322_COSMOS_NCLR,
		BG_322_COSMOS_NSCR_BIN,
		BG_322_COSMOS_NSCR_BIN,
		BG_322_COSMOS_NSCR_BIN,
	},
	{
		BG_433_WIREROOM_NCGR_BIN,
		BG_433_WIREROOM_NCLR,
		BG_433_WIREROOM_NSCR_BIN,
		BG_433_WIREROOM_NSCR_BIN,
		BG_433_WIREROOM_NSCR_BIN,
	},
	{	///< りゅうせいぐん
		BG_434_SHTINGSTAR_NCGR_BIN,
		BG_434_SHTINGSTAR_NCLR,
		BG_434_SHTINGSTAR1_NSCR_BIN,
		BG_434_SHTINGSTAR2_NSCR_BIN,
		BG_434_SHTINGSTAR2_NSCR_BIN,
	},
	{	///< ボルテッカー
		BG_192_LIGHTNING_NCGR_BIN,
		BG_192_LIGHTNING_NCLR,
		BG_192_LIGHTNING_NSCR_BIN,
		BG_192_LIGHTNING_NSCR_BIN,
		BG_192_LIGHTNING_NSCR_BIN,
		/*
		BG_344_VOLTAICER_NCGR_BIN,
		BG_344_VOLTAICER_NCLR,
		BG_344_VOLTAICER_NSCR_BIN,
		BG_344_VOLTAICER_NSCR_BIN,
		BG_344_VOLTAICER_NSCR_BIN,
		*/
	},
	{	///< インファイト
		BG_370_SPEED_NCGR_BIN,
		BG_370_SPEED_NCLR,
		BG_370_SPEED_NSCR_BIN,
		BG_370_SPEED_NSCR_BIN,
		BG_370_SPEED_NSCR_BIN,
	},
	{	///< ハードプラント
		BG_338_GREENLEAF_NCGR_BIN,
		BG_338_GREENLEAF_NCLR,
		BG_338_GREENLEAF_NSCR_BIN,
		BG_338_GREENLEAF_NSCR_BIN,
		BG_338_GREENLEAF_NSCR_BIN,
	},
	{	///< でんじほう
		BG_192_LIGHTNING_NCGR_BIN,
		BG_192_LIGHTNING_NCLR,
		BG_192_LIGHTNING_NSCR_BIN,
		BG_192_LIGHTNING_NSCR_BIN,
		BG_192_LIGHTNING_NSCR_BIN,
	},
	{	///< げきりん・せいなるほのう・ブラストバーン
		BG_200_FIRE_NCGR_BIN,
		BG_200_FIRE_NCLR,
		BG_200_FIRE_NSCR_BIN,
		BG_200_FIRE_NSCR_BIN,
		BG_200_FIRE_NSCR_BIN,
	},
	{	///< だいもんじ
		BG_126_DAIMONJI_NCGR_BIN,
		BG_126_DAIMONJI_NCLR,
		BG_126_DAIMONJI1_NSCR_BIN,
		BG_126_DAIMONJI2_NSCR_BIN,
		BG_126_DAIMONJI3_NSCR_BIN,
	},
	{	///< サイクロン
		BG_177_CYCLONE_NCGR_BIN,
		BG_177_CYCLONE_NCLR,
		BG_177_CYCLONE_NSCR_BIN,
		BG_177_CYCLONE3_NSCR_BIN,
		BG_177_CYCLONE3_NSCR_BIN,
	},
	{	///< じばく
		BG_120_SMALLBANG_NCGR_BIN,
		BG_120_SMALLBANG_NCLR,
		BG_120_SMALLBANG1_NSCR_BIN,
		BG_120_SMALLBANG2_NSCR_BIN,
		BG_120_SMALLBANG2_NSCR_BIN,
	},
	{	///< メガトンキック
		BG_025_FIREWORKS_NCGR_BIN,
		BG_025_FIREWORKS_NCLR,
		BG_025_FIREWORKS1_NSCR_BIN,
		BG_025_FIREWORKS2_NSCR_BIN,
		BG_025_FIREWORKS2_NSCR_BIN,
	},
	{	///< すてみタックル
		BG_038_BASHISHI_NCGR_BIN,
		BG_038_BASHISHI_NCLR,
		BG_038_BASHISHI1_NSCR_BIN,
		BG_038_BASHISHI2_NSCR_BIN,
		BG_038_BASHISHI3_NSCR_BIN,
	},
	{	///< はかいこうせん
		BG_063_DEPTHSPD_NCGR_BIN,
		BG_063_DEPTHSPD_NCLR,
		BG_063_DEPTHSPD_NSCR_BIN,
		BG_063_DEPTHSPD_NSCR_BIN,
		BG_063_DEPTHSPD_NSCR_BIN,
	},
	{	///< かみなり
		BG_087_DARKCLOUD_NCGR_BIN,
		BG_087_DARKCLOUD_NCLR,
		BG_087_DARKCLOUD_NSCR_BIN,
		BG_087_DARKCLOUD3_NSCR_BIN,
		BG_087_DARKCLOUD3_NSCR_BIN,
	},
	{	///< みずのはどう
		BG_352_SEABED_NCGR_BIN,
		BG_352_SEABED_NCLR,
		BG_352_SEABED_NSCR_BIN,
		BG_352_SEABED3_NSCR_BIN,
		BG_352_SEABED3_NSCR_BIN,
	},
	{	///< だくりゅう
		EFFECT_057_NCGR_BIN,
		EFFECT_330_NCLR,
		EFFECT_057A_NSCR_BIN,
		EFFECT_057B_NSCR_BIN,	
		EFFECT_057B_NSCR_BIN,	
	},
	///< 06.06.07
	{	///< ギガインパクト
		BG_025_FIREWORKS_NCGR_BIN,
		BG_416_FIREWORKS_Y_NCLR,
		BG_025_FIREWORKS1_NSCR_BIN,
		BG_025_FIREWORKS2_NSCR_BIN,
		BG_025_FIREWORKS2_NSCR_BIN,
	},
	{	///< パワーウィップ
		BG_038_BASHISHI_NCGR_BIN,
		BG_438_BASHISHI_G_NCLR,
		BG_038_BASHISHI1_NSCR_BIN,
		BG_038_BASHISHI2_NSCR_BIN,
		BG_038_BASHISHI3_NSCR_BIN,
	},
	{	///< ウッドハンマー
		BG_038_BASHISHI_NCGR_BIN,
		BG_452_BASHISHI_YG_NCLR,
		BG_038_BASHISHI1_NSCR_BIN,
		BG_038_BASHISHI2_NSCR_BIN,
		BG_038_BASHISHI3_NSCR_BIN,
	},
	{	///< ソーラービーム
		BG_063_DEPTHSPD_NCGR_BIN,
		BG_076_DEPTHSPD_Y_NCLR,
		BG_063_DEPTHSPD1_NSCR_BIN,
		BG_063_DEPTHSPD2_NSCR_BIN,
		BG_063_DEPTHSPD3_NSCR_BIN,
	},
	{	///< ゴッドバード
		BG_063_DEPTHSPD_NCGR_BIN,
		BG_143_DEPTHSPD_LB_NCLR,
		BG_063_DEPTHSPD1_NSCR_BIN,
		BG_063_DEPTHSPD2_NSCR_BIN,
		BG_063_DEPTHSPD3_NSCR_BIN,
	},
	{	///< ハイドロカノン
		BG_063_DEPTHSPD_NCGR_BIN,
		BG_308_DEPTHSPD_B_NCLR,
		BG_063_DEPTHSPD1_NSCR_BIN,
		BG_063_DEPTHSPD2_NSCR_BIN,
		BG_063_DEPTHSPD3_NSCR_BIN,
	},
	{	///< ブレイブバード
		BG_063_DEPTHSPD_NCGR_BIN,
		BG_143_DEPTHSPD_LB_NCLR,
		BG_063_DEPTHSPD1_NSCR_BIN,
		BG_063_DEPTHSPD2_NSCR_BIN,
		BG_063_DEPTHSPD3_NSCR_BIN,
	},
	{	///< きあいパンチ・オーバーヒート・フレアドライブ
		BG_264_SUPERNOVA_NCGR_BIN,
		BG_264_SUPERNOVA_NCLR,
		BG_264_SUPERNOVA1_NSCR_BIN,
		BG_264_SUPERNOVA2_NSCR_BIN,
		BG_264_SUPERNOVA3_NSCR_BIN,
	},
	{	///< あくむ
		BG_171_NIGHTMARE_NCGR_BIN,
		BG_171_NIGHTMARE_NCLR,
		BG_171_NIGHTMARE_NSCR_BIN,
		BG_171_NIGHTMARE_NSCR_BIN,
		BG_171_NIGHTMARE_NSCR_BIN,
	},
	{	///< ねんりき
		BG_093_WILLPOWER_NCGR_BIN,
		BG_093_WILLPOWER_NCLR,
		BG_093_WILLPOWER1_NSCR_BIN,
		BG_093_WILLPOWER2_NSCR_BIN,
		BG_093_WILLPOWER3_NSCR_BIN,
	},
	{	///< たきのぼり
		BG_127_WATERFALL_NCGR_BIN,
		BG_127_WATERFALL_NCLR,
		BG_127_WATERFALL_NSCR_BIN,
		BG_127_WATERFALL_NSCR_BIN,
		BG_127_WATERFALL_NSCR_BIN,
	},
	{	///< ハイドロポンプ・ミストボール
		BG_056_JUZU_NCGR_BIN,
		BG_056_JUZU_NCLR,
		BG_056_JUZU_NSCR_BIN,
		BG_056_JUZU_NSCR_BIN,
		BG_056_JUZU_NSCR_BIN,
	},
	{	///< ハイドロポンプ・ミストボール
		BG_056_JUZU_NCGR_BIN,
		BG_056_JUZU_NCLR,
		BG_056_JUZU_NSCR_BIN,
		BG_056_JUZU_NSCR_BIN,
		BG_056_JUZU_NSCR_BIN,
	},
	{	///< はどうだん
		BG_056_JUZU_NCGR_BIN,
		BG_396_JUZU_Y_NCLR,
		BG_056_JUZU_NSCR_BIN,
		BG_056_JUZU_NSCR_BIN,
		BG_056_JUZU_NSCR_BIN,
	},
	{	///< きあいだま
		BG_056_JUZU_NCGR_BIN,
		BG_411_JUZU_R_NCLR,
		BG_056_JUZU_NSCR_BIN,
		BG_056_JUZU_NSCR_BIN,
		BG_056_JUZU_NSCR_BIN,
	},
	{	///< ダストシュート
		BG_056_JUZU_NCGR_BIN,
		BG_441_JUZU_P_NCLR,
		BG_056_JUZU_NSCR_BIN,
		BG_056_JUZU_NSCR_BIN,
		BG_056_JUZU_NSCR_BIN,
	},
	{	///< リーフストーム
		BG_437_LEAFSTORM_NCGR_BIN,
		BG_437_LEAFSTORM_NCLR,
		BG_437_LEAFSTORM_NSCR_BIN,
		BG_437_LEAFSTORM_NSCR_BIN,
		BG_437_LEAFSTORM_NSCR_BIN,
	},
	{	///< がんせきほう
		BG_439_SPEED_NCGR_BIN,
		BG_439_SPEED_NCLR,
		BG_439_SPEED_NSCR_BIN,
		BG_439_SPEED_NSCR_BIN,
		BG_439_SPEED_NSCR_BIN,
	},
	{	///< もろはのずつき
		BG_457_SMALLBANG_NCGR_BIN,
		BG_457_SMALLBANG_NCLR,
		BG_457_SMALLBANG1_NSCR_BIN,
		BG_457_SMALLBANG2_NSCR_BIN,
		BG_457_SMALLBANG3_NSCR_BIN,
	},
	{	///< バーストエコー
		BG_460_ECHO_NCGR_BIN,
		BG_460_ECHO_NCLR,
		BG_460_ECHO1_NSCR_BIN,
		BG_460_ECHO2_NSCR_BIN,
		BG_460_ECHO3_NSCR_BIN,
	},
	{	///< みかづきのまい
		BG_461_CRESCENT_NCGR_BIN,
		BG_461_CRESCENT_NCLR,
		BG_461_CRESCENT_NSCR_BIN,
		BG_461_CRESCENT_NSCR_BIN,
		BG_461_CRESCENT_NSCR_BIN,
	},
	{	///< マグマストーム
		BG_463_MAGMA_NCGR_BIN,
		BG_463_MAGMA_NCLR,
		BG_463_MAGMA_NSCR_BIN,
		BG_463_MAGMA_NSCR_BIN,
		BG_463_MAGMA_NSCR_BIN,
	},
	{	///< ダークホール
		BG_464_DOWNER_NCGR_BIN,
		BG_464_DOWNER_NCLR,
		BG_464_DOWNER_NSCR_BIN,
		BG_464_DOWNER_NSCR_BIN,
		BG_464_DOWNER_NSCR_BIN,
	},
	{	///< シードフレア
		BG_465_EMISSION_NCGR_BIN,
		BG_465_EMISSION_NCLR,
		BG_465_EMISSION1_NSCR_BIN,
		BG_465_EMISSION2_NSCR_BIN,
		BG_465_EMISSION3_NSCR_BIN,
	},
	{	///< シャドーダイブ
		BG_467_SPEED_NCGR_BIN,
		BG_467_SPEED_NCLR,
		BG_467_SPEED_NSCR_BIN,
		BG_467_SPEED_NSCR_BIN,
		BG_467_SPEED_NSCR_BIN,
	},
};
#endif

static const int Haikei_BG_Table[][ 5 ] = {
	{	///< 025
		BG_025_FIREWORKS_NCGR_BIN,
		BG_025_FIREWORKS_NCLR,
		BG_025_FIREWORKS1_NSCR_BIN,
		BG_025_FIREWORKS2_NSCR_BIN,
		BG_025_FIREWORKS3_NSCR_BIN,	
	},
	{	///< 223
		BG_025_FIREWORKS_NCGR_BIN,
		BG_025_FIREWORKS_NCLR,
		BG_025_FIREWORKS1_NSCR_BIN,
		BG_025_FIREWORKS2_NSCR_BIN,
		BG_025_FIREWORKS3_NSCR_BIN,	
	},
	{	///< 224
		BG_025_FIREWORKS_NCGR_BIN,
		BG_025_FIREWORKS_NCLR,
		BG_025_FIREWORKS1_NSCR_BIN,
		BG_025_FIREWORKS2_NSCR_BIN,
		BG_025_FIREWORKS3_NSCR_BIN,	
	},
	{	///< 276
		BG_025_FIREWORKS_NCGR_BIN,
		BG_025_FIREWORKS_NCLR,
		BG_025_FIREWORKS1_NSCR_BIN,
		BG_025_FIREWORKS2_NSCR_BIN,
		BG_025_FIREWORKS3_NSCR_BIN,	
	},
	{	///< 354
		BG_025_FIREWORKS_NCGR_BIN,
		BG_025_FIREWORKS_NCLR,
		BG_025_FIREWORKS1_NSCR_BIN,
		BG_025_FIREWORKS2_NSCR_BIN,
		BG_025_FIREWORKS3_NSCR_BIN,	
	},
	{	///< 416
		BG_025_FIREWORKS_NCGR_BIN,
		BG_416_FIREWORKS_Y_NCLR,
		BG_025_FIREWORKS1_NSCR_BIN,
		BG_025_FIREWORKS2_NSCR_BIN,
		BG_025_FIREWORKS3_NSCR_BIN,	
	},
	{	///< 038
		BG_038_BASHISHI_NCGR_BIN,
		BG_038_BASHISHI_NCLR,
		BG_038_BASHISHI1_NSCR_BIN,
		BG_038_BASHISHI2_NSCR_BIN,
		BG_038_BASHISHI3_NSCR_BIN,	
	},
	{	///< 438
		BG_038_BASHISHI_NCGR_BIN,
		BG_438_BASHISHI_G_NCLR,
		BG_038_BASHISHI1_NSCR_BIN,
		BG_038_BASHISHI2_NSCR_BIN,
		BG_038_BASHISHI3_NSCR_BIN,	
	},
	{	///< 452
		BG_038_BASHISHI_NCGR_BIN,
		BG_452_BASHISHI_YG_NCLR,
		BG_038_BASHISHI1_NSCR_BIN,
		BG_038_BASHISHI2_NSCR_BIN,
		BG_038_BASHISHI3_NSCR_BIN,	
	},
	{	///< 056
		BG_056_JUZU_NCGR_BIN,
		BG_056_JUZU_NCLR,
		BG_056_JUZU_NSCR_BIN,
		BG_056_JUZU_NSCR_BIN,
		BG_056_JUZU_NSCR_BIN,	
	},
	{	///< 296
		BG_056_JUZU_NCGR_BIN,
		BG_056_JUZU_NCLR,
		BG_056_JUZU_NSCR_BIN,
		BG_056_JUZU_NSCR_BIN,
		BG_056_JUZU_NSCR_BIN,	
	},
	{	///< 396
		BG_056_JUZU_NCGR_BIN,
		BG_396_JUZU_Y_NCLR,
		BG_056_JUZU_NSCR_BIN,
		BG_056_JUZU_NSCR_BIN,
		BG_056_JUZU_NSCR_BIN,	
	},
	{	///< 411
		BG_056_JUZU_NCGR_BIN,
		BG_411_JUZU_R_NCLR,
		BG_056_JUZU_NSCR_BIN,
		BG_056_JUZU_NSCR_BIN,
		BG_056_JUZU_NSCR_BIN,	
	},
	{	///< 441
		BG_056_JUZU_NCGR_BIN,
		BG_441_JUZU_P_NCLR,
		BG_056_JUZU_NSCR_BIN,
		BG_056_JUZU_NSCR_BIN,
		BG_056_JUZU_NSCR_BIN,	
	},
	{	///< 063
		BG_063_DEPTHSPD_NCGR_BIN,
		BG_063_DEPTHSPD_NCLR,
		BG_063_DEPTHSPD_NSCR_BIN,
		BG_063_DEPTHSPD_NSCR_BIN,
		BG_063_DEPTHSPD_NSCR_BIN,	
	},
	{	///< 076
		BG_063_DEPTHSPD_NCGR_BIN,
		BG_076_DEPTHSPD_Y_NCLR,
		BG_063_DEPTHSPD_NSCR_BIN,
		BG_063_DEPTHSPD_NSCR_BIN,
		BG_063_DEPTHSPD_NSCR_BIN,	
	},
	{	///< 413
		BG_063_DEPTHSPD_NCGR_BIN,
		BG_143_DEPTHSPD_LB_NCLR,
		BG_063_DEPTHSPD_NSCR_BIN,
		BG_063_DEPTHSPD_NSCR_BIN,
		BG_063_DEPTHSPD_NSCR_BIN,	
	},
	{	///< 308
		BG_063_DEPTHSPD_NCGR_BIN,
		BG_308_DEPTHSPD_B_NCLR,
		BG_063_DEPTHSPD_NSCR_BIN,
		BG_063_DEPTHSPD_NSCR_BIN,
		BG_063_DEPTHSPD_NSCR_BIN,	
	},
	{	///< 143
		BG_063_DEPTHSPD_NCGR_BIN,
		BG_143_DEPTHSPD_LB_NCLR,
		BG_063_DEPTHSPD_NSCR_BIN,
		BG_063_DEPTHSPD_NSCR_BIN,
		BG_063_DEPTHSPD_NSCR_BIN,	
	},
	{	///< 087
		BG_087_DARKCLOUD_NCGR_BIN,
		BG_087_DARKCLOUD_NCLR,
		BG_087_DARKCLOUD_NSCR_BIN,
		BG_087_DARKCLOUD_NSCR_BIN,
		BG_087_DARKCLOUD3_NSCR_BIN,	
	},
	{	///< 093
		BG_093_WILLPOWER_NCGR_BIN,
		BG_093_WILLPOWER_NCLR,
		BG_093_WILLPOWER1_NSCR_BIN,
		BG_093_WILLPOWER2_NSCR_BIN,
		BG_093_WILLPOWER3_NSCR_BIN,	
	},
	{	///< 120
		BG_120_SMALLBANG_NCGR_BIN,
		BG_120_SMALLBANG_NCLR,
		BG_120_SMALLBANG1_NSCR_BIN,
		BG_120_SMALLBANG2_NSCR_BIN,
		BG_120_SMALLBANG3_NSCR_BIN,	
	},
	{	///< 126
		BG_126_DAIMONJI_NCGR_BIN,
		BG_126_DAIMONJI_NCLR,
		BG_126_DAIMONJI1_NSCR_BIN,
		BG_126_DAIMONJI2_NSCR_BIN,
		BG_126_DAIMONJI3_NSCR_BIN,	
	},
	{	///< 127
		BG_127_WATERFALL_NCGR_BIN,
		BG_127_WATERFALL_NCLR,
		BG_127_WATERFALL_NSCR_BIN,
		BG_127_WATERFALL_NSCR_BIN,
		BG_127_WATERFALL_NSCR_BIN,	
	},
	{	///< 171
		BG_171_NIGHTMARE_NCGR_BIN,
		BG_171_NIGHTMARE_NCLR,
		BG_171_NIGHTMARE_NSCR_BIN,
		BG_171_NIGHTMARE_NSCR_BIN,
		BG_171_NIGHTMARE_NSCR_BIN,	
	},
	{	///< 177
		BG_177_CYCLONE_NCGR_BIN,
		BG_177_CYCLONE_NCLR,
		BG_177_CYCLONE_NSCR_BIN,
		BG_177_CYCLONE_NSCR_BIN,
		BG_177_CYCLONE3_NSCR_BIN,	
	},
	{	///< 192
		BG_192_LIGHTNING_NCGR_BIN,
		BG_192_LIGHTNING_NCLR,
		BG_192_LIGHTNING_NSCR_BIN,
		BG_192_LIGHTNING_NSCR_BIN,
		BG_192_LIGHTNING_NSCR_BIN,	
	},
	{	///< 344
		BG_192_LIGHTNING_NCGR_BIN,
		BG_344_LIGHTNING_BL_NCLR,
		BG_192_LIGHTNING_NSCR_BIN,
		BG_192_LIGHTNING_NSCR_BIN,
		BG_192_LIGHTNING_NSCR_BIN,	
	},
	{	///< 200
		BG_200_FIRE_NCGR_BIN,
		BG_200_FIRE_NCLR,
		BG_200_FIRE_NSCR_BIN,
		BG_200_FIRE_NSCR_BIN,
		BG_200_FIRE_NSCR_BIN,	
	},
	{	///< 221
		BG_200_FIRE_NCGR_BIN,
		BG_221_FIRE_O_NCLR,
		BG_200_FIRE_NSCR_BIN,
		BG_200_FIRE_NSCR_BIN,
		BG_200_FIRE_NSCR_BIN,	
	},
	{	///< 307
		BG_200_FIRE_NCGR_BIN,
		BG_200_FIRE_NCLR,
		BG_200_FIRE_NSCR_BIN,
		BG_200_FIRE_NSCR_BIN,
		BG_200_FIRE_NSCR_BIN,	
	},
	{	///< 264
		BG_264_SUPERNOVA_NCGR_BIN,
		BG_264_SUPERNOVA_NCLR,
		BG_264_SUPERNOVA1_NSCR_BIN,
		BG_264_SUPERNOVA2_NSCR_BIN,
		BG_264_SUPERNOVA3_NSCR_BIN,	
	},
	{	///< 315
		BG_264_SUPERNOVA_NCGR_BIN,
		BG_264_SUPERNOVA_NCLR,
		BG_264_SUPERNOVA1_NSCR_BIN,
		BG_264_SUPERNOVA2_NSCR_BIN,
		BG_264_SUPERNOVA3_NSCR_BIN,	
	},
	{	///< 394
		BG_264_SUPERNOVA_NCGR_BIN,
		BG_264_SUPERNOVA_NCLR,
		BG_264_SUPERNOVA1_NSCR_BIN,
		BG_264_SUPERNOVA2_NSCR_BIN,
		BG_264_SUPERNOVA3_NSCR_BIN,	
	},
	{	///< 338
		BG_338_GREENLEAF_NCGR_BIN,
		BG_338_GREENLEAF_NCLR,
		BG_338_GREENLEAF_NSCR_BIN,
		BG_338_GREENLEAF_NSCR_BIN,
		BG_338_GREENLEAF_NSCR_BIN,	
	},
	{	///< 352
		BG_352_SEABED_NCGR_BIN,
		BG_352_SEABED_NCLR,
		BG_352_SEABED_NSCR_BIN,
		BG_352_SEABED_NSCR_BIN,
		BG_352_SEABED3_NSCR_BIN,	
	},
	{	///< 370
		BG_370_SPEED_NCGR_BIN,
		BG_370_SPEED_NCLR,
		BG_370_SPEED_NSCR_BIN,
		BG_370_SPEED_NSCR_BIN,
		BG_370_SPEED3_NSCR_BIN,	
	},
	{	///< 434
		BG_434_SHTINGSTAR_NCGR_BIN,
		BG_434_SHTINGSTAR_NCLR,
		BG_434_SHTINGSTAR1_NSCR_BIN,
		BG_434_SHTINGSTAR2_NSCR_BIN,
		BG_434_SHTINGSTAR2_NSCR_BIN,	
	},
	{	///< 437
		BG_437_LEAFSTORM_NCGR_BIN,
		BG_437_LEAFSTORM_NCLR,
		BG_437_LEAFSTORM_NSCR_BIN,
		BG_437_LEAFSTORM_NSCR_BIN,
		BG_437_LEAFSTORM_NSCR_BIN,	
	},
	{	///< 439
		BG_439_SPEED_NCGR_BIN,
		BG_439_SPEED_NCLR,
		BG_439_SPEED_NSCR_BIN,
		BG_439_SPEED_NSCR_BIN,
		BG_439_SPEED_NSCR_BIN,	
	},
	{	///< 457
		BG_457_SMALLBANG_NCGR_BIN,
		BG_457_SMALLBANG_NCLR,
		BG_457_SMALLBANG1_NSCR_BIN,
		BG_457_SMALLBANG2_NSCR_BIN,
		BG_457_SMALLBANG3_NSCR_BIN,	
	},
	{	///< 460
		BG_460_ECHO_NCGR_BIN,
		BG_460_ECHO_NCLR,
		BG_460_ECHO1_NSCR_BIN,
		BG_460_ECHO2_NSCR_BIN,
		BG_460_ECHO3_NSCR_BIN,	
	},
	{	///< 461
		BG_461_CRESCENT_NCGR_BIN,
		BG_461_CRESCENT_NCLR,
		BG_461_CRESCENT_NSCR_BIN,
		BG_461_CRESCENT_NSCR_BIN,
		BG_461_CRESCENT_NSCR_BIN,	
	},
	{	///< 463
		BG_463_MAGMA_NCGR_BIN,
		BG_463_MAGMA_NCLR,
		BG_463_MAGMA_NSCR_BIN,
		BG_463_MAGMA_NSCR_BIN,
		BG_463_MAGMA_NSCR_BIN,	
	},
	{	///< 464
		BG_464_DOWNER_NCGR_BIN,
		BG_464_DOWNER_NCLR,
		BG_464_DOWNER_NSCR_BIN,
		BG_464_DOWNER_NSCR_BIN,
		BG_464_DOWNER_NSCR_BIN,	
	},
	{	///< 465
		BG_465_EMISSION_NCGR_BIN,
		BG_465_EMISSION_NCLR,
		BG_465_EMISSION1_NSCR_BIN,
		BG_465_EMISSION2_NSCR_BIN,
		BG_465_EMISSION3_NSCR_BIN,	
	},
	{	///< 467
		BG_467_SPEED_NCGR_BIN,
		BG_467_SPEED_NCLR,
		BG_467_SPEED_NSCR_BIN,
		BG_467_SPEED_NSCR_BIN,
		BG_467_SPEED_NSCR_BIN,	
	},
	{	///< 097
		EFFECT_BG01_NCGR_BIN,
		EFFECT_BG01_NCLR,
		EFFECT_BG01_NSCR_BIN,
		EFFECT_BG01_NSCR_BIN,		
		EFFECT_BG01_NSCR_BIN,		
	},
	{	///< 057
		EFFECT_057_NCGR_BIN,
		EFFECT_057_NCLR,
		EFFECT_057A_NSCR_BIN,
		EFFECT_057B_NSCR_BIN,	
		EFFECT_057A_NSCR_BIN,	
	},
	{	///< 330
		EFFECT_057_NCGR_BIN,
		EFFECT_330_NCLR,
		EFFECT_057A_NSCR_BIN,
		EFFECT_057B_NSCR_BIN,	
		EFFECT_057A_NSCR_BIN,	
	},
	{	///< 059
		EFFECT_059_NCGR_BIN,
		EFFECT_059_NCLR,
		EFFECT_059B_NSCR_BIN,	/// r
		EFFECT_059A_NSCR_BIN,
		EFFECT_059A_NSCR_BIN,
	},
	{	///< 069
		BG_069_EARTH_NCGR_BIN,
		BG_069_EARTH_NCLR,
		BG_069_EARTH_NSCR_BIN,
		BG_069_EARTH_NSCR_BIN,
		BG_069_EARTH_NSCR_BIN,
	},
	{	///< 094
		BG_094_PSYCHO1_NCGR_BIN,
		BG_094_PSYCHO_NCLR,
		BG_094_PSYCHO_NSCR_BIN,
		BG_094_PSYCHO_NSCR_BIN,
		BG_094_PSYCHO_NSCR_BIN,
	},
	{	///< 090
		BG_090_JIWARE_NCGR_BIN,
		BG_090_JIWARE_NCLR,
		BG_090_JIWARE1_NSCR_BIN,
		BG_090_JIWARE1_NSCR_BIN,
		BG_090_JIWARE1_NSCR_BIN,
	},
	{	///< 236
		BG_236_MOON_NCGR_BIN,
		BG_236_MOON_NCLR,
		BG_236_MOON_NSCR_BIN,
		BG_236_MOON_NSCR_BIN,
		BG_236_MOON_NSCR_BIN,
	},
	{	///< 327
		BG_327_BLUESKY_NCGR_BIN,
		BG_327_BLUESKY_NCLR,
		BG_327_BLUESKY_NSCR_BIN,
		BG_327_BLUESKY_NSCR_BIN,
		BG_327_BLUESKY_NSCR_BIN,
	},
	{	///< 322
		BG_322_COSMOS_NCGR_BIN,
		BG_322_COSMOS_NCLR,
		BG_322_COSMOS_NSCR_BIN,
		BG_322_COSMOS_NSCR_BIN,
		BG_322_COSMOS_NSCR_BIN,
	},
	{	///< 433
		BG_433_WIREROOM_NCGR_BIN,
		BG_433_WIREROOM_NCLR,
		BG_433_WIREROOM_NSCR_BIN,
		BG_433_WIREROOM_NSCR_BIN,
		BG_433_WIREROOM_NSCR_BIN,
	},
};

//--------------------------------------------------------------
/**
 * @brief	背景データの取得
 *
 * @param	id	
 * @param	no	
 *
 * @retval	int	
 *
 */
//--------------------------------------------------------------
int WeSysHaikeiDataIDGet(int id, int no)
{
#if 1

	return Haikei_BG_Table[ id ][ no ];

#else

	return WE_HaikeiData_Table[ id ][ no ];

#endif
}


// =============================================================================
//
//
//	■
//
//
// =============================================================================
OAM_DROP_SYS* OAM_Drop_Init(BATTLE_WORK* bw, int heap, int client_no)
{
	int i;
	int pri_tbl[] = { 0, 0, 20, 10, 10, 20 };
	OAM_DROP_SYS* wk;
	
	wk = sys_AllocMemory(heap, sizeof(OAM_DROP_SYS));
	
	wk->heap	  = heap;
	wk->client_no = client_no;
	
	wk->sys.csp = BattleWorkCATS_SYS_PTRGet(bw);
	wk->sys.crp = BattleWorkCATS_RES_PTRGet(bw);
	wk->sys.pfd = BattleWorkPfdGet(bw);
	
	{		
		for(i = 0; i < CLIENT_MAX; i++){
			wk->cap[i]  = NULL;
			wk->excp[i] = BattleWorkExChrClientParamGet(bw, i);	///< キャラバッファ
		}
		BattleClientTypeBufMake(bw, &(wk->client_type[0]));		///< クライアントType
		BattleSoftSpriteBufMake(bw, &(wk->ss[0]));				///< ソフトスプライト
	}
	
	{
		int res_id[ 6 ];
			
		for (i = 0; i < CLIENT_MAX; i++){
			
			if (i != wk->client_no
			&&	wk->client_no != OAM_DROP_ALL){ continue; }
			
			///< 準備
			res_id[ 0 ] = OAM_DROP_ID + i + WES_OFS_ID(wk->client_no);
			res_id[ 1 ] = OAM_DROP_ID + i + WES_OFS_ID(wk->client_no);
			res_id[ 2 ] = OAM_DROP_ID + i + WES_OFS_ID(wk->client_no);
			res_id[ 3 ] = OAM_DROP_ID + i + WES_OFS_ID(wk->client_no);
			res_id[ 4 ] = 0;
			res_id[ 5 ] = 0;
			
		//	OS_Printf("pal id = %6d\n", res_id[ 1 ]);
				
			CATS_LoadResourceCharArc(wk->sys.csp, wk->sys.crp,
									 ARC_BATT_OBJ, PO_CHAR_ID, 0,
									 NNS_G2D_VRAM_TYPE_2DMAIN, res_id[0]);

			CATS_LoadResourcePlttWorkArc(wk->sys.pfd, FADE_MAIN_OBJ,
										 wk->sys.csp, wk->sys.crp,
										 ARC_BATT_OBJ, PO_PLTT_ID, 0,
										 NNS_G2D_VRAM_TYPE_2DMAIN, 1, res_id[1]);

			CATS_LoadResourceCellArc(wk->sys.csp, wk->sys.crp,
									 ARC_BATT_OBJ, PO_CELL_ID, 0, res_id[2]);

			CATS_LoadResourceCellAnmArc(wk->sys.csp, wk->sys.crp,
									 	ARC_BATT_OBJ, PO_CELLANM_ID, 0, res_id[3]);
		}		
	}
	
	
	{
		
		int i;
		int arcID;
		int palID;
		void* oam_temp;
		int res_id[ 6 ];
		CATS_ACT_PTR cap;
		
		for (i = 0; i < CLIENT_MAX; i++){
			
			if (i != wk->client_no
			&&	wk->client_no != OAM_DROP_ALL){ continue; }
			
			///< 準備
			wk->res_id[ i ] = OAM_DROP_ID + i + WES_OFS_ID(wk->client_no);
			res_id[ 0 ] = OAM_DROP_ID + i + WES_OFS_ID(wk->client_no);
			res_id[ 1 ] = OAM_DROP_ID + i + WES_OFS_ID(wk->client_no);
			res_id[ 2 ] = OAM_DROP_ID + i + WES_OFS_ID(wk->client_no);
			res_id[ 3 ] = OAM_DROP_ID + i + WES_OFS_ID(wk->client_no);
			res_id[ 4 ] = 0;
			res_id[ 5 ] = 0;
			
			arcID	 = wk->excp[ i ]->arcID;
			palID	 = wk->excp[ i ]->pal_index;
			oam_temp = wk->excp[ i ]->exchr_buffer;
			
			///< 登録
			{
				int n;
				TCATS_OBJECT_ADD_PARAM_S coap;
				SOFT_SPRITE*			 ssp;
				s16 px,py;
				
				ssp = wk->ss[ i ];
				
				if (ssp != NULL){
					
					px = SoftSpriteParaGet(ssp, SS_PARA_POS_X);
					py = SoftSpriteParaGet(ssp, SS_PARA_POS_Y);					
					py -= SoftSpriteParaGet(ssp, SS_PARA_SHADOW_HEIGHT);
					
				}
				else {
					continue;
				}
					
					
				coap.x		= px;
				coap.y		= py;
				coap.z		= 0;		
				coap.anm	= 0;
				coap.pri	= pri_tbl[ wk->client_type[i] ];
				coap.pal	= 0;
				coap.d_area = CATS_D_AREA_MAIN;
				coap.bg_pri = WAZAEFF_ACT_BGPRI;
				coap.vram_trans = 0;
				
					
				for (n = 0; n < 6; n++){
					coap.id[ n ] = res_id[ n ];
				}
				cap = CATS_ObjectAdd_S(wk->sys.csp, wk->sys.crp, &coap);
				CATS_ObjectUpdateCap(cap);
				wk->cap[i] = cap;

				if (ssp == NULL){
					CATS_ObjectEnableCap(cap, CATS_ENABLE_FALSE);
				}
				else if (SoftSpriteExistCheck(ssp) == FALSE){
					CATS_ObjectEnableCap(cap, CATS_ENABLE_FALSE);
				}
				else {
					int vf = SoftSpriteParaGet(ssp, SS_PARA_VANISH);
					
					if (vf == 1){
						CATS_ObjectEnableCap(cap, CATS_ENABLE_FALSE);
					}
				}
				
				if (ssp != NULL)
				{
					///< ダミーキャラに正式キャラを転送しなおし
					NNSG2dImageProxy * image;
					
					image = CLACT_ImageProxyGet(cap->act);
							
					AddVramTransferManager(
						NNS_GFD_DST_2D_OBJ_CHAR_MAIN,
						image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN],
						oam_temp,
						POKE_TEX_SIZE);
				}
				
				if (ssp != NULL)
				{
					///< ダミーパレットに正式なパレットを転送しなおし
					NNSG2dImagePaletteProxy* palette;
					int pal_no;
					
					palette = CLACT_PaletteProxyGet(cap->act);
					
					pal_no = GetPlttProxyOffset(palette, NNS_G2D_VRAM_TYPE_2DMAIN);
					
					PaletteWorkSet_Arc(wk->sys.pfd, arcID, palID, wk->heap, FADE_MAIN_OBJ, 0x20, pal_no*16);
				}
			}
		}
	}
	
	return wk;
}


OAM_DROP_SYS* OAM_DropAll_Init(BATTLE_WORK* bw, int heap)
{
	OAM_DROP_SYS* wk;
	
	wk	= OAM_Drop_Init(bw, heap, OAM_DROP_ALL);
	
	return wk;
}


void OAM_DropAll_End(OAM_DROP_SYS* ods)
{
	int i;
	
	for (i = 0; i < 4; i++){
		
		if (ods->cap[i] == NULL){ continue; }
		
		CATS_FreeResourceChar(ods->sys.crp, ods->res_id[i]);
		CATS_FreeResourcePltt(ods->sys.crp, ods->res_id[i]);
		CATS_ActorPointerDelete_S(ods->cap[i]);
	}
	
	sys_FreeMemoryEz(ods);
}

void OAM_Drop_End(OAM_DROP_SYS* ods, int client_no)
{
	int i;
	
	for (i = 0; i < 4; i++){
		
		if (i != client_no){ continue; }
		
		if (ods->cap[i] == NULL){ continue; }
		
		CATS_FreeResourceChar(ods->sys.crp, ods->res_id[i]);
		CATS_FreeResourcePltt(ods->sys.crp, ods->res_id[i]);
		CATS_ActorPointerDelete_S(ods->cap[i]);
	}
	
	sys_FreeMemoryEz(ods);
}

//--------------------------------------------------------------
/**
 * @brief	odsが管理するクライアントナンバーのアクターを取得
 *
 * @param	ods	
 * @param	client_no	
 *
 * @retval	CATS_ACT_PTR	
 *
 */
//--------------------------------------------------------------
CATS_ACT_PTR OAM_Drop_CapGet(OAM_DROP_SYS* ods, int client_no)
{
	GF_ASSERT(ods != NULL);
	
	return ods->cap[ client_no ];
}

int OAM_Drop_ClientTypeGet(OAM_DROP_SYS* ods)
{
	GF_ASSERT(ods != NULL);
	
	return ods->client_type[ ods->client_no ];	
}

