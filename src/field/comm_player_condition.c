//=============================================================================
/**
 * @file	comm_player_condition.c
 * @bfief	通信プレーヤーの状態管理  playerにhasされる
 * @author	katsumi ohno
 * @date	05/10/19
 */
//=============================================================================

#include <nitro/os.h>
#include "common.h"
#include "gflib/blact.h"

#include "communication/communication.h"
#include "comm_field_state.h"
#include "underground/ug_manager.h"

#include "system/bmp_menu.h"
#include "worldmap.h"
#include "fieldobj.h"
#include "fieldsys.h"
#include "fld_bmp.h"

#include "player.h"
#include "comm_player.h"

#include "d_ohno.h"  // デバッグ用

#include <nnsys/g3d/glbstate.h>


//==============================================================================
// extern宣言
//==============================================================================
// ワーニングを表示させないため
#include "comm_player_condition.h"


#define _SEC(a)   (30*a)
#define _TIME_ENDRESS  (-1)      //状態を解くのが時間でない場合


//==============================================================================
// 構造体宣言
//==============================================================================

typedef struct _TAG_PLAYER_CONDITION {
    int downStep;	///<ダウンステップ
    int downTimer;
    u16 oldPad;   // 移動罠用
    u8 condition;  ///<状態
} PLAYER_CONDITION;


typedef struct _TAG_PLAYER_CONDITION_MGR {
    MATHRandContext32 sRand;
    PLAYER_CONDITION sPlayer[COMM_MACHINE_MAX];
} PLAYER_CONDITION_MGR;

static int _conditionTimeTbl[]={
    0,
    _TIME_ENDRESS, 
    _TIME_ENDRESS,
    _TIME_ENDRESS,
    _TIME_ENDRESS,
    _TIME_ENDRESS,
    _TIME_ENDRESS,
};

static int _conditionStepTbl[]={
    0,
    16,  // keyでとける
    0, 
    0, 
    0, 
    0, 
    0, 
};

//==============================================================================
// static method definition 
//==============================================================================
static void _setCondition(PLAYER_CONDITION* pCond, int condition);

   
//--------------------------------------------------------------
/**
 * 構造体のサイズ
 * @param	pMgr   管理構造体
 * @retval	none
 */
//--------------------------------------------------------------

int CommPlayCondGetWorkSize(void)
{
    return sizeof(PLAYER_CONDITION_MGR);
}

//--------------------------------------------------------------
/**
 * 状態の初期化
 * @param	pMgr   管理構造体
 * @retval	none
 */
//--------------------------------------------------------------

void CommPlayerCondInitialize(PLAYER_CONDITION_MGR* pMgr)
{
    int i;
    CommRandSeedInitialize(&pMgr->sRand);

    for(i = 0; i < COMM_MACHINE_MAX; i++){
        PLAYER_CONDITION* pCond = &pMgr->sPlayer[i];
        pCond->condition = PLAYER_COND_NONE;
        pCond->downTimer = 0;
    }
}

//--------------------------------------------------------------
/**
 * 状態の終了
 * @param	pMgr   管理構造体
 * @retval	none
 */
//--------------------------------------------------------------

void CommPlayerCondFinalize(PLAYER_CONDITION_MGR* pMgr)
{
    // 
}

//--------------------------------------------------------------
/**
 * 特定のプレーヤーの状態構造体を得る
 * @param	pMgr   管理構造体
 * @retval	none
 */
//--------------------------------------------------------------

PLAYER_CONDITION_PTR CommPlayerCondGetWork(PLAYER_CONDITION_MGR* pMgr,int netID)
{
    GF_ASSERT(netID < COMM_MACHINE_MAX);
    return &pMgr->sPlayer[netID];
}

//--------------------------------------------------------------
/**
 * 状態の終了
 * @param	pMgr   管理構造体
 * @retval	none
 */
//--------------------------------------------------------------

void CommPlayerCondStep(PLAYER_CONDITION_MGR_PTR pMgr)
{
    int i;
    
    for(i = 0; i < COMM_MACHINE_MAX; i++){
        PLAYER_CONDITION* pCond = &pMgr->sPlayer[i];
        if(pCond->downTimer > 0){
            pCond->downTimer--;
        }
        if(pCond->downTimer==0){
           pCond->condition = PLAYER_COND_NONE;
           // 状態が解ける処理
       }
    }
}


//--------------------------------------------------------------
/**
 * 特定の状態にする
 * @param	pCond   状態構造体
 * @retval	none
 */
//--------------------------------------------------------------

static void _setCondition(PLAYER_CONDITION* pCond, int condition)
{
    pCond->condition = condition;
    pCond->downTimer = _conditionTimeTbl[condition];
    pCond->downStep =  _conditionStepTbl[condition];
}

//--------------------------------------------------------------
/**
 * 目がくらくらする場合パッド情報を変更する
 * @param	pCond   状態構造体
 * @retval	none
 */
//--------------------------------------------------------------

void CommPlayerCondSetCondition(PLAYER_CONDITION* pCond, int condition)
{
    _setCondition(pCond, condition);

}

//--------------------------------------------------------------
/**
 * 普通の状態かどうか
 * @param	pCond   状態構造体
 * @retval	none
 */
//--------------------------------------------------------------

BOOL CommPlayerIsNormalCondition_ServerSide(PLAYER_CONDITION* pCond)
{
    if(PLAYER_COND_NONE == pCond->condition){
        return TRUE;
    }
    return FALSE;
}

//--------------------------------------------------------------
/**
 * 移動が自由な状況なのかどうか サーバー側での判断  = 罠にかかっている状態
 * @param	pCond   状態構造体
 * @retval	none
 */
//--------------------------------------------------------------

BOOL CommPlayerIsMoveCondition_ServerSide(PLAYER_CONDITION* pCond)
{
    if(PLAYER_COND_SMOG == pCond->condition){
        return FALSE;
    }
    else if(PLAYER_COND_STOP == pCond->condition){
        return FALSE;
    }
    else if(PLAYER_COND_FORCE_MOVE == pCond->condition){
        return TRUE;
    }
    else if(PLAYER_COND_GIDDY == pCond->condition){
        return TRUE;
    }
    else if(PLAYER_COND_HOLE == pCond->condition){
        return TRUE;
    }
    else if(PLAYER_COND_NONE == pCond->condition){
        return TRUE;
    }
    return FALSE;
}

//--------------------------------------------------------------
/**
 * あなはまり状態かどうか
 * @param	pCond   状態構造体
 * @retval	none
 */
//--------------------------------------------------------------

BOOL CommPlayerIsHoleCondition_ServerSide(PLAYER_CONDITION* pCond)
{
    if(PLAYER_COND_HOLE == pCond->condition){
        return TRUE;
    }
    return FALSE;
}

