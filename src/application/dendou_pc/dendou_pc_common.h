//============================================================================================
/**
 * @file	dendou_pc_common.h
 * @bfief	殿堂入りパソコン画面
 * @author	taya GAME FREAK inc.
 *
 * @date	2006.04.21
 */
//============================================================================================
#ifndef __DENDOU_PC_COMMON_H__
#define __DENDOU_PC_COMMON_H__

#include "system\gamedata.h"
#include "savedata\dendou_data.h"

#include "dendou_pc_sound.h"

//------------------------------------------------------
/**
 *	描画コマンド
 */
//------------------------------------------------------
enum {
	VCMD_INIT,				///< 画面初期構築＆フェードイン
	VCMD_QUIT,				///< フェードアウト
	VCMD_CHANGE_POKE,		///< 選択ポケモン変更
	VCMD_CHANGE_RECORD,		///< 表示レコード変更
	VCMD_CHANGE_PARAMMODE,	///< パラメータモード変更

	VCMD_MAX,
};

//------------------------------------------------------
/**
 *	パラメータモード
 */
//------------------------------------------------------
typedef enum {
	PARAM_NORMAL,	///< 通常表示
	PARAM_WAZA,		///< わざ名表示
}DendouPC_ParamMode;

//------------------------------------------------------
/**
 *	メインワーク不完全型
 */
//------------------------------------------------------
typedef  struct  _DENDOU_PC_WORK	DENDOU_PC_WORK;

//------------------------------------------------------
/**
 *	描画ワーク不完全型
 */
//------------------------------------------------------
typedef  struct  _DENDOU_PC_VIEW	DENDOU_PC_VIEW;


//------------------------------------------------------
/**
 *	描画用情報
 */
//------------------------------------------------------
typedef struct {
	int			times;				///< 何回目の殿堂入りか
	RTCDate		date;				///< 殿堂入り日付
	int			pokeCount;			///< ポケモン何体いるか
	int			pokePos;			///< 何体目を選んでいるか
	DendouPC_ParamMode	paramMode;	///< パラメータモード
	DENDOU_POKEMON_DATA	pokemon[ TEMOTI_POKEMAX ];	///< ポケモンデータ
}DENDOU_PC_VIEWPARAM;





//--------------------------------------------------------------
// 描画側関数群
//--------------------------------------------------------------
extern DENDOU_PC_VIEW* DendouPCView_CreateWork( DENDOU_PC_WORK* mainWork, const DENDOU_PC_VIEWPARAM* vpara );
extern void DendouPCView_DeleteWork( DENDOU_PC_VIEW* vwk );
extern BOOL DendouPCView_StartCommand( DENDOU_PC_VIEW* vwk, int command );
extern BOOL DendouPCView_WaitCommand( DENDOU_PC_VIEW* vwk );


#endif
