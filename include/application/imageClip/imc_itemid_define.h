//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_itemid_define.h
 *	@brief
 *	@author	
 *	@data		2006.04.05
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __IMC_ITEMID_DEFINE_H__
#define __IMC_ITEMID_DEFINE_H__

#undef GLOBAL
#ifdef	__IMC_ITEMID_DEFINE_H_GLOBAL
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
//	
//	アクセサリリスト
//
//=====================================
#define	IMC_ACCE_WATA00			(0)			// しろいわたげ
#define	IMC_ACCE_WATA01			(1)			// きいろのわたげ
#define	IMC_ACCE_WATA02			(2)			// ピンクのわたげ
#define	IMC_ACCE_WATA03			(3)			// ちゃいろのわたげ
#define	IMC_ACCE_WATA04			(4)			// くろいわたげ
#define	IMC_ACCE_WATA05			(5)			// オレンジのわたげ
#define	IMC_ACCE_STONE00		(6)			// まんまるストーン
#define	IMC_ACCE_STONE01		(7)			// きらきらストーン
#define	IMC_ACCE_STONE02		(8)			// こつこつストーン
#define	IMC_ACCE_STONE03		(9)			// ごつごつストーン
#define	IMC_ACCE_STONE04		(10)		// まっくろストーン
#define	IMC_ACCE_STONE05		(11)		// ちびストーン
#define	IMC_ACCE_UROKO00		(12)		// ピンクのウロコ
#define	IMC_ACCE_UROKO01		(13)		// あおいウロコ
#define	IMC_ACCE_UROKO02		(14)		// みどりのウロコ
#define	IMC_ACCE_UROKO03		(15)		// むらさきのウロコ
#define	IMC_ACCE_UROKO04		(16)		// おおきいウロコ
#define	IMC_ACCE_UROKO05		(17)		// ほそいウロコ
#define	IMC_ACCE_HANE00			(18)		// あおいはね
#define	IMC_ACCE_HANE01			(19)		// あかいはね
#define	IMC_ACCE_HANE02			(20)		// きいろのはね
#define	IMC_ACCE_HANE03			(21)		// しろいはね
#define	IMC_ACCE_HANE_TABA00	(22)		// くろいちょびひげ
#define	IMC_ACCE_HANE_TABA01	(23)		// しろいちょびひげ
#define	IMC_ACCE_HANE_GROUP00	(24)		// くろいひげ
#define	IMC_ACCE_HANE_GROUP01	(25)		// しろいひげ
#define	IMC_ACCE_LEAF00			(26)		// ちいさいはっぱ
#define	IMC_ACCE_LEAF01			(27)		// おおきいはっぱ
#define	IMC_ACCE_LEAF02			(28)		// ほそいはっぱ
#define	IMC_ACCE_TUME00			(29)		// つめのカラ
#define	IMC_ACCE_TUME01			(30)		// つののカラ
#define	IMA_ACCE_MUSHROOM00		(31)		// ほそいキノコ
#define	IMA_ACCE_MUSHROOM01		(32)		// ふといキノコ
#define	IMC_ACCE_KIRIKABU00		(33)		// きりかぶ
#define	IMC_ACCE_DROP00			(34)		// きれいなしずく
#define	IMC_ACCE_SNOWDUST00		(35)		// ゆきのけっしょう
#define	IMC_ACCE_SPARK00		(36)		// パチパチひばな
#define	IMC_ACCE_FIRE00			(37)		// メラメラほのお
#define	IMC_ACCE_FIRE01			(38)		// ふしぎなほのお
#define	IMC_ACCE_KIAI00			(39)		// にじみでるきあい
#define	IMC_ACCE_SPOON00		(40)		// ふしぎなスプーン
#define	IMC_ACCE_SMOKE00		(41)		// モコモコけむり
#define	IMC_ACCE_HEDORO00		(42)		// どくエキス
#define	IMC_ACCE_COIN00			(43)		// おかねもちコイン
#define	IMC_ACCE_HORROR00		(44)		// ぶきみなもの
#define	IMC_ACCE_SPRING00		(45)		// バネ
#define	IMC_ACCE_SHELL00		(46)		// かいのかけら
#define	IMC_ACCE_NOTE00			(47)		// はなうたおんぷ
#define	IMC_ACCE_PIKAPIKA_POWDER00	(48)	// ピカピカパウダー
#define	IMC_ACCE_KIRAKIRA_POWDER00	(49)	// キラキラパウダー
#define	IMC_ACCE_FLOWER00		(50)		// あかいはな
#define	IMC_ACCE_FLOWER01		(51)		// ピンクのはな
#define	IMC_ACCE_FLOWER02		(52)		// しろいはな
#define	IMC_ACCE_FLOWER03		(53)		// あおいはな
#define	IMC_ACCE_FLOWER04		(54)		// オレンジのはな
#define	IMC_ACCE_FLOWER05		(55)		// きいろのはな
#define	IMC_ACCE_GLASSES00		(56)		// ぐるぐるメガネ
#define	IMC_ACCE_GLASSES01		(57)		// まっくろメガネ
#define	IMC_ACCE_GLASSES02		(58)		// ゴージャスメガネ
#define	IMC_ACCE_CANDY00		(59)		// あまいキャンディ
#define	IMC_ACCE_PAPERSTORM00	(60)		// かみふぶき
#define	IMC_ACCE_PARASOL00		(61)		// カラフルパラソル
#define	IMC_ACCE_PARASOL01		(62)		// カラカサ
#define	IMC_ACCE_SPOTLIGHT00	(63)		// スポットライト
#define	IMC_ACCE_CAPE00			(64)		// マント
#define	IMC_ACCE_MIKE00			(65)		// スタンドマイク
#define	IMC_ACCE_SURFBOARD00	(66)		// サーフボード
#define	IMC_ACCE_ZYUTAN00		(67)		// カーペット
#define	IMC_ACCE_DOKAN00		(68)		// なつかしどかん
#define	IMC_ACCE_BED00			(69)		// ふわふわベッド
#define	IMC_ACCE_BALL00			(70)		// ミラーボール
#define	IMC_ACCE_BAG00			(71)		// かおだしかんばん
#define	IMC_ACCE_RIBBON00		(72)		// ピンクのかみどめ
#define	IMC_ACCE_RIBBON01		(73)		// まっかなかみどめ
#define	IMC_ACCE_RIBBON02		(74)		// ブルーのかみどめ
#define	IMC_ACCE_RIBBON03		(75)		// きいろのかみどめ
#define	IMC_ACCE_RIBBON04		(76)		// みどりのかみどめ
#define	IMC_ACCE_BALLOON00		(77)		// ピンクのふうせん
#define	IMC_ACCE_BALLOON01		(78)		// あかいふうせん
#define	IMC_ACCE_BALLOON02		(79)		// あおいふうせん
#define	IMC_ACCE_BALLOON03		(80)		// きいろのふうせん
#define	IMC_ACCE_BALLOON04		(81)		// みどりのふうせん
#define	IMC_ACCE_HAT00			(82)		// ヘッドドレス
#define	IMC_ACCE_HAT01			(83)		// シルクハット
#define	IMC_ACCE_HAT02			(84)		// きぬのベール
#define	IMC_ACCE_HAT03			(85)		// たなびくハチマキ
#define	IMC_ACCE_HAT04			(86)		// はかせのぼうし
#define	IMC_ACCE_STAGE00		(87)		// おはなのステージ
#define	IMC_ACCE_STAGE01		(88)		// きんのおたちだい
#define	IMC_ACCE_STAGE02		(89)		// ガラスのステージ
#define	IMC_ACCE_HYOSHODAI00	(90)		// ひょうしょうだい
#define	IMC_ACCE_STAGE03		(91)		// キューブステージ
#define	IMC_ACCE_OMEN00			(92)		// ナエトルおめん
#define	IMC_ACCE_OMEN01			(93)		// ヒコザルおめん
#define	IMC_ACCE_OMEN02			(94)		// ポッチャマおめん
#define	IMC_ACCE_TREE00			(95)		// おおきいき
#define	IMC_ACCE_FLAG00			(96)		// フラッグ
#define	IMC_ACCE_CROWN00		(97)		// クラウン
#define	IMC_ACCE_TIARA00		(98)		// ティアラ
#define	IMC_ACCE_NAGAREBOSI00	(99)		// ながれぼし

#define	IMC_ACCE_MAX			(100)

//-------------------------------------
//	
// BGデータ列挙
//	
//=====================================
// 右画面用
#define	IMC_BG_RIGHT_00		(0)
#define	IMC_BG_RIGHT_01		(1)
#define	IMC_BG_RIGHT_02		(2)
#define	IMC_BG_RIGHT_03		(3)
#define	IMC_BG_RIGHT_04		(4)
#define	IMC_BG_RIGHT_05		(5)
#define	IMC_BG_RIGHT_06		(6)
#define	IMC_BG_RIGHT_07		(7)
#define	IMC_BG_RIGHT_08		(8)
#define	IMC_BG_RIGHT_09		(9)
#define	IMC_BG_RIGHT_10		(10)
#define	IMC_BG_RIGHT_11		(11)
#define	IMC_BG_RIGHT_12		(12)
#define	IMC_BG_RIGHT_13		(13)
#define	IMC_BG_RIGHT_14		(14)
#define	IMC_BG_RIGHT_15		(15)
#define	IMC_BG_RIGHT_16		(16)
#define	IMC_BG_RIGHT_17		(17)
#define	IMC_BG_RIGHT_MAX	(18)


//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
#undef	GLOBAL
#endif		// __IMC_ITEMID_DEFINE_H__

