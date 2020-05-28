//============================================================================================
/**
 * @file	syswork_def.h
 * @bfief	システムワーク定義
 * @author	Satoshi Nohara
 * @date	06.04.14
 */
//============================================================================================
#ifndef	__SYSWORK_DEF_H__
#define	__SYSWORK_DEF_H__


//============================================================================================
//	フラグ定義
//
//	スクリプト			定義を直接参照してよい！
//
//	プログラム			syswork.hにあるアクセス関数を使う！
//
//============================================================================================
#define		SYS_WORK_FIRST_POKE_NO		(0+OTHERS_WORK_START)	//最初のポケモンナンバー
//#define	SYS_WORK_POISON_STEP_COUNT	(1+OTHERS_WORK_START)	//毒歩数カウンター
//#define	SYS_WORK_ELEVATOR_FLOOR		(2+OTHERS_WORK_START)	//エレベータフロアナンバー
#define		SYS_WORK_BTL_SEARCHER_BATTERY	(3+OTHERS_WORK_START)	//バトルサーチャーバッテリー
#define		SYS_WORK_BTL_SEARCHER_CLEAR	(4+OTHERS_WORK_START)	//バトルサーチャークリア
#define		SYS_WORK_OOKISA_RECORD		(5+OTHERS_WORK_START)	//大きさ比べ用レコード（固体値）
#define		SYS_WORK_HIDEMAP_01			(6+OTHERS_WORK_START)	//隠しマップ判定用ワークその１
#define		SYS_WORK_HIDEMAP_02			(7+OTHERS_WORK_START)	//隠しマップ判定用ワークその２
#define		SYS_WORK_HIDEMAP_03			(8+OTHERS_WORK_START)	//隠しマップ判定用ワークその３
#define		SYS_WORK_HIDEMAP_04			(9+OTHERS_WORK_START)	//隠しマップ判定用ワークその４
#define		SYS_WORK_PARK_WALK_COUNT	(10+OTHERS_WORK_START)	//自然公園での歩数カウント
#define		SYS_WORK_NEWS_DAYS_COUNT	(11+OTHERS_WORK_START)	//新聞社締め切りカウンタ
#define		SYS_WORK_POKELOT_RND1		(12+OTHERS_WORK_START)	//ポケモンクジ用32bit
#define		SYS_WORK_POKELOT_RND2		(13+OTHERS_WORK_START)	//ポケモンクジ用32bit
#define		SYS_WORK_UG_TALK_COUNT		(14+OTHERS_WORK_START)	//地下会話カウント用(ミカゲ用）
#define		SYS_WORK_PAIR_TRAINER_ID	(15+OTHERS_WORK_START)	//連れ歩きトレーナーID
#define		SYS_WORK_RENSYOU_COUNT		(16+OTHERS_WORK_START)	//スロット連勝最大数
#define		SYS_WORK_POKE_LEVEL_NO		(17+OTHERS_WORK_START)	//ポケモンレベルでアイテム入手
#define		SYS_WORK_DEPART_COUNT		(18+OTHERS_WORK_START)	//デパートでの購入回数
#define		SYS_WORK_HAIHU_EVENT01		(19+OTHERS_WORK_START)	//配布イベント判定用ワークその１
#define		SYS_WORK_HAIHU_EVENT02		(20+OTHERS_WORK_START)	//配布イベント判定用ワークその２
#define		SYS_WORK_HAIHU_EVENT03		(21+OTHERS_WORK_START)	//配布イベント判定用ワークその３
#define		SYS_WORK_UG_TOOL_GIVE_COUNT	(22+OTHERS_WORK_START)	//地下 道具をあげた回数
#define		SYS_WORK_UG_KASEKI_DIG_COUNT	(23+OTHERS_WORK_START)	//地下 かせきを掘った回数
#define		SYS_WORK_UG_TRAP_HIT_COUNT	(24+OTHERS_WORK_START)	//地下 トラップにかけた回数
#define		SYS_WORK_UG_TALK_COUNT2		(25+OTHERS_WORK_START)	//地下会話カウント用
#define		SYS_WORK_FRIENDLY_COUNT		(26+OTHERS_WORK_START)	//なつき度用歩数カウント


//ワークの最大数など確認する！
//0 - 63

//============================================================================================
//
//		配布イベント用定義
//
//============================================================================================
#define		HAIHUEVENT_ID_D30		0		///<配布イベント：ダーレイ（ダーク）
#define		HAIHUEVENT_ID_D18		1		///<配布イベント：ミーシエ（エウリス）
#define		HAIHUEVENT_ID_D05		2		///<配布イベント：アルセウス（アウス）

//============================================================================================
//
//		隠しマップ共通定義
//
//============================================================================================
#define		HIDEMAP_ID_D15	(0)				///<隠しマップ：D15
#define		HIDEMAP_ID_D30	(1)				///<配布マップ：D30
#define		HIDEMAP_ID_L04	(2)				///<隠しマップ：L04
#define		HIDEMAP_ID_D18	(3)				///<配布マップ：D18
#endif	//__SYSWORK_DEF_H__



