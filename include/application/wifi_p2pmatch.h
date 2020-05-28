//============================================================================================
/**
 * @file	wifi_p2pmatch.h
 * @bfief	WIFI P2P�ڑ��̃}�b�`���O
 * @author	k.ohno
 * @date	06.04.07
 */
//============================================================================================
#ifndef __WIFI_P2PMATCH_H__
#define __WIFI_P2PMATCH_H__

#include "application/wifi_p2pmatch_def.h"

//============================================================================================
//	��`
//============================================================================================

//------------------------------------------------------
/**
 * WIFI�Ƃ��������X�gPROC�p�����[�^
 */
//------------------------------------------------------
typedef struct {
	SAVEDATA*  pSaveData;
    int seq;                // �ǂ��ɕ��򂵂Ăق������������Ă���
    int targetID;   //�ΐ� ��������l���N�Ȃ̂��������Ă���
}WIFIP2PMATCH_PROC_PARAM;

// �v���Z�X��`�f�[�^
extern PROC_RESULT WifiP2PMatchProc_Init( PROC * proc, int * seq );
extern PROC_RESULT WifiP2PMatchProc_Main( PROC * proc, int * seq );
extern PROC_RESULT WifiP2PMatchProc_End( PROC * proc, int * seq );

// �|�C���^�Q�Ƃ����ł��郌�R�[�h�R�[�i�[���[�N�\����
typedef struct _WIFIP2PMATCH_WORK WIFIP2PMATCH_WORK;	

// �Ăяo�����߂̃C�x���g
extern void EventCmd_P2PMatchProc(GMEVENT_CONTROL * event);
// ���E�����O�ɌĂяo�����߂̃C�x���g
extern void EventCmd_DPWInitProc(GMEVENT_CONTROL * event);
//
extern void EventCmd_DPWInitProc2(GMEVENT_CONTROL * event, u16* ret);


#endif //__WIFI_P2PMATCH_H__
