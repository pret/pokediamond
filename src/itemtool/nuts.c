//============================================================================================
/**
 * @file	nuts.c
 * @brief	木の実データ処理
 * @author	Hiroyuki Nakamura
 * @date	06.01.27
 */
//============================================================================================
#include "common.h"
#include "system/arc_tool.h"
#include "system/msgdata.h"
#include "msgdata\msg.naix"
#include "msgdata\msg_nuts_name.h"
#include "msgdata\msg_nuts_info.h"

#define	NUTS_H_GLOBAL
#include "itemtool/nuts.h"
#include "nuts_data.naix"


//============================================================================================
//	定数定義
//============================================================================================
// 木の実データ
struct _NUTS_DATA {
	u16 size;				// 大きさ
	u8	hardness;			// 堅さ
	u8	magnification;		// 実の倍率

	u8	speed;				// 育つ速度
	u8	absorption;			// 根の吸収力
	u8	karai;				// 辛さ
	u8	sibui;				// 渋さ

	u8	amai;				// 甘さ
	u8	nigai;				// 苦さ
	u8	suppai;				// 酸っぱさ
	u8	umai;				// 旨さ
};


//--------------------------------------------------------------------------------------------
/**
 * 木の実データのハンドル取得
 *
 * @param	id		木の実番号
 * @param	heap	ヒープID
 *
 * @return	データハンドル
 */
//--------------------------------------------------------------------------------------------
ARCHANDLE * Nuts_DataHandleGet( u32 heap )
{
	return ArchiveDataHandleOpen( ARC_NUTSDATA, heap );
}

//--------------------------------------------------------------------------------------------
/**
 * 木の実データロード（ハンドル使用）
 *
 * @param	handle	データハンドル
 * @param	id		木の実番号
 * @param	heap	ヒープID
 *
 * @return	木の実データ
 */
//--------------------------------------------------------------------------------------------
NUTSDATA * Nuts_DataLoadHandle( ARCHANDLE * handle, u32 id, u32 heap )
{
	return ArchiveDataLoadAllocByHandle( handle, NARC_nuts_data_nuts001_dat+id, heap );
}

//--------------------------------------------------------------------------------------------
/**
 * 木の実データハンドルを閉じる
 *
 * @param	handle	データハンドル
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void Nuts_DataHandleClose( ARCHANDLE * handle )
{
	ArchiveDataHandleClose( handle );
}

//--------------------------------------------------------------------------------------------
/**
 * 木の実データロード
 *
 * @param	id		木の実番号
 * @param	heap	ヒープID
 *
 * @return	木の実データ
 */
//--------------------------------------------------------------------------------------------
NUTSDATA * Nuts_DataLoad( u32 id, u32 heap )
{
	return ArchiveDataLoadMalloc( ARC_NUTSDATA, NARC_nuts_data_nuts001_dat+id, heap );
}

//--------------------------------------------------------------------------------------------
/**
 * 木の実データロード（アイテム番号から）
 *
 * @param	item	アイテム番号
 * @param	heap	ヒープID
 *
 * @return	木の実データ
 */
//--------------------------------------------------------------------------------------------
NUTSDATA * Nuts_DataLoadItem( u32 item, u32 heap )
{
	return Nuts_DataLoad( item-NUTS_START_ITEMNUM, heap );
}

//--------------------------------------------------------------------------------------------
/**
 * 木の実パラメータ取得
 *
 * @param	dat		木の実データ
 * @param	prm		取得パラメータID
 *
 * @return	取得パラメータ
 */
//--------------------------------------------------------------------------------------------
u32 Nuts_ParamGet( NUTSDATA * dat, u32 prm )
{
	switch( prm ){
	case NUTS_PRM_SIZE:				// 大きさ
		return dat->size;
	case NUTS_PRM_HARDNESS:			// 堅さ
		return dat->hardness;
	case NUTS_PRM_MAGNIFICATION:	// 実の倍率
		return dat->magnification;
	case NUTS_PRM_SPEED:			// 育つ速度
		return dat->speed;
	case NUTS_PRM_ABSORPTION:		// 根の吸収力
		return dat->absorption;
	case NUTS_PRM_KARAI:			// 辛さ
		return dat->karai;
	case NUTS_PRM_SIBUI:			// 渋さ
		return dat->sibui;
	case NUTS_PRM_AMAI:				// 甘さ
		return dat->amai;
	case NUTS_PRM_NIGAI:			// 苦さ
		return dat->nigai;
	case NUTS_PRM_SUPPAI:			// 酸っぱさ
		return dat->suppai;
	case NUTS_PRM_UMAI:				// 旨さ
		return dat->umai;
	}
	return 0;
}

//--------------------------------------------------------------------------------------------
/**
 * 木の実名取得
 *
 * @param   buf			格納先
 * @param	id			木の実番号
 * @param   heap		ヒープID（テンポラリとして使用）
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void NutsNameGet( STRBUF * buf, u16 id, u32 heap )
{
	MSGDATA_MANAGER * man;
	
	man = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_nuts_name_dat, heap );
	MSGMAN_GetString( man, id, buf );
	MSGMAN_Delete( man );
}

//--------------------------------------------------------------------------------------------
/**
 * 木の実名取得（領域確保）
 *
 * @param	id			木の実番号
 * @param   heap		ヒープID（テンポラリとして使用）
 *
 * @return	取得した木の実名のバッファ
 *
 * @li	解放は各自で
 */
//--------------------------------------------------------------------------------------------
STRBUF * NutsNameGetAlloc( u16 id, u32 heap )
{
	MSGDATA_MANAGER * man;
	STRBUF * str;
	
	man = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_nuts_name_dat, heap );
	str = MSGMAN_AllocString( man, id );
	MSGMAN_Delete( man );
	return str;
}

//--------------------------------------------------------------------------------------------
/**
 * 木の実名取得（アイテム番号から）
 *
 * @param   buf			格納先
 * @param	item		アイテム番号
 * @param   heap		ヒープID（テンポラリとして使用）
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void NutsNameGet_Item( STRBUF * buf, u16 item, u32 heap )
{
	NutsNameGet( buf, item-NUTS_START_ITEMNUM, heap );
}

//--------------------------------------------------------------------------------------------
/**
 * 木の実名取得（アイテム番号から）（領域確保）
 *
 * @param	item		アイテム番号
 * @param   heap		ヒープID（テンポラリとして使用）
 *
 * @return	取得した木の実名のバッファ
 *
 * @li	解放は各自で
 */
//--------------------------------------------------------------------------------------------
STRBUF * NutsNameGetAlloc_Item( u16 item, u32 heap )
{
	return NutsNameGetAlloc( item-NUTS_START_ITEMNUM, heap );
}

//--------------------------------------------------------------------------------------------
/**
 * 説明取得
 *
 * @param   buf			格納先
 * @param	id			木の実番号
 * @param	heap		ヒープID（テンポラリとして使用）
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void NutsInfoGet( STRBUF * buf, u16 id, u16 heap )
{
	MSGDATA_MANAGER * man;
	
	man = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_nuts_info_dat, heap );
	MSGMAN_GetString( man, id, buf );
	MSGMAN_Delete( man );
}

//--------------------------------------------------------------------------------------------
/**
 * 説明取得（領域確保）
 *
 * @param	id			木の実番号
 * @param	heap		ヒープID（テンポラリとして使用）
 *
 * @return	取得した木の実名のバッファ
 *
 * @li	解放は各自で
 */
//--------------------------------------------------------------------------------------------
STRBUF * NutsInfoGetAlloc( u16 id, u16 heap )
{
	MSGDATA_MANAGER * man;
	STRBUF * str;
	
	man = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_nuts_info_dat, heap );
	str = MSGMAN_AllocString( man, id );
	MSGMAN_Delete( man );
	return str;
}

//--------------------------------------------------------------------------------------------
/**
 * 説明取得（アイテム番号から）
 *
 * @param   buf			格納先
 * @param	item		アイテム番号
 * @param	heap		ヒープID（テンポラリとして使用）
 *
 * @return	none
 */
//--------------------------------------------------------------------------------------------
void NutsInfoGet_Item( STRBUF * buf, u16 item, u16 heap )
{
	NutsInfoGet( buf, item-NUTS_START_ITEMNUM, heap );
}

//--------------------------------------------------------------------------------------------
/**
 * 説明取得（アイテム番号から）（領域確保）
 *
 * @param	item		アイテム番号
 * @param	heap		ヒープID（テンポラリとして使用）
 *
 * @return	取得した木の実名のバッファ
 *
 * @li	解放は各自で
 */
//--------------------------------------------------------------------------------------------
STRBUF * NutsInfoGetAlloc_Item( u16 item, u16 heap )
{
	return NutsInfoGetAlloc( item-NUTS_START_ITEMNUM, heap );
}
