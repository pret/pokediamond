//==============================================================================
/**
 * @file	actin.h
 * @brief	演技力部門のヘッダ
 * @author	matsuda
 * @date	2005.11.16(水)
 */
//==============================================================================
#ifndef __ACTIN_H__
#define __ACTIN_H__

#include "system/procsys.h"
#include "battle/battle_common.h"
#include "system/buflen.h"
#include "contest/contest.h"
#include "system/softsprite.h"
#include "wazaeffect/we_mana.h"
#include "wazaeffect/we_sys.h"
#include "system/fontproc.h"
#include "system/msgdata.h"
#include "system/gra_tool.h"
#include "system/wordset.h"

#include "contest/actin_ex.h"
#include "contest_order.h"

#include "adv_tool.h"
#include "actin_param.h"
#include "actin_snd_def.h"


//==============================================================================
//	定数定義
//==============================================================================
///終了ターン
#define ACTIN_END_TURN		(4)

///サブ画面のサーフェース位置(FX32)
#define ACTIN_SUB_ACTOR_DISTANCE	(BATTLE_SUB_ACTOR_DISTANCE)
///サブ画面のサーフェース位置(int)
#define ACTIN_SUB_ACTOR_DISTANCE_INTEGER	(ACTIN_SUB_ACTOR_DISTANCE >> FX32_SHIFT)

///アピールアイコン1つが持つポイント
#define APPEAL_ICON_ONE_POINT		(10)
///アピールした時に出す、アピールポイントアイコンの数(アクター数)
#define APPEAL_POINT_ICON_MAX		(6)
///アピールポイントアイコンの表示が何週あるか(2週目からはハートアニメの姿が違う)
#define APPEAL_POINT_ICON_LOOP		(4)

///ボルテージが付く最大数
#define VOLTAGE_MAX			(5)
///ボルテージ１つのポイント
#define VOLTAGE_ONE_POINT	(10)
///ボルテージが最大数付いた時のポイント
#define VOLTAGE_POINT_FULL	(VOLTAGE_ONE_POINT * VOLTAGE_MAX)
///ボルテージが最大に達した時に加算するAP値(凄い審査員)
#define VOLTAGE_FULL_ADD_AP_SPECIAL		(APPEAL_ICON_ONE_POINT * 8)
///ボルテージが最大に達した時に加算するAP値(普通の審査員)
#define VOLTAGE_FULL_ADD_AP				(APPEAL_ICON_ONE_POINT * 5)

///技エフェクト中に場に出ているポケモンの数
#define ACTIN_WAZA_POKEMAX		(2)		//技を出すポケモン＋攻撃対象となる透明ポケモン

///観客の歓声のボリューム標準値
#define ACTIN_AUDIENCE_VOLUME			(70)

///ポケモン定位置X
#define ACTIN_POKEPOS_X		(CONTEST_ATTACK_POKE_X)
///ポケモン定位置Y
#define ACTIN_POKEPOS_Y		(CONTEST_ATTACK_POKE_Y)
///ポケモン定位置Z
#define ACTIN_POKEPOS_Z		(CONTEST_ATTACK_POKE_Z)

///ポケモン登場位置X
#define ACTIN_POKEPOS_APPEAR_X	(ACTIN_POKEPOS_X + 40)
///ポケモン登場位置Y
#define ACTIN_POKEPOS_APPEAR_Y	(ACTIN_POKEPOS_Y + 60)

///ポケモンINする前のウェイト
#define ACTIN_POKEMOVE_IN_BEFORE_WAIT		(10)

///ポケモンINする時、定位置までにかける移動フレーム数
#define ACTIN_POKEMOVE_IN_FRAME	(7)	//(10)
///ポケモンINする時の移動速度X(下位8ビット小数)
#define ACTIN_POKEMOVE_IN_X		(((ACTIN_POKEPOS_APPEAR_X - ACTIN_POKEPOS_X) << 8) \
									/ ACTIN_POKEMOVE_IN_FRAME)
///ポケモンINする時の移動速度Y(下位8ビット小数)
#define ACTIN_POKEMOVE_IN_Y		(((ACTIN_POKEPOS_APPEAR_Y - ACTIN_POKEPOS_Y) << 8) \
									/ ACTIN_POKEMOVE_IN_FRAME)

///ポケモンOUTする時、定位置までにかける移動フレーム数
#define ACTIN_POKEMOVE_OUT_FRAME	(7)	//(10)
///ポケモンOUTする時の移動速度X(下位8ビット小数)
#define ACTIN_POKEMOVE_OUT_X		(((ACTIN_POKEPOS_APPEAR_X - ACTIN_POKEPOS_X) << 8) \
									/ ACTIN_POKEMOVE_OUT_FRAME)
///ポケモンOUTする時の移動速度Y(下位8ビット小数)
#define ACTIN_POKEMOVE_OUT_Y		(((ACTIN_POKEPOS_APPEAR_Y - ACTIN_POKEPOS_Y) << 8) \
									/ ACTIN_POKEMOVE_OUT_FRAME)

///ブリーダー情報パネル1つのX幅(キャラ単位)
#define BREEDER_PANEL_X_LEN			(10)
///ブリーダー情報パネル1つのY幅(キャラ単位)
#define BREEDER_PANEL_Y_LEN			(6)
///ブリーダー情報パネルの左上スクリーン位置(キャラクタ単位)
#define BREEDER_PANEL_SCREEN_START_POS	(0)//(32*32 + 22)

///演技力部門メイン画面で使用するフォントOAMの最大数
#define ACTIN_FONTOAM_MAX_MAIN		(2 * BREEDER_MAX)	//(ブリーダー＋ニックネーム)＊参加人数

//--------------------------------------------------------------
//	バッファ
//--------------------------------------------------------------
///文字列バッファのサイズ
#define ACTIN_MESSAGE_BUF_SIZE	(2*160)		///<暫定で１６０文字分

///送信用バッファサイズ
#define TRANSMIT_BUF_SIZE		(512)
///受信用バッファサイズ
#define RECEIVE_BUF_SIZE		(TRANSMIT_BUF_SIZE)

//--------------------------------------------------------------
//	メッセージタグ
//--------------------------------------------------------------
///メッセージタグ
enum{
	ATAG_NONE,		///<タグなし
	ATAG_NOW,		///<現在演技中のポケモン名(ニックネーム)
	
	ATAG_MINE,		///<自分のニックネーム
	ATAG_ENEMY,		///<敵のニックネーム
	ATAG_WAZA,		///<技名
	ATAG_NUM,		///<1桁数値
	ATAG_JUDGE,		///<審判名
	
	ATAG_MINE_ENEMY,
	ATAG_MINE_WAZA,
	ATAG_MINE_NUM,
	ATAG_MINE_JUDGE,
	
	ATAG_ENEMY_MINE,
	ATAG_ENEMY_WAZA,
	ATAG_ENEMY_NUM,
	ATAG_ENEMY_JUDGE,
	
	ATAG_WAZA_MINE,
	ATAG_WAZA_ENEMY,
	ATAG_WAZA_NUM,
	ATAG_WAZA_JUDGE,
	
	ATAG_NUM_MINE,
	ATAG_NUM_ENEMY,
	ATAG_NUM_WAZA,
	ATAG_NUM_JUDGE,

	ATAG_JUDGE_MINE,
	ATAG_JUDGE_ENEMY,
	ATAG_JUDGE_WAZA,
	ATAG_JUDGE_NUM,
	
	ATAG_MINE_JUDGE_WAZA,
	
	//特殊コード
	ATAG_EXCODE_JUDGESUFFER,	///<特殊コード：審判被り
	
	ATAG_MAX,
};

///メッセージIDなし
#define AMSG_ID_NONE		(0xffff)

//--------------------------------------------------------------
//	フレーム番号
//--------------------------------------------------------------
///ウィンドウ・パネル面のフレーム
#define ACTIN_FRAME_WIN				(GF_BGL_FRAME1_M)
///エフェクト面のフレーム
#define ACTIN_FRAME_EFF				(GF_BGL_FRAME2_M)
///観客(背景)面のフレーム
#define ACTIN_FRAME_AUDIENCE		(GF_BGL_FRAME3_M)

///ブリーダーパネル面のフレーム
#define ACTIN_FRAME_BRDPANEL		(ACTIN_FRAME_EFF)

///ウィンドウ・パネル面の標準スクロール座標X
#define FRAME_WIN_DEFAULT_X			(0)//(256 + 22*8)
///ウィンドウ・パネル面の標準スクロール座標Y
#define FRAME_WIN_DEFAULT_Y			(0)

///エフェクト面のBGタイプ
enum{
	EFF_BG_TYPE_BRDPANEL,		///<ブリーダーパネル
	EFF_BG_TYPE_EFFECT,			///<技エフェクト用
};

//--------------------------------------------------------------
//	BMPウィンドウ
//--------------------------------------------------------------
enum{
	ACTIN_BMPWIN_TALK,		///<会話ウィンドウ
#if 0	//ブリーダー情報はOBJで出すようにしたのでいらなくなった 2006.02.02(木)
	ACTIN_BMPWIN_BREEDER_0,	///<ブリーダー1体目
	ACTIN_BMPWIN_BREEDER_1,	///<ブリーダー2体目
	ACTIN_BMPWIN_BREEDER_2,	///<ブリーダー3体目
	ACTIN_BMPWIN_BREEDER_3,	///<ブリーダー4体目
#endif

	ACTIN_BMPWIN_MAX,
};

///ブリーダー情報に書くメッセージカラー指定(敵用)
#define MSGCOLOR_BREEDERPARAM		(GF_PRINTCOLOR_MAKE(5, 6, 0))
///ブリーダー情報に書くメッセージカラー指定(自分用)
#define MSGCOLOR_BREEDERPARAM_MINE	(GF_PRINTCOLOR_MAKE(1, 2, 0))

//--------------------------------------------------------------
//	BGプライオリティ
//--------------------------------------------------------------
///ブリーダー名、ニックネームのフォントアクターBGプライオリティ
#define ACTIN_BGPRI_BREEDER_PARAM	(0)
///審判アクターのBGプライオリティ
#define ACTIN_BGPRI_JUDGE	(3)
///アピールポイントアイコンのBGプライオリティ
#define ACTINSUB_BGPRI_APPEAL_POINT		(0)
///ボルテージ演出のBGプライオリティ
#define ACTIN_BGPRI_VOLTAGE_EFF			(ACTIN_BGPRI_JUDGE)
///ボルテージポイントアイコンのBGプライオリティ
#define ACTINSUB_BGPRI_VOLTAGE_POINT		(ACTIN_BGPRI_JUDGE)
///次アイコンのBGプライオリティ
#define ACTINSUB_BGPRI_NEXT_ICON		(ACTIN_BGPRI_BREEDER_PARAM)
///審判リアクションアイコンのBGプライオリティ
#define ACTIN_BGPRI_JUDGE_REACTION		(ACTIN_BGPRI_JUDGE)

//--------------------------------------------------------------
//	サブ画面のBGプライオリティ
//--------------------------------------------------------------
///凄い審判につけるハートのBGプライオリティ
#define ACTINSUB_BGPRI_HEART_JUDGE	(1)
///AP値ハートのBGプライオリティ
#define ACTINSUB_BGPRI_APP_HEART	(1)

//--------------------------------------------------------------
//	アクターソフトプライオリティ
//--------------------------------------------------------------
enum{
	ACTIN_SOFTPRI_START = 10,

	ACTIN_SOFTPRI_APPEAL_POINT,	///<アピールポイントアイコン
	ACTIN_SOFTPRI_VOLTAGE_EFF,		///<ボルテージ演出
	ACTIN_SOFTPRI_VOLTAGE_POINT,	///<ボルテージポイントアイコン
	
	ACTIN_SOFTPRI_NEXT_ICON,		///<次アイコン
	ACTIN_SOFTPRI_BREEDER_PARAM,	///<ブリーダー名、ニックネームのフォントOAM
	
	ACTIN_SOFTPRI_SPECIAL_HEART = 10000,	///<特別審査員につけるハートアクター
	ACTIN_SOFTPRI_JUDGE_REACTION,	///<審判リアクションアイコンのソフトプライオリティ
	ACTIN_SOFTPRI_JUDGE_BOX,	///<審判ボックスのアクターソフトプライオリティ
	ACTIN_SOFTPRI_JUDGE,	///<審判アクターのソフトプライオリティ
};

//--------------------------------------------------------------
//	サブ画面のアクターソフトプライオリティ
//--------------------------------------------------------------
enum{
	ACTINSUB_SOFTPRI_START = 10,
	
	ACTINSUB_SOFTPRI_HEART_JUDGE = 1000,	///<凄い審判につけるハート
	ACTINSUB_SOFTPRI_APP_HEART,		///<AP値ハート
};

//--------------------------------------------------------------
//	座標：メイン画面
//--------------------------------------------------------------
///ブリーダーパネルのニックネーム基本表示座標X
#define BREEDER_PANEL_NICK_X			(1)
///ブリーダーパネルのニックネーム基本表示座標Y
#define BREEDER_PANEL_NICK_Y			(12)
///ブリーダーパネルのニックネーム表示座標の他のブリーダーと空ける間隔Y
#define BREEDER_PANEL_NICK_Y_SPACE		(48)
///ブリーダーパネルの親名基本表示座標X
#define BREEDER_PANEL_OYA_X				(BREEDER_PANEL_NICK_X)
///ブリーダーパネルの親名基本表示座標Y
#define BREEDER_PANEL_OYA_Y				(BREEDER_PANEL_NICK_Y + 16)
///ブリーダーパネルの親名表示座標の他のブリーダーと空ける間隔Y
#define BREEDER_PANEL_OYA_Y_SPACE		(BREEDER_PANEL_NICK_Y_SPACE)

///審判0の座標X
#define JUDGE_POS_X_0		(8*12)
///審判0の座標Y
#define JUDGE_POS_Y_0		(8*5)
///審判と隣の審判の間の間隔X
#define JUDGE_POS_X_SPACE	(4*8)
///審判と隣の審判の間の間隔Y
#define JUDGE_POS_Y_SPACE	(0)

///審判ボックス0の座標X
#define JUDGE_BOX_POS_X_0		(JUDGE_POS_X_0)
///審判ボックス0の座標Y
#define JUDGE_BOX_POS_Y_0		(8*4)
///審判ボックスと隣の審判ボックスの間の間隔X
#define JUDGE_BOX_POS_X_SPACE	(JUDGE_POS_X_SPACE)
///審判ボックスと隣の審判ボックスの間の間隔Y
#define JUDGE_BOX_POS_Y_SPACE	(JUDGE_POS_Y_SPACE)

///特別審査員につけるハートの座標X
#define SPECIAL_HEART_POS_X			(JUDGE_POS_X_0)
///特別審査員につけるハートの座標X
#define SPECIAL_HEART_POS_Y			(7*8)
///特別審査員につけるハートの座標X
#define SPECIAL_HEART_POS_X_SPACE	(JUDGE_POS_X_SPACE)

///次アイコンの基本座標X
#define NEXT_ICON_POS_X			(8*8)
///次アイコンの基本座標X
#define NEXT_ICON_POS_Y			(5*8 + 2)
///次アイコンの次のアイコンまでの間隔Y
#define NEXT_ICON_POS_Y_SPACE	(6*8)

///会話ウィンドウカバーで使用するアクター数
#define WINCOVER_ACT_MAX			(3)

//--------------------------------------------------------------
//	座標：サブ画面
//--------------------------------------------------------------
///審判ハートの座標X
#define SUB_HEART_JUDGE_POS_X		(5 * 8)
///審判ハートの座標Y
#define SUB_HEART_JUDGE_POS_Y		(0xc * 8)
///審判ハートと隣の審判ハートまでの間隔X
#define SUB_HEART_JUDGE_POS_X_SPACE	(11 * 8)
///審判ハートと隣の審判ハートまでの間隔Y
#define SUB_HEART_JUDGE_POS_Y_SPACE	(0)

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///順番操作フラグ
enum{
	AWK_SORT_NONE,			///<順番操作なし
	AWK_SORT_SPECIFY_FIRST,	///<順番指定(最初指定)
	AWK_SORT_SPECIFY_END,	///<順番指定(最後指定)
	AWK_SORT_RANDOM,		///<順番ランダム
};

///技効果で表示するメッセージタイプ
enum{
	KOUKA_MSGID_A,
	KOUKA_MSGID_B,
	KOUKA_MSGID_C,
	KOUKA_MSGID_D,
	
	KOUKA_MSGID_SP,
};


//==============================================================================
//	構造体定義
//==============================================================================
//--------------------------------------------------------------
//	メッセージ
//--------------------------------------------------------------
///演技部門メッセージデータ
typedef struct{
	u16 msg_id;				///<メッセージID
	u8 msg_tag;				///<タグコード
	u8 all_put;				///<TRUE:メッセージ一括表示
}ACTIN_MESSAGE_PARAM;

///メッセージタグ展開する場合、参照されるパラメータ類
typedef struct{
	u8 mine_brd;		///<MINEが指定されていた時に参照するブリーダーの番号
	u8 enemy_brd;		///<ENEMYが指定されていた時に参照するブリーダーの番号
	u16 wazano;			///<WAZAが指定されていた時に参照する技番号
	u8 num;				///<NUMが指定されていた時に表示する数値
	u8 judge_no;		///<JUDGEが指定されていた時に参照する審判の番号
}ATAG_PARAM;

//--------------------------------------------------------------
//	技効果
//--------------------------------------------------------------
///技効果によって発生した個人パラメータ
typedef struct{
	u16 wazano;				///<技番号
	u8 apno;				///<アピール番号
	u8 judge_no;			///<指名した審判番号
	u8 base_ap;				///<基本AP値
	s16 effective_ap;		///<技効果によって発生したAP加減算値
	
	s8 voltage_add_ap;					///<ボルテージによって発生したAP加減算値
	
	u8 judge_suffer;					///<被った審判の人数
	
	u8 str_target_no;	///<文字展開：技効果のターゲット対象になったブリーダーの番号(自分以外)
	u8 str_number;		///<文字展開：増減するパラメータの数値
	
	ATAG_PARAM tagpara;					///<メッセージタグパラメータ
	u8 msg_apno;						///<技効果メッセージを出す場合、その技のAPNoが入る
	u8 msg_type;						///<技効果メッセージタイプ(KOUKA_MSGID_???)
	
	u8 kouka_occ;
	
	
	s16 base_calc;						///<基本値の合計
	s16 app_total;						///<最終的な合計AP値
	s16 app_total_before;				///<計算前のAP
	s16 app_total_timing_before;		///<全員の技効果発生前のAP値
	
	
	
	s16 my_effective_ap;				///<自分の技効果によって発生したAP加減算値
	s16 enemy_effective_ap;				///<敵の技効果によって発生したAP加減算値
	u8 obstruct_apno[BREEDER_MAX];		///<妨害をしてきたブリーダーの部分に妨害技の効果番号が入る



	//-- 特殊効果フラグ --//
	u32 invalid_special:1;				///<1:特殊効果無効
	u32 invalid_voltage_up:1;			///<1:ボルテージの増加無効
	u32 invalid_voltage_down:1;			///<1:ボルテージの減少無効
	u32 voltage_all_down:1;				///<1:全員のボルテージを下げる
	u32 next_sort:2;					///<順番操作フラグ(AWK_SORT_???)
	u32 next_pos:2;						///<順番操作が有効な時、ここに順番が入る
	u32 before_next_sort:2;				///<技効果発生前の順番操作フラグ(AWK_SORT_???)
	u32 before_next_pos:2;				///<技効果発生前の順番操作が有効な時、ここに順番が入る
	u32 twice_next_apno:8;				///<「次のターン2倍」効果発動時、効果番号が入る
}AWAZA_PERSONAL;

///技効果によって次のターンに効果を発生するパラメータ
typedef struct{
	u32 waza_repeat:16;					///<繰り返し出せる技番号
	u32 twice_now_apno:8;					///<2倍効果の効果番号
}AWAZA_SAVE;

///技効果によって発生するパラメータ
typedef struct{
	AWAZA_PERSONAL personal[BREEDER_MAX];	///<個人パラメータ
	AWAZA_SAVE save[BREEDER_MAX];			///<次のターンにも影響するパラメータ
	s8 voltage_before[JUDGE_MAX];		///<アピール前のボルテージ値
	s8 voltage_after[JUDGE_MAX];		///<アピール後のボルテージ値
}AWAZA_PARAM;

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///AIの結果取得用ワーク
typedef struct{
	u16 wazano[BREEDER_MAX];	///<技番号(!!手持ちの技位置ではありません!!)
	u8 judge_no[BREEDER_MAX];	///<審判番号
}ACTIN_AI_ANSWER;

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///メインシーケンス内で使用するローカルワーク
typedef struct{
	u16 seq;
	u16 select_seq;
	s32 work;
}ACTIN_LOCAL_WORK;

///通常メッセージ(技効果以外)
typedef struct{
	ATAG_PARAM a_talk_tagpara;				///<ノーマル会話：タグ展開用パラメータ
	ATAG_PARAM after_a_talk_tagpara;		///<ノーマル会話：タグ展開用パラメータ
	u8 a_talk_id;					///<ノーマル会話ID(A_TALK_???)
	u8 after_a_talk_id;				///<ポイント加減算後に行うノーマル会話ID(A_TALK_???)

	u8 a_talk_bmpwin_close_wait;	///<メッセージを表示しきってからウィンドウを閉じるまでのwait
	u8 a_talk_bmpwin_not_close;		///<TRUE:ウィンドウを閉じずに終了
}NORMAL_TALK;

///審判被りメッセージ表示時に使用するパラメータ
typedef struct{
	u8 judge_no;		///対象審判番号
	u8 suffer_breeder[BREEDER_MAX];		///<対象審判を指名しているブリーダー(番兵はBREEDER_MAX)
	
	u16 dummy;
	u8 dummy2;
}JUDGE_SUFFER_REVIEW;

//--------------------------------------------------------------
/**
 * @brief   演技力部門進行パラメータ(現在技を出しているポケモンの進行パラメータ)
 */
//--------------------------------------------------------------
typedef struct{
	u8 now_breeder;					///<現在場に出ているブリーダーの番号
	u8 now_pos;						///<現在場に出ているブリーダーが何番目にアピールしているか
	u8 judge_no;					///<選んだ審判の番号
	u8 judge_reaction_type;			///<審判のリアクションタイプ
	
	u8 judge_select_breeder[JUDGE_MAX][BREEDER_MAX];	///その審判を指名したブリーダーNoが入る
	
//	u16 waza_no;					///<技番号
//	u8 now_sort[BREEDER_MAX];	///<現在のターンのアピール順(アピール順にブリーダーNoが入ってる)
	
	//技効果計算結果
//	s8 ap_point;			///<繰り出した技の基本AP値
//	s8 ap_point_calc;		///<繰り出した技の計算後の最終的なAP値
//	s8 voltage_now;			///<ボルテージ計算前の値
//	s8 voltage_calc;		///<出した技によって変更されたボルテージ値、計算後の値
//	s8 voltage_add_ap;		///<ボルテージによって増減するAP値
//	u8 judge_suffer;		///<指名した審判が被った人数
	
	AWAZA_PARAM wazapara;			///<技効果計算結果
//	u8 next_sort[BREEDER_MAX];		///<順番操作フラグ(AWK_SORT_???)
//	u8 next_pos[BREEDER_MAX];		///<順番操作が有効な時、ここに順番が入る
	
	NORMAL_TALK nt;			//通常メッセージ(技効果以外)
	
	union{
		JUDGE_SUFFER_REVIEW jsr;	//審判被りメッセージ表示時に使用するパラメータ
	};
}ACTIN_ADVANCE_PARAM;

//--------------------------------------------------------------
/**
 * @brief   演技力部門ゲーム進行パラメータ
 *
 * このパラメータがあれば全画面を再構築出来るだけの情報が入っています。
 * 通信時はサーバーから子機はデータを受け取る事になります。
 * 基本的にメニュー画面からの画面復帰のような事がない限り、
 * 個々の子機側で値を参照する事はないはずです。
 */
//--------------------------------------------------------------
typedef struct{
	u8 turn;						///<現在の経過ターン
	u8 breeder_sort[BREEDER_MAX];	///<技を出す順番(出る順にブリーダー番号が入ってます)
	u8 breeder_end_count;			///<行動が終了したブリーダーの数をカウント
	u16 waza_no[BREEDER_MAX];		///<現在のターン、各ブリーダーが出す技
	u8 judge_no[BREEDER_MAX];		///<現在のターン、各ブリーダーが選択した審判NO
	s16 app_total[BREEDER_MAX];		///<合計AP値
	s16 app_turn[BREEDER_MAX];		///<そのターンで稼いだAP値
	s8 voltage_total[JUDGE_MAX];	///<ボルテージ合計
	u16 waza_history[BREEDER_MAX];	///<前のターンで出した技の履歴
	AWAZA_PARAM wazapara;			///<技効果計算結果パラメータ
}ACTIN_GAME_PARAM;

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
}ACTIN_ORDER_PARAM;

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
	
	SOFT_SPRITE_MANAGER	*soft_sprite;
	SOFT_SPRITE *ss[BREEDER_MAX];
	CATS_SYS_PTR		csp;
	CATS_RES_PTR		crp;
	WE_SYS_PTR			wsp;
	GF_BGL_INI *bgl;
	GF_BGL_BMPWIN win[ACTIN_BMPWIN_MAX];
	MSGDATA_MANAGER *actin_msg;		///<演技力部門メッセージ用メッセージデータマネージャのポインタ
	MSGDATA_MANAGER *breeder_msg;	///<ブリーダーメッセージデータマネージャのポインタ
	MSGDATA_MANAGER *explain_msg;	///<技説明メッセージデータマネージャのポインタ
	MSGDATA_MANAGER *wazakouka_msg;	///<技効果メッセージデータマネージャのポインタ
	WORDSET *wordset;				///<Allocしたメッセージ用単語バッファへのポインタ
	STRBUF *msg_buf;				///<Allocした文字列バッファへのポインタ
	PALETTE_FADE_PTR pfd;			///<パレットフェードシステムへのポインタ
	FONTOAM_SYS_PTR fontoam_sys;	///<フォントOAMシステムへのポインタ

	EXCHR_PARAM exchr_param[BREEDER_MAX];		///<技エフェクト用キャラ展開バッファ
	EXCHR_PARAM transparent_exchr_param;		///<透明ソフトウェアスプライト用の展開バッファ
	
	CATS_ACT_PTR judge_cap[JUDGE_MAX];			///<審判アクターへのポインタ
	CATS_ACT_PTR judge_box_cap[JUDGE_MAX];		///<審判ボックスアクターへのポインタ
	CATS_ACT_PTR special_heart_cap;				///<特別審査員につけるハート
	CATS_ACT_PTR appeal_point_cap[BREEDER_MAX][APPEAL_POINT_ICON_MAX];
	CATS_ACT_PTR voltage_point_cap[JUDGE_MAX][VOLTAGE_MAX];
	CATS_ACT_PTR nexticon_cap[BREEDER_MAX];			///<次アイコンアクターへのポインタ
	CATS_ACT_PTR wincover_cap[WINCOVER_ACT_MAX];	///<会話ウィンドウスクロール時のカバー
	CATS_ACT_PTR judge_reaction_icon_cap;		///<審判リアクションアイコンアクター
	
	ADV_FONTACT fontact_oya[BREEDER_MAX];		///<親名のフォントアクター
	ADV_FONTACT fontact_nickname[BREEDER_MAX];	///<ニックネームのフォントアクター
	
	u8 talk_msg_index;				///<文字描画ルーチンのインデックス
}ACTIN_SYSTEM_PARAM;

//--------------------------------------------------------------
/**
 * デバッグでのみ使用するワーク
 */
//--------------------------------------------------------------
typedef struct{
	GF_BGL_BMPWIN win;
	s16 wazano;
	u8 sub_seq;
}ACTIN_DEBUG_WORK;

//--------------------------------------------------------------
/**
 * @brief   演技力部門管理ワーク
 *
 * 演技力部門全体を管理する大元のワークになります。
 * 通信時でも全てのマシンで個別に作成されます
 */
//--------------------------------------------------------------
typedef struct{
	CONTEST_SYSTEM *consys;			///<コンテストシステムワークへのポインタ
	TCB_PTR update_tcb;
	GF_G3DMAN *g3Dman;
	
	ACTIN_SYSTEM_PARAM sys;			///<演技力部門システムデータパラメータ
	ACTIN_GAME_PARAM a_game;			///<ゲーム進行パラメータ
	ACTIN_ADVANCE_PARAM advance;	///<進行パラメータ
	ACTIN_ORDER_PARAM order[BREEDER_MAX];	///<命令パラメータ
	
	void *aip;						///<サブ画面制御システム構造体へのポインタ
	
	u16 seq;
	u16 tbl_seq_no;					///<メインシーケンステーブルの番号
	u8 proc_mode;					///<現在の動作状況

	//-- 送受信バッファ --//
	u32 request_bit;				///<命令を出しているビット
	u8 transmit_buf[TRANSMIT_BUF_SIZE];	///<送信用バッファ
	u8 receive_buf[RECEIVE_BUF_SIZE];	///<受信用バッファ
	u8 transmit_flag;				///<TRUE：送信待ち。　FALSE:新たなデータセット可能
	u8 receive_flag;				///<TRUE：データ受信した
	
	CONTEST_ORDER_WORK cow;			///<送受信ワーク

	ACTIN_LOCAL_WORK local;			///<ローカルワーク
	u8 main_end;					///<TRUE:メイン処理終了
	
	u8 effect_count;				///<汎用エフェクトカウンタワーク
	
	u8  hensin_flag[BREEDER_MAX];	///<TRUE：変身状態
	
#ifdef PM_DEBUG
	ACTIN_DEBUG_WORK debug;			///<デバッグ用ワーク
#endif
}ACTIN_PROC_WORK;


//==============================================================================
//	外部データ宣言
//==============================================================================
extern const PROC_DATA ContestActinProcData;

//==============================================================================
//	外部関数宣言
//==============================================================================
extern PROC_RESULT ActinProc_Init( PROC * proc, int * seq );
extern PROC_RESULT ActinProc_Main( PROC * proc, int * seq );
extern PROC_RESULT ActinProc_End( PROC * proc, int * seq );
extern void ActinBG_BrdPanelSet(ACTIN_PROC_WORK *apw, int eff_bg_type, int disp_set);

//--------------------------------------------------------------
//	actin_waza.c
//--------------------------------------------------------------
extern void AWAZA_WazaParaTurnInit(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp);
extern void AWAZA_WazaParaBreederInit(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int breeder_no);
extern void AWAZA_WazaParaBreederGameUpdate(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int breeder_no);
extern void AWAZA_WazaParaTurnGameUpdate(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp);
extern void AWAZA_FirstMsg(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int breeder_no);
extern void AWAZA_BaseAP(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int breeder_no);
extern void AWAZA_Kouka(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, 
	int now_breeder, int now_breeder_pos);
extern void AWAZA_KoukaSpecial(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, 
	int now_breeder, int now_breeder_pos);
extern BOOL AWAZA_KoukaAfterTiming(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int now_breeder, 
	int now_breeder_pos);
extern BOOL AWAZA_KoukaJudgeSufferTiming(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int now_breeder, 
	int now_breeder_pos);
extern BOOL AWAZA_KoukaEndTiming(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int now_breeder, 
	int now_breeder_pos);
extern void AWAZA_Voltage(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int breeder_no, NORMAL_TALK *nt);
extern void AWAZA_JudgeSuffer(ACTIN_PROC_WORK *apw, AWAZA_PARAM *wp, int now_breeder, 
	NORMAL_TALK *nt);
extern void AWAZA_TimingBeforeAppUpdate(AWAZA_PARAM *wp);

//--------------------------------------------------------------
//	actin_ai.c
//--------------------------------------------------------------
extern void ActinAI_Main(ACTIN_PROC_WORK *apw, ACTIN_AI_ANSWER *answer);


#endif	//__ACTIN_H__

