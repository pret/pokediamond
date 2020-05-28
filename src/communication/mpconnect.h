#ifndef ___MPCONNECT_H___
#define ___MPCONNECT_H___
/**
 * @version "$Id: mpconnect.h,v 1.3 2006/08/11 06:30:17 mitsuhara Exp $"
 *
 * @file mpconnect.h
 * @brief MP�����ʐM���C�u����
 * 
 */
#ifdef __cplusplus
extern "C" {
#endif
  
#include    <nitro/types.h>
#include    <nitro/wm.h>
#include    <nitro/cht.h>

#ifdef PM_DEBUG
#ifndef		DEBUG_MP   
#define		DEBUG_MP	1
#endif
#else
#ifndef		DEBUG_MP   
#define		DEBUG_MP	0
#endif
#endif

#include "mpstruct.h"

  

//#define		MP_DEBUG_PRINT			1
  
/* �v�����g�o�͗}���_�~�[�֐� */
#ifdef  MP_DEBUG_PRINT
#define     MpPrintf			OS_TPrintf
#else
#define     MpPrintf(...)		((void) 0)
#endif

//#define		MP_DEBUG_STATE_PRINT		1

#ifdef  MP_DEBUG_STATE_PRINT
#define     MpStatePrintf		OS_TPrintf
#else
#define     MpStatePrintf(...)		((void) 0)
#endif


#define		MP_ERROR_CODE		(0xFFFFFFFF)

#define		MP_PORT_MIN	(4)  
#define		MP_PORT_MAX	(7)  

/**
 * ���C�u�����������p�\����
 *
 * �ڑ�ID����v���Ȃ�����Ƃ͒ʐM���s��Ȃ�
 */
typedef struct {
  u32 game_id		: 8;	/* �Q�[���^�C�g��ID */
  u32 game_version	: 4;	/* �Q�[���o�[�W���� */
  u32 language		: 4;	/* ����iOS_LANGUAGE�j */
  u32 connect_id	: 16;	/* �ڑ�ID */
  const u16* user_id;		/* �Q�[�����ł̃v���C���[ID (15�����ȓ�) */
  const u16* name;		/* �Q�[�����ł̃v���C���[�� (15�����ȓ�) */
} MpInitDesc;
  
    
/**
 * �ʐM���[�h��`
 */
typedef enum {
  MP_MODE_NONE = 0,
  MP_MODE_CHILD_MP,		/* MP�ʐM�Ńf�[�^�𑗐M�i�q�@�ɂȂ�^�ڑ���̑I����������j */
  MP_MODE_PARENT_MP,		/* MP�ʐM�Ńf�[�^����M�i�e�@�ɂȂ�j */
  MP_MODE_MAX
} MP_MODE;  




  
extern void MpProc(void);

  
extern BOOL MpIsConnect(void);


/**
 * �f�[�^�]���\�ȏ�Ԃ����ׂ�
 *
 * @return �ڑ��������TRUE��Ԃ�
 */
extern BOOL MpIsDataTrans(void);
  

/**
 * �������C�u�������g�p����o�b�t�@�T�C�Y��Ԃ�
 *
 * @return �o�C�g��
 */
extern u32 MpGetBufferSize(void);
  
  
/**
 * ���C�u����������
 *
 * @param init_desc �������f�[�^
 * @param buff ���C�u�����̎g�p����o�b�t�@�̃A�h���X���w�� MpGetBufferSize()�Ŏ擾����T�C�Y�̈悪�m�ۂ���Ă���K�v������
 */
extern void MpInit(MpInitDesc* init_desc, void* buff);


/**
 * �e�@�Ƃ��ĒʐM�J�n
 */
extern void MpRequestParent();


/**
 * �q�@�Ƃ��Đe�@�̃X�L�����J�n
 */
extern void MpRequestScan();


/**
 * �w��ڑ��ԍ��̐e�@�̃��[�U�[ID���擾
 *
 * @param num �e�@�ԍ�
 * @return ���O�iu16*�j
 */
extern u16* MpGetParentListUserID(u32 num);

       
/**
 * �w��ԍ��̐e�@�Ɛڑ��\�����ׂ�
 *
 * @param �e�@�ԍ�
 * @return �\�ȏꍇTRUE���Ԃ�
 */
extern BOOL MpGetConnectParentEnable(u32 num);


/**
 * �w��ԍ��̐e�@�Ɛڑ����� �ڑ��s�\�̏ꍇ�͉������Ȃ�
 *
 * @param num �e�@�ԍ�
 */
extern void MpConnectParent(u32 num);


/**
 * �e�@�Ƃ̐ڑ���؂� �ڑ����Ă��Ȃ��ꍇ�͉������Ȃ�
 */
extern void MpDisConnectParent(void);


/**
 * �S�Ă̎q�@�Ƃ̐ڑ���؂� �ڑ����Ă��Ȃ��ꍇ�͉������Ȃ�
 */
extern void MpDisConnectChild(void);

       
/**
 * �ڑ��ς݂̐e�@�ԍ���Ԃ� �ڑ���ԂɂȂ��ꍇ��MP_ERROR_CODE���Ԃ�
 *
 * @return �e�@�ԍ�
 */
extern u32 MpGetConnectParentNum(void);

  
/**
 * �w��ڑ��ԍ��̐e�@�̖��O���擾
 *
 * @param num �e�@�ԍ�
 * @return ���O�iu16*�j
 */
extern u16* MpGetParentListName(u32 num);


/**
 * �w��MAC�A�h���X�̎q�@�ȊO�Ƃ̐ڑ���؂� �ڑ����Ă��Ȃ��ꍇ�͉������Ȃ�
 *
 * @param num �q�@��MAC�A�h���X
 */
extern void MpConnectOnlyChild(u32 num);


/**
 * �w��ԍ��ȊO�̎q�@�Ƃ̐ڑ���؂� �ڑ����Ă��Ȃ��ꍇ�͉������Ȃ�
 *
 * @param num �q�@�ԍ�
 */
extern void MpDataTransOnlyChild(u32 num);
  
  
/**
 * �����N���x���擾
 *
 * @return �����N���x
 */
extern u32 MpGetConnectLinkLevel(void);


/**
 * �ڑ��\�ȍő吔���擾
 *
 * @return �ő吔
 */
extern u32 MpGetConnectListMax(void);

  
/**
 * �ڑ����ꂽ����Ԃ�
 *
 * @return �ڑ���
 */
extern u32 MpGetConnectListNum(void);


/**
 * �f�[�^�ʐM�\�Ȑ���Ԃ�
 *
 * @return �ڑ���
 */
extern u32 MpGetDataTransListNum(void);
  
  
/**
 * �w��ڑ��ԍ���MAC�A�h���X���擾
 *
 * @param num �ڑ��ԍ�
 * @return MAC�A�h���X
 */
extern u32 MpGetListMacAddr(u32 num);
extern u32 MpGetTransMacAddr(u32 num);


/**
 * �f�[�^�̑��M�������s��
 */
extern void MpSetSendRedy(void);
  
  
/**
 * ���[�U�[�f�[�^�̑��M���s��
 */
extern void MpSetSendUserData(void);

  
/**
 * �f�[�^�𑗐M���s��
 *
 * @param data �f�[�^���M�o�b�t�@
 * @param size ���M�T�C�Y
 * @param seq_num �ʐM�ԍ�
 */
extern void MpSetSendData(void *data, u32 size, u32 seq_num);


/**
 * �f�[�^����M���s��
 *
 * @param data �f�[�^��M�o�b�t�@
 * @param size ��M�T�C�Y
 * @param seq_num �ʐM�ԍ�
 */
extern void MpSetRecvData(void *data, u32 size, u32 seq_num);

  
/**
 * ���[�U�[�f�[�^�̎�M�o�b�t�@�T�C�Y��Ԃ�
 *
 * @return �o�C�g��
 */
extern u32 MpGetUserDataSize(void);

  
/**
 * �f�[�^�̎�M�������s��
 */
extern void MpSetRecvReady(void);


/**
 * ���[�U�[�f�[�^�̎�M���s�� ��M�o�b�t�@�T�C�Y��sizeof(MpUserGameInfoData)
 *
 * @param data �f�[�^��M�o�b�t�@
 */
extern void MpSetRecvUserData(void *data);

  
/**
 * ���M�����f�[�^�̃T�C�Y���擾����
 *
 * @return ���M�o�C�g��
 */
extern u32 MpGetSendDataSize(void);

       
/**
 * ��M�����f�[�^�̃T�C�Y���擾����
 *
 * @return ���M�o�C�g��
 */
extern u32 MpGetRecvDataSize(void);

  
/**
 * �f�[�^���M���I�����������ׂ�
 *
 * @return �I�����Ă���ꍇTRUE���Ԃ�
 */
extern BOOL MpIsSendDataEnd(void);


/**
 * �f�[�^��M���I�����������ׂ�
 *
 * @return �I�����Ă���ꍇTRUE���Ԃ�
 */
extern BOOL MpIsRecvDataEnd(void);
extern BOOL MpIsRecvDataAcknowledge(void);


/**
 * �ڑ�����Ă����Ԃ����ׂ�
 *
 * @return �ڑ��������TRUE��Ԃ�
 */
extern BOOL MpIsConnect(void);


/**
 * �������C�u������~�v��
 */
extern void MpRequestClose(void);


/**
 * �������C�u��������~���������ׂ�
 *
 * @return ��~��ԂɂȂ����ꍇTRUE���Ԃ�
 */
extern BOOL MpIsEnd(void);
  
  
#ifdef  __cplusplus
}       /* extern "C" */
#endif

#endif // ___TWL_H___
