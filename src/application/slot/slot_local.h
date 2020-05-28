//==============================================================================
/**
 * @file	slot_local.c
 * @brief	ミニゲーム　スロット　ローカル
 * @author	kagaya
 * @data	05.07.13
 */
//==============================================================================
#ifndef SLOT_MAIN_H_FILE
#define SLOT_MAIN_H_FILE

#include "system/render_oam.h"
#include "system/clact_util.h"
#include "system/arc_tool.h"
#include "..\..\field\eoa.h"
#include "system/snd_tool.h"

#include "system/bmp_list.h"
#include "system/fontproc.h"
#include "system/pm_str.h"
#include "system/wordset.h"
#include "system\fontproc.h"
#include "system\window.h"
#include "msgdata/msg.naix"

#include "poketool\monsno.h"

#include "slot.naix"	//ARC_SLOT
#include "msgdata/msg_slot.h"
#include "application\slot.h"

//==============================================================================
//	define
//==============================================================================
//--------------------------------------------------------------
//	debug
//--------------------------------------------------------------
//----
#ifdef PM_DEBUG
//----
#define DEBUG_ON_SLOT			//定義でデバッグ機能ON
#define DEBUG_SLOT_PARAM_INIT	//定義で偽パラメタ初期化
//----
#endif	//PM_DEBUG
//----

//----
#ifdef DEBUG_ON_SLOT
//----
//----
#endif 	//DEBUG_ON_SLOT
//----

//--------------------------------------------------------------
//	fx
//--------------------------------------------------------------
#define NUM_FX32(a)	(FX32_ONE*(a))							///<整数->FX32型に
#define FX32_NUM(a)	((a)/FX32_ONE)							///<FX32->整数に
#define NUM_FX16(a)	(FX16_ONE*(a))							///<整数->FX16型に
#define FX16_NUM(a)	((a)/FX16_ONE)							///<FX16->整数に

#define SUBD_NFX32(a) (NUM_FX32(192)+NUM_FX32(a))			///<下画面補正 整数->FX32

//--------------------------------------------------------------
///	CLACT
//--------------------------------------------------------------
#define G2D_2DMAIN (NNS_G2D_VRAM_TYPE_2DMAIN)	//上画面
#define G2D_2DSUB  (NNS_G2D_VRAM_TYPE_2DSUB)	//下画面
#define G2D_2DMAX  (NNS_G2D_VRAM_TYPE_MAX)		//両方

///CELLTYPE
typedef enum
{
	CELL_VRAM = FALSE,		///<セル　VRAM常駐型
	CELL_TRANS = TRUE,		///<セル　VRAM転送型
}CELLTYPE;

//--------------------------------------------------------------
///	BGプライオリティ
//--------------------------------------------------------------
typedef enum
{
	BGPRI0 = 0,
	BGPRI1,
	BGPRI2,
	BGPRI3,
}BGPRI;

//--------------------------------------------------------------
///	システム
//--------------------------------------------------------------
#define SLOT_HEAPSIZE (0x00080000)			///<ヒープサイズ
#define SLOT_VRAMTRANSM_REG_MAX (0x08)		///<VRAM転送マネージャ　登録最大

#define STR_BUF_SIZE (256)		///<文字バッファサイズ

#define SLOT_EOA_MAX (128)	///<EOA最大

//--------------------------------------------------------------
//	BG
//--------------------------------------------------------------
#define BGPLTTNO_MOUNT_SKY		(0x01)	///<空パレット
#define BGPLTTNO_LINE_1			(0x02)
#define BGPLTTNO_LINE_2_0		(0x03)
#define BGPLTTNO_LINE_2_1		(0x0c)
#define BGPLTTNO_LINE_3_0		(0x04)
#define BGPLTTNO_LINE_3_1		(0x0b)

#define BGFRAME_KAIWA			(GF_BGL_FRAME0_M)
#define BGFRAME_SLOT			(GF_BGL_FRAME1_M)
#define BGFRAME_SLOT_SHADOW		(GF_BGL_FRAME2_M)
#define BGFRAME_BGSUB			(GF_BGL_FRAME3_S)
#define BGFRAME_SUB_DEBUG		(GF_BGL_FRAME0_S)

#define BG_SLOT_CHAR_SIZE	(32)	//color 256

#define BGF_SLOT_PLTT_SIZE		(32*13)
#define BGF_SLOT_PLTT_OFFSET	(32*0)
#define BGF_SLOT_CHAR_OFFSET	(BG_SLOT_CHAR_SIZE*0)

#define BGF_SLOT_PANO	(0)

#define BGF_SLOT_PANO_FONT	(15)
#define BGF_SLOT_PANO_TALK	(14)
#define BGF_SLOT_CHAR_NO_WIN (1)
#define BGF_SLOT_CHAR_NO_TALK (BGF_SLOT_CHAR_NO_WIN+TALK_WIN_CGX_SIZ)

//--------------------------------------------------------------
///	セルアクター
//--------------------------------------------------------------
#define SLOT_CLACT_MAX (64)
#define SLOT_CLACT_TRANS_MAX (32)

#define CHAR_MANAGER_MAX (32)
#define CHAR_VRAMTRANS_M_SIZE (0x4000)	//512
#define CHAR_VRAMTRANS_S_SIZE (0x4000)	//512

#define PLTT_MANAGER_MAX (16)

#define SLOT_CHAR_MAX (64)
#define SLOT_PLTT_MAX (16)
#define SLOT_CELL_MAX (64)
#define SLOT_ANM_MAX (32)


//--------------------------------------------------------------
///	絵柄種類
//--------------------------------------------------------------
typedef enum
{
	REEL_RED7 = 0,		///<赤７
	REEL_BLACK7,		///<黒７
	REEL_REPLAY,		///<リプレイ
	REEL_CHERRY,		///<チェリー
	REEL_BELL,			///<ベル
	REEL_SUIKA,			///<スイカ
	REEL_PATTERN_MAX,	///<絵柄最大
}REEL_PATTERN;

//--------------------------------------------------------------
///　リール番号
//--------------------------------------------------------------
typedef enum
{
	REEL_0,
	REEL_1,
	REEL_2,
	REEL_MAX,
}REEL_NUM;

//--------------------------------------------------------------
///	ライン番号
//--------------------------------------------------------------
typedef enum
{
	LINE_1 = 0,
	LINE_2_0,
	LINE_2_1,
	LINE_3_0,
	LINE_3_1,
	LINE_MAX,
}LINENO;

//--------------------------------------------------------------
///	ラインビット
//--------------------------------------------------------------
#define LINEBIT_NON (0)
#define LINEBIT_1	(1<<0)
#define LINEBIT_2_0 (1<<1)
#define LINEBIT_2_1 (1<<2)
#define LINEBIT_3_0 (1<<3)
#define LINEBIT_3_1 (1<<4)

//--------------------------------------------------------------
///	リール状態
//--------------------------------------------------------------
typedef enum
{
	REEL_ST_STOP = 0,
	REEL_ST_SCROLL,
	REEL_ST_WAIT,
}REEL_ST;

//--------------------------------------------------------------
///	継続率ダウンタイプ
//--------------------------------------------------------------
typedef enum 
{
	CONT_BONUS_DOWN_10 = 0,
	CONT_BONUS_DOWN_5,
	CONT_BONUS_DOWN_MAX,
}CONTBONUSDOWN;

//--------------------------------------------------------------
///	ボール種類
//--------------------------------------------------------------
typedef enum
{
	BALL_MON = 0,
	BALL_SUP,
	BALL_HYP,
	BALL_SAF,
	BALL_PRE,
	BALL_MAX,
}BALLTYPE;

//--------------------------------------------------------------
///	MBALL TYPE モンスターボール動作タイプ
//--------------------------------------------------------------
typedef enum
{
	MBALLMT_INIT = 0,		///<ボール初期化
	MBALLMT_SPIN_START,		///<転がり開始
	MBALLMT_OPEN,			///<開く
	MBALLMT_CLOSE,			///<閉じる
	MBALLMT_SPIN_OUT,		///<画面外へ転がる
	MBALLMT_SHAKE,			///<ゆれる
	MBALLMT_STOP,			///<停止
	MBALLMT_MAX,
}MBALLMT;

//--------------------------------------------------------------
///	ボールアニメ番号
//--------------------------------------------------------------
enum
{
	MBALLANMNO_START,
	MBALLANMNO_OPEN,
	MBALLANMNO_STOP,
	MBALLANMNO_CLOSE,
	MBALLANMNO_BACK,
};

//--------------------------------------------------------------
///	ピッピセルアニメ番号
//--------------------------------------------------------------
enum
{
	PIPANMNO_STOP,
	PIPANMNO_START,
	PIPANMNO_PATAPATA,
	PIPANMNO_RIGHT,
	PIPANMNO_LEFT,
	PIPANMNO_NAKA,
};

//--------------------------------------------------------------
///	ピッピ
//--------------------------------------------------------------
typedef enum
{
	PIP_NORMAL = 0,
	PIP_META,
	PIP_RARE,
	PIP_MAX,
}PIPTYPE;

//--------------------------------------------------------------
///	PIPMT　ピッピ動作タイプ
//--------------------------------------------------------------
typedef enum
{
	PIPMT_INIT,		///<初期化
	PIPMT_START,	///<登場
	PIPMT_BACK,		///<戻る
	PIPMT_STAND,	///<立ち
	PIPMT_PATAPATA,	///<パタパタ
	PIPMT_NAKA,		///<中央指し
	PIPMT_LEFT,		///<左指し
	PIPMT_RIGHT,	///<右指し
	PIPMT_BANZAI,	///<万歳
	PIPMT_MAX,		///<動作最大
}PIPMT;

//--------------------------------------------------------------
///	ボーナス継続演出
//--------------------------------------------------------------
typedef enum
{
	BCEFF_NON = 0,		///<何も無し
	BCEFF_BACK,			///<戻る
	BCEFF_ANENCORE,		///<アンコール
	BCEFF_MAX,			///<最大
}BCEFF;

//--------------------------------------------------------------
///	獲得数or回数
//--------------------------------------------------------------
typedef enum
{
	BIGFONT_COUNT = 0,
	BIGFONT_GET,
}BIGFONTTYPE;

//--------------------------------------------------------------
///	ゲーム
//--------------------------------------------------------------
#define BET_LOWEST	(3)						///<ベットに最低限必要なクレジット
#define BET_LOWEST_BONUS	(1)				///<ボーナス時、ベットに最低限必要なクレジット

//--------------------------------------------------------------
//	リール
//--------------------------------------------------------------
#define REEL_PT_MAX      (21)							// 絵柄最大 21絵柄

#define REEL_PT_V_SIZE   (32)							// 絵柄ｻｲｽﾞ ドット
#define REEL_PT_V_OFFSET (16)							// 絵柄ｵﾌｾｯﾄ

#define REEL_PT_V_MAX    (160)							// 絵柄縦最大
#define REEL_PT_V_DG(v)  ((v)/REEL_PT_V_SIZE)			// ﾄﾞｯﾄ -> ｸﾞﾘｯﾄﾞ
#define REEL_PT_V_DG32(v)  ((FX32_NUM(v))/REEL_PT_V_SIZE)// ﾄﾞｯﾄ -> ｸﾞﾘｯﾄﾞ fx32
#define REEL_PT_V_GD(v)  ((v)*REEL_PT_V_SIZE)			// ｸﾞﾘｯﾄﾞ -> ﾄﾞｯﾄ
#define REEL_PT_V_GD32(v)  (NUM_FX32((v)*REEL_PT_V_SIZE))	// ｸﾞﾘｯﾄﾞ -> ﾄﾞｯﾄ
#define REEL_SCROLL_MAX  (REEL_PT_MAX*REEL_PT_V_SIZE)	// ﾘｰﾙｽｸﾛｰﾙ最大
#define REEL_CENTERN_V   ((0x09*8)+4)					// ﾘｰﾙ中央

#define MCREEL_PT_MAX		(0x06)						// ﾏｼﾝﾘｰﾙ絵柄最大
#define MCREEL_PT_V_SIZE	(0x14)						// ﾏｼﾝﾘｰﾙ絵柄ｻｲｽﾞ
#define MCREEL_PT_V_OFFSET	((0x06*0x08)+4+8)			// ﾏｼﾝﾘｰﾙ絵柄ｵﾌｾｯﾄ
#define MCREEL_PT_V_MAX		(0x02*MCREEL_PT_V_SIZE)		// ﾏｼﾝﾘｰﾙ縦最大
#define MCREEL_PT_V_GP(v)	((v)/MCREEL_PT_V_SIZE)		// 座標->ｸﾞﾘｯﾄﾞ
#define MCREEL_SCROLL_MAX	(MCREEL_PT_MAX*MCREEL_PT_V_SIZE)

//--------------------------------------------------------------
///	抽選
//--------------------------------------------------------------
#define LOTTERY_HITBIT_NON			(0)				///<無し
#define LOTTERY_HITBIT_REPLAY		(1<<0)			///<リプレイ
#define LOTTERY_HITBIT_REPLAY_B		(1<<1)			///<リプレイ　ビッグ
#define LOTTERY_HITBIT_CHERRY		(1<<2)			///<チェリー
#define LOTTERY_HITBIT_CHERRY_B		(1<<3)			///<チェリー　ビッグ
#define LOTTERY_HITBIT_BELL			(1<<4)			///<ベル
#define LOTTERY_HITBIT_BELL_B		(1<<5)			///<ベル　ビッグ
#define LOTTERY_HITBIT_SUIKA		(1<<6)			///<スイカ
#define LOTTERY_HITBIT_SUIKA_B		(1<<7)			///<スイカ　ビッグ
#define LOTTERY_HITBIT_BLACK7		(1<<8)			///<黒7
#define LOTTERY_HITBIT_RED7			(1<<9)			///<赤7

#define LOTTERY_NUM_MAX (10)				

///7ビット
#define LOTTERY_HITBIT_SEVEN_AND \
(LOTTERY_HITBIT_BLACK7|LOTTERY_HITBIT_RED7)
///ボーナスビット
#define LOTTERY_HITBIT_BONUS_AND \
(LOTTERY_HITBIT_REPLAY_B|LOTTERY_HITBIT_CHERRY_B|LOTTERY_HITBIT_BELL_B|LOTTERY_HITBIT_SUIKA_B)

///子役Aオートビット
#define LOTTERY_HITBIT_AUTO_AND \
(LOTTERY_HITBIT_REPLAY|LOTTERY_HITBIT_REPLAY_B|LOTTERY_HITBIT_BELL|LOTTERY_HITBIT_BELL_B)

///子役Aボーナス確定ビット
#define LOTTERY_HITBIT_BONUSMODE \
(LOTTERY_HITBIT_SUIKA_B|LOTTERY_HITBIT_CHERRY_B)

//--------------------------------------------------------------
///	当たり
//--------------------------------------------------------------
#define BIT_CHERRY		0x0001							// ﾋｯﾄﾌﾗｸﾞ
#define BIT_CHERRY_4	0x0002
#define BIT_REPLAY		0x0004
#define BIT_BELL		0x0008
#define BIT_SUIKA		0x0010
#define BIT_REGULAR		0x0020
#define BIT_BIG_RED		0x0040

//--------------------------------------------------------------
///	継続率種類
//--------------------------------------------------------------
typedef enum
{
	CONT_777_50 = 0,
	CONT_777_70,
	CONT_777_90,
	CONT_GGG_50,
	CONT_GGG_70,
	CONT_GGG_90,
	CONT_BONUS_TYPE_MAX,
}CONTBONUSTYPE;

//--------------------------------------------------------------
///	継続率
//--------------------------------------------------------------
typedef enum
{
	CONT_BONUS_50 = 0,
	CONT_BONUS_70,
	CONT_BONUS_90,
	CONT_BONUS_MAX,
}CONTBONUS;

//--------------------------------------------------------------
///	終了継続率
//--------------------------------------------------------------
typedef enum
{
	CONT_BONUSEND_0 = 0,
	CONT_BONUSEND_5 = 5,
	CONT_BONUSEND_15 = 15,
	CONT_BONUSEND_25 = 25,
	CONT_BONUSEND_35 = 35,
	CONT_BONUSEND_45 = 45,
	CONT_BONUSEND_55 = 55,
	CONT_BONUSEND_65 = 65,
	CONT_BONUSEND_100_75 = 75,
	CONT_BONUSEND_NUM_MAX = 9,
}CONT_BONUSEND;

//--------------------------------------------------------------
///	tcb	プライオリティ
//--------------------------------------------------------------
enum
{
	TCBPRI_SLOT_BASE = 0x80,							///<スロットベース
	TCBPRI_REELCONTROL0,								///<リール制御 0
	TCBPRI_REELCONTROL1,								///<リール制御 1
	TCBPRI_REELCONTROL2,								///<リール制御 2
	TCBPRI_DDISPCONTROL,								///<下画面制御
	TCBPRI_PLTTCONTROL,									///<パレット制御
	TCBPRI_MBALL,										///<モンスターボール
	TCBPRI_BALLEFF,										///<ボールエフェクト
	TCBPRI_PIKA,										///<ピカチュウ
	TCBPRI_PIP,											///<ピッピ
	TCBPRI_PAYOUTCONTROL,								///<ペイアウト制御
	TCBPRI_REEL,										///<リール絵
	TCBPRI_REEL_BIGHIT,									///<大当たりリール絵
	TCBPRI_CREDITFONT,									///<コイン文字
	TCBPRI_BONUSFONT,									///<ボーナス文字
	TCBPRI_PLTTEFF,										///<パレットエフェクト
	TCBPRI_BGM,											///<BGM
};

//--------------------------------------------------------------
///	tcb	VIntrブランクプライオリティ
//--------------------------------------------------------------
enum
{
	VINTRTCBPRI_SLOT_BASE = 0x100,							///<スロットベース
	VINTRTCBPRI_MBALLTRANS,									///<ボール追加
};

//--------------------------------------------------------------
///	tcb	VWaitブランクプライオリティ
//--------------------------------------------------------------
enum
{
	VWAITTCBPRI_SLOT_BASE = 0x100,							///<スロットベース
	VWAITTCBPRI_MBALLTRANS,									///<ボール追加
};

//--------------------------------------------------------------
///	セルアクタープライオリティ
//--------------------------------------------------------------
enum
{
	CAPRI_BIGHIT_REEL,									///<ビッグヒット絵柄
	CAPRI_CREDITFONT,									///<コイン文字
	CAPRI_REEL,											///<リール
	CAPRI_BONUS_FONT,									///<ボーナスフォント
	CAPRI_PIKA,											///<ピカチュウ
	CAPRI_BALLEFF,										///<ボール煙
	CAPRI_PIP,											///<ピッピ
	CAPRI_MBALL,										///<モンスターボール
};

//--------------------------------------------------------------
///	セルアクター　キャラID
//--------------------------------------------------------------
enum
{
	SLOT_CHARID_REEL,
	SLOT_CHARID_CREDITFONT,
	SLOT_CHARID_MBALL,
	SLOT_CHARID_BALLEFF,
	SLOT_CHARID_PIP,
	SLOT_CHARID_PIKA,
	SLOT_CHARID_BONUSFONT,
	SLOT_CHARID_GETFONT,
	SLOT_CHARID_BONUSGETFONT,
	SLOT_CHARID_MOONFONT,
	SLOT_CHARID_BIGHIT,
	SLOT_CHARID_MAX,
};

//--------------------------------------------------------------
///	セルアクター　OBJパレットID
//--------------------------------------------------------------
enum
{
	SLOT_PLTTID_REEL,
	SLOT_PLTTID_CREDITFONT,
	SLOT_PLTTID_MBALL,
	SLOT_PLTTID_BALLEFF,
	SLOT_PLTTID_PIP,
	SLOT_PLTTID_PIKA,
	SLOT_PLTTID_BONUSFONT,
	SLOT_PLTTID_MOONFONT,
	SLOT_PLTTID_MAX,
};

//--------------------------------------------------------------
///	セルアクター　セルID
//--------------------------------------------------------------
enum
{
	SLOT_CELLID_REEL,
	SLOT_CELLID_CREDITFONT,
	SLOT_CELLID_MBALL,
	SLOT_CELLID_BALLEFF,
	SLOT_CELLID_PIP,
	SLOT_CELLID_PIKA,
	SLOT_CELLID_BONUSFONT,
	SLOT_CELLID_GETFONT,
	SLOT_CELLID_BONUSGETFONT,
	SLOT_CELLID_MOONFONT,
	SLOT_CELLID_BIGHIT,
	SLOT_CELLID_MAX,
};

//--------------------------------------------------------------
///	セルアクター　アニメID
//--------------------------------------------------------------
enum
{
	SLOT_ANMID_REEL,
	SLOT_ANMID_CREDITFONT,
	SLOT_ANMID_MBALL,
	SLOT_ANMID_BALLEFF,
	SLOT_ANMID_PIP,
	SLOT_ANMID_PIKA,
	SLOT_ANMID_BONUSFONT,
	SLOT_ANMID_GETFONT,
	SLOT_ANMID_BONUSGETFONT,
	SLOT_ANMID_MOONFONT,
	SLOT_ANMID_BIGHIT,
	SLOT_ANMID_MAX,
};

//--------------------------------------------------------------
///	ウィンドウリスト
//--------------------------------------------------------------
enum
{
	SLOTWIN_TALK = 0,		///<会話ウィンドウ
	SLOTWIN_MAX,
};

//--------------------------------------------------------------
///	メッセージ番号
//--------------------------------------------------------------
#define MSGNO_SANMAI		(msg_00)
#define MSGNO_CREDIT_MAX	(msg_01)

//--------------------------------------------------------------
///	BGM
//--------------------------------------------------------------
typedef enum
{
	BGM_NORMAL,
	BGM_HIT,
	BGM_BIGHIT,
	BGM_MAX,
}BGMTYPE;

//==============================================================================
//	typedef struct
//==============================================================================
typedef struct _TAG_SLOTMAIN SLOTMAIN;			///<SLOTMAIN スロットメインワーク
typedef struct _TAG_CLACTSETDATA CLACTSETDATA;	///<CLACTSETDATA セルアクター

//--------------------------------------------------------------
///	MSGWORK
//--------------------------------------------------------------
typedef struct
{
	MSGDATA_MANAGER *msgman;
	WORDSET *wordset;
	GF_BGL_BMPWIN bmpwin[SLOTWIN_MAX];
	void *strbuf;
}MSGWORK;

//--------------------------------------------------------------
///	CLACT_WORK_EX
//--------------------------------------------------------------
typedef struct
{
	CELLTYPE trans_flag;
	CLACT_WORK_PTR act;
	const NNSG2dImageProxy *pImageProxy;
}CLACT_WORK_EX;

//--------------------------------------------------------------
///	CELLARCDATA OAM絵データ
//--------------------------------------------------------------
typedef struct
{
	u32 char_id;
	u32 pltt_id;
	u32 cell_id;
	u32 anm_id;
}CELLARCDATA;

//--------------------------------------------------------------
///	LT_CONT_BONUS
//--------------------------------------------------------------
typedef struct
{
	u32 prob;
	CONTBONUSTYPE type;
	CONTBONUS prob_type;
}LT_CONT_BONUS;

//--------------------------------------------------------------
///	LT_SMALLBONUS
//--------------------------------------------------------------
typedef struct
{
	u16 lt_bonus;
	u16 lt_small;
}LT_SMALLBONUS;

//--------------------------------------------------------------
///	LT_POKE_ENTRY
//--------------------------------------------------------------
typedef struct
{
	u32 prob;
	PIPTYPE type;
}LT_POKE_ENTRY;

//--------------------------------------------------------------
///	LT_SMALLDATA
//--------------------------------------------------------------
typedef struct
{
	LT_SMALLBONUS cherry;
	LT_SMALLBONUS suika;
	LT_SMALLBONUS bell;
	LT_SMALLBONUS replay;
}LT_SMALLDATA;

//--------------------------------------------------------------
///	LT_CONTBONUSEND
//--------------------------------------------------------------
typedef struct
{
	CONT_BONUSEND prec_bonus;
	u32 prec_back;
	u32 prec_non;
	u32 prec_anencore;
}LT_CONTBONUSEND;

//--------------------------------------------------------------
///	REELCONTROL
//--------------------------------------------------------------
typedef struct
{
	u32 seq_no;
	int scroll_flag;
	fx32 slip_dot_y;
	int frame;
	REEL_NUM reel_no;
	int reel_hit_grid_y;
	int reel_slip_grid_y;
	TCB_PTR tcb;
	SLOTMAIN *main;
}REELCONTROL;

//--------------------------------------------------------------
///	PAYOUTCONTROL
//--------------------------------------------------------------
typedef struct
{
	u32 seq_no;
	u32 end_flag;
	int frame;
	SLOTMAIN *main;
	TCB_PTR tcb;
	EOA_PTR eoa_reelanm0;
	EOA_PTR eoa_reelanm1;
}PAYOUTCONTROL;

//--------------------------------------------------------------
///	BGM
//--------------------------------------------------------------
typedef struct
{
	u32 seq_no;
	int chg_flag;
	BGMTYPE now_play;
	BGMTYPE next_play;
	TCB_PTR tcb;
}SLOTBGM;

//--------------------------------------------------------------
///	DDISPCONTROL 下画面コントロール構造体
//--------------------------------------------------------------
typedef struct
{
	u32 move_type;
	u32 seq_no;
	u32 end_flag;
	u32 bonus_font_vanish_flag;
	int frame;
	int count;
	BALLTYPE balltype;
	PIPTYPE piptype;
	SLOTMAIN *main;
	TCB_PTR tcb;
	EOA_PTR eoa_mball;
	EOA_PTR eoa_balleff;
	EOA_PTR eoa_pip;
	EOA_PTR eoa_pika;
	EOA_PTR eoa_font_bonus;
	EOA_PTR eoa_font_get;
	EOA_PTR eoa_font_bcount;
	EOA_PTR eoa_font_getcoin;
}DDISPCONTROL;

//--------------------------------------------------------------
///	PLTTCONTROL構造体
//--------------------------------------------------------------
typedef struct
{
	SLOTMAIN *main;
	
	u16 plttbase_mount[16];
	u16 plttkurai_mount[16];
	u16 plttflash_mount[16];
	u16 plttflash_red_mount[16];
	u16 plttbuf_mount[16];
	
	u16 plttbase_line[LINE_MAX][16];
	u16 plttflash_line[LINE_MAX][16];
	u16 plttbuf_line[LINE_MAX][16];
}PLTTCONTROL;

#ifdef DEBUG_ON_SLOT
//--------------------------------------------------------------
//	D_SLOTWORK
//--------------------------------------------------------------
typedef struct
{
	u32 seq_no;
	u32 auto_flag;		//自動プレイ
	u32 auto_play_replay_avoid_flag;
	u32 debug_lottery_bit;
	u32 debug_auto_set;
	u32 debug_bonus_end;
	PIPTYPE debug_pip_type;
	u32 debug_moon_light;
	u32 debug_moon_red;
	BCEFF debug_bonus_end_effect;
	int auto_stop_count;
	int auto_stop_frame;
	u32 lottery_no;
	u32 hitline[LINE_MAX];
}D_SLOTWORK;
#endif

//--------------------------------------------------------------
///	SLOTMAIN構造体
//--------------------------------------------------------------
typedef struct _TAG_SLOTMAIN
{
	u32 seq_no;								///<シーケンス
	u32 next_seq_no;						///<次シーケンス番号
	u32 bonus_game_flag;					///<ボーナスゲームフラグ
	u32 bonus_hit_count;					///<ボーナスヒット回数
	u32 bonus_count;						///<ボーナス回数
	u32 bonus_get_coin;						///<ボーナスで獲得したコイン総数
	u32 bonus_continue_prob;				///<ボーナス継続率
	u32 bonus_continue_count;				///<ボーナス継続数
	u32 bonus_continue_count_max;			///<ボーナス継続数最大
	u32 bonus_moonlight_flag;				///<月光フラグ
	u32 bonus_moonlight_red_flag;			///<赤い月フラグ
	u32 bonus_game_end_flag;				///<ボーナスゲーム終了フラグ
	u32 reel_slip_hit_flag;					///<リールヒットフラグ
	u32 yubisashi_type;						///<指差しタイプ
	u32 data_game_count;					///<ゲームカウント
	u32 data_miss_count;					///<外れた回数
	u32 data_hit_count;						///<当たった回数
	REEL_PATTERN reel_hit_pattern;			///<ヒットしたリールパターン
	u32 reel_hit_line_bit;
	CONTBONUS bonus_continue_prob_type;		///<ボーナス継続率種類
	CONTBONUSTYPE bonus_continue_type;		///<ボーナス継続率タイプ
	u32 reel_stop_btn[REEL_MAX];			///<ストップボタン格納
	int credit;								///<クレジット
	int payout;								///<支払い
	int bet;								///<ベット
	fx32 frame;								///<汎用フレーム
	int auto_hit_flag;						///<オートヒットフラグ
	u32 lottery_bit;						///<抽選フラグ
	u32 hit_bit;							///<ヒットビット
	REEL_ST reel_status[REEL_MAX];			///<リールステータス
	SLOT_HARD hard;							///<台設定
	
	fx32 reel_speed;						///<リール　速度
	fx32 reel_dot_y[REEL_MAX];				///<リール　ドット
	fx32 reel_offs_y[REEL_MAX];				///<リール　オフセット
	int  reel_grid_y[REEL_MAX];				///<リール　グリッド
	
	REELCONTROL reelcont[REEL_MAX];			///<REELCONTROL
	PAYOUTCONTROL payoutcont;				///<PAYOUTCONTROL
	DDISPCONTROL ddispcont;					///<DDISPCONTROL
	PLTTCONTROL plttcont;					///<PLTTCONTROL
	MSGWORK msgwork;						///<MSGWORK
	SLOTBGM bgm;							///<SLOTBGM
	
	ARCHANDLE *arc_handle;
	GF_BGL_INI *bgl;
	
	NNSG2dScreenData *bg_pScr;
	NNSG2dCharacterData *bg_pChar;
	NNSG2dPaletteData *bg_pPltt;
	
	EOA_SYS_PTR eoa_sys;
	CLACTSETDATA *clactset;
	EOA_PTR eoa_reel_bighit;

	u32 payout_total;
	u32 bet_total;
	u32 game_count;
	u32 ngame_count;
	u32 bmode_count;
	u32 bgame_count;
	u32 kihon_a_count;
	u32 kihon_b_count;
	u32 keizoku_50_count;
	u32 keizoku_70_count;
	u32 keizoku_90_count;
	u32 metamon_count;
	u32 pippi_count;
	u32 rare_pippi_count;
	u32 navi_hit_count;
	u32 replay_hit_count;
	u32 replay_hit_b_count;
	u32 cherry_hit_count;
	u32 cherry_hit_b_count;
	u32 bell_hit_count;
	u32 bell_hit_b_count;
	u32 suika_hit_count;
	u32 suika_hit_b_count;
	u32 ginga_hit_count;
	u32 seven_hit_count;
	u32 moonlight_count;
	u32 moonred_count;
	
	WINTYPE win_type;
#ifdef DEBUG_ON_SLOT
	D_SLOTWORK d_work;
#endif
};

#define SLOTMAIN_SIZE (sizeof(SLOTMAIN))

//==============================================================================
//	外部参照
//==============================================================================
//--------------------------------------------------------------
//	slot.c
//--------------------------------------------------------------
extern void SlotTalkWinFont_Init( SLOTMAIN *main );
static void SlotTalkWinFont_Delete( SLOTMAIN *main );
extern void SlotTalkWin_Write( SLOTMAIN *main, u32 type );
extern void SlotTalkWin_Clear( SLOTMAIN *main );

extern void SlotBGM_Play( SLOTMAIN *main, BGMTYPE type );

extern void * Slot_AllocMemory( u32 size );
extern void * Slot_AllocMemoryLo( u32 size );
extern void * SlotArc_DataLoad( SLOTMAIN *main, u32 id, int fb );

//--------------------------------------------------------------
///	slot_main.c
//--------------------------------------------------------------
extern void SlotMain_GameInit( SLOTMAIN *main );
extern void SlotMain_GameDelete( SLOTMAIN *main );

extern int SlotMain_Game( SLOTMAIN *main );

static void ReelControlTcb( TCB_PTR tcb, void *wk );

extern REEL_PATTERN Slot_ReelPatternGet( SLOTMAIN *main, REEL_NUM no, int offs );
extern REEL_PATTERN Slot_ReelPatternGridGet( SLOTMAIN *main, REEL_NUM no, int offs );

//--------------------------------------------------------------
//	slot_sub.c
//--------------------------------------------------------------
extern void SlotSubEoa_ReelPatternInit( SLOTMAIN *main );
extern void SlotSubEoa_CreditFontInit( SLOTMAIN *main );
extern void SlotSubEoa_PayOutFontInit( SLOTMAIN *main );
//extern void SlotSubEoa_WinLoseFontInit( SLOTMAIN *main );

extern EOA_PTR SlotSubEoa_MBallSet( SLOTMAIN *main, BALLTYPE type );
extern void SlotSubEoa_MBallMoveTypeChange( EOA_PTR eoa, MBALLMT type );
extern void SlotSubEoa_MBallVanishSet( EOA_PTR eoa, int vanish );
extern int SlotSubEoa_MBallMoveEndCheck( EOA_PTR eoa );

extern EOA_PTR SlotSubEoa_BallEffSet( SLOTMAIN *main );
extern int SlotSubEoa_BallEffEndCheck( EOA_PTR eoa );

extern EOA_PTR SlotSubEoa_PipSet( SLOTMAIN *main, PIPTYPE type );
extern void SlotSubEoa_PipMoveTypeChange( EOA_PTR eoa, PIPMT type );
extern int SlotSubEoa_PipMoveEndCheck( EOA_PTR eoa );

extern EOA_PTR SlotSubEoa_PikaSet( SLOTMAIN *main );
extern int SlotSubEoa_PikaEndCheck( EOA_PTR eoa );

extern EOA_PTR SlotSubEoa_BonusFontInit( SLOTMAIN *main );
extern EOA_PTR SlotSubEoa_BigBonusFontInit( SLOTMAIN *main );
extern EOA_PTR SlotSubEoa_GetFontInit( SLOTMAIN *main );
extern EOA_PTR SlotSubEoa_BigGetFontInit( SLOTMAIN *main );
extern EOA_PTR SlotSubEoa_BCountFontInit( SLOTMAIN *main );
extern EOA_PTR SlotSubEoa_GetCountFontInit( SLOTMAIN *main );
extern EOA_PTR SlotSubEoa_BigCountFont( SLOTMAIN *main, BIGFONTTYPE type );
extern EOA_PTR SlotSubEoa_MoonFontInit( SLOTMAIN *main, u32 count );

extern EOA_PTR SlotSubEoa_ReelBigHitInit( SLOTMAIN *main );

//--------------------------------------------------------------
//	slot_data.c
//--------------------------------------------------------------
extern const REEL_PATTERN DATA_SlotDataReelPattern[REEL_MAX][REEL_PT_MAX];
extern const int DATA_SlotPayOutSmall[REEL_PATTERN_MAX];
extern const int DATA_SlotPayOutBonus[REEL_PATTERN_MAX];
extern const u32 DATA_SlotBasicLotteryA[SLOT_HARD_MAX];
extern const LT_SMALLDATA DATA_SlotSmallLotteryA[SLOT_HARD_MAX];
extern const u32 DATA_LotteryNavi[SLOT_HARD_MAX];
extern const LT_CONT_BONUS DATA_LotteryContinueBonus[SLOT_HARD_MAX][CONT_BONUS_TYPE_MAX];
extern const LT_POKE_ENTRY DATA_LotteryPokeEntry[SLOT_HARD_MAX][CONT_BONUS_MAX][PIP_MAX];
extern const u32 DATA_ContinueBonusTypeParam[CONT_BONUS_TYPE_MAX];
extern const u32 DATA_SlotBasicLotteryB[SLOT_HARD_MAX];
extern const u32 DATA_SlotSmallLotteryB[SLOT_HARD_MAX][4];
extern const u32 DATA_LotteryMoonLight[SLOT_HARD_MAX];
extern const u32 DATA_LotteryMoonLightRed[SLOT_HARD_MAX];
extern const u32 DATA_LotteryBonusContinue[SLOT_HARD_MAX][CONT_BONUS_DOWN_MAX];
extern const LT_CONTBONUSEND DATA_LotteryContinueBonusEnd[SLOT_HARD_MAX][CONT_BONUSEND_NUM_MAX];

//--------------------------------------------------------------
//	slot_clact.c
//--------------------------------------------------------------
extern CLACTSETDATA * ClActSetDataInit(
		u32 heap_id,
		u32 actmax, u32 transmax,
		u32 charmax, u32 plttmax, u32 cellmax, u32 anmmax,
		u32 charnonid, u32 plttnonid, u32 cellnonid, u32 anmnonid );
extern void ClActSetDataDelete( CLACTSETDATA *set );
extern void ClActSetDataDraw( CLACTSETDATA *set );
extern void ClActCharAdd( CLACTSETDATA *set, u32 type, ARCHANDLE *hand, u32 arcid, u32 id );
extern void ClActCharVramAreaSet( CLACTSETDATA *set, u32 id );
extern void ClActCharResDelete( CLACTSETDATA *set, u32 id );
extern void ClActPlttAdd( CLACTSETDATA *set, u32 type, ARCHANDLE *hand, u32 arcid, u32 id );
extern void ClActPlttVramAreaSet( CLACTSETDATA *set, u32 id );
extern void ClActPlttResDelete( CLACTSETDATA *set, u32 id );
extern const NNSG2dImagePaletteProxy * ClActPlttProxyGet( CLACTSETDATA *set, u32 id );
extern void ClActCellAdd( CLACTSETDATA *set, ARCHANDLE *hand, u32 arcid, u32 id );
extern void ClActAnmAdd( CLACTSETDATA *set, ARCHANDLE *hand, u32 arcid, u32 id );
extern void ClActGraphicDelete(CLACTSETDATA *set,u32 charid,u32 plttid,u32 cellid,u32 anmid );
extern void ClActAdd( CLACTSETDATA *set, CLACT_WORK_EX *actwork,
		const VecFx32 *vec, u32 drawtype, int celltrans,
		u32 char_id, u32 pltt_id, u32 cell_id, u32 cellanm_id, int bg_pri, int act_pri );
extern void ClActDelete( CLACT_WORK_EX *actwork );
extern void ClActMatrixGet( CLACT_WORK_PTR act, VecFx32 *mtx );
extern void ClActScaleGet( CLACT_WORK_PTR act, VecFx32 *scale );

#endif //SLOT_MAIN_H_FILE
