//============================================================================================
/**
 * @file	ship_demo_call.c
 * @brief	船デモコール
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

#define BRIDGE_L_ANM_CONT_CODE	(1)	//橋(左)アニメ識別コード
#define BRIDGE_R_ANM_CONT_CODE	(2)	//橋(右)アニメ識別コード

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
	u8 Seq;				//シーケンサ
	u8 ShipDir;			//船デモ方向
	u8 BridgeAnmFlg;	//跳ね橋アニメ開始フラグ
	u8 ShipSpeedCnt;	//スピード加速カウンタ
	u8 PlayerDir;		//マップ遷移後の自機向き
	u8 CamMoveCnt;		//
	u8 dummy[2];
	fx32 CamColMove;
	
	int MoveDist;		//フィールドでの船ＯＢＪの移動量
	fx32 BridgeOpen;	//跳ね橋開けるアニメを開始する船移動量（跳ね橋無いときはBRIDGE_NONE）
	fx32 NowDist;			//現在移動距離
	
	int NextZone;		//マップ変移先ゾーン
	int NextX;			//マップ変移先Ｘ
	int NextZ;			//マップ変移先Ｚ
	VecFx32 CameraBindPos;	//カメラバインド座標
	M3DO_PTR ShipObjPtr;//船ＯＢＪのポインタ
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
 * @brief	船デモコール
 *
 * @param	fsys		フィールドシステムポインタ
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

	f_dat->ShipDir = inShipDir;			//船デモ方向
	f_dat->PlayerDir = inPlayerDir;		//マップ遷移後の自機向き
	f_dat->NextZone = inNextZone;		//マップ変移先ゾーン
	f_dat->NextX = inNextX;			//マップ変移先Ｘ
	f_dat->NextZ = inNextZ;			//マップ変移先Ｚ

	//ライト情報取得
	f_dat->LightData = *(fsys->glst_data);

	fld_move_flg = FALSE;
	f_dat->BridgeOpen = BRIDGE_NONE;
	f_dat->CamMoveCnt = 0;
	f_dat->CamColMove = 0;

	Snd_DataSetByScene( SND_SCENE_SUB_SHIP, 0, 0 );	// サウンドデータロード(船デモ)(BGM引継ぎ)
	
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
		//船捜す	
		rc = MPTL_CheckMap3DObjInRect(	fsys,
										obj_id,
										&rect,
										&f_dat->ShipObjPtr );

		if (rc){
			f_dat->MoveDist = dist;
			f_dat->NowDist = 0;
			f_dat->ShipSpeedCnt = 0;
			f_dat->ShipSpeed = SHIP_SPEED_FIRST;
			//主人公座標取得して、ワークにコピー
			Player_VecPosGet( fsys->player, &f_dat->CameraBindPos );	//カメラバインド座標
			//主人公とのカメラバインドを解く
			GFC_PurgeCameraTarget(fsys->camera_ptr);
			//現在位置にカメラをバインド
			GFC_BindCameraTarget(&f_dat->CameraBindPos, fsys->camera_ptr);
			//跳ね橋の有無で分岐
			if(f_dat->BridgeOpen != BRIDGE_NONE){	
				f_dat->BridgeAnmFlg = 0;		//跳ね橋アニメフラグを落としておく
				f_dat->Seq = SEQ_FLD_SHIP_MOVE_BRIDGE_OPEN;		//跳ね橋ある
				//アニメションセットアップ
				SetBridgeAnime(fsys);
				
			}else{
				f_dat->Seq = SEQ_FLD_SHIP_MOVE;		//跳ね橋ない
			}

			//汽笛音
			Snd_SePlay( SE_SHIP_KITEKI );
		}else{
			GF_ASSERT(0&&"船がない");
			sys_FreeMemoryEz(f_dat);
			return;
		}
	}else{
		f_dat->Seq = SEQ_FLD_FADE_OUT;		//フィールドデモは飛ばして、船デモへ	
	}

	FieldEvent_Call(fsys->event, FldShipDemoEvent, f_dat);
}

//----------------------------------------------------------------------------
/**
 * @brief	船デモコール
 *
 * @param	fsys			フィールドシステムポインタ
 * @param	inShipDir		船進行方向
 * @param	inLightDataPtr	ライトデータポインタ
 *
 * @return	none
 *
 */
//-----------------------------------------------------------------------------
static void CallShipDemo(FIELDSYS_WORK * fsys, const u8 inShipDir, GLST_DATA *inLightDataPtr)
{
	SHIPDEMO_DAT *dat;
	dat = sys_AllocMemoryLo(HEAPID_WORLD, sizeof(SHIPDEMO_DAT));
	//ライト情報取得
	dat->LightDataPtr = inLightDataPtr;
	dat->Dir = inShipDir;
	FieldEvent_Call(fsys->event, ShipDemoEvent, dat);
}

//----------------------------------------------------------------------------
/**
 * @brief	船デモイベント
 *
 * @param	event		イベントポインタ
 *
 * @return	BOOL		TRUE:イベント終了　FALSE:イベント継続
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
		//プロセス登録
		ShipDemo_ProcSet( fsys , dat );
		break;
	case 1:
		//サブプロセス終了待ち
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
 * @brief	フィールド船デモイベント
 *
 * @param	event		イベントポインタ
 *
 * @return	BOOL		TRUE:イベント終了　FALSE:イベント継続
 *
 */
//-----------------------------------------------------------------------------
static BOOL FldShipDemoEvent(GMEVENT_CONTROL * event)
{
	FIELDSYS_WORK * fsys = FieldEvent_GetFieldSysWork(event);
	FSHIPDEMO_DAT *f_dat = FieldEvent_GetSpecialWork(event);
	switch (f_dat->Seq) {
	case SEQ_FLD_SHIP_MOVE:
		//カメラ補正
		MoveCameraCol(f_dat);
		//船移動 現在位置と船の移動を連動させる
		if ( MoveShip(f_dat) ){
			f_dat->Seq = SEQ_FLD_FADE_OUT;
		}
		break;
	case SEQ_FLD_SHIP_MOVE_BRIDGE_OPEN:
		{
			BOOL rc;
			//カメラ補正
			MoveCameraCol(f_dat);
			//船移動 現在位置と船の移動を連動させる
			rc = MoveShip(f_dat);
			if (!f_dat->BridgeAnmFlg){
				//規定位置まで来たら、跳ね橋開くアニメスタート
				if ( CheckBridge(&f_dat->BridgeOpen, &f_dat->NowDist, &f_dat->BridgeAnmFlg) ){
					//アニメーションスタート
					F3DASub_StartAnimation(fsys->AnimeContMng, BRIDGE_L_ANM_CONT_CODE, 0);
					F3DASub_StartAnimation(fsys->AnimeContMng, BRIDGE_R_ANM_CONT_CODE, 0);
					//跳ね橋開く音
					Snd_SePlay( SE_PIER_OPEN );	
				}
			}else{
				//跳ね橋開いたら、次のシーケンス
				if ( (F3DASub_WaitAnimation(fsys->AnimeContMng, BRIDGE_L_ANM_CONT_CODE))&&
					 (F3DASub_WaitAnimation(fsys->AnimeContMng, BRIDGE_R_ANM_CONT_CODE))&&
					 rc ){
					f_dat->Seq = SEQ_FLD_FADE_OUT;
				}
			}
		}
		break;
	case SEQ_FLD_FADE_OUT:
		//ワイプスタート	ブラックアウト
		WIPE_SYS_Start(	WIPE_PATTERN_WMS, WIPE_TYPE_FADEOUT,
							WIPE_TYPE_FADEOUT,0x0,COMM_BRIGHTNESS_SYNC,1,HEAPID_WORLD );
		Snd_BgmFadeOut( 0, COMM_BRIGHTNESS_SYNC );
		f_dat->Seq = SEQ_FLD_END_F_PROC;
		break;
	case SEQ_FLD_END_F_PROC:
		//ワイプ・ＢＧＭフェード終了待ち
		if ( !WIPE_SYS_EndCheck()||(Snd_FadeCheck()!=0) ){
			return FALSE;
		}
		if (f_dat->BridgeOpen != BRIDGE_NONE){
			//アニメ解放
			F3DASub_RereaseAnimation(fsys->field_3d_anime, fsys->AnimeContMng, BRIDGE_L_ANM_CONT_CODE);
			F3DASub_RereaseAnimation(fsys->field_3d_anime, fsys->AnimeContMng, BRIDGE_R_ANM_CONT_CODE);
		}
		//イベントコマンド：フィールドマッププロセス終了
		EventCmd_FinishFieldMap(event);
		f_dat->Seq = SEQ_FLD_CALL_DEMO;
		break;
	case SEQ_FLD_CALL_DEMO:
		//船デモコール
		CallShipDemo(fsys, f_dat->ShipDir, &f_dat->LightData);
		f_dat->Seq = SEQ_FLD_MAP_JUMP;
		break;
	case SEQ_FLD_MAP_JUMP:
		//マップジャンプ
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

		//フィールドプロセス復帰(フェードイン付き)
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
 * @brief	フィールド船の移動
 *
 * @param	f_dat		フィールド船デモデータポインタ
 *
 * @return	BOOL		TRUE:目的距離移動　FALSE:移動継続
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
 * @brief	フィールド船の移動
 *
 * @param	inBridge	アニメ開始する船移動距離
 * @param	inNow		現在の移動距離
 * @param	outFlg		アニメ開始フラグポインタ
 *
 * @return	BOOL		TRUE:アニメ開始　FALSE:アニメ開始待ち
 *
 */
//-----------------------------------------------------------------------------
static BOOL CheckBridge(const fx32 *inBridge, const fx32 *inNow, u8 *outFlg)
{
	if ((*inBridge) <= (*inNow)){
		(*outFlg) = 1;	//フラグ成立
		return TRUE;
	}else{
		return FALSE;
	}
}

//----------------------------------------------------------------------------
/**
 * @brief	跳ね橋アニメセットアップ
 *
 * @param	fsys		フィールドシステムポインタ
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
			//跳ね橋あった
			//データ作成
			NNSG3dResMdl* model;
			NNSG3dResFileHeader** res_file;
			M3DO_PTR obj_ptr;
			NNSG3dRenderObj *render_obj;
			res_file = GetMapResourceModelRes(obj_id[i], fsys->MapResource);
			model = NNS_G3dGetMdlByIdx(NNS_G3dGetMdlSet(*res_file),0);
			
			rc = MPTL_CheckMap3DObj(fsys, obj_id[i], &obj_ptr,NULL);
			GF_ASSERT(rc);
			render_obj = M3DO_GetRenderObj(obj_ptr);
			//アニメーションセットアップ
			F3DASub_SetUpAnimation( fsys->field_3d_anime,
									fsys->AnimeContMng,
									anm_code[i],	
									obj_id[i],
									render_obj,
									model,
									GetMapResourceBmTexturePTR(fsys->MapResource),
									1,				//アニメ数1
									1,				//ループ1回
									FALSE			//反転しない
									);	
		}else{
			GF_ASSERT(0&&"橋ありません");
		}
	}
}

//----------------------------------------------------------------------------
/**
 * @brief	カメラ補正
 *
 * @param	f_dat		フィールド船デモデータポインタ
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
