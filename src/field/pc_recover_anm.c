//=============================================================================
/**
 * @file	pc_recover_anm.c
 * @bfief	�|�P�����Z���^�[�񕜃A�j��
 * @author	Nozomu Saito
 *
 */
//=============================================================================

#define BALL_ANM_CONT_CODE	(0x10)		//�{�[���A�j�����ʃR�[�h �l�͓K��
#define MONITOR_ANM_CONT_CODE	(0x20)	//���j�^�A�j�����ʃR�[�h �l�͓K��
#define BALL_PUT_WAIT	(15)			//�{�[������������̃E�F�C�g

#include "common.h"
#include "fieldsys.h"
#include "field_3d_anime.h"

#include "fielddata/build_model/build_model_id.h"
#include "system/snd_tool.h"

#include "pc_recover_anm.h"

enum{
	SEQ_START,
	SEQ_BALL_PUT,
	SEQ_PUT_WAIT,
	SEQ_ANM_START,
	SEQ_ANM_WAIT,
	SEQ_END
};

typedef struct PC_RECOV_ANM_tag
{
	VecFx32 MachinePos;	//�񕜃}�V�[�����W
	u8 MyPokeNum;		//�莝���|�P������	
	u8 NowPos;			//���ݔz�u���{�[����
	u8 Wait;			//�{�[����u���Ԋu
	u8 Seq;				//�V�[�P���T

	u8 EntryIdx[6];		//�{�[���ő�6��
}PC_RECOV_ANM;

static BOOL RecoverAnimeEvent(GMEVENT_CONTROL * event);

#define BALL_OFS	( (FX32_ONE*4)+(FX32_ONE/2) )		//4.5

//���񕜃}�V������Ƃ����{�[���z�u���W�iXYZ�j
static VecFx32 BallPos[6] = {
	{-BALL_OFS,FX32_ONE*12,-BALL_OFS},		//-4.5,12,-4.5
	{ BALL_OFS,FX32_ONE*12,-BALL_OFS},		//4.5,12,-4.5
	{-BALL_OFS,FX32_ONE*12,0},				//-4.5,12,0
	{ BALL_OFS,FX32_ONE*12,0},				//4.5,12,0
	{-BALL_OFS,FX32_ONE*12,BALL_OFS},		//-4.5,12,4.5
	{ BALL_OFS,FX32_ONE*12,BALL_OFS},		//4.5,12,4.5
};

//==============================================================================
/**
 * �񕜃}�V���A�j���[�V�����Z�b�g
 * 
 * @param	fsys			�t�B�[���h�V�X�e���|�C���^
 * @param	inBallNum		�{�[����
 * 
 * @return	none
 */
//==============================================================================
void PcRecoverAnm_StartAnm(FIELDSYS_WORK * fsys, const u8 inBallNum)
{
	BOOL rc;
	M3DO_PTR obj_ptr;
	int block_idx;
	int obj_id = BMID_MACHINE_PC02;

	rc = MPTL_CheckMap3DObj(fsys, obj_id, &obj_ptr,&block_idx);
			
	if (rc){
		//�񕜃}�V��������
		//�f�[�^�쐬
		PC_RECOV_ANM *work = sys_AllocMemoryLo(HEAPID_FIELD,sizeof(PC_RECOV_ANM));
		work->MyPokeNum = inBallNum;
		work->NowPos = 0;
		work->Wait = 0;
		work->Seq = 0;
		{
			VecFx32 trans;
			MPTL_CalcMapOffset(block_idx, GetWorldMapMatrixW(fsys->World), &trans);
			work->MachinePos = M3DO_GetGlobalVec(obj_ptr);
			work->MachinePos.x += trans.x;
			work->MachinePos.z += trans.z;
		}
		//�A�j���C�x���g�R�[��
		FieldEvent_Call(fsys->event, RecoverAnimeEvent, work);
	}else{
		GF_ASSERT(0&&"�|�P�Z���񕜃}�V������܂���");
	}
}

//==============================================================================
/**
 * �񕜃}�V�[���A�j���C�x���g
 * 
 * @param	event	�C�x���g�|�C���^
 * 
 * @return	BOOL	TRUE:�C�x���g�I���@FALSE:�C�x���g�p��
 */
//==============================================================================
static BOOL RecoverAnimeEvent(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	PC_RECOV_ANM *work = (PC_RECOV_ANM *)FieldEvent_GetSpecialWork(event);
	switch(work->Seq){
	case SEQ_START:
		{
			NNSG3dResMdl* ball_model;
			NNSG3dResFileHeader** ball_res_file;
			NNSG3dResMdl* moni_model;
			NNSG3dResFileHeader** moni_res_file;
			M3DO_PTR obj_ptr;
			NNSG3dRenderObj *render_obj;
			BOOL rc;
			
			ball_res_file = GetMapResourceModelRes(BMID_PC_MB, fsys->MapResource);
			moni_res_file = GetMapResourceModelRes(BMID_MACHINE_PC03, fsys->MapResource);
			ball_model = NNS_G3dGetMdlByIdx(NNS_G3dGetMdlSet(*ball_res_file),0);
			moni_model = NNS_G3dGetMdlByIdx(NNS_G3dGetMdlSet(*moni_res_file),0);
			//�{�[���A�j���[�V�����Z�b�g�A�b�v
			F3DASub_SetUpAnimation( fsys->field_3d_anime,
									fsys->AnimeContMng,
									BALL_ANM_CONT_CODE,	//�{�[���A�j�����ʃR�[�h
									BMID_PC_MB,
									NULL,			//��Ŏw��
									ball_model,
									GetMapResourceBmTexturePTR(fsys->MapResource),
									1,				//�A�j����1
									1,		//���[�v1��
									FALSE			//���]���Ȃ�
									);

			rc = MPTL_CheckMap3DObj(fsys, BMID_MACHINE_PC03, &obj_ptr,NULL);
			GF_ASSERT(rc);
			render_obj = M3DO_GetRenderObj(obj_ptr);
			
			//���j�^�A�j���[�V�����Z�b�g�A�b�v
			F3DASub_SetUpAnimation( fsys->field_3d_anime,
									fsys->AnimeContMng,
									MONITOR_ANM_CONT_CODE,	//���j�^�A�j�����ʃR�[�h
									BMID_MACHINE_PC03,
									render_obj,			//�|�P�Z�����j�^�[�̃����_�[�n�a�i
									moni_model,
									GetMapResourceBmTexturePTR(fsys->MapResource),
									1,				//�A�j����1
									1,		//���[�v1��
									FALSE			//���]���Ȃ�
									);
		}
		(work->Seq)++;
		break;
	case SEQ_BALL_PUT:
		{
			M3DO_PTR obj_ptr;
			NNSG3dRenderObj *render_obj;
			VecFx32 pos;
			VecFx32 rot = {0,0,0 };
			
			pos.x = work->MachinePos.x + BallPos[work->NowPos].x;
			pos.y = work->MachinePos.y + BallPos[work->NowPos].y;
			pos.z = work->MachinePos.z + BallPos[work->NowPos].z;
			//�{�[����u����
			Snd_SePlay(SEQ_SE_DP_BOWA);
			
			//�����X�^�[�{�[����u��
			work->EntryIdx[work->NowPos] = 
				M3DO_SetMap3DObjExp(fsys->Map3DObjExp,
									fsys->MapResource,
									BMID_PC_MB,
									&pos,
									&rot,
									fsys->field_3d_anime);
			//�n�a�i�|�C���^����蒼���āA�����_�[�n�a�i���Z�b�g
			obj_ptr = M3DO_GetMap3DObjDataFromIndex(fsys->Map3DObjExp, work->EntryIdx[work->NowPos]);
			render_obj = M3DO_GetRenderObj(obj_ptr);
			F3DASub_EntryRenderObj(fsys->AnimeContMng, BALL_ANM_CONT_CODE, work->NowPos, render_obj);
			(work->Seq)++;
		}
		break;
	case SEQ_PUT_WAIT:
		if(work->Wait < BALL_PUT_WAIT){
			work->Wait++;
			break;
		}else{
			work->Wait = 0;;
		}
		//�u�����{�[���̐����莝�����Ȃ玟�̃V�[�P���X��
		work->NowPos++;
		if (work->NowPos < work->MyPokeNum){
			(work->Seq) = SEQ_BALL_PUT;
		}else{
			(work->Seq)++;
		}
		break;
	case SEQ_ANM_START:
		//�����X�^�[�{�[���A�j���[�V�����X�^�[�g
		F3DASub_StartAnimation(fsys->AnimeContMng, BALL_ANM_CONT_CODE, 0);
		//���j�^�[�A�j���X�^�[�g
		F3DASub_StartAnimation(fsys->AnimeContMng, MONITOR_ANM_CONT_CODE, 0);
		//�񕜃W���O��
		Snd_MePlay( SEQ_ASA );

		(work->Seq)++;
		break;
	case SEQ_ANM_WAIT:
		//�A�j���E�W���O���҂�
		if ( (F3DASub_WaitAnimation(fsys->AnimeContMng, BALL_ANM_CONT_CODE))&&
			 (F3DASub_WaitAnimation(fsys->AnimeContMng, MONITOR_ANM_CONT_CODE))&&
			 (Snd_MePlayCheckBgmPlay() == FALSE) ){
			u8 i;
			//�A�j�����
			F3DASub_RereaseAnimation(fsys->field_3d_anime, fsys->AnimeContMng, MONITOR_ANM_CONT_CODE);
			F3DASub_RereaseAnimation(fsys->field_3d_anime, fsys->AnimeContMng, BALL_ANM_CONT_CODE);
			//�ǉ������{�[���n�a�i���������
			for(i=0;i<work->MyPokeNum;i++){
				M3DO_CleanMap3DObj(work->EntryIdx[i], fsys->Map3DObjExp);
			}
			(work->Seq)++;
		}
		break;
	case SEQ_END:
		//�I��
		sys_FreeMemoryEz(work);
		return TRUE;
	}

	return FALSE;
}

