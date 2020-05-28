//============================================================================================
/**
 * @file	undergrounddata.h
 * @brief	地下アイテムアクセス用ヘッダ
 * @author	k.ohno
 * @date	2006.2.23
 */
//============================================================================================
#ifndef __UNDERGROUNDDATA_H__
#define __UNDERGROUNDDATA_H__

#include "system/savedata_def.h"	//SAVEDATA参照のため

#include "gflib/msg_print.h"		//STRCODE参照のため
#include "gflib/strbuf.h"			//STRBUF参照のため
#include "savedata/mystatus.h"			//MYSTATUS参照のため


//----------------------------------------------------------
/**
 * @brief	秘密基地データ型定義
 */
//----------------------------------------------------------
typedef struct _SECRETBASEDATA SECRETBASEDATA;
typedef struct _SB_RECORD_DATA SB_RECORD_DATA;

#define SECRETBASE_PC_NUM_MAX   (1) // パソコンの最大数
#define SECRETBASE_GOODS_NUM_MAX   (15) // グッズの最大数
#define SECRETBASE_LOCK_NUM_MAX   (16)  // 岩の最大数
#define SECRETBASE_SETUPOBJ_NUM_MAX (SECRETBASE_GOODS_NUM_MAX + SECRETBASE_LOCK_NUM_MAX + SECRETBASE_PC_NUM_MAX)
#define SECRETBASE_GOODS_ROCK   (6)     // 岩のタイプ番号
#define SECRETBASE_PC_INDEX_NO  (0)    // パソコンのインデックス番号

#include "undergrounddata_def.h"


typedef enum {
  GOODS_INVALID = 0,
  GOODS_FLAG_NORMAL_PC,
  GOODS_FLAG_BRONZE_PC,
  GOODS_FLAG_SILVER_PC,
  GOODS_FLAG_GOLD_PC,
  GOODS_FLAG_PLATINA_PC,
  GOODS_BIG_ROCK,
};


typedef enum {  // 地下ポイントでもらえる称号
  UG_RANK_BEGINNER,
/*  UG_RANK_RANGER6,
  UG_RANK_RANGER5,
  UG_RANK_RANGER4,
  UG_RANK_RANGER3,
  UG_RANK_RANGER2,
  UG_RANK_RANGER1,
  UG_RANK_VETERAN,
  UG_RANK_EXPERT,
  UG_RANK_ELITE,
  UG_RANK_CHANPION, */
  UG_RANK_MASTER,
};

//============================================================================================
//============================================================================================

//----------------------------------------------------------
/**
 * @brief	地下アイテム関連定義
 */
//----------------------------------------------------------
typedef struct _UNDERGROUND_DATA UNDERGROUNDDATA;

#define UG_ITEM_PC_NUM_MAX    (200) // パソコンのアイテム最大数
#define UG_ITEM_BAG_NUM_MAX   (40) // バッグ内の最大数
#define UG_TRAP_PLACE_NUM_MAX (16)  // 配置する罠の最大数
#define UG_NATURETRAP_PLACE_NUM_MAX (16*4)  // 配置する自然罠の最大数
#define UG_STONE_PLACE_NUM_MAX (100)  // 配置するたまの最大数
#define UG_FOSSIL_PLACE_NUM_MAX (255)
#define UG_FLAG_NUM_MAX (5)  // 記録しておく旗の数

//----------------------------------------------------------
//	セーブデータシステムや通信で使用する関数
//----------------------------------------------------------
extern int UnderGroundData_GetWorkSize(void);
extern UNDERGROUNDDATA * UnderGroundData_AllocWork(u32 heapID);
extern void UnderGroundData_Copy(const UNDERGROUNDDATA *pFrom, UNDERGROUNDDATA* pTo);

extern int SecretBaseData_GetWorkSize(void);
extern SECRETBASEDATA * SecretBaseData_AllocWork(u32 heapID);
extern int SecretBaseRecord_GetWorkSize(void);
extern SB_RECORD_DATA * SecretBaseRecord_AllocWork(u32 heapID);
extern void SecretBaseData_Copy(const SECRETBASEDATA *pFrom, SECRETBASEDATA* pTo);


//----------------------------------------------------------
//	UNDERGROUNDDATA操作のための関数
//----------------------------------------------------------
extern void UnderGroundData_Init(UNDERGROUNDDATA* pSBData);

// 日数に関連した処理
extern void UnderGroundDataDayUpdate(SAVEDATA* pSave, int diff_days);
extern u32 UnderGroundGetDayRandSeed(UNDERGROUNDDATA* pUGData);
extern void UnderGroundDataMinUpdate(SAVEDATA* pSave,  s32 diff_minute, BOOL bPenaltyMode);
extern void UnderGroundDataBeforeUGSave(SAVEDATA* pSave);
extern void UnderGroundDataAfterUG(SAVEDATA* pSave);
extern void UnderGroundDataLoadUpdate(SAVEDATA* pSave);
extern BOOL UnderGroundDataIsGoodsSend(SAVEDATA* pSave);
// 地上との連動
extern void UnderGroundSetDiamondPearlEvent(UNDERGROUNDDATA* pUGData);
extern BOOL UnderGroundIsDiamondPearlEvent(UNDERGROUNDDATA* pUGData);

// 旗に関係した処理
extern void UnderGroundAddFlag(UNDERGROUNDDATA* pUGData, const MYSTATUS* pMyStatus);
extern MYSTATUS* UnderGroundGetFlag(const UNDERGROUNDDATA* pUGData,int heapID,int index);

// グッズ関連
extern int UnderGroundGetNumGoodsPCItem(UNDERGROUNDDATA* pUGData);
extern BOOL UnderGroundAddGoodsPCItem(UNDERGROUNDDATA* pUGData, int goodsNo);
extern BOOL UnderGroundAddChkGoodsPCItem(UNDERGROUNDDATA* pUGData, int goodsNo);
extern int UnderGroundGetGoodsPCItem(UNDERGROUNDDATA* pUGData, int listIndex);
extern int UnderGroundDelGoodsPCItem(UNDERGROUNDDATA* pUGData, int listIndex);
extern BOOL UnderGroundIsEntryGoodsPCItem(UNDERGROUNDDATA* pUGData, int listIndex);
extern int UnderGroundEntryGoodsPCItem(UNDERGROUNDDATA* pUGData, int listIndex, int goodsIndex);
extern void UnderGroundTrashGoodsPCItem(UNDERGROUNDDATA* pUGData, int goodsIndex);
extern void UnderGroundTrashAllGoodsPCItem(UNDERGROUNDDATA* pUGData);
extern void UnderGroundChangeGoodsPcItem(UNDERGROUNDDATA* pUGData, int listIndex,int nextIndex);

extern int UnderGroundGetNumGoodsBagItem(UNDERGROUNDDATA* pUGData);
extern int UnderGroundGetGoodsBagItem(UNDERGROUNDDATA* pUGData, int listIndex);
extern int UnderGroundDelGoodsBagItem(UNDERGROUNDDATA* pUGData, int listIndex);
extern BOOL UnderGroundAddGoodsBagItem(UNDERGROUNDDATA* pUGData, int goodsType);
extern BOOL UnderGroundAddChkGoodsBagItem(UNDERGROUNDDATA* pUGData, int goodsType);
extern void UnderGroundChangeGoodsBagItem(UNDERGROUNDDATA* pUGData, int listIndex,int nextIndex);

// たま関連
extern int UnderGroundGetNumStonePCItem(UNDERGROUNDDATA* pUGData);
extern int UnderGroundGetStonePCItem(UNDERGROUNDDATA* pUGData, int listIndex);
extern int UnderGroundGetStoneCaratPCItem(UNDERGROUNDDATA* pUGData, int listIndex);
extern int UnderGroundDelStonePCItem(UNDERGROUNDDATA* pUGData, int listIndex);
extern BOOL UnderGroundAddStonePCItem(UNDERGROUNDDATA* pUGData, int stoneType, int carat);

extern int UnderGroundGetNumStoneBagItem(UNDERGROUNDDATA* pUGData);
extern int UnderGroundGetStoneBagItem(UNDERGROUNDDATA* pUGData, int listIndex);
extern int UnderGroundGetStoneCaratBagItem(UNDERGROUNDDATA* pUGData, int listIndex);
extern int UnderGroundDelStoneBagItem(UNDERGROUNDDATA* pUGData, int listIndex);
extern BOOL UnderGroundAddStoneBagItem(UNDERGROUNDDATA* pUGData, int stoneType, int carat);
extern void UnderGroundChangeStoneBagItem(UNDERGROUNDDATA* pUGData, int listIndex,int nextIndex);

// おたから関連
extern int UnderGroundGetTreasureBagItem(UNDERGROUNDDATA* pUGData, BOOL bDelete);
extern int UnderGroundTreasureItem2Item(int treasureType);
extern int UnderGroundGetNumTreasureBagItem(UNDERGROUNDDATA* pUGData);
extern int UnderGroundGetTreasureBagItem_List(UNDERGROUNDDATA* pUGData, int listIndex);
extern int UnderGroundDelTreasureBagItem(UNDERGROUNDDATA* pUGData, int listIndex);
extern BOOL UnderGroundAddTreasureBagItem(UNDERGROUNDDATA* pUGData, int treasureType);
extern void UnderGroundChangeTreasureBagItem(UNDERGROUNDDATA* pUGData, int listIndex,int nextIndex);

// 罠関連
extern int UnderGroundGetNumTrapPCItem(UNDERGROUNDDATA* pUGData);
extern int UnderGroundGetTrapPCItem(UNDERGROUNDDATA* pUGData, int listIndex);
extern int UnderGroundDelTrapPCItem(UNDERGROUNDDATA* pUGData, int listIndex);
extern BOOL UnderGroundAddTrapPCItem(UNDERGROUNDDATA* pUGData, int trapType);

extern int UnderGroundGetNumTrapBagItem(UNDERGROUNDDATA* pUGData);
extern int UnderGroundGetTrapBagItem_List(UNDERGROUNDDATA* pUGData, int listIndex);
extern int UnderGroundDelTrapBagItem(UNDERGROUNDDATA* pUGData, int listIndex);
extern BOOL UnderGroundAddTrapBagItem(UNDERGROUNDDATA* pUGData, int trapType);
extern void UnderGroundChangeTrapBagItem(UNDERGROUNDDATA* pUGData, int listIndex,int nextIndex);


// 地面に埋めたもの関連

extern void UnderGroundAddNatureTrapGroundItem(UNDERGROUNDDATA* pUGData, int trapType,int index, int x,int z);
extern int UnderGroundGetNatureTrapGroundItemType(UNDERGROUNDDATA* pUGData,int index);
extern int UnderGroundGetNatureTrapGroundItemX(UNDERGROUNDDATA* pUGData,int index);
extern int UnderGroundGetNatureTrapGroundItemZ(UNDERGROUNDDATA* pUGData,int index);
extern void UnderGroundDelNatureTrapGroundItem(UNDERGROUNDDATA* pUGData, int index);

extern void UnderGroundAddTrapGroundItem(UNDERGROUNDDATA* pUGData, int trapType,int index, int x,int z,int order);
extern int UnderGroundGetTrapGroundItemType(UNDERGROUNDDATA* pUGData,int index);
extern int UnderGroundGetTrapGroundItemX(UNDERGROUNDDATA* pUGData,int index);
extern int UnderGroundGetTrapGroundItemZ(UNDERGROUNDDATA* pUGData,int index);
extern int UnderGroundGetTrapGroundItemOrder(UNDERGROUNDDATA* pUGData,int index);

extern void UnderGroundAddStoneGroundItem(UNDERGROUNDDATA* pUGData, int stoneType,int index, int x,int z,int carat,int addCarat);
extern void UnderGroundBuryStoneGroundItem(UNDERGROUNDDATA* pUGData, int stoneType,int index, int x,int z,int carat);
extern int UnderGroundGetStoneGroundItemType(UNDERGROUNDDATA* pUGData,int index);
extern int UnderGroundGetStoneGroundItemX(UNDERGROUNDDATA* pUGData,int index);
extern int UnderGroundGetStoneGroundItemZ(UNDERGROUNDDATA* pUGData,int index);
extern int UnderGroundGetStoneGroundItemCarat(UNDERGROUNDDATA* pUGData,int index);
extern int UnderGroundGetStoneGroundItemCaratOrg(UNDERGROUNDDATA* pUGData,int index);
extern int UnderGroundGetStoneGroundItemCaratMul(UNDERGROUNDDATA* pUGData,int index);
extern void UnderGroundCountWalk(UNDERGROUNDDATA* pUGData);
extern int UnderGroundGetWalkNum(UNDERGROUNDDATA* pUGData);

extern int UnderGroundAddFossilGroundItem(UNDERGROUNDDATA* pUGData, int x,int z);
extern void UnderGroundDelFossilGroundItem(UNDERGROUNDDATA* pUGData, int index);
extern int UnderGroundGetFossilGroundItemX(UNDERGROUNDDATA* pUGData,int index);
extern int UnderGroundGetFossilGroundItemZ(UNDERGROUNDDATA* pUGData,int index);

extern  BOOL UnderGroundIsNewDay(UNDERGROUNDDATA* pUGData);
extern  void UnderGroundResetNewDay(UNDERGROUNDDATA* pUGData);

extern void UnderGroundSetFossilDig(UNDERGROUNDDATA* pUGData,int type);
extern BOOL UnderGroundIsFossilAdvent(UNDERGROUNDDATA* pUGData,int type);

//----------------------------------------------------------
//	SECRETBASEDATA操作のための関数
//----------------------------------------------------------
extern void SecretBaseData_Init(SECRETBASEDATA* pSBData);
extern void SecretBaseData_Reform(SECRETBASEDATA* pSBData);
extern void SecretBaseData_SetGoodsPosition(SECRETBASEDATA* pSBData, int goodsIndex, int type, int x, int z);
extern void SecretBaseData_ChangeGoodsPosition(SECRETBASEDATA* pSBData, int goodsIndex, int x, int z);
extern int SecretBaseData_GetGoodsType(const SECRETBASEDATA* pSBData, int goodsIndex);
extern int SecretBaseData_GetGoodsXPos(const SECRETBASEDATA* pSBData, int goodsIndex);
extern int SecretBaseData_GetGoodsZPos(const SECRETBASEDATA* pSBData, int goodsIndex);
/// 岩をどのくらい保持していないといけないかを返す
extern int SecretBaseData_GetPlaceRockLimit(const SECRETBASEDATA* pSBData);
///	配置物をいくつまで置いていいのかを返す
extern int SecretBaseData_GetPlaceGoodsLimit(const SECRETBASEDATA* pSBData);
extern void SecretBaseData_SetMakeDown(SECRETBASEDATA* pSBData);

/// レコードデータの取得
extern int SecretBaseRecordGetPoint(const SB_RECORD_DATA* pSBRecord);
extern int SecretBaseRecordGetUGRank(const SB_RECORD_DATA* pSBRecord);
extern void SecretBaseRecordSetPoint(SB_RECORD_DATA* pSBRecord, int add);
extern int SecretBaseRecordGetTalkNum(const SB_RECORD_DATA* pSBRecord);
extern void SecretBaseRecordSetTalkNum( SB_RECORD_DATA* pSBRecord, int meetNetID);
extern int SecretBaseRecordGetSendItemNum(const SB_RECORD_DATA* pSBRecord);
extern void SecretBaseRecordSetSendItemNum( SB_RECORD_DATA* pSBRecord);
extern int SecretBaseRecordGetFlagConquerNum(const SB_RECORD_DATA* pSBRecord);
extern void SecretBaseRecordSetFlagConquerNum( SB_RECORD_DATA* pSBRecord);
extern int SecretBaseRecordGetFlagType(const SB_RECORD_DATA* pSBRecord);
extern int SecretBaseRecordGetFlagDeliveryNum(const SB_RECORD_DATA* pSBRecord);
extern void SecretBaseRecordSetFlagDeliveryNum(SB_RECORD_DATA* pSBRecord);
extern int SecretBaseRecordGetStoneNum(const SB_RECORD_DATA* pSBRecord);
extern void SecretBaseRecordSetStoneNum( SB_RECORD_DATA* pSBRecord, int add);
extern int SecretBaseRecordGetFossilNum(const SB_RECORD_DATA* pSBRecord);
extern void SecretBaseRecordSetFossilNum( SB_RECORD_DATA* pSBRecord, int add);
extern int SecretBaseRecordGetTreasureNum(const SB_RECORD_DATA* pSBRecord);
extern void SecretBaseRecordSetTreasureNum( SB_RECORD_DATA* pSBRecord, int add);
extern int SecretBaseRecordGetTrapConquerNum(const SB_RECORD_DATA* pSBRecord);
extern void SecretBaseRecordSetTrapConquerNum( SB_RECORD_DATA* pSBRecord);
extern int SecretBaseRecordGetTrapTumbleNum(const SB_RECORD_DATA* pSBRecord);
extern void SecretBaseRecordSetTrapTumbleNum( SB_RECORD_DATA* pSBRecord);
extern int SecretBaseRecordGetTrapRescueNum(const SB_RECORD_DATA* pSBRecord);
extern void SecretBaseRecordSetTrapRescueNum( SB_RECORD_DATA* pSBRecord);
extern int SecretBaseRecordGetItemRecvNum(const SB_RECORD_DATA* pSBRecord);
extern void SecretBaseRecordSetItemRecvNum( SB_RECORD_DATA* pSBRecord);
extern int SecretBaseRecordGetFlagStealNum(const SB_RECORD_DATA* pSBRecord);
extern void SecretBaseRecordSetFlagStealNum( SB_RECORD_DATA* pSBRecord);
extern int SecretBaseRecordGetFlagReverseNum(const SB_RECORD_DATA* pSBRecord);
extern void SecretBaseRecordSetFlagReverseNum( SB_RECORD_DATA* pSBRecord);
extern int SecretBaseRecordGetRelocateNum(const SB_RECORD_DATA* pSBRecord);
extern void SecretBaseRecordSetRelocateNum( SB_RECORD_DATA* pSBRecord);

extern void SecretBaseSetSecretBasePosition(SECRETBASEDATA* pSec,int x,int z,int dir);
extern int SecretBaseGetSecretBasePositionX(const SECRETBASEDATA* pSec);
extern int SecretBaseGetSecretBasePositionZ(const SECRETBASEDATA* pSec);
extern int SecretBaseGetSecretBasePositionDir(const SECRETBASEDATA* pSec);
extern BOOL SecretBaseIsSecretBaseMake(const SECRETBASEDATA* pSec);

extern void UnderGroundSetFirstFossil(UNDERGROUNDDATA* pUGData);
extern BOOL UnderGroundIsFirstFossil(UNDERGROUNDDATA* pUGData);

//----------------------------------------------------------
//	セーブデータ取得のための関数
//----------------------------------------------------------
extern UNDERGROUNDDATA* SaveData_GetUnderGroundData(SAVEDATA* pSave);
extern SECRETBASEDATA* SaveData_GetSecretBaseData(SAVEDATA* pSave);
extern SB_RECORD_DATA* SaveData_GetSecretBaseRecord(SAVEDATA* pSave);
extern SB_RECORD_DATA* SecretBaseGetSecretBaseRecord(SECRETBASEDATA* pSec);

//----------------------------------------------------------
//	デバッグのための関数
//----------------------------------------------------------
#ifdef PM_DEBUG
extern void Debug_UnderGroundData_AddTreasure(UNDERGROUNDDATA* pSBData, int type);
extern void Debug_SecretBaseData_AddGoods(SECRETBASEDATA* pSBData, int goodsType, int x, int z);
extern void D_SecretBaseRecordSetFlagDeliveryNum(SB_RECORD_DATA* pSBRecord,int num);

#endif //PM_DEBUG

#endif //__UNDERGROUNDDATA_H__
