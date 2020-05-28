//============================================================================================
/**
 * @file	msgdata.h
 * @brief	各種メッセージデータ取り扱い
 * @author	taya
 * @date	2005.09.26
 */
//============================================================================================
#ifndef __MSGDATA_H__
#define __MSGDATA_H__

#include "gflib\strbuf.h"
#include "system\arc_tool.h"




/*==========================================================================================*/
/*
 *	■メッセージデータの構造
 *
 *    複数のメッセージデータファイルがまとめられた【アーカイブ】が一番大きな単位です。
 *    これは nnsarc で作成した通常のアーカイブファイルです。
 *    メッセージデータは必ずアーカイブして使います。
 *
 *
 *    【アーカイブ】の中にはいくつかの【メッセージデータ】がまとめられています。
 *    これは MessageEditor のデータをコンバートしたもので、ＧＦ独自仕様です。
 *
 *
 *    さらに【メッセージデータ】の中にはいくつかの【文字列】が存在します。
 *    つまりアプリケーションから必要な【文字列】を取得するためには、
 *    アーカイブＩＤ，メッセージデータＩＤ、文字列ＩＤの３つのキーが必要ということになります。
 *
 *
 *	■メッセージデータの取り扱い方法
 *
 *    メッセージデータの取り扱いインターフェイスは２種類あります。
 *
 *    Ａ．【メッセージデータ】全体をRAM上にロードしておき、そこから必要に応じて
 *        【文字列】をローカルのバッファにコピーして使う。
 *          不要になったら【メッセージデータ】を破棄する。
 *
 *    Ｂ．【文字列】が必要になるたびに、その【文字列】だけをRAM上にロードする。
 *         ローカルバッファにコピーしたら即座にロード領域は破棄する。
 *
 *    Ａ方式だと、沢山の【文字列】からなる【メッセージデータ】を取り扱う場合に、
 *    たかだか数10バイト程度の【文字列】が欲しいだけなのに、数千バイトの【メッセージデータ】を
 *    ロードすることになる可能性があります。
 *
 *   （例えば全ポケモン名が１つの【メッセージデータ】になっている場合、１文字２バイトなので
 *     大ざっぱに500体分とすると 500 * 5 * 2 で 5000 バイト。ローカライズ時にポケモン名が
 *     倍に伸びれば10000バイトです）
 *
 *    場合によっては、それほど贅沢にメモリを使えないケースというのもあるかもしれません。
 *    その場合はＢ方式を使ってください。
 *
 *    ただしこちらは文字列取得のたびにファイルリード、メモリ確保＆解放を行うので、
 *    多くの【文字列】を取得する場合には実行速度が犠牲になります。
 *
 *
 *	■メッセージデータマネージャについて
 *
 *    上記Ａ・Ｂのインターフェイス差を吸収し、アプリレベルでの修正を簡単にするための
 *    マネージャを用意しました。このマネージャを介してメッセージデータを取り扱うことで、
 *    Ａ方式からＢ方式に変えたい（あるいはその逆）という場合に、アプリケーションプロ
 *    グラム自体をほぼ変更せずに実現できます。詳細はマネージャ関数の説明をご覧ください。
 *
 *
/*==========================================================================================*/




//----------------------------------------------------
/**
 *  マネージャタイプ定義
 */
//----------------------------------------------------
typedef enum {
	MSGMAN_TYPE_NORMAL,		///< Ａ方式。RAM上に必要なデータを保持し続けるので高速だがメモリを食う。
	MSGMAN_TYPE_DIRECT,		///< Ｂ方式。文字列取得ごとに必要最低限だけメモリ確保＆解放。省メモリだが遅い。
}MSGMAN_TYPE;

//----------------------------------------------------
/**
 *  マネージャワーク構造体の型宣言
 */
//----------------------------------------------------
typedef struct _MSGDATA_MANAGER	MSGDATA_MANAGER;

//------------------------------------------------------------------
/**
 * メッセージデータマネージャ作成
 *
 * ※方式を変えたい場合、この関数の type 引数を変えるだけで良い。
 *
 *
 * @param   type		マネージャタイプ指定
 * @param   arcID		メッセージデータの含まれるアーカイブＩＤ
 * @param   datID		メッセージデータ本体のアーカイブ内ＩＤ
 * @param   heapID		メモリ確保用ヒープＩＤ
 *
 * @retval  MSGDATA_MANAGER*		作成したマネージャワークポインタ
 */
//------------------------------------------------------------------
extern MSGDATA_MANAGER*  MSGMAN_Create( MSGMAN_TYPE type, u32 arcID, u32 datID, u32 heapID );


//------------------------------------------------------------------
/**
 * メッセージデータマネージャの破棄
 *
 * @param   man		マネージャワークポインタ
 *
 */
//------------------------------------------------------------------
extern void MSGMAN_Delete( MSGDATA_MANAGER* man );



//------------------------------------------------------------------
/**
 * メッセージデータマネージャを使って文字列を取得
 * （指定バッファにコピー）
 *
 * @param   man		マネージャワークポインタ
 * @param   strID	文字列ＩＤ
 * @param   dst		文字列コピー先バッファ
 *
 */
//------------------------------------------------------------------
extern void MSGMAN_GetString( const MSGDATA_MANAGER* man, u32 strID, STRBUF* dst );


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
extern	STRBUF* MSGMAN_AllocString( const MSGDATA_MANAGER* man, u32 strID );


//------------------------------------------------------------------
/**
 * 格納されているメッセージ数を返す
 *
 * @param   man		マネージャワークポインタ
 *
 * @retval  u32		メッセージ数
 */
//------------------------------------------------------------------
extern u32 MSGMAN_GetMessageCount( const MSGDATA_MANAGER* man );






//------------------------------------------------------
/**
 *  メッセージデータヘッダ
 */
//------------------------------------------------------
typedef struct _MSGDATA_HEADER	MSGDATA_HEADER;


extern MSGDATA_HEADER* MSGDAT_Load( u32 arcID, u32 datID, u32 heapID );
extern void MSGDAT_Unload( MSGDATA_HEADER* msgdat );
extern void MSGDAT_GetStr( const MSGDATA_HEADER* msgdat, u32 strID, STRBUF* dst );
extern STRBUF* MSGDAT_GetStrAlloc( const MSGDATA_HEADER* msgdat, u32 strID, u32 heapID );
extern void MSGDAT_GetStrDirect( u32 arcID, u32 datID, u32 strID, u32 heapID, STRBUF* dst );
extern STRBUF* MSGDAT_GetStrDirectAlloc( u32 arcID, u32 datID, u32 strID, u32 heapID );
extern u32 MSGDAT_GetMessageCount( const MSGDATA_HEADER* msgdat );
extern u32 MSGDAT_GetMessageCountDirect( u32 arcID, u32 datID );
extern STRBUF* MSGDAT_GetStrDirectAllocByHandle( ARCHANDLE* arcHandle, u32 datID, u32 strID, u32 heapID );
extern void MSGDAT_GetStrDirectByHandle( ARCHANDLE* arcHandle, u32 datID, u32 strID, u32 heapID, STRBUF* dst );


//====================================================================================
// ↓こいつらは旧版。いずれ消すので使わないでね
//====================================================================================
extern void MSGMAN_GetStr( const MSGDATA_MANAGER* man, u32 strID, STRCODE* dst );
extern STRCODE* MSGMAN_GetStrAlloc( const MSGDATA_MANAGER* man, u32 strID );
extern void MSGDAT_Get( const MSGDATA_HEADER* msgdat, u32 strID, STRCODE* dst );
extern STRCODE* MSGDAT_GetAlloc( const MSGDATA_HEADER* msgdat, u32 strID, u32 heapID );
extern void MSGDAT_GetDirect( u32 arcID, u32 datID, u32 strID, u32 heapID, STRCODE* dst );
extern STRCODE* MSGDAT_GetDirectAlloc( u32 arcID, u32 datID, u32 strID, u32 heapID );
extern STRCODE* MSGMAN_GetStrAlloc( const MSGDATA_MANAGER* man, u32 strID );
extern void MSGDAT_MonsNameGet( u32 monsno, u32 heapID, STRCODE* dst );


#endif
