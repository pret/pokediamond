//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_obj_list.c
 *	@brief		オブジェクトリスト	表示優先順位　タッチパネル判定優先順位などを管理
 *	@author		tomoya takahashi 
 *	@data		2005.09.28
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#include "system.h"
#include "assert.h"
#include <string.h>

#define	__IMC_OBJLIST_H_GLOBAL
#include "include/application/imageClip/imc_obj_list.h"

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

//----------------------------------------------------------------------------
/**
 *
 *	@brief	オブジェリストテーブルを初期化
 *
 *	@param	tbl		オブジェリストテーブル実態のポインタ
 *	@param	num		管理したいオブジェクト数
 *	@param	heap	使用するヒープID
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_OBJLIST_TblInit( IMC_OBJLIST_TBL* tbl, int num, int heap )
{	
	tbl->plist = sys_AllocMemory( heap, sizeof(IMC_OBJLIST) * num );
	GF_ASSERT( tbl->plist );
	memset( tbl->plist, 0, sizeof(IMC_OBJLIST) * num );
	tbl->num	= num;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	オブジェリストテーブルの破棄
 *
 *	@param	tbl		オブジェクトリストテーブル実態のポインタ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_OBJLIST_TblDelete( IMC_OBJLIST_TBL* tbl )
{
	sys_FreeMemoryEz( tbl->plist );
	tbl->plist = NULL;
	tbl->num = 0;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	オブジェリストデータ作成
 *
 *	@param	tbl		オブジェリストテーブル
 *	@param	work	オブジェワーク
 *	@param	flag	オブジェの定数	（重複注意）
 *
 *	@return	IMC_OBJLIST*	オブジェリスト
 *
 *
 */
//-----------------------------------------------------------------------------
IMC_OBJLIST* IMC_OBJLIST_MakeObjList( IMC_OBJLIST_TBL* tbl, void* work, int flag )
{
	int i;
	
	GF_ASSERT( tbl->plist );
	GF_ASSERT( tbl->num );

	for(i=0; i<tbl->num; i++){
		if(tbl->plist[ i ].obj_data == NULL){
			break;
		}
	}
	GF_ASSERT( tbl->num > i );

	tbl->plist[ i ].obj_data	= work;
	tbl->plist[ i ].flag		= flag; 

	return (tbl->plist + i);
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	オブジェリストデータ破棄
 *
 *	@param	obj		破棄するオブジェリスト
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_OBJLIST_DeleteObjList( IMC_OBJLIST* obj )
{
	memset( obj,0,sizeof(IMC_OBJLIST) );
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	リストに設定する	
 *
 *	@param	work			データを設定するワーク
 *	@param	dummy			前のデータ
 *
 *	@return
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_OBJLIST_Set( IMC_OBJLIST* work, IMC_OBJLIST* prev )
{
	work->next = prev->next;
	prev->next->prev = work;
	work->prev = prev;
	prev->next = work;
}

//----------------------------------------------------------------------------
/**
 *
 *	@brief	リストから削除
 *
 *	@param	obj		削除するリストデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_OBJLIST_Delete( IMC_OBJLIST* obj )
{
	obj->prev->next = obj->next;
	obj->next->prev = obj->prev;
}


//----------------------------------------------------------------------------
/**
 *
 *	@brief	先頭ダミーデータにつながっているファイルを全て破棄する
 *
 *	@param	dummy	ダミーデータ
 *
 *	@return	none
 *
 *
 */
//-----------------------------------------------------------------------------
void IMC_OBJLIST_DeleteAll( IMC_OBJLIST* dummy )
{
	IMC_OBJLIST* work;
	IMC_OBJLIST* next;

	work = dummy->next;
	while( work != dummy ){
		next = work->next;
		
		IMC_OBJLIST_Delete( work );
		IMC_OBJLIST_DeleteObjList( work );

		work = next;
	}
}
