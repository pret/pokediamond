//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_sound_sub.c
 *	@brief		泣き声サブ画面
 *	@author		tomoya takahashi 
 *	@data		2006.01.21
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include <string.h>
#include "include/application/zukanlist/zkn_event_func.h"

#include "include/system/snd_tool.h"

#include "include/gflib/calctool.h"
#include "include/gflib/vram_transfer_manager.h"

#include "include/system/brightness.h"
#include "include/system/arc_tool.dat"
#include "include/system/arc_util.h"
#include "include/system/clact_util.h"
#include "include/application/zukanlist/zukan.naix"
#include "include/gflib/button_man.h"
#include "include/system/msgdata_util.h"
#include "include/msgdata/msg.naix"
#include "include/msgdata/msg_zkn.h"

#include "include/application/zukanlist/zkn_snd_def.h"
#include "include/application/zukanlist/zkn_zukan_common.h"
#include "include/application/zukanlist/zkn_cursor.h"
#include "include/application/zukanlist/zkn_sound.h"


#define	__ZKN_SOUND_SUB_SUB_H_GLOBAL
#include "include/application/zukanlist/zkn_sound_sub.h"

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
//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------
#define ZKN_SOUND_SUB_EVENT_NUM ( 0 )	// イベント数

#define ZKN_SOUND_SUB_OAM_BG_PTR	( 2 )

enum{
	ZKN_SOUNDSUB_SEQINIT_ALLOC,
	ZKN_SOUNDSUB_SEQINIT_LOAD,
	ZKN_SOUNDSUB_SEQINIT_FADEIN,
	ZKN_SOUNDSUB_SEQINIT_END,
};
enum{
	ZKN_SOUNDSUB_SEQDELETE_FADEOUT_INIT,
	ZKN_SOUNDSUB_SEQDELETE_FADEOUT,
	ZKN_SOUNDSUB_SEQDELETE_RELEASE,
	ZKN_SOUNDSUB_SEQDELETE_FREE,
	ZKN_SOUNDSUB_SEQDELETE_END,
};


//-------------------------------------
//	ボタン種類
//=====================================
enum{
	ZKN_SOUNDSUB_BUTTON_SWITCH,
	ZKN_SOUNDSUB_BUTTON_DIAL,
	ZKN_SOUNDSUB_BUTTON_DISK,
	ZKN_SOUNDSUB_BUTTON_NUM,
};
#define ZKN_SOUNDSUB_BUTTON_SWITCH_X	( 64 )
#define ZKN_SOUNDSUB_BUTTON_SWITCH_Y	( 67 )
#define ZKN_SOUNDSUB_BUTTON_SWITCH_SIZXH	( 42 )	// サイズの半分
#define ZKN_SOUNDSUB_BUTTON_SWITCH_SIZYH	( 14 )	// サイズの半分
#define ZKN_SOUNDSUB_BUTTON_DIAL_X	( 51 )
#define ZKN_SOUNDSUB_BUTTON_DIAL_Y	( 157 )
#define ZKN_SOUNDSUB_BUTTON_DIAL_R	( 32 )

#define ZKN_SOUNDSUB_DISK_BG_CENTER_X	( ZKN_SOUNDSUB_DISK_BG_BGCX - (ZKN_SOUNDSUB_DISK_BG_X) )
#define ZKN_SOUNDSUB_DISK_BG_CENTER_Y	( ZKN_SOUNDSUB_DISK_BG_BGCY - (ZKN_SOUNDSUB_DISK_BG_Y) )

#define ZKN_SOUNDSUB_DISK_BG_CENTER_T_OFS_Y	( 8 )	// タッチ判定用オフセット
#define ZKN_SOUNDSUB_DISK_BG_CENTER_OFS_Y	( 16 )	// スロー再生、ピッチパンの判定境界オフセット
#define ZKN_SOUNDSUB_DISK_BG_R			( 72 )

//-------------------------------------
//	サブボタン種類
//	領域のかぶるもの用
//=====================================
enum{
	ZKN_SOUNDSUB_BUTTON_SUB_STARTSTOP,
	ZKN_SOUNDSUB_BUTTON_SUB_LOOP,
	ZKN_SOUNDSUB_BUTTON_SUB_NUM,
};
#define ZKN_SOUNDSUB_BUTTON_STARTSTOP_X	( 180 )
#define ZKN_SOUNDSUB_BUTTON_STARTSTOP_Y	( 131 )
#define ZKN_SOUNDSUB_BUTTON_STARTSTOP_SIZXH	( 24 )	// サイズの半分
#define ZKN_SOUNDSUB_BUTTON_STARTSTOP_SIZYH	( 24 )	// サイズの半分
#define ZKN_SOUNDSUB_BUTTON_STARTSTOP_X_DRAW	( ZKN_SOUNDSUB_BUTTON_STARTSTOP_X )	// 描画位置の補正用
#define ZKN_SOUNDSUB_BUTTON_STARTSTOP_Y_DRAW	( ZKN_SOUNDSUB_BUTTON_STARTSTOP_Y )	// 描画位置の補正用

#define ZKN_SOUNDSUB_BUTTON_LOOP_X	( 230 )
#define ZKN_SOUNDSUB_BUTTON_LOOP_Y	( 166 )
#define ZKN_SOUNDSUB_BUTTON_LOOP_SIZXH	( 16 )	// サイズの半分
#define ZKN_SOUNDSUB_BUTTON_LOOP_SIZYH	( 16 )	// サイズの半分
#define ZKN_SOUNDSUB_BUTTON_LOOP_X_DRAW	( ZKN_SOUNDSUB_BUTTON_LOOP_X )	// 描画位置の補正用
#define ZKN_SOUNDSUB_BUTTON_LOOP_Y_DRAW	( ZKN_SOUNDSUB_BUTTON_LOOP_Y )	// 描画位置の補正用

// 再生ボタン位置カーソル
#define ZKN_SOUNDSUB_CURSOR_START_SIZX ( 24 )
#define ZKN_SOUNDSUB_CURSOR_START_SIZY ( 24 )

// アニメーションシーケンス
enum{
	ZKN_SOUNDSUB_SEQ_SWITCH_PICH_PAN,
	ZKN_SOUNDSUB_SEQ_DIAL,
	ZKN_SOUNDSUB_SEQ_SOUND_STOP_ANM,
	ZKN_SOUNDSUB_SEQ_SOUND_START_ANM,
	ZKN_SOUNDSUB_SEQ_SWITCH_PAN_PICH,
	ZKN_SOUNDSUB_SEQ_SOUND_LOOPON_ANM,
	ZKN_SOUNDSUB_SEQ_SOUND_LOOPOFF_ANM,
};
#define ZKN_SOUNDSUB_ANIME_FRAME	( FX32_ONE * 2 )


// ピッチスイッチ
enum{
	ZKN_SOUNDSUB_SWITCH_00,
	ZKN_SOUNDSUB_SWITCH_01,
	ZKN_SOUNDSUB_SWITCH_02,
	ZKN_SOUNDSUB_SWITCH_03,
	ZKN_SOUNDSUB_SWITCH_04,
	ZKN_SOUNDSUB_SWITCH_05,
	ZKN_SOUNDSUB_SWITCH_06,
	ZKN_SOUNDSUB_SWITCH_07,
	ZKN_SOUNDSUB_SWITCH_08,
};
enum{
	ZKN_SOUNDSUB_SEQ_SWITCH_PICH,
	ZKN_SOUNDSUB_SEQ_SWITCH_PAN,
	ZKN_SOUNDSUB_SEQ_SWITCH_NUM
};
#define ZKN_SOUNDSUB_SWITCH_MOVE_OK_DIS		( 12 )

// 再生ボタン
enum{
	ZKN_SOUNDSUB_START_00,
	ZKN_SOUNDSUB_START_01,
	ZKN_SOUNDSUB_START_02,
	ZKN_SOUNDSUB_START_03,
	ZKN_SOUNDSUB_START_04,
	ZKN_SOUNDSUB_START_05,
};
#define ZKN_SOUNDDUB_BUTTON_START_NOTOUCH	( 100 )

// ループボタン
enum{
	ZKN_SOUNDSUB_LOOP_00,
	ZKN_SOUNDSUB_LOOP_01,
	ZKN_SOUNDSUB_LOOP_02,
	ZKN_SOUNDSUB_LOOP_03,
	ZKN_SOUNDSUB_LOOP_04,
	ZKN_SOUNDSUB_LOOP_05,
};

#define ZKN_SOUNDSUB_DIAL_LOOP_WAIT	( 10 )


// ダイアル
enum{
	ZKN_SOUNDSUB_DIAL_NONE,
	ZKN_SOUNDSUB_DIAL_REVERB,
	ZKN_SOUNDSUB_DIAL_FILTER,
};

#define ZKN_SOUNDSUB_DIAL_DIVISION	( 8 )

#define ZKN_SOUNDSUB_DIAL_REVERB_NUM	( 8 )
#define ZKN_SOUNDSUB_DIAL_FILTER_NUM	( 1 )
#define ZKN_SOUNDSUB_DIAL_DRAW_R		( 14 )
#define ZKN_SOUNDSUB_DIAL_MOVE_NUM_MAX	( 88 )
#define ZKN_SOUNDSUB_DIAL_MOVE_NUM_HALF	( ZKN_SOUNDSUB_DIAL_MOVE_NUM_MAX/2 )
#define ZKN_SOUNDSUB_DIAL_MOVE_LIMIT_ROTA	( 1 )
#define ZKN_SOUNDSUB_DIAL_LIMIT		( 32 )
#define ZKN_SOUNDSUB_DIAL_LIMIT_MIN	( ZKN_SOUNDSUB_DIAL_LIMIT )
#define ZKN_SOUNDSUB_DIAL_LIMIT_MAX	( (ZKN_SOUNDSUB_DIAL_MOVE_NUM_MAX - ZKN_SOUNDSUB_DIAL_LIMIT) )	

#define ZKN_SOUNDSUB_DIAL_CUT_ONE_NUM	( ZKN_SOUNDSUB_DIAL_LIMIT / ZKN_SOUNDSUB_DIAL_DIVISION )
#define ZKN_SOUNDSUB_DIAL_MIN_CUT_NUM	( ZKN_SOUNDSUB_DIAL_CUT_ONE_NUM )	// 放したとき、この角度の倍数の値にする
// リバーブのときはダイアルの値がこの間になっている
#define ZKN_SOUNDSUB_DIAL_REVERB_MIN	( ZKN_SOUNDSUB_DIAL_LIMIT_MAX / ZKN_SOUNDSUB_DIAL_MIN_CUT_NUM )
#define ZKN_SOUNDSUB_DIAL_REVERB_MAX	( ZKN_SOUNDSUB_DIAL_MOVE_NUM_MAX / ZKN_SOUNDSUB_DIAL_MIN_CUT_NUM )

// ディスク部分の座標
#define ZKN_SOUNDSUB_DISK_BG_X		( -48 )
#define ZKN_SOUNDSUB_DISK_BG_Y		( -16 )
#define ZKN_SOUNDSUB_DISK_BG_BGCX	( 131 )		// BGアフィン変換用中心
#define ZKN_SOUNDSUB_DISK_BG_BGCY	( 99 )		// BGアフィン変換用中心
#define ZKN_SOUNDSUB_DISK_BG_ROTA_MUL	( -16 )

#define ZKN_SOUNDSUB_DISK_PITCK_MAX	( 1024 )
#define ZKN_SOUNDSUB_DISK_CHORUS_MAX	( 127 )
#define ZKN_SOUNDSUB_DISK_PAN_MAX	( 127 )
#define ZKN_SOUNDSUB_DISK_PITCH_PAN_PL	( 7 )

// ピッチパン文字列
#define ZKN_SOUNDSUB_BUTTONFONT_BMP_SIZE_CX	( 8 )
#define ZKN_SOUNDSUB_BUTTONFONT_BMP_SIZE_CY	( 2 )
#define ZKN_SOUNDSUB_PITCH_FOTN_X		( 40 )
#define ZKN_SOUNDSUB_PAN_FOTN_X			( 50 )
#define ZKN_SOUNDSUB_PITCH_PAN_FOTN_Y	( 86 )
#define ZKN_SOUNDSUB_BUTTON_PAL_OFS	(0)

#define ZKN_SOUNDSUB_FADE_PLANEMSK	( GX_BLEND_PLANEMASK_BG2|GX_BLEND_PLANEMASK_BG3|GX_BLEND_PLANEMASK_BD )

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	なきごえサブ画面　グローバル変数
//=====================================
typedef struct {
	int* p_event_key;

	ZKN_GLB_DATA* p_glb;
	
	// 図鑑コモンサブアプリデータ
	const ZKN_APL_DATA* cp_zukan_common_apl;

	// 外部再参照用
	int now_pitch;		// 設定中のピッチ
} ZKN_SOUND_SUB_GLB;

//-------------------------------------
//	大きさぐらべサブ画面画面　描画グローバル変数
//=====================================
typedef struct {
	ZKN_GLB_DRAWDATA* p_drawglb;
} ZKN_SOUND_SUB_DRAWGLB;

//-------------------------------------
//	ボタンコールバックへのワーク
//=====================================
typedef struct {
	void* p_glb;
	void* p_work;
} ZKN_SOUND_BUTTON_CALLBACK;

//-------------------------------------
//	なきごえサブ画面　内部ワーク
//=====================================
typedef struct {
	// ボタンマネージャ
	BUTTON_MAN* p_button_man;
	TP_HIT_TBL *hit_tbl;	// ボタンデータ
	ZKN_SOUND_BUTTON_CALLBACK callcack;

	// サブボタンマネージャ
	TP_HIT_TBL* p_sub_hit_tbl;	// 領域のかぶるものを判定するため
	BUTTON_MAN* p_sub_button_man;
	int sub_button_event[ ZKN_SOUNDSUB_BUTTON_SUB_NUM ];

	// 再生ボタン用
	BOOL hit_start_stop_flag;

	
	// 再生ボタン反応フラグ
	BOOL start_touch_on;

	// 再生ボタン　カーソルで押したフラグ
	int sound_play_button_cursor;
		
	
	// 今音を再生中か
	BOOL sound_play;

	// ピッチスイッチ	（コーラスとパン変更スイッチに変更されました）
	int pitch_switch_touch;
	int pitch_switch_flag;
	int pitch_switch_touch_start_x;
	int pitch_num;		// ピッチ設定数
	int pan_num;		// パン設定数
	int chorus_num;		// コーラスボリューム
	BOOL pitch_pan_push;// 押されているときTRUE

	// リバーブ/フィルターダイヤル
	BOOL dial_touch;
	int	dial_flag;		// なし0 リバーブ1 フィルター2
	int dial_start_x;
	int dial_start_y;
	int dial_rota;		// 現在の回転角
	int dial_div;		// 現在の分割位置


	// ループ
	BOOL loop;			// TRUE ループ
	int loop_wait;		// ループウエイト

	const SNDWaveData* cp_snd_data;	// サウンドデータ

} ZKN_SOUND_SUB_WORK;

//-------------------------------------
//	アニメボタンワーク
//=====================================
typedef struct {
	int anm_seq1;		// シーケンス1
	int anm_seq2;		// シーケンス2
	int now_anm_seq;	// 今のシーケンス

	BOOL flag;			// シーケンススイッチフラグ

	int anm_num_max;	// アニメﾌﾚｰﾑ数最大
	int push_anm_limit;	// 押しアニメのリミットﾌﾚｰﾑ数
} ZKN_SOUND_SUB_ANM_BUTTON;


//-------------------------------------
//	なきごえサブ画面画面　内部ワーク
//=====================================
typedef struct {
	// ダイヤル
	CLACT_WORK_PTR	dial;			// ダイヤル	
	
	//　開始停止
	CLACT_WORK_PTR	startstop;		// 開始停止
	ZKN_SOUND_SUB_ANM_BUTTON start_stop_anim;

	// ループボタン
	CLACT_WORK_PTR	loop;
	ZKN_SOUND_SUB_ANM_BUTTON loop_anim;
	
	// スイッチ
	CLACT_WORK_PTR	pich_switch;	// スイッチ	
	int now_switch;	// 今表示されているスイッチ状態
	fx32 pich_switch_frame;

	//	ディスク 
	int disk_last_tick;
	u16	disk_rota;

	// ピッチパン文字列
	ZKN_FONTOAM_DATA* p_fontoam[ ZKN_SOUNDSUB_SEQ_SWITCH_NUM ];

	// リソース
	CLACT_U_RES_OBJ_PTR res_obj[ ZKN_CLACT_RES_OBJ_NUM_DEF ];

	// ディスク部分光らせようパレット
	void* p_pltt_buff;
	NNSG2dPaletteData* p_plt;
	BOOL pltt_anm;	// パレットONしているときTRUE
} ZKN_SOUND_SUB_DRAW;


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
static ZKN_SOUND_SUB_GLB* MakeSoundSubGlb( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_SOUND_SUB_DRAWGLB* MakeSoundSubDrawGlb( int heap, ZKN_SYS_PTR zkn_sys );
static ZKN_EVENT_DATA* MakeSoundSubEvent( int heap, ZKN_SYS_PTR zkn_sys );
static void DeleteSoundSubGlb( ZKN_SOUND_SUB_GLB* p_glb );
static void DeleteSoundSubDrawGlb( ZKN_SOUND_SUB_DRAWGLB* p_glb );
static void DeleteSoundSubEvent( ZKN_EVENT_DATA* p_event );


static int SoundSubEventDataNumGet( void );


//-----------------------------------------------------------------------------
/**
 *		プロセス関係
 */
//-----------------------------------------------------------------------------
static int ZknSoundSubProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknSoundSubProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknSoundSubProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata );
static int ZknSoundSubProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknSoundSubProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );
static int ZknSoundSubProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata );

// フェード処理
static void ZknSoundSubOamFadeInit( ZKN_SOUND_SUB_DRAW* p_draw );
static void ZknSoundSubOamFadeDelete( ZKN_SOUND_SUB_DRAW* p_draw );
static void ZknSoundSubFadeInit( ZKN_SOUND_SUB_DRAW* p_draw, ZKN_SOUND_SUB_DRAWGLB* p_drawglb, const ZKN_SOUND_SUB_GLB* cp_glb, BOOL fadein_out );
static BOOL ZknSoundSubFadeMain( ZKN_SOUND_SUB_DRAW* p_draw, ZKN_SOUND_SUB_DRAWGLB* p_drawglb, const ZKN_SOUND_SUB_GLB* cp_glb, BOOL fadein_out );

// ボタン制御
static void ZknSoundSubButtonMake( ZKN_SOUND_SUB_WORK* p_work, ZKN_SOUND_SUB_GLB* p_glb, int heap );
static void ZknSoundSubButtonMove( ZKN_SOUND_SUB_WORK* p_work, ZKN_SOUND_SUB_GLB* p_glb );
static void ZknSoundSubButtonDelete( ZKN_SOUND_SUB_WORK* p_work );
static void ZknSoundSubButtonCallBack( u32 button_no, u32 event, void* p_work );

// カーソル制御
static void ZknSoundSubCursorMove( ZKN_SOUND_SUB_WORK* p_work, ZKN_SOUND_SUB_GLB* p_glb );
static void ZknSoundSubCursorDrawMove( ZKN_SOUND_SUB_DRAWGLB* p_drawglb, const ZKN_SOUND_SUB_GLB* cp_glb );

static void ZknSoundSubStartButtonCallBack( u32 button_no, u32 event, void* p_work );
static void ZknSoundSubButtonTouch( u32 button_no, ZKN_SOUND_SUB_GLB* p_glb, ZKN_SOUND_SUB_WORK* p_work );
static void ZknSoundSubButtonHold( u32 button_no, ZKN_SOUND_SUB_GLB* p_glb, ZKN_SOUND_SUB_WORK* p_work );
static void ZknSoundSubButtonRelease( u32 button_no, ZKN_SOUND_SUB_GLB* p_glb, ZKN_SOUND_SUB_WORK* p_work );
static void ZknSoundSubButtonSlideOut( u32 button_no, ZKN_SOUND_SUB_GLB* p_glb, ZKN_SOUND_SUB_WORK* p_work );

// 音再生
static void ZknSoundSubSoundStart( ZKN_SOUND_SUB_WORK* p_work, ZKN_SOUND_SUB_GLB* p_glb, int monsno );
static void ZknSoundSubSoundStop( ZKN_SOUND_SUB_WORK* p_work );
static void ZknSoundSubSoundLoop(  ZKN_SOUND_SUB_WORK* p_work, ZKN_SOUND_SUB_GLB* p_glb );
static void ZknSoundSubSoundLoopSet( ZKN_SOUND_SUB_WORK* p_work, BOOL flag );

// ボタンアニメ
static void ZknSoundSubButtonAnimeMain( CLACT_WORK_PTR act, ZKN_SOUND_SUB_ANM_BUTTON* p_anmdata, BOOL now_flg, BOOL next_flg );
static void ZknSoundSubButtonAnimeMain_NO_Loop( CLACT_WORK_PTR act, ZKN_SOUND_SUB_ANM_BUTTON* p_anmdata, BOOL next_flg, int button_event );
static void ZknSoundSubButtonAnimeSeqSet( CLACT_WORK_PTR act, ZKN_SOUND_SUB_ANM_BUTTON* p_anmdata, BOOL flg );

// スイッチ
static void ZknSoundSubSwitchDrawMove( ZKN_SOUND_SUB_DRAW* p_draw, const ZKN_SOUND_SUB_WORK* cp_work );
static void ZknSoundSubStartStopDrawMove( ZKN_SOUND_SUB_DRAW* p_draw, const ZKN_SOUND_SUB_WORK* cp_work );
static void ZknSoundSubLoopDrawMove( ZKN_SOUND_SUB_DRAW* p_draw, const ZKN_SOUND_SUB_WORK* cp_work );

static void ZknSoundSubPitchPanFontDraw( ZKN_SOUND_SUB_DRAW* p_draw );
static void ZknSoundSubPitchPanChorusOnOff( ZKN_SOUND_SUB_WORK* p_work, BOOL flag );
static void ZknSoundSubPitchPanChorusFlagOnOff( ZKN_SOUND_SUB_WORK* p_work, BOOL flag );
static void ZknSoundSubPitchPanChorusNumReset( ZKN_SOUND_SUB_WORK* p_work );
static void ZknSoundSubPitchPanChorusSet( ZKN_SOUND_SUB_WORK* p_work );
static void ZknSoundSubPitchPanAnm( ZKN_SOUND_SUB_DRAW* p_draw, const ZKN_SOUND_SUB_WORK* cp_work );

static void ZknSoundSubChorusSet( int volume );
static void ZknSoundSubPitchSet( int num );

// ダイヤル動作
static void ZknSoundSubDialCalc( ZKN_SOUND_SUB_WORK* p_work );
static void ZknSoundSubDialDivSet( ZKN_SOUND_SUB_WORK* p_work );
static void ZknSoundSubDialNumSet( ZKN_SOUND_SUB_WORK* p_work );
static void ZKnSoundSubDialDrawMove( ZKN_SOUND_SUB_DRAW* p_draw, const ZKN_SOUND_SUB_WORK* cp_work );
static void ZknSoundSubReverbEffectStop( ZKN_SOUND_SUB_WORK* p_work );

// ディスク
static void ZknSoundSubDiskDrawMove( ZKN_SOUND_SUB_DRAW* p_draw, ZKN_SOUND_SUB_DRAWGLB* p_drawglb, const ZKN_SOUND_SUB_WORK* cp_work );

static void ZknSoundSubDiskPitchSet( ZKN_SOUND_SUB_WORK* p_work, int x );
static void ZknSoundSubDiskChorusSet( ZKN_SOUND_SUB_WORK* p_work, int x );
static void ZknSoundSubDiskPanSet( ZKN_SOUND_SUB_WORK* p_work, int x );

// 読み込み
static void ZknSoundSubLoadResource( ZKN_SOUND_SUB_DRAW* p_draw, ZKN_SOUND_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknSoundSubReleaseResource( ZKN_SOUND_SUB_DRAW* p_draw, ZKN_SOUND_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknSoundSubSetUpBg( ZKN_SOUND_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknSoundSubPutDownBg( ZKN_SOUND_SUB_DRAWGLB* p_drawglb );
static void ZknSoundSubLoadOamData( ZKN_SOUND_SUB_DRAW* p_draw, ZKN_SOUND_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknSoundSubReleaseOamData( ZKN_SOUND_SUB_DRAW* p_draw, ZKN_SOUND_SUB_DRAWGLB* p_drawglb );
static void ZknSoundSubAddClact( ZKN_SOUND_SUB_DRAW* p_draw, ZKN_SOUND_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknSoundSubDeleteClact( ZKN_SOUND_SUB_DRAW* p_draw );
static void ZknSoundSubAddFontOam( ZKN_SOUND_SUB_DRAW* p_draw, ZKN_SOUND_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknSoundSubDeleteFontOam( ZKN_SOUND_SUB_DRAW* p_draw, ZKN_SOUND_SUB_DRAWGLB* p_drawglb );

static void ZknSoundSubPlttLoad( ZKN_SOUND_SUB_DRAW* p_draw, ZKN_SOUND_SUB_DRAWGLB* p_drawglb, int heap );
static void ZknSoundSubPlttRelease( ZKN_SOUND_SUB_DRAW* p_draw );
static void ZknSoundSubPlttOn( ZKN_SOUND_SUB_DRAW* p_draw );
static void ZknSoundSubPlttOff( ZKN_SOUND_SUB_DRAW* p_draw );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	なきごえサブ画面　アプリ作成
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
void ZKN_SoundSubAplMake( ZKN_APL_DATA* p_data, ZKN_SYS_PTR zkn_sys, int heap )
{
	ZKN_SOUND_SUB_GLB*	p_glb;
	ZKN_SOUND_SUB_DRAWGLB*	p_drawglb;
	ZKN_EVENT_DATA*	p_event;
	
	p_glb = MakeSoundSubGlb( heap, zkn_sys );
	p_drawglb = MakeSoundSubDrawGlb( heap, zkn_sys );
	p_event = MakeSoundSubEvent( heap, zkn_sys );

	p_data->p_glb_data		= p_glb;
	p_data->p_glb_draw		= p_drawglb;
	p_data->p_event_data	= p_event;
	p_data->event_num		= SoundSubEventDataNumGet();

	p_data->do_func[ ZKN_PROC_FUNC_INIT ] = ZknSoundSubProcDoFuncInit;
	p_data->do_func[ ZKN_PROC_FUNC_MAIN ] = ZknSoundSubProcDoFuncMain;
	p_data->do_func[ ZKN_PROC_FUNC_DELETE ] = ZknSoundSubProcDoFuncDelete;
	p_data->draw_func[ ZKN_PROC_FUNC_INIT ] = ZknSoundSubProcDrawFuncInit;
	p_data->draw_func[ ZKN_PROC_FUNC_MAIN ] = ZknSoundSubProcDrawFuncMain;
	p_data->draw_func[ ZKN_PROC_FUNC_DELETE ] = ZknSoundSubProcDrawFuncDelete;
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
void ZKN_SoundSubAplDelete( ZKN_APL_DATA* p_data )
{
	DeleteSoundSubGlb( p_data->p_glb_data ); 
	DeleteSoundSubDrawGlb( p_data->p_glb_draw ); 
	DeleteSoundSubEvent( p_data->p_event_data );
}


//----------------------------------------------------------------------------
/**
 *	@brief	ピッチ数を取得する
 *
 *	@param	cp_data	アプリケーションデータ
 *
 *	@return	ピッチ数
 */
//-----------------------------------------------------------------------------
int ZKN_SoundSubAplGetPitchNum( const ZKN_APL_DATA* cp_data )
{
	const ZKN_SOUND_SUB_GLB* cp_glb = cp_data->p_glb_data;

	return cp_glb->now_pitch;
}


//-----------------------------------------------------------------------------
/**
 *		プライベート関数
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	なきごえサブ画面　グローバルデータ作成
 *
 *	@param	heap		ヒープ
 *	@param	zkn_sys		図鑑システム
 *
 *	@return	グローバルデータ
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_SOUND_SUB_GLB* MakeSoundSubGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_SOUND_SUB_GLB* p_glb;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_SOUND_SUB_GLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_SOUND_SUB_GLB) );

	// 変数初期化
	// イベントキー
	p_glb->p_event_key = ZKN_SYS_GetEventKeyPtrSub( zkn_sys );		

	// グローバルデータ
	p_glb->p_glb = ZKN_SYS_GetGlbData( zkn_sys );

	// 図鑑コモンアプリグローバルデータ
	p_glb->cp_zukan_common_apl = ZKN_GetAplDataSub( zkn_sys, ZKN_SYS_APLSUB_ZUKAN_COMMON );
	
	return p_glb;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	なきごえサブ画面　グローバルデータ作成
 *
 *	@param	heap		ヒープ
 *	@param	zkn_sys		図鑑システム
 *
 *	@return	グローバルデータ
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_SOUND_SUB_DRAWGLB* MakeSoundSubDrawGlb( int heap, ZKN_SYS_PTR zkn_sys )
{
	ZKN_SOUND_SUB_DRAWGLB* p_glb;
	ZKN_APL_DATA* p_apl;

	p_glb = sys_AllocMemory( heap, sizeof(ZKN_SOUND_SUB_DRAWGLB) );
	GF_ASSERT( p_glb );
	memset( p_glb, 0, sizeof(ZKN_SOUND_SUB_DRAWGLB) );


	// 描画データ
	p_glb->p_drawglb = ZKN_SYS_GetGlbDrawData( zkn_sys );

	return p_glb;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	なきごえサブ画面　イベント作成
 *
 *	@param	heap		使用するヒープ
 *	@param	zkn_sys		図鑑システム
 *
 *	@return	イベントデータ
 *
 *
 */
//-----------------------------------------------------------------------------
static ZKN_EVENT_DATA* MakeSoundSubEvent( int heap, ZKN_SYS_PTR zkn_sys )
{
	return NULL;	// 今はなし
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	なきごえサブ画面　グローバルデータ破棄
 *
 *	@param	p_glb		グローバルデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteSoundSubGlb( ZKN_SOUND_SUB_GLB* p_glb )
{
	GF_ASSERT( p_glb );
	sys_FreeMemoryEz( p_glb );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	なきごえサブ画面　グローバルデータ破棄
 *
 *	@param	p_glb		グローバルデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteSoundSubDrawGlb( ZKN_SOUND_SUB_DRAWGLB* p_glb )
{
	GF_ASSERT( p_glb );
	sys_FreeMemoryEz( p_glb );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	なきごえサブ画面　イベントデータ破棄
 *
 *	@param	p_event	イベントデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void DeleteSoundSubEvent( ZKN_EVENT_DATA* p_event )
{
	// 今はなし
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	なきごえサブ画面アプリ　イベント数取得
 *	
 *	@param	none	
 *
 *	@return	なきごえサブ画面アプリ　イベント数
 *
 *
 */
//-----------------------------------------------------------------------------
static int SoundSubEventDataNumGet( void )
{
	return ZKN_SOUND_SUB_EVENT_NUM;
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
static int ZknSoundSubProcDoFuncInit( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_SOUND_SUB_GLB* p_glb = p_glbdata;
	ZKN_SOUND_SUB_WORK* p_work = p_dodata->p_work;
	int i;
	int monsno = ZKN_GLBDATA_PokeMonsNoGet( p_glb->p_glb );

	// ワークの作成
	p_work = sys_AllocMemory( p_dodata->heap, sizeof(ZKN_SOUND_SUB_WORK) );
	memset( p_work, 0, sizeof(ZKN_SOUND_SUB_WORK) );


	// ボタンを作成
	ZknSoundSubButtonMake( p_work, p_glb, p_dodata->heap );

	// ボタンの状態を１回設定
	// ボタン動作
	ZknSoundSubButtonMove( p_work, p_glb );

	// サウンドデータ取得
	p_work->cp_snd_data = Snd_ZukanWaveDataSet( monsno );	


	p_dodata->p_work = p_work;
	
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
static int ZknSoundSubProcDoFuncMain( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{

	ZKN_SOUND_SUB_GLB* p_glb = p_glbdata;
	ZKN_SOUND_SUB_WORK* p_work = p_dodata->p_work;
	
	// 終了へ
	if( p_dodata->end_req == TRUE ){
		ZknSoundSubSoundStop( p_work );
		// リバーブフィルターを止める
		ZknSoundSubReverbEffectStop( p_work );
		return ZKN_PROC_TRUE;
	}

	// lock
	if( p_dodata->lock == TRUE ){
		return ZKN_PROC_FALSE;
	}

	// 現在再生中のピッチを取得
	p_glb->now_pitch = p_work->pitch_num;

	// 動作チェック
	if( ZKN_ZukanCommonSubMoveFlagGet( p_glb->cp_zukan_common_apl ) ){
		// 再生中かチェック
		if( Snd_PMVoicePlayCheck() == FALSE ){
			// ループモードではないなら停止にする
			if( p_work->loop == FALSE ){
				ZknSoundSubSoundStop( p_work );
			}
		}

		// ボタン動作
		ZknSoundSubButtonMove( p_work, p_glb );
		
		// カーソル動作
		// カーソル動作有効で、サブアプリにカーソル動作が許されているときのみ
		if( ZKN_ZukanCommonSubCursorFlagGet( p_glb->cp_zukan_common_apl ) &&
			ZKN_GLBDATA_TouchCursorFlagGet( p_glb->p_glb ) ){

			ZknSoundSubCursorMove( p_work, p_glb );
		}
		

		// ループモード時の処理
		if( p_work->loop && p_work->sound_play ){
			ZknSoundSubSoundLoop( p_work, p_glb );
		}

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
static int ZknSoundSubProcDoFuncDelete( ZKN_PROC_DO_DATA* p_dodata, void* p_glbdata )
{
	ZKN_SOUND_SUB_GLB* p_glb = p_glbdata;
	ZKN_SOUND_SUB_WORK* p_work = p_dodata->p_work;

	// ボタン破棄
	ZknSoundSubButtonDelete( p_work );

	// ワーク破棄
	sys_FreeMemoryEz( p_work );

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
static int ZknSoundSubProcDrawFuncInit( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_SOUND_SUB_GLB* cp_dataglb = cp_glbdata;
	const ZKN_SOUND_SUB_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_SOUND_SUB_DRAWGLB*	p_drawglb = p_glbdraw;
	ZKN_SOUND_SUB_DRAW*		p_drawwork = p_drawdata->p_work;

	switch( p_drawdata->seq ){
	case ZKN_SOUNDSUB_SEQINIT_ALLOC:
		p_drawdata->p_work = sys_AllocMemory( p_drawdata->heap, sizeof(ZKN_SOUND_SUB_DRAW) );
		memset( p_drawdata->p_work, 0, sizeof(ZKN_SOUND_SUB_DRAW) );
		p_drawdata->seq++;
		break;
		
	case ZKN_SOUNDSUB_SEQINIT_LOAD:
		// Resource読み込み
		ZknSoundSubLoadResource( p_drawwork, p_drawglb, p_drawdata->heap );
		// フェード処理
		ZknSoundSubFadeInit( p_drawwork, p_drawglb, cp_dataglb, TRUE );
		
		p_drawdata->seq++;
		break;
		
	case ZKN_SOUNDSUB_SEQINIT_FADEIN:
		
		if( ZknSoundSubFadeMain( p_drawwork, p_drawglb, cp_dataglb, TRUE ) ){
			p_drawdata->seq++;
		}
		break;
		
	case ZKN_SOUNDSUB_SEQINIT_END:
		// カーソルアニメ開始
		ZKN_UTIL_CursorSetAnimeStopFlag( &p_drawglb->p_drawglb->cursor, FALSE );
		return ZKN_PROC_TRUE;
		
	default:
		break;
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
static int ZknSoundSubProcDrawFuncMain( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_SOUND_SUB_GLB* cp_dataglb = cp_glbdata;
	const ZKN_SOUND_SUB_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_SOUND_SUB_DRAWGLB*	p_drawglb = p_glbdraw;
	ZKN_SOUND_SUB_DRAW*		p_drawwork = p_drawdata->p_work;

	// 動作チェック
	if( ZKN_ZukanCommonSubMoveFlagGet( cp_dataglb->cp_zukan_common_apl ) ){

		// スイッチ動作
		ZknSoundSubSwitchDrawMove( p_drawwork, cp_datawork );

		// 再生ストップ描画
		ZknSoundSubStartStopDrawMove( p_drawwork, cp_datawork );

		// ループ描画
		ZknSoundSubLoopDrawMove( p_drawwork, cp_datawork );

		// ダイアル描画
		ZKnSoundSubDialDrawMove( p_drawwork, cp_datawork );

		// ディスク
		ZknSoundSubDiskDrawMove( p_drawwork, p_drawglb, cp_datawork );

		// スイッチ文字
		ZknSoundSubPitchPanFontDraw( p_drawwork );

		// ピッチパン部分パレットアニメ
		ZknSoundSubPitchPanAnm( p_drawwork, cp_datawork );

		// カーソル
		ZknSoundSubCursorDrawMove( p_drawglb, cp_dataglb );
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
static int ZknSoundSubProcDrawFuncDelete( void* p_glbdraw, ZKN_PROC_DRAW_DATA* p_drawdata, const void* cp_glbdata, const ZKN_PROC_DO_DATA* cp_dodata )
{
	const ZKN_SOUND_SUB_GLB* cp_dataglb = cp_glbdata;
	const ZKN_SOUND_SUB_WORK* cp_datawork = cp_dodata->p_work;
	ZKN_SOUND_SUB_DRAWGLB*	p_drawglb = p_glbdraw;
	ZKN_SOUND_SUB_DRAW*		p_drawwork = p_drawdata->p_work;

	switch( p_drawdata->seq ){
	case ZKN_SOUNDSUB_SEQDELETE_FADEOUT_INIT:
		// カーソルアニメ停止
		ZKN_UTIL_CursorSetAnimeStopFlag( &p_drawglb->p_drawglb->cursor, TRUE );

		// OFFパレットを設定
		ZknSoundSubPlttOff( p_drawwork );
		
		// フェード処理
		ZknSoundSubFadeInit( p_drawwork, p_drawglb, cp_dataglb, FALSE );
		p_drawdata->seq++;
		break;
		
	case ZKN_SOUNDSUB_SEQDELETE_FADEOUT:
		if( ZknSoundSubFadeMain( p_drawwork, p_drawglb, cp_dataglb, FALSE ) ){
			p_drawdata->seq++;
		}
		break;

	case ZKN_SOUNDSUB_SEQDELETE_RELEASE:
		// Resource読み込み
		ZknSoundSubReleaseResource( p_drawwork, p_drawglb, p_drawdata->heap );
		p_drawdata->seq++;
		break;
		
	case ZKN_SOUNDSUB_SEQDELETE_FREE:
		sys_FreeMemoryEz( p_drawdata->p_work );
		p_drawdata->seq++;
		break;
		
		
	case ZKN_SOUNDSUB_SEQDELETE_END:
		return ZKN_PROC_TRUE;
		
	default:
		break;
	}
	return ZKN_PROC_FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAMフェード処理	初期化
 *
 *	@param	p_draw	描画ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubOamFadeInit( ZKN_SOUND_SUB_DRAW* p_draw )
{
	CLACT_ObjModeSet( p_draw->dial, GX_OAM_MODE_XLU );
	CLACT_ObjModeSet( p_draw->pich_switch, GX_OAM_MODE_XLU );
	CLACT_ObjModeSet( p_draw->startstop, GX_OAM_MODE_XLU );
	CLACT_ObjModeSet( p_draw->loop, GX_OAM_MODE_XLU );

	FONTOAM_ObjModeSet( p_draw->p_fontoam[ ZKN_SOUNDSUB_SEQ_SWITCH_PICH ]->p_fontoam, GX_OAM_MODE_XLU );
	FONTOAM_ObjModeSet( p_draw->p_fontoam[ ZKN_SOUNDSUB_SEQ_SWITCH_PAN ]->p_fontoam, GX_OAM_MODE_XLU );
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAMフェード処理　後処理
 *
 *	@param	p_draw 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubOamFadeDelete( ZKN_SOUND_SUB_DRAW* p_draw )
{
	CLACT_ObjModeSet( p_draw->dial, GX_OAM_MODE_NORMAL );
	CLACT_ObjModeSet( p_draw->pich_switch, GX_OAM_MODE_NORMAL );
	CLACT_ObjModeSet( p_draw->startstop, GX_OAM_MODE_NORMAL );
	CLACT_ObjModeSet( p_draw->loop, GX_OAM_MODE_NORMAL );

	FONTOAM_ObjModeSet( p_draw->p_fontoam[ ZKN_SOUNDSUB_SEQ_SWITCH_PICH ]->p_fontoam, GX_OAM_MODE_NORMAL );
	FONTOAM_ObjModeSet( p_draw->p_fontoam[ ZKN_SOUNDSUB_SEQ_SWITCH_PAN ]->p_fontoam, GX_OAM_MODE_NORMAL );
}

//----------------------------------------------------------------------------
/**
 *	@brief	サブ画面フェード処理
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb		描画グローバル
 *	@param	cp_glb		グローバル
 *	@param	fadein_out	フェードイン　TRUE　アウト FALSE	
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubFadeInit( ZKN_SOUND_SUB_DRAW* p_draw, ZKN_SOUND_SUB_DRAWGLB* p_drawglb, const ZKN_SOUND_SUB_GLB* cp_glb, BOOL fadein_out )
{
	// 半透明OAM設定
	ZknSoundSubOamFadeInit( p_draw );

	// ブライトネス処理を行ってよいか
	if( ZKN_ZukanCommonSubBrightnessOnFlagGet( cp_glb->cp_zukan_common_apl ) ){
		if( fadein_out ){
			// フェードイン
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade_sub, ZKN_SOUND_FADE_SYNC, 
					BRIGHTNESS_BLACK, BRIGHTNESS_NORMAL, 0, 16, ZKN_SOUNDSUB_FADE_PLANEMSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_SUB );
		}else{
			// フェードアウト
			ZKN_GLB_ChangeFadeRequest( &p_drawglb->p_drawglb->fade_sub, ZKN_SOUND_FADE_SYNC, 
					BRIGHTNESS_NORMAL, BRIGHTNESS_BLACK, 16, 0, ZKN_SOUNDSUB_FADE_PLANEMSK, ZKN_BRIGHTNESS_MSK_PLANE2DEF, ZKN_UTIL_FADE_SUB );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	フェード処理　メイン
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb		描画グローバル
 *	@param	cp_glb		グローバル
 *	@param	fadein_out	フェードイン　TRUE　アウト　FALSE
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
static BOOL ZknSoundSubFadeMain( ZKN_SOUND_SUB_DRAW* p_draw, ZKN_SOUND_SUB_DRAWGLB* p_drawglb, const ZKN_SOUND_SUB_GLB* cp_glb, BOOL fadein_out )
{
	BOOL check;

	// ブライトネスしよう許可でてるかチェック
	if( ZKN_ZukanCommonSubBrightnessOnFlagGet( cp_glb->cp_zukan_common_apl ) ){
		check = ZKN_GLB_ChangeFadeMain( &p_drawglb->p_drawglb->fade_sub );
	}else{
//		check = ZKN_GLB_ChangeFadeEndCheck( &p_drawglb->p_drawglb->fade_sub );
		check = IsFinishedBrightnessChg( MASK_SUB_DISPLAY );
	}

	// 終わったら終了処理
	if( check ){
		if( fadein_out ){
			// 半透明OAM破棄
			ZknSoundSubOamFadeDelete( p_draw );
		}

		return TRUE;
	}

	return FALSE;
}



//----------------------------------------------------------------------------
/**
 *	@brief	ボタン作成関数
 *
 *	@param	p_work	ワーク
 *	@param	p_glb	グローバル
 *	@param	heap	ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubButtonMake( ZKN_SOUND_SUB_WORK* p_work, ZKN_SOUND_SUB_GLB* p_glb, int heap )
{
	// テーブル作成
	p_work->hit_tbl = sys_AllocMemory( heap, sizeof(TP_HIT_TBL) * ZKN_SOUNDSUB_BUTTON_NUM );
	p_work->p_sub_hit_tbl = sys_AllocMemory( heap, sizeof(TP_HIT_TBL) * ZKN_SOUNDSUB_BUTTON_SUB_NUM );

	// テーブルデータ設定
	ZKN_UTIL_HitTblDataSet( &p_work->hit_tbl[ ZKN_SOUNDSUB_BUTTON_SWITCH ],
			ZKN_SOUNDSUB_BUTTON_SWITCH_Y - (ZKN_SOUNDSUB_BUTTON_SWITCH_SIZYH),
			ZKN_SOUNDSUB_BUTTON_SWITCH_Y + (ZKN_SOUNDSUB_BUTTON_SWITCH_SIZYH),
			ZKN_SOUNDSUB_BUTTON_SWITCH_X - (ZKN_SOUNDSUB_BUTTON_SWITCH_SIZXH),
			ZKN_SOUNDSUB_BUTTON_SWITCH_X + (ZKN_SOUNDSUB_BUTTON_SWITCH_SIZXH) );

	p_work->hit_tbl[ ZKN_SOUNDSUB_BUTTON_DIAL ].circle.code = TP_USE_CIRCLE;
	p_work->hit_tbl[ ZKN_SOUNDSUB_BUTTON_DIAL ].circle.x = ZKN_SOUNDSUB_BUTTON_DIAL_X;
	p_work->hit_tbl[ ZKN_SOUNDSUB_BUTTON_DIAL ].circle.y = ZKN_SOUNDSUB_BUTTON_DIAL_Y;
	p_work->hit_tbl[ ZKN_SOUNDSUB_BUTTON_DIAL ].circle.r = ZKN_SOUNDSUB_BUTTON_DIAL_R;


	p_work->hit_tbl[ ZKN_SOUNDSUB_BUTTON_DISK ].circle.code = TP_USE_CIRCLE;
	p_work->hit_tbl[ ZKN_SOUNDSUB_BUTTON_DISK ].circle.x = ZKN_SOUNDSUB_DISK_BG_CENTER_X;
	p_work->hit_tbl[ ZKN_SOUNDSUB_BUTTON_DISK ].circle.y = ZKN_SOUNDSUB_DISK_BG_CENTER_Y + ZKN_SOUNDSUB_DISK_BG_CENTER_T_OFS_Y;
	p_work->hit_tbl[ ZKN_SOUNDSUB_BUTTON_DISK ].circle.r = ZKN_SOUNDSUB_DISK_BG_R;


	// サブボタンマネージャ用
	ZKN_UTIL_HitTblDataSet( &p_work->p_sub_hit_tbl[ ZKN_SOUNDSUB_BUTTON_SUB_STARTSTOP ],
			ZKN_SOUNDSUB_BUTTON_STARTSTOP_Y - (ZKN_SOUNDSUB_BUTTON_STARTSTOP_SIZYH),
			ZKN_SOUNDSUB_BUTTON_STARTSTOP_Y + (ZKN_SOUNDSUB_BUTTON_STARTSTOP_SIZYH),
			ZKN_SOUNDSUB_BUTTON_STARTSTOP_X - (ZKN_SOUNDSUB_BUTTON_STARTSTOP_SIZXH),
			ZKN_SOUNDSUB_BUTTON_STARTSTOP_X + (ZKN_SOUNDSUB_BUTTON_STARTSTOP_SIZXH) );

	ZKN_UTIL_HitTblDataSet( &p_work->p_sub_hit_tbl[ ZKN_SOUNDSUB_BUTTON_SUB_LOOP ],
			ZKN_SOUNDSUB_BUTTON_LOOP_Y - (ZKN_SOUNDSUB_BUTTON_LOOP_SIZYH),
			ZKN_SOUNDSUB_BUTTON_LOOP_Y + (ZKN_SOUNDSUB_BUTTON_LOOP_SIZYH),
			ZKN_SOUNDSUB_BUTTON_LOOP_X - (ZKN_SOUNDSUB_BUTTON_LOOP_SIZXH),
			ZKN_SOUNDSUB_BUTTON_LOOP_X + (ZKN_SOUNDSUB_BUTTON_LOOP_SIZXH) );

	p_work->callcack.p_glb = p_glb;
	p_work->callcack.p_work = p_work;


	// ボタンマネージャ作成
	p_work->p_button_man = BMN_Create( 
			p_work->hit_tbl,
			ZKN_SOUNDSUB_BUTTON_NUM,
			ZknSoundSubButtonCallBack,
			&p_work->callcack,
			heap );

	// 再生ボタン用マネージャ
	p_work->p_sub_button_man = BMN_Create( 
			p_work->p_sub_hit_tbl,
			ZKN_SOUNDSUB_BUTTON_SUB_NUM,
			ZknSoundSubStartButtonCallBack,
			&p_work->callcack,
			heap );
	
}

//----------------------------------------------------------------------------
/**
 *	@brief	ボタン動作処理
 *
 *	@param	p_work	ワーク
 *	@param	p_glb	グローバルデータ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubButtonMove( ZKN_SOUND_SUB_WORK* p_work, ZKN_SOUND_SUB_GLB* p_glb )
{
	int i;
	// ボタンイベントを格納
	for( i=0; i<ZKN_SOUNDSUB_BUTTON_SUB_NUM; i++ ){
		p_work->sub_button_event[ i ] = ZKN_SOUNDDUB_BUTTON_START_NOTOUCH;
	}
	
	BMN_Main( p_work->p_button_man );
	BMN_Main( p_work->p_sub_button_man );
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
static void ZknSoundSubButtonDelete( ZKN_SOUND_SUB_WORK* p_work )
{
	BMN_Delete( p_work->p_button_man );
	BMN_Delete( p_work->p_sub_button_man );

	// テーブルワーク破棄
	sys_FreeMemoryEz( p_work->hit_tbl );
	p_work->hit_tbl = NULL;
	sys_FreeMemoryEz( p_work->p_sub_hit_tbl );
	p_work->p_sub_hit_tbl = NULL;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ボタンコールバック関数
 *
 *	@param	button_no	ボタンナンバー
 *	@param	event		ボタンイベントタイプ
 *	@param	p_work		ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubButtonCallBack( u32 button_no, u32 event, void* p_work )
{
	ZKN_SOUND_BUTTON_CALLBACK* p_work_data = p_work;
	ZKN_SOUND_SUB_GLB* p_glb = p_work_data->p_glb;
	ZKN_SOUND_SUB_WORK* p_subwork = p_work_data->p_work;

	switch( event ){
	case BMN_EVENT_TOUCH:
		ZknSoundSubButtonTouch( button_no, p_glb, p_subwork );
		break;

	case BMN_EVENT_HOLD:
		ZknSoundSubButtonHold( button_no, p_glb, p_subwork );
		break;

	case BMN_EVENT_RELEASE:	
		ZknSoundSubButtonRelease( button_no, p_glb, p_subwork );
		break;

	case BMN_EVENT_SLIDEOUT:
		ZknSoundSubButtonSlideOut( button_no, p_glb, p_subwork );
		break;
		
	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	再生ボタンコールバック関数
 *
 *	@param	button_no	ボタンナンバー
 *	@param	event		ボタンイベントタイプ
 *	@param	p_work		ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubStartButtonCallBack( u32 button_no, u32 event, void* p_work )
{
	ZKN_SOUND_BUTTON_CALLBACK* p_work_data = p_work;
	ZKN_SOUND_SUB_GLB* p_glb = p_work_data->p_glb;
	ZKN_SOUND_SUB_WORK* p_subwork = p_work_data->p_work;
	int monsno = ZKN_GLBDATA_PokeMonsNoGet( p_glb->p_glb );

	// ボタンイベント設定
	p_subwork->sub_button_event[ button_no ] = event;

	switch( event ){
	case BMN_EVENT_TOUCH:
		p_subwork->start_touch_on = FALSE;
		break;

	case BMN_EVENT_HOLD:
		if( p_subwork->start_touch_on == FALSE ){
			p_subwork->start_touch_on = TRUE;
			switch( button_no ){
			case ZKN_SOUNDSUB_BUTTON_SUB_STARTSTOP:
				// ループモードの時の処理
				if( p_subwork->loop == TRUE ){
					// 再生停止設定
					if( p_subwork->sound_play == FALSE ){
						ZknSoundSubSoundStart( p_subwork, p_glb, monsno );
					}else{
						// 停止
						ZknSoundSubSoundStop( p_subwork );
					}
				}else{
					// なっていたらとめる
					if( p_subwork->sound_play == TRUE ){
						Snd_PMVoiceStop(0);
					}	
					
					ZknSoundSubSoundStart( p_subwork, p_glb, monsno );
				}
				break;

			// ループボタン
			case ZKN_SOUNDSUB_BUTTON_SUB_LOOP:

				// キー操作でのボタンアニメOFF
				// 再生アニメを初期化する
				p_subwork->sound_play_button_cursor = 2;

				ZknSoundSubSoundLoopSet( p_subwork, p_subwork->loop ^ 1 );
				// ボタンにタッチ
				Snd_SePlay( ZKN_SND_BUTTON );
				break;

			default:
				break;
			}
		}
		break;

	case BMN_EVENT_RELEASE:	
		break;

	case BMN_EVENT_SLIDEOUT:
		break;
		
	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ボタンタッチ時関数
 *
 *	@param	button_no		ボタンナンバー
 *	@param	p_glb			グローバルデータ
 *	@param	p_work			ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubButtonTouch( u32 button_no, ZKN_SOUND_SUB_GLB* p_glb, ZKN_SOUND_SUB_WORK* p_work )
{

	switch( button_no ){
	case ZKN_SOUNDSUB_BUTTON_SWITCH:
		// 再生中は変更できないので停止
		if( p_work->sound_play == TRUE ){
			ZknSoundSubSoundStop( p_work );
		}

		// サンプリング開始座標を取得
		p_work->pitch_switch_touch_start_x = sys.tp_x;
		p_work->pitch_switch_touch = TRUE;
		
		break;
		
	case ZKN_SOUNDSUB_BUTTON_DIAL:
		// 再生中は変更できないので停止
		if( p_work->sound_play == TRUE ){
			ZknSoundSubSoundStop( p_work );
		}

		// サンプリング開始座標を取得
		p_work->dial_touch = TRUE;
		p_work->dial_start_x = sys.tp_x;
		p_work->dial_start_y = sys.tp_y;
		
		break;
		
	case ZKN_SOUNDSUB_BUTTON_DISK:

		// 再生中かチェック
		if( p_work->sound_play ){

			// 再生ボタンループにヒットしているかチェック
			p_work->hit_start_stop_flag = GF_TP_SingleHitCont( &p_work->p_sub_hit_tbl[ZKN_SOUNDSUB_BUTTON_SUB_STARTSTOP] );
			p_work->hit_start_stop_flag |= GF_TP_SingleHitCont( &p_work->p_sub_hit_tbl[ZKN_SOUNDSUB_BUTTON_SUB_LOOP] );

		}else{

			// これをTRUEにすることにより
			// ディスク面をタッチした時の処理を
			// 行わなくする
			p_work->hit_start_stop_flag = TRUE;
		}

		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ボタンHold
 *
 *	@param	button_no
 *	@param	p_glb
 *	@param	p_work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubButtonHold( u32 button_no, ZKN_SOUND_SUB_GLB* p_glb, ZKN_SOUND_SUB_WORK* p_work )
{
	int touch_move;

	switch( button_no ){
	case ZKN_SOUNDSUB_BUTTON_SWITCH:
		// タッチフラグが立っているときのみ
		if( p_work->pitch_switch_touch == TRUE ){

			// サンプリング動作座標を計算
			touch_move = sys.tp_x - p_work->pitch_switch_touch_start_x;

			// 今のスイッチ状態から切り替えるかチェックする
			if( p_work->pitch_switch_flag == ZKN_SOUNDSUB_SEQ_SWITCH_PICH ){
				// 切り替えチェック
				if( ZKN_SOUNDSUB_SWITCH_MOVE_OK_DIS <= touch_move ){
					p_work->pitch_switch_flag = ZKN_SOUNDSUB_SEQ_SWITCH_PAN;
					p_work->pitch_switch_touch_start_x = sys.tp_x;	// タッチ開始をまた設定

					// ボタンにタッチ
					Snd_SePlay( ZKN_SND_SWITCH );
				}
			}else{

				// 切り替えチェック
				if( -ZKN_SOUNDSUB_SWITCH_MOVE_OK_DIS >= touch_move ){
					p_work->pitch_switch_flag = ZKN_SOUNDSUB_SEQ_SWITCH_PICH;
					p_work->pitch_switch_touch_start_x = sys.tp_x;	// タッチ開始をまた設定

					// ボタンにタッチ
					Snd_SePlay( ZKN_SND_SWITCH );
				}
			}
		}
		break;
		
	case ZKN_SOUNDSUB_BUTTON_DIAL:
		// 再生中は変更できない
		if( p_work->dial_touch == TRUE ){

			// ダイヤル角度計算
			ZknSoundSubDialCalc( p_work );

			// 現在分割位置を設定
			ZknSoundSubDialDivSet( p_work );

			// リバーブフィルター設定による値設定
			ZknSoundSubDialNumSet( p_work );

			// 今の値格納
			p_work->dial_start_x = sys.tp_x;
			p_work->dial_start_y = sys.tp_y;
		}
		break;
		
	case ZKN_SOUNDSUB_BUTTON_DISK:


		// 再生ボタンに触っていないとき
		if( p_work->hit_start_stop_flag == FALSE  ){

			// 再生中で無くなったらもう処理を行わないようにする
			if( p_work->sound_play == FALSE ){
				p_work->hit_start_stop_flag = TRUE;

				// 設定中フラグを落とす
				ZknSoundSubPitchPanChorusOnOff( p_work, FALSE );
			}else{
			
				// センターから上か下かで処理が分岐
				if( sys.tp_y < ZKN_SOUNDSUB_DISK_BG_CENTER_Y + ZKN_SOUNDSUB_DISK_BG_CENTER_OFS_Y ){
					// ピッチORパンの設定
					if( p_work->pitch_switch_flag == ZKN_SOUNDSUB_SEQ_SWITCH_PICH ){
//						ZknSoundSubDiskPitchSet( p_work, sys.tp_x );
						ZknSoundSubDiskChorusSet( p_work, sys.tp_x );
					}else{
						ZknSoundSubDiskPanSet( p_work, sys.tp_x );
					}
					p_work->pitch_num = 0;	// ピッチの値は初期化
					// 設定中フラグを立てる
					ZknSoundSubPitchPanChorusOnOff( p_work, TRUE );
				}else{

					// 設定中フラグを落とす
					ZknSoundSubPitchPanChorusFlagOnOff( p_work, FALSE );

					// ピッチの値を最低にする
					p_work->pitch_num = SND_ZUKAN_PITCH_MIN;
				}
			}

			// ピッチパンの値を設定
			ZknSoundSubPitchPanChorusSet( p_work );
		}
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ボタンRelease
 *
 *	@param	button_no
 *	@param	p_glb
 *	@param	p_work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubButtonRelease( u32 button_no, ZKN_SOUND_SUB_GLB* p_glb, ZKN_SOUND_SUB_WORK* p_work )
{
		
	switch( button_no ){
	case ZKN_SOUNDSUB_BUTTON_SWITCH:
		p_work->pitch_switch_touch = FALSE;
		break;
		
	case ZKN_SOUNDSUB_BUTTON_DIAL:
		p_work->dial_rota = p_work->dial_div * ZKN_SOUNDSUB_DIAL_MIN_CUT_NUM;
		
		p_work->dial_touch = FALSE;
		break;
		
	case ZKN_SOUNDSUB_BUTTON_DISK:
		// 再生ボタンに触っていないとき
		if( p_work->hit_start_stop_flag == FALSE  ){

			// 設定中フラグを落とす
			ZknSoundSubPitchPanChorusOnOff( p_work, FALSE );
			
			// ピッチパンの値を設定
			ZknSoundSubPitchPanChorusSet( p_work );
		}
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ボタンスライドアウト
 *
 *	@param	button_no
 *	@param	p_glb
 *	@param	p_work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubButtonSlideOut( u32 button_no, ZKN_SOUND_SUB_GLB* p_glb, ZKN_SOUND_SUB_WORK* p_work )
{
	switch( button_no ){
	case ZKN_SOUNDSUB_BUTTON_SWITCH:
		p_work->pitch_switch_touch = FALSE;
		break;
		
	case ZKN_SOUNDSUB_BUTTON_DIAL:
		p_work->dial_rota = p_work->dial_div * ZKN_SOUNDSUB_DIAL_MIN_CUT_NUM;
		p_work->dial_touch = FALSE;
		break;
		
	case ZKN_SOUNDSUB_BUTTON_DISK:
		// 再生ボタンに触っていないとき
		if( p_work->hit_start_stop_flag == FALSE  ){

			// 設定中フラグを落とす
			ZknSoundSubPitchPanChorusOnOff( p_work, FALSE );
			
			// ピッチパンの値を設定
			ZknSoundSubPitchPanChorusSet( p_work );
		}
		break;

	default:
		break;
	}
}




//----------------------------------------------------------------------------
/**
 *	@brief	グラフィック初期化処理
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubLoadResource( ZKN_SOUND_SUB_DRAW* p_draw, ZKN_SOUND_SUB_DRAWGLB* p_drawglb, int heap )
{
	// 背景
	ZknSoundSubSetUpBg( p_drawglb, heap );

	// OAM
	ZknSoundSubLoadOamData( p_draw, p_drawglb, heap );

	// セルアクター登録
	ZknSoundSubAddClact( p_draw, p_drawglb, heap );

	// FONTOAM登録
	ZknSoundSubAddFontOam( p_draw, p_drawglb, heap );

	// アニメ用パレット読み込み
	ZknSoundSubPlttLoad( p_draw, p_drawglb, heap );

}

//----------------------------------------------------------------------------
/**
 *	@brief	グラフィック破棄処理
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubReleaseResource( ZKN_SOUND_SUB_DRAW* p_draw, ZKN_SOUND_SUB_DRAWGLB* p_drawglb, int heap )
{
	int i;
	
	// セルアクター破棄
	ZknSoundSubDeleteClact( p_draw );

	// FONTOAM破棄
	ZknSoundSubDeleteFontOam( p_draw, p_drawglb );

	// OAM
	ZknSoundSubReleaseOamData( p_draw, p_drawglb );

	// 背景初期化
	ZknSoundSubPutDownBg( p_drawglb );

	// アニメ用パレット破棄
	ZknSoundSubPlttRelease( p_draw );
}

//----------------------------------------------------------------------------
/**
 *	@brief	BG面セットアップ
 *
 *	@param	p_drawglb	描画グローバル
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubSetUpBg( ZKN_SOUND_SUB_DRAWGLB* p_drawglb, int heap )
{
	void* buff;
	NNSG2dScreenData* p_scrn;

	// キャラクタデータ転送
	ZKN_GLBDATA_BgCharSet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_sub_lzh_NCGR, p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_S, 0, 0, TRUE, heap );

	// スクリーンデータ読み込み
	buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_voice_bg_sub1_lzh_NSCR, TRUE, &p_scrn, heap );
	
	// スクリーンデータ書き込み
	GF_BGL_ScrWrite( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_S,
			p_scrn->rawData, 0, 0,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	sys_FreeMemoryEz( buff );

	// スクリーンデータ転送
	GF_BGL_LoadScreenV_Req(p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_S );


	// ディスク
	// キャラクタデータ転送
	ZKN_GLBDATA_BgCharSet( p_drawglb->p_drawglb, NARC_zukan_zkn_voice_disk_lzh_NCGR, p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_AFFINE_S, 0, 0, TRUE, heap );

	// スクリーンデータ読み込み
	buff = ZKN_GLBDATA_ScrnDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_voice_disk_lzh_NSCR, TRUE, &p_scrn, heap );
	
	// スクリーンデータ書き込み
	GF_BGL_ScrWrite( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_AFFINE_S,
			p_scrn->rawData, 0, 0,
			p_scrn->screenWidth / 8, p_scrn->screenHeight / 8 );

	sys_FreeMemoryEz( buff );

	// スクリーンデータ転送
	GF_BGL_LoadScreenV_Req(p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_AFFINE_S );

	// ディスク座標とBG優先順位設定
	GF_BGL_ScrollSet( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_AFFINE_S, GF_BGL_SCROLL_X_SET, ZKN_SOUNDSUB_DISK_BG_X );
	GF_BGL_ScrollSet( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_AFFINE_S, GF_BGL_SCROLL_Y_SET, ZKN_SOUNDSUB_DISK_BG_Y );
	GF_BGL_PrioritySet( ZKN_BG_FRM_AFFINE_S, 3 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	BG面最終処理
 *
 *	@param	p_drawglb 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubPutDownBg( ZKN_SOUND_SUB_DRAWGLB* p_drawglb )
{
	// スクリーン初期化
	GF_BGL_ScrClear( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_BACK_S );
	GF_BGL_ScrClear( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_AFFINE_S );

	GF_BGL_PrioritySet( ZKN_BG_FRM_AFFINE_S, 1 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAMリソース読み込み
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubLoadOamData( ZKN_SOUND_SUB_DRAW* p_draw, ZKN_SOUND_SUB_DRAWGLB* p_drawglb, int heap )
{
	ZKN_GLB_DRAWDATA* p_draw_glb = p_drawglb->p_drawglb;
	ARCHANDLE* p_handle = ZKN_GLBDATA_ArcHandlGet( p_drawglb->p_drawglb );
	
	// キャラクタデータ読み込み
	p_draw->res_obj[ CLACT_U_CHAR_RES ] = CLACT_U_ResManagerResAddArcChar_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ], p_handle,
			NARC_zukan_zkn_voice_oam_sub_lzh_NCGR, TRUE,
			NARC_zukan_zkn_voice_oam_sub_lzh_NCGR + ZKN_SOUND_SUB_RES_ID,
			NNS_G2D_VRAM_TYPE_2DSUB, heap );
	// 転送
	CLACT_U_CharManagerSetAreaCont( p_draw->res_obj[ CLACT_U_CHAR_RES ] );
	// グラフィックデータだけ破棄
	CLACT_U_ResManagerResOnlyDelete( p_draw->res_obj[ CLACT_U_CHAR_RES ] );

	// パレットデータ読み込み
	p_draw->res_obj[ CLACT_U_PLTT_RES ] = CLACT_U_ResManagerResAddArcPltt_ArcHandle( 
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ], p_handle,
			NARC_zukan_zkn_voice_oam_sub_NCLR, FALSE, 
			NARC_zukan_zkn_voice_oam_sub_NCLR + ZKN_SOUND_SUB_RES_ID, 
			NNS_G2D_VRAM_TYPE_2DSUB, 
			ZKN_SOUNDSUB_PLTT_LOAD, heap );
	// 転送
	CLACT_U_PlttManagerSetCleanArea( p_draw->res_obj[ CLACT_U_PLTT_RES ] );	
	// グラフィックデータだけ破棄
	CLACT_U_ResManagerResOnlyDelete( p_draw->res_obj[ CLACT_U_PLTT_RES ] );


	// セルデータ読み込み
	p_draw->res_obj[ CLACT_U_CELL_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ], p_handle,
			NARC_zukan_zkn_voice_oam_sub_lzh_NCER, TRUE,
			NARC_zukan_zkn_voice_oam_sub_lzh_NCER + ZKN_SOUND_SUB_RES_ID,
			CLACT_U_CELL_RES, heap );

	// セルアニメデータ読み込み
	p_draw->res_obj[ CLACT_U_CELLANM_RES ] = CLACT_U_ResManagerResAddArcKindCell_ArcHandle(
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ], p_handle, 
			NARC_zukan_zkn_voice_oam_sub_lzh_NANR, TRUE,
			NARC_zukan_zkn_voice_oam_sub_lzh_NANR + ZKN_SOUND_SUB_RES_ID,
			CLACT_U_CELLANM_RES, heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	OAMリソース破棄
 *
 *	@param	p_draw			描画ワーク
 *	@param	p_drawglb		描画グローバル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubReleaseOamData( ZKN_SOUND_SUB_DRAW* p_draw, ZKN_SOUND_SUB_DRAWGLB* p_drawglb )
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
 *	@brief	セルアクター登録
 *
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	@param	heap		ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubAddClact( ZKN_SOUND_SUB_DRAW* p_draw, ZKN_SOUND_SUB_DRAWGLB* p_drawglb, int heap )
{
	CLACT_HEADER		clact_head;
	CLACT_ADD_SIMPLE	add;
	ZKN_GLB_DRAWDATA*	p_draw_glb = p_drawglb->p_drawglb;
	int i;
	int x, y;
	
	// アクターヘッダー作成
	CLACT_U_MakeHeader( &clact_head,
			NARC_zukan_zkn_voice_oam_sub_lzh_NCGR + ZKN_SOUND_SUB_RES_ID,
			NARC_zukan_zkn_voice_oam_sub_NCLR + ZKN_SOUND_SUB_RES_ID, 
			NARC_zukan_zkn_voice_oam_sub_lzh_NCER + ZKN_SOUND_SUB_RES_ID,
			NARC_zukan_zkn_voice_oam_sub_lzh_NANR + ZKN_SOUND_SUB_RES_ID,
			CLACT_U_HEADER_DATA_NONE, CLACT_U_HEADER_DATA_NONE, 0, ZKN_SOUND_SUB_OAM_BG_PTR,
			p_draw_glb->res_manager[ CLACT_U_CHAR_RES ],
			p_draw_glb->res_manager[ CLACT_U_PLTT_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELL_RES ],
			p_draw_glb->res_manager[ CLACT_U_CELLANM_RES ],
			NULL, NULL );

	// 登録共通部分を設定
	add.ClActSet	= p_draw_glb->clact_set;
	add.ClActHeader = &clact_head;
	add.pri			= 31;
	add.DrawArea	= NNS_G2D_VRAM_TYPE_2DSUB;
	add.heap		= heap;
	
	// ピッチswitch
	add.mat.x = ZKN_SOUNDSUB_BUTTON_SWITCH_X << FX32_SHIFT;
	add.mat.y = ZKN_SOUNDSUB_BUTTON_SWITCH_Y << FX32_SHIFT;
	add.mat.y += SUB_SURFACE_Y;
	p_draw->pich_switch = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_draw->pich_switch, ZKN_SOUNDSUB_SEQ_SWITCH_PAN_PICH );	
	CLACT_SetAnmFlag( p_draw->pich_switch, TRUE );
	CLACT_SetAnmFrame( p_draw->pich_switch, ZKN_SOUNDSUB_ANIME_FRAME );
	CLACT_AnmFrameSet( p_draw->pich_switch,ZKN_SOUNDSUB_SWITCH_08 );

	// ダイヤル
	add.mat.x = ZKN_SOUNDSUB_BUTTON_DIAL_X << FX32_SHIFT;
	add.mat.y = ZKN_SOUNDSUB_BUTTON_DIAL_Y << FX32_SHIFT;
	add.mat.y += SUB_SURFACE_Y;
	p_draw->dial = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_draw->dial, ZKN_SOUNDSUB_SEQ_DIAL );	
	CLACT_SetAffineParam( p_draw->dial, CLACT_AFFINE_NORMAL );

	// 開始停止
	add.mat.x = ZKN_SOUNDSUB_BUTTON_STARTSTOP_X_DRAW << FX32_SHIFT;
	add.mat.y = ZKN_SOUNDSUB_BUTTON_STARTSTOP_Y_DRAW << FX32_SHIFT;
	add.mat.y += SUB_SURFACE_Y;
	p_draw->startstop = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_draw->startstop, ZKN_SOUNDSUB_SEQ_SOUND_START_ANM );	
	CLACT_SetAnmFlag( p_draw->startstop, TRUE );
	CLACT_SetAnmFrame( p_draw->startstop, ZKN_SOUNDSUB_ANIME_FRAME );
	CLACT_AnmFrameSet(p_draw->startstop, ZKN_SOUNDSUB_START_05 );
	// アニメデータ設定
	p_draw->start_stop_anim.anm_seq1 = ZKN_SOUNDSUB_SEQ_SOUND_START_ANM; 
	p_draw->start_stop_anim.anm_seq2 = ZKN_SOUNDSUB_SEQ_SOUND_STOP_ANM; 
	p_draw->start_stop_anim.now_anm_seq = ZKN_SOUNDSUB_SEQ_SOUND_START_ANM;
	p_draw->start_stop_anim.anm_num_max = ZKN_SOUNDSUB_START_05;
	p_draw->start_stop_anim.push_anm_limit = ZKN_SOUNDSUB_START_02;


	// ループ
	add.mat.x = ZKN_SOUNDSUB_BUTTON_LOOP_X_DRAW << FX32_SHIFT;
	add.mat.y = ZKN_SOUNDSUB_BUTTON_LOOP_Y_DRAW << FX32_SHIFT;
	add.mat.y += SUB_SURFACE_Y;
	p_draw->loop = CLACT_AddSimple( &add );
	CLACT_AnmChg( p_draw->loop, ZKN_SOUNDSUB_SEQ_SOUND_LOOPOFF_ANM );	
	CLACT_SetAnmFlag( p_draw->loop, TRUE );
	CLACT_SetAnmFrame( p_draw->loop, ZKN_SOUNDSUB_ANIME_FRAME );
	CLACT_AnmFrameSet(p_draw->loop, ZKN_SOUNDSUB_LOOP_05 );
	// アニメデータ設定
	p_draw->loop_anim.anm_seq1 = ZKN_SOUNDSUB_SEQ_SOUND_LOOPOFF_ANM; 
	p_draw->loop_anim.anm_seq2 = ZKN_SOUNDSUB_SEQ_SOUND_LOOPON_ANM; 
	p_draw->loop_anim.now_anm_seq = ZKN_SOUNDSUB_SEQ_SOUND_LOOPOFF_ANM;
	p_draw->loop_anim.anm_num_max = ZKN_SOUNDSUB_LOOP_05;
	p_draw->loop_anim.push_anm_limit = ZKN_SOUNDSUB_LOOP_02;
}

//----------------------------------------------------------------------------
/**
 *	@brief	セルアクター破棄
 *
 *	@param	p_draw	描画ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubDeleteClact( ZKN_SOUND_SUB_DRAW* p_draw )
{
	CLACT_Delete( p_draw->dial );
	CLACT_Delete( p_draw->pich_switch );
	CLACT_Delete( p_draw->startstop );
	CLACT_Delete( p_draw->loop );
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
static void ZknSoundSubAddFontOam( ZKN_SOUND_SUB_DRAW* p_draw, ZKN_SOUND_SUB_DRAWGLB* p_drawglb, int heap )
{
	GF_BGL_BMPWIN* win;	// 文字列書き込み先
	ZKN_FONTOAM_INIT fontoam_init;
	CLACT_U_RES_OBJ_PTR res_obj;
	ZKN_GLB_DRAWDATA* p_glb_draw = p_drawglb->p_drawglb;
	int pltt_ofs;	// パレットアドレス

	// パレットのリソースデータ取得
	// パレットプロクシ取得用
	res_obj = CLACT_U_ResManagerGetIDResObjPtr( p_glb_draw->res_manager[ CLACT_U_PLTT_RES ], NARC_zukan_zkn_voice_oam_sub_NCLR + ZKN_SOUND_SUB_RES_ID );

	// 初期化データの共通部分を作成
	// 共通データ代入
	fontoam_init.zkn_fontoam = p_glb_draw->fontoam_sys;
	fontoam_init.pltt		 = CLACT_U_PlttManagerGetProxy( res_obj, NULL );
	fontoam_init.parent		 = NULL;
	fontoam_init.y			 = ZKN_SOUNDSUB_PITCH_PAN_FOTN_Y + 192;
	fontoam_init.bg_pri		 = ZKN_SOUND_SUB_OAM_BG_PTR;
	fontoam_init.soft_pri	 = 0;
	fontoam_init.draw_area	 = NNS_G2D_VRAM_TYPE_2DSUB;
	fontoam_init.heap		 = heap;

	// パレット転送先アドレス取得
	pltt_ofs = GetPlttProxyOffset( fontoam_init.pltt, NNS_G2D_VRAM_TYPE_2DSUB );

	// ビットマップウィンドウ作成
	win = ZKN_FONTOAM_GetBmp( p_glb_draw->fontoam_sys, 
			ZKN_SOUNDSUB_BUTTONFONT_BMP_SIZE_CX,
			ZKN_SOUNDSUB_BUTTONFONT_BMP_SIZE_CY );


	// ピッチ
	fontoam_init.x			 = ZKN_SOUNDSUB_PITCH_FOTN_X;
	ZKN_FONTOAM_PrintBmpStr( p_glb_draw->fontoam_sys, win,
			NARC_msg_zkn_dat, ZNK_SOUND_BUTTON_00, 0, 0 );
	fontoam_init.p_bmp		 = win;
	p_draw->p_fontoam[ ZKN_SOUNDSUB_SEQ_SWITCH_PICH ] = ZKN_FONTOAM_Make( &fontoam_init );
	FONTOAM_SetPaletteNo( p_draw->p_fontoam[ ZKN_SOUNDSUB_SEQ_SWITCH_PICH ]->p_fontoam, pltt_ofs + ZKN_SOUNDSUB_BUTTON_PAL_OFS );

	// ビットマップウィンドウ破棄
	ZKN_FONTOAM_DeleteBmp( win );


	// ビットマップウィンドウ作成
	win = ZKN_FONTOAM_GetBmp( p_glb_draw->fontoam_sys, 
			ZKN_SOUNDSUB_BUTTONFONT_BMP_SIZE_CX,
			ZKN_SOUNDSUB_BUTTONFONT_BMP_SIZE_CY );


	// パン
	fontoam_init.x			 = ZKN_SOUNDSUB_PAN_FOTN_X;
	ZKN_FONTOAM_PrintBmpStr( p_glb_draw->fontoam_sys, win,
			NARC_msg_zkn_dat, ZNK_SOUND_BUTTON_01, 0, 0 );
	fontoam_init.p_bmp		 = win;
	p_draw->p_fontoam[ ZKN_SOUNDSUB_SEQ_SWITCH_PAN ] = ZKN_FONTOAM_Make( &fontoam_init );
	FONTOAM_SetPaletteNo( p_draw->p_fontoam[ ZKN_SOUNDSUB_SEQ_SWITCH_PAN ]->p_fontoam, pltt_ofs + ZKN_SOUNDSUB_BUTTON_PAL_OFS );

	// ビットマップウィンドウ破棄
	ZKN_FONTOAM_DeleteBmp( win );

	// パン非標示
	FONTOAM_SetDrawFlag( p_draw->p_fontoam[ ZKN_SOUNDSUB_SEQ_SWITCH_PAN ]->p_fontoam, FALSE );

}

//----------------------------------------------------------------------------
/**
 *	@brief	フォントOAM破棄
 *	
 *	@param	p_draw		描画ワーク
 *	@param	p_drawglb	描画グローバル
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubDeleteFontOam( ZKN_SOUND_SUB_DRAW* p_draw, ZKN_SOUND_SUB_DRAWGLB* p_drawglb )
{
	int i;
	for( i=0; i<ZKN_SOUNDSUB_SEQ_SWITCH_NUM; i++ ){
		ZKN_FONTOAM_Delete( p_draw->p_fontoam[ i ] );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ピッチパン切り替えスイッチ動作
 *
 *	@param	p_draw		描画ワーク
 *	@param	cp_work		ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubSwitchDrawMove( ZKN_SOUND_SUB_DRAW* p_draw, const ZKN_SOUND_SUB_WORK* cp_work )
{
	int anm_frm;
	
	if( p_draw->now_switch != cp_work->pitch_switch_flag ){
		anm_frm = CLACT_AnmFrameGet( p_draw->pich_switch );
		
		// アニメシーケンス変更
		if( cp_work->pitch_switch_flag == ZKN_SOUNDSUB_SEQ_SWITCH_PICH ){
			CLACT_AnmChg( p_draw->pich_switch, ZKN_SOUNDSUB_SEQ_SWITCH_PAN_PICH );
			CLACT_AnmFrameSet( p_draw->pich_switch, ZKN_SOUNDSUB_SWITCH_08 - anm_frm );
		}else{
			CLACT_AnmChg( p_draw->pich_switch, ZKN_SOUNDSUB_SEQ_SWITCH_PICH_PAN );
			CLACT_AnmFrameSet( p_draw->pich_switch, ZKN_SOUNDSUB_SWITCH_08 - anm_frm );
		}

		p_draw->now_switch = cp_work->pitch_switch_flag;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	再生ストップ描画動作
 *
 *	@param	p_draw		描画ワーク
 *	@param	cp_work		ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubStartStopDrawMove( ZKN_SOUND_SUB_DRAW* p_draw, const ZKN_SOUND_SUB_WORK* cp_work )
{
	int button_event = cp_work->sub_button_event[ZKN_SOUNDSUB_BUTTON_SUB_STARTSTOP];

	// ループ再生で無いときは停止ボタンにならない
	if( cp_work->loop == FALSE ){

		ZknSoundSubButtonAnimeMain_NO_Loop( p_draw->startstop, &p_draw->start_stop_anim,
				FALSE, button_event );
	}else{

		ZknSoundSubButtonAnimeMain( p_draw->startstop, &p_draw->start_stop_anim,
				cp_work->sound_play, button_event );


	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ループボタンアニメ
 *
 *	@param	p_draw		描画ワーク
 *	@param	cp_work		ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubLoopDrawMove( ZKN_SOUND_SUB_DRAW* p_draw, const ZKN_SOUND_SUB_WORK* cp_work )
{
	int button_event = cp_work->sub_button_event[ZKN_SOUNDSUB_BUTTON_SUB_LOOP];

	ZknSoundSubButtonAnimeMain( p_draw->loop, &p_draw->loop_anim,
			cp_work->loop, button_event );
}


//----------------------------------------------------------------------------
/**
 *	@brief	ダイヤル操作
 *
 *	@param	p_work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubDialCalc( ZKN_SOUND_SUB_WORK* p_work )
{
	int last_y, last_x;
	int now_y, now_x;
	int rota_num;
	int zettai;
	u16 last_rota, now_rota;

	// ホイールの中心座標からの値にする
	last_x = p_work->dial_start_x - ZKN_SOUNDSUB_BUTTON_DIAL_X;
	last_y = p_work->dial_start_y - ZKN_SOUNDSUB_BUTTON_DIAL_Y;
	now_x = sys.tp_x - ZKN_SOUNDSUB_BUTTON_DIAL_X;
	now_y = sys.tp_y - ZKN_SOUNDSUB_BUTTON_DIAL_Y;

#if 1	// 点が動いた距離を取得するタイプのとき1
	// 動さ値を求める
	rota_num = CalcTool_CircleVectorDistance( last_x, last_y, now_x, now_y, 0 );
#else
	// 円動作
	last_rota = FX_Atan2Idx( last_y, last_x );
	now_rota = FX_Atan2Idx( now_y, now_x );

	rota_num = now_rota - last_rota;

	// 絶対値を求める
	if( rota_num < 0 ){
		zettai = -rota_num;
	}else{
		zettai = rota_num;
	}

	// 180以上になることは考えにくいその場合は,０を３６０として考える
	if( zettai >= FX_GET_ROTA_NUM(180) ){
		zettai = FX_GET_ROTA_NUM(360) - zettai;
		zettai = -zettai;		// 0->360という考えになるからベクトルを変える必要がある
	}

	// 設定
	if( rota_num < 0 ){
		rota_num = -zettai;
	}else{
		rota_num = zettai;
	}
#endif

	// リミット以下の値なら抜ける
	if( MATH_IAbs( rota_num ) < ZKN_SOUNDSUB_DIAL_MOVE_LIMIT_ROTA ){
		return;
	}

	// 足す
	p_work->dial_rota += rota_num;


	// マイナスになったら一回り
	if( p_work->dial_rota < 0 ){
		p_work->dial_rota += ZKN_SOUNDSUB_DIAL_MOVE_NUM_MAX;
	}else{
		p_work->dial_rota %= ZKN_SOUNDSUB_DIAL_MOVE_NUM_MAX;
	}

//	OS_Printf( "before rota %d\n", p_work->dial_rota / 182 );

	// リミット角度までしか行かないようにする
	if( (p_work->dial_rota >= ZKN_SOUNDSUB_DIAL_LIMIT_MIN) &&
		(p_work->dial_rota <= ZKN_SOUNDSUB_DIAL_LIMIT_MAX) ){

		if( rota_num > 0 ){
			p_work->dial_rota = ZKN_SOUNDSUB_DIAL_LIMIT_MIN;
		}else{
			p_work->dial_rota = ZKN_SOUNDSUB_DIAL_LIMIT_MAX;
		}
	}

/*	// 最低角度に満たさないときは0にする
	if( (p_work->dial_rota <= ZKN_SOUNDSUB_DIAL_MIN_CUT_NUM) ||
		(p_work->dial_rota >= (FX_GET_ROTA_NUM(360) - ZKN_SOUNDSUB_DIAL_MIN_CUT_NUM)) ){

		p_work->dial_rota = 0;
	}//*/

//	OS_Printf( "after rota %d\n", p_work->dial_rota / 182 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ダイヤルの角度を分割されている決められた角度の値に設定
 *
 *	@param	p_work	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubDialDivSet( ZKN_SOUND_SUB_WORK* p_work )
{

	// 分割角度の倍数になったら音を鳴らす
	if( (p_work->dial_rota / ZKN_SOUNDSUB_DIAL_MIN_CUT_NUM) != p_work->dial_div ){
		// 動いたので音を出す
		Snd_SePlay( ZKN_SND_DIAL );

		p_work->dial_div= p_work->dial_rota / ZKN_SOUNDSUB_DIAL_MIN_CUT_NUM;
	}

}


//----------------------------------------------------------------------------
/**
 *	@brief	ダイアル回転角度により値を設定
 *
 *	@param	p_work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubDialNumSet( ZKN_SOUND_SUB_WORK* p_work )
{
	int set_num;

	// 0なら全停止
	if( p_work->dial_rota == 0 ){
		ZknSoundSubReverbEffectStop( p_work );

		return ;
	}
	
	if( (p_work->dial_rota > 0) &&
		(p_work->dial_rota <= ZKN_SOUNDSUB_DIAL_MOVE_NUM_HALF) ){

		// リバーブが設定されているときはとめる
		if( p_work->dial_flag == ZKN_SOUNDSUB_DIAL_REVERB ){
			Snd_CaptureStopReverb(0);
		}

		// エフェクト開始していないときは開始
		if( p_work->dial_flag != ZKN_SOUNDSUB_DIAL_FILTER ){
			Snd_CaptureStartEffect();
			p_work->dial_flag = ZKN_SOUNDSUB_DIAL_FILTER;
		}


		// 設定値計算
		set_num = p_work->dial_div * ZKN_SOUNDSUB_DIAL_FILTER_NUM;
		
		if( set_num == 0 ){
			set_num = 1;
		}

		// フィルター設定
		Snd_CaptureEffectLevel( set_num );

	}else{
		// フィルター設定されている時は止める
		if( p_work->dial_flag == ZKN_SOUNDSUB_DIAL_FILTER ){
			Snd_CaptureStopEffect();
		}

		// リバーブ開始していないときは開始
		if( p_work->dial_flag != ZKN_SOUNDSUB_DIAL_REVERB ){
			Snd_CaptureStartReverb( 0 );
			p_work->dial_flag = ZKN_SOUNDSUB_DIAL_REVERB;
		}
		

		// 0ならZKN_SOUNDSUB_DIAL_MOVE_NUM_MAXにする
		if( p_work->dial_rota == 0 ){
			p_work->dial_rota = ZKN_SOUNDSUB_DIAL_MOVE_NUM_MAX;
		}

		// このときdial_divはZKN_SOUNDSUB_DIAL_REVERB_MIN～ZKN_SOUNDSUB_DIAL_REVERB_MAXの値になっているので変換
		set_num = ZKN_SOUNDSUB_DIAL_REVERB_MAX - p_work->dial_div;
		
		// 設定値計算
		set_num = set_num * ZKN_SOUNDSUB_DIAL_REVERB_NUM;
		if( set_num > 0 ){	//0～63だから
			set_num --;
		}

		// リバーブ設定
		Snd_CaptureReverbVol( set_num, 0 );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	角度によるOAMの回転
 *
 *	@param	p_draw
 *	@param	cp_work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZKnSoundSubDialDrawMove( ZKN_SOUND_SUB_DRAW* p_draw, const ZKN_SOUND_SUB_WORK* cp_work )
{
	OS_Printf( "%d\n", cp_work->dial_rota );
	CLACT_SetRotation( p_draw->dial, CalcTool_CircleVectroDistRotaGet(ZKN_SOUNDSUB_DIAL_DRAW_R , cp_work->dial_rota ) );
}


//----------------------------------------------------------------------------
/**
 *	@brief	チックによってディスクが動く
 *
 *	@param	p_draw	
 *	@param	cp_work 
 *	@param	p_drawglb
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubDiskDrawMove( ZKN_SOUND_SUB_DRAW* p_draw, ZKN_SOUND_SUB_DRAWGLB* p_drawglb, const ZKN_SOUND_SUB_WORK* cp_work )
{
	int now_tick = Snd_ZukanPlayerGetSampleTick( SND_HANDLE_PMVOICE, cp_work->cp_snd_data, cp_work->pitch_num );

	// もしnow_tickが0だったらループしたのでlastも0にする
	if( now_tick == 0 ){
		p_draw->disk_last_tick = 0;
	}

	// チックの変化量分回転
	p_draw->disk_rota += (now_tick - p_draw->disk_last_tick) * ZKN_SOUNDSUB_DISK_BG_ROTA_MUL;
	p_draw->disk_rota &= 0xffff;

	// 回転角度の設定
	GF_BGL_RadianSetReq( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_AFFINE_S, GF_BGL_RADION_SET, p_draw->disk_rota / 182 );
	GF_BGL_RotateCenterSetReq( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_AFFINE_S, GF_BGL_CENTER_X_SET, ZKN_SOUNDSUB_DISK_BG_BGCX );
	GF_BGL_RotateCenterSetReq( p_drawglb->p_drawglb->p_bg, ZKN_BG_FRM_AFFINE_S, GF_BGL_CENTER_Y_SET, ZKN_SOUNDSUB_DISK_BG_BGCY );

	p_draw->disk_last_tick = now_tick;
}


//----------------------------------------------------------------------------
/**
 *	@brief	ピッチ設定
 *
 *	@param	x	ｘ座標
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubDiskPitchSet( ZKN_SOUND_SUB_WORK* p_work, int x )
{
	int dis_x;
	fx32 calc;
	int set_num;
	
	// X座標からピッチを設定
	dis_x = x - ZKN_SOUNDSUB_DISK_BG_CENTER_X;

	calc = FX_Mul( ZKN_SOUNDSUB_DISK_PITCK_MAX << FX32_SHIFT, dis_x << FX32_SHIFT );
	calc = FX_Div( calc, ZKN_SOUNDSUB_DISK_BG_R << FX32_SHIFT );
	
	set_num = calc >> FX32_SHIFT;

	// 数字設定
	p_work->pitch_num = set_num;
}

//----------------------------------------------------------------------------
/**
 *	@brief	コーラスボリューム設定
 *
 *	@param	p_work	ワーク
 *	@param	x		X座標
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubDiskChorusSet( ZKN_SOUND_SUB_WORK* p_work, int x )
{
	int dis_x;
	fx32 calc;
	int set_num;
	
	// X座標からピッチを設定
	dis_x = x - (ZKN_SOUNDSUB_DISK_BG_CENTER_X - ZKN_SOUNDSUB_DISK_BG_R);	// 左からの距離にする

	calc = FX_Mul( ZKN_SOUNDSUB_DISK_CHORUS_MAX << FX32_SHIFT, dis_x << FX32_SHIFT );
	calc = FX_Div( calc, (ZKN_SOUNDSUB_DISK_BG_R*2) << FX32_SHIFT );
	
	set_num = calc >> FX32_SHIFT;

	// 数字設定
	p_work->chorus_num = set_num;
}

//----------------------------------------------------------------------------
/**
 *	@brief	パン設定
 *
 *	@param	x	ｘ座標
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubDiskPanSet( ZKN_SOUND_SUB_WORK* p_work, int x )
{
	int dis_x;
	fx32 calc;
	int set_num;
	
	// X座標からパンを設定
	dis_x = x - ZKN_SOUNDSUB_DISK_BG_CENTER_X;

	calc = FX_Mul( ZKN_SOUNDSUB_DISK_PAN_MAX << FX32_SHIFT, dis_x << FX32_SHIFT );
	calc = FX_Div( calc, ZKN_SOUNDSUB_DISK_BG_R << FX32_SHIFT );
	
	set_num = calc >> FX32_SHIFT;

	// 数字設定
	p_work->pan_num = set_num;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ピッチパン表示設定
 *
 *	@param	p_draw 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubPitchPanFontDraw( ZKN_SOUND_SUB_DRAW* p_draw )
{
	if( p_draw->now_switch == ZKN_SOUNDSUB_SEQ_SWITCH_PICH ){
		FONTOAM_SetDrawFlag( p_draw->p_fontoam[ ZKN_SOUNDSUB_SEQ_SWITCH_PICH ]->p_fontoam, TRUE );
		FONTOAM_SetDrawFlag( p_draw->p_fontoam[ ZKN_SOUNDSUB_SEQ_SWITCH_PAN ]->p_fontoam, FALSE );
	}else{
		FONTOAM_SetDrawFlag( p_draw->p_fontoam[ ZKN_SOUNDSUB_SEQ_SWITCH_PICH ]->p_fontoam, FALSE );
		FONTOAM_SetDrawFlag( p_draw->p_fontoam[ ZKN_SOUNDSUB_SEQ_SWITCH_PAN ]->p_fontoam, TRUE );
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	ボタンアニメ
 *
 *	@param	act			アクター
 *	@param	p_anmdata	アニメデータ
 *	@param	next_flg	次のフラグ
 *	@param	button_event　ボタンイベント
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubButtonAnimeMain( CLACT_WORK_PTR act, ZKN_SOUND_SUB_ANM_BUTTON* p_anmdata, BOOL next_flg, int button_event )
{
	int anm_frm;

	// スライドアウトすることはない
	if( button_event == BMN_EVENT_SLIDEOUT ){
		button_event = BMN_EVENT_RELEASE;
	}

	anm_frm = CLACT_AnmFrameGet( act );
	
	// スイッチが変わったらアニメをオートで行う
	if( p_anmdata->flag != next_flg ){
		
		// アニメシーケンス変更
		ZknSoundSubButtonAnimeSeqSet( act, p_anmdata,  next_flg );

		p_anmdata->flag = next_flg;
	}


	// もしボタンイベントがあるときはボタンﾌﾚｰﾑをコントロールする
	switch( button_event ){
	case BMN_EVENT_TOUCH:		///< 触れた瞬間
		break;
		
	case BMN_EVENT_HOLD:		///< 触りつづけている
		// push_anm_limitまでアニメを進める
		if( anm_frm > p_anmdata->push_anm_limit ){
			CLACT_AnmFrameSet( act, p_anmdata->push_anm_limit );
			CLACT_SetAnmFrame( act, 0 );
		}
		break;

	case BMN_EVENT_RELEASE:
	case ZKN_SOUNDDUB_BUTTON_START_NOTOUCH:
		// アニメシーケンス変更
		ZknSoundSubButtonAnimeSeqSet( act, p_anmdata,  next_flg );
		CLACT_SetAnmFrame( act, ZKN_SOUNDSUB_ANIME_FRAME );
		break;

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ボタンアニメ		ループじゃないときよう
 *
 *	@param	act			アクター
 *	@param	p_anmdata	アニメデータ
 *	@param	next_flg	次のフラグ
 *	@param	button_event　ボタンイベント
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubButtonAnimeMain_NO_Loop( CLACT_WORK_PTR act, ZKN_SOUND_SUB_ANM_BUTTON* p_anmdata, BOOL next_flg, int button_event )
{
	int anm_frm;

	// スライドアウト選択することはない
	if( button_event == BMN_EVENT_RELEASE ){
		button_event = BMN_EVENT_SLIDEOUT;
	}

	anm_frm = CLACT_AnmFrameGet( act );
	
	// スイッチが変わったらアニメをオートで行う
	if( p_anmdata->flag != next_flg ){
		
		// アニメシーケンス変更
		ZknSoundSubButtonAnimeSeqSet( act, p_anmdata,  next_flg );

		p_anmdata->flag = next_flg;
	}


	// もしボタンイベントがあるときはボタンﾌﾚｰﾑをコントロールする
	switch( button_event ){
	case BMN_EVENT_TOUCH:		///< 触れた瞬間
		// アニメシーケンス設定
		if( next_flg == TRUE ){
			ZknSoundSubButtonAnimeSeqSet( act, p_anmdata,  FALSE );
		}else{
			ZknSoundSubButtonAnimeSeqSet( act, p_anmdata,  TRUE );
		}
		CLACT_AnmFrameSet( act, p_anmdata->push_anm_limit - 1 );
		break;
		
	case BMN_EVENT_HOLD:		///< 触りつづけている
		CLACT_AnmFrameSet( act, p_anmdata->push_anm_limit );
		CLACT_SetAnmFrame( act, 0 );
		break;

	case BMN_EVENT_SLIDEOUT:		///< 画面タッチしたままボタン領域から外れた瞬間
	case ZKN_SOUNDDUB_BUTTON_START_NOTOUCH:
		// アニメシーケンス設定
		ZknSoundSubButtonAnimeSeqSet( act, p_anmdata,  next_flg );
		CLACT_SetAnmFrame( act, ZKN_SOUNDSUB_ANIME_FRAME );
		break;//*/

	default:
		break;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	アニメシーケンス変更部分
 *
 *	@param	act			アクター
 *	@param	p_anmdata	アニメデータ
 *	@param	flg			フラグ
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubButtonAnimeSeqSet( CLACT_WORK_PTR act, ZKN_SOUND_SUB_ANM_BUTTON* p_anmdata, BOOL flg )
{
	int anm_frm;

	anm_frm = CLACT_AnmFrameGet( act );

	// アニメシーケンス変更
	if( flg == TRUE ){
		// 停止へ
		if( p_anmdata->now_anm_seq == p_anmdata->anm_seq1 ){
			CLACT_AnmChg( act, p_anmdata->anm_seq2 );
			p_anmdata->now_anm_seq = p_anmdata->anm_seq2;
			CLACT_AnmFrameSet( act, p_anmdata->anm_num_max - anm_frm );
		}
	}else{

		// 再生へ
		if( p_anmdata->now_anm_seq == p_anmdata->anm_seq2 ){
			CLACT_AnmChg( act, p_anmdata->anm_seq1 );
			p_anmdata->now_anm_seq = p_anmdata->anm_seq1;
			CLACT_AnmFrameSet( act, p_anmdata->anm_num_max - anm_frm );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	鳴き声再生
 *
 *	@param	p_work
 *	@param	monno
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubSoundStart( ZKN_SOUND_SUB_WORK* p_work, ZKN_SOUND_SUB_GLB* p_glb, int monsno )
{
	p_work->sound_play = TRUE;

	Snd_PMVoicePlayEx( PV_ZUKAN_CHORUS, monsno, 0, 
					   PV_VOL_MAX, PV_PTN_PARAM_NONE );	//ぺラップ

	// リバーブフィルター設定による値設定
//	ZknSoundSubDialNumSet( p_work );

	// ピッチパンの値を設定
	ZknSoundSubPitchPanChorusSet( p_work );
}

//----------------------------------------------------------------------------
/**
 *	@brief	停止時に行う処理
 *
 *	@param	p_work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubSoundStop( ZKN_SOUND_SUB_WORK* p_work )
{
	Snd_PMVoiceStop(0);

	p_work->sound_play = FALSE;

	// リバーブフィルターを止める
//	ZknSoundSubReverbEffectStop( p_work );
}

//----------------------------------------------------------------------------
/**
 *	@brief	リバーブフィルターを止める
 *
 *	@param	p_work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubReverbEffectStop( ZKN_SOUND_SUB_WORK* p_work )
{
	// フィルターリバーブの設定を止める
	if( p_work->dial_flag == ZKN_SOUNDSUB_DIAL_REVERB ){
		Snd_CaptureStopReverb(0);
	}
	// フィルター設定されている時は止める
	if( p_work->dial_flag == ZKN_SOUNDSUB_DIAL_FILTER ){
		Snd_CaptureStopEffect();
	}

	p_work->dial_flag = ZKN_SOUNDSUB_DIAL_NONE;
}


//----------------------------------------------------------------------------
/**
 *	@brief	ループ再生
 ;*
 *	@param	p_work
 *	@param	p_glb 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubSoundLoop(  ZKN_SOUND_SUB_WORK* p_work, ZKN_SOUND_SUB_GLB* p_glb )
{
	int monsno = ZKN_GLBDATA_PokeMonsNoGet( p_glb->p_glb );

	// とまったら再生
	if( Snd_PMVoicePlayCheck() == FALSE ){

		p_work->loop_wait--;
		if( p_work->loop_wait == 0 ){
			ZknSoundSubSoundStart( p_work, p_glb, monsno );
			p_work->loop_wait = ZKN_SOUNDSUB_DIAL_LOOP_WAIT;
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ループ再生設定をする
 *
 *	@param	p_work	ワークk
 *	@param	flag	TRUE　ループ　FALSE　普通に戻す
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubSoundLoopSet( ZKN_SOUND_SUB_WORK* p_work, BOOL flag )
{
	p_work->loop = flag;
	p_work->loop_wait = ZKN_SOUNDSUB_DIAL_LOOP_WAIT;
}

//----------------------------------------------------------------------------
/**
 *	@brief	パレット読み込み
 *
 *	@param	p_draw	描画ワーク
 *	@param	heap	ヒープ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubPlttLoad( ZKN_SOUND_SUB_DRAW* p_draw, ZKN_SOUND_SUB_DRAWGLB* p_drawglb, int heap )
{
	p_draw->p_pltt_buff = ZKN_GLBDATA_PalDataGet( p_drawglb->p_drawglb, NARC_zukan_zkn_data_voice_NCLR, &p_draw->p_plt, heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	パレット破棄
 *
 *	@param	p_draw	描画ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubPlttRelease( ZKN_SOUND_SUB_DRAW* p_draw )
{
	sys_FreeMemoryEz( p_draw->p_pltt_buff );
	p_draw->p_pltt_buff = NULL;
	p_draw->p_plt = NULL;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ONパレットを設定
 *
 *	@param	p_draw	描画ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubPlttOn( ZKN_SOUND_SUB_DRAW* p_draw )
{
	AddVramTransferManager(
			NNS_GFD_DST_2D_BG_PLTT_SUB,
			ZKN_SOUNDSUB_DISK_PITCH_PAN_PL * 32,
			p_draw->p_plt->pRawData,
			32 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	OFFパレットを設定
 *
 *	@param	p_draw	描画ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubPlttOff( ZKN_SOUND_SUB_DRAW* p_draw )
{
	AddVramTransferManager(
			NNS_GFD_DST_2D_BG_PLTT_SUB,
			ZKN_SOUNDSUB_DISK_PITCH_PAN_PL * 32,
			&((u8*)(p_draw->p_plt->pRawData))[32],
			32 );
}


//----------------------------------------------------------------------------
/**
 *	@brief	ピッチパンのオンオフ
 *
 *	@param	p_work	ワーク
 *	@param	flag	フラグ　TRUE　ON　　FALSE　OFF
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubPitchPanChorusOnOff( ZKN_SOUND_SUB_WORK* p_work, BOOL flag )
{
	ZknSoundSubPitchPanChorusFlagOnOff( p_work, flag );

	if( flag == FALSE ){
		ZknSoundSubPitchPanChorusNumReset( p_work );
	}
}
//　フラグの上げ下げ
static void ZknSoundSubPitchPanChorusFlagOnOff( ZKN_SOUND_SUB_WORK* p_work, BOOL flag )
{
	// ON　OFF設定
	p_work->pitch_pan_push = flag;
}
// 値の初期化
static void ZknSoundSubPitchPanChorusNumReset( ZKN_SOUND_SUB_WORK* p_work )
{
	p_work->pitch_num = 0;
	p_work->pan_num = 0;
	p_work->chorus_num = 0;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ピッチパンコーラス設定
 *
 *	@param	p_work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubPitchPanChorusSet( ZKN_SOUND_SUB_WORK* p_work )
{
	// 再生中なら設定
	if( p_work->sound_play ){
		ZknSoundSubPitchSet( p_work->pitch_num );
		Snd_PlayerSetTrackPan( SND_HANDLE_PMVOICE, 0xffff, p_work->pan_num );

		ZknSoundSubChorusSet( p_work->chorus_num );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	コーラス設定
 *
 *	@param	p_work	ワーク
 *	@param	volume	ボリューム
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubChorusSet( int volume )
{
	Snd_PlayerMoveVolume( SND_HANDLE_CHORUS, volume, 0 );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ピッチパンアニメ
 *
 *	@param	p_draw
 *	@param	cp_work 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubPitchPanAnm( ZKN_SOUND_SUB_DRAW* p_draw, const ZKN_SOUND_SUB_WORK* cp_work )
{
	// パレットアニメさせる
	if( cp_work->pitch_pan_push != p_draw->pltt_anm ){
		
		if( cp_work->pitch_pan_push == TRUE ){
			ZknSoundSubPlttOn( p_draw );	
		}else{
			ZknSoundSubPlttOff( p_draw );	
		}
		p_draw->pltt_anm = cp_work->pitch_pan_push;
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	カーソル制御
 *
 *	@param	p_work		ワーク
 *	@param	p_glb		グローバル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubCursorMove( ZKN_SOUND_SUB_WORK* p_work, ZKN_SOUND_SUB_GLB* p_glb )
{
	int monsno = ZKN_GLBDATA_PokeMonsNoGet( p_glb->p_glb );

	// 動作する
	if( sys.trg & PAD_BUTTON_A ){

		p_work->sound_play_button_cursor = 1;

		// ボタンイベント設定
		p_work->sub_button_event[ ZKN_SOUNDSUB_BUTTON_SUB_STARTSTOP ] = BMN_EVENT_TOUCH;

		// 鳴き声再生
		if( p_work->loop == FALSE ){
			// なっていたらとめる
			if( p_work->sound_play == TRUE ){
				Snd_PMVoiceStop(0);
			}	
			
			ZknSoundSubSoundStart( p_work, p_glb, monsno );
		}else{
			// 再生停止設定
			if( p_work->sound_play == FALSE ){
				ZknSoundSubSoundStart( p_work, p_glb, monsno );
			}else{
				// 停止
				ZknSoundSubSoundStop( p_work );
			}
		}
	}else if( p_work->sound_play_button_cursor == 1 ){

		// Hold
		p_work->sound_play_button_cursor = 2;
		p_work->sub_button_event[ ZKN_SOUNDSUB_BUTTON_SUB_STARTSTOP ] = BMN_EVENT_HOLD;

	}else if( p_work->sound_play_button_cursor == 2 ){

		p_work->sound_play_button_cursor = 0;
		p_work->sub_button_event[ ZKN_SOUNDSUB_BUTTON_SUB_STARTSTOP ] = BMN_EVENT_RELEASE;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	カーソル描画処理
 *
 *	@param	p_drawglb	描画グローバル
 *	@param	cp_glb		グローバル
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubCursorDrawMove( ZKN_SOUND_SUB_DRAWGLB* p_drawglb, const ZKN_SOUND_SUB_GLB* cp_glb )
{
	ZKN_GLB_DRAWDATA* p_draw = p_drawglb->p_drawglb;
	
	if( ZKN_ZukanCommonSubCursorFlagGet( cp_glb->cp_zukan_common_apl ) == TRUE ){
	
		ZKN_UTIL_CursorSetMatrix( p_draw, ZKN_SOUNDSUB_BUTTON_STARTSTOP_X, ZKN_SOUNDSUB_BUTTON_STARTSTOP_Y, ZKN_SOUNDSUB_CURSOR_START_SIZX, ZKN_SOUNDSUB_CURSOR_START_SIZY );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ピッチ設定
 *
 *	@param	num 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknSoundSubPitchSet( int num )
{
	Snd_PlayerSetTrackPitch( SND_HANDLE_PMVOICE, 0xffff, num);
	Snd_PlayerSetTrackPitch( SND_HANDLE_CHORUS, 0xffff, SND_ZUKAN_PITCH_CHORUS + num );
}
