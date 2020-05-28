/**
 *@file		effect_warppoint.h
 *@brief	���[�v�|�C���g�@�n���ړ�������炢�܂���
 *@author	k.ohno
 *@data		2006.06.21
 *
 */
#ifndef __EFFECT_WARPPOINT_H__
#define __EFFECT_WARPPOINT_H__

#include "fieldsys.h"


//----------------------------------------------------------------------------
/**
 *@brief	�n���}�b�v�t�F�[�h�G�t�F�N�g
 *@param	fsys	�t�B�[���h�V�X�e�����[�N
 *@param	no		�ォ����
 *@param	end		�I���`�F�b�N�t���O
 *@return	none
 */
//-----------------------------------------------------------------------------
extern void StartJumpPointEffect(FIELDSYS_WORK* fsys, BOOL bUp, BOOL* end);

#endif		// __EFFECT_WARPPOINT_H__

