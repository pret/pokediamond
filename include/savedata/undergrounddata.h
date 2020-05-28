//============================================================================================
/**
 * @file	undergrounddata.h
 * @brief	�n���A�C�e���A�N�Z�X�p�w�b�_
 * @author	k.ohno
 * @date	2006.2.23
 */
//============================================================================================
#ifndef __UNDERGROUNDDATA_H__
#define __UNDERGROUNDDATA_H__

#include "system/savedata_def.h"	//SAVEDATA�Q�Ƃ̂���

#include "gflib/msg_print.h"		//STRCODE�Q�Ƃ̂���
#include "gflib/strbuf.h"			//STRBUF�Q�Ƃ̂���
#include "savedata/mystatus.h"			//MYSTATUS�Q�Ƃ̂���


//----------------------------------------------------------
/**
 * @brief	�閧��n�f�[�^�^��`
 */
//----------------------------------------------------------
typedef struct _SECRETBASEDATA SECRETBASEDATA;
typedef struct _SB_RECORD_DATA SB_RECORD_DATA;

#define SECRETBASE_PC_NUM_MAX   (1) // �p�\�R���̍ő吔
#define SECRETBASE_GOODS_NUM_MAX   (15) // �O�b�Y�̍ő吔
#define SECRETBASE_LOCK_NUM_MAX   (16)  // ��̍ő吔
#define SECRETBASE_SETUPOBJ_NUM_MAX (SECRETBASE_GOODS_NUM_MAX + SECRETBASE_LOCK_NUM_MAX + SECRETBASE_PC_NUM_MAX)
#define SECRETBASE_GOODS_ROCK   (6)     // ��̃^�C�v�ԍ�
#define SECRETBASE_PC_INDEX_NO  (0)    // �p�\�R���̃C���f�b�N�X�ԍ�

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


typedef enum {  // �n���|�C���g�ł��炦��̍�
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
 * @brief	�n���A�C�e���֘A��`
 */
//----------------------------------------------------------
typedef struct _UNDERGROUND_DATA UNDERGROUNDDATA;

#define UG_ITEM_PC_NUM_MAX    (200) // �p�\�R���̃A�C�e���ő吔
#define UG_ITEM_BAG_NUM_MAX   (40) // �o�b�O���̍ő吔
#define UG_TRAP_PLACE_NUM_MAX (16)  // �z�u����㩂̍ő吔
#define UG_NATURETRAP_PLACE_NUM_MAX (16*4)  // �z�u���鎩�R㩂̍ő吔
#define UG_STONE_PLACE_NUM_MAX (100)  // �z�u���邽�܂̍ő吔
#define UG_FOSSIL_PLACE_NUM_MAX (255)
#define UG_FLAG_NUM_MAX (5)  // �L�^���Ă������̐�

//----------------------------------------------------------
//	�Z�[�u�f�[�^�V�X�e����ʐM�Ŏg�p����֐�
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
//	UNDERGROUNDDATA����̂��߂̊֐�
//----------------------------------------------------------
extern void UnderGroundData_Init(UNDERGROUNDDATA* pSBData);

// �����Ɋ֘A��������
extern void UnderGroundDataDayUpdate(SAVEDATA* pSave, int diff_days);
extern u32 UnderGroundGetDayRandSeed(UNDERGROUNDDATA* pUGData);
extern void UnderGroundDataMinUpdate(SAVEDATA* pSave,  s32 diff_minute, BOOL bPenaltyMode);
extern void UnderGroundDataBeforeUGSave(SAVEDATA* pSave);
extern void UnderGroundDataAfterUG(SAVEDATA* pSave);
extern void UnderGroundDataLoadUpdate(SAVEDATA* pSave);
extern BOOL UnderGroundDataIsGoodsSend(SAVEDATA* pSave);
// �n��Ƃ̘A��
extern void UnderGroundSetDiamondPearlEvent(UNDERGROUNDDATA* pUGData);
extern BOOL UnderGroundIsDiamondPearlEvent(UNDERGROUNDDATA* pUGData);

// ���Ɋ֌W��������
extern void UnderGroundAddFlag(UNDERGROUNDDATA* pUGData, const MYSTATUS* pMyStatus);
extern MYSTATUS* UnderGroundGetFlag(const UNDERGROUNDDATA* pUGData,int heapID,int index);

// �O�b�Y�֘A
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

// ���܊֘A
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

// ��������֘A
extern int UnderGroundGetTreasureBagItem(UNDERGROUNDDATA* pUGData, BOOL bDelete);
extern int UnderGroundTreasureItem2Item(int treasureType);
extern int UnderGroundGetNumTreasureBagItem(UNDERGROUNDDATA* pUGData);
extern int UnderGroundGetTreasureBagItem_List(UNDERGROUNDDATA* pUGData, int listIndex);
extern int UnderGroundDelTreasureBagItem(UNDERGROUNDDATA* pUGData, int listIndex);
extern BOOL UnderGroundAddTreasureBagItem(UNDERGROUNDDATA* pUGData, int treasureType);
extern void UnderGroundChangeTreasureBagItem(UNDERGROUNDDATA* pUGData, int listIndex,int nextIndex);

// 㩊֘A
extern int UnderGroundGetNumTrapPCItem(UNDERGROUNDDATA* pUGData);
extern int UnderGroundGetTrapPCItem(UNDERGROUNDDATA* pUGData, int listIndex);
extern int UnderGroundDelTrapPCItem(UNDERGROUNDDATA* pUGData, int listIndex);
extern BOOL UnderGroundAddTrapPCItem(UNDERGROUNDDATA* pUGData, int trapType);

extern int UnderGroundGetNumTrapBagItem(UNDERGROUNDDATA* pUGData);
extern int UnderGroundGetTrapBagItem_List(UNDERGROUNDDATA* pUGData, int listIndex);
extern int UnderGroundDelTrapBagItem(UNDERGROUNDDATA* pUGData, int listIndex);
extern BOOL UnderGroundAddTrapBagItem(UNDERGROUNDDATA* pUGData, int trapType);
extern void UnderGroundChangeTrapBagItem(UNDERGROUNDDATA* pUGData, int listIndex,int nextIndex);


// �n�ʂɖ��߂����̊֘A

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
//	SECRETBASEDATA����̂��߂̊֐�
//----------------------------------------------------------
extern void SecretBaseData_Init(SECRETBASEDATA* pSBData);
extern void SecretBaseData_Reform(SECRETBASEDATA* pSBData);
extern void SecretBaseData_SetGoodsPosition(SECRETBASEDATA* pSBData, int goodsIndex, int type, int x, int z);
extern void SecretBaseData_ChangeGoodsPosition(SECRETBASEDATA* pSBData, int goodsIndex, int x, int z);
extern int SecretBaseData_GetGoodsType(const SECRETBASEDATA* pSBData, int goodsIndex);
extern int SecretBaseData_GetGoodsXPos(const SECRETBASEDATA* pSBData, int goodsIndex);
extern int SecretBaseData_GetGoodsZPos(const SECRETBASEDATA* pSBData, int goodsIndex);
/// ����ǂ̂��炢�ێ����Ă��Ȃ��Ƃ����Ȃ�����Ԃ�
extern int SecretBaseData_GetPlaceRockLimit(const SECRETBASEDATA* pSBData);
///	�z�u���������܂Œu���Ă����̂���Ԃ�
extern int SecretBaseData_GetPlaceGoodsLimit(const SECRETBASEDATA* pSBData);
extern void SecretBaseData_SetMakeDown(SECRETBASEDATA* pSBData);

/// ���R�[�h�f�[�^�̎擾
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
//	�Z�[�u�f�[�^�擾�̂��߂̊֐�
//----------------------------------------------------------
extern UNDERGROUNDDATA* SaveData_GetUnderGroundData(SAVEDATA* pSave);
extern SECRETBASEDATA* SaveData_GetSecretBaseData(SAVEDATA* pSave);
extern SB_RECORD_DATA* SaveData_GetSecretBaseRecord(SAVEDATA* pSave);
extern SB_RECORD_DATA* SecretBaseGetSecretBaseRecord(SECRETBASEDATA* pSec);

//----------------------------------------------------------
//	�f�o�b�O�̂��߂̊֐�
//----------------------------------------------------------
#ifdef PM_DEBUG
extern void Debug_UnderGroundData_AddTreasure(UNDERGROUNDDATA* pSBData, int type);
extern void Debug_SecretBaseData_AddGoods(SECRETBASEDATA* pSBData, int goodsType, int x, int z);
extern void D_SecretBaseRecordSetFlagDeliveryNum(SB_RECORD_DATA* pSBRecord,int num);

#endif //PM_DEBUG

#endif //__UNDERGROUNDDATA_H__
