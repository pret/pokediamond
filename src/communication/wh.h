/*
  Project:  NitroSDK - wireless_shared - demos - wh
  File:     wh.h

  Copyright 2003-2005 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  Revision 1.19  2005/04/26 02:35:02  terui
  Fix comment

  Revision 1.18  2005/03/25 03:05:28  seiki_masashi
  WEPKey �ݒ�֐���ݒ肷�� WH_Set{Parent,Child}WEPKeyGenerator ��ǉ�

  Revision 1.17  2005/03/04 09:18:56  takano_makoto
  WH_SetUserGameInfo��ǉ�

  Revision 1.16  2005/02/28 05:26:35  yosizaki
  do-indent.

  Revision 1.15  2004/12/22 02:49:08  terui
  �s�N�g�`���b�g�T�[�`�ɑΉ�

  Revision 1.14  2004/12/20 08:31:27  takano_makoto
  WH_Initialize���g�p���ď�����������Z�k����悤�ɕύX�B

  Revision 1.13  2004/12/20 07:17:20  takano_makoto
  WHReceiver��WHReceiverFunc�ɕύX�A������OS_Alloc���g�p����̂�r���A�A�v�����ɐݒ肷��p�����[�^��wh_config.h�Ƃ��ĕ���

  Revision 1.12  2004/11/16 03:01:11  takano_makoto
  WH_GetCurrentAid�֐���ǉ�

  Revision 1.11  2004/11/08 02:46:17  takano_makoto
  WM_EndScan�̑��d�Ăіh�~

  Revision 1.10  2004/11/05 04:27:40  sasakis
  ���r�[��ʁA�e�@�I����ʂ̒ǉ��ƁA����ɕK�v�ȉ����iscan�֘A�Ȃǁj�B

  Revision 1.9  2004/11/02 19:36:19  takano_makoto
  WH_StartMeasureChannel, WH_EndScan�̕Ԃ�l��BOOL�ɕύX

  Revision 1.8  2004/11/01 09:38:14  seiki_masashi
  WH_DS_DATA_SIZE �� 14 ���� 12 �ɕύX
  �R�����g�̏C��

  Revision 1.7  2004/11/01 09:16:47  takano_makoto
  WH�֐��̕Ԃ�l�̌^�ύX�AWH_SYSSTATE_FATAL��Ԃ�ǉ�

  Revision 1.6  2004/10/29 02:16:34  takano_makoto
  WH_StartScan�̈����ύX

  Revision 1.4  2004/10/28 07:11:20  takano_makoto
  WH_Connect�̊֐�����ύX

  Revision 1.3  2004/10/27 02:31:31  takano_makoto
  ����������MeasureChannel�n�֐��̓���
  WM_ERRCODE_OPERATING�ő҂ׂ�������WM_ERRCODE_SUCCESS�Ŕ��肵�Ă����s��C��
  ���̑��s��̏C��

  Revision 1.2  2004/10/25 02:29:54  seiki_masashi
  �e�q�ő呗�M�T�C�Y�� WH_CHILD_MAX �𔽉f
  �e�q�ő呗�M�T�C�Y�� WH_{PARENT,CHILD}_MAX_SIZE �ɓ���
  �R�����g�̒���

  Revision 1.1  2004/10/21 00:41:50  yosizaki
  Initial upload.

 */

/*
  Log : (from multiboot-model)
  Revision 1.6  2004/09/30 08:28:14  yosizaki
  add SDK_MAKEGGID_SYSTEM macro.

  Revision 1.5  2004/09/30 03:58:40  takano_makoto
  WH_SYSSTATE_CONNECT_FAIL��ǉ�

  Revision 1.4  2004/09/27 08:34:38  takano_makoto
  WH_ChildConnect, WH_Initialize�̃C���^�[�t�F�C�X�ύX

  Revision 1.3  2004/09/17 14:12:45  takano_makoto
  �ڑ��q�@�̔��胋�[�`����ǉ�.

  Revision 1.2  2004/09/17 10:29:47  takano_makoto
  WH_PARENT_MAX_SIZE, WH_CHILD_MAX_SIZE���`

  Revision 1.1  2004/09/16 14:07:11  takano_makoto
  Initial Update
*/

/*
  Revision 1.15  2004/10/06 05:11:35  sasakis
  �O���t�\���̒ǉ��ȂǁB

  Revision 1.14  2004/10/05 09:21:57  seiki_masashi
  WH_SendData �� callback ���w�肷��悤�ύX
  �萔�̕�����ϊ��֐��ɃG���[�`�F�b�N��ǉ�

  Revision 1.13  2004/10/01 01:58:54  seiki_masashi
  �ʏ�� MP �ʐM�֌W�̊֐���߂��܂���

  Revision 1.12  2004/09/30 08:46:48  seiki_masashi
  GGID �Ɋ���U��ꂽ�����Ȓl��ݒ�

  Revision 1.11  2004/09/30 06:26:49  seiki_masashi
  �ꎞ�I�ɒʏ�� MP �ʐM�֌W�̊֐����폜

  Revision 1.10  2004/09/30 06:20:03  seiki_masashi
  �C���f���g��ύX

  Revision 1.9  2004/09/30 06:16:38  seiki_masashi
  �ŐV�� SDK �̎d�l�ɏ�������悤�ύX

  Revision 1.8  2004/09/24 09:43:35  sasakis
  �ׂ����o�O�t�B�b�N�X���������B

  Revision 1.7  2004/09/24 06:12:35  sasakis
  �`�����l���蓮�I���@�\��ǉ��B

  Revision 1.6  2004/09/22 09:39:33  sasakis
  �f�o�O��ʂ�ǉ��B

  Revision 1.5  2004/09/15 10:23:40  sasakis
  �d�g��M���x�A�C�R���̒ǉ��ƁA�f�[�^�T�C�Y�ω��̂��߂̉����ȂǁB

  Revision 1.4  2004/09/10 08:44:52  sasakis
  �K�C�h���C�����������̒ǉ��A�G���[�֌W�̌������ȂǁB

  Revision 1.3  2004/09/08 08:55:35  sasakis
  �ؒf���������X���������B

  Revision 1.2  2004/09/08 01:52:52  sasakis
  �G���[�E�ؒf�֌W���ǁB

  Revision 1.1  2004/09/07 04:59:42  sasakis
  ���œo�^�B
*/


#ifndef __WMHIGH_H__
#define __WMHIGH_H__

#include "wh_config.h"

// �g�p���� GGID
#define _DP_GGID       (0x333)   // ���C����GGID
#define _MYSTERY_GGID  (0x333)
#define	_RANGER_GGID   (0x00000178)
#define	_WII_GGID      (0x346)   //
#define _BCON_DOWNLOAD_GGID (0x345)


// WM_Initialize���g�p���ď���������ꍇ��OFF
// WM_Init, WM_Enable, WM_PowerOn���ʂɎg�p���čׂ������䂷��K�v������ꍇ�ɂ�ON�ɐݒ肷��B
// #define WH_USE_DETAILED_INITIALIZE

enum
{
    WH_SYSSTATE_STOP,                  // �������
    WH_SYSSTATE_IDLE,                  // �ҋ@��
    WH_SYSSTATE_SCANNING,              // �X�L������
    WH_SYSSTATE_BUSY,                  // �ڑ���ƒ�
    WH_SYSSTATE_CONNECTED,             // �ڑ������i���̏�ԂŒʐM�\�j
    WH_SYSSTATE_DATASHARING,           // data-sharing�L���Őڑ�����
    WH_SYSSTATE_KEYSHARING,            // key-sharing�L���Őڑ�����
    WH_SYSSTATE_MEASURECHANNEL,        // �`�����l���̓d�g�g�p�����`�F�b�N
    WH_SYSSTATE_CONNECT_FAIL,          // �e�@�ւ̐ڑ����s
    WH_SYSSTATE_ERROR,                 // �G���[����
    WH_SYSSTATE_FATAL,                 // FATAL�G���[����
    WH_SYSSTATE_NUM
};

enum
{
    WH_CONNECTMODE_MP_PARENT,          // �e�@ MP �ڑ����[�h
    WH_CONNECTMODE_MP_CHILD,           // �q�@ MP �ڑ����[�h
    WH_CONNECTMODE_KS_PARENT,          // �e�@ key-sharing �ڑ����[�h
    WH_CONNECTMODE_KS_CHILD,           // �q�@ key-sharing �ڑ����[�h
    WH_CONNECTMODE_DS_PARENT,          // �e�@ data-sharing �ڑ����[�h
    WH_CONNECTMODE_DS_CHILD,           // �q�@ data-sharing �ڑ����[�h
    WH_CONNECTMODE_NUM
};

enum
{
    // ���O�̃G���[�R�[�h
    WH_ERRCODE_DISCONNECTED = WM_ERRCODE_MAX,   // �e����ؒf���ꂽ
    WH_ERRCODE_PARENT_NOT_FOUND,       // �e�����Ȃ�
    WH_ERRCODE_NO_RADIO,               // �����g�p�s��
    WH_ERRCODE_LOST_PARENT,            // �e����������
    WH_ERRCODE_NOMORE_CHANNEL,         // ���ׂẴ`�����l���̒������I����
    WH_ERRCODE_FATAL,
    WH_ERRCODE_MAX
};

typedef void (*WHStartScanCallbackFunc) (WMBssDesc *bssDesc);

/* ���ڑ�, �܂��͐e�@�������Ȃ���Ԃ������r�b�g�}�b�v�l */
#define WH_BITMAP_EMPTY           1

// ���M�R�[���o�b�N�^ (for data-sharing model)
typedef void (*WHSendCallbackFunc) (BOOL result);

// �ڑ�������֐��^ (for multiboot model)
typedef BOOL (*WHJudgeAcceptFunc) (WMStartParentCallback *);

// ggid�X�L�����R�[���o�b�N
typedef void (*fGGIDCallBack) (u32 ggid, int serviceNo);

// ��M�R�[���o�b�N�^
typedef void (*WHReceiverFunc) (u16 aid, u16 *data, u16 size);

// WEP Key �����֐�
typedef u16 (*WHParentWEPKeyGeneratorFunc) (u16* wepkey, const WMParentParam* parentParam);
typedef u16 (*WHChildWEPKeyGeneratorFunc) (u16* wepkey, const WMBssDesc* bssDesc);


typedef void (*WHdisconnectCallBack) (int aid);

extern void HWSetDisconnectCallBack(WHdisconnectCallBack callBack);

/**************************************************************************
 * �ȉ��́AWH �̊e��ݒ�l��ύX����֐��ł��B
 **************************************************************************/

/*---------------------------------------------------------------------------*
  Name:         WH_SetGgid

  Description:  �Q�[���O���[�vID��ݒ肵�܂��B
                �e�@�̐ڑ��O�ɌĂяo���܂��B

  Arguments:    ggid    �ݒ肷��Q�[���O���[�vID.

  Returns:      None.
 *---------------------------------------------------------------------------*/
extern void WH_SetGgid(u32 ggid);

/*---------------------------------------------------------------------------*
  Name:         WH_SetUserGameInfo

  Description:  ���[�U��`�̐e�@����ݒ肵�܂��B
                �e�@�̐ڑ��O�ɌĂяo���܂��B

  Arguments:    userGameInfo  ���[�U��`�̐e�@���ւ̃|�C���^
                length        ���[�U��`�̐e�@���̃T�C�Y

  Returns:      None.
 *---------------------------------------------------------------------------*/
extern void WH_SetUserGameInfo( u16* userGameInfo, u16 length );

/*---------------------------------------------------------------------------*
  Name:         WH_SetDebugOutput

  Description:  �f�o�b�O������o�͗p�̊֐���ݒ肵�܂��B

  Arguments:    func    �ݒ肷��f�o�b�O������o�͗p�̊֐�.

  Returns:      None.
 *---------------------------------------------------------------------------*/
void WH_SetDebugOutput(void (*func) (const char *, ...));

/*---------------------------------------------------------------------------*
  Name:         WH_SetParentWEPKeyGenerator

  Description:  WEP Key �𐶐�����֐���ݒ肵�܂��B
                ���̊֐����Ăяo���ƁA�ڑ����̔F�؂� WEP ���g���܂��B
                �Q�[���A�v���P�[�V�������Ƃ̃A���S���Y����
                �ڑ��O�ɐe�q�œ���̒l��ݒ肵�܂��B
                ���̊֐��͐e�@�p�ł��B

  Arguments:    func    WEP Key �𐶐�����֐��ւ̃|�C���^
                        NULL ���w�肷��� WEP Key ���g�p���Ȃ�

  Returns:      None.
 *---------------------------------------------------------------------------*/
extern void WH_SetParentWEPKeyGenerator(WHParentWEPKeyGeneratorFunc func);

/*---------------------------------------------------------------------------*
  Name:         WH_SetChildWEPKeyGenerator

  Description:  WEP Key �𐶐�����֐���ݒ肵�܂��B
                ���̊֐����Ăяo���ƁA�ڑ����̔F�؂� WEP ���g���܂��B
                �Q�[���A�v���P�[�V�������Ƃ̃A���S���Y����
                �ڑ��O�ɐe�q�œ���̒l��ݒ肵�܂��B
                ���̊֐��͎q�@�p�ł��B

  Arguments:    func    WEP Key �𐶐�����֐��ւ̃|�C���^
                        NULL ���w�肷��� WEP Key ���g�p���Ȃ�

  Returns:      None.
 *---------------------------------------------------------------------------*/
extern void WH_SetChildWEPKeyGenerator(WHChildWEPKeyGeneratorFunc func);


/**************************************************************************
 * �ȉ��́A�჌�C�� WM ���C�u�����̏�Ԃ��擾���郉�b�p�[�֐��ł��B
 **************************************************************************/

/* ----------------------------------------------------------------------
  Name:        WH_GetLinkLevel
  Description: �d�g�̎�M���x���擾���܂��B
  Arguments:   none.
  Returns:     WMLinkLevel �̐��l��Ԃ��܂��B
  ---------------------------------------------------------------------- */
extern int WH_GetLinkLevel(void);

/* ----------------------------------------------------------------------
   Name:        WH_GetAllowedChannel
   Description: �ڑ��Ɏg�p�o����`�����l���̃r�b�g�p�^�[�����擾���܂��B
   Arguments:   none.
   Returns:     channel pattern
   ---------------------------------------------------------------------- */
extern u16 WH_GetAllowedChannel(void);


/**************************************************************************
 * �ȉ��́AWH �̏�Ԃ��擾����֐��ł��B
 **************************************************************************/

/* ----------------------------------------------------------------------
   Name:        WH_GetBitmap
   Description: �ڑ���Ԃ������r�b�g�p�^�[�����擾���܂��B
   Arguments:   none.
   Returns:     bitmap pattern
   ---------------------------------------------------------------------- */
extern u16 WH_GetBitmap(void);

/* ----------------------------------------------------------------------
   Name:        WH_GetSystemState
   Description: WH �̓�����Ԃ��擾���܂��B
   Arguments:   none.
   Returns:     ������ԁiWH_SYSSTATE_XXXX�j�B
   ---------------------------------------------------------------------- */
extern int WH_GetSystemState(void);

/* ----------------------------------------------------------------------
   Name:        WH_GetConnectMode
   Description: �ڑ������擾���܂��B
   Arguments:   none.
   Returns:     �ڑ����iWH_CONNECTMODE_XX_XXXX�j�B
   ---------------------------------------------------------------------- */
extern int WH_GetConnectMode(void);

/* ----------------------------------------------------------------------
   Name:        WH_GetLastError
   Description: �ł��ŋ߂ɋN�����G���[�̃R�[�h���擾���܂��B
   Arguments:   none.
   Returns:     �G���[�R�[�h�B
   ---------------------------------------------------------------------- */
extern int WH_GetLastError(void);

/*---------------------------------------------------------------------------*
  Name:         WH_PrintBssDesc

  Description:  WMBssDesc �\���̂̃����o���f�o�b�O�o�͂���B

  Arguments:    info    �f�o�b�O�o�͂�����BssDesc�ւ̃|�C���^.

  Returns:      None.
 *---------------------------------------------------------------------------*/
extern void WH_PrintBssDesc(WMBssDesc *info);


/**************************************************************************
 * �ȉ��́A�`�����l���Ɋւ��鏈�����s���֐��ł��B
 **************************************************************************/

/*---------------------------------------------------------------------------*
  Name:         WH_StartMeasureChannel

  Description:  �g�p�\�ȑS�`�����l���œd�g�g�p���̒������J�n���܂��B
                ��������������ƁA�g�p�����Œ�̃`�����l��������Ōv�Z��
                ��Ԃ� WH_SYSSTATE_MEASURECHANNEL �Ɉڍs���܂��B

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
extern BOOL WH_StartMeasureChannel(void);

/*---------------------------------------------------------------------------*
  Name:         WH_GetMeasureChannel

  Description:  ���p�\�Ȓ������Ԏg�p���̒Ⴂ�`�����l����Ԃ��܂��B
                WH_MeasureChannel�̓��삪������WH_SYSSTATE_MEASURECHANNEL���
                �ɂȂ��Ă���K�v������܂��B
                ���̊֐����R�[�������ƈ�Ԏg�p���̒Ⴂ�`�����l����Ԃ�
                WH_SYSSTATE_IDLE��ԂɑJ�ڂ��܂��B
                
  Arguments:    None.

  Returns:      �����Ƃ��g�p���̒Ⴂ���p�\�ȃ`�����l���ԍ�.
 *---------------------------------------------------------------------------*/
extern u16 WH_GetMeasureChannel(void);


/**************************************************************************
 * �ȉ��́A���������������ĒʐM�\��Ԃ܂őJ�ڂ���֐��ł��B
 **************************************************************************/

/* ----------------------------------------------------------------------
   Name:        WH_Initialize
   Description: ��������Ƃ��s���A�������V�[�P���X���J�n���܂��B
   Arguments:   None.
   Returns:     �V�[�P���X�J�n�ɐ�������ΐ^�B
   ---------------------------------------------------------------------- */
extern BOOL WH_Initialize(void* pHeap);
/* ----------------------------------------------------------------------
   �q�[�v�̈�T�C�Y��Ԃ�
   ---------------------------------------------------------------------- */
extern int WH_GetHeapSize(void);

/*---------------------------------------------------------------------------*
  Name:         WH_TurnOnPictoCatch

  Description:  �s�N�g�`���b�g�T�[�`�@�\��L���ɂ���B
                WH_StartScan�ɂăX�L�������ɁA�s�N�g�`���b�g�𔭌������ꍇ�ɂ�
                �R�[���o�b�N�֐����Ă΂��悤�ɂȂ�B

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
extern void WH_TurnOnPictoCatch(void);

/*---------------------------------------------------------------------------*
  Name:         WH_TurnOffPictoCatch

  Description:  �s�N�g�`���b�g�T�[�`�@�\�𖳌��ɂ���B
                WH_StartScan�ɂăX�L�������ɁA�s�N�g�`���b�g�𔭌������ꍇ�ł�
                ���������悤�ɂȂ�B

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
extern void WH_TurnOffPictoCatch(void);

/*---------------------------------------------------------------------------*
  Name:         WH_StartScan

  Description:  �e�@�̃r�[�R�����擾����֐�

  Arguments:    callback - �e�@�������ɕԂ��R�[���o�b�N��ݒ肷��B
                
                macAddr  - �ڑ�����e�@��MAC�A�h���X���w��
                           0xFFFFFF�Ȃ�΂��ׂĂ̐e�@����������B
                           
                channel  - �e����������`�����l�����w��
                           0�Ȃ�΂��ׂẴ`�����l������������B

  Returns:      None.
 *---------------------------------------------------------------------------*/
extern BOOL WH_StartScan(WHStartScanCallbackFunc callback, const u8 *macAddr, u16 channel);


/*---------------------------------------------------------------------------*
  Name:         WH_EndScan

  Description:  �e�@�̃r�[�R�����擾����֐�

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
extern BOOL WH_EndScan(void);

/* ----------------------------------------------------------------------
  Name:        WH_ParentConnect
  Description: �ڑ��V�[�P���X���J�n���܂��B
  Arguments:   mode    - WH_CONNECTMODE_MP_PARENT �Ȃ�ΐe�@�Ƃ���MP�J�n�B
                         WH_CONNECTMODE_DS_PARENT �Ȃ�ΐe�@�Ƃ���DataSharing�J�n�B
                         WH_CONNECTMODE_KS_PARENT �Ȃ�ΐe�@�Ƃ���KeySharing�J�n�B
               tgid    - �e�@�ʐMtgid
               channel - �e�@�ʐMchannel
               maxEntry - �ő��t�q�@��
               beaconPeriod - �r�[�R���Ԋu �T�[�r�X�ɂ���Ďw�肷��
  Returns:     �ڑ��V�[�P���X�J�n�ɐ�������ΐ^�B
  ---------------------------------------------------------------------- */
extern BOOL WH_ParentConnect(int mode, u16 tgid, u16 channel,u16 maxEntry, u16 beaconPeriod,BOOL bEntry);

/* ----------------------------------------------------------------------
  Name:        WH_ChildConnect
  Description: �ڑ��V�[�P���X���J�n���܂��B
  Arguments:   mode -    WH_CONNECTMODE_MP_CHILD �Ȃ�Ύq�@�Ƃ���MP�J�n�B
                         WH_CONNECTMODE_DS_CHILD �Ȃ�Ύq�@�Ƃ���DataSharing�J�n�B
                         WH_CONNECTMODE_KS_CHILD �Ȃ�Ύq�@�Ƃ���KeySharing�J�n�B
               bssDesc - �ڑ�����e�@��bssDesc
               
  Returns:     �ڑ��V�[�P���X�J�n�ɐ�������ΐ^�B
  ---------------------------------------------------------------------- */
extern BOOL WH_ChildConnect(int mode, WMBssDesc *bssDesc);

/* ----------------------------------------------------------------------
   Name:        WH_ChildConnectAuto
   Description: �q�@�ڑ��V�[�P���X���J�n���܂��B
                �������AWH_ParentConnect �� WH_ChildConnect �Ŏw�肷��
                �e��ݒ������̎��������ɔC���܂��B
   Arguments:   mode    - WH_CONNECTMODE_MP_CHILD �Ȃ�Ύq�@�Ƃ���MP�J�n�B
                          WH_CONNECTMODE_DS_CHILD �Ȃ�Ύq�@�Ƃ���DataSharing�J�n�B
                          WH_CONNECTMODE_KS_CHILD �Ȃ�Ύq�@�Ƃ���KeySharing�J�n�B

                macAddr - �ڑ�����e�@��MAC�A�h���X���w��
                          0xFFFFFF�Ȃ�΂��ׂĂ̐e�@����������B
                          
                channel - �e����������`�����l�����w��
                          0�Ȃ�΂��ׂẴ`�����l������������B

  Returns:     �ڑ��V�[�P���X�J�n�ɐ�������ΐ^�B
   ---------------------------------------------------------------------- */
extern BOOL WH_ChildConnectAuto(int mode, const u8 *macAddr, u16 channel);

/*---------------------------------------------------------------------------*
  Name:         WH_SetJudgeAcceptFunc

  Description:  �q�@�̐ڑ��󂯓���𔻒肷�邽�߂̊֐����Z�b�g���܂��B

  Arguments:    �q�@�̐ڑ�����֐���ݒ�.

  Returns:      None.
 *---------------------------------------------------------------------------*/
extern void WH_SetJudgeAcceptFunc(WHJudgeAcceptFunc func);


/**************************************************************************
 * �ȉ��́AWH_DATA_PORT �|�[�g���g�p���钼�ړI�� MP �ʐM�̊֐��ł��B
 **************************************************************************/

/* ----------------------------------------------------------------------
   Name:        WH_SetReceiver
   Description: WH_DATA_PORT �|�[�g�Ƀf�[�^��M�R�[���o�b�N��ݒ肵�܂��B
   Arguments:   proc - �f�[�^��M�R�[���o�b�N
                port   �f�[�^���M�|�[�g
   Returns:     none.
   ---------------------------------------------------------------------- */
extern void WH_SetReceiver(WHReceiverFunc proc, int port);

/* ----------------------------------------------------------------------
   Name:        WH_SendData
   Description: WH_DATA_PORT �|�[�g�Ƀf�[�^���M���J�n���܂��B
               �iMP�ʐM�p�B�f�[�^�V�F�A�����O���ȂǂɌĂԕK�v�͂���܂���j
   Arguments:   size - �f�[�^�T�C�Y
   Returns:     ���M�J�n�ɐ�������ΐ^�B
   ---------------------------------------------------------------------- */
extern BOOL WH_SendData(void *data, u16 datasize, int port, WHSendCallbackFunc callback);


/**************************************************************************
 * �ȉ��́A�f�[�^�V�F�A�����O�ʐM�𐧌䂷��֐��ł��B
 **************************************************************************/

/* ----------------------------------------------------------------------
   Name:        WH_GetKeySet
   Description: ���L�L�[�f�[�^��ǂݏo���܂��B
   Arguments:   keyset - �f�[�^�i�[��w��
   Returns:     ��������ΐ^�B
   ---------------------------------------------------------------------- */
extern BOOL WH_GetKeySet(WMKeySet *keyset);

/* ----------------------------------------------------------------------
   Name:        WH_GetSharedDataAdr
  Description: �w��� aid �����}�V�����瓾���f�[�^�̃A�h���X��
                ���L�f�[�^�̃A�h���X����v�Z���擾���܂��B
   Arguments:   aid - �}�V���̎w��
   Returns:     ���s���� NULL �B
   ---------------------------------------------------------------------- */
extern u16 *WH_GetSharedDataAdr(u16 aid);

/* ----------------------------------------------------------------------
   Name:        WH_StepDS
   Description: �f�[�^�V�F�A�����O�̓�����1�i�߂܂��B
                ���t���[���ʐM����Ȃ�A���̊֐������t���[���ĂԕK�v��
                ����܂��B
   Arguments:   data - ���M����f�[�^
   Returns:     ��������ΐ^�B
   ---------------------------------------------------------------------- */
extern BOOL WH_StepDS(void *data);


/**************************************************************************
 * �ȉ��́A�ʐM���I�����ď�������Ԃ܂őJ�ڂ�����֐��ł��B
 **************************************************************************/

/* ----------------------------------------------------------------------
   Name:        WH_Reset
   Description: ���Z�b�g�V�[�P���X���J�n���܂��B
                ���̊֐����ĂԂƁA���̏�Ԃɍ\�킸���Z�b�g���܂��B
        �G���[����̋������A�p�ł��B
   Arguments:   none.
   Returns:     �����J�n�ɐ�������ΐ^�B
   ---------------------------------------------------------------------- */
extern void WH_Reset(void);

/* ----------------------------------------------------------------------
   Name:        WH_Finalize
   Description: �㏈���E�I���V�[�P���X���J�n���܂��B
                ���̊֐����ĂԂƁA���̏�Ԃ����ēK�؂ȏI���V�[�P���X��
                ���s���܂��B
                �ʏ�̏I�������ɂ́iWH_Reset�ł͂Ȃ��j���̊֐����g�p���܂��B
   Arguments:   None.
   Returns:     None.
   ---------------------------------------------------------------------- */
extern void WH_Finalize(void);

/*---------------------------------------------------------------------------*
  Name:         WH_End

  Description:  �����ʐM���I������B

  Arguments:    None.

  Returns:      None.
 *---------------------------------------------------------------------------*/
extern BOOL WH_End(void);

/*---------------------------------------------------------------------------*
  Name:         WH_GetCurrentAid

  Description:  ���݂̎�����AID���擾���܂��B
                �q�@�͐ڑ��E�ؒf���ɕω�����\��������܂��B

  Arguments:    None.

  Returns:      AID�̒l
 *---------------------------------------------------------------------------*/
extern u16 WH_GetCurrentAid(void);

/*---------------------------------------------------------------------------*
  Name:         WH_IsSysStateIdle
  Description:  �A�C�h����ԂɂȂ����̂��m�F����
                ���̏�Ԃɐi�ނ̂ŁA���̊m�F�̂��߂ɕK�v  k.ohno�ǉ�
  Arguments:    none
  Returns:      WH_SYSSTATE_IDLE�Ȃ�TRUE
 *---------------------------------------------------------------------------*/
extern BOOL WH_IsSysStateIdle(void);
extern BOOL WH_IsSysStateBusy(void);
extern BOOL WH_IsSysStateScan(void);

extern void WHSetGameInfo(void* pBuff, int size, int ggid, int tgid);

extern BOOL WHSetEntry(BOOL bEnable);

extern BOOL WHIsSetEntryEnd(void);

extern void WHSetLifeTime(BOOL bMinimum);

extern BOOL HWIsParentBeaconSent(void);

extern void WH_ParentDataInit(void);

extern void WH_SetMaxEntry(int maxEntry);

extern BOOL WH_IsSysStateError(void);

/*---------------------------------------------------------------------------*
  Name:         WHSetGGIDScanCallback
  Description:  GGID����������ׂ̃R�[���o�b�N�Z�b�g
  Arguments:    �R�[���o�b�N
  Returns:      none
 *---------------------------------------------------------------------------*/

extern void WHSetGGIDScanCallback(fGGIDCallBack callback);

extern void WHParentConnectPause(BOOL bPause);

/*---------------------------------------------------------------------------*
  Name:         WHChildConnectPause
  Description:  �e�@�ɓ����Ă�����̂�ؒf����
  Arguments:    �R�[���o�b�N
  Returns:      none
 *---------------------------------------------------------------------------*/
extern void WHChildConnectPause(BOOL bPause);
extern BOOL WHGetParentConnectPause(void);

/*---------------------------------------------------------------------------*
  Name:         WHParentConnectPauseSystem  �V�X�e����p
  Description:  �e�@�ɂ���ڑ����~�߂� �������͉���
  Arguments:    �~�߂� �������͉���
  Returns:      none
 *---------------------------------------------------------------------------*/

extern void WHParentConnectPauseSystem(BOOL bPause);

#endif
