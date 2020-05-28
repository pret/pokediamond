//==============================================================================
/**
 * @file	ec_eff.h
 * @brief	�ȒP�Ȑ���������
 * @author	goto
 * @date	2006.01.17(��)
 *
 * �����ɐF�X�ȉ�����������Ă��悢
 *
 */
//==============================================================================

#ifndef	__EC_EFF_H__
#define	__EC_EFF_H__

#include "effectdata/waza_particle_def.h"

// -----------------------------------------
//
//	�G���J�E���g�G�t�F�N�g �Ǘ��\����
//
// -----------------------------------------
typedef struct _TEC_EFF_SYS * ECE_PTR;

typedef struct _TEC_EFF_MANAGER * ECEM_PTR;


// -----------------------------------------
//
//	�O���w������p �\����( ��Α����邩�� )
//
// -----------------------------------------
/// �}�l�[�W���[�������p
typedef struct {
	
	int dmy;
	
} TECM_ADD_PARAM;

/// �G���J�E���g�G�t�F�N�g�������p
typedef struct {

	int	eff_no;			///< �G�t�F�N�g�ԍ� EECE_EFF_NO �Q��
	int	camera_type;	///< �J�����̃^�C�v GF_CAMERA	�Q��
	
} TEC_ADD_PARAM;


/*
	camera_type
	GF_CAMERA_PERSPECTIV	// �����ˉe
	GF_CAMERA_ORTHO			// ���ˉe
*/


// -----------------------------------------
//
//	�G�t�F�N�g�̔ԍ���`
//
// -----------------------------------------
#define ECE_DEF_SPA_START	(P_EC_001_1_SPA)

enum EECE_EFF_NO {
	
	ECE_SPA_GRASS_001			= P_EC_001_1_SPA,			///< �Ő�
	ECE_SPA_GRASS_002,
	ECE_SPA_WATER_001			= P_EC_002_1_SPA,			///< ����
	ECE_SPA_WATER_002,
	ECE_SPA_GRAVEL_001			= P_EC_003_1_SPA,			///< ����
	ECE_SPA_GRAVEL_002,
	ECE_SPA_FLOOR_001			= P_EC_004_1_SPA,			///< ��
	ECE_SPA_FLOOR_002,
	ECE_SPA_ROCK_SURFACE_001	= P_EC_005_1_SPA,			///< �┧
	ECE_SPA_ROCK_SURFACE_002,
	ECE_SPA_SNOWFIELD_001		= P_EC_006_1_SPA,			///< �ጴ
	ECE_SPA_SNOWFIELD_002,
	ECE_SPA_CAVE_001			= P_EC_007_1_SPA,			///< ���A
	ECE_SPA_CAVE_002,
	ECE_SPA_POOL_BALL_001		= P_EC_008_1_SPA,			///< �݂����܂�
	ECE_SPA_POOL_BALL_002,
	ECE_SPA_ON_THE_ICE_001		= P_EC_009_1_SPA,			///< �X��
	ECE_SPA_ON_THE_ICE_002,
	ECE_SPA_SANDS_001			= P_EC_010_1_SPA,			///< ���n
	ECE_SPA_SANDS_002,
	ECE_SPA_BOG_001				= P_EC_011_1_SPA,			///< ���n
	ECE_SPA_BOG_002,	
};

// -----------------------------------------
//
//	�O���Q�Ɗ֐�
//
// -----------------------------------------
/// ECE_MANAGER
extern ECEM_PTR ECEM_Init(int heap_area, TECM_ADD_PARAM* ecmap);
extern ECE_PTR	ECEM_Load(ECEM_PTR ecmp, TEC_ADD_PARAM* ecap);
extern void		ECEM_ECE_Free(ECEM_PTR ecmp, ECE_PTR ecp);
extern void		ECEM_Free(ECEM_PTR ecmp);

extern void		ECEM_Skip(ECEM_PTR ecmp);

/// ECE
extern ECE_PTR	ECE_Init(int heap_area, TEC_ADD_PARAM* ecap);	///< ������
extern void		ECE_Call(ECE_PTR ecp);							///< ���s
extern BOOL		ECE_EndCheck(ECE_PTR ecp);						///< �I���`�F�b�N
extern void		ECE_Free(ECE_PTR ecp);							///< �������

/*

	/// �}�l�[�W�����p�̒��ӓ_
	
	ECEM_Init		������
	��	
	ECEM_Load		�G�t�F�N�g���[�h(�g�����̂��g���������[�h)
	��	
	ECE_Call		���s
	��	
	ECE_EndCheck	�I���҂�
	��	
	ECEM_Free		�}�l�[�W�����AECE�����ׂĔj��
	
	��3�ȏ�𓮂����ꍇ�AECEM_ECE_Free�Ŕj�����ċ󂫂����

*/

#endif