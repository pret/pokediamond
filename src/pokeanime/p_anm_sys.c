#include "pokeanime/p_anm_sys.h"
#include "system/softsprite.h"
#include "system/arc_tool.h"
#include "poketool/poke_tool.h"		//for PokePersonalParaGet
#include "tcb.h"

#include "past_def.h"


#define REQUEST_MAX	(256)
#define ANM_WORK_MAX	(8)
#define MOVE_FUNC_WORK_MAX	(8)
#define MOVE_FUNC_ENTRY_MAX	(4)

#define ANM_CMD_MAX	(34)

// ----------------------------------------
//
//	�w��T�C�Y���A�h���X��i�߂�}�N��
//		�i�߂�A�h���X�̌^�Ɉˑ�����
//
// -----------------------------------------
#define ADRS_CMD(n, m)			((n) += (m))

// -----------------------------------------
//
//	�^�T�C�Y���A�h���X��i�߂�}�N��
//		�ŏ��P�ʂŃA�h���X���i��
//		ADRS_CMD �𗘗p����̂Ō^�Ɉˑ�����
//
// -----------------------------------------
#define ADRS_SHIFT(n)			(ADRS_CMD(n, 1))

typedef int	TAP;
typedef struct POKE_ANIME_tag *POKE_ANM_PTR;
typedef struct MOVE_FUNC_DATA_tag *MOVE_FUNC_DATA_PTR;
typedef void (*pAnmFunc)( POKE_ANM_PTR );
typedef void (*MoveFunc)( MOVE_FUNC_DATA_PTR, POKE_ANM_PTR);

static TAP  GetAdrsParamEx(u32* adrs, u8 s_byte, u8 byte);	///< �f�[�^�擾
static TAP  GetAdrsParam(u32* adrs, u8 byte);					///< �f�[�^�擾
static TAP  GetSeqAdrs(u32* adrs);

typedef struct MOVE_FUNC_DATA_tag
{
	BOOL Valid;		//�֐��L���t���O
	int Work[MOVE_FUNC_WORK_MAX];	//���[�N
	int *Target;			//����֐��f�[�^���̕ύX�Ώی�
	int *ApplyTarget;		//�A�j���f�[�^���̕ύX�Ώې�
	
	u8	ApplyType;		//�l���Z�b�g���邩�A���̒l�ɒl����悹���邩�̃t���O

	u8	Wait;			//����֐����s�܂ł̃E�F�C�g
	int StartVal;		//APPLY_ADD���̊�ƂȂ�l
	int TransX;			//�w�ړ��l
	int TransY;			//�x�ړ��l
	int dx;				//�w�ړ��l�i�I�t�Z�b�g�j
	int dy;				//�x�ړ��l�i�I�t�Z�b�g�j
	int rx;				//�g�k�w
	int ry;				//�g�k�x
	int Rot;			//��]
	MoveFunc	Func;	//����֐�
}MOVE_FUNC_DATA;

typedef struct POKE_ANIME_tag
{
	SOFT_SPRITE *SoftSprite;	//�\�t�g�E�F�A�X�v���C�g�ւ̃|�C���^
	TCB_PTR Task;		//�o�^�^�X�N�i�A�j�����f������p�j
	void *ArcData;		//�A�[�J�C�u�f�[�^
	u32 *SeqAdrs;		//�f�[�^�V�[�P���X�A�h���X

	BOOL Valid;			//�f�[�^�L���t���O
//	int MonsNo;	//�����X�^�[�i���o�[	�i����Ȃ������j
	int AnimeNo;	//�A�j���i���o�[(����Ȃ�����)
	int Request;		//�A�j�����f�t���O
	int End;			//�A�j���R�}���h�I���t���O
	BOOL EndComp;		//�A�j���I���t���O
	int Work[ANM_WORK_MAX];	//���[�N
	int ReqCount;		//
	
	int LoopMax;			//���[�v��
	int LoopCount;			//���݃��[�v��
	u32 *LoopStartAdrs;		//���[�v�J�n�A�h���X

	int Wait;			//�A�j���J�n�܂ł̃E�F�C�g

	int OrgX;			//�X�v���C�g�w���W
	int OrgY;			//�X�v���C�g�x���W
	int TransX;			//�w�ړ��l
	int TransY;			//�x�ړ��l
	int dx;				//�w�ړ��l�i�I�t�Z�b�g�j
	int dy;				//�x�ړ��l�i�I�t�Z�b�g�j
	int rx;				//�g�k�w
	int ry;				//�g�k�x
	int Rot;			//��]

	MOVE_FUNC_DATA			MoveFuncData[MOVE_FUNC_ENTRY_MAX];

	u8 PokeReverse;	//�|�P�������Ƃ̔��]�t���O(�|�P�����ɂ���Ă͔��]���Ȃ�)�@0�F���]���Ȃ��@1�F���]����
	u8 CommandHold;	//����֐��N�����z�[���h�t���O
	u8 CorrectDy;	//dy�␳�L���t���O
	u8 PalFadeWaitFlg;	//�p���b�g�t�F�[�h�I���҂��t���O

}POKE_ANIME;

typedef struct POKE_ANIME_SYS_tag
{
	POKE_ANIME *PokeAnime;
	int HeapID;		//�q�[�v�h�c
	u8 Reverse;		//�A�j���𔽓]���邩�ǂ����̃t���O�@0�F���]���Ȃ�	1�F���]����
	u8 AnimeNum;
}POKE_ANIME_SYS;

typedef struct MOVE_FUNC_P_DATA_tag
{
	MoveFunc	Func;	//����֐�
	int ParamNum;		//�p�����[�^��
	int TargetWorkIdx;	//�ύX�Ώۂ��i�[�������[�N�̃C���f�b�N�X
}MOVE_FUNC_P_DATA;

static void CallMoveFuc(POKE_ANIME *pAnm, const int inMoveFuncNo);
static void	PokemonAnimeTask(TCB_PTR tcb, void *work);
static void ExecutePokeAnime(POKE_ANIME *pAnm);

static void	PAnm_End(POKE_ANIME *pAnm);
static void	PAnm_SetRequest(POKE_ANIME *pAnm);
static void PAnm_SetDefault(POKE_ANIME *pAnm);
static void PAnm_SetIfWorkVal(POKE_ANIME *pAnm);
static void PAnm_SetWorkVal(POKE_ANIME *pAnm);
static void PAnm_CopyWorkVal(POKE_ANIME *pAnm);
static void PAnm_AddWorkVal(POKE_ANIME *pAnm);
static void PAnm_MulWorkVal(POKE_ANIME *pAnm);
static void PAnm_SubWorkVal(POKE_ANIME *pAnm);
static void PAnm_DivWorkVal(POKE_ANIME *pAnm);
static void PAnm_ModWorkVal(POKE_ANIME *pAnm);
static void	PAnm_StartLoop(POKE_ANIME *pAnm);
static void	PAnm_EndLoop(POKE_ANIME *pAnm);
static void	PAnm_SetVal(POKE_ANIME *pAnm);		//���ʂ̃R�}���h���g���悤��(�����I�ɍl���ăR�}���h�͏����܂���) 20060801
static void	PAnm_AddVal(POKE_ANIME *pAnm);		//���ʂ̃R�}���h���g���悤��(�����I�ɍl���ăR�}���h�͏����܂���) 20060801
static void PAnm_SetAddVal(POKE_ANIME *pAnm);
static void PAnm_SetWorkValSin(POKE_ANIME *pAnm);
static void PAnm_SetWorkValCos(POKE_ANIME *pAnm);
static void PAnm_SetTrans(POKE_ANIME *pAnm);	//���ʂ̃R�}���h���g���悤��(�����I�ɍl���ăR�}���h�͏����܂���) 20060801
static void PAnm_AddTrans(POKE_ANIME *pAnm);	//���ʂ̃R�}���h���g���悤��(�����I�ɍl���ăR�}���h�͏����܂���) 20060801
static void PAnm_SetAddParam(POKE_ANIME *pAnm);
static void PAnm_ApplyTrans(POKE_ANIME *pAnm);
static void PAnm_ApplyAffine(POKE_ANIME *pAnm);
static void PAnm_SetD(POKE_ANIME *pAnm);
static void PAnm_SetWait(POKE_ANIME *pAnm);
static void PAnm_PaletteFade(POKE_ANIME *pAnm);
static void PAnm_WaitPaletteFade(POKE_ANIME *pAnm);

static void PAnm_HoldAnmCommand(POKE_ANIME *pAnm);
static void PAnm_SetDyCorrect(POKE_ANIME *pAnm);
static void PAnm_CallMoveFuncCurve(POKE_ANIME *pAnm);
static void PAnm_CallMoveFuncCurveDivTime(POKE_ANIME *pAnm);
static void PAnm_CallMoveFuncLine(POKE_ANIME *pAnm);
static void PAnm_CallMoveFuncLineDivTime(POKE_ANIME *pAnm);
static void PAnm_CallMoveFuncLineDst(POKE_ANIME *pAnm);

static void PMove_Curve(MOVE_FUNC_DATA_PTR pMFD, POKE_ANM_PTR pAnm);
static void PMove_CurveDivTime(MOVE_FUNC_DATA_PTR pMFD, POKE_ANM_PTR pAnm);
static void PMove_Line(MOVE_FUNC_DATA_PTR pMFD, POKE_ANM_PTR pAnm);
static void PMove_LineDivTime(MOVE_FUNC_DATA_PTR pMFD, POKE_ANM_PTR pAnm);
static void PMove_LineDst(MOVE_FUNC_DATA_PTR pMFD, POKE_ANM_PTR pAnm);

#define CHARA_MAX	(25)
//���i�ʃA�j���n�b�V���e�[�u���i0�F�h��ȓ����@1�F���ʁ@2�F�T���߂ȓ����j
static const u8 PesrsonalityTbl[CHARA_MAX] = {
	0,	//����΂��
	2,	//���݂�����
	0,	//�䂤����
	0,	//�������ς�
	0,	//��񂿂�
	1,	//���ԂƂ�
	1,	//���Ȃ�
	1,	//�̂�
	0,	//���ς�
	1,	//�̂��Ă�
	2,	//�����т傤
	0,	//��������
	1,	//�܂���
	0,	//�悤��
	0,	//�ނ��Ⴋ
	2,	//�Ђ�����
	2,	//�����Ƃ�
	2,	//�ꂢ����
	2,	//�Ă��
	1,	//���������
	1,	//�����₩
	2,	//���ƂȂ���
	1,	//�Ȃ܂���
	2,	//���񂿂傤
	1,	//���܂���
};

static const pAnmFunc PokeAnmCmdList[ANM_CMD_MAX] = {
	PAnm_End,				//0
	PAnm_SetRequest,
	PAnm_SetDefault,
	PAnm_SetIfWorkVal,
	PAnm_SetWorkVal,
	PAnm_CopyWorkVal,
	PAnm_AddWorkVal,
	PAnm_MulWorkVal,
	PAnm_SubWorkVal,
	PAnm_DivWorkVal,
	PAnm_ModWorkVal,
	PAnm_StartLoop,
	PAnm_EndLoop,
	PAnm_SetVal,		//���ʂ̃R�}���h���g���悤��(�����I�ɍl���ăR�}���h�͏����܂���) 20060801
	PAnm_AddVal,		//���ʂ̃R�}���h���g���悤��(�����I�ɍl���ăR�}���h�͏����܂���) 20060801
	PAnm_SetAddVal,
	PAnm_SetWorkValSin,
	PAnm_SetWorkValCos,
	PAnm_SetTrans,	//���ʂ̃R�}���h���g���悤��(�����I�ɍl���ăR�}���h�͏����܂���) 20060801
	PAnm_AddTrans,	//���ʂ̃R�}���h���g���悤��(�����I�ɍl���ăR�}���h�͏����܂���) 20060801
	PAnm_SetAddParam,
	PAnm_ApplyTrans,
	PAnm_ApplyAffine,
	PAnm_SetD,

	PAnm_HoldAnmCommand,
	PAnm_SetDyCorrect,
	PAnm_CallMoveFuncCurve,
	PAnm_CallMoveFuncCurveDivTime,
	PAnm_CallMoveFuncLine,
	PAnm_CallMoveFuncLineDivTime,
	PAnm_CallMoveFuncLineDst,	
	
	PAnm_SetWait,
	PAnm_PaletteFade,
	PAnm_WaitPaletteFade,
};

enum{
	MOVE_CURVE,
	MOVE_CURVE_DIVTIME,
	MOVE_LINE,
	MOVE_LINE_DIVTIME,
	MOVE_LINE_DST,
};

#define F_PARAM_NUM_CURVE			(6)	//�J�[�u�^�C�v�A�ΏہA�U���A���Z�p�x�A�ʑ��A�v�Z��	�v6
#define F_PARAM_NUM_CURVE_DIVTIME	(6)	//�J�[�u�^�C�v�A�ΏہA�U���A�p�x�A�ʑ��A�v�Z��	�v6
#define F_PARAM_NUM_LINE			(4)	//�ΏہA�����x�A�����x�A�v�Z��	�v4
#define F_PARAM_NUM_LINE_DIVTIME	(3)	//�ΏہA�ړ��l�A�v�Z��	�v3
#define F_PARAM_NUM_LINE_DST		(4)	//�ΏہA�����x�A�����x�A�ړI�l	�v4

static const MOVE_FUNC_P_DATA MoveFuncTbl[] = {
	{PMove_Curve, F_PARAM_NUM_CURVE, 1},
	{PMove_CurveDivTime, F_PARAM_NUM_CURVE_DIVTIME,1},
	{PMove_Line,F_PARAM_NUM_LINE, 0},
	{PMove_LineDivTime,F_PARAM_NUM_LINE_DIVTIME,0},
	{PMove_LineDst,F_PARAM_NUM_LINE_DST,0}
};

//--------------------------------------------------------------
/**
 * �|�P�����A�j���[�V�����Z�b�e�B���O�p�����[�^�̍쐬
 *
 * @param	inMonsNo	�����X�^�[�i���o�[
 * @param	outParam	�p�����[�^�i�[�o�b�t�@
 *
 * @retval	none
 */
//--------------------------------------------------------------
void PokeAnm_CreateSettingParam(const int inMonsNo, P_ANM_SETTING_PARAM *outParam)
{
	GF_ASSERT(outParam!=NULL&&"ERROR:paramater is NULL");
	
	outParam->AnimeNo = 0;	//0���Z�b�g
	outParam->Wait = 0;		//0���Z�b�g
	outParam->Reverse = PokePersonalParaGet(inMonsNo, ID_PER_reverse);	//�p�[�\�i�����甽�]�t���O���擾
	outParam->Reverse ^= 1;
}


//--------------------------------------------------------------
/**
 * �|�P�����A�j���[�V�����p�Ǘ��������̊m��
 *
 * @param	inHeapID	�q�[�vID
 * @param	inAllocNum	�A�j���m�ې�
 * @param	inReverse	���]���t���O
 *
 * @retval	POKE_ANM_S_PTR	�m�ۂ����|�P�����A�j���Ǘ��̈�ւ̃|�C���^
 */
//--------------------------------------------------------------
POKE_ANM_SYS_PTR PokeAnm_AllocMemory(const int inHeapID, const int inAllocNum, const u8 inReverse)
{
	POKE_ANM_SYS_PTR ptr;
	ptr = sys_AllocMemory(inHeapID, sizeof(POKE_ANIME_SYS));
	ptr->Reverse = inReverse;
	ptr->AnimeNum = inAllocNum;
	ptr->HeapID = inHeapID;
	ptr->PokeAnime = sys_AllocMemory(inHeapID, sizeof(POKE_ANIME)*inAllocNum);
	//�N���A
	MI_CpuClear8(ptr->PokeAnime,sizeof(POKE_ANIME)*inAllocNum);
	
	return  ptr;
}

//--------------------------------------------------------------
/**
 * �|�P�����A�j���[�V�����p�Ǘ����������
 *
 * @param	ptr				�|�P�����A�j���̈�ւ̃|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
void PokeAnm_FreeMemory(POKE_ANM_SYS_PTR ptr)
{
	sys_FreeMemoryEz(ptr->PokeAnime);
	sys_FreeMemoryEz(ptr);
}
//--------------------------------------------------------------
/**
 * ���i����w�ʃ|�P�����A�j���̃X���b�g�ԍ���Ԃ��i0�`2�j
 *
 * @param	inChar			�|�P�����̐��i
 *
 * @retval	u8			�̗p����X���b�g�ԍ��i0�`2�j
 */
//--------------------------------------------------------------
u8 PokeAnm_GetBackAnmSlotNo(	const u8 inChar )
{
	u8 slot_no;
	GF_ASSERT(inChar < CHARA_MAX);
	slot_no = PesrsonalityTbl[inChar];
	
	return slot_no;
}

//--------------------------------------------------------------
/**
 * �\�t�g�E�F�A�X�v���C�g�ƃ|�P�����i���o�[���Z�b�g����
 *
 * @param	ptr				�|�P�����A�j���̈�ւ̃|�C���^
 * @param	ss				�\�t�g�E�F�A�X�v���C�g�ւ̃|�C���^
 * @param	inParam			�A�j���Z�b�e�B���O�p�����[�^
 * @param	inEntryIndex	�o�^�C���f�b�N�X
 *
 * @retval	none
 */
//--------------------------------------------------------------
void PokeAnm_SetPokeAnime(	POKE_ANM_SYS_PTR ptr, SOFT_SPRITE *ss,
							const P_ANM_SETTING_PARAM *inParam,
							const u8 inEntryIndex)
{
	u8 idx = inEntryIndex;
	int anime_no = inParam->AnimeNo;
	int wait = inParam->Wait;
	
	GF_ASSERT((idx<ptr->AnimeNum)&&"ERROR:IndexOver");
	GF_ASSERT(ptr->PokeAnime[idx].Valid==FALSE&&"ERROR:PokeAnime Entry already");

	//�N���A
	MI_CpuClear8(&ptr->PokeAnime[idx],sizeof(POKE_ANIME));

	//�f�[�^�L��
	ptr->PokeAnime[idx].Valid = TRUE;

	//�X�v���C�g�Z�b�g
	ptr->PokeAnime[idx].SoftSprite = ss;
#ifdef PM_DEBUG	
	//�g�k�����`�F�b�N
	{
		int aff_x,aff_y;
		aff_x = SoftSpriteParaGet(ss, SS_PARA_AFF_X);
		aff_y = SoftSpriteParaGet(ss, SS_PARA_AFF_Y);
		GF_ASSERT( (aff_x==0x100)&&(aff_y==0x100) );
	}
#endif	
	//�A�j���i���o�[�͈͊O�Ώ�
	if (anime_no >= POKE_ANIME_MAX){
		anime_no = 0;
		wait = 0;
	}
	
	//�����X�^�[�i���o�[����A�j���[�V���������
	ptr->PokeAnime[idx].AnimeNo = anime_no;

	//���]�t���O�Z�b�g
	if (ptr->Reverse){
		//�����X�^�[���Ƃɔ��]������
		ptr->PokeAnime[idx].PokeReverse = inParam->Reverse;
	}else{
		ptr->PokeAnime[idx].PokeReverse = 0;
	}

	//�A�j���A�[�J�C�u�f�[�^�Z�b�g
	ptr->PokeAnime[idx].ArcData =
		ArchiveDataLoadMallocLo(ARC_POKE_ANM, ptr->PokeAnime[idx].AnimeNo, ptr->HeapID );
	ptr->PokeAnime[idx].SeqAdrs = (u32*)ptr->PokeAnime[idx].ArcData;
	
	//�A�j���I���t���O�I�t
	ptr->PokeAnime[idx].End = 0;
	ptr->PokeAnime[idx].EndComp = FALSE;
	//�z�[���h�N���A
	ptr->PokeAnime[idx].CommandHold = 0;
	//dy�␳����
	ptr->PokeAnime[idx].CorrectDy = CORRECT_OFF;
	//�p���b�g�҂���ԃN���A
	ptr->PokeAnime[idx].PalFadeWaitFlg = 0;
	//�A�j���o�^�i�^�X�N�o�^�j�ƃ^�X�N�L��
	ptr->PokeAnime[idx].Task = TCB_Add(PokemonAnimeTask, &ptr->PokeAnime[idx], 0);

	//�A�j���J�n�E�F�C�g���Z�b�g
	ptr->PokeAnime[idx].Wait = wait;		

	ptr->PokeAnime[idx].OrgX = SoftSpriteParaGet(ss,SS_PARA_POS_X);
	ptr->PokeAnime[idx].OrgY = SoftSpriteParaGet(ss,SS_PARA_POS_Y);
	ptr->PokeAnime[idx].TransX = 0;
	ptr->PokeAnime[idx].TransY = 0;
	ptr->PokeAnime[idx].dx = 0;
	ptr->PokeAnime[idx].dy = 0;
	ptr->PokeAnime[idx].rx = 0;
	ptr->PokeAnime[idx].ry = 0;
	ptr->PokeAnime[idx].Rot = 0;

///	OS_Printf("anime_struct_size = %d\n",sizeof(POKE_ANIME));
}

//--------------------------------------------------------------
/**
 * �A�j���[�V�����I�������o
 *
 * @param	ptr				�|�P�����A�j���̈�ւ̃|�C���^
 * @param	inEntryIndex	�O�`�R�܂ł̓o�^�C���f�b�N�X
 *
 * @retval	BOOL	TRUE:�I��		FALSE:�p��
 */
//--------------------------------------------------------------
BOOL PokeAnm_IsFinished(POKE_ANM_SYS_PTR ptr, const u8 inEntryIndex)
{
	GF_ASSERT((inEntryIndex<ptr->AnimeNum)&&"ERROR:IndexOver");

	return ptr->PokeAnime[inEntryIndex].EndComp;
}

//--------------------------------------------------------------
/**
 * �A�j���[�V���������I��(�^�X�N�폜)
 *
 * @param	ptr				�|�P�����A�j���̈�ւ̃|�C���^
 * @param	inEntryIndex	�O�`�R�܂ł̓o�^�C���f�b�N�X
 *
 * @retval	none
 */
//--------------------------------------------------------------
void PokeAnm_EndAnimeForce(POKE_ANM_SYS_PTR ptr, const u8 inEntryIndex)
{
	if ( ptr->PokeAnime[inEntryIndex].Task != NULL ){
		TCB_Delete(ptr->PokeAnime[inEntryIndex].Task);
		ptr->PokeAnime[inEntryIndex].Task = NULL;
		ptr->PokeAnime[inEntryIndex].EndComp = TRUE;
		ptr->PokeAnime[inEntryIndex].Valid = FALSE;		//�A�j������
		//�A�j���f�[�^���
		sys_FreeMemoryEz(ptr->PokeAnime[inEntryIndex].ArcData);
	}
}

//--------------------------------------------------------------
/**
 * �|�P�����A�j���[�V�����^�X�N
 *
 * @param	tcb		�^�X�N�̃|�C���^
 * @param	work	�^�X�N���[�N
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void	PokemonAnimeTask(TCB_PTR tcb, void *work)
{
	POKE_ANIME *anime = (POKE_ANIME*)(work);
	if (anime->Wait == 0){
		ExecutePokeAnime(anime);
	}else{
		anime->Wait--;
	}
	
	if (anime->End){
		anime->EndComp = TRUE;
		anime->Valid = FALSE;		//�A�j������
		//�^�X�N�j��
		TCB_Delete(tcb);
		anime->Task = NULL;
		//�A�j���f�[�^���
		sys_FreeMemoryEz(anime->ArcData);
	}
}

//--------------------------------------------------------------
/**
 * �R�}���h���s�֐�
 *
 * @param	pAnm			�A�j���|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void ExecutePokeAnime(POKE_ANIME *pAnm)
{
	pAnmFunc func;
	pAnm->Request = 0;
	pAnm->ReqCount = 0;

	{
		u8 i;
		u8 invalid;
		MOVE_FUNC_DATA_PTR mfd_ptr;
		//����֐�����
		invalid = 0;
		for(i=0;i<MOVE_FUNC_ENTRY_MAX;i++){
			mfd_ptr = &(pAnm->MoveFuncData[i]);
			if (mfd_ptr->Valid){
				if (mfd_ptr->Wait == 0){
					///����֐����s
					mfd_ptr->Func(mfd_ptr,pAnm);
				}else{
					mfd_ptr->Wait--;
				}
			}else{
				invalid++;
			}
		}
		if (invalid == MOVE_FUNC_ENTRY_MAX){	//����֐����S�ďI�����Ă���Ȃ��
			//�R�}���h���߃z�[���h������
			pAnm->CommandHold = 0;
		}
	}

	if (pAnm->CommandHold){	//����֐��ɂ��R�}���h���߂��z�[���h���Ă���Ȃ��
		//���݂܂ł̌v�Z���ʂ��X�v���C�g�ɔ��f�����āA�A�j���[�V���������s
		PAnm_ApplyTrans(pAnm);
		PAnm_ApplyAffine(pAnm);
		return;
	}

	//�p���b�g�t�F�[�h�I���҂���ԂȂ�
	if (pAnm->PalFadeWaitFlg){
		//�I���܂Ŏ��̃R�}���h�����s���Ȃ�
		if( !SoftSpritePalFadeExist(pAnm->SoftSprite) ){//�t�F�[�h�̏󋵂��݂�
			pAnm->PalFadeWaitFlg = 0;//�t�F�[�h�I��
		}else{
			return ;//�t�F�[�h�p�����Ă�̂ŁA�Ԃ�
		}
	}

	while(1) {	//�A�j�����f���N�G�X�g��������܂Ŏ��s
///		OS_Printf("val=%d\n",(u32)(*pAnm->SeqAdrs));
		pAnm->ReqCount++;
		//���s�֐�
		GF_ASSERT((u32)*(pAnm->SeqAdrs)<ANM_CMD_MAX&&"ERROR:AnimeCmdOver");
		func = PokeAnmCmdList[(u32)*(pAnm->SeqAdrs)];
		func(pAnm);

		if (pAnm->End){
			break;
		}else{
			ADRS_SHIFT(pAnm->SeqAdrs);
			if (pAnm->Request){
///				OS_Printf("pos = %d\n",SoftSpriteParaGet(pAnm->SoftSprite,SS_PARA_POS_Y));
				break;
			}else if(pAnm->CommandHold){
				//����֐�����ω��𔽉f
				PAnm_ApplyTrans(pAnm);
				PAnm_ApplyAffine(pAnm);
				break;
			}
		}

		//�������[�v���
		if (pAnm->ReqCount >= REQUEST_MAX)
		{
			GF_ASSERT(0&&"Request too long");
			//�|�P�����̈ʒu�߂��Ƃ��H
			pAnm->End = 1;
			break;
		}
	}
}

//--------------------------------------------------------------
/**
 * @brief	�w��o�C�g���f�[�^���擾
 *
 * @param	adrs	�擾����ΏۃA�h���X
 * @param	s_byte	�J�n����o�C�g�ʒu
 * @param	byte	�擾����o�C�g��
 *
 * @retval	TAP	�l
 *
 */
//--------------------------------------------------------------
static TAP GetAdrsParamEx(u32* adrs, u8 s_byte, u8 byte)
{
	TAP val = adrs[s_byte];
	
	if (byte != 1){
		GF_ASSERT(0);
	}
	return val;
}

//--------------------------------------------------------------
/**
 * @brief	�w��o�C�g���f�[�^���擾
 *
 * @param	adrs	�擾����ΏۃA�h���X
 * @param	byte	�擾����o�C�g��
 *
 * @retval	TAP		�l
 *
 */
//--------------------------------------------------------------
static TAP GetAdrsParam(u32* adrs, u8 byte)
{
	TAP val;

	val = GetAdrsParamEx(adrs, 0, byte);

	return val;
}

//--------------------------------------------------------------
/**
 * @brief	�V�[�P���X�A�h���X���擾
 *
 * @param	adrs	�擾����ΏۃA�h���X
 *
 * @retval	TAP		�l
 *
 */
//--------------------------------------------------------------
static TAP GetSeqAdrs(u32* adrs)
{
	return GetAdrsParam(adrs, 1);
}

//--------------------------------------------------------------
/**
 * ����֐��̃Z�b�g
 *
 * @param	pAnm			�A�j���|�C���^
 * @param	inMoveFuncNo	����֐��ԍ�(256�͒����Ȃ��Ǝv��)
 *
 * @retval	none
 */
//--------------------------------------------------------------
static MOVE_FUNC_DATA_PTR SetMoveFunc(POKE_ANIME *pAnm, const u8 inMoveFuncNo)
{
	MOVE_FUNC_DATA_PTR ptr;
	u8 i;
	//�󂢂Ă���Ƃ����T��
	for(i=0;i<MOVE_FUNC_ENTRY_MAX;i++){
		ptr = &(pAnm->MoveFuncData[i]);
		if (ptr->Valid == FALSE){
			//�N���A
			MI_CpuClear8(ptr,sizeof(MOVE_FUNC_DATA));	
			//�Z�b�g
			ptr->Valid = TRUE;
			ptr->Func = MoveFuncTbl[inMoveFuncNo].Func;
			return ptr;
		}
	}
	GF_ASSERT(0&&"ERROR:MOVE_FUNC_ENTRY_FAILED!!");
	return NULL;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------
/**
 * int�^�l���擾
 *
 * @param	pAnm			�A�j���|�C���^
 * @param	outVal			�i�[�o�b�t�@
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void GetInt(POKE_ANIME *pAnm, int *outVal)
{
	ADRS_SHIFT(pAnm->SeqAdrs);
	(*outVal) =  (int)GetSeqAdrs(pAnm->SeqAdrs);
}

//--------------------------------------------------------------
/**
 * u8�^�l���擾
 *
 * @param	pAnm			�A�j���|�C���^
 * @param	outVal			�i�[�o�b�t�@
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void GetU8(POKE_ANIME *pAnm, u8 *outVal)
{
	ADRS_SHIFT(pAnm->SeqAdrs);
	(*outVal) =  (u8)GetSeqAdrs(pAnm->SeqAdrs);
}

//--------------------------------------------------------------
/**
 * ���[�N�C���f�b�N�X�擾
 *
 * @param	pAnm			�A�j���|�C���^
 * @param	outIdx			�擾�C���f�b�N�X�i�[�o�b�t�@
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void GetIdx(POKE_ANIME *pAnm, u8 *outIdx)
{
	ADRS_SHIFT(pAnm->SeqAdrs);
	(*outIdx) =  (u8)GetSeqAdrs(pAnm->SeqAdrs);
	GF_ASSERT((*outIdx)<ANM_WORK_MAX&&"ERROR:WorkOver");
}

//--------------------------------------------------------------
/**
 * ���[�N�C���f�b�N�X�擾(�C���f�b�N�X��2�A�����Ă�Ƃ�)
 *
 * @param	pAnm			�A�j���|�C���^
 * @param	outIdx1			1�ߎ擾�C���f�b�N�X�i�[�o�b�t�@
 * @param	outIdx2			2�ߎ擾�C���f�b�N�X�i�[�o�b�t�@
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void GetTwoIdx(POKE_ANIME *pAnm, u8 *outIdx1, u8 *outIdx2)
{
	GetIdx(pAnm, outIdx1);
	GetIdx(pAnm, outIdx2);
}

//--------------------------------------------------------------
/**
 * ���Z�E��Z���ʏ���
 *
 * @param	pAnm			�A�j���|�C���^
 * @param	outDstIdx		�i�[�惏�[�N�C���f�b�N�X
 * @param	outVal1			1�ߒl�i�[�o�b�t�@
 * @param	outVal2			2�ߒl�i�[�o�b�t�@
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void CalcCommonAddMul(POKE_ANIME *pAnm, u8 *outDstIdx, int *outVal1, int *outVal2)
{
	u8 idx1,idx2;
	u8 calc;
	
	//�i�[�惏�[�N�C���f�b�N�X�擾
	GetIdx(pAnm,outDstIdx);
	//�v�Z�^�C�v�擾
	GetU8(pAnm,&calc);
	
	if (calc == CALC_VAL){
		//���[�N�ƒ��l�̌v�Z
		GetIdx(pAnm,&idx1);
		(*outVal1) = pAnm->Work[idx1];
		GetInt(pAnm,outVal2);
	}else if (calc == CALC_WORK){
		//���[�N���m�̌v�Z
		GetTwoIdx(pAnm, &idx1, &idx2);
		(*outVal1) = pAnm->Work[idx1];
		(*outVal2) = pAnm->Work[idx2];
	}else{
		GF_ASSERT(0);
	}
}

//--------------------------------------------------------------
/**
 * ���Z�E���Z�E�]��v�Z���ʏ���
 *
 * @param	pAnm			�A�j���|�C���^
 * @param	outDstIdx		�i�[�惏�[�N�C���f�b�N�X
 * @param	outVal1			1�ߒl�i�[�o�b�t�@
 * @param	outVal2			2�ߒl�i�[�o�b�t�@
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void CalcCommonSubDivMod(POKE_ANIME *pAnm, u8 *outDstIdx, int *outVal1, int *outVal2)
{
	u8 idx1,idx2;
	u8 calc1,calc2;
	//�i�[�惏�[�N�C���f�b�N�X�擾
	GetIdx(pAnm,outDstIdx);
	//�v�Z�^�C�v�擾
	GetU8(pAnm,&calc1);
	GetU8(pAnm,&calc2);
	
	if (calc1 == CALC_VAL){
		//���l
		GetInt(pAnm,outVal1);
	}else if(calc1 == CALC_WORK){
		//���[�N
		GetIdx(pAnm,&idx1);
		(*outVal1) = pAnm->Work[idx1];
	}else{
		GF_ASSERT(0);
	}

	if (calc2 == CALC_VAL){
		//���l
		GetInt(pAnm,outVal2);
	}else if(calc2 == CALC_WORK){
		//���[�N
		GetIdx(pAnm,&idx2);
		(*outVal2) = pAnm->Work[idx2];
	}else{
		GF_ASSERT(0);
	}
}

//--------------------------------------------------------------
/**
 * �T�C���E�R�T�C������
 *
 * @param	pAnm			�A�j���|�C���^
 * @param	outDstIdx		�i�[�惏�[�N�C���f�b�N�X
 * @param	outRad			���W�A���l�i�[�o�b�t�@
 * @param	outL			�U���l�i�[�o�b�t�@
 * 
 * @retval	COMP_MINUS:�������@COMP_PULS:�傫���@COMP_EQUAL	����
 */
//--------------------------------------------------------------
static void CalcCommonSinCos(POKE_ANIME *pAnm, u8 *outDstIdx, int *outRad, int *outL)
{
	u8 rad_idx,l_idx,ofs_idx;
	int rad;
	int ofs;
	u8 use;
	
	//���[�N�C���f�b�N�X�擾
	//���W�A���擾
	GetTwoIdx(pAnm, outDstIdx, &rad_idx);
	
	rad = pAnm->Work[rad_idx];

	//�U���擾
	GetU8(pAnm,&use);
	if (use == USE_VAL){
		GetInt(pAnm,outL);
	}else if(use == USE_WORK){
		GetIdx(pAnm,&l_idx);
		(*outL) = pAnm->Work[l_idx];
	}else{
		GF_ASSERT(0);
	}

	//�ʑ��擾
	GetU8(pAnm,&use);
	if (use == USE_VAL){
		GetInt(pAnm,&ofs);
	}else if(use == USE_WORK){
		GetIdx(pAnm,&ofs_idx);
		ofs = pAnm->Work[ofs_idx];
	}else{
		GF_ASSERT(0);
	}
	
	(*outRad) = rad+ofs;
	(*outRad) %= 0x10000;

}

//--------------------------------------------------------------
/**
 * �l��r	�Q�ڂ̒l�ɑ΂��ĂP�ڂ̒l���ǂ�Ȓl�ł��邩��Ԃ�
 *
 * @param	inVal1		�l�P��
 * @param	inVal2		�l�Q��
 *
 * @retval	COMP_MINUS:�������@COMP_PULS:�傫���@COMP_EQUAL	����
 */
//--------------------------------------------------------------
static u8 CompVal(const int *inVal1, const int *inVal2)
{
	int val;
	val = 	(*inVal1)-(*inVal2);
	if (val<0){
		return COMP_MINUS;
	}else if (val>0){
		return COMP_PLUS;
	}else{
		return COMP_EQUAL;
	}
}

//--------------------------------------------------------------
/**
 * �g�k�ɂ��c�x�␳
 *
 * @param	pAnm			�A�j���|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void CorrectDy(POKE_ANIME *pAnm)
{
	int correct;
	correct = (-pAnm->ry)/8;
	SoftSpriteParaCalc(pAnm->SoftSprite, SS_PARA_POS_Y, correct);
}

/////////////////////////////////////////////////////////////////////////////////////////
//�R�}���h

//--------------------------------------------------------------
/**
 * �A�j���I��
 *
 * @param	pAnm			�A�j���|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_End(POKE_ANIME *pAnm)
{
	//�X�v���C�g�����̈ʒu��
	PAnm_SetDefault(pAnm);
	
	pAnm->Request = 1;
	pAnm->End = 1;
}

//--------------------------------------------------------------
/**
 * �A�j�����f	(���܂ōs�����v�Z���ʂ�`��ɔ��f����)
 *
 * @param	pAnm			�A�j���|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_SetRequest(POKE_ANIME *pAnm)
{
	pAnm->Request = 1;
}

//--------------------------------------------------------------
/**
 * �X�v���C�g���A�j���O�̏�Ԃɖ߂��i��]�A�g�k�ɑ΂��ẮA����]�A�{��1���Z�b�g�j
 *
 * @param	pAnm			�A�j���|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_SetDefault(POKE_ANIME *pAnm)
{
	//�ʒu�A��]�A�g�k�����ɖ߂�
	SoftSpriteParaSet(pAnm->SoftSprite, SS_PARA_POS_X, pAnm->OrgX);
	SoftSpriteParaSet(pAnm->SoftSprite, SS_PARA_POS_Y, pAnm->OrgY);

	SoftSpriteParaSet(pAnm->SoftSprite, SS_PARA_ROT_Z, 0);
	SoftSpriteParaSet(pAnm->SoftSprite, SS_PARA_ROT_CX, 0);

	SoftSpriteParaSet(pAnm->SoftSprite, SS_PARA_AFF_X, 0x100);
	SoftSpriteParaSet(pAnm->SoftSprite, SS_PARA_AFF_Y, 0x100);
}

//--------------------------------------------------------------
/**
 * ���[�N�Ԃ̒l�̃R�s�[	
 * 1�ڂ̃C���f�b�N�X�Ŏw�肳��郏�[�N�ɁA2�ڂ̃C���f�b�N�X�Ŏw�肳��郏�[�N���R�s�[
 *
 * @param	pAnm			�A�j���|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_CopyWorkVal(POKE_ANIME *pAnm)
{
	u8 idx1,idx2;
	GetTwoIdx(pAnm, &idx1, &idx2);

	pAnm->Work[idx1] = pAnm->Work[idx2];
}

//--------------------------------------------------------------
/**
 * ���[�N�̉��Z
 *
 * @param	pAnm			�A�j���|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_AddWorkVal(POKE_ANIME *pAnm)
{
	u8 dst_idx;
	int val1,val2;

	CalcCommonAddMul(pAnm, &dst_idx, &val1, &val2);
	
	pAnm->Work[dst_idx] = val1 + val2;
}

//--------------------------------------------------------------
/**
 * ���[�N�̏�Z
 *
 * @param	pAnm			�A�j���|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_MulWorkVal(POKE_ANIME *pAnm)
{
	u8 dst_idx;
	int val1,val2;
	
	CalcCommonAddMul(pAnm, &dst_idx, &val1, &val2);

	pAnm->Work[dst_idx] = val1 * val2;
//	OS_Printf("mul=%d\n",pAnm->Work[dst_idx]);
}

//--------------------------------------------------------------
/**
 * ���[�N�̌��Z
 *
 * @param	pAnm			�A�j���|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_SubWorkVal(POKE_ANIME *pAnm)
{
	u8 dst_idx;
	int val1,val2;

	CalcCommonSubDivMod(pAnm, &dst_idx, &val1, &val2);	

	pAnm->Work[dst_idx] = val1 - val2;
//	OS_Printf("sub=%d\n",pAnm->Work[dst_idx]);
}

//--------------------------------------------------------------
/**
 * ���[�N�̏��Z
 *
 * @param	pAnm			�A�j���|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_DivWorkVal(POKE_ANIME *pAnm)
{
	u8 dst_idx;
	int val1,val2;

	CalcCommonSubDivMod(pAnm, &dst_idx, &val1, &val2);	

	pAnm->Work[dst_idx] = val1 / val2;
//	OS_Printf("div=%d\n",pAnm->Work[dst_idx]);
}

//--------------------------------------------------------------
/**
 * ���[�N�̗]������v�Z
 *
 * @param	pAnm			�A�j���|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_ModWorkVal(POKE_ANIME *pAnm)
{
	u8 dst_idx;
	int val1,val2;

	CalcCommonSubDivMod(pAnm, &dst_idx, &val1, &val2);	

	pAnm->Work[dst_idx] = val1 % val2;
}

//--------------------------------------------------------------
/**
 * �l��r��Ƀ��[�N�Z�b�g
 *
 * @param	pAnm			�A�j���|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_SetIfWorkVal(POKE_ANIME *pAnm)
{
	u8 idx1,idx2;
	u8 comp, comp_result;
	u8 use;
	
	{
		int val1,val2;
		GetU8(pAnm,&use);  
		if (use == USE_VAL){
			GetIdx(pAnm,&idx1);
			val1 = pAnm->Work[idx1];
			GetInt(pAnm,&val2);
		}else if(use == USE_WORK){
			GetTwoIdx(pAnm, &idx1, &idx2);
			val1 = pAnm->Work[idx1];
			val2 = pAnm->Work[idx2];
		}else{
			GF_ASSERT(0);
		}
	
		GetU8(pAnm,&comp);
	
		GF_ASSERT((comp<=COMP_EQUAL)&&"ERROR:COMP_ERROR");
		//��r
		comp_result = CompVal(&val1, &val2);
	}
	
	{
		int val;
		GetU8(pAnm,&use);
		if (use == USE_VAL){
			GetIdx(pAnm,&idx1);
			GetInt(pAnm,&val);
		}else if(use == USE_WORK){
			GetTwoIdx(pAnm, &idx1, &idx2);
			val = pAnm->Work[idx2];
		}else{
			GF_ASSERT(0);
		}

		if (comp == comp_result){	
			pAnm->Work[idx1] = val;
		}
	}
}

//--------------------------------------------------------------
/**
 * ���[�N�ɒl���Z�b�g
 *
 * @param	pAnm			�A�j���|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_SetWorkVal(POKE_ANIME *pAnm)
{
	u8 idx;
	GetIdx(pAnm, &idx);
	
	ADRS_SHIFT(pAnm->SeqAdrs);
	pAnm->Work[idx] = (int)GetSeqAdrs(pAnm->SeqAdrs);
}

//--------------------------------------------------------------
/**
 * ���[�v�J�n
 *
 * @param	pAnm			�A�j���|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_StartLoop(POKE_ANIME *pAnm)
{
	GF_ASSERT(pAnm->LoopStartAdrs==NULL&&"ERROR:Loop is moving");
	
	ADRS_SHIFT(pAnm->SeqAdrs);
	//���[�v�J�n�A�h���X��ۑ�
	pAnm->LoopStartAdrs = pAnm->SeqAdrs;
	//�ő僋�[�v�񐔕ۑ�
	pAnm->LoopMax = (int)GetSeqAdrs(pAnm->SeqAdrs);
	pAnm->LoopCount = 0;
}

//--------------------------------------------------------------
/**
 * ���[�v�I��
 *
 * @param	pAnm			�A�j���|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_EndLoop(POKE_ANIME *pAnm)
{
	pAnm->LoopCount++;
	if (pAnm->LoopCount >= pAnm->LoopMax){
		//���[�v�I��
		pAnm->LoopStartAdrs = NULL;
		pAnm->LoopCount = 0;
		pAnm->LoopMax = 0;
	}else{
		//���[�v�p��
		pAnm->SeqAdrs = pAnm->LoopStartAdrs;	//�A�h���X��߂�
	}
}

//--------------------------------------------------------------
/**
 * �X�v���C�g�ɒl���Z�b�g
 *
 * @param	pAnm			�A�j���|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_SetVal(POKE_ANIME *pAnm)
{
	u8 idx;
	int ss_param;
	//�ύX�p�����[�^�擾
	GetInt(pAnm,&ss_param);
/**
	GetInt(pAnm,&use);
	if (use == USE_VAL){
		;
	}else if(use == USE_WAORK){
		;
	}else{
		GF_ASSERT(0);
	}
*/	
	GetIdx(pAnm, &idx);
	
	//�Z�b�g
	SoftSpriteParaSet(pAnm->SoftSprite, ss_param, pAnm->Work[idx]);
}

//--------------------------------------------------------------
/**
 * �X�v���C�g�ɒl���A�b�h
 *
 * @param	pAnm			�A�j���|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_AddVal(POKE_ANIME *pAnm)
{
	u8 idx;
	int ss_param;
	//�ύX�p�����[�^�擾
	GetInt(pAnm,&ss_param);
	
	GetIdx(pAnm, &idx);
	
	//�A�b�h
	SoftSpriteParaCalc(pAnm->SoftSprite, ss_param, pAnm->Work[idx]);
}

//--------------------------------------------------------------
/**
 * �X�v���C�g�ɒl���Z�b�g�E�A�b�h����
 *
 * @param	pAnm			�A�j���|�C���^
 * @param	
 * @param	
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_SetAddVal(POKE_ANIME *pAnm)
{
	int ss_param;
	int val;
	
	//�ύX�p�����[�^�擾
	GetInt(pAnm,&ss_param);
	{
		u8 idx;
		u8 use;
		GetU8(pAnm,&use);
		if (use == USE_VAL){
			GetInt(pAnm,&val);
		}else if(use == USE_WORK){
			GetIdx(pAnm,&idx);
			val = pAnm->Work[idx];
		}else{
			GF_ASSERT(0);
		}
	}

	{
		u8 ss_calc;
		GetU8(pAnm,&ss_calc);
		if (ss_calc == PARAM_SET){
			SoftSpriteParaSet(pAnm->SoftSprite, ss_param, val);
		}else if (ss_calc == PARAM_ADD){
			SoftSpriteParaCalc(pAnm->SoftSprite, ss_param, val);
		}else{
			GF_ASSERT(0);
		}
	}
}

//--------------------------------------------------------------
/**
 * �T�C���v�Z
 *
 * @param	pAnm			�A�j���|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_SetWorkValSin(POKE_ANIME *pAnm)
{
	u8 idx;
	int dst_rad;
	int l;

	CalcCommonSinCos(pAnm,&idx,&dst_rad,&l);
	
	pAnm->Work[idx] = FX_Whole( FX_SinIdx(dst_rad)*l );
//	OS_Printf("sin=%d\n",pAnm->Work[idx]);
}

//--------------------------------------------------------------
/**
 * �R�T�C���v�Z
 *
 * @param	pAnm			�A�j���|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_SetWorkValCos(POKE_ANIME *pAnm)
{
	u8 idx;
	int dst_rad;
	int l;

	CalcCommonSinCos(pAnm,&idx,&dst_rad,&l);

	pAnm->Work[idx] = FX_Whole( FX_CosIdx(dst_rad)*l );
}

//--------------------------------------------------------------
/**
 * �ړ��l���A�j���f�[�^���g�����X�l�ɃZ�b�g
 *
 * @param	pAnm			�A�j���|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_SetTrans(POKE_ANIME *pAnm)
{
	u8 idx;
	u8 trans;
	
	//���[�N�C���f�b�N�X�擾
	GetIdx(pAnm, &idx);

	//�ύX�Ώێ擾
	GetU8(pAnm,&trans);

	if (trans == PARAM_X){
		pAnm->TransX = pAnm->Work[idx];
	}else if (trans == PARAM_Y){
		pAnm->TransY = pAnm->Work[idx];
	}else{
		GF_ASSERT(0);
	}
}

//--------------------------------------------------------------
/**
 * �ړ��l���A�j���f�[�^���g�����X�l�ɃA�b�h
 *
 * @param	pAnm			�A�j���|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_AddTrans(POKE_ANIME *pAnm)
{
	u8 idx;
	u8 trans;
	
	//���[�N�C���f�b�N�X�擾
	GetIdx(pAnm, &idx);

	//�ύX�Ώێ擾
	GetU8(pAnm,&trans);

	if (trans == PARAM_X){
		pAnm->TransX += pAnm->Work[idx];
	}else if (trans == PARAM_Y){
		pAnm->TransY += pAnm->Work[idx];
	}else{
		GF_ASSERT(0);
	}
}

//--------------------------------------------------------------
/**
 * �l���A�j���f�[�^���l�ɃZ�b�g�E�A�b�h
 *
 * @param	pAnm			�A�j���|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_SetAddParam(POKE_ANIME *pAnm)
{
	int *target;
	int val;

	{
		u8 param;

		//�ύX�p�����[�^�擾
		GetU8(pAnm,&param);
		if (param == PARAM_X){
			target = &pAnm->TransX; 
		}else if (param == PARAM_Y){
			target = &pAnm->TransY;
		}else if (param == PARAM_DX){
			target = &pAnm->dx;
		}else if (param == PARAM_DY){
			target = &pAnm->dy;
		}else if (param == PARAM_RX){
			target = &pAnm->rx;
		}else if (param == PARAM_RY){
			target = &pAnm->ry;
		}else if (param == PARAM_ROT){
			target = &pAnm->Rot;
		}else{
			GF_ASSERT(0);
		}
	}
	
	{
		u8 idx;
		u8 use;
		GetU8(pAnm,&use);
		if (use == USE_VAL){
			GetInt(pAnm,&val);
		}else if(use == USE_WORK){
			GetIdx(pAnm,&idx);
			val = pAnm->Work[idx];
		}else{
			GF_ASSERT(0);
		}
	}

	{
		u8 calc;
		GetU8(pAnm,&calc);
		if (calc == PARAM_SET){
			(*target) = val;
		}else if (calc == PARAM_ADD){
			(*target) += val;
		}else{
			GF_ASSERT(0);
		}
	}

}

//--------------------------------------------------------------
/**
 * �A�j���f�[�^���g�����X�l���X�v���C�g�ɔ��f
 *
 * @param	pAnm			�A�j���|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_ApplyTrans(POKE_ANIME *pAnm)
{
	if (pAnm->PokeReverse){
		SoftSpriteParaSet(pAnm->SoftSprite, SS_PARA_POS_X, pAnm->OrgX-(pAnm->TransX+pAnm->dx));
	}else{
		SoftSpriteParaSet(pAnm->SoftSprite, SS_PARA_POS_X, pAnm->OrgX+pAnm->TransX+pAnm->dx);
	}
	SoftSpriteParaSet(pAnm->SoftSprite, SS_PARA_POS_Y, pAnm->OrgY+pAnm->TransY+pAnm->dy);
//	SoftSpriteParaSet(pAnm->SoftSprite, SS_PARA_POS_OX, pAnm->dx);
//	SoftSpriteParaSet(pAnm->SoftSprite, SS_PARA_POS_OY, pAnm->dy);
///	OS_Printf("pos_x = %d\n",SoftSpriteParaGet(pAnm->SoftSprite,SS_PARA_POS_X));
}

//--------------------------------------------------------------
/**
 * �A�j���f�[�^����]�A�g�k�l���X�v���C�g�ɔ��f
 *
 * @param	pAnm			�A�j���|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_ApplyAffine(POKE_ANIME *pAnm)
{
	SoftSpriteParaSet(pAnm->SoftSprite, SS_PARA_AFF_X, 0x100+pAnm->rx);
	SoftSpriteParaSet(pAnm->SoftSprite, SS_PARA_AFF_Y, 0x100+pAnm->ry);
	SoftSpriteParaSet(pAnm->SoftSprite, SS_PARA_ROT_Z, (u16)pAnm->Rot);

	{
		int correct;
		//d���␳���邩�H
		if (pAnm->CorrectDy == CORRECT_ON_MINUS){
			//�g�k�����}�C�i�X�̂Ƃ��ɕ␳����
			if (pAnm->ry < 0){
				CorrectDy(pAnm);
			}
		}else if (pAnm->CorrectDy == CORRECT_ON_NOT_EQ){
			//�g�k�������{�ł͂Ȃ��Ƃ��ɕ␳����
			if (pAnm->ry != 0){
				CorrectDy(pAnm);
			}
		}else if(pAnm->CorrectDy == CORRECT_OFF){
			return;
		}else{
			GF_ASSERT(0);
		}
	}
}

//--------------------------------------------------------------
/**
 * �ړ��l(dx.dy)���A�j���f�[�^��D�l�ɃZ�b�g
 *
 * @param	pAnm			�A�j���|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_SetD(POKE_ANIME *pAnm)
{
	u8 idx;
	u8 trans;
	
	//���[�N�C���f�b�N�X�擾
	GetIdx(pAnm, &idx);
	
	//�ύX�Ώێ擾
	ADRS_SHIFT(pAnm->SeqAdrs);
	trans =  (int)GetSeqAdrs(pAnm->SeqAdrs);
	if ((trans == PARAM_X)||(trans == PARAM_DX)){
		pAnm->dx = pAnm->Work[idx];
	}else if ((trans == PARAM_Y)||(trans == PARAM_DY)){
		pAnm->dy = pAnm->Work[idx];
	}else{
		GF_ASSERT(0);
	}
}

//--------------------------------------------------------------
/**
 * �E�F�C�g�ɃZ�b�g
 *
 * @param	pAnm			�A�j���|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_SetWait(POKE_ANIME *pAnm)
{
	//���[�N�C���f�b�N�X�擾
	GetInt(pAnm, &pAnm->Wait);
	pAnm->Request = 1;
}

//--------------------------------------------------------------
/**
 *�@�p���b�g�t�F�[�h
 *
 * @param	pAnm			�A�j���|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_PaletteFade(POKE_ANIME *pAnm)
{
	u8 start,end,wait;
	int rgb;
	
	GetU8(pAnm,&start);
	GetU8(pAnm,&end);
	GetU8(pAnm,&wait);
	GetInt(pAnm,&rgb);

	SoftSpritePalFadeSet(pAnm->SoftSprite, start, end, wait, rgb);
	
}

//--------------------------------------------------------------
/**
 *�@�p���b�g�t�F�[�h�E�F�C�g
 *
 * @param	pAnm			�A�j���|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_WaitPaletteFade(POKE_ANIME *pAnm)
{
	u8 start,end,wait;

	if( SoftSpritePalFadeExist(pAnm->SoftSprite) ){//�t�F�[�h�̏󋵂��݂�
		//�t�F�[�h�p��
		pAnm->PalFadeWaitFlg = 1;
		pAnm->Request = 1;
	}
}


////////////////////////////////////////////////////////////////////////////////
//����֐��Z�b�g�R�}���h

//--------------------------------------------------------------
/**
 * �R�}���h���߃z�[���h
 *
 * @param	pAnm			�A�j���|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_HoldAnmCommand(POKE_ANIME *pAnm)
{
	pAnm->CommandHold = 1;
}

//--------------------------------------------------------------
/**
 * DY�␳�L���t���O�R���g���[��
 *
 * @param	pAnm			�A�j���|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_SetDyCorrect(POKE_ANIME *pAnm)
{
	GetU8(pAnm,&pAnm->CorrectDy);
	GF_ASSERT(	(pAnm->CorrectDy==CORRECT_ON_MINUS)||
				(pAnm->CorrectDy==CORRECT_ON_NOT_EQ)||
				(pAnm->CorrectDy==CORRECT_OFF)
			&&"ERROR:Correct Unknown");
}

//--------------------------------------------------------------
/**
 * �J�[�u�֐����R�[��
 *
 * @param	pAnm			�A�j���|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_CallMoveFuncCurve(POKE_ANIME *pAnm)
{
	CallMoveFuc(pAnm, MOVE_CURVE);
}

//--------------------------------------------------------------
/**
 *�@�J�[�u�񐔕����֐����R�[��
 *
 * @param	pAnm			�A�j���|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_CallMoveFuncCurveDivTime(POKE_ANIME *pAnm)
{
	CallMoveFuc(pAnm, MOVE_CURVE_DIVTIME);
}

//--------------------------------------------------------------
/**
 * ���C���֐����R�[��
 *
 * @param	pAnm			�A�j���|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_CallMoveFuncLine(POKE_ANIME *pAnm)
{
	CallMoveFuc(pAnm, MOVE_LINE);
}

//--------------------------------------------------------------
/**
 *�@���C���񐔕����֐����R�[��
 *
 * @param	pAnm			�A�j���|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_CallMoveFuncLineDivTime(POKE_ANIME *pAnm)
{
	CallMoveFuc(pAnm, MOVE_LINE_DIVTIME);
}

//--------------------------------------------------------------
/**
 *�@���C���ړI�l�w��֐����R�[��
 *
 * @param	pAnm			�A�j���|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PAnm_CallMoveFuncLineDst(POKE_ANIME *pAnm)
{
	CallMoveFuc(pAnm, MOVE_LINE_DST);
}


/////////////////////////////////////////////////////////////////////////////////////////////
//�A�j������֐��֘A

//--------------------------------------------------------------
/**
 * �A�j���f�[�^������ϐ��ɓ���֐�������l�𔽉f
 *
 * @param	inType			�K�p���@
 * @param	inApplyVal		�K�p�l
 * @param	outTarget		�K�p�Ώ�
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void ApplyMoveVal(const u8 inType, const int *inStartVal, const int *inApplyVal, int *outTarget )
{
	if (inType == APPLY_SET){			//�Z�b�g
		(*outTarget) = (*inApplyVal);
	}else if(inType == APPLY_ADD){		//�J�n�l�ɉ��Z
		(*outTarget) = (*inStartVal) + (*inApplyVal);
	}else if(inType == APPLY_SYNTHE){	//���ݒl�ɉ��Z(����)
		(*outTarget) += (*inApplyVal);
	}else{
		GF_ASSERT(0);
	}
}

//--------------------------------------------------------------
/**
 *	�ύX�Ώێ擾
 *
 * @param	inTarget		�K�p�Ώ�
 * @param	pMFD			����֐��f�[�^�|�C���^
 * @param	pAnm			�A�j���f�[�^�|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void GetTarget(	const u8 inTarget, MOVE_FUNC_DATA_PTR pMFD, POKE_ANM_PTR pAnm )
{
	switch(inTarget){
	case TARGET_DX:
		pMFD->Target = &pMFD->dx;
		pMFD->ApplyTarget = &pAnm->dx;
		pMFD->StartVal = pAnm->dx;
		break;
	case TARGET_DY:
		pMFD->Target = &pMFD->dy;
		pMFD->ApplyTarget = &pAnm->dy;
		pMFD->StartVal = pAnm->dy;
		break;
	case TARGET_RX:
		pMFD->Target = &pMFD->rx;
		pMFD->ApplyTarget = &pAnm->rx;
		pMFD->StartVal = pAnm->rx;
		break;
	case TARGET_RY:
		pMFD->Target = &pMFD->ry;
		pMFD->ApplyTarget = &pAnm->ry;
		pMFD->StartVal = pAnm->ry;
		break;
	case TARGET_ROT:
		pMFD->Target = &pMFD->Rot;
		pMFD->ApplyTarget = &pAnm->Rot;
		pMFD->StartVal = pAnm->Rot;
		break;
	default:
		GF_ASSERT(0&&"ERROR:UnkownTarget!");
	}
}

//--------------------------------------------------------------
/**
 * ����֐��R�[��
 * ����֐��̃��[�N�͂߂Ďg������
 *
 * @param	pAnm				�A�j���|�C���^
 * @param	inMoveFuncNo		����֐��ԍ�
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void CallMoveFuc(POKE_ANIME *pAnm, const int inMoveFuncNo)
{
	u8 i;
	MOVE_FUNC_DATA_PTR ptr;	
	//�󂢂Ă���Ǘ��ꏊ�ɓ���֐����Z�b�g
	ptr = SetMoveFunc(pAnm,inMoveFuncNo);

	//�v�Z���ʓK�p���@���Z�b�g
	GetU8(pAnm,&ptr->ApplyType);

	//�֐����s�ҋ@���ԃZ�b�g
	GetU8(pAnm,&ptr->Wait);
	
	//����ɕK�v�ȃp�����[�^�̃Z�b�g
	for(i=0;i<MoveFuncTbl[inMoveFuncNo].ParamNum;i++){
		GetInt(pAnm,&ptr->Work[i]);
///		OS_Printf("param=%d\n",ptr->Work[i]);
	}

	{
		int idx;
		idx = MoveFuncTbl[inMoveFuncNo].TargetWorkIdx;

///		OS_Printf("workidx = %d:%d\n",idx,ptr->Work[idx]);
		//�ύX�Ώۂ̎擾
		GetTarget(ptr->Work[idx], ptr, pAnm);
	}

	if (ptr->Wait == 0){
		//������s
		ptr->Func(ptr,pAnm);
	}else{
		ptr->Wait--;
	}
}

//--------------------------------------------------------------
/**
 * �J�[�u�ړ�
 * work0:�J�[�u�^�C�v�i�Z�b�g�ρj
 * work1:�Ώ�  (�Z�b�g��)
 * work2:�U���i�Z�b�g�ρj
 * work3:���Z�p�x�i�Z�b�g�ρj
 * work4:�ʑ��i�Z�b�g�ρj
 * work5:�v�Z�񐔁i�Z�b�g�ρj
 * work6:�񐔂̃J�E���g
 *
 * @param	pMFD			����֐��f�[�^�|�C���^
 * @param	pAnm			�A�j���|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PMove_Curve(MOVE_FUNC_DATA_PTR pMFD, POKE_ANM_PTR pAnm)
{
	u16 rad;
	
	int *work;
	
	work = pMFD->Work;

	rad = (work[3]*(work[6]+1))+work[4];

	switch(work[0]){
	case CURVE_SIN:
		(*pMFD->Target) = FX_Whole( FX_SinIdx(rad)*work[2] );
		break;
	case CURVE_COS:
		(*pMFD->Target) = FX_Whole( FX_CosIdx(rad)*work[2] );
		break;
	case CURVE_SIN_MINUS:
		(*pMFD->Target) = -FX_Whole( FX_SinIdx(rad)*work[2] );
		break;
	case CURVE_COS_MINUS:
		(*pMFD->Target) = -FX_Whole( FX_CosIdx(rad)*work[2] );
		break;
	default:
		GF_ASSERT(0&&"ERROR:UnkownCurveType!");
	}
	
	ApplyMoveVal(pMFD->ApplyType, &(pMFD->StartVal), pMFD->Target, pMFD->ApplyTarget );

	work[6]++;

	if (work[6] >= work[5]){
		//�I��
		pMFD->Valid = FALSE;
	}
}

//--------------------------------------------------------------
/**
 * �J�[�u�ړ�	�񐔕���(���߂�ꂽ���s�񐔓��ŁA�w��l���̈ړ�������@���R����)
 * work0:�J�[�u�^�C�v�i�Z�b�g�ρj
 * work1:�Ώ� (�Z�b�g��)
 * work2:�U���i�Z�b�g�ρj
 * work3:�p�x�i�Z�b�g�ρj
 * work4:�ʑ��i�Z�b�g�ρj
 * work5:�v�Z�񐔁i�Z�b�g�ρj
 * work6:�񐔂̃J�E���g
 *
 * @param	pMFD			����֐��f�[�^�|�C���^
 * @param	pAnm			�A�j���|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PMove_CurveDivTime(MOVE_FUNC_DATA_PTR pMFD, POKE_ANM_PTR pAnm)
{
	u16 rad;
	
	int *work;
	
	work = pMFD->Work;

	rad = ( (work[3]*(work[6]+1))/work[5] )+work[4];

	switch(work[0]){
	case CURVE_SIN:
		(*pMFD->Target) = FX_Whole( FX_SinIdx(rad)*work[2] );
		break;
	case CURVE_COS:
		(*pMFD->Target) = FX_Whole( FX_CosIdx(rad)*work[2] );
		break;
	case CURVE_SIN_MINUS:
		(*pMFD->Target) = -FX_Whole( FX_SinIdx(rad)*work[2] );
		break;
	case CURVE_COS_MINUS:
		(*pMFD->Target) = -FX_Whole( FX_CosIdx(rad)*work[2] );
		break;
	default:
		GF_ASSERT(0&&"ERROR:UnkownCurveType!");
	}
	
	ApplyMoveVal(pMFD->ApplyType, &(pMFD->StartVal), pMFD->Target, pMFD->ApplyTarget );

	work[6]++;

	if (work[6] >= work[5]){
		//�I��
		pMFD->Valid = FALSE;
	}
}

//--------------------------------------------------------------
/**
 * �����ړ�
 * work0:�Ώ�  (�Z�b�g��)
 * work1:�����x�i�Z�b�g�ρj
 * work2:�����x�i�Z�b�g�ρj
 * work3:�v�Z�񐔁i�Z�b�g�ρj
 * work4:�񐔂̃J�E���g
 *
 * @param	pMFD			����֐��f�[�^�|�C���^
 * @param	pAnm			�A�j���|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PMove_Line(MOVE_FUNC_DATA_PTR pMFD, POKE_ANM_PTR pAnm)
{
	int move;
	int *work;
	
	work = pMFD->Work;

	move = work[1]+(work[2]*work[4]);

	(*pMFD->Target)+=move;

	ApplyMoveVal(pMFD->ApplyType, &(pMFD->StartVal), pMFD->Target, pMFD->ApplyTarget );

///	OS_Printf("trans=%d\n",pAnm->TransX);

	work[4]++;

	if (work[4] >= work[3]){
		//�I��
		pMFD->Valid = FALSE;
	}
}

//--------------------------------------------------------------
/**
 * �����ړ��@�񐔕���(���߂�ꂽ���s�񐔓��ŁA�w��l���̈ړ�������@���R����)
 * work0:�Ώ� (�Z�b�g��)
 * work1:�ړ��l�i�Z�b�g�ρj
 * work2:�v�Z�񐔁i�Z�b�g�ρj
 * work3:�񐔂̃J�E���g
 *
 * @param	pMFD			����֐��f�[�^�|�C���^
 * @param	pAnm			�A�j���|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PMove_LineDivTime(MOVE_FUNC_DATA_PTR pMFD, POKE_ANM_PTR pAnm)
{
	int move;
	int *work;
	
	work = pMFD->Work;

	move = ( (work[3]+1)*work[1] )/work[2];

	(*pMFD->Target) = move;

	ApplyMoveVal(pMFD->ApplyType, &(pMFD->StartVal), pMFD->Target, pMFD->ApplyTarget );

	work[3]++;

	if (work[3] >= work[2]){
		//�I��
		pMFD->Valid = FALSE;
	}
}

//--------------------------------------------------------------
/**
 * �����ړ��ړI�l�w��
 * work0:�Ώ�  (�Z�b�g��)
 * work1:�����x�i�Z�b�g�ρj
 * work2:�����x�i�Z�b�g�ρj
 * work3:�ړI�l�i�Z�b�g�ρj
 * work4:�񐔂̃J�E���g
 *
 * @param	pMFD			����֐��f�[�^�|�C���^
 * @param	pAnm			�A�j���|�C���^
 *
 * @retval	none
 */
//--------------------------------------------------------------
static void PMove_LineDst(MOVE_FUNC_DATA_PTR pMFD, POKE_ANM_PTR pAnm)
{
	int move;
	int *work;
	
	work = pMFD->Work;

	move = work[1]+(work[2]*work[4]);

	(*pMFD->Target)+=move;

	if ( (pMFD->ApplyType == APPLY_SET) ||
		 (pMFD->ApplyType == APPLY_SYNTHE) ){			//�Z�b�g
		if (move < 0){		//�������񂾒l���}�C�i�X�̏ꍇ
			if ((*pMFD->Target) <= work[3]){	//���ݒl�̂ق����ړI�l��菬������ΏI��
				(*pMFD->Target) = work[3];	//�ړI�l�Z�b�g
				pMFD->Valid = FALSE;
			}
		}else{				//�������񂾒l���v���X�̏ꍇ
			if ((*pMFD->Target) >= work[3]){	//���ݒl�̂ق����ړI�l���傫����ΏI��
				(*pMFD->Target) = work[3];	//�ړI�l�Z�b�g
				pMFD->Valid = FALSE;
			}
		}
	}else if(pMFD->ApplyType == APPLY_ADD){		//�J�n�l�ɉ��Z
		int val = pMFD->StartVal+(*pMFD->Target);
		if (move < 0){		//�������񂾒l���}�C�i�X�̏ꍇ
			if (val <= work[3]){	//���ݒl�̂ق����ړI�l��菬������ΏI��
				(*pMFD->Target) += (work[3]- val);	//�ړI�l�Z�b�g
				pMFD->Valid = FALSE;
			}
		}else{				//�������񂾒l���v���X�̏ꍇ
			if (val >= work[3]){	//���ݒl�̂ق����ړI�l���傫����ΏI��
				(*pMFD->Target) -= (val - work[3]);	//�ړI�l�Z�b�g
				pMFD->Valid = FALSE;
			}
		}
	}else{
		GF_ASSERT(0);
	}

	ApplyMoveVal(pMFD->ApplyType, &(pMFD->StartVal), pMFD->Target, pMFD->ApplyTarget );

///	OS_Printf("trans=%d\n",pAnm->TransX);

	work[4]++;
}


