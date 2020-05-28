#ifndef __PAST_DEF_H__
#define __PAST_DEF_H__

//�K��softsprite.h��enum�ɍ��킹��
#define PARA_POS_X	(0)				// X���W
#define PARA_POS_Y	(1)				// Y���W
#define PARA_ROT_CX	(10)			// ��]X�I�t�Z�b�g
#define PARA_AFF_X	(12)			// X�����g��k����
#define PARA_AFF_Y	(13)			// Y�����g��k����
#define PARA_ALPHA	(19)			//�A���t�@
/**
	SS_PARA_POS_Y,			// Y���W
	SS_PARA_POS_Z,			// Z���W
	SS_PARA_POS_OX,			// X���W�I�t�Z�b�g
	SS_PARA_POS_OY,			// Y���W�I�t�Z�b�g
	SS_PARA_POS_OZ,			// Z���W�I�t�Z�b�g
	SS_PARA_VANISH,			// �o�j�b�V���t���O�i0:�\���@1:��\���j
	SS_PARA_ROT_X,			// X������]�p�x
	SS_PARA_ROT_Y,			// Y������]�p�x
	SS_PARA_ROT_Z,			// Z������]�p�x
	SS_PARA_ROT_CX,			// ��]���SX���W�I�t�Z�b�g
	SS_PARA_ROT_CY,			// ��]���SY���W�I�t�Z�b�g
	SS_PARA_AFF_X,			// X�����g��k����
	SS_PARA_AFF_Y,			// Y�����g��k����
	SS_PARA_VISIBLE,		// �r�W�u�����[�h�t���O�i0:OFF�@1:ON�j
	SS_PARA_OFS_POS_X,		// �e�N�X�`�����͈͍���X���W
	SS_PARA_OFS_POS_Y,		// �e�N�X�`�����͈͍���Y���W
	SS_PARA_OFS_SIZE_X,		// �e�N�X�`�����͈�X�T�C�Y
	SS_PARA_OFS_SIZE_Y,		// �e�N�X�`�����͈�Y�T�C�Y
	SS_PARA_ALPHA,			// Alpha�l
	SS_PARA_PAL_FADE,		// �p���b�g�t�F�[�h�t���O
	SS_PARA_PAL_RGB,		// �p���b�g�t�F�[�h RGB�l
	SS_PARA_PAL_START_EVY,	// �p���b�g�t�F�[�h START_EVY�l
	SS_PARA_PAL_END_EVY,	// �p���b�g�t�F�[�h END_EVY�l
	SS_PARA_PAL_WAIT,		// �p���b�g�t�F�[�h WAIT�l
	SS_PARA_H_FLIP,			// ���E���]�t���O
	SS_PARA_V_FLIP,			// �㉺���]�t���O
	SS_PARA_DRAW_STOP,		// �����`��X�g�b�v

	SS_PARA_END
*/
#define WORK0 (0)
#define WORK1 (1)
#define WORK2 (2)
#define WORK3 (3)
#define WORK4 (4)
#define WORK5 (5)
#define WORK6 (6)
#define WORK7 (7)

#define PARAM_X (8)
#define PARAM_Y (9)
#define PARAM_DX (10)
#define PARAM_DY (11)
#define PARAM_RX (12)
#define PARAM_RY (13)
#define PARAM_ROT	(14)

#define COMP_MINUS	(15)
#define COMP_PLUS	(16)
#define COMP_EQUAL	(17)

#define CALC_VAL	(18)
#define CALC_WORK	(19)

#define USE_VAL		(20)
#define USE_WORK	(21)

#define PARAM_SET	(22)
#define PARAM_ADD	(23)

#define APPLY_SET	(24)
#define APPLY_ADD	(25)
#define APPLY_SYNTHE		(26)

#define CORRECT_ON_MINUS	(27)
#define CORRECT_OFF			(28)
#define CORRECT_ON_NOT_EQ	(29)



#define CURVE_SIN			(30)
#define CURVE_COS			(31)
#define CURVE_SIN_MINUS		(32)
#define CURVE_COS_MINUS		(33)

#define TARGET_NONE			(34)
#define TARGET_DX			(35)
#define TARGET_DY			(36)
#define TARGET_RX			(37)
#define TARGET_RY			(38)
#define TARGET_ROT			(39)

#endif	//__PAST_DEF_H__
