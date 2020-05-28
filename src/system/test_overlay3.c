//==============================================================================
/**
 * @file	test_overlay3.c
 * @brief	オーバーレイテスト用ファイルその３
 * @author	matsuda
 * @date	2005.06.23(木)
 */
//==============================================================================
#include	<nitro.h>

void test_overlay_func_3(void);

void test_overlay_func_3(void)
{
	static int i = 0;
	++i;
	OS_Printf("here is func_3. called %d time%s.\n", i, (i == 1) ? "" : "s");
}

