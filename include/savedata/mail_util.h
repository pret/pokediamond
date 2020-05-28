/**
 *	@file	mail_util.h
 *	@brief	メールデータ参照用不完全型定義＆ユーティリティ関数定義
 *	@author	MiyukiIwasawa
 *	@date	06.02.09
 */

#ifndef __H_MAIL_UTIL_H__
#define __H_MAIL_UTIL_H__

///定数定義
#include "savedata/mail_def.h"

#include "savedata/savedata_def.h"
#include "system/pm_str.h"
#include "system/pms_data.h"

//------------------------------------------------------------
/**
 * @brief	メールセーブデータブロック管理構造への不完全型ポインタ
 *
 * 中身は見えないけどポインタ経由で参照はできる
 */
//------------------------------------------------------------
typedef struct _MAIL_BLOCK MAIL_BLOCK;

//------------------------------------------------------------
/**
 * @brief	メールデータ管理構造への不完全型ポインタ
 *
 * 中身は見えないけどポインタ経由で参照はできる
 */
//------------------------------------------------------------
typedef struct _MAIL_DATA MAIL_DATA;

/**
 *	@brief	空いているメールデータIDを取得
 *
 *	@param	id 追加したいメールブロックID
 *
 *	@return	int	データを追加できる場合は参照ID
 *				追加できない場合はマイナス値が返る
 */
extern int MAIL_SearchNullID(MAIL_BLOCK* block,MAILBLOCK_ID id);

/**
 *	@brief	メールデータを削除
 *
 *	@param	blockID	ブロックのID
 *	@param	dataID	データID
 */
extern void MAIL_DelMailData(MAIL_BLOCK* block,MAILBLOCK_ID blockID,int dataID);

/**
 *	@brief	メールデータをセーブブロックに追加
 *
 *	＊引き渡したMAIL_DATA構造体型データの中身がセーブデータに反映されるので
 *	　おかしなデータを入れないように注意！
 */
extern void MAIL_AddMailFormWork(MAIL_BLOCK* block,
		MAILBLOCK_ID blockID,int dataID,MAIL_DATA* src);


//=============================================================
/**
 *	メールセーブデータブロックアクセス系関数
 */
//=============================================================
//
/**
 *	@brief	セーブデータブロックへのポインタを取得
 */
extern MAIL_BLOCK* SaveData_GetMailBlock(SAVEDATA* sv);

/**
 *	@brief	メールセーブデータブロックサイズ取得
 *
 *	＊メールデータ一通のサイズではないので注意！
 */
extern int MAIL_GetBlockWorkSize(void);

/**
 *	@brief	メールセーブデータブロック初期化
 */
extern void MAIL_Init(MAIL_BLOCK* dat);

/**
 *	@brief	空いているメールデータIDを取得
 *
 *	@param	id 追加したいメールブロックID
 *
 *	@return	int	データを追加できる場合は参照ID
 *				追加できない場合はマイナス値が返る
 */
extern int MAIL_SearchNullID(MAIL_BLOCK* block,MAILBLOCK_ID id);

/**
 *	@brief	メールデータを削除
 *
 *	@param	blockID	ブロックのID
 *	@param	dataID	データID
 */
extern void MAIL_DelMailData(MAIL_BLOCK* block,MAILBLOCK_ID blockID,int dataID);

/**
 *	@brief	メールデータをセーブブロックに追加
 *
 *	＊引き渡したMAIL_DATA構造体型データの中身がセーブデータに反映されるので
 *	　おかしなデータを入れないように注意！
 */
extern void MAIL_AddMailFormWork(MAIL_BLOCK* block,MAILBLOCK_ID blockID,int dataID,MAIL_DATA* src);

/**
 *	@brief	指定ブロックに有効データがいくつあるか返す
 */
extern int MAIL_GetEnableDataNum(MAIL_BLOCK* block,MAILBLOCK_ID blockID);

/**
 *	@brief	メールデータのコピーを取得
 *
 *	＊内部でメモリを確保するので、呼び出し側が責任持って領域を開放すること
 */
extern MAIL_DATA* MAIL_AllocMailData(MAIL_BLOCK* block,MAILBLOCK_ID blockID,int dataID,int heapID);

/**
 *	@brief	メールデータのコピーを取得
 *
 *	＊あらかじめ確保したMAIL_DATA型メモリにセーブデータをコピーして取得
 */
extern void MAIL_GetMailData(MAIL_BLOCK* block,MAILBLOCK_ID blockID,int dataID,MAIL_DATA* dest);


//=============================================================
/**
 *	メールデータアクセス系関数
 */
//=============================================================
/**
 *	@brief	メールデータサイズ取得
 *
 *	＊メールデータ一通のサイズ
 */
extern int MailData_GetDataWorkSize(void);

/**
 *	@brief	メールデータクリア(初期データセット)
 */
extern void MailData_Clear(MAIL_DATA* dat);

/**
 *	@brief	メールデータが有効かどうか返す
 *	@retval	FALSE	無効
 *	@retval	TRUE	有効
 */
extern BOOL MailData_IsEnable(MAIL_DATA* dat);

/**
 *	@brief	メールデータのワークを取得して返す
 *
 *	＊呼び出し側が責任もって解放すること
 *	
 */
extern MAIL_DATA* MailData_CreateWork(int heapID);

/**
 *	@brief	メールデータの構造体コピー
 */
extern void MailData_Copy(MAIL_DATA* src,MAIL_DATA* dest);

/**
 *	@brief	デザインNo,持たせるポケモンのポジション、セーブデータを指定して
 *			メールデータを新規作成状態に初期化
 *	@param	dat	データを作成するMAIL_DATA構造体型へのポインタ
 *	@param	design_no	メールのイメージNo
 *	@param	pos		メールを持たせるポケモンの手持ち内のポジション
 *	@param	save	セーブデータへのポインタ
 */
extern void MailData_CreateFromSaveData(MAIL_DATA* dat,u8 design_no,u8 pos,SAVEDATA* save);

/**
 *	@brief	メールデータ　トレーナーIDアクセス
 */
extern u32	MailData_GetWriterID(const MAIL_DATA* dat);
extern void MailData_SetWriterID(MAIL_DATA* dat,u32 id);

/**
 *	@brief	メールデータ　ライター名アクセス
 */
extern STRCODE* MailData_GetWriterName(MAIL_DATA* dat);
extern void MailData_SetWriterName(MAIL_DATA* dat,STRCODE* name);

/**
 *	@brief	メールデータ　ライターの性別アクセス
 */
extern u8	MailData_GetWriterSex(const MAIL_DATA* dat);
extern void MailData_SetWriterSex(MAIL_DATA* dat,const u8 sex);

/**
 *	@brief	メールデータ　デザインNoアクセス
 */
extern u8	MailData_GetDesignNo(const MAIL_DATA* dat);
extern void MailData_SetDesignNo(MAIL_DATA* dat,const u8 design);

/**
 *	@brief	メールデータ　国コードアクセス
 */
extern u8	MailData_GetCountryCode(const MAIL_DATA* dat);
extern void MailData_SetCountryCode(MAIL_DATA* dat,const u8 code);

/**
 *	@brief	メールデータ　カセットバージョンアクセス
 */
extern u8	MailData_GetCasetteVersion(const MAIL_DATA* dat);
extern void MailData_SetCasetteVersion(MAIL_DATA* dat,const u8 version);

/**
 *	@brief	メールデータ　メールアイコンパラメータの取得(インデックス指定版)
 *
 *	@param	mode	MAIL_ICONPRM_CGX:cgxNoの取得
 *					MAIL_ICONPRM_PLT:pltNoの取得
 *					MAIL_ICONPRM_ALL:u16型(MAIL_ICON型へキャスト可)で双方の値を返す
 *
 *	＊アイコンCgxIDとモンスターNoは同一ではありません。注意！
 */
extern u16	MailData_GetIconParamByIndex(const MAIL_DATA* dat,u8 index,u8 mode);
extern void MailData_SetIconParamByIndex(MAIL_DATA* dat,u16 id,u8 index,u8 mode);

/**
 *	@brief	メールデータ　メールアイコンデータの取得(インデックス指定版)
 *
 *	@param	index	データ取得開始インデックスNo(index<MAILDAT_ICONMAX)
 *	@param	pi		データ格納場所へのポインタ
 *	@param	num		データ取得数
 *	
 *	＊アイコンNoとモンスターNoは同一ではありません。注意！
 *	＊インデックスが不正だった場合、NULLアイコンデータを格納して返します
 */
extern void MailData_GetIconArray(MAIL_DATA* dat,u8 index,MAIL_ICON* pi,u8 num);


/**
 *	@brief	メールデータ　簡易文取得(インデックス指定版)
 */
extern PMS_DATA*	MailData_GetMsgByIndex(MAIL_DATA* dat,u8 index);
extern void MailData_SetMsgByIndex(MAIL_DATA* dat,PMS_DATA* pms,u8 index);

/**
 *	@brief	メールデータ　簡易文文字列取得(インデックス指定)
 *
 *	@param	dat	MAIL_DATA*
 *	@param	index	簡易文インデックス
 *	@param	buf		取得した文字列ポインタの格納場所
 *
 *	@retval	FALSE	文字列の取得に失敗(または簡易文が有効なデータではない)
 *	
 *	@li	bufに対して内部でメモリを確保しているので、呼び出し側が明示的に解放すること
 *	@li	FALSEが返った場合、bufはNULLクリアされる
 */
extern BOOL MailData_GetMsgStrByIndex(const MAIL_DATA* dat,u8 index,STRBUF* buf,int heapID);

#endif	//__H_MAIL_UTIL_H__


