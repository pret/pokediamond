//==============================================================================
/**
 * @file	actin_tool.c
 * @brief	演技力部門で使用するツール類
 * @author	matsuda
 * @date	2005.11.24(木)
 */
//==============================================================================
#include "common.h"
#include "contest/contest.h"
#include "actin.h"
#include "actin_tcb_pri.h"
#include "battle/battle_common.h"
#include "system/clact_tool.h"
#include "system/palanm.h"

#include "system/arc_tool.h"
#include "system/arc_util.h"

#include "system/softsprite.h"

#include "system/fontproc.h"
#include "system/msgdata.h"

#include "wazaeffect/battle_particle.h"
#include "system/particle.h"
#include "wazaeffect/we_mana.h"
#include "wazaeffect/we_sys.h"

#include "system/brightness.h"

#include "graphic/contest_bg_def.h"
#include "graphic/contest_obj_def.h"

#include "actin_tool.h"
#include "con_tool.h"
#include "actin_id.h"

#include "msgdata/msg.naix"
#include "msgdata/msg_cmsg_acting.h"

#include "system/snd_tool.h"
#include "application/app_tool.h"
#include "savedata/config.h"

#include "battle/wazano_def.h"
#include "battle/battle_server.h"


//==============================================================================
//	定数定義
//==============================================================================
///ブリーダーパネルのドット幅X
#define BREEDER_PANEL_DOT_LEN_X		(10 * 8)
///ブリーダーパネルのドット幅Y
#define BREEDER_PANEL_DOT_LEN_Y		(BREEDER_PANEL_Y_LEN * 8)

//--------------------------------------------------------------
//	BMPウィンドウ
//--------------------------------------------------------------
///パネルのBMPエリアを埋め尽くす場合に使用するカラー番号
#define BMPWIN_PANEL_FILL_COLOR			(2)

///会話ウィンドウカバーのスクリーン位置(スクロール前)
#define WINSLIDE_SCRN_POS_BEFORE		(32 * 0x12 + 0x15)
///会話ウィンドウカバーのスクリーン位置(スクロール後)
#define WINSLIDE_SCRN_POS_AFTER			(32 * 0x12 + 0x1e)
///会話ウィンドウスライド速度(下位8ビット小数)
#define TALKWIN_SLIDE_SPEED		(0x0400)
///会話ウィンドウのスライド距離(ドット単位)
#define TALKWIN_SLIDE_DOT_LEN	(9 * 8 + FRAME_WIN_DEFAULT_X)

///ブリーダーパネルのαスピード(下位8ビット小数)
#define BRDPANEL_ALPHA_SP		(0x0800)	//(0x0500)

///観客アニメのウェイト
#define AUDIENCE_ANIME_WAIT		(2)
///観客アニメの繰り返し回数
#define AUDIENCE_ANIME_LOOP		2	//(8)
///観客フェードのEVY最大値
#define AUDIENCE_FADE_MAX_EVY		(EVY_MAX)
///観客フェードのEVY加算値
#define AUDIENCE_FADE_ADD_EVY		(2)
///観客フェードのEVYのカラー開始位置
#define AUDIENCE_FADE_COLOR_POS		(0 * 16 + 1)
///観客フェードのカラー開始位置からの変更カラー数
#define AUDIENCE_FADE_COLOR_NUM		(2)
///観客フェードの変更後のカラー
#define AUDIENCE_FADE_RGB			(0x237e)

///アピールアイコンエフェクト：拡縮率の初期値
#define APICON_EFF_INIT_SCALE		(0.1f)
///アピールアイコンエフェクト：拡縮率の最大値
#define APICON_EFF_MAX_SCALE		(1.5f)
///アピールアイコンエフェクト：通常の拡縮率
#define APICON_EFF_NORMAL_SCALE		(1.0f)
///アピールアイコンエフェクト：加算拡縮率
#define APICON_EFF_ADD_SCALE		(0.3f)
///アピールアイコンエフェクト：回転速度
#define APICON_EFF_ADD_ROTATION		(0)//(0x2000)

///審判動作、指名：移動量(下位8ビット小数)
#define JUDGE_NOMINATION_ADD_Y		(0x0180)
///審判動作、指名：移動繰り返し回数
#define JUDGE_NOMINATION_LOOP		(2)

///審判動作、被り：移動量X(下位8ビット小数)
#define JUDGE_WEAR_ADD_X			(0x0200)
///審判動作、被り：移動繰り返し回数
#define JUDGE_WEAR_LOOP				(4)

///審判動作、ジャンプ：指名のジャンプ力
#define JUDGE_JUMP_NOMINATION_POWER			(0x0200)
///審判動作、ジャンプ：ボルテージ時のジャンプ力
#define JUDGE_JUMP_VOLTAGE_UP_POWER			(0x0300)
///審判動作、ジャンプ：ボルテージMAX時のジャンプ力
#define JUDGE_JUMP_VOLTAGE_MAX_UP_POWER		(0x0400)
///審判動作、ジャンプ：審判被り、でかい
#define JUDGE_JUMP_SUFFER_BIG				(0x0480)
///審判動作、ジャンプ：審判被り、中くらい
#define JUDGE_JUMP_SUFFER_MIDDLE			(0x0280)
///審判動作、ジャンプ：審判被り、小さい
#define JUDGE_JUMP_SUFFER_SMALL				(0x0100)
///審判動作、ジャンプ：重力
#define JUDGE_JUMP_GRAVITY			(0x0100 / 2)

///ボルテージ移動：最初の移動にかけるフレーム数
#define VOLTAGE_MOVE_FIRST_FRAME		(10)//(15)
///ボルテージ移動：最後の移動にかけるフレーム数
#define VOLTAGE_MOVE_END_FRAME			(6)	//(10)
///ボルテージ移動：最初の移動が終わった後に発生するウェイト
#define VOLTAGE_MOVE_FIRST_WAIT			(3)//(4)
///ボルテージ移動：最後の移動が終わった後に発生するウェイト
#define VOLTAGE_MOVE_END_WAIT			(2)//(4)
///ボルテージ移動：アクターアニメの回転角加算値
#define VOLTAGE_MOVE_ADD_ROTATION		(0x2000)

///APハートが動き出すまでのウェイト(2個目の以降のハートが横にスライドするスピードに影響する)
#define APHEART_START_WAIT			(3)
///毎フレームのふり幅減算値
#define APHEART_SUB_FURIHABA		(0x0300)//(0x0200)
///ふり幅がこの値以下になったら終了
#define APHEART_END_FURIHABA		(0x0200)
///回転速度
#define APHEART_ADD_ANGLE			(0x800)//(0xb00)
///毎フレームの回転速度加算値
#define APHEART_ADD_FRAME_ANGLE		(0)

///ボルテージ移動：エフェクト開始までのウェイト
#define VOLMOVE_START_WAIT		(12)
///ボルテージ移動：ふり幅X
#define VOLMOVE_FURIHABA_X		(12 << FX32_SHIFT)
///ボルテージ移動：ふり幅Y
#define VOLMOVE_FURIHABA_Y		(6 << FX32_SHIFT)
///ボルテージ移動：角度加算値
#define VOLMOVE_ADD_ANGLE		(0x800)
///ボルテージ移動：直線移動速度X(下位8ビット小数)　この速度を基準にY速度も決定される
#define VOLMOVE_STRAIGHT_SP_X	(0x0300)
///ボルテージ移動：下降移動するフレーム数
#define VOLMOVE_DOWNMOVE_FRAME	(80)
///ボルテージ移動：下降時の速度Y(下位8ビット小数)
#define VOLMOVE_DOWNMOVE_SP_Y	(0x0080)

///ブリーダーパネル：フラッシュの開始EVY値(下位8ビット小数)
#define PANEL_FLASH_START_EVY		(10 << 8)
///ブリーダーパネル：フラッシュのEVY減算値(下位8ビット小数)
#define PANEL_FLASH_SUB_EVY		(0x280)
///ブリーダーパネル：フラッシュのカラーコード
#define PANEL_FLASH_RGB			(0x7fff)
///ブリーダーパネル：フラッシュの開始カラー位置
#define PANEL_FLASH_START_POS	(1)
///ブリーダーパネル：フラッシュの対象カラー数
#define PANEL_FLASH_COLOR_NUM	(4)


//==============================================================================
//	構造体定義
//==============================================================================
///会話ウィンドウスライドタスクで使用するワーク
typedef struct{
	ACTIN_SYSTEM_PARAM *sys;
	u8 *end_flag;	///<終了フラグをセットするワークへのポインタ
	
	s32 x;		///<下位8ビット小数
	u8 seq;
	u8 slide_dir;	///<スライド方向
}TALKWIN_SLIDE_WORK;

///ブリーダーパネルαエフェクトタスクで使用するワーク
typedef struct{
	ACTIN_PROC_WORK *apw;
	u8 *end_flag;	///<終了フラグをセットするワークへのポインタ
	
	s16 eva;
	s16 evb;
	u8 seq;
	u8 eff_type;
}BRDPANEL_ALPHA_WORK;

///観客アニメワーク
typedef struct{
	ACTIN_PROC_WORK *apw;
	int se_volume;		///<歓声SEのボリューム
	u8 seq;				///<シーケンス
	u8 anm_no;			///<現在実行中のアニメパターン
	u8 loop;			///<アニメ繰り返し回数カウント
	u8 voltage;			///<ボルテージ値
	u8 wait;			///<アニメウェイト
	u8 start_wait;		///<開始までのウェイト
	u8 fade;			///<フェードの有無
	s8 evy;				///<フェードのEVY値
	u8 *end_flag;		///<終了時、ここに終了フラグ(TRUE)をセットする
}AUDIENCE_ANIME_WORK;

///アピールポイントアイコン登場エフェクト用のワーク
typedef struct{
	CATS_ACT_PTR cap;
	f32 sx;
	f32 sy;
	u8 seq;
	u8 wait;
}APPEAL_POINT_APPEAR_WORK;

///APハート回転移動動作用ワーク
typedef struct{
	ACTIN_PROC_WORK *apw;	///<演技力部門管理ワークへのポインタ
	PANEL_FLASH_WORK *panel_flash;	///<パネルフラッシュ動作ワークへのポインタ
	CATS_ACT_PTR cap;		///<対象となるハートのアクターポインタ
	u8 *effect_count;		///<エフェクトカウンタワークへのポインタ
	u32 furihaba;			///<ふり幅(下位8ビット小数)
	u32 add_angle;			///<角度加算値
	s32 slide_x;			///<スライド時の現在座標X(下位8ビット小数)
	u16 slide_add_x;		///<横にスライドしていく時の速度X(下位8ビット小数)
	u16 angle;				///<現在の角度(整数100倍)
	u8 seq;					///<シーケンス番号
	u8 center_x;			///<Sinカーブ中心座標X
	u8 center_y;			///<Sinカーブ中心座標Y
	u8 start_x;				///<Sinカーブ開始位置X
	u8 start_y;				///<Sinカーブ開始位置Y
}APHEART_MOVE_WORK;

///審判リアクション動作用ワーク
typedef struct{
	ACTIN_PROC_WORK *apw;		///<演技力部門管理ワークへのポインタ
	u8 *end_flag;				///<エフェクト終了時にここに終了の返事としてTRUEを入れる
	u8 judge_no;				///<審判No
	s8 wait;					///<汎用ウェイト
	u8 seq;						///<シーケンスNo
	
	s16 start_x;				///<審判初期座標X
	s16 start_y;				///<審判初期座標Y
	s32 x;						///<現在座標X(下位8ビット小数)
	s32 y;						///<現在座標Y(下位8ビット小数)
	u8 loop;
	union{
		struct{
			u8 dummy;
		}nom;
		struct{
			u8 dummy;
		}wear;
		struct{
			s32 x;
			s32 y;
			s16 up_power;		///<ジャンプ力
			s16 backup_up_power;		///<ジャンプ力
		}jump;
	};
}JUDGE_REACTION_MOVE_WORK;

///ボルテージ移動エフェクト用ワーク
typedef struct{
	ACTIN_SYSTEM_PARAM *sys;
	CATS_ACT_PTR cap;				///<ボルテージ演出のアクターポインタ
	CATS_ACT_PTR voltage_cap;		///<ボルテージポイントのアクターポインタ
	fx32 theta;			///<角度(下位8ビット小数)
	s32 x;				///<現在座標X(下位8ビット小数)
	s32 y;				///<現在座標Y(下位8ビット小数)
	s32 temp_x;
	s32 temp_y;
	s32 move_end_x;		///<移動用の途中停止ポイントX
	s32 move_end_y;		///<移動用の途中停止ポイントY
	s16 add_x;			///<X加算値(下位8ビット小数)
	s16 add_y;			///<Y加算値(下位8ビット小数)
	
	u8 end_x;			///<終点座標X
	u8 end_y;			///<終点座標Y
	
	u8 seq;				///<シーケンス番号
	u8 wait;			///<ウェイトカウント
	
	//いらないかも、なデータ
	u8 judge_no;		///<審判NO
	u8 point;			///<ボルテージポイント
}VOLTAGE_MOVE_WORK;

///ボルテージポイント,パネル移動用ワーク
typedef struct{
	ACTIN_PROC_WORK *apw;	///<演技力部門管理ワークへのポインタ
	CATS_ACT_PTR cap;		///<対象となるハートのアクターポインタ
	u8 *effect_count;		///<エフェクトカウンタワークへのポインタ
	u16 angle;				///<現在の角度(整数100倍)
	u8 seq;					///<シーケンス番号
	u8 center_x;			///<パネル中心座標X
	u8 center_y;			///<パネル中心座標Y
	s32 add_x;				///<X移動加算値
	s32 add_y;				///<Y移動加算値
	s32 x;					///<現在X座標(下位8ビット小数)
	s32 y;					///<現在X座標(下位8ビット小数)
	s16 wait;
}VOLPANEL_MOVE_WORK;

//==============================================================================
//	データ
//==============================================================================
///審判アクターヘッダ
static const TCATS_OBJECT_ADD_PARAM_S JudgeObjParam = {
	JUDGE_POS_X_0, JUDGE_POS_Y_0, 0,		//x, y, z
	0, ACTIN_SOFTPRI_JUDGE, 0,		//アニメ番号、優先順位、パレット番号
	NNS_G2D_VRAM_TYPE_2DMAIN,		//描画エリア
	{	//使用リソースIDテーブル
		0,	//キャラ
		0,	//パレット
		0,	//セル
		0,	//セルアニメ
		CLACT_U_HEADER_DATA_NONE,		//マルチセル
		CLACT_U_HEADER_DATA_NONE,		//マルチセルアニメ
	},
	ACTIN_BGPRI_JUDGE,			//BGプライオリティ
	0,			//Vram転送フラグ
};

///審判ボックスアクターヘッダ
static const TCATS_OBJECT_ADD_PARAM_S JudgeBoxObjParam = {
	JUDGE_BOX_POS_X_0, JUDGE_BOX_POS_Y_0, 0,		//x, y, z
	0, ACTIN_SOFTPRI_JUDGE_BOX, PALOFS_JUDGE_BOX_LEFT,		//アニメ番号、優先順位、パレット番号
	NNS_G2D_VRAM_TYPE_2DMAIN,		//描画エリア
	{	//使用リソースIDテーブル
		CHARID_JUDGE_BOX,	//キャラ
		PLTTID_OBJ_COMMON,	//パレット
		CELLID_JUDGE_BOX,	//セル
		CELLANMID_JUDGE_BOX,	//セルアニメ
		CLACT_U_HEADER_DATA_NONE,		//マルチセル
		CLACT_U_HEADER_DATA_NONE,		//マルチセルアニメ
	},
	ACTIN_BGPRI_JUDGE,			//BGプライオリティ
	0,			//Vram転送フラグ
};

///特別審査員につけるハートのアクターヘッダ
static const TCATS_OBJECT_ADD_PARAM_S SpecialHeartObjParam = {
	0, 0, 0,		//x, y, z
	0, ACTIN_SOFTPRI_SPECIAL_HEART, PALOFS_SPECIAL_HEART,	//アニメ番号、優先順位、パレット番号
	NNS_G2D_VRAM_TYPE_2DMAIN,		//描画エリア
	{	//使用リソースIDテーブル
		CHARID_SPECIAL_HEART,	//キャラ
		PLTTID_OBJ_COMMON,	//パレット
		CELLID_SPECIAL_HEART,	//セル
		CELLANMID_SPECIAL_HEART,	//セルアニメ
		CLACT_U_HEADER_DATA_NONE,		//マルチセル
		CLACT_U_HEADER_DATA_NONE,		//マルチセルアニメ
	},
	ACTIN_BGPRI_JUDGE,			//BGプライオリティ
	0,			//Vram転送フラグ
};

///アピールポイントハートのアクターヘッダ
static const TCATS_OBJECT_ADD_PARAM_S AppealPointObjParam = {
	0, 0, 0,		//x, y, z
	0, ACTIN_SOFTPRI_APPEAL_POINT, PALOFS_APPEAL_POINT,	//アニメ番号、優先順位、パレット番号
	NNS_G2D_VRAM_TYPE_2DMAIN,		//描画エリア
	{	//使用リソースIDテーブル
		CHARID_APPEAL_POINT,	//キャラ
		PLTTID_OBJ_COMMON,	//パレット
		CELLID_APPEAL_POINT,	//セル
		CELLANMID_APPEAL_POINT,	//セルアニメ
		CLACT_U_HEADER_DATA_NONE,		//マルチセル
		CLACT_U_HEADER_DATA_NONE,		//マルチセルアニメ
	},
	ACTINSUB_BGPRI_APPEAL_POINT,			//BGプライオリティ
	0,			//Vram転送フラグ
};

///ボルテージポイントハートのアクターヘッダ
static const TCATS_OBJECT_ADD_PARAM_S VoltagePointObjParam = {
	0, 0, 0,		//x, y, z
	0, ACTIN_SOFTPRI_VOLTAGE_POINT, PALOFS_VOLTAGE_POINT,	//アニメ番号、優先順位、パレット番号
	NNS_G2D_VRAM_TYPE_2DMAIN,		//描画エリア
	{	//使用リソースIDテーブル
		CHARID_VOLTAGE_POINT,	//キャラ
		PLTTID_OBJ_COMMON,	//パレット
		CELLID_VOLTAGE_POINT,	//セル
		CELLANMID_VOLTAGE_POINT,	//セルアニメ
		CLACT_U_HEADER_DATA_NONE,		//マルチセル
		CLACT_U_HEADER_DATA_NONE,		//マルチセルアニメ
	},
	ACTINSUB_BGPRI_VOLTAGE_POINT,			//BGプライオリティ
	0,			//Vram転送フラグ
};

///ボルテージ演出のアクターヘッダ
static const TCATS_OBJECT_ADD_PARAM_S VoltageEffectObjParam = {
	0, 0, 0,		//x, y, z
	0, ACTIN_SOFTPRI_VOLTAGE_EFF, PALOFS_VOLTAGE_EFF,	//アニメ番号、優先順位、パレット番号
	NNS_G2D_VRAM_TYPE_2DMAIN,		//描画エリア
	{	//使用リソースIDテーブル
		CHARID_VOLTAGE_EFF,	//キャラ
		PLTTID_OBJ_COMMON,	//パレット
		CELLID_VOLTAGE_EFF,	//セル
		CELLANMID_VOLTAGE_EFF,	//セルアニメ
		CLACT_U_HEADER_DATA_NONE,		//マルチセル
		CLACT_U_HEADER_DATA_NONE,		//マルチセルアニメ
	},
	ACTIN_BGPRI_VOLTAGE_EFF,			//BGプライオリティ
	0,			//Vram転送フラグ
};

///次アイコンのアクターヘッダ
static const TCATS_OBJECT_ADD_PARAM_S NextIconObjParam = {
	0, 0, 0,		//x, y, z
	0, ACTIN_SOFTPRI_NEXT_ICON, PALOFS_NEXT_ICON,	//アニメ番号、優先順位、パレット番号
	NNS_G2D_VRAM_TYPE_2DMAIN,		//描画エリア
	{	//使用リソースIDテーブル
		CHARID_NEXT_ICON,	//キャラ
		PLTTID_OBJ_COMMON,	//パレット
		CELLID_NEXT_ICON,	//セル
		CELLANMID_NEXT_ICON,	//セルアニメ
		CLACT_U_HEADER_DATA_NONE,		//マルチセル
		CLACT_U_HEADER_DATA_NONE,		//マルチセルアニメ
	},
	ACTINSUB_BGPRI_NEXT_ICON,			//BGプライオリティ
	0,			//Vram転送フラグ
};

///会話ウィンドウカバーのアクターヘッダ
static const TCATS_OBJECT_ADD_PARAM_S WinCoverObjParam = {
	0, 0, 0,		//x, y, z
	0, 10, 0,		//アニメ番号、優先順位、パレット番号
	NNS_G2D_VRAM_TYPE_2DMAIN,		//描画エリア
	{	//使用リソースIDテーブル
		CHARID_WIN_COVER_0,	//キャラ
		PLTTID_WIN_COVER,	//パレット
		CELLID_WIN_COVER,	//セル
		CELLANMID_WIN_COVER,	//セルアニメ
		CLACT_U_HEADER_DATA_NONE,		//マルチセル
		CLACT_U_HEADER_DATA_NONE,		//マルチセルアニメ
	},
	0,			//BGプライオリティ
	0,			//Vram転送フラグ
};

///審判リアクションアイコンのアクターヘッダ
static const TCATS_OBJECT_ADD_PARAM_S JudgeReactionObjParam = {
	0, 0, 0,		//x, y, z
	0, ACTIN_SOFTPRI_JUDGE_REACTION, PALOFS_JUDGE_REACTION,	//アニメ番号、優先順位、パレット番号
	NNS_G2D_VRAM_TYPE_2DMAIN,		//描画エリア
	{	//使用リソースIDテーブル
		CHARID_JUDGE_REACTION,	//キャラ
		PLTTID_OBJ_COMMON,	//パレット
		CELLID_JUDGE_REACTION,	//セル
		CELLANMID_JUDGE_REACTION,	//セルアニメ
		CLACT_U_HEADER_DATA_NONE,		//マルチセル
		CLACT_U_HEADER_DATA_NONE,		//マルチセルアニメ
	},
	ACTIN_BGPRI_JUDGE_REACTION,			//BGプライオリティ
	0,			//Vram転送フラグ
};


//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///アピールポイントアイコンを出す座標(一番左側の座標)
ALIGN4 static const s16 AppealPointPos[BREEDER_MAX][2] = {	//X, Y
	{5, 5*8 + 3},
	{5, 11*8 + 3},
	{5, 17*8 + 3},
	{5, 23*8 + 3},
};

///ボルテージポイントアイコンを出す座標(一番左側の座標)
ALIGN4 static const s16 VoltagePointPos[JUDGE_MAX][2] = {	//X, Y
	{10*8 + 8 + 32*0, 1*8 + 4},
	{10*8 + 8 + 32*1, 1*8 + 4},
	{10*8 + 8 + 32*2, 1*8 + 4},
};
///ボルテージと隣のボルテージの隙間X
#define VOLTAGE_SPACE_X		(5)

///審判リアクションアイコンの表示座標
static const struct{
	s16 x;
	s16 y;
}JudgeReactionIconPos[] = {
	{JUDGE_BOX_POS_X_0 + JUDGE_BOX_POS_X_SPACE * 0, JUDGE_BOX_POS_Y_0 - 12},
	{JUDGE_BOX_POS_X_0 + JUDGE_BOX_POS_X_SPACE * 1, JUDGE_BOX_POS_Y_0 - 12},
	{JUDGE_BOX_POS_X_0 + JUDGE_BOX_POS_X_SPACE * 2, JUDGE_BOX_POS_Y_0 - 12},
};

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///演技力部門ノーマル会話メッセージデータ	※A_TALK_???の定義と並びを同じにしておく事！！
static const ACTIN_MESSAGE_PARAM ActinTalkMsgData[] = {
	{0,									ATAG_NONE,		FALSE},	//ダミー

	{CAMSG_TALK_SELECT_JUDGE,			ATAG_NUM,		TRUE},
	{CAMSG_TALK_SELECT_WAZA,			ATAG_NUM,		TRUE},
	{CAMSG_TALK_SELECT_WAZA0002,		ATAG_NUM,		TRUE},
	{CAMSG_TALK_WAZA_APPEAL,			ATAG_MINE_JUDGE_WAZA,	FALSE},
	{CAMSG_TALK_JUDGE_LOOK,				ATAG_NONE,		FALSE},		///<表示位置変更
	{CAMSG_TALK_JUDGE_SUFFER,			ATAG_JUDGE,		FALSE},	//削除
	{CAMSG_TALK_JUDGE_SUFFER0002,		ATAG_EXCODE_JUDGESUFFER,	FALSE},
	{CAMSG_TALK_JUDGE_SUFFER0003,		ATAG_EXCODE_JUDGESUFFER,	FALSE},
	{CAMSG_TALK_JUDGE_SUFFER0004,		ATAG_EXCODE_JUDGESUFFER,	FALSE},
	{CAMSG_TALK_NO_JUDGE_SUFFER,		ATAG_EXCODE_JUDGESUFFER,	FALSE},
	{CAMSG_TALK_VOLTAGE_UP_1,			ATAG_JUDGE,		FALSE},
	{CAMSG_TALK_VOLTAGE_UP_2,			ATAG_JUDGE,		FALSE},
	{CAMSG_TALK_VOLTAGE_UP_3,			ATAG_JUDGE,		FALSE},
	{CAMSG_TALK_VOLTAGE_UP_4,			ATAG_JUDGE,		FALSE},
	{CAMSG_TALK_VOLTAGE_UP_5,			ATAG_JUDGE,		FALSE},
	{CAMSG_TALK_VOLTAGE_UP_6,			ATAG_JUDGE,		FALSE},
	{CAMSG_TALK_VOLTAGE_SUB_1,			ATAG_JUDGE,		FALSE},
	{CAMSG_TALK_VOLTAGE_SUB_10,			ATAG_JUDGE,		FALSE},
	{CAMSG_TALK_VOLTAGE_SUB_2,			ATAG_JUDGE,		FALSE},
	{CAMSG_TALK_VOLTAGE_SUB_3,			ATAG_JUDGE,		FALSE},
	{CAMSG_TALK_VOLTAGE_SUB_4,			ATAG_JUDGE,		FALSE},
	{CAMSG_TALK_VOLTAGE_SUB_5,			ATAG_JUDGE,		FALSE},
	{CAMSG_TALK_VOLTAGE_STATE_UP_2,		ATAG_NONE,		FALSE},
	{CAMSG_TALK_VOLTAGE_STATE_UP_3,		ATAG_NONE,		FALSE},
	{CAMSG_TALK_VOLTAGE_STATE_UP_4,		ATAG_NONE,		FALSE},
	{CAMSG_TALK_VOLTAGE_STATE_UP_5,		ATAG_NUM,		FALSE},
	{CAMSG_TALK_VOLTAGE_STATE_SUB_3,	ATAG_NONE,		FALSE},
	{CAMSG_TALK_VOLTAGE_STATE_SUB_2,	ATAG_NONE,		FALSE},
	{CAMSG_TALK_VOLTAGE_STATE_SUB_1,	ATAG_NONE,		FALSE},
	{CAMSG_TALK_VOLTAGE_STATE_SUB_0,	ATAG_NONE,		FALSE},
	{CAMSG_TALK_TURN_RESULT_0,			ATAG_MINE,		FALSE},
	{CAMSG_TALK_TURN_RESULT_1,			ATAG_MINE,		FALSE},
	{CAMSG_TALK_TURN_RESULT_2,			ATAG_MINE,		FALSE},
	{CAMSG_TALK_TURN_RESULT_3,			ATAG_MINE,		FALSE},
	{CAMSG_TALK_TURN_RESULT_4,			ATAG_MINE,		FALSE},
	{msg_con_act_host_01,				ATAG_NONE,		FALSE},
	{msg_con_act_host_02,				ATAG_NONE,		FALSE},
	{msg_con_act_host_03,				ATAG_NONE,		FALSE},
	{msg_con_act_host_04,				ATAG_NONE,		FALSE},
	{msg_con_act_host_05,				ATAG_NONE,		FALSE},
	{msg_con_act_host_06,				ATAG_NONE,		FALSE},
	{msg_con_a_explain_01,				ATAG_NONE,		FALSE},
	{msg_con_a_explain_02,				ATAG_NONE,		FALSE},
	{msg_con_a_prac_apreface,			ATAG_NONE,		FALSE},
	{msg_con_a_prac_01,					ATAG_NONE,		FALSE},
	{msg_con_a_caution_01,				ATAG_NONE,		TRUE},	//つうしん　たいきちゅう…
};


//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///観客の歓声のボリューム
ALIGN4 static const int AudienceVolume[] = {
	0, ACTIN_AUDIENCE_VOLUME - 30, ACTIN_AUDIENCE_VOLUME, ACTIN_AUDIENCE_VOLUME + 30,
};
///ボリュームレベル最大
#define AUDIENCE_VOLUME_LEVEL_MAX		(NELEMS(AudienceVolume))
///何点毎にボリュームのレベルを上げていくか
#define AUDIENCE_VOLUME_LEVEL_POINT		(50)


//==============================================================================
//	プロトタイプ宣言
//==============================================================================
static void TalkWinSlideInOutMain(TCB_PTR tcb, void *work);
void AT_BreederPanelFontOamCreate(ACTIN_PROC_WORK *apw, int breeder_no);
void AT_BreederPanelFontOamCreateAll(ACTIN_PROC_WORK *apw);
void AT_BreederPanelFontOamDeleteAll(ACTIN_PROC_WORK *apw);
void AT_BreederPanelFontOamPosUpdate(ACTIN_PROC_WORK *apw);
void AT_BrdPanelAlphaEffectSet(ACTIN_PROC_WORK *apw, int eff_type, u8 *end_flag);
static void BrdPanelAlphaEffMain(TCB_PTR tcb, void *work);
static void BrdPanelAlphaSet_VTask(TCB_PTR tcb, void *work);
static void AudienceAnimeMain(TCB_PTR tcb, void *work);
static void AppealPointAppearEffectSet(CATS_ACT_PTR cap);
static void AppealPointAppear(TCB_PTR tcb, void *work);
static void JudgeReactionMove_Nomination(TCB_PTR tcb, void *work);
static void JudgeReactionMove_Wear(TCB_PTR tcb, void *work);
static void JudgeReactionMove_Jump(TCB_PTR tcb, void *work);
static void APHeartMoveTask(TCB_PTR tcb, void *work);
static void VoltageAnimeUpdateTask(TCB_PTR tcb, void *work);
static void VoltageMoveTask(TCB_PTR tcb, void *work);
static void BreederPanel_FlashMain(TCB_PTR tcb, void *work);

//==============================================================================
//	データ
//==============================================================================
///各ブリーダーのパネルパレット番号
ALIGN4 const u8 BreederPanelScreenPalNo[] = {6, 7, 0xa, 0xb};


//--------------------------------------------------------------
/**
 * @brief   演技力画面のデフォルトブレンド設定を行う
 *
 * 技エフェクト側からも呼ばれる関数です
 */
//--------------------------------------------------------------
void ActinExTool_DefaultBlendSet(void)
{
	G2_BlendNone();
}

#if 0	//ブリーダー情報はOBJで表示するようになった
//--------------------------------------------------------------
/**
 * @brief   ブリーダー情報をパネルに描画する
 *
 * @param   apw				演技力管理ワークへのポインタ
 * @param   breeder_no		対象のブリーダー番号
 * @param   put_pos			描画するパネルの位置
 * @param   bmp_pal			BMPのパレット番号
 */
//--------------------------------------------------------------
void BreederParamBmpWrite(ACTIN_PROC_WORK *apw, int breeder_no, int put_pos, int bmp_pal)
{
	STRBUF *oyaname_buf, *nickname_buf;
	
	nickname_buf = STRBUF_Create(BUFLEN_POKEMON_NAME, HEAPID_ACTIN);
	oyaname_buf = STRBUF_Create(BUFLEN_PERSON_NAME, HEAPID_ACTIN);

	PokeParaGet(apw->sys.c_game->pp[breeder_no], ID_PARA_nickname_buf, nickname_buf);
	PokeParaGet(apw->sys.c_game->pp[breeder_no], ID_PARA_oyaname_buf, oyaname_buf);

	GF_BGL_BmpWinSet_Pal(&apw->sys.win[ACTIN_BMPWIN_BREEDER_0 + put_pos], bmp_pal);
	GF_BGL_BmpWinDataFill(&apw->sys.win[ACTIN_BMPWIN_BREEDER_0 + put_pos], 
		BMPWIN_PANEL_FILL_COLOR);
	
	GF_STR_PrintColor(&apw->sys.win[ACTIN_BMPWIN_BREEDER_0 + put_pos], FONT_SYSTEM, 
		nickname_buf, 0, 0, 
		MSG_NO_PUT, MSGCOLOR_BREEDERPARAM, NULL);
	GF_STR_PrintColor(&apw->sys.win[ACTIN_BMPWIN_BREEDER_0 + put_pos], FONT_SYSTEM, 
		oyaname_buf, 0, 16, 
		MSG_NO_PUT, MSGCOLOR_BREEDERPARAM, NULL);

	STRBUF_Delete(oyaname_buf);
	STRBUF_Delete(nickname_buf);
}

//--------------------------------------------------------------
/**
 * @brief   全てのブリーダーの情報をパネルに描画する
 * @param   apw				演技力管理ワークへのポインタ
 */
//--------------------------------------------------------------
void BreederParamBmpWriteAll(ACTIN_PROC_WORK *apw)
{
	int i, pal;
	
	for(i = 0; i < BREEDER_MAX; i++){
		if(apw->a_game.breeder_sort[i] == apw->consys->c_game.my_breeder_no){
			pal = MYBREEDER_PANEL_SCREEN_PAL;
		}
		else{
			pal = BREEDER_PANEL_SCREEN_PAL;
		}
		BreederParamBmpWrite(apw, apw->a_game.breeder_sort[i], i, pal);
	}
	//↑全て描画してからウィンドウON↓
	for(i = 0; i < BREEDER_MAX; i++){
		GF_BGL_BmpWinOn(&apw->sys.win[ACTIN_BMPWIN_BREEDER_0 + i]);
	}
}
#endif

//--------------------------------------------------------------
/**
 * @brief   ブリーダーパネルのカラー(スクリーン)を変更する
 *
 * @param   apw				演技力管理ワークへのポインタ
 * @param   breeder_pos		書き換えるパネルの位置
 * @param   pal_no			新たにセットするパレット番号
 */
//--------------------------------------------------------------
void BreederPanelColorChange(ACTIN_PROC_WORK *apw, int breeder_pos, int pal_no)
{
	u16 *scrbuf;
	int x, y;
	
	scrbuf = GF_BGL_ScreenAdrsGet(apw->sys.bgl, ACTIN_FRAME_BRDPANEL);
	scrbuf = &scrbuf[32 * (breeder_pos * BREEDER_PANEL_Y_LEN) + BREEDER_PANEL_SCREEN_START_POS];
	for(y = 0; y < BREEDER_PANEL_Y_LEN; y++){
		for(x = 0; x < BREEDER_PANEL_X_LEN; x++){
			scrbuf[y * 32 + x] = (scrbuf[y * 32 + x] & 0x0fff) | (pal_no << 12);
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   全ブリーダーパネルのカラー(スクリーン)を変更する
 * @param   apw		演技力管理ワークへのポインタ
 *
 * breeder_sortに従って書き換えを行います
 */
//--------------------------------------------------------------
void BreederPanelColorChangeAll(ACTIN_PROC_WORK *apw)
{
	int i;
	
	for(i = 0; i < BREEDER_MAX; i++){
		BreederPanelColorChange(apw, i, BreederPanelScreenPalNo[apw->a_game.breeder_sort[i]]);
	}
	GF_BGL_LoadScreenV_Req(apw->sys.bgl, ACTIN_FRAME_BRDPANEL);
}

//--------------------------------------------------------------
/**
 * @brief   ブリーダーパネルのフラッシュ動作タスクを生成する
 *
 * @param   apw				演技力部門管理ワークへのポインタ
 * @param   breeder_no		ブリーダー番号
 *
 * @retval  生成したフラッシュ動作ワークへのポインタ
 */
//--------------------------------------------------------------
PANEL_FLASH_WORK * BreederPanel_FlashTaskSet(ACTIN_PROC_WORK *apw, int breeder_no)
{
	PANEL_FLASH_WORK *pfw;
	
	pfw = sys_AllocMemory(HEAPID_ACTIN, sizeof(PANEL_FLASH_WORK));
	MI_CpuClear8(pfw, sizeof(PANEL_FLASH_WORK));
	
	pfw->pfd = apw->sys.pfd;
	pfw->breeder_no = breeder_no;
	pfw->tcb = TCB_Add(BreederPanel_FlashMain, pfw, TCBPRI_ACTIN_BRDPANEL_FLASH);
	return pfw;
}

//--------------------------------------------------------------
/**
 * @brief   ブリーダーパネルのフラッシュ動作タスクを削除する
 * @param   pfw		フラッシュ動作ワークへのポインタ
 */
//--------------------------------------------------------------
void BreederPanel_FlashTaskDelete(PANEL_FLASH_WORK *pfw)
{
	GF_ASSERT(pfw->req == FALSE);
	TCB_Delete(pfw->tcb);
	sys_FreeMemoryEz(pfw);
}

//--------------------------------------------------------------
/**
 * @brief   ブリーダーパネルのフラッシュリクエストを設定する
 * @param   pfw		フラッシュ動作ワークへのポインタ
 */
//--------------------------------------------------------------
void BreederPanel_FlashReqSet(PANEL_FLASH_WORK *pfw)
{
	pfw->req = TRUE;
	pfw->evy = PANEL_FLASH_START_EVY;
}

//--------------------------------------------------------------
/**
 * @brief   ブリーダーパネルにフラッシュリクエストが発生しているかチェック
 * @param   pfw		フラッシュ動作ワークへのポインタ
 * @retval  TRUE:リクエスト発生中、FALSE:待機中
 */
//--------------------------------------------------------------
BOOL BreederPanel_FlashReqCheck(PANEL_FLASH_WORK *pfw)
{
	return pfw->req;
}

//--------------------------------------------------------------
/**
 * @brief   ブリーダーパネル：フラッシュ動作メインタスク
 * @param   tcb			TCBへのポインタ
 * @param   work		フラッシュ動作ワークへのポインタ
 */
//--------------------------------------------------------------
static void BreederPanel_FlashMain(TCB_PTR tcb, void *work)
{
	PANEL_FLASH_WORK *pfw = work;
	
	if(pfw->req == FALSE){
		return;
	}
	
	SoftFadePfd(pfw->pfd, FADE_MAIN_BG, 
		BreederPanelScreenPalNo[pfw->breeder_no] * 16 + PANEL_FLASH_START_POS,
		PANEL_FLASH_COLOR_NUM, pfw->evy >> 8, PANEL_FLASH_RGB);
	if(pfw->evy == 0){
		pfw->req = FALSE;
		return;
	}
	pfw->evy -= PANEL_FLASH_SUB_EVY;
	if(pfw->evy < 0){
		pfw->evy = 0;
	}
}

//--------------------------------------------------------------
/**
 * @brief   変身などの技エフェクト後、ソフトウェアスプライトの描画状態を復帰する為に、作り直す
 *
 * @param   sys				演技力システムワークへのポインタ
 * @param   breeder_no		ブリーダー番号
 */
//--------------------------------------------------------------
void AT_SoftSpriteHensinPop(ACTIN_SYSTEM_PARAM *sys, int breeder_no)
{
	SoftSpriteDel(sys->ss[breeder_no]);

	GF_ASSERT(sys->exchr_param[breeder_no].exchr_buffer != NULL);
	MI_CpuClear8(sys->exchr_param[breeder_no].exchr_buffer, EXCHR_BUFFER_SIZE);
	
	sys->ss[breeder_no] = ConTool_BreederPokemonAdd(sys->soft_sprite, breeder_no, 
		sys->c_game->pp[breeder_no], PARA_BACK, &sys->exchr_param[breeder_no], HEAPID_ACTIN, 
		ACTIN_POKEPOS_X-32*breeder_no, ACTIN_POKEPOS_Y-32*breeder_no, ACTIN_POKEPOS_Z);
	//表示OFF
	SoftSpriteParaSet(sys->ss[breeder_no], SS_PARA_VANISH, TRUE);
	SoftSpriteParaSet(sys->ss[breeder_no], SS_PARA_DRAW_STOP, TRUE);
	//反転セット
	{
		u32 monsno;
		monsno = PokeParaGet(sys->c_game->pp[breeder_no], ID_PARA_monsno, NULL);
		if(ContestPokeFlipCheck(monsno) == TRUE){
			SoftSpriteParaSet(sys->ss[breeder_no], SS_PARA_H_FLIP, TRUE);
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   全てのブリーダーのソフトウェアスプライト(ポケモン)を生成する
 *
 * @param   sys		演技力システムワークへのポインタ
 * @param   pp		全ブリーダーのポケモンパラメータが入っている配列へのポインタ
 */
//--------------------------------------------------------------
void AT_SoftSpriteAddAll(ACTIN_SYSTEM_PARAM *sys)
{
	int i;
	
	for(i = 0; i < BREEDER_MAX; i++){
		GF_ASSERT(sys->exchr_param[i].exchr_buffer == NULL);
		sys->exchr_param[i].exchr_buffer = sys_AllocMemory(HEAPID_ACTIN, EXCHR_BUFFER_SIZE);
		
		sys->ss[i] = ConTool_BreederPokemonAdd(sys->soft_sprite, i, sys->c_game->pp[i], 
			PARA_BACK, &sys->exchr_param[i], HEAPID_ACTIN, 
			ACTIN_POKEPOS_X-32*i, ACTIN_POKEPOS_Y-32*i, ACTIN_POKEPOS_Z);
		//表示OFF
		SoftSpriteParaSet(sys->ss[i], SS_PARA_VANISH, TRUE);
		SoftSpriteParaSet(sys->ss[i], SS_PARA_DRAW_STOP, TRUE);
		//反転セット
		{
			u32 monsno;
			monsno = PokeParaGet(sys->c_game->pp[i], ID_PARA_monsno, NULL);
			if(ContestPokeFlipCheck(monsno) == TRUE){
				SoftSpriteParaSet(sys->ss[i], SS_PARA_H_FLIP, TRUE);
			}
		}
	}
	
	GF_ASSERT(sys->transparent_exchr_param.exchr_buffer == NULL);
	sys->transparent_exchr_param.exchr_buffer = sys_AllocMemory(HEAPID_ACTIN, EXCHR_BUFFER_SIZE);
	sys->transparent_exchr_param.pal_index = sys->exchr_param[0].pal_index;	//ダミー
	sys->transparent_exchr_param.arcID = sys->exchr_param[0].arcID;	//ダミー
	//バッファクリア
	MI_CpuClear32(sys->transparent_exchr_param.exchr_buffer, EXCHR_BUFFER_SIZE);
}

//--------------------------------------------------------------
/**
 * @brief   全てのブリーダーのソフトウェアスプライト(ポケモン)を削除する
 * @param   sys		演技力システムワークへのポインタ
 */
//--------------------------------------------------------------
void AT_SoftSpriteDelAll(ACTIN_SYSTEM_PARAM *sys)
{
	int i;
	
	for(i = 0; i < BREEDER_MAX; i++){
		SoftSpriteDel(sys->ss[i]);
		sys_FreeMemoryEz(sys->exchr_param[i].exchr_buffer);
		sys->exchr_param[i].exchr_buffer = NULL;
	}
	sys_FreeMemoryEz(sys->transparent_exchr_param.exchr_buffer);
	sys->transparent_exchr_param.exchr_buffer = NULL;
}

//--------------------------------------------------------------
/**
 * @brief   審判アクターの生成とリソース登録
 *
 * @param   pfd			パレットフェードシステムへのポインタ
 * @param   csp			csp
 * @param   crp			crp
 * @param   judge		審判データへのポインタ
 * @param   judge_no	審判NO
 *
 * @retval  生成した審判アクターのポインタ
 */
//--------------------------------------------------------------
static CATS_ACT_PTR AT_JudgeAdd(PALETTE_FADE_PTR pfd, CATS_SYS_PTR csp, CATS_RES_PTR crp, 
	const JUDGE_DATA *judge, int judge_no)
{
	CATS_ACT_PTR judge_cap;
	TCATS_OBJECT_ADD_PARAM_S judge_head;
	
#if WAIT_FIX	//OBJコードによって使用する絵を変更する？
	switch(judge->obj_code){
	case 0:
		break;
	default:
		break;
	}
#else
	u32 char_id, pal_id, cell_id, anm_id;
	
	switch(judge_no){
	case 0:
		char_id = CON_GORGGEOUSM_NCGR_BIN;
		pal_id = CON_GORGGEOUSM_NCLR;
		cell_id = CON_GORGGEOUSM_NCER_BIN;
		anm_id = CON_GORGGEOUSM_NANR_BIN;
		break;
	case 1:
		char_id = CON_GENTLEMAN_NCGR_BIN;
		pal_id = CON_GENTLEMAN_NCLR;
		cell_id = CON_GENTLEMAN_NCER_BIN;
		anm_id = CON_GENTLEMAN_NANR_BIN;
		break;
	default:
		char_id = CON_IDOL_NCGR_BIN;
		pal_id = CON_IDOL_NCLR;
		cell_id = CON_IDOL_NCER_BIN;
		anm_id = CON_IDOL_NANR_BIN;
		break;
	}
	
	//-- リソースロード --//
	CATS_LoadResourceCharArc(csp, crp, ARC_CONTEST_OBJ, char_id, 1, 
		NNS_G2D_VRAM_TYPE_2DMAIN, CHARID_JUDGE_0 + judge_no);
	CATS_LoadResourcePlttWorkArc(pfd, FADE_MAIN_OBJ, csp, crp, 
		ARC_CONTEST_OBJ, pal_id, 0, 
		1, NNS_G2D_VRAM_TYPE_2DMAIN, PLTTID_JUDGE_0 + judge_no);
	CATS_LoadResourceCellArc(csp, crp, ARC_CONTEST_OBJ, cell_id, 1, 
		CELLID_JUDGE_0 + judge_no);
	CATS_LoadResourceCellAnmArc(csp, crp, ARC_CONTEST_OBJ, 
		anm_id, 1, CELLANMID_JUDGE_0 + judge_no);
	
	//-- アクター生成 --//
	judge_head = JudgeObjParam;
	judge_head.id[CLACT_U_CHAR_RES] = CHARID_JUDGE_0 + judge_no;
	judge_head.id[CLACT_U_PLTT_RES] = PLTTID_JUDGE_0 + judge_no;
	judge_head.id[CLACT_U_CELL_RES] = CELLID_JUDGE_0 + judge_no;
	judge_head.id[CLACT_U_CELLANM_RES] = CELLANMID_JUDGE_0 + judge_no;
	judge_head.x = JUDGE_POS_X_0 + JUDGE_POS_X_SPACE * judge_no;
	judge_head.y = JUDGE_POS_Y_0 + JUDGE_POS_Y_SPACE * judge_no;
	judge_cap = CATS_ObjectAdd_S(csp, crp, &judge_head);
	CATS_ObjectUpdate(judge_cap->act);
#endif

	return judge_cap;
}

//--------------------------------------------------------------
/**
 * @brief   審判アクター＆リソース削除
 *
 * @param   crp				crp
 * @param   judge_cap		審判アクターへのポインタ
 * @param   judge_no		審判No
 */
//--------------------------------------------------------------
static void AT_JudgeDel(CATS_RES_PTR crp, CATS_ACT_PTR judge_cap, int judge_no)
{
#if WAIT_FIX	//正規のADD方法がまだわからないので、削除もわからない
	;
#else
	//-- アクター削除 --//
	CATS_ActorPointerDelete_S(judge_cap);

	//-- リソース削除 --//
	CATS_FreeResourceChar(crp, CHARID_JUDGE_0 + judge_no);
	CATS_FreeResourcePltt(crp, PLTTID_JUDGE_0 + judge_no);
	CATS_FreeResourceCell(crp, CELLID_JUDGE_0 + judge_no);
	CATS_FreeResourceCellAnm(crp, CELLANMID_JUDGE_0 + judge_no);
#endif
}

//--------------------------------------------------------------
/**
 * @brief   審判ボックスのリソース登録
 *
 * @param   pfd			パレットフェードシステムへのポインタ
 * @param   csp			csp
 * @param   crp			crp
 *
 * 全ての審判ボックスで同じリソースを使いまわすようになっています。
 */
//--------------------------------------------------------------
static void AT_JudgeBoxResourceLoad(PALETTE_FADE_PTR pfd, CATS_SYS_PTR csp, CATS_RES_PTR crp)
{
	u32 char_id, cell_id, anm_id;
	
	char_id = JUDGE_BOX_NCGR_BIN;
	cell_id = JUDGE_BOX_NCER_BIN;
	anm_id = JUDGE_BOX_NANR_BIN;
	
	//-- リソースロード --//
	//パレットは常駐パレットを使用するのでロードなし
	CATS_LoadResourceCharArc(csp, crp, ARC_CONTEST_OBJ, char_id, 1, 
		NNS_G2D_VRAM_TYPE_2DMAIN, CHARID_JUDGE_BOX);
	CATS_LoadResourceCellArc(csp, crp, ARC_CONTEST_OBJ, cell_id, 1, 
		CELLID_JUDGE_BOX);
	CATS_LoadResourceCellAnmArc(csp, crp, ARC_CONTEST_OBJ, 
		anm_id, 1, CELLANMID_JUDGE_BOX);
}

//--------------------------------------------------------------
/**
 * @brief   審判ボックスアクターの生成
 *
 * @param   csp			csp
 * @param   crp			crp
 * @param   judge_no	審判NO
 *
 * @retval  生成した審判ボックスアクターのポインタ
 */
//--------------------------------------------------------------
static CATS_ACT_PTR AT_JudgeBoxActorAdd(CATS_SYS_PTR csp, CATS_RES_PTR crp, int judge_no)
{
	CATS_ACT_PTR box_cap;
	TCATS_OBJECT_ADD_PARAM_S box_head;
	const int judge_palofs[] = {
		PALOFS_JUDGE_BOX_LEFT, PALOFS_JUDGE_BOX_CENTER, PALOFS_JUDGE_BOX_RIGHT,
	};
	
	//-- アクター生成 --//
	box_head = JudgeBoxObjParam;
	box_head.x = JUDGE_BOX_POS_X_0 + JUDGE_BOX_POS_X_SPACE * judge_no;
	box_head.y = JUDGE_BOX_POS_Y_0 + JUDGE_BOX_POS_Y_SPACE * judge_no;
	box_head.pal = 	judge_palofs[judge_no];
	box_cap = CATS_ObjectAdd_S(csp, crp, &box_head);
	CATS_ObjectUpdate(box_cap->act);

	return box_cap;
}

//--------------------------------------------------------------
/**
 * @brief   審判ボックスアクター削除
 *
 * @param   box_cap			審判ボックスアクターへのポインタ
 */
//--------------------------------------------------------------
static void AT_JudgeBoxActorDel(CATS_ACT_PTR box_cap)
{
	CATS_ActorPointerDelete_S(box_cap);
}

//--------------------------------------------------------------
/**
 * @brief   審判ボックスリソース削除
 *
 * @param   crp				crp
 */
//--------------------------------------------------------------
static void AT_JudgeBoxResourceDel(CATS_RES_PTR crp)
{
	//-- リソース削除 --//
	//パレットは常駐パレットなので削除なし
	CATS_FreeResourceChar(crp, CHARID_JUDGE_BOX);
	CATS_FreeResourceCell(crp, CELLID_JUDGE_BOX);
	CATS_FreeResourceCellAnm(crp, CELLANMID_JUDGE_BOX);
}

//--------------------------------------------------------------
/**
 * @brief   全ての審判と審判ボックスのアクターとリソースを登録する
 * @param   sys		演技力システム構造体へのポインタ
 */
//--------------------------------------------------------------
void AT_JudgeAddAll(ACTIN_SYSTEM_PARAM *sys, CONTEST_SYSTEM *consys)
{
	int i;
	
	//審判ボックスのリソース読み込み
	AT_JudgeBoxResourceLoad(sys->pfd, sys->csp, sys->crp);

	for(i = 0; i < JUDGE_MAX; i++){
		sys->judge_box_cap[i] = AT_JudgeBoxActorAdd(sys->csp, sys->crp, i);
		sys->judge_cap[i] = 
			AT_JudgeAdd(sys->pfd, sys->csp, sys->crp, &consys->c_game.jd[i], i);
	}
}

//--------------------------------------------------------------
/**
 * @brief   全ての審判と審判ボックスのアクターとリソースの削除を行う
 * @param   sys		演技力システム構造体へのポインタ
 */
//--------------------------------------------------------------
void AT_JudgeDelAll(ACTIN_SYSTEM_PARAM *sys)
{
	int i;
	
	for(i = 0; i < JUDGE_MAX; i++){
		AT_JudgeDel(sys->crp, sys->judge_cap[i], i);
		AT_JudgeBoxActorDel(sys->judge_box_cap[i]);
	}
	AT_JudgeBoxResourceDel(sys->crp);
}

//--------------------------------------------------------------
/**
 * @brief   審判リアクションアイコンのリソース登録
 *
 * @param   pfd			パレットフェードシステムへのポインタ
 * @param   csp			csp
 * @param   crp			crp
 */
//--------------------------------------------------------------
void AT_JudgeReactionIconResourceLoad(PALETTE_FADE_PTR pfd, CATS_SYS_PTR csp, CATS_RES_PTR crp)
{
	u32 char_id, cell_id, anm_id;
	
	char_id = EXCLAMATION_NCGR_BIN;
	cell_id = EXCLAMATION_NCER_BIN;
	anm_id = EXCLAMATION_NANR_BIN;
	
	//-- リソースロード --//
	//パレットは常駐パレットを使用するのでロードなし
	CATS_LoadResourceCharArc(csp, crp, ARC_CONTEST_OBJ, char_id, 1, 
		NNS_G2D_VRAM_TYPE_2DMAIN, CHARID_JUDGE_REACTION);
	CATS_LoadResourceCellArc(csp, crp, ARC_CONTEST_OBJ, cell_id, 1, 
		CELLID_JUDGE_REACTION);
	CATS_LoadResourceCellAnmArc(csp, crp, ARC_CONTEST_OBJ, 
		anm_id, 1, CELLANMID_JUDGE_REACTION);
}

//--------------------------------------------------------------
/**
 * @brief   審判リアクションアイコンリソース削除
 *
 * @param   crp				crp
 */
//--------------------------------------------------------------
void AT_JudgeReactionIconResourceDel(CATS_RES_PTR crp)
{
	//-- リソース削除 --//
	//パレットは常駐パレットなので削除なし
	CATS_FreeResourceChar(crp, CHARID_JUDGE_REACTION);
	CATS_FreeResourceCell(crp, CELLID_JUDGE_REACTION);
	CATS_FreeResourceCellAnm(crp, CELLANMID_JUDGE_REACTION);
}

//--------------------------------------------------------------
/**
 * @brief   審判リアクションアイコンアクターの生成
 * @param   sys			演技力システムワークへのポインタ
 */
//--------------------------------------------------------------
void AT_JudgeReactionIconActorAdd(ACTIN_SYSTEM_PARAM *sys)
{
	CATS_ACT_PTR cap;
	TCATS_OBJECT_ADD_PARAM_S act_head;
	
	//-- アクター生成 --//
	act_head = JudgeReactionObjParam;
	cap = CATS_ObjectAdd_S(sys->csp, sys->crp, &act_head);
	
	CATS_ObjectEnableCap(cap, CATS_ENABLE_FALSE);

	CATS_ObjectUpdate(cap->act);
	
	sys->judge_reaction_icon_cap = cap;
}

//--------------------------------------------------------------
/**
 * @brief   審判リアクションアイコンアクター削除
 *
 * @param   box_cap			審判リアクションアイコンアクターへのポインタ
 */
//--------------------------------------------------------------
void AT_JudgeReactionIconActorDel(ACTIN_SYSTEM_PARAM *sys)
{
	GF_ASSERT(sys->judge_reaction_icon_cap != NULL);
	
	CATS_ActorPointerDelete_S(sys->judge_reaction_icon_cap);
	sys->judge_reaction_icon_cap = NULL;
}

//--------------------------------------------------------------
/**
 * @brief   審判リアクションアイコンを表示ONする
 *
 * @param   sys				演技力システムワークへのポインタ
 * @param   judge_no		審判No
 * @param   reaction_type	リアクションタイプ(JUDGE_REACTION_ICON_???)
 */
//--------------------------------------------------------------
void AT_JudgeReactionIconON(ACTIN_SYSTEM_PARAM *sys, int judge_no, int reaction_type)
{
	GF_ASSERT(sys->judge_reaction_icon_cap != NULL);

	CATS_ObjectPosSetCap(sys->judge_reaction_icon_cap, 
		JudgeReactionIconPos[judge_no].x, JudgeReactionIconPos[judge_no].y);
	CATS_ObjectAnimeSeqSetCap(sys->judge_reaction_icon_cap, reaction_type);
	CATS_ObjectEnableCap(sys->judge_reaction_icon_cap, CATS_ENABLE_TRUE);
	
	switch(reaction_type){
	case JUDGE_REACTION_ICON_NOMINATION:
		Snd_SePlay(ASE_ICON_NOMINATION);
		break;
	case JUDGE_REACTION_ICON_WEAR:
		Snd_SePlay(ASE_ICON_WEAR);
		break;
	case JUDGE_REACTION_ICON_VOLTAGE:
		Snd_SePlay(ASE_ICON_VOLTAGE);
		break;
	case JUDGE_REACTION_ICON_VOLTAGE_MAX:
		Snd_SePlay(ASE_ICON_VOLTAGE_MAX);
		break;
	}
}

//--------------------------------------------------------------
/**
 * @brief   審判リアクションアイコンを表示OFFする
 * @param   sys		演技力システムワークへのポインタ
 */
//--------------------------------------------------------------
void AT_JudgeReactionIconOFF(ACTIN_SYSTEM_PARAM *sys)
{
	GF_ASSERT(sys->judge_reaction_icon_cap != NULL);

	CATS_ObjectEnableCap(sys->judge_reaction_icon_cap, CATS_ENABLE_FALSE);
}

//--------------------------------------------------------------
/**
 * @brief   審判をリアクション動作させる
 *
 * @param   apw				演技力部門管理ワークへのポインタ
 * @param   judge_no		審判No
 * @param   reaction_type	リアクションタイプ(JUDGE_REACTION_ICON_???)
 * @param   end_flag		終了時ここにTRUEが入る
 */
//--------------------------------------------------------------
void AT_JudgeReactionMoveTaskSet(ACTIN_PROC_WORK *apw, int judge_no, 
	int reaction_type, u8 *end_flag)
{
	JUDGE_REACTION_MOVE_WORK *jrmw;
	
	jrmw = sys_AllocMemory(HEAPID_ACTIN, sizeof(JUDGE_REACTION_MOVE_WORK));
	MI_CpuClear8(jrmw, sizeof(JUDGE_REACTION_MOVE_WORK));
	
	*end_flag = FALSE;
	jrmw->end_flag = end_flag;
	jrmw->apw = apw;
	jrmw->judge_no = judge_no;
	
	CATS_ObjectPosGetCap(apw->sys.judge_cap[judge_no], &jrmw->start_x, &jrmw->start_y);
	
	switch(reaction_type){
	case JUDGE_REACTION_ICON_NOMINATION:
	default:
		//TCB_Add(JudgeReactionMove_Nomination, jrmw, TCBPRI_ACTIN_EFFECT);
		jrmw->loop = 1;
		jrmw->jump.up_power = -JUDGE_JUMP_NOMINATION_POWER;
		jrmw->jump.backup_up_power = -JUDGE_JUMP_NOMINATION_POWER;
		TCB_Add(JudgeReactionMove_Jump, jrmw, TCBPRI_ACTIN_EFFECT);
		break;
	case JUDGE_REACTION_ICON_WEAR:
		TCB_Add(JudgeReactionMove_Wear, jrmw, TCBPRI_ACTIN_EFFECT);
		break;
	case JUDGE_REACTION_ICON_VOLTAGE:
		jrmw->jump.up_power = -JUDGE_JUMP_VOLTAGE_UP_POWER;
		TCB_Add(JudgeReactionMove_Jump, jrmw, TCBPRI_ACTIN_EFFECT);
		break;
	case JUDGE_REACTION_ICON_VOLTAGE_MAX:
		jrmw->jump.up_power = -JUDGE_JUMP_VOLTAGE_MAX_UP_POWER;
		TCB_Add(JudgeReactionMove_Jump, jrmw, TCBPRI_ACTIN_EFFECT);
		break;
	case JUDGE_REACTION_ICON_SUFFER_BIG:
		jrmw->jump.up_power = -JUDGE_JUMP_SUFFER_BIG;
		TCB_Add(JudgeReactionMove_Jump, jrmw, TCBPRI_ACTIN_EFFECT);
		break;
	case JUDGE_REACTION_ICON_SUFFER_MIDDLE:
		jrmw->jump.up_power = -JUDGE_JUMP_SUFFER_MIDDLE;
		TCB_Add(JudgeReactionMove_Jump, jrmw, TCBPRI_ACTIN_EFFECT);
		break;
	case JUDGE_REACTION_ICON_SUFFER_SMALL:
		jrmw->jump.up_power = -JUDGE_JUMP_SUFFER_SMALL;
		TCB_Add(JudgeReactionMove_Jump, jrmw, TCBPRI_ACTIN_EFFECT);
		break;
	}
}

//--------------------------------------------------------------
/**
 * @brief   審判リアクション動作：指名
 * @param   tcb			TCBへのポインタ
 * @param   work		審判リアクション動作ワークへのポインタ
 */
//--------------------------------------------------------------
static void JudgeReactionMove_Nomination(TCB_PTR tcb, void *work)
{
	JUDGE_REACTION_MOVE_WORK *jrmw = work;
	
	switch(jrmw->seq){
	case 0:
		jrmw->x = jrmw->start_x * 0x0100;
		jrmw->y = jrmw->start_y * 0x0100;
		jrmw->seq++;
		//break;
	case 1:
	case 3:
		jrmw->y -= JUDGE_NOMINATION_ADD_Y;
		jrmw->loop++;
		if(jrmw->loop > JUDGE_NOMINATION_LOOP){
			jrmw->loop = 0;
			jrmw->seq++;
		}
		break;
	case 2:
	case 4:
		jrmw->y += JUDGE_NOMINATION_ADD_Y;
		jrmw->loop++;
		if(jrmw->loop > JUDGE_NOMINATION_LOOP){
			jrmw->loop = 0;
			jrmw->y = jrmw->start_y * 0x0100;
			jrmw->seq++;
		}
		break;
	default:
		*(jrmw->end_flag) = TRUE;
		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		return;
	}
	CATS_ObjectPosSetCap(jrmw->apw->sys.judge_cap[jrmw->judge_no], 
		jrmw->x / 0x0100, jrmw->y / 0x0100);
}

//--------------------------------------------------------------
/**
 * @brief   審判リアクション動作：被り
 * @param   tcb			TCBへのポインタ
 * @param   work		審判リアクション動作ワークへのポインタ
 */
//--------------------------------------------------------------
static void JudgeReactionMove_Wear(TCB_PTR tcb, void *work)
{
	JUDGE_REACTION_MOVE_WORK *jrmw = work;
	
	switch(jrmw->seq){
	case 0:
		jrmw->x = jrmw->start_x * 0x0100;
		jrmw->y = jrmw->start_y * 0x0100;
		jrmw->seq++;
		//break;
	case 1:
		if(jrmw->loop & 1){
			jrmw->x = jrmw->start_x * 0x0100 + JUDGE_WEAR_ADD_X;
		}
		else{
			jrmw->x = jrmw->start_x * 0x0100 - JUDGE_WEAR_ADD_X;
		}

		jrmw->loop++;
		if(jrmw->loop > JUDGE_WEAR_LOOP){
			jrmw->x = jrmw->start_x * 0x0100;
			jrmw->loop = 0;
			jrmw->seq++;
		}
		break;
	case 2:
		jrmw->wait++;
		if(jrmw->wait > 15){
			jrmw->wait = 0;
			jrmw->seq++;
		}
		break;
	default:
		*(jrmw->end_flag) = TRUE;
		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		return;
	}
	CATS_ObjectPosSetCap(jrmw->apw->sys.judge_cap[jrmw->judge_no], 
		jrmw->x / 0x0100, jrmw->y / 0x0100);
}

//--------------------------------------------------------------
/**
 * @brief   審判リアクション動作：ジャンプ(ボルテージ、ボルテージMAX)
 * @param   tcb			TCBへのポインタ
 * @param   work		審判リアクション動作ワークへのポインタ
 */
//--------------------------------------------------------------
static void JudgeReactionMove_Jump(TCB_PTR tcb, void *work)
{
	JUDGE_REACTION_MOVE_WORK *jrmw = work;
	
	switch(jrmw->seq){
	case 0:
		jrmw->x = jrmw->start_x * 0x0100;
		jrmw->y = jrmw->start_y * 0x0100;
		jrmw->seq++;
		//break;
	case 1:
		jrmw->y += jrmw->jump.up_power;
		jrmw->jump.up_power += JUDGE_JUMP_GRAVITY;
		if(jrmw->y >= jrmw->start_y * 0x0100){
			jrmw->y = jrmw->start_y * 0x0100;
			if(jrmw->loop > 0){
				jrmw->jump.up_power = jrmw->jump.backup_up_power;
				jrmw->loop--;
				jrmw->seq--;
			}
			else{
				jrmw->seq++;
			}
		}
		CATS_ObjectPosSetCap(jrmw->apw->sys.judge_cap[jrmw->judge_no], 
			jrmw->x / 0x0100, jrmw->y / 0x0100);
		break;
	default:
		*(jrmw->end_flag) = TRUE;
		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		return;
	}
}

//--------------------------------------------------------------
/**
 * @brief   特別審査員につけるハートアクターを生成する
 *
 * @param   sys				演技力システム構造体へのポインタ
 * @param   judge_no		つける審査員のNO
 */
//--------------------------------------------------------------
void AT_SpecialHeartSet(ACTIN_SYSTEM_PARAM *sys, int judge_no)
{
	GF_ASSERT(sys->special_heart_cap == NULL);
	
	//リソース読み込み
	//パレットは常駐パレットを使用するのでロードなし
	CATS_LoadResourceCharArc(sys->csp, sys->crp, ARC_CONTEST_OBJ, 
		HEART16_NCGR_BIN, 1, 
		NNS_G2D_VRAM_TYPE_2DMAIN, CHARID_SPECIAL_HEART);
	CATS_LoadResourceCellArc(sys->csp, sys->crp, ARC_CONTEST_OBJ, 
		HEART16_NCER_BIN, 1, 
		CELLID_SPECIAL_HEART);
	CATS_LoadResourceCellAnmArc(sys->csp, sys->crp, ARC_CONTEST_OBJ, 
		HEART16_NANR_BIN, 1, CELLANMID_SPECIAL_HEART);
	
	//アクター生成
	sys->special_heart_cap = CATS_ObjectAdd_S(sys->csp, sys->crp, &SpecialHeartObjParam);
	CATS_ObjectUpdate(sys->special_heart_cap->act);
	CATS_ObjectPosSetCap(sys->special_heart_cap, 
		SPECIAL_HEART_POS_X + SPECIAL_HEART_POS_X_SPACE * judge_no, SPECIAL_HEART_POS_Y);
}

//--------------------------------------------------------------
/**
 * @brief   特別審査員につけるハートを削除する
 *
 * @param   sys		演技力システム構造体へのポインタ
 */
//--------------------------------------------------------------
void AT_SpecialHeartDel(ACTIN_SYSTEM_PARAM *sys)
{
	//-- リソース削除 --//
	//パレットは常駐パレットなので削除なし
	CATS_FreeResourceChar(sys->crp, CHARID_SPECIAL_HEART);
	CATS_FreeResourceCell(sys->crp, CELLID_SPECIAL_HEART);
	CATS_FreeResourceCellAnm(sys->crp, CELLANMID_SPECIAL_HEART);
	
	//-- アクター削除 --//
	CATS_ActorPointerDelete_S(sys->special_heart_cap);
	sys->special_heart_cap = NULL;
}

//--------------------------------------------------------------
/**
 * @brief   アピールポイントのリソースロードする
 *
 * @param   csp
 * @param   crp
 */
//--------------------------------------------------------------
void AT_AppealPointResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp)
{
	//パレットは常駐パレットを使用するのでロードなし
	CATS_LoadResourceCharArc(csp, crp, ARC_CONTEST_OBJ, 
		HEART8_NCGR_BIN, 1, 
		NNS_G2D_VRAM_TYPE_2DMAIN, CHARID_APPEAL_POINT);
	CATS_LoadResourceCellArc(csp, crp, ARC_CONTEST_OBJ, 
		HEART8_NCER_BIN, 1, 
		CELLID_APPEAL_POINT);
	CATS_LoadResourceCellAnmArc(csp, crp, ARC_CONTEST_OBJ, 
		HEART8_NANR_BIN, 1, CELLANMID_APPEAL_POINT);
}

//--------------------------------------------------------------
/**
 * @brief   アピールポイントのリソースを解放する
 *
 * @param   crp		
 */
//--------------------------------------------------------------
void AT_AppealPointResourceFree(CATS_RES_PTR crp)
{
	//パレットは常駐パレットなので削除なし
	CATS_FreeResourceChar(crp, CHARID_APPEAL_POINT);
	CATS_FreeResourceCell(crp, CELLID_APPEAL_POINT);
	CATS_FreeResourceCellAnm(crp, CELLANMID_APPEAL_POINT);
}

//--------------------------------------------------------------
/**
 * @brief   アピールアイコンを削除する
 *
 * @param   sys				演技力システム構造体へのポインタ
 * @param   breeder_no		ブリーダーNo
 * @param   act_pos			アクターワーク位置
 */
//--------------------------------------------------------------
static inline void AppealPointActorDel(ACTIN_SYSTEM_PARAM *sys, int breeder_no, int act_pos)
{
	if(sys->appeal_point_cap[breeder_no][act_pos] != NULL){
		CATS_ActorPointerDelete_S(sys->appeal_point_cap[breeder_no][act_pos]);
		sys->appeal_point_cap[breeder_no][act_pos] = NULL;
	}
}

//--------------------------------------------------------------
/**
 * @brief   指定したブリーダーが持つアピールポイントアイコンを全て削除する
 *
 * @param   sys				演技力システム構造体へのポインタ
 * @param   breeder_no		ブリーダーNO
 */
//--------------------------------------------------------------
static void AT_AppealPointActorBreederDel(ACTIN_SYSTEM_PARAM *sys, int breeder_no)
{
	int i;
	
	for(i = 0; i < APPEAL_POINT_ICON_MAX; i++){
		AppealPointActorDel(sys, breeder_no, i);
	}
}

//--------------------------------------------------------------
/**
 * @brief   全てのアピールポイントアイコンを削除する
 * @param   sys		演技力システム構造体へのポインタ
 */
//--------------------------------------------------------------
void AT_AppealPointActorDelAll(ACTIN_SYSTEM_PARAM *sys)
{
	int breeder;
	
	for(breeder = 0; breeder < BREEDER_MAX; breeder++){
		AT_AppealPointActorBreederDel(sys, breeder);
	}
}

//--------------------------------------------------------------
/**
 * @brief   アピールポイントアイコンを生成する
 *
 * @param   csp		
 * @param   crp		
 * @param   x		表示座標X
 * @param   y		表示座標Y
 *
 * @retval  生成したアクターへのポインタ
 */
//--------------------------------------------------------------
static CATS_ACT_PTR AT_AppealPointActorSet(CATS_SYS_PTR csp, CATS_RES_PTR crp, int x, int y)
{
	CATS_ACT_PTR app_cap;
	
	//アクター生成
	app_cap = CATS_ObjectAdd_S(csp, crp, &AppealPointObjParam);
	CATS_ObjectUpdate(app_cap->act);
	CATS_ObjectPosSetCap(app_cap, x, y);
	
	return app_cap;
}

//--------------------------------------------------------------
/**
 * @brief   そのブリーダーが持つアピールポイントアイコンをいったん全て削除し、
 *          現ポイント分アイコンを作り直す
 *
 * @param   sys				演技力システム構造体へのポインタ
 * @param   breeder_no		ブリーダー番号
 * @param   breeder_pos		ブリーダー位置
 * @param   point			表示するアピールポイント
 */
//--------------------------------------------------------------
void AT_AppealPointActorMadeOver(ACTIN_SYSTEM_PARAM *sys, int breeder_no, 
	int breeder_pos, int point)
{
	int icon_num, i, icon_pos, anm_seq;
	
	icon_num = point / APPEAL_ICON_ONE_POINT;
//	GF_ASSERT(icon_num <= APPEAL_POINT_ICON_MAX);
	if(icon_num > APPEAL_POINT_ICON_MAX * APPEAL_POINT_ICON_LOOP){
		icon_num = APPEAL_POINT_ICON_MAX * APPEAL_POINT_ICON_LOOP;
		OS_TPrintf("---アピールポイントアイコンの表示数が最大数を超えています！！---\n");
	}
	
	//必要なアイコンの数以上のアイコンが出ている場合はそれらを削除する
	for(i = icon_num; i < APPEAL_POINT_ICON_MAX; i++){
		AppealPointActorDel(sys, breeder_no, i);
	}
	
	//現ポイント分までのアイコンを作る
	for(i = icon_num-1; i > -1; i--){
		icon_pos = i % APPEAL_POINT_ICON_MAX;
		anm_seq = i / APPEAL_POINT_ICON_MAX;
		
		if(sys->appeal_point_cap[breeder_no][icon_pos] == NULL){
			sys->appeal_point_cap[breeder_no][icon_pos] = AT_AppealPointActorSet(sys->csp, 
				sys->crp, AppealPointPos[breeder_pos][0] + icon_pos*8, 
				AppealPointPos[breeder_pos][1]);
			CATS_ObjectAnimeSeqSetCap(sys->appeal_point_cap[breeder_no][icon_pos], anm_seq);
			AppealPointAppearEffectSet(sys->appeal_point_cap[breeder_no][icon_pos]);
		}
		else if(CATS_ObjectAnimeSeqGetCap(sys->appeal_point_cap[breeder_no][icon_pos]) < anm_seq){
			CATS_ObjectAnimeSeqSetCap(sys->appeal_point_cap[breeder_no][icon_pos], anm_seq);
			AppealPointAppearEffectSet(sys->appeal_point_cap[breeder_no][icon_pos]);
		}
	}
	
	//SE再生
	Snd_SePlay(ASE_AP_UP);
	Snd_PlayerSetTrackPitchBySeqNo(ASE_AP_UP, 0xffff, SND_HALF_PITCH * (icon_num - 1));
}

//--------------------------------------------------------------
/**
 * @brief   アピールアイコン登場エフェクトタスクを生成する
 * @param   cap		アピールアイコンのポインタ
 */
//--------------------------------------------------------------
static void AppealPointAppearEffectSet(CATS_ACT_PTR cap)
{
	APPEAL_POINT_APPEAR_WORK *apaw;
	
	apaw = sys_AllocMemory(HEAPID_ACTIN, sizeof(APPEAL_POINT_APPEAR_WORK));
	MI_CpuClear8(apaw, sizeof(APPEAL_POINT_APPEAR_WORK));
	apaw->cap = cap;
	CATS_ObjectEnableCap(cap, CATS_ENABLE_FALSE);
	TCB_Add(AppealPointAppear, apaw, TCBPRI_ACTIN_EFFECT);
}

//--------------------------------------------------------------
/**
 * @brief   アピールアイコン登場エフェクトメインタスク
 *
 * @param   tcb			TCBへのポインタ
 * @param   work		APPEAL_POINT_APPEAR_WORK構造体
 */
//--------------------------------------------------------------
static void AppealPointAppear(TCB_PTR tcb, void *work)
{
	APPEAL_POINT_APPEAR_WORK *apaw = work;
	
	switch(apaw->seq){
	case 0:
		CATS_ObjectAffineSetCap(apaw->cap, CLACT_AFFINE_DOUBLE);
		apaw->sx = APICON_EFF_INIT_SCALE;
		apaw->sy = APICON_EFF_INIT_SCALE;
		CATS_ObjectEnableCap(apaw->cap, CATS_ENABLE_TRUE);
//		CATS_ObjectScaleSetCap(apaw->cap, 1.4f, 1.4f);
		apaw->seq++;
		//break;
	case 1:
		apaw->sx += APICON_EFF_ADD_SCALE;
		apaw->sy += APICON_EFF_ADD_SCALE;
		CATS_ObjectScaleSetCap(apaw->cap, apaw->sx, apaw->sy);
		CATS_ObjectRotationAddCap(apaw->cap, APICON_EFF_ADD_ROTATION);
		if(apaw->sx >= APICON_EFF_MAX_SCALE){
			apaw->seq++;
		}
		break;
	case 2:
		apaw->sx -= APICON_EFF_ADD_SCALE;
		apaw->sy -= APICON_EFF_ADD_SCALE;
		CATS_ObjectScaleSetCap(apaw->cap, apaw->sx, apaw->sy);
		CATS_ObjectRotationAddCap(apaw->cap, APICON_EFF_ADD_ROTATION);
		if(apaw->sx <= APICON_EFF_NORMAL_SCALE){
			CATS_ObjectScaleSetCap(apaw->cap, APICON_EFF_NORMAL_SCALE, APICON_EFF_NORMAL_SCALE);
			CATS_ObjectRotationSetCap(apaw->cap, 0);
			apaw->seq++;
		}
		break;
	default:
		CATS_ObjectAffineSetCap(apaw->cap, CLACT_AFFINE_NONE);
		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		return;
	}
}

//--------------------------------------------------------------
/**
 * @brief   ボルテージポイントのリソースロードする
 *
 * @param   csp
 * @param   crp
 */
//--------------------------------------------------------------
void AT_VoltagePointResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp)
{
	//パレットは常駐パレットを使用するのでロードなし
	CATS_LoadResourceCharArc(csp, crp, ARC_CONTEST_OBJ, 
		VOLTAGE8_NCGR_BIN, 1, 
		NNS_G2D_VRAM_TYPE_2DMAIN, CHARID_VOLTAGE_POINT);
	CATS_LoadResourceCellArc(csp, crp, ARC_CONTEST_OBJ, 
		VOLTAGE8_NCER_BIN, 1, 
		CELLID_VOLTAGE_POINT);
	CATS_LoadResourceCellAnmArc(csp, crp, ARC_CONTEST_OBJ, 
		VOLTAGE8_NANR_BIN, 1, CELLANMID_VOLTAGE_POINT);

	//ボルテージ演出
	CATS_LoadResourceCharArc(csp, crp, ARC_CONTEST_OBJ, 
		STAR16_NCGR_BIN, 1, 
		NNS_G2D_VRAM_TYPE_2DMAIN, CHARID_VOLTAGE_EFF);
	CATS_LoadResourceCellArc(csp, crp, ARC_CONTEST_OBJ, 
		STAR16_NCER_BIN, 1, 
		CELLID_VOLTAGE_EFF);
	CATS_LoadResourceCellAnmArc(csp, crp, ARC_CONTEST_OBJ, 
		STAR16_NANR_BIN, 1, CELLANMID_VOLTAGE_EFF);
}

//--------------------------------------------------------------
/**
 * @brief   ボルテージポイントのリソースを解放する
 *
 * @param   crp		
 */
//--------------------------------------------------------------
void AT_VoltagePointResourceFree(CATS_RES_PTR crp)
{
	//パレットは常駐パレットなので削除なし
	CATS_FreeResourceChar(crp, CHARID_VOLTAGE_POINT);
	CATS_FreeResourceCell(crp, CELLID_VOLTAGE_POINT);
	CATS_FreeResourceCellAnm(crp, CELLANMID_VOLTAGE_POINT);

	//ボルテージ演出
	CATS_FreeResourceChar(crp, CHARID_VOLTAGE_EFF);
	CATS_FreeResourceCell(crp, CELLID_VOLTAGE_EFF);
	CATS_FreeResourceCellAnm(crp, CELLANMID_VOLTAGE_EFF);
}

//--------------------------------------------------------------
/**
 * @brief   ボルテージアイコンの単独削除
 *
 * @param   sys				演技力システム構造体へのポインタ
 * @param   judge_no		審判No
 * @param   icon_pos		アイコンの位置
 */
//--------------------------------------------------------------
static inline void AT_VoltagePointActorDel(ACTIN_SYSTEM_PARAM *sys, int judge_no, int icon_pos)
{
	CATS_ActorPointerDelete_S(sys->voltage_point_cap[judge_no][icon_pos]);
	sys->voltage_point_cap[judge_no][icon_pos] = NULL;
}

//--------------------------------------------------------------
/**
 * @brief   指定した審判が持つボルテージポイントアイコンを全て削除する
 *
 * @param   sys				演技力システム構造体へのポインタ
 * @param   judge_no		審判No
 */
//--------------------------------------------------------------
static void AT_VoltagePointActorJudgeDel(ACTIN_SYSTEM_PARAM *sys, int judge_no)
{
	int i;
	
	for(i = 0; i < VOLTAGE_MAX; i++){
		if(sys->voltage_point_cap[judge_no][i] != NULL){
			AT_VoltagePointActorDel(sys, judge_no, i);
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   全てのボルテージポイントアイコンを削除する
 * @param   sys		演技力システム構造体へのポインタ
 */
//--------------------------------------------------------------
void AT_VoltagePointActorDelAll(ACTIN_SYSTEM_PARAM *sys)
{
	int judge;
	
	for(judge = 0; judge < JUDGE_MAX; judge++){
		AT_VoltagePointActorJudgeDel(sys, judge);
	}
}

//--------------------------------------------------------------
/**
 * @brief   ボルテージポイントアイコンを生成する
 *
 * @param   csp		
 * @param   crp		
 * @param   x		表示座標X
 * @param   y		表示座標Y
 *
 * @retval  生成したアクターへのポインタ
 */
//--------------------------------------------------------------
static CATS_ACT_PTR AT_VoltagePointActorSet(CATS_SYS_PTR csp, CATS_RES_PTR crp, int x, int y)
{
	CATS_ACT_PTR app_cap;
	
	//アクター生成
	app_cap = CATS_ObjectAdd_S(csp, crp, &VoltagePointObjParam);
	CATS_ObjectUpdate(app_cap->act);
	CATS_ObjectPosSetCap(app_cap, x, y);
	
	return app_cap;
}

//--------------------------------------------------------------
/**
 * @brief   ボルテージ演出アイコンを生成する
 *
 * @param   csp		
 * @param   crp		
 * @param   x		表示座標X
 * @param   y		表示座標Y
 *
 * @retval  生成したアクターへのポインタ
 */
//--------------------------------------------------------------
static CATS_ACT_PTR AT_VoltageEffectActorSet(CATS_SYS_PTR csp, CATS_RES_PTR crp, int x, int y)
{
	CATS_ACT_PTR cap;
	
	//アクター生成
	cap = CATS_ObjectAdd_S(csp, crp, &VoltageEffectObjParam);
	CATS_ObjectUpdate(cap->act);
	CATS_ObjectPosSetCap(cap, x, y);
	
	return cap;
}

//--------------------------------------------------------------
/**
 * @brief   ボルテージ演出：メインタスク
 * @param   tcb			TCBへのポインタ
 * @param   work		VOLTAGE_MOVE_WORK構造体
 */
//--------------------------------------------------------------
static void VoltagePointActorMove(TCB_PTR tcb, void *work)
{
	VOLTAGE_MOVE_WORK *vmw = work;
	
	switch(vmw->seq){
	case 0:
		CATS_ObjectAffineSetCap(vmw->cap, CLACT_AFFINE_NORMAL);
		
		vmw->move_end_x = vmw->x + (32<<8);
		vmw->move_end_y = vmw->y + (72<<8);
		vmw->add_x = (vmw->move_end_x - vmw->x) / VOLTAGE_MOVE_FIRST_FRAME;
		vmw->add_y = (vmw->move_end_y - vmw->y) / VOLTAGE_MOVE_FIRST_FRAME;
		vmw->seq++;
		//break;
	case 1:
		vmw->x += vmw->add_x;
		vmw->y += vmw->add_y;
		if((vmw->add_x > 0 && vmw->x >= vmw->move_end_x)
				|| (vmw->add_x < 0 && vmw->x <= vmw->move_end_x)){
			vmw->seq++;
		}
		break;
	case 2:
		vmw->wait++;
		if(vmw->wait > VOLTAGE_MOVE_FIRST_WAIT){
			vmw->wait = 0;
			vmw->seq++;
		}
		break;
	case 3:
		vmw->move_end_x = vmw->end_x << 8;
		vmw->move_end_y = vmw->end_y << 8;
		vmw->add_x = (vmw->move_end_x - vmw->x) / VOLTAGE_MOVE_END_FRAME;
		vmw->add_y = (vmw->move_end_y - vmw->y) / VOLTAGE_MOVE_END_FRAME;
		vmw->seq++;
		//break;
	case 4:
		vmw->x += vmw->add_x;
		vmw->y += vmw->add_y;
		if((vmw->add_x > 0 && vmw->x >= vmw->move_end_x)
				|| (vmw->add_x < 0 && vmw->x <= vmw->move_end_x)){
			vmw->x = vmw->end_x << 8;
			vmw->y = vmw->end_y << 8;
			vmw->seq++;
		}
		break;
	case 5:
		vmw->wait++;
		if(vmw->wait > VOLTAGE_MOVE_END_WAIT){
			vmw->wait = 0;
			vmw->seq++;
		}
		break;
	default:
		CATS_ActorPointerDelete_S(vmw->cap);

		CATS_ObjectEnableCap(vmw->voltage_cap, CATS_ENABLE_TRUE);
		
		Snd_SePlay(ASE_VOLTAGE_UP);

		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		return;
	}
	
	CATS_ObjectRotationAddCap(vmw->cap, VOLTAGE_MOVE_ADD_ROTATION);
	CATS_ObjectPosSetCap(vmw->cap, vmw->x / 0x0100, vmw->y / 0x0100);
}

//--------------------------------------------------------------
/**
 * @brief   ボルテージ移動エフェクトが終了しているか確認
 *
 * @param   sys				演技力システムワークへのポインタ
 * @param   judge_no		審判番号
 *
 * @retval  TRUE:終了。　FALSE:動作中のエフェクトがある
 */
//--------------------------------------------------------------
BOOL AT_VoltageMoveEffectEndCheck(ACTIN_SYSTEM_PARAM *sys, int judge_no)
{
	int i;
	
	for(i = 0; i < VOLTAGE_MAX; i++){
		if(sys->voltage_point_cap[judge_no][i] != NULL){
			if(CATS_ObjectEnableGetCap(sys->voltage_point_cap[judge_no][i]) == CATS_ENABLE_FALSE){
				return FALSE;
			}
		}
	}
	return TRUE;
}

//--------------------------------------------------------------
/**
 * @brief   現ポイント分までのボルテージアイコンを作成する
 * 			既に生成されているアイコンが現ポイント分に達していなければ追加で作り、
 *          逆に多く生成されているならば、その分は削除する
 *
 * @param   sys				演技力システム構造体へのポインタ
 * @param   judge_no		審判番号
 * @param   point			表示するボルテージポイント
 */
//--------------------------------------------------------------
void AT_VoltagePointActorMadeOver(ACTIN_SYSTEM_PARAM *sys, int judge_no, int point)
{
	int icon_num, i;
	VOLTAGE_MOVE_WORK *vmw;
	
	icon_num = point / VOLTAGE_ONE_POINT;
	GF_ASSERT(icon_num <= VOLTAGE_MAX);
	
	//現ポイント分のアイコンを作る
	for(i = 0; i < icon_num; i++){
		if(sys->voltage_point_cap[judge_no][i] == NULL){
			sys->voltage_point_cap[judge_no][i] = AT_VoltagePointActorSet(sys->csp, sys->crp, 
				VoltagePointPos[judge_no][0] + i*VOLTAGE_SPACE_X, 
				VoltagePointPos[judge_no][1]);
			CATS_ObjectEnableCap(sys->voltage_point_cap[judge_no][i], CATS_ENABLE_FALSE);

			//ボルテージ演出生成
			vmw = sys_AllocMemory(HEAPID_ACTIN, sizeof(VOLTAGE_MOVE_WORK));
			MI_CpuClear8(vmw, sizeof(VOLTAGE_MOVE_WORK));
			vmw->sys = sys;
			vmw->voltage_cap = sys->voltage_point_cap[judge_no][i];
			vmw->cap = AT_VoltageEffectActorSet(sys->csp, sys->crp, 
				JudgeReactionIconPos[judge_no].x, JudgeReactionIconPos[judge_no].y);
			vmw->x = JudgeReactionIconPos[judge_no].x << 8;
			vmw->y = JudgeReactionIconPos[judge_no].y << 8;
			vmw->end_x = VoltagePointPos[judge_no][0] + i*VOLTAGE_SPACE_X;
			vmw->end_y = VoltagePointPos[judge_no][1];
			vmw->judge_no = judge_no;
			vmw->point = point;
			TCB_Add(VoltagePointActorMove, vmw, TCBPRI_ACTIN_EFFECT);
		}
	}
	//現ポイント分より多くアイコンが作られている場合は削除する
	for( ; i < VOLTAGE_MAX; i++){
		if(sys->voltage_point_cap[judge_no][i] != NULL){
			AT_VoltagePointActorDel(sys, judge_no, i);
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   会話ウィンドウ、スライド時のカバーOBJを生成
 * @param   sys		演技力システム構造体へのポインタ
 */
//--------------------------------------------------------------
void AT_TalkWinSlideCoverOBJSet(ACTIN_SYSTEM_PARAM *sys)
{
	int scr_x;
	u16 *scrnbuf;
	int i, obj_palno;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	
	csp = sys->csp;
	crp = sys->crp;
	
	scr_x = GF_BGL_ScrollGetX(sys->bgl, ACTIN_FRAME_WIN);
	scrnbuf = GF_BGL_ScreenAdrsGet(sys->bgl, ACTIN_FRAME_WIN);
	if(scr_x == 0){
		scrnbuf = &scrnbuf[WINSLIDE_SCRN_POS_BEFORE];
	}
	else{
		scrnbuf = &scrnbuf[WINSLIDE_SCRN_POS_AFTER];
	}
	
	//リソース登録
	CATS_LoadResourceCharArc(csp, crp, ARC_CONTEST_OBJ, SPACE_64K_8X16_NCGR_BIN, 1, 
		NNS_G2D_VRAM_TYPE_2DMAIN, CHARID_WIN_COVER_0);
	CATS_LoadResourceCharArc(csp, crp, ARC_CONTEST_OBJ, SPACE_64K_8X16_NCGR_BIN, 1, 
		NNS_G2D_VRAM_TYPE_2DMAIN, CHARID_WIN_COVER_1);
	CATS_LoadResourceCharArc(csp, crp, ARC_CONTEST_OBJ, SPACE_64K_8X16_NCGR_BIN, 1, 
		NNS_G2D_VRAM_TYPE_2DMAIN, CHARID_WIN_COVER_2);
	obj_palno = CATS_LoadResourcePlttWorkArc(sys->pfd, FADE_MAIN_OBJ, csp, crp, 
		ARC_CONTEST_OBJ, CONTEST_OBJ_NCLR, 0, 
		1, NNS_G2D_VRAM_TYPE_2DMAIN, PLTTID_WIN_COVER);
	CATS_LoadResourceCellArc(csp, crp, ARC_CONTEST_OBJ, SPACE_64K_8X16_NCER_BIN, 1, 
		CELLID_WIN_COVER);
	CATS_LoadResourceCellAnmArc(csp, crp, ARC_CONTEST_OBJ, 
		SPACE_64K_8X16_NANR_BIN, 1, CELLANMID_WIN_COVER);

	//アクター生成
	{
		TCATS_OBJECT_ADD_PARAM_S head;
		
		head = WinCoverObjParam;
		for(i = 0; i < WINCOVER_ACT_MAX; i++){
			GF_ASSERT(sys->wincover_cap[i] == NULL);
			sys->wincover_cap[i] = CATS_ObjectAdd_S(csp, crp, &head);
			CATS_ObjectPosSetCap(sys->wincover_cap[i], 0x1f * 8 + 4, 0x13 * 8 + i * 16);
			head.id[CLACT_U_CHAR_RES]++;
		}
	}
	
	//スクリーンで使用しているキャラクタを読み取ってOBJのVRAMへコピーする
	{
		void *obj_vram;
		NNSG2dImageProxy * image;
		u8 *bgchar;
		u8 *bgchar_vram;
		int k = 0;
		
		obj_vram = G2_GetOBJCharPtr();
		bgchar_vram = GF_BGL_CgxGet(ACTIN_FRAME_WIN);
		for(i = 0; i < WINCOVER_ACT_MAX; i++){
			image = CLACT_ImageProxyGet(sys->wincover_cap[i]->act);
			
			bgchar = &bgchar_vram[32 * (scrnbuf[k * 32] & 1023)];
			MI_CpuCopy16(bgchar, (void*)((u32)obj_vram 
				+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN]), 0x20);
			k++;

			bgchar = &bgchar_vram[32 * (scrnbuf[k * 32] & 1023)];
			MI_CpuCopy16(bgchar, (void*)((u32)obj_vram 
				+ image->vramLocation.baseAddrOfVram[NNS_G2D_VRAM_TYPE_2DMAIN] + 0x20), 0x20);
			k++;
		}
	}
	
	//スクリーンで使用しているパレットを読み取ってOBJパレットへコピーする
	{
		int palno;
		
		palno = (*scrnbuf) >> 12;
		PaletteWorkCopy(sys->pfd, FADE_MAIN_BG, palno * 16, 
			FADE_MAIN_OBJ, obj_palno * 16, 0x20);
	}
}

//--------------------------------------------------------------
/**
 * @brief   会話ウィンドウ、スライド時のカバーOBJ削除
 * @param   sys		演技力システム構造体へのポインタ
 */
//--------------------------------------------------------------
void AT_TalkWinSlideCoverOBJDelete(ACTIN_SYSTEM_PARAM *sys)
{
	int i;
	CATS_RES_PTR crp;
	
	crp = sys->crp;
	
	//アクター削除
	for(i = 0; i < WINCOVER_ACT_MAX; i++){
		CATS_ActorPointerDelete_S(sys->wincover_cap[i]);
		sys->wincover_cap[i] = NULL;
	}
	
	//リソース削除
	CATS_FreeResourceChar(crp, CHARID_WIN_COVER_0);
	CATS_FreeResourceChar(crp, CHARID_WIN_COVER_1);
	CATS_FreeResourceChar(crp, CHARID_WIN_COVER_2);
	CATS_FreeResourcePltt(crp, PLTTID_WIN_COVER);
	CATS_FreeResourceCell(crp, CELLID_WIN_COVER);
	CATS_FreeResourceCellAnm(crp, CELLANMID_WIN_COVER);
}

//--------------------------------------------------------------
/**
 * @brief   会話ウィンドウのスクリーンをスライド用に描画
 *
 * @param   sys				演技力システム構造体へのポインタ
 * @param   write_type		TALKWIN_SCREEN_WRITE_???
 */
//--------------------------------------------------------------
void AT_TalkWinScreenWrite(ACTIN_SYSTEM_PARAM *sys, int write_type)
{
	u16 *scrnbuf_before, *scrnbuf_after, *scrnbuf;
	int i;
	
	scrnbuf = GF_BGL_ScreenAdrsGet(sys->bgl, ACTIN_FRAME_WIN);
	scrnbuf_before = &scrnbuf[WINSLIDE_SCRN_POS_BEFORE];
	scrnbuf_after = &scrnbuf[WINSLIDE_SCRN_POS_AFTER];
	
	if(write_type == TALKWIN_SCREEN_WRITE_BEFORE){
		for(i = 0; i < 6; i++){
			scrnbuf_before[i * 32] = scrnbuf_before[i * 32 - 1];
		}
	}
	else{
		for(i = 0; i < 6; i++){
			scrnbuf_before[i * 32] = scrnbuf_after[i * 32];
		}
	}
	
	GF_BGL_LoadScreenV_Req(sys->bgl, ACTIN_FRAME_WIN);
}

//--------------------------------------------------------------
/**
 * @brief   会話ウィンドウスライド制御タスクを生成する
 *
 * @param   sys				演技力システム構造体へのポインタ
 * @param   slide_dir		スライド方向(TALKWIN_SLIDE_DIR_???)
 * @param   end_flag		スライドの終了を知らせるワークへのポインタ(終了時TRUEがセットされます)
 */
//--------------------------------------------------------------
void AT_TalkWinSlideTaskSet(ACTIN_SYSTEM_PARAM *sys, u8 slide_dir, u8 *end_flag)
{
	TALKWIN_SLIDE_WORK *tsw;
	
	*end_flag = FALSE;

	tsw = sys_AllocMemory(HEAPID_ACTIN, sizeof(TALKWIN_SLIDE_WORK));
	MI_CpuClear8(tsw, sizeof(TALKWIN_SLIDE_WORK));
	
	tsw->sys = sys;
	tsw->slide_dir = slide_dir;
	tsw->end_flag = end_flag;
	
	tsw->x = GF_BGL_ScrollGetX(sys->bgl, ACTIN_FRAME_WIN) << 8;
	
	AT_TalkWinSlideCoverOBJSet(sys);
	
	if(slide_dir == TALKWIN_SLIDE_DIR_OUT){
		AT_TalkWinScreenWrite(sys, TALKWIN_SCREEN_WRITE_BEFORE);
	}
	
	TCB_Add(TalkWinSlideInOutMain, tsw, TCBPRI_ACTIN_TALKWIN_SLIDE);
}

//--------------------------------------------------------------
/**
 * @brief   会話ウィンドウスライド制御タスク
 *
 * @param   tcb			TCBへのポインタ
 * @param   work		TALKWIN_SLIDE_WORK構造体
 */
//--------------------------------------------------------------
static void TalkWinSlideInOutMain(TCB_PTR tcb, void *work)
{
	TALKWIN_SLIDE_WORK *tsw = work;
	
	switch(tsw->seq){
	case 0:
		if(tsw->slide_dir == TALKWIN_SLIDE_DIR_OUT){
			tsw->x += TALKWIN_SLIDE_SPEED;
			if((tsw->x >> 8) >= TALKWIN_SLIDE_DOT_LEN){
				tsw->x = TALKWIN_SLIDE_DOT_LEN << 8;
				tsw->seq++;
			}
		}
		else{
			tsw->x -= TALKWIN_SLIDE_SPEED;
			if(tsw->x <= (FRAME_WIN_DEFAULT_X << 8)){
				tsw->x = FRAME_WIN_DEFAULT_X << 8;
				tsw->seq++;
			}
		}
		GF_BGL_ScrollReq(tsw->sys->bgl, ACTIN_FRAME_WIN, GF_BGL_SCROLL_X_SET, tsw->x >> 8);
		break;
	default:
		if(tsw->slide_dir == TALKWIN_SLIDE_DIR_IN){
			AT_TalkWinScreenWrite(tsw->sys, TALKWIN_SCREEN_WRITE_AFTER);
		}
		AT_TalkWinSlideCoverOBJDelete(tsw->sys);
		*(tsw->end_flag) = TRUE;
		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		return;
	}
}

//--------------------------------------------------------------
/**
 * @brief   ブリーダーパネルの上に乗っかっているOBJに対して、半透明OBJモードをセットする
 *
 * @param   apw			演技力部門管理ワークへのポインタ
 * @param   on_off		ノーマル：GX_OAM_MODE_NORMAL、半透明：GX_OAM_MODE_XLU
 * @param   enable		TRUE:表示。　FALSE:非表示
 */
//--------------------------------------------------------------
static void AT_PanelObjBrdModeSet(ACTIN_PROC_WORK *apw, GXOamMode obj_mode, int enable)
{
	int i, k;
	int cap_enable, fontoam_enable;
	
	if(enable == TRUE){
		cap_enable = CATS_ENABLE_TRUE;
		fontoam_enable = TRUE;
	}
	else{
		cap_enable = CATS_ENABLE_FALSE;
		fontoam_enable = FALSE;
	}
	
	for(i = 0; i < BREEDER_MAX; i++){
		//アピールポイント
		for(k = 0; k < APPEAL_POINT_ICON_MAX; k++){
			if(apw->sys.appeal_point_cap[i][k] != NULL){
				CATS_ObjectObjModeSetCap(apw->sys.appeal_point_cap[i][k], obj_mode);
				CATS_ObjectEnableCap(apw->sys.appeal_point_cap[i][k], cap_enable);
			}
		}
		//次アイコン
		if(apw->sys.nexticon_cap[i] != NULL){
			CATS_ObjectObjModeSetCap(apw->sys.nexticon_cap[i], obj_mode);
			CATS_ObjectEnableCap(apw->sys.nexticon_cap[i], cap_enable);
		}
		//ニックネームとブリーダー名
		FONTOAM_ObjModeSet(apw->sys.fontact_oya[i].fontoam, obj_mode);
		FONTOAM_ObjModeSet(apw->sys.fontact_nickname[i].fontoam, obj_mode);
		FONTOAM_SetDrawFlag(apw->sys.fontact_oya[i].fontoam, fontoam_enable);
		FONTOAM_SetDrawFlag(apw->sys.fontact_nickname[i].fontoam, fontoam_enable);
	}
}

//--------------------------------------------------------------
/**
 * @brief   ブリーダーパネルαエフェクトを実行する
 *
 * @param   apw			演技力部門管理ワークへのポインタ
 * @param   eff_type	エフェクトタイプ(BRDPANEL_ALPHA_TYPE_???)
 * @param   end_flag	エフェクトの終了を知らせるワークへのポインタ(終了時TRUEがセットされます)
 */
//--------------------------------------------------------------
void AT_BrdPanelAlphaEffectSet(ACTIN_PROC_WORK *apw, int eff_type, u8 *end_flag)
{
	BRDPANEL_ALPHA_WORK *baw;
	
	*end_flag = FALSE;
	
	baw = sys_AllocMemory(HEAPID_ACTIN, sizeof(BRDPANEL_ALPHA_WORK));
	MI_CpuClear8(baw, sizeof(BRDPANEL_ALPHA_WORK));
	
	baw->apw = apw;
	baw->eff_type = eff_type;
	baw->end_flag = end_flag;
	
	TCB_Add(BrdPanelAlphaEffMain, baw, TCBPRI_ACTIN_BRDPANEL_ALPHA);
}

//--------------------------------------------------------------
/**
 * @brief   ブリーダーパネルαエフェクトメインタスク
 *
 * @param   tcb			TCBへのポインタ
 * @param   work		BRDPANEL_ALPHA_WORK構造体
 */
//--------------------------------------------------------------
static void BrdPanelAlphaEffMain(TCB_PTR tcb, void *work)
{
	BRDPANEL_ALPHA_WORK *baw = work;
	
	switch(baw->seq){
	case 0:	//OBJの直後が同じく半透明対象のブリーダーパネル面なので、同時に半透明すると
			//OBJの方が変な為、別々に半透明で消していく
		if(baw->eff_type == BRDPANEL_ALPHA_TYPE_RETIRE){
			baw->eva = 16 << 8;
			baw->evb = 0;
			G2_SetBlendAlpha(0, 
				GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_BG1, 16, 0);
			AT_PanelObjBrdModeSet(baw->apw, GX_OAM_MODE_XLU, TRUE);
		}
		else{
			baw->eva = 0;
			baw->evb = 16 << 8;
			G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG2, 
				GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_BG1, 0, 16);
			
			ActinBG_BrdPanelSet(baw->apw, EFF_BG_TYPE_BRDPANEL, TRUE);
		}
		
		VWaitTCB_Add(BrdPanelAlphaSet_VTask, baw, TCBPRI_ACTIN_BRDPANEL_ALPHA_VTASK);
		baw->seq++;
		break;
	case 1:
		if(baw->eff_type == BRDPANEL_ALPHA_TYPE_RETIRE && baw->eva == 0){
			AT_PanelObjBrdModeSet(baw->apw, GX_OAM_MODE_NORMAL, FALSE);
			baw->seq++;
		}
		else if(baw->eff_type == BRDPANEL_ALPHA_TYPE_RETURN && baw->evb == 0){
			baw->seq++;
		}
		break;

	case 2:	//2段階目
		if(baw->eff_type == BRDPANEL_ALPHA_TYPE_RETIRE){
			baw->eva = 16 << 8;
			baw->evb = 0;
			G2_SetBlendAlpha(GX_BLEND_PLANEMASK_BG2, 
				GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_BG1, 16, 0);
		}
		else{
			baw->eva = 0;
			baw->evb = 16 << 8;
			G2_SetBlendAlpha(0, 
				GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG3, 0, 16);
			
			AT_PanelObjBrdModeSet(baw->apw, GX_OAM_MODE_XLU, TRUE);
		}
		
		VWaitTCB_Add(BrdPanelAlphaSet_VTask, baw, TCBPRI_ACTIN_BRDPANEL_ALPHA_VTASK);
		baw->seq++;
		break;
	case 3:
		if(baw->eff_type == BRDPANEL_ALPHA_TYPE_RETIRE && baw->eva == 0){
			ActinBG_BrdPanelSet(baw->apw, EFF_BG_TYPE_EFFECT, TRUE);
			baw->seq++;
		}
		else if(baw->eff_type == BRDPANEL_ALPHA_TYPE_RETURN && baw->evb == 0){
			AT_PanelObjBrdModeSet(baw->apw, GX_OAM_MODE_NORMAL, TRUE);
			baw->seq++;
		}
		break;

	default:
		ActinExTool_DefaultBlendSet();
		
		*(baw->end_flag) = TRUE;
		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		return;
	}
}

//--------------------------------------------------------------
/**
 * @brief   ブリーダーパネルαエフェクトのVblank中転送タスク
 *
 * @param   tcb			TCBへのポインタ
 * @param   work		BRDPANEL_ALPHA_WORK構造体
 */
//--------------------------------------------------------------
static void BrdPanelAlphaSet_VTask(TCB_PTR tcb, void *work)
{
	BRDPANEL_ALPHA_WORK *baw = work;
	int end = 0;
	
	if(baw->eff_type == BRDPANEL_ALPHA_TYPE_RETIRE){
		baw->eva -= BRDPANEL_ALPHA_SP;
		baw->evb += BRDPANEL_ALPHA_SP;
		if(baw->eva <= 0){
			baw->eva = 0;
			end++;
		}
		if(baw->evb >= (16 << 8)){
			baw->evb = 16 << 8;
		}
	}
	else{
		baw->eva += BRDPANEL_ALPHA_SP;
		baw->evb -= BRDPANEL_ALPHA_SP;
		if(baw->eva >= (16 << 8)){
			baw->eva = 16 << 8;
			end++;
		}
		if(baw->evb <= 0){
			baw->evb = 0;
		}
	}
	
	G2_ChangeBlendAlpha(baw->eva >> 8, baw->evb >> 8);
	if(end > 0){
		TCB_Delete(tcb);
		return;
	}
}


//--------------------------------------------------------------
/**
 * @brief   メッセージタグ展開
 *
 * @param   apw			演技力部門管理ワークへのポインタ
 * @param   msg_tag		タグコード
 * @param   tagpara		タグ展開する場合、参照されるパラメータ類
 *                      (タグによっては必要ないので、その場合、NULLでもOK)
 */
//--------------------------------------------------------------
static void AT_MessageTagExpand(ACTIN_PROC_WORK *apw, int msg_tag, const ATAG_PARAM *tagpara,
	const void *extagpara)
{
	GF_ASSERT(msg_tag < ATAG_MINE || tagpara != NULL);	//ATAG_MINE以上の場合はtagpara必須
	
	if(tagpara != NULL){
		OS_TPrintf("mine=%d, enemy=%d, wazano=%d, num=%d, judge_no=%d\n",
			tagpara->mine_brd, tagpara->enemy_brd, tagpara->wazano, tagpara->num, 
			tagpara->judge_no);
	}

	switch(msg_tag){
	case ATAG_NONE:
		break;
	case ATAG_NOW:
		WORDSET_RegisterPokeNickName(apw->sys.wordset, 0, 
			PPPPointerGet(apw->sys.c_game->pp[apw->advance.now_breeder]));
		break;

	case ATAG_MINE:
		WORDSET_RegisterPokeNickName(apw->sys.wordset, 0, 
			PPPPointerGet(apw->sys.c_game->pp[tagpara->mine_brd]));
		break;
	case ATAG_ENEMY:
		WORDSET_RegisterPokeNickName(apw->sys.wordset, 0, 
			PPPPointerGet(apw->sys.c_game->pp[tagpara->enemy_brd]));
		break;
	case ATAG_WAZA:
		WORDSET_RegisterWazaName(apw->sys.wordset, 0, tagpara->wazano);
		break;
	case ATAG_NUM:
		WORDSET_RegisterNumber(apw->sys.wordset, 0, tagpara->num, 1, 
			NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT);
		break;
	case ATAG_JUDGE:
		WORDSET_RegisterJudgeName(apw->sys.wordset, 0, 
			apw->sys.c_game->jd[tagpara->judge_no].name_id);
		break;
	case ATAG_MINE_ENEMY:
		WORDSET_RegisterPokeNickName(apw->sys.wordset, 0, 
			PPPPointerGet(apw->sys.c_game->pp[tagpara->mine_brd]));
		WORDSET_RegisterPokeNickName(apw->sys.wordset, 1, 
			PPPPointerGet(apw->sys.c_game->pp[tagpara->enemy_brd]));
		break;
	case ATAG_MINE_WAZA:
		WORDSET_RegisterPokeNickName(apw->sys.wordset, 0, 
			PPPPointerGet(apw->sys.c_game->pp[tagpara->mine_brd]));
		WORDSET_RegisterWazaName(apw->sys.wordset, 1, tagpara->wazano);
		break;
	case ATAG_MINE_NUM:
		WORDSET_RegisterPokeNickName(apw->sys.wordset, 0, 
			PPPPointerGet(apw->sys.c_game->pp[tagpara->mine_brd]));
		WORDSET_RegisterNumber(apw->sys.wordset, 1, tagpara->num, 1, 
			NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT);
		break;
	case ATAG_MINE_JUDGE:
		WORDSET_RegisterPokeNickName(apw->sys.wordset, 0, 
			PPPPointerGet(apw->sys.c_game->pp[tagpara->mine_brd]));
		WORDSET_RegisterJudgeName(apw->sys.wordset, 1, 
			apw->sys.c_game->jd[tagpara->judge_no].name_id);
		break;

	case ATAG_ENEMY_MINE:
		WORDSET_RegisterPokeNickName(apw->sys.wordset, 0, 
			PPPPointerGet(apw->sys.c_game->pp[tagpara->enemy_brd]));
		WORDSET_RegisterPokeNickName(apw->sys.wordset, 1, 
			PPPPointerGet(apw->sys.c_game->pp[tagpara->mine_brd]));
		break;
	case ATAG_ENEMY_WAZA:
		WORDSET_RegisterPokeNickName(apw->sys.wordset, 0, 
			PPPPointerGet(apw->sys.c_game->pp[tagpara->enemy_brd]));
		WORDSET_RegisterWazaName(apw->sys.wordset, 1, tagpara->wazano);
		break;
	case ATAG_ENEMY_NUM:
		WORDSET_RegisterPokeNickName(apw->sys.wordset, 0, 
			PPPPointerGet(apw->sys.c_game->pp[tagpara->enemy_brd]));
		WORDSET_RegisterNumber(apw->sys.wordset, 1, tagpara->num, 1, 
			NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT);
		break;
	case ATAG_ENEMY_JUDGE:
		WORDSET_RegisterPokeNickName(apw->sys.wordset, 0, 
			PPPPointerGet(apw->sys.c_game->pp[tagpara->enemy_brd]));
		WORDSET_RegisterPokeNickName(apw->sys.wordset, 1, 
			PPPPointerGet(apw->sys.c_game->pp[tagpara->mine_brd]));
		break;

	case ATAG_WAZA_MINE:
		WORDSET_RegisterWazaName(apw->sys.wordset, 0, tagpara->wazano);
		WORDSET_RegisterPokeNickName(apw->sys.wordset, 1, 
			PPPPointerGet(apw->sys.c_game->pp[tagpara->mine_brd]));
		break;
	case ATAG_WAZA_ENEMY:
		WORDSET_RegisterWazaName(apw->sys.wordset, 0, tagpara->wazano);
		WORDSET_RegisterPokeNickName(apw->sys.wordset, 1, 
			PPPPointerGet(apw->sys.c_game->pp[tagpara->enemy_brd]));
		break;
	case ATAG_WAZA_NUM:
		WORDSET_RegisterWazaName(apw->sys.wordset, 0, tagpara->wazano);
		WORDSET_RegisterNumber(apw->sys.wordset, 1, tagpara->num, 1, 
			NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT);
		break;
	case ATAG_WAZA_JUDGE:
		WORDSET_RegisterWazaName(apw->sys.wordset, 0, tagpara->wazano);
		WORDSET_RegisterPokeNickName(apw->sys.wordset, 1, 
			PPPPointerGet(apw->sys.c_game->pp[tagpara->mine_brd]));
		break;

	case ATAG_NUM_MINE:
		WORDSET_RegisterNumber(apw->sys.wordset, 0, tagpara->num, 1, 
			NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT);
		WORDSET_RegisterPokeNickName(apw->sys.wordset, 1, 
			PPPPointerGet(apw->sys.c_game->pp[tagpara->mine_brd]));
		break;
	case ATAG_NUM_ENEMY:
		WORDSET_RegisterNumber(apw->sys.wordset, 0, tagpara->num, 1, 
			NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT);
		WORDSET_RegisterPokeNickName(apw->sys.wordset, 1, 
			PPPPointerGet(apw->sys.c_game->pp[tagpara->enemy_brd]));
		break;
	case ATAG_NUM_WAZA:
		WORDSET_RegisterNumber(apw->sys.wordset, 0, tagpara->num, 1, 
			NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT);
		WORDSET_RegisterWazaName(apw->sys.wordset, 1, tagpara->wazano);
		break;
	case ATAG_NUM_JUDGE:
		WORDSET_RegisterNumber(apw->sys.wordset, 0, tagpara->num, 1, 
			NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT);
		WORDSET_RegisterPokeNickName(apw->sys.wordset, 1, 
			PPPPointerGet(apw->sys.c_game->pp[tagpara->mine_brd]));
		break;

	case ATAG_JUDGE_MINE:
		WORDSET_RegisterJudgeName(apw->sys.wordset, 0, 
			apw->sys.c_game->jd[tagpara->judge_no].name_id);
		WORDSET_RegisterPokeNickName(apw->sys.wordset, 1, 
			PPPPointerGet(apw->sys.c_game->pp[tagpara->mine_brd]));
		break;
	case ATAG_JUDGE_ENEMY:
		WORDSET_RegisterJudgeName(apw->sys.wordset, 0, 
			apw->sys.c_game->jd[tagpara->judge_no].name_id);
		WORDSET_RegisterPokeNickName(apw->sys.wordset, 1, 
			PPPPointerGet(apw->sys.c_game->pp[tagpara->enemy_brd]));
		break;
	case ATAG_JUDGE_WAZA:
		WORDSET_RegisterJudgeName(apw->sys.wordset, 0, 
			apw->sys.c_game->jd[tagpara->judge_no].name_id);
		WORDSET_RegisterWazaName(apw->sys.wordset, 1, tagpara->wazano);
		break;
	case ATAG_JUDGE_NUM:
		WORDSET_RegisterJudgeName(apw->sys.wordset, 0, 
			apw->sys.c_game->jd[tagpara->judge_no].name_id);
		WORDSET_RegisterNumber(apw->sys.wordset, 1, tagpara->num, 1, 
			NUMBER_DISPTYPE_LEFT, NUMBER_CODETYPE_DEFAULT);
		break;

	case ATAG_MINE_JUDGE_WAZA:
		WORDSET_RegisterPokeNickName(apw->sys.wordset, 0, 
			PPPPointerGet(apw->sys.c_game->pp[tagpara->mine_brd]));
		WORDSET_RegisterJudgeName(apw->sys.wordset, 1, 
			apw->sys.c_game->jd[tagpara->judge_no].name_id);
		WORDSET_RegisterWazaName(apw->sys.wordset, 2, tagpara->wazano);
		break;
	
	case ATAG_EXCODE_JUDGESUFFER:
		{
			const JUDGE_SUFFER_REVIEW *jsr = extagpara;
			int i;
			
			WORDSET_RegisterJudgeName(apw->sys.wordset, 0, 
				apw->sys.c_game->jd[jsr->judge_no].name_id);
			for(i = 0; i < BREEDER_MAX; i++){
				if(jsr->suffer_breeder[i] == BREEDER_MAX){
					break;
				}
				WORDSET_RegisterPokeNickName(apw->sys.wordset, 1 + i, 
					PPPPointerGet(apw->sys.c_game->pp[jsr->suffer_breeder[i]]));
			}
		}
		break;
		
	default:
		GF_ASSERT(0 && "認識できないタグです\n");
		break;
	}
}

//--------------------------------------------------------------
/**
 * @brief   会話メッセージウィンドウをクリアする
 * @param   apw		演技力部門管理ワークへのポインタ
 */
//--------------------------------------------------------------
void AT_TalkMessageWinClear(ACTIN_PROC_WORK *apw)
{
	GF_BGL_BmpWinDataFill(&apw->sys.win[ACTIN_BMPWIN_TALK], 0xff);
	GF_BGL_BmpWinOn(&apw->sys.win[ACTIN_BMPWIN_TALK]);
}

//--------------------------------------------------------------
/**
 * @brief   会話メッセージセット
 *
 * @param   apw			演技力部門管理ワークへのポインタ
 * @param   msg_id		メッセージID
 * @param   msg_tag		タグコード
 * @param   tagpara		タグ展開する場合、参照されるパラメータ類
 *                      (タグによっては必要ないので、その場合、NULLでもOK)
 * @param   extagpara	タグ展開する場合、参照されるパラメータ類
 *                      (タグによっては必要ないので、その場合、NULLでもOK)
 * @param   all_put		TRUE:メッセージ一括表示
 */
//--------------------------------------------------------------
static void AT_TalkMessageSet(ACTIN_PROC_WORK *apw, MSGDATA_MANAGER *msg_man, 
	u32 msg_id, int msg_tag, const ATAG_PARAM *tagpara, const void *extagpara, int all_put)
{
	STRBUF *message_src;
	u32 wait;
	
//	BattleMSG_TagExpand(bw,mp);
//	BattleMSG_MsgExpand(bw,msg_m,mp);

	if(all_put == TRUE){
		wait = MSG_ALLPUT;
	}
	else{
		if(apw->consys->sio_flag == FALSE){
			wait = CONFIG_GetMsgPrintSpeed(apw->consys->config);
		}
		else{
			wait = CONTEST_SIO_MSG_SPEED;
		}
	}
	
	message_src = MSGMAN_AllocString(msg_man, msg_id);
	AT_MessageTagExpand(apw, msg_tag, tagpara, extagpara);
	WORDSET_ExpandStr(apw->sys.wordset, apw->sys.msg_buf, message_src);
	
	GF_BGL_BmpWinDataFill(&apw->sys.win[ACTIN_BMPWIN_TALK], 0xff);
	apw->sys.talk_msg_index = GF_STR_PrintSimple(&apw->sys.win[ACTIN_BMPWIN_TALK], 
		FONT_TALK, apw->sys.msg_buf, 0, 0, wait, NULL);
	if(wait == MSG_ALLPUT){
		apw->sys.talk_msg_index = 0xff;
		GF_BGL_BmpWinOn(&apw->sys.win[ACTIN_BMPWIN_TALK]);
	}
	
	if(GF_BGL_ScrollGetX(apw->sys.bgl, ACTIN_FRAME_WIN) == FRAME_WIN_DEFAULT_X){
		//GF_BGL_BmpWinDataFillで枠まで塗りつぶされるので再描画
//		AT_TalkWinScreenWrite(&apw->sys, TALKWIN_SCREEN_WRITE_AFTER);
	}
	
	STRBUF_Delete(message_src);
}

//--------------------------------------------------------------
/**
 * @brief   ノーマル会話用のメッセージセット
 *
 * @param   apw				演技力部門管理ワークへのポインタ
 * @param   a_talk_id		A_TALK_???
 * @param   tagpara		タグ展開する場合、参照されるパラメータ類
 *                      (タグによっては必要ないので、その場合、NULLでもOK)
 */
//--------------------------------------------------------------
void AT_A_TalkMessageSet(ACTIN_PROC_WORK *apw, u32 a_talk_id, const ATAG_PARAM *tagpara,
	const void *extagpara)
{
	u32 msg_id, msg_tag, all_put;
	
	GF_ASSERT(a_talk_id < NELEMS(ActinTalkMsgData));
	
	msg_id = ActinTalkMsgData[a_talk_id].msg_id;
	msg_tag = ActinTalkMsgData[a_talk_id].msg_tag;
	all_put = ActinTalkMsgData[a_talk_id].all_put;
	AT_TalkMessageSet(apw, apw->sys.actin_msg, msg_id, msg_tag, tagpara, extagpara, all_put);
}

//--------------------------------------------------------------
/**
 * @brief   技効果用の会話メッセージセット
 *
 * @param   apw			演技力部門管理ワークへのポインタ
 * @param   apno		アピール番号
 * @param   msg_type	メッセージタイプ(KOUKA_MSGID_???)
 * @param   tagpara		タグ展開する場合、参照されるパラメータ類
 *                      (タグによっては必要ないので、その場合、NULLでもOK)
 */
//--------------------------------------------------------------
void AT_WazaKoukaTalkMessageSet(ACTIN_PROC_WORK *apw, int apno, int msg_type, 
	const ATAG_PARAM *tagpara, const void *extagpara)
{
	u32 msg_id, msg_tag;
	
	ConTool_GetKoukaMsgID(apno, msg_type, &msg_id, &msg_tag);
	AT_TalkMessageSet(apw, apw->sys.wazakouka_msg, msg_id, msg_tag, tagpara, extagpara, FALSE);
}

//--------------------------------------------------------------
/**
 * @brief   会話メッセージフォントが表示しきっているかチェック
 * @param   apw		演技力部門管理ワークへのポインタ
 * @retval  0=終了
 */
//--------------------------------------------------------------
int AT_TalkMessageEndCheck(ACTIN_PROC_WORK *apw)
{
	if(apw->sys.talk_msg_index == 0xff){
		return 0;	//一括表示
	}
	return GF_MSG_PrintEndCheck(apw->sys.talk_msg_index);
}

//--------------------------------------------------------------
/**
 * @brief   ブリーダー情報のフォントOAMを生成する
 * @param   apw				演技力部門管理ワークへのポインタ
 * @param   breeder_no		ブリーダー番号
 */
//--------------------------------------------------------------
void AT_BreederPanelFontOamCreate(ACTIN_PROC_WORK *apw, int breeder_no)
{
//	STRBUF *oyaname_buf;
	STRBUF *nickname_buf;
	GF_PRINTCOLOR color;
	
	nickname_buf = STRBUF_Create(BUFLEN_POKEMON_NAME, HEAPID_ACTIN);
//	oyaname_buf = STRBUF_Create(BUFLEN_PERSON_NAME, HEAPID_ACTIN);

	PokeParaGet(apw->sys.c_game->pp[breeder_no], ID_PARA_nickname_buf, nickname_buf);
//	PokeParaGet(apw->sys.c_game->pp[breeder_no], ID_PARA_oyaname_buf, oyaname_buf);

	if(breeder_no == apw->consys->c_game.my_breeder_no){
		color = MSGCOLOR_BREEDERPARAM_MINE;
	}
	else{
		color = MSGCOLOR_BREEDERPARAM;
	}
	
	ADV_FontOamCreate(HEAPID_ACTIN, apw->sys.bgl, apw->sys.crp, apw->sys.fontoam_sys,
		&apw->sys.fontact_nickname[breeder_no], nickname_buf, 
		FONT_SYSTEM, color, 0, PLTTID_FONTACT, 
		0, 0, FALSE, ACTIN_BGPRI_BREEDER_PARAM, ACTIN_SOFTPRI_BREEDER_PARAM);
	ADV_FontOamCreate(HEAPID_ACTIN, apw->sys.bgl, apw->sys.crp, apw->sys.fontoam_sys,
		&apw->sys.fontact_oya[breeder_no], 
		apw->consys->c_game.breeder_name_str[breeder_no],//oyaname_buf, 
		FONT_SYSTEM, color, 0, PLTTID_FONTACT, 
		0, 0, FALSE, ACTIN_BGPRI_BREEDER_PARAM, ACTIN_SOFTPRI_BREEDER_PARAM);

	STRBUF_Delete(nickname_buf);
//	STRBUF_Delete(oyaname_buf);
}

//--------------------------------------------------------------
/**
 * @brief   ブリーダー情報のフォントOAMを全て生成する
 * @param   apw		演技力部門管理ワークへのポインタ
 */
//--------------------------------------------------------------
void AT_BreederPanelFontOamCreateAll(ACTIN_PROC_WORK *apw)
{
	int i;
	
	for(i = 0; i < BREEDER_MAX; i++){
		AT_BreederPanelFontOamCreate(apw, i);
	}
	AT_BreederPanelFontOamPosUpdate(apw);
}

//--------------------------------------------------------------
/**
 * @brief   ブリーダー情報のフォントOAMを全て削除する
 * @param   sys		ダンスシステムワークへのポインタ
 */
//--------------------------------------------------------------
void AT_BreederPanelFontOamDeleteAll(ACTIN_PROC_WORK *apw)
{
	int i;
	
	for(i = 0; i < BREEDER_MAX; i++){
		ADV_FontOamDelete(&apw->sys.fontact_nickname[i]);
		ADV_FontOamDelete(&apw->sys.fontact_oya[i]);
	}
}

//--------------------------------------------------------------
/**
 * @brief   ブリーダー情報のフォントOAMの座標をブリーダーソートに合わせて更新する
 * @param   apw		演技力部門管理ワークへのポインタ
 */
//--------------------------------------------------------------
void AT_BreederPanelFontOamPosUpdate(ACTIN_PROC_WORK *apw)
{
	int pos, breeder_no;
	
	for(pos = 0; pos < BREEDER_MAX; pos++){
		breeder_no = apw->a_game.breeder_sort[pos];
		ADV_FontOamPosSet(&apw->sys.fontact_nickname[breeder_no], 
			BREEDER_PANEL_NICK_X, BREEDER_PANEL_NICK_Y + BREEDER_PANEL_NICK_Y_SPACE * pos,
			FALSE);
		ADV_FontOamPosSet(&apw->sys.fontact_oya[breeder_no], 
			BREEDER_PANEL_OYA_X, BREEDER_PANEL_OYA_Y + BREEDER_PANEL_OYA_Y_SPACE * pos, 
			FALSE);
	}
}


//--------------------------------------------------------------
/**
 * @brief   次アイコンのリソースロードする
 *
 * @param   csp
 * @param   crp
 */
//--------------------------------------------------------------
void AT_NextIconResourceLoad(CATS_SYS_PTR csp, CATS_RES_PTR crp)
{
	//パレットは常駐パレットを使用するのでロードなし

	CATS_LoadResourceCharArc(csp, crp, ARC_CONTEST_OBJ, 
		NEXT_ICON_NCGR_BIN, 1, NNS_G2D_VRAM_TYPE_2DMAIN, CHARID_NEXT_ICON);
	CATS_LoadResourceCellArc(csp, crp, ARC_CONTEST_OBJ, NEXT_ICON_NCER_BIN, 1, CELLID_NEXT_ICON);
	CATS_LoadResourceCellAnmArc(csp, crp, ARC_CONTEST_OBJ, NEXT_ICON_NANR_BIN, 
		1, CELLANMID_NEXT_ICON);
}

//--------------------------------------------------------------
/**
 * @brief   次アイコンのリソースを解放する
 *
 * @param   crp		
 */
//--------------------------------------------------------------
void AT_NextIconResourceFree(CATS_RES_PTR crp)
{
	//パレットは常駐パレットなので削除なし
	CATS_FreeResourceChar(crp, CHARID_NEXT_ICON);
	CATS_FreeResourceCell(crp, CELLID_NEXT_ICON);
	CATS_FreeResourceCellAnm(crp, CELLANMID_NEXT_ICON);
}

//--------------------------------------------------------------
/**
 * @brief   次アイコンのアクター生成とアニメ設定を行う
 *
 * @param   sys				演技力システムワークへのポインタ
 * @param   breeder_pos		表示させるブリーダー位置
 * @param   next_pos		次のターン何番目、と表示させるか
 *
 * 既にbreeder_posの位置にアクターが生成されている場合はアニメの設定だけ行います
 */
//--------------------------------------------------------------
void AT_NextIconActorAnimeSet(ACTIN_SYSTEM_PARAM *sys, int breeder_pos, int next_pos)
{
	//アクターが生成されていない場合は生成
	if(sys->nexticon_cap[breeder_pos] == NULL){
		sys->nexticon_cap[breeder_pos] = CATS_ObjectAdd_S(sys->csp, sys->crp, &NextIconObjParam);
	}
	
	//アニメ設定
	CATS_ObjectAnimeSeqSetCap(sys->nexticon_cap[breeder_pos], next_pos);
	
	//座標設定
	CATS_ObjectPosSetCap(sys->nexticon_cap[breeder_pos], 
		NEXT_ICON_POS_X, NEXT_ICON_POS_Y + breeder_pos * NEXT_ICON_POS_Y_SPACE);

	CATS_ObjectUpdate(sys->nexticon_cap[breeder_pos]->act);
}

//--------------------------------------------------------------
/**
 * @brief   現在場に出ている次アイコンアクターを全て削除
 *
 * @param   sys				演技力システム構造体へのポインタ
 */
//--------------------------------------------------------------
void AT_NextIconActorDelAll(ACTIN_SYSTEM_PARAM *sys)
{
	int i;
	
	for(i = 0; i < BREEDER_MAX; i++){
		if(sys->nexticon_cap[i] != NULL){
			CATS_ActorPointerDelete_S(sys->nexticon_cap[i]);
			sys->nexticon_cap[i] = NULL;
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   メッセージタグ展開パラメータに各ブリーダー毎の初期値データをセットする
 *
 * @param   apw				演技力部門管理ワークへのポインタ
 * @param   tagpara			タグパラメータ代入先
 * @param   breeder_no		ブリーダー番号
 */
//--------------------------------------------------------------
void AT_MsgTagParaInitDataSet(ACTIN_PROC_WORK *apw, ATAG_PARAM *tagpara, int breeder_no)
{
	MI_CpuClear8(tagpara, sizeof(ATAG_PARAM));
	tagpara->mine_brd = breeder_no;
	tagpara->wazano = apw->a_game.waza_no[breeder_no];
	tagpara->judge_no = apw->a_game.judge_no[breeder_no];
}

//--------------------------------------------------------------
/**
 * @brief   合計AP値から審判のコメントレベルのメッセージIDとタグを取得する
 *
 * @param   breeder_no		ブリーダー番号
 * @param   app_total		合計AP
 * @param   tagpara			タグ代入先
 *
 * @retval  A_TALK_???
 */
//--------------------------------------------------------------
u32 AT_MsgTagJudgeCommentCreate(int breeder_no, int app_total, ATAG_PARAM *tagpara)
{
	int a_talk_id;
	
	tagpara->mine_brd = breeder_no;
	if(app_total <= JUDGE_COMMENT_LEVEL_0){
		a_talk_id = A_TALK_TURN_RESULT_0;
	}
	else if(app_total <= JUDGE_COMMENT_LEVEL_1){
		a_talk_id = A_TALK_TURN_RESULT_1;
	}
	else if(app_total <= JUDGE_COMMENT_LEVEL_2){
		a_talk_id = A_TALK_TURN_RESULT_2;
	}
	else if(app_total <= JUDGE_COMMENT_LEVEL_3){
		a_talk_id = A_TALK_TURN_RESULT_3;
	}
	else{
		a_talk_id = A_TALK_TURN_RESULT_4;
	}
	return a_talk_id;
}

//--------------------------------------------------------------
/**
 * @brief   現在までの得点から観客の歓声のボリュームを取得する
 * @param   app_total		現在までの得点
 * @retval  歓声のボリューム
 */
//--------------------------------------------------------------
int AT_AudienceVolumeGet(int app_total)
{
	int volume_level;
	int volume;
	
	volume_level = app_total / AUDIENCE_VOLUME_LEVEL_POINT;
	if(volume_level >= AUDIENCE_VOLUME_LEVEL_MAX){
		volume_level = AUDIENCE_VOLUME_LEVEL_MAX - 1;
	}
	
	volume = AudienceVolume[volume_level];
	GF_ASSERT(volume >= 0);
	GF_ASSERT(volume <= 127);
	return volume;
}

//--------------------------------------------------------------
/**
 * @brief   観客アニメを実行する
 *
 * @param   apw				演技力部門管理ワークへのポインタ
 * @param   voltage			ボルテージ値
 * @param   start_wait		開始ウェイト
 * @param   se_volume		歓声SEのボリューム
 * @param   fade			TRUE:フェードを行う
 * @param   end_flag		エフェクト終了時に、終了フラグをセットするワークへのポインタ
 */
//--------------------------------------------------------------
void AT_AudienceAnimeSet(ACTIN_PROC_WORK *apw, int voltage, u8 start_wait, int se_volume, int fade,
	u8 *end_flag)
{
	AUDIENCE_ANIME_WORK *aaw;
	
	*end_flag = FALSE;
	
	aaw = sys_AllocMemory(HEAPID_ACTIN, sizeof(AUDIENCE_ANIME_WORK));
	MI_CpuClear8(aaw, sizeof(AUDIENCE_ANIME_WORK));
	aaw->apw = apw;
	aaw->end_flag = end_flag;
	aaw->start_wait = start_wait;
	aaw->voltage = voltage;
	aaw->se_volume = se_volume;
	aaw->fade = fade;
	TCB_Add(AudienceAnimeMain, aaw, TCBPRI_ACTIN_AUDIENCE_ANIME);
}

//--------------------------------------------------------------
/**
 * @brief   観客アニメ実行タスク
 *
 * @param   tcb			TCBへのポインタ
 * @param   work		AUDIENCE_ANIME_WORK構造体
 */
//--------------------------------------------------------------
static void AudienceAnimeMain(TCB_PTR tcb, void *work)
{
	AUDIENCE_ANIME_WORK *aaw = work;
	
	switch(aaw->seq){
	case 0:
		if(aaw->start_wait > 0){
			aaw->start_wait--;
			break;
		}
		Snd_SePlay(ASE_AUDIENCE);
		Snd_PlayerSetInitialVolumeBySeqNo(ASE_AUDIENCE, aaw->se_volume);
		aaw->seq++;
		//break;
	case 1:
		{
			u32 scr_id;
			
			if(aaw->anm_no == 0){
				scr_id = CON_BG2_NSCR_BIN;
			}
			else{
				scr_id = CON_BG_NSCR_BIN;
			}
			ArcUtil_ScrnSet(ARC_CONTEST_BG, scr_id, aaw->apw->sys.bgl, 
				ACTIN_FRAME_AUDIENCE, 0, 0, 1, HEAPID_ACTIN);
		}
		
		aaw->seq++;
		break;
	case 2:
		aaw->wait++;
		if(aaw->wait > AUDIENCE_ANIME_WAIT){
			aaw->wait = 0;
			aaw->anm_no ^= 1;
			aaw->seq--;
			
			if(aaw->anm_no == 0){
				aaw->loop++;
				if(aaw->loop > AUDIENCE_ANIME_LOOP){
					aaw->seq = 0xff;
					break;
				}
			}
		}
		
		if(aaw->fade == TRUE){
			int evy_max;
			evy_max = aaw->voltage * AUDIENCE_FADE_MAX_EVY / VOLTAGE_POINT_FULL;
			if(aaw->evy < evy_max){
				aaw->evy += AUDIENCE_FADE_ADD_EVY;
				if(aaw->evy > evy_max){
					aaw->evy = evy_max;
				}
				SoftFadePfd(aaw->apw->sys.pfd, FADE_MAIN_BG, AUDIENCE_FADE_COLOR_POS, 
					AUDIENCE_FADE_COLOR_NUM, aaw->evy, AUDIENCE_FADE_RGB);
			}
		}
		
		break;
	default:
		if(aaw->fade == TRUE){
			if(aaw->evy != 0){
				aaw->evy -= AUDIENCE_FADE_ADD_EVY;
				if(aaw->evy < 0){
					aaw->evy = 0;
				}
				SoftFadePfd(aaw->apw->sys.pfd, FADE_MAIN_BG, AUDIENCE_FADE_COLOR_POS, 
					AUDIENCE_FADE_COLOR_NUM, aaw->evy, AUDIENCE_FADE_RGB);
				break;
			}
		}

		*(aaw->end_flag) = TRUE;
		
		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		return;
	}
}

//--------------------------------------------------------------
/**
 * @brief   各ブリーダーパネル上のAPハートをパネルに吸い込まれていくエフェクトを起動する
 *
 * @param   apw				演技力部門管理ワークへのポインタ
 * @param   breeder_no		ブリーダー番号
 * @param   breeder_pos		ブリーダー位置
 * @param   effect_count	エフェクトカウンタへのポインタ
 * @param   panel_flash		ブリーダーパネルフラッシュ動作ワークへのポインタ
 *
 * effect_count = エフェクトが生成される毎にインクリメントされ、エフェクトが終了するたびに
 * デクリメントされます。この関数呼出し後、エフェクトカウンタが0になったら全てのエフェクトが
 * 終了した、と判定する事が出来ます。
 */
//--------------------------------------------------------------
void AT_APHeartMovePanel(ACTIN_PROC_WORK *apw, int breeder_no, int breeder_pos, u8 *effect_count,
	PANEL_FLASH_WORK *panel_flash)
{
	APHEART_MOVE_WORK *heart_move;
	s32 center_x, center_y;
	s16 start_x, start_y, x, y;
	int i;
	u32 furihaba;
	u16 angle;
	
	*effect_count = 0;
	
	center_x = BREEDER_PANEL_DOT_LEN_X / 2;
	center_y = BREEDER_PANEL_DOT_LEN_Y / 2 + breeder_pos * BREEDER_PANEL_DOT_LEN_Y;
	
	furihaba = 0;
	angle = 0;
	
	for(i = 0; i < APPEAL_POINT_ICON_MAX; i++){
		if(apw->sys.appeal_point_cap[breeder_no][i] == NULL){
			continue;
		}
		
		if(*effect_count == 0){
			//ふり幅取得
			CATS_ObjectPosGetCap(apw->sys.appeal_point_cap[breeder_no][i], 
				&start_x, &start_y);
			furihaba = APP_StraightDistance(
				MATH_IAbs(start_x - center_x), MATH_IAbs(start_y - center_y)) * 0x100;

			//角度取得
			{
				f32 len_x, len_start_y;
				len_x = start_x - center_x;
				len_start_y = start_y - center_y;
				angle = FX_Atan2Idx(FX_F32_TO_FX32(len_start_y), FX_F32_TO_FX32(len_x));
				//65535がMAXの角度を、360度*100倍した角度がMAXのものに変換する
				angle = (360*100) * angle / 65535;
			}
		}
		
		heart_move = sys_AllocMemory(HEAPID_ACTIN, sizeof(APHEART_MOVE_WORK));
		MI_CpuClear8(heart_move, sizeof(APHEART_MOVE_WORK));
		
		heart_move->panel_flash = panel_flash;
		
		heart_move->cap = apw->sys.appeal_point_cap[breeder_no][i];
		
		heart_move->furihaba = furihaba;
		heart_move->angle = angle;
		
		heart_move->add_angle = APHEART_ADD_ANGLE;
		heart_move->center_x = center_x;
		heart_move->center_y = center_y;
		heart_move->effect_count = effect_count;
		heart_move->start_x = start_x;
		heart_move->start_y = start_y;
		
		CATS_ObjectPosGetCap(apw->sys.appeal_point_cap[breeder_no][i], &x, &y);
		heart_move->slide_add_x = (MATH_IAbs(start_x - x) << 8) 
			/ (APHEART_START_WAIT * (*effect_count));
		heart_move->slide_x = x << 8;
		
		TCB_Add(APHeartMoveTask, heart_move, TCBPRI_ACTIN_EFFECT);
		
		(*effect_count)++;
	}
}

//--------------------------------------------------------------
/**
 * @brief   APハート回転移動タスクメイン
 * @param   tcb			TCBへのポインタ
 * @param   work		APハート回転移動用ワークへのポインタ
 */
//--------------------------------------------------------------
static void APHeartMoveTask(TCB_PTR tcb, void *work)
{
	APHEART_MOVE_WORK *heart_move = work;
	int offset_x, offset_y, furihaba;
	s16 x, y;
	
	switch(heart_move->seq){
	case 0:		//開始位置までスライド移動
		heart_move->slide_x -= heart_move->slide_add_x;
		if(heart_move->slide_x <= (heart_move->start_x << 8)){
			heart_move->slide_x = heart_move->start_x << 8;
			heart_move->seq++;
		}
		CATS_ObjectPosGetCap(heart_move->cap, &x, &y);
		x = heart_move->slide_x >> 8;
		CATS_ObjectPosSetCap(heart_move->cap, x, y);
		break;
		
	case 1:		//Sinカーブ
		heart_move->angle += heart_move->add_angle;
		heart_move->add_angle += APHEART_ADD_FRAME_ANGLE;
		if(heart_move->angle >= 360*100){
			heart_move->angle -= 360*100;
		}
		
		if(heart_move->furihaba > APHEART_SUB_FURIHABA){
			heart_move->furihaba -= APHEART_SUB_FURIHABA;
		}
		else{
			heart_move->furihaba = 0;
		}
		if(heart_move->furihaba <= APHEART_END_FURIHABA){
			heart_move->seq++;
		}
		furihaba = heart_move->furihaba / 0x100;
		offset_x = FX_Mul(Cos360(heart_move->angle / 100), furihaba << FX32_SHIFT) / FX32_ONE;
		offset_y = FX_Mul(Sin360(heart_move->angle / 100), furihaba << FX32_SHIFT) / FX32_ONE;
		CATS_ObjectPosSetCap(heart_move->cap, 
			heart_move->center_x + offset_x, heart_move->center_y + offset_y);
		break;

	default:
		CATS_ObjectEnableCap(heart_move->cap, CATS_ENABLE_FALSE);
		Snd_SePlay(ASE_APHEART_PANEL_IN);
		BreederPanel_FlashReqSet(heart_move->panel_flash);
		
		(*(heart_move->effect_count))--;
		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		return;
	}
}

//--------------------------------------------------------------
/**
 * @brief   ボルテージポイントのアニメ実行タスクを生成する
 *
 * @param   apw				演技力部門管理ワークへのポインタ
 * @param   judge_no		審判NO
 *
 * @retval  生成したボルテージアニメワークのポインタ
 */
//--------------------------------------------------------------
VOLTAGE_POINT_ANIME_WORK * AT_VoltageAnimeSet(ACTIN_PROC_WORK *apw, int judge_no)
{
	VOLTAGE_POINT_ANIME_WORK *vaw;
	
	vaw = sys_AllocMemory(HEAPID_ACTIN, sizeof(VOLTAGE_POINT_ANIME_WORK));
	MI_CpuClear8(vaw, sizeof(VOLTAGE_POINT_ANIME_WORK));
	
	vaw->apw = apw;
	vaw->judge_no = judge_no;
	
	vaw->tcb = TCB_Add(VoltageAnimeUpdateTask, vaw, TCBPRI_ACTIN_EFFECT);
	return vaw;
}

//--------------------------------------------------------------
/**
 * @brief   ボルテージポイントアニメタスクを削除する
 * @param   vaw		ボルテージアニメワークのポインタ
 */
//--------------------------------------------------------------
void AT_VoltageAnimeDel(VOLTAGE_POINT_ANIME_WORK *vaw)
{
	TCB_Delete(vaw->tcb);
	sys_FreeMemoryEz(vaw);
}

//--------------------------------------------------------------
/**
 * @brief   ボルテージポイントアニメ実行タスク
 * @param   tcb			TCBへのポインタ
 * @param   work		ボルテージポイントアニメワークへのポインタ
 */
//--------------------------------------------------------------
static void VoltageAnimeUpdateTask(TCB_PTR tcb, void *work)
{
	VOLTAGE_POINT_ANIME_WORK *vaw = work;
	int i;
	
	for(i = 0; i < VOLTAGE_MAX; i++){
		if(vaw->apw->sys.voltage_point_cap[vaw->judge_no][i] == NULL){
			continue;
		}
		CATS_ObjectUpdateCap(vaw->apw->sys.voltage_point_cap[vaw->judge_no][i]);
	}
}

//--------------------------------------------------------------
/**
 * @brief   ボルテージポイント、パネル移動エフェクト起動
 *
 * @param   apw				演技力部門管理ワークへのポインタ
 * @param   breeder_no		ブリーダーNo
 * @param   breeder_pos		ブリーダー位置
 * @param   judge_no		審判NO
 * @param   effect_count	エフェクトカウンタへのポインタ
 *
 * effect_count = エフェクトが生成される毎にインクリメントされ、エフェクトが終了するたびに
 * デクリメントされます。この関数呼出し後、エフェクトカウンタが0になったら全てのエフェクトが
 * 終了した、と判定する事が出来ます。
 */
//--------------------------------------------------------------
void AT_VoltageMovePanel(ACTIN_PROC_WORK *apw, int breeder_no, int breeder_pos, int judge_no, u8 *effect_count)
{
	VOLPANEL_MOVE_WORK *vol_move;
	int i;
	int center_x, center_y;
	
	*effect_count = 0;
	
	center_x = BREEDER_PANEL_DOT_LEN_X / 2;
	center_y = BREEDER_PANEL_DOT_LEN_Y / 2 + breeder_pos * BREEDER_PANEL_DOT_LEN_Y;
	
	for(i = 0; i < VOLTAGE_MAX; i++){
		if(apw->sys.voltage_point_cap[judge_no][i] == NULL){
			continue;
		}
		
		vol_move = sys_AllocMemory(HEAPID_ACTIN, sizeof(VOLPANEL_MOVE_WORK));
		MI_CpuClear8(vol_move, sizeof(VOLPANEL_MOVE_WORK));
		
		vol_move->apw = apw;
		vol_move->cap = apw->sys.voltage_point_cap[judge_no][i];
		vol_move->effect_count = effect_count;
		
		vol_move->center_x = center_x;
		vol_move->center_y = center_y;
		
		vol_move->wait = VOLMOVE_START_WAIT * (*effect_count);
		
		TCB_Add(VoltageMoveTask, vol_move, TCBPRI_ACTIN_EFFECT);
		
		(*effect_count)++;
	}
}

//--------------------------------------------------------------
/**
 * @brief   ボルテージポイント、パネル移動実行タスク
 *
 * @param   tcb			TCBへのポインタ
 * @param   work		ボルテージポイント、パネル移動用ワークへのポインタ
 */
//--------------------------------------------------------------
static void VoltageMoveTask(TCB_PTR tcb, void *work)
{
	VOLPANEL_MOVE_WORK *vol_move = work;
	s16 x, y;
	int offset_x, offset_y;
	
	switch(vol_move->seq){
	case 0:
		if(vol_move->wait > 0){
			vol_move->wait--;
			break;
		}

		//回転の開始位置がCosのMAX位置に合うように座標補正
		CATS_ObjectPosGetCap(vol_move->cap, &x, &y);
		y += VOLMOVE_FURIHABA_Y >> FX32_SHIFT;
		vol_move->x = x << 8;
		vol_move->y = y << 8;
		
		Snd_SePlay(ASE_VOLTAGE_EFF_START);
		vol_move->seq++;
		//break;
	case 1:
		vol_move->angle += VOLMOVE_ADD_ANGLE;
		if(vol_move->angle >= 360*100){
			vol_move->angle -= 360*100;
		}
		offset_x = FX_Mul(Sin360(vol_move->angle / 100), VOLMOVE_FURIHABA_X) / FX32_ONE;
		offset_y = FX_Mul(Cos360(vol_move->angle / 100), VOLMOVE_FURIHABA_Y) / FX32_ONE;
		
		vol_move->y += VOLMOVE_DOWNMOVE_SP_Y;
		
		CATS_ObjectPosSetCap(vol_move->cap, (vol_move->x >> 8) + offset_x,
			(vol_move->y >> 8) + offset_y);
		
		vol_move->wait++;
		if(vol_move->wait > VOLMOVE_DOWNMOVE_FRAME){
			vol_move->wait = 0;
			CATS_ObjectPosGetCap(vol_move->cap, &x, &y);
			vol_move->x = x << 8;
			vol_move->y = y << 8;
			{//直進移動速度取得
				s32 len_x, len_y, frame;
				
				len_x = (MATH_IAbs(x - vol_move->center_x) << 8);
				len_y = (MATH_IAbs(y - vol_move->center_y) << 8);
				frame = len_x / VOLMOVE_STRAIGHT_SP_X;
				vol_move->add_x = VOLMOVE_STRAIGHT_SP_X;
				vol_move->add_y = len_y / frame;
				if(vol_move->center_y < y){
					vol_move->add_y = -vol_move->add_y;
				}
			}
			Snd_SePlay(ASE_VOLTAGE_STRAIGHT_MOVE);
			vol_move->seq++;
		}
		break;
	case 2:
		vol_move->x -= vol_move->add_x;
		vol_move->y += vol_move->add_y;
		if(vol_move->x <= (vol_move->center_x << 8)){
			vol_move->x = vol_move->center_x << 8;
			vol_move->seq++;
		}
		CATS_ObjectPosSetCap(vol_move->cap, vol_move->x >> 8, vol_move->y >> 8);
		break;
	default:
		CATS_ObjectEnableCap(vol_move->cap, CATS_ENABLE_FALSE);
		Snd_SePlay(ASE_VOLTAGE_PANEL_IN);
		
		(*(vol_move->effect_count))--;
		sys_FreeMemoryEz(work);
		TCB_Delete(tcb);
		return;
	}
}

//--------------------------------------------------------------
/**
 * @brief   演技力部門開始時に表示するA_Talk用メッセージIDを取得する
 * @param   con_type		CONTYPE_???
 * @retval  A_TALK用メッセージID
 */
//--------------------------------------------------------------
u32 AT_A_TalkIDGet_Host01(int con_type)
{
	const u16 HostMsgID[] = {
		A_TALK_ACT_HOST_06,
		A_TALK_ACT_HOST_05,
		A_TALK_ACT_HOST_01,
		A_TALK_ACT_HOST_03,
		A_TALK_ACT_HOST_04,
	};
	
	return HostMsgID[con_type];
}

//--------------------------------------------------------------
/**
 * @brief   ボルテージ上昇時に表示するA_Talk用メッセージIDを取得する
 * @param   waza_con_type		技のCONTYPE_???
 * @retval  A_TALK用メッセージID
 */
//--------------------------------------------------------------
u32 AT_A_TalkIDGet_VoltageUp(int waza_con_type)
{
	const u16 VoltageUpMsgID[] = {
		A_TALK_VOLTAGE_UP_2,
		A_TALK_VOLTAGE_UP_3,
		A_TALK_VOLTAGE_UP_4,
		A_TALK_VOLTAGE_UP_5,
		A_TALK_VOLTAGE_UP_6,
	};
	
	return VoltageUpMsgID[waza_con_type];
}

//--------------------------------------------------------------
/**
 * @brief   ボルテージ下降時に表示するA_Talk用メッセージIDを取得する
 * @param   waza_con_type		技のCONTYPE_???
 * @retval  A_TALK用メッセージID
 */
//--------------------------------------------------------------
u32 AT_A_TalkIDGet_VoltageSub(int waza_con_type)
{
	const u16 VoltageDownMsgID[] = {
		A_TALK_VOLTAGE_SUB_10,
		A_TALK_VOLTAGE_SUB_2,
		A_TALK_VOLTAGE_SUB_3,
		A_TALK_VOLTAGE_SUB_4,
		A_TALK_VOLTAGE_SUB_5,
	};
	
	return VoltageDownMsgID[waza_con_type];
}

//--------------------------------------------------------------
/**
 * @brief   技エフェクト発動の為のパラメータ取得
 *
 * @param   consys			コンテストシステムワークへのポインタ
 * @param   breeder_no		ブリーダー番号
 * @param   wazano			技番号
 * @param   wazapara		パラメータ代入先
 */
//--------------------------------------------------------------
void AT_WazaEffParamSet(CONTEST_SYSTEM *consys, int breeder_no, int wazano, 
	CON_WAZAEFF_PARAM *wazapara)
{
	MI_CpuClear8(wazapara, sizeof(CON_WAZAEFF_PARAM));
	
	wazapara->wazano = wazano;
	
	switch(wazano){
	case WAZANO_SOORAABIIMU:
	case WAZANO_KAMAITATI:
	case WAZANO_ROKETTOZUTUKI:
	case WAZANO_GODDOBAADO:
		wazapara->loop = 1;
		break;
	case WAZANO_ONGAESI:
		wazapara->natukido = 255;	//威力Max状態のを出す
		break;
	case WAZANO_YATUATARI:
		wazapara->natukido = 0;	//威力Max状態のを出す
		break;
	case WAZANO_NOROI:	//のろい
		{
			int type1, type2;
			
			type1 = PokeParaGet(consys->c_game.pp[breeder_no], ID_PARA_type1, NULL);
			type2 = PokeParaGet(consys->c_game.pp[breeder_no], ID_PARA_type2, NULL);
			if(type1 == GHOST_TYPE || type2 == GHOST_TYPE){
				wazapara->counter = 1;
			}
			else{
				wazapara->counter = 0;
			}
		}
		break;
	case WAZANO_OUMUGAESI:
		wazapara->wazano = WAZANO_HATAKU;
		break;
	case WAZANO_SIZENNOTIKARA:
		wazapara->wazano = WAZANO_TORAIATAKKU;
		break;
	case WAZANO_KAWARAWARI:
		wazapara->counter = 1;
		break;
	case WAZANO_SYADOODAIBU:
		wazapara->loop = 1;
		wazapara->waza_kouka = WAZAKOUKA_KIE;
		break;
	}
}

//--------------------------------------------------------------
/**
 * @brief   指定技を今のターン選択出来るかチェック(連続使用の確認)
 *
 * @param   a_game			演技力部門ゲームワークへのポインタ
 * @param   breeder_no		ブリーダー番号
 * @param   wazano			チェックする技番号
 *
 * @retval  TRUE:技は出せる
 * @retval  FALSE:出せない
 */
//--------------------------------------------------------------
int AT_WazaConsecutiveCheck(ACTIN_GAME_PARAM *a_game, int breeder_no, int wazano)
{
	if(wazano == 0){
		return FALSE;
	}
	
	if((wazano == a_game->waza_history[breeder_no])
			&& (a_game->wazapara.save[breeder_no].waza_repeat != wazano)){
		return FALSE;
	}
	return TRUE;
}

