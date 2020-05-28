//============================================================================================
/**
 * @file	msgdata.c
 * @brief	各種メッセージデータ取り扱い
 * @author	taya
 * @date	2005.09.26
 */
//============================================================================================
#include "common.h"
#include "gflib\strbuf_family.h"
#include "system\arc_tool.h"
#include "system\pm_str.h"
#include "system\get_text.h"
#include "system\msgdata.h"

#include "msgdata\msg.naix"
#include "msgdata\msg_monsname.h"
#include "msgdata\msg_wazaname.h"
#include "msgdata\msg_typename.h"
#include "msgdata\msg_tokusei.h"
#include "msgdata\msg_status.h"
#include "msgdata\msg_condition.h"
#include "msgdata\msg_taste.h"
#include "msgdata\msg_itemname.h"
#include "msgdata\msg_iteminfo.h"


// このdefineを有効にすると、暗号化メッセージ対応
#define  MSGDATA_CODED	


/*------------------------------------------------------------*/
/** 文字列パラメータ                                          */
/*------------------------------------------------------------*/
typedef struct {
	u32  offset;	///< ファイル先頭からのバイトオフセット
	u32  len;		///< 文字数（EOMを含む）
}MSG_PARAM_BLOCK;

/*------------------------------------------------------------*/
/** 文字列データヘッダ                                        */
/*------------------------------------------------------------*/
struct _MSGDATA_HEADER{
	#ifdef MSGDATA_CODED
	u16					numMsgs;
	u16					randValue;
	#else
	union {
		u32				numMsgs;
		u32				randValue;
	};
	#endif
	MSG_PARAM_BLOCK		params[];
};


//==============================================================
// Prototype
//==============================================================
static void StrSet( STRCODE* dst, const STRCODE* src, const MSG_PARAM_BLOCK* param );


//------------------------------------------------------------------
/**
 * メッセージデータをアーカイブからロードする
 *
 * @param   arcID		アーカイブファイルＩＤ
 * @param   datID		アーカイブファイル内のメッセージデータＩＤ
 * @param   heapID		ヒープＩＤ
 *
 * @retval  MSGDATA_HEADER*		メッセージデータポインタ
 */
//------------------------------------------------------------------
MSGDATA_HEADER* MSGDAT_Load( u32 arcID, u32 datID, u32 heapID )
{
	return ArchiveDataLoadMalloc( arcID, datID, heapID );
}
//------------------------------------------------------------------
/**
 * ロードしたメッセージデータをアンロードする
 *
 * @param   msgdat		メッセージデータポインタ
 *
 */
//------------------------------------------------------------------
void MSGDAT_Unload( MSGDATA_HEADER* msgdat )
{
	sys_FreeMemoryEz( msgdat );
}




//------------------------------------------------------------------
/**
 * 文字列ごとのパラメータ構造体オフセットを計算
 *
 * @param   strID		
 *
 * @retval  inline int		
 */
//------------------------------------------------------------------
static inline int CalcParamBlockOfs( u32 strID )
{
	return sizeof(MSGDATA_HEADER) + sizeof(MSG_PARAM_BLOCK) * strID;
}



//===============================================================================================
//  暗号化されたデータの復号処理
//===============================================================================================

//------------------------------------------------------------------
/**
 * 暗号化された文字列パラメータ構造体を復号する
 *
 * @param   param		パラメータ構造体へのポインタ
 * @param   strID		文字列ID
 * @param   rand		暗号キー乱数
 */
//------------------------------------------------------------------
static inline void DecodeParam( MSG_PARAM_BLOCK* param, u32 strID, u32 rand )
{
#ifdef MSGDATA_CODED
	rand = (rand * 765 * (strID+1)) & 0xffff;
	rand |= (rand << 16);

	param->offset ^= rand;
	param->len ^= rand;
#endif
}
//------------------------------------------------------------------
/**
 * 暗号化された文字列を復号する
 *
 * @param   str			文字列ポインタ
 * @param   len			文字列長
 * @param   strID		文字列ID
 * @param   rand		暗号キー乱数
 *
 */
//------------------------------------------------------------------
static inline void DecodeStr( STRCODE* str, u32 len, u32 strID, u16 rand )
{
#ifdef MSGDATA_CODED
	rand = (strID + 1) * 596947;
	while(len--)
	{
		*str ^= rand;
		str++;
		rand += 18749;
	}
#endif
}








//------------------------------------------------------------------
/**
 * ロードしたメッセージデータから文字列をコピー
 *
 * @param   msgdat		メッセージデータポインタ
 * @param   strID		文字列ＩＤ
 * @param   dst			文字列コピー先バッファ
 *
 */
//------------------------------------------------------------------
void MSGDAT_Get( const MSGDATA_HEADER* msgdat, u32 strID, STRCODE* dst )
{
	if( strID < msgdat->numMsgs )
	{
		MSG_PARAM_BLOCK param;
		const STRCODE* str;

		param = msgdat->params[strID];
		DecodeParam( &param, strID, msgdat->randValue );
		str = (STRCODE*)(((u8*)msgdat) + param.offset);
		StrSet( dst, str, &param );
		DecodeStr( dst, param.len, strID, msgdat->randValue );
	}
	else
	{
		GF_ASSERT(0);
	}
}
//------------------------------------------------------------------
/**
 * ロードしたメッセージデータから指定文字列サイズ分のメモリを確保＆コピー
 *
 * @param   msgdat		メッセージデータポインタ
 * @param   strID		文字列ID
 * @param   heapID		メモリ確保用のヒープID
 *
 * @retval  文字列がコピーされたメモリブロック（失敗時はNULL）
 *
 */
//------------------------------------------------------------------
STRCODE* MSGDAT_GetAlloc( const MSGDATA_HEADER* msgdat, u32 strID, u32 heapID )
{
	if( strID < msgdat->numMsgs )
	{
		MSG_PARAM_BLOCK param;
		const STRCODE* src;
		STRCODE *dst;

		param = msgdat->params[strID];
		DecodeParam( &param, strID, msgdat->randValue );
		src = (STRCODE*)(((u8*)msgdat) + param.offset);
		dst = sys_AllocMemory( heapID, param.len*sizeof(STRCODE) );
		if( dst )
		{
			StrSet( dst, src, &param );
			DecodeStr( dst, param.len, strID, msgdat->randValue );
		}
		return dst;
	}

	GF_ASSERT(0);
	return NULL;
}
//------------------------------------------------------------------
/**
 * 指定文字列のみをロード＆指定バッファにコピー
 *
 * @param   arcID		アーカイブファイルＩＤ
 * @param   datID		アーカイブファイル内のメッセージデータＩＤ
 * @param   msgID		メッセージデータ内の文字列ＩＤ
 * @param   heapID		一時メモリ確保用のヒープＩＤ
 * @param   dst			文字列コピー先バッファ
 *
 */
//------------------------------------------------------------------
void MSGDAT_GetDirect( u32 arcID, u32 datID, u32 strID, u32 heapID, STRCODE* dst )
{
	ARCHANDLE* arc = ArchiveDataHandleOpen(arcID, heapID);

	if( arc )
	{
		MSGDATA_HEADER  header;
		MSG_PARAM_BLOCK  param;
		STRCODE*  str;
		u32 size;

		ArchiveDataLoadOfsByHandle( arc, datID, 0, sizeof(MSGDATA_HEADER), &header);
		ArchiveDataLoadOfsByHandle( arc, datID, CalcParamBlockOfs(strID), sizeof(MSG_PARAM_BLOCK), &param );
		DecodeParam( &param, strID, header.randValue );

		size = param.len * sizeof(STRCODE);
		ArchiveDataLoadOfsByHandle( arc, datID, param.offset, size, dst );
		DecodeStr( dst, param.len, strID, header.randValue );

		ArchiveDataHandleClose( arc );
	}
}
//------------------------------------------------------------------
/**
 * 指定文字列のみをロード後、内部でアロケートしたメモリにコピーして返す
 *
 * @param   arcID		アーカイブファイルＩＤ
 * @param   datID		アーカイブファイル内のメッセージデータＩＤ
 * @param   msgID		メッセージデータ内の文字列ＩＤ
 * @param   heapID		一時メモリ確保用のヒープＩＤ
 *
 * @retval  STRCODE*	文字列がコピーされたメモリブロック（失敗時はNULL）
 */
//------------------------------------------------------------------
STRCODE* MSGDAT_GetDirectAlloc( u32 arcID, u32 datID, u32 strID, u32 heapID )
{
	ARCHANDLE* arc = ArchiveDataHandleOpen( arcID, heapID );

	if( arc )
	{
		MSGDATA_HEADER   header;
		MSG_PARAM_BLOCK  param;
		STRCODE*  str;
		u32 size;

		ArchiveDataLoadOfsByHandle( arc, datID, 0, sizeof(MSGDATA_HEADER), &header);
		ArchiveDataLoadOfsByHandle( arc, datID, CalcParamBlockOfs(strID), sizeof(MSG_PARAM_BLOCK), &param );
		DecodeParam( &param, strID, header.randValue );

		size = param.len * sizeof(STRCODE);
		str = sys_AllocMemory( heapID, size );
		if( str != NULL )
		{
			ArchiveDataLoadOfsByHandle( arc, datID, param.offset, size, str );
			DecodeStr( str, param.len, strID, header.randValue );
		}
		ArchiveDataHandleClose( arc );
		return str;
	}

	return NULL;
}
//------------------------------------------------------------------
/**
 * コンバートされている文字列を指定のローカルバッファにコピー
 *
 * @param   dst			コピー先バッファ
 * @param   src			コピー元文字列
 * @param   param		コピー元文字列のパラメータ
 *
 */
//------------------------------------------------------------------
static void StrSet( STRCODE* dst, const STRCODE* src, const MSG_PARAM_BLOCK* param )
{
	MI_CpuCopy16( src, dst, param->len*sizeof(STRCODE) );
}


//------------------------------------------------------------------
/**
 * 文字列バッファ型オブジェクトに、指定文字列をコピー
 *
 * @param   msgdat		メッセージデータポインタ
 * @param   strID		文字列ID
 * @param   dst			文字列バッファ型
 *
 */
//------------------------------------------------------------------
void MSGDAT_GetStr( const MSGDATA_HEADER* msgdat, u32 strID, STRBUF* dst )
{
	if( strID < msgdat->numMsgs )
	{
		MSG_PARAM_BLOCK param;
		STRCODE* str;
		u32 size;

		param = msgdat->params[strID];
		DecodeParam( &param, strID, msgdat->randValue );

		size = param.len * sizeof(STRCODE);
		str = sys_AllocMemoryLo( HEAPID_BASE_SYSTEM, size );
		if( str )
		{
			MI_CpuCopy16( (((u8*)msgdat) + param.offset), str, size );
			DecodeStr( str, param.len, strID, msgdat->randValue );
			STRBUF_SetStringCodeOrderLength( dst, str, param.len );
			sys_FreeMemoryEz( str );
		}
	}
	else
	{
		GF_ASSERT_MSG(0, "strID:%d", strID);
		STRBUF_Clear( dst );
	}
}
//------------------------------------------------------------------
/**
 * ロードしたメッセージデータから指定文字列サイズ分のメモリを確保＆コピー
 *
 * @param   msgdat		メッセージデータポインタ
 * @param   strID		文字列ID
 * @param   heapID		メモリ確保用のヒープID
 *
 * @retval  文字列がコピーされた文字列バッファ型オブジェクトへのポインタ
 *
 */
//------------------------------------------------------------------
STRBUF* MSGDAT_GetStrAlloc( const MSGDATA_HEADER* msgdat, u32 strID, u32 heapID )
{
	if( strID < msgdat->numMsgs )
	{
		MSG_PARAM_BLOCK param;
		STRCODE* str;
		u32 size;

		param = msgdat->params[strID];
		DecodeParam( &param, strID, msgdat->randValue );
		size = param.len * sizeof(STRCODE);
		str = sys_AllocMemoryLo( heapID, size );
		if( str )
		{
			STRBUF *dst;

			MI_CpuCopy16( (((u8*)msgdat) + param.offset), str, size );
			DecodeStr( str, param.len, strID, msgdat->randValue );

			dst = STRBUF_Create( param.len, heapID );
			if( dst )
			{
				STRBUF_SetStringCodeOrderLength( dst, str, param.len );
			}
			sys_FreeMemoryEz( str );
			return dst;
		}
		return NULL;
	}
	else
	{
		// 存在しないインデックスの要求が来たら空文字列を返している
		GF_ASSERT_MSG(0, "strID:%d", strID);
		return STRBUF_Create( 4, heapID );
	}
}
//------------------------------------------------------------------
/**
 * 指定文字列のみをロード＆指定バッファにコピー（アーカイブID指定）
 *
 * @param   arcID		アーカイブファイルＩＤ
 * @param   datID		アーカイブファイル内のメッセージデータＩＤ
 * @param   msgID		メッセージデータ内の文字列ＩＤ
 * @param   heapID		一時メモリ確保用のヒープＩＤ
 * @param   dst			文字列コピー先バッファ
 *
 */
//------------------------------------------------------------------
void MSGDAT_GetStrDirect( u32 arcID, u32 datID, u32 strID, u32 heapID, STRBUF* dst )
{
	ARCHANDLE*  arc;

	arc = ArchiveDataHandleOpen(arcID, heapID);
	if( arc )
	{
		MSGDAT_GetStrDirectByHandle( arc, datID, strID, heapID, dst );
		ArchiveDataHandleClose( arc );
	}
}

//------------------------------------------------------------------
/**
 * 指定文字列のみをロード＆指定バッファにコピー（アーカイブハンドル使用）
 *
 * @param   arcHandle	アーカイブハンドル
 * @param   datID		アーカイブファイル内のメッセージデータＩＤ
 * @param   msgID		メッセージデータ内の文字列ＩＤ
 * @param   heapID		一時メモリ確保用のヒープＩＤ
 * @param   dst			文字列コピー先バッファ
 *
 */
//------------------------------------------------------------------
void MSGDAT_GetStrDirectByHandle( ARCHANDLE* arcHandle, u32 datID, u32 strID, u32 heapID, STRBUF* dst )
{
	MSGDATA_HEADER  header;
	MSG_PARAM_BLOCK  param;
	STRCODE*  str;
	u32 size;

	ArchiveDataLoadOfsByHandle( arcHandle, datID, 0, sizeof(MSGDATA_HEADER), &header );

	if( strID < header.numMsgs )
	{
		ArchiveDataLoadOfsByHandle( arcHandle, datID, CalcParamBlockOfs(strID), sizeof(MSG_PARAM_BLOCK), &param );
		DecodeParam( &param, strID, header.randValue );

		size = param.len * sizeof(STRCODE);
		str = sys_AllocMemoryLo( heapID, size );
		if( str )
		{
			ArchiveDataLoadOfsByHandle( arcHandle, datID, param.offset, size, str );
			DecodeStr( str, param.len, strID, header.randValue );
			STRBUF_SetStringCodeOrderLength( dst, str, param.len );
			sys_FreeMemoryEz( str );
		}
	}
	else
	{
		GF_ASSERT_MSG(0, "datID:%d strID:%d", datID, strID);
		STRBUF_Clear( dst );
	}
}


//------------------------------------------------------------------
/**
 * 指定文字列のみをロード後、内部でアロケートしたメモリにコピーして返す
 *（アーカイブID指定）
 *
 * @param   arcID		アーカイブファイルＩＤ
 * @param   datID		アーカイブファイル内のメッセージデータＩＤ
 * @param   msgID		メッセージデータ内の文字列ＩＤ
 * @param   heapID		一時メモリ確保用のヒープＩＤ
 *
 * @retval  文字列がコピーされた文字列バッファ型オブジェクトへのポインタ
 */
//------------------------------------------------------------------
STRBUF* MSGDAT_GetStrDirectAlloc( u32 arcID, u32 datID, u32 strID, u32 heapID )
{
	ARCHANDLE*  arc;
	STRBUF* ret;

	arc = ArchiveDataHandleOpen(arcID, heapID);
	if( arc )
	{
		ret = MSGDAT_GetStrDirectAllocByHandle( arc, datID, strID, heapID );
		ArchiveDataHandleClose( arc );
	}
	else
	{
		ret = STRBUF_Create( 4, heapID );
	}
	return ret;
}

//------------------------------------------------------------------
/**
 * 指定文字列のみをロード後、内部でアロケートしたメモリにコピーして返す
 *（アーカイブハンドル使用）
 *
 * @param   arcHandle	アーカイブハンドル
 * @param   datID		アーカイブファイル内のメッセージデータＩＤ
 * @param   msgID		メッセージデータ内の文字列ＩＤ
 * @param   heapID		一時メモリ確保用のヒープＩＤ
 *
 * @retval  文字列がコピーされた文字列バッファ型オブジェクトへのポインタ
 */
//------------------------------------------------------------------
STRBUF* MSGDAT_GetStrDirectAllocByHandle( ARCHANDLE* arcHandle, u32 datID, u32 strID, u32 heapID )
{
	MSGDATA_HEADER   header;

	ArchiveDataLoadOfsByHandle( arcHandle, datID, 0, sizeof(MSGDATA_HEADER), &header );

	if( strID < header.numMsgs )
	{
		MSG_PARAM_BLOCK  param;
		STRBUF*   dst;

		ArchiveDataLoadOfsByHandle( arcHandle, datID, CalcParamBlockOfs(strID), sizeof(MSG_PARAM_BLOCK), &param );
		DecodeParam( &param, strID, header.randValue );

		dst = STRBUF_Create( param.len, heapID );
		if( dst )
		{
			STRCODE*  str;
			u32 size;

			size = param.len * sizeof(STRCODE);
			str = sys_AllocMemoryLo( heapID, size );
			if( str )
			{
				ArchiveDataLoadOfsByHandle( arcHandle, datID, param.offset, size, str );
				DecodeStr( str, param.len, strID, header.randValue );
				STRBUF_SetStringCodeOrderLength( dst, str, param.len );
				sys_FreeMemoryEz( str );
			}
		}
		return dst;
	}
	else
	{
		// 存在しないインデックスの要求が来たら空文字列を返している
		GF_ASSERT_MSG(0, "datID:%d strID:%d", datID, strID);
		return STRBUF_Create( 4, heapID );
	}
}


//------------------------------------------------------------------
/**
 * ロードしたメッセージデータを基に、格納されているメッセージの数を返す
 *
 * @param   msgdat		メッセージデータポインタ
 *
 * @retval  u32			メッセージ数
 */
//------------------------------------------------------------------
u32 MSGDAT_GetMessageCount( const MSGDATA_HEADER* msgdat )
{
	return msgdat->numMsgs;
}
//------------------------------------------------------------------
/**
 * アーカイブ＆データIDを基に、格納されているメッセージの数を返す
 *
 * @param   arcID		アーカイブID
 * @param   datID		データID
 *
 * @retval  u32			メッセージ数
 */
//------------------------------------------------------------------
u32 MSGDAT_GetMessageCountDirect( u32 arcID, u32 datID )
{
	MSGDATA_HEADER  header;
	ArchiveDataLoadOfs( &header, arcID, datID, 0, sizeof(MSGDATA_HEADER) );
	return header.numMsgs;
}




/*============================================================================================*/
/*                                                                                            */
/*  メッセージデータマネージャ                                                                */
/*                                                                                            */
/*============================================================================================*/


//----------------------------------------------------
/**
 *  マネージャワーク構造体
 */
//----------------------------------------------------
struct _MSGDATA_MANAGER {

	u16		type;
	u16		heapID;
	u16		arcID;
	u16		datID;

	union {
		MSGDATA_HEADER*  msgData;
		ARCHANDLE*       arcHandle;
	};
};



//------------------------------------------------------------------
/**
 * メッセージデータマネージャ作成
 *
 * @param   type		マネージャタイプ指定
 * @param   arcID		メッセージデータの含まれるアーカイブＩＤ
 * @param   datID		メッセージデータ本体のアーカイブ内ＩＤ
 * @param   heapID		メモリ確保用ヒープＩＤ
 *
 * @retval  MSGDATA_MANAGER*		作成したマネージャワークポインタ
 */
//------------------------------------------------------------------
MSGDATA_MANAGER*  MSGMAN_Create( MSGMAN_TYPE type, u32 arcID, u32 datID, u32 heapID )
{
	// マネージャ作成→文字列取得→マネージャ廃棄…の流れが思ったより多そうなので
	// マネージャワークはメモリブロックの後方から取得する
	MSGDATA_MANAGER* man = sys_AllocMemoryLo( heapID, sizeof(MSGDATA_MANAGER) );
	if( man )
	{
		if( type == MSGMAN_TYPE_NORMAL )
		{
			man->msgData = MSGDAT_Load( arcID, datID, heapID );
			if( man->msgData == NULL )
			{
				sys_FreeMemoryEz( man );
				return NULL;
			}
		}
		else
		{
			man->arcHandle = ArchiveDataHandleOpen(arcID, heapID);
		}
		man->type = type;
		man->arcID = arcID;
		man->datID = datID;
		man->heapID = heapID;
	}
	return man;
}
//------------------------------------------------------------------
/**
 * メッセージデータマネージャの破棄
 *
 * @param   man		マネージャワークポインタ
 *
 */
//------------------------------------------------------------------
void MSGMAN_Delete( MSGDATA_MANAGER* man )
{
	if( man )
	{
		switch( man->type ){
		case MSGMAN_TYPE_NORMAL:
			MSGDAT_Unload( man->msgData );
			break;
		case MSGMAN_TYPE_DIRECT:
			ArchiveDataHandleClose( man->arcHandle );
			break;
		}
		sys_FreeMemoryEz( man );
	}
}
//------------------------------------------------------------------
/**
 * メッセージデータマネージャを使って文字列を指定バッファにコピー
 *
 * @param   man			マネージャワークポインタ
 * @param   strID		文字列ＩＤ
 * @param   dst			コピー先バッファポインタ
 *
 */
//------------------------------------------------------------------
void MSGMAN_GetString( const MSGDATA_MANAGER* man, u32 strID, STRBUF* dst )
{
	switch( man->type ){
	case MSGMAN_TYPE_NORMAL:
		MSGDAT_GetStr( man->msgData, strID, dst );
		break;

	case MSGMAN_TYPE_DIRECT:
		MSGDAT_GetStrDirectByHandle( man->arcHandle, man->datID, strID, man->heapID, dst );
		break;
	}
}
//------------------------------------------------------------------
/**
 * メッセージデータマネージャを使って文字列を取得
 *（内部でSTRBUFを作成して返す。作成されたSTRBUFの破棄は各自で行う）
 *
 * @param   man			マネージャワークポインタ
 * @param   strID		文字列ID
 *
 * @retval  STRBUF*		コピー先バッファポインタ
 */
//------------------------------------------------------------------
STRBUF* MSGMAN_AllocString( const MSGDATA_MANAGER* man, u32 strID )
{
	switch( man->type ){
	case MSGMAN_TYPE_NORMAL:
		return MSGDAT_GetStrAlloc( man->msgData, strID, man->heapID );

	case MSGMAN_TYPE_DIRECT:
		return MSGDAT_GetStrDirectAllocByHandle( man->arcHandle, man->datID, strID, man->heapID );
	}
	return NULL;
}

//------------------------------------------------------------------
/**
 * 格納されているメッセージ数を返す
 *
 * @param   man		マネージャワークポインタ
 *
 * @retval  u32		メッセージ数
 */
//------------------------------------------------------------------
u32 MSGMAN_GetMessageCount( const MSGDATA_MANAGER* man )
{
	switch( man->type ){
	case MSGMAN_TYPE_NORMAL:
		return MSGDAT_GetMessageCount( man->msgData );

	case MSGMAN_TYPE_DIRECT:
		return MSGDAT_GetMessageCountDirect( man->arcID, man->datID );
	}
	return 0;
}









//------------------------------------------------------------------
/**
 * ※※　生の文字配列を使用している。いずれ消すので使わないように　※※
 *
 * メッセージデータマネージャを使って文字列を指定バッファにコピー
 */
//------------------------------------------------------------------
void MSGMAN_GetStr( const MSGDATA_MANAGER* man, u32 strID, STRCODE* dst )
{
	switch( man->type ){
	case MSGMAN_TYPE_NORMAL:
		MSGDAT_Get( man->msgData, strID, dst );
		break;

	case MSGMAN_TYPE_DIRECT:
		MSGDAT_GetDirect( man->arcID, man->datID, strID, man->heapID, dst );
		break;
	}
}
//------------------------------------------------------------------
/**
 * ※※　生の文字配列を使用している。いずれ消すので使わないように　※※
 *
 * メッセージデータマネージャを使って文字列を取得
 */
//------------------------------------------------------------------
STRCODE* MSGMAN_GetStrAlloc( const MSGDATA_MANAGER* man, u32 strID )
{
	switch( man->type ){
	case MSGMAN_TYPE_NORMAL:
		return MSGDAT_GetAlloc( man->msgData, strID, man->heapID );

	case MSGMAN_TYPE_DIRECT:
		return MSGDAT_GetDirectAlloc( man->arcID, man->datID, strID, man->heapID );
	}
	return NULL;
}




/*-------------------------------------------------------------------*/
/** ！！ここにこの手の関数をこれ以上追加しないようにお願いします！！ */
/*-------------------------------------------------------------------*/

//------------------------------------------------------------------
/**
 * ポケモン名取得
 *
 * @param   monsno		ポケモンナンバー
 * @param   heapID		一時メモリ確保用のヒープＩＤ
 * @param   dst			文字列コピー先バッファ
 *
 */
//------------------------------------------------------------------
void MSGDAT_MonsNameGet( u32 monsno, u32 heapID, STRCODE* dst )
{
	MSGDATA_MANAGER* man = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_monsname_dat, heapID );
	MSGMAN_GetStr( man, MONSNAME_000+monsno, dst );
	MSGMAN_Delete( man );
}

/*-------------------------------------------------------------------*/
/** ！！ここにこの手の関数をこれ以上追加しないようにお願いします！！ */
/*-------------------------------------------------------------------*/
