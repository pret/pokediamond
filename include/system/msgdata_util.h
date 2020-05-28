//============================================================================================
/**
 * @file	msgdata_util.h
 * @brief	メッセージデータ関連便利関数
 * @author	taya
 * @date	2005.12.05
 */
//============================================================================================
#ifndef __MSGDATA_UTIL_H__
#define __MSGDATA_UTIL_H__

#include "gflib/strbuf.h"
#include "system/msgdata.h"
#include "system/wordset.h"


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
extern STRBUF* MSGDAT_UTIL_AllocExpandString( WORDSET* wordSet, MSGDATA_MANAGER* msgMan, u32 strID, u32 heapID );


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
extern STRBUF* MSGDAT_UTIL_GetWazaName( u32 wazaID, u32 heapID );


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
extern STRBUF* MSGDAT_UTIL_GetMonsName( u32 monsno, u32 heapID );



#endif
