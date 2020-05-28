/**
 *	@file	nmix_gameseq.h
 *	@brief	ナッツミキサー　ゲームシーケンスコマンド定義
 *	@author	Miyuki Iwasawa
 *	@date	06.04.08
 */

#ifndef __H_NMIX_GAMESEQ_H__
#define __H_NMIX_GAMESEQ_H__

// ゲーム内処理シーケンス
enum{
	NMIX_GAME_MIANSEQ_INIT,				// ゲーム基本描画システムの初期化
	NMIX_GAME_MAINSEQ_SYSSTART,			// ゲーム処理の開始	親ー＞子開始命令
	NMIX_GAME_MAINSEQ_SYSSTART_WAIT,	// ゲームシステム開始同期待ち
	NMIX_GAME_MAINSEQ_BEFORE,			// ゲーム開始前処理
	NMIX_GAME_MAINSEQ_BEFORE_WAIT,		// ゲーム開始前処理終了ウエイト
	NMIX_GAME_MAINSEQ_RES_LOAD,			// リソース読み込み
	NMIX_GAME_MAINSEQ_GAMESTART,		// ゲーム開始
	NMIX_GAME_MAINSEQ_GAMEMAIN,			// ゲームメイン
	NMIX_GAME_MAINSEQ_GAMEEND,			// ゲーム破棄処理
	NMIX_GAME_MAINSEQ_RESULT_WAIT,		// ゲームリザルト情報待ち
	NMIX_GAME_MAINSEQ_RESULT,			// ゲームリザルト処理
	NMIX_GAME_MAINSEQ_SYSEND_WAIT,		// ゲーム終了待ち
	NMIX_GAME_MIANSEQ_RES_RELEASE,		// リソース破棄
	NMIX_GAME_MAINSEQ_SYSEND,			// 終了処理
};

#endif	//__H_NMIX_GAMESEQ_H___
