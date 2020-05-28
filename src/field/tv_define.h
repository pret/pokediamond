//============================================================================================
/**
 * @file	tv_define.h
 * @date	2006.05.11
 * @author	tamada GAME FREAK inc.
 */
//============================================================================================

#ifndef	__TV_DEFINE_H__
#define	__TV_DEFINE_H__

//----------------------------------------------------------
/**
 * @brief
 */
//----------------------------------------------------------
typedef enum {
	TV_PROGRAM_BATTLE_TRAINER = 1,
	TV_PROGRAM_TRAINER_RESEARCH,
	TV_PROGRAM_BATTLE_WATCH,
	TV_PROGRAM_TRAINERS_EVERYDAY,
	TV_PROGRAM_SINOU_NEWS_NET,
	TV_PROGRAM_RECORD_GON,
	TV_PROGRAM_SINOU_NOW,
	TV_PROGRAM_TREND,

	TV_PROGRAM_ID_MAX,
}TV_PROGRAM_ID;

//----------------------------------------------------------
/**
 * @brief	TVトピック：監視型タイプ定義
 */
//----------------------------------------------------------
typedef enum {
	TVTOPIC_WATCH_POKE_GET_SUCCESS = 1,	///<ポケモン捕獲成功！	3	ポケモン捕獲終了後
	TVTOPIC_WATCH_POKE_GET_FAILURE,		///<ポケモン捕獲失敗	3	ボール試投１以上で倒す、逃がす
	TVTOPIC_WATCH_FISHING,				///<世界を釣る！	3	ポケモンをつり上げたとき
	TVTOPIC_WATCH_CHANGE_GROUP,			///<グループ乗り換え！	4	別のグループに乗り換えたとき
	TVTOPIC_WATCH_SEE_RARE_POKEMON,		///<レアポケモン発見！	3	レアポケモンとのエンカウント後
	TVTOPIC_WATCH_GET_HIDE_ITEM,		///<隠し道具発見！	4	隠し道具を見つけたとき
	TVTOPIC_WATCH_SHOPPING,				///<買い物チェック	4	一度に10個以上の道具を買ったとき
	TVTOPIC_WATCH_BORN_EGG,				///<タマゴが孵った！	4	タマゴが孵化したとき
	TVTOPIC_WATCH_CHECK_SODATEYA,		///<育て屋チェック		育て屋に預けたとき
	TVTOPIC_WATCH_CHANGE_NICKNAME,		///<姓名判断	4	ニックネームを変更したとき
	TVTOPIC_WATCH_POISON_DEAD,			///<毒でひん死……		フィールドでポケモンが瀕死になったとき
	TVTOPIC_WATCH_WIN_LOT,				///<ポケモンくじ当選！		ポケモンくじに当たったとき
	TVTOPIC_WATCH_DIG_FOSSIL,			///<化石掘り	化石掘りをしたあと
	TVTOPIC_WATCH_DENDOU,				///<殿堂入り！	はじめて殿堂入りしたとき
	TVTOPIC_WATCH_SAFARI,				///<サファリゲーム	サファリゲームを終了させたとき
	TVTOPIC_WATCH_OSU_MESU,				///<オスだけ！メスだけ！	パソコンから抜けたときの手持ちにより
	TVTOPIC_WATCH_KANPOU,				///<良薬は口に苦し！	ポケモンに漢方薬をあげたとき
	TVTOPIC_WATCH_NUTS_HARVEST,			///<豊作！		木の実をたくさん収穫したとき（収穫時、木のHPが８、９だったとき）
	TVTOPIC_WATCH_NUTS_POOR,			///<不作・・・	木の実が１つしか収穫できなかったとき
	TVTOPIC_WATCH_MAKE_NEW_GROUP,		///<新グループ誕生！	新しくグループを作ったとき
	TVTOPIC_WATCH_SET_CUSTOMBALL,		///<カスタムボール作成！	カスタムカプセルをポケモンにセットしたとき
	TVTOPIC_WATCH_GET_FLAG,				///<旗を取った！		人の旗を持ち帰った！
	TVTOPIC_WATCH_LOSE_FLAG,			///<旗を取られた！		自分の旗を持ち帰られた！
	TVTOPIC_WATCH_RIBBON,				///<リボン		

	TVTOPIC_WATCH_MAX,
}TVTOPIC_WATCH_TYPE;


//----------------------------------------------------------
/**
 * @brief	TVトピック：ギネス型タイプ定義
 */
//----------------------------------------------------------
typedef enum {
	TVTOPIC_RECORD_BTOWER = 1,		///<バトルタワー連勝記録更新	バトルタワー連勝記録を更新したとき
	TVTOPIC_RECORD_BFACTORY,		///<ファクトリー連勝記録更新	ファクトリー連勝記録を更新したとき
	TVTOPIC_RECORD_OOKISA,			///<大きさ測定記録更新	大きさ測定で記録を更新したとき
	TVTOPIC_RECORD_SLOT,			///<スロット達人	スロットで一定枚数以上を稼いだとき
	TVTOPIC_RECORD_RIBBON,			///<リボンコレクター	リボンを一定枚数以上獲得時に作成
	TVTOPIC_RECORD_NUTS_MASTER,		///<木の実育ての名人	収穫時、木のHPが10だったとき
	TVTOPIC_RECORD_POKE_SEARCHER,	///<揺れ草名人		揺れ草エンカウントを終了したとき連続数が10以上
	TVTOPIC_RECORD_TRAP_REMOVER,	///<ワナ解除名人	地下に入ったとき、たくさんのワナを解除したら作成
	TVTOPIC_RECORD_FLAG_GET,		///<ハタトリ名人		

	TVTOPIC_RECORD_MAX,
}TVTOPIC_RECORD_TYPE;

//----------------------------------------------------------
/**
 * @brief	TVトピック：質問型タイプ定義
 */
//----------------------------------------------------------
typedef enum {
	TVTOPIC_INTERVIEW_GYM_BADGE = 1,///<ジム制覇！	1	ジムのあるシティ	ジムリーダーを倒したあと
	TVTOPIC_INTERVIEW_BTOWER,		///<挑戦！バトルタワー	1	バトルタワー	挑戦終了後
	TVTOPIC_INTERVIEW_BFACTORY,		///<挑戦！ファクトリー	1	バトルファクトリー	挑戦終了後
	TVTOPIC_INTERVIEW_POKEMON,		///<あなたのポケモン	1	ポケモン大好きクラブ	
	TVTOPIC_INTERVIEW_ITEM,			///<おすすめのどうぐ！	2	フレンドリィショップ	
	TVTOPIC_INTERVIEW_POKETCH,		///<お気に入りのポケッチ	2	カンパニー	
	TVTOPIC_INTERVIEW_CONTEST,		///<挑戦！コンテスト		コンテスト会場	コンテスト終了後
	TVTOPIC_INTERVIEW_TATOE,		///<ポケモンに例えたら？	2	大好きクラブ	
	TVTOPIC_INTERVIEW_CLIP,			///<ポケモンクリップ！	2	クリップを作る場所	クリップを作ったあと
	TVTOPIC_INTERVIEW_CHARACTOR,	///<性格診断！	2		
	TVTOPIC_INTERVIEW_PORUTO,		///<ポルト料理		ポルトを作る場所	ポルトを作ったら
	TVTOPIC_INTERVIEW_KOUKAN,		///<交換したポケモン	1		
	TVTOPIC_INTERVIEW_TUREARUKI,	///<連れ歩きを満喫！		自然公園ゲート	連れ歩き後

	TVTOPIC_INTERVIEW_TYPE_MAX,
}TVTOPIC_INTERVIEW_TYPE;


//----------------------------------------------------------
/**
 * @brief	TVトピック：イベント型タイプ定義
 */
//----------------------------------------------------------
typedef enum {
	TVTOPIC_EVENT_RANDOMGROUP = 1,		///<グループ紹介
	TVTOPIC_EVENT_WEATHER,				///<天気予報
	TVTOPIC_EVENT_TOWNGUIDE,			///<シンオウあの街この街
	TVTOPIC_EVENT_BARGAIN,				///<ショップ安売り情報
	TVTOPIC_EVENT_POKEMON_OUTBREAK,		///<大量発生！
	TVTOPIC_EVENT_POKEMON_ENCOUNT,		///<ポケモン出没情報！
	TVTOPIC_EVENT_POKEMON_AISHOU,		///<ポケモン相性チャンネル
	TVTOPIC_EVENT_POSTMAN,				///<配達員だより
	TVTOPIC_EVENT_NUTS_INFOMATION,		///<きのみじょうほう
	TVTOPIC_EVENT_WAZAMACHINE,			///<わざマシンじょうほう
	TVTOPIC_EVENT_POKEMON_ITEM,			///<どうぐを持ってる野生ポケモン
	TVTOPIC_EVENT_POKEMON_CHARACTOR,	///<せいかく診断
	TVTOPIC_EVENT_SLOT_INFO,			///<スロットの出玉情報
	TVTOPIC_EVENT_TV_SHOPPING,			///<ＴＶショッピング
	TVTOPIC_EVENT_TV_MOVE_POKEMON,		///<移動ポケモン目撃情報！
	TVTOPIC_EVENT_TV_TAMAGO_INFO,		///<タマゴ発見報告
	TVTOPIC_EVENT_TV_CLIP_INFO,			///<ポケモンファッションチェック

	TVTOPIC_EVENT_TYPE_MAX,
}TVTOPIC_EVENT_TYPE;

//----------------------------------------------------------
/**
 * @brief	CMタイプ定義
 */
//----------------------------------------------------------
typedef enum {
	CM_TYPE_POKECEN = 1,		///<ポケモンセンター	最初から
	CM_TYPE_FRIENDLYSHOP,		///<フレンドリィショップ	最初から
	CM_TYPE_TV_STATION,			///<ＴＶ局	最初から
	CM_TYPE_TRAINERSCHOOL,		///<トレーナースクール	最初から
	CM_TYPE_POKETCH,			///<ポケッチ	最初から
	CM_TYPE_POKETCH_SOFT,		///<ポケッチソフト	
	CM_TYPE_FLOWER_SHOP,		///<花屋	ソノオ到着
	CM_TYPE_BICYCLE_SHOP,		///<自転車屋	ハクタイ到着
	CM_TYPE_CONTEST,			///<美容室	
	CM_TYPE_NATURE_PARK,		///<コンテストＣＭ	ハクタイ到着
	CM_TYPE_DEPART,				///<自然公園	ヨスガ到着
	CM_TYPE_BEAUTY_SALON,		///<トバリデパート	ヨスガ到着
	CM_TYPE_SODATEYA,			///<育て屋	ヨスガ到着
	CM_TYPE_HOTEL,				///<ホテル	ヨスガ到着
	CM_TYPE_SAFARI,				///<大湿原	ヨスガ到着
	CM_TYPE_C09,				///<キッサキシティ	ジムバッジ５個
	CM_TYPE_C08,				///<ナギサ市場	ジムバッジ５個
	CM_TYPE_GTC,				///<ＧＴＣ	ＧＴＣオープン
	CM_TYPE_POKEPARK,			///<ポケモンパーク	シンオウ図鑑コンプ
	CM_TYPE_SHIP_C09,			///<キッサキシティの船	シンオウ図鑑コンプ
	CM_TYPE_BATTLEZONE,			///<バトルゾーン	シンオウ図鑑コンプ
	CM_TYPE_CLUB,				///<会員制の建物	シンオウ図鑑コンプ
	CM_TYPE_GINGA1,				///<ギンガ団１	
	CM_TYPE_GINGA2,				///<ギンガ団２	
	CM_TYPE_PC_COMM,			///<ポケモンセンター通信編	図鑑取得後
	CM_TYPE_PC_WIFI,			///<ポケモンセンターWi-Fi編	図鑑取得後
	CM_TYPE_BTOWER,				///<バトルタワー	バトルタワーオープン後
	CM_TYPE_WIFI_BTOWER,		///< Wi-Fiバトルタワー	Wi-Fiバトルタワーオープン後
	CM_TYPE_SHIP,				///<乗り物ＣＭ（船）	船に乗れるようになってから

	CM_TYPE_MAX,
}CM_TYPE;

#endif	/*	__TV_DEFINE_H__ */

