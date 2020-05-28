//==============================================================================
/**
 * @file	wpcb_def.h
 * @brief	��{�\���� wpcb_xxx.c �����Ainclude���Ă͂����Ȃ�
 * @author	goto
 * @date	2006.02.12(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================

#ifndef __WPCB_DEF_H__
#define __WPCB_DEF_H__

// -----------------------------------------
//
//	�� �v���O�������ň���
//
// -----------------------------------------
#define OPERATOR_AXIS_PARAM_MAX		(3)				///< ������EX_DATA����擾����l�̐�
#define OPERATOR_POS_PARAM_MAX		(3)				///< ���W��EX_DATA����擾����l�̐�
#define OPERATOR_REVERCE_FLAG_OFF	(1)				///< ���]�t���O
#define OPERATOR_REVERCE_FLAG_ON	(-1)			///< ���]�t���O

// -----------------------------------------
//
//	�� *.s �ň���
//
// -----------------------------------------
#define OPERATOR_EX_REVERCE_ON			(0)			///< *[ ���� ] �ʒu���]����
#define OPERATOR_EX_REVERCE_OFF			(1)			///< *[ ���� ] �ʒu���]����

#define OPERATOR_DEF_DATA_NUM			(6)			///< �f�[�^���

#define OPERATOR_PRI_NONE				(0)			///< *[ �D��x ] 
#define OPERATOR_PRI_FRONT				(1)			///< �O��
#define OPERATOR_PRI_BACK				(2)			///< �w��
#define OPERATOR_PRI_Z					(3)			///< Z

#define OPERATOR_DEF_FZ_AA				(256)		///< �O�ʗp��{Z
#define OPERATOR_DEF_BZ_AA				(0)			///< �w�ʗp��{Z
#define OPERATOR_DEF_FZ_BB				(-5120)		///< �O�ʗp��{Z
#define OPERATOR_DEF_BZ_BB				(-5376)		///< �w�ʗp��{Z

#define OPERATOR_TARGET_NONE			(0)			///< *[ ���ޯ� ] TARGET_NONE == POS_NONE
#define OPERATOR_TARGET_AT				(1)
#define OPERATOR_TARGET_DF				(2)
#define OPERATOR_TARGET_AT_SIDE			(3)
#define OPERATOR_TARGET_DF_SIDE			(4)


#define OPERATOR_POS_NONE				(0)			///< *[ ���W ]
#define OPERATOR_POS_SP					(1)			///< �J�n
#define OPERATOR_POS_EP					(2)			///< �I��
#define OPERATOR_POS_SET				(3)			///< ���[�U�[�w��
#define OPERATOR_POS_SP_OFS				(4)			///< �J�n+ofs
#define OPERATOR_POS_EP_OFS				(5)			///< �I��+ofs
#define OPERATOR_POS_LSP				(6)			///< ���[�U�[�J�n
#define OPERATOR_POS_LEP				(7)			///< ���[�U�[�I��
#define OPERATOR_POS_RSP				(8)			///< �����O�J�n
#define OPERATOR_POS_REP				(9)			///< �����O�I��
#define OPERATOR_POS_L2SP				(10)		///< ���[�U�[�J�n
#define OPERATOR_POS_L2EP				(11)		///< ���[�U�[�I��
#define OPERATOR_POS_AT_SIDE_OFS		(12)		///< �J�n+ofs
#define OPERATOR_POS_DF_SIDE_OFS		(13)		///< �I��+ofs
#define OPERATOR_POS_L3SP				(14)		///< ���[�U�[�J�n
#define OPERATOR_POS_L3EP				(15)		///< ���[�U�[�I��
#define OPERATOR_POS_L095SP				(16)		///< ���[�U�[�J�n
#define OPERATOR_POS_L095EP				(17)		///< ���[�U�[�I��
#define OPERATOR_POS_L161SP				(18)		///< ���[�U�[�J�n
#define OPERATOR_POS_L161EP				(19)		///< ���[�U�[�I��
#define OPERATOR_POS_L308SP				(20)		///< ���[�U�[�J�n
#define OPERATOR_POS_L308EP				(21)		///< ���[�U�[�I��
#define OPERATOR_POS_L304SP				(22)		///< ���[�U�[�J�n
#define OPERATOR_POS_L304EP				(23)		///< ���[�U�[�I��
#define OPERATOR_POS_L320SP				(24)		///< ���[�U�[�J�n
#define OPERATOR_POS_L320EP				(25)		///< ���[�U�[�I��
#define OPERATOR_POS_L406SP				(26)		///< ���[�U�[�J�n
#define OPERATOR_POS_L406EP				(27)		///< ���[�U�[�I��
#define OPERATOR_POS_145_CON			(28)		///< �R���e�X�g�F�A
#define OPERATOR_POS_169_CON			(29)		///< �R���e�X�g�F����
#define OPERATOR_POS_226				(30)		///< �o�g���^�b�`
#define OPERATOR_POS_145				(31)		///< �A
#define OPERATOR_POS_225				(32)		///< ��イ�̂��Ԃ�
#define OPERATOR_POS_389_CON			(33)		///< �R���e�X�g�F
#define OPERATOR_POS_194				(34)		///< �R���e�X�g�F

#define OPERATOR_POS_SP_OFS_ALL			(100)		///< �J�n������̃I�t�Z�b�g�S�w��
#define OPERATOR_POS_EP_OFS_ALL			(101)		///< �I��������̃I�t�Z�b�g�S�w��


#define OPERATOR_AXIS_NONE				(0)			///< *[ ���� ]
#define OPERATOR_AXIS_AT				(1)
#define OPERATOR_AXIS_DF				(2)
#define OPERATOR_AXIS_SET				(3)
#define OPERATOR_AXIS_AT_SIDE			(4)
#define OPERATOR_AXIS_DF_SIDE			(5)
#define OPERATOR_AXIS_AT_OLD			(6)
#define OPERATOR_AXIS_DF_OLD			(7)
#define OPERATOR_AXIS_AT_3				(8)			///< 3 �T�C�P�����Ȃ�
#define OPERATOR_AXIS_DF_3				(9)
#define OPERATOR_AXIS_AT_095			(10)		///< 095
#define OPERATOR_AXIS_DF_095			(11)
#define OPERATOR_AXIS_AT_161			(12)		///< 308
#define OPERATOR_AXIS_DF_161			(13)
#define OPERATOR_AXIS_AT_308			(14)		///< 308
#define OPERATOR_AXIS_DF_308			(15)
#define OPERATOR_AXIS_AT_304			(16)		///< 308
#define OPERATOR_AXIS_DF_304			(17)
#define OPERATOR_AXIS_AT_320			(18)		///< 308
#define OPERATOR_AXIS_DF_320			(19)
#define OPERATOR_AXIS_AT_406			(20)		///< 308
#define OPERATOR_AXIS_DF_406			(21)
#define OPERATOR_AXIS_145_CON			(22)		///< �R���e�X�g�F�A
#define OPERATOR_AXIS_169_CON			(23)		///< �R���e�X�g�F����
#define OPERATOR_AXIS_145				(24)		///< �A
#define OPERATOR_AXIS_389_CON			(25)		///< �R���e�X�g�F
#define OPERATOR_AXIS_194				(26)		///< �݂��Â�


#define OPERATOR_FLD_NONE				(0x0000)	///< *[ ̨���� ]
#define OPERATOR_FLD_GRAVITY_MAG		(0x0002)	///< VecFx16
#define OPERATOR_FLD_RANDOM_MAG			(0x0004)	///< VecFx16
#define OPERATOR_FLD_RANDOM_INTVL		(0x0008)	///< u16
#define OPERATOR_FLD_MAGNET_POS			(0x0010)	///< VecFx32
#define OPERATOR_FLD_MAGNET_MAG			(0x0020)	///< fx16
#define OPERATOR_FLD_SPIN_RAD			(0x0040)	///< u16
#define OPERATOR_FLD_SPIN_AXIS			(0x0080)	///< u16
#define OPERATOR_FLD_SIMPLE_CLS_Y		(0x0100)	///< fx32
#define OPERATOR_FLD_SIMPLE_CLS_CB		(0x0200)	///< fx16
#define OPERATOR_FLD_SIMPLE_CLS_EVT		(0x0400)	///< 2bit
#define OPERATOR_FLD_SIMPLE_CLS_GLB		(0x0800)	///< 1bit
#define OPERATOR_FLD_CONVERGENCE_POS	(0x1000)	///< VecFx32
#define OPERATOR_FLD_CONVERGENCE_RATIO	(0x2000)	///< fx16
#define OPERATOR_FLD_END				(0xFEFE)	///< 

///< EX_DATA �ɕt������
#define OPERATOR_FLD_EX_DATA_NUM		(5)			///< mode, flip, x, y, z
#define OPERATOR_FLD_DEFAULT			(0)			///< �ʏ�̒l��ݒ�
#define OPERATOR_FLD_SET				(1)			///< ���ɑ����l��ݒ�
#define OPERATOR_FLD_AT					(2)			///< �U�����̊�{�ʒu�֐ݒ�
#define OPERATOR_FLD_DF					(3)			///< �Ώۑ��̊�{�ʒu�֐ݒ�
#define OPERATOR_FLD_SET_DF				(4)			///< ���ɑ����l�@2�̃p�[�Z���g 3, 4 �Ȃ�@3/4
#define OPERATOR_FLD_NO_DATA			(0xFF)		///< �w�薳��

#define OPERATOR_CAMERA_NONE			(0)			///< *[ ��� ]
#define OPERATOR_CAMERA_SPIN			(1)			///< �X�s�����J�����ݒ�
#define OPERATOR_CAMERA_SET				(2)			///< ���[�U�[�J�����w��
#define OPERATOR_CAMERA_MOVE			(3)			///< �ړ��J�����w��
#define OPERATOR_CAMERA_145				(4)			///< �ړ��J�����w��
#define OPERATOR_CAMERA_169_CON			(5)			///< �ړ��J�����w��
#define OPERATOR_CAMERA_126				(6)			///< �ړ��J�����w��
#define OPERATOR_CAMERA_AT				(7)			///< �U�����J�����w��
#define OPERATOR_CAMERA_DF				(8)			///< �h�䑤�J�����w��

///< EX_DATA �ɕt������
#define OPERATOR_CAMERA_EX_DATA_NUM		(4)			///< flip, x, y, z

///< ��{�l
#define OPERATOR_SET_CENTER				(0)			///< ���_

#endif

