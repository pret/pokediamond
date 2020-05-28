//=============================================================================
/**
 * @file	safari_train.c
 * @bfief	�T�t�@�����c�f�����蕨�̏���
 * @author	Nozomu Saito
 *
 */
//=============================================================================
#include "common.h"
#include "fieldsys.h"
#include "include/savedata/gimmickwork.h"
#include "../fielddata/build_model/build_model_id.h"
#include "field_gimmick_def.h"
#include "system/snd_tool.h"
#include "safari_train_def.h"

#include "safari_train_local.h"

#include "safari_train.h"

#define ONE_GRID	(FX32_ONE*16)

#define TRAIN_DIR_UP	(0)
#define TRAIN_DIR_DOWN	(1)

#define TRAIN_OFS			(ONE_GRID/2)
#define TRAIN_HEIGHT		(ONE_GRID)
#define TRAIN_POS_X			(ONE_GRID*(32*2+2))
#define TRAINE_STOP_POS_1	(ONE_GRID*(32*1+8))
#define TRAINE_STOP_POS_2	(ONE_GRID*(32*2+18))
#define TRAINE_STOP_POS_3	(ONE_GRID*(32*3+12))

#define TRAIN_SPEED	(ONE_GRID/2)

#define SPD_TBL_MAX	(7)
#define UP_DEC_SP_POS1		( (32*1+14) )
#define UP_DEC_SP_POS2		( (32*2+24) )
#define DOWN_DEC_SP_POS2	( (32*2+10) )
#define DOWN_DEC_SP_POS3	( (32*3+ 4) )

#define TRAIN_ANM_CONT_CODE	(16)

typedef	struct EVENT_SAFARI_TRAIN_tag EVENT_SAFARI_TRAIN;

typedef	BOOL	(*moveFunc)(FIELDSYS_WORK *fsys, EVENT_SAFARI_TRAIN * est, const fx32 *inDst, VecFx32 *outVec);

typedef struct EVENT_SAFARI_TRAIN_tag
{
	moveFunc	Func;
	u8 Dir;
	u8 Seq;
	u8 SpdTblNo;
	u8 TblCounter;
	int Type;
//	fx32 NowPosZ;	//���ݍ��W
	fx32 DstPosZ;	//�ړI���W
	int DecSpeedPos;	//�����ʒu
	
}EVENT_SAFARI_TRAIN;



static BOOL SafariTrianeMoveEnent(GMEVENT_CONTROL * event);
static BOOL GetVecCallTrain(FIELDSYS_WORK *fsys, EVENT_SAFARI_TRAIN * est, const fx32 *inDst, VecFx32 *outVec);
static BOOL GetVecRideTrain(FIELDSYS_WORK *fsys, EVENT_SAFARI_TRAIN * est, const fx32 *inDst, VecFx32 *outVec);

static const int SpeedTbl_UP[SPD_TBL_MAX] = {
	AC_WALK_U_32F,
	AC_WALK_U_16F,
	AC_WALK_U_8F,
	AC_WALK_U_8F,
	AC_WALK_U_4F,
	AC_WALK_U_4F,
	AC_WALK_U_2F,
};

static const int SpeedTbl_DOWN[SPD_TBL_MAX] = {
	AC_WALK_D_32F,
	AC_WALK_D_16F,
	AC_WALK_D_8F,
	AC_WALK_D_8F,
	AC_WALK_D_4F,
	AC_WALK_D_4F,
	AC_WALK_D_2F,
};

static const u8 CallSpdTblNo[] = 
{
	2, 4, 4, 8, 8, 16, 32, 
};

static const fx32 CallSpeedTbl[] = {
	FX32_ONE*8,
	FX32_ONE*4,
	FX32_ONE*4,
	FX32_ONE*2,
	FX32_ONE*2,
	FX32_ONE*1,
	FX32_ONE/2,
};

//---------------------------------------------------------------------------
/**
 * @brief	�Z�b�g�A�b�v
 * 
 * @param	fsys	�t�B�[���h�V�X�e���|�C���^
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void SafariTrain_Setup(FIELDSYS_WORK *fsys)
{
	GIMMICKWORK *work;
	SAFARI_TRAIN_WORK *train_work;
	VecFx32 vec;
	//�����ŃM�~�b�N���[�N�̒��g������
	work = SaveData_GetGimmickWork(GameSystem_GetSaveData(fsys));
	train_work = (SAFARI_TRAIN_WORK*)GIMMICKWORK_Get(work, FLD_GIMMICK_SAFARI_TRAIN);

	//�T�t�@���d�Ԃ̈ʒu���M�~�b�N���[�N����擾
	vec.x = TRAIN_POS_X;
	vec.y = TRAIN_HEIGHT;
	switch(train_work->NowPos){
	case TRAIN_POS_1:
		vec.z = TRAINE_STOP_POS_1;
		break;
	case TRAIN_POS_2:
		vec.z = TRAINE_STOP_POS_2;
		break;
	case TRAIN_POS_3:
		vec.z = TRAINE_STOP_POS_3;
		break;
	}
	
	//�M�~�b�N���[�N�̒l�ňʒu�𕪊�
	M3DO_SetMap3DObjExp(fsys->Map3DObjExp,
						fsys->MapResource,
						BMID_D6_TRAIN,
						&vec, NULL,
						fsys->field_3d_anime );
}

//---------------------------------------------------------------------------
/**
 * @brief	�d�Ԉړ�
 * 
 * @param	fsys	�t�B�[���h�V�X�e���|�C���^
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void SafariTrain_Move(FIELDSYS_WORK *fsys, const u16 inDstPos, const u16 inMoveType)
{
	GIMMICKWORK *work;
	SAFARI_TRAIN_WORK *train_work;
	EVENT_SAFARI_TRAIN *est;
	work = SaveData_GetGimmickWork(GameSystem_GetSaveData(fsys));
	train_work = (SAFARI_TRAIN_WORK*)GIMMICKWORK_Get(work, FLD_GIMMICK_SAFARI_TRAIN);
	est = sys_AllocMemoryLo(HEAPID_FIELD, sizeof(EVENT_SAFARI_TRAIN));

	memset(est,0,sizeof(EVENT_SAFARI_TRAIN));

	est->Seq = 0;
//	est->Type = inMoveType;

	//���ݒn�ƖړI�n���m�F���ăp�����[�^�쐬
	
	switch(train_work->NowPos){		//���ݒn
	case TRAIN_POS_1:
		est->Dir = TRAIN_DIR_DOWN;		//�������ړ�
		//�ړI�n
		if (inDstPos == TRAIN_POS_2){
			est->DstPosZ = TRAINE_STOP_POS_2;		//1-2��ԉ��ړ�
			train_work->NowPos = TRAIN_POS_2;
			est->DecSpeedPos = DOWN_DEC_SP_POS2;
		}else{	//inDstPos == TRAIN_POS_3
			est->DstPosZ = TRAINE_STOP_POS_3;		//�S��Ԉړ�
			train_work->NowPos = TRAIN_POS_3;
			est->DecSpeedPos = DOWN_DEC_SP_POS3;
		}
		break;
	case TRAIN_POS_2:
		//�ړI�n
		if(inDstPos == TRAIN_POS_1){
			est->Dir = TRAIN_DIR_UP;	//������ړ�
			est->DstPosZ = TRAINE_STOP_POS_1;		//2-1��ԏ�ړ�
			train_work->NowPos = TRAIN_POS_1;
			est->DecSpeedPos = UP_DEC_SP_POS1;
		}else{	//inDstPos == TRAIN_POS_3
			est->Dir = TRAIN_DIR_DOWN;	//�������ړ�
			est->DstPosZ = TRAINE_STOP_POS_3;		//2-3��ԉ��ړ�
			train_work->NowPos = TRAIN_POS_3;
			est->DecSpeedPos = DOWN_DEC_SP_POS3;
		}
		break;
	case TRAIN_POS_3:
		est->Dir = TRAIN_DIR_UP;		//������ړ�
		//�ړI�n
		if(inDstPos == TRAIN_POS_1){
			est->DstPosZ = TRAINE_STOP_POS_1;		//�S��Ԉړ�
			train_work->NowPos = TRAIN_POS_1;
			est->DecSpeedPos = UP_DEC_SP_POS1;
		}else{	//inDstPos == TRAIN_POS_2
			est->DstPosZ = TRAINE_STOP_POS_2;		//3-2��ԏ�ړ�
			train_work->NowPos = TRAIN_POS_2;
			est->DecSpeedPos = UP_DEC_SP_POS2;
		}
		break;
	default:
		GF_ASSERT(0);
		break;
	}

	est->Type = inMoveType;

	if (inMoveType == MOVE_TYPE_CALL){
		est->Func  = GetVecCallTrain;
	}else{
		est->Func  = GetVecRideTrain;
	}
	FieldEvent_Call(fsys->event, SafariTrianeMoveEnent, est);
}

//---------------------------------------------------------------------------
/**
 * @brief	�d�Ԃ̏ꏊ��r
 * 
 * @param	fsys	�t�B�[���h�V�X�e���|�C���^
 * 
 * @return	u32		TRAIN_SAME_POS:�d�ԂƓ����ʒu�@TRAIN_DIF_POS:�d�ԂƈႤ�ʒu
 */
//---------------------------------------------------------------------------
u32 SafariTrain_CheckPos(FIELDSYS_WORK *fsys, const u16 inPos)
{
	GIMMICKWORK *work;
	SAFARI_TRAIN_WORK *train_work;
	work = SaveData_GetGimmickWork(GameSystem_GetSaveData(fsys));
	train_work = (SAFARI_TRAIN_WORK*)GIMMICKWORK_Get(work, FLD_GIMMICK_SAFARI_TRAIN);
	if (train_work->NowPos == inPos){
		return TRAIN_SAME_POS;
	}else{
		return TRAIN_DIF_POS;
	}
}

//---------------------------------------------------------------------------
/**
 * @brief	�ړ�
 * 
 * @param	event	�C�x���g�|�C���^
 * 
 * @return	BOOL	TRUE:�C�x���g�I��	FALSE:�C�x���g�p��
 */
//---------------------------------------------------------------------------
static BOOL SafariTrianeMoveEnent(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_SAFARI_TRAIN * est = FieldEvent_GetSpecialWork(event);

	switch (est->Seq) {
	case 0:
		//�d�ԃA�j���Z�b�g
		{
			NNSG3dResMdl* model;
			NNSG3dResFileHeader** res_file;
			M3DO_PTR obj_ptr;
			NNSG3dRenderObj *render_obj;
			
			//�d��OBJ���擾
			obj_ptr = M3DO_GetMap3DObjDataFromID(fsys->Map3DObjExp, BMID_D6_TRAIN);
			render_obj = M3DO_GetRenderObj(obj_ptr);	
			res_file = GetMapResourceModelRes(BMID_D6_TRAIN, fsys->MapResource);
			model = NNS_G3dGetMdlByIdx(NNS_G3dGetMdlSet(*res_file),0);

			//�d�ԃA�j���[�V�����Z�b�g�A�b�v
			F3DASub_SetUpAnimation( fsys->field_3d_anime,
									fsys->AnimeContMng,
									TRAIN_ANM_CONT_CODE,	//�d�ԃA�j�����ʃR�[�h
									BMID_D6_TRAIN,
									render_obj,			//��Ŏw��
									model,
									GetMapResourceBmTexturePTR(fsys->MapResource),
									1,				//�A�j����1
									LOOP_INFINIT,	//�������[�v
									FALSE			//���]���Ȃ�
									);
			//�A�j���X�^�[�g
			F3DASub_StartAnimation(fsys->AnimeContMng, TRAIN_ANM_CONT_CODE, 0);
		}
		(est->Seq) ++;
		break;
	case 1:
		if (est->Type == MOVE_TYPE_RIDE){
			//���˃x����
			Snd_SePlay( SE_TRAIN_BELL );
		}
		(est->Seq) ++;
	case 2:
		if ( !Snd_SePlayCheck( SE_TRAIN_BELL ) ){
			(est->Seq) ++;
		}
		break;
	case 3:
		//�d�Ԉړ�
		{
			M3DO_PTR ptr;
			VecFx32 vec;
			ptr = M3DO_GetMap3DObjDataFromID(fsys->Map3DObjExp, BMID_D6_TRAIN);
			vec = M3DO_GetGlobalVec(ptr);
			if(	est->Func(fsys, est, &est->DstPosZ, &vec) ){
				(est->Seq) ++;
			}
			M3DO_SetGlobalVec(ptr, &vec);
		}
		break;
	case 4:
		//�d�ԃA�j���I��
		F3DASub_RereaseAnimation(fsys->field_3d_anime, fsys->AnimeContMng, TRAIN_ANM_CONT_CODE);
		(est->Seq) ++;
		break;
	case 5:
		sys_FreeMemoryEz(est);
		return TRUE;
	}
	return FALSE;
}

//---------------------------------------------------------------------------
/**
 * @brief	�d�Ԃ��Ă񂾂Ƃ��̓d�Ԃ̈ړ�
 * 
 * @param	fsys		�t�B�[���h�V�X�e���|�C���^
 * @param	est			�C�x���g�T�t�@���d�ԃf�[�^�|�C���^
 * @param	outVec		�ʒu�x�N�g��	
 * 
 * @return	BOOL		TRUE:�ړ��I���	FALSE:�ړ��p��
 */
//---------------------------------------------------------------------------
static BOOL GetVecCallTrain(FIELDSYS_WORK *fsys, EVENT_SAFARI_TRAIN * est, const fx32 *inDst, VecFx32 *outVec)
{
	if (est->Dir == TRAIN_DIR_UP){
		//��ړ�
		outVec->z -= CallSpeedTbl[est->SpdTblNo];
		if ( (est->SpdTblNo<SPD_TBL_MAX-1)&&((outVec->z-TRAIN_OFS)/(FX32_ONE*16)<=est->DecSpeedPos) ){
			if ( ++(est->TblCounter) >= CallSpdTblNo[est->SpdTblNo] ){
				if (est->SpdTblNo == 0){
					//������
					Snd_SePlay( SE_TRAIN_END );
				}
				est->SpdTblNo++;
				est->TblCounter = 0;
			}
		}
	}else{
		//���ړ�
		outVec->z += CallSpeedTbl[est->SpdTblNo];
		if ( (est->SpdTblNo<SPD_TBL_MAX-1)&&((outVec->z-TRAIN_OFS)/(FX32_ONE*16)>=est->DecSpeedPos) ){
			if ( ++(est->TblCounter) >= CallSpdTblNo[est->SpdTblNo] ){
				if (est->SpdTblNo == 0){
					//������
					Snd_SePlay( SE_TRAIN_END );
				}
				est->SpdTblNo++;
				est->TblCounter = 0;
			}
		}
	}
	if (outVec->z == (*inDst)){
		return TRUE;
	}else{
		return FALSE;
	}
}

//---------------------------------------------------------------------------
/**
 * @brief	�d�Ԃɏ�����Ƃ��̓d�Ԃ̈ړ�
 * 
 * @param	fsys		�t�B�[���h�V�X�e���|�C���^
 * @param	est			�C�x���g�T�t�@���d�ԃf�[�^�|�C���^
 * @param	outVec		�ʒu�x�N�g��	
 * 
 * @return	BOOL		TRUE:�ړ��I���	FALSE:�ړ��p��
 */
//---------------------------------------------------------------------------
static BOOL GetVecRideTrain(FIELDSYS_WORK *fsys, EVENT_SAFARI_TRAIN * est, const fx32 *inDst, VecFx32 *outVec)
{
	FIELD_OBJ_PTR fop;
	VecFx32 player_vec;
	fop = Player_FieldOBJGet( fsys->player );
	Player_VecPosGet( fsys->player, &player_vec );
			
	//z���W�ύX�B���@�Ƃ��킹��
	outVec->z = player_vec.z+TRAIN_OFS;

	if (outVec->z == (*inDst)){
		return TRUE;
	}else{
		if (est->Dir == TRAIN_DIR_UP){
			//��ړ�
			if( FieldOBJ_AcmdSetCheck(fop) == TRUE ){	//�A�j���Z�b�g�ł��邩?	
				FieldOBJ_AcmdSet(fop,SpeedTbl_UP[est->SpdTblNo]);	//���@��ړ�
				if ( (est->SpdTblNo<SPD_TBL_MAX-1)&&(Player_NowGPosZGet( fsys->player)>est->DecSpeedPos) ){
					if (est->SpdTblNo == 0){
						//������
						Snd_SePlay( SE_TRAIN_START );
					}
					est->SpdTblNo++;
				}else if ( Player_NowGPosZGet( fsys->player)<=est->DecSpeedPos ){
					if (est->SpdTblNo != 0){
						if (est->SpdTblNo == SPD_TBL_MAX-1){
							//������
							Snd_SePlay( SE_TRAIN_END );
						}
						est->SpdTblNo--;
					}
				}
			}
		}else{
			//���ړ�
			if( FieldOBJ_AcmdSetCheck(fop) == TRUE ){	//�A�j���Z�b�g�ł��邩?	
				FieldOBJ_AcmdSet(fop,SpeedTbl_DOWN[est->SpdTblNo]);	//���@���ړ�
				if ( (est->SpdTblNo<SPD_TBL_MAX-1)&&(Player_NowGPosZGet( fsys->player)<est->DecSpeedPos) ){
					if (est->SpdTblNo == 0){
						//������
						Snd_SePlay( SE_TRAIN_START );
					}
					est->SpdTblNo++;
				}else if ( Player_NowGPosZGet( fsys->player)>=est->DecSpeedPos ){
					if (est->SpdTblNo != 0){
						if (est->SpdTblNo == SPD_TBL_MAX-1){
							//������
							Snd_SePlay( SE_TRAIN_END );
						}
						est->SpdTblNo--;
					}
				}
			}
		}
	}
	return FALSE;
}
