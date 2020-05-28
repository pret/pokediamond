//==============================================================================
/**
 * @file	actin_input.h
 * @brief	���Z�͕�����͉�ʂ̃w�b�_
 * @author	matsuda
 * @date	2005.12.02(��)
 */
//==============================================================================
#ifndef __ACTIN_INPUT_H__
#define __ACTIN_INPUT_H__


//==============================================================================
//	�萔��`
//==============================================================================
//--------------------------------------------------------------
//	�t���[���ԍ�
//--------------------------------------------------------------
///�p�l���ʂ̃t���[��
#define ACTINSUB_FRAME_PANEL			(GF_BGL_FRAME0_S)
///���g�ʂ̃t���[��
#define ACTINSUB_FRAME_BF				(GF_BGL_FRAME1_S)
///�w�i�ʂ̃t���[��
#define ACTINSUB_FRAME_BACK				(GF_BGL_FRAME2_S)
///�G�t�F�N�g�t���[����(���g�X���C�h�p)
#define ACTINSUB_FRAME_EFF				(GF_BGL_FRAME3_S)

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///�T�u��ʂ̕\��BG�^�C�v
enum{
	AINPUT_TYPE_WALL,			///<�m�[�}���w�i
	AINPUT_TYPE_HEART_WALL,		///<�Z�I���̕ǎ��̂�
	AINPUT_TYPE_WAZA,			///<�Z�I��
	AINPUT_TYPE_JUDGE,			///<�R���I��
};

//--------------------------------------------------------------
//	�^�b�`�p�l���I�����̌���
//--------------------------------------------------------------
///�Z�I���ł̃^�b�`�p�l������
enum{
	ACTIN_TP_WAZA_1,
	ACTIN_TP_WAZA_2,
	ACTIN_TP_WAZA_3,
	ACTIN_TP_WAZA_4,
};

///�R���I���ł̃^�b�`�p�l������
enum{
	ACTIN_TP_JUDGE_1,
	ACTIN_TP_JUDGE_2,
	ACTIN_TP_JUDGE_3,
	ACTIN_TP_JUDGE_MODORU,
};

//==============================================================================
//	�^��`
//==============================================================================
///BI_PARAM�̕s��`�|�C���^
typedef struct _ACI_PARAM * ACI_PARAM_PTR;


//==============================================================================
//	�O���֐��錾
//==============================================================================
extern void AINPUT_DefaultFrameSet(GF_BGL_INI *bgl);
extern void AINPUT_FrameExit(GF_BGL_INI *bgl);
extern void * AINPUT_SystemInit(CONTEST_SYSTEM *consys, ACTIN_SYSTEM_PARAM *sys, 
	ACTIN_GAME_PARAM *a_game);
extern void AINPUT_SystemFree(ACI_PARAM_PTR aci);
extern void AINPUT_CreateBG(ACI_PARAM_PTR aci, int select_bg, int force_put, void *scene_work);
extern int AINPUT_TouchCheck(ACI_PARAM_PTR aci);
extern BOOL AINPUT_EffectEndCheck(ACI_PARAM_PTR aci);
extern void AINPUT_WazaParaMemoryDecord(ACI_PARAM_PTR aci, u16 wazano[]);


#endif	//__ACTIN_INPUT_H__

