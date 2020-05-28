//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		weather_sys.h
 *@brief	���V�C�V�X�e��
 *@author	tomoya takahashi
 *@data		2005.04.25
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]



#ifndef __WEATHER_SYS_H__
#define	__WEATHER_SYS_H__

#include "include/field/weather_no.h"
#include "field_common.h"
#include "weather_sys_def.h"

#undef	GLOBAL
#ifdef	__WEATHER_SYS_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif



//-----------------------------------------------------------------------------
/**
 *
 *					�V�C�Ǘ��V�X�e��
 * 
 */
//-----------------------------------------------------------------------------
//-------------------------------------
//	�V�C���g�p����q�[�v�̍쐬
//=====================================
GLOBAL void WEATHER_CreateHeap( u32 heapid );
GLOBAL void WEATHER_DeleteHeap( void );

//-------------------------------------
// �V�C�Ǘ��V�X�e����{����֐�
//=====================================
GLOBAL WEATHER_MANAGER_PTR WEATHER_Init( FIELDSYS_WORK * fsys );	// ������(�ŏ��ɂP��)
GLOBAL void WEATHER_Delete( WEATHER_MANAGER_PTR pWes );				// �j���i�Ō�ɂP��j

//-------------------------------------
// �V�C	�ύX
//=====================================
GLOBAL void WEATHER_Set( WEATHER_MANAGER_PTR pWes, int no );		// �V�C�ݒ�@�����Ɏw�肵���V�C�ɂȂ�܂��B
GLOBAL BOOL WEATHER_ChengeReq( WEATHER_MANAGER_PTR pWes, int no );	// �V�C�ύX���N�G�X�g�@���܂ł̓V�C���t�F�[�h�A�E�g�����A���X�Ɏw�肵���V�C�ɂȂ�܂��B
GLOBAL BOOL WEATHER_ChengeReqWithLast( WEATHER_MANAGER_PTR pWes, int no );	// �V�C�ύX���N�G�X�g�@���܂ł̓V�C���t�F�[�h�A�E�g�����A���X�Ɏw�肵���V�C�ɂȂ�܂��B
GLOBAL u32 WEATHER_GetNow( WEATHER_MANAGER_PTR pWes );





//-----------------------------------------------------------------------------
/**
 *
 *				�V�C�V�X�e��
 *
 */
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
 */
//-----------------------------------------------------------------------------

//-------------------------------------
//	�V�C�Ǘ��֐��O���R���g���[��	(cont)
//=====================================
enum{
	WEATHER_SYS_INIT=0,			// ������(�L�����N�^�t�@�C���Ȃǂ̓ǂݍ��݂��s���Ă��܂��B)
	WEATHER_SYS_INIT_DIV,		// �����������i�L�����N�^�t�@�C���Ȃǂ̓ǂݍ��݂𕡐��V���N���g�p���ď������܂��B�j
	WEATHER_SYS_START,			// ����J�n�i�t�F�[�h���Ȃ���͂��܂�j
	WEATHER_SYS_START_NOFADE,	// �t�F�[�h�����J�n
	WEATHER_SYS_START_WITHFOG,	// �t�H�O���c�����܂܃t�F�[�h�J�n
	WEATHER_SYS_END,			// ����I��(�t�F�[�h���ďI���)
	WEATHER_SYS_END_NOFADE,		// �t�F�[�h�����I��
	WEATHER_SYS_END_NOFOG,		// �t�H�O���c�����܂܃t�F�[�h�I��
	WEATHER_SYS_DEST			// �j��(�Ǘ��^�X�N���I�������A�ǂݍ��񂾃t�@�C����j�����܂��B)
};

//-------------------------------------
//	MoveFlag�p�萔
//		���̓V�C�R���g���[�����
//=====================================
enum{
	WEATHER_SYS_MOVE_NONE,		// �����Ă��Ȃ�
	WEATHER_SYS_MOVE_INIT,		// ��������
	WEATHER_SYS_MOVE_READY,		// �J�n�҂�
	WEATHER_SYS_MOVE_DO,		// ���s��
};


//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
 */
//-----------------------------------------------------------------------------

//----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
 */
//-----------------------------------------------------------------------------
GLOBAL WEATHER_CONT_PTR InitWeatherSys(FIELDSYS_WORK * fsys);	// ������(�ŏ��ɂP��)
GLOBAL void DestWeatherSys(WEATHER_CONT_PTR* pWes);						// �j���i�Ō�ɂP��j
GLOBAL BOOL ControlWeatherSys(WEATHER_CONT_PTR Wes, int cont, int no);	// �V�C�R���g���[���֐�
GLOBAL int CheckMoveWeatherSys(WEATHER_CONT_PTR Wes, int no);			// �V�C���ǂ�ȏ�Ԃ��`�F�b�N


#undef	GLOBAL
#endif

