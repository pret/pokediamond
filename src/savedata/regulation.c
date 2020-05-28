//============================================================================================
/**
 * @file	regulation.c
 * @brief	バトルレギュレーションデータアクセス用ソース
 * @author	k.ohno
 * @date	2006.1.20
 */
//============================================================================================

#include "savedata/savedata_def.h"	//SAVEDATA参照のため

#include "common.h"

#include "system/gamedata.h"
#include "savedata/savedata.h"


#include "savedata/regulation.h"
#include "regulation_local.h"

#include "system/pm_str.h"

#include "gflib/strbuf_family.h"


//============================================================================================
//============================================================================================

//============================================================================================
//
//	セーブデータシステムが依存する関数
//
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	ワークサイズ取得
 * @return	int		サイズ（バイト単位）
 */
//----------------------------------------------------------
int Regulation_GetWorkSize(void)
{
	return sizeof(REGULATION);
}

//----------------------------------------------------------
/**
 * @brief	ワークサイズ取得
 * @return	int		サイズ（バイト単位）
 */
//----------------------------------------------------------
int RegulationData_GetWorkSize(void)
{
	return sizeof(REGULATION_DATA);
}

//----------------------------------------------------------
/**
 * @brief	バトルレギュレーションワークの確保
 * @param	heapID		メモリ確保をおこなうヒープ指定
 * @return	REGULATION*	取得したワークへのポインタ
 */
//----------------------------------------------------------
REGULATION* Regulation_AllocWork(u32 heapID)
{
	REGULATION* reg;
	reg = sys_AllocMemory(heapID, sizeof(REGULATION));
	Regulation_Init(reg);
	return reg;
}

//----------------------------------------------------------
/**
 * @brief	REGULATIONのコピー
 * @param	from	コピー元REGULATIONへのポインタ
 * @param	to		コピー先REGULATIONへのポインタ
 */
//----------------------------------------------------------
void Regulation_Copy(const REGULATION *pFrom, REGULATION* pTo)
{
	MI_CpuCopy8(pFrom, pTo, sizeof(REGULATION));
}

//----------------------------------------------------------
/**
 * @brief	REGULATIONの比較
 * @param	cmp1   比較するREGULATIONへのポインタ
 * @param	cmp2   比較されるREGULATIONへのポインタ
 * @return  一致していたらTRUE
 */
//----------------------------------------------------------
int Regulation_Cmp(const REGULATION* pCmp1,const REGULATION* pCmp2)
{
    int i,size = sizeof(REGULATION);
    const u8* pc1 = (const u8*)pCmp1;
    const u8* pc2 = (const u8*)pCmp2;

    for(i = 0; i < size; i++){
        if(*pc1 != *pc2){
            return FALSE;
        }
        pc1++;
        pc2++;
    }
    return TRUE;
}

//============================================================================================
//
//	REGULATION操作のための関数
//
//============================================================================================
//----------------------------------------------------------
/**
 * @brief	バトルレギュレーションデータの初期化
 * @param	pReg		REGULATIONワークへのポインタ
 */
//----------------------------------------------------------
void Regulation_Init(REGULATION* pReg)
{
	memset(pReg, 0, sizeof(REGULATION));
}

//----------------------------------------------------------
/**
 * @brief	バトルレギュレーションデータの初期化
 * @param	pReg		REGULATIONワークへのポインタ
 */
//----------------------------------------------------------
void RegulationData_Init(REGULATION_DATA* pRegData)
{
	memset(pRegData, 0, sizeof(REGULATION_DATA));
}

//----------------------------------------------------------
/**
 * @brief	カップ名セット
 * @param	pReg	REGULATIONワークポインタ
 * @param	pCupBuf	カップ名が入ったバッファ
 */
//----------------------------------------------------------
void Regulation_SetCupName(REGULATION* pReg, const STRBUF *pCupBuf)
{
    STRBUF_GetStringCode(pCupBuf, pReg->cupName, (REGULATION_NAME_SIZE + EOM_SIZE));
}

//----------------------------------------------------------
/**
 * @brief	カップ名取得
 * @param	pReg		    REGULATIONワークポインタ
 * @param	pReturnCupName	カップ名を入れるSTRBUFポインタ
 * @return	none
 */
//----------------------------------------------------------
void Regulation_GetCupName(const REGULATION* pReg,STRBUF* pReturnCupName)
{
    STRBUF_SetStringCodeOrderLength(pReturnCupName, pReg->cupName, (REGULATION_NAME_SIZE + EOM_SIZE));
}

//----------------------------------------------------------
/**
 * @brief	カップ名前取得（STRBUFを生成）
 * @param	pReg	ワークへのポインタ
 * @param	heapID	STRBUFを生成するヒープのID
 * @return	STRBUF	名前を格納したSTRBUFへのポインタ
 */
//----------------------------------------------------------
STRBUF* Regulation_CreateCupName(const REGULATION* pReg, int heapID)
{
	STRBUF* tmpBuf = STRBUF_Create((REGULATION_NAME_SIZE + EOM_SIZE)*GLOBAL_MSGLEN, heapID);
	STRBUF_SetStringCode( tmpBuf, pReg->cupName );
	return tmpBuf;
}

//----------------------------------------------------------
/**
 * @brief	パラメーターを取得する
 * @param	pReg	REGULATIONワークポインタ
 * @param	type	REGULATION_PARAM_TYPE enum のどれか
 */
//----------------------------------------------------------
int Regulation_GetParam(const REGULATION* pReg, REGULATION_PARAM_TYPE type)
{
    int ret = 0;

    switch(type){
      case REGULATION_POKE_NUM:      //ポケモン数
        ret = pReg->num;
        break;
      case REGULATION_LEVEL:         //ポケモンのレベル
        ret = pReg->level;
        break;
      case REGULATION_TOTAL_LEVEL:   //ポケモンのレベル合計
        ret = pReg->totalLevel;
        break;
      case REGULATION_EVOLUTION:     //進化前中後
        ret = pReg->evolution;
        break;
      case REGULATION_HEIGHT:        //身長
        ret = pReg->height;
        break;
      case REGULATION_HEIGHT_LIMIT:  //身長制限  -1,0,1
        if(pReg->height>0){
            ret = 1;   // 以上
        }
        else if(pReg->height<0){
            ret = -1;  // 以下
        }
        break;
      case REGULATION_WEIGHT:       //体重
        ret = pReg->weight;
        break;
      case REGULATION_WEIGHT_LIMIT:   //体重制限  -1,0,1
        if(pReg->weight>0){
            ret = 1;   // 以上
        }
        else if(pReg->weight<0){
            ret = -1;  // 以下
        }
        break;
      case REGULATION_BOTH_ITEM:    //同じ道具がＯＫか？
        ret = pReg->bBothItem;
        break;
      case REGULATION_BOTH_MONSTER: //同じポケモンＯＫか？
        ret = pReg->bBothMonster;
        break;
      case REGULATION_LEGEND:       // 伝説系有無
        ret = pReg->bLegend;
        break;
      case REGULATION_FIXDAMAGE:       // 特殊ルール（固定ダメージ無効）
        ret = pReg->bFixDamage;
        break;
    }
    return ret;
}

//----------------------------------------------------------
/**
 * @brief	パラメーターを書きこむ
 * @param	pReg	REGULATIONワークポインタ
 * @param	type	REGULATION_PARAM_TYPE enum のどれか
 * @param	param	書きこむ値
 * @return  正しく書き込んだらTRUE  不正な値の場合FALSE
 */
//----------------------------------------------------------
BOOL Regulation_SetParam(REGULATION* pReg, REGULATION_PARAM_TYPE type, int param)
{
    switch(type){
      case REGULATION_POKE_NUM:      //ポケモン数
        GF_ASSERT_RETURN(param <= _REG_NUM_MAX,FALSE);
        GF_ASSERT_RETURN(param >= _REG_NUM_MIN,FALSE);
        pReg->num = param;
        break;
      case REGULATION_LEVEL:         //ポケモンのレベル
        GF_ASSERT_RETURN(param <= _REG_LEVEL_MAX,FALSE);
        GF_ASSERT_RETURN(param >= _REG_LEVEL_MIN,FALSE);
        pReg->level = param;
        break;
      case REGULATION_TOTAL_LEVEL:   //ポケモンのレベル合計
        GF_ASSERT_RETURN(param <= _REG_TOTAL_LEVEL_MAX,FALSE);
        GF_ASSERT_RETURN(param >= _REG_TOTAL_LEVEL_MIN,FALSE);
        pReg->totalLevel = param;
        break;
      case REGULATION_EVOLUTION:     //進化前中後
        pReg->evolution = param;
        break;
      case REGULATION_HEIGHT:        //身長
        pReg->height = param;
        break;
      case REGULATION_HEIGHT_LIMIT:  //身長制限  -1,0,1
        if((param == 1) && (pReg->height < 0)){
            pReg->height = -pReg->height;
        }
        else if((param == -1) && (pReg->height > 0)){
            pReg->height = -pReg->height;
        }
        else{
            pReg->height = 0;
        }
        break;
      case REGULATION_WEIGHT:       //体重
        GF_ASSERT_RETURN(param <= _REG_WEIGHT_MAX, FALSE);
        GF_ASSERT_RETURN(param >= _REG_WEIGHT_MIN, FALSE);
        pReg->weight;
        break;
      case REGULATION_WEIGHT_LIMIT:   //体重制限  -1,0,1
        if((param == 1) && (pReg->weight < 0)){
            pReg->weight = -pReg->weight;
        }
        else if((param == -1) && (pReg->weight > 0)){
            pReg->weight = -pReg->weight;
        }
        else{
            pReg->weight = 0;
        }
        break;
      case REGULATION_BOTH_ITEM:    //同じ道具がＯＫか？
        pReg->bBothItem = param;
        break;
      case REGULATION_BOTH_MONSTER: //同じポケモンＯＫか？
        pReg->bBothMonster = param;
        break;
      case REGULATION_LEGEND:       // 伝説系有無
        pReg->bLegend = param;
        break;
      case REGULATION_FIXDAMAGE:       // 固定ダメージ技が必ず失敗
        pReg->bFixDamage = param;
        break;
    }
    return TRUE;
}

//----------------------------------------------------------
/**
 * @brief	レギュレーションデータへのポインタ取得
 * @param	pSave    	セーブデータ保持ワークへのポインタ
 * @param	何本目のレギュレーションデータか
 * @return	REGULATION	ワークへのポインタ  無効データの場合NULL
 */
//----------------------------------------------------------
REGULATION* SaveData_GetRegulation(SAVEDATA* pSave, int regNo)
{
	REGULATION_DATA* pRegData = NULL;

    GF_ASSERT_RETURN(regNo < REGULATION_MAX_NUM,NULL);
    
	pRegData = SaveData_Get(pSave, GMDATA_ID_REGULATION);
    if(Regulation_GetParam(&pRegData->regulation_buff[regNo],REGULATION_POKE_NUM)!=0){
        return &pRegData->regulation_buff[regNo];
    }
    return NULL;
}

//----------------------------------------------------------
/**
 * @brief	レギュレーションデータの保存
 * @param	pSave    	セーブデータ保持ワークへのポインタ
 * @param	const REGULATION  レギュレーションデータ
 * @return	none
 */
//----------------------------------------------------------
void SaveData_SetRegulation(SAVEDATA* pSave, const REGULATION* pReg)
{
	REGULATION_DATA* pRegData = NULL;

	pRegData = SaveData_Get(pSave, GMDATA_ID_REGULATION);
    Regulation_Copy(pReg, &pRegData->regulation_buff[0]);
}

