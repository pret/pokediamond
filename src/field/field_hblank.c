//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		field_hblank.c
 *	@brief		フィールドHBlankシステム
 *	@author		tomoya takahashi
 *	@data		2006.04.10
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include <string.h>

#define	__FIELD_HBLANK_H_GLOBAL
#include "field_hblank.h"

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
//-------------------------------------
//
//	Hブランク期間内に動作するオブジェクト数
//
//=====================================
#define FIELD_HBLANK_WORK_NUM	 ( 2 )

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	Hブランク期間ワーク
//=====================================
typedef struct _FIELD_HBLANK_OBJ{
	u32	status;
	void* p_work;
	FLDHBLANK_FUNC func;
};

//-------------------------------------
//	Hブランク期間管理システム
//=====================================
typedef struct _FIELD_HBLANK_SYS{
	u32	status;
	FIELD_HBLANK_OBJ work[ FIELD_HBLANK_WORK_NUM ];
} ;


//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
static void FldHblank_InitSys( FIELD_HBLANK_SYS* p_sys );
static void FldHblank_InitObj( FIELD_HBLANK_OBJ* p_obj );
static void Field_Sys_HBlank( void* p_work );
static void Field_Sys_DummyCallBack( FIELD_HBLANK_OBJ* p_obj, void* p_work );

static FIELD_HBLANK_OBJ* FldHblank_GetCleanObj( FIELD_HBLANK_SYS* p_sys );

//----------------------------------------------------------------------------
/**
 *	@brief	【管理システム】初期化関数
 *	@param	heap 
 *	@return	作成した【管理システム】
 */
//-----------------------------------------------------------------------------
FIELD_HBLANK_SYS* FLDHBLANK_SYS_Init( u32 heap )
{
	FIELD_HBLANK_SYS* p_sys;

	// メモリ確保
	p_sys = sys_AllocMemory( heap, sizeof(FIELD_HBLANK_SYS) );
	FldHblank_InitSys( p_sys );

	return p_sys;
}

//----------------------------------------------------------------------------
/**
 *	@brief	【管理システム】破棄処理
 *	@param	p_sys	【管理システム】
 */
//-----------------------------------------------------------------------------
void FLDHBLANK_SYS_Delete( FIELD_HBLANK_SYS* p_sys )
{
	if( p_sys == NULL ){ return ; }
	
	// HBlank割り込みの解除
	if( p_sys->status == FIELD_HBLANK_STATE_DO ){
		FLDHBLANK_SYS_Stop( p_sys );
	}

	// 管理データクリーン
	FldHblank_InitSys( p_sys );
	
	// 全体ワーク破棄
	sys_FreeMemoryEz( p_sys );
}

//----------------------------------------------------------------------------
/**
 *	@brief	【管理システム】HBlank処理	スタート　HBLANK割り込み設定
 *	@param	p_sys	【管理システム】
 */
//-----------------------------------------------------------------------------
void FLDHBLANK_SYS_Start( FIELD_HBLANK_SYS* p_sys )
{
	BOOL result;
	result = sys_HBlankIntrSet( Field_Sys_HBlank, p_sys );
	// 設定失敗
	GF_ASSERT( result == TRUE );

	p_sys->status = FIELD_HBLANK_STATE_DO;
}

//----------------------------------------------------------------------------
/**
 *	@brief	【管理システム】HBlank処理終了	HBLANK割り込みの解除
 *	@param	p_sys	【管理システム】
 */
//-----------------------------------------------------------------------------
void FLDHBLANK_SYS_Stop( FIELD_HBLANK_SYS* p_sys )
{
	BOOL result;
	result = sys_HBlankIntrSet( NULL, NULL );
	// 設定失敗
	GF_ASSERT( result == TRUE );

	p_sys->status = FIELD_HBLANK_STATE_STANDBY;
}

//----------------------------------------------------------------------------
/**
 *	@brief	【管理システム】の状態を取得
 *	@param	cp_sys	【管理システム】
 *
 *	@return	FIELD_HBLANK_STATE_STANDBY	開始待ち
 *	@return	FIELD_HBLANK_STATE_DO		実行中
 */
//-----------------------------------------------------------------------------
u32 FLDHBLANK_SYS_GetState( const FIELD_HBLANK_SYS* cp_sys )
{
	return cp_sys->status;
}

//-----------------------------------------------------------------------------
/**
 *					【オブジェクト】プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	【オブジェクト】登録
 *	@param	p_sys		【管理システム】
 *	@param	func		コールバック関数
 *	@param	p_work		ワーク
 *
 *	@return	作成された【オブジェクト】	NULLの時失敗（最大数登録済み）
 */
//-----------------------------------------------------------------------------
FIELD_HBLANK_OBJ* FLDHBLANK_OBJ_Add( FIELD_HBLANK_SYS* p_sys, FLDHBLANK_FUNC func, void* p_work )
{
	FIELD_HBLANK_OBJ* p_obj;
	p_obj = FldHblank_GetCleanObj( p_sys );
	// 登録失敗　　最大数を超えた登録をしようとしました
	GF_ASSERT( p_obj );
	if( p_obj ){
		p_obj->p_work	= p_work;
		p_obj->func		= func;
		p_obj->status	= FIELD_HBLANK_STATE_DO;
	}
	return p_obj;
}

//----------------------------------------------------------------------------
/**
 *	@brief	【オブジェクト】破棄
 *	@param	p_obj	【オブジェクト】
 */
//-----------------------------------------------------------------------------
void FLDHBLANK_OBJ_Delete( FIELD_HBLANK_OBJ* p_obj )
{
	FldHblank_InitObj( p_obj );
}



//-----------------------------------------------------------------------------
/**
 *		ローカル関数
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	システムワーク初期化
 *	@param	p_sys	管理システム
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FldHblank_InitSys( FIELD_HBLANK_SYS* p_sys )
{
	int i;
	memset( p_sys, 0, sizeof(FIELD_HBLANK_SYS) );
	p_sys->status = FIELD_HBLANK_STATE_STANDBY;
	for( i=0; i<FIELD_HBLANK_WORK_NUM; i++ ){
		FldHblank_InitObj( &p_sys->work[i] );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	オブジェクトワーク初期化
 *	@param	p_obj	オブジェクト
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void FldHblank_InitObj( FIELD_HBLANK_OBJ* p_obj )
{
	// この初期化を行っているときにHブランク期間が来ることも考え
	// ワークの初期化を一番下にする
	p_obj->status = FIELD_HBLANK_STATE_STANDBY;
	p_obj->func	  = Field_Sys_DummyCallBack;
	p_obj->p_work = NULL;
}

//----------------------------------------------------------------------------
/**
 *	@brief	Hブランク関数
 *	@param	p_work	ワーク
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void Field_Sys_HBlank( void* p_work )
{
	int i;
	FIELD_HBLANK_SYS* p_sys = p_work;

	for( i=0; i<FIELD_HBLANK_WORK_NUM; i++ ){
		p_sys->work[i].func( &p_sys->work[i], p_sys->work[i].p_work );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	コールバック関数初期化用　ダミーコールバック
 *	@param	p_obj		オブジェ
 *	@param	p_work		ワーク
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void Field_Sys_DummyCallBack( FIELD_HBLANK_OBJ* p_obj, void* p_work )
{
}

//----------------------------------------------------------------------------
/**
 *	@brief	空いているオブジェクトワークを取得
 *
 *	@param	p_sys	システムワーク
 *
 *	@return	オブジェクトワーク	NULL　最大数使用中
 */
//-----------------------------------------------------------------------------
static FIELD_HBLANK_OBJ* FldHblank_GetCleanObj( FIELD_HBLANK_SYS* p_sys )
{
	int i;
	for( i=0; i<FIELD_HBLANK_WORK_NUM; i++ ){
		if( p_sys->work[i].status == FIELD_HBLANK_STATE_STANDBY ){
			return &p_sys->work[i];
		}
	}
	return NULL;
}

