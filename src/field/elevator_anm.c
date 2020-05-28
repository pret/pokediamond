//=============================================================================
/**
 * @file	elevator_anm.c
 * @bfief	�G���x�[�^�[�A�j��
 * @author	Nozomu Saito
 *
 */
//=============================================================================
#include "common.h"
#include "fieldsys.h"
#include "field_3d_anime.h"

#include "fielddata/build_model/build_model_id.h"
#include "system/snd_tool.h"

#include "elevator_anm_def.h"

#include "elevator_anm.h"

#define ELE_ANM_CONT_CODE	(0x1)		//�G���x�[�^�A�j�����ʃR�[�h �l�͓K��
enum{
	SEQ_SETUP,
	SEQ_ANM_START,
	SEQ_ANM_WAIT,
	SEQ_SE_WAIT,
	SEQ_END
};

typedef struct ELEVATOR_ANM_tag
{
	u8 Loop;		//�A�j�����[�v��	
	u8 Dir;			//����
	u8 Seq;			//�V�[�P���T
	u8 dummy;
}ELEVATOR_ANM;

static BOOL ElevatorAnimeEvent(GMEVENT_CONTROL * event);

//==============================================================================
/**
 * �G�X�J���[�^�A�j���[�V�����Z�b�g
 * 
 * @param	fsys		�t�B�[���h�V�X�e���|�C���^
 * @param	inDir		�����i�㉺�j
 * @param	inLoop		�A�j�����[�v��
 * 
 * @return	none
 */
//==============================================================================
void ElevatorAnm_StartAnm(FIELDSYS_WORK * fsys, const u8 inDir, const u8 inLoop)
{
	BOOL rc;

	rc = MPTL_CheckMap3DObj(fsys, BMID_EV_O01, NULL, NULL);
			
	if (rc){
		//�G���x�[�^�[������
		//�f�[�^�쐬
		ELEVATOR_ANM *work = sys_AllocMemoryLo(HEAPID_FIELD,sizeof(ELEVATOR_ANM));
		work->Loop = inLoop;
		work->Dir = inDir;
		work->Seq = 0;
		//�A�j���C�x���g�R�[��
		FieldEvent_Call(fsys->event, ElevatorAnimeEvent, work);
	}else{
		GF_ASSERT(0&&"�G���x�[�^�[����܂���");
	}
}

//==============================================================================
/**
 * �G���x�[�^�A�j���C�x���g
 * 
 * @param	event	�C�x���g�|�C���^
 * 
 * @return	BOOL	TRUE:�C�x���g�I���@FALSE:�C�x���g�p��
 */
//==============================================================================
static BOOL ElevatorAnimeEvent(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	ELEVATOR_ANM *work = (ELEVATOR_ANM *)FieldEvent_GetSpecialWork(event);
	switch(work->Seq){
	case SEQ_SETUP:
		{
			NNSG3dResMdl* model;
			NNSG3dResFileHeader** res_file;
			M3DO_PTR obj_ptr;
			NNSG3dRenderObj *render_obj;
			BOOL rc;
			res_file = GetMapResourceModelRes(BMID_EV_O01, fsys->MapResource);
			model = NNS_G3dGetMdlByIdx(NNS_G3dGetMdlSet(*res_file),0);
			
			rc = MPTL_CheckMap3DObj(fsys, BMID_EV_O01, &obj_ptr,NULL);
			GF_ASSERT(rc);
			render_obj = M3DO_GetRenderObj(obj_ptr);
			//�A�j���[�V�����Z�b�g�A�b�v
			F3DASub_SetUpAnimation( fsys->field_3d_anime,
									fsys->AnimeContMng,
									ELE_ANM_CONT_CODE,	//�G���x�[�^�[�A�j�����ʃR�[�h
									BMID_EV_O01,
									render_obj,
									model,
									GetMapResourceBmTexturePTR(fsys->MapResource),
									2,				//�A�j����2
									work->Loop,		//���[�v
									FALSE			//���]���Ȃ�
									);
		}
		(work->Seq)++;
		break;
	case SEQ_ANM_START:
		GF_ASSERT( ((work->Dir==ELE_UP)||(work->Dir==ELE_DOWN))&&"�������s��" );
		//�A�j���[�V�����X�^�[�g
		F3DASub_StartAnimation(fsys->AnimeContMng, ELE_ANM_CONT_CODE, work->Dir);
		//�G���x�[�^�[��
		if (work->Dir==ELE_UP){	
			Snd_SePlay( SE_ELEBETA_UP);
		}else{	//work->Dir==ELE_DOWN
			Snd_SePlay( SE_ELEBETA_DOWN );
		}
		(work->Seq)++;
		break;
	case SEQ_ANM_WAIT:
		//�A�j���҂�
		if ( (F3DASub_WaitAnimation(fsys->AnimeContMng, ELE_ANM_CONT_CODE)) ){
			//���X�g�b�v
			if (work->Dir==ELE_UP){
				Snd_SeStopBySeqNo( SE_ELEBETA_UP, 0 );
			}else{	//work->Dir==ELE_DOWN
				Snd_SeStopBySeqNo( SE_ELEBETA_DOWN, 0 );
			}

			//�s���|�[��
			Snd_SePlay( SE_ELEBETA_ARRIVAL );
			
			//�A�j�����
			F3DASub_RereaseAnimation(fsys->field_3d_anime, fsys->AnimeContMng, ELE_ANM_CONT_CODE);
			(work->Seq)++;
		}
		break;
	case SEQ_SE_WAIT:
		if (!Snd_SePlayCheck(SE_ELEBETA_ARRIVAL)){
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
