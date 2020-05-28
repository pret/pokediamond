//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		nmix_game_comm.h
 *	@brief		ゲーム内容　通信データ構造体
 *	@author		tomoya takahashi
 *	@data		2006.05.25
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __NMIX_GAME_COMM_H__
#define __NMIX_GAME_COMM_H__

#include "nutmixer_def.h"
#include "include/savedata/mystatus.h"
#include "communication/communication.h"
#include "include/savedata/poruto_util.h"

#undef GLOBAL
#ifdef	__NMIX_GAME_COMM_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------

#ifdef PM_DEBUG
#define NMIX_DEBUG_DUMMY_RESULT_ON
#endif // PM_DEBUG



//-------------------------------------
//	こげリクエスト定数
//=====================================
#define NMIX_GAME_COMM_KOGE_KOGE_REQ	( 1 )
#define NMIX_GAME_COMM_KOGE_KEMURI_REQ	( 2 )

//-------------------------------------
//	スープタイプ定義
//=====================================
enum{
	NMIX_SOOPTYPE_SOOP_0,
	NMIX_SOOPTYPE_SOOP_1,
	NMIX_SOOPTYPE_SOOP_2,
	NMIX_SOOPTYPE_SOOP_NUM,
};


// スープ回転中心座標
#define NMIX_SOOP_ROTA_CX	( 128 )
#define NMIX_SOOP_ROTA_CY	( 96 )

// ワードセット最大数
#define NMIX_GAME_WORD_SET_MAX	( 4 )

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	ゲーム開始前データ	子ー＞親
//	4
//=====================================
typedef struct {
	u32			nut_type;	// 木の実タイプ			
} NUTMIX_GAME_BGFORE;

//-------------------------------------
//	各々のデータ
//	8byte
//=====================================
typedef struct {
	u8  x;			// 現在X座標
	u8  y;			// 現在Y座標
	u16 rota;		// 回転角度
	
	u8  rota_way;	// 0:右 1:左	回転方向
	u8	dummy[3];	// 4byte境界用
} NUTMIX_ONE;

//-------------------------------------
//	親の転送するデータ
//	20byte
//=====================================
typedef struct {
	u8	x[NUTMIXER_MEMBER_MAX];	// 皆のｘ座標
	u8	y[NUTMIXER_MEMBER_MAX];	// 皆のｙ座標

	u16 rota;			// スープ回転角度
	u16	rota_sp;		// 今の回転速度
	u8  rota_way;		// 0:右 1:左	回転方向
	u8	mix_type;		// 今のスープの形状	3タイプ	
	u8	rota_req_eff;	// 回転方向が変わったのでエフェクト出す
	u8	kirakira_eff;	// キラキラエフェクトを出すタイミング

	u8	alpha_num;		// 形状のα値（下の形状に溶け込んでいく）
	u8	now_rota_req;	// 今回転してほしい方向　0:右回転 1:左回転
	u8	koge_req;		// こげリクエスト
	u8	kobore_req;		// こぼれリクエスト
} NUTMIX_OYA;

//-------------------------------------
//	ゲーム中の通信ワーク
//	28byte
//=====================================
typedef struct {
	NUTMIX_ONE one;		// それぞれのデータ
	NUTMIX_OYA oya;		// 親データ
} NUTMIX_COMM_DATA;

//-------------------------------------
//	皆の木の実データ
//	親->子
//=====================================
typedef struct {
	NUTMIX_GAME_BGFORE before[ NUTMIXER_MEMBER_MAX ];
	NUTMIX_OYA oya;		// 初期親データ
} NUTMIX_COMM_BEFORE_KO;


//-------------------------------------
//	計算結果表示用通信ワーク
//	親ー＞子
//	20byte
//=====================================
typedef struct {
	u32	kobore_num;	// こぼれた数
	
	u32	kogasi_num;	// 焦がした数

	u32	match_num;	// チームワーク得点

	u8	poruto_type;// 出来たポルトのタイプ
	u8	poruto_lv;	// 出来たポルトのレベル
	u8	min;		// 分
	u8	second;		// 秒
	
	u8	dec;		// コンマ
	u8	dummy[3];	// 4byte境界のため
} NUTMIX_COMM_RESULT;


//-------------------------------------
//	ゲーム内通信データ　パック構造体
//=====================================
typedef struct {
	// 送信データ
	NUTMIX_GAME_BGFORE  send_before_data;	// 自分の木の実など
	NUTMIX_COMM_DATA	send_game_data;		// 自分の位置　回転角	親のとき、ここに今のゲーム状態を追加で設定する

	// 親送信データ
	NUTMIX_COMM_RESULT	send_oya_result_data;		// ゲーム結果
	NUTMIX_COMM_BEFORE_KO get_oya_ko_before_data;	// この木の実情報

	// 受信バッファ
	NUTMIX_COMM_RESULT	get_result_data;			// ゲーム結果
	NUTMIX_COMM_BEFORE_KO get_ko_before_data;		// 皆の木の実情報
	NUTMIX_COMM_DATA	get_game_data[ NUTMIXER_MEMBER_MAX ];	// ゲームデータ
	PORUTO_DATA*	p_get_ko_poruto;	// ポルト取得バッファ

	// 親受信バッファ
	u32		get_oya_resutl_end[ NUTMIXER_MEMBER_MAX ];
	NUTMIX_GAME_BGFORE  get_before_data[ NUTMIXER_MEMBER_MAX ];
	u8		get_before_data_flg[ NUTMIXER_MEMBER_MAX ];
	u8		game_next[NUTMIXER_MEMBER_MAX];	// ゲームをつづけるか
	u8		get_next_data_flg[ NUTMIXER_MEMBER_MAX ];

	// プレイヤーナンバーからネットIDナンバーを取得
	u8	playno_netid[NUTMIXER_MEMBER_MAX];
	// プレイヤーステータス
	const MYSTATUS*	p_mystate[NUTMIXER_MEMBER_MAX];

	u8 my_netid;

	// 受信データ
	u8				get_game_next;		// ゲームを続けるとき TRUE
} NUTMIX_GAME_COMM_PACK;



//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
#undef	GLOBAL
#endif		// __NMIX_GAME_COMM_H__

