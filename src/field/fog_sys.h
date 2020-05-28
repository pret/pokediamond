//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		fog_sys.h
 *@brief	�t�H�O�V�X�e��
 *@author	tomoya takahashi
 *@data		2005.04.27
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

#ifndef __FOG_SYS_H__
#define	__FOG_SYS_H__

#undef	GLOBAL
#ifdef	__FOG_SYS_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

#include "nnsys.h"

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
 */
//-----------------------------------------------------------------------------
#define	FOG_MDL_SET_CHECK

//-------------------------------------
//	�R���g���[���萔
//=====================================
#define	FOG_SYS_FLAG	(1)		// on/off�t���O
#define	FOG_SYS_MODE	(1<<1)	// ���[�h
#define	FOG_SYS_SLOPE	(1<<2)	// ������
#define	FOG_SYS_OFFSET	(1<<3)	// �I�t�Z�b�g
#define	FOG_SYS_RGB		(1<<4)	// �F
#define	FOG_SYS_ALPHA	(1<<5)	// ���l
#define	FOG_SYS_TBL		(1<<6)	// �t�H�O�e�[�u��

#define	FOG_SYS_ALL		(0xffffffff)		// �S��

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
 */
//-----------------------------------------------------------------------------
typedef struct _FOG_DATA* FOG_DATA_PTR;		// �t�H�O�f�[�^�|�C���^


//----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	�t�H�O�f�[�^�ۑ��̈���쐬
//-------------------------------------
GLOBAL FOG_DATA_PTR	FogSys_Init(void);
GLOBAL void	FogSys_Delete(FOG_DATA_PTR* pFogData);

//-------------------------------------
//	���̃t�H�O�̏�Ԃ��擾
//-------------------------------------
GLOBAL BOOL GetFogFlag(FOG_DATA_PTR FogData);			// ON/OFF
GLOBAL int GetFogMode(FOG_DATA_PTR FogData);			// �t�H�O���[�h
GLOBAL int GetFogSlope(FOG_DATA_PTR FogData);			// ������
GLOBAL int GetFogOffset(FOG_DATA_PTR FogData);			// ������n�߂�f�v�X�l
GLOBAL GXRgb GetFogColor(FOG_DATA_PTR FogData);			// �t�H�O�J���[
GLOBAL int GetFogAlpha(FOG_DATA_PTR FogData);			// �t�H�O���l
GLOBAL const char* GetFogTbl(FOG_DATA_PTR FogData);		// �t�H�O�e�[�u��

//-------------------------------------
//	�t�H�O�f�[�^��ݒ�
//-------------------------------------
GLOBAL void SetFogData(FOG_DATA_PTR FogData, int cont, BOOL flag, int fogMode, int fogSlope, int offset);	// �t�H�O�f�[�^
GLOBAL void SetFogColor(FOG_DATA_PTR FogData, int cont, GXRgb color, int alpha);	// �t�H�O�J���[
GLOBAL void SetFogTbl(FOG_DATA_PTR FogData, const char* fog_tbl);		// �t�H�O�e�[�u��
//----------------------------------------------------------------------------
/**
 *					�O���[�o���ϐ��錾
 */
//-----------------------------------------------------------------------------

#undef	GLOBAL
#endif

