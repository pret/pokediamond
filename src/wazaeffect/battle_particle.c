//==============================================================================
/**
 * @file	battle_particle.c
 * @brief	�퓬�p�̃p�[�e�B�N������c�[��
 * @author	matsuda
 * @date	2005.07.15(��)
 */
//==============================================================================
#include "common.h"
#include "system/particle.h"
#include "spl.h"
#include "battle_particle.h"
#include "we_err.h"
#include "we_tool.h"


//==============================================================================
//	�萔��`
//==============================================================================
///�퓬�p�[�e�B�N���̃J�����j�A�ݒ�
#define BP_NEAR			(FX32_ONE)
///�퓬�p�[�e�B�N���̃J�����t�@�[�ݒ�
#define BP_FAR			(FX32_ONE * 900)

//==============================================================================
//	�\���̒�`
//==============================================================================
typedef struct{
	PTC_PTR ptc;
	void *ptc_heap;
	u8 seq;
}BP_SYS;

//==============================================================================
//	�v���g�^�C�v�錾
//==============================================================================
static u32 sAllocTex(u32 size, BOOL is4x4comp);
static u32 sAllocTexPalette(u32 size, BOOL is4pltt);
#ifdef PM_DEBUG
static void BattleParticle_TestMain(TCB_PTR tcb, void *work);
#endif

//==============================================================================
//	�f�[�^
//==============================================================================
const char * const PathLen[] = {
	NULL,
/*
	"wazaeffect/effectdata/test1.spa",
	"wazaeffect/effectdata/test2.spa",
	"wazaeffect/effectdata/test3.spa",
	"wazaeffect/effectdata/test_fire.spa",
*/
};



//--------------------------------------------------------------
/**
 * @brief   �퓬�p�p�[�e�B�N���V�X�e�����쐬����
 *
 * @retval  �p�[�e�B�N���V�X�e�����[�N�ւ̃|�C���^
 *
 * �퓬�̏�������Particle_SystemWorkInit����Ɏ��s����Ă���K�v������܂��B
 */
//--------------------------------------------------------------
PTC_PTR BattleParticle_SystemSet(int heap_id)
{
	PTC_PTR ptc;
	void *heap;
	GF_CAMERA_PTR camera_ptr;
	
	heap = sys_AllocMemory(heap_id, PARTICLE_LIB_HEAP_SIZE);
	ptc = Particle_SystemCreate(sAllocTex, sAllocTexPalette, heap, PARTICLE_LIB_HEAP_SIZE, 
		TRUE, heap_id);
	camera_ptr = Particle_GetCameraPtr(ptc);
	if(camera_ptr != NULL){
		GFC_SetCameraClip(BP_NEAR, BP_FAR, camera_ptr);
	}
	return ptc;
}

PTC_PTR CB_Particle_SystemSet(int heap_id)
{
	PTC_PTR ptc;
	void *heap;
	GF_CAMERA_PTR camera_ptr;
	
	heap = sys_AllocMemory(heap_id, PARTICLE_LIB_HEAP_SIZE_CB);
	ptc = Particle_SystemCreate(sAllocTex, sAllocTexPalette, heap, PARTICLE_LIB_HEAP_SIZE_CB, 
		TRUE, heap_id);
	camera_ptr = Particle_GetCameraPtr(ptc);
	if(camera_ptr != NULL){
		GFC_SetCameraClip(BP_NEAR, BP_FAR, camera_ptr);
	}
	return ptc;
}

//--------------------------------------------------------------
/**
 * @brief   �퓬�p�p�[�e�B�N���V�X�e���I������
 *
 * @param  �p�[�e�B�N���V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void BattleParticle_Exit(PTC_PTR ptc)
{
	void *heap;

	heap = Particle_HeapPtrGet(ptc);
	Particle_SystemExit(ptc);
	sys_FreeMemoryEz(heap);
}

//--------------------------------------------------------------
/**
 * @brief   �퓬�p�p�[�e�B�N���V�X�e���E���C���֐�(�v�Z�E�`�揈���Ȃǂ����s)
 *
 * @param   ptc		�p�[�e�B�N���V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void BattleParticle_Main(void)
{
	int draw_num;
	const MtxFx43 *camera_ptr;
	
	//��check 3D���g���Ȃ疈�t���[���K���Ăяo���K�v�����邩���BSDK�}�j���A���Q��
	//		  ����Ȃ�퓬�̃��C�����[�v�̍ŏ��ɌĂ�ł��炤�K�v������B
	//		  �����|�P�����ƃp�[�e�B�N���ƂŕʁX�̕����o���Ă���̂ł����ł����邩������Ȃ��B
	//G3X_Reset();
	GF_G3X_Reset();


	if(Particle_GetActionNum() == 0){
		return;
	}
	
	//�퓬���\�t�g�E�F�A�X�v���C�g�p�J�����ɂȂ��Ă���̂��ꎞ�I�ɖ߂�
	//G3X_InitMtxStack();
	
	draw_num = Particle_DrawAll();	//�p�[�e�B�N���`��

	if(draw_num > 0){
		//�p�[�e�B�N���̕`�悪�I�������̂ŁA�Ăу\�t�g�E�F�A�X�v���C�g�p�J�����ɐݒ�
	#if 0
		G3X_InitMtxStack();
	#else
		//G3X_Reset();
		GF_G3X_Reset();
	#endif
		NNS_G2dSetupSoftwareSpriteCamera();
	}

	Particle_CalcAll();	//�p�[�e�B�N���v�Z
}

//--------------------------------------------------------------
/**
 * @brief   �e�N�X�`��VRAM�A�h���X��Ԃ����߂̃R�[���o�b�N�֐�
 *
 * @param   size		�e�N�X�`���T�C�Y
 * @param   is4x4comp	4x4���k�e�N�X�`���ł��邩�ǂ����̃t���O(TRUE=���k�e�N�X�`��)
 *
 * @retval  �ǂݍ��݂��J�n����VRAM�̃A�h���X
 */
//--------------------------------------------------------------
static u32 sAllocTex(u32 size, BOOL is4x4comp)
{
#if 1
	NNSGfdTexKey key;
	u32 address;
	
	key = NNS_GfdAllocTexVram(size, is4x4comp, 0);
	Particle_LnkTexKeySet(key);		//�����N�h���X�g���g�p���Ă���̂ŃL�[�����Z�b�g
	
	address = NNS_GfdGetTexKeyAddr(key);
//	OS_Printf("�e�N�X�`��Vram�A�h���X��%#x\n", address);
	
	return address;
	
#elif 1		//�t���[���e�N�X�`���}�l�[�W��
	u32 address;
	NNSGfdTexKey key;
	
	key = NNS_GfdAllocFrmTexVram(size, is4x4comp, 0);
	SDK_ASSERT(key != NNS_GFD_ALLOC_ERROR_TEXKEY);
	
	address = NNS_GfdGetTexKeyAddr(key);
#ifdef OSP_PARTICLE_ON
	OS_Printf("Vram�A�h���X��%#x\n", address);
#endif
	return address;
#else		//�����N�h���X�g�e�N�X�`���}�l�[�W��
	��psys���O���[�o���ϐ��o�R�œn���K�v������B
	(�R�[���o�b�N�֐��̓��C�u�����Ō^�����߂��Ă���̂ŁA����������ȏ㑝�₷�����o���Ȃ�)
	
	u32 address;
	NNSGfdTexKey key;
	
	key = NNS_GfdAllocLnkTexVram(size, is4x4comp, 0);
	SDK_ASSERT(key != NNS_GFD_ALLOC_ERROR_TEXKEY);
	
	address = NNS_GfdGetTexKeyAddr(key);
	OS_Printf("Vram�A�h���X��%#x\n", address);
	
	for(i = 0; i < LNK_TEX_KEY_MAX; i++){
		if(psys->tex_key == 0){
			psys->tex_key = key;
		}
	}
	return address;
#endif
}

//--------------------------------------------------------------
/**
 * @brief	�e�N�X�`���p���b�gVRAM�A�h���X��Ԃ����߂̃R�[���o�b�N�֐�
 *
 * @param	size		�e�N�X�`���T�C�Y
 * @param	is4pltt		4�F�p���b�g�ł��邩�ǂ����̃t���O
 *
 * @retval	�ǂݍ��݂��J�n����VRAM�̃A�h���X
 *
 * direct�`���̃e�N�X�`���̏ꍇ�ASPL_LoadTexPlttByCallbackFunction��
 * �R�[���o�b�N�֐����Ăяo���܂���B
 */
//--------------------------------------------------------------
static u32 sAllocTexPalette(u32 size, BOOL is4pltt)
{
#if 1
	NNSGfdPlttKey key;
	u32 address;
	
	key = NNS_GfdAllocPlttVram(size, is4pltt, 0);
	Particle_PlttLnkTexKeySet(key);	//�����N�h���X�g���g�p���Ă���̂ŃL�[�����Z�b�g
	
	address = NNS_GfdGetPlttKeyAddr(key);
//	OS_Printf("�p���b�gVram�A�h���X��%#x\n", address);
	return address;
	
#elif 0
	return 0x20*4;
#else
	NNSGfdPlttKey key;
	u32 address;
	
	key = NNS_GfdAllocFrmPlttVram(size, is4pltt, NNS_GFD_ALLOC_FROM_LOW);
	if(key == NNS_GFD_ALLOC_ERROR_PLTTKEY){
		GF_ASSERT(0 && "�p�[�e�B�N���Ńp���b�g�̊m�ۂ��o���܂���I\n");
	}
	address = NNS_GfdGetPlttKeyAddr(key);
#ifdef OSP_PARTICLE_ON
	OS_Printf("�p���b�gVram�A�h���X��%#x\n", address);
#endif
	return address;
#endif
}






//==============================================================================
//
//	�e�X�g�p�֐�
//
//==============================================================================

#ifdef PM_DEBUG	//++++++++++++++++++++++++++++++++++++++++++++++++++++
void BattleParticle_TestInit(void)
{
	BP_SYS *bp;
	
	// �}�l�[�W�����e�N�X�`���C���[�W�X���b�g���w��X���b�g���Ǘ��ł���悤�ɂ���
	// �f�t�H���g�}�l�[�W���ɂ���B
	NNS_GfdInitFrmTexVramManager(2, TRUE);
		
	// �}�l�[�W�����p���b�g��32KB���Ǘ��ł���悤�ɂ���
	// �f�t�H���g�}�l�[�W���ɂ���B
	NNS_GfdInitFrmPlttVramManager(0x8000, TRUE);

	//�|�P�����Ŏg�p���镪���m��
	NNS_GfdAllocFrmTexVram(0x1000*4, 0, 0);
	NNS_GfdAllocFrmPlttVram(0x20 * 4, 0, NNS_GFD_ALLOC_FROM_LOW);

	//�p�[�e�B�N���V�X�e�����[�N������
	Particle_SystemWorkInit();


	bp = sys_AllocMemory(HEAPID_BATTLE, sizeof(BP_SYS));
	memset(bp, 0, sizeof(BP_SYS));
	
//	bp->ptc = BattleParticle_SystemSet();

//	err_y = -0x0800;//-0.520508;
//	err_z = 0x2100;//2.156250;
	
	TCB_Add(BattleParticle_TestMain, bp, 20);
}

static const VecFx32 EnemyEye = {
	0x1700, 0x4d00, -0x1000
};
static const VecFx32 EnemyUp = {
	0, -FX32_ONE, 0
};

static void TestEmitCallback(EMIT_PTR emit)
{
//	VecFx32 vex;
	VecFx32 eye;
	BP_SYS *bp;
	VecFx32 vel;
	
	bp = Particle_GetTempPtr();
	
//	WET_PokeParticlePosGet(we_sys, 0, &vex);
//	Particle_SetEye(bp->ptc, &EnemyEye);
//	Particle_SetVup(bp->ptc, &EnemyUp);
	
//	SPL_SetEmitterPositionX(emit, vex.x);
//	SPL_SetEmitterPositionY(emit, vex.y);
//	SPL_SetEmitterPositionZ(emit, vex.z + 0x100);
	
	
	Particle_GetEye(bp->ptc, &eye);
//	eye.x *= -1;
//	eye.y *= -1;
//	eye.z *= -1;
	Particle_SetEye(bp->ptc, &eye);

	SplSub_GetEmitterVelocity(emit, &vel);
	vel.x *= -1;
	vel.y *= -1;
	vel.z *= -1;
	SplSub_SetEmitterVelocity(emit, &vel);
	
//	SPL_SetEmitterPositionZ(emit, err_z);
//	SPL_SetEmitterRadius(emit, err_z); 
//	SPL_SetEmitterBaseScale(emit, err_base_scl);
}

static void BattleParticle_TestMain(TCB_PTR tcb, void *work)
{
	BP_SYS *bp = work;
	const VecFx32 init_pos = {0,0,0};
	
	if(WeDebugWork.debug_flag & WE_DEBUG_BIT_EMITPOS){
		if(sys.cont & PAD_KEY_UP){
			WeDebugWork.emit_pos.y += 0x40;
		}
		else if(sys.cont & PAD_KEY_DOWN){
			WeDebugWork.emit_pos.y -= 0x40;
		}
		if(sys.cont & PAD_KEY_LEFT){
			WeDebugWork.emit_pos.x += 0x40;
		}
		else if(sys.cont & PAD_KEY_RIGHT){
			WeDebugWork.emit_pos.x -= 0x40;
		}
		if(sys.cont & PAD_BUTTON_A){
			WeDebugWork.emit_pos.z += 0x40;
		}
		else if(sys.cont & PAD_BUTTON_B){
			WeDebugWork.emit_pos.z -= 0x40;
		}
	}
	
	switch(bp->seq){
	case 0:
		bp->ptc = BattleParticle_SystemSet(HEAPID_BATTLE);
	//	resource = Particle_ResourceLoad(bp->ptc, PathLen[3]);
	//	Particle_LoadFile(bp->ptc, resource, PTC_AUTOTEX_FRM | PTC_AUTOPLTT_FRM);
		//Particle_CreateEmitter(bp->ptc, 0, &init_pos);
		Particle_CreateEmitterCallback(bp->ptc, 0, TestEmitCallback, bp);
		
		bp->seq++;
		break;
	case 1:
		//BattleParticle_Main();
		
		if(WeDebugWork.debug_flag & WE_DEBUG_BIT_EMITPOS){
			WeDebugWork.wait++;
			if(WeDebugWork.wait > 10){
				WeDebugWork.wait = 0;
				Particle_EmitterDeleteAll(bp->ptc);
			}
		}
		
		//�G�~�b�^���S�Ė����Ȃ�����I��
		if(Particle_GetEmitterNum(bp->ptc) == 0){
			bp->seq = 0;
			BattleParticle_Exit(bp->ptc);
			//Particle_ResourceFinish(bp->ptc);
//			sys_FreeMemoryEz(bp);
//			TCB_Delete(tcb);
			return;
		}
		break;
	}
}

#endif	//PM_DEBUG ++++++++++++++++++++++++++++++++++++++++++++


