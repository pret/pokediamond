//============================================================================================
/**
 * @file	op_poke_cutin.c
 * @brief	�I�[�v�j���O�|�P�����J�b�g�C��
 * @author	Nozomu Saito
 * @date	2006.06.03
 */
//============================================================================================
#include "common.h"
#include "system/softsprite.h"
#include "system/particle.h"
#include "system/arc_tool.h"
#include "poketool/poke_tool.h"
#include "poketool/monsno.h"

#include "op_poke_cutin.h"

#include "op_frame_def.h"

#include "particledata/particledata.h"
#include "particledata/particledata.naix"

#define MONS_MAX	(3)
///�퓬�p�[�e�B�N���̃J�����j�A�ݒ�
#define BP_NEAR			(FX32_ONE)
///�퓬�p�[�e�B�N���̃J�����t�@�[�ݒ�
#define BP_FAR			(FX32_ONE * 900)

#define OUT_WAIT	(20)

#define POKE_ZOOM	(0x400)
#define POKE_ZOOM_IN_SPD	(0x80)
#define POKE_ZOOM_OUT_SPD	(0x20)

typedef struct OPD_SSM_tag
{
	SOFT_SPRITE_MANAGER *SSMPtr;
	SOFT_SPRITE *SoftSprit[MONS_MAX];
	BOOL UseSSFlg;
	void *PtcHeap;
	PTC_PTR PtcPtr;
	u8 CutInSeq;		//�J�b�g�C���V�[�P���X
	u8 Counter;
}OPD_SSM;

//�O�̂̃|�P�����̏����ʒu
typedef struct P2D_POS_tag
{
	int X;
	int Y;
}P2D_POS;


static void ParticleMain(void);
static void ParticleCallBack(EMIT_PTR emit);

static const P2D_POS PokeStartPos[MONS_MAX] = 
{
	{128,192},		//�i�G�g��
	{256,192},		//�q�R�U��
	{80,192},		//�|�b�`���}
};

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
	u32 address;
	NNSGfdTexKey key;
	
	key = NNS_GfdAllocTexVram(size, is4x4comp, 0);

	Particle_LnkTexKeySet(key);		//�����N�h���X�g���g�p���Ă���̂ŃL�[�����Z�b�g
	
	GF_ASSERT(key != NNS_GFD_ALLOC_ERROR_TEXKEY);
	
	address = NNS_GfdGetTexKeyAddr(key);
	OS_TPrintf("op_vram=%d\n", address);
	return address;
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
	NNSGfdPlttKey key;
	u32 address;
	
	key = NNS_GfdAllocPlttVram(size, is4pltt, NNS_GFD_ALLOC_FROM_LOW);
	
	if(key == NNS_GFD_ALLOC_ERROR_PLTTKEY){
		GF_ASSERT(0 && "�p�[�e�B�N���Ńp���b�g�̊m�ۂ��o���܂���I\n");
	}
	
	Particle_PlttLnkTexKeySet(key);	//�����N�h���X�g���g�p���Ă���̂ŃL�[�����Z�b�g
	
	address = NNS_GfdGetPlttKeyAddr(key);
	OS_TPrintf("op_vram=%d\n", address);
	return address;
}

const int  OPD_Poke_GetSSMSize(void)
{
	return sizeof(OPD_SSM);
}

void OPD_Poke_Init(OPD_SSM_PTR opd_ssm_ptr)
{
	u8 i;
	SOFT_SPRITE_ARC ssa;
	GF_CAMERA_PTR camera_ptr;
	void *resource;

	int monsno[MONS_MAX] = {MONSNO_NAETORU,MONSNO_HIKOZARU, MONSNO_POTTYAMA};
	
	opd_ssm_ptr->SSMPtr = SoftSpriteInit(HEAPID_OP_DEMO);
	for(i=0;i<MONS_MAX;i++){
		//�Ō�̈����́AFormNo�ƌ�����	�i�����ł�NULL���w��j
		PokeGraArcDataGet( &ssa, monsno[i], PARA_MALE, PARA_FRONT, PARA_NORMAL, NULL, NULL );
		opd_ssm_ptr->SoftSprit[i] = SoftSpriteAdd(opd_ssm_ptr->SSMPtr, &ssa,
				PokeStartPos[i].X, PokeStartPos[i].Y, 1023, i, NULL, NULL);
		//��\��
		SoftSpriteParaSet(opd_ssm_ptr->SoftSprit[i],SS_PARA_VANISH,1);
	}
	//�q�R�U���͔��]
	SoftSpriteParaSet(opd_ssm_ptr->SoftSprit[CUT_IN_HIKOZARU],SS_PARA_H_FLIP,1);
	
	opd_ssm_ptr->UseSSFlg = 1;

	Particle_SystemWorkInit();	//�p�[�e�B�N���V�X�e��������

	//�p�[�e�B�N���������m��
	opd_ssm_ptr->PtcHeap = sys_AllocMemory(HEAPID_OP_DEMO, PARTICLE_LIB_HEAP_SIZE);
	opd_ssm_ptr->PtcPtr = Particle_SystemCreate(sAllocTex, sAllocTexPalette,
												opd_ssm_ptr->PtcHeap, 
												PARTICLE_LIB_HEAP_SIZE, TRUE, HEAPID_OP_DEMO);
	camera_ptr = Particle_GetCameraPtr(opd_ssm_ptr->PtcPtr);
	GFC_SetCameraClip(BP_NEAR, BP_FAR, camera_ptr);

	resource = Particle_ArcResourceLoad(
			ARC_PARTICLE_DATA, NARC_particledata_title_scene1_spa, HEAPID_OP_DEMO);
	Particle_ResourceSet(opd_ssm_ptr->PtcPtr, resource, PTC_AUTOTEX_LNK | PTC_AUTOPLTT_LNK, TRUE);
}

void OPD_Poke_End(OPD_SSM_PTR opd_ssm_ptr)
{
	//�p�[�e�B�N�����
	Particle_SystemExit(opd_ssm_ptr->PtcPtr);
	sys_FreeMemoryEz(opd_ssm_ptr->PtcHeap);
	//�X�v���C�g�I��
	SoftSpriteEnd(opd_ssm_ptr->SSMPtr);
}

void OPD_Poke_VBlank(OPD_SSM_PTR opd_ssm_ptr)
{
	if (opd_ssm_ptr != NULL){
		SoftSpriteTextureTrans(opd_ssm_ptr->SSMPtr);
	}
}

void OPD_Poke_Main(OPD_SSM_PTR opd_ssm_ptr)
{
	if (opd_ssm_ptr != NULL){
		GF_G3X_Reset();
		NNS_G2dSetupSoftwareSpriteCamera();
		SoftSpriteMain(opd_ssm_ptr->SSMPtr);
		ParticleMain();
		GF_G3_RequestSwapBuffers(GX_SORTMODE_MANUAL, GX_BUFFERMODE_Z);
	}
}


static BOOL InNAETORU(OPD_SSM_PTR opd_ssm_ptr, const u8 inMonster);
static BOOL OutNAETORU(OPD_SSM_PTR opd_ssm_ptr, const u8 inMonster);
static BOOL InHIKOZARU(OPD_SSM_PTR opd_ssm_ptr, const u8 inMonster);
static BOOL OutHIKOZARU(OPD_SSM_PTR opd_ssm_ptr, const u8 inMonster);
static BOOL InPOTTYAMA(OPD_SSM_PTR opd_ssm_ptr, const u8 inMonster);
static BOOL OutPOTTYAMA(OPD_SSM_PTR opd_ssm_ptr, const u8 inMonster);

typedef BOOL (*CUT_FUNC)(OPD_SSM_PTR opd_ssm_ptr, const u8 inMonster);

typedef struct CUT_FMC_TBL_tag{
	CUT_FUNC InFunc;
	CUT_FUNC OutFunc;
}CUT_FUNC_TBL;

static const CUT_FUNC_TBL	CutInTbl[MONS_MAX] = {
	{ InNAETORU, OutNAETORU },
	{ InHIKOZARU, OutHIKOZARU },
	{ InPOTTYAMA, OutPOTTYAMA },
};



static const int SkillEffect[MONS_MAX][2] = 
{
	{TITLE_SCENE1_OP_DEMOBG2_LEAF1, TITLE_SCENE1_OP_DEMOBG2_LEAF2},
	{TITLE_SCENE1_OP_DEMOBG2_FIRE1, TITLE_SCENE1_OP_DEMOBG2_FIRE2},
	{TITLE_SCENE1_OP_DEMOBG2_BUBBLE1, TITLE_SCENE1_OP_DEMOBG2_BUBBLE2}
};

static const int WaitCounter[MONS_MAX] = {
	FM_NAETORU_WAIT,
	FM_HIKOZARU_WAIT,
	FM_POTTYAMA_WAIT,
};

BOOL OPD_Poke_CutIn(OPD_SSM_PTR opd_ssm_ptr, const u8 inMonster, const int inCounter )
{
	u8 * seq = &opd_ssm_ptr->CutInSeq;
	switch(*seq){
	case 0:
		G2_SetWndOutsidePlane( GX_WND_PLANEMASK_BG0|GX_WND_PLANEMASK_OBJ, 1 );
		
		SoftSpriteParaSet(opd_ssm_ptr->SoftSprit[inMonster],SS_PARA_AFF_X,POKE_ZOOM);
		SoftSpriteParaSet(opd_ssm_ptr->SoftSprit[inMonster],SS_PARA_AFF_Y,POKE_ZOOM);
		//�X�v���C�g�\��
		SoftSpriteParaSet(opd_ssm_ptr->SoftSprit[inMonster],SS_PARA_VANISH,0);
		(*seq)++;	//<<break�u���Ȃ�
	case 1:	//�C��
		if ( CutInTbl[ inMonster ].InFunc(opd_ssm_ptr, inMonster) ){
			opd_ssm_ptr->Counter = 0;
			(*seq)++;
		}
		break;
	case 2:	//�p�[�e�B�N��
		Particle_CameraTypeSet(opd_ssm_ptr->PtcPtr, GF_CAMERA_ORTHO);

		Particle_CreateEmitterCallback(opd_ssm_ptr->PtcPtr, SkillEffect[inMonster][0],
										ParticleCallBack, opd_ssm_ptr->SoftSprit[inMonster]);
		Particle_CreateEmitterCallback(opd_ssm_ptr->PtcPtr, SkillEffect[inMonster][1],
										ParticleCallBack, opd_ssm_ptr->SoftSprit[inMonster]);
		(*seq)++;
		break;
	case 3:
		if(Particle_GetEmitterNum(opd_ssm_ptr->PtcPtr) == 0){
			if (inCounter >= WaitCounter[inMonster]){
				G2_SetWndOutsidePlane( GX_WND_PLANEMASK_OBJ, 1 );
				(*seq)++;
			}
		}
		break;
	case 4:	//�A�E�g
		if ( CutInTbl[ inMonster ].OutFunc(opd_ssm_ptr, inMonster) ){
			//�X�v���C�g��\��
			SoftSpriteParaSet(opd_ssm_ptr->SoftSprit[inMonster],SS_PARA_VANISH,1);
			opd_ssm_ptr->Counter = 0;
			(*seq)++;
		}
		break;
	case 5:
		//�ޔ������Ƃ̃E�F�C�g
		opd_ssm_ptr->Counter++;
		if (opd_ssm_ptr->Counter>=OUT_WAIT){
			opd_ssm_ptr->Counter = 0;
			(*seq) = 0;
			return TRUE;
		}
	}
	return FALSE;
}

//�i�G�g���C��
static BOOL InNAETORU(OPD_SSM_PTR opd_ssm_ptr, const u8 inMonster)
{
	SOFT_SPRITE *ss = opd_ssm_ptr->SoftSprit[inMonster];
	//6�t�������Ĉړ�
	SoftSpriteParaCalc(ss, SS_PARA_POS_X, 6);
	SoftSpriteParaCalc(ss, SS_PARA_POS_Y, -16);
	
	SoftSpriteParaCalc(ss,SS_PARA_AFF_X,-POKE_ZOOM_IN_SPD);
	SoftSpriteParaCalc(ss,SS_PARA_AFF_Y,-POKE_ZOOM_IN_SPD);
	
	opd_ssm_ptr->Counter++;
	if ( opd_ssm_ptr->Counter>=6 ){
		SoftSpriteParaSet(ss,SS_PARA_AFF_X,0x100);
		SoftSpriteParaSet(ss,SS_PARA_AFF_Y,0x100);
		return TRUE;
	}

	return FALSE;
}

//�i�G�g���A�E�g
static BOOL OutNAETORU(OPD_SSM_PTR opd_ssm_ptr, const u8 inMonster)
{
	SOFT_SPRITE *ss = opd_ssm_ptr->SoftSprit[inMonster];
	//6�t�������Ĉړ�
	SoftSpriteParaCalc(ss, SS_PARA_POS_X, -3);
	SoftSpriteParaCalc(ss, SS_PARA_POS_Y, -18);

///	SoftSpriteParaCalc(ss,SS_PARA_AFF_X,POKE_ZOOM_OUT_SPD);
///	SoftSpriteParaCalc(ss,SS_PARA_AFF_Y,POKE_ZOOM_OUT_SPD);
	
	opd_ssm_ptr->Counter++;
	if ( opd_ssm_ptr->Counter>=6 ){
		SoftSpriteParaSet(ss,SS_PARA_AFF_X,0x100);
		SoftSpriteParaSet(ss,SS_PARA_AFF_Y,0x100);
		return TRUE;
	}

	return FALSE;
}

//�q�R�U���C��
static BOOL InHIKOZARU(OPD_SSM_PTR opd_ssm_ptr, const u8 inMonster)
{
	SOFT_SPRITE *ss = opd_ssm_ptr->SoftSprit[inMonster];
	//6�t�������Ĉړ�
	SoftSpriteParaCalc(ss, SS_PARA_POS_X, -16);
	SoftSpriteParaCalc(ss, SS_PARA_POS_Y, -16);

	SoftSpriteParaCalc(ss,SS_PARA_AFF_X,-POKE_ZOOM_IN_SPD);
	SoftSpriteParaCalc(ss,SS_PARA_AFF_Y,-POKE_ZOOM_IN_SPD);
	
	opd_ssm_ptr->Counter++;
	if ( opd_ssm_ptr->Counter>=6 ){
		SoftSpriteParaSet(ss,SS_PARA_AFF_X,0x100);
		SoftSpriteParaSet(ss,SS_PARA_AFF_Y,0x100);
		return TRUE;
	}

	return FALSE;
}

//�q�R�U���A�E�g
static BOOL OutHIKOZARU(OPD_SSM_PTR opd_ssm_ptr, const u8 inMonster)
{
	SOFT_SPRITE *ss = opd_ssm_ptr->SoftSprit[inMonster];
	//6�t�������Ĉړ�
	SoftSpriteParaCalc(ss, SS_PARA_POS_X, -6);
	SoftSpriteParaCalc(ss, SS_PARA_POS_Y, -16);

///	SoftSpriteParaCalc(ss,SS_PARA_AFF_X,POKE_ZOOM_OUT_SPD);
///	SoftSpriteParaCalc(ss,SS_PARA_AFF_Y,POKE_ZOOM_OUT_SPD);
	
	opd_ssm_ptr->Counter++;
	if ( opd_ssm_ptr->Counter>=6 ){
		SoftSpriteParaSet(ss,SS_PARA_AFF_X,0x100);
		SoftSpriteParaSet(ss,SS_PARA_AFF_Y,0x100);
		return TRUE;
	}

	return FALSE;
}

//�|�b�`���}�C��
static BOOL InPOTTYAMA(OPD_SSM_PTR opd_ssm_ptr, const u8 inMonster)
{
	SOFT_SPRITE *ss = opd_ssm_ptr->SoftSprit[inMonster];
	//6�t�������Ĉړ�
	SoftSpriteParaCalc(ss, SS_PARA_POS_X, 8);
	SoftSpriteParaCalc(ss, SS_PARA_POS_Y, -16);

	SoftSpriteParaCalc(ss,SS_PARA_AFF_X,-POKE_ZOOM_IN_SPD);
	SoftSpriteParaCalc(ss,SS_PARA_AFF_Y,-POKE_ZOOM_IN_SPD);
	
	opd_ssm_ptr->Counter++;
	if ( opd_ssm_ptr->Counter>=6 ){
		SoftSpriteParaSet(ss,SS_PARA_AFF_X,0x100);
		SoftSpriteParaSet(ss,SS_PARA_AFF_Y,0x100);
		return TRUE;
	}

	return FALSE;
}

//�|�b�`���}�A�E�g
static BOOL OutPOTTYAMA(OPD_SSM_PTR opd_ssm_ptr, const u8 inMonster)
{
	SOFT_SPRITE *ss = opd_ssm_ptr->SoftSprit[inMonster];
	//6�t�������Ĉړ�
	SoftSpriteParaCalc(ss, SS_PARA_POS_X, 6);
	SoftSpriteParaCalc(ss, SS_PARA_POS_Y, -20);

///	SoftSpriteParaCalc(ss,SS_PARA_AFF_X,POKE_ZOOM_OUT_SPD);
///	SoftSpriteParaCalc(ss,SS_PARA_AFF_Y,POKE_ZOOM_OUT_SPD);
	
	opd_ssm_ptr->Counter++;
	if ( opd_ssm_ptr->Counter>=6 ){
		SoftSpriteParaSet(ss,SS_PARA_AFF_X,0x100);
		SoftSpriteParaSet(ss,SS_PARA_AFF_Y,0x100);
		return TRUE;
	}

	return FALSE;
}

//--------------------------------------------------------------
/**
 * @brief   �퓬�p�p�[�e�B�N���V�X�e���E���C���֐�(�v�Z�E�`�揈���Ȃǂ����s)
 *
 * @param   ptc		�p�[�e�B�N���V�X�e�����[�N�ւ̃|�C���^
 */
//--------------------------------------------------------------
static void ParticleMain(void)
{
	int draw_num;
	
	draw_num = Particle_DrawAll();	//�p�[�e�B�N���`��

	Particle_CalcAll();	//�p�[�e�B�N���v�Z
}

#define ONE_DOT	(172)	//��1�h�b�g
//--------------------------------------------------------------
/**
 * @brief	�R�[���o�b�N
 *
 * @param	emit	
 *
 * @retval	none	
 *
 */
//--------------------------------------------------------------
static void ParticleCallBack(EMIT_PTR emit)
{
	SOFT_SPRITE *ss = Particle_GetTempPtr();
	VecFx32 pos = { 0, 0, 0 };

	pos.x = ONE_DOT * ( SoftSpriteParaGet(ss, SS_PARA_POS_X)-128 );
	pos.y = ONE_DOT * ( SoftSpriteParaGet(ss, SS_PARA_POS_Y)-96 );
	pos.z = 0x40;
	SPL_SetEmitterPosition(emit, &pos);
}


