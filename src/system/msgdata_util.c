//============================================================================================
/**
 * @file	msgdata_util.c
 * @brief	メッセージデータ関連便利関数
 * @author	taya
 * @date	2005.12.05
 *
 * ポケモン名・ワザ名・アイテム名等、
 * 多くのプログラムから参照され、管理者が曖昧な文字列の取得処理を取り扱う
 *
 *
 */
//============================================================================================
#include "common.h"
#include "system/msgdata_util.h"
#include "system/buflen.h"

#include "msgdata/msg.naix"



//=================================================================================
// 
//=================================================================================
#define  EXPAND_BUFFER_SIZE		(1024)		/// どんな文字列も展開できるであろうサイズ


//------------------------------------------------------------------
/**
 * メッセージデータをタグ展開した文字列バッファを作成して返す。
 * 事前に個別のタグ設定処理を行っておく必要がある。
 * 作成された文字列の解放処理は各自で行う。
 *
 * @param   wordSet		タグが設定された単語セットモジュール
 * @param   msgMan		展開前文字列を管理しているメッセージマネージャ
 * @param   strID		展開前文字列のID
 * @param   heapID		文字列バッファ作成先のヒープID
 *
 * @retval  STRBUF*		作成された文字列バッファ
 */
//------------------------------------------------------------------
STRBUF* MSGDAT_UTIL_AllocExpandString( WORDSET* wordSet, MSGDATA_MANAGER* msgMan, u32 strID, u32 heapID )
{
	STRBUF* retbuf = NULL;
	STRBUF* exbuf;

	exbuf = STRBUF_Create(EXPAND_BUFFER_SIZE, HEAPID_BASE_SYSTEM);
	if(exbuf)
	{
		STRBUF* srcbuf = MSGMAN_AllocString( msgMan, strID );
		if( srcbuf )
		{
			WORDSET_ExpandStr(wordSet, exbuf, srcbuf);
			retbuf = STRBUF_CreateBufferCopy( exbuf, heapID );
			STRBUF_Delete(srcbuf);
		}
		STRBUF_Delete(exbuf);
	}

	return retbuf;
}


//------------------------------------------------------------------
/**
 * ワザ名文字列を、新規に作成した文字列バッファにコピーして返す
 * （文字列バッファの削除は各自で行う）
 *
 * @param   wazaID		ワザＩＤ
 * @param   heapID		ヒープＩＤ
 *
 * @retval  STRBUF*		文字列バッファ（失敗ならNULL)
 */
//------------------------------------------------------------------
STRBUF* MSGDAT_UTIL_GetWazaName( u32 wazaID, u32 heapID )
{
	MSGDATA_MANAGER *man = MSGMAN_Create(MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_wazaname_dat, heapID);
	if( man )
	{
		STRBUF* wazaname = STRBUF_Create(BUFLEN_WAZA_NAME, heapID);
		if( wazaname )
		{
			MSGMAN_GetString(man, wazaID, wazaname);
		}
		MSGMAN_Delete(man);
		return wazaname;
	}
	return NULL;
}


//------------------------------------------------------------------
/**
 * ポケモン名文字列を、新規に作成した文字列バッファにコピーして返す
 * （文字列バッファの削除は各自で行う）
 *
 * @param   monsno		ポケモンナンバー
 * @param   heapID		ヒープＩＤ
 *
 * @retval  STRBUF*		文字列バッファ（失敗ならNULL)
 */
//------------------------------------------------------------------
STRBUF* MSGDAT_UTIL_GetMonsName( u32 monsno, u32 heapID )
{
	MSGDATA_MANAGER* man = MSGMAN_Create( MSGMAN_TYPE_DIRECT, ARC_MSG, NARC_msg_monsname_dat, heapID );
	if( man )
	{
		STRBUF* buf = MSGMAN_AllocString( man, monsno );
		MSGMAN_Delete(man);
		return buf;
	}
	return NULL;
}

