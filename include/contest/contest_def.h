//==============================================================================
/**
 * @file	contest_def.h
 * @brief	コンテストのヘッダ：スクリプトなどからもincludeされるのでenum禁止！
 * @author	matsuda
 * @date	2005.12.14(水)
 */
//==============================================================================
#ifndef __CONTEST_DEF_H__
#define __CONTEST_DEF_H__


///コンテストの最大参加人数
#define BREEDER_MAX				(4)
///コンテストの通信最大参加人数
///BREEDER_MAXとの違いはブリーダーNoで管理されているものはBREEDER_MAXを使用し、
///ネットIDで管理されているものはCC_NETID_MAXを使用しています。
///2005.12.18(日) 現在は ブリーダーNo＝ネットID になっているので厳密には気にしなくて大丈夫です
#define CC_NETID_MAX			(4)

//--------------------------------------------------------------
//	コンテストタイプ
//--------------------------------------------------------------
///コンテストタイプ：格好よさ
#define CONTYPE_STYLE		(0)
///コンテストタイプ：美しさ
#define CONTYPE_BEAUTIFUL	(1)
///コンテストタイプ：可愛さ
#define CONTYPE_CUTE		(2)
///コンテストタイプ：賢さ
#define CONTYPE_CLEVER		(3)
///コンテストタイプ：逞しさ
#define CONTYPE_STRONG		(4)

///コンテストタイプ：最大
#define CONTYPE_MAX		(5)

//--------------------------------------------------------------
//	コンテストランク
//--------------------------------------------------------------
///コンテストランク：ノーマルランク
#define CONRANK_NORMAL		(0)
///コンテストランク：スーパーランク(新名称：グレートランク)
#define CONRANK_SUPER		(1)
///コンテストランク：ハイパーランク(新名称：ウルトラランク)
#define CONRANK_HYPER		(2)
///コンテストランク：マスターランク
#define CONRANK_MASTER		(3)

///コンテストランク：イメージクリップ用定義　通信ランク
#define CONRANK_IMC_SIO		(CONRANK_MASTER + 1)
///コンテストランク：最大
#define CONRANK_MAX			(4)

//--------------------------------------------------------------
//	コンテストモード(コンテストを行う順番)
//--------------------------------------------------------------
///チャームモード(ビジュアル部門＞演技部門)：ポケモンコンテスト
#define CONMODE_CHARM					(0)
///アクティブモード(ビジュアル部門＞ダンス部門)：ポケモンコンクール
#define CONMODE_ACTIVE					(1)
///グランドモード(ビジュアル部門＞ダンス部門＞演技部門)：ポケモントライアル
#define CONMODE_GRAND					(2)
///ビジュアル練習モード
#define CONMODE_VISUAL_PRACTICE			(3)
///ビジュアルチュートリアルモード
#define CONMODE_VISUAL_TUTORIAL			(4)
///ダンス練習モード
#define CONMODE_DANCE_PRACTICE			(5)
///ダンスチュートリアルモード
#define CONMODE_DANCE_TUTORIAL			(6)
///演技練習モード
#define CONMODE_ACTIN_PRACTICE			(7)
///演技チュートリアルモード
#define CONMODE_ACTIN_TUTORIAL			(8)

//--------------------------------------------------------------
//	参加しているゲーム(コンテストの種類)
//--------------------------------------------------------------
///ビジュアル
#define CONGAME_VISUAL		(0)
///ダンス
#define CONGAME_DANCE		(1)
///演技
#define CONGAME_ACTIN		(2)

//--------------------------------------------------------------
//	イメージクリップのテーマ
//--------------------------------------------------------------
///イメージクリップテーマ：華やかなもの(新名称:かたちあるもの)
#define CON_IMAGE_THEME_FLOWERY			(0)
///イメージクリップテーマ：シンプルなもの(新名称:とんがったもの)
#define CON_IMAGE_THEME_SIMPLE			(1)
///イメージクリップテーマ：人工のもの(新名称:つくられたもの)
#define CON_IMAGE_THEME_ARTIFICIAL		(2)
///イメージクリップテーマ：自然のもの
#define CON_IMAGE_THEME_NATURAL			(3)
///イメージクリップテーマ：色つきのもの
#define CON_IMAGE_THEME_COLORFUL		(4)
///イメージクリップテーマ：にぎやかなもの(新名称:しっかりしたもの)
#define CON_IMAGE_THEME_LIVELY			(5)
///イメージクリップテーマ：すっきりしたもの(新名称:あかるいもの)
#define CON_IMAGE_THEME_REFRESH			(6)
///イメージクリップテーマ：ギリギリのもの(新名称:はでなもの)
#define CON_IMAGE_THEME_LIMIT			(7)
///イメージクリップテーマ：ゆるやかなもの(新名称:しなやかなもの)
#define CON_IMAGE_THEME_SOFTLY			(8)
///イメージクリップテーマ：きらびやかなもの
#define CON_IMAGE_THEME_GORGEOUS		(9)
///イメージクリップテーマ：上品なもの(新名称:かたちのないもの)
#define CON_IMAGE_THEME_ELEGANT			(10)
///イメージクリップテーマ：派手なもの(新名称:おちついたもの)
#define CON_IMAGE_THEME_SHOWY			(11)

///イメージクリップテーマ：最大数
#define CON_IMAGE_THEME_MAX				(12)

//--------------------------------------------------------------
//	イメージクリップでつけられる個数
//--------------------------------------------------------------
///ノーマルランクで付けられるアクセサリ最大数
#define CON_IMAGE_ACCE_MAX_NORMAL		(5)
///スーパーランクで付けられるアクセサリ最大数
#define CON_IMAGE_ACCE_MAX_SUPER		(10)
///ハイパーランクで付けられるアクセサリ最大数
#define CON_IMAGE_ACCE_MAX_HYPER		(15)
///マスターランクで付けられるアクセサリ最大数
#define CON_IMAGE_ACCE_MAX_MASTER		(20)
///通信対戦で付けられるアクセサリ最大数
#define CON_IMAGE_ACCE_MAX_SIO			(20)


//==============================================================================
//	通信同期待ち用の番号定義
//==============================================================================
///コンテスト側での開始時の最初の同期待ち
#define CONSIO_TIMING_START				(0)

///イメージクリップ画面呼び出し前の同期待ち
#define CONSIO_TIMING_CALL_IMC			(1)
///イメージクリッププロック内で使用する同期待ち
#define CONSIO_TIMING_CALL_IN_IMCPROC	(2)

///スクリプト：開始時の同期待ち
#define CONSIO_TIMING_SCR_START			(3)
///スクリプト：イメージクリップ呼び出し前の同期待ち
#define CONSIO_TIMING_SCR_IMC			(4)

#define CONSIO_TIMING_FAST_PARAM		(5)
#define CONSIO_TIMING_POKE				(6)
#define CONSIO_TIMING_POKE_RESEND		(7)
#define CONSIO_TIMING_BD				(8)
#define CONSIO_TIMING_BD_RESEND			(9)
#define CONSIO_TIMING_NAME				(10)
#define CONSIO_TIMING_NAME_RESEND		(11)
#define CONSIO_TIMING_PERAP				(12)
#define CONSIO_TIMING_PERAP_RESEND		(13)
#define CONSIO_TIMING_ETC				(14)
#define CONSIO_TIMING_ETC_RESEND		(15)
#define CONSIO_TIMING_JUDGE				(16)
#define CONSIO_TIMING_IMC				(17)
#define CONSIO_TIMING_IMC_RESEND		(18)

///スクリプト：要所要所での同期待ち
#define CONSIO_TIMING_SCR_0				(19)
#define CONSIO_TIMING_SCR_1				(20)
#define CONSIO_TIMING_SCR_2				(21)
#define CONSIO_TIMING_SCR_3				(22)
#define CONSIO_TIMING_SCR_4				(23)
#define CONSIO_TIMING_SCR_END			(24)
#define CONSIO_TIMING_SCR_5				(25)
#define CONSIO_TIMING_SCR_6				(26)


#endif	//__CONTEST_DEF_H__

