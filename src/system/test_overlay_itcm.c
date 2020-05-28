//==============================================================================
/**
 * @file	test_overlay_itcm.c
 * @brief	ITCMへのオーバーレイテスト用ファイル
 * @author	matsuda
 * @date	2005.06.20(月)
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
