//==============================================================================
/**
 * @file	particle.c
 * @brief	�p�[�e�B�N������c�[��
 * @author	matsuda
 * @date	2005.07.04(��)
 */
//==============================================================================
#include "common.h"
#include "system/particle.h"
#include "spl.h"
#include "wazaeffect/we_err.h"
#include "system/arc_tool.h"

#ifdef PM_DEBUG

	PTC_PTR gDebugPTC = NULL;
	
#endif

//==============================================================================
//	�萔��`
//==============================================================================
//SPL_Init
enum{
	EMIT_MAX = 20,			///<1�̃��\�[�X�œ����ɏo����ő�G�~�b�^��
	PARTICLE_MAX = 200,		///<�ő�p�[�e�B�N����
	FIX_POLYGON_ID = 5,		///<�Œ�|���S��ID
	MIN_POLYGON_ID = 6,		///<�ŏ��|���S��ID
	MAX_POLYGON_ID = 63,	///<�ő�|���S��ID
};

///�G�~�b�^����������Ă��Ȃ��t���O
#define NON_EMIT		(0xffff)

///�����N�h�e�N�X�`��VRAM�}�l�[�W���ōő�Ǘ��o���鐔
#define LNK_TEX_KEY_MAX		(16)

///�����N�h�p���b�gVRAM�}�l�[�W���ōő�Ǘ��o���鐔
//���p�̂̑���NNSGfdFrmPlttVramState�Ɠ��T�C�Y�ɂ���Ȃ�2�Ȃ񂾂��ǁA
//���ꂾ�Ƃ��܂�ɂ��������Ȃ��̂łƂ肠����8��
#define LNK_PLTT_KEY_MAX	(16)

//==============================================================================
//	�\���̒�`
//==============================================================================
//--------------------------------------------------------------
/**
 * @brief   �G�~�b�^�p�����[�^�\����
 */
//--------------------------------------------------------------
typedef struct{
	SPLEmitter *emit_ptr;			///<�G�~�b�^�ւ̃|�C���^
	u16 res_no;						///<���\�[�X�ԍ�
}EMIT_PARAM;

//--------------------------------------------------------------
/**
 * @brief	�p�[�e�B�N���V�X�e���\����
 */
//--------------------------------------------------------------
typedef struct _PARTICLE_SYSTEM{
	SPLManager *spl_manager;		///<SPL�}�l�[�W���ւ̃|�C���^
//	EMIT_PARAM emitter[EMIT_MAX];	///<�G�~�b�^�p�����[�^
	void *res_ptcl;					///<�p�[�e�B�N�����\�[�X�ւ̃|�C���^
	SPLEmitter *temp_emit;			///<�Ō�ɐ��������G�~�b�^�̃|�C���^��ێ�����
	
	void *heap_start;				///<SPL���C�u�����Ŏg�p���郏�[�N�̐擪�A�h���X
	void *heap;						///<�q�[�v�̌��݂̋󂫗̈�̐擪�A�h���X���w��
	void *heap_end;					///<�q�[�v�Ŏg�p�o����I���n�_�̃A�h���X
	
	pTexCallback user_tex_func;		///<�e�N�X�`��VRAM�A�h���X��Ԃ����߂̃R�[���o�b�N�֐�
	pTexCallback user_pltt_func;	///<�e�N�X�`���p���b�g�A�h���X��Ԃ����߂̃R�[���o�b�N�֐�
	
	GF_CAMERA_PTR camera;			///<�J����
	VecFx32 vec;
	u16 persp_way;					///<���ˉe�̊p�x
	
	VecFx32 eye;		//�J�����̈ʒu�x�N�g��
	VecFx32 v_up;		//�J�����̏�����̃x�N�g���ւ̃|�C���^
	VecFx32 at;			//�J�����̏œ_�ւ̃x�N�g��
	
	union{
		NNSGfdFrmTexVramState tex_frm_state;	///<�t���[���e�N�X�`���̌��݂̃������m�ۏ��
		NNSGfdTexKey tex_key[LNK_TEX_KEY_MAX];	///<�����N�h�e�N�X�`���̃e�N�X�`���L�[
	};
	union{
		NNSGfdFrmPlttVramState pltt_frm_state;		///<�t���[���p���b�g�̌��݂̃������m�ۏ��
		NNSGfdPlttKey pltt_key[LNK_PLTT_KEY_MAX];	///<�����N�h�p���b�g�̃p���b�g�L�[
	};
	
	u8 vram_free;					///<Vram�̎���������[�h(PTC_AUTO???_???)
	u8 seq;							///<�V�[�P���X�ԍ�
	u8 global_no;					///<�g�p����O���[�o���ϐ��ԍ�
	u8 camera_type;					///<�J�����̎ˉe����(GF_CAMERA_PERSPECTIV��)
}PARTICLE_SYSTEM;


//==============================================================================
//	�O���[�o���ϐ�
//==============================================================================
//--------------------------------------------------------------
/**
 * ���ݐ�������Ă��p�[�e�B�N���V�X�e���̃|�C���^������B
 * SPL���C�u�����Ŏg�p����LocalAlloc�֐����ŁA�p�[�e�B�N���V�X�e���Ŋm�ۂ��Ă���q�[�v�̈��
 * �擾����K�v������B������LocalAlloc��SPL���C�u�����Ŋ֐��̌^�����߂��Ă��邽�߁A
 * �q�[�v�̈�̃|�C���^��n�����Ƃ��o���Ȃ��̂ŁA���̃O���[�o���ϐ��o�R�œn���B
 */
//--------------------------------------------------------------
static void *ParticleSystemPtr[PARTICLE_GLOBAL_MAX];

//--------------------------------------------------------------
/**
 * �G�~�b�^�쐬���̃R�[���o�b�N�֐����ŁA�C�ӂ̃f�[�^���Q�Əo����悤�A
 * �ꎞ�I�ɂ����ɓn�������f�[�^�̃|�C���^������B
 * (���ŃG�~�b�^�̏ꍇ�AEmitCreate��NULL�|�C���^���Ԃ��Ă���̂ŁA�G�~�b�^�����ς���ꍇ�A
 *  �R�[���o�b�N�֐����ŕύX���Ă�����K�v�����邽��)
 */
//--------------------------------------------------------------
static void *ParticleTempPtr;

//--------------------------------------------------------------
/**
 * �e�N�X�`�����[�h���̃R�[���o�b�N�֐����ŁA�����N�h�}�l�[�W���[�̏ꍇ�A�L�[����
 * PTC�ɋL������K�v������̂ŁA�����Ɉꎞ�I��PTC�̃A�h���X���Z�b�g���Ă���
 */
//--------------------------------------------------------------
static PTC_PTR TexLoadTempPtc;


//==============================================================================
//	�f�[�^��`
//==============================================================================
///�f�t�H���g�̃J�����̈ʒu�x�N�g��
static const VecFx32 DefaultEye = {
//	0, -0x2500, 0x3500
//	0x2500, 0, 0x2200
//	-0x2000, -0x2000, -0x2000
//	-0x300, -0x100, 0x2100
//	0, 0, 0x2100
	0, 0, 0x4000
//	0, 15*0x1000, 0
//	128*0x1000, 128*0x1000, 0x4000
};
///�f�t�H���g�̃J�����̏�����̃x�N�g��
static const VecFx32 DefaultUp = {
	0, FX32_ONE, 0
};
///�f�t�H���g�̃J�����̏œ_�ւ̃x�N�g��
static const VecFx32 DefaultAt = {
	0, 0, 0
};

//==============================================================================
//	�v���g�^�C�v�錾
//==============================================================================
static void *Particle_LocalAlloc_0(u32 size);
static void *Particle_LocalAlloc_1(u32 size);
static void *Particle_LocalAlloc_2(u32 size);
static void *Particle_LocalAlloc_3(u32 size);
static void *Particle_LocalAlloc_4(u32 size);
static void *Particle_LocalAlloc_5(u32 size);
static void *Particle_LocalAlloc_6(u32 size);
static void *Particle_LocalAlloc_7(u32 size);
static void *Particle_LocalAlloc_8(u32 size);
static void *Particle_LocalAlloc_9(u32 size);
static void *Particle_LocalAlloc_10(u32 size);
static void *Particle_LocalAlloc_11(u32 size);
static void *Particle_LocalAlloc_12(u32 size);
static void *Particle_LocalAlloc_13(u32 size);
static void *Particle_LocalAlloc_14(u32 size);
static void *Particle_LocalAlloc_15(u32 size);
static inline void *Particle_LocalAlloc(PARTICLE_SYSTEM *psys, u32 size);
static void Particle_TexLoad(PTC_PTR psys);
static void VWait_TexLoad(TCB_PTR tcb, void *work);

void Particle_SystemExit(PTC_PTR psys);
void Particle_EmitterDeleteAll(PTC_PTR psys);
void Particle_ResourceSet(PTC_PTR psys, void *resource, int vram_free, int tex_at_once);

//==============================================================================
//	
//==============================================================================
///�p�[�e�B�N���V�X�e�����Ŏg�p����̈�m�ۊ֐��̃|�C���^�e�[�u��
static const SPLAlloc LocalAllocFunc[] = {
	Particle_LocalAlloc_0,
	Particle_LocalAlloc_1,
	Particle_LocalAlloc_2,
	Particle_LocalAlloc_3,
	Particle_LocalAlloc_4,
	Particle_LocalAlloc_5,
	Particle_LocalAlloc_6,
	Particle_LocalAlloc_7,
	Particle_LocalAlloc_8,
	Particle_LocalAlloc_9,
	Particle_LocalAlloc_10,
	Particle_LocalAlloc_11,
	Particle_LocalAlloc_12,
	Particle_LocalAlloc_13,
	Particle_LocalAlloc_14,
	Particle_LocalAlloc_15,
};



#if 0	//------- �p�[�e�B�N���g�p�� ---- 2005.07.15(��)

void BattleParticle_TestInit(void)
{
	PARTICLE_SYSTEM *psys;
	
	psys = Particle_SystemCreate(sAllocTex, sAllocTexPalette);
//	psys = Particle_SystemCreate(NULL, sAllocTexPalette);
	TCB_Add(BattleParticle_Main, psys, 20);
}

static void BattleParticle_Main(TCB_PTR tcb, void *work)
{
	PARTICLE_SYSTEM *psys = work;
	void *resource;
	
	switch(psys->seq){
	case 0:
		resource = Particle_ResourceLoad("wazaeffect/effectdata/output5.spa");
		Particle_ResourceSet(psys, resource);
		psys->seq++;
		break;
	case 1:
		Particle_Draw(psys);	//�p�[�e�B�N���`��
		Particle_Calc(psys);	//�p�[�e�B�N���v�Z
		break;
	}
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
#if 0
	NNSGfdTexKey key = NNS_GfdAllocTexVram(size, is4x4comp, 0);
	SDK_ASSERT(key != NNS_GFD_ALLOC_ERROR_TEXKEY);
	return NNS_GfdGetTexKeyAddr(key);
#else
	u32 address;
	
	NNSGfdTexKey key = NNS_GfdAllocTexVram(size, is4x4comp, 0);
	key = NNS_GfdAllocTexVram(size, is4x4comp, 0);
	SDK_ASSERT(key != NNS_GFD_ALLOC_ERROR_TEXKEY);
	address = NNS_GfdGetTexKeyAddr(key);
	OS_Printf("Vram�A�h���X��%#x\n", address);
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
#if 0
	NNSGfdPlttKey key = NNS_GfdAllocPlttVram(size, is4pltt, 0);
	if(key == NNS_GFD_ALLOC_ERROR_PLTTKEY){
		GF_ASSERT(0 && "�p���b�g�G���[");
	}
	return NNS_GfdGetPlttKeyAddr(key);
#else
	return 0x20*4;
#endif
}

#endif	//------------- �p�[�e�B�N���g�p�� ---------------------------




//--------------------------------------------------------------
/**
 * @brief   �p�[�e�B�N���V�X�e���Ŏg�p���郏�[�N�̏�����
 *
 * Particle_SystemCreate������ɂ�������s����K�v������܂��B
 */
//--------------------------------------------------------------
void Particle_SystemWorkInit(void)
{
	int i;
	
	for(i = 0; i < PARTICLE_GLOBAL_MAX; i++){
		ParticleSystemPtr[i] = NULL;
	}
}

//--------------------------------------------------------------
/**
 * @brief   �p�[�e�B�N���V�X�e�����쐬����
 *
 * @param   tex_func		�e�N�X�`�����[�h���A�g�p����Vram�A�h���X��Ԃ��֐��ւ̃|�C���^
 * @param   pltt_func		�e�N�X�`�����[�h���A�g�p����p���b�gVram�A�h���X��Ԃ��֐��ւ̃|�C���^
 * @param   work			SPL���C�u�����Ŏg�p���邽�߂Ɋ��蓖�Ă郏�[�N�̃|�C���^
 * @param   work_size		�n�������[�N�̃T�C�Y(PARTICLE_LIB_HEAP_SIZE�Ɠ���OR�ȏ�̃T�C�Y���K�v)
 * @param   personal_camera		�p�[�e�B�N���Ǝ��̃J�����ݒ�����ꍇ��TRUE�B
 * @param   heap_id			�p�[�e�B�N���V�X�e���쐬�Ɏg�p����q�[�vID
 *
 * @retval  �p�[�e�B�N���V�X�e�����[�N�ւ̃|�C���^(�����o���Ȃ������ꍇ��NULL)
 *
 * tex_func, pltt_func ��NULL�w�肵���ꍇ��NitroSystem��Vram�APltt�}�l�[�W���Ɉˑ����܂��B
 *
 * work�œn�������[�N��SPL���C�u�����Ŏg�p���܂��B
 * Alloc���Ď�ɓ��ꂽ���[�N�̈�̃|�C���^��n�����ꍇ�AParticle_SystemExit��A�O����
 * ����������s���Ă��������B(�p�[�e�B�N���V�X�e�����Ń��[�N�̉�������͂��܂���)
 *
 * global_no�F�p�[�e�B�N���V�X�e������SPL���C�u�����Ƃ̂����ŃO���[�o���ϐ����g�p���܂��B
 * ���ׂ̈̃O���[�o���ϐ����z��Ŋ��ɗp�ӂ���Ă��܂��B���̉��Ԗڂ̃O���[�o���ϐ����g�p���āA
 * �p�[�e�B�N���V�X�e���𓮂������A�Ƃ����w��ł��B
 * �p�ӂ���Ă���O���[�o���ϐ��ɂ͌��肪����܂��B(2005.07.26(��)���݂�3��(0�`2))
 */
//--------------------------------------------------------------
PTC_PTR Particle_SystemCreate(pTexCallback tex_func, pTexCallback pltt_func, void *work, int work_size, int personal_camera, int heap_id)
{
	PARTICLE_SYSTEM *psys;
	int global_no;
	
	//�O���[�o���ϐ��̋󂫂��T�[�`
	for(global_no = 0; global_no < PARTICLE_GLOBAL_MAX; global_no++){
		if(ParticleSystemPtr[global_no] == NULL){
			break;
		}
	}
	if(global_no >= PARTICLE_GLOBAL_MAX){
		return NULL;
	}
	
	//�p�[�e�B�N���V�X�e���̃������m��
	psys = sys_AllocMemory(heap_id, sizeof(PARTICLE_SYSTEM));
	if(psys == NULL){
		GF_ASSERT(0 && "�������m�ێ��s\n");
	}
	memset(psys, 0, sizeof(PARTICLE_SYSTEM));

	//�p�����[�^�����ݒ�
	psys->user_tex_func = tex_func;
	psys->user_pltt_func = pltt_func;

	psys->eye = DefaultEye;
	psys->v_up = DefaultUp;
	psys->at = DefaultAt;

	//�������ݒ�
	SDK_ASSERT(global_no < PARTICLE_GLOBAL_MAX);
	memset(work, 0, work_size);
	psys->heap_start = work;
	psys->heap = work;
	psys->heap_end = (void*)((u32)work + work_size);
	psys->global_no = global_no;
	ParticleSystemPtr[global_no] = psys;
	
	//�J�����ݒ�
	if(personal_camera == TRUE){
		psys->camera = GFC_AllocCamera(heap_id);
		{
			VEC_Set(&psys->vec, 0, 0, 0);
			psys->persp_way = 8192;//0x06c1;
		#if 0
			GFC_InitCameraTDA(&psys->vec,
						0x1000,					//����
						&psys->angle,
						psys->persp_way,		//���ˉe�̊p�x
						GF_CAMERA_PERSPECTIV,
						psys->camera
						);
		#elif 0
			GFC_InitCameraCDA(&psys->vec,
						0x1000,					//����
						&psys->angle,
						psys->persp_way,		//���ˉe�̊p�x
						GF_CAMERA_PERSPECTIV,
						psys->camera
						);
		#else
			GFC_InitCameraTC(&DefaultAt, &DefaultEye,
						psys->persp_way,		//���ˉe�̊p�x
						GF_CAMERA_PERSPECTIV,
						FALSE,
						psys->camera
						);
		#endif
			psys->camera_type = GF_CAMERA_PERSPECTIV;
			GFC_AttachCamera(psys->camera);
		}
	}

	// �p�[�e�B�N���}�l�[�W����������
	psys->spl_manager = SPL_Init(LocalAllocFunc[global_no], EMIT_MAX, PARTICLE_MAX, 
		FIX_POLYGON_ID, MIN_POLYGON_ID, MAX_POLYGON_ID);
	
	Particle_SetVup(psys, &DefaultUp);
	
	return psys;
}

//--------------------------------------------------------------
/**
 * @brief   �p�[�e�B�N���V�X�e���I������
 *
 * @param   �p�[�e�B�N���V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void Particle_SystemExit(PTC_PTR psys)
{
	int i;
	
	SDK_ASSERT(psys != NULL);
	SDK_ASSERT(psys->spl_manager != NULL);

	//�G�~�b�^�S�폜
	Particle_EmitterDeleteAll(psys);
	
	//�e�N�X�`��Vram�������
	if(psys->vram_free & PTC_AUTOTEX_FRM){
		NNS_GfdSetFrmTexVramState(&psys->tex_frm_state);
	}
	else if(psys->vram_free & PTC_AUTOTEX_LNK){
		//2005.07.25(��)�@���ݖ����� �����Ǎ폜���̂̏����͍���̂ŁA�폜�����͍쐬
		int i;
		for(i = 0; i < LNK_TEX_KEY_MAX; i++){
			if(psys->tex_key[i] != NNS_GFD_ALLOC_ERROR_TEXKEY){
				NNS_GfdFreeLnkTexVram(psys->tex_key[i]);
				psys->tex_key[i] = NNS_GFD_ALLOC_ERROR_TEXKEY;
			}
		}
	}
	//�p���b�gVram��������p�����[�^������
	if(psys->vram_free & PTC_AUTOPLTT_FRM){
		NNS_GfdSetFrmPlttVramState(&psys->pltt_frm_state);
	}
	else if(psys->vram_free & PTC_AUTOPLTT_LNK){
		//2005.07.25(��)�@���ݖ����� �����Ǎ폜���̂̏����͍���̂ŁA�폜�����͍쐬
		int i;
		for(i = 0; i < LNK_PLTT_KEY_MAX; i++){
			if(psys->pltt_key[i] != NNS_GFD_ALLOC_ERROR_PLTTKEY){
				NNS_GfdFreeLnkPlttVram(psys->pltt_key[i]);
				psys->pltt_key[i] = NNS_GFD_ALLOC_ERROR_PLTTKEY;
			}
		}
	}
	psys->vram_free = PTC_AUTOTEX_NULL | PTC_AUTOPLTT_NULL;
	psys->temp_emit = NULL;

	//���\�[�X�t�@�C����ǂݍ���ł��郁���������
	if(psys->res_ptcl != NULL){
		sys_FreeMemoryEz(psys->res_ptcl);
		psys->res_ptcl = NULL;
	}
	
	//�p�[�e�B�N���V�X�e���̃��[�N���
	for(i = 0; i < PARTICLE_GLOBAL_MAX; i++){
		if(ParticleSystemPtr[i] == psys){
			ParticleSystemPtr[i] = NULL;
			break;
		}
	}
	SDK_ASSERT(i < PARTICLE_GLOBAL_MAX); //ParticleSystemPtr�Ɉ���������Ȃ��Ƃ������Ƃ͕s���Ȓl
	
	//�J�������
	if(psys->camera != NULL){
		GFC_FreeCamera(psys->camera);
	}

	sys_FreeMemoryEz(psys);
}

//--------------------------------------------------------------
/**
 * @brief   ��������Ă���p�[�e�B�N���V�X�e���S�Ă��I��������
 */
//--------------------------------------------------------------
void Particle_SystemExitAll(void)
{
	int i;
	
	for(i = 0; i < PARTICLE_GLOBAL_MAX; i++){
		if(ParticleSystemPtr[i] != NULL){
			Particle_SystemExit(ParticleSystemPtr[i]);
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief   �p�[�e�B�N���V�X�e�����Ŏg�p����Alloc�֐�
 *
 * @param   size		�m�ۂ��郁�����T�C�Y
 *
 * SPL_Init�Ŋ֐��|�C���^�Ƃ��ēn���Ă���̂ŁA���̊֐��̌`��ς��Ă͂����Ȃ��B
 */
//--------------------------------------------------------------
static inline void *Particle_LocalAlloc(PARTICLE_SYSTEM *psys, u32 size)
{
	void *work;
	u32 heap_adrs, rem;
	
	work = psys->heap;
	
	heap_adrs = (u32)psys->heap + size;
	rem = heap_adrs % 4;
	if(rem > 0){
		heap_adrs += 4 - rem;	//4�o�C�g�␳
	}
	psys->heap = (void*)heap_adrs;

	if(psys->heap >= psys->heap_end){
		GF_ASSERT(0 && "�p�[�e�B�N���V�X�e���Ń������I�[�o�[���������܂����I\n");
	}
	return work;
}

//--------------------------------------------------------------
/**
 * @brief   �p�[�e�B�N���V�X�e�����Ŏg�p����Alloc�֐�
 * @param   size		�m�ۂ��郁�����T�C�Y
 *
 * SPL_Init�Ŋ֐��|�C���^�Ƃ��ēn���Ă���̂ŁA���̊֐��̌`��ς��Ă͂����Ȃ��B
 */
//--------------------------------------------------------------
static void *Particle_LocalAlloc_0(u32 size)
{
	PARTICLE_SYSTEM *psys;
	
	psys = ParticleSystemPtr[PARTICLE_GLOBAL_0];
	return Particle_LocalAlloc(psys, size);
}

//--------------------------------------------------------------
/**
 * @brief   �p�[�e�B�N���V�X�e�����Ŏg�p����Alloc�֐�
 * @param   size		�m�ۂ��郁�����T�C�Y
 *
 * SPL_Init�Ŋ֐��|�C���^�Ƃ��ēn���Ă���̂ŁA���̊֐��̌`��ς��Ă͂����Ȃ��B
 */
//--------------------------------------------------------------
static void *Particle_LocalAlloc_1(u32 size)
{
	PARTICLE_SYSTEM *psys;
	
	psys = ParticleSystemPtr[PARTICLE_GLOBAL_1];
	return Particle_LocalAlloc(psys, size);
}

//--------------------------------------------------------------
/**
 * @brief   �p�[�e�B�N���V�X�e�����Ŏg�p����Alloc�֐�
 * @param   size		�m�ۂ��郁�����T�C�Y
 *
 * SPL_Init�Ŋ֐��|�C���^�Ƃ��ēn���Ă���̂ŁA���̊֐��̌`��ς��Ă͂����Ȃ��B
 */
//--------------------------------------------------------------
static void *Particle_LocalAlloc_2(u32 size)
{
	PARTICLE_SYSTEM *psys;
	
	psys = ParticleSystemPtr[PARTICLE_GLOBAL_2];
	return Particle_LocalAlloc(psys, size);
}

//--------------------------------------------------------------
/**
 * @brief   �p�[�e�B�N���V�X�e�����Ŏg�p����Alloc�֐�
 * @param   size		�m�ۂ��郁�����T�C�Y
 *
 * SPL_Init�Ŋ֐��|�C���^�Ƃ��ēn���Ă���̂ŁA���̊֐��̌`��ς��Ă͂����Ȃ��B
 */
//--------------------------------------------------------------
static void *Particle_LocalAlloc_3(u32 size)
{
	PARTICLE_SYSTEM *psys;
	
	psys = ParticleSystemPtr[PARTICLE_GLOBAL_3];
	return Particle_LocalAlloc(psys, size);
}

//--------------------------------------------------------------
/**
 * @brief   �p�[�e�B�N���V�X�e�����Ŏg�p����Alloc�֐�
 * @param   size		�m�ۂ��郁�����T�C�Y
 *
 * SPL_Init�Ŋ֐��|�C���^�Ƃ��ēn���Ă���̂ŁA���̊֐��̌`��ς��Ă͂����Ȃ��B
 */
//--------------------------------------------------------------
static void *Particle_LocalAlloc_4(u32 size)
{
	PARTICLE_SYSTEM *psys;
	
	psys = ParticleSystemPtr[PARTICLE_GLOBAL_4];
	return Particle_LocalAlloc(psys, size);
}

//--------------------------------------------------------------
/**
 * @brief   �p�[�e�B�N���V�X�e�����Ŏg�p����Alloc�֐�
 * @param   size		�m�ۂ��郁�����T�C�Y
 *
 * SPL_Init�Ŋ֐��|�C���^�Ƃ��ēn���Ă���̂ŁA���̊֐��̌`��ς��Ă͂����Ȃ��B
 */
//--------------------------------------------------------------
static void *Particle_LocalAlloc_5(u32 size)
{
	PARTICLE_SYSTEM *psys;
	
	psys = ParticleSystemPtr[PARTICLE_GLOBAL_5];
	return Particle_LocalAlloc(psys, size);
}

//--------------------------------------------------------------
/**
 * @brief   �p�[�e�B�N���V�X�e�����Ŏg�p����Alloc�֐�
 * @param   size		�m�ۂ��郁�����T�C�Y
 *
 * SPL_Init�Ŋ֐��|�C���^�Ƃ��ēn���Ă���̂ŁA���̊֐��̌`��ς��Ă͂����Ȃ��B
 */
//--------------------------------------------------------------
static void *Particle_LocalAlloc_6(u32 size)
{
	PARTICLE_SYSTEM *psys;
	
	psys = ParticleSystemPtr[PARTICLE_GLOBAL_6];
	return Particle_LocalAlloc(psys, size);
}

//--------------------------------------------------------------
/**
 * @brief   �p�[�e�B�N���V�X�e�����Ŏg�p����Alloc�֐�
 * @param   size		�m�ۂ��郁�����T�C�Y
 *
 * SPL_Init�Ŋ֐��|�C���^�Ƃ��ēn���Ă���̂ŁA���̊֐��̌`��ς��Ă͂����Ȃ��B
 */
//--------------------------------------------------------------
static void *Particle_LocalAlloc_7(u32 size)
{
	PARTICLE_SYSTEM *psys;
	
	psys = ParticleSystemPtr[PARTICLE_GLOBAL_7];
	return Particle_LocalAlloc(psys, size);
}

//--------------------------------------------------------------
/**
 * @brief   �p�[�e�B�N���V�X�e�����Ŏg�p����Alloc�֐�
 * @param   size		�m�ۂ��郁�����T�C�Y
 *
 * SPL_Init�Ŋ֐��|�C���^�Ƃ��ēn���Ă���̂ŁA���̊֐��̌`��ς��Ă͂����Ȃ��B
 */
//--------------------------------------------------------------
static void *Particle_LocalAlloc_8(u32 size)
{
	PARTICLE_SYSTEM *psys;
	
	psys = ParticleSystemPtr[PARTICLE_GLOBAL_8];
	return Particle_LocalAlloc(psys, size);
}

//--------------------------------------------------------------
/**
 * @brief   �p�[�e�B�N���V�X�e�����Ŏg�p����Alloc�֐�
 * @param   size		�m�ۂ��郁�����T�C�Y
 *
 * SPL_Init�Ŋ֐��|�C���^�Ƃ��ēn���Ă���̂ŁA���̊֐��̌`��ς��Ă͂����Ȃ��B
 */
//--------------------------------------------------------------
static void *Particle_LocalAlloc_9(u32 size)
{
	PARTICLE_SYSTEM *psys;
	
	psys = ParticleSystemPtr[PARTICLE_GLOBAL_9];
	return Particle_LocalAlloc(psys, size);
}

//--------------------------------------------------------------
/**
 * @brief   �p�[�e�B�N���V�X�e�����Ŏg�p����Alloc�֐�
 * @param   size		�m�ۂ��郁�����T�C�Y
 *
 * SPL_Init�Ŋ֐��|�C���^�Ƃ��ēn���Ă���̂ŁA���̊֐��̌`��ς��Ă͂����Ȃ��B
 */
//--------------------------------------------------------------
static void *Particle_LocalAlloc_10(u32 size)
{
	PARTICLE_SYSTEM *psys;
	
	psys = ParticleSystemPtr[PARTICLE_GLOBAL_10];
	return Particle_LocalAlloc(psys, size);
}

//--------------------------------------------------------------
/**
 * @brief   �p�[�e�B�N���V�X�e�����Ŏg�p����Alloc�֐�
 * @param   size		�m�ۂ��郁�����T�C�Y
 *
 * SPL_Init�Ŋ֐��|�C���^�Ƃ��ēn���Ă���̂ŁA���̊֐��̌`��ς��Ă͂����Ȃ��B
 */
//--------------------------------------------------------------
static void *Particle_LocalAlloc_11(u32 size)
{
	PARTICLE_SYSTEM *psys;
	
	psys = ParticleSystemPtr[PARTICLE_GLOBAL_11];
	return Particle_LocalAlloc(psys, size);
}

//--------------------------------------------------------------
/**
 * @brief   �p�[�e�B�N���V�X�e�����Ŏg�p����Alloc�֐�
 * @param   size		�m�ۂ��郁�����T�C�Y
 *
 * SPL_Init�Ŋ֐��|�C���^�Ƃ��ēn���Ă���̂ŁA���̊֐��̌`��ς��Ă͂����Ȃ��B
 */
//--------------------------------------------------------------
static void *Particle_LocalAlloc_12(u32 size)
{
	PARTICLE_SYSTEM *psys;
	
	psys = ParticleSystemPtr[PARTICLE_GLOBAL_12];
	return Particle_LocalAlloc(psys, size);
}

//--------------------------------------------------------------
/**
 * @brief   �p�[�e�B�N���V�X�e�����Ŏg�p����Alloc�֐�
 * @param   size		�m�ۂ��郁�����T�C�Y
 *
 * SPL_Init�Ŋ֐��|�C���^�Ƃ��ēn���Ă���̂ŁA���̊֐��̌`��ς��Ă͂����Ȃ��B
 */
//--------------------------------------------------------------
static void *Particle_LocalAlloc_13(u32 size)
{
	PARTICLE_SYSTEM *psys;
	
	psys = ParticleSystemPtr[PARTICLE_GLOBAL_13];
	return Particle_LocalAlloc(psys, size);
}

//--------------------------------------------------------------
/**
 * @brief   �p�[�e�B�N���V�X�e�����Ŏg�p����Alloc�֐�
 * @param   size		�m�ۂ��郁�����T�C�Y
 *
 * SPL_Init�Ŋ֐��|�C���^�Ƃ��ēn���Ă���̂ŁA���̊֐��̌`��ς��Ă͂����Ȃ��B
 */
//--------------------------------------------------------------
static void *Particle_LocalAlloc_14(u32 size)
{
	PARTICLE_SYSTEM *psys;
	
	psys = ParticleSystemPtr[PARTICLE_GLOBAL_14];
	return Particle_LocalAlloc(psys, size);
}

//--------------------------------------------------------------
/**
 * @brief   �p�[�e�B�N���V�X�e�����Ŏg�p����Alloc�֐�
 * @param   size		�m�ۂ��郁�����T�C�Y
 *
 * SPL_Init�Ŋ֐��|�C���^�Ƃ��ēn���Ă���̂ŁA���̊֐��̌`��ς��Ă͂����Ȃ��B
 */
//--------------------------------------------------------------
static void *Particle_LocalAlloc_15(u32 size)
{
	PARTICLE_SYSTEM *psys;
	
	psys = ParticleSystemPtr[PARTICLE_GLOBAL_15];
	return Particle_LocalAlloc(psys, size);
}

//--------------------------------------------------------------
/**
 * @brief   �p�[�e�B�N���̃��\�[�X�t�@�C����ǂݍ���
 *
 * @param   heap_id		�q�[�vID
 * @param   path		�ǂݍ��ރ��\�[�X�t�@�C��(*.spa)�ւ̃|�C���^
 *
 * @retval  �ǂݍ��񂾃��\�[�X�t�@�C���̃|�C���^
 *
 * Particle_ResourceSet�֐��ƃZ�b�g�Ŏg�p���鎖���O��ł��B
 * �ǂݍ��񂾃��\�[�X�t�@�C����Particle_SystemExit��FreeMemory����܂��B
 */
//--------------------------------------------------------------
void * Particle_ResourceLoad(int heap_id, const char *path)
{
	return sys_LoadFile(heap_id, path);
}

//--------------------------------------------------------------
/**
 * @brief   Arc����Ă���p�[�e�B�N���̃��\�[�X�t�@�C����ǂݍ���
 *
 * @param   file_kind	�ǂݍ��ރA�[�J�C�u�t�@�C���̎�ރC���f�b�N�X�i���o�[�iarc_tool.h�ɋL�q)
 * @param   index		�ǂݍ��ރf�[�^�̃A�[�J�C�u�t�@�C����̃C���f�b�N�X�i���o�[
 * @param   heap_id		�q�[�vID
 *
 * @retval  �ǂݍ��񂾃��\�[�X�t�@�C���̃|�C���^
 *
 * Particle_ResourceSet�֐��ƃZ�b�g�Ŏg�p���鎖���O��ł��B
 * �ǂݍ��񂾃��\�[�X�t�@�C����Particle_SystemExit��FreeMemory����܂��B
 */
//--------------------------------------------------------------
void * Particle_ArcResourceLoad(int file_kind, int index, int heap_id)
{
	return ArchiveDataLoadMalloc(file_kind, index, heap_id);
}

//--------------------------------------------------------------
/**
 * @brief   �p�[�e�B�N���̃��\�[�X�t�@�C�����p�[�e�B�N���V�X�e���ɃZ�b�g�����������s��
 *
 * @param   psys			�p�[�e�B�N���V�X�e�����[�N�ւ̃|�C���^
 * @param   resource		Particle_(Arc)ResourceLoad�œǂݍ��񂾃��\�[�X�t�@�C���̃|�C���^
 * @param   vram_free		Vram�̎������(�r�b�g�w��FPTC_AUTOTEX_??? | PTC_AUTOPLTT_???)
 * @param   tex_at_once		TRUE:�e�N�X�`�����]���AFALSE:V�u�����N���ɓ]��
 *
 * vram_free�⑫:���[�h��L���ɂ��邱�ƂŁAParticle_SystemExit���Ƀe�N�X�`���Ő�L����Vram��Ԃ�
 * LoadFile���s�O�̏�Ԃɖ߂��܂��B
 * �A��Particle_SystemCreate���ɁA�e�N�X�`���̃R�[���o�b�N�֐���ݒ肵�Ȃ������ꍇ��SPL���C�u������
 * ����Ɉˑ����邱�ƂɂȂ�܂��B(���������ŉ�����Ă����񂶂�Ȃ��ł��傤���c)
 */
//--------------------------------------------------------------
void Particle_ResourceSet(PTC_PTR psys, void *resource, int vram_free, int tex_at_once)
{
	GF_ASSERT(psys->spl_manager != NULL);
	GF_ASSERT(psys->res_ptcl == NULL);
	
	psys->vram_free = vram_free;
	//�e�N�X�`��Vram��������p�����[�^������
	if(vram_free & PTC_AUTOTEX_FRM){
		NNS_GfdGetFrmTexVramState(&psys->tex_frm_state);
	}
	else if(vram_free & PTC_AUTOTEX_LNK){
		//2005.07.25(��)�@���ݖ�����(�֐��R�����g�ɂ���Ԃ������Ă���܂�)
		//�Ƃ肠�����������������Ă���
		int i;
		for(i = 0; i < LNK_TEX_KEY_MAX; i++){
			psys->tex_key[i] = NNS_GFD_ALLOC_ERROR_TEXKEY;
		}
	}
	//�p���b�gVram��������p�����[�^������
	if(vram_free & PTC_AUTOPLTT_FRM){
		NNS_GfdGetFrmPlttVramState(&psys->pltt_frm_state);
	}
	else if(vram_free & PTC_AUTOPLTT_LNK){
		//2005.07.25(��)�@���ݖ�����(�֐��R�����g�ɂ���Ԃ������Ă���܂�)
		//�Ƃ肠�����������������Ă���
		int i;
		for(i = 0; i < LNK_PLTT_KEY_MAX; i++){
			psys->pltt_key[i] = NNS_GFD_ALLOC_ERROR_PLTTKEY;
		}
	}
	
	//�p�[�e�B�N�����\�[�X���֘A�t����
	psys->res_ptcl = resource;
	
	//�e�N�X�`�����[�h
	if(tex_at_once == TRUE){
		Particle_TexLoad(psys);
	}
	else{
		VWaitTCB_Add(VWait_TexLoad, psys, 5);
	}
}

//--------------------------------------------------------------
/**
 * @brief   �p�[�e�B�N���̃e�N�X�`���[���[�h
 * @param   psys		�p�[�e�B�N���V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void Particle_TexLoad(PTC_PTR psys)
{
	//�}�l�[�W���ɑ΂��ăp�[�e�B�N�����\�[�X��ǂݍ���
	SPL_Load(psys->spl_manager, psys->res_ptcl);

	// �e�N�X�`����ǂݍ���
	TexLoadTempPtc = psys;
	if(psys->user_tex_func == NULL){
		//NitroSystem��VRAM�}�l�[�W���Ɉˑ�����
		(void)SPL_LoadTexByVRAMManager(psys->spl_manager);
	}
	else{
		// �R�[���o�b�N�֐���p���ăe�N�X�`���ǂݍ��݂����O�ł����Ȃ��ꍇ
		SPL_LoadTexByCallbackFunction(psys->spl_manager, psys->user_tex_func);
	}
	if(psys->user_pltt_func == NULL){
		(void)SPL_LoadTexPlttByVRAMManager(psys->spl_manager);
	}
	else{
		SPL_LoadTexPlttByCallbackFunction(psys->spl_manager, psys->user_pltt_func);
	}
	TexLoadTempPtc = NULL;

	{
		u32 tex_size;
		tex_size = SPL_GetTexSizeOnResource(psys->res_ptcl);
	#ifdef OSP_PARTICLE_ON
		OS_Printf("�e�N�X�`���T�C�Y��%#x\n", tex_size);
	#endif
	}
}

//--------------------------------------------------------------
/**
 * @brief   V�u�����N�^�X�N�F�p�[�e�B�N���̃e�N�X�`���[���[�h
 *
 * @param   tcb			TCB�ւ̃|�C���^
 * @param   work		�p�[�e�B�N���V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void VWait_TexLoad(TCB_PTR tcb, void *work)
{
	PTC_PTR psys = work;
	
	Particle_TexLoad(psys);
	TCB_Delete(tcb);
}

//--------------------------------------------------------------
/**
 * @brief   �����N�h���X�g�̃e�N�X�`���L�[���L������
 *
 * @param   psys		�p�[�e�B�N���V�X�e�����[�N�ւ̃|�C���^
 * @param   tex_key		�e�N�X�`���L�[
 *
 * ���e�N�X�`�����[�h���̃R�[���o�b�N�֐����ł̂݌ĂԎ���������܂�
 */
//--------------------------------------------------------------
void Particle_LnkTexKeySet(NNSGfdTexKey tex_key)
{
	int i;
	PTC_PTR psys;
	
	GF_ASSERT(tex_key != NNS_GFD_ALLOC_ERROR_TEXKEY);
	GF_ASSERT(TexLoadTempPtc != NULL);
	
	psys = TexLoadTempPtc;
	
	for(i = 0; i < LNK_TEX_KEY_MAX; i++){
		if(psys->tex_key[i] == NNS_GFD_ALLOC_ERROR_TEXKEY){
			psys->tex_key[i] = tex_key;
			return;
		}
	}
	GF_ASSERT(0 && "�p�[�e�B�N���e�N�X�`���Ǘ����𒴂��Ă��܂�!\n");
}

//--------------------------------------------------------------
/**
 * @brief   �p���b�g�����N�h���X�g�̃e�N�X�`���L�[���L������
 *
 * @param   psys		�p�[�e�B�N���V�X�e�����[�N�ւ̃|�C���^
 * @param   tex_key		�e�N�X�`���L�[
 *
 * ���e�N�X�`�����[�h���̃R�[���o�b�N�֐����ł̂݌ĂԎ���������܂�
 */
//--------------------------------------------------------------
void Particle_PlttLnkTexKeySet(NNSGfdPlttKey pltt_key)
{
	int i;
	PTC_PTR psys;
	
	GF_ASSERT(pltt_key != NNS_GFD_ALLOC_ERROR_PLTTKEY);
	GF_ASSERT(TexLoadTempPtc != NULL);
	
	psys = TexLoadTempPtc;
	
	for(i = 0; i < LNK_PLTT_KEY_MAX; i++){
		if(psys->pltt_key[i] == NNS_GFD_ALLOC_ERROR_PLTTKEY){
			psys->pltt_key[i] = pltt_key;
			return;
		}
	}
	GF_ASSERT(0 && "�p�[�e�B�N���p���b�g�e�N�X�`���Ǘ����𒴂��Ă��܂�!\n");
}

#ifdef PM_DEBUG		//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//--------------------------------------------------------------
/**
 * @brief   �L�[���͂ɂ���ăJ�����̈ʒu���ړ�����(�f�o�b�O�@�\)
 * @param   psys		�p�[�e�B�N���V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void DebugCameraMove(PTC_PTR psys)
{
	const fx32 a = FX32_ONE / 0x10;
	int flag = 0;
	
	if((sys.trg & PAD_BUTTON_START) && (sys.cont & PAD_BUTTON_R) && (sys.cont & PAD_BUTTON_L)){
		WeDebugWork.eye = DefaultEye;
		WeDebugWork.up = DefaultUp;
		WeDebugWork.at = DefaultAt;
		OS_Printf("DebugCamera:�W���ݒ�ɖ߂��܂���\n");
		return;
	}
	
	if(sys.cont & PAD_BUTTON_R){
		if(sys.cont & PAD_KEY_LEFT){
			WeDebugWork.up.x -= a;
		}
		else if(sys.cont & PAD_KEY_RIGHT){
			WeDebugWork.up.x += a;
		}
		else if(sys.cont & PAD_KEY_UP){
			WeDebugWork.up.y -= a;
		}
		else if(sys.cont & PAD_KEY_DOWN){
			WeDebugWork.up.y += a;
		}
		else if(sys.cont & PAD_BUTTON_X){
			WeDebugWork.up.z -= a;
		}
		else if(sys.cont & PAD_BUTTON_B){
			WeDebugWork.up.z += a;
		}
		else{
			flag++;
		}
		if(flag == 0){
			OS_Printf("v_up: x = %#xd, y = %#xd, z = %#xd\n", WeDebugWork.up.x, WeDebugWork.up.y, WeDebugWork.up.z);
		}
	}
	else if(sys.cont & PAD_BUTTON_L){
		if(sys.cont & PAD_KEY_LEFT){
			WeDebugWork.at.x -= a;
		}
		else if(sys.cont & PAD_KEY_RIGHT){
			WeDebugWork.at.x += a;
		}
		else if(sys.cont & PAD_KEY_UP){
			WeDebugWork.at.y -= a;
		}
		else if(sys.cont & PAD_KEY_DOWN){
			WeDebugWork.at.y += a;
		}
		else if(sys.cont & PAD_BUTTON_X){
			WeDebugWork.at.z -= a;
		}
		else if(sys.cont & PAD_BUTTON_B){
			WeDebugWork.at.z += a;
		}
		else{
			flag++;
		}
		if(flag == 0){
			OS_Printf("at: x = %#xd, y = %#xd, z = %#xd\n", WeDebugWork.at.x, WeDebugWork.at.y, WeDebugWork.at.z);
		}
	}
	else{
		if(sys.cont & PAD_KEY_LEFT){
			WeDebugWork.eye.x -= a;
		}
		else if(sys.cont & PAD_KEY_RIGHT){
			WeDebugWork.eye.x += a;
		}
		else if(sys.cont & PAD_KEY_UP){
			WeDebugWork.eye.y -= a;
		}
		else if(sys.cont & PAD_KEY_DOWN){
			WeDebugWork.eye.y += a;
		}
		else if(sys.cont & PAD_BUTTON_X){
			WeDebugWork.eye.z -= a;
		}
		else if(sys.cont & PAD_BUTTON_B){
			WeDebugWork.eye.z += a;
		}
		else{
			flag++;
		}
		if(flag == 0){
			OS_Printf("eye: x = %#xd, y = %#xd, z = %#xd\n", WeDebugWork.eye.x, WeDebugWork.eye.y, WeDebugWork.eye.z);
		}
	}
}
#endif		//+++++++++++++++++++++++++ PM_DEBUG ++++++++++++++++++++++++++++++++++++++

//--------------------------------------------------------------
/**
 * @brief	�`��
 */
//--------------------------------------------------------------
void Particle_Draw(PTC_PTR psys)
{
	const MtxFx43 *camera_ptr;

#ifdef PM_DEBUG
	if((sys.cont & PAD_BUTTON_SELECT) && (sys.trg & PAD_BUTTON_START)){
		WeDebugWork.debug_flag ^= WE_DEBUG_BIT_CAMERA;
		if(WeDebugWork.debug_flag & WE_DEBUG_BIT_CAMERA){
			WeDebugWork.eye = DefaultEye;
			WeDebugWork.up = DefaultUp;
			WeDebugWork.at = DefaultAt;
		}
		OS_Printf("�f�o�b�O�J�����ړ� = %d\n", WeDebugWork.debug_flag & WE_DEBUG_BIT_CAMERA);
	}
	if(WeDebugWork.debug_flag & WE_DEBUG_BIT_CAMERA){
		DebugCameraMove(psys);
		psys->eye = WeDebugWork.eye;
		psys->v_up = WeDebugWork.up;
		psys->at = WeDebugWork.at;
	}
#endif

	if(psys->camera != NULL){
		GFC_SetCameraView(psys->camera_type, psys->camera);
		GFC_AttachCamera(psys->camera);
		GFC_CameraLookAt();
	}
	
	//�O���[�o���X�e�[�g��K�p
	NNS_G3dGlbFlush();

	// �p�[�e�B�N���`��
	camera_ptr = NNS_G3dGlbGetCameraMtx();
	SPL_Draw(psys->spl_manager, camera_ptr);

	if(psys->camera != NULL){
		GFC_PurgeCamera();
	}

	//�ĂуO���[�o���X�e�[�g��K�p�B�T���v����Simple����������Ă��Ő^���B
	NNS_G3dGlbFlush();
}

//--------------------------------------------------------------
/**
 * @brief	�v�Z
 */
//--------------------------------------------------------------
void Particle_Calc(PTC_PTR psys)
{
	SPL_Calc(psys->spl_manager);
}

//--------------------------------------------------------------
/**
 * @brief   ���ۂɓ��삵�Ă���p�[�e�B�N���}�l�[�W���̐����擾����
 * @retval  ���s����Ă���}�l�[�W����
 */
//--------------------------------------------------------------
int Particle_GetActionNum(void)
{
	int i, count;
	
	count = 0;
	for(i = 0; i < PARTICLE_GLOBAL_MAX; i++){
		if(ParticleSystemPtr[i] != NULL){
			count++;
		}
	}
	return count;
}

//--------------------------------------------------------------
/**
 * @brief   ��������Ă���p�[�e�B�N���V�X�e���S�Ă̕`����s��
 * @retval  �`�悪�s��ꂽ��
 */
//--------------------------------------------------------------
int Particle_DrawAll(void)
{
	int i, count;
	
	count = 0;
	for(i = 0; i < PARTICLE_GLOBAL_MAX; i++){
		if(ParticleSystemPtr[i] != NULL){
			Particle_Draw(ParticleSystemPtr[i]);
			count++;
		}
	}
	return count;
}

//--------------------------------------------------------------
/**
 * @brief   ��������Ă���p�[�e�B�N���V�X�e���S�Ă̌v�Z���s��
 * @retval  �v�Z���s��ꂽ��
 */
//--------------------------------------------------------------
int Particle_CalcAll(void)
{
	int i, count;
	
	count = 0;
	for(i = 0; i < PARTICLE_GLOBAL_MAX; i++){
		if(ParticleSystemPtr[i] != NULL){
			Particle_Calc(ParticleSystemPtr[i]);
			count++;
		}
	}
	return count;
}

//--------------------------------------------------------------
/**
 * @brief   �G�~�b�^�𐶐�
 *
 * @param   psys			�p�[�e�B�N���V�X�e�����[�N�ւ̃|�C���^
 * @param   res_no			���\�[�X�ԍ�
 * @param   init_pos		�ʒu(���\�[�X�ɐݒ肳�ꂽ�G�~�b�^�I�t�Z�b�g�ʒu�ɉ��Z���܂�)
 *
 * @retval  �������ꂽ�G�~�b�^�ւ̃|�C���^�B���ŃG�~�b�^�̏ꍇ��NULL���Ԃ�܂�
 */
//--------------------------------------------------------------
EMIT_PTR Particle_CreateEmitter(PTC_PTR psys, int res_no, const VecFx32 *init_pos)
{
	EMIT_PTR emit;
	
	emit = SPL_Create(psys->spl_manager, res_no, init_pos);
	psys->temp_emit = emit;
#if 0
	if(emit != NULL){
		SPL_Terminate(emit);
	}
#endif
	return emit;
}

//--------------------------------------------------------------
/**
 * @brief   �G�~�b�^�𐶐�(������������callback�ɓo�^�����֐������s����܂�)
 *
 * @param   psys			�p�[�e�B�N���V�X�e�����[�N�ւ̃|�C���^
 * @param   res_no			���\�[�X�ԍ�
 * @param   callback		�G�~�b�^�������ɌĂяo�����R�[���o�b�N�֐��ւ̃|�C���^
 * @param   temp_ptr		�R�[���o�b�N�֐��̒���Particle_GetTempPtr�֐����g�����ŁA
 *                          �����œn�����|�C���^���擾���鎖���o���܂��B
 *                          Particle_GetTempPtr�֐����g����̂̓R�[���o�b�N�֐����݂̂ł��B
 *
 * @retval  �������ꂽ�G�~�b�^�ւ̃|�C���^�B���ŃG�~�b�^�̏ꍇ��NULL���Ԃ�܂�
 *
 * ���ŃG�~�b�^��SPL_Create�ō쐬�����ꍇ�ANULL���������Ă���̂ŃG�~�b�^�̐ݒ���v���O��������
 * �ύX���邱�Ƃ͂ł��܂���B���̊֐�����������SPLEmitter*�������Ƃ���R�[���o�b�N��o�^����
 * ���ƂŁA���őO�̎��ŃG�~�b�^�ւ̃|�C���^�������Ƃ��ăR�[���o�b�N�֐����Ăяo����܂��B
 * ���̃R�[���o�b�N�֐����ŃG�~�b�^�̐ݒ��ύX���邱�Ƃ��\�ł��B 
 */
//--------------------------------------------------------------
EMIT_PTR Particle_CreateEmitterCallback(PTC_PTR psys, int res_no, pEmitFunc callback, void *temp_ptr)
{
	EMIT_PTR emit;
	
	ParticleTempPtr = temp_ptr;
	emit = SPL_CreateWithInitialize(psys->spl_manager, res_no, callback);
	ParticleTempPtr = NULL;
	psys->temp_emit = emit;

	return emit;
}

//--------------------------------------------------------------
/**
 * @brief   �A�N�e�B�u�ȃG�~�b�^�̐����擾���܂�
 *
 * @param   psys		�p�[�e�B�N���V�X�e�����[�N�ւ̃|�C���^
 *
 * @retval  �A�N�e�B�u�ȃG�~�b�^��
 */
//--------------------------------------------------------------
s32 Particle_GetEmitterNum(PTC_PTR psys)
{
	return SPL_GetEmitterNum(psys->spl_manager);
}

//--------------------------------------------------------------
/**
 * @brief   �p�[�e�B�N���V�X�e�����[�N���Ǘ����Ă���p�[�e�B�N����S�č폜
 * @param   psys		�p�[�e�B�N���V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
void Particle_EmitterDeleteAll(PTC_PTR psys)
{
	SPL_DeleteAll(psys->spl_manager);	//�p�[�e�B�N���S�폜
}

//--------------------------------------------------------------
/**
 * @brief	emitter1�폜
 *
 * @param	psys	
 * @param	emit	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
void Particle_EmitterDelete(PTC_PTR psys, EMIT_PTR emit)
{
	SPL_Delete(psys->spl_manager, emit);	//�p�[�e�B�N���S�폜
}


//--------------------------------------------------------------
/**
 * @brief   �Ō�ɐ��������G�~�b�^�̃|�C���^���擾����
 *
 * @param   psys		�p�[�e�B�N���V�X�e�����[�N�ւ̃|�C���^
 *
 * @retval  �Ō�ɐ��������G�~�b�^�̃|�C���^
 */
//--------------------------------------------------------------
EMIT_PTR Particle_TempEmitterPtrGet(PTC_PTR psys)
{
	return psys->temp_emit;
}

//--------------------------------------------------------------
/**
 * @brief   �p�[�e�B�N���V�X�e�����[�N�ɐݒ肳��Ă���q�[�v�̈�̐擪�A�h���X���擾
 *
 * @param   psys		�p�[�e�B�N���V�X�e�����[�N�ւ̃|�C���^
 *
 * @retval  �q�[�v�̐擪�A�h���X(Particle_SystemCreate�œn�����A�h���X���Ԃ�܂�)
 */
//--------------------------------------------------------------
void * Particle_HeapPtrGet(PTC_PTR psys)
{
	return psys->heap_start;
}

//--------------------------------------------------------------
/**
 * @brief   �J�����̈ʒu�x�N�g�����擾
 * @param   ptc		�p�[�e�B�N���V�X�e�����[�N�ւ̃|�C���^
 * @param   eye		�l�����
 */
//--------------------------------------------------------------
void Particle_GetEye(PTC_PTR psys, VecFx32 *eye)
{
	*eye = psys->eye;
}

//--------------------------------------------------------------
/**
 * @brief   �J�����̈ʒu�x�N�g�����Z�b�g
 * @param   ptc		�p�[�e�B�N���V�X�e�����[�N�ւ̃|�C���^
 * @param   eye		�l�����
 *
 * GFLib�̃J�������g�p���Ă���ꍇ�͂���͋@�\���܂���
 */
//--------------------------------------------------------------
void Particle_SetEye(PTC_PTR psys, const VecFx32 *eye)
{
	psys->eye = *eye;
}

//--------------------------------------------------------------
/**
 * @brief   �J�����̏�����x�N�g�����擾
 * @param   ptc		�p�[�e�B�N���V�X�e�����[�N�ւ̃|�C���^
 * @param   v_up		�l�����
 */
//--------------------------------------------------------------
void Particle_GetVup(PTC_PTR psys, VecFx32 *v_up)
{
	*v_up = psys->v_up;
}

//--------------------------------------------------------------
/**
 * @brief   �J�����̏�����x�N�g�����Z�b�g
 * @param   ptc		�p�[�e�B�N���V�X�e�����[�N�ւ̃|�C���^
 * @param   v_up		�l�����
 */
//--------------------------------------------------------------
void Particle_SetVup(PTC_PTR psys, const VecFx32 *v_up)
{
	psys->v_up = *v_up;
	GFC_SetCamUp(v_up, psys->camera);
}

//--------------------------------------------------------------
/**
 * @brief   �e���|�������[�N�ɃZ�b�g����Ă���|�C���^���擾����
 * @retval  �e���|�������[�N�ɃZ�b�g����Ă���|�C���^
 *
 * �G�~�b�^�쐬���̃R�[���o�b�N�֐����ł̂ݎg�p�\�ł��B
 */
//--------------------------------------------------------------
void * Particle_GetTempPtr(void)
{
	SDK_ASSERT(ParticleTempPtr != NULL);
	return ParticleTempPtr;
}

//--------------------------------------------------------------
/**
 * @brief   �f�t�H���g�J�����ʒu�x�N�g�����擾
 * @param   eye		�l�����
 */
//--------------------------------------------------------------
void Particle_GetDefaultEye(VecFx32 *eye)
{
	*eye = DefaultEye;
}

//--------------------------------------------------------------
/**
 * @brief   �f�t�H���g�J�����̏�����x�N�g�����擾
 * @param   eye		�l�����
 */
//--------------------------------------------------------------
void Particle_GetDefaultUp(VecFx32 *v_up)
{
	*v_up = DefaultUp;
}

//--------------------------------------------------------------
/**
 * @brief   �f�t�H���g�J�����̏œ_�ւ̃x�N�g�����擾
 * @param   eye		�l�����
 */
//--------------------------------------------------------------
void Particle_GetDefaultAt(VecFx32 *at)
{
	*at = DefaultAt;
}

//--------------------------------------------------------------
/**
 * @brief   �p�[�e�B�N���V�X�e���������Ă���J�����̃|�C���^���擾���܂�
 * @param   ptc		�p�[�e�B�N���V�X�e�����[�N�ւ̃|�C���^
 * @retval  GF�J�����ւ̃|�C���^(�Ǝ��̃J�������g�p���Ă��Ȃ��ꍇ��NULL)
 */
//--------------------------------------------------------------
GF_CAMERA_PTR Particle_GetCameraPtr(PTC_PTR ptc)
{
	return ptc->camera;
}

//--------------------------------------------------------------
/**
 * @brief   �p�[�e�B�N���V�X�e���̃J�����ˉe�������Z�b�g����
 * @param   ptc				�p�[�e�B�N���V�X�e�����[�N�ւ̃|�C���^
 * @param   camera_type		GF_CAMERA_PERSPECTIV or GF_CAMERA_ORTHO
 */
//--------------------------------------------------------------
void Particle_CameraTypeSet(PTC_PTR ptc, int camera_type)
{
	ptc->camera_type = camera_type;
}

//--------------------------------------------------------------
/**
 * @brief   �p�[�e�B�N���V�X�e���̃J�����ˉe�������擾����
 * @param   ptc		�p�[�e�B�N���V�X�e�����[�N�ւ̃|�C���^
 * @retval  GF_CAMERA_PERSPECTIV or GF_CAMERA_ORTHO
 */
//--------------------------------------------------------------
u8 Particle_CameraTypeGet(PTC_PTR ptc)
{
	return ptc->camera_type;
}

//--------------------------------------------------------------
/**
 * @brief   �G�~�b�^�̑��x���擾���܂�
 *
 * @param   emit	�G�~�b�^�ւ̃|�C���^
 * @param   vel		�l�����
 */
//--------------------------------------------------------------
void SplSub_GetEmitterVelocity(EMIT_PTR emit, VecFx32 *vel)
{
	*vel = emit->emtr_vel;
}

//--------------------------------------------------------------
/**
 * @brief   �G�~�b�^�̑��x���Z�b�g���܂�
 *
 * @param   emit	�G�~�b�^�ւ̃|�C���^
 * @param   vel		�Z�b�g����l
 */
//--------------------------------------------------------------
void SplSub_SetEmitterVelocity(EMIT_PTR emit, const VecFx32 *vel)
{
	SPL_SetEmitterVelocity(emit, vel);
}

//--------------------------------------------------------------
/**
 * @brief   �G�~�b�^�̌������擾
 * @param   emit		�G�~�b�^�ւ̃|�C���^
 * @param   vec			�l�����
 */
//--------------------------------------------------------------
void SplSub_GetEmitterAxis(EMIT_PTR emit, VecFx16 *vec)
{
	*vec = emit->axis;
}

//--------------------------------------------------------------
/**
 * @brief   �G�~�b�^�̑傫�����擾
 * @param   emit		�G�~�b�^�ւ̃|�C���^
 * @retval  �傫��
 */
//--------------------------------------------------------------
fx32 SplSub_GetEmitterRadius(EMIT_PTR emit)
{
	return emit->radius;
}

//--------------------------------------------------------------
/**
 * @brief   �G�~�b�^�̑S�����������擾
 * @param   emit		�G�~�b�^�ւ̃|�C���^
 * @retval  �S��������
 */
//--------------------------------------------------------------
fx16 SplSub_GetEmitterInitVelocityPos(EMIT_PTR emit)
{
	return emit->init_vel_mag_pos;
}

//--------------------------------------------------------------
/**
 * @brief   �G�~�b�^�̎������������擾
 * @param   emit		�G�~�b�^�ւ̃|�C���^
 * @retval  ����������
 */
//--------------------------------------------------------------
fx16 SplSub_GetEmitterInitVelocityAxis(EMIT_PTR emit)
{
	return emit->init_vel_mag_axis;
}

//--------------------------------------------------------------
/**
 * @brief   �G�~�b�^�̊�{�X�P�[�����擾
 * @param   emit		�G�~�b�^�ւ̃|�C���^
 * @retval  ��{�X�P�[��
 */
//--------------------------------------------------------------
fx16 SplSub_GetEmitterBaseScale(EMIT_PTR emit)
{
	return emit->base_scl;
}

//--------------------------------------------------------------
/**
 * @brief   �G�~�b�^�̐����Ԋu���擾
 * @param   emit		�G�~�b�^�ւ̃|�C���^
 * @retval  �����Ԋu
 */
//--------------------------------------------------------------
u16 SplSub_GetEmitterEmissionInterval(EMIT_PTR emit)
{
	return emit->etc.gen_intvl;
}

//--------------------------------------------------------------
/**
 * @brief   �G�~�b�^�̊�{�����擾
 * @param   emit		�G�~�b�^�ւ̃|�C���^
 * @retval  ��{��
 */
//--------------------------------------------------------------
u16 SplSub_GetEmitterBaseAlpha(EMIT_PTR emit)
{
	return emit->etc.base_alp;
}

//--------------------------------------------------------------
/**
 * @brief   �G�~�b�^�̃O���[�o���F���擾
 * @param   emit		�G�~�b�^�ւ̃|�C���^
 * @retval  �O���[�o���F
 */
//--------------------------------------------------------------
GXRgb SplSub_GetEmitterGlobalColor(EMIT_PTR emit)
{
	return emit->clr;
}

//--------------------------------------------------------------
/**
 * @brief   �w�肵���G�~�b�^�̕��o���[�g��ݒ肵�܂�
 *
 * @param   emit		�G�~�b�^�ւ̃|�C���^
 * @param   gen_num		�ݒ���o���[�g
 *
 * SPL_SetEmitterGenerationRatio�֐����Ȃ��悤�Ȃ̂ő���
 */
//--------------------------------------------------------------
void SplSub_SetEmitterGenerationRatio(EMIT_PTR emit, fx32 gen_num)
{
	emit->p_res->p_base->gen_num = gen_num;
}

//--------------------------------------------------------------
/**
 * @brief   ���o���[�g���擾���܂�
 * @param   emit		�G�~�b�^�ւ̃|�C���^
 * @retval  ���o���[�g
 */
//--------------------------------------------------------------
fx32 SplSub_GetEmitterGenerationRatio(EMIT_PTR emit)
{
	return emit->p_res->p_base->gen_num;
}

//--------------------------------------------------------------
/**
 * @brief   �G�~�b�^�̌��݈ʒu���擾����
 *
 * @param   p_emtr		�G�~�b�^�ւ̃|�C���^
 * @param   p_pos		�擾���W�����
 */
//--------------------------------------------------------------
void SplSub_GetEmitterPosition(EMIT_PTR emit, VecFx32 * p_pos)
{
	*p_pos = emit->emtr_pos;
}

//--------------------------------------------------------------
/**
 * @brief   �G�~�b�^�̃f�t�H���g�ʒu���擾����
 *
 * @param   emit		�G�~�b�^�ւ̃|�C���^
 * @param   p_pos		�擾���W�����
 */
//--------------------------------------------------------------
void SplSub_GetEmitterBasePosition(EMIT_PTR emit, VecFx32 * p_pos)
{
	*p_pos = emit->p_res->p_base->pos;
}


// ----------------------------------------------------------------------------
//
//
//
//
//
//	�� Field ����n�̓Ǝ��֐��S
//		�p�[�e�B�N�����C�u��������private�ň�����ϐ���
//		�O���爵���Ă���̂ŕs������邩������Ȃ�
//
//
//
//
// ----------------------------------------------------------------------------
#if 0

typedef struct SPLGravity{				// �d�̓t�B�[���h
    VecFx16 mag;
    u16 reserved0;
} SPLGravity;

typedef struct SPLRandom{				// �����_���t�B�[���h
    VecFx16 mag;
    u16 intvl;
} SPLRandom;

typedef struct SPLMagnet{				// �}�O�l�b�g�t�B�[���h
    VecFx32 pos;
    fx16    mag;
    u16     reserved0;
} SPLMagnet;

typedef struct SPLSpin{					// �X�s���t�B�[���h
    u16 radian;
    u16 axis_type;
} SPLSpin;

typedef struct SPLSimpleCollisionField{	// �V���v���R���W�����t�B�[���h
    fx32 y ; // �C�x���g���N����y���ʂ̒l
    fx16 coeff_bounce ;
    
    struct {
        u16 eventtype:2 ;
        u16 global:1 ;
        u16 reserved:13 ;
    } etc ;
} SPLSimpleCollisionField ;

typedef struct SPLConvergence{			// �ʒu�ɉ��Z�t�B�[���h�i�}�O�l�b�g�̈���j
    VecFx32 pos  ; // �z���񂹂���ꏊ
    fx16    ratio; // �z���񂹂��鋭��
    u16     reserved0;
} SPLConvergence ;

void spl_calc_gravity(const void* p_obj, SPLParticle* p_ptcl, VecFx32* p_acc, struct SPLEmitter* p_emtr );
void spl_calc_random(const void* p_obj, SPLParticle* p_ptcl, VecFx32* p_acc, struct SPLEmitter* p_emtr );
void spl_calc_magnet(const void* p_obj, SPLParticle* p_ptcl, VecFx32* p_acc, struct SPLEmitter* p_emtr );
void spl_calc_spin(const void* p_obj, SPLParticle* p_ptcl, VecFx32* p_acc, struct SPLEmitter* p_emtr );
void spl_calc_scfield(const void* p_obj, SPLParticle* p_ptcl, VecFx32* p_acc, struct SPLEmitter* p_emtr );
void spl_calc_convergence(const void* p_obj, SPLParticle* p_ptcl, VecFx32* p_acc, struct SPLEmitter* p_emtr );

#endif

enum {
	SPL_FLD_TYPE_GRAVITY = 0,		///< �d��
	SPL_FLD_TYPE_RANDOM,			///< �����_��
	SPL_FLD_TYPE_MAGNET,			///< �}�O�l�b�g
	SPL_FLD_TYPE_SPIN,				///< �X�s��
	SPL_FLD_TYPE_SIMPLE_COLL,		///< �V���v���R���W����
	SPL_FLD_TYPE_CONVERGENCE,		///< �R���o�[�W�F���X
};


//--------------------------------------------------------------
/**
 * @brief	SPL_FieldObject �̃|�C���^�擾
 *
 * @param	emit					�G�~�b�^�[
 * @param	field_type				�擾�t�B�[���h�̃^�C�v
 *
 * @retval	static const void*		�|�C���^
 *
 */
//--------------------------------------------------------------
static const void* SPLFieldObj_PointerSearch(EMIT_PTR emit, int field_type)
{
	int i;
	int num;
	SPLField* p_field;
	
	num = emit->p_res->fld_num;
	
	if (num == 0){
		return NULL;
	}
	
	for (i = 0; i < num; i++){
		
		p_field = &emit->p_res->fld_ary[i];
		
		if (p_field == NULL){ continue; }
		
		switch(field_type){
		case SPL_FLD_TYPE_GRAVITY:
			if (p_field->p_exec == spl_calc_gravity){
				return p_field->p_obj;
			}
			continue;
		case SPL_FLD_TYPE_RANDOM:
			if (p_field->p_exec == spl_calc_random){
				return p_field->p_obj;
			}
			continue;
		case SPL_FLD_TYPE_MAGNET:
			if (p_field->p_exec == spl_calc_magnet){
				return p_field->p_obj;
			}
			continue;
		case SPL_FLD_TYPE_SPIN:
			if (p_field->p_exec == spl_calc_spin){
				return p_field->p_obj;
			}
			continue;
		case SPL_FLD_TYPE_SIMPLE_COLL:
			if (p_field->p_exec == spl_calc_scfield){
				return p_field->p_obj;
			}
			break;
		case SPL_FLD_TYPE_CONVERGENCE:
			if (p_field->p_exec == spl_calc_convergence){
				return p_field->p_obj;
			}
			continue;
		default:
			return NULL;
		}		
	}
	
	return NULL;
}

// -----------------------------------------
//
//	�d��
//
//--------------------------------------------------------------
///< �d�͂̍��W����
void SplSub_SetSPLField_GravityPos(EMIT_PTR emit, VecFx16 *mag)
{
	SPLGravity* p_obj;
	
	p_obj = (SPLGravity*)SPLFieldObj_PointerSearch(emit, SPL_FLD_TYPE_GRAVITY);
	
	if (p_obj == NULL){ return; }
	
	p_obj->mag = *mag;
}

void SplSub_GetSPLField_GravityPos(EMIT_PTR emit, VecFx16 *mag)
{
	SPLGravity* p_obj;
	
	p_obj = (SPLGravity*)SPLFieldObj_PointerSearch(emit, SPL_FLD_TYPE_GRAVITY);
	
	if (p_obj == NULL){
		VecFx16 err_p = { 0,0,0 };
		*mag = err_p;
		return;
	}
			
	*mag = p_obj->mag;
}


// -----------------------------------------
//
//	�����_��
//
// -----------------------------------------
///< �g���K�v�����邩�s���Ȃ̂łƂ肠����������
void SplSub_SetSPLField_RandomMag(EMIT_PTR emit, VecFx16* mag)
{
}
void SplSub_GetSPLField_RandomMag(EMIT_PTR emit, VecFx16* mag)
{
}
void SplSub_SetSPLField_RandomIntvl(EMIT_PTR emit, u16* mag)
{
}
void SplSub_GetSPLField_RandomIntvl(EMIT_PTR emit, u16* mag)
{
}

// -----------------------------------------
//
// �}�O�l�b�g
//
// -----------------------------------------
///< �}�O�l�b�g�̍��W����
void SplSub_SetSPLField_MagnetPos(EMIT_PTR emit, VecFx32* p_pos)
{
	SPLMagnet* p_obj;
	
	p_obj = (SPLMagnet*)SPLFieldObj_PointerSearch(emit, SPL_FLD_TYPE_MAGNET);
	
	if (p_obj == NULL){ return; }
			
	p_obj->pos = *p_pos;
}

void SplSub_GetSPLField_MagnetPos(EMIT_PTR emit, VecFx32* p_pos)
{
	SPLMagnet* p_obj;
	
	p_obj = (SPLMagnet*)SPLFieldObj_PointerSearch(emit, SPL_FLD_TYPE_MAGNET);
	
	if (p_obj == NULL){
		VecFx32 err_p = { 0,0,0 };
		*p_pos = err_p;
		return;
	}
	
	*p_pos = p_obj->pos;
}

///< �}�O�l�b�g�̃}�O����
void SplSub_SetSPLField_MagnetMag(EMIT_PTR emit, fx16* mag)
{
	SPLMagnet* p_obj;
	
	p_obj = (SPLMagnet*)SPLFieldObj_PointerSearch(emit, SPL_FLD_TYPE_MAGNET);
	
	if (p_obj == NULL){ return; }
			
	p_obj->mag = *mag;
}

void SplSub_GetSPLField_MagnetMag(EMIT_PTR emit, fx16* mag)
{
	SPLMagnet* p_obj;
	
	p_obj = (SPLMagnet*)SPLFieldObj_PointerSearch(emit, SPL_FLD_TYPE_MAGNET);
	
	if (p_obj == NULL){
		*mag = 0;
		return;
	}

	*mag = p_obj->mag;
}


// -----------------------------------------
//
//	�X�s��
//
// -----------------------------------------
///< �X�s���̊p�x����
void SplSub_SetSPLField_SpinRad(EMIT_PTR emit, u16* rad)
{
	SPLSpin* p_obj;
	
	p_obj = (SPLSpin*)SPLFieldObj_PointerSearch(emit, SPL_FLD_TYPE_SPIN);
	
	if (p_obj == NULL){ return; }
	
	p_obj->radian = *rad;
}

void SplSub_GetSPLField_SpinRad(EMIT_PTR emit, u16* rad)
{
	SPLSpin* p_obj;
	
	p_obj = (SPLSpin*)SPLFieldObj_PointerSearch(emit, SPL_FLD_TYPE_SPIN);
	
	if (p_obj == NULL){
		*rad = 0;
		return;
	}
	
	*rad = p_obj->radian;
}

///< �X�s���̕����^�C�v����
void SplSub_SetSPLField_SpinAxisType(EMIT_PTR emit, u16* axis_type)
{
	SPLSpin* p_obj;
	
	p_obj = (SPLSpin*)SPLFieldObj_PointerSearch(emit, SPL_FLD_TYPE_SPIN);
	
	if (p_obj == NULL){ return; }
	
	p_obj->axis_type = *axis_type;
}

void SplSub_GetSPLField_SpinAxisType(EMIT_PTR emit, u16* axis_type)
{
	SPLSpin* p_obj;
	
	p_obj = (SPLSpin*)SPLFieldObj_PointerSearch(emit, SPL_FLD_TYPE_SPIN);
	
	if (p_obj == NULL){
		*axis_type = 0;
		return;
	}
	
	*axis_type = p_obj->axis_type;
}

// -----------------------------------------
//
//	�V���v���R���W����
//
// -----------------------------------------
///< ���삷��K�v�����邩�s���Ȃ̂ŁA�Ƃ肠����������
void SplSub_SetSPLField_SimpleCollisionYPos(EMIT_PTR emit, fx32* y)
{
}
void SplSub_GetSPLField_SimpleCollisionYPos(EMIT_PTR emit, fx32* y)
{
}
void SplSub_SetSPLField_SimpleCollisionCoeffBounce(EMIT_PTR emit, fx16* coeff_bounce)
{
}
void SplSub_GetSPLField_SimpleCollisionCoeffBounce(EMIT_PTR emit, fx16* coeff_bounce)
{
}
void SplSub_SetSPLField_SimpleCollisionEventType(EMIT_PTR emit, u16* ev_type)
{
}
void SplSub_GetSPLField_SimpleCollisionEventType(EMIT_PTR emit, u16* ev_type)
{
}
void SplSub_SetSPLField_SimpleCollisionGlobal(EMIT_PTR emit, u16* global)
{
}
void SplSub_GetSPLField_SimpleCollisionGlobal(EMIT_PTR emit, u16* global)
{
}

// -----------------------------------------
//
//	�R���o�[�W�F���X
//
// -----------------------------------------
///< �R���o�[�W�F���X�̍��W����
void SplSub_SetSPLField_ConvergencePos(EMIT_PTR emit, VecFx32* p_pos)
{
	SPLConvergence* p_obj;
	
	p_obj = (SPLConvergence*)SPLFieldObj_PointerSearch(emit, SPL_FLD_TYPE_CONVERGENCE);
	
	if (p_obj == NULL){ return; }
	
	p_obj->pos = *p_pos;
}

void SplSub_GetSPLField_ConvergencePos(EMIT_PTR emit, VecFx32* p_pos)
{
	SPLConvergence* p_obj;
	
	p_obj = (SPLConvergence*)SPLFieldObj_PointerSearch(emit, SPL_FLD_TYPE_CONVERGENCE);
	
	if (p_obj == NULL){
		VecFx32 err_p = { 0,0,0 };
		*p_pos = err_p;
		return;
	}
	
	*p_pos = p_obj->pos;
}

///< �R���o�[�W�F���X�̋�������
void SplSub_SetSPLField_ConvergenceRatio(EMIT_PTR emit, fx16* ratio)
{
	SPLConvergence* p_obj;
	
	p_obj = (SPLConvergence*)SPLFieldObj_PointerSearch(emit, SPL_FLD_TYPE_CONVERGENCE);
	
	if (p_obj == NULL){ return; }
	
	p_obj->ratio = *ratio;
}

void SplSub_GetSPLField_ConvergenceRatio(EMIT_PTR emit, fx16* ratio)
{
	SPLConvergence* p_obj;
	
	p_obj = (SPLConvergence*)SPLFieldObj_PointerSearch(emit, SPL_FLD_TYPE_CONVERGENCE);
	
	if (p_obj == NULL){
		*ratio = 0;
		return;
	}
	
	*ratio = p_obj->ratio;
}
