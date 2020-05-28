//==============================================================================================
/**
 * @file	score_def.h
 * @brief	スコア関連定義
 * @author	Nozomu Saito
 * @date	2006.06.15
 */
//==============================================================================================
#ifndef __SCORE_DEF_H__
#define __SCORE_DEF_H__

//----------------------------------------------------------
//		スコア集計用の指定ID
//----------------------------------------------------------
#define	SCORE_ID_GET_NUTS				0			///<スコア：きのみを取った
#define	SCORE_ID_HONEY_TREE				1			///<スコア：木に蜜塗った
#define SCORE_ID_WRITE_MAIL				2			///<スコア：メールを書いた
#define SCORE_ID_INTERVIEW				3			///<スコア：テレビインタビューに答えた
#define SCORE_ID_WRITE_SIGN				4			///<スコア：サイン書いた
#define SCORE_ID_PLAY_SLOT				5			///<スコア：スロット始めた
#define SCORE_ID_CUSTOM_CAPSULE			6			///<スコア：カスタムカプセル作った
#define SCORE_ID_MAKE_CLIP				7			///<スコア：クリップ作った
#define	SCORE_ID_WILD_BATTLE_WIN		8			///<スコア：野生エンカウント勝利
#define	SCORE_ID_POKE_GET_SINOU			9			///<スコア：ポケモンゲット（シンオウずかん）
#define	SCORE_ID_POKE_GET_WORLD			10			///<スコア：ポケモンゲット（シンオウずかん外）
#define	SCORE_ID_TRAINER_BATTLE_WIN		11			///<スコア：トレーナー戦勝利
#define	SCORE_ID_MINIGAME_NUTS			12			///<スコア：木の実料理(1人)
#define	SCORE_ID_CONTEST_GRANDPRIX		13			///<スコア：コンテスト優勝
#define	SCORE_ID_BTOWER_7WIN			14			///<スコア：バトルタワー7人勝ち抜き
#define	SCORE_ID_EGG_HATCHING			15			///<スコア：タマゴが孵った
#define	SCORE_ID_COMM_TRADE_POKE		16			///<スコア：通信交換(Wifi/ダイレクト)
#define SCORE_ID_CLEAR_POKEPARK			17			///<スコア：ポケパーククリア
#define	SCORE_ID_COMM_MINIGAME_NUTS		18			///<スコア：木の実料理（通信）
#define	SCORE_ID_COMM_CONTEST_GRANDPRIX	19			///<スコア：コンテスト優勝（通信）
#define	SCORE_ID_COMM_RECORD_CORNER		20			///<スコア：レコードコーナー
#define	SCORE_ID_COMM_BATTLE_COUNT		21			///<スコア：通信対戦(Wifi/ダイレクト/ユニオン)
#define	SCORE_ID_ZUKAN_ENTRY			22			///<スコア：ずかん登録
#define SCORE_ID_GYM_LEADER_WIN			23			///<スコア：ジムリーダーに勝った
#define	SCORE_ID_DENDOU					24			///<スコア：殿堂入りした
#define SCORE_ID_WORLD_TRADE			25			///<スコア：世界通信交換をした
#define	SCORE_ID_COMMENDATION_A			26			///<スコア：表彰状Aをもらった
#define	SCORE_ID_COMMENDATION_B			27			///<スコア：表彰状Bをもらった

#define	SCORE_ID_NEW_FLAG_TAKE_OUT		28			///<スコア：炭鉱 新しい旗持ち帰り
#define	SCORE_ID_FLAG_TAKE_OUT			29			///<スコア：炭鉱 旗持ち帰り
#define	SCORE_ID_GET_FOSSIL				30			///<スコア：炭鉱 化石発掘
#define	SCORE_ID_ITEM_DEPOSIT			31			///<スコア：炭鉱 相手に道具あげる
#define	SCORE_ID_HELLO					32			///<スコア：炭鉱 あいさつする
#define	SCORE_ID_QUESTION				33			///<スコア：炭鉱 質問する
#define	SCORE_ID_RESCUE					34			///<スコア：炭鉱 罠から助けた
#define	SCORE_ID_MAKE_BASE				35			///<スコア：炭鉱 基地作る
#define	SCORE_ID_MINE_IN				36			///<スコア：炭鉱 地下に来る
#define	SCORE_ID_WLAK_100				37			///<スコア：炭鉱 100歩あるく

#define	SCOREID_MAX						38
#define SCORE_MAX						99999999	//スコア最大値

#endif //__SCORE_DEF_H__
