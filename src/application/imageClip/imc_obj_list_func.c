//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_obj_list_func.c
 *	@brief		沢山のシステムが使用するオブジェリスト用関数を宣言
 *	@author		tomoya takahashi 
 *	@data		2005.09.30
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]


#include "system.h"
#include "include/application/imageClip/imc_drawdata_define.h"
#include "include/application/imageClip/imc_accessorie.h"
#include "include/application/imageClip/imc_poke_obj.h"

#define __IMC_OBJ_LIST_FUNC_H_GLOBAL
#include "include/application/imageClip/imc_obj_list_func.h"

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

//-----------------------------------------------------------------------------
/**
 *					プロトタイプ宣言
*/
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
/**
*	アクセサリとポケモンオブジェの表示優先順位、当たり判定、座標変更
*	を行う関数
*/
//-----------------------------------------------------------------------------
//----------------------------------------------------------------------------
/**
 *
 *	@brief	表示優先順位設定
 *
 *	@param	work	オブジェリストワーク
 *	@param	pri		表示優先順位
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_OBJLIST_ACCEPOKE_Pri( IMC_OBJLIST* work, int pri )
{
	if( work->flag < IMC_OBJLIST_POKE ){
		// アクセサリ
		IMC_ACCESSORIE_OBJ* acce = work->obj_data;
		IMC_ACCE_ObjDrawPrioritySet( acce, pri );
	}else{
		// ポケモン
		IMC_POKE* poke = work->obj_data;
		IMC_POKE_DrawPrioritySet( poke, pri );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	タッチパネル当たり判定
 *
 *	@param	work	オブジェリストワーク
 *	@param	x		判定X
 *	@param	y		判定Y
 *
 *	@retval	TRUE	あたった
 *	@retval	FALSE	あたらなかった
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL IMC_OBJLIST_ACCEPOKE_Hit( IMC_OBJLIST* work, int x, int y )
{
	if( work->flag < IMC_OBJLIST_POKE ){
		// アクセサリ
		IMC_ACCESSORIE_OBJ* acce = work->obj_data;
		
		if(x == IMC_OBJ_LIST_FUNC_TP_NOW){
			return IMC_ACCE_ObjTpHit( acce );
		}else{
			return IMC_ACCE_ObjTpHitSelf( acce, x, y );
		}
	}	
	
	// ポケモン
	{
		IMC_POKE* poke = work->obj_data;

		if(x == IMC_OBJ_LIST_FUNC_TP_NOW){
			return IMC_POKE_TPHit( poke );
		}else{
			return IMC_POKE_TPHitSelf( poke, x, y );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	細かいタッチパネル当たり判定
 *
 *	@param	work		オブジェリストワーク
 *	@param	offs_x		左上からのオフセットｘ座標
 *	@param	offs_y		左上からのオフセットｙ座標 
 *	@param	drawData	キャラクタデータ
 *
 *	@retval	TRUE	あたった
 *	@retval	FALSE	あたらなかった
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL IMC_OBJLIST_ACCEPOKE_HitEx( IMC_OBJLIST* work, int* offs_x, int* offs_y, NNSG2dCharacterData** drawData )
{
	NNSG2dCharacterData* char_data;

	if( work->flag == IMC_OBJLIST_ACCE ){
		// アクセサリ
		IMC_ACCESSORIE_OBJ* acce = work->obj_data;
	
		// キャラクタデータ取得
		char_data = drawData[ acce->accessorie_no ];

		return IMC_ACCE_ObjTpHitEx( acce, offs_x, offs_y, char_data );
	}	
	
	if( work->flag == IMC_OBJLIST_BG ){
		// BGサムネイル
		IMC_ACCESSORIE_OBJ* acce = work->obj_data;
		int char_no = IMC_BG_THUMB_CHAR_CONT_ID( acce->accessorie_no );
	
		// キャラクタデータ取得
		char_data = drawData[ char_no ];

		return IMC_ACCE_ObjTpHitEx( acce, offs_x, offs_y, char_data );
	}	
	
	if( work->flag == IMC_OBJLIST_SND ){
		// 音サムネイル
		IMC_ACCESSORIE_OBJ* acce = work->obj_data;
		int char_no = IMC_SND_THUMB_CHAR_CONT_ID( acce->accessorie_no );
	
		// キャラクタデータ取得
		char_data = drawData[ char_no ];
	
		return IMC_ACCE_ObjTpHitEx( acce, offs_x, offs_y, char_data );
	}	
	
	// ポケモン
	{
		IMC_POKE* poke = work->obj_data;

		// キャラクタデータ取得
		char_data = drawData[ IMC_DRAW_POKE_CHAR_ID ];

		return IMC_POKE_TPHitEx( poke, offs_x, offs_y, char_data );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	座標設定
 *
 *	@param	work	オブジェクトリストワーク
 *	@param	x		ｘ座標
 *	@param	y		ｙ座標
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_OBJLIST_ACCEPOKE_Mat( IMC_OBJLIST* work, int x, int y )
{
	if( work->flag < IMC_OBJLIST_POKE ){
		// アクセサリ
		IMC_ACCESSORIE_OBJ* acce = work->obj_data;
		IMC_ACCE_ObjSetMat( acce, x, y );
	}else{
		// ポケモン
		IMC_POKE* poke = work->obj_data;
		int size_x, size_y;		// サイズ
		// 左上座標にする
		IMC_POKE_SizeGet( poke, &size_x, &size_y );
		size_x /= 2;
		size_y /= 2;
		x += size_x;
		y += size_y;

		IMC_POKE_MatrixSet( poke, x, y );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	座標を取得
 *
 *	@param	obj		オブジェワーク
 *	@param	x		ｘ座標格納先
 *	@param	y		ｙ座標格納先
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_OBJLIST_ACCEPOKE_MatGet( IMC_OBJLIST* obj, int* x, int* y )
{
	if( obj->flag < IMC_OBJLIST_POKE ){
		// アクセサリ
		IMC_ACCESSORIE_OBJ* acce = obj->obj_data;
		IMC_ACCE_ObjGetMat( acce, x, y );
	}else{
		// ポケモン
		IMC_POKE* poke = obj->obj_data;
		int size_x, size_y;		// サイズ
		
		IMC_POKE_MatrixGet( poke, x, y );

		// 左上座標にする
		IMC_POKE_SizeGet( poke, &size_x, &size_y );
		size_x /= 2;
		size_y /= 2;
		*x -= size_x;
		*y -= size_y;
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	サイズを取得
 *
 *	@param	obj		オブジェワーク
 *	@param	x		ｘサイズ格納先
 *	@param	y		ｙサイズ格納先
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_OBJLIST_ACCEPOKE_SizeGet( IMC_OBJLIST* obj, int* x, int* y )
{
	if( obj->flag < IMC_OBJLIST_POKE ){
		// アクセサリ
		IMC_ACCESSORIE_OBJ* acce = obj->obj_data;
		IMC_ACCE_ObjGetSize( acce, x, y );
	}else{
		// ポケモン
		IMC_POKE* poke = obj->obj_data;
		IMC_POKE_SizeGet( poke, x, y );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	食い込んでよいサイズを取得
 *
 *	@param	obj		オブジェワーク
 *	@param	x		ｘサイズ格納先
 *	@param	y		ｙサイズ格納先
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_OBJLIST_ACCEPOKE_InSizeGet( IMC_OBJLIST* obj, int* x, int* y )
{
	if( obj->flag < IMC_OBJLIST_POKE ){
		// アクセサリ
		IMC_ACCESSORIE_OBJ* acce = obj->obj_data;
		IMC_ACCE_ObjInSizeGet( acce, x, y );
	}else{
		// ポケモン
		IMC_POKE* poke = obj->obj_data;
		IMC_POKE_InSizeGet( poke, x, y );
	}
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	リストごと足し算移動させる
 *	
 *	@param	top		リスト先頭ポインタ
 *	@param	x		足すX座標
 *	@param	y		足すY座標
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_OBJLIST_ACCEPOKE_ListMove( IMC_OBJLIST* top, int x, int y )
{
	IMC_OBJLIST* work;
	int mat_x, mat_y;

	
	work = top->next;
	while( work != top ){

		IMC_OBJLIST_ACCEPOKE_MatGet( work, &mat_x, &mat_y );

		mat_x += x;
		mat_y += y;
		
		IMC_OBJLIST_ACCEPOKE_Mat( work, mat_x, mat_y );
		
		work = work->next;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	オブジェクト矩形取得　食い込んでよいサイズ分減らし済み
 *	
 *	@param	p_obj	ワーク
 *	@param	top		上
 *	@param	bottom	下
 *	@param	left	左
 *	@param	right	右
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void IMC_OBJLIST_GetObjRectSubInSize( IMC_OBJLIST* p_obj, int* top, int* bottom, int* left, int* right )
{
	int size_x,size_y;			// オブジェクトサイズXY
	int mat_x, mat_y;			// オブジェクト座標
	int in_size_x, in_size_y;	// 食い込んでよいサイズXY


	IMC_OBJLIST_ACCEPOKE_SizeGet( p_obj, &size_x, &size_y );
	IMC_OBJLIST_ACCEPOKE_MatGet( p_obj, &mat_x, &mat_y );
	IMC_OBJLIST_ACCEPOKE_InSizeGet( p_obj, &in_size_x, &in_size_y );
	
	*top	= mat_y + in_size_y;
	*bottom	= mat_y + size_y - in_size_y;
	*left	= mat_x + in_size_x;
	*right	= mat_x + size_x - in_size_x;
}

//----------------------------------------------------------------------------
/**
 *	@brief	中心座標を取得する
 *
 *	@param	p_obj	オブジェクト
 *	@param	x		ｘ座標格納先
 *	@param	y		ｙ座標格納先
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
void IMC_OBJLIST_GetObjCenterMat( IMC_OBJLIST* p_obj, int* x, int* y )
{
	int size_x,size_y;			// オブジェクトサイズXY
	int mat_x, mat_y;			// オブジェクト座標

	IMC_OBJLIST_ACCEPOKE_SizeGet( p_obj, &size_x, &size_y );
	IMC_OBJLIST_ACCEPOKE_MatGet( p_obj, &mat_x, &mat_y );

	*x = mat_x + (size_x/2);
	*y = mat_y + (size_y/2);
}

