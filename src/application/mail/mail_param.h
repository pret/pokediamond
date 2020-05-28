/**
 *	@file	mail_param.h
 *	@brief	メールシステム　呼び出し時の引継ぎデータ構造体型定義
 *	@author	Miyuki Iwasawa
 *	@date	06.02.08
 */

#ifndef _H_MAIL_PARAM_H_
#define _H_MAIL_PARAM_H_

#include "savedata/mail_util.h"

typedef struct _MAIL_PARAM{
	u16	mode;		///<メールモジュール呼び出しタイプ
	u16	id;			///<呼び出しID
	
	int	ret_val;	///<戻り値

	int	blockID;
	u16 dataID;
	u8	poke_pos;
	u8	designNo;
	
	SAVEDATA*	savedata;	///<セーブデータの参照ポインタ
	MAIL_DATA*	pDat;	///MAIL_DATAの構築ワーク参照ポインタ
	MAIL_BLOCK* pBlock;
}MAIL_PARAM;

///メールモジュール呼び出しモード
enum{
 MAIL_MODE_VIEW,
 MAIL_MODE_CREATE,
 MAIL_MODE_MAX,
};

#endif	//_H_MAIL_PARAM_H_



