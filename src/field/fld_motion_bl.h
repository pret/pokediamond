//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		fld_motion_bl.h
 *@brief	�t�B�[���h��僂�[�V�����u���[
 *@author	tomoya takahashi
 *@data		2005.07.28
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __FLD_MOTION_BL_H__
#define __FLD_MOTION_BL_H__

#include "motion_bl.h"

#undef GLOBAL
#ifdef	__FLD_MOTION_BL_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
typedef struct _FLD_MOTION_BL_DATA* FLD_MOTION_BL_DATA_PTR;


//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
GLOBAL FLD_MOTION_BL_DATA_PTR FLDMotionBl_Init(int eva, int evb);	// ���[�V�����u���[���g�p���鏀��������
GLOBAL void FLDMotionBl_Delete(FLD_MOTION_BL_DATA_PTR* data);		// ���[�V�����u���[���g�p���鏀��������
GLOBAL void FLDMotionBl_ParamChg(FLD_MOTION_BL_DATA_PTR data, int eva, int evb); // �p�����[�^�[Change

#undef	GLOBAL
#endif		// __FLD_MOTION_BL_H__

