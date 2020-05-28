//============================================================================================
/**
 * @file	syswork_def.h
 * @bfief	�V�X�e�����[�N��`
 * @author	Satoshi Nohara
 * @date	06.04.14
 */
//============================================================================================
#ifndef	__SYSWORK_DEF_H__
#define	__SYSWORK_DEF_H__


//============================================================================================
//	�t���O��`
//
//	�X�N���v�g			��`�𒼐ڎQ�Ƃ��Ă悢�I
//
//	�v���O����			syswork.h�ɂ���A�N�Z�X�֐����g���I
//
//============================================================================================
#define		SYS_WORK_FIRST_POKE_NO		(0+OTHERS_WORK_START)	//�ŏ��̃|�P�����i���o�[
//#define	SYS_WORK_POISON_STEP_COUNT	(1+OTHERS_WORK_START)	//�ŕ����J�E���^�[
//#define	SYS_WORK_ELEVATOR_FLOOR		(2+OTHERS_WORK_START)	//�G���x�[�^�t���A�i���o�[
#define		SYS_WORK_BTL_SEARCHER_BATTERY	(3+OTHERS_WORK_START)	//�o�g���T�[�`���[�o�b�e���[
#define		SYS_WORK_BTL_SEARCHER_CLEAR	(4+OTHERS_WORK_START)	//�o�g���T�[�`���[�N���A
#define		SYS_WORK_OOKISA_RECORD		(5+OTHERS_WORK_START)	//�傫����חp���R�[�h�i�ő̒l�j
#define		SYS_WORK_HIDEMAP_01			(6+OTHERS_WORK_START)	//�B���}�b�v����p���[�N���̂P
#define		SYS_WORK_HIDEMAP_02			(7+OTHERS_WORK_START)	//�B���}�b�v����p���[�N���̂Q
#define		SYS_WORK_HIDEMAP_03			(8+OTHERS_WORK_START)	//�B���}�b�v����p���[�N���̂R
#define		SYS_WORK_HIDEMAP_04			(9+OTHERS_WORK_START)	//�B���}�b�v����p���[�N���̂S
#define		SYS_WORK_PARK_WALK_COUNT	(10+OTHERS_WORK_START)	//���R�����ł̕����J�E���g
#define		SYS_WORK_NEWS_DAYS_COUNT	(11+OTHERS_WORK_START)	//�V���В��ߐ؂�J�E���^
#define		SYS_WORK_POKELOT_RND1		(12+OTHERS_WORK_START)	//�|�P�����N�W�p32bit
#define		SYS_WORK_POKELOT_RND2		(13+OTHERS_WORK_START)	//�|�P�����N�W�p32bit
#define		SYS_WORK_UG_TALK_COUNT		(14+OTHERS_WORK_START)	//�n����b�J�E���g�p(�~�J�Q�p�j
#define		SYS_WORK_PAIR_TRAINER_ID	(15+OTHERS_WORK_START)	//�A������g���[�i�[ID
#define		SYS_WORK_RENSYOU_COUNT		(16+OTHERS_WORK_START)	//�X���b�g�A���ő吔
#define		SYS_WORK_POKE_LEVEL_NO		(17+OTHERS_WORK_START)	//�|�P�������x���ŃA�C�e������
#define		SYS_WORK_DEPART_COUNT		(18+OTHERS_WORK_START)	//�f�p�[�g�ł̍w����
#define		SYS_WORK_HAIHU_EVENT01		(19+OTHERS_WORK_START)	//�z�z�C�x���g����p���[�N���̂P
#define		SYS_WORK_HAIHU_EVENT02		(20+OTHERS_WORK_START)	//�z�z�C�x���g����p���[�N���̂Q
#define		SYS_WORK_HAIHU_EVENT03		(21+OTHERS_WORK_START)	//�z�z�C�x���g����p���[�N���̂R
#define		SYS_WORK_UG_TOOL_GIVE_COUNT	(22+OTHERS_WORK_START)	//�n�� �������������
#define		SYS_WORK_UG_KASEKI_DIG_COUNT	(23+OTHERS_WORK_START)	//�n�� ���������@������
#define		SYS_WORK_UG_TRAP_HIT_COUNT	(24+OTHERS_WORK_START)	//�n�� �g���b�v�ɂ�������
#define		SYS_WORK_UG_TALK_COUNT2		(25+OTHERS_WORK_START)	//�n����b�J�E���g�p
#define		SYS_WORK_FRIENDLY_COUNT		(26+OTHERS_WORK_START)	//�Ȃ��x�p�����J�E���g


//���[�N�̍ő吔�ȂǊm�F����I
//0 - 63

//============================================================================================
//
//		�z�z�C�x���g�p��`
//
//============================================================================================
#define		HAIHUEVENT_ID_D30		0		///<�z�z�C�x���g�F�_�[���C�i�_�[�N�j
#define		HAIHUEVENT_ID_D18		1		///<�z�z�C�x���g�F�~�[�V�G�i�G�E���X�j
#define		HAIHUEVENT_ID_D05		2		///<�z�z�C�x���g�F�A���Z�E�X�i�A�E�X�j

//============================================================================================
//
//		�B���}�b�v���ʒ�`
//
//============================================================================================
#define		HIDEMAP_ID_D15	(0)				///<�B���}�b�v�FD15
#define		HIDEMAP_ID_D30	(1)				///<�z�z�}�b�v�FD30
#define		HIDEMAP_ID_L04	(2)				///<�B���}�b�v�FL04
#define		HIDEMAP_ID_D18	(3)				///<�z�z�}�b�v�FD18
#endif	//__SYSWORK_DEF_H__



