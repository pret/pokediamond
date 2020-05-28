//=============================================================================
/**
 * @file	fieldmap.h	
 * @bfief	�t�B�[���h�}�b�v�V�X�e��
 * @author	GAME FREAK inc.
 */
//=============================================================================
#ifndef	__FIELDMAP_H__
#define __FIELDMAP_H__


#include "system/brightness.h"
#include "field_common.h"

// �P�x�����p�t���O
enum {
	FLD_DISP_BRIGHT_BLACKOUT = 0,		// �Â�����
	FLD_DISP_BRIGHT_BLACKIN			// ���ɖ߂�
};

// BG�t���[��
#define	FLD_MBGFRM_MAP		( GF_BGL_FRAME0_M )		///<�}�b�v
#define	FLD_MBGFRM_EFFECT1	( GF_BGL_FRAME1_M )		///<�G�t�F�N�g�P
#define	FLD_MBGFRM_EFFECT2	( GF_BGL_FRAME2_M )		///<�G�t�F�N�g�Q
#define	FLD_MBGFRM_FONT		( GF_BGL_FRAME3_M )		///<���b�Z�[�W

#define	FLD_SBGFRM_MENU		( GF_BGL_FRAME0_S )		///<���j���[
#define	FLD_SBGFRM_EFFECT1	( GF_BGL_FRAME1_S )		///<�G�t�F�N�g�P
#define	FLD_SBGFRM_EFFECT2	( GF_BGL_FRAME2_S )		///<�G�t�F�N�g�Q
#define	FLD_SBGFRM_FONT		( GF_BGL_FRAME3_S )		///<���b�Z�[�W

extern  void FieldFadeWipeSet(const u8 flg);

extern void Fieldmap_BgSet( GF_BGL_INI * ini );
extern void Fieldmap_BgExit( GF_BGL_INI * ini );


#endif //__FIELDMAP_H__

