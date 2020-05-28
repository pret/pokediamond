//============================================================================================
/**
 * @file	bmp_menu_list.h
 * @brief	bmp_menu と bmp_list で使用する文字列指定構造体の処理
 * @author	taya
 * @date	2005.12.02
 *
 * bmp_menu と bmp_list で全く同じ型・同じ用途の構造体を別個に定義しているのでまとめておく。
 *
 */
//============================================================================================

#include "common.h"

#include "system/bmp_menu_list.h"


//==============================================================
// Prototype
//==============================================================
static BMP_MENULIST_DATA*  SeekEmptyListPos( BMP_MENULIST_DATA* list, u32* heapID );


/// リストの終端コード
#define LIST_ENDCODE		((const void*)0xffffffff)

//------------------------------------------------------------------
/**
 * リストバッファを作成する。
 * 作成後、BMP_MENULIST_AddArchiveString か BMP_MENULIST_AddString を使って文字列をセットする
 *
 * @param   maxElems		リストに登録する文字列の最大件数
 * @param   heapID			リスト作成先ヒープID
 *
 * @retval  BMP_MENULIST_DATA*		作成されたリストバッファ
 */
//------------------------------------------------------------------
BMP_MENULIST_DATA*  BMP_MENULIST_Create( u32 maxElems, u32 heapID )
{
	// 指定数より１つ多めに作っておき、最後に終端コードを置いて管理する
	BMP_MENULIST_DATA* list = sys_AllocMemory( heapID, sizeof(BMP_MENULIST_DATA)*(maxElems+1) );
	if( list )
	{
		u32 i;

		for(i=0; i<maxElems; i++)
		{
			list[i].str = NULL;
			list[i].param = 0;
		}

		list[i].str = LIST_ENDCODE;
		list[i].param = heapID;
	}
	return list;
}


//------------------------------------------------------------------
/**
 * リストバッファを破棄する
 * ※BMP_MENULIST_Createで作成したもの以外を渡してはダメ。
 *
 * @param   list		リストバッファ
 *
 */
//------------------------------------------------------------------
void BMP_MENULIST_Delete( BMP_MENULIST_DATA* list_top )
{
    BMP_MENULIST_STRBUFDelete(list_top);
	sys_FreeMemoryEz(list_top);
}

//------------------------------------------------------------------
/**
 * リストバッファに文字列＆パラメータをセットする（マネージャを介してアーカイブデータから読み込み）
 *
 * @param   list		[in] リストバッファ
 * @param   man			[in] メッセージデータマネージャ
 * @param   strID		文字列ID
 * @param   param		文字列パラメータ
 *
 */
//------------------------------------------------------------------
void BMP_MENULIST_AddArchiveString( BMP_MENULIST_DATA* list, const MSGDATA_MANAGER* man, u32 strID, u32 param )
{
	u32 dmy;

	list = SeekEmptyListPos(list, &dmy);

	if( list )
	{
		list->str = MSGMAN_AllocString( man, strID );
		list->param = param;
	}
}

//------------------------------------------------------------------
/**
 * リストバッファに文字列＆パラメータをセットする（文字列を直接指定）
 *
 * @param   list		[in] リストバッファ
 * @param   str			[in] 文字列
 * @param   param		文字列パラメータ
 *
 */
//------------------------------------------------------------------
void BMP_MENULIST_AddString( BMP_MENULIST_DATA* list, const STRBUF* str, u32 param )
{
	u32 heapID;

	list = SeekEmptyListPos(list, &heapID);

	if( list )
	{
		list->str = STRBUF_CreateBufferCopy( str, heapID );
		list->param = param;
	}
}


//------------------------------------------------------------------
/**
 * リストバッファに他のリストのデータをLinkする
 * @param   list		[inout] リストバッファ
 * @param   insList		[in] リストポインタ
 *
 */
//------------------------------------------------------------------
void BMP_MENULIST_AddLinkList( BMP_MENULIST_DATA* list, const BMP_MENULIST_DATA* insList )
{
	u32 heapID;

	list = SeekEmptyListPos(list, &heapID);

	if( list )
	{
		list->str = insList->str;
		list->param = insList->param;
	}
}

//------------------------------------------------------------------
/**
 * リストの先頭から空きがある位置をシークする
 *
 * @param   list		[in]  空き位置ポインタ（無ければNULL）
 * @param   heapID		[out] リスト作成時に保存したヒープIDを受け取る
 *
 * @retval  BMP_MENULIST_DATA*		
 */
//------------------------------------------------------------------
static BMP_MENULIST_DATA*  SeekEmptyListPos( BMP_MENULIST_DATA* list, u32* heapID )
{
	BMP_MENULIST_DATA* ret;

	while( list->str != NULL )
	{
		if( list->str == LIST_ENDCODE )
		{
			GF_ASSERT(0);
			return NULL;
		}
		list++;
	}

	ret = list;

	while( list->str != LIST_ENDCODE )
	{
		list++;
	}

	*heapID = list->param;

	return ret;
}

//------------------------------------------------------------------
/**
 * リストバッファのSTRBUFを破棄する
 * ※BMP_MENULIST_Createで作成したもの以外を渡してはダメ。
 *
 * @param   list		リストバッファ
 *
 */
//------------------------------------------------------------------
void BMP_MENULIST_STRBUFDelete( BMP_MENULIST_DATA* list_top )
{
	BMP_MENULIST_DATA* list = list_top;
	while( list->str != LIST_ENDCODE )
	{
		if( list->str == NULL )
		{
			break;
		}
		STRBUF_Delete((STRBUF*)(list->str));
        list->str = NULL;
		list++;
	}
}

