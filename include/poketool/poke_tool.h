
//============================================================================================
/**
 * @file	poke_tool.h
 * @bfief	ポケモンパラメータツール郡
 * @author	HisashiSogabe
 * @date	05.05.31
 */
//============================================================================================

#ifndef	__POKE_TOOL_H_
#define	__POKE_TOOL_H_

//	PokeGraArcDataGetの引数のdefine定義（POKEMON_PARAMのID_PARA_sexに入っている性別定義）
#define	PARA_MALE		(0)		///<オス
#define	PARA_FEMALE		(1)		///<メス
#define	PARA_UNK		(2)		///<性別なし

#define	PARA_BACK		(0)		///<背面
#define	PARA_FRONT		(2)		///<正面

#define	PARA_NORMAL		(0)		///<ノーマルカラー
#define	PARA_RARE		(1)		///<レアカラー

//PokePrgAnmDataSetに関する定義
#define	PARA_HFLIP_OFF	(0)		///<HFLIPなし
#define	PARA_HFLIP_ON	(1)		///<HFLIPあり

//努力値に関する定義
#define	PARA_EXP_TOTAL_MAX	(510)		//6個のパラメータの合計値のMAX
#define	PARA_EXP_ITEM_MAX	(100)		//アイテムで上昇できる限界値
#define	PARA_EXP_MAX		(255)		//6個のパラメータのMAX

// マーキングに関する定義
#define POKEPARA_MARKING_ELEMS_MAX	(6)	///< マーキングに使用する記号の総数

// 技覚えテーブルに関する定義
#define LEVELUPWAZA_OBOE_MAX	( 44     )	///<（技20個＋終端コード:1+4バイト境界補正:1）* 2バイト
#define LEVELUPWAZA_OBOE_END	( 0xffff )
#define LEVELUPWAZA_LEVEL_MASK  ( 0xfe00 )
#define LEVELUPWAZA_WAZA_MASK   ( 0x01ff )
#define LEVELUPWAZA_LEVEL_SHIFT (      9 )

//PokeItemSetのrange引数定義
#define	ITEM_RANGE_NORMAL		(0)	//通常確率
#define	ITEM_RANGE_HUKUGAN		(1)	//特性ふくがん効果確率

//バトルタワーで勝負に参加できないポケモンの種類数
#define BTOWER_EXPOKE_NUM	(18)

//アセンブラでincludeされている場合は、下の宣言を無視できるようにifndefで囲んである
#ifndef	__ASM_NO_DEF_

#include	"system/softsprite.h"
#include	"savedata/mystatus.h"

//ポケモンプログラムアニメ
typedef struct POKE_ANIME_SYS_tag * POKE_ANM_SYS_PTR;
typedef struct PERAPVOICE PERAPVOICE;
typedef struct _POKEPARTY POKEPARTY;

//	文字列関連の長さ定義
#include "system/gamedata.h"

//パーソナルデータの色定義
enum{
	COLOR_RED=0,		//赤
	COLOR_BLUE,			//青
	COLOR_YELLOW,		//黄
	COLOR_GREEN,		//緑
	COLOR_BLACK,		//黒
	COLOR_BROWN,		//茶
	COLOR_PERPLE,		//紫
	COLOR_GRAY,			//灰
	COLOR_WHITE,		//白
	COLOR_PINK,			//桃
};

//なつき計算
enum{
	FRIEND_LEVELUP=0,		//レベルアップ
	FRIEND_PARAEXP_ITEM,	//努力値アイテム	
	FRIEND_BATTLE_ITEM,		//戦闘中アイテム
	FRIEND_BOSS_BATTLE,		//ボス戦闘	
	FRIEND_WAZA_MACHINE,	//技マシン使用
	FRIEND_TSUREARUKI,		//連れ歩き	
	FRIEND_HINSHI,			//瀕死
	FRIEND_DOKU_HINSHI,		//毒による瀕死
	FRIEND_LEVEL30_HINSHI,	//レベル差30以上の瀕死
	FRIEND_CONTEST_VICTORY,	//コンテスト優勝
};

///<ボックスポケモン分の構造体
typedef struct pokemon_paso_param POKEMON_PASO_PARAM;
typedef struct pokemon_paso_param1 POKEMON_PASO_PARAM1;
typedef struct pokemon_paso_param2 POKEMON_PASO_PARAM2;
typedef struct pokemon_paso_param3 POKEMON_PASO_PARAM3;
typedef struct pokemon_paso_param4 POKEMON_PASO_PARAM4;

typedef struct pokemon_para_data11 POKEMON_PARA_DATA11;
typedef struct pokemon_para_data12 POKEMON_PARA_DATA12;
typedef struct pokemon_para_data13 POKEMON_PARA_DATA13;
typedef struct pokemon_para_data14 POKEMON_PARA_DATA14;
typedef struct pokemon_para_data15 POKEMON_PARA_DATA15;
typedef struct pokemon_para_data16 POKEMON_PARA_DATA16;
typedef struct pokemon_para_data21 POKEMON_PARA_DATA21;
typedef struct pokemon_para_data22 POKEMON_PARA_DATA22;
typedef struct pokemon_para_data23 POKEMON_PARA_DATA23;
typedef struct pokemon_para_data24 POKEMON_PARA_DATA24;
typedef struct pokemon_para_data25 POKEMON_PARA_DATA25;
typedef struct pokemon_para_data26 POKEMON_PARA_DATA26;
typedef struct pokemon_para_data31 POKEMON_PARA_DATA31;
typedef struct pokemon_para_data32 POKEMON_PARA_DATA32;
typedef struct pokemon_para_data33 POKEMON_PARA_DATA33;
typedef struct pokemon_para_data34 POKEMON_PARA_DATA34;
typedef struct pokemon_para_data35 POKEMON_PARA_DATA35;
typedef struct pokemon_para_data36 POKEMON_PARA_DATA36;
typedef struct pokemon_para_data41 POKEMON_PARA_DATA41;
typedef struct pokemon_para_data42 POKEMON_PARA_DATA42;
typedef struct pokemon_para_data43 POKEMON_PARA_DATA43;
typedef struct pokemon_para_data44 POKEMON_PARA_DATA44;
typedef struct pokemon_para_data45 POKEMON_PARA_DATA45;
typedef struct pokemon_para_data46 POKEMON_PARA_DATA46;

///<ボックスポケモン分以外の構造体
typedef struct pokemon_calc_param POKEMON_CALC_PARAM;

///<手持ちポケモンの構造体
typedef struct pokemon_param POKEMON_PARAM;

///<ポケモンパラメータデータ取得のためのインデックス
enum{
	ID_PARA_personal_rnd=0,						//個性乱数
	ID_PARA_pp_fast_mode,						//
	ID_PARA_ppp_fast_mode,						//
	ID_PARA_fusei_tamago_flag,					//ダメタマゴフラグ
	ID_PARA_checksum,							//チェックサム

	ID_PARA_monsno,								//モンスターナンバー
	ID_PARA_item,								//所持アイテムナンバー
	ID_PARA_id_no,								//IDNo
	ID_PARA_exp,								//経験値
	ID_PARA_friend,								//なつき度
	ID_PARA_speabino,							//特殊能力
	ID_PARA_mark,								//ポケモンにつけるマーク（ボックス）
	ID_PARA_country_code,						//国コード
	ID_PARA_hp_exp,								//HP努力値
	ID_PARA_pow_exp,							//攻撃力努力値
	ID_PARA_def_exp,							//防御力努力値
	ID_PARA_agi_exp,							//素早さ努力値
	ID_PARA_spepow_exp,							//特攻努力値
	ID_PARA_spedef_exp,							//特防努力値
	ID_PARA_style,								//かっこよさ
	ID_PARA_beautiful,							//うつくしさ
	ID_PARA_cute,								//かわいさ
	ID_PARA_clever,								//かしこさ
	ID_PARA_strong,								//たくましさ
	ID_PARA_fur,								//毛艶
	ID_PARA_sinou_champ_ribbon,					//シンオウチャンプリボン
	ID_PARA_sinou_battle_tower_ttwin_first,		//シンオウバトルタワータワータイクーン勝利1回目
	ID_PARA_sinou_battle_tower_ttwin_second,	//シンオウバトルタワータワータイクーン勝利2回目
	ID_PARA_sinou_battle_tower_2vs2_win50,		//シンオウバトルタワータワーダブル50連勝
	ID_PARA_sinou_battle_tower_aimulti_win50,	//シンオウバトルタワータワーAIマルチ50連勝
	ID_PARA_sinou_battle_tower_siomulti_win50,	//シンオウバトルタワータワー通信マルチ50連勝
	ID_PARA_sinou_battle_tower_wifi_rank5,		//シンオウバトルタワーWifiランク５入り
	ID_PARA_sinou_syakki_ribbon,				//シンオウしゃっきリボン
	ID_PARA_sinou_dokki_ribbon,					//シンオウどっきリボン
	ID_PARA_sinou_syonbo_ribbon,				//シンオウしょんぼリボン
	ID_PARA_sinou_ukka_ribbon,					//シンオウうっかリボン
	ID_PARA_sinou_sukki_ribbon,					//シンオウすっきリボン
	ID_PARA_sinou_gussu_ribbon,					//シンオウぐっすリボン
	ID_PARA_sinou_nikko_ribbon,					//シンオウにっこリボン
	ID_PARA_sinou_gorgeous_ribbon,				//シンオウゴージャスリボン
	ID_PARA_sinou_royal_ribbon,					//シンオウロイヤルリボン
	ID_PARA_sinou_gorgeousroyal_ribbon,			//シンオウゴージャスロイヤルリボン
	ID_PARA_sinou_ashiato_ribbon,				//シンオウあしあとリボン
	ID_PARA_sinou_record_ribbon,				//シンオウレコードリボン
	ID_PARA_sinou_history_ribbon,				//シンオウヒストリーリボン
	ID_PARA_sinou_legend_ribbon,				//シンオウレジェンドリボン
	ID_PARA_sinou_red_ribbon,					//シンオウレッドリボン
	ID_PARA_sinou_green_ribbon,					//シンオウグリーンリボン
	ID_PARA_sinou_blue_ribbon,					//シンオウブルーリボン
	ID_PARA_sinou_festival_ribbon,				//シンオウフェスティバルリボン
	ID_PARA_sinou_carnival_ribbon,				//シンオウカーニバルリボン
	ID_PARA_sinou_classic_ribbon,				//シンオウクラシックリボン
	ID_PARA_sinou_premiere_ribbon,				//シンオウプレミアリボン
	ID_PARA_sinou_amari_ribbon,					//あまり

	ID_PARA_waza1,								//所持技1
	ID_PARA_waza2,								//所持技2
	ID_PARA_waza3,								//所持技3
	ID_PARA_waza4,								//所持技4
	ID_PARA_pp1,								//所持技PP1
	ID_PARA_pp2,								//所持技PP2
	ID_PARA_pp3,								//所持技PP3
	ID_PARA_pp4,								//所持技PP4
	ID_PARA_pp_count1,							//所持技PP_COUNT1
	ID_PARA_pp_count2,							//所持技PP_COUNT2
	ID_PARA_pp_count3,							//所持技PP_COUNT3
	ID_PARA_pp_count4,							//所持技PP_COUNT4
	ID_PARA_pp_max1,							//所持技PPMAX1
	ID_PARA_pp_max2,							//所持技PPMAX2
	ID_PARA_pp_max3,							//所持技PPMAX3
	ID_PARA_pp_max4,							//所持技PPMAX4
	ID_PARA_hp_rnd,								//HP乱数
	ID_PARA_pow_rnd,							//攻撃力乱数
	ID_PARA_def_rnd,							//防御力乱数
	ID_PARA_agi_rnd,							//素早さ乱数
	ID_PARA_spepow_rnd,							//特攻乱数
	ID_PARA_spedef_rnd,							//特防乱数
	ID_PARA_tamago_flag,						//タマゴフラグ
	ID_PARA_nickname_flag,						//ニックネームをつけたかどうかフラグ
	ID_PARA_stylemedal_normal,					//かっこよさ勲章(ノーマル)AGBコンテスト
	ID_PARA_stylemedal_super,					//かっこよさ勲章(スーパー)AGBコンテスト
	ID_PARA_stylemedal_hyper,					//かっこよさ勲章(ハイパー)AGBコンテスト
	ID_PARA_stylemedal_master,					//かっこよさ勲章(マスター)AGBコンテスト
	ID_PARA_beautifulmedal_normal,				//うつくしさ勲章(ノーマル)AGBコンテスト
	ID_PARA_beautifulmedal_super,				//うつくしさ勲章(スーパー)AGBコンテスト
	ID_PARA_beautifulmedal_hyper,				//うつくしさ勲章(ハイパー)AGBコンテスト
	ID_PARA_beautifulmedal_master,				//うつくしさ勲章(マスター)AGBコンテスト
	ID_PARA_cutemedal_normal,					//かわいさ勲章(ノーマル)AGBコンテスト
	ID_PARA_cutemedal_super,					//かわいさ勲章(スーパー)AGBコンテスト
	ID_PARA_cutemedal_hyper,					//かわいさ勲章(ハイパー)AGBコンテスト
	ID_PARA_cutemedal_master,					//かわいさ勲章(マスター)AGBコンテスト
	ID_PARA_clevermedal_normal,					//かしこさ勲章(ノーマル)AGBコンテスト
	ID_PARA_clevermedal_super,					//かしこさ勲章(スーパー)AGBコンテスト
	ID_PARA_clevermedal_hyper,					//かしこさ勲章(ハイパー)AGBコンテスト
	ID_PARA_clevermedal_master,					//かしこさ勲章(マスター)AGBコンテスト
	ID_PARA_strongmedal_normal,					//たくましさ勲章(ノーマル)AGBコンテスト
	ID_PARA_strongmedal_super,					//たくましさ勲章(スーパー)AGBコンテスト
	ID_PARA_strongmedal_hyper,					//たくましさ勲章(ハイパー)AGBコンテスト
	ID_PARA_strongmedal_master,					//たくましさ勲章(マスター)AGBコンテスト
	ID_PARA_champ_ribbon,						//チャンプリボン
	ID_PARA_winning_ribbon,						//ウィニングリボン
	ID_PARA_victory_ribbon,						//ビクトリーリボン
	ID_PARA_bromide_ribbon,						//ブロマイドリボン
	ID_PARA_ganba_ribbon,						//がんばリボン
	ID_PARA_marine_ribbon,						//マリンリボン
	ID_PARA_land_ribbon,						//ランドリボン
	ID_PARA_sky_ribbon,							//スカイリボン
	ID_PARA_country_ribbon,						//カントリーリボン
	ID_PARA_national_ribbon,					//ナショナルリボン
	ID_PARA_earth_ribbon,						//アースリボン
	ID_PARA_world_ribbon,						//ワールドリボン
	ID_PARA_event_get_flag,						//イベントで配布されたことを示すフラグ
	ID_PARA_sex,								//性別
	ID_PARA_form_no,							//形状ナンバー（アンノーン、デオキシス、ミノメスなど用）
	ID_PARA_dummy_p2_1,							//あまり
	ID_PARA_dummy_p2_2,							//あまり
	ID_PARA_dummy_p2_3,							//あまり

	ID_PARA_nickname,							//ニックネーム
	ID_PARA_nickname_code_flag,					//ニックネーム（STRCODE使用,nickname_flagもオンにする）
	ID_PARA_nickname_buf,						//ニックネーム（STRBUF使用）
	ID_PARA_nickname_buf_flag,					//ニックネーム（STRBUF使用,nickname_flagもオンにする）
	ID_PARA_pref_code,							//都道府県コード
	ID_PARA_get_cassette,						//捕まえたカセット（カラーバージョン）
	ID_PARA_trial_stylemedal_normal,			//かっこよさ勲章(ノーマル)トライアル
	ID_PARA_trial_stylemedal_super,				//かっこよさ勲章(スーパー)トライアル
	ID_PARA_trial_stylemedal_hyper,				//かっこよさ勲章(ハイパー)トライアル
	ID_PARA_trial_stylemedal_master,			//かっこよさ勲章(マスター)トライアル
	ID_PARA_trial_beautifulmedal_normal,		//うつくしさ勲章(ノーマル)トライアル
	ID_PARA_trial_beautifulmedal_super,			//うつくしさ勲章(スーパー)トライアル
	ID_PARA_trial_beautifulmedal_hyper,			//うつくしさ勲章(ハイパー)トライアル
	ID_PARA_trial_beautifulmedal_master,		//うつくしさ勲章(マスター)トライアル
	ID_PARA_trial_cutemedal_normal,				//かわいさ勲章(ノーマル)トライアル
	ID_PARA_trial_cutemedal_super,				//かわいさ勲章(スーパー)トライアル
	ID_PARA_trial_cutemedal_hyper,				//かわいさ勲章(ハイパー)トライアル
	ID_PARA_trial_cutemedal_master,				//かわいさ勲章(マスター)トライアル
	ID_PARA_trial_clevermedal_normal,			//かしこさ勲章(ノーマル)トライアル
	ID_PARA_trial_clevermedal_super,			//かしこさ勲章(スーパー)トライアル
	ID_PARA_trial_clevermedal_hyper,			//かしこさ勲章(ハイパー)トライアル
	ID_PARA_trial_clevermedal_master,			//かしこさ勲章(マスター)トライアル
	ID_PARA_trial_strongmedal_normal,			//たくましさ勲章(ノーマル)トライアル
	ID_PARA_trial_strongmedal_super,			//たくましさ勲章(スーパー)トライアル
	ID_PARA_trial_strongmedal_hyper,			//たくましさ勲章(ハイパー)トライアル
	ID_PARA_trial_strongmedal_master,			//たくましさ勲章(マスター)トライアル
	ID_PARA_amari_ribbon,						//余りリボン

	ID_PARA_oyaname,							//親の名前
	ID_PARA_oyaname_buf,						//親の名前（STRBUF使用）
	ID_PARA_get_year,							//捕まえた年
	ID_PARA_get_month,							//捕まえた月
	ID_PARA_get_day,							//捕まえた日
	ID_PARA_birth_year,							//生まれた年
	ID_PARA_birth_month,						//生まれた月
	ID_PARA_birth_day,							//生まれた日
	ID_PARA_get_place,							//捕まえた場所
	ID_PARA_birth_place,						//生まれた場所
	ID_PARA_pokerus,							//ポケルス
	ID_PARA_get_ball,							//捕まえたボール
	ID_PARA_get_level,							//捕まえたレベル
	ID_PARA_oyasex,								//親の性別
	ID_PARA_get_ground_id,						//捕まえた場所の地形アトリビュート（ミノッチ用）
	ID_PARA_dummy_p4_1,							//あまり

	ID_PARA_condition,							//コンディション
	ID_PARA_level,								//レベル
	ID_PARA_cb_id,								//カスタムボールID
	ID_PARA_hp,									//HP
	ID_PARA_hpmax,								//HPMAX
	ID_PARA_pow,								//攻撃力
	ID_PARA_def,								//防御力
	ID_PARA_agi,								//素早さ
	ID_PARA_spepow,								//特攻
	ID_PARA_spedef,								//特防
	ID_PARA_mail_data,							//メールデータ
	ID_PARA_cb_core,							//カスタムボールデータ
	
	ID_PARA_poke_exist,							//ポケモン存在フラグ
	ID_PARA_tamago_exist,						//タマゴ存在フラグ

	ID_PARA_monsno_egg,							//タマゴかどうかも同時にチェック

	ID_PARA_power_rnd,							//パワー乱数をu32で扱う
	ID_PARA_nidoran_nickname,					//モンスターナンバーがニドランの時にnickname_flagが立っているかチェック

	ID_PARA_type1,								//ポケモンのタイプ１を取得（アウス、マルチタイプチェックもあり）
	ID_PARA_type2,								//ポケモンのタイプ２を取得（アウス、マルチタイプチェックもあり）

	ID_PARA_default_name,						//ポケモンのデフォルト名

	ID_PARA_end									//パラメータを追加するときは、ここから上に追加
};

///<ポケモンパーソナルデータの構造体
typedef struct pokemon_personal_data POKEMON_PERSONAL_DATA;

///<ポケモンパーソナルデータ取得のためのインデックス
enum{
	ID_PER_basic_hp=0,			//基本ＨＰ
	ID_PER_basic_pow,			//基本攻撃力
	ID_PER_basic_def,			//基本防御力
	ID_PER_basic_agi,			//基本素早さ
	ID_PER_basic_spepow,		//基本特殊攻撃力
	ID_PER_basic_spedef,		//基本特殊防御力
	ID_PER_type1,				//属性１
	ID_PER_type2,				//属性２
	ID_PER_get_rate,			//捕獲率
	ID_PER_give_exp,			//贈与経験値
	ID_PER_pains_hp,			//贈与努力値ＨＰ
	ID_PER_pains_pow,			//贈与努力値攻撃力
	ID_PER_pains_def,			//贈与努力値防御力
	ID_PER_pains_agi,			//贈与努力値素早さ
	ID_PER_pains_spepow,		//贈与努力値特殊攻撃力
	ID_PER_pains_spedef,		//贈与努力値特殊防御力
	ID_PER_item1,				//アイテム１
	ID_PER_item2,				//アイテム２
	ID_PER_sex,					//性別ベクトル
	ID_PER_egg_birth,			//タマゴの孵化歩数
	ID_PER_friend,				//なつき度初期値
	ID_PER_grow,				//成長曲線識別
	ID_PER_egg_group1,			//こづくりグループ1
	ID_PER_egg_group2,			//こづくりグループ2
	ID_PER_speabi1,				//特殊能力１
	ID_PER_speabi2,				//特殊能力２
	ID_PER_escape,				//逃げる率
	ID_PER_color,				//色（図鑑で使用）
	ID_PER_reverse,				//反転フラグ
	ID_PER_machine1,			//技マシンフラグ１
	ID_PER_machine2,			//技マシンフラグ２
	ID_PER_machine3,			//技マシンフラグ３
	ID_PER_machine4				//技マシンフラグ４
};

//	ポケモンの性別定義（パーソナル上のオスメス比率）(1～253でオスメスの比率が変わる）
#define	MONS_MALE		(0)				///<オスのみ
#define	MONS_FEMALE		(254)			///<メスのみ
#define	MONS_UNKNOWN	(255)			///<性別なし

#define	POW_RND			(32)		//PokeParaSetを使うときにパワー乱数をランダムでとるための値
#define	RND_NO_SET		(0)			//PokeParaSetを使うときに個性乱数をランダムでセットするための値
#define	RND_SET			(1)			//PokeParaSetを使うときに個性乱数を固定値でセットするための値
#define	ID_NO_SET		(0)			//PokeParaSetを使うときにIDをランダムでセットするための値
#define	ID_SET			(1)			//PokeParaSetを使うときにIDを固定値でセットするための値
#define	ID_NO_RARE		(2)			//PokeParaSetを使うときにIDを個性乱数との組み合わせでレアが出ないようにするの値
#define	NO_WAZA_SET		(0xffff)	//技のセットができなかったときの返り値
#define	SAME_WAZA_SET	(0xfffe)	//すでに覚えていた技のときの返り値

///<ポケモン進化データの構造体
typedef struct pokemon_shinka_data POKEMON_SHINKA_DATA;

typedef struct pokemon_shinka_table POKEMON_SHINKA_TABLE;

enum{
	ID_EVO_Cond=0,
	ID_EVO_Data,
	ID_EVO_Mons
};

//ポケモンパラメータ取得系の定義
enum{
	ID_POKEPARADATA11=0,	//0
	ID_POKEPARADATA12,		//1
	ID_POKEPARADATA13,		//2
	ID_POKEPARADATA14,		//3
	ID_POKEPARADATA15,		//4
	ID_POKEPARADATA16,		//5
	ID_POKEPARADATA21,		//6
	ID_POKEPARADATA22,		//7
	ID_POKEPARADATA23,		//8
	ID_POKEPARADATA24,		//9
	ID_POKEPARADATA25,		//10
	ID_POKEPARADATA26,		//11
	ID_POKEPARADATA31,		//12
	ID_POKEPARADATA32,		//13
	ID_POKEPARADATA33,		//14
	ID_POKEPARADATA34,		//15
	ID_POKEPARADATA35,		//16
	ID_POKEPARADATA36,		//17
	ID_POKEPARADATA41,		//18
	ID_POKEPARADATA42,		//19
	ID_POKEPARADATA43,		//20
	ID_POKEPARADATA44,		//21
	ID_POKEPARADATA45,		//22
	ID_POKEPARADATA46,		//23

	ID_POKEPARADATA51,		//24
	ID_POKEPARADATA52,		//25
	ID_POKEPARADATA53,		//26
	ID_POKEPARADATA54,		//27
	ID_POKEPARADATA55,		//28
	ID_POKEPARADATA56,		//29

	ID_POKEPARADATA61,		//30
	ID_POKEPARADATA62,		//31
};

enum{
	ID_POKEPARA1=0,
	ID_POKEPARA2,
	ID_POKEPARA3,
	ID_POKEPARA4,
};

enum{
	UNK_A=0,
	UNK_B,
	UNK_C,
	UNK_D,
	UNK_E,
	UNK_F,
	UNK_G,
	UNK_H,
	UNK_I,
	UNK_J,
	UNK_K,
	UNK_L,
	UNK_M,
	UNK_N,
	UNK_O,
	UNK_P,
	UNK_Q,
	UNK_R,
	UNK_S,
	UNK_T,
	UNK_U,
	UNK_V,
	UNK_W,
	UNK_X,
	UNK_Y,
	UNK_Z,
	UNK_ENC,
	UNK_QUE,
	UNK_END
};

//extern宣言
extern	void	PokeParaInit(POKEMON_PARAM *pp);
extern	void	PokePasoParaInit(POKEMON_PASO_PARAM *ppp);

extern	int		PokemonParam_GetWorkSize(void);
extern	POKEMON_PARAM	*PokemonParam_AllocWork(u32 heapID);

extern	BOOL	PokeParaFastModeOn(POKEMON_PARAM *pp);
extern	BOOL	PokeParaFastModeOff(POKEMON_PARAM *pp,BOOL flag);
extern	BOOL	PokePasoParaFastModeOn(POKEMON_PASO_PARAM *ppp);
extern	BOOL	PokePasoParaFastModeOff(POKEMON_PASO_PARAM *ppp,BOOL flag);

extern	void	PokeParaSet(POKEMON_PARAM *pp,int mons_no,int level,int pow,int rndflag,u32 rnd,int idflag,u32 id);
extern	void	PokePasoParaSet(POKEMON_PASO_PARAM *ppp,int mons_no,int level,int pow,int rndflag,u32 rnd,int idflag,u32 id);
extern	void	PokeParaSetChr(POKEMON_PARAM *,u16,u8,u8,u8);
extern	void	PokeParaSetSexChr(POKEMON_PARAM *,u16,u8,u8,u8,u8,u8);
extern	u32		PokeParaSexChrRndGet(u16 mons_no,u8 sex,u8 chr);
extern	void	PokeParaSetPowRnd(POKEMON_PARAM *,u16,u8,u32,u32);
extern	void	PokeParaSetPowRndBuf(POKEMON_PARAM *,u16,u8,u8*,u32);
extern	void	PokeParaSetParaExp(POKEMON_PARAM *,u16,u8,u8,u8);
extern	void	PokeParaSetBattleFrontier(POKEMON_PARAM *pp,u16 pokeno,u8 pokelevel,u8 chr,u8 pow,u8 expbit,u32 id);
extern	void	PokeParaCalc(POKEMON_PARAM *pp);
extern	void	PokeParaCalcLevelUp(POKEMON_PARAM *pp);

extern	u32		PokeParaGet(POKEMON_PARAM *pp,int id,void *buf);
//extern	u32		PokeParaGetFast(POKEMON_PARAM *pp,int id,void *buf);
extern	u32		PokePasoParaGet(POKEMON_PASO_PARAM *ppp,int id,void *buf);
//extern	u32		PokePasoParaGetFast(POKEMON_PASO_PARAM *ppp,int id,void *buf);
extern	void	PokeParaPut(POKEMON_PARAM *pp,int id,const void *buf);
//extern	void	PokeParaPutFast(POKEMON_PARAM *pp,int id,const void *buf);
extern	void	PokePasoParaPut(POKEMON_PASO_PARAM *ppp,int id,const void *buf);
//extern	void	PokePasoParaPutFast(POKEMON_PASO_PARAM *ppp,int id,const void *buf);
extern	void	PokeParaAdd(POKEMON_PARAM *pp,int id,int value);
//extern	void	PokeParaAddFast(POKEMON_PARAM *pp,int id,int value);
extern	void	PokePasoParaAdd(POKEMON_PASO_PARAM *ppp,int id,int value);
//extern	void	PokePasoParaAddFast(POKEMON_PASO_PARAM *ppp,int id,int value);

extern	u32		PokeParaPersonalParaGet(POKEMON_PARAM *pp,int para);
extern	u32		PokePasoParaPersonalParaGet(POKEMON_PASO_PARAM *ppp,int para);
extern	u32		PokeFormNoPersonalParaGet(int mons_no,int form_no,int para);

extern	u32		PokePersonalParaGet(int mons_no,int para);

extern POKEMON_PERSONAL_DATA *PokePersonalPara_Open( int mons_no, int HeapID );
extern u32      PokePersonalPara_Get( POKEMON_PERSONAL_DATA *ppd, int para );
extern void     PokePersonalPara_Close( POKEMON_PERSONAL_DATA *ppd );

extern	u8		PokeParaNextLevelExpRatioGet(POKEMON_PARAM *pp);

extern	u32		PokeParaNextLevelExpGet(POKEMON_PARAM *pp);
extern	u32		PokePasoParaNextLevelExpGet(POKEMON_PASO_PARAM *ppp);

extern	u32		PokeParaLevelExpGet(POKEMON_PARAM *pp);
extern	u32		PokeLevelExpGet(int	mons_no,int level);
extern	u8		PokeSexGet(POKEMON_PARAM *pp);
extern	u8		PokePasoSexGet(POKEMON_PASO_PARAM *ppp);
extern	u8		PokeSexGetMonsNo(u16 monsno,u32 rnd);
extern	u8		PokeRareGet(POKEMON_PARAM *pp);
extern	u8		PokePasoRareGet(POKEMON_PASO_PARAM *ppp);
extern	u8		PokeRareGetPara(u32 id,u32 rnd);
extern	u32		PokeRareRndGet(u32 id);
extern  u8		PokeRareGetPara(u32 id,u32 rnd);

extern	u32		PokeParaLevelCalc(POKEMON_PARAM *pp);
extern	u32		PokePasoLevelCalc(POKEMON_PASO_PARAM *ppp);
extern	u32		PokeLevelCalc(u16 mons_no,u32 exp);

extern	u8		PokeSeikakuGet(POKEMON_PARAM *pp);
extern	u8		PokePasoSeikakuGet(POKEMON_PASO_PARAM *ppp);
extern	u8		PokeSeikakuGetRnd(u32 rnd);

extern	void	PokeGraArcDataGetPP(SOFT_SPRITE_ARC *ssa,POKEMON_PARAM *pp,u8 dir);
extern	void	PokeGraArcDataGetPPP(SOFT_SPRITE_ARC *ssa,POKEMON_PASO_PARAM *ppp,u8 dir);
extern	void	PokeGraArcDataGet(SOFT_SPRITE_ARC *ssa,u16 mons_no,u8 sex,u8 dir,u8 col,u8 form_no,u32 rnd);
extern	u8		PokeParaHeightGet(POKEMON_PARAM *pp,u8 dir);
extern	u8		PokePasoParaHeightGet(POKEMON_PASO_PARAM *ppp,u8 dir);
extern	u8		PokeHeightGet(u16 mons_no,u8 sex,u8 dir,u8 form_no,u32 rnd);
extern	void	TrGraArcDataGet(SOFT_SPRITE_ARC *ssa,u16 trtype,u8 dir,u8 sex);
extern	void	TrTypeGraArcDataGet(SOFT_SPRITE_ARC *ssa,u16 tr_type);
extern	void	PokeAnmDataSet(SOFT_SPRITE_ANIME *ssanm,u16 mons_no);
extern	void	PokePrgAnmDataSet(POKE_ANM_SYS_PTR pasp,SOFT_SPRITE *ss,u16 mons_no,int dir,int chr,int reverse,int index);

extern	u32		PokemonParamSizeGet(void);
extern	u32		PokemonPasoParamSizeGet(void);

extern	u8		PokeParaUnknownFormGet(POKEMON_PARAM *pp);
extern	u8		PokePasoParaUnknownFormGet(POKEMON_PASO_PARAM *ppp);
//extern	u8		PokemonUnknownFormGet(u32 rnd);

//extern	u32		PokemonPasoUnknownFormRndGet(int form);

extern	POKEMON_PASO_PARAM	*PPPPointerGet(POKEMON_PARAM *pp);

extern	u8		PokeLevelUpCheck(POKEMON_PARAM *pp);
extern	u16		PokeShinkaCheck(POKEPARTY *ppt,POKEMON_PARAM *pp,u8 type,u16 itemno,int *shinka_cond);
extern  u16     PokeSearchChild(const u16 monsno);
extern  u16 	PokeChildCheck( const u16 monsno );


extern	u16		PokeParaZenkokuNo2ShinouNo(POKEMON_PARAM *pp);
extern	u16		PokePasoParaZenkokuNo2ShinouNo(POKEMON_PASO_PARAM *ppp);
extern	u16		PokeZenkokuNo2ShinouNo(u16 mons_no);
extern	u16		PokeShinouNo2ZenkokuNo(u16 mons_no);

extern	void	PokeCopyPPtoPP(POKEMON_PARAM *pp_src,POKEMON_PARAM *pp_dest);
extern	void	PokeCopyPPPtoPPP(POKEMON_PASO_PARAM *ppp_src,POKEMON_PASO_PARAM *ppp_dest);
extern	void	PokeCopyPPtoPPP(POKEMON_PARAM *pp_src,POKEMON_PASO_PARAM *ppp_dest);

extern	void	PokeWazaOboe(POKEMON_PARAM *pp);
extern	void	PokePasoWazaOboe(POKEMON_PASO_PARAM *ppp);
extern	u16		PokeWazaSet(POKEMON_PARAM *pp,u16 wazano);
extern	u16		PokePasoWazaSet(POKEMON_PASO_PARAM *ppp,u16 wazano);
extern	void	PokeWazaOboeOshidashi(POKEMON_PARAM *pp,u16 wazano);
extern	void	PokePasoWazaOboeOshidashi(POKEMON_PASO_PARAM *ppp,u16 wazano);
extern	void	PokeWazaSetPos(POKEMON_PARAM *pp,u16 wazano,u8 pos);
extern	void	PokePasoWazaSetPos(POKEMON_PASO_PARAM *ppp,u16 wazano,u8 pos);
extern	u16		PokeWazaOboeCheck(POKEMON_PARAM *pp,int *cnt,u16 *wazano);
extern int PokeOboeruWazaAllGet( int monsno, int form, u16 *wazalist );

extern	void	PokeParaWazaDelPos(POKEMON_PARAM *pp,u32 pos);

extern	s8		PokeParaLikeTasteCheck(POKEMON_PARAM *pp,int taste);
extern	s8		PokePasoParaLikeTasteCheck(POKEMON_PASO_PARAM *ppp,int taste);
extern	s8		PokeLikeTasteCheck(u32 rnd,int taste);

extern	void	PokeParaWazaReplace(POKEMON_PARAM *pp,int src_pos,int dest_pos);
extern	void	PokePasoParaWazaReplace(POKEMON_PASO_PARAM *ppp,int src_pos,int dest_pos);
extern	void	PokeReplace(POKEMON_PASO_PARAM *ppp,POKEMON_PARAM *pp);

typedef struct _POKEPARTY POKEPARTY;

extern	u8		GetStockPokeMaxLevel(POKEPARTY *ppt);
extern	void	PokerusSetCheck(POKEPARTY *ppt);
extern	u8		PokerusCheck(POKEPARTY *ppt,u8 check_bit);
extern	u8		PokerusedCheck(POKEPARTY *ppt,u8 check_bit);
extern	void	PokerusCounterDec(POKEPARTY *ppt,s32 day);
extern	void	PokerusCatchCheck(POKEPARTY *ppt);

extern	BOOL	PokeParaPokerusCheck(POKEMON_PARAM *pp);
extern	BOOL	PokePasoParaPokerusCheck(POKEMON_PASO_PARAM *ppp);
extern	BOOL	PokeParaPokerusedCheck(POKEMON_PARAM *pp);
extern	BOOL	PokePasoParaPokerusedCheck(POKEMON_PASO_PARAM *ppp);

extern	void	PokeParaAusuFormChange(POKEMON_PARAM *pp);
extern	void	PokePasoParaAusuFormChange(POKEMON_PASO_PARAM *ppp);
extern	u8		AusuTypeGet(u16	item_param);

extern	void	PokeWazaOboeDataGet(int monsno,u16 *wot);
extern	void	PokeFormNoWazaOboeDataGet(int monsno,int form_no,u16 *wot);
extern	BOOL	PokeParaWazaHaveCheck(POKEMON_PARAM *pp,u16 waza_no);

extern	void	PokeVoicePlaySet(PERAPVOICE *p_voice,int voice,u16 monsno,int pan,int vol,int flag,int heapID);

extern	void	PokeParaGetInfoSet(POKEMON_PARAM *pp,MYSTATUS *status,int ball,int place,int ground_id,int heapID);
extern	void	PokePasoParaGetInfoSet(POKEMON_PASO_PARAM *ppp,MYSTATUS *status,int ball,int place,int ground_id,int heapID);
extern	void	PokeParaBirthInfoSet(POKEMON_PARAM *pp,MYSTATUS *status,int ball,int place,int ground_id,int heapID);
extern	void	PokePasoParaBirthInfoSet(POKEMON_PASO_PARAM *ppp,MYSTATUS *status,int ball,int place,int ground_id,int heapID);

extern	void	PokeItemSet(POKEMON_PARAM *pp,u32 fight_type,int range);

extern	BOOL	PokeParaWazaMachineCheck(POKEMON_PARAM *pp,u8 machine_no);
extern	BOOL	PokePasoParaWazaMachineCheck(POKEMON_PASO_PARAM *pp,u8 machine_no);
extern	BOOL	PokeWazaMachineCheck(u16 mons_no,int form_no,u8 machine_no);

extern	void	PokeParaSpeabiSet(POKEMON_PARAM *pp);
extern	void	PokePasoParaSpeabiSet(POKEMON_PASO_PARAM *ppp);

extern	void	PokeParaPersonalRndChange(POKEMON_PARAM *pp,u32 personal_rnd);

extern	s8		PokeChrAbiTableGet(u8 chr,u8 cond);

extern	void	FriendCalc(POKEMON_PARAM *pp,u8 id,u16 placeID);

extern	u32		PokePersonal_LevelCalc( POKEMON_PERSONAL_DATA* personalData, u16 monsno, u32 exp );
extern	u8		PokePersonal_SexGet( POKEMON_PERSONAL_DATA* personalData, u16 monsno, u32 rnd );

extern	u32		No2Bit(int no);
extern	int		Bit2No(u32 bit);

extern BOOL BattleTowerExPokeCheck_MonsNo( u16 mons );
extern BOOL BattleTowerExPokeCheck_PokePara( POKEMON_PARAM * pp );
extern u16 BattleTowerExPoke_MonsNoGet(u8 idx);

extern BOOL	PokemonOyaCheckPP( POKEMON_PARAM* pp, MYSTATUS* my, int heapID );
extern BOOL	PokemonOyaCheckPPP( POKEMON_PASO_PARAM* ppp, MYSTATUS* my, int heapID );

extern	int	TrainerBTrTypeGet(int trtype);

extern void PokePara_CustomBallDataInit( POKEMON_PARAM * pp );
extern void PokePasoPara_RecoverPP( POKEMON_PASO_PARAM* ppp );

#endif

#endif	__POKE_TOOL_H_
