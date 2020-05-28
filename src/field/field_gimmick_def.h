//============================================================================================
/**
 * @file	field_gimmick_def.h
 * @brief	�}�b�v�ŗL�̎d�|����ID���`����t�@�C��
 * @author	saito
 * @date	2006.02.09
 *
 */
//============================================================================================
#ifndef __FIELD_GIMMICK_DEF_H__
#define __FIELD_GIMMICK_DEF_H__

typedef enum{
	FLD_GIMMICK_NONE,			//0:�Ȃ�
	FLD_GIMMICK_WATER_GYM,		//1:���W��
	FLD_GIMMICK_GHOST_GYM,		//2:�S�[�X�g�W��
	FLD_GIMMICK_STEEL_GYM,		//3:�|�W��
	FLD_GIMMICK_COMBAT_GYM,		//4:�i���W��
	FLD_GIMMICK_ELEC_GYM,		//5:�d�C�W��
	FLD_GIMMICK_SAFARI_TRAIN,	//6:�T�t�@���d��
	FLD_GIMMICK_FLD_LIFT,		//7:�t�B�[���h���t�g
}FLD_GYMMICK_ID;

#define FLD_GIMMICK_MAX	(8)		//�M�~�b�N�������܂߂���

#endif	//__FIELD_GIMMICK_DEF_H__

