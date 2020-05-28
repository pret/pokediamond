#ifndef _BRIGHTNESS_H_
#define _BRIGHTNESS_H_
//#undef GLOBAL

//#ifdef BRIGHTNESS_H_GLOBAL
//#define GLOBAL	/*	*/
//#else
//#define GLOBAL	extern
//#endif	//BRIGHTNESS_H_GLOBAL

// �t�F�[�h�Ɏw�肷��P�x
#define BRIGHTNESS_WHITE	(  16 )		// �^����
#define BRIGHTNESS_NORMAL	(   0 )		// �ʏ�p���b�g���f���
#define BRIGHTNESS_BLACK	( -16 )		// �^����

#define	COMM_BRIGHTNESS_SYNC	( 6 )	// ��{�̋P�x�ύXSync��


//�A�Z���u����include����Ă���ꍇ�́A���̐錾�𖳎��ł���悤��ifndef�ň͂�ł���
#ifndef	__ASM_NO_DEF_

// �t�F�[�h�ɂ�����LCD�̐ݒ�
typedef enum{
	MASK_MAIN_DISPLAY	= 0x1,									// ���C��
	MASK_SUB_DISPLAY	= 0x02,									// �T�u
	MASK_DOUBLE_DISPLAY = MASK_MAIN_DISPLAY|MASK_SUB_DISPLAY,	// ����
}BRIGHT_DISPMASK;

// �t�F�[�h��������BG�ʂ̎w��
typedef enum{
	PLANEMASK_NONE	= GX_BLEND_PLANEMASK_NONE,
	PLANEMASK_BG0	= GX_BLEND_PLANEMASK_BG0,
	PLANEMASK_BG1	= GX_BLEND_PLANEMASK_BG1,
	PLANEMASK_BG2	= GX_BLEND_PLANEMASK_BG2,
	PLANEMASK_BG3	= GX_BLEND_PLANEMASK_BG3,
	PLANEMASK_OBJ	= GX_BLEND_PLANEMASK_OBJ,
	PLANEMASK_BD	= GX_BLEND_PLANEMASK_BD,
	PLANEMASK_ALL	= GX_BLEND_PLANEMASK_BG0|GX_BLEND_PLANEMASK_BG1|GX_BLEND_PLANEMASK_BG2|GX_BLEND_PLANEMASK_BG3|GX_BLEND_PLANEMASK_OBJ|GX_BLEND_PLANEMASK_BD
}BRIGHT_PLANEMASK;

//�P�x�ύX�p�����[�^
typedef struct BrightParam_tag{
	BRIGHT_PLANEMASK PlaneMask;
	BRIGHT_DISPMASK DisplayMask;
	u16 Sync;
	s16 Dst;
	s16 Src;
//	BOOL *IsFinished;
}BRIGHT_PARAM;

#if 0
//--------------------------------------------------------------------------------------------
/**
 * �P�x�ύX�p�����[�^�ݒ�
 *
 * @param	mode		�������擾���[�h
 * @param	sync		���V���N�ŐF��ς��邩
 * @param	dst			�ύX��̋P�x
 * @param	src			�����P�x
 * @param	plane		�P�x�ύX�ʃ}�X�N
 * @param	display		���f�\����ʃ}�X�N
 *
 * @return	�ݒ肵���f�[�^�̃|�C���^
 *
 * @li	AllocMemory�g�p
 */
//--------------------------------------------------------------------------------------------
GLOBAL BRIGHTNESS_CHG * BrightnessChgParamSet(
			int mode, const u8 sync, const s16 dst, const s16 src,
			const BRIGHT_PLANEMASK plane, const BRIGHT_DISPMASK display );

//--------------------------------------------------------------------------------------------
/**
 * �P�x�ύX���C������
 *
 * @param	dat		�ύX�f�[�^
 *
 * @retval	"0 = �I��"
 * @retval	"1 = ������"
 *
 * @li	FreeMemory�͂��Ă��Ȃ�
 *
 *	BrightnessChgParamSet()���g�p�����ꍇ�A�J����Y��Ȃ��悤�ɁI
 */
//--------------------------------------------------------------------------------------------
GLOBAL u8 BrightnessChgMain( BRIGHTNESS_CHG * dat );
#endif



//==============================================================================
/**
 * �P�x�ύX�t�F�[�h���N�G�X�g
 *
 * @param   inSync			�t�F�[�h����̂ɂ�����Sync��
 * @param   inDstBright		�t�F�[�h�I�����̋P�x�i���define����)	��  ���������I����
 * @param   inSrcBright		�t�F�[�h�J�n���̋P�x�i���define����)
 * @param   inPlaneMask		�t�F�[�h�����f�����BG�ʁi���enum����)
 * @param   inDisplayMask	�t�F�[�h�����f�����LCD�i���enum����)
 * @param   outFnishFlg		�|�C���^���w�肷�鎖�Ńt�F�[�h�I�������m�ł���
 *
 * @retval  �Ȃ�
 */
//==============================================================================
extern  void ChangeBrightnessRequest(
				const u8 inSync, const s16 inDstBright, const s16 inSrcBright,
				const BRIGHT_PLANEMASK inPlaneMask, const BRIGHT_DISPMASK inDisplayMask );

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
extern  void SetBrightness(	const s16 inDstBright,
					const BRIGHT_PLANEMASK inPlaneMask,
					const BRIGHT_DISPMASK inDisplayMask);

//==============================================================================
/**
 * �P�x�ύX�\���̏�����
 *
 * @param	�Ȃ�
 *
 * @retval  �Ȃ�
 */
//==============================================================================
extern  void BrightnessChgInit(void);

//==============================================================================
/**
 * �P�x�ύX�\���̂̃��Z�b�g
 *
 * @param   inDisplayMask	�t�F�[�h�����f�����LCD�i���enum����)
 *
 * @retval  �Ȃ�
 */
//==============================================================================
extern void BrightnessChgReset(const BRIGHT_DISPMASK inDisplayMask);

//==============================================================================
/**
 * �P�x�ύX���C��
 *
 * @param	�Ȃ�
 *
 * @retval  �Ȃ�
 */
//==============================================================================
extern  void BrightnessChgMain(void);

//==============================================================================
/**
 * �P�x�ύX�I���I���`�F�b�N
 *
 * @param	flg ���ׂ�k�b�c�b
 *
 * @retval  �I���L��
 */
//==============================================================================

extern  BOOL IsFinishedBrightnessChg(BRIGHT_DISPMASK flg);

#endif	__ASM_NO_DEF_

#undef GLOBAL
#endif //_BRIGHTNESS_H_
