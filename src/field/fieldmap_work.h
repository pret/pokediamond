//============================================================================================
/**
 * @file	fieldmap_work.h
 * @date	2006.02.04
 * @author	tamada
 * @brief	�t�B�[���h�}�b�v����̃��[�N��`
 *
 * FIELDMAP_WORK�́A�t�B�[���h�}�b�v�̒��ɂ����������Ԃ̂Ȃ����[�N�ł��B
 * �I�[�o�[���C�Œǂ��o�����v�f�i�t�B�[���h�̂RD�\���A�G�t�F�N�g���̑��j��
 * ���̗̈�ɂԂ炳���邱�ƂɂȂ�܂��B
 *
 */
//============================================================================================
#ifndef	__FIELDMAP_WORK_H__
#define	__FIELDMAP_WORK_H__

#include "field/poketch.h"
#include "place_name.h"
#include "weather_sys_def.h"
#include "field_anime_def.h"
#include "seedsys.h"
#include "fieldmap_func_def.h"
#include "field_hblank.h"
#include "poison_effect.h"

//------------------------------------------------------------------
/**
 * @brief	�t�B�[���h�}�b�v��p���[�N��`
 */
//------------------------------------------------------------------
struct FIELDMAP_WORK {
	BOOL main_mode_flag;
	FLDMAPFUNC_SYS * fmapfunc_sys;
	PNC_PTR place_name_cont;
	WEATHER_MANAGER_PTR weather_data;
	FIELD_ANIME_PTR field_trans_anime;
	POKETCH_WORK * poketch;
	SEEDSYS_WORK * seedsys;
	FIELD_HBLANK_SYS * hblanksys;
	POISON_EFFECT_WORK * poisoneffect;

	void *Work;			//�ėp���[�N�|�C���^�@���݂́A�W�����[�N�Ƃ��Ďg���܂�
};


#endif	/* __FIELDMAP_WORK_H__ */
