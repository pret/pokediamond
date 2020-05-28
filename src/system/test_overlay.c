//==============================================================================
/**
 * @file	test_overlay.c
 * @brief	�I�[�o�[���C�e�X�g�p�t�@�C��
 * @author	matsuda
 * @date	2005.06.20(��)
 */
//==============================================================================
#include	<nitro.h>
#include "common.h"

static const vu32 dummy_data[8] = {20, 20, 20};

static int i = 0;

void test_overlay_func_1(void);

void test_overlay_func_1(void)
{
	static int s = 0;
	
	++i;
	s++;
	OS_Printf("here is func_1. called %d time%s.\n", i, (i == 1) ? "" : "s");
	OS_Printf("here is func_1. local_s = %d\n", s);
}

