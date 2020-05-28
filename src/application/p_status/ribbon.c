//============================================================================================
/**
 * @file	ribbon.c
 * @brief	リボンデータ関連
 * @author	Hiroyuki Nakamura
 * @date	2006.04.18
 */
//============================================================================================
#include "common.h"
#include "poketool/poke_tool.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_ribbon.h"
#include "application/pst_gra.naix"

#define	RIBBON_H_GLOBAL
#include "ribbon.h"


//============================================================================================
//	定数定義
//============================================================================================
typedef struct {
	u32	pp_id;		// PokeParaGetの取得ID
	u16	graphic;	// グラフィックID
	u16	pal_num;	// パレット番号
	u16 name;		// リボン名
	u16	info;		// リボン説明
}RIBBON_TABLE;


//============================================================================================
//	グローバル変数
//============================================================================================
// リボンデータ
static const RIBBON_TABLE RibbonTable[] =
{
	{ ID_PARA_champ_ribbon,					NARC_pst_gra_ribbon00_NCGR, 0,	mes_ribbon_name_000,	mes_ribbon_text_000 },	//チャンプリボン

	{ ID_PARA_stylemedal_normal,			NARC_pst_gra_ribbon01_NCGR, 0,	mes_ribbon_name_001,	mes_ribbon_text_001 },	//かっこよさ勲章(ノーマル)AGBコンテスト
	{ ID_PARA_stylemedal_super,				NARC_pst_gra_ribbon02_NCGR, 0,	mes_ribbon_name_002,	mes_ribbon_text_002 },	//かっこよさ勲章(スーパー)AGBコンテスト
	{ ID_PARA_stylemedal_hyper,				NARC_pst_gra_ribbon03_NCGR, 0,	mes_ribbon_name_003,	mes_ribbon_text_003 },	//かっこよさ勲章(ハイパー)AGBコンテスト
	{ ID_PARA_stylemedal_master,			NARC_pst_gra_ribbon04_NCGR, 0,	mes_ribbon_name_004,	mes_ribbon_text_004 },	//かっこよさ勲章(マスター)AGBコンテスト

	{ ID_PARA_beautifulmedal_normal,		NARC_pst_gra_ribbon01_NCGR, 1,	mes_ribbon_name_005,	mes_ribbon_text_005 },	//うつくしさ勲章(ノーマル)AGBコンテスト
	{ ID_PARA_beautifulmedal_super,			NARC_pst_gra_ribbon02_NCGR, 1,	mes_ribbon_name_006,	mes_ribbon_text_006 },	//うつくしさ勲章(スーパー)AGBコンテスト
	{ ID_PARA_beautifulmedal_hyper,			NARC_pst_gra_ribbon03_NCGR, 1,	mes_ribbon_name_007,	mes_ribbon_text_007 },	//うつくしさ勲章(ハイパー)AGBコンテスト
	{ ID_PARA_beautifulmedal_master,		NARC_pst_gra_ribbon04_NCGR, 1,	mes_ribbon_name_008,	mes_ribbon_text_008 },	//うつくしさ勲章(マスター)AGBコンテスト

	{ ID_PARA_cutemedal_normal,				NARC_pst_gra_ribbon01_NCGR, 2,	mes_ribbon_name_009,	mes_ribbon_text_009 },	//かわいさ勲章(ノーマル)AGBコンテスト
	{ ID_PARA_cutemedal_super,				NARC_pst_gra_ribbon02_NCGR, 2,	mes_ribbon_name_010,	mes_ribbon_text_010 },	//かわいさ勲章(スーパー)AGBコンテスト
	{ ID_PARA_cutemedal_hyper,				NARC_pst_gra_ribbon03_NCGR, 2,	mes_ribbon_name_011,	mes_ribbon_text_011 },	//かわいさ勲章(ハイパー)AGBコンテスト
	{ ID_PARA_cutemedal_master,				NARC_pst_gra_ribbon04_NCGR, 2,	mes_ribbon_name_012,	mes_ribbon_text_012 },	//かわいさ勲章(マスター)AGBコンテスト

	{ ID_PARA_clevermedal_normal,			NARC_pst_gra_ribbon01_NCGR, 3,	mes_ribbon_name_013,	mes_ribbon_text_013 },	//かしこさ勲章(ノーマル)AGBコンテスト
	{ ID_PARA_clevermedal_super,			NARC_pst_gra_ribbon02_NCGR, 3,	mes_ribbon_name_014,	mes_ribbon_text_014 },	//かしこさ勲章(スーパー)AGBコンテスト
	{ ID_PARA_clevermedal_hyper,			NARC_pst_gra_ribbon03_NCGR, 3,	mes_ribbon_name_015,	mes_ribbon_text_015 },	//かしこさ勲章(ハイパー)AGBコンテスト
	{ ID_PARA_clevermedal_master,			NARC_pst_gra_ribbon04_NCGR, 3,	mes_ribbon_name_016,	mes_ribbon_text_016 },	//かしこさ勲章(マスター)AGBコンテスト

	{ ID_PARA_strongmedal_normal,			NARC_pst_gra_ribbon01_NCGR, 4,	mes_ribbon_name_017,	mes_ribbon_text_017 },	//たくましさ勲章(ノーマル)AGBコンテスト
	{ ID_PARA_strongmedal_super,			NARC_pst_gra_ribbon02_NCGR, 4,	mes_ribbon_name_018,	mes_ribbon_text_018 },	//たくましさ勲章(スーパー)AGBコンテスト
	{ ID_PARA_strongmedal_hyper,			NARC_pst_gra_ribbon03_NCGR, 4,	mes_ribbon_name_019,	mes_ribbon_text_019 },	//たくましさ勲章(ハイパー)AGBコンテスト
	{ ID_PARA_strongmedal_master,			NARC_pst_gra_ribbon04_NCGR, 4,	mes_ribbon_name_020,	mes_ribbon_text_020 },	//たくましさ勲章(マスター)AGBコンテスト

	{ ID_PARA_winning_ribbon,				NARC_pst_gra_ribbon06_NCGR, 0,	mes_ribbon_name_021,	mes_ribbon_text_021 },	//ウィニングリボン
	{ ID_PARA_victory_ribbon,				NARC_pst_gra_ribbon05_NCGR, 0,	mes_ribbon_name_022,	mes_ribbon_text_022 },	//ビクトリーリボン
	{ ID_PARA_bromide_ribbon,				NARC_pst_gra_ribbon07_NCGR, 1,	mes_ribbon_name_023,	mes_ribbon_text_023 },	//ブロマイドリボン

	{ ID_PARA_ganba_ribbon,					NARC_pst_gra_ribbon08_NCGR, 2,	mes_ribbon_name_024,	mes_ribbon_text_024 },	//がんばリボン
	{ ID_PARA_marine_ribbon,				NARC_pst_gra_ribbon09_NCGR, 1,	mes_ribbon_name_025,	MSG_SP_RIBBON+0 },		//マリンリボン
	{ ID_PARA_land_ribbon,					NARC_pst_gra_ribbon09_NCGR, 3,	mes_ribbon_name_026,	MSG_SP_RIBBON+1 },		//ランドリボン
	{ ID_PARA_sky_ribbon,					NARC_pst_gra_ribbon09_NCGR, 4,	mes_ribbon_name_027,	MSG_SP_RIBBON+2 },		//スカイリボン

	{ ID_PARA_country_ribbon,				NARC_pst_gra_ribbon10_NCGR, 3,	mes_ribbon_name_028,	mes_ribbon_haihu_text_032 },	//MSG_SP_RIBBON+3 },	//カントリーリボン
	{ ID_PARA_national_ribbon,				NARC_pst_gra_ribbon10_NCGR, 4,	mes_ribbon_name_029,	mes_ribbon_haihu_text_044 },	//MSG_SP_RIBBON+4 },	//ナショナルリボン
	{ ID_PARA_earth_ribbon,					NARC_pst_gra_ribbon11_NCGR, 0,	mes_ribbon_name_030,	mes_ribbon_haihu_text_045 },	//MSG_SP_RIBBON+5 },	//アースリボン
	{ ID_PARA_world_ribbon,					NARC_pst_gra_ribbon11_NCGR, 1,	mes_ribbon_name_031,	mes_ribbon_haihu_text_032 },	//MSG_SP_RIBBON+6 },	//ワールドリボン

	{ ID_PARA_sinou_champ_ribbon,			NARC_pst_gra_ribon_32_NCGR, 0,	mes_ribbon_name_032,	mes_ribbon_text_032 },	//シンオウチャンプリボン

	{ ID_PARA_trial_stylemedal_normal,		NARC_pst_gra_ribon_33_NCGR, 0,	mes_ribbon_name_033,	mes_ribbon_text_033 },	//かっこよさ勲章(ノーマル)トライアル
	{ ID_PARA_trial_stylemedal_super,		NARC_pst_gra_ribon_34_NCGR, 0,	mes_ribbon_name_034,	mes_ribbon_text_034 },	//かっこよさ勲章(スーパー)トライアル
	{ ID_PARA_trial_stylemedal_hyper,		NARC_pst_gra_ribon_35_NCGR, 0,	mes_ribbon_name_035,	mes_ribbon_text_035 },	//かっこよさ勲章(ハイパー)トライアル
	{ ID_PARA_trial_stylemedal_master,		NARC_pst_gra_ribon_36_NCGR, 0,	mes_ribbon_name_036,	mes_ribbon_text_036 },	//かっこよさ勲章(マスター)トライアル

	{ ID_PARA_trial_beautifulmedal_normal,	NARC_pst_gra_ribon_33_NCGR, 1,	mes_ribbon_name_037,	mes_ribbon_text_037 },	//うつくしさ勲章(ノーマル)トライアル
	{ ID_PARA_trial_beautifulmedal_super,	NARC_pst_gra_ribon_34_NCGR, 1,	mes_ribbon_name_038,	mes_ribbon_text_038 },	//うつくしさ勲章(スーパー)トライアル
	{ ID_PARA_trial_beautifulmedal_hyper,	NARC_pst_gra_ribon_35_NCGR, 1,	mes_ribbon_name_039,	mes_ribbon_text_039 },	//うつくしさ勲章(ハイパー)トライアル
	{ ID_PARA_trial_beautifulmedal_master,	NARC_pst_gra_ribon_36_NCGR, 1,	mes_ribbon_name_040,	mes_ribbon_text_040 },	//うつくしさ勲章(マスター)トライアル

	{ ID_PARA_trial_cutemedal_normal,		NARC_pst_gra_ribon_33_NCGR, 2,	mes_ribbon_name_041,	mes_ribbon_text_041 },	//かわいさ勲章(ノーマル)トライアル
	{ ID_PARA_trial_cutemedal_super,		NARC_pst_gra_ribon_34_NCGR, 2,	mes_ribbon_name_042,	mes_ribbon_text_042 },	//かわいさ勲章(スーパー)トライアル
	{ ID_PARA_trial_cutemedal_hyper,		NARC_pst_gra_ribon_35_NCGR, 2,	mes_ribbon_name_043,	mes_ribbon_text_043 },	//かわいさ勲章(ハイパー)トライアル
	{ ID_PARA_trial_cutemedal_master,		NARC_pst_gra_ribon_36_NCGR, 2,	mes_ribbon_name_044,	mes_ribbon_text_044 },	//かわいさ勲章(マスター)トライアル

	{ ID_PARA_trial_clevermedal_normal,		NARC_pst_gra_ribon_33_NCGR, 3,	mes_ribbon_name_045,	mes_ribbon_text_045 },	//かしこさ勲章(ノーマル)トライアル
	{ ID_PARA_trial_clevermedal_super,		NARC_pst_gra_ribon_34_NCGR, 3,	mes_ribbon_name_046,	mes_ribbon_text_046 },	//かしこさ勲章(スーパー)トライアル
	{ ID_PARA_trial_clevermedal_hyper,		NARC_pst_gra_ribon_35_NCGR, 3,	mes_ribbon_name_047,	mes_ribbon_text_047 },	//かしこさ勲章(ハイパー)トライアル
	{ ID_PARA_trial_clevermedal_master,		NARC_pst_gra_ribon_36_NCGR, 3,	mes_ribbon_name_048,	mes_ribbon_text_048 },	//かしこさ勲章(マスター)トライアル

	{ ID_PARA_trial_strongmedal_normal,		NARC_pst_gra_ribon_33_NCGR, 4,	mes_ribbon_name_049,	mes_ribbon_text_049 },	//たくましさ勲章(ノーマル)トライアル
	{ ID_PARA_trial_strongmedal_super,		NARC_pst_gra_ribon_34_NCGR, 4,	mes_ribbon_name_050,	mes_ribbon_text_050 },	//たくましさ勲章(スーパー)トライアル
	{ ID_PARA_trial_strongmedal_hyper,		NARC_pst_gra_ribon_35_NCGR, 4,	mes_ribbon_name_051,	mes_ribbon_text_051 },	//たくましさ勲章(ハイパー)トライアル
	{ ID_PARA_trial_strongmedal_master,		NARC_pst_gra_ribon_36_NCGR, 4,	mes_ribbon_name_052,	mes_ribbon_text_052 },	//たくましさ勲章(マスター)トライアル

	{ ID_PARA_sinou_battle_tower_ttwin_first,		NARC_pst_gra_ribon_53_NCGR, 0,	mes_ribbon_name_053,	mes_ribbon_text_053 },	//シンオウバトルタワータワータイクーン勝利1回目
	{ ID_PARA_sinou_battle_tower_ttwin_second,		NARC_pst_gra_ribon_54_NCGR, 0,	mes_ribbon_name_054,	mes_ribbon_text_054 },	//シンオウバトルタワータワータイクーン勝利2回目
	{ ID_PARA_sinou_battle_tower_2vs2_win50,		NARC_pst_gra_ribon_55_NCGR, 0,	mes_ribbon_name_055,	mes_ribbon_text_055 },	//シンオウバトルタワータワーダブル50連勝
	{ ID_PARA_sinou_battle_tower_aimulti_win50,		NARC_pst_gra_ribon_56_NCGR, 0,	mes_ribbon_name_056,	mes_ribbon_text_056 },	//シンオウバトルタワータワーAIマルチ50連勝
	{ ID_PARA_sinou_battle_tower_siomulti_win50,	NARC_pst_gra_ribon_57_NCGR, 0,	mes_ribbon_name_057,	mes_ribbon_text_057 },	//シンオウバトルタワータワー通信マルチ50連勝
	{ ID_PARA_sinou_battle_tower_wifi_rank5,		NARC_pst_gra_ribon_58_NCGR, 0,	mes_ribbon_name_058,	mes_ribbon_text_058 },	//シンオウバトルタワーWifiランク５入り

	{ ID_PARA_sinou_syakki_ribbon,			NARC_pst_gra_ribon_59_NCGR, 2,	mes_ribbon_name_059,	mes_ribbon_text_059 },	//シンオウしゃっきリボン
	{ ID_PARA_sinou_dokki_ribbon,			NARC_pst_gra_ribon_60_NCGR, 0,	mes_ribbon_name_060,	mes_ribbon_text_060 },	//シンオウどっきリボン
	{ ID_PARA_sinou_syonbo_ribbon,			NARC_pst_gra_ribon_61_NCGR, 1,	mes_ribbon_name_061,	mes_ribbon_text_061 },	//シンオウしょんぼリボン
	{ ID_PARA_sinou_ukka_ribbon,			NARC_pst_gra_ribon_62_NCGR, 2,	mes_ribbon_name_062,	mes_ribbon_text_062 },	//シンオウうっかリボン
	{ ID_PARA_sinou_sukki_ribbon,			NARC_pst_gra_ribon_63_NCGR, 3,	mes_ribbon_name_063,	mes_ribbon_text_063 },	//シンオウすっきリボン
	{ ID_PARA_sinou_gussu_ribbon,			NARC_pst_gra_ribon_64_NCGR, 0,	mes_ribbon_name_064,	mes_ribbon_text_064 },	//シンオウぐっすリボン
	{ ID_PARA_sinou_nikko_ribbon,			NARC_pst_gra_ribon_65_NCGR, 2,	mes_ribbon_name_065,	mes_ribbon_text_065 },	//シンオウにっこリボン
	{ ID_PARA_sinou_gorgeous_ribbon,		NARC_pst_gra_ribon_66_NCGR, 1,	mes_ribbon_name_066,	mes_ribbon_text_066 },	//シンオウゴージャスリボン
	{ ID_PARA_sinou_royal_ribbon,			NARC_pst_gra_ribon_67_NCGR, 3,	mes_ribbon_name_067,	mes_ribbon_text_067 },	//シンオウロイヤルリボン
	{ ID_PARA_sinou_gorgeousroyal_ribbon,	NARC_pst_gra_ribon_68_NCGR, 0,	mes_ribbon_name_068,	mes_ribbon_text_068 },	//シンオウゴージャスロイヤルリボン
	{ ID_PARA_sinou_ashiato_ribbon,			NARC_pst_gra_ribon_69_NCGR, 0,	mes_ribbon_name_069,	mes_ribbon_text_069 },	//シンオウあしあとリボン
	{ ID_PARA_sinou_record_ribbon,			NARC_pst_gra_ribon_70_NCGR, 1,	mes_ribbon_name_070,	mes_ribbon_text_070 },	//シンオウレコードリボン
	{ ID_PARA_sinou_history_ribbon,			NARC_pst_gra_ribon_71_NCGR, 3,	mes_ribbon_name_071,	mes_ribbon_text_071 },	//シンオウヒストリーリボン
	{ ID_PARA_sinou_legend_ribbon,			NARC_pst_gra_ribon_72_NCGR, 0,	mes_ribbon_name_072,	mes_ribbon_text_072 },	//シンオウレジェンドリボン
	{ ID_PARA_sinou_red_ribbon,				NARC_pst_gra_ribon_73_NCGR, 0,	mes_ribbon_name_073,	MSG_SP_RIBBON+7 },		//シンオウレッドリボン
	{ ID_PARA_sinou_green_ribbon,			NARC_pst_gra_ribon_74_NCGR, 3,	mes_ribbon_name_074,	MSG_SP_RIBBON+8 },		//シンオウグリーンリボン
	{ ID_PARA_sinou_blue_ribbon,			NARC_pst_gra_ribon_75_NCGR, 1,	mes_ribbon_name_075,	MSG_SP_RIBBON+9 },		//シンオウブルーリボン
	{ ID_PARA_sinou_festival_ribbon,		NARC_pst_gra_ribon_76_NCGR, 1,	mes_ribbon_name_076,	MSG_SP_RIBBON+10 },		//シンオウフェスティバルリボン
	{ ID_PARA_sinou_carnival_ribbon,		NARC_pst_gra_ribon_77_NCGR, 0,	mes_ribbon_name_077,	MSG_SP_RIBBON+11 },		//シンオウカーニバルリボン
	{ ID_PARA_sinou_classic_ribbon,			NARC_pst_gra_ribon_78_NCGR, 1,	mes_ribbon_name_078,	MSG_SP_RIBBON+12 },		//シンオウクラシックリボン
	{ ID_PARA_sinou_premiere_ribbon,		NARC_pst_gra_ribon_79_NCGR, 0,	mes_ribbon_name_079,	MSG_SP_RIBBON+13 },		//シンオウプレミアリボン
};



//--------------------------------------------------------------------------------------------
/**
 * リボンデータ取得
 *
 * @param	dat_id		データ番号
 * @param	prm_id		取得パラメータID
 *
 * @return	指定パラメータ
 */
//--------------------------------------------------------------------------------------------
u32 RIBBON_DataGet( u8 dat_id, u8 prm_id )
{
	switch( prm_id ){
	case RIBBON_PARA_POKEPARA:	// PokeParaGetの取得ID
		return RibbonTable[dat_id].pp_id;

	case RIBBON_PARA_GRAPHIC:	// グラフィックID
		return RibbonTable[dat_id].graphic;

	case RIBBON_PARA_PALNUM:	// パレット番号
		return RibbonTable[dat_id].pal_num;

	case RIBBON_PARA_NAME:		// リボン名
		return RibbonTable[dat_id].name;

	case RIBBON_PARA_INFO:		// リボン説明
		return RibbonTable[dat_id].info;
	}

	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * リボン説明取得
 *
 * @param	sv			セーブデータ
 * @param	dat_id		データ番号
 *
 * @return	リボン説明メッセージインデックス
 */
//--------------------------------------------------------------------------------------------
u32	RIBBON_InfoGet( u8 * sv, u8 dat_id )
{
	if( RibbonTable[dat_id].info & MSG_SP_RIBBON ){
		return ( mes_ribbon_haihu_text_000 + sv[ RibbonTable[dat_id].info & 0xff ] );
	}
	return RibbonTable[dat_id].info;
}

//--------------------------------------------------------------------------------------------
/**
 * リボンIDから説明が格納されている位置を取得
 *
 * @param	dat_id		データ番号
 *
 * @retval	"0xff = 配布リボン以外"
 * @retval	"0xff != 格納位置"
 */
//--------------------------------------------------------------------------------------------
u8 RIBBON_SaveIndexGet( u8 dat_id )
{
	if( RibbonTable[dat_id].info & MSG_SP_RIBBON ){
		return ( RibbonTable[dat_id].info & 0xff );
	}
	return 0xff;
}
