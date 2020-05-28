//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_event_func.h
 *	@brief		イベント関数のおき場所
 *	@author		tomoya takahashi
 *	@data		2006.01.18
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __ZKN_EVENT_FUNC_H__
#define __ZKN_EVENT_FUNC_H__

#include "include/application/zukanlist/zkn_sys_static.h"

#undef GLOBAL
#ifdef	__ZKN_EVENT_FUNC_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *
 *
 *			共通で使えるイベント関数をここにまとめましょう。
 * 
 * 
 */
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *		何も無しー＞アプリケーションスタート
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	イベントデータのZKN_EVENT_DATA.p_dataに
//	格納しておいてもらう構造体
//=====================================
typedef struct {
	ZKN_APL_DATA*		p_apl;		// 始めるアプリケーションデータ
	ZKN_PROC_SYS_PTR	p_proc;		// プロックシステム
	ZKN_EVENT_SYS_PTR	p_event;	// イベントシステム
} ZKN_EVENT_APL_START;
GLOBAL BOOL ZKN_EVENT_AplStart( ZKN_EVENT_WORK* p_work );


//-----------------------------------------------------------------------------
/**
 *		前のアプリケーション終了ー＞次のアプリケーション開始
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	イベントデータのZKN_EVENT_DATA.p_dataに
//	格納しておいてもらう構造体
//=====================================
typedef struct {
	ZKN_APL_DATA*		p_apl;		// 始めるアプリケーションデータ
	ZKN_PROC_SYS_PTR	p_proc;		// プロックシステム
	ZKN_EVENT_SYS_PTR	p_event;	// イベントシステム
} ZKN_EVENT_APL_CHANGE;
GLOBAL BOOL ZKN_EVENT_AplChange( ZKN_EVENT_WORK* p_work );

//-----------------------------------------------------------------------------
/**
 *		今のアプリケーション終了ー＞図鑑破棄
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	イベントデータのZKN_EVENT_DATA.p_dataに
//	格納しておいてもらう構造体
//=====================================
typedef struct {
	ZKN_PROC_SYS_PTR	p_proc_m;		// プロックシステム
	ZKN_PROC_SYS_PTR	p_proc_s;		// プロックシステム
	ZKN_PROC_SYS_PTR	p_proc_mc;		// プロックシステム
	ZKN_PROC_SYS_PTR	p_proc_sc;		// プロックシステム
	BOOL*				p_delete_flag;	// 破棄フラグ
} ZKN_EVENT_APL_END_ZKN_DELETE;
GLOBAL BOOL ZKN_EVENT_AplEndZknDelete( ZKN_EVENT_WORK* p_work );

//-----------------------------------------------------------------------------
/**
 *	今のアプリケーション終了
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	イベントデータのZKN_EVENT_DATA.p_dataに
//	格納しておいてもらう構造体
//=====================================
typedef struct {
	// 無くす
	ZKN_PROC_SYS_PTR	p_proc;		// プロックシステム
	ZKN_EVENT_SYS_PTR	p_event;	// イベントシステム
} ZKN_EVENT_APL_END;
GLOBAL BOOL ZKN_EVENT_AplEnd( ZKN_EVENT_WORK* p_work );

//-----------------------------------------------------------------------------
/**
 *		main画面サブ画面全変更
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	イベントデータのZKN_EVENT_DATA.p_dataに
//	格納しておいてもらう構造体
//=====================================
typedef struct {
	ZKN_PROC_SYS_PTR	p_proc_m;		// プロックシステム
	ZKN_PROC_SYS_PTR	p_proc_s;		// プロックシステム
	ZKN_PROC_SYS_PTR	p_proc_mc;		// プロックシステム
	ZKN_PROC_SYS_PTR	p_proc_sc;		// プロックシステム
	
	ZKN_EVENT_SYS_PTR	p_event_m;		// イベントシステム
	ZKN_EVENT_SYS_PTR	p_event_s;		// イベントシステム
	ZKN_EVENT_SYS_PTR	p_event_mc;		// イベントシステム
	ZKN_EVENT_SYS_PTR	p_event_sc;		// イベントシステム

	ZKN_APL_DATA*		p_apl_m;		// 始めるアプリケーションデータ
	ZKN_APL_DATA*		p_apl_s;		// 始めるアプリケーションデータ
	ZKN_APL_DATA*		p_apl_mc;		// 始めるアプリケーションデータ
	ZKN_APL_DATA*		p_apl_sc;		// 始めるアプリケーションデータ
} ZKN_EVENT_APL_AllCHANGE;
GLOBAL BOOL ZKN_EVENT_AplAllChange( ZKN_EVENT_WORK* p_work );

//-----------------------------------------------------------------------------
/**
 *		main画面サブ画面	２つ変更
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	イベントデータのZKN_EVENT_DATA.p_dataに
//	格納しておいてもらう構造体
//=====================================
typedef struct {
	ZKN_PROC_SYS_PTR	p_proc_m;		// プロックシステム
	ZKN_PROC_SYS_PTR	p_proc_s;		// プロックシステム
	
	ZKN_EVENT_SYS_PTR	p_event_m;		// イベントシステム
	ZKN_EVENT_SYS_PTR	p_event_s;		// イベントシステム

	ZKN_APL_DATA*		p_apl_m;		// 始めるアプリケーションデータ
	ZKN_APL_DATA*		p_apl_s;		// 始めるアプリケーションデータ
} ZKN_EVENT_APL_DOUBLE_CHANGE;
GLOBAL BOOL ZKN_EVENT_AplDoubleChange( ZKN_EVENT_WORK* p_work );



//-----------------------------------------------------------------------------
/**
 *		各アプリケーションに変更するイベントデータ作成関数
 */
//-----------------------------------------------------------------------------
GLOBAL void ZKN_EVENT_DeleteData( ZKN_EVENT_DATA* p_event_data );

// ソート画面
GLOBAL void ZKN_EVENT_MakeChangeSortSearch( int heap, ZKN_EVENT_DATA* p_event_data, ZKN_SYS_PTR zkn_sys, int event_key );

// 図鑑システム終了
GLOBAL void ZKN_EVENT_MakeZukanEnd( int heap, ZKN_EVENT_DATA* p_event_data, ZKN_SYS_PTR zkn_sys, int event_key );

// 図鑑サブコモン
GLOBAL void ZKN_EVENT_MakeChangeZukanCommonSubOnly( int heap, ZKN_EVENT_DATA* p_event_data, ZKN_SYS_PTR zkn_sys, int event_key );

// 図鑑画面
GLOBAL void ZKN_EVENT_MakeChangeZukan( int heap, ZKN_EVENT_DATA* p_event_data, ZKN_SYS_PTR zkn_sys, int event_key );
GLOBAL void ZKN_EVENT_MakeChangeZukanOnly(  int heap, ZKN_EVENT_DATA* p_data, ZKN_SYS_PTR zkn_sys, int event_key  );
GLOBAL void ZKN_EVENT_MakeChangeZukanNormalMainOnly(  int heap, ZKN_EVENT_DATA* p_data, ZKN_SYS_PTR zkn_sys, int event_key  );
GLOBAL void ZKN_EVENT_MakeChangeZukanTextMainOnly(  int heap, ZKN_EVENT_DATA* p_data, ZKN_SYS_PTR zkn_sys, int event_key  );

// すがた画面
GLOBAL void ZKN_EVENT_MakeChangeZukanGraphic(  int heap, ZKN_EVENT_DATA* p_data, ZKN_SYS_PTR zkn_sys, int event_key  );

// 分布画面
GLOBAL void ZKN_EVENT_MakeChangeRange( int heap, ZKN_EVENT_DATA* p_data, ZKN_SYS_PTR zkn_sys, int event_key );
GLOBAL void ZKN_EVENT_MakeChangeRangeMain( int heap, ZKN_EVENT_DATA* p_data, ZKN_SYS_PTR zkn_sys, int event_key );

// 泣き声画面
GLOBAL void ZKN_EVENT_MakeChangeSound( int heap, ZKN_EVENT_DATA* p_data, ZKN_SYS_PTR zkn_sys, int event_key );
GLOBAL void ZKN_EVENT_MakeChangeSoundMain( int heap, ZKN_EVENT_DATA* p_data, ZKN_SYS_PTR zkn_sys, int event_key );

// 大きさ比べ画面へ
GLOBAL void ZKN_EVENT_MakeChangeBig( int heap, ZKN_EVENT_DATA* p_data, ZKN_SYS_PTR zkn_sys, int event_key );
GLOBAL void ZKN_EVENT_MakeChangeBigMain( int heap, ZKN_EVENT_DATA* p_data, ZKN_SYS_PTR zkn_sys, int event_key );
GLOBAL void ZKN_EVENT_MakeChangeBigWeightMain( int heap, ZKN_EVENT_DATA* p_data, ZKN_SYS_PTR zkn_sys, int event_key );

// ポケモンリスト画面
GLOBAL void ZKN_EVENT_MakeChangePokeList( int heap, ZKN_EVENT_DATA* p_data, ZKN_SYS_PTR zkn_sys, int event_key );

// ポケモンリストの上画面のみ変更
GLOBAL void ZKN_EVENT_MakeStartMainPokeList( ZKN_EVENT_DATA* p_event, ZKN_SYS_PTR zkn_sys, int heap, int event_key );


#ifdef PM_DEBUG
// 高さ比べDEBUGアプリへ
GLOBAL void ZKN_EVENT_BigHeightDebugApl( ZKN_EVENT_DATA* p_event, ZKN_SYS_PTR zkn_sys, int heap, int event_key );

// 高さ比べDEBUGアプリから高さ比べに復帰
GLOBAL void ZKN_EVENT_BigHeightDebugAplReturn( ZKN_EVENT_DATA* p_event, ZKN_SYS_PTR zkn_sys, int heap, int event_key );
#endif


#undef	GLOBAL
#endif		// __ZKN_EVENT_FUNC_H__

