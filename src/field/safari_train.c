//=============================================================================
/**
 * @file	safari_train.c
 * @bfief	サファリを縦断する乗り物の処理
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
//	fx32 NowPosZ;	//現在座標
	fx32 DstPosZ;	//目的座標
	int DecSpeedPos;	//減速位置
	
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
 * @brief	セットアップ
 * 
 * @param	fsys	フィールドシステムポインタ
 * 
 * @return	none
 */
//---------------------------------------------------------------------------
void SafariTrain_Setup(FIELDSYS_WORK *fsys)
{
	GIMMICKWORK *work;
	SAFARI_TRAIN_WORK *train_work;
	VecFx32 vec;
	//ここでギミックワークの中身を見る
	work = SaveData_GetGimmickWork(GameSystem_GetSaveData(fsys));
	train_work = (SAFARI_TRAIN_WORK*)GIMMICKWORK_Get(work, FLD_GIMMICK_SAFARI_TRAIN);

	//サファリ電車の位置をギミックワークから取得
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
	
	//ギミックワークの値で位置を分岐
	M3DO_SetMap3DObjExp(fsys->Map3DObjExp,
						fsys->MapResource,
						BMID_D6_TRAIN,
						&vec, NULL,
						fsys->field_3d_anime );
}

//---------------------------------------------------------------------------
/**
 * @brief	電車移動
 * 
 * @param	fsys	フィールドシステムポインタ
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

	//現在地と目的地を確認してパラメータ作成
	
	switch(train_work->NowPos){		//現在地
	case TRAIN_POS_1:
		est->Dir = TRAIN_DIR_DOWN;		//下方向移動
		//目的地
		if (inDstPos == TRAIN_POS_2){
			est->DstPosZ = TRAINE_STOP_POS_2;		//1-2区間下移動
			train_work->NowPos = TRAIN_POS_2;
			est->DecSpeedPos = DOWN_DEC_SP_POS2;
		}else{	//inDstPos == TRAIN_POS_3
			est->DstPosZ = TRAINE_STOP_POS_3;		//全区間移動
			train_work->NowPos = TRAIN_POS_3;
			est->DecSpeedPos = DOWN_DEC_SP_POS3;
		}
		break;
	case TRAIN_POS_2:
		//目的地
		if(inDstPos == TRAIN_POS_1){
			est->Dir = TRAIN_DIR_UP;	//上方向移動
			est->DstPosZ = TRAINE_STOP_POS_1;		//2-1区間上移動
			train_work->NowPos = TRAIN_POS_1;
			est->DecSpeedPos = UP_DEC_SP_POS1;
		}else{	//inDstPos == TRAIN_POS_3
			est->Dir = TRAIN_DIR_DOWN;	//下方向移動
			est->DstPosZ = TRAINE_STOP_POS_3;		//2-3区間下移動
			train_work->NowPos = TRAIN_POS_3;
			est->DecSpeedPos = DOWN_DEC_SP_POS3;
		}
		break;
	case TRAIN_POS_3:
		est->Dir = TRAIN_DIR_UP;		//上方向移動
		//目的地
		if(inDstPos == TRAIN_POS_1){
			est->DstPosZ = TRAINE_STOP_POS_1;		//全区間移動
			train_work->NowPos = TRAIN_POS_1;
			est->DecSpeedPos = UP_DEC_SP_POS1;
		}else{	//inDstPos == TRAIN_POS_2
			est->DstPosZ = TRAINE_STOP_POS_2;		//3-2区間上移動
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
 * @brief	電車の場所比較
 * 
 * @param	fsys	フィールドシステムポインタ
 * 
 * @return	u32		TRAIN_SAME_POS:電車と同じ位置　TRAIN_DIF_POS:電車と違う位置
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
 * @brief	移動
 * 
 * @param	event	イベントポインタ
 * 
 * @return	BOOL	TRUE:イベント終了	FALSE:イベント継続
 */
//---------------------------------------------------------------------------
static BOOL SafariTrianeMoveEnent(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	EVENT_SAFARI_TRAIN * est = FieldEvent_GetSpecialWork(event);

	switch (est->Seq) {
	case 0:
		//電車アニメセット
		{
			NNSG3dResMdl* model;
			NNSG3dResFileHeader** res_file;
			M3DO_PTR obj_ptr;
			NNSG3dRenderObj *render_obj;
			
			//電車OBJを取得
			obj_ptr = M3DO_GetMap3DObjDataFromID(fsys->Map3DObjExp, BMID_D6_TRAIN);
			render_obj = M3DO_GetRenderObj(obj_ptr);	
			res_file = GetMapResourceModelRes(BMID_D6_TRAIN, fsys->MapResource);
			model = NNS_G3dGetMdlByIdx(NNS_G3dGetMdlSet(*res_file),0);

			//電車アニメーションセットアップ
			F3DASub_SetUpAnimation( fsys->field_3d_anime,
									fsys->AnimeContMng,
									TRAIN_ANM_CONT_CODE,	//電車アニメ識別コード
									BMID_D6_TRAIN,
									render_obj,			//後で指定
									model,
									GetMapResourceBmTexturePTR(fsys->MapResource),
									1,				//アニメ数1
									LOOP_INFINIT,	//無限ループ
									FALSE			//反転しない
									);
			//アニメスタート
			F3DASub_StartAnimation(fsys->AnimeContMng, TRAIN_ANM_CONT_CODE, 0);
		}
		(est->Seq) ++;
		break;
	case 1:
		if (est->Type == MOVE_TYPE_RIDE){
			//発射ベル音
			Snd_SePlay( SE_TRAIN_BELL );
		}
		(est->Seq) ++;
	case 2:
		if ( !Snd_SePlayCheck( SE_TRAIN_BELL ) ){
			(est->Seq) ++;
		}
		break;
	case 3:
		//電車移動
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
		//電車アニメ終了
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
 * @brief	電車を呼んだときの電車の移動
 * 
 * @param	fsys		フィールドシステムポインタ
 * @param	est			イベントサファリ電車データポインタ
 * @param	outVec		位置ベクトル	
 * 
 * @return	BOOL		TRUE:移動終わり	FALSE:移動継続
 */
//---------------------------------------------------------------------------
static BOOL GetVecCallTrain(FIELDSYS_WORK *fsys, EVENT_SAFARI_TRAIN * est, const fx32 *inDst, VecFx32 *outVec)
{
	if (est->Dir == TRAIN_DIR_UP){
		//上移動
		outVec->z -= CallSpeedTbl[est->SpdTblNo];
		if ( (est->SpdTblNo<SPD_TBL_MAX-1)&&((outVec->z-TRAIN_OFS)/(FX32_ONE*16)<=est->DecSpeedPos) ){
			if ( ++(est->TblCounter) >= CallSpdTblNo[est->SpdTblNo] ){
				if (est->SpdTblNo == 0){
					//減速音
					Snd_SePlay( SE_TRAIN_END );
				}
				est->SpdTblNo++;
				est->TblCounter = 0;
			}
		}
	}else{
		//下移動
		outVec->z += CallSpeedTbl[est->SpdTblNo];
		if ( (est->SpdTblNo<SPD_TBL_MAX-1)&&((outVec->z-TRAIN_OFS)/(FX32_ONE*16)>=est->DecSpeedPos) ){
			if ( ++(est->TblCounter) >= CallSpdTblNo[est->SpdTblNo] ){
				if (est->SpdTblNo == 0){
					//減速音
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
 * @brief	電車に乗ったときの電車の移動
 * 
 * @param	fsys		フィールドシステムポインタ
 * @param	est			イベントサファリ電車データポインタ
 * @param	outVec		位置ベクトル	
 * 
 * @return	BOOL		TRUE:移動終わり	FALSE:移動継続
 */
//---------------------------------------------------------------------------
static BOOL GetVecRideTrain(FIELDSYS_WORK *fsys, EVENT_SAFARI_TRAIN * est, const fx32 *inDst, VecFx32 *outVec)
{
	FIELD_OBJ_PTR fop;
	VecFx32 player_vec;
	fop = Player_FieldOBJGet( fsys->player );
	Player_VecPosGet( fsys->player, &player_vec );
			
	//z座標変更。自機とあわせる
	outVec->z = player_vec.z+TRAIN_OFS;

	if (outVec->z == (*inDst)){
		return TRUE;
	}else{
		if (est->Dir == TRAIN_DIR_UP){
			//上移動
			if( FieldOBJ_AcmdSetCheck(fop) == TRUE ){	//アニメセットできるか?	
				FieldOBJ_AcmdSet(fop,SpeedTbl_UP[est->SpdTblNo]);	//自機上移動
				if ( (est->SpdTblNo<SPD_TBL_MAX-1)&&(Player_NowGPosZGet( fsys->player)>est->DecSpeedPos) ){
					if (est->SpdTblNo == 0){
						//加速音
						Snd_SePlay( SE_TRAIN_START );
					}
					est->SpdTblNo++;
				}else if ( Player_NowGPosZGet( fsys->player)<=est->DecSpeedPos ){
					if (est->SpdTblNo != 0){
						if (est->SpdTblNo == SPD_TBL_MAX-1){
							//減速音
							Snd_SePlay( SE_TRAIN_END );
						}
						est->SpdTblNo--;
					}
				}
			}
		}else{
			//下移動
			if( FieldOBJ_AcmdSetCheck(fop) == TRUE ){	//アニメセットできるか?	
				FieldOBJ_AcmdSet(fop,SpeedTbl_DOWN[est->SpdTblNo]);	//自機下移動
				if ( (est->SpdTblNo<SPD_TBL_MAX-1)&&(Player_NowGPosZGet( fsys->player)<est->DecSpeedPos) ){
					if (est->SpdTblNo == 0){
						//加速音
						Snd_SePlay( SE_TRAIN_START );
					}
					est->SpdTblNo++;
				}else if ( Player_NowGPosZGet( fsys->player)>=est->DecSpeedPos ){
					if (est->SpdTblNo != 0){
						if (est->SpdTblNo == SPD_TBL_MAX-1){
							//減速音
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
