
//============================================================================================
/**
 * @file	fight.h
 * @bfief	戦闘メインプログラム
 * @author	HisashiSogabe
 * @date	05.05.24
 */
//============================================================================================

#ifndef __FIGHT_H_
#define __FIGHT_H_

#include "battle/battle_common.h"
#include "system/procsys.h"

#define	TALK_WIN_CGX_START	(1)			///<会話ウインドウキャラ読み込み先
#define	TALK_WIN_PAL_NO		(10)		///<会話ウインドウパレットナンバー
#define	TALK_MSG_PAL_NO		(11)		///<会話ウインドウ内メッセージパレットナンバー
#define	TALK_MSG_START		(TALK_WIN_CGX_SIZ+1)	///<会話ウインドウ内メッセージキャラスタート位置
#define	TALK_WIN_NO			(0)			///<会話ウインドウNo
#define	TALK_WIN_X			(0x02)		///<会話ウインドウ左上X位置
#define	TALK_WIN_Y			(0x13)		///<会話ウインドウ左上X位置
#define	TALK_WIN_SIZE_X		(27)		///<会話ウインドウXサイズ
#define	TALK_WIN_SIZE_Y		(4)			///<会話ウインドウYサイズ
#define	TALK_PAL_BIT		(0x0c00)	///<会話ウインドウパレットビット

//レベルアップステータスウインドウ
#define	MENU_WIN_CGX_START	(1)			///<メニューウインドウキャラ読み込み先
#define	MENU_WIN_PAL_NO		(8)			///<メニューウインドウパレットナンバー
#define	MENU_MSG_PAL_NO		(11)		///<メニューウインドウ内メッセージパレットナンバー
#define	MENU_MSG_START		(MENU_WIN_CGX_SIZ+1)	   ///<メニューウインドウ内メッセージキャラスタート位置
#define	MENU_WIN_NO			(1)			///<メニューウインドウNo
#define	MENU_WIN_X			(0x11)		///<メニューウインドウ左上X位置
#define	MENU_WIN_Y			(0x07)		///<メニューウインドウ左上X位置
#define	MENU_WIN_SIZE_X		(14)		///<メニューウインドウXサイズ
#define	MENU_WIN_SIZE_Y		(12)		///<メニューウインドウYサイズ

#define	TAG_WIN_NO			(2)			///<タグウインドウNo
#define	TAG_WIN_X			(0x11)		///<メニューウインドウ左上X位置
#define	TAG_WIN_Y			(0x01)		///<メニューウインドウ左上X位置
#define	TAG_WIN_SIZE_X		(14)		///<メニューウインドウXサイズ
#define	TAG_WIN_SIZE_Y		(4)			///<メニューウインドウYサイズ



//戦闘システムブートパラメータ
typedef struct
{
	u8	client_no;
	u8	client_type;
}FIGHT_SYSTEM_BOOT_PARAM;

extern	BOOL	BattleSystemProc(PROC *proc,int *seq);
extern	void	FightScreenTransition(BATTLE_WORK *bw);
extern	void	FightScreenEnd(BATTLE_WORK *bw);
extern	void	FightScreenRecover(BATTLE_WORK *bw);
extern	void	FightScreenPokemonGetEnd(BATTLE_WORK *bw);
extern	void	FightScreenPokemonGet(BATTLE_WORK *bw);

#endif __FIGHT_H_
