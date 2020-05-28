//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_proc_sys.c
 *	@brief		図鑑処理分岐システム
 *	@author		tomoya takahashi
 *	@data		2006.01.17
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include <string.h>

#define __ZKN_PROC_SYS_H_GLOBAL
#include "include/application/zukanlist/zkn_proc_sys.h"

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
//	図鑑プロセスシステムの処理の流れ
//=====================================
enum{
	ZKN_PROC_MAINSEQ_DO_INIT,			// データ変更処理の初期化
	ZKN_PROC_MAINSEQ_DRAW_INIT,			// 描画処理初期化＆フェードイン
	ZKN_PROC_MAINSEQ_MAIN,				// メイン
	ZKN_PROC_MAINSEQ_DRAW_DELETE,		// 描画処理破棄＆フェードアウト
	ZKN_PROC_MAINSEQ_DO_DELETE,			// データ変更処理破棄
	ZKN_PROC_MAINSEQ_ALL_END,			// 全ての処理が終わりました
};

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
 *		プロセスシステム
 */
//-----------------------------------------------------------------------------
typedef struct _ZKN_PROC_SYS{
	// グローバルデータ
	void* p_glb_data;	// 管理者から受け取るグローバルデータ
	void* p_glb_draw;	// 管理者から受け取るグローバルデータ

	// 全体の処理の流れ
	int	main_seq;

	// データ入力＆更新処理
	ZKN_PROC_DO_DATA	do_data;						// 内部ワーク
	ZKN_PROC_DO_FUNC	do_func[ ZKN_PROC_FUNC_NUM ];	// 各処理関数

	// 描画処理
	ZKN_PROC_DRAW_DATA	draw_data;						// 内部ワーク
	ZKN_PROC_DRAW_FUNC	draw_func[ ZKN_PROC_FUNC_NUM ];	// 各処理関数

	// その他
	int heap;				// 使用するヒープ
} ZKN_PROC_SYS;



//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
static void InitProcDoData( ZKN_PROC_DO_DATA* data );
static void InitProcDrawData( ZKN_PROC_DRAW_DATA* data );

static int DoFuncProcDo( ZKN_PROC_DO_FUNC func, ZKN_PROC_DO_DATA* p_do_data, void* p_glb_data );
static int DoFuncProcDraw( ZKN_PROC_DRAW_FUNC func, void* p_glb_draw, ZKN_PROC_DRAW_DATA* p_draw_data, const void* cp_glb_data, const ZKN_PROC_DO_DATA* cp_do_data );

//-----------------------------------------------------------------------------
/**
 *
 *				実装部
 * 
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	メモリ確保
 *
 *	@param	heap	ヒープ
 *
 *	@return	確保して初期化済みのプロセスシステム
 *
 *
 */
//-----------------------------------------------------------------------------
ZKN_PROC_SYS_PTR ZKN_PROC_MemoryAlloc( int heap )
{
	ZKN_PROC_SYS_PTR proc;

	proc = sys_AllocMemory( heap, sizeof(ZKN_PROC_SYS) );
	GF_ASSERT( proc );
	memset( proc, 0, sizeof(ZKN_PROC_SYS) );

	proc->main_seq = ZKN_PROC_MAINSEQ_ALL_END;
	proc->heap = heap;

	return proc;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	初期化処理
 *
 *	@param	proc		プロセスシステム
 *	@param	cp_init		初期化データ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_PROC_Init( ZKN_PROC_SYS_PTR proc, const ZKN_PROC_INIT* cp_init )
{
	GF_ASSERT( proc );
	GF_ASSERT( cp_init );

	// 終了していないのに初期化しようとした
	GF_ASSERT( ZKN_PROC_EndCheck(proc) );

	// プロセスデータの代入
	proc->p_glb_data = cp_init->p_glb_data;		// グローバルデータ
	proc->p_glb_draw = cp_init->p_glb_draw;		// グローバルデータ
	proc->main_seq	 = ZKN_PROC_FUNC_INIT;		// メインシーケンス
	InitProcDoData( &proc->do_data );			// データ変更処理用ワーク
	proc->do_data.heap = proc->heap;
	InitProcDrawData( &proc->draw_data );		// 描画処理用ワーク
	proc->draw_data.heap = proc->heap;

	// 関数ポインタ代入
	proc->do_func[ ZKN_PROC_FUNC_INIT ] = cp_init->cp_do_func[ ZKN_PROC_FUNC_INIT ];
	proc->do_func[ ZKN_PROC_FUNC_MAIN ] = cp_init->cp_do_func[ ZKN_PROC_FUNC_MAIN ];
	proc->do_func[ ZKN_PROC_FUNC_DELETE ] = cp_init->cp_do_func[ ZKN_PROC_FUNC_DELETE ];
	proc->draw_func[ ZKN_PROC_FUNC_INIT ] = cp_init->cp_draw_func[ ZKN_PROC_FUNC_INIT ];
	proc->draw_func[ ZKN_PROC_FUNC_MAIN ] = cp_init->cp_draw_func[ ZKN_PROC_FUNC_MAIN ];
	proc->draw_func[ ZKN_PROC_FUNC_DELETE ] = cp_init->cp_draw_func[ ZKN_PROC_FUNC_DELETE ];
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	メイン処理
 *
 *	@param	proc	プロセスシステム
 *
 *	@retval	ZKN_PROC_TRUE		全て破棄して処理が終わりました。
 *	@retval	ZKN_PROC_FALSE		正常
 *
 *
 */
//-----------------------------------------------------------------------------
int ZKN_PROC_Main( ZKN_PROC_SYS_PTR proc )
{
	int ret;

	GF_ASSERT( proc );

	switch( proc->main_seq ){

	//-------------------------------------
	// データ変更処理の初期化
	//=====================================
	case ZKN_PROC_MAINSEQ_DO_INIT:			
		ret = DoFuncProcDo( proc->do_func[ ZKN_PROC_FUNC_INIT ], &proc->do_data, proc->p_glb_data );
		if( ret == ZKN_PROC_TRUE ){
			proc->main_seq++;
			proc->do_data.seq = 0;
		}
		break;
		
	//-------------------------------------
	// 描画処理初期化＆フェードイン
	//=====================================
	case ZKN_PROC_MAINSEQ_DRAW_INIT:			
		break;
		
	//-------------------------------------
	// メイン
	//=====================================
	case ZKN_PROC_MAINSEQ_MAIN:				
		// データ変更
		ret = DoFuncProcDo( proc->do_func[ ZKN_PROC_FUNC_MAIN ], &proc->do_data, proc->p_glb_data );

		// データ変更が終わりなら終わり
		if( ret == ZKN_PROC_TRUE ){
			proc->main_seq++;
			proc->do_data.seq = 0;
			proc->draw_data.seq = 0;
		}
		break;
		
	//-------------------------------------
	// 描画処理破棄＆フェードアウト
	//=====================================
	case ZKN_PROC_MAINSEQ_DRAW_DELETE:		
		break;
		
	//-------------------------------------
	// データ変更処理破棄
	//=====================================
	case ZKN_PROC_MAINSEQ_DO_DELETE:			
		ret = DoFuncProcDo( proc->do_func[ ZKN_PROC_FUNC_DELETE ], &proc->do_data, proc->p_glb_data );
		if( ret == ZKN_PROC_TRUE ){
			proc->main_seq++;
		}
		break;
		
	//-------------------------------------
	//	全処理変更
	//=====================================
	case ZKN_PROC_MAINSEQ_ALL_END:			// 全ての処理が終わりました
		return ZKN_PROC_TRUE;

	default:
		// ここにくるのはおかしい
		GF_ASSERT(0);
		break;
	}
	
	return ZKN_PROC_FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	描画処理
 *
 *	@param	proc	プロセスデータ
 *
 *	@retval	ZKN_PROC_TRUE		全て破棄して処理が終わりました。
 *	@retval	ZKN_PROC_FALSE		正常
 */
//-----------------------------------------------------------------------------
int ZKN_PROC_Draw( ZKN_PROC_SYS_PTR proc )
{
	int ret;

	GF_ASSERT( proc );

	switch( proc->main_seq ){

	//-------------------------------------
	// データ変更処理の初期化
	//=====================================
	case ZKN_PROC_MAINSEQ_DO_INIT:			
		break;
		
	//-------------------------------------
	// 描画処理初期化＆フェードイン
	//=====================================
	case ZKN_PROC_MAINSEQ_DRAW_INIT:			
		ret = DoFuncProcDraw( proc->draw_func[ ZKN_PROC_FUNC_INIT ], proc->p_glb_draw, &proc->draw_data, proc->p_glb_data, &proc->do_data );
		if( ret == ZKN_PROC_TRUE ){
			proc->main_seq++;
			proc->draw_data.seq = 0;
		}
		break;
		
	//-------------------------------------
	// メイン
	//=====================================
	case ZKN_PROC_MAINSEQ_MAIN:				
		
		// 描画
		DoFuncProcDraw( proc->draw_func[ ZKN_PROC_FUNC_MAIN ], proc->p_glb_draw, &proc->draw_data, proc->p_glb_data, &proc->do_data );
		break;
		
	//-------------------------------------
	// 描画処理破棄＆フェードアウト
	//=====================================
	case ZKN_PROC_MAINSEQ_DRAW_DELETE:		
		ret = DoFuncProcDraw( proc->draw_func[ ZKN_PROC_FUNC_DELETE ], proc->p_glb_draw, &proc->draw_data, proc->p_glb_data, &proc->do_data );
		if( ret == ZKN_PROC_TRUE ){
			proc->main_seq++;
		}
		break;
		
	//-------------------------------------
	// データ変更処理破棄
	//=====================================
	case ZKN_PROC_MAINSEQ_DO_DELETE:			
		break;
		
	//-------------------------------------
	//	全処理変更
	//=====================================
	case ZKN_PROC_MAINSEQ_ALL_END:			// 全ての処理が終わりました
		return ZKN_PROC_TRUE;

	default:
		// ここにくるのはおかしい
		GF_ASSERT(0);
		break;
	}
	
	return ZKN_PROC_FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	メイン動作lock
 *
 *	@param	proc	プロックメイン
 *	@param	lock	動作lockフラグ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_PROC_MoveLock( ZKN_PROC_SYS_PTR proc, BOOL lock )
{
	proc->do_data.lock = lock;
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	終了リクエストを出す
 *
 *	@param	proc	プロセスシステム
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_PROC_EndReq( ZKN_PROC_SYS_PTR proc )
{
	GF_ASSERT( proc );

	proc->do_data.end_req = TRUE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	終了チェック
 *
 *	@param	proc	チェックするプロセスシステム
 *
 *	@retval	TRUE	終了
 *	@retval	FALSE	続行中
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL ZKN_PROC_EndCheck( ZKN_PROC_SYS_PTR proc )
{
	GF_ASSERT( proc );

	if( proc->main_seq == ZKN_PROC_MAINSEQ_ALL_END ){
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	メイン動作しているかチェック
 *
 *	@param	proc	プロセスシステム
 *
 *	@retval	TRUE	メイン動作中
 *	@retval	FALSE	それ以外の処理をしています
 *
 *	メイン動作とはフェードイン終了語の処理です
 */
//-----------------------------------------------------------------------------
BOOL ZKN_PROC_MainMoveCheck( ZKN_PROC_SYS_PTR proc )
{
	GF_ASSERT( proc );

	if( proc->main_seq == ZKN_PROC_MAINSEQ_MAIN ){
		return TRUE;
	}

	return FALSE;
}




//-----------------------------------------------------------------------------
/**
 *			プライベート関数
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	データ変更処理用ワークを使用前の状態にする
 *
 *	@param	data	データ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void InitProcDoData( ZKN_PROC_DO_DATA* data )
{
	data->seq = 0;
	data->p_work = NULL;
	data->end_req = FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	描画用ワークを使用前の状態にする
 *
 *	@param	data	ワーク
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void InitProcDrawData( ZKN_PROC_DRAW_DATA* data )
{
	data->seq = 0;
	data->p_work = NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	データ変更処理　関数実行
 *
 *	@param	func			関数
 *	@param	p_do_data		データ変更処理ワーク
 *	@param	p_glb_data		グローバルデータ
 *
 *	@retval	ZKN_PROC_TRUE		次の処理へ
 *	@retval	ZKN_PROC_FALSE		正常
 *
 *
 */
//-----------------------------------------------------------------------------
static int DoFuncProcDo( ZKN_PROC_DO_FUNC func, ZKN_PROC_DO_DATA* p_do_data, void* p_glb_data )
{
	int ret;
	
	GF_ASSERT( func );
	GF_ASSERT( p_do_data );
//	GF_ASSERT( p_glb_data );

	ret = func( p_do_data, p_glb_data );

	return ret;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	描画処理関数を実行
 *
 *	@param	func			関数ポインタ
 *	@param	p_glb_draw		描画用グローバルデータ
 *	@param	p_draw_data		描画処理ワーク
 *	@param	cp_glb_data		グローバルデータ
 *	@param	cp_do_data		内部ワーク 
 *
 *	@retval	ZKN_PROC_TRUE		全て破棄して処理が終わりました。
 *	@retval	ZKN_PROC_FALSE		正常
 *
 *
 */
//-----------------------------------------------------------------------------
static int DoFuncProcDraw( ZKN_PROC_DRAW_FUNC func, void* p_glb_draw,  ZKN_PROC_DRAW_DATA* p_draw_data, const void* cp_glb_data, const ZKN_PROC_DO_DATA* cp_do_data )
{
	int ret;
	
	GF_ASSERT( func );
	GF_ASSERT( p_draw_data );
	GF_ASSERT( cp_do_data );
//	GF_ASSERT( cp_glb_data );
//	GF_ASSERT( p_glb_draw );

	ret = func( p_glb_draw, p_draw_data, cp_glb_data, cp_do_data );

	return ret;
}
