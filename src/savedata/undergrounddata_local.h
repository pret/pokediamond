//============================================================================================
/**
 * @file	undergrounditem_local.h
 * @brief	地下データヘッダー(このディレクトリのみでのみ参照可)
 * @author	k.ohno
 * @date	2006.2.23
 */
//============================================================================================

#ifndef __UNDERGROUNDDATA_LOCAL_H__
#define __UNDERGROUNDDATA_LOCAL_H__

//============================================================================================

#include "savedata/undergrounddata.h"


//----------------------------------------------------------
/**
 * @brief	地下ステータスデータ型定義
 */
//----------------------------------------------------------

typedef struct _SB_GOODS SB_GOODS;
typedef struct _SB_LOCK SB_LOCK;
typedef struct _SECRETBASEDATA SECRETBASEDATA;

struct _SB_GOODS {
  u8 x;       // グッズの位置 セクション内単位
  u8 z;
  u8 type;    // グッズの種類  パソコンのデーターンデックスになるかも
};

struct _SB_LOCK {
  u8 x;   // 岩の位置 セクション内単位   
  u8 z;
};

struct _SB_RECORD_DATA {
    u32 pointCount:20;        // ちかポイント
    u32 talkCount:20;         // であった人の人数
    u32 sendItemCount:20;     // 道具をあげた回数
    u32 flagConquerCount:20;  // ハタをとった回数
    u32 stoneCount:20;        // タマを掘った回数
    u32 fossilCount:20;       // 化石を掘った回数
    u32 treasureCount:20;     // 宝を掘った回数
    u32 trapConquerCount:20;  // トラップをかけた回数
    u32 trapTumbleCount:20;   // トラップにかかった回数
    u32 trapRescueCount:20;   // 人を助けた回数
    u32 itemRecvCount:20;     // 道具をもらった回数
    u32 flagStealCount:20;    // 旗をとられた回数
    u32 flagReverseCount:20;  // 旗を取り返した回数
    u32 relocateCount:20;     // 引っ越しした回数
    u32 flagDeliveryCount:20; // 旗を納品した回数
};

//----------------------------------------------------------
/**
 * @brief	地下ステータスデータ型定義
 */
//----------------------------------------------------------
struct _SECRETBASEDATA {
  SB_GOODS goodsPos[SECRETBASE_GOODS_NUM_MAX];
  SB_LOCK rockPos[SECRETBASE_LOCK_NUM_MAX];
  SB_RECORD_DATA recordData;
  u16 xpos;         // ドアの位置
  u16 zpos;
  u8 dir;        // 外に出てるドアの方向
  u8 bMake;     //  作ったかどうか
};


//----------------------------------------------------------
/**
 * @brief	各データの許す範囲
 */
//----------------------------------------------------------
#define _GOODS_TYPE_NUM_MAX   (150)    // グッズの最大

#define _PCPOS_X (15)
#define _PCPOS_Z (12)

#define _INVALID_POS  (0)

#define _MAX  (999999)   // レコード値の最大

#define _MAX_WALK_COUNT (100)

// グッズの受け渡しとペナルティー関連
#define _GOODS_SEND_NONE  (0)
#define _GOODS_SEND_UNDERIN  (1)
#define _GOODS_SEND_NOT  (2)
#define _PENALTY_TIME (24*60)

// 地上アイテム入手での連動
#define _ITEM_KONGOUDAMA_BIT (1)
#define _ITEM_SIRATAMA_BIT (2)

//----------------------------------------------------------
/**
 * @brief	地下ステータスデータ型定義
 */
//----------------------------------------------------------

struct _UNDERGROUND_DATA {
  SECRETBASEDATA base;
  u32 randSeed;                     //グッズ親父の売り物決定乱数の種
  s32 sendGoodsMinTimer;   // グッズ受け渡し抑制のタイマー
  u8 sendGoodsSaveInfo;   // 地下のセーブ状態フラグ
  u8 groundStoneGetBit;   //地上でこんごうだま、ましろだまを入手した時のBIT
  //-------------旗関連
  u32 id[UG_FLAG_NUM_MAX];						// 持ち主のID
  STRCODE name[UG_FLAG_NUM_MAX][PERSON_NAME_SIZE + EOM_SIZE];		// 持ち主の名前
  u8 region_code[UG_FLAG_NUM_MAX];	      			// 国コード
  u8 rom_code[UG_FLAG_NUM_MAX];	      			// ROMコード
  u8 newFlagNo;
  //--------------旗関連
  u8 groundNatureTrapType[UG_NATURETRAP_PLACE_NUM_MAX];
  u8 groundNatureTrapPos[UG_NATURETRAP_PLACE_NUM_MAX][3];
  u8 groundFossilPos[UG_FOSSIL_PLACE_NUM_MAX][3];
  u8 groundTrapType[UG_TRAP_PLACE_NUM_MAX];
  u8 groundTrapPos[UG_TRAP_PLACE_NUM_MAX][3];
  u8 groundTrapOrder[UG_TRAP_PLACE_NUM_MAX];
  u8 groundStoneType[UG_STONE_PLACE_NUM_MAX];
  u8 groundStoneCaratAdd[UG_STONE_PLACE_NUM_MAX];
  u8 groundStoneCarat[UG_STONE_PLACE_NUM_MAX];
  u8 groundStonePos[UG_STONE_PLACE_NUM_MAX][3];
  u8 groundStoneDummy[UG_STONE_PLACE_NUM_MAX-12];
  //------化石関連
  u32 digBit;  // プレートを掘ったかどうかの管理
  u8 pcGoods[UG_ITEM_PC_NUM_MAX];
  u8 bagTrap[UG_ITEM_BAG_NUM_MAX];
  u8 bagGoods[UG_ITEM_BAG_NUM_MAX];
  u8 bagTreasure[UG_ITEM_BAG_NUM_MAX];
  u8 bagStone[UG_ITEM_BAG_NUM_MAX];
  u8 bagStoneCarat[UG_ITEM_BAG_NUM_MAX];
  u8 secretBasePlace[SECRETBASE_GOODS_NUM_MAX]; // 秘密基地に配置したパソコンのGOODSの pcGood index+1が入る
  u8 walk;   // 歩いた歩数 100歩でリセット
  u8 bNewDay:4;  // このBITがTRUEなら化石配置換えを地下に入った時に実行
  u8 bFossilFirst:4;  // このBITがFALSEなら初回
};


//============================================================================================

#endif //__UNDERGROUNDDATA_LOCAL_H__

