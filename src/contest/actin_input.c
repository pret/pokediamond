//==============================================================================
/**
 * @file	actin_input.c
 * @brief	演技力部門入力画面処理
 * @author	matsuda
 * @date	2005.12.02(金)
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
#include "actin_input.h"
#include "battle/wazatype_panel.h"
#include "gflib/touchpanel.h"
#include "contype_icon.h"
#include "poketool/waza_tool.h"
#include "aci_tool.h"

#include "system/msgdata_util.h"
#include "system/wordset.h"
#include "system/fontoam.h"
#include "msgdata/msg_cmsg_acting.h"

#include "contest/contest_cursor.h"



//==============================================================================
//	定数定義
//==============================================================================
//デバッグ用定義：１＝S_MSGを使用した正式な形。０＝S_MSG対応Expandが用意されるまでの暫定処理
#define S_MSG_DEBUG		(0)

//--------------------------------------------------------------
//	メッセージ関係
//--------------------------------------------------------------
///S_MSGで使用する番号：ポケモン選択(技範囲)の時のポケモン名
#define S_MSG_POKESELE_NAME		(0)

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///スクリーンバッファ番号
enum{
	SCRNBUF_BACKGROUND,
	SCRNBUF_TITLE,
	SCRNBUF_COMMAND_WAZA,
	SCRNBUF_COMMAND_JUDGE,
	SCRNBUF_COMMAND_BACKGROUND,
	
	SCRNBUF_MAX,
};

///スクリーンバッファに対応したスクリーンデータのID
///	※SCRNBUFと並びを同じにしておくこと！！
ALIGN4 static const u16 ScrnArcDataNo[] = {
	CON_SUB_BG_NSCR_BIN,
	CON_TIT_NSCR_BIN,
	CON_WAZA_BUT_NSCR_BIN,
	CON_SINSA_BUT_NSCR_BIN,
	CON_ENGI_SUB_BG_NSCR_BIN,
};


///パレットバッファ番号
enum{
	PALBUF_TITLE,
	PALBUF_COMMAND,
	
	PALBUF_MAX,
};

///パレットバッファに対応したスクリーンデータのID
///	※PALBUFと並びを同じにしておくこと！！
ALIGN4 static const u16 PaletteArcDataNo[] = {
	CONTEST_SUB_NCLR,
	CON_ENGI_BUT_NCLR,
};

//--------------------------------------------------------------
//	ローカルTCBプライオリティ
//--------------------------------------------------------------
#define VWAIT_TCBPRI_CGRTRANS			(10)
#define VWAIT_TCBPRI_FRAMEVISIBLE		(10)
#define VWAIT_TCBPRI_BACKSCRN_VISIBLE	(10)
#define VWAIT_TCBPRI_CGRPARAM_TRANS		(20)

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///連続技使用の為、選択出来なくなっている時のパネルフェードEVY
#define NOT_TOUCH_WAZA_EVY		(8)
///連続技使用の為、選択出来なくなっている時のパネルフェードカラー
#define NOT_TOUCH_WAZA_COLOR	(0x6f39)
///連続技使用の為、選択出来なくなっている技が1つもない場合の初期化パラメータ
#define NOT_TOUCH_WAZA_POS_NULL	(0xff)

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///BG指定なし
#define NONE_ID			(0xffff)

///BG使用面数
#define ACI_BG_NUM		(4)

///標準パレットデータ使用本数
#define BASE_PLTT_NUM	(16)

///makedata_no初期値(未使用状態)
#define MAKEDATA_NO_INIT	(-1)

///コンテスト入力画面で使用出来るBGのCGRサイズ
#define ACI_BG_CGR_SIZE			(0x6000)

///BGスクリーンのクリアコード
#define BG_CLEAR_CODE			(0)

///半透明第1対象面
#define BLD_PLANE_1		(GX_BLEND_PLANEMASK_BG0)
///半透明第2対象面
#define BLD_PLANE_2		(GX_BLEND_BGALL)
///第1対象面に対するαブレンディング係数
#define BLD_ALPHA_1		(9)
///第2対象面に対するαブレンディング係数
#define BLD_ALPHA_2		(8)

///コンテストランク、タイプを表示するプレート部分のパレット番号
#define PLATE_PALNO		(2)

///選択出来ないパネルの絵のパレット番号
#define ACI_NOT_SELECT_PANEL_PALNO		(0x8)

///コマンド選択画面のバックグラウンドのパレット番号
#define COMMAND_BACKGROUND_PALNO		(0xe)

//--------------------------------------------------------------
//	スクリーンスクロール値
//--------------------------------------------------------------
///TYPE_AのBG表示時にタッチパネルが押された時にY方向にスクロールさせる値(エフェクト面)
#define SCRN_SCROLL_A_EFF_Y				(-2)
///TYPE_AのBG表示時にタッチパネルが押された時にY方向にスクロールさせる値(エフェクト面)
#define SCRN_SCROLL_BACK_A_EFF_Y		(1)

//--------------------------------------------------------------
//	タッチフェード
//--------------------------------------------------------------
///タッチした時のボタンフェードEVY
#define TOUCH_FADE_EVY		(10 << 8)
///タッチした時のボタンフェードEVY加算値
#define TOUCH_FADE_ADD_EVY	(TOUCH_FADE_EVY / 2)

//--------------------------------------------------------------
//	カーソル
//--------------------------------------------------------------
///カーソルのアクターソフトプライオリティ
#define SOFTPRI_CURSOR				(5)
///カーソルのBGプライオリティ
#define BGPRI_CURSOR				(0)

//--------------------------------------------------------------
//	フォントOBJ
//--------------------------------------------------------------
///フォントOBJの文字間隔X
#define PANEL_MSG_MARGIN		(0)
///フォントOBJの最大使用OAM数
#define PANEL_MSG_MAXOAM		(8)
///フォントOBJのアクターソフトプライオリティ
#define PANEL_MSG_SOFTPRI		(100)
///フォントOBJのBGプライオリティ
#define PANEL_MSG_BGPRI			(0)

enum{
	FONTOAM_LEFT,		///<X左端座標
	FONTOAM_CENTER,		///<X中心座標
};

///フォントOBJアクターワークで使用する添え字の位置
enum{
	//WALL
	FA_NO_CONRANK = 0,				///<コンテストランク
	FA_NO_CONTYPE,				///<コンテストタイプ
	
	//WAZA
	FA_NO_WAZA_1 = 0,			///<手持ち技1
	FA_NO_WAZA_2,				///<手持ち技2
	FA_NO_WAZA_3,				///<手持ち技3
	FA_NO_WAZA_4,				///<手持ち技4
	FA_NO_SETUMEI_1_U,			///<技1の説明上段
	FA_NO_SETUMEI_2_U,			///<技1の説明上段
	FA_NO_SETUMEI_3_U,			///<技1の説明上段
	FA_NO_SETUMEI_4_U,			///<技1の説明上段
	FA_NO_SETUMEI_1_D,			///<技2の説明下段
	FA_NO_SETUMEI_2_D,			///<技2の説明下段
	FA_NO_SETUMEI_3_D,			///<技2の説明下段
	FA_NO_SETUMEI_4_D,			///<技2の説明下段
	
	//JUDGE
	FA_NO_JUDGE_1 = 0,
	FA_NO_JUDGE_2,
	FA_NO_JUDGE_3,
	FA_NO_JUDGE_MODORU,
	
	FA_NO_MAX = FA_NO_SETUMEI_4_D + 1,		///<フォントOBJを一度に出せる最大数
};

///技名フォントOBJの表示座標
ALIGN4 static const u16 FontWazaPos[][2] = {	//0:X, 1:Y
	{2 * 8 + 3, 4 * 8},		//Xは左端座標
	{0x12 * 8 + 3, 4 * 8},
	{2 * 8 + 3, 0x10 * 8},
	{0x12 * 8 + 3, 0x10 * 8},
};

///技説明文フォントOBJの表示座標
ALIGN4 static const u16 FontSetumeiPos[][2][2] = {	//[no][UP,DOWN][X,Y]
	{
		{2 * 8 + 3, 8 * 8},		//Xは左端座標
		{2 * 8 + 3, 10 * 8},		//Xは左端座標
	},
	{
		{0x12 * 8 + 3, 8 * 8},
		{0x12 * 8 + 3, 10 * 8},
	},
	{
		{2 * 8 + 3, 0x14 * 8},
		{2 * 8 + 3, 0x16 * 8},
	},
	{
		{0x12 * 8 + 3, 0x14 * 8},
		{0x12 * 8 + 3, 0x16 * 8},
	},
};

///審判名フォントOBJの表示座標
ALIGN4 static const u16 FontJudgePos[][2] = {	//X,Y
	{5 * 8, 9 * 8},		//Xはセンター座標
	{16 * 8, 9 * 8},
	{0x1b * 8, 9 * 8},
};

///審判選択画面：「もどる」のフォントOBJ表示座標X(センター座標)
#define FONT_JUDGE_MODORU_X		(128)
///審判選択画面：「もどる」のフォントOBJ表示座標Y
#define FONT_JUDGE_MODORU_Y		(0x14 * 8 + 4)

///コンテストランクフォントOBJの表示座標X
#define FONT_CONRANK_POS_X		(128)
///コンテストランクフォントOBJの表示座標Y
#define FONT_CONRANK_POS_Y		(8*0x10-1)
///コンテストタイプフォントOBJの表示座標X
#define FONT_CONTYPE_POS_X		(128)
///コンテストタイプフォントOBJの表示座標Y
#define FONT_CONTYPE_POS_Y		(8*0x14-1)

//--------------------------------------------------------------
//	パレット関連定義
//--------------------------------------------------------------
///フォントOBJのパレット番号オフセット
enum{
	PALOFS_CONRANK = 0,
	PALOFS_WAZA = 0,
	PALOFS_SETUMEI = 0,
	PALOFS_JUDGE = 0,
};

#define MSGCOLOR_CONRANK		(GF_PRINTCOLOR_MAKE(1, 2, 0))	//FONT_SYSTEMなので背景抜き色指定
#define MSGCOLOR_WAZA			(GF_PRINTCOLOR_MAKE(1, 7, 8))
#define MSGCOLOR_SETUMEI		(GF_PRINTCOLOR_MAKE(1, 2, 0))	//FONT_SYSTEMなので背景抜き色指定
#define MSGCOLOR_JUDGE			(GF_PRINTCOLOR_MAKE(1, 9, 0xa))

//--------------------------------------------------------------
//	エフェクトTCB
//--------------------------------------------------------------
///パネルをタッチした後、エフェクトで待つフレーム数
#define SCRN_TOUCH_WAIT			(0)
///パネルをタッチした後、エフェクトで待つフレーム数
#define SCRN_TOUCH_ANM_WAIT		(0)

//--------------------------------------------------------------
//	技タイプ
//--------------------------------------------------------------
///技タイプのパレット開始位置
#define WAZATYPE_START_PALPOS	(4)

//--------------------------------------------------------------
//	AP値
//--------------------------------------------------------------
///AP値ハートの表示座標
ALIGN4 static const AppHeartPos[][2] = {	//X, Y
	{7*8 + 4 + 3, 6*8 + 4},
	{0x17*8 + 4 + 3, 6*8 + 4},
	{7*8 + 4 + 3, 0x12*8 + 4},
	{0x17*8 + 4 + 3, 0x12*8 + 4},
};
///AP値ハートの隣のハート間のスペース
#define APP_HEART_SPACE_X		(8)


//==============================================================================
//	構造体定義
//==============================================================================
///演技力入力画面カーソル位置記憶
typedef struct{
	s8 waza_x;
	s8 waza_y;
	s8 judge_x;
	s8 judge_y;
}ACI_CURSOR_SAVE;

///カーソル移動用ワーク
typedef struct{
	u8 cursor_on;			///<TRUE：カーソル表示状態
	s8 y_menu;				///<階層メニューの位置(Y)
	s8 x_menu;				///<水平メニューの位置(X)
	
	u8 dummy;
}CURSOR_MOVE;

///スクリーン書き換え時の範囲指定構造体
typedef struct{
	s32 top;
	s32 bottom;
	s32 left;
	s32 right;
}REWRITE_SCRN_RECT;

///CGR転送アニメ実行時の範囲データ
typedef struct{
	u16 dest_x;			///<転送先X開始位置(キャラ単位)
	u16 dest_y;			///<転送先Y開始位置(キャラ単位)
	u16 src_x;			///<転送元X開始位置(キャラ単位)
	u16 src_y;			///<転送元Y開始位置(キャラ単位)
	u16 size_x;			///<X転送サイズ(キャラ単位)
	u16 size_y;			///<Y転送サイズ(キャラ単位)
}CGR_TRANS_RECTDATA;

///CGR転送アニメ実行時のパラメータ
typedef struct{
	TCB_PTR v_tcb;		///<Vブランク転送を実行するTCBのポインタ
	u8 *dest_vram;		///<VRAM転送先アドレス
	void *arc_data;		///<アーカイブしたキャラファイルのポインタ
	u8 *raw_data;		///<アーカイブしたキャラファイルのキャラデータ先頭アドレス
	CGR_TRANS_RECTDATA rd;	///<CGR転送アニメ実行時の範囲データ
	u16 x_len;			///<キャラファイルのX幅(バイト単位)
}CGR_TRANS_PARAM;

///paracgr構造体で使用するアクターポインタの数
#define PARACGR_CAP_MAX			(3)
///ボタンのアニメパターン数
#define BUTTON_ANM_NUM			(2)

///エフェクトTCB用のワーク
typedef struct{
	s16 seq;
	s16 wait;
	union{
		struct{		//CGR転送用(汎用)
			CATS_ACT_PTR cap[PARACGR_CAP_MAX];	///<一緒にスクロールさせるアクターへのポインタ

//			CGR_TRANS_PARAM *ctp;
//			const CGR_TRANS_RECTDATA *ctp_rd_ptr[BUTTON_ANM_NUM];
//			u32 transcgr_id[BUTTON_ANM_NUM];
			const s16 *scrn_offset;
			const REWRITE_SCRN_RECT *scrn_range;
			int tp_ret;
			u8 scrnbuf_no;

			u8 fa_no;						///<対象フォントOBJアクターワークの添え字
		}paracgr;
	};
}ACI_EFFECT_WORK;

///カラーエフェクトTCB用のワーク
typedef struct{
	int tp_ret;
	s16 evy;		///<EVY値(下位8ビット小数)
	s16 evy_add;	///<EVY加減算値(下位8ビット小数)
	u8 seq;
	u8 pal_pos;	///<フェード対象のパレット番号
}ACI_COLOR_EFF_WORK;

///エフェクトBG書き換えパラメータ
typedef struct{
	const REWRITE_SCRN_RECT *rsr;	///<スクリーン書き換え範囲データへのポインタ
	u8 rsr_num;						///<rsrデータ個数
	s8 add_charname;				///<キャラクタネームに足しこむオフセット値
}EFFBG_WRITE_PARAM;

///フォントアクターワーク
typedef struct{
	FONTOAM_OBJ_PTR fontoam;
	CHAR_MANAGER_ALLOCDATA cma;
	u16 font_len;
}FONT_ACTOR;

///フォントOAM作成時、外側でBMP指定する場合に使用
typedef struct{
	GF_BGL_BMPWIN bmpwin;
	u16 char_len;
	u16 font_len;
}FONT_EX_BMPWIN;

///描画処理高速化の為、あらかじめデータを作成しておく為のワーク
typedef struct{
	//フォントOAMに関連付けるBMPWIN
	FONT_EX_BMPWIN exbmp_waza[WAZA_TEMOTI_MAX];
	FONT_EX_BMPWIN exbmp_explain_u[WAZA_TEMOTI_MAX];
	FONT_EX_BMPWIN exbmp_explain_d[WAZA_TEMOTI_MAX];

	FONT_EX_BMPWIN exbmp_judge[JUDGE_MAX];
	
	u8 ap_no[WAZA_TEMOTI_MAX];
	u8 con_type[WAZA_TEMOTI_MAX];
}MEMORY_DECORD_WORK;

///コンテスト入力画面制御ワーク
typedef struct _ACI_PARAM{
	CONTEST_SYSTEM *consys;
	ACTIN_SYSTEM_PARAM *sys;
	ACTIN_GAME_PARAM *a_game;
	void *scene_work;	///<シーン毎に異なる必要となるデータ類へのポインタ
	TCB_PTR effect_tcb;	///<エフェクト動作TCBへのポインタ
	TCB_PTR color_eff_tcb;	///<カラーエフェクト動作TCBへのポインタ
	EFFBG_WRITE_PARAM ewp;	///<エフェクトBG書き換えパラメータ

	//スクリーンバッファ
	u16 *scrn_buf[SCRNBUF_MAX];	///<スクリーンバッファ
	//パレットバッファ
	u16 *pal_buf[PALBUF_MAX];				///<パレットバッファ

	//フォントOAM
	FONTOAM_SYS_PTR fontoam_sys;	///<フォントシステムへのポインタ
	FONT_ACTOR font_actor[FA_NO_MAX];	///<フォントアクターワーク
	
	//コンテストタイプアイコン
	CATS_ACT_PTR icon_cap[WAZA_TEMOTI_MAX];		///<コンテストタイプアイコンアクターポインタ
	//凄い審判ハート
	CATS_ACT_PTR special_heart_cap;			///<凄い審判ハートのアクターポインタ
	//AP値・妨害値ハート
	CATS_ACT_PTR app_heart_cap[WAZA_TEMOTI_MAX][APP_HEART_MAX];	///<AP値ハートのアクターポインタ
	
	MEMORY_DECORD_WORK memory_decord;
	void *cgr_arc_data;
	NNSG2dCharacterData *cgr_char_data;
	
	s8 makedata_no;		///<現在使用しているBgMakeDataの番号
	u8 not_touch_pos;	///<連続使用不可技の手持ち位置(不可技がない場合はNOT_TOUCH_WAZA_POS_NULL)
	
	ACI_EFFECT_WORK effect_work;	///<エフェクトTCB用ワーク
	ACI_COLOR_EFF_WORK color_work;	///<カラーエフェクトTCB用ワーク

	ACI_CURSOR_SAVE cursor_save;	///<カーソルセーブ用ワーク
	CCURSOR_PTR cursor;			///<カーソルワークへのポインタ
	CURSOR_MOVE cursor_move;	///<カーソル移動用ワーク
	u8 decend_key;				///<TRUE:決定ボタンを押したのがカーソル
}ACI_PARAM;

///BG作成データ構造体
typedef struct{
	u16 cgr_id;			///<使用CGRのアーカイブID
	u16 pal_id;			///<使用パレットのアーカイブID
	union{
		struct{
			u16 scr0_id;
			u16 scr1_id;
			u16 scr2_id;
			u16 scr3_id;
		};
		u16 scr_id[ACI_BG_NUM];		///<使用スクリーンのアーカイブID
	};
	union{
		struct{
			u16 pri0;		///<BG0面のプライオリティ
			u16 pri1;		///<BG1面のプライオリティ
			u16 pri2;
			u16 pri3;
		};
		u16 pri[ACI_BG_NUM];		///<BGのプライオリティ
	};
	
	//タッチパネル
	const RECT_HIT_TBL *tpd;	///<使用するタッチパネルデータへのポインタ
	const int *tpd_ret;			///<タッチパネルの結果
	const u8 *tpd_pal;			///<タッチした部分のパネルのパレット番号データへのポインタ

	//カーソル移動
	int (*cursor_move_func)(ACI_PARAM_PTR, int);	///<キー入力をした時のコールバック関数
	void (*cursor_save_func)(ACI_PARAM_PTR, int);	///<キー位置記憶のコールバック関数
	
	//関数ポインタ
	void (*callback_bg)(ACI_PARAM_PTR, int, int);	///<BGCreate時に呼び出す関数
	int (*callback_tp)(ACI_PARAM_PTR, int, int);	///<タッチパネル反応時に呼び出す関数
}BG_MAKE_DATA;


//==============================================================================
//	プロトタイプ宣言
//==============================================================================
static void * AINPUT_WorkInit(void);
static void BGCallback_Wall(ACI_PARAM_PTR aci, int select_bg, int force_put);
static void BGCallback_WazaSelect(ACI_PARAM_PTR aci, int select_bg, int force_put);
static void BGCallback_JudgeSelect(ACI_PARAM_PTR aci, int select_bg, int force_put);
static int TPCallback_WazaSelect(ACI_PARAM_PTR aci, int tp_ret, int panel_pal);
static int TPCallback_JudgeSelect(ACI_PARAM_PTR aci, int tp_ret, int panel_pal);
static void Sub_SubHeartJudgeDeleteAll(ACI_PARAM_PTR aci);
static void Sub_AppHeartDeleteAll(ACI_PARAM_PTR aci);
static void Sub_SceneOBJDelete(ACI_PARAM_PTR aci);
static void Sub_ConTypeIconCreateAll(ACI_PARAM_PTR aci, u16 wazano[]);
static void Sub_ConTypeIconDeleteAll(ACI_PARAM_PTR aci);
static void Sub_WazaTypeCGRTrans(ACI_PARAM_PTR aci, int waza_type, int waza_pos);
static void Sub_BackScrnOnlyVisible(void);
static void Sub_TouchEndDelete(ACI_PARAM_PTR aci);
static void EffectTCB_Add(TCB_FUNC func, ACI_PARAM_PTR aci);
static void EffectTCB_Delete(ACI_PARAM_PTR aci);
static void Effect_ButtonDown(TCB_PTR tcb, void *work);
static void Effect_WazaButtonDown(TCB_PTR tcb, void *work);
static void VWait_CgrTrans(TCB_PTR tcb, void *work);
static void VWait_FrameVisibleUpdate(TCB_PTR tcb, void *work);
static void VWait_BackScrnOnlyVisible(TCB_PTR tcb, void *work);
static void Sub_ScrnErase(const REWRITE_SCRN_RECT rsr[], int rsr_num, GF_BGL_INI *bgl, 
	int frame_no, u16 clear_code);
static void Sub_FontOamCreate(ACI_PARAM_PTR aci, FONT_ACTOR *font_actor, const STRBUF *str, 
	FONT_TYPE font_type, GF_PRINTCOLOR color, int pal_offset, int pal_id, 
	int x, int y, int pos_center, FONT_EX_BMPWIN *ex_bmpwin);
static void Sub_FontOamDeleteAll(ACI_PARAM_PTR aci);
void AINPUT_DefaultFrameSet(GF_BGL_INI *bgl);
void AINPUT_FrameExit(GF_BGL_INI *bgl);
void *AINPUT_SystemInit(CONTEST_SYSTEM *consys, ACTIN_SYSTEM_PARAM *sys, ACTIN_GAME_PARAM *a_game);
void AINPUT_SystemFree(ACI_PARAM_PTR aci);
void AINPUT_CreateBG(ACI_PARAM_PTR aci, int select_bg, int force_put, void *scene_work);
int AINPUT_TouchCheck(ACI_PARAM_PTR aci);
BOOL AINPUT_EffectEndCheck(ACI_PARAM_PTR aci);
static void MemoryDecordWorkFree(ACI_PARAM_PTR aci);
static void FontExBmpwin_FontSet(ACI_PARAM_PTR aci, const STRBUF *str, FONT_TYPE font_type,
	FONT_EX_BMPWIN *ex_bmp, GF_PRINTCOLOR color);
static void FontLenGet(const STRBUF *str, FONT_TYPE font_type, int *ret_dot_len, 
	int *ret_char_len);
static void ColorEff_PointFade(TCB_PTR tcb, void *work);
static void ColorEffTCB_PointFadeSet(ACI_PARAM_PTR aci, int pal_pos);
static int CursorCheck(ACI_PARAM_PTR aci);
static int CursorMove_WazaSelect(ACI_PARAM_PTR aci, int init_flag);
static void CursorSave_WazaSelect(ACI_PARAM_PTR aci, int index);
static int CursorMove_JudgeSelect(ACI_PARAM_PTR aci, int init_flag);
static void CursorSave_JudgeSelect(ACI_PARAM_PTR aci, int index);
static u32 CursorMove_KeyCheckMove(CURSOR_MOVE *move, int x_menu_num, int y_menu_num, 
	const u8 *move_data);

//==============================================================================
//	外部データ
//==============================================================================
#include "con_engi_type_ncl_txt.dat"

//==============================================================================
//	データ
//==============================================================================
///コンテスト入力画面用のBGフレーム構成
static const GF_BGL_BGCNT_HEADER AciBgCntDat[] = {
	{//GF_BGL_FRAME0_S
		0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
		GX_BG_SCRBASE_0x6000, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
		0, 0, 0, FALSE
	},
	{//GF_BGL_FRAME1_S
		0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
		GX_BG_SCRBASE_0x6800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
		0, 0, 0, FALSE
	},
	{//GF_BGL_FRAME2_S
		0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
		GX_BG_SCRBASE_0x7000, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
		0, 0, 0, FALSE
	},
	{//GF_BGL_FRAME3_S
		0, 0, 0x800, 0, GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
		GX_BG_SCRBASE_0x7800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01,
		0, 0, 0, FALSE
	},
};

//============================================================================================
//	タッチパネル領域設定
//============================================================================================
//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///技選択タッチパネル領域設定
static const RECT_HIT_TBL WazaSelectTouchData[] = {
	//UP DOWN LEFT RIGHT
	{1*8, 12*8, 1*8, 0xf*8},		//技１
	{1*8, 12*8, 0x11*8, 0x1f*8},	//技２
	{13*8, 0x18*8, 1*8, 0xf*8},		//技３
	{13*8, 0x18*8, 0x11*8, 0x1f*8},	//技４
	{ RECT_HIT_END, 0, 0, 0 }
};
///技選択タッチパネルのタッチ結果返事
static const int WazaSelectTouchRet[NELEMS(WazaSelectTouchData) - 1] = {
	ACTIN_TP_WAZA_1,			//技1
	ACTIN_TP_WAZA_2,			//技2
	ACTIN_TP_WAZA_3,			//技3
	ACTIN_TP_WAZA_4,			//技4
};
///コマンド選択タッチパネルの各パネルのパレット番号
ALIGN4 static const u8 WazaSelectPaletteNo[NELEMS(WazaSelectTouchData) - 1] = {
	WAZATYPE_START_PALPOS + 0,		//技1
	WAZATYPE_START_PALPOS + 1,		//技2
	WAZATYPE_START_PALPOS + 2,		//技3
	WAZATYPE_START_PALPOS + 3,		//技4
};

///カーソル移動：技選択の水平メニューの最大数
#define CURSOR_WAZA_SELECT_X_MENU_NUM		(2)
///カーソル移動：技選択のメニューの階層の数
#define CURSOR_WAZA_SELECT_Y_MENU_NUM		(2)
///技選択のタッチパネルINDEX(WazaSelectTouchRetの順番)
enum{
	WAZASELE_INDEX_SKILL_1,
	WAZASELE_INDEX_SKILL_2,
	WAZASELE_INDEX_SKILL_3,
	WAZASELE_INDEX_SKILL_4,
};
///カーソル移動：技選択の移動範囲データ
ALIGN4 static const u8 CursorMoveDataWazaSelect[CURSOR_WAZA_SELECT_Y_MENU_NUM][CURSOR_WAZA_SELECT_X_MENU_NUM] = {
	{WAZASELE_INDEX_SKILL_1, WAZASELE_INDEX_SKILL_2},		//技１、技２
	{WAZASELE_INDEX_SKILL_3, WAZASELE_INDEX_SKILL_4},		//技３、技４
};

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///審判選択タッチパネル領域設定
static const RECT_HIT_TBL JudgeSelectTouchData[] = {
	//UP DOWN LEFT RIGHT
	{1*8, 0x10*8, 0*8, 10*8},		//審判１
	{1*8, 0x10*8, 11*8, 0x15*8},		//審判２
	{1*8, 0x10*8, 0x16*8, 255},		//審判３
	{0x11*8, 0x18*8, 0, 255},			//もどる
	{ RECT_HIT_END, 0, 0, 0 }
};
///審判選択タッチパネルのタッチ結果返事
static const int JudgeSelectTouchRet[NELEMS(JudgeSelectTouchData) - 1] = {
	ACTIN_TP_JUDGE_1,		//審判１
	ACTIN_TP_JUDGE_2,		//審判２
	ACTIN_TP_JUDGE_3,		//審判３
	ACTIN_TP_JUDGE_MODORU,	//もどる
};
///コマンド選択タッチパネルの各パネルのパレット番号
ALIGN4 static const u8 JudgeSelectPaletteNo[NELEMS(JudgeSelectTouchData) - 1] = {
	0,		//審判1
	1,		//審判2
	2,		//審判3
	3,		//もどる
};

///カーソル移動：技選択の水平メニューの最大数
#define CURSOR_JUDGE_SELECT_X_MENU_NUM		(3)
///カーソル移動：技選択のメニューの階層の数
#define CURSOR_JUDGE_SELECT_Y_MENU_NUM		(2)
///技選択のタッチパネルINDEX(JudgeSelectTouchRetの順番)
enum{
	JUDGESELE_INDEX_1,
	JUDGESELE_INDEX_2,
	JUDGESELE_INDEX_3,
	JUDGESELE_INDEX_CANCEL,
};
///カーソル移動：技選択の移動範囲データ
ALIGN4 static const u8 CursorMoveDataJudgeSelect[CURSOR_JUDGE_SELECT_Y_MENU_NUM][CURSOR_JUDGE_SELECT_X_MENU_NUM] = {
	{JUDGESELE_INDEX_1, JUDGESELE_INDEX_2, JUDGESELE_INDEX_3},		//審判１，２，３
	{JUDGESELE_INDEX_CANCEL, JUDGESELE_INDEX_CANCEL, JUDGESELE_INDEX_CANCEL},		//キャンセル
};


//==============================================================================
//	
//==============================================================================
///BG作成データ(※ここの並びを追加、変更したらAINPUT_TYPE_???の定義も変更すること！！)
static const BG_MAKE_DATA BgMakeData[] = {
	{//WALL
		CON_SUB_NCGR_BIN,
		PALBUF_TITLE,
		{
			SCRNBUF_TITLE,		//パネル
			NONE_ID,		//黒枠
			SCRNBUF_BACKGROUND,		//背景
			NONE_ID,							//黒枠スライド用
		},
		{2, 1, 3, 0},
		NULL,				//タッチパネルデータ
		NULL,				//タッチパネル結果
		NULL,				//タッチパレット番号
		NULL,				//キー入力をした時のコールバック関数
		NULL,			///<キー位置記憶のコールバック関数
		BGCallback_Wall,				//BG作成時のコールバック関数
		NULL,				//タッチパネル反応時のコールバック関数
	},
	{//HEART_WALL
		CON_BUT_NCGR_BIN,
		PALBUF_COMMAND,
		{
			NONE_ID,		//パネル
			NONE_ID,		//黒枠
			SCRNBUF_COMMAND_BACKGROUND,		//背景
			NONE_ID,							//黒枠スライド用
		},
		{2, 1, 3, 0},
		NULL,				//タッチパネルデータ
		NULL,				//タッチパネル結果
		NULL,				//タッチパレット番号
		NULL,				//キー入力をした時のコールバック関数
		NULL,			///<キー位置記憶のコールバック関数
		NULL,				//BG作成時のコールバック関数
		NULL,				//タッチパネル反応時のコールバック関数
	},
	{//WAZA
		CON_BUT_NCGR_BIN,
		PALBUF_COMMAND,
		{
			SCRNBUF_COMMAND_WAZA,		//パネル
			NONE_ID,		//黒枠
			SCRNBUF_COMMAND_BACKGROUND,		//背景
			NONE_ID,							//黒枠スライド用
		},
		{2, 1, 3, 0},
		WazaSelectTouchData,				//タッチパネルデータ
		WazaSelectTouchRet,					//タッチパネル結果
		WazaSelectPaletteNo,				//タッチパレット番号
		CursorMove_WazaSelect,				//キー入力をした時のコールバック関数
		CursorSave_WazaSelect,			///<キー位置記憶のコールバック関数
		BGCallback_WazaSelect,				//BG作成時のコールバック関数
		TPCallback_WazaSelect,				//タッチパネル反応時のコールバック関数
	},
	{//JUDGE
		CON_BUT_NCGR_BIN,
		PALBUF_COMMAND,
		{
			SCRNBUF_COMMAND_JUDGE,		//パネル
			NONE_ID,		//黒枠
			SCRNBUF_COMMAND_BACKGROUND,		//背景
			NONE_ID,							//黒枠スライド用
		},
		{2, 1, 3, 0},
		JudgeSelectTouchData,				//タッチパネルデータ
		JudgeSelectTouchRet,				//タッチパネル結果
		JudgeSelectPaletteNo,				//タッチパレット番号
		CursorMove_JudgeSelect,				//キー入力をした時のコールバック関数
		CursorSave_JudgeSelect,			///<キー位置記憶のコールバック関数
		BGCallback_JudgeSelect,				//BG作成時のコールバック関数
		TPCallback_JudgeSelect,				//タッチパネル反応時のコールバック関数
	},
};


//==============================================================================
//
//	アクターヘッダ
//
//==============================================================================
///コンテストタイプアイコン：アクターヘッダ
static const TCATS_OBJECT_ADD_PARAM_S ConTypeIconObjParam = {
	0, 0, 0,		//x, y, z
	0, 100, 0,		//アニメ番号、優先順位、パレット番号
	NNS_G2D_VRAM_TYPE_2DSUB,		//描画エリア
	{	//使用リソースIDテーブル
		CHARID_CONTYPE_ICON_1,	//キャラ
		PLTTID_OBJ_COMMON_SUB,	//パレット
		CELLID_CONTYPE_ICON,	//セル
		CELLANMID_CONTYPE_ICON,	//セルアニメ
		CLACT_U_HEADER_DATA_NONE,		//マルチセル
		CLACT_U_HEADER_DATA_NONE,		//マルチセルアニメ
	},
	1,			//BGプライオリティ
	0,			//Vram転送フラグ
};


//==============================================================================
//
//	技タイプ
//
//==============================================================================
///技の技タイプキャラ転送位置(キャラクタ単位)
ALIGN4 static const u16 WazaTypeCgrPos[] = {0+1, 6+1, 12+1, 18+1};

///コンテストタイプアイコンの座標
ALIGN4 static const u16 WazaIconPos[][2] = {	//X, Y
	{4*8 + 4 + 3, 6*8},
	{0x14*8 + 4 + 3, 6*8},
	{4*8 + 4 + 3, 0x12*8},
	{0x14*8 + 4 + 3, 0x12*8},
};

//==============================================================================
//
//	
//
//==============================================================================
///ボタンの押した時のアニメパターン数
#define BUTTON_ANM_MAX		(3)

//--------------------------------------------------------------
//	押せないパネル
//--------------------------------------------------------------
///スクリーン番号：押せないパネル　アニメ0、左上
#define SCRN_NO_NOT_TOUCH_0		(0x220)

//--------------------------------------------------------------
//	技選択
//--------------------------------------------------------------
///スクリーン番号：技選択「技0」アニメ0、左上
#define SCRN_NO_WAZA_SKILL_0_0		(0xc)
///スクリーン番号：技選択「技0」アニメ1、左上
#define SCRN_NO_WAZA_SKILL_0_1		(0xcc)
///スクリーン番号：技選択「技0」アニメ2、左上
#define SCRN_NO_WAZA_SKILL_0_2		(0x18c)

///スクリーン番号：技選択「技1」アニメ0、左上
#define SCRN_NO_WAZA_SKILL_1_0		(0xf)
///スクリーン番号：技選択「技1」アニメ1、左上
#define SCRN_NO_WAZA_SKILL_1_1		(0xcf)
///スクリーン番号：技選択「技1」アニメ2、左上
#define SCRN_NO_WAZA_SKILL_1_2		(0x18f)

///スクリーン番号：技選択「技2」アニメ0、左上
#define SCRN_NO_WAZA_SKILL_2_0		(0x12)
///スクリーン番号：技選択「技2」アニメ1、左上
#define SCRN_NO_WAZA_SKILL_2_1		(0xd2)
///スクリーン番号：技選択「技2」アニメ2、左上
#define SCRN_NO_WAZA_SKILL_2_2		(0x192)

///スクリーン番号：技選択「技3」アニメ0、左上
#define SCRN_NO_WAZA_SKILL_3_0		(0x15)
///スクリーン番号：技選択「技3」アニメ1、左上
#define SCRN_NO_WAZA_SKILL_3_1		(0xd5)
///スクリーン番号：技選択「技3」アニメ2、左上
#define SCRN_NO_WAZA_SKILL_3_2		(0x195)

///技選択パネルを押した時のボタンアニメ用スクリーンオフセット値
ALIGN4 static const s16 WazaButtonScrnOffset[][BUTTON_ANM_MAX] = {
	{//SELECT_SKILL_1
		SCRN_NO_WAZA_SKILL_0_0 - SCRN_NO_WAZA_SKILL_0_0,
		SCRN_NO_WAZA_SKILL_0_1 - SCRN_NO_WAZA_SKILL_0_0,
		SCRN_NO_WAZA_SKILL_0_2 - SCRN_NO_WAZA_SKILL_0_0,
	},
	{//SELECT_SKILL_2
		SCRN_NO_WAZA_SKILL_1_0 - SCRN_NO_WAZA_SKILL_1_0,
		SCRN_NO_WAZA_SKILL_1_1 - SCRN_NO_WAZA_SKILL_1_0,
		SCRN_NO_WAZA_SKILL_1_2 - SCRN_NO_WAZA_SKILL_1_0,
	},
	{//SELECT_SKILL_3
		SCRN_NO_WAZA_SKILL_2_0 - SCRN_NO_WAZA_SKILL_2_0,
		SCRN_NO_WAZA_SKILL_2_1 - SCRN_NO_WAZA_SKILL_2_0,
		SCRN_NO_WAZA_SKILL_2_2 - SCRN_NO_WAZA_SKILL_2_0,
	},
	{//SELECT_SKILL_4
		SCRN_NO_WAZA_SKILL_3_0 - SCRN_NO_WAZA_SKILL_3_0,
		SCRN_NO_WAZA_SKILL_3_1 - SCRN_NO_WAZA_SKILL_3_0,
		SCRN_NO_WAZA_SKILL_3_2 - SCRN_NO_WAZA_SKILL_3_0,
	},
};

///技選択パネルを押した時のスクリーンアニメ書き換え範囲
ALIGN4 static const REWRITE_SCRN_RECT WazaButtonScrnRect[] = {
	{0, 11, 1, 14},
	{0, 11, 0x11, 0x1e},
	{12, 0x17, 1, 14},
	{12, 0x17, 0x11, 0x1e},
};

///技選択パネルを押せないボタンにする時のスクリーンオフセット値
ALIGN4 static const s16 WazaButtonNotTouchScrnOffset[] = {
	SCRN_NO_NOT_TOUCH_0 - SCRN_NO_WAZA_SKILL_0_0,	//SELECT_SKILL_1
	SCRN_NO_NOT_TOUCH_0 - SCRN_NO_WAZA_SKILL_1_0,	//SELECT_SKILL_1
	SCRN_NO_NOT_TOUCH_0 - SCRN_NO_WAZA_SKILL_2_0,	//SELECT_SKILL_1
	SCRN_NO_NOT_TOUCH_0 - SCRN_NO_WAZA_SKILL_3_0,	//SELECT_SKILL_1
};

///技選択パネルを押せないボタンにする時のスクリーンアニメ書き換え範囲
ALIGN4 static const REWRITE_SCRN_RECT WazaButtonNotTouchScrnRect[] = {
	{1, 11, 1, 14},
	{1, 11, 0x11, 0x1e},
	{13, 0x17, 1, 14},
	{13, 0x17, 0x11, 0x1e},
};

//--------------------------------------------------------------
//	審判選択
//--------------------------------------------------------------
///スクリーン番号：審判選択「審判0」アニメ0、左上
#define SCRN_NO_JUDGE_0_0		(0x0)
///スクリーン番号：審判選択「審判0」アニメ1、左上
#define SCRN_NO_JUDGE_0_1		(0xc0)
///スクリーン番号：審判選択「審判0」アニメ2、左上
#define SCRN_NO_JUDGE_0_2		(0x180)

///スクリーン番号：審判選択「審判1」アニメ0、左上
#define SCRN_NO_JUDGE_1_0		(0x3)
///スクリーン番号：審判選択「審判1」アニメ1、左上
#define SCRN_NO_JUDGE_1_1		(0xc3)
///スクリーン番号：審判選択「審判1」アニメ2、左上
#define SCRN_NO_JUDGE_1_2		(0x183)

///スクリーン番号：審判選択「審判2」アニメ0、左上
#define SCRN_NO_JUDGE_2_0		(0x6)
///スクリーン番号：審判選択「審判2」アニメ1、左上
#define SCRN_NO_JUDGE_2_1		(0xc6)
///スクリーン番号：審判選択「審判2」アニメ2、左上
#define SCRN_NO_JUDGE_2_2		(0x186)

///スクリーン番号：審判選択「キャンセル」アニメ0、左上
#define SCRN_NO_JUDGE_CANCEL_0	(0x9)
///スクリーン番号：審判選択「キャンセル」アニメ1、左上
#define SCRN_NO_JUDGE_CANCEL_1	(0xc9)
///スクリーン番号：審判選択「キャンセル」アニメ2、左上
#define SCRN_NO_JUDGE_CANCEL_2	(0x189)

///審判選択パネルを押した時のボタンアニメ用スクリーンオフセット値
ALIGN4 static const s16 JudgeButtonScrnOffset[][BUTTON_ANM_MAX] = {
	{//JUDGE_1
		SCRN_NO_JUDGE_0_0 - SCRN_NO_JUDGE_0_0,
		SCRN_NO_JUDGE_0_1 - SCRN_NO_JUDGE_0_0,
		SCRN_NO_JUDGE_0_2 - SCRN_NO_JUDGE_0_0,
	},
	{//JUDGE_2
		SCRN_NO_JUDGE_1_0 - SCRN_NO_JUDGE_1_0,
		SCRN_NO_JUDGE_1_1 - SCRN_NO_JUDGE_1_0,
		SCRN_NO_JUDGE_1_2 - SCRN_NO_JUDGE_1_0,
	},
	{//JUDGE_3
		SCRN_NO_JUDGE_2_0 - SCRN_NO_JUDGE_2_0,
		SCRN_NO_JUDGE_2_1 - SCRN_NO_JUDGE_2_0,
		SCRN_NO_JUDGE_2_2 - SCRN_NO_JUDGE_2_0,
	},
	{//CANCEL
		SCRN_NO_JUDGE_CANCEL_0 - SCRN_NO_JUDGE_CANCEL_0,
		SCRN_NO_JUDGE_CANCEL_1 - SCRN_NO_JUDGE_CANCEL_0,
		SCRN_NO_JUDGE_CANCEL_2 - SCRN_NO_JUDGE_CANCEL_0,
	},
};

///審判選択パネルを押した時のスクリーンアニメ書き換え範囲
ALIGN4 static const REWRITE_SCRN_RECT JudgeButtonScrnRect[] = {
	{0, 0xf, 0, 9},
	{0, 0xf, 11, 0x14},
	{0, 0xf, 0x16, 0x1f},
	{0x10, 0x17, 0, 0x1f},
};



//==============================================================================
//
//	
//
//==============================================================================

//--------------------------------------------------------------
/**
 * @brief   BIシステムワークの確保と初期化
 *
 * @retval  確保したBIシステムワークのポインタ
 */
//--------------------------------------------------------------
static void * AINPUT_WorkInit(void)
{
	ACI_PARAM *aci;

	aci = sys_AllocMemory(HEAPID_ACTIN, sizeof(ACI_PARAM));
	MI_CpuClear8(aci, sizeof(ACI_PARAM));
	
	aci->makedata_no = MAKEDATA_NO_INIT;
	
	return aci;
}

//--------------------------------------------------------------
/**
 * @brief   BG構成を標準フレーム構成で設定する
 * @param   bgl		BGLデータ
 */
//--------------------------------------------------------------
void AINPUT_DefaultFrameSet(GF_BGL_INI *bgl)
{
	int i;
	
	for(i = 0; i < NELEMS(AciBgCntDat); i++){
		GF_BGL_BGControlSet(bgl, GF_BGL_FRAME0_S + i, &AciBgCntDat[i], GF_BGL_MODE_TEXT);
		GF_BGL_ScrClearCode(bgl, GF_BGL_FRAME0_S + i, BG_CLEAR_CODE);
		GF_BGL_ScrollSet(bgl, GF_BGL_FRAME0_S + i, GF_BGL_SCROLL_X_SET, 0);
		GF_BGL_ScrollSet(bgl, GF_BGL_FRAME0_S + i, GF_BGL_SCROLL_Y_SET, 0);
	}
}

//--------------------------------------------------------------
/**
 * @brief   BGフレーム終了処理
 * @param   bgl		BGLデータ
 */
//--------------------------------------------------------------
void AINPUT_FrameExit(GF_BGL_INI *bgl)
{
	int i;
	
	for(i = 0; i < NELEMS(AciBgCntDat); i++){
		GF_BGL_VisibleSet(GF_BGL_FRAME0_S + i, VISIBLE_OFF);
		GF_BGL_BGControlExit(bgl, GF_BGL_FRAME0_S + i);
	}
}

//--------------------------------------------------------------
/**
 * @brief   コンテスト入力画面のシステムを初期化
 * @param   bgl		BGLデータ
 * @retval  Allocしたコンテスト入力画面のシステムワークのポインタ
 */
//--------------------------------------------------------------
void * AINPUT_SystemInit(CONTEST_SYSTEM *consys, ACTIN_SYSTEM_PARAM *sys, ACTIN_GAME_PARAM *a_game)
{
	ACI_PARAM *aci;
	
	//ワーク確保
	aci = AINPUT_WorkInit();
	aci->consys = consys;
	aci->sys = sys;
	aci->a_game = a_game;
	
	//フレーム構成設定	ここでやるかは微妙？
//	AINPUT_DefaultFrameSet(bgl);

	//フォントOAMシステム作成
	aci->fontoam_sys = FONTOAM_SysInit(FA_NO_MAX, HEAPID_ACTIN);

	//スクリーン全読み込み
	{
		NNSG2dScreenData *scrnData;
		void *arc_data;
		int i;
		
		for(i = 0; i < SCRNBUF_MAX; i++){
			//スクリーンバッファ確保
			aci->scrn_buf[i] = sys_AllocMemory(HEAPID_ACTIN, 0x800);

			//スクリーン読み込み
			arc_data = ArcUtil_ScrnDataGet(ARC_CONTEST_BG, ScrnArcDataNo[i], 1, 
				&scrnData, HEAPID_ACTIN);
			MI_CpuCopy32(scrnData->rawData, aci->scrn_buf[i], 0x800);
			sys_FreeMemoryEz(arc_data);
		}
	}

	//パレット読み込み
	{
		u16 *def_wk;
		PALETTE_FADE_PTR pfd;
		int i;
		
		pfd = aci->sys->pfd;
		
		for(i = 0; i < PALBUF_MAX; i++){
			aci->pal_buf[i] = sys_AllocMemory(HEAPID_ACTIN, 0x200);
			PaletteWorkSet_Arc(pfd, ARC_CONTEST_BG, PaletteArcDataNo[i], HEAPID_ACTIN, 
				FADE_SUB_BG, 0, 0);
			def_wk = PaletteWorkDefaultWorkGet(pfd, FADE_SUB_BG);
			MI_CpuCopy16(def_wk, aci->pal_buf[i], 0x200);
		}
	}

	return aci;
}

//--------------------------------------------------------------
/**
 * @brief   コンテスト入力画面のシステムを解放する
 * @param   aci		BIシステムワークへのポインタ
 */
//--------------------------------------------------------------
void AINPUT_SystemFree(ACI_PARAM_PTR aci)
{
	int i;
	
	Sub_SceneOBJDelete(aci);
	FONTOAM_SysDelete(aci->fontoam_sys);

	//-- カーソル --//
	CCURSOR_ResourceFree(aci->sys->crp, CHARID_ACTIN_CURSOR, PLTTID_ACTIN_CURSOR,
		CELLID_ACTIN_CURSOR, CELLANMID_ACTIN_CURSOR);
	CCURSOR_ActorDelete(aci->cursor);

	for(i = 0; i < SCRNBUF_MAX; i++){
		sys_FreeMemoryEz(aci->scrn_buf[i]);
	}
	for(i = 0; i < PALBUF_MAX; i++){
		sys_FreeMemoryEz(aci->pal_buf[i]);
	}
	
	MemoryDecordWorkFree(aci);

	sys_FreeMemoryEz(aci);
}

//--------------------------------------------------------------
/**
 * @brief   指定タイプのBG画面を形成する
 *
 * @param   aci				BIシステムワークへのポインタ
 * @param   select_bg		表示BGタイプ(AINPUT_TYPE_???)
 * @param   force_put		TRUE:強制転送、FALSE:既に同じデータが転送されているなら再転送はしない
 * @param   work			シーン毎に異なる必要なデータへのポインタ
 */
//--------------------------------------------------------------
void AINPUT_CreateBG(ACI_PARAM_PTR aci, int select_bg, int force_put, void *scene_work)
{
	const BG_MAKE_DATA *bmd, *old_bmd;
	int i;
	GF_BGL_INI *bgl;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	
	aci->scene_work = scene_work;
	bgl = aci->sys->bgl;
	csp = aci->sys->csp;
	crp = aci->sys->crp;
	
	if(aci->makedata_no == MAKEDATA_NO_INIT){
		force_put = TRUE;
		old_bmd = NULL;
	}
	else{
		old_bmd = &BgMakeData[aci->makedata_no];
	}
	bmd = &BgMakeData[select_bg];

	//背景以外は全て非表示
//	Sub_BackScrnOnlyVisible();
	
	//各BG面のBGプライオリティ更新
	{
		for(i = 0; i < ACI_BG_NUM; i++){
			GF_BGL_PrioritySet(GF_BGL_FRAME0_S + i, bmd->pri[i]);
		}
	}
	
	//PALETTE
//	if(bmd->pal_id != NONE_ID && (force_put == TRUE || bmd->pal_id != old_bmd->pal_id)){
	if(1){
		PaletteWorkSet(aci->sys->pfd, aci->pal_buf[bmd->pal_id], FADE_SUB_BG, 0, 0x200);
	}
	//SCREEN
	for(i = 0; i < ACI_BG_NUM; i++){
		if(bmd->scr_id[i] != NONE_ID 
				&& (force_put == TRUE || bmd->scr_id[i] != old_bmd->scr_id[i])){
			GF_BGL_ScreenBufSet(bgl, GF_BGL_FRAME0_S + i, aci->scrn_buf[bmd->scr_id[i]], 0x800);
			GF_BGL_LoadScreenV_Req(bgl, GF_BGL_FRAME0_S + i);
		}
	}
	
	aci->makedata_no = select_bg;

//	G2S_SetBlendAlpha(BLD_PLANE_1, BLD_PLANE_2, BLD_ALPHA_1, BLD_ALPHA_2);

	Sub_SceneOBJDelete(aci);
	//コールバック関数呼び出し
	if(bmd->callback_bg != NULL){
		bmd->callback_bg(aci, select_bg, force_put);
	}

	//CGR	メモリをVblankで転送するまで確保したままなので、最後にする
//	if(1){	//CGR転送アニメを行うならキャラIDが同じでも必ず転送しておかないとアニメが戻らない
	if(bmd->cgr_id != NONE_ID && (force_put == TRUE || bmd->cgr_id != old_bmd->cgr_id)){
//		ArcUtil_BgCharSet(ARC_CONTEST_BG, bmd->cgr_id, bgl, GF_BGL_FRAME0_S, 
//			0, ACI_BG_CGR_SIZE, 1, HEAPID_ACTIN);
		aci->cgr_arc_data = ArcUtil_CharDataGet(ARC_CONTEST_BG, bmd->cgr_id, 1, 
			&aci->cgr_char_data, HEAPID_ACTIN);
		VWaitTCB_Add(VWait_CgrTrans, aci, VWAIT_TCBPRI_CGRTRANS);
	}

	VWaitTCB_Add(VWait_FrameVisibleUpdate, aci, VWAIT_TCBPRI_FRAMEVISIBLE);
}

//--------------------------------------------------------------
/**
 * @brief   タッチパネル状態を調べる
 * @param   aci		BIシステムワークへのポインタ
 * @retval  結果(当たりなしの場合はRECT_HIT_NONE)
 */
//--------------------------------------------------------------
int AINPUT_TouchCheck(ACI_PARAM_PTR aci)
{
	int tp_ret, hit, ret, panel_pal;
	const BG_MAKE_DATA *bmd;
	int cursor_check = 0;
	
	GF_ASSERT(aci->makedata_no != MAKEDATA_NO_INIT);
	
	bmd = &BgMakeData[aci->makedata_no];
	if(bmd->tpd == NULL){
		return RECT_HIT_NONE;
	}
	
	GF_ASSERT(bmd->tpd_ret != NULL);
	
	hit = GF_TP_RectHitTrg(bmd->tpd);
	if(hit == RECT_HIT_NONE){
		hit = CursorCheck(aci);
		cursor_check++;
	}
	
	if(hit == RECT_HIT_NONE){
		tp_ret = RECT_HIT_NONE;
		panel_pal = 0xff;
	}
	else{
		tp_ret = bmd->tpd_ret[hit];
		panel_pal = bmd->tpd_pal[hit];
	}
	
	//コールバック関数呼び出し
	if(bmd->callback_tp != NULL){
		tp_ret = bmd->callback_tp(aci, tp_ret, panel_pal);
		if(tp_ret != RECT_HIT_NONE){
			if(bmd->cursor_save_func != NULL){
				bmd->cursor_save_func(aci, hit);
			}
			MI_CpuClear8(&aci->cursor_move, sizeof(CURSOR_MOVE));
			CCURSOR_OFF(aci->cursor);
			if(cursor_check > 0){
				aci->decend_key = TRUE;
			}
			else{
				aci->decend_key = FALSE;
			}
		}
	}
	
	return tp_ret;
}

//--------------------------------------------------------------
/**
 * @brief   エフェクトTCBが終了しているかチェック
 * @param   aci		BIシステムワークへのポインタ
 * @retval  TRUE:終了している。　FALSE:終了していない
 */
//--------------------------------------------------------------
BOOL AINPUT_EffectEndCheck(ACI_PARAM_PTR aci)
{
	if(aci->effect_tcb == NULL && aci->color_eff_tcb == NULL){
		return TRUE;
	}
	return FALSE;
}



//==============================================================================
//
//	BG作成時に呼ばれるコールバック関数
//
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   AINPUT_TYPE_WALLのBGCreate時に呼ばれるコールバック関数
 *
 * @param   aci				BIシステムワークへのポインタ
 * @param   select_bg		表示BGタイプ(AINPUT_TYPE_???)
 * @param   force_put		TRUE:強制転送、FALSE:既に同じデータが転送されているなら再転送はしない
 */
//--------------------------------------------------------------
static void BGCallback_Wall(ACI_PARAM_PTR aci, int select_bg, int force_put)
{
	STRBUF *rank_src, *type_src;
	u32 rank_id, type_id;
	
	rank_id = ConTool_GetRankMsgID(aci->sys->c_game->rank, aci->sys->c_game->mode, 
		aci->consys->sio_flag);
	type_id = ConTool_GetTypeMsgID(aci->sys->c_game->type, aci->sys->c_game->mode);
	
	rank_src = MSGMAN_AllocString(aci->sys->actin_msg, rank_id);
	type_src = MSGMAN_AllocString(aci->sys->actin_msg, type_id);
	
	Sub_FontOamCreate(aci, &aci->font_actor[FA_NO_CONRANK], 
		rank_src, FONT_SYSTEM, 
		MSGCOLOR_CONRANK, PALOFS_CONRANK,
		PLTTID_SUB_FONTACT, FONT_CONRANK_POS_X, FONT_CONRANK_POS_Y, FONTOAM_CENTER, NULL);
	Sub_FontOamCreate(aci, &aci->font_actor[FA_NO_CONTYPE], 
		type_src, FONT_SYSTEM, 
		MSGCOLOR_CONRANK, PALOFS_CONRANK,
		PLTTID_SUB_FONTACT, FONT_CONTYPE_POS_X, FONT_CONTYPE_POS_Y, FONTOAM_CENTER, NULL);
	
	STRBUF_Delete(rank_src);
	STRBUF_Delete(type_src);
	
	PaletteWorkSetEx_Arc(aci->sys->pfd, ARC_CONTEST_BG, CONTEST_SUBTIT_NCLR, HEAPID_ACTIN, 
		FADE_SUB_BG, 0x20, PLATE_PALNO * 16, 16 * aci->sys->c_game->type);
}

//--------------------------------------------------------------
/**
 * @brief   AINPUT_TYPE_AのBGCreate時に呼ばれるコールバック関数
 *
 * @param   aci				BIシステムワークへのポインタ
 * @param   select_bg		表示BGタイプ(AINPUT_TYPE_???)
 * @param   force_put		TRUE:強制転送、FALSE:既に同じデータが転送されているなら再転送はしない
 */
//--------------------------------------------------------------
static void BGCallback_WazaSelect(ACI_PARAM_PTR aci, int select_bg, int force_put)
{
	u16 wazano[WAZA_TEMOTI_MAX], appeal_no[WAZA_TEMOTI_MAX];
	int i;
	STRBUF *waza_src;
	STRBUF *setumei_u_src, *setumei_d_src;
	u32 u_id, d_id;
	MEMORY_DECORD_WORK *mdw;

	mdw = &aci->memory_decord;
	aci->not_touch_pos = NOT_TOUCH_WAZA_POS_NULL;
	
	for(i = 0; i < WAZA_TEMOTI_MAX; i++){
		wazano[i] = PokeParaGet(aci->sys->c_game->pp[aci->sys->c_game->my_breeder_no], 
			ID_PARA_waza1 + i, NULL);
		if(wazano[i] != 0){
			appeal_no[i] = mdw->ap_no[i];
		}
		else{
			appeal_no[i] = 0;
		}
		
		//技名
		Sub_FontOamCreate(aci, &aci->font_actor[FA_NO_WAZA_1 + i], NULL, FONT_BUTTON, 
			MSGCOLOR_WAZA, PALOFS_WAZA,
			PLTTID_SUB_FONTACT, FontWazaPos[i][0], FontWazaPos[i][1], FONTOAM_LEFT, 
			&mdw->exbmp_waza[i]);
		
		//技説明：上段
		Sub_FontOamCreate(aci, &aci->font_actor[FA_NO_SETUMEI_1_U + i], 
			NULL, FONT_SYSTEM, MSGCOLOR_SETUMEI, PALOFS_SETUMEI,
			PLTTID_SUB_FONTACT, FontSetumeiPos[i][0][0], FontSetumeiPos[i][0][1], FONTOAM_LEFT,
			&mdw->exbmp_explain_u[i]);
		
		//技説明：下段
		Sub_FontOamCreate(aci, &aci->font_actor[FA_NO_SETUMEI_1_D + i], 
			NULL, FONT_SYSTEM, MSGCOLOR_SETUMEI, PALOFS_SETUMEI,
			PLTTID_SUB_FONTACT, FontSetumeiPos[i][1][0], FontSetumeiPos[i][1][1], FONTOAM_LEFT,
			&mdw->exbmp_explain_d[i]);
		
		//手持ち技がないなら、フォントOBJバニッシュ＆黒枠消す
		if(wazano[i] == 0){
			FONTOAM_SetDrawFlag(aci->font_actor[FA_NO_WAZA_1 + i].fontoam, FALSE);
			FONTOAM_SetDrawFlag(aci->font_actor[FA_NO_SETUMEI_1_U + i].fontoam, FALSE);
			FONTOAM_SetDrawFlag(aci->font_actor[FA_NO_SETUMEI_1_D + i].fontoam, FALSE);
		}
	}

	//-- 技タイプ毎のCGRを転送 --//
	{
		for(i = 0; i < WAZA_TEMOTI_MAX; i++){
			if(wazano[i] != 0){
				int con_type;
				con_type = mdw->con_type[i];
				Sub_WazaTypeCGRTrans(aci, con_type, i);
			}
			else{
				Sub_WazaTypeCGRTrans(aci, -1, i);
			}
		}
	}

	//-- 2度連続使用技チェック --//
	for(i = 0; i < WAZA_TEMOTI_MAX; i++){
		if(wazano[i] != 0 
				&& AT_WazaConsecutiveCheck(aci->a_game, aci->sys->c_game->my_breeder_no, 
				wazano[i]) == FALSE){
			//2度連続使用で連続許可技でもないのなら、暗くしてタッチ出来ないようにする
		//	SoftFadePfd(aci->sys->pfd, FADE_SUB_BG, (WAZATYPE_START_PALPOS + i) * 16, 16, 
		//		NOT_TOUCH_WAZA_EVY, NOT_TOUCH_WAZA_COLOR);
			PaletteWorkSet(aci->sys->pfd, 
				&aci->pal_buf[PALBUF_COMMAND][ACI_NOT_SELECT_PANEL_PALNO * 16], 
				FADE_SUB_BG, (WAZATYPE_START_PALPOS + i) * 16, 0x20);
			
			GF_ASSERT(aci->not_touch_pos == NOT_TOUCH_WAZA_POS_NULL && "2つ以上の技が連続使用不可状態になっています");
			aci->not_touch_pos = i;
		}
	}

	//コンテストタイプアイコン
	Sub_ConTypeIconCreateAll(aci, wazano);
	
	//AP値・妨害値
	{
		int ap_point;
		int heart_num, loop;
		
		//アクターセット
		for(i = 0; i < WAZA_TEMOTI_MAX; i++){
			if(wazano[i] == 0){
				continue;
			}
			ap_point = ConTool_GetAPWaza_App(appeal_no[i]);
			heart_num = MATH_IAbs(ap_point) / APP_APPEAL_ICON_ONE_POINT;
			GF_ASSERT(heart_num <= APP_HEART_MAX);
			for(loop = 0; loop < heart_num; loop++){
				GF_ASSERT(aci->app_heart_cap[i][loop] == NULL);
				aci->app_heart_cap[i][loop] = ACIT_AppHeartActorSet(
					aci->sys->csp, aci->sys->crp, 
					AppHeartPos[i][0] + APP_HEART_SPACE_X * loop, 
					AppHeartPos[i][1], ap_point);
			}
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   AINPUT_TYPE_BのBGCreate時に呼ばれるコールバック関数
 *
 * @param   aci				BIシステムワークへのポインタ
 * @param   select_bg		表示BGタイプ(AINPUT_TYPE_???)
 * @param   force_put		TRUE:強制転送、FALSE:既に同じデータが転送されているなら再転送はしない
 */
//--------------------------------------------------------------
static void BGCallback_JudgeSelect(ACI_PARAM_PTR aci, int select_bg, int force_put)
{
	int i;
	GF_BGL_INI *bgl;
	STRBUF *modoru_src;
	MEMORY_DECORD_WORK *mdw;

	mdw = &aci->memory_decord;
	bgl = aci->sys->bgl;

	for(i = 0; i < JUDGE_MAX; i++){
		Sub_FontOamCreate(aci, &aci->font_actor[FA_NO_JUDGE_1 + i], 
			NULL, FONT_BUTTON, MSGCOLOR_JUDGE, PALOFS_JUDGE,
			PLTTID_SUB_FONTACT, FontJudgePos[i][0], FontJudgePos[i][1], FONTOAM_CENTER, 
			&mdw->exbmp_judge[i]);
	}
	
	modoru_src = MSGMAN_AllocString(aci->sys->actin_msg, CAMSG_MODORU);
	Sub_FontOamCreate(aci, &aci->font_actor[FA_NO_JUDGE_1 + i], 
			modoru_src, FONT_BUTTON, 
			MSGCOLOR_JUDGE, PALOFS_JUDGE,
			PLTTID_SUB_FONTACT, FONT_JUDGE_MODORU_X, FONT_JUDGE_MODORU_Y, FONTOAM_CENTER, NULL);
	STRBUF_Delete(modoru_src);
	
	//凄い審判の印のハートアイコン
	aci->special_heart_cap = ACIT_SubHeartJudgeActorAdd(aci->sys->csp, 
		aci->sys->crp, aci->sys->c_game->special_judge_no);
}



//==============================================================================
//
//	タッチパネル反応時に呼ばれるコールバック関数
//
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   AINPUT_TYPE_Aでタッチパネル反応時に呼び出されるコールバック関数
 *
 * @param   aci			BIシステムワークへのポインタ
 * @param   tp_ret		タッチパネル結果(bmd->tpd_retの値かRECT_HIT_NONE)
 * @param   panel_pal	押したパネルのパレット番号
 * 
 * @retval  tp_retを返す(処理の中で変更する必要がないなら、引数で渡された値をそのまま返す)
 */
//--------------------------------------------------------------
static int TPCallback_WazaSelect(ACI_PARAM_PTR aci, int tp_ret, int panel_pal)
{
	u32 rd_no;
	int wazano;
	const s16 *scrn_offset;
	const REWRITE_SCRN_RECT *scrn_range;
	
	rd_no = tp_ret;
	switch(tp_ret){
	case RECT_HIT_NONE:
	default:
		return RECT_HIT_NONE;
	case ACTIN_TP_WAZA_1:
	case ACTIN_TP_WAZA_2:
	case ACTIN_TP_WAZA_3:
	case ACTIN_TP_WAZA_4:
		wazano = PokeParaGet(aci->sys->c_game->pp[aci->sys->c_game->my_breeder_no], 
			ID_PARA_waza1 + tp_ret, NULL);
		if(wazano == 0 || aci->not_touch_pos == (tp_ret - ACTIN_TP_WAZA_1)){
			return RECT_HIT_NONE;	//押された場所の手持ち技がない
		}
		scrn_offset = WazaButtonScrnOffset[rd_no];
		scrn_range = &WazaButtonScrnRect[rd_no];
		break;
	}
	
	ColorEffTCB_PointFadeSet(aci, panel_pal);
	
	EffectTCB_Add(Effect_WazaButtonDown, aci);
	aci->effect_work.paracgr.scrn_offset = scrn_offset;
	aci->effect_work.paracgr.scrn_range = scrn_range;
	aci->effect_work.paracgr.scrnbuf_no = SCRNBUF_COMMAND_WAZA;
	aci->effect_work.paracgr.tp_ret = tp_ret;
	return tp_ret;
}

//--------------------------------------------------------------
/**
 * @brief   AINPUT_TYPE_Bでタッチパネル反応時に呼び出されるコールバック関数
 *
 * @param   aci			BIシステムワークへのポインタ
 * @param   tp_ret		タッチパネル結果(bmd->tpd_retの値かRECT_HIT_NONE)
 * @param   panel_pal	押したパネルのパレット番号
 * 
 * @retval  tp_retを返す(処理の中で変更する必要がないなら、引数で渡された値をそのまま返す)
 */
//--------------------------------------------------------------
static int TPCallback_JudgeSelect(ACI_PARAM_PTR aci, int tp_ret, int panel_pal)
{
	int fa_no;
	int special;
	
	switch(tp_ret){
	case RECT_HIT_NONE:
	default:
		return tp_ret;
	case ACTIN_TP_JUDGE_1:
		fa_no = FA_NO_JUDGE_1;
		break;
	case ACTIN_TP_JUDGE_2:
		fa_no = FA_NO_JUDGE_2;
		break;
	case ACTIN_TP_JUDGE_3:
		fa_no = FA_NO_JUDGE_3;
		break;
	case ACTIN_TP_JUDGE_MODORU:
		fa_no = FA_NO_JUDGE_MODORU;
		break;
	}
	
	//凄い審判を選択したかチェック
	special = (tp_ret == aci->sys->c_game->special_judge_no) ? TRUE:FALSE;

	ColorEffTCB_PointFadeSet(aci, panel_pal);
	
	EffectTCB_Add(Effect_ButtonDown, aci);
	aci->effect_work.paracgr.scrn_offset = JudgeButtonScrnOffset[tp_ret];
	aci->effect_work.paracgr.scrn_range = &JudgeButtonScrnRect[tp_ret];
	aci->effect_work.paracgr.scrnbuf_no = SCRNBUF_COMMAND_JUDGE;
	aci->effect_work.paracgr.tp_ret = tp_ret;
	aci->effect_work.paracgr.fa_no = fa_no;
	if(special == TRUE){
		aci->effect_work.paracgr.cap[0] = aci->special_heart_cap;
	}

	return tp_ret;
}




//==============================================================================
//
//	サブ関数
//
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   指定範囲のスクリーンバッファを指定コードでクリアする
 *
 * @param   rsr[]			クリア範囲
 * @param   rsr_num			rsrデータ個数
 * @param   bgl				BGLデータ
 * @param   frame_no		フレーム番号
 * @param   clear_code		クリアーコード
 */
//--------------------------------------------------------------
static void Sub_ScrnErase(const REWRITE_SCRN_RECT rsr[], int rsr_num, GF_BGL_INI *bgl, 
	int frame_no, u16 clear_code)
{
	u16 *buf;
	int i, y;
	
	buf = GF_BGL_ScreenAdrsGet(bgl, frame_no);
	GF_ASSERT(buf != NULL);

	for(i = 0; i < rsr_num; i++){
		for(y = rsr[i].top; y <= rsr[i].bottom; y++){
			MI_CpuFill16(&buf[0x20*y + rsr[i].left], clear_code, 
				(rsr[i].right - rsr[i].left + 1) * 2);
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   フォントOAMを作成する
 *
 * @param   aci			BIシステムワークへのポインタ
 * @param   font_actor	生成したフォントOAM関連のワーク代入先
 * @param   str			文字列
 * @param   font_type	フォントタイプ(FONT_SYSTEM等)
 * @param   color		フォントカラー構成
 * @param   pal_offset	パレット番号オフセット
 * @param   pal_id		登録開始パレットID
 * @param   x			座標X
 * @param   y			座標Y
 * @param   pos_center  FONTOAM_LEFT(X左端座標) or FONTOAM_CENTER(X中心座標)
 * @param   ex_bmpwin	呼び出し側でフォントOAMに関連付けるBMPWINを持っている場合はここで渡す。
 *          			NULLの場合は中で作成されます。(ex_bmpwinを使用する場合はstrはNULLでOK)
 */
//--------------------------------------------------------------
static void Sub_FontOamCreate(ACI_PARAM_PTR aci, FONT_ACTOR *font_actor, const STRBUF *str, 
	FONT_TYPE font_type, GF_PRINTCOLOR color, int pal_offset, int pal_id, 
	int x, int y, int pos_center, FONT_EX_BMPWIN *ex_bmpwin)
{
	FONTOAM_INIT finit;
	GF_BGL_BMPWIN bmpwin;
	CHAR_MANAGER_ALLOCDATA cma;
	int vram_size;
	FONTOAM_OBJ_PTR fontoam;
	GF_BGL_INI *bgl;
	CATS_RES_PTR crp;
	int font_len, char_len;
	
	GF_ASSERT(font_actor->fontoam == NULL);
	
	bgl = aci->sys->bgl;
	crp = aci->sys->crp;
	
	//文字列のドット幅から、使用するキャラ数を算出する
	if(ex_bmpwin == NULL){
		FontLenGet(str, font_type, &font_len, &char_len);
	}
	else{
		font_len = ex_bmpwin->font_len;
		char_len = ex_bmpwin->char_len;
	}

	//BMP作成
	if(ex_bmpwin == NULL){
		GF_BGL_BmpWinInit(&bmpwin);
		GF_BGL_BmpWinObjAdd(bgl, &bmpwin, char_len, 16 / 8, 0, 0);
		GF_STR_PrintExpand(&bmpwin, font_type, str, 0, 0, MSG_NO_PUT, color, 
			PANEL_MSG_MARGIN, 0, NULL);
//		GF_STR_PrintColor(&bmpwin, font_type, str, 0, 0, MSG_NO_PUT, color, NULL );
	}
	else{
		bmpwin = ex_bmpwin->bmpwin;
	}

	vram_size = FONTOAM_NeedCharSize(&bmpwin, NNS_G2D_VRAM_TYPE_2DSUB,  HEAPID_ACTIN);
	CharVramAreaAlloc(vram_size, CHARM_CONT_AREACONT, NNS_G2D_VRAM_TYPE_2DSUB, &cma);
	
	//座標位置修正
	if(pos_center == FONTOAM_CENTER){
		x -= font_len / 2;
	}
//	y += SUB_SURFACE_Y_INTEGER - 8;
	y += ACTIN_SUB_ACTOR_DISTANCE_INTEGER - 8;
	
	finit.fontoam_sys = aci->fontoam_sys;
	finit.bmp = &bmpwin;
	finit.clact_set = CATS_GetClactSetPtr(crp);
	finit.pltt = CATS_PlttProxy(crp, pal_id);
	finit.parent = NULL;
	finit.char_ofs = cma.alloc_ofs;
	finit.x = x;
	finit.y = y;
	finit.bg_pri = PANEL_MSG_BGPRI;
	finit.soft_pri = PANEL_MSG_SOFTPRI;
	finit.draw_area = NNS_G2D_VRAM_TYPE_2DSUB;
	finit.heap = HEAPID_ACTIN;
	
	fontoam = FONTOAM_Init(&finit);
//	FONTOAM_SetPaletteOffset(fontoam, pal_offset);
	FONTOAM_SetPaletteOffsetAddTransPlttNo(fontoam, pal_offset);
	FONTOAM_SetMat(fontoam, x, y);
	
	//解放処理
	if(ex_bmpwin == NULL){
		GF_BGL_BmpWinDel(&bmpwin);
	}
	
	font_actor->fontoam = fontoam;
	font_actor->cma = cma;
	font_actor->font_len = font_len;
}

//--------------------------------------------------------------
/**
 * @brief   生成されているフォントOAMを全て削除をする
 * @param   aci		BIシステムワークへのポインタ
 */
//--------------------------------------------------------------
static void Sub_FontOamDeleteAll(ACI_PARAM_PTR aci)
{
	int i;
	
	for(i = 0; i < FA_NO_MAX; i++){
		if(aci->font_actor[i].fontoam != NULL){
			FONTOAM_Delete(aci->font_actor[i].fontoam);
			CharVramAreaFree(&aci->font_actor[i].cma);
			aci->font_actor[i].fontoam = NULL;
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   凄い審判ハートを全て削除する
 * @param   aci		BIシステムワークへのポインタ
 */
//--------------------------------------------------------------
static void Sub_SubHeartJudgeDeleteAll(ACI_PARAM_PTR aci)
{
	if(aci->special_heart_cap != NULL){
		ACIT_SubHeartJudgeActorDel(aci->special_heart_cap);
		aci->special_heart_cap = NULL;
	}
}

//--------------------------------------------------------------
/**
 * @brief   AP値ハートを全て削除する
 * @param   aci			BIシステムワークへのポインタ
 */
//--------------------------------------------------------------
static void Sub_AppHeartDeleteAll(ACI_PARAM_PTR aci)
{
	int i, k;
	
	for(k = 0; k < WAZA_TEMOTI_MAX; k++){
		for(i = 0; i < APP_HEART_MAX; i++){
			if(aci->app_heart_cap[k][i] != NULL){
				ACIT_AppHeartActorDel(aci->app_heart_cap[k][i]);
				aci->app_heart_cap[k][i] = NULL;
			}
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   コンテストタイプアイコンを全て生成する
 *
 * @param   aci		BIシステムワークへのポインタ
 * @param   wazano[]	手持ちの技番号が入った配列へのポインタ(WAZA_TEMOTI_MAX分ある事!)
 */
//--------------------------------------------------------------
static void Sub_ConTypeIconCreateAll(ACI_PARAM_PTR aci, u16 wazano[])
{
	int i;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	TCATS_OBJECT_ADD_PARAM_S obj_param;
	int con_type;

	csp = aci->sys->csp;
	crp = aci->sys->crp;

	obj_param = ConTypeIconObjParam;
	for(i = 0; i < WAZA_TEMOTI_MAX; i++){
		GF_ASSERT(aci->icon_cap[i] == NULL);
		if(wazano[i] != 0){
			con_type = aci->memory_decord.con_type[i];
			
			obj_param.id[CLACT_U_CHAR_RES] = CHARID_CONTYPE_ICON_1 + i;
			obj_param.x = WazaIconPos[i][0];
			obj_param.y = WazaIconPos[i][1];
			aci->icon_cap[i] = ConTypeIcon_ActorCreate(csp, crp, 
				con_type, &obj_param);
			CATS_ObjectPosSetCap_SubSurface(aci->icon_cap[i], obj_param.x, obj_param.y, 
				ACTIN_SUB_ACTOR_DISTANCE);
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   コンテストタイプアイコンを全て削除する
 * @param   aci		BIシステムワークへのポインタ
 */
//--------------------------------------------------------------
static void Sub_ConTypeIconDeleteAll(ACI_PARAM_PTR aci)
{
	int i;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;

	csp = aci->sys->csp;
	crp = aci->sys->crp;

	for(i = 0; i < WAZA_TEMOTI_MAX; i++){
		if(aci->icon_cap[i] != NULL){
			ConTypeIcon_ActorDelete(aci->icon_cap[i]);
			aci->icon_cap[i] = NULL;
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   スクリーン書き換え
 *
 * @param   aci				ACIシステムワークへのポインタ
 * @param   scrn_offset		加算するスクリーン値
 * @param   range			スクリーン書き換え範囲
 * @param   scrnbuf_no		元データとなるスクリーンバッファの番号
 * @param   anm_no			アニメ番号
 */
//--------------------------------------------------------------
static void Sub_ScrnOffsetRewrite(ACI_PARAM_PTR aci, const s16 *scrn_offset, 
	const REWRITE_SCRN_RECT *range, int scrnbuf_no, int anm_no)
{
	int x, y;
	GF_BGL_INI *bgl;
	u16 *scrn, *write_scrn;
	u16 *src_scrn, *read_scrn;
	int add_scrn;
	
	bgl = aci->sys->bgl;
	scrn = GF_BGL_ScreenAdrsGet(bgl, ACTINSUB_FRAME_PANEL);
	src_scrn = aci->scrn_buf[scrnbuf_no];
	add_scrn = scrn_offset[anm_no];
	
	for(y = range->top; y <= range->bottom; y++){
		write_scrn = &scrn[y * 32];
		read_scrn = &src_scrn[y * 32];
		for(x = range->left; x <= range->right; x++){
			write_scrn[x] = read_scrn[x] + add_scrn;
		}
	}
	
	GF_BGL_LoadScreenV_Req(bgl, ACTINSUB_FRAME_PANEL);
}

//--------------------------------------------------------------
/**
 * @brief   技タイプ毎にCGRデータを書き換える
 *
 * @param   aci				BIシステムワークへのポインタ
 * @param   con_type		コンテスト技タイプ(手持ち無しの場合は-1)
 * @param   waza_pos		手持ちの技の位置(0～3)
 */
//--------------------------------------------------------------
static void Sub_WazaTypeCGRTrans(ACI_PARAM_PTR aci, int con_type, int waza_pos)
{
#if 0
	GF_BGL_INI *bgl;
	u32 screen_type;
	
	bgl = aci->sys->bgl;
	screen_type = GF_BGL_ScreenTypeGet(bgl, ACTINSUB_FRAME_PANEL);
	
	WazaPanel_EasyCharLoad(bgl, waza_type, HEAPID_ACTIN, ACTINSUB_FRAME_PANEL, 
		WazaTypeCgrPos[waza_pos], screen_type);
	WazaPanel_EasyPalLoad(aci->sys->pfd, waza_type, HEAPID_ACTIN, FADE_SUB_BG, 
		WAZATYPE_START_PALPOS + waza_pos);
#endif
	const u16 * const type_pal_tbl[] = {
		&con_engi_type_ncl[16 * 3],		//CONTYPE_STYLE
		&con_engi_type_ncl[16 * 4],		//CONTYPE_BEAUTIFUL
		&con_engi_type_ncl[16 * 1],		//CONTYPE_CUTE
		&con_engi_type_ncl[16 * 2],		//CONTYPE_CLEVER
		&con_engi_type_ncl[16 * 0],		//CONTYPE_STRONG
	};
	
	if(con_type != -1){
		PaletteWorkSet(aci->sys->pfd, type_pal_tbl[con_type], FADE_SUB_BG, 
			(WAZATYPE_START_PALPOS + waza_pos) * 16, 0x20);
	}
	else{
		Sub_ScrnOffsetRewrite(aci, &WazaButtonNotTouchScrnOffset[waza_pos], 
			&WazaButtonNotTouchScrnRect[waza_pos], SCRNBUF_COMMAND_WAZA, 0);
		PaletteWorkSet(aci->sys->pfd, 
			&aci->pal_buf[PALBUF_COMMAND][ACI_NOT_SELECT_PANEL_PALNO * 16], 
			FADE_SUB_BG, (WAZATYPE_START_PALPOS + waza_pos) * 16, 0x20);
	}
}

//--------------------------------------------------------------
/**
 * @brief   背景以外のフレームを全て非表示にする
 */
//--------------------------------------------------------------
static void Sub_BackScrnOnlyVisible(void)
{
	int i;
	
	for(i = 0; i < ACI_BG_NUM; i++){
		if(GF_BGL_FRAME0_S + i != ACTINSUB_FRAME_BACK){
			GF_BGL_VisibleSet(GF_BGL_FRAME0_S + i, VISIBLE_OFF);
		}
		else{
			GF_BGL_VisibleSet(GF_BGL_FRAME0_S + i, VISIBLE_ON);
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   パネルタッチエフェクト終了後、背景のみにするための処理を色々する(フォントOBJの削除とか)
 * @param   none		BIシステムワークへのポインタ
 */
//--------------------------------------------------------------
static void Sub_TouchEndDelete(ACI_PARAM_PTR aci)
{
	Sub_SceneOBJDelete(aci);
//	VWaitTCB_Add(VWait_BackScrnOnlyVisible, aci, VWAIT_TCBPRI_BACKSCRN_VISIBLE);
}

//--------------------------------------------------------------
/**
 * @brief   BGタイプが切り替わる毎に削除する必要のあるOBJのDelete処理
 * @param   aci		BIシステムワークへのポインタ
 */
//--------------------------------------------------------------
static void Sub_SceneOBJDelete(ACI_PARAM_PTR aci)
{
	Sub_SubHeartJudgeDeleteAll(aci);
	Sub_AppHeartDeleteAll(aci);
	Sub_ConTypeIconDeleteAll(aci);
	Sub_FontOamDeleteAll(aci);
}



//==============================================================================
//
//	エフェクトTCB
//
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   エフェクトTCBを生成する
 *
 * @param   func		TCBにセットする関数ポインタ
 * @param   aci			BIシステムワークへのポインタ
 */
//--------------------------------------------------------------
static void EffectTCB_Add(TCB_FUNC func, ACI_PARAM_PTR aci)
{
	GF_ASSERT(aci->effect_tcb == NULL);
	
	MI_CpuClear8(&aci->effect_work, sizeof(ACI_EFFECT_WORK));
	aci->effect_tcb = TCB_Add(func, aci, TCBPRI_AINPUT_EFFECT);
}

//--------------------------------------------------------------
/**
 * @brief   エフェクトTCBを削除する
 * @param   aci		BIシステムワークへのポインタ
 */
//--------------------------------------------------------------
static void EffectTCB_Delete(ACI_PARAM_PTR aci)
{
	if(aci->effect_tcb != NULL){
		TCB_Delete(aci->effect_tcb);
		aci->effect_tcb = NULL;
		MI_CpuClear8(&aci->effect_work, sizeof(ACI_EFFECT_WORK));
	}
}


//--------------------------------------------------------------
/**
 * @brief   パネル部分をキャラ転送アニメを実行して書き換えます。
 *          1つのパネルに対して1つのフォントOBJがセットになっているもの用の汎用タスクです
 *
 * @param   tcb		TCBへのポインタ
 * @param   work	BIシステムワークへのポインタ
 */
//--------------------------------------------------------------
static void Effect_ButtonDown(TCB_PTR tcb, void *work)
{
	ACI_PARAM_PTR aci = work;
	GF_BGL_INI *bgl;
	int x, y;
	int i;
	
	bgl = aci->sys->bgl;
	
	switch(aci->effect_work.seq){
	case 0:
		Sub_ScrnOffsetRewrite(aci, aci->effect_work.paracgr.scrn_offset, 
			aci->effect_work.paracgr.scrn_range, aci->effect_work.paracgr.scrnbuf_no, 2);
		
		FONTOAM_GetMat(aci->font_actor[aci->effect_work.paracgr.fa_no].fontoam, &x, &y);
		FONTOAM_SetMat(aci->font_actor[aci->effect_work.paracgr.fa_no].fontoam, 
			x, y + SCRN_SCROLL_A_EFF_Y);
		
		for(i = 0; i < PARACGR_CAP_MAX; i++){
			if(aci->effect_work.paracgr.cap[i] != NULL){
				CATS_ObjectPosMove(aci->effect_work.paracgr.cap[i]->act, 0, SCRN_SCROLL_A_EFF_Y);
			}
		}
		
		aci->effect_work.seq++;
		break;
	case 1:
		aci->effect_work.wait++;
		if(aci->effect_work.wait <= SCRN_TOUCH_ANM_WAIT){
			break;
		}
		aci->effect_work.wait = 0;
		aci->effect_work.seq++;
		//break;

	case 2:
		Sub_ScrnOffsetRewrite(aci, aci->effect_work.paracgr.scrn_offset, 
			aci->effect_work.paracgr.scrn_range, aci->effect_work.paracgr.scrnbuf_no, 1);
		
		FONTOAM_GetMat(aci->font_actor[aci->effect_work.paracgr.fa_no].fontoam, &x, &y);
		FONTOAM_SetMat(aci->font_actor[aci->effect_work.paracgr.fa_no].fontoam, 
			x, y + SCRN_SCROLL_BACK_A_EFF_Y);
		
		for(i = 0; i < PARACGR_CAP_MAX; i++){
			if(aci->effect_work.paracgr.cap[i] != NULL){
				CATS_ObjectPosMove(aci->effect_work.paracgr.cap[i]->act, 
					0, SCRN_SCROLL_BACK_A_EFF_Y);
			}
		}
		
		aci->effect_work.seq++;
		break;
	default:
		aci->effect_work.wait++;
		if(aci->effect_work.wait > SCRN_TOUCH_WAIT){
			Sub_TouchEndDelete(aci);
			EffectTCB_Delete(aci);
			return;
		}
		break;
	}
}

//--------------------------------------------------------------
/**
 * @brief   パネル部分をキャラ転送アニメを実行して書き換えます。
 *          技選択時専用です。
 *
 * @param   tcb		TCBへのポインタ
 * @param   work	ACIシステムワークへのポインタ
 */
//--------------------------------------------------------------
static void Effect_WazaButtonDown(TCB_PTR tcb, void *work)
{
	ACI_PARAM_PTR aci = work;
	GF_BGL_INI *bgl;
	int x, y;
	int fa_waza, fa_up, fa_down;
	int cap_icon, wazano;
	u16 wazano_array[WAZA_TEMOTI_MAX];
	int i, wazapos;
	
	bgl = aci->sys->bgl;
	
	for(i = 0; i < WAZA_TEMOTI_MAX; i++){
		wazano_array[i] = PokeParaGet(aci->sys->c_game->pp[aci->sys->c_game->my_breeder_no], 
			ID_PARA_waza1 + i, NULL);
	}

	switch(aci->effect_work.paracgr.tp_ret){
	case ACTIN_TP_WAZA_1:
		fa_waza = FA_NO_WAZA_1;
		fa_up = FA_NO_SETUMEI_1_U;
		fa_down = FA_NO_SETUMEI_1_D;
		cap_icon = 0;
		wazano = wazano_array[0];
		wazapos = 0;
		break;
	case ACTIN_TP_WAZA_2:
		fa_waza = FA_NO_WAZA_2;
		fa_up = FA_NO_SETUMEI_2_U;
		fa_down = FA_NO_SETUMEI_2_D;
		cap_icon = 1;
		wazano = wazano_array[1];
		wazapos = 1;
		break;
	case ACTIN_TP_WAZA_3:
		fa_waza = FA_NO_WAZA_3;
		fa_up = FA_NO_SETUMEI_3_U;
		fa_down = FA_NO_SETUMEI_3_D;
		cap_icon = 2;
		wazano = wazano_array[2];
		wazapos = 2;
		break;
	case ACTIN_TP_WAZA_4:
		fa_waza = FA_NO_WAZA_4;
		fa_up = FA_NO_SETUMEI_4_U;
		fa_down = FA_NO_SETUMEI_4_D;
		cap_icon = 3;
		wazano = wazano_array[3];
		wazapos = 3;
		break;
//	case SELECT_CANCEL:		今の所キャンセルはない　2005.12.03(土)
	default:
		fa_waza = 0;
		fa_up = 0;
		fa_down = 0;
		cap_icon = 0;
		wazano = 0;
		break;
	}
	
	switch(aci->effect_work.seq){
	case 0:
		Sub_ScrnOffsetRewrite(aci, aci->effect_work.paracgr.scrn_offset, 
			aci->effect_work.paracgr.scrn_range, aci->effect_work.paracgr.scrnbuf_no, 2);
		
		if(1){	//aci->effect_work.paracgr.tp_ret != SELECT_CANCEL){
			FONTOAM_GetMat(aci->font_actor[fa_waza].fontoam, &x, &y);
			FONTOAM_SetMat(aci->font_actor[fa_waza].fontoam, x, y + SCRN_SCROLL_A_EFF_Y);
			FONTOAM_GetMat(aci->font_actor[fa_up].fontoam, &x, &y);
			FONTOAM_SetMat(aci->font_actor[fa_up].fontoam, x, y + SCRN_SCROLL_A_EFF_Y);
			FONTOAM_GetMat(aci->font_actor[fa_down].fontoam, &x, &y);
			FONTOAM_SetMat(aci->font_actor[fa_down].fontoam, x, y + SCRN_SCROLL_A_EFF_Y);
			if(wazano != 0){
				CATS_ObjectPosMove(aci->icon_cap[cap_icon]->act, 0, SCRN_SCROLL_A_EFF_Y);
				for(i = 0; i < APP_HEART_MAX; i++){
					if(aci->app_heart_cap[wazapos][i] != NULL){
						CATS_ObjectPosMove(aci->app_heart_cap[wazapos][i]->act, 0, 
							SCRN_SCROLL_A_EFF_Y);
					}
				}
			}
		}
		else{
		#if 0	//今のところキャンセルなし 2005.12.02(金)
			FontOBJ_PosGet(&aci->font_actor[FA_NO_WAZA_MODORU], FONTOBJ_POS_LEFT, &x, &y);
			FontOBJ_PosSet(&aci->font_actor[FA_NO_WAZA_MODORU], FONTOBJ_POS_LEFT, 
				x, y + SCRN_SCROLL_A_EFF_Y);
		#endif
		}
		
		aci->effect_work.seq++;
		break;
	case 1:
		aci->effect_work.wait++;
		if(aci->effect_work.wait <= SCRN_TOUCH_ANM_WAIT){
			break;
		}
		aci->effect_work.wait = 0;
		aci->effect_work.seq++;
		//break;

	case 2:
		Sub_ScrnOffsetRewrite(aci, aci->effect_work.paracgr.scrn_offset, 
			aci->effect_work.paracgr.scrn_range, aci->effect_work.paracgr.scrnbuf_no, 1);
		
		if(1){	//aci->effect_work.paracgr.tp_ret != SELECT_CANCEL){
			FONTOAM_GetMat(aci->font_actor[fa_waza].fontoam, &x, &y);
			FONTOAM_SetMat(aci->font_actor[fa_waza].fontoam, x, y + SCRN_SCROLL_BACK_A_EFF_Y);
			FONTOAM_GetMat(aci->font_actor[fa_up].fontoam, &x, &y);
			FONTOAM_SetMat(aci->font_actor[fa_up].fontoam, x, y + SCRN_SCROLL_BACK_A_EFF_Y);
			FONTOAM_GetMat(aci->font_actor[fa_down].fontoam, &x, &y);
			FONTOAM_SetMat(aci->font_actor[fa_down].fontoam, x, y + SCRN_SCROLL_BACK_A_EFF_Y);
			if(wazano != 0){
				CATS_ObjectPosMove(aci->icon_cap[cap_icon]->act, 0, SCRN_SCROLL_BACK_A_EFF_Y);
				for(i = 0; i < APP_HEART_MAX; i++){
					if(aci->app_heart_cap[wazapos][i] != NULL){
						CATS_ObjectPosMove(aci->app_heart_cap[wazapos][i]->act, 0, 
							SCRN_SCROLL_BACK_A_EFF_Y);
					}
				}
			}
		}
		else{
		#if 0	//今のところキャンセルなし 2005.12.02(金)
			FontOBJ_PosGet(&aci->font_actor[FA_NO_WAZA_MODORU], FONTOBJ_POS_LEFT, &x, &y);
			FontOBJ_PosSet(&aci->font_actor[FA_NO_WAZA_MODORU], FONTOBJ_POS_LEFT, 
				x, y + SCRN_SCROLL_BACK_A_EFF_Y);
		#endif
		}
		
		aci->effect_work.seq++;
		break;
	default:
		aci->effect_work.wait++;
		if(aci->effect_work.wait > SCRN_TOUCH_WAIT){
			Sub_TouchEndDelete(aci);
			EffectTCB_Delete(aci);
			return;
		}
		break;
	}
}

//--------------------------------------------------------------
/**
 * @brief   カラーエフェクトTCBを生成する
 *
 * @param   func		TCBにセットする関数ポインタ
 * @param   aci			BIシステムワークへのポインタ
 */
//--------------------------------------------------------------
static void ColorEffTCB_Add(TCB_FUNC func, ACI_PARAM_PTR aci)
{
	GF_ASSERT(aci->color_eff_tcb == NULL);
	
	MI_CpuClear8(&aci->color_work, sizeof(ACI_COLOR_EFF_WORK));
	aci->color_eff_tcb = TCB_Add(func, aci, TCBPRI_AINPUT_COLOR_EFFECT);
}

//--------------------------------------------------------------
/**
 * @brief   カラーエフェクトTCBを削除する
 * @param   aci		BIシステムワークへのポインタ
 */
//--------------------------------------------------------------
static void ColorEffTCB_Delete(ACI_PARAM_PTR aci)
{
	if(aci->color_eff_tcb != NULL){
		TCB_Delete(aci->color_eff_tcb);
		aci->color_eff_tcb = NULL;
		MI_CpuClear8(&aci->color_work, sizeof(ACI_COLOR_EFF_WORK));
	}
}

//--------------------------------------------------------------
/**
 * @brief   特定の位置のカラーだけをフェードさせるタスクを生成する
 * @param   aci		BIシステムワークへのポインタ
 * @param   pal_pos	フェードさせるパレット番号
 */
//--------------------------------------------------------------
static void ColorEffTCB_PointFadeSet(ACI_PARAM_PTR aci, int pal_pos)
{
	if(pal_pos == 0xff){
		return;
	}
	
	ColorEffTCB_Add(ColorEff_PointFade, aci);
	aci->color_work.pal_pos = pal_pos;
}

//--------------------------------------------------------------
/**
 * @brief   特定の位置のカラーだけをフェードさせる
 *
 * @param   tcb			TCBへのポインタ
 * @param   work		BIシステムワークへのポインタ
 */
//--------------------------------------------------------------
static void ColorEff_PointFade(TCB_PTR tcb, void *work)
{
	ACI_PARAM_PTR aci = work;
	ACI_COLOR_EFF_WORK *cw;
	PALETTE_FADE_PTR pfd;
	int i, end;
	
	cw = &aci->color_work;
	pfd = aci->sys->pfd;
	end = FALSE;
	
	switch(cw->seq){
	case 0:
		cw->evy = TOUCH_FADE_EVY;
		cw->evy_add = -TOUCH_FADE_ADD_EVY;
		//最初の計算分を足しこんでおく
		cw->evy -= cw->evy_add;
		
		cw->seq++;
		//break;
	case 1:
		cw->evy += cw->evy_add;
		if(cw->evy_add >= 0 && cw->evy >= (16<<8)){
			cw->evy = 16<<8;
			end = TRUE;
		}
		else if(cw->evy_add < 0 && cw->evy <= 0){
			cw->evy = 0;
			end = TRUE;
		}
		
	#if 1
		//全体を白く
		SoftFadePfd(pfd, FADE_SUB_BG, cw->pal_pos * 16, 16, cw->evy >> 8, 0x7fff);
	#elif 0
		//全体を暗く
		SoftFadePfd(pfd, FADE_SUB_BG, cw->pal_pos * 16, 16, cw->evy >> 8, 0x0000);
		//枠だけ白く
		SoftFadePfd(pfd, FADE_SUB_BG, cw->pal_pos * 16 + 3, 1, cw->evy >> 8, 0x7fff);
	#else
		SoftFadePfd(pfd, FADE_SUB_BG, cw->pal_pos * 16, 16, (cw->evy >> 8) / 2, 0x7fff);
		//全体を暗く
		SoftFadePfd(pfd, FADE_SUB_BG, cw->pal_pos * 16 + 1, 1, cw->evy >> 8, 0x7b1a);
		//枠だけ白く
		SoftFadePfd(pfd, FADE_SUB_BG, cw->pal_pos * 16 + 0xa, 1, cw->evy >> 8, 0x4634);
	#endif
		if(end == TRUE){
			ColorEffTCB_Delete(aci);
			return;
		}
		break;
	}
}

//--------------------------------------------------------------
/**
 * @brief   MEMORY_DECORD_WORKを解放する
 * @param   aci		BIシステムワークへのポインタ
 */
//--------------------------------------------------------------
static void MemoryDecordWorkFree(ACI_PARAM_PTR aci)
{
	int i, client;

	for(i = 0; i < WAZA_TEMOTI_MAX; i++){
		if(aci->memory_decord.exbmp_waza[i].bmpwin.chrbuf != NULL){
			GF_BGL_BmpWinDel(&aci->memory_decord.exbmp_waza[i].bmpwin);
		}
		if(aci->memory_decord.exbmp_explain_u[i].bmpwin.chrbuf != NULL){
			GF_BGL_BmpWinDel(&aci->memory_decord.exbmp_explain_u[i].bmpwin);
		}
		if(aci->memory_decord.exbmp_explain_d[i].bmpwin.chrbuf != NULL){
			GF_BGL_BmpWinDel(&aci->memory_decord.exbmp_explain_d[i].bmpwin);
		}
	}

	for(i = 0; i < JUDGE_MAX; i++){
		if(aci->memory_decord.exbmp_judge[i].bmpwin.chrbuf != NULL){
			GF_BGL_BmpWinDel(&aci->memory_decord.exbmp_judge[i].bmpwin);
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   技パラメータのデータをメモリに展開する
 *
 * @param   aci				BIシステムワークへのポインタ
 * @param   wazano			技番号の入った配列へのポインタ(WAZA_TEMOTI_MAX分)
 */
//--------------------------------------------------------------
void AINPUT_WazaParaMemoryDecord(ACI_PARAM_PTR aci, u16 wazano[])
{
	MEMORY_DECORD_WORK *mdw;
	int i;
	STRBUF *wazaname_p;
	STRBUF *setumei_u_src, *setumei_d_src, *judge_src;
	u32 u_id, d_id;
	
	mdw = &aci->memory_decord;
	
	for(i = 0; i < WAZA_TEMOTI_MAX; i++){
		if(wazano[i] != 0){
			mdw->ap_no[i] = WT_WazaDataParaGet(wazano[i], ID_WTD_ap_no);
			mdw->con_type[i] = WT_WazaDataParaGet(wazano[i], ID_WTD_contype);
		}
		else{
			mdw->ap_no[i] = 0;
			mdw->con_type[i] = 0;
		}
		
		//BMPWIN：技名
		wazaname_p = MSGDAT_UTIL_GetWazaName(wazano[i], HEAPID_ACTIN);
		FontExBmpwin_FontSet(aci, wazaname_p, FONT_BUTTON, &mdw->exbmp_waza[i], MSGCOLOR_WAZA);
		STRBUF_Delete(wazaname_p);
		
		//BMPWIN:技説明
		ConTool_GetAPSetumeiMsgID(mdw->ap_no[i], &u_id, &d_id);
		setumei_u_src = MSGMAN_AllocString(aci->sys->explain_msg, u_id);
		setumei_d_src = MSGMAN_AllocString(aci->sys->explain_msg, d_id);
		FontExBmpwin_FontSet(aci, setumei_u_src, FONT_SYSTEM, &mdw->exbmp_explain_u[i], 
			MSGCOLOR_SETUMEI);
		FontExBmpwin_FontSet(aci, setumei_d_src, FONT_SYSTEM, &mdw->exbmp_explain_d[i], 
			MSGCOLOR_SETUMEI);
		STRBUF_Delete(setumei_u_src);
		STRBUF_Delete(setumei_d_src);
	}
	
	//審判名
	for(i = 0; i < JUDGE_MAX; i++){
		judge_src = ADV_MSGDAT_GetJudgeName(aci->sys->c_game->jd[i].name_id, HEAPID_ACTIN);
		FontExBmpwin_FontSet(aci, judge_src, FONT_BUTTON, &mdw->exbmp_judge[i], 
			MSGCOLOR_JUDGE);
		STRBUF_Delete(judge_src);
	}

	//-- ついでにここでカーソルも生成 --//
	{
		CCURSOR_ResourceLoad(aci->sys->csp, aci->sys->crp, aci->sys->pfd, 
			CHARID_ACTIN_CURSOR, PLTTID_ACTIN_CURSOR,
			CELLID_ACTIN_CURSOR, CELLANMID_ACTIN_CURSOR);
		aci->cursor = CCURSOR_ActorCreate(aci->sys->csp, aci->sys->crp, HEAPID_ACTIN, 
			CHARID_ACTIN_CURSOR, PLTTID_ACTIN_CURSOR, CELLID_ACTIN_CURSOR, CELLANMID_ACTIN_CURSOR, 
			SOFTPRI_CURSOR, BGPRI_CURSOR);
	}
}

//--------------------------------------------------------------
/**
 * @brief   FONT_EX_BMPWINに対してフォントデータを作成し、セットする
 *
 * @param   aci				BIシステムワークへのポインタ
 * @param   str				文字列へのポインタ
 * @param   font_type		フォントタイプ
 * @param   ex_bmpwin		データ代入先
 * @param   color			文字カラー
 */
//--------------------------------------------------------------
static void FontExBmpwin_FontSet(ACI_PARAM_PTR aci, const STRBUF *str, FONT_TYPE font_type, 	
	FONT_EX_BMPWIN *ex_bmp, GF_PRINTCOLOR color)
{
	int font_len, char_len;
	
	FontLenGet(str, font_type, &font_len, &char_len);
	ex_bmp->font_len = font_len;
	ex_bmp->char_len = char_len;
	if(ex_bmp->bmpwin.chrbuf != NULL){
		GF_BGL_BmpWinDel(&ex_bmp->bmpwin);
	}
	GF_BGL_BmpWinInit(&ex_bmp->bmpwin);
	GF_BGL_BmpWinObjAdd(aci->sys->bgl, &ex_bmp->bmpwin, char_len, 16 / 8, 0, 0);
	GF_STR_PrintExpand(&ex_bmp->bmpwin, font_type, str, 0, 0, MSG_NO_PUT, color, 
		PANEL_MSG_MARGIN, 0, NULL);
}

//--------------------------------------------------------------
/**
 * @brief   文字列の長さを取得する
 *
 * @param   str				文字列へのポインタ
 * @param   font_type		フォントタイプ
 * @param   ret_dot_len		ドット幅代入先
 * @param   ret_char_len	キャラ幅代入先
 */
//--------------------------------------------------------------
static void FontLenGet(const STRBUF *str, FONT_TYPE font_type, int *ret_dot_len, int *ret_char_len)
{
	int dot_len, char_len;
	
	//文字列のドット幅から、使用するキャラ数を算出する
	dot_len = FontProc_GetPrintStrWidth(font_type, str, PANEL_MSG_MARGIN);
	char_len = dot_len / 8;
	if(FX_ModS32(dot_len, 8) != 0){
		char_len++;
	}
	
	*ret_dot_len = dot_len;
	*ret_char_len = char_len;
}



//==============================================================================
//
//	キー入力
//
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   キー入力判定処理
 * @param   aci		BIシステムワークへのポインタ
 * @retval  結果(当たりなしの場合はRECT_HIT_NONE)
 */
//--------------------------------------------------------------
static int CursorCheck(ACI_PARAM_PTR aci)
{
	CURSOR_MOVE *move;
	const BG_MAKE_DATA *bmd;

	move = &aci->cursor_move;
	bmd = &BgMakeData[aci->makedata_no];
	
	if(bmd->cursor_move_func == NULL){
		return RECT_HIT_NONE;
	}
	
	if(move->cursor_on == FALSE){
		if(aci->decend_key == TRUE || 
				(sys.trg & (PAD_BUTTON_A|PAD_BUTTON_B|PAD_BUTTON_X|PAD_BUTTON_Y
				|PAD_KEY_RIGHT|PAD_KEY_LEFT|PAD_KEY_UP|PAD_KEY_DOWN))){
			if(aci->decend_key == FALSE){
				Snd_SePlay(ASE_CCURSOR_MOVE_SE);	//キーを押してカーソルを表示した時音を鳴らす
			}
			move->cursor_on = TRUE;
			aci->decend_key = FALSE;
			bmd->cursor_move_func(aci, TRUE);
		}
		return RECT_HIT_NONE;
	}
	
	return bmd->cursor_move_func(aci, FALSE);
}

//--------------------------------------------------------------
/**
 * @brief   カーソル移動：技選択
 *
 * @param   aci				BIシステムワークへのポインタ
 * @param   init_flag		TRUE:初期化処理
 *
 * @retval  結果(当たりなしの場合はRECT_HIT_NONE)
 */
//--------------------------------------------------------------
static int CursorMove_WazaSelect(ACI_PARAM_PTR aci, int init_flag)
{
	CURSOR_MOVE *move;
	u32 key;
	const BG_MAKE_DATA *bmd;
	int index, i;
	u8 move_data[CURSOR_WAZA_SELECT_Y_MENU_NUM][CURSOR_WAZA_SELECT_X_MENU_NUM];
	ACI_CURSOR_SAVE *cursor_save;
	u16 wazano[WAZA_TEMOTI_MAX];
	
	cursor_save = &aci->cursor_save;
	move = &aci->cursor_move;
	bmd = &BgMakeData[aci->makedata_no];
	for(i = 0;i < WAZA_TEMOTI_MAX; i++){
		wazano[i] = PokeParaGet(aci->sys->c_game->pp[aci->sys->c_game->my_breeder_no], 
			ID_PARA_waza1 + i, NULL);
	}

	if(init_flag == TRUE){
		move->x_menu = cursor_save->waza_x;
		move->y_menu = cursor_save->waza_y;
		index = CursorMoveDataWazaSelect[move->y_menu][move->x_menu];
		if(wazano[index - WAZASELE_INDEX_SKILL_1] == 0){
			cursor_save->waza_x = 0;
			cursor_save->waza_y = 0;
			move->x_menu = 0;
			move->y_menu = 0;
			index = CursorMoveDataWazaSelect[move->y_menu][move->x_menu];
		}
		CCURSOR_PosSetON_Surface(aci->cursor, bmd->tpd[index].rect.left+8, 
			bmd->tpd[index].rect.right-8, 
			bmd->tpd[index].rect.top+8, bmd->tpd[index].rect.bottom-8,
			ACTIN_SUB_ACTOR_DISTANCE);
		return RECT_HIT_NONE;
	}

	MI_CpuCopy8(CursorMoveDataWazaSelect, move_data, 
		CURSOR_WAZA_SELECT_Y_MENU_NUM * CURSOR_WAZA_SELECT_X_MENU_NUM);
#if 0	//手持ち技がない場所もカーソルが移動出来るように変更 2006.05.27(土)
	for(i = 0; i < WAZA_TEMOTI_MAX; i++){
		if(wazano[i] == 0){
			((u8*)move_data)[i] = 0xff;	//手持ち技がない所は範囲からはずす
		}
	}
#endif
	
	key = CursorMove_KeyCheckMove(move, 
		CURSOR_WAZA_SELECT_X_MENU_NUM, CURSOR_WAZA_SELECT_Y_MENU_NUM,
		move_data[0]);
	switch(key){
	case PAD_KEY_UP:
	case PAD_KEY_DOWN:
	case PAD_KEY_LEFT:
	case PAD_KEY_RIGHT:
		index = CursorMoveDataWazaSelect[move->y_menu][move->x_menu];
		CCURSOR_PosSetON_Surface(aci->cursor, bmd->tpd[index].rect.left+8, 
			bmd->tpd[index].rect.right-8, 
			bmd->tpd[index].rect.top+8, bmd->tpd[index].rect.bottom-8,
			ACTIN_SUB_ACTOR_DISTANCE);
		break;
	case PAD_BUTTON_DECIDE:
		return CursorMoveDataWazaSelect[move->y_menu][move->x_menu];
	case PAD_BUTTON_CANCEL:
		break;
	}

	return RECT_HIT_NONE;
}

//--------------------------------------------------------------
/**
 * @brief   カーソル位置保存：コマンド選択
 * @param   aci				BIシステムワークへのポインタ
 * @param   index			選択した項目
 */
//--------------------------------------------------------------
static void CursorSave_WazaSelect(ACI_PARAM_PTR aci, int index)
{
	ACI_CURSOR_SAVE *cursor_save;
	int x, y;

	cursor_save = &aci->cursor_save;
	for(y = 0; y < CURSOR_WAZA_SELECT_Y_MENU_NUM; y++){
		for(x = 0; x < CURSOR_WAZA_SELECT_X_MENU_NUM; x++){
			if(index == CursorMoveDataWazaSelect[y][x]){
				cursor_save->waza_x = x;
				cursor_save->waza_y = y;
				return;
			}
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   カーソル移動：審判選択
 *
 * @param   aci				BIシステムワークへのポインタ
 * @param   init_flag		TRUE:初期化処理
 *
 * @retval  結果(当たりなしの場合はRECT_HIT_NONE)
 */
//--------------------------------------------------------------
static int CursorMove_JudgeSelect(ACI_PARAM_PTR aci, int init_flag)
{
	CURSOR_MOVE *move;
	u32 key;
	const BG_MAKE_DATA *bmd;
	int index, i;
	u8 move_data[CURSOR_JUDGE_SELECT_Y_MENU_NUM][CURSOR_JUDGE_SELECT_X_MENU_NUM];
	ACI_CURSOR_SAVE *cursor_save;
	
	cursor_save = &aci->cursor_save;
	move = &aci->cursor_move;
	bmd = &BgMakeData[aci->makedata_no];

	if(init_flag == TRUE){
		move->x_menu = cursor_save->judge_x;
		move->y_menu = cursor_save->judge_y;
		index = CursorMoveDataJudgeSelect[move->y_menu][move->x_menu];
		CCURSOR_PosSetON_Surface(aci->cursor, bmd->tpd[index].rect.left+8, 
			bmd->tpd[index].rect.right-8, 
			bmd->tpd[index].rect.top+8, bmd->tpd[index].rect.bottom-8,
			ACTIN_SUB_ACTOR_DISTANCE);
		return RECT_HIT_NONE;
	}

	MI_CpuCopy8(CursorMoveDataJudgeSelect, move_data, 
		CURSOR_JUDGE_SELECT_Y_MENU_NUM * CURSOR_JUDGE_SELECT_X_MENU_NUM);
	
	key = CursorMove_KeyCheckMove(move, 
		CURSOR_JUDGE_SELECT_X_MENU_NUM, CURSOR_JUDGE_SELECT_Y_MENU_NUM,
		move_data[0]);
	switch(key){
	case PAD_KEY_UP:
	case PAD_KEY_DOWN:
	case PAD_KEY_LEFT:
	case PAD_KEY_RIGHT:
		index = CursorMoveDataJudgeSelect[move->y_menu][move->x_menu];
		CCURSOR_PosSetON_Surface(aci->cursor, bmd->tpd[index].rect.left+8, 
			bmd->tpd[index].rect.right-8, 
			bmd->tpd[index].rect.top+8, bmd->tpd[index].rect.bottom-8,
			ACTIN_SUB_ACTOR_DISTANCE);
		break;
	case PAD_BUTTON_DECIDE:
		return CursorMoveDataJudgeSelect[move->y_menu][move->x_menu];
	case PAD_BUTTON_CANCEL:
		return JUDGESELE_INDEX_CANCEL;
	}

	return RECT_HIT_NONE;
}

//--------------------------------------------------------------
/**
 * @brief   カーソル位置保存：コマンド選択
 * @param   aci				BIシステムワークへのポインタ
 * @param   index			選択した項目
 */
//--------------------------------------------------------------
static void CursorSave_JudgeSelect(ACI_PARAM_PTR aci, int index)
{
	ACI_CURSOR_SAVE *cursor_save;
	int client_no, x, y;

	if(index == JUDGESELE_INDEX_CANCEL){
		return;
	}
	
	cursor_save = &aci->cursor_save;
	for(y = 0; y < CURSOR_JUDGE_SELECT_Y_MENU_NUM; y++){
		for(x = 0; x < CURSOR_JUDGE_SELECT_X_MENU_NUM; x++){
			if(index == CursorMoveDataJudgeSelect[y][x]){
				cursor_save->judge_x = x;
				cursor_save->judge_y = y;
				return;
			}
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   キー入力によるカーソル移動処理
 *
 * @param   move			カーソル移動用ワークへのポインタ
 * @param   x_menu_num		水平方向のメニュー数
 * @param   y_menu_num		垂直方向のメニュー数
 * @param   move_data		移動データへのポインタ(移動先が同じ場所なら移動しない判定に必要)
 *                          その判定が必要でないならNULLでOK
 *
 * @retval  押されたキー
 */
//--------------------------------------------------------------
static u32 CursorMove_KeyCheckMove(CURSOR_MOVE *move, int x_menu_num, int y_menu_num, 
	const u8 *move_data)
{
	int old_y_menu, old_x_menu;
	u32 ret_key;
	
	old_x_menu = move->x_menu;
	old_y_menu = move->y_menu;
	
	if(sys.trg & PAD_KEY_UP){
		move->y_menu--;
		if(move->y_menu < 0){
			move->y_menu = 0;//y_menu_num - 1;
		}
		if(move_data != NULL){
			while(move_data[x_menu_num * move->y_menu + move->x_menu] == 0xff){
				move->y_menu--;
				if(move->y_menu < 0){
					move->y_menu = old_y_menu;
					break;
				}
			}
		}
		ret_key = PAD_KEY_UP;
	}
	else if(sys.trg & PAD_KEY_DOWN){
		move->y_menu++;
		if(move->y_menu >= y_menu_num){
			move->y_menu = y_menu_num - 1;//0;
		}
		if(move_data != NULL){
			while(move_data[x_menu_num * move->y_menu + move->x_menu] == 0xff){
				move->y_menu++;
				if(move->y_menu >= y_menu_num){
					move->y_menu = old_y_menu;
					break;
				}
			}
		}
		ret_key = PAD_KEY_DOWN;
	}
	else if(sys.trg & PAD_KEY_LEFT){
		move->x_menu--;
		if(move->x_menu < 0){
			move->x_menu = 0;//x_menu_num - 1;
		}
		if(move_data != NULL){
			while(move_data[x_menu_num * move->y_menu + move->x_menu] == 0xff){
				move->x_menu--;
				if(move->x_menu < 0){
					move->x_menu = old_x_menu;
					break;
				}
			}
		}
		ret_key = PAD_KEY_LEFT;
	}
	else if(sys.trg & PAD_KEY_RIGHT){
		move->x_menu++;
		if(move->x_menu >= x_menu_num){
			move->x_menu = x_menu_num-1;//0;
		}
		if(move_data != NULL){
			while(move_data[x_menu_num * move->y_menu + move->x_menu] == 0xff){
				move->x_menu++;
				if(move->x_menu >= x_menu_num){
					move->x_menu = old_x_menu;
					break;
				}
			}
		}
		ret_key = PAD_KEY_RIGHT;
	}
	else if(sys.trg & PAD_BUTTON_DECIDE){
		ret_key = PAD_BUTTON_DECIDE;
	}
	else if(sys.trg & PAD_BUTTON_CANCEL){
		ret_key = PAD_BUTTON_CANCEL;
	}
	else{
		return 0;
	}
	
	if(move_data != NULL){
		int old_index, new_index;

		old_index = move_data[x_menu_num * old_y_menu + old_x_menu];
		new_index = move_data[x_menu_num * move->y_menu + move->x_menu];
		
		//カーソル移動後位置確認
		if(old_index == new_index){
			//移動後のindexが変わらないのであればカーソル座標の移動はしない
			move->x_menu = old_x_menu;
			move->y_menu = old_y_menu;
		}
	}

	if(move->x_menu != old_x_menu || move->y_menu != old_y_menu){
		Snd_SePlay(ASE_CCURSOR_MOVE_SE);
	}
	else{
		if(ret_key & (PAD_KEY_UP|PAD_KEY_DOWN|PAD_KEY_LEFT|PAD_KEY_RIGHT)){
			return 0;
		}
	}

	return ret_key;
}



//==============================================================================
//
//	Vブランク処理
//
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   CGR転送を行う
 *
 * @param   tcb			TCBへのポインタ
 * @param   work		BIシステムワークへのポインタ
 */
//--------------------------------------------------------------
static void VWait_CgrTrans(TCB_PTR tcb, void *work)
{
	ACI_PARAM_PTR aci = work;

	GF_BGL_LoadCharacter(aci->sys->bgl, GF_BGL_FRAME0_S, aci->cgr_char_data->pRawData, 
		ACI_BG_CGR_SIZE, 0);
	sys_FreeMemoryEz(aci->cgr_arc_data);
	aci->cgr_arc_data = NULL;
	
	TCB_Delete(tcb);
}

//--------------------------------------------------------------
/**
 * @brief   各フレームのVisible設定を行う
 *
 * @param   tcb			TCBへのポインタ
 * @param   work		BIシステムワークへのポインタ
 */
//--------------------------------------------------------------
static void VWait_FrameVisibleUpdate(TCB_PTR tcb, void *work)
{
	ACI_PARAM_PTR aci = work;
	const BG_MAKE_DATA *bmd;
	int i;

	bmd = &BgMakeData[aci->makedata_no];
	
	//各BG面の表示・非表示設定
	for(i = 0; i < ACI_BG_NUM; i++){
		if(bmd->scr_id[i] == NONE_ID){
			GF_BGL_VisibleSet(GF_BGL_FRAME0_S + i, VISIBLE_OFF);
		}
		else{
			GF_BGL_VisibleSet(GF_BGL_FRAME0_S + i, VISIBLE_ON);
		}
	}
	
	TCB_Delete(tcb);
}

//--------------------------------------------------------------
/**
 * @brief   背景以外のフレーム全てを非表示にする
 *
 * @param   tcb		TCBへのポインタ
 * @param   work	BIシステムワークへのポインタ
 *
 * @retval  
 *
 *
 */
//--------------------------------------------------------------
static void VWait_BackScrnOnlyVisible(TCB_PTR tcb, void *work)
{
	ACI_PARAM_PTR aci = work;

	Sub_BackScrnOnlyVisible();
	TCB_Delete(tcb);
}

