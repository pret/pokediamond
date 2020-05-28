//==============================================================================
/**
 * @file	contest_def.h
 * @brief	�R���e�X�g�̃w�b�_�F�X�N���v�g�Ȃǂ����include�����̂�enum�֎~�I
 * @author	matsuda
 * @date	2005.12.14(��)
 */
//==============================================================================
#ifndef __CONTEST_DEF_H__
#define __CONTEST_DEF_H__


///�R���e�X�g�̍ő�Q���l��
#define BREEDER_MAX				(4)
///�R���e�X�g�̒ʐM�ő�Q���l��
///BREEDER_MAX�Ƃ̈Ⴂ�̓u���[�_�[No�ŊǗ�����Ă�����̂�BREEDER_MAX���g�p���A
///�l�b�gID�ŊǗ�����Ă�����̂�CC_NETID_MAX���g�p���Ă��܂��B
///2005.12.18(��) ���݂� �u���[�_�[No���l�b�gID �ɂȂ��Ă���̂Ō����ɂ͋C�ɂ��Ȃ��đ��v�ł�
#define CC_NETID_MAX			(4)

//--------------------------------------------------------------
//	�R���e�X�g�^�C�v
//--------------------------------------------------------------
///�R���e�X�g�^�C�v�F�i�D�悳
#define CONTYPE_STYLE		(0)
///�R���e�X�g�^�C�v�F������
#define CONTYPE_BEAUTIFUL	(1)
///�R���e�X�g�^�C�v�F����
#define CONTYPE_CUTE		(2)
///�R���e�X�g�^�C�v�F����
#define CONTYPE_CLEVER		(3)
///�R���e�X�g�^�C�v�F痂���
#define CONTYPE_STRONG		(4)

///�R���e�X�g�^�C�v�F�ő�
#define CONTYPE_MAX		(5)

//--------------------------------------------------------------
//	�R���e�X�g�����N
//--------------------------------------------------------------
///�R���e�X�g�����N�F�m�[�}�������N
#define CONRANK_NORMAL		(0)
///�R���e�X�g�����N�F�X�[�p�[�����N(�V���́F�O���[�g�����N)
#define CONRANK_SUPER		(1)
///�R���e�X�g�����N�F�n�C�p�[�����N(�V���́F�E���g�������N)
#define CONRANK_HYPER		(2)
///�R���e�X�g�����N�F�}�X�^�[�����N
#define CONRANK_MASTER		(3)

///�R���e�X�g�����N�F�C���[�W�N���b�v�p��`�@�ʐM�����N
#define CONRANK_IMC_SIO		(CONRANK_MASTER + 1)
///�R���e�X�g�����N�F�ő�
#define CONRANK_MAX			(4)

//--------------------------------------------------------------
//	�R���e�X�g���[�h(�R���e�X�g���s������)
//--------------------------------------------------------------
///�`���[�����[�h(�r�W���A�����偄���Z����)�F�|�P�����R���e�X�g
#define CONMODE_CHARM					(0)
///�A�N�e�B�u���[�h(�r�W���A�����偄�_���X����)�F�|�P�����R���N�[��
#define CONMODE_ACTIVE					(1)
///�O�����h���[�h(�r�W���A�����偄�_���X���偄���Z����)�F�|�P�����g���C�A��
#define CONMODE_GRAND					(2)
///�r�W���A�����K���[�h
#define CONMODE_VISUAL_PRACTICE			(3)
///�r�W���A���`���[�g���A�����[�h
#define CONMODE_VISUAL_TUTORIAL			(4)
///�_���X���K���[�h
#define CONMODE_DANCE_PRACTICE			(5)
///�_���X�`���[�g���A�����[�h
#define CONMODE_DANCE_TUTORIAL			(6)
///���Z���K���[�h
#define CONMODE_ACTIN_PRACTICE			(7)
///���Z�`���[�g���A�����[�h
#define CONMODE_ACTIN_TUTORIAL			(8)

//--------------------------------------------------------------
//	�Q�����Ă���Q�[��(�R���e�X�g�̎��)
//--------------------------------------------------------------
///�r�W���A��
#define CONGAME_VISUAL		(0)
///�_���X
#define CONGAME_DANCE		(1)
///���Z
#define CONGAME_ACTIN		(2)

//--------------------------------------------------------------
//	�C���[�W�N���b�v�̃e�[�}
//--------------------------------------------------------------
///�C���[�W�N���b�v�e�[�}�F�؂₩�Ȃ���(�V����:�������������)
#define CON_IMAGE_THEME_FLOWERY			(0)
///�C���[�W�N���b�v�e�[�}�F�V���v���Ȃ���(�V����:�Ƃ񂪂�������)
#define CON_IMAGE_THEME_SIMPLE			(1)
///�C���[�W�N���b�v�e�[�}�F�l�H�̂���(�V����:����ꂽ����)
#define CON_IMAGE_THEME_ARTIFICIAL		(2)
///�C���[�W�N���b�v�e�[�}�F���R�̂���
#define CON_IMAGE_THEME_NATURAL			(3)
///�C���[�W�N���b�v�e�[�}�F�F���̂���
#define CON_IMAGE_THEME_COLORFUL		(4)
///�C���[�W�N���b�v�e�[�}�F�ɂ��₩�Ȃ���(�V����:�������肵������)
#define CON_IMAGE_THEME_LIVELY			(5)
///�C���[�W�N���b�v�e�[�}�F�������肵������(�V����:�����邢����)
#define CON_IMAGE_THEME_REFRESH			(6)
///�C���[�W�N���b�v�e�[�}�F�M���M���̂���(�V����:�͂łȂ���)
#define CON_IMAGE_THEME_LIMIT			(7)
///�C���[�W�N���b�v�e�[�}�F���₩�Ȃ���(�V����:���Ȃ₩�Ȃ���)
#define CON_IMAGE_THEME_SOFTLY			(8)
///�C���[�W�N���b�v�e�[�}�F����т₩�Ȃ���
#define CON_IMAGE_THEME_GORGEOUS		(9)
///�C���[�W�N���b�v�e�[�}�F��i�Ȃ���(�V����:�������̂Ȃ�����)
#define CON_IMAGE_THEME_ELEGANT			(10)
///�C���[�W�N���b�v�e�[�}�F�h��Ȃ���(�V����:������������)
#define CON_IMAGE_THEME_SHOWY			(11)

///�C���[�W�N���b�v�e�[�}�F�ő吔
#define CON_IMAGE_THEME_MAX				(12)

//--------------------------------------------------------------
//	�C���[�W�N���b�v�ł������
//--------------------------------------------------------------
///�m�[�}�������N�ŕt������A�N�Z�T���ő吔
#define CON_IMAGE_ACCE_MAX_NORMAL		(5)
///�X�[�p�[�����N�ŕt������A�N�Z�T���ő吔
#define CON_IMAGE_ACCE_MAX_SUPER		(10)
///�n�C�p�[�����N�ŕt������A�N�Z�T���ő吔
#define CON_IMAGE_ACCE_MAX_HYPER		(15)
///�}�X�^�[�����N�ŕt������A�N�Z�T���ő吔
#define CON_IMAGE_ACCE_MAX_MASTER		(20)
///�ʐM�ΐ�ŕt������A�N�Z�T���ő吔
#define CON_IMAGE_ACCE_MAX_SIO			(20)


//==============================================================================
//	�ʐM�����҂��p�̔ԍ���`
//==============================================================================
///�R���e�X�g���ł̊J�n���̍ŏ��̓����҂�
#define CONSIO_TIMING_START				(0)

///�C���[�W�N���b�v��ʌĂяo���O�̓����҂�
#define CONSIO_TIMING_CALL_IMC			(1)
///�C���[�W�N���b�v�v���b�N���Ŏg�p���铯���҂�
#define CONSIO_TIMING_CALL_IN_IMCPROC	(2)

///�X�N���v�g�F�J�n���̓����҂�
#define CONSIO_TIMING_SCR_START			(3)
///�X�N���v�g�F�C���[�W�N���b�v�Ăяo���O�̓����҂�
#define CONSIO_TIMING_SCR_IMC			(4)

#define CONSIO_TIMING_FAST_PARAM		(5)
#define CONSIO_TIMING_POKE				(6)
#define CONSIO_TIMING_POKE_RESEND		(7)
#define CONSIO_TIMING_BD				(8)
#define CONSIO_TIMING_BD_RESEND			(9)
#define CONSIO_TIMING_NAME				(10)
#define CONSIO_TIMING_NAME_RESEND		(11)
#define CONSIO_TIMING_PERAP				(12)
#define CONSIO_TIMING_PERAP_RESEND		(13)
#define CONSIO_TIMING_ETC				(14)
#define CONSIO_TIMING_ETC_RESEND		(15)
#define CONSIO_TIMING_JUDGE				(16)
#define CONSIO_TIMING_IMC				(17)
#define CONSIO_TIMING_IMC_RESEND		(18)

///�X�N���v�g�F�v���v���ł̓����҂�
#define CONSIO_TIMING_SCR_0				(19)
#define CONSIO_TIMING_SCR_1				(20)
#define CONSIO_TIMING_SCR_2				(21)
#define CONSIO_TIMING_SCR_3				(22)
#define CONSIO_TIMING_SCR_4				(23)
#define CONSIO_TIMING_SCR_END			(24)
#define CONSIO_TIMING_SCR_5				(25)
#define CONSIO_TIMING_SCR_6				(26)


#endif	//__CONTEST_DEF_H__

