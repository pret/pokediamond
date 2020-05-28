//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_right_box.h
 *	@brief		右ボックスデータ
 *	@author		tomoya takahashi
 *	@data		2005.09.22
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __IMC_RIGHT_BOX_H__
#define __IMC_RIGHT_BOX_H__

#include <nnsys.h>

#include "include/application/imageClip/imc_accessorie.h"
#include "include/application/imageClip/imc_poke_obj.h"
#include "include/application/imageClip/imc_obj_list.h"
#include "include/application/imageClip/imc_bg.h"
#include "touchpanel.h"

#undef GLOBAL
#ifdef	__IMC_RIGHT_BOX_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------
#define	IMC_RBOX_ACCE_PRIORITY_START	(-1)		// アクセサリの表示優先順の番号
#define	IMC_RBOX_OBJ_MAX				(11)		// 右ボックスのオブジェクト登録最大数
													// アクセサリ10 + ポケモン1

#define	IMC_RBOX_OBJ_CONTEST_MAX		(21)		// 右ボックスのオブジェクト登録最大数

#define	IMC_RBOX_ACCE_TELEVISION_MAX	(10)		// 右ボックスのオブジェクト登録最大数
													// アクセサリ10

#define	IMC_RBOX_ACCE_CONTEST_MAX		(20)		// 右ボックスのアクセサリ最大数


//-------------------------------------
//	
//	BG用
//	
//=====================================
#define	IMC_RBOX_BG_PLTT_NUM	(1)		// パレット数
#define IMC_RBOX_BG_PLTT_OFFS	(1)		// パレット番号

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	右ボックス構造体	
//	描画部
//	
//=====================================
typedef struct {
	// 描画システムデータ
	// アクセサリ用
	SWSP_SYS_PTR	SWSP_drawSys;		// スプライト描画システム
	SWSP_CHAR_PTR*	SWSP_charData;		// キャラクタデータ配列
	SWSP_PLTT_PTR*	SWSP_plttData;		// パレットデータ配列
	u8* accePlttOfsTbl;

	// ポケモン用
	SOFT_SPRITE_MANAGER* SSM_drawSys;		// ポケモン描画用スプライト

	// BGデータ
	GF_BGL_INI*		BG_Ini;
	
	// アクセサリデータ
	IMC_ACCESSORIE_OBJ_TBL*	acce;

	
	// 右背景データ
	IMC_BG	bg;		// 右BGデータ
	int bg_no;		// 右BGナンバー
	
	// ポケモンデータ
	IMC_POKE	poke;
	
	// 音声データ
	
} IMC_RIGHT_BOXDRAW;

//-------------------------------------
//	
//	右ボックス構造体データ部
//	
//=====================================
typedef struct {
	// オブジェリスト
	IMC_OBJLIST_TBL*		objListTbl;
	IMC_OBJLIST				dummy;		// ポケモンの下
	IMC_OBJLIST				dummy_poke;	// ポケモンの上
	int		obj_count;		// アクセサリ登録数
	int		obj_count_max;	// アクセサリ登録最大数

} IMC_RIGHT_BOXDATA;


//-------------------------------------
//	
//	右ボックスデータ
//	
//=====================================
typedef struct {

	IMC_RIGHT_BOXDATA	boxData;
	IMC_RIGHT_BOXDRAW	boxDraw;
} IMC_RIGHT_BOX;



//-------------------------------------
//	
//	右ボックス初期化構造体	
//	
//=====================================
typedef struct {
	// アクセサリ用
	SWSP_SYS_PTR	SWSP_drawSys;		// スプライト描画システム
	SWSP_CHAR_PTR*	SWSP_charData;		// キャラクタデータ配列
	SWSP_PLTT_PTR*	SWSP_plttData;		// パレットデータ配列
	u8* accePlttOfsTbl;

	// ポケモン用
	SOFT_SPRITE_MANAGER* SSM_drawSys;		// ポケモン描画用スプライト

	// BGデータ
	GF_BGL_INI*		BG_Ini;

	IMC_ACCESSORIE_OBJ_TBL* acce;		// アクセサリリストデータ
	IMC_OBJLIST_TBL*		objListTbl;	// オブジェリストテーブル

	int acce_count_max;			// アクセサリ登録最大数
} IMC_RIGHT_BOX_INIT;

//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	右ボックス用領域作成
 *
 *	@param	rbox		右ボックス用データ
 *	@param	init		右ボックス初期化データ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_RBOX_InitSys( IMC_RIGHT_BOX* rbox, IMC_RIGHT_BOX_INIT* init );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	右ボック用領域破棄
 *
 *	@param	rbox		破棄する右ボックスデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_RBOX_DeleteSys( IMC_RIGHT_BOX* rbox );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ポケモンデータプレイヤー用作成
 *
 *	@param	rbox			右ボックスデータ
 *	@param	poke_para		作成するポケモンのポケモンパラメータ
 *	@param	arc_data		アーカイブファイルデータ格納領域
 *	@param	x				x座標
 *	@param	y				y座標
 *	@param	pri				表示優先順位
 *	@param	heap			ヒープID
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_RBOX_AddPokePlayer( IMC_RIGHT_BOX* rbox, POKEMON_PARAM* poke_para, SOFT_SPRITE_ARC* arc_data, int x, int y, int pri, int heap );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ポケモンデータ作成
 *
 *	@param	rbox			右ボックスデータ
 *	@param	poke_para		作成するポケモンのポケモンパラメータ
 *	@param	arc_data		アーカイブファイルデータ格納領域
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_RBOX_AddPoke( IMC_RIGHT_BOX* rbox, POKEMON_PARAM* poke_para, SOFT_SPRITE_ARC* arc_data, int heap );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ポケモン移動追加
 *
 *	@param	rbox	右ボックス
 *	@param	poke	ポケモンオブジェ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_RBOX_MoveAddPoke( IMC_RIGHT_BOX* rbox, IMC_OBJLIST* poke );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	移動させるためリストから削除
 *	
 *	@param	poke		ポケモンオブジェ
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_RBOX_MoveDeletePoke( IMC_OBJLIST* poke );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ポケモンオブジェクト破棄
 *
 *	@param	rbox	右ボックスデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_RBOX_DeletePoke( IMC_RIGHT_BOX* rbox );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	アクセサリの新規追加
 *
 *	@param	rbox				右ボックス用データ
 *	@param	accessorie_no		追加するアクセサリナンバー
 *	@param	x					X座標
 *	@param	y					Y座標
 *	@param	pri					表示優先順位
 *
 *	@retval	TRUE	成功
 *	@retval	FALSE	失敗	（登録最大数以上登録しようとした）
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL IMC_RBOX_AddAccessorieEasy( IMC_RIGHT_BOX* rbox, int accessorie_no, int x, int y, int pri );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	アクセサリの移動追加
 *
 *	@param	rbox		右ボックス用データ
 *	@param	acce_obj	アクセサリデータ
 *
 *	@retval	TRUE	成功
 *	@retval	FALSE	失敗	（登録最大数以上登録しようとした）
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL IMC_RBOX_AddAccessorieMoveEasy( IMC_RIGHT_BOX* rbox, IMC_OBJLIST* acce_obj );


//----------------------------------------------------------------------------
/**
 *	[細かい処理　イメージクリップ作成システムではこっちを呼ぶ]
 *	@brief	アクセサリの新規追加
 *
 *	@param	rbox				右ボックス用データ
 *	@param	accessorie_no		追加するアクセサリナンバー
 *	@param	x					X座標
 *	@param	y					Y座標
 *	@param	SWSP_UPchar			判定用キャラクタデータ
 *
 *	@retval	TRUE	成功
 *	@retval	FALSE	失敗	（登録最大数以上登録しようとした）
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL IMC_RBOX_AddAccessorie( IMC_RIGHT_BOX* rbox, int accessorie_no, int x, int y, NNSG2dCharacterData** SWSP_UPchar );

//----------------------------------------------------------------------------
/**
 *	[細かい処理　イメージクリップ作成システムではこっちを呼ぶ]
 *	@brief	アクセサリの移動追加
 *
 *	@param	rbox		右ボックス用データ
 *	@param	acce_obj	アクセサリデータ
 *	@param	SWSP_UPchar			判定用キャラクタデータ
 *
 *	@retval	TRUE	成功
 *	@retval	FALSE	失敗	（登録最大数以上登録しようとした）
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL IMC_RBOX_AddAccessorieMove( IMC_RIGHT_BOX* rbox, IMC_OBJLIST* acce_obj, NNSG2dCharacterData** SWSP_UPchar );


//----------------------------------------------------------------------------
/**
 *
 *	@brief	アクセサリオブジェ破棄
 *
 *	@param	rbox	右ボックス
 *	@param	acce_obj	破棄するアクセサリ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_RBOX_DeleteAccessorie( IMC_RIGHT_BOX* rbox, IMC_OBJLIST* acce_obj );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	移動させるためのリストからの削除
 *
 *	@param	rbox	右ボックス
 *	@param	acce_obj	移動させるためにリストから削除するアクセサリデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_RBOX_DeleteAccessorieMove( IMC_RIGHT_BOX* rbox, IMC_OBJLIST* acce_obj );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	登録されているアクセサリ全てをはき
 *
 *	@param	rbox	右ボックス
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_RBOX_DeleteAccessorieAll( IMC_RIGHT_BOX* rbox );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	右ボックス内のスプライトで表示されているオブジェクトを動かす
 *
 *	@param	rbox	右ボックス
 *	@param	x		足すｘ値
 *	@param	y		足すｙ値
 *	
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_RBOX_ListMove( IMC_RIGHT_BOX* rbox, int x, int y );

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンの上のアクセサリを動かす
 *
 *	@param	rbox	右ボックス
 *	@param	x		ｘ座標
 *	@param	y		ｙ座標
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_RBOX_PokeUpListMove( IMC_RIGHT_BOX* rbox, int x, int y );

//----------------------------------------------------------------------------
/**
 *	@brief	リストの中心座標を設定
 *
 *	@param	rbox		右ボックス
 *	@param	old_x		前は何処を基準にしていたのか
 *	@param	old_y
 *	@param	x			これからは何処を基準にするのか
 *	@param	y 
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_RBOX_ListMatSet( IMC_RIGHT_BOX* rbox, int old_x, int old_y, int x, int y );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	右ボックスのアクセサリ表示プライオリティを設定
 *
 *	@param	rbox		右ボックス 
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_RBOX_SetObjPriority( IMC_RIGHT_BOX* rbox );
GLOBAL void IMC_RBOX_SetObjPriorityMC( IMC_RIGHT_BOX* rbox, int priority );
GLOBAL void IMC_RBOX_AddObjPriorityMC( IMC_RIGHT_BOX* rbox, int priority );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	タッチパネルが右ボックスに当たってるかチェック
 *
 *	@param	rbox		右ボックスデータ
 *
 *	@retval	TRUE		ヒット
 *	@retval	FALSE		非ヒット
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL IMC_RBOX_TPHit( IMC_RIGHT_BOX* rbox );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	指定座標が右ボックスに当たってるかチェック
 *
 *	@param	rbox		右ボックスデータ
 *	@param	x			判定ｘ座標
 *	@param	y			判定ｙ座標
 *
 *	@retval	TRUE		ヒット
 *	@retval	FALSE		非ヒット
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL IMC_RBOX_TPHitSelf( IMC_RIGHT_BOX* rbox, int x, int y );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	アクセサリごとの当たり判定を行う
 *
 *	@param	rbox	右ボックス
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL IMC_OBJLIST* IMC_RBOX_TPHitObj( IMC_RIGHT_BOX* rbox );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	アクセサリごとの当たり判定を細かく行う
 *
 *	@param	rbox		右ボックス
 *	@param	offset_x	オフセットｘ座標
 *	@param	offset_y	オフセットｙ座標
 *	@param	SWSP_UPchar	判定キャラクタデータテーブル
 *
 *	@return	none
 *
 * キャラクタデータを参照して抜き色ではないかチェック
 *
 */
//-----------------------------------------------------------------------------
GLOBAL IMC_OBJLIST* IMC_RBOX_TPHitObjEx( IMC_RIGHT_BOX* rbox, int* offset_x, int* offset_y, NNSG2dCharacterData** SWSP_UPchar );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BGを表示
 *
 *	@param	rbox		右ボックス
 *	@param	bg_num		右ボックスBGナンバー
 *	@param	heap		使用するヒープ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_RBOX_BGSet( IMC_RIGHT_BOX* rbox, int bg_num, int heap );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BGをクリーンする
 *
 *	@param	rbox		右ボックス
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_RBOX_BGClean( IMC_RIGHT_BOX* rbox );

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモン座標を取得
 *
 *	@param	rbox	右ボックス
 *	@param	x		ｘ座標
 *	@param	y		ｙ座標
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_RBOX_GetPokeMatrix( IMC_RIGHT_BOX* rbox, int* x, int* y );

//----------------------------------------------------------------------------
/**
 *	@brief	保持しているアクセサリ数取得
 *
 *	@param	rbox	右ボックス
 *
 *	@return	アクセサリ数
 */
//-----------------------------------------------------------------------------
GLOBAL int IMC_RBOX_GetNowHaveAcceNum( IMC_RIGHT_BOX* rbox );

//----------------------------------------------------------------------------
/**
 *	@brief	ポケモンの上に乗っているアクセサリが食い込んでいるサイズを取得
 *
 *	@param	rbox		右ボックスワーク
 *	@param	enc_x		食い込んでるサイズｘ
 *	@param	enc_y		食い込んでるサイズｙ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_RBOX_GetPokeUpListEncSize( IMC_RIGHT_BOX* rbox, int* enc_x, int* enc_y );

//----------------------------------------------------------------------------
/**
 *	@brief	右ボックス　色設定
 *
 *	@param	rbox	右ボックス
 *	@param	color	色
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_RBOX_SetObjColor( IMC_RIGHT_BOX* rbox, GXRgb color );

#undef	GLOBAL
#endif		// __IMC_RIGHT_BOX_H__

