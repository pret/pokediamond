//==============================================================================
/**
 * @file	gauge.c
 * @brief	戦闘画面：HPゲージ
 * @author	matsuda
 * @date	2005.09.27(火)
 */
//==============================================================================
#include "common.h"
#include "gauge.h"
#include "graphic\batt_obj_def.h"
#include "system/arc_tool.h"
#include "battle/fight_tool.h"
#include "system/fontproc.h"
#include "application/app_tool.h"
#include "system/pm_str.h"
#include "system/numfont.h"
#include "battle/battle_tcb_pri.h"

#include "system/msgdata_util.h"
#include "system/wordset.h"
#include "msgdata/msg_fightmsg_dp.h"

#include "battle/battle_id.h"


//==============================================================================
//	定数定義
//==============================================================================

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
enum{
	GAUGE_REQ_HP,		///<HPバー書き込みリクエスト
	GAUGE_REQ_EXP,		///<EXPバー書き込みリクエスト
};

///ゲージアクターソフトプライオリティ
enum{
	SOFTPRI_START = 10,
	
	SOFTPRI_NAME_AA,	///<AA用ポケモン名
	SOFTPRI_NAME_BB,
	SOFTPRI_NAME_A,
	SOFTPRI_NAME_B,
	SOFTPRI_NAME_C,
	SOFTPRI_NAME_D,

	SOFTPRI_ARROW_AA,	///<AA用ゲージ矢印
	SOFTPRI_ARROW_BB,	///<BB用ゲージ矢印
	SOFTPRI_ARROW_B,
	SOFTPRI_ARROW_C,
	SOFTPRI_ARROW_D,
	SOFTPRI_ARROW_A,

	SOFTPRI_GAUGE_AA,	///<AA用ゲージ本体
	SOFTPRI_GAUGE_BB,	///<BB用ゲージ本体
	SOFTPRI_GAUGE_B,
	SOFTPRI_GAUGE_C,
	SOFTPRI_GAUGE_D,
	SOFTPRI_GAUGE_A,
};

///矢印のゲージ本体の中心からの表示オフセット座標Y
#define ARROW_OFFSET_Y		(0)

///ゲージを画面外に持っていく時のオフセットX
#define GAUGE_SCROLL_OUT_OFFSET_X		(160)
///ゲージを画面外に持っていく時のオフセットY
#define GAUGE_SCROLL_OUT_OFFSET_Y		(0)
///ゲージスクロール時の速度X
#define GAUGE_SCROLL_SP_X		(24)	//(12)

///ゲージSinカーブの秒加算値
#define GAUGE_SIN_SEC_ADD		(20)
///ゲージSinカーブのふり幅Y(fx32)
#define GAUGE_SIN_FURIHABA_Y	(0x1800)


//==============================================================================
//	矢印オフセット座標
//==============================================================================
///矢印のゲージ本体の中心からの表示オフセット座標X
ALIGN4 static const s8 ArrowOffsetPosX[] = {
	72-8,		//AA
	0,			//BB
	72,			//A
	0,			//B
	72-8,		//C
	0,			//D
};

//==============================================================================
//	パーツ描画
//==============================================================================
typedef struct{
	u16 pos;		///転送位置(バイトオフセット)
	u16 size;		///転送サイズ
}PARTS_TRANS_PARAM;

//--------------------------------------------------------------
//	名前
//--------------------------------------------------------------
///名前のXサイズ(キャラ単位)。　※*.NCEファイルで設定している横のキャラ数を記入
#define NAME_SIZE_X		(8)
///名前のYサイズ(キャラ単位)。　※*.NCEファイルで設定している縦のキャラ数を記入
#define NAME_SIZE_Y		(2)
///名前CGXオフセット
#define NAME_CHAR_OFFSET	(0)
///名前キャラクターのバイトサイズ
#define NAME_BYTE_SIZE		(NAME_SIZE_X * NAME_SIZE_Y * 0x20)

//名前描画位置
static const PARTS_TRANS_PARAM NameTrans[][4] = {
	{//GAUGE_TYPE_AA
		{0x12 * 0x20, 6 * 0x20},		///<1枚目OAM：上段
		{0x1a * 0x20, 6 * 0x20},		///<1枚目OAM：下段
		{0x50 * 0x20, 2 * 0x20},		///<2枚目OAM：上段
		{0x58 * 0x20, 2 * 0x20},		///<2枚目OAM：下段
	},
	{//GAUGE_TYPE_BB
		{0x11 * 0x20, 7 * 0x20},		///<1枚目OAM：上段
		{0x19 * 0x20, 7 * 0x20},		///<1枚目OAM：下段
		{0x50 * 0x20, 1 * 0x20},		///<2枚目OAM：上段
		{0x58 * 0x20, 1 * 0x20},		///<2枚目OAM：下段
	},
	{//GAUGE_TYPE_A
		{0x12 * 0x20, 6 * 0x20},		///<1枚目OAM：上段
		{0x1a * 0x20, 6 * 0x20},		///<1枚目OAM：下段
		{0x50 * 0x20, 2 * 0x20},		///<2枚目OAM：上段
		{0x58 * 0x20, 2 * 0x20},		///<2枚目OAM：下段
	},
	{//GAUGE_TYPE_B
		{0x11 * 0x20, 7 * 0x20},		///<1枚目OAM：上段
		{0x19 * 0x20, 7 * 0x20},		///<1枚目OAM：下段
		{0x50 * 0x20, 1 * 0x20},		///<2枚目OAM：上段
		{0x58 * 0x20, 1 * 0x20},		///<2枚目OAM：下段
	},
	{//GAUGE_TYPE_C
		{0x12 * 0x20, 6 * 0x20},		///<1枚目OAM：上段
		{0x1a * 0x20, 6 * 0x20},		///<1枚目OAM：下段
		{0x50 * 0x20, 2 * 0x20},		///<2枚目OAM：上段
		{0x58 * 0x20, 2 * 0x20},		///<2枚目OAM：下段
	},
	{//GAUGE_TYPE_D
		{0x11 * 0x20, 7 * 0x20},		///<1枚目OAM：上段
		{0x19 * 0x20, 7 * 0x20},		///<1枚目OAM：下段
		{0x50 * 0x20, 1 * 0x20},		///<2枚目OAM：上段
		{0x58 * 0x20, 1 * 0x20},		///<2枚目OAM：下段
	},
};

///名前描画位置の背景色番号
#define NAME_BACK_COLOR		(0xf)
///名前の文字色
#define NAME_FONT_COLOR		(GF_PRINTCOLOR_MAKE(0xe, 2, NAME_BACK_COLOR))

//--------------------------------------------------------------
//	レベル文字
//--------------------------------------------------------------
//レベル文字描画位置
static const PARTS_TRANS_PARAM LvFontTrans[][2] = {
	{//GAUGE_TYPE_AA
		{0x52 * 0x20, 2 * 0x20},		///<1枚目OAM
		{0x5a * 0x20, 2 * 0x20},		///<2枚目OAM
	},
	{//GAUGE_TYPE_BB
		{0x51 * 0x20, 2 * 0x20},		///<1枚目OAM
		{0x59 * 0x20, 2 * 0x20},		///<2枚目OAM
	},
	{//GAUGE_TYPE_A
		{0x52 * 0x20, 2 * 0x20},		///<1枚目OAM
		{0x5a * 0x20, 2 * 0x20},		///<2枚目OAM
	},
	{//GAUGE_TYPE_B
		{0x51 * 0x20, 2 * 0x20},		///<1枚目OAM
		{0x59 * 0x20, 2 * 0x20},		///<2枚目OAM
	},
	{//GAUGE_TYPE_C
		{0x52 * 0x20, 2 * 0x20},		///<1枚目OAM
		{0x5a * 0x20, 2 * 0x20},		///<2枚目OAM
	},
	{//GAUGE_TYPE_D
		{0x51 * 0x20, 2 * 0x20},		///<1枚目OAM
		{0x59 * 0x20, 2 * 0x20},		///<2枚目OAM
	},
};

//--------------------------------------------------------------
//	レベル
//--------------------------------------------------------------
//レベル描画位置
static const PARTS_TRANS_PARAM LvTrans[][2] = {
	{//GAUGE_TYPE_AA
		{0x54 * 0x20, 3 * 0x20},		///<1枚目OAM
		{0x5c * 0x20, 3 * 0x20},		///<2枚目OAM
	},
	{//GAUGE_TYPE_BB
		{0x53 * 0x20, 3 * 0x20},		///<1枚目OAM
		{0x5b * 0x20, 3 * 0x20},		///<2枚目OAM
	},
	{//GAUGE_TYPE_A
		{0x54 * 0x20, 3 * 0x20},		///<1枚目OAM
		{0x5c * 0x20, 3 * 0x20},		///<2枚目OAM
	},
	{//GAUGE_TYPE_B
		{0x53 * 0x20, 3 * 0x20},		///<1枚目OAM
		{0x5b * 0x20, 3 * 0x20},		///<2枚目OAM
	},
	{//GAUGE_TYPE_C
		{0x54 * 0x20, 3 * 0x20},		///<1枚目OAM
		{0x5c * 0x20, 3 * 0x20},		///<2枚目OAM
	},
	{//GAUGE_TYPE_D
		{0x53 * 0x20, 3 * 0x20},		///<1枚目OAM
		{0x5b * 0x20, 3 * 0x20},		///<2枚目OAM
	},
};

///レベル描画位置の背景色番号
#define LEVEL_BACK_COLOR		(NAME_BACK_COLOR)
///レベルの文字色
#define LEVEL_FONT_COLOR		(NAME_FONT_COLOR)

//--------------------------------------------------------------
//	現在HP
//--------------------------------------------------------------
//現在HP描画位置
static const PARTS_TRANS_PARAM HPTrans[][2] = {
	{//GAUGE_TYPE_AA
		{0x68 * 0x20, 3 * 0x20},		///<2枚目OAM
		{0, 0 * 0x20},					///<2枚目OAM
	},
	{//GAUGE_TYPE_BB
		{0x31 * 0x20, 3 * 0x20},			///<1枚目OAM
		{0, 0 * 0x20},					///<2枚目OAM
	},
	{//GAUGE_TYPE_A
		{0, 0 * 0x20},		///<1枚目OAM
		{0x60 * 0x20, 3 * 0x20},		///<2枚目OAM
	},
	{//GAUGE_TYPE_B
		{0x31 * 0x20, 3 * 0x20},			///<1枚目OAM
		{0, 0 * 0x20},					///<2枚目OAM
	},
	{//GAUGE_TYPE_C
		{0 * 0x20, 0 * 0x20},		///<1枚目OAM
		{0x60 * 0x20, 3 * 0x20},		///<2枚目OAM
	},
	{//GAUGE_TYPE_D
		{0x31 * 0x20, 3 * 0x20},			///<1枚目OAM
		{0, 0 * 0x20},					///<2枚目OAM
	},
};

///現在HP描画位置の背景色番号
#define HP_BACK_COLOR		(0xf)
///現在HPの文字色
#define HP_FONT_COLOR		(GF_PRINTCOLOR_MAKE(0xe, 2, HP_BACK_COLOR))

//--------------------------------------------------------------
//	最大HP
//--------------------------------------------------------------
//最大HP描画位置
static const PARTS_TRANS_PARAM HPMaxTrans[] = {
	//GAUGE_TYPE_AA
	{0x6c * 0x20, 3 * 0x20},		///<2枚目OAM
	//GAUGE_TYPE_BB
	{0x35 * 0x20, 3 * 0x20},		///<2枚目OAM
	//GAUGE_TYPE_A
	{0x64 * 0x20, 3 * 0x20},		///<2枚目OAM
	//GAUGE_TYPE_B
	{0x35 * 0x20, 3 * 0x20},		///<2枚目OAM
	//GAUGE_TYPE_C
	{0x64 * 0x20, 3 * 0x20},		///<2枚目OAM
	//GAUGE_TYPE_D
	{0x35 * 0x20, 3 * 0x20},		///<2枚目OAM
};

///最大HP描画位置の背景色番号
#define HPMAX_BACK_COLOR		(HP_BACK_COLOR)
///最大HPの文字色
#define HPMAX_FONT_COLOR		(HP_FONT_COLOR)

//--------------------------------------------------------------
//	デバッグ数値
//--------------------------------------------------------------
#ifdef PM_DEBUG
#define DEBUG_NUM_KETA_MAX		(8)
static const PARTS_TRANS_PARAM DebugNumTrans[] = {
	//GAUGE_TYPE_AA
	{0x78 * 0x20, DEBUG_NUM_KETA_MAX * 0x20},		///<2枚目OAM
	//GAUGE_TYPE_BB
	{0x78 * 0x20, DEBUG_NUM_KETA_MAX * 0x20},		///<2枚目OAM
	//GAUGE_TYPE_A
	{0x78 * 0x20, DEBUG_NUM_KETA_MAX * 0x20},		///<2枚目OAM
	//GAUGE_TYPE_B
	{0x78 * 0x20, DEBUG_NUM_KETA_MAX * 0x20},		///<2枚目OAM
	//GAUGE_TYPE_C
	{0x78 * 0x20, DEBUG_NUM_KETA_MAX * 0x20},		///<2枚目OAM
	//GAUGE_TYPE_D
	{0x78 * 0x20, DEBUG_NUM_KETA_MAX * 0x20},		///<2枚目OAM
};
#endif

//--------------------------------------------------------------
//	HPバー
//--------------------------------------------------------------
//HPバー描画位置
static const PARTS_TRANS_PARAM HPBarTrans[][2] = {
	{//GAUGE_TYPE_AA
		{0x27 * 0x20, 0 * 0x20},		///<1枚目OAM
		{0x60 * 0x20, 6 * 0x20},		///<2枚目OAM
	},
	{//GAUGE_TYPE_BB
		{0x27 * 0x20, 1 * 0x20},		///<1枚目OAM
		{0x60 * 0x20, 5 * 0x20},		///<2枚目OAM
	},
	{//GAUGE_TYPE_A
		{0x27 * 0x20, 0 * 0x20},		///<1枚目OAM
		{0x60 * 0x20, 6 * 0x20},		///<2枚目OAM
	},
	{//GAUGE_TYPE_B
		{0x27 * 0x20, 1 * 0x20},		///<1枚目OAM
		{0x60 * 0x20, 5 * 0x20},		///<2枚目OAM
	},
	{//GAUGE_TYPE_C
		{0x27 * 0x20, 0 * 0x20},		///<1枚目OAM
		{0x60 * 0x20, 6 * 0x20},		///<2枚目OAM
	},
	{//GAUGE_TYPE_D
		{0x27 * 0x20, 1 * 0x20},		///<1枚目OAM
		{0x60 * 0x20, 5 * 0x20},		///<2枚目OAM
	},
};

///HPバー描画位置の背景色番号
#define HPBAR_BACK_COLOR		(HP_BACK_COLOR)
///HPバーの文字色
#define HPBAR_FONT_COLOR		(HP_FONT_COLOR)

//--------------------------------------------------------------
//	経験値バー
//--------------------------------------------------------------
//EXPバー描画位置(シングル・ダブル・味方・敵共通)
enum{
	EXPBAR_FAST_HIGH = 0x34 * 0x20,		///<EXPバー：1枚目のOAMの描画開始位置
	EXPBAR_SECOND_HIGH = 0x70 * 0x20,	///<EXPバー：2枚目のOAMの描画開始位置
	
	EXPBAR_NEXT_OAM = 4,		///<1枚目のOAMが持つEXPバーのキャラ数
};

//--------------------------------------------------------------
//	性別
//--------------------------------------------------------------
//性別転送位置
static const PARTS_TRANS_PARAM SexTrans[][2] = {
	{//GAUGE_TYPE_AA
		{0x52 * 0x20, 1 * 0x20},		///<上段
		{0x5a * 0x20, 1 * 0x20},		///<下段
	},
	{//GAUGE_TYPE_BB
		{0x50 * 0x20, 1 * 0x20},		///<上段
		{0x58 * 0x20, 1 * 0x20},		///<下段
	},
	{//GAUGE_TYPE_A
		{0x51 * 0x20, 1 * 0x20},		///<上段
		{0x59 * 0x20, 1 * 0x20},		///<下段
	},
	{//GAUGE_TYPE_B
		{0x51 * 0x20, 1 * 0x20},		///<上段
		{0x59 * 0x20, 1 * 0x20},		///<下段
	},
	{//GAUGE_TYPE_C
		{0x52 * 0x20, 1 * 0x20},		///<上段
		{0x5a * 0x20, 1 * 0x20},		///<下段
	},
	{//GAUGE_TYPE_D
		{0x50 * 0x20, 1 * 0x20},		///<上段
		{0x58 * 0x20, 1 * 0x20},		///<下段
	},
};

//--------------------------------------------------------------
//	ゲット済みマーク
//--------------------------------------------------------------
//ゲット済みマーク転送位置
static const PARTS_TRANS_PARAM GetBallTrans[] = {
	//GAUGE_TYPE_AA
	{0x22 * 0x20, 1 * 0x20},
	//GAUGE_TYPE_BB
	{0x21 * 0x20, 1 * 0x20},
	//GAUGE_TYPE_A
	{0x22 * 0x20, 1 * 0x20},
	//GAUGE_TYPE_B
	{0x21 * 0x20, 1 * 0x20},
	//GAUGE_TYPE_C
	{0x22 * 0x20, 1 * 0x20},
	//GAUGE_TYPE_D
	{0x21 * 0x20, 1 * 0x20},
};

//--------------------------------------------------------------
//	状態異常
//--------------------------------------------------------------
//状態異常転送位置
static const PARTS_TRANS_PARAM StatusTrans[] = {
	//GAUGE_TYPE_AA
	{0x23 * 0x20, 3 * 0x20},
	//GAUGE_TYPE_BB
	{0x22 * 0x20, 3 * 0x20},
	//GAUGE_TYPE_A
	{0x23 * 0x20, 3 * 0x20},
	//GAUGE_TYPE_B
	{0x22 * 0x20, 3 * 0x20},
	//GAUGE_TYPE_C
	{0x23 * 0x20, 3 * 0x20},
	//GAUGE_TYPE_D
	{0x22 * 0x20, 3 * 0x20},
};


//--------------------------------------------------------------
//	サファリボール
//--------------------------------------------------------------
///「サファリボール」のXサイズ(キャラ単位)。　※*.NCEファイルで設定している横のキャラ数を記入
#define SAFARIBALL_SIZE_X		(13)
///「サファリボール」のYサイズ(キャラ単位)。　※*.NCEファイルで設定している縦のキャラ数を記入
#define SAFARIBALL_SIZE_Y		(2)
///「サファリボール」CGXオフセット
#define SAFARIBALL_CHAR_OFFSET	(0)
///「サファリボール」キャラクターのバイトサイズ
#define SAFARIBALL_BYTE_SIZE		(SAFARIBALL_SIZE_X * SAFARIBALL_SIZE_Y * 0x20)

//「サファリボール」描画位置
static const PARTS_TRANS_PARAM SafariballTrans[4] = {
	{0x12 * 0x20, 6 * 0x20},		///<1枚目OAM：上段
	{0x1a * 0x20, 6 * 0x20},		///<1枚目OAM：下段
	{0x50 * 0x20, 7 * 0x20},		///<2枚目OAM：上段
	{0x58 * 0x20, 7 * 0x20},		///<2枚目OAM：下段
};

///「サファリボール」描画位置の背景色番号
#define SAFARIBALL_BACK_COLOR		(0xf)
///「サファリボール」の文字色
#define SAFARIBALL_FONT_COLOR		(GF_PRINTCOLOR_MAKE(0xe, 2, SAFARIBALL_BACK_COLOR))


//--------------------------------------------------------------
//	のこり　○○こ
//--------------------------------------------------------------
///「のこり　○○こ」のXサイズ(キャラ単位)。　※*.NCEファイルで設定している横のキャラ数を記入
#define NOKORI_SIZE_X		(13)
///「のこり　○○こ」のYサイズ(キャラ単位)。　※*.NCEファイルで設定している縦のキャラ数を記入
#define NOKORI_SIZE_Y		(2)
///「のこり　○○こ」CGXオフセット
#define NOKORI_CHAR_OFFSET	(0)
///「のこり　○○こ」キャラクターのバイトサイズ
#define NOKORI_BYTE_SIZE		(NOKORI_SIZE_X * NOKORI_SIZE_Y * 0x20)

//「のこり　○○こ」描画位置
static const PARTS_TRANS_PARAM NokoriTrans[4] = {
	{0x22 * 0x20, 6 * 0x20},		///<1枚目OAM：上段
	{0x2a * 0x20, 6 * 0x20},		///<1枚目OAM：下段
	{0x60 * 0x20, 7 * 0x20},		///<2枚目OAM：上段
	{0x68 * 0x20, 7 * 0x20},		///<2枚目OAM：下段
};

///「のこり　○○こ」描画位置の背景色番号
#define NOKORI_BACK_COLOR		(0xf)
///「のこり　○○こ」の文字色
#define NOKORI_FONT_COLOR		(GF_PRINTCOLOR_MAKE(0xe, 2, NOKORI_BACK_COLOR))

///「のこり　○○こ」の数値桁数
#define NOKORI_SAFARI_NUM_KETA		(2)

//--------------------------------------------------------------
//	2vs2ゲージのHP数値表示モード
//--------------------------------------------------------------
//HPバーの頭描画位置
static const PARTS_TRANS_PARAM HPBarHeadTrans[] = {
	//GAUGE_TYPE_AA
	{0 * 0x20, 0 * 0x20},		///<1枚目OAM
	//GAUGE_TYPE_BB
	{0 * 0x20, 0 * 0x20},		///<1枚目OAM
	//GAUGE_TYPE_A
	{0x26 * 0x20, 2 * 0x20},		///<1枚目OAM
	//GAUGE_TYPE_B
	{0 * 0x20, 0 * 0x20},		///<1枚目OAM
	//GAUGE_TYPE_C
	{0x26 * 0x20, 2 * 0x20},		///<1枚目OAM
	//GAUGE_TYPE_D
	{0 * 0x20, 0 * 0x20},		///<1枚目OAM
};

//HPバーの蓋描画位置
static const PARTS_TRANS_PARAM HPBarCapTrans[] = {
	//GAUGE_TYPE_AA
	{0 * 0x20, 0 * 0x20},		///<1枚目OAM
	//GAUGE_TYPE_BB
	{0 * 0x20, 0 * 0x20},		///<1枚目OAM
	//GAUGE_TYPE_A
	{0x66 * 0x20, 1 * 0x20},		///<1枚目OAM
	//GAUGE_TYPE_B
	{0 * 0x20, 0 * 0x20},		///<1枚目OAM
	//GAUGE_TYPE_C
	{0x66 * 0x20, 1 * 0x20},		///<1枚目OAM
	//GAUGE_TYPE_D
	{0 * 0x20, 0 * 0x20},		///<1枚目OAM
};

//HPのスラッシュ描画位置(2vs2ゲージの数値モードの時用)
static const PARTS_TRANS_PARAM HPSlashTrans[] = {
	//GAUGE_TYPE_AA
	{0 * 0x20, 0 * 0x20},		///<1枚目OAM
	//GAUGE_TYPE_BB
	{0 * 0x20, 0 * 0x20},		///<1枚目OAM
	//GAUGE_TYPE_A
	{0x63 * 0x20, 1 * 0x20},		///<1枚目OAM
	//GAUGE_TYPE_B
	{0 * 0x20, 0 * 0x20},		///<1枚目OAM
	//GAUGE_TYPE_C
	{0x63 * 0x20, 1 * 0x20},		///<1枚目OAM
	//GAUGE_TYPE_D
	{0 * 0x20, 0 * 0x20},		///<1枚目OAM
};


//==============================================================================
//	プロトタイプ宣言
//==============================================================================
static s32 GaugeOBJ(GAUGE_WORK *gauge, int req_data);
static s32 GaugeProc(s32 MaxHP, s32 NowHP, s32 beHP, s32 *HP_Work, u8 GaugeMax, u16 add_dec);
static u8 PutGaugeProc(s32 MaxHP, s32 NowHP, s32 beHP, s32 *HP_Work, u8 *gauge_chr, u8 GaugeMax);
static u32 DottoOffsetCalc(s32 nowHP, s32 beHP, s32 MaxHP, u8 GaugeMax);
static const u8 * GetGaugePartsAdrs(int parts_num);
static void PutGaugeOBJ(GAUGE_WORK *gauge, u8 req);
void MsgTool_OamSlideBuf(void *src_buf, void *dest_buf, const u8 oam_list[], int list_num);
static void GaugeParts_NameDraw(GAUGE_WORK *gauge);
static void GaugeParts_LevelFontDraw(GAUGE_WORK *gauge);
static void GaugeParts_LevelDraw(GAUGE_WORK *gauge);
static void GaugeParts_HPDraw(GAUGE_WORK *gauge, u32 hp);
static void GaugeParts_HPMaxDraw(GAUGE_WORK *gauge);
static void GaugeParts_SexDraw(GAUGE_WORK *gauge);
static void GaugeParts_GetBallDraw(GAUGE_WORK *gauge);
static void GaugeParts_StatusDraw(GAUGE_WORK *gauge, int gp_num);
static void GaugeParts_SafariballDraw(GAUGE_WORK *gauge, u32 draw_flag);
static void GaugeParts_SafariNokoriDraw(GAUGE_WORK *gauge, u32 draw_flag);
static void Gauge_ArrowResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, PALETTE_FADE_PTR pfd, 
	int gauge_type);
static CATS_ACT_PTR Gauge_ArrowActorSet(CATS_SYS_PTR csp, CATS_RES_PTR crp, int gauge_type);
static void Gauge_ArrowActorDel(GAUGE_WORK *gauge);
static void Gauge_ArrowResourceFree(GAUGE_WORK *gauge);
static const TCATS_OBJECT_ADD_PARAM_S * Sub_GaugeObjHeadGet(u8 gauge_type);
static const TCATS_OBJECT_ADD_PARAM_S * Sub_ArrowObjHeadGet(u8 gauge_type);
static void Gauge_ScrollInOut(TCB_PTR tcb, void *work);
static void GaugeLevelUpEffTask(TCB_PTR tcb, void *work);
void Gauge_SinCurveSet(GAUGE_WORK *gauge);
void Gauge_SinCurveStop(GAUGE_WORK *gauge);
static void GaugeSinCurveMain(TCB_PTR tcb, void *work);
static void Gauge_ArrowEnableSet(GAUGE_WORK *gauge, int enable);


//==============================================================================
//	データ
//==============================================================================
///AA用ゲージアクターヘッダ
static const TCATS_OBJECT_ADD_PARAM_S GaugeObjParam_aa = {
	192+6,112 + 4, 0,		//x, y, z
	0, SOFTPRI_GAUGE_AA, 0,		//アニメ番号、優先順位、パレット番号
	NNS_G2D_VRAM_TYPE_2DMAIN,		//描画エリア
	{	//使用リソースIDテーブル
		SINGLE_GAGE2_NCGR_BIN,	//キャラ
		PLTTID_GAUGE,	//パレット
		SINGLE_GAGE2_NCER_BIN,	//セル
		SINGLE_GAGE2_NANR_BIN,	//セルアニメ
		CLACT_U_HEADER_DATA_NONE,		//マルチセル
		CLACT_U_HEADER_DATA_NONE,		//マルチセルアニメ
	},
	GAUGE_DEFAULT_BGPRI,			//BGプライオリティ
	0,			//Vram転送フラグ
};

///BB用ゲージアクターヘッダ
static const TCATS_OBJECT_ADD_PARAM_S GaugeObjParam_bb = {
	64-6,40-4, 0,		//x, y, z
	0, SOFTPRI_GAUGE_BB, 0,		//アニメ番号、優先順位、パレット番号
	NNS_G2D_VRAM_TYPE_2DMAIN,		//描画エリア
	{	//使用リソースIDテーブル
		SINGLE_GAGE1_NCGR_BIN,	//キャラ
		PLTTID_GAUGE,	//パレット
		SINGLE_GAGE1_NCER_BIN,	//セル
		SINGLE_GAGE1_NANR_BIN,	//セルアニメ
		CLACT_U_HEADER_DATA_NONE,		//マルチセル
		CLACT_U_HEADER_DATA_NONE,		//マルチセルアニメ
	},
	GAUGE_DEFAULT_BGPRI,			//BGプライオリティ
	0,			//Vram転送フラグ
};

///A用ゲージアクターヘッダ
static const TCATS_OBJECT_ADD_PARAM_S GaugeObjParam_a = {
	192,96 + 7, 0,		//x, y, z
	0, SOFTPRI_GAUGE_A, 0,		//アニメ番号、優先順位、パレット番号
	NNS_G2D_VRAM_TYPE_2DMAIN,		//描画エリア
	{	//使用リソースIDテーブル
		DOUBLE_GAGE3_NCGR_BIN,	//キャラ
		PLTTID_GAUGE,	//パレット
		DOUBLE_GAGE3_NCER_BIN,	//セル
		DOUBLE_GAGE3_NANR_BIN,	//セルアニメ
		CLACT_U_HEADER_DATA_NONE,		//マルチセル
		CLACT_U_HEADER_DATA_NONE,		//マルチセルアニメ
	},
	GAUGE_DEFAULT_BGPRI,			//BGプライオリティ
	0,			//Vram転送フラグ
};

///B用ゲージアクターヘッダ
static const TCATS_OBJECT_ADD_PARAM_S GaugeObjParam_b = {
	64,19-3, 0,		//x, y, z
	0, SOFTPRI_GAUGE_B, 0,		//アニメ番号、優先順位、パレット番号
	NNS_G2D_VRAM_TYPE_2DMAIN,		//描画エリア
	{	//使用リソースIDテーブル
		DOUBLE_GAGE1_NCGR_BIN,	//キャラ
		PLTTID_GAUGE,	//パレット
		DOUBLE_GAGE1_NCER_BIN,	//セル
		DOUBLE_GAGE1_NANR_BIN,	//セルアニメ
		CLACT_U_HEADER_DATA_NONE,		//マルチセル
		CLACT_U_HEADER_DATA_NONE,		//マルチセルアニメ
	},
	GAUGE_DEFAULT_BGPRI,			//BGプライオリティ
	0,			//Vram転送フラグ
};

///C用ゲージアクターヘッダ
static const TCATS_OBJECT_ADD_PARAM_S GaugeObjParam_c = {
	192+6,128+4, 0,		//x, y, z
	0, SOFTPRI_GAUGE_C, 0,		//アニメ番号、優先順位、パレット番号
	NNS_G2D_VRAM_TYPE_2DMAIN,		//描画エリア
	{	//使用リソースIDテーブル
		DOUBLE_GAGE4_NCGR_BIN,	//キャラ
		PLTTID_GAUGE,	//パレット
		DOUBLE_GAGE4_NCER_BIN,	//セル
		DOUBLE_GAGE4_NANR_BIN,	//セルアニメ
		CLACT_U_HEADER_DATA_NONE,		//マルチセル
		CLACT_U_HEADER_DATA_NONE,		//マルチセルアニメ
	},
	GAUGE_DEFAULT_BGPRI,			//BGプライオリティ
	0,			//Vram転送フラグ
};

///D用ゲージアクターヘッダ
static const TCATS_OBJECT_ADD_PARAM_S GaugeObjParam_d = {
	64-6,48-3, 0,		//x, y, z
	0, SOFTPRI_GAUGE_D, 0,		//アニメ番号、優先順位、パレット番号
	NNS_G2D_VRAM_TYPE_2DMAIN,		//描画エリア
	{	//使用リソースIDテーブル
		DOUBLE_GAGE2_NCGR_BIN,	//キャラ
		PLTTID_GAUGE,	//パレット
		DOUBLE_GAGE2_NCER_BIN,	//セル
		DOUBLE_GAGE2_NANR_BIN,	//セルアニメ
		CLACT_U_HEADER_DATA_NONE,		//マルチセル
		CLACT_U_HEADER_DATA_NONE,		//マルチセルアニメ
	},
	GAUGE_DEFAULT_BGPRI,			//BGプライオリティ
	0,			//Vram転送フラグ
};

///AA用ゲージ矢印アクターヘッダ
static const TCATS_OBJECT_ADD_PARAM_S ArrowParam_aa = {
	0,0, 0,		//x, y, z
	0, SOFTPRI_ARROW_AA, 0,		//アニメ番号、優先順位、パレット番号
	NNS_G2D_VRAM_TYPE_2DMAIN,		//描画エリア
	{	//使用リソースIDテーブル
		SINGLE_ARROW_ANIMATION2_NCGR_BIN,	//キャラ
		PLTTID_GAUGE,	//パレット
		SINGLE_ARROW_ANIMATION2_NCER_BIN,	//セル
		SINGLE_ARROW_ANIMATION2_NANR_BIN,	//セルアニメ
		CLACT_U_HEADER_DATA_NONE,		//マルチセル
		CLACT_U_HEADER_DATA_NONE,		//マルチセルアニメ
	},
	GAUGE_DEFAULT_BGPRI,			//BGプライオリティ
	0,			//Vram転送フラグ
};

///BB用ゲージ矢印アクターヘッダ
static const TCATS_OBJECT_ADD_PARAM_S ArrowParam_bb = {
	0, 0, 0,		//x, y, z
	0, SOFTPRI_ARROW_BB, 0,		//アニメ番号、優先順位、パレット番号
	NNS_G2D_VRAM_TYPE_2DMAIN,		//描画エリア
	{	//使用リソースIDテーブル
		SINGLE_ARROW_ANIMATION1_NCGR_BIN,	//キャラ
		PLTTID_GAUGE,	//パレット
		SINGLE_ARROW_ANIMATION1_NCER_BIN,	//セル
		SINGLE_ARROW_ANIMATION1_NANR_BIN,	//セルアニメ
		CLACT_U_HEADER_DATA_NONE,		//マルチセル
		CLACT_U_HEADER_DATA_NONE,		//マルチセルアニメ
	},
	GAUGE_DEFAULT_BGPRI,			//BGプライオリティ
	0,			//Vram転送フラグ
};

///サファリ用ゲージアクターヘッダ
static const TCATS_OBJECT_ADD_PARAM_S GaugeObjParam_Safari = {
	192,112 + 4, 0,		//x, y, z
	0, SOFTPRI_GAUGE_AA, 0,		//アニメ番号、優先順位、パレット番号
	NNS_G2D_VRAM_TYPE_2DMAIN,		//描画エリア
	{	//使用リソースIDテーブル
		SAFARI_GAUGE_NCGR_BIN,	//キャラ
		PLTTID_GAUGE_SAFARI,	//パレット
		SAFARI_GAUGE_NCER_BIN,	//セル
		SAFARI_GAUGE_NANR_BIN,	//セルアニメ
		CLACT_U_HEADER_DATA_NONE,		//マルチセル
		CLACT_U_HEADER_DATA_NONE,		//マルチセルアニメ
	},
	GAUGE_DEFAULT_BGPRI,			//BGプライオリティ
	0,			//Vram転送フラグ
};


//==============================================================================
//	外部データ
//==============================================================================
#include "gage_parts_txt.dat"


//--------------------------------------------------------------
/**
 * @brief   ゲージのリソース読み込み
 *
 * @param   gauge		
 */
//--------------------------------------------------------------
void Gauge_ResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, PALETTE_FADE_PTR pfd, int gauge_type)
{
	const TCATS_OBJECT_ADD_PARAM_S *obj_head;
	
	//リソース読み込み
	obj_head = Sub_GaugeObjHeadGet(gauge_type);
	
	CATS_LoadResourceCharArc(csp, crp, ARC_BATT_OBJ, obj_head->id[CLACT_U_CHAR_RES], 1, 
		NNS_G2D_VRAM_TYPE_2DMAIN, obj_head->id[CLACT_U_CHAR_RES]);
//	CATS_LoadResourcePlttArc(csp, crp, ARC_BATT_OBJ, obj_head->id[CLACT_U_PLTT_RES], 0, 
//		1, NNS_G2D_VRAM_TYPE_2DMAIN, obj_head->id[CLACT_U_PLTT_RES]);
	CATS_LoadResourcePlttWorkArc(pfd, FADE_MAIN_OBJ, csp, crp, 
		ARC_BATT_OBJ, GAGE_PALETTE_NCLR, 0, 
		1, NNS_G2D_VRAM_TYPE_2DMAIN, PLTTID_GAUGE);
	CATS_LoadResourceCellArc(csp, crp, ARC_BATT_OBJ, obj_head->id[CLACT_U_CELL_RES], 1, 
		obj_head->id[CLACT_U_CELL_RES]);
	CATS_LoadResourceCellAnmArc(csp, crp, ARC_BATT_OBJ, 
		obj_head->id[CLACT_U_CELLANM_RES], 1, obj_head->id[CLACT_U_CELLANM_RES]);

	//エフェクト用パレットセット
	CATS_LoadResourcePlttWorkArc(pfd, FADE_MAIN_OBJ, csp, crp, 
		ARC_BATT_OBJ, GAGE_PALETTE_NCLR, 0, 
		1, NNS_G2D_VRAM_TYPE_2DMAIN, PLTTID_GAUGE_EFF);
	if(gauge_type == GAUGE_TYPE_SAFARI || gauge_type == GAUGE_TYPE_PARK){
		CATS_LoadResourcePlttWorkArc(pfd, FADE_MAIN_OBJ, csp, crp, 
			ARC_BATT_OBJ, SAFARI_W_NCLR, 0, 
			1, NNS_G2D_VRAM_TYPE_2DMAIN, PLTTID_GAUGE_SAFARI);
	}
}

//--------------------------------------------------------------
/**
 * @brief   ゲージ矢印のリソース読み込み
 *
 * @param   gauge		ゲージワークへのポインタ
 */
//--------------------------------------------------------------
static void Gauge_ArrowResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp, PALETTE_FADE_PTR pfd, 
	int gauge_type)
{
	const TCATS_OBJECT_ADD_PARAM_S *obj_head;
	
	//リソース読み込み
	obj_head = Sub_ArrowObjHeadGet(gauge_type);
	if(obj_head != NULL){
		CATS_LoadResourceCharArc(csp, crp, ARC_BATT_OBJ, obj_head->id[CLACT_U_CHAR_RES], 
			1, NNS_G2D_VRAM_TYPE_2DMAIN, obj_head->id[CLACT_U_CHAR_RES]);
//		CATS_LoadResourcePlttArc(csp, crp, ARC_BATT_OBJ, obj_head->id[CLACT_U_PLTT_RES], 
//			0, 1, NNS_G2D_VRAM_TYPE_2DMAIN, obj_head->id[CLACT_U_PLTT_RES]);
		CATS_LoadResourcePlttWorkArc(pfd, FADE_MAIN_OBJ, csp, crp, 
			ARC_BATT_OBJ, GAGE_PALETTE_NCLR, 
			0, 1, NNS_G2D_VRAM_TYPE_2DMAIN, PLTTID_GAUGE);
		CATS_LoadResourceCellArc(csp, crp, ARC_BATT_OBJ, obj_head->id[CLACT_U_CELL_RES], 
			1, obj_head->id[CLACT_U_CELL_RES]);
		CATS_LoadResourceCellAnmArc(csp, crp, ARC_BATT_OBJ, 
			obj_head->id[CLACT_U_CELLANM_RES], 1, 
			obj_head->id[CLACT_U_CELLANM_RES]);
	}
}

//--------------------------------------------------------------
/**
 * @brief   ゲージのアクターを生成する
 *
 * @param   gauge		
 *
 * 先にリソースが読み込まれている必要があります。
 */
//--------------------------------------------------------------
CATS_ACT_PTR Gauge_ActorSet(CATS_SYS_PTR csp, CATS_RES_PTR crp, int gauge_type)
{
	const TCATS_OBJECT_ADD_PARAM_S *obj_head;
	CATS_ACT_PTR cap;
	
	obj_head = Sub_GaugeObjHeadGet(gauge_type);

	cap = CATS_ObjectAdd_S(csp, crp, obj_head);
	CATS_ObjectUpdate(cap->act);
	return cap;
}

//--------------------------------------------------------------
/**
 * @brief   ゲージ矢印のアクターを生成する
 * @param   gauge		ゲージワークへのポインタ
 */
//--------------------------------------------------------------
static CATS_ACT_PTR Gauge_ArrowActorSet(CATS_SYS_PTR csp, CATS_RES_PTR crp, int gauge_type)
{
	const TCATS_OBJECT_ADD_PARAM_S *obj_head;
	CATS_ACT_PTR arrow_cap;
	
	obj_head = Sub_ArrowObjHeadGet(gauge_type);
	if(obj_head == NULL){
		arrow_cap = NULL;
		return arrow_cap;
	}
	
	arrow_cap = CATS_ObjectAdd_S(csp, crp, obj_head);
	CATS_ObjectUpdate(arrow_cap->act);
	return arrow_cap;
}

//--------------------------------------------------------------
/**
 * @brief   ゲージのパーツ(HPバー、状態異常等)を描画する
 *
 * @param   gauge			ゲージワークへのポインタ
 * @param   hp				表示するHP(Calc等で途中経過を表示する必要があるのでHPだけは引数指定)
 * @param   draw_flag		描画するパーツのフラグ(GAUGE_DRAW_???) ※ビット指定(複数指定可)
 *
 * この関数は再描画用です。HP加減算処理の書き換えに使用するものではありません。
 * HP加減算の書き換えを行う場合はGauge_CalcHP関数を使用してください。
 * 
 * 再描画するフラグによっては作業用ワークの初期化も行います
 */
//--------------------------------------------------------------
void Gauge_PartsDraw(GAUGE_WORK *gauge, u32 hp, u32 draw_flag)
{
	int status_getball = FALSE;
	u32 draw_backup;
	
	GF_ASSERT(gauge->cap != NULL);
	
	draw_backup = draw_flag;
	
	//不要なビットを落とす
	if(gauge->type == GAUGE_TYPE_SAFARI){
		draw_flag &= GAUGE_DRAW_ALL_SAFARI;
	}
	else if(gauge->type == GAUGE_TYPE_PARK){
		draw_flag &= GAUGE_DRAW_ALL_PARK;
	}
	else{
		draw_flag &= GAUGE_DRAW_ALL ^ (GAUGE_DRAW_ALL_SAFARI | GAUGE_DRAW_ALL_PARK);
	}
	switch(gauge->type){
	case GAUGE_TYPE_BB:
	case GAUGE_TYPE_B:
	case GAUGE_TYPE_D:
		draw_flag &= GAUGE_DRAW_ALL ^ (GAUGE_DRAW_HPNUM | GAUGE_DRAW_HPNUMMAX | GAUGE_DRAW_EXP);
		status_getball = TRUE;	//ステータス表示がノーマル描画の時、ゲット済みボール表示する
	#ifdef PM_DEBUG
		if(gauge->debug_hp_put == TRUE){
			if(draw_backup & GAUGE_DRAW_HPNUM){
				draw_flag |= GAUGE_DRAW_HPNUM;
			}
			if(draw_backup & GAUGE_DRAW_HPNUMMAX){
				draw_flag |= GAUGE_DRAW_HPNUMMAX;
			}
		}
	#endif
		break;
	case GAUGE_TYPE_A:
	case GAUGE_TYPE_C:
		draw_flag &= GAUGE_DRAW_ALL ^ (GAUGE_DRAW_EXP | GAUGE_DRAW_GETBALL);
		if(gauge->num_mode == FALSE){	//HP表示：バー
			draw_flag &= GAUGE_DRAW_ALL ^ (GAUGE_DRAW_HPNUM | GAUGE_DRAW_HPNUMMAX);
		}
		else{	//HP表示：数値
			draw_flag &= GAUGE_DRAW_ALL ^ (GAUGE_DRAW_HPBAR);
		}
		break;
	case GAUGE_TYPE_AA:
		draw_flag &= GAUGE_DRAW_ALL ^ (GAUGE_DRAW_GETBALL);
		break;
	case GAUGE_TYPE_SAFARI:
	case GAUGE_TYPE_PARK:
		break;
	}
	if(BattleWorkFightTypeGet(gauge->bw) & FIGHT_TYPE_TRAINER){
		draw_flag &= GAUGE_DRAW_ALL ^ (GAUGE_DRAW_GETBALL);
	}
	
	
	if(draw_flag & GAUGE_DRAW_HPBAR){
		Gauge_InitCalcHP(gauge, 0);
		GaugeOBJ(gauge, GAUGE_REQ_HP);
	}
	
	if(draw_flag & GAUGE_DRAW_HPNUM){
		GaugeParts_HPDraw(gauge, hp);
	}
	
	if(draw_flag & GAUGE_DRAW_HPNUMMAX){
		GaugeParts_HPMaxDraw(gauge);
	}
	
//	if(draw_flag & GAUGE_DRAW_LEVEL_FONT){
	if((draw_flag & GAUGE_DRAW_LEVEL_FONT) || (draw_flag & GAUGE_DRAW_SEX)){
		GaugeParts_LevelFontDraw(gauge);
	}
	
	if(draw_flag & GAUGE_DRAW_LEVEL){
		GaugeParts_LevelDraw(gauge);
	}
	
	if(draw_flag & GAUGE_DRAW_NAME){
		GaugeParts_NameDraw(gauge);
	}
	
	if(draw_flag & GAUGE_DRAW_EXP){
		Gauge_InitCalcEXP(gauge, 0);
		GaugeOBJ(gauge, GAUGE_REQ_EXP);
	}
	
#if 0	//「LV」文字と統合 2006.04.19(水)
	if(draw_flag & GAUGE_DRAW_SEX){
		GaugeParts_SexDraw(gauge);
	}
#endif

	if(draw_flag & GAUGE_DRAW_GETBALL){
		GaugeParts_GetBallDraw(gauge);
	}
	
	if(draw_flag & GAUGE_DRAW_STATUS){
		switch(gauge->status){
		default:
		case STATUS_NORMAL:
			GaugeParts_StatusDraw(gauge, GP_NON_STATUS);
			
		#if 0	//レイアウト的に状態異常の時でもゲットマークを消さなくてよくなった 2006.04.19(水)
			if(status_getball == TRUE){
				GaugeParts_GetBallDraw(gauge);
			}
		#endif
			break;
		case STATUS_NEMURI:
			GaugeParts_StatusDraw(gauge, GP_NEMURI);
			break;
		case STATUS_DOKU:
			GaugeParts_StatusDraw(gauge, GP_DOKU);
			break;
		case STATUS_YAKEDO:
			GaugeParts_StatusDraw(gauge, GP_YAKEDO);
			break;
		case STATUS_KOORI:
			GaugeParts_StatusDraw(gauge, GP_KOORI);
			break;
		case STATUS_MAHI:
			GaugeParts_StatusDraw(gauge, GP_MAHI);
			break;
		}
	}
	
	if(draw_flag & (GAUGE_DRAW_SAFARIBALL | GAUGE_DRAW_PARKBALL)){
		GaugeParts_SafariballDraw(gauge, draw_flag);
	}
	
	if(draw_flag & (GAUGE_DRAW_SAFARI_NOKORI | GAUGE_DRAW_PARK_NOKORI)){
		GaugeParts_SafariNokoriDraw(gauge, draw_flag);
	}
}

//--------------------------------------------------------------
/**
 * @brief   ゲージのアクターを削除する
 * @param   gauge		ゲージワークへのポインタ
 */
//--------------------------------------------------------------
void Gauge_ActorDel(GAUGE_WORK *gauge)
{
	if(gauge->sin_tcb != NULL){
		TCB_Delete(gauge->sin_tcb);
		gauge->sin_tcb = NULL;
	}
	
	if(gauge->cap == NULL){
		return;
	}
	CATS_ActorPointerDelete_S(gauge->cap);
	gauge->cap = NULL;
}

//--------------------------------------------------------------
/**
 * @brief   ゲージ矢印のアクターを削除する
 * @param   gauge		ゲージワークへのポインタ
 */
//--------------------------------------------------------------
static void Gauge_ArrowActorDel(GAUGE_WORK *gauge)
{
	if(gauge->arrow_cap == NULL){
		return;
	}
	CATS_ActorPointerDelete_S(gauge->arrow_cap);
	gauge->arrow_cap = NULL;
}

//--------------------------------------------------------------
/**
 * @brief   ゲージのリソースを解放する
 * @param   gauge		ゲージワークへのポインタ
 */
//--------------------------------------------------------------
void Gauge_ResourceFree(GAUGE_WORK *gauge)
{
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	const TCATS_OBJECT_ADD_PARAM_S *obj_head;

	obj_head = Sub_GaugeObjHeadGet(gauge->type);
	
	csp = BattleWorkCATS_SYS_PTRGet(gauge->bw);
	crp = BattleWorkCATS_RES_PTRGet(gauge->bw);

	//リソース解放
	CATS_FreeResourceChar(crp, obj_head->id[CLACT_U_CHAR_RES]);
//	CATS_FreeResourcePltt(crp, PLTTID_GAUGE);
	CATS_FreeResourceCell(crp, obj_head->id[CLACT_U_CELL_RES]);
	CATS_FreeResourceCellAnm(crp, obj_head->id[CLACT_U_CELLANM_RES]);
}

//--------------------------------------------------------------
/**
 * @brief   ゲージ矢印のリソースを解放する
 * @param   gauge		ゲージワークへのポインタ
 */
//--------------------------------------------------------------
static void Gauge_ArrowResourceFree(GAUGE_WORK *gauge)
{
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	const TCATS_OBJECT_ADD_PARAM_S *obj_head;

	obj_head = Sub_ArrowObjHeadGet(gauge->type);
	if(obj_head == NULL){
		return;
	}
	
	csp = BattleWorkCATS_SYS_PTRGet(gauge->bw);
	crp = BattleWorkCATS_RES_PTRGet(gauge->bw);

	//リソース解放
	CATS_FreeResourceChar(crp, obj_head->id[CLACT_U_CHAR_RES]);
//	CATS_FreeResourcePltt(crp, PLTTID_GAUGE);
	CATS_FreeResourceCell(crp, obj_head->id[CLACT_U_CELL_RES]);
	CATS_FreeResourceCellAnm(crp, obj_head->id[CLACT_U_CELLANM_RES]);
}


//--------------------------------------------------------------
/**
 * @brief   ゲージのアクター登録とリソース登録をセットにしたもの
 * @param   gauge		ゲージワークへのポインタ
 */
//--------------------------------------------------------------
void Gauge_ActorResourceSet(GAUGE_WORK *gauge)
{
	const TCATS_OBJECT_ADD_PARAM_S *obj_head;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	PALETTE_FADE_PTR pfd;
	
	csp = BattleWorkCATS_SYS_PTRGet(gauge->bw);
	crp = BattleWorkCATS_RES_PTRGet(gauge->bw);
	pfd = BattleWorkPfdGet(gauge->bw);
	
	obj_head = Sub_GaugeObjHeadGet(gauge->type);

	Gauge_ResourceLoad(csp, crp, pfd, gauge->type);
	gauge->cap = Gauge_ActorSet(csp, crp, gauge->type);
//	Gauge_PartsDraw(gauge, gauge->hp, GAUGE_DRAW_ALL);
	
	//矢印
	Gauge_ArrowResourceLoad(csp, crp, pfd, gauge->type);
//	gauge->arrow_cap = Gauge_ArrowActorSet(csp, crp, gauge->type);
	//矢印の座標セット
	if(gauge->arrow_cap != NULL){
		CATS_ObjectPosSet(gauge->arrow_cap->act, obj_head->x - ArrowOffsetPosX[gauge->type], 
			obj_head->y + ARROW_OFFSET_Y);
	}
}

//--------------------------------------------------------------
/**
 * @brief   ゲージのアクター削除とリソース解放をセットにしたもの
 * @param   gauge		ゲージワークへのポインタ
 */
//--------------------------------------------------------------
void Gauge_ActorResourceDel(GAUGE_WORK *gauge)
{
	//ゲージ本体
	Gauge_ActorDel(gauge);
	Gauge_ResourceFree(gauge);
	//矢印
	Gauge_ArrowActorDel(gauge);
	Gauge_ArrowResourceFree(gauge);
}

//--------------------------------------------------------------
/**
 * @brief   2vs2時、HP表示をバー表示と数値表示に切り替える
 *
 * @param   gauge			ゲージワークへのポインタ
 */
//--------------------------------------------------------------
void Gauge_NumModeChange(GAUGE_WORK *gauge)
{
	const u8 *parts;
	NNSG2dImageProxy * image;
	void *obj_vram;
	
	switch(gauge->type){
	case GAUGE_TYPE_A:
	case GAUGE_TYPE_C:
		break;
	default:
		return;
	}
	
	gauge->num_mode ^= 1;

	obj_vram = G2_GetOBJCharPtr();
	image = CLACT_ImageProxyGet(gauge->cap->act);

	if(gauge->num_mode == TRUE){	//数値モード
		//HPバーの頭と蓋を消去
		parts = GetGaugePartsAdrs(GP_HPBAR_HEAD_CLEAR);
		MI_CpuCopy16(parts, (void*)((u32)obj_vram + HPBarHeadTrans[gauge->type].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			HPBarHeadTrans[gauge->type].size);

		//現在HPと最大HPの間のスラッシュを描画
		parts = GetGaugePartsAdrs(GP_SLASH);
		MI_CpuCopy16(parts, (void*)((u32)obj_vram + HPSlashTrans[gauge->type].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			HPSlashTrans[gauge->type].size);
		
		//数値描画
		Gauge_PartsDraw(gauge, gauge->hp, GAUGE_DRAW_HPNUM | GAUGE_DRAW_HPNUMMAX);
	}
	else{	//バーモード
		//HPバーの頭を描画
		parts = GetGaugePartsAdrs(GP_HPBAR_HEAD);
		MI_CpuCopy16(parts, (void*)((u32)obj_vram + HPBarHeadTrans[gauge->type].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			HPBarHeadTrans[gauge->type].size);

		//HPバーの蓋を描画
		parts = GetGaugePartsAdrs(GP_HPBAR_CAP);
		MI_CpuCopy16(parts, (void*)((u32)obj_vram + HPBarCapTrans[gauge->type].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			HPBarCapTrans[gauge->type].size);
		
		//HPバー描画
		Gauge_PartsDraw(gauge, gauge->hp, GAUGE_DRAW_HPBAR);
	}
}


//--------------------------------------------------------------
/**
 * @brief   HPバーの計算を開始する前に作業用ワーク等の初期化を行う
 *
 * @param   gauge		ゲージワークへのポインタ
 * @param   damage		ダメージ(マイナスでダメージ、プラスなら回復)
 *
 * Gauge_CalcHPを実行する前に必ず呼び出して置く必要があります。
 */
//--------------------------------------------------------------
void Gauge_InitCalcHP(GAUGE_WORK *gauge, int damage)
{
	gauge->hp_work = HP_WORK_INIT_VALUE;
	
	if(gauge->hp + damage < 0){
		damage -= gauge->hp + damage;
	}
	if(gauge->hp + damage > gauge->hpmax){
		damage -= (gauge->hp + damage) - gauge->hpmax;
	}
	
	//-- 旧ゲージ計算ルーチンに合わせるため、正負の逆転などを行う --//
	gauge->damage = -damage;
	if(gauge->hp < 0){
		gauge->hp = 0;
	}
	if(gauge->hp > gauge->hpmax){
		gauge->hp = gauge->hpmax;
	}
}

//--------------------------------------------------------------
/**
 * @brief   HPバーの計算と書き込みを行う
 *
 * @param   gauge		ゲージワークへのポインタ
 *
 * @retval  -1=終了。　-1以外=計算途中の数字(画面に表示する数値)
 *
 * Gauge_InitCalcHPを先に呼んである必要があります。
 */
//--------------------------------------------------------------
s32 Gauge_CalcHP(GAUGE_WORK *gauge)
{
	s32 calc_hp;
	
	calc_hp = GaugeOBJ(gauge, GAUGE_REQ_HP);	//計算＆バー書き込み
	if(calc_hp == -1){
		//計算終了時にゲージワークのhpパラメータを最新の値(ダメージ計算後)で更新しておく
		gauge->hp -= gauge->damage;
		Gauge_PartsDraw(gauge, gauge->hp, GAUGE_DRAW_HPNUM);	//数値書き込み
	}
	else{
		Gauge_PartsDraw(gauge, calc_hp, GAUGE_DRAW_HPNUM);	//数値書き込み
	}
	return calc_hp;
}

//--------------------------------------------------------------
/**
 * @brief   EXPバーの計算を開始する前に作業用ワーク等の初期化を行う
 *
 * @param   gauge		ゲージワークへのポインタ
 * @param   add_exp		加算するEXP値
 *
 * Gauge_CalcEXPを実行する前に必ず呼び出して置く必要があります。
 */
//--------------------------------------------------------------
void Gauge_InitCalcEXP(GAUGE_WORK *gauge, int add_exp)
{
	gauge->exp_work = HP_WORK_INIT_VALUE;

	if(gauge->exp + add_exp < 0){
		add_exp -= gauge->exp + add_exp;
	}
	if(gauge->exp + add_exp > gauge->max_exp){
		add_exp -= (gauge->exp + add_exp) - gauge->max_exp;
	}

	//-- 旧ゲージ計算ルーチンに合わせるため、正負の逆転などを行う --//
	gauge->add_exp = -add_exp;
	if(gauge->exp < 0){
		gauge->exp = 0;
	}
	if(gauge->exp > gauge->max_exp){
		gauge->exp = gauge->max_exp;
	}
}

//--------------------------------------------------------------
/**
 * @brief   EXPバーの計算と書き込みを行う
 *
 * @param   gauge		ゲージワークへのポインタ
 *
 * @retval  -1=終了。　-1以外=計算途中の数字(画面に表示する数値)
 *
 * Gauge_InitCalcEXPを先に呼んである必要があります。
 */
//--------------------------------------------------------------
s32 Gauge_CalcEXP(GAUGE_WORK *gauge)
{
	s32 calc_exp;
	
	calc_exp = GaugeOBJ(gauge, GAUGE_REQ_EXP);
	if(calc_exp == -1){
		//計算終了時にゲージワークのexpパラメータを最新の値(ダメージ計算後)で更新しておく
		gauge->exp -= gauge->add_exp;
	}
	return calc_exp;
}

//--------------------------------------------------------------
/**
 * @brief   矢印アニメ開始
 * @param   gauge		ゲージワークへのポインタ
 */
//--------------------------------------------------------------
void Gauge_AnimeStart(GAUGE_WORK *gauge)
{
	if(gauge->arrow_cap != NULL){
		CLACT_SetAnmFlag(gauge->arrow_cap->act, 1);
		Gauge_ArrowEnableSet(gauge, CATS_ENABLE_TRUE);
	}
	
	if((BattleWorkFightTypeGet(gauge->bw) & FIGHT_TYPE_NO_ARROW_ANIME) == 0){
		Gauge_SinCurveSet(gauge);
	}
}

//--------------------------------------------------------------
/**
 * @brief   矢印アニメ停止
 * @param   gauge		ゲージワークへのポインタ
 */
//--------------------------------------------------------------
void Gauge_AnimeStop(GAUGE_WORK *gauge)
{
	if(gauge->arrow_cap != NULL){
		CLACT_SetAnmFlag(gauge->arrow_cap->act, 0);
		CLACT_AnmFrameSet(gauge->arrow_cap->act, 0);
		Gauge_ArrowEnableSet(gauge, CATS_ENABLE_FALSE);
	}
	
	Gauge_SinCurveStop(gauge);
}

//--------------------------------------------------------------
/**
 * @brief   ゲージのBGプライオリティ変更
 *
 * @param   gauge		ゲージワークへのポインタ
 * @param   bg_pri		BGプライオリティ
 */
//--------------------------------------------------------------
void Gauge_BGPriSet(GAUGE_WORK *gauge, int bg_pri)
{
	if(gauge->cap == NULL){
		return;
	}
	CATS_ObjectBGPriSetCap(gauge->cap, bg_pri);
	if(gauge->arrow_cap != NULL){
		CATS_ObjectBGPriSetCap(gauge->arrow_cap, bg_pri);
	}
}

//--------------------------------------------------------------
/**
 * @brief   ゲージ矢印の表示・非表示セット
 *
 * @param   gauge		ゲージワークへのポインタ
 * @param   enable		CATS_ENABLE_TRUE(表示) or CATS_ENABLE_FALSE(非表示)
 */
//--------------------------------------------------------------
static void Gauge_ArrowEnableSet(GAUGE_WORK *gauge, int enable)
{
	if(gauge->arrow_cap != NULL){
		if((BattleWorkFightTypeGet(gauge->bw) & FIGHT_TYPE_NO_ARROW_ANIME) && enable == CATS_ENABLE_TRUE){
			;		//サファリ、ポケパークなら矢印表示状態にはしない
		}
		else{
			CATS_ObjectEnableCap(gauge->arrow_cap, enable);
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   ゲージの表示・非表示セット
 *
 * @param   gauge		ゲージワークへのポインタ
 * @param   enable		CATS_ENABLE_TRUE(表示) or CATS_ENABLE_FALSE(非表示)
 */
//--------------------------------------------------------------
void Gauge_EnableSet(GAUGE_WORK *gauge, int enable)
{
	if(gauge->cap == NULL){
		return;
	}
	
	CATS_ObjectEnableCap(gauge->cap, enable);
	Gauge_ArrowEnableSet(gauge, enable);
}

//--------------------------------------------------------------
/**
 * @brief   ゲージにオフセットポジションをセットする
 *
 * @param   gauge		ゲージワークへのポインタ
 * @param   x			オフセットX
 * @param   y			オフセットY
 *
 * 通常の定位置からのオフセットになります。
 */
//--------------------------------------------------------------
void Gauge_OffsetPosSet(GAUGE_WORK *gauge, int x, int y)
{
	const TCATS_OBJECT_ADD_PARAM_S *obj_head;
	
	GF_ASSERT(gauge->cap != NULL);

	obj_head = Sub_GaugeObjHeadGet(gauge->type);
	
	CATS_ObjectPosSet(gauge->cap->act, obj_head->x + x, obj_head->y + y);
	if(gauge->arrow_cap != NULL){
		CATS_ObjectPosSet(gauge->arrow_cap->act, 
			obj_head->x + x - ArrowOffsetPosX[gauge->type], obj_head->y + y + ARROW_OFFSET_Y);
	}
}

//--------------------------------------------------------------
/**
 * @brief   ゲージスクロールIN・OUTエフェクトを起動する
 *
 * @param   gauge		ゲージワークへのポインタ
 * @param   in_out		スクロール方向(GAUGE_SCROLL_IN or GAUGE_SCROLL_OUT)
 *
 * エフェクト終了時に、gauge->eff_wait_in_outにTRUEがセットされます
 */
//--------------------------------------------------------------
void Gauge_ScrollEffectSet(GAUGE_WORK *gauge, int in_out)
{
	GF_ASSERT(gauge != NULL);
	GF_ASSERT(gauge->cap != NULL);
	
	gauge->eff_wait_in_out = FALSE;
	
	gauge->in_out_dir = in_out;
	if(in_out == GAUGE_SCROLL_IN){
		switch(gauge->type){
		case GAUGE_TYPE_AA:
		case GAUGE_TYPE_A:
		case GAUGE_TYPE_C:
		case GAUGE_TYPE_SAFARI:
		case GAUGE_TYPE_PARK:
			Gauge_OffsetPosSet(gauge, GAUGE_SCROLL_OUT_OFFSET_X, GAUGE_SCROLL_OUT_OFFSET_Y);
			break;
		default:
			Gauge_OffsetPosSet(gauge, -GAUGE_SCROLL_OUT_OFFSET_X, GAUGE_SCROLL_OUT_OFFSET_Y);
			break;
		}
	}
	else{
		Gauge_OffsetPosSet(gauge, 0, 0);
	}
	TCB_Add(Gauge_ScrollInOut, gauge, TCBPRI_HP_GAUGE_IN_TASK);
}

//--------------------------------------------------------------
/**
 * @brief   ゲージスクロール実動作タスク
 *
 * @param   tcb			TCBへのポインタ
 * @param   work		GAUGE_WORKへのポインタ
 */
//--------------------------------------------------------------
static void Gauge_ScrollInOut(TCB_PTR tcb, void *work)
{
	GAUGE_WORK *gauge = work;
	s16 x, y;
	const TCATS_OBJECT_ADD_PARAM_S *obj_head;
	int end;
	
	end = 0;
	obj_head = Sub_GaugeObjHeadGet(gauge->type);
	CATS_ObjectPosGetCap(gauge->cap, &x, &y);
	switch(gauge->type){
	case GAUGE_TYPE_AA:
	case GAUGE_TYPE_A:
	case GAUGE_TYPE_C:
	case GAUGE_TYPE_SAFARI:
	case GAUGE_TYPE_PARK:
		if(gauge->in_out_dir == GAUGE_SCROLL_IN){
			x -= GAUGE_SCROLL_SP_X;
			if(x < obj_head->x){
				x = obj_head->x;
				end++;
			}
		}
		else{
			x += GAUGE_SCROLL_SP_X;
			if(x > obj_head->x + GAUGE_SCROLL_OUT_OFFSET_X){
				x = obj_head->x + GAUGE_SCROLL_OUT_OFFSET_X;
				end++;
			}
		}
		break;
	default:
		if(gauge->in_out_dir == GAUGE_SCROLL_IN){
			x += GAUGE_SCROLL_SP_X;
			if(x > obj_head->x){
				x = obj_head->x;
				end++;
			}
		}
		else{
			x -= GAUGE_SCROLL_SP_X;
			if(x < obj_head->x - GAUGE_SCROLL_SP_X){
				x = obj_head->x - GAUGE_SCROLL_SP_X;
				end++;
			}
		}
		break;
	}
	CATS_ObjectPosSetCap(gauge->cap, x, y);
	if(gauge->arrow_cap != NULL){
		CATS_ObjectPosSetCap(gauge->arrow_cap, x - ArrowOffsetPosX[gauge->type], 
			y + ARROW_OFFSET_Y);
	}
	
	if(end > 0){
		gauge->eff_wait_in_out = TRUE;
		TCB_Delete(tcb);
		return;
	}
}

//--------------------------------------------------------------
/**
 * @brief   ゲージのデバッグHP表示フラグを反転する
 *
 * @param   gauge		ゲージーワークへのポインタ
 * @param   put			TRUE:表示。　FALSE:非表示
 *
 * PM_DEBUGが有効でない場合は何も処理しません。
 */
//--------------------------------------------------------------
void Gauge_DebugHPPutFlagFlip(GAUGE_WORK *gauge)
{
#ifdef PM_DEBUG
	gauge->debug_hp_put ^= TRUE;
#endif
}




//==============================================================================
//
//	パーツ描画
//
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   ゲージパーツ描画：名前
 * @param   gauge		ゲージワークへのポインタ
 */
//--------------------------------------------------------------
static void GaugeParts_NameDraw(GAUGE_WORK *gauge)
{
	GF_BGL_INI *bgl;
	u8 *buf;
	NNSG2dImageProxy * image;
	GF_BGL_BMPWIN bmpwin;
	MSGDATA_MANAGER *msg_man;
	STRBUF *monsname_p, *monsname_src;
	POKEMON_PARAM *pp;
	POKEMON_PASO_PARAM *ppp;
	WORDSET *wordset;
	
	bgl = BattleWorkGF_BGL_INIGet(gauge->bw);
	msg_man = BattleWorkFightMsgGet(gauge->bw);
	wordset = BattleWorkWORDSETGet(gauge->bw);
	
	//文字列展開
	monsname_p = STRBUF_Create(BUFLEN_GAUGE_POKESELENAME, HEAPID_BATTLE);
	monsname_src = MSGMAN_AllocString(msg_man, TargetPokemonMsg);
	pp = BattleWorkPokemonParamGet(gauge->bw, gauge->client_no, gauge->sel_mons_no);
	ppp = PPPPointerGet(pp);
	WORDSET_RegisterPokeNickName(wordset, 0, ppp);
	WORDSET_ExpandStr(wordset, monsname_p, monsname_src);
	
	//バッファにBMPデータ展開
	GF_BGL_BmpWinObjAdd(bgl, &bmpwin, NAME_SIZE_X, NAME_SIZE_Y, 
		NAME_CHAR_OFFSET, NAME_BACK_COLOR);
	GF_STR_PrintExpand(&bmpwin, FONT_SYSTEM, monsname_p, 0, 0, MSG_NO_PUT, NAME_FONT_COLOR, GAUGE_FONT_MARGIN, 0, NULL);
	buf = bmpwin.chrbuf;
	
	//形成された文字バッファをVRAMに直書き
	{
		void *obj_vram;
		u8 *high, *low;
		
		obj_vram = G2_GetOBJCharPtr();
		image = CLACT_ImageProxyGet(gauge->cap->act);
		high = buf;
		low = &buf[NAME_SIZE_X * 0x20];
		//左側
		MI_CpuCopy16(high, (void*)((u32)obj_vram + NameTrans[gauge->type][0].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			NameTrans[gauge->type][0].size);
		MI_CpuCopy16(low, (void*)((u32)obj_vram + NameTrans[gauge->type][1].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			NameTrans[gauge->type][1].size);
		//右側
		MI_CpuCopy16(&high[NameTrans[gauge->type][0].size], 
			(void*)((u32)obj_vram + NameTrans[gauge->type][2].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			NameTrans[gauge->type][2].size);
		MI_CpuCopy16(&low[NameTrans[gauge->type][1].size], 
			(void*)((u32)obj_vram + NameTrans[gauge->type][3].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			NameTrans[gauge->type][3].size);
	}
	
	//BMPデータ解放
	GF_BGL_BmpWinDel(&bmpwin);
	//文字列バッファ解放
	STRBUF_Delete(monsname_p);
	STRBUF_Delete(monsname_src);
	
#if 0
	//転送
	image = CLACT_ImageProxyGet(gauge->cap->act);
	AddVramTransferManager(
		NNS_GFD_DST_2D_OBJ_CHAR_MAIN,
		image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN],
		buf,
		NAME_BYTE_SIZE
		);
#endif
}

//--------------------------------------------------------------
/**
 * @brief   ゲージパーツ描画：レベル
 * @param   gauge		ゲージワークへのポインタ
 */
//--------------------------------------------------------------
static void GaugeParts_LevelFontDraw(GAUGE_WORK *gauge)
{
	u8 *dest_buf;
	NNSG2dImageProxy * image;
	int numfont_size, i, t, k;
	const u8 *level_buf;
	int gp;
	
	numfont_size = 0x20 * 2;
	if(gauge->sex == PARA_MALE){
		gp = GP_SEX_MALE;
	}
	else if(gauge->sex == PARA_FEMALE){
		gp = GP_SEX_FEMALE;
	}
	else{
		gp = GP_SEX_UNK;
	}
	level_buf = GetGaugePartsAdrs(gp);
	dest_buf = sys_AllocMemory(HEAPID_BATTLE, numfont_size * 2);
	
	//形成された文字バッファをVRAMに直書き
	{
		void *obj_vram;
		u8 *high, *low;
		
		obj_vram = G2_GetOBJCharPtr();
		image = CLACT_ImageProxyGet(gauge->cap->act);
		
		//Vramからメモリ領域に一度コピー
		MI_CpuCopy16((void*)((u32)obj_vram + LvFontTrans[gauge->type][0].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			dest_buf, LvFontTrans[gauge->type][0].size);
		MI_CpuCopy16((void*)((u32)obj_vram + LvFontTrans[gauge->type][1].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			&dest_buf[numfont_size], LvFontTrans[gauge->type][1].size);
		
		//メモリ領域にコピーしたものに数字フォントを書き込み
		k = 0;
		for(t = 0; t < numfont_size; t += 32){
			for(i = 0; i < 16; i++){
				dest_buf[t + 16 + i] = level_buf[k];
				dest_buf[t + i + numfont_size] = level_buf[k + 16];
				k++;
			}
			k += 16;
		}
		
		//出来上がったものをVramへ書き戻す
		high = dest_buf;
		low = &dest_buf[numfont_size];
		MI_CpuCopy16(high, (void*)((u32)obj_vram + LvFontTrans[gauge->type][0].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			LvFontTrans[gauge->type][0].size);
		MI_CpuCopy16(low, (void*)((u32)obj_vram + LvFontTrans[gauge->type][1].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			LvFontTrans[gauge->type][1].size);
	}
	
	//展開領域解放
	sys_FreeMemoryEz(dest_buf);
}

//--------------------------------------------------------------
/**
 * @brief   ゲージパーツ描画：レベル
 * @param   gauge		ゲージワークへのポインタ
 */
//--------------------------------------------------------------
static void GaugeParts_LevelDraw(GAUGE_WORK *gauge)
{
	u8 *level_buf, *dest_buf;
	NNSG2dImageProxy * image;
	int size, i, t, k;
	
	//展開領域確保
	size = LEVEL_KETA_MAX * 0x20;
	level_buf = sys_AllocMemory(HEAPID_BATTLE, size);
	dest_buf = sys_AllocMemory(HEAPID_BATTLE, size * 2);
	MI_CpuFill8(level_buf, LEVEL_BACK_COLOR | (LEVEL_BACK_COLOR << 4), size);
	
	NUMFONT_WriteNumberCGXOnly(BattleWorkGF_BGL_NumFontLVGet(gauge->bw),
		gauge->level, LEVEL_KETA_MAX, NUMFONT_MODE_LEFT, level_buf);
	
	//形成された文字バッファをVRAMに直書き
	{
		void *obj_vram;
		u8 *high, *low;
		
		obj_vram = G2_GetOBJCharPtr();
		image = CLACT_ImageProxyGet(gauge->cap->act);

		//Vramからメモリ領域に一度コピー
		MI_CpuCopy16((void*)((u32)obj_vram + LvTrans[gauge->type][0].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			dest_buf, LvTrans[gauge->type][0].size);
		MI_CpuCopy16((void*)((u32)obj_vram + LvTrans[gauge->type][1].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			&dest_buf[size], LvTrans[gauge->type][1].size);

		//メモリ領域にコピーしたものに数字フォントを書き込み
		k = 0;
		for(t = 0; t < size; t += 32){
			for(i = 0; i < 16; i++){
				dest_buf[t + 16 + i] = level_buf[k];
				dest_buf[t + i + size] = level_buf[k + 16];
				k++;
			}
			k += 16;
		}
		//出来上がったものをVramへ書き戻す
		high = dest_buf;
		low = &dest_buf[size];
		MI_CpuCopy16(high, (void*)((u32)obj_vram + LvTrans[gauge->type][0].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			LvTrans[gauge->type][0].size);
		MI_CpuCopy16(low, (void*)((u32)obj_vram + LvTrans[gauge->type][1].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			LvTrans[gauge->type][1].size);
	}
	
	//展開領域解放
	sys_FreeMemoryEz(level_buf);
	sys_FreeMemoryEz(dest_buf);
}

//--------------------------------------------------------------
/**
 * @brief   ゲージパーツ描画：現在HP
 * @param   gauge		ゲージワークへのポインタ
 * @param   hp			表示するHP
 */
//--------------------------------------------------------------
static void GaugeParts_HPDraw(GAUGE_WORK *gauge, u32 hp)
{
	u8 *alloc_buf;
	NNSG2dImageProxy * image;
	
	//展開領域確保
	alloc_buf = sys_AllocMemory(HEAPID_BATTLE, HP_KETA_MAX * 0x20);
	MI_CpuFill8(alloc_buf, HP_BACK_COLOR | (HP_BACK_COLOR << 4), HP_KETA_MAX * 0x20);
	
	NUMFONT_WriteNumberCGXOnly(BattleWorkGF_BGL_NumFontHPGet(gauge->bw),
		hp, HP_KETA_MAX, NUMFONT_MODE_SPACE, alloc_buf);
	
	//形成された文字バッファをVRAMに直書き
	{
		void *obj_vram;
		u8 *high;
		
		obj_vram = G2_GetOBJCharPtr();
		image = CLACT_ImageProxyGet(gauge->cap->act);
		high = alloc_buf;
		//1枚目書き込み
		MI_CpuCopy16(high, (void*)((u32)obj_vram + HPTrans[gauge->type][0].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			HPTrans[gauge->type][0].size);
		//2枚目書き込み
		MI_CpuCopy16(&high[HPTrans[gauge->type][0].size], 
			(void*)((u32)obj_vram + HPTrans[gauge->type][1].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			HPTrans[gauge->type][1].size);
	}
	
	//展開領域解放
	sys_FreeMemoryEz(alloc_buf);
}

//--------------------------------------------------------------
/**
 * @brief   ゲージパーツ描画：現在HP
 * @param   gauge		ゲージワークへのポインタ
 */
//--------------------------------------------------------------
static void GaugeParts_HPMaxDraw(GAUGE_WORK *gauge)
{
	u8 *alloc_buf;
	NNSG2dImageProxy * image;
	
	//展開領域確保
	alloc_buf = sys_AllocMemory(HEAPID_BATTLE, HP_KETA_MAX * 0x20);
	MI_CpuFill8(alloc_buf, HPMAX_BACK_COLOR | (HPMAX_BACK_COLOR << 4), HP_KETA_MAX * 0x20);
	
	NUMFONT_WriteNumberCGXOnly(BattleWorkGF_BGL_NumFontHPGet(gauge->bw),
		gauge->hpmax, HP_KETA_MAX, NUMFONT_MODE_LEFT, alloc_buf);
	
	//形成された文字バッファをVRAMに直書き
	{
		void *obj_vram;
		u8 *high;
		
		obj_vram = G2_GetOBJCharPtr();
		image = CLACT_ImageProxyGet(gauge->cap->act);
		high = alloc_buf;
		//書き込み
		MI_CpuCopy16(high, (void*)((u32)obj_vram + HPMaxTrans[gauge->type].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			HPMaxTrans[gauge->type].size);
	}
	
	//展開領域解放
	sys_FreeMemoryEz(alloc_buf);
}

//--------------------------------------------------------------
/**
 * @brief   ゲージパーツ描画：性別
 * @param   gauge		ゲージワークへのポインタ
 */
//--------------------------------------------------------------
static void GaugeParts_SexDraw(GAUGE_WORK *gauge)
{
	NNSG2dImageProxy * image;
	const u8 *parts_sex;
	
	if(gauge->sex == PARA_MALE){
		parts_sex = GetGaugePartsAdrs(GP_SEX_MALE);
	}
	else if(gauge->sex == PARA_FEMALE){
		parts_sex = GetGaugePartsAdrs(GP_SEX_FEMALE);
	}
	else{
		parts_sex = GetGaugePartsAdrs(GP_SEX_UNK);
	}
	
	//形成された文字バッファをVRAMに直書き
	{
		void *obj_vram;
		
		obj_vram = G2_GetOBJCharPtr();
		image = CLACT_ImageProxyGet(gauge->cap->act);
		
		//書き込み
		MI_CpuCopy16(parts_sex, (void*)((u32)obj_vram + SexTrans[gauge->type][0].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			SexTrans[gauge->type][0].size);
		MI_CpuCopy16(&parts_sex[0x20], (void*)((u32)obj_vram + SexTrans[gauge->type][1].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			SexTrans[gauge->type][1].size);
	}
}

//--------------------------------------------------------------
/**
 * @brief   ゲージパーツ描画：ゲット済みマーク
 * @param   gauge		ゲージワークへのポインタ
 */
//--------------------------------------------------------------
static void GaugeParts_GetBallDraw(GAUGE_WORK *gauge)
{
	NNSG2dImageProxy * image;
	const u8 *parts_ball;
	
	if(gauge->getball == TRUE){
		parts_ball = GetGaugePartsAdrs(GP_GETBALL);
	}
	else{
		parts_ball = GetGaugePartsAdrs(GP_NON_GETBALL);
	}
	
	//形成された文字バッファをVRAMに直書き
	{
		void *obj_vram;
		
		obj_vram = G2_GetOBJCharPtr();
		image = CLACT_ImageProxyGet(gauge->cap->act);
		
		//書き込み
		MI_CpuCopy16(parts_ball, (void*)((u32)obj_vram + GetBallTrans[gauge->type].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			GetBallTrans[gauge->type].size);
	}
}

//--------------------------------------------------------------
/**
 * @brief   ゲージパーツ描画：麻痺
 * @param   gauge		ゲージワークへのポインタ
 */
//--------------------------------------------------------------
static void GaugeParts_StatusDraw(GAUGE_WORK *gauge, int gp_num)
{
	NNSG2dImageProxy * image;
	const u8 *parts_status;
	
	parts_status = GetGaugePartsAdrs(gp_num);
	
	//形成された文字バッファをVRAMに直書き
	{
		void *obj_vram;
		
		obj_vram = G2_GetOBJCharPtr();
		image = CLACT_ImageProxyGet(gauge->cap->act);
		
		//書き込み
		MI_CpuCopy16(parts_status, (void*)((u32)obj_vram + StatusTrans[gauge->type].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			StatusTrans[gauge->type].size);
	}
}

//--------------------------------------------------------------
/**
 * @brief   ゲージパーツ描画：「サファリボール」
 * @param   gauge		ゲージワークへのポインタ
 * @param   draw_flag
 */
//--------------------------------------------------------------
static void GaugeParts_SafariballDraw(GAUGE_WORK *gauge, u32 draw_flag)
{
	GF_BGL_INI *bgl;
	u8 *buf;
	NNSG2dImageProxy * image;
	GF_BGL_BMPWIN bmpwin;
	MSGDATA_MANAGER *msg_man;
	STRBUF *str_src;
	
	bgl = BattleWorkGF_BGL_INIGet(gauge->bw);
	msg_man = BattleWorkFightMsgGet(gauge->bw);
	
	//文字列展開
	if(draw_flag & GAUGE_DRAW_SAFARIBALL){
		str_src = MSGMAN_AllocString(msg_man, SafariBallMsg);
	}
	else{
		str_src = MSGMAN_AllocString(msg_man, ParkBallMsg);
	}
	
	//バッファにBMPデータ展開
	GF_BGL_BmpWinObjAdd(bgl, &bmpwin, SAFARIBALL_SIZE_X, SAFARIBALL_SIZE_Y, 
		SAFARIBALL_CHAR_OFFSET, SAFARIBALL_BACK_COLOR);
	GF_STR_PrintExpand(&bmpwin, FONT_SYSTEM, str_src, 0, 0, MSG_NO_PUT, SAFARIBALL_FONT_COLOR, GAUGE_FONT_MARGIN, 0, NULL);
	buf = bmpwin.chrbuf;
	
	//形成された文字バッファをVRAMに直書き
	{
		void *obj_vram;
		u8 *high, *low;
		
		obj_vram = G2_GetOBJCharPtr();
		image = CLACT_ImageProxyGet(gauge->cap->act);
		high = buf;
		low = &buf[SAFARIBALL_SIZE_X * 0x20];
		//左側
		MI_CpuCopy16(high, (void*)((u32)obj_vram + SafariballTrans[0].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			SafariballTrans[0].size);
		MI_CpuCopy16(low, (void*)((u32)obj_vram + SafariballTrans[1].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			SafariballTrans[1].size);
		//右側
		MI_CpuCopy16(&high[SafariballTrans[0].size], 
			(void*)((u32)obj_vram + SafariballTrans[2].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			SafariballTrans[2].size);
		MI_CpuCopy16(&low[SafariballTrans[1].size], 
			(void*)((u32)obj_vram + SafariballTrans[3].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			SafariballTrans[3].size);
	}
	
	//BMPデータ解放
	GF_BGL_BmpWinDel(&bmpwin);
	//文字列バッファ解放
	STRBUF_Delete(str_src);
}

//--------------------------------------------------------------
/**
 * @brief   ゲージパーツ描画：「のこり　○○こ」
 * @param   gauge		ゲージワークへのポインタ
 * @param   draw_flag
 */
//--------------------------------------------------------------
static void GaugeParts_SafariNokoriDraw(GAUGE_WORK *gauge, u32 draw_flag)
{
	GF_BGL_INI *bgl;
	u8 *buf;
	NNSG2dImageProxy * image;
	GF_BGL_BMPWIN bmpwin;
	MSGDATA_MANAGER *msg_man;
	STRBUF *nokori_p, *nokori_src;
	WORDSET *wordset;
	
	bgl = BattleWorkGF_BGL_INIGet(gauge->bw);
	msg_man = BattleWorkFightMsgGet(gauge->bw);
	wordset = BattleWorkWORDSETGet(gauge->bw);
	
	//文字列展開
	nokori_p = STRBUF_Create(BUFLEN_GAUGE_SAFARI_NOKORI, HEAPID_BATTLE);
	if(draw_flag & GAUGE_DRAW_SAFARIBALL){
		nokori_src = MSGMAN_AllocString(msg_man, SafariNokoriMsg);
	}
	else{
		nokori_src = MSGMAN_AllocString(msg_man, ParkNokoriMsg);
	}
	WORDSET_RegisterNumber(wordset, 0, gauge->safari_nokori, NOKORI_SAFARI_NUM_KETA, 
		NUMBER_DISPTYPE_SPACE, NUMBER_CODETYPE_DEFAULT);
	WORDSET_ExpandStr(wordset, nokori_p, nokori_src);
	
	//バッファにBMPデータ展開
	GF_BGL_BmpWinObjAdd(bgl, &bmpwin, NOKORI_SIZE_X, NOKORI_SIZE_Y, 
		NOKORI_CHAR_OFFSET, NOKORI_BACK_COLOR);
	GF_STR_PrintExpand(&bmpwin, FONT_SYSTEM, nokori_p, 0, 0, MSG_NO_PUT, NOKORI_FONT_COLOR, GAUGE_FONT_MARGIN, 0, NULL);
	buf = bmpwin.chrbuf;
	
	//形成された文字バッファをVRAMに直書き
	{
		void *obj_vram;
		u8 *high, *low;
		
		obj_vram = G2_GetOBJCharPtr();
		image = CLACT_ImageProxyGet(gauge->cap->act);
		high = buf;
		low = &buf[NOKORI_SIZE_X * 0x20];
		//左側
		MI_CpuCopy16(high, (void*)((u32)obj_vram + NokoriTrans[0].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			NokoriTrans[0].size);
		MI_CpuCopy16(low, (void*)((u32)obj_vram + NokoriTrans[1].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			NokoriTrans[1].size);
		//右側
		MI_CpuCopy16(&high[NokoriTrans[0].size], 
			(void*)((u32)obj_vram + NokoriTrans[2].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			NokoriTrans[2].size);
		MI_CpuCopy16(&low[NokoriTrans[1].size], 
			(void*)((u32)obj_vram + NokoriTrans[3].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			NokoriTrans[3].size);
	}
	
	//BMPデータ解放
	GF_BGL_BmpWinDel(&bmpwin);
	//文字列バッファ解放
	STRBUF_Delete(nokori_p);
	STRBUF_Delete(nokori_src);
	
#if 0
	//転送
	image = CLACT_ImageProxyGet(gauge->cap->act);
	AddVramTransferManager(
		NNS_GFD_DST_2D_OBJ_CHAR_MAIN,
		image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN],
		buf,
		NOKORI_BYTE_SIZE
		);
#endif
}

//--------------------------------------------------------------
/**
 * @brief   ゲージパーツ描画：デバッグ用の数値描画
 * @param   gauge		ゲージワークへのポインタ
 * @param   num			表示する数値
 */
//--------------------------------------------------------------
void GaugeParts_DebugNumDraw(GAUGE_WORK *gauge, u32 num)
{
#ifdef PM_DEBUG
	u8 *alloc_buf;
	NNSG2dImageProxy * image;
	
	if(gauge->cap == NULL){
		return;
	}
	
	//展開領域確保
	alloc_buf = sys_AllocMemory(HEAPID_BATTLE, DEBUG_NUM_KETA_MAX * 0x20);
	MI_CpuFill8(alloc_buf, HP_BACK_COLOR | (HP_BACK_COLOR << 4), DEBUG_NUM_KETA_MAX * 0x20);
	
	NUMFONT_WriteNumberCGXOnly(BattleWorkGF_BGL_NumFontHPGet(gauge->bw),
		num, DEBUG_NUM_KETA_MAX, NUMFONT_MODE_LEFT, alloc_buf);
	
	//形成された文字バッファをVRAMに直書き
	{
		void *obj_vram;
		u8 *high;
		
		obj_vram = G2_GetOBJCharPtr();
		image = CLACT_ImageProxyGet(gauge->cap->act);
		high = alloc_buf;
		//1枚目書き込み
		MI_CpuCopy16(high, (void*)((u32)obj_vram + DebugNumTrans[gauge->type].pos
			+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 
			DebugNumTrans[gauge->type].size);
	}
	
	//展開領域解放
	sys_FreeMemoryEz(alloc_buf);
#endif
}







//==============================================================================
//
//	旧：ゲージ計算ルーチン	(エメラルドから移植)
//
//==============================================================================

//--------------------------------------------------------------
/**
 * @brief   HPゲージのバーの部分を書き込み
 *
 * @param   gauge			ゲージワークへのポインタ
 * @param   req_data		GAUGE_REQ_???
 *
 * @retval  -1=終了。　-1以外=計算途中の数字(画面に表示する数値)
 */
//--------------------------------------------------------------
static s32 GaugeOBJ(GAUGE_WORK *gauge, int req_data)
{
	s32 temp;
	s32 dotto_offset;
	
	//ゲージ計算
	if(req_data == GAUGE_REQ_HP){
		temp = GaugeProc(gauge->hpmax, gauge->hp, gauge->damage, 
			&gauge->hp_work, BAR_HP_CHARMAX, 1);
	}
	else{	//GAUGE_REQ_EXP
		//EXPｹﾞｰｼﾞは計算数値が大きいので、ﾄﾞｯﾄのｵﾌｾｯﾄから何Syncで終わらせるかを決める
		dotto_offset = DottoOffsetCalc(gauge->exp, gauge->add_exp, gauge->max_exp,
				BAR_EXP_CHARMAX);
		if(dotto_offset == 0)
			dotto_offset = 1;
		dotto_offset = abs(gauge->add_exp / dotto_offset);
		temp = GaugeProc(gauge->max_exp, gauge->exp, gauge->add_exp,
				&gauge->exp_work, BAR_EXP_CHARMAX, dotto_offset);
	}
	
	//ゲージ描画
	if(req_data == GAUGE_REQ_HP && gauge->num_mode == TRUE){
		;	//HP数字表示モードならばゲージ描画は行わない
	}
	else{
		PutGaugeOBJ(gauge, req_data);
	}
	
	if(temp == -1){
		if(req_data == GAUGE_REQ_HP){
			gauge->hp_work = 0;
		}
		else{
			gauge->exp_work = 0;
		}
	}
	return temp;
}


//--------------------------------------------------------------
/**
 * @brief   ゲージバー描画
 *
 * @param   gauge		ゲージワークへのポインタ
 * @param   req			GAUGE_REQ_???
 */
//--------------------------------------------------------------
static void PutGaugeOBJ(GAUGE_WORK *gauge, u8 req)
{
	u8 i;
	u8 gauge_chr[BAR_ALL_MAX];
	u8 parts, parts_num;
	u8 put_dot;
	u8 level;
	const u8 *parts_address;
	void *obj_vram;
	NNSG2dImageProxy * image;
	int one_loop;
	
	obj_vram = G2_GetOBJCharPtr();
	image = CLACT_ImageProxyGet(gauge->cap->act);
	
	switch(req){
	case GAUGE_REQ_HP:
		put_dot = PutGaugeProc(gauge->hpmax, gauge->hp, gauge->damage,
			 &gauge->hp_work, gauge_chr, BAR_HP_CHARMAX);

		//ゲージの表示ドット数から色とパーツアドレスを取得
		{
			int dotto_color;
			
			dotto_color = GetGaugeDottoColor(put_dot, GAUGE_HP_DOTTOMAX);
			switch(dotto_color){
			case HP_DOTTO_GREEN:
				parts_num = GP_HPBAR_GREEN;
				break;
			case HP_DOTTO_YELLOW:
				parts_num = GP_HPBAR_YELLOW;
				break;
			case HP_DOTTO_RED:
			default:
				parts_num = GP_HPBAR_RED;
				break;
			}
		}
		parts_address = GetGaugePartsAdrs(parts_num);
		
		one_loop = HPBarTrans[gauge->type][0].size / 0x20;
		for(i = 0; i < BAR_HP_CHARMAX; i++){
			if(i < one_loop){
				MI_CpuCopy16(parts_address + (gauge_chr[i] << 5),
					(void*)((u32)obj_vram + HPBarTrans[gauge->type][0].pos + (i * 0x20)
					+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]),
					0x20);
			}
			else{
				MI_CpuCopy16(parts_address + (gauge_chr[i] << 5),
					(void*)((u32)obj_vram + HPBarTrans[gauge->type][1].pos + ((i-one_loop) * 0x20)
					+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]),
					0x20);
			}
		}
		break;
	
	case GAUGE_REQ_EXP:
		PutGaugeProc(gauge->max_exp, gauge->exp, gauge->add_exp,
				&gauge->exp_work, gauge_chr, BAR_EXP_CHARMAX);
		level = gauge->level;
		if(level == 100){
			for(i = 0; i < BAR_EXP_CHARMAX; i++){
				gauge_chr[i] = 0;
			}
		}
		
		parts_address = GetGaugePartsAdrs(GP_EXP);
		for(i = 0; i < BAR_EXP_CHARMAX; i++){
			if(i < EXPBAR_NEXT_OAM){
				MI_CpuCopy16(parts_address + (gauge_chr[i] << 5),
					(void*)((u32)obj_vram + EXPBAR_FAST_HIGH + (i * 0x20)
					+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]),
					0x20);
			}
			else{
				MI_CpuCopy16(parts_address + (gauge_chr[i] << 5),
					(void*)((u32)obj_vram + EXPBAR_SECOND_HIGH + ((i-EXPBAR_NEXT_OAM) * 0x20)
					+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]),
					0x20);
			}
		}
	#if 0
		for(i = 0; i < BAR_EXP_CHARMAX; i++){
			if(i < 4){
				CpuCopy(
					(void*)(GetGaugePartsAdrs(GP_EXPBAR) + (gauge_chr[i] << 5)),
					((ActWork[gwork[client_no].actno].oamData.CharNo +0x24 + i) << 5)
					+ OBJ_MODE0_VRAM, 0x20, 32);
			}
			else{
				CpuCopy(
					(void*)(GetGaugePartsAdrs(GP_EXPBAR) + (gauge_chr[i] << 5)),
					((ActWork[gwork[client_no].actno].oamData.CharNo +0x60 + i-4) << 5)
					+ OBJ_MODE0_VRAM, 0x20, 32);
			}
		}
	#endif
		break;
	}
}

//--------------------------------------------------------------
/**
 * @brief   ゲージバー計算
 *
 * @param   MaxHP		最大HP
 * @param   NowHP		現在HP(計算前のHP)
 * @param   beHP		ダメージ(-でダメージ、+なら回復)
 * @param   HP_Work		作業用ワーク
 * @param   GaugeMax	ゲージのキャラクタ数
 * @param   add_dec		ｹﾞｰｼﾞを加減算していく値 GaugeDottoがGaugeMax以下の場合は無視する
 *
 * @retval  -1 = 終了	それ以外：計算途中の数字(画面に出す数値)
 */
//--------------------------------------------------------------
static s32 GaugeProc(s32 MaxHP, s32 NowHP, s32 beHP, s32 *HP_Work, u8 GaugeMax, u16 add_dec)
{
	s32 endHP;	//2002.09.14(土)
	s32 ret;
	u8 GaugeMaxDot;
	s32 add_hp;
	
	GaugeMaxDot = GaugeMax * GAUGE_DOTTO;
	
	//-- HP_WorkがHP_WORK_INIT_VALUEの時は初回なのでワークを初期化 --//
	if(*HP_Work == HP_WORK_INIT_VALUE){
		if(MaxHP < GaugeMaxDot){
			*HP_Work = NowHP << 8;
		}
		else{
			*HP_Work = NowHP;
		}
	}

	//-- 終了ﾁｪｯｸ --//
	endHP = NowHP - beHP;
	if(endHP < 0)
		endHP = 0;
	else if(endHP > MaxHP)
		endHP = MaxHP;
	
	if(MaxHP < GaugeMaxDot){			//↓少数部分もﾁｪｯｸ
		if(endHP == (*HP_Work >> 8) && (*HP_Work & 0xff) == 0)
			return (-1);
	}
	else{
		if(endHP == *HP_Work)
			return (-1);
	}
	//-- 終了ﾁｪｯｸ終了 --//
	
	if(MaxHP < GaugeMaxDot){
		add_hp = MaxHP * 0x100 / GaugeMaxDot;
		if(beHP < 0){	//ｹﾞｰｼﾞ回復
			*HP_Work += add_hp;
			ret = *HP_Work >> 8;
			if(ret >= endHP){	//少数を扱っているのでｵｰﾊﾞｰﾌﾛｰﾁｪｯｸ
				*HP_Work = endHP << 8;
				ret = endHP;
			}
		}
		else{					//ｹﾞｰｼﾞ減少
			*HP_Work -= add_hp;
			ret = *HP_Work >> 8;
			if((*HP_Work & 0xff) > 0)	//少数部分があるなら少数繰り上げで表示
				ret++;
			if(ret <= endHP){	//少数を扱っているのでｵｰﾊﾞｰﾌﾛｰﾁｪｯｸ
				*HP_Work = endHP << 8;
				ret = endHP;
			}
		}
	}
	else{
		if(beHP < 0){		//ｹﾞｰｼﾞ回復
			*HP_Work += add_dec;
			if(*HP_Work > endHP)
				*HP_Work = endHP;
		}
		else{				//ｹﾞｰｼﾞ減少
			*HP_Work -= add_dec;
			if(*HP_Work < endHP)
				*HP_Work = endHP;
		}
		ret = *HP_Work;
	}
	return ret;
}

//--------------------------------------------------------------
/**
 * @brief   ゲージ表示計算
 *
 * @param   MaxHP		最大HP
 * @param   NowHP		現在HP(計算前のHP)
 * @param   beHP		ダメージ(-でダメージ、+なら回復)
 * @param   HP_Work		作業用ワーク
 * @param   gauge_chr	ゲージ表示結果代入先(GaugeMax分の配列要素数が必要)
 * @param   GaugeMax	ゲージのキャラクタ数
 *
 * @retval  表示するドット数
 *
 * gauge_chrに入る値は、0:空っぽのｹﾞｰｼﾞ  1:1ﾄﾞｯﾄのｹﾞｰｼﾞ 2:2ﾄﾞｯﾄのｹﾞｰｼﾞ ･･･ 8:8ﾄﾞｯﾄ(満ﾀﾝ)のｹﾞｰｼﾞ
 */
//--------------------------------------------------------------
static u8 PutGaugeProc(s32 MaxHP, s32 NowHP, s32 beHP, s32 *HP_Work, u8 *gauge_chr, u8 GaugeMax)
{
	int i;
	u32 GaugeMaxDot;
	u32 put_dot, dot_ret;		//表示するﾄﾞｯﾄ数
	s32 AfterHP;
	
	AfterHP = NowHP - beHP;
	if(AfterHP < 0){
		AfterHP = 0;
	}
	else if(AfterHP > MaxHP){
		AfterHP = MaxHP;
	}

	GaugeMaxDot = GAUGE_DOTTO * GaugeMax;
	for(i = 0; i < GaugeMax; i++){	//空白ｹﾞｰｼﾞで初期化
		gauge_chr[i] = 0;
	}

	//※※ここのドット取得の計算式を変更したらGetNumDottoの計算式も変更すること!!
	if(MaxHP < GaugeMaxDot){	// by 2002.07.11(木) matsuda
		put_dot = (*HP_Work * GaugeMaxDot / MaxHP) >> 8;
	}
	else{
		put_dot = *HP_Work * GaugeMaxDot / MaxHP;
	}
	dot_ret = put_dot;
	//ﾄﾞｯﾄ計算では0でも、実際のHPが1以上あるなら1ﾄﾞｯﾄのｹﾞｰｼﾞを表示する
	if(put_dot == 0 && AfterHP > 0){
		gauge_chr[0] = 1;
		dot_ret = 1;
	}else{
		for(i = 0; i < GaugeMax; i++){
			if(put_dot >= GAUGE_DOTTO){
				gauge_chr[i] = 8;
				put_dot -= GAUGE_DOTTO;
			}
			else{
				gauge_chr[i] = put_dot;
				break;	//ﾄﾞｯﾄが尽きたので抜ける
			}
		}
	}
	return dot_ret;
}

//--------------------------------------------------------------
/**
 * @brief   ｹﾞｰｼﾞ計算前と計算後の最終的なﾄﾞｯﾄの差分を求める
 *
 * @param   nowHP		現在HP(計算前のHP)
 * @param   beHP		ダメージ(-でダメージ、+なら回復)
 * @param   MaxHP		最大HP
 * @param   GaugeMax	ゲージのキャラクタ数
 *
 * @retval  ドット差分
 */
//--------------------------------------------------------------
static u32 DottoOffsetCalc(s32 nowHP, s32 beHP, s32 MaxHP, u8 GaugeMax)
{
	s8 now_dotto, end_dotto;
	u8 GaugeMaxDot;
	s32 endHP;
	
	GaugeMaxDot = GaugeMax * GAUGE_DOTTO;

	endHP = nowHP - beHP;
	if(endHP < 0)
		endHP = 0;
	else if(endHP > MaxHP)
		endHP = MaxHP;
	now_dotto = nowHP * GaugeMaxDot / MaxHP;
	end_dotto = endHP * GaugeMaxDot / MaxHP;
	return (abs(now_dotto - end_dotto));
}

//--------------------------------------------------------------
/**
 * @brief   指定パーツのグラフィックアドレスを取得する
 * @param   parts_num		パーツ番号
 * @retval  パーツのグラフィックアドレス
 */
//--------------------------------------------------------------
static const u8 * GetGaugePartsAdrs(int parts_num)
{
	return &gage_parts[parts_num * 0x20];
}

//--------------------------------------------------------------
/**
 * @brief   クライアントタイプからゲージタイプを取り出す
 * @param   client_type		クライアントタイプ
 * @retval  ゲージタイプ
 */
//--------------------------------------------------------------
u8 Gauge_TypeGet(int client_type, u32 fight_type)
{
	switch(client_type){
	case CLIENT_TYPE_AA:
		if(fight_type & FIGHT_TYPE_POKE_PARK){
			return GAUGE_TYPE_PARK;
		}
		if(fight_type & FIGHT_TYPE_SAFARI){
			return GAUGE_TYPE_SAFARI;
		}
		return GAUGE_TYPE_AA;
	case CLIENT_TYPE_BB:
		return GAUGE_TYPE_BB;
	case CLIENT_TYPE_A:
		return GAUGE_TYPE_A;
	case CLIENT_TYPE_B:
		return GAUGE_TYPE_B;
	case CLIENT_TYPE_C:
		return GAUGE_TYPE_C;
	case CLIENT_TYPE_D:
		return GAUGE_TYPE_D;
	default:
		GF_ASSERT(0 && "用意されていないクライアントタイプが渡されています");
		return NULL;
	}
	return 0;
}

//--------------------------------------------------------------
/**
 * @brief   ゲージタイプからゲージ本体のアクターヘッダポインタを取得する
 * @param   gauge_type		ゲージタイプ
 * @retval  アクターヘッダポインタ
 */
//--------------------------------------------------------------
static const TCATS_OBJECT_ADD_PARAM_S * Sub_GaugeObjHeadGet(u8 gauge_type)
{
	const TCATS_OBJECT_ADD_PARAM_S *obj_head;

	//リソース読み込み
	switch(gauge_type){
	case GAUGE_TYPE_AA:
		obj_head = &GaugeObjParam_aa;
		break;
	case GAUGE_TYPE_BB:
		obj_head = &GaugeObjParam_bb;
		break;
	case GAUGE_TYPE_A:
		obj_head = &GaugeObjParam_a;
		break;
	case GAUGE_TYPE_B:
		obj_head = &GaugeObjParam_b;
		break;
	case GAUGE_TYPE_C:
		obj_head = &GaugeObjParam_c;
		break;
	case GAUGE_TYPE_D:
		obj_head = &GaugeObjParam_d;
		break;
	case GAUGE_TYPE_SAFARI:
	case GAUGE_TYPE_PARK:
		obj_head = &GaugeObjParam_Safari;
		break;
	default:
		GF_ASSERT(0 && "用意されていないゲージタイプが渡されています");
		return NULL;
	}
	return obj_head;
}

//--------------------------------------------------------------
/**
 * @brief   ゲージタイプから矢印のアクターヘッダポインタを取得する
 * @param   gauge_type		ゲージタイプ
 * @retval  アクターヘッダポインタ(矢印が必要ないタイプの場合はNULL)
 */
//--------------------------------------------------------------
static const TCATS_OBJECT_ADD_PARAM_S * Sub_ArrowObjHeadGet(u8 gauge_type)
{
	const TCATS_OBJECT_ADD_PARAM_S *obj_head;

	//リソース読み込み
	switch(gauge_type){
	case GAUGE_TYPE_AA:
	case GAUGE_TYPE_A:
	case GAUGE_TYPE_C:
	case GAUGE_TYPE_SAFARI:
	case GAUGE_TYPE_PARK:
		obj_head = &ArrowParam_aa;
		break;
	case GAUGE_TYPE_BB:		//敵側は矢印必要なし
	case GAUGE_TYPE_B:
	case GAUGE_TYPE_D:
		return NULL;
	default:
		GF_ASSERT(0 && "用意されていないゲージタイプが渡されています");
		return NULL;
	}
	return obj_head;
}





//==============================================================================
//
//	エフェクト関連：レベルアップ
//
//==============================================================================
///ゲージレベルアップ：EVY加算値
#define GAUGE_LEVELUP_ADD_EVY		(4)
///ゲージレベルアップ：カラー変更開始位置(カラー単位)
#define GAUGE_LEVELUP_COLOR_NO		(0xf)
///ゲージレベルアップ：カラー変更する色の数
#define GAUGE_LEVELUP_COLOR_NUM		(1)
///ゲージレベルアップ：変更後のカラー
#define GAUGE_LEVELUP_COLOR			(0x73a5)

///ゲージレベルアップエフェクト用構造体
typedef struct{
	GAUGE_WORK *gauge;		///<ゲージワークへのポインタ
	u8 *end_flag;			///<終了後のフラグをセットするワークへのポインタ
	u8 seq;					///<シーケンス番号
	u8 pal_no;				///<パレット番号
	s8 evy;					///<現在EVY値
}GAUGE_LEVELUP_EFF_WORK;

//--------------------------------------------------------------
/**
 * @brief   ゲージレベルアップエフェクト開始
 *
 * @param   gauge			ゲージワークへのポインタ
 * @param   end_flag		終了フラグをセットするワークへのポインタ
 *
 * エフェクトが終了するとend_flagに渡したワークにTRUEがセットされます
 */
//--------------------------------------------------------------
void Gauge_LevelUpEffectStart(GAUGE_WORK *gauge, u8 *end_flag)
{
	GAUGE_LEVELUP_EFF_WORK *level_eff;
	
	*end_flag = FALSE;
	
	level_eff = sys_AllocMemory(HEAPID_BATTLE, sizeof(GAUGE_LEVELUP_EFF_WORK));
	MI_CpuClear8(level_eff, sizeof(GAUGE_LEVELUP_EFF_WORK));
	
	level_eff->gauge = gauge;
	level_eff->end_flag = end_flag;
	
	TCB_Add(GaugeLevelUpEffTask, level_eff, TCBPRI_GAUGE_LEVELUP_EFF);
}

//--------------------------------------------------------------
/**
 * @brief   ゲージレベルアップエフェクト：メインタスク
 * @param   tcb			TCBへのポインタ
 * @param   work		GAUGE_LEVELUP_EFF_WORK
 */
//--------------------------------------------------------------
static void GaugeLevelUpEffTask(TCB_PTR tcb, void *work)
{
	GAUGE_LEVELUP_EFF_WORK *level_eff = work;
	CATS_RES_PTR crp;
	int pal_no;
	PALETTE_FADE_PTR pfd;
	
	crp = BattleWorkCATS_RES_PTRGet(level_eff->gauge->bw);
	pfd = BattleWorkPfdGet(level_eff->gauge->bw);
	
	switch(level_eff->seq){
	case 0:
		pal_no = CATS_PlttID_NoGet(crp, PLTTID_GAUGE_EFF, NNS_G2D_VRAM_TYPE_2DMAIN);
		CATS_ObjectPaletteSetCap(level_eff->gauge->cap, pal_no);
		level_eff->pal_no = pal_no;
		
		level_eff->seq++;
		//break;
		
	case 1:
		level_eff->evy += GAUGE_LEVELUP_ADD_EVY;
		if(level_eff->evy >= 16){
			level_eff->evy = 16;
			level_eff->seq++;
		}
		SoftFadePfd(pfd, FADE_MAIN_OBJ, level_eff->pal_no * 16 + GAUGE_LEVELUP_COLOR_NO, 
			GAUGE_LEVELUP_COLOR_NUM, level_eff->evy, GAUGE_LEVELUP_COLOR);
		break;
	case 2:
		level_eff->evy -= GAUGE_LEVELUP_ADD_EVY;
		if(level_eff->evy <= 0){
			level_eff->evy = 0;
			level_eff->seq++;
		}
		SoftFadePfd(pfd, FADE_MAIN_OBJ, level_eff->pal_no * 16 + GAUGE_LEVELUP_COLOR_NO, 
			GAUGE_LEVELUP_COLOR_NUM, level_eff->evy, GAUGE_LEVELUP_COLOR);
		break;
	
	default:
		pal_no = CATS_PlttID_NoGet(crp, PLTTID_GAUGE, NNS_G2D_VRAM_TYPE_2DMAIN);
		CATS_ObjectPaletteSetCap(level_eff->gauge->cap, pal_no);

		(*(level_eff->end_flag)) = TRUE;

		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		return;
	}
}





//==============================================================================
//
//	エフェクト関連：特定のゲージのカラーを暗くする
//
//==============================================================================
///ゲージの色を黒色にした時のEVY値
#define GAUGE_COLOR_BACK_EVY		(8)

//--------------------------------------------------------------
/**
 * @brief   ゲージの色を黒色にする
 * @param   gauge		ゲージワークへのポインタ
 */
//--------------------------------------------------------------
void Gauge_ColorBlackSet(GAUGE_WORK *gauge)
{
#if 1		//色変えはしなくなった 2006.04.11(火)
	return;
#else
	CATS_RES_PTR crp;
	int pal_no;
	PALETTE_FADE_PTR pfd;
	
	if(gauge == NULL){
		return;
	}
	
	crp = BattleWorkCATS_RES_PTRGet(gauge->bw);
	pfd = BattleWorkPfdGet(gauge->bw);
	
	pal_no = CATS_PlttID_NoGet(crp, PLTTID_GAUGE_EFF, NNS_G2D_VRAM_TYPE_2DMAIN);
	SoftFadePfd(pfd, FADE_MAIN_OBJ, pal_no * 16, 16, GAUGE_COLOR_BACK_EVY, 0x0000);
	CATS_ObjectPaletteSetCap(gauge->cap, pal_no);
#endif
}

//--------------------------------------------------------------
/**
 * @brief   ゲージの色を元に戻した
 * @param   gauge		ゲージワークへのポインタ
 */
//--------------------------------------------------------------
void Gauge_ColorNormalSet(GAUGE_WORK *gauge)
{
#if 1	//色変えはしなくなった 2006.04.11(火)
	return;
#else
	CATS_RES_PTR crp;
	int pal_no;
	PALETTE_FADE_PTR pfd;

	if(gauge == NULL){
		return;
	}
	
	crp = BattleWorkCATS_RES_PTRGet(gauge->bw);
	pfd = BattleWorkPfdGet(gauge->bw);
	
	pal_no = CATS_PlttID_NoGet(crp, PLTTID_GAUGE_EFF, NNS_G2D_VRAM_TYPE_2DMAIN);
	SoftFadePfd(pfd, FADE_MAIN_OBJ, pal_no * 16, 16, 0, 0x0000);
	
	pal_no = CATS_PlttID_NoGet(crp, PLTTID_GAUGE, NNS_G2D_VRAM_TYPE_2DMAIN);
	CATS_ObjectPaletteSetCap(gauge->cap, pal_no);
#endif
}

//--------------------------------------------------------------
/**
 * @brief   ゲージのSinカーブエフェクトをセットする
 * @param   gauge		ゲージワークへのポインタ
 */
//--------------------------------------------------------------
void Gauge_SinCurveSet(GAUGE_WORK *gauge)
{
	if(gauge->sin_tcb != NULL){
		return;
	}
	
	gauge->sin_sec = 0;
	gauge->sin_tcb = TCB_Add(GaugeSinCurveMain, gauge, TCBPRI_HP_GAUGE_SIN_CURVE);
}

//--------------------------------------------------------------
/**
 * @brief   ゲージのSinカーブエフェクトを停止させる
 * @param   gauge		ゲージワークへのポインタ
 */
//--------------------------------------------------------------
void Gauge_SinCurveStop(GAUGE_WORK *gauge)
{
	if(gauge->sin_tcb != NULL){
		TCB_Delete(gauge->sin_tcb);
		gauge->sin_tcb = NULL;
	}
	gauge->sin_sec = 0;
	Gauge_OffsetPosSet(gauge, 0, 0);
}

//--------------------------------------------------------------
/**
 * @brief   ゲージのSinカーブメイン動作
 * @param   tcb			TCBへのポインタ
 * @param   work		ゲージワークへのポインタ
 */
//--------------------------------------------------------------
static void GaugeSinCurveMain(TCB_PTR tcb, void *work)
{
	GAUGE_WORK *gauge = work;
	int offset_y;
	
	gauge->sin_sec += GAUGE_SIN_SEC_ADD;
	if(gauge->sin_sec >= 360){
		gauge->sin_sec -= 360;
	}
	
	offset_y = FX_Mul(Sin360(gauge->sin_sec), GAUGE_SIN_FURIHABA_Y) / FX32_ONE;
	Gauge_OffsetPosSet(gauge, 0, offset_y);//MATH_ABS(offset_y));
}

