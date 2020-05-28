#ifndef __AGBPOKE_TOOL_H__
#define __AGBPOKE_TOOL_H__

#define	MONSNO_AGB_TAMAGO	412

enum{
	ID_AGB_personal_rnd=0,		//個性乱数
	ID_AGB_id_no,			//IDナンバー
	ID_AGB_nickname,		//ニックネーム
	ID_AGB_country_code,		//国コード
	ID_AGB_fusei_tamago_flag,	//データ改ざんによるタマゴ化
	ID_AGB_poke_exist_flag,		//ポケモンの存在フラグ
	ID_AGB_egg_exist_flag,		//ポケモンの存在フラグ
	ID_AGB_oyaname,			//親の名前
	ID_AGB_mark,			//ポケモンにつけるマーク
	ID_AGB_checksum,		//チェックサム
	ID_AGB_amari,   		//続編のための余り領域←この位置を変更するのも禁止
					//ここから上の順番を変更するのは禁止！！

	ID_AGB_monsno,			//モンスターナンバー
	ID_AGB_item,			//所持アイテム
	ID_AGB_waza1,			//技１
	ID_AGB_waza2,			//技２
	ID_AGB_waza3,			//技３
	ID_AGB_waza4,			//技４
	ID_AGB_pp1,			//技ポイント1
	ID_AGB_pp2,			//技ポイント２
	ID_AGB_pp3,			//技ポイント３
	ID_AGB_pp4,			//技ポイント４
	ID_AGB_pp_count,		//技ポイントアップカウンタ
	ID_AGB_style,			//かっこよさ
	ID_AGB_beautiful,		//うつくしさ
	ID_AGB_cute,			//かわいさ
	ID_AGB_exp,			//経験値
	ID_AGB_hp_exp,			//ヒットポイント努力値
	ID_AGB_pow_exp,			//攻撃力努力値
	ID_AGB_def_exp,			//防御力努力値
	ID_AGB_agi_exp,			//素早さ努力値
	ID_AGB_spepow_exp,		//特殊攻撃努力値
	ID_AGB_spedef_exp,		//特殊防御努力値
	ID_AGB_friend,			//なつき度
	ID_AGB_clever,			//かしこさ
	ID_AGB_pokerus,			//ポケルス
	ID_AGB_get_place,		//捕獲場所
	ID_AGB_get_level,		//捕獲レベル
	ID_AGB_get_cassette,		//捕獲カセット
	ID_AGB_get_ball,		//捕獲ボール
	ID_AGB_hp_rnd,			//ヒットポイントパワー乱数
	ID_AGB_pow_rnd,			//攻撃力パワー乱数
	ID_AGB_def_rnd,			//防御力パワー乱数
	ID_AGB_agi_rnd,			//素早さパワー乱数
	ID_AGB_spepow_rnd,		//特殊攻撃パワー乱数
	ID_AGB_spedef_rnd,		//特殊防御パワー乱数
	ID_AGB_tamago_flag,		//たまごかどうか（0:タマゴじゃない1:たまごだよ）
	ID_AGB_speabi,			//特殊能力（0:特殊能力1　1:特殊能力2）
	ID_AGB_strong,			//たくましさ
	ID_AGB_fur,			//毛ヅヤ
	ID_AGB_oyasex,			//親の性別
	ID_AGB_stylemedal,		//かっこよさメダル
	ID_AGB_beautifulmedal,		//うつくしさメダル
	ID_AGB_cutemedal,		//かわいさメダル
	ID_AGB_clevermedal,		//かしこさメダル
	ID_AGB_strongmedal,		//たくましさメダル
	ID_AGB_condition,		//コンディション(状態異常）
	ID_AGB_level,			//レベル
	ID_AGB_hp,			//ヒットポイント
	ID_AGB_hpmax,			//ヒットポイントマックス
	ID_AGB_pow,			//攻撃力
	ID_AGB_def,			//防御力
	ID_AGB_agi,			//素早さ
	ID_AGB_spepow,			//特殊攻撃
	ID_AGB_spedef,			//特殊防御
	ID_AGB_mailid,			//所持メール
	ID_AGB_monsno_egg,		//モンスターナンバー（タマゴかどうかもチェックする）
	ID_AGB_power_rnd,		//パワー乱数をu32で扱う
	ID_AGB_champ_ribbon,		//チャンプリボン（殿堂入り）
	ID_AGB_winning_ribbon, 		//ウィニングリボン（バトルタワーLV50勝ち抜き）
	ID_AGB_victory_ribbon, 		//ビクトリーリボン（バトルタワーLV100勝ち抜き）
	ID_AGB_bromide_ribbon, 		//ブロマイドリボン（美術館に似顔絵を飾られた）
	ID_AGB_ganba_ribbon,	      	//がんばリボン（努力値既定以上）
	ID_AGB_marine_ribbon,	      	//マリンリボン（イベントで入手）
	ID_AGB_land_ribbon,		//ランドリボン（イベントで入手）
	ID_AGB_sky_ribbon,		//スカイリボン（イベントで入手）
	ID_AGB_country_ribbon,	  	//カントリーリボン（イベントで入手）
	ID_AGB_national_ribbon,	  	//ナショナルリボン（イベントで入手）
	ID_AGB_earth_ribbon,	      	//アースリボン（イベントで入手）
	ID_AGB_world_ribbon,	    	//ワールドリボン（イベントで入手）
	ID_AGB_amari_ribbon,		//あまり
	ID_AGB_event_get_flag,		//イベントで配布されたことを示すフラグ
	ID_AGB_waza_have_check,		//技を持っているかチェック
	ID_AGB_ribbon_cnt,		//リボンをいくつ持っているか？
	ID_AGB_ribbon_bit,	 	//取得リボンに応じたbitを立てて返す（ﾎﾟｹﾅﾋﾞ）
	ID_AGB_pow_nocalc,		//攻撃力（デオキシス計算をしない）
	ID_AGB_def_nocalc,		//防御力（デオキシス計算をしない）
	ID_AGB_agi_nocalc,		//素早さ（デオキシス計算をしない）
	ID_AGB_spepow_nocalc,	  	//特殊攻撃（デオキシス計算をしない）
	ID_AGB_spedef_nocalc	  	//特殊防御（デオキシス計算をしない）
};

#if 0
#define	POKE2VS2_OK		0				//2体2戦闘可能
#define	POKE2VS2_ONE	1				//1体しかポケモンがいない
#define	POKE2VS2_NOTWO	2				//戦えるポケモンが2体いない

//StatusRecover関数がどこから呼ばれたのかを指示するフラグ

#define		CALL_FIELD	0
#define		CALL_BATTLE	1

//進化条件
enum{
	LEVELUP_SHINKA=0,		//レベルアップによる進化
	TUUSHIN_SHINKA,			//通信による進化
	ITEM_SHINKA,			//アイテムによる進化
	ITEM_SHINKA_CHECK		//アイテムによる進化（かわらずのいしを装備していてもチェックはする）
};

#define	SHINKA_FRIEND		220		//進化に必要ななつき度

#define	SHINKA_CANCEL_OFF	0
#define	SHINKA_CANCEL_ON	1

#define	SHINKA_BGM_RESTART_ON	0x00	//進化デモからの復帰時にBGMStartをかける
#define	SHINKA_BGM_RESTART_OFF	0x80	//進化デモからの復帰時にBGMStartをかけない


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
	FRIEND_LEVEL30_HINSHI	//レベル差30以上の瀕死
};

//努力値に関する定義

#define	PARA_EXP_TOTAL_MAX	510		//6個のパラメータの合計値のマックス
#define	PARA_EXP_MAX		100		//6個のパラメータのマックス

#endif

//ポケモンパラメータ取得系の定義
enum{
	ID_AGB_POKEPARADATA11=0,
	ID_AGB_POKEPARADATA12,
	ID_AGB_POKEPARADATA13,
	ID_AGB_POKEPARADATA14,
	ID_AGB_POKEPARADATA15,
	ID_AGB_POKEPARADATA16,
	ID_AGB_POKEPARADATA21,
	ID_AGB_POKEPARADATA22,
	ID_AGB_POKEPARADATA23,
	ID_AGB_POKEPARADATA24,
	ID_AGB_POKEPARADATA25,
	ID_AGB_POKEPARADATA26,
	ID_AGB_POKEPARADATA31,
	ID_AGB_POKEPARADATA32,
	ID_AGB_POKEPARADATA33,
	ID_AGB_POKEPARADATA34,
	ID_AGB_POKEPARADATA35,
	ID_AGB_POKEPARADATA36,
	ID_AGB_POKEPARADATA41,
	ID_AGB_POKEPARADATA42,
	ID_AGB_POKEPARADATA43,
	ID_AGB_POKEPARADATA44,
	ID_AGB_POKEPARADATA45,
	ID_AGB_POKEPARADATA46
};

enum{
	ID_AGB_POKEPARA1=0,
	ID_AGB_POKEPARA2,
	ID_AGB_POKEPARA3,
	ID_AGB_POKEPARA4
};

#if 0

//ポケモン捕獲情報
#define	POS_EVENT_EGG	253		//おんせんバーさんにもらうタマゴ
#define	POS_CABLEKOUKAN	254		//ゲーム内交換
#define	POS_EVENTHAIHU	255		//イベントでの配布

//味覚情報
enum{
	TASTE_KARAI=0,
	TASTE_SIBUI,
	TASTE_AMAI,
	TASTE_NIGAI,
	TASTE_SUPPAI
};

//HitCountCheckFlag
#define	HCC_NORMAL		0		//自分に以外で場にいるポケモンの数
#define	HCC_ATTACK		1		//Attack側にいるポケモンの数
#define	HCC_DEFENCE		2		//Defence側にいるポケモンの数

#endif

extern int ChangeAGBPoke2DPPoke(int agbpoke);
extern int GBAcode2DSuni(int c_id, u8 *agb_str, u16 *ds_str);
extern u32 AgbPokePasoParaGet(PokemonPasoParam *PPP,int id,u8 *buf);
extern void AgbPokePasoParaPut(PokemonPasoParam *PPP,int id,const u8 *buf);
extern u32 AgbPokePasoLevelCalc(PokemonPasoParam *ppp);


#endif	// __AGBPOKE_TOOL_H__
/*  */
