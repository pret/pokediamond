//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_right_box.c
 *	@brief		右の箱
 *	@author		tomoya takahashi
 *	@data		2005.09.22
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]


#include "system.h"
#include "assert.h"
#include <string.h>
#include "include/application/imageClip/imc_drawdata_define.h"
#include "include/application/imageClip/imc_obj_list_func.h"

#include "imc_calc.h"

#define	__IMC_RIGHT_BOX_H_GLOBAL
#include "include/application/imageClip/imc_right_box.h"

//-----------------------------------------------------------------------------
/**
 *					定数宣言
*/
//-----------------------------------------------------------------------------
#define IMC_RIGHT_BOX_ACCE_MAX	(10)

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
static void ImcRightSetAcceList( IMC_RIGHT_BOX* p_data, IMC_OBJLIST* objList, BOOL top_bottom, NNSG2dCharacterData** SWSP_UPchar );
static void imcRbox_GetAcceEncSize( IMC_OBJLIST* objlist, int* enc_x, int* enc_y );

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
void IMC_RBOX_InitSys( IMC_RIGHT_BOX* rbox, IMC_RIGHT_BOX_INIT* init )
{
	// 描画データ作成
	rbox->boxDraw.SWSP_drawSys	= init->SWSP_drawSys;
	rbox->boxDraw.SWSP_charData	= init->SWSP_charData;
	rbox->boxDraw.SWSP_plttData	= init->SWSP_plttData;
	rbox->boxDraw.accePlttOfsTbl= init->accePlttOfsTbl;
	rbox->boxDraw.SSM_drawSys	= init->SSM_drawSys;
	rbox->boxDraw.BG_Ini		= init->BG_Ini;
	rbox->boxDraw.acce			= init->acce;
	rbox->boxDraw.bg_no			= 0;

	// システムデータ
	rbox->boxData.objListTbl = init->objListTbl;

	rbox->boxData.dummy.next = &rbox->boxData.dummy;
	rbox->boxData.dummy.prev = &rbox->boxData.dummy;
	rbox->boxData.dummy_poke.next = &rbox->boxData.dummy_poke;
	rbox->boxData.dummy_poke.prev = &rbox->boxData.dummy_poke;
	rbox->boxData.obj_count = 0;
	rbox->boxData.obj_count_max = init->acce_count_max;


	// ポケモンオブジェ作成
	{
		IMC_OBJLIST* objList;
		objList = IMC_OBJLIST_MakeObjList( rbox->boxData.objListTbl, &rbox->boxDraw.poke, IMC_OBJLIST_POKE );

		// 先頭にリスト登録
		IMC_OBJLIST_Set( objList, &rbox->boxData.dummy_poke );
	}
}

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
void IMC_RBOX_DeleteSys( IMC_RIGHT_BOX* rbox )
{
	// ポケモン破棄
	IMC_RBOX_DeletePoke( rbox );

	// リスト破棄
	IMC_RBOX_DeleteAccessorieAll( rbox );
	
	memset( rbox, 0, sizeof(IMC_RIGHT_BOX) );
}


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
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_RBOX_AddPokePlayer( IMC_RIGHT_BOX* rbox, POKEMON_PARAM* poke_para, SOFT_SPRITE_ARC* arc_data, int x, int y, int pri, int heap )
{
	// ポケモンデータ作成
	IMC_POKE_Init( &rbox->boxDraw.poke, rbox->boxDraw.SSM_drawSys, poke_para, arc_data, heap );

	// 表示優先順位
	IMC_POKE_DrawPrioritySet( &rbox->boxDraw.poke, pri );

	// 座標
	IMC_POKE_MatrixSet( &rbox->boxDraw.poke, x, y );
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	ポケモンデータ作成
 *
 *	@param	rbox			右ボックスデータ
 *	@param	poke_para		作成するポケモンのポケモンパラメータ
 *	@param	arc_data		アーカイブファイルデータ格納領域
 *	@param	heap
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_RBOX_AddPoke( IMC_RIGHT_BOX* rbox, POKEMON_PARAM* poke_para, SOFT_SPRITE_ARC* arc_data, int heap )
{
	// ポケモンデータ作成
	IMC_POKE_Init( &rbox->boxDraw.poke, rbox->boxDraw.SSM_drawSys, poke_para, arc_data, heap );
}

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
void IMC_RBOX_MoveAddPoke( IMC_RIGHT_BOX* rbox, IMC_OBJLIST* poke )
{
	// ポケモン上リストの最後に登録
	IMC_OBJLIST_Set(  poke, rbox->boxData.dummy_poke.prev);
}

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
void IMC_RBOX_MoveDeletePoke( IMC_OBJLIST* poke )
{
	// リストから破棄
	IMC_OBJLIST_Delete( poke );
}

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
void IMC_RBOX_DeletePoke( IMC_RIGHT_BOX* rbox )
{
	// ポケモンデータ破棄
	IMC_POKE_Delete( &rbox->boxDraw.poke );
}


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
BOOL IMC_RBOX_AddAccessorieEasy( IMC_RIGHT_BOX* rbox, int accessorie_no, int x, int y, int pri )
{
	IMC_ACCE_ADD acce_add;
	IMC_ACCESSORIE_OBJ* acce_obj;
	
	// 最大登録数チェック
	if( rbox->boxData.obj_count < rbox->boxData.obj_count_max ){

		// アクセサリを登録し、リストに登録
		// アクセサリ登録データ作成
		acce_add.objTbl		= rbox->boxDraw.acce;
		acce_add.SWSPsys	= rbox->boxDraw.SWSP_drawSys;
		acce_add.SWSPchar	= rbox->boxDraw.SWSP_charData[ accessorie_no ];
		acce_add.SWSPpltt	= rbox->boxDraw.SWSP_plttData[ IMC_DRAW_ACCESSORIE_PLTT_ID ];
		acce_add.m_x		= x;
		acce_add.m_y		= y;
		acce_add.accessorie_no = accessorie_no;
		acce_add.pltt_offs	= rbox->boxDraw.accePlttOfsTbl[ accessorie_no ];

		// 登録
		acce_obj = IMC_ACCE_ObjAdd( &acce_add );

		// 表示優先順位設定
		IMC_ACCE_ObjDrawPrioritySet( acce_obj, pri );

		// リストオブジェ作成
		{
			IMC_OBJLIST* objList;

			objList = IMC_OBJLIST_MakeObjList( rbox->boxData.objListTbl, acce_obj, IMC_OBJLIST_ACCE );
			
			
			// リストの先頭に登録
			IMC_OBJLIST_Set( objList, &rbox->boxData.dummy );
		}

		//	オブジェクト数追加
		rbox->boxData.obj_count ++;

		return TRUE;
	}

	return FALSE;
}


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
BOOL IMC_RBOX_AddAccessorieMoveEasy( IMC_RIGHT_BOX* rbox, IMC_OBJLIST* acce_obj )
{
	if( rbox->boxData.obj_count < rbox->boxData.obj_count_max ){

		// リストの先頭に登録
		IMC_OBJLIST_Set( acce_obj, &rbox->boxData.dummy );

		//	オブジェクト数追加
		rbox->boxData.obj_count ++;

		return TRUE;
	}

	return FALSE;
}




//----------------------------------------------------------------------------
/**
 *
 *	@brief	アクセサリの新規追加
 *
 *	@param	rbox				右ボックス用データ
 *	@param	accessorie_no		追加するアクセサリナンバー
 *	@param	x					X座標
 *	@param	y					Y座標
 *
 *	@retval	TRUE	成功
 *	@retval FALSE	失敗
 *
 *
 */
//-----------------------------------------------------------------------------
BOOL IMC_RBOX_AddAccessorie( IMC_RIGHT_BOX* rbox, int accessorie_no, int x, int y, NNSG2dCharacterData** SWSP_UPchar )
{
	IMC_ACCE_ADD acce_add;
	IMC_ACCESSORIE_OBJ* acce_obj;
	
	// 最大登録数チェック
	if( rbox->boxData.obj_count < rbox->boxData.obj_count_max ){

		// アクセサリを登録し、リストに登録
		// アクセサリ登録データ作成
		acce_add.objTbl		= rbox->boxDraw.acce;
		acce_add.SWSPsys	= rbox->boxDraw.SWSP_drawSys;
		acce_add.SWSPchar	= rbox->boxDraw.SWSP_charData[ accessorie_no ];
		acce_add.SWSPpltt	= rbox->boxDraw.SWSP_plttData[ IMC_DRAW_ACCESSORIE_PLTT_ID ];
		acce_add.m_x		= x;
		acce_add.m_y		= y;
		acce_add.accessorie_no = accessorie_no;
		acce_add.pltt_offs	= rbox->boxDraw.accePlttOfsTbl[ accessorie_no ];

		// 登録
		acce_obj = IMC_ACCE_ObjAdd( &acce_add );

		// リストオブジェ作成
		{
			IMC_OBJLIST* objList;

			objList = IMC_OBJLIST_MakeObjList( rbox->boxData.objListTbl, acce_obj, IMC_OBJLIST_ACCE );
			
			
			// リストの先頭に登録
			ImcRightSetAcceList( rbox, objList, TRUE, SWSP_UPchar );
		}

		//	オブジェクト数追加
		rbox->boxData.obj_count ++;

		return TRUE;
	}

	return FALSE;
}

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
 */
//-----------------------------------------------------------------------------
BOOL IMC_RBOX_AddAccessorieMove( IMC_RIGHT_BOX* rbox, IMC_OBJLIST* acce_obj, NNSG2dCharacterData** SWSP_UPchar )
{
	if( rbox->boxData.obj_count < rbox->boxData.obj_count_max ){

		// リストの先頭に登録
		ImcRightSetAcceList( rbox, acce_obj, TRUE, SWSP_UPchar );

		//	オブジェクト数追加
		rbox->boxData.obj_count ++;

		return TRUE;
	}

	return FALSE;
}

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
void IMC_RBOX_DeleteAccessorie( IMC_RIGHT_BOX* rbox, IMC_OBJLIST* acce_obj )
{
	// リストから破棄
	IMC_OBJLIST_Delete( acce_obj );
	
	// アクセサリ破棄
	IMC_ACCE_ObjDelete( (IMC_ACCESSORIE_OBJ*)acce_obj->obj_data );

	// リストを破棄
	IMC_OBJLIST_DeleteObjList( acce_obj );
	
	//	オブジェクト数削除
	rbox->boxData.obj_count--;

	// マイナスの値になったらおかしい
	GF_ASSERT( rbox->boxData.obj_count >= 0 );
}

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
void IMC_RBOX_DeleteAccessorieMove( IMC_RIGHT_BOX* rbox, IMC_OBJLIST* acce_obj )
{
	// リストから破棄
	IMC_OBJLIST_Delete( acce_obj );

	//	オブジェクト数削除
	rbox->boxData.obj_count--;
	// マイナスの値になったらおかしい
	GF_ASSERT( rbox->boxData.obj_count >= 0 );
}

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
void IMC_RBOX_DeleteAccessorieAll( IMC_RIGHT_BOX* rbox )
{
	IMC_OBJLIST_DeleteAll( &rbox->boxData.dummy );
	IMC_OBJLIST_DeleteAll( &rbox->boxData.dummy_poke );

	//	オブジェクト数削除
	rbox->boxData.obj_count = 0;
}

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
void IMC_RBOX_ListMove( IMC_RIGHT_BOX* rbox, int x, int y )
{
	IMC_OBJLIST_ACCEPOKE_ListMove( &rbox->boxData.dummy, x, y );
	IMC_OBJLIST_ACCEPOKE_ListMove( &rbox->boxData.dummy_poke, x, y );
}

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
void IMC_RBOX_PokeUpListMove( IMC_RIGHT_BOX* rbox, int x, int y )
{
	IMC_OBJLIST_ACCEPOKE_ListMove( &rbox->boxData.dummy_poke, x, y );
}

//----------------------------------------------------------------------------
/**
 *	@brief	右ボックスリストの座標を設定
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
void IMC_RBOX_ListMatSet( IMC_RIGHT_BOX* rbox, int old_x, int old_y, int x, int y )
{
	IMC_OBJLIST_ACCEPOKE_ListMove( &rbox->boxData.dummy, -old_x, -old_y );
	IMC_OBJLIST_ACCEPOKE_ListMove( &rbox->boxData.dummy, x, y );
	IMC_OBJLIST_ACCEPOKE_ListMove( &rbox->boxData.dummy_poke, -old_x, -old_y );
	IMC_OBJLIST_ACCEPOKE_ListMove( &rbox->boxData.dummy_poke, x, y );
}


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
void IMC_RBOX_SetObjPriority( IMC_RIGHT_BOX* rbox )
{
	IMC_RBOX_SetObjPriorityMC( rbox, IMC_RBOX_ACCE_PRIORITY_START );
}
// 細かく
void IMC_RBOX_SetObjPriorityMC( IMC_RIGHT_BOX* rbox, int priority )
{
	IMC_OBJLIST* work;

	// 先頭からポケモンまで
	work = rbox->boxData.dummy_poke.next;
	while( work != &rbox->boxData.dummy_poke ){

		if( work->flag == IMC_OBJLIST_ACCE ){
			IMC_ACCE_ObjDrawPrioritySet( work->obj_data, priority );	
		}else{
			
			IMC_POKE_DrawPrioritySet( work->obj_data, priority );	
		}

		priority --;
			
		work = work->next;
	}

	priority -= 8;	// 少し間隔をあける　ご描画防止のため

	// ポケモンから下
	work = rbox->boxData.dummy.next;
	while( work != &rbox->boxData.dummy ){

		if( work->flag == IMC_OBJLIST_ACCE ){
			IMC_ACCE_ObjDrawPrioritySet( work->obj_data, priority );	
		}else{
			
			IMC_POKE_DrawPrioritySet( work->obj_data, priority );	
		}

		priority --;
		work = work->next;
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	優先順位足し算
 *
 *	@param	rbox
 *	@param	pri 
 */
//-----------------------------------------------------------------------------
void IMC_RBOX_AddObjPriorityMC( IMC_RIGHT_BOX* rbox, int priority )
{
	IMC_OBJLIST* work;
	int tmp_pri;

	// 先頭からポケモンまで
	work = rbox->boxData.dummy_poke.next;
	while( work != &rbox->boxData.dummy_poke ){

		if( work->flag == IMC_OBJLIST_ACCE ){
			tmp_pri = IMC_ACCE_ObjDrawPriorityGet( work->obj_data );
			IMC_ACCE_ObjDrawPrioritySet( work->obj_data, tmp_pri + priority );	
		}else{
			
			tmp_pri = IMC_POKE_DrawPriorityGet( work->obj_data );
			IMC_POKE_DrawPrioritySet( work->obj_data, tmp_pri + priority );	
		}

		work = work->next;
	}

	// ポケモンから下
	work = rbox->boxData.dummy.next;
	while( work != &rbox->boxData.dummy ){

		if( work->flag == IMC_OBJLIST_ACCE ){
			tmp_pri = IMC_ACCE_ObjDrawPriorityGet( work->obj_data );
			IMC_ACCE_ObjDrawPrioritySet( work->obj_data, tmp_pri + priority );	
		}else{
			
			tmp_pri = IMC_POKE_DrawPriorityGet( work->obj_data );
			IMC_POKE_DrawPrioritySet( work->obj_data, tmp_pri + priority );	
		}

		work = work->next;
	}
}


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
BOOL IMC_RBOX_TPHit( IMC_RIGHT_BOX* rbox )
{
	TP_HIT_TBL	tp_hit;

	tp_hit.rect.top		= IMC_RBOX_AREA_Y_MOVEOK;
	tp_hit.rect.bottom	= IMC_RBOX_AREA_Y_MOVEOK + IMC_RBOX_AREA_HEIGHT_MOVEOK;
	tp_hit.rect.left	= IMC_RBOX_AREA_X_MOVEOK;
	tp_hit.rect.right	= IMC_RBOX_AREA_X_MOVEOK + IMC_RBOX_AREA_WIDTH_MOVEOK;

	return GF_TP_SingleHitCont( &tp_hit );
}

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
BOOL IMC_RBOX_TPHitSelf( IMC_RIGHT_BOX* rbox, int x, int y )
{
	TP_HIT_TBL	tp_hit;

	tp_hit.rect.top		= IMC_RBOX_AREA_Y_MOVEOK;
	tp_hit.rect.bottom	= IMC_RBOX_AREA_Y_MOVEOK + IMC_RBOX_AREA_HEIGHT_MOVEOK;
	tp_hit.rect.left	= IMC_RBOX_AREA_X_MOVEOK;
	tp_hit.rect.right	= IMC_RBOX_AREA_X_MOVEOK + IMC_RBOX_AREA_WIDTH_MOVEOK;

	return GF_TP_SingleHitSelf( &tp_hit, x, y );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	オブジェクトごとの当たり判定を行う
 *
 *	@param	rbox	右ボックス
 *
 *	@retval	非NULL	あたるアクセサリ
 *	@retval	NULL	なし
 *
 *
 */
//-----------------------------------------------------------------------------
IMC_OBJLIST* IMC_RBOX_TPHitObj( IMC_RIGHT_BOX* rbox )
{
	IMC_OBJLIST* work;
	BOOL	ret;

	// 先頭のアクセサリから
	work = rbox->boxData.dummy_poke.next;
	while( work != &rbox->boxData.dummy_poke ){

		ret = IMC_OBJLIST_ACCEPOKE_Hit( work, IMC_OBJ_LIST_FUNC_TP_NOW, 0 );
		
		if(ret == TRUE){

			return work;
		}
		
		work = work->next;
	}


	// ポケモンの下のアクセサリ
	work = rbox->boxData.dummy.next;
	while( work != &rbox->boxData.dummy ){

		ret = IMC_OBJLIST_ACCEPOKE_Hit( work, IMC_OBJ_LIST_FUNC_TP_NOW, 0 );
		
		if(ret == TRUE){

			return work;
		}
		
		work = work->next;
	}


	return NULL;
}

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
IMC_OBJLIST* IMC_RBOX_TPHitObjEx( IMC_RIGHT_BOX* rbox, int* offset_x, int* offset_y, NNSG2dCharacterData** SWSP_UPchar )
{
	IMC_OBJLIST* work;
	BOOL	ret;

	// ポケモンの上のアクセサリから
	work = rbox->boxData.dummy_poke.next;
	while( work != &rbox->boxData.dummy_poke ){

		ret = IMC_OBJLIST_ACCEPOKE_HitEx( work, offset_x, offset_y, SWSP_UPchar );
		
		if(ret == TRUE){

			return work;
		}
		
		work = work->next;
	}


	// ポケモンの下のアクセサリ
	work = rbox->boxData.dummy.next;
	while( work != &rbox->boxData.dummy ){

		ret = IMC_OBJLIST_ACCEPOKE_HitEx( work, offset_x, offset_y, SWSP_UPchar );
		
		if(ret == TRUE){

			return work;
		}
		
		work = work->next;
	}

	return NULL;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	BGを表示
 *
 *	@param	rbox		右ボックス
 *	@param	bg_num		右ボックスBGナンバー
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_RBOX_BGSet( IMC_RIGHT_BOX* rbox, int bg_num, int heap )
{
	IMC_BG_ADD add;
	
	// 登録データ設定
	add.bg_ini		= rbox->boxDraw.BG_Ini;
	add.arc_file	= ARC_IMAGECLIP_GRA;
	add.char_arc	= IMC_BG_RIGHT_CG_ARC_GET(bg_num);
	add.pltt_arc	= IMC_BG_RIGHT_CL_ARC_GET(bg_num);
	add.scrn_arc	= IMC_BG_RIGHT_SC_ARC_GET(bg_num);
	add.x			= IMC_RBOX_AREA_X;
	add.y			= IMC_RBOX_AREA_Y;
	add.frame		= GF_BGL_FRAME2_M;
	add.pltt_num	= IMC_RBOX_BG_PLTT_NUM;
	add.pltt_offs	= IMC_RBOX_BG_PLTT_OFFS;
	add.char_offs	= 0;
	add.heap		= heap;

	IMC_BG_MakaObj( &rbox->boxDraw.bg, &add );

	rbox->boxDraw.bg_no = bg_num;
}

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
void IMC_RBOX_BGClean( IMC_RIGHT_BOX* rbox )
{
	IMC_BG_DeleteObj( &rbox->boxDraw.bg );
}

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
void IMC_RBOX_GetPokeMatrix( IMC_RIGHT_BOX* rbox, int* x, int* y )
{
	*x = SoftSpriteParaGet( rbox->boxDraw.poke.sprite, SS_PARA_POS_X );
	*y = SoftSpriteParaGet( rbox->boxDraw.poke.sprite, SS_PARA_POS_Y );
}

//----------------------------------------------------------------------------
/**
 *	@brief	保持しているアクセサリ数取得
 *
 *	@param	rbox	右ボックス
 *
 *	@return	アクセサリ数
 */
//-----------------------------------------------------------------------------
int IMC_RBOX_GetNowHaveAcceNum( IMC_RIGHT_BOX* rbox )
{
	return rbox->boxData.obj_count;
}

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
void IMC_RBOX_GetPokeUpListEncSize( IMC_RIGHT_BOX* rbox, int* enc_x, int* enc_y )
{
	int enc_x_max;
	int enc_y_max;
	int enc_x_w;
	int enc_y_w;
	IMC_OBJLIST* work;

	work = rbox->boxData.dummy_poke.next;
	enc_x_max = 0;
	enc_y_max = 0;
	while( work != &rbox->boxData.dummy_poke ){
		imcRbox_GetAcceEncSize( work, &enc_x_w, &enc_y_w );

		if(MATH_ABS(enc_x_w) > MATH_ABS(enc_x_max) ){
			enc_x_max = enc_x_w;
		}
		if( MATH_ABS(enc_y_w) > MATH_ABS(enc_y_max) ){
			enc_y_max = enc_y_w;
		}

		work = work->next;
	}

	*enc_x = enc_x_max;
	*enc_y = enc_y_max;
}

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
void IMC_RBOX_SetObjColor( IMC_RIGHT_BOX* rbox, GXRgb color )
{
	IMC_OBJLIST* work;

	// ポケモンの上のアクセサリから
	work = rbox->boxData.dummy_poke.next;
	while( work != &rbox->boxData.dummy_poke ){

		if( work->flag == IMC_OBJLIST_ACCE ){
			IMC_ACCESSORIE_OBJ* p_obj = work->obj_data;
			SWSP_SetSpriteDiffColor( p_obj->drawObj, color );
		}else{
			IMC_POKE* p_obj = work->obj_data;
			SoftSpriteParaSet( p_obj->sprite, SS_PARA_DIFF_R, (color >> 10) & 0x1f );
			SoftSpriteParaSet( p_obj->sprite, SS_PARA_DIFF_G, (color >> 5) & 0x1f );
			SoftSpriteParaSet( p_obj->sprite, SS_PARA_DIFF_B, (color >> 0) & 0x1f );
		}
		work = work->next;
	}

	// ポケモンの下のアクセサリ
	work = rbox->boxData.dummy.next;
	while( work != &rbox->boxData.dummy ){
		IMC_ACCESSORIE_OBJ* p_obj = work->obj_data;
		SWSP_SetSpriteDiffColor( p_obj->drawObj, color );
		work = work->next;
	}
}







//----------------------------------------------------------------------------
/**
 *	@brief	上か下にアクセサリを設定する
 *
 *	@param	p_data			ボックスデータ
 *	@param	objList			アクセサリデータ
 *	@param	top_bottom		TRUE　先頭　BOTTOM　最後尾
 *	@param	SWSP_UPchar			判定用キャラクタデータ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void ImcRightSetAcceList( IMC_RIGHT_BOX* p_data, IMC_OBJLIST* objList, BOOL top_bottom, NNSG2dCharacterData** SWSP_UPchar  )
{
	int i;
	int x;
	int y;
	int size_x;
	int size_y;
	int in_size_x;
	int in_size_y;
	int top;
	int bottom;
	int left;
	int right;
	int ch_x, ch_y;
	BOOL check;
	NNSG2dCharacterData* char_data;
	
	// 座標を取得
	IMC_OBJLIST_ACCEPOKE_MatGet( objList, &x, &y );

	// サイズを取得
	IMC_OBJLIST_ACCEPOKE_SizeGet( objList, &size_x, &size_y );

	// 食い込んでよいサイズ取得
	IMC_OBJLIST_ACCEPOKE_InSizeGet( objList, &in_size_x, &in_size_y );

	top = y + in_size_y;
	bottom = y + size_y - in_size_y;
	left = x + in_size_x;
	right = x + size_x - in_size_x;

	
	// キャラクタデータ取得
	char_data = SWSP_UPchar[ IMC_DRAW_POKE_CHAR_ID ];
	
	// ポケモンエリアに引っかかるかチェック
	// 16点チェックする
	check = FALSE;
	for( i=0; i<16; i++ ){
		IMC_CALC_HitPoint16Get( top, bottom, left, right, i, &ch_x, &ch_y );
		check  |= IMC_POKE_TPHitExSelf( &p_data->boxDraw.poke, ch_x, ch_y, char_data );
	}

	
	// ポケモンの上ならポケモンの上リストに
	if( check ){
		
		if( top_bottom ){
			// 先頭に登録
			IMC_OBJLIST_Set( objList, &p_data->boxData.dummy_poke );
		}else{
			// 最後尾に登録
			IMC_OBJLIST_Set( objList, p_data->boxData.dummy_poke.prev );
		}
	}else{

		if( top_bottom ){
			// 先頭に登録
			IMC_OBJLIST_Set( objList, &p_data->boxData.dummy );
		}else{
			// 最後尾に登録
			IMC_OBJLIST_Set( objList, p_data->boxData.dummy.prev );
		}
	}
}

//----------------------------------------------------------------------------
/**
 *	@brief	アクセサリ食い込みサイズ　取得
 *
 *	@param	objlist		アクセサリリスト
 *	@param	enc_x		食い込みｘサイズ
 *	@param	enc_y		食い込みｙサイズ
 *
 *	@return	none
 */
//-----------------------------------------------------------------------------
static void imcRbox_GetAcceEncSize( IMC_OBJLIST* objlist, int* enc_x, int* enc_y )
{
	int size_x,size_y;			// オブジェクトサイズXY
	int mat_x, mat_y;			// オブジェクト座標
	int in_size_x, in_size_y;	// 食い込んでよいサイズXY
	int top, bottom, left, right;// 上下右左
	int in_top, in_bottom, in_left, in_right;// 食い込み上下右左

	IMC_OBJLIST_ACCEPOKE_SizeGet( objlist, &size_x, &size_y );
	IMC_OBJLIST_ACCEPOKE_MatGet( objlist, &mat_x, &mat_y );
	IMC_OBJLIST_ACCEPOKE_InSizeGet( objlist, &in_size_x, &in_size_y );
	
	top		= mat_y + in_size_y;
	bottom	= mat_y + size_y - in_size_y;
	left	= mat_x + in_size_x;
	right	= mat_x + size_x - in_size_x;


	// 右ボックス矩形外にどのくらい食い込んでいるかをチェック
	// プラスが食い込んでいるサイズ　マイナスはOK
	in_left		= IMC_RBOX_AREA_X_MOVEOK - left;
	in_right	= right - (IMC_RBOX_AREA_X_MOVEOK + IMC_RBOX_AREA_WIDTH_MOVEOK);
	in_top		= IMC_RBOX_AREA_Y_MOVEOK - top;
	in_bottom	= bottom - (IMC_RBOX_AREA_Y_MOVEOK + IMC_RBOX_AREA_HEIGHT_MOVEOK);

	// 食い込んでいるサイズを返す
	if( in_left > 0 ){
		*enc_x = in_left;
	}else if( in_right > 0 ){
		*enc_x = -in_right;
	}else{
		*enc_x = 0;
	}
	if( in_top > 0 ){
		*enc_y = in_top;
	}else if( in_bottom > 0 ){
		*enc_y = -in_bottom;
	}else{
		*enc_y = 0;
	}
}
