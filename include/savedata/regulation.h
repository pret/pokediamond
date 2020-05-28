//============================================================================================
/**
 * @file	regulation.h
 * @brief	バトルレギュレーションデータアクセス用ヘッダ
 * @author	k.ohno
 * @date	2006.1.20
 */
//============================================================================================
#ifndef __REGULATION_H__
#define __REGULATION_H__

#include "system/savedata_def.h"	//SAVEDATA参照のため
#include "system/gamedata.h"        //EOM_SIZE参照のため
#include "gflib/msg_print.h"		//STRCODE参照のため
#include "gflib/strbuf.h"			//STRBUF参照のため

//============================================================================================
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	バトルレギュレーションデータ型定義
 */
//----------------------------------------------------------
typedef struct _REGULATION_DATA REGULATION_DATA;


#define REGULATION_NAME_SIZE   (11)      // ルール名の長さ 11文字22バイト +EOM2byte
#define REGULATION_MAX_NUM   (1)   // １本保存可能

typedef enum  {
  REGULATION_NAME,          //ルール名
  REGULATION_POKE_NUM,      //ポケモン数
  REGULATION_LEVEL,         //ポケモンのレベル
  REGULATION_TOTAL_LEVEL,   //ポケモンのレベル合計
  REGULATION_EVOLUTION,     //進化ポケモンかどうか
  REGULATION_HEIGHT,        //身長   0.2 - 9.9m 
  REGULATION_HEIGHT_LIMIT,  //身長制限  -1,0,1
  REGULATION_WEIGHT,       //体重    1-99  kg
  REGULATION_WEIGHT_LIMIT,   //体重制限  -1,0,1
  REGULATION_BOTH_ITEM,    //同じ道具がＯＫか？
  REGULATION_BOTH_MONSTER, //同じポケモンＯＫか？
  REGULATION_LEGEND,       // 伝説系有無
  REGULATION_FIXDAMAGE,    // 固定ダメージ技が必ず失敗
} REGULATION_PARAM_TYPE;

//----------------------------------------------------------
/**
 * @brief	バトルレギュレーションデータ型定義  fushigi_data.h参照の為外部公開に
 */
//----------------------------------------------------------
typedef struct {
	STRCODE cupName[REGULATION_NAME_SIZE + EOM_SIZE];
	u16 totalLevel;
	u8 num;
	u8 level;
    s8 height;
    s8 weight;
    u8 evolution:1;    //  
    u8 bLegend:1;
    u8 bBothMonster:1;
    u8 bBothItem:1;
    u8 bFixDamage:1;
}  REGULATION;

//============================================================================================
//============================================================================================
//----------------------------------------------------------
//	セーブデータシステムや通信で使用する関数
//----------------------------------------------------------
extern int Regulation_GetWorkSize(void);
extern int RegulationData_GetWorkSize(void);
extern REGULATION * Regulation_AllocWork(u32 heapID);
extern void Regulation_Copy(const REGULATION * from, REGULATION * to);
extern int Regulation_Cmp(const REGULATION* pCmp1,const REGULATION* pCmp2);

//----------------------------------------------------------
//	REGULATION操作のための関数
//----------------------------------------------------------
extern void Regulation_Init(REGULATION * my);
extern void RegulationData_Init(REGULATION_DATA * my);

//名前
extern void Regulation_SetCupName(REGULATION * pReg, const STRBUF* pCupName);
extern void Regulation_GetCupName(const REGULATION* pReg,STRBUF* pReturnCupName);
extern STRBUF* Regulation_CreateCupName(const REGULATION* pReg, int heapID);

extern int Regulation_GetParam(const REGULATION* pReg, REGULATION_PARAM_TYPE type);
extern BOOL Regulation_SetParam(REGULATION * pReg, REGULATION_PARAM_TYPE type, int param);

//----------------------------------------------------------
//	セーブデータ取得のための関数
//----------------------------------------------------------
extern REGULATION* SaveData_GetRegulation(SAVEDATA* pSave,int regNo);
extern void SaveData_SetRegulation(SAVEDATA* pSave, const REGULATION* pReg);


#endif //__REGULATION_H__
