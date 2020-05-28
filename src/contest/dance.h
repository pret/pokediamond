//==============================================================================
/**
 * @file	dance.h
 * @brief	ダンス部門のヘッダ
 * @author	matsuda
 * @date	2005.12.10(土)
 */
//==============================================================================
#ifndef __DANCE_H__
#define __DANCE_H__

#include "system/procsys.h"
#include "battle/battle_common.h"
#include "system/buflen.h"
#include "contest/contest.h"
#include "system/softsprite.h"
#include "system/fontproc.h"
#include "system/msgdata.h"
#include "system/gra_tool.h"
#include "system/wordset.h"
#include "system/clact_tool.h"
#include "contest_order.h"
#include "system/fontoam.h"
#include "system/particle.h"

#include "adv_tool.h"
#include "dance_snd_def.h"



//==============================================================================
//	定数定義
//==============================================================================
///サブ画面のサーフェース位置
#define DANCE_SUB_ACTOR_DISTANCE		(256 * FX32_ONE)

//--------------------------------------------------------------
//	ゲームバランスパラメータ
//--------------------------------------------------------------
///1分間にかかるフレーム数
#define ONE_MIN_FRAME		(60 * 30)
///鳴っている曲のメインの小節数
#define TEMPO_BASE_ONPU		(16)
///1小節にかけるフレーム数を求める時に行う固定小数化のための乗算分
#define ONE_TEMPO_CALC_DECIMAL		(10000)
///ダンスの小節数(裏拍含む)
#define DANCE_BEAT			(TEMPO_BASE_ONPU * 2)

///1度のダンスで実行出来る最大ダンス回数
#define DANCING_MAX				(8)
///メインダンサーの履歴を取る数
#define DANCING_RECORD_MAX		(DANCING_MAX)
///ダンスアニメーションの予約バッファ数
#define DANCE_STEP_REQUEST_MAX	(DANCE_BEAT)

///評価パネルの移動速度Y
#define REVIEW_PANEL_SPEED_Y		(-4)

///4分音符一つ分のtick数
#define QUARTER_NOTE_TICK			(48)

///tickとmusic_vcountがずれ始めた時、何フレームずれたら補正を入れるか
///(数値を大きくするほど、広範囲に渡ってずれが許容される瞬間を探す。
/// その分、ずれている時間は自動的に許容されるまでは長くなる。
/// 但し、2フレーム以上のずれがある場合は、ここで指定しているフレームに関係なく
/// 補正が入るので、ずれているのは1フレームだけである。
/// 逆に値を小さくすると、ずれ始めてもすぐにtickの値で補正されるので、
/// 曲とタイミングのずれているフレーム数は少なくなるが、tickのカウンタの性質上、
/// 188tick, 188tick, 190tick... のように同じ数字が2回続いた後、1個飛ばして数字が
/// 上がる場合がある。
#define MUSIC_VCOUNT_HOSEI_COUNT	(18)


///タッチ後に次のタッチチェックが出来るまでのウェイトに減算させるウェイト値
///(4分音符の長さ丁度の期間を押せなくすると、次の4分音符の前後が押しずらいので、
/// 少しだけウェイトを短くする為の減算値)
#define DANCE_TOUCH_WAIT_SUB_OFFSET		(2)

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///バックダンサーに足しこむプライオリティ
#define DANCE_BACK_IMC_ADD_PRI		(-100)

///ポケモン定位置Z(メインダンサー)
#define DANCE_POKEPOS_Z_MAIN		(APPEAR_Z_TYPE_AA)
///ポケモン定位置Z(バックダンサー)
#define DANCE_POKEPOS_Z_SUB			(DANCE_POKEPOS_Z_MAIN - 0x80)

///メインダンサーのポケモン拡縮率(XY共通)
#define DANCE_POKEAFF_MAIN		(0x0100)
///バックダンサーのポケモン拡縮率(XY共通)
#define DANCE_POKEAFF_BACK		(0x00c0)	//(0x0080)

///曲進行バーの横幅数(キャラクタ単位)
#define MUSIC_BAR_NUM		(32)
///曲進行バー1つが持つ横幅ドット数
#define MUSIC_BAR_ONE_LEN	(8)
///曲進行バー1つが持つ横幅ドット数
#define MUSIC_BAR_LEN		(MUSIC_BAR_ONE_LEN * MUSIC_BAR_NUM)

///音符アクターを同時に出せる最大数(メインダンサー＋バックダンサー)
#define ONPU_ACTOR_MAX		((DANCE_BEAT / 2) * BREEDER_MAX + 4)	//+4は保険で多めに

///評価パネルアクターを同時に出せる最大数
#define REVIEW_ACTOR_MAX		(3)

///評価タイプ
enum{
	REVIEW_TYPE_EXCELLENT,
	REVIEW_TYPE_GOOD,
	REVIEW_TYPE_FAILED,
	
	REVIEW_TYPE_MAX,
};

///ダンス部門メイン画面で使用するフォントOAMの最大数
#define DANCE_FONTOAM_MAX_MAIN	(REVIEW_TYPE_MAX * REVIEW_ACTOR_MAX)

///ブリーダー1人が同時に出せる星エフェクト最大数
#define STAR_EFF_MAX			(16)
///星の数を増やして行く基準のポイント
#define STAR_LVUP_POINT			(2)

//--------------------------------------------------------------
//	ローテーション位置
//--------------------------------------------------------------
///ローテーション位置
enum{
	DANCE_ROTATION_POS_A,		///<メイン
	DANCE_ROTATION_POS_B,		///<次に踊るポケモン
	DANCE_ROTATION_POS_C,
	DANCE_ROTATION_POS_D,
};

//--------------------------------------------------------------
//	バッファ
//--------------------------------------------------------------
///文字列バッファのサイズ
#define DANCE_MESSAGE_BUF_SIZE	(2*160)		///<暫定で１６０文字分

///パレット中間バッファのサイズ
#define DANCE_MIDDLE_PALWORK_SIZE	(0x200)

//--------------------------------------------------------------
//	フレーム番号
//--------------------------------------------------------------
///ウィンドウ・メッセージ面のフレーム
#define DANCE_FRAME_WIN				(GF_BGL_FRAME1_M)
///エフェクト面のフレーム
#define DANCE_FRAME_EFF				(GF_BGL_FRAME2_M)
///背景面のフレーム
#define DANCE_FRAME_BACKGROUND		(GF_BGL_FRAME3_M)

///<BG番号：ウィンドウ
#define DANCE_BGNO_WIN			(1)
///<BG番号：エフェクト
#define DANCE_BGNO_EFF			(2)
///<BG番号：背景
#define DANCE_BGNO_BACKGROUND	(3)

///<3D面のBGプライオリティ
#define DANCE_3DBG_PRIORITY		(2)
///ウィンドウ面のBGプライオリティ
#define DANCE_BGPRI_WIN			(0)
///エフェクト面のBGプライオリティ
#define DANCE_BGPRI_EFF			(0)
///背景面のBGプライオリティ
#define DANCE_BGPRI_BACKGROUND	(3)


//--------------------------------------------------------------
//	BMPウィンドウ
//--------------------------------------------------------------
enum{
	DANCE_BMPWIN_TALK,		///<会話ウィンドウ
	DANCE_BMPWIN_PANEL,		///<看板メッセージ
	
	DANCE_BMPWIN_MAX,
};

//--------------------------------------------------------------
//	会話ウィンドウ
//--------------------------------------------------------------
///会話ウィンドウのキャラクタ転送オフセット(キャラクタ単位)
#define DANCE_TALKWIN_CGX_OFFSET	(1)
///会話ウィンドウ背景色
#define DANCE_TALKWIN_BACK_COLOR	(15)
///会話ウィンドウのパレット番号
#define DANCE_TALKWIN_PALNO		(14)

//--------------------------------------------------------------
//	エフェクト面
//--------------------------------------------------------------
///どんちょうのパレット番号
#define DONTYOU_PALNO			(0xc)

///ダンスした時に被せる半透明BGのパレット番号
#define DANCE_ALPHA_BG_PALNO	(DONTYOU_PALNO)

//--------------------------------------------------------------
//	譜面
//--------------------------------------------------------------
///譜面の色タイプ
typedef enum{
	FUMENCOLOR_MAIN,		///<メインダンサーの譜面色
	FUMENCOLOR_BACK,		///<バックダンサーの譜面色
	FUMENCOLOR_NULL,		///<指定なし
}FUMENCOLOR_TYPE;

///メインダンサーの譜面のカラー位置
#define FUMEN_MAIN_COLOR_POS		(2 * 16 + 9)
///メインダンサーの譜面で使用しているカラー数
#define FUMEN_MAIN_COLOR_NUM		(2)

///メインダンサーの譜面のパレット番号
#define FUMEN_PALNO_MAIN			(4)
///バックダンサーの譜面のパレット番号
#define FUMEN_PALNO_BACK			(3)
///曲進行バーのパレット番号
#define FUMEN_PALNO_MUSICBAR		(2)

//--------------------------------------------------------------
//	フェード
//--------------------------------------------------------------
///ダンス部門開始時にかかっているハードフェードの対象プレーン
#define DANCE_OPENING_BRIGHTNESS_PALNE		(GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_BD | GX_BLEND_PLANEMASK_OBJ)
///ダンス部門開始時にかかっているハードフェードの輝度(16 ～ -16)
#define DANCE_OPENING_BRIGHTNESS_EVY		(-6)

///画面全体フェード用のBGフェードビット(会話ウィンドウ、フォント、ローカライズ用を除く)
#define DANCE_DISP_BG_FADE_BIT			(0x1fff ^ ((1<<FUMEN_PALNO_MAIN) | (1<<FUMEN_PALNO_BACK) | (1 << FUMEN_PALNO_MUSICBAR)))
///画面全体フェード用のOBJフェードビット(通信アイコン、ローカライズ用を除く)
#define DANCE_DISP_OBJ_FADE_BIT			(0x3fff)
///画面全体フェード用のBGカラー数(会話ウィンドウ、フォント、ローカライズ用を除く)
#define DANCE_DISP_BG_COLOR_NUM		(16 * 13)
///画面全体フェード用のOBJカラー数(通信アイコン、ローカライズ用を除く)
#define DANCE_DISP_OBJ_COLOR_NUM	(16 * 14)

//--------------------------------------------------------------
//	ダンスした時に被せる半透明BG
//--------------------------------------------------------------
///ダンス実行半透明BGタイプ
enum{
	DANCE_BGALPHA_TYPE_NULL,	///<何もなし(カラーパレットの0位置(抜き色)分のダミー
	DANCE_BGALPHA_TYPE_UP,		///<半透明BG：上
	DANCE_BGALPHA_TYPE_DOWN,	///<半透明BG：下
	DANCE_BGALPHA_TYPE_LEFT,	///<半透明BG：左
	DANCE_BGALPHA_TYPE_RIGHT,	///<半透明BG：右
	DANCE_BGALPHA_TYPE_FAILED,	///<半透明BG：失敗
};

///ダンス実行半透明BGの第1対象面
#define DANCE_BGALPHA_PLANE_1		(GX_BLEND_PLANEMASK_BG2)
///ダンス実行半透明BGの第2対象面
#define DANCE_BGALPHA_PLANE_2		(GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BD)

//--------------------------------------------------------------
//	パーティクル
//--------------------------------------------------------------
///ダンスパーティクルのデフォルトZ位置
#define DANCE_PARTICLE_DEFAULT_Z		(-5248)
///パーティクル絶対座標：左端
#define DANCE_PARTICLE_LEFT				(-28600)
///パーティクル絶対座標：右端
#define DANCE_PARTICLE_RIGHT			(-DANCE_PARTICLE_LEFT)

///譜面の中心Y座標
#define DANCE_PARTICLE_FUMEN_CENTER_Y	(-17700)

///決めパーティクル(Lv1)の絶対座標：左側
#define DANCE_PARTICLE_FINISH_LEFT_LV1		(-13000)
///決めパーティクル(Lv1)の絶対座標：右側
#define DANCE_PARTICLE_FINISH_RIGHT_LV1		((-DANCE_PARTICLE_FINISH_LEFT_LV1) + 7500)
///決めパーティクル(Lv1)の絶対座標：Y
#define DANCE_PARTICLE_FINISH_Y_LV1			(-6300)

///決めパーティクル(Lv2)の絶対座標：左側
#define DANCE_PARTICLE_FINISH_LEFT_LV2		(DANCE_PARTICLE_FINISH_LEFT_LV1 - 4000)
///決めパーティクル(Lv2)の絶対座標：右側
#define DANCE_PARTICLE_FINISH_RIGHT_LV2		(DANCE_PARTICLE_FINISH_RIGHT_LV1 - 4000)
///決めパーティクル(Lv2)の絶対座標：Y
#define DANCE_PARTICLE_FINISH_Y_LV2			(DANCE_PARTICLE_FINISH_Y_LV1)


//--------------------------------------------------------------
//	アクターBGプライオリティ
//--------------------------------------------------------------
///曲進行バーアクターのBGプライオリティ
#define DANCE_BGPRI_MUSIC_BAR	(1)
///音符アクターのBGプライオリティ
#define DANCE_BGPRI_ONPU		(DANCE_BGPRI_BACKGROUND)	//(1)
///評価パネルアクターのBGプライオリティ
#define DANCE_BGPRI_REVIEW		(1)
///自分カーソルアクターのBGプライオリティ
#define DANCE_BGPRI_MY_CURSOR		(1)
///プリンアクターのBGプライオリティ
#define DANCE_BGPRI_PRIN		(1)
///影アクターのBGプライオリティ
#define DANCE_BGPRI_SHADOW		(DANCE_BGPRI_BACKGROUND)
///星アクターのBGプライオリティ
#define DANCE_BGPRI_STAR		(DANCE_BGPRI_BACKGROUND)

//--------------------------------------------------------------
//	アクターソフトプライオリティ
//--------------------------------------------------------------
enum{
	DANCE_SOFTPRI_START = 10,
	
	DANCE_PRIN,						///<プリン
	
	DANCE_SOFTPRI_REVIEW_FONT,		///<評価パネルアクターの上に乗るフォントOAM
	DANCE_SOFTPRI_REVIEW,			///<評価パネルアクター
	
	DANCE_SOFTPRI_MUSIC_BAR,		///<曲進行バーアクター
	DANCE_SOFTPRI_ONPU = DANCE_SOFTPRI_MUSIC_BAR + 30,				///<音符アクター
	DANCE_SOFTPRI_MY_CURSOR,		///<自分カーソルアクター
	
	DANCE_SOFTPRI_STAR,				///<星
	DANCE_SOFTPRI_SHADOW,			///<影
};

///音符タイプ
enum{
	ONPU_TYPE_A,
	ONPU_TYPE_B,
	
	ONPU_TYPE_MAX,
};

///ダンスタイプ
enum{
	DANCE_STEP_NONE,
	
	DANCE_STEP_JUMP,
	DANCE_STEP_ADVANCE,
	DANCE_STEP_LEFT,
	DANCE_STEP_RIGHT,
};

///ダンサータイプ
enum{
	DANCER_MAIN,	///<メインダンサー
	DANCER_BACK,	///<バックダンサー
};

///ダンスのラグ
enum{
	DANCE_LAG_EXCELLENT_A,
	DANCE_LAG_EXCELLENT_B,
	DANCE_LAG_GOOD_A,
	DANCE_LAG_GOOD_B,
	
	DANCE_LAG_FAILED,
	DANCE_LAG_MAX = DANCE_LAG_FAILED,
};

///ダンスのラグ毎の得点
enum{
	DANCE_POINT_EXCELLENT_A = 2,
	DANCE_POINT_EXCELLENT_B = 2,
	DANCE_POINT_GOOD_A = 1,
	DANCE_POINT_GOOD_B = 1,
};

//--------------------------------------------------------------
//	スクリーンコード
//--------------------------------------------------------------
///曲進行バーの先頭スクリーンコード
#define MUSIC_BAR_FAST_SCRN_CODE_BASE		(0x200c)
///曲進行バーのメーター満タンのスクリーンコード
#define MUSIC_BAR_FAST_SCRN_CODE_FULL		(MUSIC_BAR_FAST_SCRN_CODE_BASE + 8)
///曲進行バーの先頭スクリーンコード
#define MUSIC_BAR_SECOND_SCRN_CODE_BASE		(0x202c)
///曲進行バーのメーター満タンのスクリーンコード
#define MUSIC_BAR_SECOND_SCRN_CODE_FULL		(MUSIC_BAR_SECOND_SCRN_CODE_BASE + 8)
///曲進行バーの先頭スクリーンコード
#define MUSIC_BAR_THERD_SCRN_CODE_BASE		(0x204c)
///曲進行バーのメーター満タンのスクリーンコード
#define MUSIC_BAR_THERD_SCRN_CODE_FULL		(MUSIC_BAR_THERD_SCRN_CODE_BASE + 8)

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///音符のアニメタイプ
enum{
	ONPU_ANMTYPE_MINE,			///<自分用音符
	ONPU_ANMTYPE_ENEMY,			///<敵用音符
	ONPU_ANMTYPE_HISTORY,		///<履歴用音符
};


///メッセージタグ
enum{
	DTAG_NONE,		///<タグなし
	
	DTAG_NICK,		///<ニックネーム
	DTAG_RANK,		///<コンテストランク
	DTAG_NUM,		///<数値
	DTAG_OYA_NICK,	///<親名、ニックネーム
	DTAG_NICK_NUM,	///<ニックネーム、数値
	DTAG_RANK_NUM_OYA_NICK,
	
	DTAG_MAX,
};


//==============================================================================
//	構造体定義
//==============================================================================
//--------------------------------------------------------------
//	
//--------------------------------------------------------------
typedef struct{
	u8 actin_sort[BREEDER_MAX];
}DANCE_EXIT_PARAM;

//--------------------------------------------------------------
//	メッセージ
//--------------------------------------------------------------
///演技部門メッセージデータ
typedef struct{
	u16 msg_id;				///<メッセージID
	u8 msg_tag;				///<タグコード
}DANCE_MESSAGE_PARAM;

///メッセージタグ展開する場合、参照されるパラメータ類
typedef struct{
	u8 mine_brd;		///<MINEが指定されていた時に参照するブリーダーの番号
	u8 enemy_brd;		///<ENEMYが指定されていた時に参照するブリーダーの番号
	u16 wazano;			///<WAZAが指定されていた時に参照する技番号
	u8 num;				///<NUMが指定されていた時に表示する数値
	u8 judge_no;		///<JUDGEが指定されていた時に参照する審判の番号
}DTAG_PARAM;

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///評価パネルエフェクトタスク
typedef struct{
	CATS_ACT_PTR cap;
	ADV_FONTACT *fontact;
	TCB_PTR tcb;			///<動作タスクへのポインタ
	
	s32 work;
	u8 seq;
}REVIEW_PANEL_TASK_WORK;

///プリン動作ワーク
typedef struct{
	TCB_PTR tcb;			///<プリン動作メインタスクへのポインタ
	CATS_ACT_PTR cap;		///<プリンアクターへのポインタ
	struct _DANCE_PROC_WORK *dpw;	///<ダンス部門管理ワークへのポインタ
	
	u8 seq;
}PRIN_WORK;

///影動作ワーク
typedef struct{
	TCB_PTR tcb;			///<影動作メインタスクへのポインタ
	CATS_ACT_PTR cap;		///<影アクターへのポインタ
	struct _DANCE_PROC_WORK *dpw;	///<ダンス部門管理ワークへのポインタ
	CONTEST_IMC_WORK *imcwork;	///<対象のポケモンイメージクリップへのポインタ
	
	u8 seq;
	u8 homing;				///<TRUE:追尾ON、FALSE:追尾OFF
	u8 homing_jump;			///<TRUE:追尾ON、FALSE:追尾OFF
	u8 breeder_no;			///<影を担当するブリーダー番号
	s8 height;				///<ポケモンの高さ
}SHADOW_WORK;

///スポットライト動作ワーク
typedef struct{
	TCB_PTR tcb;			///<スポットライト動作メインタスクへのポインタ
	CATS_ACT_PTR cap;		///<アクターへのポインタ
	struct _DANCE_PROC_WORK *dpw;	///<ダンス部門管理ワークへのポインタ
	
	u8 seq;
	u8 breeder_no;			///<スポットライトを担当するブリーダー番号
	s8 height;				///<ポケモンの高さ
}SPOTLIGHT_WORK;

///星動作ワーク
typedef struct{
	TCB_PTR tcb;			///<星動作メインタスクへのポインタ
	CATS_ACT_PTR cap;		///<星アクターへのポインタ
	
	s32 x;					///<現在座標X(下位8ビット小数)
	s32 y;					///<現在座標Y(下位8ビット小数)
	s32 add_x;				///<X方向加算値
	s32 up_power;			///<ジャンプ力
	u16 life_frame;			///<生存フレーム
}STAR_WORK;

///譜面フラッシュ動作ワーク
typedef struct{
	struct _DANCE_PROC_WORK *dpw;	///<ダンス部門管理ワークへのポインタ
	TCB_PTR tcb;			///<譜面フラッシュメイン動作タスクへのポインタ
	u16 evy;				///<EVY値(下位8ビット小数)
	u8 color_pos;			///<フェード開始カラー位置
	u8 occ;					///<TRUE：エフェクト起動中
}FUMEN_FLASH_WORK;

///ポケモン常駐アニメ用ワーク
typedef struct{
	struct _DANCE_PROC_WORK *dpw;	///<ダンス部門管理ワークへのポインタ
	TCB_PTR tcb;			///<アニメ実行タスクへのポインタ
	SOFT_SPRITE *ss;		///<対象のポケモンソフトウェアスプライトへのポインタ
	CONTEST_IMC_WORK *imcwork;	///<対象のポケモンイメージクリップへのポインタ
	s32 aff_z;				///<拡縮の為のZ座標(下位8ビット小数)
	s32 move_sin;			///<移動アニメの現在のSin値
	
	u8 aff_loop;			///<拡縮アニメ繰り返し回数
	u8 rotation_pos;		///<ローテーション位置
	u8 breeder_no;			///<ブリーダー番号
	u8 aff_seq;
	u8 move_seq;
	
	u32 move_stop_sin;		///<移動アニメ：停止した時の角度
	
	u8 move_stop_req:1;		///<1:移動アニメ停止リクエスト(通常位置に戻ったら停止)
	u8 move_stop:1;			///<1:移動アニメ停止(即停止)
	u8 move_start_req:1;	///<1:移動アニメ開始リクエスト
	u8 move_init:1;			///<1:初期起動

	u8 aff_stop_req:1;		///<1:拡縮アニメ停止リクエスト(通常Affineサイズに戻ったら停止)
	u8 aff_stop:1;			///<1:拡縮アニメ即停止
	u8 aff_dir:1;			///<拡縮アニメの方向(0:手前へ、1:奥へ)
}POKE_DEF_ANM_WORK;

///パーティクル引数受け渡し用テンポラリワーク
typedef struct{
	s32 x;				///<座標X
	s32 y;				///<座標Y
	s32 z;				///<座標Z
	fx32 gen_num;		///<放出レート
}DANCE_PARTICLE_TEMP_WORK;

///ダンス実行動作のパラメータ(1frameの通信で全て送受信出来るように20バイト以内に収める事!!)
typedef struct{
	u16 frame;			///<ダンスした時のフレーム数
	u8 breeder_no;		///<ブリーダー番号(このダンスをしたブリーダー)
	u8 dance_step;		///<ダンスの種類(上下左右)
	u8 review_type;		///<評価タイプ(REVIEW_TYPE_EXCELLENT等)
	u8 lag_type;		///<ラグタイプ
	u8 hit_beat;		///<何小節目を評価対象にしたか
	u8 rotation_pos;	///<ローテーション位置
	
	u8 finish:1;		///<TRUE:最後のダンス、決めポーズ
	u8 button_failed:1;	///<TRUE:押したボタンがメインダンサーと違った
	u8 occ:1;			///<有効無効フラグ(TRUE:データ有効)
	u8 :6;
}DANCING_PARAM;

///<ダンスのずれ許容範囲(EXCELLENT_A,B,GOOD_A,B)
typedef struct{
	u8 excellent_a;
	u8 excellent_b;
	u8 good_a;
	u8 good_b;
}DANCE_LAG_DATA;

///ダンス音楽進行データ
typedef struct{
	u16 music_id;				///<曲ID
	u16 tempo;					///<曲のテンポ
	u8 loop;					///<繰り返し回数
	u8 touch_count;				///<タッチ(ダンス)出来る回数
	u8 ready_count;				///<準備時間の小節数
	u8 rotation_count;			///<ローテーションの小節数
	DANCE_LAG_DATA lag;			///<ダンスのずれ許容範囲(EXCELLENT_A,B,GOOD_A,B)
}DANCE_MUSIC_DATA;

///ダンスアニメーションワークのエフェクト動作で使用するワーク
typedef struct{
	//どのステップでも共通で使用するであろうワーク
	s32 start_x;		///<アニメ開始前のX座標
	s32 start_y;		///<アニメ開始前のY座標
	s32 x;				///<現在座標X
	s32 y;				///<現在座標Y
	u8 seq;
	
	//各ステップ毎に独自で持つワーク
	union{
		struct{
			s16 up_power;
			s16 gravity;
		}jump;
		
		struct{
			s32 add_go_x;
			s32 add_back_x;
		}advance;
		
		struct{
			u32 theta;
			int add_theta;
			int back_theta;
			int add_x;
			int back_x;
		}lr;
	};
}MOVE_EFF_WORK;

///ダンスアニメーションワーク
typedef struct{
	u8 dance_step[DANCE_STEP_REQUEST_MAX];	///<ダンスの種類(DANCE_STEP_???)
	
	u8 work_pos;							///<現在指しているdance_stepワークの配列位置
	u8 rotation_pos;
	u8 finish;								///<TRUE:最後の決めダンス
	u8 point;								///<ダンスした時の合計得点
	
	MOVE_EFF_WORK eff;						///<エフェクト動作用のワーク
}DANCE_MOVE_WORK;

///ダンス用AIワーク
typedef struct{
	union{
		//メインダンサー用ワーク
		struct{
			u32 hit_frame[DANCING_MAX];			///<ダンスを実行するフレーム
			u8 tp_type[DANCING_MAX];
			u8 occ[DANCING_MAX];
		}main;

		//バックダンサー用ワーク
		struct{
			u32 frame;
			u8 tp_type;
			u8 occ;
		}back;
	};

	//共用ワーク
	u32 random_seed;					///<AI計算用のランダムの種
	s16 touch_wait;						///<タッチ出来ないフレームをカウント
	u8 touch_count;						///<ダンスした回数をカウント
	u8 breeder_no;						///<AI自身のブリーダー番号
	u8 rotation_pos;					///<ローテーション位置
	u8 character;						///<性格
}DANCE_AI_WORK;

///メインシーケンス内で使用するローカルワーク
typedef struct{
	u16 seq;
	u16 select_seq;
	s32 work;
}DANCE_LOCAL_WORK;

//--------------------------------------------------------------
/**
 * @brief   ダンス部門進行パラメータ(現在技を出しているポケモンの進行パラメータ)
 */
//--------------------------------------------------------------
typedef struct{
	u8 now_breeder;					///<現在場に出ているブリーダーの番号
	u8 now_count;					///<現在場に出ているブリーダーが何番目にアピールしているか
	
	u8 breeder_rotation[BREEDER_MAX];	///<現在のブリーダーのローテーション並び
										///<メインダンサーから順々にブリーダー番号が入ってます

	u32 one_tempo_frame;			///<1小節進むのに必要なフレーム数
									///<(整数部：ONE_TEMPO_CALC_DECIMAL乗算部分、以下小数)
	u32 all_tempo_frame;			///<画面端から端まで進むのに必要なフレーム数(整数)
	u16 tempo;						///<ダンス曲のテンポ

	u32 ai_random_seed[BREEDER_MAX];	///<AI用のランダムの種
	
	DANCE_MUSIC_DATA musicdata;		///<音楽進行データ

	DTAG_PARAM a_talk_tagpara;		///<ノーマル会話：タグ展開用パラメータ
	u8 a_talk_id;					///<ノーマル会話ID(A_TALK_DANCE_???)
	u8 a_talk_bmpwin_close_wait;	///<メッセージを表示しきってからウィンドウを閉じるまでのwait
	u8 a_talk_bmpwin_not_close;		///<TRUE:ウィンドウを閉じずに終了
}DANCE_ADVANCE_PARAM;

//--------------------------------------------------------------
/**
 * @brief   ダンス部門ゲーム進行パラメータ
 *
 * このパラメータがあれば全画面を再構築出来るだけの情報が入っています。
 * 通信時はサーバーから子機はデータを受け取る事になります。
 * 基本的にメニュー画面からの画面復帰のような事がない限り、
 * 個々の子機側で値を参照する事はないはずです。
 */
//--------------------------------------------------------------
typedef struct{
	u8 breeder_sort[BREEDER_MAX];	///<技を出す順番(出る順にブリーダー番号が入ってます)
	u8 breeder_end_count;			///<行動が終了したブリーダーの数をカウント

	u8 breeder_rotation[BREEDER_MAX];	///<現在のブリーダーのローテーション並び
										///<メインダンサーから順々にブリーダー番号が入ってます
	
	s16 dance_point[BREEDER_MAX];	///<獲得したダンスポイント
	
	u32 music_id;					///<ダンスの曲ID

	u32 one_tempo_frame;			///<1小節進むのに必要なフレーム数
									///<(整数部：ONE_TEMPO_CALC_DECIMAL乗算部分、以下小数)
	u32 all_tempo_frame;			///<画面端から端まで進むのに必要なフレーム数(整数)
	u32 ready_frame;				///<準備時間のフレーム数(整数部：ONE_TEMPO_CALC_DECIMAL乗算)
	u32 rotation_frame;		///<ローテーション時間のフレーム数(整数部：ONE_TEMPO_CALC_DECIMAL乗算)
	u32 tick_frame;			///<1フレーム＝何tick なのか(整数部：ONE_TEMPO_CALC_DECIMAL乗算)
	u16 tempo;						///<ダンス曲のテンポ
	
	u8 touch_count;					///<タッチ出来る最大回数
}DANCE_GAME_PARAM;

//--------------------------------------------------------------
/**
 * @brief   命令送受信用パラメータ
 * 
 * サーバーとの命令の送受信に使用します
 */
//--------------------------------------------------------------
typedef struct{
	u8 breeder_no;
	
	u8 buffer[255];					///<各命令で個別に渡すデータが変わる場合、ここを使用
}DANCE_ORDER_PARAM;

///パレット中間バッファ
typedef struct{
	u16 *buf;			///<中間バッファへのポインタ
	u16 evy;			///<EVY値(下位8ビット小数)
	u16 fade_bit;		///<フェードBIT
	u16 now_evy;		///<現在のEVY値(下位8ビット小数)
	u16 end_evy;		///<終了EVY値(下位8ビット小数)
	s16 add_evy;		///<EVY加算値
	u16 next_rgb;		///<変更後のカラー
	u8 req;				///<TRUE:フェードリクエスト中
	u8 occ;				///<TRUE:中間バッファを使用する
}DANCE_MIDDLE_FADE;

//--------------------------------------------------------------
/**
 * @brief   ゲーム画面を構成するために必要なシステムデータ類を持つ構造体
 *
 * 通信時でも全てのマシンで個別に作成されます
 * 各スタッフが命令受信時、そのマシン個々で生成したこのワークバッファを渡す事になります
 */
//--------------------------------------------------------------
typedef struct{
	CONTEST_GAME_PARAM *c_game;		///<コンテスト進行パラメータ(受付で既に通信済みのデータへのポインタを持つだけ。参照用)
	
	//イメージクリップ
	CONTEST_IMC_WORK imcwork[BREEDER_MAX];	///<イメージクリップ関連ワーク

	SOFT_SPRITE_MANAGER	*soft_sprite;
	SOFT_SPRITE *ss[BREEDER_MAX];
	CATS_SYS_PTR		csp;
	CATS_RES_PTR		crp;
	GF_BGL_INI *bgl;
	GF_BGL_BMPWIN win[DANCE_BMPWIN_MAX];
	MSGDATA_MANAGER *dance_msg;	///<ダンス部門メッセージ用メッセージマネージャのポインタ
	WORDSET *wordset;
	STRBUF *msg_buf;				///<Allocした文字列バッファへのポインタ
	PALETTE_FADE_PTR pfd;			///<パレットフェードシステムへのポインタ
	FONTOAM_SYS_PTR fontoam_sys;	///<フォントOAMシステムへのポインタ
	
	EXCHR_PARAM exchr_param[BREEDER_MAX];		///<技エフェクト用キャラ展開バッファ

	CATS_ACT_PTR onpu_cap[ONPU_ACTOR_MAX];		///<音符アクターのポインタ
	
	CATS_ACT_PTR my_cursor_cap;		///<自分カーソルアクターのポインタ
	TCB_PTR my_cursor_tcb;			///<自分カーソルタスクのTCBポインタ
	
	FUMEN_FLASH_WORK fumen_flash;	///<譜面フラッシュ動作ワーク
	PRIN_WORK *prin_sys;			///<プリン動作ワーク
	SHADOW_WORK shadow[BREEDER_MAX];	///<影動作ワーク
	SPOTLIGHT_WORK spotlight[BREEDER_MAX];	///<スポットライト動作ワーク
	STAR_WORK star[BREEDER_MAX][STAR_EFF_MAX];	///<星動作ワーク
	
	REVIEW_PANEL_TASK_WORK rptw[REVIEW_ACTOR_MAX];	///<評価パネル動作タスクのワーク
	CATS_ACT_PTR review_cap[REVIEW_ACTOR_MAX];		///<評価パネルアクターのポインタ
	ADV_FONTACT fontact[REVIEW_TYPE_MAX][REVIEW_ACTOR_MAX];	///<評価パネル上のフォントアクター

	const DANCE_MUSIC_DATA *musicdata;		///<音楽進行データへのポインタ

	u8 jump_up[BREEDER_MAX];		///<TRUE:ジャンプOK。　FALSE:ジャンプ禁止("上"動作)
	
	u8 talk_msg_index;				///<文字描画ルーチンのインデックス
	
	u8 excellent_count[BREEDER_MAX];		///<Excellent連続取得回数(全てのダンス継続)
	u8 now_excellent_count[BREEDER_MAX];	///<Excellent連続取得回数(今の譜面のダンスのみ)
	u8 now_failed_count[BREEDER_MAX];		///<FAILED取得回数(今の譜面のダンスのみ)
	u8 now_back_excellent_all_count;		///<バックダンサーのExcellent取得回数
	u8 now_back_good_all_count;				///<バックダンサーのGood取得回数
	u8 now_back_failed_all_count;			///<バックダンサーのFailed取得回数
	u8 succession_count[BREEDER_MAX];		///<連続ダンス回数(全てのダンス継続)
	u8 my_dancing_rotation_pos;				///<ダンス中の自分のローテーション位置
}DANCE_SYSTEM_PARAM;

//--------------------------------------------------------------
/**
 * @brief   ダンス部門管理ワーク
 *
 * ダンス部門全体を管理する大元のワークになります。
 * 通信時でも全てのマシンで個別に作成されます
 */
//--------------------------------------------------------------
typedef struct _DANCE_PROC_WORK{
	CONTEST_SYSTEM *consys;			///<コンテストシステムワークへのポインタ
	TCB_PTR update_tcb;				///<システム更新処理
	TCB_PTR move_tcb;				///<ポケモンダンスエフェクト実行タスクへのポインタ
	PTC_PTR ptc;					///<常駐パーティクルシステム
	GF_G3DMAN *g3Dman;
	
	DANCE_SYSTEM_PARAM sys;			///<ダンス部門システムデータパラメータ
	DANCE_GAME_PARAM d_game;			///<ゲーム進行パラメータ
	DANCE_ADVANCE_PARAM advance;		///<進行パラメータ
	DANCE_ORDER_PARAM order[BREEDER_MAX];	///<命令パラメータ
	DANCE_MOVE_WORK move[BREEDER_MAX];		///<ダンスアニメーションワーク
	POKE_DEF_ANM_WORK pda[BREEDER_MAX];		///<ポケモン常駐アニメ用ワーク

	DANCE_MIDDLE_FADE middle_fade;	///<パレット中間バッファ

	DANCE_PARTICLE_TEMP_WORK particle_temp;	///<パーティクル引数受け渡し用テンポラリワーク
	
	void *dip;						///<サブ画面制御システム構造体へのポインタ
	
	u8 music_vcount_flag;			///<TRUE：曲進行フレームカウントアップ
	u64 music_vcount;				///<曲進行のフレーム確認(曲とずれないようにVblankで++する)
	u64 music_vcount_start;			///<ダンスを開始した時のVカウンタを記憶
	u32 music_vcount_hosei_count;	///<補正しなければいけないフレームが貯まっている数
	u32 tick_temp;					///<tickの値を保存
	
	u16 seq;
	u16 tbl_seq_no;					///<メインシーケンステーブルの番号
	u8 proc_mode;					///<現在の動作状況

#if 0
	//-- 送受信バッファ --//
	u32 request_bit;				///<命令を出しているビット
	u8 transmit_buf[TRANSMIT_BUF_SIZE];	///<送信用バッファ
	u8 receive_buf[RECEIVE_BUF_SIZE];	///<受信用バッファ
	u8 transmit_flag;				///<TRUE：送信待ち。　FALSE:新たなデータセット可能
	u8 receive_flag;				///<TRUE：データ受信した
#endif
	CONTEST_ORDER_WORK cow;			///<送受信ワーク

	DANCING_PARAM dancing[BREEDER_MAX];		///<ダンス実行動作のパラメータ
	DANCING_PARAM maindancer_record[DANCING_RECORD_MAX];	///<メインダンサーのダンス履歴(通信時、データは個々のこの場所に受信される事になり、クライアントそれぞれが自分自身のDANCE_PROC_WORKのこの場所を参照する事になります)

	DANCE_LOCAL_WORK local;			///<ローカルワーク
	u8 main_end;					///<TRUE:メイン処理終了
	
	u8 bord_msg_flag;				///<TRUE:看板メッセージ表示中
}DANCE_PROC_WORK;


//==============================================================================
//	外部関数宣言
//==============================================================================
extern PROC_RESULT DanceProc_Init( PROC * proc, int * seq );
extern PROC_RESULT DanceProc_Main( PROC * proc, int * seq );
extern PROC_RESULT DanceProc_End( PROC * proc, int * seq );

#ifdef PM_DEBUG
extern void TestParticleDance(DANCE_PROC_WORK *dpw);
#endif

//==============================================================================
//	外部データ宣言
//==============================================================================
extern const PROC_DATA ContestDanceProcData;



#endif	//__DANCE_H__

