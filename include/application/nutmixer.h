/**
 *	@file	nutmixer.h
 *	@brief	ナッツミキサー　外部公開ヘッダ
 *	@author	Miyuki Iwasawa
 *	@date	06.04.06
 */

#ifndef __H_NUTMIXER_H__
#define __H_NUTMIXER_H__

#include "savedata/savedata_def.h"
#include "savedata/poruto_util.h"
#include "savedata/mystatus.h"
#include "system/gamedata.h"
#include "itemtool/myitem.h"
#include "poketool/pokeparty.h"
#include "application/p_status.h"
#include "application/pokelist.h"
#include "savedata/fnote_mem.h"

//ローカルデータ引継ぎ構造体
typedef struct _NUTMIXER_PARAM{
	int	ret_val;	///<返り値
	int	sys_mode;	///<システム動作モード	通信か１人用か

	PORUTO_BLOCK* poruSave;	///<ポルトセーブデータ
	
	SAVEDATA*	SaveData;	///<セーブデータ
	
	MYSTATUS	*mySave;	///<ステータス
	MYITEM		*itemSave;	///<アイテム
	CONFIG		*configSave;	///<コンフィグ
	FNOTE_DATA * fnote;		///<冒険ノート
}NUTMIXER_PARAM;

//オーバーレイプロセス外部参照宣言
extern const PROC_DATA NutMixerProcData;

#endif	//__H_NUTMIXER_H__
