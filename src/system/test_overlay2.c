//==============================================================================
/**
 * @file	test_overlay2.c
 * @brief	�I�[�o�[���C�e�X�g�p�t�@�C�����̂Q
 * @author	matsuda
 * @date	2005.06.20(��)
 */
//==============================================================================
#include	<nitro.h>

/*
 * NitroStaticInit() �� static initializer �Ɏw�肷��ɂ�
 * ���̃w�b�_���C���N���[�h���܂�.
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
 * @brief   static initializer �Ƃ��Ă̎����������֐�.
 */
//--------------------------------------------------------------
static void NitroStaticInit(void)
{
	static int i = 0;
	
	i++;
	OS_Printf("func2 StaticInit = %d\n", i);
}

