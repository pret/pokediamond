//[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[
/**
 *
 *	@file		imc_itemid_define.h
 *	@brief
 *	@author	
 *	@data		2006.04.05
 *
 */
//]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
#ifndef __IMC_ITEMID_DEFINE_H__
#define __IMC_ITEMID_DEFINE_H__

#undef GLOBAL
#ifdef	__IMC_ITEMID_DEFINE_H_GLOBAL
#define	GLOBAL	/* */
#else
#define	GLOBAL	extern
#endif

//-----------------------------------------------------------------------------
/**
 *					�萔�錾
*/
//-----------------------------------------------------------------------------
//-------------------------------------
//	
//	�A�N�Z�T�����X�g
//
//=====================================
#define	IMC_ACCE_WATA00			(0)			// ���낢�킽��
#define	IMC_ACCE_WATA01			(1)			// ������̂킽��
#define	IMC_ACCE_WATA02			(2)			// �s���N�̂킽��
#define	IMC_ACCE_WATA03			(3)			// ���Ⴂ��̂킽��
#define	IMC_ACCE_WATA04			(4)			// ���낢�킽��
#define	IMC_ACCE_WATA05			(5)			// �I�����W�̂킽��
#define	IMC_ACCE_STONE00		(6)			// �܂�܂�X�g�[��
#define	IMC_ACCE_STONE01		(7)			// ���炫��X�g�[��
#define	IMC_ACCE_STONE02		(8)			// �����X�g�[��
#define	IMC_ACCE_STONE03		(9)			// �����X�g�[��
#define	IMC_ACCE_STONE04		(10)		// �܂�����X�g�[��
#define	IMC_ACCE_STONE05		(11)		// ���уX�g�[��
#define	IMC_ACCE_UROKO00		(12)		// �s���N�̃E���R
#define	IMC_ACCE_UROKO01		(13)		// �������E���R
#define	IMC_ACCE_UROKO02		(14)		// �݂ǂ�̃E���R
#define	IMC_ACCE_UROKO03		(15)		// �ނ炳���̃E���R
#define	IMC_ACCE_UROKO04		(16)		// ���������E���R
#define	IMC_ACCE_UROKO05		(17)		// �ق����E���R
#define	IMC_ACCE_HANE00			(18)		// �������͂�
#define	IMC_ACCE_HANE01			(19)		// �������͂�
#define	IMC_ACCE_HANE02			(20)		// ������̂͂�
#define	IMC_ACCE_HANE03			(21)		// ���낢�͂�
#define	IMC_ACCE_HANE_TABA00	(22)		// ���낢����тЂ�
#define	IMC_ACCE_HANE_TABA01	(23)		// ���낢����тЂ�
#define	IMC_ACCE_HANE_GROUP00	(24)		// ���낢�Ђ�
#define	IMC_ACCE_HANE_GROUP01	(25)		// ���낢�Ђ�
#define	IMC_ACCE_LEAF00			(26)		// ���������͂���
#define	IMC_ACCE_LEAF01			(27)		// ���������͂���
#define	IMC_ACCE_LEAF02			(28)		// �ق����͂���
#define	IMC_ACCE_TUME00			(29)		// �߂̃J��
#define	IMC_ACCE_TUME01			(30)		// �̂̃J��
#define	IMA_ACCE_MUSHROOM00		(31)		// �ق����L�m�R
#define	IMA_ACCE_MUSHROOM01		(32)		// �ӂƂ��L�m�R
#define	IMC_ACCE_KIRIKABU00		(33)		// ���肩��
#define	IMC_ACCE_DROP00			(34)		// ���ꂢ�Ȃ�����
#define	IMC_ACCE_SNOWDUST00		(35)		// �䂫�̂������傤
#define	IMC_ACCE_SPARK00		(36)		// �p�`�p�`�Ђ΂�
#define	IMC_ACCE_FIRE00			(37)		// ���������ق̂�
#define	IMC_ACCE_FIRE01			(38)		// �ӂ����Ȃق̂�
#define	IMC_ACCE_KIAI00			(39)		// �ɂ��݂ł邫����
#define	IMC_ACCE_SPOON00		(40)		// �ӂ����ȃX�v�[��
#define	IMC_ACCE_SMOKE00		(41)		// ���R���R���ނ�
#define	IMC_ACCE_HEDORO00		(42)		// �ǂ��G�L�X
#define	IMC_ACCE_COIN00			(43)		// �����˂����R�C��
#define	IMC_ACCE_HORROR00		(44)		// �Ԃ��݂Ȃ���
#define	IMC_ACCE_SPRING00		(45)		// �o�l
#define	IMC_ACCE_SHELL00		(46)		// �����̂�����
#define	IMC_ACCE_NOTE00			(47)		// �͂Ȃ��������
#define	IMC_ACCE_PIKAPIKA_POWDER00	(48)	// �s�J�s�J�p�E�_�[
#define	IMC_ACCE_KIRAKIRA_POWDER00	(49)	// �L���L���p�E�_�[
#define	IMC_ACCE_FLOWER00		(50)		// �������͂�
#define	IMC_ACCE_FLOWER01		(51)		// �s���N�̂͂�
#define	IMC_ACCE_FLOWER02		(52)		// ���낢�͂�
#define	IMC_ACCE_FLOWER03		(53)		// �������͂�
#define	IMC_ACCE_FLOWER04		(54)		// �I�����W�̂͂�
#define	IMC_ACCE_FLOWER05		(55)		// ������̂͂�
#define	IMC_ACCE_GLASSES00		(56)		// ���邮�郁�K�l
#define	IMC_ACCE_GLASSES01		(57)		// �܂����냁�K�l
#define	IMC_ACCE_GLASSES02		(58)		// �S�[�W���X���K�l
#define	IMC_ACCE_CANDY00		(59)		// ���܂��L�����f�B
#define	IMC_ACCE_PAPERSTORM00	(60)		// ���݂ӂԂ�
#define	IMC_ACCE_PARASOL00		(61)		// �J���t���p���\��
#define	IMC_ACCE_PARASOL01		(62)		// �J���J�T
#define	IMC_ACCE_SPOTLIGHT00	(63)		// �X�|�b�g���C�g
#define	IMC_ACCE_CAPE00			(64)		// �}���g
#define	IMC_ACCE_MIKE00			(65)		// �X�^���h�}�C�N
#define	IMC_ACCE_SURFBOARD00	(66)		// �T�[�t�{�[�h
#define	IMC_ACCE_ZYUTAN00		(67)		// �J�[�y�b�g
#define	IMC_ACCE_DOKAN00		(68)		// �Ȃ����ǂ���
#define	IMC_ACCE_BED00			(69)		// �ӂ�ӂ�x�b�h
#define	IMC_ACCE_BALL00			(70)		// �~���[�{�[��
#define	IMC_ACCE_BAG00			(71)		// ������������΂�
#define	IMC_ACCE_RIBBON00		(72)		// �s���N�̂��݂ǂ�
#define	IMC_ACCE_RIBBON01		(73)		// �܂����Ȃ��݂ǂ�
#define	IMC_ACCE_RIBBON02		(74)		// �u���[�̂��݂ǂ�
#define	IMC_ACCE_RIBBON03		(75)		// ������̂��݂ǂ�
#define	IMC_ACCE_RIBBON04		(76)		// �݂ǂ�̂��݂ǂ�
#define	IMC_ACCE_BALLOON00		(77)		// �s���N�̂ӂ�����
#define	IMC_ACCE_BALLOON01		(78)		// �������ӂ�����
#define	IMC_ACCE_BALLOON02		(79)		// �������ӂ�����
#define	IMC_ACCE_BALLOON03		(80)		// ������̂ӂ�����
#define	IMC_ACCE_BALLOON04		(81)		// �݂ǂ�̂ӂ�����
#define	IMC_ACCE_HAT00			(82)		// �w�b�h�h���X
#define	IMC_ACCE_HAT01			(83)		// �V���N�n�b�g
#define	IMC_ACCE_HAT02			(84)		// ���ʂ̃x�[��
#define	IMC_ACCE_HAT03			(85)		// ���Ȃт��n�`�}�L
#define	IMC_ACCE_HAT04			(86)		// �͂����̂ڂ���
#define	IMC_ACCE_STAGE00		(87)		// ���͂Ȃ̃X�e�[�W
#define	IMC_ACCE_STAGE01		(88)		// ����̂���������
#define	IMC_ACCE_STAGE02		(89)		// �K���X�̃X�e�[�W
#define	IMC_ACCE_HYOSHODAI00	(90)		// �Ђ傤���傤����
#define	IMC_ACCE_STAGE03		(91)		// �L���[�u�X�e�[�W
#define	IMC_ACCE_OMEN00			(92)		// �i�G�g�����߂�
#define	IMC_ACCE_OMEN01			(93)		// �q�R�U�����߂�
#define	IMC_ACCE_OMEN02			(94)		// �|�b�`���}���߂�
#define	IMC_ACCE_TREE00			(95)		// ����������
#define	IMC_ACCE_FLAG00			(96)		// �t���b�O
#define	IMC_ACCE_CROWN00		(97)		// �N���E��
#define	IMC_ACCE_TIARA00		(98)		// �e�B�A��
#define	IMC_ACCE_NAGAREBOSI00	(99)		// �Ȃ���ڂ�

#define	IMC_ACCE_MAX			(100)

//-------------------------------------
//	
// BG�f�[�^��
//	
//=====================================
// �E��ʗp
#define	IMC_BG_RIGHT_00		(0)
#define	IMC_BG_RIGHT_01		(1)
#define	IMC_BG_RIGHT_02		(2)
#define	IMC_BG_RIGHT_03		(3)
#define	IMC_BG_RIGHT_04		(4)
#define	IMC_BG_RIGHT_05		(5)
#define	IMC_BG_RIGHT_06		(6)
#define	IMC_BG_RIGHT_07		(7)
#define	IMC_BG_RIGHT_08		(8)
#define	IMC_BG_RIGHT_09		(9)
#define	IMC_BG_RIGHT_10		(10)
#define	IMC_BG_RIGHT_11		(11)
#define	IMC_BG_RIGHT_12		(12)
#define	IMC_BG_RIGHT_13		(13)
#define	IMC_BG_RIGHT_14		(14)
#define	IMC_BG_RIGHT_15		(15)
#define	IMC_BG_RIGHT_16		(16)
#define	IMC_BG_RIGHT_17		(17)
#define	IMC_BG_RIGHT_MAX	(18)


//-----------------------------------------------------------------------------
/**
 *					�\���̐錾
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
/**
 *					�v���g�^�C�v�錾
*/
//-----------------------------------------------------------------------------
#undef	GLOBAL
#endif		// __IMC_ITEMID_DEFINE_H__

