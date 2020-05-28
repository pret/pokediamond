
//============================================================================================
/**
 * @file	server.h
 * @bfief	�퓬�T�[�o�v���O����
 * @author	HisashiSogabe
 * @date	05.05.24
 */
//============================================================================================

#ifndef __SERVER_H_
#define __SERVER_H_

#include	"battle/battle_common.h"

#define	SERVER_QUE_TIME_OUT		(60*30)	///<ServerQueCheck���̃^�C���A�E�g�J�E���g�i60�b�j

//ServerSequenceTbl�̃V�[�P���X�i���o�[
enum{
	SERVER_POKEMON_PARAM_GET_NO,		///<�|�P�����p�����[�^���T�[�o���[�N�ɃQ�b�g
	SERVER_ENCOUNT_SET_NO,				///<�G���J�E���g����
	SERVER_TRAINER_MESSAGE_NO,			///<�퓬���Ƀg���[�i�[���o�Ă��ă��b�Z�[�W�\��
	SERVER_POKE_APPEAR_CHECK_NO,		///<�|�P�����o�ꎞ�Ƀ`�F�b�N���鍀��
	SERVER_COMMAND_SELECT_INIT_NO,		///<�R�}���h�I������������
	SERVER_COMMAND_SELECT_NO,			///<�R�}���h�I������
	SERVER_AGI_CALC_NO,					///<�f�����v�Z����
	SERVER_BEFORE_ACT_NO,				///<����O����
	SERVER_ACTION_BRANCH_NO,			///<���앪�򏈗�
	SERVER_FIELD_CONDITION_CHECK_NO,	///<��ɂ������Ă���퓬���ʃ`�F�b�N
	SERVER_POKE_CONDITION_CHECK_NO,		///<�|�P�����ɂ������Ă���퓬���ʃ`�F�b�N
	SERVER_SIDE_CONDITION_CHECK_NO,		///<�|�P�����ɂ������Ă���퓬���ʃ`�F�b�N�i���ɂ������Ă�����ʁj
	SERVER_TURN_END_NO,					///<�퓬�^�[���I������

	SERVER_FIGHT_COMMAND_NO,			///<�����������쏈��
	SERVER_ITEM_COMMAND_NO,				///<����g�p����
	SERVER_POKEMON_COMMAND_NO,			///<�|�P�����I������
	SERVER_ESCAPE_COMMAND_NO,			///<�ɂ��铮�쏈��

	SERVER_SAFARI_BALL_NO,				///<�T�t�@���{�[�������鏈��
	SERVER_SAFARI_ESA_NO,				///<�T�t�@���G�T�����鏈��
	SERVER_SAFARI_DORO_NO,				///<�T�t�@���h�������鏈��
	SERVER_SAFARI_YOUSUMI_NO,			///<�T�t�@���l�q������

	SERVER_WAZA_SEQUENCE_NO,			///<�Z�V�[�P���X���s
	SERVER_WAZA_BEFORE_NO,				///<�Z�O����
	SERVER_WAZA_OUT_CHECK_NO,			///<�Z�����`�F�b�N
	SERVER_ADD_STATUS_DIRECT_CHECK_NO,	///<�ǉ����ʃ`�F�b�N�i���ڒǉ��̂݁j
	SERVER_WAZA_HAZURE_MESSAGE_NO,		///<������Ȃ������n���b�Z�[�W�\��
	SERVER_WAZA_OUT_NO,					///<�Z��������
	SERVER_HP_CALC_NO,					///<HP�v�Z
	SERVER_WAZA_OUT_AFTER_MESSAGE_NO,	///<�Z���ł���̂��낢��ȃ��b�Z�[�W�\��
	SERVER_ADD_STATUS_CHECK_NO,			///<�ǉ����ʃ`�F�b�N�i���ڒǉ��ȊO�j
	SERVER_WAZA_OUT_AFTER_KOUKA_NO,		///<�Z���ł���̂��낢��Ȍ��ʃ`�F�b�N
	SERVER_RENZOKU_CHECK_NO,			///<�A���U���̃`�F�b�N
	SERVER_SINKURO_CHECK_NO,			///<�V���N���`�F�b�N
	SERVER_KIZETSU_EFFECT_NO,			///<�C��G�t�F�N�g
	SERVER_LOOP_CHECK_NO,				///<�����̓�����Z�̃`�F�b�N
	SERVER_JIBAKU_EFFECT_NO,			///<���΂��ɂ��C��G�t�F�N�g
	SERVER_WAZA_HIT_AFTER_CHECK_NO,		///<�Z���q�b�g������̃`�F�b�N
	SERVER_GET_EXP_EFFECT_NO,			///<�o���l�擾�`�F�b�N
	SERVER_WAZA_NO_BUFFER_SET_NO,		///<�Z�i���o�[���o�b�t�@�֊i�[
	SERVER_WAZA_END_NO,					///<�Z�V�[�P���X�I��

	SERVER_POKE_RESHUFFLE_AFTER_NO,		///<�|�P�������ꂩ����V�[�P���X

	SERVER_WIN_LOSE_NO,					///<�퓬���s�V�[�P���X

//	SERVER_QUE_CHECK_NO,				///<�T�[�o�L���[���`�F�b�N���ďI����҂�

	SERVER_FIGHT_END_NO,				///<�퓬�I��
	SERVER_FIGHT_END_WAIT_NO			///<�퓬�I���i�ʐM�ΐ펞�̑҂��j
};

extern	void	*ServerInit(BATTLE_WORK *bw);
extern	int		ServerMain(BATTLE_WORK *battle_work,SERVER_PARAM *server_param);
extern	void	ServerEnd(SERVER_PARAM *server_param);

extern	void	ServerHitCheckAct(BATTLE_WORK *bw,SERVER_PARAM *sp,int attack,int defence,int waza_no);

#endif __SERVER_H_
