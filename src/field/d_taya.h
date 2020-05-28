//============================================================================================
/**
 * @file	d_taya.h
 * @bfief	�c�J �f�o�b�O���j���[
 * @author	taya GAME FREAK inc.
 */
//============================================================================================
#ifndef _D_TAYA_H_
#define _D_TAYA_H_

#include "field_common.h"


typedef struct {
	u16  key;			///< �Đ��L�[�f�[�^�i�O�Ő擪�ɖ߂�j
	u16  frames;		///< ���̃L�[�Đ��܂ł̃E�F�C�g�t���[����
	u16  repeat;		///< ���̃V�[�P���X���J��Ԃ���
}DEBUG_KEYPLAY_DATA;

#define DEBUG_KEYPLAY_END	(0x8000)	/// �L�[�f�[�^�ɂ��̒l��������擪�ɖ߂�

extern void DebugTayaMenuInit( void* fsys );


extern void DebugKeyPlay_Start( const DEBUG_KEYPLAY_DATA* tbl );
extern void DebugKeyPlay_Stop( void );
extern BOOL DebugKeyPlay_IsPlaying( void );


extern void DebugKeyPlay_Main( void );


#endif
