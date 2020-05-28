//==============================================================================
/**
 * @file	actin_ex.h
 * @brief	���Z�͕���F�O�����J�w�b�_
 * @author	matsuda
 * @date	2005.11.29(��)
 *
 * ���Z�͕���ŊO���Ɍ��J����K�v�̂����`���������ɏ����Ă��܂�
 */
//==============================================================================
#ifndef __ACTIN_EX_H__
#define __ACTIN_EX_H__


#define ACTIN_3DBG_PRIORITY			(2)		///<3D�ʂ�BG�v���C�I���e�B
///�E�B���h�E�ʂ�BG�v���C�I���e�B
#define ACTIN_BGPRI_WINDOW			(0)
///�G�t�F�N�g�ʂ�BG�v���C�I���e�B
#define ACTIN_BGPRI_EFFECT			(1)
///�w�i�ʂ�BG�v���C�I���e�B
#define ACTIN_BGPRI_BACKGROUND		(3)

#define ACTIN_FRAME_WINDOW			(GF_BGL_FRAME1_M)	///<�t���[���ʁF�E�B���h�E
#define ACTIN_FRAME_EFFECT			(GF_BGL_FRAME2_M)	///<�t���[���ʁF�G�t�F�N�g
#define ACTIN_FRAME_BACKGROUND		(GF_BGL_FRAME3_M)	///<�t���[���ʁF�w�i

#define ACTIN_BGNO_WINDOW			(1)					///<BG�ԍ��F�E�B���h�E
#define ACTIN_BGNO_EFFECT			(2)					///<BG�ԍ��F�G�t�F�N�g
#define ACTIN_BGNO_BACKGROUND		(3)					///<BG�ԍ��F�w�i


//--------------------------------------------------------------
//	�Z�G�t�F�N�g
//--------------------------------------------------------------
///�U���|�P�����̍��WX
#define CONTEST_ATTACK_POKE_X		(APPEAR_X_TYPE_B)
///�U���|�P�����̍��WY
#define CONTEST_ATTACK_POKE_Y		(APPEAR_Y_TYPE_A)
///�U���|�P�����̍��WZ
#define CONTEST_ATTACK_POKE_Z		(APPEAR_Z_TYPE_A)

///�h��|�P�����̍��WX
#define CONTEST_DEFENCE_POKE_X		(APPEAR_X_TYPE_C)
///�h��|�P�����̍��WY
#define CONTEST_DEFENCE_POKE_Y		(APPEAR_Y_TYPE_D)
///�h��|�P�����̍��WZ
#define CONTEST_DEFENCE_POKE_Z		(APPEAR_Z_TYPE_B)


//--------------------------------------------------------------
//	�w�i�Ŏg�p���Ă���p���b�g�̃t�F�[�hbit
//--------------------------------------------------------------
///�w�i�Ŏg�p���Ă���p���b�g�J�n�ʒu
#define ACTIN_HAIKEI_PAL_START		(0)
///�w�i�Ŏg�p���Ă���p���b�g�{��
#define ACTIN_HAIKEI_PAL_NUM		(3)
///�w�i�̃t�F�[�hbit(�Z�G�t�F�N�g�p)
#define ACTIN_HAIKEI_FADE_BIT		(0x0007)
///�Z�G�t�F�N�gBG�p�p���b�g�̃t�F�[�hbit
#define ACTIN_WAZAEFF_FADE_BIT		(0x0300)
///�w�i�̃t�F�[�hbit�{�Z�G�t�F�N�gBG�p�p���b�g(�Z�G�t�F�N�g�p)
#define ACTIN_EFFBG_ALL_FADE_BIT	(ACTIN_HAIKEI_FADE_BIT | ACTIN_WAZAEFF_FADE_BIT)


//==============================================================================
//	�O���֐��錾
//==============================================================================
extern void ActinExTool_DefaultBlendSet(void);

#endif	//__ACTIN_EX_H__

