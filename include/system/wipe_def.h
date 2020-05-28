//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *@file		wipe_def.h
 *@brief	���C�v�֐��p�w�b�_
 *@author	tomoya takahashi
 *@data		2005.08.18
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __WIPE_DEF_H__
#define __WIPE_DEF_H__

#include "system/wipe_wnd.h"

#undef GLOBAL
#ifdef	__WIPE_DEF_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif


//-------------------------------------
//	
//	�V�[�P���X������
//	
//=====================================
enum{
	WIPE_INIT,			// ���쏉����
	WIPE_MAIN,			// ����
	WIPE_END,			// ����I��
	WIPE_END_WAIT,		// �I����҂�	�I���O��1���V�u�����N��ʂ����߁@�}�X�N�̐ݒ�ύX��v�u�����N�ōs���Ă����
};


typedef void (*pHBFunc)(void* work);
//-------------------------------------
//
//	���[�J��H�u�����N���[�N
//
//	H�u�����N���Ŏg�p���܂��B
//	flg���O�ɂȂ�����I���������ƂɂȂ�܂��B
//
//=====================================
typedef struct{
	void*	work[2];	// 2=MAIN �� SUB
	pHBFunc	func[2];
	int		flg[2];		// ����t���O	0:���ݒ�	1:���s��
} WIPE_HBLANK;

enum{
	WIPE_HBLANK_NONE = 0,
	WIPE_HBLANK_DO
};

//-------------------------------------
//	
//	���C�v���[�N	
//	
//=====================================
typedef struct {
	int		wipe_no;
	int		division;
	int		piece_sync;
	int		sequence;
	int		disp;			// ���C���T�u�ǂ�����
	void*	wipe_work;		// �e���C�v�p��Ɨ̈�
	WNDP_SYS_PTR wnd_sys;	// �E�B���h�EVBlank�V�X�e���̃|�C���^
	WIPE_HBLANK* p_wipehb;	// ���C�v�pHBlank���[�N
	int		heap;			// �g�p����q�[�v
	u16		color;			// �F

	// ���ꂼ��̃��C�v��
	// ���̃��C�v�̏�Ԃ��i�[���Ă��炤
	u32 fade_inout;		// �t�F�[�h�C�����A�E�g��
	u32 wnd_br;			// ��ײ�Ƚ���g�p����̂��E�B���h�E���g�p����̂�
} WIPE_SYS_WIPE_WORK;

// ���ꂼ��̃��C�v��
// ���̃��C�v�̏�Ԃ��i�[���Ă��炤
//-------------------------------------
//	�t�F�[�h��ޗ�	
//=====================================
enum{
	WIPE_FADE_IN,
	WIPE_FADE_OUT
};
//-------------------------------------
//	�t�F�[�h�g�p�V�X�e����	
//=====================================
enum{
	WIPE_USE_WND,
	WIPE_USE_BRI
};


//----------------------------------------------------------------------------
/**
 *
 *@brief	���C�v�֐�
 *
 *@param	wipe		���C�v���[�N
 *
 *@return	BOOL		�I���FTRUE		���s�FFALSE
 *
 * �K���I��������TRUE��Ԃ��悤�ɂ���B
 * ��Ɨ̈�͊e���C�v���ō쐬���A���C�v���Ŕj������B
 *
 */
//-----------------------------------------------------------------------------
typedef BOOL (*pWIPEFunc)(WIPE_SYS_WIPE_WORK* wipe);

// HBlank�֐�
GLOBAL void WIPE_HBlankInit(WIPE_HBLANK* p_wipehb, void* work, pHBFunc func, int disp);	// H�u�����N�ݒ�
GLOBAL void WIPE_HBlankDelete(WIPE_HBLANK* p_wipehb, int disp);	// H�u�����N�j��
GLOBAL void WIPE_V_HBlankInit(WIPE_HBLANK* p_wipehb, void* work, pHBFunc func, int disp, int heap);	// H�u�����N�ݒ�
GLOBAL void WIPE_V_HBlankDelete(WIPE_HBLANK* p_wipehb, int disp, int heap);	// H�u�����N�j��
GLOBAL void defaultHFunc( void* work );

// ���C�v�J���[�ݒ�֐�
GLOBAL void WIPE_SetBackDropColor( u16 color );

// �u���C�g�l�X��Ԑݒ�֐�
GLOBAL void WIPE_SetMstBrightness( int disp, int no );

#undef	GLOBAL
#endif		// __WIPE_DEF_H__

