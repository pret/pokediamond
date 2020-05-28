//============================================================================================
/**
 * @file	sysflag_def.h
 * @bfief	システムフラグ定義
 * @author	Satoshi Nohara
 * @date	06.04.14
 */
//============================================================================================
#ifndef	__SYSFLAG_DEF_H__
#define	__SYSFLAG_DEF_H__


//============================================================================================
//	フラグ定義
//
//	スクリプト			定義を直接参照してよい！
//
//	プログラム			sysflag.hにあるアクセス関数を使う！
//
//	SYSFLAG_MAX = 320
//	SYS_FLAG_ARRIVE_START(80) ナンバーが重複しないように注意！
//============================================================================================
#define	SYS_FLAG_BAG_GET				(SYSFLAG_START+0)		//バッグ入手
#define	SYS_FLAG_PAIR					(SYSFLAG_START+1)		//連れ歩きフラグ
#define	SYS_FLAG_KAIRIKI				(SYSFLAG_START+2)		//かいりき状態フラグ
#define	SYS_FLAG_FNOTE_GET				(SYSFLAG_START+3)		//冒険ノート入手
#define	SYS_FLAG_GAME_CLEAR				(SYSFLAG_START+4)		//ゲームクリア
#define	SYS_FLAG_ONE_STEP				(SYSFLAG_START+5)		//一歩動いたかフラグ
#define	SYS_FLAG_COMM_COUNTER			(SYSFLAG_START+6)		//通信カウンター通過フラグ
#define	SYS_FLAG_SAFARI_MODE			(SYSFLAG_START+7)		//サファリモードフラグ
#define	SYS_FLAG_CON_STYLE_MASTER		(SYSFLAG_START+8)		//コンテストマスターランククリア
#define	SYS_FLAG_CON_BEAUTIFUL_MASTER	(SYSFLAG_START+9)		//コンテストマスターランククリア
#define	SYS_FLAG_CON_CUTE_MASTER		(SYSFLAG_START+10)		//コンテストマスターランククリア
#define	SYS_FLAG_CON_CLEVER_MASTER		(SYSFLAG_START+11)		//コンテストマスターランククリア
#define	SYS_FLAG_CON_STRONG_MASTER		(SYSFLAG_START+12)		//コンテストマスターランククリア
#define	SYS_FLAG_BTL_SEARCHER_USE		(SYSFLAG_START+13)		//バトルサーチャーを使用中
#define	SYS_FLAG_UG_ARRIVE				(SYSFLAG_START+14)		//地下：到着
#define	SYS_FLAG_UG_DIG					(SYSFLAG_START+15)		//地下：化石
#define	SYS_FLAG_UG_TAMA				(SYSFLAG_START+16)		//地下：玉
#define	SYS_FLAG_UG_BASE				(SYSFLAG_START+17)		//地下：基地
#define	SYS_FLAG_UG_GOODS				(SYSFLAG_START+18)		//地下：模様替え
#define	SYS_FLAG_UG_HATA				(SYSFLAG_START+19)		//地下：旗
#define	SYS_FLAG_GTC_OPEN				(SYSFLAG_START+20)		//施設：GTC
#define	SYS_FLAG_BTOWER_OPEN			(SYSFLAG_START+21)		//施設：バトルタワー
#define	SYS_FLAG_SHIP					(SYSFLAG_START+22)		//船使用可能
//#define	SYS_FLAG_					(SYSFLAG_START+23)		//
#define	SYS_FLAG_PST					(SYSFLAG_START+24)		//ポケモンステータス　コンテスト技
#define	SYS_FLAG_POKEPARK_MODE			(SYSFLAG_START+25)		//ポケパークモードフラグ
#define SYS_FLAG_FLASH					(SYSFLAG_START+26)		//フラッシュ状態フラグ
#define	SYS_FLAG_KIRIBARAI				(SYSFLAG_START+27)		//霧払い状態フラグ
#define	SYS_FLAG_POKETCH_HOOK			(SYSFLAG_START+28)		//ポケッチ抑止フラグ
#define	SYS_FLAG_REIAIHAI				(SYSFLAG_START+29)		//レイアイハイ救出フラグ
#define	SYS_FLAG_MIZUKI					(SYSFLAG_START+30)		//ミズキフラグ(PC管理者)
#define	SYS_FLAG_BS_LV1					(SYSFLAG_START+31)		//バトルサーチャーLV1
#define	SYS_FLAG_BS_LV2					(SYSFLAG_START+32)		//バトルサーチャーLV2
#define	SYS_FLAG_BS_LV3					(SYSFLAG_START+33)		//バトルサーチャーLV3
#define	SYS_FLAG_BS_LV4					(SYSFLAG_START+34)		//バトルサーチャーLV4
#define	SYS_FLAG_BS_LV5					(SYSFLAG_START+35)		//バトルサーチャーLV5
#define	SYS_FLAG_BGM_D28				(SYSFLAG_START+36)		//イベントBGM切り替え
#define	SYS_FLAG_BGM_GINGA				(SYSFLAG_START+37)		//イベントBGM切り替え
#define	SYS_FLAG_BGM_D26				(SYSFLAG_START+38)		//イベントBGM切り替え
#define	SYS_FLAG_BGM_C04				(SYSFLAG_START+39)		//イベントBGM切り替え
#define	SYS_FLAG_BGM_D02				(SYSFLAG_START+40)		//イベントBGM切り替え
#define	SYS_FLAG_BGM_D13				(SYSFLAG_START+41)		//イベントBGM切り替え
#define	SYS_FLAG_BGM_R224				(SYSFLAG_START+42)		//イベントBGM切り替え
#define	SYS_FLAG_BGM_C10				(SYSFLAG_START+43)		//イベントBGM切り替え
#define	SYS_FLAG_WIFI_USE				(SYSFLAG_START+44)		//WiFiに繋いだ
#define	SYS_FLAG_T05_GINGA_EVENT		(SYSFLAG_START+45)		//カンナギのギンガ団イベント
#define	SYS_FLAG_BGM_D27				(SYSFLAG_START+46)		//イベントBGM切り替え
#define	SYS_FLAG_BGM_D29				(SYSFLAG_START+47)		//イベントBGM切り替え
#define	SYS_FLAG_BGM_D16				(SYSFLAG_START+48)		//イベントBGM切り替え
#define	SYS_FLAG_BGM_C02				(SYSFLAG_START+49)		//イベントBGM切り替え
#define	SYS_FLAG_UG_FIRST				(SYSFLAG_START+50)		//地下初回イベント
#define	SYS_FLAG_BGM_T02				(SYSFLAG_START+51)		//イベントBGM切り替え
#define SYS_FLAG_CYCLINGROAD			(SYSFLAG_START+52)		//サイクリングロードモードフラグ
#define	SYS_FLAG_BGM_D10				(SYSFLAG_START+53)		//イベントBGM切り替え


//--------------------------------------------------------------------------------------------
//到着フラグ操作用定義
//
//	SYSFLAG_MAX = 320
//	SYS_FLAG_ARRIVE_START(80) + FLAG_ARRIVE_MAX(66) = 146 超えないように注意！
//--------------------------------------------------------------------------------------------
#define	SYS_FLAG_ARRIVE_START			(SYSFLAG_START+80)

#define	FLAG_ARRIVE_T01		( 0)
#define	FLAG_ARRIVE_T02		( 1)
#define	FLAG_ARRIVE_T03		( 2)
#define	FLAG_ARRIVE_T04		( 3)
#define	FLAG_ARRIVE_T05		( 4)
#define	FLAG_ARRIVE_T06		( 5)
#define	FLAG_ARRIVE_T07		( 6)
#define	FLAG_ARRIVE_C01		( 7)
#define	FLAG_ARRIVE_C02		( 8)
#define	FLAG_ARRIVE_C03		( 9)
#define	FLAG_ARRIVE_C04		(10)
#define	FLAG_ARRIVE_C05		(11)
#define	FLAG_ARRIVE_C06		(12)
#define	FLAG_ARRIVE_C07		(13)
#define	FLAG_ARRIVE_C08		(14)
#define	FLAG_ARRIVE_C09		(15)
#define	FLAG_ARRIVE_C10		(16)
#define	FLAG_ARRIVE_C11		(17)

//060525 施設到着フラグ追加
#define FLAG_ARRIVE_D01R0101	(18)	//クロガネ炭鉱//
#define FLAG_ARRIVE_D02R0101	(19)	//谷間の発電所//
#define FLAG_ARRIVE_D03			(20)	//フラグ不要//ハクタイの森
#define FLAG_ARRIVE_D04R0101	(21)	//タタラ製鉄所//
#define FLAG_ARRIVE_D05			(22)	//フラグ不要//天冠山
#define FLAG_ARRIVE_D05R0114	(23)	//槍の柱//
#define FLAG_ARRIVE_D06			(24)	//フラグ不要//大湿原
#define FLAG_ARRIVE_D07R0102	(25)	//ズイの遺跡//
#define FLAG_ARRIVE_D09R0101	(26)	//チャンピオンロード//
#define FLAG_ARRIVE_D10R0101	(27)	//ポケモンパーク//
#define FLAG_ARRIVE_D11R0101	(28)	//触れあい広場//
#define FLAG_ARRIVE_D12R0101	(29)	//荒れた抜け道//
#define FLAG_ARRIVE_D13R0101	(30)	//ソノオの花畑//
#define FLAG_ARRIVE_D14R0101	(31)	//クロガネゲート//
#define FLAG_ARRIVE_D15			(32)	//隠しマップフラグ//隠しポケモン「ムーバス」の島
#define FLAG_ARRIVE_D16			(33)	//フラグ不要//火山
#define FLAG_ARRIVE_D16R0101	(34)	//ハードマウンテン（火山洞窟）//
#define FLAG_ARRIVE_D17			(35)	//隠しマップフラグ//送りの泉（Ｌ０４湖）
#define FLAG_ARRIVE_D17R0102	(36)	//戻りの洞窟//
#define FLAG_ARRIVE_D18			(37)	//隠しマップフラグ//配布ポケモン「エウリス」の島。
#define FLAG_ARRIVE_D20R0101	(38)	//キッサキ神殿//
#define FLAG_ARRIVE_D21R0101	(39)	//迷いの洞窟//
#define FLAG_ARRIVE_D22R0101	(40)	//遺跡マニアの穴//
#define FLAG_ARRIVE_D23R0101	(41)	//自慢の裏庭//
#define FLAG_ARRIVE_D24			(42)	//フラグ不要//鋼鉄島
#define FLAG_ARRIVE_D24R0101	(43)	//鉱山//
#define FLAG_ARRIVE_D25R0101	(44)	//森の洋館//
#define FLAG_ARRIVE_D26R0101	(45)	//ギンガ団アジト//
#define FLAG_ARRIVE_D27			(46)	//フラグ不要//Ｌ０１湖
#define FLAG_ARRIVE_D27R0103	(47)	//Ｌ０１湖の内部洞窟//
#define FLAG_ARRIVE_D28			(48)	//フラグ不要//Ｌ０２湖
#define FLAG_ARRIVE_D28R0103	(49)	//Ｌ０２湖の内部洞窟//
#define FLAG_ARRIVE_D29			(50)	//フラグ不要//Ｌ０３湖
#define FLAG_ARRIVE_D29R0103	(51)	//Ｌ０３湖の内部洞窟//
#define FLAG_ARRIVE_D30			(52)	//隠しマップフラグ//配布ポケモン「ダーク」の島
#define FLAG_ARRIVE_C11R0101	(53)	//バトルタワー受付ゲート//
#define FLAG_ARRIVE_R206		(54)	//フラグ不要//サイクリングロード
#define FLAG_ARRIVE_R208R0101	(55)	//木の実爺//
#define FLAG_ARRIVE_R209R0101	(56)	//ロストタワー//
#define FLAG_ARRIVE_R210AR0101	(57)	//喫茶店//
#define FLAG_ARRIVE_R210BR0101	(58)	//最強ドラゴン技教えの家//
#define FLAG_ARRIVE_R212AR0101	(59)	//ポケモン屋敷と裏庭//
#define FLAG_ARRIVE_R212BR0101	(60)	//かけらと道具を交換してくれる民家//
#define FLAG_ARRIVE_R213R0201	(61)	//足跡博士の家//
#define FLAG_ARRIVE_L02R0101	(62)	//ホテルレストラン//
#define FLAG_ARRIVE_R222R0101	(63)	//釣りオヤジの家//
#define FLAG_ARRIVE_R222R0201	(64)	//大きさ比べの家//
#define FLAG_ARRIVE_W226R0101	(65)	//海外版ポケモンと交換してくれる親父//

#define	FLAG_ARRIVE_R221		(66)	//ポケパーク施設//
#define	FLAG_ARRIVE_R221R0101	(67)	//ポケパーク受付//
#define	FLAG_ARRIVE_CHAMPLEAGUE	(68)	//チャンピオンリーグ//

#define	FLAG_ARRIVE_MAX			(69)


//フラグの最大数など確認する！


//============================================================================================
//
//============================================================================================
//バッジ共通定義(MyStatus_GetBadgeFlag)
#define BADGE_ID_C03			(0)						//クロガネ
#define BADGE_ID_C04			(1)						//ハクタイ
#define BADGE_ID_C07			(2)						//トパリ
#define BADGE_ID_C06			(3)						//ノモセ
#define BADGE_ID_C05			(4)						//ヨスガ
#define BADGE_ID_C02			(5)						//ミオ
#define BADGE_ID_C09			(6)						//キッサキ
#define BADGE_ID_C08			(7)						//ナギサ
#define BADGE_MAX				(8)						//バッジ最大数

#endif	//__SYSFLAG_DEF_H__


