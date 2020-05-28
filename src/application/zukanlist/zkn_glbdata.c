//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_glbdata.c
 *	@brief		図鑑グローバルデータ
 *	@author		tomoya takahashi
 *	@data		2006.01.20
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include <string.h>
#include "include/system/arc_util.h"
#include "src/application/zukanlist/zkn_data/zukan_data.naix"

#include "include/application/zukanlist/zkn_glbdata.h"
#include "include/poketool/poke_tool.h"



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
 *					定数宣言
*/
//-----------------------------------------------------------------------------
#define ZKN_SORTDATA_START_IDX	( NARC_zukan_data_zkn_sort_zenkoku_dat )
#define ZKN_SORTDATA_ONESIZE	( sizeof(u16) )
enum{
	// 大本
	ZKN_SORTDATA_ZENKOKU,
	ZKN_SORTDATA_SHINOH,
	
	// ソートﾃﾞｰﾀ
	ZKN_SORTDATA_AIUEO,
	ZKN_SORTDATA_HEAVY,
	ZKN_SORTDATA_LIGHT,
	ZKN_SORTDATA_TALL,
	ZKN_SORTDATA_SMALL,
	
	// 名前検索
	ZKN_SORTDATA_NAME_A,
	ZKN_SORTDATA_NAME_KA,
	ZKN_SORTDATA_NAME_SA,
	ZKN_SORTDATA_NAME_TA,
	ZKN_SORTDATA_NAME_NA,
	ZKN_SORTDATA_NAME_HA,
	ZKN_SORTDATA_NAME_MA,
	ZKN_SORTDATA_NAME_RA,
	ZKN_SORTDATA_NAME_YAWA,

	// タイプ検索
	ZKN_SORTDATA_TYPE_NORMAL,
	ZKN_SORTDATA_TYPE_BATTLE,	
	ZKN_SORTDATA_TYPE_HIKOU,	
	ZKN_SORTDATA_TYPE_POISON,	
	ZKN_SORTDATA_TYPE_JIMEN,	
	ZKN_SORTDATA_TYPE_IWA,		
	ZKN_SORTDATA_TYPE_MUSHI,	
	ZKN_SORTDATA_TYPE_GHOST,	
	ZKN_SORTDATA_TYPE_METAL,	
	ZKN_SORTDATA_TYPE_FIRE,	
	ZKN_SORTDATA_TYPE_WATER,	
	ZKN_SORTDATA_TYPE_KUSA,	
	ZKN_SORTDATA_TYPE_ELECTRIC,
	ZKN_SORTDATA_TYPE_SP,		
	ZKN_SORTDATA_TYPE_KOORI,	
	ZKN_SORTDATA_TYPE_DRAGON,	
	ZKN_SORTDATA_TYPE_AKU,	

	// 形検索
	ZKN_SORTDATA_FORM_FOUR_LEGS,
	ZKN_SORTDATA_FORM_TWO_LEGS,
	ZKN_SORTDATA_FORM_TAIL,
	ZKN_SORTDATA_FORM_HARABAI,
	ZKN_SORTDATA_FORM_FOUR_WING,
	ZKN_SORTDATA_FORM_TWO_WING,
	ZKN_SORTDATA_FORM_HAITSUKUBARI,
	ZKN_SORTDATA_FORM_STRAIGHT,
	ZKN_SORTDATA_FORM_ARM,
	ZKN_SORTDATA_FORM_LEGS,
	ZKN_SORTDATA_FORM_MANY_LEGS,
	ZKN_SORTDATA_FORM_WATER,
	ZKN_SORTDATA_FORM_CIRCLE,
	ZKN_SORTDATA_FORM_COMP,
	ZKN_SORTDATA_NUM
};







//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
static void ZknPokeListTblMakeSortData( u16* p_buff, int* p_count, const ZUKAN_WORK* cp_zukansave_data, const u16* cp_tbl, int num );
static void ZknPokeListTblMakeSarch( u16* p_buff, int* p_count, const u16* cp_tbl, int num, const u16* cp_sarch_tbl, int sarch_num, BOOL see_ok_flg, const ZUKAN_WORK* cp_zukansave_data );
static void ZknPokeListTblMake( ZKN_POKELIST_TBL* p_poke_list, const ZUKAN_WORK* cp_zukansave_data, const u16* cp_tbl, int tbl_num );
static void ZknPokeListDrawTblMake( ZKN_POKELIST_TBL* p_poke_list, const u16* cp_all_tbl, int all_tbl_num );
static void ZknPokeListDrawTblCopy( ZKN_POKELIST_TBL* p_poke_list );
static void ZknPokeListTblSeeGetNumCount( ZKN_POKELIST_TBL* p_poke_list, int* p_see_num, int* p_get_num );

static u16* ZKN_SORTDATA_Get( int heap, int idx, int* p_arry_num );

static void ZknPokeListSort_Core( int sort_type, u16* p_buff, int* p_count, const u16* cp_tbl, int num, int heap, const ZUKAN_WORK* cp_zukansave_data );
static void ZknPokeListSarchName_Core( int search_name, u16* p_buff, int* p_count, const u16* cp_tbl, int num, int heap, const ZUKAN_WORK* cp_zukansave_data );
static void ZknPokeListSarchType_Core( int search_type, u16* p_buff, int* p_count, const u16* cp_tbl, int num, int heap, const ZUKAN_WORK* cp_zukansave_data );
static void ZknPokeListSarchForm_Core( int search_form, u16* p_buff, int* p_count, const u16* cp_tbl, int num, int heap, const ZUKAN_WORK* cp_zukansave_data );

//-----------------------------------------------------------------------------
/**
 *	グローバル変数
 *
 */
//-----------------------------------------------------------------------------
#define ZENKOKU_POKEON_TBL_NUM	(MONSNO_END)
//----------------------------------------------------------------------------
/**
 *
 *	@brief	グローバルデータ初期化
 *
 *	@param	p_glb				グローバルデータ
 *	@param	p_init				初期化データ
 *	@param	heap				ヒープ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_GLBDATA_Init( ZKN_GLB_DATA* p_glb, ZKN_GLB_DATA_INIT* p_init, int heap )
{
	int sort_type;
	int search_name;
	int search_type1;
	int search_type2;
	int search_form;
	BOOL check;
	u32 zkn_mode;
	
	memset( p_glb, 0, sizeof(ZKN_GLB_DATA) );

	// 図鑑セーブデータ設定
	p_glb->cp_zukansave_data = p_init->cp_zukansave_data;

	// 時間帯
	p_glb->time_zone = p_init->time_zone;

	// ゼンコク図鑑保持フラグ設定
	if( ZukanWork_GetZenkokuZukanFlag( p_glb->cp_zukansave_data ) ){
		p_glb->zkn_allmap_get = TRUE;
	}else{
		p_glb->zkn_allmap_get = FALSE;
	}


	// 全国図鑑があるなら全国図鑑モードで開始
	if( p_init->zkn_mode == ZKN_MODE_NAZO ){
		// ゼンコク
		if( p_glb->zkn_allmap_get ){
			zkn_mode = ZKN_MODE_ZENKOKU;
		}else{
			zkn_mode = ZKN_MODE_SHINOH;
		}
	}else{
		zkn_mode = p_init->zkn_mode;
	}

	if( zkn_mode == ZKN_MODE_ZENKOKU ){
		p_glb->zkn_mode = ZKN_MODE_ZENKOKU;

		// ポケモンリストデータ作成
		sort_type	= ZKN_POKELIST_SORT_NORMAL;
		search_name = ZKN_POKELIST_SEARCH_NAME_NONE;
		search_type1= ZKN_POKELIST_SEARCH_TYPE_NONE;
		search_type2= ZKN_POKELIST_SEARCH_TYPE_NONE;
		search_form = ZKN_POKELIST_SEARCH_FORM_NONE;
	}else{
		// シンオウモードで開始
		p_glb->zkn_mode = ZKN_MODE_SHINOH;

		// ポケモンリストデータ作成
		sort_type	= ZKN_POKELIST_SORT_NORMAL;
		search_name = ZKN_POKELIST_SEARCH_NAME_NONE;
		search_type1= ZKN_POKELIST_SEARCH_TYPE_NONE;
		search_type2= ZKN_POKELIST_SEARCH_TYPE_NONE;
		search_form = ZKN_POKELIST_SEARCH_FORM_NONE;
	}
	// ポケモンリスト作成
	check = ZKN_GLBDATA_PokeListTblMake( p_glb, sort_type, 
			search_name, search_type1, search_type2, search_form,
			p_glb->zkn_mode, heap );
	// リスト作成結果が0個
	GF_ASSERT( check );

	// モンスターナンバーでリスト参照先を設定
	ZKN_GLBDATA_PokeListTblNoSet_Monsno( p_glb, p_init->init_list_monsno );
	ZKN_GLBDATA_PokeTextSeeSetMonsno( p_glb, p_init->init_list_monsno );
	ZKN_GLBDATA_PokeTextSeeSetZknMode( p_glb, p_init->zkn_mode );
/*
	// 見つけた数取得
	p_glb->see_num = ZukanWork_GetPokeSeeCount( p_glb->cp_zukansave_data );
	
	// 捕獲数取得
	p_glb->get_num = ZukanWork_GetPokeGetCount( p_glb->cp_zukansave_data );
//*/

	// ロムコード
	p_glb->rom_code = MyStatus_GetRomCode( p_init->cp_hero_data );

	// 主人公性別
	p_glb->hero_sex = MyStatus_GetMySex( p_init->cp_hero_data );	

	// 主人公名前
	p_glb->hero_name = MyStatus_CreateNameString( p_init->cp_hero_data, heap );

	// 高さ重さデータ取得
	p_glb->height_gram = ZKN_HEIGHTGRAM_Alloc( heap );
	// 男か女かチェック
	if( p_glb->hero_sex == 0 ){
		ZKN_HEIGHTGRAM_Load( p_glb->height_gram, ZKN_HEIGHT_GRAM_TYPE_MAN, heap );
	}else{
		ZKN_HEIGHTGRAM_Load( p_glb->height_gram, ZKN_HEIGHT_GRAM_TYPE_GIRL, heap );
	}

	// 隠しマップ
	p_glb->hidemap_id_D15 = p_init->hidemap_id_D15;
	p_glb->hidemap_id_D30 = p_init->hidemap_id_D30;
	p_glb->hidemap_id_L04 = p_init->hidemap_id_L04;
	p_glb->hidemap_id_D18 = p_init->hidemap_id_D18;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	グローバルデータ破棄
 *
 *	@param	p_glb	グローバルデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void ZKN_GLBDATA_Delete( ZKN_GLB_DATA* p_glb )
{

	// 主人公名
	STRBUF_Delete( p_glb->hero_name );
	
	// 高さデータ
	ZKN_HEIGHTGRAM_Release( p_glb->height_gram );
	ZKN_HEIGHTGRAM_Free( p_glb->height_gram );
	p_glb->height_gram = NULL;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンナンバーのポケモンを表示する性別を取得
 *
 *	@param	cp_glb		グローバルデータ
 *	@param	monsno		モンスターナンバー
 *	@param	count		ZUKAN_WORK_SEX_FIRST　ZUKAN_WORK_SEX_SECOND
 *
 *	@retval	PARA_MALE		オス
 *	@retval	PARA_FEMALE		メス
 *	@retval	PARA_UNK		不明
 */
//-----------------------------------------------------------------------------
u32 ZKN_GLBDATA_SaveData_SexGet( const ZKN_GLB_DATA* cp_glb, int monsno, int count )
{
	u32 sex;
	sex = ZukanWork_GetPokeSexFlag( cp_glb->cp_zukansave_data, monsno, count );
	return sex;
}

//----------------------------------------------------------------------------
/**
 *	@brief	アンノーンフォームの取得
 *
 *	@param	cp_glb		グローバルデータ
 *	@param	count		(0～27)
 *
 *	@return	フォルムナンバー
 */
//-----------------------------------------------------------------------------
u32 ZKN_GLBDATA_SaveData_AnoonFormGet( const ZKN_GLB_DATA* cp_glb, int count )
{
	int form;
	GF_ASSERT( count < 28 );

	form = ZukanWork_GetPokeAnoonForm( cp_glb->cp_zukansave_data, count );

	return form;
}

//----------------------------------------------------------------------------
/**
 *	@brief	シーウシ　フォルム取得
 *
 *	@param	cp_glb	グローバルデータ
 *	@param	count	順番	0or1
 *
 *	@return	フォルム
 */
//-----------------------------------------------------------------------------
u32 ZKN_GLBDATA_SaveData_SiiusiFormGet( const ZKN_GLB_DATA* cp_glb, int count )
{
	u32 form;
	GF_ASSERT( count < 2 );
	
	form = ZukanWork_GetPokeSiiusiForm( cp_glb->cp_zukansave_data, count );
	return form;
}

//----------------------------------------------------------------------------
/**
 *	@brief	シードルゴ
 *
 *	@param	cp_glb	グローバルデータ
 *	@param	count	順番	0or1
 *
 *	@return	フォルム
 */
//-----------------------------------------------------------------------------
u32 ZKN_GLBDATA_SaveData_SiidorugoFormGet( const ZKN_GLB_DATA* cp_glb, int count )
{
	u32 form;
	GF_ASSERT( count < 2 );
	
	form = ZukanWork_GetPokeSiidorugoForm( cp_glb->cp_zukansave_data, count );
	return form;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ミノムッチ
 *
 *	@param	cp_glb	グローバルデータ
 *	@param	count	順番	0or1or2
 *
 *	@return	フォルム
 */
//-----------------------------------------------------------------------------
u32 ZKN_GLBDATA_SaveData_MinomuttiFormGet( const ZKN_GLB_DATA* cp_glb, int count )
{
	u32 form;
	GF_ASSERT( count < 3 );
	
	form = ZukanWork_GetPokeMinomuttiForm( cp_glb->cp_zukansave_data, count );
	return form;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ミノメス
 *
 *	@param	cp_glb	グローバルデータ
 *	@param	count	順番	0or1or2
 *
 *	@return	フォルム
 */
//-----------------------------------------------------------------------------
u32 ZKN_GLBDATA_SaveData_MinomesuFormGet( const ZKN_GLB_DATA* cp_glb, int count )
{
	u32 form;
	GF_ASSERT( count < 3 );
	
	form = ZukanWork_GetPokeMinomesuForm( cp_glb->cp_zukansave_data, count );
	return form;
}

//----------------------------------------------------------------------------
/**
 *	@brief	最初に見た形状を返す
 *
 *	@param	cp_glb	グローバルデータ
 *	@param	monsno	モンスターナンバー
 */
//-----------------------------------------------------------------------------
u32 ZKN_GLBDATA_SaveData_FirstFormGet( const ZKN_GLB_DATA* cp_glb, u32 monsno )
{
	u32 form;
	
	switch( monsno ){
	case MONSNO_ANNOON:
		form = ZKN_GLBDATA_SaveData_AnoonFormGet( cp_glb, 0 );
		break;

	case MONSNO_SIIUSI:
		form = ZKN_GLBDATA_SaveData_SiiusiFormGet( cp_glb, 0 );
		break;
		
	case MONSNO_SIIDORUGO:
		form = ZKN_GLBDATA_SaveData_SiidorugoFormGet( cp_glb, 0 );
		break;
		
	case MONSNO_MINOMUTTI:
		form = ZKN_GLBDATA_SaveData_MinomuttiFormGet( cp_glb, 0 );
		break;
		
	case MONSNO_MINOMESU:
		form = ZKN_GLBDATA_SaveData_MinomesuFormGet( cp_glb, 0 );
		break;

	case MONSNO_DEOKISISU:
		form = ZKN_GLBDATA_SaveData_DeokisisuFormGet( cp_glb, 0 );
		break;
		
	default:
		form = 0;	
		break;
	}

	return form;
}


//----------------------------------------------------------------------------
/**	
 *	@brief	見た性別の数を取得
 *
 *	@param	cp_glb	描画グローバル
 *	@param	monsno	モンスターナンバー
 *
 *	@return	見た性別の数
 */
//-----------------------------------------------------------------------------
u32 ZKN_GLBDATA_SaveData_SexNumGet( const ZKN_GLB_DATA* cp_glb, int monsno )
{
	int sex = ZKN_GLBDATA_SaveData_SexGet( cp_glb, monsno, ZUKAN_WORK_SEX_SECOND );
	
	
	// 2つ目の性別をみたかチェック
	if( sex == ZUKAN_WORK_GET_SEX_ERR ){
		return 1;
	}

	return 2;
}

//----------------------------------------------------------------------------
/**
 *	@brief	アンノーンの種類を見つけた数取得
 *
 *	@param	cp_glb	グローバル
 *
 *	@return	見つけた数
 */
//-----------------------------------------------------------------------------
u32 ZKN_GLBDATA_SaveData_AnoonNumGet( const ZKN_GLB_DATA* cp_glb )
{
	return ZukanWork_GetPokeAnoonSeeNum( cp_glb->cp_zukansave_data );
}

//----------------------------------------------------------------------------
/**
 *	@brief	シーウシ　種類取得
 */
//-----------------------------------------------------------------------------
u32 ZKN_GLBDATA_SaveData_SiiusiNumGet( const ZKN_GLB_DATA* cp_glb )
{
	return ZukanWork_GetPokeSiiusiSeeNum( cp_glb->cp_zukansave_data );
}

//----------------------------------------------------------------------------
/**
 *	@brief	シードルゴ　種類取得
 */
//-----------------------------------------------------------------------------
u32 ZKN_GLBDATA_SaveData_SiidorugoNumGet( const ZKN_GLB_DATA* cp_glb )
{
	return ZukanWork_GetPokeSiidorugoSeeNum( cp_glb->cp_zukansave_data );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ミノムッチ　種類取得
 */
//-----------------------------------------------------------------------------
u32 ZKN_GLBDATA_SaveData_MinomuttiNumGet( const ZKN_GLB_DATA* cp_glb )
{
	return ZukanWork_GetPokeMinomuttiSeeNum( cp_glb->cp_zukansave_data );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ミノメス　種類取得
 */
//-----------------------------------------------------------------------------
u32 ZKN_GLBDATA_SaveData_MinomesuNumGet( const ZKN_GLB_DATA* cp_glb )
{
	return ZukanWork_GetPokeMinomesuSeeNum( cp_glb->cp_zukansave_data );
}

//----------------------------------------------------------------------------
/**
 *	@brief	パッチール固体乱数取得
 *
 *	@param	cp_glb	グローバルワーク
 *
 *	@return	固体乱数
 */
//-----------------------------------------------------------------------------
u32 ZKN_GLBDATA_SaveData_PattiruRndGet( const ZKN_GLB_DATA* cp_glb )
{
	return ZukanWork_GetPokeRandomFlag( cp_glb->cp_zukansave_data, ZUKAN_WORK_RANDOM_PACHI );
}

//----------------------------------------------------------------------------
/**
 *	@brief	デオキシスフォルム取得
 *
 *	@param	cp_glb	グローバルデータ
 *
 *	@return	フォルムナンバー
 */
//-----------------------------------------------------------------------------
u32 ZKN_GLBDATA_SaveData_DeokisisuFormGet( const ZKN_GLB_DATA* cp_glb, int count )
{
	return ZukanWork_GetPokeDeokisisuForm( cp_glb->cp_zukansave_data, count );
}

//----------------------------------------------------------------------------
/**
 *	@brief	デオキシス形状見た数取得
 *
 *	@param	cp_glb	グローバルデータ
 *
 *	@return	デオキシス形状見た数
 */
//-----------------------------------------------------------------------------
u32 ZKN_GLBDATA_SaveData_DeokisisuFormSeeNumGet( const ZKN_GLB_DATA* cp_glb )
{
	return ZukanWork_GetPokeDeokisisuFormSeeNum( cp_glb->cp_zukansave_data );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ゼンコク図鑑完成しているかチェック
 * 
 *	@param	cp_glb	ワーク
 *
 *	@retval	TRUE	完成
 *	@retval	FALSE	未完成
 */
//-----------------------------------------------------------------------------
BOOL ZKN_GLBDATA_SaveData_ZenkokuZukanComp( const ZKN_GLB_DATA* cp_glb )
{
	return ZukanWork_CheckZenkokuComp( cp_glb->cp_zukansave_data );
}

//----------------------------------------------------------------------------
/**
 *	@brief	ゼンコク図鑑取得しているかチェック
 * 
 *	@param	cp_glb	ワーク
 *
 *	@retval	TRUE	取得
 *	@retval	FALSE	未取得
 */
//-----------------------------------------------------------------------------
BOOL ZKN_GLBDATA_SaveData_ZenkokuZukanGet( const ZKN_GLB_DATA* cp_glb )
{
	return ZukanWork_GetZenkokuZukanFlag( cp_glb->cp_zukansave_data );
}



//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンテキスト見たフラグ
 *
 *	@param	p_glb		グローバルデータ
 *	@param	monsno		モンスターナンバー
 */
//-----------------------------------------------------------------------------
void ZKN_GLBDATA_PokeTextSeeSetMonsno( ZKN_GLB_DATA* p_glb, u32 monsno )
{
	p_glb->last_see_monsno = monsno;
}

//----------------------------------------------------------------------------
/**
 *	@brief	最後に見たポケモンナンバー取得
 *
 *	@param	cp_glb	グローバルデータ
 */
//-----------------------------------------------------------------------------
u32 ZKN_GLBDATA_PokeTextSeeGetMonsno( const ZKN_GLB_DATA* cp_glb )
{
	return cp_glb->last_see_monsno;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンテキスト見たフラグ
 *
 *	@param	p_glb		グローバルデータ
 *	@param	zkn_mode	図鑑ﾓｰﾄﾞ
 */
//-----------------------------------------------------------------------------
void ZKN_GLBDATA_PokeTextSeeSetZknMode( ZKN_GLB_DATA* p_glb, u32 zkn_mode )
{
	p_glb->last_see_zkn_mode = zkn_mode;
}

//----------------------------------------------------------------------------
/**
 *	@brief	最後に見たポケモンナンバー取得
 *
 *	@param	cp_glb	グローバルデータ
 */
//-----------------------------------------------------------------------------
u32 ZKN_GLBDATA_PokeTextSeeGetZknMode( const ZKN_GLB_DATA* cp_glb )
{
	return cp_glb->last_see_zkn_mode;
}



//----------------------------------------------------------------------------
/**
 *	@brief	グラフィックバージョンフラグ取得
 *
 *	@param	cp_glb	グローバル
 *
 *	@retval	TRUE	バージョンアップ完了
 *	@retval	FALSE	バージョンアップ未完了
 */
//-----------------------------------------------------------------------------
BOOL ZKN_GLBDATA_SaveData_GraModeGet( const ZKN_GLB_DATA* cp_glb )
{
	return ZukanWork_GetGraphicVersionUpFlag( cp_glb->cp_zukansave_data );
}

//----------------------------------------------------------------------------
/**
 *	@brief	言語バージョンフラグ取得
 *
 *	@param	cp_glb		グローバル
 *	@param	country		国コード 
 *
 *	@retval	TRUE	バージョンアップ完了
 *	@retval	FALSE	バージョンアップ未完了
 */
//-----------------------------------------------------------------------------
BOOL ZKN_GLBDATA_SaveData_TextModeGet( const ZKN_GLB_DATA* cp_glb, int country )
{
//	return ZukanWork_GetTextVersionUpFlag( cp_glb->cp_zukansave_data, country );
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ポケモンリストテーブルの作成
 *
 *	@param	p_glb			グローバルデータ
 *	@param	sort_type		ソートタイプ
 *	@param	search_name		名前サーチ
 *	@param	search_type1	タイプサーチ
 *	@param	search_type2	タイプサーチ
 *	@param	search_form		フォームサーチ
 *	@param	shinoh			シンオウ図鑑ならTRUE
 *	@param	heap			使用ヒープ
 *	@param	dummy_list_cut	ダミーリストカットフラグ
 *	
 *	@retval	TRUE	作成成功
 *	@retval	FALSE	作成結果リストが０個
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL ZKN_GLBDATA_PokeListTblMake_DummyListCutFlg( ZKN_GLB_DATA* p_glb, int sort_type, int search_name, int search_type1, int search_type2, int search_form, int shinoh, int heap, BOOL dummy_list_cut )
{
	u16* p_buff0;	// 検索元ﾃﾞｰﾀ用テーブルバッファ
	int count0;
	u16* p_buff1;	// 検索結果受け取り用テーブルバッファ
	int count1;
	u16* p_all_list_data;	// ｿｰﾄ前全ﾎﾟｹﾓﾝﾘｽﾄﾃﾞｰﾀ
	int all_list_data_count;
	BOOL ret;

	// バッファ領域を確保
	p_buff0 = sys_AllocMemoryLo( heap, sizeof(u16) * POKEMON_LIST_TBL_NUM );
	GF_ASSERT( p_buff0 );
	memset( p_buff0, 0, sizeof(u16) * POKEMON_LIST_TBL_NUM );
	count0 = 0;
	p_buff1 = sys_AllocMemoryLo( heap, sizeof(u16) * POKEMON_LIST_TBL_NUM );
	GF_ASSERT( p_buff1 );
	memset( p_buff1, 0, sizeof(u16) * POKEMON_LIST_TBL_NUM );
	count1 = 0;

	// ポケモンデータをシンオウテーブルから持ってくるのか
	// 全国図鑑からもってくるのか
	if( shinoh == ZKN_MODE_SHINOH ){
		// シンオウ
		p_all_list_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_SHINOH, &all_list_data_count );
		ZknPokeListTblMakeSortData( p_buff0, &count0, p_glb->cp_zukansave_data, p_all_list_data, all_list_data_count );
	}else{
		// 全国
		p_all_list_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_ZENKOKU, &all_list_data_count );
		ZknPokeListTblMakeSortData( p_buff0, &count0, p_glb->cp_zukansave_data, p_all_list_data, all_list_data_count );
	}
	
	// ｿｰﾄ
	ZknPokeListSort_Core( sort_type, p_buff1, &count1, p_buff0, count0, heap, p_glb->cp_zukansave_data );
	memcpy( p_buff0, p_buff1, sizeof(u16) * count1 );	// データコピー
	count0 = count1;
	memset( p_buff1, 0, sizeof(u16) * count1 );
	count1 = 0;
	
	// 検索処理
	do{
		// なまえけんさく
		ZknPokeListSarchName_Core( search_name, p_buff1, &count1, p_buff0, count0, heap, p_glb->cp_zukansave_data );
		if( count1 == 0 ){
			ret = FALSE;
			break;
		}
		memcpy( p_buff0, p_buff1, sizeof(u16) * count1 );	// データコピー
		count0 = count1;
		memset( p_buff1, 0, sizeof(u16) * count1 );
		count1 = 0;

		// タイプ
		ZknPokeListSarchType_Core( search_type1, p_buff1, &count1, p_buff0, count0, heap, p_glb->cp_zukansave_data );
		if( count1 == 0 ){
			ret = FALSE;
			break;
		}
		memcpy( p_buff0, p_buff1, sizeof(u16) * count1 );	// データコピー
		count0 = count1;
		memset( p_buff1, 0, sizeof(u16) * count1 );
		count1 = 0;

		// ﾀｲﾌﾟ2
		ZknPokeListSarchType_Core( search_type2, p_buff1, &count1, p_buff0, count0, heap, p_glb->cp_zukansave_data );
		if( count1 == 0 ){
			ret = FALSE;
			break;
		}
		memcpy( p_buff0, p_buff1, sizeof(u16) * count1 );	// データコピー
		count0 = count1;
		memset( p_buff1, 0, sizeof(u16) * count1 );
		count1 = 0;

		// かたち
		ZknPokeListSarchForm_Core( search_form, p_buff1, &count1, p_buff0, count0, heap, p_glb->cp_zukansave_data );
		if( count1 == 0 ){
			ret = FALSE;
			break;
		}
		memcpy( p_buff0, p_buff1, sizeof(u16) * count1 );	// データコピー
		count0 = count1;
		memset( p_buff1, 0, sizeof(u16) * count1 );
		count1 = 0;


		// ﾃﾞｰﾀがあったらリスト作成
		// ポケモンリストデータ作成
		ZknPokeListTblMake( &p_glb->poke_list, p_glb->cp_zukansave_data, p_buff0, count0 );

		// 検索ソートがかかったときはコピーするのみ
		// モンスターナンバーでリスト作成したときはモンスターナンバーで描画リストを作成する
		if( ((sort_type != ZKN_POKELIST_SORT_NORMAL) ||
			(search_name != ZKN_POKELIST_SEARCH_NAME_NONE) ||
			(search_type1 != ZKN_POKELIST_SEARCH_TYPE_NONE) ||
			(search_type2 != ZKN_POKELIST_SEARCH_TYPE_NONE) ||
			(search_form != ZKN_POKELIST_SEARCH_FORM_NONE)) ){
			dummy_list_cut = TRUE;
		}

		if( dummy_list_cut == FALSE ){
			ZknPokeListDrawTblMake( &p_glb->poke_list, p_all_list_data, all_list_data_count );
		}else{
			ZknPokeListDrawTblCopy( &p_glb->poke_list );
		}
		ret = TRUE;
	}while(0);
	

	// みつけたかず　捕まえた数計算
	ZknPokeListTblSeeGetNumCount( &p_glb->poke_list, &p_glb->see_num, &p_glb->get_num );
	

	// バッファ破棄
	sys_FreeMemoryEz( p_buff0 );
	sys_FreeMemoryEz( p_buff1 );
	sys_FreeMemoryEz( p_all_list_data );

	return ret;
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	ポケモンリストテーブルの作成
 *
 *	@param	p_glb			グローバルデータ
 *	@param	sort_type		ソートタイプ
 *	@param	search_name		名前サーチ
 *	@param	search_type1	タイプサーチ
 *	@param	search_type2	タイプサーチ
 *	@param	search_form		フォームサーチ
 *	@param	shinoh			シンオウ図鑑ならTRUE
 *	@param	heap			使用ヒープ
 *	@param	dummy_list_cut	ダミーリストカットフラグ
 *	
 *	@retval	TRUE	作成成功
 *	@retval	FALSE	作成結果リストが０個
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL ZKN_GLBDATA_PokeListTblMake( ZKN_GLB_DATA* p_glb, int sort_type, int search_name, int search_type1, int search_type2, int search_form, int shinoh, int heap )
{
	return ZKN_GLBDATA_PokeListTblMake_DummyListCutFlg( p_glb, sort_type, search_name, search_type1, search_type2, search_form, shinoh, heap, FALSE );
}


//----------------------------------------------------------------------------
/**
 *	@brief	全国図鑑モードに変更できるかチェック
 *
 *	@param	cp_glb		グローバルデータ
 *	@param	zkn_mode	変更する図鑑モード
 *
 *	@retval	TRUE	出来る
 *	@retval FALSE	出来ない
 */
//-----------------------------------------------------------------------------
BOOL ZKN_GLBDATA_PokeZknModeChengeCheck( const ZKN_GLB_DATA* cp_glb, int zkn_mode )
{
	// シンオウ図鑑は無条件
	if( zkn_mode == ZKN_MODE_SHINOH ){
		return TRUE;
	}

	// 全国は全国図鑑を持っていたらOK
	if( cp_glb->zkn_allmap_get ){
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	図鑑モード変更
 *
 *	@param	p_glb		グローバルデータ
 *	@param	zkn_mode	図鑑モード
 *
 *	@retval	TRUE		変更できた
 *	@retval	FALSE		変更できなかった
 */
//-----------------------------------------------------------------------------
BOOL ZKN_GLBDATA_PokeZknModeChenge( ZKN_GLB_DATA* p_glb, int zkn_mode )
{
	BOOL check;

	check = ZKN_GLBDATA_PokeZknModeChengeCheck( p_glb, zkn_mode );

	if( check ){
		p_glb->zkn_mode = zkn_mode;
	}


	return check;
}

//----------------------------------------------------------------------------
/**
 *	@brief	図鑑モードを取得
 *
 *	@param	cp_glb	グローバルデータ
 *
 *	@return	図鑑モード
 */
//-----------------------------------------------------------------------------
int ZKN_GLBDATA_PokeZknModeGet( const ZKN_GLB_DATA* cp_glb )
{
	return cp_glb->zkn_mode;
}

//----------------------------------------------------------------------------
/**	
 *	@brief	ポケモンリストテーブルナンバー設定可能ﾁｪｯｸ
 *
 *	@param	cp_glb		グローバルデータ
 *	@param	no			チェックナンバー
 *
 *	@retval	TRUE	設定可能
 *	@retval	FALSE	設定不可能
 */
//-----------------------------------------------------------------------------
BOOL ZKN_GLBDATA_PokeListTblNoSetCheck( const ZKN_GLB_DATA* cp_glb, int no )
{
	// 設定可能かチェック
	if( ((no) >= 0) &&
		((no) < cp_glb->poke_list.tbl_poke_num) ){
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンリストテーブルナンバー設定
 *
 *	@param	p_glb		グローバルデータ
 *	@param	no			設定ナンバー
 *
 *	@retval	TRUE	設定成功
 *	@retval	FALSE	設定失敗	（値が不正）
 */
//-----------------------------------------------------------------------------
BOOL ZKN_GLBDATA_PokeListTblNoSet( ZKN_GLB_DATA* p_glb, int no )
{
	// 設定可能かチェック
	if( ZKN_GLBDATA_PokeListTblNoSetCheck( p_glb, no ) ){
		p_glb->poke_list.tbl_no = no;
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	足し算
 *
 *	@param	p_glb	グローバルデータ
 *	@param	no		足す値
 *
 *	@retval	TRUE	設定成功
 *	@retval	FALSE	設定失敗		0か最大数になっています
 */
//-----------------------------------------------------------------------------
BOOL ZKN_GLBDATA_PokeListTblNoAdd( ZKN_GLB_DATA* p_glb, int no )
{
	if( ZKN_GLBDATA_PokeListTblNoSetCheck( p_glb, p_glb->poke_list.tbl_no + no ) ){
		p_glb->poke_list.tbl_no += no;
		return TRUE;
	}

	if( no >= 0 ){
		p_glb->poke_list.tbl_no = p_glb->poke_list.tbl_poke_num - 1;
	}else{
		p_glb->poke_list.tbl_no = 0;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	テーブルナンバー取得
 *
 *	@param	cp_glb	グローバルデータ
 *
 *	@return	現在のテーブルナンバー
 */
//-----------------------------------------------------------------------------
int ZKN_GLBDATA_PokeListTblNoGet( const ZKN_GLB_DATA* cp_glb )
{
	return cp_glb->poke_list.tbl_no;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンリストテーブル数取得
 *
 *	@param	cp_glb	グローバルデータ
 *
 *	@return	テーブル数
 */
//-----------------------------------------------------------------------------
int ZKN_GLBDATA_PokeListTblNumGet( const ZKN_GLB_DATA* cp_glb )
{
	return cp_glb->poke_list.tbl_poke_num;
}

//----------------------------------------------------------------------------
/**
 *	@brief	モンスターナンバーからリストテーブルナンバーを取得
 *
 *	@param	cp_glb	グローバルデータ
 *	@param	monsno	モンスターナンバー
 *
 *	@return	テーブルナンバー  テーブル最大数のときは、無かったとき
 */
//-----------------------------------------------------------------------------
int ZKN_GLBDATA_PokeListTblNoGet_Monsno( const ZKN_GLB_DATA* cp_glb, u32 monsno )
{
	int i;
	int tbl_num = ZKN_GLBDATA_PokeListTblNumGet( cp_glb );
	int tbl_mons;

	for( i=0; i<tbl_num; i++ ){
		tbl_mons = cp_glb->poke_list.zkn_pokelist_tbl[ i ].mons_no;
		if( tbl_mons == monsno ){
			break;
		}
	}
	return i;
}

//----------------------------------------------------------------------------
/**
 *	@brief	モンスターナンバーに対応したリストを設定する
 *
 *	@param	p_glb	グローバルデータ
 *	@param	monsno	ﾓﾝｽﾀｰﾅﾝﾊﾞｰ
 *
 *	@retval	TRUE		設定成功
 *	@retval	FALSE		設定失敗
 */	
//-----------------------------------------------------------------------------
BOOL ZKN_GLBDATA_PokeListTblNoSet_Monsno( ZKN_GLB_DATA* p_glb, int monsno )
{
	u32 tbl_num = ZKN_GLBDATA_PokeListTblNumGet( p_glb );
	u32 tbl_no	= ZKN_GLBDATA_PokeListTblNoGet_Monsno( p_glb, monsno );

	if( tbl_num > tbl_no ){
		return ZKN_GLBDATA_PokeListTblNoSet( p_glb, tbl_no );
	}
	return FALSE;
}


//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンナンバー取得
 *
 *	@param	cp_glb	グローバルデータ
 *
 *	@return	ポケモンナンバー
 */
//-----------------------------------------------------------------------------
int ZKN_GLBDATA_PokeMonsNoGet( const ZKN_GLB_DATA* cp_glb )
{
	return cp_glb->poke_list.zkn_pokelist_tbl[ cp_glb->poke_list.tbl_no ].mons_no;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモン　捕獲　発見タイプ取得
 *
 *	@param	cp_glb	グローバルデータ
 *
 *	@retval	ZKN_POKELIST_TYPE_NONE,	// わからない
 *	@retval ZKN_POKELIST_TYPE_SEE,	// 見つけた
 *	@retval	ZKN_POKELIST_TYPE_GET,	// 捕まえた
 */
//-----------------------------------------------------------------------------
int ZKN_GLBDATA_PokeMonsTypeGet( const ZKN_GLB_DATA* cp_glb )
{
	return cp_glb->poke_list.zkn_pokelist_tbl[ cp_glb->poke_list.tbl_no ].type;
}


//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンリストテーブル取得
 *
 *	@param	cp_glb		グローバルデータ
 *	@param	tbl_no		テーーブルナンバー
 *
 *	@return	テーブルポインタ
 */
//-----------------------------------------------------------------------------
const ZKN_POKELIST_DATA* ZKN_GLBDATA_PokeListTblGet( const ZKN_GLB_DATA* cp_glb, int tbl_no )
{
	//取得可能かﾁｪｯｸ 
	if( ZKN_GLBDATA_PokeListTblNoSetCheck( cp_glb, tbl_no ) ){
		return &cp_glb->poke_list.zkn_pokelist_tbl[ tbl_no ];
	}

	return NULL;
}

//----------------------------------------------------------------------------
/**
 *	@brief	描画ポケモンリストのテーブルナンバー設定チェック
 *
 *	@param	cp_glb	グローバルデータ
 *	@param	no		設定ナンバー
 *
 *	@retval	TRUE 成功
 *	@retval	FALSE 失敗
 */
//-----------------------------------------------------------------------------
BOOL ZKN_GLBDATA_PokeListDrawTblNoSetCheck( const ZKN_GLB_DATA* cp_glb, int no )
{
	if( (cp_glb->poke_list.draw_tbl_poke_num > no) && (no >= 0) ){
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	描画ポケモンリストナンバー設定
 *
 *	@param	p_glb	グローバル
 *	@param	no		ポケモンリストテーブルナンバー
 *	
 *	@retval	TRUE 成功
 *	@retval	FALSE 失敗
 */
//-----------------------------------------------------------------------------
BOOL ZKN_GLBDATA_PokeListDrawTblNoSet( ZKN_GLB_DATA* p_glb, int no )
{
	if( ZKN_GLBDATA_PokeListDrawTblNoSetCheck( p_glb, no ) ){
		p_glb->poke_list.draw_tbl_no = no;

		// ポケモンリストにも反映
		ZKN_GLBDATA_PokeListTblNoSet( p_glb, p_glb->poke_list.zkn_pokelistdraw_tbl[ p_glb->poke_list.draw_tbl_no ] );
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	描画ポケモンリストナンバー足し算
 *
 *	@param	p_glb
 *	@param	no 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
BOOL ZKN_GLBDATA_PokeListDrawTblNoAdd( ZKN_GLB_DATA* p_glb, int no )
{
	if( ZKN_GLBDATA_PokeListDrawTblNoAddCheck( p_glb, no ) ){
		p_glb->poke_list.draw_tbl_no += no;

		// ポケモンリストにも反映
		ZKN_GLBDATA_PokeListTblNoSet( p_glb, p_glb->poke_list.zkn_pokelistdraw_tbl[ p_glb->poke_list.draw_tbl_no ] );
		return TRUE;
	}

	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	足し算できるかチェック
 *
 *	@param	p_glb
 *	@param	no 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
BOOL ZKN_GLBDATA_PokeListDrawTblNoAddCheck( ZKN_GLB_DATA* p_glb, int no )
{
	if( ZKN_GLBDATA_PokeListDrawTblNoSetCheck( p_glb, p_glb->poke_list.draw_tbl_no + no ) ){
		return TRUE;
	}
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 *	@brief	描画テーブルナンバー取得
 *
 *	@param	cp_glb	現在描画グローバルナンバー設定
 *
 *	@return	
 */
//-----------------------------------------------------------------------------
int ZKN_GLBDATA_PokeListDrawTblNoGet( const ZKN_GLB_DATA* cp_glb )
{
	return cp_glb->poke_list.draw_tbl_no;
}

//----------------------------------------------------------------------------
/**
 *	@brief	描画テーブル数取得
 *
 *	@param	cp_glb 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
int ZKN_GLBDATA_PokeListDrawTblNumGet( const ZKN_GLB_DATA* cp_glb )
{
	return cp_glb->poke_list.draw_tbl_poke_num;
}

//----------------------------------------------------------------------------
/**
 *	@brief	表示データテーブルナンバー取得
 *
 *	@param	cp_glb
 *	@param	no 
 *
 *	@return
 */
//-----------------------------------------------------------------------------
int ZKN_GLBDATA_PokeListDrawTblDataGet( const ZKN_GLB_DATA* cp_glb, int no )
{
	return cp_glb->poke_list.zkn_pokelistdraw_tbl[ no ];
}

//----------------------------------------------------------------------------
/**
 *	@brief	今のポケリスト選択位置に描画リスト位置を合わせる
 *
 *	@param	cp_glb	グローバル
 *
 *	@return
 */
//-----------------------------------------------------------------------------
void ZKN_GLBDATA_PokeListDrawTblSetNowTblNo( ZKN_GLB_DATA* p_glb )
{
	int i;

	for( i=0; i<p_glb->poke_list.draw_tbl_poke_num; i++ ){

		if( ZKN_GLBDATA_PokeListDrawTblDataGet( p_glb, i ) == ZKN_GLBDATA_PokeListTblNoGet( p_glb ) ){
			
			ZKN_GLBDATA_PokeListDrawTblNoSet( p_glb, i );
			break;
		}
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	ポケモン発見数取得
 *
 *	@param	cp_glb	グローバルデータ
 *
 *	@return	発見数
 */
//-----------------------------------------------------------------------------
int ZKN_GLBDATA_PokeSeeNumGet( const ZKN_GLB_DATA* cp_glb )
{
	return cp_glb->see_num;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモン捕獲数取得
 *
 *	@param	cp_glb	グローバルデータ」
 *
 *	@return	捕獲数
 */
//-----------------------------------------------------------------------------
int ZKN_GLBDATA_PokeGetNumGet( const ZKN_GLB_DATA* cp_glb )
{
	return cp_glb->get_num;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ロム種類
 *
 *	@param	cp_glb	グローバルデータ
 *
 *	@return	0ダイヤ 1パール
 */
//-----------------------------------------------------------------------------
int ZKN_GLBDATA_RomDataGet( const ZKN_GLB_DATA* cp_glb )
{
	return cp_glb->rom_code;
}

//----------------------------------------------------------------------------
/**
 *	@brief	主人公名
 *
 *	@param	cp_glb	グローバルデータ
 *
 *	@return	主人公名
 */
//-----------------------------------------------------------------------------
STRBUF* ZKN_GLBDATA_HeroNameGet( const ZKN_GLB_DATA* cp_glb )
{
	return cp_glb->hero_name;
}

//----------------------------------------------------------------------------
/**
 *	@brief	主人公性別
 *
 *	@param	cp_glb	グローバルデータ
 *
 *	@return	性別
 */
//-----------------------------------------------------------------------------
u32 ZKN_GLBDATA_HeroSexGet( const ZKN_GLB_DATA* cp_glb )
{
	return cp_glb->hero_sex;
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモン外国語テキストバージョンフラグ取得
 *
 *	@param	cp_glb	グローバルデータ
 *	@param	lang	言語コード
 *
 *	@retval	TRUE	フラグがたっている
 *	@retval	FALSE	フラグがたっていない
 */
//-----------------------------------------------------------------------------
BOOL ZKN_GLBDATA_PokeTextVersionFlagGet( const ZKN_GLB_DATA* cp_glb, int lang )
{
	int monsno = ZKN_GLBDATA_PokeMonsNoGet( cp_glb );

	// 文字外国語図鑑マスターバージョンアップされていなければ、FALSEしか返さない
	if( ZukanWork_GetTextVersionUpMasterFlag( cp_glb->cp_zukansave_data ) == FALSE ){
		return FALSE;
	}
	return ZukanWork_GetTextVersionUpFlag( cp_glb->cp_zukansave_data, monsno, lang );
}

//----------------------------------------------------------------------------
/**
 *	@brief	グラフィックバージョンフラグ
 *
 *	@param	cp_glb	グローバルデータ
 *
 *	@retval	TRUE バージョンアップ済み
 *	@retval	FALSE バージョンアップされていない
 */
//-----------------------------------------------------------------------------
BOOL ZKN_GLBDATA_PokeGraphicVersionFlagGet( const ZKN_GLB_DATA* cp_glb )
{
	return ZukanWork_GetGraphicVersionUpFlag( cp_glb->cp_zukansave_data );
}

//----------------------------------------------------------------------------
/**
 *	@brief	タッチパネル　カーソルフラグを切り替える
 *
 *	@param	cp_glb	グローバルデータ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void ZKN_GLBDATA_TouchCursorFlagSet( ZKN_GLB_DATA* cp_glb )
{
	// タッチパネル優先
	if( sys.tp_cont ){
		cp_glb->touch_cursor_flag = ZKN_TCHCUSO_TOUCHPANEL;
		return ;
	}

	// キーは優先度低い
	if( sys.cont ){
		cp_glb->touch_cursor_flag = ZKN_TCHCUSO_CURSOR;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	タッチパネルカーソルフラグ取得
 *
 *	@param	cp_glb	グローバルデータ
 *
 *	@retval	ZKN_TCHCUSO_TOUCHPANEL		タッチパネルで行う
 *	@retval ZKN_TCHCUSO_CURSOR			カーソルで行う
 */
//-----------------------------------------------------------------------------
BOOL ZKN_GLBDATA_TouchCursorFlagGet( const ZKN_GLB_DATA* cp_glb )
{
	return cp_glb->touch_cursor_flag;
}




//-----------------------------------------------------------------------------
/**
 *		プライベート関数
 */
//-----------------------------------------------------------------------------

//----------------------------------------------------------------------------
/**
 *
 *	@brief	シンオウ　全国　リストから今捕まえてあるポケモンリストを作成
 *
 *	@param	p_buff				リスト作成先		(テーブル数以上あること)
 *	@param	p_count				カウント
 *	@param	cp_zukansave_data	図鑑セーブデータ
 *	@param	cp_tbl				ソートテーブル
 *	@param	num					テーブル数
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void ZknPokeListTblMakeSortData( u16* p_buff, int* p_count, const ZUKAN_WORK* cp_zukansave_data, const u16* cp_tbl, int num )
{
	int i;			// ループ用

	*p_count = 0;
	for( i=0; i<num; i++ ){
		
		// 捕まえたことあるかチェック
		if( ZukanWork_GetPokeSeeFlag( cp_zukansave_data, cp_tbl[ i ] ) ){
			p_buff[ *p_count ] = cp_tbl[ i ];
			(*p_count) ++;
		}
		
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ソートされているテーブルないからさらに絞り込む
 *
 *	@param	p_buff		データ格納先
 *	@param	p_count		カウンタ
 *	@param	cp_tbl		ソート済みデータテーブル
 *	@param	num			テーブル数
 *	@param	cp_sarch_tbl　サーチテーブル
 *	@param	sarch_num	サーチテーブル数
 *	@param	see_ok_flg	見ただけポケモンもOKかチェック
 *	@param	cp_zukansave_data	図鑑セーブデータ
 *
 *	@return	none
 *		検索処理
 */
//-----------------------------------------------------------------------------
static void ZknPokeListTblMakeSarch( u16* p_buff, int* p_count, const u16* cp_tbl, int num, const u16* cp_sarch_tbl, int sarch_num, BOOL see_ok_flg, const ZUKAN_WORK* cp_zukansave_data )
{
	int i,j;			// ループ用

	*p_count = 0;
	for( i=0; i<num; i++ ){
		
		for( j=0; j<sarch_num; j++ ){
			if( cp_tbl[i] == cp_sarch_tbl[j] ){
				if( see_ok_flg == TRUE ){	// 見ただけでもリストに入れていとき
					break;
				}else{
					// みただけは許されないとき
					// 捕まえているかチェック
					if( ZukanWork_GetPokeGetFlag( cp_zukansave_data, cp_tbl[ i ] ) ){
						break;
					}
				}
			}
		}
		
		// サーチテーブル内にあったら設定
		if( j < sarch_num ){
			p_buff[ *p_count ] = cp_tbl[ i ];
			(*p_count) ++;
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑ポケモンリストテーブル作成関数
 *
 *	@param	p_poke_list			作成先
 *	@param	cp_zukansave_data	図鑑セーブデータ
 *	@param	cp_tbl				見つけたポケモンでソート済みテーブル
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void ZknPokeListTblMake( ZKN_POKELIST_TBL* p_poke_list, const ZUKAN_WORK* cp_zukansave_data, const u16* cp_tbl, int tbl_num )
{
	int i;	// ループ用

	p_poke_list->tbl_poke_num = 0;
	for( i=0; i<tbl_num; i++ ){
		
		// 捕まえたことがあるかチェック
		if( ZukanWork_GetPokeGetFlag( cp_zukansave_data, cp_tbl[ i ] ) ){
			p_poke_list->zkn_pokelist_tbl[ p_poke_list->tbl_poke_num ].type = ZKN_POKELIST_TYPE_GET;
		}else{
			p_poke_list->zkn_pokelist_tbl[ p_poke_list->tbl_poke_num ].type = ZKN_POKELIST_TYPE_SEE;
		}

		p_poke_list->zkn_pokelist_tbl[ p_poke_list->tbl_poke_num ].mons_no = cp_tbl[ i ];

		p_poke_list->tbl_poke_num ++;
	}
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	図鑑ポケモンリスト描画テーブル作成関数
 *
 *	@param	p_poke_list			作成先
 *	@param	cp_all_tbl			ソート元データ
 *	@param	tbl_num				テーブル数
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
static void ZknPokeListDrawTblMake( ZKN_POKELIST_TBL* p_poke_list, const u16* cp_all_tbl, int all_tbl_num )
{
	int i;	// ループ用
	int count;

	// 元データから描画データ作成		上の省いたデータをダミーとして格納する
	count = 0;
	p_poke_list->draw_tbl_poke_num = 0;
	for( i=0; i<all_tbl_num; i++ ){
		
		// テーブル以上になったら終わり
		if( count < p_poke_list->tbl_poke_num ){
			if( p_poke_list->zkn_pokelist_tbl[ count ].mons_no == cp_all_tbl[ i ] ){
				p_poke_list->zkn_pokelistdraw_tbl[ p_poke_list->draw_tbl_poke_num ] = count;
				count ++;
				p_poke_list->draw_tbl_poke_num++;

			}else{
				p_poke_list->zkn_pokelistdraw_tbl[ p_poke_list->draw_tbl_poke_num ] = POKEMON_LIST_DRAWTBL_DUMMY;
				p_poke_list->draw_tbl_poke_num++;
			}
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンリスト描画テーブルコピー
 *
 *	@param	p_poke_list		ポケモンリストデータ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeListDrawTblCopy( ZKN_POKELIST_TBL* p_poke_list )
{
	int i;	// ループ用

	p_poke_list->draw_tbl_poke_num = 0;
	for( i=0; i<p_poke_list->tbl_poke_num; i++ ){
		
		p_poke_list->zkn_pokelistdraw_tbl[ p_poke_list->draw_tbl_poke_num ] = i;
		p_poke_list->draw_tbl_poke_num++;
	}
}


//----------------------------------------------------------------------------
/**
 *	@brief	ソートﾃﾞｰﾀ取得
 *
 *	@param	heap		ヒープ
 *	@param	idx			ﾃﾞｰﾀｲﾝﾃﾞｯｸｽ
 *	@param	p_arry_num	配列要素数取得先
 *
 *	@return	ﾃﾞｰﾀバッファ		要素数はp_arry_numに格納
 */
//-----------------------------------------------------------------------------
static u16* ZKN_SORTDATA_Get( int heap, int idx, int* p_arry_num )
{
	u32 size;
	u16* p_buf;
	
	GF_ASSERT( ZKN_SORTDATA_NUM > idx );
	

	// 読み込み
	p_buf = ArcUtil_LoadEx( ARC_ZUKAN_DATA, ZKN_SORTDATA_START_IDX + idx, FALSE, heap, ALLOC_TOP, &size );

	*p_arry_num = size / ZKN_SORTDATA_ONESIZE;

	return p_buf;
}


//----------------------------------------------------------------------------
/**
 *	@brief	ｿｰﾄ処理　を行う
 *
 *	@param	sort_type		ｿｰﾄﾀｲﾌﾟ
 *	@param	p_buff			結果格納先
 *	@param	p_count			結果の要素数格納先
 *	@param	cp_tbl			元ﾃﾞｰﾀ
 *	@param	num				元ﾃﾞｰﾀ数
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeListSort_Core( int sort_type, u16* p_buff, int* p_count, const u16* cp_tbl, int num, int heap, const ZUKAN_WORK* cp_zukansave_data )
{
	u16* p_sort_data;	// ｿｰﾄﾃﾞｰﾀ
	int sort_data_count;
	BOOL see_ok_flg = FALSE;
	

	// 並びから選択する
	switch( sort_type ){
	case ZKN_POKELIST_SORT_NORMAL:		// ポケモンナンバー
		// そのまま
		p_sort_data = NULL;
		break;
		
	case ZKN_POKELIST_SORT_GOZYUUON:		// 五十音
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_AIUEO, &sort_data_count );
		see_ok_flg = TRUE;
		break;
		
	case ZKN_POKELIST_SORT_GRAM_L:		// 重い
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_HEAVY, &sort_data_count );
		break;
		
	case ZKN_POKELIST_SORT_GRAM_S:		// 軽い
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_LIGHT, &sort_data_count );
		break;
		
	case ZKN_POKELIST_SORT_HIGH_L:		// 高い
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_TALL, &sort_data_count );
		break;
		
	case ZKN_POKELSIT_SOTT_HIGH_S:		// 低い
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_SMALL, &sort_data_count );
		break;
		
	default:
		GF_ASSERT(0);
		break;
	}

	if( p_sort_data != NULL ){
		ZknPokeListTblMakeSarch( p_buff, p_count,  p_sort_data, sort_data_count, cp_tbl, num, see_ok_flg, cp_zukansave_data );
		sys_FreeMemoryEz( p_sort_data );
	}else{

		// そのままコピー
		memcpy( p_buff, cp_tbl, ZKN_SORTDATA_ONESIZE * num );
		*p_count = num;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	名前検索
 *
 *	@param	search_name		検索ﾀｲﾌﾟ
 *	@param	p_buff			格納先バッファ
 *	@param	p_count			バッファ要素数
 *	@param	cp_tbl			元ﾃﾞｰﾀ
 *	@param	num				元ﾃﾞｰﾀ要素数
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeListSarchName_Core( int search_name, u16* p_buff, int* p_count, const u16* cp_tbl, int num, int heap, const ZUKAN_WORK* cp_zukansave_data )
{
	u16* p_sort_data;	// ｿｰﾄﾃﾞｰﾀ
	int sort_data_count;

	// なまえ
	switch( search_name ){
	case ZKN_POKELIST_SEARCH_NAME_NONE:
		// そのまま
		p_sort_data = NULL;
		break;
	case ZKN_POKELIST_SEARCH_NAME_A:
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_NAME_A, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_NAME_KA:
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_NAME_KA, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_NAME_SA:
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_NAME_SA, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_NAME_TA:
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_NAME_TA, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_NAME_NA:
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_NAME_NA, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_NAME_HA:
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_NAME_HA, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_NAME_MA:
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_NAME_MA, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_NAME_RA:
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_NAME_RA, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_NAME_YAWA:
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_NAME_YAWA, &sort_data_count );
		break;
	default:
		GF_ASSERT(0);
		break;
	}

	if( p_sort_data != NULL ){
		ZknPokeListTblMakeSarch( p_buff, p_count, cp_tbl, num,  p_sort_data, sort_data_count, TRUE, cp_zukansave_data );
		sys_FreeMemoryEz( p_sort_data );
	}else{

		// そのままコピー
		memcpy( p_buff, cp_tbl, ZKN_SORTDATA_ONESIZE * num );
		*p_count = num;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ﾀｲﾌﾟ検索
 *
 *	@param	search_type		検索ﾀｲﾌﾟ
 *	@param	p_buff			格納先バッファ
 *	@param	p_count			バッファ要素数
 *	@param	cp_tbl			元ﾃﾞｰﾀ
 *	@param	num				元ﾃﾞｰﾀ要素数
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeListSarchType_Core( int search_type, u16* p_buff, int* p_count, const u16* cp_tbl, int num, int heap, const ZUKAN_WORK* cp_zukansave_data )
{
	u16* p_sort_data;	// ｿｰﾄﾃﾞｰﾀ
	int sort_data_count;

	// ﾀｲﾌﾟ
	switch( search_type ){
	case ZKN_POKELIST_SEARCH_TYPE_NONE:
		p_sort_data = NULL;
		break;
	case ZKN_POKELIST_SEARCH_TYPE_NORMAL:
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_TYPE_NORMAL, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_TYPE_BATTLE:	
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_TYPE_BATTLE, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_TYPE_HIKOU:	
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_TYPE_HIKOU, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_TYPE_POISON:	
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_TYPE_POISON, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_TYPE_JIMEN:	
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_TYPE_JIMEN, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_TYPE_IWA:		
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_TYPE_IWA, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_TYPE_MUSHI:	
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_TYPE_MUSHI, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_TYPE_GHOST:	
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_TYPE_GHOST, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_TYPE_METAL:	
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_TYPE_METAL, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_TYPE_FIRE:	
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_TYPE_FIRE, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_TYPE_WATER:	
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_TYPE_WATER, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_TYPE_KUSA:	
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_TYPE_KUSA, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_TYPE_ELECTRIC:
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_TYPE_ELECTRIC, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_TYPE_SP:		
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_TYPE_SP, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_TYPE_KOORI:	
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_TYPE_KOORI, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_TYPE_DRAGON:	
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_TYPE_DRAGON, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_TYPE_AKU:	
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_TYPE_AKU, &sort_data_count );
		break;

	default:
		GF_ASSERT(0);
		break;
	}

	if( p_sort_data != NULL ){
		ZknPokeListTblMakeSarch( p_buff, p_count, cp_tbl, num,  p_sort_data, sort_data_count, FALSE, cp_zukansave_data );
		sys_FreeMemoryEz( p_sort_data );
	}else{

		// そのままコピー
		memcpy( p_buff, cp_tbl, ZKN_SORTDATA_ONESIZE * num );
		*p_count = num;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	形検索
 *
 *	@param	search_form		検索ﾀｲﾌﾟ
 *	@param	p_buff			格納先バッファ
 *	@param	p_count			バッファ要素数
 *	@param	cp_tbl			元ﾃﾞｰﾀ
 *	@param	num				元ﾃﾞｰﾀ要素数
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ZknPokeListSarchForm_Core( int search_form, u16* p_buff, int* p_count, const u16* cp_tbl, int num, int heap, const ZUKAN_WORK* cp_zukansave_data )
{
	u16* p_sort_data;	// ｿｰﾄﾃﾞｰﾀ
	int sort_data_count;

	// ﾀｲﾌﾟ
	switch( search_form ){
	case ZKN_POKELIST_SEARCH_FORM_NONE:
		p_sort_data = NULL;
		break;
	case ZKN_POKELIST_SEARCH_FORM_FOUR_LEGS:
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_FORM_FOUR_LEGS, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_FORM_TWO_LEGS:
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_FORM_TWO_LEGS, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_FORM_TAIL:
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_FORM_TAIL, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_FORM_HARABAI:
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_FORM_HARABAI, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_FORM_FOUR_WING:
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_FORM_FOUR_WING, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_FORM_TWO_WING:
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_FORM_TWO_WING, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_FORM_HAITSUKUBARI:
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_FORM_HAITSUKUBARI, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_FORM_STRAIGHT:
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_FORM_STRAIGHT, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_FORM_ARM:
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_FORM_ARM, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_FORM_LEGS:
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_FORM_LEGS, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_FORM_MANY_LEGS:
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_FORM_MANY_LEGS, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_FORM_WATER:
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_FORM_WATER, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_FORM_CIRCLE:
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_FORM_CIRCLE, &sort_data_count );
		break;
	case ZKN_POKELIST_SEARCH_FORM_COMP:
		p_sort_data = ZKN_SORTDATA_Get( heap, ZKN_SORTDATA_FORM_COMP, &sort_data_count );
		break;
	default:
		GF_ASSERT(0);
		break;
	}

	if( p_sort_data != NULL ){
		ZknPokeListTblMakeSarch( p_buff, p_count, cp_tbl, num,  p_sort_data, sort_data_count, TRUE, cp_zukansave_data );
		sys_FreeMemoryEz( p_sort_data );
	}else{

		// そのままコピー
		memcpy( p_buff, cp_tbl, ZKN_SORTDATA_ONESIZE * num );
		*p_count = num;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	ﾎﾟｹﾓﾝﾘｽﾄ内の見つけた数　発見した数をカウント
 *
 *	@param	p_poke_list		ﾎﾟｹﾓﾝﾘｽﾄテーブル
 *	@param	p_see_num		見つけた数格納先
 *	@param	p_get_num		発見した数格納先
 *
 *	@return
 */
//-----------------------------------------------------------------------------
static void ZknPokeListTblSeeGetNumCount( ZKN_POKELIST_TBL* p_poke_list, int* p_see_num, int* p_get_num )
{
	int i;	// ループ用

	*p_see_num = 0;
	*p_get_num = 0;
	
	for( i=0; i<p_poke_list->tbl_poke_num; i++ ){
		if(p_poke_list->zkn_pokelist_tbl[ i ].type == ZKN_POKELIST_TYPE_GET	){

			(*p_get_num)++;
		}
		(*p_see_num)++;
	}
}
