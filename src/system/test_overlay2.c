//==============================================================================
/**
 * @file	test_overlay2.c
 * @brief	オーバーレイテスト用ファイルその２
 * @author	matsuda
 * @date	2005.06.20(月)
 */
//==============================================================================
#include	<nitro.h>

/*
 * NitroStaticInit() を static initializer に指定するには
 * このヘッダをインクルードします.
 */
#include <nitro/sinit.h>

void test_overlay_func_2(void);

void test_overlay_func_2(void)
{
	static int i = 0;
	++i;
	OS_Printf("here is func_2. called %d time%s.\n", i, (i == 1) ? "" : "s");
}

//--------------------------------------------------------------
/**
 * @brief   static initializer としての自動初期化関数.
 */
//--------------------------------------------------------------
static void NitroStaticInit(void)
{
	static int i = 0;
	
	i++;
	OS_Printf("func2 StaticInit = %d\n", i);
}

