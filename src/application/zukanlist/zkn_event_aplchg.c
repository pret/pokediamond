//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_event_aplchg.c
 *	@brief		アプリケーション変更イベント
 *	@author		tomoya takahashi 
 *	@data		2006.01.18
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include <string.h>

#include "include/application/zukanlist/zkn_event_func.h"

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

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
static void ZknAplStart( ZKN_APL_DATA* p_apl, ZKN_EVENT_SYS_PTR p_event, ZKN_PROC_SYS_PTR p_proc );

//-----------------------------------------------------------------------------
/**
 *		何も無しー＞アプリケーション開始
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief		アプリケーション開始
 *
 *	@param		p_work	ワーク
 *
 *	@retval		TRUE	イベント終了
 *	@retval		FALSE	イベント続行
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL ZKN_EVENT_AplStart( ZKN_EVENT_WORK* p_work )
{
	ZKN_EVENT_APL_START*	p_data = p_work->p_data;

	switch( p_work->seq ){
	case 0:
		// アプリケーション開始
		ZknAplStart( p_data->p_apl, p_data->p_event, p_data->p_proc );
		p_work->seq++;
		break;

	case 1:
		// 動作開始を確認
		if( ZKN_PROC_MainMoveCheck( p_data->p_proc ) == TRUE ){
			p_work->seq++;
		}
		break;
		
	case 2:
		return TRUE;
	}

	return FALSE;
}



//-----------------------------------------------------------------------------
/**
 *		前のアプリケーション終了ー＞次のアプリケーション開始
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief		アプリケーション変更
 *
 *	@param		p_work	ワーク
 *
 *	@retval		TRUE	イベント終了
 *	@retval		FALSE	イベント続行
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL ZKN_EVENT_AplChange( ZKN_EVENT_WORK* p_work )
{
	ZKN_EVENT_APL_CHANGE*	p_data = p_work->p_data;

	switch( p_work->seq ){
	//-------------------------------------
	//		今のプロセス終了
	//=====================================
	case 0:
		ZKN_PROC_EndReq( p_data->p_proc );
		p_work->seq++;
		break;

	//-------------------------------------
	//		終了チェック
	//=====================================
	case 1:
		if( ZKN_PROC_EndCheck( p_data->p_proc ) == TRUE ){
			p_work->seq++;
		}
		break;

	//-------------------------------------
	//		次開始
	//=====================================
	case 2:
		// アプリケーション開始
		ZknAplStart( p_data->p_apl, p_data->p_event, p_data->p_proc );
		p_work->seq++;
		break;

	//-------------------------------------
	//		開始チェック
	//=====================================
	case 3:
		if( ZKN_PROC_MainMoveCheck( p_data->p_proc ) == TRUE ){
			return TRUE;
		}
		break;

	default:
		// ここにくるのはおかしい
		GF_ASSERT( 0 );
		break;
	}

	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 *		今のアプリケーション終了ー＞図鑑破棄
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	今のアプリケーションを終了させ図鑑の終了
 *
 *	@param	p_work	ワーク
 *
 *	@retval		TRUE	イベント終了
 *	@retval		FALSE	イベント続行
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL ZKN_EVENT_AplEndZknDelete( ZKN_EVENT_WORK* p_work )
{
	ZKN_EVENT_APL_END_ZKN_DELETE*	p_data = p_work->p_data;
	BOOL check[4];
	int i;

	switch( p_work->seq ){
	//-------------------------------------
	//		今のプロセス終了
	//=====================================
	case 0:
		ZKN_PROC_EndReq( p_data->p_proc_m );
		ZKN_PROC_EndReq( p_data->p_proc_s );
		ZKN_PROC_EndReq( p_data->p_proc_mc );
		ZKN_PROC_EndReq( p_data->p_proc_sc );
		p_work->seq++;
		break;

	//-------------------------------------
	//		終了チェック
	//=====================================
	case 1:
		check[0] = ZKN_PROC_EndCheck( p_data->p_proc_m );
		check[1] = ZKN_PROC_EndCheck( p_data->p_proc_s );
		check[2] = ZKN_PROC_EndCheck( p_data->p_proc_mc );
		check[3] = ZKN_PROC_EndCheck( p_data->p_proc_sc );
		for( i=0; i<4; i++ ){
			if( check[ i ] == FALSE ){
				break;
			}
		}
		if( i >= 4 ){
			p_work->seq++;
		}
		break;

	//-------------------------------------
	//		破棄フラグを立てる
	//=====================================
	case 2:
		*p_data->p_delete_flag = TRUE;
		return TRUE;

	default:
		// ここにくるのはおかしい
		GF_ASSERT( 0 );
		break;
	}

	return FALSE;
}



//-----------------------------------------------------------------------------
/**
 *	今のアプリケーション終了
 */
//-----------------------------------------------------------------------------
BOOL ZKN_EVENT_AplEnd( ZKN_EVENT_WORK* p_work )
{
	ZKN_EVENT_APL_END* p_data = p_work->p_data;

	switch( p_work->seq ){
	//-------------------------------------
	//		今のプロセス終了
	//=====================================
	case 0:
		ZKN_PROC_EndReq( p_data->p_proc );
		p_work->seq++;
		break;

	//-------------------------------------
	//		終了チェック
	//=====================================
	case 1:
		
		if( ZKN_PROC_EndCheck( p_data->p_proc ) ){
			p_work->seq++;
		}
		break;

	//-------------------------------------
	//		破棄フラグを立てる
	//=====================================
	case 2:
		// イベントデータ破棄
		ZKN_EVENT_Init( p_data->p_event, NULL, 0 );
		return TRUE;

	default:
		// ここにくるのはおかしい
		GF_ASSERT( 0 );
		break;
	}

	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 *		main画面サブ画面全変更
 */
//-----------------------------------------------------------------------------
BOOL ZKN_EVENT_AplAllChange( ZKN_EVENT_WORK* p_work )
{
	ZKN_EVENT_APL_AllCHANGE*	p_data = p_work->p_data;
	BOOL check[4];
	int i;

	switch( p_work->seq ){
	//-------------------------------------
	//		今のプロセス終了
	//=====================================
	case 0:
		ZKN_PROC_EndReq( p_data->p_proc_m );
		ZKN_PROC_EndReq( p_data->p_proc_s );
		ZKN_PROC_EndReq( p_data->p_proc_mc );
		ZKN_PROC_EndReq( p_data->p_proc_sc );
		p_work->seq++;
		break;

	//-------------------------------------
	//		終了チェック
	//=====================================
	case 1:
		check[0] = ZKN_PROC_EndCheck( p_data->p_proc_m );
		check[1] = ZKN_PROC_EndCheck( p_data->p_proc_s );
		check[2] = ZKN_PROC_EndCheck( p_data->p_proc_mc );
		check[3] = ZKN_PROC_EndCheck( p_data->p_proc_sc );
		for( i=0; i<4; i++ ){
			if( check[ i ] == FALSE ){
				break;
			}
		}
		if( i >= 4 ){
			p_work->seq++;
		}
		break;

	//-------------------------------------
	//		次開始
	//=====================================
	case 2:
		// アプリケーション開始
		ZknAplStart( p_data->p_apl_m, p_data->p_event_m, p_data->p_proc_m );
		ZknAplStart( p_data->p_apl_s, p_data->p_event_s, p_data->p_proc_s );
		ZknAplStart( p_data->p_apl_mc, p_data->p_event_mc, p_data->p_proc_mc );
		ZknAplStart( p_data->p_apl_sc, p_data->p_event_sc, p_data->p_proc_sc );
		p_work->seq++;
		break;

	//-------------------------------------
	//		アプリケーション開始をチェック	
	//=====================================
	case 3:
		if( p_data->p_apl_m ){
			check[0] = ZKN_PROC_MainMoveCheck( p_data->p_proc_m );
		}else{
			check[0] = TRUE;
		}
		if( p_data->p_apl_s ){
			check[1] = ZKN_PROC_MainMoveCheck( p_data->p_proc_s );
		}
		if( p_data->p_apl_mc ){
			check[2] = ZKN_PROC_MainMoveCheck( p_data->p_proc_mc );
		}else{
			check[2] = TRUE;
		}
		if( p_data->p_apl_sc ){
			check[3] = ZKN_PROC_MainMoveCheck( p_data->p_proc_sc );
		}else{
			check[3] = TRUE;
		}
		
		for( i=0; i<4; i++ ){
			if( check[ i ] == FALSE ){
				break;
			}
		}
		if( i >= 4 ){
			return TRUE;
		}
		break;

	default:
		// ここにくるのはおかしい
		GF_ASSERT( 0 );
		break;
	}

	return FALSE;
}

//-----------------------------------------------------------------------------
/**
 *		main画面サブ画面	２つ変更
 */
//-----------------------------------------------------------------------------
BOOL ZKN_EVENT_AplDoubleChange( ZKN_EVENT_WORK* p_work )
{
	ZKN_EVENT_APL_DOUBLE_CHANGE*	p_data = p_work->p_data;
	BOOL check[2];
	int i;

	switch( p_work->seq ){
	//-------------------------------------
	//		今のプロセス終了
	//=====================================
	case 0:
		ZKN_PROC_EndReq( p_data->p_proc_m );
		ZKN_PROC_EndReq( p_data->p_proc_s );
		p_work->seq++;
		break;

	//-------------------------------------
	//		終了チェック
	//=====================================
	case 1:
		check[0] = ZKN_PROC_EndCheck( p_data->p_proc_m );
		check[1] = ZKN_PROC_EndCheck( p_data->p_proc_s );
		for( i=0; i<2; i++ ){
			if( check[ i ] == FALSE ){
				break;
			}
		}
		if( i >= 2 ){
			p_work->seq++;
		}
		break;

	//-------------------------------------
	//		次開始
	//=====================================
	case 2:
		// アプリケーション開始
		ZknAplStart( p_data->p_apl_m, p_data->p_event_m, p_data->p_proc_m );
		ZknAplStart( p_data->p_apl_s, p_data->p_event_s, p_data->p_proc_s );
		p_work->seq++;
		break;

	//-------------------------------------
	//		アプリケーション開始チェック
	//=====================================
	case 3:
		if( p_data->p_apl_m ){
			check[0] = ZKN_PROC_MainMoveCheck( p_data->p_proc_m );
		}else{
			check[0] = TRUE;
		}
		if( p_data->p_apl_s ){
			check[1] = ZKN_PROC_MainMoveCheck( p_data->p_proc_s );
		}else{
			check[1] = TRUE;
		}
		
		for( i=0; i<2; i++ ){
			if( check[ i ] == FALSE ){
				break;
			}
		}
		if( i >= 2 ){
			return TRUE;
		}
		break;

	default:
		// ここにくるのはおかしい
		GF_ASSERT( 0 );
		break;
	}

	return FALSE;
}




//-----------------------------------------------------------------------------
/**
 *		プライベート関数
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	アプリケーションの開始
 *
 *	@param	p_apl		アプリケーションデータ
 *	@param	p_event		イベントシステム
 *	@param	p_proc		プロセスシステム
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void ZknAplStart( ZKN_APL_DATA* p_apl, ZKN_EVENT_SYS_PTR p_event, ZKN_PROC_SYS_PTR p_proc )
{
	ZKN_PROC_INIT			proc_init;

	// アプリケーションデータがあるかチェック
	if( p_apl ){

		// プロセスに登録
		proc_init.p_glb_data	= p_apl->p_glb_data;
		proc_init.p_glb_draw	= p_apl->p_glb_draw;
		proc_init.cp_do_func	= p_apl->do_func;
		proc_init.cp_draw_func	= p_apl->draw_func;
		ZKN_PROC_Init( p_proc, &proc_init );

		// イベント登録
		ZKN_EVENT_Init( p_event, p_apl->p_event_data, p_apl->event_num );
	}
}








//-----------------------------------------------------------------------------
/**
 *		各アプリケーションに変更するイベントデータ作成関数
 */
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	イベントデータ破棄関数
 *
 *	@param	p_event_data	データ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_EVENT_DeleteData( ZKN_EVENT_DATA* p_event_data )
{
	GF_ASSERT( p_event_data->work.p_data );

	sys_FreeMemoryEz( p_event_data->work.p_data );
	p_event_data->work.p_data = NULL;
}

// ソート画面
//----------------------------------------------------------------------------
/**
 *
 *	@brief	検索ソートに変更するイベント生成
 *
 *	@param	heap				ヒープ
 *	@param	p_event_data		イベントデータ
 *	@param	zkn_sys				図鑑システム
 *	@param	event_key			イベントキー
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_EVENT_MakeChangeSortSearch( int heap, ZKN_EVENT_DATA* p_event_data, ZKN_SYS_PTR zkn_sys, int event_key )
{
	ZKN_EVENT_APL_AllCHANGE* p_e_data;
	
	p_event_data->key_msk	= event_key;
	p_event_data->func		= ZKN_EVENT_AplAllChange;
	
	// イベントデータ作成
	p_e_data = sys_AllocMemory( heap, sizeof(ZKN_EVENT_APL_AllCHANGE) );
	GF_ASSERT( p_e_data );
	memset( p_e_data, 0, sizeof(ZKN_EVENT_APL_AllCHANGE) );
	p_e_data->p_proc_m	= ZKN_SYS_GetProcSysMain( zkn_sys );			// プロックシステム
	p_e_data->p_proc_s	= ZKN_SYS_GetProcSysSub( zkn_sys );				// プロックシステム
	p_e_data->p_proc_mc	= ZKN_SYS_GetProcSysMainCommon( zkn_sys );		// プロックシステム
	p_e_data->p_proc_sc	= ZKN_SYS_GetProcSysSubCommon( zkn_sys );		// プロックシステム
		
	p_e_data->p_event_m	= ZKN_SYS_GetEventSysMain( zkn_sys );		// イベントシステム
	p_e_data->p_event_s	= ZKN_SYS_GetEventSysSub( zkn_sys );		// イベントシステム
	p_e_data->p_event_mc= ZKN_SYS_GetEventSysMainCommon( zkn_sys );		// イベントシステム
	p_e_data->p_event_sc= ZKN_SYS_GetEventSysSubCommon( zkn_sys );		// イベントシステム

	p_e_data->p_apl_m	= ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_SORTSEARCH );		// 始めるアプリケーションデータ
	p_e_data->p_apl_s	= ZKN_GetAplDataSub( zkn_sys, ZKN_SYS_APLSUB_SORTSEARCH );		// 始めるアプリケーションデータ
	p_e_data->p_apl_mc	= NULL;		// 始めるアプリケーションデータ
	p_e_data->p_apl_sc	= NULL;		// 始めるアプリケーションデータ
	
	p_event_data->work.p_data = p_e_data;
}

// 図鑑システム終了
//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑終了イベントの生成
 *
 *	@param	heap			ヒープID
 *	@param	p_event_data	イベントデータ
 *	@param	zkn_sys			図鑑システム
 *	@param	event_key			イベントキー
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_EVENT_MakeZukanEnd( int heap, ZKN_EVENT_DATA* p_event_data, ZKN_SYS_PTR zkn_sys, int event_key )
{
	ZKN_EVENT_APL_END_ZKN_DELETE* p_e_data;
	
	p_event_data->key_msk	= event_key;
	p_event_data->func		= ZKN_EVENT_AplEndZknDelete;
	
	// イベントデータ作成
	p_e_data = sys_AllocMemory( heap, sizeof(ZKN_EVENT_APL_END_ZKN_DELETE) );
	GF_ASSERT( p_e_data );
	memset( p_e_data, 0, sizeof(ZKN_EVENT_APL_END_ZKN_DELETE) );
	p_e_data->p_proc_m	= ZKN_SYS_GetProcSysMain( zkn_sys );
	p_e_data->p_proc_s	= ZKN_SYS_GetProcSysSub( zkn_sys );
	p_e_data->p_proc_mc	= ZKN_SYS_GetProcSysMainCommon( zkn_sys );
	p_e_data->p_proc_sc	= ZKN_SYS_GetProcSysSubCommon( zkn_sys );
	p_e_data->p_delete_flag	= ZKN_SYS_GetZknDeleteFlag( zkn_sys );
	
	p_event_data->work.p_data = p_e_data;
}


// 図鑑画面
//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑に変更するイベント生成
 *
 *	@param	heap				ヒープ
 *	@param	p_event_data		イベントデータ
 *	@param	zkn_sys				図鑑システム
 *	@param	event_key			イベントキー
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_EVENT_MakeChangeZukan( int heap, ZKN_EVENT_DATA* p_event_data, ZKN_SYS_PTR zkn_sys, int event_key )
{
	ZKN_EVENT_APL_AllCHANGE* p_e_data;
	
	p_event_data->key_msk	= event_key;
	p_event_data->func		= ZKN_EVENT_AplAllChange;
	
	// イベントデータ作成
	p_e_data = sys_AllocMemory( heap, sizeof(ZKN_EVENT_APL_AllCHANGE) );
	GF_ASSERT( p_e_data );
	memset( p_e_data, 0, sizeof(ZKN_EVENT_APL_AllCHANGE) );
	p_e_data->p_proc_m	= ZKN_SYS_GetProcSysMain( zkn_sys );			// プロックシステム
	p_e_data->p_proc_s	= ZKN_SYS_GetProcSysSub( zkn_sys );				// プロックシステム
	p_e_data->p_proc_mc	= ZKN_SYS_GetProcSysMainCommon( zkn_sys );		// プロックシステム
	p_e_data->p_proc_sc	= ZKN_SYS_GetProcSysSubCommon( zkn_sys );		// プロックシステム
		
	p_e_data->p_event_m	= ZKN_SYS_GetEventSysMain( zkn_sys );		// イベントシステム
	p_e_data->p_event_s	= ZKN_SYS_GetEventSysSub( zkn_sys );		// イベントシステム
	p_e_data->p_event_mc= ZKN_SYS_GetEventSysMainCommon( zkn_sys );		// イベントシステム
	p_e_data->p_event_sc= ZKN_SYS_GetEventSysSubCommon( zkn_sys );		// イベントシステム

	p_e_data->p_apl_m	= ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_ZUKAN );		// 始めるアプリケーションデータ
	p_e_data->p_apl_s	= ZKN_GetAplDataSub( zkn_sys, ZKN_SYS_APLSUB_ZUKAN );		// 始めるアプリケーションデータ
	p_e_data->p_apl_mc	= ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_ZUKAN_COMMON );		// 始めるアプリケーションデータ
	p_e_data->p_apl_sc	= ZKN_GetAplDataSub( zkn_sys, ZKN_SYS_APLSUB_ZUKAN_COMMON );		// 始めるアプリケーションデータ
	
	p_event_data->work.p_data = p_e_data;
}

// ポケモンリスト画面
//----------------------------------------------------------------------------
/**
 *
 *	@brief	ポケモンリストに移動
 *
 *	@param	heap		ヒープ
 *	@param	p_data		イベントデータ
 *	@param	zkn_sys		図鑑システム
 *	@param	event_key			イベントキー
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_EVENT_MakeChangePokeList( int heap, ZKN_EVENT_DATA* p_data, ZKN_SYS_PTR zkn_sys, int event_key )
{
	ZKN_EVENT_APL_AllCHANGE* p_e_data;
	
	p_data->key_msk	= event_key;
	p_data->func		= ZKN_EVENT_AplAllChange;
	
	// イベントデータ作成
	p_e_data = sys_AllocMemory( heap, sizeof(ZKN_EVENT_APL_AllCHANGE) );
	GF_ASSERT( p_e_data );
	memset( p_e_data, 0, sizeof(ZKN_EVENT_APL_AllCHANGE) );
	p_e_data->p_proc_m	= ZKN_SYS_GetProcSysMain( zkn_sys );			// プロックシステム
	p_e_data->p_proc_s	= ZKN_SYS_GetProcSysSub( zkn_sys );				// プロックシステム
	p_e_data->p_proc_mc	= ZKN_SYS_GetProcSysMainCommon( zkn_sys );		// プロックシステム
	p_e_data->p_proc_sc	= ZKN_SYS_GetProcSysSubCommon( zkn_sys );		// プロックシステム
		
	p_e_data->p_event_m	= ZKN_SYS_GetEventSysMain( zkn_sys );		// イベントシステム
	p_e_data->p_event_s	= ZKN_SYS_GetEventSysSub( zkn_sys );		// イベントシステム
	p_e_data->p_event_mc= ZKN_SYS_GetEventSysMainCommon( zkn_sys );		// イベントシステム
	p_e_data->p_event_sc= ZKN_SYS_GetEventSysSubCommon( zkn_sys );		// イベントシステム

	p_e_data->p_apl_m	= ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_POKELIST );		// 始めるアプリケーションデータ
	p_e_data->p_apl_s	= ZKN_GetAplDataSub( zkn_sys, ZKN_SYS_APLSUB_POKELIST );		// 始めるアプリケーションデータ
	p_e_data->p_apl_mc	= NULL;		// 始めるアプリケーションデータ
	p_e_data->p_apl_sc	= NULL;		// 始めるアプリケーションデータ
	
	p_data->work.p_data = p_e_data;
}

// ポケモンリストの上画面のみ変更
//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンリストを再スタート
 *
 *	@param	p_event		イベント格納先
 *	@param	zkn_sys		図鑑システム
 *	@param	heap		ヒープ
 *	@param	event_key			イベントキー
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_EVENT_MakeStartMainPokeList( ZKN_EVENT_DATA* p_event, ZKN_SYS_PTR zkn_sys, int heap, int event_key )
{
	ZKN_EVENT_APL_CHANGE* p_aplchg;
	
	p_event->key_msk	= event_key;
	p_event->func		= ZKN_EVENT_AplChange;

	// イベントワーク作成
	p_aplchg = sys_AllocMemory( heap, sizeof(ZKN_EVENT_APL_CHANGE) );
	GF_ASSERT( p_aplchg );
	p_aplchg->p_apl		= ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_POKELIST );
	p_aplchg->p_proc	= ZKN_SYS_GetProcSysMain( zkn_sys );
	p_aplchg->p_event	= ZKN_SYS_GetEventSysMain( zkn_sys );
	
	// イベントワーク設定
	p_event->work.p_data = p_aplchg;
}

//----------------------------------------------------------------------------
/**
 *	@brief	分布図移動
 *
 *	@param	heap		ヒープ
 *	@param	p_data		イベントデータ
 *	@param	zkn_sys		図鑑システム
 *	@param	event_key	イベントキー
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_EVENT_MakeChangeRange( int heap, ZKN_EVENT_DATA* p_data, ZKN_SYS_PTR zkn_sys, int event_key )
{
	ZKN_EVENT_APL_DOUBLE_CHANGE* p_e_data;
	
	p_data->key_msk		= event_key;
	p_data->func		= ZKN_EVENT_AplDoubleChange;
	
	// イベントデータ作成
	p_e_data = sys_AllocMemory( heap, sizeof(ZKN_EVENT_APL_DOUBLE_CHANGE) );
	GF_ASSERT( p_e_data );
	memset( p_e_data, 0, sizeof(ZKN_EVENT_APL_DOUBLE_CHANGE) );
	p_e_data->p_proc_m	= ZKN_SYS_GetProcSysMain( zkn_sys );			// プロックシステム
	p_e_data->p_proc_s	= ZKN_SYS_GetProcSysSub( zkn_sys );				// プロックシステム
		
	p_e_data->p_event_m	= ZKN_SYS_GetEventSysMain( zkn_sys );		// イベントシステム
	p_e_data->p_event_s	= ZKN_SYS_GetEventSysSub( zkn_sys );		// イベントシステム

	p_e_data->p_apl_m	= ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_RANGE );		// 始めるアプリケーションデータ
	p_e_data->p_apl_s	= ZKN_GetAplDataSub( zkn_sys, ZKN_SYS_APLSUB_RANGE );		// 始めるアプリケーションデータ
	
	p_data->work.p_data = p_e_data;
}

//----------------------------------------------------------------------------
/**
 *	@brief	分布のメイン画面だけ変更
 *
 *	@param	heap		ヒープ
 *	@param	p_data		イベントデータ
 *	@param	zkn_sys		図鑑システム
 *	@param	event_key	イベントキー
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_EVENT_MakeChangeRangeMain( int heap, ZKN_EVENT_DATA* p_data, ZKN_SYS_PTR zkn_sys, int event_key )
{
	ZKN_EVENT_APL_CHANGE* p_e_data;
	
	p_data->key_msk		= event_key;
	p_data->func		= ZKN_EVENT_AplChange;
	
	// イベントデータ作成
	p_e_data = sys_AllocMemory( heap, sizeof(ZKN_EVENT_APL_CHANGE) );
	GF_ASSERT( p_e_data );
	memset( p_e_data, 0, sizeof(ZKN_EVENT_APL_CHANGE) );
	p_e_data->p_proc	= ZKN_SYS_GetProcSysMain( zkn_sys );			// プロックシステム
		
	p_e_data->p_event	= ZKN_SYS_GetEventSysMain( zkn_sys );		// イベントシステム

	p_e_data->p_apl	= ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_RANGE );		// 始めるアプリケーションデータ
	
	p_data->work.p_data = p_e_data;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	泣き声移動
 *
 *	@param	heap		ヒープ
 *	@param	p_data		イベントデータ
 *	@param	zkn_sys		図鑑システム
 *	@param	event_key	イベントキー
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_EVENT_MakeChangeSound( int heap, ZKN_EVENT_DATA* p_data, ZKN_SYS_PTR zkn_sys, int event_key )
{
	ZKN_EVENT_APL_DOUBLE_CHANGE* p_e_data;
	
	p_data->key_msk		= event_key;
	p_data->func		= ZKN_EVENT_AplDoubleChange;
	
	// イベントデータ作成
	p_e_data = sys_AllocMemory( heap, sizeof(ZKN_EVENT_APL_DOUBLE_CHANGE) );
	GF_ASSERT( p_e_data );
	memset( p_e_data, 0, sizeof(ZKN_EVENT_APL_DOUBLE_CHANGE) );
	p_e_data->p_proc_m	= ZKN_SYS_GetProcSysMain( zkn_sys );			// プロックシステム
	p_e_data->p_proc_s	= ZKN_SYS_GetProcSysSub( zkn_sys );				// プロックシステム
		
	p_e_data->p_event_m	= ZKN_SYS_GetEventSysMain( zkn_sys );		// イベントシステム
	p_e_data->p_event_s	= ZKN_SYS_GetEventSysSub( zkn_sys );		// イベントシステム

	p_e_data->p_apl_m	= ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_SOUND );		// 始めるアプリケーションデータ
	p_e_data->p_apl_s	= ZKN_GetAplDataSub( zkn_sys, ZKN_SYS_APLSUB_SOUND );		// 始めるアプリケーションデータ
	
	p_data->work.p_data = p_e_data;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	泣き声移動
 *
 *	@param	heap		ヒープ
 *	@param	p_data		イベントデータ
 *	@param	zkn_sys		図鑑システム
 *	@param	event_key	イベントキー
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_EVENT_MakeChangeSoundMain( int heap, ZKN_EVENT_DATA* p_data, ZKN_SYS_PTR zkn_sys, int event_key )
{
	ZKN_EVENT_APL_CHANGE* p_e_data;
	
	p_data->key_msk		= event_key;
	p_data->func		= ZKN_EVENT_AplChange;
	
	// イベントデータ作成
	p_e_data = sys_AllocMemory( heap, sizeof(ZKN_EVENT_APL_CHANGE) );
	GF_ASSERT( p_e_data );
	memset( p_e_data, 0, sizeof(ZKN_EVENT_APL_CHANGE) );
	p_e_data->p_proc	= ZKN_SYS_GetProcSysMain( zkn_sys );			// プロックシステム
		
	p_e_data->p_event	= ZKN_SYS_GetEventSysMain( zkn_sys );		// イベントシステム

	p_e_data->p_apl	= ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_SOUND );		// 始めるアプリケーションデータ
	
	p_data->work.p_data = p_e_data;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	大きさ比べ移動
 *
 *	@param	heap		ヒープ
 *	@param	p_data		イベントデータ
 *	@param	zkn_sys		図鑑システム
 *	@param	event_key	イベントキー
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_EVENT_MakeChangeBig( int heap, ZKN_EVENT_DATA* p_data, ZKN_SYS_PTR zkn_sys, int event_key )
{
	ZKN_EVENT_APL_DOUBLE_CHANGE* p_e_data;
	
	p_data->key_msk		= event_key;
	p_data->func		= ZKN_EVENT_AplDoubleChange;
	
	// イベントデータ作成
	p_e_data = sys_AllocMemory( heap, sizeof(ZKN_EVENT_APL_DOUBLE_CHANGE) );
	GF_ASSERT( p_e_data );
	memset( p_e_data, 0, sizeof(ZKN_EVENT_APL_DOUBLE_CHANGE) );
	p_e_data->p_proc_m	= ZKN_SYS_GetProcSysMain( zkn_sys );			// プロックシステム
	p_e_data->p_proc_s	= ZKN_SYS_GetProcSysSub( zkn_sys );				// プロックシステム
		
	p_e_data->p_event_m	= ZKN_SYS_GetEventSysMain( zkn_sys );		// イベントシステム
	p_e_data->p_event_s	= ZKN_SYS_GetEventSysSub( zkn_sys );		// イベントシステム

	p_e_data->p_apl_m	= ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_BIG );		// 始めるアプリケーションデータ
	p_e_data->p_apl_s	= ZKN_GetAplDataSub( zkn_sys, ZKN_SYS_APLSUB_BIG );		// 始めるアプリケーションデータ
	
	p_data->work.p_data = p_e_data;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	大きさ比べ移動	
 *
 *	@param	heap		ヒープ
 *	@param	p_data		イベントデータ
 *	@param	zkn_sys		図鑑システム
 *	@param	event_key	イベントキー
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_EVENT_MakeChangeBigMain( int heap, ZKN_EVENT_DATA* p_data, ZKN_SYS_PTR zkn_sys, int event_key )
{
	ZKN_EVENT_APL_CHANGE* p_e_data;
	
	p_data->key_msk		= event_key;
	p_data->func		= ZKN_EVENT_AplChange;
	
	// イベントデータ作成
	p_e_data = sys_AllocMemory( heap, sizeof(ZKN_EVENT_APL_CHANGE) );
	GF_ASSERT( p_e_data );
	memset( p_e_data, 0, sizeof(ZKN_EVENT_APL_CHANGE) );
	p_e_data->p_proc	= ZKN_SYS_GetProcSysMain( zkn_sys );			// プロックシステム
		
	p_e_data->p_event	= ZKN_SYS_GetEventSysMain( zkn_sys );		// イベントシステム

	p_e_data->p_apl	= ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_BIG );		// 始めるアプリケーションデータ
	
	p_data->work.p_data = p_e_data;
}


//----------------------------------------------------------------------------
//
/**
 *
 *	@brief	大きさ比べ移動	
 *
 *	@param	heap		ヒープ
 *	@param	p_data		イベントデータ
 *	@param	zkn_sys		図鑑システム
 *	@param	event_key	イベントキー
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_EVENT_MakeChangeBigWeightMain( int heap, ZKN_EVENT_DATA* p_data, ZKN_SYS_PTR zkn_sys, int event_key )
{
	ZKN_EVENT_APL_CHANGE* p_e_data;
	
	p_data->key_msk		= event_key;
	p_data->func		= ZKN_EVENT_AplChange;
	
	// イベントデータ作成
	p_e_data = sys_AllocMemory( heap, sizeof(ZKN_EVENT_APL_CHANGE) );
	GF_ASSERT( p_e_data );
	memset( p_e_data, 0, sizeof(ZKN_EVENT_APL_CHANGE) );
	p_e_data->p_proc	= ZKN_SYS_GetProcSysMain( zkn_sys );			// プロックシステム
		
	p_e_data->p_event	= ZKN_SYS_GetEventSysMain( zkn_sys );		// イベントシステム

	p_e_data->p_apl	= ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_BIG_WEIGHT );		// 始めるアプリケーションデータ
	
	p_data->work.p_data = p_e_data;
}

//----------------------------------------------------------------------------
/**
 *	@brief	図鑑のみ作成する
 *
 *	@param	heap			ヒープ
 *	@param	p_event_data	イベントデータ
 *	@param	zkn_sys			図鑑システム
 *	@param	event_key		イベントキー
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_EVENT_MakeChangeZukanOnly(  int heap, ZKN_EVENT_DATA* p_data, ZKN_SYS_PTR zkn_sys, int event_key  )
{
	ZKN_EVENT_APL_DOUBLE_CHANGE* p_e_data;
	
	p_data->key_msk		= event_key;
	p_data->func		= ZKN_EVENT_AplDoubleChange;
	
	// イベントデータ作成
	p_e_data = sys_AllocMemory( heap, sizeof(ZKN_EVENT_APL_DOUBLE_CHANGE) );
	GF_ASSERT( p_e_data );
	memset( p_e_data, 0, sizeof(ZKN_EVENT_APL_DOUBLE_CHANGE) );
	p_e_data->p_proc_m	= ZKN_SYS_GetProcSysMain( zkn_sys );			// プロックシステム
	p_e_data->p_proc_s	= ZKN_SYS_GetProcSysSub( zkn_sys );				// プロックシステム
		
	p_e_data->p_event_m	= ZKN_SYS_GetEventSysMain( zkn_sys );		// イベントシステム
	p_e_data->p_event_s	= ZKN_SYS_GetEventSysSub( zkn_sys );		// イベントシステム

	p_e_data->p_apl_m	= ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_ZUKAN );		// 始めるアプリケーションデータ
	p_e_data->p_apl_s	= ZKN_GetAplDataSub( zkn_sys, ZKN_SYS_APLSUB_ZUKAN );		// 始めるアプリケーションデータ
	
	p_data->work.p_data = p_e_data;
}

//----------------------------------------------------------------------------
/**
 *	@brief	図鑑データメイン画面のみ作成する
 *
 *	@param	heap			ヒープ
 *	@param	p_event_data	イベントデータ
 *	@param	zkn_sys			図鑑システム
 *	@param	event_key		イベントキー
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_EVENT_MakeChangeZukanNormalMainOnly(  int heap, ZKN_EVENT_DATA* p_data, ZKN_SYS_PTR zkn_sys, int event_key  )
{
	ZKN_EVENT_APL_CHANGE* p_e_data;
	
	p_data->key_msk		= event_key;
	p_data->func		= ZKN_EVENT_AplChange;
	
	// イベントデータ作成
	p_e_data = sys_AllocMemory( heap, sizeof(ZKN_EVENT_APL_CHANGE) );
	GF_ASSERT( p_e_data );
	memset( p_e_data, 0, sizeof(ZKN_EVENT_APL_CHANGE) );
	p_e_data->p_proc	= ZKN_SYS_GetProcSysMain( zkn_sys );			// プロックシステム
		
	p_e_data->p_event	= ZKN_SYS_GetEventSysMain( zkn_sys );		// イベントシステム

	p_e_data->p_apl	= ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_ZUKAN );		// 始めるアプリケーションデータ
	
	p_data->work.p_data = p_e_data;
}

//----------------------------------------------------------------------------
/**
 *	@brief	図鑑データグラフィックバージョン
 *
 *	@param	heap			ヒープ
 *	@param	p_event_data	イベントデータ
 *	@param	zkn_sys			図鑑システム
 *	@param	event_key		イベントキー
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_EVENT_MakeChangeZukanGraphic(  int heap, ZKN_EVENT_DATA* p_data, ZKN_SYS_PTR zkn_sys, int event_key  )
{
	ZKN_EVENT_APL_DOUBLE_CHANGE* p_e_data;
	
	p_data->key_msk		= event_key;
	p_data->func		= ZKN_EVENT_AplDoubleChange;
	
	// イベントデータ作成
	p_e_data = sys_AllocMemory( heap, sizeof(ZKN_EVENT_APL_DOUBLE_CHANGE) );
	GF_ASSERT( p_e_data );
	memset( p_e_data, 0, sizeof(ZKN_EVENT_APL_DOUBLE_CHANGE) );
	p_e_data->p_proc_m	= ZKN_SYS_GetProcSysMain( zkn_sys );			// プロックシステム
	p_e_data->p_proc_s	= ZKN_SYS_GetProcSysSub( zkn_sys );				// プロックシステム
		
	p_e_data->p_event_m	= ZKN_SYS_GetEventSysMain( zkn_sys );		// イベントシステム
	p_e_data->p_event_s	= ZKN_SYS_GetEventSysSub( zkn_sys );		// イベントシステム

	p_e_data->p_apl_m	= ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_ZUKAN_GRA );		// 始めるアプリケーションデータ
	p_e_data->p_apl_s	= ZKN_GetAplDataSub( zkn_sys, ZKN_SYS_APLSUB_ZUKAN_GRA );		// 始めるアプリケーションデータ
	
	p_data->work.p_data = p_e_data;
}

//----------------------------------------------------------------------------
/**
 *	@brief	図鑑データ言語バージョンメイン画面のみ作成する
 *
 *	@param	heap			ヒープ
 *	@param	p_event_data	イベントデータ
 *	@param	zkn_sys			図鑑システム
 *	@param	event_key		イベントキー
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_EVENT_MakeChangeZukanTextMainOnly(  int heap, ZKN_EVENT_DATA* p_data, ZKN_SYS_PTR zkn_sys, int event_key  )
{
	ZKN_EVENT_APL_CHANGE* p_e_data;
	
	p_data->key_msk		= event_key;
	p_data->func		= ZKN_EVENT_AplChange;
	
	// イベントデータ作成
	p_e_data = sys_AllocMemory( heap, sizeof(ZKN_EVENT_APL_CHANGE) );
	GF_ASSERT( p_e_data );
	memset( p_e_data, 0, sizeof(ZKN_EVENT_APL_CHANGE) );
	p_e_data->p_proc	= ZKN_SYS_GetProcSysMain( zkn_sys );			// プロックシステム
		
	p_e_data->p_event	= ZKN_SYS_GetEventSysMain( zkn_sys );		// イベントシステム

	p_e_data->p_apl	= ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_ZUKAN_TEXT );		// 始めるアプリケーションデータ
	
	p_data->work.p_data = p_e_data;
}


//----------------------------------------------------------------------------
/**
 *	@brief	図鑑サブコモンのみ変更
 *
 *	@param	heap			ヒープ
 *	@param	p_event_data	イベントデータ格納先
 *	@param	zkn_sys			図鑑システム
 *	@param	event_key		イベントキー
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_EVENT_MakeChangeZukanCommonSubOnly( int heap, ZKN_EVENT_DATA* p_event_data, ZKN_SYS_PTR zkn_sys, int event_key )
{
	ZKN_EVENT_APL_CHANGE* p_e_data;
	
	p_event_data->key_msk		= event_key;
	p_event_data->func		= ZKN_EVENT_AplChange;
	
	// イベントデータ作成
	p_e_data = sys_AllocMemory( heap, sizeof(ZKN_EVENT_APL_CHANGE) );
	GF_ASSERT( p_e_data );
	memset( p_e_data, 0, sizeof(ZKN_EVENT_APL_CHANGE) );
	p_e_data->p_proc	= ZKN_SYS_GetProcSysSubCommon( zkn_sys );			// プロックシステム
		
	p_e_data->p_event	= ZKN_SYS_GetEventSysSubCommon( zkn_sys );		// イベントシステム

	p_e_data->p_apl	= ZKN_GetAplDataSub( zkn_sys, ZKN_SYS_APLSUB_ZUKAN_COMMON );		// 始めるアプリケーションデータ
	
	p_event_data->work.p_data = p_e_data;
}

#ifdef PM_DEBUG
// 高さ比べDEBUGアプリへ
void ZKN_EVENT_BigHeightDebugApl( ZKN_EVENT_DATA* p_event, ZKN_SYS_PTR zkn_sys, int heap, int event_key )
{
	ZKN_EVENT_APL_AllCHANGE* p_e_data;
	
	p_event->key_msk	= event_key;
	p_event->func		= ZKN_EVENT_AplAllChange;
	
	// イベントデータ作成
	p_e_data = sys_AllocMemory( heap, sizeof(ZKN_EVENT_APL_AllCHANGE) );
	GF_ASSERT( p_e_data );
	memset( p_e_data, 0, sizeof(ZKN_EVENT_APL_AllCHANGE) );
	p_e_data->p_proc_m	= ZKN_SYS_GetProcSysMain( zkn_sys );			// プロックシステム
	p_e_data->p_proc_s	= ZKN_SYS_GetProcSysSub( zkn_sys );				// プロックシステム
	p_e_data->p_proc_mc	= ZKN_SYS_GetProcSysMainCommon( zkn_sys );		// プロックシステム
	p_e_data->p_proc_sc	= ZKN_SYS_GetProcSysSubCommon( zkn_sys );		// プロックシステム
		
	p_e_data->p_event_m	= ZKN_SYS_GetEventSysMain( zkn_sys );		// イベントシステム
	p_e_data->p_event_s	= ZKN_SYS_GetEventSysSub( zkn_sys );		// イベントシステム
	p_e_data->p_event_mc= ZKN_SYS_GetEventSysMainCommon( zkn_sys );		// イベントシステム
	p_e_data->p_event_sc= ZKN_SYS_GetEventSysSubCommon( zkn_sys );		// イベントシステム

	p_e_data->p_apl_m	= ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_BIG );		// 始めるアプリケーションデータ
	p_e_data->p_apl_s	= ZKN_GetAplDataSub( zkn_sys, ZKN_SYS_APLSUB_HEIGHT_DEBUG );		// 始めるアプリケーションデータ
	p_e_data->p_apl_mc	= NULL;		// 始めるアプリケーションデータ
	p_e_data->p_apl_sc	= NULL;		// 始めるアプリケーションデータ
	
	p_event->work.p_data = p_e_data;
}

// 高さ比べDEBUGアプリから高さ比べに復帰
void ZKN_EVENT_BigHeightDebugAplReturn( ZKN_EVENT_DATA* p_event, ZKN_SYS_PTR zkn_sys, int heap, int event_key )
{
	ZKN_EVENT_APL_AllCHANGE* p_e_data;
	
	p_event->key_msk	= event_key;
	p_event->func		= ZKN_EVENT_AplAllChange;
	
	// イベントデータ作成
	p_e_data = sys_AllocMemory( heap, sizeof(ZKN_EVENT_APL_AllCHANGE) );
	GF_ASSERT( p_e_data );
	memset( p_e_data, 0, sizeof(ZKN_EVENT_APL_AllCHANGE) );
	p_e_data->p_proc_m	= ZKN_SYS_GetProcSysMain( zkn_sys );			// プロックシステム
	p_e_data->p_proc_s	= ZKN_SYS_GetProcSysSub( zkn_sys );				// プロックシステム
	p_e_data->p_proc_mc	= ZKN_SYS_GetProcSysMainCommon( zkn_sys );		// プロックシステム
	p_e_data->p_proc_sc	= ZKN_SYS_GetProcSysSubCommon( zkn_sys );		// プロックシステム
		
	p_e_data->p_event_m	= ZKN_SYS_GetEventSysMain( zkn_sys );		// イベントシステム
	p_e_data->p_event_s	= ZKN_SYS_GetEventSysSub( zkn_sys );		// イベントシステム
	p_e_data->p_event_mc= ZKN_SYS_GetEventSysMainCommon( zkn_sys );		// イベントシステム
	p_e_data->p_event_sc= ZKN_SYS_GetEventSysSubCommon( zkn_sys );		// イベントシステム

	p_e_data->p_apl_m	= ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_BIG );		// 始めるアプリケーションデータ
	p_e_data->p_apl_s	= ZKN_GetAplDataSub( zkn_sys, ZKN_SYS_APLSUB_BIG );		// 始めるアプリケーションデータ
	p_e_data->p_apl_mc	= ZKN_GetAplDataMain( zkn_sys, ZKN_SYS_APLMAIN_ZUKAN_COMMON );		// 始めるアプリケーションデータ
	p_e_data->p_apl_sc	= ZKN_GetAplDataSub( zkn_sys, ZKN_SYS_APLSUB_ZUKAN_COMMON );		// 始めるアプリケーションデータ
	
	p_event->work.p_data = p_e_data;
}
#endif

