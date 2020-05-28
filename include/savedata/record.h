//============================================================================================
/**
 * @file	record.h
 * @brief
 * @date	2006.03.28
 * @author	tamada/iwasawa
 */
//============================================================================================

#ifndef	__RECORD_H__
#define	__RECORD_H__

#ifndef	__ASM_NO_DEF_

#include "savedata/savedata_def.h"
#include "score_def.h"
#include "savedata/zukanwork.h"

//============================================================================================
//
//	RECORDを操作するのに必要な定義
//
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	RECORDへの不完全型定義
 */
//----------------------------------------------------------
typedef struct RECORD RECORD;

//----------------------------------------------------------
//----------------------------------------------------------
//レコードデータの取得
extern RECORD * SaveData_GetRecord(SAVEDATA * sv);

extern void RECORD_Init(RECORD * rec);
extern int RECORD_GetWorkSize(void);

//----------------------------------------------------------
//----------------------------------------------------------
//値をセットする
extern u32 RECORD_Set(RECORD * rec, int id, u32 value);
//現在の値と比較、大きければ値をセットする
extern u32 RECORD_SetIfLarge(RECORD * rec, int id, u32 value);
//値をインクリメントする
extern u32 RECORD_Inc(RECORD * rec, int id);
//値を取得する
extern u32 RECORD_Get(const RECORD * rec, int id);
//値を足す
extern u32 RECORD_Add(RECORD * rec, int id, u32 add_value);

#ifdef PM_DEBUG
//スコアのセット
extern void RECORD_Score_DebugSet(RECORD * rec, const u32 inScore);
#endif

//----------------------------------------------------------
//----------------------------------------------------------
//スコアの加算処理
extern void RECORD_Score_Add(RECORD * rec, int id);
//スコアを取得する
extern u32 RECORD_Score_Get(const RECORD * rec);
//図鑑スコア加算
extern void RECORD_Score_AddZukanScore(RECORD * rec, const ZUKAN_WORK * zw, u16 const inMonsno);

#endif	//__ASM_NO_DEF_


//============================================================================================
//
//	RECORD各項目の定義
//
//============================================================================================
//----------------------------------------------------------
//----------------------------------------------------------
#define	REC_FIRST		0

/**
 *	@brief	スコア取得指定ID(4byte)
 *
 *	値の加算には必ずRECORD_Score_Add()関数
 *	値の参照には必ずRECORD_Score_Get()関数を使用すること
 *
 *	RECORD_Add()/RECORD_Get()に直接指定して値を更新/参照することは禁止です
*/
#define RECID_SCORE						(REC_FIRST+0)	///<スコア

#define	LARGE_REC_START		1

//以下は、4バイトのカウンタを持つ
#define RECID_REPORT_COUNT				(LARGE_REC_START+0)	///<レポート回数
#define RECID_CLEAR_TIME				(LARGE_REC_START+1)	///<クリアタイム
#define RECID_NUTS_PLANT				(LARGE_REC_START+2)	///<木の実を植えた回数
#define RECID_RIDE_CYCLE				(LARGE_REC_START+3)	///<自転車に乗った回数
#define RECID_WALK_COUNT				(LARGE_REC_START+4)	///<歩数
#define RECID_BATTLE_COUNT				(LARGE_REC_START+5)	///<全戦闘回数
#define RECID_BTL_ENCOUNT				(LARGE_REC_START+6)	///<エンカウント戦闘回数
#define RECID_BTL_TRAINER				(LARGE_REC_START+7)	///<トレーナー戦闘回数

#define	RECID_CAPTURE_POKE				(LARGE_REC_START+8)	///<企画08:捕獲したポケモンの数
#define RECID_FISHING_SUCCESS			(LARGE_REC_START+9)	///<釣りあげたポケモンの回数
#define	RECID_TAMAGO_HATCHING			(LARGE_REC_START+10)	///<企画12:タマゴを孵した回数
#define	RECID_POKE_EVOLUTION			(LARGE_REC_START+11)	///<進化させたポケモンの引数
#define RECID_RECOVERY_PC				(LARGE_REC_START+12)	///<ポケセンで休んだ回数
#define RECID_SLOT_FEAVER				(LARGE_REC_START+13)	///<スロットで大当たりさせた回数
#define RECID_BTOWER_CHALLENGE			(LARGE_REC_START+14)	///<バトルタワーに挑んだ回数
#define RECID_ENTER_MARSHLAND			(LARGE_REC_START+15)	///<湿原に入った回数
#define RECID_WAZA_IAIGIRI				(LARGE_REC_START+16)	///<居合い切りを使った回数
#define RECID_WAZA_IWAKUDAKI			(LARGE_REC_START+17)	///<いわくだきを使った回数

#define RECID_COMM_TRADE				(LARGE_REC_START+18)	///<ワイヤレス通信交換をした回数
#define RECID_COMM_BATTLE				(LARGE_REC_START+19)	///<ワイヤレス通信対戦をした回数
#define RECID_COMM_BTL_WIN				(LARGE_REC_START+20)	///<ワイヤレス通信対戦の勝利数
#define RECID_COMM_BTL_LOSE				(LARGE_REC_START+21)	///<ワイヤレス通信対戦の敗北数
#define RECID_COMM_BTL_DRAW				(LARGE_REC_START+22)	///<ワイヤレス通信対戦の引き分け数

#define RECID_WIFI_TRADE				(LARGE_REC_START+23)	///<WiFi通信交換をした回数
#define RECID_WIFI_BATTLE				(LARGE_REC_START+24)	///<WiFi通信対戦をした回数
#define RECID_WIFI_BTL_WIN				(LARGE_REC_START+25)	///<WiFi通信対戦の勝利数
#define RECID_WIFI_BTL_LOSE				(LARGE_REC_START+26)	///<WiFi通信対戦の敗北数
#define RECID_WIFI_BTL_DRAW				(LARGE_REC_START+27)	///<WiFi通信対戦の引き分け数

#define RECID_BTOWER_WIN				(LARGE_REC_START+28)	///<バトルタワーでの総勝利数(リトライモード以外全て)
#define RECID_NMIXER_PLAY				(LARGE_REC_START+29)	///<まぜまぜ料理を行った回数
#define RECID_NMUSU_PLAY				(LARGE_REC_START+30)	///<むすむす料理を行った回数
#define RECID_PORUTO_COMM				(LARGE_REC_START+31)	///<ポルトをワイヤレス通信で作った回数
#define RECID_PORUTO_EAT				(LARGE_REC_START+32)	///<ポケモンに食べさせたポルトの個数

#define RECID_SHOPPING_CNT				(LARGE_REC_START+33)	///<買い物をした回数
#define RECID_SHOPPING_MONEY			(LARGE_REC_START+34)	///<買い物をした合計金額
#define RECID_POKETCH_CHANGE			(LARGE_REC_START+35)	///<ポケッチの機能を切り替えた回数
#define RECID_ZUKAN_OPEN				(LARGE_REC_START+36)	///<ポケモン図鑑を開いた回数
#define RECID_WATCH_TV					(LARGE_REC_START+37)	///<テレビを見た回数
#define RECID_DANSA_JUMP				(LARGE_REC_START+38)	///<段差を飛び降りた回数
#define RECID_SODATEYA_CNT				(LARGE_REC_START+39)	///<育て屋にポケモンを預けた回数

#define	RECID_KILL_POKE					(LARGE_REC_START+40)	///<企画07:倒したポケモンの数
#define	RECID_DAYMAX_EXP				(LARGE_REC_START+41)	///<企画24:1日に稼いだ経験値
#define	RECID_DAYCNT_EXP				(LARGE_REC_START+42)	///<企画24:1日に稼いだ経験値


#define	LARGE_REC_NUM	(43+LARGE_REC_START)
#define	LARGE_REC_MAX	(LARGE_REC_NUM)	

//以下は、2バイトしかカウンタを持たない
#define	SMALL_REC_START		LARGE_REC_MAX

#define RECID_MAKE_TRAND_CNT			(SMALL_REC_START+0)	///<流行を作った回数
#define RECID_INTERVIEW_CNT				(SMALL_REC_START+1)	///<インタビューに答えた回数
#define RECID_DENDOU_CNT				(SMALL_REC_START+2)	///<殿堂入りした回数
#define RECID_RECOVERY_HOME				(SMALL_REC_START+3)	///<自分の家で休んだ回数
#define RECID_MOVE_MYBASE				(SMALL_REC_START+4)	///<秘密基地を移動した回数

#define RECID_WAZA_HANERU				(SMALL_REC_START+5)	///<「はねる」を使った回数
#define RECID_WAZA_WARUAGAKI			(SMALL_REC_START+6)	///<「わるあがき」を使った回数
#define RECID_WAZA_ZIBAKU				(SMALL_REC_START+7)	///<「じばく」を使った回数
#define RECID_WAZA_DAIBAKUHATU			(SMALL_REC_START+8)	///<「だいばくはつ」を使った回数

#define	RECID_RENSHOU_SINGLE			(SMALL_REC_START+9)	///<タワー:シングルバトル連勝数
#define	RECID_RENSHOU_SINGLE_CNT		(SMALL_REC_START+10)///<タワー:シングルバトル連勝数
#define	RECID_RENSHOU_DOUBLE			(SMALL_REC_START+11)	///<タワー:ダブルバトル連勝数
#define	RECID_RENSHOU_DOUBLE_CNT		(SMALL_REC_START+12)	///<タワー:ダブルバトル連勝数
#define	RECID_RENSHOU_MULTI				(SMALL_REC_START+13)	///<タワー:マルチバトル連勝数
#define	RECID_RENSHOU_MULTI_CNT			(SMALL_REC_START+14)	///<タワー:マルチバトル連勝数
#define	RECID_RENSHOU_COMM_MULTI		(SMALL_REC_START+15)	///<タワー:マルチバトル（通信）連勝数
#define	RECID_RENSHOU_COMM_MULTI_CNT	(SMALL_REC_START+16)	///<タワー:マルチバトル（通信）連勝数
#define	RECID_RENSHOU_WIFI				(SMALL_REC_START+17)	///<タワー:Wi-Fiバトル連勝数
#define	RECID_RENSHOU_WIFI_CNT			(SMALL_REC_START+18)	///<タワー:Wi-Fiバトル連勝数

#define RECID_CONTEST_ENTRY				(SMALL_REC_START+19)	///<コンテストに参加した回数
#define RECID_CONTEST_COMM_ENTRY		(SMALL_REC_START+20)	///<コンテスト(通信)に参加した回数
#define RECID_CONTEST_GPX				(SMALL_REC_START+21)	///<コンテストで優勝した回数
#define RECID_CONTEST_COMM_GPX			(SMALL_REC_START+22)	///<コンテスト(通信)で優勝した回数
#define RECID_CONTEST_RIBBON_GET		(SMALL_REC_START+23)	///<貰ったリボンの個数(コンテスト限定)

#define	RECID_WAZA_MUKOU				(SMALL_REC_START+24)	///<企画14:無効果わざを出した回数
#define	RECID_TEMOTI_KIZETU				(SMALL_REC_START+25)	///<企画15:気絶させた手持ちの引数
#define	RECID_TEMOTI_MAKIZOE			(SMALL_REC_START+26)	///<企画16:味方にダメージを与えた回数
#define	RECID_NIGERU_SIPPAI				(SMALL_REC_START+27)	///<企画17:逃げそこなった回数
#define	RECID_NIGERARETA				(SMALL_REC_START+28)	///<企画18：逃げられたポケモンの数
#define	RECID_FISHING_FAILURE			(SMALL_REC_START+29)	///<企画22:つり損なった回数
#define	RECID_DAYMAX_PORUTO				(SMALL_REC_START+30)	///<企画23:1日にポルトを食べさせた数
#define	RECID_DAYCNT_PORUTO				(SMALL_REC_START+31)	///<企画23:1日にポルトを食べさせた数
#define	RECID_DAYMAX_KILL				(SMALL_REC_START+32)	///<企画25:1日に倒したポケモンの数
#define	RECID_DAYCNT_KILL				(SMALL_REC_START+33)	///<企画25:1日に倒したポケモンの数
#define	RECID_DAYMAX_CAPTURE			(SMALL_REC_START+34)	///<企画26:1日に捕獲したポケモンの数
#define	RECID_DAYCNT_CAPTURE			(SMALL_REC_START+35)	///<企画26:1日に捕獲したポケモンの数
#define	RECID_DAYMAX_TRAINER_BATTLE		(SMALL_REC_START+36)	///<企画27:1日にトレーナー戦した回数
#define	RECID_DAYCNT_TRAINER_BATTLE		(SMALL_REC_START+37)	///<企画27:1日にトレーナー戦した回数
#define	RECID_DAYMAX_EVOLUTION			(SMALL_REC_START+38)	///<企画28:1日にポケモン進化させた回数
#define	RECID_DAYCNT_EVOLUTION			(SMALL_REC_START+39)	///<企画28:1日にポケモン進化させた回数

#define RECID_COMM_SURETIGAI			(SMALL_REC_START+40)	///<すれ違い通信をした回数
#define RECID_NMIXER_TEAMWORK			(SMALL_REC_START+41)	///<まぜまぜ料理チームワーク最高得点


#define	SMALL_REC_NUM	(42+35)	//35箇所分余り
#define	SMALL_REC_MAX	(SMALL_REC_NUM+LARGE_REC_MAX)


#endif	/* __RECORD_H__ */

