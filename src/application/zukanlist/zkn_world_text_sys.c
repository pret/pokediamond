//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_world_text_sys.c
 *	@brief		図鑑の外国語テキストアクセス
 *	@author		tomoya takahashi 
 *	@data		2006.02.28
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include <string.h>
#include "include/system/fontproc.h"
#include "include/system/msgdata_util.h"
#include "include/msgdata/msg.naix"

#include "include/application/zukanlist/zkn_world_text_data.h"
#include "src/application/zukanlist/zkn_worldtext.h"

#include "include/application/zukanlist/zkn_version.h"

#define	__ZKN_WORLD_TEXT_SYS_H_GLOBAL
#include "include/application/zukanlist/zkn_world_text_sys.h"

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
#define ZKN_WT_ALLOC_STR_NUM		( 256 )		// 確保する文字列数


//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
/**
 *					グローバルデータ
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	ポケモン外国語テキスト用国コードと
//	実際にGMMファイルに入っているデータの外国語項目数
//	対応データ
//	IDXは外国語テキスト用国コード
//
//	zukan_data.xlsには下の数字の順にﾃﾞｰﾀを格納しておく
//=====================================
static const u8 ZKN_WORLD_TEXT_GmmIdx[ ZKN_WORLD_TEXT_NUM ] = {
/* 日本 */
#if( PM_LANG == LANG_JAPAN )
	ZKN_WORLD_TEXT_NUM,	// 自国
	0,		// アメリカ
	1,		// フランス
	2,		// ドイツ		
	3,		// イタリア	
	4		// スペイン
#endif
/* アメリカ */
#if( PM_LANG == LANG_ENGLISH )
	0,
	ZKN_WORLD_TEXT_NUM,
	1,
	2,
	3,
	4
#endif
/* フランス */
#if( PM_LANG == LANG_FRANCE )
	0,
	1,
	ZKN_WORLD_TEXT_NUM,
	2,
	3,
	4
#endif
/* イタリア */
#if( PM_LANG == LANG_ITALY )
	0,
	1,
	2,
	ZKN_WORLD_TEXT_NUM,
	3,
	4
#endif
/* ドイツ */
#if( PM_LANG == LANG_GERMANY )
	0,
	1,
	2,
	3,
	ZKN_WORLD_TEXT_NUM,
	4
#endif
/* スペイン */
#if( PM_LANG == LANG_SPAIN )
	0,
	1,
	2,
	3,
	4,
	ZKN_WORLD_TEXT_NUM
#endif
};


//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
static inline int ZknWt_GetGmmIdx( int zkn_text_code );
static inline BOOL ZknWt_CheckWorldData( int textverpokenum, int gmm_idx );
static STRBUF* ZknWt_GetSTRData( int file_idx, int data_idx, int heap );
static void ZknWt_GetCountryPokeData( int monsno, int country, int* p_country_poke_num, int* p_country_text_code, int* p_country_gmm_idx );

//----------------------------------------------------------------------------
/**
 *	@brief	文字列バッファを破棄する
 *
 *	@param	buf		バッファ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_WT_DeleteStrBuf( STRBUF* buf )
{
	STRBUF_Delete( buf );
}

//----------------------------------------------------------------------------
/**
 *	@brief	国コードから対応する外国語GMMインデックスを取得
 *
 *	@param	country	国コード
 *
 *	@return	外国語番号
 */
//-----------------------------------------------------------------------------
int ZKN_WT_LANG_Code_WORLD_TEXT_GMM_Idx( int country )
{
	int country_text_code;
	int country_gmm_idx;
	
	// 外国語テキスト用国コードに変換
	country_text_code = ZKN_WT_GetLANG_Code_ZKN_WORLD_TEXT_Code( country );
	GF_ASSERT( country_text_code < ZKN_WORLD_TEXT_NUM );	// 無いということはデータも無い
	// 外国語テキスト用国コードからGMMデータ外国語項目数取得
	country_gmm_idx = ZknWt_GetGmmIdx( country_text_code );

	return country_gmm_idx;
}

//----------------------------------------------------------------------------
/**
 *	@brief	外国語番号から対応する国コードを取得する
 *
 *	@param	county	外国語番号	(gmmファイルに並んでいる番号)
 *
 *	@return	国コード		// 引っかからないときはホームタウンを返す
 */
//-----------------------------------------------------------------------------
int ZKN_WT_WORLD_TEXT_GMM_Idx_LANG_Code( int country )
{
	int i;

	// countryのナンバーのGmmIdxテーブルインデックスを求める
	// (これが外国語用国コード)
	for( i=0; i<ZKN_WORLD_TEXT_NUM; i++ ){
		if( ZKN_WORLD_TEXT_GmmIdx[i] == country ){
			break;
		}
	}
	if( i== ZKN_WORLD_TEXT_NUM ){
		return PM_LANG;
	}

	// この外国用国コードのゲーム内国コードを取得
	return ZKN_WT_GetZKN_WORLD_TEXT_Code_LANG_Code( i );
}


//----------------------------------------------------------------------------
/**
 *	@brief	国のポケモン名を返す
 *
 *	@param	monsno		モンスターナンバー
 *	@param	country		ゲーム内国コード
 *	@param	heap		ヒープ
 *
 *	@return	文字列データ
 */
//-----------------------------------------------------------------------------
STRBUF* ZKN_WT_GetPokeName( int monsno, int country, int heap )
{
	int country_poke_num;
	int country_text_code;
	int country_gmm_idx;
	int gmm_file_idx;

	// モンスターナンバーとゲーム内国コードから
	// 外国語テキストデータ項目数
	// 外国語テキストデータ用国コード
	// 外国語テキストデータGMM外国項目数取得
	ZknWt_GetCountryPokeData( monsno, country, &country_poke_num, &country_text_code, &country_gmm_idx );

	// 自国チェック
	if( country_gmm_idx == ZKN_WORLD_TEXT_NUM ){
		// 自国
		// GMMの中のデータidx＝monsno
		return MSGDAT_UTIL_GetMonsName( monsno, heap );
	}else{
		// 外国
		// GMMの中のデータインデックスを求める
		// 外国ポケモン名GMMのデータ構成
		// 外国語１のAポケモン名, 外国語２のAポケモン名,外国語３のAポケモン名,外国語４のAポケモン名,外国語５のAポケモン名
		// 外国語１のBポケモン名, 外国語２のBポケモン名,外国語３のBポケモン名,外国語４のBポケモン名,外国語５のBポケモン名
		country_gmm_idx += country_poke_num * ZKN_WORLD_TEXT_OUTWORLD_NUM;
		gmm_file_idx = NARC_msg_zkn_worldname_dat;
	}

	// gmm_file_idxとcountry_gmm_idxからSTRBUFを取得する
	return ZknWt_GetSTRData( gmm_file_idx, country_gmm_idx, heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	国のポケモンタイプを返す
 *
 *	@param	monsno		モンスターナンバー
 *	@param	country		ゲーム内国コード
 *	@param	heap		ヒープ
 *
 *	@return	文字列データ
 */
//-----------------------------------------------------------------------------
STRBUF* ZKN_WT_GetPokeType( int monsno, int country, int heap )
{
	int country_poke_num;
	int country_text_code;
	int country_gmm_idx;
	int gmm_file_idx;

	// モンスターナンバーとゲーム内国コードから
	// 外国語テキストデータ項目数
	// 外国語テキストデータ用国コード
	// 外国語テキストデータGMM外国項目数取得
	ZknWt_GetCountryPokeData( monsno, country, &country_poke_num, &country_text_code, &country_gmm_idx );

	// 自国チェック
	if( country_gmm_idx == ZKN_WORLD_TEXT_NUM ){
		// 自国
		// GMMの中のデータidx＝monsno
		country_gmm_idx = monsno;
		gmm_file_idx = NARC_msg_zkn_type_dat;
	}else{
		// 外国
		// GMMの中のデータインデックスを求める
		// 外国ポケモン名GMMのデータ構成
		// 外国語１のAポケモン, 外国語２のAポケモン,外国語３のAポケモン,外国語４のAポケモン,外国語５のAポケモン
		// 外国語１のBポケモン, 外国語２のBポケモン,外国語３のBポケモン,外国語４のBポケモン,外国語５のBポケモン
		country_gmm_idx += country_poke_num * ZKN_WORLD_TEXT_OUTWORLD_NUM;
		gmm_file_idx = NARC_msg_zkn_worldtype_dat;
	}

	// gmm_file_idxとcountry_gmm_idxからSTRBUFを取得する
	return ZknWt_GetSTRData( gmm_file_idx, country_gmm_idx, heap );
}

//----------------------------------------------------------------------------
/**
 *	@brief	国のテキストデータを返す
 *
 *	@param	monsno		モンスターナンバー
 *	@param	country		ゲーム内国コード
 *	@param	page		ページ
 *	@param	heap		ヒープ
 *	
 *	@return	文字列データ
 */
//-----------------------------------------------------------------------------
STRBUF* ZKN_WT_GetText( int monsno, int country, int page, int heap )
{
	int country_poke_num;
	int country_text_code;
	int country_gmm_idx;
	int gmm_file_idx;

	// モンスターナンバーとゲーム内国コードから
	// 外国語テキストデータ項目数
	// 外国語テキストデータ用国コード
	// 外国語テキストデータGMM外国項目数取得
	ZknWt_GetCountryPokeData( monsno, country, &country_poke_num, &country_text_code, &country_gmm_idx );

	// 自国チェック
	if( country_gmm_idx == ZKN_WORLD_TEXT_NUM ){

		// ページ数チェック
		GF_ASSERT( page < ZKN_WT_HOME_TEXT_PAGE_NUM );
		// 自国
		// GMMの中のデータidx＝monsno
		country_gmm_idx = (monsno * ZKN_WT_HOME_TEXT_PAGE_NUM) + page;
		gmm_file_idx = ZKN_TEXT_DAT;
	}else{

		// ページ数チェック
		GF_ASSERT( page < ZKN_WT_WORLD_TEXT_PAGE_NUM );
		// 外国
		// GMMの中のデータインデックスを求める
		// 外国ポケモン名GMMのデータ構成
		// 外国語１のAポケモン1ページ,外国語２のAポケモン1ページ,外国語３のAポケモン1ページ,外国語４のAポケモン1ページ,外国語５のAポケモン1ページ,
		// 外国語１のBポケモン1ページ,外国語２のBポケモン1ページ,外国語３のBポケモン1ページ,外国語４のBポケモン1ページ,外国語５のBポケモン1ページ,
		country_gmm_idx = (country_gmm_idx * ZKN_WT_WORLD_TEXT_PAGE_NUM) + page + (country_poke_num * (ZKN_WORLD_TEXT_OUTWORLD_NUM * ZKN_WT_WORLD_TEXT_PAGE_NUM));
		gmm_file_idx = NARC_msg_zkn_comment_02_dat;
	}

	// gmm_file_idxとcountry_gmm_idxからSTRBUFを取得する
	return ZknWt_GetSTRData( gmm_file_idx, country_gmm_idx, heap );
}


//-----------------------------------------------------------------------------
/**
 *			プライベート関数
 */
//-----------------------------------------------------------------------------

//----------------------------------------------------------------------------
/**
 *	@brief	関数での戻り値[外国語GMM内のデータ項目][GMMデータ外国語項目数]からそのデータがあるのかチェックする
 *
 *	@param	textverpokenum
 *	@param	gmm_idx 
 *
 *	@retval	TRUE	データがある
 *	@retval	FALSE	そのポケモンのその国のデータはない
 */
//-----------------------------------------------------------------------------
static inline BOOL ZknWt_CheckWorldData( int textverpokenum, int gmm_idx )
{
	// 自国のデータを求めていないのにそのポケモンの外国語データが無いとき
	// はデータがないということになる
	if( (textverpokenum == ZKN_WORLD_TEXT_POKE_NUM) && (gmm_idx != ZKN_WORLD_TEXT_NUM) ){
		return FALSE;
	}

	return TRUE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ファイルインデックスから文字列データを取得する
 *
 *	@param	file_idx
 *	@param	data_idx
 *	@param	heap 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static STRBUF* ZknWt_GetSTRData( int file_idx, int data_idx, int heap )
{
	MSGDATA_MANAGER* man = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, file_idx, heap );
	if( man )
	{
		STRBUF* buf = STRBUF_Create(ZKN_WT_ALLOC_STR_NUM, heap );
		if( buf )
		{
			MSGMAN_GetString(man, data_idx, buf);
		}
		MSGMAN_Delete(man);
		return buf;
	}
	return NULL;
}

//----------------------------------------------------------------------------
/**
 *	@brief	モンスターナンバーとゲーム内国コードから
 *			外国語テキストデータ項目数
 *			外国語テキストデータ用国コード
 *			外国語テキストデータGMM外国項目数
 *			取得
 *
 *	@param	monsno				モンスターナンバー
 *	@param	country				ゲーム内国コード
 *	@param	p_country_poke_num	外国語テキストデータ項目数
 *	@param	p_country_text_code	外国語テキストデータ用国コード
 *	@param	p_country_gmm_idx	外国語テキストデータGMM外国項目数
 */
//-----------------------------------------------------------------------------
static void ZknWt_GetCountryPokeData( int monsno, int country, int* p_country_poke_num, int* p_country_text_code, int* p_country_gmm_idx )
{
	// 外国語テキスト用国コードに変換
	*p_country_text_code = ZKN_WT_GetLANG_Code_ZKN_WORLD_TEXT_Code( country );
	GF_ASSERT( *p_country_text_code < ZKN_WORLD_TEXT_NUM );	// 無いということはデータも無い
	// モンスターナンバーから外国語GMM内のデータ項目数を求める
	*p_country_poke_num = ZKN_WT_GetMonsNo_TEXTVERPokeNum( monsno );

	// 外国語テキスト用国コードからGMMデータ外国語項目数取得
	*p_country_gmm_idx = ZknWt_GetGmmIdx( *p_country_text_code );

	// データがあるかチェック
	GF_ASSERT( ZknWt_CheckWorldData( *p_country_poke_num, *p_country_gmm_idx ) );
}

//----------------------------------------------------------------------------
/**
 *	@brief	図鑑外国語テキスト用国コードから外国語テキストGMMデータの外国語項目数を取得
 *
 *	@param	zkn_text_code	図鑑外国語テキスト用国コード
 *
 *	@retval	外国語テキストGMMデータ外国語項目数
 *	@retval ZKN_WORLD_TEXT_NUMの時は自国GMMにデータがある
 */
//-----------------------------------------------------------------------------
static inline int ZknWt_GetGmmIdx( int zkn_text_code )
{
	GF_ASSERT( zkn_text_code < ZKN_WORLD_TEXT_NUM );
	
	return ZKN_WORLD_TEXT_GmmIdx[ zkn_text_code ];
}

