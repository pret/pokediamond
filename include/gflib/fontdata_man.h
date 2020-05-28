//=============================================================================================
/**
 * @file	fontdata_man.c
 * @brief	フォントデータマネージャ
 * @author	taya
 * @date	2005.09.14
 *
 * @li	ntrfont.exe で作成したフォントデータを管理するマネージャ
 */
//=============================================================================================
#ifndef __FONTDATA_MAN_H__
#define __FONTDATA_MAN_H__


#include "fontdata_loadtype.h"

typedef struct _GF_FONTDATA_MAN  GF_FONTDATA_MAN;


//==============================================================================================
/**
 * フォントデータマネージャ作成
 *
 * @param   arcID			フォントデータが格納されているアーカイブID
 * @param   datID			フォントデータが格納されているアーカイブ内ファイルID
 * @param   loadType		フォントデータの読み出し方式
 * @param   fixedFontFlag	TRUEなら等幅フォントとして扱う
 * @param   heapID			マネージャ作成先ヒープID
 *
 * @retval  GF_FONTDATA_MAN*	フォントデータマネージャポインタ
 *
 * @li  loadType が FONTDATA_LOADTYPE_ON_MEMORY の場合、マネージャと同じヒープ領域にフォントデータを読み込む
 */
//==============================================================================================
extern GF_FONTDATA_MAN* FontDataMan_Create( u32 arcID, u32 datID, FONTDATA_LOADTYPE loadType, BOOL fixedFontFlag, u32 heapID );


//==============================================================================================
/**
 * フォントデータマネージャ削除
 *
 * @param   wk		フォントデータマネージャのポインタ
 *
 */
//==============================================================================================
extern void FontDataMan_Delete( GF_FONTDATA_MAN* wk );


//==============================================================================================
/**
 * フォントビットデータの読み込みタイプを変更する
 *
 * @param   wk			フォントデータマネージャポインタ
 * @param   loadType	変更後の読み込みタイプ
 *
 */
//==============================================================================================
extern void FontDataMan_ChangeLoadType( GF_FONTDATA_MAN* wk, FONTDATA_LOADTYPE loadType, u32 heapID );


//------------------------------------------------------------------
/*
 *	文字ビットマップデータ取得
 *
 * @param	wk			フォントデータマネージャ
 * @param	fcode		文字コード
 * @param	dst			ビットマップ取得ワーク
 *
 */
//------------------------------------------------------------------
extern void FontDataMan_GetBitmap( const GF_FONTDATA_MAN* wk, STRCODE fcode, MSG_FONT_DATA* dst );


//------------------------------------------------------------------
/**
 * 文字列をビットマップ化した時の長さ（ドット）を計算して返す
 *
 * @param   wk		フォントデータマネージャ
 * @param   str		文字列
 * @param   margin	字間（ドット）
 *
 * @retval  u32		長さ
 */
//------------------------------------------------------------------
extern u32 FontDataMan_GetStrWidth( const GF_FONTDATA_MAN* wk, const STRCODE* str, u32 margin );

#endif
