//==============================================================================
/**
 * @file	test_overlay_itcm.c
 * @brief	ITCM�ւ̃I�[�o�[���C�e�X�g�p�t�@�C��
 * @author	matsuda
 * @date	2005.06.20(��)
 */
//==============================================================================
#include	<nitro.h>

static int i = 0;

void test_overlay_itcm(void);

void test_overlay_itcm(void)
{
	++i;
	OS_Printf("here is func_itcm. called %d time%s.\n", i, (i == 1) ? "" : "s");
}
