//==============================================================================
/**
 * @file	d_particle.c
 * @brief	�p�[�e�B�N���̃f�o�b�O�p����Ȃ�
 * @author	matsuda
 * @date	2005.08.30(��)
 */
//==============================================================================
#include "common.h"

#ifdef PM_DEBUG		//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include "system/particle.h"
#include "spl.h"
#include "battle_particle.h"
#include "we_err.h"
#include "we_tool.h"
#include "wazaeffect/we_mana.h"
#include "wp_tbl.h"
#include "we_sys.h"
#include <nitro.h>
#include <nnsys.h>

#include "common.h"
#include "camera.h"

#define ANGLE_MOVE	(32)
static void DebugParticle_AxisLoopEmitCallBack(EMIT_PTR emit);
static void DebugParticle_CameraLoopEmitCallBack(EMIT_PTR emit);
static void DebugParticle_MoveLoopEmitCallBack(EMIT_PTR emit);
void DebugLoopEmitter_TCB(TCB_PTR tcb, void* work);

static BOOL CameraInput(GF_CAMERA_PTR camera_ptr)
{
	u8 view;
	fx32 dist;
	u16 persp_way;
	
	BOOL res = FALSE;
	CAMERA_ANGLE angle = {0,0,0,0};
	VecFx32 move = {0,0,0};

	if (/*sys.cont & PAD_BUTTON_L*/1){
		if (sys.cont & PAD_BUTTON_B){			//�J������]�i���]�j
			if (sys.cont & PAD_KEY_UP){
				angle.x = ANGLE_MOVE;
				GFC_AddCameraAngleRev(&angle,camera_ptr);
			}else if (sys.cont & PAD_KEY_DOWN){
				angle.x = -ANGLE_MOVE;
				GFC_AddCameraAngleRev(&angle,camera_ptr);
			}else if (sys.cont & PAD_KEY_LEFT){
				angle.y = -ANGLE_MOVE;
				GFC_AddCameraAngleRev(&angle,camera_ptr);
			}else if (sys.cont & PAD_KEY_RIGHT){
				angle.y = ANGLE_MOVE;
				GFC_AddCameraAngleRev(&angle,camera_ptr);
			}
		}
		else if (sys.cont & PAD_BUTTON_Y){		//�J������]�i���]�j
			if (sys.cont & PAD_KEY_UP){
				angle.x = ANGLE_MOVE;
				GFC_AddCameraAngleRot(&angle,camera_ptr);
			}else if (sys.cont & PAD_KEY_DOWN){
				angle.x = -ANGLE_MOVE;
				GFC_AddCameraAngleRot(&angle,camera_ptr);
			}else if (sys.cont & PAD_KEY_LEFT){
				angle.y = ANGLE_MOVE;
				GFC_AddCameraAngleRot(&angle,camera_ptr);
			}else if (sys.cont & PAD_KEY_RIGHT){
				angle.y = -ANGLE_MOVE;
				GFC_AddCameraAngleRot(&angle,camera_ptr);
			}
		}
		else if (sys.cont & PAD_BUTTON_A){
			if (sys.cont & PAD_KEY_UP){			//�J�����Y�[���A�E�g
				persp_way = GFC_GetCameraPerspWay(camera_ptr);
				if (persp_way+64<0x4000){
					GFC_AddCameraPerspWay(64,camera_ptr);
				}
			}else if (sys.cont & PAD_KEY_DOWN){	//�J�����Y�[���C��
				persp_way = GFC_GetCameraPerspWay(camera_ptr);
				if ((u16)(persp_way-64)<0x4000){
					GFC_AddCameraPerspWay(-64,camera_ptr);
				}
			}else if (sys.cont & PAD_KEY_LEFT){
				GFC_AddCameraPerspWay(64,camera_ptr);
				persp_way = GFC_GetCameraPerspWay(camera_ptr);
				//�J�����̒��S�ɂ���2D�摜���A���ꂸ�ɕ\���ł��鋗�������߂�
				//�Ԃꂸ�ɕ\�����邽�߂ɂ́A1Dot�@���@1Unit�Ōv�Z����΂悢
				//�J��������ʒ��S�����߂�Ƃ��A��ʔ����̃T�C�Y�́A96Dot
				//�\�����������A�J�����̃p�[�X���l���A96Dot�@���@96Unit�ɂȂ鋗���ɂ���΂悢
				dist = FX_Div( FX_Mul( FX_CosIdx( persp_way ), FX_F32_TO_FX32(96) ),	
									 FX_SinIdx( persp_way ));
				GFC_SetCameraDistance(dist,camera_ptr);
			}else if(sys.cont & PAD_KEY_RIGHT){
				GFC_AddCameraPerspWay(-64,camera_ptr);
				persp_way = GFC_GetCameraPerspWay(camera_ptr);
				//�J�����̒��S�ɂ���2D�摜���A���ꂸ�ɕ\���ł��鋗�������߂�
				//�Ԃꂸ�ɕ\�����邽�߂ɂ́A1Dot�@���@1Unit�Ōv�Z����΂悢
				//�J��������ʒ��S�����߂�Ƃ��A��ʔ����̃T�C�Y�́A96Dot
				//�\�����������A�J�����̃p�[�X���l���A96Dot�@���@96Unit�ɂȂ鋗���ɂ���΂悢
				dist = FX_Div( FX_Mul( FX_CosIdx( persp_way ), FX_F32_TO_FX32(96) ),	
									 FX_SinIdx( persp_way ));					
				GFC_SetCameraDistance(dist,camera_ptr);
			}
		}
		else if (sys.cont & PAD_BUTTON_X){
			if (sys.cont & PAD_KEY_UP){
				move.z -= FX32_ONE;
				GFC_ShiftCamera(&move,camera_ptr);
			}else if (sys.cont & PAD_KEY_DOWN){
				move.z += FX32_ONE;
				GFC_ShiftCamera(&move,camera_ptr);
			}else if (sys.cont & PAD_KEY_LEFT){
				move.x -= FX32_ONE;
				GFC_ShiftCamera(&move,camera_ptr);
			}else if (sys.cont & PAD_KEY_RIGHT){
				move.x += FX32_ONE;
				GFC_ShiftCamera(&move,camera_ptr);
			}
		}
		else if (sys.cont & PAD_KEY_UP){	//�J��������������
			GFC_AddCameraDistance(FX32_ONE,camera_ptr);
		}else if (sys.cont & PAD_KEY_DOWN){	//�J�������߂Â���
			GFC_AddCameraDistance(-FX32_ONE,camera_ptr);
		}
		else if (sys.trg & PAD_BUTTON_SELECT){
			//�ˉe�擾
			view = GFC_GetCameraView(camera_ptr);
			view = ((view+1)%2);
			GFC_SetCameraView(view,camera_ptr);
		}
		
		res = TRUE;
	}
	
	{
		CAMERA_ANGLE ang = GFC_GetCameraAngle(camera_ptr);
		OS_Printf("camera x = %d, y = %d, z = %d\n", ang.x,ang.y,ang.z);
	}

	return res;
}






//==============================================================================
//
//	�G�~�b�^���\���L�[�œ�����
//
//==============================================================================
typedef struct{
	int mode;
	int camera;
	VecFx32 vec[5];			///<�G�~�b�^�̍��W
	EMIT_PTR emit;			///<�G�~�b�^�ւ̃|�C���^
	PTC_PTR ptc;			///<�G�~�b�^�������Ă���p�[�e�B�N���V�X�e�����[�N�ւ̃|�C���^
	WE_SYS_PTR	we_sys;
}DEBUG_EMIT_MOVE;

///1��̏\���L�[�̓��͂ŃG�~�b�^�ɑ������ޒl
#define D_EMIT_POS_ADD		(0x0080)

//--------------------------------------------------------------
/**
 * @brief   �G�~�b�^�\���L�[�ړ����C������
 *
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		DEBUG_EMIT_MOVE�\����
 */

static inline void SPL_SetEmitterParticleAge( SPLEmitter* p_emtr, u16 age )
{
    p_emtr->age = age ;
}
//--------------------------------------------------------------
static void DebugParticle_EmitMoveMain(TCB_PTR tcb, void *work)
{
	DEBUG_EMIT_MOVE *dew = work;
	
	if((sys.trg & PAD_BUTTON_START) || Particle_GetEmitterNum(dew->ptc) == 0){
		sys_FreeMemoryEz(dew);
		TCB_Delete(tcb);
		return;
	}
	
	if(sys.cont & PAD_KEY_LEFT){
		dew->vec[dew->mode].x -= D_EMIT_POS_ADD;
	}
	if(sys.cont & PAD_KEY_RIGHT){
		dew->vec[dew->mode].x += D_EMIT_POS_ADD;
	}
	if(sys.cont & PAD_KEY_UP){
		dew->vec[dew->mode].y -= D_EMIT_POS_ADD;
	}
	if(sys.cont & PAD_KEY_DOWN){
		dew->vec[dew->mode].y += D_EMIT_POS_ADD;
	}

	if(sys.cont & PAD_BUTTON_X){
		dew->vec[dew->mode].z -= D_EMIT_POS_ADD;
	}
	if(sys.cont & PAD_BUTTON_B){
		dew->vec[dew->mode].z += D_EMIT_POS_ADD;
	}
	if (sys.trg & PAD_BUTTON_Y){
		dew->mode++;
		dew->mode %= 2;
	}
	if (sys.cont & PAD_BUTTON_A){
		SPL_SetEmitterParticleAge(dew->emit, 0);
	}
	
	switch(dew->mode){
	case 0:
		SPL_SetEmitterPositionX(dew->emit, dew->vec[dew->mode].x);
		SPL_SetEmitterPositionY(dew->emit, dew->vec[dew->mode].y);
		SPL_SetEmitterPositionZ(dew->emit, dew->vec[dew->mode].z);
		OS_Printf(">> pos --");
		break;
	case 1:
		SplSub_SetSPLField_MagnetPos(dew->emit, &dew->vec[dew->mode]);
		OS_Printf(">> mag --");
		break;
	default:
		OS_Printf(">> ne-yo--");
		break;
	}
	OS_Printf("EmitPos x = %d, y = %d, z = %d\n", dew->vec[dew->mode].x, dew->vec[dew->mode].y, dew->vec[dew->mode].z);
}
static void DebugParticle_EmitMoveMain2(TCB_PTR tcb, void *work)
{
	DEBUG_EMIT_MOVE *dew = work;
	
	if ((sys.trg & PAD_BUTTON_SELECT)){
		dew->camera ^= 1;
	}
	Particle_CameraTypeSet(dew->ptc, dew->camera);
	
	if(Particle_GetEmitterNum(dew->ptc) == 0){
		dew->emit = NULL;
		Particle_CreateEmitterCallback(dew->ptc, 0, DebugParticle_MoveLoopEmitCallBack, dew);
	}
	
	if((sys.trg & PAD_BUTTON_START) || Particle_GetEmitterNum(dew->ptc) == 0){
		sys_FreeMemoryEz(dew);
		TCB_Delete(tcb);
		return;
	}
	
	if(sys.cont & PAD_KEY_LEFT){
		dew->vec[dew->mode].x -= D_EMIT_POS_ADD;
	}
	if(sys.cont & PAD_KEY_RIGHT){
		dew->vec[dew->mode].x += D_EMIT_POS_ADD;
	}
	if(sys.cont & PAD_KEY_UP){
		dew->vec[dew->mode].y -= D_EMIT_POS_ADD;
	}
	if(sys.cont & PAD_KEY_DOWN){
		dew->vec[dew->mode].y += D_EMIT_POS_ADD;
	}

	if(sys.cont & PAD_BUTTON_X){
		dew->vec[dew->mode].z -= D_EMIT_POS_ADD;
	}
	if(sys.cont & PAD_BUTTON_B){
		dew->vec[dew->mode].z += D_EMIT_POS_ADD;
	}
	if (sys.trg & PAD_BUTTON_Y){
		dew->mode++;
		dew->mode %= 2;
	}
	if (sys.cont & PAD_BUTTON_A){
		SPL_SetEmitterParticleAge(dew->emit, 0);
	}
	
	switch(dew->mode){
	case 0:
		SPL_SetEmitterPositionX(dew->emit, dew->vec[dew->mode].x);
		SPL_SetEmitterPositionY(dew->emit, dew->vec[dew->mode].y);
		SPL_SetEmitterPositionZ(dew->emit, dew->vec[dew->mode].z);
		OS_Printf(">> pos --");
		break;
	case 1:
		SplSub_SetSPLField_MagnetPos(dew->emit, &dew->vec[dew->mode]);
		OS_Printf(">> mag --");
		break;
	default:
		OS_Printf(">> ne-yo--");
		break;
	}
	OS_Printf("EmitPos x = %d, y = %d, z = %d\n", dew->vec[dew->mode].x, dew->vec[dew->mode].y, dew->vec[dew->mode].z);
}

#if 0

#define HEAP_ID_DEBUG	(HEAPID_BATTLE)

#else

#define HEAP_ID_DEBUG	(HEAPID_WORLD)

#endif

//--------------------------------------------------------------
/**
 * @brief   �G�~�b�^���\���L�[�ňړ�������f�o�b�O���[�h
 *
 * @param   ptc		�p�[�e�B�N���V�X�e���ւ̃|�C���^
 * @param   emit	�G�~�b�^�ւ̃|�C���^
 * @param   vec		���݂̃G�~�b�^�ʒu
 *
 * ��{�I��ADD_PARTICLE��������̃G�~�b�^�������̃R�[���o�b�N�֐����ŌĂ΂�邱�Ƃ�z�肵�Ă��܂�
 */
//--------------------------------------------------------------
void DebugParticle_EmitMove(PTC_PTR ptc, EMIT_PTR emit, const VecFx32 *vec)
{
	DEBUG_EMIT_MOVE *dew;
	
	GF_ASSERT(ptc != NULL && emit != NULL && vec != NULL);
	
	dew = sys_AllocMemory(HEAP_ID_DEBUG, sizeof(DEBUG_EMIT_MOVE));
	dew->mode = 0;
	dew->vec[0] = *vec;
	dew->vec[1] = *vec;
	dew->emit = emit;
	dew->ptc = ptc;
	TCB_Add(DebugParticle_EmitMoveMain, dew, 1000);
}

void DebugParticle_EmitMove2(PTC_PTR ptc, EMIT_PTR emit, WE_SYS_PTR we_sys)
{
	DEBUG_EMIT_MOVE *dew;
	VecFx32 vec = { 0,0,0 };
	
	GF_ASSERT(ptc != NULL && emit != NULL);
	
	dew = sys_AllocMemory(HEAP_ID_DEBUG, sizeof(DEBUG_EMIT_MOVE));
	dew->mode = 0;
	dew->vec[0] = vec;
	dew->vec[1] = vec;
	dew->emit = emit;
	dew->ptc = ptc;
	dew->we_sys = we_sys;
	dew->camera = 0;
	TCB_Add(DebugParticle_EmitMoveMain2, dew, 1000);
}


//==============================================================================
//
//	�p�[�e�B�N���V�X�e���̃J�������ړ�
//
//==============================================================================
#include "field\camera_move_test.h"

typedef struct{
	EMIT_PTR emit;
	WE_SYS_PTR we_sys;
	PTC_PTR ptc;
	GF_CAMERA_PTR camera;
}DEBUG_CAMERA_MOVE;

//--------------------------------------------------------------
/**
 * @brief   �p�[�e�B�N���̃J�������\���L�[�ňړ������郁�C������
 *
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		DEBU_CAMERA_MOVE�\����
 */
//--------------------------------------------------------------
static void DebugParticle_CameraMoveMain(TCB_PTR tcb, void *work)
{
	DEBUG_CAMERA_MOVE *dcm = work;

	if(Particle_GetEmitterNum(dcm->ptc) == 0){
		dcm->emit = NULL;
		//Wp_EmitterCreate(ta->ptc, ta->index, ta->cb_no, ta->we_sys);
		Particle_CreateEmitterCallback(dcm->ptc, 0, DebugParticle_CameraLoopEmitCallBack, dcm);
	}
		
	if((sys.trg & PAD_BUTTON_START) || Particle_GetEmitterNum(dcm->ptc) == 0){
		sys_FreeMemoryEz(dcm);
		TCB_Delete(tcb);
		return;
	}
	CameraInput(dcm->camera);
}

//--------------------------------------------------------------
/**
 * @brief   �p�[�e�B�N���̃J�������\���L�[�ňړ�������
 * @param   ptc		�p�[�e�B�N���V�X�e���ւ̃|�C���^
 */
//--------------------------------------------------------------
void DebugParticle_CameraMove(PTC_PTR ptc)
{
	DEBUG_CAMERA_MOVE *dcm;
	GF_CAMERA_PTR camera_ptr;
	
	camera_ptr = Particle_GetCameraPtr(ptc);
	if(camera_ptr == NULL){
		return;
	}
	
	dcm = sys_AllocMemory(HEAP_ID_DEBUG, sizeof(DEBUG_CAMERA_MOVE));
	dcm->ptc = ptc;
	dcm->camera = camera_ptr;
	TCB_Add(DebugParticle_CameraMoveMain, dcm, 1000);
}
void DebugParticle_CameraMove2(PTC_PTR ptc, EMIT_PTR emit, WE_SYS_PTR we_sys)
{
	DEBUG_CAMERA_MOVE *dcm;
	GF_CAMERA_PTR camera_ptr;
	
	camera_ptr = Particle_GetCameraPtr(ptc);
	if(camera_ptr == NULL){
		OS_Printf("�J�����|�C���^�h��\n");
		return;
	}
	if (we_sys == NULL){
		OS_Printf("we_sys�|�C���^�h��\n");
		return;
	}
	
	dcm = sys_AllocMemory(HEAP_ID_DEBUG, sizeof(DEBUG_CAMERA_MOVE));
	dcm->ptc = ptc;
	dcm->we_sys = we_sys;
	dcm->emit = emit;
	dcm->camera = camera_ptr;
	TCB_Add(DebugParticle_CameraMoveMain, dcm, 1000);
}






//==============================================================================
//
//	�G�~�b�^�̕������L�[����ł�������
//
//==============================================================================
typedef struct{
	PTC_PTR ptc;
	EMIT_PTR emit;
	VecFx16 vel;
	WE_SYS_PTR we_sys;
	int index;
	int cb_no;
}DEBUG_AXIS;

#define ADD_AXIS		(0x0008*4)

//--------------------------------------------------------------
/**
 * @brief   �G�~�b�^�̕������L�[����ł������鏈�����C��
 *
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		DEBUG_AXIS�\����
 */
//--------------------------------------------------------------
static void DebugParticle_AxisMain(TCB_PTR tcb, void *work)
{
	DEBUG_AXIS *ta = work;
	
	if(sys.cont & PAD_KEY_LEFT){
		ta->vel.x -= ADD_AXIS;
	}
	if(sys.cont & PAD_KEY_RIGHT){
		ta->vel.x += ADD_AXIS;
	}
	if(sys.cont & PAD_KEY_UP){
		ta->vel.y -= ADD_AXIS;
	}
	if(sys.cont & PAD_KEY_DOWN){
		ta->vel.y += ADD_AXIS;
	}
	if(sys.cont & PAD_BUTTON_A){
		ta->vel.z += ADD_AXIS;
	}
	if(sys.cont & PAD_BUTTON_B){
		ta->vel.z -= ADD_AXIS;
	}
	SPL_SetEmitterAxis(ta->emit, &ta->vel);
	OS_Printf("DebugAxis x = %d, y = %d, z = %d\n", ta->vel.x, ta->vel.y, ta->vel.z);
}

//--------------------------------------------------------------
/**
 * @brief   �G�~�b�^�̕������L�[����ł�������f�o�b�O�p�^�X�N�𐶐�����
 *
 * @param   ptc			�p�[�e�B�N���V�X�e�����[�N�ւ̃|�C���^
 * @param   emit		�ΏۃG�~�b�^�ւ̃|�C���^
 *
 * ��{�I��ADD_PARTICLE��������̃G�~�b�^�������̃R�[���o�b�N�֐����ŌĂ΂�邱�Ƃ�z�肵�Ă��܂�
 */
//--------------------------------------------------------------
void DebugParticle_Axis(PTC_PTR ptc, EMIT_PTR emit)
{
	DEBUG_AXIS *ta;
	
	ta = sys_AllocMemory(HEAP_ID_DEBUG, sizeof(DEBUG_AXIS));
	memset(ta, 0, sizeof(DEBUG_AXIS));
	ta->ptc = ptc;
	ta->emit = emit;
	TCB_Add(DebugParticle_AxisMain, ta, 1000);
}


//==============================================================================
//	�J��Ԃ������o�[�W����
//==============================================================================
static void DebugParticle_AxisLoopEmitCallBack(EMIT_PTR emit)
{
	DEBUG_AXIS *ta;
	int attack;
	VecFx32 vex;
	WE_SYS_PTR we_sys;
	
	ta = Particle_GetTempPtr();
	we_sys = ta->we_sys;
	attack = WeSysATNoGet(we_sys);

	WET_PokeParticlePosGet(we_sys, attack, &vex);
	SPL_SetEmitterPositionX(emit, vex.x);
	SPL_SetEmitterPositionY(emit, vex.y);
	SPL_SetEmitterPositionZ(emit, vex.z);
	
	ta->emit = emit;
}
static void DebugParticle_CameraLoopEmitCallBack(EMIT_PTR emit)
{
	DEBUG_CAMERA_MOVE *ta;
	int attack;
	VecFx32 vex;
	WE_SYS_PTR we_sys = NULL;
	
	ta = Particle_GetTempPtr();
	we_sys = ta->we_sys;
	
	if (we_sys == NULL){
		OS_Printf("���������m�ۂ���Ă��Ȃ����J����\n");
		return;
	}
	/*
	attack = 0;//WeSysATNoGet(we_sys);

	WET_PokeParticlePosGet(we_sys, attack, &vex);
	SPL_SetEmitterPositionX(emit, vex.x);
	SPL_SetEmitterPositionY(emit, vex.y);
	SPL_SetEmitterPositionZ(emit, vex.z);
	*/
	
	SPL_SetEmitterPositionX(emit, -9472);
	SPL_SetEmitterPositionY(emit, -4480);
	SPL_SetEmitterPositionZ(emit, 0);	
	
	ta->emit = emit;
}
static void DebugParticle_MoveLoopEmitCallBack(EMIT_PTR emit)
{
	DEBUG_EMIT_MOVE *ta;
	int attack;
	VecFx32 vex;
	WE_SYS_PTR we_sys = NULL;
	
	ta = Particle_GetTempPtr();
	we_sys = ta->we_sys;
	
	if (we_sys == NULL){
		OS_Printf("���������m�ۂ���Ă��Ȃ����J����\n");
		return;
	}
	/*
	attack = 0;//WeSysATNoGet(we_sys);

	WET_PokeParticlePosGet(we_sys, attack, &vex);
	SPL_SetEmitterPositionX(emit, vex.x);
	SPL_SetEmitterPositionY(emit, vex.y);
	SPL_SetEmitterPositionZ(emit, vex.z);
	*/
	
	SPL_SetEmitterPositionX(emit, ta->vec[ta->mode].x);
	SPL_SetEmitterPositionY(emit, ta->vec[ta->mode].y);
	SPL_SetEmitterPositionZ(emit, ta->vec[ta->mode].z);	
	
	ta->emit = emit;
}
//--------------------------------------------------------------
/**
 * @brief   �G�~�b�^�̕������L�[����ł������鏈�����C��
 *
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		DEBUG_AXIS�\����
 */
//--------------------------------------------------------------
static void DebugParticle_AxisLoopMain(TCB_PTR tcb, void *work)
{
	DEBUG_AXIS *ta = work;
	
	
	if(Particle_GetEmitterNum(ta->ptc) == 0){
		ta->emit = NULL;
		//Wp_EmitterCreate(ta->ptc, ta->index, ta->cb_no, ta->we_sys);
		Particle_CreateEmitterCallback(ta->ptc, ta->index, DebugParticle_AxisLoopEmitCallBack, ta);
	}
	if(ta->emit == NULL){
		OS_Printf("emit���܂���������Ă��܂���\n");
		return;
	}
	
	if(sys.cont & PAD_KEY_LEFT){
		ta->vel.x -= ADD_AXIS;
	}
	if(sys.cont & PAD_KEY_RIGHT){
		ta->vel.x += ADD_AXIS;
	}
	if(sys.cont & PAD_KEY_UP){
		ta->vel.y -= ADD_AXIS;
	}
	if(sys.cont & PAD_KEY_DOWN){
		ta->vel.y += ADD_AXIS;
	}
	if(sys.cont & PAD_BUTTON_A){
		ta->vel.z += ADD_AXIS;
	}
	if(sys.cont & PAD_BUTTON_B){
		ta->vel.z -= ADD_AXIS;
	}
	SPL_SetEmitterAxis(ta->emit, &ta->vel);
	OS_Printf("DebugAxis x = %d, y = %d, z = %d\n", ta->vel.x, ta->vel.y, ta->vel.z);
}

//--------------------------------------------------------------
/**
 * @brief   �G�~�b�^�̕������L�[����ł�������f�o�b�O�p�^�X�N�𐶐�����
 *
 * @param   ptc			�p�[�e�B�N���V�X�e�����[�N�ւ̃|�C���^
 * @param   emit		�ΏۃG�~�b�^�ւ̃|�C���^
 *
 * DebugParticle_Axis�Ƃ̈Ⴂ�́A������̓G�~�b�^����I����A�ēx����ɃG�~�b�^���J��Ԃ��������܂�
 *
 * ��{�I��WEST_ADD_PARTICLE�֐�����Wp_EmitterCreate�̑���ɌĂ�ł��炤�g������z�肵�Ă��܂�
 */
//--------------------------------------------------------------
void DebugParticle_AxisLoop(PTC_PTR ptc, int index, int cb_no, WE_SYS_PTR we_sys)
{
	DEBUG_AXIS *ta;
	
	ta = sys_AllocMemory(HEAP_ID_DEBUG, sizeof(DEBUG_AXIS));
	memset(ta, 0, sizeof(DEBUG_AXIS));
	ta->ptc = ptc;
	ta->we_sys = we_sys;
	ta->index = index;
	ta->cb_no = cb_no;

//	Wp_EmitterCreate(ptc, index, cb_no, we_sys);
	Particle_CreateEmitterCallback(ptc, index, DebugParticle_AxisLoopEmitCallBack, ta);
	
	TCB_Add(DebugParticle_AxisLoopMain, ta, 10);
}



// =============================================================================
//
//
//	��
//
//
// =============================================================================

typedef struct {
	int				index;
	int				mode;
	int				camera_mode;
	VecFx32			vec[10];
	VecFx16			vel[10];

	GF_CAMERA_PTR	camera;
	EMIT_PTR		emit;
	PTC_PTR			ptc;
	WE_SYS_PTR		wsp;

} DEL;

static void DebugLoopEmitter_CallBack(EMIT_PTR emit)
{
	DEL* wk;
	
	wk = Particle_GetTempPtr();
	
	SPL_SetEmitterPositionX(emit, wk->vec[0].x);
	SPL_SetEmitterPositionY(emit, wk->vec[0].y);
	SPL_SetEmitterPositionZ(emit, wk->vec[0].z);
	
	SPL_SetEmitterAxis(emit, &wk->vel[1]);
	
	Particle_SetEye(wk->ptc, &wk->vec[wk->mode]);
	
//	GFC_ShiftCamera(&wk->vec[4],wk->camera);
	
	wk->emit = emit;
}
#define ADD_FX32		(0x0008)
#define ADD_FX16		(0x0008)
#define ADD_SPEED_UP	(8)
static int DLM_Fx32(VecFx32* p)
{
	VecFx32 op;
	int sw = 0;
	fx32 s = ADD_FX32;
	
	if (sys.cont & PAD_BUTTON_R){
		s *= ADD_SPEED_UP;
	}
	
	op = *p;
	
	if (sys.cont & PAD_KEY_RIGHT){
		(*p).x += s;
	}
	if (sys.cont & PAD_KEY_LEFT){
		(*p).x -= s;
	}
	if (sys.cont & PAD_KEY_UP){
		(*p).y += s;
	}
	if (sys.cont & PAD_KEY_DOWN){
		(*p).y -= s;
	}
	if (sys.cont & PAD_BUTTON_X){
		(*p).z += s;
	}
	if (sys.cont & PAD_BUTTON_Y){
		(*p).z -= s;
	}
	if (sys.cont & PAD_BUTTON_B){
		(*p).x = 0;
		(*p).y = 0;
		(*p).z = 0;
	}
	
	if (op.x != p->x
	||	op.y != p->y
	||	op.z != p->z){
		sw++;
	}

	return sw;
}

static int DLM_Fx16(VecFx16* p)
{
	VecFx16 op;
	int sw = 0;
	fx16 s = ADD_FX32;
	
	if (sys.cont & PAD_BUTTON_R){
		s *= ADD_SPEED_UP;
	}
	
	op = *p;
	
	if (sys.cont & PAD_KEY_RIGHT){
		(*p).x += s;
	}
	if (sys.cont & PAD_KEY_LEFT){
		(*p).x -= s;
	}
	if (sys.cont & PAD_KEY_UP){
		(*p).y += s;
	}
	if (sys.cont & PAD_KEY_DOWN){
		(*p).y -= s;
	}
	if (sys.cont & PAD_BUTTON_X){
		(*p).z += s;
	}
	if (sys.cont & PAD_BUTTON_Y){
		(*p).z -= s;
	}
	
	if (op.x != p->x
	||	op.y != p->y
	||	op.z != p->z){
		sw++;
	}

	return sw;
}

#define ADD_CAM		(1*FX32_HALF)
static int DLM_Camera(VecFx32* p)
{
	VecFx32 op;
	int sw = 0;
	fx32 s = ADD_CAM;
	
	if (sys.cont & PAD_BUTTON_R){
		s *= ADD_SPEED_UP;
	}
	
	op = *p;
	
	if (sys.cont & PAD_KEY_RIGHT){
		(*p).x += s;
	}
	if (sys.cont & PAD_KEY_LEFT){
		(*p).x -= s;
	}
	if (sys.cont & PAD_KEY_UP){
		(*p).y += s;
	}
	if (sys.cont & PAD_KEY_DOWN){
		(*p).y -= s;
	}
	if (sys.cont & PAD_BUTTON_X){
		(*p).z += s;
	}
	if (sys.cont & PAD_BUTTON_Y){
		(*p).z -= s;
	}
	if (sys.cont & PAD_BUTTON_B){
		(*p).x = 0;
		(*p).y = 0;
		(*p).z = 0;
	}
	
	if (op.x != p->x
	||	op.y != p->y
	||	op.z != p->z){
		sw++;
	}

	return sw;
}

static int CameraInput2(GF_CAMERA_PTR camera_ptr)
{
	u8 view;
	fx32 dist;
	u16 persp_way;
	
	BOOL res = FALSE;
	CAMERA_ANGLE angle = {0,0,0,0};
	VecFx32 move = {0,0,0};
	
	int sw = 1;

	//�J������]�i���]�j
	if (sys.cont & PAD_KEY_UP){
		angle.x = ANGLE_MOVE;
		GFC_AddCameraAngleRev(&angle,camera_ptr);
	}else if (sys.cont & PAD_KEY_DOWN){
		angle.x = -ANGLE_MOVE;
		GFC_AddCameraAngleRev(&angle,camera_ptr);
	}else if (sys.cont & PAD_KEY_LEFT){
		angle.y = -ANGLE_MOVE;
		GFC_AddCameraAngleRev(&angle,camera_ptr);
	}else if (sys.cont & PAD_KEY_RIGHT){
		angle.y = ANGLE_MOVE;
		GFC_AddCameraAngleRev(&angle,camera_ptr);
	}
	else {
		sw = 0;
	}

	return sw;
}
static int CameraInput3(GF_CAMERA_PTR camera_ptr)
{
	u8 view;
	fx32 dist;
	u16 persp_way;
	
	BOOL res = FALSE;
	CAMERA_ANGLE angle = {0,0,0,0};
	VecFx32 move = {0,0,0};
	
	int sw = 1;

	if (sys.cont & PAD_KEY_UP){
		angle.x = ANGLE_MOVE;
		GFC_AddCameraAngleRot(&angle,camera_ptr);
	}
	else if (sys.cont & PAD_KEY_DOWN){
		angle.x = -ANGLE_MOVE;
		GFC_AddCameraAngleRot(&angle,camera_ptr);
	}
	else if (sys.cont & PAD_KEY_LEFT){
		angle.y = ANGLE_MOVE;
		GFC_AddCameraAngleRot(&angle,camera_ptr);
	}
	else if (sys.cont & PAD_KEY_RIGHT){
		angle.y = -ANGLE_MOVE;
		GFC_AddCameraAngleRot(&angle,camera_ptr);
	}
	else {
		sw = 0;
	}

	return sw;
}
#define MENU_MAX	(6)
void DebugLoopEmitter_TCB(TCB_PTR tcb, void* work)
{
	DEL* wk = (DEL*)work;
	VecFx32 tmp = { 0, 0, 0 };
	
	if (Particle_GetEmitterNum(wk->ptc) == 0){
		wk->emit = NULL;
		if (sys.cont & PAD_BUTTON_L){
			wk->index++;
			wk->index %= 8;
		}
		Particle_CreateEmitterCallback(wk->ptc, wk->index, DebugLoopEmitter_CallBack, wk);
		return;
	}

	
	{
		int sw = 0;
		int x,y,z;
				
		if (sys.cont & PAD_BUTTON_L){			
			if (sys.trg & PAD_BUTTON_A){
				WET_PokeParticleLaserPosGet_ClientType(2, &wk->vec[0], FALSE, wk->camera_mode);
				sw = 1;
			}
			else if (sys.trg & PAD_BUTTON_B){
				WET_PokeParticleLaserPosGet_ClientType(3, &wk->vec[0], FALSE, wk->camera_mode);
				sw = 1;
			}
			else if (sys.trg & PAD_BUTTON_X){
				WET_PokeParticleLaserPosGet_ClientType(4, &wk->vec[0], FALSE, wk->camera_mode);
				sw = 1;
			}
			else if (sys.trg & PAD_BUTTON_Y){
				WET_PokeParticleLaserPosGet_ClientType(5, &wk->vec[0], FALSE, wk->camera_mode);
				sw = 1;
			}
			else if (sys.trg & PAD_BUTTON_START){
				WET_PokeParticleLaserPosGet_ClientType(0, &wk->vec[0], FALSE, wk->camera_mode);
				sw = 1;
			}
			else if (sys.trg & PAD_BUTTON_SELECT){
				WET_PokeParticleLaserPosGet_ClientType(1, &wk->vec[0], FALSE, wk->camera_mode);
				sw = 1;
			}
			x = wk->vec[0].x;
			y = wk->vec[0].y;
			z = wk->vec[0].z;
			SPL_SetEmitterPositionX(wk->emit, wk->vec[0].x);
			SPL_SetEmitterPositionY(wk->emit, wk->vec[0].y);
			SPL_SetEmitterPositionZ(wk->emit, wk->vec[0].z);
		}
		else {	
			///< �J�������[�h
			if (sys.trg & PAD_BUTTON_SELECT){
				wk->camera_mode ^= 1;
				Particle_CameraTypeSet(wk->ptc, wk->camera_mode);
				{
					char* str_mode[] = {
						"�����ˉe", "���ˉe"
					};
					OS_Printf("�J�������[�h�ؑց@�@>> %s\n", str_mode[wk->camera_mode]);
				}
			}
			
			///< ���샂�[�h
			if (sys.trg & PAD_BUTTON_START){
				wk->mode++;
				wk->mode %= MENU_MAX;
				{
					char* str_mode[] = {
						"���W���샂�[�h",
						"�������샂�[�h",
						"�J�������]���샂�[�h",
						"�J�������]���샂�[�h",
						"�J�����ړ����샂�[�h",
						"���W�I�t�Z�b�g���샂�[�h",
					};
					OS_Printf("���샂�[�h�ؑց@�@�@>> %s\n", str_mode[wk->mode]);
				}
			}
			switch(wk->mode){
			case 0:
				///< ���W
				sw = DLM_Fx32(&wk->vec[wk->mode]);
				x = wk->vec[wk->mode].x;
				y = wk->vec[wk->mode].y;
				z = wk->vec[wk->mode].z;
				SPL_SetEmitterPositionX(wk->emit, wk->vec[wk->mode].x);
				SPL_SetEmitterPositionY(wk->emit, wk->vec[wk->mode].y);
				SPL_SetEmitterPositionZ(wk->emit, wk->vec[wk->mode].z);
				break;
			case 5:
				///< ofs
				wk->vec[wk->mode+1].x = wk->vec[wk->mode].x;
				wk->vec[wk->mode+1].y = wk->vec[wk->mode].y;
				wk->vec[wk->mode+1].z = wk->vec[wk->mode].z;
				sw = DLM_Fx32(&wk->vec[wk->mode]);
				x = wk->vec[wk->mode].x - wk->vec[wk->mode+1].x;
				y = wk->vec[wk->mode].y - wk->vec[wk->mode+1].y;
				z = wk->vec[wk->mode].z - wk->vec[wk->mode+1].z;
				wk->vec[0].x += x;
				wk->vec[0].y += y;
				wk->vec[0].z += z;
				OS_Printf("pos = \(%d\(%d\),%d\(%d\),%d\(%d\)\)\n", wk->vec[0].x,wk->vec[wk->mode+1].x,
																	wk->vec[0].y,wk->vec[wk->mode+1].y,
																	wk->vec[0].z,wk->vec[wk->mode+1].z);
				SPL_SetEmitterPositionX(wk->emit, wk->vec[0].x);
				SPL_SetEmitterPositionY(wk->emit, wk->vec[0].y);
				SPL_SetEmitterPositionZ(wk->emit, wk->vec[0].z);
				break;
			case 1:
				///< ����
				sw = DLM_Fx16(&wk->vel[wk->mode]);
				x = wk->vel[wk->mode].x;
				y = wk->vel[wk->mode].y;
				z = wk->vel[wk->mode].z;
				SPL_SetEmitterAxis(wk->emit, &wk->vel[wk->mode]);
				break;
			case 2:
				///< ���]
				{
					CAMERA_ANGLE ang = GFC_GetCameraAngle(wk->camera);
					sw = CameraInput2(wk->camera);
					x = ang.x;
					y = ang.y;
					z = ang.z;
				}
				break;
			case 3:
				///< ���]
				{
					CAMERA_ANGLE ang = GFC_GetCameraAngle(wk->camera);
					sw = CameraInput3(wk->camera);
					x = ang.x;
					y = ang.y;
					z = ang.z;
				}
				break;
			case 4:
				///< �ړ�
				{
					sw = DLM_Fx32(&wk->vec[wk->mode]);
					x = wk->vec[wk->mode].x;
					y = wk->vec[wk->mode].y;
					z = wk->vec[wk->mode].z;
					GFC_SetLookTarget(&wk->vec[wk->mode], wk->camera);
				}
				break;
			}
		}

		
		if (sw != 0){
			char* str_mode[] = {
				"�@�@�@���W","�@�@�@����","�J�������]","�J�������]","�J�����ړ�","�I�t�Z�b�g",
			};
			OS_Printf("%s = \(%d, %d, %d\)\n",str_mode[wk->mode], x,y,z);
		}
	}
}

static int DebugMasterFlag = 0;

void DebugWazaEffect_LoopEmitter(PTC_PTR ptc, EMIT_PTR emit, WE_SYS_PTR we_sys)
{
	DEL* del = NULL;
	
	if (DebugMasterFlag != 0){ return; }
	#if 1
	DebugMasterFlag = 1;
	#endif
	del = sys_AllocMemory(HEAP_ID_DEBUG, sizeof(DEL));
	
	if (del == NULL){ return; }
	
	memset(del, 0, sizeof(DEL));
	
	del->wsp	= we_sys;
	del->ptc	= ptc;
	del->emit	= emit;
	del->camera = Particle_GetCameraPtr(ptc);
	del->index	= 0;
	del->camera_mode = 0;

	Particle_CreateEmitterCallback(del->ptc, del->index, DebugLoopEmitter_CallBack, del);

	TCB_Add(DebugLoopEmitter_TCB, del, 0x1000);
}



#endif	//PM_DEBUG	+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

