
//============================================================================================
/**
 * @file	client_def.h
 * @bfief	戦闘クライアントプログラム
 * @author	HisashiSogabe
 * @date	05.05.24
 */
//============================================================================================

#ifndef __CLIENT_DEF_H_
#define __CLIENT_DEF_H_

#include	"system/softsprite.h"
#include	"gauge.h"
#include 	"client_types.h"

///<クライアント用ユーザインターフェース構造体宣言
typedef struct
{
	TCB_FUNC	UI_CommandSelect;		///<コマンド選択
	TCB_FUNC	UI_WazaSelect;			///<技選択
	TCB_FUNC	UI_DirSelect;			///<攻撃対象選択
	TCB_FUNC	UI_ItemSelect;			///<アイテム選択
	TCB_FUNC	UI_PokemonSelect;		///<ポケモン選択
	TCB_FUNC	UI_YesNoSelect;			///<Yes/No選択
}USER_INTERFACE;

///<クライアント用パラメータ構造体宣言
struct client_param
{
	USER_INTERFACE	ui;
	CATS_ACT_PTR	cap;
	SOFT_SPRITE		*tr_ss;
	SOFT_SPRITE		*poke_ss;
	GF_BGL_BMPWIN	*win;
	GAUGE_WORK		gauge;		///<HPゲージ
	CURSOR_SAVE		cursor_save;
	BMS_PTR			bms;
	OAM_DROP_SYS*	ods;		///< OAM 変換
	void			*time_icon;					//通信待機メッセージタイマーアイコン用タスク
	u8				client_buffer[BUF_SIZE];
	u8				client_no;
	u8				client_type;
	u8				client_boot;
	u8				bip_flag;
	
	TCB_PTR			sin_tcb;	///<選択中のポケモンの揺れ制御タスク
	u16				sin_sec;	///<選択中のポケモンの揺れ：秒

	int				migawari_flag;
};

#endif __CLIENT_DEF_H_
