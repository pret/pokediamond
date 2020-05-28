//�P�x�ύX
#include "common.h"
#include "system/brightness.h"

enum{
	BRIGHT_CHG_NO = 0,
	BRIGHT_CHG_YES
};

typedef struct BRIGHTNESS_CHG_tag{
	BRIGHT_PARAM BrightParam;
	s8	Dir;

	s16 Dif;
	s16 dps;
	u16 d_rest;
	u16	rest;
	
	s16 Now;

	BOOL Request;

//BRIGHT_PLANEMASK PlaneMask;
//BRIGHT_DISPMASK DisplayMask;	
//u16 Sync;
//s16 Dst;
//s16 Src;
}BRIGHTNESS_CHG;


static BRIGHTNESS_CHG MainBrightCont;
static BRIGHTNESS_CHG SubBrightCont;

static void SetUpBrightness(BRIGHTNESS_CHG	*bright_data,
							const u8 inSync,
							const s16 inDstBright,
							const s16 inSrcBright,
							const BRIGHT_PLANEMASK inPlaneMask,
							const BRIGHT_DISPMASK inDisplayMask);

//==============================================================================
/**
 * �P�x�ύX
 *
 * @param	bright_data	�P�x�ύX�\���̂ւ̃|�C���^
 *
 * @retval  �Ȃ�
 */
//==============================================================================
static void ChangeBrightness(BRIGHTNESS_CHG *bright_data)
{
	BRIGHT_PARAM *param;
	BOOL finished;
	
	finished = BRIGHT_CHG_NO;
	param = &bright_data->BrightParam;
	
	if ((bright_data->Now + bright_data->Dir*bright_data->dps != param->Dst) &&
			(bright_data->Now != param->Dst)){
		bright_data->Now += bright_data->Dir*bright_data->dps;
		bright_data->rest += bright_data->d_rest;
		if (bright_data->rest>=param->Sync){
			bright_data->Now += bright_data->Dir;

			if (bright_data->Now != param->Dst){
				bright_data->rest -= param->Sync;
			}else{
				finished = BRIGHT_CHG_YES;
			}
		}
	}else{
		bright_data->Now = param->Dst;
		finished = BRIGHT_CHG_YES;
	}

	if (param->DisplayMask & MASK_MAIN_DISPLAY){
		G2_SetBlendBrightness(param->PlaneMask,bright_data->Now);
	}
	else if (param->DisplayMask & MASK_SUB_DISPLAY){
		G2S_SetBlendBrightness(param->PlaneMask,bright_data->Now);
	}

	if (finished == BRIGHT_CHG_YES){
		bright_data->Request = FALSE;
	}

}

//==============================================================================
/**
 * �P�x�Z�b�g�A�b�v
 *
 * @param	*bright_data	�P�x�ύX�\���̂ւ̃|�C���^
 * @param   inSync			�t�F�[�h����̂ɂ�����Sync��
 * @param   inDstBright		�t�F�[�h�I�����̋P�x�i���define����)	��  ���������I����
 * @param   inSrcBright		�t�F�[�h�J�n���̋P�x�i���define����)
 * @param   inPlaneMask		�t�F�[�h�����f�����BG�ʁi���enum����)
 * @param   inDisplayMask	�t�F�[�h�����f�����LCD�i���enum����)
 *
 * @retval  �Ȃ�
 */
//==============================================================================
static void SetUpBrightness(BRIGHTNESS_CHG	*bright_data,
							const u8 inSync,
							const s16 inDstBright,
							const s16 inSrcBright,
							const BRIGHT_PLANEMASK inPlaneMask,
							const BRIGHT_DISPMASK inDisplayMask)
{
	BRIGHT_PARAM *param;
	GF_ASSERT((bright_data->Request == FALSE)&&"�P�x�ύX���N�G�X�g���������Ă��܂�");
	bright_data->Request = TRUE;
	
	param = &bright_data->BrightParam;

	//�P�x�ύX�ʃ}�X�N
	param->PlaneMask = (u8)inPlaneMask;
	//�P�x���f�\����ʃ}�X�N
	param->DisplayMask = (u8)inDisplayMask;
	//Sync���V���N�ŐF��ς��邩
	param->Sync = inSync;
	//�ړI�P�x
	param->Dst = inDstBright;
	//���݋P�x
	bright_data->Now = inSrcBright;
	//���݋P�x�Ǝw��P�x�̍����Ƃ�
	bright_data->Dif = inSrcBright - inDstBright;
	//�Ƃ����������V���N���Ŋ���
	//�����P�V���N�̕ω��ʁi�]��͕ۑ����đ������݁A��������(�w��V���N)�𒴂�����ω��ʂɒǉ��j
	
	if (bright_data->Dif>0){
		bright_data->Dir = -1;
	}else{
		bright_data->Dir = 1;
		bright_data->Dif *= (-1);
	}
	bright_data->dps = bright_data->Dif/inSync;
	bright_data->d_rest = bright_data->Dif%inSync;
	bright_data->rest = 0;
}

//==============================================================================
/**
 * �P�x�ύX�t�F�[�h���N�G�X�g
 *
 * @param   inSync			�t�F�[�h����̂ɂ�����Sync��
 * @param   inDstBright		�t�F�[�h�I�����̋P�x�i���define����)	��  ���������I����
 * @param   inSrcBright		�t�F�[�h�J�n���̋P�x�i���define����)
 * @param   inPlaneMask		�t�F�[�h�����f�����BG�ʁi���enum����)
 * @param   inDisplayMask	�t�F�[�h�����f�����LCD�i���enum����)
 *
 * @retval  �Ȃ�
 */
//==============================================================================
void ChangeBrightnessRequest(const u8 inSync, const s16 inDstBright, const s16 inSrcBright,
		const BRIGHT_PLANEMASK inPlaneMask, const BRIGHT_DISPMASK inDisplayMask)
{
	BRIGHTNESS_CHG	*bright_data;
	
	//0�V���N�ł̋P�x�ύX�͕s�\�Ȃ̂ŁA���N�G�X�g������
	if (inSync == 0){
		return;
	}

	//�����P�x���Z�b�g
	if (inDisplayMask & MASK_MAIN_DISPLAY){
		G2_SetBlendBrightness(inPlaneMask,inSrcBright);
		bright_data = &MainBrightCont;
		SetUpBrightness(bright_data,inSync,inDstBright,inSrcBright,
				inPlaneMask, MASK_MAIN_DISPLAY);
	}
	if (inDisplayMask & MASK_SUB_DISPLAY){
		G2S_SetBlendBrightness(inPlaneMask,inSrcBright);
		bright_data = &SubBrightCont;
		SetUpBrightness(bright_data,inSync,inDstBright,inSrcBright,
				inPlaneMask, MASK_SUB_DISPLAY);
	}
	
}

//==============================================================================
/**
 * �P�x�ύX
 *
 * @param   inDstBright		�P�x�i���define����)
 * @param   inPlaneMask		�t�F�[�h�����f�����BG�ʁi���enum����)
 * @param   inDisplayMask	�t�F�[�h�����f�����LCD�i���enum����)
 *
 * @retval  �Ȃ�
 */
//==============================================================================
void SetBrightness(	const s16 inDstBright,
					const BRIGHT_PLANEMASK inPlaneMask,
					const BRIGHT_DISPMASK inDisplayMask)
{
	if (inDisplayMask & MASK_MAIN_DISPLAY){
		G2_SetBlendBrightness(inPlaneMask,inDstBright);
	}
	if (inDisplayMask & MASK_SUB_DISPLAY){
		G2S_SetBlendBrightness(inPlaneMask,inDstBright);
	}
	BrightnessChgReset(inDisplayMask);
}

//==============================================================================
/**
 * �P�x�ύX�\���̏�����
 *
 * @param	�Ȃ�
 *
 * @retval  �Ȃ�
 */
//==============================================================================
void BrightnessChgInit(void)
{
	MI_CpuClear8(&MainBrightCont, sizeof(BRIGHTNESS_CHG));
	MI_CpuClear8(&SubBrightCont, sizeof(BRIGHTNESS_CHG));
	MainBrightCont.Request = FALSE;
	SubBrightCont.Request = FALSE;
}

//==============================================================================
/**
 * �P�x�ύX�\���̂̃��Z�b�g
 *
 * @param   inDisplayMask	�t�F�[�h�����f�����LCD�i���enum����)
 *
 * @retval  �Ȃ�
 */
//==============================================================================
void BrightnessChgReset(const BRIGHT_DISPMASK inDisplayMask)
{
	if (inDisplayMask & MASK_MAIN_DISPLAY){
		MI_CpuClear8(&MainBrightCont, sizeof(BRIGHTNESS_CHG));
		MainBrightCont.Request = FALSE;
	}
	if (inDisplayMask & MASK_SUB_DISPLAY){
		MI_CpuClear8(&SubBrightCont, sizeof(BRIGHTNESS_CHG));
		SubBrightCont.Request = FALSE;
	}
}

//==============================================================================
/**
 * �P�x�ύX���C��
 *
 * @param	�Ȃ�
 *
 * @retval  �Ȃ�
 */
//==============================================================================
void BrightnessChgMain(void)
{
	//���N�G�X�g�`�F�b�N
	if (MainBrightCont.Request){
		ChangeBrightness(&MainBrightCont);
	}
	if (SubBrightCont.Request){
		ChangeBrightness(&SubBrightCont);
	}
}

//==============================================================================
/**
 * �I���`�F�b�N
 *
 * @param	flg ���ׂ�k�b�c�b
 *
 * @retval  �I���L��
 */
//==============================================================================
BOOL IsFinishedBrightnessChg(BRIGHT_DISPMASK flg)
{
	if (flg == MASK_DOUBLE_DISPLAY){
		if (MainBrightCont.Request == FALSE && SubBrightCont.Request == FALSE){
			return TRUE;
		}
	}else if(flg == MASK_MAIN_DISPLAY){
		if (MainBrightCont.Request == FALSE){
			return TRUE;
		}
	}else if (flg == MASK_SUB_DISPLAY){
		if (SubBrightCont.Request == FALSE){
			return TRUE;
		}
	}

	return FALSE;
}

