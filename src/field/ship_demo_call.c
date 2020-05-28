//============================================================================================
/**
 * @file	ship_demo_call.c
 * @brief	�D�f���R�[��
 * @date	2006.05.23
 * @author	Nozomu Saito
 *
 */
//============================================================================================
#include "common.h"
#include "fieldsys.h"
#include "field_event.h"
#include "ev_mapchange.h"
#include "system/wipe.h"
#include "ship_demo.h"

#include "map_tool.h"
#include "system/brightness.h"
#include "system/snd_tool.h"
#include "fld_bgm.h"

#include "ship_demo_def.h"
#include "../fielddata/build_model/build_model_id.h"
#include "zonedata.h"
#include "fieldmap_work.h"

#include "fld_flg_init.h"

#include "ship_demo_call.h"

#define SHIP_SP_CNT	(24)

#define SHIP_SPEED	(FX32_ONE)
#define SHIP_SPEED_FIRST	(FX32_ONE/4)

#define BRIDGE_L_ANM_CONT_CODE	(1)	//��(��)�A�j�����ʃR�[�h
#define BRIDGE_R_ANM_CONT_CODE	(2)	//��(�E)�A�j�����ʃR�[�h

#define BRIDGE_OPEN_DIST	(14*16*FX32_ONE)
#define UP_MOVE_DIST	(25*16*FX32_ONE)
#define RIGHT_MOVE_DIST	(12*16*FX32_ONE)

#define BRIDGE_NONE	(0xffffffff)

#define CAM_MOVE_CNT_X	(FX32_ONE*16*2)
#define CAM_MONE_X	(FX32_ONE)
#define CAM_MOVE_CNT_Z	(FX32_ONE*16*3)
#define CAM_MONE_Z	(FX32_ONE/2)

enum{
	SEQ_FLD_SHIP_MOVE,
	SEQ_FLD_SHIP_MOVE_BRIDGE_OPEN,
	SEQ_FLD_FADE_OUT,
	SEQ_FLD_END_F_PROC,
	SEQ_FLD_CALL_DEMO,
	SEQ_FLD_MAP_JUMP,
	SEQ_FLD_START_F_PROC,
	SEQ_FLD_END,
};

typedef struct FSHIPDEMO_DAT_tag
{
	u8 Seq;				//�V�[�P���T
	u8 ShipDir;			//�D�f������
	u8 BridgeAnmFlg;	//���ˋ��A�j���J�n�t���O
	u8 ShipSpeedCnt;	//�X�s�[�h�����J�E���^
	u8 PlayerDir;		//�}�b�v�J�ڌ�̎��@����
	u8 CamMoveCnt;		//
	u8 dummy[2];
	fx32 CamColMove;
	
	int MoveDist;		//�t�B�[���h�ł̑D�n�a�i�̈ړ���
	fx32 BridgeOpen;	//���ˋ��J����A�j�����J�n����D�ړ��ʁi���ˋ������Ƃ���BRIDGE_NONE�j
	fx32 NowDist;			//���݈ړ�����
	
	int NextZone;		//�}�b�v�ψڐ�]�[��
	int NextX;			//�}�b�v�ψڐ�w
	int NextZ;			//�}�b�v�ψڐ�y
	VecFx32 CameraBindPos;	//�J�����o�C���h���W
	M3DO_PTR ShipObjPtr;//�D�n�a�i�̃|�C���^
	GLST_DATA LightData;
	fx32 ShipSpeed;
}FSHIPDEMO_DAT;

static void CallShipDemo(	FIELDSYS_WORK * fsys,
							const u8 inShipDir,
							GLST_DATA *inLightDataPtr);
static BOOL ShipDemoEvent(GMEVENT_CONTROL * event);
static BOOL FldShipDemoEvent(GMEVENT_CONTROL * event);
static BOOL MoveShip(FSHIPDEMO_DAT *f_dat);
static BOOL CheckBridge(const fx32 *inBridge, const fx32 *innow, u8 *outFlg);
static void SetBridgeAnime(FIELDSYS_WORK * fsys);
static void MoveCameraCol(FSHIPDEMO_DAT *f_dat);

//----------------------------------------------------------------------------
/**
 * @brief	�D�f���R�[��
 *
 * @param	fsys		�t�B�[���h�V�X�e���|�C���^
 *
 * @return	none
 *
 */
//-----------------------------------------------------------------------------
void ShipDemo_CallDemo(	FIELDSYS_WORK * fsys,
							const u8 inShipDir,
							const u8 inPlayerDir,
							const int inNextZone,
							const int inNextX,
							const int inNextZ)
{
	FSHIPDEMO_DAT *f_dat;
	BOOL fld_move_flg;
	BOOL rc;
	TARGET_RECT rect;
	int obj_id;

	int dist;
	
	f_dat = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(FSHIPDEMO_DAT));

	f_dat->ShipDir = inShipDir;			//�D�f������
	f_dat->PlayerDir = inPlayerDir;		//�}�b�v�J�ڌ�̎��@����
	f_dat->NextZone = inNextZone;		//�}�b�v�ψڐ�]�[��
	f_dat->NextX = inNextX;			//�}�b�v�ψڐ�w
	f_dat->NextZ = inNextZ;			//�}�b�v�ψڐ�y

	//���C�g���擾
	f_dat->LightData = *(fsys->glst_data);

	fld_move_flg = FALSE;
	f_dat->BridgeOpen = BRIDGE_NONE;
	f_dat->CamMoveCnt = 0;
	f_dat->CamColMove = 0;

	Snd_DataSetByScene( SND_SCENE_SUB_SHIP, 0, 0 );	// �T�E���h�f�[�^���[�h(�D�f��)(BGM���p��)
	
	if (inShipDir == SHIP_DIR_UP){
		obj_id = BMID_C2_O02;
		MPTL_MakeTargetRect(	Player_NowGPosXGet( fsys->player ),
								Player_NowGPosZGet( fsys->player ),
								1, -3, 3, 6, &rect );
		fld_move_flg = TRUE;
		dist = UP_MOVE_DIST;
		f_dat->BridgeOpen = BRIDGE_OPEN_DIST;
	}else if (inShipDir == SHIP_DIR_RIGHT){
		obj_id = BMID_C06_S02;
		MPTL_MakeTargetRect(	Player_NowGPosXGet( fsys->player ),
								Player_NowGPosZGet( fsys->player ),
								-2, 2, 6, 3, &rect );
		fld_move_flg = TRUE;
		dist = RIGHT_MOVE_DIST;
	}
	
	if (fld_move_flg){
		//�D�{��	
		rc = MPTL_CheckMap3DObjInRect(	fsys,
										obj_id,
										&rect,
										&f_dat->ShipObjPtr );

		if (rc){
			f_dat->MoveDist = dist;
			f_dat->NowDist = 0;
			f_dat->ShipSpeedCnt = 0;
			f_dat->ShipSpeed = SHIP_SPEED_FIRST;
			//��l�����W�擾���āA���[�N�ɃR�s�[
			Player_VecPosGet( fsys->player, &f_dat->CameraBindPos );	//�J�����o�C���h���W
			//��l���Ƃ̃J�����o�C���h������
			GFC_PurgeCameraTarget(fsys->camera_ptr);
			//���݈ʒu�ɃJ�������o�C���h
			GFC_BindCameraTarget(&f_dat->CameraBindPos, fsys->camera_ptr);
			//���ˋ��̗L���ŕ���
			if(f_dat->BridgeOpen != BRIDGE_NONE){	
				f_dat->BridgeAnmFlg = 0;		//���ˋ��A�j���t���O�𗎂Ƃ��Ă���
				f_dat->Seq = SEQ_FLD_SHIP_MOVE_BRIDGE_OPEN;		//���ˋ�����
				//�A�j���V�����Z�b�g�A�b�v
				SetBridgeAnime(fsys);
				
			}else{
				f_dat->Seq = SEQ_FLD_SHIP_MOVE;		//���ˋ��Ȃ�
			}

			//�D�J��
			Snd_SePlay( SE_SHIP_KITEKI );
		}else{
			GF_ASSERT(0&&"�D���Ȃ�");
			sys_FreeMemoryEz(f_dat);
			return;
		}
	}else{
		f_dat->Seq = SEQ_FLD_FADE_OUT;		//�t�B�[���h�f���͔�΂��āA�D�f����	
	}

	FieldEvent_Call(fsys->event, FldShipDemoEvent, f_dat);
}

//----------------------------------------------------------------------------
/**
 * @brief	�D�f���R�[��
 *
 * @param	fsys			�t�B�[���h�V�X�e���|�C���^
 * @param	inShipDir		�D�i�s����
 * @param	inLightDataPtr	���C�g�f�[�^�|�C���^
 *
 * @return	none
 *
 */
//-----------------------------------------------------------------------------
static void CallShipDemo(FIELDSYS_WORK * fsys, const u8 inShipDir, GLST_DATA *inLightDataPtr)
{
	SHIPDEMO_DAT *dat;
	dat = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(SHIPDEMO_DAT));
	//���C�g���擾
	dat->LightDataPtr = inLightDataPtr;
	dat->Dir = inShipDir;
	FieldEvent_Call(fsys->event, ShipDemoEvent, dat);
}

//----------------------------------------------------------------------------
/**
 * @brief	�D�f���C�x���g
 *
 * @param	event		�C�x���g�|�C���^
 *
 * @return	BOOL		TRUE:�C�x���g�I���@FALSE:�C�x���g�p��
 *
 */
//-----------------------------------------------------------------------------
static BOOL ShipDemoEvent(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	SHIPDEMO_DAT *dat = FieldEvent_GetSpecialWork(event);
	int *seq = FieldEvent_GetSeqWork(event);
	switch (*seq) {
	case 0:
		//�v���Z�X�o�^
		ShipDemo_ProcSet( fsys , dat );
		break;
	case 1:
		//�T�u�v���Z�X�I���҂�
		if (FieldEvent_Cmd_WaitSubProcEnd(fsys)) {
			return FALSE;
		}
		break;
	case 2:
		sys_FreeMemoryEz(dat);
		return TRUE;
	}
	(*seq) ++;
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 * @brief	�t�B�[���h�D�f���C�x���g
 *
 * @param	event		�C�x���g�|�C���^
 *
 * @return	BOOL		TRUE:�C�x���g�I���@FALSE:�C�x���g�p��
 *
 */
//-----------------------------------------------------------------------------
static BOOL FldShipDemoEvent(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	FSHIPDEMO_DAT *f_dat = FieldEvent_GetSpecialWork(event);
	switch (f_dat->Seq) {
	case SEQ_FLD_SHIP_MOVE:
		//�J�����␳
		MoveCameraCol(f_dat);
		//�D�ړ� ���݈ʒu�ƑD�̈ړ���A��������
		if ( MoveShip(f_dat) ){
			f_dat->Seq = SEQ_FLD_FADE_OUT;
		}
		break;
	case SEQ_FLD_SHIP_MOVE_BRIDGE_OPEN:
		{
			BOOL rc;
			//�J�����␳
			MoveCameraCol(f_dat);
			//�D�ړ� ���݈ʒu�ƑD�̈ړ���A��������
			rc = MoveShip(f_dat);
			if (!f_dat->BridgeAnmFlg){
				//�K��ʒu�܂ŗ�����A���ˋ��J���A�j���X�^�[�g
				if ( CheckBridge(&f_dat->BridgeOpen, &f_dat->NowDist, &f_dat->BridgeAnmFlg) ){
					//�A�j���[�V�����X�^�[�g
					F3DASub_StartAnimation(fsys->AnimeContMng, BRIDGE_L_ANM_CONT_CODE, 0);
					F3DASub_StartAnimation(fsys->AnimeContMng, BRIDGE_R_ANM_CONT_CODE, 0);
					//���ˋ��J����
					Snd_SePlay( SE_PIER_OPEN );	
				}
			}else{
				//���ˋ��J������A���̃V�[�P���X
				if ( (F3DASub_WaitAnimation(fsys->AnimeContMng, BRIDGE_L_ANM_CONT_CODE))&&
					 (F3DASub_WaitAnimation(fsys->AnimeContMng, BRIDGE_R_ANM_CONT_CODE))&&
					 rc ){
					f_dat->Seq = SEQ_FLD_FADE_OUT;
				}
			}
		}
		break;
	case SEQ_FLD_FADE_OUT:
		//���C�v�X�^�[�g	�u���b�N�A�E�g
		WIPE_SYS_Start(	WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT,
							WIPE_TYPE_FADEOUT,0x0,COMM_BRIGHTNESS_SYNC,1,HEAPID_WORLD );
		Snd_BgmFadeOut( 0, COMM_BRIGHTNESS_SYNC );
		f_dat->Seq = SEQ_FLD_END_F_PROC;
		break;
	case SEQ_FLD_END_F_PROC:
		//���C�v�E�a�f�l�t�F�[�h�I���҂�
		if ( !WIPE_SYS_EndCheck()||(Snd_FadeCheck()!=0) ){
			return FALSE;
		}
		if (f_dat->BridgeOpen != BRIDGE_NONE){
			//�A�j�����
			F3DASub_RereaseAnimation(fsys->field_3d_anime, fsys->AnimeContMng, BRIDGE_L_ANM_CONT_CODE);
			F3DASub_RereaseAnimation(fsys->field_3d_anime, fsys->AnimeContMng, BRIDGE_R_ANM_CONT_CODE);
		}
		//�C�x���g�R�}���h�F�t�B�[���h�}�b�v�v���Z�X�I��
		EventCmd_FinishFieldMap(event);
		f_dat->Seq = SEQ_FLD_CALL_DEMO;
		break;
	case SEQ_FLD_CALL_DEMO:
		//�D�f���R�[��
		CallShipDemo(fsys, f_dat->ShipDir, &f_dat->LightData);
		f_dat->Seq = SEQ_FLD_MAP_JUMP;
		break;
	case SEQ_FLD_MAP_JUMP:
		//�}�b�v�W�����v
		EventCmd_MapChange(event,
							f_dat->NextZone,
							DOOR_ID_JUMP_CODE,
							f_dat->NextX,
							f_dat->NextZ,
							f_dat->PlayerDir);
		f_dat->Seq = SEQ_FLD_START_F_PROC;
		break;
	case SEQ_FLD_START_F_PROC:
		//Snd_MapChangeFadeOutNextPlaySub( fsys, f_dat->NextZone, BGM_FADE_ROOM_MODE );
		Snd_EvMapChangeBgmPlay( fsys, f_dat->NextZone );

		//�t�B�[���h�v���Z�X���A(�t�F�[�h�C���t��)
		EventCmd_StartField_FadeIn(event);
		f_dat->Seq = SEQ_FLD_END;
		break;
	case SEQ_FLD_END:
		sys_FreeMemoryEz(f_dat);
		return TRUE;
	}
	return FALSE;
}

//----------------------------------------------------------------------------
/**
 * @brief	�t�B�[���h�D�̈ړ�
 *
 * @param	f_dat		�t�B�[���h�D�f���f�[�^�|�C���^
 *
 * @return	BOOL		TRUE:�ړI�����ړ��@FALSE:�ړ��p��
 *
 */
//-----------------------------------------------------------------------------
static BOOL MoveShip(FSHIPDEMO_DAT *f_dat)
{
	VecFx32 vec;
	vec = M3DO_GetGlobalVec(f_dat->ShipObjPtr);

	switch(f_dat->ShipDir){
	case SHIP_DIR_DOWN:
		vec.z += f_dat->ShipSpeed;
		f_dat->CameraBindPos.z += f_dat->ShipSpeed;
		break;
	case SHIP_DIR_UP:
		vec.z -= f_dat->ShipSpeed;
		f_dat->CameraBindPos.z -= f_dat->ShipSpeed;
		break;
	case SHIP_DIR_RIGHT:
		vec.x += f_dat->ShipSpeed;
		f_dat->CameraBindPos.x += f_dat->ShipSpeed;
		break;
	case SHIP_DIR_LEFT:
		vec.x -= f_dat->ShipSpeed;
		f_dat->CameraBindPos.x -= f_dat->ShipSpeed;
		break;
	default:
		GF_ASSERT(0);
		return TRUE;
	}

	if(f_dat->ShipSpeed < SHIP_SPEED){
		f_dat->ShipSpeedCnt++;
		if(f_dat->ShipSpeedCnt >= SHIP_SP_CNT){
			f_dat->ShipSpeed += FX32_ONE;
			f_dat->ShipSpeedCnt = 0;
		}
	}
	
	M3DO_SetGlobalVec(f_dat->ShipObjPtr, &vec);

	f_dat->NowDist += f_dat->ShipSpeed;
	if (f_dat->MoveDist<=f_dat->NowDist){
		return TRUE;
	}else{
		return FALSE;
	}		
}

//----------------------------------------------------------------------------
/**
 * @brief	�t�B�[���h�D�̈ړ�
 *
 * @param	inBridge	�A�j���J�n����D�ړ�����
 * @param	inNow		���݂̈ړ�����
 * @param	outFlg		�A�j���J�n�t���O�|�C���^
 *
 * @return	BOOL		TRUE:�A�j���J�n�@FALSE:�A�j���J�n�҂�
 *
 */
//-----------------------------------------------------------------------------
static BOOL CheckBridge(const fx32 *inBridge, const fx32 *inNow, u8 *outFlg)
{
	if ((*inBridge) <= (*inNow)){
		(*outFlg) = 1;	//�t���O����
		return TRUE;
	}else{
		return FALSE;
	}
}

//----------------------------------------------------------------------------
/**
 * @brief	���ˋ��A�j���Z�b�g�A�b�v
 *
 * @param	fsys		�t�B�[���h�V�X�e���|�C���^
 *
 * @return	none
 *
 */
//-----------------------------------------------------------------------------
static void SetBridgeAnime(FIELDSYS_WORK * fsys)
{
	u8 i;
	BOOL rc;
	int obj_id[2] = {BMID_C2_S03A, BMID_C2_S03B};
	int anm_code[2] = {BRIDGE_L_ANM_CONT_CODE, BRIDGE_R_ANM_CONT_CODE};

	for(i=0;i<2;i++){
		rc = MPTL_CheckMap3DObj(fsys, obj_id[i], NULL, NULL);
			
		if (rc){
			//���ˋ�������
			//�f�[�^�쐬
			NNSG3dResMdl* model;
			NNSG3dResFileHeader** res_file;
			M3DO_PTR obj_ptr;
			NNSG3dRenderObj *render_obj;
			res_file = GetMapResourceModelRes(obj_id[i], fsys->MapResource);
			model = NNS_G3dGetMdlByIdx(NNS_G3dGetMdlSet(*res_file),0);
			
			rc = MPTL_CheckMap3DObj(fsys, obj_id[i], &obj_ptr,NULL);
			GF_ASSERT(rc);
			render_obj = M3DO_GetRenderObj(obj_ptr);
			//�A�j���[�V�����Z�b�g�A�b�v
			F3DASub_SetUpAnimation( fsys->field_3d_anime,
									fsys->AnimeContMng,
									anm_code[i],	
									obj_id[i],
									render_obj,
									model,
									GetMapResourceBmTexturePTR(fsys->MapResource),
									1,				//�A�j����1
									1,				//���[�v1��
									FALSE			//���]���Ȃ�
									);	
		}else{
			GF_ASSERT(0&&"������܂���");
		}
	}
}

//----------------------------------------------------------------------------
/**
 * @brief	�J�����␳
 *
 * @param	f_dat		�t�B�[���h�D�f���f�[�^�|�C���^
 *
 * @return	none
 *
 */
//-----------------------------------------------------------------------------
static void MoveCameraCol(FSHIPDEMO_DAT *f_dat)
{
	switch(f_dat->ShipDir){
	case SHIP_DIR_UP:
		if (f_dat->CamColMove < CAM_MOVE_CNT_X){
			f_dat->CameraBindPos.x += CAM_MONE_X;
			f_dat->CamColMove+=CAM_MONE_X;
		}
		break;
	case SHIP_DIR_RIGHT:
		if (f_dat->CamColMove < CAM_MOVE_CNT_Z){
			f_dat->CameraBindPos.z += CAM_MONE_Z;
			f_dat->CamColMove+=CAM_MONE_Z;
		}
		break;
	default:
		GF_ASSERT(0);
		return;
	}

}
