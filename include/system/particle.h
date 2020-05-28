//==============================================================================
/**
 * @file	particle.h
 * @brief	�p�[�e�B�N������w�b�_
 * @author	matsuda
 * @date	2005.07.11(��)
 */
//==============================================================================
#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "spl.h"

#define MATSUDA_TEST

//==============================================================================
//	�萔��`
//==============================================================================
//--------------------------------------------------------------
//	Particle_ResourceSet�֐���vram_free_mode
//--------------------------------------------------------------
///�e�N�X�`����������Ȃ�
#define PTC_AUTOTEX_NULL	(0)
///�t���[���e�N�X�`��VRAM�}�l�[�W�����g���ĉ��
#define PTC_AUTOTEX_FRM		(1 << 0)
///�����N�h���X�g�e�N�X�`��VRAM�}�l�[�W�����g���ĉ��
#define PTC_AUTOTEX_LNK		(1 << 1)

///�p���b�g��������Ȃ�
#define PTC_AUTOPLTT_NULL	(0)
///�t���[���p���b�gVRAM�}�l�[�W�����g���ĉ��
#define PTC_AUTOPLTT_FRM	(1 << 2)
///�����N�h���X�g�p���b�gVRAM�}�l�[�W�����g���ĉ��
#define PTC_AUTOPLTT_LNK	(1 << 3)

//--------------------------------------------------------------
//	�V�X�e����SPL���C�u�����Ƃ���肷��ۂɎg�p����O���[�o�����[�N�̔ԍ�
//--------------------------------------------------------------
enum{
	PARTICLE_GLOBAL_0 = 0,
	PARTICLE_GLOBAL_1,
	PARTICLE_GLOBAL_2,
	//�{�[���J�X�^�}�C�Y���ő�8��spa��ǂݍ��ނ̂ő��₵��
	PARTICLE_GLOBAL_3,
	PARTICLE_GLOBAL_4,
	PARTICLE_GLOBAL_5,
	PARTICLE_GLOBAL_6,
	PARTICLE_GLOBAL_7,

	//�{�[���J�X�^�}�C�Y��2�����ɏo��̂�2�{�K�v����B
	PARTICLE_GLOBAL_8,
	PARTICLE_GLOBAL_9,
	PARTICLE_GLOBAL_10,
	PARTICLE_GLOBAL_11,
	PARTICLE_GLOBAL_12,
	PARTICLE_GLOBAL_13,
	PARTICLE_GLOBAL_14,
	PARTICLE_GLOBAL_15,
	
	PARTICLE_GLOBAL_MAX,
};

//--------------------------------------------------------------
//	�g�p�q�[�v�̈�
//--------------------------------------------------------------
///�p�[�e�B�N���V�X�e���Ŏg�p����q�[�v�̈�
#define PTC_SYS_HEAP		(HEAPID_BATTLE)	//(SYSTEM_W_HEAP_AREA)

//--------------------------------------------------------------
//	
//--------------------------------------------------------------
///�p�[�e�B�N���V�X�e������SPL���C�u�������g�p����q�[�v���[�N�̕W���T�C�Y
//#define PARTICLE_LIB_HEAP_SIZE		(0x4200)	///< EMIT_MAX��3����20�ɑ��₵���̂ŁA0x3800����ύX
#define PARTICLE_LIB_HEAP_SIZE		(0x4800)	///< �J�X�^���{�[���ȊO�@���X0x4200
#define PARTICLE_LIB_HEAP_SIZE_CB	(0x4200)	///< �J�X�^���{�[�� 0x4200�܂ł�����0x41D8�����E


///< �p�[�e�B�N���ŕK�{�Ƃ��Ă郁�����̃T�C�Y
///< (0x419c)

//==============================================================================
//	�^��`
//==============================================================================
///�p�[�e�B�N���V�X�e�����[�N�ւ̃|�C���^
typedef struct _PARTICLE_SYSTEM * PTC_PTR;


#ifdef PM_DEBUG

extern PTC_PTR gDebugPTC;

static inline PTC_PTR DEBUG_PTC_PTR_Get(void)
{
	return gDebugPTC;
}

#endif


///�G�~�b�^�̃|�C���^�^
typedef SPLEmitter * EMIT_PTR;

///�e�N�X�`�����[�h����VRAM�A�h���X��Ԃ����߂̃R�[���o�b�N�֐��̌^
typedef u32 (*pTexCallback)(u32, BOOL);

///�G�~�b�^�������ɌĂ΂��R�[���o�b�N�֐��̌^
typedef void (*pEmitFunc)(EMIT_PTR);

//==============================================================================
//	�O���֐��錾
//==============================================================================
extern PTC_PTR Particle_SystemCreate(pTexCallback tex_func, pTexCallback pltt_func, 
	void *work, int work_size, int personal_camera, int heap_id);
extern void Particle_SystemExit(PTC_PTR psys);
extern void * Particle_ResourceLoad(int heap_id, const char *path);
extern void * Particle_ArcResourceLoad(int file_kind, int index, int heap_id);
extern void Particle_ResourceSet(PTC_PTR psys, void *resource, int vram_free, int tex_at_once);
extern EMIT_PTR Particle_CreateEmitter(PTC_PTR psys, int res_no, const VecFx32 *init_pos);
extern void Particle_Draw(PTC_PTR psys);
extern void Particle_Calc(PTC_PTR psys);
extern s32 Particle_GetEmitterNum(PTC_PTR psys);
extern void Particle_EmitterDeleteAll(PTC_PTR psys);
extern void Particle_EmitterDelete(PTC_PTR psys, EMIT_PTR emit);
extern EMIT_PTR Particle_TempEmitterPtrGet(PTC_PTR psys);
extern EMIT_PTR Particle_CreateEmitterCallback(PTC_PTR psys, int res_no, 
	pEmitFunc callback, void *temp_ptr);
extern void * Particle_HeapPtrGet(PTC_PTR psys);
extern void Particle_SystemWorkInit(void);
extern int Particle_DrawAll(void);
extern int Particle_CalcAll(void);
extern void Particle_SystemExitAll(void);
extern void Particle_GetEye(PTC_PTR psys, VecFx32 *eye);
extern void Particle_SetEye(PTC_PTR psys, const VecFx32 *eye);
extern void Particle_GetVup(PTC_PTR psys, VecFx32 *up);
extern void Particle_SetVup(PTC_PTR psys, const VecFx32 *up);
extern void * Particle_GetTempPtr(void);
extern void Particle_GetDefaultEye(VecFx32 *eye);
extern void Particle_GetDefaultUp(VecFx32 *v_up);
extern void Particle_GetDefaultAt(VecFx32 *at);
extern int Particle_GetActionNum(void);
extern GF_CAMERA_PTR Particle_GetCameraPtr(PTC_PTR ptc);
extern void Particle_CameraTypeSet(PTC_PTR ptc, int camera_type);
extern u8 Particle_CameraTypeGet(PTC_PTR ptc);
extern void Particle_LnkTexKeySet(NNSGfdTexKey tex_key);
extern void Particle_PlttLnkTexKeySet(NNSGfdPlttKey pltt_key);

extern void SplSub_GetEmitterVelocity(EMIT_PTR emit, VecFx32 *vel);
extern void SplSub_SetEmitterVelocity(EMIT_PTR emit, const VecFx32 *vel);
extern void SplSub_GetEmitterAxis(EMIT_PTR emit, VecFx16 *vec);
extern fx32 SplSub_GetEmitterRadius(EMIT_PTR emit);
extern fx16 SplSub_GetEmitterInitVelocityPos(EMIT_PTR emit);
extern fx16 SplSub_GetEmitterInitVelocityAxis(EMIT_PTR emit);
extern fx16 SplSub_GetEmitterBaseScale(EMIT_PTR emit);
extern u16 SplSub_GetEmitterEmissionInterval(EMIT_PTR emit);
extern u16 SplSub_GetEmitterBaseAlpha(EMIT_PTR emit);
extern GXRgb SplSub_GetEmitterGlobalColor(EMIT_PTR emit);
extern void SplSub_SetEmitterGenerationRatio(EMIT_PTR emit, fx32 gen_num);
extern fx32 SplSub_GetEmitterGenerationRatio(EMIT_PTR emit);
extern void SplSub_GetEmitterPosition(EMIT_PTR emit, VecFx32 * p_pos);
extern void SplSub_GetEmitterBasePosition(EMIT_PTR emit, VecFx32 * p_pos);

extern void BattleParticle_TestInit(void);

// -----------------------------------------
//
//	Field param ����֐�
//
// -----------------------------------------
void SplSub_SetSPLField_GravityPos(EMIT_PTR emit, VecFx16 *mag);
void SplSub_GetSPLField_GravityPos(EMIT_PTR emit, VecFx16 *mag);
void SplSub_SetSPLField_RandomMag(EMIT_PTR emit, VecFx16* mag);
void SplSub_GetSPLField_RandomMag(EMIT_PTR emit, VecFx16* mag);
void SplSub_SetSPLField_RandomIntvl(EMIT_PTR emit, u16* mag);
void SplSub_GetSPLField_RandomIntvl(EMIT_PTR emit, u16* mag);
void SplSub_SetSPLField_MagnetPos(EMIT_PTR emit, VecFx32* p_pos);
void SplSub_GetSPLField_MagnetPos(EMIT_PTR emit, VecFx32* p_pos);
void SplSub_SetSPLField_MagnetMag(EMIT_PTR emit, fx16* mag);
void SplSub_GetSPLField_MagnetMag(EMIT_PTR emit, fx16* mag);
void SplSub_SetSPLField_SpinRad(EMIT_PTR emit, u16* rad);
void SplSub_GetSPLField_SpinRad(EMIT_PTR emit, u16* rad);
void SplSub_SetSPLField_SpinAxisType(EMIT_PTR emit, u16* axis_type);
void SplSub_GetSPLField_SpinAxisType(EMIT_PTR emit, u16* axis_type);
void SplSub_SetSPLField_SimpleCollisionYPos(EMIT_PTR emit, fx32* y);
void SplSub_GetSPLField_SimpleCollisionYPos(EMIT_PTR emit, fx32* y);
void SplSub_SetSPLField_SimpleCollisionCoeffBounce(EMIT_PTR emit, fx16* coeff_bounce);
void SplSub_GetSPLField_SimpleCollisionCoeffBounce(EMIT_PTR emit, fx16* coeff_bounce);
void SplSub_SetSPLField_SimpleCollisionEventType(EMIT_PTR emit, u16* ev_type);
void SplSub_GetSPLField_SimpleCollisionEventType(EMIT_PTR emit, u16* ev_type);
void SplSub_SetSPLField_SimpleCollisionGlobal(EMIT_PTR emit, u16* global);
void SplSub_GetSPLField_SimpleCollisionGlobal(EMIT_PTR emit, u16* global);
void SplSub_SetSPLField_ConvergencePos(EMIT_PTR emit, VecFx32* p_pos);
void SplSub_GetSPLField_ConvergencePos(EMIT_PTR emit, VecFx32* p_pos);
void SplSub_SetSPLField_ConvergenceRatio(EMIT_PTR emit, fx16* ratio);
void SplSub_GetSPLField_ConvergenceRatio(EMIT_PTR emit, fx16* ratio);

#endif	//__PARTICLE_H__

