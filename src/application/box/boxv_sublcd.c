//============================================================================================
/**
 * @file	boxv_sublcd.c
 * @brief	ボックス操作画面　描画下請け（リールコントロール関連）
 * @author	taya
 * @date	2005.11.07
 */
//============================================================================================
#include  "common.h"
#include  "gflib\calctool.h"
#include  "gflib\strbuf.h"
#include  "system\fontproc.h"
#include  "system\arc_util.h"
#include  "system\clact_util.h"
#include  "system\render_oam.h"
#include  "system\brightness.h"

#include  "box_arc.h"
#include  "box_view.h"
#include  "box_common.h"


//#define SUBLCD_PRINT_DEBUG

#define TRAYICON_MOVE_MAX	(4)

//==============================================================================================================
// 定数
//==============================================================================================================
enum {
	USE_PAL_NUMS = 3,		// BGパレット使用本数

	ICON_DISP_MAX = 6,

	TRAYICON_LEFT_NUM = 3,
	TRAYICON_RIGHT_NUM = 2,

	TRAYICON_ADD_MAX = ICON_DISP_MAX + TRAYICON_MOVE_MAX,	// 合計10までにしないとCGX領域が足りない
	TRAYICON_CHAR_FREE = -1,

	MARKICON_DISP_MAX = 6,

	STRBUF_LEN = 32,

	BLEND_STEP_MAX = BOX_TIMER(8),
	ICON_MOVE_TIME = BOX_TIMER(3),
};


// ボタンアニメーション
enum {
	BUTTON_ANM_FREE,
	BUTTON_ANM_PUSH,
};

// マークアイコンアニメーション
enum {
	MARKICON_ANM_ALLOFF_OFF,
	MARKICON_ANM_ALLOFF_ON,
	MARKICON_ANM_ITEM_OFF,
	MARKICON_ANM_ITEM_ON,
	MARKICON_ANM_MARK1_OFF,
	MARKICON_ANM_MARK1_ON,
	MARKICON_ANM_MARK2_OFF,
	MARKICON_ANM_MARK2_ON,
	MARKICON_ANM_MARK3_OFF,
	MARKICON_ANM_MARK3_ON,
	MARKICON_ANM_MARK4_OFF,
	MARKICON_ANM_MARK4_ON,
	MARKICON_ANM_MARK5_OFF,
	MARKICON_ANM_MARK5_ON,
};

// リールBG表示位置、スクロール動作パラメータ
enum {
	REEL_DEFAULT_X = 0,
	REEL_TRAYMODE_X = ((-96) * FX32_ONE),
	REEL_MARKMODE_X = (88 * FX32_ONE),
	REEL_MOVE_TIMER = BOX_TIMER(4),
};

static const fx32 ReelDispXpos[] = {
	0,
	REEL_TRAYMODE_X,
	REEL_MARKMODE_X,
};
static const int LineDispXpos[] = {
	0,
	-16*8,
	128,
};

//==============================================================================================================
// 画面レイアウト
//==============================================================================================================
enum {
	BUTTON_LEFT_X = 0,
	BUTTON_LEFT_Y = SUBSURFACE_YOFS+184,
	BUTTON_RIGHT_X = 256,	//画像サイズに依存
	BUTTON_RIGHT_Y = BUTTON_LEFT_Y,

	TRAYICON_START_XPOS = 16,
	TRAYICON_START_YPOS = SUBSURFACE_YOFS-16,

	TRAYICON_END_XPOS = 106,
	TRAYICON_END_YPOS = SUBSURFACE_YOFS + 192+16,

	TRAYICON_START_POS = 143,
	TRAYICON_1ST_POS = 127,
	TRAYICON_2ND_POS = 106,
	TRAYICON_3RD_POS = 74,
	TRAYICON_4TH_POS = 51,
	TRAYICON_5TH_POS = 31,
	TRAYICON_6TH_POS = 12,
	TRAYICON_END_POS = 0,
	TRAYICON_POS_MAX = 7,

	TRAYNAME_XDIFF = 20,
	TRAYNAME_1ST_XPOS = TRAYNAME_XDIFF + 16,
	TRAYNAME_2ND_XPOS = TRAYNAME_XDIFF + 16,
	TRAYNAME_3RD_XPOS = TRAYNAME_XDIFF + 30,
	TRAYNAME_4TH_XPOS = TRAYNAME_XDIFF + 72,
	TRAYNAME_5TH_XPOS = TRAYNAME_XDIFF + 94,
	TRAYNAME_6TH_XPOS = TRAYNAME_XDIFF + 104,

	TRAYNAME_YDIFF = -12,
	TRAYNAME_1ST_YPOS = TRAYNAME_YDIFF + 16,
	TRAYNAME_2ND_YPOS = TRAYNAME_YDIFF + 48,
	TRAYNAME_3RD_YPOS = TRAYNAME_YDIFF + 81,
	TRAYNAME_4TH_YPOS = TRAYNAME_YDIFF + 104,
	TRAYNAME_5TH_YPOS = TRAYNAME_YDIFF + 136,
	TRAYNAME_6TH_YPOS = TRAYNAME_YDIFF + 168,

	TRAYNAME_WIN_WIDTH = 96 + 8,	// 文字描画用96ドット＋左右余白4ドットずつ
	TRAYNAME_WIN_HEIGHT = 16,
	TRAYNAME_WRITE_XOFS = 4,
	TRAYNAME_WRITE_YOFS = 2,


	MARKICON_START_XPOS = 240,
	MARKICON_START_YPOS = SUBSURFACE_YOFS-16,


};

static const struct {
	s16  x;
	s16  y;
}IconEllipsePosTbl[] = {
	{ 106, SUBSURFACE_YOFS+200 },	// 0 
	{ 106, SUBSURFACE_YOFS+194 },	// 1 
	{ 106, SUBSURFACE_YOFS+190 },	// 2 
	{ 105, SUBSURFACE_YOFS+186 },	// 3 
	{ 105, SUBSURFACE_YOFS+184 },	// 4 
	{ 105, SUBSURFACE_YOFS+182 },	// 5 
	{ 105, SUBSURFACE_YOFS+180 },	// 6 
	{ 105, SUBSURFACE_YOFS+178 },	// 7 
	{ 105, SUBSURFACE_YOFS+176 },	// 8 
	{ 104, SUBSURFACE_YOFS+174 },	// 9 
	{ 104, SUBSURFACE_YOFS+172 },	// 10 
	{ 104, SUBSURFACE_YOFS+170 },	// 11 
	{ 104, SUBSURFACE_YOFS+168 },	// 12 *
	{ 103, SUBSURFACE_YOFS+166 },	// 13 
	{ 103, SUBSURFACE_YOFS+164 },	// 14 
	{ 103, SUBSURFACE_YOFS+163 },	// 15 
	{ 102, SUBSURFACE_YOFS+161 },	// 16 
	{ 102, SUBSURFACE_YOFS+159 },	// 17 
	{ 101, SUBSURFACE_YOFS+157 },	// 18 
	{ 101, SUBSURFACE_YOFS+155 },	// 19 
	{ 100, SUBSURFACE_YOFS+153 },	// 20 
	{ 100, SUBSURFACE_YOFS+151 },	// 21 
	{  99, SUBSURFACE_YOFS+150 },	// 22 
	{  98, SUBSURFACE_YOFS+148 },	// 23 
	{  98, SUBSURFACE_YOFS+146 },	// 24 
	{  97, SUBSURFACE_YOFS+144 },	// 25 
	{  96, SUBSURFACE_YOFS+142 },	// 26 
	{  96, SUBSURFACE_YOFS+141 },	// 27 
	{  95, SUBSURFACE_YOFS+139 },	// 28 
	{  94, SUBSURFACE_YOFS+137 },	// 29 
	{  94, SUBSURFACE_YOFS+136 },	// 30 
	{  93, SUBSURFACE_YOFS+134 },	// 31 *
	{  92, SUBSURFACE_YOFS+132 },	// 32 
	{  91, SUBSURFACE_YOFS+131 },	// 33 
	{  90, SUBSURFACE_YOFS+129 },	// 34 
	{  89, SUBSURFACE_YOFS+127 },	// 35 
	{  88, SUBSURFACE_YOFS+126 },	// 36 
	{  87, SUBSURFACE_YOFS+124 },	// 37 
	{  86, SUBSURFACE_YOFS+123 },	// 38 
	{  86, SUBSURFACE_YOFS+121 },	// 39 
	{  85, SUBSURFACE_YOFS+120 },	// 40 
	{  83, SUBSURFACE_YOFS+118 },	// 41 
	{  82, SUBSURFACE_YOFS+117 },	// 42 
	{  81, SUBSURFACE_YOFS+115 },	// 43 
	{  80, SUBSURFACE_YOFS+114 },	// 44 
	{  79, SUBSURFACE_YOFS+112 },	// 45 
	{  78, SUBSURFACE_YOFS+111 },	// 46 
	{  77, SUBSURFACE_YOFS+110 },	// 47 
	{  76, SUBSURFACE_YOFS+108 },	// 48 
	{  75, SUBSURFACE_YOFS+107 },	// 49 
	{  73, SUBSURFACE_YOFS+106 },	// 50 
	{  72, SUBSURFACE_YOFS+104 },	// 51 *
	{  71, SUBSURFACE_YOFS+103 },	// 52 
	{  70, SUBSURFACE_YOFS+102 },	// 53 
	{  68, SUBSURFACE_YOFS+101 },	// 54 
	{  67, SUBSURFACE_YOFS+100 },	// 55 
	{  66, SUBSURFACE_YOFS+ 99 },	// 56 
	{  65, SUBSURFACE_YOFS+ 98 },	// 57 
	{  63, SUBSURFACE_YOFS+ 97 },	// 58 
	{  62, SUBSURFACE_YOFS+ 95 },	// 59 
	{  61, SUBSURFACE_YOFS+ 95 },	// 60 
	{  59, SUBSURFACE_YOFS+ 94 },	// 61 
	{  58, SUBSURFACE_YOFS+ 93 },	// 62 
	{  56, SUBSURFACE_YOFS+ 92 },	// 63 
	{  55, SUBSURFACE_YOFS+ 91 },	// 64 
	{  54, SUBSURFACE_YOFS+ 90 },	// 65 
	{  52, SUBSURFACE_YOFS+ 89 },	// 66 
	{  51, SUBSURFACE_YOFS+ 88 },	// 67 
	{  49, SUBSURFACE_YOFS+ 88 },	// 68 
	{  48, SUBSURFACE_YOFS+ 87 },	// 69 
	{  46, SUBSURFACE_YOFS+ 86 },	// 70 
	{  45, SUBSURFACE_YOFS+ 86 },	// 71 
	{  43, SUBSURFACE_YOFS+ 85 },	// 72 
	{  42, SUBSURFACE_YOFS+ 84 },	// 73 
	{  40, SUBSURFACE_YOFS+ 84 },	// 74 *
	{  39, SUBSURFACE_YOFS+ 83 },	// 75 
	{  37, SUBSURFACE_YOFS+ 83 },	// 76 
	{  36, SUBSURFACE_YOFS+ 82 },	// 77 
	{  34, SUBSURFACE_YOFS+ 82 },	// 78 
	{  33, SUBSURFACE_YOFS+ 82 },	// 79 
	{  31, SUBSURFACE_YOFS+ 81 },	// 80 
	{  30, SUBSURFACE_YOFS+ 81 },	// 81 
	{  28, SUBSURFACE_YOFS+ 81 },	// 82 
	{  26, SUBSURFACE_YOFS+ 80 },	// 83 
	{  25, SUBSURFACE_YOFS+ 80 },	// 84 
	{  23, SUBSURFACE_YOFS+ 80 },	// 85 
	{  22, SUBSURFACE_YOFS+ 80 },	// 86 
	{  20, SUBSURFACE_YOFS+ 80 },	// 87 
	{  19, SUBSURFACE_YOFS+ 80 },	// 88 
	{  17, SUBSURFACE_YOFS+ 80 },	// 89 
	{  16, SUBSURFACE_YOFS+ 80 },	// 90 
	{  16, SUBSURFACE_YOFS+ 78 },	// 91 
	{  16, SUBSURFACE_YOFS+ 76 },	// 92 
	{  16, SUBSURFACE_YOFS+ 74 },	// 93 
	{  16, SUBSURFACE_YOFS+ 72 },	// 94 
	{  16, SUBSURFACE_YOFS+ 70 },	// 95 
	{  16, SUBSURFACE_YOFS+ 68 },	// 96 
	{  16, SUBSURFACE_YOFS+ 66 },	// 97 
	{  16, SUBSURFACE_YOFS+ 64 },	// 98 
	{  16, SUBSURFACE_YOFS+ 63 },	// 99 
	{  16, SUBSURFACE_YOFS+ 61 },	// 100
	{  16, SUBSURFACE_YOFS+ 60 },	// 101
	{  16, SUBSURFACE_YOFS+ 58 },	// 102
	{  16, SUBSURFACE_YOFS+ 57 },	// 103
	{  16, SUBSURFACE_YOFS+ 55 },	// 104
	{  16, SUBSURFACE_YOFS+ 54 },	// 105
	{  16, SUBSURFACE_YOFS+ 52 },	// 106 *
	{  16, SUBSURFACE_YOFS+ 51 },	// 107
	{  16, SUBSURFACE_YOFS+ 49 },	// 108
	{  16, SUBSURFACE_YOFS+ 48 },	// 109
	{  16, SUBSURFACE_YOFS+ 46 },	// 110
	{  16, SUBSURFACE_YOFS+ 45 },	// 111
	{  16, SUBSURFACE_YOFS+ 43 },	// 112
	{  16, SUBSURFACE_YOFS+ 42 },	// 113
	{  16, SUBSURFACE_YOFS+ 40 },	// 114
	{  16, SUBSURFACE_YOFS+ 39 },	// 115
	{  16, SUBSURFACE_YOFS+ 38 },	// 116
	{  16, SUBSURFACE_YOFS+ 36 },	// 117
	{  16, SUBSURFACE_YOFS+ 34 },	// 118
	{  16, SUBSURFACE_YOFS+ 32 },	// 119
	{  16, SUBSURFACE_YOFS+ 30 },	// 120
	{  16, SUBSURFACE_YOFS+ 28 },	// 121
	{  16, SUBSURFACE_YOFS+ 26 },	// 122
	{  16, SUBSURFACE_YOFS+ 24 },	// 123
	{  16, SUBSURFACE_YOFS+ 22 },	// 124
	{  16, SUBSURFACE_YOFS+ 20 },	// 125
	{  16, SUBSURFACE_YOFS+ 18 },	// 126
	{  16, SUBSURFACE_YOFS+ 16 },	// 127 *
	{  16, SUBSURFACE_YOFS+ 14 },	// 128
	{  16, SUBSURFACE_YOFS+ 12 },	// 129
	{  16, SUBSURFACE_YOFS+ 10 },	// 130
	{  16, SUBSURFACE_YOFS + 8 },	// 131
	{  16, SUBSURFACE_YOFS + 6 },	// 132
	{  16, SUBSURFACE_YOFS + 4 },	// 133 
	{  16, SUBSURFACE_YOFS + 2 },	// 134 
	{  16, SUBSURFACE_YOFS + 0 },	// 135 
	{  16, SUBSURFACE_YOFS - 2 },	// 136 
	{  16, SUBSURFACE_YOFS - 4 },	// 137 
	{  16, SUBSURFACE_YOFS - 6 },	// 138 
	{  16, SUBSURFACE_YOFS - 8 },	// 139 
	{  16, SUBSURFACE_YOFS -10 },	// 140 
	{  16, SUBSURFACE_YOFS -12 },	// 141 
	{  16, SUBSURFACE_YOFS -14 },	// 142 
	{  16, SUBSURFACE_YOFS -16 },	// 143 
};


static const u16 IconFixedPosTbl[] = {
	TRAYICON_START_POS,
	TRAYICON_1ST_POS,
	TRAYICON_2ND_POS,
	TRAYICON_3RD_POS,
	TRAYICON_4TH_POS,
	TRAYICON_5TH_POS,
	TRAYICON_6TH_POS,
	TRAYICON_END_POS,
};


//==============================================================================================================
// 構造体定義
//==============================================================================================================

//---------------------------------------------
/**
 * モード切替エフェクト用タスクワーク
 */
//---------------------------------------------

typedef struct {
	REEL_VIEW_WORK*	wk;		///< メインワーク
	u32					seq;	///< シーケンス
	CLACT_WORK_PTR  	button_actor;
	u16					timer;
	s16					blend;
	fx32				x_pos;
	fx32				x_add;
	int					x_end;

}CHANGE_STATE_WORK;

//---------------------------------------------
/**
 * アイコン移動処理タスクワーク
 */
//---------------------------------------------
typedef struct {
	void* cwk;
	CLACT_WORK_PTR act;

	fx32  pos;
	fx32  endpos;
	fx32  add;

	u16   timer;
	u16   wait;

	BOOL  next_move_flag;
	fx32  next_pos;
	fx32  next_endpos;
	fx32  next_add;
	u16   next_timer;
	u16   next_wait;

}ICON_MOVE_WORK;


//---------------------------------------------
/**
 * アイコン移動コントロールタスクワーク
 */
//---------------------------------------------
typedef struct {
	REEL_VIEW_WORK* wk;
	CLACT_WORK_PTR* actor;
	ICON_MOVE_WORK  icon_move_work[ TRAYICON_ADD_MAX ];
	u8              icon_pos[ TRAYICON_ADD_MAX ];
	u8              icon_move_cnt;
	u8              task_cnt;
	u8              seq;
	u8              timer;
}ICON_DISP_CTRL_WORK;

//---------------------------------------------
/**
 * メインワーク
 */
//---------------------------------------------
struct _REEL_VIEW_WORK {
	BOXAPP_VIEW_WORK*		vwk;
	const BOXAPP_VPARAM*	vpara;
	GF_BGL_INI*				bgl;
	CLACT_SET_PTR			actsys;

	u32						disp_state;
	TCB_PTR					tcb;

	NNSG2dImagePaletteProxy	objPlttProxy;

	CLACT_WORK_PTR			buttonLeftActor;
	CLACT_WORK_PTR			buttonRightActor;
	CLACT_WORK_PTR			markIconActor[ LIMITMODE_ICON_MAX ];
	CLACT_WORK_PTR			trayIconActor[ TRAYICON_ADD_MAX ];
	int						trayMoveIconCnt;
	int						topicon_ptr;

	STRBUF*					strbuf;
	GF_BGL_BMPWIN			bmpwin;


	void*					buttonCellBuf;
	NNSG2dCellDataBank*		buttonCellData;
	void*					buttonAnimBuf;
	NNSG2dAnimBankData*		buttonAnimData;

	void*					iconCellBuf;
	NNSG2dCellDataBank*		iconCellData;
	void*					iconAnimBuf;
	NNSG2dAnimBankData*		iconAnimData;

	CHANGE_STATE_WORK		changeStateWork;
	u8						blendAlphaEv1[ BLEND_STEP_MAX ];
	u8						blendAlphaEv2[ BLEND_STEP_MAX ];

};

//==============================================================================================================
// Prototype
//==============================================================================================================
static void setup_blend_alpha_table( REEL_VIEW_WORK* wk );
static void setup_actors( REEL_VIEW_WORK* wk );
static void load_actor_datas( REEL_VIEW_WORK* wk );
static TCB_PTR start_command_tcb( REEL_VIEW_WORK* wk, TCB_FUNC func, void* taskwk );
static void stop_command_tcb( REEL_VIEW_WORK* wk );
static BOOL check_command_tcb_end( REEL_VIEW_WORK* wk );
static void dispmode_on_task( TCB_PTR tcb, void* wk_adrs );
static void dispmode_switch_task( TCB_PTR tcb, void* wk_adrs );
static void dispmode_off_task( TCB_PTR tcb, void* wk_adrs );
static void trayicon_move_end_proc( REEL_VIEW_WORK* wk );
static void markicon_move_end_proc( REEL_VIEW_WORK* wk );
static void setup_traymode_icon_actor( REEL_VIEW_WORK* wk );
static u32 get_trayicon_free_actno( REEL_VIEW_WORK* wk, int direction, u32 actno );
static void setup_traymode_move_icon_actor( REEL_VIEW_WORK* wk );
static void cleanup_traymode_icon_actor( REEL_VIEW_WORK* wk );
static u32 get_markicon_anmno( u32 icon_id, u32 bit_flag );
static void setup_markmode_icon_actor( REEL_VIEW_WORK* wk );
static void cleanup_markmode_icon_actor( REEL_VIEW_WORK* wk );
static void icon_movetask( TCB_PTR tcb, void* wk_adrs );
static void icon_reverse_movetask( TCB_PTR tcb, void* wk_adrs );
static void icon_movetask_delete(TCB_PTR tcb, ICON_MOVE_WORK* taskwk);
static void  print_iconmove_taskcnt( int cnt );
static void icon_movetask_set( ICON_DISP_CTRL_WORK* cwk, CLACT_WORK_PTR act, ICON_MOVE_WORK* taskwk, u32 startPos, u32 endPos, u32 time, u32 wait, BOOL reverse_flag );
static void icon_movework_set_nextparam( ICON_DISP_CTRL_WORK* cwk,ICON_MOVE_WORK* taskwk, u32 wait, u32 startPos, u32 endPos );
static void trayicon_appear_task( TCB_PTR tcb, void* wk_adrs );
static void setup_trayicon_appear_task( REEL_VIEW_WORK* wk );
static void trayicon_move_task( TCB_PTR tcb, void* wk_adrs );
static void setup_traymode_iconmove_task( REEL_VIEW_WORK* wk );
static void markicon_appear_task( TCB_PTR tcb, void* wk_adrs );
static void setup_markicon_appear_task( REEL_VIEW_WORK* wk );
static void markicon_move_task( TCB_PTR tcb, void* wk_adrs );
static void setup_markmode_iconmove_task( REEL_VIEW_WORK* wk );
static void dispoff_tray_name( REEL_VIEW_WORK* wk );
static void dispon_tray_name( REEL_VIEW_WORK* wk );
static void  update_tray_name( REEL_VIEW_WORK* wk );


//==============================================================================================================
// メインモジュールから呼ばれる初期化・終了関連
//==============================================================================================================

//======================================================================================
/**
 * 初期化処理
 *
 * @param   wk_ptr_adrs		[out] 確保したワークのアドレスを保存しておくポインタのアドレス
 * @param   vwk				[in]  描画メインワークポインタ
 * @param   vpara			[in]  参照用描画パラメータ
 * @param   bgl				[in]  GF BGLib システムポインタ
 * @param   actsys			[in]  GF セルアクターシステムポインタ
 *
 * @retval  BOOL	TRUEで成功／ FALSEで失敗
 */
//======================================================================================
BOOL BoxAppView_Reel_Init( REEL_VIEW_WORK** wk_ptr_adrs, BOXAPP_VIEW_WORK* vwk, const BOXAPP_VPARAM* vpara, GF_BGL_INI* bgl, CLACT_SET_PTR actsys )
{
	REEL_VIEW_WORK* wk;

	wk = sys_AllocMemory( HEAPID_BOX_VIEW, sizeof(REEL_VIEW_WORK) );
	if( wk )
	{
		int i;

		wk->bgl = bgl;
		wk->vwk = vwk;
		wk->vpara = vpara;
		wk->actsys = actsys;
		wk->tcb = NULL;
		wk->strbuf = STRBUF_Create( STRBUF_LEN, HEAPID_BOX_VIEW );


		wk->disp_state = vpara->subLCD.state;

		wk->buttonCellBuf = NULL;
		wk->buttonAnimBuf = NULL;
		wk->iconCellBuf = NULL;
		wk->iconAnimBuf = NULL;

		wk->buttonLeftActor = NULL;
		wk->buttonRightActor = NULL;
		for(i=0; i<LIMITMODE_ICON_MAX; i++)
		{
			wk->markIconActor[i] = NULL;
		}
		for(i=0; i<TRAYICON_ADD_MAX; i++)
		{
			wk->trayIconActor[i] = NULL;
		}
		wk->topicon_ptr = 0;

		setup_blend_alpha_table( wk );

		*wk_ptr_adrs = wk;
		return TRUE;
	}

	return FALSE;
}

//------------------------------------------------------------------
/**
 * 帯BG用アルファブレンド係数テーブルを作成しておく
 * ※ 0 が帯BG表示オフ、MAXで表示完全オン
 *
 * @param   wk		ワークポインタ（内部テーブルに作成）
 *
 */
//------------------------------------------------------------------
static void setup_blend_alpha_table( REEL_VIEW_WORK* wk )
{
	fx32  s1, s2, sval;
	int i;

	s1 = 0;
	sval = (90 << FX32_SHIFT) / BLEND_STEP_MAX;

	wk->blendAlphaEv1[0] = 0;
	wk->blendAlphaEv2[0] = 16;

	for(i=1; i<(BLEND_STEP_MAX-1); i++)
	{
		s1 += sval;
		wk->blendAlphaEv1[i] = (FixSinCosTbl[ (s1>>FX32_SHIFT) ] * 16) >>FX32_SHIFT;
		wk->blendAlphaEv2[i] = 16 - wk->blendAlphaEv1[i];
	}

	wk->blendAlphaEv1[i] = 16;
	wk->blendAlphaEv2[i] = 0;
}

//======================================================================================
/**
 * 終了処理
 *
 * @param   wk		
 *
 */
//======================================================================================
void BoxAppView_Reel_Quit( REEL_VIEW_WORK* wk )
{
	int i;

	GF_BGL_BmpWinDel( &(wk->bmpwin) );

	if( wk->buttonCellBuf ){
		sys_FreeMemoryEz( wk->buttonCellBuf );
	}
	if( wk->buttonAnimBuf ){
		sys_FreeMemoryEz( wk->buttonAnimBuf );
	}
	if( wk->iconCellBuf ){
		sys_FreeMemoryEz( wk->iconCellBuf );
	}
	if( wk->iconAnimBuf ){
		sys_FreeMemoryEz( wk->iconAnimBuf );
	}

	if( wk->buttonLeftActor )
	{
		CLACT_Delete( wk->buttonLeftActor );
	}
	if( wk->buttonRightActor )
	{
		CLACT_Delete( wk->buttonRightActor );
	}
	if( wk->strbuf != NULL )
	{
		STRBUF_Delete( wk->strbuf );
	}

	for(i=0; i<LIMITMODE_ICON_MAX; i++)
	{
		if( wk->markIconActor[i] ){
			CLACT_Delete( wk->markIconActor[i] );
		}
	}
	for(i=0; i<TRAYICON_ADD_MAX; i++)
	{
		if( wk->trayIconActor[i] ){
			CLACT_Delete( wk->trayIconActor[i] );
		}
	}

	sys_FreeMemoryEz( wk );
}
//======================================================================================
/**
 * 初期画面作成
 *
 * @param   wk		ワークポインタ
 *
 */
//======================================================================================
void BoxAppView_Reel_Setup( REEL_VIEW_WORK* wk )
{
	ArcUtil_BgCharSet(ARC_BOX_GRA, NARC_box_sub_bg_lz_ncgr, wk->bgl, FRM_SUB_BACK, 0, 0, TRUE, HEAPID_BOX_VIEW);
	ArcUtil_ScrnSet(ARC_BOX_GRA, NARC_box_sub_bg3_lz_nscr, wk->bgl, FRM_SUB_BACK, 0, 0, TRUE, HEAPID_BOX_VIEW);
	ArcUtil_ScrnSet(ARC_BOX_GRA, NARC_box_sub_bg2_lz_nscr, wk->bgl, FRM_SUB_ICONLINE, 0, 0, TRUE, HEAPID_BOX_VIEW);
	ArcUtil_ScrnSet(ARC_BOX_GRA, NARC_box_sub_bg1_lz_nscr, wk->bgl, FRM_SUB_REEL, 0, 0, TRUE, HEAPID_BOX_VIEW);

	GF_BGL_CharFill( wk->bgl, FRM_SUB_BMPWIN, 0x00, 1, 0 );
	GF_BGL_ScrFill( wk->bgl, FRM_SUB_BMPWIN, 0x0000, 0, 0, 32, 32, GF_BGL_SCRWRT_PALIN );
	GF_BGL_LoadScreenReq( wk->bgl, FRM_SUB_BMPWIN );

	GF_BGL_ScrollSet( wk->bgl, FRM_SUB_REEL, GF_BGL_SCROLL_X_SET, ReelDispXpos[ wk->disp_state ] );

	GF_BGL_BmpWinAdd( wk->bgl, &(wk->bmpwin), FRM_SUB_BMPWIN, 0, 0, 32, 24, PAL_SUB_BMPWIN, 0 );
	GF_BGL_BmpWinDataFill( &(wk->bmpwin), 0x00 );
	GF_BGL_BmpWinOn( &wk->bmpwin );
	dispoff_tray_name( wk );

	ArcUtil_PalSet( ARC_BOX_GRA, NARC_box_sub_bg_nclr, PALTYPE_SUB_BG, 0, 0x20*USE_PAL_NUMS, HEAPID_BOX_VIEW );

	setup_actors( wk );
}

//------------------------------------------------------------------
/**
 * アクター初期状態セットアップ
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
static void setup_actors( REEL_VIEW_WORK* wk )
{
	CLACT_HEADER		header;
	NNSG2dImageProxy	imgProxy;

	load_actor_datas( wk );

	NNS_G2dInitImageProxy( &imgProxy );
	ArcUtil_CharSysLoad( ARC_BOX_GRA, NARC_box_sub_button_lz_ncgr, TRUE, CHAR_MAP_1D, 0, NNS_G2D_VRAM_TYPE_2DSUB,
		OBJCHAR_SUB_BUTTON_POS*0x20, HEAPID_BOX_VIEW, &(imgProxy) );

	BoxAppView_SetActHeader( &header, &imgProxy, &(wk->objPlttProxy),
			wk->buttonCellData, wk->buttonAnimData, BGPRI_SUB_BUTTON );

	wk->buttonLeftActor = BoxAppView_AddActor( wk->actsys, &header, BUTTON_LEFT_X, BUTTON_LEFT_Y, 
 							ACTPRI_SUB_BUTTON, NNS_G2D_VRAM_TYPE_2DSUB );

	wk->buttonRightActor = BoxAppView_AddActor( wk->actsys, &header, BUTTON_RIGHT_X, BUTTON_RIGHT_Y, 
							ACTPRI_SUB_BUTTON, NNS_G2D_VRAM_TYPE_2DSUB );

	CLACT_SetFlip( wk->buttonRightActor, CLACT_FLIP_H );

	if( BoxAppVPara_GetBoxMode(wk->vpara) == BOX_MODE_ITEM )
	{
		CLACT_AnmChg( wk->buttonRightActor, BUTTON_ANM_PUSH );
	}
}

//------------------------------------------------------------------
/**
 * アクター表示に必要なセル＆アニメデータをRAM上に読み込んでおく
 *
 * @param   wk			ワークポインタ
 *
 */
//------------------------------------------------------------------
static void load_actor_datas( REEL_VIEW_WORK* wk )
{
	wk->buttonCellBuf = ArcUtil_CellBankDataGet( ARC_BOX_GRA, NARC_box_sub_button_lz_ncer, TRUE,
									&(wk->buttonCellData), HEAPID_BOX_VIEW );

	wk->buttonAnimBuf = ArcUtil_AnimBankDataGet( ARC_BOX_GRA, NARC_box_sub_button_lz_nanr, TRUE,
									&(wk->buttonAnimData), HEAPID_BOX_VIEW );

	wk->iconCellBuf = ArcUtil_CellBankDataGet( ARC_BOX_GRA, NARC_box_sub_icon_lz_ncer, TRUE,
									&(wk->iconCellData), HEAPID_BOX_VIEW );

	wk->iconAnimBuf = ArcUtil_AnimBankDataGet( ARC_BOX_GRA, NARC_box_sub_icon_lz_nanr, TRUE,
									&(wk->iconAnimData), HEAPID_BOX_VIEW );

//	ArcUtil_ObjCharSet( ARC_BOX_GRA, NARC_box_sub_button_lz_ncgr, OBJTYPE_SUB, OBJCHAR_SUB_BUTTON_POS*0x20,
//							0, TRUE, HEAPID_BOX_VIEW );

	NNS_G2dInitImagePaletteProxy( &(wk->objPlttProxy) );
	ArcUtil_PalSysLoad( ARC_BOX_GRA, NARC_box_sub_obj_nclr, NNS_G2D_VRAM_TYPE_2DSUB, 0, 
			HEAPID_BOX_VIEW, &(wk->objPlttProxy) );


}

//==============================================================================================================
// メインモジュールから呼ばれるコマンド処理関数群
//==============================================================================================================


//------------------------------------------------------------------
/**
 * コマンド用TCBスタート
 *
 * @param   wk			モジュールワークポインタ
 * @param   func		TCB関数
 * @param   taskwk		TCB用ワーク
 *
 */
//------------------------------------------------------------------
static TCB_PTR start_command_tcb( REEL_VIEW_WORK* wk, TCB_FUNC func, void* taskwk )
{
	wk->tcb = BoxAppView_VTaskAdd( func, taskwk, TASKPRI_V_SUB );
	return wk->tcb;
}
//------------------------------------------------------------------
/**
 * コマンド用TCBストップ
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
static void stop_command_tcb( REEL_VIEW_WORK* wk )
{
	TCB_Delete( wk->tcb );
	wk->tcb = NULL;
}
//------------------------------------------------------------------
/**
 * コマンド用TCB終了チェック
 *
 * @param   wk			ワークポインタ
 *
 * @retval  BOOL		TRUEで終了している
 */
//------------------------------------------------------------------
static BOOL check_command_tcb_end( REEL_VIEW_WORK* wk )
{
	return wk->tcb == NULL;
}

//==============================================================================================
/**
 * リール表示（BG)をモードに合わせて変更
 *
 * @param   wk		
 *
 */
//==============================================================================================
void BoxAppView_Reel_ChangeState( REEL_VIEW_WORK* wk )
{
	u32 next_state = wk->vpara->subLCD.state;
	if( wk->disp_state != next_state )
	{
		TCB_FUNC   func;
		CHANGE_STATE_WORK* taskwk = &(wk->changeStateWork);

		taskwk->wk = wk;
		taskwk->button_actor = NULL;
		taskwk->seq = 0;

		switch( next_state ){
		case SUBLCD_STATE_NORMAL:
			taskwk->timer = REEL_MOVE_TIMER;
			func = dispmode_off_task;
			cleanup_traymode_icon_actor( wk );
			cleanup_markmode_icon_actor( wk );
			dispoff_tray_name( wk );
			break;
		case SUBLCD_STATE_TRAY:
			taskwk->timer = REEL_MOVE_TIMER;
			if( wk->disp_state == SUBLCD_STATE_NORMAL ){
				func = dispmode_on_task;
			}else{
				func = dispmode_switch_task;
				taskwk->timer += REEL_MOVE_TIMER;
			}
			cleanup_markmode_icon_actor( wk );
			taskwk->button_actor = wk->buttonLeftActor;
			break;

		case SUBLCD_STATE_MARK:
			taskwk->timer = REEL_MOVE_TIMER;
			if( wk->disp_state == SUBLCD_STATE_NORMAL ){
				func = dispmode_on_task;
			}else{
				func = dispmode_switch_task;
				taskwk->timer += REEL_MOVE_TIMER;
			}
			taskwk->button_actor = wk->buttonRightActor;
			cleanup_traymode_icon_actor( wk );
			dispoff_tray_name( wk );
			break;

		default:
			sys_FreeMemoryEz(taskwk);
			return;
		}

		wk->disp_state = next_state;
		taskwk->x_pos = (GF_BGL_ScrollGetX( wk->bgl, FRM_SUB_REEL ) * FX32_ONE);
		taskwk->x_add = (ReelDispXpos[ next_state ] - taskwk->x_pos) / taskwk->timer;
		taskwk->x_end = ReelDispXpos[ next_state ] >> FX32_SHIFT;

		if( taskwk->button_actor != NULL )
		{
			CLACT_AnmChg( taskwk->button_actor, BUTTON_ANM_PUSH );
		}

		start_command_tcb( wk, func, taskwk );
	}
}

BOOL BoxAppView_Reel_ChangeStateWait( REEL_VIEW_WORK* wk )
{
	return check_command_tcb_end(wk);
}




//------------------------------------------------------------------
/**
 * 通常時からトレイ選択モード／絞り込みモードへBG表示を移行する
 *
 * @param   tcb			
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void dispmode_on_task( TCB_PTR tcb, void* wk_adrs )
{
	CHANGE_STATE_WORK* taskwk = (CHANGE_STATE_WORK*)wk_adrs;
	REEL_VIEW_WORK* wk = taskwk->wk;

	switch( taskwk->seq ){
	case 0:
		if( CLACT_AnmActiveCheck( taskwk->button_actor ) == FALSE )
		{
			taskwk->seq++;
		}
		break;

	case 1:
		if( taskwk->timer )
		{
			taskwk->x_pos += taskwk->x_add;
			GF_BGL_ScrollSet( wk->bgl, FRM_SUB_REEL, GF_BGL_SCROLL_X_SET, (taskwk->x_pos>>FX32_SHIFT) );
			taskwk->timer--;
		}
		else
		{
			GF_BGL_ScrollSet( wk->bgl, FRM_SUB_REEL, GF_BGL_SCROLL_X_SET, taskwk->x_end );
			G2S_SetBlendAlpha( GX_BLEND_PLANEMASK_BG2, GX_BLEND_PLANEMASK_BG3, 0, 16 );
			taskwk->seq++;
		}
		break;

	case 2:
		GF_BGL_ScrollSet( wk->bgl, FRM_SUB_ICONLINE, GF_BGL_SCROLL_X_SET, LineDispXpos[wk->disp_state] );
		taskwk->blend = 0;
		taskwk->seq++;
		break;

	case 3:
		G2S_ChangeBlendAlpha(wk->blendAlphaEv1[taskwk->blend], wk->blendAlphaEv2[taskwk->blend]);
		if( ++(taskwk->blend) >= BLEND_STEP_MAX )
		{
			CLACT_AnmChg( taskwk->button_actor, BUTTON_ANM_FREE );
			stop_command_tcb(wk);
		}
		break;
	}
}

//------------------------------------------------------------------
/**
 * トレイ選択モード <-> 絞り込みモードの相互切り替え
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void dispmode_switch_task( TCB_PTR tcb, void* wk_adrs )
{
	CHANGE_STATE_WORK* taskwk = (CHANGE_STATE_WORK*)wk_adrs;
	REEL_VIEW_WORK* wk = taskwk->wk;

	switch( taskwk->seq ){
	case 0:
		if( CLACT_AnmActiveCheck( taskwk->button_actor ) == FALSE )
		{
			G2S_SetBlendAlpha( GX_BLEND_PLANEMASK_BG2, GX_BLEND_PLANEMASK_BG3, 16, 0 );
			taskwk->blend = (BLEND_STEP_MAX - 1);
			taskwk->seq++;
		}
		break;

	case 1:
		taskwk->blend--;
		G2S_ChangeBlendAlpha(wk->blendAlphaEv1[taskwk->blend], wk->blendAlphaEv2[taskwk->blend]);
		if( taskwk->blend == 0 )
		{
			GF_BGL_ScrollSet( wk->bgl, FRM_SUB_ICONLINE, GF_BGL_SCROLL_X_SET, LineDispXpos[wk->disp_state] );
			taskwk->seq++;
		}
		break;

	case 2:
		if( taskwk->timer )
		{
			taskwk->x_pos += taskwk->x_add;
			GF_BGL_ScrollSet( wk->bgl, FRM_SUB_REEL, GF_BGL_SCROLL_X_SET, (taskwk->x_pos>>FX32_SHIFT) );
			taskwk->timer--;
		}
		else
		{
			GF_BGL_ScrollSet( wk->bgl, FRM_SUB_REEL, GF_BGL_SCROLL_X_SET, taskwk->x_end );
			G2S_SetBlendAlpha( GX_BLEND_PLANEMASK_BG2, GX_BLEND_PLANEMASK_BG3, 0, 16 );
			taskwk->seq++;
		}
		break;

	case 3:
		GF_BGL_ScrollSet( wk->bgl, FRM_SUB_ICONLINE, GF_BGL_SCROLL_X_SET, LineDispXpos[wk->disp_state] );
		taskwk->blend = 0;
		taskwk->seq++;
		break;

	case 4:
		G2S_ChangeBlendAlpha(wk->blendAlphaEv1[taskwk->blend], wk->blendAlphaEv2[taskwk->blend]);
		if( ++(taskwk->blend) >= BLEND_STEP_MAX )
		{
			CLACT_AnmChg( taskwk->button_actor, BUTTON_ANM_FREE );
			stop_command_tcb(wk);
		}
		break;
	}
}
//------------------------------------------------------------------
/**
 * トレイ選択モード／絞り込みモードから通常時の状態へ
 *
 * @param   tcb			
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void dispmode_off_task( TCB_PTR tcb, void* wk_adrs )
{
	CHANGE_STATE_WORK* taskwk = (CHANGE_STATE_WORK*)wk_adrs;
	REEL_VIEW_WORK* wk = taskwk->wk;

	switch( taskwk->seq ){
	case 0:
		taskwk->blend = (BLEND_STEP_MAX - 1);
		taskwk->seq++;
		/* fallthru */
	case 1:
		taskwk->blend--;
		G2S_ChangeBlendAlpha(wk->blendAlphaEv1[taskwk->blend], wk->blendAlphaEv2[taskwk->blend]);
		if( taskwk->blend == 0 )
		{
			GF_BGL_ScrollSet( wk->bgl, FRM_SUB_ICONLINE, GF_BGL_SCROLL_X_SET, LineDispXpos[SUBLCD_STATE_NORMAL] );
			taskwk->seq++;
		}
		break;
	case 2:
		if( taskwk->timer )
		{
			taskwk->x_pos += taskwk->x_add;
			GF_BGL_ScrollSet( wk->bgl, FRM_SUB_REEL, GF_BGL_SCROLL_X_SET, (taskwk->x_pos>>FX32_SHIFT) );
			taskwk->timer--;
		}
		else
		{
			GF_BGL_ScrollSet( wk->bgl, FRM_SUB_REEL, GF_BGL_SCROLL_X_SET, taskwk->x_end );
			taskwk->seq++;
		}
		break;
	case 3:
		stop_command_tcb(wk);
		break;
	}
}
//==============================================================================================
/**
 * モードに合わせてアイコン出現動作開始
 *
 * @param   wk		ワークポインタ
 *
 */
//==============================================================================================
void BoxAppView_Reel_DispIcon( REEL_VIEW_WORK* wk )
{
	switch( wk->disp_state ){
	case SUBLCD_STATE_TRAY:
		setup_traymode_icon_actor(wk);
		setup_trayicon_appear_task(wk);
		break;
	case SUBLCD_STATE_MARK:
		setup_markmode_icon_actor(wk);
		setup_markicon_appear_task(wk);
		break;
	}
}

//==============================================================================================
/**
 * アイコン出現動作の終了待ち
 *
 * @param   wk		ワークポインタ
 *
 * @retval  BOOL	TRUEで終了
 */
//==============================================================================================
BOOL BoxAppView_Reel_DispIconWait( REEL_VIEW_WORK* wk )
{
	if( check_command_tcb_end(wk) )
	{
		if( wk->disp_state == SUBLCD_STATE_TRAY )
		{
			update_tray_name( wk );
		}
		return TRUE;
	}
	return FALSE;
}
//==============================================================================================
/**
 * アイコン移動開始
 *
 * @param   wk		ワークポインタ
 *
 */
//==============================================================================================
void BoxAppView_Reel_MoveIcon( REEL_VIEW_WORK* wk )
{
	switch( wk->disp_state ){
	case SUBLCD_STATE_TRAY:
		dispoff_tray_name(wk);
		setup_traymode_move_icon_actor(wk);
		setup_traymode_iconmove_task(wk);
		break;
	case SUBLCD_STATE_MARK:
		setup_markmode_iconmove_task(wk);
		break;
	}
}

static void trayicon_move_end_proc( REEL_VIEW_WORK* wk )
{
	int act_id, add, i, move;


	move = BoxAppVPara_GetSubLCDMove( wk->vpara );
	if( move > 0 )
	{
		act_id = wk->topicon_ptr + (ICON_DISP_MAX-1);
		if(act_id >= TRAYICON_ADD_MAX){ act_id -= TRAYICON_ADD_MAX; }
		add = -1;

		wk->topicon_ptr -= move;
		if( wk->topicon_ptr < 0 ){
			wk->topicon_ptr += TRAYICON_ADD_MAX;
		}
	}
	else{
		act_id = wk->topicon_ptr;
//		if(act_id < 0){ act_id += TRAYICON_ADD_MAX; }
		add = 1;

		wk->topicon_ptr -= move;
		if( wk->topicon_ptr >= TRAYICON_ADD_MAX )
		{
			wk->topicon_ptr -= TRAYICON_ADD_MAX;
		}
	}

	for(i=0; i<wk->trayMoveIconCnt; i++)
	{
		#ifdef SUBLCD_PRINT_DEBUG
		OS_TPrintf("アクター[%d]消すねん\n", act_id);
		#endif
		GF_ASSERT( wk->trayIconActor[act_id] != NULL );
		CLACT_Delete( wk->trayIconActor[act_id] );
		wk->trayIconActor[act_id] = NULL;
		act_id += add;
		if(act_id >= TRAYICON_ADD_MAX){
			act_id -= TRAYICON_ADD_MAX;
		}else if(act_id < 0){
			act_id += TRAYICON_ADD_MAX;
		}
	}
}

static void markicon_move_end_proc( REEL_VIEW_WORK* wk )
{
	int move;

	move = BoxAppVPara_GetSubLCDMove( wk->vpara );
	wk->topicon_ptr += move;
	if( wk->topicon_ptr < 0 )
	{
		wk->topicon_ptr += LIMITMODE_ICON_MAX;
	}
	else if( wk->topicon_ptr >= LIMITMODE_ICON_MAX )
	{
		wk->topicon_ptr -= LIMITMODE_ICON_MAX;
	}

}




//==============================================================================================
/**
 * アイコン移動の終了待ち
 *
 * @param   wk		ワークポインタ
 *
 * @retval  BOOL	TRUEで終了
 */
//==============================================================================================
BOOL BoxAppView_Reel_MoveIconWait( REEL_VIEW_WORK* wk )
{
	if( check_command_tcb_end(wk) )
	{
		if( wk->disp_state == SUBLCD_STATE_TRAY )
		{
			update_tray_name( wk );
			trayicon_move_end_proc( wk );
		}
		else
		{
			markicon_move_end_proc( wk );
		}
		return TRUE;
	}
	return FALSE;
}
//------------------------------------------------------------------
/**
 * トレイモード用アイコンアクター登録
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
static void setup_traymode_icon_actor( REEL_VIEW_WORK* wk )
{
	CLACT_HEADER   header;
	EXWIN_VIEW_WORK* exwin_work;
	NNSG2dImageProxy imgProxy;
	int i, trayno;

	exwin_work = BoxAppView_GetExWinViewWork(wk->vwk);
	trayno = BoxAppVPara_GetSubLCDPos( wk->vpara ) + TRAYICON_LEFT_NUM;
	if( trayno >= BOX_MAX_TRAY ){ trayno -= BOX_MAX_TRAY; }

	for(i=0; i<ICON_DISP_MAX; i++)
	{
		NNS_G2dInitImageProxy( &imgProxy );
		BoxAppView_ExWin_TransTrayIconCharData( exwin_work, trayno, OBJCHAR_SUB_TRAYICON_POS+i*OBJCHAR_TRAYICON_SIZE, 
			NNS_G2D_VRAM_TYPE_2DSUB, &imgProxy );

		BoxAppView_SetActHeader( &header, &imgProxy, &(wk->objPlttProxy),
				BoxAppView_ExWin_GetTrayIconCellDataAdrs(exwin_work), NULL, BGPRI_SUB_ICON );

		wk->trayIconActor[i] = BoxAppView_AddActor( wk->actsys, &header, TRAYICON_START_XPOS, TRAYICON_START_YPOS,
									ACTPRI_SUB_ICON, NNS_G2D_VRAM_TYPE_2DSUB );

		GF_ASSERT(wk->trayIconActor[i]!=NULL);

		trayno--;
		if(trayno < 0)
		{
			trayno = BOX_MAX_TRAY - 1;
		}
	}
	wk->topicon_ptr = 0;

}

static u32 get_trayicon_free_actno( REEL_VIEW_WORK* wk, int direction, u32 actno )
{
	s32 no;
	if( direction > 0 ){
		no = wk->topicon_ptr + ICON_DISP_MAX + actno;
		if( no >= TRAYICON_ADD_MAX ){
			no -= TRAYICON_ADD_MAX;
		}
	}else{
		no = wk->topicon_ptr - actno;
		if( no < 0 ){
			no += TRAYICON_ADD_MAX;
		}
	}
	return no;
}

//------------------------------------------------------------------
/**
 * アイコンが動くときに新規追加されるアイコンアクターの登録
 *
 * @param   wk		
 *
 */
//------------------------------------------------------------------
static void setup_traymode_move_icon_actor( REEL_VIEW_WORK* wk )
{
	CLACT_HEADER   header;
	EXWIN_VIEW_WORK* exwin_work;
	NNSG2dImageProxy imgProxy;
	int i, max, trayno, trayno_add, xpos, ypos, act_id;

	exwin_work = BoxAppView_GetExWinViewWork(wk->vwk);
	trayno = BoxAppVPara_GetSubLCDPos( wk->vpara );// + TRAYICON_LEFT_NUM;

	#ifdef SUBLCD_PRINT_DEBUG
	OS_TPrintf("次の中心はトレイ %d\n", trayno);
	#endif

	if( wk->vpara->subLCD.move > 0 )
	{
		trayno = (trayno - wk->vpara->subLCD.move) + (TRAYICON_LEFT_NUM+1);
		if( trayno >= BOX_MAX_TRAY ){ trayno -= BOX_MAX_TRAY; }
		trayno_add = 1;

		act_id = wk->topicon_ptr - 1;
		if( act_id < 0 ){
			act_id += TRAYICON_ADD_MAX;
		}

		max = wk->vpara->subLCD.move;
		xpos = TRAYICON_START_XPOS;
		ypos = TRAYICON_START_YPOS;
	}
	else
	{
		trayno = (trayno - wk->vpara->subLCD.move) - (TRAYICON_RIGHT_NUM+1);
		if( trayno < 0 ){ trayno += BOX_MAX_TRAY; }
		trayno_add = -1;

		act_id = wk->topicon_ptr + ICON_DISP_MAX;
		if( act_id >= TRAYICON_ADD_MAX ){
			act_id -= TRAYICON_ADD_MAX;
		}

		max = wk->vpara->subLCD.move * -1;
		xpos = TRAYICON_END_XPOS;
		ypos = TRAYICON_END_YPOS;

	}

	wk->trayMoveIconCnt = max;

	for(i=0; i<max; i++)
	{
		NNS_G2dInitImageProxy( &imgProxy );
		BoxAppView_ExWin_TransTrayIconCharData( exwin_work, trayno, OBJCHAR_SUB_TRAYICON_POS+act_id*OBJCHAR_TRAYICON_SIZE, 
			NNS_G2D_VRAM_TYPE_2DSUB, &imgProxy );

		BoxAppView_SetActHeader( &header, &imgProxy, &(wk->objPlttProxy),
				BoxAppView_ExWin_GetTrayIconCellDataAdrs(exwin_work), NULL, BGPRI_SUB_ICON );

		wk->trayIconActor[act_id] = BoxAppView_AddActor( wk->actsys, &header, xpos, ypos,
									ACTPRI_SUB_ICON, NNS_G2D_VRAM_TYPE_2DSUB );

		GF_ASSERT(wk->trayIconActor[act_id] != NULL);

		#ifdef SUBLCD_PRINT_DEBUG
		OS_TPrintf("アクター[%d]足した(trayno=%d) \n", act_id, trayno);
		#endif

		trayno += trayno_add;
		if(trayno < 0){
			trayno = BOX_MAX_TRAY - 1;
		}else if( trayno >= BOX_MAX_TRAY ){
			trayno = 0;
		}

		act_id -= trayno_add;
		if(act_id < 0){
			act_id += TRAYICON_ADD_MAX;
		}else if(act_id >= TRAYICON_ADD_MAX){
			act_id -= TRAYICON_ADD_MAX;
		}
	}
}
//------------------------------------------------------------------
/**
 * トレイモード用アイコンアクター全削除
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
static void cleanup_traymode_icon_actor( REEL_VIEW_WORK* wk )
{
	int i;
	for(i=0; i<TRAYICON_ADD_MAX; i++)
	{
		if( wk->trayIconActor[i] )
		{
			CLACT_Delete(wk->trayIconActor[i]);
			wk->trayIconActor[i] = NULL;
		}
	}
}


//------------------------------------------------------------------
/**
 * マークアイコンにセットするアニメナンバーを取得
 *
 * @param   icon_id			マークアイコンID
 * @param   bit_flag		絞り込みモードのビットフラグ
 *
 * @retval  u32		アニメナンバー
 */
//------------------------------------------------------------------
static u32 get_markicon_anmno( u32 icon_id, u32 bit_flag )
{
	if( icon_id == LIMITMODE_ICON_ALLOFF )
	{
		return (bit_flag == 0)? MARKICON_ANM_ALLOFF_ON : MARKICON_ANM_ALLOFF_OFF;
	}

	if( bit_flag & (1<<(icon_id-1)) )
	{
		return icon_id * 2 + 1;
	}
	else
	{
		return icon_id * 2;
	}
}
//------------------------------------------------------------------
/**
 * マークモード用アイコンアクター登録
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
static void setup_markmode_icon_actor( REEL_VIEW_WORK* wk )
{
	CLACT_HEADER   header;
	NNSG2dImageProxy imgProxy;
	u32  limitBitFlag;
	int i;

//	ArcUtil_ObjCharSet( ARC_BOX_GRA, NARC_box_sub_icon_lz_ncgr, OBJTYPE_SUB, OBJCHAR_SUB_TRAYICON_POS*0x20, TRUE, HEAPID_BOX_VIEW );


	limitBitFlag = BoxAppVPara_GetLimitModeBitFlag( wk->vpara );

	NNS_G2dInitImageProxy( &imgProxy );
	ArcUtil_CharSysLoad( ARC_BOX_GRA, NARC_box_sub_icon_lz_ncgr, TRUE, CHAR_MAP_1D, 0, NNS_G2D_VRAM_TYPE_2DSUB,
			OBJCHAR_SUB_TRAYICON_POS*0x20, HEAPID_BOX_VIEW, &imgProxy );

	for(i=0; i<LIMITMODE_ICON_MAX; i++)
	{
		BoxAppView_SetActHeader( &header, &imgProxy, &(wk->objPlttProxy),
				wk->iconCellData, wk->iconAnimData, BGPRI_SUB_ICON );

		wk->markIconActor[i] = BoxAppView_AddActor( wk->actsys, &header, MARKICON_START_XPOS, MARKICON_START_YPOS,
									ACTPRI_SUB_ICON, NNS_G2D_VRAM_TYPE_2DSUB );


		GF_ASSERT(wk->markIconActor[i]!=NULL);

		CLACT_AnmChg( wk->markIconActor[i], get_markicon_anmno(i, limitBitFlag) );
	}

	wk->topicon_ptr = BoxAppVPara_GetSubLCDLimitPos( wk->vpara );
}
//------------------------------------------------------------------
/**
 * マークモード用アイコンアクター全削除
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
static void cleanup_markmode_icon_actor( REEL_VIEW_WORK* wk )
{
	int i;
	for(i=0; i<LIMITMODE_ICON_MAX; i++)
	{
		if( wk->markIconActor[i] )
		{
			CLACT_Delete(wk->markIconActor[i]);
			wk->markIconActor[i] = NULL;
		}
	}
}



//------------------------------------------------------------------
/**
 * アイコンがリールに沿って動く動作タスク（左側用）
 *
 * @param   tcb			
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void icon_movetask( TCB_PTR tcb, void* wk_adrs )
{
	ICON_MOVE_WORK* taskwk = (ICON_MOVE_WORK*)wk_adrs;
	VecFx32 vec;

	if(taskwk->wait){
		taskwk->wait--;
		return;
	}

	if(taskwk->timer)
	{
		u32 p;
		taskwk->timer--;

		taskwk->pos += taskwk->add;
		p = taskwk->pos >> FX32_SHIFT;

		vec.x = IconEllipsePosTbl[p].x << FX32_SHIFT;
		vec.y = IconEllipsePosTbl[p].y << FX32_SHIFT;
		vec.z = 0;
		CLACT_SetMatrix(taskwk->act, &vec);
	}
	else
	{
		u32 p = taskwk->endpos >> FX32_SHIFT;
		vec.x = IconEllipsePosTbl[p].x << FX32_SHIFT;
		vec.y = IconEllipsePosTbl[p].y << FX32_SHIFT;
		vec.z = 0;
		CLACT_SetMatrix(taskwk->act, &vec);

		icon_movetask_delete(tcb, taskwk);
	}
}
//------------------------------------------------------------------
/**
 * アイコンがリールに沿って動く動作タスク（右側用）
 *
 * @param   tcb			
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void icon_reverse_movetask( TCB_PTR tcb, void* wk_adrs )
{
	ICON_MOVE_WORK* taskwk = (ICON_MOVE_WORK*)wk_adrs;
	VecFx32 vec;

	if(taskwk->wait){
		taskwk->wait--;
		return;
	}

	if(taskwk->timer)
	{
		u32 p;
		taskwk->timer--;
		taskwk->pos += taskwk->add;
		p = taskwk->pos >> FX32_SHIFT;
		vec.x = (256-IconEllipsePosTbl[p].x) << FX32_SHIFT;
		vec.y = IconEllipsePosTbl[p].y << FX32_SHIFT;
		vec.z = 0;
		CLACT_SetMatrix(taskwk->act, &vec);
	}
	else
	{
		u32 p = taskwk->endpos >> FX32_SHIFT;
		vec.x = (256-IconEllipsePosTbl[p].x) << FX32_SHIFT;
		vec.y = IconEllipsePosTbl[p].y << FX32_SHIFT;
		vec.z = 0;
		CLACT_SetMatrix(taskwk->act, &vec);

		if( taskwk->next_move_flag )
		{
			taskwk->timer = taskwk->next_timer;
			taskwk->pos = taskwk->next_pos;
			taskwk->add = taskwk->next_add;
			taskwk->endpos = taskwk->next_endpos;
			taskwk->wait = taskwk->next_wait;
			taskwk->next_move_flag = FALSE;
		}
		else
		{
			icon_movetask_delete(tcb, taskwk);
		}
	}
}
//------------------------------------------------------------------
/**
 * アイコンリール動作タスク停止
 *
 * @param   tcb		
 * @param   taskwk		
 *
 */
//------------------------------------------------------------------
static void icon_movetask_delete(TCB_PTR tcb, ICON_MOVE_WORK* taskwk)
{
	ICON_DISP_CTRL_WORK* cwk = taskwk->cwk;
	GF_ASSERT(cwk->task_cnt);
	cwk->task_cnt--;
	TCB_Delete(tcb);
	print_iconmove_taskcnt(-1);

}




#ifdef PM_DEBUG
static void  print_iconmove_taskcnt( int cnt )
{
	static int p = 0;

	p += cnt;
//	OS_TPrintf("iconmove taskcnt = %d\n", p);
}
#endif




//------------------------------------------------------------------
/**
 * アイコンがリールに沿って動くタスクのセット
 *
 * @param   cwk				親タスクのワークポインタ
 * @param   act				アイコンアクターポインタ
 * @param   taskwk			タスクワーク（確保済み領域）ポインタ
 * @param   startPos		開始位置
 * @param   endPos			終了位置
 * @param   time			移動に要するフレーム数
 * @param   reverse_flag	TRUEだと右側リールの動き
 *
 */
//------------------------------------------------------------------
static void icon_movetask_set( ICON_DISP_CTRL_WORK* cwk, CLACT_WORK_PTR act, ICON_MOVE_WORK* taskwk, u32 startPos, u32 endPos, u32 time, u32 wait, BOOL reverse_flag )
{
	TCB_FUNC func;

	GF_ASSERT(act!=NULL);

	if(wait){ wait--; }

	taskwk->cwk = cwk;
	taskwk->act = act;
	taskwk->timer = time;
	taskwk->wait = wait;

	func = (reverse_flag)? icon_reverse_movetask : icon_movetask;

	taskwk->pos = IconFixedPosTbl[startPos] << FX32_SHIFT;
	taskwk->endpos = IconFixedPosTbl[endPos] << FX32_SHIFT;
	taskwk->add = (taskwk->endpos-taskwk->pos) / (s32)time;
	taskwk->next_move_flag = FALSE;

	if(BoxAppView_VTaskAdd( func, taskwk, TASKPRI_V_SUB )!=NULL)
	{
		print_iconmove_taskcnt(1);
		cwk->task_cnt++;
	}
}
//------------------------------------------------------------------
/**
 * ↑icon_movetask_set でセットした動作の終了後、さらに動き始めたい時の動作
 *
 * @param   cwk			
 * @param   taskwk		icon_movetask_set でセットしたのと同じワーク
 * @param   wait		動き始めるまでのウェイト
 * @param   startPos	
 * @param   endPos		
 *
 */
//------------------------------------------------------------------
static void icon_movework_set_nextparam( ICON_DISP_CTRL_WORK* cwk,ICON_MOVE_WORK* taskwk, u32 wait, u32 startPos, u32 endPos )
{
	int timer;

	taskwk->next_move_flag = TRUE;
	taskwk->next_wait = wait;
	if( wait ){
		taskwk->next_wait--;
	}

	timer = endPos - startPos;
	if( timer < 0 ){
		timer *= -1;
	}
	timer *= ICON_MOVE_TIME;
	taskwk->next_timer = timer;

	taskwk->next_pos = IconFixedPosTbl[startPos] << FX32_SHIFT;
	taskwk->next_endpos = IconFixedPosTbl[endPos] << FX32_SHIFT;
	taskwk->next_add = (taskwk->next_endpos-taskwk->next_pos) / (s32)timer;
}
//------------------------------------------------------------------
/**
 * トレイアイコン出現タスク（各アイコン動作タスクの親になる）
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void trayicon_appear_task( TCB_PTR tcb, void* wk_adrs )
{
	ICON_DISP_CTRL_WORK* cwk = (ICON_DISP_CTRL_WORK*)wk_adrs;
	REEL_VIEW_WORK* wk = cwk->wk;

	switch(cwk->seq){
	case 0:
		{
			int act_id;

			cwk->icon_move_cnt++;
			act_id = ICON_DISP_MAX - cwk->icon_move_cnt;
			icon_movetask_set( cwk, wk->trayIconActor[act_id], &cwk->icon_move_work[act_id],
								0, TRAYICON_POS_MAX-cwk->icon_move_cnt, (act_id+1)*ICON_MOVE_TIME, 0, FALSE );

			cwk->timer = ICON_MOVE_TIME - BOX_TIMER(1);

			if( cwk->icon_move_cnt >= ICON_DISP_MAX )
			{
				cwk->seq = 2;
			}
			else
			{
				if( cwk->timer )
				{
					cwk->seq = 1;
				}
			}
		}
		break;

	case 1:
		cwk->timer -= BOX_TIMER(1);
		if( cwk->timer == 0 )
		{
			cwk->seq = 0;
		}
		break;

	case 2:
		if( cwk->task_cnt == 0 )
		{
			sys_FreeMemoryEz(cwk);
			stop_command_tcb(wk);
		}
		break;
	}
}
//------------------------------------------------------------------
/**
 * トレイアイコン出現動作タスクの開始
 *
 * @param   wk			ワークポインタ
 */
//------------------------------------------------------------------
static void setup_trayicon_appear_task( REEL_VIEW_WORK* wk )
{
	ICON_DISP_CTRL_WORK* cwk;
	int i;

	cwk = sys_AllocMemory( HEAPID_BOX_VIEW, sizeof(ICON_DISP_CTRL_WORK) );
	if(cwk)
	{
		TCB_PTR tcb;
		cwk->wk = wk;
		cwk->seq = 0;
		cwk->icon_move_cnt = 0;
		cwk->task_cnt = 0;
		for(i=0; i<LIMITMODE_ICON_MAX; i++)
		{
			cwk->icon_pos[i] = 0;
		}

		if( start_command_tcb( wk, trayicon_appear_task, cwk ) == NULL )
		{
			sys_FreeMemoryEz( cwk );
		}
	}
}
//------------------------------------------------------------------
/**
 * トレイアイコンスライド動作タスク（各アイコン動作タスクの親になる）
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void trayicon_move_task( TCB_PTR tcb, void* wk_adrs )
{
	ICON_DISP_CTRL_WORK* cwk = (ICON_DISP_CTRL_WORK*)wk_adrs;
	REEL_VIEW_WORK* wk = cwk->wk;

	switch(cwk->seq){
	case 0:
		{
			int i, max, act_id, id_add, time, start_pos, end_pos;

			if( wk->vpara->subLCD.move > 0 )
			{
				act_id = wk->topicon_ptr + ICON_DISP_MAX-1;
				if( act_id >= TRAYICON_ADD_MAX ){
					act_id -= TRAYICON_ADD_MAX;
				}
				id_add = -1;
				start_pos = ICON_DISP_MAX;
				end_pos = TRAYICON_POS_MAX;
			}
			else
			{
				act_id = wk->topicon_ptr;
				id_add = 1;
				start_pos = 1;
				end_pos = 0;
			}


			// 今から消える
			for(i=0; i<wk->trayMoveIconCnt; i++)
			{
				#ifdef SUBLCD_PRINT_DEBUG
				OS_TPrintf("消えるアクター[%d]  %d -> %d\n", act_id, start_pos, end_pos);
				#endif
				icon_movetask_set( cwk, cwk->actor[act_id], &cwk->icon_move_work[act_id],
								start_pos, end_pos, (i+1)*ICON_MOVE_TIME, 0, FALSE );

				start_pos += id_add;
				act_id += id_add;
				if( act_id >= TRAYICON_ADD_MAX ){
					act_id = 0;
				}else if( act_id < 0 ){
					act_id = TRAYICON_ADD_MAX - 1;
				}
			}

			// 普通にずれる
			max = (ICON_DISP_MAX - wk->trayMoveIconCnt);
			for(i=0; i<max; i++)
			{
				end_pos = start_pos - (id_add * wk->trayMoveIconCnt);
				#ifdef SUBLCD_PRINT_DEBUG
				OS_TPrintf("ずれるアクター[%d] %d -> %d\n", act_id, start_pos, end_pos);
				#endif
				icon_movetask_set( cwk, cwk->actor[act_id], &cwk->icon_move_work[act_id],
								start_pos, end_pos, wk->trayMoveIconCnt*ICON_MOVE_TIME, 0, FALSE );

				start_pos += id_add;
				act_id += id_add;
				if( act_id >= TRAYICON_ADD_MAX ){
					act_id = 0;
				}else if( act_id < 0 ){
					act_id = TRAYICON_ADD_MAX-1;
				}
			}

			// 今から出てくる
			if( wk->vpara->subLCD.move > 0 ){
				start_pos = 0;
				end_pos = wk->trayMoveIconCnt;
			}else {
				start_pos = TRAYICON_POS_MAX;
				end_pos = start_pos - wk->trayMoveIconCnt;
			}
			max = wk->trayMoveIconCnt;
			for(i=0; i<max; i++)
			{
				#ifdef SUBLCD_PRINT_DEBUG
				OS_TPrintf("現れるアクター[%d] %d -> %d\n", act_id, start_pos, end_pos);
				#endif
				icon_movetask_set( cwk, cwk->actor[act_id], &cwk->icon_move_work[act_id],
								start_pos, end_pos, (wk->trayMoveIconCnt-i)*ICON_MOVE_TIME,
								(i+1)*ICON_MOVE_TIME, FALSE );

				end_pos += id_add;
				act_id += id_add;
				if( act_id >= TRAYICON_ADD_MAX ){
					act_id -= TRAYICON_ADD_MAX;
				}else if( act_id < 0 ){
					act_id += TRAYICON_ADD_MAX;
				}
			}

			cwk->seq++;
		}
		break;

	case 1:
		if( cwk->task_cnt == 0 )
		{
			sys_FreeMemoryEz(cwk);
			stop_command_tcb(wk);
		}
		break;
	}
}
//------------------------------------------------------------------
/**
 * トレイアイコンスライド動作タスクセット
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
static void setup_traymode_iconmove_task( REEL_VIEW_WORK* wk )
{
	ICON_DISP_CTRL_WORK* cwk;
	int i;

	cwk = sys_AllocMemory( HEAPID_BOX_VIEW, sizeof(ICON_DISP_CTRL_WORK) );
	if(cwk)
	{
		TCB_PTR tcb;
		cwk->wk = wk;
		cwk->actor = wk->trayIconActor;
		cwk->seq = 0;
		cwk->icon_move_cnt = 0;
		cwk->task_cnt = 0;
		for(i=0; i<LIMITMODE_ICON_MAX; i++)
		{
			cwk->icon_pos[i] = 0;
		}

		if( start_command_tcb( wk, trayicon_move_task, cwk ) == NULL )
		{
			sys_FreeMemoryEz( cwk );
		}
	}
}



//------------------------------------------------------------------
/**
 * マークアイコン出現動作タスク（各アイコン動作タスクの親になる）
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void markicon_appear_task( TCB_PTR tcb, void* wk_adrs )
{
	ICON_DISP_CTRL_WORK* cwk = (ICON_DISP_CTRL_WORK*)wk_adrs;
	REEL_VIEW_WORK* wk = cwk->wk;


	switch(cwk->seq){
	case 0:
		{
			int i, act, pos;

			pos = MARKICON_DISP_MAX;
			act = wk->topicon_ptr;
			for(i=0; i<MARKICON_DISP_MAX; i++)
			{
				icon_movetask_set( cwk, wk->markIconActor[act], &(cwk->icon_move_work[act]), 0, pos,
					ICON_MOVE_TIME*pos, ICON_MOVE_TIME*i, TRUE );

				pos--;
				if(++act >= LIMITMODE_ICON_MAX){ act = 0; }
			}
			cwk->seq++;
		}
		break;

	case 1:
		if( cwk->task_cnt == 0 )
		{
			sys_FreeMemoryEz(cwk);
			stop_command_tcb(wk);
		}
		break;

	}
}

//------------------------------------------------------------------
/**
 * マークアイコン出現動作タスクの開始
 *
 * @param   wk			ワークポインタ
 */
//------------------------------------------------------------------
static void setup_markicon_appear_task( REEL_VIEW_WORK* wk )
{
	ICON_DISP_CTRL_WORK* cwk;
	int i;

	cwk = sys_AllocMemory( HEAPID_BOX_VIEW, sizeof(ICON_DISP_CTRL_WORK) );
	if(cwk)
	{
		TCB_PTR tcb;
		cwk->wk = wk;
		cwk->seq = 0;
		cwk->icon_move_cnt = 0;
		cwk->task_cnt = 0;
		for(i=0; i<LIMITMODE_ICON_MAX; i++)
		{
			cwk->icon_pos[i] = 0;
		}

		if( start_command_tcb( wk, markicon_appear_task, cwk ) == NULL )
		{
			sys_FreeMemoryEz( cwk );
		}
	}
}
//------------------------------------------------------------------
/**
 * マークアイコンスライド動作タスク（各アイコン動作タスクの親になる）
 *
 * @param   tcb		
 * @param   wk_adrs		
 *
 */
//------------------------------------------------------------------
static void markicon_move_task( TCB_PTR tcb, void* wk_adrs )
{
	ICON_DISP_CTRL_WORK* cwk = (ICON_DISP_CTRL_WORK*)wk_adrs;
	REEL_VIEW_WORK* wk = cwk->wk;

	switch(cwk->seq){
	case 0:
		{
			int act, move, add, i, pos, end_pos, move_max, move_len, wait;

			move = BoxAppVPara_GetSubLCDMove(wk->vpara);
			act = wk->topicon_ptr;
			if( move < 0 )
			{
				act += (MARKICON_DISP_MAX-1);
				if( act >= LIMITMODE_ICON_MAX ){
					act -= LIMITMODE_ICON_MAX;
				}
				add = -1;
				move_len = -move;
				pos = 1;
				end_pos = 0;
			}
			else
			{
				add = 1;
				move_len = move;
				pos = TRAYICON_POS_MAX-1;
				end_pos = TRAYICON_POS_MAX;
			}

			move_max = MARKICON_DISP_MAX + move_len;
			for(i=0; i<move_len; i++)
			{
				OS_TPrintf("消える: act=%d, pos=%d, endpos=%d wait=0\n", act, pos, end_pos);
				icon_movetask_set( cwk, wk->markIconActor[act], &(cwk->icon_move_work[act]), pos, end_pos,
					ICON_MOVE_TIME*(i+1), 0, TRUE );
				pos -= add;
				act += add;
				if( act < 0 ){
					act += LIMITMODE_ICON_MAX;
				}else if( act >= LIMITMODE_ICON_MAX ){
					act -= LIMITMODE_ICON_MAX;
				}
			}

			wait = 0;
			for( ; i<LIMITMODE_ICON_MAX; i++)
			{
				end_pos -= add;

				OS_TPrintf("ずれる: act=%d, pos=%d, endpos=%d wait=%d\n", act, pos, end_pos, wait);
				icon_movetask_set( cwk, wk->markIconActor[act], &(cwk->icon_move_work[act]), pos, end_pos,
					ICON_MOVE_TIME*(move_len), wait, TRUE );

				if( pos != 0 && pos != TRAYICON_POS_MAX ){
					pos -= add;
				}else{
					wait += ICON_MOVE_TIME;
				}

				act += add;
				if( act < 0 ){
					act += LIMITMODE_ICON_MAX;
				}else if( act >= LIMITMODE_ICON_MAX ){
					act -= LIMITMODE_ICON_MAX;
				}
			}

			if( move < 0 )
			{
				pos = TRAYICON_POS_MAX;
				end_pos = pos - (move_len-2);
			}
			else
			{
				pos = 0;
				end_pos = pos + (move_len-2);
			}

//			OS_TPrintf("movelen=%d, i=%d, movemax=%d\n", move_len, i, move_max);
			for( ; i<move_max; i++)
			{
				OS_TPrintf("現れる: act=%d, pos=%d, endpos=%d\n", act, pos, end_pos);
				icon_movework_set_nextparam( cwk, &(cwk->icon_move_work[act]), ICON_MOVE_TIME, pos, end_pos );
				end_pos -= add;
				act += add;
				if( act < 0 ){
					act += LIMITMODE_ICON_MAX;
				}else if( act >= LIMITMODE_ICON_MAX ){
					act -= LIMITMODE_ICON_MAX;
				}
			}

			cwk->seq++;
		}
		break;

	case 1:
		if( cwk->task_cnt == 0 )
		{
			sys_FreeMemoryEz(cwk);
			stop_command_tcb(wk);
		}
		break;
	}
}
//------------------------------------------------------------------
/**
 * マークアイコンスライド動作タスクセット
 *
 * @param   wk		ワークポインタ
 *
 */
//------------------------------------------------------------------
static void setup_markmode_iconmove_task( REEL_VIEW_WORK* wk )
{
	ICON_DISP_CTRL_WORK* cwk;
	int i;

	cwk = sys_AllocMemory( HEAPID_BOX_VIEW, sizeof(ICON_DISP_CTRL_WORK) );
	if(cwk)
	{
		TCB_PTR tcb;
		cwk->wk = wk;
		cwk->seq = 0;
		cwk->icon_move_cnt = 0;
		cwk->task_cnt = 0;
		for(i=0; i<LIMITMODE_ICON_MAX; i++)
		{
			cwk->icon_pos[i] = 0;
		}

		if( start_command_tcb( wk, markicon_move_task, cwk ) == NULL )
		{
			sys_FreeMemoryEz( cwk );
		}
	}
}


//==============================================================================================
/**
 * 絞り込みアイコンの表示状態更新
 *
 * @param   wk		ワークポインタ
 */
//==============================================================================================
void BoxAppView_Reel_MarkIconUpdate( REEL_VIEW_WORK* wk )
{
	if(wk->markIconActor[0] != NULL)
	{
		int i;
		u32 bitflag = BoxAppVPara_GetLimitModeBitFlag( wk->vpara );

		for(i=0; i<LIMITMODE_ICON_MAX; i++)
		{
			CLACT_AnmChg( wk->markIconActor[i], get_markicon_anmno(i, bitflag) );
		}
	}
}



//=====================================================================================
// BitmapWindow関連
//=====================================================================================

static void dispoff_tray_name( REEL_VIEW_WORK* wk )
{
	GF_BGL_VisibleSet( FRM_SUB_BMPWIN, FALSE );
}

static void dispon_tray_name( REEL_VIEW_WORK* wk )
{
	G2S_SetBlendAlpha( GX_BLEND_PLANEMASK_BG0, GX_BLEND_ALL, 14, 2 );
	GF_BGL_VisibleSet( FRM_SUB_BMPWIN, TRUE );
}

static void  update_tray_name( REEL_VIEW_WORK* wk )
{
	enum {
		COL_LETTER = 0x01,
		COL_SHADOW = 0x02,
		COL_GROUND = 0x00,
	};

	static const struct {
		s16 x;
		s16 y;
	}winpos[] = {
		{ TRAYNAME_1ST_XPOS, TRAYNAME_1ST_YPOS },
		{ TRAYNAME_2ND_XPOS, TRAYNAME_2ND_YPOS },
		{ TRAYNAME_3RD_XPOS, TRAYNAME_3RD_YPOS },
		{ TRAYNAME_4TH_XPOS, TRAYNAME_4TH_YPOS },
		{ TRAYNAME_5TH_XPOS, TRAYNAME_5TH_YPOS },
		{ TRAYNAME_6TH_XPOS, TRAYNAME_6TH_YPOS },
	};

	int i, trayno;

	trayno = BoxAppVPara_GetSubLCDPos( wk->vpara ) + TRAYICON_LEFT_NUM;
	if( trayno >= BOX_MAX_TRAY )
	{
		trayno -= BOX_MAX_TRAY;
	}

	for(i=0; i<NELEMS(winpos); i++)
	{
		BOXDAT_GetBoxName( wk->vpara->boxData, trayno, wk->strbuf );
		GF_BGL_BmpWinFill( &wk->bmpwin, COL_GROUND, winpos[i].x, winpos[i].y, TRAYNAME_WIN_WIDTH, TRAYNAME_WIN_HEIGHT );
		GF_STR_PrintColor( &wk->bmpwin, FONT_SYSTEM, wk->strbuf,
				winpos[i].x+TRAYNAME_WRITE_XOFS, winpos[i].y+TRAYNAME_WRITE_YOFS,
				MSG_NO_PUT, GF_PRINTCOLOR_MAKE( COL_LETTER, COL_SHADOW, COL_GROUND ),
				NULL );
		if( --trayno < 0 ){
			trayno = BOX_MAX_TRAY - 1;
		}
	}
	GF_BGL_BmpWinCgxOn( &wk->bmpwin );

	dispon_tray_name( wk );
}

