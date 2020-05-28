//============================================================================================
/**
 * @file	regulation_data.c
 * @brief	バトルレギュレーションデータアクセス用ソース
 * @author	k.ohno
 * @date	2006.5.24
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

#include "msgdata/msg.naix"
#include "system/wordset.h"
#include "msgdata/msg_directbattlecorner.h"

#include "savedata/regulation_data.h"

//============================================================================================
//============================================================================================

REGULATION _cup[] = {
    {
        {EOM_},  //  // スタンダードカップ 名前はgmmから取ってくる
        0,     // 合計なし
        3,      // 3匹
        50,     // LV50
        0,      // 身長制限なし
        0,      // 体重制限なし
        1,      // 進化ポケモンOK
        0,      // 特殊不可
        0,      // 同じポケモン不可
        0,      // 同じ道具不可
        0,// 固定ダメージ技が必ず失敗
    },
    {
        {EOM_},//● ファンシーカップ
        80,//レベルの合計８０まで
        3,//３匹
        30,//ポケモンのレベル３０まで
        -20,//身長制限２．０ｍいか
        -20,// 体重制限２０ｋｇいか
        0,// 進化ポケモン参加できない
        0,// 特別なポケモン参加できない
        0,// 同じポケモン参加できない
        0,// 同じ道具持たせられない
        0,// 固定ダメージ技が必ず失敗
    },
    {
        {EOM_},//● リトルカップ
        0,//レベルの合計制限なし
        3,//３匹
        5,//ポケモンのレベル５まで
        0,// 身長制限なし
        0,// 体重制限なし
        0,// 進化ポケモン参加できない
        0,// 特別なポケモン参加できない
        0,// 同じポケモン参加できない
        0,// 同じ道具持たせられない 
        1,//特別ルール：りゅうのいかり、ソニックブームの命中率が０になる。
    },
    {
        {EOM_},//● ライトカップ
        0,//レベルの合計制限なし
        3,//３匹
        50,//ポケモンのレベル５０まで
        0,// 身長制限なし
        -99,// 体重９９ｋｇいか
        0,// 進化ポケモン参加できない
        0,// 特別なポケモン参加できない
        0,// 同じポケモン参加できない
        0,// 同じ道具持たせられない
        0,// 固定ダメージ技が必ず失敗
    },
    {
        {EOM_},//● ダブルカップ
        0,//　・レベルの合計制限無し
        4,//・３匹
        50,//　・ポケモンのレベル５０まで
        0,//・ 身長制限なし
        0,//・ 体重９９ｋｇいじょう
        1,//・ 進化ポケモン参加できる
        0,//・ 特別なポケモン参加できない
        0,//・ 同じポケモン参加できない
        0,//・ 同じ道具持たせられない
        0,// 固定ダメージ技が必ず失敗
    },
};


//----------------------------------------------------------
/**
 * @brief	レギュレーションデータへのポインタ取得
 * @param	セーブデータ保持ワークへのポインタ
 * @param	何本目のレギュレーションデータか
 * @return	REGULATION	ワークへのポインタ
 */
//----------------------------------------------------------
const REGULATION* Data_GetRegulation(SAVEDATA* pSave, int regNo)
{
	REGULATION_DATA* pRegData = NULL;

    if(regNo < NELEMS(_cup)){
        return &_cup[regNo];
    }
    pRegData = SaveData_Get(pSave, GMDATA_ID_REGULATION);
    return &pRegData->regulation_buff[0];  // 現状セーブデータには1本しかない
}

//----------------------------------------------------------
/**
 * @brief	レギュレーションデータへのポインタ取得
 * @param	セーブデータ保持ワークへのポインタ
 * @param	何本目のレギュレーションデータか
 * @param	REGULATION	ワークへのポインタ
 */
//----------------------------------------------------------
void Data_GetRegulationName(SAVEDATA* pSave, int regNo, STRBUF* pStrBuff, int HeapID)
{
    MSGDATA_MANAGER* msgman;
	REGULATION_DATA* pRegData = NULL;

    if(regNo < NELEMS(_cup)){
		msgman = MSGMAN_Create(MSGMAN_TYPE_NORMAL, ARC_MSG, NARC_msg_directbattlecorner_dat, HeapID);
        MSGMAN_GetString(msgman, msg_dbc_rule01+regNo, pStrBuff);
        MSGMAN_Delete(msgman);
    }
    else{
        Regulation_GetCupName(SaveData_GetRegulation(pSave,0), pStrBuff);
    }
}

