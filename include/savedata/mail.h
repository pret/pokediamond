/**
 *	@file	mail.h
 *	@brief	メールセーブデータ構造定義　グローバルヘッダ
 *	@date	06.01.12
 *	@author	Miyuki Iwasawa
 *
 *	＊データ実体を定義する箇所以外で参照してはいけません
 *	仮想ポインタ経由でデータアクセスできれば良い箇所では
 *	savedata/mail_util.hをincludeしてください
 */

#ifndef __MAIL_H__
#define __MAIL_H__

#include "system/gamedata.h"
//#include "system/buflen.h"
#include "system/pm_str.h"
#include "system/pms_data.h"

///定数定義
#include "savedata/mail_def.h"
///メールデータ型
//=============================================================
//	外部公開していますが、直接構造体メンバへアクセスすることは
//	許可していません。
//
//	メンバアクセスはsavedata/mail_util.hに定義された
//	アクセス系関数を介してください
//
//  size=56byte
//
//  構造体サイズを4byte境界に合わせるため、MAIL_ICON配列要素数に+1して
//  パディングを行っています
//=============================================================
typedef struct _MAIL_DATA{
	u32	writerID;	//<トレーナーID 4
	u8	sex;	//<主人公の性別 1
	u8	region;	//<国コード 1
	u8	version;	//<カセットバージョン 1
	u8	design;	//<デザインナンバー 1
	STRCODE name[PERSON_NAME_SIZE+EOM_SIZE]; // 16
	MAIL_ICON	icon[MAILDAT_ICONMAX+1];	//<アイコンNO格納場所[](3+1<padding>) 6+2=8
	PMS_DATA	msg[MAILDAT_MSGMAX];	//<文章データ
}_MAIL_DATA;


//=============================================================
/**
 *	メールデータアクセス系関数
 */
//=============================================================
#include "savedata/mail_util.h"
#endif	//__H_MAIL_H__

