//==============================================================================
/**
 * @file	ball_effect.h
 * @brief	ボールエフェクト
 * @author	goto
 * @date	2005.10.26(水)
 *
 * ここに色々な解説等を書いてもよい
 *
 */
//==============================================================================

#ifndef __BALL_EFFECT_H__
#define __BALL_EFFECT_H__

#include "include/system/particle.h"
#include "wazaeffect/wp_tbl.h"
#include "wazaeffect/wazatool.h"

#include "battle/battle_common.h"
#include "battle/fight_tool.h"

#include "include/itemtool/itemsym.h"

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

#define BALL_EFF_EX_DP		(0xFF)						// DP用拡張ID　※使わないでください

#define BALL_EFF_PARK_BALL	(BALL_EFF_EX_DP + 17)		// パークボール
#define BALL_EFF_STONE		(BALL_EFF_EX_DP + 18)		// 泥
#define BALL_EFF_FOOD		(BALL_EFF_EX_DP + 19)		// エサ
#define BALL_EFF_BACK		(BALL_EFF_EX_DP + 20)		// 戻す ※直接指定禁止

#define BALL_EFF_DP_END		(BALL_EFF_BACK)				// DPの終わり

///< 分割読み込み
#define LOAD_SEQ_SEP
#define LOAD_SEQ_END		(0xFF)


// -----------------------------------------
//
//	ボールエフェクト用の定数定義
//
// -----------------------------------------
#include "wazaeffect/effectdata/waza_particle_def.h"
//#include "wazaeffect/effectdata/p_ball_effect.h"
//#include "wazaeffect\effectdata\we_list.h"
#include "wazaeffect\effectdata\ball_effect_setup.h"
#define BALL_EFFECT_USE_SPA		(SPA_P_BALL_EFFECT)			///< 利用するSPA
#define BALL_EFFECT_BIT_MAX		(20)//P_BALL_EFFECT_SPAMAX)		///< SPAの登録個数


// -----------------------------------------
//
//	ボールエフェクト管理システム
//
// -----------------------------------------
typedef struct _TBALL_EFFECT_SYS * BES_PTR;


// -----------------------------------------
//
//	カスタマイズパラメーター
//
// -----------------------------------------
typedef struct {
	
	int	client_type;		///< 各ボール初期化パラメータに渡す必要がある
	
	int ball_id;

	POKEMON_PARAM*	pp;		///< ポケモンパラメータ

} TBALL_CUSTOM_PARAM;

/*

モンスターボール
スーパーボール
ハイパーボール
マスターボール
サファリボール
ネットボール
ダイブボール
ネストボール
リピートボール
タイマーボール
ゴージャスボール
プレミアボール
ダークボール
ヒールボール
クイックボール
プレシアボール

*/

// -----------------------------------------
//
//	定数定義
//
// -----------------------------------------
#define BECB_INIT_DEF_POS	(1)			///< 初期座標指定
#define	BECB_INIT_VELO		(1)			///< 初速度変更
#define	BECB_GENE_RAITO		(1)			///< レート変更
#define	BECB_INTERVAL		(0)			///< 放出間隔変更
#define	BECB_INIT_POS		(0)			///< 初期座標変更

enum EEFF_TYPE {
	BE_EFF_MONSTAR_BALL = 0,			///< 通常のモンスターボール
	BE_EFF_CUSTOM_BALL,					///< カスタムボール
};

enum EBE_BIT {							///< エフェクトビット操作モード
	BEBIT_ON	= 0,					///< Set
	BEBIT_OFF,							///< Reset
	BEBIT_CHECK,						///< Check
};


// -----------------------------------------
//
//	メモリ確保初期化
//
// -----------------------------------------
extern BES_PTR BallEffect_InitEz(int heap_area);


// -----------------------------------------
//
//	メモリ確保＋パラメーター設定
//
// -----------------------------------------
extern BES_PTR BallEffect_Init(int heap_area, const TBALL_CUSTOM_PARAM* bcp);


// -----------------------------------------
//
//	リソース読み込み
//
// -----------------------------------------
extern void BallEffect_ResourceLoad(BES_PTR bes);
extern BOOL BallEffect_IsLoadEnd(BES_PTR bes);


// -----------------------------------------
//
//	パラメーター設定
//
// -----------------------------------------
extern void BallEffect_ParamSet(BES_PTR bes, const TBALL_CUSTOM_PARAM* bcp);


// -----------------------------------------
//
//	エフェクト実行
//
// -----------------------------------------
extern void BallEffect_Executed(BES_PTR bes, pEmitFunc callback);
extern void BallEffect_ExecutedEz(BES_PTR bes);


// -----------------------------------------
//
//	エフェクト終了チェック
//
// -----------------------------------------
extern BOOL BallEffect_EndCheck(BES_PTR bes);


// -----------------------------------------
//
//	メモリの解放
//
// -----------------------------------------
extern void BallEffect_FreeMemory(BES_PTR bes);



#define ALL_DATA_SET	(0xFF)
#define ONE_DATA_SET	(0xEE)

typedef struct {
	
	s16 x;
	s16 y;
	
	int	ball_id;
	int heap_id;
	
	int set_id;			///< この値が、0xFFの場合は、すべて登録 0xFF いがいならそれのみ登録
	int close_only;		///< このフラグがあると、ボール番号無視して閉じる用のエフェクトが出る
	
} TSP_BALL_PARAM;


typedef struct _TSP_BALL_SYS * SPB_PTR;

extern SPB_PTR	SPB_Init(TSP_BALL_PARAM* param);
extern void		SPB_Load(SPB_PTR spb);
extern BOOL		SPB_Main(SPB_PTR spb);
extern void		SPB_End(SPB_PTR spb);






// =============================================================================
//
//
//	■ボール投げエフェクト
//
//
// =============================================================================
typedef struct _TBALL_MOVE_SYS * BMS_PTR;

typedef struct {

	int type;
	int heap_id;
	int mode;
	int id;						///< クライアントNO
	int ball_id;				///< ボールID
	int	bg_pri;
	int surface;				///< サーフェイスどうするか
	
	CATS_SYS_PTR		csp;
	PALETTE_FADE_PTR	pfd;
	
	BATTLE_WORK*		bw;
	
} TBALL_MOVE_DATA;

enum EBM_TYPE {
	
	EBMT_STAY_AA = 0,	///< 基本位置
	EBMT_STAY_BB,
	EBMT_STAY_A,
	EBMT_STAY_B,
	EBMT_STAY_C,
	EBMT_STAY_D,

	EBMT_THROW_C,		///< 1匹の時
	EBMT_THROW_R,		///< 右に投げ落ちる
	EBMT_THROW_L,		///< 左に投げ落ちる
	
	EBMT_THROW_E0,		///< 敵に投げる
	EBMT_THROW_E1,		///< 敵2対の右側
	EBMT_THROW_E2,		///< 敵2対の左側
	
	EBMT_THROW_E0_STONE,///< 敵に投げる　石
	EBMT_THROW_E0_FOOD,	///< 敵に投げる　エサ
	
	EBMT_VISUAL,		///< コンテストビジュアル部門
	
	EBMT_CAPTURE_BB,	///< 捕獲デモ
	EBMT_CAPTURE_B,		///< 捕獲デモ
	EBMT_CAPTURE_D,		///< 捕獲デモ
	
	EBMT_MAX,
};

enum EBM_MODE {
	
	EBMM_THROW = 0,		///< 投げる
	EBMM_FAILURE,		///< 失敗専用
	
	EBMM_SHAKE,			///< 揺らす
	
	EBMM_CAPTURE,		///< 捕獲用

	EBMM_FREE,			///< 自由に
	
	EBMM_CLOSE,			///< 戻る
	
};

enum EBM_STATE {
	
	EBMS_START	= 0,	///< 開始
	
	EBMS_THROW,			///< 投げている
	EBMS_THROW_END,		///< ポケモンの頭上に到着
	
	EBMS_OPEN,			///< 開いている
	EBMS_OPEN_END,		///< 開き終わった
	
	EBMS_SHED,			///< トレーナー戦だった弾き
	EBMS_SHED_END,		///< トレーナー戦だった終わった
	
	EBMS_CLOSE,			///< 閉じている
	EBMS_CLOSE_END,		///< 閉じ終わった
	
	EBMS_FLASH,			///< 光っている
	EBMS_FLASH_END,		///< 光り終わった
	
	EBMS_FALL,			///< 落下している
	EBMS_FALL_END,		///< 落下し終わった
	
	EBMS_BOUNCE,		///< 跳ねている
	EBMS_BOUNCE_END,	///< 跳ね終わった
	
	EBMS_STOP,			///< 停止
	EBMS_STOP_END,		///< 停止が終わった
	
	EBMS_ROLL,			///< 転がる 5dot
	EBMS_ROLL_END,		///< 転がり終わった
	
	EBMS_FAILURE,		///< 失敗
	EBMS_FAILURE_END,	///< 失敗終わった
	
	EBMS_SUCCESS_1,		///< 成功 - 1 暗くなる
	EBMS_SUCCESS_1_END,	///< 成功終わった
	
	EBMS_SUCCESS_2,		///< 成功 - 2 元に戻る
	EBMS_SUCCESS_2_END,	///< 成功終わった - 2
	
	EBMS_SUCCESS_3,		///< 成功 - 3 消える
	EBMS_SUCCESS_3_END,	///< 成功終わった - 3
	
	EBMS_END,			///< 終了
};

enum EBM_DEMO {
	
	EBM_DEMO_SCENE_THROW = 0,		///< ボール投げ～まで
	EBM_DEMO_SCENE_OPEN,			///< 開く
	EBM_DEMO_SCENE_SHED,			///< 弾かれる
	EBM_DEMO_SCENE_FALL,			///< 閉じる～バウンド
	EBM_DEMO_SCENE_ROLL,			///< 停止～ころころ
	EBM_DEMO_SCENE_END_FAILURE,		///< 失敗～終了
	EBM_DEMO_SCENE_END_SUCCESS,		///< 捕獲～暗くなるまで
	EBM_DEMO_SCENE_END_SUCCESS_2,	///< 暗くなっている～終了

};

enum EBM_ANIME {
	
	EBM_ANM_THROW = 0,
	EBM_ANM_CLOSE = 0,
	EBM_ANM_OPEN,
};

#define BM_STOP_TIME		(5)//(5)		///< 10
#define BM_OPEN_WAIT		(15)//(10)	///< 15
#define BM_OPEN_WAIT_2		(15)	///< 20

#define BM_BG_PRI_BATTLE	(1)
#define BM_BG_PRI_CUSTOM	(0)
#define BM_SUITABLE_ID		(0xFF)
#define BM_BOUNCE_WAIT		(20)
#define BM_STOP_WAIT		(14)
#define BM_ROLL_DOT_RAD(n)	( (n) * 2)
#define BM_ROLL_RAD(n)		( FX_GET_ROTA_NUM(BM_ROLL_DOT_RAD(n)) )
#define BM_ROLL_WAIT		(11)
#define BM_ROLL_NUM			(3)

#define BM_FALL_WAIT		(1)

#define BM_FADE_FLASH		(0x037F)
#define BM_FADE_FLASH_PARA	(12)
#define BM_FADE_FLASH_SPD	(-1)
#define BM_FADE_DARK		(0x0000)
#define BM_FADE_DARK_PARA	(10)			///< 暗くなり度
#define BM_FADE_DARK_SPD	(-5)			///< 暗くなるスピード

#if 0

#define BM_STOP_TIME		(10)//(5)		///< 10
#define BM_OPEN_WAIT		(15)//(10)	///< 15
#define BM_OPEN_WAIT_2		(15)	///< 20

#define BM_BG_PRI_BATTLE	(1)
#define BM_BG_PRI_CUSTOM	(0)
#define BM_SUITABLE_ID		(0xFF)
#define BM_BOUNCE_WAIT		(30)
#define BM_STOP_WAIT		(21)
#define BM_ROLL_DOT_RAD(n)	( (n) * 2)
#define BM_ROLL_RAD(n)		( FX_GET_ROTA_NUM(BM_ROLL_DOT_RAD(n)) )
#define BM_ROLL_WAIT		(9)
#define BM_ROLL_NUM			(3)

#define BM_FALL_WAIT		(4)

#define BM_FADE_FLASH		(0x037F)
#define BM_FADE_FLASH_PARA	(12)
#define BM_FADE_FLASH_SPD	(-4)
#define BM_FADE_DARK		(0x0000)
#define BM_FADE_DARK_PARA	(10)			///< 暗くなり度
#define BM_FADE_DARK_SPD	(-2)			///< 暗くなるスピード

#endif

extern BMS_PTR	BM_Init(TBALL_MOVE_DATA* bmd);
extern BOOL		BM_EndCheck(BMS_PTR bms);
extern BOOL 	BM_IsOpen(BMS_PTR bms);

extern void		BM_Delete(BMS_PTR bms);
extern void		BM_ModeChange(BMS_PTR bms, int mode);
extern int		BM_ModeGet(BMS_PTR bms);


extern int		BM_CaptureStateGet(BMS_PTR bms);
extern void		BM_CaptureStateSet(BMS_PTR bms, int state);
extern BOOL		BM_IsCaptureStateEnd(BMS_PTR bms, int state);

extern void		BM_SceneSet(BMS_PTR bms, int scene);
extern BOOL		BM_SceneStateGet(BMS_PTR bms, int scene);

///< 外部操作
extern void		BM_BallEnable(BMS_PTR bms, int flag);			///< ボールの表示非表示
/*
	CATS_ENABLE_TRUE	= 表示
	CATS_ENABLE_FALSE	= 非表示
*/
extern void		BM_BallPosGet(BMS_PTR bms, s16* x, s16* y);		///< ボールの位置取得
extern void		BM_BallPosSet(BMS_PTR bms, s16 x, s16 y);		///< ボールの位置設定
extern void		BM_BallRadGet(BMS_PTR bms, u16* rot);			///< ボールの角度取得
extern void		BM_BallRadSet(BMS_PTR bms, u16 rot);			///< ボールの角度取得
extern void		BM_BallAnimeFlagSet(BMS_PTR bms, BOOL flag);	///< ボールのアニメフラグ
extern void		BM_BallSoftPriSet(BMS_PTR bms, int pri);		///< ボールの優先度
extern void		BM_BallBgPriSet(BMS_PTR bms, int pri);			///< ボールの優先度
extern void		BM_BallFreeEnd(BMS_PTR bms);					///< 自由操作を終わらせる
extern void		BM_BallWaitSet(BMS_PTR bms, int wait);			///< 外部指定ウェイト


#endif
