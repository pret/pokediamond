//=============================================================================
/**
 * @file	gf_gx.c
 * @brief	NitroSDK��GX���C�u�����̃��b�p�[
 * @author	GAME FREAK Inc.
 * @date	2005.11.17
 */
//=============================================================================

#ifndef	__GF_GX_H__
#define	__GF_GX_H__
#include <nitro/gx.h>
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//������
extern void GF_GX_Init(void);
//�`�揈�����Z�b�g
extern void GF_G3X_Reset(void);
//SwapBuffer���N�G�X�g
extern void GF_G3_RequestSwapBuffers(GXSortMode am, GXBufferMode zw);
//SwapBuffer���s
extern void GF_G3_SwapBuffers(void);

#endif	//__GF_GX_H__
