/**
 *	@file	comm_command_nutmixer.h
 *	@brief	ナッツミキサー　通信コマンドテーブル
 *	@author	Miyuki Iwasawa
 *	@date	06.04.06
 *	@data	06.05.23	tomoya 変更
 */

#ifndef __H_COMM_COMMAND_NUTMIXER_H__
#define __H_COMM_COMMAND_NUTMIXER_H__

/// ナッツミキサー専用通信コマンドの定義。
enum CommCommandTradeList_e {

	//-------------------------------------
	//　ゲーム用
	//=====================================
	// 同期用	
	CNM_MIXER_GAME_SYS_START = CS_COMMAND_MAX,	///< ミキサーゲーム開始		親ー＞子
	CNM_MIXER_GAME_END,							///< ゲーム終了				親ー＞子
	
	// データ受信用
	CNM_MIXER_GAME_BEFOREDATA_KO,	///< ゲーム開始前データ	親ー＞子	ゲーム開始同期にもなっている
	CNM_MIXER_GAME_BEFOREDATA,		///< ゲーム開始前データ	子ー＞親
	CNM_MIXER_GAMEDATA,				///< ゲームデータ		親＜ー＞子
	CNM_MIXER_GAME_RESULTDATA,		///< 結果データ			親ー＞子	結果表示同期にもなっている
	CNM_MIXER_PORUTO_DATA,			///< ポルトデータ転送　親ー＞子
	CNM_MIXER_GAME_NEXT_KO,			///< ゲームをつづけるかどうか 親ー＞子
	CNM_MIXER_GAME_NEXT,			///< ゲームをづつけるかどうか 子ー＞親


	//-------------------------------------
	//	
	//=====================================
	
	//------------------------------------------------ここまで
	CNM_COMMAND_MAX   // 終端--------------これは移動させないでください
};

extern const CommPacketTbl* NutMixer_CommCommandTclGet( void );
extern int NutMixer_CommCommandTblNumGet( void );


#endif	//__H_COMM_COMMAND_NUTMIXER_H__
