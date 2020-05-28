//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		weather_sys_def.h
 *@brief	���V�C�V�X�e���\���̂̐錾
 *@author	tomoya takahashi
 *@data		2005.07.29
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __WEATHER_SYS_DEF_H__
#define __WEATHER_SYS_DEF_H__

#undef GLOBAL
#ifdef	__WEATHER_SYS_DEF_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------
// �e�V�C�̐���
typedef struct _WEATHER_SYS_CONTROL* WEATHER_CONT_PTR;		// �V�C����f�[�^�|�C���^

// �����s���̓V�C�@���̓V�C�ւ̃t�F�[�h�������Ǘ�
typedef struct _WEATHER_MANAGER* WEATHER_MANAGER_PTR;		// �V�C�V�X�e������}�l�[�W��

#undef	GLOBAL
#endif		// __WEATHER_SYS_DEF_H__

