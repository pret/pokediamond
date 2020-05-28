//==============================================================================
/**
 * @file	gauge.h
 * @brief	戦闘画面：HPゲージのヘッダ
 * @author	matsuda
 * @date	2005.09.27(火)
 */
//==============================================================================
#ifndef __GAUGE_H__
#define __GAUGE_H__

#include "system/buflen.h"
#include "client_tool_def.h"



//==============================================================================
//	定数定義
//==============================================================================
///ゲージの標準BGプライオリティ
#define GAUGE_DEFAULT_BGPRI			(0)

//--------------------------------------------------------------
//	ゲージタイプ
//		クライアントタイプが数値が変更されてもテーブルの並びに影響が出ないように、
//		ゲージタイプを別に定義。クライアントタイプから適切なゲージタイプを取り出すようにする
//		テーブル等はゲージタイプの並びに従っておけば安全にデータ取得が行える
//--------------------------------------------------------------
enum{
	GAUGE_TYPE_AA,
	GAUGE_TYPE_BB,
	GAUGE_TYPE_A,
	GAUGE_TYPE_B,
	GAUGE_TYPE_C,
	GAUGE_TYPE_D,
	GAUGE_TYPE_SAFARI,
	GAUGE_TYPE_PARK,
};

///ゲージスクロール方向
enum{
	GAUGE_SCROLL_IN,		///<スクロールIN
	GAUGE_SCROLL_OUT,		///<スクロールOUT
};


//--------------------------------------------------------------
//	ゲージパーツ描画
//--------------------------------------------------------------
///ゲージパーツ描画フラグ：HPバー
#define GAUGE_DRAW_HPBAR		(1 << 0)
///ゲージパーツ描画フラグ：現在HP(数値)
#define GAUGE_DRAW_HPNUM		(1 << 1)
///ゲージパーツ描画フラグ：最大HP(数値)
#define GAUGE_DRAW_HPNUMMAX		(1 << 2)
///ゲージパーツ描画フラグ：レベル
#define GAUGE_DRAW_LEVEL		(1 << 3)
///ゲージパーツ描画フラグ：名前
#define GAUGE_DRAW_NAME			(1 << 4)
///ゲージパーツ描画フラグ：経験値
#define GAUGE_DRAW_EXP			(1 << 5)
///ゲージパーツ描画フラグ：性別
#define GAUGE_DRAW_SEX			(1 << 6)
///ゲージパーツ描画フラグ：レベル文字
#define GAUGE_DRAW_LEVEL_FONT	(1 << 7)
///ゲージパーツ描画フラグ：状態異常
#define GAUGE_DRAW_STATUS		(1 << 8)
///ゲージパーツ描画フラグ：ゲット済みマーク
#define GAUGE_DRAW_GETBALL		(1 << 9)
///ゲージパーツ描画フラグ：「サファリボール」
#define GAUGE_DRAW_SAFARIBALL	(1 << 10)
///ゲージパーツ描画フラグ：「のこり　○○こ」
#define GAUGE_DRAW_SAFARI_NOKORI	(1 << 11)
///ゲージパーツ描画フラグ：「パークボール」
#define GAUGE_DRAW_PARKBALL	(1 << 12)
///ゲージパーツ描画フラグ：「のこり　○○こ」
#define GAUGE_DRAW_PARK_NOKORI	(1 << 13)

///ゲージパーツ描画フラグ：全て
#define GAUGE_DRAW_ALL			(0xffffffff)
///ゲージパーツ描画フラグ：全て(サファリ用の全ビット)
#define GAUGE_DRAW_ALL_SAFARI	(GAUGE_DRAW_SAFARIBALL | GAUGE_DRAW_SAFARI_NOKORI)
///ゲージパーツ描画フラグ：全て(ポケパーク用の全ビット)
#define GAUGE_DRAW_ALL_PARK	(GAUGE_DRAW_PARKBALL | GAUGE_DRAW_PARK_NOKORI)


//--------------------------------------------------------------
//	ゲージのパーツグラフィックの配置番号
//--------------------------------------------------------------
enum{
	GP_HPBAR_GREEN = 2,			///<HPバー緑
	GP_HPBAR_YELLOW = 0x0b,		///<HPバー黄色
	GP_HPBAR_RED = 0x14,		///<HPバー赤
	
	GP_EXP = 0x1d,				///<経験値
	
	GP_NON_GETBALL = 0x38,		///<ゲット済みマークなし
	GP_GETBALL = 0x3b,			///<ゲット済みマーク
	
	GP_SEX_FEMALE = 0x3c,		///<性別：雌
	GP_SEX_MALE = 0x3e,			///<性別：雄
	GP_SEX_UNK = 0x40,			///<性別：なし
	
	GP_MAHI = 0x29,				///<麻痺
	GP_KOORI = 0x2c,			///<氷
	GP_NEMURI = 0x2f,			///<眠り
	GP_DOKU = 0x32,				///<毒
	GP_YAKEDO = 0x35,			///<やけど
	GP_NON_STATUS = 0x38,		///<状態異常なし
	
	GP_HPBAR_HEAD = 0x42,		///<HPバーのタイトル
	GP_HPBAR_CAP = 0x44,		///<HPバーの蓋
	GP_HPBAR_HEAD_CLEAR = GP_NON_STATUS,	///<HPバーのタイトルなし
	GP_HPBAR_CAP_CLEAR = GP_NON_STATUS,		///<HPバーの蓋なし
	GP_SLASH = 0x45,			///<HP数値のスラッシュ
};


//--------------------------------------------------------------
//	旧：ゲージ計算ルーチンで使用
//--------------------------------------------------------------
///ポケモン名の文字間隔X
#define GAUGE_FONT_MARGIN	(0)

///1キャラの中に入っているゲージのドット数
#define GAUGE_DOTTO			(8)

///HPバーのキャラ数
#define BAR_HP_CHARMAX		(6)
///EXPバーのキャラ数
#define BAR_EXP_CHARMAX		(11)
///ゲージバーで一番大きいゲージのキャラ数
#define BAR_ALL_MAX			(BAR_EXP_CHARMAX)

///HPゲージのドット数
#define GAUGE_HP_DOTTOMAX	(GAUGE_DOTTO * BAR_HP_CHARMAX)

///作業用ワークの初期値として使用
#define HP_WORK_INIT_VALUE	(-2147483648)



//==============================================================================
//	構造体定義
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   HPゲージ：サブパラメータ
 *
 * クライアントから命令を受ける毎に、クリア、更新されるパラメータ群
 */
//--------------------------------------------------------------
typedef struct{
	u8			seq_no;
}GAUGE_SUB_PARAM;

//--------------------------------------------------------------
/**
 * @brief   HPゲージ構造体
 */
//--------------------------------------------------------------
typedef struct{
	GAUGE_SUB_PARAM param;	///<サブパラメータ
	CATS_ACT_PTR cap;		///<ゲージ本体のヘッダー付きアクターポインタ
	CATS_ACT_PTR arrow_cap;	///<矢印のヘッダー付きアクターポインタ
	BATTLE_WORK	*bw;		///<戦闘システムワーク構造体
	TCB_PTR tcb;			///<動作中のTCB
	GF_BGL_BMPWIN name_bmpwin;	///<名前BITMAP形成用

	u8			client_no;
	u8 			type;		///<ゲージタイプ(GAUGE_TYPE_???)
	u8			sel_mons_no;	///<何番目のポケモンが選択されているか

	u8			safari_nokori;		///<サファリ：残りボール数
	
	s32			hp;			///<現在HP(be_hp計算前。　※正確には hp+be_hp が最新の現在HPと言える)
	s32			hpmax;		///<最大HP
	s32			damage;		///<受けたダメージ(-でダメージ、+なら回復)
	s32			hp_work;	///<ゲージ増減作業用ワーク
	
	s32			exp;		///<現在のEXP(add_exp計算前) ※現在のレベルの開始EXPを引いた値
	s32			max_exp;	///<次のレベルアップまでのEXP ※現在のレベルの開始EXPを引いた値
	s32			add_exp;	///<加算するEXP
	s32			exp_work;	///<ゲージ増減作業用ワーク
	
	u8			level;		///<レベル
	u8			sex;		///<性別
	u8			status;		///<状態異常
	u8			getball;	///<ゲット済みマーク
	
	u8			command_code;
	u8			in_wait;			///<INエフェクトをする前のウェイト
	u8			se_wait;			///<SEウェイト
	
	u8			in_out_dir:1;		///<スクロール方向(GAUGE_SCROLL_IN or GAUGE_SCROLL_OUT)
	u8			eff_wait_in_out:1;	///<エフェクト待ちフラグ(TRUE=終了)：スクロールIN or OUT
	u8			eff_wait_lvup:1;	///<エフェクト待ちフラグ(TRUE=終了)：レベルアップ
	u8			num_mode:1;			///<TRUE:HP数値表示モード(2vs2ゲージで自機側のみ)
	
	TCB_PTR		sin_tcb;		///<Sinカーブ：エフェクト実行タスク
	u16			sin_sec;		///<Sinカーブ：秒
	
#ifdef PM_DEBUG
	u8			debug_hp_put;	///<TRUE:敵のHPを数値でも表示
#endif
}GAUGE_WORK;



//==============================================================================
//	外部関数宣言
//==============================================================================
extern void Gauge_ResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, PALETTE_FADE_PTR pfd, 
	int gauge_type);
extern CATS_ACT_PTR Gauge_ActorSet(CATS_SYS_PTR csp, CATS_RES_PTR crp, int gauge_type);
extern void Gauge_InitCalcHP(GAUGE_WORK *gauge, int damage);
extern s32 Gauge_CalcHP(GAUGE_WORK *gauge);
extern void Gauge_InitCalcEXP(GAUGE_WORK *gauge, int add_exp);
extern s32 Gauge_CalcEXP(GAUGE_WORK *gauge);
extern void Gauge_ActorDel(GAUGE_WORK *gauge);
extern void Gauge_ResourceFree(GAUGE_WORK *gauge);
extern void Gauge_ActorResourceSet(GAUGE_WORK *gauge);
extern void Gauge_ActorResourceDel(GAUGE_WORK *gauge);
extern void Gauge_PartsDraw(GAUGE_WORK *gauge, u32 hp, u32 draw_flag);
extern void Gauge_AnimeStart(GAUGE_WORK *gauge);
extern void Gauge_AnimeStop(GAUGE_WORK *gauge);
extern u8 Gauge_TypeGet(int client_type, u32 fight_type);
extern void Gauge_BGPriSet(GAUGE_WORK *gauge, int bg_pri);
extern void Gauge_OffsetPosSet(GAUGE_WORK *gauge, int x, int y);
extern void Gauge_ScrollEffectSet(GAUGE_WORK *gauge, int in_out);
extern void Gauge_EnableSet(GAUGE_WORK *gauge, int enable);
extern void Gauge_LevelUpEffectStart(GAUGE_WORK *gauge, u8 *end_flag);
extern void Gauge_ColorBlackSet(GAUGE_WORK *gauge);
extern void Gauge_ColorNormalSet(GAUGE_WORK *gauge);
extern void Gauge_SinCurveSet(GAUGE_WORK *gauge);
extern void Gauge_SinCurveStop(GAUGE_WORK *gauge);
extern void Gauge_NumModeChange(GAUGE_WORK *gauge);

extern void Gauge_DebugHPPutFlagFlip(GAUGE_WORK *gauge);
extern void GaugeParts_DebugNumDraw(GAUGE_WORK *gauge, u32 num);


#endif	//__GAUGE_H__
