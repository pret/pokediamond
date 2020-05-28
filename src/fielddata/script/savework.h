//==============================================================================================
/**
 * @file	savework.h
 * @brief	ゲーム内セーブワーク定義(スクリプトからのみアクセスされるワーク)
 * @author	tomo
 * @date	2005.10.22
 */
//==============================================================================================
#ifndef	__SAVEWORK_H__
#define	__SAVEWORK_H__

//----------------------------------------------------------------------------------------------
//0-31は、ローカルワークとして使用
//MAX = evwkdef.h LOCAL_WORK_MAX
//----------------------------------------------------------------------------------------------
#define	 LOCALWORK0					(0+LOCAL_WORK_START)
#define	 LOCALWORK1					(1+LOCAL_WORK_START)
#define	 LOCALWORK2					(2+LOCAL_WORK_START)
#define	 LOCALWORK3					(3+LOCAL_WORK_START)
#define	 LOCALWORK4					(4+LOCAL_WORK_START)
#define	 LOCALWORK5					(5+LOCAL_WORK_START)
#define	 LOCALWORK6					(6+LOCAL_WORK_START)
#define	 LOCALWORK7					(7+LOCAL_WORK_START)
#define	 LOCALWORK8					(8+LOCAL_WORK_START)
#define	 LOCALWORK9					(9+LOCAL_WORK_START)
#define	 LOCALWORK10				(10+LOCAL_WORK_START)
#define	 LOCALWORK11				(11+LOCAL_WORK_START)
#define	 LOCALWORK12				(12+LOCAL_WORK_START)
#define	 LOCALWORK13				(13+LOCAL_WORK_START)
#define	 LOCALWORK14				(14+LOCAL_WORK_START)
#define	 LOCALWORK15				(15+LOCAL_WORK_START)
#define	 LOCALWORK16				(16+LOCAL_WORK_START)
#define	 LOCALWORK17				(17+LOCAL_WORK_START)
#define	 LOCALWORK18				(18+LOCAL_WORK_START)
#define	 LOCALWORK19				(19+LOCAL_WORK_START)
#define	 LOCALWORK20				(20+LOCAL_WORK_START)
#define	 LOCALWORK21				(21+LOCAL_WORK_START)
#define	 LOCALWORK22				(22+LOCAL_WORK_START)
#define	 LOCALWORK23				(23+LOCAL_WORK_START)
#define	 LOCALWORK24				(24+LOCAL_WORK_START)
#define	 LOCALWORK25				(25+LOCAL_WORK_START)
#define	 LOCALWORK26				(26+LOCAL_WORK_START)
#define	 LOCALWORK27				(27+LOCAL_WORK_START)
#define	 LOCALWORK28				(28+LOCAL_WORK_START)
#define	 LOCALWORK29				(29+LOCAL_WORK_START)
#define	 LOCALWORK30				(30+LOCAL_WORK_START)
#define	 LOCALWORK31				(31+LOCAL_WORK_START)

//----------------------------------------------------------------------------------------------
//32-47は、変更OKなOBJキャラ指定として使用
//MAX = evwkdef.h OBJCHR_WORK_MAX
//----------------------------------------------------------------------------------------------
#define	 OBJCHRWORK0				(0+OBJCHR_WORK_START)
#define	 OBJCHRWORK1				(1+OBJCHR_WORK_START)
#define	 OBJCHRWORK2				(2+OBJCHR_WORK_START)
#define	 OBJCHRWORK3				(3+OBJCHR_WORK_START)
#define	 OBJCHRWORK4				(4+OBJCHR_WORK_START)
#define	 OBJCHRWORK5				(5+OBJCHR_WORK_START)
#define	 OBJCHRWORK6				(6+OBJCHR_WORK_START)
#define	 OBJCHRWORK7				(7+OBJCHR_WORK_START)
#define	 OBJCHRWORK8				(8+OBJCHR_WORK_START)
#define	 OBJCHRWORK9				(9+OBJCHR_WORK_START)
#define	 OBJCHRWORK10				(10+OBJCHR_WORK_START)
#define	 OBJCHRWORK11				(11+OBJCHR_WORK_START)
#define	 OBJCHRWORK12				(12+OBJCHR_WORK_START)
#define	 OBJCHRWORK13				(13+OBJCHR_WORK_START)
#define	 OBJCHRWORK14				(14+OBJCHR_WORK_START)
#define	 OBJCHRWORK15				(15+OBJCHR_WORK_START)

//------------------------------------------------------------------------
//							フィールドタウン
//------------------------------------------------------------------------
#define WK_SCENE_T01					(SVSCRWK_START+0)
/* フタバタウンイベント
01 ゲーム開始時から1
02 ライバルと会話して、T01のストッパー解除
*/

#define WK_SCENE_T02					(SVSCRWK_START+1)
/* マサゴタウンイベント
01 研究所への誘導イベント終了
02 サポートの教えイベント終了
*/

#define WK_SCENE_T03					(SVSCRWK_START+2)
/* ソノオタウンイベント
01 ギンガ団ボスイベント終了
*/

#define WK_SCENE_T04					(SVSCRWK_START+3)

#define WK_SCENE_T05					(SVSCRWK_START+4)
/* カンナギタウンイベント
01 ギンガ団ボス会話イベント開始
02 ギンガ団ボス会話イベント終了
*/

//#define WK_SCENE_NONE					(SVSCRWK_START+5)

//#define WK_SCENE_NONE					(SVSCRWK_START+6)		//※未使用ワーク

//------------------------------------------------------------------------
//							フィールドシティ
//------------------------------------------------------------------------
#define WK_SCENE_C01					(SVSCRWK_START+7)
/* コトブキシティイベント
01 サポートイベント終了
02 ポケッチ入手した
03 ギンガ団イベント開始
04 ギンガ団イベント終了
*/

#define WK_SCENE_C02					(SVSCRWK_START+8)
/* ミオシティイベント
01 ライバル戦闘に勝利
02 ライバル図書館へ移動イベント開始
03 ライバル図書館へ移動イベント終了
04 図書館イベント終了後の博士イベント開始
05 図書館イベント終了後の博士イベント終了
06 ↑イベント後にマップ切り替えて戻ってきた
*/

#define WK_SCENE_C03					(SVSCRWK_START+9)
/* クロガネシティイベント
01 ジム誘導イベント終了
02 ジムクリアしてライバルイベント開始
03 ライバルイベント終了
*/

#define WK_SCENE_C04					(SVSCRWK_START+10)
/*ハクタイシティ
01 チャンピオンにいあいぎりもらった 
*/

#define WK_SCENE_C05					(SVSCRWK_START+11)
/*ヨスガシティ
01 ライバルイベント開始
02 ライバルイベント終了
*/

#define WK_SCENE_C06					(SVSCRWK_START+12)
/*ノモセシティ
1 ジムクリア
*/

#define WK_SCENE_C07					(SVSCRWK_START+13)
/*トバリシティ
01 ジムクリア(倉庫前イベントのPOSに使用)
*/

#define WK_SCENE_C08					(SVSCRWK_START+14)
/*ナギサシティ
01 ジムリーダーイベント終了
02 ミカンイベント終了
*/

#define WK_SCENE_C09					(SVSCRWK_START+15)
/*キッサキシティ
01 神殿ストッパー終了
*/

#define WK_SCENE_C10					(SVSCRWK_START+16)

#define WK_SCENE_C11					(SVSCRWK_START+17)
/*？？シティ
00 ライバルと５人衆イベント開始(c11に初めて入ったら)
01 ライバルと５人衆イベント終了
*/

//------------------------------------------------------------------------
//							フィールドみずうみ
//------------------------------------------------------------------------
#define WK_SCENE_L01					(SVSCRWK_START+18)
/* 湖
01 湖へ移動イベント終了
02 湖から帰ってきて連れ歩きセット
03 湖から帰ってきて連れ歩きセット終了
04 自宅へ帰るイベント終了(湖に引き返せないPOS終了)
*/

#define WK_SCENE_L02					(SVSCRWK_START+19)
/* 湖(未使用)
02 チャンピオンイベント終了
*/

#define WK_SCENE_L03					(SVSCRWK_START+20)

#define WK_SCENE_L04					(SVSCRWK_START+21)

//------------------------------------------------------------------------
//							フィールドロード
//------------------------------------------------------------------------
#define WK_SCENE_R201					(SVSCRWK_START+22)
/* ライバル登場イベント
01 連れ歩き開始
02 博士と会うイベント開始
03 博士と会うイベント終了
*/

#define WK_SCENE_R202					(SVSCRWK_START+23)
/* サポート捕獲デモ
01 イベント終了
*/

#define WK_SCENE_R203					(SVSCRWK_START+24)
/* ライバル登場イベント
01 イベント終了
*/

#define WK_SCENE_R205A					(SVSCRWK_START+25)
/* ギンガ団イベント
01 少女イベント終了
02 ギンガ団イベント終了
*/

#define WK_SCENE_R209					(SVSCRWK_START+26)
/* みたまのとう
01 かなめいしを使った
02 ミカゲと戦闘後
*/

#define WK_SCENE_R227					(SVSCRWK_START+27)
/* R227イベント
01 ジムリーダーとライバルイベント終了
*/

#define WK_SCENE_R207					(SVSCRWK_START+28)

#define WK_SCENE_R224					(SVSCRWK_START+29)
/* R224イベント
01 エウリス石碑イベント中
*/

//#define WK_SCENE_NONE					(SVSCRWK_START+30)		//※未使用ワーク

//#define WK_SCENE_NONE					(SVSCRWK_START+31)		//※未使用ワーク

//------------------------------------------------------------------------
//							部屋の中(ダンジョン)
//------------------------------------------------------------------------
#define WK_SCENE_D09R0104				(SVSCRWK_START+32)
/* チャンピオンロード
00 連れ歩き終了
01 連れ歩き開始
02 ゴールについた
*/

#define WK_SCENE_D21R0101				(SVSCRWK_START+33)
/* 迷いの洞窟
00 連れ歩き終了
01 連れ歩き開始
02 ゴールについた
*/

#define WK_SCENE_D24R0105				(SVSCRWK_START+34)
/* 鋼鉄島
00 連れ歩き終了
01 連れ歩き開始
02 ゴールについた
*/

#define WK_SCENE_D14R0101				(SVSCRWK_START+35)
/* クロガネゲート
01 秘伝入手イベント開始
02 秘伝入手イベント終了
*/

#define WK_SCENE_D16R0102				(SVSCRWK_START+36)
/* 火山２階
00 連れ歩き終了
01 連れ歩き開始
02 ゴールについた
*/

#define WK_SCENE_D27R0101				(SVSCRWK_START+37)
/* 湖イベント
01 ポケモン入手した
*/

#define WK_SCENE_D05R0101				(SVSCRWK_START+38)
/* テンガン山イベント
01 ボスイベント終了
*/

#define WK_SCENE_D27R0102				(SVSCRWK_START+39)
/* 湖イベント
01 博士が伝説ポケモンを助けてくれ強制イベント終了
*/

#define	WK_SCENE_D05R0114				(SVSCRWK_START+40)
/* テンガン山山頂イベント
00	初期状態、ギンガ団ザコと対戦
01	POSでイア（エア）登場へ
02	POSでギンガ団幹部とマルチバトル開始→デモ→ボス戦
03	POSでイア（エア）対戦へ→サポート＆博士登場、イベントクリア
04	イベント終了状態
05	クリア後隠しイベントへ続く…
 */

#define WK_SCENE_D11R0101				(SVSCRWK_START+41)
/* ふれあい広場
00 連れ歩き前
01 連れ歩き中
 */

#define WK_SCENE_D11R0101_MONSNO              (SVSCRWK_START+42)
/* 連れているポケモンナンバー
 */

#define WK_SCENE_D11R0101_PRESENT		(SVSCRWK_START+43)
/* 貰えるものの種類
00 きのみ
01 アクセサリー
 */

#define WK_SCENE_D11R0101_PRESENT_ACCE_NO	(SVSCRWK_START+44)
/* 貰えるアクセサリーナンバー
 */

#define WK_SCENE_D11R0101_TNO        (SVSCRWK_START+45)
/* 連れているポケモンの手持ちナンバー
 */

#define WK_SCENE_D16R0103				(SVSCRWK_START+46)
/* 火山３階
01 かざんのおきいしイベント終了
*/

#define WK_SCENE_D11R0101_PRESENT_KINOMI_NO	(SVSCRWK_START+47)
/* 貰えるきのみナンバー
 */

//#define WK_SCENE_NONE					(SVSCRWK_START+48)		//※未使用ワーク

//#define WK_SCENE_NONE					(SVSCRWK_START+49)		//※未使用ワーク

//------------------------------------------------------------------------
//							部屋の中(タウン)
//------------------------------------------------------------------------
#define WK_SCENE_T01R0101				(SVSCRWK_START+50)

#define WK_SCENE_T01R0102				(SVSCRWK_START+51)
/* ライバル2階イベント
01 ライバル出発イベント終了
*/

#define WK_SCENE_T01R0201				(SVSCRWK_START+52)
/* 自宅1階イベント
01 2階から降りてきた会話終了
02 外出しようとしてママとの会話終了
03 シューズイベント開始
04 シューズをもらった
05 シューズをもらって外に出た
06 冒険ノート入手イベント終了
07 冒険ノート入手イベント後に外に出て戻ってきた
*/

#define WK_SCENE_T01R0202				(SVSCRWK_START+53)
/* 自宅2階イベント ※060801現在　未使用
01 初期設定終了
*/

#define WK_SCENE_T02R0101				(SVSCRWK_START+54)

#define WK_SCENE_T07R0101				(SVSCRWK_START+55)
/* 
00 会員になれるかチェック
*/

//#define WK_SCENE_NONE					(SVSCRWK_START+56)		//※未使用ワーク

//#define WK_SCENE_NONE					(SVSCRWK_START+57)		//※未使用ワーク

//#define WK_SCENE_NONE					(SVSCRWK_START+58)		//※未使用ワーク

//#define WK_SCENE_NONE					(SVSCRWK_START+59)		//※未使用ワーク

//#define WK_SCENE_NONE					(SVSCRWK_START+60)		//※未使用ワーク

//------------------------------------------------------------------------
//							部屋の中(シティ)
//------------------------------------------------------------------------
#define WK_SCENE_C01R0101				(SVSCRWK_START+61)
#define WK_SCENE_C04GYM0102				(SVSCRWK_START+62)

#define WK_SCENE_C01R0701				(SVSCRWK_START+63)
/* トレーナースクールイベント
01 ポケッチイベント開始
02 ポケッチイベント終了
*/

#define WK_SCENE_C01R0201				(SVSCRWK_START+64)
/* TV局イベント
*/

#define WK_SCENE_D03R0101				(SVSCRWK_START+65)
/* ハクタイの森内部イベント
01 連れ歩き開始
02 連れ歩きゴールについた
*/

#define WK_SCENE_C02R0103				(SVSCRWK_START+66)
/* 図書館３階イベント
01 みんなそろうイベント開始
02 みんなそろうイベント終了
*/

#define WK_SCENE_C03R0401				(SVSCRWK_START+67)
/* 化石イベント
01 化石預かり中
02 ポケモン預かり中
*/

#define WK_SCENE_KASEKI_MONSNO			(SVSCRWK_START+68)
/* 化石イベント
xxxx ポケモン番号
*/

#define WK_SCENE_C08R0701				(SVSCRWK_START+69)
/* ポケッチマニア
00 会話前
01 会話した
02 ポケッチアプリ1つ目入手
03 ポケッチアプリ2つ目入手
04 ポケッチアプリ3つ目入手
*/

#define WK_SCENE_C08R0401				(SVSCRWK_START+70)
/* 探検状態
01 ミッション１クリア 
02 ミッション２クリア 
03 ミッション３クリア 
04 ミッション４クリア 
05 ミッション５クリア 
06 ミッション６クリア 
07 ハタ３本以上の表彰済み
08 ハタ１０本以上の表彰済み
09 ちかマスター（ハタ５０本以上の表彰済み）
*/

//#define WK_SCENE_NONE					(SVSCRWK_START+71)		//※未使用ワーク

//#define WK_SCENE_NONE					(SVSCRWK_START+72)		//※未使用ワーク

//#define WK_SCENE_NONE					(SVSCRWK_START+73)		//※未使用ワーク

//#define WK_SCENE_NONE					(SVSCRWK_START+74)		//※未使用ワーク

//#define WK_SCENE_NONE					(SVSCRWK_START+75)		//※未使用ワーク

//#define WK_SCENE_NONE					(SVSCRWK_START+76)		//※未使用ワーク

//#define WK_SCENE_NONE					(SVSCRWK_START+77)		//※未使用ワーク

//#define WK_SCENE_NONE					(SVSCRWK_START+78)		//※未使用ワーク

//#define WK_SCENE_NONE					(SVSCRWK_START+79)		//※未使用ワーク

//------------------------------------------------------------------------
//							部屋の中(みずうみ)
//------------------------------------------------------------------------
#define WK_SCENE_L01R0101				(SVSCRWK_START+80)

//#define WK_SCENE_NONE					(SVSCRWK_START+81)		//※未使用ワーク

//#define WK_SCENE_NONE					(SVSCRWK_START+82)		//※未使用ワーク

//#define WK_SCENE_NONE					(SVSCRWK_START+83)		//※未使用ワーク

//#define WK_SCENE_NONE					(SVSCRWK_START+84)		//※未使用ワーク

//------------------------------------------------------------------------
//							部屋の中(ロード)
//180～219まで使用
//------------------------------------------------------------------------
#define WK_SCENE_R201R0101				(SVSCRWK_START+85)

#define WK_SCENE_R221R0101				(SVSCRWK_START+86)
/*
00 オーキドが待っている
01 オーキドが去った
*/

//#define WK_SCENE_NONE					(SVSCRWK_START+87)		//※未使用ワーク

//#define WK_SCENE_NONE					(SVSCRWK_START+88)		//※未使用ワーク

//#define WK_SCENE_NONE					(SVSCRWK_START+89)		//※未使用ワーク

//------------------------------------------------------------------------
//							その他
//------------------------------------------------------------------------
#define WK_SCENE_PAIR_R201_RIVAL		(SVSCRWK_START+90)
/* R201連れ歩きライバルイベント
01 会話1
02 会話2
03 会話3
04 会話4
05 会話5
*/

#define WK_SCENE_PAIR_L01_RIVAL			(SVSCRWK_START+91)
/* L01連れ歩きライバルイベント
01 会話1
02 会話2
03 会話3
*/

#define WK_SCENE_CONTEST				(SVSCRWK_START+92)
/* コンテスト
00 何もしていない
01 コンテスト中
02 エンディング中
*/

#define WK_SCENE_D03R0101_GHOST			(SVSCRWK_START+93)
/* ハクタイの森の幽霊イベント(未使用)
01 5人衆と会話した
*/

#define WK_ELEVATOR_FLOOR				(SVSCRWK_START+94)
/* エレベータフロアワーク
*/

#define WK_SCENE_D02R0101				(SVSCRWK_START+95)
/* 発電所内
01 ギンガ団イベント終了
02 ギンガ団幹部POSイベント終了
*/

#define WK_SCENE_UG						(SVSCRWK_START+96)
/* 地下
01 初回山男イベント終了
*/

#define WK_SCENE_C05_MAIN				(SVSCRWK_START+97)
/* ヨスガシティイベント
01 ジムクリア後のチャンピオンイベント開始
02 ジムクリア後のチャンピオンイベント終了
*/

//#define WK_SCENE_PC_UG					(SVSCRWK_START+98)
/* ポケセン地下イベント
//01 初回ともだちてちょう入手イベント終了
*/

#define WK_SCENE_D29R0102				(SVSCRWK_START+99)
/* 湖イベント
01 ライバルが負けるイベント開始
02 ライバルが負けるイベント終了
*/

#define WK_SCENE_PC0103					(SVSCRWK_START+100)
/* ポケセン地下
01 マミナイベント終了(ともだちてちょうイベント)
*/

#define WK_SCENE_COMM_ID				(SVSCRWK_START+101)
/* スクリプト通信受付ID
00 何もなし
01 バトル
02 ユニオン
03 レコード
04 WiFi
*/

#define WK_SCENE_D26R0104				(SVSCRWK_START+102)
/* ギンガ団アジト
01 ボスイベント終了
*/

#define WK_SCENE_SAFARI_GATE			(SVSCRWK_START+103)
/* サファリ入り口
*/

#define WK_SCENE_D31R0201				(SVSCRWK_START+104)
/*
00 何もなし
01 プレイ終了時受付
02 続きからプレイ時受付
*/

#define WK_SCENE_D31R0205				(SVSCRWK_START+105)
/* バトルタワーシングルバトル対戦部屋
00 最初に部屋に入るとき
01 連戦時
 */

#define WK_SCENE_SAFARI_ZONE			(SVSCRWK_START+106)
/* サファリ制御用
00:サファリに入る前
01:サファリ中
02:サファリ終了
03:ボールがなくなってサファリ終了	※現在共通で"2"にしている
*/

#define WK_SCENE_D31R0202				(SVSCRWK_START+107)
/* バトルタワーエレベータ部屋
00 なにもなし
01 イベント起動時
 */

#define WK_SCENE_D31R0203				(SVSCRWK_START+108)
/* バトルタワーシングル通路
00 なにもなし
01 イベント起動時
 */

#define WK_SCENE_D31R0204				(SVSCRWK_START+109)
/* バトルタワーマルチ通路
00 なにもなし
01 イベント起動時
 */

#define WK_SCENE_D31R0206				(SVSCRWK_START+110)
/* バトルタワーマルチ対戦部屋
00 なにもなし
01 イベント起動時
 */

#define WK_SCENE_D31R0207				(SVSCRWK_START+111)
/* バトルタワーマルチサロン
 * 00 なにもなし
01 イベント起動時
 */

#define WK_SCENE_POKE_PARK				(SVSCRWK_START+112)
/* 
01 ポケパーク中
*/

#define WK_SCENE_PAIR_D16R0102_SEVEN5	(SVSCRWK_START+113)
/* d16r0102連れ歩き５人衆イベント
00 会話0
01 会話1
02 会話2
03 会話3
*/

#define WK_SCENE_PAIR_D21R0101_SEVEN2	(SVSCRWK_START+114)
/* d21r0101連れ歩き５人衆イベント
00 会話0
01 会話1
02 会話2
03 会話3
*/

#define WK_SCENE_PAIR_D24R0105_SEVEN3	(SVSCRWK_START+115)
/* d24r0105連れ歩き５人衆イベント
00 会話0
01 会話1
02 会話2
03 会話3
*/

#define WK_SCENE_PAIR_D09R0104_SEVEN4	(SVSCRWK_START+116)
/* d09r0104連れ歩き５人衆イベント
00 会話0
01 会話1
02 会話2
03 会話3
*/

#define WK_SCENE_NEWS_MONSNO			(SVSCRWK_START+117)
/* 新聞社で探しているポケモン
00 依頼前 
01～　依頼後。ポケモンNo
*/

#define WK_SCENE_T01_RIVAL				(SVSCRWK_START+118)
/* フタバ　ライバルイベント
01 ライバル家の前でぶつかるイベント終了
*/

#define WK_SCENE_C01_RIVAL				(SVSCRWK_START+119)
/* コトブキ ライバルイベント
01 ポケッチイベント開始
02 ポケッチイベント終了
*/

#define WK_SCENE_PAIR_D03R0101_SEVEN1	(SVSCRWK_START+120)
/* d03r0101連れ歩き５人衆イベント
00 会話0
01 会話1
02 会話2
*/

#define WK_SCENE_D13R0101				(SVSCRWK_START+121)
/* ソノオ花畑
01 ギンガ団イベント終了
*/

#define WK_SCENE_C05_RIVAL				(SVSCRWK_START+122)
/* ヨスガシティイベント
01 ライバルイベント開始
02 ライバルイベント終了
*/

#define WK_SCENE_C05R1101				(SVSCRWK_START+123)
/* コンテスト受付イベント
01 ママイベント終了
*/

#define WK_SCENE_BICYCLE				(SVSCRWK_START+124)
/* サインクリングゲート
01 ストッパー解除
*/

#define	WK_SCENE_POSTMAN				(SVSCRWK_START+125)
/* ふしぎ配達員判定用ワーク
 * セーブする必要はないがFLAG_CHANGEラベルで操作するため確保しておく
 */

#define WK_SCENE_T03_ZUKAN				(SVSCRWK_START+126)		//現在使用せず（Makeの関係でまだ残っています）
/*図鑑のパワーアップイベント(オスメス追加）
01　イベント終了
*/

#define WK_SCENE_C10R0101				(SVSCRWK_START+127)
/* ポケモンリーグ
01 ライバルイベント終了
*/

#define WK_SCENE_C01_GTC				(SVSCRWK_START+128)
/* GTCストッパー
01 ストッパーイベント終了
*/

#define WK_SCENE_T05_OLDWOMAN			(SVSCRWK_START+129)
/* カンナギタウン2
01 長老イベント
*/

#define WK_SCENE_KUJI_AZUKE_ITEM		(SVSCRWK_START+130)
/* 預けている賞（１～４）
00 預けていない
01 １等
02 ２等
03 ３等
04 ４等
05 特等
*/

#define	WK_SCENE_D10R0101				(SVSCRWK_START+131)

#define WK_SCENE_DENDOU					(SVSCRWK_START+132)
/* 初回殿堂
01 殿堂入りデータあり
02 クリア後の初回イベント終了
*/

#define WK_SCENE_C07_SUPPORT			(SVSCRWK_START+133)
/*トバリシティ
01 ジム前サポートイベント終了 
*/

#define WK_SCENE_C05_JUDGE				(SVSCRWK_START+134)
/* ヨスガシティイベント
01 ミミィのイベント終了
*/

#define WK_SCENE_C05R1101_JUDGE			(SVSCRWK_START+135)
/* ヨスガシティイベント
01 ミミィのイベント終了
*/

#define WK_SCENE_C02R0401				(SVSCRWK_START+136)
/* ダークイベント
01 ダークイベント開始イベント：開始
02 ダークイベント終了イベント：開始
03 ダークイベント終了イベント：終了
04 ダークイベントその後イベント：終了
*/

#define WK_SCENE_GAME_START				(SVSCRWK_START+137)
/* ゲームスタートイベント
01 ゲームスタートイベント終了
*/

#define WK_SCENE_D20R0106				(SVSCRWK_START+138)
/* レジキングイベント
01 レジキング挑戦可
02 レジキング挑戦不可
03 レジキング挑戦終了
*/

#define WK_SCENE_L02R0101_P01			(SVSCRWK_START+139)
/* カップル１の会話
00 乾杯
01 オードブル
02 メインディッシュ
03 デザート
*/

#define WK_SCENE_L02R0101_P02			(SVSCRWK_START+140)

#define WK_SCENE_L02R0101_P03			(SVSCRWK_START+141)

#define WK_SCENE_L02R0101_P04			(SVSCRWK_START+142)

#define WK_SCENE_L02R0101_P05			(SVSCRWK_START+143)

#define WK_SCENE_L02R0101_P06			(SVSCRWK_START+144)

#define WK_SCENE_L02R0101_P07			(SVSCRWK_START+145)

#define WK_SCENE_L02R0101_P08			(SVSCRWK_START+146)

#define WK_SCENE_L02R0101_P09			(SVSCRWK_START+147)

#define WK_SCENE_L02R0101_CLOSE			(SVSCRWK_START+148)
/* レストラン閉店処理関連
01 閉店処理へ
*/

#define WK_SCENE_R218R0201_ZUKAN		(SVSCRWK_START+149)
/*図鑑のパワーアップイベント(オスメス追加）
01　イベント終了
*/

#define WK_SCENE_C02R0501				(SVSCRWK_START+150)
/** ミオシティ 船乗りナミキの家のムーバスイベント
 01	悪夢イベント開始
 02	悪夢イベント中
 03 悪夢イベント解決直後～一度家を出るまで
 */

#define WK_SCENE_C07R0201_GET_ACCE_NO		(SVSCRWK_START+151)
/** 貰ったアクセサリー番号
 */

#define WK_SCENE_R221R0201_ITEM_LOOP		(SVSCRWK_START+152)
/** ナンバージジイからアイテムゲット(番号がループする）
 00 くろおび
 01 たつじんのおび
 02 きあいのタスキ
 */

#define WK_SCENE_C05_GOODS_EV		(SVSCRWK_START+153)
/** グッズを貰える絵描き
 01 アイテムを渡した
 02 全てのグッズを貰った
 */

#define WK_SCENE_C01R0202_GET_ACCE_NO		(SVSCRWK_START+154)
/** 貰ったアクセサリー番号
 */

#define WK_D17SYSTEM_GET_POINT		(SVSCRWK_START+155)
/** d17戻ラズの洞窟　柱のある部屋を通過した数
 */
#define WK_D17SYSTEM_PATH_MAP		(SVSCRWK_START+156)
/** d17戻ラズの洞窟　通過した部屋述べ数
 */
#define WK_SCENE_D26R0107			(SVSCRWK_START+157)
/** ギンガ団アジト　レイアイハイの部屋
01 サターン戦後～解放スイッチ押すまで(部屋からでれないストッパー有効)
 */

#define WK_SCENE_D31					(SVSCRWK_START+158)
/* バトルタワー前イベント
01 バトルタイクーン、ライバルイベント終了
*/

#define WK_SCENE_T01R0201_GAME_CLEAR	(SVSCRWK_START+159)
/* ゲームクリア後のママの会話
01 ゲームクリアしてイベント発動可能状態
02 イベント終了
*/

#define WK_SCENE_D25R0102		(SVSCRWK_START+160)
/*	d25r0102 森の洋館ゴーストイベント
01 ゴーストイベント発生時 
*/

#define WK_SCENE_D25R0108		(SVSCRWK_START+161)
/*	d25r0108 森の洋館ゴーストイベント
01 ゴーストイベント発生時 
*/

#define WK_SCENE_L02_BIGMAN		(SVSCRWK_START+162)
/*	L02ナギサ方面へのストッパー
00 ストッパー有効
01 ストッパー解除
*/

#define WK_SCENE_C11R0101		(SVSCRWK_START+163)
/*	C11R0101　バトルタワー受付ゲート
00 初めて到達
01 それ以外
*/

#define WK_SCENE_C04_STOPPER	(SVSCRWK_START+164)
/*	C04のストッパー
00 ストッパー有効
01 ストッパー解除
*/

#define WK_SCENE_PLATE_MSG		(SVSCRWK_START+165)
/*	プレートメッセージワーク
01 - 08 メッセージ
*/

#define WK_SCENE_R212AR0101_POLICEMAN	(SVSCRWK_START+166)
/* おまわりさん
00 無効
01 有効
*/ 

#define WK_SCENE_T04R0301_RE_ITEM	(SVSCRWK_START+167)
/* 預けているアイテム番号
*/

#define WK_SCENE_D05R0116	(SVSCRWK_START+168)
/* D05R0116 アウスの出現場所
01 アウスエンカウントイベント発生時
*/

#define WK_SCENE_R227_SEVEN2		(SVSCRWK_START+169)
/* R227イベント
01 ５人衆イベント終了
*/

#define WK_SCENE_C07_SUPPORT_GYM_AFTER		(SVSCRWK_START+170)
/* C07ジム後のサポートイベント
01 イベント開始
02 イベント終了
*/

#define WK_SCENE_C04_STOPPER_02	(SVSCRWK_START+171)
/*	C04のストッパー じてんしゃストッパー
00 ストッパー解除(まだ自転車を貰っていない)
01 ストッパー有効
02 R207サポートイベント終了（ストッパー解除）
*/

#define WK_SCENE_CYCLINGROAD	(SVSCRWK_START+172)
/* サイクリングロード
01 サイクリングロードに入ったので自転車状態にする(変更したら0に戻る)
*/

//#define WK_SCENE_NONE		(SVSCRWK_START+176)			/* Max = 176 */
//------------------------------------------------------------------------
//------------------------------------------------------------------------

//------------------------------------------------------------------------
//------------------------------------------------------------------------

#endif	//__SAVEWORK_H__
