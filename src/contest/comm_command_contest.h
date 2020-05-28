//=============================================================================
/**
 * @file	comm_command_contest.h
 * @brief	通信のコマンド一覧  コンテスト用
 * @author	matsuda
 * @date    2005.12.15(木)
 */
//=============================================================================

#ifndef __COMM_COMMAND_CONTEST_H__
#define __COMM_COMMAND_CONTEST_H__

#include "communication/comm_command.h"
#include "poketool/poke_tool.h"


/// バトル専用通信コマンドの定義。
enum CommCommandBattle_e {
  CC_EXIT_CONTEST = CS_COMMAND_MAX, ///<コンテストを終了しフィールドに戻る事を送信

	CC_TIMING_DATA,				///<同期取り用
	CC_NORMAL_DATA,				///<通常データ送信
	CC_DANCE_DATA,				///<ダンス用データ送信
	CC_FAST_PARAM,				///<初回データ送受信
	CC_POKEPARA_DATA,			///<ポケモンパラメータ
	CC_POKEPARA_ALL_DATA,		///<ポケモンパラメータ(全員分)
	CC_BREEDER_DATA,			///<ブリーダーデータ
	CC_JUDGE_DATA,				///<審判データ
	CC_NAME_DATA,				///<ブリーダー名
	CC_IMC_DATA,				///<クリップデータ
	CC_IMC_ALL_DATA,			///<クリップデータ(全員分)
	CC_IMC_LOCAL,				///<イメージクリップ画面用データ送信
	CC_IMC_FORCE_END,			///<イメージクリップ画面用：強制終了フラグ送信
	CC_PERAP_DATA,				///<ぺラップデータ
	CC_ETC_DATA,				///<固定長の細かいデータ群
	
  //------------------------------------------------ここまで
  CC_COMMAND_MAX   // 終端--------------これは移動させないでください
};

extern void CommCommandContestInitialize(void* pWork);


//==============================================================================
//	外部関数宣言
//==============================================================================
extern BOOL CommContestSendFastParam(CONTEST_SYSTEM *consys);
extern BOOL CommContestSendPokePara(CONTEST_SYSTEM *consys, int breeder_no, 
	const POKEMON_PARAM *pp);
extern BOOL CommContestSendPokeParaAll(CONTEST_SYSTEM *consys, POKEMON_PARAM **pp);
extern BOOL CommContestSendBreederData(CONTEST_SYSTEM *consys, int breeder_no, const BREEDER_DATA *bd);
extern BOOL CommContestSendJudgeData(CONTEST_SYSTEM *consys, int breeder_no, const JUDGE_DATA *jd);
extern BOOL CommContestSendNameData(CONTEST_SYSTEM *consys, int breeder_no, const STRBUF *name);
extern BOOL CommContestSendClipData(CONTEST_SYSTEM *consys, int breeder_no, const IMC_CONTEST_SAVEDATA *imc_data);
extern BOOL CommContestSendClipDataAll(CONTEST_SYSTEM *consys, IMC_CONTEST_SAVEDATA **imc_data);
extern BOOL CommContestSendImcLocal(CON_IMC_LOCAL *imc_local, u32 counter);
extern BOOL CommContestSendPerap(CONTEST_SYSTEM *consys, int breeder_no, void *perap_voice);
extern BOOL CommContestSendEtcData(CONTEST_SYSTEM *consys, int breeder_no, const CON_ETC_SIO_DATA *etc_data);
extern BOOL CommContestSendImcForceEnd(CON_IMC_LOCAL *imc_local, int force_end);


#endif// __COMM_COMMAND_CONTEST_H__

