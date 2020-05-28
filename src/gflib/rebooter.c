/*---------------------------------------------------------------------------*
  Project:  NitroSDK - TRIAL - tests - rebooter
  File:     main.c

  Copyright 2006 Nintendo.  All rights reserved.

  These coded instructions, statements, and computer programs contain
  proprietary information of Nintendo of America Inc. and/or Nintendo
  Company Ltd., and are protected by Federal copyright law.  They may
  not be disclosed to third parties or copied or duplicated in any form,
  in whole or in part, without the prior written consent of Nintendo.

  $Log: rebooter.c,v $
  Revision 1.2  2006/06/29 06:57:24  mitsuhara
  *** empty log message ***

  Revision 1.1  2006/06/26 03:23:26  shimizu
  *** empty log message ***

  $NoKeywords: $
 *---------------------------------------------------------------------------*/
#include <nitro.h>

#include <rebooter.h>
#include "hack.h"

void
rebooter_init()
{
// [for pokemon_dp download] ---
    /*
     * �N������ 1 �񂱂̊֐����Ăяo���Ă����܂�.
     * ���̏�����, ����ɋN�������{�̃v���O�������g�����
     * �ċN�������ʃv���O����������Ăяo���K�v������܂�.
     */
    NormalizeRomArchive();
}
// --- [for pokemon_dp download]


void
rebooter(const char *path)
{
	/*
	 * �Q�[���I����ʂ��N����, �w�肵���v���O���������u�[�g���܂�.
	 * ���u�[�g����s�������t�@�C����HW_ROM_BASE_OFFSET_BUF�Ɏw�肵�Ă����܂��B
	 */

	FSFile file;
	u32 prog_rom_base;

	FS_InitFile(&file);
	if (!FS_OpenFile(&file, path)) {
		OS_TPrintf("rebooter: cannot open file: %s\n", path);
		return;
	}

	prog_rom_base = FS_GetFileImageTop(&file);

	*(u32 *)HW_ROM_BASE_OFFSET_BUF = prog_rom_base;
	OS_ResetSystem(0);

	/* no return */
}
