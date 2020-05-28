//============================================================================================
/**
 * @file	map_jump_def.h
 * @brief	�}�b�v�W�����v�^�C�v��`
 * @date	2006.02.08
 * @author	Nozomu Saito
 */
//============================================================================================
#ifndef __MAP_JUMP_DEF_H__
#define __MAP_JUMP_DEF_H__

#define MAP_JUMP_TYPE_MAX	(7)

typedef enum{
	M_JUMP_MATOUT,		//0:�������O
	M_JUMP_DOOR,	//1:�h�A�i�O�j������
	M_JUMP_ESCA,	//2:�G�X�J���[�^�[
	M_JUMP_STAIRS,	//3:�K�i
	M_JUMP_DUNIN,	//4:�_���W�����O�������
	M_JUMP_DUNOUT,	//5:�_���W�����O�ɏo��
	M_JUMP_MATIN,	//6:�O�}�b�g������
}MAP_JUMP_TYPE;

#endif //__MAP_JUMP_DEF_H__
