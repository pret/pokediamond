//============================================================================================
/**
 * @file	sysflag_def.h
 * @bfief	�V�X�e���t���O��`
 * @author	Satoshi Nohara
 * @date	06.04.14
 */
//============================================================================================
#ifndef	__SYSFLAG_DEF_H__
#define	__SYSFLAG_DEF_H__


//============================================================================================
//	�t���O��`
//
//	�X�N���v�g			��`�𒼐ڎQ�Ƃ��Ă悢�I
//
//	�v���O����			sysflag.h�ɂ���A�N�Z�X�֐����g���I
//
//	SYSFLAG_MAX = 320
//	SYS_FLAG_ARRIVE_START(80) �i���o�[���d�����Ȃ��悤�ɒ��ӁI
//============================================================================================
#define	SYS_FLAG_BAG_GET				(SYSFLAG_START+0)		//�o�b�O����
#define	SYS_FLAG_PAIR					(SYSFLAG_START+1)		//�A������t���O
#define	SYS_FLAG_KAIRIKI				(SYSFLAG_START+2)		//�����肫��ԃt���O
#define	SYS_FLAG_FNOTE_GET				(SYSFLAG_START+3)		//�`���m�[�g����
#define	SYS_FLAG_GAME_CLEAR				(SYSFLAG_START+4)		//�Q�[���N���A
#define	SYS_FLAG_ONE_STEP				(SYSFLAG_START+5)		//������������t���O
#define	SYS_FLAG_COMM_COUNTER			(SYSFLAG_START+6)		//�ʐM�J�E���^�[�ʉ߃t���O
#define	SYS_FLAG_SAFARI_MODE			(SYSFLAG_START+7)		//�T�t�@�����[�h�t���O
#define	SYS_FLAG_CON_STYLE_MASTER		(SYSFLAG_START+8)		//�R���e�X�g�}�X�^�[�����N�N���A
#define	SYS_FLAG_CON_BEAUTIFUL_MASTER	(SYSFLAG_START+9)		//�R���e�X�g�}�X�^�[�����N�N���A
#define	SYS_FLAG_CON_CUTE_MASTER		(SYSFLAG_START+10)		//�R���e�X�g�}�X�^�[�����N�N���A
#define	SYS_FLAG_CON_CLEVER_MASTER		(SYSFLAG_START+11)		//�R���e�X�g�}�X�^�[�����N�N���A
#define	SYS_FLAG_CON_STRONG_MASTER		(SYSFLAG_START+12)		//�R���e�X�g�}�X�^�[�����N�N���A
#define	SYS_FLAG_BTL_SEARCHER_USE		(SYSFLAG_START+13)		//�o�g���T�[�`���[���g�p��
#define	SYS_FLAG_UG_ARRIVE				(SYSFLAG_START+14)		//�n���F����
#define	SYS_FLAG_UG_DIG					(SYSFLAG_START+15)		//�n���F����
#define	SYS_FLAG_UG_TAMA				(SYSFLAG_START+16)		//�n���F��
#define	SYS_FLAG_UG_BASE				(SYSFLAG_START+17)		//�n���F��n
#define	SYS_FLAG_UG_GOODS				(SYSFLAG_START+18)		//�n���F�͗l�ւ�
#define	SYS_FLAG_UG_HATA				(SYSFLAG_START+19)		//�n���F��
#define	SYS_FLAG_GTC_OPEN				(SYSFLAG_START+20)		//�{�݁FGTC
#define	SYS_FLAG_BTOWER_OPEN			(SYSFLAG_START+21)		//�{�݁F�o�g���^���[
#define	SYS_FLAG_SHIP					(SYSFLAG_START+22)		//�D�g�p�\
//#define	SYS_FLAG_					(SYSFLAG_START+23)		//
#define	SYS_FLAG_PST					(SYSFLAG_START+24)		//�|�P�����X�e�[�^�X�@�R���e�X�g�Z
#define	SYS_FLAG_POKEPARK_MODE			(SYSFLAG_START+25)		//�|�P�p�[�N���[�h�t���O
#define SYS_FLAG_FLASH					(SYSFLAG_START+26)		//�t���b�V����ԃt���O
#define	SYS_FLAG_KIRIBARAI				(SYSFLAG_START+27)		//��������ԃt���O
#define	SYS_FLAG_POKETCH_HOOK			(SYSFLAG_START+28)		//�|�P�b�`�}�~�t���O
#define	SYS_FLAG_REIAIHAI				(SYSFLAG_START+29)		//���C�A�C�n�C�~�o�t���O
#define	SYS_FLAG_MIZUKI					(SYSFLAG_START+30)		//�~�Y�L�t���O(PC�Ǘ���)
#define	SYS_FLAG_BS_LV1					(SYSFLAG_START+31)		//�o�g���T�[�`���[LV1
#define	SYS_FLAG_BS_LV2					(SYSFLAG_START+32)		//�o�g���T�[�`���[LV2
#define	SYS_FLAG_BS_LV3					(SYSFLAG_START+33)		//�o�g���T�[�`���[LV3
#define	SYS_FLAG_BS_LV4					(SYSFLAG_START+34)		//�o�g���T�[�`���[LV4
#define	SYS_FLAG_BS_LV5					(SYSFLAG_START+35)		//�o�g���T�[�`���[LV5
#define	SYS_FLAG_BGM_D28				(SYSFLAG_START+36)		//�C�x���gBGM�؂�ւ�
#define	SYS_FLAG_BGM_GINGA				(SYSFLAG_START+37)		//�C�x���gBGM�؂�ւ�
#define	SYS_FLAG_BGM_D26				(SYSFLAG_START+38)		//�C�x���gBGM�؂�ւ�
#define	SYS_FLAG_BGM_C04				(SYSFLAG_START+39)		//�C�x���gBGM�؂�ւ�
#define	SYS_FLAG_BGM_D02				(SYSFLAG_START+40)		//�C�x���gBGM�؂�ւ�
#define	SYS_FLAG_BGM_D13				(SYSFLAG_START+41)		//�C�x���gBGM�؂�ւ�
#define	SYS_FLAG_BGM_R224				(SYSFLAG_START+42)		//�C�x���gBGM�؂�ւ�
#define	SYS_FLAG_BGM_C10				(SYSFLAG_START+43)		//�C�x���gBGM�؂�ւ�
#define	SYS_FLAG_WIFI_USE				(SYSFLAG_START+44)		//WiFi�Ɍq����
#define	SYS_FLAG_T05_GINGA_EVENT		(SYSFLAG_START+45)		//�J���i�M�̃M���K�c�C�x���g
#define	SYS_FLAG_BGM_D27				(SYSFLAG_START+46)		//�C�x���gBGM�؂�ւ�
#define	SYS_FLAG_BGM_D29				(SYSFLAG_START+47)		//�C�x���gBGM�؂�ւ�
#define	SYS_FLAG_BGM_D16				(SYSFLAG_START+48)		//�C�x���gBGM�؂�ւ�
#define	SYS_FLAG_BGM_C02				(SYSFLAG_START+49)		//�C�x���gBGM�؂�ւ�
#define	SYS_FLAG_UG_FIRST				(SYSFLAG_START+50)		//�n������C�x���g
#define	SYS_FLAG_BGM_T02				(SYSFLAG_START+51)		//�C�x���gBGM�؂�ւ�
#define SYS_FLAG_CYCLINGROAD			(SYSFLAG_START+52)		//�T�C�N�����O���[�h���[�h�t���O
#define	SYS_FLAG_BGM_D10				(SYSFLAG_START+53)		//�C�x���gBGM�؂�ւ�


//--------------------------------------------------------------------------------------------
//�����t���O����p��`
//
//	SYSFLAG_MAX = 320
//	SYS_FLAG_ARRIVE_START(80) + FLAG_ARRIVE_MAX(66) = 146 �����Ȃ��悤�ɒ��ӁI
//--------------------------------------------------------------------------------------------
#define	SYS_FLAG_ARRIVE_START			(SYSFLAG_START+80)

#define	FLAG_ARRIVE_T01		( 0)
#define	FLAG_ARRIVE_T02		( 1)
#define	FLAG_ARRIVE_T03		( 2)
#define	FLAG_ARRIVE_T04		( 3)
#define	FLAG_ARRIVE_T05		( 4)
#define	FLAG_ARRIVE_T06		( 5)
#define	FLAG_ARRIVE_T07		( 6)
#define	FLAG_ARRIVE_C01		( 7)
#define	FLAG_ARRIVE_C02		( 8)
#define	FLAG_ARRIVE_C03		( 9)
#define	FLAG_ARRIVE_C04		(10)
#define	FLAG_ARRIVE_C05		(11)
#define	FLAG_ARRIVE_C06		(12)
#define	FLAG_ARRIVE_C07		(13)
#define	FLAG_ARRIVE_C08		(14)
#define	FLAG_ARRIVE_C09		(15)
#define	FLAG_ARRIVE_C10		(16)
#define	FLAG_ARRIVE_C11		(17)

//060525 �{�ݓ����t���O�ǉ�
#define FLAG_ARRIVE_D01R0101	(18)	//�N���K�l�Y�z//
#define FLAG_ARRIVE_D02R0101	(19)	//�J�Ԃ̔��d��//
#define FLAG_ARRIVE_D03			(20)	//�t���O�s�v//�n�N�^�C�̐X
#define FLAG_ARRIVE_D04R0101	(21)	//�^�^�����S��//
#define FLAG_ARRIVE_D05			(22)	//�t���O�s�v//�V���R
#define FLAG_ARRIVE_D05R0114	(23)	//���̒�//
#define FLAG_ARRIVE_D06			(24)	//�t���O�s�v//�厼��
#define FLAG_ARRIVE_D07R0102	(25)	//�Y�C�̈��//
#define FLAG_ARRIVE_D09R0101	(26)	//�`�����s�I�����[�h//
#define FLAG_ARRIVE_D10R0101	(27)	//�|�P�����p�[�N//
#define FLAG_ARRIVE_D11R0101	(28)	//�G�ꂠ���L��//
#define FLAG_ARRIVE_D12R0101	(29)	//�r�ꂽ������//
#define FLAG_ARRIVE_D13R0101	(30)	//�\�m�I�̉Ԕ�//
#define FLAG_ARRIVE_D14R0101	(31)	//�N���K�l�Q�[�g//
#define FLAG_ARRIVE_D15			(32)	//�B���}�b�v�t���O//�B���|�P�����u���[�o�X�v�̓�
#define FLAG_ARRIVE_D16			(33)	//�t���O�s�v//�ΎR
#define FLAG_ARRIVE_D16R0101	(34)	//�n�[�h�}�E���e���i�ΎR���A�j//
#define FLAG_ARRIVE_D17			(35)	//�B���}�b�v�t���O//����̐�i�k�O�S�΁j
#define FLAG_ARRIVE_D17R0102	(36)	//�߂�̓��A//
#define FLAG_ARRIVE_D18			(37)	//�B���}�b�v�t���O//�z�z�|�P�����u�G�E���X�v�̓��B
#define FLAG_ARRIVE_D20R0101	(38)	//�L�b�T�L�_�a//
#define FLAG_ARRIVE_D21R0101	(39)	//�����̓��A//
#define FLAG_ARRIVE_D22R0101	(40)	//��Ճ}�j�A�̌�//
#define FLAG_ARRIVE_D23R0101	(41)	//�����̗���//
#define FLAG_ARRIVE_D24			(42)	//�t���O�s�v//�|�S��
#define FLAG_ARRIVE_D24R0101	(43)	//�z�R//
#define FLAG_ARRIVE_D25R0101	(44)	//�X�̗m��//
#define FLAG_ARRIVE_D26R0101	(45)	//�M���K�c�A�W�g//
#define FLAG_ARRIVE_D27			(46)	//�t���O�s�v//�k�O�P��
#define FLAG_ARRIVE_D27R0103	(47)	//�k�O�P�΂̓������A//
#define FLAG_ARRIVE_D28			(48)	//�t���O�s�v//�k�O�Q��
#define FLAG_ARRIVE_D28R0103	(49)	//�k�O�Q�΂̓������A//
#define FLAG_ARRIVE_D29			(50)	//�t���O�s�v//�k�O�R��
#define FLAG_ARRIVE_D29R0103	(51)	//�k�O�R�΂̓������A//
#define FLAG_ARRIVE_D30			(52)	//�B���}�b�v�t���O//�z�z�|�P�����u�_�[�N�v�̓�
#define FLAG_ARRIVE_C11R0101	(53)	//�o�g���^���[��t�Q�[�g//
#define FLAG_ARRIVE_R206		(54)	//�t���O�s�v//�T�C�N�����O���[�h
#define FLAG_ARRIVE_R208R0101	(55)	//�؂̎���//
#define FLAG_ARRIVE_R209R0101	(56)	//���X�g�^���[//
#define FLAG_ARRIVE_R210AR0101	(57)	//�i���X//
#define FLAG_ARRIVE_R210BR0101	(58)	//�ŋ��h���S���Z�����̉�//
#define FLAG_ARRIVE_R212AR0101	(59)	//�|�P�������~�Ɨ���//
#define FLAG_ARRIVE_R212BR0101	(60)	//������Ɠ�����������Ă���閯��//
#define FLAG_ARRIVE_R213R0201	(61)	//���Ք��m�̉�//
#define FLAG_ARRIVE_L02R0101	(62)	//�z�e�����X�g����//
#define FLAG_ARRIVE_R222R0101	(63)	//�ނ�I���W�̉�//
#define FLAG_ARRIVE_R222R0201	(64)	//�傫����ׂ̉�//
#define FLAG_ARRIVE_W226R0101	(65)	//�C�O�Ń|�P�����ƌ������Ă����e��//

#define	FLAG_ARRIVE_R221		(66)	//�|�P�p�[�N�{��//
#define	FLAG_ARRIVE_R221R0101	(67)	//�|�P�p�[�N��t//
#define	FLAG_ARRIVE_CHAMPLEAGUE	(68)	//�`�����s�I�����[�O//

#define	FLAG_ARRIVE_MAX			(69)


//�t���O�̍ő吔�ȂǊm�F����I


//============================================================================================
//
//============================================================================================
//�o�b�W���ʒ�`(MyStatus_GetBadgeFlag)
#define BADGE_ID_C03			(0)						//�N���K�l
#define BADGE_ID_C04			(1)						//�n�N�^�C
#define BADGE_ID_C07			(2)						//�g�p��
#define BADGE_ID_C06			(3)						//�m���Z
#define BADGE_ID_C05			(4)						//���X�K
#define BADGE_ID_C02			(5)						//�~�I
#define BADGE_ID_C09			(6)						//�L�b�T�L
#define BADGE_ID_C08			(7)						//�i�M�T
#define BADGE_MAX				(8)						//�o�b�W�ő吔

#endif	//__SYSFLAG_DEF_H__


