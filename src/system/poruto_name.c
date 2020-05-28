/**
 *	@file	poruto_name.c
 *	@brief	ポルトの種類名を取得する
 *	@author	Miyuki Iwasawa
 *	@date	06.02.28
 */

#include "common.h"
#include "gflib/strbuf.h"
#include "system/buflen.h"
#include "system/pm_str.h"
#include "msgdata/msg.naix"
#include "msgdata/msg_porutoname.h"

#include "system/poruto_name.h"

/**
 *	@brief	ポルト名取得マネージャ作成
 *
 *	＊利用し終わったら必ず PorutoName_ReleaseManager()を呼び出して
 *	　領域を開放してください
 */
PORUTO_NAME_MAN* PorutoName_CreateManager(int heapID)
{
	PORUTO_NAME_MAN *man;
	int i;
	
	man = sys_AllocMemory(heapID,sizeof(PORUTO_NAME_MAN));
	MI_CpuClear8(man,sizeof(PORUTO_NAME_MAN));

	man->pMsgMan = MSGMAN_Create(MSGMAN_TYPE_NORMAL,ARC_MSG,
			NARC_msg_porutoname_dat,heapID);

	//ポルト名を取得しておく
	for(i = 0;i < PORUTO_FLAVOR_MAX;i++){
		man->name[i] = STRBUF_Create(BUFLEN_PORUTO_NAME,heapID);
		MSGMAN_GetString(man->pMsgMan,i,man->name[i]);
	}
	return man;
}

/**
 *	@brief	ポルト名取得マネージャ解放
 */
void PorutoName_ReleaseManager(PORUTO_NAME_MAN* man)
{
	int i;

	for(i = (PORUTO_FLAVOR_MAX-1);i >= 0;i--){
		STRBUF_Delete(man->name[i]);
	}
	MSGMAN_Delete(man->pMsgMan);

	sys_FreeMemoryEz(man);
}

/**
 *	@brief	ポルトフレバーIDから名前文字列を取得(マネージャ指定版)
 *
 *	＊予めPORUTO_NAME_STRLEN (20)+EOM_サイズ分のバッファを確保した
 *	  STRBUFデータへのポインタを渡す必要がある
 *	　長さ指定にはBUFLEN_PORUTO_NAMEを使用しても良い
 */
void PorutoName_GetNameStrByMan(PORUTO_NAME_MAN* man,PORUTO_FLAVORID id,STRBUF* buf)
{
	STRBUF_Clear(buf);
	MSGMAN_GetString(man->pMsgMan,id,buf);
}

/**
 *	@brief	ポルトフレバーIDから名前文字列を取得(マネージャ内STRBUF*を取得)
 *
 *	＊マネージャワーク内に確保されているSTRBUF領域へのポインタを返す
 *	　参照は可だが編集は不可！
 */
const STRBUF* PorutoName_GetNameAdrByMan(PORUTO_NAME_MAN* man,PORUTO_FLAVORID id)
{
	return (const STRBUF*)man->name[id];
}

/**
 *	@brief	ポルトフレバーIDから名前文字列を取得(マネージャ指定/メモリ取得版)
 *
 *	＊STRBUFにメモリを確保して返すので、解放は自分でやること！
 */
STRBUF* PorutoName_AllocNameStrByMan(PORUTO_NAME_MAN* man,PORUTO_FLAVORID id,int heapID)
{
	return STRBUF_CreateBufferCopy(man->name[id],heapID);
}

/**
 *	@brief　ポルトフレバーIDから名前文字列を取得(使い捨て)
 *	
 *	＊予めPORUTO_NAME_STRLEN (20)+EOM_サイズ分のバッファを確保した
 *	  STRBUFデータへのポインタを渡す必要がある
 */
void PorutoName_GetNameStrInst(PORUTO_FLAVORID id,STRBUF* buf,int heapID)
{
	MSGDATA_MANAGER *man;

	man = MSGMAN_Create(MSGMAN_TYPE_NORMAL,ARC_MSG,
			NARC_msg_porutoname_dat,heapID);
	
	STRBUF_Clear(buf);
	MSGMAN_GetString(man,id,buf);

	MSGMAN_Delete(man);
}

/**
 *	@brief　ポルトフレバーIDから名前文字列を取得(使い捨て/メモリ取得版)
 *	
 *	＊STRBUFにメモリを取得して返すので、解放は自分で行うこと！
 */
STRBUF* PorutoName_AllocNameStrInst(PORUTO_FLAVORID id,int heapID)
{
	MSGDATA_MANAGER *man;
	STRBUF* buf;
	
	man = MSGMAN_Create(MSGMAN_TYPE_NORMAL,ARC_MSG,
			NARC_msg_porutoname_dat,heapID);
	
	buf = STRBUF_Create(BUFLEN_PORUTO_NAME,heapID);
	MSGMAN_GetString(man,id,buf);

	STRBUF_Delete(buf);
	MSGMAN_Delete(man);

	return buf;
}

/**
 *	@brief	ポルトフレバーIDを指定して名前文字列を描画(マネージャ指定版)
 *
 * @param	win			BMPウィンドウデータ
 * @param	fnt_index	使用文字ヘッダINDEX(msg_print.h 参照)
 * @param	x			ウインドウ内表示開始Xオフセット
 * @param	y			ウインドウ内表示開始Yオフセット
 * @param	wait		文字描画ウェイト
 * @param	call_back	文字描画ごとのコールバック関数
 *
 * @return	メッセージインデックス
 *
 * call_back 設定に関して、この関数からの引数は 
 *   MSG_PRINT_HEADER 構造体(msg_print.h を参照)ポインタ
 * となる
 *
 * wait 設定は
 *   MSG_NOTRANS	ディスプレイ転送なし
 *　 MSG_ALL		ディスプレイ一括転送
 *   1 ～			１文字ごとの転送ウェイト値
 * で指定(msg_print.h 定義)
 */
void PorutoName_WriteByMan(PORUTO_NAME_MAN* man,PORUTO_FLAVORID id,
	GF_BGL_BMPWIN *win,u8 font,u8 ofsx,u8 ofsy,u8 wait,GF_PRINTCOLOR col,void* call_back )
{
	GF_STR_PrintColor(	win,font,man->name[id],
						ofsx,ofsy,
						wait,col,call_back);
}

/**
 *	@brief	ポルトフレバーIDを指定して名前文字列を描画(使い捨て)
 *
 * @param	win			BMPウィンドウデータ
 * @param	fnt_index	使用文字ヘッダINDEX(msg_print.h 参照)
 * @param	x			ウインドウ内表示開始Xオフセット
 * @param	y			ウインドウ内表示開始Yオフセット
 * @param	wait		文字描画ウェイト
 * @param	call_back	文字描画ごとのコールバック関数
 *
 * @return	メッセージインデックス
 *
 * call_back 設定に関して、この関数からの引数は 
 *   MSG_PRINT_HEADER 構造体(msg_print.h を参照)ポインタ
 * となる
 *
 * wait 設定は
 *   MSG_NOTRANS	ディスプレイ転送なし
 *　 MSG_ALL		ディスプレイ一括転送
 *   1 ～			１文字ごとの転送ウェイト値
 * で指定(msg_print.h 定義)
 */
void PorutoName_WriteInst(PORUTO_FLAVORID id,int heapID,GF_BGL_BMPWIN *win,
		u8 font,u8 ofsx,u8 ofsy,u8 wait,GF_PRINTCOLOR col,void* call_back )
{
	STRBUF *buf;
	MSGDATA_MANAGER *man;

	man = MSGMAN_Create(MSGMAN_TYPE_NORMAL,ARC_MSG,
			NARC_msg_porutoname_dat,heapID);
	

	buf = STRBUF_Create(BUFLEN_PORUTO_NAME,heapID);
	MSGMAN_GetString(man,id,buf);
	
	GF_STR_PrintColor(	win,font,buf,
						ofsx,ofsy,
						wait,col,call_back);

	STRBUF_Delete(buf);
	MSGMAN_Delete(man);
}
