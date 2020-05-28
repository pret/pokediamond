//=============================================================================
/**
 * @file	comm_player_condition.h
 * @bfief	�ʐM�v���[���[�̏�ԊǗ�  player��has�����
 * @author	katsumi ohno
 * @date	05/10/19
 */
//=============================================================================

#ifndef __COMM_PLAYER_CONDITION_H__
#define __COMM_PLAYER_CONDITION_H__

//==============================================================================
//	enum
//==============================================================================
// ������Ԃ�����
typedef enum{
  PLAYER_COND_NONE,
  PLAYER_COND_GIDDY,   // �ډ񂵏��
  PLAYER_COND_SMOG,   // �����
  PLAYER_COND_FORCE_MOVE,  // �����ړ�
  PLAYER_COND_HOLE,  // ����
  PLAYER_COND_STOP,  // ��~
  PLAYER_COND_SLOW,  // ������ �̂낢
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
