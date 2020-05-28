/**
 *  @file	mail_local.h
 *	@brief	メールセーブデータ制御モジュールのみがincludeして良い
 *	@author	Miyuki Iwasawa
 *	@date	06.03.02
 */

#ifndef __H_MAIL_LOCAL_H__
#define __H_MAIL_LOCAL_H__

#include "savedata/mail.h"

///メールデータセーブデータブロック定義構造体
typedef struct _MAIL_BLOCK{
//	MAIL_DATA	temoti[MAIL_STOCK_TEMOTI];	
	MAIL_DATA	paso[MAIL_STOCK_PASOCOM];
//	MAIL_DATA	extrade[MAIL_STOCK_EXTRADE];
//	MAIL_DATA	sodateya[MAIL_STOCK_SODATEYA];
}_MAIL_BLOCK;

#endif	//__H_MAIL_LOCAL_H__

