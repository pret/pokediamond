//==============================================================================
/**
 * @file	wp_tbl.c
 * @brief	�Z�G�t�F�N�g�p�[�e�B�N���f�[�^�e�[�u��
 * @author	matsuda
 * @date	2005.07.22(��)
 */
//==============================================================================
#include "common.h"
#include "system/particle.h"
#include "wazaeffect/wp_tbl.h"
#include "wazaeffect/wp_num.h"
#include "wazaeffect/battle_particle.h"
#include "wazaeffect/wp_callback.h"
#include "wazaeffect/effectdata/we_list.h"
#include "system/arc_tool.h"

#include "wpcb_common.h"

//==============================================================================
//	�v���g�^�C�v�錾
//==============================================================================
static void DummyEmitCallback(EMIT_PTR emit);

//==============================================================================
//	�萔��`
//==============================================================================
#define DUMMY_CALLBACK		DummyEmitCallback

//==============================================================================
//	�Z�G�t�F�N�g�p�[�e�B�N���f�[�^�e�[�u��
//==============================================================================
#if 0	//Arc����悤�ɂȂ����̂ŕs�v 2005.10.05(��)
#include "wazaeffect/effectdata/we_list.dat"
#endif


//--------------------------------------------------------------
/**
 * @brief   �G�~�b�^�쐬���ɌĂяo���R�[���o�b�N�֐��ւ̃|�C���^�z��
 *
 * ���������邽�тɁAwp_num.h�̒�`�����킹�đ���������K�v������܂��B(EMTFUNC_???)
 */
//--------------------------------------------------------------
static const pEmitFunc EmitterCallbackFunc[] = {
	DummyEmitCallback,
	EmitCall_CameraReverseAttack,
	EmitCall_CameraReverseDefence,
	EmitCall_AttackPos,
	EmitCall_DefencePos,
	EmitCall_AxisAttack,
	EmitCall_AxisDefence,
	
	EmitCall_AxisAttack_DefaultCNV,
	EmitCall_AxisAttack_CenterCNV,
	EmitCall_AxisAttack_TargetPokemonCNV,
	EmitCall_AxisAttack_PlayerPokemonCNV,
	EmitCall_AxisAttack_PosSetCNV,
	
	EmitCall_AxisAttack_DefaultMAG,
	EmitCall_AxisAttack_CenterMAG,
	EmitCall_AxisAttack_TargetPokemonMAG,
	EmitCall_AxisAttack_PlayerPokemonMAG,
	EmitCall_AxisAttack_PosSetMAG,
	
	ECB_Operator,
	EmitCall_SepPos,
	
	EmitCall_DFsidePos,
	EmitCall_ATsidePos,
	
	EmitCall_ATPosCR,
	
	EmitCall_Debug,
};


#if 0		//======================================
static const WP_DATA WazaParticleDataTbl[] = {
	{
		"wazaeffect/effectdata/test1.spa",
		DUMMY_CALLBACK,
		0,
	},
	{
		"wazaeffect/effectdata/test2.spa",
		DUMMY_CALLBACK,
		0,
	},
	{
		"wazaeffect/effectdata/test3.spa",
		DUMMY_CALLBACK,
		0,
	},
};
#endif




//--------------------------------------------------------------
/**
 * @brief   �G�~�b�^�������ɌĂяo���R�[���o�b�N�֐����K�v�Ȃ����Ɏw�肷��_�~�[�֐�
 *
 * @param   emit		���������G�~�b�^�ւ̃|�C���^
 *
 * NULL�w��ł����v���������ǁA���Ƀ}�j���A���ɋL�ڂ���Ă����ł��Ȃ��̂ŁA
 * ���S���l�����ă_�~�[�֐���ݒ肷��悤�ɂ��܂��B
 */
//--------------------------------------------------------------
static void DummyEmitCallback(EMIT_PTR emit)
{
	return;
}


#if 0	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//--------------------------------------------------------------
/**
 * @brief   �Z�G�t�F�N�g�p�[�e�B�N���f�[�^�e�[�u������A�w��f�[�^�ԍ��̃A�h���X���擾����
 *
 * @param   data_no		�f�[�^�ԍ�(wp_num.h:WP_???)
 *
 * @retval  �f�[�^�A�h���X
 */
//--------------------------------------------------------------
const WP_DATA * Wp_DataPtrGet(int data_no)
{
	if(data_no >= NELEMS(WazaParticleDataTbl)){
		SDK_ASSERT(0);
		return &WazaParticleDataTbl[0];	//������΂Ȃ��悤�ɍŏ��̃|�C���^���ꉞ�Ԃ�
	}
	
	return &WazaParticleDataTbl[data_no];
}

//--------------------------------------------------------------
/**
 * @brief   �p�[�e�B�N���𐶐�����
 *
 * @param   data_no		�f�[�^�ԍ�(wp_num.h:WP_???)
 */
//--------------------------------------------------------------
void Wp_ParticleSet(PTC_PTR ptc, int data_no)
{
	const WP_DATA *wpdata;
	
	wpdata = Wp_DataPtrGet(data_no);
	
	Particle_LoadFile(ptc, wpdata->spa_path);
	Particle_CreateEmitterCallback(ptc, wpdata->res_no, wpdata->emit_func);
}
#endif


//--------------------------------------------------------------
/**
 * @brief   �p�[�e�B�N���V�X�e���𐶐����A���\�[�X�t�@�C����ǂݍ���
 *
 * @param   data_no		�f�[�^�ԍ�(wp_num.h:SPA_???)
 * @param   tex_at_once		TRUE:�e�N�X�`�����]���AFALSE:V�u�����N���ɓ]��
 */
//--------------------------------------------------------------
PTC_PTR Wp_Init(int heap_id, int data_no, int tex_at_once)
{
	PTC_PTR ptc;
	void *resource;
	
	ptc = BattleParticle_SystemSet(heap_id);
	resource = Particle_ArcResourceLoad(ARC_WAZA_PARTICLE, data_no, heap_id);
	Particle_ResourceSet(ptc, resource, PTC_AUTOTEX_LNK | PTC_AUTOPLTT_LNK, tex_at_once);

#ifdef PM_DEBUG

	gDebugPTC = ptc;

#endif
	
	return ptc;
}

//--------------------------------------------------------------
/**
 * @brief	
 *
 * @param	heap_id	
 * @param	arc_id	
 * @param	data_no	
 * @param   tex_at_once		TRUE:�e�N�X�`�����]���AFALSE:V�u�����N���ɓ]��
 *
 * @retval	PTC_PTR	
 *
 */
//--------------------------------------------------------------
PTC_PTR Wp_InitEx(int heap_id, int arc_id, int data_no, int tex_at_once)
{
	PTC_PTR ptc;
	void *resource;
	
	ptc = BattleParticle_SystemSet(heap_id);
	resource = Particle_ArcResourceLoad(arc_id, data_no, heap_id);
	Particle_ResourceSet(ptc, resource, PTC_AUTOTEX_LNK | PTC_AUTOPLTT_LNK, tex_at_once);

#ifdef PM_DEBUG

	gDebugPTC = ptc;

#endif
	
	return ptc;
}

///< �J�X�^����p
PTC_PTR Wp_InitEx_CB(int heap_id, int arc_id, int data_no, int tex_at_once)
{
	PTC_PTR ptc;
	void *resource;
	
	ptc = CB_Particle_SystemSet(heap_id);
	resource = Particle_ArcResourceLoad(arc_id, data_no, heap_id);
	Particle_ResourceSet(ptc, resource, PTC_AUTOTEX_LNK | PTC_AUTOPLTT_LNK, tex_at_once);
	
	return ptc;
}


void * Particle_ArcResourceLoad_AH(ARCHANDLE* ah, int index, int heap_id)
{
	return ArchiveDataLoadAllocByHandle(ah,index, heap_id );
}

///< �A�[�J�C�u�̃n���h���ێ�
PTC_PTR Wp_InitEx_CBAH(ARCHANDLE* ah, int heap_id, int data_no, int tex_at_once)
{
	PTC_PTR ptc;
	void *resource;
	
	ptc = CB_Particle_SystemSet(heap_id);
	resource = Particle_ArcResourceLoad_AH(ah, data_no, heap_id);
	Particle_ResourceSet(ptc, resource, PTC_AUTOTEX_LNK | PTC_AUTOPLTT_LNK, tex_at_once);

	return ptc;
}

//--------------------------------------------------------------
/**
 * @brief   �p�[�e�B�N���̃G�~�b�^���쐬����
 *
 * @param   ptc				�p�[�e�B�N���V�X�e�����[�N�ւ̃|�C���^
 * @param   resource_no		���\�[�X�ԍ�
 * @param   func_num		�R�[���o�b�N�֐��ԍ�(wp_num.h:EMTFUNC_???)
 * @param   temp_ptr		�G�~�b�^�쐬���Ƀe���|�������[�N�ɗa����|�C���^
 */
//--------------------------------------------------------------
EMIT_PTR Wp_EmitterCreate(PTC_PTR ptc, int resource_no, int func_num, void *temp_ptr)
{
	return Particle_CreateEmitterCallback(ptc, resource_no, EmitterCallbackFunc[func_num], temp_ptr);
}

//--------------------------------------------------------------
/**
 * @brief   �p�[�e�B�N���̃G�~�b�^���쐬����(�R�[���o�b�N�֐��𒼐ڃ|�C���^�œn��)
 *
 * @param   ptc				�p�[�e�B�N���V�X�e�����[�N�ւ̃|�C���^
 * @param   resource_no		���\�[�X�ԍ�
 * @param   func_num		�R�[���o�b�N�֐��ԍ�(wp_num.h:EMTFUNC_???)
 * @param   temp_ptr		�G�~�b�^�쐬���Ƀe���|�������[�N�ɗa����|�C���^
 */
//--------------------------------------------------------------
EMIT_PTR Wp_EmitterCreateFunc(PTC_PTR ptc, int resource_no, pEmitFunc func, void *temp_ptr)
{
	return Particle_CreateEmitterCallback(ptc, resource_no, func, temp_ptr);
}

//--------------------------------------------------------------
/**
 * @brief   �ǂݍ���ł��郊�\�[�X�t�@�C�����������
 *
 * @param   ptc		�p�[�e�B�N���V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void Wp_Exit(PTC_PTR ptc)
{
	BattleParticle_Exit(ptc);
}

