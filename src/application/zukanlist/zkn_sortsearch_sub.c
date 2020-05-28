//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_sortsearch_sub.c
 *	@brief		検索ソートサブ画面サブ画面		共通部分
 *	@author		tomoya takahashi 
 *	@data		2006.01.21
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include <string.h>
#include "include/application/zukanlist/zkn_event_func.h"

#include "include/system/brightness.h"
#include "include/system/arc_tool.dat"
#include "include/system/arc_util.h"
#include "include/system/clact_util.h"
#include "include/application/zukanlist/zukan.naix"
#include "include/gflib/button_man.h"
#include "include/gflib/calctool.h"
#include "include/system/msgdata_util.h"
#include "include/msgdata/msg.naix"
#include "include/msgdata/msg_zkn.h"
#include "include/application/zukanlist/zkn_snd_def.h"

#include "include/application/zukanlist/zukan.naix"
#include "include/application/zukanlist/zkn_sortsearch.h"

#define	__ZKN_SORTSEARCHSUB_SUB_H_GLOBAL
#include "include/application/zukanlist/zkn_sortsearch_sub.h"

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
 *					定数宣言
*/
//-----------------------------------------------------------------------------
#define ZKN_SORTSEARCHSUB_EVENT_NUM ( 0 )	// イベント数


//-------------------------------------
//	シーケンス
//=====================================
enum{
	ZKN_SORTSEARCHSUB_SEQINIT_ALLOC,
	ZKN_SORTSEARCHSUB_SEQINIT_LOAD,
	ZKN_SORTSEARCHSUB_SEQINIT_FADEIN,
	ZKN_SORTSEARCHSUB_SEQINIT_END,
};
enum{
	ZKN_SORTSEARCHSUB_SEQDELETE_FADEOUT_INIT,
	ZKN_SORTSEARCHSUB_SEQDELETE_FADEOUT,
	ZKN_SORTSEARCHSUB_SEQDELETE_RELEASE,
	ZKN_SORTSEARCHSUB_SEQDELETE_FREE,
	ZKN_SORTSEARCHSUB_SEQDELETE_END,
};


//アニメシーケンス
enum{
	ZKN_SORTSEARCHSUB_MAIN_BUTTON,
	ZKN_SORTSEARCHSUB_ACTION_BUTTON,
	ZKN_SORTSEARCHSUB_SELECT_BUTTON,
	ZKN_SORTSEARCHSUB_RET_BUTTON,
	ZKN_SORTSEARCHSUB_PAGE_SUB_BUTTON,
	ZKN_SORTSEARCHSUB_PAGE_ADD_BUTTON,
	ZKN_SORTSEARCHSUB_FORM_BUTTON,
};
enum{
	// FORM
	ZKN_SORTSEARCHSUB_CIRCLE_BUTTON,
	ZKN_SORTSEARCHSUB_ARM_BUTTON,
	ZKN_SORTSEARCHSUB_LEGS_BUTTON,
	ZKN_SORTSEARCHSUB_MANY_LEGS_BUTTON,
	ZKN_SORTSEARCHSUB_FOURWING_BUTTON,
	ZKN_SORTSEARCHSUB_HARABAI_BUTTON,
	ZKN_SORTSEARCHSUB_STRAIGHT_BUTTON,
	ZKN_SORTSEARCHSUB_HAITSUKUBARI_BUTTON,
	ZKN_SORTSEARCHSUB_COMP_BUTTON,
	ZKN_SORTSEARCHSUB_FOURLEGS_BUTTON,
	ZKN_SORTSEARCHSUB_WATER_BUTTON,
	ZKN_SORTSEARCHSUB_TAIL_BUTTON,
	ZKN_SORTSEARCHSUB_TWO_WING_BUTTON,
	ZKN_SORTSEARCHSUB_TWO_LEGS_BUTTON,
	ZKN_SORTSEARCHSUB_FORM_NONE,
};

// 処理フラグの初期化数
#define ZKN_SORTSEARCHSUB_DO_FLAG_INIT ( 0xffff )

//-----------------------------------------------------------------------------
/**
 *		ボタンカーソルﾃﾞｰﾀ共通部分
 */
//-----------------------------------------------------------------------------
// 共通以外のボタンの最大数
#define ZKN_SORTSEARCHSUB_BUTTON_SUB_MAX	( 15 )


// 縦軸の数
#define ZKN_SORTSEARCHSUB_BUTTON_Y_NUM		( 6 )


// Y座標位置
#define ZKN_SORTSEARCHSUB_BUTTON_00_Y		( 16 )	
#define ZKN_SORTSEARCHSUB_BUTTON_01_Y		( 48 )	
#define ZKN_SORTSEARCHSUB_BUTTON_02_Y		( 80 )
#define ZKN_SORTSEARCHSUB_BUTTON_03_Y		( 112 )	
#define ZKN_SORTSEARCHSUB_BUTTON_04_Y		( 144 )
#define ZKN_SORTSEARCHSUB_BUTTON_05_Y		( 176 )

// ならび　なまえ　たいぷ共通X座標
#define ZKN_SORTSEARCHSUB_BUTTONDEF_00_X	( 48 )
#define ZKN_SORTSEARCHSUB_BUTTONDEF_01_X	( 128 )


// ふぉんとOAMの文字数別OFSET
#define ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_2_X		( -12 )
#define ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_3_X		( -18 )
#define ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_4_X		( -24 )
#define ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_5_X		( -30 )
#define ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_6_X		( -36 )
#define ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_Y		( -6 )
#define ZKN_SORTSEARCHSUB_BUTTONFONT_PLTOFS	( 3 )
#define ZKN_SORTSEARCHSUB_BUTTONFONT_KETTEI_PLTOFS	( 1 )
#define ZKN_SORTSEARCHSUB_BUTTONFONT_PUSHPLTOFS	( 5 )
#define ZKN_SORTSEARCHSUB_BUTTONFONT_OTHER_PLTOFS	( 0xB )
#define ZKN_SORTSEARCHSUB_BUTTONFONT_OTHER_PUSHPLTOFS	( 6 )

// カーソルY軸数
#define ZKN_SORTSEARCHSUB_CURSOR_MAX_Y	( ZKN_SORTSEARCHSUB_BUTTON_Y_NUM )

// 実行と基本ボタンのサイズ
#define ZKN_SORTSEARCHSUB_BUTTON_ACTION_SIZX	( 80 )
#define ZKN_SORTSEARCHSUB_BUTTON_ACTION_SIZY	( 32 )
#define ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZX	( 60 )
#define ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZY	( 16 )

// ﾀｲﾌﾟ1とﾀｲﾌﾟ2のページ切り替えボタンサイズ
#define ZKN_SORTSEARCHSUB_BUTTON_PAGE_SIZX	( 32 )
#define ZKN_SORTSEARCHSUB_BUTTON_PAGE_SIZY	( 32 )
#define ZKN_SORTSEARCHSUB_CURSOR_PAGE_SIZX	( 16 )
#define ZKN_SORTSEARCHSUB_CURSOR_PAGE_SIZY	( 16 )


//-------------------------------------
//	カーソル制御ID	カーソルIDはかぶらないようにする
//=====================================
enum{
	ZKN_SORTSEARCHSUB_CURSOR_ID_BACK,
	ZKN_SORTSEARCHSUB_CURSOR_ID_NARABI,
	ZKN_SORTSEARCHSUB_CURSOR_ID_NAME,
	ZKN_SORTSEARCHSUB_CURSOR_ID_TYPE,
	ZKN_SORTSEARCHSUB_CURSOR_ID_FORM,
	ZKN_SORTSEARCHSUB_CURSOR_ID_ACTION,
	ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_00,
	ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_01,
	ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_02,
	ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_03,
	ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_04,
	ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_05,
	ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_06,
	ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_07,
	ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_08,
	ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_09,
	ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_10,
	ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_11,
	ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_12,
	ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_13,
	ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_14,
	ZKN_SORTSEARCHSUB_SURSOR_ID_NUM,
};

// カーソルの無いところに入れるID
#define ZKN_SORTSEARCHSUB_CURSOR_ID_NONE	( 0xff )

//-----------------------------------------------------------------------------
/**
 *		共通部分ボタンカーソルﾃﾞｰﾀ
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	サブコモンボタン数
//=====================================
enum{
	ZKN_SORTSEARCHSUB_BUTTON_BACK,
	ZKN_SORTSEARCHSUB_BUTTON_NARABI,
	ZKN_SORTSEARCHSUB_BUTTON_NAME,
	ZKN_SORTSEARCHSUB_BUTTON_TYPE,
	ZKN_SORTSEARCHSUB_BUTTON_FORM,
	ZKN_SORTSEARCHSUB_BUTTON_ACTION,
	ZKN_SORTSEARCHSUB_BUTTON_NUM,
};
#define ZKN_SORTSEARCHSUB_BUTTON_SIZX		( 64 )
#define ZKN_SORTSEARCHSUB_BUTTON_SIZY		( 32 )
#define ZKN_SORTSEARCHSUB_BUTTON_BACK_SIZX		( 48 )
#define ZKN_SORTSEARCHSUB_BUTTON_BACK_SIZY		( 32 )
#define ZKN_SORTSEARCHSUB_BUTTON_X			( 224 )
#define ZKN_SORTSEARCHSUB_BUTTON_ACTION_X	( 212 )
#define ZKN_SORTSEARCHSUB_BUTTON_BACK_X		( 212 )
#define ZKN_SORTSEARCHSUB_BUTTON_BACK_Y		( ZKN_SORTSEARCHSUB_BUTTON_00_Y )	
#define ZKN_SORTSEARCHSUB_BUTTON_NARABI_Y	( ZKN_SORTSEARCHSUB_BUTTON_01_Y )	
#define ZKN_SORTSEARCHSUB_BUTTON_NAME_Y		( ZKN_SORTSEARCHSUB_BUTTON_02_Y )
#define ZKN_SORTSEARCHSUB_BUTTON_TYPE_Y		( ZKN_SORTSEARCHSUB_BUTTON_03_Y )	
#define ZKN_SORTSEARCHSUB_BUTTON_FORM_Y		( ZKN_SORTSEARCHSUB_BUTTON_04_Y )
#define ZKN_SORTSEARCHSUB_BUTTON_ACTION_Y	(ZKN_SORTSEARCHSUB_BUTTON_05_Y  )

// FONTOAM
#define ZKN_SORTSEARCHSUB_BUTTONFONT_BMP_SIZE_CX	( 8 )
#define ZKN_SORTSEARCHSUB_BUTTONFONT_BMP_SIZE_CY	( 2 )

// カーソル
#define ZKN_SORTSEARCHSUB_CURSOR_SIZX		( 44 )
#define ZKN_SORTSEARCHSUB_CURSOR_SIZY		( 16 )
#define ZKN_SORTSEARCHSUB_CURSOR_BACK_SIZX	( 28 )
#define ZKN_SORTSEARCHSUB_CURSOR_BACK_SIZY	( 16 )



//-----------------------------------------------------------------------------
/**
 *		ならび画面ボタン配置ﾃﾞｰﾀ
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	サブボタン数
//=====================================
enum{
	ZKN_SORTSEARCHSUB_BUTTON_NARABI_NUMBER,
	ZKN_SORTSEARCHSUB_BUTTON_NARABI_AIUEO,
	ZKN_SORTSEARCHSUB_BUTTON_NARABI_HEAVY,
	ZKN_SORTSEARCHSUB_BUTTON_NARABI_LIGHT,
	ZKN_SORTSEARCHSUB_BUTTON_NARABI_TALL,
	ZKN_SORTSEARCHSUB_BUTTON_NARABI_SHORT,
	ZKN_SORTSEARCHSUB_BUTTON_NARABI_NUM,
};

// FONTOAM
#define ZKN_SORTSEARCHSUB_BUTTONFONT_BMP_NARABI_SIZE_CX	( 10 )
#define ZKN_SORTSEARCHSUB_BUTTONFONT_BMP_NARABI_SIZE_CY	( 2 )

// カーソル
#define ZKN_SORTSEARCHSUB_CURSOR_NARABI_MAX_X	( 3 )

//-----------------------------------------------------------------------------
/**
 *		なまえ画面ボタン配置ﾃﾞｰﾀ
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	サブボタン数
//=====================================
enum{
	ZKN_SORTSEARCHSUB_BUTTON_NAME_A,
	ZKN_SORTSEARCHSUB_BUTTON_NAME_HA,
	ZKN_SORTSEARCHSUB_BUTTON_NAME_KA,
	ZKN_SORTSEARCHSUB_BUTTON_NAME_MA,
	ZKN_SORTSEARCHSUB_BUTTON_NAME_SA,
	ZKN_SORTSEARCHSUB_BUTTON_NAME_RA,
	ZKN_SORTSEARCHSUB_BUTTON_NAME_TA,
	ZKN_SORTSEARCHSUB_BUTTON_NAME_YAWA,
	ZKN_SORTSEARCHSUB_BUTTON_NAME_NA,
	ZKN_SORTSEARCHSUB_BUTTON_NAME_NONE,
	ZKN_SORTSEARCHSUB_BUTTON_NAME_NUM,
};

// FONTOAM
#define ZKN_SORTSEARCHSUB_BUTTONFONT_BMP_NAME_SIZE_CX	( 10 )
#define ZKN_SORTSEARCHSUB_BUTTONFONT_BMP_NAME_SIZE_CY	( 2 )

// カーソル
#define ZKN_SORTSEARCHSUB_CURSOR_NAME_MAX_X	( 3 )


//-----------------------------------------------------------------------------
/**
 *		ﾀｲﾌﾟ1画面ボタン配置ﾃﾞｰﾀ
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	サブボタン数
//=====================================
enum{
	ZKN_SORTSEARCHSUB_BUTTON_TYPE1_AKU,
	ZKN_SORTSEARCHSUB_BUTTON_TYPE1_KOORI,
	ZKN_SORTSEARCHSUB_BUTTON_TYPE1_IWA,
	ZKN_SORTSEARCHSUB_BUTTON_TYPE1_GHOST,
	ZKN_SORTSEARCHSUB_BUTTON_TYPE1_SP,
	ZKN_SORTSEARCHSUB_BUTTON_TYPE1_JIMEN,
	ZKN_SORTSEARCHSUB_BUTTON_TYPE1_BATTLE,
	ZKN_SORTSEARCHSUB_BUTTON_TYPE1_ELEC,
	ZKN_SORTSEARCHSUB_BUTTON_TYPE1_KUSA,
	ZKN_SORTSEARCHSUB_BUTTON_TYPE1_NONE,
	ZKN_SORTSEARCHSUB_BUTTON_TYPE1_TYPE2,
	ZKN_SORTSEARCHSUB_BUTTON_TYPE1_NUM,
};

// FONTOAM
#define ZKN_SORTSEARCHSUB_BUTTONFONT_BMP_TYPE1_SIZE_CX	( 10 )
#define ZKN_SORTSEARCHSUB_BUTTONFONT_BMP_TYPE1_SIZE_CY	( 2 )

// 次へのボタン位置
#define ZKN_SORTSEARCHSUB_BUTTON_TYPE1_TYPE2_X	( ZKN_SORTSEARCHSUB_BUTTONDEF_00_X - 24 )

// カーソル
#define ZKN_SORTSEARCHSUB_CURSOR_TYPE1_MAX_X	( 3 )

//-----------------------------------------------------------------------------
/**
 *		ﾀｲﾌﾟ2画面ボタン配置ﾃﾞｰﾀ
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	サブボタン数
//=====================================
enum{
	ZKN_SORTSEARCHSUB_BUTTON_TYPE2_DOKU,
	ZKN_SORTSEARCHSUB_BUTTON_TYPE2_HIKOR,
	ZKN_SORTSEARCHSUB_BUTTON_TYPE2_DRAGON,
	ZKN_SORTSEARCHSUB_BUTTON_TYPE2_FIRE,
	ZKN_SORTSEARCHSUB_BUTTON_TYPE2_NORMAL,
	ZKN_SORTSEARCHSUB_BUTTON_TYPE2_WATER,
	ZKN_SORTSEARCHSUB_BUTTON_TYPE2_HAGANE,
	ZKN_SORTSEARCHSUB_BUTTON_TYPE2_MUSHI,
	ZKN_SORTSEARCHSUB_BUTTON_TYPE2_NONE,
	ZKN_SORTSEARCHSUB_BUTTON_TYPE2_TYPE1,
	ZKN_SORTSEARCHSUB_BUTTON_TYPE2_NUM,
};
// FONTOAM
#define ZKN_SORTSEARCHSUB_BUTTONFONT_BMP_TYPE2_SIZE_CX	( 10 )
#define ZKN_SORTSEARCHSUB_BUTTONFONT_BMP_TYPE2_SIZE_CY	( 2 )

// 次へのボタン位置
#define ZKN_SORTSEARCHSUB_BUTTON_TYPE2_TYPE1_X	( ZKN_SORTSEARCHSUB_BUTTONDEF_00_X - 24 )

// カーソル
#define ZKN_SORTSEARCHSUB_CURSOR_TYPE2_MAX_X	( 3 )


//-----------------------------------------------------------------------------
/**
 *		形画面ボタン配置ﾃﾞｰﾀ
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	サブボタン数
//=====================================
enum{
	ZKN_SORTSEARCHSUB_BUTTON_FORM_CIRCLE,
	ZKN_SORTSEARCHSUB_BUTTON_FORM_HARABAI,
	ZKN_SORTSEARCHSUB_BUTTON_FORM_WATER,
	ZKN_SORTSEARCHSUB_BUTTON_FORM_ARM,
	ZKN_SORTSEARCHSUB_BUTTON_FORM_STRAIGHT,
	ZKN_SORTSEARCHSUB_BUTTON_FORM_TAIL,
	ZKN_SORTSEARCHSUB_BUTTON_FORM_LEGS,
	ZKN_SORTSEARCHSUB_BUTTON_FORM_FOUR_LEGS,
	ZKN_SORTSEARCHSUB_BUTTON_FORM_TWO_WING,
	ZKN_SORTSEARCHSUB_BUTTON_FORM_MANY_LEGS,
	ZKN_SORTSEARCHSUB_BUTTON_FORM_COMP,
	ZKN_SORTSEARCHSUB_BUTTON_FORM_TWO_LEGS,
	ZKN_SORTSEARCHSUB_BUTTON_FORM_FOUR_WING,
	ZKN_SORTSEARCHSUB_BUTTON_FORM_HAITSUKUBARI,
	ZKN_SORTSEARCHSUB_BUTTON_FORM_NONE,
	ZKN_SORTSEARCHSUB_BUTTON_FORM_NUM,
};

#define ZKN_SORTSEARCHSUB_BUTTON_FORM_SIZX		( 48 )
#define ZKN_SORTSEARCHSUB_BUTTON_FORM_SIZY		( 32 )

#define ZKN_SORTSEARCHSUB_BUTTON_FORM_DEF_X			( 28 )
#define ZKN_SORTSEARCHSUB_BUTTON_FORM_OFS_X			( 56 )

// カーソル
#define ZKN_SORTSEARCHSUB_CURSOR_FORM_MAX_X	( 4 )
#define ZKN_SORTSEARCHSUB_CURSOR_FORM_SIZX		( 32 )
#define ZKN_SORTSEARCHSUB_CURSOR_FORM_SIZY		( 20 )

// ボタンフェード種類
enum{
	ZKN_SORTSEARCH_SUB_BUTTON_FADE_NONE,
	ZKN_SORTSEARCH_SUB_BUTTON_FADE_IN,
	ZKN_SORTSEARCH_SUB_BUTTON_FADE_OUT,
};
#define ZKN_SORTSEARCHSUB_BUTTON_FADE_SYNC	(2)

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	検索ソート画面　グローバル変数
//=====================================
typedef struct {
	int*				p_event_key;		// イベントキー
	ZKN_GLB_DATA*		p_glb;				// グローバルデータ
	ZKN_APL_DATA*		p_main_apl;			// メイン画面アプリデータ

	// 自分のアプリケーションﾃﾞｰﾀ
	ZKN_APL_DATA*		p_my_apl;			// 描画との連携を取る必要があるため
} ZKN_SORTSEARCHSUB_GLB;

//-------------------------------------
//	検索ソート画面　描画グローバル変数
//=====================================
typedef struct {
	ZKN_GLB_DRAWDATA*	p_drawglb;			// 描画グローバルデータ

	// ボタンフェード用
	int button_fade_req;
	BOOL* button_fade;
} ZKN_SORTSEARCHSUB_DRAWGLB;

//-------------------------------------
//	ボタン用ワーク
//=====================================
typedef struct {
	void* p_glb;
	void* p_work;
} ZKN_SORTSEARCHSUB_BUTTON_WORK;

//-------------------------------------
//	検索ソート画面　内部ワーク
//=====================================
typedef struct {
	// ボタンマネージャ
	BUTTON_MAN* p_button_man;
	TP_HIT_TBL *hit_tbl;	// ボタンデータ
	// サブボタンマネージャ
	BUTTON_MAN* p_button_man_sub;
	TP_HIT_TBL *hit_tbl_sub;	// ボタンデータ
	ZKN_SORTSEARCHSUB_BUTTON_WORK button_work;


	// カーソルシステム
	ZKN_CURSOR* p_cursor;
	ZKN_CURSOR_ONEDATA* p_cursor_tbl;


	int type_page;			// ﾀｲﾌﾟページ

	// ワークローカル今の選択ﾀｲﾌﾟ
	int local_select;	
	int local_type_page;			// 反映チェック用ﾀｲﾌﾟページ

	// ボタン動作ﾃﾞｰﾀ
	int button_event[ ZKN_SORTSEARCHSUB_BUTTON_NUM ];	// ボタンイベントデータ
	int button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_SUB_MAX ];	// ボタンイベントデータ

	// 処理実行ﾃﾞｰﾀ
	int do_flag_common;		// 処理実行ﾃﾞｰﾀ	押されたボタンﾅﾝﾊﾞｰを格納
	int do_flag_select;		// 処理実行ﾃﾞｰﾀ押されたボタンﾅﾝﾊﾞｰを格納

	int type_set_no;		// 設定するﾀｲﾌﾟﾅﾝﾊﾞｰ

	BOOL cursor_no_touch;
	BOOL tp_no_touch;
	

	int req_count;	// 押しっぱなし時の２回目からTRUEが入る

	// ボタンフェード処理待ちフラグ
	BOOL button_fade_flag;
} ZKN_SORTSEARCHSUB_WORK;

//-------------------------------------
//	検索ソート画面　描画ワーク
//=====================================
typedef struct {
	CLACT_WORK_PTR clact[ ZKN_SORTSEARCHSUB_BUTTON_NUM ];
	ZKN_FONTOAM_DATA* p_fontoam[ ZKN_SORTSEARCHSUB_BUTTON_NUM ];

	CLACT_WORK_PTR clact_sub[ ZKN_SORTSEARCHSUB_BUTTON_SUB_MAX ];
	ZKN_FONTOAM_DATA* p_fontoam_sub[ ZKN_SORTSEARCHSUB_BUTTON_SUB_MAX ];
	CLACT_WORK_PTR clact_sub_form[ ZKN_SORTSEARCHSUB_BUTTON_SUB_MAX ];

	CLACT_U_RES_OBJ_PTR res_obj[ ZKN_CLACT_RES_OBJ_NUM_DEF ];	// Resourceオブジェポインタ
	CLACT_U_RES_OBJ_PTR res_obj_form[ ZKN_CLACT_RES_OBJ_NUM_DEF ];	// Resourceオブジェポインタ

	// ワークローカル今の選択ﾀｲﾌﾟ
	int local_select;	
	int local_type_page;			// ﾀｲﾌﾟページ


	// ボタンフェード処理
	ZKN_UTIL_MOVE_WORK fade_work;
	int do_fade;
	int do_fade_seq;
	BOOL* end_flag;
} ZKN_SORTSEARCHSUB_DRAW;

//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *		アプリケーションデータ作成関係
 */
//-----------------------------------------------------------------------------
static ZKN_SORTSEARCHSUB_GLB* MakeSortSearchSubGlb( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_SORTSEARCHSUB_DRAWGLB* MakeSortSearchSubDrawGlb( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_EVENT_DATA* MakeSortSearchSubEvent( int heap, ZKN_SYS_PTR zkn_sys );
static void DeleteSortSearchSubGlb( ZKN_SORTSEARCHSUB_GLB* p_glb );
static void DeleteSortSearchSubDrawGlb( ZKN_SORTSEARCHSUB_DRAWGLB* p_glb );
static void DeleteSortSearchSubEvent( ZKN_EVENT_DATA* p_event );


static int SortSearchSubEventDataNumGet( void );

//-----------------------------------------------------------------------------
/**
 *		プロセス関係
 */
//-----------------------------------------------------------------------------
static int ZknSortSearchSubProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknSortSearchSubProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknSortSearchSubProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknSortSearchSubProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknSortSearchSubProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknSortSearchSubProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );


// フェード処理
static void ZknSortSearchSubSortFadeSys( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb, const ZKN_SORTSEARCHSUB_GLB* cp_glb );

// Resource読み込み
static void ZknSortSearchSubLoadRes( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb, const ZKN_SORTSEARCHSUB_GLB* cp_glb, const ZKN_SORTSEARCHSUB_WORK* cp_datawork, int heap );
static void ZknSortSearchSubDeleteRes( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb );
static void ZknSortSearchSubSetUpBg( ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb, const ZKN_SORTSEARCHSUB_GLB* cp_glb, int heap );
static void ZknSortSearchSubLoadOam( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb, int heap );
static void ZknSortSearchSubReleaseOam( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb );
static void ZknSortSearchSubLoadOamForm( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb, int heap );
static void ZknSortSearchSubReleaseOamForm( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb );


// ボタンフェード処理
static void ZknSortSearchSubButtonFadeCont( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb );
static void ZknSortSearchSubButtonFade( ZKN_SORTSEARCHSUB_DRAW* p_draw );
static void ZknSortSearchSubButtonFadeOamModeSet_Pack( ZKN_SORTSEARCHSUB_DRAW* p_draw, int mode, int select_type, int type_page );
static void ZknSortSearchSubButtonFadeOamModeSet( ZKN_SORTSEARCHSUB_DRAW* p_draw, int mode );
static void ZknSortSearchSubButtonFadeOamModeSet_Type1Ver( ZKN_SORTSEARCHSUB_DRAW* p_draw, int mode );
static void ZknSortSearchSubButtonFadeOamModeSet_Type2Ver( ZKN_SORTSEARCHSUB_DRAW* p_draw, int mode );

//-----------------------------------------------------------------------------
/**
 *	セルアクター登録
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubAddClact( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb, int heap );
static void ZknSortSearchSubDeleteClact( ZKN_SORTSEARCHSUB_DRAW* p_draw );
static void ZknSortSearchSubAddSubClact( ZKN_SORTSEARCHSUB_DRAW* p_draw, CLACT_ADD_SIMPLE* p_add, int select_type, int local_type_page );
static void ZknSortSearchSubChgClact( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb, int heap );

// 共通ボタン登録
static void ZknSortSearchSubAddClactCommon( ZKN_SORTSEARCHSUB_DRAW* p_draw, CLACT_ADD_SIMPLE* p_add );
static void ZknSortSearchSubDeleteClactCommon( ZKN_SORTSEARCHSUB_DRAW* p_draw );
// 破棄共通
static void ZknSortSearchSubDeleteClactSub( ZKN_SORTSEARCHSUB_DRAW* p_draw );
// ｿｰﾄ画面登録
static void ZknSortSearchSubAddClactSort( ZKN_SORTSEARCHSUB_DRAW* p_draw, CLACT_ADD_SIMPLE* p_add );
// なまえ画面登録
static void ZknSortSearchSubAddClactName( ZKN_SORTSEARCHSUB_DRAW* p_draw, CLACT_ADD_SIMPLE* p_add );
// ﾀｲﾌﾟ1画面登録
static void ZknSortSearchSubAddClactType1( ZKN_SORTSEARCHSUB_DRAW* p_draw, CLACT_ADD_SIMPLE* p_add );
// ﾀｲﾌﾟ2画面登録
static void ZknSortSearchSubAddClactType2( ZKN_SORTSEARCHSUB_DRAW* p_draw, CLACT_ADD_SIMPLE* p_add );
// フォーム画面登録
static void ZknSortSearchSubAddClactForm( ZKN_SORTSEARCHSUB_DRAW* p_draw, CLACT_ADD_SIMPLE* p_add );
static void ZknSortSearchSubAddClactForm_Gra( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb, int heap );
static void ZknSortSearchSubDeleteClactForm_Gra( ZKN_SORTSEARCHSUB_DRAW* p_draw );

//-----------------------------------------------------------------------------
/**
 *	FONTOAM作成
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubAddFontOam( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb, int heap );
static void ZknSortSearchSubDeleteFontOam( ZKN_SORTSEARCHSUB_DRAW* p_draw );
static void ZknSortSearchSubAddSubFontOam( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_FONTOAM_INIT* p_fontoam_init, ZKN_FONTOAM_SYS_PTR fontoam_sys, int select_type, int local_type_page );
static void ZknSortSearchSubChgFontOam( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb, int heap );
// 共通ボタン
static void ZknSortSearchSubAddFontCommon( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_FONTOAM_INIT* p_fontoam_init, ZKN_FONTOAM_SYS_PTR fontoam_sys );
static void ZknSortSearchSubDeleteFontCommon( ZKN_SORTSEARCHSUB_DRAW* p_draw );
// 破棄共通
static void ZknSortSearchSubDeleteFontSub( ZKN_SORTSEARCHSUB_DRAW* p_draw );
// ｿｰﾄボタン
static void ZknSortSearchSubAddFontSort( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_FONTOAM_INIT* p_fontoam_init, ZKN_FONTOAM_SYS_PTR fontoam_sys );
// 名前ボタン
static void ZknSortSearchSubAddFontName( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_FONTOAM_INIT* p_fontoam_init, ZKN_FONTOAM_SYS_PTR fontoam_sys );
// ﾀｲﾌﾟ1ボタン
static void ZknSortSearchSubAddFontType1( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_FONTOAM_INIT* p_fontoam_init, ZKN_FONTOAM_SYS_PTR fontoam_sys );
// ﾀｲﾌﾟ2ボタン
static void ZknSortSearchSubAddFontType2( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_FONTOAM_INIT* p_fontoam_init, ZKN_FONTOAM_SYS_PTR fontoam_sys );

//-----------------------------------------------------------------------------
/**
 *		ボタン動作
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubButtonInit( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb, int heap );
static void ZknSortSearchSubButtonAllDelete( ZKN_SORTSEARCHSUB_WORK* p_work );
static void ZknSortSearchSubButtonChgMake( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb, int heap );
static void ZknSortSearchSubButtonMakeSub( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb, int heap, int select_type, int type_page );
static void ZknSortSearchSubButtonMoveAll( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb );
static void ZknSortSearchSubButtonMoveSub( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb, int select_type, int type_page );

static void ZknSortSearchSubButtonEventBuffInit( ZKN_SORTSEARCHSUB_WORK* p_work );

//　共通ボタン用
static void ZknSortSearchSubButtonMake( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb, int heap );
static void ZknSortSearchSubButtonMove( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb );
static void ZknSortSearchSubButtonDelete( ZKN_SORTSEARCHSUB_WORK* p_work );
static void ZknSortSearchSubButtonCallBack( u32 button_no, u32 event, void* p_work );
static void ZknSortSearchSubButtonEventInit( ZKN_SORTSEARCHSUB_WORK* p_work );
static void ZknSortSearchSubButtonSelectEventSet( ZKN_SORTSEARCHSUB_WORK* p_work, int select_type );

// サブボタン用破棄
static void ZknSortSearchSubButtonSubDelete( ZKN_SORTSEARCHSUB_WORK* p_work );
// サブボタンイベント配列初期化
static void ZknSortSearchSubButtonSubEventInit( ZKN_SORTSEARCHSUB_WORK* p_work );
// ソート画面
static void ZknSortSearchSubButtonMakeSort( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb, int heap );
static void ZknSortSearchSubButtonMoveSort( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb );
static void ZknSortSearchSubButtonCallBackSort( u32 button_no, u32 event, void* p_work );
// 名前画面
static void ZknSortSearchSubButtonMakeName( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb, int heap );
static void ZknSortSearchSubButtonMoveName( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb );
static void ZknSortSearchSubButtonCallBackName( u32 button_no, u32 event, void* p_work );
// ﾀｲﾌﾟ1画面
static void ZknSortSearchSubButtonMakeType1( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb, int heap );
static void ZknSortSearchSubButtonMoveType1( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb );
static void ZknSortSearchSubButtonCallBackType1( u32 button_no, u32 event, void* p_work );
static void ZknSortSearchSubButtonSelectSetType1( ZKN_SORTSEARCHSUB_WORK* p_work, int type );
// ﾀｲﾌﾟ2画面
static void ZknSortSearchSubButtonMakeType2( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb, int heap );
static void ZknSortSearchSubButtonMoveType2( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb );
static void ZknSortSearchSubButtonCallBackType2( u32 button_no, u32 event, void* p_work );
static void ZknSortSearchSubButtonSelectSetType2( ZKN_SORTSEARCHSUB_WORK* p_work, int type );
// かたち画面
static void ZknSortSearchSubButtonMakeForm( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb, int heap );
static void ZknSortSearchSubButtonMoveForm( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb );
static void ZknSortSearchSubButtonCallBackForm( u32 button_no, u32 event, void* p_work );

//-----------------------------------------------------------------------------
/**
 *	カーソル制御
 */
//-----------------------------------------------------------------------------
//　共通破棄
static void ZknSortSearchSubCursorDelete( ZKN_SORTSEARCHSUB_WORK* p_work );

// カーソル動作共通
static void ZknSortSearchSubCursorMake( ZKN_SORTSEARCHSUB_WORK* p_work, int heap );
static void ZknSortSearchSubCursorMakeSub( ZKN_SORTSEARCHSUB_WORK* p_work, int heap, int select_type, int type_page );
static void ZknSortSearchSubCursorInit( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb );
static void ZknSortSearchSubCursorMove( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb );
static void ZknSortSearchSubCursorMoveSub( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb, int select_type, int type_page );
static void ZknSortSearchSubCursorChg( ZKN_SORTSEARCHSUB_WORK* p_work, int heap );
static void ZknSortSearchSubCursorCommonSet( ZKN_CURSOR_ONEDATA* p_data, int id );
static void ZknSortSearchSubCursorMoveCommon( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb );

// ｿｰﾄ画面
static void ZknSortSearchSubCursorMakeSort( ZKN_SORTSEARCHSUB_WORK* p_work, int heap );
static void ZknSortSearchSubCursorMoveSort( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb );
// 名前画面
static void ZknSortSearchSubCursorMakeName( ZKN_SORTSEARCHSUB_WORK* p_work, int heap );
static void ZknSortSearchSubCursorMoveName( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb );
// ﾀｲﾌﾟ1画面
static void ZknSortSearchSubCursorMakeType1( ZKN_SORTSEARCHSUB_WORK* p_work, int heap );
static void ZknSortSearchSubCursorMoveType1( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb );
// ﾀｲﾌﾟ2画面
static void ZknSortSearchSubCursorMakeType2( ZKN_SORTSEARCHSUB_WORK* p_work, int heap );
static void ZknSortSearchSubCursorMoveType2( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb );
// 形画面
static void ZknSortSearchSubCursorMakeForm( ZKN_SORTSEARCHSUB_WORK* p_work, int heap );
static void ZknSortSearchSubCursorMoveForm( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb );

// 描画処理
static void ZknSortSearchSubCursorDrawInit( ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb, const ZKN_SORTSEARCHSUB_WORK* cp_work, const ZKN_SORTSEARCHSUB_GLB* cp_glb );
static void ZknSortSearchSubCursorDrawPack( ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb, const ZKN_SORTSEARCHSUB_WORK* cp_work, const ZKN_SORTSEARCHSUB_GLB* cp_glb );
static void ZknSortSearchSubCursorDraw( ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb, const ZKN_SORTSEARCHSUB_WORK* cp_work );
static BOOL ZknSortSearchSubCursorOnOff( ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb,  BOOL flag );


//-----------------------------------------------------------------------------
/**
 *		実行動作
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubDoInit( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb );
static void ZknSortSearchSubDoMain( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb );
static void ZknSortSearchSubDoSelect( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb, int select_type, int type_page );

// 共通ボタンの実行
static void ZknSortSearchSubDoCommon( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb );
// ｿｰﾄボタンの実行
static void ZknSortSearchSubDoSort( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb );
// 名前ボタンの実行
static void ZknSortSearchSubDoName( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb );
// ﾀｲﾌﾟ1ボタンの実行
static void ZknSortSearchSubDoType1( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb );
// ﾀｲﾌﾟ2ボタンの実行
static void ZknSortSearchSubDoType2( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb );
static void ZknSortSearchSubDoTypeSetCommon( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb, int set_num );
// 形ボタンの実行
static void ZknSortSearchSubDoForm( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb );


//----------------------------------------------------------------------------
/**
 *
 *	@brief	検索ソート　アプリ作成
 *
 *	@param	p_data		アプリケーションデータ
 *	@param	zkn_sys		図鑑システム
 *	@param	heap		使用ヒープ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_SortSearchSubAplMake( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap )
{
	ZKN_SORTSEARCHSUB_GLB*	p_glb;
	ZKN_SORTSEARCHSUB_DRAWGLB*	p_drawglb;
	ZKN_EVENT_DATA*	p_event;
	
	p_glb = MakeSortSearchSubGlb( heap, zkn_sys );
	p_drawglb = MakeSortSearchSubDrawGlb( heap, zkn_sys );
	p_event = MakeSortSearchSubEvent( heap, zkn_sys );

	p_data->p_glb_data		= p_glb;
	p_data->p_glb_draw		= p_drawglb;
	p_data->p_event_data	= p_event;
	p_data->event_num		= SortSearchSubEventDataNumGet();

	p_data->do_func[ ZKN_PROC_FUNC_INIT ] = ZknSortSearchSubProcDoFuncInit;
	p_data->do_func[ ZKN_PROC_FUNC_MAIN ] = ZknSortSearchSubProcDoFuncMain;
	p_data->do_func[ ZKN_PROC_FUNC_DELETE ] = ZknSortSearchSubProcDoFuncDelete;
	p_data->draw_func[ ZKN_PROC_FUNC_INIT ] = ZknSortSearchSubProcDrawFuncInit;
	p_data->draw_func[ ZKN_PROC_FUNC_MAIN ] = ZknSortSearchSubProcDrawFuncMain;
	p_data->draw_func[ ZKN_PROC_FUNC_DELETE ] = ZknSortSearchSubProcDrawFuncDelete;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ポケモンリスト	サブ画面　メニューアプリ破棄
 *
 *	@param	p_data	アプリケーションデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_SortSearchSubAplDelete( ZKN_APL_DATA* p_data )
{
	DeleteSortSearchSubGlb( p_data->p_glb_data ); 
	DeleteSortSearchSubDrawGlb( p_data->p_glb_draw ); 
	DeleteSortSearchSubEvent( p_data->p_event_data );
}



//-----------------------------------------------------------------------------
/**
 *		プライベート関数
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	検索ソート　グローバルデータ作成
 *
 *	@param	heap		ヒープ
 *	@param	zkn_sys		図鑑システム
 *
 *	@return	グローバルデータ
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_SORTSEARCHSUB_GLB* MakeSortSearchSubGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_SORTSEARCHSUB_GLB* p_glb;
	ZKN_APL_DATA* p_apl;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_SORTSEARCHSUB_GLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_SORTSEARCHSUB_GLB) );

	// main画面からのイベントキー
	p_glb->p_event_key = ZKN_SYS_GetEventKeyPtrMain( zkn_sys ); 

	// グローバルデータ
	p_glb->p_glb = ZKN_SYS_GetGlbData( zkn_sys );


	// メイン画面アプリﾃﾞｰﾀ
	p_glb->p_main_apl = ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_SORTSEARCH );

	// 自分のアプリﾃﾞｰﾀ
	p_glb->p_my_apl = ZKN_GetAplDataSub( zkn_sys, ZKN_SYS_APLSUB_SORTSEARCH );
	
	return p_glb;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	検索ソート　グローバルデータ作成
 *
 *	@param	heap		ヒープ
 *	@param	zkn_sys		図鑑システム
 *
 *	@return	グローバルデータ
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_SORTSEARCHSUB_DRAWGLB* MakeSortSearchSubDrawGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_SORTSEARCHSUB_DRAWGLB* p_glb;
	ZKN_APL_DATA* p_apl;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_SORTSEARCHSUB_DRAWGLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_SORTSEARCHSUB_DRAWGLB) );

	// 描画データ
	p_glb->p_drawglb = ZKN_SYS_GetGlbDrawData( zkn_sys );

	return p_glb;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	検索ソート　イベント作成
 *
 *	@param	heap		使用するヒープ
 *	@param	zkn_sys		図鑑システム
 *
 *	@return	イベントデータ
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_EVENT_DATA* MakeSortSearchSubEvent( int heap, ZKN_SYS_PTR zkn_sys )
{
	return NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	検索ソート　グローバルデータ破棄
 *
 *	@param	p_glb		グローバルデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteSortSearchSubGlb( ZKN_SORTSEARCHSUB_GLB* p_glb )
{
	GF_ASSERT( p_glb );
	sys_FreeMemoryEz( p_glb );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	検索ソート　グローバルデータ破棄
 *
 *	@param	p_glb		グローバルデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteSortSearchSubDrawGlb( ZKN_SORTSEARCHSUB_DRAWGLB* p_glb )
{
	GF_ASSERT( p_glb );
	sys_FreeMemoryEz( p_glb );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	検索ソート　イベントデータ破棄
 *
 *	@param	p_event	イベントデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteSortSearchSubEvent( ZKN_EVENT_DATA* p_event )
{
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	検索ソートアプリ　イベント数取得
 *	
 *	@param	none	
 *
 *	@return	検索ソートアプリ　イベント数
 *
 *
 */
//-----------------------------------------------------------------------------
static int SortSearchSubEventDataNumGet( void )
{
	return ZKN_SORTSEARCHSUB_EVENT_NUM;
}


//-----------------------------------------------------------------------------
/**
 *		プロセス関係
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	[初期化]
 *	@brief	アプリケーションプロセス	データ変更
 *
 *	@param	p_dodata	ZKN_PROC_DO_DATA
 *	@param	p_glbdata	管理者から受け取るデータ　（保存しておきたいデータ）
 *
 *	@retval	ZKN_PROC_TRUE		次の処理へ進みます。
 *	@retval	ZKN_PROC_FALSE		まだ進みません。
 *
 *
 */
//-----------------------------------------------------------------------------
static int ZknSortSearchSubProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_SORTSEARCHSUB_GLB* p_glb = p_glbdata;
	ZKN_SORTSEARCHSUB_WORK* p_work;
	int i;

	// ワーク作成
	p_work = sys_AllocMemory( p_dodata->heap, sizeof(ZKN_SORTSEARCHSUB_WORK) );
	GF_ASSERT( p_work );
	memset( p_work, 0, sizeof(ZKN_SORTSEARCHSUB_WORK) );
	p_dodata->p_work = p_work;


	// 分岐処理初期化
	p_work->do_flag_common = ZKN_SORTSEARCHSUB_DO_FLAG_INIT;
	ZknSortSearchSubDoInit( p_work, p_glb );


	// ボタンカーソルを作成
	ZknSortSearchSubButtonInit( p_work, p_glb, p_dodata->heap );
	ZknSortSearchSubCursorMake( p_work, p_dodata->heap );
	ZknSortSearchSubCursorInit( p_work, p_glb );


	// ボタンイベントデータ
	for( i=0; i<ZKN_SORTSEARCHSUB_BUTTON_NUM; i++ ){
		p_work->button_event[ i ] = ZKN_UTIL_BUTTON_PUSH_NONE;	// ボタンイベントデータ
	}
	
	return ZKN_PROC_TRUE;
}

//----------------------------------------------------------------------------
/**
 *	[メイン]
 *	@brief	アプリケーションプロセス	データ変更
 *
 *	@param	p_dodata	ZKN_PROC_DO_DATA
 *	@param	p_glbdata	管理者から受け取るデータ　（保存しておきたいデータ）
 *
 *	@retval	ZKN_PROC_TRUE		次の処理へ進みます。
 *	@retval	ZKN_PROC_FALSE		まだ進みません。
 *
 *
 */
//-----------------------------------------------------------------------------
static int ZknSortSearchSubProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_SORTSEARCHSUB_GLB* p_glb = p_glbdata;
	ZKN_SORTSEARCHSUB_WORK*	p_work = p_dodata->p_work;
	ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb = p_glb->p_my_apl->p_glb_draw;
	int select_type;
	int old_local_select;
	
	// 終了へ
	if( p_dodata->end_req == TRUE ){
		return ZKN_PROC_TRUE;
	}


	// lock
	if( p_dodata->lock == TRUE ){
		return ZKN_PROC_FALSE;
	}

	// フェード処理中は動作禁止！！
	if( ZKN_SortSearchAplFadeModeGet( p_glb->p_main_apl ) != ZKN_SORTSEARCH_FADENONE ){
		return ZKN_PROC_FALSE;
	}

	select_type = ZKN_SortSearchAplSelectTypeGet( p_glb->p_main_apl );
	
	switch( p_dodata->seq ){
	// 動作処理
	case 0:	

		// 選択ﾀｲﾌﾟ分岐
		if( (p_work->local_select != select_type) ||
			(p_work->local_type_page != p_work->type_page ) ){

			// ボタンフェードリクエスト
			p_work->button_fade_flag = FALSE;
			p_drawglb->button_fade_req = ZKN_SORTSEARCH_SUB_BUTTON_FADE_OUT;
			p_drawglb->button_fade = &p_work->button_fade_flag;

			// ボタンイベントを初期化
			ZknSortSearchSubButtonEventInit( p_work );
			// 描画のためにボタンイベントの値を設定
			ZknSortSearchSubButtonSelectEventSet( p_work, select_type );


			// ボタン動作変更へ
			p_dodata->seq++;
			break;
		}

		// ボタン動作
		ZknSortSearchSubButtonMoveAll( p_work, p_glb );

		// カーソル動作
		if( (ZKN_GLBDATA_TouchCursorFlagGet( p_glb->p_glb ) == TRUE) ){

			ZknSortSearchSubCursorMove( p_work, p_glb );
		}


		// 動作メイン
		ZknSortSearchSubDoMain( p_work, p_glb );
		break;

	// ボタンフェードアウト待ち
	case 1:
		if( p_work->button_fade_flag ){
			p_dodata->seq ++;

		}
		break;

	// ボタン変更
	case 2:
		old_local_select = p_work->local_select;	// カーソル位置初期化のため保存
		p_work->local_select = select_type;
		p_work->local_type_page = p_work->type_page;
		
		ZknSortSearchSubButtonChgMake( p_work, p_glb, p_dodata->heap );
		ZknSortSearchSubCursorChg( p_work, p_dodata->heap );
		ZknSortSearchSubDoInit( p_work, p_glb );

		// 選択ﾀｲﾌﾟの変更があったときのみカーソル位置を初期化
		if( old_local_select != p_work->local_select ){
			ZknSortSearchSubCursorInit( p_work, p_glb );
		}

		// ボタンフェードリクエスト
		p_work->button_fade_flag = FALSE;
		p_drawglb->button_fade_req = ZKN_SORTSEARCH_SUB_BUTTON_FADE_IN;
		p_drawglb->button_fade = &p_work->button_fade_flag;


		// サブボタン初期化
		ZknSortSearchSubButtonSubEventInit( p_work );
		
		p_dodata->seq++;
		break;

	// ボタンフェードイン待ち
	case 3:
		if( p_work->button_fade_flag ){
			p_dodata->seq ++;
		}
		break;

	// メイン動作処理に戻る
	case 4:
		p_dodata->seq = 0;
		break;
	}

	return ZKN_PROC_FALSE;
}

//----------------------------------------------------------------------------
/**
 *	[破棄]
 *	@brief	アプリケーションプロセス	データ変更
 *
 *	@param	p_dodata	ZKN_PROC_DO_DATA
 *	@param	p_glbdata	管理者から受け取るデータ　（保存しておきたいデータ）
 *
 *	@retval	ZKN_PROC_TRUE		次の処理へ進みます。
 *	@retval	ZKN_PROC_FALSE		まだ進みません。
 *
 *
 */
//-----------------------------------------------------------------------------
static int ZknSortSearchSubProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_SORTSEARCHSUB_WORK* p_work = p_dodata->p_work;

	// ボタンカーソル破棄
	ZknSortSearchSubButtonAllDelete( p_work );
	ZknSortSearchSubCursorDelete( p_work );

	sys_FreeMemoryEz( p_work );
	p_dodata->p_work = NULL;
	
	return ZKN_PROC_TRUE;
}

//----------------------------------------------------------------------------
/**
 * [初期化]
 *
 *	@brief	アプリケーションプロセス	描画
 *
 *	@param	p_glbdraw	描画グローバルデータ
 *	@param	p_drawdata	ZKN_PROC_DRAW_DATA
 *	@param	cp_glbdata	管理者から受け取るデータ　（保存しておきたいデータ）
 *	@param	cp_dodata	今の処理の内部ワークデータ
 *
 *	@retval	ZKN_PROC_TRUE		次の処理へ進みます。
 *	@retval	ZKN_PROC_FALSE		まだ進みません。
 *
 *
 */
//-----------------------------------------------------------------------------
static int ZknSortSearchSubProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_SORTSEARCHSUB_GLB* cp_dataglb = cp_glbdata;
	const ZKN_SORTSEARCHSUB_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb = p_glbdraw;
	ZKN_SORTSEARCHSUB_DRAW* p_drawwork = p_drawdata->p_work;
	BOOL check;

	switch( p_drawdata->seq ){
	case ZKN_SORTSEARCHSUB_SEQINIT_ALLOC:
		p_drawdata->p_work = sys_AllocMemory( p_drawdata->heap, sizeof(ZKN_SORTSEARCHSUB_DRAW) );
		memset( p_drawdata->p_work, 0, sizeof(ZKN_SORTSEARCHSUB_DRAW) );
		p_drawdata->seq++;
		break;
		
	case ZKN_SORTSEARCHSUB_SEQINIT_LOAD:
		ZknSortSearchSubLoadRes( p_drawwork, p_drawglb, cp_dataglb, cp_datawork, p_drawdata->heap );
		
		// フェード初期化
		ChangeBrightnessRequest( ZKN_FADE_SYNC_COMMON,
				BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK, PLANEMASK_ALL, MASK_SUB_DISPLAY );

		// カーソル描画初期化
		ZknSortSearchSubCursorDrawInit( p_drawglb, cp_datawork, cp_dataglb );
		
		p_drawdata->seq++;
		break;
		
	case ZKN_SORTSEARCHSUB_SEQINIT_FADEIN:
		// フェード
		if( IsFinishedBrightnessChg( MASK_SUB_DISPLAY  ) ){
			p_drawdata->seq++;
		}
		break;
		
	case ZKN_SORTSEARCHSUB_SEQINIT_END:
		return ZKN_PROC_TRUE;
	}

	return ZKN_PROC_FALSE;
}

//----------------------------------------------------------------------------
/**
 * [メイン]
 *
 *	@brief	アプリケーションプロセス	描画
 *
 *	@param	p_glbdraw	描画グローバルデータ
 *	@param	p_drawdata	ZKN_PROC_DRAW_DATA
 *	@param	cp_glbdata	管理者から受け取るデータ　（保存しておきたいデータ）
 *	@param	cp_dodata	今の処理の内部ワークデータ
 *
 *	@retval	ZKN_PROC_TRUE		次の処理へ進みます。
 *	@retval	ZKN_PROC_FALSE		まだ進みません。
 *
 *
 */
//-----------------------------------------------------------------------------
static int ZknSortSearchSubProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_SORTSEARCHSUB_GLB* cp_dataglb = cp_glbdata;
	const ZKN_SORTSEARCHSUB_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb = p_glbdraw;
	ZKN_SORTSEARCHSUB_DRAW* p_drawwork = p_drawdata->p_work;
	int i;
	int old_select;
	int old_type_page;
	int pltt_ofs;


	if( ZKN_SortSearchAplFadeModeGet( cp_dataglb->p_main_apl ) != ZKN_SORTSEARCH_FADENONE ){

		// フェードシステム
		ZknSortSearchSubSortFadeSys( p_drawwork, p_drawglb, cp_dataglb );


	}else{

		// フェードインアウト処理
		ZknSortSearchSubButtonFadeCont( p_drawwork, p_drawglb );

		// アクター　フォントOAMの変更処理
		if( (p_drawwork->local_select != cp_datawork->local_select) || 
			(p_drawwork->local_type_page != cp_datawork->local_type_page) ){
			old_select = p_drawwork->local_select;
			old_type_page = p_drawwork->local_type_page;

			p_drawwork->local_select = cp_datawork->local_select;
			p_drawwork->local_type_page = cp_datawork->local_type_page;

			// もしold_selectが形状のときはリソース破棄
			if( old_select == ZKN_SORTSEARCH_SELECT_FORM ){
				ZknSortSearchSubReleaseOamForm( p_drawwork, p_drawglb );
				ZknSortSearchSubDeleteClactForm_Gra( p_drawwork );
			}

			ZknSortSearchSubChgClact( p_drawwork, p_drawglb, p_drawdata->heap );
			ZknSortSearchSubChgFontOam( p_drawwork, p_drawglb, p_drawdata->heap );

			// 次が形状のときはリソース読み込み
			if( p_drawwork->local_select == ZKN_SORTSEARCH_SELECT_FORM ){
				ZknSortSearchSubLoadOamForm( p_drawwork, p_drawglb, p_drawdata->heap );
				ZknSortSearchSubAddClactForm_Gra( p_drawwork, p_drawglb, p_drawdata->heap );
			} 

			// OAMを半透明設定
			ZknSortSearchSubButtonFadeOamModeSet_Pack( p_drawwork, GX_OAM_MODE_XLU, p_drawwork->local_select, p_drawwork->local_type_page );
		}
		
		// カーソル動作
		ZknSortSearchSubCursorDrawPack( p_drawglb, cp_datawork, cp_dataglb );
	}

	// ボタン動作
	for( i=0; i<ZKN_SORTSEARCHSUB_BUTTON_NUM; i++ ){
		ZKN_UTIL_ButtonMove( p_drawwork->clact[ i ],
				cp_datawork->button_event[ i ] );

		// ボタンフォントアニメ
		if( p_drawwork->p_fontoam[ i ] ){
			if( i==ZKN_SORTSEARCHSUB_BUTTON_ACTION ){
				pltt_ofs = ZKN_SORTSEARCHSUB_BUTTONFONT_KETTEI_PLTOFS;		
			}else{
				pltt_ofs = ZKN_SORTSEARCHSUB_BUTTONFONT_PLTOFS;	
			}
			ZKN_UTIL_ButtonFontMove_Col( p_drawwork->clact[ i ],
					p_drawwork->p_fontoam[ i ],
					ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_Y,
					pltt_ofs,
					ZKN_SORTSEARCHSUB_BUTTONFONT_PUSHPLTOFS );
		}
	}

	// サブボタン動作
	for( i=0; i<ZKN_SORTSEARCHSUB_BUTTON_SUB_MAX; i++ ){
		if( p_drawwork->clact_sub[ i ] ){
			ZKN_UTIL_ButtonMove( p_drawwork->clact_sub[ i ],
					cp_datawork->button_event_sub[ i ] );
		}

		// ボタンフォントアニメ
		if( p_drawwork->p_fontoam_sub[ i ] ){
			ZKN_UTIL_ButtonFontMove_Col( p_drawwork->clact_sub[ i ],
					p_drawwork->p_fontoam_sub[ i ],
					ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_Y,
					ZKN_SORTSEARCHSUB_BUTTONFONT_OTHER_PLTOFS,
					ZKN_SORTSEARCHSUB_BUTTONFONT_OTHER_PUSHPLTOFS );
		}

		// 形状ボタン
		if( p_drawwork->clact_sub_form[i] ){
			ZKN_UTIL_ButtonMove( p_drawwork->clact_sub_form[ i ],
					cp_datawork->button_event_sub[ i ] );
		}
	}

	return ZKN_PROC_FALSE;
}

//----------------------------------------------------------------------------
/**
 * [破棄]
 *
 *	@brief	アプリケーションプロセス	描画
 *
 *	@param	p_glbdraw	描画グローバルデータ
 *	@param	p_drawdata	ZKN_PROC_DRAW_DATA
 *	@param	cp_glbdata	管理者から受け取るデータ　（保存しておきたいデータ）
 *	@param	cp_dodata	今の処理の内部ワークデータ
 *
 *	@retval	ZKN_PROC_TRUE		次の処理へ進みます。
 *	@retval	ZKN_PROC_FALSE		まだ進みません。
 *
 *
 */
//-----------------------------------------------------------------------------
static int ZknSortSearchSubProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_SORTSEARCHSUB_GLB* cp_dataglb = cp_glbdata;
	const ZKN_SORTSEARCHSUB_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb = p_glbdraw;
	ZKN_SORTSEARCHSUB_DRAW* p_drawwork = p_drawdata->p_work;
	BOOL check;


	switch( p_drawdata->seq ){
	case ZKN_SORTSEARCHSUB_SEQDELETE_FADEOUT_INIT:

		if( ZKN_SortSearchAplSortDoFlagGet( cp_dataglb->p_main_apl ) == TRUE ){
			p_drawdata->seq = ZKN_SORTSEARCHSUB_SEQDELETE_RELEASE;
		}else{
		
			ChangeBrightnessRequest( COMM_BRIGHTNESS_SYNC, 
					BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL, PLANEMASK_ALL, MASK_SUB_DISPLAY );
			p_drawdata->seq++;
		}
		break;
		
	case ZKN_SORTSEARCHSUB_SEQDELETE_FADEOUT:
		if( IsFinishedBrightnessChg( MASK_SUB_DISPLAY  ) ){
			p_drawdata->seq++;
		}
		break;

	case ZKN_SORTSEARCHSUB_SEQDELETE_RELEASE:
		
		ZknSortSearchSubDeleteRes( p_drawwork, p_drawglb );

		// もし形状のときはリソース破棄
		if( p_drawwork->local_select == ZKN_SORTSEARCH_SELECT_FORM ){
			ZknSortSearchSubReleaseOamForm( p_drawwork, p_drawglb );
			ZknSortSearchSubDeleteClactForm_Gra( p_drawwork );
		}
		
		p_drawdata->seq++;
		break;
		
	case ZKN_SORTSEARCHSUB_SEQDELETE_FREE:

		sys_FreeMemoryEz(p_drawdata->p_work);
		p_drawdata->p_work = NULL;
		p_drawdata->seq++;
		break;
		
		
	case ZKN_SORTSEARCHSUB_SEQDELETE_END:
		return ZKN_PROC_TRUE;
	}

	return ZKN_PROC_FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	Resource読み込み＆画面構築
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	cp_glb		グローバルデータ
 *	@param	cp_datawork	データワーク
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubLoadRes( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb, const ZKN_SORTSEARCHSUB_GLB* cp_glb, const ZKN_SORTSEARCHSUB_WORK* cp_datawork, int heap )
{
	// BG設定
	ZknSortSearchSubSetUpBg( p_drawglb, cp_glb, heap );

	// リソース読み込み
	ZknSortSearchSubLoadOam( p_draw, p_drawglb, heap );

	// OAM登録
	ZknSortSearchSubAddClact( p_draw, p_drawglb, heap );


	// FONTOAM
	ZknSortSearchSubAddFontOam( p_draw, p_drawglb, heap );

	// OAMを半透明設定
	ZknSortSearchSubButtonFadeOamModeSet_Pack( p_draw, GX_OAM_MODE_XLU, p_draw->local_select, p_draw->local_type_page );

}

//----------------------------------------------------------------------------
/**
 *	@brief	Resource破棄
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubDeleteRes( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb )
{
	// FOMTOAM	
	ZknSortSearchSubDeleteFontOam( p_draw );

	// OAM
	ZknSortSearchSubDeleteClact( p_draw );

	// OAMリソース
	ZknSortSearchSubReleaseOam( p_draw, p_drawglb );

	// カーソル表示のOFF
	ZKN_UTIL_CursorSetDrawFlag( &p_drawglb->p_drawglb->cursor, FALSE );
}

//----------------------------------------------------------------------------
/**
 *	@brief	背景面セット	
 *
 *	@param	p_drawglb	描画グローバル
 *	@param	cp_glb		グローバル
 *	@param	heap		ヒープ
 *
 *	@return	none
 *
 * [イベントで出てくる島のスクリーンデータ書き換えもこの中]
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubSetUpBg( ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb, const ZKN_SORTSEARCHSUB_GLB* cp_glb, int heap )
{
	void* buff;
	NNSG2dScreenData* p_scrn;

	// キャラクタデータ転
	ZKN_GLBDATA_BgCharSet( p_drawglb->p_drawglb, NARC_zukan_zkn_list_sub_lzh_NCGR, p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_S, 0, 0, TRUE, heap );
	// スクリーンデータ読み込み
	buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_sort_bg_sub2_lzh_NSCR, TRUE, &p_scrn, heap );
	
	// スクリーンデータ書き込み
	GF_BGL_ScrWrite( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_S,
			p_scrn->rawData, 0, 0,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	sys_FreeMemoryEz( buff );

	// スクリーンデータ転送
	GF_BGL_LoadScreenV_Req(p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_S );
}



//----------------------------------------------------------------------------
/**
 *	@brief	ボタンﾃﾞｰﾀ初期化作成
 *
 *	@param	p_work		ﾃﾞｰﾀワーク
 *	@param	p_glb		ﾃﾞｰﾀグローバル
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubButtonInit( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb, int heap )
{
	// 共通ボタン作成
	ZknSortSearchSubButtonMake( p_work, p_glb, heap );

	// サブ面ボタン作成
	ZknSortSearchSubButtonMakeSub( p_work, p_glb, heap, p_work->local_select, p_work->local_type_page );

	// ボタンイベントバッファ初期化
	ZknSortSearchSubButtonEventBuffInit( p_work );
}
// ボタンイベントバッファ初期化
static void ZknSortSearchSubButtonEventBuffInit( ZKN_SORTSEARCHSUB_WORK* p_work )
{
	int i;
	
	for( i = 0; i < ZKN_SORTSEARCHSUB_BUTTON_NUM; i++ ){
		p_work->button_event[ i ] = BMN_EVENT_SLIDEOUT;
	}

	for( i = 0; i < ZKN_SORTSEARCHSUB_BUTTON_SUB_MAX; i++ ){
		p_work->button_event_sub[ i ] = BMN_EVENT_SLIDEOUT;
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	全ボタンﾃﾞｰﾀ破棄
 *
 *	@param	p_work	ﾃﾞｰﾀワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubButtonAllDelete( ZKN_SORTSEARCHSUB_WORK* p_work )
{
	// 共通ボタン
	ZknSortSearchSubButtonDelete( p_work );

	// サブ面ボタン
	ZknSortSearchSubButtonSubDelete( p_work );
}

//----------------------------------------------------------------------------
/**
 *	@brief	サブ面ボタンﾃﾞｰﾀの変更
 *
 *	@param	p_work	ﾃﾞｰﾀワーク
 *	@param	p_glb	ﾃﾞｰﾀグローバル
 *	@param	heap	ヒープ 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubButtonChgMake( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb, int heap )
{
	// 今までのを破棄
	ZknSortSearchSubButtonSubDelete( p_work );


	// 再作成
	ZknSortSearchSubButtonMakeSub( p_work, p_glb, heap, p_work->local_select, p_work->local_type_page );
}

//----------------------------------------------------------------------------
/**
 *	@brief	サブ面ボタン作成
 *
 *	@param	p_work		ﾃﾞｰﾀワーク
 *	@param	p_glb		ﾃﾞｰﾀグローバル
 *	@param	heap		ヒープ
 *	@param	select_type	選択ﾀｲﾌﾟ
 *	@param	type_page	ﾀｲﾌﾟページ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubButtonMakeSub( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb, int heap, int select_type, int type_page )
{
	switch( select_type ){
	case ZKN_SORTSEARCH_SELECT_SORT:
		ZknSortSearchSubButtonMakeSort( p_work, p_glb, heap );
		break;
		
	case ZKN_SORTSEARCH_SELECT_NEME:
		ZknSortSearchSubButtonMakeName( p_work, p_glb, heap );
		break;
		
	case ZKN_SORTSEARCH_SELECT_TYPE:
		if( type_page == 0 ){
			ZknSortSearchSubButtonMakeType1( p_work, p_glb, heap );
		}else{
			ZknSortSearchSubButtonMakeType2( p_work, p_glb, heap );
		}
		break;
		
	case ZKN_SORTSEARCH_SELECT_FORM:
		ZknSortSearchSubButtonMakeForm( p_work, p_glb, heap );
		break;
		
	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ボタンの動作
 *
 *	@param	p_work	ﾃﾞｰﾀワーク
 *	@param	p_glb	ﾃﾞｰﾀグローバル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubButtonMoveAll( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb )
{
	// 共通ボタン動作
	ZknSortSearchSubButtonMove( p_work, p_glb );


	//　選択ﾀｲﾌﾟ別動作
	ZknSortSearchSubButtonMoveSub( p_work, p_glb, p_work->local_select, p_work->local_type_page );
}

//----------------------------------------------------------------------------
/**
 *	@brief	サブ面ボタン動作
 *
 *	@param	p_work			ﾃﾞｰﾀワーク
 *	@param	p_glb			ﾃﾞｰﾀグローバル
 *	@param	select_type		選択ﾀｲﾌﾟ
 *	@param	type_page		ﾀｲﾌﾟページ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubButtonMoveSub( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb, int select_type, int type_page )
{
	switch( select_type ){
	case ZKN_SORTSEARCH_SELECT_SORT:
		ZknSortSearchSubButtonMoveSort( p_work, p_glb );
		break;
		
	case ZKN_SORTSEARCH_SELECT_NEME:
		ZknSortSearchSubButtonMoveName( p_work, p_glb );
		break;
		
	case ZKN_SORTSEARCH_SELECT_TYPE:
		if( type_page == 0 ){
			ZknSortSearchSubButtonMoveType1( p_work, p_glb );
		}else{
			ZknSortSearchSubButtonMoveType2( p_work, p_glb );
		}
		break;
		
	case ZKN_SORTSEARCH_SELECT_FORM:
		ZknSortSearchSubButtonMoveForm( p_work, p_glb );
		break;
		
	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ボタンタッチデータ作成
 *
 *	@param	p_work	ワーク
 *	@param	p_glb	グローバルデータ
 *	@param	heap	ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubButtonMake( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb, int heap )
{
	// テーブル作成
	p_work->hit_tbl = sys_AllocMemory( heap, sizeof(TP_HIT_TBL) * ZKN_SORTSEARCHSUB_BUTTON_NUM );

	// テーブルデータ設定
	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_SORTSEARCHSUB_BUTTON_NARABI ],
			ZKN_SORTSEARCHSUB_BUTTON_NARABI_Y - (ZKN_SORTSEARCHSUB_BUTTON_SIZY/2),
			ZKN_SORTSEARCHSUB_BUTTON_NARABI_Y + (ZKN_SORTSEARCHSUB_BUTTON_SIZY/2),
			ZKN_SORTSEARCHSUB_BUTTON_X - (ZKN_SORTSEARCHSUB_BUTTON_SIZX/2),
			ZKN_SORTSEARCHSUB_BUTTON_X + (ZKN_SORTSEARCHSUB_BUTTON_SIZX/2) );
	
	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_SORTSEARCHSUB_BUTTON_BACK ],
			ZKN_SORTSEARCHSUB_BUTTON_BACK_Y - (ZKN_SORTSEARCHSUB_BUTTON_SIZY/2),
			ZKN_SORTSEARCHSUB_BUTTON_BACK_Y + (ZKN_SORTSEARCHSUB_BUTTON_SIZY/2),
			ZKN_SORTSEARCHSUB_BUTTON_BACK_X - (ZKN_SORTSEARCHSUB_BUTTON_BACK_SIZX/2),
			ZKN_SORTSEARCHSUB_BUTTON_BACK_X + (ZKN_SORTSEARCHSUB_BUTTON_BACK_SIZX/2) );

	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_SORTSEARCHSUB_BUTTON_NAME ],
			ZKN_SORTSEARCHSUB_BUTTON_NAME_Y - (ZKN_SORTSEARCHSUB_BUTTON_SIZY/2),
			ZKN_SORTSEARCHSUB_BUTTON_NAME_Y + (ZKN_SORTSEARCHSUB_BUTTON_SIZY/2),
			ZKN_SORTSEARCHSUB_BUTTON_X - (ZKN_SORTSEARCHSUB_BUTTON_SIZX/2),
			ZKN_SORTSEARCHSUB_BUTTON_X + (ZKN_SORTSEARCHSUB_BUTTON_SIZX/2) );

	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_SORTSEARCHSUB_BUTTON_TYPE ],
			ZKN_SORTSEARCHSUB_BUTTON_TYPE_Y - (ZKN_SORTSEARCHSUB_BUTTON_SIZY/2),
			ZKN_SORTSEARCHSUB_BUTTON_TYPE_Y + (ZKN_SORTSEARCHSUB_BUTTON_SIZY/2),
			ZKN_SORTSEARCHSUB_BUTTON_X - (ZKN_SORTSEARCHSUB_BUTTON_SIZX/2),
			ZKN_SORTSEARCHSUB_BUTTON_X + (ZKN_SORTSEARCHSUB_BUTTON_SIZX/2) );

	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_SORTSEARCHSUB_BUTTON_FORM ],
			ZKN_SORTSEARCHSUB_BUTTON_FORM_Y - (ZKN_SORTSEARCHSUB_BUTTON_SIZY/2),
			ZKN_SORTSEARCHSUB_BUTTON_FORM_Y + (ZKN_SORTSEARCHSUB_BUTTON_SIZY/2),
			ZKN_SORTSEARCHSUB_BUTTON_X - (ZKN_SORTSEARCHSUB_BUTTON_SIZX/2),
			ZKN_SORTSEARCHSUB_BUTTON_X + (ZKN_SORTSEARCHSUB_BUTTON_SIZX/2) );

	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_SORTSEARCHSUB_BUTTON_ACTION ],
			ZKN_SORTSEARCHSUB_BUTTON_ACTION_Y - (ZKN_SORTSEARCHSUB_BUTTON_SIZY/2),
			ZKN_SORTSEARCHSUB_BUTTON_ACTION_Y + (ZKN_SORTSEARCHSUB_BUTTON_SIZY/2),
			ZKN_SORTSEARCHSUB_BUTTON_ACTION_X - (ZKN_SORTSEARCHSUB_BUTTON_ACTION_SIZX/2),
			ZKN_SORTSEARCHSUB_BUTTON_ACTION_X + (ZKN_SORTSEARCHSUB_BUTTON_ACTION_SIZX/2) );

	p_work->button_work.p_glb = p_glb;
	p_work->button_work.p_work = p_work;

	// ボタンマネージャ作成
	p_work->p_button_man = BMN_Create( 
			p_work->hit_tbl,
			ZKN_SORTSEARCHSUB_BUTTON_NUM,
			ZknSortSearchSubButtonCallBack,
			&p_work->button_work,
			heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ボタン動作
 *
 *	@param	p_work	ワーク
 *	@param	p_glb	グローバルデータ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubButtonMove( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb )
{
	// ボタンイベント初期化
	ZknSortSearchSubButtonEventInit( p_work );
	
	BMN_Main( p_work->p_button_man );

	// 今選択中の項目のボタンは押しっぱなし
	ZknSortSearchSubButtonSelectEventSet( p_work, p_work->local_select );
}

// イベント初期
static void ZknSortSearchSubButtonEventInit( ZKN_SORTSEARCHSUB_WORK* p_work )
{
	int i;
	
	// 放されたら全てのボタンが元の絵に戻る
	for( i = 0; i < ZKN_SORTSEARCHSUB_BUTTON_NUM; i++ ){
		p_work->button_event[ i ] = BMN_EVENT_SLIDEOUT;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ボタンのセレクトﾀｲﾌﾟ設定
 *
 *	@param	p_work 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubButtonSelectEventSet( ZKN_SORTSEARCHSUB_WORK* p_work, int select_type )
{
	switch( select_type ){
	case ZKN_SORTSEARCH_SELECT_SORT:
		if( p_work->button_event[ ZKN_SORTSEARCHSUB_BUTTON_NARABI ] != BMN_EVENT_HOLD ){
			p_work->button_event[ ZKN_SORTSEARCHSUB_BUTTON_NARABI ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_SORTSEARCH_SELECT_NEME:
		if( p_work->button_event[ ZKN_SORTSEARCHSUB_BUTTON_NAME ] != BMN_EVENT_HOLD ){
			p_work->button_event[ ZKN_SORTSEARCHSUB_BUTTON_NAME ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_SORTSEARCH_SELECT_TYPE:
		if( p_work->button_event[ ZKN_SORTSEARCHSUB_BUTTON_TYPE ] != BMN_EVENT_HOLD ){
			p_work->button_event[ ZKN_SORTSEARCHSUB_BUTTON_TYPE ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_SORTSEARCH_SELECT_FORM:
		if( p_work->button_event[ ZKN_SORTSEARCHSUB_BUTTON_FORM ] != BMN_EVENT_HOLD ){
			p_work->button_event[ ZKN_SORTSEARCHSUB_BUTTON_FORM ] = BMN_EVENT_RELEASE;
		}
		break;
	default:
		break;
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	ボタン破棄
 *
 *	@param	p_work	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubButtonDelete( ZKN_SORTSEARCHSUB_WORK* p_work )
{
	BMN_Delete( p_work->p_button_man );

	// テーブルワーク破棄
	sys_FreeMemoryEz( p_work->hit_tbl );
	p_work->hit_tbl = NULL;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ボタンイベントコールバック
 *
 *	@param	button_no	ボタンナンバー
 *	@param	event		イベントタイプ
 *	@param	p_work		ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubButtonCallBack( u32 button_no, u32 event, void* p_work )
{
	ZKN_SORTSEARCHSUB_BUTTON_WORK* p_button_work = p_work;
	ZKN_SORTSEARCHSUB_GLB* p_glb = p_button_work->p_glb;
	ZKN_SORTSEARCHSUB_WORK* p_subwork = p_button_work->p_work;

	// ボタンイベント格納
	p_subwork->button_event[ button_no ] = event;
	
	switch( event ){
	case BMN_EVENT_HOLD:
		p_subwork->do_flag_common = button_no;
		p_subwork->req_count ++;
		break;

	default:
		p_subwork->req_count = 0;
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	サブボタン用破棄
 *
 *	@param	p_work
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubButtonSubDelete( ZKN_SORTSEARCHSUB_WORK* p_work )
{
	BMN_Delete( p_work->p_button_man_sub );

	// テーブルワーク破棄
	sys_FreeMemoryEz( p_work->hit_tbl_sub );
	p_work->hit_tbl_sub = NULL;
}

//----------------------------------------------------------------------------
/**
 *	@brief	サブボタンイベント初期化
 *
 *	@param	p_work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubButtonSubEventInit( ZKN_SORTSEARCHSUB_WORK* p_work )
{
	int i;
	
	// 放されたら全てのボタンが元の絵に戻る
	for( i = 0; i < ZKN_SORTSEARCHSUB_BUTTON_SUB_MAX; i++ ){
		p_work->button_event_sub[ i ] = BMN_EVENT_SLIDEOUT;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ソート画面
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubButtonMakeSort( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb, int heap )
{
	int i, j;
	int x, y;
	// テーブル作成
	p_work->hit_tbl_sub = sys_AllocMemory( heap, sizeof(TP_HIT_TBL) * ZKN_SORTSEARCHSUB_BUTTON_NARABI_NUM );


	// 各座標異OAMを作成する
	for( i=0; i<3; i++ ){
		y = ZKN_SORTSEARCHSUB_BUTTON_01_Y + (i * (ZKN_SORTSEARCHSUB_BUTTON_01_Y - ZKN_SORTSEARCHSUB_BUTTON_00_Y));
		for( j=0; j<2; j++ ){
			x = ZKN_SORTSEARCHSUB_BUTTONDEF_00_X + (j * (ZKN_SORTSEARCHSUB_BUTTONDEF_01_X - ZKN_SORTSEARCHSUB_BUTTONDEF_00_X));

			// テーブルデータ設定
			ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl_sub[ (i*2)+j ],
					y - (ZKN_SORTSEARCHSUB_BUTTON_SIZY/2),
					y + (ZKN_SORTSEARCHSUB_BUTTON_SIZY/2),
					x - (ZKN_SORTSEARCHSUB_BUTTON_ACTION_SIZX/2),
					x + (ZKN_SORTSEARCHSUB_BUTTON_ACTION_SIZX/2) );
		}
	}
	

	p_work->button_work.p_glb = p_glb;
	p_work->button_work.p_work = p_work;

	// ボタンマネージャ作成
	p_work->p_button_man_sub = BMN_Create( 
			p_work->hit_tbl_sub,
			ZKN_SORTSEARCHSUB_BUTTON_NARABI_NUM,
			ZknSortSearchSubButtonCallBackSort,
			&p_work->button_work,
			heap );
}
static void ZknSortSearchSubButtonMoveSort( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb )
{
	int i;
	
	// 放されたら全てのボタンが元の絵に戻る
	for( i = 0; i < ZKN_SORTSEARCHSUB_BUTTON_NARABI_NUM; i++ ){
		p_work->button_event_sub[ i ] = BMN_EVENT_SLIDEOUT;
	}
	
	BMN_Main( p_work->p_button_man_sub );

	// 今選択中のボタンを押しっぱなしにする
	switch( ZKN_SortSearchAplSortTypeGet( p_glb->p_main_apl ) ){
	case ZKN_POKELIST_SORT_NORMAL:		// ポケモンナンバー
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NARABI_NUMBER ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NARABI_NUMBER ] = BMN_EVENT_RELEASE;
		}
		break;
		
	case ZKN_POKELIST_SORT_GOZYUUON:		// 五十音
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NARABI_AIUEO ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NARABI_AIUEO ] = BMN_EVENT_RELEASE;
		}
		break;
		
	case ZKN_POKELIST_SORT_GRAM_L:		// 重い
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NARABI_HEAVY ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NARABI_HEAVY ] = BMN_EVENT_RELEASE;
		}
		break;
		
	case ZKN_POKELIST_SORT_GRAM_S:		// 軽い
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NARABI_LIGHT ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NARABI_LIGHT ] = BMN_EVENT_RELEASE;
		}
		break;
		
	case ZKN_POKELIST_SORT_HIGH_L:		// 高い
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NARABI_TALL ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NARABI_TALL ] = BMN_EVENT_RELEASE;
		}
		break;
		
	case ZKN_POKELSIT_SOTT_HIGH_S:		// 低い
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NARABI_SHORT ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NARABI_SHORT ] = BMN_EVENT_RELEASE;
		}
		break;
	}
}
static void ZknSortSearchSubButtonCallBackSort( u32 button_no, u32 event, void* p_work )
{
	ZKN_SORTSEARCHSUB_BUTTON_WORK* p_button_work = p_work;
	ZKN_SORTSEARCHSUB_GLB* p_glb = p_button_work->p_glb;
	ZKN_SORTSEARCHSUB_WORK* p_subwork = p_button_work->p_work;

	// ボタンイベント格納
	p_subwork->button_event_sub[ button_no ] = event;
	
	switch( event ){
	case BMN_EVENT_HOLD:
		p_subwork->do_flag_select = button_no;
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	名前画面
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubButtonMakeName( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb, int heap )
{
	int i, j;
	int x, y;
	// テーブル作成
	p_work->hit_tbl_sub = sys_AllocMemory( heap, sizeof(TP_HIT_TBL) * ZKN_SORTSEARCHSUB_BUTTON_NAME_NUM );

	// 各座標異OAMを作成する
	for( i=0; i<5; i++ ){
		y = ZKN_SORTSEARCHSUB_BUTTON_00_Y + (i * (ZKN_SORTSEARCHSUB_BUTTON_01_Y - ZKN_SORTSEARCHSUB_BUTTON_00_Y));
		for( j=0; j<2; j++ ){
			x = ZKN_SORTSEARCHSUB_BUTTONDEF_00_X + (j * (ZKN_SORTSEARCHSUB_BUTTONDEF_01_X - ZKN_SORTSEARCHSUB_BUTTONDEF_00_X));

			// テーブルデータ設定
			ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl_sub[ (i*2)+j ],
					y - (ZKN_SORTSEARCHSUB_BUTTON_SIZY/2),
					y + (ZKN_SORTSEARCHSUB_BUTTON_SIZY/2),
					x - (ZKN_SORTSEARCHSUB_BUTTON_ACTION_SIZX/2),
					x + (ZKN_SORTSEARCHSUB_BUTTON_ACTION_SIZX/2) );
		}
	}

	p_work->button_work.p_glb = p_glb;
	p_work->button_work.p_work = p_work;

	// ボタンマネージャ作成
	p_work->p_button_man_sub = BMN_Create( 
			p_work->hit_tbl_sub,
			ZKN_SORTSEARCHSUB_BUTTON_NAME_NUM,
			ZknSortSearchSubButtonCallBackName,
			&p_work->button_work,
			heap );
}
static void ZknSortSearchSubButtonMoveName( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb )
{
	int i;
	
	// 放されたら全てのボタンが元の絵に戻る
	for( i = 0; i < ZKN_SORTSEARCHSUB_BUTTON_NAME_NUM; i++ ){
		p_work->button_event_sub[ i ] = BMN_EVENT_SLIDEOUT;
	}
	
	BMN_Main( p_work->p_button_man_sub );

	switch( ZKN_SortSearchAplNameTypeGet( p_glb->p_main_apl ) ){
	case ZKN_POKELIST_SEARCH_NAME_A:
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NAME_A ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NAME_A ] = BMN_EVENT_RELEASE;
		}
		break;
		
	case ZKN_POKELIST_SEARCH_NAME_KA:
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NAME_KA ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NAME_KA ] = BMN_EVENT_RELEASE;
		}
		break;
		
	case ZKN_POKELIST_SEARCH_NAME_SA:
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NAME_SA ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NAME_SA ] = BMN_EVENT_RELEASE;
		}
		break;
		
	case ZKN_POKELIST_SEARCH_NAME_TA:
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NAME_TA ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NAME_TA ] = BMN_EVENT_RELEASE;
		}
		break;
		
	case ZKN_POKELIST_SEARCH_NAME_NA:
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NAME_NA ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NAME_NA ] = BMN_EVENT_RELEASE;
		}
		break;
		
	case ZKN_POKELIST_SEARCH_NAME_HA:
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NAME_HA ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NAME_HA ] = BMN_EVENT_RELEASE;
		}
		break;
		
	case ZKN_POKELIST_SEARCH_NAME_MA:
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NAME_MA ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NAME_MA ] = BMN_EVENT_RELEASE;
		}
		break;
		
	case ZKN_POKELIST_SEARCH_NAME_RA:
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NAME_RA ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NAME_RA ] = BMN_EVENT_RELEASE;
		}
		break;
		
	case ZKN_POKELIST_SEARCH_NAME_YAWA:
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NAME_YAWA ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_NAME_YAWA ] = BMN_EVENT_RELEASE;
		}
		break;

	default:
		break;
	}
}
static void ZknSortSearchSubButtonCallBackName( u32 button_no, u32 event, void* p_work )
{
	ZKN_SORTSEARCHSUB_BUTTON_WORK* p_button_work = p_work;
	ZKN_SORTSEARCHSUB_GLB* p_glb = p_button_work->p_glb;
	ZKN_SORTSEARCHSUB_WORK* p_subwork = p_button_work->p_work;

	// ボタンイベント格納
	p_subwork->button_event_sub[ button_no ] = event;
	
	switch( event ){
	case BMN_EVENT_HOLD:
		p_subwork->do_flag_select = button_no;
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ﾀｲﾌﾟ1画面
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubButtonMakeType1( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb, int heap )
{
	int i, j;
	int x, y;
	// テーブル作成
	p_work->hit_tbl_sub = sys_AllocMemory( heap, sizeof(TP_HIT_TBL) * ZKN_SORTSEARCHSUB_BUTTON_TYPE1_NUM );

	// 各座標異OAMを作成する
	for( i=0; i<5; i++ ){
		y = ZKN_SORTSEARCHSUB_BUTTON_00_Y + (i * (ZKN_SORTSEARCHSUB_BUTTON_01_Y - ZKN_SORTSEARCHSUB_BUTTON_00_Y));
		for( j=0; j<2; j++ ){
			x = ZKN_SORTSEARCHSUB_BUTTONDEF_00_X + (j * (ZKN_SORTSEARCHSUB_BUTTONDEF_01_X - ZKN_SORTSEARCHSUB_BUTTONDEF_00_X));

			// テーブルデータ設定
			ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl_sub[ (i*2)+j ],
					y - (ZKN_SORTSEARCHSUB_BUTTON_SIZY/2),
					y + (ZKN_SORTSEARCHSUB_BUTTON_SIZY/2),
					x - (ZKN_SORTSEARCHSUB_BUTTON_ACTION_SIZX/2),
					x + (ZKN_SORTSEARCHSUB_BUTTON_ACTION_SIZX/2) );
		}
	}
	
	// ページ送りボタン
	y = ZKN_SORTSEARCHSUB_BUTTON_05_Y;
	x = ZKN_SORTSEARCHSUB_BUTTON_TYPE1_TYPE2_X;
	// テーブルデータ設定
	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE1_TYPE2 ],
			y - (ZKN_SORTSEARCHSUB_BUTTON_PAGE_SIZY/2),
			y + (ZKN_SORTSEARCHSUB_BUTTON_PAGE_SIZY/2),
			x - (ZKN_SORTSEARCHSUB_BUTTON_PAGE_SIZX/2),
			x + (ZKN_SORTSEARCHSUB_BUTTON_PAGE_SIZX/2) );

	p_work->button_work.p_glb = p_glb;
	p_work->button_work.p_work = p_work;

	// ボタンマネージャ作成
	p_work->p_button_man_sub = BMN_Create( 
			p_work->hit_tbl_sub,
			ZKN_SORTSEARCHSUB_BUTTON_TYPE1_NUM,
			ZknSortSearchSubButtonCallBackType1,
			&p_work->button_work,
			heap );
}
static void ZknSortSearchSubButtonMoveType1( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb )
{
	int i;
	
	// 放されたら全てのボタンが元の絵に戻る
	for( i = 0; i < ZKN_SORTSEARCHSUB_BUTTON_TYPE1_NUM; i++ ){
		p_work->button_event_sub[ i ] = BMN_EVENT_SLIDEOUT;
	}
	
	BMN_Main( p_work->p_button_man_sub );

	// 選択中の項目を押しっぱなしに
	ZknSortSearchSubButtonSelectSetType1( p_work, ZKN_SortSearchAplTypeTypeGet( p_glb->p_main_apl, ZKN_SORTSEARCH_TYPE1 ) );
	ZknSortSearchSubButtonSelectSetType1( p_work, ZKN_SortSearchAplTypeTypeGet( p_glb->p_main_apl, ZKN_SORTSEARCH_TYPE2 ) );

}
static void ZknSortSearchSubButtonSelectSetType1( ZKN_SORTSEARCHSUB_WORK* p_work, int type )
{
	switch( type ){
	case ZKN_POKELIST_SEARCH_TYPE_BATTLE:	
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE1_BATTLE ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE1_BATTLE ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_POKELIST_SEARCH_TYPE_JIMEN:	
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE1_JIMEN ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE1_JIMEN ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_POKELIST_SEARCH_TYPE_IWA:		
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE1_IWA ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE1_IWA ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_POKELIST_SEARCH_TYPE_GHOST:	
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE1_GHOST ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE1_GHOST ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_POKELIST_SEARCH_TYPE_KUSA:	
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE1_KUSA ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE1_KUSA ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_POKELIST_SEARCH_TYPE_ELECTRIC:
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE1_ELEC ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE1_ELEC ] = BMN_EVENT_RELEASE;
			}
		break;
	case ZKN_POKELIST_SEARCH_TYPE_SP:		
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE1_SP ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE1_SP ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_POKELIST_SEARCH_TYPE_KOORI:	
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE1_KOORI ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE1_KOORI ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_POKELIST_SEARCH_TYPE_AKU:	
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE1_AKU ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE1_AKU ] = BMN_EVENT_RELEASE;
		}
		break;
	default:
		break;
	}
}
static void ZknSortSearchSubButtonCallBackType1( u32 button_no, u32 event, void* p_work )
{
	ZKN_SORTSEARCHSUB_BUTTON_WORK* p_button_work = p_work;
	ZKN_SORTSEARCHSUB_GLB* p_glb = p_button_work->p_glb;
	ZKN_SORTSEARCHSUB_WORK* p_subwork = p_button_work->p_work;

	// ボタンイベント格納
	p_subwork->button_event_sub[ button_no ] = event;

	switch( event ){
	case BMN_EVENT_HOLD:
		if( p_subwork->tp_no_touch == FALSE ){
			p_subwork->do_flag_select = button_no;
			p_subwork->tp_no_touch = TRUE;
		}
		break;

	default:
		p_subwork->tp_no_touch = FALSE;
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ﾀｲﾌﾟ2画面
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubButtonMakeType2( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb, int heap )
{
	int i, j;
	int x, y;
	// テーブル作成
	p_work->hit_tbl_sub = sys_AllocMemory( heap, sizeof(TP_HIT_TBL) * ZKN_SORTSEARCHSUB_BUTTON_TYPE2_NUM );

	// 各座標異OAMを作成する
	for( i=0; i<4; i++ ){
		y = ZKN_SORTSEARCHSUB_BUTTON_00_Y + (i * (ZKN_SORTSEARCHSUB_BUTTON_01_Y - ZKN_SORTSEARCHSUB_BUTTON_00_Y));
		for( j=0; j<2; j++ ){
			x = ZKN_SORTSEARCHSUB_BUTTONDEF_00_X + (j * (ZKN_SORTSEARCHSUB_BUTTONDEF_01_X - ZKN_SORTSEARCHSUB_BUTTONDEF_00_X));

			// テーブルデータ設定
			ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl_sub[ (i*2)+j ],
					y - (ZKN_SORTSEARCHSUB_BUTTON_SIZY/2),
					y + (ZKN_SORTSEARCHSUB_BUTTON_SIZY/2),
					x - (ZKN_SORTSEARCHSUB_BUTTON_ACTION_SIZX/2),
					x + (ZKN_SORTSEARCHSUB_BUTTON_ACTION_SIZX/2) );
		}
	}

	// ーーーーーボタン
	y = ZKN_SORTSEARCHSUB_BUTTON_04_Y;
	x = ZKN_SORTSEARCHSUB_BUTTONDEF_01_X;
	// テーブルデータ設定
	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE2_NONE ],
			y - (ZKN_SORTSEARCHSUB_BUTTON_SIZY/2),
			y + (ZKN_SORTSEARCHSUB_BUTTON_SIZY/2),
			x - (ZKN_SORTSEARCHSUB_BUTTON_ACTION_SIZX/2),
			x + (ZKN_SORTSEARCHSUB_BUTTON_ACTION_SIZX/2) );
	
	// ページ送りボタン
	y = ZKN_SORTSEARCHSUB_BUTTON_05_Y;
	x = ZKN_SORTSEARCHSUB_BUTTON_TYPE2_TYPE1_X;
	// テーブルデータ設定
	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE2_TYPE1 ],
			y - (ZKN_SORTSEARCHSUB_BUTTON_PAGE_SIZY/2),
			y + (ZKN_SORTSEARCHSUB_BUTTON_PAGE_SIZY/2),
			x - (ZKN_SORTSEARCHSUB_BUTTON_PAGE_SIZX/2),
			x + (ZKN_SORTSEARCHSUB_BUTTON_PAGE_SIZX/2) );


	p_work->button_work.p_glb = p_glb;
	p_work->button_work.p_work = p_work;

	// ボタンマネージャ作成
	p_work->p_button_man_sub = BMN_Create( 
			p_work->hit_tbl_sub,
			ZKN_SORTSEARCHSUB_BUTTON_TYPE2_NUM,
			ZknSortSearchSubButtonCallBackType2,
			&p_work->button_work,
			heap );
}
static void ZknSortSearchSubButtonMoveType2( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb )
{
	int i;
	
	// 放されたら全てのボタンが元の絵に戻る
	for( i = 0; i < ZKN_SORTSEARCHSUB_BUTTON_TYPE2_NUM; i++ ){
		p_work->button_event_sub[ i ] = BMN_EVENT_SLIDEOUT;
	}
	
	BMN_Main( p_work->p_button_man_sub );

	// 選択中の項目を押しっぱなしに
	ZknSortSearchSubButtonSelectSetType2( p_work, ZKN_SortSearchAplTypeTypeGet( p_glb->p_main_apl, ZKN_SORTSEARCH_TYPE1 ) );
	ZknSortSearchSubButtonSelectSetType2( p_work, ZKN_SortSearchAplTypeTypeGet( p_glb->p_main_apl, ZKN_SORTSEARCH_TYPE2 ) );
}
static void ZknSortSearchSubButtonCallBackType2( u32 button_no, u32 event, void* p_work )
{
	ZKN_SORTSEARCHSUB_BUTTON_WORK* p_button_work = p_work;
	ZKN_SORTSEARCHSUB_GLB* p_glb = p_button_work->p_glb;
	ZKN_SORTSEARCHSUB_WORK* p_subwork = p_button_work->p_work;

	// ボタンイベント格納
	p_subwork->button_event_sub[ button_no ] = event;
	
	switch( event ){
	case BMN_EVENT_HOLD:
		if( p_subwork->tp_no_touch == FALSE ){
			p_subwork->do_flag_select = button_no;
			p_subwork->tp_no_touch = TRUE;
		}
		break;

	default:
		p_subwork->tp_no_touch = FALSE;
		break;
	}
}
static void ZknSortSearchSubButtonSelectSetType2( ZKN_SORTSEARCHSUB_WORK* p_work, int type )
{
	switch( type ){
	case ZKN_POKELIST_SEARCH_TYPE_NORMAL:
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE2_NORMAL ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE2_NORMAL ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_POKELIST_SEARCH_TYPE_HIKOU:	
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE2_HIKOR ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE2_HIKOR ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_POKELIST_SEARCH_TYPE_POISON:	
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE2_DOKU ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE2_DOKU ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_POKELIST_SEARCH_TYPE_MUSHI:	
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE2_MUSHI ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE2_MUSHI ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_POKELIST_SEARCH_TYPE_METAL:	
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE2_HAGANE ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE2_HAGANE ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_POKELIST_SEARCH_TYPE_FIRE:	
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE2_FIRE ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE2_FIRE ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_POKELIST_SEARCH_TYPE_WATER:	
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE2_WATER ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE2_WATER ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_POKELIST_SEARCH_TYPE_DRAGON:	
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE2_DRAGON ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE2_DRAGON ] = BMN_EVENT_RELEASE;
		}
		break;
	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	かたち画面
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubButtonMakeForm( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb, int heap )
{
	int i, j;
	int x, y;
	// テーブル作成
	p_work->hit_tbl_sub = sys_AllocMemory( heap, sizeof(TP_HIT_TBL) * ZKN_SORTSEARCHSUB_BUTTON_FORM_NUM );

	// 各座標異OAMを作成する
	for( i=0; i<5; i++ ){
		y = ZKN_SORTSEARCHSUB_BUTTON_00_Y + (i * (ZKN_SORTSEARCHSUB_BUTTON_01_Y - ZKN_SORTSEARCHSUB_BUTTON_00_Y));
		for( j=0; j<3; j++ ){
			x = ZKN_SORTSEARCHSUB_BUTTON_FORM_DEF_X + (j * ZKN_SORTSEARCHSUB_BUTTON_FORM_OFS_X);

			// テーブルデータ設定
			ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl_sub[ (i*3)+j ],
					y - (ZKN_SORTSEARCHSUB_BUTTON_FORM_SIZY/2),
					y + (ZKN_SORTSEARCHSUB_BUTTON_FORM_SIZY/2),
					x - (ZKN_SORTSEARCHSUB_BUTTON_FORM_SIZX/2),
					x + (ZKN_SORTSEARCHSUB_BUTTON_FORM_SIZX/2) );
		}
	}
	
	p_work->button_work.p_glb = p_glb;
	p_work->button_work.p_work = p_work;

	// ボタンマネージャ作成
	p_work->p_button_man_sub = BMN_Create( 
			p_work->hit_tbl_sub,
			ZKN_SORTSEARCHSUB_BUTTON_FORM_NUM,
			ZknSortSearchSubButtonCallBackForm,
			&p_work->button_work,
			heap );
}
static void ZknSortSearchSubButtonMoveForm( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb )
{
	int i;
	
	// 放されたら全てのボタンが元の絵に戻る
	for( i = 0; i < ZKN_SORTSEARCHSUB_BUTTON_FORM_NUM; i++ ){
		p_work->button_event_sub[ i ] = BMN_EVENT_SLIDEOUT;
	}
	
	BMN_Main( p_work->p_button_man_sub );

	switch( ZKN_SortSearchAplFormTypeGet( p_glb->p_main_apl ) ){
	case ZKN_POKELIST_SEARCH_FORM_FOUR_LEGS:
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_FORM_FOUR_LEGS ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_FORM_FOUR_LEGS ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_POKELIST_SEARCH_FORM_TWO_LEGS:
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_FORM_TWO_LEGS ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_FORM_TWO_LEGS ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_POKELIST_SEARCH_FORM_TAIL:
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_FORM_TAIL ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_FORM_TAIL ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_POKELIST_SEARCH_FORM_HARABAI:
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_FORM_HARABAI ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_FORM_HARABAI ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_POKELIST_SEARCH_FORM_FOUR_WING:
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_FORM_FOUR_WING ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_FORM_FOUR_WING ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_POKELIST_SEARCH_FORM_TWO_WING:
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_FORM_TWO_WING ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_FORM_TWO_WING ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_POKELIST_SEARCH_FORM_HAITSUKUBARI:
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_FORM_HAITSUKUBARI ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_FORM_HAITSUKUBARI ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_POKELIST_SEARCH_FORM_STRAIGHT:
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_FORM_STRAIGHT ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_FORM_STRAIGHT ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_POKELIST_SEARCH_FORM_ARM:
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_FORM_ARM ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_FORM_ARM ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_POKELIST_SEARCH_FORM_LEGS:
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_FORM_LEGS ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_FORM_LEGS ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_POKELIST_SEARCH_FORM_MANY_LEGS:
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_FORM_MANY_LEGS ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_FORM_MANY_LEGS ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_POKELIST_SEARCH_FORM_WATER:
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_FORM_WATER ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_FORM_WATER ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_POKELIST_SEARCH_FORM_CIRCLE:
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_FORM_CIRCLE ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_FORM_CIRCLE ] = BMN_EVENT_RELEASE;
		}
		break;
	case ZKN_POKELIST_SEARCH_FORM_COMP:
		if( p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_FORM_COMP ] != BMN_EVENT_HOLD ){
			p_work->button_event_sub[ ZKN_SORTSEARCHSUB_BUTTON_FORM_COMP ] = BMN_EVENT_RELEASE;
		}
		break;

	default:
		break;
	}
}
static void ZknSortSearchSubButtonCallBackForm( u32 button_no, u32 event, void* p_work )
{
	ZKN_SORTSEARCHSUB_BUTTON_WORK* p_button_work = p_work;
	ZKN_SORTSEARCHSUB_GLB* p_glb = p_button_work->p_glb;
	ZKN_SORTSEARCHSUB_WORK* p_subwork = p_button_work->p_work;

	// ボタンイベント格納
	p_subwork->button_event_sub[ button_no ] = event;
	
	switch( event ){
	case BMN_EVENT_HOLD:
		p_subwork->do_flag_select = button_no;
		break;

	default:
		break;
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	カーソルデータ作成
 *	
 *	@param	p_work	ワーク
 *	@param	heap	ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------

//----------------------------------------------------------------------------
/**
 *	@brief	カーソル動作
 *
 *	@param	p_work	ワーク
 *	@param	p_glb	グローバル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
// 共通ボタン
static void ZknSortSearchSubCursorCommonSet( ZKN_CURSOR_ONEDATA* p_data, int id )
{
	int x, y;
	int size_x, size_y;

	switch( id ){
	case ZKN_SORTSEARCHSUB_CURSOR_ID_BACK:
		x = ZKN_SORTSEARCHSUB_BUTTON_BACK_X;
		y = ZKN_SORTSEARCHSUB_BUTTON_BACK_Y;
		size_x = ZKN_SORTSEARCHSUB_CURSOR_BACK_SIZX;
		size_y = ZKN_SORTSEARCHSUB_CURSOR_BACK_SIZY;
		break;
		
	case ZKN_SORTSEARCHSUB_CURSOR_ID_NARABI:
		x = ZKN_SORTSEARCHSUB_BUTTON_X;
		y = ZKN_SORTSEARCHSUB_BUTTON_NARABI_Y;
		size_x = ZKN_SORTSEARCHSUB_CURSOR_SIZX;
		size_y = ZKN_SORTSEARCHSUB_CURSOR_SIZY;
		break;
		
	case ZKN_SORTSEARCHSUB_CURSOR_ID_NAME:
		x = ZKN_SORTSEARCHSUB_BUTTON_X;
		y = ZKN_SORTSEARCHSUB_BUTTON_NAME_Y;
		size_x = ZKN_SORTSEARCHSUB_CURSOR_SIZX;
		size_y = ZKN_SORTSEARCHSUB_CURSOR_SIZY;
		break;
		
	case ZKN_SORTSEARCHSUB_CURSOR_ID_TYPE:
		x = ZKN_SORTSEARCHSUB_BUTTON_X;
		y = ZKN_SORTSEARCHSUB_BUTTON_TYPE_Y;
		size_x = ZKN_SORTSEARCHSUB_CURSOR_SIZX;
		size_y = ZKN_SORTSEARCHSUB_CURSOR_SIZY;
		break;
		
	case ZKN_SORTSEARCHSUB_CURSOR_ID_FORM:
		x = ZKN_SORTSEARCHSUB_BUTTON_X;
		y = ZKN_SORTSEARCHSUB_BUTTON_FORM_Y;
		size_x = ZKN_SORTSEARCHSUB_CURSOR_SIZX;
		size_y = ZKN_SORTSEARCHSUB_CURSOR_SIZY;
		break;
		
	case ZKN_SORTSEARCHSUB_CURSOR_ID_ACTION:
		x = ZKN_SORTSEARCHSUB_BUTTON_ACTION_X;
		y = ZKN_SORTSEARCHSUB_BUTTON_ACTION_Y;
		size_x = ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZX;
		size_y = ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZY;
		break;
	}
	// カーソル移動データ設定
	ZKN_CURSOR_SetOneData( 
			p_data,
			x, 
			y,
			size_x,
			size_y,
			ZKN_CURSOR_MOVE_NORMAL,
			ZKN_CURSOR_MOVE_NORMAL,
			id );

}
//----------------------------------------------------------------------------
/**
 *	@brief	共通ボタン動作
 *
 *	@param	p_work	ﾃﾞｰﾀワーク
 *	@param	p_glb	ﾃﾞｰﾀグローバル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubCursorMoveCommon( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb )
{
	// カーソル位置の機能を実行
	// 共通部分が押された処理は一緒
	if( sys.cont & PAD_BUTTON_A ){

		if( p_work->cursor_no_touch == FALSE ){

			switch( ZKN_CURSOR_GetContID( p_work->p_cursor ) ){
			case ZKN_SORTSEARCHSUB_CURSOR_ID_NARABI:
				p_work->do_flag_common = ZKN_SORTSEARCHSUB_BUTTON_NARABI;
				p_work->button_event[ p_work->do_flag_common ] = BMN_EVENT_HOLD;
				break;
				
			case ZKN_SORTSEARCHSUB_CURSOR_ID_NAME:
				p_work->do_flag_common = ZKN_SORTSEARCHSUB_BUTTON_NAME;
				p_work->button_event[ p_work->do_flag_common ] = BMN_EVENT_HOLD;
				break;
				
			case ZKN_SORTSEARCHSUB_CURSOR_ID_TYPE:
				p_work->do_flag_common = ZKN_SORTSEARCHSUB_BUTTON_TYPE;
				p_work->button_event[ p_work->do_flag_common ] = BMN_EVENT_HOLD;
				break;
				
			case ZKN_SORTSEARCHSUB_CURSOR_ID_FORM:
				p_work->do_flag_common = ZKN_SORTSEARCHSUB_BUTTON_FORM;
				p_work->button_event[ p_work->do_flag_common ] = BMN_EVENT_HOLD;
				break;

			case ZKN_SORTSEARCHSUB_CURSOR_ID_ACTION:
				p_work->do_flag_common = ZKN_SORTSEARCHSUB_BUTTON_ACTION;
				p_work->button_event[ p_work->do_flag_common ] = BMN_EVENT_HOLD;
				break;
				
			case ZKN_SORTSEARCHSUB_CURSOR_ID_BACK:
				p_work->do_flag_common = ZKN_SORTSEARCHSUB_BUTTON_BACK;
				p_work->button_event[ p_work->do_flag_common ] = BMN_EVENT_HOLD;
				break;

			default:
				break;
			}

			p_work->req_count ++;
		}

	}else{
		p_work->req_count = 0;

		p_work->cursor_no_touch = FALSE;	// PAD_BUTTON_Aをはなした
	}

	// Bボタンでポケリストに戻る
	if(sys.trg & PAD_BUTTON_B){
		p_work->do_flag_common = ZKN_SORTSEARCHSUB_BUTTON_BACK;
		p_work->button_event[ p_work->do_flag_common ] = BMN_EVENT_HOLD;
	}

}

// ｿｰﾄ画面
static void ZknSortSearchSubCursorMakeSort( ZKN_SORTSEARCHSUB_WORK* p_work, int heap )
{
	int i, j;
	int x, y;
	int move_type;
	int id;

	p_work->p_cursor_tbl = sys_AllocMemory( heap, sizeof(ZKN_CURSOR_ONEDATA) * (ZKN_SORTSEARCHSUB_CURSOR_NARABI_MAX_X * ZKN_SORTSEARCHSUB_CURSOR_MAX_Y) );

	//　カーソルﾃﾞｰﾀ作成
	for( i=0; i<ZKN_SORTSEARCHSUB_CURSOR_MAX_Y; i++ ){
		y = ZKN_SORTSEARCHSUB_BUTTON_00_Y + (i * (ZKN_SORTSEARCHSUB_BUTTON_01_Y - ZKN_SORTSEARCHSUB_BUTTON_00_Y));
		
		for( j=0; j<ZKN_SORTSEARCHSUB_CURSOR_NARABI_MAX_X; j++ ){	
		
			x = ZKN_SORTSEARCHSUB_BUTTONDEF_00_X + (j * (ZKN_SORTSEARCHSUB_BUTTONDEF_01_X - ZKN_SORTSEARCHSUB_BUTTONDEF_00_X));
			id = ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_00 + (i * (ZKN_SORTSEARCHSUB_CURSOR_NARABI_MAX_X - 1)) + j;

			// 行により格納データが変更する
			switch( i ){
			case ZKN_SORTSEARCHSUB_BUTTON_BACK:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_NARABI_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_BACK;
				}else{
					move_type = ZKN_CURSOR_MOVE_STOP;
				}
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_NARABI:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_NARABI_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_NARABI;
				}else{
					move_type = ZKN_CURSOR_MOVE_NORMAL;
				}
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_NAME:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_NARABI_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_NAME;
				}else{
					move_type = ZKN_CURSOR_MOVE_NORMAL;
				}
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_TYPE:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_NARABI_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_TYPE;
				}else{
					move_type = ZKN_CURSOR_MOVE_NORMAL;
				}
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_FORM:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_NARABI_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_FORM;
				}else{
					move_type = ZKN_CURSOR_MOVE_STOP;
				}
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_ACTION:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_NARABI_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_ACTION;
				}else{
					move_type = ZKN_CURSOR_MOVE_STOP;
				}
				break;
			}

			// 選択ﾀｲﾌﾟボタン
			if( j < (ZKN_SORTSEARCHSUB_CURSOR_NARABI_MAX_X - 1) ){
				// カーソル移動データ設定
				ZKN_CURSOR_SetOneData( 
						&p_work->p_cursor_tbl[ (i*ZKN_SORTSEARCHSUB_CURSOR_NARABI_MAX_X) + j ],
						x, y,
						ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZX, 
						ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZY,
						move_type, move_type,
						id );
			}else{
				// 共用ボタン
				ZknSortSearchSubCursorCommonSet( 
						&p_work->p_cursor_tbl[ (i*ZKN_SORTSEARCHSUB_CURSOR_NARABI_MAX_X) + j ],
						id );
			}
		}
	}


	// カーソルデータ設定
	p_work->p_cursor = ZKN_CURSOR_Alloc( heap );
	ZKN_CURSOR_Init( p_work->p_cursor, p_work->p_cursor_tbl,
			ZKN_SORTSEARCHSUB_CURSOR_NARABI_MAX_X,
			ZKN_SORTSEARCHSUB_CURSOR_MAX_Y );
}
static void ZknSortSearchSubCursorMoveSort( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb )
{
	if( sys.cont & PAD_BUTTON_A ){

		if( p_work->cursor_no_touch == FALSE ){

			switch( ZKN_CURSOR_GetContID( p_work->p_cursor ) ){
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_02:		// 0と1はダミー
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_NARABI_NUMBER;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_03:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_NARABI_AIUEO;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_04:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_NARABI_HEAVY;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_05:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_NARABI_LIGHT;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_06:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_NARABI_TALL;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_07:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_NARABI_SHORT;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
				
			default:
				break;
			}
		}

	}else{
		p_work->cursor_no_touch = FALSE;	// PAD_BUTTON_Aをはなした
	}
}

// 名前画面
static void ZknSortSearchSubCursorMakeName( ZKN_SORTSEARCHSUB_WORK* p_work, int heap )
{
	int i, j;
	int x, y;
	int move_type;
	int id;
	p_work->p_cursor_tbl = sys_AllocMemory( heap, sizeof(ZKN_CURSOR_ONEDATA) * (ZKN_SORTSEARCHSUB_CURSOR_NAME_MAX_X * ZKN_SORTSEARCHSUB_CURSOR_MAX_Y) );

	//　カーソルﾃﾞｰﾀ作成
	for( i=0; i<ZKN_SORTSEARCHSUB_CURSOR_MAX_Y; i++ ){
		y = ZKN_SORTSEARCHSUB_BUTTON_00_Y + (i * (ZKN_SORTSEARCHSUB_BUTTON_01_Y - ZKN_SORTSEARCHSUB_BUTTON_00_Y));
		
		for( j=0; j<ZKN_SORTSEARCHSUB_CURSOR_NAME_MAX_X; j++ ){	
		
			x = ZKN_SORTSEARCHSUB_BUTTONDEF_00_X + (j * (ZKN_SORTSEARCHSUB_BUTTONDEF_01_X - ZKN_SORTSEARCHSUB_BUTTONDEF_00_X));
			id = ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_00 + (i * 2) + j;

			// 行により格納データが変更する
			switch( i ){
			case ZKN_SORTSEARCHSUB_BUTTON_BACK:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_NAME_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_BACK;
				}else{
					move_type = ZKN_CURSOR_MOVE_NORMAL;
				}
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_NARABI:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_NAME_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_NARABI;
				}else{
					move_type = ZKN_CURSOR_MOVE_NORMAL;
				}
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_NAME:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_NAME_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_NAME;
				}else{
					move_type = ZKN_CURSOR_MOVE_NORMAL;
				}
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_TYPE:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_NAME_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_TYPE;
				}else{
					move_type = ZKN_CURSOR_MOVE_NORMAL;
				}
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_FORM:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_NAME_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_FORM;
				}else{
					move_type = ZKN_CURSOR_MOVE_NORMAL;
				}
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_ACTION:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_NAME_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_ACTION;
				}else{
					move_type = ZKN_CURSOR_MOVE_STOP;
				}
				break;
			}

			// 選択ﾀｲﾌﾟボタン
			if( j < (ZKN_SORTSEARCHSUB_CURSOR_NAME_MAX_X - 1) ){
				// カーソル移動データ設定
				ZKN_CURSOR_SetOneData( 
						&p_work->p_cursor_tbl[ (i*ZKN_SORTSEARCHSUB_CURSOR_NAME_MAX_X) + j ],
						x, y,
						ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZX, 
						ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZY,
						move_type, move_type,
						id );
			}else{
				// 共用ボタン
				ZknSortSearchSubCursorCommonSet( 
						&p_work->p_cursor_tbl[ (i*ZKN_SORTSEARCHSUB_CURSOR_NAME_MAX_X) + j ],
						id );
			}
		}
	}

	// カーソルデータ設定
	p_work->p_cursor = ZKN_CURSOR_Alloc( heap );
	ZKN_CURSOR_Init( p_work->p_cursor, p_work->p_cursor_tbl,
			ZKN_SORTSEARCHSUB_CURSOR_NAME_MAX_X,
			ZKN_SORTSEARCHSUB_CURSOR_MAX_Y );
}
static void ZknSortSearchSubCursorMoveName( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb )
{
	if( sys.cont & PAD_BUTTON_A ){
		if( p_work->cursor_no_touch == FALSE ){

			switch( ZKN_CURSOR_GetContID( p_work->p_cursor ) ){
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_00:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_NAME_A;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_01:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_NAME_HA;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_02:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_NAME_KA;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_03:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_NAME_MA;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_04:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_NAME_SA;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_05:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_NAME_RA;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_06:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_NAME_TA;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_07:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_NAME_YAWA;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_08:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_NAME_NA;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_09:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_NAME_NONE;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			default:
				break;
			}
		}

	}else{

		p_work->cursor_no_touch = FALSE;
	}
}

// ﾀｲﾌﾟ1画面
static void ZknSortSearchSubCursorMakeType1( ZKN_SORTSEARCHSUB_WORK* p_work, int heap )
{
	int i, j;
	int x, y;
	int size_x, size_y;
	int move_type;
	int id;
	p_work->p_cursor_tbl = sys_AllocMemory( heap, sizeof(ZKN_CURSOR_ONEDATA) * (ZKN_SORTSEARCHSUB_CURSOR_TYPE1_MAX_X * ZKN_SORTSEARCHSUB_CURSOR_MAX_Y) );

	//　カーソルﾃﾞｰﾀ作成
	for( i=0; i<ZKN_SORTSEARCHSUB_CURSOR_MAX_Y; i++ ){
		y = ZKN_SORTSEARCHSUB_BUTTON_00_Y + (i * (ZKN_SORTSEARCHSUB_BUTTON_01_Y - ZKN_SORTSEARCHSUB_BUTTON_00_Y));
		
		for( j=0; j<ZKN_SORTSEARCHSUB_CURSOR_TYPE1_MAX_X; j++ ){	
		
			x = ZKN_SORTSEARCHSUB_BUTTONDEF_00_X + (j * (ZKN_SORTSEARCHSUB_BUTTONDEF_01_X - ZKN_SORTSEARCHSUB_BUTTONDEF_00_X));
			id = ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_00 + (i * 2) + j;

			// 行により格納データが変更する
			switch( i ){
			case ZKN_SORTSEARCHSUB_BUTTON_BACK:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_TYPE1_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_BACK;
				}else{
					move_type = ZKN_CURSOR_MOVE_NORMAL;
					size_x = ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZX;
					size_y = ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZY;
				}
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_NARABI:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_TYPE1_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_NARABI;
				}else{
					move_type = ZKN_CURSOR_MOVE_NORMAL;
					size_x = ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZX;
					size_y = ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZY;
				}
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_NAME:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_TYPE1_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_NAME;
				}else{
					move_type = ZKN_CURSOR_MOVE_NORMAL;
					size_x = ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZX;
					size_y = ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZY;
				}
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_TYPE:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_TYPE1_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_TYPE;
				}else{
					move_type = ZKN_CURSOR_MOVE_NORMAL;
					size_x = ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZX;
					size_y = ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZY;
				}
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_FORM:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_TYPE1_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_FORM;
				}else{
					move_type = ZKN_CURSOR_MOVE_NORMAL;
					size_x = ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZX;
					size_y = ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZY;
				}
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_ACTION:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_TYPE1_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_ACTION;
				}else{
					if( j == 0 ){
						move_type = ZKN_CURSOR_MOVE_NORMAL;
						size_x = ZKN_SORTSEARCHSUB_CURSOR_PAGE_SIZX;
						size_y = ZKN_SORTSEARCHSUB_CURSOR_PAGE_SIZY;
						x = ZKN_SORTSEARCHSUB_BUTTON_TYPE1_TYPE2_X;	
					}else{
						move_type = ZKN_CURSOR_MOVE_STOP;
						size_x = ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZX;
						size_y = ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZY;
					}
				}
				break;
			}

			// 選択ﾀｲﾌﾟボタン
			if( j < (ZKN_SORTSEARCHSUB_CURSOR_TYPE1_MAX_X - 1) ){
				// カーソル移動データ設定
				ZKN_CURSOR_SetOneData( 
						&p_work->p_cursor_tbl[ (i*ZKN_SORTSEARCHSUB_CURSOR_TYPE1_MAX_X) + j ],
						x, y,
						size_x, 
						size_y,
						move_type, move_type,
						id );
			}else{
				// 共用ボタン
				ZknSortSearchSubCursorCommonSet( 
						&p_work->p_cursor_tbl[ (i*ZKN_SORTSEARCHSUB_CURSOR_TYPE1_MAX_X) + j ],
						id );
			}
		}
	}

	// カーソルデータ設定
	p_work->p_cursor = ZKN_CURSOR_Alloc( heap );
	ZKN_CURSOR_Init( p_work->p_cursor, p_work->p_cursor_tbl,
			ZKN_SORTSEARCHSUB_CURSOR_TYPE1_MAX_X,
			ZKN_SORTSEARCHSUB_CURSOR_MAX_Y );
}
static void ZknSortSearchSubCursorMoveType1( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb )
{
	if( sys.cont & PAD_BUTTON_A ){

		if( p_work->cursor_no_touch == FALSE ){

			switch( ZKN_CURSOR_GetContID( p_work->p_cursor ) ){
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_00:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_TYPE1_AKU;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_01:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_TYPE1_KOORI;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_02:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_TYPE1_IWA;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_03:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_TYPE1_GHOST;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_04:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_TYPE1_SP;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_05:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_TYPE1_JIMEN;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_06:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_TYPE1_BATTLE;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_07:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_TYPE1_ELEC;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_08:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_TYPE1_KUSA;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_09:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_TYPE1_NONE;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				p_work->cursor_no_touch = TRUE;	// 次押しても反応しない
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_10:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_TYPE1_TYPE2;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			default:
				break;
			}
		}

	}else{

		p_work->cursor_no_touch = FALSE;
	}
}

// ﾀｲﾌﾟ2画面
static void ZknSortSearchSubCursorMakeType2( ZKN_SORTSEARCHSUB_WORK* p_work, int heap )
{
	int i, j;
	int x, y;
	int size_x, size_y;
	int move_typex, move_typey;
	int id;
	p_work->p_cursor_tbl = sys_AllocMemory( heap, sizeof(ZKN_CURSOR_ONEDATA) * (ZKN_SORTSEARCHSUB_CURSOR_TYPE2_MAX_X * ZKN_SORTSEARCHSUB_CURSOR_MAX_Y) );

	//　カーソルﾃﾞｰﾀ作成
	for( i=0; i<ZKN_SORTSEARCHSUB_CURSOR_MAX_Y; i++ ){
		y = ZKN_SORTSEARCHSUB_BUTTON_00_Y + (i * (ZKN_SORTSEARCHSUB_BUTTON_01_Y - ZKN_SORTSEARCHSUB_BUTTON_00_Y));
		
		for( j=0; j<ZKN_SORTSEARCHSUB_CURSOR_TYPE2_MAX_X; j++ ){	
		
			x = ZKN_SORTSEARCHSUB_BUTTONDEF_00_X + (j * (ZKN_SORTSEARCHSUB_BUTTONDEF_01_X - ZKN_SORTSEARCHSUB_BUTTONDEF_00_X));
			id = ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_00 + (i * 2) + j;

			// 行により格納データが変更する
			switch( i ){
			case ZKN_SORTSEARCHSUB_BUTTON_BACK:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_TYPE2_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_BACK;
				}else{
					move_typex = ZKN_CURSOR_MOVE_NORMAL;
					move_typey = ZKN_CURSOR_MOVE_NORMAL;
					size_x = ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZX;
					size_y = ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZY;
				}
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_NARABI:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_TYPE2_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_NARABI;
				}else{
					move_typex = ZKN_CURSOR_MOVE_NORMAL;
					move_typey = ZKN_CURSOR_MOVE_NORMAL;
					size_x = ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZX;
					size_y = ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZY;
				}
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_NAME:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_TYPE2_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_NAME;
				}else{
					move_typex = ZKN_CURSOR_MOVE_NORMAL;
					move_typey = ZKN_CURSOR_MOVE_NORMAL;
					size_x = ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZX;
					size_y = ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZY;
				}
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_TYPE:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_TYPE2_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_TYPE;
				}else{
					move_typex = ZKN_CURSOR_MOVE_NORMAL;
					move_typey = ZKN_CURSOR_MOVE_NORMAL;
					size_x = ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZX;
					size_y = ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZY;
				}
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_FORM:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_TYPE2_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_FORM;
				}else{
					if( j==0 ){
						move_typex = ZKN_CURSOR_MOVE_STOP;
						move_typey = ZKN_CURSOR_MOVE_SKIP;
						size_x = ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZX;
						size_y = ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZY;
					}else{
						move_typex = ZKN_CURSOR_MOVE_NORMAL;
						move_typey = ZKN_CURSOR_MOVE_NORMAL;
						size_x = ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZX;
						size_y = ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZY;
					}
				}
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_ACTION:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_TYPE2_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_ACTION;
				}else{
					if( j == 0 ){
						move_typex = ZKN_CURSOR_MOVE_NORMAL;
						move_typey = ZKN_CURSOR_MOVE_NORMAL;
						size_x = ZKN_SORTSEARCHSUB_CURSOR_PAGE_SIZX;
						size_y = ZKN_SORTSEARCHSUB_CURSOR_PAGE_SIZY;
						x = ZKN_SORTSEARCHSUB_BUTTON_TYPE2_TYPE1_X;
					}else{
						move_typex = ZKN_CURSOR_MOVE_STOP;
						move_typey = ZKN_CURSOR_MOVE_STOP;
						size_x = ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZX;
						size_y = ZKN_SORTSEARCHSUB_CURSOR_ACTION_SIZY;
					}
				}
				break;
			}

			// 選択ﾀｲﾌﾟボタン
			if( j < (ZKN_SORTSEARCHSUB_CURSOR_TYPE2_MAX_X - 1) ){
				// カーソル移動データ設定
				ZKN_CURSOR_SetOneData( 
						&p_work->p_cursor_tbl[ (i*ZKN_SORTSEARCHSUB_CURSOR_TYPE2_MAX_X) + j ],
						x, y,
						size_x, 
						size_y,
						move_typex, move_typey,
						id );
			}else{
				// 共用ボタン
				ZknSortSearchSubCursorCommonSet( 
						&p_work->p_cursor_tbl[ (i*ZKN_SORTSEARCHSUB_CURSOR_TYPE2_MAX_X) + j ],
						id );
			}
		}
	}

	// カーソルデータ設定
	p_work->p_cursor = ZKN_CURSOR_Alloc( heap );
	ZKN_CURSOR_Init( p_work->p_cursor, p_work->p_cursor_tbl,
			ZKN_SORTSEARCHSUB_CURSOR_TYPE2_MAX_X,
			ZKN_SORTSEARCHSUB_CURSOR_MAX_Y );
}
static void ZknSortSearchSubCursorMoveType2( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb )
{
	if( sys.cont & PAD_BUTTON_A ){
		if( p_work->cursor_no_touch == FALSE ){

			switch( ZKN_CURSOR_GetContID( p_work->p_cursor ) ){
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_00:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_TYPE2_DOKU;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_01:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_TYPE2_HIKOR;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_02:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_TYPE2_DRAGON;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_03:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_TYPE2_FIRE;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_04:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_TYPE2_NORMAL;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_05:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_TYPE2_WATER;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_06:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_TYPE2_HAGANE;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_07:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_TYPE2_MUSHI;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_09:		// ８はダミー
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_TYPE2_NONE;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				p_work->cursor_no_touch = TRUE;	// 次押しても反応しない
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_10:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_TYPE2_TYPE1;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			default:
				break;
			}
		}

	}else{

		p_work->cursor_no_touch = FALSE;
	}
}

// 形画面
static void ZknSortSearchSubCursorMakeForm( ZKN_SORTSEARCHSUB_WORK* p_work, int heap )
{
	int i, j;
	int x, y;
	int move_type;
	int id;
	p_work->p_cursor_tbl = sys_AllocMemory( heap, sizeof(ZKN_CURSOR_ONEDATA) * (ZKN_SORTSEARCHSUB_CURSOR_FORM_MAX_X * ZKN_SORTSEARCHSUB_CURSOR_MAX_Y) );


	//　カーソルﾃﾞｰﾀ作成
	for( i=0; i<ZKN_SORTSEARCHSUB_CURSOR_MAX_Y; i++ ){
		y = ZKN_SORTSEARCHSUB_BUTTON_00_Y + (i * (ZKN_SORTSEARCHSUB_BUTTON_01_Y - ZKN_SORTSEARCHSUB_BUTTON_00_Y));
		
		for( j=0; j<ZKN_SORTSEARCHSUB_CURSOR_FORM_MAX_X; j++ ){	
		
			x = ZKN_SORTSEARCHSUB_BUTTON_FORM_DEF_X + (j * ZKN_SORTSEARCHSUB_BUTTON_FORM_OFS_X);
			id = ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_00 + (i * (ZKN_SORTSEARCHSUB_CURSOR_FORM_MAX_X - 1)) + j;

			// 行により格納データが変更する
			switch( i ){
			case ZKN_SORTSEARCHSUB_BUTTON_BACK:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_FORM_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_BACK;
				}else{
					move_type = ZKN_CURSOR_MOVE_NORMAL;
				}
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_NARABI:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_FORM_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_NARABI;
				}else{
					move_type = ZKN_CURSOR_MOVE_NORMAL;
				}
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_NAME:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_FORM_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_NAME;
				}else{
					move_type = ZKN_CURSOR_MOVE_NORMAL;
				}
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_TYPE:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_FORM_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_TYPE;
				}else{
					move_type = ZKN_CURSOR_MOVE_NORMAL;
				}
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_FORM:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_FORM_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_FORM;
				}else{
					move_type = ZKN_CURSOR_MOVE_NORMAL;
				}
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_ACTION:
				if( j == (ZKN_SORTSEARCHSUB_CURSOR_FORM_MAX_X - 1) ){
					id = ZKN_SORTSEARCHSUB_CURSOR_ID_ACTION;
				}else{
					move_type = ZKN_CURSOR_MOVE_STOP;
				}
				break;
			}

			// 選択ﾀｲﾌﾟボタン
			if( j < (ZKN_SORTSEARCHSUB_CURSOR_FORM_MAX_X - 1) ){
				// カーソル移動データ設定
				ZKN_CURSOR_SetOneData( 
						&p_work->p_cursor_tbl[ (i*ZKN_SORTSEARCHSUB_CURSOR_FORM_MAX_X) + j ],
						x, y,
						ZKN_SORTSEARCHSUB_CURSOR_FORM_SIZX, 
						ZKN_SORTSEARCHSUB_CURSOR_FORM_SIZY,
						move_type, move_type,
						id );
			}else{
				// 共用ボタン
				ZknSortSearchSubCursorCommonSet( 
						&p_work->p_cursor_tbl[ (i*ZKN_SORTSEARCHSUB_CURSOR_FORM_MAX_X) + j ],
						id );
			}
		}
	}

	// カーソルデータ設定
	p_work->p_cursor = ZKN_CURSOR_Alloc( heap );
	ZKN_CURSOR_Init( p_work->p_cursor, p_work->p_cursor_tbl,
			ZKN_SORTSEARCHSUB_CURSOR_FORM_MAX_X,
			ZKN_SORTSEARCHSUB_CURSOR_MAX_Y );
}
static void ZknSortSearchSubCursorMoveForm( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb )
{
	if( sys.cont & PAD_BUTTON_A ){
		if( p_work->cursor_no_touch == FALSE ){

			switch( ZKN_CURSOR_GetContID( p_work->p_cursor ) ){
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_00:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_FORM_CIRCLE;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_01:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_FORM_HARABAI;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_02:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_FORM_WATER;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_03:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_FORM_ARM;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_04:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_FORM_STRAIGHT;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_05:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_FORM_TAIL;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_06:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_FORM_LEGS;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_07:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_FORM_FOUR_LEGS;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_08:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_FORM_TWO_WING;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_09:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_FORM_MANY_LEGS;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_10:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_FORM_COMP;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_11:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_FORM_TWO_LEGS;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_12:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_FORM_FOUR_WING;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_13:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_FORM_HAITSUKUBARI;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			case ZKN_SORTSEARCHSUB_SURSOR_ID_OTHER_14:
				p_work->do_flag_select = ZKN_SORTSEARCHSUB_BUTTON_FORM_NONE;
				p_work->button_event_sub[ p_work->do_flag_select ] = BMN_EVENT_HOLD;
				break;
			default:
				break;
			}
		}
	}else{
		p_work->cursor_no_touch = FALSE;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	カーソル共通動作
 *
 *	@param	p_work
 *	@param	p_glb 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubCursorMove( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb )
{
	
	if( sys.trg & PAD_KEY_RIGHT ){
		ZKN_CURSOR_Cont( p_work->p_cursor, ZKN_CURSOR_CONT_ADD_X, 1 );
		p_work->cursor_no_touch = TRUE;	// PAD_BUTTON_Aを押しても反応しない
		//		Snd_SePlay( ZKN_SND_SELECT );
	}

	if( sys.trg & PAD_KEY_LEFT ){
		ZKN_CURSOR_Cont( p_work->p_cursor, ZKN_CURSOR_CONT_ADD_X, -1 );
		p_work->cursor_no_touch = TRUE;	// PAD_BUTTON_Aを押しても反応しない
//		Snd_SePlay( ZKN_SND_SELECT );
	}

	if( sys.trg & PAD_KEY_UP ){
		ZKN_CURSOR_Cont( p_work->p_cursor, ZKN_CURSOR_CONT_ADD_Y, -1 );
		p_work->cursor_no_touch = TRUE;	// PAD_BUTTON_Aを押しても反応しない
//		Snd_SePlay( ZKN_SND_SELECT );
	}

	if( sys.trg & PAD_KEY_DOWN ){
		ZKN_CURSOR_Cont( p_work->p_cursor, ZKN_CURSOR_CONT_ADD_Y, 1 );
		p_work->cursor_no_touch = TRUE;	// PAD_BUTTON_Aを押しても反応しない
//		Snd_SePlay( ZKN_SND_SELECT );
	}

	// 共通動作
	ZknSortSearchSubCursorMoveCommon( p_work, p_glb );


	// 選択別動作
	ZknSortSearchSubCursorMoveSub( p_work, p_glb, p_work->local_select, p_work->local_type_page );
}

//----------------------------------------------------------------------------
/**
 *	@brief	選択ﾀｲﾌﾟ別カーソル動作
 *
 *	@param	p_work			ワークﾃﾞｰﾀ
 *	@param	p_glb			グローバルﾃﾞｰﾀ
 *	@param	select_type		セレクトﾀｲﾌﾟ
 *	@param	type_page		ﾀｲﾌﾟのページ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubCursorMoveSub( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb, int select_type, int type_page )
{
	switch( select_type ){
	case ZKN_SORTSEARCH_SELECT_SORT:
		ZknSortSearchSubCursorMoveSort( p_work, p_glb );
		break;
		
	case ZKN_SORTSEARCH_SELECT_NEME:
		ZknSortSearchSubCursorMoveName( p_work, p_glb );
		break;
		
	case ZKN_SORTSEARCH_SELECT_TYPE:
		if( type_page == 0 ){
			ZknSortSearchSubCursorMoveType1( p_work, p_glb );
		}else{
			ZknSortSearchSubCursorMoveType2( p_work, p_glb );
		}
		break;
		
	case ZKN_SORTSEARCH_SELECT_FORM:
		ZknSortSearchSubCursorMoveForm( p_work, p_glb );
		break;
		
	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	カーソルデータ破棄
 *
 *	@param	p_work	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubCursorDelete( ZKN_SORTSEARCHSUB_WORK* p_work )
{
	sys_FreeMemoryEz( p_work->p_cursor_tbl );
	ZKN_CURSOR_Free( p_work->p_cursor );
	p_work->p_cursor = NULL;
	p_work->p_cursor_tbl = NULL;
}


//----------------------------------------------------------------------------
/**
 *	@brief	カーソルの初期作成
 *
 *	@param	p_work	ワーク
 *	@param	heap	ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubCursorMake( ZKN_SORTSEARCHSUB_WORK* p_work, int heap )
{
	ZknSortSearchSubCursorMakeSub( p_work, heap, p_work->local_select, p_work->local_type_page );
}

//----------------------------------------------------------------------------
/**
 *	@brief	選択ﾀｲﾌﾟ別作成
 *
 *	@param	p_work			ワーク
 *	@param	heap			ヒープ
 *	@param	select_type		選択ﾀｲﾌﾟ
 *	@param	type_page		ﾀｲﾌﾟページ
 *
 *	@return	none
 */	
//-----------------------------------------------------------------------------
static void ZknSortSearchSubCursorMakeSub( ZKN_SORTSEARCHSUB_WORK* p_work, int heap, int select_type, int type_page )
{
	switch( select_type ){
	case ZKN_SORTSEARCH_SELECT_SORT:
		ZknSortSearchSubCursorMakeSort( p_work, heap );
		break;
		
	case ZKN_SORTSEARCH_SELECT_NEME:
		ZknSortSearchSubCursorMakeName( p_work, heap );
		break;
		
	case ZKN_SORTSEARCH_SELECT_TYPE:
		if( type_page == 0 ){
			ZknSortSearchSubCursorMakeType1( p_work, heap );
		}else{
			ZknSortSearchSubCursorMakeType2( p_work, heap );
		}
		break;
		
	case ZKN_SORTSEARCH_SELECT_FORM:
		ZknSortSearchSubCursorMakeForm( p_work, heap );
		break;
		
	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	カーソル初期化処理
 *
 *	@param	p_work
 *	@param	p_glb 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubCursorInit( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb )
{
	int cursor_id; 
	
	switch( p_work->local_select ){
	case ZKN_SORTSEARCH_SELECT_SORT:
		cursor_id = ZKN_SORTSEARCHSUB_CURSOR_ID_NARABI;
		break;
		
	case ZKN_SORTSEARCH_SELECT_NEME:
		cursor_id = ZKN_SORTSEARCHSUB_CURSOR_ID_NAME;
		break;
		
	case ZKN_SORTSEARCH_SELECT_TYPE:
		cursor_id = ZKN_SORTSEARCHSUB_CURSOR_ID_TYPE;
		break;
		
	case ZKN_SORTSEARCH_SELECT_FORM:
		cursor_id = ZKN_SORTSEARCHSUB_CURSOR_ID_FORM;
		break;
	default:
		GF_ASSERT(0);
		break;
	}
	
	ZKN_CURSOR_Cont( p_work->p_cursor, ZKN_CURSOR_CONT_SET_CONTID, cursor_id );
}

//----------------------------------------------------------------------------
/**
 *	@brief	カーソル変更
 *
 *	@param	p_work
 *	@param	heap 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubCursorChg( ZKN_SORTSEARCHSUB_WORK* p_work, int heap )
{
	// 今までのカーソルﾃﾞｰﾀ破棄
	ZknSortSearchSubCursorDelete( p_work );

	// 作成
	ZknSortSearchSubCursorMakeSub( p_work, heap, p_work->local_select, p_work->local_type_page );
}




//----------------------------------------------------------------------------
/**
 *	@brief	カーソル初期化
 *
 *	@param	p_drawglb	描画グローバル
 *	@param	cp_work		データワーク
 *	@param	cp_glb		データグローバル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubCursorDrawInit( ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb, const ZKN_SORTSEARCHSUB_WORK* cp_work, const ZKN_SORTSEARCHSUB_GLB* cp_glb )
{
	// カーソル初期化座標設定
	ZKN_UTIL_CursorSetMatrixCursorSysNotAnm( cp_work->p_cursor, p_drawglb->p_drawglb );
	// カーソル動作
	ZknSortSearchSubCursorDrawPack( p_drawglb, cp_work, cp_glb );
}



//----------------------------------------------------------------------------
/**
 *	@brief	カーソル描画処理パック関数
 *
 *	@param	p_drawglb	描画グローバル
 *	@param	cp_work		データワーク
 *	@param	cp_glb		データグローバル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubCursorDrawPack( ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb, const ZKN_SORTSEARCHSUB_WORK* cp_work, const ZKN_SORTSEARCHSUB_GLB* cp_glb )
{
	BOOL check;
	
	//　表示ＯＮＯＦＦとカーソル動作
	if( (ZKN_GLBDATA_TouchCursorFlagGet( cp_glb->p_glb ) == TRUE) ){

		check = ZknSortSearchSubCursorOnOff( p_drawglb, TRUE );

		if( check ){
			// 再描画されたときは,カーソル描画座標を初期化
			// カーソル初期化座標設定
			ZKN_UTIL_CursorSetMatrixCursorSysNotAnm( cp_work->p_cursor, p_drawglb->p_drawglb );
		}

		ZknSortSearchSubCursorDraw( p_drawglb, cp_work );
	}else{
		ZknSortSearchSubCursorOnOff( p_drawglb, FALSE );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	図鑑カーソル描画処理
 *
 *	@param	p_drawglb	描画グローバル
 *	@param	p_work		データワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubCursorDraw( ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb, const ZKN_SORTSEARCHSUB_WORK* cp_work )
{
	ZKN_GLB_DRAWDATA* p_draw = p_drawglb->p_drawglb;
	
	ZKN_UTIL_CursorSetMatrixCursorSys( cp_work->p_cursor, p_draw );
}

//----------------------------------------------------------------------------
/**
 *	@brief	カーソル描画ONOFF
 *
 *	@param	p_draw	描画ワーク
 *	@param	flag	ONOFFフラグ
 *	
 *	@retval	TRUE	値変更
 *	@retval	FALSE	変更しなかった
 */
//-----------------------------------------------------------------------------
static BOOL ZknSortSearchSubCursorOnOff( ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb,  BOOL flag )
{
	ZKN_GLB_DRAWDATA* p_draw = p_drawglb->p_drawglb;
	
	if( ZKN_UTIL_CursorGetDrawFlag( &p_draw->cursor ) != flag ){
		ZKN_UTIL_CursorSetDrawFlag( &p_draw->cursor, flag );
		return TRUE;
	}
	
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	サブ画面OAMResource読み込み
 *
 *	@param	p_draw			描画ワーク
 *	@param	p_drawglb		描画グローばる
 *	@param	heap			ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubLoadOam( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb, int heap )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;
	ARCHANDLE* p_handle = ZKN_GLBDATA_ArcHandlGet( p_drawglb->p_drawglb );
	
	// キャラクタデータ読み込み
	p_draw->res_obj[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerResAddArcChar_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ], p_handle,
			NARC_zukan_zkn_sort_oam_sub_lzh_NCGR, TRUE,
			NARC_zukan_zkn_sort_oam_sub_lzh_NCGR + ZKN_SORTSEARCHSUB_RES_ID,
			NNS_G2D_VRAM_TYPE_2DSUB, heap );
	// 転送
	CLACT_U_CharManagerSetAreaCont( p_draw->res_obj[ CLACT_U_CHAR_RES ] );
	// グラフィックデータだけ破棄
	CLACT_U_ResManagerResOnlyDelete( p_draw->res_obj[ CLACT_U_CHAR_RES ] );

	// パレットデータ読み込み
	p_draw->res_obj[ CLACT_U_PLTT_RES ] = CLACT_U_ResManagerResAddArcPltt_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ], p_handle,
			NARC_zukan_zkn_list_oam_NCLR, FALSE, 
			NARC_zukan_zkn_list_oam_NCLR + ZKN_SORTSEARCHSUB_RES_ID, 
			NNS_G2D_VRAM_TYPE_2DSUB, 
			ZKN_ZUKAN_COMMON_PLTT_SUB_LOAD, heap );
	// 転送
	CLACT_U_PlttManagerSetCleanArea( p_draw->res_obj[ CLACT_U_PLTT_RES ] );	
	// グラフィックデータだけ破棄
	CLACT_U_ResManagerResOnlyDelete( p_draw->res_obj[ CLACT_U_PLTT_RES ] );


	// セルデータ読み込み
	p_draw->res_obj[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ], p_handle,
			NARC_zukan_zkn_sort_oam_sub_lzh_NCER, TRUE,
			NARC_zukan_zkn_sort_oam_sub_lzh_NCER + ZKN_SORTSEARCHSUB_RES_ID,
			CLACT_U_CELL_RES, heap );

	// セルアニメデータ読み込み
	p_draw->res_obj[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ], p_handle, 
			NARC_zukan_zkn_sort_oam_sub_lzh_NANR, TRUE,
			NARC_zukan_zkn_sort_oam_sub_lzh_NANR + ZKN_SORTSEARCHSUB_RES_ID,
			CLACT_U_CELLANM_RES, heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	サブ画面OAMResource破棄
 *
 *	@param	p_draw			描画ワーク
 *	@param	p_drawglb		描画グローバル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubReleaseOam( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;


	CLACT_U_CharManagerDelete( p_draw->res_obj[ CLACT_U_CHAR_RES ] );
	CLACT_U_PlttManagerDelete( p_draw->res_obj[ CLACT_U_PLTT_RES ] );

	// リソース破棄
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw->res_obj[ CLACT_U_CHAR_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ],
			p_draw->res_obj[ CLACT_U_PLTT_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw->res_obj[ CLACT_U_CELL_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			p_draw->res_obj[ CLACT_U_CELLANM_RES ] );
}

//----------------------------------------------------------------------------
/**
 *	@brief	形態OAM読み込み
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubLoadOamForm( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb, int heap )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;
	ARCHANDLE* p_handle = ZKN_GLBDATA_ArcHandlGet( p_drawglb->p_drawglb );
	
	// キャラクタデータ読み込み
	p_draw->res_obj_form[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerResAddArcChar_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ], p_handle,
			NARC_zukan_zkn_sort_oam_sub2_lzh_NCGR, TRUE,
			NARC_zukan_zkn_sort_oam_sub2_lzh_NCGR + ZKN_SORTSEARCHSUB_RES_ID,
			NNS_G2D_VRAM_TYPE_2DSUB, heap );
	// 転送
	CLACT_U_CharManagerSetAreaCont( p_draw->res_obj_form[ CLACT_U_CHAR_RES ] );
	// グラフィックデータだけ破棄
	CLACT_U_ResManagerResOnlyDelete( p_draw->res_obj_form[ CLACT_U_CHAR_RES ] );


	// セルデータ読み込み
	p_draw->res_obj_form[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ], p_handle,
			NARC_zukan_zkn_sort_oam_sub2_lzh_NCER, TRUE,
			NARC_zukan_zkn_sort_oam_sub2_lzh_NCER + ZKN_SORTSEARCHSUB_RES_ID,
			CLACT_U_CELL_RES, heap );

	// セルアニメデータ読み込み
	p_draw->res_obj_form[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ], p_handle, 
			NARC_zukan_zkn_sort_oam_sub2_lzh_NANR, TRUE,
			NARC_zukan_zkn_sort_oam_sub2_lzh_NANR + ZKN_SORTSEARCHSUB_RES_ID,
			CLACT_U_CELLANM_RES, heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	形状OMA破棄
 *
 *	@param	p_draw
 *	@param	p_drawglb 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubReleaseOamForm( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;


	CLACT_U_CharManagerDelete( p_draw->res_obj_form[ CLACT_U_CHAR_RES ] );

	// リソース破棄
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw->res_obj_form[ CLACT_U_CHAR_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw->res_obj_form[ CLACT_U_CELL_RES ] );
	CLACT_U_ResManagerResDelete( 
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			p_draw->res_obj_form[ CLACT_U_CELLANM_RES ] );
}

//----------------------------------------------------------------------------
/**
 *	@brief	アクター登録
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubAddClact( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb, int heap )
{
	CLACT_HEADER		clact_head;
	CLACT_ADD_SIMPLE	add;
	ZKN_GLB_DRAWDATA*	p_draw_glb = p_drawglb->p_drawglb;
	int i;
	
	// 各ボタンを登録
	// アクターヘッダー作成
	CLACT_U_MakeHeader( &clact_head,
			NARC_zukan_zkn_sort_oam_sub_lzh_NCGR + ZKN_SORTSEARCHSUB_RES_ID,
			NARC_zukan_zkn_list_oam_NCLR + ZKN_SORTSEARCHSUB_RES_ID, 
			NARC_zukan_zkn_sort_oam_sub_lzh_NCER + ZKN_SORTSEARCHSUB_RES_ID,
			NARC_zukan_zkn_sort_oam_sub_lzh_NANR + ZKN_SORTSEARCHSUB_RES_ID,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE, 0, 0,
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );

	// 登録共通部分を設定
	add.ClActSet	= p_draw_glb->clact_set;
	add.ClActHeader = &clact_head;
	add.pri			= 32;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DSUB;
	add.heap		= heap;

	// 共通ﾃﾞｰﾀ登録
	ZknSortSearchSubAddClactCommon( p_draw, &add );

	// サブﾃﾞｰﾀ登録
	ZknSortSearchSubAddSubClact( p_draw, &add, p_draw->local_select, p_draw->local_type_page );
}

//----------------------------------------------------------------------------
/**
 *	@brief	アクター破棄
 *
 *	@param	p_draw		描画ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubDeleteClact( ZKN_SORTSEARCHSUB_DRAW* p_draw )
{
	ZknSortSearchSubDeleteClactCommon( p_draw );

	// 選択ﾀｲﾌﾟ別アクター破棄
	ZknSortSearchSubDeleteClactSub( p_draw );
}

//----------------------------------------------------------------------------
/**
 *	@brief	セレクトﾀｲﾌﾟが変更されたので、セルアクターを変更
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubChgClact( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb, int heap )
{
	CLACT_HEADER		clact_head;
	CLACT_ADD_SIMPLE	add;
	ZKN_GLB_DRAWDATA*	p_draw_glb = p_drawglb->p_drawglb;
	int i;
	
	// 各ボタンを登録
	// アクターヘッダー作成
	CLACT_U_MakeHeader( &clact_head,
			NARC_zukan_zkn_sort_oam_sub_lzh_NCGR + ZKN_SORTSEARCHSUB_RES_ID,
			NARC_zukan_zkn_list_oam_NCLR + ZKN_SORTSEARCHSUB_RES_ID, 
			NARC_zukan_zkn_sort_oam_sub_lzh_NCER + ZKN_SORTSEARCHSUB_RES_ID,
			NARC_zukan_zkn_sort_oam_sub_lzh_NANR + ZKN_SORTSEARCHSUB_RES_ID,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE, 0, 0,
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );

	// 登録共通部分を設定
	add.ClActSet	= p_draw_glb->clact_set;
	add.ClActHeader = &clact_head;
	add.pri			= 32;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DSUB;
	add.heap		= heap;


	// 今までのものを破棄
	ZknSortSearchSubDeleteClactSub( p_draw );

	// サブﾃﾞｰﾀ登録
	ZknSortSearchSubAddSubClact( p_draw, &add, p_draw->local_select, p_draw->local_type_page );
}

//----------------------------------------------------------------------------
/**
 *	@brief	サブセルアクター登録関数
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_add		登録ﾃﾞｰﾀ
 *	@param	select_type	セレクトﾀｲﾌﾟ
 *	@param	local_type_page	ﾀｲﾌﾟのpage数
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubAddSubClact( ZKN_SORTSEARCHSUB_DRAW* p_draw, CLACT_ADD_SIMPLE* p_add, int select_type, int local_type_page )
{
	switch( select_type ){
	case ZKN_SORTSEARCH_SELECT_SORT:
		ZknSortSearchSubAddClactSort( p_draw, p_add );
		break;
	case ZKN_SORTSEARCH_SELECT_NEME:
		ZknSortSearchSubAddClactName( p_draw, p_add );
		break;
	case ZKN_SORTSEARCH_SELECT_TYPE:
		if( local_type_page == 0 ){
			ZknSortSearchSubAddClactType1( p_draw, p_add );
		}else{
			ZknSortSearchSubAddClactType2( p_draw, p_add );
		}
		break;
	case ZKN_SORTSEARCH_SELECT_FORM:
		ZknSortSearchSubAddClactForm( p_draw, p_add );
		break;
	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	共通部分のグラフィックセルアクター登録
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_add		登録ﾃﾞｰﾀ　必須ﾃﾞｰﾀ格納済み
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubAddClactCommon( ZKN_SORTSEARCHSUB_DRAW* p_draw, CLACT_ADD_SIMPLE* p_add )
{
	int i;
	
	
	// ボタン作成
	for( i=0; i<ZKN_SORTSEARCHSUB_BUTTON_NUM; i++ ){
		// 登録座標設定
		switch( i ){
		case ZKN_SORTSEARCHSUB_BUTTON_BACK:
			p_add->mat.y		= (ZKN_SORTSEARCHSUB_BUTTON_BACK_Y * FX32_ONE) + SUB_SURFACE_Y;
			p_add->mat.x		= ZKN_SORTSEARCHSUB_BUTTON_BACK_X * FX32_ONE;
			break;

		case ZKN_SORTSEARCHSUB_BUTTON_NARABI:
			p_add->mat.y		= (ZKN_SORTSEARCHSUB_BUTTON_NARABI_Y * FX32_ONE) + SUB_SURFACE_Y;
			p_add->mat.x		= ZKN_SORTSEARCHSUB_BUTTON_X * FX32_ONE;
			break;
			
		case ZKN_SORTSEARCHSUB_BUTTON_NAME:
			p_add->mat.y		= (ZKN_SORTSEARCHSUB_BUTTON_NAME_Y * FX32_ONE) + SUB_SURFACE_Y;
			p_add->mat.x		= ZKN_SORTSEARCHSUB_BUTTON_X * FX32_ONE;
			break;
			
		case ZKN_SORTSEARCHSUB_BUTTON_TYPE:
			p_add->mat.y		= (ZKN_SORTSEARCHSUB_BUTTON_TYPE_Y * FX32_ONE) + SUB_SURFACE_Y;
			p_add->mat.x		= ZKN_SORTSEARCHSUB_BUTTON_X * FX32_ONE;
			break;
			
		case ZKN_SORTSEARCHSUB_BUTTON_FORM:
			p_add->mat.y		= (ZKN_SORTSEARCHSUB_BUTTON_FORM_Y * FX32_ONE) + SUB_SURFACE_Y;
			p_add->mat.x		= ZKN_SORTSEARCHSUB_BUTTON_X * FX32_ONE;
			break;

		case ZKN_SORTSEARCHSUB_BUTTON_ACTION:
			p_add->mat.y		= (ZKN_SORTSEARCHSUB_BUTTON_ACTION_Y * FX32_ONE) + SUB_SURFACE_Y;
			p_add->mat.x		= ZKN_SORTSEARCHSUB_BUTTON_ACTION_X * FX32_ONE;
			break;
		}

		// 登録　アニメーション設定
		p_draw->clact[ i ] = CLACT_AddSimple( p_add );
		
		// アニメシーケンス設定
		switch( i ){
		case ZKN_SORTSEARCHSUB_BUTTON_BACK:
			CLACT_AnmChg( p_draw->clact[ i ], ZKN_SORTSEARCHSUB_RET_BUTTON );
			break;

		case ZKN_SORTSEARCHSUB_BUTTON_NARABI:
		case ZKN_SORTSEARCHSUB_BUTTON_NAME:
		case ZKN_SORTSEARCHSUB_BUTTON_TYPE:
		case ZKN_SORTSEARCHSUB_BUTTON_FORM:
			CLACT_AnmChg( p_draw->clact[ i ], ZKN_SORTSEARCHSUB_SELECT_BUTTON );
			break;

		case ZKN_SORTSEARCHSUB_BUTTON_ACTION:
			CLACT_AnmChg( p_draw->clact[ i ], ZKN_SORTSEARCHSUB_ACTION_BUTTON );
			break;
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	共通部分のOAM破棄
 *
 *	@param	p_draw	描画ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubDeleteClactCommon( ZKN_SORTSEARCHSUB_DRAW* p_draw )
{
	int i;

	for( i=0; i<ZKN_SORTSEARCHSUB_BUTTON_NUM; i++ ){
		CLACT_Delete( p_draw->clact[i] );
	}
}

//-----------------------------------------------------------------------------
/**
 *	@brief	サブボタンアクター破棄共通
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubDeleteClactSub( ZKN_SORTSEARCHSUB_DRAW* p_draw )
{
	int i;

	for( i=0; i<ZKN_SORTSEARCHSUB_BUTTON_SUB_MAX; i++ ){
		if( p_draw->clact_sub[i] ){
			CLACT_Delete( p_draw->clact_sub[i] );
			p_draw->clact_sub[i] = NULL;
		}
	}
}

//-----------------------------------------------------------------------------
/**
 *	@brief	ｿｰﾄ画面登録
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubAddClactSort( ZKN_SORTSEARCHSUB_DRAW* p_draw, CLACT_ADD_SIMPLE* p_add )
{
	int i, j;
	
	// 各座標異OAMを作成する
	for( i=0; i<3; i++ ){
		p_add->mat.y = ZKN_SORTSEARCHSUB_BUTTON_01_Y + (i * (ZKN_SORTSEARCHSUB_BUTTON_01_Y - ZKN_SORTSEARCHSUB_BUTTON_00_Y));
		p_add->mat.y = (p_add->mat.y << FX32_SHIFT)  + SUB_SURFACE_Y;
		for( j=0; j<2; j++ ){
			p_add->mat.x = ZKN_SORTSEARCHSUB_BUTTONDEF_00_X + (j * (ZKN_SORTSEARCHSUB_BUTTONDEF_01_X - ZKN_SORTSEARCHSUB_BUTTONDEF_00_X));

			p_add->mat.x <<= FX32_SHIFT;
			p_draw->clact_sub[ (i*2) + j ] = CLACT_AddSimple( p_add );
			CLACT_AnmChg( p_draw->clact_sub[ (i*2) + j ], ZKN_SORTSEARCHSUB_MAIN_BUTTON );
		}
	}
}

//-----------------------------------------------------------------------------
/**
 *	@brief	なまえ画面登録
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubAddClactName( ZKN_SORTSEARCHSUB_DRAW* p_draw, CLACT_ADD_SIMPLE* p_add )
{
	int i, j;
	
	// 各座標異OAMを作成する
	for( i=0; i<5; i++ ){
		p_add->mat.y = ZKN_SORTSEARCHSUB_BUTTON_00_Y + (i * (ZKN_SORTSEARCHSUB_BUTTON_01_Y - ZKN_SORTSEARCHSUB_BUTTON_00_Y));
		p_add->mat.y = (p_add->mat.y << FX32_SHIFT)  + SUB_SURFACE_Y;
		for( j=0; j<2; j++ ){
			p_add->mat.x = ZKN_SORTSEARCHSUB_BUTTONDEF_00_X + (j * (ZKN_SORTSEARCHSUB_BUTTONDEF_01_X - ZKN_SORTSEARCHSUB_BUTTONDEF_00_X));

			p_add->mat.x <<= FX32_SHIFT;
			p_draw->clact_sub[ (i*2) + j ] = CLACT_AddSimple( p_add );
			CLACT_AnmChg( p_draw->clact_sub[ (i*2) + j ], ZKN_SORTSEARCHSUB_MAIN_BUTTON );
		}
	}
}

//-----------------------------------------------------------------------------
/**
 *	@brief	ﾀｲﾌﾟ1画面登録
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubAddClactType1( ZKN_SORTSEARCHSUB_DRAW* p_draw, CLACT_ADD_SIMPLE* p_add )
{
	int i, j;
	
	// 各座標異OAMを作成する
	for( i=0; i<5; i++ ){
		p_add->mat.y = ZKN_SORTSEARCHSUB_BUTTON_00_Y + (i * (ZKN_SORTSEARCHSUB_BUTTON_01_Y - ZKN_SORTSEARCHSUB_BUTTON_00_Y));
		p_add->mat.y = (p_add->mat.y << FX32_SHIFT)  + SUB_SURFACE_Y;
		for( j=0; j<2; j++ ){
			p_add->mat.x = ZKN_SORTSEARCHSUB_BUTTONDEF_00_X + (j * (ZKN_SORTSEARCHSUB_BUTTONDEF_01_X - ZKN_SORTSEARCHSUB_BUTTONDEF_00_X));

			p_add->mat.x <<= FX32_SHIFT;
			p_draw->clact_sub[ (i*2) + j ] = CLACT_AddSimple( p_add );
			CLACT_AnmChg( p_draw->clact_sub[ (i*2) + j ], ZKN_SORTSEARCHSUB_MAIN_BUTTON );
		}
	}
	
	// ページ送りボタン
	p_add->mat.y = ZKN_SORTSEARCHSUB_BUTTON_05_Y;
	p_add->mat.x = ZKN_SORTSEARCHSUB_BUTTON_TYPE1_TYPE2_X;
	p_add->mat.x <<= FX32_SHIFT;
	p_add->mat.y = (p_add->mat.y << FX32_SHIFT)  + SUB_SURFACE_Y;
	p_draw->clact_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE1_TYPE2 ] = CLACT_AddSimple( p_add );
	CLACT_AnmChg( p_draw->clact_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE1_TYPE2 ], ZKN_SORTSEARCHSUB_PAGE_ADD_BUTTON );
}

//-----------------------------------------------------------------------------
/**
 *	@brief	ﾀｲﾌﾟ2画面登録
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubAddClactType2( ZKN_SORTSEARCHSUB_DRAW* p_draw, CLACT_ADD_SIMPLE* p_add )
{
	int i, j;
	
	// 各座標異OAMを作成する
	for( i=0; i<4; i++ ){
		p_add->mat.y = ZKN_SORTSEARCHSUB_BUTTON_00_Y + (i * (ZKN_SORTSEARCHSUB_BUTTON_01_Y - ZKN_SORTSEARCHSUB_BUTTON_00_Y));
		p_add->mat.y = (p_add->mat.y << FX32_SHIFT)  + SUB_SURFACE_Y;
		for( j=0; j<2; j++ ){
			p_add->mat.x = ZKN_SORTSEARCHSUB_BUTTONDEF_00_X + (j * (ZKN_SORTSEARCHSUB_BUTTONDEF_01_X - ZKN_SORTSEARCHSUB_BUTTONDEF_00_X));

			p_add->mat.x <<= FX32_SHIFT;
			p_draw->clact_sub[ (i*2) + j ] = CLACT_AddSimple( p_add );
			CLACT_AnmChg( p_draw->clact_sub[ (i*2) + j ], ZKN_SORTSEARCHSUB_MAIN_BUTTON );
		}
	}

	// ーーーーーボタン
	p_add->mat.y = ZKN_SORTSEARCHSUB_BUTTON_04_Y;
	p_add->mat.x = ZKN_SORTSEARCHSUB_BUTTONDEF_01_X;
	p_add->mat.x <<= FX32_SHIFT;
	p_add->mat.y = (p_add->mat.y << FX32_SHIFT)  + SUB_SURFACE_Y;
	p_draw->clact_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE2_NONE ] = CLACT_AddSimple( p_add );
	CLACT_AnmChg( p_draw->clact_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE2_NONE ], ZKN_SORTSEARCHSUB_MAIN_BUTTON );
	
	// ページ送りボタン
	p_add->mat.y = ZKN_SORTSEARCHSUB_BUTTON_05_Y;
	p_add->mat.x = ZKN_SORTSEARCHSUB_BUTTON_TYPE2_TYPE1_X;
	p_add->mat.x <<= FX32_SHIFT;
	p_add->mat.y = (p_add->mat.y << FX32_SHIFT)  + SUB_SURFACE_Y;
	p_draw->clact_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE2_TYPE1 ] = CLACT_AddSimple( p_add );
	CLACT_AnmChg( p_draw->clact_sub[ ZKN_SORTSEARCHSUB_BUTTON_TYPE2_TYPE1 ], ZKN_SORTSEARCHSUB_PAGE_SUB_BUTTON );
}

//-----------------------------------------------------------------------------
/**
 *	@brief	フォーム画面登録
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubAddClactForm( ZKN_SORTSEARCHSUB_DRAW* p_draw, CLACT_ADD_SIMPLE* p_add )
{
	int i, j;
	
	// 各座標異OAMを作成する
	for( i=0; i<5; i++ ){
		p_add->mat.y = ZKN_SORTSEARCHSUB_BUTTON_00_Y + (i * (ZKN_SORTSEARCHSUB_BUTTON_01_Y - ZKN_SORTSEARCHSUB_BUTTON_00_Y));
		p_add->mat.y = (p_add->mat.y << FX32_SHIFT)  + SUB_SURFACE_Y;
		for( j=0; j<3; j++ ){
			p_add->mat.x = ZKN_SORTSEARCHSUB_BUTTON_FORM_DEF_X + (j * ZKN_SORTSEARCHSUB_BUTTON_FORM_OFS_X);

			p_add->mat.x <<= FX32_SHIFT;
			p_draw->clact_sub[ (i*3) + j ] = CLACT_AddSimple( p_add );

			CLACT_AnmChg( p_draw->clact_sub[ (i*3) + j ], ZKN_SORTSEARCHSUB_FORM_BUTTON );
		}
	}
}
//----------------------------------------------------------------------------
/**
 *	@brief	形状OAMの絵部分のOAM作成
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubAddClactForm_Gra( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb, int heap )
{
	CLACT_HEADER		clact_head;
	CLACT_ADD_SIMPLE	add;
	ZKN_GLB_DRAWDATA*	p_draw_glb = p_drawglb->p_drawglb;
	int i, j;
	
	// 各ボタンを登録
	// アクターヘッダー作成
	CLACT_U_MakeHeader( &clact_head,
			NARC_zukan_zkn_sort_oam_sub2_lzh_NCGR + ZKN_SORTSEARCHSUB_RES_ID,
			NARC_zukan_zkn_list_oam_NCLR + ZKN_SORTSEARCHSUB_RES_ID, 
			NARC_zukan_zkn_sort_oam_sub2_lzh_NCER + ZKN_SORTSEARCHSUB_RES_ID,
			NARC_zukan_zkn_sort_oam_sub2_lzh_NANR + ZKN_SORTSEARCHSUB_RES_ID,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE, 0, 0,
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );

	// 登録共通部分を設定
	add.ClActSet	= p_draw_glb->clact_set;
	add.ClActHeader = &clact_head;
	add.pri			= 15;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DSUB;
	add.heap		= heap;


	// 各座標異OAMを作成する
	for( i=0; i<5; i++ ){
		add.mat.y = ZKN_SORTSEARCHSUB_BUTTON_00_Y + (i * (ZKN_SORTSEARCHSUB_BUTTON_01_Y - ZKN_SORTSEARCHSUB_BUTTON_00_Y));
		add.mat.y = (add.mat.y << FX32_SHIFT)  + SUB_SURFACE_Y;
		for( j=0; j<3; j++ ){
			add.mat.x = ZKN_SORTSEARCHSUB_BUTTON_FORM_DEF_X + (j * ZKN_SORTSEARCHSUB_BUTTON_FORM_OFS_X);

			add.mat.x <<= FX32_SHIFT;
			p_draw->clact_sub_form[ (i*3) + j ] = CLACT_AddSimple( &add );

			switch( (i*3) + j ){
			case ZKN_SORTSEARCHSUB_BUTTON_FORM_CIRCLE:
				CLACT_AnmChg( p_draw->clact_sub_form[ (i*3) + j ], ZKN_SORTSEARCHSUB_CIRCLE_BUTTON );
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_FORM_HARABAI:
				CLACT_AnmChg( p_draw->clact_sub_form[ (i*3) + j ], ZKN_SORTSEARCHSUB_HARABAI_BUTTON );
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_FORM_WATER:
				CLACT_AnmChg( p_draw->clact_sub_form[ (i*3) + j ], ZKN_SORTSEARCHSUB_WATER_BUTTON );
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_FORM_ARM:
				CLACT_AnmChg( p_draw->clact_sub_form[ (i*3) + j ], ZKN_SORTSEARCHSUB_ARM_BUTTON );
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_FORM_STRAIGHT:
				CLACT_AnmChg( p_draw->clact_sub_form[ (i*3) + j ], ZKN_SORTSEARCHSUB_STRAIGHT_BUTTON );
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_FORM_TAIL:
				CLACT_AnmChg( p_draw->clact_sub_form[ (i*3) + j ], ZKN_SORTSEARCHSUB_TAIL_BUTTON );
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_FORM_LEGS:
				CLACT_AnmChg( p_draw->clact_sub_form[ (i*3) + j ], ZKN_SORTSEARCHSUB_LEGS_BUTTON );
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_FORM_FOUR_LEGS:
				CLACT_AnmChg( p_draw->clact_sub_form[ (i*3) + j ], ZKN_SORTSEARCHSUB_FOURLEGS_BUTTON );
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_FORM_TWO_WING:
				CLACT_AnmChg( p_draw->clact_sub_form[ (i*3) + j ], ZKN_SORTSEARCHSUB_TWO_WING_BUTTON );
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_FORM_MANY_LEGS:
				CLACT_AnmChg( p_draw->clact_sub_form[ (i*3) + j ], ZKN_SORTSEARCHSUB_MANY_LEGS_BUTTON );
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_FORM_COMP:
				CLACT_AnmChg( p_draw->clact_sub_form[ (i*3) + j ], ZKN_SORTSEARCHSUB_COMP_BUTTON );
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_FORM_TWO_LEGS:
				CLACT_AnmChg( p_draw->clact_sub_form[ (i*3) + j ], ZKN_SORTSEARCHSUB_TWO_LEGS_BUTTON );
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_FORM_FOUR_WING:
				CLACT_AnmChg( p_draw->clact_sub_form[ (i*3) + j ], ZKN_SORTSEARCHSUB_FOURWING_BUTTON );
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_FORM_HAITSUKUBARI:
				CLACT_AnmChg( p_draw->clact_sub_form[ (i*3) + j ], ZKN_SORTSEARCHSUB_HAITSUKUBARI_BUTTON );
				break;
			case ZKN_SORTSEARCHSUB_BUTTON_FORM_NONE:
				CLACT_SetDrawFlag( p_draw->clact_sub_form[ (i*3) + j ], FALSE );
				break;
			}
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	形状　グラフィックアクター破棄
 *
 *	@param	p_draw 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubDeleteClactForm_Gra( ZKN_SORTSEARCHSUB_DRAW* p_draw )
{
	int i;

	for( i=0; i<ZKN_SORTSEARCHSUB_BUTTON_SUB_MAX; i++ ){
		if( p_draw->clact_sub_form[ i ] ){
			CLACT_Delete( p_draw->clact_sub_form[ i ] );
			p_draw->clact_sub_form[ i ] = NULL;
		}
	}
}



//----------------------------------------------------------------------------
/**
 *	@brief	フォントOAM作成
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	heap		ヒープ
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubAddFontOam( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb, int heap )
{
	ZKN_FONTOAM_INIT fontoam_init;
	CLACT_U_RES_OBJ_PTR res_obj;
	ZKN_GLB_DRAWDATA* p_glb_draw = p_drawglb->p_drawglb;

	// パレットのリソースデータ取得
	// パレットプロクシ取得用
	res_obj = CLACT_U_ResManagerGetIDResObjPtr( p_glb_draw->res_manager[ CLACT_U_PLTT_RES ], NARC_zukan_zkn_list_oam_NCLR + ZKN_SORTSEARCHSUB_RES_ID );

	// 初期化データの共通部分を作成
	// 共通データ代入
	fontoam_init.zkn_fontoam = p_glb_draw->fontoam_sys;
	fontoam_init.pltt		 = CLACT_U_PlttManagerGetProxy( res_obj, NULL );
	fontoam_init.bg_pri		 = 0;
	fontoam_init.soft_pri	 = 0;
	fontoam_init.draw_area	 = NNS_G2D_VRAM_TYPE_2DSUB;
	fontoam_init.heap		 = heap;

	// 共通ボタンのフォントOAM
	ZknSortSearchSubAddFontCommon( p_draw, &fontoam_init, p_glb_draw->fontoam_sys );


	// 選択ﾀｲﾌﾟのフォントOAM登録
	ZknSortSearchSubAddSubFontOam( p_draw, &fontoam_init, p_glb_draw->fontoam_sys, p_draw->local_select, p_draw->local_type_page );
}

//----------------------------------------------------------------------------
/**
 *	@brief	フォントOAM破棄
 *
 *	@param	p_draw	描画ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubDeleteFontOam( ZKN_SORTSEARCHSUB_DRAW* p_draw )
{
	ZknSortSearchSubDeleteFontCommon( p_draw );

	// 選択フォントOAMの破棄
	ZknSortSearchSubDeleteFontSub( p_draw );
}

//----------------------------------------------------------------------------
/**
 *	@brief	フォントOAM変更処理
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	heap		ヒープ
 *
 *	@return	none
 *	変更順番としてはZknSortSearchSubChgClactの後に行う
 *
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubChgFontOam( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb, int heap )
{
	ZKN_FONTOAM_INIT fontoam_init;
	CLACT_U_RES_OBJ_PTR res_obj;
	ZKN_GLB_DRAWDATA* p_glb_draw = p_drawglb->p_drawglb;

	// パレットのリソースデータ取得
	// パレットプロクシ取得用
	res_obj = CLACT_U_ResManagerGetIDResObjPtr( p_glb_draw->res_manager[ CLACT_U_PLTT_RES ], NARC_zukan_zkn_list_oam_NCLR + ZKN_SORTSEARCHSUB_RES_ID );

	// 初期化データの共通部分を作成
	// 共通データ代入
	fontoam_init.zkn_fontoam = p_glb_draw->fontoam_sys;
	fontoam_init.pltt		 = CLACT_U_PlttManagerGetProxy( res_obj, NULL );
	fontoam_init.bg_pri		 = 0;
	fontoam_init.soft_pri	 = 0;
	fontoam_init.draw_area	 = NNS_G2D_VRAM_TYPE_2DSUB;
	fontoam_init.heap		 = heap;

	// 今までのFONTOAM破棄
	ZknSortSearchSubDeleteFontSub( p_draw );


	// 登録
	ZknSortSearchSubAddSubFontOam( p_draw, &fontoam_init, p_glb_draw->fontoam_sys, p_draw->local_select, p_draw->local_type_page );
}

//----------------------------------------------------------------------------
/**
 *	@brief	サブ面フォントOAMの登録
 *
 *	@param	p_draw			描画ワーク
 *	@param	p_fontoam_init	フォントOAM登録データ
 *	@param	fontoam_sys		フォントOAMシステム
 *	@param	select_type		選択ﾀｲﾌﾟ
 *	@param	local_type_page	ﾀｲﾌﾟのページ数
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubAddSubFontOam( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_FONTOAM_INIT* p_fontoam_init, ZKN_FONTOAM_SYS_PTR fontoam_sys, int select_type, int local_type_page )
{
	switch( select_type ){
	case ZKN_SORTSEARCH_SELECT_SORT:
		ZknSortSearchSubAddFontSort( p_draw, p_fontoam_init, fontoam_sys );
		break;
		
	case ZKN_SORTSEARCH_SELECT_NEME:
		ZknSortSearchSubAddFontName( p_draw, p_fontoam_init, fontoam_sys );
		break;
		
	case ZKN_SORTSEARCH_SELECT_TYPE:
		if( local_type_page == 0 ){
			ZknSortSearchSubAddFontType1( p_draw, p_fontoam_init, fontoam_sys );
		}else{
			ZknSortSearchSubAddFontType2( p_draw, p_fontoam_init, fontoam_sys );
		}
		break;
		
	default:
		break;
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	ボタンフォント　共通ボタン用
 *
 *	@param	p_draw
 *	@param	p_fontoam_init	必須ﾃﾞｰﾀ格納済み
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubAddFontCommon( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_FONTOAM_INIT* p_fontoam_init, ZKN_FONTOAM_SYS_PTR fontoam_sys )
{
	GF_BGL_BMPWIN* win;	// 文字列書き込み先
	int pltt_ofs;	// パレットアドレス


	// パレット転送先アドレス取得
	pltt_ofs = GetPlttProxyOffset( p_fontoam_init->pltt, NNS_G2D_VRAM_TYPE_2DSUB );

	//-------------------------------------
	//	ならび
	//=====================================
	// ビットマップウィンドウ作成
	win = ZKN_FONTOAM_GetBmp( fontoam_sys, 
			ZKN_SORTSEARCHSUB_BUTTONFONT_BMP_SIZE_CX,
			ZKN_SORTSEARCHSUB_BUTTONFONT_BMP_SIZE_CY );
	ZKN_FONTOAM_PrintBmpStr( fontoam_sys, win,
			NARC_msg_zkn_dat, ZNK_SORTSEARCH_03, 0, 0 );
	p_fontoam_init->p_bmp		 = win;
	p_fontoam_init->parent = p_draw->clact[ ZKN_SORTSEARCHSUB_BUTTON_NARABI ];
	p_fontoam_init->x			 = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_3_X;
	p_fontoam_init->y			 = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_Y;
	p_draw->p_fontoam[ ZKN_SORTSEARCHSUB_BUTTON_NARABI ] = ZKN_FONTOAM_Make( p_fontoam_init );
	FONTOAM_SetPaletteNo( p_draw->p_fontoam[ ZKN_SORTSEARCHSUB_BUTTON_NARABI ]->p_fontoam, pltt_ofs + ZKN_SORTSEARCHSUB_BUTTONFONT_PLTOFS );
	// ビットマップウィンドウ破棄
	ZKN_FONTOAM_DeleteBmp( win );

	//-------------------------------------
	//	なまえ
	//=====================================
	// ビットマップウィンドウ作成
	win = ZKN_FONTOAM_GetBmp( fontoam_sys, 
			ZKN_SORTSEARCHSUB_BUTTONFONT_BMP_SIZE_CX,
			ZKN_SORTSEARCHSUB_BUTTONFONT_BMP_SIZE_CY );
	ZKN_FONTOAM_PrintBmpStr( fontoam_sys, win,
			NARC_msg_zkn_dat, ZNK_SORTSEARCH_00, 0, 0 );
	p_fontoam_init->p_bmp		 = win;
	p_fontoam_init->parent = p_draw->clact[ ZKN_SORTSEARCHSUB_BUTTON_NAME ];
	p_fontoam_init->x			 = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_3_X;
	p_fontoam_init->y			 = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_Y;
	p_draw->p_fontoam[ ZKN_SORTSEARCHSUB_BUTTON_NAME ] = ZKN_FONTOAM_Make( p_fontoam_init );
	FONTOAM_SetPaletteNo( p_draw->p_fontoam[ ZKN_SORTSEARCHSUB_BUTTON_NAME ]->p_fontoam, pltt_ofs + ZKN_SORTSEARCHSUB_BUTTONFONT_PLTOFS );
	// ビットマップウィンドウ破棄
	ZKN_FONTOAM_DeleteBmp( win );

	//-------------------------------------
	//	ﾀｲﾌﾟ
	//=====================================
	// ビットマップウィンドウ作成
	win = ZKN_FONTOAM_GetBmp( fontoam_sys, 
			ZKN_SORTSEARCHSUB_BUTTONFONT_BMP_SIZE_CX,
			ZKN_SORTSEARCHSUB_BUTTONFONT_BMP_SIZE_CY );
	ZKN_FONTOAM_PrintBmpStr( fontoam_sys, win,
			NARC_msg_zkn_dat, ZNK_SORTSEARCH_01, 0, 0 );
	p_fontoam_init->p_bmp		 = win;
	p_fontoam_init->parent = p_draw->clact[ ZKN_SORTSEARCHSUB_BUTTON_TYPE ];
	p_fontoam_init->x			 = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_3_X;
	p_fontoam_init->y			 = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_Y;
	p_draw->p_fontoam[ ZKN_SORTSEARCHSUB_BUTTON_TYPE ] = ZKN_FONTOAM_Make( p_fontoam_init );
	FONTOAM_SetPaletteNo( p_draw->p_fontoam[ ZKN_SORTSEARCHSUB_BUTTON_TYPE ]->p_fontoam, pltt_ofs + ZKN_SORTSEARCHSUB_BUTTONFONT_PLTOFS );
	// ビットマップウィンドウ破棄
	ZKN_FONTOAM_DeleteBmp( win );

	//-------------------------------------
	//　かたち
	//=====================================
	// ビットマップウィンドウ作成
	win = ZKN_FONTOAM_GetBmp( fontoam_sys, 
			ZKN_SORTSEARCHSUB_BUTTONFONT_BMP_SIZE_CX,
			ZKN_SORTSEARCHSUB_BUTTONFONT_BMP_SIZE_CY );
	ZKN_FONTOAM_PrintBmpStr( fontoam_sys, win,
			NARC_msg_zkn_dat, ZNK_SORTSEARCH_02, 0, 0 );
	p_fontoam_init->p_bmp		 = win;
	p_fontoam_init->parent = p_draw->clact[ ZKN_SORTSEARCHSUB_BUTTON_FORM ];
	p_fontoam_init->x			 = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_3_X;
	p_fontoam_init->y			 = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_Y;
	p_draw->p_fontoam[ ZKN_SORTSEARCHSUB_BUTTON_FORM ] = ZKN_FONTOAM_Make( p_fontoam_init );
	FONTOAM_SetPaletteNo( p_draw->p_fontoam[ ZKN_SORTSEARCHSUB_BUTTON_FORM ]->p_fontoam, pltt_ofs + ZKN_SORTSEARCHSUB_BUTTONFONT_PLTOFS );
	// ビットマップウィンドウ破棄
	ZKN_FONTOAM_DeleteBmp( win );

	//-------------------------------------
	//	決定
	//=====================================
	// ビットマップウィンドウ作成
	win = ZKN_FONTOAM_GetBmp( fontoam_sys, 
			ZKN_SORTSEARCHSUB_BUTTONFONT_BMP_SIZE_CX,
			ZKN_SORTSEARCHSUB_BUTTONFONT_BMP_SIZE_CY );
	ZKN_FONTOAM_PrintBmpStr( fontoam_sys, win,
			NARC_msg_zkn_dat, ZNK_SORTSEARCH_04, 0, 0 );
	p_fontoam_init->p_bmp		 = win;
	p_fontoam_init->parent = p_draw->clact[ ZKN_SORTSEARCHSUB_BUTTON_ACTION ];
	p_fontoam_init->x			 = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_3_X;
	p_fontoam_init->y			 = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_Y;
	p_draw->p_fontoam[ ZKN_SORTSEARCHSUB_BUTTON_ACTION ] = ZKN_FONTOAM_Make( p_fontoam_init );
	FONTOAM_SetPaletteNo( p_draw->p_fontoam[ ZKN_SORTSEARCHSUB_BUTTON_ACTION ]->p_fontoam, pltt_ofs + ZKN_SORTSEARCHSUB_BUTTONFONT_KETTEI_PLTOFS );
	// ビットマップウィンドウ破棄
	ZKN_FONTOAM_DeleteBmp( win );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ボタンフォント破棄
 *
 *	@param	p_draw 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubDeleteFontCommon( ZKN_SORTSEARCHSUB_DRAW* p_draw )
{
	int i;

	for( i=0; i<ZKN_SORTSEARCHSUB_BUTTON_NUM; i++ ){
		if( p_draw->p_fontoam[ i ] ){
			ZKN_FONTOAM_Delete( p_draw->p_fontoam[ i ] );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief		サブ面のボタンフォント設定
 */
//-----------------------------------------------------------------------------
// 破棄共通
static void ZknSortSearchSubDeleteFontSub( ZKN_SORTSEARCHSUB_DRAW* p_draw )
{
	int i;
	for( i=0; i<ZKN_SORTSEARCHSUB_BUTTON_SUB_MAX; i++ ){
		if( p_draw->p_fontoam_sub[ i ] ){
			ZKN_FONTOAM_Delete( p_draw->p_fontoam_sub[ i ] );
			p_draw->p_fontoam_sub[ i ] = NULL;
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ｿｰﾄボタン
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubAddFontSort( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_FONTOAM_INIT* p_fontoam_init, ZKN_FONTOAM_SYS_PTR fontoam_sys )
{
	GF_BGL_BMPWIN* win;	// 文字列書き込み先
	int pltt_ofs;	// パレットアドレス
	int i;
	int msg_idx;
	int x;

	// パレット転送先アドレス取得
	pltt_ofs = GetPlttProxyOffset( p_fontoam_init->pltt, NNS_G2D_VRAM_TYPE_2DSUB );

	for( i=0; i<ZKN_SORTSEARCHSUB_BUTTON_NARABI_NUM; i++ ){
		// ビットマップウィンドウ作成
		win = ZKN_FONTOAM_GetBmp( fontoam_sys, 
				ZKN_SORTSEARCHSUB_BUTTONFONT_BMP_NARABI_SIZE_CX,
				ZKN_SORTSEARCHSUB_BUTTONFONT_BMP_NARABI_SIZE_CY );
		
		
		switch( i ){
		case ZKN_SORTSEARCHSUB_BUTTON_NARABI_NUMBER:
			msg_idx = ZNK_SORTSEARCH_SORT_00;
			x = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_4_X;
			break;
			
		case ZKN_SORTSEARCHSUB_BUTTON_NARABI_AIUEO:
			msg_idx = ZNK_SORTSEARCH_SORT_01;
			x = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_6_X;
			break;
			
		case ZKN_SORTSEARCHSUB_BUTTON_NARABI_HEAVY:
			msg_idx = ZNK_SORTSEARCH_SORT_02;
			x = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_3_X;
			break;
			
		case ZKN_SORTSEARCHSUB_BUTTON_NARABI_LIGHT:
			msg_idx = ZNK_SORTSEARCH_SORT_03;
			x = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_3_X;
			break;
			
		case ZKN_SORTSEARCHSUB_BUTTON_NARABI_TALL:
			msg_idx = ZNK_SORTSEARCH_SORT_04;
			x = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_3_X;
			break;
			
		case ZKN_SORTSEARCHSUB_BUTTON_NARABI_SHORT:
			msg_idx = ZNK_SORTSEARCH_SORT_05;
			x = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_3_X;
			break;
		}
		
		ZKN_FONTOAM_PrintBmpStr( fontoam_sys, win,
				NARC_msg_zkn_dat, msg_idx, 0, 0 );
		p_fontoam_init->x			 = x;
		p_fontoam_init->p_bmp		 = win;
		p_fontoam_init->parent = p_draw->clact_sub[ i ];
		p_fontoam_init->y			 = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_Y;
	
		p_draw->p_fontoam_sub[ i ] = ZKN_FONTOAM_Make( p_fontoam_init );
		FONTOAM_SetPaletteNo( p_draw->p_fontoam_sub[ i ]->p_fontoam, pltt_ofs + ZKN_SORTSEARCHSUB_BUTTONFONT_OTHER_PLTOFS );
		// ビットマップウィンドウ破棄
		ZKN_FONTOAM_DeleteBmp( win );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	名前ボタン
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubAddFontName( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_FONTOAM_INIT* p_fontoam_init, ZKN_FONTOAM_SYS_PTR fontoam_sys )
{
	GF_BGL_BMPWIN* win;	// 文字列書き込み先
	int pltt_ofs;	// パレットアドレス
	int i, j;
	int msg_idx;

	// パレット転送先アドレス取得
	pltt_ofs = GetPlttProxyOffset( p_fontoam_init->pltt, NNS_G2D_VRAM_TYPE_2DSUB );

	for( i=0; i<ZKN_SORTSEARCHSUB_BUTTON_NAME_NUM; i++ ){
		// ビットマップウィンドウ作成
		win = ZKN_FONTOAM_GetBmp( fontoam_sys, 
				ZKN_SORTSEARCHSUB_BUTTONFONT_BMP_NAME_SIZE_CX,
				ZKN_SORTSEARCHSUB_BUTTONFONT_BMP_NAME_SIZE_CY );
		
		
		switch( i ){
		case ZKN_SORTSEARCHSUB_BUTTON_NAME_A:
			msg_idx = ZNK_SORTSEARCH_NAME_01;
			break;
		case ZKN_SORTSEARCHSUB_BUTTON_NAME_HA:
			msg_idx = ZNK_SORTSEARCH_NAME_06;
			break;
		case ZKN_SORTSEARCHSUB_BUTTON_NAME_KA:
			msg_idx = ZNK_SORTSEARCH_NAME_02;
			break;
		case ZKN_SORTSEARCHSUB_BUTTON_NAME_MA:
			msg_idx = ZNK_SORTSEARCH_NAME_07;
			break;
		case ZKN_SORTSEARCHSUB_BUTTON_NAME_SA:
			msg_idx = ZNK_SORTSEARCH_NAME_03;
			break;
		case ZKN_SORTSEARCHSUB_BUTTON_NAME_RA:
			msg_idx = ZNK_SORTSEARCH_NAME_09;
			break;
		case ZKN_SORTSEARCHSUB_BUTTON_NAME_TA:
			msg_idx = ZNK_SORTSEARCH_NAME_04;
			break;
		case ZKN_SORTSEARCHSUB_BUTTON_NAME_YAWA:
			msg_idx = ZNK_SORTSEARCH_NAME_08;
			break;
		case ZKN_SORTSEARCHSUB_BUTTON_NAME_NA:
			msg_idx = ZNK_SORTSEARCH_NAME_05;
			break;
		case ZKN_SORTSEARCHSUB_BUTTON_NAME_NONE:
			msg_idx = ZNK_SORTSEARCH_NAME_00;
			break;
		}
		
		if( msg_idx == ZNK_SORTSEARCH_NAME_00 ){
			for( j=0; j<5; j++ ){
				ZKN_FONTOAM_PrintBmpStr( fontoam_sys, win,
						NARC_msg_zkn_dat, msg_idx, j * 12, 0 );
			}
		}else{
			ZKN_FONTOAM_PrintBmpStr( fontoam_sys, win,
					NARC_msg_zkn_dat, msg_idx, 0, 0 );
		}

		p_fontoam_init->x			 = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_5_X;
		p_fontoam_init->p_bmp		 = win;
		p_fontoam_init->parent		 = p_draw->clact_sub[ i ];
		p_fontoam_init->y			 = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_Y;
	
		p_draw->p_fontoam_sub[ i ] = ZKN_FONTOAM_Make( p_fontoam_init );
		FONTOAM_SetPaletteNo( p_draw->p_fontoam_sub[ i ]->p_fontoam, pltt_ofs + ZKN_SORTSEARCHSUB_BUTTONFONT_OTHER_PLTOFS );
		// ビットマップウィンドウ破棄
		ZKN_FONTOAM_DeleteBmp( win );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ﾀｲﾌﾟ1ボタン
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubAddFontType1( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_FONTOAM_INIT* p_fontoam_init, ZKN_FONTOAM_SYS_PTR fontoam_sys )
{
	GF_BGL_BMPWIN* win;	// 文字列書き込み先
	int pltt_ofs;	// パレットアドレス
	int i, j;
	int msg_idx;
	int x;

	// パレット転送先アドレス取得
	pltt_ofs = GetPlttProxyOffset( p_fontoam_init->pltt, NNS_G2D_VRAM_TYPE_2DSUB );

	for( i=0; i<ZKN_SORTSEARCHSUB_BUTTON_TYPE1_TYPE2; i++ ){
		// ビットマップウィンドウ作成
		win = ZKN_FONTOAM_GetBmp( fontoam_sys, 
				ZKN_SORTSEARCHSUB_BUTTONFONT_BMP_TYPE1_SIZE_CX,
				ZKN_SORTSEARCHSUB_BUTTONFONT_BMP_TYPE1_SIZE_CY );
		
		
		switch( i ){
		case ZKN_SORTSEARCHSUB_BUTTON_TYPE1_AKU:
			msg_idx = ZNK_SORTSEARCH_TYPE_15;
			x = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_2_X;
			break;
		case ZKN_SORTSEARCHSUB_BUTTON_TYPE1_KOORI:
			msg_idx = ZNK_SORTSEARCH_TYPE_05;
			x = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_3_X;
			break;
		case ZKN_SORTSEARCHSUB_BUTTON_TYPE1_IWA:
			msg_idx = ZNK_SORTSEARCH_TYPE_12;
			x = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_2_X;
			break;
		case ZKN_SORTSEARCHSUB_BUTTON_TYPE1_GHOST:
			msg_idx = ZNK_SORTSEARCH_TYPE_13;
			x = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_4_X;
			break;
		case ZKN_SORTSEARCHSUB_BUTTON_TYPE1_SP:
			msg_idx = ZNK_SORTSEARCH_TYPE_10;
			x = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_4_X;
			break;
		case ZKN_SORTSEARCHSUB_BUTTON_TYPE1_JIMEN:
			msg_idx = ZNK_SORTSEARCH_TYPE_08;
			x = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_3_X;
			break;
		case ZKN_SORTSEARCHSUB_BUTTON_TYPE1_BATTLE:
			msg_idx = ZNK_SORTSEARCH_TYPE_06;
			x = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_4_X;
			break;
		case ZKN_SORTSEARCHSUB_BUTTON_TYPE1_ELEC:
			msg_idx = ZNK_SORTSEARCH_TYPE_03;
			x = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_3_X;
			break;
		case ZKN_SORTSEARCHSUB_BUTTON_TYPE1_KUSA:
			msg_idx = ZNK_SORTSEARCH_TYPE_04;
			x = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_2_X;
			break;
		case ZKN_SORTSEARCHSUB_BUTTON_TYPE1_NONE:
			msg_idx = ZNK_SORTSEARCH_NAME_00;
			x = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_4_X;
			break;
		}
		
		if( msg_idx == ZNK_SORTSEARCH_NAME_00 ){
			for( j=0; j<4; j++ ){
				ZKN_FONTOAM_PrintBmpStr( fontoam_sys, win,
						NARC_msg_zkn_dat, msg_idx, j * 12, 0 );
			}
		}else{
			ZKN_FONTOAM_PrintBmpStr( fontoam_sys, win,
					NARC_msg_zkn_dat, msg_idx, 0, 0 );
		}
		p_fontoam_init->x			 = x;
		p_fontoam_init->p_bmp		 = win;
		p_fontoam_init->parent = p_draw->clact_sub[ i ];
		p_fontoam_init->y			 = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_Y;
	
		p_draw->p_fontoam_sub[ i ] = ZKN_FONTOAM_Make( p_fontoam_init );
		FONTOAM_SetPaletteNo( p_draw->p_fontoam_sub[ i ]->p_fontoam, pltt_ofs + ZKN_SORTSEARCHSUB_BUTTONFONT_OTHER_PLTOFS );
		// ビットマップウィンドウ破棄
		ZKN_FONTOAM_DeleteBmp( win );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ﾀｲﾌﾟ2ボタン
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubAddFontType2( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_FONTOAM_INIT* p_fontoam_init, ZKN_FONTOAM_SYS_PTR fontoam_sys )
{
	GF_BGL_BMPWIN* win;	// 文字列書き込み先
	int pltt_ofs;	// パレットアドレス
	int i, j;
	int msg_idx;
	int x;

	// パレット転送先アドレス取得
	pltt_ofs = GetPlttProxyOffset( p_fontoam_init->pltt, NNS_G2D_VRAM_TYPE_2DSUB );

	for( i=0; i<ZKN_SORTSEARCHSUB_BUTTON_TYPE2_TYPE1; i++ ){
		// ビットマップウィンドウ作成
		win = ZKN_FONTOAM_GetBmp( fontoam_sys, 
				ZKN_SORTSEARCHSUB_BUTTONFONT_BMP_TYPE2_SIZE_CX,
				ZKN_SORTSEARCHSUB_BUTTONFONT_BMP_TYPE2_SIZE_CY );
		
		
		switch( i ){
		case ZKN_SORTSEARCHSUB_BUTTON_TYPE2_DOKU:
			msg_idx = ZNK_SORTSEARCH_TYPE_07;
			x = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_2_X;
			break;
		case ZKN_SORTSEARCHSUB_BUTTON_TYPE2_HIKOR:
			msg_idx = ZNK_SORTSEARCH_TYPE_09;
			x = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_3_X;
			break;
		case ZKN_SORTSEARCHSUB_BUTTON_TYPE2_DRAGON:
			msg_idx = ZNK_SORTSEARCH_TYPE_14;
			x = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_4_X;
			break;
		case ZKN_SORTSEARCHSUB_BUTTON_TYPE2_FIRE:
			msg_idx = ZNK_SORTSEARCH_TYPE_01;
			x = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_3_X;
			break;
		case ZKN_SORTSEARCHSUB_BUTTON_TYPE2_NORMAL:
			msg_idx = ZNK_SORTSEARCH_TYPE_00;
			x = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_4_X;
			break;
		case ZKN_SORTSEARCHSUB_BUTTON_TYPE2_WATER:
			msg_idx = ZNK_SORTSEARCH_TYPE_02;
			x = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_2_X;
			break;
		case ZKN_SORTSEARCHSUB_BUTTON_TYPE2_HAGANE:
			msg_idx = ZNK_SORTSEARCH_TYPE_16;
			x = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_3_X;
			break;
		case ZKN_SORTSEARCHSUB_BUTTON_TYPE2_MUSHI:
			msg_idx = ZNK_SORTSEARCH_TYPE_11;
			x = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_2_X;
			break;
		case ZKN_SORTSEARCHSUB_BUTTON_TYPE2_NONE:
			msg_idx = ZNK_SORTSEARCH_NAME_00;
			x = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_4_X;
			break;
		}
		
		if( msg_idx == ZNK_SORTSEARCH_NAME_00 ){
			for( j=0; j<4; j++ ){
				ZKN_FONTOAM_PrintBmpStr( fontoam_sys, win,
						NARC_msg_zkn_dat, msg_idx, j * 12, 0 );
			}
		}else{
			ZKN_FONTOAM_PrintBmpStr( fontoam_sys, win,
					NARC_msg_zkn_dat, msg_idx, 0, 0 );
		}
		p_fontoam_init->x			 = x;
		p_fontoam_init->p_bmp		 = win;
		p_fontoam_init->parent = p_draw->clact_sub[ i ];
		p_fontoam_init->y			 = ZKN_SORTSEARCHSUB_BUTTONFONT_OFS_Y;
	
		p_draw->p_fontoam_sub[ i ] = ZKN_FONTOAM_Make( p_fontoam_init );
		FONTOAM_SetPaletteNo( p_draw->p_fontoam_sub[ i ]->p_fontoam, pltt_ofs + ZKN_SORTSEARCHSUB_BUTTONFONT_OTHER_PLTOFS );
		// ビットマップウィンドウ破棄
		ZKN_FONTOAM_DeleteBmp( win );
	}
}





//----------------------------------------------------------------------------
/**
 *	@brief	処理実行　初期化
 *
 *	@param	p_work	ﾃﾞｰﾀワーク
 *	@param	p_glb	ﾃﾞｰﾀグローバル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubDoInit( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb )
{
	int select_type = p_work->local_select;
	p_work->do_flag_select = ZKN_SORTSEARCHSUB_DO_FLAG_INIT;
}

//----------------------------------------------------------------------------
/**
 *	@brief	処理の実行処理
 *
 *	@param	p_work		ﾃﾞｰﾀワーク
 *	@param	p_glb		ﾃﾞｰﾀグローバル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubDoMain( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb )
{
	// 共通動作
	ZknSortSearchSubDoCommon( p_work, p_glb );


	// 選択ﾀｲﾌﾟ別動作
	ZknSortSearchSubDoSelect( p_work, p_glb, p_work->local_select, p_work->local_type_page  );
}
static void ZknSortSearchSubDoSelect( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb, int select_type, int type_page )
{
	switch( select_type ){
	case ZKN_SORTSEARCH_SELECT_SORT:
		ZknSortSearchSubDoSort( p_work, p_glb );
		break;
		
	case ZKN_SORTSEARCH_SELECT_NEME:
		ZknSortSearchSubDoName( p_work, p_glb );
		break;
		
	case ZKN_SORTSEARCH_SELECT_TYPE:
		if( type_page == 0 ){
			ZknSortSearchSubDoType1( p_work, p_glb );
		}else{
			ZknSortSearchSubDoType2( p_work, p_glb );
		}
		break;

	case ZKN_SORTSEARCH_SELECT_FORM:
		ZknSortSearchSubDoForm( p_work, p_glb );
		break;
		
	default:
		break;
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	共通ボタンの実行
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubDoCommon( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb )
{
	switch( p_work->do_flag_common ){
	case ZKN_SORTSEARCHSUB_BUTTON_BACK:
		// ポケリストに何もせずに戻る
		ZKN_SortSearchAplReqListFade( p_glb->p_main_apl, FALSE );
		// ボタン音
		Snd_SePlay( ZKN_SND_BUTTON );
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_NARABI:
		if( ZKN_SortSearchAplSelectTypeGet( p_glb->p_main_apl ) != ZKN_SORTSEARCH_SELECT_SORT ){
			// ｿｰﾄ選択モードへ
			ZKN_SortSearchAplSelectTypeSet( p_glb->p_main_apl, ZKN_SORTSEARCH_SELECT_SORT );
			// ボタン音
			Snd_SePlay( ZKN_SND_BUTTON );
		}
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_NAME:
		if( ZKN_SortSearchAplSelectTypeGet( p_glb->p_main_apl ) != ZKN_SORTSEARCH_SELECT_NEME ){
			// なまえ選択モードへ
			ZKN_SortSearchAplSelectTypeSet( p_glb->p_main_apl, ZKN_SORTSEARCH_SELECT_NEME );
			// ボタン音
			Snd_SePlay( ZKN_SND_BUTTON );
		}
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_TYPE:
		if( ZKN_SortSearchAplSelectTypeGet( p_glb->p_main_apl ) != ZKN_SORTSEARCH_SELECT_TYPE ){
			// ﾀｲﾌﾟ選択モードへ
			ZKN_SortSearchAplSelectTypeSet( p_glb->p_main_apl, ZKN_SORTSEARCH_SELECT_TYPE );
			// ボタン音
			Snd_SePlay( ZKN_SND_BUTTON );
			p_work->type_set_no = ZKN_SORTSEARCH_TYPE1;
		}
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_FORM:
		if( ZKN_SortSearchAplSelectTypeGet( p_glb->p_main_apl ) != ZKN_SORTSEARCH_SELECT_FORM ){
			// 形選択モードへ
			ZKN_SortSearchAplSelectTypeSet( p_glb->p_main_apl, ZKN_SORTSEARCH_SELECT_FORM );
			// ボタン音
			Snd_SePlay( ZKN_SND_BUTTON );
		}
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_ACTION:
		if( p_work->req_count <= 1 ){	// 最初のリクエストにしか反応しない
			//　ｿｰﾄ実行 
			ZKN_SortSearchAplReqListFade( p_glb->p_main_apl, TRUE );
			// ボタン音
			Snd_SePlay( ZKN_SND_BUTTON );
		}
		break;

	default:
		break;
	}
	p_work->do_flag_common = ZKN_SORTSEARCHSUB_DO_FLAG_INIT;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ｿｰﾄボタンの実行
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubDoSort( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb )
{
	int set_num = 100;
	
	switch( p_work->do_flag_select ){
	case ZKN_SORTSEARCHSUB_BUTTON_NARABI_NUMBER:
		set_num = ZKN_POKELIST_SORT_NORMAL;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_NARABI_AIUEO:
		set_num =  ZKN_POKELIST_SORT_GOZYUUON;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_NARABI_HEAVY:
		set_num =  ZKN_POKELIST_SORT_GRAM_L;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_NARABI_LIGHT:
		set_num =  ZKN_POKELIST_SORT_GRAM_S;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_NARABI_TALL:
		set_num =  ZKN_POKELIST_SORT_HIGH_L;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_NARABI_SHORT:
		set_num =  ZKN_POKELSIT_SOTT_HIGH_S;
		break;
	default:
		break;
	}
	if( set_num != 100 ){

		if( ZKN_SortSearchAplSortTypeGet( p_glb->p_main_apl ) != set_num ){
			// ボタン音
			Snd_SePlay( ZKN_SND_BUTTON );
			ZKN_SortSearchAplSortTypeSet( p_glb->p_main_apl, set_num );	
		}
	}
	
	p_work->do_flag_select = ZKN_SORTSEARCHSUB_DO_FLAG_INIT; 
}

//----------------------------------------------------------------------------
/**
 *	@brief	名前ボタンの実行
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubDoName( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb )
{
	int set_num = 100;
	
	switch( p_work->do_flag_select ){
	case ZKN_SORTSEARCHSUB_BUTTON_NAME_A:
		set_num = ZKN_POKELIST_SEARCH_NAME_A;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_NAME_HA:
		set_num = ZKN_POKELIST_SEARCH_NAME_HA;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_NAME_KA:
		set_num = ZKN_POKELIST_SEARCH_NAME_KA;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_NAME_MA:
		set_num = ZKN_POKELIST_SEARCH_NAME_MA;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_NAME_SA:
		set_num = ZKN_POKELIST_SEARCH_NAME_SA;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_NAME_RA:
		set_num = ZKN_POKELIST_SEARCH_NAME_RA;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_NAME_TA:
		set_num = ZKN_POKELIST_SEARCH_NAME_TA;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_NAME_YAWA:
		set_num = ZKN_POKELIST_SEARCH_NAME_YAWA;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_NAME_NA:
		set_num = ZKN_POKELIST_SEARCH_NAME_NA;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_NAME_NONE:
		set_num = ZKN_POKELIST_SEARCH_NAME_NONE;
		break;
	default:
		break;
	}

	if( set_num != 100 ){
		if( ZKN_SortSearchAplNameTypeGet( p_glb->p_main_apl ) !=set_num  ){
			// ボタン音
			Snd_SePlay( ZKN_SND_BUTTON );

			ZKN_SortSearchAplNameTypeSet( p_glb->p_main_apl, set_num );
		}
	}
	p_work->do_flag_select = ZKN_SORTSEARCHSUB_DO_FLAG_INIT; 
}

//----------------------------------------------------------------------------
/**
 *	@brief	ﾀｲﾌﾟ1ボタンの実行
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubDoType1( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb )
{
	int set_num = 100;
	
	switch( p_work->do_flag_select ){
	case ZKN_SORTSEARCHSUB_BUTTON_TYPE1_AKU:
		set_num = ZKN_POKELIST_SEARCH_TYPE_AKU;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_TYPE1_KOORI:
		set_num = ZKN_POKELIST_SEARCH_TYPE_KOORI;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_TYPE1_IWA:
		set_num = ZKN_POKELIST_SEARCH_TYPE_IWA;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_TYPE1_GHOST:
		set_num = ZKN_POKELIST_SEARCH_TYPE_GHOST;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_TYPE1_SP:
		set_num = ZKN_POKELIST_SEARCH_TYPE_SP;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_TYPE1_JIMEN:
		set_num = ZKN_POKELIST_SEARCH_TYPE_JIMEN;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_TYPE1_BATTLE:
		set_num = ZKN_POKELIST_SEARCH_TYPE_BATTLE;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_TYPE1_ELEC:
		set_num = ZKN_POKELIST_SEARCH_TYPE_ELECTRIC;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_TYPE1_KUSA:
		set_num = ZKN_POKELIST_SEARCH_TYPE_KUSA;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_TYPE1_NONE:
		set_num = ZKN_POKELIST_SEARCH_TYPE_NONE;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_TYPE1_TYPE2:
		p_work->type_page = 1;
		// ボタン音
		Snd_SePlay( ZKN_SND_BUTTON );
		break;
	default:
		break;
	}

	if( set_num != 100 ){
		ZknSortSearchSubDoTypeSetCommon( p_work, p_glb, set_num );
	}
	p_work->do_flag_select = ZKN_SORTSEARCHSUB_DO_FLAG_INIT; 
}

//----------------------------------------------------------------------------
/**
 *	@brief	ﾀｲﾌﾟ2ボタンの実行
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubDoType2( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb )
{
	int set_num = 100;
	
	switch( p_work->do_flag_select ){
	case ZKN_SORTSEARCHSUB_BUTTON_TYPE2_DOKU:
		set_num = ZKN_POKELIST_SEARCH_TYPE_POISON;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_TYPE2_HIKOR:
		set_num = ZKN_POKELIST_SEARCH_TYPE_HIKOU;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_TYPE2_DRAGON:
		set_num = ZKN_POKELIST_SEARCH_TYPE_DRAGON;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_TYPE2_FIRE:
		set_num = ZKN_POKELIST_SEARCH_TYPE_FIRE;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_TYPE2_NORMAL:
		set_num = ZKN_POKELIST_SEARCH_TYPE_NORMAL;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_TYPE2_WATER:
		set_num = ZKN_POKELIST_SEARCH_TYPE_WATER;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_TYPE2_HAGANE:
		set_num = ZKN_POKELIST_SEARCH_TYPE_METAL;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_TYPE2_MUSHI:
		set_num = ZKN_POKELIST_SEARCH_TYPE_MUSHI;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_TYPE2_NONE:
		set_num = ZKN_POKELIST_SEARCH_TYPE_NONE;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_TYPE2_TYPE1:
		p_work->type_page = 0;
		// ボタン音
		Snd_SePlay( ZKN_SND_BUTTON );
		break;
	default:
		break;
	}

	if( set_num != 100 ){
		ZknSortSearchSubDoTypeSetCommon( p_work,p_glb, set_num );
	}
	p_work->do_flag_select = ZKN_SORTSEARCHSUB_DO_FLAG_INIT; 
}
static void ZknSortSearchSubDoTypeSetCommon( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb, int set_num )
{
	if( set_num != ZKN_POKELIST_SEARCH_TYPE_NONE ){

		// 両方の値と違っていたら設定
		if( (ZKN_SortSearchAplTypeTypeGet( p_glb->p_main_apl, ZKN_SORTSEARCH_TYPE1 ) != set_num) &&
			(ZKN_SortSearchAplTypeTypeGet( p_glb->p_main_apl, ZKN_SORTSEARCH_TYPE2 ) != set_num) ){
		
			if( ZKN_SortSearchAplTypeTypeGet( p_glb->p_main_apl, p_work->type_set_no ) != set_num ){
				
				ZKN_SortSearchAplTypeTypeSet( p_glb->p_main_apl, set_num, p_work->type_set_no );
				p_work->type_set_no = (p_work->type_set_no + 1) % ZKN_SORTSEARCH_TYPENUM;
				// ボタン音
				Snd_SePlay( ZKN_SND_BUTTON );
			}
		}
	}else{
		// 空白にするとき
		// 空白以外が入っているほうを初期化する
		if( ZKN_SortSearchAplTypeTypeGet( p_glb->p_main_apl, ZKN_SORTSEARCH_TYPE1 ) != ZKN_POKELIST_SEARCH_TYPE_NONE ){
			ZKN_SortSearchAplTypeTypeSet( p_glb->p_main_apl, set_num, ZKN_SORTSEARCH_TYPE1 );
			// ボタン音
			Snd_SePlay( ZKN_SND_BUTTON );
		}else{
			if( ZKN_SortSearchAplTypeTypeGet( p_glb->p_main_apl, ZKN_SORTSEARCH_TYPE2 ) != ZKN_POKELIST_SEARCH_TYPE_NONE ){
				ZKN_SortSearchAplTypeTypeSet( p_glb->p_main_apl, set_num, ZKN_SORTSEARCH_TYPE2 );
				// ボタン音
				Snd_SePlay( ZKN_SND_BUTTON );
			}
		}
		p_work->type_set_no = ZKN_SORTSEARCH_TYPE1;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	形ボタンの実行
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubDoForm( ZKN_SORTSEARCHSUB_WORK* p_work, ZKN_SORTSEARCHSUB_GLB* p_glb )
{
	int set_num = 100;
	
	switch( p_work->do_flag_select ){
	case ZKN_SORTSEARCHSUB_BUTTON_FORM_CIRCLE:
		set_num = ZKN_POKELIST_SEARCH_FORM_CIRCLE;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_FORM_HARABAI:
		set_num = ZKN_POKELIST_SEARCH_FORM_HARABAI;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_FORM_WATER:
		set_num = ZKN_POKELIST_SEARCH_FORM_WATER;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_FORM_ARM:
		set_num = ZKN_POKELIST_SEARCH_FORM_ARM;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_FORM_STRAIGHT:
		set_num = ZKN_POKELIST_SEARCH_FORM_STRAIGHT;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_FORM_TAIL:
		set_num = ZKN_POKELIST_SEARCH_FORM_TAIL;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_FORM_LEGS:
		set_num = ZKN_POKELIST_SEARCH_FORM_LEGS;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_FORM_FOUR_LEGS:
		set_num = ZKN_POKELIST_SEARCH_FORM_FOUR_LEGS;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_FORM_TWO_WING:
		set_num = ZKN_POKELIST_SEARCH_FORM_TWO_WING;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_FORM_MANY_LEGS:
		set_num = ZKN_POKELIST_SEARCH_FORM_MANY_LEGS;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_FORM_COMP:
		set_num = ZKN_POKELIST_SEARCH_FORM_COMP;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_FORM_TWO_LEGS:
		set_num = ZKN_POKELIST_SEARCH_FORM_TWO_LEGS;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_FORM_FOUR_WING:
		set_num = ZKN_POKELIST_SEARCH_FORM_FOUR_WING;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_FORM_HAITSUKUBARI:
		set_num = ZKN_POKELIST_SEARCH_FORM_HAITSUKUBARI;
		break;
	case ZKN_SORTSEARCHSUB_BUTTON_FORM_NONE:
		set_num = ZKN_POKELIST_SEARCH_FORM_NONE;
		break;
	default:
		break;
	}

	if( set_num != 100 ){
		if( ZKN_SortSearchAplFormTypeGet( p_glb->p_main_apl ) != set_num ){
			// ボタン音
			Snd_SePlay( ZKN_SND_BUTTON );

			ZKN_SortSearchAplFormTypeSet( p_glb->p_main_apl, set_num );
		}
	}
	p_work->do_flag_select = ZKN_SORTSEARCHSUB_DO_FLAG_INIT; 
}


//----------------------------------------------------------------------------
/**
 *	@brief	ボタンフェードコントロール
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubButtonFadeCont( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb )
{
	// 今フェード中かチェック
	if( p_draw->do_fade == ZKN_SORTSEARCH_SUB_BUTTON_FADE_NONE ){
		
		// リクエストがあったらフェード開始
		if( p_drawglb->button_fade_req > ZKN_SORTSEARCH_SUB_BUTTON_FADE_NONE ){
			p_draw->do_fade = p_drawglb->button_fade_req;
			p_draw->do_fade_seq = 0;
			p_draw->end_flag = p_drawglb->button_fade;
			*p_draw->end_flag = FALSE;

			// リクエストﾃﾞｰﾀ初期化
			p_drawglb->button_fade_req = ZKN_SORTSEARCH_SUB_BUTTON_FADE_NONE;
		}
	}else{

		// フェード実行
		ZknSortSearchSubButtonFade( p_draw );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ボタンフェード処理
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubButtonFade( ZKN_SORTSEARCHSUB_DRAW* p_draw )
{
	BOOL check;


	// 実行フェードﾀｲﾌﾟがNONEならなにもしない
	if( p_draw->do_fade == ZKN_SORTSEARCH_SUB_BUTTON_FADE_NONE ){
		return ;
	}
	
	switch( p_draw->do_fade_seq ){
	case 0:
		// 動作初期化
		if( p_draw->do_fade == ZKN_SORTSEARCH_SUB_BUTTON_FADE_IN ){
			ZKN_UTIL_MoveReq( &p_draw->fade_work, 0, 16, 0, 0, ZKN_SORTSEARCHSUB_BUTTON_FADE_SYNC );
		}else{
			ZKN_UTIL_MoveReq( &p_draw->fade_work, 16, 0, 0, 0, ZKN_SORTSEARCHSUB_BUTTON_FADE_SYNC );
		}

		G2S_SetBlendAlpha( GX_BLEND_PLANEMASK_NONE, GX_BLEND_PLANEMASK_BG2, p_draw->fade_work.x, 16 - p_draw->fade_work.x );
		p_draw->do_fade_seq ++;
		break;

	case 1:
		check = ZKN_UTIL_MoveMain( &p_draw->fade_work );	
		G2S_ChangeBlendAlpha( p_draw->fade_work.x, 16 - p_draw->fade_work.x );
		if( check == TRUE ){
			// OAMを半透明解除
			if( p_draw->do_fade == ZKN_SORTSEARCH_SUB_BUTTON_FADE_IN ){
				G2S_BlendNone();
			}
			
			*p_draw->end_flag = TRUE;
			p_draw->do_fade_seq = 0;
			p_draw->do_fade = ZKN_SORTSEARCH_SUB_BUTTON_FADE_NONE;
		}
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ｿｰﾄｻｰﾁOAMﾓｰﾄﾞ設定パック関数
 *
 *	@param	p_draw
 *	@param	mode
 *	@param	select_type
 *	@param	type_page 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubButtonFadeOamModeSet_Pack( ZKN_SORTSEARCHSUB_DRAW* p_draw, int mode, int select_type, int type_page )
{
	if( select_type == ZKN_SORTSEARCH_SELECT_TYPE ){
		if( type_page == 0 ){
			// TYPE1
			ZknSortSearchSubButtonFadeOamModeSet_Type1Ver( p_draw, mode );
		}else{
			// TYPE2
			ZknSortSearchSubButtonFadeOamModeSet_Type2Ver( p_draw, mode );
		}
	}else{
		ZknSortSearchSubButtonFadeOamModeSet( p_draw, mode );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	フェードするオブジェもモード設定
 *
 *	@param	p_draw
 *	@param	mode 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubButtonFadeOamModeSet( ZKN_SORTSEARCHSUB_DRAW* p_draw, int mode )
{
	int i;

	for( i=0; i<ZKN_SORTSEARCHSUB_BUTTON_SUB_MAX; i++ ){
		if( p_draw->clact_sub[i] ){
			CLACT_ObjModeSet( p_draw->clact_sub[i], mode );
		}
		if( p_draw->p_fontoam_sub[i] ){
			FONTOAM_ObjModeSet( p_draw->p_fontoam_sub[i]->p_fontoam, mode );
		}
		if( p_draw->clact_sub_form[i] ){
			CLACT_ObjModeSet( p_draw->clact_sub_form[i], mode );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	半透明設定　ﾀｲﾌﾟ１バージョン
 *
 *	@param	p_draw
 *	@param	mode 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubButtonFadeOamModeSet_Type1Ver( ZKN_SORTSEARCHSUB_DRAW* p_draw, int mode )
{
	int i;

	for( i=0; i<ZKN_SORTSEARCHSUB_BUTTON_SUB_MAX; i++ ){
		if( i != ZKN_SORTSEARCHSUB_BUTTON_TYPE1_TYPE2 ){
			if( p_draw->clact_sub[i] ){
				CLACT_ObjModeSet( p_draw->clact_sub[i], mode );
			}
			if( p_draw->p_fontoam_sub[i] ){
				FONTOAM_ObjModeSet( p_draw->p_fontoam_sub[i]->p_fontoam, mode );
			}
		}
	}
}
// ﾀｲﾌﾟ２バージョン
static void ZknSortSearchSubButtonFadeOamModeSet_Type2Ver( ZKN_SORTSEARCHSUB_DRAW* p_draw, int mode )
{
	int i;

	for( i=0; i<ZKN_SORTSEARCHSUB_BUTTON_SUB_MAX; i++ ){
		if( i != ZKN_SORTSEARCHSUB_BUTTON_TYPE2_TYPE1 ){
			if( p_draw->clact_sub[i] ){
				CLACT_ObjModeSet( p_draw->clact_sub[i], mode );
			}
			if( p_draw->p_fontoam_sub[i] ){
				FONTOAM_ObjModeSet( p_draw->p_fontoam_sub[i]->p_fontoam, mode );
			}
		}
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	ｿｰﾄフェードシステム
 *
 *	@param	p_draw			描画ワーク
 *	@param	p_drawglb		描画グローバル
 *	@param	cp_glb			グローバル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSortSearchSubSortFadeSys( ZKN_SORTSEARCHSUB_DRAW* p_draw, ZKN_SORTSEARCHSUB_DRAWGLB* p_drawglb, const ZKN_SORTSEARCHSUB_GLB* cp_glb )
{
	// 動作処理初期化
	if( ZKN_SortSearchAplFadeModeCountGet( cp_glb->p_main_apl ) == ZKN_SORTSEARCH_FADECOUNT_MAX ){
		
		if( ZKN_SortSearchAplFadeModeGet( cp_glb->p_main_apl ) == ZKN_SORTSEARCH_FADEIN ){
			ChangeBrightnessRequest( ZKN_SORTSEARCH_FADECOUNT_MAX,
					BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK, PLANEMASK_ALL, MASK_SUB_DISPLAY );
		}else if( ZKN_SortSearchAplFadeModeGet( cp_glb->p_main_apl ) == ZKN_SORTSEARCH_FADEOUT ){
			ChangeBrightnessRequest( ZKN_SORTSEARCH_FADECOUNT_MAX,
					BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL, PLANEMASK_ALL, MASK_SUB_DISPLAY );
		}
	}
}

