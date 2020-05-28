//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_accessorie.c
 *	@brief		アクセサリ管理システム
 *	@author		tomoya takahashi
 *	@data		2005.09.20
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include <string.h>
#include "system.h"
#include "assert.h"
#include "include/application/imageClip/imc_drawsys.h"

#include "include/application/imageClip/imc_drawdata_define.h"
#define	__IMC_ACCESSORIE_H_GLOBAL
#include "include/application/imageClip/imc_accessorie.h"

//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------
// 各グラフィックサイズの画面外にめり込んでよいサイズ
#define IMC_ACCE_HIT_16_SIZE_X	(0)
#define IMC_ACCE_HIT_16_SIZE_Y	(0)
#define IMC_ACCE_HIT_32_SIZE_X	(10)
#define IMC_ACCE_HIT_32_SIZE_Y	(10)
#define IMC_ACCE_HIT_64_SIZE_X	(20)
#define IMC_ACCE_HIT_64_SIZE_Y	(20)

#define IMC_ACCE_SIZE_16	(16)
#define IMC_ACCE_SIZE_32	(32)
#define IMC_ACCE_SIZE_64	(64)


// 当たり判定矩形の半サイズ
#define IMC_ACCE_HIT_AREA_HALF	(4)

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
static IMC_ACCESSORIE_OBJ* cleanObjDataGet( IMC_ACCESSORIE_OBJ_TBL* objTbl );
static SWSP_OBJ_PTR SWSP_add( IMC_ACCE_ADD* data );

static void setHitTbl( IMC_ACCESSORIE_OBJ* obj, TP_HIT_TBL* tp_hit );

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
IMC_ACCESSORIE_OBJ_TBL* IMC_ACCE_ObjTblInit( int obj_num, int heap )
{
	IMC_ACCESSORIE_OBJ_TBL* objTbl;
	
	// メモリ確保
	objTbl = sys_AllocMemory( heap, sizeof(IMC_ACCESSORIE_OBJ_TBL) );

	// アクセサリテーブル作成
	objTbl->obj_tbl = sys_AllocMemory( heap, sizeof(IMC_ACCESSORIE_OBJ)*obj_num );
	memset( objTbl->obj_tbl, 0, sizeof(IMC_ACCESSORIE_OBJ)*obj_num );
	objTbl->obj_num = obj_num;

	return objTbl;
}

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
void IMC_ACCE_ObjTblDelete( IMC_ACCESSORIE_OBJ_TBL* obj_tbl )
{
	sys_FreeMemoryEz( obj_tbl->obj_tbl );
	sys_FreeMemoryEz( obj_tbl );

	obj_tbl = NULL;
}

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
IMC_ACCESSORIE_OBJ* IMC_ACCE_ObjAdd( IMC_ACCE_ADD* data )
{
	IMC_ACCESSORIE_OBJ* obj_data;
	
	// 空いているテーブル取得
	obj_data = cleanObjDataGet( data->objTbl );
	GF_ASSERT( obj_data );
	
	// アクセサリデータ設定
	obj_data->accessorie_no = data->accessorie_no;
	
	// 描画データ作成
	obj_data->drawObj = SWSP_add( data );

	return obj_data;
}

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
void IMC_ACCE_ObjDelete( IMC_ACCESSORIE_OBJ* obj )
{
	// 描画データの破棄
	SWSP_Delete( obj->drawObj );

	// データclean
	memset( obj, 0, sizeof( IMC_ACCESSORIE_OBJ ) );
}

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
void IMC_ACCE_ObjDeleteAll( IMC_ACCESSORIE_OBJ_TBL* obj_tbl )
{
	int i;

	for(i=0; i<obj_tbl->obj_num; i++){
		if( obj_tbl->obj_tbl[ i ].drawObj != NULL ){
			IMC_ACCE_ObjDelete( obj_tbl->obj_tbl + i );
		}
	}
}

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
BOOL IMC_ACCE_ObjTpHit( IMC_ACCESSORIE_OBJ* obj )
{
	TP_HIT_TBL	tp_hit;
	
	// 当たり判定データ作成
	setHitTbl( obj, &tp_hit );	
	
	return GF_TP_SingleHitCont( &tp_hit );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	タッチパネルとの当たり判定を細かく行う
 *
 *	@param	obj			オブジェクトデータ
 *	@param	offs_x		左上からのオフセットｘ座標
 *	@param	offs_y		左上からのオフセットｙ座標
 *	@param	drawData	キャラクタデータ
 *
 *	@retval	TRUE	あたった
 *	@retval	FALSE	あたらなかった	（オフセット座標不定）
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL IMC_ACCE_ObjTpHitEx( IMC_ACCESSORIE_OBJ* obj, int* offs_x, int* offs_y, NNSG2dCharacterData* drawData )
{
	BOOL check;		// チェック用
	int x, y;		// 現在の左上座標
	int i, j;		// ループ用

	// まず当たり判定を普通に行う
	check = IMC_ACCE_ObjTpHit( obj );
	if( check == FALSE ){
		return FALSE;
	}

	// 座標取得
	IMC_ACCE_ObjGetMat( obj, &x, &y );

	// オフセット値を取得
	*offs_x = sys.tp_x - x;
	*offs_y = sys.tp_y - y;

	// その位置のキャラクタデータをチェック
	// 抜け色でないかをチェック
/*	// カラーナンバーが０出なければTRUEを返す
	check = IMC_DRAW_CharCheck( drawData, *offs_x, *offs_y, 0 );
	if(check == IMC_DRAW_CHAR_CHECK_FALSE){
		return TRUE;
	}
//*/
	for( i = (*offs_y - IMC_ACCE_HIT_AREA_HALF); i < (*offs_y + IMC_ACCE_HIT_AREA_HALF); i++ ){
	
		if( i >= 0 ){
			
			for( j = (*offs_x - IMC_ACCE_HIT_AREA_HALF); j < (*offs_x + IMC_ACCE_HIT_AREA_HALF); j++ ){
				
				if( j >= 0 ){
					// カラーナンバーが０出なければTRUEを返す
					check = IMC_DRAW_CharCheck( drawData, j, i, 0 );
					if(check == IMC_DRAW_CHAR_CHECK_FALSE){
						return TRUE;
					}
				}
			}
		}
	}

	return FALSE;
}

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
BOOL IMC_ACCE_ObjTpHitSelf( IMC_ACCESSORIE_OBJ* obj, int x, int y )
{
	TP_HIT_TBL	tp_hit;
	
	// 当たり判定データ作成
	setHitTbl( obj, &tp_hit );	

	return GF_TP_SingleHitSelf( &tp_hit, x, y );
}

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
void IMC_ACCE_ObjSetMat( IMC_ACCESSORIE_OBJ* obj, s16 x, s16 y )
{
	// スプライトに設定
	SWSP_SetSpritePos( obj->drawObj, x, y );
}

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
void IMC_ACCE_ObjGetMat( IMC_ACCESSORIE_OBJ* obj, int* x, int* y )
{
	NNSG2dSVec2 mat;
	mat = SWSP_GetSpritePos( obj->drawObj );
	*x = mat.x;	
	*y = mat.y;	
}

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
void IMC_ACCE_ObjGetSize( IMC_ACCESSORIE_OBJ* obj, int* x, int* y )
{
	NNSG2dSVec2 size;
	size = SWSP_GetSpriteSize( obj->drawObj );
	*x = size.x;	
	*y = size.y;	
}

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
void IMC_ACCE_ObjListDrawSet( IMC_ACCESSORIE_OBJ* obj, BOOL flag )
{
	SWSP_SetSpriteDraw( obj->drawObj, flag );
}

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
void IMC_ACCE_ObjDrawPrioritySet( IMC_ACCESSORIE_OBJ* obj, int priority )
{
	SWSP_SetSpritePriority( obj->drawObj, priority );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	アクセサリリストの表示優先順位を取得
 *
 *	@param	obj			アクセサリオブジェ
 *
 *	@return	priority
 *
 *
 */
//-----------------------------------------------------------------------------
int IMC_ACCE_ObjDrawPriorityGet( IMC_ACCESSORIE_OBJ* obj )
{
	return SWSP_GetSpritePriority( obj->drawObj );
}

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
void IMC_ACCE_ObjInSizeGet( IMC_ACCESSORIE_OBJ* obj, int* ins_x, int* ins_y )
{
	int size_x, size_y;		// サイズ取得用

	// アクセサリオブジェクトのとき
	IMC_ACCE_ObjGetSize( obj, &size_x, &size_y );
	
	// グラフィックサイズから取得
	switch(size_x){
	case IMC_ACCE_SIZE_16:
		*ins_x = IMC_ACCE_HIT_16_SIZE_X;
		break;
	case IMC_ACCE_SIZE_32:
		*ins_x = IMC_ACCE_HIT_32_SIZE_X;
		break;
	case IMC_ACCE_SIZE_64:
		*ins_x = IMC_ACCE_HIT_64_SIZE_X;
		break;
	}

	switch(size_y){
	case IMC_ACCE_SIZE_16:
		*ins_y = IMC_ACCE_HIT_16_SIZE_Y;
		break;
	case IMC_ACCE_SIZE_32:
		*ins_y = IMC_ACCE_HIT_32_SIZE_Y;
		break;
	case IMC_ACCE_SIZE_64:
		*ins_y = IMC_ACCE_HIT_64_SIZE_Y;
		break;
	}

}

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
void IMC_ACCE_ObjScaleSet( IMC_ACCESSORIE_OBJ* obj, int scale_x, int scale_y )
{
	GF_ASSERT( obj );
	
	SWSP_SetSpriteScale( obj->drawObj, scale_x, scale_y );
}


//-----------------------------------------------------------------------------
/**
*		プライベート関数郡
*/
//-----------------------------------------------------------------------------

//----------------------------------------------------------------------------
/**
 *
 *	@brief	空のテーブルを取得
 *
 *	@param	objTbl	オブジェクトテーブル
 *
 *	@return	IMC_ACCESSORIE_OBJ*	空のテーブル
 *
 *
 */
//-----------------------------------------------------------------------------
static IMC_ACCESSORIE_OBJ* cleanObjDataGet( IMC_ACCESSORIE_OBJ_TBL* objTbl )
{
	int i;		// ループ用

	for(i=0; i<objTbl->obj_num; i++){
		if( objTbl->obj_tbl[ i ].drawObj == NULL ){
			return objTbl->obj_tbl + i;
		}
	}

	return NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	ソフトウェアスプライトの登録
 *
 *	@param	data	登録データ	
 *
 *	@return	SWSP_OBJ_PTR	作成したスプライトデータ
 *
 *
 */
//-----------------------------------------------------------------------------
static SWSP_OBJ_PTR SWSP_add( IMC_ACCE_ADD* data )
{
	SWSP_ADDDATA add;


	add.s_sys = data->SWSPsys;
	add.p_char = data->SWSPchar;
	add.p_pltt = data->SWSPpltt;
	add.m_x		= data->m_x;
	add.m_y		= data->m_y;
	add.rota	= 0;
	add.alpha	= 31;
	add.pri		= 0;
	add.pltt_offs = data->pltt_offs;

	return SWSP_Add( &add );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	アクセサリオブジェの当たり判定データ作成
 *
 *	@param	obj		作るオブジェクト
 *	@param	tp_hit	タッチパネルあたり判定データ
 *
 *	@return
 *
 *	事前にスプライト作成を行っている必要があります。
 *
 */
//-----------------------------------------------------------------------------
static void setHitTbl( IMC_ACCESSORIE_OBJ* obj, TP_HIT_TBL* tp_hit )
{
	NNSG2dSVec2	pos	= SWSP_GetSpritePos( obj->drawObj );
	NNSG2dSVec2 size = SWSP_GetSpriteSize( obj->drawObj );
	
	// スプライトサイズから当たり判定エリア作成
	tp_hit->rect.top		= pos.y;
	tp_hit->rect.bottom		= pos.y + size.y;
	tp_hit->rect.left		= pos.x;
	tp_hit->rect.right		= pos.x + size.x;
}
