//=============================================================================
/**
 * @file	communication.h
 * @brief	�ʐM�֘A�ŊO���Q�Ƃ��K�v�Ȋ�{�I�Ȃ��̂��`
 * @author	Katsumi Ohno
 * @date    2005.11.14
 */
//=============================================================================
#ifndef _COMMUNICATION_H_
#define _COMMUNICATION_H_

#include "comm_def.h"
#include "system/pms_data.h"


//ggid��`��wh.h�Ɉړ����܂���

// ���������f�o�b�O�v�����g����d�g��  ��������S���ɕύX
#ifndef OHNO_PRINT
#if 1 //(defined(DEBUG_ONLY_FOR_ohno) | defined(DEBUG_ONLY_FOR_tomoya_takahashi) | defined(DEBUG_ONLY_FOR_mituhara))
//#ifdef  SDK_DEBUG

#if 1
#define OHNO_SP_PRINT(...) \
  (void) ((OS_Printf(__VA_ARGS__)))
#define OHNO_PRINT(...)           ((void) 0)

#else
#define OHNO_PRINT(...) \
  (void) ((OS_Printf(__VA_ARGS__)))
#define OHNO_SP_PRINT(...)           ((void) 0)
#endif

#else   //DEBUG_ONLY_FOR_ohno

#define OHNO_PRINT(...)           ((void) 0)
#define OHNO_SP_PRINT(...)           ((void) 0)

#endif  // DEBUG_ONLY_FOR_ohno
#endif  //OHNO_PRINT

#define MYSTERY_BEACON_DATA_SIZE   (84)

// WMBssDesc��gameInfo.userGameInfo���g�p���Ă���󋵂̍\����
// WM_SIZE_USER_GAMEINFO  �ő� 112byte
// ����̉�c�ŕύX�ɂȂ�\��
// ���ł����Ɉ��z��
typedef struct{
  u32 		pokeID;     	// ID												8
  u8  		serviceNo;   	// �ʐM�T�[�r�X�ԍ�									9
  u8  		regulationNo;  	// �퓬���M�����[�V�������R���e�X�g�^�C�v�̎���		10
  u8  		connectNum;    	// �Ȃ����Ă���䐔  --> �{�e���ǂ�������			11
  u8 		soloDebugNo;  	// ���̐l�ƒʐM���Ȃ��悤�ɂ��邽�߂̔ԍ�			12
  PMS_DATA	pmsData;									// �ȈՉ�b�f�[�^		20
  u8  		myStatusBuff[COMM_SEND_MYSTATUS_SIZE];  	// ���ۂ�mystatus�̑傫���͎��s���łȂ��Ƃ킩��Ȃ��̂ŏ�ɐ؂��Ă���
  u8  		regulationBuff[COMM_SEND_REGULATION_SIZE];  // ���ۂ�reg�̑傫���͎��s���łȂ��Ƃ킩��Ȃ��̂ŏ�ɐ؂��Ă���
  // �퓬�̎��ȊO�͋󂢂Ă�̂ŁA���j�I�����[���̎q�@ID������鎖�ɂ���
  u32		UnionRoomTime;								// ���j�I�����[���ɓ����Ă��鎞�Ԃ�����������
  u8        pause;   // �ڑ����֎~���������Ɏg�p����
} _GF_BSS_DATA_INFO;

// ���p�̂ɕς��������������܂��UNION�̃\�[�X�ύX�������̂ŁA�ʍ\����
typedef struct{
  u32 		pokeID;     	// ID												8
  u8  		serviceNo;   	// �ʐM�T�[�r�X�ԍ�									9
  u8  		regulationNo;  	// �퓬���M�����[�V�������R���e�X�g�^�C�v�̎���		10
  u8  		connectNum;    	// �Ȃ����Ă���䐔  --> �{�e���ǂ�������			11
  u8 		soloDebugNo;  	// ���̐l�ƒʐM���Ȃ��悤�ɂ��邽�߂̔ԍ�			12
  u8 mysteryData[MYSTERY_BEACON_DATA_SIZE];
} _GF_BSS_MYSTERY;


#include "communication/comm_command.h"
#include "communication/comm_info.h"
#include "communication/comm_mp.h"
#include "communication/comm_system.h"
#include "communication/comm_recv.h"
#include "communication/comm_message.h"
#include "communication/comm_tool.h"
#include "communication/wm_icon.h"
#include "communication/comm_state.h"

// ���̐l�ƒʐM�ڑ����Ȃ��悤�ɂ��邽�߂̔ԍ�
#ifdef PM_DEBUG		//DebugROM
#if (defined(DEBUG_ONLY_FOR_ohno) | defined(DEBUG_ONLY_FOR_mituhara))
#define   SOLO_DEBUG_NO   (0)
#else
#define   SOLO_DEBUG_NO   (0)
#endif
#endif //PM_DEBUG

// �_�C���N�g�f�o�b�O�ʐM�����̂��̂ƍ������Ȃ��悤��
#define COMMDIRECT_DEBUG_NO  (2)


// �f�[�^�_���v
#ifdef PM_DEBUG
extern void CommDump_Debug(u8* adr, int length, char* pInfoStr);
#define DEBUG_DUMP(a,l,s)  CommDump_Debug(a,l,s)
#else
#define DEBUG_DUMP(a,l,s)       ((void) 0)
#endif

#endif //_COMMUNICATION_H_
