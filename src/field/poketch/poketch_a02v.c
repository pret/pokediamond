//============================================================================================
/**
 * @file	poketch_a02_v.c
 * @bfief	ポケッチ（アプリNo02 = 電卓）　描画
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#include "common.h"
#include "system\lib_pack.h"
#include "system\fontproc.h"

#include "field\poketch.h"

#include "poketch_prv.h"
#include "poketch_view.h"
#include "poketch_a02.h"


//====================================================
// graphic files
//====================================================

//==============================================================
// consts
//==============================================================
#define CMD_STORE_MAX	(8)
#define USE_BG_FRAME	(GF_BGL_FRAME2_S)

//==============================================================
// Work
//==============================================================
struct _POKETCH_A02_VIEWWORK {
	const  POKETCH_A02_VIEW_PARAM  *vpara;
	GF_BGL_INI*                     bgl;
	POKETCH_CMD_STORE		cmd_store[ CMD_STORE_HEADER_SIZE + CMD_STORE_MAX ];

	u16 dispnum_ary[ DISP_COLUMN_MAX + 4 ];		// 多少、多めに。

	u16 btnscrn[BUTTON_ID_MAX][ 8 * 4 ];		// 4*4のボタンが多いが、最大サイズで
};



//====================================================
// bg param
//====================================================
enum {
	BASE_PALNO = 0,
	BASE_CHARNO = 0,

	CHAR_BASE_XSIZE = 40,

	CHARNO_FREENUM_START = 0x05,
	CHARNO_PUSHNUM_START = 0x55,
	CHARNO_DISPNUM_START = 0xa5,
	CHARNO_DISPNUM_SPACE = 0x2b,

	CHARNO_FREEBTN_FRAME = 0xf8,
	CHARNO_PUSHBTN_FRAME = 0xfb,
	CHARNO_FREEBTN_BTM_FRAME = 0xfe,
	CHARNO_PUSHBTN_BTM_FRAME = 0x101,

	CHARNO_QUESTION = 0xa3,

	CHARNO_FREEBTN_FRAME_LT    = CHARNO_FREEBTN_FRAME,
	CHARNO_FREEBTN_FRAME_TOP   = CHARNO_FREEBTN_FRAME+1,
	CHARNO_FREEBTN_FRAME_RT    = CHARNO_FREEBTN_FRAME+2,
	CHARNO_FREEBTN_FRAME_LEFT  = CHARNO_FREEBTN_FRAME+CHAR_BASE_XSIZE,
	CHARNO_FREEBTN_FRAME_SPC   = CHARNO_FREEBTN_FRAME+CHAR_BASE_XSIZE+1,
	CHARNO_FREEBTN_FRAME_RIGHT = CHARNO_FREEBTN_FRAME+CHAR_BASE_XSIZE+2,
	CHARNO_FREEBTN_FRAME_LB    = CHARNO_FREEBTN_FRAME+(CHAR_BASE_XSIZE*2),
	CHARNO_FREEBTN_FRAME_BOTTOM= CHARNO_FREEBTN_FRAME+(CHAR_BASE_XSIZE*2)+1,
	CHARNO_FREEBTN_FRAME_RB    = CHARNO_FREEBTN_FRAME+(CHAR_BASE_XSIZE*2)+2,

	CHARNO_PUSHBTN_FRAME_LT    = CHARNO_PUSHBTN_FRAME,
	CHARNO_PUSHBTN_FRAME_TOP   = CHARNO_PUSHBTN_FRAME+1,
	CHARNO_PUSHBTN_FRAME_RT    = CHARNO_PUSHBTN_FRAME+2,
	CHARNO_PUSHBTN_FRAME_LEFT  = CHARNO_PUSHBTN_FRAME+CHAR_BASE_XSIZE,
	CHARNO_PUSHBTN_FRAME_SPC   = CHARNO_PUSHBTN_FRAME+CHAR_BASE_XSIZE+1,
	CHARNO_PUSHBTN_FRAME_RIGHT = CHARNO_PUSHBTN_FRAME+CHAR_BASE_XSIZE+2,
	CHARNO_PUSHBTN_FRAME_LB    = CHARNO_PUSHBTN_FRAME+(CHAR_BASE_XSIZE*2),
	CHARNO_PUSHBTN_FRAME_BOTTOM= CHARNO_PUSHBTN_FRAME+(CHAR_BASE_XSIZE*2)+1,
	CHARNO_PUSHBTN_FRAME_RB    = CHARNO_PUSHBTN_FRAME+(CHAR_BASE_XSIZE*2)+2,

	CHARNO_FREEBTN_BTM_FRAME_LT    = CHARNO_FREEBTN_BTM_FRAME,
	CHARNO_FREEBTN_BTM_FRAME_TOP   = CHARNO_FREEBTN_BTM_FRAME+1,
	CHARNO_FREEBTN_BTM_FRAME_RT    = CHARNO_FREEBTN_BTM_FRAME+2,
	CHARNO_FREEBTN_BTM_FRAME_LEFT  = CHARNO_FREEBTN_BTM_FRAME+CHAR_BASE_XSIZE,
	CHARNO_FREEBTN_BTM_FRAME_SPC   = CHARNO_FREEBTN_BTM_FRAME+CHAR_BASE_XSIZE+1,
	CHARNO_FREEBTN_BTM_FRAME_RIGHT = CHARNO_FREEBTN_BTM_FRAME+CHAR_BASE_XSIZE+2,
	CHARNO_FREEBTN_BTM_FRAME_LB    = CHARNO_FREEBTN_BTM_FRAME+(CHAR_BASE_XSIZE*2),
	CHARNO_FREEBTN_BTM_FRAME_BOTTOM= CHARNO_FREEBTN_BTM_FRAME+(CHAR_BASE_XSIZE*2)+1,
	CHARNO_FREEBTN_BTM_FRAME_RB    = CHARNO_FREEBTN_BTM_FRAME+(CHAR_BASE_XSIZE*2)+2,

	CHARNO_PUSHBTN_BTM_FRAME_LT    = CHARNO_PUSHBTN_BTM_FRAME,
	CHARNO_PUSHBTN_BTM_FRAME_TOP   = CHARNO_PUSHBTN_BTM_FRAME+1,
	CHARNO_PUSHBTN_BTM_FRAME_RT    = CHARNO_PUSHBTN_BTM_FRAME+2,
	CHARNO_PUSHBTN_BTM_FRAME_LEFT  = CHARNO_PUSHBTN_BTM_FRAME+CHAR_BASE_XSIZE,
	CHARNO_PUSHBTN_BTM_FRAME_SPC   = CHARNO_PUSHBTN_BTM_FRAME+CHAR_BASE_XSIZE+1,
	CHARNO_PUSHBTN_BTM_FRAME_RIGHT = CHARNO_PUSHBTN_BTM_FRAME+CHAR_BASE_XSIZE+2,
	CHARNO_PUSHBTN_BTM_FRAME_LB    = CHARNO_PUSHBTN_BTM_FRAME+(CHAR_BASE_XSIZE*2),
	CHARNO_PUSHBTN_BTM_FRAME_BOTTOM= CHARNO_PUSHBTN_BTM_FRAME+(CHAR_BASE_XSIZE*2)+1,
	CHARNO_PUSHBTN_BTM_FRAME_RB    = CHARNO_PUSHBTN_BTM_FRAME+(CHAR_BASE_XSIZE*2)+2,


	CHAR_BUTTON_XSIZE = 2,
	CHAR_BUTTON_YSIZE = 2,


	SCRN_OP_XPOS = 3,
	SCRN_OP_YPOS = 3,
	SCRN_OP_WIDTH = 2,
	SCRN_OP_HEIGHT = 2,

	CHARNO_OP_NULL = 0x29,
	CHARNO_OP_TOP = 0xf0,
};


//====================================================
// 各種ボタンのスクリーンデータ
//====================================================
#define NUM_CHARNO_U(n)		((CHARNO_PUSHNUM_START+(n)*2))
#define NUM_CHARNO_D(n)		((CHARNO_PUSHNUM_START+CHAR_BASE_XSIZE+(n)*2))

static const u16 btnscrn_0[8 * 4] = {
	CHARNO_PUSHBTN_FRAME_LT,  CHARNO_PUSHBTN_FRAME_TOP, CHARNO_PUSHBTN_FRAME_TOP, CHARNO_PUSHBTN_FRAME_TOP,
	CHARNO_PUSHBTN_FRAME_TOP, CHARNO_PUSHBTN_FRAME_TOP, CHARNO_PUSHBTN_FRAME_TOP, CHARNO_PUSHBTN_FRAME_RT,

	CHARNO_PUSHBTN_FRAME_LEFT, NUM_CHARNO_U(0), NUM_CHARNO_U(0)+1, CHARNO_PUSHBTN_FRAME_SPC,
	CHARNO_PUSHBTN_FRAME_SPC, CHARNO_PUSHBTN_FRAME_SPC, CHARNO_PUSHBTN_FRAME_SPC, CHARNO_PUSHBTN_FRAME_RIGHT,

	CHARNO_PUSHBTN_FRAME_LEFT, NUM_CHARNO_D(0), NUM_CHARNO_D(0)+1, CHARNO_PUSHBTN_FRAME_SPC,
	CHARNO_PUSHBTN_FRAME_SPC, CHARNO_PUSHBTN_FRAME_SPC, CHARNO_PUSHBTN_FRAME_SPC, CHARNO_PUSHBTN_FRAME_RIGHT,

	CHARNO_PUSHBTN_BTM_FRAME_LB, CHARNO_PUSHBTN_BTM_FRAME_BOTTOM, CHARNO_PUSHBTN_BTM_FRAME_BOTTOM, CHARNO_PUSHBTN_BTM_FRAME_BOTTOM,
	CHARNO_PUSHBTN_BTM_FRAME_BOTTOM, CHARNO_PUSHBTN_BTM_FRAME_BOTTOM, CHARNO_PUSHBTN_BTM_FRAME_BOTTOM, CHARNO_PUSHBTN_BTM_FRAME_RB,
};

static const u16 btnscrn_1[4 * 4] = {
	CHARNO_PUSHBTN_FRAME_LT,  CHARNO_PUSHBTN_FRAME_TOP, CHARNO_PUSHBTN_FRAME_TOP, CHARNO_PUSHBTN_FRAME_RT,
	CHARNO_PUSHBTN_FRAME_LEFT, NUM_CHARNO_U(1), NUM_CHARNO_U(1)+1, CHARNO_PUSHBTN_FRAME_RIGHT,
	CHARNO_PUSHBTN_FRAME_LEFT, NUM_CHARNO_D(1), NUM_CHARNO_D(1)+1, CHARNO_PUSHBTN_FRAME_RIGHT,
	CHARNO_PUSHBTN_FRAME_LB, CHARNO_PUSHBTN_FRAME_BOTTOM, CHARNO_PUSHBTN_FRAME_BOTTOM, CHARNO_PUSHBTN_FRAME_RB,
};
static const u16 btnscrn_2[4 * 4] = {
	CHARNO_PUSHBTN_FRAME_LT,  CHARNO_PUSHBTN_FRAME_TOP, CHARNO_PUSHBTN_FRAME_TOP, CHARNO_PUSHBTN_FRAME_RT,
	CHARNO_PUSHBTN_FRAME_LEFT, NUM_CHARNO_U(2), NUM_CHARNO_U(2)+1, CHARNO_PUSHBTN_FRAME_RIGHT,
	CHARNO_PUSHBTN_FRAME_LEFT, NUM_CHARNO_D(2), NUM_CHARNO_D(2)+1, CHARNO_PUSHBTN_FRAME_RIGHT,
	CHARNO_PUSHBTN_FRAME_LB, CHARNO_PUSHBTN_FRAME_BOTTOM, CHARNO_PUSHBTN_FRAME_BOTTOM, CHARNO_PUSHBTN_FRAME_RB,
};
static const u16 btnscrn_3[4 * 4] = {
	CHARNO_PUSHBTN_FRAME_LT,  CHARNO_PUSHBTN_FRAME_TOP, CHARNO_PUSHBTN_FRAME_TOP, CHARNO_PUSHBTN_FRAME_RT,
	CHARNO_PUSHBTN_FRAME_LEFT, NUM_CHARNO_U(3), NUM_CHARNO_U(3)+1, CHARNO_PUSHBTN_FRAME_RIGHT,
	CHARNO_PUSHBTN_FRAME_LEFT, NUM_CHARNO_D(3), NUM_CHARNO_D(3)+1, CHARNO_PUSHBTN_FRAME_RIGHT,
	CHARNO_PUSHBTN_FRAME_LB, CHARNO_PUSHBTN_FRAME_BOTTOM, CHARNO_PUSHBTN_FRAME_BOTTOM, CHARNO_PUSHBTN_FRAME_RB,
};
static const u16 btnscrn_4[4 * 4] = {
	CHARNO_PUSHBTN_FRAME_LT,  CHARNO_PUSHBTN_FRAME_TOP, CHARNO_PUSHBTN_FRAME_TOP, CHARNO_PUSHBTN_FRAME_RT,
	CHARNO_PUSHBTN_FRAME_LEFT, NUM_CHARNO_U(4), NUM_CHARNO_U(4)+1, CHARNO_PUSHBTN_FRAME_RIGHT,
	CHARNO_PUSHBTN_FRAME_LEFT, NUM_CHARNO_D(4), NUM_CHARNO_D(4)+1, CHARNO_PUSHBTN_FRAME_RIGHT,
	CHARNO_PUSHBTN_FRAME_LB, CHARNO_PUSHBTN_FRAME_BOTTOM, CHARNO_PUSHBTN_FRAME_BOTTOM, CHARNO_PUSHBTN_FRAME_RB,
};
static const u16 btnscrn_5[4 * 4] = {
	CHARNO_PUSHBTN_FRAME_LT,  CHARNO_PUSHBTN_FRAME_TOP, CHARNO_PUSHBTN_FRAME_TOP, CHARNO_PUSHBTN_FRAME_RT,
	CHARNO_PUSHBTN_FRAME_LEFT, NUM_CHARNO_U(5), NUM_CHARNO_U(5)+1, CHARNO_PUSHBTN_FRAME_RIGHT,
	CHARNO_PUSHBTN_FRAME_LEFT, NUM_CHARNO_D(5), NUM_CHARNO_D(5)+1, CHARNO_PUSHBTN_FRAME_RIGHT,
	CHARNO_PUSHBTN_FRAME_LB, CHARNO_PUSHBTN_FRAME_BOTTOM, CHARNO_PUSHBTN_FRAME_BOTTOM, CHARNO_PUSHBTN_FRAME_RB,
};
static const u16 btnscrn_6[4 * 4] = {
	CHARNO_PUSHBTN_FRAME_LT,  CHARNO_PUSHBTN_FRAME_TOP, CHARNO_PUSHBTN_FRAME_TOP, CHARNO_PUSHBTN_FRAME_RT,
	CHARNO_PUSHBTN_FRAME_LEFT, NUM_CHARNO_U(6), NUM_CHARNO_U(6)+1, CHARNO_PUSHBTN_FRAME_RIGHT,
	CHARNO_PUSHBTN_FRAME_LEFT, NUM_CHARNO_D(6), NUM_CHARNO_D(6)+1, CHARNO_PUSHBTN_FRAME_RIGHT,
	CHARNO_PUSHBTN_FRAME_LB, CHARNO_PUSHBTN_FRAME_BOTTOM, CHARNO_PUSHBTN_FRAME_BOTTOM, CHARNO_PUSHBTN_FRAME_RB,
};
static const u16 btnscrn_7[4 * 4] = {
	CHARNO_PUSHBTN_FRAME_LT,  CHARNO_PUSHBTN_FRAME_TOP, CHARNO_PUSHBTN_FRAME_TOP, CHARNO_PUSHBTN_FRAME_RT,
	CHARNO_PUSHBTN_FRAME_LEFT, NUM_CHARNO_U(7), NUM_CHARNO_U(7)+1, CHARNO_PUSHBTN_FRAME_RIGHT,
	CHARNO_PUSHBTN_FRAME_LEFT, NUM_CHARNO_D(7), NUM_CHARNO_D(7)+1, CHARNO_PUSHBTN_FRAME_RIGHT,
	CHARNO_PUSHBTN_FRAME_LB, CHARNO_PUSHBTN_FRAME_BOTTOM, CHARNO_PUSHBTN_FRAME_BOTTOM, CHARNO_PUSHBTN_FRAME_RB,
};
static const u16 btnscrn_8[4 * 4] = {
	CHARNO_PUSHBTN_FRAME_LT,  CHARNO_PUSHBTN_FRAME_TOP, CHARNO_PUSHBTN_FRAME_TOP, CHARNO_PUSHBTN_FRAME_RT,
	CHARNO_PUSHBTN_FRAME_LEFT, NUM_CHARNO_U(8), NUM_CHARNO_U(8)+1, CHARNO_PUSHBTN_FRAME_RIGHT,
	CHARNO_PUSHBTN_FRAME_LEFT, NUM_CHARNO_D(8), NUM_CHARNO_D(8)+1, CHARNO_PUSHBTN_FRAME_RIGHT,
	CHARNO_PUSHBTN_FRAME_LB, CHARNO_PUSHBTN_FRAME_BOTTOM, CHARNO_PUSHBTN_FRAME_BOTTOM, CHARNO_PUSHBTN_FRAME_RB,
};
static const u16 btnscrn_9[4 * 4] = {
	CHARNO_PUSHBTN_FRAME_LT,  CHARNO_PUSHBTN_FRAME_TOP, CHARNO_PUSHBTN_FRAME_TOP, CHARNO_PUSHBTN_FRAME_RT,
	CHARNO_PUSHBTN_FRAME_LEFT, NUM_CHARNO_U(9), NUM_CHARNO_U(9)+1, CHARNO_PUSHBTN_FRAME_RIGHT,
	CHARNO_PUSHBTN_FRAME_LEFT, NUM_CHARNO_D(9), NUM_CHARNO_D(9)+1, CHARNO_PUSHBTN_FRAME_RIGHT,
	CHARNO_PUSHBTN_FRAME_LB, CHARNO_PUSHBTN_FRAME_BOTTOM, CHARNO_PUSHBTN_FRAME_BOTTOM, CHARNO_PUSHBTN_FRAME_RB,
};
static const u16 btnscrn_dot[4 * 4] = {
	CHARNO_PUSHBTN_FRAME_LT,  CHARNO_PUSHBTN_FRAME_TOP, CHARNO_PUSHBTN_FRAME_TOP, CHARNO_PUSHBTN_FRAME_RT,
	CHARNO_PUSHBTN_FRAME_LEFT, NUM_CHARNO_U(BUTTON_DOT), NUM_CHARNO_U(BUTTON_DOT)+1, CHARNO_PUSHBTN_FRAME_RIGHT,
	CHARNO_PUSHBTN_FRAME_LEFT, NUM_CHARNO_D(BUTTON_DOT), NUM_CHARNO_D(BUTTON_DOT)+1, CHARNO_PUSHBTN_FRAME_RIGHT,
	CHARNO_PUSHBTN_BTM_FRAME_LB, CHARNO_PUSHBTN_BTM_FRAME_BOTTOM, CHARNO_PUSHBTN_BTM_FRAME_BOTTOM, CHARNO_PUSHBTN_BTM_FRAME_RB,
};
static const u16 btnscrn_clear[8 * 4] = {
	CHARNO_PUSHBTN_FRAME_LT,  CHARNO_PUSHBTN_FRAME_TOP, CHARNO_PUSHBTN_FRAME_TOP, CHARNO_PUSHBTN_FRAME_TOP,
	CHARNO_PUSHBTN_FRAME_TOP, CHARNO_PUSHBTN_FRAME_TOP, CHARNO_PUSHBTN_FRAME_TOP, CHARNO_PUSHBTN_FRAME_RT,

	CHARNO_PUSHBTN_FRAME_LEFT, NUM_CHARNO_U(BUTTON_CLEAR), NUM_CHARNO_U(BUTTON_CLEAR)+1, CHARNO_PUSHBTN_FRAME_SPC,
	CHARNO_PUSHBTN_FRAME_SPC, CHARNO_PUSHBTN_FRAME_SPC, CHARNO_PUSHBTN_FRAME_SPC, CHARNO_PUSHBTN_FRAME_RIGHT,

	CHARNO_PUSHBTN_FRAME_LEFT, NUM_CHARNO_D(BUTTON_CLEAR), NUM_CHARNO_D(BUTTON_CLEAR)+1, CHARNO_PUSHBTN_FRAME_SPC,
	CHARNO_PUSHBTN_FRAME_SPC, CHARNO_PUSHBTN_FRAME_SPC, CHARNO_PUSHBTN_FRAME_SPC, CHARNO_PUSHBTN_FRAME_RIGHT,

	CHARNO_PUSHBTN_FRAME_LB, CHARNO_PUSHBTN_FRAME_BOTTOM, CHARNO_PUSHBTN_FRAME_BOTTOM, CHARNO_PUSHBTN_FRAME_BOTTOM,
	CHARNO_PUSHBTN_FRAME_BOTTOM, CHARNO_PUSHBTN_FRAME_BOTTOM, CHARNO_PUSHBTN_FRAME_BOTTOM, CHARNO_PUSHBTN_FRAME_RB,
};
static const u16 btnscrn_plus[4 * 4] = {
	CHARNO_PUSHBTN_FRAME_LT,  CHARNO_PUSHBTN_FRAME_TOP, CHARNO_PUSHBTN_FRAME_TOP, CHARNO_PUSHBTN_FRAME_RT,
	CHARNO_PUSHBTN_FRAME_LEFT, NUM_CHARNO_U(BUTTON_PLUS), NUM_CHARNO_U(BUTTON_PLUS)+1, CHARNO_PUSHBTN_FRAME_RIGHT,
	CHARNO_PUSHBTN_FRAME_LEFT, NUM_CHARNO_D(BUTTON_PLUS), NUM_CHARNO_D(BUTTON_PLUS)+1, CHARNO_PUSHBTN_FRAME_RIGHT,
	CHARNO_PUSHBTN_FRAME_LB, CHARNO_PUSHBTN_FRAME_BOTTOM, CHARNO_PUSHBTN_FRAME_BOTTOM, CHARNO_PUSHBTN_FRAME_RB,
};
static const u16 btnscrn_minus[4 * 4] = {
	CHARNO_PUSHBTN_FRAME_LT,  CHARNO_PUSHBTN_FRAME_TOP, CHARNO_PUSHBTN_FRAME_TOP, CHARNO_PUSHBTN_FRAME_RT,
	CHARNO_PUSHBTN_FRAME_LEFT, NUM_CHARNO_U(BUTTON_MINUS), NUM_CHARNO_U(BUTTON_MINUS)+1, CHARNO_PUSHBTN_FRAME_RIGHT,
	CHARNO_PUSHBTN_FRAME_LEFT, NUM_CHARNO_D(BUTTON_MINUS), NUM_CHARNO_D(BUTTON_MINUS)+1, CHARNO_PUSHBTN_FRAME_RIGHT,
	CHARNO_PUSHBTN_FRAME_LB, CHARNO_PUSHBTN_FRAME_BOTTOM, CHARNO_PUSHBTN_FRAME_BOTTOM, CHARNO_PUSHBTN_FRAME_RB,
};
static const u16 btnscrn_mul[4 * 4] = {
	CHARNO_PUSHBTN_FRAME_LT,  CHARNO_PUSHBTN_FRAME_TOP, CHARNO_PUSHBTN_FRAME_TOP, CHARNO_PUSHBTN_FRAME_RT,
	CHARNO_PUSHBTN_FRAME_LEFT, NUM_CHARNO_U(BUTTON_MUL), NUM_CHARNO_U(BUTTON_MUL)+1, CHARNO_PUSHBTN_FRAME_RIGHT,
	CHARNO_PUSHBTN_FRAME_LEFT, NUM_CHARNO_D(BUTTON_MUL), NUM_CHARNO_D(BUTTON_MUL)+1, CHARNO_PUSHBTN_FRAME_RIGHT,
	CHARNO_PUSHBTN_FRAME_LB, CHARNO_PUSHBTN_FRAME_BOTTOM, CHARNO_PUSHBTN_FRAME_BOTTOM, CHARNO_PUSHBTN_FRAME_RB,
};
static const u16 btnscrn_div[4 * 4] = {
	CHARNO_PUSHBTN_FRAME_LT,  CHARNO_PUSHBTN_FRAME_TOP, CHARNO_PUSHBTN_FRAME_TOP, CHARNO_PUSHBTN_FRAME_RT,
	CHARNO_PUSHBTN_FRAME_LEFT, NUM_CHARNO_U(BUTTON_DIV), NUM_CHARNO_U(BUTTON_DIV)+1, CHARNO_PUSHBTN_FRAME_RIGHT,
	CHARNO_PUSHBTN_FRAME_LEFT, NUM_CHARNO_D(BUTTON_DIV), NUM_CHARNO_D(BUTTON_DIV)+1, CHARNO_PUSHBTN_FRAME_RIGHT,
	CHARNO_PUSHBTN_FRAME_LB, CHARNO_PUSHBTN_FRAME_BOTTOM, CHARNO_PUSHBTN_FRAME_BOTTOM, CHARNO_PUSHBTN_FRAME_RB,
};
static const u16 btnscrn_eq[8 * 4] = {
	CHARNO_PUSHBTN_FRAME_LT,  CHARNO_PUSHBTN_FRAME_TOP, CHARNO_PUSHBTN_FRAME_TOP, CHARNO_PUSHBTN_FRAME_TOP,
	CHARNO_PUSHBTN_FRAME_TOP, CHARNO_PUSHBTN_FRAME_TOP, CHARNO_PUSHBTN_FRAME_TOP, CHARNO_PUSHBTN_FRAME_RT,

	CHARNO_PUSHBTN_FRAME_LEFT, NUM_CHARNO_U(BUTTON_EQ), NUM_CHARNO_U(BUTTON_EQ)+1, CHARNO_PUSHBTN_FRAME_SPC,
	CHARNO_PUSHBTN_FRAME_SPC, CHARNO_PUSHBTN_FRAME_SPC, CHARNO_PUSHBTN_FRAME_SPC, CHARNO_PUSHBTN_FRAME_RIGHT,

	CHARNO_PUSHBTN_FRAME_LEFT, NUM_CHARNO_D(BUTTON_EQ), NUM_CHARNO_D(BUTTON_EQ)+1, CHARNO_PUSHBTN_FRAME_SPC,
	CHARNO_PUSHBTN_FRAME_SPC, CHARNO_PUSHBTN_FRAME_SPC, CHARNO_PUSHBTN_FRAME_SPC, CHARNO_PUSHBTN_FRAME_RIGHT,

	CHARNO_PUSHBTN_BTM_FRAME_LB, CHARNO_PUSHBTN_BTM_FRAME_BOTTOM, CHARNO_PUSHBTN_BTM_FRAME_BOTTOM, CHARNO_PUSHBTN_BTM_FRAME_BOTTOM,
	CHARNO_PUSHBTN_BTM_FRAME_BOTTOM, CHARNO_PUSHBTN_BTM_FRAME_BOTTOM, CHARNO_PUSHBTN_BTM_FRAME_BOTTOM, CHARNO_PUSHBTN_BTM_FRAME_RB,
};

static const u16 * const PushButtonScreen[] = {
	btnscrn_0,
	btnscrn_1,
	btnscrn_2,
	btnscrn_3,
	btnscrn_4,
	btnscrn_5,
	btnscrn_6,
	btnscrn_7,
	btnscrn_8,
	btnscrn_9,
	btnscrn_dot,
	btnscrn_minus,
	btnscrn_plus,
	btnscrn_mul,
	btnscrn_div,
	btnscrn_eq,
	btnscrn_clear,
};


//====================================================
// enum BUTTON_ID に対応したそれぞれのスクリーン位置
//====================================================
static const struct {
	u8 x;
	u8 y;
	u8 w;
	u8 h;
}ButtonScrnPos[] = {
	{ 4, 18, 8, 4 },	// 0
	{ 4, 14, 4, 4 },	// 1
	{ 8, 14, 4, 4 },	// 2
	{12, 14, 4, 4 },	// 3
	{ 4, 10, 4, 4 },	// 4
	{ 8, 10, 4, 4 },	// 5
	{12, 10, 4, 4 },	// 6
	{ 4,  6, 4, 4 },	// 7
	{ 8,  6, 4, 4 },	// 8
	{12,  6, 4, 4 },	// 9
	{12, 18, 4, 4 },	// .
	{20, 10, 4, 4 },	// -
	{16, 10, 4, 4 },	// +
	{16, 14, 4, 4 },	// *
	{20, 14, 4, 4 },	// /
	{16, 18, 8, 4 },	// =
	{16,  6, 8, 4 },	// Clear
};


//==============================================================
// Prototype
//==============================================================
static void DeleteCommand(POKETCH_CMD_WORK *cwk);
static void CmdInit(TCB_PTR tcb, void *wk_ptr);
static void SaveFreeBtnScrn(POKETCH_A02_VIEWWORK *wk);
static void CmdButtonPush(TCB_PTR tcb, void *wk_adrs);
static void CmdButtonFree(TCB_PTR tcb, void *wk_adrs);
static void CmdDispNum1(TCB_PTR tcb, void *wk_adrs);
static void CmdDispNum1_OpClear(TCB_PTR tcb, void *wk_adrs);
static void CmdDispNum2(TCB_PTR tcb, void *wk_adrs);
static void CmdDispAns(TCB_PTR tcb, void *wk_adrs);
static void CmdDispAnsOp(TCB_PTR tcb, void *wk_adrs);
static void CmdOverFlow( TCB_PTR tcb, void *wk_adrs );
static void CmdOperation( TCB_PTR tcb, void *wk_adrs );
static void DispOpCommon( GF_BGL_INI* bgl, const POKETCH_A02_VIEW_PARAM* vpara );
static void ClearOpScrn( GF_BGL_INI* bgl );
static void CmdQuit(TCB_PTR tcb, void *wk_ptr);
static void DispNumCommon( GF_BGL_INI* bgl, const u16 *ary );

extern struct _POKETCH_WORK* GetPoketchMainWorkPtr(void);



//------------------------------------------------------------------
/**
 * ワーク確保
 *
 * @param   wk_ptr		確保したワークアドレスを保存するポインタのアドレス
 *
 */
//------------------------------------------------------------------
BOOL Poketch_A02_SetViewWork(POKETCH_A02_VIEWWORK **wk_ptr, const POKETCH_A02_VIEW_PARAM *vpara, GF_BGL_INI* bgl)
{
	POKETCH_A02_VIEWWORK *wk = (POKETCH_A02_VIEWWORK*)sys_AllocMemory( POKETCH_APP_VIEW_HEAPID, sizeof(POKETCH_A02_VIEWWORK));

	if(wk != NULL)
	{
		wk->vpara = vpara;
		wk->bgl = bgl;

		PoketchViewTool_CmdStoreInit( wk->cmd_store, CMD_STORE_MAX );
		*wk_ptr = wk;

		return TRUE;
	}

	return FALSE;
}

//------------------------------------------------------------------
/**
 * ワーク削除
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
void Poketch_AOO_DeleteViewWork( POKETCH_A02_VIEWWORK* wk )
{
	if( wk )
	{
		sys_FreeMemoryEz( wk );
	}
}

//------------------------------------------------------------------
/**
 * @brief	コマンドテーブル
 */
//------------------------------------------------------------------

static const POKETCH_VIEW_CMD CmdTbl[] = {
	{ CMD_INIT, CmdInit, 0 },
	{ CMD_BUTTON_PUSH, CmdButtonPush, 0 },
	{ CMD_BUTTON_FREE, CmdButtonFree, 0 },
	{ CMD_DISPNUM_1,   CmdDispNum1,   0 },
	{ CMD_DISPNUM_1_OPCLEAR,   CmdDispNum1_OpClear,   0 },
	{ CMD_DISPNUM_2,   CmdDispNum2,   0 },
	{ CMD_DISPNUM_ANS, CmdDispAns,    0 },
	{ CMD_DISPNUM_ANS_OP, CmdDispAnsOp,   0 },
	{ CMD_OVERFLOW,    CmdOverFlow,   0 },
	{ CMD_OPERATION,   CmdOperation,  0 },
	{ CMD_QUIT, CmdQuit, 0 },
	{ 0, NULL, 0 },
};


//------------------------------------------------------------------
/**
 * 描画コマンドのセット
 *
 * @param   cmd		コマンド
 * @param   view_wk_adrs	ワーク領域アドレス
 *
 */
//------------------------------------------------------------------
void Poketch_A02_SetViewCommand(POKETCH_A02_VIEWWORK *wk, u32 cmd)
{
	PoketchViewTool_SetCommand(CmdTbl, cmd, wk, wk->vpara, wk->cmd_store, POKETCH_GRAPHIC_TASKPRI, POKETCH_APP_VIEW_HEAPID);
}
//------------------------------------------------------------------
/**
 * 描画コマンドの終了待ち（単発）
 *
 * @param   cmd			コマンド
 *
 * @retval  BOOL		TRUEで終了
 */
//------------------------------------------------------------------
BOOL Poketch_A02_WaitViewCommand(POKETCH_A02_VIEWWORK *wk, u32 cmd)
{
	return PoketchViewTool_WaitCommand(wk->cmd_store, cmd);
}
//------------------------------------------------------------------
/**
 * 描画コマンドの終了待ち（全部）
 *
 * @retval  BOOL		TRUEで終了
 */
//------------------------------------------------------------------
BOOL Poketch_A02_WaitViewCommandAll(POKETCH_A02_VIEWWORK *wk)
{
	return PoketchViewTool_WaitCommandAll(wk->cmd_store);
}



//------------------------------------------------------------------
/**
 * コマンド削除
 *
 * @param   cwk		コマンドワーク
 *
 */
//------------------------------------------------------------------
static void DeleteCommand(POKETCH_CMD_WORK *cwk)
{
	POKETCH_A02_VIEWWORK *wk = PoketchViewTool_GetViewWork(cwk);
	PoketchViewTool_DelCommand( wk->cmd_store, cwk );
}

//------------------------------------------------------------------
/**
 * コマンド：画面構築
 *
 * @param   tcb			TCBポインタ
 * @param   wk_ptr		ワークポインタ
 *
 */
//------------------------------------------------------------------
static void CmdInit(TCB_PTR tcb, void *wk_ptr)
{
	static const GF_BGL_BGCNT_HEADER header = {
		0, 0, 0x800, 0,		// scrX, scrY, scrbufSize, scrbufofs,
		GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
		GX_BG_SCRBASE_0x7000, GX_BG_CHARBASE_0x00000,
		GX_BG_EXTPLTT_01, 2, 0, 0, FALSE	// pal, pri, areaover, dmy, mosaic
	};

	GXSDispCnt dispcnt;
	const POKETCH_A02_VIEW_PARAM* vpara;
	POKETCH_A02_VIEWWORK*  vwk;
	u32 palDataIdx;

	vpara = PoketchViewTool_GetViewParam( wk_ptr );
	vwk = PoketchViewTool_GetViewWork( wk_ptr );

	GF_BGL_BGControlSet( vwk->bgl, USE_BG_FRAME, &header, GF_BGL_MODE_TEXT );

	ArcUtil_BgCharSet(ARC_POKETCH_IMG, NARC_poketch_dentaku_ncgr, vwk->bgl,
							USE_BG_FRAME, 0, 0, TRUE, POKETCH_APP_VIEW_HEAPID);
	ArcUtil_ScrnSet(ARC_POKETCH_IMG, NARC_poketch_dentaku_nscr, vwk->bgl,
							USE_BG_FRAME, 0, 0, TRUE, POKETCH_APP_VIEW_HEAPID);

	SaveFreeBtnScrn( vwk );

	PoketchView_SetBaseColorPalette(0,0);

	GF_BGL_LoadScreenReq( vwk->bgl, USE_BG_FRAME );

	dispcnt = GXS_GetDispCnt();
	GXS_SetVisiblePlane(dispcnt.visiblePlane | GX_PLANEMASK_BG2);

	DeleteCommand( wk_ptr );

}
//------------------------------------------------------------------
/**
 * 各ボタン解放時のスクリーンデータをワークにコピーしておく
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void SaveFreeBtnScrn(POKETCH_A02_VIEWWORK *wk)
{
	u16 *scrn;
	u32 i, x, y, p;

	scrn = GF_BGL_ScreenAdrsGet( wk->bgl, USE_BG_FRAME );

	for(i = 0; i < NELEMS(ButtonScrnPos); i++)
	{
		p = 0;
		for(y = ButtonScrnPos[i].y; y < ButtonScrnPos[i].y + ButtonScrnPos[i].h; y++)
		{
			for(x = ButtonScrnPos[i].x; x < ButtonScrnPos[i].x + ButtonScrnPos[i].w; x++)
			{
				wk->btnscrn[i][p++] = scrn[ y * 32 + x ];
			}
		}
	}
}

//------------------------------------------------------------------
/**
 * コマンド：ボタン押した状態を描画
 *
 * @param   tcb			TCBポインタ
 * @param   wk_ptr		ワークポインタ
 *
 */
//------------------------------------------------------------------
static void CmdButtonPush(TCB_PTR tcb, void *wk_adrs)
{
	const POKETCH_A02_VIEW_PARAM* vpara;
	POKETCH_A02_VIEWWORK*  vwk;
	u32 id;

	vpara = PoketchViewTool_GetViewParam( wk_adrs );
	vwk = PoketchViewTool_GetViewWork( wk_adrs );
	id = vpara->btn_id;

	PoketchSePlay( POKETCH_SE_CALC_BUTTON );

	GF_BGL_ScrWrite( vwk->bgl, USE_BG_FRAME, PushButtonScreen[ id ],
			ButtonScrnPos[ id ].x, ButtonScrnPos[ id ].y, 
			ButtonScrnPos[ id ].w, ButtonScrnPos[ id ].h
			);

	GF_BGL_LoadScreenReq( vwk->bgl, USE_BG_FRAME );
	DeleteCommand( wk_adrs );

}

//------------------------------------------------------------------
/**
 * コマンド：ボタン離した状態に戻す
 *
 * @param   tcb			TCBポインタ
 * @param   wk_ptr		ワークポインタ
 *
 */
//------------------------------------------------------------------
static void CmdButtonFree(TCB_PTR tcb, void *wk_adrs)
{
	const POKETCH_A02_VIEW_PARAM* vpara;
	POKETCH_A02_VIEWWORK *vwk;
	u32 id;

	vpara = PoketchViewTool_GetViewParam( wk_adrs );
	id = vpara->btn_id;
	vwk = PoketchViewTool_GetViewWork( wk_adrs );

	GF_BGL_ScrWrite( vwk->bgl, USE_BG_FRAME, vwk->btnscrn[ id ],
			ButtonScrnPos[ id ].x, ButtonScrnPos[ id ].y, 
			ButtonScrnPos[ id ].w, ButtonScrnPos[ id ].h
			);

	GF_BGL_LoadScreenReq( vwk->bgl, USE_BG_FRAME );
	DeleteCommand( wk_adrs );
}

//------------------------------------------------------------------
/**
 * コマンド：数値１をデジタル部に描画
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdDispNum1(TCB_PTR tcb, void *wk_adrs)
{
	const POKETCH_A02_VIEW_PARAM* vpara;
	POKETCH_A02_VIEWWORK *vwk;

	vpara = PoketchViewTool_GetViewParam( wk_adrs );
	vwk = PoketchViewTool_GetViewWork( wk_adrs );

	RNUM_PrintBuf( vpara->num1, vwk->dispnum_ary );

	DispNumCommon( vwk->bgl, vwk->dispnum_ary );

	GF_BGL_LoadScreenReq( vwk->bgl, USE_BG_FRAME );
	DeleteCommand( wk_adrs );

}
//------------------------------------------------------------------
/**
 * コマンド：数値１をデジタル部に描画し、計算記号クリア
 *
 * @param   tcb		
 * @param   wk_adrs		
 */
//------------------------------------------------------------------
static void CmdDispNum1_OpClear(TCB_PTR tcb, void *wk_adrs)
{
	const POKETCH_A02_VIEW_PARAM* vpara;
	POKETCH_A02_VIEWWORK *vwk;

	vpara = PoketchViewTool_GetViewParam( wk_adrs );
	vwk = PoketchViewTool_GetViewWork( wk_adrs );

	RNUM_PrintBuf( vpara->num1, vwk->dispnum_ary );

	DispNumCommon( vwk->bgl, vwk->dispnum_ary );
	ClearOpScrn( vwk->bgl );

	GF_BGL_LoadScreenReq( vwk->bgl, USE_BG_FRAME );
	DeleteCommand( wk_adrs );
}
//------------------------------------------------------------------
/**
 * コマンド：数値２をデジタル部に描画
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdDispNum2(TCB_PTR tcb, void *wk_adrs)
{
	const POKETCH_A02_VIEW_PARAM* vpara;
	POKETCH_A02_VIEWWORK *vwk;

	vpara = PoketchViewTool_GetViewParam( wk_adrs );
	vwk = PoketchViewTool_GetViewWork( wk_adrs );

	RNUM_PrintBuf( vpara->num2, vwk->dispnum_ary );

	DispNumCommon( vwk->bgl, vwk->dispnum_ary );

	GF_BGL_LoadScreenReq( vwk->bgl, USE_BG_FRAME );
	DeleteCommand( wk_adrs );

}
//------------------------------------------------------------------
/**
 * コマンド：計算結果をデジタル部に描画
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdDispAns(TCB_PTR tcb, void *wk_adrs)
{
	const POKETCH_A02_VIEW_PARAM* vpara;
	POKETCH_A02_VIEWWORK *vwk;

	vpara = PoketchViewTool_GetViewParam( wk_adrs );
	vwk = PoketchViewTool_GetViewWork( wk_adrs );

	RNUM_PrintBuf( vpara->ans, vwk->dispnum_ary );

	DispNumCommon( vwk->bgl, vwk->dispnum_ary );
	ClearOpScrn( vwk->bgl );

	GF_BGL_LoadScreenReq( vwk->bgl, USE_BG_FRAME );
	DeleteCommand( wk_adrs );
}
//------------------------------------------------------------------
/**
 * コマンド：計算結果をデジタル部に描画
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdDispAnsOp(TCB_PTR tcb, void *wk_adrs)
{
	const POKETCH_A02_VIEW_PARAM* vpara;
	POKETCH_A02_VIEWWORK *vwk;

	vpara = PoketchViewTool_GetViewParam( wk_adrs );
	vwk = PoketchViewTool_GetViewWork( wk_adrs );

	RNUM_PrintBuf( vpara->ans, vwk->dispnum_ary );

	DispNumCommon( vwk->bgl, vwk->dispnum_ary );

	DispOpCommon( vwk->bgl, vpara );

	GF_BGL_LoadScreenReq( vwk->bgl, USE_BG_FRAME );
	DeleteCommand( wk_adrs );
}
//------------------------------------------------------------------
/**
 * コマンド：計算結果異常をデジタル部に表示
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdOverFlow( TCB_PTR tcb, void *wk_adrs )
{
	POKETCH_A02_VIEWWORK *vwk;
	u32 i;

	vwk = PoketchViewTool_GetViewWork( wk_adrs );

	for(i = 0; i < DISP_COLUMN_MAX; i++)
	{
		vwk->dispnum_ary[i] = NUM_QUESTION;
	}
	vwk->dispnum_ary[i] = NUM_ENDCODE;

	DispNumCommon( vwk->bgl, vwk->dispnum_ary );
	ClearOpScrn( vwk->bgl );

	GF_BGL_LoadScreenReq( vwk->bgl, USE_BG_FRAME );
	DeleteCommand( wk_adrs );
}

//------------------------------------------------------------------
/**
 * コマンド：計算記号をデジタル部に表示
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void CmdOperation( TCB_PTR tcb, void *wk_adrs )
{
	const POKETCH_A02_VIEW_PARAM* vpara;
	POKETCH_A02_VIEWWORK *vwk;

	vwk = PoketchViewTool_GetViewWork( wk_adrs );
	vpara = PoketchViewTool_GetViewParam( wk_adrs );

	DispOpCommon( vwk->bgl, vpara );

	GF_BGL_LoadScreenReq( vwk->bgl, USE_BG_FRAME );
	DeleteCommand( wk_adrs );

}

//------------------------------------------------------------------
/**
 * 記号描画
 *
 * @param   vpara		
 *
 */
//------------------------------------------------------------------
static void DispOpCommon( GF_BGL_INI* bgl, const POKETCH_A02_VIEW_PARAM* vpara )
{
	u16* scrn;

	scrn = GF_BGL_ScreenAdrsGet( bgl, USE_BG_FRAME );
	if( vpara->operation == OP_NULL )
	{
		ClearOpScrn( bgl );
	}
	else
	{
		u32 charno = CHARNO_OP_TOP + (vpara->operation - OP_MINUS) * 2;
		PoketchViewTool_MakeBlockScrn( scrn, SCRN_OP_XPOS, SCRN_OP_YPOS, 32, 
				charno, CHAR_BASE_XSIZE, BASE_PALNO );
	}


}

//------------------------------------------------------------------
/**
 * 記号部オフ
 *
 * @param   none		
 *
 */
//------------------------------------------------------------------
static void ClearOpScrn( GF_BGL_INI* bgl )
{
	u16* scrn = GF_BGL_ScreenAdrsGet( bgl, USE_BG_FRAME );

	PoketchViewTool_MakeBlockScrn( scrn, SCRN_OP_XPOS, SCRN_OP_YPOS, 32, 
		CHARNO_OP_NULL, CHAR_BASE_XSIZE, BASE_PALNO );

}

//------------------------------------------------------------------
/**
 * コマンド：終了処理
 *
 * @param   tcb			TCBポインタ
 * @param   wk_ptr		ワークポインタ
 *
 */
//------------------------------------------------------------------
static void CmdQuit(TCB_PTR tcb, void *wk_ptr)
{
	POKETCH_A02_VIEWWORK *vwk;

	vwk = PoketchViewTool_GetViewWork( wk_ptr );
	GF_BGL_BGControlExit( vwk->bgl, USE_BG_FRAME );
	DeleteCommand( wk_ptr );
}







//------------------------------------------------------------------
/**
 * デジタル部文字描画共通処理
 *
 * @param   ary		
 *
 */
//------------------------------------------------------------------
static void DispNumCommon( GF_BGL_INI* bgl, const u16 *ary )
{
	enum {
		SCRN_YORG = 5,
		SCRN_XORG = 3,
	};

	u32 len, i, a;
	u16 *scrn;

	scrn = GF_BGL_ScreenAdrsGet( bgl, USE_BG_FRAME );

	for(len = 0; ary[len] != NUM_ENDCODE; len++){ ; }

	for(i = 0; i  < (DISP_COLUMN_MAX - len); i++)
	{
		PoketchViewTool_MakeBlockScrn( scrn, SCRN_YORG + i*2, SCRN_XORG, 32, 
				CHARNO_DISPNUM_SPACE, CHAR_BASE_XSIZE, BASE_PALNO );
	}

	for(a = 0 ; i < DISP_COLUMN_MAX; i++, a++)
	{
		PoketchViewTool_MakeBlockScrn( scrn, SCRN_YORG + i*2, SCRN_XORG, 32, 
				CHARNO_DISPNUM_START+ary[a]*2, CHAR_BASE_XSIZE, BASE_PALNO );
	}
}
