//==============================================================================
/**
 * @file	dance_input.c
 * @brief	演技力部門入力画面処理
 * @author	matsuda
 * @date	2005.12.02(金)
 */
//==============================================================================
#include "common.h"
#include "contest/contest.h"
#include "dance.h"
#include "dance_tcb_pri.h"
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

#include "dance_tool.h"
#include "con_tool.h"
#include "dance_id.h"
#include "dance_input.h"
#include "battle/wazatype_panel.h"
#include "gflib/touchpanel.h"
#include "contype_icon.h"
#include "poketool/waza_tool.h"
#include "aci_tool.h"

#include "system/msgdata_util.h"
#include "system/wordset.h"

#include "msgdata/msg_cmsg_dance.h"
#include "system/fontoam.h"



//==============================================================================
//	定数定義
//==============================================================================
///１＝フォントOBJの処理が重いので最初に生成して、以後、バニッシュのON,OFF操作で行う
///０＝今まで通り必要な時に生成して、必要なくなったら削除する
#define FONTOBJ_VANISH		(1)


//--------------------------------------------------------------
//	ローカルTCBプライオリティ
//--------------------------------------------------------------
#define VWAIT_TCBPRI_CGR_REQ			(8)
#define VWAIT_TCBPRI_FRAMEVISIBLE		(10)
#define VWAIT_TCBPRI_BACKSCRN_VISIBLE	(10)
#define VWAIT_TCBPRI_CGRPARAM_TRANS		(20)



//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///BG指定なし
#define NONE_ID			(0xffff)

///BG使用面数
#define DCI_BG_NUM		(4)

///BGキャラクタのVRAM使用サイズ
#define BG_VRAM_SIZE	(0x8000 - (0x800 * DCI_BG_NUM))

///標準パレットデータ使用本数
#define BASE_PLTT_NUM	(16)

///makedata_no初期値(未使用状態)
#define MAKEDATA_NO_INIT	(-1)

///コンテスト入力画面で使用出来るBGのCGRサイズ
#define DCI_BG_CGR_SIZE			(0x6000)

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

///ボタンカラー開始位置(カラー単位)
#define BUTTON_COLOR_START		(0*16)
///ボタンカラーの数(カラー単位)
#define BUTTON_COLOR_NUM		(16 * 4)

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///キャラクタ展開領域ID
enum{
	EXPAND_CHAR_WALL,
	EXPAND_CHAR_COMMAND,
	
	EXPAND_CHAR_BUTTON_ANM,
	
	EXPAND_CHAR_MAX,
};

///パレット展開領域ID
enum{
	EXPAND_PALETTE_WALL,
	EXPAND_PALETTE_COMMAND,
	
	EXPAND_PALETTE_MAX,
};

///スクリーン展開領域ID
enum{
	EXPAND_SCREEN_WALL_PANEL,
	EXPAND_SCREEN_WALL_BF,
	EXPAND_SCREEN_COMMAND_PANEL,
	EXPAND_SCREEN_BACKGROUND,
	
	EXPAND_SCREEN_MAX,
};

//--------------------------------------------------------------
//	スクリーンスクロール値
//--------------------------------------------------------------
///TYPE_AのBG表示時にタッチパネルが押された時にY方向にスクロールさせる値(エフェクト面)
#define SCRN_SCROLL_A_EFF_Y				(16)//(-2)
///TYPE_AのBG表示時にタッチパネルが押された時にY方向にスクロールさせる値(エフェクト面)
#define SCRN_SCROLL_BACK_A_EFF_Y		(-4)//(1)
///SCRN_SCROLL_BACK_A_EFF_Yの後に定位置に戻すまでのスクロール値
#define SCRN_SCROLL_RESET_A_EFF_Y		(-(SCRN_SCROLL_A_EFF_Y + SCRN_SCROLL_BACK_A_EFF_Y))

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
	FA_NO_CONRANK = 0,
	FA_NO_CONTYPE,
	
	//COMMAND
#if FONTOBJ_VANISH
	FA_NO_FORWARD,
#else
	FA_NO_FORWARD = 0,			///<まえ
#endif
	FA_NO_BACK,					///<うしろ
	FA_NO_LEFT,					///<ひだり
	FA_NO_RIGHT,				///<みぎ
	
	
	FA_NO_MAX = FA_NO_RIGHT + 1,		///<フォントOBJを一度に出せる最大数
};

///フォントOBJの表示座標
enum{
	//-- 画面COMMAND --//
	FA_POS_FORWARD_X = 0x10 * 8,	//Xは中心座標
	FA_POS_FORWARD_Y = 0x3 * 8,
	FA_POS_BACK_X = 0x10 * 8,	//Xは中心座標
	FA_POS_BACK_Y = 0xf * 8,
	FA_POS_LEFT_X = 0x6 * 8,	//Xは中心座標
	FA_POS_LEFT_Y = 0x8 * 8,
	FA_POS_RIGHT_X = 0x1a * 8,	//Xは中心座標
	FA_POS_RIGHT_Y = 0x8 * 8,
};

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
	PALOFS_COMMAND = 0,
	PALOFS_CONRANK = 0,
};

#define MSGCOLOR_COMMAND		(GF_PRINTCOLOR_MAKE(1, 1, 0xb))
#define MSGCOLOR_CONRANK		(GF_PRINTCOLOR_MAKE(1, 2, 0))	//FONT_SYSTEMなので背景抜き色指定

//--------------------------------------------------------------
//	エフェクトTCB
//--------------------------------------------------------------
///パネルをタッチした後、エフェクトで待つフレーム数
#define SCRN_TOUCH_WAIT	(2)
///パネルをタッチした後、エフェクトで待つフレーム数
#define SCRN_TOUCH_ANM_WAIT	(2)

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///ボタンキャラ転送用のサイズX(キャラクタ単位)
#define BUTTON_CGR_SIZE_X		(6)
///ボタンキャラ転送用のサイズY(キャラクタ単位)
#define BUTTON_CGR_SIZE_Y		(12)
///ボタンキャラ転送用グラフィックのアニメパターン数
#define BUTTON_ANM_NUM	(3)

///paracgr構造体で使用するアクターポインタの数
#define PARACGR_CAP_MAX			(3)


//==============================================================================
//	構造体定義
//==============================================================================
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

///エフェクトTCB用のワーク
typedef struct{
	s16 seq;
	s16 wait;
	union{
		struct{		//CGR転送用(汎用)
			CGR_TRANS_PARAM *ctp;
			const CGR_TRANS_RECTDATA *ctp_rd_ptr[BUTTON_ANM_NUM];
			CATS_ACT_PTR cap[PARACGR_CAP_MAX];	///<一緒にスクロールさせるアクターへのポインタ
			u32 transcgr_id[BUTTON_ANM_NUM];
			int tp_ret;
			u16 arc_id;
			u16 char_x_len;
			u8 fa_no;						///<対象フォントOBJアクターワークの添え字
		}paracgr;
	};
}DCI_EFFECT_WORK;

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

///コンテスト入力画面制御ワーク
typedef struct _DCI_PARAM{
	CONTEST_SYSTEM *consys;
	DANCE_SYSTEM_PARAM *sys;
	void *scene_work;	///<シーン毎に異なる必要となるデータ類へのポインタ
	TCB_PTR effect_tcb;	///<エフェクト動作TCBへのポインタ
	EFFBG_WRITE_PARAM ewp;	///<エフェクトBG書き換えパラメータ

	//フォントOAM
	FONTOAM_SYS_PTR fontoam_sys;	///<フォントシステムへのポインタ
	FONT_ACTOR font_actor[FA_NO_MAX];	///<フォントアクターワーク
	
	u16 cgr_trans_req;		///<Vブランク転送CGRリクエスト
	s8 makedata_no;		///<現在使用しているBgMakeDataの番号
	
	DCI_EFFECT_WORK effect_work;	///<エフェクトTCB用ワーク
	
	u8 *expand_char[EXPAND_CHAR_MAX];
	u16 *expand_screen[EXPAND_SCREEN_MAX];
	u16 *expand_palette[EXPAND_PALETTE_MAX];
}DCI_PARAM;

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
		u16 scr_id[DCI_BG_NUM];		///<使用スクリーンのアーカイブID
	};
	union{
		struct{
			u16 pri0;		///<BG0面のプライオリティ
			u16 pri1;		///<BG1面のプライオリティ
			u16 pri2;
			u16 pri3;
		};
		u16 pri[DCI_BG_NUM];		///<BGのプライオリティ
	};
	
	//タッチパネル
	const RECT_HIT_TBL *tpd;	///<使用するタッチパネルデータへのポインタ
	const int *tpd_ret;			///<タッチパネルの結果
	
	//関数ポインタ
	void (*callback_bg)(DCI_PARAM_PTR, int, int);	///<BGCreate時に呼び出す関数
	int (*callback_tp)(DCI_PARAM_PTR, int);			///<タッチパネル反応時に呼び出す関数
}BG_MAKE_DATA;


//==============================================================================
//	プロトタイプ宣言
//==============================================================================
static void Sub_ScrnErase(const REWRITE_SCRN_RECT rsr[], int rsr_num, GF_BGL_INI *bgl, 
	int frame_no, u16 clear_code);
static CGR_TRANS_PARAM * Sub_CgrTransParamSet(DCI_PARAM_PTR dci, int frame_no, u16 arc_id, 
	u32 cgr_id, const CGR_TRANS_RECTDATA *rd, int char_len_x);
static CGR_TRANS_PARAM * Sub_CgrTransTaskSet(DCI_PARAM_PTR dci, int frame_no, u16 arc_id, 
	u32 cgr_id, const CGR_TRANS_RECTDATA *rd, int char_len_x);
static void * DINPUT_WorkInit(void);
static void BGCallback_CommandSelect(DCI_PARAM_PTR dci, int select_bg, int force_put);
static int TPCallback_CommandSelect(DCI_PARAM_PTR dci, int tp_ret);
static BOOL Sub_CgrTransEndCheck(CGR_TRANS_PARAM *ctp);
static void Sub_CgrTransNowCopy(DCI_PARAM_PTR dci, int frame_no, u16 arc_id, u32 cgr_id, 
	const CGR_TRANS_RECTDATA *rd, int char_len_x);
static void Sub_CgrParamTrans(CGR_TRANS_PARAM *ctp);
static void Sub_BackScrnOnlyVisible(void);
static void Sub_TouchEndDelete(DCI_PARAM_PTR dci);
static void Sub_SceneOBJDelete(DCI_PARAM_PTR dci, int sys_exit);
static void EffectTCB_Add(TCB_FUNC func, DCI_PARAM_PTR dci);
static void EffectTCB_Delete(DCI_PARAM_PTR dci);
static void Effect_ButtonDown(TCB_PTR tcb, void *work);
static void VWait_FrameVisibleUpdate(TCB_PTR tcb, void *work);
static void VWait_CgrRequest(TCB_PTR tcb, void *work);
static void VWait_BackScrnOnlyVisible(TCB_PTR tcb, void *work);
static void VWait_CgrParamTrans(TCB_PTR tcb, void *work);
static void CommandFontObjCreate(DCI_PARAM_PTR dci);
static void Sub_FontOamCreate(DCI_PARAM_PTR dci, FONT_ACTOR *font_actor, const STRBUF *str, 
	FONT_TYPE font_type, GF_PRINTCOLOR color, int pal_offset, int pal_id, 
	int x, int y, int pos_center);
static void Sub_FontOamDeleteAll(DCI_PARAM_PTR dci);
static void Sub_FontOamVanishAll(DCI_PARAM_PTR dci, int vanish);
static void WallFontObjCreate(DCI_PARAM_PTR dci);
static void BGCallback_Wall(DCI_PARAM_PTR dci, int select_bg, int force_put);
static void DINPUT_DefaultExpandBGSet(DCI_PARAM_PTR dci);
static void DINPUT_DefaultExpandBGFree(DCI_PARAM_PTR dci);




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
static const RECT_HIT_TBL CommandSelectTouchData[] = {
	//TOP BOTTOM LEFT RIGHT
	{0*8, 10*8, 11*8, 0x15*8},		//DANCE_TP_JUMP
	{12*8, 0x16*8, 11*8, 0x15*8},	//DANCE_TP_ADVANCE
	{5*8, 15*8, 1*8, 11*8},		//DANCE_TP_LEFT
	{5*8, 15*8, 0x15*8, 0x1f*8},	//DANCE_TP_RIGHT
	{ RECT_HIT_END, 0, 0, 0 }
};
///技選択タッチパネルのタッチ結果返事
static const int CommandSelectTouchRet[NELEMS(CommandSelectTouchData) - 1] = {
	DANCE_TP_JUMP,
	DANCE_TP_ADVANCE,
	DANCE_TP_LEFT,
	DANCE_TP_RIGHT,
};
///技選択のタッチパネルINDEX(CommandSelectTouchRetの順番)
enum{
	DANCE_INDEX_JUMP,
	DANCE_INDEX_ADVANCE,
	DANCE_INDEX_LEFT,
	DANCE_INDEX_RIGHT,
};


//==============================================================================
//	
//==============================================================================
///BG作成データ(※ここの並びを追加、変更したらDINPUT_TYPE_???の定義も変更すること！！)
static const BG_MAKE_DATA BgMakeData[] = {
	{//WALL
		EXPAND_CHAR_WALL,	//CON_SUB_NCGR_BIN,
		EXPAND_PALETTE_WALL,	//CONTEST_SUB_NCLR,
		{
			EXPAND_SCREEN_WALL_PANEL,	//CON_TIT_NSCR_BIN,		//パネル
			NONE_ID,		//黒枠
			EXPAND_SCREEN_WALL_BF,	//CON_SUB_BG_NSCR_BIN,		//背景
			NONE_ID,							//黒枠スライド用
		},
		{2, 1, 3, 0},
		NULL,				//タッチパネルデータ
		NULL,				//タッチパネル結果
		BGCallback_Wall,				//BG作成時のコールバック関数
		NULL,				//タッチパネル反応時のコールバック関数
	},
	{//COMMAND
		EXPAND_CHAR_COMMAND,	//CON_DANCE_BUT_NCGR_BIN,
		EXPAND_PALETTE_COMMAND,	//CONTEST_DANCE_SUB_BG_NCLR,
		{
			EXPAND_SCREEN_COMMAND_PANEL,	//CON_DANCE_BUT_NSCR_BIN,		//パネル
			NONE_ID,		//黒枠
			EXPAND_SCREEN_BACKGROUND,		//背景
			NONE_ID,							//黒枠スライド用
		},
		{2, 1, 3, 0},
		CommandSelectTouchData,				//タッチパネルデータ
		CommandSelectTouchRet,					//タッチパネル結果
		BGCallback_CommandSelect,				//BG作成時のコールバック関数
		TPCallback_CommandSelect,				//タッチパネル反応時のコールバック関数
	},
};



//==============================================================================
//
//	
//
//==============================================================================
///コマンド選択パネルを押した時のCGRアニメ転送範囲
static const CGR_TRANS_RECTDATA CommandSelectCgrTransRect[][WAZA_TEMOTI_MAX] = {
	{
		{0, 0, 12, 0, BUTTON_CGR_SIZE_X, BUTTON_CGR_SIZE_Y},		//DANCE_TP_JUMP
		{18, 0, 12, 0, BUTTON_CGR_SIZE_X, BUTTON_CGR_SIZE_Y},		//DANCE_TP_ADVANCE
		{6, 0, 12, 0, BUTTON_CGR_SIZE_X, BUTTON_CGR_SIZE_Y},		//DANCE_TP_LEFT
		{12, 0, 12, 0, BUTTON_CGR_SIZE_X, BUTTON_CGR_SIZE_Y},		//DANCE_TP_RIGHT
	},
	{
		{0, 0, 6, 0, BUTTON_CGR_SIZE_X, BUTTON_CGR_SIZE_Y},			//DANCE_TP_JUMP
		{18, 0, 6, 0, BUTTON_CGR_SIZE_X, BUTTON_CGR_SIZE_Y},		//DANCE_TP_ADVANCE
		{6, 0, 6, 0, BUTTON_CGR_SIZE_X, BUTTON_CGR_SIZE_Y},			//DANCE_TP_LEFT
		{12, 0, 6, 0, BUTTON_CGR_SIZE_X, BUTTON_CGR_SIZE_Y},		//DANCE_TP_RIGHT
	},
	{
		{0, 0, 0, 0, BUTTON_CGR_SIZE_X, BUTTON_CGR_SIZE_Y},			//DANCE_TP_JUMP
		{18, 0, 0, 0, BUTTON_CGR_SIZE_X, BUTTON_CGR_SIZE_Y},		//DANCE_TP_ADVANCE
		{6, 0, 0, 0, BUTTON_CGR_SIZE_X, BUTTON_CGR_SIZE_Y},			//DANCE_TP_LEFT
		{12, 0, 0, 0, BUTTON_CGR_SIZE_X, BUTTON_CGR_SIZE_Y},		//DANCE_TP_RIGHT
	},
};


//==============================================================================
//
//	
//
//==============================================================================

//--------------------------------------------------------------
/**
 * @brief   DIシステムワークの確保と初期化
 *
 * @retval  確保したDIシステムワークのポインタ
 */
//--------------------------------------------------------------
static void * DINPUT_WorkInit(void)
{
	DCI_PARAM *dci;

	dci = sys_AllocMemory(HEAPID_DANCE, sizeof(DCI_PARAM));
	MI_CpuClear8(dci, sizeof(DCI_PARAM));
	
	dci->makedata_no = MAKEDATA_NO_INIT;
	
	return dci;
}

//--------------------------------------------------------------
/**
 * @brief   BG構成を標準フレーム構成で設定する
 * @param   bgl		BGLデータ
 */
//--------------------------------------------------------------
void DINPUT_DefaultFrameSet(GF_BGL_INI *bgl)
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
void DINPUT_FrameExit(GF_BGL_INI *bgl)
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
void * DINPUT_SystemInit(CONTEST_SYSTEM *consys, DANCE_SYSTEM_PARAM *sys)
{
	DCI_PARAM *dci;
	
	//ワーク確保
	dci = DINPUT_WorkInit();
	dci->consys = consys;
	dci->sys = sys;
	
	//フレーム構成設定	ここでやるかは微妙？
//	DINPUT_DefaultFrameSet(bgl);

	//フォントOAMシステム作成
	dci->fontoam_sys = FONTOAM_SysInit(FA_NO_MAX, HEAPID_DANCE);

	//BG展開
	DINPUT_DefaultExpandBGSet(dci);

	return dci;
}

//--------------------------------------------------------------
/**
 * @brief   コンテスト入力画面のシステムを解放する
 * @param   dci		DIシステムワークへのポインタ
 */
//--------------------------------------------------------------
void DINPUT_SystemFree(DCI_PARAM_PTR dci)
{
	DINPUT_DefaultExpandBGFree(dci);

	Sub_SceneOBJDelete(dci, TRUE);
	FONTOAM_SysDelete(dci->fontoam_sys);
	sys_FreeMemoryEz(dci);
}

//--------------------------------------------------------------
/**
 * @brief   コンテスト入力画面で最初にセットしておく常駐アクターの登録を行う
 * @param   dci		DIシステムワークへのポインタ
 */
//--------------------------------------------------------------
void DINPUT_DefaultActorSet(DCI_PARAM_PTR dci)
{
#if FONTOBJ_VANISH
	WallFontObjCreate(dci);
	CommandFontObjCreate(dci);
	Sub_FontOamVanishAll(dci, FALSE);
#endif
}

//--------------------------------------------------------------
/**
 * @brief   入力画面で使用するBG関連データを全て展開領域にロードしておく
 * @param   dci		DIシステムワークへのポインタ
 */
//--------------------------------------------------------------
static void DINPUT_DefaultExpandBGSet(DCI_PARAM_PTR dci)
{
	NNSG2dCharacterData *char_data;
	NNSG2dScreenData *scrn_data;
	void *arc_data;
	
	dci->expand_char[EXPAND_CHAR_WALL] = sys_AllocMemory(HEAPID_DANCE, BG_VRAM_SIZE);
	dci->expand_char[EXPAND_CHAR_COMMAND] = sys_AllocMemory(HEAPID_DANCE, BG_VRAM_SIZE);
	dci->expand_char[EXPAND_CHAR_BUTTON_ANM] = sys_AllocMemory(HEAPID_DANCE, 
		BUTTON_CGR_SIZE_X * BUTTON_CGR_SIZE_Y * 0x20 * BUTTON_ANM_NUM);

	dci->expand_screen[EXPAND_SCREEN_WALL_PANEL] = sys_AllocMemory(HEAPID_DANCE, 0x800);
	dci->expand_screen[EXPAND_SCREEN_WALL_BF] = sys_AllocMemory(HEAPID_DANCE, 0x800);
	dci->expand_screen[EXPAND_SCREEN_COMMAND_PANEL] = sys_AllocMemory(HEAPID_DANCE, 0x800);
	dci->expand_screen[EXPAND_SCREEN_BACKGROUND] = sys_AllocMemory(HEAPID_DANCE, 0x800);
	
	dci->expand_palette[EXPAND_PALETTE_WALL] = sys_AllocMemory(HEAPID_DANCE, 0x200);
	dci->expand_palette[EXPAND_PALETTE_COMMAND] = sys_AllocMemory(HEAPID_DANCE, 0x200);
	
	//-- キャラクタ --//
	arc_data = ArcUtil_CharDataGet(ARC_CONTEST_BG, CON_SUB_NCGR_BIN, 1, &char_data, HEAPID_DANCE);
	MI_CpuCopy32(char_data->pRawData, dci->expand_char[EXPAND_CHAR_WALL], BG_VRAM_SIZE);
	sys_FreeMemoryEz(arc_data);

	arc_data = ArcUtil_CharDataGet(ARC_CONTEST_BG, CON_DANCE_BUT_NCGR_BIN, 1, 
		&char_data, HEAPID_DANCE);
	MI_CpuCopy32(char_data->pRawData, dci->expand_char[EXPAND_CHAR_COMMAND], BG_VRAM_SIZE);
	sys_FreeMemoryEz(arc_data);

	arc_data = ArcUtil_CharDataGet(ARC_CONTEST_BG, CON_DANCE_BUT_ANIM_NCGR_BIN, 1, 
		&char_data, HEAPID_DANCE);
	MI_CpuCopy32(char_data->pRawData, dci->expand_char[EXPAND_CHAR_BUTTON_ANM], 
		BUTTON_CGR_SIZE_X * BUTTON_CGR_SIZE_Y * 0x20 * BUTTON_ANM_NUM);
	sys_FreeMemoryEz(arc_data);
	
	//-- スクリーン --//
	arc_data = ArcUtil_ScrnDataGet(ARC_CONTEST_BG, CON_TIT_NSCR_BIN, 1, &scrn_data, HEAPID_DANCE);
	MI_CpuCopy32(scrn_data->rawData, dci->expand_screen[EXPAND_SCREEN_WALL_PANEL], 0x800);
	sys_FreeMemoryEz(arc_data);

	arc_data = ArcUtil_ScrnDataGet(ARC_CONTEST_BG, CON_SUB_BG_NSCR_BIN, 1, 
		&scrn_data, HEAPID_DANCE);
	MI_CpuCopy32(scrn_data->rawData, dci->expand_screen[EXPAND_SCREEN_WALL_BF], 0x800);
	sys_FreeMemoryEz(arc_data);
	
	arc_data = ArcUtil_ScrnDataGet(ARC_CONTEST_BG, CON_DANCE_BUT_NSCR_BIN, 1, 
		&scrn_data, HEAPID_DANCE);
	MI_CpuCopy32(scrn_data->rawData, dci->expand_screen[EXPAND_SCREEN_COMMAND_PANEL], 0x800);
	sys_FreeMemoryEz(arc_data);

	arc_data = ArcUtil_ScrnDataGet(ARC_CONTEST_BG, CON_DANCE_SUB_NSCR_BIN, 1, 
		&scrn_data, HEAPID_DANCE);
	MI_CpuCopy32(scrn_data->rawData, dci->expand_screen[EXPAND_SCREEN_BACKGROUND], 0x800);
	sys_FreeMemoryEz(arc_data);

	//-- パレット --//
	PaletteWorkSetEx_ArcWork(ARC_CONTEST_BG, CONTEST_SUB_NCLR, HEAPID_DANCE, 0x200, 0, 
		dci->expand_palette[EXPAND_PALETTE_WALL]);
	//プレート部分だけ上書き
	PaletteWorkSetEx_ArcWork(ARC_CONTEST_BG, CONTEST_SUBTIT_NCLR, HEAPID_DANCE, 32, 
		16 * dci->sys->c_game->type, 
		&dci->expand_palette[EXPAND_PALETTE_WALL][PLATE_PALNO * 16]);

	PaletteWorkSetEx_ArcWork(ARC_CONTEST_BG, CONTEST_DANCE_SUB_BG_NCLR, HEAPID_DANCE, 0x200, 0, 
		dci->expand_palette[EXPAND_PALETTE_COMMAND]);
}

//--------------------------------------------------------------
/**
 * @brief   ロードしておいたBG関係データを全て解放する
 * @param   dci		DIシステムワークへのポインタ
 */
//--------------------------------------------------------------
static void DINPUT_DefaultExpandBGFree(DCI_PARAM_PTR dci)
{
	int i;
	
	for(i = 0; i < EXPAND_CHAR_MAX; i++){
		sys_FreeMemoryEz(dci->expand_char[i]);
	}
	for(i = 0; i < EXPAND_SCREEN_MAX; i++){
		sys_FreeMemoryEz(dci->expand_screen[i]);
	}
	for(i = 0; i < EXPAND_PALETTE_MAX; i++){
		sys_FreeMemoryEz(dci->expand_palette[i]);
	}
}

//--------------------------------------------------------------
/**
 * @brief   指定タイプのBG画面を形成する
 *
 * @param   dci				DIシステムワークへのポインタ
 * @param   select_bg		表示BGタイプ(DINPUT_TYPE_???)
 * @param   force_put		TRUE:強制転送、FALSE:既に同じデータが転送されているなら再転送はしない
 * @param   work			シーン毎に異なる必要なデータへのポインタ
 */
//--------------------------------------------------------------
void DINPUT_CreateBG(DCI_PARAM_PTR dci, int select_bg, int force_put, void *scene_work)
{
	const BG_MAKE_DATA *bmd, *old_bmd;
	int i;
	GF_BGL_INI *bgl;
	CATS_SYS_PTR csp;
	CATS_RES_PTR crp;
	
	dci->scene_work = scene_work;
	bgl = dci->sys->bgl;
	csp = dci->sys->csp;
	crp = dci->sys->crp;
	
	if(dci->makedata_no == MAKEDATA_NO_INIT){
		force_put = TRUE;
		old_bmd = NULL;
	}
	else{
		old_bmd = &BgMakeData[dci->makedata_no];
	}
	bmd = &BgMakeData[select_bg];

	//背景以外は全て非表示
//	Sub_BackScrnOnlyVisible();
	
	//各BG面のBGプライオリティ更新
	{
		for(i = 0; i < DCI_BG_NUM; i++){
			GF_BGL_PrioritySet(GF_BGL_FRAME0_S + i, bmd->pri[i]);
		}
	}
	
	//CGR
	if(1){	//CGR転送アニメを行うならキャラIDが同じでも必ず転送しておかないとアニメが戻らない
//	if(bmd->cgr_id != NONE_ID && (force_put == TRUE || bmd->cgr_id != old_bmd->cgr_id)){
	//	ArcUtil_BgCharSet(ARC_CONTEST_BG, bmd->cgr_id, bgl, GF_BGL_FRAME0_S, 
	//		0, DCI_BG_CGR_SIZE, 1, HEAPID_DANCE);
		dci->cgr_trans_req = bmd->cgr_id;
		VWaitTCB_Add(VWait_CgrRequest, dci, VWAIT_TCBPRI_CGR_REQ);
	}
	//PALETTE
	if(bmd->pal_id != NONE_ID && (force_put == TRUE || bmd->pal_id != old_bmd->pal_id)){
	//	PaletteWorkSet_Arc(dci->sys->pfd, ARC_CONTEST_BG, bmd->pal_id, HEAPID_DANCE, 
	//		FADE_SUB_BG, 0, 0);
		PaletteWorkSet(dci->sys->pfd, dci->expand_palette[bmd->pal_id], FADE_SUB_BG, 0, 0x200);
	}
	//SCREEN
	for(i = 0; i < DCI_BG_NUM; i++){
		if(bmd->scr_id[i] != NONE_ID 
				&& (force_put == TRUE || bmd->scr_id[i] != old_bmd->scr_id[i])){
		//	ArcUtil_ScrnSet(ARC_CONTEST_BG, bmd->scr_id[i], bgl, 
		//		GF_BGL_FRAME0_S + i, 0, 0, 1, HEAPID_DANCE);
			GF_BGL_ScreenBufSet(bgl, GF_BGL_FRAME0_S + i, dci->expand_screen[bmd->scr_id[i]], 
				0x800);
			GF_BGL_LoadScreenV_Req(bgl, GF_BGL_FRAME0_S + i);
		}
	}
	
	dci->makedata_no = select_bg;

//	G2S_SetBlendAlpha(BLD_PLANE_1, BLD_PLANE_2, BLD_ALPHA_1, BLD_ALPHA_2);

	Sub_SceneOBJDelete(dci, FALSE);
	//コールバック関数呼び出し
	if(bmd->callback_bg != NULL){
		bmd->callback_bg(dci, select_bg, force_put);
	}

	VWaitTCB_Add(VWait_FrameVisibleUpdate, dci, VWAIT_TCBPRI_FRAMEVISIBLE);
}

//--------------------------------------------------------------
/**
 * @brief   タッチパネル状態を調べる
 * @param   dci		DIシステムワークへのポインタ
 * @retval  結果(当たりなしの場合はRECT_HIT_NONE)
 */
//--------------------------------------------------------------
int DINPUT_TouchCheck(DCI_PARAM_PTR dci)
{
	int tp_ret, hit, ret;
	const BG_MAKE_DATA *bmd;
	
	GF_ASSERT(dci->makedata_no != MAKEDATA_NO_INIT);
	
	bmd = &BgMakeData[dci->makedata_no];
	if(bmd->tpd == NULL){
		return RECT_HIT_NONE;
	}
	
	GF_ASSERT(bmd->tpd_ret != NULL);
	
	hit = GF_TP_RectHitTrg(bmd->tpd);
	if(hit == RECT_HIT_NONE){
		if(bmd->tpd_ret == CommandSelectTouchRet){
			//キー入力チェック
			if(sys.trg & (PAD_BUTTON_A | PAD_KEY_RIGHT)){
				hit = DANCE_INDEX_RIGHT;
			}
			else if(sys.trg & (PAD_BUTTON_B | PAD_KEY_DOWN)){
				hit = DANCE_INDEX_ADVANCE;
			}
			else if(sys.trg & (PAD_BUTTON_X | PAD_KEY_UP)){
				hit = DANCE_INDEX_JUMP;
			}
			else if(sys.trg & (PAD_BUTTON_Y | PAD_KEY_LEFT)){
				hit = DANCE_INDEX_LEFT;
			}
		}
	}
	
	if(hit == RECT_HIT_NONE){
		tp_ret = RECT_HIT_NONE;
	}
	else{
		tp_ret = bmd->tpd_ret[hit];
	}
	
	//コールバック関数呼び出し
	if(bmd->callback_tp != NULL){
		tp_ret = bmd->callback_tp(dci, tp_ret);
	}
	
	return tp_ret;
}

//--------------------------------------------------------------
/**
 * @brief   エフェクトTCBが終了しているかチェック
 * @param   dci		DIシステムワークへのポインタ
 * @retval  TRUE:終了している。　FALSE:終了していない
 */
//--------------------------------------------------------------
BOOL DINPUT_EffectEndCheck(DCI_PARAM_PTR dci)
{
	if(dci->effect_tcb == NULL){
		return TRUE;
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   現在使用しているBgMakeDataの番号を取得する
 * @param   dci		DIシステムワークへのポインタ
 */
//--------------------------------------------------------------
int DINPUT_MakeDataNoGet(DCI_PARAM_PTR dci)
{
	return dci->makedata_no;
}


//==============================================================================
//
//	BG作成時に呼ばれるコールバック関数
//
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   DINPUT_TYPE_WALLのBGCreate時に呼ばれるコールバック関数
 *
 * @param   dci				DIシステムワークへのポインタ
 * @param   select_bg		表示BGタイプ(DINPUT_TYPE_???)
 * @param   force_put		TRUE:強制転送、FALSE:既に同じデータが転送されているなら再転送はしない
 */
//--------------------------------------------------------------
static void BGCallback_Wall(DCI_PARAM_PTR dci, int select_bg, int force_put)
{
#if FONTOBJ_VANISH
	Sub_FontOamVanishAll(dci, TRUE);
#else
	WallFontObjCreate(dci);
#endif
}

//--------------------------------------------------------------
/**
 * @brief   DINPUT_TYPE_WALLで使用するフォントOBJを生成する
 * @param   dci		DIシステムワークへのポインタ
 */
//--------------------------------------------------------------
static void WallFontObjCreate(DCI_PARAM_PTR dci)
{
	STRBUF *rank_src, *type_src;
	u32 rank_id, type_id;
	MSGDATA_MANAGER *man;
	
	//演技力部門のメッセージファイルに入っているのでここで一時的にマネージャー作成
	man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_cmsg_acting_dat, HEAPID_DANCE);

	rank_id = ConTool_GetRankMsgID(dci->sys->c_game->rank, dci->sys->c_game->mode, 
		dci->consys->sio_flag);
	type_id = ConTool_GetTypeMsgID(dci->sys->c_game->type, dci->sys->c_game->mode);
	
	rank_src = MSGMAN_AllocString(man, rank_id);
	type_src = MSGMAN_AllocString(man, type_id);
	
	Sub_FontOamCreate(dci, &dci->font_actor[FA_NO_CONRANK], 
		rank_src, FONT_SYSTEM, 
		MSGCOLOR_CONRANK, PALOFS_CONRANK,
		D_PLTTID_SUB_FONTACT, FONT_CONRANK_POS_X, FONT_CONRANK_POS_Y, FONTOAM_CENTER);
	Sub_FontOamCreate(dci, &dci->font_actor[FA_NO_CONTYPE], 
		type_src, FONT_SYSTEM, 
		MSGCOLOR_CONRANK, PALOFS_CONRANK,
		D_PLTTID_SUB_FONTACT, FONT_CONTYPE_POS_X, FONT_CONTYPE_POS_Y, FONTOAM_CENTER);
	
	STRBUF_Delete(rank_src);
	STRBUF_Delete(type_src);

	MSGMAN_Delete(man);
}

//--------------------------------------------------------------
/**
 * @brief   DINPUT_TYPE_AのBGCreate時に呼ばれるコールバック関数
 *
 * @param   dci				DIシステムワークへのポインタ
 * @param   select_bg		表示BGタイプ(DINPUT_TYPE_???)
 * @param   force_put		TRUE:強制転送、FALSE:既に同じデータが転送されているなら再転送はしない
 */
//--------------------------------------------------------------
static void BGCallback_CommandSelect(DCI_PARAM_PTR dci, int select_bg, int force_put)
{
#if FONTOBJ_VANISH
	Sub_FontOamVanishAll(dci, TRUE);
#else
	CommandFontObjCreate(dci);
#endif
}

//--------------------------------------------------------------
/**
 * @brief   コマンド選択画面のフォントOBJを生成する
 * @param   dci		DIシステムワークへのポインタ
 */
//--------------------------------------------------------------
static void CommandFontObjCreate(DCI_PARAM_PTR dci)
{
	STRBUF *forward_src, *back_src, *left_src, *right_src;
	MSGDATA_MANAGER *msg_man;

	msg_man = dci->sys->dance_msg;
	if(dci->sys->jump_up[dci->sys->c_game->my_breeder_no] == TRUE){
		forward_src = MSGMAN_AllocString(msg_man, CDMSG_FORWARD);
	}
	else{
		forward_src = MSGMAN_AllocString(msg_man, CDMSG_FORWARD_02);
	}
	back_src = MSGMAN_AllocString(msg_man, CDMSG_BACK);
	left_src = MSGMAN_AllocString(msg_man, CDMSG_LEFT);
	right_src = MSGMAN_AllocString(msg_man, CDMSG_RIGHT);

	Sub_FontOamCreate(dci, &dci->font_actor[FA_NO_FORWARD], forward_src, FONT_BUTTON, 
		MSGCOLOR_COMMAND, PALOFS_COMMAND,
		D_PLTTID_SUB_FONTACT, FA_POS_FORWARD_X, FA_POS_FORWARD_Y, FONTOAM_CENTER);
	Sub_FontOamCreate(dci, &dci->font_actor[FA_NO_BACK], back_src, FONT_BUTTON, 
		MSGCOLOR_COMMAND, PALOFS_COMMAND,
		D_PLTTID_SUB_FONTACT, FA_POS_BACK_X, FA_POS_BACK_Y, FONTOAM_CENTER);
	Sub_FontOamCreate(dci, &dci->font_actor[FA_NO_LEFT], left_src, FONT_BUTTON, 
		MSGCOLOR_COMMAND, PALOFS_COMMAND,
		D_PLTTID_SUB_FONTACT, FA_POS_LEFT_X, FA_POS_LEFT_Y, FONTOAM_CENTER);
	Sub_FontOamCreate(dci, &dci->font_actor[FA_NO_RIGHT], right_src, FONT_BUTTON, 
		MSGCOLOR_COMMAND, PALOFS_COMMAND,
		D_PLTTID_SUB_FONTACT, FA_POS_RIGHT_X, FA_POS_RIGHT_Y, FONTOAM_CENTER);
	
	STRBUF_Delete(forward_src);
	STRBUF_Delete(back_src);
	STRBUF_Delete(left_src);
	STRBUF_Delete(right_src);
}



//==============================================================================
//
//	タッチパネル反応時に呼ばれるコールバック関数
//
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   DINPUT_TYPE_COMMANDでタッチパネル反応時に呼び出されるコールバック関数
 *
 * @param   dci			DIシステムワークへのポインタ
 * @param   tp_ret		タッチパネル結果(bmd->tpd_retの値かRECT_HIT_NONE)
 * 
 * @retval  tp_retを返す(処理の中で変更する必要がないなら、引数で渡された値をそのまま返す)
 */
//--------------------------------------------------------------
static int TPCallback_CommandSelect(DCI_PARAM_PTR dci, int tp_ret)
{
	int fa_no;
	
	switch(tp_ret){
	case RECT_HIT_NONE:
	default:
		return tp_ret;
	case DANCE_TP_JUMP:
		fa_no = FA_NO_FORWARD;
		break;
	case DANCE_TP_ADVANCE:
		fa_no = FA_NO_BACK;
		break;
	case DANCE_TP_LEFT:
		fa_no = FA_NO_LEFT;
		break;
	case DANCE_TP_RIGHT:
		fa_no = FA_NO_RIGHT;
		break;
	}
	
	EffectTCB_Add(Effect_ButtonDown, dci);
	dci->effect_work.paracgr.transcgr_id[0] = EXPAND_CHAR_BUTTON_ANM;//CON_DANCE_BUT_ANIM_NCGR_BIN;
	dci->effect_work.paracgr.transcgr_id[1] = EXPAND_CHAR_BUTTON_ANM;//CON_DANCE_BUT_ANIM_NCGR_BIN;
	dci->effect_work.paracgr.transcgr_id[2] = EXPAND_CHAR_BUTTON_ANM;//CON_DANCE_BUT_ANIM_NCGR_BIN;
	dci->effect_work.paracgr.char_x_len = BUTTON_CGR_SIZE_X * BUTTON_ANM_NUM;
	dci->effect_work.paracgr.arc_id = ARC_CONTEST_BG;
	dci->effect_work.paracgr.ctp_rd_ptr[0] = &CommandSelectCgrTransRect[0][tp_ret];
	dci->effect_work.paracgr.ctp_rd_ptr[1] = &CommandSelectCgrTransRect[1][tp_ret];
	dci->effect_work.paracgr.ctp_rd_ptr[2] = &CommandSelectCgrTransRect[2][tp_ret];
	dci->effect_work.paracgr.tp_ret = tp_ret;
	dci->effect_work.paracgr.fa_no = fa_no;
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
 * @brief   CGR転送アニメを行うためのパラメータをセットします
 *
 * @param   dci				DIシステムワークへのポインタ
 * @param   frame_no		フレームNO
 * @param   arc_id			ARCインデックス
 * @param   cgr_id			転送グラフィックのCGRID(0xffffffffの場合はクリアします)
 * @param   rd				転送範囲データのポインタ(cgr_idが0xffffffffの場合はsrcの値は適当でOK)
 * @param   char_len_x		転送グラフィックの横サイズ(キャラクタ単位)
 *							cgr_idが0xfffffffffの場合は0で構いません
 *
 * @retval  CGR転送アニメパラメータワークへのポインタ
 */
//--------------------------------------------------------------
static CGR_TRANS_PARAM * Sub_CgrTransParamSet(DCI_PARAM_PTR dci, int frame_no, u16 arc_id, 
	u32 cgr_id, const CGR_TRANS_RECTDATA *rd, int char_len_x)
{
//	void *arc_data;
//	NNSG2dCharacterData *char_data;
	CGR_TRANS_PARAM *ctp;
	
	ctp = sys_AllocMemory(HEAPID_DANCE, sizeof(CGR_TRANS_PARAM));
	MI_CpuClear8(ctp, sizeof(CGR_TRANS_PARAM));
	
	if(cgr_id != 0xffffffff){
		//既にexpand済みなので必要なくなった 2006.04.06(木)
		//ctp->arc_data = ArcUtil_CharDataGet(arc_id, cgr_id, 1, &char_data, HEAPID_DANCE);
		//ctp->raw_data = char_data->pRawData;
		ctp->raw_data = dci->expand_char[cgr_id];
	}
	ctp->x_len = char_len_x * 0x20;	//char_data->W * 0x20;
	
	ctp->rd = *rd;
	ctp->dest_vram = GF_BGL_CgxGet(frame_no);
	
	return ctp;
}

//--------------------------------------------------------------
/**
 * @brief   CGR転送アニメを行うタスクを生成します
 *
 * @param   frame_no		フレームNO
 * @param   arc_id			ARCインデックス
 * @param   cgr_id			転送グラフィックのCGRID(0xffffffffの場合はクリアします)
 * @param   rd				転送範囲データのポインタ(cgr_idが0xffffffffの場合はsrcの値は適当でOK)
 * @param   char_len_x		転送グラフィックの横サイズ(キャラクタ単位)
 *							cgr_idが0xfffffffffの場合は0で構いません
 *
 * @retval  CGR転送アニメパラメータワークへのポインタ
 *
 * この関数使用後、必ずSub_CgrTransEndCheck関数を使用し、終了確認を行ってください。
 * Sub_CgrTransEndCheck関数内でワークの解放処理などを行っています。
 */
//--------------------------------------------------------------
static CGR_TRANS_PARAM * Sub_CgrTransTaskSet(DCI_PARAM_PTR dci, int frame_no, u16 arc_id, 
	u32 cgr_id, const CGR_TRANS_RECTDATA *rd, int char_len_x)
{
	CGR_TRANS_PARAM *ctp;

	ctp = Sub_CgrTransParamSet(dci, frame_no, arc_id, cgr_id, rd, char_len_x);
	ctp->v_tcb = VWaitTCB_Add(VWait_CgrParamTrans, ctp, VWAIT_TCBPRI_CGRPARAM_TRANS);
	return ctp;
}

//--------------------------------------------------------------
/**
 * @brief   CGR転送アニメタスクが終了しているか確認
 * @param   ctp		CGR転送アニメパラメータワークへのポインタ
 * @retval  TRUE:終了。　FALSE:続行中
 *
 * TRUEを返す時、同時にCGR転送アニメパラメータワークの解放処理も行います。
 */
//--------------------------------------------------------------
static BOOL Sub_CgrTransEndCheck(CGR_TRANS_PARAM *ctp)
{
	if(ctp->v_tcb == NULL){
		if(ctp->arc_data != NULL){
			sys_FreeMemoryEz(ctp->arc_data);
		}
		sys_FreeMemoryEz(ctp);
		return TRUE;
	}
	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   CGR転送アニメをVブランクタスクを利用せずにすぐ実行します
 *
 * @param   frame_no		フレームNO
 * @param   arc_id			ARCインデックス
 * @param   cgr_id			転送グラフィックのCGRID(0xffffffffの場合はクリアします)
 * @param   rd				転送範囲データのポインタ(cgr_idが0xffffffffの場合はsrcの値は適当でOK)
 * @param   char_len_x		転送グラフィックの横サイズ(キャラクタ単位)
 *							cgr_idが0xfffffffffの場合は0で構いません
 *
 * @retval  CGR転送アニメパラメータワークへのポインタ
 *
 * この関数使用後、必ずSub_CgrTransEndCheck関数を使用し、終了確認を行ってください。
 * Sub_CgrTransEndCheck関数内でワークの解放処理などを行っています。
 */
//--------------------------------------------------------------
static void Sub_CgrTransNowCopy(DCI_PARAM_PTR dci, int frame_no, u16 arc_id, u32 cgr_id, 
	const CGR_TRANS_RECTDATA *rd, int char_len_x)
{
	CGR_TRANS_PARAM *ctp;
	
	ctp = Sub_CgrTransParamSet(dci, frame_no, arc_id, cgr_id, rd, char_len_x);
	Sub_CgrParamTrans(ctp);
	if(ctp->arc_data != NULL){
		sys_FreeMemoryEz(ctp->arc_data);
	}
	sys_FreeMemoryEz(ctp);
}

//--------------------------------------------------------------
/**
 * @brief   CGR転送アニメを行います
 * @param   ctp		CGR転送アニメパラメータワークへのポインタ
 */
//--------------------------------------------------------------
static void Sub_CgrParamTrans(CGR_TRANS_PARAM *ctp)
{
	int x, y, dest_x_len;
	u32 src_y, dest_y;
	
	dest_x_len = 32*32;
	
	src_y = ctp->rd.src_y * ctp->x_len;
	dest_y = ctp->rd.dest_y * dest_x_len;
	
	for(y = 0; y < ctp->rd.size_y; y++){
		if(ctp->raw_data != NULL){
			MI_CpuCopy16(&ctp->raw_data[ctp->x_len * y + src_y + ctp->rd.src_x*0x20], 
				&ctp->dest_vram[dest_x_len * y + dest_y + ctp->rd.dest_x*0x20],
				ctp->rd.size_x * 0x20);
		}
		else{
			MI_CpuClear16(&ctp->dest_vram[dest_x_len * y + dest_y + ctp->rd.dest_x*0x20],
				ctp->rd.size_x * 0x20);
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   フォントOAMを作成する
 *
 * @param   dci			BIシステムワークへのポインタ
 * @param   font_actor	生成したフォントOAM関連のワーク代入先
 * @param   str			文字列
 * @param   font_type	フォントタイプ(FONT_SYSTEM等)
 * @param   color		フォントカラー構成
 * @param   pal_offset	パレット番号オフセット
 * @param   pal_id		登録開始パレットID
 * @param   x			座標X
 * @param   y			座標Y
 * @param   pos_center  FONTOAM_LEFT(X左端座標) or FONTOAM_CENTER(X中心座標)
 */
//--------------------------------------------------------------
static void Sub_FontOamCreate(DCI_PARAM_PTR dci, FONT_ACTOR *font_actor, const STRBUF *str, 
	FONT_TYPE font_type, GF_PRINTCOLOR color, int pal_offset, int pal_id, 
	int x, int y, int pos_center)
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
	
	bgl = dci->sys->bgl;
	crp = dci->sys->crp;
	
	//文字列のドット幅から、使用するキャラ数を算出する
	{
		font_len = FontProc_GetPrintStrWidth(font_type, str, PANEL_MSG_MARGIN);
		char_len = font_len / 8;
		if(FX_ModS32(font_len, 8) != 0){
			char_len++;
		}
	}

	//BMP作成
	{
		GF_BGL_BmpWinInit(&bmpwin);
		GF_BGL_BmpWinObjAdd(bgl, &bmpwin, char_len, 16 / 8, 0, 0);
		GF_STR_PrintExpand(&bmpwin, font_type, str, 0, 0, MSG_NO_PUT, color, 
			PANEL_MSG_MARGIN, 0, NULL);
//		GF_STR_PrintColor(&bmpwin, font_type, str, 0, 0, MSG_NO_PUT, color, NULL );
	}

	vram_size = FONTOAM_NeedCharSize(&bmpwin, NNS_G2D_VRAM_TYPE_2DSUB,  HEAPID_DANCE);
	CharVramAreaAlloc(vram_size, CHARM_CONT_AREACONT, NNS_G2D_VRAM_TYPE_2DSUB, &cma);
	
	//座標位置修正
	if(pos_center == FONTOAM_CENTER){
		x -= font_len / 2;
	}
//	y += SUB_SURFACE_Y_INTEGER - 8;
	y += (DANCE_SUB_ACTOR_DISTANCE / FX32_ONE) - 8;
	
	finit.fontoam_sys = dci->fontoam_sys;
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
	finit.heap = HEAPID_DANCE;
	
	fontoam = FONTOAM_Init(&finit);
//	FONTOAM_SetPaletteOffset(fontoam, pal_offset);
	FONTOAM_SetPaletteOffsetAddTransPlttNo(fontoam, pal_offset);
	FONTOAM_SetMat(fontoam, x, y);
	
	//解放処理
	GF_BGL_BmpWinDel(&bmpwin);
	
	font_actor->fontoam = fontoam;
	font_actor->cma = cma;
	font_actor->font_len = font_len;
}

//--------------------------------------------------------------
/**
 * @brief   生成されているフォントOAMを全て削除をする
 * @param   dci		BIシステムワークへのポインタ
 */
//--------------------------------------------------------------
static void Sub_FontOamDeleteAll(DCI_PARAM_PTR dci)
{
	int i;
	
	for(i = 0; i < FA_NO_MAX; i++){
		if(dci->font_actor[i].fontoam != NULL){
			FONTOAM_Delete(dci->font_actor[i].fontoam);
			CharVramAreaFree(&dci->font_actor[i].cma);
			dci->font_actor[i].fontoam = NULL;
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   生成されているフォントOBJ全てのバニッシュフラグを操作する
 * @param   dci		DIシステムワークへのポインタ
 * @param   vanish	バニッシュフラグ(TRUE(表示) or FALSE(非表示))
 */
//--------------------------------------------------------------
static void Sub_FontOamVanishAll(DCI_PARAM_PTR dci, int vanish)
{
	CATS_RES_PTR crp;
	int i;
	int start, end;
	
	if(vanish == TRUE){
		if(dci->makedata_no == DINPUT_TYPE_WALL){
			start = FA_NO_CONRANK;
			end = FA_NO_CONTYPE;
		}
		else{
			start = FA_NO_FORWARD;
			end = FA_NO_RIGHT;
		}
	}
	else{
		start = 0;
		end = FA_NO_MAX-1;
	}
	
	crp = dci->sys->crp;
	for(i = start; i <= end; i++){
		if(dci->font_actor[i].fontoam != NULL){
			FONTOAM_SetDrawFlag(dci->font_actor[i].fontoam, vanish);
		}
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
	
	for(i = 0; i < DCI_BG_NUM; i++){
		if(1){//GF_BGL_FRAME0_S + i != DANCESUB_FRAME_BACK){
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
 * @param   none		DIシステムワークへのポインタ
 */
//--------------------------------------------------------------
static void Sub_TouchEndDelete(DCI_PARAM_PTR dci)
{
	Sub_SceneOBJDelete(dci, FALSE);
	VWaitTCB_Add(VWait_BackScrnOnlyVisible, dci, VWAIT_TCBPRI_BACKSCRN_VISIBLE);
}

//--------------------------------------------------------------
/**
 * @brief   BGタイプが切り替わる毎に削除する必要のあるOBJのDelete処理
 * @param   dci		DIシステムワークへのポインタ
 * @param   sys_exit	TRUE:システムの終了による削除。　FALSE:画面変更、エフェクトでの削除等
 */
//--------------------------------------------------------------
static void Sub_SceneOBJDelete(DCI_PARAM_PTR dci, int sys_exit)
{
#if FONTOBJ_VANISH
	if(sys_exit == TRUE){
		Sub_FontOamDeleteAll(dci);
	}
	else{
		Sub_FontOamVanishAll(dci, FALSE);
	}
#else
	Sub_FontOamDeleteAll(dci);
#endif
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
 * @param   dci			DIシステムワークへのポインタ
 */
//--------------------------------------------------------------
static void EffectTCB_Add(TCB_FUNC func, DCI_PARAM_PTR dci)
{
	GF_ASSERT(dci->effect_tcb == NULL);
	
	MI_CpuClear8(&dci->effect_work, sizeof(DCI_EFFECT_WORK));
	dci->effect_tcb = TCB_Add(func, dci, TCBPRI_DINPUT_EFFECT);
}

//--------------------------------------------------------------
/**
 * @brief   エフェクトTCBを削除する
 * @param   dci		DIシステムワークへのポインタ
 */
//--------------------------------------------------------------
static void EffectTCB_Delete(DCI_PARAM_PTR dci)
{
	if(dci->effect_tcb != NULL){
		TCB_Delete(dci->effect_tcb);
		dci->effect_tcb = NULL;
		MI_CpuClear8(&dci->effect_work, sizeof(DCI_EFFECT_WORK));
	}
}


//--------------------------------------------------------------
/**
 * @brief   パネル部分をキャラ転送アニメを実行して書き換えます。
 *          1つのパネルに対して1つのフォントOBJがセットになっているもの用の汎用タスクです
 *
 * @param   tcb		TCBへのポインタ
 * @param   work	DIシステムワークへのポインタ
 */
//--------------------------------------------------------------
static void Effect_ButtonDown(TCB_PTR tcb, void *work)
{
	DCI_PARAM_PTR dci = work;
	GF_BGL_INI *bgl;
	int x, y;
	int i;
	
	bgl = dci->sys->bgl;
	
	switch(dci->effect_work.seq){
	case 0:
		dci->effect_work.paracgr.ctp = Sub_CgrTransTaskSet(dci, DANCESUB_FRAME_PANEL, 
			dci->effect_work.paracgr.arc_id,
			dci->effect_work.paracgr.transcgr_id[0], dci->effect_work.paracgr.ctp_rd_ptr[0],
			dci->effect_work.paracgr.char_x_len);
		
		FONTOAM_GetMat(dci->font_actor[dci->effect_work.paracgr.fa_no].fontoam, &x, &y);
		FONTOAM_SetMat(dci->font_actor[dci->effect_work.paracgr.fa_no].fontoam, 
			x, y + SCRN_SCROLL_A_EFF_Y);
		
		for(i = 0; i < PARACGR_CAP_MAX; i++){
			if(dci->effect_work.paracgr.cap[i] != NULL){
				CATS_ObjectPosMove(dci->effect_work.paracgr.cap[i]->act, 0, SCRN_SCROLL_A_EFF_Y);
			}
		}
		
		dci->effect_work.seq++;
		break;
	case 1:
		if(Sub_CgrTransEndCheck(dci->effect_work.paracgr.ctp) == FALSE){
			break;
		}
		dci->effect_work.seq++;
		//break;
	case 2:
		dci->effect_work.wait++;
		if(dci->effect_work.wait > SCRN_TOUCH_ANM_WAIT){
			dci->effect_work.wait = 0;
			dci->effect_work.seq++;
		}
		else{
			break;
		}
		//break;
	case 3:
		dci->effect_work.paracgr.ctp = Sub_CgrTransTaskSet(dci, DANCESUB_FRAME_PANEL, 
			dci->effect_work.paracgr.arc_id,
			dci->effect_work.paracgr.transcgr_id[1], dci->effect_work.paracgr.ctp_rd_ptr[1],
			dci->effect_work.paracgr.char_x_len);
		
		FONTOAM_GetMat(dci->font_actor[dci->effect_work.paracgr.fa_no].fontoam, &x, &y);
		FONTOAM_SetMat(dci->font_actor[dci->effect_work.paracgr.fa_no].fontoam, 
			x, y + SCRN_SCROLL_BACK_A_EFF_Y);
		
		for(i = 0; i < PARACGR_CAP_MAX; i++){
			if(dci->effect_work.paracgr.cap[i] != NULL){
				CATS_ObjectPosMove(dci->effect_work.paracgr.cap[i]->act, 
					0, SCRN_SCROLL_BACK_A_EFF_Y);
			}
		}
		
		dci->effect_work.seq++;
		break;
	case 4:
		if(Sub_CgrTransEndCheck(dci->effect_work.paracgr.ctp) == FALSE){
			break;
		}
		dci->effect_work.seq++;
		//break;
	case 5:
		dci->effect_work.wait++;
		if(dci->effect_work.wait > SCRN_TOUCH_WAIT){
			dci->effect_work.wait = 0;
			dci->effect_work.seq++;
		}
		else{
			break;
		}
		//break;

	case 6:
		dci->effect_work.paracgr.ctp = Sub_CgrTransTaskSet(dci, DANCESUB_FRAME_PANEL, 
			dci->effect_work.paracgr.arc_id,
			dci->effect_work.paracgr.transcgr_id[2], dci->effect_work.paracgr.ctp_rd_ptr[2],
			dci->effect_work.paracgr.char_x_len);

		FONTOAM_GetMat(dci->font_actor[dci->effect_work.paracgr.fa_no].fontoam, &x, &y);
		FONTOAM_SetMat(dci->font_actor[dci->effect_work.paracgr.fa_no].fontoam, 
			x, y + SCRN_SCROLL_RESET_A_EFF_Y);
		
		for(i = 0; i < PARACGR_CAP_MAX; i++){
			if(dci->effect_work.paracgr.cap[i] != NULL){
				CATS_ObjectPosMove(dci->effect_work.paracgr.cap[i]->act, 
					0, SCRN_SCROLL_RESET_A_EFF_Y);
			}
		}
		
		dci->effect_work.seq++;
		break;
	case 7:
		if(Sub_CgrTransEndCheck(dci->effect_work.paracgr.ctp) == FALSE){
			break;
		}
		dci->effect_work.seq++;
		//break;
	case 8:
		dci->effect_work.wait++;
		if(dci->effect_work.wait > SCRN_TOUCH_WAIT){
			dci->effect_work.wait = 0;
			dci->effect_work.seq++;
		}
		else{
			break;
		}
		//break;

	default:
		//Sub_TouchEndDelete(dci);
		EffectTCB_Delete(dci);
		return;
	}
}









//==============================================================================
//
//	Vブランク処理
//
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   各フレームのVisible設定を行う
 *
 * @param   tcb			TCBへのポインタ
 * @param   work		DIシステムワークへのポインタ
 */
//--------------------------------------------------------------
static void VWait_FrameVisibleUpdate(TCB_PTR tcb, void *work)
{
	DCI_PARAM_PTR dci = work;
	const BG_MAKE_DATA *bmd;
	int i;

	bmd = &BgMakeData[dci->makedata_no];
	
	//各BG面の表示・非表示設定
	for(i = 0; i < DCI_BG_NUM; i++){
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
 * @brief   リクエストCGR転送
 *
 * @param   tcb			TCBへのポインタ
 * @param   work		DIシステムワークへのポインタ
 */
//--------------------------------------------------------------
static void VWait_CgrRequest(TCB_PTR tcb, void *work)
{
	DCI_PARAM_PTR dci = work;
	
	if(dci->cgr_trans_req != NONE_ID){
		GF_BGL_LoadCharacter(dci->sys->bgl, GF_BGL_FRAME0_S, 
			dci->expand_char[dci->cgr_trans_req], BG_VRAM_SIZE, 0);
		dci->cgr_trans_req = NONE_ID;
	}
	TCB_Delete(tcb);
}

//--------------------------------------------------------------
/**
 * @brief   背景以外のフレーム全てを非表示にする
 *
 * @param   tcb		TCBへのポインタ
 * @param   work	DIシステムワークへのポインタ
 *
 * @retval  
 *
 *
 */
//--------------------------------------------------------------
static void VWait_BackScrnOnlyVisible(TCB_PTR tcb, void *work)
{
	DCI_PARAM_PTR dci = work;

	Sub_BackScrnOnlyVisible();
	TCB_Delete(tcb);
}

//--------------------------------------------------------------
/**
 * @brief   Vブランク中にCGR転送アニメを実行します
 *
 * @param   tcb			TCBへのポインタ
 * @param   work		CGR転送アニメパラメータワークへのポインタ
 */
//--------------------------------------------------------------
static void VWait_CgrParamTrans(TCB_PTR tcb, void *work)
{
	CGR_TRANS_PARAM *ctp = work;
	
	Sub_CgrParamTrans(ctp);
	ctp->v_tcb = NULL;
	TCB_Delete(tcb);
}






//==============================================================================
//
//	ツール
//
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   ボタンフェード
 *
 * @param   dci			DIシステムワークへのポインタ
 * @param   color		変更後のカラー
 * @param   evy			EVY値
 */
//--------------------------------------------------------------
void DINPUT_FadeSet(DCI_PARAM_PTR dci, u16 color, u8 evy)
{
	SoftFadePfd(dci->sys->pfd, FADE_SUB_BG, BUTTON_COLOR_START, BUTTON_COLOR_NUM, evy, color);
}

