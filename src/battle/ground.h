//==============================================================================
/**
 * @file	ground.h
 * @brief	�퓬��ʁF�n��(�|�P��������ɏ�邨�~)�̃w�b�_
 * @author	matsuda
 * @date	2005.10.06(��)
 */
//==============================================================================
#ifndef __GROUND_H__
#define __GROUND_H__


//==============================================================================
//	�萔��`
//==============================================================================
///���@���n�ʂ�X���W
#define GROUND_MINE_X		(64)
///���@���n�ʂ�Y���W
#define GROUND_MINE_Y		(128 + 8)
///�G���n�ʂ�X���W
#define GROUND_ENEMY_X		(24*8)
///�G���n�ʂ�Y���W
#define GROUND_ENEMY_Y		(8*11)


///�n��(�|�P��������邨�~)�̃O���t�B�b�N�^�C�v
enum{
	GROUND_TYPE_NORMAL_MINE,		///<�m�[�}���n�`������
	GROUND_TYPE_NORMAL_ENEMY,	///<�m�[�}���n�`�G��
};


//==============================================================================
//	�\���̒�`
//==============================================================================
///�n��(�|�P��������邨�~)���[�N
typedef struct{
	CATS_ACT_PTR cap;		///<�w�b�_�[�t���A�N�^�[�|�C���^
	BATTLE_WORK	*bw;		///<�퓬�V�X�e�����[�N�\����
	u8 mine_enemy;			///<GROUND_TYPE_NORMAL_???
	u8 ground_id;			///<GROUND_ID_???
	s16 x;
	s16 y;
}GROUND_WORK;


//==============================================================================
//	�O���֐��錾
//==============================================================================
extern void Ground_ResourceLoad(GROUND_WORK *ground);
extern void Ground_ActorSet(GROUND_WORK *ground);
extern void Ground_ActorDel(GROUND_WORK *ground);
extern void Ground_ResourceFree(GROUND_WORK *ground);
extern void Ground_ActorResourceSet(GROUND_WORK *ground, BATTLE_WORK *bw, 
	u16 mine_enemy, int ground_id);
extern void Ground_ActorResourceDel(GROUND_WORK *ground);
extern void Ground_EnableSet(GROUND_WORK *ground, int enable);



#endif	//__GROUND_H__

