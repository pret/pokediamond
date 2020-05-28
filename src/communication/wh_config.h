/*
  Project:  NitroSDK - wireless_shared - demos - wh
  File:     wh_config.h

  Copyright 2003-2005 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.


  Revision 1.2  2005/02/28 05:26:35  yosizaki
  do-indent.

  Revision 1.1  2004/12/20 07:17:48  takano_makoto
  �A�v���P�[�V�������̖����ʐM�p�����[�^��wh_config.h�Ƃ��ĕ���

 */

#ifndef __WH_CONFIG_H__
#define __WH_CONFIG_H__

#include "communication/comm_def.h"


// �����Ŏg�p����DMA�ԍ�
#define WH_DMA_NO                 COMM_DMA_NO

// �ʏ�� MP �ʐM�Ŏg�p����|�[�g
#define WH_DATA_PORT              (4)  //14

// �ʏ�� MP �ʐM�Ŏg�p����D��x
#define WH_DATA_PRIO              WM_PRIORITY_NORMAL

// �f�[�^�V�F�A�����O�Ŏg�p����|�[�g
#define WH_DS_PORT                13

// MP�ʐM�݂̂̏ꍇ�̃f�[�^�T�C�Y
#define WH_MP_PARENT_DATA_SIZE           (192)
#define WH_MP_CHILD_DATA_SIZE           (12)

// �q�@���M�ʂ𑝂₷���ڂ̎q�@�{�e�@��
#define COMM_WIDE_BYTE_SEND_CHILDNUM   (5) //

#define WH_MP_4CHILD_DATA_SIZE         (38)  // �ܐl  //  (192/COMM_WIDE_BYTE_SEND_CHILDNUM) 


#endif // __WH_CONFIGH_H__
