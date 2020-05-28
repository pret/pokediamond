//=============================================================================
/**
 * @file	comm_player_condition.h
 * @bfief	通信プレーヤーの状態管理  playerにhasされる
 * @author	katsumi ohno
 * @date	05/10/19
 */
//=============================================================================

#ifndef __COMM_PLAYER_CONDITION_H__
#define __COMM_PLAYER_CONDITION_H__

//==============================================================================
//	enum
//==============================================================================
// 内部状態を示す
typedef enum{
  PLAYER_COND_NONE,
  PLAYER_COND_GIDDY,   // 目回し状態
  PLAYER_COND_SMOG,   // 霧状態
  PLAYER_COND_FORCE_MOVE,  // 強制移動
  PLAYER_COND_HOLE,  // あな
  PLAYER_COND_STOP,  // 停止
  PLAYER_COND_SLOW,  // おそい のろい
};

//==============================================================================
//	typedef
//==============================================================================
typedef struct _TAG_PLAYER_CONDITION* PLAYER_CONDITION_PTR;
typedef struct _TAG_PLAYER_CONDITION_MGR* PLAYER_CONDITION_MGR_PTR;
typedef struct _TAG_PLAYER_CONDITION_MGR PLAYER_CONDITION_MGR_ORG;


extern int CommPlayCondGetWorkSize(void);
extern void CommPlayerCondInitialize(PLAYER_CONDITION_MGR_PTR pMgr);
extern void CommPlayerCondFinalize(PLAYER_CONDITION_MGR_PTR pMgr);
extern PLAYER_CONDITION_PTR CommPlayerCondGetWork(PLAYER_CONDITION_MGR_PTR pMgr, int netID);
extern void CommPlayerCondStep(PLAYER_CONDITION_MGR_PTR pMgr);
extern void CommPlayerCondSetCondition(PLAYER_CONDITION_PTR pCond, int condition);
extern u16 CommPlayerCondGetFakePad(PLAYER_CONDITION_MGR_PTR pMgr,
                                    int netID, u16 normalPad);
extern BOOL CommPlayerIsMoveCondition_ServerSide(PLAYER_CONDITION_PTR pCond);
extern BOOL CommPlayerIsNormalCondition_ServerSide(PLAYER_CONDITION_PTR pCond);
extern BOOL CommPlayerIsHoleCondition_ServerSide(PLAYER_CONDITION_PTR pCond);


#endif //__COMM_PLAYER_CONDITION_H__
