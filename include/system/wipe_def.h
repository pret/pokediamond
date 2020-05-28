//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		wipe_def.h
 *@brief	ワイプ関数用ヘッダ
 *@author	tomoya takahashi
 *@data		2005.08.18
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __WIPE_DEF_H__
#define __WIPE_DEF_H__

#include "system/wipe_wnd.h"

#undef GLOBAL
#ifdef	__WIPE_DEF_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif


//-------------------------------------
//	
//	シーケンス処理列挙
//	
//=====================================
enum{
	WIPE_INIT,			// 動作初期化
	WIPE_MAIN,			// 動作
	WIPE_END,			// 動作終了
	WIPE_END_WAIT,		// 終了後待ち	終了前に1回はVブランクを通すため　マスクの設定変更はvブランクで行われている為
};


typedef void (*pHBFunc)(void* work);
//-------------------------------------
//
//	ローカルHブランクワーク
//
//	Hブランク内で使用します。
//	flgが０になったら終了したことになります。
//
//=====================================
typedef struct{
	void*	work[2];	// 2=MAIN と SUB
	pHBFunc	func[2];
	int		flg[2];		// 動作フラグ	0:未設定	1:実行中
} WIPE_HBLANK;

enum{
	WIPE_HBLANK_NONE = 0,
	WIPE_HBLANK_DO
};

//-------------------------------------
//	
//	ワイプワーク	
//	
//=====================================
typedef struct {
	int		wipe_no;
	int		division;
	int		piece_sync;
	int		sequence;
	int		disp;			// メインサブどっちか
	void*	wipe_work;		// 各ワイプ用作業領域
	WNDP_SYS_PTR wnd_sys;	// ウィンドウVBlankシステムのポインタ
	WIPE_HBLANK* p_wipehb;	// ワイプ用HBlankワーク
	int		heap;			// 使用するヒープ
	u16		color;			// 色

	// それぞれのワイプに
	// そのワイプの状態を格納してもらう
	u32 fade_inout;		// フェードインかアウトか
	u32 wnd_br;			// ﾌﾞﾗｲﾄﾈｽを使用するのかウィンドウを使用するのか
} WIPE_SYS_WIPE_WORK;

// それぞれのワイプに
// そのワイプの状態を格納してもらう
//-------------------------------------
//	フェード種類列挙	
//=====================================
enum{
	WIPE_FADE_IN,
	WIPE_FADE_OUT
};
//-------------------------------------
//	フェード使用システム列挙	
//=====================================
enum{
	WIPE_USE_WND,
	WIPE_USE_BRI
};


//----------------------------------------------------------------------------
/**
 *
 *@brief	ワイプ関数
 *
 *@param	wipe		ワイプワーク
 *
 *@return	BOOL		終了：TRUE		続行：FALSE
 *
 * 必ず終了したらTRUEを返すようにする。
 * 作業領域は各ワイプ内で作成し、ワイプ内で破棄する。
 *
 */
//-----------------------------------------------------------------------------
typedef BOOL (*pWIPEFunc)(WIPE_SYS_WIPE_WORK* wipe);

// HBlank関数
GLOBAL void WIPE_HBlankInit(WIPE_HBLANK* p_wipehb, void* work, pHBFunc func, int disp);	// Hブランク設定
GLOBAL void WIPE_HBlankDelete(WIPE_HBLANK* p_wipehb, int disp);	// Hブランク破棄
GLOBAL void WIPE_V_HBlankInit(WIPE_HBLANK* p_wipehb, void* work, pHBFunc func, int disp, int heap);	// Hブランク設定
GLOBAL void WIPE_V_HBlankDelete(WIPE_HBLANK* p_wipehb, int disp, int heap);	// Hブランク破棄
GLOBAL void defaultHFunc( void* work );

// ワイプカラー設定関数
GLOBAL void WIPE_SetBackDropColor( u16 color );

// ブライトネス状態設定関数
GLOBAL void WIPE_SetMstBrightness( int disp, int no );

#undef	GLOBAL
#endif		// __WIPE_DEF_H__

