//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		ev_poke_select.c
 *	@brief
 *	@author	 
 *	@data		2006.03.13
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include <string.h>
#include <nnsys.h>
#include "gf_gx.h"
#include "include/gflib/calc2D.h"
#include "include/gflib/calctool.h"
#include "include/gflib/display.h"
#include "include/gflib/vram_transfer_manager.h"
#include "include/gflib/touchpanel_system.h"
#include "include/gflib/camera.h"
#include "include/gflib/char_manager.h"
#include "include/gflib/pltt_manager.h"
#include "include/gflib/simple_3dgraphics.h"
#include "include/gflib/strbuf.h"
#include "include/gflib/msg_print.h"
#include "include/system/heapdefine.h"
#include "include/system/wipe.h"
#include "include/system/clact_util.h"
#include "include/system/clact_util_res.h"
#include "include/system/clact_util_vram.h"
#include "include/system/arc_util.h"
#include "include/system/softsprite.h"
#include "include/system/render_oam.h"
#include "include/system/msgdata.h"
#include "include/system/fontproc.h"
#include "include/system/bmp_menu.h"
#include "include/system/window.h"
#include "include/system/tcbman.h"
#include "include/system/swsprite.h"

#include "include/poketool/poke_tool.h"
#include "include/poketool/monsno.h"

#include "include/msgdata/msg.naix"
#include "include/msgdata/msg_ev_pokeselect.h"


#include "src/demo/ev_pokeselect.naix"


#include "include/system/snd_tool.h"


#define	__EV_POKE_SELECT_H_GLOBAL
#include "include/demo/ev_poke_select.h"


//-----------------------------------------------------------------------------
/**
 *					コーディング規約
 *		●関数名
 *				１文字目は大文字それ以降は小文字にする
 *		●変数名
 *				・変数共通
 *						constには c_ を付ける
 *						staticには s_ を付ける
 *						ポインタには p_ を付ける
 *						全て合わさると csp_ となる
 *				・グローバル変数
 *						１文字目は大文字
 *				・関数内変数
 *						小文字と”＿”と数字を使用する 関数の引数もこれと同じ
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *		音用定数
 */
//-----------------------------------------------------------------------------
#define EV_POKESELE_SND_SELECT	( SE_DECIDE )		// 選択
#define EV_POKESELE_SND_DECIDE	( SE_DECIDE )		// 決定
#define EV_POKESELE_SND_BAGOPEN	( SEQ_SE_DP_BAG_030 ) // バッグ開く





//-----------------------------------------------------------------------------
/**
 *	プロック
 */
//-----------------------------------------------------------------------------
// 描画システム関係
#define EV_POKESELECT_VRAMTRANSFER_MANAGER_NUM	( 8 )
#define OAM_OAM_MAIN_S			(0)			// メイン画面 OAM使用領域開始
#define OAM_OAM_MAIN_E			(128)		// メイン画面 OAM使用領域終了
#define OAM_AFF_MAIN_S			(0)			// メイン画面 アフィン使用領域開始
#define OAM_AFF_MAIN_E			(32)		// メイン画面 アフィン使用領域終了
#define OAM_OAM_SUB_S			(0)			// サブ画面 OAM使用領域開始
#define OAM_OAM_SUB_E			(128)		// サブ画面 OAM使用領域終了
#define OAM_AFF_SUB_S			(0)			// サブ画面 アフィン使用領域開始
#define OAM_AFF_SUB_E			(32)		// サブ画面 アフィン使用領域終了
#define OAM_CHAR_ENTRY_NUM		(32)		// キャラクタマネージャエントリー数
#define OAM_CHAR_VRAMTRANS_MAIN_SIZE	(0x14000)// メイン画面 キャラクタマネージャVram管理領域
#define OAM_CHAR_VRAMTRANS_SUB_SIZE		(0x4000)// サブ画面 キャラクタマネージャVram管理領域
#define OAM_PLTT_ENTRY_NUM		(32)		// パレットマネージャエントリー数
#define CLACT_SET_WORK_NUM		( 2 )	// セルアクターセットワーク数
#define CLACT_RES_DATA_TBL_NUM	( 2 )	// 各リソースマネージャに登録できるデータ数
#define CLACT_BG_PRI			( 1 )
#define SWSP_OBJNUM		(1)		// SWSPオブジェクト数
#define SWSP_CHARNUM	(1)		// SWSPオブジェクト数
#define SWSP_PLTTNUM	(1)		// SWSPオブジェクト数

#define BG_FONTBMP_X	( 4 )			// 文字面ビットマップsize
#define BG_FONTBMP_Y	( 19 )			// 文字面ビットマップsize
#define BG_FONTBMP_CX	( 23 )			// 文字面ビットマップsize
#define BG_FONTBMP_CY	( 4 )			// 文字面ビットマップsize
#define BG_FONT_COLOR		( 0 )		// 枠用カラーパレット
#define BG_FONT_CG_OFS		( 512 )
#define BG_FONT_STR_COLOR	( 2 )		// フォント用カラーパレット
#define BG_FONTBMP_PRICOLOR	( GF_PRINTCOLOR_MAKE(1,2,15) )

#define BG_YESNOBMP_X	( 23 )			// 文字面ビットマップsize
#define BG_YESNOBMP_Y	( 12 )			// 文字面ビットマップsize
#define BG_YESNOBMP_CX	( 5 )			// 文字面ビットマップsize
#define BG_YESNOBMP_CY	( 4 )			// 文字面ビットマップsize
#define BG_YESNOBMP_CG_CHR_OFS	( BG_FONT_CG_OFS + TALK_WIN_CGX_SIZ + 128 )
#define BG_YESNOBMP_CG_OFS	( TALK_WIN_CGX_SIZ + MENU_WIN_CGX_SIZ + 128 )
#define BG_YESNOBMP_COLOR		( 1 )	// 枠用
#define BG_YESNOBMP_STR_COLOR	( 3 )	// 文字用

#define BG_BACK_COLOR	( 4 )

#define BG_FONTSUBBMP_0X		( 12 )			// 文字面ビットマップ位置
#define BG_FONTSUBBMP_0Y		( 4 )			// 文字面ビットマップ位置
#define BG_FONTSUBBMP_1X		( 4 )			// 文字面ビットマップ位置
#define BG_FONTSUBBMP_1Y		( 14 )			// 文字面ビットマップ位置
#define BG_FONTSUBBMP_2X		( 20 )			// 文字面ビットマップ位置
#define BG_FONTSUBBMP_2Y		( 13 )			// 文字面ビットマップ位置
#define BG_FONTSUBBMP_CX	( 11 )			// 文字面ビットマップsize
#define BG_FONTSUBBMP_CY	( 4 )			// 文字面ビットマップsize
#define BG_FONTSUB_COLOR		( 5 )		// カラーパレット
#define BG_FONTSUB_CGX_OFS		( 64 )		// カラーパレット
#define BG_FONTSUBBMP_ALPHA	( 10 )
#define BG_FONTSUBBMP_PRICOLOR	( GF_PRINTCOLOR_MAKE(1,2,0xa) )

// ポケモングラフィック
#define POKEGRA_TEX_SIZE	(0x8000)	// ポケモン4体分
#define POKEGRA_PLTT_SIZE	(0x80)

// カメラ設定
#define CAMERA_TARGET_X	( 0 )
#define CAMERA_TARGET_Y	( 0 )
#define CAMERA_TARGET_Z	( 0 )
#define CAMERA_ANGLE_X	( FX_GET_ROTA_NUM( -30 ) )
#define CAMERA_ANGLE_Y	( FX_GET_ROTA_NUM( 0 ) )
#define CAMERA_ANGLE_Z	( FX_GET_ROTA_NUM( 0 ) )
#define CAMERA_PEARCE	( FX_GET_ROTA_NUM( 22 ) )
#define CAMERA_DISTANCE	( 300 << FX32_SHIFT )

//-------------------------------------
//	カメラ動作後
//=====================================
#define CAMERA_TARGET_AF_Z	( 36 * FX32_ONE )
#define CAMERA_ANGLE_AF_X	( FX_GET_ROTA_NUM( -50 ) )
#define CAMERA_DISTANCE_AF	( 200 << FX32_SHIFT )
#define CAMERA_MOVE_AF_COUNT	( 6 )
 

// フェード処理関係
#define EV_POKESELECT_PROC_FADE_DIV		( 6 )
#define EV_POKESELECT_PROC_FADE_SYNC	( 1 )


// 選択数
enum{
	POKESELECT_LEFT_BALL,
	POKESELECT_CENTER_BALL,
	POKESELECT_RIGHT_BALL,
	EV_POKESELECT_MONSNUM,
};

// 3Dオブジェクト数
enum{
	POKESELECT_AUTOANM,
	POKESELECT_BAG,
	POKESELECT_BALL_LEFT,
	POKESELECT_BALL_CENTER,
	POKESELECT_BALL_RIGHT,
	POKESELECT_GROUND,
	POKESELECT_3DOBJ_NUM
};
// 3Dボタン位置です
#define EV_POKESELECT_DRAW_MAT_BALL_LEFT_X	( -44 ) 
#define EV_POKESELECT_DRAW_MAT_BALL_LEFT_Y	( -4 ) 
#define EV_POKESELECT_DRAW_MAT_BALL_LEFT_Z	( 32 ) 
#define EV_POKESELECT_DRAW_MAT_BALL_CENTER_X	( 0 ) 
#define EV_POKESELECT_DRAW_MAT_BALL_CENTER_Y	( -4 ) 
#define EV_POKESELECT_DRAW_MAT_BALL_CENTER_Z	( 62 ) 
#define EV_POKESELECT_DRAW_MAT_BALL_RIGHT_X	( 38 ) 
#define EV_POKESELECT_DRAW_MAT_BALL_RIGHT_Y	( -4 ) 
#define EV_POKESELECT_DRAW_MAT_BALL_RIGHT_Z	( 26 ) 

// 地形位置です
#define EV_POKESELECT_DRAW_GRUND_X	( 0 )
#define EV_POKESELECT_DRAW_GRUND_Y	( -28 * FX32_ONE )
#define EV_POKESELECT_DRAW_GRUND_Z	( 40 * FX32_ONE )
#define EV_POKESELECT_DRAW_GRUND_SCA_X	( FX32_CONST( 3.50f ) )
#define EV_POKESELECT_DRAW_GRUND_SCA_Y	( FX32_ONE )
#define EV_POKESELECT_DRAW_GRUND_SCA_Z	( FX32_CONST( 3.50f ) )
#define EV_POKESELECT_DRAW_GRUND_ROTA_X	( FX_GET_ROTA_NUM(0) )
#define EV_POKESELECT_DRAW_GRUND_ROTA_Y	( FX_GET_ROTA_NUM(180) )
#define EV_POKESELECT_DRAW_GRUND_ROTA_Z	( FX_GET_ROTA_NUM(0) )

// 矢印位置です
#define EV_POKESELECT_DRAW_MAT_BALL_LEFT_2X		( 78 ) 
#define EV_POKESELECT_DRAW_MAT_BALL_LEFT_2Y		( 55 ) 
#define EV_POKESELECT_DRAW_MAT_BALL_CENTER_2X	( 130 ) 
#define EV_POKESELECT_DRAW_MAT_BALL_CENTER_2Y	( 82 ) 
#define EV_POKESELECT_DRAW_MAT_BALL_RIGHT_2X	( 172 ) 
#define EV_POKESELECT_DRAW_MAT_BALL_RIGHT_2Y	( 50 ) 

//-------------------------------------
//	処理シーケンス
//=====================================
enum{
	POKESELECT_SEQ_INIT,
	POKESELECT_SEQ_WAIT,
	POKESELECT_SEQ_AUTOANM,		// AUTOアニメ
	POKESELECT_SEQ_SELECT,		// 選択
	POKESELECT_SEQ_QUESTION,	// 確認
	POKESELECT_SEQ_END,	// 終了
};


//-------------------------------------
//	開始までの待ち
//=====================================
#define POKESELECT_MONNSUTA_START_WAIT ( 36 )

//-------------------------------------
//	メッセージが出るまでのまち
//=====================================
#define POKESELECT_MSSAGE_WAIT ( 6 )



//-------------------------------------
//	カーソル動作
//=====================================
#define CURSOR_MOVE_Y		( 8 * FX32_ONE )
#define CURSOR_MOVE_COUNT	( 32 )

//-------------------------------------
//	確認画面ｴﾌｪｸﾄ
//=====================================
#define QUESTION_FADE_SYNC	( 6 )	// シンク数
#define QUESTION_FADE_SCALE_S	( FX32_CONST( 0.40f ) )
#define QUESTION_FADE_SCALE_E	( FX32_CONST( 1.0f ) )
#define QUESTION_CIRCLE_SIZE	( 128 )
#define QUESTION_CIRCLE_Y_OFS	( 48 )
// ﾎﾟｹｸﾞﾗ表示位置
#define EV_POKESELECT_POKEGRA_X		( 128 )
#define EV_POKESELECT_POKEGRA_Y		( 96 )

#define QUESTION_CIRCLE_RET_ADD	( -2 )





//-------------------------------------
//	オートアニメオブジェクト
//=====================================
typedef struct {
	NNSG3dRenderObj			RenderObj;		// レンダーオブジェクト
	void*					pResMdl;		// モデルﾃﾞｰﾀ
	NNSG3dResMdlSet*		pModelSet;		// モデルセット
	NNSG3dResMdl*			pModel;			// モデルリソース
	NNSG3dResTex*			pMdlTex;		// モデルに貼り付けるテクスチャ
	void*					pResAnm;		// アニメリソース
	void*					pOneResAnm;		// 1つ切り取ったリソース
	NNSG3dAnmObj*			pAnmObj;			// アニメーションオブジェ
	fx32 frame;

	BOOL draw_flag;
	VecFx32 mat;
	VecFx32 scal;
	u16 rota_x;		// x軸回転
	u16 rota_y;		// y軸回転
	u16 rota_z;		// z軸回転
} EV_3D_ANM_OBJ;

//-------------------------------------
//	動作ワーク
//=====================================
typedef struct {
	s32 data;
	s32 s_data;
	s32 add_data;
	s32 count_max;
} EV_MOVE_PARAM;


//-------------------------------------
//	カメラ動作タスク
//=====================================
typedef struct {
	EV_MOVE_PARAM x_rota;
	EV_MOVE_PARAM dist;
//	EV_MOVE_PARAM target_x;
//	EV_MOVE_PARAM target_y;
	EV_MOVE_PARAM target_z;
	GF_CAMERA_PTR p_camera;
	VecFx32* p_target;
	s32 count;
	BOOL end_flag;
	TCB_PTR	tcb;
} EV_CAMERA_MOVE;

//-------------------------------------
//	カーソル動作　（回転動作）
//	sin回転です。
//=====================================
typedef struct {
	fx32 num;		// 今の値
	fx32 r;			// 動作値
	int count_max;	// ｶｳﾝﾀ最大値　1回転にかかる値
	int count;
} EV_ROTA_MOVE_ONE;

//-------------------------------------
//	カーソルオブジェクト
//=====================================
typedef struct {
	CLACT_WORK_PTR cursor;
	CLACT_U_RES_OBJ_PTR res_obj[ CLACT_U_RES_MAX ];
	VecFx32 mat;

	TCB_PTR tcb;
	EV_ROTA_MOVE_ONE move_param;
} EV_CURSOR_OBJ;

//-------------------------------------
//	円系ウィンドウオブジェクト　動作パラメータ
//=====================================
typedef struct {
	EV_MOVE_PARAM x;
	EV_MOVE_PARAM y;
	EV_MOVE_PARAM scale;
	int count;
	int count_add;
} EV_CIRCLE_MOVE_PARAM;


//-------------------------------------
//	CIRCLEウィンドウオブジェクト
//=====================================
typedef struct {
	SWSP_CHAR_PTR swsp_char;
	SWSP_PLTT_PTR swsp_pltt;
	SWSP_OBJ_PTR  swsp_obj;
	void* swsp_char_buff;
	void* swsp_pltt_buff;
	NNSG2dCharacterData* p_chardata;
	NNSG2dPaletteData* p_plttdata;

	// 動作パラメータ
	EV_CIRCLE_MOVE_PARAM param;
	TCB_PTR tcb;
} EV_CIRCLE_WND;

//-------------------------------------
//	ポケモングラフィックオブジェアニメ
//=====================================
typedef struct {
	SOFT_SPRITE* p_soft_sprite;
	
	// 動作パラメータ
	EV_CIRCLE_MOVE_PARAM param;
	TCB_PTR tcb;
} EV_POKEOBJ_ANM;



//-------------------------------------
//	
//	図鑑プロックワーク
//	
//=====================================
typedef struct {
	// 動作シーケンス
	int seq;

	// 描画ﾃﾞｰﾀ
	int draw_seq;		// 描画用シーケンス
	BOOL move_lock;		// 動作lock	(描画側が操作)
	int draw_count;
	EV_CAMERA_MOVE camera_move;	// カメラ動作パラメータ
	
	// 動作ﾃﾞｰﾀ
	int now_select_no;
	int select_matrix[ EV_POKESELECT_MONSNUM ][3];
	int select_2_matrix[ EV_POKESELECT_MONSNUM ][2];

	// 描画ﾃﾞｰﾀ
	// BGL
	GF_BGL_INI*	p_bg;					// ｂｇ管理
	GF_BGL_BMPWIN* p_bmp_mfont;			// メイン画面フォント描画用
	GF_BGL_BMPWIN* p_bmp_subfont[ EV_POKESELECT_MONSNUM ];		// メイン画面サブフォント描画用
	int local_select_no;
	STRBUF* p_glb_str_buff;


	// ビットマップウィンドウﾃﾞｰﾀ
	BMPWIN_DAT bmp_data;
	BMPMENU_WORK* p_yes_no_menu;
	
	// OAM
	CLACT_U_EASYRENDER_DATA	oam_rend;	// oamレンダラーデータ
	CLACT_SET_PTR			clact_set;	// セルアクターセット
	CLACT_U_RES_MANAGER_PTR	res_manager[ CLACT_U_RES_MAX ];	// リソースマネージャ

	// 3Dポケモン
	SOFT_SPRITE_MANAGER* soft_sprite_man;	// ソフトウェアスプライトマネージャ
	SOFT_SPRITE*		 soft_sprite[ EV_POKESELECT_MONSNUM ];	// 選択中のポケモンのソフトウェアスプライト
	EV_POKEOBJ_ANM	soft_sprite_anm;	// アニメﾃﾞｰﾀ

	// ３Dアニメーションオブジェ
	NNSFndAllocator allocator;
	EV_3D_ANM_OBJ	ev_3d_obj[ POKESELECT_3DOBJ_NUM ];

	// カメラ
	GF_CAMERA_PTR p_camera;
	VecFx32 camera_target;

	// カーソルオブジェクト
	EV_CURSOR_OBJ	cursor;

	// 3Dエッジマーキングﾃﾞｰﾀ
	GXRgb edge_marking[ 8 ];

	// ソフトウェアスプライト
	SWSP_SYS_PTR	swsp_sys;
	
	// 円形ウィンドウオブジェクト
	EV_CIRCLE_WND	circle_wnd;

	// コンフィグデータ
	WINTYPE wintype;
	u32 msg_speed;

	u8 msg_index;
	u8 dummy[3];
} EV_POKESELECT_PROC_WORK;



//-----------------------------------------------------------------------------
/**
 *		プロトタイプ宣言
 */
//-----------------------------------------------------------------------------
static void EV_PokeSelect_VBlankFunc( void* work );

static void EV_PokeSelect_FadeInReq( EV_POKESELECT_PROC_WORK* p_work );
static void EV_PokeSelect_FadeOutReq( EV_POKESELECT_PROC_WORK* p_work );
static BOOL EV_PokeSelect_FadeMain( EV_POKESELECT_PROC_WORK* p_work );

static u16 EV_PokeSelect_SelectNoMonsnoGet( u16 no );

#ifdef PM_DEBUG
//#define DEBUG_EV_POKESELE
#endif

#ifdef DEBUG_EV_POKESELE
//-------------------------------------
//	デバック関数
//=====================================
static void EV_PokeSelect_Deback_Anm( EV_POKESELECT_PROC_WORK* p_psl );
#endif


//-------------------------------------
// 動作描画メイン関数
//=====================================
static BOOL EV_PokeSelect_MoveData( EV_POKESELECT_PROC_WORK* p_psl, int heap );
static void EV_PokeSelect_MoveDraw( EV_POKESELECT_PROC_WORK* p_psl, int heap );
static void EV_PokeSelect_Draw( EV_POKESELECT_PROC_WORK* p_psl );


//-------------------------------------
//	描画関係
//=====================================
static void EV_PokeSelect_SetUpDraw( EV_POKESELECT_PROC_WORK* p_psl, int heap );
static void EV_PokeSelect_PutDownDraw( void );
static void VramBankSet( void );
static void OamSet( int heap );
static void Setup_3d( EV_POKESELECT_PROC_WORK* p_psl );
static void Putback_3d( void );
static void Bg_setup( GF_BGL_INI* p_bg, int heap );
static void Bg_putdown( GF_BGL_INI* p_bg );
static void Fontbg_bmpwin_make( EV_POKESELECT_PROC_WORK* p_psl, int heap );
static void Fontbg_bmpwin_delete( EV_POKESELECT_PROC_WORK* p_psl );
static u8 Fontbg_bmpwin_str( GF_BGL_BMPWIN* p_bmp, int heap, int arcidx, int msgidx, GF_PRINTCOLOR color, u32 wait );
static u8 Fontbg_bmpwin_str_buff( GF_BGL_BMPWIN* p_bmp, int heap, int arcidx, int msgidx, GF_PRINTCOLOR color, u32 wait, STRBUF** pp_glb_str );
static void Fontbg_bmpwin_strbuff_clear( EV_POKESELECT_PROC_WORK* p_psl );

static void FontSubbg_bmpwin_make( EV_POKESELECT_PROC_WORK* p_psl, int heap );
static void FontSubbg_bmpwin_delete( EV_POKESELECT_PROC_WORK* p_psl );
static void FontSubbg_bmpwin_str( GF_BGL_BMPWIN* p_bmp, int heap, int arcidx, int msgidx, GF_PRINTCOLOR color );
static void FontSubbg_bmpwin_select( EV_POKESELECT_PROC_WORK* p_psl );
static void FontSubbg_bmpwin_clean( EV_POKESELECT_PROC_WORK* p_psl );

static void Fontbg_yesno_bmp_dat_make( EV_POKESELECT_PROC_WORK* p_psl, int heap );
static void Bg_Back_Set( GF_BGL_INI* p_bg, int heap );
static void Softsprite_init( EV_POKESELECT_PROC_WORK* p_psl, int heap );
static void Softsprite_delete( EV_POKESELECT_PROC_WORK* p_psl );
static void SwspSprite_init( EV_POKESELECT_PROC_WORK* p_psl, int heap );
static void SwspSprite_delete( EV_POKESELECT_PROC_WORK* p_psl );
static void Clact_init( EV_POKESELECT_PROC_WORK* p_psl, int heap );
static void Clact_delete( EV_POKESELECT_PROC_WORK* p_psl );
static void Camera_init( EV_POKESELECT_PROC_WORK* p_psl, int heap );
static void Camera_init_param( GF_CAMERA_PTR p_camera, VecFx32* p_target );
static void Camera_delete( EV_POKESELECT_PROC_WORK* p_psl );

static void Ev3dobj_make( EV_POKESELECT_PROC_WORK* p_psl, int heap );
static void Ev3dobj_delete( EV_POKESELECT_PROC_WORK* p_psl );
static void Ev3dobj_draw( EV_POKESELECT_PROC_WORK* p_psl );

static void Cursor_oam_load( EV_POKESELECT_PROC_WORK* p_psl, EV_CURSOR_OBJ* p_data, int heap );
static void Cursor_oam_delete( EV_POKESELECT_PROC_WORK* p_psl, EV_CURSOR_OBJ* p_data );
static void Cursor_clact_add( EV_POKESELECT_PROC_WORK* p_psl, EV_CURSOR_OBJ* p_data, int heap );
static void Cursor_clact_delete( EV_CURSOR_OBJ* p_data );
static void Cursor_clact_set_draw_flag( EV_CURSOR_OBJ* p_data, BOOL flag );
static void Cursor_clact_set_matrix( EV_CURSOR_OBJ* p_data, int x, int y );

static void Select_matrix_make( EV_POKESELECT_PROC_WORK* p_psl );
static void Select_matrix_set_3dobj( EV_POKESELECT_PROC_WORK* p_psl );

static void DrawMoveSelect( EV_POKESELECT_PROC_WORK* p_psl, int heap );
static void Draw_move_select_monsball( EV_POKESELECT_PROC_WORK* p_psl );
static void Draw_move_select_cursor( EV_POKESELECT_PROC_WORK* p_psl );

static void DrawMoveQuestion( EV_POKESELECT_PROC_WORK* p_psl, int heap );

static void PokeGra_set( SOFT_SPRITE** p_soft_sprite, EV_POKESELECT_PROC_WORK* p_psl, int monsno );

//3Dオブジェクト
static void Init_ev_3d_obj( EV_3D_ANM_OBJ* p_obj, int mdl_dataidx, int anm_dataidx, int heap, NNSFndAllocator* pallocator );
static void Init_ev_3d_obj_no_anm( EV_3D_ANM_OBJ* p_obj, int mdl_dataidx, int heap );
static void Delete_ev_3d_obj( EV_3D_ANM_OBJ* p_obj, NNSFndAllocator* pallocator );
static void Draw_ev_3d_obj( EV_3D_ANM_OBJ* p_obj );
static void Set_ev_3d_obj_draw( EV_3D_ANM_OBJ* p_obj, BOOL flag );
static void Set_ev_3d_obj_mat( EV_3D_ANM_OBJ* p_obj, fx32 x, fx32 y, fx32 z );
static void Set_ev_3d_obj_scal( EV_3D_ANM_OBJ* p_obj, fx32 x, fx32 y, fx32 z );
static void Set_ev_3d_obj_rota( EV_3D_ANM_OBJ* p_obj, u16 x, u16 y, u16 z );
static BOOL Anm_ev_3d_obj( EV_3D_ANM_OBJ* p_obj );
static void Anm_ev_3d_obj_loop( EV_3D_ANM_OBJ* p_obj );
static void Anm_ev_3d_obj_set( EV_3D_ANM_OBJ* p_obj, fx32 anm );
static fx32 Anm_ev_3d_obj_get( EV_3D_ANM_OBJ* p_obj );
static void Load_ev_3d_obj_mdl( EV_3D_ANM_OBJ* p_obj, int mdl_dataidx, int heap );
static void Load_ev_3d_obj_anm( EV_3D_ANM_OBJ* p_obj, int mdl_dataidx, int heap, NNSFndAllocator* pallocator );

static void CircleWnd_Gra_Init( EV_CIRCLE_WND* p_data, EV_POKESELECT_PROC_WORK* p_psl, int heap );
static void CircleWnd_Gra_Delete( EV_CIRCLE_WND* p_data );
static void CircleWnd_Gra_Draw( EV_CIRCLE_WND* p_data, BOOL flag );
static void CircleWnd_Move_Req( EV_CIRCLE_WND* p_data, fx32 s_x, fx32 e_x, fx32 s_y, fx32 e_y, fx32 s_s, fx32 e_s, int sync );
static void CircleWnd_ReMove_Req( EV_CIRCLE_WND* p_data );
static void CircleWnd_Move_Tcb( TCB_PTR tcb, void* work );
static BOOL CircleWnd_Move_EndCheck( EV_CIRCLE_WND* p_data );

static void QuestionFade_Req( EV_POKESELECT_PROC_WORK* p_psl );
static void QuestionReFade_Req( EV_POKESELECT_PROC_WORK* p_psl );
static BOOL QuestionFade_EndCheck( EV_POKESELECT_PROC_WORK* p_psl );

static void PokeGra_Move_Req( EV_POKEOBJ_ANM* p_data, SOFT_SPRITE* p_soft_sprit, fx32 s_x, fx32 e_x, fx32 s_y, fx32 e_y, fx32 s_s, fx32 e_s, int sync );
static void PokeGra_ReMove_Req( EV_POKEOBJ_ANM* p_data );
static void PokeGra_Move_Tcb( TCB_PTR tcb, void* work );
static BOOL PokeGra_Move_EndCheck( EV_POKEOBJ_ANM* p_data );



//-------------------------------------
//	動作関係
//=====================================
static void Move_select( EV_POKESELECT_PROC_WORK* p_psl );
static void Move_seq_add( EV_POKESELECT_PROC_WORK* p_psl, int no );
static void Move_seq_set( EV_POKESELECT_PROC_WORK* p_psl, int no );
static int Move_seq_get( EV_POKESELECT_PROC_WORK* p_psl );
static void EvMoveInit( EV_MOVE_PARAM* p_data, s32 s_num, s32 e_num, s32 count );
static BOOL EvMoveMain( EV_MOVE_PARAM* p_data, s32 count );
static void EvRotaMoveInit( EV_ROTA_MOVE_ONE* p_data, fx32 r, int count );
static void EvRotaMoveMain( EV_ROTA_MOVE_ONE* p_data );

static void EvCameraMoveReq( EV_CAMERA_MOVE* p_camera_move, GF_CAMERA_PTR p_camera, VecFx32* p_target );
static void EvCameraMoveTcb( TCB_PTR tcb, void* work );
static BOOL EvCameraMoveEndCheck( EV_CAMERA_MOVE* p_camera_move );

static void EvCursorMoveReq( EV_CURSOR_OBJ* p_cursor );
static void EvCursorMoveTcb( TCB_PTR tcb, void* work );
static void EvCursorMoveDelete( EV_CURSOR_OBJ* p_cursor );


//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑プロック生成
 *
 *	@param	proc		プロックデータ	
 *	@param	seq			シーケンス
 *
 *	@return	処理状況
 *
 *	typedef enum {
 *		PROC_RES_CONTINUE = 0,		///<動作継続中
 *		PROC_RES_FINISH,			///<動作終了
 *	}PROC_RESULT;
 *
 *
 */
//-----------------------------------------------------------------------------
PROC_RESULT EV_PokeSelect_ProcInit( PROC* proc, int* seq )
{
	EV_POKESELECT_PROC_WORK* p_pls;
	EV_POKESELECT_PEARENT_DATA* p_pearent;
	GF_BGL_SYS_HEADER bg_header;
	BOOL check;

	// 音
//	Snd_DataSetByScene( SND_SCENE_SUB_ZUKAN, 0, 0 );	// サウンドデータロード（図鑑）（BGM引継ぎ）

	// ヒープ作成
	sys_CreateHeap( HEAPID_BASE_APP, HEAPID_EV_POKESELECT, 0x40000 );

	// 図鑑ワーク作成
	p_pls = PROC_AllocWork( proc, sizeof(EV_POKESELECT_PROC_WORK), HEAPID_EV_POKESELECT );
	GF_ASSERT( p_pls );
	memset( p_pls, 0, sizeof(EV_POKESELECT_PROC_WORK) );

	// アロケーター作成
	sys_InitAllocator( &p_pls->allocator, HEAPID_EV_POKESELECT, 32 );

	// 外部からのデータ取得
	p_pearent = PROC_GetParentWork( proc );
	p_pls->wintype = CONFIG_GetWindowType( p_pearent->cp_config );
	p_pls->msg_speed = CONFIG_GetMsgPrintSpeed( p_pearent->cp_config );


	// VramTransferManager初期化
	initVramTransferManagerHeap( EV_POKESELECT_VRAMTRANSFER_MANAGER_NUM, HEAPID_EV_POKESELECT );

	// VBlank HBlank設定
	sys_VBlankFuncChange( EV_PokeSelect_VBlankFunc, p_pls );	// VBlankセット
	sys_HBlankIntrStop();	//HBlank割り込み停止

	// タッチパネルオートサンプリング開始
	InitTPSystem();
	check = InitTPNoBuff( 4 );
	GF_ASSERT( check == TP_OK );


	// 描画設定
	EV_PokeSelect_SetUpDraw( p_pls, HEAPID_EV_POKESELECT );


	// BG面設定
	p_pls->p_bg = GF_BGL_BglIniAlloc( HEAPID_EV_POKESELECT );
	bg_header.dispMode	= GX_DISPMODE_GRAPHICS;
	bg_header.bgMode	= GX_BGMODE_0;
	bg_header.bgModeSub	= GX_BGMODE_1;
	bg_header.bg0_2Dor3D= GX_BG0_AS_3D;
	GF_BGL_InitBG( &bg_header );
	Bg_setup( p_pls->p_bg, HEAPID_EV_POKESELECT );
	// 表示
	GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG0, VISIBLE_ON );
	GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG1, VISIBLE_OFF );

	// 文字列面作成
	Fontbg_bmpwin_make( p_pls, HEAPID_EV_POKESELECT );

	// yesno_data作成
	Fontbg_yesno_bmp_dat_make( p_pls, HEAPID_EV_POKESELECT );
	FontSubbg_bmpwin_make( p_pls, HEAPID_EV_POKESELECT );

	// ソフトウェアスプライト初期化
	Softsprite_init( p_pls, HEAPID_EV_POKESELECT );
	SwspSprite_init( p_pls, HEAPID_EV_POKESELECT );

	// セルアクター
	Clact_init( p_pls, HEAPID_EV_POKESELECT );	

	// 3Dモデル生成
	Ev3dobj_make( p_pls, HEAPID_EV_POKESELECT );

	// カメラ作成
	Camera_init( p_pls, HEAPID_EV_POKESELECT );

	// 選択座標設定
	Select_matrix_make( p_pls );

	// 3Dオブジェクトに座標を設定
	Select_matrix_set_3dobj( p_pls );

	// カーソル初期化
	Cursor_oam_load( p_pls, &p_pls->cursor, HEAPID_EV_POKESELECT );
	Cursor_clact_add( p_pls, &p_pls->cursor, HEAPID_EV_POKESELECT );
	EvCursorMoveReq( &p_pls->cursor );

	// サークルウィンドウ初期化
	CircleWnd_Gra_Init( &p_pls->circle_wnd, p_pls, HEAPID_EV_POKESELECT );


	// 音関係
	Snd_DataSetByScene( SND_SCENE_SUB_FIRSTPOKE, 0, 0 );	// sound_load(最初のポケモン選択)(BGM引継ぎ)

	return PROC_RES_FINISH;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑プロックメイン
 *
 *	@param	proc		プロックデータ	
 *	@param	seq			シーケンス
 *
 *	@return	処理状況
 *
 *	typedef enum {
 *		PROC_RES_CONTINUE = 0,		///<動作継続中
 *		PROC_RES_FINISH,			///<動作終了
 *	}PROC_RESULT;
 *
 *
 */
//-----------------------------------------------------------------------------
PROC_RESULT EV_PokeSelect_ProcMain( PROC* proc, int* seq )
{
	EV_POKESELECT_PROC_WORK* p_pls = PROC_GetWork( proc );
	BOOL ret;
	short num = 0x08c3;

	switch( *seq ){
	// フェードイン
	case 0:
		EV_PokeSelect_FadeInReq( p_pls );
		GX_LoadBGPltt( &num, 0, sizeof(short) );
		(*seq)++;
		break;
	case 1:
		if( EV_PokeSelect_FadeMain( p_pls ) ){
			WIPE_ResetWndMask( WIPE_DISP_MAIN );
			WIPE_ResetWndMask( WIPE_DISP_SUB );
			(*seq)++;
		}
		break;

		
	//-------------------------------------
	//	
	// メイン動作	
	//	
	//=====================================
	case 2:
		ret = EV_PokeSelect_MoveData( p_pls, HEAPID_EV_POKESELECT );
		EV_PokeSelect_MoveDraw( p_pls, HEAPID_EV_POKESELECT );

		// 終了チェック
		if( ret == TRUE ){
			(*seq)++;
		}
		break;


	// フェードアウト
	case 3:
		EV_PokeSelect_FadeOutReq( p_pls );
		(*seq)++;
		break;
	case 4:
		if( EV_PokeSelect_FadeMain( p_pls ) ){
			WIPE_ResetWndMask( WIPE_DISP_MAIN );
			WIPE_ResetWndMask( WIPE_DISP_SUB );

			return PROC_RES_FINISH;
		}
		break;
	}

	//　描画処理
	EV_PokeSelect_Draw( p_pls );

	return PROC_RES_CONTINUE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑プロック終了
 *
 *	@param	proc		プロックデータ	
 *	@param	seq			シーケンス
 *
 *	@return	処理状況
 *
 *	typedef enum {
 *		PROC_RES_CONTINUE = 0,		///<動作継続中
 *		PROC_RES_FINISH,			///<動作終了
 *	}PROC_RESULT;
 *
 *
 */
//-----------------------------------------------------------------------------
PROC_RESULT EV_PokeSelect_ProcEnd( PROC* proc, int* seq )
{
	EV_POKESELECT_PROC_WORK* p_pls = PROC_GetWork( proc );
	EV_POKESELECT_PEARENT_DATA* p_pearent =PROC_GetParentWork( proc );
	BOOL check;

	sys_VBlankFuncChange( NULL, NULL );	// VBlankセット

	// 親に選択したポケモンﾅﾝﾊﾞｰを設定する
	p_pearent->select_monsno = EV_PokeSelect_SelectNoMonsnoGet( p_pls->now_select_no );

	// タッチパネルサンプリング終了
	check = StopTP();
	GF_ASSERT( check == TP_OK );

	// CIRCLEウィンドウﾃﾞｰﾀ破棄
	CircleWnd_Gra_Delete( &p_pls->circle_wnd );

	// カーソル破棄
	Cursor_clact_delete( &p_pls->cursor );
	Cursor_oam_delete( p_pls, &p_pls->cursor );
	EvCursorMoveDelete( &p_pls->cursor );

	// カメラ破棄
	Camera_delete( p_pls );

	// 3Dモデル破棄
	Ev3dobj_delete( p_pls );
	
	// セルアクター破棄
	Clact_delete( p_pls );
	
	// ソフトウェアスプライト破棄
	Softsprite_delete( p_pls );
	SwspSprite_delete( p_pls );
	
	// 文字列面破棄
	Fontbg_bmpwin_delete( p_pls );
	FontSubbg_bmpwin_delete( p_pls );
	
	// BG破棄
	Bg_putdown( p_pls->p_bg );

	// BGシステム
	sys_FreeMemoryEz( p_pls->p_bg );
	
	// 表示データ破棄
	EV_PokeSelect_PutDownDraw();

	// VramTransferManager破棄
	DellVramTransferManager();

	// ワーク破棄
	PROC_FreeWork( proc );

	// ヒープ破棄
	sys_DeleteHeap( HEAPID_EV_POKESELECT );

	return PROC_RES_FINISH;
}


//-----------------------------------------------------------------------------
/**
 *			プライベート関数
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	VBlank関数
 *
 *	@param	work	ワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void EV_PokeSelect_VBlankFunc( void* work )
{
	EV_POKESELECT_PROC_WORK* p_psl = work;

	// レンダラーOAM転送
	REND_OAMTrans();

	GF_BGL_VBlankFunc( p_psl->p_bg );

	// ソフトウェアスプライト
	SoftSpriteTextureTrans( p_psl->soft_sprite_man );

	// Vram転送タスク
	DoVramTransferManager();
}

//----------------------------------------------------------------------------
/**
 *	@brief	フェードイン設定
 *
 *	@param	p_work	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void EV_PokeSelect_FadeInReq( EV_POKESELECT_PROC_WORK* p_work )
{
	WIPE_SYS_Start(
			WIPE_PATTERN_WMS,
			WIPE_TYPE_FADEIN,
			WIPE_TYPE_FADEIN,
			WIPE_FADE_BLACK,
			EV_POKESELECT_PROC_FADE_DIV,
			EV_POKESELECT_PROC_FADE_SYNC,
			HEAPID_EV_POKESELECT );
}

//----------------------------------------------------------------------------
/**
 *	@brief	フェードアウト設定
 *
 *	@param	p_work	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void EV_PokeSelect_FadeOutReq( EV_POKESELECT_PROC_WORK* p_work )
{
	WIPE_SYS_Start(
			WIPE_PATTERN_WMS,
			WIPE_TYPE_FADEOUT,
			WIPE_TYPE_FADEOUT,
			WIPE_FADE_BLACK,
			EV_POKESELECT_PROC_FADE_DIV,
			EV_POKESELECT_PROC_FADE_SYNC,
			HEAPID_EV_POKESELECT );
}

//----------------------------------------------------------------------------
/**
 *	@brief	フェードチェック
 *
 *	@param	p_work	ワーク
 *
 *	@retval	TRUE		フェード終了
 *	@retval	FALSE		フェード中
 */
//-----------------------------------------------------------------------------
static BOOL EV_PokeSelect_FadeMain( EV_POKESELECT_PROC_WORK* p_work )
{
	return WIPE_SYS_EndCheck();
}


//----------------------------------------------------------------------------
/**
 *	@brief	描画セットアップ
 *
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void EV_PokeSelect_SetUpDraw( EV_POKESELECT_PROC_WORK* p_psl, int heap )
{
	// バンクセットアップ
	VramBankSet();
	
	// oam関係セットアップ
	OamSet( heap );


	// 3D面
	Setup_3d( p_psl );
}

//----------------------------------------------------------------------------
/**
 *	@brief	描画プットダウン
 *
 *	@param	none
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void EV_PokeSelect_PutDownDraw( void )
{
	// レンダラー共有OAMマネージャ破棄
	REND_OAM_Delete();
	
	// キャラクタデータ破棄
	DeleteCharManager();
	// パレットデータ破棄
	DeletePlttManager();

	// 3D面
	Putback_3d();
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	VramBankセットアップ
 *
 *	@param	none
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void VramBankSet( void )
{
	GF_BGL_DISPVRAM vramSetTable = {
		GX_VRAM_BG_128_B,				// メイン2DエンジンのBG
		GX_VRAM_BGEXTPLTT_NONE,			// メイン2DエンジンのBG拡張パレット
		GX_VRAM_SUB_BG_128_C,			// サブ2DエンジンのBG
		GX_VRAM_SUB_BGEXTPLTT_NONE,		// サブ2DエンジンのBG拡張パレット
		GX_VRAM_OBJ_80_EF,				// メイン2DエンジンのOBJ
		GX_VRAM_OBJEXTPLTT_NONE,		// メイン2DエンジンのOBJ拡張パレット
		GX_VRAM_SUB_OBJ_16_I,			// サブ2DエンジンのOBJ
		GX_VRAM_SUB_OBJEXTPLTT_NONE,	// サブ2DエンジンのOBJ拡張パレット
		GX_VRAM_TEX_0_A,				// テクスチャイメージスロット
		GX_VRAM_TEXPLTT_0_G				// テクスチャパレットスロット
	};
	GF_Disp_SetBank( &vramSetTable );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	OAMセットアップ
 *
 *	@param	none
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void OamSet( int heap )
{
	// OAMマネージャーの初期化
	NNS_G2dInitOamManagerModule();

	// 共有OAMマネージャ作成
	// レンダラ用OAMマネージャ作成
	// ここで作成したOAMマネージャをみんなで共有する
	REND_OAMInit( 
			OAM_OAM_MAIN_S, OAM_OAM_MAIN_E,	// メイン画面OAM管理領域
			OAM_AFF_MAIN_S, OAM_AFF_MAIN_E,		// メイン画面アフィン管理領域
			OAM_OAM_SUB_S, OAM_OAM_SUB_E,		// サブ画面OAM管理領域
			OAM_AFF_SUB_S, OAM_AFF_SUB_E,		// サブ画面アフィン管理領域
			heap);
	
	// キャラクタマネージャー初期化
	{
		CHAR_MANAGER_MAKE cm = {
			OAM_CHAR_ENTRY_NUM,
			OAM_CHAR_VRAMTRANS_MAIN_SIZE,
			OAM_CHAR_VRAMTRANS_SUB_SIZE,
		};
		cm.heap = heap;
		
		InitCharManagerReg(&cm, GX_OBJVRAMMODE_CHAR_1D_128K, GX_OBJVRAMMODE_CHAR_1D_32K );
	}
	// パレットマネージャー初期化
	InitPlttManager(OAM_PLTT_ENTRY_NUM, heap);

	// 読み込み開始位置を初期化
	CharLoadStartAll();
	PlttLoadStartAll();
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	3D面設定
 *
 *	@param	none
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void Setup_3d( EV_POKESELECT_PROC_WORK* p_psl )
{
	int i;
	
	// NitroSystem:３Ｄエンジンの初期化
	NNS_G3dInit();
	// マトリクススタックの初期化
    G3X_InitMtxStack();

	// 各種描画モードの設定(シェード＆アンチエイリアス＆半透明)
    G3X_SetShading(GX_SHADING_TOON);
    G3X_AntiAlias(TRUE);
	G3X_AlphaTest(FALSE, 0);	// アルファテスト　　オフ
	G3X_AlphaBlend(TRUE);		// アルファブレンド　オン

	// エッジマーキング
	G3X_EdgeMarking(TRUE);
	for( i=0; i<8; i++ ){
		p_psl->edge_marking[i] = GX_RGB( 4, 4, 4 );
	}
	G3X_SetEdgeColorTable( p_psl->edge_marking );

	
	// クリアカラーの設定
    G3X_SetClearColor(GX_RGB(31, 31, 16),	// clear color
                      0,				// clear alpha
                      0x7fff,			// clear depth
                      63,				// clear polygon ID
                      FALSE				// fog
                      );

	// ジオメトリエンジン起動後必ず呼ばれなければならない
    G3_SwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_W);

	// ビューポートの設定
    G3_ViewPort(0, 0, 255, 191);

	// マネージャがテクスチャイメージスロットを指定スロット分管理できるようにして
	// デフォルトマネージャにする。
	NNS_GfdInitFrmTexVramManager(1, TRUE);
		
	// マネージャがパレットを16KB分管理できるようにして
	// デフォルトマネージャにする。
	NNS_GfdInitFrmPlttVramManager(0x4000, TRUE);

}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	３D設定で使用したメモリを破棄
 *
 *	@param	none 
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void Putback_3d( void )
{
	NNS_GfdResetFrmTexVramState();
	NNS_GfdResetFrmPlttVramState();
}


//----------------------------------------------------------------------------
/**
 *	@brief	BG面設定
 *
 *	@param	p_bg	ｂｇﾃﾞｰﾀ
 *	@param	heap	ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void Bg_setup( GF_BGL_INI* p_bg, int heap )
{
	// BG0の優先順位
	G2_SetBG0Priority( 1 );
	
	// メイン画面 BG1面		文字列書き込み面
	{
		GF_BGL_BGCNT_HEADER bg_cnt_header = {
			0, 0, 0x800, 0,
			GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x0000, GX_BG_CHARBASE_0x04000,
			GX_BG_EXTPLTT_01, 0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( p_bg, GF_BGL_FRAME1_M, &bg_cnt_header, GF_BGL_MODE_TEXT );
		GF_BGL_ClearCharSet( GF_BGL_FRAME1_M, 32, 0, heap );
		GF_BGL_ScrClear( p_bg, GF_BGL_FRAME1_M );
	}

	// メイン画面 BG2面		背景面
	{
		GF_BGL_BGCNT_HEADER bg_cnt_header = {
			0, 0, 0x800, 0,
			GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x0800, GX_BG_CHARBASE_0x0c000,
			GX_BG_EXTPLTT_01, 2, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( p_bg, GF_BGL_FRAME2_M, &bg_cnt_header, GF_BGL_MODE_TEXT );
		GF_BGL_ClearCharSet( GF_BGL_FRAME2_M, 32, 0, heap );
		GF_BGL_ScrClear( p_bg, GF_BGL_FRAME2_M );
	}

	// メイン画面 BG3面		サブ文字面
	{
		GF_BGL_BGCNT_HEADER bg_cnt_header = {
			0, 0, 0x800, 0,
			GF_BGL_SCRSIZ_256x256, GX_BG_COLORMODE_16,
			GX_BG_SCRBASE_0x1000, GX_BG_CHARBASE_0x14000,
			GX_BG_EXTPLTT_01, 0, 0, 0, FALSE
		};
		GF_BGL_BGControlSet( p_bg, GF_BGL_FRAME3_M, &bg_cnt_header, GF_BGL_MODE_TEXT );
		GF_BGL_ClearCharSet( GF_BGL_FRAME3_M, 32, 0, heap );
		GF_BGL_ScrClear( p_bg, GF_BGL_FRAME3_M );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	BG面設定破棄
 *
 *	@param	p_bg 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void Bg_putdown( GF_BGL_INI* p_bg )
{
	GF_BGL_BGControlExit( p_bg, GF_BGL_FRAME1_M );
	GF_BGL_BGControlExit( p_bg, GF_BGL_FRAME2_M );
	GF_BGL_BGControlExit( p_bg, GF_BGL_FRAME3_M );
}


//----------------------------------------------------------------------------
/**
 *	@brief	ビットマップウィンドウ作成
 *
 *	@param	p_bmp_mfont	ビットマップウィンドウ
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void Fontbg_bmpwin_make( EV_POKESELECT_PROC_WORK* p_psl, int heap )
{
	p_psl->p_bmp_mfont = GF_BGL_BmpWinAllocGet( heap, 1 );
	GF_BGL_BmpWinInit( p_psl->p_bmp_mfont );
	
	// ビットマップウィンドウ登録
	GF_BGL_BmpWinAdd( p_psl->p_bg, p_psl->p_bmp_mfont,
			GF_BGL_FRAME1_M, BG_FONTBMP_X, BG_FONTBMP_Y, BG_FONTBMP_CX, BG_FONTBMP_CY, BG_FONT_STR_COLOR, TALK_WIN_CGX_SIZ + 1 );

	// クリーン
	GF_BGL_BmpWinDataFill( p_psl->p_bmp_mfont, 15 );

	// 枠を描画
	TalkWinGraphicSet( p_psl->p_bg, GF_BGL_FRAME1_M, BG_FONT_CG_OFS, BG_FONT_COLOR, p_psl->wintype, heap );

	// 会話フォントパレット読み込み
	ArcUtil_PalSet( ARC_EV_POKESELECT_GRA, NARC_ev_pokeselect_font_talk_NCLR, PALTYPE_MAIN_BG, BG_FONT_STR_COLOR * 32, 32, heap );

	BmpTalkWinWrite( p_psl->p_bmp_mfont, WINDOW_TRANS_ON, BG_FONT_CG_OFS, BG_FONT_COLOR );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ビットマップウィンドウ破棄
 *
 *	@param	p_bmp_mfont 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void Fontbg_bmpwin_delete( EV_POKESELECT_PROC_WORK* p_psl )
{
	GF_BGL_BmpWinDel( p_psl->p_bmp_mfont );
	sys_FreeMemoryEz( p_psl->p_bmp_mfont );
}


//----------------------------------------------------------------------------
/**
 *	@brief	スプライトマネージャ初期化
 *	
 *	@param	p_psl		ワーク
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void Softsprite_init( EV_POKESELECT_PROC_WORK* p_psl, int heap )
{
	NNSGfdTexKey	texKey;
	NNSGfdPlttKey	plttKey;
	int i;

	// ポケモンデータ転送領域のVramを確保＆転送アドレスとサイズを設定
	p_psl->soft_sprite_man = SoftSpriteInit( heap );	
	texKey = NNS_GfdAllocTexVram(POKEGRA_TEX_SIZE, FALSE, 0);
	plttKey = NNS_GfdAllocPlttVram(POKEGRA_PLTT_SIZE, FALSE, NNS_GFD_ALLOC_FROM_LOW);
	SoftSpriteTextureTransParamSet( 
			p_psl->soft_sprite_man,
			NNS_GfdGetTexKeyAddr(texKey),
			NNS_GfdGetTexKeySize(texKey) );
	SoftSpritePaletteTransParamSet( 
			p_psl->soft_sprite_man,
			NNS_GfdGetPlttKeyAddr(plttKey),
			NNS_GfdGetPlttKeySize(plttKey) );

	//初期化
	PokeGra_set( &p_psl->soft_sprite[0], p_psl, MONSNO_NAETORU );
	PokeGra_set( &p_psl->soft_sprite[1], p_psl, MONSNO_HIKOZARU );
	PokeGra_set( &p_psl->soft_sprite[2], p_psl, MONSNO_POTTYAMA );

	// それぞれ非表示
	for( i=0; i<EV_POKESELECT_MONSNUM; i++ ){
		SoftSpriteParaSet( p_psl->soft_sprite[ i ], SS_PARA_VANISH, 1 );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモングラフィック登録
 *
 *	@param	p_soft_sprite
 *	@param	p_psl
 *	@param	monsno 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void PokeGra_set( SOFT_SPRITE** p_soft_sprite, EV_POKESELECT_PROC_WORK* p_psl, int monsno )
{
	SOFT_SPRITE_ARC arc_data;
	int sex;

	sex = PokeSexGetMonsNo( monsno, 0 );
	//最後の引数は、FormNoと個性乱数です by soga 2006.05.01
	PokeGraArcDataGet( &arc_data, monsno, sex, PARA_FRONT, PARA_NORMAL, NULL, NULL );
	*p_soft_sprite = SoftSpriteAdd( 
			p_psl->soft_sprite_man,
			&arc_data,
			EV_POKESELECT_POKEGRA_X, EV_POKESELECT_POKEGRA_Y, 1023,
			0, NULL, NULL );
}

//----------------------------------------------------------------------------
/**
 *	@brief	スプライトマネージャ破棄
 *
 *	@param	p_psl 
  *
 *	@return
 */
//-----------------------------------------------------------------------------
static void Softsprite_delete( EV_POKESELECT_PROC_WORK* p_psl )
{
	int i;
	
	for( i=0; i<EV_POKESELECT_MONSNUM; i++ ){

		if( p_psl->soft_sprite[i] ){
			SoftSpriteDel( p_psl->soft_sprite[i] );
		}
	}
	
	// ポケモン描画スプライトデータ破棄
	SoftSpriteEnd( p_psl->soft_sprite_man );
}

//----------------------------------------------------------------------------
/**
 *	@brief	swspシステム作成
 *
 *	@param	p_psl
 *	@param	heap 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void SwspSprite_init( EV_POKESELECT_PROC_WORK* p_psl, int heap )
{
	SWSP_SYSDATA swsp_sys_data = {
		SWSP_OBJNUM,
		SWSP_CHARNUM,			
		SWSP_PLTTNUM,
		0
	};
	swsp_sys_data.heap = heap;

	p_psl->swsp_sys = SWSP_SysInit( &swsp_sys_data );
}

//----------------------------------------------------------------------------
/**
 *	@brief	swspシステム破棄
 *
 *	@param	p_psl 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void SwspSprite_delete( EV_POKESELECT_PROC_WORK* p_psl )
{
	// ソフトウェアスプライト
	SWSP_SysDelete( p_psl->swsp_sys );
}

//----------------------------------------------------------------------------
/**
 *	@brief	セルアクター初期化
 *
 *	@param	p_psl		ワーク
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void Clact_init( EV_POKESELECT_PROC_WORK* p_psl, int heap )
{
	// セルアクターセット
	p_psl->clact_set = CLACT_U_SetEasyInit( CLACT_SET_WORK_NUM, &p_psl->oam_rend, heap );

	// セルアクター用リソース管理システム
	p_psl->res_manager[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerInit( CLACT_RES_DATA_TBL_NUM, CLACT_U_CHAR_RES, heap );
	p_psl->res_manager[ CLACT_U_PLTT_RES ] = CLACT_U_ResManagerInit( CLACT_RES_DATA_TBL_NUM, CLACT_U_PLTT_RES, heap );
	p_psl->res_manager[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerInit( CLACT_RES_DATA_TBL_NUM, CLACT_U_CELL_RES, heap );
	p_psl->res_manager[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerInit( CLACT_RES_DATA_TBL_NUM, CLACT_U_CELLANM_RES, heap );

	// OBJON
	GF_Disp_GX_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );
	GF_Disp_GXS_VisibleControl( GX_PLANEMASK_OBJ, VISIBLE_ON );
}

//----------------------------------------------------------------------------
/**
 *	@brief	セルアクター破棄
 *
 *	@param	p_psl 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void Clact_delete( EV_POKESELECT_PROC_WORK* p_psl )
{
	// セルアクターセット
	CLACT_DestSet( p_psl->clact_set );

	// セルアクター用リソース管理システム
	CLACT_U_ResManagerDelete( p_psl->res_manager[ CLACT_U_CHAR_RES ] );
	CLACT_U_ResManagerDelete( p_psl->res_manager[ CLACT_U_PLTT_RES ] );
	CLACT_U_ResManagerDelete( p_psl->res_manager[ CLACT_U_CELL_RES ] );
	CLACT_U_ResManagerDelete( p_psl->res_manager[ CLACT_U_CELLANM_RES ] );
}


//----------------------------------------------------------------------------
/**
 *	@brief	３Dオブジェクト設定
 *
 *	@param	p_obj			オブジェクトポインタ
 *	@param	mdl_dataidx		モデルアーカイブﾃﾞｰﾀｲﾝﾃﾞｯｸｽ
 *	@param	anm_dataidx		モデルアニメアーカイブﾃﾞｰﾀｲﾝﾃﾞｯｸｽ
 *	@param	heap			ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void Init_ev_3d_obj( EV_3D_ANM_OBJ* p_obj, int mdl_dataidx, int anm_dataidx, int heap, NNSFndAllocator* pallocator )
{
	memset( p_obj, 0, sizeof(EV_3D_ANM_OBJ) );
	Load_ev_3d_obj_mdl( p_obj, mdl_dataidx, heap );
	Load_ev_3d_obj_anm( p_obj, anm_dataidx, heap, pallocator );

	Set_ev_3d_obj_scal( p_obj, FX32_ONE, FX32_ONE, FX32_ONE );
}

//----------------------------------------------------------------------------
/**
 *	@brief	アニメのないオブジェクトの登録
 *
 *	@param	p_obj			オブジェクト
 *	@param	mdl_dataidx		モデルﾃﾞｰﾀｲﾝﾃﾞｯｸｽ
 *	@param	heap			ヒープ
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void Init_ev_3d_obj_no_anm( EV_3D_ANM_OBJ* p_obj, int mdl_dataidx, int heap )
{
	memset( p_obj, 0, sizeof(EV_3D_ANM_OBJ) );
	Load_ev_3d_obj_mdl( p_obj, mdl_dataidx, heap );
	Set_ev_3d_obj_scal( p_obj, FX32_ONE, FX32_ONE, FX32_ONE );
}
// モデルﾃﾞｰﾀ読み込み＆設定
static void Load_ev_3d_obj_mdl( EV_3D_ANM_OBJ* p_obj, int mdl_dataidx, int heap )
{
	// モデルﾃﾞｰﾀ読み込み
	p_obj->pResMdl = ArcUtil_Load( ARC_EV_POKESELECT_GRA, mdl_dataidx, FALSE, heap, ALLOC_TOP );

	// モデルﾃﾞｰﾀ取得
	p_obj->pModelSet	= NNS_G3dGetMdlSet( p_obj->pResMdl );
	p_obj->pModel		= NNS_G3dGetMdlByIdx( p_obj->pModelSet, 0 );
	p_obj->pMdlTex		= NNS_G3dGetTex( p_obj->pResMdl );
	
	// モデルﾃﾞｰﾀを転送
	LoadVRAMTexture( p_obj->pMdlTex );
	BindTexture( p_obj->pResMdl, p_obj->pMdlTex );

	// レンダーオブジェクトに登録
	NNS_G3dRenderObjInit( &p_obj->RenderObj, p_obj->pModel );
}
// アニメﾃﾞｰﾀ読み込み＆設定		load_ev_3d_obj_mdlの後に呼ぶ必要あり
static void Load_ev_3d_obj_anm( EV_3D_ANM_OBJ* p_obj, int mdl_dataidx, int heap, NNSFndAllocator* pallocator )
{
	// アニメﾃﾞｰﾀ読み込み
	p_obj->pResAnm = ArcUtil_Load( ARC_EV_POKESELECT_GRA, mdl_dataidx, FALSE, heap, ALLOC_TOP );

	//リソース取得
	p_obj->pOneResAnm = NNS_G3dGetAnmByIdx(p_obj->pResAnm,0);

	// アニメオブジェのメモリ確保
	p_obj->pAnmObj = NNS_G3dAllocAnmObj( 
			pallocator,
			p_obj->pOneResAnm,
			p_obj->pModel );

	// アニメオブジェ初期化
	NNS_G3dAnmObjInit(
		p_obj->pAnmObj,
		p_obj->pOneResAnm,
		p_obj->pModel,
		p_obj->pMdlTex );

	// レンダーオブジェクトに登録
	NNS_G3dRenderObjAddAnmObj( &p_obj->RenderObj, p_obj->pAnmObj );
}

//----------------------------------------------------------------------------
/**
 *	@brief	3Dオブジェクトの破棄
 *
 *	@param	p_obj	オブジェクト
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void Delete_ev_3d_obj( EV_3D_ANM_OBJ* p_obj, NNSFndAllocator* pallocator )
{
	// 全リソース破棄
	if(p_obj->pResMdl){
		sys_FreeMemoryEz( p_obj->pResMdl );
	}
	if(p_obj->pResAnm){
		NNS_G3dFreeAnmObj( pallocator, p_obj->pAnmObj );
		sys_FreeMemoryEz( p_obj->pResAnm );
	}

	memset( p_obj, 0, sizeof(EV_3D_ANM_OBJ) );
}

//----------------------------------------------------------------------------
/**
 *	@brief	描画処理
 *
 *	@param	p_obj 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void Draw_ev_3d_obj( EV_3D_ANM_OBJ* p_obj )
{
	MtxFx33 mtx;
	MtxFx33 calc_mtx;


	// 回転行列作成
	MTX_Identity33( &mtx );
	MTX_RotX33( &calc_mtx, FX_SinIdx( p_obj->rota_x ), FX_CosIdx( p_obj->rota_x ) );
	MTX_Concat33( &calc_mtx, &mtx, &mtx );
	MTX_RotY33( &calc_mtx, FX_SinIdx( p_obj->rota_y ), FX_CosIdx( p_obj->rota_y ) );
	MTX_Concat33( &calc_mtx, &mtx, &mtx );
	MTX_RotZ33( &calc_mtx, FX_SinIdx( p_obj->rota_z ), FX_CosIdx( p_obj->rota_z ) );
	MTX_Concat33( &calc_mtx, &mtx, &mtx );

	
	if( p_obj->draw_flag ){
		simple_3DModelDraw( &p_obj->RenderObj, &p_obj->mat, &mtx, &p_obj->scal );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	描画フラグの設定
 *
 *	@param	p_obj	オブジェクト
 *	@param	flag	フラグ		TRUE描画 
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void Set_ev_3d_obj_draw( EV_3D_ANM_OBJ* p_obj, BOOL flag )
{
	p_obj->draw_flag = flag;
}

//----------------------------------------------------------------------------
/**
 *	@brief	座標設定
 *	
 *	@param	p_obj	オブジェクト
 *	@param	x		ｘ座標
 *	@param	y		ｙ座標
 *	@param	z		ｚ座標
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void Set_ev_3d_obj_mat( EV_3D_ANM_OBJ* p_obj, fx32 x, fx32 y, fx32 z )
{
	p_obj->mat.x = x;
	p_obj->mat.y = y;
	p_obj->mat.z = z;
}

//----------------------------------------------------------------------------
/**
 *	@brief	拡縮値
 *
 *	@param	p_obj	オブジェクト
 *	@param	x		X拡大値
 *	@param	y		Y拡大値
 *	@param	z		Z拡大値
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void Set_ev_3d_obj_scal( EV_3D_ANM_OBJ* p_obj, fx32 x, fx32 y, fx32 z )
{
	p_obj->scal.x = x;
	p_obj->scal.y = y;
	p_obj->scal.z = z;
}

//----------------------------------------------------------------------------
/**
 *	@brief	回転角度設定
 *
 *	@param	p_obj	オブジェクト
 *	@param	x	ｘ軸回転
 *	@param	y	ｙ軸回転
 *	@param	z	ｚ軸回転
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void Set_ev_3d_obj_rota( EV_3D_ANM_OBJ* p_obj, u16 x, u16 y, u16 z )
{
	p_obj->rota_x = x;
	p_obj->rota_y = y;
	p_obj->rota_z = z;
}

//----------------------------------------------------------------------------
/**
 *	@brief	アニメーション
 *
 *	@param	p_obj 
 *
 *	@return	TRUE	終了
 */
//-----------------------------------------------------------------------------
static BOOL Anm_ev_3d_obj( EV_3D_ANM_OBJ* p_obj )
{
	fx32 end_frame = NNS_G3dAnmObjGetNumFrame( p_obj->pAnmObj );
	BOOL ret;
	
	if( (p_obj->frame + FX32_ONE) < end_frame ){
		p_obj->frame += FX32_ONE;
		ret = FALSE;
	}else{
		p_obj->frame = end_frame;
		ret = TRUE;
	}
	NNS_G3dAnmObjSetFrame( p_obj->pAnmObj, p_obj->frame );

	return ret;
}
static void Anm_ev_3d_obj_loop( EV_3D_ANM_OBJ* p_obj )
{
	fx32 end_frame = NNS_G3dAnmObjGetNumFrame( p_obj->pAnmObj );
	
	p_obj->frame = (p_obj->frame + FX32_ONE) % end_frame;

	NNS_G3dAnmObjSetFrame( p_obj->pAnmObj, p_obj->frame );
}

//----------------------------------------------------------------------------
/**
 *	@brief	アニメーション数設定
 *
 *	@param	p_obj
 *	@param	anm			ﾌﾚｰﾑ数
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void Anm_ev_3d_obj_set( EV_3D_ANM_OBJ* p_obj, fx32 anm )
{
	p_obj->frame = anm;
	NNS_G3dAnmObjSetFrame( p_obj->pAnmObj, anm );
}

//----------------------------------------------------------------------------
/**
 *	@brief	アニメーションﾌﾚｰﾑ数取得
 *
 *	@param	p_obj 
 *
 *	@return	ﾌﾚｰﾑ数	
 */
//-----------------------------------------------------------------------------
static fx32 Anm_ev_3d_obj_get( EV_3D_ANM_OBJ* p_obj )
{
	return p_obj->frame;
;
}

//----------------------------------------------------------------------------
/**
 *	@brief	3dオブジェを作成する
 *
 *	@param	p_psl	ワーク
 *	@param	heap	ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void Ev3dobj_make( EV_POKESELECT_PROC_WORK* p_psl, int heap )
{
	int i;

	// AUTOアニメ素材
	Init_ev_3d_obj( &p_psl->ev_3d_obj[ POKESELECT_AUTOANM ],
			NARC_ev_pokeselect_psel_all_nsbmd, NARC_ev_pokeselect_psel_all_nsbca,
			heap, &p_psl->allocator );
	Set_ev_3d_obj_draw( &p_psl->ev_3d_obj[ POKESELECT_AUTOANM ], TRUE );

	// かばんモデル
	Init_ev_3d_obj_no_anm( &p_psl->ev_3d_obj[ POKESELECT_BAG ],
			NARC_ev_pokeselect_psel_trunk_nsbmd, heap );
	Set_ev_3d_obj_draw( &p_psl->ev_3d_obj[ POKESELECT_BAG ], FALSE );

	// ﾓﾝｽﾀｰボールモデル
	for( i=POKESELECT_BALL_LEFT; i<=POKESELECT_BALL_RIGHT; i++ ){
		Init_ev_3d_obj( &p_psl->ev_3d_obj[ i ],
				NARC_ev_pokeselect_psel_mb_a_nsbmd + (i-POKESELECT_BALL_LEFT) * 2,
				NARC_ev_pokeselect_psel_mb_a_nsbca + (i-POKESELECT_BALL_LEFT) * 2,
				heap, &p_psl->allocator );
		Set_ev_3d_obj_draw( &p_psl->ev_3d_obj[ i ], FALSE );
	}

	// 地形モデル
	Init_ev_3d_obj_no_anm( &p_psl->ev_3d_obj[ POKESELECT_GROUND ],
			NARC_ev_pokeselect_pmsel_bg_nsbmd, heap );
	Set_ev_3d_obj_draw( &p_psl->ev_3d_obj[ POKESELECT_GROUND ], TRUE );
	
	Set_ev_3d_obj_mat( &p_psl->ev_3d_obj[ POKESELECT_GROUND ],
			EV_POKESELECT_DRAW_GRUND_X,
			EV_POKESELECT_DRAW_GRUND_Y,
			EV_POKESELECT_DRAW_GRUND_Z);
	Set_ev_3d_obj_scal( &p_psl->ev_3d_obj[ POKESELECT_GROUND ],
			EV_POKESELECT_DRAW_GRUND_SCA_X,
			EV_POKESELECT_DRAW_GRUND_SCA_Y,
			EV_POKESELECT_DRAW_GRUND_SCA_Z);
	Set_ev_3d_obj_rota(  &p_psl->ev_3d_obj[ POKESELECT_GROUND ],
			EV_POKESELECT_DRAW_GRUND_ROTA_X,
			EV_POKESELECT_DRAW_GRUND_ROTA_Y,
			EV_POKESELECT_DRAW_GRUND_ROTA_Z);
}

//----------------------------------------------------------------------------
/**
 *	@brief	３Dオブジェ破棄
 *
 *	@param	p_psl
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void Ev3dobj_delete( EV_POKESELECT_PROC_WORK* p_psl )
{
	int i;

	for( i=0; i<POKESELECT_3DOBJ_NUM; i++ ){
		Delete_ev_3d_obj( &p_psl->ev_3d_obj[ i ], &p_psl->allocator );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	3Dオブジェクト描画処理
 *
 *	@param	p_psl 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void Ev3dobj_draw( EV_POKESELECT_PROC_WORK* p_psl )
{
	int i;

	// ライトとアンビエント
	NNS_G3dGlbLightVector( 0, 0, -FX32_ONE, 0 );
	NNS_G3dGlbLightColor( 0, GX_RGB( 31,31,31 ) );
	NNS_G3dGlbMaterialColorDiffAmb( GX_RGB( 31,31,31 ), GX_RGB( 31,31,31 ), FALSE );
	NNS_G3dGlbMaterialColorSpecEmi( GX_RGB( 31,31,31 ), GX_RGB( 31,31,31 ), FALSE );
	
	
	for( i=0; i<POKESELECT_3DOBJ_NUM; i++ ){
		Draw_ev_3d_obj( &p_psl->ev_3d_obj[ i ] );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	動作メイン
 *
 *	@param	p_psl 
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	つづく
 */
//-----------------------------------------------------------------------------
static BOOL EV_PokeSelect_MoveData( EV_POKESELECT_PROC_WORK* p_psl, int heap )
{
	if( p_psl->move_lock == TRUE ){
		return FALSE;
	}
	
	switch( Move_seq_get( p_psl ) ){
	case POKESELECT_SEQ_INIT:
		break;

	case POKESELECT_SEQ_WAIT:
		break;

	case POKESELECT_SEQ_AUTOANM:		// AUTOアニメ
		break;
		
	case POKESELECT_SEQ_SELECT:		// 選択
		Move_select( p_psl );
		if( sys.trg & PAD_BUTTON_A ){
			Move_seq_add( p_psl, 1 );

			Snd_SePlay( EV_POKESELE_SND_DECIDE );
		}

#ifdef DEBUG_EV_POKESELE
		// デバック
		EV_PokeSelect_Deback_Anm( p_psl );
#endif
		break;
		
	case POKESELECT_SEQ_QUESTION:	// 確認
		break;

	case POKESELECT_SEQ_END:
		return TRUE;

	default:
		break;
	}
	return FALSE;
}

#ifdef DEBUG_EV_POKESELE
static void EV_PokeSelect_Deback_Anm( EV_POKESELECT_PROC_WORK* p_psl )
{
	CAMERA_ANGLE angle;
	
	// デバック機能
	if( sys.trg & PAD_BUTTON_B ){
		Move_seq_set( p_psl, 0 );
		Anm_ev_3d_obj_set( &p_psl->ev_3d_obj[POKESELECT_AUTOANM], 0 );
		Set_ev_3d_obj_draw( &p_psl->ev_3d_obj[ POKESELECT_AUTOANM ], TRUE );
		Set_ev_3d_obj_draw( &p_psl->ev_3d_obj[ POKESELECT_BAG ], FALSE );
		Set_ev_3d_obj_draw( &p_psl->ev_3d_obj[ POKESELECT_BALL_LEFT ], FALSE );
		Set_ev_3d_obj_draw( &p_psl->ev_3d_obj[ POKESELECT_BALL_CENTER ], FALSE );
		Set_ev_3d_obj_draw( &p_psl->ev_3d_obj[ POKESELECT_BALL_RIGHT ], FALSE );

		angle.x = CAMERA_ANGLE_X;
		angle.y = CAMERA_ANGLE_Y;
		angle.z = CAMERA_ANGLE_Z;
		GFC_SetCameraAngleRev( &angle, p_psl->p_camera );
		GFC_SetCameraDistance( CAMERA_DISTANCE, p_psl->p_camera );
		p_psl->camera_target.z = CAMERA_TARGET_Z;

		// カーソルを合わせる
		Cursor_clact_set_draw_flag( &p_psl->cursor, FALSE );

		// クリーン
		GF_BGL_BmpWinOff( p_psl->p_bmp_mfont );
		FontSubbg_bmpwin_clean( p_psl );
	}
}
#endif

//----------------------------------------------------------------------------
/**
 *	@brief	描画動作メイン
 *
 *	@param	p_psl 
 */
//-----------------------------------------------------------------------------
static void EV_PokeSelect_MoveDraw( EV_POKESELECT_PROC_WORK* p_psl, int heap )
{
	
	switch( Move_seq_get( p_psl ) ){
	case POKESELECT_SEQ_INIT:
		// 動作lockする
		p_psl->move_lock = TRUE;
		p_psl->draw_count = POKESELECT_MONNSUTA_START_WAIT;
		Move_seq_add( p_psl, 1 );
		//半透明設定する
		G2_SetBlendAlpha( GX_BLEND_PLANEMASK_BG3, GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_OBJ, BG_FONTSUBBMP_ALPHA, 16 - BG_FONTSUBBMP_ALPHA );
		break;

	case POKESELECT_SEQ_WAIT:
		p_psl->draw_count --;
		if( p_psl->draw_count < 0 ){
			Move_seq_add( p_psl, 1 );

			Snd_SePlay( EV_POKESELE_SND_BAGOPEN );
		}
		break;

	case POKESELECT_SEQ_AUTOANM:		// AUTOアニメ
		// アニメーションさせる
		// アニメ終了後選択へ
		if( Anm_ev_3d_obj( &p_psl->ev_3d_obj[POKESELECT_AUTOANM] ) ){
			// 自分を消し、ばらばらなオブジェを出す
			Set_ev_3d_obj_draw( &p_psl->ev_3d_obj[ POKESELECT_AUTOANM ], FALSE );
			Set_ev_3d_obj_draw( &p_psl->ev_3d_obj[ POKESELECT_BAG ], TRUE );
			Set_ev_3d_obj_draw( &p_psl->ev_3d_obj[ POKESELECT_BALL_LEFT ], TRUE );
			Set_ev_3d_obj_draw( &p_psl->ev_3d_obj[ POKESELECT_BALL_CENTER ], TRUE );
			Set_ev_3d_obj_draw( &p_psl->ev_3d_obj[ POKESELECT_BALL_RIGHT ], TRUE );

			Move_seq_add( p_psl, 1 );
		}
		break;
		
	case POKESELECT_SEQ_SELECT:		// 選択
		DrawMoveSelect( p_psl, heap );
		break;
		
	case POKESELECT_SEQ_QUESTION:	// 確認
		DrawMoveQuestion( p_psl, heap );
		break;

	case POKESELECT_SEQ_END:
		G2_BlendNone();
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	描画メイン
 *
 *	@param	p_psl 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void EV_PokeSelect_Draw( EV_POKESELECT_PROC_WORK* p_psl )
{
	//３Ｄ描画開始
	GF_G3X_Reset();

	NNS_G3dGePushMtx();
	{
		NNS_G3dGeFlushBuffer();

		// ソフトウェアスプライトの描画
		// カメラセットアップ
		NNS_G2dSetupSoftwareSpriteCamera();
		// ソフトウェアスプライト描画
		SoftSpriteMain( p_psl->soft_sprite_man );
		SWSP_SysDraw( p_psl->swsp_sys );
	}
	NNS_G3dGePopMtx(1);


	NNS_G3dGePushMtx();
	{
		// カメラ設定
		GFC_CameraLookAt();

		//　モデルの描画
		Ev3dobj_draw( p_psl );
	}
	NNS_G3dGePopMtx(1);
	

	/* ジオメトリ＆レンダリングエンジン関連メモリのスワップ */
	GF_G3_RequestSwapBuffers(GX_SORTMODE_AUTO, GX_BUFFERMODE_Z);

	// セルアクター描画
	CLACT_Draw( p_psl->clact_set );
}

//----------------------------------------------------------------------------
/**
 *	@brief	カメラ作成＆初期化
 *
 *	@param	p_psl		ワーク
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void Camera_init( EV_POKESELECT_PROC_WORK* p_psl, int heap )
{
	// カメラアロック
	p_psl->p_camera = GFC_AllocCamera( heap );

	// 初期化
	Camera_init_param( p_psl->p_camera, &p_psl->camera_target );
}

//----------------------------------------------------------------------------
/**
 *	@brief	カメラ初期設定
 *
 *	@param	p_camera	カメラ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void Camera_init_param( GF_CAMERA_PTR p_camera, VecFx32* p_target )
{
	CAMERA_ANGLE angle;
	VecFx32 up;
	
	p_target->x = CAMERA_TARGET_X;
	p_target->y = CAMERA_TARGET_Y;
	p_target->z = CAMERA_TARGET_Z;

	angle.x = CAMERA_ANGLE_X;
	angle.y = CAMERA_ANGLE_Y;
	angle.z = CAMERA_ANGLE_Z;

	
	GFC_InitCameraTDA( 
			p_target, CAMERA_DISTANCE,
			&angle, CAMERA_PEARCE,
			GF_CAMERA_PERSPECTIV,
			TRUE,	
			p_camera
			);

	up.x = 0;
	up.y = FX32_ONE;
	up.z = 0;
	GFC_SetCamUp( &up, p_camera );
	
	GFC_AttachCamera( p_camera );
}

//----------------------------------------------------------------------------
/**
 *	@brief	カメラ破棄
 *
 *	@param	p_psl		ワーク
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void Camera_delete( EV_POKESELECT_PROC_WORK* p_psl )
{
	GFC_FreeCamera( p_psl->p_camera );
}

//----------------------------------------------------------------------------
/**
 *	@brief	座標セレクト
 *
 *	@param	p_psl 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void Select_matrix_make( EV_POKESELECT_PROC_WORK* p_psl )
{
	int i;
	
	// 座標位置ワーク作成
	for( i=0; i<EV_POKESELECT_MONSNUM; i++ ){
		switch( i ){
		case POKESELECT_LEFT_BALL:
			p_psl->select_matrix[ i ][0] = EV_POKESELECT_DRAW_MAT_BALL_LEFT_X;
			p_psl->select_matrix[ i ][1] = EV_POKESELECT_DRAW_MAT_BALL_LEFT_Y;
			p_psl->select_matrix[ i ][2] = EV_POKESELECT_DRAW_MAT_BALL_LEFT_Z;
			break;
		case POKESELECT_CENTER_BALL:
			p_psl->select_matrix[ i ][0] = EV_POKESELECT_DRAW_MAT_BALL_CENTER_X;
			p_psl->select_matrix[ i ][1] = EV_POKESELECT_DRAW_MAT_BALL_CENTER_Y;
			p_psl->select_matrix[ i ][2] = EV_POKESELECT_DRAW_MAT_BALL_CENTER_Z;
			break;
		case POKESELECT_RIGHT_BALL:
			p_psl->select_matrix[ i ][0] = EV_POKESELECT_DRAW_MAT_BALL_RIGHT_X;
			p_psl->select_matrix[ i ][1] = EV_POKESELECT_DRAW_MAT_BALL_RIGHT_Y;
			p_psl->select_matrix[ i ][2] = EV_POKESELECT_DRAW_MAT_BALL_RIGHT_Z;
			break;
		}
	}

	// 2d座標
	for( i=0; i<EV_POKESELECT_MONSNUM; i++ ){
		switch( i ){
		case POKESELECT_LEFT_BALL:
			p_psl->select_2_matrix[ i ][0] = EV_POKESELECT_DRAW_MAT_BALL_LEFT_2X;
			p_psl->select_2_matrix[ i ][1] = EV_POKESELECT_DRAW_MAT_BALL_LEFT_2Y;
			break;
		case POKESELECT_CENTER_BALL:
			p_psl->select_2_matrix[ i ][0] = EV_POKESELECT_DRAW_MAT_BALL_CENTER_2X;
			p_psl->select_2_matrix[ i ][1] = EV_POKESELECT_DRAW_MAT_BALL_CENTER_2Y;
			break;
		case POKESELECT_RIGHT_BALL:
			p_psl->select_2_matrix[ i ][0] = EV_POKESELECT_DRAW_MAT_BALL_RIGHT_2X;
			p_psl->select_2_matrix[ i ][1] = EV_POKESELECT_DRAW_MAT_BALL_RIGHT_2Y;
			break;
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	3dオブジェの座標を設定
 *
 *	@param	p_psl 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void Select_matrix_set_3dobj( EV_POKESELECT_PROC_WORK* p_psl )
{
	int i;
	for( i=0; i<EV_POKESELECT_MONSNUM; i++ ){
		Set_ev_3d_obj_mat( &p_psl->ev_3d_obj[i + POKESELECT_BALL_LEFT], 
				p_psl->select_matrix[i][0] << FX32_SHIFT,
				p_psl->select_matrix[i][1] << FX32_SHIFT,
				p_psl->select_matrix[i][2] << FX32_SHIFT );
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	セレクトポケモンを変更する動作
 *
 *	@param	p_psl	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void Move_select( EV_POKESELECT_PROC_WORK* p_psl )
{
	if( sys.trg & PAD_KEY_LEFT ){
		if( p_psl->now_select_no - 1 >= 0 ){
			p_psl->now_select_no -= 1;
			Snd_SePlay( EV_POKESELE_SND_SELECT );
		}
	}

	if( sys.trg & PAD_KEY_RIGHT ){
		if( p_psl->now_select_no + 1 < EV_POKESELECT_MONSNUM ){
			p_psl->now_select_no += 1;
			Snd_SePlay( EV_POKESELE_SND_SELECT );
		}
	}
}


//-----------------------------------------------------------------------------
/**
 *		シーケンス操作
 */
//-----------------------------------------------------------------------------
static void Move_seq_add( EV_POKESELECT_PROC_WORK* p_psl, int no )
{
	p_psl->seq += no;
	p_psl->draw_seq = 0;
}
static void Move_seq_set( EV_POKESELECT_PROC_WORK* p_psl, int no )
{
	p_psl->seq = no;
	p_psl->draw_seq = 0;
}
static int Move_seq_get( EV_POKESELECT_PROC_WORK* p_psl )
{
	return p_psl->seq;
}


//----------------------------------------------------------------------------
/**
 *	@brief	選択ﾓﾝｽﾀｰボール動作
 *
 *	@param	p_psl	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void DrawMoveSelect( EV_POKESELECT_PROC_WORK* p_psl, int heap )
{
	switch( p_psl->draw_seq ){
	case 0:
		//	カメラ動作
		EvCameraMoveReq( &p_psl->camera_move, p_psl->p_camera, &p_psl->camera_target );
		
		// ビットマップ面を表示させたりする
		GF_Disp_GX_VisibleControl(GX_PLANEMASK_BG1, VISIBLE_ON );
		p_psl->draw_seq++;
		break;

	case 1:	// 待機
		if( EvCameraMoveEndCheck( &p_psl->camera_move ) ){
			p_psl->draw_count = POKESELECT_MSSAGE_WAIT;	
			p_psl->draw_seq ++;
		}
		break;

	case 2:		// ワンテンポ
		p_psl->draw_count --;

		if( p_psl->draw_count < 0 ){
			Draw_move_select_cursor( p_psl );
			p_psl->draw_seq ++;
		}
		break;

	case 3:

		// モンスターボールだ！これでたたかおう
		p_psl->msg_index = Fontbg_bmpwin_str_buff( p_psl->p_bmp_mfont, heap, NARC_msg_ev_pokeselect_dat, EV_POKESELECT_00, BG_FONTBMP_PRICOLOR, p_psl->msg_speed, &p_psl->p_glb_str_buff );

		p_psl->draw_seq ++;
		break;

	case 4:
		//メッセージ終了待ち
		if( GF_MSG_PrintEndCheck( p_psl->msg_index ) == 0 ){
			Fontbg_bmpwin_strbuff_clear( p_psl );
			p_psl->draw_seq ++;
		}
		break;

	case 5:
		// どれにする？
		p_psl->msg_index = Fontbg_bmpwin_str_buff( p_psl->p_bmp_mfont, heap, NARC_msg_ev_pokeselect_dat, EV_POKESELECT_08, BG_FONTBMP_PRICOLOR, p_psl->msg_speed, &p_psl->p_glb_str_buff );
		p_psl->draw_seq ++;
		break;

	case 6:
		//メッセージ終了待ち
		if( GF_MSG_PrintEndCheck( p_psl->msg_index ) == 0 ){
			Fontbg_bmpwin_strbuff_clear( p_psl );
			p_psl->draw_seq ++;
		}
		break;

	case 7:
		// カーソル描画
		Cursor_clact_set_draw_flag( &p_psl->cursor, TRUE );
		p_psl->move_lock = FALSE;	// lock解除
		p_psl->draw_seq ++;
		break;
	
	case 8:
		// 選択されたﾓﾝｽﾀｰボールを動かす
		Draw_move_select_monsball( p_psl );		

		// カーソルを合わせる
		Draw_move_select_cursor( p_psl );

		// カーソルの位置のポケモン情報描画
//		FontSubbg_bmpwin_select( p_psl );	非表示にしました。
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	選択したﾓﾝｽﾀｰボールを動かす
 *
 *	@param	p_psl 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void Draw_move_select_monsball( EV_POKESELECT_PROC_WORK* p_psl )
{
	int i;
	for( i=0; i<EV_POKESELECT_MONSNUM; i++ ){
		if( p_psl->now_select_no == i ){
			Anm_ev_3d_obj_loop( &p_psl->ev_3d_obj[ POKESELECT_BALL_LEFT + i ] );
		}else{
			Anm_ev_3d_obj_set( &p_psl->ev_3d_obj[ POKESELECT_BALL_LEFT + i ], 0 );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	カーソルを合わせる
 *
 *	@param	p_psl	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void Draw_move_select_cursor( EV_POKESELECT_PROC_WORK* p_psl )
{
	Cursor_clact_set_matrix( &p_psl->cursor, p_psl->select_2_matrix[ p_psl->now_select_no ][0], p_psl->select_2_matrix[ p_psl->now_select_no ][1] );
}


//----------------------------------------------------------------------------
/**
 *	@brief	確認画面描画
 *
 *	@param	p_psl
 *	@param	heap 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void DrawMoveQuestion( EV_POKESELECT_PROC_WORK* p_psl, int heap )
{
	u32 ret;
	
	switch( p_psl->draw_seq ){
	case 0:

		// カーソル非描画
		Cursor_clact_set_draw_flag( &p_psl->cursor, FALSE );

		// カーソルを合わせる
		Draw_move_select_cursor( p_psl );
		
		// 文字列
		FontSubbg_bmpwin_clean( p_psl );
		
		// フェード処理
		QuestionFade_Req( p_psl );

		p_psl->draw_seq++;
		p_psl->move_lock = TRUE;	// lock
		break;

	case 1:	// 待機
		CircleWnd_Gra_Draw( &p_psl->circle_wnd, TRUE );
		SoftSpriteParaSet( p_psl->soft_sprite[ p_psl->now_select_no ], SS_PARA_VANISH, 0 );
		if( QuestionFade_EndCheck( p_psl ) ){

			// ポケモン鳴き声を流す
			Snd_PMVoicePlay( EV_PokeSelect_SelectNoMonsnoGet( p_psl->now_select_no ) );
		
			p_psl->draw_seq ++;
		}
		break;

	case 2:	// WNDがちゃんと大きくなってから文字列変更
		// このぽけもんでよいですか？ 
		Fontbg_bmpwin_str( p_psl->p_bmp_mfont, heap, NARC_msg_ev_pokeselect_dat, EV_POKESELECT_02 + p_psl->now_select_no, BG_FONTBMP_PRICOLOR, MSG_NO_PUT );

		// ハイ、いいえ作成
		p_psl->p_yes_no_menu = BmpYesNoSelectInit( p_psl->p_bg, &p_psl->bmp_data, BG_YESNOBMP_CG_CHR_OFS, BG_YESNOBMP_COLOR, heap );

		p_psl->move_lock = FALSE;	// lock解除
		p_psl->draw_seq ++;
		break;

	case 3:
		ret = BmpYesNoSelectMain( p_psl->p_yes_no_menu, heap );

		switch( ret ){
		case BMPMENU_NULL:
			break;
			
		case 0:
			// 最終分岐へ
			Move_seq_add( p_psl, 1 );
			break;
			
		case BMPMENU_CANCEL:
			p_psl->draw_seq++;

			// 逆フェード
			QuestionReFade_Req( p_psl );
			break;
		}
		break;

	case 4:		// 選択画面に戻る
		if( QuestionFade_EndCheck( p_psl ) ){
			// 前に戻る
			Move_seq_add( p_psl, -1 );

			// もう選択画面の状態にする
			p_psl->draw_seq = 7;

			CircleWnd_Gra_Draw( &p_psl->circle_wnd, FALSE );
			SoftSpriteParaSet( p_psl->soft_sprite[ p_psl->now_select_no ], SS_PARA_VANISH, 1 );

			// どどれにする？
			p_psl->msg_index = Fontbg_bmpwin_str( p_psl->p_bmp_mfont, heap, NARC_msg_ev_pokeselect_dat, EV_POKESELECT_08, BG_FONTBMP_PRICOLOR, MSG_NO_PUT );
		}
		break;

	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	文字列の描画
 *
 *	@param	p_psl
 *	@param	heap
 *	@param	arcidx
 *	@param	
 *
 *	@return	msg_index
 */
//-----------------------------------------------------------------------------
static u8 Fontbg_bmpwin_str( GF_BGL_BMPWIN* p_bmp, int heap, int arcidx, int msgidx, GF_PRINTCOLOR color, u32 wait )
{
	MSGDATA_MANAGER* msg_data;
	STRBUF* str;
	u8 msg_index;

	// 文字列取得
	msg_data = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, arcidx, heap );
	GF_ASSERT( msg_data );
	str = MSGMAN_AllocString( msg_data, msgidx );

	// ビットマップ初期化
	GF_BGL_BmpWinDataFill( p_bmp, 15 );

	// 文字列書き込み
	msg_index = GF_STR_PrintColor( p_bmp, FONT_TALK, str, 0, 0, wait, color, NULL );
												// ↑描画位置
	BmpTalkWinWrite( p_bmp, WINDOW_TRANS_ON, BG_FONT_CG_OFS, BG_FONT_COLOR );

	STRBUF_Delete( str );
	MSGMAN_Delete( msg_data );

	return msg_index;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ウエイト文字列描画用　関数　STRBUF保存
 *	
 *	@param	p_bmp		ビットマップ
 *	@param	heap		ヒープ
 *	@param	arcidx		アーカイブIDX
 *	@param	msgidx		メッセージIDX
 *	@param	color		カラー
 *	@param	wait		ウエイト
 *	@param	pp_glb_str	文字列バッファポインタ格納先
 *
 *	@return	メッセージインデックス
 */
//-----------------------------------------------------------------------------
static u8 Fontbg_bmpwin_str_buff( GF_BGL_BMPWIN* p_bmp, int heap, int arcidx, int msgidx, GF_PRINTCOLOR color, u32 wait, STRBUF** pp_glb_str )
{
	MSGDATA_MANAGER* msg_data;
	u8 msg_index;

	GF_ASSERT( (*pp_glb_str) == NULL );

	// 文字列取得
	msg_data = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, arcidx, heap );
	GF_ASSERT( msg_data );
	*pp_glb_str = MSGMAN_AllocString( msg_data, msgidx );

	// ビットマップ初期化
	GF_BGL_BmpWinDataFill( p_bmp, 15 );

	// 文字列書き込み
	msg_index = GF_STR_PrintColor( p_bmp, FONT_TALK, *pp_glb_str, 0, 0, wait, color, NULL );
												// ↑描画位置
	BmpTalkWinWrite( p_bmp, WINDOW_TRANS_ON, BG_FONT_CG_OFS, BG_FONT_COLOR );

	MSGMAN_Delete( msg_data );

	return msg_index;
}

//----------------------------------------------------------------------------
/**
 *	@brief	グローバルSTRBUFFのクリア
 *
 *	@param	p_psl	ワーク
 */
//-----------------------------------------------------------------------------
static void Fontbg_bmpwin_strbuff_clear( EV_POKESELECT_PROC_WORK* p_psl )
{
	STRBUF_Delete( p_psl->p_glb_str_buff );
	p_psl->p_glb_str_buff = NULL;
}

//----------------------------------------------------------------------------
/**
 *	@brief	YES　NO　ﾃﾞｰﾀ作成
 *
 *	@param	p_psl
 *	@param	heap 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void Fontbg_yesno_bmp_dat_make( EV_POKESELECT_PROC_WORK* p_psl, int heap )
{
	p_psl->bmp_data.frm_num = GF_BGL_FRAME1_M;
	p_psl->bmp_data.pos_x	= BG_YESNOBMP_X;
	p_psl->bmp_data.pos_y	= BG_YESNOBMP_Y;
	p_psl->bmp_data.siz_x	= BG_YESNOBMP_CX;
	p_psl->bmp_data.siz_y	= BG_YESNOBMP_CY;
	p_psl->bmp_data.palnum	= BG_YESNOBMP_STR_COLOR;
	p_psl->bmp_data.chrnum	= BG_YESNOBMP_CG_OFS;


	// 枠を転送
	MenuWinGraphicSet( p_psl->p_bg, GF_BGL_FRAME1_M, BG_YESNOBMP_CG_CHR_OFS, BG_YESNOBMP_COLOR, 0, heap );

	// システムフォントカラーパレット読み込み
	SystemFontPaletteLoad( PALTYPE_MAIN_BG, BG_YESNOBMP_STR_COLOR*32, heap );	
}

//----------------------------------------------------------------------------
/**
 *	@brief	動作パラメータ
 *
 *	@param	p_data	ワーク
 *	@param	s_num	開始値
 *	@param	e_num	終了値
 *	@param	count	最大カウント
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void EvMoveInit( EV_MOVE_PARAM* p_data, s32 s_num, s32 e_num, s32 count )
{
	p_data->data		= s_num;
	p_data->s_data		= s_num;
	p_data->add_data	= e_num - s_num;
	p_data->count_max	= count;
}

//----------------------------------------------------------------------------
/**
 *	@brief	動作計算部分
 *
 *	@param	p_data
 *	@param	count	現在カウント
 *
 *	@retval TRUE	終了
 *	@retval	FALSE	つうじょう
 */
//-----------------------------------------------------------------------------
static BOOL EvMoveMain( EV_MOVE_PARAM* p_data, s32 count )
{
	s32 local_count;
	BOOL ret;
	s32 num;
	
	if( count >= p_data->count_max ){
		local_count = p_data->count_max;
		ret = TRUE;
	}else{
		local_count = count;
		ret = FALSE;
	}

	// 計算
	num = p_data->add_data * count;
	num = num / p_data->count_max;
	num += p_data->s_data;

	// 設定
	p_data->data = num;

	return ret;
}


//----------------------------------------------------------------------------
/**
 *	@brief	カメラ動作設定
 *
 *	@param	p_camera_move	カメラ動作パラメータ
 *	@param	p_camera		カメラワーク
 *	@param	p_target		ターゲット座標ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void EvCameraMoveReq( EV_CAMERA_MOVE* p_camera_move, GF_CAMERA_PTR p_camera, VecFx32* p_target )
{
	// 登録済みチェック
	GF_ASSERT( p_camera_move->tcb == NULL );
	
	EvMoveInit( &p_camera_move->x_rota, CAMERA_ANGLE_X, CAMERA_ANGLE_AF_X, CAMERA_MOVE_AF_COUNT );
	EvMoveInit( &p_camera_move->dist, CAMERA_DISTANCE, CAMERA_DISTANCE_AF, CAMERA_MOVE_AF_COUNT );
	EvMoveInit( &p_camera_move->target_z, CAMERA_TARGET_Z, CAMERA_TARGET_AF_Z, CAMERA_MOVE_AF_COUNT );

	p_camera_move->end_flag = FALSE;
	p_camera_move->p_camera	= p_camera;
	p_camera_move->p_target = p_target;

	p_camera_move->count = 0;
 
	TCB_Add( EvCameraMoveTcb, p_camera_move, 0 );
}

//----------------------------------------------------------------------------
/**
 *	@brief
 *
 *	@param	tcb
 *	@param	work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void EvCameraMoveTcb( TCB_PTR tcb, void* work )
{
	EV_CAMERA_MOVE* p_data = work;
	BOOL check;
	CAMERA_ANGLE angle;
	
	check = EvMoveMain( &p_data->x_rota, p_data->count );
	EvMoveMain( &p_data->dist, p_data->count );
	EvMoveMain( &p_data->target_z, p_data->count );

	// カメラに反映
	angle.x = p_data->x_rota.data;
	angle.y = CAMERA_ANGLE_Y;
	angle.z = CAMERA_ANGLE_Z;
	GFC_SetCameraAngleRev( &angle, p_data->p_camera );
	GFC_SetCameraDistance( p_data->dist.data, p_data->p_camera );
	p_data->p_target->z = p_data->target_z.data;

	// カウント
	p_data->count ++;
	
	// 終了チェック
	if( check == TRUE ){
		TCB_Delete( tcb );
		p_data->tcb = NULL;
		p_data->end_flag = TRUE;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	カメラ動作終了チェック
 *	
 *	@param	p_camera_move 
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	実行中
 */
//-----------------------------------------------------------------------------
static BOOL EvCameraMoveEndCheck( EV_CAMERA_MOVE* p_camera_move )
{
	return p_camera_move->end_flag;
}


//----------------------------------------------------------------------------
/**
 *	@brief	OAMリソース読み込み
 *
 *	@param	p_psl	ワーク
 *	@param	heap	ヒープ
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void Cursor_oam_load( EV_POKESELECT_PROC_WORK* p_psl, EV_CURSOR_OBJ* p_data, int heap )
{
	
	// キャラクタデータ読み込み
	p_data->res_obj[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerResAddArcChar( 
			p_psl->res_manager[ CLACT_U_CHAR_RES ], ARC_EV_POKESELECT_GRA,
			NARC_ev_pokeselect_psel_cursol_NCGR, FALSE,
			NARC_ev_pokeselect_psel_cursol_NCGR,
			NNS_G2D_VRAM_TYPE_2DMAIN, heap );
	// 転送
	CLACT_U_CharManagerSetAreaCont( p_data->res_obj[ CLACT_U_CHAR_RES ] );
	// グラフィックデータだけ破棄
	CLACT_U_ResManagerResOnlyDelete( p_data->res_obj[ CLACT_U_CHAR_RES ] );

	// パレットデータ読み込み
	p_data->res_obj[ CLACT_U_PLTT_RES ] = CLACT_U_ResManagerResAddArcPltt( 
			p_psl->res_manager[ CLACT_U_PLTT_RES ], ARC_EV_POKESELECT_GRA,
			NARC_ev_pokeselect_psel_cursol_NCLR, FALSE, 
			NARC_ev_pokeselect_psel_cursol_NCLR, 
			NNS_G2D_VRAM_TYPE_2DMAIN, 
			1, heap );
	// 転送
	CLACT_U_PlttManagerSetCleanArea( p_data->res_obj[ CLACT_U_PLTT_RES ] );	
	// グラフィックデータだけ破棄
	CLACT_U_ResManagerResOnlyDelete( p_data->res_obj[ CLACT_U_PLTT_RES ] );


	// セルデータ読み込み
	p_data->res_obj[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerResAddArcKindCell(
			p_psl->res_manager[ CLACT_U_CELL_RES ], ARC_EV_POKESELECT_GRA,
			NARC_ev_pokeselect_psel_cursol_NCER, FALSE,
			NARC_ev_pokeselect_psel_cursol_NCER,
			CLACT_U_CELL_RES, heap );

	// セルアニメデータ読み込み
	p_data->res_obj[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerResAddArcKindCell(
			p_psl->res_manager[ CLACT_U_CELLANM_RES ], ARC_EV_POKESELECT_GRA, 
			NARC_ev_pokeselect_psel_cursol_NANR, FALSE,
			NARC_ev_pokeselect_psel_cursol_NANR,
			CLACT_U_CELLANM_RES, heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAMリソース破棄
 *
 *	@param	p_psl	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void Cursor_oam_delete( EV_POKESELECT_PROC_WORK* p_psl, EV_CURSOR_OBJ* p_data )
{
	CLACT_U_CharManagerDelete( p_data->res_obj[ CLACT_U_CHAR_RES ] );
	CLACT_U_PlttManagerDelete( p_data->res_obj[ CLACT_U_PLTT_RES ] );

	// リソース破棄
	CLACT_U_ResManagerResDelete( 
			p_psl->res_manager[ CLACT_U_CHAR_RES ],
			p_data->res_obj[ CLACT_U_CHAR_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_psl->res_manager[ CLACT_U_PLTT_RES ],
			p_data->res_obj[ CLACT_U_PLTT_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_psl->res_manager[ CLACT_U_CELL_RES ],
			p_data->res_obj[ CLACT_U_CELL_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_psl->res_manager[ CLACT_U_CELLANM_RES ],
			p_data->res_obj[ CLACT_U_CELLANM_RES ] );
}

//----------------------------------------------------------------------------
/**
 *	@brief	セルアクター登録
 *
 *	@param	p_psl	ワーク
 *	@param	heap	ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void Cursor_clact_add( EV_POKESELECT_PROC_WORK* p_psl, EV_CURSOR_OBJ* p_data, int heap )
{
	CLACT_HEADER		clact_head;
	CLACT_ADD_SIMPLE	add;
	
	// 各ボタンを登録
	// アクターヘッダー作成
	CLACT_U_MakeHeader( &clact_head,
			NARC_ev_pokeselect_psel_cursol_NCGR,
			NARC_ev_pokeselect_psel_cursol_NCLR,
			NARC_ev_pokeselect_psel_cursol_NCER,
			NARC_ev_pokeselect_psel_cursol_NANR,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE, 0, CLACT_BG_PRI,
			p_psl->res_manager[ CLACT_U_CHAR_RES ],
			p_psl->res_manager[ CLACT_U_PLTT_RES ],
			p_psl->res_manager[ CLACT_U_CELL_RES ],
			p_psl->res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );

	add.ClActSet	= p_psl->clact_set;
	add.ClActHeader = &clact_head;
	add.pri			= 32;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DMAIN;
	add.heap		= heap;

	// カーソル登録
	add.mat.x = 0;
	add.mat.y = 0;
	p_data->cursor = CLACT_AddSimple( &add );
	CLACT_SetDrawFlag( p_data->cursor, FALSE );

	p_data->mat.x = 0;
	p_data->mat.y = 0;
}

//----------------------------------------------------------------------------
/**
 *	@brief	セルアクター破棄
 *
 *	@param	p_data	カーソルオブジェ	
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void Cursor_clact_delete( EV_CURSOR_OBJ* p_data )
{
	CLACT_Delete( p_data->cursor );
}

//----------------------------------------------------------------------------
/**
 *	@brief	回転動作ワーク初期化
 *
 *	@param	p_data	ﾃﾞｰﾀ格納先
 *	@param	r		半径の大きさ
 *	@param	count	ｶｳﾝﾀ最大値
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void EvRotaMoveInit( EV_ROTA_MOVE_ONE* p_data, fx32 r, int count )
{
	p_data->num			= 0;
	p_data->r			= r;
	p_data->count_max	= count;
	p_data->count		= 0;
}

//----------------------------------------------------------------------------
/**
 *	@brief	回転動作メイン
 *
 *	@param	p_data	ワーク
 */
//-----------------------------------------------------------------------------
static void EvRotaMoveMain( EV_ROTA_MOVE_ONE* p_data )
{
	u16 rota;
	int calc;

	// 現在回転角を求める
	calc = FX_GET_ROTA_NUM( 360 ) * p_data->count;
	calc = calc / p_data->count_max;
	rota = calc;

	// 現在動作位置
	p_data->num = FX_Mul( FX_SinIdx( rota ), p_data->r );


	// カウント処理
	p_data->count = (p_data->count + 1) % p_data->count_max;
}

//----------------------------------------------------------------------------
/**
 *	@brief	カーソル動作開始
 *
 *	@param	p_cursor	カーソルオブジェクト
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void EvCursorMoveReq( EV_CURSOR_OBJ* p_cursor )
{
	// 初期化ずみチェック
	GF_ASSERT( p_cursor->tcb == NULL );
	
	EvRotaMoveInit( &p_cursor->move_param, CURSOR_MOVE_Y, CURSOR_MOVE_COUNT );
	
	p_cursor->tcb = TCB_Add( EvCursorMoveTcb, p_cursor, 0 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	カーソルタスク
 *
 *	@param	tcb
 *	@param	work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void EvCursorMoveTcb( TCB_PTR tcb, void* work )
{
	EV_CURSOR_OBJ* p_cursor = work;
	VecFx32 set_mat;
	
	EvRotaMoveMain( &p_cursor->move_param );

	// 座標設定
	set_mat = p_cursor->mat;
	set_mat.y += p_cursor->move_param.num;
	CLACT_SetMatrix( p_cursor->cursor, &set_mat );
}

//----------------------------------------------------------------------------
/**
 *	@brief	カーソル動作破棄
 *
 *	@param	p_cursor 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void EvCursorMoveDelete( EV_CURSOR_OBJ* p_cursor )
{
	if(p_cursor->tcb){
		TCB_Delete( p_cursor->tcb );
		p_cursor->tcb = NULL;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	表示ONOFF
 *
 *	@param	p_data
 *	@param	flag 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void Cursor_clact_set_draw_flag( EV_CURSOR_OBJ* p_data, BOOL flag )
{
	CLACT_SetDrawFlag( p_data->cursor, flag );
}

static void Cursor_clact_set_matrix( EV_CURSOR_OBJ* p_data, int x, int y )
{
	p_data->mat.x = x << FX32_SHIFT;
	p_data->mat.y = y << FX32_SHIFT;
}

//----------------------------------------------------------------------------
/**
 *	@brief	円形ウィンドウぐらふぃっく初期化
 *
 *	@param	p_data		ﾃﾞｰﾀ格納先
 *	@param	p_psl		ﾃﾞｰﾀワーク
 *	@param	heap		ヒープ
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void CircleWnd_Gra_Init( EV_CIRCLE_WND* p_data, EV_POKESELECT_PROC_WORK* p_psl, int heap )
{
	SWSP_CHARDATA char_ent;
	SWSP_PLTTDATA pltt_ent;
	SWSP_ADDDATA add;
	
	// キャラクタデータ
	p_data->swsp_char_buff = ArcUtil_CharDataGet( 
			ARC_EV_POKESELECT_GRA, NARC_ev_pokeselect_psel_circle_NCBR, FALSE,
			&p_data->p_chardata, heap );
	
	// パレットデータ読み込み
	p_data->swsp_pltt_buff = ArcUtil_PalDataGet( 
			ARC_EV_POKESELECT_GRA, NARC_ev_pokeselect_psel_circle_NCLR,
			&p_data->p_plttdata, heap );

	// キャラクタデータ転送
	char_ent.s_sys		= p_psl->swsp_sys;
	char_ent.res_file	= p_data->p_chardata;
	p_data->swsp_char = SWSP_CharLoad( &char_ent );

	// パレットデータ転送
	pltt_ent.s_sys		= p_psl->swsp_sys;
	pltt_ent.res_file	= p_data->p_plttdata;
	pltt_ent.load_num	= 1;
	p_data->swsp_pltt = SWSP_PlttLoad( &pltt_ent );


	//-------------------------------------
	//	登録
	//=====================================
	add.s_sys	= p_psl->swsp_sys;
	add.p_char	= p_data->swsp_char;
	add.p_pltt	= p_data->swsp_pltt;

	// 登録データ格納
	add.m_x = 0;
	add.m_y = 0;
	add.rota = 0;
	add.alpha = 31;
	add.pri = 1022;
	add.pltt_offs = 0; 

	// 登録
	p_data->swsp_obj = SWSP_Add( &add );

	// 取り合えず非表示
	SWSP_SetSpriteDraw( p_data->swsp_obj, FALSE );

	// 中心座標
	SWSP_SetSpriteCenterPos( p_data->swsp_obj, QUESTION_CIRCLE_SIZE / 2, QUESTION_CIRCLE_SIZE / 2 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	CIRCLEグラフィックﾃﾞｰﾀ破棄
 *
 *	@param	p_data
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void CircleWnd_Gra_Delete( EV_CIRCLE_WND* p_data )
{
	// オブジェクト破棄
	SWSP_Delete( p_data->swsp_obj );
	
	// Vramから破棄
	SWSP_CharDelete( p_data->swsp_char );
	SWSP_PlttDelete( p_data->swsp_pltt );
	// メモリから破棄
	sys_FreeMemoryEz( p_data->swsp_char_buff );
	sys_FreeMemoryEz( p_data->swsp_pltt_buff );
}

//----------------------------------------------------------------------------
/**
 *	@brief	サークル　描画ONOFF
 *
 *	@param	p_data 
 *	@param	flag
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void CircleWnd_Gra_Draw( EV_CIRCLE_WND* p_data, BOOL flag )
{
	SWSP_SetSpriteDraw( p_data->swsp_obj, flag );
}

//----------------------------------------------------------------------------
/**
 *	@brief	サークルウィンドウ動作リクエスト
 *
 *	@param	p_data 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void CircleWnd_Move_Req( EV_CIRCLE_WND* p_data, fx32 s_x, fx32 e_x, fx32 s_y, fx32 e_y, fx32 s_s, fx32 e_s, int sync )
{
	// 初期ずみチェック
	GF_ASSERT( p_data->tcb == NULL );
	
	// X座標動作
	EvMoveInit( &p_data->param.x, s_x, e_x, sync );

	// Y座標動作
	EvMoveInit( &p_data->param.y, s_y, e_y, sync );

	// scale座標動作
	EvMoveInit( &p_data->param.scale, s_s, e_s, sync );

	// ｶｳﾝﾀ初期化
	p_data->param.count = 0;
	p_data->param.count_add = 1;

	p_data->tcb = TCB_Add( CircleWnd_Move_Tcb, p_data, 0 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	パラメータを取っておいて、逆再生させる
 *
 *	@param	p_data		ﾃﾞｰﾀ
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void CircleWnd_ReMove_Req( EV_CIRCLE_WND* p_data )
{
	// 初期ずみチェック
	GF_ASSERT( p_data->tcb == NULL );

	// ｶｳﾝﾀ初期化
	p_data->param.count_add = QUESTION_CIRCLE_RET_ADD;
	

	// すぐおわっちゃうの回避
	if( p_data->param.count >= p_data->param.x.count_max  ){
		p_data->param.count = p_data->param.x.count_max + p_data->param.count_add;
	}

	p_data->tcb = TCB_Add( CircleWnd_Move_Tcb, p_data, 0 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	サークルウィンドウ動作タスク
 *
 *	@param	tcb
 *	@param	work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void CircleWnd_Move_Tcb( TCB_PTR tcb, void* work )
{
	EV_CIRCLE_WND* p_data = work;
	BOOL check;
	fx32 x, y;

	// 動作させる
	check = EvMoveMain( &p_data->param.x, p_data->param.count );
	EvMoveMain( &p_data->param.y, p_data->param.count );
	EvMoveMain( &p_data->param.scale, p_data->param.count );

	// 左上座標にして値を設定
	x = p_data->param.x.data - ((QUESTION_CIRCLE_SIZE/2)*FX32_ONE);	
	y = p_data->param.y.data - ((QUESTION_CIRCLE_SIZE/2)*FX32_ONE);	
	SWSP_SetSpritePos( p_data->swsp_obj, 
			x >> FX32_SHIFT, y >> FX32_SHIFT );

	// 拡縮値
	SWSP_SetSpriteScale( p_data->swsp_obj, p_data->param.scale.data, p_data->param.scale.data );

	if( (check == TRUE) || (p_data->param.count < 0) ){
		// 終了
		TCB_Delete( tcb );
		p_data->tcb = NULL;
	}

	// カウント処理
	p_data->param.count += p_data->param.count_add;

}

//----------------------------------------------------------------------------
/**
 *	@brief	サークルウィンドウ動作終了チェック
 *
 *	@param	p_data 
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
static BOOL CircleWnd_Move_EndCheck( EV_CIRCLE_WND* p_data )
{
	if( p_data->tcb ){
		return  FALSE;
	}

	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	確認画面フェードリクエスト
 *
 *	@param	p_psl 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void QuestionFade_Req( EV_POKESELECT_PROC_WORK* p_psl )
{
	fx32 s_x, s_y;

	// 開始位置を求める
	s_x = p_psl->select_2_matrix[ p_psl->now_select_no ][ 0 ] << FX32_SHIFT;
	s_y = (p_psl->select_2_matrix[ p_psl->now_select_no ][ 1 ] + QUESTION_CIRCLE_Y_OFS) << FX32_SHIFT;
	CircleWnd_Move_Req( &p_psl->circle_wnd, 
			s_x, EV_POKESELECT_POKEGRA_X << FX32_SHIFT,
			s_y, EV_POKESELECT_POKEGRA_Y << FX32_SHIFT,
			QUESTION_FADE_SCALE_S, QUESTION_FADE_SCALE_E,
			QUESTION_FADE_SYNC );

	// ﾎﾟｹｸﾞﾗ
	PokeGra_Move_Req( &p_psl->soft_sprite_anm, 
			p_psl->soft_sprite[ p_psl->now_select_no ],
			s_x, EV_POKESELECT_POKEGRA_X << FX32_SHIFT,
			s_y, EV_POKESELECT_POKEGRA_Y << FX32_SHIFT,
			QUESTION_FADE_SCALE_S, QUESTION_FADE_SCALE_E,
			QUESTION_FADE_SYNC );

}

//----------------------------------------------------------------------------
/**
 *	@brief	確認画面から戻るフェードリクエスト
 *
 *	@param	p_psl 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void QuestionReFade_Req( EV_POKESELECT_PROC_WORK* p_psl )
{
	CircleWnd_ReMove_Req( &p_psl->circle_wnd );
	PokeGra_ReMove_Req( &p_psl->soft_sprite_anm );
}

//----------------------------------------------------------------------------
/**
 *	@brief	フェード終了待ち
 *
 *	@param	p_psl 
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
static BOOL QuestionFade_EndCheck( EV_POKESELECT_PROC_WORK* p_psl )
{
	return CircleWnd_Move_EndCheck( &p_psl->circle_wnd );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモングラフィック動作
 *
 *	@param	p_data
 *	@param	p_soft_sprit
 *	@param	s_x
 *	@param	e_x
 *	@param	s_y
 *	@param	e_y
 *	@param	s_s
 *	@param	e_s
 *	@param	sync 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void PokeGra_Move_Req( EV_POKEOBJ_ANM* p_data, SOFT_SPRITE* p_soft_sprit, fx32 s_x, fx32 e_x, fx32 s_y, fx32 e_y, fx32 s_s, fx32 e_s, int sync )
{
	// 初期ずみチェック
	GF_ASSERT( p_data->tcb == NULL );
	
	// X座標動作
	EvMoveInit( &p_data->param.x, s_x, e_x, sync );

	// Y座標動作
	EvMoveInit( &p_data->param.y, s_y, e_y, sync );

	// scale座標動作
	EvMoveInit( &p_data->param.scale, s_s, e_s, sync );

	// スプライトワーク
	p_data->p_soft_sprite = p_soft_sprit;

	// ｶｳﾝﾀ初期化
	p_data->param.count = 0;
	p_data->param.count_add = 1;

	p_data->tcb = TCB_Add( PokeGra_Move_Tcb, p_data, 0 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモングラフィック逆再生
 *
 *	@param	p_data 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void PokeGra_ReMove_Req( EV_POKEOBJ_ANM* p_data )
{
	// 初期ずみチェック
	GF_ASSERT( p_data->tcb == NULL );

	// ｶｳﾝﾀ初期化
	p_data->param.count_add = QUESTION_CIRCLE_RET_ADD;
	

	// すぐおわっちゃうの回避
	if( p_data->param.count >= p_data->param.x.count_max  ){
		p_data->param.count = p_data->param.x.count_max + p_data->param.count_add;
	}

	p_data->tcb = TCB_Add( PokeGra_Move_Tcb, p_data, 0 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモングラフィックに反映
 *
 *	@param	tcb
 *	@param	work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void PokeGra_Move_Tcb( TCB_PTR tcb, void* work )
{
	EV_POKEOBJ_ANM* p_data = work;
	BOOL check;
	u32 scale_num;

	// 動作させる
	check = EvMoveMain( &p_data->param.x, p_data->param.count );
	EvMoveMain( &p_data->param.y, p_data->param.count );
	EvMoveMain( &p_data->param.scale, p_data->param.count );

	// 0x100が1の拡大縮小にする
	scale_num = FX_Mul( 0x100*FX32_ONE, p_data->param.scale.data ) >> FX32_SHIFT;

	SoftSpriteParaSet( p_data->p_soft_sprite, SS_PARA_POS_X, p_data->param.x.data >> FX32_SHIFT );
	SoftSpriteParaSet( p_data->p_soft_sprite, SS_PARA_POS_Y, p_data->param.y.data >> FX32_SHIFT );
	SoftSpriteParaSet( p_data->p_soft_sprite, SS_PARA_AFF_X, scale_num );
	SoftSpriteParaSet( p_data->p_soft_sprite, SS_PARA_AFF_Y, scale_num );

	if( (check == TRUE) || (p_data->param.count < 0) ){
		// 終了
		TCB_Delete( tcb );
		p_data->tcb = NULL;
	}

	// カウント処理
	p_data->param.count += p_data->param.count_add;
}

//----------------------------------------------------------------------------
/**
 *	@brief	終了チェック
 *
 *	@param	p_data 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static BOOL PokeGra_Move_EndCheck( EV_POKEOBJ_ANM* p_data )
{
	if( p_data->tcb ){
		return  FALSE;
	}

	return TRUE;
}


//----------------------------------------------------------------------------
/**
 *	@brief	サブ面ビットマップウィンドウ作成
 *
 *	@param	p_psl	ワーク
 *	@param	heap	ヒープ
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void FontSubbg_bmpwin_make( EV_POKESELECT_PROC_WORK* p_psl, int heap )
{
	int i;
	int x, y;

	// パレット転送
	ArcUtil_PalSet( ARC_EV_POKESELECT_GRA, NARC_ev_pokeselect_font_system_NCLR, PALTYPE_MAIN_BG, BG_FONTSUB_COLOR * 32, 32, heap );
	
	for( i=0; i<EV_POKESELECT_MONSNUM; i++ ){
		p_psl->p_bmp_subfont[i] = GF_BGL_BmpWinAllocGet( heap, 1 );
		GF_BGL_BmpWinInit( p_psl->p_bmp_subfont[i] );

		switch( i ){
		case POKESELECT_LEFT_BALL:
			x = BG_FONTSUBBMP_0X;
			y = BG_FONTSUBBMP_0Y;
			break;
		case POKESELECT_CENTER_BALL:
			x = BG_FONTSUBBMP_1X;
			y = BG_FONTSUBBMP_1Y;
			break;
		case POKESELECT_RIGHT_BALL:
			x = BG_FONTSUBBMP_2X;
			y = BG_FONTSUBBMP_2Y;
			break;
		}
	
		// ビットマップウィンドウ登録
		GF_BGL_BmpWinAdd( p_psl->p_bg, p_psl->p_bmp_subfont[i],
				GF_BGL_FRAME3_M, x, y, BG_FONTSUBBMP_CX, BG_FONTSUBBMP_CY, BG_FONTSUB_COLOR, 1 + (BG_FONTSUB_CGX_OFS * i) );

		// 文字列描画
		FontSubbg_bmpwin_str( p_psl->p_bmp_subfont[i], heap, NARC_msg_ev_pokeselect_dat, EV_POKESELECT_05 + i, BG_FONTSUBBMP_PRICOLOR );
	}

}
//----------------------------------------------------------------------------
/**
 *	@brief	ビットマップウィンドウ破棄
 *
 *	@param	p_psl 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void FontSubbg_bmpwin_delete( EV_POKESELECT_PROC_WORK* p_psl )
{
	int i;

	for( i=0; i<EV_POKESELECT_MONSNUM; i++ ){
		GF_BGL_BmpWinDel( p_psl->p_bmp_subfont[i] );
		sys_FreeMemoryEz( p_psl->p_bmp_subfont[i] );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	文字列描画
 *
 *	@param	p_bmp
 *	@param	heap
 *	@param	arcidx
 *	@param	msgidx
 *	@param	color 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void FontSubbg_bmpwin_str( GF_BGL_BMPWIN* p_bmp, int heap, int arcidx, int msgidx, GF_PRINTCOLOR color )
{
	MSGDATA_MANAGER* msg_data;
	STRBUF* str;

	// 文字列取得
	msg_data = MSGMAN_Create( MSGMAN_TYPE_NORMAL, ARC_MSG, arcidx, heap );
	GF_ASSERT( msg_data );
	str = MSGMAN_AllocString( msg_data, msgidx );

	// ビットマップ初期化
	GF_BGL_BmpWinDataFill( p_bmp, GF_PRINTCOLOR_GET_GROUND( color ) );

	// 文字列書き込み
	GF_STR_PrintColor( p_bmp, FONT_SYSTEM, str, 1, 0, MSG_NO_PUT, color, NULL );
												// ↑描画位
	STRBUF_Delete( str );

	MSGMAN_Delete( msg_data );
}

//----------------------------------------------------------------------------
/**
 *	@brief	選択されているメッセージを出す
 *
 *	@param	p_psl ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FontSubbg_bmpwin_select( EV_POKESELECT_PROC_WORK* p_psl )
{
	// 今までのものをクリア
	GF_BGL_BmpWinOff( p_psl->p_bmp_subfont[ p_psl->local_select_no ] );

	// 次のをON
	GF_BGL_BmpWinOn( p_psl->p_bmp_subfont[ p_psl->now_select_no ] );
	p_psl->local_select_no = p_psl->now_select_no;
}

//----------------------------------------------------------------------------
/**
 *	@brief	完全に消す
 *
 *	@param	p_psl 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void FontSubbg_bmpwin_clean( EV_POKESELECT_PROC_WORK* p_psl )
{
	GF_BGL_BmpWinOff( p_psl->p_bmp_subfont[ p_psl->local_select_no ] );
}

//----------------------------------------------------------------------------
/**
 *	@brief	選択ナンバーから選択したポケモンナンバーを取得
 *
 *	@param	no	選択ナンバー
 *
 *	@return	モンスターナンバー
 */
//-----------------------------------------------------------------------------
static u16 EV_PokeSelect_SelectNoMonsnoGet( u16 no )
{
	// 親に選択したポケモンﾅﾝﾊﾞｰを設定する
	switch( no ){
	case POKESELECT_LEFT_BALL:
		return MONSNO_NAETORU;
	case POKESELECT_CENTER_BALL:
		return MONSNO_HIKOZARU;
	case POKESELECT_RIGHT_BALL:
		return MONSNO_POTTYAMA;
	default:
		GF_ASSERT(0);
		break;
	}
	return 0;
}
