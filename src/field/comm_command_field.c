//=============================================================================
/**
 * @file	comm_command_field.c
 * @brief	�f�[�^�𑗂邽�߂̃R�}���h���e�[�u�������Ă��܂�
 *          �t�B�[���h�p�ł�
 *          comm_command_field.h �� enum �Ɠ������тł���K�v������܂�
 * @author	Katsumi Ohno
 * @date    2005.11.07
 */
//=============================================================================

#include "common.h"
#include "communication/communication.h"
#include "comm_command_field.h"
#include "comm_field_state.h"

#include "field/fieldsys.h" //FIELDSYS_WORK
#include "system/mystatus.h"
#include "system/pms_data.h"
#include "savedata/trainercard_data.h"
#include "application/trainer_card.h"

// �R�[���o�b�N�֐�����������
#include "underground/ug_manager.h"
#include "comm_union.h"
#include "poketool/poke_tool.h"

#include "comm_vsroom.h"

#include "d_ohno.h"

//==============================================================================
//  �e�[�u���ɏ����֐��̒�`
//==============================================================================

//==============================================================================
//  static��`
//==============================================================================

static int _getTrainerCardSize(void);
static int _getCRECW(void);
static int _getCOECW(void);

static int _getThree(void)
{
    return 3;
}


//==============================================================================
//	�e�[�u���錾
//  comm_shar.h �� enum �Ɠ����Ȃ�тɂ��Ă�������
//  CALLBACK���Ă΂ꂽ���Ȃ��ꍇ��NULL�������Ă�������
//  �R�}���h�̃T�C�Y��Ԃ��֐��������Ă��炦��ƒʐM���y���Ȃ�܂�
//  _getZero�̓T�C�Y�Ȃ���Ԃ��܂��B_getVariable�͉σf�[�^�g�p���Ɏg���܂�
//==============================================================================
static const CommPacketTbl _CommPacketTbl[] = {
    {CommPlayerRecvPlace,         CommPlayerGetRecvPlaceSize ,  NULL},
    {CommPlayerRecvIDPlace,       CommPlayerGetRecvIDPlaceSize , NULL},
    {UgMgrRecvNPCTalk,       _getOne , NULL},//  CF_NPC_TALK,                  ///<  NPC�Ƃ̉�b
    {CommPlayerRecvOtherTalk,             _getZero,  NULL},
    {CommPlayerRecvOtherTalk_ServerSide,  _getOne,  NULL},
    {CommPlayerRecvCheckFieldMenuOpen, _getZero,  NULL},
    {CommUnderRecvCheckAbutton,    CommUnderRecvCheckAbuttonSize,  NULL},
    {CommPlayerRecvResultFieldMenuOpen, _getVariable,    NULL},
    {CommPlayerRecvResultUGMenuOpen,    _getVariable,    NULL},
    {CommUgRecvChildStateNormal,    _getZero,  NULL},
    {CommTrapInfoRecvTrapData,    _getOne,  NULL},
    {CommTrapInfoRecvTrapDataDel, CommTrapInfoGetTrapDataDelSize,   NULL},
    {CommTrapInfoRecvTrapDataResult,    CommTrapInfoGetTrapDataResultSize,  NULL},
    {CommTrapInfoRecvArrayData,   CommTrapInfoGetTrapDataSize ,NULL},
    {CommTrapInfoRecvResult,      CommTrapInfoGetResultSize , NULL},
    {CommTrapRecvStart,           CommTrapGetStartSize ,      NULL},
    {CommTrapRecvSecondStart,     _getOne ,      NULL},
    {CommTrapRecvSecondStartRet,     _getThree ,      NULL},
    {CommTrapRecvPriEnd,           _getOne,      NULL},
    {CommTrapRecvEnd,             _getZero,      NULL},
    {CommTrapRecvEndResult,       CommTrapGetEndResultSize,     NULL},
    {CommTrapRecvForceEnd,             _getZero,      NULL},
    {CommTrapRecvRelease,         CommTrapGetReleaseSize,      NULL},
    {CommTrapRecvTrapingArray,   _getOne, NULL},
    {UgTrapRecvNatureRadar,         _getZero,     NULL},
    {UgTrapRecvNatureRadarPos,       UgTrapGetNatureTrapRadarSize ,  NULL},
    {CommTrapInfoRecvTouch,       CommTrapInfoGetTouchSize , NULL},
    {UgManagerRecvTouchResult1, _getVariable ,            NULL},
    {UgManagerRecvTouchResult2, _getVariable ,             NULL},
    {CommTrapInfoRecvTrapDefuse,    CommTrapInfoRecvTrapDefuseSize, NULL},
    {CommPlayerRecvDelete,        _getOne,      NULL},
    {CommSecretBaseInfoRecvData,  CommSecretBaseInfoGetDataSize,NULL},
    {CommSecretBaseInfoRecvDataServer,   CommSecretBaseInfoGetDataSize ,NULL},
    {CommSecretBaseInfoRecvPos,    CommSecretBaseInfoGetPosSize,  NULL},
    {CommSecretBaseInfoRecvJumpEnd,   _getZero,  NULL},
    {CommSecretBaseInfoRecvRetJump,   CommSecretBaseInfoGetRetJumpSize,NULL},
    {UgSecretBaseRecvJumpEvent,   UgSecretBaseRecvJumpEventSize,NULL},
    {UgSecretBaseRecvJumpEventRes,   UgSecretBaseRecvJumpEventResSize,NULL},
    {UgSecretBaseRecvGoodsCheck,   UgSecretBaseGetRecvGoodsCheckSize, NULL},
    {UgSecretBaseRecvMoveFailed,   _getOne, NULL},
    {CommPlayerRecvMoveControl,   _getOne, NULL},
    {CommDigStoneRecvPickUp,      _getOne, NULL},
    {CommFossilRecvFind,     _getOne,  NULL},
    {CommFossilRecvDigStartReq,     _getOne,  NULL},
    {CommFossilRecvDigStart,     _getOne,  NULL},
    {CommFossilRecvDigEndReq,     _getOne,  NULL},
    {CommFossilRecvDigPos,  CommFossilGetDigPosSize ,  NULL},
    {CommFossilRecvDigPosReturn,  CommFossilGetDigPosReturnSize ,NULL},
    {UgInitialDataRecv, UgInitialDataSendSize, NULL}, //CF_DIG_FOSSIL_INIT
    {UgFossilRecvPcRadar,  _getZero ,  NULL},
    {UgFossilRecvPcRadarPos,  UgFossilGetPcRadarSize ,NULL},
    {CommUnderTalkRecvAskSeq,  CommUnderTalkGetSeqCommandSize,   NULL},
    {CommUnderTalkRecvTalkSeq, CommUnderTalkGetSeqCommandSize,   NULL},
    {CommUnderTalkRecvAskSeqCall,  CommUnderTalkGetSeqCommandSize,   NULL},
    {CommUnderTalkRecvTalkSeqCall, CommUnderTalkGetSeqCommandSize,   NULL},
    {CommUnderTalkRecvSendItem,     CommUnderTalkGetSendItemSize,   NULL},
    {CommUnderTalkRecvSendItemCall, CommUnderTalkGetSendItemSize, NULL},
    {UgTalkRecvSecretQ,     UgTalkGetSecretQSize,  NULL},
    {UgTalkRecvSecretQCall, UgTalkGetSecretQSize, NULL},
    {UgRecordRecvTargetData,     _getVariable,  NULL},
    {UgRecordRecvTargetDataCall, _getVariable,  NULL},
    {CommUnderPCRecvAccess,  CommUnderPCGetAccessSize,  NULL},
    {CommPlayerRecvFlagState,  _getOne, NULL},
    {CommPlayerRecvFlagStateServerRet,  CommPlayerRecvFlagStateServerRetGetSize,  NULL},
    {CommSecretBaseRecvDrillStart,   _getOne, NULL},
    {CommSecretBaseRecvDrillStartResult,   CommSecretBaseDrillStartResultSize, NULL},
    {CommDCRecvTrainerCard, _getTrainerCardSize,   	CommDCGetTrainerCardRecvBuff},
    {UgPcRecvFlagGet,     CommUnderPCGetAccessSize,  NULL},  //CF_GET_FLAG,       
    {UgPcRecvFlagGetRet, CommUnderPCGetAccessSize,  NULL},  //CF_GET_FLAG_RET,   
    {CommPlayerRecvNowFlagDataReq, CommPlayerNowFlagSize,  NULL},  //CF_FLAG_NOWARRAY_REQ,   
    {CommPlayerRecvNowFlagDataArray, CommPlayerNowFlagDataArraySize,  CommPlayerGetFlagRecvBuff},  //CF_FLAG_NOWARRAY,
    {CommPlayerRecvNowFlagDataEnd, _getOne,  NULL},  //CF_FLAG_NOWARRAY_END,
    {CommPlayerRecvStartLineSet, _getOne, NULL}, //CF_DIRECT_START_SET,
    {CommDirectRecvStartPos, _getOne, NULL}, //CF_DIRECT_STARTPOS,
    {UgSBRecvLVUPFlag, _getOne, NULL},  //CF_LVUP_FLAG,           ///< �p�\�R��LVUP
    {UgSBRecvLVUPFlagRet, UgSBGetLVUPFlagRetSize, NULL},  //CF_LVUP_FLAG_RET,       ///< �p�\�R��LVUP

    {CommUnionRecvStatus,				MyStatus_GetWorkSize,	NULL},
    {CommUnionRecvSelect,  				_getOne,                NULL},
    {CommUnionRecvTalk,    				_getOne,                NULL},
    {CommUnionRecvBattlePokeListResult, _getOne,				NULL},
    {CommUnionRecvNo,      				_getZero,               NULL},
    {CommUnionStartNext,   				_getOne,               	NULL},
    {CommUnionEndConnect,  				_getZero,              	NULL},
    {CommUnionRecvTrainerCard, 			_getTrainerCardSize,   	getTrainerCardRecvBuff},

    { CommMixBattleRecv, CommMixBattleGetDataSize, CommMixBattleGetBuffer },
    { CommMixBattleTradeRecv, _getOne, NULL },

	{ CommDummyCallBack, _getOne, NULL},// ���R�[�h�R�[�i�[�p�̃e�[�u��
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getOne, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getCRECW, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getZero, NULL},
    { CommDummyCallBack, _getRecordSize, NULL},
    { CommDummyCallBack, _getOne, NULL},
    
    
    { CommDummyCallBack, _getPictureSize, NULL},// ���������p�̃e�[�u��
    { CommDummyCallBack, _getLinePosSize,    NULL},
    { CommDummyCallBack, _getLinePosServerSize, NULL},
    { CommDummyCallBack, _getOne,            NULL},
    { CommDummyCallBack, _getOne,            NULL},
    { CommDummyCallBack, _getOne,            NULL},
    { CommDummyCallBack, _getZero,           NULL},
    { CommDummyCallBack, _getZero,           NULL},
    { CommDummyCallBack, _getCOECW,          NULL},
    { CommDummyCallBack, _getZero,           NULL},
    { CommDummyCallBack, _getZero,			 NULL},
    { CommDummyCallBack, _getZero,			 NULL},


};



//--------------------------------------------------------------
// �������Ȃ��_�~�[�̃R�[���o�b�N
//--------------------------------------------------------------
void CommDummyCallBack( int netID, int size, void* pBuff, void* pWork )
{

}

//--------------------------------------------------------------
/**
 * @brief   �t�B�[���h�p�̃R�}���h�̌n�ɏ��������܂�
 * @param   none
 * @retval  none
 */
//--------------------------------------------------------------

void CommCommandFieldInitialize(void* pWork)
{
    int length = sizeof(_CommPacketTbl)/sizeof(CommPacketTbl);
    CommCommandInitialize(_CommPacketTbl, length, pWork);
}

//--------------------------------------------------------------------------------
// �g���[�i�[�J�[�h�̑傫����\���֐�
//--------------------------------------------------------------------------------
static int _getTrainerCardSize(void)
{
	return sizeof(TR_CARD_DATA);
	
}

//--------------------------------------------------------------------------------
// ���R�[�h�f�[�^�̑傫����\���֐�
//--------------------------------------------------------------------------------
int _getRecordSize(void)
{
	return (3000+8);
}


//--------------------------------------------------------------------------------
// �`��ς݉摜�̃T�C�Y��\���i���M�ʃM���M�����`�j
//--------------------------------------------------------------------------------
int _getPictureSize(void)
{
	return 1008;
}

//--------------------------------------------------------------------------------
// �T�l�ڑ��̎��ɁA�q�@�����M�ł���ő�p�P�b�g�T�C�Y
//--------------------------------------------------------------------------------

#define COMM_SEND_5TH_PACKET_MAX	( 10 )
#define OEKAKI_MEMBER_MAX			(  5 )

int _getLinePosSize(void)
{
	return COMM_SEND_5TH_PACKET_MAX;
}

int _getLinePosServerSize(void)
{
	return COMM_SEND_5TH_PACKET_MAX*OEKAKI_MEMBER_MAX;
}

//--------------------------------------------------------------------------------
// �o�C�g��\���֐�
//--------------------------------------------------------------------------------
static int _getCRECW(void)
{
	return 4;	//COMM_RECORD_END_CHILD_WORK
}

//--------------------------------------------------------------------------------
// �o�C�g��\���֐�
//--------------------------------------------------------------------------------
static int _getCOECW(void)
{
	return 4;	//COMM_OEKAKI_END_CHILD_WORK
}



#ifdef PM_DEBUG

static BOOL _debugChannelDisp = FALSE;

void DebugOhnoCommDebugDisp(void* pDummy)
{
    _debugChannelDisp = 1 - _debugChannelDisp;
    FieldSystemProc_SeqHoldEnd();		
}

BOOL DebugOhnoGetCommDebugDisp(void)
{
    return _debugChannelDisp;
}

#endif
