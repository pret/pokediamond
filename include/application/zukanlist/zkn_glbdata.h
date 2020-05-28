//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		zkn_glbdata.h
 *	@brief		図鑑アプリケーション共有データ
 *	@author		tomoya takahashi
 *	@data		2006.01.19
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __ZKN_GLBDATA_H__
#define __ZKN_GLBDATA_H__

#include "include/poketool/monsno.h"
#include "include/savedata/zukanwork.h"
#include "include/savedata/mystatus.h"

#include "include/application/zukanlist/zkn_height_gram.h"

#undef GLOBAL
#ifdef	__ZKN_GLBDATA_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------

//-------------------------------------
//	ポケモンタイプ
//=====================================
enum{
	ZKN_POKELIST_TYPE_NONE,	// わからない
	ZKN_POKELIST_TYPE_SEE,	// 見つけた
	ZKN_POKELIST_TYPE_GET,	// 捕まえた
};

//-------------------------------------
//	ポケモンリスト
//=====================================
#define POKEMON_LIST_TBL_NUM	(MONSNO_END)	// テーブル数 = 全ポケモンの数
#define POKEMON_LIST_DRAWTBL_DUMMY	( POKEMON_LIST_TBL_NUM + 1 )

//-------------------------------------
//	ポケモンリストソート
//=====================================
enum{
	ZKN_POKELIST_SORT_NORMAL,		// ポケモンナンバー
	ZKN_POKELIST_SORT_GOZYUUON,		// 五十音
	ZKN_POKELIST_SORT_GRAM_L,		// 重い
	ZKN_POKELIST_SORT_GRAM_S,		// 軽い
	ZKN_POKELIST_SORT_HIGH_L,		// 高い
	ZKN_POKELSIT_SOTT_HIGH_S,		// 低い
	ZKN_POKELIST_SORT_NUM,
};

//-------------------------------------
//	ポケモン検索マスク
//=====================================
// 名前
enum{
	ZKN_POKELIST_SEARCH_NAME_NONE,
	ZKN_POKELIST_SEARCH_NAME_A,
	ZKN_POKELIST_SEARCH_NAME_KA,
	ZKN_POKELIST_SEARCH_NAME_SA,
	ZKN_POKELIST_SEARCH_NAME_TA,
	ZKN_POKELIST_SEARCH_NAME_NA,
	ZKN_POKELIST_SEARCH_NAME_HA,
	ZKN_POKELIST_SEARCH_NAME_MA,
	ZKN_POKELIST_SEARCH_NAME_RA,
	ZKN_POKELIST_SEARCH_NAME_YAWA,
	ZKN_POKELIST_SEARCH_NAME_NUM
};
// タイプ
enum{
	ZKN_POKELIST_SEARCH_TYPE_NONE,
	ZKN_POKELIST_SEARCH_TYPE_NORMAL,
	ZKN_POKELIST_SEARCH_TYPE_BATTLE,	
	ZKN_POKELIST_SEARCH_TYPE_HIKOU,	
	ZKN_POKELIST_SEARCH_TYPE_POISON,	
	ZKN_POKELIST_SEARCH_TYPE_JIMEN,	
	ZKN_POKELIST_SEARCH_TYPE_IWA,		
	ZKN_POKELIST_SEARCH_TYPE_MUSHI,	
	ZKN_POKELIST_SEARCH_TYPE_GHOST,	
	ZKN_POKELIST_SEARCH_TYPE_METAL,	
	ZKN_POKELIST_SEARCH_TYPE_FIRE,	
	ZKN_POKELIST_SEARCH_TYPE_WATER,	
	ZKN_POKELIST_SEARCH_TYPE_KUSA,	
	ZKN_POKELIST_SEARCH_TYPE_ELECTRIC,
	ZKN_POKELIST_SEARCH_TYPE_SP,		
	ZKN_POKELIST_SEARCH_TYPE_KOORI,	
	ZKN_POKELIST_SEARCH_TYPE_DRAGON,	
	ZKN_POKELIST_SEARCH_TYPE_AKU,	
	ZKN_POKELIST_SEARCH_TYPE_NUM
};
// 形
enum{
	ZKN_POKELIST_SEARCH_FORM_NONE,
	ZKN_POKELIST_SEARCH_FORM_FOUR_LEGS,
	ZKN_POKELIST_SEARCH_FORM_TWO_LEGS,
	ZKN_POKELIST_SEARCH_FORM_TAIL,
	ZKN_POKELIST_SEARCH_FORM_HARABAI,
	ZKN_POKELIST_SEARCH_FORM_FOUR_WING,
	ZKN_POKELIST_SEARCH_FORM_TWO_WING,
	ZKN_POKELIST_SEARCH_FORM_HAITSUKUBARI,
	ZKN_POKELIST_SEARCH_FORM_STRAIGHT,
	ZKN_POKELIST_SEARCH_FORM_ARM,
	ZKN_POKELIST_SEARCH_FORM_LEGS,
	ZKN_POKELIST_SEARCH_FORM_MANY_LEGS,
	ZKN_POKELIST_SEARCH_FORM_WATER,
	ZKN_POKELIST_SEARCH_FORM_CIRCLE,
	ZKN_POKELIST_SEARCH_FORM_COMP,
	ZKN_POKELIST_SEARCH_FORM_NUM
};

//-------------------------------------
//	図鑑モード
//=====================================
enum {
	ZKN_MODE_SHINOH,	// シンオウ図鑑
	ZKN_MODE_ZENKOKU,	// 全国図鑑
	ZKN_MODE_NAZO,		// 不明	（まだ1回も図鑑を開いていないとき）
} ;

//-------------------------------------
//	検索ソート切り替えよう
//=====================================
enum {
	ZKN_SORTSEARCH_NONE,
	ZKN_SORTSEARCH_SORT,
} ;

//-------------------------------------
//	タッチパネル　カーソルフラグ
//=====================================
enum{
	ZKN_TCHCUSO_TOUCHPANEL,
	ZKN_TCHCUSO_CURSOR,
};

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	ポケモンリスト構造体
//=====================================
typedef struct {
	int mons_no;	// ポケモンナンバー
	int type;		// 見つけた 捕まえた
} ZKN_POKELIST_DATA;

//-------------------------------------
//	ポケモンリストテーブル構造体
//=====================================
typedef struct {
	ZKN_POKELIST_DATA zkn_pokelist_tbl[ POKEMON_LIST_TBL_NUM ];
	int	tbl_no;			// 今選択中のテーブルナンバー
	int tbl_poke_num;	// 今のテーブルの総数

	// 表示用
	int zkn_pokelistdraw_tbl[ POKEMON_LIST_TBL_NUM ];
	int	draw_tbl_no;			// 今選択中のテーブルナンバー
	int draw_tbl_poke_num;		// 今のテーブルの総数
} ZKN_POKELIST_TBL;


//-------------------------------------
//	図鑑グローバルデータ
//
//	複数アプリケーションで共有したいデータ
//=====================================
typedef struct{
	// 図鑑画面データ
	const ZUKAN_WORK*	cp_zukansave_data;
	
	// ポケモンリストテーブル構造体
	ZKN_POKELIST_TBL poke_list;			// 表示データ

	// 図鑑モード
	int zkn_mode;

	// 全国図鑑所持フラグ
	BOOL zkn_allmap_get;

	// 発見数
	int	see_num;

	// 捕獲数
	int get_num;

	// 検索ソート切り替えよう
	int sort_search_flag;

	// 図鑑を開いたときの時間帯
	int time_zone;

	// 高さ重さデータ
	ZKN_HEIGHT_GRAM_PTR height_gram;

	// ROMコード
	u32 rom_code;
	
	// 主人公が男か女か
	u32 hero_sex; 
	
	// 主人公の名前
	STRBUF*	hero_name;

	// タッチパネル　カーソルフラグ
	int touch_cursor_flag;
	
	// 最後に図鑑テキストを見たポケモン
	u16 last_see_monsno;
	u16 last_see_zkn_mode;

	// 隠しマップ
	BOOL hidemap_id_D15;
	BOOL hidemap_id_D30;
	BOOL hidemap_id_L04;
	BOOL hidemap_id_D18;
} ZKN_GLB_DATA;


//-------------------------------------
//	グローバルデータ初期化構造体
//=====================================
typedef struct {
	const ZUKAN_WORK* cp_zukansave_data;
	const MYSTATUS* cp_hero_data;
	int time_zone;
	BOOL hidemap_id_D15;
	BOOL hidemap_id_D30;
	BOOL hidemap_id_L04;
	BOOL hidemap_id_D18;
	u32 init_list_monsno;
	u32 zkn_mode;
} ZKN_GLB_DATA_INIT;


//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------

GLOBAL void ZKN_GLBDATA_Init( ZKN_GLB_DATA* p_glb, ZKN_GLB_DATA_INIT* p_init, int heap );
GLOBAL void ZKN_GLBDATA_Delete( ZKN_GLB_DATA* p_glb );

GLOBAL u32 ZKN_GLBDATA_SaveData_SexGet( const ZKN_GLB_DATA* cp_glb, int monsno, int count );
GLOBAL u32 ZKN_GLBDATA_SaveData_AnoonFormGet( const ZKN_GLB_DATA* cp_glb, int count );
GLOBAL u32 ZKN_GLBDATA_SaveData_SiiusiFormGet( const ZKN_GLB_DATA* cp_glb, int count );
GLOBAL u32 ZKN_GLBDATA_SaveData_SiidorugoFormGet( const ZKN_GLB_DATA* cp_glb, int count );
GLOBAL u32 ZKN_GLBDATA_SaveData_MinomuttiFormGet( const ZKN_GLB_DATA* cp_glb, int count );
GLOBAL u32 ZKN_GLBDATA_SaveData_MinomesuFormGet( const ZKN_GLB_DATA* cp_glb, int count );
GLOBAL u32 ZKN_GLBDATA_SaveData_FirstFormGet( const ZKN_GLB_DATA* cp_glb, u32 monsno );
GLOBAL u32 ZKN_GLBDATA_SaveData_SexNumGet( const ZKN_GLB_DATA* cp_glb, int monsno );
GLOBAL u32 ZKN_GLBDATA_SaveData_AnoonNumGet( const ZKN_GLB_DATA* cp_glb );
GLOBAL u32 ZKN_GLBDATA_SaveData_SiiusiNumGet( const ZKN_GLB_DATA* cp_glb );
GLOBAL u32 ZKN_GLBDATA_SaveData_SiidorugoNumGet( const ZKN_GLB_DATA* cp_glb );
GLOBAL u32 ZKN_GLBDATA_SaveData_MinomuttiNumGet( const ZKN_GLB_DATA* cp_glb );
GLOBAL u32 ZKN_GLBDATA_SaveData_MinomesuNumGet( const ZKN_GLB_DATA* cp_glb );
GLOBAL u32 ZKN_GLBDATA_SaveData_PattiruRndGet( const ZKN_GLB_DATA* cp_glb );
GLOBAL u32 ZKN_GLBDATA_SaveData_DeokisisuFormGet( const ZKN_GLB_DATA* cp_glb, int count );
GLOBAL u32 ZKN_GLBDATA_SaveData_DeokisisuFormSeeNumGet( const ZKN_GLB_DATA* cp_glb );
GLOBAL BOOL ZKN_GLBDATA_SaveData_ZenkokuZukanComp( const ZKN_GLB_DATA* cp_glb );
GLOBAL BOOL ZKN_GLBDATA_SaveData_ZenkokuZukanGet( const ZKN_GLB_DATA* cp_glb );


GLOBAL void ZKN_GLBDATA_PokeTextSeeSetMonsno( ZKN_GLB_DATA* p_glb, u32 monsno );
GLOBAL u32 ZKN_GLBDATA_PokeTextSeeGetMonsno( const ZKN_GLB_DATA* cp_glb );
GLOBAL void ZKN_GLBDATA_PokeTextSeeSetZknMode( ZKN_GLB_DATA* p_glb, u32 zkn_mode );
GLOBAL u32 ZKN_GLBDATA_PokeTextSeeGetZknMode( const ZKN_GLB_DATA* cp_glb );

GLOBAL BOOL ZKN_GLBDATA_SaveData_GraModeGet( const ZKN_GLB_DATA* cp_glb );
GLOBAL BOOL ZKN_GLBDATA_SaveData_TextModeGet( const ZKN_GLB_DATA* cp_glb, int country );

GLOBAL BOOL ZKN_GLBDATA_PokeListTblMake_DummyListCutFlg( ZKN_GLB_DATA* p_glb, int sort_type, int search_name, int search_type1, int search_type2, int search_form, int shinoh, int heap, BOOL dummy_list_cut );

GLOBAL BOOL ZKN_GLBDATA_PokeListTblMake( ZKN_GLB_DATA* p_glb, int sort_type, int search_name, int search_type1, int search_type2, int search_form, int shinoh, int heap );

GLOBAL BOOL ZKN_GLBDATA_PokeZknModeChengeCheck( const ZKN_GLB_DATA* cp_glb, int zkn_mode );
GLOBAL BOOL ZKN_GLBDATA_PokeZknModeChenge( ZKN_GLB_DATA* p_glb, int zkn_mode );
GLOBAL int ZKN_GLBDATA_PokeZknModeGet( const ZKN_GLB_DATA* cp_glb );

GLOBAL BOOL ZKN_GLBDATA_PokeListTblNoSetCheck( const ZKN_GLB_DATA* cp_glb, int no );
GLOBAL BOOL ZKN_GLBDATA_PokeListTblNoSet_Monsno( ZKN_GLB_DATA* p_glb, int monsno );
GLOBAL BOOL ZKN_GLBDATA_PokeListTblNoSet( ZKN_GLB_DATA* p_glb, int no );
GLOBAL BOOL ZKN_GLBDATA_PokeListTblNoAdd( ZKN_GLB_DATA* p_glb, int no );
GLOBAL int ZKN_GLBDATA_PokeListTblNoGet( const ZKN_GLB_DATA* cp_glb );
GLOBAL int ZKN_GLBDATA_PokeListTblNumGet( const ZKN_GLB_DATA* cp_glb );
GLOBAL int ZKN_GLBDATA_PokeListTblNoGet_Monsno( const ZKN_GLB_DATA* cp_glb, u32 monsno );
GLOBAL int ZKN_GLBDATA_PokeMonsNoGet( const ZKN_GLB_DATA* cp_glb );
GLOBAL int ZKN_GLBDATA_PokeMonsTypeGet( const ZKN_GLB_DATA* cp_glb );
GLOBAL const ZKN_POKELIST_DATA* ZKN_GLBDATA_PokeListTblGet( const ZKN_GLB_DATA* cp_glb, int tbl_no );
GLOBAL BOOL ZKN_GLBDATA_PokeListDrawTblNoSetCheck( const ZKN_GLB_DATA* cp_glb, int no );
GLOBAL BOOL ZKN_GLBDATA_PokeListDrawTblNoSet( ZKN_GLB_DATA* p_glb, int no );
GLOBAL BOOL ZKN_GLBDATA_PokeListDrawTblNoAdd( ZKN_GLB_DATA* p_glb, int no );
GLOBAL BOOL ZKN_GLBDATA_PokeListDrawTblNoAddCheck( ZKN_GLB_DATA* p_glb, int no );
GLOBAL int ZKN_GLBDATA_PokeListDrawTblNoGet( const ZKN_GLB_DATA* cp_glb );
GLOBAL int ZKN_GLBDATA_PokeListDrawTblNumGet( const ZKN_GLB_DATA* cp_glb );
GLOBAL int ZKN_GLBDATA_PokeListDrawTblDataGet( const ZKN_GLB_DATA* cp_glb, int no );
GLOBAL void ZKN_GLBDATA_PokeListDrawTblSetNowTblNo( ZKN_GLB_DATA* p_glb );

GLOBAL int ZKN_GLBDATA_PokeSeeNumGet( const ZKN_GLB_DATA* cp_glb );
GLOBAL int ZKN_GLBDATA_PokeGetNumGet( const ZKN_GLB_DATA* cp_glb );

GLOBAL int ZKN_GLBDATA_RomDataGet( const ZKN_GLB_DATA* cp_glb );
GLOBAL STRBUF* ZKN_GLBDATA_HeroNameGet( const ZKN_GLB_DATA* cp_glb );
GLOBAL u32 ZKN_GLBDATA_HeroSexGet( const ZKN_GLB_DATA* cp_glb );
GLOBAL BOOL ZKN_GLBDATA_PokeTextVersionFlagGet( const ZKN_GLB_DATA* cp_glb, int lang );
GLOBAL BOOL ZKN_GLBDATA_PokeGraphicVersionFlagGet( const ZKN_GLB_DATA* cp_glb );

GLOBAL void ZKN_GLBDATA_TouchCursorFlagSet( ZKN_GLB_DATA* cp_glb );
GLOBAL BOOL ZKN_GLBDATA_TouchCursorFlagGet( const ZKN_GLB_DATA* cp_glb );

#undef	GLOBAL
#endif		// __ZKN_GLBDATA_H__

