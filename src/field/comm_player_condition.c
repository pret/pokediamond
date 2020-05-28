//=============================================================================
/**
 * @file	comm_player_condition.c
 * @bfief	�ʐM�v���[���[�̏�ԊǗ�  player��has�����
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

#include "d_ohno.h"  // �f�o�b�O�p

#include <nnsys/g3d/glbstate.h>


//==============================================================================
// extern�錾
//==============================================================================
// ���[�j���O��\�������Ȃ�����
#include "comm_player_condition.h"


#define _SEC(a)   (30*a)
#define _TIME_ENDRESS  (-1)      //��Ԃ������̂����ԂłȂ��ꍇ


//==============================================================================
// �\���̐錾
//==============================================================================

typedef struct _TAG_PLAYER_CONDITION {
    int downStep;	///<�_�E���X�e�b�v
    int downTimer;
    u16 oldPad;   // �ړ�㩗p
    u8 condition;  ///<���
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
    16,  // key�łƂ���
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
 * �\���̂̃T�C�Y
 * @param	pMgr   �Ǘ��\����
 * @retval	none
 */
//--------------------------------------------------------------

int CommPlayCondGetWorkSize(void)
{
    return sizeof(PLAYER_CONDITION_MGR);
}

//--------------------------------------------------------------
/**
 * ��Ԃ̏�����
 * @param	pMgr   �Ǘ��\����
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
 * ��Ԃ̏I��
 * @param	pMgr   �Ǘ��\����
 * @retval	none
 */
//--------------------------------------------------------------

void CommPlayerCondFinalize(PLAYER_CONDITION_MGR* pMgr)
{
    // 
}

//--------------------------------------------------------------
/**
 * ����̃v���[���[�̏�ԍ\���̂𓾂�
 * @param	pMgr   �Ǘ��\����
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
 * ��Ԃ̏I��
 * @param	pMgr   �Ǘ��\����
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
           // ��Ԃ������鏈��
       }
    }
}


//--------------------------------------------------------------
/**
 * ����̏�Ԃɂ���
 * @param	pCond   ��ԍ\����
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
 * �ڂ����炭�炷��ꍇ�p�b�h����ύX����
 * @param	pCond   ��ԍ\����
 * @retval	none
 */
//--------------------------------------------------------------

void CommPlayerCondSetCondition(PLAYER_CONDITION* pCond, int condition)
{
    _setCondition(pCond, condition);

}

//--------------------------------------------------------------
/**
 * ���ʂ̏�Ԃ��ǂ���
 * @param	pCond   ��ԍ\����
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
 * �ړ������R�ȏ󋵂Ȃ̂��ǂ��� �T�[�o�[���ł̔��f  = 㩂ɂ������Ă�����
 * @param	pCond   ��ԍ\����
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
 * ���Ȃ͂܂��Ԃ��ǂ���
 * @param	pCond   ��ԍ\����
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

