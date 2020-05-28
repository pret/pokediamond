//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imageclip_data.c
 *	@brief		イメージクリップセーブデータ
 *	@author		tomoya takahashi
 *	@data		2006.02.27
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]


#include "include/savedata/savedata_def.h"	//SAVEDATA参照のため
#include "include/savedata/savedata.h"
#include "include/gflib/system.h"
#include "include/gflib/assert.h"
#include <string.h>

#define	__IMAGECLIP_DATA_H_GLOBAL
#include "include/savedata/imageclip_data.h"


#include "include/gflib/strbuf_family.h"

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
#define IMC_SAVEDATA_DATAINIT_FLAG	( 0x1234 )		// 初期化データ格納時のフラグ
#define IMC_SAVEDATA_DATASET_FLAG	( 0x2345 )		// セーブデータ格納時のフラグ

enum{
	IMC_ACCE_9_GET_NUM = 9,
	IMC_ACCE_1_GET_NUM = 1,
	
	IMC_ACCE_9_ARRY_IN = 8,		// 9個用配列u32に入るデータの数
	IMC_ACCE_1_ARRY_IN = 32,	// 1個用配列u32に入るデータの数
	IMC_BG_ARRY_IN	   = 4,		// BG用配列u32に入るデータの数
	IMC_ACCE_9_ARRY_BIT = 4,	// 9個用配列に1データに使うビット数
	IMC_ACCE_1_ARRY_BIT = 1,	// 1個用配列に1データに使うビット数
	IMC_BG_ARRY_BIT		= 8,	// BG用配列に1データに使うビット数
	
	IMC_ACCE_9_ARRY_NUM	= 8,	// 9個もてるアクセサリのフラグ配列
	IMC_ACCE_1_ARRY_NUM = 2,	// 1個もてるアクセサリのフラグ配列
	IMC_BG_ARRY_NUM = 6,		// BGのフラグ配列
};

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------

//-------------------------------------
//	ポケモンデータ
//=====================================
typedef struct _IMC_SAVEDATA_POKEMON{
	u32 personal_rnd;				///<ポケモンの個性乱数
	u32 idno;						///<IDNo	レアポケモン用
	u16	monsno;						///<モンスターナンバー
	u16 nickname[ IMC_SAVEDATA_NICKNAME_STR_NUM ];	///<ニックネーム
	u16 oyaname[ IMC_SAVEDATA_OYANAME_STR_NUM ];	///<ニックネーム
	s8 poke_pri;					///<ポケモン優先順位
	u8 poke_x;						///<ポケモンｘ座標
	u8 poke_y;						///<ポケモンｙ座標
	u8 form_id;					///<形状アトリビュート
	u8 oya_sex;						///<親性別
} ;

//-------------------------------------
//	アクセサリデータ構造体
//=====================================
typedef struct _IMC_SAVEDATA_ACCESSORIE{
	u8 accessory_no;	///<アクセサリナンバー
	u8 accessory_x;		///<アクセサリｘ座標
	u8 accessory_y;		///<アクセサリｙ座標
	s8 accessory_pri;	///<アクセサリ表示優先
} ;



//-------------------------------------
//	テレビ局用セーブデータワーク
//=====================================
typedef struct _IMC_TELEVISION_SAVEDATA{
	u32 init_flag;					///<初期化ﾃﾞｰﾀかのフラグ
	IMC_SAVEDATA_POKEMON	pokemon;///<ポケモンデータ
	u32 accessory_set_msk;			///<格納アクセサリーマスク
	PMS_DATA title;					///<クリップタイトル
	IMC_SAVEDATA_ACCESSORIE acce[ IMC_SAVEDATA_TELEVISION_ACCE_NUM ];	///<アクセサリ
	u8 bg_id;								///<bgナンバー	
	u8 country;	// 国コード
} ;

//-------------------------------------
//	コンテスト用セーブデータワーク
//=====================================
typedef struct _IMC_CONTEST_SAVEDATA{
	u32 init_flag;					///<初期化ﾃﾞｰﾀかのフラグ
	u32 rank_code;					///<コンテストランクコード
	IMC_SAVEDATA_POKEMON	pokemon;///<ポケモンデータ
	u32 accessory_set_msk;			///<格納アクセサリーマスク
	IMC_SAVEDATA_ACCESSORIE acce[ IMC_SAVEDATA_CONTEST_ACCE_NUM ];	///<アクセサリ
	u8 bg_id;						///<bgナンバー	
} ;

//-------------------------------------
//	アイテム保持セーブデータワーク
//=====================================
typedef struct _IMC_ITEM_SAVEDATA{
	u32 acce_9[ IMC_ACCE_9_ARRY_NUM ];		// 9個もてるアクセサリ　取得フラグ
	u32 acce_1[ IMC_ACCE_1_ARRY_NUM ];		// 1個もてるアクセサリ　取得フラグ
	u32 bg[ IMC_BG_ARRY_NUM ];				// BG取得順番データ
} ;


//-------------------------------------
//	セーブデータ
//=====================================
struct _IMC_SAVEDATA{
	IMC_TELEVISION_SAVEDATA imc_television_savedata[ IMC_SAVEDATA_TELEVISION_SAVENUM ];	///<saveデータ
	IMC_CONTEST_SAVEDATA	imc_contest_savedata[ IMC_SAVEDATA_CONTEST_SAVENUM ];		///<saveデータ

	IMC_ITEM_SAVEDATA	imc_item_savedata;	///<アイテムセーブデータ
};


//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	イメージクリップワークが壊れていないかチェック
 *
 *	@param	init_flag		初期化データフラグ
 *
 *	@retval	TRUE	正しい	
 *	@retval FALSE	壊れている
 */
//-----------------------------------------------------------------------------
static inline BOOL correct_savedata( u32 init_flag )
{
	if( (init_flag == IMC_SAVEDATA_DATAINIT_FLAG) ||
		(init_flag == IMC_SAVEDATA_DATASET_FLAG) ){

		return TRUE;
	}
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	テレビ局用セーブデータの正当性チェック
 *	
 *	@param	wk	セーブデータ
 *
 *	@retval	TRUE	正しい	
 *	@retval FALSE	壊れている
 */
//-----------------------------------------------------------------------------
static inline BOOL correct_television_savedata( const IMC_TELEVISION_SAVEDATA* wk )
{
	return correct_savedata( wk->init_flag );
}

//----------------------------------------------------------------------------
/**
 *	@brief	コンテスト用セーブデータの正当性チェック
 *	
 *	@param	wk	セーブデータ
 *
 *	@retval	TRUE	正しい	
 *	@retval FALSE	壊れている
 */
//-----------------------------------------------------------------------------
static inline BOOL correct_contest_savedata( const IMC_CONTEST_SAVEDATA* wk )
{
	return correct_savedata( wk->init_flag );
}

//----------------------------------------------------------------------------
/**
 *	@brief	テレビ局用セーブデータの初期化
 *	
 *	@param	wk	セーブデータ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static inline void clean_television_savedata( IMC_TELEVISION_SAVEDATA* wk )
{
	memset( wk, 0, sizeof(IMC_TELEVISION_SAVEDATA) );
	wk->init_flag = IMC_SAVEDATA_DATAINIT_FLAG;
}

//----------------------------------------------------------------------------
/**
 *	@brief	コンテスト用セーブデータの初期化
 *	
 *	@param	wk	セーブデータ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static inline void clean_contest_savedata( IMC_CONTEST_SAVEDATA* wk )
{
	memset( wk, 0, sizeof(IMC_CONTEST_SAVEDATA) );
	wk->init_flag = IMC_SAVEDATA_DATAINIT_FLAG;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンワークからデータを取得
 *
 *	@param	ip		ポケモンパラメータ
 *	@param	x		ｘ座標取得先
 *	@param	y		ｙ座標取得先
 *	@param	pri		表示優先順位
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static inline void get_poke_mat( IMC_POKE* ip, u8* x, u8* y, s8* pri )
{
	int gx, gy;
	int gpri;

	IMC_POKE_MatrixGet( ip, &gx, &gy );
	gpri = IMC_POKE_DrawPriorityGet( ip );
	GF_ASSERT( gx < 256 );
	GF_ASSERT( gy < 256 );
	GF_ASSERT( gpri > -128 );

	*x = gx;
	*y = gy;
	*pri = gpri;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンデータの格納
 *
 *	@param	p_pokemon	イメージクリップポケモンセーブワーク
 *	@param	pp			ポケモンパラメータ
 *	@param	x			ｘ座標
 *	@param	y			ｙ座標
 *	@param	pri			優先順位
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ImcSaveData_SetPokeData_Local_Core( IMC_SAVEDATA_POKEMON* p_pokemon, POKEMON_PARAM* pp, u8 x, u8 y, s8 pri )
{
	p_pokemon->monsno   = PokeParaGet(pp, ID_PARA_monsno, NULL);
	PokeParaGet(pp, ID_PARA_nickname, p_pokemon->nickname);
//	PokeParaGet(pp, ID_PARA_oyaname, p_pokemon->oyaname);
	p_pokemon->personal_rnd = PokeParaGet(pp, ID_PARA_personal_rnd, NULL );
	p_pokemon->idno = PokeParaGet(pp, ID_PARA_id_no, NULL);
	p_pokemon->form_id = PokeParaGet(pp, ID_PARA_form_no, NULL);
//	p_pokemon->oya_sex = PokeParaGet(pp, ID_PARA_oyasex, NULL);
	p_pokemon->poke_x = x;
	p_pokemon->poke_y = y;
	p_pokemon->poke_pri = pri;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンデータの格納
 *
 *	@param	p_pokemon	イメージクリップポケモンセーブワーク
 *	@param	pp			ポケモンパラメータ
 *	@param	ip			イメージクリップポケモンデータ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ImcSaveData_SetPokeData_Local( IMC_SAVEDATA_POKEMON* p_pokemon, POKEMON_PARAM* pp, IMC_POKE* ip )
{
	u8 x, y;
	s8 pri;
	get_poke_mat( ip, &x, &y, &pri );
	ImcSaveData_SetPokeData_Local_Core( p_pokemon, pp, x, y, pri );
}

//----------------------------------------------------------------------------
/**
 *	@brief	トレーナーデータ設定
 *
 *	@param	p_pokemon		ポケモンデータ
 *	@param	pbuff			トレーナー名バッファ
 *	@param	sex				性別
 */
//-----------------------------------------------------------------------------
static void ImcSaveData_SetTrData_Local( IMC_SAVEDATA_POKEMON* p_pokemon, const STRBUF* pbuff, int sex )
{
	STRBUF_GetStringCode( pbuff, p_pokemon->oyaname, IMC_SAVEDATA_OYANAME_STR_NUM );
	p_pokemon->oya_sex = sex;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンパラメータの作成
 *	@param	p_pokemon		イメージクリップポケモンセーブデータ
 *	@param	pp				ポケモンパラメータ格納先
 */
//-----------------------------------------------------------------------------
static inline void imcsacedata_GetPokePara_Local( const IMC_SAVEDATA_POKEMON* p_pokemon, POKEMON_PARAM* pp )
{
	PokeParaSet( pp, p_pokemon->monsno, 0, 0, RND_SET, p_pokemon->personal_rnd, ID_SET, p_pokemon->idno );
	PokeParaPut( pp, ID_PARA_nickname, p_pokemon->nickname );
//	PokeParaPut( pp, ID_PARA_oyaname, p_pokemon->oyaname );
	PokeParaPut( pp, ID_PARA_form_no, &p_pokemon->form_id );
//	PokeParaPut( pp, ID_PARA_oyasex, &p_pokemon->oya_sex );
}

//----------------------------------------------------------------------------
/**
 *	@brief	アクセサリデータ格納
 *
 *	@param	p_acce		アクセサリワーク
 *	@param	acce_no		アクセサリナンバー
 *	@param	x			ｘ座標
 *	@param	y			ｙ座標
 *	@param	pri			優先順位
 */
//-----------------------------------------------------------------------------
static void imcsavedata_SetAcce_Local( IMC_SAVEDATA_ACCESSORIE* p_acce, u8 acce_no, u8 x, u8 y, u8 pri )
{
	p_acce->accessory_no	= acce_no;
	p_acce->accessory_x		= x;
	p_acce->accessory_y		= y;
	p_acce->accessory_pri	= pri;
}



//----------------------------------------------------------------------------
/**
 *	@brief	アクセサリ保持数設定
 *
 *	@param	p_arry		アクセサリ配列
 *	@param	set_data	設定数
 *	@param	idx			インデックス
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void imcsavedata_Acce9Set( u32* p_arry, u8 set_data, u8 idx )
{
	u8 arry_idx;
	u8 bit_idx;

	// idxが大きすぎ
	GF_ASSERT( idx < IMC_ACCE_GET_9_NUM );
	arry_idx = idx / IMC_ACCE_9_ARRY_IN;
	
	bit_idx = idx % IMC_ACCE_9_ARRY_IN;
	bit_idx *= IMC_ACCE_9_ARRY_BIT;

	// 領域クリーン
	p_arry[ arry_idx ] &= ~(0xf << bit_idx);
	// 設定
	p_arry[ arry_idx ] |= (set_data << bit_idx);
}

//----------------------------------------------------------------------------
/**
 *	@brief	アクセサリ保持数取得
 *
 *	@param	p_arry		アクセサリ配列
 *	@param	idx			インデックス	
 *
 *	@return	保持数
 */
//-----------------------------------------------------------------------------
static u8 imcsavedata_Acce9Get( const u32* p_arry, u8 idx )
{
	u8 now;
	u8 arry_idx;
	u8 bit_idx;
	
	// idxが大きすぎ
	GF_ASSERT( idx < IMC_ACCE_GET_9_NUM );

	arry_idx = idx / IMC_ACCE_9_ARRY_IN;
	bit_idx = idx % IMC_ACCE_9_ARRY_IN;
	bit_idx *= IMC_ACCE_9_ARRY_BIT;
	now = (p_arry[ arry_idx ] >> bit_idx) & 0xf;
	
	return now;
}

//----------------------------------------------------------------------------
/**
 *	@brief	1bitフラグ配列のフラグ設定
 *
 *	@param	p_arry		配列ポインタ
 *	@param	set_data	設定数　0 or 1
 *	@param	idx			インデックス 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void imcsavedata_1bitArry_set( u32* p_arry, u8 set_data, u8 idx )
{
	u8 arry_idx;
	u8 bit_idx;

	// 値が大きすぎ
	GF_ASSERT( set_data < 2 );

	arry_idx = idx / IMC_ACCE_1_ARRY_IN;
	bit_idx = idx % IMC_ACCE_1_ARRY_IN;
	bit_idx *= IMC_ACCE_1_ARRY_BIT;

	// 領域クリーン
	p_arry[ arry_idx ] &= ~(0x1 << bit_idx);
	// 設定
	p_arry[ arry_idx ] |= (set_data << bit_idx);
}

//----------------------------------------------------------------------------
/**
 *	@brief	1ビットフラグ配列の値取得関数
 *
 *	@param	p_arry	1ビット配列
 *	@param	idx		インデックス
 *
 *	@return	値
 */
//-----------------------------------------------------------------------------
static u8 imcsavedata_1bitArry_get( const u32* p_arry, u8 idx )
{
	u8 arry_idx;
	u8 bit_idx;

	arry_idx = idx / IMC_ACCE_1_ARRY_IN;
	bit_idx = idx % IMC_ACCE_1_ARRY_IN;
	bit_idx *= IMC_ACCE_1_ARRY_BIT;

	return (p_arry[ arry_idx ] >> bit_idx) & 0x1;
}

//----------------------------------------------------------------------------
/**
 *	@brief	BG配列のフラグ設定
 *
 *	@param	p_arry		配列ポインタ
 *	@param	set_data	設定数
 *	@param	idx			インデックス 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void imcsavedata_BGArry_set( u32* p_arry, u8 set_data, u8 idx )
{
	u8 arry_idx;
	u8 bit_idx;

	// 値が大きすぎ
	GF_ASSERT( set_data <= IMC_BG_RIGHT_MAX );

	arry_idx = idx / IMC_BG_ARRY_IN;
	bit_idx = idx % IMC_BG_ARRY_IN;
	bit_idx *= IMC_BG_ARRY_BIT;

	// 領域クリーン
	p_arry[ arry_idx ] &= ~(0xff << bit_idx);
	// 設定
	p_arry[ arry_idx ] |= (set_data << bit_idx);
}

//----------------------------------------------------------------------------
/**
 *	@brief	BGフラグ配列の値取得関数
 *
 *	@param	p_arry	BG配列
 *	@param	idx		インデックス
 *
 *	@return	値
 */
//-----------------------------------------------------------------------------
static u8 imcsavedata_BGArry_get( const u32* p_arry, u8 idx )
{
	u8 arry_idx;
	u8 bit_idx;

	arry_idx = idx / IMC_BG_ARRY_IN;
	bit_idx = idx % IMC_BG_ARRY_IN;
	bit_idx *= IMC_BG_ARRY_BIT;

	return (p_arry[ arry_idx ] >> bit_idx) & 0xff;
}

//----------------------------------------------------------------------------
/**
 *	@brief	保持しているデータ数を取得
 *
 *	@param	p_arry		BG配列
 *
 *	@return	保持数
 */
//-----------------------------------------------------------------------------
static u8 imcsavedata_BGArry_FlagOnDataNumGet( const u32* p_arry )
{
	int i;
	int count;

	count = 0;
	for( i=0; i<IMC_BG_RIGHT_MAX; i++ ){

		if( imcsavedata_BGArry_get( p_arry, i ) != IMC_BG_RIGHT_MAX ){
			count ++;
		}
	}
	return count;
}

//----------------------------------------------------------------------------
/**
 *	@brief	そのアクセサリは9個保持するアクセサリかチェック
 *
 *	@param	acce_no		アクセサリナンバー
 *
 *	@retval	TRUE	9個保持出来る
 *	@retval	FALSE	1個保持できる
 */
//-----------------------------------------------------------------------------
static inline BOOL imcsavedata_AcceNo_9Check( u32 acce_no )
{
	if( acce_no < IMC_ACCE_GET_1_START ){
		return TRUE;
	}
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	アクセサリナンバーを1個保持アクセサリからの数字に変更
 *
 *	@param	acce_no		アクセサリナンバー
 *
 *	@return	1個保持アクセサリからの数
 */
//-----------------------------------------------------------------------------
static inline u8 imcsavedata_AcceNo_1Get( u32 acce_no )
{
	GF_ASSERT( acce_no >= IMC_ACCE_GET_1_START );

	return acce_no - IMC_ACCE_GET_1_START;
}

//----------------------------------------------------------------------------
/**
 *	@brief	アイテムセーブ領域の初期化
 *
 *	@param	wk	ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static inline void clean_item_savedata( IMC_ITEM_SAVEDATA* wk )
{
	int i;
	memset( wk, 0, sizeof(IMC_ITEM_SAVEDATA) );

	// BGの領域は最初に最大数を格納しておく
	for( i=0; i<IMC_BG_RIGHT_MAX; i++ ){
		imcsavedata_BGArry_set( wk->bg, IMC_BG_RIGHT_MAX, i );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンナンバーから　ポケモンの座標を取得
 */
//-----------------------------------------------------------------------------
static void ImcSaveData_ImcPokeObjContestMatGet( POKEMON_PARAM* pp, u8* x, u8* y )
{
	u8 height = PokeParaHeightGet( pp, PARA_FRONT );

	*x = IMC_POKE_INIT_X - (IMC_SEENFADE_MOVE_ADD_X*IMC_SEENFADE_MOVE_COUNT);

	// 1まずクリップ時のざひょうにする
	*y = (IMC_RBOX_AREA_Y + IMC_RBOX_AREA_HEIGHT) - ((SOFT_SPRITE_SIZE_Y/2) - height) + IMC_POKE_MAT_CONTEST_Y_OFS;
	// 2その後、セーブ時のざひょうにする	テレビ用とコンテスト用のセーブ時の基準座標をあわせるため
	*y += (IMC_SEENFADE_MOVE_ADD_Y*IMC_SEENFADE_MOVE_COUNT);
}


//----------------------------------------------------------------------------
/**
 *	@brief	イメージクリップワークの初期化
 *
 *	@param	iw	イメージクリップワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ImcSaveData_Init(IMC_SAVEDATA * iw)
{
	int i;

	for( i=0; i<IMC_SAVEDATA_TELEVISION_SAVENUM; i++ ){
		clean_television_savedata( &iw->imc_television_savedata[ i ] );
	}
	for( i=0; i<IMC_SAVEDATA_CONTEST_SAVENUM; i++ ){
		clean_contest_savedata( &iw->imc_contest_savedata[ i ] );
	}
	clean_item_savedata( &iw->imc_item_savedata );
}


//----------------------------------------------------------
//	セーブデータシステムが依存する関数
//----------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	イメージクリップセーブデータワークサイズの取得
 *
 *	@param	none
 *
 *	@return	ワークサイズ
 */
//-----------------------------------------------------------------------------
int ImcSaveData_GetWorkSize(void)
{
	return sizeof(IMC_SAVEDATA);
}

//----------------------------------------------------------------------------
/**
 *	@brief	イメージクリップ用ワークの生成処理
 *
 *	@param	heapID		ヒープID
 *
 *	@return	生成したイメージクリップワークのポインタ
 */
//-----------------------------------------------------------------------------
IMC_SAVEDATA * ImcSaveData_AllocWork(u32 heapID)
{
	IMC_SAVEDATA * iw;
	iw = sys_AllocMemory(heapID, sizeof(IMC_SAVEDATA));
	ImcSaveData_Init(iw);
	return iw;
}

//----------------------------------------------------------------------------
/**
 *	@brief	テレビ用ワークサイズ取得
 *
 *	@param	none
 *
 *	@return	ワークサイズ
 */
//-----------------------------------------------------------------------------
int ImcSaveData_GetTelevisionWorkSize(void)
{
	return sizeof(IMC_TELEVISION_SAVEDATA);
}

//----------------------------------------------------------------------------
/**
 *	@brief	コンテスト用ワークサイズ取得
 *
 *	@param	none
 *
 *	@return	ワークサイズ
 */
//-----------------------------------------------------------------------------
int ImcSaveData_GetContestWorkSize(void)
{
	return sizeof(IMC_CONTEST_SAVEDATA);
}


//----------------------------------------------------------------------------
/**
 *	@brief	テレビ用ワーク作成
 *
 *	@param	heapID	ヒープ
 *
 *	@return	ワークポインタ
 */
//-----------------------------------------------------------------------------
IMC_TELEVISION_SAVEDATA* ImcSaveData_TelevisionAllocWork(u32 heapID)
{
	IMC_TELEVISION_SAVEDATA* iow;

	iow = sys_AllocMemory(heapID, sizeof(IMC_TELEVISION_SAVEDATA));
	clean_television_savedata( iow );
	return iow;
}

//----------------------------------------------------------------------------
/**
 *	@brief	コンテスト用ワーク作成
 *
 *	@param	heapID	ヒープ
 *
 *	@return	ワークポインタ
 */
//-----------------------------------------------------------------------------
IMC_CONTEST_SAVEDATA* ImcSaveData_ContestAllocWork(u32 heapID)
{
	IMC_CONTEST_SAVEDATA* iow;

	iow = sys_AllocMemory(heapID, sizeof(IMC_CONTEST_SAVEDATA));
	clean_contest_savedata( iow );
	return iow;
}

//----------------------------------------------------------------------------
/**
 *	@brief	アイテム用ワーク作成
 *
 *	@param	heapID	ヒープ
 *
 *	@return	ワークポインタ
 */
//-----------------------------------------------------------------------------
IMC_ITEM_SAVEDATA* ImcSaveData_ItemAllocWork(u32 heapID)
{
	IMC_ITEM_SAVEDATA* iow;

	iow = sys_AllocMemory(heapID, sizeof(IMC_ITEM_SAVEDATA));
	clean_item_savedata( iow );
	
	return iow;
}


//-----------------------------------------------------------------------------
//	ワークデータ読み書き
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	イメージクリップデータのテレビジョン1つを取得する
 *
 *	@param	iw		イメージクリップワーク
 *	@param	no		取得インデックス
 *
 *	@return	テレビジョン1つのデータ
 */
//-----------------------------------------------------------------------------
IMC_TELEVISION_SAVEDATA* ImcSaveData_GetTelevisionSaveData(IMC_SAVEDATA* iw, int no)
{
	GF_ASSERT( no < IMC_SAVEDATA_TELEVISION_SAVENUM );		///<配列最大数チェック
	//正当性チェック
	GF_ASSERT( correct_television_savedata( &iw->imc_television_savedata[ no ] ) );
	
	return &iw->imc_television_savedata[ no ];
}

//----------------------------------------------------------------------------
/**
 *	@brief	コンテスト用セーブデータの1つを取得する
 *
 *	@param	iw		イメージクリップワーク
 *	@param	no		取得インデックス
 *
 *	@return	コンテスト用セーブデータ
 */
//-----------------------------------------------------------------------------
IMC_CONTEST_SAVEDATA* ImcSaveData_GetContestSaveData(IMC_SAVEDATA* iw, int no)
{
	GF_ASSERT( no < IMC_SAVEDATA_CONTEST_SAVENUM );		///<配列最大数チェック
	//正当性チェック
	GF_ASSERT( correct_contest_savedata( &iw->imc_contest_savedata[ no ] ) );
	
	return &iw->imc_contest_savedata[ no ];
}

//----------------------------------------------------------------------------
/**
 *	@brief	セーブデータからアイテム保持セーブワークを取得
 *
 *	@param	iw		イメージクリップワーク
 *
 *	@return	アイテムセーブデータ
 */
//-----------------------------------------------------------------------------
IMC_ITEM_SAVEDATA* ImcSaveData_GetItemSaveData(IMC_SAVEDATA* iw)
{
	return &iw->imc_item_savedata;
}

//----------------------------------------------------------------------------
/**
 *	@brief	そのテレビ局用セーブデータ領域にセーブしているか
 *
 *	@param	iw	イメージクリップワーク
 *	@param	no	チェックするインデックス
 *
 *	@retval	TRUE	セーブ済み
 *	@retval	FALSE	セーム未完了
 */
//-----------------------------------------------------------------------------
BOOL ImcSaveData_CheckTelevisionSaveData(const IMC_SAVEDATA* iw, int no)
{
	GF_ASSERT( no < IMC_SAVEDATA_TELEVISION_SAVENUM );		///<配列最大数チェック

	return ImcSaveData_CheckTelevisionData( &iw->imc_television_savedata[ no ] );
}

//----------------------------------------------------------------------------
/**
 *	@brief	そのテレビ局用セーブデータ領域にセーブしているか
 *
 *	@param	iw	イメージクリップワーク
 *	@param	no	チェックするインデックス
 *
 *	@retval	TRUE	セーブ済み
 *	@retval	FALSE	セーム未完了
 */
//-----------------------------------------------------------------------------
BOOL ImcSaveData_CheckContestSaveData(const IMC_SAVEDATA* iw, int no)
{
	GF_ASSERT( no < IMC_SAVEDATA_CONTEST_SAVENUM );		///<配列最大数チェック

	return ImcSaveData_CheckContestData( &iw->imc_contest_savedata[ no ] );
}

//----------------------------------------------------------------------------
/**
 *	@brief	アクセサリ追加できるかチェック
 *
 *	@param	p_iow		セーブデータワーク
 *	@param	acce_no		アクセサリワーク
 *	@param	num			アクセサリ数
 *
 *	@retval	TRUE	追加可能
 *	@retval	FALSE	追加不可能
 */
//-----------------------------------------------------------------------------
BOOL ImcSaveData_CheckAcceAdd( const IMC_ITEM_SAVEDATA* p_iow, u32 acce_no, u32 num )
{
	u32 get;
	BOOL ret = TRUE;

	// 保持数取得
	get = ImcSaveData_GetAcceFlag( p_iow, acce_no );
	
	// 9個もてるか1個もてるかチェック
	if( imcsavedata_AcceNo_9Check( acce_no ) ){
		// 9
		get += num;
		if( get > 9 ){
			ret = FALSE;
		}
	}else{
		// 1
		get += num;
		if( get > 1 ){
			ret = FALSE;
		}
	}
	return ret;
}

//----------------------------------------------------------------------------
/**
 *	@brief	アクセサリ保持しているかチェック
 *
 *	@param	p_iow		セーブデータワーク
 *	@param	acce_no		アクセサリナンバー 
 *
 *	@retval	TRUE	保持
 *	@retval	FALSE	もっていない
 */
//-----------------------------------------------------------------------------
BOOL ImcSaveData_CheckAcceGet( const IMC_ITEM_SAVEDATA* p_iow, u32 acce_no )
{
	u32 get;

	// 保持数取得
	get = ImcSaveData_GetAcceFlag( p_iow, acce_no );

	if( get > 0 ){
		return TRUE;
	}
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	BG背景を保持しているかをチェック
 *
 *	@param	p_iow		セーブデータワーク
 *	@param	bg_no		BGナンバー
 *	
 *	@retval	TRUE	保持
 *	@retval	FALSE	もっていない
 */
//-----------------------------------------------------------------------------
BOOL ImcSaveData_CheckBgGet( const IMC_ITEM_SAVEDATA* p_iow, u32 bg_no )
{
	u32 get;

	// 保持順番取得
	get = ImcSaveData_GetBGFlag( p_iow, bg_no );

	if( get != IMC_BG_RIGHT_MAX ){
		return TRUE;
	}
	return FALSE;
}


//----------------------------------------------------------------------------
/**
 *	@brief	アクセサリフラグがたっているかチェック
 *
 *	@param	cp_iow		アイテムセーブワーク
 *	@param	acce_no		アクセサリナンバー
 *
 *	@return	保持数
 */
//-----------------------------------------------------------------------------
u32 ImcSaveData_GetAcceFlag( const IMC_ITEM_SAVEDATA* cp_iow, u32 acce_no )
{
	u32 num;
	
	// アクセサリ数
	GF_ASSERT( acce_no < IMC_ACCE_MAX );

	// 9個もてるか1個もてるかチェック
	if( imcsavedata_AcceNo_9Check( acce_no ) ){
		// 9個
		num = imcsavedata_Acce9Get( cp_iow->acce_9, acce_no );
	}else{
		// 1個
		acce_no = imcsavedata_AcceNo_1Get( acce_no );	// アクセサリNoを1個保持アクセサリからの数に変更
		num = imcsavedata_1bitArry_get( cp_iow->acce_1, acce_no );
	}

	return num;
}

//----------------------------------------------------------------------------
/**
 *	@brief	BG保持フラグ取得
 *
 *	@param	cp_iow	アイテムセーブデータ
 *	@param	bg_no	BGナンバー
 *	
 *	@return	保持した順番
 *	@retval	IMC_BG_RIGHT_MAXのときはまだ保持していない
 */
//-----------------------------------------------------------------------------
u32 ImcSaveData_GetBGFlag( const IMC_ITEM_SAVEDATA* cp_iow, u32 bg_no )
{
	BOOL get;
	
	// 背景数
	GF_ASSERT( bg_no < IMC_BG_RIGHT_MAX );
	get = imcsavedata_BGArry_get( cp_iow->bg, bg_no );

	return get;
}


//----------------------------------------------------------------------------
/**
 *	@brief	アクセサリ　背景　全てのアイテム保持数を返す
 *
 *	@param	cp_iow	アイテムセーブデータ
 *
 *	@return	保持数
 */
//-----------------------------------------------------------------------------
u32 ImcSaveData_GetAcceBGAllNum( const IMC_ITEM_SAVEDATA* cp_iow )
{
	u32 count;

	count = ImcSaveData_GetAcceAllNum( cp_iow );
	count += ImcSaveData_GetBGAllNum( cp_iow );
	return count;
}

//----------------------------------------------------------------------------
/**
 *	@brief	アクセサリ　全てのアイテム保持数を返す
 *
 *	@param	cp_iow	アイテムセーブデータ
 *
 *	@return	保持数
 */
//-----------------------------------------------------------------------------
u32 ImcSaveData_GetAcceAllNum( const IMC_ITEM_SAVEDATA* cp_iow )
{
	int i;	
	int count;
	count = 0;
	for( i=0; i<IMC_ACCE_MAX; i++ ){
		count += ImcSaveData_GetAcceFlag( cp_iow, i );
	}

	return count;
}

//----------------------------------------------------------------------------
/**
 *	@brief	背景　全てのアイテム保持数を返す
 *
 *	@param	cp_iow	アイテムセーブデータ
 *
 *	@return	保持数
 */
//-----------------------------------------------------------------------------
u32 ImcSaveData_GetBGAllNum( const IMC_ITEM_SAVEDATA* cp_iow )
{
	int i;
	int count = 0;
	
	for( i=0; i<IMC_BG_RIGHT_MAX; i++ ){

		if( ImcSaveData_GetBGFlag( cp_iow, i ) != IMC_BG_RIGHT_MAX ){
			count ++;
		}
	}
	return count;
}

//----------------------------------------------------------------------------
/**
 *	@brief	アクセサリ保持数セット
 *
 *	@param	p_iow		アイテムセーブ領域
 *	@param	acce_no		アクセサリナンバー
 *	@param	num			設定数
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ImcSaveData_SetAcceFlag( IMC_ITEM_SAVEDATA* p_iow, u32 acce_no, u32 num )
{
	// アクセサリ数
	GF_ASSERT( acce_no < IMC_ACCE_MAX );

	// 9個もてるか1個もてるかチェック
	if( imcsavedata_AcceNo_9Check( acce_no ) ){
		// 9個以上にしない
		if( num > IMC_ACCE_9_GET_NUM ){
			num = IMC_ACCE_9_GET_NUM;
		}
		imcsavedata_Acce9Set( p_iow->acce_9, num, acce_no );
	}else{
		// 1個以上にしない
		if( num > IMC_ACCE_1_GET_NUM ){
			num = IMC_ACCE_1_GET_NUM;
		}
		acce_no = imcsavedata_AcceNo_1Get( acce_no );	// アクセサリNoを1個保持アクセサリからの数に変更
		imcsavedata_1bitArry_set( p_iow->acce_1, num, acce_no );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	アクセサリ保持数の足し算
 *
 *	@param	p_iow		アイテムセーブ領域
 *	@param	acce_no		アクセサリナンバー
 *	@param	num			足す値
 *
 *	@return
 */
//-----------------------------------------------------------------------------
void ImcSaveData_AddAcceFlag( IMC_ITEM_SAVEDATA* p_iow, u32 acce_no, u32 num )
{
	u8 now_num;
	
	// アクセサリ数
	GF_ASSERT( acce_no < IMC_ACCE_MAX );

	// 9個もてるか1個もてるかチェック
	if( imcsavedata_AcceNo_9Check( acce_no ) ){
		now_num = imcsavedata_Acce9Get( p_iow->acce_9, acce_no );
		// 9個以上にしない
		now_num += num;
		if( now_num > IMC_ACCE_9_GET_NUM ){
			now_num = IMC_ACCE_9_GET_NUM;
		}
		imcsavedata_Acce9Set( p_iow->acce_9, now_num, acce_no );
	}else{
		now_num = imcsavedata_1bitArry_get( p_iow->acce_1, acce_no );
		// 1個以上にしない
		now_num += num;
		if( now_num > IMC_ACCE_1_GET_NUM ){
			now_num = IMC_ACCE_1_GET_NUM;
		}
		acce_no = imcsavedata_AcceNo_1Get( acce_no );	// アクセサリNoを1個保持アクセサリからの数に変更
		imcsavedata_1bitArry_set( p_iow->acce_1, now_num, acce_no );
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	アクセサリ保持数の引き算
 *
 *	@param	p_iow		アイテムセーブ領域
 *	@param	acce_no		アクセサリナンバー
 *	@param	num			引く値
 *
 *	@return
 */
//-----------------------------------------------------------------------------
void ImcSaveData_SubAcceFlag( IMC_ITEM_SAVEDATA* p_iow, u32 acce_no, u32 num )
{
	u8 now_num;
	
	// アクセサリ数
	GF_ASSERT( acce_no < IMC_ACCE_MAX );

	// 9個もてるか1個もてるかチェック
	if( imcsavedata_AcceNo_9Check( acce_no ) ){
		now_num = imcsavedata_Acce9Get( p_iow->acce_9, acce_no );
		if( now_num > num){
			now_num -= num;
		}else{
			now_num = 0;
		}
		imcsavedata_Acce9Set( p_iow->acce_9, now_num, acce_no );
	}else{
		now_num = 0;
		acce_no = imcsavedata_AcceNo_1Get( acce_no );	// アクセサリNoを1個保持アクセサリからの数に変更
		imcsavedata_1bitArry_set( p_iow->acce_1, now_num, acce_no );
	}
}

//----------------------------------------------------------------------------
/**	
 *	@brief	BG保持フラグ設定
 *
 *	@param	p_iow		アイテムセーブ領域ワーク
 *	@param	bg_no		BGナンバー
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ImcSaveData_SetBGFlag( IMC_ITEM_SAVEDATA* p_iow, u32 bg_no )
{
	u8 get_no;
	
	// 背景数
	GF_ASSERT( bg_no < IMC_BG_RIGHT_MAX );

	// すでに保持していないかチェック
	if( imcsavedata_BGArry_get( p_iow->bg, bg_no ) == IMC_BG_RIGHT_MAX ){

		// 設定する保持した順番を取得
		get_no = imcsavedata_BGArry_FlagOnDataNumGet( p_iow->bg );

		// 設定
		imcsavedata_BGArry_set( p_iow->bg, get_no, bg_no );
	}
	
}





//----------------------------------------------------------------------------
/**
 *	@brief	セーブデータに値を設定済みかチェック
 *
 *	@param	iow	イメージクリップワーク
 *
 *	@retval	TRUE	セーブ済み
 *	@retval	FALSE	セーム未完了
 */
//-----------------------------------------------------------------------------
BOOL ImcSaveData_CheckTelevisionData(const IMC_TELEVISION_SAVEDATA* iow)
{
	//正当性チェック
	GF_ASSERT( correct_television_savedata( iow ) );

	if( iow->init_flag == IMC_SAVEDATA_DATASET_FLAG ){
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	セーブ完了フラグを設定する
 *
 *	@param	iw	イメージクリップワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ImcSaveData_SetComplateFlagTelevisionData(IMC_TELEVISION_SAVEDATA* iow)
{
	//正当性チェック
	GF_ASSERT( correct_television_savedata( iow ) );
	iow->init_flag = IMC_SAVEDATA_DATASET_FLAG;
	iow->country = CasetteLanguage;
}

//----------------------------------------------------------------------------
/**
 *	@brief	セーブデータを初期化する
 *
 *	@param	iw		イメージクリップワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ImcSaveData_ClaenTelevisionData(IMC_TELEVISION_SAVEDATA* iow)
{
	//正当性チェック
	GF_ASSERT( correct_television_savedata( iow ) );

	// ワークの初期化
	clean_television_savedata( iow );
}
	
//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンデータを登録する
 *
 *	@param	iow		イメージクリップワーク
 *	@param	pp		ポケモンパラメータ
 *	@param	ip		イメージクリップポケモンデータ
 */
//-----------------------------------------------------------------------------
void ImcSaveData_SetTelevisionPokeData(IMC_TELEVISION_SAVEDATA* iow, POKEMON_PARAM* pp, IMC_POKE* ip)
{
	//正当性チェック
	GF_ASSERT( correct_television_savedata( iow ) );
	// ポケモンデータ格納
	ImcSaveData_SetPokeData_Local( &iow->pokemon, pp, ip );
}

//----------------------------------------------------------------------------
/**
 *	@brief	アクセサリデータ設定
 *
 *	@param	iow		イメージクリップワーク	
 *	@param	ao		アクセサリーデータ
 *	@param	no		アクセサリーナンバー
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ImcSaveData_SetTelevisionAcceData(IMC_TELEVISION_SAVEDATA* iow, const IMC_ACCESSORIE_OBJ* ao, int no)
{
	NNSG2dSVec2 mat = SWSP_GetSpritePos( ao->drawObj );
	int pri = SWSP_GetSpritePriority( ao->drawObj );
	
	GF_ASSERT( no < IMC_SAVEDATA_TELEVISION_ACCE_NUM );		///<配列最大数チェック
	GF_ASSERT( mat.x < 256 );		// u8に入るように
	GF_ASSERT( mat.y < 256 );		// u8に入るように
	GF_ASSERT( pri > -128 );		// u8に入るように
	GF_ASSERT( !(iow->accessory_set_msk & (1 << no)) );	///<多重登録チェック
	//正当性チェック
	GF_ASSERT( correct_television_savedata( iow ) );
	
	//　データ設定
	imcsavedata_SetAcce_Local( &iow->acce[ no ],
			ao->accessorie_no,
			mat.x,
			mat.y,
			pri);

	// マスク設定
	iow->accessory_set_msk |= 1 << no;
}

//----------------------------------------------------------------------------
/**
 *	@brief	BGIDの設定
 *
 *	@param	iow		イメージクリップワーク
 *	@param	bg		BGID
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ImcSaveData_SetTelevisionBgId(IMC_TELEVISION_SAVEDATA* iow, u8 bg)
{
	//正当性チェック
	GF_ASSERT( correct_television_savedata( iow ) );

	iow->bg_id = bg;
}

//----------------------------------------------------------------------------
/**
 *	@brief	クリップのタイトル格納
 *
 *	@param	iow		イメージクリップワーク
 *	@param	str		タイトル名単語
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ImcSaveData_SetTelevisionTitle( IMC_TELEVISION_SAVEDATA* iow, const PMS_DATA* str )
{
	//正当性チェック
	GF_ASSERT( correct_television_savedata( iow ) );
	PMSDAT_Copy( &iow->title, str );
}

//----------------------------------------------------------------------------
/**
 *	@brief	タイトル単語設定
 *
 *	@param	iow		ワーク
 *	@param	word	簡易単語ID
 */
//-----------------------------------------------------------------------------
void ImcSaveData_SetTelevisionTitlePmsWord( IMC_TELEVISION_SAVEDATA* iow, PMS_WORD word )
{
	//正当性チェック
	GF_ASSERT( correct_television_savedata( iow ) );
	PMSDAT_Clear( &iow->title );
	PMSDAT_SetWord( &iow->title, 0, word );
}

//----------------------------------------------------------------------------
/**
 *	@brief	テレビ局クリップデータコピー関数
 *
 *	@param	iow			ワーク
 *	@param	set_iow		設定するデータワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ImcSaveData_CopyTelevision( IMC_TELEVISION_SAVEDATA* iow, const IMC_TELEVISION_SAVEDATA* set_iow )
{
	//正当性チェック
	GF_ASSERT( correct_television_savedata( iow ) );
	memcpy( iow, set_iow, sizeof(IMC_TELEVISION_SAVEDATA) );
}

//----------------------------------------------------------------------------
/**
 *	@brief	トレーナーデータ設定
 *
 *	@param	iow		ワーク
 *	@param	pbuff	トレーナー名データ
 *	@param	sex		性別
 */
//-----------------------------------------------------------------------------
void ImcSaveData_SetTelevisionTrData( IMC_TELEVISION_SAVEDATA* iow, const STRBUF* pbuff, int sex )
{
	//正当性チェック
	GF_ASSERT( correct_television_savedata( iow ) );
	ImcSaveData_SetTrData_Local( &iow->pokemon, pbuff, sex );
}

//----------------------------------------------------------------------------
/**
 *	@brief	引数のインデックスのアクセサリが登録されているかチェック
 *
 *	@param	iow		１セーブデータ
 *	@param	no		アクセサリ格納配列インデックス
 *
 *	@retval	TRUE	登録済み
 *	@retval	FALSE	未登録
 */
//-----------------------------------------------------------------------------
BOOL ImcSaveData_CheckTelevisionAcceDataSet(const IMC_TELEVISION_SAVEDATA* iow, int no)
{
	GF_ASSERT( no < IMC_SAVEDATA_TELEVISION_ACCE_NUM );		///<配列最大数チェック
	//正当性チェック
	GF_ASSERT( correct_television_savedata( iow ) );

	return iow->accessory_set_msk & (1 << no);
}


//----------------------------------------------------------------------------
/**
 *	@brief	テレビ局用ワークからポケモンセーブデータ取得
 *
 *	@param	iow		ワーク
 *
 *	@return	ポケモンセーブデータ
 */
//-----------------------------------------------------------------------------
const IMC_SAVEDATA_POKEMON* ImcSaveData_GetTelevisionPokemon(const IMC_TELEVISION_SAVEDATA* iow)
{
	//正当性チェック
	GF_ASSERT( correct_television_savedata( iow ) );
	return &iow->pokemon;
}

//----------------------------------------------------------------------------
/**
 *	@brief	テレビ局ワークからアクセサリセーブデータ取得
 *
 *	@param	iow		ワーク
 *	@param	no		アクセサリナンバー
 *
 *	@return	アクセサリセーブデータ
 */
//-----------------------------------------------------------------------------
const IMC_SAVEDATA_ACCESSORIE* ImcSaveData_GetTelevisionAcce(const IMC_TELEVISION_SAVEDATA* iow, int no)
{
	GF_ASSERT( no < IMC_SAVEDATA_TELEVISION_ACCE_NUM );		///<1データ無いアクセサリ最大数チェック
	GF_ASSERT( iow->accessory_set_msk & (1 << no) );	///<アクセサリデータ格納済みチェック
	//正当性チェック
	GF_ASSERT( correct_television_savedata( iow ) );
	return &iow->acce[no];
}

//----------------------------------------------------------------------------
/**
 *	@brief	モンスターナンバー取得
 *
 *	@param	iow		イメージクリップワーク
 *
 *	@return	モンスターナンバー
 */
//-----------------------------------------------------------------------------
u16 ImcSaveData_GetTelevisionPokeMonsNo(const IMC_TELEVISION_SAVEDATA* iow)
{
	//正当性チェック
	GF_ASSERT( correct_television_savedata( iow ) );
	return ImcSaveData_GetUtilPokeMonsNo(&iow->pokemon);
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンニックネーム取得
 *
 *	@param	iow		イメージクリップワーク
 *	@param	pbuff	文字列格納バッファ　要素数　IMC_SAVEDATA_STRBUF_NUM必要
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ImcSaveData_GetTelevisionPokeNickName(const IMC_TELEVISION_SAVEDATA* iow, STRBUF* pbuff)
{
	//正当性チェック
	GF_ASSERT( correct_television_savedata( iow ) );
	ImcSaveData_GetUtilPokeNickName(&iow->pokemon, pbuff);
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンの親ネーム取得
 *
 *	@param	iow		イメージクリップワーク
 *	@param	pbuff	文字列格納バッファ　要素数　IMC_SAVEDATA_STRBUF_NUM必要
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ImcSaveData_GetTelevisionPokeOyaName(const IMC_TELEVISION_SAVEDATA* iow, STRBUF* pbuff)
{
	//正当性チェック
	GF_ASSERT( correct_television_savedata( iow ) );
	ImcSaveData_GetUtilPokeOyaName(&iow->pokemon, pbuff);
}

//----------------------------------------------------------------------------
/**
 *	@brief	親性別取得
 *
 *	@param	iow		イメージクリップワーク
 *
 *	@return	親性別
 */
//-----------------------------------------------------------------------------
u32 ImcSaveData_GetTelevisionPokeOyaSex(const IMC_TELEVISION_SAVEDATA* iow)
{
	//正当性チェック
	GF_ASSERT( correct_television_savedata( iow ) );
	return ImcSaveData_GetUtilPokeOyaSex(&iow->pokemon);
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモン個性乱数取得
 *
 *	@param	iow		イメージクリップワーク
 *
 *	@return	個性乱数
 */
//-----------------------------------------------------------------------------
u32 ImcSaveData_GetTelevisionPokeRnd(const IMC_TELEVISION_SAVEDATA* iow)
{
	//正当性チェック
	GF_ASSERT( correct_television_savedata( iow ) );
	return ImcSaveData_GetUtilPokeRnd( &iow->pokemon );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンIDナンバー取得
 *
 *	@param	iow		イメージクリップワーク
 *
 *	@return	IDNo
 */
//-----------------------------------------------------------------------------
u32 ImcSaveData_GetTelevisionPokeIDNo(const IMC_TELEVISION_SAVEDATA* iow)
{
	//正当性チェック
	GF_ASSERT( correct_television_savedata( iow ) );
	return ImcSaveData_GetUtilPokeIDNo( &iow->pokemon );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモン形状ナンバーの取得
 *
 *	@param	iow
 *
 *	@return	形状ナンバー
 */
//-----------------------------------------------------------------------------
u32 ImcSaveData_GetTelevisionPokeFormID(const IMC_TELEVISION_SAVEDATA* iow)
{
	//正当性チェック
	GF_ASSERT( correct_television_savedata( iow ) );
	return ImcSaveData_GetUtilPokeFormID( &iow->pokemon );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモングラフィック優先順位取得
 *
 *	@param	iow		イメージクリップワーク
 *
 *	@return	個性乱数
 */
//-----------------------------------------------------------------------------
s8 ImcSaveData_GetTelevisionPokePri(const IMC_TELEVISION_SAVEDATA* iow)
{
	//正当性チェック
	GF_ASSERT( correct_television_savedata( iow ) );
	return ImcSaveData_GetUtilPokePri(&iow->pokemon);
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモングラフィック表示ｘ座標取得
 *
 *	@param	iow		イメージクリップワーク
 *
 *	@return	X座標
 */
//-----------------------------------------------------------------------------
u8 ImcSaveData_GetTelevisionPokeX(const IMC_TELEVISION_SAVEDATA* iow)
{
	//正当性チェック
	GF_ASSERT( correct_television_savedata( iow ) );
	return ImcSaveData_GetUtilPokeX( &iow->pokemon );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモングラフィックｙ座標取得
 *
 *	@param	iow		イメージクリップワーク
 *
 *	@return	ｙ座標
 */
//-----------------------------------------------------------------------------
u8 ImcSaveData_GetTelevisionPokeY(const IMC_TELEVISION_SAVEDATA* iow)
{
	//正当性チェック
	GF_ASSERT( correct_television_savedata( iow ) );
	return ImcSaveData_GetUtilPokeY( &iow->pokemon );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンパラメータを取得する
 *
 *	@param	iow		イメージクリップセーブデータ
 *	@param	pp		ポケモンパラメータ
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ImcSaveData_GetTelevisionPokePara(const IMC_TELEVISION_SAVEDATA* iow, POKEMON_PARAM* pp)
{
	//正当性チェック
	GF_ASSERT( correct_television_savedata( iow ) );
	imcsacedata_GetPokePara_Local( &iow->pokemon, pp );
}

//----------------------------------------------------------------------------
/**
 *	@brief	アクセサリナンバー取得
 *
 *	@param	iow		イメージクリップワーク
 *	@param	no		アクセサリインデックス
 *	
 *	@return	アクセサリナンバー
 */
//-----------------------------------------------------------------------------
u8 ImcSaveData_GetTelevisionAcceNo(const IMC_TELEVISION_SAVEDATA* iow, int no)
{
	GF_ASSERT( no < IMC_SAVEDATA_TELEVISION_ACCE_NUM );		///<1データ無いアクセサリ最大数チェック
	GF_ASSERT( iow->accessory_set_msk & (1 << no) );	///<アクセサリデータ格納済みチェック
	//正当性チェック
	GF_ASSERT( correct_television_savedata( iow ) );
	return ImcSaveData_GetUtilAcceNo( &iow->acce[no] );
}

//----------------------------------------------------------------------------
/**
 *	@brief	アクセサリX座標取得
 *
 *	@param	iow		イメージクリップワーク
 *	@param	no		アクセサリインデックス
 *	
 *	@return	アクセサリ表示ｘ座標
 */
//-----------------------------------------------------------------------------
u8 ImcSaveData_GetTelevisionAcceMatX(const IMC_TELEVISION_SAVEDATA* iow, int no)
{
	GF_ASSERT( no < IMC_SAVEDATA_TELEVISION_ACCE_NUM );		///<1データ無いアクセサリ最大数チェック
	GF_ASSERT( iow->accessory_set_msk & (1 << no) );	///<アクセサリデータ格納済みチェック
	//正当性チェック
	GF_ASSERT( correct_television_savedata( iow ) );
	return ImcSaveData_GetUtilAcceMatX( &iow->acce[no] );
}

//----------------------------------------------------------------------------
/**
 *	@brief	アクセサリｙ座標取得
 *
 *	@param	iow		イメージクリップワーク
 *	@param	no		アクセサリインデックス
 *
 *	@return	アクセサリ表示ｙ座標
 */
//-----------------------------------------------------------------------------
u8 ImcSaveData_GetTelevisionAcceMatY(const IMC_TELEVISION_SAVEDATA* iow, int no)
{
	GF_ASSERT( no < IMC_SAVEDATA_TELEVISION_ACCE_NUM );		///<1データ無いアクセサリ最大数チェック
	GF_ASSERT( iow->accessory_set_msk & (1 << no) );	///<アクセサリデータ格納済みチェック
	//正当性チェック
	GF_ASSERT( correct_television_savedata( iow ) );

	return ImcSaveData_GetUtilAcceMatY( &iow->acce[no] );
}

//----------------------------------------------------------------------------
/**
 *	@brief	アクセサリ表示優先順位取得
 *
 *	@param	iow		イメージクリップワーク
 *	@param	no		アクセサリインデックス
 *
 *	@return	アクセサリ表示優先順位
 */
//-----------------------------------------------------------------------------
s8 ImcSaveData_GetTelevisionAccePri(const IMC_TELEVISION_SAVEDATA* iow, int no)
{
	GF_ASSERT( no < IMC_SAVEDATA_TELEVISION_ACCE_NUM );		///<1データ無いアクセサリ最大数チェック
	GF_ASSERT( iow->accessory_set_msk & (1 << no) );	///<アクセサリデータ格納済みチェック
	//正当性チェック
	GF_ASSERT( correct_television_savedata( iow ) );

	return ImcSaveData_GetUtilAccePri( &iow->acce[no] );
}

//----------------------------------------------------------------------------
/**
 *	@brief	BGIDを取得
 *	
 *	@param	iow		イメージクリップワーク
 *
 *	@return	BGID
 */
//-----------------------------------------------------------------------------
u8 ImcSaveData_GetTelevisionBgId(const IMC_TELEVISION_SAVEDATA* iow)
{
	//正当性チェック
	GF_ASSERT( correct_television_savedata( iow ) );
	return iow->bg_id;
}

//----------------------------------------------------------------------------
/**
 *	@brief	イメージクリップタイトルを取得
 *
 *	@param	iow		イメージクリップワーク
 *	@param	pbuff	格納先バッファ
 *
 *	@return	none	
 */
//-----------------------------------------------------------------------------
void ImcSaveData_GetTelevisionTitle( const IMC_TELEVISION_SAVEDATA* iow, PMS_DATA* pbuff )
{
	//正当性チェック
	GF_ASSERT( correct_television_savedata( iow ) );
	PMSDAT_Copy(pbuff, &iow->title);
}

//----------------------------------------------------------------------------
/**
 *	@brief	テレビタイトル　簡易会話単語
 *
 *	@param	iow		セーブワーク
 *
 *	@return	単語ID
 */
//-----------------------------------------------------------------------------
PMS_WORD ImcSaveData_GetTelevisionTitlePmsWord( const IMC_TELEVISION_SAVEDATA* iow )
{
	PMS_WORD work = PMSDAT_GetWordNumber( &iow->title, 0 );
	return work;
}

//----------------------------------------------------------------------------
/**
 *	@brief	国コード取得
 *
 *	@param	iow 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
u8 ImcSaveData_GetCountryCode( const IMC_TELEVISION_SAVEDATA* iow )
{
	//正当性チェック
	GF_ASSERT( correct_television_savedata( iow ) );

	return iow->country;
}
	

//-----------------------------------------------------------------------------
//	IMC_CONTEST_SAVEDATA操作関数
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *	@brief	ワークにコンテストセーブデータが格納されているかチェック
 *
 *	@param	iow		イメージクリップワーク
 *
 *	@retval	TRUE	セーブ済み
 *	@retval	FALSE	セーム未完了
 */
//-----------------------------------------------------------------------------
BOOL ImcSaveData_CheckContestData(const IMC_CONTEST_SAVEDATA* iow)
{
	//正当性チェック
	GF_ASSERT( correct_contest_savedata( iow ) );
	if( iow->init_flag == IMC_SAVEDATA_DATASET_FLAG ){
		return TRUE;
	}
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	セーブ完了フラグを設定
 *
 *	@param	iow		イメージクリップワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ImcSaveData_SetComplateFlagContestData(IMC_CONTEST_SAVEDATA* iow)
{
	//正当性チェック
	GF_ASSERT( correct_contest_savedata( iow ) );
	iow->init_flag = IMC_SAVEDATA_DATASET_FLAG;
}

//----------------------------------------------------------------------------
/**
 *	@brief	セーブデータを初期化する
 *
 *	@param	iow		イメージクリップワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ImcSaveData_ClaenContestData(IMC_CONTEST_SAVEDATA* iow)
{
	//正当性チェック
	GF_ASSERT( correct_contest_savedata( iow ) );

	// ワークの初期化
	clean_contest_savedata( iow );
}

//----------------------------------------------------------------------------
/**
 *	@brief	コンテスト用ワークポケモンデータの設定
 *
 *	@param	iow		イメージクリップワーク
 *	@param	pp		ポケモンパラメータ
 *	@param	ip		イメージクリップポケモンワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ImcSaveData_SetContestPokeData(IMC_CONTEST_SAVEDATA* iow, POKEMON_PARAM* pp, IMC_POKE* ip)
{
	//正当性チェック
	GF_ASSERT( correct_contest_savedata( iow ) );
	// ポケモンデータ格納
	ImcSaveData_SetPokeData_Local( &iow->pokemon, pp, ip );
}

//----------------------------------------------------------------------------
/**
 *	@brief	コンテスト用アクセサリデータの設定
 *
 *	@param	iow		イメージクリップワーク
 *	@param	ao		アクセサリデータ
 *	@param	no		格納ワークインデックス
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ImcSaveData_SetContestAcceData(IMC_CONTEST_SAVEDATA* iow, const IMC_ACCESSORIE_OBJ* ao, int no)
{
	NNSG2dSVec2 mat = SWSP_GetSpritePos( ao->drawObj );
	int pri = SWSP_GetSpritePriority( ao->drawObj );
	
	GF_ASSERT( no < IMC_SAVEDATA_CONTEST_ACCE_NUM );		///<配列最大数チェック
	GF_ASSERT( mat.x < 256 );		// u8に入るように
	GF_ASSERT( mat.y < 256 );		// u8に入るように
	GF_ASSERT( pri > -128 );		// u8に入るように
	GF_ASSERT( !(iow->accessory_set_msk & (1 << no)) );	///<多重登録チェック
	//正当性チェック
	GF_ASSERT( correct_contest_savedata( iow ) );
	
	//　データ設定
	imcsavedata_SetAcce_Local( &iow->acce[ no ],
			ao->accessorie_no,
			mat.x,
			mat.y,
			pri);

	// マスク設定
	iow->accessory_set_msk |= 1 << no;
}

//----------------------------------------------------------------------------
/**
 *	@brief	コンテスト用BGID設定
 *
 *	@param	iow		イメージクリップワーク
 *	@param	bg		BGID
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ImcSaveData_SetContestBgId(IMC_CONTEST_SAVEDATA* iow, u8 bg)
{
	//正当性チェック
	GF_ASSERT( correct_contest_savedata( iow ) );

	iow->bg_id = bg;
}

//----------------------------------------------------------------------------
/**
 *	@brief	コンテスト用ワーク　コンテストランク格納
 *
 *	@param	iow			イメージクリップワーク
 *	@param	rank_code	ランクコード
 *	
 *	@return	none
 *	
 *	rank_code
		///コンテストランク：ノーマルランク
		CONRANK_NORMAL		(0)
		///コンテストランク：スーパーランク
		CONRANK_SUPER		(1)
		///コンテストランク：ハイパーランク
		CONRANK_HYPER		(2)
		///コンテストランク：マスターランク
		CONRANK_MASTER		(3)
 */
//-----------------------------------------------------------------------------
void ImcSaveData_SetContestRank(IMC_CONTEST_SAVEDATA* iow, u32 rank_code)
{
	//正当性チェック
	GF_ASSERT( correct_contest_savedata( iow ) );

	iow->rank_code = rank_code;
}

//----------------------------------------------------------------------------
/**
 *	@brief	コンテストワークのデータをコピー設定
 *
 *	@param	iow			ワーク
 *	@param	set_iow		設定ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ImcSaveData_CopyContest( IMC_CONTEST_SAVEDATA* iow, const IMC_CONTEST_SAVEDATA* set_iow )
{
	//正当性チェック
	GF_ASSERT( correct_contest_savedata( iow ) );
	memcpy( iow, set_iow, sizeof(IMC_CONTEST_SAVEDATA) );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンデータ設定
 *
 *	@param	iow		セーブデータ
 *	@param	pp		ポケモンパラメータ
 *	@param	pri		優先順位
 *	@param	x		ｘ座標
 *	@param	y		ｙ座標
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ImcSaveData_SetContestPokeData_Easy( IMC_CONTEST_SAVEDATA* iow, POKEMON_PARAM* pp, s8 pri )
{
	u8 x;
	u8 y;

	//正当性チェック
	GF_ASSERT( correct_contest_savedata( iow ) );

	// ポケモンパラメータからポケモンサイズ取得
	ImcSaveData_ImcPokeObjContestMatGet( pp, &x, &y );

	// ポケモンデータ格納
	ImcSaveData_SetPokeData_Local_Core( &iow->pokemon, pp, x, y, pri );
}

//----------------------------------------------------------------------------
/**
 *	@brief	アクセサリデータ設定
 *
 *	@param	iow			セーブワーク
 *	@param	acce_idx	アクセサリ配列インデックス
 *	@param	acce_no		アクセサリナンバー
 *	@param	x			ｘ座標
 *	@param	y			ｙ座標
 *	@param	pri			優先順位
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ImcSaveData_SetContestAcceData_Easy( IMC_CONTEST_SAVEDATA* iow, u32 acce_idx, u8 acce_no, u8 x, u8 y, s8 pri )
{
	GF_ASSERT( acce_idx < IMC_SAVEDATA_CONTEST_ACCE_NUM );		///<配列最大数チェック
	GF_ASSERT( acce_no < IMC_ACCE_MAX );		///<アクセサリ最大数チェック
	GF_ASSERT( x < 256 );		// u8に入るように
	GF_ASSERT( y < 256 );		// u8に入るように
	GF_ASSERT( pri > -128 );		// u8に入るように
	GF_ASSERT( !(iow->accessory_set_msk & (1 << acce_idx)) );	///<多重登録チェック
	//正当性チェック
	GF_ASSERT( correct_contest_savedata( iow ) );

	// アクセサリの優先順位を、強制的にポケモンよりも高くする
	if( iow->pokemon.poke_pri >= pri ){
		pri = iow->pokemon.poke_pri + 1;
	}
	
	//　データ設定
	imcsavedata_SetAcce_Local( &iow->acce[ acce_idx ],
			acce_no,
			x,
			y,
			pri);

	// マスク設定
	iow->accessory_set_msk |= 1 << acce_idx;
}

//----------------------------------------------------------------------------
/**
 *	@brief	引数のインデックスのアクセサリが登録されているかチェック
 *
 *	@param	iow		１セーブデータ
 *	@param	no		アクセサリ格納配列インデックス
 *
 *	@retval	TRUE	登録済み
 *	@retval	FALSE	未登録
 */
//-----------------------------------------------------------------------------
BOOL ImcSaveData_CheckContestAcceDataSet(const IMC_CONTEST_SAVEDATA* iow, int no)
{
	GF_ASSERT( no < IMC_SAVEDATA_CONTEST_ACCE_NUM );		///<配列最大数チェック
	//正当性チェック
	GF_ASSERT( correct_contest_savedata( iow ) );

	if( (iow->accessory_set_msk & (1 << no)) != 0 ){
		return TRUE;
	}
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	コンテスト　トレーナーデータ
 *	
 *	@param	iow		ワーク
 *	@param	pbuff	トレーナー名
 *	@param	sex		性別
 */
//-----------------------------------------------------------------------------
void ImcSaveData_SetContestTrData( IMC_CONTEST_SAVEDATA* iow, const STRBUF* pbuff, int sex )
{
	//正当性チェック
	GF_ASSERT( correct_contest_savedata( iow ) );
	ImcSaveData_SetTrData_Local( &iow->pokemon, pbuff, sex );
}

//----------------------------------------------------------------------------
/**
 *	@brief	コンテスト用ワークからポケモンセーブデータ取得
 *
 *	@param	iow		ワーク
 *
 *	@return	ポケモンセーブデータ
 */
//-----------------------------------------------------------------------------
const IMC_SAVEDATA_POKEMON* ImcSaveData_GetContestPokemon(const IMC_CONTEST_SAVEDATA* iow)
{
	//正当性チェック
	GF_ASSERT( correct_contest_savedata( iow ) );
	return &iow->pokemon;
}

//----------------------------------------------------------------------------
/**
 *	@brief	コンテストワークからアクセサリセーブデータ取得
 *
 *	@param	iow		ワーク
 *	@param	no		ワークナンバー
 *
 *	@return	アクセサリセーブデータ
 */
//-----------------------------------------------------------------------------
const IMC_SAVEDATA_ACCESSORIE* ImcSaveData_GetContestAcce(const IMC_CONTEST_SAVEDATA* iow, int no)
{
	GF_ASSERT( no < IMC_SAVEDATA_CONTEST_ACCE_NUM );		///<1データ無いアクセサリ最大数チェック
	GF_ASSERT( iow->accessory_set_msk & (1 << no) );	///<アクセサリデータ格納済みチェック
	//正当性チェック
	GF_ASSERT( correct_contest_savedata( iow ) );

	return &iow->acce[ no ];
}


//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンナンバー
 *
 *	@param	iow		イメージクリップワーク
 *
 *	@return	ポケモンナンバー
 */
//-----------------------------------------------------------------------------
u16 ImcSaveData_GetContestPokeMonsNo(const IMC_CONTEST_SAVEDATA* iow)
{
	//正当性チェック
	GF_ASSERT( correct_contest_savedata( iow ) );
	return ImcSaveData_GetUtilPokeMonsNo(&iow->pokemon);
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンニックネーム
 *
 *	@param	iow		イメージクリップワーク
 *	@param	pbuff	文字列格納バッファ　要素数　IMC_SAVEDATA_STRBUF_NUM必要
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ImcSaveData_GetContestPokeNickName(const IMC_CONTEST_SAVEDATA* iow, STRBUF* pbuff)
{
	//正当性チェック
	GF_ASSERT( correct_contest_savedata( iow ) );
	ImcSaveData_GetUtilPokeNickName(&iow->pokemon, pbuff);
}

//----------------------------------------------------------------------------
/**
 *	@brief	コンテスト用ポケモン親名前取得
 *
 *	@param	iow		イメージクリップワーク
 *	@param	pbuff	名前格納領域
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ImcSaveData_GetContestPokeOyaName(const IMC_CONTEST_SAVEDATA* iow, STRBUF* pbuff)
{
	//正当性チェック
	GF_ASSERT( correct_contest_savedata( iow ) );
	ImcSaveData_GetUtilPokeOyaName(&iow->pokemon, pbuff);
}

//----------------------------------------------------------------------------
/**
 *	@brief	親性別取得
 *
 *	@param	iow	ワーク
 *
 *	@return	親性別
 */
//-----------------------------------------------------------------------------
u32 ImcSaveData_GetContestPokeOyaSex(const IMC_CONTEST_SAVEDATA* iow)
{
	//正当性チェック
	GF_ASSERT( correct_contest_savedata( iow ) );
	return ImcSaveData_GetUtilPokeOyaSex(&iow->pokemon);
}

//----------------------------------------------------------------------------
/**
 *	@brief	コンテスト用　ポケモン固体乱数を取得
 *
 *	@param	iow		イメージクリップワーク
 *
 *	@return	固体乱数
 */
//-----------------------------------------------------------------------------
u32 ImcSaveData_GetContestPokeRnd(const IMC_CONTEST_SAVEDATA* iow)
{
	//正当性チェック
	GF_ASSERT( correct_contest_savedata( iow ) );
	return ImcSaveData_GetUtilPokeRnd( &iow->pokemon );
}

//----------------------------------------------------------------------------
/**
 *	@brief	コンテスト用　ポケモンIDNo取得
 *
 *	@param	iow		イメージクリップワーク
 *
 *	@return	ポケモンIDNo
 */
//-----------------------------------------------------------------------------
u32 ImcSaveData_GetContestPokeIDNo(const IMC_CONTEST_SAVEDATA* iow)
{
	//正当性チェック
	GF_ASSERT( correct_contest_savedata( iow ) );
	return ImcSaveData_GetUtilPokeIDNo( &iow->pokemon );
}

//----------------------------------------------------------------------------
/**
 *	@brief	コンテスト用　形状ナンバー取得
 *
 *	@param	iow		イメージクリップワーク
 *
 *	@return	形状ナンバー
 */
//-----------------------------------------------------------------------------
u32 ImcSaveData_GetContestPokeFormID(const IMC_CONTEST_SAVEDATA* iow)
{
	//正当性チェック
	GF_ASSERT( correct_contest_savedata( iow ) );
	return ImcSaveData_GetUtilPokeFormID( &iow->pokemon );
}

//----------------------------------------------------------------------------
/**
 *	@brief	コンテスト用　ポケモン表示優先順位	取得
 *
 *	@param	iow		イメージクリップワーク
 *
 *	@return	表示優先順位
 */
//-----------------------------------------------------------------------------
s8 ImcSaveData_GetContestPokePri(const IMC_CONTEST_SAVEDATA* iow)
{
	//正当性チェック
	GF_ASSERT( correct_contest_savedata( iow ) );
	return ImcSaveData_GetUtilPokePri(&iow->pokemon);
}

//----------------------------------------------------------------------------
/**
 *	@brief	コンテスト用　ポケモンｘ座標	取得
 *
 *	@param	iow		イメージクリップワーク
 *
 *	@return	ｘ座標
 */
//-----------------------------------------------------------------------------
u8 ImcSaveData_GetContestPokeX(const IMC_CONTEST_SAVEDATA* iow)
{
	//正当性チェック
	GF_ASSERT( correct_contest_savedata( iow ) );
	return ImcSaveData_GetUtilPokeX( &iow->pokemon );
}

//----------------------------------------------------------------------------
/**
 *	@brief	コンテスト用　ポケモンｙ座標	取得
 *
 *	@param	iow		イメージクリップワーク
 *
 *	@return	ｙ座標
 */
//-----------------------------------------------------------------------------
u8 ImcSaveData_GetContestPokeY(const IMC_CONTEST_SAVEDATA* iow)
{
	//正当性チェック
	GF_ASSERT( correct_contest_savedata( iow ) );
	return ImcSaveData_GetUtilPokeY( &iow->pokemon );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンパラメータを作成する
 *
 *	@param	iow		イメージクリップワーク
 *	@param	pp		ポケモンパラメータ格納先
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ImcSaveData_GetContestPokePara(const IMC_CONTEST_SAVEDATA* iow, POKEMON_PARAM* pp)
{
	//正当性チェック
	GF_ASSERT( correct_contest_savedata( iow ) );
	imcsacedata_GetPokePara_Local( &iow->pokemon, pp );
}

//----------------------------------------------------------------------------
/**
 *	@brief	コンテスト用	アクセサリナンバー取得
 *
 *	@param	iow		イメージクリップワーク
 *	@param	no		アクセサリインデックス
 *
 *	@return	アクセサリナンバー
 */
//-----------------------------------------------------------------------------
u8 ImcSaveData_GetContestAcceNo(const IMC_CONTEST_SAVEDATA* iow, int no)
{
	GF_ASSERT( no < IMC_SAVEDATA_CONTEST_ACCE_NUM );		///<1データ無いアクセサリ最大数チェック
	GF_ASSERT( iow->accessory_set_msk & (1 << no) );	///<アクセサリデータ格納済みチェック
	//正当性チェック
	GF_ASSERT( correct_contest_savedata( iow ) );

	return ImcSaveData_GetUtilAcceNo( &iow->acce[no] );
}

//----------------------------------------------------------------------------
/**
 *	@brief	コンテスト用　アクセサリｘ座標取得
 *
 *	@param	iow		イメージクリップワーク
 *	@param	no		アクセサリインデックス
 *
 *	@return	ｘ座標
 */
//-----------------------------------------------------------------------------
u8 ImcSaveData_GetContestAcceMatX(const IMC_CONTEST_SAVEDATA* iow, int no)
{
	GF_ASSERT( no < IMC_SAVEDATA_CONTEST_ACCE_NUM );		///<1データ無いアクセサリ最大数チェック
	GF_ASSERT( iow->accessory_set_msk & (1 << no) );	///<アクセサリデータ格納済みチェック
	//正当性チェック
	GF_ASSERT( correct_contest_savedata( iow ) );

	return ImcSaveData_GetUtilAcceMatX( &iow->acce[no] );
}

//----------------------------------------------------------------------------
/**
 *	@brief	コンテスト用アクセサリｙ座標取得
 *
 *	@param	iow		イメージクリップワーク
 *	@param	no		アクセサリーインデックス
 *
 *	@return	アクセサリｙ座標
 */
//-----------------------------------------------------------------------------
u8 ImcSaveData_GetContestAcceMatY(const IMC_CONTEST_SAVEDATA* iow, int no)
{
	GF_ASSERT( no < IMC_SAVEDATA_CONTEST_ACCE_NUM );		///<1データ無いアクセサリ最大数チェック
	GF_ASSERT( iow->accessory_set_msk & (1 << no) );	///<アクセサリデータ格納済みチェック
	//正当性チェック
	GF_ASSERT( correct_contest_savedata( iow ) );

	return ImcSaveData_GetUtilAcceMatY( &iow->acce[no] );
}

//----------------------------------------------------------------------------
/**
 *	@brief	コンテスト用　アクセサリ表示優先順位	取得
 *
 *	@param	iow		イメージクリップワーク
 *	@param	no		アクセサリインデックス
 *
 *	@return	表示優先順位
 */
//-----------------------------------------------------------------------------
s8 ImcSaveData_GetContestAccePri(const IMC_CONTEST_SAVEDATA* iow, int no)
{
	GF_ASSERT( no < IMC_SAVEDATA_CONTEST_ACCE_NUM );		///<1データ無いアクセサリ最大数チェック
	GF_ASSERT( iow->accessory_set_msk & (1 << no) );	///<アクセサリデータ格納済みチェック
	//正当性チェック
	GF_ASSERT( correct_contest_savedata( iow ) );

	return ImcSaveData_GetUtilAccePri( &iow->acce[no] );
}

//----------------------------------------------------------------------------
/**
 *	@brief	コンテスト用　BGID取得
 *
 *	@param	iow		イメージクリップワーク
 *
 *	@return	BGID
 */
//-----------------------------------------------------------------------------
u8 ImcSaveData_GetContestBgId(const IMC_CONTEST_SAVEDATA* iow)
{
	//正当性チェック
	GF_ASSERT( correct_contest_savedata( iow ) );
	return iow->bg_id;
}

//----------------------------------------------------------------------------
/**
 *	@brief	コンテストランクコード取得
 *
 *	@param	iow		イメージクリップワーク
 *
 *	@return	ランクコード
 */
//-----------------------------------------------------------------------------
u32 ImcSaveData_GetContestRank(const IMC_CONTEST_SAVEDATA* iow)
{
	//正当性チェック
	GF_ASSERT( correct_contest_savedata( iow ) );
	return iow->rank_code;
}



//-------------------------------------
//	ポケモンデータ取得
//=====================================
//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンモンスターナンバー取得
 *
 *	@param* iow		ワーク
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
u16 ImcSaveData_GetUtilPokeMonsNo(const IMC_SAVEDATA_POKEMON* iow)
{
	return iow->monsno;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンニックネーム取得
 *
 *	@param	iow		ワーク
 *	@param	pbuff	文字列格納バッファ　要素数　IMC_SAVEDATA_STRBUF_NUM必要
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ImcSaveData_GetUtilPokeNickName(const IMC_SAVEDATA_POKEMON* iow, STRBUF* pbuff)
{
	STRBUF_SetStringCode(pbuff, iow->nickname);
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモン親名前取得
 *
 *	@param	iow		イメージクリップワーク
 *	@param	pbuff	名前格納領域
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ImcSaveData_GetUtilPokeOyaName(const IMC_SAVEDATA_POKEMON* iow, STRBUF* pbuff)
{
	STRBUF_SetStringCode(pbuff, iow->oyaname);
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモン固体乱数を取得
 *
 *	@param	iow		ワーク
 *
 *	@return	固体乱数
 */
//-----------------------------------------------------------------------------
u32 ImcSaveData_GetUtilPokeRnd(const IMC_SAVEDATA_POKEMON* iow)
{
	return iow->personal_rnd;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンIDNo取得
 *
 *	@param	iow		ワーク	
 *
 *	@return	ポケモンIDNo
 */
//-----------------------------------------------------------------------------
u32 ImcSaveData_GetUtilPokeIDNo(const IMC_SAVEDATA_POKEMON* iow)
{
	return iow->idno;
}

//----------------------------------------------------------------------------
/**
 *	@brief	形状ナンバー取得
 *
 *	@param	iow		ワーク
 *
 *	@return	形状ナンバー
 */
//-----------------------------------------------------------------------------
u32 ImcSaveData_GetUtilPokeFormID(const IMC_SAVEDATA_POKEMON* iow)
{
	return iow->form_id;
}

//----------------------------------------------------------------------------
/**
 *	@brief	親性別取得
 *
 *	@param	iow		ワーク
 *
 *	@return	親性別
 */
//-----------------------------------------------------------------------------
u32 ImcSaveData_GetUtilPokeOyaSex(const IMC_SAVEDATA_POKEMON* iow)
{
	return iow->oya_sex;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモン表示優先順位	取得
 *
 *	@param	iow		ワーク
 *
 *	@return	表示優先順位
 */
//-----------------------------------------------------------------------------
s8 ImcSaveData_GetUtilPokePri(const IMC_SAVEDATA_POKEMON* iow)
{
	return iow->poke_pri;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンｘ座標	取得
 *
 *	@param	iow		ワーク
 *
 *	@return	ｘ座標
 */
//-----------------------------------------------------------------------------
u8 ImcSaveData_GetUtilPokeX(const IMC_SAVEDATA_POKEMON* iow)
{
	return iow->poke_x;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンｙ座標	取得
 *
 *	@param	iow		ワーク
 *
 *	@return	ｙ座標
 */
//-----------------------------------------------------------------------------
u8 ImcSaveData_GetUtilPokeY(const IMC_SAVEDATA_POKEMON* iow)
{
	return iow->poke_y;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンパラメータを作成する
 *
 *	@param	iow		イメージクリップワーク
 *	@param	pp		ポケモンパラメータ格納先
 *	
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ImcSaveData_GetUtilPokePara(const IMC_SAVEDATA_POKEMON* iow, POKEMON_PARAM* pp)
{
	imcsacedata_GetPokePara_Local( iow, pp );
}


//-------------------------------------
//	アクセサリデータ取得
//=====================================
//----------------------------------------------------------------------------
/**
 *	@brief	アクセサリナンバー取得
 *
 *	@param	iow		ワーク
 *
 *	@return	アクセサリナンバー
 */
//-----------------------------------------------------------------------------
u8 ImcSaveData_GetUtilAcceNo(const IMC_SAVEDATA_ACCESSORIE* iow)
{
	return iow->accessory_no;
}

//----------------------------------------------------------------------------
/**
 *	@brief	アクセサリX座標取得
 *
 *	@param	iow		ワーク
 *	
 *	@return	アクセサリ表示ｘ座標
 */
//-----------------------------------------------------------------------------
u8 ImcSaveData_GetUtilAcceMatX(const IMC_SAVEDATA_ACCESSORIE* iow)
{
	return iow->accessory_x;
}

//----------------------------------------------------------------------------
/**
 *	@brief	アクセサリｙ座標取得
 *
 *	@param	iow		ワーク
 *
 *	@return	アクセサリ表示ｙ座標
 */
//-----------------------------------------------------------------------------
u8 ImcSaveData_GetUtilAcceMatY(const IMC_SAVEDATA_ACCESSORIE* iow)
{
	return iow->accessory_y;
}

//----------------------------------------------------------------------------
/**
 *	@brief	アクセサリ表示優先順位取得
 *
 *	@param	iow		ワーク
 *
 *	@return	アクセサリ表示優先順位
 */
//-----------------------------------------------------------------------------
s8 ImcSaveData_GetUtilAccePri(const IMC_SAVEDATA_ACCESSORIE* iow)
{
	return iow->accessory_pri;
}

//-------------------------------------
//	レコード処理
//=====================================
// セーブするかチェック関数
static BOOL imcSaveData_RecordMixSaveCheck( IMC_SAVEDATA* iw, const IMC_TELEVISION_SAVEDATA* cp_src )
{
	int i;
	const void* cp_checkdata;
	u32 hash_0, hash_1;
	MATHCRC32Table hash_tbl;
	BOOL ret_val = TRUE;
	
	// セーブデータが格納されているワークかチェック
	if( ImcSaveData_CheckTelevisionData( cp_src ) == TRUE ){

		MATH_CRC32InitTable( &hash_tbl );
		hash_0 = MATH_CalcCRC32( &hash_tbl, cp_src, sizeof(IMC_TELEVISION_SAVEDATA) );

		// 保持しているワークの中に同じデータがないかチェック
		for( i=0; i<IMC_SAVEDATA_TELEVISION_SAVENUM; i++ ){
			cp_checkdata = ImcSaveData_GetTelevisionSaveData( iw, i );
			MATH_CRC32InitTable( &hash_tbl );
			hash_1 = MATH_CalcCRC32( &hash_tbl, cp_checkdata, sizeof(IMC_TELEVISION_SAVEDATA) );

			// ハッシュ値が一致したとき、
			// データ更新しない
			if( hash_1 == hash_0 ){
				ret_val = FALSE;
				break;
			}
		}
	}else{
		ret_val = FALSE;
	}
	return ret_val;
}


//----------------------------------------------------------------------------
/**
 *	@brief	レコード処理
 *
 *	@param	datanum		レコードデータ最大数
 *	@param	myid		自分のID
 *	@param	iw			セーブデータ
 *	@param	cpp_arry	データ配列
 */
//-----------------------------------------------------------------------------
void ImcSaveData_RecordMix( u8 datanum, int myid, IMC_SAVEDATA* iw, const void** cpp_arry )
{
	int data_num;	// 実データ数
	IMC_TELEVISION_SAVEDATA* p_dest;
	const IMC_TELEVISION_SAVEDATA* cp_src;
	int i;
	int count;
	
	// 実データ数チェック
	data_num = 0;
	for( i=0; i<datanum; i++ ){

		// 自分はパス
		if( i==myid ){
			continue;
		}
		
		if( cpp_arry[ i ] != NULL ){
			cp_src = cpp_arry[ i ];
			// データ有無
			if( imcSaveData_RecordMixSaveCheck( iw, cp_src ) == TRUE ){
				data_num ++;
			}
		}
	}

	// 押し出し式で格納していく
	// 元あったデータをdata_numづつずらす	
	for( i=IMC_SAVEDATA_TELEVISION_SAVENUM - 1; i>=IMC_SAVEDATA_TELEVISION_OTHER_S; i-- ){
		
		// 移動先のバッファがあるならコピー
		if( i+data_num < IMC_SAVEDATA_TELEVISION_SAVENUM ){
			p_dest = ImcSaveData_GetTelevisionSaveData( iw, i+data_num );
			cp_src = ImcSaveData_GetTelevisionSaveData( iw, i );
			ImcSaveData_CopyTelevision( p_dest, cp_src );
		}
	}

	// IMC_SAVEDATA_TELEVISION_OTHER_Sのセーブデータから
	// 順にデータを設定していく
	count = IMC_SAVEDATA_TELEVISION_OTHER_S;	// セーブ先バッファｶｳﾝﾀ
	for( i=0; i<datanum; i++ ){

		// 自分はパス
		if( i==myid ){
			continue;
		}
		
		if( cpp_arry[ i ] != NULL ){
			cp_src = cpp_arry[ i ];
			// データ有無
			if( imcSaveData_RecordMixSaveCheck( iw, cp_src ) == TRUE ){
				p_dest = ImcSaveData_GetTelevisionSaveData( iw, count );
				count ++;
				ImcSaveData_CopyTelevision( p_dest, cp_src );
			}
		}
	}
}



//============================================================================================
//
//	セーブデータ取得のための関数
//
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	自分状態データへのポインタ取得
 * @param	sv			セーブデータ保持ワークへのポインタ
 * @return	イメージクリップワークへのポインタ
 */
//----------------------------------------------------------
IMC_SAVEDATA * SaveData_GetImcSaveData(SAVEDATA * sv)
{
	IMC_SAVEDATA * is = NULL;
	is = SaveData_Get(sv, GMDATA_ID_IMAGECLIPDATA);
	return is;
}

//----------------------------------------------------------
//	デバッグ用
//----------------------------------------------------------
#ifdef PM_DEBUG
void Debug_ImcSaveData_Make(IMC_SAVEDATA * iw, int option)
{
	int i;
	IMC_ITEM_SAVEDATA* p_item;

	p_item = ImcSaveData_GetItemSaveData( iw );
	
	// アイテムデータを全て追加
	for( i=0; i<IMC_ACCE_MAX; i++ ){

		if( i < IMC_ACCE_GET_1_START ){
			ImcSaveData_SetAcceFlag( p_item, i, IMC_ACCE_9_GET_NUM );
		}else{
			ImcSaveData_SetAcceFlag( p_item, i, IMC_ACCE_1_GET_NUM );
		}
	}
	// BG
/*	for( i=IMC_BG_RIGHT_MAX; i>0; i-- ){
		ImcSaveData_SetBGFlag( p_item, i - 1 );
	}//*/
	for( i=0; i<IMC_BG_RIGHT_MAX; i++ ){
		ImcSaveData_SetBGFlag( p_item, i );
	}
}

void Debug_ImcSaveData_SetItemData(IMC_ITEM_SAVEDATA* iow)
{
	int i;

	// アイテムデータを全て追加
	for( i=0; i<IMC_ACCE_MAX; i++ ){

		if( i < IMC_ACCE_GET_1_START ){
			ImcSaveData_SetAcceFlag( iow, i, IMC_ACCE_9_GET_NUM );
		}else{
			ImcSaveData_SetAcceFlag( iow, i, IMC_ACCE_1_GET_NUM );
		}
	}
	// BG
/*	for( i=IMC_BG_RIGHT_MAX; i>0; i-- ){
		ImcSaveData_SetBGFlag( iow, i - 1 );
	}//*/
	for( i=0; i<IMC_BG_RIGHT_MAX; i++ ){
		ImcSaveData_SetBGFlag( iow, i );
	}
}

static void debug_PokeDataSet( IMC_SAVEDATA_POKEMON* p_poke, POKEMON_PARAM* p_pp )
{
	p_poke->monsno = PokeParaGet(p_pp, ID_PARA_monsno, NULL);
	PokeParaGet(p_pp, ID_PARA_nickname, p_poke->nickname);
	PokeParaGet(p_pp, ID_PARA_oyaname, p_poke->oyaname);
	p_poke->personal_rnd = PokeParaGet(p_pp, ID_PARA_personal_rnd, NULL );
	p_poke->idno = PokeParaGet(p_pp, ID_PARA_id_no, NULL);
	p_poke->form_id = PokeParaGet(p_pp, ID_PARA_form_no, NULL);
	p_poke->oya_sex = PokeParaGet(p_pp, ID_PARA_oyasex, NULL);
	p_poke->poke_x		= IMC_RBOX_END_SX + (IMC_RBOX_AREA_WIDTH/2);
	p_poke->poke_y		= IMC_RBOX_END_SY + (IMC_RBOX_AREA_HEIGHT/2);
	p_poke->poke_pri	= 5;
}
static void debug_AcceDataSet( IMC_SAVEDATA_ACCESSORIE* p_acce, u32 rnd )
{
	int acce_no;
	int x, y;
	int pri;

	// 出来るだけポケモンの座標にあわせる
	acce_no = (rnd * 555) % IMC_ACCE_MAX;
	x = (IMC_RBOX_END_SX + (IMC_RBOX_AREA_WIDTH/2) - 40) + ((rnd * 9) % 80);
	y = (IMC_RBOX_END_SY + (IMC_RBOX_AREA_HEIGHT/2) - 40) + ((rnd * 2) % 80);
	pri = (rnd * 15) % 20;
	imcsavedata_SetAcce_Local( p_acce, acce_no, x, y, pri );
}

void Debug_ImcSaveData_MakeTelevisionDummyData(IMC_TELEVISION_SAVEDATA* iow, POKEMON_PARAM* p_pp, u32 acce_num )
{
	int i;
	
	// 初期化
	ImcSaveData_ClaenTelevisionData( iow );

	// ポケモン登録
	debug_PokeDataSet( &iow->pokemon, p_pp );

	// アクセサリデータ設定
	for( i=0; i<acce_num; i++ ){
		debug_AcceDataSet( &iow->acce[i], iow->pokemon.personal_rnd * (i+1) );
		iow->accessory_set_msk |= 1 << i;
	}
	iow->bg_id = 0;

	// セーブ完了
	ImcSaveData_SetComplateFlagTelevisionData( iow );
}

void Debug_ImcSaveData_MakeContestDummyData(IMC_CONTEST_SAVEDATA* iow, POKEMON_PARAM* p_pp, u32 acce_num, u32 rank_code )
{
	int i;
	
	// 初期化
	ImcSaveData_ClaenContestData( iow );

	// ポケモン登録
	debug_PokeDataSet( &iow->pokemon, p_pp );

	// アクセサリデータ設定
	for( i=0; i<acce_num; i++ ){
		debug_AcceDataSet( &iow->acce[i], iow->pokemon.personal_rnd * (i+1) );
		iow->accessory_set_msk |= 1 << i;
	}

	iow->rank_code = rank_code;
	iow->bg_id = 0;

	// セーブ完了
	ImcSaveData_SetComplateFlagContestData( iow );
}


#endif

