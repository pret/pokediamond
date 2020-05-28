//==============================================================================
/**
 * @file	contest.h
 * @brief	コンテストのヘッダ
 * @author	matsuda
 * @date	2005.11.16(水)
 */
//==============================================================================
#ifndef __CONTEST_H__
#define __CONTEST_H__

#include "battle/battle_common.h"
#include "system/buflen.h"
#include "field/field_common.h"
#include "poketool/poke_tool.h"
#include "system/wordset.h"
#include "savedata/mystatus.h"
#include "contest/actin_ex.h"

#include "contest/contest_def.h"

#include "include/application/imageClip/imc_playsys.h"

#include "contest/contest_conv.h"


//--------------------------------------------------------------
//	デバッグ定義
//--------------------------------------------------------------
///処理作成待ち
#define WAIT_FIX		(0)		///<1:作成後、有効。　0:まだ作成してないので無効

#define DEBUG_SIO_WAIT	(0)		///<1:通信用に強制でウェイト入れる

///デバッグメニューからの選択モード
enum{
	DEBUG_CON_VISUAL,
	DEBUG_CON_CLIP_VISUAL,
	DEBUG_CON_DANCE,
	DEBUG_CON_ACTIN,
	DEBUG_CON_RESULT,
//	DEBUG_CON_SIO,
};


//==============================================================================
//	定数定義
//==============================================================================
///コンテストバージョン
#define CONTEST_VERSION			(100)

///コンテストシステム受信バッファサイズ
///(各部門の受信バッファではなくコンテストシステムの受信バッファであることに注意!)
#define CC_RECIEVE_BUF_MAX		(256)

///コンテストの共通で使用するメッセージ終了後のウィンドウを閉じるまでのウェイト(仮) ※check
#define CONTEST_MESSAGE_END_WAIT	0	//(20)

///通信時のメッセージ速度
#define CONTEST_SIO_MSG_SPEED		(1)	//(4)

//--------------------------------------------------------------
//	動作中の部門
//--------------------------------------------------------------
enum{
	CON_CLASS_VISUAL,		///<ビジュアル部門
	CON_CLASS_DANCE,		///<ダンス部門
	CON_CLASS_ACTIN,		///<演技部門
	CON_CLASS_RESULT,		///<結果発表画面
};

//--------------------------------------------------------------
//	ヒープ
//--------------------------------------------------------------
///コンテスト全体システムで使用するヒープサイズ
#define CONTEST_ALLOC_SIZE		(0x3000 + 0x1000)	//+0x1000=ぺラップボイス分追加
///演技力部門で使用するヒープサイズ
#define ACTIN_ALLOC_SIZE		(0x70000)
///ビジュアル部門で使用するヒープサイズ
#define VISUAL_ALLOC_SIZE		(0x70000)
///ダンス部門で使用するヒープサイズ
#define DANCE_ALLOC_SIZE		(0xa0000)
///結果発表で使用するヒープサイズ
#define CONRES_ALLOC_SIZE		(0x70000)

///巨大データ送受信用バッファサイズ
#define CON_HUGEBUF_SIZE		(1024)

///ゲスト審判の最大参加数
#define GUEST_JUDGE_MAX			(1)
///普通の審判の最大参加数
#define NORMAL_JUDGE_MAX		(2)
///審判の最大参加数
#define JUDGE_MAX				(GUEST_JUDGE_MAX + NORMAL_JUDGE_MAX)

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///AP値ハートアクターの最大数
#define APP_HEART_MAX				(6)
///AP値のハートが1つで持っているポイント数
#define APP_APPEAL_ICON_ONE_POINT		(10)

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///OBJパレット：PFD管理本数(パレット単位)
#define CONTEST_MAIN_OBJPAL_NUM				(16 - 2)	//-2 = 通信アイコン＋ローカライズ用
///OBJパレット：PFD管理本数(カラー単位)
#define CONTEST_MAIN_OBJPAL_COLOR_NUM		(CONTEST_MAIN_OBJPAL_NUM * 16)
///OBJパレット：バイトサイズ
#define CONTEST_MAIN_OBJPAL_SIZE			(CONTEST_MAIN_OBJPAL_COLOR_NUM * sizeof(u16))
///OBJパレット：フェードbit
#define CONTEST_MAIN_OBJPAL_FADEBIT			(0x3fff)

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///カメラのフラッシュエフェクトのEVY値
#define CON_CAMERA_FLASH_EVY			(4)	//12
///カメラのフラッシュエフェクトにかけるフレーム数
#define CON_CAMERA_FLASH_FRAME			(6)


//==============================================================================
//	構造体定義
//==============================================================================

///送信用の固定長の細かいデータ群
typedef struct{
	u8 player_sex;		///<プレイヤーの性別
	u8 character;		///<性格
	u8 popularity;		///<人気
	u16 obj_code;		///<OBJコード
}CON_ETC_SIO_DATA;

//--------------------------------------------------------------
/**
 * コンテスト用イメージクリップ関連をまとめた構造体
 */
//--------------------------------------------------------------
typedef struct{
	IMC_PLAYERSYS_PTR imc_ptr;	///<イメージクリッププレイヤーシステムへのポインタ
	int x;						///<座標X
	int y;						///<座標Y(足元座標)
	int z;						///<座標Z
}CONTEST_IMC_WORK;

//--------------------------------------------------------------
/**
 * CON_IMC_LOCAL構造体内の通信送受信データ類
 *
 * この中身が全て送受信されます
 */
//--------------------------------------------------------------
typedef struct{
	//-- 送受信で使われるバッファ --//
	u32 counter;			///<カウントダウン受信用バッファ
	
	//-- 送信のみに使われるバッファ --//
	u8 force_end;			///<強制終了フラグ(TRUE:強制終了)
}CON_IMC_LOCAL_SIO;

//--------------------------------------------------------------
/**
 * イメージクリップ内で使用するワーク類(コンテストシステムで持っておく必要のある物のみ)
 * 基本的に通信用です。
 * 送受信するのはCON_IMC_LOCAL_SIO構造体のデータのみです。
 */
//--------------------------------------------------------------
typedef struct{
	CON_IMC_LOCAL_SIO recieve_sio;		///<受信バッファ
	CON_IMC_LOCAL_SIO trans_sio;		///<送信バッファ

	//-- マシン毎の個別の受信用バッファ --//
	u8 recieve_force_end[BREEDER_MAX];	///<強制終了フラグ(TRUE:強制終了)

	//-- システム的なデータ類 --//
	u8 server_no;				///<サーバーのnetID
	u8 my_net_id;				///<自分のnetID
	u8 sio_flag;				///<通信フラグ TRUE 通信中
	u8 player_num;				///<プレイヤー人数

//	u8 dummy[1];	///<4バイト境界オフセット
}CON_IMC_LOCAL;

//--------------------------------------------------------------
/**
 * コンテストの各部門で取得した得点
 */
//--------------------------------------------------------------
typedef struct{
	s16 bp;				///<ブリーダーポイント(ポロックで得られる”けづや”等)
	s16 clip;			///<クリップポイント
	s16 dance;			///<ダンス部門で獲得したポイント
	s16 actin;			///<演技力部門で獲得したポイント
	
	u8 final_ranking;	///<最終的な順位
	
	u8 dummy[3];
}CONTEST_SCORE;

//--------------------------------------------------------------
/**
 * @brief   コンテスト:ゲーム進行パラメータ
 *
 * コンテストを進行する為のパラメータが入っています。
 * 通信時はサーバーから子機はデータを受け取る事になります。
 */
//--------------------------------------------------------------
typedef struct{
	POKEMON_PARAM *pp[BREEDER_MAX];	///<出場するブリーダーのポケモンデータ
	BREEDER_DATA bd[BREEDER_MAX];	///<ブリーダーデータ
	JUDGE_DATA jd[JUDGE_MAX];		///<審判データ
	STRBUF *breeder_name_str[BREEDER_MAX];	///<ブリーダー名(プレイヤー名)
	IMC_CONTEST_SAVEDATA *imc_data[BREEDER_MAX];	///<各ブリーダーのクリップデータ
	
	u8 player_sex[BREEDER_MAX];		///<ブリーダーの性別
	u8 character[BREEDER_MAX];		///<ブリーダーの性格
	u8 popularity[BREEDER_MAX];		///<ブリーダーの人気
	u16 obj_code[BREEDER_MAX];		///<OBJコード
	
	u8 server_no;					///<サーバーのブリーダー番号
	u8 server_version;				///<サーバーのコンテストバージョン
	u8 special_judge_no;			///<凄い審査が出来る審査員のNo
	
	//-- ここから下は自分で取得可能なデータ。上は通信で貰うデータ --//
	u8 type;						///<CONTYPE_???
	u8 rank;						///<CONRANK_???
	u8 mode;						///<CONMODE_???
	u8 theme;						///<CON_IMAGE_THEME_???
	u8 my_breeder_no;				///<自分のブリーダー番号
	u8 my_net_id;					///<自分のnetID
	u8 my_version;					///<自分のコンテストバージョン
	u8 cpu_num;						///<CPUの数
	u8 player_num;					///<プレイヤーの数

	//-- 得点：サーバーのみ計算して保持。子機は基本的に持っていない。 --//
	//-- 結果発表後に結果として、親から送られてきます --//
	//-- (イベントで順位や得点を使用するだろうから --//
	CONTEST_SCORE score[BREEDER_MAX];	///<各部門で獲得した得点
	
}CONTEST_GAME_PARAM;

///カメラのフラッシュ制御ワーク：スクリプト上で使用
typedef struct{
	TCB_PTR tcb;
	const u8 *wait_tbl;		///<フラッシュのウェイトテーブルへのポインタ
	s16 wait;
	u8 count;
	u8 seq;
	u8 breeder_no;
}CONSCR_CAMERA_FLASH;

//--------------------------------------------------------------
/**
 * @brief   コンテストシステムワーク
 *
 * コンテスト全体の進行を管理する為のワークです。
 * 各マシン毎に個別に作成されます。
 */
//--------------------------------------------------------------
typedef struct{
	CONTEST_GAME_PARAM c_game;		///<コンテスト：ゲーム進行パラメータ
	POKEPARTY *poke_party;			///<手持ちポケモンの構造体
	void *perap_voice[BREEDER_MAX];	///<ぺラップの鳴き声データへのポインタ
	void *class_proc;				///<現在の部門の管理ワークへのポインタ
	u8 class_flag;					///<現在実行中の部門(CON_CLASS_???)
	u8 sio_flag;					///<TRUE：通信中
	u8 actin_sort[BREEDER_MAX];		///<演技力部門開始時の並び順
	
	u8 seq;
	int work;
	int wait;
	TCB_PTR sio_tcb;
	
	//通信の送受信バッファ
	u8 recieve_buf[CC_NETID_MAX][CC_RECIEVE_BUF_MAX];	///<受信バッファ
	u8 recieve_count;				///<受信データを受け取った人数をカウント
	u8 huge_buf[CON_HUGEBUF_SIZE];				///<巨大データ送信用バッファ
	u8 recieve_huge_buf[CC_NETID_MAX][CON_HUGEBUF_SIZE];		///<巨大データ受信用バッファ
	
	//コンフィグ
	const CONFIG *config;		///<コンフィグデータへのポインタ
	//セーブデータ
	SAVEDATA *sv;				///<セーブデータへのポインタ
	POKEMON_PARAM *my_pp;		///<出場させる自分の手持ちポケモンへのポインタ(フィールド上の)
								///<最後にリボンなどをセットさせる為に持っています。
	const MYSTATUS *my_status;	///<マイステータスへのポインタ
	u8 temoti_pos;				///<出場させるポケモンの手持ち位置
	u8 hof_flag;				///<殿堂入りフラグ
	u8 zenkoku_zukan_flag;		///<全国図鑑フラグ
	
	//イメージクリップ画面用(コンテスト内部では使用しません)
	IMC_SAVEDATA *imc_save;		///<イメージクリップのセーブデータへのポインタ
	CON_IMC_LOCAL imc_local;	///<イメージクリップ内で使用するワーク
	void *icpw;					///<イメージクリップ画面構成用初期化データへのポインタ
	
	//スクリプト上で使用するワーク
	CONSCR_CAMERA_FLASH *conscr_flash;		///<カメラのフラッシュ制御ワーク
	
	//ランダムの種退避用ワーク
	u32 push_random_seed;		///<イベント進行時のランダムの種退避用ワーク
}CONTEST_SYSTEM;


//--------------------------------------------------------------
/**
 * @brief   コンテストシステム作成初期データ
 */
//--------------------------------------------------------------
typedef struct{
	u8 type;							///<CONTYPE_???
	u8 rank;							///<CONRANK_???
	u8 mode;							///<CONMODE_???
	u8 hof_flag;						///<殿堂入りフラグ(TRUE:殿堂入りしている)
	u8 zenkoku_zukan_flag;				///<全国図鑑入手フラグ(TRUE:入手している)
	u8 temoti_pos;				///<出場させるポケモンの手持ち位置
	POKEMON_PARAM *my_pp;				///<出場させる自分の手持ちポケモンへのポインタ
	const STRBUF *player_name_str;		///<プレイヤー名へのポインタ
	const MYSTATUS *my_status;			///<マイステータスへのポインタ
	IMC_SAVEDATA *imc_save;				///<イメージクリップセーブデータワークへのポインタ
	const CONFIG *config;				///<コンフィグへのポインタ
	SAVEDATA *sv;						///<セーブデータへのポインタ
	void *perap_voice;					///<ぺラップボイスへのポインタ
}CONTEST_INIT_DATA;



//==============================================================================
//	外部関数宣言
//==============================================================================
extern u16 contest_rand(CONTEST_SYSTEM *consys);
extern u16 contest_fix_rand(u32 seed, u32 *new_seed);
extern CONTEST_SYSTEM * Contest_SystemCreate(const CONTEST_INIT_DATA *cid);
extern void Contest_SystemExit(CONTEST_SYSTEM *consys);
extern void ConScr_JudgeNameGet(CONTEST_SYSTEM *consys, int judge_no, 
	WORDSET *wordset, u32 buf_id);
extern void ConScr_BreederNameGet(CONTEST_SYSTEM *consys, int entry_no, WORDSET *wordset, 
	u32 buf_id);
extern void ConScr_NickNameGet(CONTEST_SYSTEM *consys, int entry_no, WORDSET *wordset, u32 buf_id);
extern void ConScr_RankNameGet(CONTEST_SYSTEM *consys, WORDSET *wordset, u32 buf_id);
extern void ConScr_TypeNameGet(CONTEST_SYSTEM *consys, WORDSET *wordset, u32 buf_id);
extern void ConScr_VictoryBreederNameGet(CONTEST_SYSTEM *consys, WORDSET *wordset, u32 buf_id);
extern u32 ConScr_VictoryItemNoGet(CONTEST_SYSTEM *consys);
extern BOOL Contest_SioParamInitSet(CONTEST_SYSTEM *consys);
extern BOOL Contest_SioFastDataEndCheck(CONTEST_SYSTEM *consys);
extern void EventCmd_ContestProc(GMEVENT_CONTROL * event, CONTEST_SYSTEM *consys);
extern void ConScr_SioTimingSend(CONTEST_SYSTEM *consys, u8 timing_no);
extern BOOL ConScr_SioTimingCheck(CONTEST_SYSTEM *consys, u8 timing_no);
extern int ConScr_RankingCheck(CONTEST_SYSTEM *consys);
extern void ConScr_EndParamSet(CONTEST_SYSTEM *consys, SAVEDATA *sv, u32 place_id, 
	FNOTE_DATA *f_note);
extern void ConScr_VictoryNickNameGet(CONTEST_SYSTEM *consys, WORDSET *wordset, u32 buf_id);
extern int ConScr_VictoryEntryNoGet(CONTEST_SYSTEM *consys);
extern int ConScr_MyEntryNoGet(CONTEST_SYSTEM *consys);
extern int ConScr_OBJCodeGet(CONTEST_SYSTEM *consys, int entry_no);
extern int ConScr_PopularityGet(CONTEST_SYSTEM *consys, int entry_no);
extern int ConScr_DeskModeGet(CONTEST_SYSTEM *consys);
extern void ConScr_MsgPrintFlagSet(CONTEST_SYSTEM *consys);
extern void ConScr_MsgPrintFlagReset(CONTEST_SYSTEM *consys);
extern void ConScr_FlashTaskCreate(CONTEST_SYSTEM *consys, int entry_no);
extern BOOL ConScr_FlashTaskCheck(CONTEST_SYSTEM *consys);
extern void ConScr_VictoryParamGet(CONTEST_SYSTEM *consys, 
	int *victory_entry, int *sio_flag, int *cpu_flag, int *tutorial, int *practice);
extern void ConScr_EntryParamGet(CONTEST_SYSTEM *consys, u16 *rank, u16 *type, u16 *mode, 
	u16 *temoti_pos);
extern BOOL ConScr_HaveRibbonCheck(CONTEST_SYSTEM *consys);
extern void ConScr_RibbonItemNameGet(CONTEST_SYSTEM *consys, WORDSET *wordset, 
	u32 buf_id, int heap_id);
extern u32 ConScr_AcceNoGet(CONTEST_SYSTEM *consys);

//-- con_record.c --//
extern void * ContestSioRecord_Create( void * fsys );
extern void ContestSioRecord_Delete(void *con_rec);
extern void EventCmd_ConRecordDisp(GMEVENT_CONTROL *event);

//-- con_tool.c --//
extern void ConTool_MsgPrintFlagSet(int sio_flag);
extern void ConTool_MsgPrintFlagReset(void);

//-- con_battle.c --//
extern BOOL ContestPokeFlipCheck(u32 monsno);


#ifdef PM_DEBUG
extern void DebugContest_FieldConnectStart(FIELDSYS_WORK *fsys, int debug_mode);
#endif


#endif	//__CONTEST_H__

