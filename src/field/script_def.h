//============================================================================================
/**
 * @file	script_def.h
 * @bfief	�X�N���v�g��`�t�@�C��
 * @author	Satoshi Nohara
 * @date	05.12.14
 */
//============================================================================================
#ifndef SCRIPT_DEF_H
#define SCRIPT_DEF_H


//============================================================================================
//
//	��`
//
//============================================================================================
//����X�N���v�g��`
#define SP_SCRID_NONE				(0)
#define SP_SCRID_SCENE_CHANGE		(1)
#define SP_SCRID_FLAG_CHANGE		(2)
#define SP_SCRID_OBJ_CHANGE			(3)			//���ӁI�@�t�B�[���h�������ŌĂ΂��
#define SP_SCRID_INIT_CHANGE		(4)

//�G�C���A�X���ʗp�X�N���v�gID
#define SP_SCRID_ALIES				(0xffff)

//�g���[�i�[�^�C�v��`
#define SCR_EYE_TR_TYPE_SINGLE		(0)
#define SCR_EYE_TR_TYPE_DOUBLE		(1)
#define SCR_EYE_TR_TYPE_TAG			(2)

//�g���[�i�[�̔ԍ���`
#define SCR_EYE_TR_0				(0)
#define SCR_EYE_TR_1				(1)

//fld_menu.c
#define SCR_REPORT_OK				(0)			//�Z�[�u����
#define SCR_REPORT_CANCEL			(1)			//�Z�[�u���Ă��Ȃ�

//�A�����OBJ���擾����OBJID��`
#define SCR_OBJID_MV_PAIR			(0xf2)

//�����_�~�[OBJ���擾����OBJID��`
#define SCR_OBJID_DUMMY				(0xf1)

//�t���O����֐��̃��[�h�w��p
#define	FLAG_MODE_RESET				(0)
#define	FLAG_MODE_SET				(1)
#define	FLAG_MODE_GET				(2)

//�G���x�[�^�A�j��
#define T07R0103_ELEVATOR_LOOP		(4)
#define C05R0103_ELEVATOR_LOOP		(4)
#define C05R0803_ELEVATOR_LOOP		(4)
#define C07R0206_ELEVATOR_LOOP		(4)
#define C08R0802_ELEVATOR_LOOP		(4)
#define C01R0208_ELEVATOR_LOOP		(4)

//�j���擾�֐��̖߂�l
#define RTC_WEEK_SUNDAY		0
#define RTC_WEEK_MONDAY		1
#define RTC_WEEK_TUESDAY	2
#define RTC_WEEK_WEDNESDAY	3
#define RTC_WEEK_THURSDAY	4
#define RTC_WEEK_FRIDAY		5
#define RTC_WEEK_SATURDAY	6

//�}�Ӄ��[�h
#define SCR_SHINOU_ZUKAN_MODE	0
#define SCR_ZENKOKU_ZUKAN_MODE	1

//�p�\�R���A�j���Ǘ��i���o�[
#define SCR_PASO_ANM_NO		90


#endif	/* SCRIPT_DEF_H */


