//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_accessorie.h
 *	@brief		アクセサリー管理システム
 *	@author		tomoya takahashi
 *	@data		2005.09.20
 *
 * アクセサリをリストで管理するシステム
 * 
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __IMC_ACCESSORIE_H__
#define __IMC_ACCESSORIE_H__

#include <nnsys.h>
#include "include/system/swsprite.h"
#include "touchpanel.h"

#undef GLOBAL
#ifdef	__IMC_ACCESSORIE_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	アクセサリ管理データ
//	
//=====================================
typedef struct IMC_ACCESSORIE_OBJ_tag{
	int accessorie_no;			// アクセサリナンバー
	
	
	SWSP_OBJ_PTR drawObj;	// 表示データ

} IMC_ACCESSORIE_OBJ;

//-------------------------------------
//	
//	アクセサリ管理構造体
//	
//=====================================
typedef struct IMC_ACCESSORIE_OBJ_TBL_tag{

	IMC_ACCESSORIE_OBJ* obj_tbl;
	int					obj_num;

} IMC_ACCESSORIE_OBJ_TBL;

//-------------------------------------
//	
//	アクセサリデータ登録関数
//	
//=====================================
typedef struct {
	IMC_ACCESSORIE_OBJ_TBL* objTbl;	// オブジェクトテーブル
	SWSP_SYS_PTR	SWSPsys;	// スプライトシステムデータ
	SWSP_CHAR_PTR	SWSPchar;	// キャラクタデータ
	SWSP_PLTT_PTR	SWSPpltt;	// パレットデータ
	int					m_x;	// 座標ｘ
	int					m_y;	// 座標ｙ
	u32					accessorie_no;	// アクセサリナンバー
	u32					pltt_offs;	// パレットオフセット
} IMC_ACCE_ADD;

//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	アクセサリオブジェクトテーブルを作成
 *
 *	@param	obj_num		アクセサリ数
 *	@param	heap		ヒープ数
 *
 *	@return	IMC_ACCESSORIE_OBJ_TBL*	オブジェクトテーブル
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL IMC_ACCESSORIE_OBJ_TBL* IMC_ACCE_ObjTblInit( int obj_num, int heap );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	アクセサリオブジェクトテーブルを作成
 *
 *	@param	obj_num		アクセサリ数
 *	@param	heap		ヒープ数
 *
 *	@return	IMC_ACCESSORIE_OBJ_TBL*	オブジェクトテーブル
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_ACCE_ObjTblDelete( IMC_ACCESSORIE_OBJ_TBL* obj_tbl );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	アクセサリ作成
 *
 *	@param	data	オブジェクト登録データ
 *
 *	@return	IMC_ACCESSORIE_OBJ*	アクセサリオブジェ
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL IMC_ACCESSORIE_OBJ* IMC_ACCE_ObjAdd( IMC_ACCE_ADD* data );

//----------------------------------------------------------------------------
/**
 * ●BGサムネイル登録用
 *
 *	@brief	アクセサリ作成		アクセサリ以外のスプライトオブジェ用
 *
 *	@param	data	オブジェクト登録データ
 *
 *	@return	IMC_ACCESSORIE_OBJ*	アクセサリオブジェ
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL IMC_ACCESSORIE_OBJ* IMC_ACCE_ObjAddBGThum( IMC_ACCE_ADD* data );

//----------------------------------------------------------------------------
/**
 * ●SNDサムネイル登録用
 *
 *	@brief	アクセサリ作成		アクセサリ以外のスプライトオブジェ用
 *
 *	@param	data	オブジェクト登録データ
 *
 *	@return	IMC_ACCESSORIE_OBJ*	アクセサリオブジェ
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL IMC_ACCESSORIE_OBJ* IMC_ACCE_ObjAddSNDThum( IMC_ACCE_ADD* data );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	オブジェクトデータ破棄
 *
 *	@param	obj		破棄するオブジェクト
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_ACCE_ObjDelete( IMC_ACCESSORIE_OBJ* obj );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	アクセサリオブジェクトテーブル内のアクセサリ破棄
 *
 *	@param	obj_tbl		オブジェクトテーブル
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_ACCE_ObjDeleteAll( IMC_ACCESSORIE_OBJ_TBL* obj_tbl );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	座標を設定	（同時にスプライトも移動）
 *
 *	@param	obj	アクセサリオブジェ
 *	@param	x	x座標
 *	@param	y	y座標
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_ACCE_ObjSetMat( IMC_ACCESSORIE_OBJ* obj, s16 x, s16 y );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	座標を取得
 *
 *	@param	obj		アクセサリオブジェクト
 *	@param	x		ｘ座標取得先
 *	@param	y		ｙ座標取得先
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_ACCE_ObjGetMat( IMC_ACCESSORIE_OBJ* obj, int* x, int* y );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	スプライトサイズを取得
 *
 *	@param	obj		アクセサリオブジェクト
 *	@param	x		ｘサイズ取得先
 *	@param	y		ｙサイズ取得先
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_ACCE_ObjGetSize( IMC_ACCESSORIE_OBJ* obj, int* x, int* y );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	タッチパネルとの当たり判定を行う
 *
 *	@param	obj		オブジェクトデータ
 *
 *	@retval	TRUE	あたった
 *	@retval	FALSE	あたらなかった
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL IMC_ACCE_ObjTpHit( IMC_ACCESSORIE_OBJ* obj );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	タッチパネルとの当たり判定を細かく行う
 *
 *	@param	obj			オブジェクトデータ
 *	@param	offs_x		左上からのオフセットｘ座標
 *	@param	offs_y		左上からのオフセットｙ座標
 *	@param	drawData	チェックするキャラクタデータ
 *
 *	@retval	TRUE	あたった
 *	@retval	FALSE	あたらなかった	（オフセット座標不定）
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL IMC_ACCE_ObjTpHitEx( IMC_ACCESSORIE_OBJ* obj, int* offs_x, int* offs_y, NNSG2dCharacterData* drawData );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	タッチパネルとの当たり判定を行う
 *
 *	@param	obj		オブジェクトデータ
 *	@param	x		判定ｘ座標
 *	@param	y		判定ｙ座標
 *
 *	@retval	TRUE	あたった
 *	@retval	FALSE	あたらなかった
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL IMC_ACCE_ObjTpHitSelf( IMC_ACCESSORIE_OBJ* obj, int x, int y );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	アクセサリリストのアクセサリの描画ON　OFF　設定
 *
 *	@param	obj		アクセサリオブジェクトデータ
 *	@param	flag	ON　OFF　フラグ
 *			
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_ACCE_ObjListDrawSet( IMC_ACCESSORIE_OBJ* obj, BOOL flag );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	アクセサリリストの表示優先順位を設定
 *
 *	@param	obj			アクセサリオブジェ
 *	@param	priority	表示優先順位
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_ACCE_ObjDrawPrioritySet( IMC_ACCESSORIE_OBJ* obj, int priority );
GLOBAL int IMC_ACCE_ObjDrawPriorityGet( IMC_ACCESSORIE_OBJ* obj );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	食い込んで良いサイズを取得
 *
 *	@param	obj		オブジェクトデータ
 *	@param	ins_x	食い込んで良いサイズX
 *	@param	ins_y	食い込んで良いサイズY
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_ACCE_ObjInSizeGet( IMC_ACCESSORIE_OBJ* obj, int* ins_x, int* ins_y );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	拡縮値を設定する
 *
 *	@param	obj			アクセサリオブジェ
 *	@param	scale_x		ｘ拡縮値
 *	@param	scale_y		ｙ拡縮値
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_ACCE_ObjScaleSet( IMC_ACCESSORIE_OBJ* obj, int scale_x, int scale_y );

#undef	GLOBAL
#endif		// __IMC_ACCESSORIE_H__

