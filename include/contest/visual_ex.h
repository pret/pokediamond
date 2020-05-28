//==============================================================================
/**
 * @file	visual_ex.h
 * @brief	�_���X����F�O�����J�w�b�_
 * @author	matsuda
 * @date	2006.03.09(��)
 *
 * �_���X����ŊO���Ɍ��J����K�v�̂����`���������ɏ����Ă��܂�
 */
//==============================================================================
#ifndef __VISUAL_EX_H__
#define __VISUAL_EX_H__


//==============================================================================
//	�萔��`
//==============================================================================
//--------------------------------------------------------------
//	���W
//--------------------------------------------------------------
///�|�P�����o����WX
#define VISUAL_APPEAR_X			(128)
///�|�P�����o����WY
#define VISUAL_APPEAR_Y			(24)

///�|�P�����������WX
#define VISUAL_ARRIVAL_X		(VISUAL_APPEAR_X)
///�|�P�����������WY
#define VISUAL_ARRIVAL_Y		(96 - 32)

///�|�P������ʒuZ
#define VISUAL_POKEPOS_Z		(APPEAR_Z_TYPE_AA)


///�g���[�i�[�������WX
#define VISUAL_TRAINER_APPEAR_X		(320)
///�g���[�i�[�������WX
#define VISUAL_TRAINER_APPEAR_Y		(32)
///�g���[�i�[�������WX
#define VISUAL_TRAINER_APPEAR_Z		(VISUAL_POKEPOS_Z - 0x40)

///�g���[�i�[�������WX
#define VISUAL_TRAINER_ARRIVAL_X		(230)
///�g���[�i�[�������WX
#define VISUAL_TRAINER_ARRIVAL_Y		(VISUAL_TRAINER_APPEAR_Y)
///�g���[�i�[�������WX
#define VISUAL_TRAINER_ARRIVAL_Z		(VISUAL_POKEPOS_Z - 0x40)



#endif	//__VISUAL_EX_H__

