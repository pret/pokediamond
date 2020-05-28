//==============================================================================================
/**
 * @file	usescript.h
 * @brief	スクリプトで使用するファイルのインクルードなど
 * @author	Satoshi Nohara
 * @date	2005.10.04
 */
//==============================================================================================
#ifndef __USESCRIPT_H__
#define __USESCRIPT_H__

#define	__ASM_NO_DEF_

#define ASM_CPP							//pm_version.h


//==============================================================================================
//
//	
//
//==============================================================================================

//----------------------------------------------------------------------------------------------
//(エメラルドではvmstat.hに定義してあった)
//----------------------------------------------------------------------------------------------
#define	LT				0				/* <	*/
#define	EQ				1				/* ==	*/
#define	GT				2				/* >	*/
#define	LE				3				/* <=	*/
#define	GE				4				/* >=	*/
#define	NE				5				/* !=	*/
#define	EQUAL			EQ
#define	LITTLER			LT
#define	GREATER			GT
#define	LT_EQ			LE
#define	GT_EQ			GE

#define	FLGON			1
#define	FLGOFF			0

//nitro/type.hで定義されているがインクルードできないので自力で定義
#define	TRUE			1
#define	FALSE			0

//スクリプト通信受付の判別定義
#define SCR_COMM_ID_NOTHING	(0)			//何もなし
#define SCR_COMM_ID_BATTLE	(1)			//バトル
#define SCR_COMM_ID_UNION	(2)			//ユニオン
#define SCR_COMM_ID_WIFI	(3)			//WiFi
#define SCR_COMM_ID_RECORD	(4)			//レコード(sp_***.evに埋め込んでしまったので残している)
#define SCR_COMM_ID_CONTEST	(5)			//コンテスト
#define SCR_COMM_ID_GTC		(6)			//GTC

//----------------------------------------------------------------------------------------------
//*.evの中で使用する定義
//----------------------------------------------------------------------------------------------
//スクリプトとプログラムのデータ交換用
#define	SCWK_PARAM0		( 0x8000 )
#define SCWK_PARAM1		( 0x8001 )
#define SCWK_PARAM2		( 0x8002 )
#define SCWK_PARAM3		( 0x8003 )

//スクリプトでのテンポラリ
#define SCWK_TEMP0		( 0x8004 )
#define SCWK_TEMP1		( 0x8005 )
#define SCWK_TEMP2		( 0x8006 )
#define SCWK_TEMP3		( 0x8007 )

//スクリプト内部での処理用
#define SCWK_REG0		( 0x8008 )
#define SCWK_REG1		( 0x8009 )
#define SCWK_REG2		( 0x800a )
#define SCWK_REG3		( 0x800b )

//スクリプトに答えを返す汎用ワーク
#define SCWK_ANSWER		( 0x800c )

//話しかけ対象OBJIDワーク(変更不可)
#define SCWK_TARGET_OBJID	( 0x800d )

/*
	// 話かけた方向を保持するワーク
	u16 TalkSiteWork = 0;

	// 手持ちがいっぱいでＰＣに転送された時
	u16 BoxNoWork = 0;			//何番のBOXか
	u16 PasoNoWork = 0;			//そのBOXの何番目か

	//ユニオンルームでのイベント状態制御用ワーク
	u16 UnionRoomWork = 0;
*/

/*アンノーンいせき*/
#define ANOON_SEE_NUM_1	(10)
#define ANOON_SEE_NUM_2	(26)


//==============================================================================================
//
//	
//
//==============================================================================================
#include "common_scr_def.h"							//共通スクリプトデータID

#include "saveflag.h"								//フラグ、ワーク定義
#include "savework.h"

#include "../../../include/pm_version.h"

//include/field
#include "../../../include/field/evwkdef.h"
#include "../../../include/field/poketch_app_no.h"	//ポケッチアプリナンバー

#include "../../../include/system/brightness.h"		//輝度
#include "../../../include/system/window.h"			//ウィンドウ
#include "../../../include/system/wipe.h"			//ワイプ
#include "../../../include/system/timezone.h"		//時間帯

#include "../../../include/poketool/monsno.h"		//ポケモンナンバー
#include "../../../include/battle/battle_common.h"	//戦闘関連
#include "../../../include/battle/trno_def.h"		//トレーナーナンバー定義

#include "../../../include/application/wifi_p2pmatch_def.h"	//P2P対戦マッチングボード
#include "../../../include/application/imageClip/imc_itemid_define.h"	//イメージクリップ定義
#include "../../../include/application/box_mode.h"	//ボックスモード定義
#include "../../../include/application/bag_def.h"	//ポケット定義
#include "../../../include/application/seal_id.h"	//シール定義
#include "../../../include/contest/contest_def.h"	//コンテスト
#include "../../../include/itemtool/itemsym.h"		//アイテムナンバー定義
#include "../../../include/communication/comm_def.h"//通信

#include "../../../include/battle/wazano_def.h"		//ワザNo

//include/savedata
#include "../../../include/savedata/fnote_mem.h"	//冒険ノート
#include "../../../include/savedata/score_def.h"	//スコア
#include "../../../include/savedata/record.h"	//スコア

//src/field
#include "../../field/script_def.h"					//特殊スクリプト定義
#include "../../field/ev_win.h"						//イベントウィンドウ定義
#include "../../field/comm_union_def.h"				//ユニオン定義
#include "../../field/comm_union_beacon.h"			//ユニオンルーム用ビーコン定義
#include "../../field/comm_direct_counter_def.h"	//通信ダイレクトコーナー
#include "../../field/fieldobj_code.h"				//フィールドOBJで使用するシンボル、コード宣言
#include "../../field/player_code.h"				//REQBIT
#include "../../field/board.h"						//看板
#include "../../field/honey_tree_def.h"				//蜜木ステート定義
#include "../../field/sysflag_def.h"				//システムフラグ定義
#include "../../field/syswork_def.h"				//システムワーク定義
#include "../../field/gym_def.h"					//ジム関連定義
#include "../../field/safari_train_def.h"
#include "../../field/field_trade.h"				//ゲーム内交換

#include "../../data/sound/sound_data.sadl"			//サウンドナンバー定義
#include "../../../include/system/snd_def.h"		//サウンド定義の置き換え定義
#include "../maptable/zone_id.h"					//ゾーンID定義
#include "../shopdata/fs_item_def.h"				//固定アイテムショップ定義
#include "../shopdata/fs_goods_def.h"				//固定グッズショップ定義
#include "../shopdata/fs_seal_def.h"				//固定シールショップ定義

#include "../../field/move_pokemon_def.h"			//移動ポケモン定義
#include "../../field/elevator_anm_def.h"			//エレベータ関連定義
#include "../../field/ship_demo_def.h"				//船デモ関連定義



//ワイプフェードの基本の値
#define SCR_WIPE_DIV				(WIPE_DEF_DIV)
#define SCR_WIPE_SYNC				(WIPE_DEF_SYNC)


//==============================================================================================
//
//	共通メッセージ関連
//
//==============================================================================================
#include "../../../include/msgdata/msg_common_scr.h"
#include "../../../include/msgdata/msg_ev_win.h"
#include "../../../include/msgdata/msg_gameover.h"
//#include "msglist.h"


#endif


