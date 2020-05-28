//============================================================================================
/**
 * @file	seedbed.h
 * @author	tamada
 * @date	2005.02.01
 * @brief	きのみの状態データ定義
 */
//============================================================================================
#ifndef	__SEEDBED_H__
#define	__SEEDBED_H__

#include "savedata/savedata_def.h"

//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	きのみ状態データの不完全型定義
 */
//----------------------------------------------------------
typedef struct _SEEDBED SEEDBED;

//----------------------------------------------------------
/**
 * @brief	きのみの状態定義
 */
//----------------------------------------------------------
typedef enum {
	SEEDSTAT_NOTHING = 0,	///<きのみが植えられていない
	SEEDSTAT_UNDERGROUND,	///<きのみを植えた状態
	SEEDSTAT_HUTABA,		///<芽が出てきた状態
	SEEDSTAT_MIKI,			///<少し成長した状態
	SEEDSTAT_FLOWER,		///<花が咲いている状態
	SEEDSTAT_FRUIT,			///<実がなっている状態

	SEEDSTAT_CHANGE = 0xff,	///<状態変化中
}SEEDSTAT;

//----------------------------------------------------------
/**
 * @brief	湿り気の状態
 */
//----------------------------------------------------------
typedef enum {
	SEEDGROUND_DRY = 0,	///<乾ききってヒビがでている状態
	SEEDGROUND_WET,		///<少し乾いた状態
	SEEDGROUND_FULL,		///<十分水分がある状態
}SEEDGROUND;

//----------------------------------------------------------
/**
 * @brief	肥料の種類
 */
//----------------------------------------------------------
typedef enum {
	SEEDCOMPOST_NOTHING = 0,
	SEEDCOMPOST_SUKUSUKU,
	SEEDCOMPOST_YURURI,
	SEEDCOMPOST_MINAARU,
	SEEDCOMPOST_NEBARI,
}SEEDCOMPOST;

//----------------------------------------------------------
/**
 * @brief	きのみの成長処理に必要なパラメータ
 */
//----------------------------------------------------------
typedef struct {
	u8 grow_speed;		///<成長速度（時間単位）
	u8 root_power;		///<吸水力
	u8 nuts_rate;		///<実の生る数の倍率
}SEED_TABLE;

//============================================================================================
//============================================================================================
//----------------------------------------------------------
//----------------------------------------------------------
extern int SEEDBED_GetWorkSize(void);
extern SEEDBED * SEEDBED_AllocWork(u32 heapID);
extern void SEEDBED_Init(SEEDBED * sbed);

//成長用テーブル生成
extern SEED_TABLE * SEEDBED_CreateParamTable(int heapID);

//初期状態セット処理
extern void SEEDBED_SetDefaultData(SEEDBED * sbed, int heapID, const u16 * init_data, int max);
//----------------------------------------------------------
//----------------------------------------------------------
//状態取得
extern SEEDSTAT SEEDBED_GetSeedStatus(const SEEDBED * sbed, int id);

//きのみの種類を取得
extern int SEEDBED_GetSeedType(const SEEDBED * sbed, int id);

//水やりの状態を取得
extern SEEDGROUND SEEDBED_GetGroundStatus(const SEEDBED * sbed, int id);

//きのみのHPを取得
extern int SEEDBED_GetSeedHP(const SEEDBED * sbed, int id);

//きのみを植える
extern void SEEDBED_SetNuts(SEEDBED * sbed, int id, const SEED_TABLE * param, int type);
//水をあげる
extern void SEEDBED_SetSeedWater(SEEDBED * sbed, int id);
//コヤシをまく
//コヤシの種類を取得
extern void SEEDBED_SetCompost(SEEDBED * sbed, int id, SEEDCOMPOST compost);

//成長フラグの設定
extern BOOL SEEDBED_GetGrowthFlag(const SEEDBED * sbed, int id);
//成長フラグの取得
extern void SEEDBED_SetGrowthFlag(SEEDBED * sbed, int id, BOOL flag);

//きのみの数を取得
extern int SEEDBED_GetSeedCount(const SEEDBED * sbed, int id);

extern SEEDCOMPOST SEEDBED_GetCompost(const SEEDBED * sbed, int id);
//----------------------------------------------------------
//----------------------------------------------------------
//きのみを収穫
extern int SEEDBED_GetHarvest(SEEDBED * sbed, int id);

//きのみを成長させる
extern void SEEDBED_Growth(SEEDBED * sbed, const SEED_TABLE * param, int minute);

//----------------------------------------------------------
//----------------------------------------------------------
extern SEEDBED * SaveData_GetSeedBed(SAVEDATA * sv);

#endif /* __SEEDBED_H__ */
