/**
 *	@file	poruto_name.c
 *	@brief	ポルトの種類名を取得するツール群
 *	@author	Miyuki Iwasawa
 *	@date	06.02.28
 */

#ifndef __H_PORUTO_NAME_H__
#define __H_PORUTO_NAME_H__

#include "gflib/msg_print.h"
#include "gflib/bg_system.h"
#include "system/msgdata.h"
#include "savedata/poruto_def.h"

///ポルト名取得マネージャー型
typedef struct _PORUTO_NAME_MAN{
	MSGDATA_MANAGER* pMsgMan;
	STRBUF	*name[PORUTO_FLAVOR_MAX];	
}PORUTO_NAME_MAN;

/**
 *	@brief	ポルト名取得マネージャ作成
 *
 *	＊利用し終わったら必ず PorutoName_ReleaseManager()を呼び出して
 *	　領域を開放してください
 */
extern PORUTO_NAME_MAN* PorutoName_CreateManager(int heapID);

/**
 *	@brief	ポルト名取得マネージャ解放
 */
extern void PorutoName_ReleaseManager(PORUTO_NAME_MAN* man);

/**
 *	@brief	ポルトフレバーIDから名前文字列を取得(マネージャ指定版)
 *
 *	＊PORUTO_NAME_STRLEN (10)+EOM_サイズ分のバッファを確保する必要有り
 *	　BUFLEN_PORUTO_NAMEを使用しても良い
 */
extern void PorutoName_GetNameStrByMan(PORUTO_NAME_MAN* man,PORUTO_FLAVORID id,STRBUF* buf);

/**
 *	@brief	ポルトフレバーIDから名前文字列を取得(マネージャ内STRBUF*を取得)
 *
 *	＊マネージャワーク内に確保されているSTRBUF領域へのポインタを返す
 *	　参照は可だが編集は不可！
 */
extern const STRBUF* PorutoName_GetNameAdrByMan(PORUTO_NAME_MAN* man,PORUTO_FLAVORID id);

/**
 *	@brief　ポルトフレバーIDから名前文字列を取得(使い捨て)
 */
extern void PorutoName_GetNameStrInst(PORUTO_FLAVORID id,STRBUF* buf,int heapID);

/**
 *
 *	@brief　ポルトフレバーIDから名前文字列を取得(使い捨て/メモリ取得版)
 *	
 *	＊STRBUFにメモリを取得して返すので、解放は自分で行うこと！
 */
extern STRBUF* PorutoName_AllocNameStrInst(PORUTO_FLAVORID id,int heapID);

/**
 *	@brief	ポルトフレバーIDから名前文字列を取得(マネージャ指定/メモリ取得版)
 *
 *	＊STRBUFにメモリを確保して返すので、解放は自分でやること！
 */
extern STRBUF* PorutoName_AllocNameStrByMan(PORUTO_NAME_MAN* man,PORUTO_FLAVORID id,int heapID);

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
extern void PorutoName_WriteByMan(PORUTO_NAME_MAN* man,PORUTO_FLAVORID id,
	GF_BGL_BMPWIN *win,u8 font,u8 ofsx,u8 ofsy,u8 wait,GF_PRINTCOLOR col,void* call_back );

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
extern void PorutoName_WriteInst(PORUTO_FLAVORID id,int heapID,GF_BGL_BMPWIN *win,
		u8 font,u8 ofsx,u8 ofsy,u8 wait,GF_PRINTCOLOR col,void* call_back );






#endif	//__H_PORUTO_NAME_H__
