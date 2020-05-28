//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		wipe.c
 *@brief	DP画面切り替えシステム
 *@author	tomoya takahashi
 *@data		2005.08.18
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#include <string.h>
#include "system.h"
#include "tcb.h"
#include "assert.h"
#include "system/lib_pack.h"
#include "system/wipe_wnd.h"
#include "include/system/brightness.h"
#include "include/gflib/sdkdef.h"

#define	__WIPE_H_GLOBAL
#include "system/wipe.h"
#define __WIPE_DEF_H_GLOBAL
#define __WIPE_DEF_H_GLOBAL_VAL
#include "system/wipe_def.h"
#include "system/wipe_sub.h"




//-------------------------------------
//	
//	Vblank中に登録するデータ
//	
//=====================================
typedef struct {
	WIPE_HBLANK* p_wipehb;
	void*	work;
	pHBFunc	func;
	int		disp;
} WIPE_V_HBLANK;

//-------------------------------------
//	
//	vblank中に破棄するデータ
//	
//=====================================
typedef struct {
	WIPE_HBLANK* p_wipehb;
	int disp;
} WIPE_V_DELHBLANK;


//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------
// 画面切り替えパターン定数
enum{
	WIPE_THE_SAME_TIME = 0,		// 同時
	WIPE_START_MAIN,			// メイン開始
	WIPE_START_SUB,				// サブ開始
};


//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	画面切り替えパターンテーブル
//	
//=====================================
typedef struct {
	// 画面切り替えパターンフラグ
	int wipe_pattern;
	
	// メインサブのワイプの存在、非存在フラグ
	BOOL wipe_exist_m;	// ワイプが終了したらFALSEになってします	ワイプ終了したかチェック用
	BOOL wipe_exist_s;	// ワイプが終了したらFALSEになってします	ワイプ終了したかﾁｪｯｸ用

	BOOL wipe_exist_m_check;	// ワイプが終了してもTRUEのままです。	ワイプ存在チェック用
	BOOL wipe_exist_s_check;	// ワイプが終了してもTRUEのままです。	ワイプ存在チェック用
} WIPE_SYS_PATTERN_DATA;


//-------------------------------------
//	
//	フェードシステムデータ
//	
//=====================================
typedef struct _WIPE_SYS_DATA{
	// フェードパターンデータ
	WIPE_SYS_PATTERN_DATA	wipe_pattern_data;

	// ワイプデータ
	WIPE_SYS_WIPE_WORK	wipe_m;
	WIPE_SYS_WIPE_WORK	wipe_s;

	// HBlankワーク
	WIPE_HBLANK			wipehb;

	// wndsysワーク
	WNDP_SYS	wnd_sys;

	// 動作フラグ
	u16 move_flg;	
	u8 effect_flg_m;	// 画面に何か影響をあたえているか
	u8 effect_flg_s;	// 画面に何か影響をあたえているか

	// フェードアウトカラー
	u16 fade_color;

} WIPE_SYS_DATA;	// size		316byte

//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------

static void endWipe(WIPE_SYS_DATA* scchg);
static void cleanWipeData( WIPE_SYS_DATA* p_wipe_data );

static void scchg_HBlankWorkSet( WIPE_HBLANK* p_wipehb );
static void scchg_HBlankFunc(void * work);
static void scchg_v_HBlankInit(TCB_PTR tcb, void* work);
static void scchg_v_HBlankDelete(TCB_PTR tcb, void* work);
static BOOL screenChangeSub(WIPE_SYS_PATTERN_DATA* pattern, WIPE_SYS_WIPE_WORK* wipe_m, WIPE_SYS_WIPE_WORK* wipe_s);

static void wipeFuncPack(BOOL* exist, WIPE_SYS_WIPE_WORK* wipe);
static BOOL wipeFunc(WIPE_SYS_WIPE_WORK* wipe);

static void setScreenChangePattern(int no, WIPE_SYS_PATTERN_DATA* pattern);
static void setWipeWork(WIPE_SYS_WIPE_WORK* wipe_w, int wipe_no, int division, int piece_sync, int sequence, void* work, int disp, WNDP_SYS_PTR wnd_sys, WIPE_HBLANK* p_wipehb,  int heap, u16 color);
static void patternDataSet(WIPE_SYS_PATTERN_DATA* pattern_data, int pattern, BOOL exist_m, BOOL exist_s);

static void setBackDropColor( u16 color );

static u16 getSetColor( WIPE_SYS_DATA* p_data, u16 color );
static u16 getSaveWiepColor( const WIPE_SYS_DATA* cp_data );
static void chgWnd_MstBrightnessCheck_Do( WIPE_SYS_WIPE_WORK* p_data );
static void resetMstBrightnessCheck_Do( WIPE_SYS_WIPE_WORK* p_data );


static BOOL WipeFadeInCheck( u32 wipe_type );

static void resetMstBrightnessVblank( TCB_PTR tcb, void* work );


//-----------------------------------------------------------------------------
/**
 *					グローバル宣言宣言
*/
//-----------------------------------------------------------------------------
const static pWIPEFunc WipeFunc[] = {
	WipeFunc00,
	WipeFunc01,
	WipeFunc02,
	WipeFunc03,
	WipeFunc04,
	WipeFunc05,
	WipeFunc06,
	WipeFunc07,
	WipeFunc08,
	WipeFunc09,
	WipeFunc10,
	WipeFunc11,
	WipeFunc12,
	WipeFunc13,
	WipeFunc14,
	WipeFunc15,
	WipeFunc16,
	WipeFunc17,
	WipeFunc18,
	WipeFunc19,
	WipeFunc20,
	WipeFunc21,
	WipeFunc22,
	WipeFunc23,
	WipeFunc24,
	WipeFunc25,
	WipeFunc26,
	WipeFunc27,
	WipeFunc28,
	WipeFunc29,
	WipeFunc30,
	WipeFunc31,
	WipeFunc32,
	WipeFunc33,
	WipeFunc34,
	WipeFunc35,
	WipeFunc36,
	WipeFunc37,
	WipeFunc38,
	WipeFunc39,
	WipeFunc40,
	WipeFunc41,
};

//-------------------------------------
//
//	ワイプシステムワーク
//	316byte
//	
//	大体の画面で使用するシステムのため
//	グローバルにワークを持つことにしました
//=====================================
static WIPE_SYS_DATA WipeSysWork;

//----------------------------------------------------------------------------
/**
 *@brief	画面切り替えワイプを開始
 *
 *@param	pattern		切り替えパターン番号
 *@param	wipe_m		ワイプ　　メイン画面ワイプ番号
 *@param	wipe_s		ワイプ　　サブ画面ワイプ番号
 *@param	color		ワイプの色
 *@param	division	各ワイプ処理の分割数
 *@param	piece_sync	各ワイプの処理を分割した１片のシンク数
 *@param	heap		使用するヒープ
 *
 *@return	none
 */
//-----------------------------------------------------------------------------
void WIPE_SYS_Start(int pattern, int wipe_m, int wipe_s, u16 color, int division, int piece_sync, int heap)
{
	WIPE_SYS_DATA* scw;
	u16 set_color;
	
	//"division ０無効です"
	GF_ASSERT(division);
	//"piece_sync ０無効です"
	GF_ASSERT(piece_sync);
	// 動作中ならとめる
	GF_ASSERT( WipeSysWork.move_flg == FALSE );

	// ワークポインタ設定
	scw = &WipeSysWork;
	// ワーク初期化
	cleanWipeData( scw );

	// 切り替えパターンデータ作成
	setScreenChangePattern(pattern, &scw->wipe_pattern_data);

	// HBlankワークの初期設定
	scchg_HBlankWorkSet( &scw->wipehb );

	// 設定カラー取得
	set_color = getSetColor( scw, color );
	
	// ワイプワークの作成
	setWipeWork(&scw->wipe_m, wipe_m, division, piece_sync, 0, NULL, WIPE_DISP_MAIN, &scw->wnd_sys, &scw->wipehb, heap, set_color);
	setWipeWork(&scw->wipe_s, wipe_s, division, piece_sync, 0, NULL, WIPE_DISP_SUB, &scw->wnd_sys, &scw->wipehb, heap, set_color);

	scw->move_flg	= TRUE;			// 動作中にする	

	// 初期化関数を実行
	// １回目の動作は初期化になっている
	// 初期化動作で、画面の設定（ウィンドウマスクで黒くしたり、ブライトネスの初期設定をおこなったり）
	// をするのでここで呼ぶ
	wipeFuncPack(&scw->wipe_pattern_data.wipe_exist_m, &scw->wipe_m);
	wipeFuncPack(&scw->wipe_pattern_data.wipe_exist_s, &scw->wipe_s);
		
	// もしフェードインの時　＆＆　白黒のとき　＆＆　ウィンドウを使用したワイプ
	// ならば、ﾌﾞﾗｲﾄﾈｽ設定をOFFする
	if( scw->wipe_pattern_data.wipe_exist_m_check ){
		resetMstBrightnessCheck_Do( &scw->wipe_m );
		scw->effect_flg_m = TRUE;
	}
	if( scw->wipe_pattern_data.wipe_exist_s_check ){
		resetMstBrightnessCheck_Do( &scw->wipe_s );
		scw->effect_flg_s = TRUE;
	}

}


//----------------------------------------------------------------------------
/**
 *	@brief	画面切り替えワイプメイン関数
 *
 *	@param	none
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WIPE_SYS_Main( void )
{
	WIPE_SYS_DATA* scw = &WipeSysWork;
	BOOL	ret;

	// 動作フラグがたっているときのみ動作
	if( scw->move_flg  ){
		ret = screenChangeSub(&scw->wipe_pattern_data, &scw->wipe_m, &scw->wipe_s);
		if(ret == TRUE){
			// ワイプ終了
			endWipe( scw );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	画面切り替えワイプ　終了チェック
 *
 *	@param	none
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	途中
 */
//-----------------------------------------------------------------------------
BOOL WIPE_SYS_EndCheck( void )
{
	if( WipeSysWork.move_flg ){
		return FALSE;
	}
	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ワイプの強制終了
 *
 *	@param	none
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WIPE_SYS_ExeEnd( void )
{
	// HBLANK初期化
	WIPE_HBlankDelete( &WipeSysWork.wipehb, WIPE_DISP_MAIN );
	WIPE_HBlankDelete( &WipeSysWork.wipehb, WIPE_DISP_SUB );
	// WNDワーク破棄
	if( WipeSysWork.wipe_pattern_data.wipe_exist_m ){
		WipeSysWork.wipe_m.sequence = WIPE_END;	
	}
	if( WipeSysWork.wipe_pattern_data.wipe_exist_s ){
		WipeSysWork.wipe_s.sequence = WIPE_END;	
	}
	wipeFuncPack(&WipeSysWork.wipe_pattern_data.wipe_exist_m,
			&WipeSysWork.wipe_m);
	wipeFuncPack(&WipeSysWork.wipe_pattern_data.wipe_exist_s,
			&WipeSysWork.wipe_s);
	// ワイプ終了
	WipeSysWork.move_flg = FALSE;	// 動作OFF
	WipeSysWork.effect_flg_m = FALSE;
	WipeSysWork.effect_flg_s = FALSE;
	// ワークのクリア
	cleanWipeData( &WipeSysWork );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ワイプが画面に影響を与えているかチェック
 *
 *	@retval	TRUE	ワイプ状態クリアしている
 *	@retval	FALSE	ワイプ状態クリアされていない
 */
//-----------------------------------------------------------------------------
BOOL WIPE_SYS_EffectCheck( void )
{
	if( (WipeSysWork.effect_flg_m == TRUE) ||
		(WipeSysWork.effect_flg_s == TRUE) ){
		return FALSE;
	}
	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ワイプ状態を解除する
 *
 *	@param	disp	解除したい画面
 *	@param	heap	使用するヒープ
 *
 *	@return	none
 *
 * disp
	WIPE_DISP_MAIN,		// メイン面
	WIPE_DISP_SUB		// サブ面
 *
 */
//-----------------------------------------------------------------------------
void WIPE_Reset( int disp )
{
	WIPE_ResetWndMask( disp );
	WIPE_ResetBrightness( disp );

	if( disp == WIPE_DISP_MAIN ){
		WipeSysWork.effect_flg_m = FALSE;
	}else{
		WipeSysWork.effect_flg_s = FALSE;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ウィンドウマスク状態を解除する
 *
 *	@param	disp	解除したい画面
 *
 *	@return
 *
 * disp
	WIPE_DISP_MAIN,		// メイン面
	WIPE_DISP_SUB		// サブ面
 *
 * ＊この関数は
 *	 ハードウェアウィンドウを使用したワイプから
 * 　ブライトネスを使用したワイプに移行する時に、
 * 　ハードウェアウィンドウの設定を解除する為に使用します。
 * 
 */
//-----------------------------------------------------------------------------
void WIPE_ResetWndMask( int disp )
{
	// ウィンドウマスク解除
	WNDP_SetVisibleWnd(GX_WNDMASK_NONE, disp);
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ブライトネス状態を解除
 *
 *	@param	disp	解除したい画面
 *
 *	@return	none
 *
 * disp
	WIPE_DISP_MAIN,		// メイン面
	WIPE_DISP_SUB		// サブ面
 *
 * ＊この関数は
 *	 ブライトネスを使用したワイプから
 * 　ハードウェアウィンドウを使用したワイプに移行する時に、
 * 　ブライトネスの設定を解除する為に使用します。
 */
//-----------------------------------------------------------------------------
void WIPE_ResetBrightness( int disp )
{
	// ブライトネス解除
	WIPE_SetMstBrightness( disp, BRIGHTNESS_NORMAL );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ワイプブライトネス状態を設定
 *
 *	@param	disp	設定する画面
 *	@param	color	ブライトネスカラー
 *
 *	@return	none
 *
 * disp
	WIPE_DISP_MAIN,		// メイン面
	WIPE_DISP_SUB		// サブ面

 *	color
			#define WIPE_FADE_WHITE		(0x7fff)	// ホワイトイン・アウト
			#define WIPE_FADE_BLACK		(0x0000)	// ブラックイン・アウト
 */
//-----------------------------------------------------------------------------
void WIPE_SetBrightness( int disp, u16 color )
{
	int color_msk;

	if( color == WIPE_FADE_WHITE ){
		color_msk = BRIGHTNESS_WHITE;
	}else{
		color_msk = BRIGHTNESS_BLACK;
	}
	
	WIPE_SetMstBrightness( disp, color_msk);
}

//----------------------------------------------------------------------------
/**
 *	@brief	ワイプウィンドウマスク状態を設定
 *
 *	@param	disp		設定する画面
 *	@param	color		カラー
 *
 * disp
	WIPE_DISP_MAIN,		// メイン面
	WIPE_DISP_SUB		// サブ面

 *	color
			#define WIPE_FADE_WHITE		(0x7fff)	// ホワイトイン・アウト
			#define WIPE_FADE_BLACK		(0x0000)	// ブラックイン・アウト
			#define WIPE_FADE_OUTCOLOR	(0xffff)	// 1つ前のフェードアウトカラーでイン・アウト
 *
 *	この関数は、
 *		タッチペン使用画面の場合に、フェードイン前にタッチペンを
 *		出すなど、例外処理があります。そのとき用の関数です
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WIPE_SetWndMask( int disp, u16 color )
{
	// バックドロップcolorの指定
	if( disp == WIPE_DISP_MAIN ){
		GX_LoadBGPltt((void*)&color, 0, sizeof(short));
	}else{
		GXS_LoadBGPltt((void*)&color, 0, sizeof(short));
	}
	
	// ウィンドウ０面で画面を覆う
	WNDP_V_SetVisibleWnd(&WipeSysWork.wnd_sys, GX_WNDMASK_W0, disp);
	WNDP_V_SetWndInsidePlane(&WipeSysWork.wnd_sys, GX_BLEND_ALL, FALSE, 0, disp);
	WNDP_V_SetWndPosition(&WipeSysWork.wnd_sys, 0,0,0,0,0, disp);	
	WNDP_V_SetWndOutsidePlane(&WipeSysWork.wnd_sys, GX_BLEND_PLANEMASK_BD, FALSE, disp);	
}




//----------------------------------------------------------------------------
/**
 *	@brief	背景面パレット色を設定
 *
 *	@param	color	カラー
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WIPE_SetBackDropColor( u16 color )
{
	// バックドロップcolorの指定
	GX_LoadBGPltt((void*)&color, 0, sizeof(short));
	GXS_LoadBGPltt((void*)&color, 0, sizeof(short));
}

//----------------------------------------------------------------------------
/**
 *	@brief	ブライトネス値設定関数
 *
 *	@param	disp	画面
 *	@param	no		設定値
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void WIPE_SetMstBrightness( int disp, int no )
{
	// ブライトネス解除
	if( disp == WIPE_DISP_MAIN ){
		GX_SetMasterBrightness(no);
	}else{
		GXS_SetMasterBrightness(no);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	画面切り替えフェードを終了する
 *
 *@param	scchg	画面切り替えデータ
 *
 *@return	none
 *
 *
 * 終了時に必ず呼ぶ必要があります。
 *
 */
//-----------------------------------------------------------------------------
static void endWipe(WIPE_SYS_DATA* scchg)
{
	scchg->move_flg = FALSE;	// 動作OFF
	
	// ワイプカラーの保存
	scchg->fade_color = getSaveWiepColor( scchg );

	// もしフェードアウトの時　＆＆　白黒のとき　＆＆　ウィンドウを使用したワイプ
	// ならば、ﾏｽﾀｰﾌﾞﾗｲﾄﾈｽを設定してウィンドウ破棄
	if( scchg->wipe_pattern_data.wipe_exist_m_check ){
		chgWnd_MstBrightnessCheck_Do( &scchg->wipe_m );

		// フェードインならeffect_flgを破棄
		if( scchg->wipe_m.fade_inout == WIPE_FADE_IN ){
			WipeSysWork.effect_flg_m = FALSE;
		}
	}
	if( scchg->wipe_pattern_data.wipe_exist_s_check ){
		chgWnd_MstBrightnessCheck_Do( &scchg->wipe_s );

		// フェードインならeffect_flgを破棄
		if( scchg->wipe_m.fade_inout == WIPE_FADE_IN ){
			WipeSysWork.effect_flg_s = FALSE;
		}
	}

	// ワークのクリア
	cleanWipeData( scchg );
}


//----------------------------------------------------------------------------
/**
 *
 *@brief	画面切り替えサブ関数
 *
 *@param	pattern		切り替えパターン
 *@param	wipe_m		ワイプメイン
 *@param	wipe_s		ワイプサブ
 *
 *@return	BOOL	TRUE：終了		FALSE：続行
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL screenChangeSub(WIPE_SYS_PATTERN_DATA* pattern, WIPE_SYS_WIPE_WORK* wipe_m, WIPE_SYS_WIPE_WORK* wipe_s)
{	
	switch(pattern->wipe_pattern){
	case WIPE_THE_SAME_TIME:	// 同時
		wipeFuncPack(&pattern->wipe_exist_m, wipe_m);
		wipeFuncPack(&pattern->wipe_exist_s, wipe_s);
		break;	
		
	case WIPE_START_MAIN:		// メインが先
		if(pattern->wipe_exist_m){
			wipeFuncPack(&pattern->wipe_exist_m, wipe_m);
		}else{
			wipeFuncPack(&pattern->wipe_exist_s, wipe_s);
		}
		break;	
	case WIPE_START_SUB:		// サブが先
		if(pattern->wipe_exist_s){
			wipeFuncPack(&pattern->wipe_exist_s, wipe_s);
		}else{
			wipeFuncPack(&pattern->wipe_exist_m, wipe_m);
		}	
		break;	
	}
	
	// 両方のワイプの存在フラグがFALSEになったら終了
	if((pattern->wipe_exist_m == FALSE) &&
		(pattern->wipe_exist_s == FALSE)){
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ワイプ動作関数をパックした関数
 *	
 *@param	exist	存在フラグ（WIPE_SYS_PATTERN_DATA内）
 *@param	wipe	ワイプワーク
 *
 *@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void wipeFuncPack(BOOL* exist, WIPE_SYS_WIPE_WORK* wipe)
{
	int ret;
	
	if(*exist){

		ret = wipeFunc(wipe);	

		if(ret == TRUE){
			*exist = FALSE;
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ワイプ関数を実行
 *
 *@param	wipe	ワイプデータ
 *
 *@return	BOOL	TRUE：終了		FALSE：続行
 *
 *
 */
//-----------------------------------------------------------------------------
static BOOL wipeFunc(WIPE_SYS_WIPE_WORK* wipe)
{
	return WipeFunc[wipe->wipe_no](wipe);	
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	画面変更パターンデータを作成
 *
 *@param	no			パターンナンバー
 *@param	pattern_m	メインのパターンデータ格納領域
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void setScreenChangePattern(int no, WIPE_SYS_PATTERN_DATA* pattern)
{
	switch(no){
	case WIPE_PATTERN_WMS:
		patternDataSet(pattern, WIPE_THE_SAME_TIME, TRUE, TRUE);
		break;
		
	case WIPE_PATTERN_FMAS:
		patternDataSet(pattern, WIPE_START_MAIN, TRUE, TRUE);
		break;
		
	case WIPE_PATTERN_FSAM:
		patternDataSet(pattern, WIPE_START_SUB, TRUE, TRUE);
		break;
		
	case WIPE_PATTERN_M:
		patternDataSet(pattern, WIPE_START_MAIN, TRUE, FALSE);
		break;
		
	case WIPE_PATTERN_S:
		patternDataSet(pattern, WIPE_START_SUB, FALSE, TRUE);
		break;
	};
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	パターンデータを設定
 *
 *@param	pattern_data	パターンデータ設定先
 *@param	pattern			パターン
 *@param	exist_m			メインワイプ存在フラグ
 *@param	exist_s			サブワイプ存在フラグ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void patternDataSet(WIPE_SYS_PATTERN_DATA* pattern_data, int pattern, BOOL exist_m, BOOL exist_s)
{
	pattern_data->wipe_pattern = pattern;
	pattern_data->wipe_exist_m = exist_m;
	pattern_data->wipe_exist_s = exist_s;
	pattern_data->wipe_exist_m_check = exist_m;
	pattern_data->wipe_exist_s_check = exist_s;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	ワイプワークデータを設定
 *
 *@param	wipe_w		設定先
 *@param	wipe_no		ワイプナンバー
 *@param	division	処理分割数
 *@param	piece_sync	分割１片のシンク数
 *@param	sequence	シーケンス
 *@param	work		ワーク領域
 *@param	disp		面
 *@param	wnd_sys		ウィンドウシステムポインタ
 *@param	heap		使用するヒープ
 *@param	color		色
 *
 *@return
 *
 *
 */
//-----------------------------------------------------------------------------
static void setWipeWork(WIPE_SYS_WIPE_WORK* wipe_w, int wipe_no, int division, int piece_sync, int sequence, void* work, int disp, WNDP_SYS_PTR wnd_sys, WIPE_HBLANK* p_wipehb,  int heap, u16 color)
{
	wipe_w->wipe_no		= wipe_no;
	wipe_w->division	= division;
	wipe_w->piece_sync	= piece_sync;
	wipe_w->sequence	= sequence;
	wipe_w->wipe_work	= work;
	wipe_w->disp		= disp;
	wipe_w->wnd_sys		= wnd_sys;
	wipe_w->p_wipehb	= p_wipehb;
	wipe_w->heap		= heap;
	wipe_w->color		= color;
}




//----------------------------------------------------------------------------
//
//
//	エフェクト用Hブランク関数郡
//
//
//============================================================================

//----------------------------------------------------------------------------
/**
 *
 *	@brief	Hブランクワークの初期化値を設定
 *
 *	@param	p_wipehb	ワイプHブランクワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_HBlankWorkSet( WIPE_HBLANK* p_wipehb )
{
	int i;
	for( i=0; i<2; i++ ){
		p_wipehb->work[ i ] = NULL;
		p_wipehb->func[ i ] = defaultHFunc;
		p_wipehb->flg[ i ]	= 0;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	HBlank関数
 *
 *@param	none
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_HBlankFunc(void * work)
{
	int i;		// ループ用
	WIPE_HBLANK* p_wipehb = work;

	for(i=0;i<2;i++){
		p_wipehb->func[i](p_wipehb->work[i]);
	}
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	Hブランク関数を設定
 *
 *@param	p_wipehb	ワイプシステムのHブランクワーク構造体
 *@param	work		ワーク
 *@param	func		Hブランク関数
 *@param	disp		表示面（メインサブ）
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WIPE_HBlankInit(WIPE_HBLANK* p_wipehb, void* work, pHBFunc func, int disp)
{
	u8	result=TRUE;
	GF_ASSERT((p_wipehb->flg[disp] == 0));
	GF_ASSERT( p_wipehb->func[disp] != NULL );	// NULLだとおかしい

	if((p_wipehb->flg[0] == 0) &&
		(p_wipehb->flg[1] == 0)){
		result = sys_HBlankIntrSet(scchg_HBlankFunc, p_wipehb);		// 関数設定
	}
	GF_ASSERT(result == TRUE);

	
	p_wipehb->work[disp] = work;
	if(func){
		p_wipehb->func[disp] = func;
	}else{
		p_wipehb->func[disp] = defaultHFunc;
	}
	p_wipehb->flg[disp] = WIPE_HBLANK_DO;

}

//----------------------------------------------------------------------------
/**
 *
 *@brief	Hブランク破棄
 *
 *@param	p_wipehb	ワイプのHブランクワーク
 *@param	disp		表示面	メイン・サブ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WIPE_HBlankDelete(WIPE_HBLANK* p_wipehb, int disp)
{
	p_wipehb->flg[disp] = WIPE_HBLANK_NONE;

	if((p_wipehb->flg[0] == 0) &&
		(p_wipehb->flg[1] == 0)){
		sys_HBlankIntrStop();		//HBlank割り込み停止
	}
	
	p_wipehb->func[disp] = defaultHFunc;
	p_wipehb->work[disp] = NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	Vブランク期間中にHブランク関数を設定
 *
 *@param	work		ワーク
 *@param	func		Hブランク関数
 *@param	disp		表示面
 *@param	heap		使用するヒープ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WIPE_V_HBlankInit(WIPE_HBLANK* p_wipehb, void* work, pHBFunc func, int disp, int heap)
{
	WIPE_V_HBLANK* data = sys_AllocMemoryLo(heap, sizeof(WIPE_V_HBLANK));
	
	data->p_wipehb = p_wipehb;
	data->work = work;
	data->func = func;
	data->disp = disp;
	VWaitTCB_Add( scchg_v_HBlankInit, data, WIPE_HBLANK_INIT_TCB);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	Hブランク破棄
 *
 *@param	disp		表示面	メイン・サブ
 *@param	heap		使用するヒープ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void WIPE_V_HBlankDelete(WIPE_HBLANK* p_wipehb, int disp, int heap)
{
	WIPE_V_DELHBLANK* p_delhb = sys_AllocMemoryLo(heap, sizeof(WIPE_V_DELHBLANK));
	p_delhb->p_wipehb	= p_wipehb;
	p_delhb->disp		= disp;
	VWaitTCB_Add( scchg_v_HBlankDelete, p_delhb, WIPE_HBLANK_DELETE_TCB);
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	Vblank期間中にHblankを初期化するタスク
 *
 *@param	tcb		タスクポインタ
 *@param	work	初期化データ	
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_v_HBlankInit(TCB_PTR tcb, void* work)
{
	WIPE_V_HBLANK*	data = (WIPE_V_HBLANK*)work;
	
	WIPE_HBlankInit(data->p_wipehb, data->work, data->func, data->disp);

	TCB_Delete( tcb );
	sys_FreeMemoryEz( work );
}

//----------------------------------------------------------------------------
/**
 *
 *@brief	Vblank期間中にHblankを破棄する関数
 *
 *@param	tcb		タスクポインタ
 *@param	work	破棄データ
 *
 *@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void scchg_v_HBlankDelete(TCB_PTR tcb, void* work)
{
	WIPE_V_DELHBLANK* p_delhb = (WIPE_V_DELHBLANK*)work;
	
	WIPE_HBlankDelete(p_delhb->p_wipehb, p_delhb->disp);
	
	TCB_Delete( tcb );
	sys_FreeMemoryEz( work );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	Hブランク関数	NULLが渡されたら設定される関数
 *
 *	@param	work	ワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void defaultHFunc( void* work )
{
}


//----------------------------------------------------------------------------
/**
 *	@brief	ワイプカラー取得
 *
 *	@param	p_data	ワイプデータ
 *	@param	color	カラーパラメータ
 *
 *	@return	
 */
//-----------------------------------------------------------------------------
static u16 getSetColor( WIPE_SYS_DATA* p_data, u16 color )
{
	if( color == WIPE_FADE_OUTCOLOR ){
		return p_data->fade_color;
	}
	return color;
}

//----------------------------------------------------------------------------
/**
 *	@brief	今回のワイプデータの保存
 *
 *	@param	cp_data	ワーク
 *
 *	@return	保存するカラー
 */
//-----------------------------------------------------------------------------
static u16 getSaveWiepColor( const WIPE_SYS_DATA* cp_data )
{
	const WIPE_SYS_WIPE_WORK* cp_wipe_w;
	
	// ワイプでのフェードアウト時の場合
	// 色を保存
	if( cp_data->wipe_pattern_data.wipe_exist_m_check == TRUE ){
		cp_wipe_w = &cp_data->wipe_m;
	}else{
		cp_wipe_w = &cp_data->wipe_s;
	}

	// ワイプ色保存
	if( cp_wipe_w->fade_inout == WIPE_FADE_OUT ){
		return cp_wipe_w->color;
	}
	return cp_data->fade_color;	// そのまま
}

//----------------------------------------------------------------------------
/**
 *	@brief	Vブランクﾏｽﾀｰ輝度リセットTCB
 */
//-----------------------------------------------------------------------------
static void resetMstBrightnessVblank( TCB_PTR tcb, void* work )
{
	WIPE_SYS_WIPE_WORK* p_data = work;
	WIPE_SetMstBrightness( p_data->disp, 0 );	
	TCB_Delete( tcb );
}

//----------------------------------------------------------------------------
/**
 *	@brief	マスターﾌﾞﾗｲﾄﾈｽ状態をリセットする
 *
 *	@param	p_data	ワーク
 */
//-----------------------------------------------------------------------------
static void resetMstBrightnessCheck_Do( WIPE_SYS_WIPE_WORK* p_data )
{
	// もしフェードインの時　＆＆　白黒のとき　＆＆　ウィンドウを使用したワイプ
	// ならば、ﾌﾞﾗｲﾄﾈｽ設定をOFFする
	if( (p_data->fade_inout == WIPE_FADE_IN) &&
		((p_data->color == WIPE_FADE_WHITE) || (p_data->color == WIPE_FADE_BLACK)) &&
		(p_data->wnd_br == WIPE_USE_WND) ){

		VWaitTCB_Add( resetMstBrightnessVblank, p_data, WIPE_VBLANK_BR_RESET_TCB );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	フェードアウトでウィンドウ設定時に白黒のときは、ﾏｽﾀーﾌﾞﾗｲﾄﾈｽにする
 *
 *	@param	p_data	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void chgWnd_MstBrightnessCheck_Do( WIPE_SYS_WIPE_WORK* p_data )
{
	// もしフェードアウトの時　＆＆　白黒のとき　＆＆　ウィンドウを使用したワイプ
	// ならば、ﾏｽﾀｰﾌﾞﾗｲﾄﾈｽを設定してウィンドウ破棄
	if( (p_data->fade_inout == WIPE_FADE_OUT) &&
		((p_data->color == WIPE_FADE_WHITE) || (p_data->color == WIPE_FADE_BLACK)) &&
		(p_data->wnd_br == WIPE_USE_WND) ){

		// ﾌﾞﾗｲﾄﾈｽ設定
		WIPE_SetBrightness( p_data->disp, p_data->color );

		// ウィンドウ破棄
		WIPE_ResetWndMask( p_data->disp);
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ワイプデータを空にする
 *
 *	@param	p_wipe_data		ワイプデータ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void cleanWipeData( WIPE_SYS_DATA* p_wipe_data )
{
	memset( &p_wipe_data->wipe_pattern_data, 0, sizeof(WIPE_SYS_PATTERN_DATA) );
	memset( &p_wipe_data->wipe_m, 0, sizeof(WIPE_SYS_WIPE_WORK) );
	memset( &p_wipe_data->wipe_s, 0, sizeof(WIPE_SYS_WIPE_WORK) );
	memset( &p_wipe_data->wipehb, 0, sizeof(WIPE_HBLANK) );
	memset( &p_wipe_data->wnd_sys, 0, sizeof(WNDP_SYS) );
}

//----------------------------------------------------------------------------
/**
 *	@brief	フェードインﾁｪｯｸ
 *
 *	@param	wipe_type	ワイプﾀｲﾌﾟ
 *
 *	@retval	TRUE	フェードイン
 *	@retval	FALSE	フェードアウト
 */
//-----------------------------------------------------------------------------
static BOOL WipeFadeInCheck( u32 wipe_type )
{
	// ホールアウトイン未満のﾀｲﾌﾟは、奇数がフェードイン
	if( (wipe_type % 2) ){
		return TRUE;
	}
	return FALSE;
}

