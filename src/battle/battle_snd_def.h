//==============================================================================
/**
 * @file	battle_snd_def.h
 * @brief	�퓬�̌��ʉ��ݒ�t�@�C��
 * @author	matsuda
 * @date	2006.03.28(��)
 */
//==============================================================================
#ifndef __BATTLE_SND_DEF_H__
#define __BATTLE_SND_DEF_H__

///�퓬���͉�ʃJ�[�\���ړ���
#define BCURSOR_MOVE_SE			(SEQ_SE_DP_SELECT)
///�擪���͉�ʁF�R�}���h�I���E�B���h�E�X���C�h�C��
#define BCOMMAND_SLIDEIN		(SEQ_SE_DP_SLIDEIN)

///< �G���J�E���g�G�t�F�N�g
#define BECEFF_GRASS_01			(SEQ_SE_DP_PASA2)
#define BECEFF_GRASS_02			(SEQ_SE_DP_PASA3)

///<�Z�̈З�SE
#define	BSE_HIT_NORMAL			(SEQ_SE_DP_KOUKA_M)
#define	BSE_HIT_BATSUGUN		(SEQ_SE_DP_KOUKA_H)
#define	BSE_HIT_IMAHITOTSU		(SEQ_SE_DP_KOUKA_L)

///<�^�b�`�p�l���v�b�V����
#define	BSE_TP_DECIDE			(SEQ_SE_DP_DECIDE)

///<�o���l�擾��
#define	BSE_EXP_GET				(SEQ_SE_DP_EXP)

///<�o���lMAX��
#define	BSE_EXP_MAX				(SEQ_SE_DP_EXPMAX)

///<�|�P�����C��
//#define	BSE_POKE_DEAD		(SEQ_SE_DP_POKE_DEAD)
//#define	BSE_POKE_DEAD		(SEQ_SE_DP_POKE_DEAD2)
#define	BSE_POKE_DEAD		(SEQ_SE_DP_POKE_DEAD3)

///<�{�[���J��
#define	BSE_BALL_OPEN			(SEQ_SE_DP_BOWA2)

///<�{�[��������
#define	BSE_BALL_THROW			(SEQ_SE_DP_NAGERU)

///<�{�[��HIT
//#define	BSE_BALL_HIT		(SEQ_SE_DP_KON)
//#define	BSE_BALL_HIT		(SEQ_SE_DP_BOWA2)
#define	BSE_BALL_HIT			(SEQ_SE_DP_KON)
#define	BSE_BALL_HIT_OPEN		(SEQ_SE_DP_BOWA4)		//KON + BOWA2 + SUIKOMU

///<�|�P�����{�[���ɋz������
#define	BSE_BALL_INHALE			(SEQ_SE_DP_SUIKOMU)

///<�|�P�����{�[���ɋz������
#define	BSE_POKEMON_GET			(SEQ_SE_DP_GETTING)

///<�|�P�����{�[�����
#define	BSE_BALL_SHAKE			(SEQ_SE_DP_BOWA)

///<HP��
#define	BSE_PINCH				(SEQ_SE_DP_HINSI)

///<�ɂ���
#define	BSE_ESCAPE				(SEQ_SE_DP_NIGERU2)

///<��
#define	BSE_KAIHUKU				(SEQ_SE_DP_KAIFUKU)

///<���艹
#define	BSE_OKURI				(SEQ_SE_DP_SELECT)

///<�T�t�@���I����
#define	BSE_SAFARI_END			(SEQ_SE_DP_PINPON)

///<�T�t�@���]�[���Ń{�[���ȊO�𓊂���
#define	BSE_SAFARI_THROW		(SEQ_SE_DP_NAGERU)

///<�t�H�����`�F���W�G�t�F�N�g�̃��U�C�N�I��
#define	BSE_MOSAIC_ON			(SEQ_SE_DP_W100)

///<�t�H�����`�F���W�G�t�F�N�g�̃��U�C�N�I�t
#define	BSE_MOSAIC_OFF			(SEQ_SE_DP_W107)

//--------------------------------------------------------------
//	�莝���Q�[�W
//--------------------------------------------------------------
///�莝���Q�[�W�F�莝���Q�[�WIN
#define BSE_TB_START			(SEQ_SE_DP_TB_START)
///�莝���Q�[�W�F���g�������Ă���{�[��
#define BSE_TB_KON				(SEQ_SE_DP_TB_KON)
///�莝���Q�[�W�F���g����̃{�[��
#define BSE_TB_KARA				(SEQ_SE_DP_TB_KARA)



#ifndef __ASM_NO_DEF_

#include "system/snd_tool.h"

#endif __ASM_NO_DEF_

#endif	//__BATTLE_SND_DEF_H__
