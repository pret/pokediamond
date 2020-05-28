//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_left_box.h
 *	@brief		左ボックスシステム
 *	@author		tomoya takahashi
 *	@data		2005.09.23
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __IMC_LEFT_BOX_H__
#define __IMC_LEFT_BOX_H__

#include <nnsys.h>

#include "include/application/imageClip/imc_accessorie.h"
#include "include/application/imageClip/imc_obj_list.h"
#include "include/application/imageClip/imc_bg.h"
#include "include/application/imageClip/imc_item_buff.h"
#include "touchpanel.h"


#undef GLOBAL
#ifdef	__IMC_LEFT_BOX_H_GLOBAL
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
//	左ボックスアクセサリ表示優先順位開始
//	
//=====================================
#define IMC_LBOX_ACCE_PRIORITY_START	(-1)



//-------------------------------------
//	
//	BG用
//	
//=====================================
#define	IMC_LBOX_BG_PLTT_NUM	(1)
#define IMC_LBOX_BG_PLTT_OFFS	(2)

//-------------------------------------
//	
//	今の動作状態
//	
//=====================================
enum{
	IMC_LBOX_STATE_NORM,	// 通常
	IMC_LBOX_STATE_FADE,	// パレットフェード中
};

//-------------------------------------
//	
//	フェード方向
//	
//=====================================
enum{
	IMC_LBOX_FADE_X = 1,
	IMC_LBOX_FADE_Y = 2
};

//-------------------------------------
//	
//	リスト足し算ﾓｰﾄﾞ
//	
//=====================================
enum{
	IMC_LBOX_ADD_ONE,		// +1
	IMC_LBOX_SUB_ONE,		// -1
};

//-------------------------------------
//
//	左パレットフェードアウト用
//	リストモード
//
//	フェードアウト用リストは
//	１個しかないです
//	
//	フェード時何もないリストを描画させるため
//=====================================
#define IMC_LBOX_FADELIST_MODE		(IMC_OBJLIST_ACCE_MAX)
#define IMC_LBOX_FADELIST_LISTNUM	(1)
#define IMC_LBOX_LIST_NUM			(IMC_LBOX_FADELIST_MODE + 1)


//-----------------------------------------------------------------------------
/**
 *					構造体宣言
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	左パレットリスト
//	
//=====================================
typedef struct {
	IMC_OBJLIST*			dummyTbl;		// リストダミーテーブル
	int						dummyNum;		// ダミーテーブル数
	int						dummyCurrent;	// 今のカレントダミーテーブル
} IMC_LEFT_LIST_DATA;

//-------------------------------------
//	
//	左ボックス構造体	
//	描画部
//	
//=====================================
typedef struct {
	// 描画システムデータ
	SWSP_SYS_PTR	SWSP_drawSys;		// スプライト描画システム
	SWSP_CHAR_PTR*	SWSP_charData;		// キャラクタデータ配列
	SWSP_PLTT_PTR*	SWSP_plttData;		// パレットデータ配列
	u8* accePlttOfsTbl;						// アクセサリパレットオフセット
	
	// BGデータ
	GF_BGL_INI*		BG_Ini;
	
	// アクセサリデータ
	IMC_ACCESSORIE_OBJ_TBL*	acce;
	
	// 背景データリスト
	IMC_BG	bg;
	IMC_ACCESSORIE_OBJ_TBL*	bg_acce;	// BGサムネイル
	
	// 音声データリスト
	
} IMC_LEFT_BOXDRAW;

//-------------------------------------
//	
//	左ボックス構造体データ部
//	
//=====================================
typedef struct {

	// 今の編集モード
	// アクセサリ	BG	サウンド
	int		mode;

	// BGサムネイル表示順データ
	IMC_ITEM_BUFF* p_item_buff;

	// オブジェクトリスト
	IMC_OBJLIST_TBL* objListTbl;
	
	// アクセサリモード分のリストデータ
	// 先頭ダミーデータ
	// 先頭ダミーデータ数
	// 今のカレントダミーデータ
	//
	IMC_LEFT_LIST_DATA	acce_list[ IMC_LBOX_LIST_NUM ];

	int	state;		// 今の動作状態 
	int back_no;	// 今の背景ナンバー
} IMC_LEFT_BOXDATA;


//-------------------------------------
//	
//	左ボックスデータ
//	
//=====================================
typedef struct {

	IMC_LEFT_BOXDATA	boxData;
	IMC_LEFT_BOXDRAW	boxDraw;
} IMC_LEFT_BOX;



//-------------------------------------
//	
//	左ボックス初期化構造体	
//	
//=====================================
typedef struct {
	SWSP_SYS_PTR	SWSP_drawSys;		// スプライト描画システム
	SWSP_CHAR_PTR*	SWSP_charData;		// キャラクタデータ配列
	SWSP_PLTT_PTR*	SWSP_plttData;		// パレットデータ配列
	u8* accePlttOfsTbl;						// アクセサリパレットオフセット
	
	// BGデータ
	GF_BGL_INI*		BG_Ini;

	IMC_ACCESSORIE_OBJ_TBL* acce;			// アクセサリリストデータ
	IMC_OBJLIST_TBL*		objListTbl;		// オブジェクトリストテーブル
	int						accelist_num;	// 作成するアクセサリリスト数
	int						bglist_num;		// 作成するBGサムネイルリスト数
	int						sndlist_num;	// 作成するサウンドサムネイルリスト数

	IMC_ITEM_BUFF* p_item_buff;		// BGの表示順データ
} IMC_LEFT_BOX_INIT;

//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	左ボックス用領域作成
 *
 *	@param	lbox		左ボックス用データ
 *	@param	init		左ボックス初期化データ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_LBOX_InitSys( IMC_LEFT_BOX* lbox, IMC_LEFT_BOX_INIT* init );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	左ボック用領域破棄
 *
 *	@param	lbox		破棄する左ボックスデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_LBOX_DeleteSys( IMC_LEFT_BOX* lbox );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	アクセサリーナンバーからリストナンバーを取得
 *
 *	@param	mode			モード
 *	@param	accessorie_no	アクセサリナンバー
 *
 *	@return	int		アクセサリーリストナンバー
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL int IMC_LBOX_GetListNo( int mode, int accessorie_no, IMC_ITEM_BUFF* p_item_buff );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	モードとアクセサリナンバーから登録されておくべき座標を取得
 *
 *	@param	mode			モード
 *	@param	accessorie_no	アクセサリナンバー
 *	@param	x				ｘ座標格納先
 *	@param	y				ｙ座標格納先
 *
 *	@return	none
 *	
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_LBOX_GetMat( int mode, int accessorie_no, int* x, int* y, int size_x, int size_y, IMC_ITEM_BUFF* p_item_buff );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	アクセサリの新規追加
 *
 *	@param	lbox				左ボックス用データ
 *	@param	mode				アクセサリモード
 *	@param	accessorie_no		追加するアクセサリナンバー
 *
 *	@return	none
 *
 * mode
	IMC_OBJLIST_ACCE,		// アクセサリタイプ
	IMC_OBJLIST_BG,		// BGサムネイルタイプ
	IMC_OBJLIST_SND,		// サウンドサムネイルタイプ
	IMC_OBJLIST_ACCE_MAX		// モード最大数
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_LBOX_AddAccessorie( IMC_LEFT_BOX* lbox, int mode, int accessorie_no );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	アクセサリの移動追加
 *
 *	@param	lbox		左ボックス用データ
 *	@param	acce_obj	アクセサリデータ
 *	@param	mode		アクセサリモード
 *	@param	list_num	登録するリスト
 *
 *	@return	none
 * 
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_LBOX_AddAccessorieMove( IMC_LEFT_BOX* lbox, int mode, int list_num, IMC_OBJLIST* acce_obj );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	アクセサリオブジェ破棄
 *
 *	@param	acce_obj	破棄するアクセサリ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_LBOX_DeleteAccessorie( IMC_OBJLIST* acce_obj );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	移動させるためのリストからの削除
 *
 *	@param	acce_obj	移動させるためにリストから削除するアクセサリデータ
 *
 *	@return	none
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_LBOX_DeleteAccessorieMove( IMC_OBJLIST* acce_obj );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	登録されているアクセサリ全てをはき
 *
 *	@param	lbox	左ボックス
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_LBOX_DeleteAccessorieAll( IMC_LEFT_BOX* lbox );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	アクセサリリスト全ての座標を動かす
 *
 *	@param	lbox		左ボックス
 *	@param	mode		モード
 *	@param	list_no		リストナンバー
 *	@param	x			動かすｘ座標
 *	@param	y			動かすｙ座標
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_LBOX_AccessorieListMove( IMC_LEFT_BOX* lbox, int mode, int list_no, int x, int y );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	左ボックスアクセサリの表示優先順を設定
 *
 *	@param	lbox	左ブロック
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_LBOX_SetAccessoriePriority( IMC_LEFT_BOX* lbox );

//----------------------------------------------------------------------------
/**
 *
 * ●自動でエフェクトを行います。
 *
 *	@brief	カレントアクセサリリストを変更
 *
 *	@param	lbox			左ボックスデータ
 *	@param	mode			アクセサリモード
 *	@param	list_num		設定するカレントアクセサリリスト
 *
 *	@retval	TRUE			成功
 *	@retval	FALSE			失敗
 *
 * mode
	IMC_OBJLIST_ACCE,		// アクセサリタイプ
	IMC_OBJLIST_BG,			// BGサムネイルタイプ
	IMC_OBJLIST_SND,		// サウンドサムネイルタイプ
	IMC_LBOX_FADELIST_MODE	// フェード時用リスト	list_numは０固定
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL IMC_LBOX_ChangeCurrentAccessorie( IMC_LEFT_BOX* lbox, int mode, int list_num );

//----------------------------------------------------------------------------
/**
 * ●自動でエフェクトを行います。
 *
 *	@brief	カレントアクセサリリストの足し算
 *
 *	@param	lbox			左ボックスデータ
 *	@param	mode			アクセサリモード
 *	@param	add_mode		足すモード
 *
 *	@retval	TRUE			成功
 *	@retval	FALSE			失敗
 *
 * mode
	IMC_OBJLIST_ACCE,		// アクセサリタイプ
	IMC_OBJLIST_BG,			// BGサムネイルタイプ
	IMC_OBJLIST_SND,		// サウンドサムネイルタイプ
	IMC_LBOX_FADELIST_MODE	// フェード時用リスト	list_numは０固定

	add_mode
		IMC_LBOX_ADD_ONE,		// +1
		IMC_LBOX_SUB_ONE,		// -1
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL IMC_LBOX_AddCurrentAccessorie( IMC_LEFT_BOX* lbox, int mode, int add_mode );

//----------------------------------------------------------------------------
/**
 *
 * ●エフェクトなし
 *
 *	@brief	カレントアクセサリリストを設定
 *
 *	@param	lbox			左ボックスデータ
 *	@param	mode			アクセサリモード
 *	@param	list_num		設定するカレントアクセサリリスト
 *
 *	@return	none
 *
 * mode
	IMC_OBJLIST_ACCE,		// アクセサリタイプ
	IMC_OBJLIST_BG,			// BGサムネイルタイプ
	IMC_OBJLIST_SND,		// サウンドサムネイルタイプ
	IMC_LBOX_FADELIST_MODE	// フェード時用リスト	list_numは０固定
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_LBOX_SetCurrentAccessorie( IMC_LEFT_BOX* lbox, int mode, int list_num );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	タッチパネルが左ボックスに当たってるかチェック
 *
 *	@param	lbox		左ボックスデータ
 *
 *	@retval	TRUE		ヒット
 *	@retval	FALSE		非ヒット
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL IMC_LBOX_TPHit( IMC_LEFT_BOX* lbox );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	指定座標が左ボックスに当たってるかチェック
 *
 *	@param	lbox		左ボックスデータ
 *	@param	x			判定ｘ座標
 *	@param	y			判定ｙ座標
 *
 *	@retval	TRUE		ヒット
 *	@retval	FALSE		非ヒット
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL IMC_LBOX_TPHitSelf( IMC_LEFT_BOX* lbox, int x, int y );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	アクセサリごとの当たり判定を行う
 *
 *	@param	lbox	左ボックス
 *
 *	@return	none
 *
 *	カレントアクセサリリストをチェックします。
 *
 */
//-----------------------------------------------------------------------------
GLOBAL IMC_OBJLIST* IMC_LBOX_TPHitAccessorie( IMC_LEFT_BOX* lbox );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	アクセサリごとの当たり判定を細かく行う
 *
 *	@param	lbox	左ボックス
 *	@param	offset_x	オフセットｘ座標
 *	@param	offset_y	オフセットｙ座標
 *	@param	SWSP_UPchar	キャラクタリソーステーブル
 *
 *	@return	none
 *
 *	カレントアクセサリリストをチェックします。
 *
 */
//-----------------------------------------------------------------------------
GLOBAL IMC_OBJLIST* IMC_LBOX_TPHitAccessorieEx( IMC_LEFT_BOX* lbox, int* offset_x, int* offset_y, NNSG2dCharacterData** SWSP_UPchar );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BGを表示
 *
 *	@param	rbox		左ボックス
 *	@param	bg_num		左ボックスBGナンバー
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_LBOX_BGSet( IMC_LEFT_BOX* lbox, int bg_num );

//----------------------------------------------------------------------------
/**
 * ●エフェクト付き
 *
 *	@brief	左ボックス背景を変更
 *
 *	@param	lbox		左ボックデータ
 *	@param	bg_num		変更後のBGナンバー
 *	@param	fade_way	フェード方向
 *	@param	sync		何シンクで行うか
 *	@param	end_flg		終了検知フラグ
 *
 *	@return	none
 *
 * fade_way
	IMC_LBOX_FADE_X = 1,
	IMC_LBOX_FADE_Y = 2
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_LBOX_BGChange( IMC_LEFT_BOX* lbox, int bg_num, int fade_way, int sync, BOOL* end_flg );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BGをクリーンする
 *
 *	@param	lbox		左ボックス
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL void IMC_LBOX_BGClean( IMC_LEFT_BOX* lbox );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	現在のモード
 *
 *	@param	lbox	左ボックス
 *
 *	@return	アクセサリモード
 *
 * mode
	IMC_OBJLIST_ACCE,		// アクセサリタイプ
	IMC_OBJLIST_BG,			// BGサムネイルタイプ
	IMC_OBJLIST_SND,		// サウンドサムネイルタイプ
	IMC_LBOX_FADELIST_MODE	// フェード時用リスト	list_numは０固定
 *
 */
//-----------------------------------------------------------------------------
GLOBAL int IMC_LBOX_GetMode( IMC_LEFT_BOX* lbox );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	モードごとのカレントダミーテーブルナンバーを取得
 *
 *	@param	lbox	左ボックスデータ
 *	@param	mode	調べたいモード
 *	
 *	@return	カレントダミーテーブルナンバー
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL int IMC_LBOX_GetCurrentNo( IMC_LEFT_BOX* lbox, int mode  );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ダミーテーブル数を取得
 *
 *	@param	lbox		左ボックスオブジェ
 *	@param	mode		アクセサリモード
 *
 *	@return	ダミーテーブル数
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL int IMC_LBOX_GetDummyTblNum( IMC_LEFT_BOX* lbox, int mode );

//----------------------------------------------------------------------------
/**
 *
 *	@brief	今左ボックを壊してよい状態なのかをチェック
 *
 *	@param	lbox	左ボックスデータ
 *
 *	@retval	TRUE	OK
 *	@retval FALSE	NG		フェード中です
 *
 *
 */
//-----------------------------------------------------------------------------
GLOBAL BOOL IMC_LBOX_ENDCheck( IMC_LEFT_BOX* lbox );
	
#undef	GLOBAL
#endif		// __IMC_LEFT_BOX_H__
