//==============================================================================
/**
 * @file	dance_input.h
 * @brief	�_���X������͉�ʂ̃w�b�_
 * @author	matsuda
 * @date	2005.12.17(�y)
 */
//==============================================================================
#ifndef __DANCE_INPUT_H__
#define __DANCE_INPUT_H__


//==============================================================================
//	�萔��`
//==============================================================================
//--------------------------------------------------------------
//	�t���[���ԍ�
//--------------------------------------------------------------
///�p�l���ʂ̃t���[��
#define DANCESUB_FRAME_PANEL			(GF_BGL_FRAME0_S)
///���g�ʂ̃t���[��
#define DANCESUB_FRAME_BF				(GF_BGL_FRAME1_S)
///�w�i�ʂ̃t���[��
#define DANCESUB_FRAME_BACK				(GF_BGL_FRAME2_S)
///�G�t�F�N�g�t���[����(���g�X���C�h�p)
#define DANCESUB_FRAME_EFF				(GF_BGL_FRAME3_S)

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///�T�u��ʂ̕\��BG�^�C�v
enum{
	DINPUT_TYPE_WALL,			///<�m�[�}���w�i
	DINPUT_TYPE_COMMAND,		///<�R�}���h�I��
};

//--------------------------------------------------------------
//	�^�b�`�p�l���I�����̌���
//--------------------------------------------------------------
///�R�}���h�I���ł̃^�b�`�p�l������
enum{
	DANCE_TP_JUMP,
	DANCE_TP_ADVANCE,
	DANCE_TP_LEFT,
	DANCE_TP_RIGHT,
	
	DANCE_TP_MAX,
};

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///�{�^����ύX���鎞�̐F(��)
#define DINPUT_COLOR_BLACK		(0x0000)
///�{�^�����Â����鎞��EVY�l
#define DINPUT_BLACK_EVY		(6)
///�{�^���ʏ펞��EVY�l
#define DINPUT_NORMAL_EVY		(0)


//==============================================================================
//	�^��`
//==============================================================================
///DI_PARAM�̕s��`�|�C���^
typedef struct _DCI_PARAM * DCI_PARAM_PTR;


//==============================================================================
//	�O���֐��錾
//==============================================================================
extern void DINPUT_DefaultFrameSet(GF_BGL_INI *bgl);
extern void DINPUT_FrameExit(GF_BGL_INI *bgl);
extern void * DINPUT_SystemInit(CONTEST_SYSTEM *consys, DANCE_SYSTEM_PARAM *sys);
extern void DINPUT_SystemFree(DCI_PARAM_PTR dci);
extern void DINPUT_CreateBG(DCI_PARAM_PTR dci, int select_bg, int force_put, void *scene_work);
extern int DINPUT_TouchCheck(DCI_PARAM_PTR dci);
extern BOOL DINPUT_EffectEndCheck(DCI_PARAM_PTR dci);
extern void DINPUT_DefaultActorSet(DCI_PARAM_PTR dci);
extern int DINPUT_MakeDataNoGet(DCI_PARAM_PTR dci);
extern void DINPUT_FadeSet(DCI_PARAM_PTR dci, u16 color, u8 evy);


#endif	//__DANCE_INPUT_H__

